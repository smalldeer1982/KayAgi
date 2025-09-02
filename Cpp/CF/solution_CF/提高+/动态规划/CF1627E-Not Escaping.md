# Not Escaping

## 题目描述

Major Ram is being chased by his arch enemy Raghav. Ram must reach the top of the building to escape via helicopter. The building, however, is on fire. Ram must choose the optimal path to reach the top of the building to lose the minimum amount of health.

The building consists of $ n $ floors, each with $ m $ rooms each. Let $ (i, j) $ represent the $ j $ -th room on the $ i $ -th floor. Additionally, there are $ k $ ladders installed. The $ i $ -th ladder allows Ram to travel from $ (a_i, b_i) $ to $ (c_i, d_i) $ , but not in the other direction. Ram also gains $ h_i $ health points if he uses the ladder $ i $ . It is guaranteed $ a_i < c_i $ for all ladders.

If Ram is on the $ i $ -th floor, he can move either left or right. Travelling across floors, however, is treacherous. If Ram travels from $ (i, j) $ to $ (i, k) $ , he loses $ |j-k| \cdot x_i $ health points.

Ram enters the building at $ (1, 1) $ while his helicopter is waiting at $ (n, m) $ . What is the minimum amount of health Ram loses if he takes the most optimal path? Note this answer may be negative (in which case he gains health). Output "NO ESCAPE" if no matter what path Ram takes, he cannot escape the clutches of Raghav.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627E/deebf4ace32c90c729995f8cfd0fc9e081fe2525.png)

## 说明/提示

The figure for the first test case is in the statement. There are only $ 2 $ possible paths to $ (n, m) $ :

- Ram travels to $ (1, 3) $ , takes the ladder to $ (3, 3) $ , travels to $ (3, 2) $ , takes the ladder to $ (5, 1) $ , travels to $ (5, 3) $ where he finally escapes via helicopter. The health lost would be $ $$$ \begin{align*} &\mathrel{\phantom{=}} x_1 \cdot |1-3| - h_1 + x_3 \cdot |3-2| - h_3 + x_5 \cdot |1-3| \\ &= 5 \cdot 2 - 4 + 8 \cdot 1 - 6 + 4 \cdot 2 \\ &= 16. \end{align*}  $ $  </li><li> Ram travels to  $ (1, 3) $ , takes the ladder to  $ (3, 3) $ , travels to  $ (3, 1) $ , takes the ladder to  $ (5, 2) $ , travels to  $ (5, 3) $  where he finally escapes via helicopter. The health lost would be  $ $  \begin{align*} &\mathrel{\phantom{=}} x_1 \cdot |1-3| - h_1 + x_3 \cdot |3-1| - h_2 + a_5 \cdot |2-3| \\ &= 5 \cdot 2 - 4 + 8 \cdot 2 - 5 + 4 \cdot 1 \\ &= 21. \end{align*}  $ $  </li></ul> Therefore, the minimum health lost would be  $ 16 $ .<p>In the second test case, there is no path to  $ (n, m) $ .</p><p>In the third case case, Ram travels to  $ (1, 3) $  and takes the only ladder to  $ (5, 3) $ . He loses  $ 5 \\cdot 2 $  health points and gains  $ h\_1 = 100 $  health points. Therefore the total loss is  $ 10-100=-90$$$ (negative implies he gains health after the path).

## 样例 #1

### 输入

```
4
5 3 3
5 17 8 1 4
1 3 3 3 4
3 1 5 2 5
3 2 5 1 6
6 3 3
5 17 8 1 4 2
1 3 3 3 4
3 1 5 2 5
3 2 5 1 6
5 3 1
5 17 8 1 4
1 3 5 3 100
5 5 5
3 2 3 7 5
3 5 4 2 1
2 2 5 4 5
4 4 5 2 3
1 2 4 2 2
3 3 5 2 4```

### 输出

```
16
NO ESCAPE
-90
27```

# 题解

## 作者：NBest (赞：3)

想不到什么很好的做法，只是觉得这个看上去很好建图，一看是单向边且只能向上，所以就打算打个建图暴力了。

每个楼梯开个点，然后跑个 SPFA 即可。
### $Code$
```cpp
const int N=100050;
typedef pair<int,ll> PII;
struct FLOOR{int stx,sty,enx,eny;ll hp;};
struct loca{int x,y;}w[N];
int n,m,g,a[N],tot;
vector<FLOOR>fl[N];
vector<PII>f[N],id;
queue<int>Q;
ll dis[N];
bool vis[N];
int main(){
    for(int T=read();T--;){
        n=read(),m=read(),g=read();
        for(int i=1;i<=n;i++){
            a[i]=read();
        }
        for(int i=1;i<=g;i++){
            int x1=read(),y1=read(),x2=read(),y2=read(),hp=read();
            fl[x1].push_back({x1,y1,x2,y2,hp});
        }
        w[(tot=1)]={1,1};
        for(int i=1;i<=tot;i++){
            int F=w[i].x;
            for(auto flo:fl[F]){
                w[++tot]={flo.enx,flo.eny};
                if(flo.enx==n)id.push_back({tot,flo.eny});
                f[i].push_back({tot,1ll*abs(flo.sty-w[i].y)*a[F]-flo.hp});
            }
        }
        for(int i=2;i<=tot;i++)dis[i]=1e18;
        dis[1]=0;
        Q.push(1);
        while(!Q.empty()){
            int x=Q.front();
            Q.pop();
            vis[x]=0;
            for(auto PI:f[x]){
                ll y=PI.first,w=PI.second;
                if(dis[y]>dis[x]+w){
                    dis[y]=dis[x]+w;
                    if(!vis[y]){
                        vis[y]=1;
                        Q.push(y);
                    }
                }
            }
        }
        ll ans=1e18;
        for(auto PI:id){
            int y=PI.first,eny=PI.second;
            if(dis[y]+1ll*abs(m-eny)*a[n]<ans)ans=dis[y]+1ll*abs(m-eny)*a[n];
        }
        if(ans>1e17)puts("NO ESCAPE");
        else printf("%lld\n",ans);
        for(int i=1;i<=tot;i++)f[i].clear(),vis[i]=0;
        for(int i=1;i<=n;i++)fl[i].clear();
        id.clear();
    }
    return 0;
}
```
然而不出我所料，在 Codeforces 上第四个点就 T 了，原因之一是其本身就是一个网络图，然后显然就噶了。

