# 题目信息

# Restoring Three Numbers

## 题目描述

Polycarp has guessed three positive integers $ a $ , $ b $ and $ c $ . He keeps these numbers in secret, but he writes down four numbers on a board in arbitrary order — their pairwise sums (three numbers) and sum of all three numbers (one number). So, there are four numbers on a board in random order: $ a+b $ , $ a+c $ , $ b+c $ and $ a+b+c $ .

You have to guess three numbers $ a $ , $ b $ and $ c $ using given numbers. Print three guessed integers in any order.

Pay attention that some given numbers $ a $ , $ b $ and $ c $ can be equal (it is also possible that $ a=b=c $ ).

## 样例 #1

### 输入

```
3 6 5 4
```

### 输出

```
2 1 3
```

## 样例 #2

### 输入

```
40 40 40 60
```

### 输出

```
20 20 20
```

## 样例 #3

### 输入

```
201 101 101 200
```

### 输出

```
1 100 100
```

# AI分析结果



# Restoring Three Numbers

## 题目描述

Polycarp 猜想了三个正整数 $a$、$b$ 和 $c$。他将这四个数以任意顺序写在黑板上：它们的三个两两之和（$a+b$、$a+c$、$b+c$）以及三个数的总和（$a+b+c$）。你需要根据这四个数还原出 $a$、$b$ 和 $c$。输出任意顺序的三个数。

## 算法分类
数学

## 题解分析与结论

所有题解均基于以下核心思路：四个数中的最大值必为三个数的总和 $x_4 = a+b+c$。排序后，通过 $a = x_4 - (b+c)$、$b = x_4 - (a+c)$、$c = x_4 - (a+b)$ 推导出结果。以下为评分最高的三种实现方案：

---

### 题解选录

#### 1. 作者：codemap（5星）
**核心亮点**：代码极简，直击问题本质  
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{	
    int a[5];
    cin>>a[1]>>a[2]>>a[3]>>a[4];
    sort(a+1,a+5);
    cout<<a[4]-a[1]<<" "<<a[4]-a[2]<<" "<<a[4]-a[3];
    return 0;
}
```
**实现思路**：将输入存入数组后排序，最大值即为总和。直接输出总和与前三个数的差值。

#### 2. 作者：一扶苏一（5星）
**核心亮点**：严格数学推导，代码规范  
```cpp
ll a[4];
int main() {
  for (auto &i : a) qr(i);
  std::sort(a, a + 4);
  qw(a[3] - a[0], ' ', true); 
  qw(a[3] - a[1], ' ' , true); 
  qw(a[3] - a[2], '\n', true);
  return 0;
}
```
**实现思路**：使用快速读写优化，通过排序后直接计算差值。

#### 3. 作者：Eason_AC（5星）
**核心亮点**：公式推导清晰，代码精简  
```cpp
int x[7];
int main() {
    _for(i, 1, 4) getint(x[i]);
    sort(x + 1, x + 5);
    int a = x[4] - x[1], b = x[4] - x[2], c = x[4] - x[3];
    writeint(a), putchar(' '), writeint(b), putchar(' '), writeint(c);
    return 0;
}
```
**实现思路**：通过宏简化输入输出，直接应用公式计算结果。

---

## 关键思路
将四个数排序后，**最大值即为总和**，其余三个数分别为总和减去三个原始两两和。计算方式为：
- $a = sum - (b+c)$
- $b = sum - (a+c)$
- $c = sum - (a+b)$

## 拓展应用
类似需要从和差关系推导原始数据的题目，可参考以下洛谷题目：
1. [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)（基础求和）
2. [P1618 三连击（升级版）](https://www.luogu.com.cn/problem/P1618)（构造特定比例数）
3. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)（坐标覆盖问题）

## 心得体会
1. **排序简化判断**：通过排序快速确定最大值，避免复杂条件判断（如多个if分支）。
2. **数学公式转化**：将看似复杂的多变量问题转化为简单的代数运算。
3. **SPJ特性利用**：注意题目可能使用 Special Judge，输出任意顺序解均可，无需额外排序。

---
处理用时：77.39秒