from sqlalchemy.ext.asyncio import AsyncSession, create_async_engine
from sqlalchemy.orm import sessionmaker
from fastapi import Depends
from .models import Base

# URL базы данных
DATABASE_URL = "sqlite+aiosqlite:///./todo_project.db"

# Создание асинхронного движка SQLAlchemy для работы с базой данных
engine = create_async_engine(DATABASE_URL, echo=True)

# Создание фабрики сессий для работы с базой данных
AsyncSessionLocal = sessionmaker(engine, expire_on_commit=False, class_=AsyncSession)

async def get_db():
    """
    Зависимость для получения асинхронной сессии базы данных.

    Эта функция используется для получения сессии базы данных в каждом запросе. 
    Она создает новую сессию и автоматически закрывает её по завершении работы.

    **Returns:**

        - AsyncSession: Асинхронная сессия базы данных для выполнения запросов.
    """
    async with AsyncSessionLocal() as session:
        yield session
