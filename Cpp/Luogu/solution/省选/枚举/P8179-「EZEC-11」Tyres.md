# 「EZEC-11」Tyres

## 题目背景

这道题曾经有有趣的题目背景。

## 题目描述

有 $n$ 套轮胎，滴叉需要用这些轮胎跑 $m$ 圈。

使用第 $i$ 套轮胎跑的第 $j$ 圈（对每套轮胎单独计数）需要 $a_i+b_i(j-1)^2$ 秒。在本题中，你不需要担心爆胎，安全车，红旗或者不同的比赛策略。

滴叉需要进入维修站来更换轮胎，所消耗的时间为 $t$ 秒。特别地，滴叉使用的**第一套**轮胎不需要进站更换。

为了帮助滴叉拿下 WDC，你需要最小化总时间，总时间等于每圈的时间之和加上进站所花费的时间。

## 说明/提示

**【样例解释】**

对于第一个样例：

* 你先让滴叉用第一套轮胎跑一圈，消耗 $10$ 秒。
* 然后进站更换第二套轮胎，消耗 $50$ 秒。
* 然后用第二套轮胎跑三圈。第一圈消耗 $100$ 秒，第二圈消耗 $100+1\times 1^2=101$ 秒，第三圈消耗 $100+1\times 2^2=104$ 秒。
* 总时间为 $10+50+100+101+104=365$ 秒。

对于第二个样例，滴叉每圈更换一次新轮胎。

注意一套轮胎被卸下后并不会重置它跑的圈数。

对于第三个样例，滴叉先使用第一套轮胎跑 $4$ 圈，然后更换第二套轮胎跑 $6$ 圈。

**【数据范围】**

**本题采用捆绑测试**。

- Subtask 1（7 pts）：$n=1$。
- Subtask 2（9 pts）：$n\leq10$，$m\leq 100$。
- Subtask 3（13 pts）：$t=0$。
- Subtask 4（21 pts）：保证 $a_i,b_i$ 随机生成。
- Subtask 5（50 pts）：无特殊限制。

对于前 $100\%$ 的数据，$1\leq n,b_i\leq 500$，$0\leq t\leq 500$，$1\leq m\leq 2 \times 10^5$，$1\leq a_i\leq 10^9$。

## 样例 #1

### 输入

```
2 4 50
10 100
100 1```

### 输出

```
365```

## 样例 #2

### 输入

```
6 6 10
90 200
90 200
90 200
92 200
92 200
94 200```

### 输出

```
598```

## 样例 #3

### 输入

```
3 10 30
1000 8
1050 3
1100 1```

### 输出

```
10607```

# 题解

## 作者：dead_X (赞：18)

## 前言
EZEC R11 Problem C。

Div.1 预期通过 $50$，实际通过 $6$。

Div.2 预期通过 $30$，实际通过 $1$。

本来是想用这个题让大家笑一笑然后去轻松地开始这场比赛，结果似乎没有人笑……

