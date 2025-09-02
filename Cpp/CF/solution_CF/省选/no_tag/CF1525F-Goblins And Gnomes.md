# Goblins And Gnomes

## 题目描述

Monocarp plays a computer game called "Goblins and Gnomes". In this game, he manages a large underground city of gnomes and defends it from hordes of goblins.

The city consists of $ n $ halls and $ m $ one-directional tunnels connecting them. The structure of tunnels has the following property: if a goblin leaves any hall, he cannot return to that hall.

The city will be attacked by $ k $ waves of goblins; during the $ i $ -th wave, $ i $ goblins attack the city. Monocarp's goal is to pass all $ k $ waves.

The $ i $ -th wave goes as follows: firstly, $ i $ goblins appear in some halls of the city and pillage them; at most one goblin appears in each hall. Then, goblins start moving along the tunnels, pillaging all the halls in their path.

Goblins are very greedy and cunning, so they choose their paths so that no two goblins pass through the same hall. Among all possible attack plans, they choose a plan which allows them to pillage the maximum number of halls. After goblins are done pillaging, they leave the city.

If all halls are pillaged during the wave — Monocarp loses the game. Otherwise, the city is restored. If some hall is pillaged during a wave, goblins are still interested in pillaging it during the next waves.

Before each wave, Monocarp can spend some time preparing to it. Monocarp doesn't have any strict time limits on his preparations (he decides when to call each wave by himself), but the longer he prepares for a wave, the fewer points he gets for passing it. If Monocarp prepares for the $ i $ -th wave for $ t_i $ minutes, then he gets $ \max(0, x_i - t_i \cdot y_i) $ points for passing it (obviously, if he doesn't lose in the process).

While preparing for a wave, Monocarp can block tunnels. He can spend one minute to either block all tunnels leading from some hall or block all tunnels leading to some hall. If Monocarp blocks a tunnel while preparing for a wave, it stays blocked during the next waves as well.

Help Monocarp to defend against all $ k $ waves of goblins and get the maximum possible amount of points!

## 说明/提示

In the first example, Monocarp, firstly, block all tunnels going in hall $ 2 $ , secondly — all tunnels going in hall $ 3 $ , and after that calls all waves. He spent two minutes to prepare to wave $ 1 $ , so he gets $ 98 $ points for it. He didn't prepare after that, that's why he gets maximum scores for each of next waves ( $ 200 $ , $ 10 $ and $ 100 $ ). In total, Monocarp earns $ 408 $ points.

In the second example, Monocarp calls for the first wave immediately and gets $ 100 $ points. Before the second wave he blocks all tunnels going in hall $ 3 $ . He spent one minute preparing to the wave, so he gets $ 195 $ points. Monocarp didn't prepare for the third wave, so he gets $ 10 $ points by surviving it. Before the fourth wave he blocks all tunnels going out from hall $ 1 $ . He spent one minute, so he gets $ 99 $ points for the fourth wave. In total, Monocarp earns $ 404 $ points.

In the third example, it doesn't matter how many minutes Monocarp will spend before the wave, since he won't get any points for it. That's why he decides to block all tunnels in the city, spending $ 5 $ minutes. He survived the wave though without getting any points.

## 样例 #1

### 输入

```
5 4 4
1 2
2 3
4 3
5 3
100 1
200 5
10 10
100 1```

### 输出

```
6
-2 -3 0 0 0 0```

## 样例 #2

### 输入

```
5 4 4
1 2
2 3
4 3
5 3
100 100
200 5
10 10
100 1```

### 输出

```
6
0 -3 0 0 1 0```

## 样例 #3

### 输入

```
5 10 1
1 2
1 3
1 4
1 5
5 2
5 3
5 4
4 2
4 3
2 3
100 100```

### 输出

```
6
1 2 3 4 5 0```

# 题解

## 作者：StaroForgin (赞：6)

## 题解

我们可以先考虑如何求出一个图的最小路径覆盖。

我们可以将一个有向图的每个点拆成入点与出点两个点，在入点与出点两点之间连边。

