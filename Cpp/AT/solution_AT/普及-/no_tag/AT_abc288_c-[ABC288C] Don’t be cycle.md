# [ABC288C] Don’t be cycle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc288/tasks/abc288_c

$ N $ 頂点 $ M $ 辺の単純無向グラフが与えられます。頂点には $ 1 $ から $ N $ の番号がついており、$ i $ 番目の辺は頂点 $ A_i $ と頂点 $ B_i $ を結んでいます。 このグラフから $ 0 $ 本以上のいくつかの辺を削除してグラフが閉路を持たないようにするとき、削除する辺の本数の最小値を求めてください。

 単純無向グラフとは **単純無向グラフ**とは、自己ループや多重辺を含まず、辺に向きの無いグラフのことをいいます。

 閉路とは 単純無向グラフが**閉路**を持つとは、$ i\ \neq\ j $ ならば $ v_i\ \neq\ v_j $ を満たす長さ $ 3 $ 以上の頂点列 $ (v_0,\ v_1,\ \ldots,\ v_{n-1}) $ であって、各 $ 0\ \leq\ i\ に対し\ v_i $ と $ v_{i+1\ \bmod\ n} $ の間に辺が存在するものがあることをいいます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $
- 与えられるグラフは単純
- 入力はすべて整数
 
### Sample Explanation 1

頂点 $ 1 $ と頂点 $ 2 $ を結ぶ辺・頂点 $ 4 $ と頂点 $ 5 $ を結ぶ辺の $ 2 $ 本を削除するなどの方法でグラフが閉路を持たないようにすることができます。 $ 1 $ 本以下の辺の削除でグラフが閉路を持たないようにすることはできないので、$ 2 $ を出力します。

## 样例 #1

### 输入

```
6 7
1 2
1 3
2 3
4 2
6 5
4 6
4 5```

### 输出

```
2```

## 样例 #2

### 输入

```
4 2
1 2
3 4```

### 输出

```
0```

## 样例 #3

### 输入

```
5 3
1 2
1 3
2 3```

### 输出

```
1```

# 题解

## 作者：Neil_Qian (赞：3)

# [ABC288C] Don’t be cycle 题解

## 前置知识

并查集。

## 题意

给定一个简单无向图，要求删除最小的边数（可以不删）使得图中没有环。

## 题解

一开始可能会觉得就是 $m-n+1$，但第三个样例就否了这种做法，看样例就能明白。每增加一条边，设两个顶点为 $a$ 和 $b$，我们只需要看 $a$ 和 $b$ 是否在一个连通图中，在的话就答案 $+1$，否则将两个连通块合并。

如何判断两个点是否在一个连通块内？我们用 $f[i]$ 表示第 $i$ 个结点所在的连通块的代表的编号，每次递归查找 $f[f[f[f[f[\dots]]]]]$，直到这个顶点所在的连通块的代表是自己。每到一个点 $i$ 也要记录 $f[i]=ans$，其中 $ans$ 是递归调用的结果。最后比较递归调用 $a$ 和 $b$ 的结果即可。显然，初始化为 $f[i]=i$。

如何将两个连通块合并？设两个数 $a$ 和 $b$ 递归调用的结果是 $fnd(a)$ 和 $fnd(b)$，让 $f[fnd(a)]=fnd(b)$ 即可。这样 $a$ 里的元素递归调用后一定会先到 $fnd(a)$，然后就会到达 $fnd(b)$。

