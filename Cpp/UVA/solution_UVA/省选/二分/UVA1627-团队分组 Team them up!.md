# 团队分组 Team them up!

## 题目描述

你的任务是按照以下要求将一些人员划分到两个队伍中。
1. 每个人都属于其中的一个队伍。
2. 每个队伍至少包含一个人。
3. 每个人都认识几个人，而同一个队伍中的人必须两两认识。
4. 两个队伍的人数尽可能的接近。
这个任务可能有多组解或无解，你只需要输出其中的任意一种或者宣布无解。

# 题解

## 作者：Uniecho1 (赞：6)

这题真的有难度欸

首先就是判断有无解

正着来想好想有点来...

反着来吧？

我么在两个不认识的人之间连无向边（注意，只有单方面不认识就算，因为他俩绝对不能在一个队伍里了）

然后我们就可以跑一发二分图染色（有边-->不能在同一个队伍里，当然图不一定联通，所以每个点都得跑一次）

如果染色失败？$No\ solution$呗

染色成功？

我们注意到，对于每一个成功染色的连通块，我们可以把它看成一个整体，整体之间互不影响

这个整体具有两个属性：可以向第一个队贡献多少人，向另一个队贡献多少人

然后就是[多米诺骨牌](https://www.luogu.org/problem/P1282)啦

当然还是要讲一下的

我们不妨假设先把每个整体中更多的给一队，少一些的给二队

那么我们肯定可以通过翻转一些整体来减小两队的差值

翻转的对答案产生的影响是什么呢？？

显然是$2*abs(a-b)$嘛，其中$a,b$就是那两个属性啦

然后就直接从大到小枚举能使差值减小多少（当然我写的记搜）

然后输出一下就完事啦（话说记录每个状态由哪个状态转移这种方法应该都会吧）

然后就没有了...

上代码
```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define mkp make_pair
using namespace std;
const int maxn=105;
int T,N,tot,sum,cnt;
int vis[maxn],col[maxn],val[maxn];
int Dp[maxn][maxn],Fr[maxn][maxn];
vector<int>G[maxn],P[maxn][2];
pii vec[maxn];
bool Dfs(int u,int c) {
	col[u]=c;
	for(int i=0; i<G[u].size(); i++) {
		int v=G[u][i];
		if(col[v]!=-1&&col[v]!=c^1)
			return false;
		if(col[v]==-1&&!Dfs(v,c^1))
			return false;
	}
	return true;
}
bool Check(int n,int k) {
	if(!k)
		return true;
	if(!n||k<0)
		return false;
	if(Dp[n][k]!=-1)
		return Dp[n][k];
	Dp[n][k]=0;
	if(Check(n-1,k-val[n]))
		Dp[n][k]=1,Fr[n][k]=1;
	else if(Check(n-1,k))
		Dp[n][k]=1,Fr[n][k]=0;
	return Dp[n][k];
}
void Print1(int n,int k) {
	while(n) {
		if(Fr[n][k]==1) {
			for(int i=0; i<P[n][1].size(); i++)
				cout<<P[n][1][i]<<" ";
			k-=val[n];
			--n;
		} else {
			for(int i=0; i<P[n][0].size(); i++)
				cout<<P[n][0][i]<<" ";
			--n;
		}
	}
}
void Print2(int n,int k) {
	while(n) {
		if(Fr[n][k]==0) {
			for(int i=0; i<P[n][1].size(); i++)
				cout<<P[n][1][i]<<" ";
			--n;
		} else {
			for(int i=0; i<P[n][0].size(); i++)
				cout<<P[n][0][i]<<" ";
			k-=val[n];
			--n;
		}
	}
}
int main() {
	//freopen("in.txt","r",stdin);
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--) {
		tot=sum=cnt=0;
		memset(vis,0,sizeof(vis));
		memset(col,0,sizeof(col));
		memset(val,0,sizeof(val));
		memset(Dp,0,sizeof(Dp));
		memset(Fr,0,sizeof(Fr));
		for(int i=1; i<=100; i++)
			G[i].clear(),P[i][0].clear(),P[i][1].clear();
		cin>>N;
		for(int i=1; i<=N; i++) {
			memset(vis,0,sizeof(vis));
			int x;
			vis[i]=1;
			while(cin>>x&&x) {
				vis[x]=1;
			}
			for(int j=1; j<=N; j++)
				if(!vis[j])
					G[i].push_back(j),G[j].push_back(i);
		}
		memset(col,-1,sizeof(col));
		memset(vis,0,sizeof(vis));
		bool flag=0;
		for(int i=1; i<=N; i++)
			if(col[i]==-1) {
				if(!Dfs(i,0))
					flag=1;
				else {
					++cnt;
					pii cur;
					for(int j=1; j<=N; j++)
						if(!vis[j]&&col[j]!=-1) {
							vis[j]=1;
							if(col[j]==0)
								P[cnt][0].push_back(j),cur.first++;
							else
								P[cnt][1].push_back(j),cur.second++;
						}
					if(cur.first<cur.second)
						swap(cur.first,cur.second),swap(P[cnt][0],P[cnt][1]);
					tot+=abs(cur.first-cur.second);
					val[cnt]=2*abs(cur.first-cur.second);
					vec[cnt]=cur;
				}
			}
		if(flag)
			cout<<"No solution"<<endl;
		else {
			memset(Dp,-1,sizeof(Dp));
			for(int i=tot; i>=0; i--) {
				if(Check(cnt,i)) {
					int delta=tot-i;
					cout<<(delta+N)/2<<" ";
					Print1(cnt,i);
					cout<<endl;
					cout<<N-(delta+N)/2<<" ";
					Print2(cnt,i);
					cout<<endl;
					break;
				}
			}
		}

		if(T)
			cout<<endl;
	}

	return 0;
}
```

---

## 作者：kkxhh (赞：2)

## 思路来自 刘汝佳《算法竞赛入门经典第二版》 p291

大概做的事情就是先bfs一边对每个点进行黑白染色，判断解的存在性，然后做一个01背包就好了

代码十分丑陋qaq

大概解释一下代码里变量的作用

$c$ 是黑白染色里的颜色

$m$ 是邻接矩阵

$d$ 是dp转移用的

$p$ 是用来记录每个状态是从哪一个状态转移过来的

$head$,$nex$,$v$ 是一个链表（输出答案时要用到）

$w$ 记录每个图黑白点数的差值

$r$ 记录黑白点分别有多少个

$tot$ 的图的编号

$lot$ 是链表的编号

代码内部应该没有什么不好理解的吧qwq

~~效率莫名地还挺高的~~

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
#define d(x,i) d[x][i+125]
#define p(x,i) p[x][i+125]

int t,n,m[110][110],d[110][250],p[110][250],tot,lot,r[2][110],w[110],head[2][110],nex[110],v[110],c[110],tag;

inline int read(){
    int num=0,k=1; char c=getchar();
    while(c>'9' || c<'0') k=(c=='-')?-1:k,c=getchar();
    while(c>='0' && c<='9') num=num*10+c-'0',c=getchar();
    return num*k;
}

int bfs(int x){
    int tmp=1; queue<int> q;
    c[x]=1; r[1][tot]++; nex[++lot]=head[1][tot]; head[1][tot]=lot; v[lot]=x; q.push(x); 
    while(!q.empty()){
        int t=q.front(),u=(c[t]==1)?0:1; q.pop();
        for(int i=1;i<=n;i++) if(i!=t && (!m[i][t] || !m[t][i])){
            if(!c[i]) {c[i]=-c[t]; tmp+=c[i]; r[u][tot]++; nex[++lot]=head[u][tot]; head[u][tot]=lot; v[lot]=i; q.push(i);}
            else if(c[i]==c[t]) return -1;
        }
    }
    return (tmp>=0)?tmp:-tmp;
}

void printans(int x){
    int t1=0,t2=0,a1[110]={0},a2[110]={0};
    for(int i=tot;i>=1;i--){
        if(p(i,x)<x){
            if(r[1][i]>r[0][i]){
                for(int j=head[1][i];j;j=nex[j]) a1[++t1]=v[j];
                for(int j=head[0][i];j;j=nex[j]) a2[++t2]=v[j];
            }
            else{
                for(int j=head[1][i];j;j=nex[j]) a2[++t2]=v[j];
                for(int j=head[0][i];j;j=nex[j]) a1[++t1]=v[j];
            }
        }
        else{
            if(r[1][i]>r[0][i]){
                for(int j=head[1][i];j;j=nex[j]) a2[++t2]=v[j];
                for(int j=head[0][i];j;j=nex[j]) a1[++t1]=v[j];
            }
            else{
                for(int j=head[1][i];j;j=nex[j]) a1[++t1]=v[j];
                for(int j=head[0][i];j;j=nex[j]) a2[++t2]=v[j];
            }
        }
        x=p(i,x);
    }
    printf("%d",t1); for(int i=1;i<=t1;i++) printf(" %d",a1[i]); printf("\n");
    printf("%d",t2); for(int i=1;i<=t2;i++) printf(" %d",a2[i]); printf("\n");
}

int main(){
    t=read();
    while(t--){
        n=read(); lot=tot=0; tag=1;
        memset(m,0,sizeof(m)); memset(w,0,sizeof(w)); memset(c,0,sizeof(c)); memset(d,0,sizeof(d)); memset(r,0,sizeof(r));
        memset(p,0,sizeof(p)); memset(head,0,sizeof(head)); memset(nex,0,sizeof(nex)); memset(v,0,sizeof(v));
        for(int i=1,a;i<=n;i++) while((a=read())) m[i][a]=1;
        for(int i=1;i<=n && tag;i++)
            if(!c[i]) tot++,w[tot]=bfs(i),tag=(w[tot]!=-1);
        if(!tag) printf("No solution\n");
        else{
            d(0,0)=1;
            for(int i=1;i<=tot;i++) for(int j=-n;j<=n;j++)
                if(d(i-1,j)) d(i,j+w[i])=d(i,j-w[i])=1,p(i,j+w[i])=p(i,j-w[i])=j;
            for(int i=0;i<=n;i++)
                if(d(tot,i)) {printans(i); break;}
                else if(d(tot,-i)) {printans(-i); break;}
        }
        if(t) printf("\n");
    }
    return 0;
}

```

---

## 作者：Mirasycle (赞：1)

典题。

分成两个队伍考虑二分图，发现同一个队伍的人必须两两认识，所以对于非双向认识的人必须在不同的队伍中。于是我们将非双向认识的人之间连边，然后跑二分图染色。如果无法染色，就是无解即分组失败。

如果可以染色，现在目标就是合并若干个二分图，我们可以将一个的左部和另一个的右部划分在一起，这样就要求把这个的右部和另一个的左部也划分在一起。我们记录 $w_i=size_1-size_2$，然后每次对于队伍人数差可以考虑加入 $w_i$ 或者 $-w_i$，直接跑一遍背包 dp 即可。

时间复杂度 $O(n^2)$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
const int maxn=110;
int a[maxn][maxn],col[maxn],w[maxn];
int n,tot,dp[maxn][maxn*2],vis[maxn]; 
vector<int> team[maxn][3],ans1,ans2;
bool dfs(int u,int c){
	col[u]=c; vis[u]=1; team[tot][c].pb(u);
  	for(int v=1;v<=n;v++){
  		if(u==v||(a[u][v]&&a[v][u])) continue;
    	if(vis[v]&&col[v]==col[u]) return 0;
    	if(!vis[v]&&!dfs(v,c^1)) return 0;
	}
	return 1;
}
bool build(){
	for(int i=1;i<=n;i++){
		if(vis[i]) continue;
		team[++tot][0].clear();
		team[tot][1].clear();
		if(!dfs(i,0)) return 0;
		w[tot]=team[tot][0].size()-team[tot][1].size();
	}
	return 1;
}
void print(int ans){
	for(int i=tot,t;i>=1;i--){
		if(dp[i-1][ans-w[i]+n]) t=0,ans-=w[i]; 
		else t=1,ans+=w[i];
		for(auto v:team[i][t]) ans1.pb(v);
		for(auto v:team[i][t^1]) ans2.pb(v);
	}
	cout<<ans1.size();
	for(auto v:ans1) cout<<" "<<v;
	cout<<endl;
	cout<<ans2.size();
	for(auto v:ans2) cout<<" "<<v;
	cout<<endl;
}
void Dp(){
	dp[0][n]=1;
	for(int i=1;i<=tot;i++)
		for(int j=-n;j<=n;j++){
				dp[i][j+w[i]+n]|=dp[i-1][j+n];
				dp[i][j-w[i]+n]|=dp[i-1][j+n];
			}
	for(int ans=0;ans<=n;ans++){
		if(dp[tot][ans+n]){ 
			print(ans);
			return ;
		}else if(dp[tot][-ans+n]){
			print(-ans);
			return ;
		}
	}
}
void init(){
	ans1.clear(); ans2.clear();
	memset(a,0,sizeof(a)); tot=0;
	memset(dp,0,sizeof(dp));
  	memset(col,0,sizeof(col));
  	memset(vis,0,sizeof(vis));
}
int main(){
	int T; cin>>T;
	while(T--){
		cin>>n; init();
    	for(int i=1;i<=n;i++){ int j; while(cin>>j&&j) a[i][j]=1; }
    	if(n==1||!build()) cout<<"No solution\n";
		else Dp(); if(T) cout<<endl;
	}
	return 0;
}
```

---

## 作者：Genius_Star (赞：1)

### 思路：

正着做不好做，考虑让每个人与其不认识的人连边，那么就转化为一条边的两个端点不在一个集合中，是经典二分图问题。

因为整个图不一定联通，考虑对于每个联通块验证是否为二分图，可以用二分图染色法。

若有一个联通块不是二分图，则无解；否则求出该联通块两个集合的分别点的个数 $s_{i,1},s_{i,2}$。

因为要使得两组成员的人数之差（绝对值）尽可能小，考虑动态规划算法，令 $dp_{i,j}$ 表示考虑前 $i$ 个联通块，使得 $A$ 组刚好有 $j$ 个人是否可以分配到，初始 $dp_{0,0}=1$。

则状态转移方程为：

$$dp_{i,j} = dp_{i-1,j-s_{i,0}} ||  dp_{i-1,j-s_{i,1}}$$

设联通块个数为 $cnt$，最后因为我们要使得差尽可能小，那么要找到一个 $k$，满足 $dp_{i,k}=1$，使得 $k$ 尽量接近 $\frac{n}{2}$，枚举一下即可。

现在考虑求方案数，定义 $pre_{i,j}$ 表示 $dp_{i,j}$ 是由 $s_{i,1}$ 还是 $s_{i,2}$ 转移而来，那么可以进行回溯。

初始令 $x=k$，然后要将第 $cnt$ 联通块内是 $pre_{cnt,x}$ 集合的点加入 $A$ 组，然后令 $x \to x - s_{cnt,pre_{cnt,x}}$，回溯到上一层重复此操作。

时间复杂度为 $O(N^2)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define tidy(a) memset(a,0,sizeof(a))
using namespace std;
typedef long long ll;
typedef double db;
const ll N=105;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll T,n,x,cnt,ans;
ll t[N][2];
bool s[N][N],dp[N][N],pre[N][N];
bool f[N],h[N];
bool F;
vector<ll> E[N];
vector<ll> G[N][2];
vector<ll> ans1,ans2;
void build(){
	n=x=cnt=ans=0;
	tidy(t),tidy(s),tidy(dp),tidy(pre),tidy(f),tidy(h);
	ans1.clear(),ans2.clear();
	for(int i=0;i<N;i++){
		E[i].clear();
		G[i][0].clear();
		G[i][1].clear();
	}
}
void add(ll u,ll v){
	E[u].push_back(v);
	E[v].push_back(u);
}
void dfs(ll u,ll fa){
	G[cnt][h[u]].push_back(u);
	t[cnt][h[u]]++;
	f[u]=1;
	for(auto v:E[u]){
		if(v==fa)
		  continue;
		if(f[v]){
			if(h[v]^h[u]!=1)
			  F=0;
			continue;
		}
		h[v]=h[u]^1ll;
		dfs(v,u);
	}
}
void init(){
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(s[i][j]&&s[j][i])
			  continue;
			add(i,j);
		}
	}
}
void solve(){
	for(int i=1;i<=n;i++){
		if(!f[i]){
			++cnt;
			dfs(i,0);
		}
	}
	for(int i=1;i<=cnt;i++){
		for(int j=0;j<=n/2;j++){
			for(int k=0;k<2;k++){
				if(j>=t[i][k]){
					dp[i][j]|=dp[i-1][j-t[i][k]];
					if(dp[i-1][j-t[i][k]])
					  pre[i][j]=k;
				}
			}
		}
	}
	for(int i=n/2;i>=0;i--){
		if(dp[cnt][i]){
			ans=i;
			break;
		}
	}
}
void print(ll x){
	for(int i=cnt;i>=1;i--){
		for(auto v:G[i][pre[i][x]])
		  ans1.push_back(v);
		for(auto v:G[i][pre[i][x]^1ll])
		  ans2.push_back(v);
		x-=t[i][pre[i][x]];
	}
	sort(ans1.begin(),ans1.end());
	sort(ans2.begin(),ans2.end());
	write(ans1.size());
	for(auto v:ans1){
		putchar(' ');
		write(v);
	}
	putchar('\n');
	write(ans2.size());
	for(auto v:ans2){
		putchar(' ');
		write(v);
	}
	putchar('\n');
}
int main(){	
	T=read();
	while(T--){
		build();
		dp[0][0]=F=1;
		n=read();
		for(int i=1;i<=n;i++){
			while(1){
				x=read();
				if(!x)
				  break;
				s[i][x]=1;
			}
		}
		init();
		solve();
		if(!F)
		  puts("No solution");
		else
		  print(ans);
		if(T)
		  putchar('\n');		
	}
	return 0;
}
```

---

## 作者：Stinger (赞：1)

# 前言：

[博客使用体验更佳](https://blog.csdn.net/jvruo_shabi/article/details/109355508)

~~这份代码在vjudge上过了，洛谷RJ出锅了交不起。~~

[传送门](https://www.luogu.com.cn/problem/UVA1627)

思路来源紫书。

这道题其实~~不难~~(那你……![](https://img-blog.csdnimg.cn/20201029104445814.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2p2cnVvX3NoYWJp,size_16,color_FFFFFF,t_70#pic_center)

嗯，对的，把话说在前面，这题输出坑死~~JB~~人，每组测试数据输出后要输出**两个**换行，末行**一个**换行。

- 然后我先解释一下紫书为什么要用“不相互认识关系“来建图。因为两个人认识不一定在一个组，但是不认识一定在不同的组。

- 无解判断：对于这道题，无解只有一种可能，就是人们的“不相互认识关系”发生冲突。即当图出现一个由奇数条边构成的环的时候，问题无解。

- 具体来说，1和2不相互认识，2和4也是，4和1也是，那么这个图就构成了一个由3条边组成的环，那么1如果在0组，2肯定在1组（对面组），4肯定在0组，这样我们又可以推出1肯定在1组，矛盾，故无解。

- 然后显然，对于图中每个强连通分量，如果其中1个人选择了他的组别，这个连通分量的所有人的组别都确定了。因此对于一个强连通分量，我们只有两种决策：指定其中一个人，让他在0组或者1组。

- 可以通过大法师实现

- 于是这就是一个01背包问题，每个强连通分量可以看作一个没有体积的物品，他的价值是选择这个强连通分量给0组增加的人数-给1组增加的人数，设为 $d[i]$。对于每一个 $d[i]$，我们可以选择加上 $d[i]$，也可以反过来选，于是就变成了 $-d[i]$。

- 这个“01背包”似乎不满足最优子结构性质……

- 对付这种“01背包”，常见的状态设定是：用 $f[i][j]$ 表示前 $i$ 个物品是否能凑出 $j$ 的价值。

- 然而由于可以减 $d[i]$，$j$ 可以为负，我们需要加上偏移量。（其实由于本题的对称性，有不加偏移量的做法，但思路大同小异）。

- 方程很好列就不赘述了

- 然后就可以愉快地开始动规啦！代码里打的有注释哦！

# $Code:$

```cpp
//author：zhangqs
//date:2020/10/29
//problem:UVA1627
//Lang:C++11

