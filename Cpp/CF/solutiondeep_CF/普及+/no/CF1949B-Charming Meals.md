# 题目信息

# Charming Meals

## 题目描述

The Czech cuisine features $ n $ appetizers and $ n $ main dishes. The $ i $ -th appetizer has spiciness $ a_i $ , and the $ i $ -th main dish has spiciness $ b_i $ .

A typical Czech meal consists of exactly one appetizer and one main dish. You want to pair up the $ n $ appetizers and $ n $ main dishes into $ n $ meals with each appetizer and each main dish being included in exactly one meal.

Your meals shall surprise the diners, so you want the spiciness levels of the two parts of the same meal to be as different as possible. The charm of a meal is the difference (in absolute value) between the spiciness of the appetizer and the spiciness of the main dish. So, a meal consisting of an appetizer with spiciness $ x $ and a main dish with spiciness $ y $ has charm equal to $ |x-y| $ .

You want to maximize the minimum charm of the resulting $ n $ meals. What is the largest possible value of the minimum charm that you can achieve?

## 说明/提示

In the first test case, no matter how you pair up the appetizers with the main dishes, each meal will have an appetizer with spiciness $ 0 $ and a main dish with spiciness $ 1000000000 $ , so the charm of each meal will be $ 1000000000 $ .

In the second test case, one optimal way to pair up appetizers and main dishes is: $ (1, 5) $ , $ (2, 4) $ , $ (3, 1) $ , $ (4, 2) $ , $ (5, 3) $ . The corresponding meals have charms: $ 4 $ , $ 2 $ , $ 2 $ , $ 2 $ , $ 2 $ . The resulting minimum charm is $ 2 $ .

In the third test case, one way to maximize the minimum charm is to pair up the three appetizers with spiciness $ 0 $ with the three main dishes with spiciness $ 100 $ , and the three appetizers with spiciness $ 100 $ with the three main dishes with spiciness $ 0 $ . Doing so, the charm of each meal will be exactly $ 100 $ .

## 样例 #1

### 输入

```
4
3
0 0 0
1000000000 1000000000 1000000000
5
1 2 3 4 5
1 2 3 4 5
6
0 0 0 100 100 100
100 100 100 0 0 0
7
14 25 62 74 86 95 12
51 62 71 72 92 20 84```

### 输出

```
1000000000
2
100
30```

# AI分析结果

### 题目内容重写
# 魅力餐点

## 题目描述

捷克菜系有 $n$ 种开胃菜和 $n$ 种主菜。第 $i$ 种开胃菜的辣度为 $a_i$，第 $i$ 种主菜的辣度为 $b_i$。

一顿典型的捷克餐点由恰好一种开胃菜和一种主菜组成。你需要将 $n$ 种开胃菜和 $n$ 种主菜配对成 $n$ 顿餐点，每顿餐点包含一种开胃菜和一种主菜，且每种开胃菜和主菜只能使用一次。

为了让餐点更具惊喜感，你希望同一顿餐点中的开胃菜和主菜的辣度差异尽可能大。一顿餐点的魅力值定义为开胃菜和主菜辣度差的绝对值。即，若一顿餐点包含辣度为 $x$ 的开胃菜和辣度为 $y$ 的主菜，则其魅力值为 $|x-y|$。

你希望最大化所有 $n$ 顿餐点中最小魅力值。请问你能达到的最大最小魅力值是多少？

## 说明/提示

在第一个测试用例中，无论如何配对开胃菜和主菜，每顿餐点都将包含辣度为 $0$ 的开胃菜和辣度为 $1000000000$ 的主菜，因此每顿餐点的魅力值都为 $1000000000$。

在第二个测试用例中，一种最优的配对方式为：$(1, 5)$、$(2, 4)$、$(3, 1)$、$(4, 2)$、$(5, 3)$。对应的餐点魅力值分别为：$4$、$2$、$2$、$2$、$2$。最终的最小魅力值为 $2$。

在第三个测试用例中，一种最大化最小魅力值的方式是将三个辣度为 $0$ 的开胃菜与三个辣度为 $100$ 的主菜配对，将三个辣度为 $100$ 的开胃菜与三个辣度为 $0$ 的主菜配对。这样，每顿餐点的魅力值恰好为 $100$。

## 样例 #1

### 输入

```
4
3
0 0 0
1000000000 1000000000 1000000000
5
1 2 3 4 5
1 2 3 4 5
6
0 0 0 100 100 100
100 100 100 0 0 0
7
14 25 62 74 86 95 12
51 62 71 72 92 20 84
```

### 输出

```
1000000000
2
100
30
```

### 算法分类
贪心

### 题解分析与结论
题目要求最大化所有餐点中最小魅力值，即最大化最小差值。常见的解决思路是贪心算法，通过排序和枚举来找到最优的配对方式。

### 所选高分题解

#### 题解1：作者：OIer_Hhy (赞：4)
**星级：4**
**关键亮点：**
- 通过排序和枚举折点的方式，找到最优的配对方案。
- 代码简洁，思路清晰。

**核心代码：**
```cpp
int ans=0;
for(int i=1;i<=n;i++){ // 枚举折点
    int tmp=INT_MAX; 
    for(int j=1;j<=i;j++)
        tmp=min(tmp,abs(a[j]-b[n-i+j]));
    for(int j=i+1;j<=n;j++)
        tmp=min(tmp,abs(a[j]-b[j-i]));
    ans=max(ans,tmp);
}
```
**核心思想：**
- 排序后枚举折点，分别计算前一部分和后一部分的最小差值，取最大值。

#### 题解2：作者：Erica_N_Contina (赞：3)
**星级：4**
**关键亮点：**
- 通过枚举 $p$ 的值，计算每一对匹配的差值，取最小值作为答案。
- 提供了详细的证明，增强了思路的可信度。

**核心代码：**
```cpp
void check(int t){
    int res=INF;
    for(int i=1;i<=t;i++){
        res=min(res,abs(a[i]-b[i+n-t]));
    }
    for(int i=t+1;i<=n;i++){
        res=min(res,abs(a[i]-b[i-t]));
    }
    ans=max(ans,res);
}
```
**核心思想：**
- 枚举 $p$ 的值，计算前 $p$ 个和后 $n-p$ 个的最小差值，取最大值。

#### 题解3：作者：Star_F (赞：0)
**星级：4**
**关键亮点：**
- 使用二分答案的方法，优化了时间复杂度。
- 通过二分前缀长度和后缀长度，检查答案的合法性。

**核心代码：**
```cpp
bool check(int w){
    int st=0,ed=n;
    while(st<ed){
        int mid=(st+ed+1)>>1;
        if(calc1(mid,w)) st=mid;
        else ed=mid-1;
    }
    return calc2(st,w);
}
```
**核心思想：**
- 二分答案，检查前缀和后缀是否满足最小差值的条件。

### 最优关键思路
1. **排序与枚举**：通过排序数组，枚举折点或 $p$ 的值，计算最小差值，取最大值。
2. **二分答案**：通过二分答案，检查前缀和后缀是否满足条件，优化时间复杂度。

### 可拓展之处
类似的问题可以扩展到多维数组的匹配，或者更复杂的差值计算。贪心和二分答案的思路在这些问题中仍然适用。

### 推荐题目
1. [P1896 [SCOI2005] 互不侵犯](https://www.luogu.com.cn/problem/P1896)
2. [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)
3. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)

### 个人心得摘录
- **调试经历**：在枚举折点时，注意边界条件的处理，避免数组越界。
- **顿悟感想**：通过排序和贪心策略，可以有效地解决最大化最小值的问题。

---
处理用时：48.77秒