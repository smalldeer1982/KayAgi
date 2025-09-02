# Min-Fund Prison (Easy)

## 题目描述

现给出一张由 $n$ 个点 $m=n-1$ 条边构成的树，其 $m$ 条边为 $(u_i, v_i)$ ( $1\leq i\leq m$ )，表示 $u_i,v_i$ 相连。

你可以以 $c$ 的成本在任意两个点 $x, y$ 之间连一条边。这个操作可以进行任意次，设你操作了 $k$ 次。

在连边操作之后，你必须删去一条割边，使得剩下的图恰由 $2$ 个连通块组成。设两个连通块的大小为 $x,y$ ，请问 $x^2+y^2+kc$ 的最小值为何？

## 样例 #1

### 输入

```
2
2 1 3
1 2
8 7 76
3 1
3 2
2 4
2 5
4 6
4 7
7 8```

### 输出

```
2
32```

# 题解

## 作者：Sparse_Table (赞：3)

[原题传送门](https://www.luogu.com.cn/problem/CF1970G1)

这题显然加边是没有用的，删边就相当于把树拆成一个点的子树和其余部分，题意就变成

> 求一个点子树和其余部分的平方和最小。

根据题意可知：当一个点的子树大小越趋近于 $\frac{n}{2}$ 时，答案越小。

证明：记一个点的子树有 $a$ 的点，其余部分 $(n - a)$ 个点，还有一个点的子树有 $b$ 的点，其余部分 $(n - b)$ 个点。$(|a - \frac{n}{2}| < |b - \frac{n}{2}|)$
$$
a ^ 2 + (n - a) ^ 2 = n ^ 2 - 2a(n - a)\\
b ^ 2 + (n - b) ^ 2 = n ^ 2 - 2b(n - b)\\
\because |a - \frac{n}{2}| < |b - \frac{n}{2}|\\
\therefore 2a(n - a) > 2b(n - b)\\
\therefore n ^ 2 - 2a(n - a) < n ^ 2 - 2b(n - b)\\
\therefore a ^ 2 + (n - a) ^ 2 < b ^ 2 + (n - b) ^ 2
$$

思路：跑一遍 dfs，求一个点的子树点的个数与 $\frac{n}{2}$ 最接近的点，进行计算。

有疑问欢迎私信，谢谢。

---

## 作者：conti123 (赞：1)

## CF1970G1 Min-Fund Prison (Easy)

G1 还是很简单的。

性质为原图是一棵树，注意到，如果我们加入了一条边，我们不可能删去它，那我们加入它干什么？显然没用。

所以题意变成了找一条边断掉，然后使两部分节点数 $x^2+y^2$ 最小。

那么考虑一遍 dfs 把每棵子树的大小求出来，然后对每个不是根的节点考虑是否断掉它和它父亲的边即可。

```cpp
void dfs(int u,int pa){
	sz[u]=1;
	for(int v:E[u]){
		if(v==pa)
			continue;
		dfs(v,u);
		ans=min(ans,(n-sz[v])*(n-sz[v])+sz[v]*sz[v]);
		sz[u]+=sz[v];
	}
}
int k;
void solve() {
	cin>>n>>m>>k;
	ans=1e18;
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		E[x].push_back(y);
		E[y].push_back(x);
	}
	dfs(1,0);
	cout<<ans<<"\n";
	for(int i=1;i<=n;i++)
		E[i].clear(),sz[i]=0;
}
```

---

## 作者：Alexandr (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1970G1)

## 解析

因为题目说明了是由 $n$ 个点 $m=n-1$ 条边构成的树，容易知道这个树是本身就是连通的，所以任意删除树边即可把这个树砍成两部分。同时我们花成本为 $c$ 的新连边，我们在最后删除一条边的时候是不可能删去我们新连的边的，因为这样就相当于不用连这条新边，也不可能把这个树分成两部分。所以我们最后删的那一条边只能是树边，也就是不需要任何的加边了。


现在的问题就转化成了

> 给你一个树，让你删掉一条树边后，这时整棵树被分成两部分，求这两部分结点数的平方和的最小值。

这个问题就很好解决了，求出每个结点 $i$ 的子树大小 $sze_i$，那么我们用 $n$ 减去 $sze_i$ 就是把结点 $i$ 连接上面的结点的边删除后的上部分的结点数，所以这两个部分的结点数分别 $sze_i$ 和 $n-sze_i$ 了。最后求一下平方和取最小值即可。

## code

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _antirep(i,a,b) for(int i=(a);i>=(b);--i)
#define In(x) freopen(x".in","r",stdin)
#define Out(x) freopen(x".out","w",stdout)
#define File(x) (In(x),Out(x)) 
using namespace std;
typedef long long LL;
typedef double db;
const int N=1e5+5;
int T;
int n,m,c;
LL sze[N];
vector<int>e[N]; 
void dfs(int u,int fa)
{
    sze[u]=1;
    for(int i=0;i<e[u].size();++i)
    {
        int v=e[u][i];
        if(v==fa) continue;
        dfs(v,u);
        sze[u]+=sze[v];//求出子树大小
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0); 
    cin>>T;
    while(T--)
    {
        cin>>n>>m>>c;
        _rep(i,1,n) e[i].clear();//多测清空
        _rep(i,1,m)
        {
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);//建树边
            e[v].push_back(u);
        }
        dfs(1,0);
        LL ans=1e17;
        _rep(i,1,n) 
          ans=min(ans,sze[i]*sze[i]+(n-sze[i])*(n-sze[i]));
        cout<<ans<<"\n";
    }
    return 0;
}
```

---

