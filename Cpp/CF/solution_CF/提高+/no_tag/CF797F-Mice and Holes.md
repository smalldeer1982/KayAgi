# Mice and Holes

## 题目描述

One day Masha came home and noticed $ n $ mice in the corridor of her flat. Of course, she shouted loudly, so scared mice started to run to the holes in the corridor.

The corridor can be represeted as a numeric axis with $ n $ mice and $ m $ holes on it. $ i $ th mouse is at the coordinate $ x_{i} $ , and $ j $ th hole — at coordinate $ p_{j} $ . $ j $ th hole has enough room for $ c_{j} $ mice, so not more than $ c_{j} $ mice can enter this hole.

What is the minimum sum of distances that mice have to go through so that they all can hide in the holes? If $ i $ th mouse goes to the hole $ j $ , then its distance is $ |x_{i}-p_{j}| $ .

Print the minimum sum of distances.

## 样例 #1

### 输入

```
4 5
6 2 8 9
3 6
2 1
3 6
4 7
4 7
```

### 输出

```
11
```

## 样例 #2

### 输入

```
7 2
10 20 30 40 50 45 35
-1000000000 10
1000000000 1
```

### 输出

```
7000000130
```

# 题解

## 作者：泠小毒 (赞：16)

# Mice and Holes
n个老鼠，m个洞，告诉你他们的一维坐标和m个洞的容量限制，问最小总距离。
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190509/)
## 解法
明显是dp，dp[i][j]表示前j只老鼠进了前i个洞的最小距离

无解很好判断，只要老鼠数量大于洞的总容量就无解

转移方程呢，dp[i][j]=min(dp[i-1][k]+sum[i][j]-sum[i][k])

sum[i][j]表示前j只老鼠都到i号洞的距离

发现这样做是n^3，接受不了，需要优化

因为sum[i][j]是定值，将dp[i-1][k]-sum[i][k]维护成一个单调队列，就可以n方做了
## ac代码
```cpp
#include<bits/stdc++.h>
#define inf 2333333333333333
#define ll long long
using namespace std;
struct node{ll x,s;}b[5010];
ll n,m,l,r,a[5010],s[5010],sum[5010],dp[5010][5010],q[5010];
ll cmp(node x,node y){return x.x<y.x;}
int main()
{
    scanf("%lld%lld",&n,&m),memset(dp,inf,sizeof(dp)),dp[0][0]=0;
    for(ll i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(ll i=1;i<=m;i++)scanf("%lld%lld",&b[i].x,&b[i].s);
    sort(a+1,a+1+n),sort(b+1,b+1+m,cmp);
    for(ll i=1;i<=m;i++)s[i]=s[i-1]+b[i].s;
    if(s[m]<n){puts("-1");return 0;}
    for(ll i=1;i<=m;i++)
    {
        dp[i][0]=l=r=0,q[++r]=0;
        for(ll j=1;j<=s[i]&&j<=n;j++)
        {
            dp[i][j]=dp[i-1][j],sum[j]=sum[j-1]+abs(a[j]-b[i].x);
            while((j-q[l]>b[i].s)||l<=r&&dp[i-1][q[l]]-sum[q[l]]>dp[i-1][j]-sum[j])l++;
            q[++r]=j,dp[i][j]=min(dp[i][j],sum[j]+dp[i-1][q[l]]-sum[q[l]]);
        }
    }
    printf("%lld\n",dp[m][n]);
    return 0;
}
```

---

## 作者：王奕清 (赞：13)

一道还算好想的单调队列优化 $dp$

首先是$dp$数组的定义：$dp[i][j]$ 表示前$i$个洞中藏了前$j$只老鼠
（洞和老鼠都已按照坐标排序）

然后可以得出一个$n^3$的$dp$,

$dp[i][j]$ = max{ $dp[i-1][k]+sum[i][j]-sum[i][k]$ }（$j>=k>=j-c[i]$）

// $sum[i][j]$ 表示前 $j$ 只老鼠到第 $i$ 个洞的距离前缀和。

这个转移方程就是表示 $k+1$ 到 $j$ 只老鼠进了 $i$ 这个洞


