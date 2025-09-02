# Baggage Claim

## 题目描述

每个机场都有一个行李提取区，Balbesovo 机场也不例外。某天，Sheremetyevo 机场的一位管理员提出了一个不同寻常的想法：将传统的行李传送带形状从旋转盘改为更复杂的形式。

假设行李提取区被表示为一个 $n \times m$ 的矩形网格。管理员提议传送带的路径应穿过单元格 $p_1, p_2, \ldots, p_{2k+1}$，其中 $p_i = (x_i, y_i)$。

对于每个单元格 $p_i$ 和下一个单元格 $p_{i+1}$（其中 $1 \leq i \leq 2k$），这两个单元格必须共享一条公共边。此外，路径必须是简单的，即对于任意两个不同的索引 $i \neq j$，单元格 $p_i$ 和 $p_j$ 不能重合。

不幸的是，路径计划被意外洒出的咖啡弄脏了，只保留了路径中奇数索引的单元格：$p_1, p_3, p_5, \ldots, p_{2k+1}$。你的任务是给定这些 $k+1$ 个单元格，计算恢复原始完整路径 $p_1, p_2, \ldots, p_{2k+1}$ 的可能方式的数量。

由于答案可能非常大，请输出其对 $10^9+7$ 取模的结果。

## 说明/提示

在第一个测试用例中，有两种可能的路径：

- $(1,1) \to (2,1) \to (2, 2) \to (2, 3) \to (2, 4)$
- $(1,1) \to (1,2) \to (2, 2) \to (2, 3) \to (2, 4)$

在第二个测试用例中，没有合适的路径，因为单元格 $(1,1)$ 和 $(1,4)$ 没有共同的相邻单元格。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2 4 2
1 1
2 2
2 4
1 4 1
1 1
1 4
5 5 11
2 5
3 4
4 5
5 4
4 3
5 2
4 1
3 2
2 1
1 2
2 3
1 4
3 4 4
1 2
2 1
3 2
2 3
3 4
3 3 2
2 2
1 1
1 3```

### 输出

```
2
0
2
5
1```

# 题解

## 作者：littlebug (赞：7)

脑子不够用了 /ll

## Solution

我们发现如果两个相邻已知位置是对角线的关系，那么就是在剩下的两个位置里面任选一个，且不能重复选，那么可以想到，把位置当成点，上面所说的条件当成边，这样建图。

于是就相当于每条边占有它的一个端点，且两条不同的边不能占有同一个点的方案数，分讨下就解决了，具体地：

- 如果 $E>V$，显然无解。
- 如果 $E = V - 1$，考虑哪个点不被占有，方案数为 $V$。
- 如果 $E = V$，也就是一个环，那么考虑顺时针选还是逆时针选，方案数为 $2$。

然后，对于两个位置不是对角线关系的，显然可以直接特判掉，但是有一个更简便的方法。还是按照上面的模型，那么这种情况就相当于一个点连了一个自环，需要注意的是自环的方案数只有 $1$，需要特判。

## Code

```cpp
int n,m,k;
vector <int> p[N*N];
bitset <N*N> slf;

il int calc(int x,int y) {return (x-1)*m+y;}
il void adde(int u,int v) {p[u].pb(v),p[v].pb(u),u==v && (slf[u]=1);}

bitset <N*N> vis;
struct result{int V,E; bool op;};
il result dfs_c(int u)
{
	result ans=(result){1,p[u].size(),!slf[u]},res;
	for(auto v:p[u]) if(!vis[v])
	{
		vis[v]=1,res=dfs_c(v);
		ans.V+=res.V,ans.E+=res.E,ans.op&=res.op;
	}
	return ans;
}