考虑正解。

SPFA 被卡的原因大概也有我对于每一个终点都通过起点跟起点所在层的所有终点连了边，而如果同一层有 $10^4$ 个起点，然后上面有 $10^4$ 个终点，那光连边的复杂度就得爆炸。

首先还是用一个很显然的结论，我只可能往 $(n,m)$ 和楼梯走，所以有效点只有起点终点和楼梯的起点和终点。考虑每个有效点的答案 $dp_i$ 表示到 $i$ 点减小的最小生命值，那么显然如果它是楼梯终点，它的答案可以从楼梯起点转移过来，也可以从同层的点转移过来，因为同层左右都有，所以得做两次转移。有人可能会觉得做两次转移不会使其错误吗，答案是显然的不会，如果之前转移来的没有被更新，显然也不会加入答案，复杂度 $O(k)$。
## $Code$
```cpp
const int N=100050;
typedef pair<int,ll> PII;
struct FLOOR{
    int i,x,to=-1,hp;
    inline bool operator <(const FLOOR &w)const{return x<w.x;}
};
int n,m,g,a[N],tot;
vector<FLOOR>f[N];
ll dp[200005];
int main(){
    for(int T=read();T--;tot=0){
        n=read(),m=read(),g=read();
        for(int i=1;i<=n;i++)
            a[i]=read(),f[i].clear();
        for(int i=1;i<=g;i++){
            int x1=read(),y1=read(),x2=read(),y2=read(),hp=read();
            f[x1].push_back({++tot,y1,tot+1,hp});
            f[x2].push_back({++tot,y2,-1,0});
        }
        f[1].push_back({++tot,1,-1,0});
        f[n].push_back({++tot,m,-1,0});
        for(int i=1;i<=tot;i++)dp[i]=1e18+0.3;
        dp[tot-1]=0;
        for(int t=1;t<=n;t++){
            sort(f[t].begin(),f[t].end());
            for(int i=1;i<f[t].size();i++)
                dp[f[t][i].i]=min(dp[f[t][i].i],dp[f[t][i-1].i]+1ll*(f[t][i].x-f[t][i-1].x)*a[t]);
            for(int i=f[t].size()-2;i>=0;--i)
                dp[f[t][i].i]=min(dp[f[t][i].i],dp[f[t][i+1].i]+1ll*(f[t][i+1].x-f[t][i].x)*a[t]);
            for(int i=0;i<f[t].size();i++)
                if(dp[f[t][i].i]<1e18)
                dp[f[t][i].to]=min(dp[f[t][i].to],dp[f[t][i].i]-f[t][i].hp);
        }
        if(dp[tot]<1e18)printf("%lld\n",dp[tot]);
        else puts("NO ESCAPE");
    }
    return 0;
}
```

---

## 作者：enucai (赞：3)

**2022.1.29 Update:** 更改了错别字。

### 题意

有些复杂，没什么好简化的，直接那题面 Google 机翻好了，这里不再赘述。

### 思路

想想 Ram 的逃生路线是怎样的。发现一定从一层爬梯子到上面，同层穿梭一下，再换梯子往上继续爬，知道爬到顶层。由于 $\forall i$，$a_i<c_i$，所以梯子**都是往上的**，不存在爬梯子向下再换梯子向上的情况。

因此，整幢大楼可以被看做是 $2\times k+2$ 个点。它们分别是**每个梯子的端点与起点、终点**。

将所有的点按照楼层整理好，每层内的点都从左往右排序。接下来就可以**按楼层序**号进行 dp 了。

$dp_i$ 表示到达 $i$ 号点的最大生命值。初始状态**唯有**起点的 dp 值为 $0$，其余点**均为** $-\infty$。

对于每一个点，它可能是从**通往它的梯子的另一个端点**推来的。这种情况用**刷表法**可以快速解决。即：$dp_{to_i}=\min\{dp_{to_i},dp_i+h\}$。$h$ 是这个梯子可以增加的生命值。

每一个点还有可能从**同一层的其他点**转移过来，这种情况用**填表法**进行 dp 较为方便，即：$dp_i=\min\{dp_i,dp_j+dis(i,j)\times x_{floor}\}$。

第二种转移可能从左边也可能从右边，因此要**顺序和倒序**各做一遍。

**注意**：要求输出最小损耗生命值，因此答案为 $-dp_{final}$。

### 代码

