# Policeman and a Tree

## 题目描述

You are given a tree (a connected non-oriented graph without cycles) with vertices numbered from $ 1 $ to $ n $ , and the length of the $ i $ -th edge is $ w_{i} $ . In the vertex $ s $ there is a policeman, in the vertices $ x_{1},x_{2},...,x_{m} $ ( $ x_{j}≠s $ ) $ m $ criminals are located.

The policeman can walk along the edges with speed $ 1 $ , the criminals can move with arbitrary large speed. If a criminal at some moment is at the same point as the policeman, he instantly gets caught by the policeman. Determine the time needed for the policeman to catch all criminals, assuming everybody behaves optimally (i.e. the criminals maximize that time, the policeman minimizes that time). Everybody knows positions of everybody else at any moment of time.

## 说明/提示

In the first example one of the optimal scenarios is the following. The criminal number $ 2 $ moves to vertex $ 3 $ , the criminal $ 4 $ — to vertex $ 4 $ . The policeman goes to vertex $ 4 $ and catches two criminals. After that the criminal number $ 1 $ moves to the vertex $ 2 $ . The policeman goes to vertex $ 3 $ and catches criminal $ 2 $ , then goes to the vertex $ 2 $ and catches the remaining criminal.

## 样例 #1

### 输入

```
4
1 2 2
1 3 1
1 4 1
2
4
3 1 4 1
```

### 输出

```
8
```

## 样例 #2

### 输入

```
6
1 2 3
2 3 5
3 4 1
3 5 4
2 6 3
2
3
1 3 5
```

### 输出

```
21
```

# 题解

## 作者：platelett (赞：22)

