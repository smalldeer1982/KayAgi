# 题目信息

# New Year Permutation

## 题目描述

## 题意翻译

用户 ainta 有一个排列 $p_1,p_2,...,p_n$ 。新年到了，他希望把他的排列变得尽可能漂亮。

当且仅当存在整数 $k$（$1 \le k \le n$）使 $a_1=b_1,a_2=b_2,\ldots,a_{k-1}=b_{k-1}$ 和 $a_k<b_k$ 都成立，排列 $a_1,a_2,...,a_n$ 比  $b_1,b_2,...,b_n$ 更漂亮。

排列 $p$ 非常敏感，只可以通过交换两个不同的元素来修改它。但是交换两个不同的元素比你想象得要难。给出一个 $n\times n$ 的二进制矩阵 $A$ ，当且仅当 $A_{i,j}=1$ 时，用户 ainta 可以交换两个元素 $p_i,p_j (1<=i,j<=n,i\neq j)$ 的值。

给定排列 $p$ 和矩阵 $A$ ，用户 ainta 想知道他能得到的最漂亮的排列。

## 样例 #1

### 输入

```
7
5 2 4 3 6 7 1
0001001
0000000
0000010
1000001
0000000
0010000
1001000
```

### 输出

```
1 2 4 3 6 7 5
```

## 样例 #2

### 输入

```
5
4 2 1 5 3
00100
00011
10010
01101
01010
```

### 输出

```
1 2 3 4 5
```

# AI分析结果

### 题目内容
# 新年排列

## 题目描述

## 题意翻译
用户 ainta 有一个排列 $p_1,p_2,\ldots,p_n$ 。新年到了，他希望把他的排列变得尽可能漂亮。

当且仅当存在整数 $k$（$1 \leq k \leq n$）使 $a_1 = b_1,a_2 = b_2,\ldots,a_{k - 1} = b_{k - 1}$ 和 $a_k < b_k$ 都成立，排列 $a_1,a_2,\ldots,a_n$ 比排列 $b_1,b_2,\ldots,b_n$ 更漂亮。

排列 $p$ 非常敏感，只可以通过交换两个不同的元素来修改它。但是交换两个不同的元素比你想象得要难。给出一个 $n\times n$ 的二进制矩阵 $A$ ，当且仅当 $A_{i,j}=1$ 时，用户 ainta 可以交换两个元素 $p_i,p_j (1\leq i,j\leq n,i\neq j)$ 的值。

给定排列 $p$ 和矩阵 $A$ ，用户 ainta 想知道他能得到的最漂亮的排列。

## 样例 #1
### 输入
```
7
5 2 4 3 6 7 1
0001001
0000000
0000010
1000001
0000000
0010000
1001000
```
### 输出
```
1 2 4 3 6 7 5
```

## 样例 #2
### 输入
```
5
4 2 1 5 3
00100
00011
10010
01101
01010
```
### 输出
```
1 2 3 4 5
```

### 算法分类
贪心

### 题解综合分析与结论
该题主要目标是根据给定的交换规则将排列变为字典序最小。多数题解使用Floyd传递闭包来处理交换关系，也有题解采用并查集维护连通性。各题解思路和实现方式较为相似，差异主要在具体算法选择和代码细节上。难点在于理解如何通过给定的矩阵确定元素间的可交换关系，并据此构造出字典序最小的排列。

### 所选的题解
#### 作者：zhanghzqwq (5星)
- **关键亮点**：思路清晰，代码简洁明了，直接使用Floyd传递闭包处理交换关系，随后通过简单贪心策略寻找字典序最小的排列。
- **个人心得**：两分钟写完传递闭包，但在求字典序最小时调试花费较多时间。
```cpp
#include<iostream>
using namespace std;
const int MAXN = 305;
int p[MAXN];
int adj[MAXN][MAXN];
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char ch;
            cin >> ch;
            adj[i][j] = ch - '0';
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        int index = i;
        for (int j = i + 1; j <= n; j++) {
            if (adj[i][j]) {
                if (p[j] < p[index]) {
                    index = j;
                }
            }
        }
        int t = p[i];
        p[i] = p[index];
        p[index] = t;
    }
    for (int i = 1; i <= n; i++) {
        cout << p[i] << " ";
    }
    cout << endl;
    return 0;
}
```
核心代码实现思想：先读入排列和矩阵，通过Floyd传递闭包更新邻接矩阵表示所有可交换关系，然后从前往后遍历排列，每次在可交换元素中找到最小的交换到当前位置。