il void solve()
{
	read(n,m,k);
	rep(i,1,n*m) clr(p[i]),vis[i]=0,slf[i]=0;
	
	bool ok=1;
	{
		int lx=read(),ly=read(),x,y;
		rep(i,2,k+1) 
		{
			read(x,y);
			if(abs(x-lx)+abs(y-ly)!=2) ok=0;
			
			if(abs(x-lx)==abs(y-ly)) adde(calc(x,ly),calc(lx,y));
			else if(x-lx) adde(calc(x+lx>>1,y),calc(x+lx>>1,y));
			else adde(calc(x,y+ly>>1),calc(x,y+ly>>1));
			
			lx=x,ly=y;
		}
	}
	
	if(!ok) return write(0ll,'\n');
	
	result res; int ans=1;
	rep(u,1,n*m) if(!p[u].empty() && !vis[u])
	{
		vis[u]=1,res=dfs_c(u),res.E>>=1;
		
		if(res.V<res.E) return write(0ll,'\n');
		else if(res.V-1==res.E) ans=mod_(ans*res.V);
		else if(res.op && res.V>1) ans=mod_(ans<<1);
	}
	
	write(ans,'\n');
}
```

---

华风夏韵，洛水天依！

---

## 作者：2huk (赞：4)

某梦姓机构在模拟赛中出过几乎一模一样的，怎么现在还是不会做呢？

首先如果存在相邻两个点（$p_{2i-1},p_{2i+1}$）的曼哈顿距离不是 $2$，直接输出 $0$ 结束了。然后我们考察这两个点中间的点是啥。

1. 如果这两个点的横坐标相同或纵坐标相同，那么中间这个点是唯一确定的。

2. 否则，这两个点一定横纵坐标都相差 $1$。那么中间这个点是有两种情况的。

![](https://cdn.luogu.com.cn/upload/image_hosting/fz8tpi7r.png)

我们给所有可能成为中间的点编号（就是离散化）。得到两个数组 $a_i,b_i$，表示 $p_{2i-1},p_{2i+1}$ 这两个点中间的点编号一定是 $a_i$ 或 $b_i$。当然如果是左图的情况则 $a_i=b_i$。

现在问题变成了，对于每个 $i$，选择 $a_i,b_i$ 中的恰好一个数，使得选出的 $n$ 个数互不相同，求方案数。这样的答案再除以 $2$ 的第一种情况数次幂就是真正答案。

这个咋做呢？

~~首先考虑二分图。我们连边 $i \to a_i+n,i \to b_i+n$。然后答案是这张二分图的完美匹配方案数。显然我们没有解决 NPC 问题的能力。~~

既然是两个点，我们考虑建无向图 $a_i - b_i$。那么怎么体现两个点只能选一个，且这个点在全局只能选一次呢？

考虑转化成一个给无向图的边定向的问题。具体的，如果我们给这条边定向为 $a_i \to b_i$，则表示这个位置选 $b_i$。同理，如果是 $a_i \gets b_i$，表示这个位置选 $a_i$。那么一个点至多被选一次，等价于一个点的入度 $\le 1$。

我们考虑对图中每个连痛块单独计数。最后乘起来即可。

我们考虑这个连通块中的点数 $n$ 和边数 $m$。**注意可能有自环**。显然因为联通所以 $m \ge n - 1$。

- $m = n - 1$，是一颗树。显然一定存在一个点的入度为 $0$。枚举这个点，发现剩下的边的方向都确定了。所以答案为 $n$。
- $m=n$，基环树。中间的环有两种定向方案，除非中间是个自环（此时是 $1$）。剩下的边的方向也确定了。所以答案为 $1$ 或 $2$。
- $m > n$：注意到所有点的入度和为 $m$。根据鸽巢原理，一定有一个点的入度 $> 1$。答案为 $0$。

那你不就做完了。

---

## 作者：gcx114514 (赞：4)

首先如果两个相邻的点的曼哈顿距离不为 $2$ 一定不合法，先判掉。

对于相邻的两个奇数点，如果他们是一条水平或者垂直的线，那么他们的中点一定要选，那么我们用 $0$ 号点向其连接一条有向边。对于另外的情况，选择的可能有两种，我们将这两种选择的点连接一条无向边。

由于每个点只能选择一次，那么我们将问题转换为对我们新建的图给无向边定向，使得每个点的入度最大为 $1$。

由于 $0$ 的出边已经确定，那么其所对于的连通块一定是棵树，否则答案为 $0$。

对于其他连通块（假设有 $n$ 个点，$m$ 条边），我们分讨：

1. 如果是一棵树，那么我们可以选择一个定点使其没有入边，这样就有 $n$ 中选择。
2. 如果给定的是一颗基环树，可以知道只有环上正向和反向两种选择，故对答案的贡献是 $2$。
3. 对于其他情况的答案就是 $0$（因为边数已经大于点数了，无论如何都有点的入度大于 $1$）。

对于不同连通块我们直接相乘即可。这样的复杂度是 $O(nm)$ 的，可以通过。

### Code

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb emplace_back
#define ll long long
#define mk make_pair
#define se second
#define fi first
//#define mid ((l+r)>>1)
//#define rs now<<1|1
//#define ls now<<1
using namespace std;
bool Mst;
const int Max=2e6+10;
const int mod=998244353;
const int inf=1e9+10;

inline int read(){
	int res=0,v=1;
	char c=getchar();
	while(c<'0'||c>'9'){v=(c=='-'?-1:1);c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
	return res*v;
}

template <int mod>
struct modint{

	int val;

	static int norm(const int &x){return x<0?x+mod:x;}
	static int Norm(const int &x){return x>=mod?x%mod:x;}

	modint inv()const{
		int a=val,b=mod,u=1,v=0,t;
		while(b>0)t=a/b,swap(a-=t*b,b),swap(u-=t*v,v);
		return modint(u);
	}


	modint():val(0){}
	modint(const int &m):val(norm(m)){}
	modint(const long long &m):val(norm(m%mod)){}
	modint operator -()const{return modint(norm(-val));}
	bool operator ==(const modint &x){return val==x.val;}
	bool operator !=(const modint &x){return val!=x.val;}
	bool operator <=(const modint &x){return val<=x.val;}
	bool operator >=(const modint &x){return val>=x.val;}
	bool operator >(const modint &x){return val>x.val;}
	bool operator <(const modint &x){return val<x.val;}
	modint& operator *=(const modint &x){return val=static_cast<int>(1ll*val*x.val%mod),*this;}
	modint& operator <<=(const modint &x){return val=(1ll*val<<x.val)%mod,*this;}
	modint& operator +=(const modint &x){return val=Norm(1ll*val+x.val),*this;}
	modint& operator -=(const modint &x){return val=norm(1ll*val-x.val),*this;}
	modint& operator >>=(const modint &x){return val>>=x.val,*this;}
	modint& operator ^=(const modint &x){return val^=x.val,*this;}
	modint operator >>(const modint &x){return modint(*this)>>=x;}
	modint operator <<(const modint &x){return modint(*this)<<=x;}
	modint& operator /=(const modint &x){return *this*=x.inv();}
	modint operator +(const modint &x){return modint(*this)+=x;}
	modint operator -(const modint &x){return modint(*this)-=x;}
	modint operator *(const modint &x){return modint(*this)*=x;}
	modint operator /(const modint &x){return modint(*this)/=x;}
	modint operator ^(const modint &x){return modint(*this)^=x;}
	friend std::ostream& operator<<(std::ostream& os,const modint &a){return os<<a.val;}
	friend std::istream& operator>>(std::istream& is,modint &a){return is>>a.val;}
};

typedef modint<1000000007>m17;


vector<int>v[Max];

int id[1010][1010];

void add(int x,int y){v[x].pb(y);v[y].pb(x);}

pii p[Max];


int vis[1010*1010];

int fa[Max];
int FindFa(int x){return x==fa[x]?x:fa[x]=FindFa(fa[x]);}
void merge(int x,int y){
	x=FindFa(x);y=FindFa(y);
	fa[x]=y;
}
int siz[Max],num[Max];
void dfs(int now){
	vis[now]=1;siz[now]=1;num[now]=v[now].size();
	for(auto to:v[now]){
		if(vis[to])continue;
		dfs(to);num[now]+=num[to];siz[now]+=siz[to];
	}
}

void work(){
	int n=read(),m=read(),k=read();int cnt=0;
	for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)id[i][j]=++cnt;
	for(int i=0;i<=cnt;++i)v[i].clear(),vis[i]=siz[i]=num[i]=0;
	int tag=0;
	for(int i=1;i<=k+1;++i){
		int x,y;x=read();y=read();
		p[i]=mk(x,y);
		if(i!=1){
			if(abs(x-p[i-1].fi)+abs(y-p[i-1].se)!=2){
				tag=1;
			}
			if(abs(x-p[i-1].fi)==abs(y-p[i-1].se)){
				add(id[x][p[i-1].se],id[p[i-1].fi][y]);
			}else{
				add(0,id[(x+p[i-1].fi)/2][(y+p[i-1].se)/2]);
			}
		}
	}
	if(tag){
		cout << "0\n";
		return ; 
	}
	
	for(int i=0;i<=cnt;++i)fa[i]=i;
	for(int i=0;i<=cnt;++i){
		for(auto to:v[i]){
			merge(i,to);
		}
	}
	m17 ans=1;
	for(int i=1;i<=cnt;++i){
		if(FindFa(i)!=FindFa(0)&&!vis[i]){
			dfs(i);
			if(num[i]==siz[i]*2)ans*=2;
			else if(num[i]==(siz[i]-1)*2)ans*=siz[i];
			else ans=0;
		}
	}
	dfs(0);
	if(num[0]!=(siz[0]-1)*2)ans=0;
	cout << ans << "\n";
}

bool Med;
signed main(){
	int T=read();
	while(T--)work();


	cerr<< "Time: "<<clock()/1000.0 << "s\n";
	cerr<< "Memory: " << (&Mst-&Med)/1000000.0 << "MB\n";
	return 0;
}
/*

*/

 
```

