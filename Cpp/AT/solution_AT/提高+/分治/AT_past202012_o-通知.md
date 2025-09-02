# 通知

## 题目描述

有一张 $n$ 点 $m$ 边的无向图。点的编号从 $1$ 到 $n$，第 $i$ 条边连接点 $a_i$ 和 $b_i$。每个点都有一个属性值，初始时均为 $0$。

有 $q$ 次操作，每次操作给出操作类型 $t_i$ 和操作参数 $x_i$。

- 当 $t_i=1$ 时，将与点 $x_i$ **直接相连**的点的属性值加 $1$。
- 当 $t_i=2$ 时，将点 $x_i$ 的属性值输出，然后将该值设为 $0$。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的测试数据，保证：

- $2 \le n \le 2 \times 10^5$，$1 \le m \le 2 \times 10^5$，$1 \le a_i \lt b_i \le n$；
- $1 \le q \le 2 \times 10^5$，$t_i \in \{ 1,2 \}$，$1 \le x_i \le n$。

输入数据均为整数。

## 样例 #1

### 输入

```
3 2
1 2
1 3
5
1 1
2 2
1 1
2 3
2 1```

### 输出

```
1
2
0```

## 样例 #2

### 输入

```
7 7
1 4
1 6
3 4
3 5
3 7
4 5
4 7
15
1 1
2 3
1 4
2 2
1 5
1 1
1 4
2 4
2 3
2 1
1 7
1 2
2 5
2 4
2 2```

### 输出

```
0
0
3
3
2
2
1
0```

## 样例 #3

### 输入

```
10 13
1 2
1 5
1 9
2 3
2 4
3 5
3 6
3 9
4 8
5 7
5 10
6 7
6 10
20
1 5
2 8
1 4
2 9
1 1
1 6
2 8
1 10
2 7
1 10
1 10
2 8
1 7
2 5
1 9
2 2
1 9
1 4
2 4
2 6```

### 输出

```
0
0
1
2
0
5
2
0
4```

# 题解

## 作者：EityDawn (赞：2)

## 思路
一类关于在图上进行操作的根号分治题。

分析默认 $n,m,q$ 同阶。

我们设立一个阈值 $B$。修改时，对于出度 $\ge B$，我们对这个点打上标记，而对于出度 $\le B$ 的点，可以直接暴力来搞，这一步复杂度为 $O(B)$。而询问时，我们将这个点周围出度 $\ge B$ 的点的标记累加上输出，将点权设为标记和的相反数，那么后续操作这些标记就不会重复计算，而出度 $\ge B$ 的点数不超过 $n\over B$，这一步复杂度 $O({n\over B})$。

综上来看，复杂度为 $O(n(B+{n\over B}))$，$B$ 取 $\sqrt n$ 时最优，为 $O(n\sqrt n)$。

## code
```cpp
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<climits>
#include<cmath>
#include<ctime>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=2e5+10,M=400;
vector<int>G[N],Fa[N];
int Tag[N];
int n,m,q,out[N],a[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1,x,y;i<=m;i++)
	{
		cin>>x>>y;
		G[x].push_back(y);
		G[y].push_back(x);
		++out[x],++out[y];
	}
	for(int now=1;now<=n;now++)
		if(out[now]>M){
			for(int to:G[now])
				Fa[to].push_back(now);
		}
	cin>>q;
	int op,x;
	for(int i=1,x;i<=q;i++)
	{
		cin>>op>>x;
		if(op==1){
			if(out[x]>M)
				++Tag[x];
			else for(int to:G[x]) ++a[to];
		}
		else{
			int Sum=0;
			for(int from:Fa[x])
				Sum+=Tag[from];
			cout<<a[x]+Sum<<'\n';a[x]=-Sum;
		}
	}
	return 0;
}


```

---

## 作者：hgckythgcfhk (赞：2)

一个根号分治板题，我们定义关键节点为度数大于 $\sqrt{m}$ 的节点，这样的节点只有 $O(\sqrt{m})$ 个，正确性显然，因为在边数等于所有点的度数之和，这种度数很大的节点会浪费更多的边数。同时，与每个点相邻的点最多有 $O(\sqrt{m})$ 个关键点，这是句废话，但这是句有用的废话，这提示我们可以存下与每个点相邻的关键点，单独计算关键点的贡献，这样我们得到一个做法。

1. 对于关键点的修改：打上标记。

2. 对于非关键点的修改：暴力的修改所有相邻点的权值。

3. 对于查询：答案为当前点的权值加上所有相邻关键点的标记。

4. 对于清零：将当前点的权值设为所有相邻关键点的标记和的相反数。

