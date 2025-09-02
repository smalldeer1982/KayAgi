# 题目信息

# Win or Freeze

## 题目描述

You can't possibly imagine how cold our friends are this winter in Nvodsk! Two of them play the following game to warm up: initially a piece of paper has an integer $ q $ . During a move a player should write any integer number that is a non-trivial divisor of the last written number. Then he should run this number of circles around the hotel. Let us remind you that a number's divisor is called non-trivial if it is different from one and from the divided number itself.

The first person who can't make a move wins as he continues to lie in his warm bed under three blankets while the other one keeps running. Determine which player wins considering that both players play optimally. If the first player wins, print any winning first move.

## 说明/提示

Number $ 6 $ has only two non-trivial divisors: $ 2 $ and $ 3 $ . It is impossible to make a move after the numbers $ 2 $ and $ 3 $ are written, so both of them are winning, thus, number $ 6 $ is the losing number. A player can make a move and write number $ 6 $ after number $ 30 $ ; $ 6 $ , as we know, is a losing number. Thus, this move will bring us the victory.

## 样例 #1

### 输入

```
6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
30
```

### 输出

```
1
6
```

## 样例 #3

### 输入

```
1
```

### 输出

```
1
0
```

# AI分析结果



# Win or Freeze

## 题目描述

你无法想象我们的朋友在诺夫哥斯克的冬天有多冷！两个朋友用以下游戏取暖：初始时纸上有一个整数 $q$。每轮玩家需写出前一个数的非平凡因数（即不是1和自身的因数）。无法操作的玩家获胜（可以躺在温暖被窝里）。

若先手必胜，输出 1 并给出任意必胜的第一步操作；否则输出 2。

## 算法分类
数学（质因数分解）

---

## 题解分析与结论

题目核心在于分析数的质因数结构。通过质因数分解，我们发现：

1. **当 q 是质数或 1 时**：先手无法操作，直接获胜（输出1 0）
2. **当质因数总次数和为2时**（如 6=2×3 或 4=2²）：后手必胜
3. **其他情况**：先手可通过选取特定因数将局面转化为必败态获胜

关键点在于快速分解质因数并统计质因数的种类和次数。

---

## 精选题解

### 题解作者：Lyw\_and\_Segment\_Tree（5星）
**关键亮点**：
- 使用质因数分解快速判断胜负状态
- 通过记录前两个质因数构造必胜操作
- 代码简洁，处理了所有边界情况

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[2],t;
void isprime(int n) {
    if (n==1) return;
    for(int i=2;i<=sqrt(n);i++){
        if(n%i==0){
            a[t++]=i;
            n/=i;
            i--;
            if(t==2) return;
        }
    }
}
signed main(){
    int q;
    cin>>q;
    isprime(q);
    if(t==0) puts("1\n0");
    else if(t==1) puts("2");
    else{ puts("1"); cout<<a[0]*a[1]; }
    return 0;
}
```

**核心思路**：
1. 分解质因数时记录前两个质因数
2. 质因数个数不足2 ⇒ 后手必胜
3. 否则输出前两个质因数的乘积作为必胜操作

---

### 题解作者：hjm777（4星）
**关键亮点**：
- 引入质因数次数和的概念（tot变量）
- 通过向量存储质因数，便于后续处理

```cpp
vector<int> vec; // 存储质因数
if(tot == 1) ... // q为质数
else if(tot == 2) ... // 后手必胜 
else ... // 输出前两个质因数积
```

**调试心得**：
- 注意处理质数的平方情况（如4=2²）
- 使用vector存储质因数便于扩展逻辑

---

### 题解作者：DinnerHunt（4星）
**优化技巧**：
- 在分解过程中及时判断状态，提前返回
- 使用累乘方式构造必胜操作数

```cpp
long long ans = 1;
void check(long long x) {
    // 分解过程中若已找到足够信息则提前返回
    if(k==2 && x!=y) { k++; return; } 
}
```

---

## 关键思路总结
1. **质因数分解**：快速将数分解为质因数乘积形式
2. **状态判断**：根据质因数个数和总次数判断游戏状态
3. **构造必胜操作**：选取前两个质因数乘积作为最优第一步

---

## 拓展应用
类似质因数分解博弈问题：
1. [CF1538D - Another Problem About Dividing Numbers](https://www.luogu.com.cn/problem/CF1538D)
2. [P2926 [USACO08DEC]Patting Heads S](https://www.luogu.com.cn/problem/P2926)
3. [P1072 [NOIP2009 提高组] Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)

---
处理用时：76.13秒