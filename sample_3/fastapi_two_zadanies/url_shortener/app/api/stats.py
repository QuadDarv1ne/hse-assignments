from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session
from app.crud.pagination import get_paginated_urls
from app.schemas.pagination import PaginatedURLs
from app.database.db import get_db

router = APIRouter()

@router.get("/stats", response_model=PaginatedURLs)
async def get_all_urls(page: int = 1, per_page: int = 10, db: Session = Depends(get_db)):
    """
    **Эндпоинт для получения статистики о сокращенных ссылках с пагинацией.**

    Этот эндпоинт позволяет получить список сокращённых и полных URL с пагинацией.
    Он поддерживает параметры `page` и `per_page` для управления количеством ссылок
    на каждой странице. Возвращает объект с мета-информацией о пагинации и списком URL.

    **Параметры:**
        - page (int): Номер страницы, на которой нужно получить данные (по умолчанию 1).
        - per_page (int): Количество записей на странице (по умолчанию 10).

    **Ответ:**
        - Возвращает объект с пагинированными данными, включая список коротких и полных URL.

    **Пример ответа:**
        {
            "total": 100,
            "page": 1,
            "per_page": 10,
            "urls": [
                {
                    "short_url": "http://short.ly/abc123",
                    "full_url": "http://example.com"
                },
                ...
            ]
        }
    """
    # Вызов функции для получения пагинированных данных
    return get_paginated_urls(page=page, per_page=per_page, db=db)