于是，我们就将我们的图变成了一个二分图，由于二分图的 $最小路径覆盖=点数-最大匹配$，原图 DAG 的路径数等于有没有与出点连接的如点的数量，所以我们可以通过匈牙利求出原图的最小路径覆盖。

此时我们的删边操作就变成了从二分图中删去一个出点或入点。

很明显，我们删去一个点最多只会让最小路径覆盖增加 $1$，也就是让最大匹配减 $1$，因为它最多只会对一对匹配造成影响。

而对于任意一个最大匹配不为 $0$ 的二分图，一定存在一个节点，使得我们将这个节点删去后，最大匹配刚好减 $1$ ，即所有的最大匹配存在一个公共的匹配点。

如果不存在一个公共点，那么必定有点可以向一条增广路径的末尾连边，使得最大匹配增大。

所以所有的最大匹配必然存在这样的一个公共点。

那么假设我们最开始的最大匹配为 $x$，那么我们就要去找到 $k+1-x$ 次这样的公共点，并将他删去。

找公共点可以直接一个一个点地枚举，如果删去这个点后二分图的最大匹配减小，那么这个点就是所有最大匹配的公共点。

在找到这些公共点后，我们只需要将它们在合适的时候删去即可。

至于删点的顺序，我们可以通过 dp，来实现，即 $dp_{i,j}$ 表示哥布林袭击了 $i$ 次，已经删去了 $j$ 个点。

我们只对 $i<x+j$ 的 $dp_{i,j}$ 进行 dp 即可，直接枚举每次多删几个点暴力 dp 就行了。

最后我们只需要对 $dp_{k,k+1-x}$ 按原路返回输出答案即可。

时间复杂度 $O\left(n^5\right)$，如果不一个一个点删去后找，而是一次找完的话是可以做到 $O\left(n^3\right)$ 的 ~~，不过   $O\left(n^5\right)$ 已经可以过了~~。
## 源码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 2505
#define lowbit(x) (x&-x)
#define reg register
#define mkpr make_pair
#define fir first
#define sec second
typedef long long LL;
typedef unsigned long long uLL;
const LL INF=0x7f7f7f7f7f7f7f7f;
const LL jzm=2333;
const int zero=2500;
const int mo=998244353;
const double Pi=acos(-1.0);
typedef pair<int,int> pii;
const double PI=acos(-1.0);
template<typename _T>
_T Fabs(_T x){return x<0?-x:x;}
template<typename _T>
void read(_T &x){
	_T f=1;x=0;char s=getchar();
	while(s>'9'||s<'0'){if(s=='-')f=-1;s=getchar();}
	while('0'<=s&&s<='9'){x=(x<<3)+(x<<1)+(s^48);s=getchar();}
	x*=f;
}
template<typename _T>
void print(_T x){if(x<0){x=(~x)+1;putchar('-');}if(x>9)print(x/10);putchar(x%10+'0');}
int n,m,k,sta[55],stak,pre[55][55];bool link[55][55];LL dp[55][55];
vector<int> ans[55];
struct ming{int x,y;}s[55];
class Graph{
	private:
		int head[55],tot,p[55];bool mp[55][55],vis[55];
	public:
		void Remove(int u){
			if(u<=n)for(int i=1;i<=n;i++)mp[u][i]=0;
			else for(int i=1;i<=n;i++)mp[i][u-n]=0;
		}
		void Insert(int u){
			if(u<=n)for(int i=1;i<=n;i++)mp[u][i]=link[u][i];
			else for(int i=1;i<=n;i++)mp[i][u-n]=link[i][u-n];
		}
		void Copy(int u){
			if(u<=n)for(int i=1;i<=n;i++)link[u][i]=mp[u][i];
			else for(int i=1;i<=n;i++)link[i][u-n]=mp[i][u-n];
		}
		bool misaka(int x){
			vis[x]=1;
			for(int i=1;i<=n;i++){
				if(!mp[x][i])continue;
				if(p[i]==-1||(!vis[p[i]]&&misaka(p[i])))
					return (p[i]=x,1);
			}
			return 0;
		}
		int sakura(){
			for(int i=1;i<=n;i++)p[i]=-1;int res=0;
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++)vis[j]=0;
				if(misaka(i))res++;
			}
			return res;
		}
}G;
signed main(){
	read(n);read(m);read(k);
	for(int i=1,u,v;i<=m;i++)read(u),read(v),link[u][v]=1;
	for(int i=1;i<=n;i++)G.Insert(i),G.Insert(i+n);
	for(int i=1;i<=k;i++)read(s[i].x),read(s[i].y);int now=n-G.sakura(),tmp=now;
	if(now>k){printf("%d\n",k);while(k--)printf("0 ");puts("");return 0;}
	printf("%d\n",k+k+1-now);
	while(now<=k){
		for(int i=1;i<=2*n;i++){
			G.Remove(i);
			if(n-G.sakura()>now){now++,G.Copy(i);sta[++stak]=i;break;}
			else G.Insert(i);
		}
	}
	memset(dp,-0x7f,sizeof(dp));dp[0][0]=0;
	for(int i=0;i<k;i++){
		for(int j=0;j<=i-tmp;j++)dp[i][j]=-INF;
		for(int j=max(0,i+1-tmp);j<=k+1-tmp;j++){
			int num=s[i+1].x;
			for(int d=0;d<=k+1-j-tmp;d++){
				if(dp[i+1][j+d]<dp[i][j]+1ll*num)
					dp[i+1][j+d]=dp[i][j]+1ll*num,pre[i+1][j+d]=j;
				num=max(num-s[i+1].y,0);
			}
		}
	}
	now=k+1-tmp;
	for(int i=k;i>0;i--){
		for(int j=pre[i][now]+1;j<=now;j++)
			if(sta[j]>n)ans[i].push_back(-(sta[j]-n));
			else ans[i].push_back(sta[j]);
		now=pre[i][now];
	}
	for(int i=1;i<=k;i++){
		for(int j=0;j<ans[i].size();j++)printf("%d ",ans[i][j]);
		printf("0 ");
	}
	puts("");
	return 0;
}

