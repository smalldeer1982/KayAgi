# 题目信息

# Prime Graph

## 题目描述

Every person likes prime numbers. Alice is a person, thus she also shares the love for them. Bob wanted to give her an affectionate gift but couldn't think of anything inventive. Hence, he will be giving her a graph. How original, Bob! Alice will surely be thrilled!

When building the graph, he needs four conditions to be satisfied:

- It must be a simple undirected graph, i.e. without multiple (parallel) edges and self-loops.
- The number of vertices must be exactly $ n $ — a number he selected. This number is not necessarily prime.
- The total number of edges must be prime.
- The degree (i.e. the number of edges connected to the vertex) of each vertex must be prime.

Below is an example for $ n = 4 $ . The first graph (left one) is invalid as the degree of vertex $ 2 $ (and $ 4 $ ) equals to $ 1 $ , which is not prime. The second graph (middle one) is invalid as the total number of edges is $ 4 $ , which is not a prime number. The third graph (right one) is a valid answer for $ n = 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1178D/3f451a0a015e85e0d9b919833cd5a0b4f7edb60b.png)Note that the graph can be disconnected.

Please help Bob to find any such graph!

## 说明/提示

The first example was described in the statement.

In the second example, the degrees of vertices are $ [7, 5, 2, 2, 3, 2, 2, 3] $ . Each of these numbers is prime. Additionally, the number of edges, $ 13 $ , is also a prime number, hence both conditions are satisfied.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1178D/44a2f5b9baacda9bf16e12d85f0a2a6d19c2b3cb.png)

## 样例 #1

### 输入

```
4
```

### 输出

```
5
1 2
1 3
2 3
2 4
3 4```

## 样例 #2

### 输入

```
8
```

### 输出

```
13
1 2
1 3
2 3
1 4
2 4
1 5
2 5
1 6
2 6
1 7
1 8
5 8
7 8
```

# AI分析结果

### 题目内容翻译
# 质数图

## 题目描述
每个人都喜欢质数。爱丽丝也是人，所以她也喜欢质数。鲍勃想送她一份深情的礼物，但想不出有创意的东西。因此，他将送她一个图。多么有创意啊，鲍勃！爱丽丝肯定会很激动！

在构建图时，他需要满足四个条件：
- 它必须是一个简单的无向图，即没有多重（平行）边和自环。
- 顶点的数量必须恰好为 $n$ —— 这是他选择的一个数字。这个数字不一定是质数。
- 边的总数必须是质数。
- 每个顶点的度数（即连接到该顶点的边的数量）必须是质数。

以下是 $n = 4$ 的一个例子。第一个图（左边的）是无效的，因为顶点 $2$（和 $4$）的度数等于 $1$，而 $1$ 不是质数。第二个图（中间的）是无效的，因为边的总数是 $4$，不是质数。第三个图（右边的）是 $n = 4$ 的有效答案。

![示例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1178D/3f451a0a015e85e0d9b919833cd5a0b4f7edb60b.png)

请注意，该图可以是不连通的。

请帮助鲍勃找到任何这样的图！

## 说明/提示
第一个样例在题目描述中已经给出。

在第二个样例中，顶点的度数为 $[7, 5, 2, 2, 3, 2, 2, 3]$。这些数字都是质数。此外，边的数量 $13$ 也是质数，因此两个条件都满足。

![第二个样例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1178D/44a2f5b9baacda9bf16e12d85f0a2a6d19c2b3cb.png)

## 样例 #1
### 输入
```
4
```
### 输出
```
5
1 2
1 3
2 3
2 4
3 4
```

