# 题目信息

# Dasha and Password

## 题目描述

After overcoming the stairs Dasha came to classes. She needed to write a password to begin her classes. The password is a string of length $ n $ which satisfies the following requirements:

- There is at least one digit in the string,
- There is at least one lowercase (small) letter of the Latin alphabet in the string,
- There is at least one of three listed symbols in the string: '\#', '\*', '&'.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF761C/cb0ada85db7c7b0388e7b419452d8653e44781e1.png)Considering that these are programming classes it is not easy to write the password.

For each character of the password we have a fixed string of length $ m $ , on each of these $ n $ strings there is a pointer on some character. The $ i $ -th character displayed on the screen is the pointed character in the $ i $ -th string. Initially, all pointers are on characters with indexes $ 1 $ in the corresponding strings (all positions are numbered starting from one).

During one operation Dasha can move a pointer in one string one character to the left or to the right. Strings are cyclic, it means that when we move the pointer which is on the character with index $ 1 $ to the left, it moves to the character with the index $ m $ , and when we move it to the right from the position $ m $ it moves to the position $ 1 $ .

You need to determine the minimum number of operations necessary to make the string displayed on the screen a valid password.

## 说明/提示

In the first test it is necessary to move the pointer of the third string to one left to get the optimal answer.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF761C/89086e09018b91f648aacd8cd5238770a033e69b.png)In the second test one of possible algorithms will be:

- to move the pointer of the second symbol once to the right.
- to move the pointer of the third symbol twice to the right.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF761C/3400aa9e98cacdc13b42e316e367bed427854028.png)

## 样例 #1

### 输入

```
3 4
1**2
a3*0
c4**
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 5
#*&#*
*a1c&
&q2w*
#a3c#
*&#*&```

### 输出

```
3
```

# AI分析结果



# Dasha and Password

## 题目描述

Dasha 需要设置一个密码，该密码满足以下条件：
- 至少包含一个数字
- 至少包含一个小写字母
- 至少包含一个特殊符号（#、*、&）

密码的每个字符来自不同的循环字符串。每个字符串初始指针指向第一个字符，每次操作可以左右移动指针（循环结构）。求满足条件的最小操作次数。

## 算法分类
枚举

---

## 题解分析

### 关键思路对比
1. **三重循环枚举**：大部分题解通过三层嵌套循环分别枚举提供数字、字母、符号的字符串，计算每个字符串对应类型字符的最小移动步数。
2. **环形步数计算**：所有题解均采用 `min(正向移动, 反向移动)` 的方式处理循环字符串的移动次数。
3. **预处理优化**：部分题解（如 __asdf__、rainbow_cat）预处理每个字符串成为三种类型所需的最小步数，将时间复杂度优化至 O(n³)。

### 最优解法
预处理每个字符串成为数字/字母/符号的最小步数，枚举三个不同字符串分别提供三种类型的最小步数之和。时间复杂度 O(n³)，空间复杂度 O(n)。

---

## 精选题解

### 题解1：__asdf__（⭐⭐⭐⭐⭐）
**核心思路**：预处理每个字符串转化为三种类型的代价，通过三重循环枚举不同组合。
```cpp
for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        for(int k=1;k<=n;k++){
            if(i==j||j==k||i==k) continue;
            ans = min(ans, f[0][i] + f[1][j] + f[2][k]);
        }
    }
}
```
**亮点**：预处理避免重复计算，代码简洁高效。

### 题解2：rainbow_cat（⭐⭐⭐⭐）
**核心技巧**：独立计算每个字符串的三种类型代价，使用三次 min 操作优化预处理。
```cpp
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        if(isdigit(c[i][j])) nd[i] = min(nd[i], min(j-1,m-j+1));
        // 类似处理字母、符号
    }
}
```
**亮点**：代码结构清晰，变量命名直观。

### 题解3：菲斯斯夫斯基（⭐⭐⭐）
**实现方式**：三层嵌套循环直接计算，未预处理。
```cpp
for(int i=1;i<=n;i++){ // 枚举数字
    for(int j=1;j<=n;j++){ // 枚举字母
        for(int k=1;k<=n;k++){ // 枚举符号
            // 计算三个字符串的最小步数
        }
    }
}
```
**不足**：重复计算字符类型判断，时间复杂度 O(n³m)。

---

## 总结技巧
1. **环形移动公式**：`min(pos-1, m-pos+1)` 快速计算循环移动步数。
2. **预处理思维**：将字符串特征提取为数值，减少嵌套循环中的重复计算。
3. **独立枚举维度**：将问题分解为三个独立的条件，分别处理后再组合求解。

---

## 同类题目推荐
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008) - 枚举三位数组合
2. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094) - 双指针与贪心结合
3. [P2119 魔法阵](https://www.luogu.com.cn/problem/P2119) - 多维枚举与数学优化

---
处理用时：52.03秒