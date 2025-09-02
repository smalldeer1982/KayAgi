# Omkar and Heavenly Tree

## 题目描述

Lord Omkar would like to have a tree with $ n $ nodes ( $ 3 \le n \le 10^5 $ ) and has asked his disciples to construct the tree. However, Lord Omkar has created $ m $ ( $ \mathbf{1 \le m < n} $ ) restrictions to ensure that the tree will be as heavenly as possible.

A tree with $ n $ nodes is an connected undirected graph with $ n $ nodes and $ n-1 $ edges. Note that for any two nodes, there is exactly one simple path between them, where a simple path is a path between two nodes that does not contain any node more than once.

Here is an example of a tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1583B/922e28fa3dc9009cfe0a3df0832a3fd2d74db75e.png)A restriction consists of $ 3 $ pairwise distinct integers, $ a $ , $ b $ , and $ c $ ( $ 1 \le a,b,c \le n $ ). It signifies that node $ b $ cannot lie on the simple path between node $ a $ and node $ c $ .

Can you help Lord Omkar and become his most trusted disciple? You will need to find heavenly trees for multiple sets of restrictions. It can be shown that a heavenly tree will always exist for any set of restrictions under the given constraints.

## 说明/提示

The output of the first sample case corresponds to the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1583B/0c5be7df736dea93d6f4b675bd823f2c78ee5fb4.png) For the first restriction, the simple path between $ 1 $ and $ 3 $ is $ 1, 3 $ , which doesn't contain $ 2 $ . The simple path between $ 3 $ and $ 5 $ is $ 3, 5 $ , which doesn't contain $ 4 $ . The simple path between $ 5 $ and $ 7 $ is $ 5, 3, 1, 2, 7 $ , which doesn't contain $ 6 $ . The simple path between $ 6 $ and $ 4 $ is $ 6, 7, 2, 1, 3, 4 $ , which doesn't contain $ 5 $ . Thus, this tree meets all of the restrictions.The output of the second sample case corresponds to the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1583B/72e70755d9a3eab42b10c011746b34dd97df37a1.png)

## 样例 #1

### 输入

```
2
7 4
1 2 3
3 4 5
5 6 7
6 5 4
5 3
1 2 3
2 3 4
3 4 5```

### 输出

```
1 2
1 3
3 5
3 4
2 7
7 6
5 1
1 3
3 2
2 4```

# 题解

## 作者：Yizhixiaoyun (赞：7)