然后一看到这个方程只含有加减，就考虑单调队列优化，发现 $dp[i-1][k]$ 与 $-sum[i][k]$ 都与 $j$ 无关就用单调对列维护这两个值，然后就可以 $O(n^2)$ $dp$ 了。

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[5005],dp[5005][5005],nx;
pair<int,int>c[5005]; 
signed main()
{
	cin>>n>>m;
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;i++)cin>>a[i];sort(a+1,a+n+1);
	for(int i=1;i<=m;i++)cin>>c[i].first>>c[i].second,nx+=c[i].second;
	if(nx<n)puts("-1"),exit(0);sort(c+1,c+m+1);
	for(int i=1;i<=m;i++)
	{
    		deque<pair<int,int> >q;
		int sum=0;q.push_back(make_pair(dp[i][0]=0,0));
		for(int j=1;j<=n;j++)
		{
			while(!q.empty()&&j-q.front().second>c[i].second)q.pop_front();
			sum+=abs(a[j]-c[i].first);//sum可以边做边求，不需要开数组了
			dp[i][j]=min(dp[i-1][j],sum+q.front().first);
			while(!q.empty()&&q.back().first>dp[i-1][j]-sum)q.pop_back();
            //维护一个递增的队列
			q.push_back(make_pair(dp[i-1][j]-sum,j));
		}
	}
	printf("%lld",dp[m][n]);
}
```

---

## 作者：wwlw (赞：7)

[Link](https://www.luogu.com.cn/problem/CF797F)
-----------

### Solution

有一个非常显然的性质，一个洞最终容纳的一定是一段横坐标连续的老鼠。就是说不可能出现交叉的请况。数学证明也是非常的容易，懒得写了。

那么就预先将老鼠和洞分别按横坐标排序。这样之后，容易想到 dp 状态 $dp[i][j]$ 表示用前 $i$ 个洞容纳前 $j$ 个老鼠的最小花费。方程也非常好想
$$dp_{i,j}=\min\limits_{j-c_i\leq k \leq j}\{dp_{i-1,k}+\sum_{k<r\leq j} {|P_i-p_r|}\}$$
其中 $P$ 是洞的坐标，$p$ 是老鼠的坐标，$c$ 是洞的容量。特别注意，当前 $i$ 个洞填满都不够 $j$ 只老鼠时，就不存在方案，$dp_{i,j}=\infty$ 

当 $i$ 确定时，后面的那个和式可以直接用前缀和优化掉，记为 $S_{i,j}$。之后发现 $S_{i,j}$ 是与 $k$ 无关的变量，所以直接从 $\min$ 里面提出来。
$$dp_{i,j}=S_{i,j}+\min\limits_{j-c_i\leq k \leq j}\{dp_{i-1,k}-S_{i,k}\}$$
枚举一个 $i$ 和 $j$ 后，后面的 $\min$ 就只与 $k$ 有关了，发现决策集合是连续的若干个区间，所以直接用单调队列优化掉就可以了。

```cpp
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define N 5007
#define ll long long

