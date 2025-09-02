# [USTCPC 2025] 图上交互题 3 / Constructive Maximum Mex Path

## 题目背景

USTCPC 设置 3s 时限为了使得 python 通过。洛谷改为 1s 时限。

2024 年 12 月 28 日 14:59:50，随着最后一发 E 题的提交出现了 Wrong Answer，小 G 的 EC-Final 比赛结束了。

小 G 的 EC-Final 连续两年都在不同的细节题上倒闭了。克露丝卡尔酱想要帮助她的同学小 G！很可惜细节题是不能批量生产的，但刚好克露丝卡尔酱想到了这样一个细节题，考验大家的细节题能力。希望大家不要在细节题上倒闭！

~~为什么这个系列的题目还在继续呢？~~

## 题目描述

给定一个 $n$ 个点，$m$ 条边的**无向图**。第 $i$ 条边 $(u_i,v_i)$ 有一个**未知边权** $a_i$。

对于任何一条**路径**，定义其**代价**如下：设路径为 $(p_0,p_1,...,p_k)$，其中要求 $(p_{i-1},p_i)$ 是无向图中的边，设其为第 $e_i$ 条边。那么路径的代价即为 $\mathop{\text{mex}}\limits_{i=1}^{k} a_{e_i}$。（该路径可以经过重复点和重复边，即 $p$ 和 $e$ 可以包含重复的数）

$\text{mex}$ 是一种定义域为一个非负整数的可重集合，函数值为非负整数的映射，定义为集合内最小未在集合内出现过的非负整数。

定义 $f(x,y)$ 为从 $x$ 到 $y$ 的所有路径中代价的**最大值**。

给定 $n,m$，再对于每条边 $(u_i,v_i)$ 给定 $f(u_i,v_i)$，你需要求出是否存在一组合法的 $a_i$，如果有解，你还需要构造一组解。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/chqq6le8.png)

考虑 $f(1,2)$：

+ 考虑路径 $1\rightarrow 2$，路径的代价为 $\text{mex}\{0\}=1$。
+ 考虑路径 $1\rightarrow 2\rightarrow 3\rightarrow 1\rightarrow 2$，路径的代价为 $\text{mex}\{0,1,114514,0\}=2$。
+ 考虑路径 $1\rightarrow 3\rightarrow 2$，路径的代价为 $\text{mex}\{1,114514\}=0$。

此外还存在其他路径，但可以证明不存在代价比 $2$ 更大的路径，故 $f(1,2)=2$。

## 样例 #1

### 输入

```
3 3
1 2 2
2 3 2
3 1 2```

### 输出

```
Yes
0 1 114514```

## 样例 #2

### 输入

```
1 1
1 1 114514```

### 输出

```
NO```

# 题解

## 作者：hgckythgcfhk (赞：1)

