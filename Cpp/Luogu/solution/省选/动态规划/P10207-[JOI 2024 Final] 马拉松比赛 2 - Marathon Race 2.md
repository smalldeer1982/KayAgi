# [JOI 2024 Final] 马拉松比赛 2 / Marathon Race 2

## 题目描述

JOI 大道是一条东西向的长度为 $L$ 米的道路，地点 $l$ 位于从道路的西端走 $l\ (0 \leq l \leq L)$ 米的地方。

今年 JOI 大道上第一次举办了马拉松大会。这个马拉松大会的规则和一般的不同，是按照以下的方式进行的：

- 道路上放了 $N$ 个球，第 $i\ (1 \leq i \leq N)$ 个球放在地点 $X_{i}$。有些地方可能有多个球放在一起。
- 参加者从规定的起点出发，拿到所有 $N$ 个球后，如果在规定的时间内到达规定的终点，就算是完赛。但是，如果把拿到的球放在地上就会被取消资格。

这个大会的起点，终点和时间限制还没有公布，但是已经公布了 $Q$ 个可能的方案。第 $j\ (1 \leq j \leq Q)$ 个方案的起点是地点 $S_{j}$，终点是地点 $G_{j}$，时间限制是 $T_{j}$ 秒。

理恵是马拉松大会的其中一名运动员。她拿起一个球要花 $1$ 秒，拿着 $x$ 个球在道路上跑 $1$ 米要花 $x+1$ 秒。

给出 JOI 大道，球，方案的信息。编写一个程序，对于每个方案判断理恵能不能完赛。

## 说明/提示

对于所有输入数据，满足：

- $1 \leq N \leq 5\times 10^5$
- $1 \leq L \leq 5\times 10^5$
- $0 \leq X_{i} \leq L\ (1 \leq i \leq N)$
- $1 \leq Q \leq 5\times 10^5$
- $0 \leq S_{j} \leq L\ (1 \leq j \leq Q)$
- $0 \leq G_{j} \leq L\ (1 \leq j \leq Q)$
- $1 \leq T_{j} \leq 5\times 10^5\ (1 \leq j \leq Q)$

详细子任务附加限制及分值如下表所示。

|子任务|	附加限制|	分值|
|:-:|:-:|:-:|
|1|	$N \leq 7, Q \leq 10, S_{j}=0, G_{j}=0\ (1 \leq j \leq Q)$|	7
|2|	$N \leq 7, Q \leq 10$|	7
|3|	$N \leq 14, Q \leq 10$|	10
|4|	$N \leq 100, Q \leq 10$|	28
|5|	$N \leq 2000, Q \leq 10$|	10
|6|	$N \leq 2000$|	19
|7|	无附加限制	|19

## 样例 #1

### 输入

```
3 100
30 80 30
3
0 100 403
0 100 300
0 100 262```

### 输出

```
Yes
Yes
No```

## 样例 #2

### 输入

```
3 100
30 80 30
3
0 0 403
0 0 300
0 0 262```

### 输出

```
Yes
No
No```

## 样例 #3

### 输入

```
6 100
0 50 100 0 50 100
4
20 70 600
70 20 600
10 40 600
40 10 600```

### 输出

```
No
Yes
No
Yes```

# 题解

## 作者：Perta (赞：12)

拿球的总时间是固定的，这个可以不考虑。

一个朴素的想法是，设 $f_{S,i}$ 表示已经拿了 $S$ 的球，现在在第 $i$ 个球的位置所用的最短时间，转移是朴素的，可以获得 24 分。

我们可以发现一个比较显然的性质：位于 $G$ 同一侧的球，离 $G$ 较远的球必然先于较近的被拿。

那么实际上有效状态 $S$ 只有 $O(N^2)$ 个。设 $f_{l,r,0/1}$ 表示拿了编号范围 $[1,l)\cup(r,N]$ 的球，现在在第 $l/r$ 个球的位置所需的最短时间，转移是朴素的。初始有 $f_{1,N,0}=\lvert S-X_1\rvert,f_{1,N,1}=\lvert S-X_N\rvert$。

