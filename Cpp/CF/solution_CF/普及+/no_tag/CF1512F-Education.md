# Education

## 题目描述

Polycarp is wondering about buying a new computer, which costs $ c $ tugriks. To do this, he wants to get a job as a programmer in a big company.

There are $ n $ positions in Polycarp's company, numbered starting from one. An employee in position $ i $ earns $ a[i] $ tugriks every day. The higher the position number, the more tugriks the employee receives. Initially, Polycarp gets a position with the number $ 1 $ and has $ 0 $ tugriks.

Each day Polycarp can do one of two things:

- If Polycarp is in the position of $ x $ , then he can earn $ a[x] $ tugriks.
- If Polycarp is in the position of $ x $ ( $ x < n $ ) and has at least $ b[x] $ tugriks, then he can spend $ b[x] $ tugriks on an online course and move to the position $ x+1 $ .

For example, if $ n=4 $ , $ c=15 $ , $ a=[1, 3, 10, 11] $ , $ b=[1, 2, 7] $ , then Polycarp can act like this:

- On the first day, Polycarp is in the $ 1 $ -st position and earns $ 1 $ tugrik. Now he has $ 1 $ tugrik;
- On the second day, Polycarp is in the $ 1 $ -st position and move to the $ 2 $ -nd position. Now he has $ 0 $ tugriks;
- On the third day, Polycarp is in the $ 2 $ -nd position and earns $ 3 $ tugriks. Now he has $ 3 $ tugriks;
- On the fourth day, Polycarp is in the $ 2 $ -nd position and is transferred to the $ 3 $ -rd position. Now he has $ 1 $ tugriks;
- On the fifth day, Polycarp is in the $ 3 $ -rd position and earns $ 10 $ tugriks. Now he has $ 11 $ tugriks;
- On the sixth day, Polycarp is in the $ 3 $ -rd position and earns $ 10 $ tugriks. Now he has $ 21 $ tugriks;
- Six days later, Polycarp can buy himself a new computer.

Find the minimum number of days after which Polycarp will be able to buy himself a new computer.

## 样例 #1

### 输入

```
3
4 15
1 3 10 11
1 2 7
4 100
1 5 10 50
3 14 12
2 1000000000
1 1
1```

### 输出

```
6
13
1000000000```

# 题解

## 作者：rui_er (赞：6)

有一个长度为 $n$ 的数组 $a$ 和一个长度为 $n-1$ 的数组 $b$，初始位置为 $pos=1$，每一天可以选择得到 $a_{pos}$ 元钱，或者花费 $b_{pos}$ 元钱（钱数不能为负）使得 $pos\leftarrow pos+1$。

现在希望买一台 $c$ 元的电脑，最少需要多少天。

---

做法：

对于 $i\in\left[1,n\right]$ 扫一遍，根据到达 $pos=i$ 位置的天数 $day_i$ 和剩余的钱 $now_i$，得到停留在 $pos=i$ 的位置需要多少天攒够 $c$ 元，取最小值即可。

递推所需信息的公式为：
            
$$
\begin{aligned}
day_1&=1\\
now_1&=a_1\\
ans_1&=\dfrac{c+a_1-1}{a_1}\\
day_i&=day_{i-1}+1+\dfrac{b_{i-1}-now_{i-1}+a_{i-1}-1}{a_{i-1}}\\
now_i&=\dfrac{b_{i-1}-now_{i-1}+a_{i-1}-1}{a_{i-1}}\times a_{i-1}+now_{i-1}-b_{i-1}\\
ans_i&=day_i+\dfrac{c-now_i+a_i-1}{a_i}\\
\end{aligned}
$$

