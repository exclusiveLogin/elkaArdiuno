elkaArdiuno
===========
Это проект для  управления сведодинамической елкой.
Проект реализован с использованием Аппаратно-программного комплекса  Arduino Mega 2650
В контроллере задействованы следующие каналы:
вертикальные ветки спадающие с кроны(Radial):2,3,4,5,6 pin
Хоризонтальные кольца (Horizontal): Используются пины 22-36
при этом предполагается что кольцо это 3 не зависимых канала RGB.
Красные кольца это 22-26 каналы
Зеленые кольца это 27-31 каналы
Синии кольца это 32-36 каналы
К контроллеру предполагается подключение клавиш управления
1кл- Перевод системы в режим StandBy
Выполнение кода висит в основной ф-ции main LED 13 мигает раз в 500мс
2кл это запуск режима приветствия или старт программы "Елочка гори"
Этот режим предполагает запуск программы светодинамических эффектов под музыку.
3кл переводит контроллер в режим цикла светодинамических паттернов 1-9