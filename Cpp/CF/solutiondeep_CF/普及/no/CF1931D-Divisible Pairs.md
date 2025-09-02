# 题目信息

# Divisible Pairs

## 题目描述

Polycarp has two favorite integers $ x $ and $ y $ (they can be equal), and he has found an array $ a $ of length $ n $ .

Polycarp considers a pair of indices $ \langle i, j \rangle $ ( $ 1 \le i < j \le n $ ) beautiful if:

- $ a_i + a_j $ is divisible by $ x $ ;
- $ a_i - a_j $ is divisible by $ y $ .

For example, if $ x=5 $ , $ y=2 $ , $ n=6 $ , $ a= $ \[ $ 1, 2, 7, 4, 9, 6 $ \], then the only beautiful pairs are:

- $ \langle 1, 5 \rangle $ : $ a_1 + a_5 = 1 + 9 = 10 $ ( $ 10 $ is divisible by $ 5 $ ) and $ a_1 - a_5 = 1 - 9 = -8 $ ( $ -8 $ is divisible by $ 2 $ );
- $ \langle 4, 6 \rangle $ : $ a_4 + a_6 = 4 + 6 = 10 $ ( $ 10 $ is divisible by $ 5 $ ) and $ a_4 - a_6 = 4 - 6 = -2 $ ( $ -2 $ is divisible by $ 2 $ ).

 Find the number of beautiful pairs in the array $ a $ .

## 样例 #1

### 输入

```
7
6 5 2
1 2 7 4 9 6
7 9 5
1 10 15 3 8 12 15
9 4 10
14 10 2 2 11 11 13 5 6
9 5 6
10 7 6 7 9 7 7 10 10
9 6 2
4 9 7 1 2 2 13 3 15
9 2 3
14 6 1 15 12 15 8 2 15
10 5 7
13 3 3 2 12 11 3 7 13 14```

### 输出

```
2
0
1
3
5
7
0```

# AI分析结果



# 可被整除对

## 题目描述

Polycarp 有两个喜欢的整数 $x$ 和 $y$（可以相等），并发现了一个长度为 $n$ 的数组 $a$。

Polycarp 认为下标对 $\langle i, j \rangle$（$1 \le i < j \le n$）是美丽的，当且仅当：

- $a_i + a_j$ 能被 $x$ 整除；
- $a_i - a_j$ 能被 $y$ 整除。

例如，当 $x=5$，$y=2$，$n=6$，$a= [1, 2, 7, 4, 9, 6]$ 时，唯一的美丽对是：

- $\langle 1, 5 \rangle$：$a_1 + a_5 = 1 + 9 = 10$（能被 $5$ 整除），$a_1 - a_5 = 1 - 9 = -8$（能被 $2$ 整除）；
- $\langle 4, 6 \rangle$：$a_4 + a_6 = 4 + 6 = 10$（能被 $5$ 整除），$a_4 - a_6 = 4 - 6 = -2$（能被 $2$ 整除）。

请找出数组中美丽对的总数。

## 算法分类
数学

## 题解综合分析

本题核心在于利用同余性质和哈希映射统计符合条件的数对。所有题解均通过以下思路优化暴力解法：

1. **同余转换**：将条件转换为：
   - $(a_i \bmod x + a_j \bmod x) \equiv 0 \pmod x$
   - $(a_i \bmod y) \equiv (a_j \bmod y) \pmod y$

2. **逆向映射**：维护哈希表记录已遍历元素的 $(a_i \bmod x, a_i \bmod y)$ 出现次数。对于当前元素 $a_j$，查询满足 $(x - a_j \bmod x) \bmod x$ 和 $a_j \bmod y$ 的键值对数目。

3. **遍历顺序**：采用逆序或正序处理，确保 $i < j$ 的条件。

## 精选题解

### 题解1（jiangxinyang2012）⭐⭐⭐⭐⭐
**亮点**  
- 逆向遍历配合map存储余数对  
- 代码简洁高效，逻辑清晰  
```cpp
map<pair<ll, ll>, int> mp;
for(int i = n; i >= 1; i--) {
    int s1 = (x - a[i]%x) %x, s2 = a[i]%y;
    ans += mp[{s1, s2}];
    mp[{a[i]%x, a[i]%y}]++;
}
```

### 题解2（zhuweiqi）⭐⭐⭐⭐⭐
**亮点**  
- 使用pair作为map键，代码可读性极佳  
- 正序处理时先查询后更新，保证顺序正确  
```cpp
map<pair<int,int>,int> p;
for(int i=n;i>=1;i--){
    ans+=p[{(x-a[i]%x)%x,a[i]%y}];
    p[{a[i]%x,a[i]%y}]++;
}
```

### 题解3（信息向阳花木）⭐⭐⭐⭐
**亮点**  
- 预处理模运算结果减少冗余计算  
- 采用pair结构维护余数关系  
```cpp
map<PII, int> mp;
for(int i=1;i<=n;i++){
    int p = x - a[i]%x;
    if(p ==x) p=0;
    res += mp[{p, a[i]%y}];
    mp[{a[i]%x, a[i]%y}]++;
}
```

## 关键思路总结
1. **同余转换**：将加法减法条件转换为模运算形式，建立逆向映射关系。
2. **哈希优化**：用哈希表存储已遍历元素的模值组合，将双重循环优化至线性复杂度。
3. **顺序处理**：通过逆序或先查询后更新的方式保证数对顺序。

## 拓展思考
类似问题可参考：
1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)  
2. [P2421 荒岛野人](https://www.luogu.com.cn/problem/P2421)  
3. [P1463 反素数](https://www.luogu.com.cn/problem/P1463)

## 调试心得
- **余数零处理**：注意当 $a_i \bmod x =0$ 时，对应的互补余数应为 $(x - 0) \bmod x =0$。
- **负数处理**：C++中负数的取模运算结果可能为负，需通过 `(x - a%x) %x` 确保结果非负。

---
处理用时：60.01秒