from fastapi import FastAPI
from app.api import urls, stats

app = FastAPI()

@app.on_event("startup")
async def startup_db():
    """
    **Инициализация базы данных при старте приложения.**
    
    **Создание таблиц, если они еще не существуют.**
    """
    from app.database.db import init_db
    init_db()

# Регистрируем маршруты (эндпоинты)
app.include_router(urls.router)
app.include_router(stats.router)

@app.get("/")
async def root():
    """
    **Главная страница с приветственным сообщением.**
    """
    return {"message": "Welcome to the URL Shortener API"}
