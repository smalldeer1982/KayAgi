---
title: "Circular Dance"
layout: "post"
diff: 普及/提高-
pid: CF1095D
tag: []
---

# Circular Dance

## 题目描述

There are $ n $ kids, numbered from $ 1 $ to $ n $ , dancing in a circle around the Christmas tree. Let's enumerate them in a clockwise direction as $ p_1 $ , $ p_2 $ , ..., $ p_n $ (all these numbers are from $ 1 $ to $ n $ and are distinct, so $ p $ is a permutation). Let the next kid for a kid $ p_i $ be kid $ p_{i + 1} $ if $ i < n $ and $ p_1 $ otherwise. After the dance, each kid remembered two kids: the next kid (let's call him $ x $ ) and the next kid for $ x $ . Each kid told you which kids he/she remembered: the kid $ i $ remembered kids $ a_{i, 1} $ and $ a_{i, 2} $ . However, the order of $ a_{i, 1} $ and $ a_{i, 2} $ can differ from their order in the circle.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1095D/ba706820d7e68c6ca7fa05954588bb8c356ad841.png)Example: 5 kids in a circle, $ p=[3, 2, 4, 1, 5] $ (or any cyclic shift). The information kids remembered is: $ a_{1,1}=3 $ , $ a_{1,2}=5 $ ; $ a_{2,1}=1 $ , $ a_{2,2}=4 $ ; $ a_{3,1}=2 $ , $ a_{3,2}=4 $ ; $ a_{4,1}=1 $ , $ a_{4,2}=5 $ ; $ a_{5,1}=2 $ , $ a_{5,2}=3 $ .You have to restore the order of the kids in the circle using this information. If there are several answers, you may print any. It is guaranteed that at least one solution exists.

If you are Python programmer, consider using PyPy instead of Python when you submit your code.

## 输入格式

The first line of the input contains one integer $ n $ ( $ 3 \le n \le 2 \cdot 10^5 $ ) — the number of the kids.

The next $ n $ lines contain $ 2 $ integers each. The $ i $ -th line contains two integers $ a_{i, 1} $ and $ a_{i, 2} $ ( $ 1 \le a_{i, 1}, a_{i, 2} \le n, a_{i, 1} \ne a_{i, 2} $ ) — the kids the $ i $ -th kid remembered, given in arbitrary order.

## 输出格式

Print $ n $ integers $ p_1 $ , $ p_2 $ , ..., $ p_n $ — permutation of integers from $ 1 $ to $ n $ , which corresponds to the order of kids in the circle. If there are several answers, you may print any (for example, it doesn't matter which kid is the first in the circle). It is guaranteed that at least one solution exists.

## 样例 #1

### 输入

```
5
3 5
1 4
2 4
1 5
2 3

```

### 输出

```
3 2 4 1 5 

```

## 样例 #2

### 输入

```
3
2 3
3 1
1 2

```

### 输出

```
3 1 2 

```

