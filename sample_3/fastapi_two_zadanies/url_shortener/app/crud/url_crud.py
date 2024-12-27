from app.models.url_model import URL
from app.database.db import SessionLocal
import hashlib
from fastapi import HTTPException

def create_short_url(full_url: str, db: SessionLocal):
    """
    **Создание сокращенной ссылки для переданного полного URL.**
    
    **Если сокращенная ссылка уже существует, возвращается существующая.**
    """

    # Проверка на валидность URL
    if not full_url.startswith("http://") and not full_url.startswith("https://"):
        raise HTTPException(status_code=400, detail="Invalid URL. URL must start with http:// or https://")

    # Генерация короткого ID
    short_id = hashlib.md5(full_url.encode()).hexdigest()[:6]

    # Проверка на существование сокращенной ссылки в базе данных
    db_url = db.query(URL).filter(URL.short_id == short_id).first()
    if db_url:
        return {"short_url": f"http://localhost:8000/{short_id}"}

    # Сохранение новой записи в базе данных
    try:
        new_url = URL(short_id=short_id, full_url=full_url)
        db.add(new_url)
        db.commit()
        db.refresh(new_url)
    except Exception as e:
        db.rollback()  # Откат транзакции в случае ошибки
        raise HTTPException(status_code=500, detail="Error saving the URL to the database.")

    # Возвращаем короткую ссылку
    return {"short_url": f"http://localhost:8000/{short_id}"}