#include <cstdio>
#include <cstring>
#include <vector>

#define INF 0x3fffffff

using namespace std;

int n, cnt, d[205];
bool f[205][205], mp[205][205], vis[205], dep[205];
int Pre[205][205];
vector<int> Grp1, Grp2, Group[205];//Group[x]表示第x个强连通分量有那些人

//dep[x]表示这个点x在他所属的强连通分量中的“深度”，即在一个强连通分量中，
//dep[x]值相同的两个点一定在同一组，否则一定不在同一组

//Grp1和Grp2分别表示结果中第0组和第一组的人数

inline void Clear() {
	cnt = 0;
	for (auto &i : Group) i.clear();
	Grp1.clear(), Grp2.clear();
	memset(mp, 0, sizeof(mp));
	memset(f, 0, sizeof(f));
	memset(vis, 0, sizeof(vis));
	memset(dep, 0, sizeof(dep));
}

inline int dfs(int u, bool depth) {//大法师
	int ans(1);
	vis[u] = true, dep[u] = depth, Group[cnt].push_back(u);
	for (register int i(1); i <= n; ++ i) if ((!mp[u][i] || !mp[i][u]) && !vis[i]) {
		int t(dfs(i, !depth));
		if (t == -INF) return -INF;
		ans -= t;
	}
	else if (i != u && (!mp[u][i] || !mp[i][u]) && !(depth ^ dep[i])) return -INF;//无解，出现了由奇数条边构成的环
	return ans;
}

