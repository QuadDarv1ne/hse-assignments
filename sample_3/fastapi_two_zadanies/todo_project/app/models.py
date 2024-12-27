from sqlalchemy import Column, Integer, String, Boolean, ForeignKey
from sqlalchemy.orm import relationship
from sqlalchemy.ext.declarative import declarative_base

# Создаём базовый класс для моделей SQLAlchemy
Base = declarative_base()

class Item(Base):
    """
    Модель задачи для хранения в базе данных.

    **Атрибуты:**

        - id (int): Уникальный идентификатор задачи.
        - title (str): Заголовок задачи (уникальный).
        - description (str): Описание задачи (опционально).
        - completed (bool): Статус выполнения задачи (по умолчанию False).
        - priority (int): Приоритет задачи (по умолчанию 1).

    **Методы:**

        - __repr__ (str): Представление задачи в строковом формате.
    """
    __tablename__ = "items"

    id = Column(Integer, primary_key=True, index=True)
    title = Column(String, unique=True, index=True)
    description = Column(String, nullable=True)
    completed = Column(Boolean, default=False)
    priority = Column(Integer, default=1)

    def __repr__(self):
        """
        Строковое представление задачи.

        Возвращает строку с названием задачи, её приоритетом и статусом выполнения.

        **Returns:**
            
            - str: Строка, описывающая задачу.
        """
        return f"<Item(title={self.title}, priority={self.priority}, completed={self.completed})>"
