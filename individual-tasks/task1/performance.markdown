# Анализ произвадительности

Задача решить систему нелинейный уравнений.
Колличество не известных переменных `3000`.

1. Однопоточный режим

| №  | Время в секундах | 
|:--:|:----------------:|
| 1  |  3.39            |
| 2  |  3.43            |
| 3  |  3.47            |
| 4  |  3.33            |
| 5  |  3.35            |

2. Многопоточный режим
    1. static

| №  | 2      | 3      | 4      |  
|:--:|:------:|:------:|:------:|
| 1  |  1.47  | 1.23   | 1.26   |
| 2  |  1.28  | 1.24   | 1.33   |
| 3  |  1.29  | 1.43   | 1.28   |
| 4  |  1.30  | 1.61   | 1.34   |
| 5  |  1.35  | 1.30   | 1.28   |

    2. dynamic