# 题目信息

# Range = √Sum

## 题目描述

You are given an integer $ n $ . Find a sequence of $ n $ distinct integers $ a_1, a_2, \dots, a_n $ such that $ 1 \leq a_i \leq 10^9 $ for all $ i $ and $ $$$\max(a_1, a_2, \dots, a_n) - \min(a_1, a_2, \dots, a_n)= \sqrt{a_1 + a_2 + \dots + a_n}. $ $$$

It can be proven that there exists a sequence of distinct integers that satisfies all the conditions above.

## 说明/提示

In the first test case, the maximum is $ 3 $ , the minimum is $ 1 $ , the sum is $ 4 $ , and $ 3 - 1 = \sqrt{4} $ .

In the second test case, the maximum is $ 29 $ , the minimum is $ 18 $ , the sum is $ 121 $ , and $ 29-18 = \sqrt{121} $ .

For each test case, the integers are all distinct.

## 样例 #1

### 输入

```
3
2
5
4```

### 输出

```
3 1
20 29 18 26 28
25 21 23 31```

# AI分析结果



### 题目中文重写
见原题描述，已为中文无需重复翻译。

---

### 题解综合分析

#### 最优关键思路总结
1. **平方和构造法**：设定总和为 $4n^2$，此时差值需为 $2n$。构造连续数列后整体调整余数（nullqtr_pwp）
2. **奇偶分段构造**：分奇偶构造对称数列，利用等差数列特性满足条件（Binary_Lee）
3. **中心扩散法**：以 $3n$ 和 $5n$ 为极差，构造平均值为 $4n$ 的对称数列（Svemit）

#### 推荐题解列表

**1. nullqtr_pwp（★★★★☆）**
- **核心思路**：预计算总和为 $4n^2$，构建初始序列后整体调整余数
- **代码亮点**：时间复杂度 $O(n)$，处理余数巧妙
```cpp
void solve(){
    int n=read();
    int sum=n*n*4,tot=0;
    for(int i=1;i<=n-1;i++) a[i]=i;
    a[n]=1+2*n;  //初始构造
    for(int i=1;i<=n;i++) tot+=a[i];
    int add=(sum-tot)/n;  //计算整体偏移量
    a[n-1]+=sum-tot-add*n;  //处理余数
    for(int i=1;i<=n;i++) printf("%lld ",a[i]+add);
}
```

**2. Binary_Lee（★★★★☆）**
- **核心思路**：分奇偶构造对称等差数列，数学验证严谨
- **奇偶处理**：奇数构造中间值，偶数构造对称区间
```cpp
void solve(){
    if(n&1){ //奇数构造
        for(int i=n/2+2;i<=n;i++) cout<<i<<' ';
        for(int i=n+3;i<=n+n/2+3;i++) cout<<i<<' ';
    }
    else{ //偶数构造
        for(int i=n/2;i<n;i++) cout<<i<<' ';
        for(int i=n+1;i<=n+n/2;i++) cout<<i<<' ';
    }
}
```

**3. Svemit（★★★★☆）**
- **核心思路**：以 $3n$ 和 $5n$ 为极差构造对称数列
- **实现技巧**：奇偶统一处理，维护平均数 $4n$
```cpp
a[1]=3*n;
a[n]=5*n;
if(n%2==0){ //偶数特殊处理中间对
    a[n/2]=4*n-1;
    a[n/2+1]=4*n+1;
}
```

---

### 同类题目推荐
1. [CF1353D - Constructing the Array](https://www.luogu.com.cn/problem/CF1353D)  
   **相似点**：构造类问题，需要设计特殊排列策略

2. [P1495 曹冲养猪](https://www.luogu.com.cn/problem/P1495)  
   **相似点**：数学构造题，利用模数特性构建解

3. [CF1156C - Match Points](https://www.luogu.com.cn/problem/CF1156C)  
   **相似点**：极差与数列性质结合，需要贪心策略

---

### 个人心得摘录
1. **nullqtr_pwp**：通过预计算总和简化构造过程，余数处理体现数学优化
2. **liangbowen**：构造失败后采用整体翻倍调整，体现调试中的灵活应变
3. **huangrenheluogu**：尝试连续数列失败后改用对称构造，展示思维迭代过程

---

### 关键实现技巧
**余数均匀分配**：当整体偏移后仍有剩余量时，将余数加至中间元素保持有序性  
**极差平方对齐**：通过设定 (max-min)² = sum 建立方程，降低构造难度  
**奇偶统一处理**：通过数学变换将不同情况统一为相似构造模式

---
处理用时：49.38秒