---

## 作者：MattL (赞：4)

## 题意
网格图中有一条路径，每一步只能走到相邻的边。给出第奇数步的点的坐标，问有多少条路径能满足不走重复的格子？
## 分析
- 当给出的两个相邻节点的曼哈顿距离（即要走的步数）不等于 $2$ 时，显然无解。形式地，对于 $(x_1,y_1)$ 与 $(x_2,y_2)$ 节点，满足 $|x_1-x_2|+|y_1-y_2|\neq 2$，则无解。
- 当给出的两个相邻节点为直线时，夹着的点只有一个可能，即中间的那个点。对于 $(x_1,y_1)$ 与 $(x_2,y_2)$ 节点，满足 $|x_1-x_2|=2,|y_1-y_2|\neq 0$ 或 $|x_1-x_2|=0,|y_1-y_2|\neq 2$，我们只能选择 $(\frac{x_1+x_2}{2},\frac{y_1+y_2}{2})$。
- 当给出的两个相邻节点为折线时，夹着的点有两个可能。形式地，对于 $(x_1,y_1)$ 与 $(x_2,y_2)$ 节点，满足 $|x_1-x_2|=0$ 或 $|y_1-y_2|=0$，我们可以选择 $(x_1,y_2)$ 与 $(x_2,y_1)$。