#### 作者：SymphonyOfEuler (4星)
- **关键亮点**：同样使用Floyd传递闭包解决问题，代码结构清晰，对Floyd算法有形象描述，并对思路进行了详细分步说明。
```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
int n, d[305][305], w[305][305];
int p[305];
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            char qaq;
            cin >> qaq;
            d[i][j] = qaq - '0';
        }
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                d[i][j] = d[i][j] || (d[i][k] && d[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        int dex = i;
        for (int j = i + 1; j <= n; ++j) {
            if (d[i][j]) {
                if (p[j] < p[dex]) dex = j;
            }
        }
        int t = p[i];
        p[i] = p[dex];
        p[dex] = t;
    }
    for (int i = 1; i <= n; ++i) {
        cout << p[i] << " ";
    }
    return 0;
}
```
核心代码实现思想：读入排列和矩阵后，利用Floyd传递闭包确定元素间所有可交换关系，之后通过贪心策略，每次在可交换元素中找最小元素交换到当前位置以得到字典序最小排列。

#### 作者：叶枫 (4星)
- **关键亮点**：采用并查集维护连通性，从左往右从连通块中每次取出最小的，提供了与Floyd不同的解题视角。
```cpp
#include<bits/stdc++.h>
#define inf 1000000000
#define int long long 
using namespace std;
int read() {
    ll x = 0; char ch = getchar();
    while (ch < '0' || ch > '9')ch = getchar();
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x;
}
int n;
int a[305], fa[305];
char ch[305];
inline int find(int x) {
    return x == fa[x]? x : fa[x] = find(fa[x]);
}
signed main() {
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= n; i++) {
        scanf("%s", ch + 1);
        for (int j = 1; j <= n; j++)
            if (ch[j] == '1') {
                int p = find(i), q = find(j);
                if (p!= q) fa[p] = q;
            }
    }
    for (int i = 1; i <= n; i++) {
        int t = i;
        for (int j = i + 1; j <= n; j++)
            if (find(j) == find(i) && a[j] < a[t]) t = j;
        swap(a[i], a[t]);
    }
    for (int i = 1; i <= n; i++) printf("%d ", a[i]);
    return 0;
}
```
核心代码实现思想：读入排列后初始化并查集，根据矩阵中1的位置合并连通块，之后从前往后遍历排列，每次在同一连通块内找到最小元素交换到当前位置。

### 最优关键思路或技巧
- **利用Floyd传递闭包或并查集**：Floyd传递闭包可以快速确定所有元素间的可交换关系；并查集则以另一种方式维护元素的连通性，从而确定可交换元素集合。
- **贪心策略**：在确定可交换关系后，从前往后遍历排列，每次选择可交换元素中的最小元素交换到当前位置，以构造字典序最小的排列。

### 同类型题或类似算法套路拓展
同类型题目通常围绕排列、交换规则与目标优化（如字典序最小、最大等）展开。类似算法套路包括先确定元素间的关系（通过图论算法如Floyd、并查集等），再基于目标进行贪心选择。

### 洛谷相似题目推荐
- [P1192 台阶问题](https://www.luogu.com.cn/problem/P1192)：涉及递推和贪心思想，与本题类似在于根据一定规则对元素进行操作以达到某种最优。
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)：同样需要通过分析条件确定元素间关系，利用贪心策略解决问题，与本题思路有相似之处。
- [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)：运用贪心策略，与本题在通过特定规则优化结果上有相似性。 

---
处理用时：78.30秒