# 题目信息

# Optimal Subsequences (Easy Version)

## 题目描述

This is the easier version of the problem. In this version $ 1 \le n, m \le 100 $ . You can hack this problem only if you solve and lock both problems.

You are given a sequence of integers $ a=[a_1,a_2,\dots,a_n] $ of length $ n $ . Its subsequence is obtained by removing zero or more elements from the sequence $ a $ (they do not necessarily go consecutively). For example, for the sequence $ a=[11,20,11,33,11,20,11] $ :

- $ [11,20,11,33,11,20,11] $ , $ [11,20,11,33,11,20] $ , $ [11,11,11,11] $ , $ [20] $ , $ [33,20] $ are subsequences (these are just some of the long list);
- $ [40] $ , $ [33,33] $ , $ [33,20,20] $ , $ [20,20,11,11] $ are not subsequences.

Suppose that an additional non-negative integer $ k $ ( $ 1 \le k \le n $ ) is given, then the subsequence is called optimal if:

- it has a length of $ k $ and the sum of its elements is the maximum possible among all subsequences of length $ k $ ;
- and among all subsequences of length $ k $ that satisfy the previous item, it is lexicographically minimal.

Recall that the sequence $ b=[b_1, b_2, \dots, b_k] $ is lexicographically smaller than the sequence $ c=[c_1, c_2, \dots, c_k] $ if the first element (from the left) in which they differ less in the sequence $ b $ than in $ c $ . Formally: there exists $ t $ ( $ 1 \le t \le k $ ) such that $ b_1=c_1 $ , $ b_2=c_2 $ , ..., $ b_{t-1}=c_{t-1} $ and at the same time $ b_t<c_t $ . For example:

- $ [10, 20, 20] $ lexicographically less than $ [10, 21, 1] $ ,
- $ [7, 99, 99] $ is lexicographically less than $ [10, 21, 1] $ ,
- $ [10, 21, 0] $ is lexicographically less than $ [10, 21, 1] $ .

You are given a sequence of $ a=[a_1,a_2,\dots,a_n] $ and $ m $ requests, each consisting of two numbers $ k_j $ and $ pos_j $ ( $ 1 \le k \le n $ , $ 1 \le pos_j \le k_j $ ). For each query, print the value that is in the index $ pos_j $ of the optimal subsequence of the given sequence $ a $ for $ k=k_j $ .

For example, if $ n=4 $ , $ a=[10,20,30,20] $ , $ k_j=2 $ , then the optimal subsequence is $ [20,30] $ — it is the minimum lexicographically among all subsequences of length $ 2 $ with the maximum total sum of items. Thus, the answer to the request $ k_j=2 $ , $ pos_j=1 $ is the number $ 20 $ , and the answer to the request $ k_j=2 $ , $ pos_j=2 $ is the number $ 30 $ .

## 说明/提示

In the first example, for $ a=[10,20,10] $ the optimal subsequences are:

- for $ k=1 $ : $ [20] $ ,
- for $ k=2 $ : $ [10,20] $ ,
- for $ k=3 $ : $ [10,20,10] $ .

## 样例 #1

### 输入

```
3
10 20 10
6
1 1
2 1
2 2
3 1
3 2
3 3
```

### 输出

```
20
10
20
10
20
10
```

## 样例 #2

### 输入

```
7
1 2 1 3 1 2 1
9
2 1
2 2
3 1
3 2
3 3
1 1
7 1
7 7
7 4
```

### 输出

```
2
3
2
3
2
3
1
1
3
```

# AI分析结果

### 题目翻译
#### 最优子序列（简单版本）

#### 题目描述
这是该问题的简单版本。在此版本中，$ 1 \le n, m \le 100 $。只有当你解决并锁定两个问题后，才能对本题进行 Hack 操作。

给定一个长度为 $ n $ 的整数序列 $ a=[a_1,a_2,\dots,a_n] $。它的子序列是通过从序列 $ a $ 中移除零个或多个元素（这些元素不一定连续）得到的。例如，对于序列 $ a=[11,20,11,33,11,20,11] $：
- $ [11,20,11,33,11,20,11] $、$ [11,20,11,33,11,20] $、$ [11,11,11,11] $、$ [20] $、$ [33,20] $ 都是子序列（这些只是众多子序列中的一部分）；
- $ [40] $、$ [33,33] $、$ [33,20,20] $、$ [20,20,11,11] $ 都不是子序列。

