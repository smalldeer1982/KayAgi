# 『GROI-R1』 虹色的彼岸花

## 题目背景

少年身着春季校服的深灰色外套与黑色短裤，外套内是白净的衬衫。

他的右手不知为何缠着绷带，右眼用头发挡得严严实实，扑面而来的是一种神秘感。

一瓣鲜红的彼岸花，在教室上空无人在意之处打旋。

玘的身世，总是一个谜题吧。

「所以你到底是什么人，又为什么要来这里！」

可是彼岸花显然不想让你知道这些。

## 题目描述

玘给了寒一棵编号为 $1\sim n$ 的树，这棵树上每个点都有一个点权，同时有些边有边权，有些边没有边权。可是玘把每一个点的点权删除了。寒只知道****点权都是整数，而且在 $l$ 和 $r$ 之间（包含端点）****。而且，点权和边权有着下面的特殊关系：

- 对于****有边权****的边，要求****连接的两个点的点权和为边权****。

- 对于****没有边权的边****，****无限制****。

玘问寒这棵树****有多少种不同的点权填写方式****。两种填写方式不同，当且仅当至少存在一个点的点权不同。可是寒不会做这个题。

寒请你解决这个问题。

## 说明/提示

**样例解释**

对于样例的第一组测试数据，可以得到下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/91vlqt5k.png)

$5$ 种填写方式分别为：

$\{0,2,2,0,0,3\}\\\{0,2,2,0,1,3\}\\\{0,2,2,0,2,3\}\\\{0,2,2,0,3,3\}\\\{0,2,2,0,4,3\}$

可以证明，不存在别的填写方式。

样例输入中，为了直观，添加了空行。实际数据中不存在多余空行。

**数据范围**

**本题采用捆绑测试。**

| 子任务编号 | 数据范围 | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $\text{Subtask1}$ | $1\le n\le 10$，$0\le l,r\le5$ |  | $15$ |
| $\text{Subtask2}$ | $1\le n\le 2\times 10^5$，$0\le l,r\le5$ |  | $20$ |
| $\text{Subtask3}$ | $1\le n\le 10$，$-10^9\le l,r\le 10^9$ |  | $15$ |
| $\text{Subtask4}$ | $1\le n\le 2\times10^5$，$-10^9\le l,r\le 10^9$ | 有 | $10$ |
| $\text{Subtask5}$ | $1\le n\le 2\times10^5$，$-10^9\le l,r\le 10^9$ |  | $40$ |

特殊性质：保证每条边都无边权。

对于 $100\%$ 的数据，保证 $1\le T \le 5$，$1\le n\le 2\times10^5$，$1\le \sum n\le 10^6$，$-10^9\le l\le r \le 10^9$，$-10^9\le w\le 10^9$，$op\in\{0,1\}$。

## 样例 #1

### 输入

```
2
6 0 4
1 1 2 2
1 2 3 4
1 3 4 2
0 2 5
1 4 6 3

6 -1 4
1 1 2 4
0 2 3
0 3 4
0 2 5
0 4 6```

### 输出

```
5
6480```

# 题解

## 作者：imzfx_Square (赞：15)

