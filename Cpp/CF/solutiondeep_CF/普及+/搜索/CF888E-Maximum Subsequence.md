# 题目信息

# Maximum Subsequence

## 题目描述

You are given an array $ a $ consisting of $ n $ integers, and additionally an integer $ m $ . You have to choose some sequence of indices $ b_{1},b_{2},...,b_{k} $ ( $ 1<=b_{1}&lt;b_{2}&lt;...&lt;b_{k}<=n $ ) in such a way that the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png) is maximized. Chosen sequence can be empty.

Print the maximum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png).

## 说明/提示

In the first example you can choose a sequence $ b={1,2} $ , so the sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/08d6750b1b23699a8b513ddd01c316f10e6a789c.png) is equal to $ 7 $ (and that's $ 3 $ after taking it modulo $ 4 $ ).

In the second example you can choose a sequence $ b={3} $ .

## 样例 #1

### 输入

```
4 4
5 2 4 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 20
199 41 299
```

### 输出

```
19
```

# AI分析结果



# Maximum Subsequence

## 题目描述

给定一个包含 $n$ 个整数的数组 $a$ 和一个整数 $m$。你需要选择一个下标序列 $b_{1},b_{2},...,b_{k}$（$1 \leq b_1 < b_2 < ... < b_k \leq n$），使得 $\left( \sum_{i=1}^{k} a_{b_i} \right) \mod m$ 的值最大。选择的序列可以为空。

## 样例 #1

### 输入
```
4 4
5 2 4 1
```

### 输出
```
3
```

## 样例 #2

### 输入
```
3 20
199 41 299
```

### 输出
```
19
```

---

### 综合分析与结论
各题解核心思路高度一致，均采用折半搜索（Meet-in-the-Middle）算法。关键解决路径为：
1. 将数组分为两半，分别暴力枚举所有子集和
2. 对两部分结果排序后，使用双指针或二分法快速合并最优解
3. 处理模运算时巧妙利用数值范围特性（所有值 < m）

---

### 优质题解推荐

#### 1. 作者：newbiechd（★★★★★）
**核心亮点**：
- 分治策略清晰，代码实现简洁
- 双指针合并部分的数学证明完整
- 包含特判n=1的边界处理
```cpp
// 关键代码：双指针合并策略
sort(p+1,p+k+1), sort(q+1,q+t+1);
int i=0, j=t, ans=0;
while(i <= k) {
    while(p[i]+q[j] >= m) --j;
    ans = max(ans, p[i]+q[j]);
    ++i;
}
ans = max(ans, p[k]+q[t] - m);
```

#### 2. 作者：Youngore（★★★★☆）
**核心亮点**：
- 对模运算结果分类讨论透彻
- 指针移动策略的数学推导严谨
- 博客链接提供扩展思考
```cpp
// 关键代码：模数分类处理
sort(sum1, sum2);
for(r=1~cnt2) {
    while(sum1[l]+sum2[r] >= mod) --l;
    res = max(res, sum1[l]+sum2[r]);
}
```

#### 3. 作者：fls233666（★★★★☆）
**核心亮点**：
- 使用vector存储中间结果节省空间
- 二分查找实现方式适合新手理解
- 代码注释详细便于学习
```cpp
// 关键代码：二分查找优化
int tp = lower_bound(pans.begin(), pans.end(), m-s)-1 - pans.begin();
ans = max(ans, pans[tp]+s);
ans = max(ans, (pans.back()+s)%m);
```

---

### 关键技巧总结
1. **折半搜索框架**：将35元素拆分为两个18元素的子问题，复杂度从O(2^35)降为O(2^18)
2. **双指针合并法**：利用排序后数组的单调性，线性时间找到最优配对
3. **模运算性质运用**：最大有效和为2m-1，分情况讨论（<m 和 ≥m）
4. **边界处理**：特判n=1等极端情况

---

### 同类题目推荐
1. [P4799 世界冰球锦标赛](https://www.luogu.com.cn/problem/P4799)（折半搜索模板题）
2. [P3067 Balanced Cow Subsets](https://www.luogu.com.cn/problem/P3067)（状态压缩+双向搜索）
3. [P7542 马来熊学数学](https://www.luogu.com.cn/problem/P7542)（模运算优化技巧）

---

### 调试经验摘录
- **特判陷阱**：多个作者提到n=1时需要单独处理（直接输出a[1]%m）
- **初始值设定**：ans初始值应设为0而非-INF，因空集是合法选择
- **排序必要性**：未排序的数组无法应用双指针优化，会导致错误配对
- **模运算溢出**：部分题解强调要在每次加法后立即取模，防止整型溢出

---
处理用时：48.49秒