[本套题所有题解](https://www.luogu.com.cn/blog/yizhixiaoyun/cf1583-ti-xie)

由于笔者水平较弱，所以可能只能一路做到自己做不了的题，不保证能全部写完。

------------

构造练手题。

由于数据保证了 $m < n$ ，所以事实上 $b_i$ 最多出现 $n - 1$ 次，那么至少会有一个节点不受任何限制的影响。

直接找到这个不受任何限制的节点，以它为根构造一个菊花图就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
int T;
int n,m;
int u,v,w;
bool vis[maxn];
int main(){
//	freopen("test.out","w",stdout);
	cin>>T;
	while(T--){
		memset(vis,false,sizeof(vis));
		cin>>n>>m;
		for(register int i=1;i<=m;++i){
			cin>>u>>v>>w;vis[v]=true;
		}
		for(register int i=1;i<=n;++i){
			if(vis[i]==false){
				for(register int j=1;j<=n;++j){
					if(i!=j) cout<<i<<" "<<j<<endl;
				}
				break;
			}
		}
	}
}
```

---

## 作者：Wuyanru (赞：3)

首先介绍一个**错误的**解法，解答一下一部分小伙伴的困惑：

一个非常好想的做法就是直接将所有 $ a_i $ 与 $ c_i $ 连接，下面给大家一组数据作为 hack。

```
1
4 3
1 2 3
2 3 1
3 1 2
```

这组样例的解是这样的：

![](https://z3.ax1x.com/2021/10/21/5ylwpF.png)

但是按照上述方法的话就会连成这个样子：

![](https://z3.ax1x.com/2021/10/21/5y1pBn.png)

虽说可能没有什么用但是上面的例子其实对于想正解还是很有用的。

那么下面我们来想正解。

首先不知道大家有没有注意到一个条件就是 $ m<n $,注意，这里是小于号。

这说明什么呢？

所有的 $ b_i $ 至多只会出现 $ n-1 $ 次，也就是至少会有一个节点对于任意的限制都没有影响！

那么，我们只需要把这个点当做根，其余所有节点向这个点连边即可。

时间复杂度为 $ O\left(n+m\right) $,空间复杂度为 $ O\left(n\right) $。

由于题目太水代码就不粘了~~其实是比赛代码码风究极扯~~。

感谢观看！！！

---

## 作者：xiaofeng_and_xiaoyu (赞：0)

都说 CF 的题考思维，于是我这个不会拍代码的蒟蒻来看思维题了。

看完题后先看数据范围$~~而不是题解~~$，发现光数据就达到了可怕的 $10^{4}$，最大图还会有 $10^{5}$ 的大小，完了，要爆。

但是别慌，CF 的题考思维，所以我们要仔细看题。不难发现有一个地方反复加粗，那就是 $1\le m<n$（可惜翻译扼杀了这个细节）。这说明总有一个点不受 $b_i$ 的限制，把它遍历找出来，然后以它为根构造一棵除它外全是叶子节点的树，就达成了条件。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int a,b,c,d,e,f=0;
		cin>>a>>b;
		bool x[a+1];
		memset(x,0,sizeof(x));
		for(int i=0;i<b;i++){
			cin>>c>>d>>e;
			x[d]=1;
		}
		for(int i=1;i<=a;i++){
			if(!x[i]){
				f=1;
				for(int j=1;j<=a;j++){
					if(i!=j)cout<<i<<' '<<j<<endl;
				}
			}
			if(f)break;
		}
	}
	return 0;
} 
```
提示：记住 CF 的题考思维，这会对你板刷 CF 的题有很大帮助！

---

## 作者：hellhell (赞：0)

### 题目描述

一共 $t$ 组数据，每组数据给出一棵树的点数 $n$ 和 $m$ 个限制形如 $a,b,c$，表示树上的点 $b$ 不能出现在 $a,c$ 的简单路径上。

对于每组数据你需要构造一棵树，满足这 $m$ 个限制。输出方式为 $n-1$ 行，每行两个数 $u,v$ 表示在 $u,v$ 之间连边。

数据范围：$3\leq n \leq10^5,1\leq m <n$，每个限制中的 $a,b,c$ 互不相同。 

### 思路分析

一道比较简单的构造题，注意到数据范围 $m<n$，也就是说这 $m$ 个限制，最多会限制 $n-1$ 点，至少有一个点，不受这 $m$ 个限制的影响。我们把这个点当做树根，所有点都连向树根即可。这样形成了一个菊花图。

这样构造，任意两点之间的简单路径都只会经过我们找的这个根节点和这两个点自己本身。

一定满足限制。

### 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long 

using namespace std;

int read(){
    int res=0;
    int f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        res=res*10+ch-'0';
        ch=getchar();
    }
    return res*f;
}

const int maxn=1e5+5;

int t;
int n,m,a,b,c;
bool vis[maxn];

signed main(){
	t=read();
	while(t--){
		int rt=0;
		n=read(),m=read();
		memset(vis,false,sizeof(vis));
		for(int i=1;i<=m;i++){
			a=read(),b=read(),c=read();
			vis[b]=true;
		}
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				rt=i;
				break;
			}
		}
		for(int i=1;i<=n;i++){
			if(!(i^rt))
				continue;
			printf("%lld %lld\n",rt,i);
		}
	}
    return 0;    
}
```


---

## 作者：_Clown_ (赞：0)

# B.Omkar and Heavenly Tree
这道题目我们考虑构造。

显然，我们要让 $a_i$ 到 $c_i$ 的路径上没有 $b_i$，

那么我们为了简单，

不难想到找一个没有用过的 $b_i$，

把他放在菊花图的根节点，

显然所有的路径都会成立。

而且很容易证得，一定能找到这样的点。

代码就不难写出了。
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int N,M,U[100001],V[100001],W[100001],Visit[100001];
int main(void)
{
	BetterIO;
	register int Case;cin>>Case;while(Case--)
	{
		register int i;cin>>N>>M;
		for(i=1;i<=M;i++)
		{
			cin>>U[i]>>V[i]>>W[i];
			Visit[V[i]]=i;
		}
		register int k;
		for(i=1;i<=N;i++)if(!Visit[i]){k=i;break;}
		for(i=1;i<=N;i++)if(i!=k)cout<<i<<' '<<k<<endl;
		memset(Visit,false,sizeof(Visit));
	}
	return 0;
}
```

