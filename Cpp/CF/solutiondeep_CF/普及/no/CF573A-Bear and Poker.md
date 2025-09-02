# 题目信息

# Bear and Poker

## 题目描述

Limak is an old brown bear. He often plays poker with his friends. Today they went to a casino. There are $ n $ players (including Limak himself) and right now all of them have bids on the table. $ i $ -th of them has bid with size $ a_{i} $ dollars.

Each player can double his bid any number of times and triple his bid any number of times. The casino has a great jackpot for making all bids equal. Is it possible that Limak and his friends will win a jackpot?

## 说明/提示

In the first sample test first and third players should double their bids twice, second player should double his bid once and fourth player should both double and triple his bid.

It can be shown that in the second sample test there is no way to make all bids equal.

## 样例 #1

### 输入

```
4
75 150 75 50
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
3
100 150 250
```

### 输出

```
No
```

# AI分析结果



# Bear and Poker

## 题目描述

Limak 是一只年迈的棕熊，他经常和朋友们玩扑克。今天他们去了赌场。现在有 $n$ 名玩家（包括 Limak 自己），每个玩家在桌上都有一个出价。第 $i$ 个玩家的出价为 $a_i$ 美元。

每个玩家可以将其出价翻倍任意次数，或将其出价三倍化任意次数。赌场会为所有出价相等的情况提供巨额奖金。Limak 和他的朋友们能否赢得这个奖金？

## 说明/提示

第一个样例中，第一个和第三个玩家应将出价翻倍两次，第二个玩家翻倍一次，第四个玩家需要翻倍一次再三倍化一次。第二个样例无法使所有出价相等。

## 样例 #1

### 输入

```
4
75 150 75 50
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
3
100 150 250
```

### 输出

```
No
```

**分类标签**：数学

---

### 题解分析与结论

所有数的核心操作是去除所有 2 和 3 的因子，若剩余部分相同则可通过调整 2 和 3 的幂次使所有数相等。三种解法中，前两种思路一致且更简洁，第三种通过计算最大公约数后的分解方式验证可行性。

---

### 精选题解

#### 题解作者：Rbu_nas（★★★★★）
**核心思路**：  
每个数不断除以 2 和 3 直到无法整除，最终检查所有数是否相同。  
**实现要点**：  
- 遍历每个数，逐步去除所有 2 和 3 的因子  
- 剩余部分相同则返回 Yes  

```cpp
for(int i=1; i<=n; ++i) {
    while(!(a[i] % 2)) a[i]/=2;
    while(!(a[i] % 3)) a[i]/=3;
}
for(int i=1; i<n; ++i) 
    if(a[i] != a[i+1]) return puts("No");
```

#### 题解作者：Zhou_Wingay（★★★★☆）
**核心思路**：  
定义函数去除 2 和 3 的因子，代码更模块化。  
**实现要点**：  
- 单独函数处理数的因子去除  
- 简化主逻辑的判断流程  

```cpp
int zh(int x) {
    while(x%2==0) x/=2;
    while(x%3==0) x/=3;
    return x;
}
for(int i=0; i<n; i++) 
    if(a[i] != a[0]) return cout<<"No";
```

---

### 关键技巧总结

**核心数学思维**：  
问题等价于所有数在去除 2 和 3 的因子后是否同源。通过操作 2 和 3 的幂次调整，可以将数统一为相同值。这种去除无关因子、保留核心特征的思路适用于质因数分解相关题目。

**同类拓展**：  
- 质因数分解后的因子调整问题  
- 数论中的最大公约数/最小公倍数应用  

---

### 推荐练习题
1. P1075 [质因数分解](https://www.luogu.com.cn/problem/P1075)  
2. P1469 [找筷子](https://www.luogu.com.cn/problem/P1469)（异或性质）  
3. P2441 [角色属性](https://www.luogu.com.cn/problem/P2441)（最大公约数应用）

---
处理用时：186.19秒