[关注嘉然，顿顿解馋！](https://space.bilibili.com/672328094)
## Hint
每套轮胎一定只会使用一个连续的区间。

不然把这两段放一起能省一次换胎的时间。
## Solution 1
我会模拟！

第 $i$ 圈需要 $a_1+b_1(i-1)^2$ 的时间，暴力算出每一圈的时间加起来就行了。

可以通过 Subtask $1$。
## Solution 2
我会贪心！

如果 $t=0$，那么我们相当于每圈都可以自己选一套轮胎。

每套轮胎的单圈时间随着圈数上升，也就是一个单调的函数。

于是我们需要归并这 $n$ 个序列并求出前 $m$ 项。

使用一个堆即可，时间复杂度 $O(m\log n)$。

可以通过 Subtask $1,3,4$。

对于 Subtask $2$，如果你枚举 $2^n$ 个子集为至少使用一次的轮胎也可以通过。
## Solution 3
我会暴力 dp！

考虑枚举第 $i$ 套轮胎跑 $0\sim m$ 圈的代价，问题变为分组背包，时间复杂度 $O(nm^2)$。

可以通过 Subtask $1,2$。
## Solution 4
我会决策单调性优化！

直接优化前面的背包问题，时间复杂度可以降低到 $O(nm\log m)$。

还是只能通过 Subtask $1,2$。

这里忘记给一档分了，但是如果你在 $nm$ 比较大的时候直接跑 Solution $2$ 可以直接通过。

这种做法是可以卡的，直接将卡堆贪心的测试点中放几个 $(1,500)$ 再整体平移 $a_i$ 就可以了，但是由于没有验题人写这个算法（大家都认为这个算法的实现可能比本题正解更难）就没有卡掉，向大家道歉。

不过这样是不是也避免了一些人去写 $O(nm)$ 算法呢？
## Solution 5
我会找性质！

不妨把换胎时间加到第一圈的时间上，这样就不存在“换胎”这个操作了。

注意到我们不能使用堆贪心是因为价格不单调，考虑强行将价格变为单调。

我们考虑记 $S=\lceil\sqrt t\rceil$。不难发现对于每套轮胎，$S$ 圈以后的价格一定比 $S$ 圈之前的价格贵，并且也是单调的，我们可以将两部分分开决策。

于是我们对于每套轮胎的前 $S$ 圈做一个 dp，$S$ 圈之后用堆贪心，合并两边的结果即可。

如果使用 Solution $2,3$ 的方法，时间复杂度为 $O(n^2t+m\log n)$。

如果使用 Solution $2,4$ 的方法，时间复杂度为 $O(n^2\sqrt t\log(n\sqrt t)+m\log n)$。

两者都可以通过。
## Code
```cpp
//And in that light,I find deliverance.
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int B=25;
int f[503][33],g[13003],h[200003],a[503],b[503],c[503];
struct cmp
{
	bool operator()(const int&x,const int&y)
	{
		return (a[x]+b[x]*c[x]*c[x]>a[y]+b[y]*c[y]*c[y])||
			(a[x]+b[x]*c[x]*c[x]==a[y]+b[y]*c[y]*c[y]&&x>y);
	}
};
priority_queue<int,vector<int>,cmp> q;
signed main()
{
	int n=read(),m=read(),d=read(),s=0;
	for(int i=1; i<=n; ++i) 
	{
		a[i]=read(),b[i]=read(),c[i]=25,q.push(i);
		f[i][1]=a[i]+d;
		for(int j=2; j<=B; ++j) f[i][j]=f[i][j-1]+a[i]+b[i]*(j-1)*(j-1);
	}
	memset(g,0x3f,sizeof(g)),g[0]=0;
	for(int i=1; i<=n; ++i)
	{
		s=min(m,s+B);
		for(int j=s; j>=0; --j)
			for(int k=0; k<=B&&k<=j; ++k)
				g[j]=min(g[j],g[j-k]+f[i][k]);
	}
	for(int i=1; i<=m; ++i)
	{
		int x=q.top();
		q.pop(),h[i]=h[i-1]+a[x]+b[x]*c[x]*c[x],
		++c[x],q.push(x);
	}
	int ans=0x3f3f3f3f3f3f3f3f;
	for(int i=0; i<=s&&i<=m; ++i) ans=min(ans,g[i]+h[m-i]);
	printf("%lld\n",ans-d);
	return 0;
}
```

---

## 作者：bluewindde (赞：8)

upd 2024-11-20：修复了笔误，添加了对决策点单调的证明。

---

设 $dp_{i, j}$ 表示考虑了前 $i$ 个轮胎，跑了 $j$ 圈的最小时间，$f_i(x)$ 表示第 $i$ 个轮胎跑前 $x$ 圈所用的时间之和。容易转移：

$$
dp_{i, j} =
\min
\begin{cases}
dp_{i - 1, j}, \\
dp_{i - 1, 0} + f_i(j), \\
\min\limits_{k = 1}^{j} dp_{i - 1, j - k} + f_i(k) + t. \\
\end{cases}$$

其中 $f_i(x)$ 可以 $O(1)$ 计算：

$$
\begin{align*}
f_i(x) &= \sum\limits_{j = 1}^x (a_i + b_i (j - 1)^2) \\
&= a_i \cdot x + b_i \sum\limits_{j = 1}^{x - 1} j^2 \\
\end{align*}
$$

后半段的级数用自然数平方和公式计算，于是得到时间复杂度 $O(nm^2)$ 的做法。

猜一手决策单调性，对于上述第三个转移，每次二分最优决策点 $k$，时间复杂度 $O(nm \log m)$。

继续优化，发现对于固定的 $i$，最优决策点 $k$ 关于 $j$ 单调，于是不用二分，时间复杂度 $O(nm)$，可以通过。

---

证明决策单调性。函数 $f_i$ 可以近似看作函数 $g_i = a_i \cdot x + \frac 1 6 x (x + 1) (2x + 1)$，当 $a > 0$ 时，它在正数域上单调增。显然当 $i$ 相同时 $dp_{i, j}$ 关于 $j$ 不降，因此它们之和有单调性。

证明决策点单调。$j$ 增加相当于在坐标系中将不降函数 $y = dp_{i - 1, x}$ 的图像向右平移，它与前述单调递增函数 $g_i$ 之和组成的函数的最小值点也不减。（可以画图感性理解）

---

代码

```cpp
#include <iostream>
#include <string.h>

#define int long long

using namespace std;

static inline int s2(int x) { return x * (x + 1) * (2 * x + 1) / 6; }

int n, m, t;
struct node {
    int a, b;
} a[505];

int dp[2][200005];

static inline int calc(int i, int j, int k) {
    return dp[(i - 1) & 1][j - k] + t + a[i].a * k + a[i].b * s2(k - 1);
}

static inline void solve() {
    cin >> n >> m >> t;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].a >> a[i].b;
    memset(dp, 0x3f, sizeof dp);
    for (int i = 1; i <= n; ++i) {
        int ptr = 1;
        for (int j = 1; j <= m; ++j) {
            dp[i & 1][j] = min(dp[(i - 1) & 1][j], a[i].a * j + a[i].b * s2(j - 1));
            ptr = max(ptr, 1ll);
            while (ptr <= j && calc(i, j, ptr) < calc(i, j, ptr - 1))
                ++ptr;
            --ptr;
            dp[i & 1][j] = min(dp[i & 1][j], calc(i, j, ptr));
        }
    }
    cout << dp[n & 1][m] << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    cout.flush();
    return 0;
}
```

---

## 作者：DarksideCoderω (赞：8)

首先 , 可以发现对于一个轮胎 $i$ , 他的费用在 $t=0$ 是单调的 , 考虑用平均值将 $t$ 分配到后面的几圈中 , 可以证明 , 在十步操作内可以使序列单调 . $(\forall a,b=1,t=500)$ 

先用堆维护轮胎的费用 , $m$ 将减去这些圈数 , 把平均值段当做整体处理 , 正确性在平均值段被完全取完时显然的 .

然后 , 考虑平均值段在中间裂开的情况 . 在这种情况下 , 有一种策略是可能更优的 : 先把已经选入的圈再拿出来 $k$ 圈 , 再在没跑的选出 $k+m$ 圈 , 使其差值最小 .

> 1. 平均数段没跑完的轮胎 $($ 接下来称之为后面的 $)$ 不可能拿非平均数段 , 跑完的可以 .
>
> 2. 那么我们直接对后面的数列用堆 , 圈数是 $k+m~($ 设 $k$ 是个定值 $)$ , 那么当平均值段再次拿完后 , 中间裂开的部分可以直接还给前面 . 因此可以证明只要 $k+m\le 10$ . 就可以拿完某个平均数段$,$ 得到答案 .

最后的解决方式是跑两次分组背包 , 第一次求出放 $0\sim 10-m$ 圈的最小时间 , 第二次求出拿 $0\sim 10-m$ 圈的最多时间 . 不过我在实现时直接跑了 $10$ .  

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
inline long long GetSqrSum(long long x){return x*(x+1)*(x*2+1)/6;}
long long t,sum;
struct Tyres{
	long long a,b,c;
	long long cost;
	int id;
	inline long long Finder(long long _c){
		return a+b*(_c-1)*(_c-1)+t*(_c==1);
	}
	inline void Reader(){scanf("%lld%lld",&a,&b);}
	inline bool operator<(const Tyres&t)const{return cost*t.c>t.cost*c;}
};
const int MaxN=510;
priority_queue<Tyres>H;
Tyres T[MaxN];
int n,m;
int Size[MaxN];
long long Dp1[MaxN],Dp2[MaxN],Object[MaxN];
int main(){
	scanf("%d%d",&n,&m);
	scanf("%lld",&t);
	for(int i=1;i<=n;i++){
		T[i].Reader();T[i].id=i;T[i].c=1;
		while(T[i].a*T[i].c+T[i].b*GetSqrSum(T[i].c-1)+t>=T[i].Finder(T[i].c+1)*T[i].c)T[i].c++;
		T[i].cost=T[i].a*T[i].c+T[i].b*GetSqrSum(T[i].c-1)+t;
		H.push(T[i]);
	}
	while(true){
		Tyres P=H.top();H.pop();
		if(m>=P.c){
			m-=P.c;
			sum+=P.cost;
			Size[P.id]+=P.c;
			P.cost=T[P.id].Finder(Size[P.id]+1);
			P.c=1;
			H.push(P);
		}
		else break;
	}
	if(!m){printf("%lld\n",sum-t);return 0;}
	memset(Dp1,-1,sizeof(Dp1));Dp1[0]=0;
	memset(Dp2,-1,sizeof(Dp2));Dp2[0]=0;
	for(int i=1;i<=n;i++){
		int top=10;
		for(int j=1;j<=top;j++)
			Object[j]=Object[j-1]+T[i].Finder(Size[i]+j);
		for(int j=10;j>=0;j--){
			for(int k=1;k<=top&&k<=j;k++){
				if(Dp1[j-k]==-1)continue;
				if(Dp1[j]==-1||Dp1[j-k]+Object[k]<Dp1[j])
					Dp1[j]=Dp1[j-k]+Object[k];
			}
		}
	}
	for(int i=1;i<=n;i++){
		int top=min(10,Size[i]);
		for(int j=1;j<=top;j++)
			Object[j]=Object[j-1]+T[i].Finder(Size[i]-j+1);
		for(int j=10;j>=0;j--){
			for(int k=1;k<=top&&k<=j;k++){
				if(Dp2[j-k]==-1)continue;
				if(Dp2[j]==-1||Dp2[j-k]+Object[k]>Dp2[j])
					Dp2[j]=Dp2[j-k]+Object[k];
			}
		}
	}
	long long ans=0x7f7f7f7f7f7f7f7f;
	for(int i=m;i<=10;i++){
		if(Dp1[i]==-1||Dp2[i-m]==-1)continue;
		if(ans>Dp1[i]-Dp2[i-m])ans=Dp1[i]-Dp2[i-m];
	}
	printf("%lld\n",ans+sum-t);
	return 0;
}
```



---

## 作者：hcy1117 (赞：5)

## 前言
有趣的部分贪心，适合从部分分入手。
## 思路
1. 暴力 dp

    显然可以设 $dp_{j}$ 为跑 $j$ 圈的最小代价，枚举车轮 $i$ 有转移:
    $$
      dp_{j} = \min(dp_{j},dp_{k}+(k\ne 0)\times t+a_{i}\times (j-k)+b_{i}\times sum_{j-k-1})
    $$
    其中 $sum_{i} = \sum_{j=0}^{i} j^{2}$。
    
    时间复杂度 $O(nm^{2})$，能过 Subtask 1,2。
1. 特殊性质 $t=0$

   此时换胎没有代价，对于同一个轮胎圈数小时的代价一定比圈数大时的代价小，所以可以直接用堆贪心维护。

   时间复杂度 $O(m\log{n})$，能过 Subtask 3。
1. 正解

   发现在 $t>0$ 时不能贪心的原因是因为第一圈的代价要加上一个换胎的 $t$ 代价，这样的话无法保证第二圈的代价比第一圈大。直接用堆维护，可能会优先选择第二圈而没有算上换胎的代价，导致答案偏小。

   考虑分开计算，找到一个 $s$ 使得
   $$
    a_{i}+t \le a_{i}+b_{i}\times (s-1)^{2}
   $$
   即第 $s$ 圈的代价大于等于第 $1$ 圈的代价。这样我们就可以对 $s$ 及 $s$ 以后的圈重新用堆贪心，至于 $s$ 之前的圈可以用 dp 维护。

   当 $s=\sqrt t+1$ 时，因为 $b_{i}\ge 1$，上述条件显然成立。故可以对于每一个轮胎前 $\sqrt t$ 圈 dp，$\sqrt t+1$ 圈开始贪心，最后合并即可。时间复杂度 $O(n^{2}t+m\log{n})$。

1. 细节

   可能有的疑惑：对于一个轮胎可能合并时它对 dp 的贡献并不没有跑满 $1$ 到 $\sqrt t$ 圈，但对贪心部分的答案又有贡献（即跑了 $1$ 到 $p (p<\sqrt t)$ 和 $\sqrt t+1$ 到 $q(q\ge\sqrt t+1)$）。

   但仔细想想发现错解显然不优，所以无需考虑。
## 代码
```
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
const int INF=5e18+1;
int n,m,t;
struct node{
    int a,b,c;
}a[505];
int sum[25];
int dp[200005];
priority_queue<pii,vector<pii>,greater<pii>>Q;
int res[200005];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>t;
    int _t=(int)ceil(sqrt(t));
    for(int i=1;i<=n;i++)
        cin>>a[i].a>>a[i].b,a[i].c=_t;
    for(int i=1;i<=_t;i++)
        sum[i]=sum[i-1]+i*i;
    //对前根号t圈dp
    for(int i=1;i<=m;i++)
        dp[i]=INF;
    for(int i=1;i<=n;i++)
        for(int j=min(_t*i,m);j>=0;j--)
            for(int k=max(0ll,j-_t);k<=j;k++){
                dp[j]=min(dp[j],dp[k]+(k!=j&&k!=0)*t+a[i].a*(j-k)+a[i].b*sum[j-k-1]);
            }
    //从根号t+1圈开始贪心
    for(int i=1;i<=n;i++)
        Q.push({a[i].a+a[i].b*a[i].c*a[i].c,i}),a[i].c++;
    for(int i=1;i<=m;i++){
        res[i]=res[i-1]+Q.top().first;
        int x=Q.top().second;
        Q.pop();
        Q.push({a[x].a+a[x].b*a[x].c*a[x].c,x}),a[x].c++;
    }
    //合并
    int ans=INF;
    for(int i=0;i<=min(n*_t,m);i++)
        ans=min(ans,dp[i]+res[m-i]);
    cout<<ans<<"\n";
    return 0;
}

