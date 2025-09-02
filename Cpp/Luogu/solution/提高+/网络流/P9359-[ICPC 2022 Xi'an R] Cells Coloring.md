# [ICPC 2022 Xi'an R] Cells Coloring

## 题目描述

给定一个 $n\times m$ 的网格。一些格子是障碍，其它格子是空的。选择一个非负整数 $k$，并用 $k + 1$ 种颜色 $0, 1, \ldots, k$ 给空格子染色。不能有同一行或同一列的两个格子被染成了相同的 **非零** 颜色。

给定两个非负整数 $c, d$。对于一组染色方案，定义 $z$ 表示染成颜色 $0$ 的格子数量，则该方案的代价为 $ck + dz$。

求出最小代价。

$1\leq n, m \leq 250$，$0\leq c, d\leq 10 ^ 9$。

## 样例 #1

### 输入

```
3 4 2 1
.***
*..*
**..
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 4 1 2
.***
*..*
**..
```

### 输出

```
2```

# 题解

## 作者：xiezheyuan (赞：4)

## 思路

首先考虑当 $k$ 给定的时候如何求出 $z$。

先来考虑一个 $k=1$ 的情况，则转换为经典的二分图最大匹配问题。我们对行建立一个点，对列建立一个点，不为障碍的格子建立一条边，去做一遍二分图最大匹配即可。

考虑如何扩展到 $k\neq 1$ 的情况，我们只需要把源点到行，汇点到列的这些边容量改为 $k$ 即可。

然后我们可以枚举 $k$ 去修改这些边的容量，跑一遍最大流。但是我被卡了。所以考虑其他的做法。

观察答案形式 $ck+dz$，容易发现 $z$ 随着 $k$ 的增大而不增。于是 $ck+dz$ 是一个单峰函数。在上面跑一个整数三分就可以求出答案。

时间复杂度 $O(n^2\log n)$。默认 $n,m$ 同阶。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 255 * 255, M = 300 * 300 + 5;
struct edge{
    int nxt, to, cap, w;
} g[M<<1];
int head[N],ec = 1;
void add(int u,int v,int cap){
    g[++ec].nxt=head[u];
    g[ec].to=v;g[ec].cap = cap; g[ec].w = cap;
    head[u] = ec;
}

int S,T,dep[N],cur[N];
int n,m;

bool bfs(){
    queue<int> q;
    fill(dep + 1, dep + n + m + 3, 0);
    q.push(S);dep[S] = 1;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i=head[u];i;i=g[i].nxt){
            int v = g[i].to;
            if(g[i].cap > 0 && !dep[v]) dep[v] = dep[u] + 1, q.push(v);
        }
    }
    return dep[T];
}

int dfs(int u,int f){
    if((u == T) || !f) return f;
    int ret = 0;
    for(int &i=cur[u];i;i=g[i].nxt){
        int v=g[i].to, d = 0;
        if((dep[v] == dep[u] + 1) && (d = dfs(v, min(f - ret, g[i].cap)))){
            ret += d;
            g[i].cap -= d;
            g[i ^ 1].cap += d;
            if(ret == f) return f;
        }
    }
    return ret;
}

int dinic(){
    int mxflow = 0;
    while(bfs()){
        for(int i=0;i<=(n + m + 2);i++) cur[i] = head[i];
        int x = 0;
        while((x = dfs(S, INT_MAX))) mxflow += x;
    }
    return mxflow;
}

int c, d, blank;
bool mp[255][255];
vector<int> ndchg;

int f(int k){
    for(int i=0;i<=ec;i++) g[i].cap = g[i].w;
    for(int i : ndchg) g[i].cap = k;
    int z = blank - dinic();
    return c * k + d * z;
}


signed main(){
    cin >> n >> m >> c >> d;
    S = n + m + 2, T = n + m + 1;
    for(int i=1;i<=n;i++){
        string s; cin >> s;
        for(int j=1;j<=m;j++) mp[i][j] = s[j - 1] == '.';
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mp[i][j]) add(i, j + n, 1), add(j + n, i, 0), blank++;
        }
    }
    for(int i=1;i<=n;i++){
        add(S, i, 1), add(i, S, 0);
        ndchg.push_back(ec ^ 1);
    }
    for(int i=1;i<=m;i++){
        add(i + n, T, 1), add(T, i + n, 0);
        ndchg.push_back(ec ^ 1);
    }
    int L = 0, R = max(n, m);
    while(L < R){
        int mid = (L + R) >> 1;
        int lmid = L + (R - L) / 3;
        int rmid = R - (R - L) / 3;
        if(f(lmid) <= f(rmid)) R = rmid - 1;
        else L = lmid + 1;
    }
    cout << f(L);
    return 0;
}

// Written by xiezheyuan
```

---

