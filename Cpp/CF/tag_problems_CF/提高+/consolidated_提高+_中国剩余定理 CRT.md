---
title: "ConstructOR"
layout: "post"
diff: 提高+/省选-
pid: CF1748D
tag: ['贪心', '中国剩余定理 CRT', '位运算', '构造']
---

# ConstructOR

## 题目描述

You are given three integers $ a $ , $ b $ , and $ d $ . Your task is to find any integer $ x $ which satisfies all of the following conditions, or determine that no such integers exist:

- $ 0 \le x \lt 2^{60} $ ;
- $ a|x $ is divisible by $ d $ ;
- $ b|x $ is divisible by $ d $ .

Here, $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 输入格式

Each test contains multiple test cases. The first line of input contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of one line, containing three integers $ a $ , $ b $ , and $ d $ ( $ 1 \le a,b,d \lt 2^{30} $ ).

## 输出格式

For each test case print one integer. If there exists an integer $ x $ which satisfies all of the conditions from the statement, print $ x $ . Otherwise, print $ -1 $ .

If there are multiple solutions, you may print any of them.

## 说明/提示

In the first test case, $ x=18 $ is one of the possible solutions, since $ 39|18=55 $ and $ 12|18=30 $ , both of which are multiples of $ d=5 $ .

In the second test case, $ x=14 $ is one of the possible solutions, since $ 8|14=6|14=14 $ , which is a multiple of $ d=14 $ .

In the third and fourth test cases, we can show that there are no solutions.

## 样例 #1

### 输入

```
8
12 39 5
6 8 14
100 200 200
3 4 6
2 2 2
18 27 3
420 666 69
987654321 123456789 999999999
```

### 输出

```
18
14
-1
-1
0
11
25599
184470016815529983
```



---

---
title: "Dyn-scripted Robot (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1993F1
tag: ['扩展欧几里德算法', '中国剩余定理 CRT']
---

# Dyn-scripted Robot (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version $ k \le n $ . You can make hacks only if both versions of the problem are solved.

Given a $ w \times h $ rectangle on the $ Oxy $ plane, with points $ (0, 0) $ at the bottom-left and $ (w, h) $ at the top-right of the rectangle.

You also have a robot initially at point $ (0, 0) $ and a script $ s $ of $ n $ characters. Each character is either L, R, U, or D, which tells the robot to move left, right, up, or down respectively.

The robot can only move inside the rectangle; otherwise, it will change the script $ s $ as follows:

- If it tries to move outside a vertical border, it changes all L characters to R's (and vice versa, all R's to L's).
- If it tries to move outside a horizontal border, it changes all U characters to D's (and vice versa, all D's to U's).

Then, it will execute the changed script starting from the character which it couldn't execute.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1993F1/ff49f6aa11a19418f77260f4c00c02fa1a42de65.png) An example of the robot's movement process, $ s = \texttt{"ULULURD"} $ The script $ s $ will be executed for $ k $ times continuously. All changes to the string $ s $ will be retained even when it is repeated. During this process, how many times will the robot move to the point $ (0, 0) $ in total? Note that the initial position does NOT count.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains four integers $ n $ , $ k $ , $ w $ , and $ h $ ( $ 1 \le n, w, h \le 10^6 $ ; $ 1 \le k \le n $ ).

The second line contains a single string $ s $ of size $ n $ ( $ s_i \in \{\texttt{L}, \texttt{R}, \texttt{U}, \texttt{D}\} $ ) — the script to be executed.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, print a single integer — the number of times the robot reaches $ (0, 0) $ when executing script $ s $ for $ k $ times continuously.

## 说明/提示

In the first test case, the robot only moves up and right. In the end, it occupies the position $ (2, 2) $ but never visits $ (0, 0) $ . So the answer is $ 0 $ .

In the second test case, each time executing the script the robot visits the origin twice. And since $ k=2 $ , it visits the origin $ 2 \cdot 2 = 4 $ times overall.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1993F1/4c04dc66914a3e1ee672ced7111b24a5891eec80.png)In the third test case, the visualization is shown as below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1993F1/354b17fd45a6d2914b35f5325993193690563e94.png)

## 样例 #1

### 输入

```
5
2 2 2 2
UR
4 2 1 1
LLDD
6 3 3 1
RLRRRL
5 5 3 3
RUURD
7 5 3 4
RRDLUUU
```

### 输出

```
0
4
3
0
1
```



---

---
title: "Bermuda Triangle"
layout: "post"
diff: 提高+/省选-
pid: CF2097C
tag: ['数学', '扩展欧几里德算法', '中国剩余定理 CRT']
---

# Bermuda Triangle

## 题目描述

百慕大三角——大西洋中一片神秘区域，据传言船只和飞机都会在此凭空消失。有人归咎于磁力异常，有人则认为是通往异世界的传送门，但真相仍笼罩在谜团之中。

在一个晴朗的日子里，814 次常规客运航班正从迈阿密飞往拿骚。在飞机进入一片诡异闪烁的迷雾区域前，一切都看似正常。无线电通讯中断，仪表疯狂旋转，窗外闪烁着非自然的光芒。

为简化问题，我们假设百慕大三角和飞机都位于平面上，且三角形的顶点坐标为 $(0, 0)$、$(0, n)$ 和 $(n, 0)$。飞机初始位于严格处于百慕大三角内部的点 $(x, y)$，并以速度向量 $(v_x, v_y)$ 移动。由于所有仪器都已失灵，机组人员无法控制飞机。

当飞机到达三角形任意一个顶点时，即可成功逃离。但如果飞机在任意时刻（可能是非整数时间）碰到三角形的边界（不包括顶点），其速度向量会立即根据该边进行镜面反射$^\dagger$，随后飞机将继续沿新方向移动。

请判断飞机是否能逃离百慕大三角（即到达某个顶点）。如果可能，还需计算在逃离前会碰到边界的次数（每次触碰边界都计入次数，即使是在同一点；经过顶点不计入次数）。

$^\dagger$ 反射遵循物理定律：入射角等于反射角。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的唯一一行包含五个整数 $n$、$x$、$y$、$v_x$ 和 $v_y$（$3 \le n \le 10^9$，$1 \le x, y$，$x+y < n$，$1 \le v_x, v_y \le 10^9$）——分别描述三角形的顶点坐标、飞机的初始位置和初始速度向量。

## 输出格式

对于每个测试用例，输出一个整数——飞机逃离前触碰边界的次数。如果飞机永远无法逃离，则输出 $-1$。

## 说明/提示

第一个测试用例的示意图如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2097C/5dcc41152cc7283979e514f25388f82aa27ff3b9.png)

第二个测试用例中，除速度外初始数据与第一个测试用例相同，且飞机初始运动方向相同，因此答案相同。

第三个测试用例的答案为 $-1$，因为飞机将始终沿着绿色标记的线段移动。示意图如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2097C/dea0fd33e36a4eb6795ed5c962c688b9827de243.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6
6 2 2 5 2
6 2 2 20 8
4 1 2 1 1
4 1 1 1 2
4 1 1 2 1
6 2 3 2 3
```

### 输出

```
2
2
-1
-1
-1
5
```



---