时间复杂度是多少呢？乍一看是 $O(n^2)$，因为每次递归调用好像是 $O(n)$ 的。然而，我们仔细思考，什么时候会让我们的递归次数上升？当然是合并啊！而一次合并最多让我们多搜索一次，因为搜了一次以后就直接 $O(1)$ 找到答案。更详细的可以自行上网查看，这里不在赘述。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;const int N=2e5+2;
int n,m,a,b,f[N],ans;
inline int fnd(int x){return (f[x]==x?x:f[x]=fnd(f[x]));}//fnd函数
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)f[i]=i;//初始化
	while(m--){
		scanf("%d%d",&a,&b);
		if(fnd(a)!=fnd(b))f[fnd(a)]=fnd(b);//合并
		else ans++;//发现一个环
	}
	return printf("%d\n",ans),0;
}
```

---

## 作者：_JF_ (赞：1)

### [ABC288C] Don’t be cycle 

给定一个简单无向图，要求删除最小的边数（可以不删）使得图中没有环。

还是可以考虑搜索，深搜万岁！

我们考虑每跑到一个节点，我们就把他标记起来。如果我们在遍历的过程之中，如果走回一个我们标记过得节点，就会产生环。

我们只能从没有标记的节点开始查找，不然的话会多算。

但是这样的话会算成两倍，原因是假设 $vis_u$ 和 $vis_v$ 为 $1$ 的话。由于 $u$ 和 $v$ 相同，故加一。但回溯的时候 $v$ 和 $u$ 相同，所以多算了一次。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
bool flag=true;
int vis[N];
vector<int> g[N<<1];	
int sum;
void dfs(int u,int la,int find)
{		
	vis[u]=1;
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(v==la)
			continue;
		if(vis[v]==1)
		{
			sum++;
			flag=false;
			continue;
		}		
		dfs(v,u,find);
	}
}
int main()
{

	int n,m;
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++)
		cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	for(int i=1;i<=n;i++)
	{
		flag=true;
		if(vis[i]==true)
			continue;
		dfs(i,INT_MAX,i);
	}
	cout<<sum/2<<endl;
	return 0;
}

```


---

## 作者：yinhy09 (赞：0)

## 题目分析：

本题我们可以用最小生成森林解，也可以用并查集。这里选用并查集的思路。

我们每添加一条边，判断这条边连接的两个节点是不是属于同一个连通块，如果是，那么这条边统计入答案（废边），否则就继续。

这个操作明显可以用并查集加速到 $O(n\log_2n)$，可以通过此题。QwQ

## AC Code : 

```cpp
/*******************************
| Author:  yinhy09
| Problem: C - Don’t be cycle
| Contest: AtCoder - Toyota Programming Contest 2023 Spring Qual A（AtCoder Beginner Contest 288）
| URL:     https://atcoder.jp/contests/abc288/tasks/abc288_c
| When:    2023-02-04 20:10:34
| 
| Memory:  1024 MB
| Time:    2000 ms
*******************************/

#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define multicase() ll T;scanf("%lld",&T);while(T--)
ll read()
{
	char c;
	ll x=0;
	ll f=1;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f*=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
ll n,m;
const int maxn=2e5+10;
ll u,v;
ll fa[maxn];
void init()
{
	for(int i=1;i<=n;i++)fa[i]=i;
}
ll find(ll x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
bool merge(ll x,ll y)
{
	ll fx=find(x),fy=find(y);
	if(fx==fy)return 1;
	fa[fx]=fy;
	return 0;
}
int main()
{
	cin>>n>>m;
	ll ans=0;
	init();
	for(int i=1;i<=m;i++)
	{
		cin>>u>>v;
		ans+=merge(u,v);
	}
	printf("%lld\n",ans);
	return 0;
}
```

谢谢观看喵~

---

## 作者：Paris_Commune (赞：0)

### 分析

问题要求找到需要删除的最小边数，但我们考虑可以保留的最大边数，如果最多 $K$ 边缘可以保留，原始问题的答案是 $M-K$ 。

设 $Q$ 是图形中的连通分量。如果连通分量具有 $x$ 个顶点，至少 $x-1$ 个可以通过采用适当的生成树来保留边。如果 $x$ 无法保留更多边，因为如果要添加 $x$ 个边到没有任何边的图形，至少应减少连接组件的数量 $x$ 次。

因此 $K=\sum_{i=1}^{Q} (x_i-1)$ , $x_1\sim x_n$
 是连通分量的大小。因为 $N=\sum_{i=1}^{Q} (x_i)$ 就可以得到 $L=N-Q$ 。

答案为 $M-N+Q$ 。

---

## 作者：liangbob (赞：0)

### AT_abc288_c 题解

题目比较板，说一下思路。

假设图中共有 $x$ 个连通块，那么显然，我们应该将这 $x$ 个连通块每个都删除到只剩一棵树（个人喜欢将其称之为连通链）。不妨第 $i$ 个连通块有 $v_i$ 个点，即 $e_i = v_i-1$ 条边。共需删除 $\sum{e_i} = n - x$ 条边。所以答案为 $m - (n-x)$。

接着就是求连通块。我们可以将 $n$ 个点形象化为 $n$ 个罪犯。将连通块形象化为犯罪团伙。对于由一条无向边连接的两点 $(u,v)$ 可以定义为“$(u,v)$ 在同一个犯罪团伙”。这就是一个经典的并查集问题“犯罪团伙问题”，可以直接套用并查集板子，最后根据上述公式输出即可。

代码过板，就不放了。


---

