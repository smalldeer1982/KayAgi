# 题目信息

# [ABC359F] Tree Degree Optimization

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc359/tasks/abc359_f

整数列 $ A=(A_1,\ldots,A_N) $ が与えられます。 $ N $ 頂点の木 $ T $ に対して、 $ f(T) $ を以下で定めます。

- $ T $ の頂点 $ i $ の次数を $ d_i $ とする。このとき、$ f(T)=\sum_{i=1}^N\ {d_i}^2\ A_i $ とする。
 
$ f(T) $ として考えられる最小値を求めてください。

なお、制約下において答えが $ 2^{63} $ 未満となることは保証されています。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ \leq\ 10^9 $
- 入力される数値は全て整数
 
### Sample Explanation 1

頂点 $ 1 $ と頂点 $ 2 $ を結ぶ辺、頂点 $ 2 $ と頂点 $ 4 $ を結ぶ辺、頂点 $ 4 $ と頂点 $ 3 $ を結ぶ辺からなるような木 $ T $ を考えます。 このとき $ f(T)\ =\ 1^2\times\ 3\ +\ 2^2\times\ 2+1^2\times\ 5\ +2^2\times\ 2\ =\ 24 $ です。これが $ f(T) $ の最小値であることが証明できます。

## 样例 #1

### 输入

```
4

3 2 5 2```

### 输出

```
24```

## 样例 #2

### 输入

```
3

4 3 2```

### 输出

```
15```

## 样例 #3

### 输入

```
7

10 5 10 2 10 13 15```

### 输出

```
128```

# AI分析结果

### 题目内容重写

#### [ABC359F] 树度优化

**题目描述**

给定一个整数序列 $A=(A_1,\ldots,A_N)$。对于一棵有 $N$ 个顶点的树 $T$，定义 $f(T)$ 如下：

- 设 $T$ 的顶点 $i$ 的度数为 $d_i$，则 $f(T)=\sum_{i=1}^N {d_i}^2 A_i$。

求 $f(T)$ 的最小可能值。

**说明/提示**

**约束条件**

- $2\leq N\leq 2\times 10^5$
- $1\leq A_i \leq 10^9$
- 输入的所有数值均为整数

**样例解释1**

考虑一棵树 $T$，其边为顶点 $1$ 和顶点 $2$ 之间的边，顶点 $2$ 和顶点 $4$ 之间的边，以及顶点 $4$ 和顶点 $3$ 之间的边。此时 $f(T) = 1^2\times 3 + 2^2\times 2 + 1^2\times 5 + 2^2\times 2 = 24$。可以证明这是 $f(T)$ 的最小值。

**样例 #1**

输入：
```
4
3 2 5 2
```
输出：
```
24
```

**样例 #2**

输入：
```
3
4 3 2
```
输出：
```
15
```

**样例 #3**

输入：
```
7
10 5 10 2 10 13 15
```
输出：
```
128
```

### 题解综合分析与结论

本题的核心问题是如何在满足树的度数约束条件下，最小化 $\sum_{i=1}^N {d_i}^2 A_i$。由于树的性质，每个顶点的度数至少为1，且所有度数的总和为 $2(N-1)$。因此，我们需要在初始每个顶点度数为1的基础上，分配剩余的 $N-2$ 个度数，使得目标函数最小。

大多数题解采用了贪心策略，通过优先队列（最小堆）来动态维护每个顶点增加一度对目标函数的贡献，并每次选择贡献最小的顶点进行度数增加。这种方法的时间复杂度为 $O(N \log N)$，能够高效地解决问题。

### 所选高星题解

#### 题解1：作者：Heldivis (赞：5)

**星级：5星**

**关键亮点：**
- 思路清晰，直接使用贪心策略，通过优先队列维护每个顶点增加一度的贡献。
- 代码简洁，可读性强，直接实现了贪心算法的核心逻辑。

**代码实现：**
```cpp
struct Node { int d, a; };
bool operator<(Node x, Node y) {return (x.d * 2 + 1) * x.a > (y.d * 2 + 1) * y.a;}
priority_queue<Node> q;
int main() {
  int n = read(); long long res = 0;
  for (int i = 1; i <= n; i++) q.push({1, read()});
  for (int t = 1; t <= n - 2; t++) {
    Node x = q.top();
    q.pop();
    x.d++;
    q.push(x);
  }
  while (q.size()) {
    res += q.top().d * q.top().d * q.top().a;
    q.pop();
  }
  printf("%lld\n", res);
  return 0;
}
```

#### 题解2：作者：kkxacj (赞：2)

**星级：4星**

**关键亮点：**
- 同样采用贪心策略，通过优先队列维护每个顶点增加一度的贡献。
- 代码实现较为详细，解释了每一步的操作，适合初学者理解。

**代码实现：**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[300010],f[300010],l,l1,r1,r,v[300010],ans;
priority_queue<pair<int,int> >p,p1; 
int find(int x) {
  if(f[x] == x) return x;
  return f[x] = find(f[x]);
}
signed main() {
  read(n);
  for(int i = 1; i <= n; i++) v[i] = 1, read(a[i]), ans += a[i], p.push(make_pair(-a[i]*(2*v[i]+1), i)), v[i]++;
  for(int i = 1; i <= (n-1)*2-n; i++) {
    l = -p.top().first, r = p.top().second;
    p.pop();
    ans += l;
    p.push(make_pair(-a[r]*(2*v[r]+1), r));
    v[r]++; 
  }
  print(ans);
  flush();
  return 0;
}
```

#### 题解3：作者：_Weslie_ (赞：1)

**星级：4星**

**关键亮点：**
- 通过Prufer序列的性质，解释了树度数的分配问题，进一步验证了贪心策略的正确性。
- 代码实现简洁，逻辑清晰，适合有一定基础的读者。

**代码实现：**
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<pair<int,int> >q;
int n;
int a[300005];
int ans;
signed main() {
  cin >> n;
  for(int i = 1; i <= n; i++) cin >> a[i];
  for(int i = 1; i <= n; i++) ans += a[i];
  for(int i = 1; i <= n; i++) q.push({-3*a[i], i});
  for(int i = 1; i <= n - 2; i++) {
    pair<int,int >t = q.top(); q.pop();
    ans -= t.first;
    q.push({(t.first - 2*a[t.second]), t.second});
  }
  cout << ans;
  return 0;
}
```

### 最优关键思路与技巧

1. **贪心策略**：通过优先队列动态维护每个顶点增加一度对目标函数的贡献，每次选择贡献最小的顶点进行度数增加。
2. **优先队列的使用**：利用最小堆（优先队列）来高效地选择每次增加度数的顶点，确保每次操作都是最优的。
3. **Prufer序列的性质**：通过Prufer序列的性质，验证了树度数的分配问题，进一步保证了贪心策略的正确性。

### 可拓展之处

- **类似问题**：类似的问题可以扩展到其他类型的图或网络流问题，其中需要优化某些与度数相关的目标函数。
- **算法套路**：贪心算法结合优先队列的套路可以应用于其他需要动态选择最优解的问题，如任务调度、资源分配等。

### 推荐题目

1. [P7840](https://www.luogu.com.cn/problem/P7840) - 双倍经验题，考察树度数的优化问题。
2. [P1231](https://www.luogu.com.cn/problem/P1231) - 考察图的度数分配问题，适合进一步练习贪心策略。
3. [P1967](https://www.luogu.com.cn/problem/P1967) - 考察树的重构问题，适合深入理解树的性质和度数分配。

---
处理用时：55.79秒