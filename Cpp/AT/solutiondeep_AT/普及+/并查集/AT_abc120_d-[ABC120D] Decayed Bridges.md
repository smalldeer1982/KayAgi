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

### 题目内容重写

#### [ABC120D] Decayed Bridges

**题目描述**

有 $N$ 个岛和 $M$ 座桥。

第 $i$ 座桥连接了岛 $A_i$ 和岛 $B_i$，并且可以双向通行。

最初，任意两个岛之间都可以通过若干座桥互相到达。

调查发现，由于老化，这些桥将按照从第 $1$ 座到第 $M$ 座的顺序依次崩塌。

定义“不便度”为“无法通过若干座桥互相到达的岛对 $(a, b)$（$a < b$）的数量”。

对于每个 $i$（$1 \leq i \leq M$），请输出第 $i$ 座桥崩塌后的不便度。

**说明/提示**

**约束条件**

- 输入均为整数。
- $2 \leq N \leq 10^5$
- $1 \leq M \leq 10^5$
- $1 \leq A_i < B_i \leq N$
- $(A_i, B_i)$ 的组合均不相同。
- 初始状态的不便度为 $0$。

**样例解释 1**

例如，当第 $1$ 到第 $3$ 座桥崩塌时，岛对 $(1, 2)$、$(1, 3)$、$(2, 4)$、$(3, 4)$ 将无法互相到达，因此不便度为 $4$。

**样例 #1**

**输入**

```
4 5

1 2

3 4

1 3

2 3

1 4
```

**输出**

```
0

0

4

5

6
```

**样例 #2**

**输入**

```
6 5

2 3

1 2

5 6

3 4

4 5
```

**输出**

```
8

9

12

14

15
```

**样例 #3**

**输入**

```
2 1

1 2
```

**输出**

```
1
```

### 题解分析与结论

#### 综合分析与结论

本题的核心在于如何处理边的删除操作，并动态维护图的连通性。由于并查集（Disjoint Set Union, DSU）无法直接处理删除操作，因此大多数题解采用了“反向思维”，即从最后一条边开始逐步添加边，并利用并查集维护连通块的大小，从而计算出每次删除边后的不便度。

#### 关键思路与技巧

1. **反向思维**：将删除边的操作转化为添加边的操作，简化了问题的处理。
2. **并查集维护连通块大小**：通过并查集维护每个连通块的大小，方便计算每次添加边后新增的连通对数。
3. **预处理与倒序处理**：预处理所有边的信息，并倒序处理，逐步添加边并更新不便度。

#### 推荐题解

1. **作者：ElmPoplar**  
   **星级：★★★★★**  
   **关键亮点**：思路清晰，代码简洁，详细解释了反向思维和并查集的实现细节。  
   **代码核心思想**：倒序处理边，使用并查集维护连通块大小，计算每次添加边后新增的连通对数。

   ```cpp
   #include <bits/stdc++.h>
   using namespace std;
   const int N = 100005;
   int n, m, u[N], v[N], fa[N], Size[N];
   long long ans[N];

   int find(int x) {
       if (x != fa[x]) fa[x] = find(fa[x]);
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

2. **作者：HMZHMZHMZ**  
   **星级：★★★★☆**  
   **关键亮点**：代码结构清晰，使用了结构体存储边的信息，并详细解释了并查集的合并操作。  
   **代码核心思想**：倒序处理边，使用并查集维护连通块大小，计算每次添加边后新增的连通对数。

   ```cpp
   #include<bits/stdc++.h>
   #define ll long long
   using namespace std;
   const int N=1e5+10;
   struct node{
       ll from,to;
   }a[N];
   struct bcj{
       ll siz,fa;
   }f[N];
   ll n,m,cnt;
   ll ans[N],now;
   inline ll find(ll x){
       if(f[x].fa==x) return x;
       return f[x].fa=find(f[x].fa);
   }
   inline void add(ll x,ll y){
       now+=1ll*f[find(x)].siz*f[find(y)].siz;
       f[find(y)].siz+=f[find(x)].siz;
       f[find(x)].fa=find(y);
   }
   inline ll read(){
       ll s=0,f=0;
       char ch=getchar();
       while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
       while(ch<='9'&&ch>='0') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
       return f?-s:s;
   }
   int main(){
       n=read(),m=read();
       for(register ll i=1;i<=n;++i) f[i]=(bcj){1,i};
       for(register ll i=m;i>=1;--i) a[i].from=read(),a[i].to=read();
       for(register ll i=1;i<=m;++i){
           ans[i]=now;
           if(find(a[i].from)!=find(a[i].to)) add(a[i].from,a[i].to);
       }
       ll tot=n*(n-1)>>1;
       for(register ll i=m;i>=1;--i) printf("%lld\n",tot-ans[i]);
       return 0;
   }
   ```

3. **作者：徐晨轩✅**  
   **星级：★★★★☆**  
   **关键亮点**：代码简洁，使用了结构体存储边的信息，并详细解释了并查集的合并操作。  
   **代码核心思想**：倒序处理边，使用并查集维护连通块大小，计算每次添加边后新增的连通对数。

   ```cpp
   #include <stdio.h>
   int n,m,ff,ft,f[100001];
   long long ans[100001],size[100001];
   struct node
   {
       int from;
       int to;
   }ge[100001];
   int find(int x)
   {
       if(f[x]!=x)f[x]=find(f[x]);
       return f[x];
   }
   void merge(int x,int y)
   {
       int fx=find(x);
       int fy=find(y);
       f[fy]=fx;
       size[fx]+=size[fy];
   }
   int main()
   {
       scanf("%d%d",&n,&m);
       for(int i=1;i<=n;i++)
           f[i]=i,size[i]=1;
       for(int i=1;i<=m;i++)
           scanf("%d%d",&ge[i].from,&ge[i].to);
       ans[m]=1LL*n*(n-1)/2;
       for(int i=m;i>=1;i--)
       {
           ff=find(ge[i].from),ft=find(ge[i].to);
           if(ff==ft)ans[i-1]=ans[i];
           else ans[i-1]=ans[i]-size[ff]*size[ft],merge(ff,ft);
       }
       for(int i=1;i<=m;i++)
           printf("%lld\n",ans[i]);
       return 0;
   }
   ```

### 推荐题目

1. [P1197 [JSOI2008]星球大战](https://www.luogu.com.cn/problem/P1197)
2. [P6121 [USACO16OPEN]248](https://www.luogu.com.cn/problem/P6121)
3. [P8359 [NOI2022] 挑战](https://www.luogu.com.cn/problem/P8359)

### 个人心得

- **反向思维**：在处理删除操作时，反向思维往往能简化问题，尤其是在并查集等数据结构无法直接处理删除操作时。
- **并查集维护连通块大小**：通过维护连通块的大小，可以方便地计算每次操作后新增的连通对数。
- **预处理与倒序处理**：预处理所有操作信息并倒序处理，可以避免动态删除操作的复杂性。

---
处理用时：68.67秒