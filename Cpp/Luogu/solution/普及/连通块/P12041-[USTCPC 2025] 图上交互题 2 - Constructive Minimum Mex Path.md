# [USTCPC 2025] 图上交互题 2 / Constructive Minimum Mex Path

## 题目背景

USTCPC 设置 3s 时限为了使得 python 通过。洛谷改为 1s 时限。

2024 年 1 月 13 日 15:59:31，随着最后一发交互 J 题的提交出现了 Wrong Answer，小 G 的 EC-Final 比赛结束了，也意味着在 ICPC 生涯中第一次打铁。

克露丝卡尔酱想要帮助她的同学小 G！她打算批量生产交互题给小 G 做。如何批量生产交互题？只要在一个数据结构中有若干个未知量 $a_i$，每次询问给定向量 $x$，交互库会返回关于 $a_i$ 的函数 $f(x)$，这样就能批量生产交互题了！

~~为什么题目名里有 2 呢？~~

## 题目描述

给定一个 $n$ 个点，$m$ 条边的**无向图**。第 $i$ 条边 $(u_i,v_i)$ 有一个**未知边权** $a_i$。

对于任何一条**路径**，定义其**代价**如下：设路径为 $(p_0,p_1,...,p_k)$，其中要求 $(p_{i-1},p_i)$ 是无向图中的边，设其为第 $e_i$ 条边。那么路径的代价即为 $\mathop{\text{mex}}\limits_{i=1}^{k} a_{e_i}$。（该路径可以经过重复点和重复边，即 $p$ 和 $e$ 可以包含重复的数）

$\text{mex}$ 是一种定义域为一个非负整数的可重集合，函数值为非负整数的映射，定义为集合内最小未在集合内出现过的非负整数。

定义 $f(x,y)$ 为从 $x$ 到 $y$ 的所有路径中代价的**最小值**。特别地，当 $x=y$ 时，$f(x,y)=0$。

给定 $n,m$，再对于每条边 $(u_i,v_i)$ 给定 $f(u_i,v_i)$，你需要求出是否存在一组合法的 $a_i$，如果有解，你还需要构造一组解。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/z3pthk3a.png)

考虑 $f(1,2)$：

+ 考虑路径 $1\rightarrow 2$，路径的代价为 $\text{mex}\{0\}=1$。
+ 考虑路径 $1\rightarrow 2\rightarrow 3\rightarrow 1\rightarrow 2$，路径的代价为 $\text{mex}\{0,1,2,0\}=3$。
+ 考虑路径 $1\rightarrow 3\rightarrow 2$，路径的代价为 $\text{mex}\{1,2\}=0$。

此外还存在其他路径，但可以证明不存在代价比 $0$ 更小的路径，故 $f(1,2)=0$。

## 样例 #1

### 输入

```
4 4
1 2 0
2 3 0
3 1 0
3 4 1```

### 输出

```
Yes
0 1 2 0```

## 样例 #2

### 输入

```
1 1
1 1 114514```

### 输出

```
NO```

# 题解

## 作者：ELECTRODE_kaf (赞：2)

注意到 $u_i$ 和 $v_i$ 之间存在一条长度为 $1$ 的直接连边，所以这个路径的贡献为 $0$ 或 $1$，故 $\forall f(x)\le 1$，否则无解。

若 $f(x)=1$，则 $a=0$，且 $u_i$ 和 $v_i$ 之间任意其他路径上至少存在一个边权为 $0$。将所有边权为 $0$ 的边删除，若这两点连通则无解，跑 DFS 检验连通性。否则令 $a=1$，可构造一组合法方案。

```
const ll N=1e5+10;
ll n,m,f[N],bl[N],bcnt;
vector<ll> e0[N],e1[N];

void dfs(ll p){
	bl[p]=bcnt;
	
	for(ll i:e1[p]){
		if(bl[i]) ctn;
		
		dfs(i);
	}
}

int main(){
	cin>>n>>m;
	
	rep(i,1,m){
		ll u,v;
		cin>>u>>v>>f[i];
		
		if(f[i]>1){
			cout<<"no";
			return 0;
		}else if(f[i]==1){
			e0[u].pb(v);
			e0[v].pb(u);
		}else{
			e1[u].pb(v);
			e1[v].pb(u);
		}
	}

	rep(i,1,n){
		if(bl[i]==0){
			bcnt++;
			dfs(i);
		}
	}
	
	rep(i,1,n){
		for(ll j:e0[i]){
			if(bl[i]==bl[j]){
				cout<<"no";
				return 0;
			}
		}
	}
		
	cout<<"yes\n";
	
	rep(i,1,m) cout<<(f[i]^1)<<' ';
}
```

---

## 作者：hgckythgcfhk (赞：1)