假设给定一个额外的非负整数 $ k $（$ 1 \le k \le n $），那么满足以下条件的子序列被称为最优子序列：
- 它的长度为 $ k $，并且在所有长度为 $ k $ 的子序列中，其元素之和最大；
- 在所有满足上述条件的长度为 $ k $ 的子序列中，它的字典序最小。

回顾一下，如果序列 $ b=[b_1, b_2, \dots, b_k] $ 和序列 $ c=[c_1, c_2, \dots, c_k] $ 从左到右第一个不同的元素在序列 $ b $ 中比在序列 $ c $ 中小，那么序列 $ b $ 的字典序小于序列 $ c $。形式上：存在 $ t $（$ 1 \le t \le k $），使得 $ b_1=c_1 $，$ b_2=c_2 $，...，$ b_{t - 1}=c_{t - 1} $，同时 $ b_t < c_t $。例如：
- $ [10, 20, 20] $ 的字典序小于 $ [10, 21, 1] $；
- $ [7, 99, 99] $ 的字典序小于 $ [10, 21, 1] $；
- $ [10, 21, 0] $ 的字典序小于 $ [10, 21, 1] $。

给定一个序列 $ a=[a_1,a_2,\dots,a_n] $ 和 $ m $ 个查询，每个查询由两个数 $ k_j $ 和 $ pos_j $（$ 1 \le k \le n $，$ 1 \le pos_j \le k_j $）组成。对于每个查询，输出给定序列 $ a $ 在 $ k = k_j $ 时的最优子序列中索引为 $ pos_j $ 的值。

例如，如果 $ n = 4 $，$ a = [10,20,30,20] $，$ k_j = 2 $，那么最优子序列是 $ [20,30] $ —— 它是所有长度为 $ 2 $ 且元素总和最大的子序列中字典序最小的。因此，查询 $ k_j = 2 $，$ pos_j = 1 $ 的答案是数字 $ 20 $，查询 $ k_j = 2 $，$ pos_j = 2 $ 的答案是数字 $ 30 $。

#### 说明/提示
在第一个示例中，对于 $ a = [10,20,10] $，最优子序列如下：
- 当 $ k = 1 $ 时：$ [20] $；
- 当 $ k = 2 $ 时：$ [10,20] $；
- 当 $ k = 3 $ 时：$ [10,20,10] $。

#### 样例 #1
##### 输入
```
3
10 20 10
6
1 1
2 1
2 2
3 1
3 2
3 3
```
##### 输出
```
20
10
20
10
20
10
```

#### 样例 #2
##### 输入
```
7
1 2 1 3 1 2 1
9
2 1
2 2
3 1
3 2
3 3
1 1
7 1
7 7
7 4
```
##### 输出
```
2
3
2
3
2
3
1
1
3
```

### 算法分类
排序

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，结合排序来解决问题。因为题目要求子序列和最大且字典序最小，所以先将序列从大到小排序，取前 $k$ 个数保证和最大。当存在相同元素时，为满足字典序最小，优先选取原序列中靠前的元素。

各题解的主要区别在于实现细节，比如使用的数据结构不同，有的用 `map` 记录元素数量，有的用结构体记录元素值和原下标；排序方式也有差异，部分题解在排序时考虑了元素原下标，以确保字典序最小。

### 高评分题解
- **作者：HoshizoraZ (赞：5)，4星**
    - **关键亮点**：思路清晰，对贪心策略的解释详细，代码实现简洁，使用 `std::map` 处理元素数量，易于理解。
- **作者：Rex01 (赞：2)，4星**
    - **关键亮点**：思路明确，代码规范，通过注释解释了关键步骤，使用 `map` 避免超时，提高了代码效率。
- **作者：elbissoPtImaerD (赞：2)，4星**
    - **关键亮点**：复杂度分析清晰，使用结构体记录元素值和下标，通过自定义排序函数实现按要求排序，代码简洁高效。

