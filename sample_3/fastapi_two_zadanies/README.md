
# Проекты FastAPI: TODO API и URL Shortener

**Этот репозиторий содержит два проекта на FastAPI:** `TODO API` и `URL Shortener API`

Оба проекта используют `SQLite` для хранения данных и контейнеризованы с помощью `Docker` для удобства развертывания.

## 🚀 Обзор проектов

### TODO API с FastAPI и SQLite

Простое приложение для списка задач, где можно создавать, обновлять, удалять и получать задачи.

Этот API позволяет управлять коллекцией задач с помощью основных операций CRUD.

### URL Shortener API с FastAPI и SQLite

Этот проект предоставляет сервис сокращения URL, где пользователи могут сократить URL и получать статистику по ним с поддержкой пагинации.

API также обрабатывает перенаправления с сокращённого URL на оригинальный.

## 📁 Структура проекта

```
fastapi_two_zadanies/
│
├── todo_project/          # Проект для TODO API
│   ├── app/               # Основной код приложения
│   ├── alembic/           # Миграции базы данных
│   ├── test.db            # SQLite база данных
│   ├── .gitignore         # Файлы и папки, которые игнорируются Git
│   ├── Dockerfile         # Конфигурация для Docker контейнера
│   └── requirements.txt   # Список зависимостей
│
├── url_shortener/         # Проект для сокращения URL
│   ├── app/               # Основной код приложения
│   ├── database.db        # SQLite база данных для сокращенных URL
│   ├── Dockerfile         # Конфигурация для Docker контейнера
│   ├── .gitignore         # Файлы и папки, которые игнорируются Git
│   └── README.md          # Документация проекта
│
├── .gitignore             # Главный .gitignore для всего репозитория
└── README.md              # Главная документация для всего репозитория
```

## ⚙️ Установка

Следуйте этим шагам, чтобы начать работу с обоими проектами.

- **Клонируйте репозиторий с помощью команды:** `git clone https://github.com/QuadDarv1ne/fastapi_two_zadanies.git`
- **Перейдите в папку проекта:** `cd fastapi_two_zadanies`
- **Создайте виртуальное окружение** (необязательно, но рекомендуется) с помощью команды `python -m venv venv`
- **Активируйте виртуальное окружение** (используйте `source venv/bin/activate` для `macOS/Linux` или `venv\Scriptsctivate` для `Windows`)
- **Установите зависимости с помощью команды:** `pip install -r requirements.txt`
- **Запустите приложения с помощью Uvicorn командой:** `uvicorn app.main:app --reload`

## 🔧 API Эндпоинты

### **TODO API Эндпоинты**
1. **POST** `/items` — Создание задачи
   
   **Пример запроса:**
   ```json
   {
    "title": "Новая задача",
    "description": "Это новая задача",
    "completed": false
   }
   ```
1. **GET** `/items` — Получение списка всех задач
1. **GET** `/items/{item_id}` — Получение задачи по ID
1. **PUT** `/items/{item_id}` — Обновление задачи по ID
   
   **Пример запроса:**
   ```json
   {
    "title": "Обновленная задача",
    "description": "Эта задача была обновлена",
    "completed": true
   }
   ```
1. **DELETE** `/items/{item_id}` — Удаление задачи по ID

### **URL Shortener API Эндпоинты**
1. **POST** `/shorten` — Создание сокращённого URL
   
   **Пример запроса:**
   ```json
   {
    "url": "https://www.example.com"
   }
   ```
1. **GET** `/stats` — Получение списка всех сокращённых URL с пагинацией
   
   **Пример запроса:**
   ```json
   {
    "page": 1,
    "per_page": 10
   }
   ```
1. **GET** `/{short_id}` — Перенаправление на оригинальный URL

## 📜 Лицензия

Этот проект распространяется под лицензией `MIT License`

 - см. файл [LICENSE](LICENSE) для подробной информации.

## 📝 Автор

**Максим Игоревич Дуплей**

- [Сайт школы программирования Maestro7IT](https://school-maestro7it.tilda.ws/)
- Telegram: [@quadd4rv1n7](https://t.me/@quadd4rv1n7)
- Email: [maksimqwe42@mail.ru](maksimqwe42@mail.ru)
- Дата: `27 декабря 2024`
