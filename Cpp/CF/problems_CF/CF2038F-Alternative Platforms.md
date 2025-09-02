---
title: "Alternative Platforms"
layout: "post"
diff: 省选/NOI-
pid: CF2038F
tag: ['数学', '快速数论变换 NTT']
---

# Alternative Platforms

## 题目描述

Suppose you are working in the Ministry of Digital Development of Berland, and your task is to monitor the industry of video blogging.

There are $ n $ bloggers in Berland. Recently, due to the poor state of the main video platform in Berland, two alternative platforms were introduced. That's why bloggers started to reupload their videos to these alternative platforms. You've got the statistics that the $ i $ -th blogger uploaded $ v_i $ videos to the first alternative platform and $ r_i $ videos to the second alternative platform.

You think that a potential user will be upset if even at least one of his favorite bloggers doesn't upload anything. However, if a blogger uploads videos to both platforms, the user will watch that blogger on the platform where more videos are available. So, you've come up with the following function to estimate user experience. Suppose a user watches $ k $ bloggers $ b_1, b_2, \dots, b_k $ ; then, let user experience be  $E(b_1, \dots, b_k) = \max\left(\min_{i=1..k}{v[b_i]}, \min_{i=1..k}{r[b_i]}\right).$ 

In order to get some statistics, you want to calculate the value  $ \mathit{avg}\_k $  that is equal to an average experience among all subsets of bloggers of size  $ k $ . Also, you have to calculate  $ \mathit{avg}\_k $  for each  $ k $  from  $ 1 $  to  $ n $. 

Since answers may be too large, print them modulo  $ 998\,244\,353$.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of bloggers.

The second line contains $ n $ integers $ v_1, v_2, \dots, v_n $ ( $ 0 \le v_i \le 10^6 $ ), where $ v_i $ is the number of videos of the $ i $ -th blogger on the first alternative platform.

The third line contains $ n $ integers $ r_1, r_2, \dots, r_n $ ( $ 0 \le r_i \le 10^6 $ ), where $ r_i $ is the number of videos of the $ i $ -th blogger on the second alternative platform.

## 输出格式

Print $ n $ integers $ \mathit{avg}_1, \mathit{avg}_2, \dots, \mathit{avg}_n $ .

It can be proven that $ \mathit{avg}_k $ may be represented as an irreducible fraction $ \dfrac{x}{y} $ where $ y \not\equiv 0 \pmod{998\,244\,353} $ . So, print $ \mathit{avg}_k $ in a form $ x \cdot y^{-1} \bmod 998\,244\,353 $ .

## 说明/提示

In the first example, $ 332748119 $ is $ \frac{4}{3} $ . In the third example, $ 199648873 $ is $ \frac{12}{5} $ .

## 样例 #1

### 输入

```
3
2 1 2
1 2 1
```

### 输出

```
2 332748119 1
```

## 样例 #2

### 输入

```
4
5 5 5 5
0 0 0 0
```

### 输出

```
5 5 5 5
```

## 样例 #3

### 输入

```
5
1 9 3 7 5
2 4 6 8 5
```

### 输出

```
6 4 3 199648873 2
```