> [题目链接](http://codeforces.com/problemset/problem/868/E)    [可能更好的体验](http://coding-pages-bucket-3532178-8430896-13917-522304-1305159063.cos-website.ap-hongkong.myqcloud.com/CF868E/)
>
> 一棵 $n$ 个结点的边带权树，有一个警察初始在 $s$ 点，速度为 $1$，树上分布有 $m$ 个罪犯，速度为任意大，如果罪犯和警察在同一个结点就会被干掉，警察希望干掉所有罪犯的时间尽量短，而罪犯希望最大化这个时间，假设每个人都以最优策略行动，求这个时间。
>
> $1 \le n, m, w_i \le 50$，$w_i$ 为边权。
>
> 所有罪犯初始不在 $s$ 点，一个结点可能会有多个罪犯。

### 状态设计

考虑这个过程是怎样的。

当警察在结点 $1$ 时，由于罪犯速度任意大，但不能经过警察，所以罪犯分布在被结点 $1$ 隔开的三个部分中，并且可以在所属部分的任意位置上，**不妨假设**罪犯全部分布在所有与结点 $1$ 相邻的结点 $2,3,4$ 上。

图上的红数字表示该结点上有多少名罪犯。

![](https://i.loli.net/2021/03/18/A4Zpd72bkRMeINU.png)

当警察从结点 $1$ 走到结点 $4$ 时，结点 $4$ 上的两名罪犯就需要走到结点 $5,6$ ，同时结点 $2,3$ 上的两名罪犯可以一起走到结点 $1$。

![](https://i.loli.net/2021/03/18/gtTQYLueC21mlZW.png)

容易想到用警察所在的结点 $u$ 和所有与结点 $u$ 相邻的结点上分别有多少名罪犯来表示一个状态。  
但一个结点的度数是  $O(n)$ 级别的，因此状态数爆炸。

另一个描述状态的想法是警察当前在哪条边上，这条边的两端分别有多少名罪犯。  
然后状态数就减少成了 $O(n^3)$，非常少。

因此我们用 $f_{i,j,k}$ 表示当前总共还剩 $i$ 名罪犯，警察**刚走上** $j = u \rightarrow v$ 这条**有向边**（警察和 $u$ 的距离忽略不计），结点 $v$ 上有 $k$ 名罪犯。

### 转移

假设当前总共还剩  $i$ 名罪犯，警察在**有向边** $j = u \rightarrow v$ 上，边权为 $w$，结点 $v$ 上有 $k$ 名罪犯。

如果结点 $v$ 是叶子结点，显然
$$
f_{i,j,k}=f_{i-k,\bar j,i-k} + w
$$
其中 $\bar j$ 是 $j$ 的反向边。

另一种情况：

![](https://i.loli.net/2021/03/18/Vsnf9c6hIvYkCRd.png)

结点 $4$ 上的 $k$ 名罪犯必须要分为两波，其中 $a$ 名跑到了结点 $5$，$b$ 名跑到了结点 $6$。  
警察会下一步会在 $4 \rightarrow 5$ 和 $4 \rightarrow 6$ 中选择较优的一条有向边。

罪犯为了最大化时间：
$$
f_{i,1 \rightarrow 4,k} = \max_{a+b=k}\min \lbrace f_{i,4 \rightarrow 5,a},f_{i,4 \rightarrow 6,b}\rbrace + w
$$
一般地，设结点 $v$ 除 $u$ 以外的相邻点分别为 $a_1,a_2,a_3,\cdots,a_d$，则转移方程为：
$$
f_{i,j,k}=\max_{c_1+c_2+\cdots+c_d=k}\min_{s=1}^df_{i,v \rightarrow a_s,c_s} + w
$$
下面给出一种复杂度比较优秀的贪心算法实现第二种转移：

>引理：若求 $f_{i,j,k}$ 时的**决策**为 $c_1,c_2,\cdots,c_d$。  
>那么求 $f_{i,j,k+1}$ 时的决策 $\bar c_1,\bar c_2,\cdots,\bar c_d$ 一定是在 $c_1,c_2,\cdots,c_d$ 中的某个数 $+1$ 得到的。  
>并且 $+1$ 的这个 $c_x$ 满足
>$$
>f_{i,v \rightarrow a_x,c_x+1}=\max_{s=1}^df_{i,v \rightarrow a_s,c_s+1}
>$$
>证明：首先在总人数和位置相同的情况下，警察追的人越多，剩下的时间就越短。  
>故 $f_{i,j,0} \ge f_{i,j,1} \ge f_{i,j,2} \ge \cdots \ge f_{i,j,i}$。
>
>考虑
>$$
>\forall x \le f_{i,j,k}\exists c_1,c_2,\cdots,c_d,\\f_{i,v \rightarrow a_1,c_1} \ge x\\f_{i,v \rightarrow a_2,c_2} \ge x\\\cdots\\f_{i,v \rightarrow a_d,c_d} \ge x
>$$
>由二分答案算法的 ```check``` 函数可知：若 $m_i$ 是 $f_{i,v \rightarrow a_i}$ 数列中最后一个大于等于 $x$ 的位置，  
>则 $m_1+m_2+\cdots+m_d \ge k$。
>
>而以这种决策的构造方式，一定有 $c_1 \le m_1,c_2 \le m_2, \cdots, c_d \le m_d$，因此通过该决策得到的值一定不劣于 $x$。
>

因此可以用一个大根堆维护那个 $x$，可以在 $O(n\log n)$ 的时间同时求出 $f_{i,j,0},f_{i,j,1},\cdots,f_{i,j,i}$。

复杂度 $O(n^3\log n)$，标算的复杂度是 $O(n^5)$ 的。

然而由于常数巨大，最小的点要 $15$ ```ms```，最大的点要 $30$ ```ms```。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define per(i, r, l) for(int i = (r); i >= (l); i--)
#define mem(a, b) memset(a, b, sizeof a)
#define For(i, l, r) for(int i = (l), i##e = (r); i < i##e; i++)

using namespace std;
const int N = 55, Inf = 1e9;
int n, s, m, ev[N * 2], ew[N * 2], cnt[N], deg[N];
vector <int> G[N];
int f[N][N * 2][N];
void solve(int, int);
int dp(int i, int j, int k) {
	if(!f[i][j][k]) solve(i, j);
	return f[i][j][k];
}
struct node {
	int i, e, c;
	int val()const { return c < i ? dp(i, e, c + 1) : 0; }
	bool operator <(const node& b)const { return val() < b.val(); }
};
void solve(int i, int j) {
	f[i][j][0] = Inf;
	if(deg[ev[j]] == 1)
		rep(k, 1, i) f[i][j][k] = k < i ? dp(i - k, j ^ 1, i - k) + ew[j] : ew[j];
	else {
		priority_queue <node> q;
		for(int e : G[ev[j]]) if(e ^ j ^ 1) q.push({ i, e, 0 });
		rep(k, 1, i) {
			node x = q.top(); q.pop();
			f[i][j][k] = min(f[i][j][k - 1], x.val() + ew[j]);
			x.c++, q.push(x);
		}
	}
}
int dfs(int u, int fa) {
	int res = cnt[u];
	for(int e : G[u]) if(ev[e] ^ fa) res += dfs(ev[e], u);
	return res;
}
int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	int u, v, w;
	rep(i, 2, n) {
		int a = i * 2, b = a + 1;
		cin >> u >> v >> w, deg[ev[a] = v]++, deg[ev[b] = u]++, ew[a] = ew[b] = w;
		G[u].push_back(a), G[v].push_back(b);
	}
	cin >> s >> m;
	rep(i, 1, m) cin >> u, cnt[u]++;
	int ans = Inf;
	for(int e : G[s]) ans = min(ans, dp(m, e, dfs(ev[e], s)));
	cout << ans;
	return 0;
}
```

---

## 作者：Inui_Sana (赞：7)

Daily problem.

感觉是一个易懂的方法。

首先手玩样例，发现罪犯可以在警察进入一棵子树时从警察后面溜走，所以警察很有可能要重复走某些路径，这样用树形 dp 比较困难，所以可以考虑更像放在序列上的 dp。

设 $dp_{u,t}$ 为当前在 $u$ 位置，还有 $t$ 个罪犯没抓到，最快多久全抓到。首先限制 $u$ 为叶子，则这个状态是没有后效性的，因为如果上一步警察移动到 $u$，则所有剩下的罪犯都可以随便移动。并且罪犯在最优策略下一定是移动到叶子，故得证。

然后考虑转移。转移时，罪犯要分配每个叶子上去多少人，所以另外设一个 dp 状态 $f_{v,i}$ 表示 $[1,v]$ 的点内分配了 $i$ 个罪犯，警察在最优决策下，最慢多久抓到全部罪犯。以此辅助转移。类似背包转移：$f_{v,i}=\max(f_{v-1,i},\max_{j\le i}\min(f_{v-1,i-j},dis_{u,v}+dp_{v,t-j}))$。

最后还要看警察一开始从 $s$ 先去到哪个叶子，与上面类似地转移即可。

时间复杂度 $O(n^5)$。跑了 100ms-。而且看其他题解，显然可以至少优化到 $O(n^4\log n)$，把背包部分换成一个二分即可。不过应该也快不了多少。:)

code：

```cpp
int n,m,s,c[N],id[N],deg[N],dis[N][N],dp[N][N],f[N][N];
vector<int> g[N];
int tot,head[N];
struct node{int to,nxt,cw;}e[N<<1];
il void add(int u,int v,int w){e[++tot]={v,head[u],w},head[u]=tot;}
void getDis(int u,int f,int s,int w=0){
	dis[s][u]=dis[s][f]+w;
	go(i,u){
		int v=e[i].to;
		if(v==f)continue;
		getDis(v,u,s,e[i].cw);
	}
}
void dfs(int u,int f,int s){
	if(!g[s].size())g[s].eb(0);
	g[id[u]=s].eb(u);
	go(i,u){
		int v=e[i].to;
		if(v==f)continue;
		dfs(v,u,s);
	}
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n-1){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		add(u,v,w),add(v,u,w);
		deg[u]++,deg[v]++;
	}
	scanf("%d%d",&s,&m);
	int p=0;
	go(i,s)dfs(e[i].to,s,++p);
	rep(i,1,m){
		int x;scanf("%d",&x);
		c[id[x]]++;
	}
	rep(u,1,n)getDis(u,0,u);
	rep(u,1,n)dp[u][0]=0;
	rep(t,1,m){
		rep(u,1,n){
			mems(f,-0x3f);
			f[0][0]=inf;
			rep(v,1,n){
				rep(i,0,t)f[v][i]=f[v-1][i];
				if(deg[v]>1)continue;
				rep(j,1,t)rep(i,j,t){
					f[v][i]=max(f[v][i],min(f[v-1][i-j],dis[u][v]+dp[v][t-j]));
				}
			}
			dp[u][t]=f[n][t];
		}
	}
	int ans=inf;
	rep(k,1,p){
		mems(f,-0x3f);
		f[0][0]=inf;
		int sz=(int)g[k].size()-1;
		rep(u,1,sz){
			rep(i,0,c[k])f[u][i]=f[u-1][i];
			if(deg[g[k][u]]>1)continue;
			rep(j,1,c[k])rep(i,j,c[k]){
				f[u][i]=max(f[u][i],min(f[u-1][i-j],dis[s][g[k][u]]+dp[g[k][u]][m-j]));
			}
		}
		ans=min(ans,f[sz][c[k]]);
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：Caiest_Oier (赞：6)

# [CF868E](https://www.luogu.com.cn/problem/CF868E)  

提供一种两篇题解都没有提到的新方法。   

首先有一个很明显的性质，就是罪犯被抓住时一定待在叶子结点。所以说，考虑抓住罪犯的过程就是从 $s$ 到某个叶子结点后，不断前往下一个叶子节点。发现当警察处在叶子结点时，罪犯可以全树随便跑，于是重要的只有罪犯的数量了。令 $dp_{i,j}$ 表示警察在结点 $i$，全图还剩 $j$ 个罪犯时要用多久来抓人。但是发现这个值很不好求，于是我们考虑二分答案，变成一个判定是否可以在 $mid$ 内抓到问题。    

当警察从叶子结点出发的时候，罪犯一定分布在了若干叶子上，并且直到警察抓到一个罪犯之前，罪犯们一定不会动，因为这没有任何意义（警察与罪犯都持最优策略）。于是我们考虑罪犯在叶子结点的分布，令 $v_i$ 表示点 $i$ 的罪犯数，剩 $k$ 个罪犯，起点叶子为 $x$，则对于每一个非零的 $v_i$ 都必须满足 $dp_{i,k-v_i}+dis(i,x)\le mid$，这样的分布是合法的。而目标是找到一个不合法的，即所有 $v$ 非零的 $i$ 都满足 $dp_{i,k-v_i}+dis(i,x)> mid$。发现这个东西可以对每个叶子分开讨论，每个叶子可以取的罪犯数是一个前缀，都取最大，看总和能否达到 $k$ 即可。      

最后就是要对 $s$ 处理，二分答案时对 $s$ 的每个子树，分别检查即可。  

丑陋的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Edge{
	int st;
	int ed;
	int nxt;
	int val;
}E[503];
int totE,head[503],dp[53][53],F[503][23],dep[503],dis[503],n,m,s,wz[503],mk[503],k1,k2,k3,k4,k5,k6,k7,k8,k9,f,lft,rgt,mid,sum[503];
int stk[5003],tot,mk2[503];
vector<int>lst[503];
void dfs(int now){
	for(int i=1;;i++){
		if(F[F[now][i-1]][i-1]==0)break;
		F[now][i]=F[F[now][i-1]][i-1];
	}
	for(int i=head[now];i;i=E[i].nxt){
		if(E[i].ed==F[now][0])continue;
		dis[E[i].ed]=dis[now]+E[i].val;
		dep[E[i].ed]=dep[now]+1;
		F[E[i].ed][0]=now;
		dfs(E[i].ed);
	}
	return;
}
int ds(int X,int Y){
	int ret=dis[X]+dis[Y],c=20;
	if(dep[X]<dep[Y])swap(X,Y);
	while(c--)if(dep[F[X][c]]>=dep[Y])X=F[X][c];
	c=20;
	while(c--)if(F[X][c]!=F[Y][c])X=F[X][c],Y=F[Y][c];
	while(X!=Y)X=F[X][0],Y=F[Y][0];
	return ret-2*dis[X];
}
void addEdge(int st,int ed,int val){
	E[++totE].st=st;
	E[totE].ed=ed;
	E[totE].val=val;
	E[totE].nxt=head[st];
	head[st]=totE;
	return;
}
bool chk(int X,int num,int dt){
	int op=num;
	for(int i=1;i<=tot;i++){
		if(i==dt)continue;
		k8=ds(stk[dt],stk[i]);
		for(int j=1;j<=num;j++){
			if(dp[i][num-j]+k8<=X){
				op-=(j-1);
				break;
			}
			if(j==num)op-=j;
		}
	}
	if(op<=0)return false;
	return true;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&k1,&k2,&k3);
		addEdge(k1,k2,k3);
		addEdge(k2,k1,k3);
	}
	for(int i=1;i<=n;i++)if(E[head[i]].nxt==0)stk[++tot]=i;
	scanf("%d%d",&s,&m);
	for(int i=1;i<=m;i++)scanf("%d",&wz[i]);
	dep[s]=1;
	dfs(s);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=tot;j++){
			lft=0;
			rgt=100000000;
			while(lft<rgt){
				mid=((lft+rgt)>>1);
				if(chk(mid,i,j))rgt=mid;
				else lft=mid+1;
			}
			dp[j][i]=lft;
		}
	}
	for(int i=1;i<=m;i++){
		mk[i]=wz[i];
		while(F[mk[i]][0]!=s)mk[i]=F[mk[i]][0];
		sum[mk[i]]++;
	}
	for(int i=1;i<=tot;i++){
		if(stk[i]==s){
			printf("%d",dp[i][m]);
			return 0;
		}
		mk2[i]=stk[i];
		while(F[mk2[i]][0]!=s)mk2[i]=F[mk2[i]][0];
		lst[mk2[i]].emplace_back(i);
	}
	lft=0;
	rgt=100000000;
	while(lft<rgt){
		mid=((lft+rgt)>>1);
		f=0;
		for(int i=1;i<=n;i++){
			k1=sum[i];
			for(auto j:lst[i]){
				for(int u=1;u<=sum[i];u++){
					if(dp[j][m-u]+dis[stk[j]]<=mid){
						k1-=(u-1);
						break;
					}
					if(u==sum[i])k1-=u;
				}
			}
			if(k1>0)f=1;
		}
		if(f)rgt=mid;
		else lft=mid+1;
	}
	printf("%d",lft);
	return 0;
}
```


---

## 作者：daniEl_lElE (赞：5)

考虑 $dp_{i,j}$ 表示现在警察跑到 $i$ 点抓人，除了该点以外的还在逍遥法外的有 $j$ 人的最小时间。

考虑对于每个 $dp_{i,j}$ 分别二分答案。对于每个叶子结点计算出到该叶子结点抓人至多转移到 $dp_{x,k}$，则该点至多藏 $j-k$ 人才能让警察不能成功。然后就可以计算出以 $i$ 为根所有叶子至多藏的人数的和，如果大于等于 $j$ 警察就不能在二分的时间内捉人，否则可以。

总复杂度 $O(n^3m\log V)$，$V$ 为答案范围~~我也不知道就取了 $10^{18}$~~，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<pair<int,int>> vc[55];
int dp[55][55],cnt[55];
int f[55];
int M;
void dfs(int now,int fa,int lim){
	if(vc[now].size()==1&&fa!=0){
		for(int j=0;j<M;j++){
			if(dp[now][j]>=lim){
				f[now]=M-j;
				break;
			}
		}
	}
	for(auto v:vc[now]){
		if(v.first==fa) continue;
		dfs(v.first,now,lim-v.second);
		f[now]+=f[v.first];
	}
}
void calc(int now,int fa){
	for(auto v:vc[now]){
		if(v.first==fa) continue;
		calc(v.first,now);
		cnt[now]+=cnt[v.first];
	}
}
signed main(){
	int n; cin>>n;
	for(int i=1;i<n;i++){
		int u,v,w; cin>>u>>v>>w;
		vc[u].push_back(make_pair(v,w));
		vc[v].push_back(make_pair(u,w));
	}
	int s; cin>>s;
	int m; cin>>m;
	memset(dp,1,sizeof(dp));
	for(int i=1;i<=n;i++) dp[i][0]=0;
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			M=j;
			int L=0,R=1e18;
			while(L<R){
				int mid=(L+R+1)>>1;
				memset(f,0,sizeof(f));
				dfs(i,0,mid);
				if(f[i]>=j) L=mid;
				else R=mid-1;
			}
			dp[i][j]=L;
//			cout<<dp[i][j]<<" ";
		}
//		cout<<"\n";
	}
	for(int i=1;i<=m;i++){
		int x; cin>>x;
		cnt[x]++;
	}
	calc(s,0);
	int L=0,R=1e18;
	while(L<R){
		int mid=(L+R+1)>>1;
		memset(f,0,sizeof(f));
		dfs(s,0,mid);
		bool ok=1;
		for(auto v:vc[s]){
			if(f[v.first]<cnt[v.first]){
				ok=0;
			}
		}
		if(ok) L=mid;
		else R=mid-1;
	}
	cout<<L;
	return 0;
}
```