inline int read(){
    int x=0,flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') flag=0;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}

struct Hole{
    int p,c;
    bool operator <(const Hole X) const{return p<X.p;}
}t[N];

ll S[N],dp[N][N],V[N];
int n,m,Q[N],hd=1,tl=0,ret,a[N];
int main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    sort(a+1,a+1+n);
    for(int i=1;i<=m;i++)
        t[i].p=read(),t[i].c=read();
    sort(t+1,t+1+m);
    for(int j=1;j<=n;j++) dp[0][j]=(1LL<<60);
    for(int i=1;i<=m;i++){
        ret+=t[i].c;
        for(int j=1;j<=n;j++)
            S[j]=abs(t[i].p-a[j])+S[j-1];
        hd=1,tl=0;
        for(int j=0;j<=n;j++){
            while(hd<=tl&&Q[hd]<j-t[i].c) hd++;
            while(hd<=tl&&dp[i-1][j]-S[j]<=V[tl]) tl--;
            Q[++tl]=j,V[tl]=dp[i-1][j]-S[j];
            if(ret>=j) dp[i][j]=S[j]+V[hd];
            else dp[i][j]=(1LL<<60);
        }
    }
    printf("%lld",(dp[m][n]!=(1LL<<60))? dp[m][n]:-1);
}
```

---

## 作者：无心揽青丝 (赞：7)

搬运博客园“谁知道你啊啊啊”大佬

## Mentality
```cpp
根据贪心策略，每只老鼠有两个选择，左边最近的有容量的洞，右边最近的有容量的洞。
优先队列Q1存老鼠，Q2存洞，按坐标大小出队。存的值为-k-x，x为该点坐标，Q1为老鼠坐标，Q2为洞的坐标，k为偏差值。
洞：左边的老鼠进，贡献为x，右边的老鼠进，贡献为-x
老鼠：进左边的洞，贡献为x，进右边的洞，贡献为-x
将代码取消注释，输入最下方的洞-鼠-洞-鼠-洞样例，仔细观察。当鼠2进洞2时，鼠1的位置被挤掉，那么鼠1就会回到上一个状态，k值算的就是所有现状态回到上一个状态时的偏差值的累加，即ans += k，就能让ans回到上一个状态。具体观察洞2出现时的ans，和鼠2出现时的ans思考。
```
## Code
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long LL;
const int N=2e6+100;
int gi() {
	int w=0;bool q=1;char c=getchar();
	while ((c<'0'||c>'9') && c!='-') c=getchar();
	if (c=='-') q=0,c=getchar();
	while (c>='0'&&c <= '9') w=w*10+c-'0',c=getchar();
	return q? w:-w;
}
pair<int,int>p[N];
struct Q{ LL w; int id; inline bool operator < (const Q &b) const { return w>b.w; } };
int main()
{
#ifndef ONLINE_JUDGE
	freopen("mice.in","r",stdin);
	freopen("mice.out","w",stdout);
#endif
	int n=gi(),m=gi(),i,k,s=-n;LL ans=0,w;
	const LL inf=1e15;
	for (i=1;i<=n;i++) p[i]=make_pair(gi(),-1);
	while (m--) p[++n].x=gi(),s+=p[n].y=gi();
	if (s<0) return puts("-1"),0;
	sort(p+1,p+1+n);
	priority_queue< LL , vector<LL> , greater<LL> >q0;
	priority_queue<Q>q1;
	for (i=1;i<=n;i++)
		if (p[i].y==-1) {
			w=inf;
			if (!q1.empty()) {
				k=q1.top().id;w=p[i].x+q1.top().w;q1.pop();
				if (p[k].y) p[k].y--,q1.push((Q){-p[k].x,k});
			}
			ans+=w;
			q0.push(-p[i].x-w);
		} else {
			while (p[i].y&&!q0.empty()&&p[i].x+q0.top()<0) {
				p[i].y--;
				w=p[i].x+q0.top();q0.pop();
				ans+=w;q1.push((Q){-p[i].x-w,0});
			}
			if (p[i].y) q1.push((Q){-p[i].x,i}),p[i].y--;
		}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：lskksl (赞：3)

这道题分 $2$ 个部分去做：
## 贪心部分
显然我们可以知道，每只老鼠只会前往自己左边或右边最近的一个洞。

如果不是这样，那么可能出现两只老鼠的路线出现交叉的情况。

显然这是不好的。所以我们知道，我们的贪心是不劣的。

这样可以预处理了。
## $dp$ 部分
### $O(n^3)$ 做法
设 $dp_{i,j}$ 表示前 $i$ 个洞容纳前 $j$ 个老鼠。

由于洞有容量限制，转移的时候每次枚举一个洞放多少老鼠。

转移：
$$dp_{i,j}=\min_{j-c_{i} \leqslant k \leqslant j}(dp_{i-1,k}+sum_{i,j}-sum_{i,k})$$

显然这不足够。

### $O(n^2)$ 做法
设 $S_{a,b}$ 表示前 $a$ 只老鼠都到第 $b$ 个洞的代价，这样枚举让若干只老鼠进入某个洞的时候，就变成了两个差值相减。

转移：
$$dp_{i,j}=\min_{j-c_{i} \leqslant k \leqslant j}(dp_{i-1,k}+S_{j,i}-S_{k,i})$$

移项，得：
$$dp_{i,j}=S_{j,i}+\min_{j-c_{i} \leqslant k \leqslant j}(dp_{i-1,k}-S_{k,i})$$

然后发现后面的东西跟前面的j没有任何关系了。

枚举 $j$ 之前先预处理好 $\min$ 值再枚举 $j$ 更新 $dp$ 值即可，并且可以使用单调队列进行优化。

---

## 作者：Zhddd_ (赞：2)

### 分析

首先，先对所有洞和老鼠按照横坐标从小到大排序。

其次，我们可发现：一个洞所容纳的必定是一段连续区间的老鼠。

![](https://cdn.luogu.com.cn/upload/image_hosting/9w7ku5rg.png)

如图所示，上方的 $1\sim 2$ 是洞，下方的 $1\sim 7$ 是老鼠。

如果出现了类似老鼠 $3$ 进入洞 $2$，但老鼠 $4$ 进入洞 $1$ 的情况，它们两个可以互换所进入的洞，这样一定更优。

据此，可以设计状态：令 $dp_{i,j}$ 表示前 $j$ 只老鼠进入前 $i$ 的洞的最小距离之和，那么状态转移如下：

$$f_{i,j}\gets\underset{k=0}{\overset{j-1}{\min}}(f_{i-1,k}+{\sum^{j}_{p=k+1}}{dis_{i,p}})$$

含义为前 $k$ 只老鼠进入前 $i-1$ 个洞，而第 $k\sim j$ 只老鼠进入第 $i$ 个洞的最小距离之和（前面已经证明过一个洞容纳的必定是一段连续区间的老鼠）。

对于 ${\sum^{j}_{p=k+1}}dis_{p,i}$，可以用前缀和来优化：用 $sum_{i,j}$ 表示前 $j$ 只老鼠都进入第 $i$ 个洞的距离，那么状态转移可以变成：

$$f_{i,j}\gets\underset{k=0}{\overset{j-1}{\min}}(f_{i-1,k}-sum_{i,k})+sum_{i,j}$$

$sum_{i,j}$ 是一个定值，所以我们重点关注 $f_{i-1,k}-sum_{i,k}$。每个 $f_{i,j}$ 肯定是会通过一个最优的 $f_{i-1,k}-sum_{i,k}$ 转移过来的，用单调队列可以优化到 $\mathcal{O}(1)$。

时间复杂度：$\mathcal{O}(n^2)$。

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;
const int N = 5e3 + 10;
const LL INF = 0x3f3f3f3f3f3f3f3f;
struct Hole {
    int p, c;
    bool operator<(const Hole o) const
    {
        return p < o.p;
    }
} hole[N];
int n, m, mice[N];
LL dis[N], dp[2][N], q[N], v[N], cnt;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &mice[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &hole[i].p, &hole[i].c);
    sort(mice + 1, mice + n + 1);
    sort(hole + 1, hole + m + 1);
    for (int i = 1; i <= n; i++)
        dp[0][i] = INF;
    for (int i = 1; i <= m; i++) {
        cnt += hole[i].c;
        for (int j = 1; j <= n; j++)
            dis[j] = dis[j - 1] + abs(mice[j] - hole[i].p);
        int hh = 1, tt = 0;
        for (int j = 0; j <= n; j++) {
            while (hh <= tt && q[hh] < j - hole[i].c)
                hh++;
            while (hh <= tt && dp[!(i & 1)][j] - dis[j] <= v[tt])
                tt--;
            q[++tt] = j;
            v[tt] = dp[!(i & 1)][j] - dis[j];
            if (cnt >= j)
                dp[i & 1][j] = dis[j] + v[hh];
            else
                dp[i & 1][j] = INF;
        }
    }
    printf("%lld", (dp[m & 1][n] == INF) ? -1 : dp[m & 1][n]);
    return 0;
}
```

