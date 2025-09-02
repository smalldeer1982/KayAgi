# New Year Snowflake

## 题目描述

As Gerald ..., in other words, on a New Year Eve Constantine prepared an unusual present for the Beautiful Lady. The present is the magic New Year snowflake that can make any dream come true.

The New Year snowflake consists of tiny ice crystals, which can be approximately regarded as points on the plane. The beauty of the New Year snowflake is that it has a center of symmetry. This is a point such that for each crystal of the snowflake exists another crystal, symmetrical to it relative to that point. One of the crystals can be placed directly in the center of symmetry.

While Constantine was choosing a snowflake among millions of other snowflakes, no less symmetrical and no less magical, then endured a difficult path through the drifts to the house of his mistress, while he was waiting with bated breath for a few long moments before the Beautiful Lady opens the door, some of the snowflake crystals melted and naturally disappeared. Constantine is sure that there were no more than $ k $ of such crystals, because he handled the snowflake very carefully. Now he is ready to demonstrate to the Beautiful Lady all the power of nanotechnology and restore the symmetry of snowflakes.

You are given the coordinates of the surviving snowflake crystals, given in nanometers. Your task is to identify all possible positions of the original center of symmetry.

## 样例 #1

### 输入

```
4 0
0 0
0 1
1 0
1 1
```

### 输出

```
1
0.5 0.5
```

## 样例 #2

### 输入

```
4 2
0 0
0 1
1 0
1 1
```

### 输出

```
5
0.0 0.5
0.5 0.0
0.5 0.5
0.5 1.0
1.0 0.5
```

## 样例 #3

### 输入

```
4 4
0 0
0 1
1 0
1 1
```

### 输出

```
-1
```