[Codeforces status](https://codeforces.com/contest/1627/submission/143757757)

```cpp
#define int long long
#define inf 1e18
int n,m,k,tot;
int heal[100010];
vector<pi> a[100010];
pi to[200010];
int dp[200010];
void work(){
	n=read(),m=read(),k=read(),tot=0;
	For(i,1,n) heal[i]=read();
	For(i,1,n) a[i].clear();
	a[1].eb(1,++tot);
	For(i,1,k){
		int x1=read(),y1=read(),x2=read(),y2=read(),h=read();
		a[x1].eb(y1,++tot);
		to[tot]=mkp(tot+1,h);
		a[x2].eb(y2,++tot);
		to[tot]=mkp(0,0);
	}
	a[n].eb(m,++tot);
	For(i,1,tot) dp[i]=-inf;
	dp[1]=0;
	For(i,1,n){
		sort(a[i].begin(),a[i].end());
		For(j,1ll,(int)a[i].size()-1) ckmx(dp[a[i][j].sec],dp[a[i][j-1].sec]-(a[i][j].fir-a[i][j-1].fir)*heal[i]);
		Rof(j,(int)a[i].size()-2,0ll) ckmx(dp[a[i][j].sec],dp[a[i][j+1].sec]-(a[i][j+1].fir-a[i][j].fir)*heal[i]);
		For(j,0ll,(int)a[i].size()-1) if(dp[a[i][j].sec]!=-inf&&to[a[i][j].sec].fir!=0) ckmx(dp[to[a[i][j].sec].fir],dp[a[i][j].sec]+to[a[i][j].sec].sec);
	}
	if(dp[tot]==-inf) puts("NO ESCAPE");
	else printf("%lld\n",-dp[tot]);
}
```

---

## 作者：Hisaishi_Kanade (赞：2)

很自然的想法是最短路。因为 $a_i<c_i$，所以梯子向上。那么最终的路线必然是每一层横着走一些然后从某个跳到上面某一层。

所以我们将至多梯子的两端连边，然后同层点连边，注意加入 $(1,1),(n,m)$ 两个点。但是发现，梯子加生命，同层减生命，这样的图边权有正有负不能 dij，需要 SPFA 就直接 $k^2$ 了。

既然楼层肯定从下往上走，那么这玩意就不会有后效性，我们设计一个 dp。

我们将梯子两端的节点称为关键节点，将每层的关键节点排序。$f(i,j)$ 表示目前在第 $i$ 层的第 $j$ 个关键节点能剩下的最大生命值。

$f(i,j)$ 从 $f(i,j-1)$ 和 $f(i,j+1)$ 的转移比较显然。而我们求出 $f(i,j)$ 之后，如果 $(i,j)$ 这个点有向上的梯子，则用 $f(i,j)+h$ 去更新这些梯子所对应的 $f(i^\prime,j^\prime)$。如何找对应的点呢，直接把每个梯子这条边建起来就行了。

具体实现我是这样的，将每层的关键点排序之后，按照楼层从低到高，每层依次赋予一个新的编号。然后动态规划在这个编号上进行。显然，同一层的编号是连续的。这样建边也容易很多。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
map<int, map<int, int>> q;
#define int long long
const int N=3e5+5; ll inf=-(1ll<<60);
vector<int> p[N]; vector<pair<int, int>> e[N];
int t, n, m, k, i, j, tot, l, r;
int a[N], b[N], c[N], d[N], h[N]; ll f[N], x[N], w[N];
signed main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d %d %d", &n, &m, &k); tot=0;
		q.clear(); rep(i, 1, n) p[i].clear(); rep(i, 1, 3*k) e[i].clear();
		rep(i, 1, n) scanf("%d", x+i);
		rep(i, 1, k)
		{
			scanf("%d %d %d %d %d", a+i, b+i, c+i, d+i, h+i);
			if(q[a[i]][b[i]]==false) p[a[i]].emplace_back(b[i]);
			if(q[c[i]][d[i]]==false) p[c[i]].emplace_back(d[i]);
			q[a[i]][b[i]]=q[c[i]][d[i]]=true;
		} if(!q[1][1]) { q[1][1]=true; p[1].emplace_back(1);}
		if(!q[n][m]) { q[n][m]=true; p[n].emplace_back(m); }
		rep(i, 1, n) sort(p[i].begin(), p[i].end());
		rep(i, 1, n) for(auto y : p[i]) q[i][y]=++tot;
		rep(i, 2, tot) f[i]=inf;
		rep(i, 1, k) e[q[a[i]][b[i]]].emplace_back(q[c[i]][d[i]], h[i]);
		f[1]=0;
		rep(i, 1, n)
		{
			if(p[i].empty()) continue;
			l=q[i][p[i].front()]; r=q[i][p[i].back()];
			rep(j, 1, p[i].size()-1) w[j]=x[i]*(p[i][j]-p[i][j-1]);
			rep(j, l+1, r) f[j]=max(f[j], f[j-1]-w[j-l]);
			req(j, r-1, l) f[j]=max(f[j], f[j+1]-w[j-l+1]);
			int k, val;
			rep(j, l, r) if(f[j]!=inf) for(auto pii: e[j]) k=pii.first, val=pii.second, f[k]=max(f[k], f[j]+val);
//			rep(j, l, r) printf("f[%d]=%d\n", j, f[j]);
		}
		if(f[tot]==inf) puts("NO ESCAPE");
		else printf("%lld\n", -f[tot]);
	}
}
```

---

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 2200}$
---
### 解题思路：

最短路是可以通过这道题的，但是需要加一些玄学优化。

最初的想法就是将所有的相邻的点之间连一条边，有梯子的连一条。但是空间太大了，可以将大部分的仅链接了左右两边的一类平凡的点去除掉，仅仅留下被梯子链接的点和特殊的起点，终点。然后为每一个关键的点做一个标号就能直接解决空间问题了。

但是直接这样会被卡掉，考虑加一些乱搞，我在代码中加的是记录下所有的点的入队次数，然后将入队次数在 $[2,\sqrt{n+5}]$ 的点加入前端，其余的加入后端，然后就能过了。


---
### 代码：

```cpp
#include<map>
#include<cmath>
#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=400005;
struct str{
	int x,y;
	bool operator <(str a){
		if(x==a.x)return y<a.y;
		return x<a.x;
	}
}p[MAXN];
map <int,int> M;
int n,T,m,k,x[MAXN],a,b,c,d,h,cnt,cnt_,que[MAXN],L,R;
int head[MAXN],nxt[MAXN*4],num[MAXN*4],w[MAXN*4],tot,dis[MAXN],v[MAXN];
deque <int> q;
int N(int x,int y){
	if(M[(x-1)*m+y]==0)M[(x-1)*m+y]=++cnt_;
	return M[(x-1)*m+y];
}
void init(){
	while(!q.empty())q.pop_front();
	for(int i=1;i<=cnt_;i++)head[i]=0,que[i]=0;
	for(int i=1;i<=tot;i++)w[i]=nxt[i]=num[i]=0;
	for(int i=1;i<=cnt_;i++)v[i]=0;
	tot=0;cnt=0;cnt_=0;
	M.clear();
}
void add_(int x,int y){
	N(x,y);
	p[++cnt].x=x;
	p[cnt].y=y;
}
void add(int x,int y,int z){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
	w[tot]=z;
}
signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%I64d%I64d%I64d",&n,&m,&k);
		for(int i=1;i<=n;i++)
		scanf("%I64d",&x[i]);
		add_(1,1);add_(n,m);
		N(1,1);N(n,m);
		for(int i=1;i<=k;i++){
			scanf("%I64d%I64d%I64d%I64d%I64d",&a,&b,&c,&d,&h);
			add_(a,b);add_(c,d);
			add(N(a,b),N(c,d),-h);
		}
		sort(p+1,p+cnt+1);
		for(int i=1;i<=cnt;i++){
			if(p[i].x==p[i-1].x&&p[i-1].y!=p[i].y){
				add(N(p[i].x,p[i].y),N(p[i-1].x,p[i-1].y),x[p[i].x]*abs(p[i-1].y-p[i].y));
				add(N(p[i-1].x,p[i-1].y),N(p[i].x,p[i].y),x[p[i].x]*abs(p[i-1].y-p[i].y));
			}
		}
		q.push_front(N(1,1));
		for(int i=1;i<=cnt_;i++)
		dis[i]=9223372036854775807;
		dis[N(1,1)]=0;
		L=2;R=(int)sqrt(cnt_+5);
		while(!q.empty()){
			int now=q.front();
			q.pop_front();v[now]=0;
			for(int i=head[now];i;i=nxt[i]){
				if(dis[now]+w[i]<dis[num[i]]){
					dis[num[i]]=dis[now]+w[i];
					if(v[num[i]]==0){
						v[num[i]]=1;
						que[num[i]]++;
						if(L<=que[num[i]]&&que[num[i]]<=R)q.push_front(num[i]);
						else q.push_back(num[i]);
					}
				}
			}
		}
		if(dis[N(n,m)]==9223372036854775807)printf("NO ESCAPE\n");
		else printf("%I64d\n",dis[N(n,m)]);
		init();
	}
	return 0;
}
```


---

## 作者：PosVII (赞：1)

**前言**

------------

超棒的一道题，建议评紫/蓝。

**思路**

------------

法一：最短路

可能是做网络流的经验，我看出本题需要进行一定程度的离散。

即我们只需要存储起点和终点节点，然后再存储梯子两端为节点。我们可以将每条梯子视作长度为 $-h_i$ 的边，然后对每一行上所有相邻的节点连个双向边跑 spfa 即可。

被卡空间又被卡时间……如果有神仙最短路过了请告诉我，Orz！！！

法二：动态规划

我们可以换个思路，将最短路换成普通的动态规划——显然，双向边都在同一行上，我们可以使用一次正向和一次逆向的转移实现。而我们也可以发现梯子是一定从低到高的，那么也可以转移。这样就不会被卡空间和时间了。

**code**

------------

```
#include<bits/stdc++.h> 
using namespace std;
template<typename G>inline void read(G&x){x=0;G f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();x*=f;}
template<typename G>inline void write(G x){if(x<0) putchar('-'),x=-x;G y=10,len=1;while(y<=x){y*=10;++len;}while(len--){y/=10;putchar(x/y^48);x%=y;}}
const int MAXN=2e5+5;
vector<pair<long long,int> > pos[MAXN];
pair<int,long> nxt[MAXN];
int t,n,m,k,cnt,a,b,c,d;
long long x[MAXN],dp[MAXN],h;
int main() {
    read(t);
    while(t--) {
    	read(n),read(m),read(k),cnt=2;
    	for(int i=1;i<=n;++i) read(x[i]),pos[i].clear();
    	pos[1].push_back(make_pair(1,1)),pos[n].push_back(make_pair(m,2));
    	for(int i=1;i<=k;++i) {
    		read(a),read(b),read(c),read(d),read(h);
    		pos[a].push_back(make_pair(b,++cnt));
    		nxt[cnt]=make_pair(cnt+1,h);
			pos[c].push_back(make_pair(d,++cnt));
			nxt[cnt]=make_pair(0,0);
		}
		for(int i=1;i<=cnt;++i) dp[i]=-1e18;
		dp[1]=0;
		for(int i=1;i<=n;++i) {
			sort(pos[i].begin(),pos[i].end());
			for(int j=1;j<pos[i].size();++j) {
				dp[pos[i][j].second]=max(dp[pos[i][j].second],dp[pos[i][j-1].second]-(pos[i][j].first-pos[i][j-1].first)*x[i]);
			}
			for(int j=pos[i].size()-2;j>=0;--j) {
				dp[pos[i][j].second]=max(dp[pos[i][j].second],dp[pos[i][j+1].second]-(pos[i][j+1].first-pos[i][j].first)*x[i]);
			}
			for(int j=0;j<pos[i].size();++j) {
				int now=pos[i][j].second;
				if(dp[now]!=-1e18&&nxt[now].first!=0) dp[nxt[now].first]=max(dp[nxt[now].first],dp[now]+nxt[now].second);
			}
		}
		if(dp[2]>-1e18) printf("%lld\n",-dp[2]);
		else printf("NO ESCAPE\n");
	}
    return 0;
}
```

---

## 作者：do_while_true (赞：1)

设 $f_{i,j}$ 为走到第 $i$ 层，第 $j$ 个房间，损失的最小健康点是多少。

然后注意到只有梯子端点处这些特殊点的 dp 值是需要维护的，处理同一层特殊点之间的转移，就把转移拆成两种，一种是从前面的房间转移到后面的房间，一种是后面的房间转移到前面的房间，这两种转移从前往后或者从后往前扫一下，把 dp 式子拆一下，用个 堆/`set`/变量 来记录最优的转移就可以了。

如果整数排序是线性的话，总复杂度可以线性。

整数排序并不是线性但是如果换成线性整数排序总复杂度就是线性的代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string.h>
#include<queue>
#include<vector>
#include<map>
#include<unordered_map>
#include<bitset>
#include<set>
#include<cmath>
#include<ctime>
#include<random>
#define vi vector<int>
#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define bc(x) __builtin_popcount(x)
#define re register
#define il inline
#define pii pair<int,int>
#define pil pair<int,long long>
#define pll pair<long long,long long>
#define mem0(x) memset(x,0,sizeof(x))
#define mem0x3f(x) memset(x,0x3f,sizeof(x))
// #pra gma GCC opti mize(3)
#define int long long
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
namespace IO_BUFF{
	mt19937 rnd(time(0)^(ll)(new char));
	int rend(int x){
		return rnd()%x+1;
	}
	void rendom_shuffle(int *a,int len){
		shuffle(a+1,a+len+1,rnd);
	}
	const int BS=(1<<24)+5;char Buffer[BS],*HD,*TL;
	inline int gc(){
	    if(HD==TL) TL=(HD=Buffer)+fread(Buffer,1,BS,stdin);
	    return (HD==TL)?EOF:*HD++;
	}
	inline int inn(){
	    int x,ch,s=1;while((ch=gc())<'0'||ch>'9')if(ch=='-')s=-1;x=ch^'0';
	    while((ch=gc())>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^'0');return x*s;
	}
	char ssss[19999999],tttt[20];int ssl,ttl;
    inline int print(int x)
    {
        if(x<0)ssss[++ssl]='-',x=(-x);
		if(!x) ssss[++ssl]='0';for(ttl=0;x;x/=10) tttt[++ttl]=char(x%10+'0');
        for(;ttl;ttl--) ssss[++ssl]=tttt[ttl];return ssss[++ssl]='\n';
    }
	inline int Flush(){return fwrite(ssss+1,sizeof(char),ssl,stdout),ssl=0,0;}
	int read(){
		char c=getchar();int x=1;int s=0;
		while(c<'0' || c>'9'){if(c=='-')x=-1;c=getchar();}
		while(c>='0' && c<='9'){
			s=s*10+c-'0';c=getchar();
		}
		return s*x;
	}
}using namespace IO_BUFF;
const int N=100010;
const ll inf=1e16+5e15;
int n,m,k,ect;
ll v[N];
struct Edge{
	int tx,ty,h;
	Edge(){}
	Edge(int a,int b,int c){tx=a;ty=b;h=c;}
}e[N];
vi eg[N];
unordered_map<int,ll>dp[N],egp[N];
vi vec[N];
void mian(){
	n=read();m=read();k=read();ect=0;
	for(int i=1;i<=n;i++)v[i]=read(),dp[i].clear(),egp[i].clear(),vec[i].clear();
	for(int i=1;i<=k;i++)eg[i].clear();
	vec[1].pb(1);vec[n].pb(m);dp[n][m]=inf;dp[1][1]=0;
	for(int i=1;i<=k;i++){
		int a=read(),b=read(),c=read(),d=read(),h=-read();
		if(!dp[a][b])vec[a].pb(b);
		if(!dp[c][d])vec[c].pb(d);
		if(!(a==1&&b==1))dp[a][b]=inf;
		dp[c][d]=inf;
		e[i]=Edge(c,d,h);
		if(!egp[a][b])egp[a][b]=++ect;
		eg[egp[a][b]].pb(i);
	}
	for(int i=1;i<=n;i++)sort(vec[i].begin(),vec[i].end());
	for(int x=1;x<=n;x++){
		ll qwq=inf;
		for(auto y:vec[x]){
			if(dp[x][y]!=inf)qwq=min(qwq,dp[x][y]-y*v[x]);
			if(qwq!=inf)dp[x][y]=min(dp[x][y],qwq+y*v[x]);
		}
		reverse(vec[x].begin(),vec[x].end());
		qwq=inf;
		for(auto y:vec[x]){
			if(dp[x][y]!=inf)qwq=min(qwq,dp[x][y]+y*v[x]);
			if(qwq!=inf)dp[x][y]=min(dp[x][y],qwq-y*v[x]);
		}
		for(auto y:vec[x]){
			if(egp[x][y]&&dp[x][y]!=inf){
				for(auto i:eg[egp[x][y]]){
					int tx=e[i].tx,ty=e[i].ty,h=e[i].h;
					dp[tx][ty]=min(dp[tx][ty],dp[x][y]+h);
				}
			}
		}
	}
	if(dp[n][m]==inf)puts("NO ESCAPE");
	else cout << dp[n][m] << '\n';
	return ;
}
signed main(){
	#ifdef awawawa
	freopen("data.in","r",stdin);
	#else
	#endif
	int T=read();
	while(T--)mian();
	return 0;
}
```