最终答案即为 $Ans=\min\limits_{i=1}^nans_i$。

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define loop while(true)
#define rep(x,y,z) for(ll x=y;x<=z;x++)
#define per(x,y,z) for(ll x=y;x>=z;x--)
#define fil(x,y) memset(x, y, sizeof(x))
#define mulT0 ll T; for(scanf("%lld", &T);T;T--)
#define mulT1 ll T, rnds; for(scanf("%lld", &T),rnds=1;rnds<=T;rnds++)
using namespace std;
typedef long long ll;
const ll N = 2e5+5;

ll n, c, a[N], b[N], day[N], now[N], ans[N];

int main() {
	mulT0 {
		scanf("%lld%lld", &n, &c);
		rep(i, 1, n) scanf("%lld", &a[i]);
		rep(i, 1, n-1) scanf("%lld", &b[i]);
		day[1] = 1; now[1] = a[1]; ans[1] = (c + a[1] - 1) / a[1];
		ll Ans = ans[1];
		rep(i, 2, n) {
			day[i] = day[i-1] + 1 + (b[i-1] - now[i-1] + a[i-1] - 1) / a[i-1];
			now[i] = (b[i-1] - now[i-1] + a[i-1] - 1) / a[i-1] * a[i-1] + now[i-1] - b[i-1];
			ans[i] = day[i] + (c - now[i] + a[i] - 1) / a[i];
			Ans = min(Ans, ans[i]);
		}
//		rep(i, 1, n) printf("I=%lld DAY=%lld NOW=%lld ANS=%lld\n", i, day[i], now[i], ans[i]);
		printf("%lld\n", Ans);
	}
	return 0;
}
```

---

## 作者：SunsetVoice (赞：2)

建议降橙。

翻译不全，并没有补充 $a$ 序列不降此点，且这点对贪心的证明**极为必要**，强烈建议添加~~并严惩翻译者~~。

由于不能返回，所以直接从 $1$ 到 $n$ 直接扫一遍，没有必要考虑回头的情况。

当碰到一个值时：

- 在该点停下，直接加到 $c$。此时设是第 $dt$ 步来到该位置，当前手上还有 $dsum$ 个钱，此时答案为 $dt+\frac{\left \lceil c-dsum \right \rceil }{a_i}$。
- 继续向前。**一旦当前手上的钱 $\ge b_i$ 就直接向前**。此时让 $dt$ 和 $dsum$ 改变。

贪心正确性证明：由于题目保证了单调不减，所以继续向前显然不比当前劣（即 $a_i\le a_{i+1}$），加上若最终要向前，$b_i$ 必然会且只会取一次，所以最大化。

附：理论上空间可以从 $n$ 优化到 $1$，但输入方式限制了它（悲）。

---

## 作者：No21 (赞：1)

### 解题思路

看到状态转移很容易想到 DP，不过在 DP 之前，我们要考虑一个问题，对于一个最优解，它的位置移动过程是否有规律。

我们发现，最优解一定是先移动到某个位置，然后在某个位置一直赚钱。

给出证明：

如果不在一个位置一直赚钱，那么就代表我们是边走边赚钱。我们设两个 $pos_i$ 和 $pos_j$ 并且 $pos_i<pos_j$，且我们边走边赚钱会经过 $pos_i$ 和 $pos_j$，那么对于 $a_{pos_i}$ 和 $a_{pos_j}$，我们分类讨论。

- 若 $a_{pos_i}<a_{pos_j}$，也就是说我们在 $pos_j$ 赚的钱更多，那么我们在 $pos_i$ 赚钱的时候其实一直是亏的（本可以用这几天在 $pos_j$ 赚钱）。

- 若 $a_{pos_i}>a_{pos_j}$，也就是说我们在 $pos_i$ 赚的钱更多，那么我们就没有必要走到 $pos_j$（花钱还让收入变少了）。

- 若 $a_{pos_i}=a_{pos_j}$，也就是说我们在 $pos_i$ 和 $pos_j$ 赚的钱一样多，那么我们也没有必要走到 $pos_j$（花钱但是收入不变）。

有了这个结论，DP 就变得非常简单，因为到达每个点后一直赚钱所需要的天数是固定的，所以我们设 $dp_{i,0}$ 为到达 $i$ 点所需要的天数，$dp_{i,1}$ 为到达 $i$ 点后的剩余钱数。

到 $i$ 点是需要路费的，那么怎么赚路费是最优的呢？我们将路费看作目标费用，其实和上面一样，因此我们只要在 $1$ 到 $i-1$这些点里收入最高的那个点一直赚够到 $i$ 点的路费即可，因此我们对每个点需要维护一个前缀最大值和前缀和。最后加上在 $i$ 的赚钱时间扫一遍找最小天数即可。

蒟蒻的转移方程没有化简，直接跟着思路写的qwq，看起来比较长，其实还是比较好想的。还有，记得开 long long。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace TO
{
    const int N=2e5+21;
    int T,n,c;
    int a[N],b[N],maxx[N],sum[N],dp[N][2],ans;
    int mian()
    {
        cin>>T;
        while(T--)
        {
            ans=1e9;
            cin>>n>>c;
            for(int i=1;i<=n;i++)
            {
                cin>>a[i];
                if(a[i-1]<a[maxx[i-1]])
                    maxx[i]=maxx[i-1];
                else
                    maxx[i]=i-1;
            }
            for(int i=2;i<=n;i++)
            {
                cin>>b[i];
                sum[i]=sum[i-1]+b[i];
            }
            for(int i=2;i<=n;i++)
            {
                dp[i][0]=dp[maxx[i]][0]+ceil(1.0*(sum[i]-sum[maxx[i]]-dp[maxx[i]][1])/a[maxx[i]])+(i-maxx[i]);
                dp[i][1]=a[maxx[i]]*ceil(1.0*(sum[i]-sum[maxx[i]]-dp[maxx[i]][1])/a[maxx[i]])-(sum[i]-sum[maxx[i]]-dp[maxx[i]][1]);
            }
            for(int i=1;i<=n;i++)
                ans=min(ans,dp[i][0]+(int)ceil(1.0*(c-dp[i][1])/a[i]));
            cout<<ans<<'\n';
        }
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return TO::mian();
}
```