---

## 作者：Memory_of_winter (赞：5)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/11193001.html)

**题目大意：** 有一棵$n$个点的带边权的树，上面有$m$个罪犯，速度为任意大，有一个警察在点$S$，速度为$1$。若警察和罪犯在同一个地方，罪犯就被干掉了，警察希望干掉所有罪犯时间最短，而罪犯希望最大化这个时间。求出这个时间，若无解输出`Terrorists win`。$n,m\leqslant 50$

**题解：** 一定有解，令$f[u][v][x][y]$表示从警察$u$走到$v$，$v$关于$u$的子树内有$x$个罪犯，另外的节点还有$y$个罪犯的最小时间。警察一定选择$dp$值最小的走，而罪犯的分布会使每条边$dp$值得最小值最大。用类似背包的东西转移。在转移时另开一个数组$g[i][j]$表示现在是$v$的第$i$棵子树，放了$j$个罪犯所需的时间。
$$
g[i][j]=\max\{g[i][j],\min\{g[i-1][j-k],dp[v][v'][k][x+y-k]+w\}\}
$$
$v'$为$v$的第$i$棵子树，$k$为$v'$这棵子树放几个罪犯，$w$为$v\to v'$的边权。$g$明显可以用$01$背包的方法把第一维滚掉。到叶子的时候抓住罪犯然后返回。记忆化搜索即可。



**C++ Code：**

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn = 60, inf = 0x3f3f3f3f;

int head[maxn], cnt = 1, deg[maxn];
struct Edge {
	int to, nxt, w;
} e[maxn << 1];
inline void addedge(int a, int b, int c) {
	e[++cnt] = (Edge) { b, head[a], c }; head[a] = cnt;
	e[++cnt] = (Edge) { a, head[b], c }; head[b] = cnt;
	++deg[a], ++deg[b];
}

int n, m, S, sz[maxn];
int f[maxn << 1][maxn][maxn];
void dfs(int u, int fa = 0) {
	for (int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].to;
		if (v != fa) dfs(v, u), sz[u] += sz[v];
	}
}
int dp(int E, int x, int y) {
	if (!x && !y) return 0;
	int &F = f[E][x][y], u = e[E].to;
	if (~F) return F;
	if (deg[u] == 1) {
		if (y == 0) return 0;
		return F = dp(E ^ 1, y, 0) + e[E].w;
	}
	int g[maxn];
	memset(g, 0, sizeof g), g[0] = inf;
	for (int i = head[u], v; i; i = e[i].nxt) if (i ^ E ^ 1) {
		v = e[i].to;
		for (int j = x; j; --j)
			for (int k = j; k; --k)
				g[j] = std::max(g[j], std::min(g[j - k], dp(i, k, x + y - k) + e[i].w));
	}
	return F = g[x];
}

int main() {
	std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
	std::cin >> n;
	for (int i = 1, a, b, c; i < n; ++i) {
		std::cin >> a >> b >> c;
		addedge(a, b, c);
	}
	std::cin >> S >> m;
	for (int i = 0, x; i < m; ++i) std::cin >> x, ++sz[x];
	dfs(S), memset(f, -1, sizeof f);
	int ans = inf;
	for (int i = head[S], v; i; i = e[i].nxt) {
		v = e[i].to;
		ans = std::min(ans, dp(i, sz[v], m - sz[v]) + e[i].w);
	}
	std::cout << ans << '\n';
	return 0;
}

```



---

## 作者：Jryno1 (赞：3)

## CF868E

换个角度思考的题，不是很难。

### 题意

一个 $n$ 个节点带边权的树，警察从 $s$ 出发，树节点上有 $m$ 个位置位置（可能重复）有小偷，如果警察和一个小偷在同一个节点那么这个警察就把小偷抓到了。警察的移动速度是 $1$，小偷可以瞬移。问警察能否抓到所有的小偷，如果能求最快多久。

$n,m\le 50$。

### Sol

首先显然一定有解，实在不行警察硬着头皮一个小偷一个小偷抓，因为是在一棵树上一定能够抓到。些简单的观察发现，小偷苟在叶子节点一定是不错的选择，这样可以甩警察尽可能远。

反过来想，警察每次抓到小偷一定是在一个叶子节点。这时候可能还会剩下一些小偷，由于警察是在一个叶子节点，那么剩下小偷可以趁这个时间随意调整位置，让警察再次出发的时候消耗时间最多。因为可以随意移动，我们不妨设 $f_{u,i}$ 表示警察目前在 $u$ 这个叶子节点，还剩下 $i$ 个小偷，他们调整完之后警察最短多少时间可以抓到小偷。

状态很理想，考虑如何转移。假设剩下的每个叶子节点的小偷数量已经确定了，为 $c_u$，转移式就应该是 $f_{u,i}=\min\limits_{v\in leaves,u\neq v}dis(u,v)+f_{v,i-c_v}$。而此时小偷还有机会调整每一个位置的 $c_u$，所以这个转移还不确定。反过来考虑问题，小偷希望 $f_{u,i}$ 尽可能大，那么直接二分这个值，然后判断小偷能不能构造出来一种方案达到这种值。设目前二分的值为 $lim$，检查的时候贪心，在满足 $dis(u,v)+f_{v,i-c_v}\ge lim$ 的条件下让 $c_v$ 尽可能大。

最后统计答案，由于起始的位置不一定是叶子，但是这影响并不大，因为这个条件对于小偷的唯一限制就是一个小偷不能跑出其所在的子树。那么开始的时候记录一下每一个子树中小偷总数然后再贪心即可。

复杂度 $\mathcal{O}(n^4\log ans)$ 其实还可以优化，因为 $f_{u,i}$ 随着 $i$ 增大是单调递增的，找 $c_v$ 最优解的时候也可以二分。

[CF 提交记录](https://codeforces.com/contest/868/submission/229697195)

---

## 作者：SFlyer (赞：1)

这一题最重要的是设计状态。

首先，坏人不可能不被抓到，因为你再怎么说都可以一个一个抓，这样每一次逼到叶子节点。

一个显然的状态是 $dp_{s,(a_1\sim a_m)}$ 代表警察在 $s$，坏人在 $a_1\sim a_m$ 的最小时间，但是显然会爆掉。

- 性质一：因为坏人速度无限大，所以警察来抓他们的时候一定呆在叶子节点。

如果不在叶子节点，一定可以省去时间。

- 性质二：坏人在哪一个节点不重要，只和警察的相对位置重要。

这也是因为坏人的速度是无限大。

所以现在有另一个状态 $dp_{u,(c_{1}\sim c_{sz})}$ 代表警察在 $u$，在 $1\sim sz$ 个 $u$ 的子树内分别有 $c_1\sim c_{sz}$ 个坏人。但是还是会爆炸。

分析一下爆炸的本质。因为我们是模拟警察从一个节点到另一个节点，所以相对方位有很多种。但是其实因为坏人速度无限大，其实警察可以看作是从一个边到另一个边，因为坏人可以“预判”警察下一步是什么（可以想象为，警察在 $u\rightarrow v$ 中间时定住了，$u,v$ 两边的坏人分别可以随意交换顺序）。

因此设计状态：$dp_{u,v,al,c}$ 表示目前警察 $u\rightarrow v$ 这个方向，警察面向的子树内有 $c$ 个坏人，现在一共还剩 $al$ 个坏人。

考虑转移：枚举下一步，那么新的时间其实就是坏人的所有排列的下一步得到的最小时间。这个可以用一个背包求得。

代码很好写。

```c++
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 55;

int n,s,f[N][N][N][N],d[N][N],m,x[N],cnt,vis[N]; 
vector<int> e[N];

void dfs(int u,int fa){
	cnt+=vis[u];
	for (auto v : e[u]){
		if (v^fa) dfs(v,u);
	}
}

int sol(int u,int v,int al,int in){
	auto &ans=f[u][v][al][in];
	if (~ans) return ans;
	if (!al) return ans=0;
	if (e[v].size()==1) return ans=sol(v,u,al-in,al-in)+d[u][v];
	int g[N];
	g[0]=1e9;
	for (int i=1; i<=al; i++) g[i]=-1e9;
	for (auto p : e[v]){
		if (p^u){
			for (int i=in; i; i--){
				for (int j=1; j<=i; j++){
					g[i]=max(g[i],min(g[i-j],sol(v,p,al,j)+d[u][v]));
				}
			}
		}
	}
	return ans=g[in];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n;
	for (int i=1; i<n; i++){
		int u,v,w;
		cin>>u>>v>>w;
		e[u].push_back(v);
		e[v].push_back(u);
		d[u][v]=d[v][u]=w;
	}
	cin>>s>>m;
	for (int i=1; i<=m; i++){
		cin>>x[i];
		vis[x[i]]++;
	}
	memset(f,-1,sizeof f);
	int ans=1e9;
	for (auto u : e[s]){
		cnt=0;  
		dfs(u,s);
		ans=min(ans,sol(s,u,m,cnt));
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