---

## 作者：2021hych (赞：0)

# 简要/形式化题意
给定一个 $n \times m$ 的矩阵，长度为 $n$  的数组 $x$，$k$ 个有序五元组 $(a,b,c,d,h)$，满足 $a<c$。选择一条从 $(1,1)$ 到 $(n,m)$ 的路径，开始时，代价为 $0$。该路径上，对于从 $(a,b)$ 直接到 $(c,d)$，若 $a \ne c$，则存在 $h$ 使得 $(a,b,c,d,h)$ 出现在有序五元组集合中，代价减 $h$。若 $a = c$，$b$，$d$ 无限制，代价加 $\left\vert b-d \right\vert \times x_a$。问路径结束后代价的最小值。
# 题解
显然可以看出是一道二维线性 $\text{DP}$ 题。记 $dp_{i,j}$ 表示从 $(1,1)$ 到 $(i,j)$ 的合法路径的最小代价。

对于同行的，把绝对值拆掉：当 $b>d$ 时，代价加 $(b-d) \times x_a$，当 $b<d$ 时，代价加 $(d-b) \times x_a$，两者的最小值即为答案，故从左到右和从右到左两次转移即可，转移方程如下：

$dp_{i,j}=\min\limits_{1 \le j' <j}\{dp_{i,j},dp_{i,j'}+(j-j') \times x_i\}$。

$dp_{i,j}=\min\limits_{j < j' \le m}\{dp_{i,j},dp_{i,j'}+(j'-j) \times x_i\}$。

优化：对于决策点 $j_1$，$j_2$ 满足 $j_1 < j_2 < j$。如果 $j_1$ 是 $j$ 的最优决策点。则 $dp_{i,j_1}+(j-j_1) \times x_i = dp_{i,j_1}+(j_2-j_1) \times x_i+(j-j_2) \times x_i< dp_{i,j_2}+(j-j_2) \times x_i$。得出：$dp_{i,j_1}+(j_2-j_1) \times x_i < dp_{i,j_2}$。与 $dp_{i,j_2}$ 的最优性质矛盾。因此可能作为最优决策点的只有 $j$ 左侧第一个点和 $j$ 右侧第一个点，改写之后为。

$dp_{i,j}=\min\{dp_{i,j},dp_{i,j-1}+x_i\}$。

$dp_{i,j}=\min\{dp_{i,j},dp_{i,j+1}+x_i\}$。

考虑跨行的情况，对于有序五元组 $(a,b,c,d,h)$ 来说。

$dp_{c,d}=\min\{dp_{c,d},dp_{a,b}-h\}$。

那么这样做的时间复杂度 $O(nm)$ 的，无法通过此题。仔细思考一下行内的转移式子。我们发现，如果没有出现在有序五元组中的点对，他在转移之前的值为 $\text{inf}$（初始时，除了$dp_{1,1}=0$，$dp_{i,j}$ 都为 $\text{inf}$）。故不可能作为最优决策点。也就是说，实际上只有 $2k$ 个有效点加上起始点一共 $2k+2$ 个。我们只要对这些点进行 $\text{DP}$ 即可。实现的时候要多一步排序，也是这个算法的瓶颈，所以时间复杂度 $O(n \log k)$。

当然，状态的设计要改一改，记 $dp_i$ 为 $(1,1)$ 到第 $i$ 个有效点的最小代价，然后维护一下编号之间的关系，实现起来略微复杂。 

# AC code
```
#include<bits/stdc++.h>
#define int long long 
#define fi first
#define se second
using namespace std;
const int N=1e5+10; 
int t,n,m,k,a,b,c,d,h,x[N]; 
vector<pair<int,int> >E1[N];
pair<int,int>F[3*N];
int dp[3*N];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--) {
		int cnt=0;
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++) cin>>x[i];
		for(int i=1;i<=n;i++) E1[i].clear();
		E1[1].push_back(make_pair(1,++cnt));
		for(int i=1;i<=k;i++) {
			cin>>a>>b>>c>>d>>h;
			E1[a].push_back(make_pair(b,++cnt));
			F[cnt]=make_pair(cnt+1,h);
			E1[c].push_back(make_pair(d,++cnt));
		}
		E1[n].push_back(make_pair(m,++cnt));
		for(int i=1;i<=cnt;i++) dp[i]=1e18;
		dp[1]=0;
		for(int i=1;i<=n;i++) {
			sort(E1[i].begin(),E1[i].end());
			int len=E1[i].size();
			for(int j=1;j<len;j++) 
				dp[E1[i][j].se]=min(dp[E1[i][j].se],dp[E1[i][j-1].se]+x[i]*(E1[i][j].fi-E1[i][j-1].fi));
			for(int j=len-2;j>=0;j--) 
				dp[E1[i][j].se]=min(dp[E1[i][j].se],dp[E1[i][j+1].se]+x[i]*(E1[i][j+1].fi-E1[i][j].fi));
			for(int j=0;j<len;j++) 
				if(dp[E1[i][j].se]!=1e18&&F[E1[i][j].se].fi) 
					dp[F[E1[i][j].se].fi]=min(dp[F[E1[i][j].se].fi],dp[E1[i][j].se]-F[E1[i][j].se].se);
		}
		if(dp[cnt]<1e18) cout<<dp[cnt]<<endl;
		else cout<<"NO ESCAPE"<<endl;
	}
	return 0;
}

```

---

## 作者：intel_core (赞：0)

做法 $1$：$\text{SPFA}$ 最短路

很显然，如果建图的话只会考虑梯子对应的节点和 $(1,1)$ 还有 $(m,n)$。

如果对于互相可达的梯子，都连边的话边数最多是 $O(k^2)$ 的。

但因为同一层的关键点之间是一条链的关系，所以只用连相邻的节点即可。

建图的时候把每层楼的梯子的位置排个序，相邻的点连边，梯子对应的点也连边。最后再把起点和重点加进图里。

建图 $O(k \log k)$，最短路 $O(k^2)$，因为建出来的图就是网格图所以会被卡。

做法 $2$：分层处理

延续上面的建图抽象问题的方法，逐层求解。

因为梯子是单向的，所以把同一行的所有关键点拿出来变成一条数轴，每个点有位置和最短路。

假设当前考虑到的第 $u$ 层的关键点的分别是 $p_1,p_2,\cdots,p_t$，距离分别是 $d_1,d_2,\cdots,d_t$。

那么 $d_x=\min\limits_{1\le i\le t}d_i+x_u|p_i-p_x|$，讨论正负拆绝对值即可。

处理完第 $u$ 层之后顺着梯子更新一下可达的节点的距离。

复杂度瓶颈在排序的 $O(k\log k)$。

---

## 作者：Nightingale_OI (赞：0)

## CF1627E Not Escaping

### 大意

有一 $ n $ 行 $ m $ 列的网格，有人要从 $ (1,1) $ 走到 $ (n,m) $ 。

在同一行，可以任意向左或右移动，需要损失 $ x_i $ 的生命值，人无法从某一行直接走到另一行。

网格中有 $ k $ 架梯子，每架梯子可以让他从 $ (a_i,b_i) $ 单向移动到 $ (c_i,d_i) $ 并获得 $ h_i $ 的生命值（ $ a_i < c_i $ ）。

请输出最小损失生命值（可为负），若不可能走到，输出 `NO ESCAPE` 。

### 思路

考虑每个梯子连着的两个点以及起终点设为关键点。

对于同一行，处理到达该行每个关键点的最小值。

把一行里的关键点按照列编号排序一遍。

发现一行里的移动只会向左或向右，顺着扫（从左到右）处理向右走，逆着扫处理向左走。

处理完一行更新一下爬梯子到达的后面的关键点即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int n,m,s,l;
const long long inf=1e17;
struct xyz{
	int x,y,z;
};
struct sto{
	long long dp;
	vector<xyz>to;
};
struct orz{
	int a,b,c,d,h;
};
int x[101010];
orz in[202020];
vector<sto>a[101010];
vector<int>c[101010];
map<int,int>d[101010];
inline long long Min(long long& x,long long y){return x<y?x:x=y;}
inline bool cmp(orz x,orz y){return x.a==y.a?x.b==y.b?x.c<y.c:x.b<y.b:x.a<y.a;}
void doing(){
	int tx,ty,v;
	scanf("%d %d %d",&n,&m,&s);
	f(i,1,n)scanf("%d",&x[i]);
	f(i,1,n)a[i].clear();
	f(i,1,n)c[i].clear();
	f(i,1,n)d[i].clear();
	f(i,1,s)scanf("%d %d %d %d %d",&in[i].a,&in[i].b,&in[i].c,&in[i].d,&in[i].h);
	l=s;
	f(i,1,l)in[++s]=(orz){in[i].c,in[i].d,0,1,0};
	in[++s]=(orz){1,1,0,0,0};in[++s]=(orz){n,m,0,1,0};
	sort(in+1,in+s+1,cmp);
	f(i,1,s){
		tx=in[i].a;ty=in[i].b;l=c[tx].size();
		if(!l)goto next;
		if(c[tx][l-1]==ty)goto end;
		next:;
		d[tx][ty]=l;
		c[tx].push_back(ty);
		a[tx].push_back((sto){in[i].d?inf:0,(vector<xyz>){}});
		end:;
		if(in[i].c)a[tx][d[tx][ty]].to.push_back((xyz){in[i].c,in[i].d,in[i].h});
	}
	f(i,1,n){
		l=c[i].size();
		f(j,2,l)Min(a[i][j-1].dp,a[i][j-2].dp+1ll*x[i]*(c[i][j-1]-c[i][j-2]));
		g(j,l,2)Min(a[i][j-2].dp,a[i][j-1].dp+1ll*x[i]*(c[i][j-1]-c[i][j-2]));
		f(j,1,l)if(a[i][j-1].dp!=inf)f(k,1,a[i][j-1].to.size()){
			tx=a[i][j-1].to[k-1].x;ty=a[i][j-1].to[k-1].y;v=a[i][j-1].to[k-1].z;
			Min(a[tx][d[tx][ty]].dp,a[i][j-1].dp-v);
		}
	}
	if(a[n][d[n][m]].dp==inf)printf("NO ESCAPE\n");
	else printf("%lld\n",a[n][d[n][m]].dp);
}
int main(){
	int t;
	cin>>t;
	while(t--)doing();
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1627E - Not Escaping 题解

## 题目描述

有一个 $n$ 行 $m$ 列的网格，$(i,j)$ 表示第 $i$ 行的第 $j$ 格。有人要从 $(1,1)$ 走到 $(n,m)$。

在同一行，可以任意向左或右移动，且从 $(i,j)$ 到 $(i,k)$ 需要损失 $\left|j-k\right|\times x_i$ 的生命值，但是，他无法从某一行直接走到另一行。

网格中有 $k$ 架梯子，第 $i$ 架梯子可以让他从 $(a_i,b_i)$ 单向移动到 $(c_i,d_i)$（保证 $a_i<c_i$），并获得 $h_i$ 的生命值。

请输出所有可以走到 $(n,m)$ 的路径中损失的生命值的最小值（若该值为负数说明他在逃脱后反而能增加生命值），若不可能走到，输出"NO ESCAPE"。

数据范围保证：$n,m,k\le10^5$。

## 思路分析

考虑直接 dp，用 $dp[i][j]$ 表示从 $(1,1)$ 到 $(i,j)$ 的最大收益（注意这里不是最小损失），然后每一行之间进行常规的状态转移。

对于额外的梯子，在到达起始点的时候就可以用起始点的 $dp$ 值去更新终点的 $dp$ 值，由于每一次只会从低的行影响高的行，所以满足状态转移的无后效性。

查询答案的时候只需要输出 $-dp[n][m]$ 即可。

但是这样直接做空间是 $10^{10}$ 的，直接 MLE 爆炸，所以考虑优化。

不难发现，对于状态转移的过程中，对其他的行有影响的只有每个梯子的起点终点，可以考虑缩点，只计算到达每个梯子的起点终点和 $(1,1)$ 以及 $(n,m)$ 的最大收益，然后按行存储，每一次先考虑同行之间的互相转换，然后沿着梯子更新。

对于同一行之间的状态转移，注意到转移花费随着两个点列距离的增加而增加，而且从 $(i,p_1)$ 到 $(i,p_2)$ 再到 $(i,p_3)$ 的路径中，只要方向相同，花费是等于从 $(i,p_1)$ 直接到 $(i,p_3)$ 的。

所以按列排序后每个节点只可能由前后两个节点转移而来，所以按列排序后分别从前到后从后到前各扫一遍然后考虑相邻节点的转移即可。

这样做的时间复杂度是 $\Theta(n\log k)$ 的，可以通过本题。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+7,INF=-1e18;
struct node {
	int y,id,des,cost;
	/*
	* y记录每个节点在第几列
	* id记录这个节点重构后对应的是几 
	* des记录以该节点为起点的梯子的终点，梯子不存在时是-1 
	* des记录以该节点为起点的梯子的能增加多少生命，梯子不存在时是0 
	*/ 
	node() { y=id=cost=0,des=-1; }
	inline friend bool operator <(const node &u,const node &v) {
		//排序时按列从小到大升序排序 
		return u.y<v.y;
	}
};
inline node mp(int y,int id,int des,int cost) {
	//用y,id,des,cost的值构造一个node节点 
	node ans;
	ans.y=y,ans.id=id,ans.des=des,ans.cost=cost;
	return ans;
}
vector <node> f[MAXN];
int dp[MAXN<<1],x[MAXN];
inline void solve() {
	int n,m,k,tot=0;
	scanf("%lld%lld%lld",&n,&m,&k);
	for(register int i=1;i<=n;++i) {
		scanf("%lld",&x[i]);
		f[i].clear();
	}
	f[1].push_back(mp(1,++tot,-1,0));		//放入路径的起点 
	for(register int i=1;i<=k;++i) {
		int a,b,c,d,h;
		scanf("%lld%lld%lld%lld%lld",&a,&b,&c,&d,&h);
		++tot;
		f[a].push_back(mp(b,tot,tot+1,h));	//放入梯子的起点 
		++tot;
		f[c].push_back(mp(d,tot,-1,0));		//放入梯子的终点 
	}
	f[n].push_back(mp(m,++tot,-1,0));		//放入路径的终点 
	//初始化成最小值(这里用memset好像会TLE) 
	for(register int i=1;i<=tot;++i) dp[i]=INF;
	dp[1]=0; //边界条件，原地不动没有收益 
	for(register int i=1;i<=n;++i) {
		sort(f[i].begin(),f[i].end()); //按列排序 
		for(register int j=1;j<f[i].size();++j) {
			//注意循环下标不要越界 
			if(dp[f[i][j-1].id]!=INF) {
				//考虑从前面转移过来的情况 
				dp[f[i][j].id]=max(dp[f[i][j].id],dp[f[i][j-1].id]-(f[i][j].y-f[i][j-1].y)*x[i]);
			}
		}
		for(register int j=f[i].size()-2;j>=0;--j) {
			//注意循环下标不要越界 
			if(dp[f[i][j+1].id]!=INF) {
				//考虑从后面转移过来的情况 
				dp[f[i][j].id]=max(dp[f[i][j].id],dp[f[i][j+1].id]-(f[i][j+1].y-f[i][j].y)*x[i]);
			}
		}
		for(register int j=0;j<f[i].size();++j) {
			if(dp[f[i][j].id]!=INF&&f[i][j].des!=-1) {
				//用这一行的梯子去更新更高行 
				dp[f[i][j].des]=max(dp[f[i][j].des],dp[f[i][j].id]+f[i][j].cost);
			}
		}
	}
	if(dp[tot]==INF) puts("NO ESCAPE"); //输出无解信息 
	else printf("%lld\n",-dp[tot]); 
	return ;
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) solve(); //多组数据 
	return 0;
} 
```



---

## 作者：loverintime (赞：0)

可以非常显然的发现： 有用的点只有起点、 终点和梯子的两个端点。 所以我们可以对图重新编号， 所以只剩下了 $\Theta(k)$ 个节点。

对于第 $x$ 层的层内转移， 有 dp 方程：

$f(i)=\min_{j}\{f(j)+a_x\times |i-j|\}$

我们按照这一层的房间编号顺序分别从左往右、 从右往左扫一遍。 注意到一个点要么能作为最优决策点， 要么一直无法作为最优决策点。 并且一个点一旦不是最优决策点， 后面都不会成为最优决策点。 所以我们可以通过这个性质减小枚举量。

对于层间转移， 按照梯子转移即可。

每次时间复杂度 $\Theta(n\log n)$ （瓶颈在重新编号）, 可以通过。

[AC记录](https://codeforces.com/contest/1627/submission/143483527)

---

