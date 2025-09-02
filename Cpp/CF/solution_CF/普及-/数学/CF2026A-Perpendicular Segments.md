# Perpendicular Segments

## 题目描述

You are given a coordinate plane and three integers $ X $ , $ Y $ , and $ K $ . Find two line segments $ AB $ and $ CD $ such that

1. the coordinates of points $ A $ , $ B $ , $ C $ , and $ D $ are integers;
2. $ 0 \le A_x, B_x, C_x, D_x \le X $ and $ 0 \le A_y, B_y, C_y, D_y \le Y $ ;
3. the length of segment $ AB $ is at least $ K $ ;
4. the length of segment $ CD $ is at least $ K $ ;
5. segments $ AB $ and $ CD $ are perpendicular: if you draw lines that contain $ AB $ and $ CD $ , they will cross at a right angle.

Note that it's not necessary for segments to intersect. Segments are perpendicular as long as the lines they induce are perpendicular.

## 说明/提示

The answer for the first test case is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2026A/ec912df39bb0649b8cac618bfc67861cbe33f3a9.png)  The answer for the second test case:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2026A/16297a765040b390fcf117cbdd6958cb27cfd2f6.png)  The answer for the third test case:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2026A/2fa935fca6647221cd973d5ea3b266eb1839dab4.png)  The answer for the fourth test case:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2026A/41df202ce65e0906ba528f2a40ffbcdc5a825158.png)

## 样例 #1

### 输入

```
4
1 1 1
3 4 1
4 3 3
3 4 4```

### 输出

```
0 0 1 0
0 0 0 1
2 4 2 2
0 1 1 1
0 0 1 3
1 2 4 1
0 1 3 4
0 3 3 0```