设 $G$ 左右两边的小球编号分别为 $p_1,p_2$（也可能只有一个），所需时间为 $\min(f_{p_1,p_1,0}+(N+1)\lvert X_{p_1}-G\rvert,f_{p_2,p_2,0}+(N+1)\lvert X_{p_2}-G\rvert)$。

对于多次询问，我们不妨直接设另一个数组 $g$，含义与 $f$ 相同，初始有 $f_{1,N,0}=g_{1,N,1}=0$，那么所需时间为 $\min(\lvert S-X_1\rvert+f_{p_1,p_1,0}+(N+1)\lvert X_{p_1}-G\rvert,\lvert S-X_N\rvert+g_{p_2,p_2,0}+(N+1)\lvert X_{p_2}-G\rvert)$。$f,g$ 可以预处理，时间复杂度为  $O(N^2+Q)$（$Q$ 带不带 $\log$ 都行）。

看起来似乎没有优化空间了？

注意到 $T\leq5\times10^5$。若**去重**后不同的球的位置有 $n$ 个，在最理想的情况下，所需的时间也得是 $2+3+4+\cdots+(n+1)$（每捡一个球后走一米）。若理恵能完赛，至少要求 $\frac{(n+2)(n+1)}{2}-1\leq T$，也就是说 $n\geq10^3$ 时答案全是 ``No``。

去重不影响我们的算法正确性，时间复杂度 $O(n^2+Q)$（最后记得加上拿球的总时间 $N$）。

