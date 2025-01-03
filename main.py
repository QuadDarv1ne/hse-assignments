import random
import time
from colorama import init, Fore, Style
import sys

init(autoreset=True)

# Функция для случайного выбора украшений
def get_random_decoration():
    return random.choice([
        Fore.GREEN + "*",  # Зеленая звезда
        Fore.RED + "o",    # Красный шарик
        Fore.YELLOW + "x", # Желтая гирлянда
        Fore.CYAN + "+",   # Голубой огонёк
        Fore.MAGENTA + "&", # Розовый шарик
    ])

# Функция для создания уровня ёлки с украшениями
def create_tree_level(level, height):
    return "".join(
        get_random_decoration() if char == "*" else char
        for char in " " * (height - level) + "*" * (2 * level - 1)
    )

# Функция для создания ствола ёлки
def draw_tree_trunk(height):
    return " " * (height - 1) + Fore.YELLOW + Style.BRIGHT + "|||"

# Функция для генерации снежинок
def generate_snowflakes(snowflakes_count, height):
    snow = ""
    for _ in range(snowflakes_count):
        snow += random.choice([Fore.WHITE + "•", " "])
    return snow

# Функция для анимации ёлки
def draw_tree(height=10, snowflakes_count=30, flash_effect=True):
    """
    Анимация новогодней ёлки с мигающими огоньками, снегопадом и текстурированным стволом.
    
    :param height: Высота ёлки (по умолчанию 10)
    :param snowflakes_count: Количество снежинок (по умолчанию 30)
    :param flash_effect: Включение мигающих огоньков на ёлке (по умолчанию True)
    """
    try:
        while True:
            print("\033c", end="")  # Очистка консоли
            # Рисуем верхушку ёлки (Звезда)
            print(" " * (height - 1) + Fore.YELLOW + "★")  # Верхушка ёлки

            # Рисуем ёлку
            for i in range(1, height + 1):
                level = create_tree_level(i, height)
                print(level)

            # Рисуем ствол ёлки
            print(draw_tree_trunk(height))

            # Генерируем снегопад
            snow = generate_snowflakes(snowflakes_count, height)
            print(snow)

            # Задержка между кадрами
            time.sleep(0.5)
            if flash_effect:
                # Мигающие огоньки на ёлке
                time.sleep(0.2)

    except KeyboardInterrupt:
        # Завершаем анимацию с поздравлением
        print(Fore.CYAN + "\nАнимация остановлена. С Новым годом и счастья в новом году! 🎉")
        sys.exit(0)


if __name__ == "__main__":
    draw_tree()
