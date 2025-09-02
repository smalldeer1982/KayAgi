# 题目信息

# Guess the Array

## 题目描述

This is an interactive problem. You should use flush operation after each printed line. For example, in C++ you should use fflush(stdout), in Java you should use System.out.flush(), and in Pascal — flush(output).

In this problem you should guess an array $ a $ which is unknown for you. The only information you have initially is the length $ n $ of the array $ a $ .

The only allowed action is to ask the sum of two elements by their indices. Formally, you can print two indices $ i $ and $ j $ (the indices should be distinct). Then your program should read the response: the single integer equals to $ a_{i}+a_{j} $ .

It is easy to prove that it is always possible to guess the array using at most $ n $ requests.

Write a program that will guess the array $ a $ by making at most $ n $ requests.

## 说明/提示

The format of a test to make a hack is:

- The first line contains an integer number $ n $ ( $ 3<=n<=5000 $ ) — the length of the array.
- The second line contains $ n $ numbers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{5} $ ) — the elements of the array to guess.

## 样例 #1

### 输入

```
5
 
9
 
7
 
9
 
11
 
6
 ```

### 输出

```
 
? 1 5
 
? 2 3
 
? 4 1
 
? 5 2
 
? 3 4
 
! 4 6 1 5 5```

# AI分析结果



# Guess the Array（猜数组）

## 题目描述
这是一个交互题。每次询问可以获取两个不同位置元素的和，最多询问n次后输出完整数组。

## 算法分类
构造、数学

---

### 题解综合分析
各题解核心思路一致：通过前三个元素的两两和建立方程组求解初始值，之后每次询问第1个元素与后续元素的和。关键差异在于方程求解方式和交互输出处理细节。

---

### 优质题解推荐
#### 1. rsdbk_husky（★★★★☆）
**亮点**  
- 完整推导三元一次方程求解过程  
- 验证了交互题中`endl`与`fflush`的配合使用  
- 代码结构清晰，变量命名规范  
**核心代码**  
```cpp
int add12, add23, add13;
cout << "? 1 2" << endl; scanf("%d", &add12);
cout << "? 2 3" << endl; scanf("%d", &add23);
cout << "? 1 3" << endl; scanf("%d", &add13);
int first = (add13 - add23 + add12) >> 1;
for(int i=4; i<=n; i++) {
    cout << "? 1 " << i << endl;
    scanf("%d", &add[i]);
    a[i] = add[i] - first;
}
```
**心得**  
"endl会自动刷新缓冲区，但printf需要手动fflush"  

#### 2. codeLJH114514（★★★★☆）
**亮点**  
- 数学公式排版清晰  
- 代码注释详细解释推导过程  
**核心公式**  
$$x = \frac{a + c - b}{2},\ y = a - x,\ z = c - x$$

#### 3. qw1234321（★★★☆☆）
**亮点**  
- 使用统一变量名sum12等提高可读性  
- 包含完整后处理流程  

---

### 最优技巧总结
1. **三元方程构造**：通过前三次询问构建三元方程组，利用总和公式快速求解  
2. **链式推导**：已知首元素后，每次只需一次询问即可推出后续元素  
3. **交互处理**：优先使用`cout << endl`自动刷新，避免忘记fflush  

---

### 拓展训练
1. **同型构造题**：[CF727C](https://codeforces.com/contest/727/problem/C)（本题原型）  
2. **交互技巧**：[P1947](https://www.luogu.com.cn/problem/P1947)（双重反馈机制）  
3. **方程构造**：[P7705](https://www.luogu.com.cn/problem/P7705)（数学+构造综合应用）

---
处理用时：51.01秒