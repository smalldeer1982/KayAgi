# [CEOI 2016] popeala

## 题目描述

你办了一场比赛，有 $n$ 个人参加，只有一道题，有 $m$ 个数据点，标号为 $1\sim m$，每个测试点都有一个分数 $a_i$。

现在所有选手已经提交了程序并且测评完了，你知道每个人都能通过哪些测试点。

你现在要安排捆绑测试的方式，把数据点划分为若干个连续的区间，每个区间至少有一个测试点。每个区间只要有一个测试点错误就不会得分，如果所有
点都正确得分为所有测试点的分数的和。

**你的目的是最小化所有人的得分和**。你需要对 $1\le i\le S$，输出当把所有测试点划分为 $i$ 组时，最小的所有人分数和。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 50$，$1\le m\le 2\times 10^4$，$S\le \min(50,m)，1\le a_i \le 10^4$，$\Sigma a_i\times n\le 2\times10^9$。


## 样例 #1

### 输入

```
2 3 3
4 3 5
101
110```

### 输出

```
0
8
16```

# 题解

## 作者：yzy1 (赞：5)

首先考虑朴素做法：设 $\operatorname{dp}(i,j)$ 为将前 $i$ 个测试点分成 $j$ 个子任务的最小分数，则有转移

$$
\operatorname{dp}(i,j) \gets \min_{k=0}^{i-1} \operatorname{dp}(k,j-1) + \operatorname{cnt}(k+1,i) (\textstyle \sum a_{[k+1,i]}).
$$

其中 $\operatorname{cnt}(l,r)$ 表示假设以 $[l,r]$ 区间内的测试点作为一个子任务，能通过该子任务的人数．

朴素做法的时间复杂度是 $O(nm + m^2S)$，考虑对其优化．观察到我们没有利用 $n\le 50$ 的性质．考虑到