广告：[USTCPC2025 题解汇总（部分）](https://www.luogu.com.cn/article/xl8dsc9j)。

注意到最小值，所以显然直接走现成的边是比较优的，如果这条边大于 $0$，则答案一定是 $0$，否则考虑周围是否有全大于 $0$ 的环，有则答案是 $0$，否则答案是 $1$，所以如果输入的时候有大于 $1$ 的边一定无解。

因为边权只有两种，所以可以分开考虑，先把 $f(u,v)=0$ 的边加上，这种边最好的处理方式是全放 $1$，因为我们要兼顾剩下的边，所以真的全放 $1$ 是不太优的，但考虑到把某条边设为 $0$ 后一定有另一条全 $1$ 的路径，对于别的边，如果真的要走这两个点之间的路径完全可以绕路不直接走这两个点之间的边，所以这条边设为 $0$ 是没用的。

于是可以发现每条边的权值其实是确定的，只需要最后判这样赋权是否合法就行。

同时根据上对 $1$ 的连通块的处理，我们先加入 $1$ 边后的连通块两两的 $f$ 等于 $0$，所以，同一个连通块内出现 $f(u,v)=1$ 的边是不合法的，而对于跨连通块的情况由于现在只需要加入 $0$ 的边，所以无论怎么连都是不影响的。

其实看到上面 $f$ 是 $0$ 的条件就可以观察出来 $1$ 相当于是有边 $0$ 相当于是没边，因为上面的描述提示了我们要尽量不走 $0$ 的边。

 以下是线下选手 $42$ 队提供的赛时代码，非常感谢 $42$ 队。

```cpp
#include<iostream>
using namespace std;
const int N=2e5+10;
typedef long long ll;
int n,m,pa[N],a[N];
bool ans=false;
struct bc{
	int u,v;
	ll w;
}b[N];
int fd(int x){
	if(pa[x]==x)return x;
	else return pa[x]=fd(pa[x]);
}
void adp(int x,int y){
	int xf=fd(x),yf=fd(y);
	if(xf!=yf)pa[yf]=xf;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)pa[i]=i;
	for(int i=1;i<=m;i++){
		scanf("%d%d%lld",&b[i].u,&b[i].v,&b[i].w);
		if(b[i].u==b[i].v && b[i].w!=0)ans=true;
		else if(b[i].w==0)adp(b[i].u,b[i].v);
		else if(b[i].w>1)ans=true;
	}
	if(ans){
		printf("No");
		return 0;
	}
	for(int i=1;i<=m;i++){
		if(b[i].w==0){
			a[i]=1;
		}else if(b[i].w==1){
			a[i]=0;
			if(fd(b[i].u)==fd(b[i].v))ans=true;
		}
	}
	if(ans){
		printf("No");
	}else{
		printf("Yes\n");
		for(int i=1;i<=m;i++)printf("%d ",a[i]);
	}
	return 0;
}

---

## 作者：R_shuffle (赞：1)

我们经过思考可以发现，由于我们要求 $\rm mex$ 的最小值，所以不妨直接考虑两个直接有边相连的点，考察这条边的权值，我们发现，若这条边的权值不为 $0$，那么 $\rm mex$ 的最小值一定为 $0$ ，否则我们不确定 $\rm mex$ 的最小值，但是我们发现 $\rm mex$ 最大不会超过 $1$。由这两条性质，我们可以先行判断一些无解情况。如果输入的有大于 $1$ 的情况就直接判无解就行了。同样的，由上面的两条性质，我们可以肯定的是，如果有解，显然是可以通过边权为 $0$ 或 $1$ 的边构造出来。

考虑构造的过程，由上面的结论，我们可以想到一个最简单的的构造，就是直接把点对之间的 $\rm mex$ 为 $0$ 的连一条 $1$ 的边，把 $\rm mex=1$ 的连一条 $0$ 的边。我们发现这种构造可能会有问题，就是我们并不能保证点对的 $\rm mex=1$ 的其他路径也是至少有 $1$ 个 $0$ 的边，那么问题就在于，按照我们这种构造方案，我们对于那些边权为 $1$ 的边是十分确定的，不可能替换成其他的权值。所以实际上如果我们发现按照这种构造会使得点对的 $\rm mex=1$ 不成立，那么这种情况也是无解的。

具体实现可以用并查集简单实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>gra[100005];
vector<pair<int,int> >wc;
int fa[1000005];
int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
void Union(int u,int v)
{
    u=find(u),v=find(v);
    if(u==v) return ;
    fa[u]=v;
}
signed main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) fa[i]=i;
    vector<int>ans;
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        if(w>1)
        {
            cout<<"No\n";
            return 0;
        }
        if(w==0)
        {
            Union(u,v);
        }
        else
            wc.push_back(make_pair(u,v));
        ans.push_back(w^1);
    }
    for(auto [u,v]:wc)
    {
        if(find(u)==find(v))
        {
            cout<<"No\n";
            return 0;
        }
    }
    cout<<"Yes\n";
    for(auto v:ans) cout<<v<<" ";
}
```

---

## 作者：Jorisy (赞：0)

搞笑题。

对于边 $(u,v,a)$，若 $a>0$，那么 $f(u,v)=0$；若 $a=0$，那么 $f(u,v)\le 1$。所以若存在 $f(u,v)>1$ 必然无解。

若 $f(u,v)=0$，由于 $u,v$ 之间必然存在一条边，那么你只要令 $a=1$ 即可。

若 $f(u,v)=1$，那么我们至少首先要 $a=0$，并且此时我们不存在一条 $u$ 到 $v$ 的路径，满足路径上的边权都 $>0$。

将边权为 $0$ 的边全部删去，就变成了 $f(u,v)=1$ 的点不在同一连通块。并查集维护即可。

```cpp
#include<bits/stdc++.h>
#define N 100005
#define ll long long
#define mod 
using namespace std;

struct edge{
    int u,v,f;
}e[N];
struct dsuni{
    int fa[N];
    void init(int n){iota(fa+1,fa+n+1,1);}
    int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
    void merge(int u,int v){fa[find(v)]=find(u);}
}dsu;
int n,m,ans[N];

int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    dsu.init(n);
    for(int i=1;i<=m;i++)
    {
        int u,v,f;
        cin>>u>>v>>f;
        if(f>1)
        {
            cout<<"No";
            return 0;
        }
        e[i]={u,v,f};
        ans[i]=!f;
    }
    for(int i=1;i<=m;i++)
    {
        if(!ans[i]) continue;
        auto [u,v,f]=e[i];
        dsu.merge(u,v);
    }
    for(int i=1;i<=m;i++)
    {
        if(ans[i]) continue;
        auto [u,v,f]=e[i];
        if(dsu.find(u)^dsu.find(v)) continue;
        cout<<"No";
        return 0;
    }
    cout<<"Yes\n";
    for(int i=1;i<=m;i++) cout<<ans[i]<<' ';
    return 0;
}
```

---

## 作者：VinstaG173 (赞：0)

诈骗题。

显然 $u_i,v_i$ 间有一条路径只有一条边 $(u_i,v_i)$，这条路径的代价为 $\operatorname{mex}(\{a_i\})\le1$。因此只要有 $f(x,y)>1$ 即无解。

若 $f(u_i,v_i)=1$，则说明 $a_i=0$，且 $u_i,v_i$ 间任意路径上都有至少一条边的权值为 $0$。也就是说，将图中所有权值为 $0$ 的边删除后这些点对 $(u_i,v_i)$ 将不连通。

此时对于 $f(u_i,v_i)=0$，由于存在一条 $u_i,v_i$ 间的路径上没有边权为 $0$，在上述删除的图中 $(u_i,v_i)$ 连通，我们可以直接视为 $a_i=1$ 即边 $(u_i,v_i)$ 不被删除，这不会使得图的连通性更优。

那么我们只保留所有 $f(u_i,v_i)=0$ 的边时，一旦有一对 $f(u_i,v_i)=1$ 的边两端在同一个连通块，则无解；否则容易发现上述构造即为满足要求的一个图。

时间与空间复杂度均为 $O(n+m)$。

Code:
```cpp
int n,m,flag;
int d[100003];
int w[100003];
set<int>nx[100003];
vector<int>e[100003];

int vs[100003],cnt;
void dfs(int u){vs[u]=cnt;
	for(int i=0,v;i<d[u];++i){
		v=e[u][i];
		if(vs[v])continue;
		dfs(v);
	}
}

inline void solve(){
	cin>>n>>m;
	for(int i=0,u,v;i<m;++i){
		cin>>u>>v>>w[i];
		if(w[i]>1){
			cout<<"No\n";
			return;
		}else if(w[i]==1){
			nx[u].insert(v);
			nx[v].insert(u);
			continue;
		}++d[u],++d[v];
		e[u].push_back(v);
		e[v].push_back(u);
	}flag=1;cnt=0;
	for(int i=1;i<=n;++i){
		if(!vs[i]){
			++cnt;dfs(i);
		}
	}
	
	set<int>::iterator it;
	for(int i=1,j;i<=n;++i){
		for(it=nx[i].begin();it!=nx[i].end();++it){
			j=*it;if(vs[i]==vs[j]){
				flag=0;break;
			}
		}if(!flag)break;
	}
	
	if(!flag){
		cout<<"No\n";
		return;
	}cout<<"Yes\n";
	for(int i=0;i<m;++i)
		cout<<(w[i]^1)<<" \n"[i==m-1];
}
```

---

