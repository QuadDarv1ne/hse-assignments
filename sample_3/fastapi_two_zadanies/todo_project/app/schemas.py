from pydantic import BaseModel, Field, validator
from typing import Optional

class ItemBase(BaseModel):
    """
    Базовая модель для задачи.

    **Атрибуты:**

        - title (str): Заголовок задачи.
        - description (str, optional): Описание задачи.
        - completed (bool): Статус выполнения задачи (по умолчанию False).
        - priority (int): Приоритет задачи (по умолчанию 1). Может быть 1, 2 или 3.

    **Методы:**
        
        - validate_priority (int): Валидатор для атрибута priority, проверяющий, что значение приоритета находится в пределах от 1 до 3.
    """
    title: str
    description: Optional[str] = None
    completed: bool = False
    priority: int = Field(1)

    @validator("priority")
    def validate_priority(cls, value):
        """
        Проверяет, что приоритет задачи находится в пределах от 1 до 3.

        **Args:**

            - value (int): Значение приоритета задачи.

        **Returns:**
            
            - int: Проверенное значение приоритета.

        **Raises:**
            
            - ValueError: Если значение приоритета не находится в пределах от 1 до 3.
        """
        if value not in [1, 2, 3]:
            raise ValueError("Priority must be between 1 and 3")
        return value

class ItemCreate(ItemBase):
    """
    Модель для создания новой задачи.

    Наследует все атрибуты и валидаторы от модели ItemBase.
    """
    pass

class ItemUpdate(ItemBase):
    """
    Модель для обновления существующей задачи.

    **Атрибуты:**
        
        - title (str, optional): Заголовок задачи, может быть изменён.
        - description (str, optional): Описание задачи, может быть изменено.
        - completed (bool, optional): Статус выполнения задачи, может быть изменён.
        - priority (int, optional): Приоритет задачи, может быть изменён.
    """
    title: Optional[str] = None
    description: Optional[str] = None
    completed: Optional[bool] = None
    priority: Optional[int] = None

class ItemOut(ItemBase):
    """
    Модель для вывода данных задачи.

    Наследует все атрибуты и валидаторы от модели ItemBase и добавляет атрибут id.

    **Атрибуты:**
        
        - id (int): Уникальный идентификатор задачи.
    """
    id: int

    class Config:
        """
        Конфигурация модели для работы с SQLAlchemy.

        Устанавливает использование режима from_attributes для работы с данными как с объектами модели.
        """
        from_attributes = True