我们来考虑如何做到不走重复的格子。对于给出的相邻两个格子，我们只能选择一个。于是我们想到把这件事抽象成一张图，一条边只能选择一个节点。特别地，对于只有一种选择的，我们连自环。最后，我们希望一个节点只能被选一次，每一条边都要选其中的一个顶点。

显然这样建图不一定都联通，会形成很多个连通块。我们考虑对于每一个连通块：
- 如果这个连通块有多个环，即 $E>V$，那么一定无解。因为一条边需选择一个节点，总共需选择 $E$ 个节点，而节点没那么多。
- 若这个连通块仅有一个环，即 $E=V$，那么分两种情况
  1. 这个环是个自环，没有选择的余地，答案为 $1$。
  2. 这个环是非退化环（即自环），对于每条边都可以同时选其中一个和另外一个，答案为 $2$。
- 若这个连通块是一棵树，即 $E=V-1$，那么我只需要在这棵树里面选择一个不要的节点，其他点就都确定了。答案为 $V$。

最后，根据乘法原理把答案乘起来即可。

**注意：无解时请勿直接退出，还要清空。**

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ls (now<<1)
#define rs (now<<1|1)
#define LL long long
#define f(i,n) for(int i=1;i<=n;i++)
#define f_(i,n) for(int i=n;i>=1;i--)
#define ff(i,a,b) for(int i=a;i<=b;i++)
#define ff_(i,a,b) for(int i=a;i>=b;i--)
#define pi pair<int,int>
#define pb push_back
#define vi vector<int>
#define yes cout<<"Yes"<<endl
#define no cout<<"No"<<endl
#define fs(i,s) for(int i=0;i<s.size();i++)
#define re return
#define con continue
#define bre break
#define mkp make_pair
#define umap unordered_map
#define ld long double
const int N=3e6+10,M=1e3+100;
int n,m,k,x[N],y[N],xx[N],yy[N];
int chox[N],choy[N];
bool mp[M][M];
int num[M][M],cnt,cntm;
vector<int> to[N];
void add(int x1,int y1,int x2,int y2){
	if(!num[x1][y1]){
		num[x1][y1]=++cnt;
		xx[cnt]=x1,yy[cnt]=y1;//还需要记录节点以便清空 
	}
	if(!num[x2][y2]){
		num[x2][y2]=++cnt;
		xx[cnt]=x2,yy[cnt]=y2;
	}
	to[num[x1][y1]].pb(num[x2][y2]);
	to[num[x2][y2]].pb(num[x1][y1]);
}
const int mod=1e9+7;
LL ans;
int sum,numm;
bool ok,vis[N];
void dfs(int k){
	vis[k]=1;
	numm++;
	sum+=to[k].size();
	for(auto i:to[k]){
		if(!vis[i])
			dfs(i);
		if(i==k)ok=1;
	}
}
void solve(){
	cin>>n>>m>>k;
	k++;cnt=0;ans=1;
	f(i,k)cin>>x[i]>>y[i];
	f(i,k-1){
		if(abs(x[i]-x[i+1])+abs(y[i]-y[i+1])!=2){
			cout<<0<<'\n';
			f(o,cnt)vis[o]=0,to[o].clear(),num[xx[o]][yy[o]]=0;
			re;
		}if(x[i]==x[i+1]){
			add(x[i],(y[i]+y[i+1])/2,x[i],(y[i]+y[i+1])/2);
		}else if(y[i]==y[i+1]){
			add((x[i]+x[i+1])/2,y[i],(x[i]+x[i+1])/2,y[i]);
		}else{
			add(x[i],y[i+1],x[i+1],y[i]);
		}
	}
	f(i,cnt){
		if(!vis[i]){
			numm=sum=ok=0;dfs(i);sum>>=1;
			if(sum>numm){
				cout<<0<<'\n';
				f(o,cnt)vis[o]=0,to[o].clear(),num[xx[o]][yy[o]]=0;
				re;
			}
			if(sum==numm){
				if(!ok)ans=1ll*ans*2%mod;
			}else{
				ans=1ll*ans*numm%mod;
			}
		}
	}
	f(o,cnt)vis[o]=0,to[o].clear(),num[xx[o]][yy[o]]=0;
	cout<<ans<<'\n';
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    int T; 
    cin>>T;
	while(T--)
        solve();
    return 0;
}
```

---

## 作者：wangyizhi (赞：2)

**题目传送门：[洛谷](https://www.luogu.com.cn/problem/CF2097B) || [CF](https://codeforces.com/problemset/problem/2097/B)**

神秘分类讨论题。赛时两罚才过。/kk

蒟蒻的做法可能更为麻烦一些。

## 题目大意

一条路径是合法的，当且仅当每次只能走到相邻格子，且一个格子不能经过两次。现在有一条长为奇数的路径，不告诉你其中第偶数个格子，问有多少种合法填法。

## 题目分析

首先有几种情况可以特判掉，方便后续处理：

+ 存在 $i$ 使得 $|x_{i+1}-x_i|+|y_{i+1}-y_i| \neq 2$；

+ 存在 $i,j$ 满足 $|x_{i+1}-x_i|=2,|y_{j+1}-y_j|=2$ 使得 $\frac{x_{i+1}+x_i}{2}=x_j,\frac{y_{j+1}+y_j}{2}=y_i$。

发现可能有多个填法的只有一种情况：$|x_{i+1}-x_i|=1,|y_{i+1}-y_i|=1$。这时只能在 $(x_i,y_{i+1}),(x_{i+1},y_i)$ 中选一个，且不能重复选这个点。于是在这两个点间连边，那么就变成了在一个图中给每条边选两端点中一个且不能重复的方案数。

但先等等。有的点其实是不能被选的。当 $|x_{i+1}-x_i|=2$ 或 $|y_{i+1}-y_i|=2$ 时，$(\frac{x_i+x_{i+1}}{2},\frac{y_i+y_{i+1}}{2})$ 不能被选。我们对这些点打标记。

对图中的每个联通块都数出其中点数 $a$，标记过的点数 $b$，边数 $c$。此时有很多种情况：

+ $a<c$

  - $b=0$ ：此时每个分配方式都等价于选一个点使其不被分配，故答案为 $a$。

  - $b=1$ ：此时可选点数与边数相同，答案为 $1$。
 
  - $b>1$ ：此时可选点数少于边数，答案为 $0$。
 
+ $a=c$

  - $b=0$ ：此时所有点都能被恰好分配完。但由于此时是基环树，环上的点有两种分配方式，故答案为 $2$。

  - $b>0$ ：此时可选点数少于边数，答案为 $0$。
+ $a>c$ ：此时可选点数少于边数，答案为 $0$。
  
最后把每个联通块的答案乘起来就行了。

## AC Code

```cpp
// by wangyizhi(571247)
#include<bits/stdc++.h>
//#include<bits/extc++.h>
using namespace std;
using ll=long long;
using ld=long double;
//#define int ll
using pii=pair<int,int>;
//bool Mst;
const int N=1e6+5,mod=1e9+7;
vector<int> g[N];
int x[N],y[N],to[N],used[N];
array<int,3> dfs(int u,int fa)
{
	to[u]=1;
	array<int,3> ans={1,used[u],(int)g[u].size()};
	for(int v:g[u]) if(v!=fa&&!to[v])
	{
		auto res=dfs(v,u);
		ans[0]+=res[0],ans[1]+=res[1],ans[2]+=res[2];
	}
	return ans;
}
//bool Med;
signed main()
{
//	cerr<<"Memory Size: "<<abs((&Med)-(&Mst))/1024.0/1024<<" MB\n";
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--) [&]()
	{
		int n,m,k,cnt=0,ans=1;
		cin>>n>>m>>k;k++;
		vector<vector<int>> num(n+2,vector<int>(m+2));
		for(int i=1;i<=n*m;i++) g[i].clear(),to[i]=0,used[i]=0;
		for(int i=1;i<=k;i++) cin>>x[i]>>y[i];
		for(int i=1;i<k;i++)
			if(abs(x[i]-x[i+1])+abs(y[i]-y[i+1])!=2)
			{
				cout<<0<<"\n";
				return;
			}
		for(int i=1;i<k;i++)
		{
			if(x[i]==x[i+1]||y[i]==y[i+1])
			{
				int xx=(x[i]+x[i+1])/2,yy=(y[i]+y[i+1])/2;
				if(!num[xx][yy]) num[xx][yy]=++cnt;
				if(used[num[xx][yy]])
				{
					cout<<0<<"\n";
					return;
				}
				used[num[xx][yy]]=1;
			}
		}
		for(int i=1;i<k;i++)
		{
			if(abs(x[i]-x[i+1])==1)
			{
				if(!num[x[i]][y[i+1]]) num[x[i]][y[i+1]]=++cnt;
				if(!num[x[i+1]][y[i]]) num[x[i+1]][y[i]]=++cnt;
				g[num[x[i]][y[i+1]]].push_back(num[x[i+1]][y[i]]);
				g[num[x[i+1]][y[i]]].push_back(num[x[i]][y[i+1]]);
			}
		}
		for(int i=1;i<=cnt;i++) if(!to[i])
		{
			auto p=dfs(i,0);p[2]/=2;
			if(p[2]<p[0])
			{
				if(!p[1]) ans=1ll*ans*p[0]%mod;
				else if(p[1]>1)
				{
					cout<<0<<"\n";
					return;
				}
			}
			else if(p[2]==p[0])
			{
				if(!p[1]) ans=1ll*ans*2%mod;
				else
				{
					cout<<0<<"\n";
					return;
				}
			}
			else
			{
				cout<<0<<"\n";
				return;
			}
		}
		cout<<ans<<"\n";
	}();
	return 0;
}
```

---

## 作者：Comentropy (赞：1)

### Tl.dr.

Too long don't read.

呃，在场上后面想到正解，但是由于前面的写法消耗了过多的体力，即使还剩很多时间也没写了。开摆了。C 题又是一道不会的题，所以就爆炸。至于为什么没有先想到这个做法，因为太久没打 CF，各种套路有点忘得差不多了；其次是这个分支的考虑有点麻烦，感觉应该不用这么麻烦。

（其实是想到了正解但是写挂了以为假了。）非常可惜，掉蓝了。

不过今天用了点时间开发了一下这个写法，而且这个写法其实更自然，更容易想到。正解也可以用这种方式思考得到，所以，其实两者是同一个意思，不过你要是注意力涣散，这种大码量换正确性的方法值得你看一眼。同时我也会讲讲官解。

## 注意力部分

正如前文所说，该做法不需要注意力，这里就讲一点显然的事实。首先是 $p_i$ 和 $p_{i+2}$ 的曼哈顿距离，显然应恰好等于 $2$，否则不可能走相邻格两步到达。

然后曼哈顿距离为 $2$ 有个比较好的刻画方案：棋盘染色。这里看不出来没关系：很自然能发现奇偶位置位置的变化，感觉是个二分图状物，也能自然想到染色。

另外，若两点在同一直线上，显然只能经过中间那个点；而如果是斜着走，你会遇见有两个可选点的情况，比较棘手，我们要处理的就是这种情况。

## 初步分析

所以说，我们从 $p_i \to p_{i+1}$ 的过程正如其下标所示，是奇偶性变换的。我们可以把点拎出来建图！我们称可能的偶数层的点为可选点。

咋建？难道是把奇数层的点和偶数层的点分别连起来路径计数？不行，这不一定是 DAG，因为可能共用可选点。然后你可能考虑直接在网格图上做，利用这种图形（粉色的格子就是那些可选点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/do7ki8he.png?x-oss-process=image/resize,p_20)

我们可能可以发现一些性质，在忽略其它点的情况下，这里的方案数很容易算：假设一共有 $n$ 对这样的点，那应该有 $n+1$ 种选的方式（有这么多粉的点，其中有一个不选）。是不是只要关注这样的对角线就好了？不过还有一种更复杂的图形：

![](https://cdn.luogu.com.cn/upload/image_hosting/ehc1190v.png?x-oss-process=image/resize,p_20)

好难！不过一个比较启发性的研究是，我们好像不应该研究斜行，而是应该研究连通块。研究如何扩展上述结论就可以得到官解。

（本来我关于官解的部分写的基本成了翻译，因为官解需要一点注意力，而且个人认为官方题解写得相当烂，我很难说清楚，所以把这一部分删节了，建议去原文看：[link](https://codeforces.com/blog/entry/142316)）。

## 我的做法

（其实和官解本质是一样的。）

正如上文所言，一个奇数层点最多连向两个可选点，考虑利用这个性质。我们研究的是选择可选点的方案数，换言之，就是考虑可选点和奇数层点的匹配——把 $p_i$ 与其到 $p_{i+2}$ 中间经过的可选点 $u,v$ 分别连边。把奇数层点作为左部点，颜色为黑，偶数层可选点放在右部，颜色为白，那么就意味着让左部点匹配满的方案数。

随后我们可以对各连通块分别考虑。

如果没有环，就是一个树形的方案，随便 DP 一下就好了。容易做到线性。

有环呢？此时可以发现，一个单独的环上的匹配方案数如果单独拆出来看，有两种（顺时针逆时针，而且建图过程保证了是偶环）。那它连了其它边怎么办？注意黑点的度数至多为 $2$，在环上已经用完了所有度数，不会再连边。白点的度数是否有相似的性质？画图发现有，不过度数最多为 $3$（在它旁边转一圈可以达到这个上界）。

那环上的白点其实可能和其它黑点连，而至多连一个。注意这里只能是白点和黑点连，而且对于环上黑点对白点的匹配，其实并不影响。（环上黑点想要满匹配还是只有那两种情况，而且把环上白点占满了）

不难发现，如果有多个环并在一起，而不是一个环带一些链的情况，是不存在合法方案的，因为此时黑点数量大于白点数量，必然不存在满匹配。（画个图就能明白是怎么回事了，证明也很简单）

实现的话，朴素的实现就是找环然后断掉环和其它点连的边。更好的方式是：直接缩边双然后判黑白点个数就可以了。把边双和它连的边断掉单独处理，其余部分用树形 DP 做就好了。

代码写得比较潦草，跑得不快，但时间确实是 $O(k)$ 的。

[Submission](https://codeforces.com/contest/2097/submission/317404522).

---

