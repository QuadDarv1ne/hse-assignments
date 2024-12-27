import os

# Путь к базе данных
DATABASE_URL = os.getenv("DATABASE_URL", "sqlite:///./url_shortener.db")
