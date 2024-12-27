from pydantic import BaseModel
from typing import List

class PaginatedURLs(BaseModel):
    """
    **Схема для пагинированного списка URL.**
    """
    total_count: int
    page: int
    per_page: int
    urls: List[dict]