### 重点代码
#### HoshizoraZ 的代码
```cpp
#include <bits/stdc++.h>
#define INF 1e9
#define eps 1e-6
typedef long long ll;
using namespace std;

map <int, int> M;
int n, m, a[110], b[110], seq[110], ss;
bool bb[110];

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]), b[i] = a[i];
    sort(b + 1, b + n + 1);
    scanf("%d", &m);
    for(int i = 1, k, pos; i <= m; i++){
        scanf("%d%d", &k, &pos);
        for(int j = n; j >= n - k + 1; j--)  // 挑前 k 大
            M[b[j]]++;
        ss = 0;
        for(int j = 1; j <= n; j++)  // 放到原序列找
            if(M[a[j]] > 0)
                M[a[j]]--, seq[++ss] = a[j];
        printf("%d\n", seq[pos]);
    }
    return 0;
}
```
**核心实现思想**：先将原序列复制一份并排序，对于每个查询，统计前 $k$ 大元素的数量，然后遍历原序列，按顺序选取这些元素，最后输出指定位置的元素。

#### Rex01 的代码
```cpp
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

const int N = 110;
int n, a[N], m;
int b[N], d[N];
map <int, int> c;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(a + 1, a + n + 1);
    cin >> m;
    for(int i = 1; i <= m; i++)
    {
        int k, p, sum = 0;
        cin >> k >> p;
        for(int j = n; j >= n - k + 1; j--) c[a[j]]++;
        for(int j = 1; j <= n; j++)
            if(c[b[j]] > 0)
            {
                c[b[j]]--;
                d[++sum] = b[j];
            }
        cout << d[p] << endl;
    }
    return 0;
}
```
**核心实现思想**：同样先复制原序列并排序，对于每个查询，统计前 $k$ 大元素的数量，再遍历原序列选取元素，最后输出指定位置的元素。

#### elbissoPtImaerD 的代码
```cpp
const int N=2e5+3;
int n,m;
struct wt{int x,y;}a[N],b[N];
void Solve()
{
    rd(n);
    for(re int i=1;i<=n;++i) rd(a[i].x),a[i].y=i;
    std::sort(a+1,a+n+1,[](re wt x,re wt y){return x.x==y.x?x.y<y.y:x.x>y.x;});
    rd(m);
    for(re int k,pos;m--;)
    {
        rd(k),rd(pos);
        for(re int i=1;i<=k;++i) b[i]=a[i];
        std::sort(b+1,b+k+1,[](re wt x,re wt y){return x.y<y.y;});
        prt(b[pos].x,'\n');
    }
    return;
}
```
**核心实现思想**：使用结构体记录元素值和下标，先按元素值从大到小排序，若值相同则按下标从小到大排序。对于每个查询，选取前 $k$ 个元素，再按原下标排序，最后输出指定位置的元素。

### 关键思路或技巧
- **贪心策略**：要使子序列和最大，取前 $k$ 大的元素。
- **排序技巧**：在排序时考虑元素原下标，当元素值相同时，按下标从小到大排序，保证字典序最小。
- **数据结构**：使用 `map` 记录元素数量，方便在原序列中选取元素。

### 拓展思路
同类型题目可能会改变数据范围或增加其他限制条件，例如加强版题目可能需要优化算法复杂度。可以使用优先队列、树状数组等数据结构来优化，或者采用离线查询的方式。

### 推荐题目
- [P1104 生日](https://www.luogu.com.cn/problem/P1104)：考察排序和结构体的使用。
- [P1093 奖学金](https://www.luogu.com.cn/problem/P1093)：涉及排序和贪心策略。
- [P1781 宇宙总统](https://www.luogu.com.cn/problem/P1781)：需要对字符串进行排序，同时考虑数值大小。

### 个人心得
- **Novelist_**：提到由于 $a$ 序列有点大，可以用映射，并且强调映射里不要用布尔类型，否则会出错。这是因为布尔类型只能记录元素是否存在，无法记录元素的数量，在处理相同元素时会出现问题。 

---
处理用时：78.77秒