---

## 作者：2huk (赞：1)

> - $n$ 个老鼠，$m$ 个洞，告诉你他们的一维坐标和 $m$ 个洞的容量限制，问最小总距离。
> - $n, m \le 5 \times 10^3$，坐标在 $\pm 10^9$ 内。

不难发现每个洞内的老鼠在坐标上是连续的。因此我们将老鼠和洞按坐标排序，并将老鼠分成 $m$ 段，每段老鼠对应一个洞。

设计 DP。令 $g(l,r , x)$ 表示 $[l, r]$ 老鼠到第 $x$ 个洞的距离和。显然 $g(l,r , x) = g(1, r, x) - g(1, l -1, x)$。令 $f(i, j)$ 表示前 $i$ 个洞，前 $j$ 个老鼠的答案。那么转移枚举这个洞的老鼠数量：
$$
\begin{aligned}
f(i, j) &= \min_{k=0}^{c_i} \{f(i - 1, j - k) + g(j - k + 1, j, i) \}
\\&= \min_{k=\max(0,j-c_i)}^{j} \{f(i - 1, k) + g(k+1, j, i)\}
\\&= \min_{k=\max(0,j-c_i)}^{j} \{f(i - 1, k) + g(1, j, i) - g(1, k, i)\}
\\&= g(1, j, i) + \min_{k=\max(0,j-c_i)}^{j} \{f(i - 1, k) - g(1, k, i)\}
\end{aligned}
$$
单调队列维护即可。

