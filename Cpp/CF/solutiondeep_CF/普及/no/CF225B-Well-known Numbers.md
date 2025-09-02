# 题目信息

# Well-known Numbers

## 题目描述

Numbers $ k $ -bonacci ( $ k $ is integer, $ k&gt;1 $ ) are a generalization of Fibonacci numbers and are determined as follows:

- $ F(k,n)=0 $ , for integer $ n $ , $ 1<=n&lt;k $ ;
- $ F(k,k)=1 $ ;
- $ F(k,n)=F(k,n-1)+F(k,n-2)+...+F(k,n-k) $ , for integer $ n $ , $ n&gt;k $ .

Note that we determine the $ k $ -bonacci numbers, $ F(k,n) $ , only for integer values of $ n $ and $ k $ .

You've got a number $ s $ , represent it as a sum of several (at least two) distinct $ k $ -bonacci numbers.

## 样例 #1

### 输入

```
5 2
```

### 输出

```
3
0 2 3
```

## 样例 #2

### 输入

```
21 5
```

### 输出

```
3
4 1 16
```

# AI分析结果



# Well-known Numbers

## 题目描述

$k$-bonacci 数（$k$ 为整数且 $k>1$）是斐波那契数列的推广，定义如下：

- 对于 $1 \leq n < k$ 的整数 $n$，$F(k,n) = 0$；
- $F(k,k) = 1$；
- 对于 $n > k$ 的整数 $n$，$F(k,n) = F(k,n-1) + F(k,n-2) + ... + F(k,n-k)$。

给定一个数 $s$，将其表示为若干个（至少两个）不同的 $k$-bonacci 数的和。

## 算法分类
构造、贪心

## 题解综合分析

所有题解均采用**贪心构造**思路：首先生成 $k$-bonacci 数列，然后从大到小贪心选择元素进行拆分。核心差异在于数列生成方式和边界处理。关键难点在于证明贪心策略的正确性，以及处理最少元素要求。

---

### 精选题解列表

#### 题解作者：HllwEureka（★★★★☆）
**关键亮点**：  
1. 使用数学归纳法证明贪心策略的正确性  
2. 动态计算数列时自动处理窗口移动  
3. 代码简洁，采用数组直接存储结果  
**代码核心**：
```cpp
for(n=2;f[n-1]<s;n++)
    for(int j=max(1,n-k);j<=n-1;j++) 
        f[n]+=f[j];
// 贪心选取部分
for(int i=n-1;i>=1&&s;i--) 
    if(f[i]<=s) 
        ans[++m]=f[i], s-=f[i];
```

#### 题解作者：OIerZhang（★★★★☆）
**关键亮点**：  
1. 显式处理数值溢出问题（1e9 截断）  
2. 使用独立 pos 变量记录有效数列长度  
3. 边界条件处理清晰  
**个人心得**：  
"数据保证有解，无需复杂证明，直接暴力生成数列即可"  
**代码核心**：
```cpp
for(int i=3; i<=100; i++) {
    if(a[i-1] > 1e9) break; // 防止溢出
    for(int j=max(1,i-k); j<i; j++)
        a[i] += a[j];
}
// 贪心选取部分
for(int i=pos; i>=1; i--) 
    if(a[i] <= n) 
        ans[++cnt] = a[i], n -= a[i];
```

#### 题解作者：pitiless0514（★★★☆☆）
**优化亮点**：  
1. 前缀和优化加速数列生成  
2. 负数检测提前终止数列生成  
**核心思路**：
```cpp
// 前缀和生成数列
s[i] = s[i-1] + f[i];
// 滑动窗口维护前k项和
f[i] = s[i-1] - s[it-1];
```

---

## 最优关键思路
1. **数列生成优化**：使用滑动窗口或前缀和减少重复计算，时间复杂度从 $O(nk)$ 降为 $O(n)$  
2. **贪心策略证明**：数学归纳法证明从最大元素开始取的完备性  
3. **边界处理技巧**：当结果元素不足时补零满足题目至少两个数的要求  

## 拓展延伸
类似问题可参考：
1. 分解数为特殊数列和（如 [CF1102A Integer Sequence Dividing](https://www.luogu.com.cn/problem/CF1102A)）  
2. 贪心构造类问题（如 [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)）  
3. 斐波那契变种题（如 [P1962 斐波那契数列](https://www.luogu.com.cn/problem/P1962)）

## 推荐题目
1. [CF1263D. Secret Passwords](https://www.luogu.com.cn/problem/CF1263D)（构造+并查集）  
2. [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)（斐波那契+高精度）  
3. [P7072 直播获奖](https://www.luogu.com.cn/problem/P7072)（动态贪心策略）

---
处理用时：60.16秒