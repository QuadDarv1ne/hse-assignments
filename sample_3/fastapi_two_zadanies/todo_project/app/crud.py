from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy.future import select
from sqlalchemy.orm import Session
from fastapi import HTTPException
from .models import Item
from .schemas import ItemCreate, ItemUpdate
from sqlalchemy import desc, asc

async def get_item_by_id(db: AsyncSession, item_id: int):
    """
    Получение задачи по её идентификатору.

    Args:
        db (AsyncSession): Сессия базы данных.
        item_id (int): Идентификатор задачи.

    Returns:
        Item: Найденная задача.

    Raises:
        HTTPException: Если задача с таким идентификатором не найдена.
    """
    result = await db.execute(select(Item).filter(Item.id == item_id))
    return result.scalars().first()

async def create_item(db: AsyncSession, item: ItemCreate):
    """
    Создание новой задачи.

    Args:
        db (AsyncSession): Сессия базы данных.
        item (ItemCreate): Данные задачи, которую нужно создать.

    Returns:
        Item: Созданная задача.
    """
    db_item = Item(
        title=item.title,
        description=item.description,
        completed=item.completed,
        priority=item.priority,
    )
    db.add(db_item)
    await db.commit()
    await db.refresh(db_item)
    return db_item

async def update_item(db: AsyncSession, item_id: int, item_data: ItemUpdate):
    """
    Обновление задачи по её идентификатору.

    Args:
        db (AsyncSession): Сессия базы данных.
        item_id (int): Идентификатор задачи.
        item_data (ItemUpdate): Обновлённые данные задачи.

    Returns:
        Item: Обновлённая задача.

    Raises:
        HTTPException: Если задача с таким идентификатором не найдена.
    """
    db_item = await get_item_by_id(db, item_id)
    if db_item is None:
        raise HTTPException(status_code=404, detail="Item not found")
    
    for key, value in item_data.dict(exclude_unset=True).items():
        setattr(db_item, key, value)

    await db.commit()
    await db.refresh(db_item)
    return db_item

async def get_items(db: AsyncSession, skip: int = 0, limit: int = 10, sort_by: str = "id", sort_order: str = "asc"):
    """
    Получение списка задач с поддержкой пагинации и сортировки.

    Args:
        db (AsyncSession): Сессия базы данных.
        skip (int): Количество пропускаемых записей.
        limit (int): Максимальное количество возвращаемых записей.
        sort_by (str): Поле для сортировки.
        sort_order (str): Порядок сортировки ("asc" или "desc").

    Returns:
        List[Item]: Список задач, удовлетворяющих запросу.
    """
    query = select(Item).offset(skip).limit(limit)
    if sort_order == "asc":
        query = query.order_by(asc(getattr(Item, sort_by)))
    else:
        query = query.order_by(desc(getattr(Item, sort_by)))

    result = await db.execute(query)
    return result.scalars().all()

async def delete_item(db: AsyncSession, item_id: int):
    """
    Удаление задачи по её идентификатору.

    Args:
        db (AsyncSession): Сессия базы данных.
        item_id (int): Идентификатор задачи.

    Returns:
        dict: Сообщение об успешном удалении задачи.

    Raises:
        HTTPException: Если задача с таким идентификатором не найдена.
    """
    db_item = await get_item_by_id(db, item_id)
    if db_item is None:
        raise HTTPException(status_code=404, detail="Item not found")
    
    await db.delete(db_item)
    await db.commit()
    return {"message": "Item deleted successfully"}