---

## 作者：KSToki (赞：0)

# 题目大意
你需要构造一个 $n$ 个点的树，其需要满足 $m$ 个形如从 $a$ 到 $c$ 不经过 $b$ 的要求，注意  $m<n$。
# 题目分析
出题人很贴心啊，直接把 $m<n$ 给加粗了，这暗示了一定有一个点没有成为过 $b$，找到这样的一个点以其为根构造一个菊花即可。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first
#define se second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,m,a,b,c;
bool vis[100001];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		m=read();
		For(i,1,n)
			vis[i]=0;
		For(i,1,m)
		{
			a=read();
			b=read();
			c=read();
			vis[b]=1;
		}
		For(i,1,n)
			if(!vis[i])
			{
				For(j,1,n)
					if(i!=j)
						printf("%d %d\n",i,j);
				break;
			}
	}
	return 0;
}

```

---

## 作者：tongyanmin (赞：0)

## 题目大意
- 给出一棵树的结点数 $n$ 以及 $m$ 个约束条件，构造出一棵满足所有条件的树。
- 每个条件包含 $3$ 个不同的正整数 $a_i,b_i,c_i$，表示从结点 $a_i$ 到 $c_i$ 的路径上不能经过 $b_i$。
- 数据范围：$3≤n≤10^5,1≤m<n$。

## 题目分析
首先注意到对于树上任意的两个结点，两点之间的路径必定会经过它们的 LCA（[最近公共祖先](https://oi-wiki.org/graph/lca/)）。

再注意到本题的数据范围中有 $m<n$，说明一定存在一个结点 $x$，使得 $x∉b$。若能使树上任意两个结点间的路径除端点外只经过结点 $x$（即 $x$ 是任意两个结点的 LCA），就能满足题意。

至此，答案就很显然了，只要构造一棵以 $x$ 为根，其他结点为叶的菊花即可。

对于以下数据
```
7 4
1 2 3
3 4 5
5 6 7
6 5 4
```
我们不妨构造以 $1$ 为根的菊花，不难发现能够满足所给条件。![](https://cdn.luogu.com.cn/upload/image_hosting/fj8supak.png)
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;		
int a,b,c,root;		
bool vis[100005];
int main(){
	cin>>t;
	while(t--){
		memset(vis,0,sizeof(vis));
		cin>>n>>m;
		for(int i=1;i<=m;i++){
			cin>>a>>b>>c;
			vis[b]=1;
		}
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				root=i;//寻找根结点 
				break;
			}
		}
		for(int i=1;i<=n;i++){
			if(i==root)continue;
			cout<<root<<" "<<i<<endl;
		}
	}
	return 0;
}
```


---

## 作者：WuMin4 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1583B)

# 思路

首先看到翻译上面的一段话：$1 \le m < n$，而这就是解题的关键。因为 $m < n$，所以不论怎样都**至少会有一个点不在限制里**，于是可以以这个点为根节点构造**菊花图**。不难证得，任意两点的路径最多都只会包含这两个点和根节点，又因根节点不在限制里，所以可以满足所有限制。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m;
bool f[100005];
int main(){
	cin>>T;
	while(T--){
		memset(f,0,sizeof(f));
		cin>>n>>m;
		for(int a,b,c,i=1;i<=m;i++)
			cin>>a>>b>>c,f[b]=true;
		for(int i=1;i<=n;i++)
			if(!f[i]){
				for(int j=1;j<=n;j++)
					if(j!=i)
						cout<<i<<" "<<j<<endl;
				break;
			}
	}
	return 0;
}
```

---