## 样例 #2
### 输入
```
8
```
### 输出
```
13
1 2
1 3
2 3
1 4
2 4
1 5
2 5
1 6
2 6
1 7
1 8
5 8
7 8
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先构造一个环，使每个点的度数为 2（2 是质数），然后根据边数不是质数的情况进行加边操作，保证边数和点的度数都为质数。

- **思路对比**：大部分题解都是基于贪心策略，通过加边来满足边数为质数的条件。部分题解使用了素数筛来判断素数，还有的题解直接暴力判断素数。
- **算法要点**：先构建环，再通过加边使边数达到最近的质数，加边时保证点的度数仍为质数（通常是 2 变为 3）。
- **解决难点**：主要难点在于如何在加边过程中保证边数和点的度数都为质数，以及如何高效地找到满足条件的边数。

### 所选题解
- **max0810（5星）**
  - **关键亮点**：思路清晰，代码简洁，直接通过暴力判断素数和简单的加边操作实现。
  - **个人心得**：无
- **zhangzirui66（4星）**
  - **关键亮点**：思路与 max0810 类似，通过向量存储边，代码可读性高。
  - **个人心得**：随机跳到的题，做完发现解法和第一篇的思路一模一样，有点激动。
- **封禁用户（4星）**
  - **关键亮点**：思路简洁，代码实现简单，直接暴力判断素数。
  - **个人心得**：无

### 重点代码
#### max0810
```cpp
bool f(int x)
{
    for(int i = 2;i*i <= x;i++)
        if(x%i==0)return 0;
    return 1;
}
int main()
{
    cin >> n;m = n;
    while(!f(m))m++;
    cout << m << endl;
    for(int i = 1;i <= n;i++)printf("%d %d\n",i,i%n+1);
    for(int i = 1;i <= m-n;i++)printf("%d %d\n",i,i+n/2);
    return 0;
}
```
**核心实现思想**：先找到比 $n$ 大的最小质数 $m$，然后输出 $m$ 条边，先输出构成环的 $n$ 条边，再输出额外的 $m - n$ 条边。

#### zhangzirui66
```cpp
bool prime(int x){
    if(x <= 1) return 0;
    for(int i = 2; i * i <= x; i ++) if(x % i == 0){
        return 0;
    }
    return 1;
}
int main(){
    cin >> n;
    if(n <= 2){
        cout << -1;
        return 0;
    }
    for(int i = 1; i <= n; i ++) g.push_back({i, i % n + 1});
    while(!prime(g.size())){
        g.push_back({now, now + n / 2});
        now ++;
    }
    cout << g.size() << "\n";
    for(int i = 0; i < g.size(); i ++) cout << g[i].u << " " << g[i].v << "\n";
    return 0;
}
```
**核心实现思想**：先将图构造成环，存储在向量 $g$ 中，然后不断加边直到边数为质数，最后输出边数和所有边。

#### 封禁用户
```c++
bool ck(int x){
    for(int i=2;i*i<=x;i++) if(x%i==0) return 0;
    return 1;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    while(!ck(s+n)) s++;
    cout<<n+s<<'\n';
    for(int i=1;i<=n;i++) cout<<i<<' '<<((i+1>n)?(i+1-n):(i+1))<<'\n';
    for(int i=1;i<=s;i++) cout<<i<<' '<<((i+n/2>n)?(i+n/2-n):(i+n/2))<<'\n';
    return 0;
}
```
**核心实现思想**：先找到需要额外加的边数 $s$，使边数为质数，然后输出构成环的 $n$ 条边和额外的 $s$ 条边。

### 最优关键思路或技巧
- 先构造一个环，使每个点的度数为 2，满足点的度数为质数的条件。
- 利用素数的密集性，通过加边使边数达到最近的质数，加边时选择合适的点对，保证点的度数仍为质数。

### 拓展思路
同类型题或类似算法套路：
- 其他图的构造问题，可能需要满足不同的条件，如连通性、边权限制等。
- 数论相关的构造问题，需要结合数的性质进行构造。

### 推荐题目
- [P1217 [USACO1.5] 回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
- [P1075 [NOIP2012 普及组] 质因数分解](https://www.luogu.com.cn/problem/P1075)
- [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)

### 个人心得总结
zhangzirui66 随机跳到该题，做完发现解法和第一篇思路一样而感到激动，说明在解题过程中可能会遇到相似的思路，这也体现了算法题的规律性。 

---
处理用时：56.33秒