```
## 谢谢！！！

---

## 作者：scallion (赞：4)

## 题意

原题面很简洁。

## 做法

是否能被占领相当于求 DAG 图最小不可重路径覆盖，我们将每个点拆成入点和出点，转化为二分图最大匹配问题，每次操作相当于删去一个点。

接着，我们发现最大匹配非零二分图一定可以删去一个点使得最大匹配减一。且我们找到一个最大匹配方案，找到一个匹配点对，满足其中一个有与非匹配点连边，那么删去有与非匹配点连边的那个点就可以使最大匹配减一，如果没有，那么随便找一个匹配的点即可。具体证明放在后面。

然后，我们就可以在开始时求出二分图最大匹配，单次 $O(n)$ 地找出每次要删的点。之后我们设 $f_{i,j}$ 为时刻 $i$，此时图需要 $j$ 个人才能被占领的答案，转移时前缀 $\max$ 优化就可以做到 $O(n^2)$。

时间复杂度 $O(n^2\sqrt n)$，瓶颈在于 dinic 求二分图最大匹配。

关于证明，看 [这篇文章](https://www.luogu.com.cn/article/bfho9wot)。

## 代码
```cpp

bool M1;
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define ll long long
#define ull unsigned long long
#define LL __int128
#define Pii pair<int,int>
#define Pll pair<ll,ll>
#define Pull pair<ull,ull>
#define fir first
#define sec second
#define vec vector<int>
#define pb push_back
#define qlr cerr<<"qlr\n"
#define dyh cerr<<"dyh\n"
#define pc(x) __builtin_popcount(x)
#define uni(x,y) uniform_int_distribution<int>(x,y)(rng)
#define unl(x,y) uniform_int_distribution<ll>(x,y)(rng)
#define unr(x,y) uniform_real_distribution<double>(x,y)(rng)
#define F(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define UF(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define look_memory cerr<<'\n'<<abs(&M1-&M2)/1024.0/1024<<'\n'
#define look_time cerr<<'\n'<<clock()*1.0/CLOCKS_PER_SEC<<'\n'
mt19937 rng(time(0)^(*new int));
const ll INF=0x3f3f3f3f3f3f3f3f;
const int Mod=998244353;
template<typename T>
inline void inc(T &a,T b){
	if(b<0) b+=Mod;
	a+=b;
	if(a>=Mod) a-=Mod;
}
template<typename T>
inline void dec(T &a,T b){
	if(b<0) b+=Mod;
	a-=b;
	if(a<0) a+=Mod;
}
template<typename T>
inline void muc(T &a,T b){
	a=a*b%Mod;
}
template<typename T>
inline bool chkmin(T &a,T b){
	if(a<=b) return false;
	a=b;
	return true;
}
template<typename T>
inline bool chkmax(T &a,T b){
	if(a>=b) return false;
	a=b;
	return true;
}
int n,m,K,cnt,ans,sp,tp;
ll px[60],py[60],t[60],d[110],now[110],e[110][110];
bool vis[60],vx[60],vy[60];
bool E[60][60];
ll f[60],pos[60][60];
Pll a[60],g[60];
queue<int> q;
bool bfs(){
	F(i,1,tp) now[i]=1;
	F(i,1,tp) d[i]=INF;
	d[sp]=0;
	q.push(sp);
	while(!q.empty()){
		int u=q.front();q.pop();
		F(i,1,tp){
			if(!e[u][i]||d[i]!=INF) continue;
			d[i]=d[u]+1;
			q.push(i);
		}
	}
	return d[tp]!=INF;
}
ll dfs(int u,ll sum){
	if(u==tp) return sum;
	ll res=0,fv;
	F(i,now[u],tp){
		if(!sum) break;
		now[u]=i;
		if(!e[u][i]||d[i]!=d[u]+1) continue;
		fv=dfs(i,min(sum,e[u][i]));
		if(!fv) d[i]=INF;
		e[u][i]-=fv;
		e[i][u]+=fv;
		sum-=fv;
		res+=fv;
	}
	return res;
}
void print(int x,int y){
	if(x>1) print(x-1,pos[x][y]);
	F(i,pos[x][y]+1,y) cout<<t[i]<<' ';
	cout<<"0 ";
}
void work1(int x){
	F(i,1,n){
		if(py[i]||vy[i]) continue;
		F(j,1,n){
			if(!px[j]||!E[j][i]) continue;
			t[x]=j;
			py[px[j]]=0;
			px[j]=0;
			F(k,1,n) E[j][k]=0;
			return;
		}
		vy[i]=1;
	}
}
void work2(int x){
	F(i,1,n){
		if(px[i]||vx[i]) continue;
		F(j,1,n){
			if(!py[j]||!E[i][j]) continue;
			t[x]=-j;
			px[py[j]]=0;
			py[j]=0;
			F(k,1,n) E[k][j]=0;
			return;
		}
		vx[i]=1;
	}
}
void work3(int x){
	F(i,1,n){
		if(!px[i]) continue;
		t[x]=i;
		py[px[i]]=0;
		px[i]=0;
		F(j,1,n) E[i][j]=0;
		return;
	}
}
bool M2;
int main(){
	srand(time(0)^(*new int));
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>K;
	F(i,1,m){
		int x,y;
		cin>>x>>y;
		e[x][y+n]=1;
		E[x][y]=1;
	}
	F(i,1,K) cin>>a[i].fir>>a[i].sec;
	sp=2*n+1,tp=2*n+2;
	F(i,1,n) e[sp][i]=1;
	F(i,1,n) e[i+n][tp]=1;
	while(bfs()) cnt+=dfs(sp,INF);
	F(i,1,n) F(j,1,n) if(e[j+n][i]) px[i]=j,py[j]=i;
	F(i,1,n) if(py[i]) px[py[i]]=i;
	F(i,n-cnt+1,n){
		work1(i);
		if(!t[i]) work2(i);
		if(!t[i]) work3(i);
	}
	F(i,0,n) f[i]=-INF;
	f[n-cnt]=0;
	F(i,1,K){
		ll tmp=a[i].fir/a[i].sec+1;
		if(tmp<=n) g[tmp]={f[0],0};
		F(j,tmp+1,n) g[j]=max(g[j-1],{f[j-tmp],j-tmp});
		
		F(j,0,n) pos[i][j]=j;
		F(j,1,n) if(chkmax(f[j],f[j-1]-a[i].sec)) pos[i][j]=pos[i][j-1];
		F(j,i+1,n) f[j]+=a[i].fir;
		F(j,tmp,n) if(chkmax(f[j],g[j].fir)) pos[i][j]=g[j].sec;
		f[i]=-INF;
	}
	
	F(i,0,n) if(f[i]>f[ans]) ans=i;
	cout<<K+ans-n+cnt<<'\n';
	print(K,ans);
	look_memory;
	look_time;
	return 0;
}