---

## 作者：dengjunhaodejia09 (赞：4)

听同学介绍了冷门算法部分贪心后写。

考虑若是选一个轮胎一次两次等等，每次代价都递增，那么很显然可以堆贪心，就是把每个轮胎塞进堆，每次选代价最小的。

但是当 $t>0$ 时第一次与第二次之间是没有单调性的，但是到了第 $\lceil\sqrt{t}\rceil$ 次时又与第一个有了单调性，考虑 $dp$ 处理前   $\lceil\sqrt{t}\rceil$ 个，后续堆贪心，记得堆贪心从 $\lceil\sqrt{t}\rceil+1$ 个开始，不用加 $t$，因为若是前面的没选选了后面的，那么是不如选前面的更优。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int L=25;
int dp[150005],ldp[150005];
int a[505],b[505];
int f[200005],Sum[30];
inline int get(int id,int tim){
    return a[id]+b[id]*(tim-1)*(tim-1);
}
signed main(){
    // freopen("1.in","r",stdin);
    // freopen("1.out","w",stdout);
    int T=1;
    while(T--){
        memset(dp,0,sizeof(dp));
        memset(ldp,0,sizeof(ldp));
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(f,0,sizeof(f));
        memset(Sum,0,sizeof(Sum));
        int n,m,t;
        cin>>n>>m>>t;
        for(int i=0;i<=n*L;i++){
            dp[i]=4e18;
        }
        dp[0]=0;
        for(int i=1;i<=n;i++){
            cin>>a[i]>>b[i];
            memcpy(ldp,dp,sizeof(dp));
            memset(Sum,0,sizeof(Sum));
            for(int j=1;j<=L;j++){
                Sum[j]=Sum[j-1]+a[i]+(j-1)*(j-1)*b[i];
            }
            for(int j=L*n;j>=0;j--){
                for(int k=1;k<=L;k++){
                    if(j-k<0){
                        break;
                    }
                    dp[j]=min(dp[j],ldp[j-k]+t+Sum[k]);
                }
            }
        }
        priority_queue<pair<int,pair<int,int> > ,vector<pair<int,pair<int,int> > > ,greater<pair<int,pair<int,int> > > > q;
        for(int i=1;i<=n;i++){
            q.push(make_pair(get(i,L+1),make_pair(i,L+1)));
        }
        int cnt=0;
        while(q.size() && cnt<=m){
            ++cnt;
            f[cnt]=f[cnt-1]+q.top().first;
            int it=q.top().second.first,num=q.top().second.second;
            q.pop();
            q.push(make_pair(get(it,num+1),make_pair(it,num+1)));
        }
        int Min=4e18;
        for(int i=0;i<=L*n;i++){
            if(i>m){
                continue;
            }
            Min=min(Min,dp[i]+f[m-i]);
        }
        cout<<Min-t<<'\n';
    }
    
    return 0;
}
```

---