inline void DP() {
	Pre[1][d[1] + 100] = Pre[1][d[1] - 100] = 100;
	f[1][d[1] + 100] = f[1][100 - d[1]] = true;
	for (register int i(1); i < cnt; ++ i)
	for (register int j(0); j <= 100 + n; ++ j)
	if (f[i][j]) f[i + 1][j - d[i + 1]] = f[i + 1][j + d[i + 1]] = true,
	Pre[i + 1][j - d[i + 1]] = Pre[i + 1][j + d[i + 1]] = j;//是个人都会的方程
}

inline void output(int x, int y) {
	if (x == 0) return;
	if (Pre[x][y] == y - d[x])
	for (auto i : Group[x]) if (dep[i]) Grp1.push_back(i);
	else Grp2.push_back(i);
	else for (auto i : Group[x]) if (dep[i]) Grp2.push_back(i);
	else Grp1.push_back(i);
	output(x - 1, Pre[x][y]);
}

inline void print_ans() {
	for (register int i(0); i <= n; ++ i)
	if (f[cnt][100 + i]) {output(cnt, 100 + i); break;}
	else if (f[cnt][100 - i]) {output(cnt, 100 - i); break;}
	printf("%llu", Grp1.size());
	for (auto i : Grp1)  printf(" %d", i);
	printf("\n%llu", Grp2.size());
	for (auto i : Grp2) printf(" %d", i);
	putchar('\n');
}