# P8971 『GROI-R1』 虹色的彼岸花 题解
[题目传送门](https://www.luogu.com.cn/problem/P8971)
### 分析部分：
对于一条边连接的两个点，如果这条边有边权，当其中一个点的点权确定时，另一个点的点权**也会确定**；如果这条边无边权，两个点的点权相互之间**不会有影响**。因此可以将无边权的边**忽略**，将这一棵树看作**森林**，对其中的每棵树进行处理。

对于一棵树，只要确定了一个点的点权，就可以确定通过边权计算出其他点的点权。因此我们可以从一点开始访问，令其值为 $x$，将其他点的点权用 $x$ 和 一个数 $k$ 来表示。对于一个点来说，点权只会有 $k+x$ 和 $k-x$ 这两种情况。因此我们需要计算 $k$ 和判断 $x$ 的正负性。

我们可以从最开始的点进行 dfs。对于一个点 $u$，设它的点权为 $k_u+sign_u \times x$，则它的儿子 $v$ 的点权就是 $w_{u,v}-(k_u+sign_u \times x)=w_{u,v}-k_u-sign_u \times x$，可以得到 $k_v=w_{u,v}-k_u$，$sign_v=-sign_u$，实际实现时只需将 $k$ 和 $sign$ 作为参数下传即可。对于算出的点权，解出关于 $x$ 的不等式，取左极值最大，右极值最小。设最终计算出的解集为 $ll \le x \le rr$ （~~一年半前极差的取名习惯~~），若 $rr<ll$ ，说明没有可行解，否则这棵树的填写方式共有 $rr-ll+1$ 种，将每棵树的填写方式相乘即可。

### 代码部分：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,mod=1e9+7;
struct node{
	int to,next,w;
}e[N<<1];
long long l,r;
long long n,t,cnt,ans;
long long h[N];
long long ll,rr,x,y,op,w;
bool vis[N];
void Link(int x,int y,int w){
	e[++cnt].to=y;
	e[cnt].next=h[x];
	e[cnt].w=w;
	h[x]=cnt;
}
void dfs(int x,int k,int sign){
	vis[x]=true;
	long long nl=l-k,nr=r-k;//解不等式
	if(sign==-1)swap(nl,nr),nl=-nl,nr=-nr;
	ll=max(ll,nl),rr=min(rr,nr);//更新左极值、右极值
	for(int i=h[x];i;i=e[i].next){
		if(!vis[e[i].to])
			dfs(e[i].to,e[i].w-k,-sign);//计算k和sign
	}
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>l>>r;
		memset(vis,false,sizeof(vis));//多测清空
		memset(e,0,sizeof(e));
		memset(h,0,sizeof(h));
		cnt=0;
		ans=1;
		for(int i=1;i<=n-1;i++){
			cin>>op>>x>>y;
			if(op==1)cin>>w;
			else continue;//忽略无边权的边
			Link(x,y,w);
			Link(y,x,w);
		}
		for(int i=1;i<=n;i++){
			ll=l,rr=r;
			if(!vis[i]){
				dfs(i,0,1);//从自己开始，自己的k是0，sign是1
				if(rr<ll)ans*=0;//更新范围
				else ans=ans*(rr-ll+1)%mod;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
} 
```

---

## 作者：MichaelWong (赞：9)

# [原题链接](https://www.luogu.com.cn/problem/P8971)



------------



先介绍一下大概情况：

- 给定一棵树，节点编号 $1 \sim n$；
- 对于有边权的边连接的两点，点权相加等于边权；
- 对于无边权的边连接的两点，无限制。
- 给定点权的取值范围 $[l,r]$，点权都是整数；
- 求点权的所有填写方式的个数。

简单分析，可以得出一下结论：

1. 对于有边权的边连接的两点，确定了其中一个点的点权，另一个点的点权也会 **确定**；
1. 对于无边权的边连接的两点，其中一点的点权 **不会** 对另一点的点权产生影响。

根据结论 2，我们可以把这个树沿无边权的边拆成 **多个部分**，这几个部分之间不会互相影响；求出 **每个部分** 的填写方式个数，再把各个部分的个数 **相乘**，就可以得到整个树的填写方式个数了。

在具体做法上，我们 **不记录** 无边权的边，把 **树** 当作 **森林** 处理，其中的每一棵树的所有边都有边权。如所给样例，我们把它看作 `5` 和 `1 2 3 4 6` 两棵树。接下来，我们来针对每一个树进行处理。

![](https://cdn.luogu.com.cn/upload/image_hosting/91vlqt5k.png)

根据结论 1，对于任意一棵树，只要确定 **一个点的点权**，整棵树的所有点权就 **全部确定** 了。对于树上的一点 $u$，若其点权为 $k$ 时，该树上的所有点的点权都在 $[l,r]$ 内，则这个方式是 **合法** 的。此时，对于每棵树，问题从 **求填写方式个数** 转化为了 **求树上任意一点 $u$ 的合法点权个数**。

不难得出，如果 $a$ 和 $b$ 都是点 $u$ 的合法点权，那么 $[a,b]$ 内的任何一个整数 **都是** $u$ 的合法点权。所以，我们只需要求出 $u$ 的合法点权的取值范围 $[nowl,nowr]$ 即可。$u$ 的合法点权个数即为 $nowr-nowl+1$。

我们可以求出树上任意一点的点权 $v$ 用 $u$ 的点权表达的表达式。易得所有的表达式都是 **一次函数**：

$$val_u + val_v = w(u,v)$$
$$val_v = w(u,v) - val_u$$

举个例子，如果有三个点 $x,y,z$，其中 $(x,y)$，$(y,z)$ 间有有权边，则可以表示为：

$$val_y = w(x,y) - val_x$$
$$val_z = w(y,z) - val_y$$
$$val_z = w(y,z) - w(x,y) + val_x$$

可以发现，在表达不同点的点权时 $val_x$ 的系数可能是 $1$ 或 $-1$，且该点与该点的子节点中 $val_x$ 的系数必然为相反数。在代码中我们可以引入一个新变量 $typ_v$ 来记录表达式中 $val_u$ 的系数为正还是为负。（我的代码中 $0$ 为正，$1$ 为负。）

接下来解出对于 **任意一点** $l \leq val_v \leq r$ 时 $val_u$ 的 **取值范围**，左极值取 $\max$ ，右极值取 $\min$，即可得出 $u$ 的合法点权的取值范围。
特殊地，如果结果得出 $nowl > nowr$，则证明这棵树 **没有合法解**；一棵树没有合法解，意味着 **全森林都没有**。

总结一下大致流程：

- 忽略无权边，把树当作 **森林** 处理；
- 对于每棵树，求出所有点用其中一点 $u$ 表达的解析式，求出满足任意一点 $v$ 的点权 $l \leq val_v \leq r$ 时 $u$ 的取值范围 $[nowl,nowr]$，该树的所有填写方式即为 $nowr-nowl+1$；
- 将每棵树的填写方式个数 **相乘**，即为最终结果；
- 特殊地，如果 $nowl > nowr$，则 **没有合法解**。

$\text{AC Code}$：

```cpp
// Author: MichaelWong
// Code: C++14(GCC 9)
#include<bits/stdc++.h>
const int M=2e5+5;
const int mod=1e9+7;
std::vector<std::pair<int,int>> e[M];
bool vis[M],typ[M];
int val[M],n,T;
long long l,r,nowl,nowr,ans;
void init() {
    for(int i=1;i<M;++i) e[i].clear();
    memset(vis,0,sizeof vis);
    ans=1;
}
void dfs(int u) {
    for(auto i:e[u]){
        int v=i.first,w=i.second;
        if(vis[v]) continue; vis[v]=1;
        if(typ[u]) { // 系数为负
            typ[v]=0; // 子节点系数是其相反数
            val[v]=w-val[u]; // 求解析式
            nowl=std::max(nowl,l-val[v]);
            nowr=std::min(nowr,r-val[v]);
		} // 比较取值范围
        else { // 系数为正
            typ[v]=1;
            val[v]=w-val[u];
            nowl=std::max(nowl,val[v]-r);
            nowr=std::min(nowr,val[v]-l);
		}
        dfs(v);
    }
}
int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);std::cout.tie(0);
    std::cin>>T;
    while(T--) {
        init();
        std::cin>>n>>l>>r;
        for(int i=1,opt,u,v,w;i<n;++i) {
            std::cin>>opt;
            if(opt) {
                std::cin>>u>>v>>w;
                e[u].push_back(std::make_pair(v,w)),e[v].push_back(std::make_pair(u,w));
			}
            else std::cin>>u>>v;
		}
        for(int i=1;i<=n;++i) {
            if(vis[i]) continue; vis[i]=1; // 跳过已遍历的树
            nowl=l,nowr=r; // 赋初值
            typ[i]=0,val[i]=0; // 用自己表达自己系数当然为正
            dfs(i);
            if(nowl>nowr) { ans=0; break; } // 无合法解
            else ans=ans*(nowr-nowl+1)%mod; // 有合法解
        }
        std::cout<<ans<<'\n';
	}
    return 0;       
}
```

本题解毕。

---

## 作者：jiazhichen844 (赞：2)

# 题意
有一棵树，有的边有边权，有的边没有，问你有多少种点权填写方式，使得：

1.$l \le \text{点权}\le r$

2.对于有边权的边，连接的两点点权之和为边权。

## 思路
对于无边权的边，断掉，考虑剩下的一个连通块。设最高点点权为 $x$ ，则他的儿子点权为 $w-x$ ，孙子点权为 $t-(w-x)=x+(t-w)$……于是可以列出不等式组：

$$\begin{cases}l \le x \le r\\ l \le w-x \le r \\l \le x+(t-w) \le r \\...\end{cases}$$

于是我们需要解 $l \le ax+b\le r$。

即 $l-b \le ax \le r-b$。

- 当 $a > 0$，$\frac{l-b}{a} \le x \le \frac{r-b}{a}$

- 当 $a < 0$，$\frac{r-b}{a} \le x \le \frac{l-b}{a}$

下传至子树时，每次对 $a$ 和 $b$ 取负，再加上 $w$。

于是，我们可以对 $x$ 进行一系列限制，合并一下，就可以得到一棵树的方案数。

乘起来，即为答案。

## AC code
~~多测不清空，零分两行泪。~~~
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<pair<int,long long> > e[200005];
vector<int> root;
long long l,r;
int mod=1e9+7;
void dfs(int pos,bool f,int fa)
{
	if(f)
		root.push_back(pos);
	for(int i=0;i<e[pos].size();i++)
	{
		if(e[pos][i].first==fa)
			continue;
		if(e[pos][i].second==INT_MAX)
			dfs(e[pos][i].first,1,pos);
		else
			dfs(e[pos][i].first,0,pos);
	}
}
void dfs2(int pos,int f,long long b,int minn,int maxn,int fa)
{
	if(f==1)
	{
		r=min(r,maxn-b);
		l=max(l,minn-b);
	}
	else
	{
		l=max(l,b-maxn);
		r=min(r,b-minn);
	}
	for(int i=0;i<e[pos].size();i++)
	{
		if(e[pos][i].first==fa)
			continue;
		if(e[pos][i].second==INT_MAX)
			continue;
		dfs2(e[pos][i].first,-f,e[pos][i].second-b,minn,maxn,pos);
	}
}
void test() 
{
	int rl,rr;
	int n;
	cin>>n>>l>>r;
	rl=l;
	rr=r;
	int u,v;
	for(int i=1;i<=n;i++)
		e[i].clear();
	for(int i=1;i<n;i++)
	{
		int o;
		cin>>o;
		if(o==0)
		{
			cin>>u>>v;
			e[u].push_back({v,INT_MAX});
			e[v].push_back({u,INT_MAX});
		}
		else
		{
			long long w;
			cin>>u>>v>>w;
			e[u].push_back({v,w});
			e[v].push_back({u,w});
		}
	}
	root.clear();
	dfs(1,1,0);
	long long s=1;
	for(int i=0;i<root.size();i++)
	{
		l=rl;
		r=rr;
		dfs2(root[i],1,0,l,r,0);
		if(l>r)
			s=0;
		else
			s=s*(r-l+1)%mod;
	}
	cout<<s<<endl;
}
int main()
{
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
		test();
}
```

---

## 作者：masonpop (赞：2)

* 非常好的一道题。希望以后有更多的这样的高质量比赛。
* 发现这个没有边权的边根本没用，那就不加吧。此时就变成了一个森林。显然对于每棵树求出答案再相乘即可。
* 考虑一棵树怎么做。显然，只要确定了一个点的值，其它点的值就唯一确定了。可以任取一个点，将其值设为 $x,$ 根据边权可以写出其它点权值关于 $x$ 的表达式，解出 $x$ 的范围即可。显然，其他点关于 $x$ 的形式只可能是一次函数，且只有 $x+k$ 或 $k-x$ 两种形式(手模一下样例试试)，根据这个可以列出不等式 $l\leq \pm x+k\leq r.$ 可以通过每个点解出的区间缩小左右端点的范围。

* 具体实现起来很简单。建立两个数组 $typ,val,$ 分别储存 $x$ 的正负性和后面的常数(我的代码里 $1$ 是正，$2$ 是负)。对于 $x$ 的每个子节点 $y,$ 我们分类讨论一下就可以确定 $y$ 的形式了。注意左端点要和每次解出的左端点取 $\max,$ 右端点取 $\min.$
* 那么，如果最终的 $r>l$ 当然无解，否则答案乘上 $r-l+1.$
* 时间复杂度 $O(n).$ 如果还是不明白，代码里有注释辅助理解。

代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,n,m,l,r,x,y,z,op;
const int maxn=4e5+10;
const int mod=1e9+7;
int head[maxn],nxt[maxn],to[maxn],ver[maxn],tot;
int typ[maxn],val[maxn],vis[maxn];//typ:种类
int nowl,nowr,ans=1;
//typ=1:x+a
//typ=2:a-x 
inline void add(int x,int y,int z)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
	ver[tot]=z;
}
inline void dfs(int x)
{
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(vis[y])continue;
		vis[y]=1;
		if(typ[x]==1)//x+a -> (val-a)-x
		{
			typ[y]=2;
			val[y]=ver[i]-val[x];//解方程
			//val[y]-x>=l
			nowr=min(nowr,val[y]-l);
			//val[y]-x<=r
			nowl=max(nowl,val[y]-r); 
		}
		else//a-x -> (val-a)+x
		{
			typ[y]=1;
			val[y]=ver[i]-val[x];
			//val[y]+x>=l
			nowl=max(nowl,l-val[y]);
			//val[y]+x<=r
			nowr=min(nowr,r-val[y]);
		}
		dfs(y);
	}
}
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		tot=0;ans=1;
		memset(vis,0,sizeof(vis));
		memset(typ,0,sizeof(typ));
		memset(val,0,sizeof(val));
		memset(head,0,sizeof(head));
		scanf("%lld%lld%lld",&n,&l,&r);
		for(int i=1;i<n;i++)
		{
			scanf("%lld%lld%lld",&op,&x,&y); 
			if(op==1)
			{
				scanf("%lld",&z);
				add(x,y,z);add(y,x,z);
			}
		} 
		for(int i=1;i<=n;i++)
		{
			if(vis[i])continue;
			vis[i]=1;
			nowl=l;nowr=r;//当前变量x的范围
			typ[i]=1;val[i]=0;//x+0的形式 
			dfs(i);
			if(nowl>nowr)ans=0;
			else ans=ans*(nowr-nowl+1)%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：迟暮天复明 (赞：1)

对于前三个子任务，随便暴力做一做，判断一下无解的情况，总能过的。这里不多展开。

对于第四个子任务，显然每个点的点权都没有限制，所以答案就是 $(r-l+1)^n$。

接下来讲解正解的做法。

首先，由于没有边权的边无限制，就不去管它。把没有边权的边删除后可以得到一个森林。我们只需要对森林中的每一棵树进行求解，然后把每一棵树的答案乘起来即可。

考虑每一棵树的解法。我们发现，一棵树中，只要确定一个点的权值，其他所有点的权值都是可以计算的。如果设最初那个点的权值是 $x$，那么其他点的权值只能是 $x+k$ 或 $-x+k$，其中 $k$ 是常数。如何计算每个点的 $k$ 呢？我们考虑从最初的点开始对这棵树进行深度优先遍历。通过上一个点的 $k$ 和这条边的权值可以计算出这个点的 $k$，用数学公式表示就是 $k_v=val_e-k_u$。同时，每条边连接的两个点 $x$ 的符号相反。我们只需要在遍历的同时记录当前点 $x$ 的符号与 $k$，即可进行计算。

遍历完这一棵树之后，我们就可以找到点权形如 $x+k$ 的点的点权最大值和最小值，以及点权形如 $-x+k$ 的点的点权最大值和最小值。这其实就是它们各自 $k$ 的最大值和最小值。我们设这四个值分别为 $\text{maxp,minp,maxn,minn}$。只要它们四个点的权值满足在取值范围之内，就一定成立。我们可以列出以下不等式组：

$$

\begin{cases}
x+maxp\le r \\
x+minp\ge l \\
-x+maxn\le r \\
-x+minn\ge l
\end{cases}

$$


解出这个不等式组，我们就得到了 $x$ 的取值范围。如果这个不等式组无解，那么答案就是 $0$。否则，我们设解出来 $L\le x\le R$，那么因为 $x$ 是整数，我们就知道成立的 $x$ 个数就是 $R-L+1$。这就是一棵树的答案求解方式。最后把每棵树的答案相乘即可。

注意如果这棵树只有一个点，那么答案就是 $r-l+1$。否则，在开始遍历之前，需要任意找一个根节点连着的点以计算四个数的初始值。

---

## 作者：wwwwwza (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P8971)  
一道高质量题目，思路新颖，建议大家都去尝试一下。  

## 步骤
### 一、输入  
1. 由于有多组输入，要在输入前要初始化。   
2. 可以发现没有边权的边根本没用，所以输入时可直接跳过，将一颗树变成森林。    

### 二、遍历森林
1. 对于一颗树遍历的第一个节点 $u$，设其的点权为 $x$。由于大多数节点的点权要用多项式表示，所以要开数组存储每一个点的点权的常数项和未知数的系数。
2. 因为在途中只有有权边，所以知道了节点 $u$ 的点权，即可知与点 $u$ 相连的节点 $v$ 的点权。
3. 将整个图的节点的点权记录下来，因为全部点权 $w$ 都满足不等式：$l \leq w \leq r$，所以就可以求出开头设的未知数 $x$ 的取值范围。又因为所有点权都为整数，即可求出一棵树有多少种不同的点权填写方式。
4. 当 $x \leq 0$ 时，即无答案，输出 $0$。

### 三、输出
1. 将每棵树有多少种不同的点权填写方式相乘，再 $ \bmod \ 10^9+7 $，最后输出答案。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int mod=1e9+7;
int t,n,l,r,opt,x,y,z,p,q,ans;
int sum[N][2];//常数项、未知数的系数 
bool vis[N];
struct node{
	int v,w;
};
vector<node>g[N];
void init(){//初始化 
	for(int i=1;i<=n;i++){
		g[i].clear();
	}
	memset(vis,0,sizeof(vis));
	memset(sum,0,sizeof(sum));
	ans=1;
}
void dfs(int u){
	int s=l-sum[u][0],t=r-sum[u][0];//判断上限和下限 
	if(sum[u][1]<0){
		int k=t;
		t=-s;s=-k;
	}
	p=max(p,s);q=min(q,t);
	
	vis[u]=1;//正常遍历 
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i].v,w=g[u][i].w;
		if(vis[v])continue;
		sum[v][0]=w-sum[u][0];//算出点v的点权 
		sum[v][1]=-sum[u][1];
		dfs(v);
	}
}
signed main(){
	cin >>t;
	while(t--){
		cin >>n>>l>>r;
		init();
		for(int i=1;i<n;i++){//输入 
			cin >>opt>>x>>y;
			if(opt==1){//只添加有边权的边 
				cin >>z;
				g[x].push_back({y,z});
				g[y].push_back({x,z});
			}
		}
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				p=l;q=r;
				sum[i][0]=0;
				sum[i][1]=1;
				dfs(i);
				ans=ans*max(0ll,q-p+1)%mod;//计算答案 
			}
		}
		cout <<ans<<endl;//输出 
	}
	return 0;
}

