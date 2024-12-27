from app.models.url_model import URL
from sqlalchemy.orm import Session
from sqlalchemy import desc
from app.database.db import get_db  # импорт функции для получения сессии

def get_paginated_urls(page: int, per_page: int, db: Session):
    """
    **Получение списка сокращенных URL с пагинацией.**
    """
    offset = (page - 1) * per_page
    urls = db.query(URL).order_by(desc(URL.created_at)).offset(offset).limit(per_page).all()
    total_count = db.query(URL).count()

    return {
        "total_count": total_count,
        "page": page,
        "per_page": per_page,
        "urls": [{"short_id": url.short_id, "full_url": url.full_url} for url in urls]
    }