$$
\begin{aligned}
\operatorname{dp}(i,j) &\gets \min_{k=0}^{i-1} \operatorname{dp}(k,j-1) + \operatorname{cnt}(k+1,i) \textstyle \sum a_{[k+1,i]}\\
&= \min_{k=0}^{i-1} \fcolorbox{#f66}{#fee}{$\operatorname{dp}(k,j-1) + \operatorname{cnt}(k+1,i) \textstyle \sum a_{[k+1,n]}$} - \operatorname{cnt}(k+1,i) \textstyle \sum a_{[i+1,n]}.
\end{aligned}
$$

观察到其中的 $\operatorname{cnt}(k+1,i)$ 最大值为 $n$，且该式子的红色部分的值不随 $i$ 变化．我们可以维护 $n+1$ 个双指针，第 $i+1$ 个双指针维护满足 $\operatorname{cnt}(l,r)=i$ 的极大区间，很显然这样的区间唯一．同时每个双指针维护 $S$ 个堆表示这段区间内 $j$ 取不同值的时候上式红色部分的值．我们可以在枚举 $i$ 的时候去移动这 $n+1$ 个双指针，然后直接暴力查询这些双指针对应的堆里的最小值来更新 $\operatorname{dp}(i,j)$ 即可．由于每个双指针都只会移动 $O(m)$ 次，所以该做法的时间复杂度为 $O(nmS \log m)$．

更近一步地，显然每个双指针的左右两个指针都只会向右单向移动．我们可以用一个单调队列来代替堆．时间复杂度优化至 $O(nmS)$．

代码参考见 [原始 OJ 提交](https://loj.ac/s/1782327)．


---

## 作者：Math_rad_round (赞：1)

 _[P6001](https://www.luogu.com.cn/problem/P6001)_ 
 
最简单的朴素做法就是设 $F[i][j]$ 第 $i$ 道题是 $j$ 子任务的最后一个数据时的得分最小值，转移枚举前一个子任务结束在第 $l$ 个数据点，$O(t^2S)$ 显然过不去。

糟糕的是，这道题并没有什么显而易见的决策单调性或斜优可用，因此我们需要仔细审视题目。

我们可以发现 $n\leq 50$ 的条件尚未用上，而只有 $50$ 个人意味着每一个子任务通过人数也只有 $51$ 种可能。

而如果我们钦定最后一个子任务的通过人数为 $k$。那我们可以惊奇地发现，此时对于同一个 $k$，决策优劣的顺序始终不变！

（因为对于决策上一个子任务结束于 $a,b$，从 $i-1$ 扩
展到 $i$ 分数都加上了 $k \times p[i]$。）

所以我们只需要维护 $n+1$ 个单调队列，第 $k$ 个队列维护钦定通过人数为 $k$ 时的决策。（同时保证决策点所在位置在通过 $k$ 人的范围内。）

具体来说，分 $S$ 次进行DP，每次DP顺序枚举测试点和人，如果某个人错了这一个点，则意味着从他上一次错的位置加一以后的通过人数全部减一，把这些位置（决策）从原先队列弹出并插入序号减一的队列。

如图所示（假设有三个人）

![](https://cdn.luogu.com.cn/upload/image_hosting/5xp9e484.png)

因此本题的时间复杂度为 $O(ntS)$，可以通过。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll read(){ll x=0,f=1;char a=getchar();while('0'>a||a>'9'){if(a=='-')f=-f;a=getchar();}
	while('0'<=a&&a<='9'){x=x*10+(a^48);a=getchar();}return x;}
void write(ll x,int ok=1){if(x==0)putchar('0');else{if(x<0){putchar('-');x=-x;}
	ull a=0,f=0;for(;x;f++,x/=10)a=a*10+x%10;for(;f;f--,a/=10)putchar('0'+a%10);}if(ok==1)putchar('\n');else if(ok==2)putchar(' ');}
const int N=110000,P=60;
int p[N];
int s[N];
int g[N][P];
int f[N],tm[N],fi[N];//f为DP数组，显然可以滚动节省空间。 
//fi[a] 代表从a开始，到目前点(i)有多少个人全对 
int n,e9=2e9;

struct line{
	int l[N],id,w,h;
	void clear(){w=0;h=1;}
	void push(int x){
		if(f[x]>=e9)return;int v=f[x]-s[x]*id;
		while(w>=h&&f[l[w]]-s[l[w]]*id>=v)w--;l[++w]=x;
	}
	void del(int x){if(w>=h&&l[h]==x)h++;}
	int get(int x){
		return w>=h?(f[l[h]]+id*(s[x]-s[l[h]])):e9;
	}
}l[P];
int lw[P];
//第i个人最后错了哪一道题 
int main(){
	n=read();int t=read(),nk=read();
	for(int i=1;i<=t;i++){
		s[i]=s[i-1]+(p[i]=read());
	}
	for(int i=1;i<=n;i++){
		int ok=1;l[i].id=i;
		for(int j=1;j<=t;j++){
			char a1;cin>>a1;
			g[j][i]=a1^'0';
			if(ok&&g[j][i])f[j]+=s[j];
			else ok=0;
		}
	}
	write(f[t]);
	for(int i=2;i<=nk;i++){
		for(int j=0;j<=n;j++){
			l[j].clear();lw[j]=0;
		}f[0]=e9;
		for(int j=1;j<=t;j++){
			l[fi[j]=n].push(j-1);
			for(int k=1;k<=n;k++){
				if(g[j][k]==0){
					for(int z=lw[k]+1;z<=j;z++){
						l[  fi[z]].del (z-1);
						l[--fi[z]].push(z-1);
					}lw[k]=j; 
				}
			}tm[j]=e9;
			for(int k=0;k<=n;k++)tm[j]=min(tm[j],l[k].get(j));
		}
		for(int j=0;j<=t;j++)f[j]=tm[j];
		write(f[t]);
	}
	return 0;
}

```


---

## 作者：内拉组里 (赞：0)

本题解方法为开桶 + 单调队列优化 dp。

# Pts 30

暴力 dp。

令 $ dp[i][j] $ 表示将数据点 $ [1,j] $ 分成 $ i $ 个捆绑测试点时所有人分数和的最小值。

转移 $ dp[i][j] = \min \{ dp[i - 1][k] + \sum\limits^j_{t = k + 1} (ak (k + 1,j) \times a_t) \} \qquad (k \in [0,j - 1]) $ 

$ ak (l,r) $ 表示在数据点 $ [l,r] $ 中 AK 的人数。

每一个 $ i $ 的答案就是 $ dp[i][m] $。

## Optimizations：

- 对 $ a $ 数组跑前缀和，求解 $ \sum\limits^j_{t = k + 1} a_t $。
- 对每一个人的通过情况开倍增表，求解 $ ak (k + 1,j) $。

## Analyses：

> 总时间复杂度 $ \Theta ((N + S) M^2 \log{M}) $。
>
> 总空间复杂度 $ \Theta ((N + S) M \log{M}) $。

***

# Pts 100

对于每个右端点 $ r $，可以预处理出每个人对应的最小的左端点 $ l $，使其能 AK 数据点 $ [l,r] $。

记 $ lst[i][j] $ 表示第 $ j $ 个人以 $ i $ 为右端点，所对应的最小左端点。

重新整理转移方程，

$ dp[i][j] = \min \{ dp[i - 1][k] - ak (k + 1,j) \times p[k] \} + ak (k + 1,j) \times p[j] $​ 

显而易见地，区间 $ [k + 1,j] $ 越大区间内解一定更优，这里存在一个单调性。

观察数据范围发现 $ N $ 的范围很小，考虑就每个数据点通过的人数开 $ n + 1 $ 个单调递增队列，

维护这一个数据点通过 $ [0,n] $ 人时的最优的 $ dp[i - 1][k] - ak (k + 1,j) \times p[k] $。

这里首先要对 $ lst[i][1,n] $ 进行排序，然后升序枚举 AK 人数 $ k $，

确切的来讲，这里更像一个双指针的处理，

每一次将右端点更新到不满足 $ k + 1 $ 人 AK 的最大位置，即 $ lst[j][k + 1] $；

然后将左端点更新到满足 $ k $ 人 AK 的最小位置，即 $ lst[j][k] $。

单调队列维护当前区间内最优解即可。

## Analyses：

> 总时间复杂度 $ \Theta (NMS) $。
>
> 总空间复杂度 $ \Theta (NM) $。

# Code：

```cpp
/* reference : @ZLOJ.huhangqi */
/* reference : @ZLOJ.admin */
#include	<algorithm>
#include	<iostream>
#include	<cstring>
#include	<deque>
#define		int		long long
using namespace std;
constexpr int inf = 0x3f3f3f3f3f3f3f3f;
constexpr int maxn = 55;
constexpr int maxm = 2e4+4;

namespace pts30
{
	int n, m, s;
	int a[maxm];
	int G[maxn][maxm];
	int dp[maxn][maxm];
	namespace ST
	{
		int pwd[maxm];
		int nd[maxn][maxm][20];
		
		void init (int n)
		{
			for (int i = 2; i <= m; i++)
				pwd[i] = pwd[i >> 1] + 1;
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= m; j++)
				{
					nd[i][j][0] = G[i][j];
				}
			}
			for (int k = 1; k < 20; k++)
			{
				for (int i = 1; i <= n; i++)
				{
					for (int j = 1; j + (1 << k) - 1 <= m; j++)
					{
						nd[i][j][k] = nd[i][j][k - 1] & nd[i][j + (1 << (k - 1))][k - 1];
					}
				}
			}
		}
		
		inline int rmq (int rw, int l, int r)
		{
			int k = pwd[r - l + 1];
			return nd[rw][l][k] & nd[rw][r - (1 << k) + 1][k];
		}
	}
	using namespace ST;
	
	inline int ak (int l, int r)
	{
		int ans = 0;
		for (int i = 1; i <= n; i++)
			if (rmq (i, l, r))
				ans++;
		return ans;
	}
	
	signed main (void)
	{
		cin >> n >> m >> s;
		for (int i = 1; i <= m; i++)
		{
			cin >> a[i];
			a[i] += a[i - 1];
		}
		for (int i = 1; i <= n; i++)
		{
			char s[maxm];
			cin >> s + 1;
			for (int j = 1; j <= m; j++) G[i][j] = s[j] ^ '0';
		}
		init (n);
		memset (dp, 0x3f, sizeof dp);
		dp[0][0] = 0;
		for (int i = 1; i <= s; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				for (int k = 0; k < j; k++)
				{
					dp[i][j] = min (dp[i][j], dp[i - 1][k] + ak (k + 1, j) * (a[j] - a[k]));
				}
			}
			cout << dp[i][m] << endl;
		}
	//	for (int i = 1; i <= m; i++)
	//	{
	//		for (int j = 1; j <= s; j++)
	//		{
	//			if (dp[i][j] == inf) cerr << "- ";
	//			else cerr << dp[i][j] << ' ';
	//		}
	//		cerr << endl;
	//	}
		return 0;
	}
}

namespace pts100
{
	int a[maxm];
	int dp[2][maxm];
	int n, m, s, pre;
	int lst[maxm][maxn];				/* last time to fail for each one */
	struct Q
	/* monoin */
	{
		int id;
		deque<int> q;
		
		inline int calc (int idx)
		{
			return dp[pre][idx] - id * a[idx];
		}
		
		void clear (void)
		{
			q.clear();
		}
		
		void push (int x)
		{
			while (!q.empty() && calc (q.back()) >= calc (x)) q.pop_back();
			q.push_back(x);
		}
		
		void pop (int idx)
		{
			while (!q.empty() && q.front() < idx) q.pop_front();
		}
		
		int top (void)
		{
			if (q.empty()) return inf;
			return calc (q.front());
		}
	}q[maxn];
	
	signed main (void)
	{
		cin >> n >> m >> s;
		for (int i = 1; i <= m; i++)
		{
			cin >> a[i];
			a[i] += a[i - 1];
		}
		for (int i = 1; i <= n; i++)
		{
			char s[maxm];
			cin >> s + 1;
			for (int j = 1; j <= m; j++)
			{
				if (s[j] ^ '0') lst[j][i] = lst[j - 1][i];
				else lst[j][i] = j;
			}
		}
		for (int i = 1; i <= m; i++)
		{
			sort (lst[i] + 1, lst[i] + n + 1);
			lst[i][n + 1] = i;
		}
		memset (dp, 0x3f, sizeof dp);
		dp[0][0] = 0;
		for (int i = 0; i <= n; i++) q[i].id = i;
		for (int i = 1; i <= s; i++)
		{
			int now = i & 1;
			pre = now ^ 1;
			for (int j = 0; j <= n; j++) q[j].clear();
			for (int j = i; j <= m; j++)
			{
				dp[now][j] = inf;
				for (int k = 0; k <= n; k++)
				{
					for (int t = max (i - 1, lst[j - 1][k + 1]); t < lst[j][k + 1]; t++) q[k].push(t);
					q[k].pop(lst[j][k]);
					dp[now][j] = min (dp[now][j], q[k].top() + k * a[j]);
				}
			}
			cout << dp[now][m] << endl;
		}
		return 0;
	}
}

signed main (void)
{
	return pts100::main ();
}
```

---

## 作者：cike_bilibili (赞：0)

考虑 DP。

自然地设 $f_{i,j}$ 表示第 $i$ 个测试点之前划分了 $j$ 段的最小得分，于是有朴素方程：
$$$ f_{i,j}=\min_{k=0}^{i-1} \{f_{k,j-1}+Val(k+1,i) \}$$$

其中 $Val(l,r)$ 表示将区间 $[l,r]$ 划分为一个子任务的得分，直接暴力枚举复杂度是 $O(T^2S)$ 的。

考虑优化，改写一下式子：
$$$ f_{i,j}=\min_{k=0}^{i-1} \{f_{k,j-1}+p(pre_i-pre_k) \} $$$

其中 $p$ 是区间 $[k+1,i]$ 中通过了所有测试点的人数，$pre_i$ 表示前 $i$ 个测试点的得分之和，我们发现最多只有 $50$ 个人，我们就可以用每一段整体去转移，相当于每一段求一个区间最值，如果写线段树的话时间复杂度是 $O(TNS\log T)$ 的。

但常数过大可能无法通过，我们发现每次添加一个元素时，每一个表示连续段的指针只会往后挪，相当于滑动窗口，单调队列维护即可，时间复杂度 $O(NTS)$。

# Code


```cpp
#include <bits/stdc++.h>
#define ls (i<<1)
#define rs (i<<1|1)
using namespace std;
inline int read(){
	int ans=0,w=1;
	char ch=getchar();
	while(ch<48||ch>57){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>=48&&ch<=57){
		ans=(ans<<1)+(ans<<3)+ch-48;
		ch=getchar();
	}
	return w*ans;
}
int n,t,s;
int p[20005];
int a[55][20005];
int f[20005][55];
int pre[20005];
set<pair<int,int> >S;
int lst[55];
struct Segment_tree{
	int que[20005];
	int id[20005];
	int l,r;
	int ql,qr;
	void build(){
		memset(que,0,sizeof que);
		memset(id,0,sizeof id);
		l=0,r=-1;
		ql=0,qr=-1;
	}
	int ask(int ll,int rr,int j,int tol){
		while(qr<rr){
			++qr;
			int val=f[qr][j]-tol*pre[qr];
			while(r>=l&&que[r]>=val)--r;
			que[++r]=val,id[r]=qr;
		}
		ql=ll;
		while(id[l]<ql)++l;
		// cout<<"*** "<<ll<<' '<<rr<<' '<<l<<' '<<r<<' '<<que[l]<<"\n";
		if(l>r)return 2e9;

		else return que[l];
	}
}T[55];
void find(int i,int j){
	auto it=S.end();
	int lst=i,tol=n;
	do{
		--it;
		// cout<<i<<' '<<j<<' '<<it->first<<' '<<it->second<<' '<<tol<<' '<<lst<<' '<<pre[i]<<' '<<T[tol].ask(it->first,lst-1,j-1,tol)<<'\n';
		if(it->first!=lst){
			f[i][j]=min(f[i][j],tol*pre[i]+T[tol].ask(it->first,lst-1,j-1,tol));
		}
		--tol,lst=it->first;
	}while(it!=S.begin());
	// cout<<"*** "<<f[i][j]<<"\n";
}
char ch[20005];
signed main(){
	n=read(),t=read(),s=read();
	for(int i=1;i<=t;i++)p[i]=read(),pre[i]=pre[i-1]+p[i];
	for(int i=1;i<=n;i++){
		scanf("%s",ch+1);
		for(int j=1;j<=t;j++){
			a[i][j]=ch[j]-'0';
		}
	}
	for(int i=0;i<=n;i++){
		S.insert({0,i});
		T[i].build();
	}
	memset(f,0x3f,sizeof f);
	f[0][0]=0;
	for(int j=1;j<=s;j++){
		
		for(int i=1;i<=t;i++){
			for(int k=1;k<=n;k++){
				if(a[k][i]==0){
					S.erase({lst[k],k});
					lst[k]=i;
					S.insert({lst[k],k});
				}
			}
			find(i,j);
		}
		S.clear();
		for(int i=0;i<=n;i++){
			// cout<<i<<' '<<lst[i]<<'\n';
			lst[i]=0;
			S.insert({0,i});
			T[i].build();
		}
	}
	for(int i=1;i<=s;i++){
		cout<<f[t][i]<<'\n';
	}
	return 0;
}
/*
很容易列出方程 f[i][j]=min{f[k][j-1]+p*(pre[i]-pre[k])}
具体p我们不知道是多少，考虑每个人的最近一次wa的时刻，排个序用区间最值更新就行了
滑动窗口->单调队列
*/
/*
2 3 3
4 3 5
101
110
*/
```

---

## 作者：cwfxlh (赞：0)

# [P6001](https://www.luogu.com.cn/problem/P6001)          

发现 $S$ 很小，所以令 $dp_i$ 表示分段分到 $i$ 的最小值，做 $S$ 次转移就可以得到所有答案。      

暴力转移一次应该是最好能做到 $O(\frac{n^2m}{\omega})$，考虑优化。转移形如 $g_j=\min(g_j,dp_i+c\times (pre_j-pre_i))$，其中 $c$ 是能通过 $[i+1,j]$ 的测试点的人数。发现固定 $i$，$c$ 随 $j$ 的增长而减小，并且最多有 $n+1$ 种取值，于是维护每个人当前第一个无法通过的测试点位置，然后系数分成 $O(n)$ 段转移，可以表示成区间取 $\min$ 的形式。表示成后缀取 $\min$ 是不优的，不会影响答案，所以这部分可以做到不带 $\log$，不过对于指针的排序需要一个小 $\log$，复杂度 $O(nmS\log n)$。          

代码：        


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,S,pre[500003],dp[20003],g[20003],zz[53];
int stk[53];
string a[53];
int mnv[20003][53];
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>m>>S;
    for(int i=1;i<=m;i++)cin>>pre[i];
    for(int i=1;i<=m;i++)pre[i]+=pre[i-1];
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++)dp[i]=2000000000000ll;
    for(int i=1;i<=S;i++){
        for(int j=0;j<=m;j++){
            for(int u=0;u<=n;u++)mnv[j][u]=2000000000000ll;
            g[j]=2000000000000ll;
        }
        for(int j=1;j<=n;j++)zz[j]=1;
        for(int j=0;j<m;j++){
            for(int u=1;u<=n;u++){
                zz[u]=max(zz[u],j+1);
                while(zz[u]<=m&&a[u][zz[u]-1]=='1')zz[u]++;
                stk[u]=zz[u];
            }
            sort(stk+1,stk+n+1);
            stk[0]=j+1;
            for(int u=0;u<=n;u++)mnv[stk[u]][n-u]=min(mnv[stk[u]][n-u],dp[j]-pre[j]*(n-u));
            for(int u=0;u<=n;u++){
                mnv[j+1][u]=min(mnv[j+1][u],mnv[j][u]);
                g[j+1]=min(g[j+1],mnv[j+1][u]+u*pre[j+1]);
            }
        }
        for(int j=0;j<=m;j++)dp[j]=g[j];
        cout<<dp[m]<<'\n';
    }
    return 0;
}
```

---