```cpp
#include <bits/stdc++.h>

typedef long long ll;

constexpr int N = 5010;

int n, m;
int x[N];

struct Mice {
	int p, c;
	bool operator <(const Mice& h) const {
		return p < h.p;
	}
}y[N];

ll sum[N];
ll f[2][N];		// 前 i 个洞，前 j 只老鼠，最小距离和
ll g[N];	// 前 i 只老鼠，到第 j 个洞的距离和

int q[N], hh, tt = -1;

signed main() {
	std::cin >> n >> m;
	
	for (int i = 1; i <= n; ++ i ) std::cin >> x[i];
	for (int i = 1; i <= m; ++ i ) std::cin >> y[i].p >> y[i].c;
	
	std::sort(x + 1, x + n + 1);
	std::sort(y + 1, y + m + 1);
	
	for (int i = 1; i <= m; ++ i ) sum[i] = sum[i - 1] + y[i].c;
	
	memset(f, 0x3f, sizeof f);
	for (int i = 0; i <= m; ++ i ) f[i & 1][0] = 0;
	
	auto calc = [&](int i, int j) -> ll {
		return f[i - 1 & 1][j] - g[j];
	};
	
	for (int i = 1; i <= m; hh = 0, tt = -1, ++ i ) {
		for (int j = 1; j <= n; ++ j ) {
			g[j] = g[j - 1] + abs(x[j] - y[i].p);
		}
		
		for (int j = 0; j <= n; ++ j ) {
			if (hh <= tt && j - y[i].c > q[hh]) ++ hh;
			while (hh <= tt && calc(i, q[tt]) >= calc(i, j)) -- tt;
			q[ ++ tt] = j;
			
			if (j <= sum[i]) {
				f[i & 1][j] = f[i - 1 & 1][j];
				f[i & 1][j] = std::min(f[i - 1 & 1][j], g[j] + calc(i, q[hh]));
			}
		}
	}
	
	if (f[m & 1][n] > 1e12) f[m & 1][n] = -1;
	std::cout << f[m & 1][n] << '\n';
	
	return 0;
}
```

---

## 作者：Rushroom (赞：1)

DP 之神 @GreenSnake 一秒口胡出斜率优化做法！@GreenSnake，卡密！

显然，先把老鼠和洞按照坐标从小到大排序。

$f_{i,j}$ 表示考虑完前 $i$ 个洞，装了前 $j$ 个老鼠，最少的总距离是多少（注意和正常的状态 $i$ 和 $j$ 是反过来的，因为限制在于洞的容量，老鼠没有限制）。

转移时枚举到第 $i-1$ 个洞为止，一共装了 $k$ 个老鼠，$f_{i,j}\leftarrow f_{i,k}+cost(k+1,j,i)$，其中 $cost(l,r,i)$ 表示 $[l,r]$ 的老鼠到第 $i$ 个洞的总距离，可以预处理前缀和优化（注意要在枚举 $i$ 的循环里处理前缀和，否则再开一个二维数组为 $\mathtt{MLE}$）。

另外，需要满足 $j-k\le c_i$ 才能转移（不然装不下那么多老鼠）。

这样做是 $O(n^3)$ 的，注意到能转移的 $k$ 一定是连续的一段，所以可以用单调队列优化到 $O(n^2)$。

单调队列初始时是只有一个元素 $(0,0)$，代表 $f_{i,0}=0$。