```

---

## 作者：TernaryTree (赞：1)

首先“没有边权”没啥用。当 $op=0$ 时，我们就不建边。这样我们得到了一个森林。对于每棵树求解，然后答案乘积即可。

现在我们得到了一个带权森林。对于每一棵树，我们钦定一个点为根，将 $0$ 作为这个点的点权。然后 dfs 一遍求出每个点的点权。

手玩一下可以发现，当根的点权增加 $k$ 时，深度为偶数（即距根节点距离为偶数）的点点权增加 $k$，其他点点权减少 $k$。于是求出 $0$ 代入后奇偶深度的最小值与最大值，然后解不等式组即可。

记得特判不等数组无解。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

struct ios {
    inline char read() {
        static const int inlen = 1 << 18 | 1;
        static char buf[inlen], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, inlen, stdin)), s == t ? -1 : *s++;
    }
    template<typename T> inline ios& operator>> (T &x) {
        static char c11, boo;
        for (c11 = read(), boo = 0; !isdigit(c11); c11 = read()) {
            if (c11 == -1) return *this;
            boo |= c11 == '-';
        }
        for (x = 0; isdigit(c11); c11 = read()) x = x * 10 + (c11 ^ '0');
        boo && (x = -x);
        return *this;
    }
} fin;

struct exios {
    template<typename _CharT, typename _Traits = char_traits<_CharT>>
    struct typ {
        typedef basic_ostream<_CharT, _Traits>& (* end) (basic_ostream<_CharT, _Traits>&);
    };

    template<typename T> friend exios &operator<<(exios &out, T num) {
        if (num < 0) putchar('-'), num = -num;
        if (num >= 10) out << num / 10;
        putchar(num % 10 + '0');
        return out;
    }

    friend exios &operator<<(exios &out, const char * s) { printf("%s", s); return out; }
    friend exios &operator<<(exios &out, string s) { cout << s; return out; }
    friend exios &operator<<(exios &out, typ<char>::end e) { puts(""); return out; }
} fout;

const int maxn = 2e5 + 1;
const int mod = 1e9 + 7;
const int inf = 1e15;

struct edge {
    int to, next, w;
};

int t, n, l, r;
int head[maxn];
edge e[maxn << 1];
int cnt;

void add_edge(int u, int v, int w) {
    e[++cnt].to = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt;
}

int dep[maxn];
int val[maxn];
int mn[2], mx[2];
int lans, rans, ans = 1, tot;

void dfs(int u, int fa, int vl) {
    ++tot;
    dep[u] = dep[fa] + 1;
    val[u] = vl;
    mn[dep[u] & 1] = min(mn[dep[u] & 1], val[u]);
    mx[dep[u] & 1] = max(mx[dep[u] & 1], val[u]);
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs(v, u, e[i].w - vl);
    }
}

void intersec(int l, int r) {
    if (lans < l) lans = l;
    if (rans > r) rans = r;
}

signed main() {
    fin >> t;
    while (t--) {
        memset(dep, -1, sizeof(dep));
        memset(val, 0, sizeof(val));
        memset(head, 0, sizeof(head));
        memset(e, 0, sizeof(e));
        cnt = 0, ans = 1;
        fin >> n >> l >> r;
        int op, u, v, w;
        for (int i = 1; i <= n - 1; i++) {
            fin >> op >> u >> v;
            if (!op) continue;
            fin >> w;
            add_edge(u, v, w);
            add_edge(v, u, w);
        }
        for (int i = 1; i <= n; i++) {
            if (!~dep[i]) {
                mn[0] = mn[1] = inf;
                mx[0] = mx[1] = -inf;
                tot = 0;
                dfs(i, 0, 0);
                if (tot == 1) {
                    // cout << i << " " << (r - l + 1) << endl;
                    ans = ans * ((r - l + 1) % mod) % mod;
                    continue;
                }
                lans = -inf, rans = inf;
                intersec(l - mn[0], r - mn[0]);
                intersec(l - mx[0], r - mx[0]);
                intersec(mn[1] - r, mn[1] - l);
                intersec(mx[1] - r, mx[1] - l);
                // cout << i << " " << (rans - lans + 1) << endl;
                if (lans <= rans) ans = ans * ((rans - lans + 1) % mod) % mod;
                else ans = 0;
            }
        }
        fout << ans << endl;
    }
    return 0;
}

```