int main() {
	int TnT;
	scanf("%d", &TnT);
	for (register int QWQ(1); QWQ <= TnT; ++ QWQ) {
		QAQ:
		Clear();
		scanf("%d", &n);
		for (register int i(1); i <= n; ++ i) {
			int x;
			while (scanf("%d", &x), x) mp[i][x] = true;
		}
		for (register int i(1); i <= n; ++ i) if (!vis[i]) {
			++ cnt, d[cnt] = dfs(i, 1);
			if (d[cnt] == -INF) {
				puts("No solution");
				if (QWQ != TnT) putchar('\n');
				if ((++ QWQ) > TnT) return 0;
				goto QAQ;
			}
		}
		DP();
		print_ans();
		if (QWQ != TnT) putchar('\n');
	}
}
```

~~下面是经典老话：~~

和上次相比，修改了~~两~~一个笔误的地方，望管理员大大通过！

---

## 作者：AlicX (赞：1)

## Solution 

经典题。

考虑在同一个团队内的人互相是朋友关系，不妨转化一下：把不是朋友的人相互连边，那么此时同一个团队内的人互相之间则没有边。

考虑对建出来的图跑染色法，则我们会得到有数个二分图的图。考虑无解的情况：即在跑染色法时无解，则原图无解。

考虑共有 $cnt$ 个二分图，第 $i$ 个二分图左半部分的数量为 $l_i$，右半部分的数量为 $r_i$。

此时不妨设 $f_{i,j}$ 表示在前 $i$ 个二分图中，在前 $i$ 个二分图中给最终的二分图的左半部分选择了 $j$ 个人是否可行。还需要一个辅助数组 $g_{i,j}$ 表示给最终二分图的左半部分选择的是第 $i$ 个二分图的左还是右半部分。

不难推出状态转移方程：
1. $f_{i,j+l_i}=f_{i-1,j}$，此时 $g_{i,j+l_i}=0$，表示选择了左半部分。

2. $f_{i,j+r_i}=f_{i-1,j}$，此时 $g_{i,j+r_i}=1$，表示选择了右半部分。

最后利用辅助数组递归输出即可。

注意初始化以及建图用 `vector`。同学实测用链式前向星会 TLE？

```cpp
#include<bits/stdc++.h> 
#define ll long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<vector<int>,vector<int>> PII; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=110; 
int n; 
bool flg;  
int cnt=0; 
PII vec[N]; 
int col[N]; 
int g[N][N]; 
bool f[N][N]; 
bool st[N][N]; 
vector<int> e[N]; 
vector<int> t1,t2; 
il void dfs(int u,int w){  
	if(~col[u]){ 
		if(col[u]!=w) flg=false; 
		return ; 
	} col[u]=w; 
	if(!w) vec[cnt].x.push_back(u); 
	else vec[cnt].y.push_back(u); 
	for(auto to:e[u]) dfs(to,w^1); 
} 
il void print(int i,int x){ 
	if(!x) return ; 
	if(!g[i][x]){ 
		for(auto u:vec[i].x) t1.push_back(u); 
		for(auto u:vec[i].y) t2.push_back(u); 
		print(i-1,x-vec[i].x.size()); 
	} else{ 
		for(auto u:vec[i].y) t1.push_back(u); 
		for(auto u:vec[i].x) t2.push_back(u); 
		print(i-1,x-vec[i].y.size()); 
	} 
} 
il void solve(){ 
	n=read(); 
	cnt=0,flg=true; 
	t1.clear(),t2.clear(); 
	for(int i=0;i<=n;i++) 
		for(int j=0;j<=n;j++) 
			f[i][j]=st[i][j]=false,g[i][j]=-1; 
	for(int i=1,x;i<=n;i++){ 
		while(true){ 
			x=read(); 
			if(!x) break; 
			st[i][x]=true; 
		} col[i]=-1,e[i].clear(); 
		vec[i].x.clear(),vec[i].y.clear(); 
	} for(int i=1;i<=n;i++){ 
		for(int j=i+1;j<=n;j++){ 
			if(!st[i][j]||!st[j][i]) e[i].push_back(j),e[j].push_back(i); 
		} 
	} for(int i=1;i<=n;i++) if(col[i]==-1) cnt++,dfs(i,0); 
	if(!flg){ puts("No solution\n"); return ; } 
	f[0][0]=true; 
	for(int i=1;i<=cnt;i++){ 
		for(int j=0;j<=n;j++){ 
			if(!f[i-1][j]) continue; 
			g[i][j+vec[i].x.size()]=0; 
			g[i][j+vec[i].y.size()]=1; 
			f[i][j+vec[i].x.size()]=true; 
			f[i][j+vec[i].y.size()]=true; 
		} 
	} int ans=n,res=0; 
	for(int i=1;i<=n;i++) if(f[cnt][i]&&abs(n-2*i)<ans) ans=abs(n-2*i),res=i; 
	print(cnt,res); 
	printf("%d ",(int)t1.size()); 
	for(auto u:t1) printf("%d ",u); puts(""); 
	printf("%d ",(int)t2.size()); 
	for(auto u:t2) printf("%d ",u); puts("\n"); 
} 
signed main(){ 
	int T=read();  
	while(T--) solve();  
	return 0; 
} 
```


---