---

## 作者：irris (赞：1)

## Preface

为啥你谷所有题解都没证正确性啊。仅仅补一发证明。

## Solution

我们更关心的是为什么当我们确定了一个位置，然后死命选 $a$ 不动后，我们 **不会在前面其他位置选其它的 $\bm a$ 来减少在这里选 $\bm a$ 的天数**。事实上，这保证了解法的正确性。

不妨假设确定的位置为 $a_i$，前面的位置为 $a_j$。

+ （虽然题目约束条件里没有，但是若 $a_i \lt a_j$）：我花了一些天走到下面某一个位置，结果这个位置的效率还比前面一个位置低，那为啥不直接在 $a_j$ 选到底呢？
+ $a_i \geq a_j$：那么这个时候在前面花 1 天选 $a_j$，后面选 $a_i$ 的时候，整除的答案只能减少 1 或 0，是不能减少 2 的（否则在整除上跨越了至少一个整周期，那么 $a_j \gt a_i$），那么减少 1 还好，减少 0 还不如在 $a_i$ 选。所以在 $a_i$ 选不劣。

剩下的就是简单递推了，对每个位置记录到这里最少需要多少天，还剩下多少钱，最后 **向上取整** 算一下即可。如果这个部分也不会的话，可以参考一下代码。

## Code

