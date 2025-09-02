# Framing Pictures

## 题目描述

Life has been discovered on Venus! What is more, the life forms appear to be convex polygons. An international consortium is designing a probe to send to Venus to take pictures, but they need to estimate the bandwidth needed to send back pictures.

When the probe takes a picture of a life form and wishes to send it back to Earth, the bandwidth required is proportional to the area of the bounding box (in other words, the smallest axis-aligned rectangle that contains the life-form). The shape and size of the life forms are known, but the orientation relative to the camera is random. You must thus determine the expected (average) area of the bounding box across all orientations.

## 说明/提示

The pictures show example life forms and various camera orientations.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1578F/7bf5484b8f790ebf466874683ff7667e104e8a6b.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1578F/7e42566134414108c937e1e5ff26ff9d1b86c9db.png)

## 样例 #1

### 输入

```
4
0 0
10 0
10 10
0 10```

### 输出

```
163.661977237```

## 样例 #2

### 输入

```
5
0 0
10 0
15 8
5 20
-5 7```

### 输出

```
365.666028588```

