# BerPaint

## 题目描述

Anfisa the monkey got disappointed in word processors as they aren't good enough at reflecting all the range of her emotions, that's why she decided to switch to graphics editors. Having opened the BerPaint, she saw a white rectangle $ W×H $ in size which can be painted on. First Anfisa learnt to navigate the drawing tool which is used to paint segments and quickly painted on that rectangle a certain number of black-colored segments. The resulting picture didn't seem bright enough to Anfisa, that's why she turned her attention to the "fill" tool which is used to find a point on the rectangle to paint and choose a color, after which all the area which is the same color as the point it contains, is completely painted the chosen color. Having applied the fill several times, Anfisa expressed her emotions completely and stopped painting. Your task is by the information on the painted segments and applied fills to find out for every color the total area of the areas painted this color after all the fills.

## 说明/提示

Initially the black segments painted by Anfisa can also be painted a color if any of the chosen points lays on the segment. The segments have areas equal to 0. That is why if in the final picture only parts of segments is painted some color, then the area, painted the color is equal to 0.

## 样例 #1

### 输入

```
4 5
6
1 1 1 3
1 3 3 3
3 3 3 1
3 1 1 1
1 3 3 1
1 1 3 3
2
2 1 red
2 2 blue
```

### 输出

```
blue 0.00000000
white 20.00000000
```

## 样例 #2

### 输入

```
5 5
5
1 1 2 2
2 2 4 2
4 2 4 4
4 4 2 4
2 4 2 2
2
3 3 black
3 3 green
```

### 输出

```
green 4.00000000
white 21.00000000
```

## 样例 #3

### 输入

```
7 4
9
1 2 2 3
2 3 3 2
3 2 2 1
2 1 1 2
3 2 4 2
4 2 5 3
5 3 6 2
6 2 5 1
5 1 4 2
2
2 2 black
2 2 red
```

### 输出

```
red 2.00000000
white 26.00000000
```

