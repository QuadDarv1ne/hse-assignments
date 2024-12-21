# Задачи по практике работы с Git

## Функциональность Bash

### 1. Список всех файлов в текущей директории с указанием их типа
```bash
FILES=$(find . -type f -printf '%f (%a)
' -o -type d -printf '%f (%a)
' | sort)
```

### 2. Проверка наличия файла, переданного как аргумент
```bash
if [ -n "$1" ]; then
    FILE_EXISTS=$(find . -type f -name "$1" -print -quit)
    if [ -n "$FILE_EXISTS" ]; then
        echo "Файл $1 существует."
    else
        echo "Файл $1 не существует."
    fi
else
    echo "Пожалуйста, укажите имя файла."
    exit 1
fi
```

### 3. Использование цикла `for` для вывода информации о каждом файле
```bash
for FILE in $FILES; do
    FILE_NAME=$(basename "$FILE")
    FILE_PERMISSIONS=$(stat -c '%a' "$FILE")
    echo "Имя файла: $FILE_NAME  Права доступа: $FILE_PERMISSIONS"
done
```

## Переменная PATH

### 1. Вывод текущего значения переменной PATH и добавление новой директории
```bash
CURRENT_PATH=$PATH
echo "Текущее значение переменной PATH: $PATH"

NEW_DIRECTORY="$1"
if [ -d "$NEW_DIRECTORY" ]; then
    PATH=$PATH:$NEW_DIRECTORY
    echo "Новая директория добавлена в PATH: $PATH"
else
    echo "Ошибка: указанная директория не существует."
    exit 1
fi
```

### 2. Объяснение временных изменений переменной PATH и как сделать их постоянными
```bash
echo "Изменения переменной PATH, сделанные через терминал, временные, так как они действуют только для текущего сеанса оболочки."

echo "Для того чтобы изменения стали постоянными, добавьте следующую команду в файл .bashrc:"
echo "export PATH=$CURRENT_PATH:$NEW_DIRECTORY" >> ~/.bashrc

echo "Чтобы изменения вступили в силу, перезапустите терминал или выполните команду: source ~/.bashrc"
```

## Управляющие конструкции (условия и циклы)

### Запрос ввода числа у пользователя
```bash
read -p "Введите число: " NUMBER
```

**Проверка, является ли число положительным, отрицательным или нулём:**
```bash
if [ "$NUMBER" -ge 0 ]; then
    if [ "$NUMBER" -gt 0 ]; then
        echo "Число положительное."
    else
        echo "Число ноль."
    fi
else
    echo "Число отрицательное."
fi
```

**Подсчёт от 1 до введённого числа (если оно положительное):**
```bash
if [ "$NUMBER" -ge 0 ]; then
    echo "Подсчёт от 1 до $NUMBER:"
    count=1
    while [ "$count" -le "$NUMBER" ]; do
        echo $count
        count=$(($count + 1))
    done
else
    echo "Некорректное число."
fi
```

## Работа с функциями

**Функция для вывода строки с префиксом `"Hello,"`:**
```bash
function greet {
    echo "Hello, $1"
}
```

**Функция для сложения двух чисел:**
```bash
function sum {
    local num1=$1
    local num2=$2
    echo "$num1 + $num2 = $(($num1 + $num2))"
}
```

**Вызов функций и вывод результатов:**
```bash
greet "World"
result=$(sum 10 20)
echo "Результат сложения: $result"
```

## Управление процессами и фоновое выполнение

**Запуск трёх команд `sleep` в фоновом режиме:**
```bash
sleep 5 &
job1=$!
sleep 10 &
job2=$!
sleep 15 &
job3=$!
```

**Вывод текущих фоновых задач:**
```bash
echo "Текущие фоновые задачи:"
jobs
```

**Перевод первой задачи на передний план:**
```bash
fg %job1
echo "Первая задача на переднем плане"
sleep 5
```

**Возвращаем первую задачу в фоновый режим:**
```bash
bg %job1
```

**Переводим вторую задачу на передний план:**
```bash
fg %job2
echo "Вторая задача на переднем плане"
sleep 10
```

**Возвращаем вторую задачу в фоновый режим:**
```bash
bg %job2
```

**Переводим третью задачу на передний план:**
```bash
fg %job3
echo "Третья задача на переднем плане"
sleep 15
```

**Возвращаем третью задачу в фоновый режим и ждём завершения всех задач:**
```bash
bg %job3
wait
```

Выводим результаты
```bash
echo "Все задачи завершены."
```

## Ввод/вывод и перенаправление

Чтение данных из файла `input.txt`
```bash
cat input.txt
```

Перенаправление вывода команды `wc -l` в файл `output.txt`
```bash
wc -l < input.txt > output.txt
```

Перенаправление ошибок выполнения команды `ls` для несуществующего файла в файл `error.log`
```bash
ls non_existent_file > error.log 2>&1
```

## Использование alias и автодополнения

**Функция для создания и настройки alias и демонстрации автодополнения:**
```bash
setup_aliases_and_completions() {
    alias ll='ls -la'
    echo 'alias ll='ls -la'' >> ~/.bashrc

    complete -W '~/Documents ~/Downloads' cd
}
```

**Инициализация функции при запуске скрипта:**
```bash
setup_aliases_and_completions
```

**Проверка работы alias и автодополнения:**
```bash
echo "Текущие alias:"
alias

echo "
Демонстрация автодополнения:
"
cd ~/Doc<Tab>
```

**Дата:** 21.12.2024
