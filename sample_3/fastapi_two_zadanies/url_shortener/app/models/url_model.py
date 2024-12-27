from sqlalchemy import Column, String, DateTime
from sqlalchemy.ext.declarative import declarative_base
from datetime import datetime

Base = declarative_base()

class URL(Base):
    """
    Модель для хранения данных о сокращенных URL.
    """
    __tablename__ = "urls"

    short_id = Column(String, primary_key=True, index=True)
    full_url = Column(String, unique=True, index=True)
    created_at = Column(DateTime, default=datetime.utcnow)
