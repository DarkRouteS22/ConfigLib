# ConfigLib
![Version](https://img.shields.io/badge/version-work_in_progress-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![CMake](https://img.shields.io/badge/CMake-3.16+-064C8B) 

### Предназначение
Эта библиотека просто служит моей практикой C++

## Установка
> тут пока ничего нет, ЛОЛ

## Features
- lazy типизация для узлов
- ещё одна крутая фитча

## API

### Node

Основной класс, с которым вы и будете в основном работать.

Этот класс имеет 4 состояния:
- None
- Value
- Object
- Array

Я разделю этот блок на 4 часть, где расскажу про методы всех состояний.

#### None
По умолчанию Node имеет тип None, но при инициализации можно указать, какой тип будет у Node:
``` cpp
Node node(Config::NodeType::Value)
```

Что бы узнать, какой это тип, можно воспользоваться несколькими методами:

| Метод        | return   | описание           |
| --------------| ----------| --------------------|
| `nodeType()` | NodeType | Тип узла           |
| `isNone()`   | bool     | Является ли None   |
| `isValue()`  | bool     | Является ли Value  |
| `isObject()` | bool     | Является ли Object |
| `isArray()`  | bool     | Является ли Array  |
| --------------| ----------| --------------------|


Так же есть методы, приводящие к определённому типу Node:

| Метод        | Описание                   |
| --------------| ----------------------------|
| `asValue()`  | Приводит NodeType к Value  |
| `asObject()` | Приводит NodeType к Object |
| `asArray()`  | Приводит NodeType к Array  |
| --------------| ----------------------------|

Но они будут использоваться редко из за lazy приведения.

Так же есть метод `size()` - возвращает размер хранилища Node

| Тип    | return             |
| --------| --------------------|
| None   | 0                  |
| Value  | 1                  |
| Object | unordered_map size |
| Array  | vector size        |
| --------| --------------------|

---

#### Value