对于第最后一条，如果直接设为 $0$，下次查询的时候还会计算相邻关键点的贡献，相当于只清零了相邻非关键点的贡献。

注意事项：本题翻译有误，按题面翻译的意思，修改操作会把 $x_i$ **和** 与它相邻的点的权值加 $1$，但是，手搓一下样例，参考一下百度翻译，$x_i$ 不会加 $1$，我按 $x_i$ 不加 $1$ 写的，过了。

最后警示后人：如果你 WA 了比较靠后的点，但感觉自己是对的，看一下数组开的够不够大，数组开小了不一定会 RE 也有可能 WA。

```
#include<bits/stdc++.h>
#define cit const register unsigned
#define open ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)//,freopen("1.in","r",stdin),freopen("1.out","w",stdout)
#define int register unsigned
#define void inline void
using namespace std;constexpr unsigned N=2e5+1;
unsigned lz[N],c[N];vector<unsigned>a[N],b[N];
#define pb emplace_back
signed main(){open;int n,m;cin>>n>>m;
	for(int i=m,u,v;i;--i)cin>>u>>v,a[u].pb(v),a[v].pb(u);m=__builtin_sqrt(m);
	for(int i=1;i<=n;++i)for(const int j:a[i])if(a[j].size()>m)b[i].pb(j);
	int q;cin>>q;while(q--){int op,u;cin>>op>>u;
		if(op==1){if(a[u].size()>m)++lz[u];
			else for(const int v:a[u])++c[v];
		}else{int ans=c[u];c[u]=0;for(const int v:b[u])ans+=lz[v],c[u]-=lz[v];
			cout<<ans<<'\n';
		}
	}
}

```


---

## 作者：BFSDFS123 (赞：1)

**题目大意**

将一个点相邻的所有节点加一，查询节点值。

**solution**

修改相邻节点，一眼顶针，鉴定为根号分治。

为什么能想到根号分治？

首先考虑暴力怎么做，有以下两种方法。

1. 对于一个点，遍历它连接的所有点，修改这些点的点权。每次询问查询值即可。修改 $O(\operatorname{siz})$，查询 $O(1)$。
2. 对于一个点，若要执行一次修改，便将这个节点打上一个标记。每次查询遍历所有相邻节点的标记数量。修改 $O(1)$，查询 $O(\operatorname{siz})$。

其中 $\operatorname{siz}$ 指与当前节点相邻的节点个数。

容易发现两种暴力方法的瓶颈分别在修改和查询，不妨把他们结合起来。

一下默认 $n,m$ 同阶。

设阈值 $B=\sqrt{n}$。若 $\operatorname{siz}< B$，则执行第一种暴力，否则执行第二种暴力。

对于 $\operatorname{siz}<B$ 的情况，容易发现单次暴力修改相邻节点权值的时间复杂度变为了 $\sqrt n$。

对于 $\operatorname{siz}\ge B$ 的情况。显然只有 $\operatorname{siz} \ge B$ 的节点会有标记值，我们称这样的节点为重节点。

由于每个重节点的 $\operatorname{siz}$ 至少为 $B$，那么重节点数量一定不超过 $\frac{n}{B}=\frac{n}{\sqrt n}=\sqrt n$。

对于一个节点的价值，为该点权值和加上该点相邻所有重节点的标记和。时间复杂度为 $O(1) + O(\sqrt n)$。

整体的时间复杂度便为 $O(q\sqrt n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=2e5+10;
int n,m;
vector<int> G[Maxn];
vector<int> Heavysons[Maxn];
int deg[Maxn];
int isheavy[Maxn];

int tags[Maxn];
int val[Maxn];
int main()
{
    scanf("%d%d",&n,&m);
    int Maxb=sqrt(n);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v),G[v].push_back(u);
        deg[u]++,deg[v]++;
    }
    for(int i=1;i<=n;i++)
    {
        if(deg[i]>=Maxb)
        {
            isheavy[i]=1;
        }
    }

    for(int i=1;i<=n;i++)
    {
        for(auto j:G[i])
        {
            if(isheavy[j])
            {
                Heavysons[i].push_back(j);
            }
        }
    }

    int q;
    scanf("%d",&q);
    while(q--)
    {
        int opt,x;
        scanf("%d%d",&opt,&x);
        if(opt==1)
        {
            if(G[x].size()<Maxb)
            {
                for(auto i:G[x])
                {
                    val[i]++;
                }
            }else{
                tags[x]++;
            }
        }else{
            int ans=val[x];
            val[x]=0;
            for(auto i:Heavysons[x])
            {
                ans+=tags[i];
                val[x]-=tags[i];
            }

            printf("%d\n",ans);
        }
    }
    return 0;
}
```

---

