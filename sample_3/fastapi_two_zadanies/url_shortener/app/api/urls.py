from fastapi import APIRouter, Depends, HTTPException
from app.schemas.url_schema import URLRequest
from app.crud.url_crud import create_short_url
from app.database.db import SessionLocal  # Сессия для работы с базой данных
from sqlalchemy.orm import Session

router = APIRouter()

# Зависимость для получения сессии базы данных
def get_db() -> Session:
    """
    Получает сессию базы данных для использования в эндпоинтах FastAPI.

    Эта функция используется для предоставления сессии базы данных как зависимость
    в маршрутах FastAPI, чтобы можно было безопасно выполнять запросы и операции с данными.

    Возвращает:
        Session: Сессия для работы с базой данных.
    """
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

@router.post("/shorten")
async def shorten_url(request: URLRequest, db: Session = Depends(get_db)):
    """
    **Эндпоинт для создания короткой ссылки**.

    Этот эндпоинт принимает полный URL и возвращает его укороченную версию.

    Параметры:
        - request (URLRequest): Объект, содержащий полный URL для сокращения.
        - db (Session): Сессия базы данных, переданная через зависимость.

    Возвращает:
        dict: Словарь с укороченной ссылкой.
    
    Исключения:
        - HTTPException: В случае ошибки при создании короткой ссылки.
    """
    try:
        # Вызываем функцию для создания короткой ссылки и передаем URL и сессию
        short_url = create_short_url(request.url, db)
        return {"shortened_url": short_url}
    except Exception as e:
        # Логирование или дополнительная обработка ошибок
        raise HTTPException(status_code=500, detail=str(e))