[**Code**](https://www.luogu.com.cn/paste/1rwpylj3)

---

## 作者：1234567890sjx (赞：0)

考虑 dp。设 $f_{i,j}$ 表示当前前 $i$ 个老鼠进入了前 $j$ 个洞穴，最小总距离是多少。因此显然有初始状态 $f_{0,0}=0$，$f_{i,j}$ 则可以枚举第 $k$ 只老鼠进入了上一个洞，则有转移：

$$
f_{i,j}=\min\limits_{k<i} f_{k,j-1}+\text{S}(b_k+1,b_i,j)
$$

其中 $b_i$ 表示第 $i$ 个老鼠的位置，$a_i$ 表示第 $i$ 个洞的位置，$\text{S}(i,j,k)$ 表示 $i$ 和 $j$ 之间所有的老鼠都移动到 $k$ 洞，所需要的最小距离。

直接转移是 $$O(n^3)$$ 的，过不去令人愤怒，因此考虑对 dp 优化。将 $\text{S}$ 函数拆开，令 $s_{i,j}$ 表示前缀 $1\sim i$ 中老鼠都移动到 $j$ 洞穴的最小距离，则

$$
f_{i,j}=\min\limits_{k<i} f_{k,j-1}+s_{b_i,j}-s_{b_k,j}
$$

在已枚举 $i,j$ 的情况下，式子等号右侧部分 $s_{b_i,j}$ 的值固定，而 $f_{k,j-1}-s_{b_k,j}$ 的值变化，取其最小值。

即

$$
f_{i,j}=s_{b_i,j}+\min\limits_{k<i} (f_{k,j-1}-s_{b_k,j})
$$

考虑对 $f_{k,j-1}-s_{b_k,j}$ 维护单调队列，枚举 $i$ 和 $j$，则上述表达式的最小值可以直接用单调队列计算，因此总时间复杂度为 $O(n^2)$，十分可过。

---

## 作者：Lu_xZ (赞：0)

给出 $O(n\log n)$ 的做法，可以通过牛客的这道[加强版](https://ac.nowcoder.com/acm/problem/14847)。

****

先讲一下 $n, m \le 5000$ 的做法。

结论：对于任意 $x_i \le x_j$，其匹配位置 $y _i \le y_j$（匹配定义为球走到哪个洞）。

如果结论成立，那么每个洞一定分配一段连续区间（如下图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/9vpxa1wr.png)

我们使 $(x_i, y_j)$ 和 $(x_j, y_i)$ 两两匹配。

显然 $y_i$ 和 $y_j$ 处的容量都不受影响，只需考虑答案的改变量是否可能小于 $0$。
$$
\Delta

= \big(\vert y_i - x_i \vert - \vert y_i - x_j \vert\big) + \big(\vert y_j - x_j \vert - \vert y_j - x_i\vert\big)
$$
分类讨论一下，$\Delta$ 始终非负，也就是交换任意 $(i, j)$ 答案都不会变小。

将球和洞分别排序。

定义 $f(i, j)$ 表示前 $i$ 个洞容纳前 $j$ 个球的最小代价，洞 $i$ 一定分管 $[1, j]$ 的一个后缀。
$$
f(i, j) = f(i - 1, k) + \sum_{u = k + 1}^j \vert x_u - p_i \vert
$$
我们可以花 $O(n^2)$ 预处理到 $sum(i, j) = \sum_{k = 1}^j\vert x_k - p_i \vert$。

那么转移式可以写成
$$
f(i, j) = f(i - 1, k) + sum(i, j) - sum(i, k) \quad \big(j - k \in [0, c_i]\big)
$$
暴力转移是 $O(n^3)$ 的，把式子写漂亮点：
$$
f(i, j) = sum(i, j)  + \bigg(f(i - 1, k) - sum(i, k)\bigg) \quad \big(k \in [j - c_i, j]\big)
$$
只有后面一部分与 $k$ 有关，

由于 $sum(i, k)$ 和 $f(i - 1, k)$ 在递推 $f(i, j)$ 之前都已经已知，显然可以用数据结构维护。

我们实际是要求 $\min_{k = j - c_i}^{j} \bigg(f(i - 1, k) - sum(i, k)\bigg)$，左右端点都是单调递增的，单调队列维护区间最值。

状态数 $O(n^2)$，转移均摊 $O(1)$，时间复杂度 $O(n^2)$。数组开二维会爆，可以滚动掉一维。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int N = 5005;

struct Hole {
	int p, c;
	bool operator < (const Hole &o) const {
		return p < o.p;
	}
} b[N];

int n, m, a[N], q[N], hh, tt; ll f[2][N], sum[N];

void check() {
	ll tmp = 0;
	for(int i = 1; i <= m; ++ i) tmp += b[i].c;
	if(tmp < n) {
		cout << -1;
		exit(0);
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	for(int i = 1; i <= n; ++ i) cin >> a[i];
	for(int i = 1; i <= m; ++ i) cin >> b[i].p >> b[i].c;
	check();
	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);
	memset(f, 0x3f, sizeof f), f[0][0] = f[1][0] = 0;
	
	for(int i = 1; i <= m; ++ i) {
		for(int j = 1; j <= n; ++ j) {
			sum[j] = sum[j - 1] + abs(b[i].p - a[j]);
		}
		auto calc = [&](int j) {
			return f[i - 1 & 1][j] - sum[j];
		};
		q[hh = tt = 0] = 0;
		for(int j = 1; j <= n; ++ j) {
			while(hh <= tt && q[hh] < j - b[i].c) ++ hh;
			while(hh <= tt && calc(j) <= calc(q[tt])) -- tt;
			q[++ tt] = j;
			f[i & 1][j] = sum[j] + calc(q[hh]); 
		}
	}
	cout << f[m & 1][n];
	return 0;
}
```

****

$n, m \le 10^6$。

将球与洞放在一起排序，从小到大扫描。

+ 如果加入一个球，坐标为 $x$。

  只考虑球走到左侧的洞里，走到右侧的情况可以后续反悔得到。

  从堆 $q_1$ 里找到**代价**最小的一个洞 $(y, v)$，给答案加上 $x + v$ 的贡献（洞的反悔代价的具体表达在后续给出）。

  考虑洞的反悔：

  $x$ 有可能与 $y$ 匹配不是最优的，如果存在 $x$ 右侧的洞 $y'$ 与 $x$ 匹配使总答案变小，我们就要反悔与 $y$ 的匹配。

  **球的反悔代价** 可以分成**撤销原贡献**（$-(x + v)$）和**添加新贡献**（$y' - x$）两部分。

  因此当扫描到洞 $y'$ 时，找到所有 $-v - 2x$ 中最小值 $v'$，如果 $y'+ v' < 0$ 说明反悔这一步会使答案变小，否则没必要反悔。

  找最小值显然可以把 $-v - 2x$ 放到堆 $q_0$ 里维护。
  
+ 如果加入一个洞，坐标为 $y$。

  第一种操作就是不断找 $q_0$ 的 $y + v < 0$ 进行反悔，如果 $y + v \ge 0$ 或容量为 $0$ 则停止。

  假设匹配到了球 $x$，$x$ 有可能与比 $y$ 更后面的洞匹配，因此仍然要把 $x$ 的反悔代价 $-(y + v) + v$ 丢进 $q_0$。

  第二种操作是可能 $y$ 与在他后面的球 $x'$ 匹配。

  类似的，**洞的反悔代价**表达式为 $-(y + v)-y$，把 $-2y-v$ 丢进堆 $q_1$。

  如果一操作终止后洞还有容量剩余，那么 $q_1$ 里直接加入 $-y$，并实时维护 $y$ 的容量。

```cpp
#include<bits/stdc++.h>
#define eb emplace_back
#define ep emplace
using namespace std;

using ll = long long;
constexpr int N = 2e6 + 5;
constexpr ll inf = 1e16;

int n, m; ll ans;

struct Hole {
	int p, c;
	bool operator < (const Hole &o) const {
		return p < o.p;
	}
} a[N];
struct Node {
	ll v; int cnt;
	Node(ll x = 0, int y = 1)
	: v(x), cnt(y) {}
	bool operator < (const Node &o) const {
		return v > o.v;
	}
};
priority_queue<Node> q0, q1;

void check() {
	ll tmp = 0;
	for(int i = 1; i <= m; ++ i) tmp += a[i].c;
	if(tmp < n) {
		cout << -1;
		exit(0);
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	for(int i = 1; i <= n; ++ i) cin >> a[i + m].p;
	for(int i = 1; i <= m; ++ i) cin >> a[i].p >> a[i].c;
	check();
	n += m;
	sort(a + 1, a + n + 1);
	q1.ep(inf, n);
	for(int i = 1; i <= n; ++ i) {
		if(!a[i].c) {
			int x = a[i].p;
			if(!q1.empty()) {
				auto [v, cnt] = q1.top();
				q1.pop();
				if(-- cnt) q1.ep(v, cnt);
				ans += x + v;
				q0.ep(-v - 2 * x);
			}
		}
		else {
			int y = a[i].p;
			while(!q0.empty() && y < -q0.top().v && a[i].c) {
				ll v = q0.top().v;
				q0.pop();
				q1.ep(-2 * y - v);		// 当前的一份容量匹配后面的球
				ans += y + v;
				q0.ep(-y), -- a[i].c;				// 当前一份容量匹配的球去匹配后面的洞。
			}
			if(a[i].c) q1.ep(-y, a[i].c);
		}
	}
	cout << ans;
	return 0;
}
```
时间复杂度可以通过代码中 $q_0$ 的进出队情况看出是 $O(n\log n)$ 的。

[《浅谈反悔贪心》](https://www.luogu.com/article/a23p3j83)

[《老鼠进洞模型》](https://www.cnblogs.com/zychh/p/16907855.html)

---

## 作者：__yun__ (赞：0)

### 题目大意
一条直线上共有 $n$ 只鼠鼠和 $m$ 个鼠洞，分别给出 $n$ 只鼠鼠和 $m$ 个鼠洞在直线上的位置以及每个鼠洞的容量，求当每只鼠鼠均能到鼠洞中的所有鼠鼠移动距离的最小值。

### 思路
考虑贪心。将老鼠和洞放在一起按坐标排序，然后从左向右遍历。若为老鼠，则跑向左侧离自己最近的洞；若为洞，则尽可能多的容纳自己右边的老鼠。

至于老鼠老鼠跑向右侧洞更优以及洞满了的情况，用自动机解决。

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5005;
const ll inf=0x3f3f3f3f3f3f3f3f;
int n,m;
struct object{
	ll pos,val;
	friend bool operator < (object x,object y){
		return x.pos<y.pos;
	}
}a[N<<1];
priority_queue<ll> mice;
priority_queue<object> hole;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].pos;
		a[i].val=-1;
	}
	int sum=0;
	for(int i=n+1;i<=n+m;i++){
		cin>>a[i].pos>>a[i].val;
		sum+=a[i].val;
	}
	if(sum<n){
		cout<<-1;
		return 0;
	}
	sort(a+1,a+n+m+1);
	ll ans=0;
	for(int i=1;i<=n+m;i++){
		if(~a[i].val){
			while(!mice.empty()&&a[i].val&&mice.top()>a[i].pos){
				ll t=mice.top();mice.pop();
				ans+=a[i].pos-t;
				a[i].val--;
				hole.push({2*a[i].pos-t,1});//洞满了，跑回左侧的洞
			}
			if(a[i].val) hole.push(a[i]);
		}
		else{
			if(!hole.empty()){//跑向左侧最近的洞
				object t=hole.top();hole.pop();
				ans+=a[i].pos-t.pos;t.val--;
				if(t.val) hole.push(t);
				mice.push(2*a[i].pos-t.pos);//向右跑
			}
			else{//左边没有洞
				mice.push(inf+a[i].pos);//保证下一个洞一定将其取出
				ans+=inf;//方便后面抵消
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```
~~十年OI一场空，不开long long见祖宗。~~

---

## 作者：FreedomKing (赞：0)

部分内容参考自大佬 @[wwlw](https://www.luogu.com.cn/user/83337)。

### 题目大意

一条直线上共有 $n$ 只鼠鼠和 $m$ 个鼠洞，分别给出 $n$ 只鼠鼠和 $m$ 个鼠洞在直线上的位置以及每个鼠洞的容量，求当每只鼠鼠均能到鼠洞中的所有鼠鼠移动距离的最小值。

### 思路

首先，为了使老鼠移动的最少，它们的移动路线绝不可能出现这两种情况：

1. 两只老鼠的行进方向相反且行进路线有重合部分，不难想到，两只老鼠的目的地分别是离对方更近的目的地。

2. 两只老鼠的行进方向相同且一只老鼠的行进路线完全包含另一只老鼠的行进路线，那么对于包含另一只的老鼠，那只被包含的老鼠的目的地相较于它的目的地一定是更近的。

设状态，我们考虑将 $dp_{i,j}$ 表示为前 $j$ 只老鼠进前 $i$ 个洞的最小距离之和，易得状态转移方程如下：

$$dp_{i,j}=\min_{j-c_i\le k\le j}{(dp_{i-1,k},\sum_{k<s\le j}{\left|a_i-p_s\right|})}$$

然后考虑使用前缀和优化复杂度即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5;
int a[N],dp[N][N],s[N],q[N],v[N],n,m,k;
struct node{
	int c,p;
}f[N];
bool cmp(node x,node y){
	return x.p<y.p;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=m;i++) cin>>f[i].p>>f[i].c;
	sort(f+1,f+m+1,cmp);
	for(int i=1;i<=n;i++) dp[0][i]=LONG_LONG_MAX;
	int cnt=0;
	for(int i=1;i<=m;i++){
		cnt+=f[i].c;
		for(int j=1;j<=n;j++) s[j]=((f[i].p-a[j])>0?(f[i].p-a[j]):-(f[i].p-a[j]))+s[j-1];
		int h=1,t=0;
		for(int j=0;j<=n;j++){
			while(h<=t&&q[h]<j-f[i].c) h++;
			while(h<=t&&dp[i-1][j]-s[j]<=v[t]) t--;
			q[++t]=j;
			v[t]=dp[i-1][j]-s[j];
			if(cnt>=j) dp[i][j]=s[j]+v[h];
			else dp[i][j]=LONG_LONG_MAX;
		}
	}
	cout<<((dp[m][n]!=LONG_LONG_MAX)?dp[m][n]:-1);
	return 0;
}
```

---

