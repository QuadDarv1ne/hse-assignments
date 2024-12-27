from fastapi import FastAPI, Depends, HTTPException, APIRouter, Query
from typing import List
from . import crud, models, schemas, dependencies
from sqlalchemy.ext.asyncio import AsyncSession
import logging

# Настройка логирования
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

app = FastAPI()

# Роутер для задач
router = APIRouter()

@router.post("/items/", response_model=schemas.ItemOut)
async def create_item(item: schemas.ItemCreate, db: AsyncSession = Depends(dependencies.get_db)):
    """
    **Создание новой задачи.**

    **Args:**

        - item (schemas.ItemCreate): Данные задачи для создания.

        - db (AsyncSession): Сессия базы данных.

    **Returns:**

        - schemas.ItemOut: Созданная задача с её данными.

    **Логирует создание задачи.**
    """
    logger.info(f"Creating item: {item.title}")
    return await crud.create_item(db=db, item=item)

@router.get("/items/", response_model=List[schemas.ItemOut])
async def get_items(
    skip: int = 0,
    limit: int = 10,
    sort_by: str = Query("id", regex="^(id|title|completed|priority)$"),
    sort_order: str = Query("asc", regex="^(asc|desc)$"),
    db: AsyncSession = Depends(dependencies.get_db),
):
    """
    **Получение списка задач с пагинацией и сортировкой.**

    **Args:**

        - skip (int): Количество пропускаемых записей.

        - limit (int): Максимальное количество возвращаемых записей.

        - sort_by (str): Поле для сортировки.

        - sort_order (str): Порядок сортировки ("asc" или "desc").

        - db (AsyncSession): Сессия базы данных.

    **Returns:**

        - List[schemas.ItemOut]: Список задач с указанными параметрами.

    **Логирует запрос на получение задач с указанной сортировкой.**
    """
    logger.info(f"Fetching items sorted by {sort_by} in {sort_order} order")
    return await crud.get_items(db=db, skip=skip, limit=limit, sort_by=sort_by, sort_order=sort_order)

@router.get("/items/{item_id}", response_model=schemas.ItemOut)
async def get_item(item_id: int, db: AsyncSession = Depends(dependencies.get_db)):
    """
    **Получение задачи по её идентификатору.**

    **Args:**

        - item_id (int): Идентификатор задачи.

        - db (AsyncSession): Сессия базы данных.

    **Returns:**

        - schemas.ItemOut: Найденная задача.

    **Raises:**

        - HTTPException: Если задача с указанным идентификатором не найдена.
    
    **Логирует запрос на получение задачи по ID.**
    """
    logger.info(f"Fetching item with ID {item_id}")
    item = await crud.get_item_by_id(db=db, item_id=item_id)
    if item is None:
        raise HTTPException(status_code=404, detail="Item not found")
    return item

@router.put("/items/{item_id}", response_model=schemas.ItemOut)
async def update_item(item_id: int, item: schemas.ItemUpdate, db: AsyncSession = Depends(dependencies.get_db)):
    """
    **Обновление существующей задачи по её идентификатору.**

    **Args:**

        - item_id (int): Идентификатор задачи для обновления.

        - item (schemas.ItemUpdate): Данные для обновления задачи.

        - db (AsyncSession): Сессия базы данных.

    **Returns:**

        - schemas.ItemOut: Обновлённая задача.

    **Логирует запрос на обновление задачи по ID.**
    """
    logger.info(f"Updating item with ID {item_id}")
    return await crud.update_item(db=db, item_id=item_id, item_data=item)

@router.delete("/items/{item_id}", response_model=dict)
async def delete_item(item_id: int, db: AsyncSession = Depends(dependencies.get_db)):
    """
    **Удаление задачи по её идентификатору.**

    **Args:**

        - item_id (int): Идентификатор задачи для удаления.

        - db (AsyncSession): Сессия базы данных.

    **Returns:**

        - dict: Сообщение об успешном удалении задачи.

    **Логирует запрос на удаление задачи по ID.**
    """
    logger.info(f"Deleting item with ID {item_id}")
    return await crud.delete_item(db=db, item_id=item_id)

app.include_router(router)

@app.on_event("startup")
async def on_startup():
    """
    **Событие запуска приложения.**

    **Создаёт все таблицы в базе данных при запуске приложения.**
    """
    async with dependencies.engine.begin() as conn:
        await conn.run_sync(models.Base.metadata.create_all)

@app.get("/")
async def root():
    """
    **Приветственный эндпоинт.**

    **Returns:**

        - dict: Сообщение о приветствии.
    """
    return {"message": "Добро пожаловать в API списка дел"}
