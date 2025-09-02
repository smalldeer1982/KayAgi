# Tick, Tock

## 题目描述

Tannhaus, the clockmaker in the town of Winden, makes mysterious clocks that measure time in $ h $ hours numbered from $ 0 $ to $ h-1 $ . One day, he decided to make a puzzle with these clocks.

The puzzle consists of an $ n \times m $ grid of clocks, and each clock always displays some hour exactly (that is, it doesn't lie between two hours). In one move, he can choose any row or column and shift all clocks in that row or column one hour forward $ ^\dagger $ .

The grid of clocks is called solvable if it is possible to make all the clocks display the same time.

While building his puzzle, Tannhaus suddenly got worried that it might not be possible to make the grid solvable. Some cells of the grid have clocks already displaying a certain initial time, while the rest of the cells are empty.

Given the partially completed grid of clocks, find the number of ways $ ^\ddagger $ to assign clocks in the empty cells so that the grid is solvable. The answer can be enormous, so compute it modulo $ 10^9 + 7 $ .

 $ ^\dagger $ If a clock currently displays hour $ t $ and is shifted one hour forward, then the clock will instead display hour $ (t+1) \bmod h $ .

 $ ^\ddagger $ Two assignments are different if there exists some cell with a clock that displays a different time in both arrangements.

## 说明/提示

For the first sample, this is a possible configuration for the clocks:

| 1 | 0 | 3 |
| :-----------: | :-----------: | :-----------: |
| 0 | 3 | 2 |

This is solvable since we can:

1. Move the middle column forward one hour.
2. Move the third column forward one hour.
3. Move the third column forward one hour.
4. Move the second row forward one hour.

 After that all the clocks show one hour.For the second test case, it can be shown that there are no possible solvable clock configurations.

## 样例 #1

### 输入

```
5
2 3 4
1 0 -1
-1 -1 2
2 2 10
1 2
3 5
4 5 1024
1 -1 -1 -1 -1
-1 -1 -1 1000 -1
-1 -1 -1 -1 69
420 -1 -1 999 -1
3 3 3
-1 -1 1
2 -1 1
2 -1 2
3 3 3
1 -1 2
-1 0 -1
-1 1 0```

### 输出

```
4
0
73741817
0
1```

# 题解

## 作者：zhaoyp (赞：4)

先考虑没有 $-1$ 的情况该怎么判断是否合法。

容易发现成立的条件就是，相邻列之间每一行的两个数的差对应相等。

我们可以直接枚举判断或者使用边带权并查集维护。

想想怎么扩展。

继续使用边带权并查集。

对于每一个不是所有列都是 $-1$ 的行，用边带权并查集维护列与列之间的关系。判掉无解的情况

设有 $x$ 个连通块。

在每一行中，对于每一个连通块，只要连通块中任意一个位置确定，那么这一行在这个连通块中的所有列都可以确定。

任取一个不是全为 $-1$ 的行，所有非 $-1$ 列在同一个连通块中，确定剩下的 $x-1$ 个联通块即可确定这一行，进而可以确定出所有不是全为 $-1$ 的行，共 $h^{x - 1}$ 种方案。

剩下 $y$ 个全是 $-1$ 的行，只要确定任意一个位置即可确定整行，方案数 $h^y$。

$$ans = h^{x+y-1}$$

---

## 作者：MSqwq (赞：4)

题意：  
就是给你一个矩阵，每次你可以操作每一行或者每一列同时加一，注意是在模 $h$ 意义下的加法，有些数是空着的你可以去填，然后问你有多少种填法可以操作后使整个矩阵全部数相同。  


------------
题解：  
分行列考虑每个数的构成，那么对于每个数，它所在打那一行会对他有一个 $x$ 贡献，它所在的那一列会对它有一个 $y$ 的贡献。那么很显然，每一行的 $x$ 和每一列的 $y$ 是确定的，就是说每一行的贡献一定影响了那一行的所有数，每一列的贡献一定影响了那一列的所有数。   
那么先考虑无解，显然就是当行列贡献不足以让所有数变成相同的就无解。就只需要找矛盾。比如 $a_{i.j}$ 是我已经知道了，那么它的贡献就是对应行和列的贡献和，假设记作 $c_i+r_j$，因为有两个未知量，不好考虑，而且最后全部变成的那个数没有规定，我们不妨规定最后全部变成 $0$。那么当我们第一次讨论到某一行或者某一列的时候，就直接令它的贡献为 $0$，然后就可以继续推下去了。  
具体的实现就是我们讨论每一行和每一列一共讨论 $n + m$ 次。然后如果这个东西没有被标记过，我们就令它的贡献为 $0$。然后再去匹配，如果它是行，那么找列，如果列没有标记过，就把它扔进队列里面，进行讨论，然后看列的贡献有没有更新，如果没有就用 $a_{i,j} - r_i$ 去更新，如果更新过了就去看有没有毛肚即判断 $r_i + c_j $ 与 $a_{i,j}$ 相不相等，如果不相等就一定无解，反之继续讨论。对于当前是列的讨论也是一样，就不多赘述。这样就很巧妙的从填数转化为找矛盾。  
处理了这个之后其实就是算答案的问题了，其实很好算，因为每次我们讨论都是令的这个行列的贡献为 $0$，但其实它可以是 $[0,h-1]$，所以我们只需要找我们令了多少个初始贡献为 $0$ 的行列进行的推导。假设有 $s$ 个行列我们令它初始贡献为 $0$，因为只有在两次链接之间才能赋值，所以答案就是 $h^{s-1}$。  
如果读者觉得这个不好理解我们换个方式，用图论去理解，就是 $a_{i,j} = c_i + r_j$。我们看成这里 $i$ 和 $j$ 有一条边，判断无解就是看有没有矛盾，最后算答案其实就是看连通块个数，因为我们只需要满足每个连通块相等就可以，每个连通块可以同时为 $h$ 个数，所以 $s$ 就是连通块个数，那么要将这连通块相连，就需要 $s-1$ 条边，我们只能在连接的时候改变块值，所以答案就是 $h^{s-1}$。  
这题其实还算比较好想，但是细节巨多，非常不喜欢这种不让开正常数组的这种题。。。  
代码如下：  
```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<functional>
#define ll long long
using namespace std;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;

inline ll read()
{
	ll  x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}
ll ksm(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)res=res*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return res;
}
void solve()
{
	int n=read(),m=read(),h=read();
    vector<int>r(n+1,-1),c(m+1,-1);
    vector<int>v(n+m+1,false);
    vector<vector<int>>a(n+1,c);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)a[i][j]=read();

	ll s=0;
	for(int i=1;i<=n+m;i++)
	{
		if(!v[i])
		{
			
			s++,v[i]=1;
			if(i<=n)r[i]=0;
			else c[i-n]=0;
			
			queue<int>q;
			q.push(i);
			while(!q.empty())
			{
				int now=q.front();q.pop();
				if(now<=n)
				{
					for(int j=1;j<=m;j++)
					{
						if(a[now][j]!=-1)
						{
							if(!v[j+n])v[j+n]=1,q.push(j+n);
							if(c[j]==-1)c[j]=((a[now][j]-r[now])%h+h)%h;
							else if(a[now][j]!=(r[now]+c[j])%h)
							{
								cout<<0<<endl;
								return;
							}
						}
					}
				}
				else
				{
					for(int j=1;j<=n;j++)
					{
						if(a[j][now-n]!=-1)
						{
							if(!v[j])v[j]=1,q.push(j);
							if(r[j]==-1)r[j]=((a[j][now-n]-c[now-n])%h+h)%h;
							else if(a[j][now-n]!=(r[j]+c[now-n])%h)
							{
								cout<<0<<endl;
								return;
							}
						}
					}
				}
			}
		}
	}
	printf("%llld\n",ksm(h,s-1));
}

int main()
{
	int T=read();
	while(T--)solve();
	return 0;
}
```


---

## 作者：Polaris_Australis_ (赞：3)

考虑在一行内如果多个位置值不为 $-1$，假设第 $x$ 行的第 $y_1$ 列和第 $y_2$ 列值不为 $-1$，则可以确定 $y_1$ 与 $y_2$ 两列的关系，这个关系可以用带权并查集维护，如果出现冲突则无解。

如果有解，考虑选出值不全是 $-1$ 的一行，这一行里所有值不为 $-1$ 的位置一定在一个连通块里，假设连通块总数为 $cnt$，则对于剩下的 $cnt-1$ 个连通块，从每个连通块里选出一个点在这行赋值，即可确定这一行，并把连通块合并成了 $1$ 个，这样，剩余的所有值不全是 $-1$ 的行就都确定了，只需要考虑那些全是 $-1$ 的行，设有 $cont$ 行，这样的行我们只需要确定一个位置即可。

所以最终答案为：

$$
h^{cnt-1+cont}
$$

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define inv(x) qp(x,mod-2)
using namespace std;
namespace Std{
	void read(int &x){
		x=0;
		int y=1;
		char c=getchar();
		while(c<'0'||c>'9'){
			if(c=='-')y=-1;
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<1)+(x<<3)+(c&15);
			c=getchar();
		}
		x*=y;
	}
	int qp(int x,int y){
		int cmp=1;
		while(y){
			if(y&1)(cmp*=x)%=mod;
			(x*=x)%=mod;
			y>>=1;
		}
		return cmp;
	}
	int T,n,m,h,f[200010],g[200010];
	int find(int x){
		if(f[x]==x)return x;
		int ff=find(f[x]);
		(g[x]+=g[f[x]])%=h;
		return f[x]=ff;
	}
	void solve(){
		read(n);
		read(m);
		read(h);
		vector<vector<int> >a(n+1);
		bool mark=false;
		for(int i(1);i<=m;++i)f[i]=i,g[i]=0;
		for(int i(1);i<=n;++i){
			int lst=0;
			a[i].resize(m+1);
			for(int j=1;j<=m;++j){
				read(a[i][j]);
				if(mark)continue;
				if(~a[i][j]){
					if(lst){
						int fx=find(lst),fy=find(j);
						if(fx==fy){
							if(((a[i][j]-a[i][lst]+g[j])%h+h)%h!=g[lst]){
								mark=true;
								continue;
							}
						}else{
							if(fx<fy){
								f[fx]=fy;
								g[fx]=((a[i][j]-a[i][lst]+g[j]-g[lst])%h+h)%h;
							}else{
								f[fy]=fx;
								g[fy]=((g[lst]-a[i][j]+a[i][lst]-g[j])%h+h)%h;
							}
						}
					}
					lst=j;
				}
			}
		}
		if(h==1){
			puts("1");
			return;
		}
		if(mark){
			puts("0");
			return;
		}
		int ans(inv(h));
		for(int i(1);i<=m;++i){
			if(find(i)==i)(ans*=h)%=mod;
		}
		for(int i(1);i<=n;++i){
			mark=false;
			for(int j(1);j<=m;++j){
				if((~a[i][j]))mark=true;
			}
			if(!mark)(ans*=h)%=mod;
		}
		printf("%lld\n",ans);
	}
	void main(){
		read(T);
		while(T--)solve();
	}
}  // namespace Std
#undef int
int main(){
	Std::main();
	return 0;
}
```


---

## 作者：Tx_Lcy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1758E)

## 思路

首先考虑如何 $\rm check$ 某个答案是否合法。

不难发现，我们可以任意规定操作的顺序，所以假设先操作行，后操作列。

显然，我们在操作行的过程中需要把每列都变成相同的数，所以需要满足每一行的差分数组（$\bmod \ h$ 意义下）都完全相同。

同理，如果规定先操作列，后操作行，可以得到每一列的差分数组都完全相同。

这样我们就可以判断无解了，使用带权并查集维护列差分数组（其实就是互相推的关系）和行差分数组即可。

计数也非常简单，考虑先确定第一列的数，假设第一列已经确定了，所以列差分数组已经确定，那么对于 $2 \sim m$ 列每列的数，有下面两种情况：

+ 存在一个位置不是 $-1$，这一列被唯一确定。

+ 全部位置都是 $-1$，这一列有 $h$ 种填法。

接下来我们只需要计数第一列的方案就行了。

考虑我们用带权并查集维护出来的若干连通块，如果连通块中一个点确定了，那么整个连通块就确定了。

所以第一列可以自由填的数就是第一列的所有 $-1$ 组成的连通块个数，每个数都有 $h$ 种可能。

然后这道题就做完了。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define sqr(x) ((x)*(x))
#define all(x) (x).begin(),(x).end()
#define Tim ((double)clock()/CLOCKS_PER_SEC)
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
int const N=2e5+10;
int const mod=1e9+7;
vector<int>a[N];
int cha[N],n,m,h,ct,fa[N];
inline int find(int x){
    if (x==fa[x]) return x;
    int t=fa[x];fa[x]=find(fa[x]),cha[x]+=cha[t],cha[x]%=h;
    return fa[x];
}
void solve(){
    cin>>n>>m>>h;
    for (int i=1;i<=n;++i){
        a[i].resize(m+1);
        for (int j=1;j<=m;++j) cin>>a[i][j];
    }
    for (int i=1;i<=m;++i) fa[i]=i,cha[i]=0;
    for (int j=1;j<=n;++j){
        vector<int>vec;
        for (int i=1;i<=m;++i) if (a[j][i]!=-1) vec.push_back(i);
        if (vec.size()<2) continue;
        for (int i=1;i<(int)vec.size();++i){
            int x=find(vec[i]),y=find(vec[0]);
            if (x^y){
                cha[x]=(a[j][vec[i]]-cha[vec[i]]-a[j][vec[0]]+cha[vec[0]]+h+h)%h;
                fa[x]=y;
            }else if (cha[x]!=(a[j][vec[i]]-cha[vec[i]]-a[j][vec[0]]+cha[vec[0]]+h+h)%h)
                return cout<<"0\n",void();
        }
    }
    for (int i=1;i<=n;++i){
        for (int j=m;j>=1;--j)
            if (a[i][j]!=-1) a[i][find(j)]=(a[i][j]-cha[j]+h)%h;
        for (int j=1;j<=m;++j)
            if (a[i][find(j)]!=-1) a[i][j]=(a[i][find(j)]+cha[j])%h;
    }
    for (int i=1;i<=n;++i) fa[i]=i,cha[i]=0;
    for (int j=1;j<=m;++j){
        vector<int>vec;
        for (int i=1;i<=n;++i) if (a[i][j]!=-1) vec.push_back(i);
        if (vec.size()<2) continue;
        for (int i=1;i<(int)vec.size();++i){
            int x=find(vec[i]),y=find(vec[0]);
            if (x^y){
                cha[x]=(a[vec[i]][j]-cha[vec[i]]-a[vec[0]][j]+cha[vec[0]]+h+h)%h;
                fa[x]=y;
            }else if (cha[x]!=(a[vec[i]][j]-cha[vec[i]]-a[vec[0]][j]+cha[vec[0]]+h+h)%h)
                return cout<<"0\n",void();
        }
    }
    for (int j=1;j<=m;++j){
        for (int i=n;i>=1;--i)
            if (a[i][j]!=-1) a[find(i)][j]=(a[i][j]-cha[i]+h)%h;
        for (int i=1;i<=n;++i)
            if (a[find(i)][j]!=-1) a[i][j]=(a[find(i)][j]+cha[i])%h;
    }
    int ans=1;map<int,int>mp;
    for (int i=1;i<=n;++i)
        if (a[i][1]==-1 && !mp[find(i)]) mp[find(i)]=1,ans*=h,ans%=mod;
    for (int j=2;j<=m;++j){
        int fl=1;
        for (int i=1;i<=n;++i) fl&=(a[i][j]==-1);
        if (fl) ans*=h,ans%=mod;
    }
    cout<<ans<<'\n';
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t=1;
    cin>>t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：shinkuu (赞：1)

简单题。

发现把所有对行的操作提到前面对最终矩阵没有影响。然后要求就变成了进行完所有对行的操作后，每一列内所有数相同。

然后考虑这样会带来什么限制，发现相当于最后所有行相同，也就是操作前 $\forall i,j,k,l,a_{i,k}-a_{j,k}=a_{i,l}-a_{j,l}$。

于是发现如果 $a_{i,k},a_{j,k}$ 都不是 $-1$，则这两行的数两两的差确定为 $a_{i,k}-a_{j,k}$。显然可以并查集或者建图。这里选择建图，跑一遍看是不是符合所有限制即可判无解。

然后考虑计数。从建图的角度，如果当前有 $x$ 个连通块，则再连 $x-1$ 条边即可知道所有位置的值，边权为 $[0,h-1]$。除此之外，如果有一列一个不为 $-1$ 的数都没有，则还可以在 $[0,h-1]$ 中任选一个数确定一个位置，进而确定其他位置。设这样的有 $y$ 列，则答案为 $h^{x+y-1}$。

code：

```cpp
int n,m,k,dis[N],f[N];bool vis[N];
vector<int> a[N];
int tot,head[N];
struct node{int to,nxt,cw;}e[N<<1];
il void add(int u,int v,int w){e[++tot]={v,head[u],w},head[u]=tot;}
il int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)ret=1ll*ret*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
bool dfs(int u){
	vis[u]=1;
	go(i,u){
		int v=e[i].to;
		if(vis[v]){
			if(dis[v]!=(1ll*dis[u]+e[i].cw+k)%k)return 0;
			continue;
		}
		dis[v]=(1ll*dis[u]+e[i].cw+k)%k;
		if(!dfs(v))return 0;
	}
	return 1;
}
void Yorushika(){
	scanf("%d%d%d",&n,&m,&k),tot=0;
	rep(i,1,m)f[i]=0;
	rep(i,1,n)dis[i]=head[i]=vis[i]=0,a[i].clear(),a[i].resize(m+1);
	rep(i,1,n){
		rep(j,1,m){
			scanf("%d",&a[i][j]);
			if(a[i][j]==-1)continue;
			if(f[j])add(i,f[j],a[i][j]-a[f[j]][j]),add(f[j],i,a[f[j]][j]-a[i][j]);
			f[j]=i;
		}
	}
	int cnt=0;
	rep(i,1,n)if(!vis[i])if(cnt++,!dfs(i))return puts("0"),void();
	rep(j,1,m){
		bool fl=1;
		rep(i,1,n)fl&=a[i][j]==-1;
		cnt+=fl;
	}
	printf("%d\n",qpow(k,cnt-1));
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：happybob (赞：0)

很套路的一个题。

我们考虑什么矩阵可以被操作成全相同的。我们给出结论：充要条件是任意两行对应列的值之差都相同。也就是说任意两行 $x,y$ 都满足 $a_{x,1}-a_{y,1}=a_{x,2}-a_{y,2}=\cdots=a_{x,m}-a_{y,m}$。这个是很显然的，随便分析一下就行。

进一步，首先判无解。考虑每行相邻的不为 $-1$ 的位置，用带权并查集合并一下就行。然后考虑方案数。发现若有解，则只填第一行，剩下所有行，只要不是全 $-1$，则必然有唯一解。而全 $-1$ 的有 $h$ 种方案。对于第一行，考虑并查集每个连通块，若是全 $-1$ 则有 $h$ 种方案。所以记第一行全空连通块个数为 $c$，除了第一行有 $b$ 行全空，则答案为 $h^{b+c}$。

[Submission Link.](https://codeforces.com/contest/1758/submission/293309651)

---

