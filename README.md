# Тестовые задания для СТЦ
## №1 (2.3) По четырем числам линейного конгруэнтого генератора вычислить следующее
### Ответ: lcg_crack
#### Стандартная сборка cmake, проверял для Ubuntu 18.04 (g++/gcc)
##### После сборки запускать: lcg_crack N1 N2 N3 N4, где Ni-числа последовательности
Упрощение изначальной системы уравнений:
$$x_2= (x_1 \cdot a + c) mod(m) \text{ (1)}$$
$$x_3= (x_2 \cdot a + c) mod(m) \text{ (2)}$$
$$x_4= (x_3 \cdot a + c) mod(m) \text{ (3)}$$

Приводятся к (4), (5) путем вычитания (1) из (3) и (2):
$$x_3 - x_2 = ((x_2 - x_1) \cdot a) mod(m) \text{ (4)}$$
$$x_4 - x_2 = ((x_3 - x_1) \cdot a) mod(m) \text{ (5)}$$

Далее (4) умножается на (X3 - X1), а (5) - на (X2 - X1):
$$(x_3 - x_2)\cdot(x_3 - x_1) = ((x_2 - x_1)\cdot(x_3 - x_1) \cdot a) mod(m) \text{ (5)}$$
$$(x_4 - x_2)\cdot(x_2 - x_1) = ((x_3 - x_1)\cdot(x_2 - x_1) \cdot a) mod(m) \text{ (6)}$$

(5) вычитается из (6):
$$(x_4 - x_2)\cdot(x_2 - x_1) - (x_3 - x_2)\cdot(x_3 - x_1) = 0 mod(m)$$

Таким образом, m - среди делителей данного числа: 
$$(x_4 - x_2)\cdot(x_2 - x_1) - (x_3 - x_2) \cdot (x_3 - x_1)$$

Далее находятся все делители числа, отсекаются лишние, т.к. делители:
  - не могут быть меньше наибольшего числа в последовательности
  - не могут быть больше максимального m
  
После чего находится a и c методом подбора, при том, что:
  0 < a < m;
  0 <= c < m;
  
(из условий генератора)


Из всего перечня полученных решений помечается наиболее вероятным то,
в котором c и m взаимно простые (одно из условий, при котором
генератор повторяется с периодичностью m, т.е. изначально скорее
всего этот набор параметров и был выбран). Прочие решения также
являются валидными, однако если построить последовательность генератора
для каждого набора параметров, станет видно, что многие очень быстро начинают
повторяться.

## №2 (2.9) Задача на разностно-дальномерный метод
### Ответ: rdm_locator
#### Запускать rdm_solve(x1 y1 x2 y2 x3 y3 dt12 dt13), где {x,y} - координаты постов, {dt} - разность прихода сигнала
В данной задаче я изначально не понял, в каком виде требуется решение
(предполагал, что требуется скрипт matlab-а, или вообще, решение в C++
коде). Сделал следующим образом: небольшой скрипт для matlab-а, к нему
приложил результат его выполнения (полученные графики). Matlab compilator не 
доступен к установке, поэтому не смог сделать .exe файлы используя скрипты.
Задача на поиск источника радио излучения разностно-дальномерным
методом сводится к решению системы из двух уравнений:
$$R_{12} = \sqrt{(x_s - x_1)^2 + (y_s - y_1)^2} - \sqrt{(x_s - x_2)^2 + (y_s - y_1)^2} = c \cdot dt_{12}$$
$$R_{13} = \sqrt{(x_s - x_1)^2 + (y_s - y_1)^2} - \sqrt{(x_s - x_3)^2 + (y_s - y_3)^2} = c \cdot dt_{13}$$
, где: 
  - $R_{12}$ - расстояние между 1 и 2 постами;
  - $R_{13}$ - расстояние между 1 и 3 постами;
  - $x_s$, $y_s$ - координаты источника;
  - $x_1$, $x_2$, $x_3$, $y_1$, $y_2$, $y_3$ - координаты постов;
  - $c$ - скорость света;
  - $dt_{12}$, $dt_{13}$ - задержка во времени приема сигнала между 1 и 2, 1 и 3 постами соответственно, при этом
$dt_{12} = T_1 - T_2$; $dt_{13} = T_1 - T_3$.

Полная формула символьного решения для $x_s$, $y_s$ слишком длинная для разумного использования в коде, поэтому решение получено в matlab-е исключительно.
Ответ для приведенных данных: ИРИ находится по координатам {1993, 4007} (с округлением). Графическое решение - "stc_entry_tasks/rdm_locator/graph_solution.jpg"

## №3 (2.4) Формирование звукового стереосигнала, по методу Interaural time difference
### Ответ: stereo_sound
#### Запускать ITD_stereo_sound_gen(speed radius), где speed-скорость источника, radius-радиус окружности движения источника
Данная задача решается следующим образом - находится текущая разность между источником и каждым ухом, вычисляется 
время, затрачиваемое звуком на преодоление данных расстояний, после чего в левый и правый каналы пишутся звуки с соответствующей
разностью во времени:
$$left_A = A \cdot sin{(2 \cdot \pi \cdot F \cdot (t+dt_L) + \phi)}$$
$$right_A = A \cdot sin{(2 \cdot \pi \cdot F \cdot (t+dt_R) + \phi)}$$
, где $A$ - амплитуда (по умолчанию установил равной 1), $F$ - частота сигнала, установил равной 200
$$dt_L = S_L \ V_{sound}$$
$$dt_R = S_R \ V_{sound}$$
Где $S_L$ и $S_R$ - расстояния между источником и каждым ухом соответственно:
$$S_L = \sqrt{(x_{source}^2-x_L)+(y_{source}^2-y_L)}$$
$$S_R = \sqrt{(x_{source}^2-x_R)+(y_{source}^2-y_R)}$$
Так как задано равномерное движение по окружности, то:
$$x_{source} = R \cdot cos{(w \cdot t)};$$
$$y_{source} = R \cdot sin{(w \cdot t)};$$
Результат записывается в файл "stereo sound.wav" в каталоге скрипта.
