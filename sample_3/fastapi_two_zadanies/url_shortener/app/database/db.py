from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from app.models.url_model import Base

DATABASE_URL = "sqlite:///./url_shortener.db"

# Создание движка для подключения к базе данных
engine = create_engine(DATABASE_URL, connect_args={"check_same_thread": False})

# Создание фабрики сессий для работы с базой данных
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

def init_db():
    """
    Создает таблицы в базе данных, если они еще не существуют.

    Эта функция использует метаданные моделей, чтобы автоматически
    создать необходимые таблицы в базе данных на основе текущей схемы.
    """
    Base.metadata.create_all(bind=engine)

def get_db():
    """
    Получает сессию базы данных для инъекции зависимостей.

    Функция используется для предоставления сессии базы данных в
    качестве зависимости для FastAPI, что позволяет выполнять
    запросы к базе данных внутри маршрутов.

    Возвращает:
        Session: Сессия базы данных для выполнения операций.
    """
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()