广告：[USTCPC2025 题解汇总（部分）](https://www.luogu.com.cn/article/xl8dsc9j)。

由于路径可以不是简单路径，所以为了使得 $\operatorname{mex}$ 最大一定会走完整个连通块的每一条边，这样一定不劣，所以两个点的  $f$ 等价于这两个点所在连通快的  $\operatorname{mex}$，只需要构造一个连通块有 $0$ 到 $f(u,v)-1$ 就行，然后如果连通块边数不够或者里面的边的 $f$ 不相等则无解。

 以下是线下选手 $42$ 队提供的赛时代码，非常感谢 $42$ 队。

```cpp
#include <bits/stdc++.h>
#define il inline
#define rg register
#define cit const rg unsigned
#define open ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)//,freopen("I.in","r",stdin),freopen("I.out","w",stdout)
#define int rg unsigned
#define void il void
#define ll long long
#define ull unsigned ll
#define lll __int128
#define db double
#define vector basic_string
#define pq priority_queue
#define vint vector<unsigned>
#define vll vector<ll>
#define vull vector<ull>
#define ump unordered_map
#define ust unordered_set
#define deq deque
#define mkp make_pair
#define pii pair<unsigned,unsigned>
#define pll pair<ull,ull>
#define fi first
#define se second
#define Bool(a,n) bitset<n>a
#define sca(a) for(int $=0;$<n;cin>>a[++$])
#define cle(a) memset(a,0,sizeof a)
#define tmx(a) memset(a,0x3f,sizeof a)
#define tmn(a) memset(a,0xbf,sizeof a)
#define tif(a) memset(a,0xff,sizeof a)
//#define ge getchar_unlocked()
#define pu putchar_unlocked
#define lik(x) __builtin_expect((x),1)
#define ulk(x) __builtin_expect((x),0)
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
//#define abs(a,b) (a>b?a-b:b-a)
#define fls cout<<endl;
#define PP pop_back()
#define PS push
#define BK back()
#define SZ size()
//inline ll max(const rg ll a,const rg ll b){return a>b?a:b;}
//inline ll min(const rg ll a,const rg ll b){return a<b?a:b;}
inline ll abs(const rg ll a,const rg ll b){return a>b?a-b:b-a;}
using namespace std;constexpr unsigned N=1e6+1,M=4e3+2;//constexpr ll inf=1e9+7;
//unsigned p;
constexpr unsigned p=998244353;
//constexpr unsigned p=1e9+7;
//自动取模类
/**/
namespace mod{
	void add(int&a,cit b){a+=b,a>=p?a-=p:0;}
	void sub(int&a,cit b){add(a,p-b);}
	il unsigned mul(cit ll a,cit ll b){return a*b%p;}
	il unsigned pw(int ll a,int b){int ll s=1;for(;b;b>>=1,a=a*a%p)b&1?s=s*a%p:0;return s;}
	il unsigned inv(cit a){return pw(a,p-2);}
	void div(int&a,cit b){a=mul(a,inv(b));}
	il unsigned div(cit a,cit b){return mul(a,inv(b));}
}
using mod::add;
using mod::sub;
using mod::mul;
using mod::inv;
using mod::pw;
/**/
namespace IO{unsigned char b[1<<22],*l=b,*r=b;
	#define ge (ulk(l==r)?r=(l=b)+fread(b,1,1<<22,stdin):0,ulk(l==r)?'\0':*l++)
	il unsigned rd(){int char c=ge;int s=0;while(c<48||c>58)c=ge;while(lik(c<59&&c>47))s=s*10+(c&0b1111),c=ge;return s;}
	void rd(int&s){int char c=ge;s=0;while(c<48||c>58)c=ge;while(lik(c<59&&c>47))s=s*10+(c&0b1111),c=ge;}
}using IO::rd;
unsigned n,m;struct A{unsigned u,v,w;}e[N];vint a[N];
unsigned b[N],ans[N];vint c[N];
void dfs(cit u,cit rt){b[u]=rt;for(cit&v:a[u])if(!b[v])dfs(v,rt);}
void init(){rd(n),rd(m);
    for(int i=1;i<=m;++i)rd(e[i].u),rd(e[i].v),rd(e[i].w),a[e[i].u]+=e[i].v,a[e[i].v]+=e[i].u;
    for(int i=1;i<=n;++i)if(!b[i])dfs(i,i);
    for(int i=1;i<=m;++i)c[b[e[i].u]]+=i;

}void solve(){init();
    for(int i=1;i<=n;++i)if(c[i].SZ){int id=0;
        for(cit&j:c[i])if(!id)id=e[j].w;
        else if(id^e[j].w){cout<<"No\n";return;}
        if(id>c[i].SZ){cout<<"No\n";return;}
        for(int j=0;j<id;++j)ans[c[i][j]]=j;
        for(int j=id;j<c[i].SZ;++j)ans[c[i][j]]=p;
    }cout<<"Yes\n";for(int i=1;i<=m;++i)cout<<ans[i]<<' ';
}signed main(){open;int t=1;//cin>>t;
	while(t--)solve();}
```

删除了引用的被注释掉的 `hgckythgcfhk.h` 的内容，保证这部分全是注释。

---

## 作者：Jorisy (赞：0)

注意到路径可以经过重复边、点，那么相当于我们要选择一个包含 $u,v$ 的连通块，最大化其边权集 $\text{mex}$。

显然我们把 $u,v$ 所在的**极大连通块**内的**所有**边全选上就好了。

然后注意到在同一连通块内的 $f$ 必然相等，因为他们是本质相同的。

假设我们要构造一个连通块内的边 $\text{mex}=k$，那么我们就需要边权 $=0\sim k-1$ 的边，且不能存在边权 $=k$ 的边，这个很容易处理。

然后就做完了。

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
    int fa[N],sz[N],cnt[N];
    void init(int n){iota(fa+1,fa+n+1,1);fill(sz+1,sz+n+1,1);}
    int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
    int size(int x){return sz[find(x)];}
    int edge(int x){return cnt[find(x)];}
    void merge(int u,int v)
    {
        u=find(u);
        v=find(v);
        cnt[u]++;
        if(u==v) return;
        fa[v]=u;
        sz[u]+=sz[v];
        cnt[u]+=cnt[v];
    }
}dsu;
vector<int>vec[N];
int n,m,ans[N],w[N];

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
        dsu.merge(u,v);
        e[i]={u,v,f};
    }
    fill(w+1,w+n+1,-1);
    for(int i=1;i<=m;i++)
    {
        auto [u,v,f]=e[i];
        int t=dsu.find(u);
        if(w[t]>=0&&w[t]!=f||f>dsu.edge(u))
        {
            cout<<"No";
            return 0;
        }
        w[t]=f;
        vec[t].push_back(i);
    }
    for(int i=1;i<=n;i++)
    {
        if(vec[i].empty()) continue;
        int t=w[i];
        for(int j=0;j<vec[i].size();j++) ans[vec[i][j]]=j+(j==t);
    }
    cout<<"Yes\n";
    for(int i=1;i<=m;i++) cout<<ans[i]<<' ';
    return 0;
}
```

---

## 作者：VinstaG173 (赞：0)

诈骗题。

显然两点间的路径代价最大可以在路径走遍整个连通块中所有边时取到，因此一个连通块内的所有边的代价 $f(u_i,v_i)$ 都应当相等，否则无解。这个代价不应该超过连通块内的边数，否则无解。

判断掉无解情况之后对于每个连通块，只要把连通块内边权任意顺序设定为从小到大的自然数，取值跳过连通块内的代价即可。

可以用并查集维护，注意一些实现细节。时间复杂度 $O((n+m)\alpha(n))$，空间复杂度 $O(n+m)$。

Code:
```cpp
int n,m,flag;
int f[100003];
int wgt[100003];
int szv[100003];
int sze[100003];
int gf(int x){
	return (x==f[x])?x:f[x]=gf(f[x]);
}inline void merge(int x,int y){
	int fx=gf(x),fy=gf(y),tmp;
	if(fx==fy){
		++sze[fx];return;
	}if(wgt[fx]<0)wgt[fx]=wgt[fy];
	if(wgt[fy]<0)wgt[fy]=wgt[fx];
	if(wgt[fx]!=wgt[fy]){
		flag=0;return;
	}if(szv[fx]<szv[fy])tmp=fx,fx=fy,fy=tmp;
	f[fy]=fx;szv[fx]+=szv[fy];
	sze[fx]+=(sze[fy]+1);
}

int u[100003];
int v[100003];
int w[100003];
int cnt[100003];
inline void solve(){
	cin>>n>>m;flag=1;
	for(int i=1;i<=n;++i)
		f[i]=i,wgt[i]=-1,cnt[i]=0;
	for(int i=0;i<m;++i){
		cin>>u[i]>>v[i]>>w[i];
		merge(u[i],v[i]);
		if(!flag)break;
		if(wgt[gf(u[i])]<0)
			wgt[f[u[i]]]=w[i];
		if(w[i]!=wgt[f[u[i]]]){
			flag=0;break;
		}
	}
	
	for(int i=1;i<=n;++i){
		if(f[i]!=i)continue;
		if(wgt[i]==-1)continue;
		if(sze[i]<wgt[i]){
			flag=0;break;
		}
	}
	
	if(!flag){
		cout<<"No\n";
		return;
	}cout<<"Yes\n";
	for(int i=0;i<m;++i){
		if(cnt[gf(u[i])]==wgt[gf(u[i])])
			++cnt[f[u[i]]];
		cout<<cnt[f[u[i]]]<<" ";
		++cnt[f[u[i]]];
	}
}
```

---