```cpp
#include <bits/stdc++.h>

namespace FastIO {
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= ch == '-', ch = getchar(); while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); return w ? ((~x) + 1) : x; }
	template <typename T> inline void write(T x) { x && (write<T>(x / 10), putchar(x % 10 ^ '0')); }
	template <typename T> inline void print(T x) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x); }
	template <typename T> inline void print(T x, char end) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x), putchar(end); }
};
using namespace FastIO;

inline long long dv(long long a, long long b) { return std::max((a + b - 1) / b, 0ll); }

#define MAXN 200001
long long a[MAXN], b[MAXN], c[MAXN], d[MAXN];
void solve() {
	int N = read<int>(), T = read<int>(), ans = 1000000000;
	d[1] = 0, c[1] = 0;
	for (int i = 1; i <= N; ++i) a[i] = read<int>();
	for (int i = 1; i < N; ++i) 
		b[i] = read<int>(), d[i + 1] = dv(b[i] - c[i], a[i]), c[i + 1] = c[i] + d[i + 1] * a[i] - b[i], d[i + 1] += d[i] + 1;
	for (int i = 1; i <= N; ++i) ans = std::min((long long)ans, d[i] + dv(T - c[i], a[i]));
	print<int>(ans, '\n');
}
int main() {
	int T = read<int>();
	while (T--) solve();
	return 0;
}
```

---

## 作者：dingyi2007 (赞：1)