---

## 作者：出言不逊王子 (赞：0)

给定一棵树，有些边有边权。

你需要给点定权，满足一条带边权的边两边的点权和是边权。

每个点的点权 $u_i$ 均满足 $l\le u_i\le r$，问一共有多少种定权的方式。

如果每条边都没边权，那么每个点互不干扰，答案就是 $(r-l+1)^n$。

这启发我们，没有边权的边可以忽略，于是这棵树成为了一个个连通块。

那么我们只需要考虑每个连通块的答案就好了。

假设你已经知道了一个连通块中一个点（点 $A$）的点权 $u$，那么假设和这个点相连的边的边权是 $e$，那么这条边对面的点（点 $B$）的点权就是 $e-u$。再来一条边权是 $f$ 的边和 $B$ 相连，则这条边对面的点（点 $C$）的点权就是 $f-(e-u)=f-e+u$。

以此类推，只要我们确定了一个点的点权，连通块中所有的点的点权都能被确定下来。

所以我们需要知道每个连通块中点权的范围。不难发现这就是个解不等式的过程。遍历整张图，在遍历每条边的时候更新当前点权的情况，引入新的不等式即可。

考虑我们上面提到的例子：如果连通块中只有 $A$，那么范围是 $l\le u\le r$。引入 $B$ 后，多了一个 $l\le e-u\le r$ 的限制，也就是 $e-r\le u\le e-l$。再引入 $C$，又多了一个 $l\le f-e+u\le r$ 的限制，得 $e-f+l\le u\le r-f+e$。