[Code](https://www.luogu.com.cn/paste/lcxa4ndp)，你怎么知道我 $Q$ 带了个 $\log$。

---

## 作者：DaiRuiChen007 (赞：6)

[Problem Link](https://www.luogu.com.cn/problem/P10207)

**题目大意**

> 给定 $n$ 个球，位置为 $a_1\sim a_n$，$q$ 次询问 $x,y,t$，要求从 $x$ 走到 $y$，要走到每个球的位置上并拿起所有球，当你拿着 $k$ 个球时移动速度为 $\dfrac 1{k+1}$，求是否能在 $t$ 时间内到达。
>
> 数据范围：$n,q,a_i,x,y,t\le 5\times 10^5$。

**思路分析**

考虑对 $a_i$ 去重，注意到如果有 $m$ 个本质不同的 $a_i$，那么代价至少为 $\dfrac {m(m+1)}2$，因此 $m$ 只有 $\mathcal O(\sqrt t)$ 级别。

注意到一个球所在位置如果被经过多次，肯定是最后一次经过时拿上最优。

因此每条路径第一次拿起的球一定是 $a_1/a_n$，并且任何时候拿的球都是一段后缀和一段前缀。

考虑区间 dp，设 $f_{l,r,0/1,0/1}$ 表示从 $1/n$ 出发，已经拿走了 $a_{1\sim l-1},a_{r+1\sim n}$ 范围内的球，当前在 $l/r$ 的方案数。

转移是容易的，复杂度 $\mathcal O(m^2)=\mathcal O(t)$。

查询时枚举起点并找到最接近终点的节点判断答案即可。

时间复杂度 $\mathcal O(t+q\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1005,MAXL=5e5+5,inf=1e9;
int n,m,q,cnt[MAXL],a[MAXL];
ll dp[MAXN][MAXN][2][2];
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),++cnt[a[i]];
	scanf("%d",&q);
	for(int i=1;i<=m;++i) cnt[i]+=cnt[i-1];
	sort(a+1,a+n+1),n=unique(a+1,a+n+1)-a-1;
	if(n>=1000) {
		while(q--) puts("No");
		return 0;
	}
	memset(dp,0x3f,sizeof(dp));
	dp[1][n][0][0]=dp[1][n][1][1]=0;
	for(int len=n-1;len;--len) for(int l=1,r=len;r<=n;++l,++r) {
		ll s=cnt[a[l]-1]+cnt[m]-cnt[a[r]]+1;
		for(int x:{0,1}) {
			dp[l][r][x][0]=min(dp[l-1][r][x][0]+s*(a[l]-a[l-1]),dp[l][r+1][x][1]+s*(a[r+1]-a[l]));
			dp[l][r][x][1]=min(dp[l-1][r][x][0]+s*(a[r]-a[l-1]),dp[l][r+1][x][1]+s*(a[r+1]-a[r]));
		}
	}
	for(int s,t,k;q--;) {
		scanf("%d%d%d",&s,&t,&k);
		ll ans=inf;
		if(t<=a[n]) {
			int i=lower_bound(a+1,a+n+1,t)-a;
			ans=min(ans,dp[i][i][0][0]+abs(s-a[1])+1ll*(cnt[m]+1)*abs(a[i]-t));
			ans=min(ans,dp[i][i][1][0]+abs(s-a[n])+1ll*(cnt[m]+1)*abs(a[i]-t));
		}
		if(a[1]<=t) {
			int i=upper_bound(a+1,a+n+1,t)-a-1;
			ans=min(ans,dp[i][i][0][0]+abs(s-a[1])+1ll*(cnt[m]+1)*abs(a[i]-t));
			ans=min(ans,dp[i][i][1][0]+abs(s-a[n])+1ll*(cnt[m]+1)*abs(a[i]-t));
		}
		puts(ans+cnt[m]<=k?"Yes":"No");
	}
	return 0;
}
```

---

## 作者：ln001 (赞：2)

首先我们发现一个~~诈骗~~性质，设给出的球总个数为 $n$，其中位置完全不同的个数为 $cnt$，当所有的球按距离间隔为 $1$ 排列(即全部相邻)，且每一组询问的起点和终点分别位于最左侧和最右侧的球上。容易发现此时所需时间最少，且为 $n+\sum_{i=2}^{cnt}i$。而询问时限 $t$ 又不超过 $2 \times 10^5 $，将求和展开后解二次不等式，能求出 $cnt$ 的有解上界约为 $998.5$。因此读入数据后去重，$cnt$ 高于 $1000$ 直接不可以总司令即可。

现在考虑正解是长什么样子的，因为每一个球拿起后不能放下，经过时可以不拿，最终的答案是自己走的每一段路拿了多少球再 $+1$。所以可以得出我们不能带着很多球走远路。进一步地，我们会优先选择两端的球。

那么做法很简单了，设 $f_{2,i,j,2}$ 表示我在选球的第一步优先选了最左边还是最右边的球，经过若干次操作使得仅有区间 $[l,r]$ 之间的球没有被捡，当前我在区间 $[l,r]$ 的哪一个端点，值就是最短时间。

dp 的初始值、转移、统计答案有点长，放到代码里了。


```cpp
const long long INF = 0x3f3f3f3f3f3f3f3f, N = 5e5 + 10, M = N, _N = 2024;
void to_min(ll &x, ll y)
{
    x = min(x, y);
}

ll n, m, q;
ll a[N];
ll cnt = 0;
ll b[M];

ll qz[M];
ll get_sum(ll l, ll r) //求区间中球的个数
{
    if (l > r)
        swap(l, r);
    if (l == 0)
        return qz[r];
    return qz[r] - qz[l - 1];
}

ll f[2][_N][_N][2]; //从全局的最左侧/最右侧开始走，经过若干次操作使得仅有区间l~r之间的球没有被捡，且当前我站在l/r点
signed main()
{
    // freopen("run.in", "r", stdin);
    // freopen("run.out", "w", stdout);
    csf;

    cin >> n >> m;
    f(i, 1, n)
    {
        cin >> a[i];
        b[a[i]]++;
    }
    f(i, 0, m)
    {
        qz[i] = qz[i - 1] + b[i];
        cnt += (bool)b[i];
    }
    cin >> q;

    if (cnt > 1e3)
    {
        while (q--)
            puts("No"); //去重后，若所有的球按距离间隔为1排列(即全部相邻)，且起点终点位于两端的球上，我们能在最短的时间内捡完所有的球，此时最短用时为 (cnt + (2 + 3 +……+ n)) = cnt + (2 + cnt) * (cnt - 1) / 2，而限时的最大值为5e5，解二次不等式可的cnt上限为998.5，即cnt>998.5时一定无解。
        return 0;
    }

    sort(a + 1, a + n + 1);
    unique(a + 1, a + n + 1);
    memset(f, 0x3f, sizeof f);
    f[0][1][cnt][0] = 0;
    f[1][1][cnt][1] = 0;
    for (ll len = cnt; len; len--)
    {
        f(l, 1, cnt)
        {
            ll r = l + len - 1;
            if (r > cnt)
                break;
            ll summ = n - get_sum(a[l], a[r]) + 1;
            to_min(f[0][l][r][0], f[0][l - 1][r][0] + summ * (a[l] - a[l - 1]));
            to_min(f[0][l][r][0], f[0][l][r + 1][1] + summ * (a[r + 1] - a[l]));
            to_min(f[0][l][r][1], f[0][l - 1][r][0] + summ * (a[r] - a[l - 1]));
            to_min(f[0][l][r][1], f[0][l][r + 1][1] + summ * (a[r + 1] - a[r]));

            to_min(f[1][l][r][0], f[1][l - 1][r][0] + summ * (a[l] - a[l - 1]));
            to_min(f[1][l][r][0], f[1][l][r + 1][1] + summ * (a[r + 1] - a[l]));
            to_min(f[1][l][r][1], f[1][l - 1][r][0] + summ * (a[r] - a[l - 1]));
            to_min(f[1][l][r][1], f[1][l][r + 1][1] + summ * (a[r + 1] - a[r]));
        }
    }
    a[0] = 0;       //如果没有找到终点左侧的球，那么令这个被找到的假球位置在全场的最左侧
    a[cnt + 1] = m; //如果没有找到终点右侧的球，那么令这个被找到的假球位置在全场的最右侧
    while (q--)
    {
        ll u, v, t, ans = INF;
        cin >> u >> v >> t;
        ll x2 = lower_bound(a + 1, a + cnt + 1, v) - a;                              //终点右侧的球
        ll x1 = x2 - 1;                                                              //终点左侧的球
        to_min(ans, n + abs(u - a[1]) + f[0][x1][x1][0] + (n + 1) * abs(v - a[x1])); //捡起所有的球需要耗费n的时间，走到全局最左侧需要耗费abs(u - a[1])的时间，经过若干次操作需要耗费f[0][x1][x1][0]的时间，带着所有的球走到终点需要耗费(n + 1) * abs(v - a[x1])的时间。
        to_min(ans, n + abs(u - a[1]) + f[0][x2][x2][0] + (n + 1) * abs(v - a[x2]));
        to_min(ans, n + abs(u - a[cnt]) + f[1][x1][x1][0] + (n + 1) * abs(v - a[x1]));
        to_min(ans, n + abs(u - a[cnt]) + f[1][x2][x2][0] + (n + 1) * abs(v - a[x2]));
        if (ans <= t)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
```

---

## 作者：123456xwd (赞：1)

首先，我们发现 $T\le 5\times 10^5$，考虑如何利用，若本质不同的有 $n$ 个，则至少要花费 $1+2+3+\cdots +n$ 的时间，也就是说若 $n\ge 1000$ 我们就可以直接无脑输出 ``No`` 了。

考虑一个 $\mathcal{O}(n^2)$ 的算法，发现对于一个点上的球，肯定是在最后一次经过他的时候拿，也就是说，对于在 $G$ 同侧的两个点，肯定是有靠近 $G$ 的后被拿，那么没有被拿的一定是一个区间，考虑区间 dp。

设 $dp_{l,r,0/1}$ 表示只有区间 $[l,r]$ 的球没有拿，当前在 $l/r$ 的时候，最小的花费时间，$\mathcal{O}(1)$ 的从 $dp_{l-1,r,0/1},dp_{l,r+1,0/1}$ 转移。

但是呢，我们发现，随着起点的变化，我们的初始状态也在变化，不妨设两个 dp（$dp1_{l,r,0/1},dp2_{l,r,0/1}$），分别表示从最左边或最右边开始拿球，初始设 $dp1_{1,n,0}=dp2_{1,n,1}=0$，正常跑即可。

对于答案，我们设在 $G$ 左边和右边的点分别为 $p,q$，那么我们枚举一下最后停留在哪一个点以及一开始去往最左边还是最右边即可。

注意一下 $G$ 在最左边或最右边的情况，以及不要忘记拿所有球的时间。

总时间复杂的为 $\mathcal{O}(N^2+Q\log N)$，其中 $N\le 1000$。


```c++
#include<bits/stdc++.h>
#define ull unsigned long long
#define int long long
#define p_b push_back
#define m_p make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
#define gcd __gcd
#define lowbit(x) (x&(-x))
using namespace std;
int rd(){
    int x=0,f=1; char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar())if (ch=='-') f=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
void write(int x){
    if(x>9) write(x/10);
    putchar('0'+x%10);
}
const int N=5e5+5,M=1000+5,INF=0x3f3f3f3f3f3f3f3f;
int n,L,Q;
int a[N],sum[N];
int dp[2][M][M][2];
signed main(){
	n=rd(),L=rd();
	for(int i=1;i<=n;i++) a[i]=rd(),sum[a[i]]++;
	Q=rd();
	sort(a+1,a+n+1);
    n=unique(a+1,a+n+1)-a-1;
	if(n>1000){
		while(Q--) puts("No");
		return 0;
	}
	for(int i=1;i<=L;i++) sum[i]+=sum[i-1];
	memset(dp,0x3f,sizeof(dp));
	dp[0][1][n][0]=dp[1][1][n][1]=0;
	for(int i=0;i<=1;i++){
		for(int len=n-1;len>=1;len--){
			for(int l=1;l+len-1<=n;l++){
				int r=l+len-1,tmp=sum[L]-sum[a[r]]+1;
				if(a[l]) tmp+=sum[a[l]-1];
				dp[i][l][r][0]=min(dp[i][l][r][0],dp[i][l][r+1][1]+tmp*(a[r+1]-a[l]));
				dp[i][l][r][0]=min(dp[i][l][r][0],dp[i][l-1][r][0]+tmp*(a[l]-a[l-1]));
				
				dp[i][l][r][1]=min(dp[i][l][r][1],dp[i][l][r+1][1]+tmp*(a[r+1]-a[r]));
				dp[i][l][r][1]=min(dp[i][l][r][1],dp[i][l-1][r][0]+tmp*(a[r]-a[l-1]));
				//cout<<l<<" "<<r<<":"<<dp[i][l][r][1]<<" "<<dp[i][l][r][0]<<endl;
			}
		}
	}
	while(Q--){
		int S=rd(),G=rd(),T=rd();
		int ans=INF;
		if(G>a[1]){
			int p=lower_bound(a+1,a+1+n,G)-a-1;
			ans=min(ans,dp[0][p][p][0]+abs(a[1]-S)+(sum[L]+1)*abs(a[p]-G));
			ans=min(ans,dp[1][p][p][0]+abs(a[n]-S)+(sum[L]+1)*abs(a[p]-G));
		}
		if(G<=a[n]){
			int p=lower_bound(a+1,a+1+n,G)-a;
			ans=min(ans,dp[0][p][p][0]+abs(a[1]-S)+(sum[L]+1)*abs(a[p]-G));
			ans=min(ans,dp[1][p][p][0]+abs(a[n]-S)+(sum[L]+1)*abs(a[p]-G));
		}
		
		ans+=sum[L];
		if(ans<=T) puts("Yes");
		else puts("No");
	}
    return 0;
}
```

---

## 作者：2huk (赞：1)

MX-C 8.16 模拟赛 T4。

对楼上大佬的题解做的一些详细解释。

## 题意

一条数轴上放了 $n$ 个球，第 $i$ 个球放在了位置 $x_i$，一个位置可能有多个球。

你需要从起点 $s$ 出发，捡起所有 $n$ 个球（一个球捡起了就不能放下了），回到终点 $t$。如果你能在规定时间 $T$ 内完成，则算你成功。

已知：拿起 $1$ 个球需要 $1$ 单位时间；带着 $x$ 个球移动 $1$ 个单位距离需要 $x + 1$ 单位时间。

给定 $n,l,x_i$，你需要回答 $q$ 个询问，每个询问给定 $s,t,T$，你需要回答能不能成功。

所有数都 $\le 5 \times 10^5$。

## 做法

显然第一步是将球按照坐标排序。

我们考虑如果在 $t$ 的某侧有两个球，那么最优策略一定是选捡那个远的再捡近的。这是因为如果先捡近的你会抱着这个球跑一个来回。

所以对于 $t$ 的某侧（左侧或右侧）而言，一定是先捡最远的，再捡第二远的，以此类推。所以我们捡的第一个球一定是第一个或第 $n$ 个，这是因为我们将球按坐标排序了。

考虑最朴素的区间 DP。设 $f(l, r, 0/1)$ 表示我们已经捡了 $[1, l-1]$ 和 $[r+1, n]$ 这些球，且现在我们正位于第 $l/r$ 个球的位置，所需要的最小时间。这样设状态的问题是没法设置边界，因此我们再引入一个与 $f$ 意义相同的 $g$，其中 $f$ 表示起点是第一个球，$g$ 表示起点是第 $n$ 个球。

显然边界 $f(1,n,0) = 0,g(1,n,1)=0$。转移枚举一下最后一个捡的球是 $l - 1$ 还是 $r + 1$：

$$
f(l,r,0) = \min \{f(l-1,r,0) + (cnt+1)\times (x_l - x_{l - 1}), f(l, r+1, 1) + (cnt+1)\times (x_{r+1}-x_l)\} \\
f(l,r,1) = \min \{f(l-1,r,0)+(cnt+1)\times(x_r - x_{l-1}), f(l,r+1,1)+(cnt+1)\times(x_{r+1}-x_r)\}
$$

$g$ 的转移**一模一样**。

其中 $cnt = (l-1) + (n-r)$，表示 $[1,l-1] \cup [r+1,n]$ 的大小，即当前在手上的球的数量。

考虑计算答案。对于 $t$ 的一侧而言，因为我们按照球到 $t$ 的距离从大到小取球，所以最后一个球一定距离 $t$ 最近。分别求出这两侧的这两个最近的球 $p_1,p_2$。那么我们可以枚举第一个取的球（第 $1$ 个或第 $n$ 个），以及最后一个取的球（第 $p_1$ 个或第 $p_2$ 个），即：

$$
\min \{|s-x_1| + f(p,p,0) + (n + 1) \times |x_p-t|, |s-x_n| + f(p,p,0) + (n+1) \times |x_p - t|\}
$$

其中 $p \in \{p_1,p_2\}$，我们可以枚举。

复杂度？$n^2$ 过五十万你搞笑呢？

令 $S$ 表示将球的坐标去重后的数量。**注意到**在最坏情况下，如果我们在第一米捡第一个球，第二米捡第二个球，以此类推，那么总答案为 $2+3+\dots+(S+1) = \mathcal O(S^2)$。而 $t \le 5 \times 10^5$ 远小于这个数，所以当 $S$ 大于某个阈值后全输出 $\texttt{No}$ 即可。这个阈值是 $10^3$。

那么区间 DP 的状态数优化到了 $10^3 \times 10^3 \times 2$。这是被允许的。

去重后实现较为复杂。一个记忆化搜索的实现如下：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1e6 + 10, INF = 1e9;

int n, L, x[N];
int s[N];
int f[1010][1010][2];
int g[1010][1010][2];

int dp0(int l, int r, bool flg) {
	if (l == 1 && r == n) return flg ? INF : 0;
	if (~f[l][r][flg]) return f[l][r][flg];
	int res = 1e9;
	
	int sum = 1 + (x[l] ? s[x[l] - 1] : 0) + s[L] - s[x[r]];
	
	if (!flg) {
		if (l > 1) res = min(res, dp0(l - 1, r, 0) + sum * (x[l] - x[l - 1]));
		if (r < n) res = min(res, dp0(l, r + 1, 1) + sum * (x[r + 1] - x[l]));
	}
	else {
		if (l > 1) res = min(res, dp0(l - 1, r, 0) + sum * (x[r] - x[l - 1]));
		if (r < n) res = min(res, dp0(l, r + 1, 1) + sum * (x[r + 1] - x[r]));
	}
	
	return f[l][r][flg] = res;
}

int dp1(int l, int r, bool flg) {
	if (l == 1 && r == n) return !flg ? INF : 0;
	if (~g[l][r][flg]) return g[l][r][flg];
	int res = 1e9;
	
	int sum = 1 + (x[l] ? s[x[l] - 1] : 0) + s[L] - s[x[r]];
	
	if (!flg) {
		if (l > 1) res = min(res, dp1(l - 1, r, 0) + sum * (x[l] - x[l - 1]));
		if (r < n) res = min(res, dp1(l, r + 1, 1) + sum * (x[r + 1] - x[l]));
	}
	else {
		if (l > 1) res = min(res, dp1(l - 1, r, 0) + sum * (x[r] - x[l - 1]));
		if (r < n) res = min(res, dp1(l, r + 1, 1) + sum * (x[r + 1] - x[r]));
	}
	
	return g[l][r][flg] = res;
}

signed main() {
	cin >> n >> L;
	
	int backup = n;
	
	for (int i = 1; i <= n; ++ i ) {
		cin >> x[i];
		s[x[i]] ++ ;
	}
	
	for (int i = 1; i <= L; ++ i ) {
		s[i] += s[i - 1];
	}
	
	sort(x + 1, x + n + 1);
	n = unique(x + 1, x + n + 1) - x - 1;
	
	memset(f, -1, sizeof f);
	memset(g, -1, sizeof g);
	
	int q;
	cin >> q;
	
	while (q -- ) {
		if (n > 1e3) {
			puts("No");
			continue;
		}
		
		int s, t, jp;
		cin >> s >> t >> jp;
		
		int res = 1e9;
		
		if (x[n] >= t) {
			int p = lower_bound(x + 1, x + n + 1, t) - x;
			res = min(res, abs(s - x[1]) + dp0(p, p, 0) + (backup + 1) * abs(x[p] - t));
			res = min(res, abs(s - x[n]) + dp1(p, p, 0) + (backup + 1) * abs(x[p] - t));
		}
		
		if (x[1] < t) {
			int p = lower_bound(x + 1, x + n + 1, t) - x - 1;
			res = min(res, abs(s - x[1]) + dp0(p, p, 0) + (backup + 1) * abs(x[p] - t));
			res = min(res, abs(s - x[n]) + dp1(p, p, 0) + (backup + 1) * abs(x[p] - t));
		}
		
		res += backup;
		
		puts(res <= jp ? "Yes" : "No");
	}
	
	return 0;
}
```

---