## 题意：
+ 原题翻译说得非常简洁明了，[请自行查看](https://www.luogu.com.cn/problem/CF1512F)。
+ 题目翻译并没有给出输入格式和数据范围，下面展示一下：
>1. 首先输入 $t$, 表示有 $t(1 \le t \le 2\cdot 10^5)$ 组数据。
>1. 对于每组数据，第一行输入两个整数 $n , c (2 \le n \le 2\cdot10^5,1 \le c \le 10^9)$ 分别表示等级数和买电脑所需的钱数。
>1. 第二行，有一个长为 $n$ 的**不降**整数序列，第 $i$ 个数 $a_i (1 \le a_i \le 10^9)$ 表示第 $i$ 级每天能拿多少钱。
>1. 第三行，有一个长为 $n-1$ 的序列，第 $i$ 个数 $b_i (1 \le b_i \le 10^9)$ 表示升到第 $i+1$ 级需要多少钱。
## 分析：
不难看出，本题是一道动态规划的题，我们可以用用一个二维数组  _$dp_{i,j}$_ 来表示在第 $i$ 天升到 $j$ 级后停止升级攒钱买电脑所需的天数。复杂度 $O(nc)$,**很明显会 TLE 掉**。于是我们来思考一个不会TLE的方法。\
我们发现如果升到第 $i$ 级最早是第 $j$ 天才能实现，那么，可以证明在 $j$ 天升到第 $i$ 级是升到第 $i$ 级后一直攒钱买电脑的最优解。
### 证明：
假设在升到第 $i$ 级最早是第 $j$ 天才能实现，而我们选择在第 $k(k > j)$ 天实现，由于升到第 $i$ 级所需的钱相同，所以我们只需比较获得的钱即可。由于 $j$ 天前和 $k$ 天后两种情况一致，不考虑，只考虑 $j$ 到 $k$ 这 $k-j$ 天的情况。在这段时间中，选择在第 $j$ 天升级获得的钱数是 _$(k-j) \cdot a_i$_ ,而选择在第 $k$ 天升级获得的钱数是 _$(k-j) \cdot a_{i-1}$_ ,由于 $a$ 是一个**不降**序列，故 _$(k-j) \cdot a_i \ge (k-j) \cdot a_{i-1}$_ ,所以选择在第 $j$ 天升级是最优解，得证。
### 接着分析：
于是，我们可以使用两个一维数组 $k$ 表示升到某级最少钱数以及 $w$ 来表示最快升到某级剩余的钱数。于是得到公式：
>* $k_i = k_{i-1} + \left\lceil\dfrac{b_{i-1}-w_{i-1}}{a_{i-1}}\right\rceil$
>* 
>* $w_i = w_{i-1} - b_{i-1} + \left\lceil\dfrac{b_{i-1}-w_{i-1}}{a_{i-1}}\right\rceil \cdot a_{i-1}$
## 小技巧：
$\left\lceil\dfrac{m}{n}\right\rceil = \left\lfloor\dfrac{m+n-1}{n}\right\rfloor$

我们之所以要要如此操作的愿意是 $C++$ **默认下取整**。
### 附代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<string>

using namespace std;
#define LL long long
#define Max 200005

int a[Max]/*每级获得的钱数*/,b[Max]/*升级所需的钱数*/;
LL k[Max]/*升到每级最少的天数*/,w[Max]/*最快升到每级剩的钱数*/;
int t;

int main()
{
	scanf("%d",&t);
	while (t--)
	{
		int n,c;
		scanf("%d%d",&n,&c);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		for (int i=1;i<n;i++) scanf("%d",&b[i]);
		k[1]=1,w[1]=a[1];
		for (int i=2;i<=n;i++)
		{
			k[i]=1ll*k[i-1]+(1ll*b[i-1]-w[i-1]+a[i-1]-1)/a[i-1]+1;
			w[i]=1ll*(b[i-1]-w[i-1]+a[i-1]-1)/a[i-1]*a[i-1]+w[i-1]-b[i-1];
		}
		LL miin=1ll*(c+a[1]-1)/a[1];/*不升级攒钱买电脑*/
		for (int i=2;i<=n;i++)
		{
			LL m=1ll*k[i]+1ll*(c-w[i]+a[i]-1)/a[i];/*求出升到第i级后一直攒钱买电脑所需的天数*/
			miin=min(maxn,m);/*球最小值*/
		}
		printf("%lld\n",miin);
	}

	return 0;
}
```
### 本题解到此结束，感谢各位观看。

---

## 作者：ZLCT (赞：0)

# CF1512F Education
## 题意
给定一个长度为 $n$ 的序列 $a$ 和长度为 $n-1$ 的序列 $b$ 以及一个整数 $c$。初始在 $1$ 位置，有一个 $sum=0$ 每次操作可以选择令 $sum\leftarrow sum+a_i$ 或者花费 $b_i$ 代价令位置 $+1$，求要使 $sum$ 始终非负，最少多少步骤能使 $sum\ge c$。
## solution
首先我们会注意到一件事情，由于这是个不归路，所以最后我们一定停在某个点一直执行 $sum\leftarrow sum+a_i$ 的操作。\
于是我们的题目就转化为选择哪一个点能使答案最小。
### greedy
我们贪心地想到我们选择的点在 $1\sim i$ 之间一定是最大的。\
证明：\
假设存在一个最优解不是 $1\sim i$ 的最大值且比贪心解更优，那么我们通过调整法把 $1\sim i$ 中最大值后面的点舍去，每次获得的贡献既多了，又不需要支付代价。肯定不劣于选择 $i$ 点。
我们继续贪心地想假设已经确定了一个点 $i$，那么我们应该以什么策略走到 $i$ 呢？\
这个第一反应是想到既然最后一个的贡献最快，前面能少选则少选，除非选不了了才在不能走的位置加几次补到可以走为止。\
你会发现这个思路能 AC，但是这是个错误思路。\
假设前面有一个数比这个数大，我们更应该选择那一个数使得每个操作的性价比最高。\
于是这个贪心就变成如果选不了了，就在 $1\sim j$ 中选择一个最大的 $a_k$ 多加几遍知道可以选。\
于是我们就可以对于每一个位置都作为 $i$ 计算出一个答案，最终答案就是所有答案的最小值。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+666;
const int inf=1e9+7;
using ld=long double;
const ld eps=1e-7;
int n,c,ans,sum,money,tim,now;
int a[N],b[N];
void solve(){
    cin>>n>>c;
    ans=inf;
    sum=0;
    money=0;
    tim=0;
    now=0;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int i=1;i<n;++i){
        cin>>b[i];
    }
    for(int i=1;i<=n;++i){
        ans=min(ans,tim+(c-money+a[i]-1)/(a[i]));
        now=max(now,a[i]);
        if(b[i]<=money){
            tim++;money-=b[i];
        }else{
            int d=(b[i]-money)/now;
            tim+=d;money+=now*d;
            if(b[i]>money){
                tim++;money+=now;
            }
            tim++;money-=b[i];
        }
    }
    cout<<ans<<'\n';
}
signed main(){
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：haokee (赞：0)

一种不需要额外开数组的解法。

既然是要求出买新电脑的最少天数，那么最后一个可能的打工地点 $i$ 的日薪 $a_i$ 一定是 $a_1\sim a_i$ 当中最大的那个，不然我晋升上来有什么意义是不是？还浪费了钱去学习。因此，我们可以将打工的过程分为两部分：

- 从第一个位置干到满足条件的位置 $i$；

- 在 $i$ 位置上一直干到能够买一台新电脑。

但是，我们从 $1$ 干到 $i$ 所经过的所有位置当中只有日薪比前面优的才会在哪里停留打工，不然在上一个日薪更高的地方一直打工一遍凑齐不久是了？

因此，我们可以看出来了，这是一个分段的问题。实现就很简单了，当遇到一个 $a_i$ 比 $a_1\sim a_{i-1}$ 都要大的 $i$ 时，就在上一个地方一直打工知道赚完到 $i$ 的钱，然后移到 $i$，计算剩余的钱，求出在最后 $i$ 打工买电脑的天数加起来，取最小值就行了。

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const LL kMaxN = 2e5 + 5;

LL a[kMaxN], b[kMaxN], ned, t, n, cost, tim, sum, cnt, has, m, ans;
  
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t; t--) {
    cin >> n >> cost;
    m = sum = ned = has = tim = 0;
    ans = 1e18;
    for (LL i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (LL i = 1; i < n; i++) {
      cin >> b[i];
    }
    for (LL i = 1; i <= n; i++) {
      if (a[i] > m) {
        LL days = max(0LL, m ? (ned - sum + m - 1) / m : 0);                 // 需要工作的天数
        sum = sum + days * m - ned;                                          // 升级之后留下来的钱
        ans = min(ans, has + days + tim + (cost - sum + a[i] - 1) / a[i]);   // 在当前位置打工
        has += days + tim;                                                   // 累加 1-i 已经经过的天数
        m = a[i];                                                            // 更改最大值
        ned = tim = 0;                                                       // 清空
      }
      ned += b[i];                                                           // 晋升所需要的钱
      tim++;                                                                 // 看视频的天数
    }
    cout << ans << '\n';
  }
  return 0;
}  
```

---

## 作者：EC75 (赞：0)

### 难度

这道题还是普高难度。

### 思路

由于数组 $a$ 不会减少，如果我们想在某个时刻得到位置 $x$，最好尽早得到它。

因此，解决方案看起来是这样的：晋升到某个职位，用它为笔记本电脑赚钱。我们来看看这个职位的数量，用简单的公式来计算晋升到这个职位所需的天数，以及购买笔记本电脑所需的天数。

最后，从所有选项中，选择最小的一个。

## 代码

~~没凑够字数啊!~~

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void solve() {
    int n, c;
    cin >> n >> c;
    vector<int> a(n);
    vector<int> b(n - 1);
    for (int &e : a) {
        cin >> e;
    }
    for (int &e : b) {
        cin >> e;
    }
    b.push_back(0);
    ll ans = 1e18;
    ll cur = 0;
    ll bal = 0;
    for (int i = 0; i < n; i++) {
        ans = min(ans, cur + max(0ll, c - bal + a[i] - 1) / a[i]);
        ll newDays = max(0ll, b[i] - bal + a[i] - 1) / a[i];
        cur += newDays + 1;
        bal += a[i] * newDays - b[i];
    }
    cout << ans << "\n";
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        solve();
    }
    return 0;
}
```


---

