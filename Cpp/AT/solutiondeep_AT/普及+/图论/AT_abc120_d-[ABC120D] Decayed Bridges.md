# 题目信息

# [ABC120D] Decayed Bridges

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc120/tasks/abc120_d

$ N $ 個の島と $ M $ 本の橋があります。

$ i $ 番目の橋は $ A_i $ 番目の島と $ B_i $ 番目の島を繋いでおり、双方向に行き来可能です。

はじめ、どの $ 2 $ つの島についてもいくつかの橋を渡って互いに行き来できます。

調査の結果、老朽化のためこれら $ M $ 本の橋は $ 1 $ 番目の橋から順に全て崩落することがわかりました。

「いくつかの橋を渡って互いに行き来できなくなった $ 2 $ つの島の組 $ (a,\ b) $ ($ a\ <\ b $) の数」を**不便さ**と呼ぶことにします。

各 $ i $ $ (1\ \leq\ i\ \leq\ M) $ について、$ i $ 番目の橋が崩落した直後の不便さを求めてください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ <\ B_i\ \leq\ N $
- $ (A_i,\ B_i) $ の組は全て異なる。
- 初期状態における不便さは $ 0 $ である。

### Sample Explanation 1

例えば、$ 1 $ から $ 3 $ 番目の橋が崩落したとき、$ (1,\ 2),\ (1,\ 3),\ (2,\ 4),\ (3,\ 4) $ の島の組について行き来できなくなるので不便さは $ 4 $ です。

## 样例 #1

### 输入

```
4 5

1 2

3 4

1 3

2 3

1 4```

### 输出

```
0

0

4

5

6```

## 样例 #2

### 输入

```
6 5

2 3

1 2

5 6

3 4

4 5```

### 输出

```
8

9

12

14

15```

## 样例 #3

### 输入

```
2 1

1 2```

### 输出

```
1```

# AI分析结果

### 题目翻译
有 $N$ 个岛屿和 $M$ 座桥。

第 $i$ 座桥连接着第 $A_i$ 个岛屿和第 $B_i$ 个岛屿，并且可以双向通行。

起初，任意两个岛屿之间都可以通过若干座桥相互到达。

经过调查发现，由于老化，这 $M$ 座桥将按从第 1 座桥开始的顺序全部坍塌。

我们将“无法通过若干座桥相互到达的两个岛屿的组合 $(a, b)$（$a < b$）的数量”称为**不便度**。

对于每个 $i$（$1 \leq i \leq M$），请求出第 $i$ 座桥坍塌后立即的不便度。

### 综合分析与结论
- **思路对比**：所有题解都采用了逆向思维，将删边问题转化为加边问题，利用并查集维护连通块信息。
- **算法要点**：
    - 初始化并查集，每个点的父节点为自身，连通块大小为 1。
    - 倒序处理边，判断边的两个端点是否属于同一连通块。
    - 若不属于同一连通块，合并连通块并更新答案；若属于同一连通块，答案不变。
- **解决难点**：并查集本身不便于进行删边操作，通过逆向思维将删边转化为加边，利用并查集的合并操作解决问题。

### 所选题解
- **作者：ElmPoplar（5星）**
    - **关键亮点**：思路清晰，代码注释详细，对注意事项有明确提示。
    - **个人心得**：强调“一场 OI 一场空，不开 long long 见祖宗”，提醒注意答案可能超出 int 范围。
    - **核心代码**：
```c++
int find(int x) {
    if (x!= fa[x]) fa[x] = find(fa[x]);
    return fa[x];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i ++)
        scanf("%d%d", &u[i], &v[i]);

    for (int i = 1; i <= n; i ++)
        Size[i] = 1;
    for (int i = 1; i <= n; i ++)
        fa[i] = i;

    ans[m] = (long long)n * (n - 1) / 2;
    for (int i = m; i > 1; i --) {
        int x = find(u[i]), y = find(v[i]);
        if (x == y)
            ans[i - 1] = ans[i];
        else {
            ans[i - 1] = ans[i] - (long long)Size[x] * Size[y];
            fa[y] = x;
            Size[x] += Size[y], Size[y] = 0;
        }
    }

    for (int i = 1; i <= m; i ++)
        printf("%lld\n", ans[i]);

    return 0;
}
```
- **作者：徐晨轩✅（4星）**
    - **关键亮点**：思路和代码简洁明了，对操作的解释清晰。
    - **核心代码**：
```cpp
int find(int x) {
    if(f[x]!=x)f[x]=find(f[x]);
    return f[x];
}
void merge(int x,int y) {
    int fx=find(x);
    int fy=find(y);
    f[fx]=fy;
    size[fy]+=size[fx];
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        f[i]=i,size[i]=1;
    for(int i=1;i<=m;i++)
        scanf("%d%d",&ge[i].from,&ge[i].to);
    ans[m]=1LL*n*(n-1)/2;
    for(int i=m;i>=1;i--) {
        ff=find(ge[i].from),ft=find(ge[i].to);
        if(ff==ft)ans[i-1]=ans[i];
        else ans[i-1]=ans[i]-size[ff]*size[ft],merge(ff,ft);
    }
    for(int i=1;i<=m;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
```
- **作者：hxhhxh（4星）**
    - **关键亮点**：代码简洁，思路清晰，采用带权并查集解决问题。
    - **核心代码**：
```cpp
int dfs(int x) {
    if(f[x]==x) return x;
    return f[x]=dfs(f[x]);
}
signed main() {
    cin>>n>>m;
    int an=0;
    for(int i=1;i<=n;i++) f[i]=i,siz[i]=1;
    for(int i=1;i<=m;i++) scanf("%lld %lld",&ea[i],&eb[i]);
    for(int i=m;i>=1;i--) {
        ans[i]=an;
        if(dfs(ea[i])!=dfs(eb[i])) {
            int sa=siz[dfs(ea[i])],sb=siz[dfs(eb[i])];
            an+=sa*sb;
            siz[dfs(eb[i])]+=sa;
            f[dfs(ea[i])]=dfs(eb[i]);
        }
    }
    for(int i=1;i<=m;i++) printf("%lld\n",n*(n-1)/2-ans[i]);
    return 0;
}
```

### 最优关键思路或技巧
- **逆向思维**：将删边问题转化为加边问题，利用并查集的合并操作解决问题。
- **带权并查集**：使用 `size` 数组维护连通块的大小，方便计算合并连通块时减少的不连通点对数量。

### 拓展思路
同类型题或类似算法套路：
- 处理图的动态操作（如删点、删边、加点、加边）时，若正向操作困难，可考虑逆向操作。
- 利用并查集维护图的连通性，结合连通块大小等信息解决相关问题。

### 推荐题目
- [P1197 [JSOI2008]星球大战](https://www.luogu.com.cn/problem/P1197)
- [P8359 [SDOI2022] 小 N 的独立集](https://www.luogu.com.cn/problem/P8359)
- [P6121 [NEERC2013]Non-boring sequences](https://www.luogu.com.cn/problem/P6121)

### 个人心得总结
- ElmPoplar 提醒在 OI 中要注意答案可能超出 int 范围，记得开 long long。
- 紊莫提到自己在 `merge` 函数的操作上被坑，强调要注意将一个集合合并到另一个集合时的相加顺序。 

---
处理用时：36.31秒