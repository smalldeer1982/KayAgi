# 题目信息

# Gluttony

## 题目描述

You are given an array $ a $ with $ n $ distinct integers. Construct an array $ b $ by permuting $ a $ such that for every non-empty subset of indices $ S={x_{1},x_{2},...,x_{k}} $ ( $ 1<=x_{i}<=n $ , $ 0&lt;k&lt;n $ ) the sums of elements on that positions in $ a $ and $ b $ are different, i. e.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF891B/3cd3fa1580a1bdd16185974adbd0425cf2d97136.png)

## 说明/提示

An array $ x $ is a permutation of $ y $ , if we can shuffle elements of $ y $ such that it will coincide with $ x $ .

Note that the empty subset and the subset containing all indices are not counted.

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
2 1 
```

## 样例 #2

### 输入

```
4
1000 100 10 1
```

### 输出

```
100 1 1000 10
```

# AI分析结果

### 题目内容
# 暴食

## 题目描述
给定一个包含 $n$ 个不同整数的数组 $a$ 。通过对 $a$ 进行排列构造一个数组 $b$ ，使得对于每个非空的索引子集 $S = \{x_1, x_2, \ldots, x_k\}$ （$1 \leq x_i \leq n$ ，$0 < k < n$ ），$a$ 和 $b$ 中这些位置上元素的和是不同的，即

$\sum_{i \in S} a_i \neq \sum_{i \in S} b_i$

## 说明/提示
数组 $x$ 是 $y$ 的一个排列，是指我们可以对 $y$ 的元素进行洗牌，使其与 $x$ 重合。

注意，空子集和包含所有索引的子集不计算在内。

## 样例 #1
### 输入
```
2
1 2
```
### 输出
```
2 1 
```
## 样例 #2
### 输入
```
4
1000 100 10 1
```
### 输出
```
100 1 1000 10
```
### 算法分类
构造
### 综合分析与结论
三道题解思路本质相同，均是先对数组排序，再通过特定方式构造满足条件的数组 $b$ 。区别在于对构造方式的思考角度和证明过程。“我梦见一片焦土”从图论中环的角度思考，分析出要避免环上子序列通过加除减交错使和为0 ，进而采用递增序列构造；“pufanyi”和“Hutao__”直接提出排序后右移一位并将最大数与最小数配对的构造方法，并从子集和大小比较的角度给出证明。整体而言，“pufanyi”和“Hutao__”的思路更直接简洁，“我梦见一片焦土”的思考过程相对复杂但提供了不同视角。三道题解代码实现思路相近，均先读入数据排序，再按构造规则生成数组 $b$ 并输出。
### 所选的题解
- **作者：pufanyi  星级：4星**
    - **关键亮点**：思路简洁清晰，直接提出排序后右移一位并将最大数与最小数配对的构造方法，并给出简洁的证明。
    - **个人心得**：作者表示是乱搞通过，后思考得出证明，反映出先尝试再深入理解的解题过程。
    - **核心代码**：
```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 30;

int ans[maxn];

struct E
{
    int id, x;

    inline bool operator < (const E& other) const
    {
        return this->x < other.x;
    }
} aa[maxn];

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
    {
        scanf("%d", &aa[i].x);
        aa[i].id = i;
    }
    sort(aa + 1, aa + n + 1);
    for(int i = 1; i < n; ++i)
        ans[aa[i].id] = aa[i+1].x;
    ans[aa[n].id] = aa[1].x;
    for(int i = 1; i <= n; ++i)
        printf("%d ", ans[i]);
    return 0;
}
```
核心实现思想：先读入数据并记录每个数的原始位置，排序后按右移一位并将最大数与最小数配对的规则填充到 `ans` 数组，最后输出 `ans` 数组。
- **作者：Hutao__  星级：4星**
    - **关键亮点**：思路简洁，直接提出排序后右移一位的构造方法，并从子集和比较角度给出证明。
    - **核心代码**：
```cpp
//lgRMJ坏了不保证此代码能通过此题
#include<bits/stdc++.h>
using namespace std;
int n;
int ans[25];
struct m{
    int x;
    int id;
}a[205];
bool kkk(m a,m b){
    return a.x<b.x;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].x;
        a[i].id=i;
    }
    sort(a+1,a+n+1,kkk);
    for(int i=1;i<n;i++)ans[a[i].id]=a[i+1].x;
    ans[a[n].id]=a[1].x;
    for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
    return 0;
} 
```
核心实现思想：读入数据并记录原始位置，排序后按右移一位的规则填充到 `ans` 数组并输出。
### 最优关键思路或技巧
将数组排序后采用右移一位并把最大数与最小数配对的构造方式，能巧妙满足对于任意非空真子集，$a$ 和 $b$ 中对应位置元素和不同的条件。从子集和大小比较的角度证明该构造方法的正确性，简洁明了。
### 可拓展之处
此类题目属于构造类型，类似套路是对给定数据进行排序等预处理后，依据题目条件设计特定的排列或构造方式。常见于一些需要构造满足特定条件序列或数组的题目。
### 推荐洛谷题目
- [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

---
处理用时：38.46秒