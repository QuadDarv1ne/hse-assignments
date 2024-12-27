from pydantic import BaseModel

class URLRequest(BaseModel):
    """
    **Схема для валидации входного запроса на создание короткой ссылки.**
    """
    url: str