---

## 作者：EuphoricStar (赞：2)

套路地，将 DAG 的最小不交路径覆盖转化为点数减去拆点以后最大匹配。感性理解就是一开始每个点都是一条路径，一个匹配意味着两条路径结合了。

由题意知，第 $i$ 次进攻时最小不交路径覆盖必须 $> i$，也就是说，设最大匹配为 $k$，那么 $n - k > i$，即 $k \le n - i - 1$。

同时，通过上面的转化，题中删除某个点所有入边或出边的操作也可以转化为，在二分图上删去一个点，左右都可以。

我们发现，只要 $k > 0$，我们总能找到一个点，使得删掉后 $k \gets k - 1$。因为由 Konig 定理得二分图最大匹配 $=$ 最小点覆盖，只要从最小点覆盖中随意删除一个点即可。

于是我们可以求出一个删点序列，满足依次删除序列中的点，$k$ 都能依次减 $1$。

既然我们已经能够满足任意次删点了，那我们就可以对着每次进攻的参数 $a_i, b_i$ 做一个 dp，求出最大收益。输出方案就直接依次输出上面求出的删点序列即可。

时间复杂度大概是 $O(n^5)$？

[code](https://codeforces.com/contest/1525/submission/213130931)

---

## 作者：wind_whisper (赞：2)

证明角度和构造方法都和题解有所不同，感觉可能更为简洁一些？
## 解析
（以下基本模拟本人心路历程）  
看到最小链覆盖，联想到经典做法：最大匹配。  
然后就发现题目中的操作就等价于删除二分图的任意一个点，如此恰到好处甚至于略显刻意的设计，也侧面说明这是本题的正确方向了。

显然最后的代价计算就是套了一个无聊的皮，关键就是求出减少 $i$ 个最大匹配的最小删点数 $f_i$。  
然后在纸上画来画去...怎么感觉删除一个点必然减少一个匹配阿...  
~~结合这是CF题~~，猜结论：删除一个点必然减少一个最大匹配。

怎么证？

掏出经典结论：最大匹配 $=$ 最小点覆盖 $=$ $n$ $-$ 最大独立集。  

问题一下子变得简单了：转化为每次删除一个点的所有边，使最大独立集变大。那么显然只需要任意选取一个不在当前最大独立集的点即可。至于构造方案，预处理出独立集，每次在补集里随便挑一个点删去就行啦。  

不会构造最大独立集？可以看看 [这道题](https://www.luogu.com.cn/problem/P4298)。

使用匈牙利实现，时间复杂度 $O(n^3)$，也可以用网络流获得更优的复杂度。  

（最后最小化代价的那部分我采用了贪心而不是 dp 的实现。）  
（~~所以写挂了好几发~~）。  

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned ll
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define ok debug("ok\n")

const int N=105;
const bool Flag=1;

inline ll read() {
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)) {if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
bool mem1;

int n,m,k;
vector<int>e[N];
int mat[N],tag[N],tim;
int ans;
bool dfs(int x){
  if(tag[x]==tim) return false;
  tag[x]=tim;
  for(int to:e[x]){
    if(!mat[to]||dfs(mat[to])){
      mat[to]=x;
      mat[x]=to;
      return true;
    }
  }
  return false;
}
int op[N];
void find(int x){
  if(op[x]) return;
  op[x]=1;
  if(x<=n){
    if(mat[x]) find(mat[x]);
  }
  else{
    for(int to:e[x]){
      if(to==mat[x]) continue;
      find(to);
    }
  }
}
int q[N],ed,cur;
void hangry(){
  for(int i=1;i<=n;i++){
    ++tim;
    ans+=dfs(i);
  }
  for(int i=n+1;i<=n+n;i++){
    if(!mat[i]) find(i);
  }
  for(int i=1;i<=n;i++){
    if(op[i]) q[++ed]=i;
    else ++cur;
    if(!op[i+n]) q[++ed]=i+n;
    else ++cur;
  }
  //printf("ans=%d cur=%d\n",ans,cur);
  return;
}
int a[N],b[N];
int cnt[N];
int mnb=1e9+100,mna=1e9+100,idb,ida;
int pos;

bool mem2;
signed main() {
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  
  n=read();m=read();k=read();
  for(int i=1;i<=m;i++){
    int x=read(),y=read();  
    e[x].push_back(y+n);
    e[y+n].push_back(x);
  }
  hangry();
  int tot=k,ori=cur;
  ll res(0),ans=2e18;  
  for(int i=1;i<=k;i++){
    a[i]=read();
    b[i]=read();
    if(b[i]<mnb){
      mnb=b[i];
      idb=i;
    }
    if(a[i]<mna){
      mna=a[i];
      ida=i;
    }
    if(res+mna<ans){
      ans=res+mna;
      pos=ida;
    }
    while(cur<=i+n){
      cur++;
      res+=mnb;
    }
  }
  if(res<ans){
    ans=res;pos=k+1;
  }
  mnb=1e9;
  cur=ori;
  for(int i=1;i<=k;i++){
    if(b[i]<mnb){
      mnb=b[i];
      idb=i;
    }
    
    while(cur<=i+n){
      //cnt[id]++;
      cur++;
      if(i>=pos) cnt[pos]++;
      else cnt[idb]++;
      ++tot;
    }
  }
  printf("%d\n",tot);
  for(int i=1;i<=k;i++){
    for(int j=1;j<=cnt[i];j++){
      int x=q[ed--];
      printf("%d ",x<=n?x:-(x-n));
    }
    printf("0 ");
  }
  return 0;
}

```


---

## 作者：Mashu77 (赞：0)

将每个点拆为入点和出点，做二分图匹配，则覆盖所有点的最小路径数量 
$=
n
−$
 匹配数。

每次操作可以关闭某个点的所有入边或出边，就是在二分图中删去一个点。我们要求第 
$i$
 波时 
$n
−$
 匹配数 
$>
i$。

而删去一个点，最多只会减少一个匹配。我们希望每次删点都减少一个匹配，能否做到？

设某个时刻二分图中点数为 
$m$，初始 
$=2
n$。因为匹配数 
$=
m
−
|
S
|$，$S$
 为最大独立集，所以只要我们每次删 
$\overline{S}$
 中的元素就可以做到。
$n−(2n−|S|)+(2n−|S|)=
n$，而 
$k≤n
−
1$
，所以可以做到。

每次删去的点地位相同，做一个简单的 
DP
 即可。复杂度 
$O
(
n^
3
)$。

---

## 作者：intel_core (赞：0)

翻译一下题目条件：在第 $i$ 次攻击时要使最小不相交链覆盖 $\ge i+1$。

回顾一下最小链覆盖的求法，不难发现 ban 掉一个点的出边或者入边就相当于在二分图上把与一个点相邻的点全部删掉。

每次枚举一个点，如果删掉之后最大匹配 $-1$ 那么就相当于删掉之后最小链覆盖 $+1$。我们只需要 $n$ 次枚举，每次 $O(n^3)$ 求最大匹配。这部分复杂度 $O(n^4)$。

在得到一个删点序列之后剩下的就是简单 DP 了。设 $f_{i,j}$ 表示第 $i$ 次攻击前最小链覆盖是 $j$ 的最大分数，转移显然。

---

