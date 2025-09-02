---
title: "Magic Box"
layout: "post"
diff: 普及/提高-
pid: CF231D
tag: []
---

# Magic Box

## 题目描述

One day Vasya was going home when he saw a box lying on the road. The box can be represented as a rectangular parallelepiped. Vasya needed no time to realize that the box is special, as all its edges are parallel to the coordinate axes, one of its vertices is at point $ (0,0,0) $ , and the opposite one is at point $ (x_{1},y_{1},z_{1}) $ . The six faces of the box contain some numbers $ a_{1},a_{2},...,a_{6} $ , exactly one number right in the center of each face.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF231D/891b16d62b99e19e4dbbcc1ffa7c6345c322e404.png)The numbers are located on the box like that:

- number $ a_{1} $ is written on the face that lies on the ZOX plane;
- $ a_{2} $ is written on the face, parallel to the plane from the previous point;
- $ a_{3} $ is written on the face that lies on the XOY plane;
- $ a_{4} $ is written on the face, parallel to the plane from the previous point;
- $ a_{5} $ is written on the face that lies on the YOZ plane;
- $ a_{6} $ is written on the face, parallel to the plane from the previous point.

At the moment Vasya is looking at the box from point $ (x,y,z) $ . Find the sum of numbers that Vasya sees. Note that all faces of the box are not transparent and Vasya can't see the numbers through the box. The picture contains transparent faces just to make it easier to perceive. You can consider that if Vasya is looking from point, lying on the plane of some face, than he can not see the number that is written on this face. It is enough to see the center of a face to see the corresponding number for Vasya. Also note that Vasya always reads correctly the $ a_{i} $ numbers that he sees, independently of their rotation, angle and other factors (that is, for example, if Vasya sees some $ a_{i}=6 $ , then he can't mistake this number for $ 9 $ and so on).

## 输入格式

The fist input line contains three space-separated integers $ x $ , $ y $ and $ z $ ( $ |x|,|y|,|z|<=10^{6} $ ) — the coordinates of Vasya's position in space. The second line contains three space-separated integers $ x_{1} $ , $ y_{1} $ , $ z_{1} $ ( $ 1<=x_{1},y_{1},z_{1}<=10^{6} $ ) — the coordinates of the box's vertex that is opposite to the vertex at point $ (0,0,0) $ . The third line contains six space-separated integers $ a_{1},a_{2},...,a_{6} $ ( $ 1<=a_{i}<=10^{6} $ ) — the numbers that are written on the box faces.

It is guaranteed that point $ (x,y,z) $ is located strictly outside the box.

## 输出格式

Print a single integer — the sum of all numbers on the box faces that Vasya sees.

## 说明/提示

The first sample corresponds to perspective, depicted on the picture. Vasya sees numbers $ a_{2} $ (on the top face that is the darkest), $ a_{6} $ (on the right face that is the lightest) and $ a_{4} $ (on the left visible face).

In the second sample Vasya can only see number $ a_{4} $ .

## 样例 #1

### 输入

```
2 2 2
1 1 1
1 2 3 4 5 6

```

### 输出

```
12

```

## 样例 #2

### 输入

```
0 0 10
3 2 3
1 2 3 4 5 6

```

### 输出

```
4

```