上面的不等式有两种：
- $l\le d+u\le r$
- $l\le d-u\le r$

分别解这两种不等式就好了。

把这些限制取个交集，就是这个连通块的答案了。

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
#define mid (l+r>>1)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=200001,inf=1e9+7;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int ksm(int x,int y){
	int r=1;while(y){if(y&1)r=r*x%inf;x=x*x%inf;y>>=1;}
	return r;
}
struct edge{int v,nx,w,op;}e[N<<1];
int hd[N],totm,n,l,r,p,fa[N],res,li,ri,vis[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void mrg(int x,int y){
	x=find(x),y=find(y);
	fa[x]=y;
}
void add(int u,int v,int w,int op){
	e[++totm].v=v;e[totm].nx=hd[u];
	hd[u]=totm;e[totm].w=w;e[totm].op=op;
} 
void dfs(int now,int pm,int delta){
	vis[now]=1;
	if(pm==1) li=max(li,l-delta),ri=min(ri,r-delta);
	if(pm==-1) li=max(li,delta-r),ri=min(ri,delta-l);
	for(int i=hd[now];i;i=e[i].nx){
		int v=e[i].v;if(vis[v]||!e[i].op) continue;
		dfs(v,pm*-1,e[i].w-delta);
	}
}
void mian(){
	n=read(),l=read(),r=read();p=1,totm=0,res=1;fs(i,1,n,1) hd[i]=0,fa[i]=i,vis[i]=0;
	fs(i,1,n-1,1){
		int op=read(),u=read(),v=read(),w=0;if(op) w=read(),p=0;
		add(u,v,w,op);add(v,u,w,op);if(op) mrg(u,v);
	}
	if(p==1) return void(cout<<ksm(r-l+1,n)<<'\n');
	fs(i,1,n,1){
		if(fa[i]==i&&!vis[i]){
			li=l,ri=r;
			dfs(i,1,0);
			if(ri-li<0) return void(puts("0"));
			(res*=(ri-li+1))%=inf;
		}
	}
	cout<<res<<'\n';
}
signed main(){
	int t=read();while(t--) mian();
	return 0;
}
//把树木按照有无边权拆成一个个连通块，分开讨论
//假设当前我的点权是x，则其他点的点权都能被确定下来（45p）
//就是合法性的问题：选一个叶子，其点权可以为[l,r]，对吧
```

---

