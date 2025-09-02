# Bear and Paradox

## 题目描述

Limak is a big polar bear. He prepared $ n $ problems for an algorithmic contest. The $ i $ -th problem has initial score $ p_{i} $ . Also, testers said that it takes $ t_{i} $ minutes to solve the $ i $ -th problem. Problems aren't necessarily sorted by difficulty and maybe harder problems have smaller initial score but it's too late to change it — Limak has already announced initial scores for problems. Though it's still possible to adjust the speed of losing points, denoted by $ c $ in this statement.

Let $ T $ denote the total number of minutes needed to solve all problems (so, $ T=t_{1}+t_{2}+...+t_{n} $ ). The contest will last exactly $ T $ minutes. So it's just enough to solve all problems.

Points given for solving a problem decrease linearly. Solving the $ i $ -th problem after $ x $ minutes gives exactly ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF639E/fc7b6e21f01df9be187009231b77169e209e48ba.png) points, where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF639E/bafa872406a0b1a8fb62b20801e6fefc299422a3.png) is some real constant that Limak must choose.

Let's assume that $ c $ is fixed. During a contest a participant chooses some order in which he or she solves problems. There are $ n! $ possible orders and each of them gives some total number of points, not necessarily integer. We say that an order is optimal if it gives the maximum number of points. In other words, the total number of points given by this order is greater or equal than the number of points given by any other order. It's obvious that there is at least one optimal order. However, there may be more than one optimal order.

Limak assumes that every participant will properly estimate $ t_{i} $ at the very beginning and will choose some optimal order. He also assumes that testers correctly predicted time needed to solve each problem.

For two distinct problems $ i $ and $ j $ such that $ p_{i}&lt;p_{j} $ Limak wouldn't be happy to see a participant with strictly more points for problem $ i $ than for problem $ j $ . He calls such a situation a paradox.

It's not hard to prove that there will be no paradox for $ c=0 $ . The situation may be worse for bigger $ c $ . What is the maximum real value $ c $ (remember that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF639E/bafa872406a0b1a8fb62b20801e6fefc299422a3.png)) for which there is no paradox possible, that is, there will be no paradox for any optimal order of solving problems?

It can be proved that the answer (the maximum $ c $ as described) always exists.

## 说明/提示

In the first sample, there are $ 3 $ problems. The first is $ (4,1) $ (initial score is $ 4 $ and required time is $ 1 $ minute), the second problem is $ (3,1) $ and the third one is $ (10,8) $ . The total time is $ T=1+1+8=10 $ .

Let's show that there is a paradox for $ c=0.7 $ . Solving problems in order $ 1 $ , $ 2 $ , $ 3 $ turns out to give the best total score, equal to the sum of:

1. solved $ 1 $ minute after the start: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF639E/5d24fac1eb4d5cfcf64d9207f252db7e5c0491df.png)
2. solved $ 2 $ minutes after the start: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF639E/f85b826c56f62f67a5d3d0474c30c9b216890f8c.png)
3. solved $ 10 $ minutes after the start: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF639E/c37a6ee62d21f25241df408bcd9cb5719cc26559.png)

So, this order gives $ 3.72+2.58+3=9.3 $ points in total and this is the only optimal order (you can calculate total scores for other $ 5 $ possible orders too see that they are lower). You should check points for problems $ 1 $ and $ 3 $ to see a paradox. There is $ 4&lt;10 $ but $ 3.72&gt;3 $ . It turns out that there is no paradox for $ c=0.625 $ but there is a paradox for any bigger $ c $ .

In the second sample, all $ 24 $ orders are optimal.

In the third sample, even for $ c=1 $ there is no paradox.

## 样例 #1

### 输入

```
3
4 3 10
1 1 8
```

### 输出

```
0.62500000000
```

## 样例 #2

### 输入

```
4
7 20 15 10
7 20 15 10
```

### 输出

```
0.31901840491
```

## 样例 #3

### 输入

```
2
10 20
10 1
```

### 输出

```
1.00000000000
```

# 题解

## 作者：Kinandra (赞：10)

标签: 贪心, 二分答案.

#### Part 1

首先我们需要知道一个最优顺序有什么样的性质.

实际上是按 $\frac{p_i}{t_i}$ 递减的顺序就可以的到最优顺序. 考虑反证, 若(排序后)存在一个 $i$ 使得 $\frac{p_i}{t_i}<\frac{p_{i+1}}{t_{i+1}}$, 则这两题的得分为 $s_1=p_i(1-\frac{c(T'+t_i)}{T})+p_{i+1}(1-\frac{c(T'+t_{i}+t_{i+1})}{T})$ , 其中 $T'=\sum_{j=1}^{i-1}t_i$.

我们交换这两道题的顺序, 其他题目得分显然不发生变化, 而这两题的得分变为 $s_2=p_{i+1}(1-\frac{c(T'+t_{i+1})}{T})+p_{i}(1-\frac{c(T'+t_{i}+t_{i+1})}{T})$ , 那么 $s_1-s_2=p_i\frac{ct_{i+1}}{T}-p_{i+1}\frac{ct_i}{T}=\frac{c}{T}(p_it_{i+1}-p_{i+1}t_i)$, 由 $\frac{p_i}{t_i}<\frac{p_{i+1}}{t_{i+1}}$ 可知 $s1-s2<0$ , 矛盾.

#### Part 2

有了 `Part 1` 的结论后, 我们就可以处理出每个问题的最早完成时间和最晚完成时间. 然后二分一个 $c$ , 判断每个问题 $i$ 存不存在一个 $p_j<p_i$ 的 $j$ , 使得 $i$ 最晚完成的得分小于 $j$ 最早完成的得分, 如果存在就不合法, 否则就合法.

时间复杂度 $\mathcal O(n(\log eps+\log n))$.

```cpp
#include <bits/stdc++.h>
using namespace std;
int read();

int n;
int st[200005], top;
long long T;
struct P {
    long long p, t, tmin, tmax, sum;
    int fp;
} p[200005];

bool cmppdivt(P a, P b) { return a.p * b.t > b.p * a.t; }
bool cmpp(P a, P b) { return a.p < b.p; }
bool check(double x) {
    double mx = 0, tmx = 0;
    for (int i = 1; i <= n; ++i) {
        if (p[i].p != p[i - 1].p) mx = tmx;
        if ((1 - x * p[i].tmax / T) * p[i].p < mx) return 0;
        tmx = max(tmx, (1 - x * p[i].tmin / T) * p[i].p);
    }
    return 1;
}

int main() {
    n = read();
    for (int i = 1; i <= n; ++i) st[i] = p[i].p = read();
    for (int i = 1; i <= n; ++i) T += (p[i].t = read());

    sort(st + 1, st + 1 + n), top = unique(st + 1, st + 1 + n) - st - 1;
    for (int i = 1; i <= n; ++i)
        p[i].fp = lower_bound(st + 1, st + top + 1, p[i].p) - st;
    sort(p + 1, p + 1 + n, cmppdivt);
    for (int i = 1; i <= n; ++i) p[i].sum = p[i - 1].sum + p[i].t;

    for (int i = 1, j; i <= n; i = j + 1) {
        j = i;
        while (j < n && p[j + 1].p * p[i].t == p[i].p * p[j + 1].t) ++j;
        for (int k = i; k <= j; ++k)
            p[k].tmin = p[i - 1].sum + p[k].t, p[k].tmax = p[j].sum;
    }
    sort(p + 1, p + 1 + n, cmpp);
    double l = 0, r = 1, mid;
    while (r - l > 1e-6) check(mid = (l + r) / 2) ? l = mid : r = mid;
    printf("%.8lf", l);
    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
int read() {
    int x = 0, f = 1;
    char c = gc;
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x * f;
}
```



---

## 作者：xht (赞：6)

> [CF639E Bear and Paradox](https://codeforces.com/contest/639/problem/E)

## 题意

- 有 $n$ 个问题，第 $i$ 个问题的初始得分为 $p_i$，所花费的时间为 $t_i$。
- 设 $T = \sum_{i=1}^n t_i$，你可以按照某个顺序恰好花费 $T$ 时间完成所有问题。
- 若你在时刻 $x$ 完成了问题 $i$，你可以得到 $p_i \cdot (1 - \frac{cx}T)$ 的得分，其中 $c$ 是一个 $[0,1]$ 的实数。
- 对于每个 $c$，都存在至少一个可以使得分最大的最佳做题顺序。
- 对于一个做题顺序，若出现了两个问题 $i,j$ 满足 $p_i < p_j$ 但 $i$ 的得分严格大于 $j$ 的得分，则认为这种做题顺序存在悖论。
- 你需要求出最大的 $c$，使得这个 $c$ 对应的任意最佳做题顺序都不存在悖论。
- $n \le 1.5 \times 10^5$，$p_i,t_i \le 10^8$，答案精度误差 $\le 10^{-6}$。

## 题解

最佳做题顺序一定是按照 $\frac{p_i}{t_i}$ 从大到小排序的，在所有 $\frac{p_i}{t_i}$ 都不相同的情况下，设排序后第 $i$ 个问题的得分为 $p_i - \frac{p_i\sum_{j=1}^{i}t_j}{T}c$，即有 $n$ 个关于 $c$ 的一次函数。

题目要求不存在悖论，等价于最大的 $c$ 满足这 $n$ 个一次函数在 $(0,c)$ 中不存在交点。

找到对于每个相同的 $p_i$ 最靠上和最靠下的一次函数，解出相邻两个 $p_i$ 对应的函数交点，取最小的横坐标即可。

当有 $\frac{p_i}{t_i}$ 相同的时候，会出现有多个最佳做题顺序，因此需要找到每道题对应的一次函数的斜率的最大和最小值。

时间复杂度 $\mathcal O(n \log n)$。

## 代码

```cpp
const int N = 1.5e5 + 7;
const ld eps = 1e-10L;
int n;
ll T, s;
struct P {
	int p, t;
	ld x, l, r;
	inline bool operator < (const P &o) const { return x > o.x; }
} p[N];

int main() {
	rd(n);
	for (int i = 1; i <= n; i++) rd(p[i].p);
	for (int i = 1; i <= n; i++)
		rd(p[i].t), p[i].x = 1.0L * p[i].p / p[i].t, T += p[i].t;
	sort(p + 1, p + n + 1);
	for (int i = 1, j = 0; i <= n; i = j + 1) {
		while (j + 1 <= n && abs(p[i].x - p[j+1].x) < eps) ++j;
		for (int k = i; k <= j; k++) p[k].l = 1.0L * p[k].p * (s + p[k].t) / T;
		for (int k = i; k <= j; k++) s += p[k].t;
		for (int k = i; k <= j; k++) p[k].r = 1.0L * p[k].p * s / T;
	}
	sort(p + 1, p + n + 1, [&](P x, P y) { return x.p < y.p; });
	ld ans = 1;
	for (int i = 1; i < n; i++)
		if (p[i].p < p[i+1].p) {
			ld l = 1e8L, r = 0.0L;
			int j = i;
			while (j && p[j].p == p[i].p) l = min(l, p[j--].l);
			j = i + 1;
			while (j <= n && p[j].p == p[i+1].p) r = max(r, p[j++].r);
			if (l + eps < r) ans = min(ans, (p[i].p - p[i+1].p) / (l - r));
		}
	printf("%.10Lf\n", ans);
	return 0;
}
```

---

## 作者：installb (赞：3)

这个 $c$ 明显提示二分答案了  

最优顺序用邻项交换排序求出  
令开始做 $i,j$ 中先做的那个时已经用去了 $x$ 时间。  
令先做 $i$ 更优，则有：  
$$p_i\times (1-\frac{c(x+t_i)}{T})+p_j\times (1-\frac{c(x+t_i+t_j)}{T})>p_i\times (1-\frac{c(x+t_i)}{T})+p_j\times (1-\frac{c(x+t_i+t_j)}{T})$$  
$$xp_i+p_it_i+xp_j+p_jt_i+p_jt_j<xp_j+p_jt_j+xp_i+p_it_i+p_it_j$$  
$$p_jt_i<p_it_j$$  
即 $\frac{t_i}{p_i}<\frac{t_j}{p_j}$  
对于 $\frac{t_i}{p_i}$ 相等的数可以随意交换，这样可以求出**每个数最早和最晚**可以放在哪个时间做完，这些数形成**连续的一段**，且**段与段之间位置关系确定**，第 $i$ 个问题最早完成时间为这一段的起始时间加 $t_i$，最晚就是这个段的结束时间，即这个段的起始时间加这个段中所有问题用时之和，起始时间为这个段之前所有段用时之和。  

如果两问题产生了 paradox，则同时满足两个条件：  
$p_i<p_j$  
$p_i\times(T-cx_i)>p_j\times(T-cx_j)$  
$x_i$ 代表完成时间。  
一定考虑最坏情况是否有 paradox，所以 $x_i$ 取最小时间，$x_j$ 取最大时间。  
先按 $p_i$ 排序，把第一个式子的影响去掉。然后保存所有 $p_k<p_i$ 的 $p_k\times(T-cx_k)$ 的最大值，做比较，即可。注意 $p$ 是严格小于。

做这步的时候可以看出答案是有单调性的..  

如果两问题处于同一段，也并不会有问题，因为在判断是否有 paradox 时，两数**分别处于段的第一个和最后一个**。

```cpp
using namespace std;
typedef long long LL;
const LL N = 300005;

struct node{
	LL p,t;
}s[N];
bool cmp(node x,node y){ return x.t * y.p < y.t * x.p; }
bool cmpp(LL x,LL y){ return s[x].p < s[y].p; }

LL n,sum = 0;
LL lis[N],l[N],r[N];

char chk(double c){
	double mx = 0.0,mx2 = 0.0;
	LL tmp = -1;
	for(LL i = 1;i <= n;i ++){
		LL now = lis[i];
		if(s[lis[i]].p != s[lis[i - 1]].p){
//			mx = max(mx,mx2);
			mx = mx2; // p 增大了，把 mx2 加入 mx
			mx2 = 0.0;
		}
		if(s[now].p * (sum - c * r[now]) < mx) return 0; // maximum of p != now_p
		mx2 = max(mx2,s[now].p * (sum - c * l[now])); // maximum of p = now_p
	}
	return 1;
}

int main(){
	LL ls,pre,st,ed;
	scanf("%lld",&n);
	for(LL i = 1;i <= n;i ++) scanf("%lld",&s[i].p);
	for(LL i = 1;i <= n;i ++){
		scanf("%lld",&s[i].t);
		sum += s[i].t;
	}
	sort(s + 1,s + 1 + n,cmp);
	ls = 1; st = 0; ed = 0;
	while(1){
		pre = ls;
		while(cmp(s[ls],s[ls + 1]) == 0 && ls < n) ls ++;
		
		for(LL i = pre;i <= ls;i ++) ed += s[i].t;
		for(LL i = pre;i <= ls;i ++){
			l[i] = st + s[i].t;
			r[i] = ed;
		} st = ed;
		ls ++; if(ls > n) break;
	}
	
	for(LL i = 1;i <= n;i ++) lis[i] = i;
	sort(lis + 1,lis + 1 + n,cmpp);
	
	double l = 0.0,r = 1.0,mid;
	for(LL ef = 1;ef <= 40;ef ++){
		mid = (l + r) / 2.0;
		if(chk(mid)) l = mid; // no paradox
		else r = mid;
	}
	printf("%.10lf\n",mid);
	return 0;
}
```

---

## 作者：樱雪喵 (赞：1)

## Description

见题面。

## Solution

首先我们试图找到一个最优策略。这里用临项交换的 trick，设 $i$ 排在 $j$ 前面比反过来更优，有：
$$
p_i\times (1-\frac{c(x+t_i)}{T})+p_j\times (1-\frac{c(x+t_i+t_j)}{T})>p_i\times (1-\frac{c(x+t_i+t_j)}{T})+p_j\times (1-\frac{c(x+t_j)}{T})
$$

化简得到 $\dfrac{p_i}{t_i}> \dfrac{p_j}{t_j}$。

也就是说我们将所有问题按照 $\frac{p_i}{t_i}$ 降序排序，依次完成它们即可使得分最大。

对于给定的 $c$，考虑如何判断是否合法。  
所有 $\frac{p_i}{t_i}$ 相同的点都可以任意互换顺序，我们可以处理出每个问题最早和最晚的完成时间，即每个问题最小和最大的得分。  
题意要求所有最优策略均合法，从小到大枚举 $p_i$，并维护所有 $p_j<p_i$ 的 $j$ 的最大得分。若其大于 $i$ 的最小得分，则不合法。

容易发现这个东西具有单调性，可以二分 $c$ 的值。  
注意判断 $\frac{p_i}{t_i}$ 的值相同时使用乘法判断 / 使用足够小的 $\text{eps}$，否则会像樱雪喵一样炸精度从昨天晚上调到今天下午 /fn

```cpp
#define int long long
const double eps=1e-11;
const int N=1.5e5+5;
int n;
struct node
{
    int p,t;
    double d;
}a[N];
int sum[N],st[N],ed[N],b[N];
il bool cmp(node x,node y) {return x.d>y.d;}
il bool cmp2(int x,int y) {return a[x].p<a[y].p;}
il double get(int id,int t,double c)
{
    return 1.0*a[id].p*(1-1.0*c*t/sum[n]);
}
double mx[N];
il bool check(double c)
{
    int lst=0;
    for(int i=1;i<=n;i++) mx[i]=get(b[i],st[b[i]],c);
    for(int i=2;i<=n;i++) mx[i]=max(mx[i],mx[i-1]);
    for(int i=1;i<=n;i++)
    {
        if(a[b[i]].p!=a[b[i-1]].p) lst=i-1;
        if(get(b[i],ed[b[i]],c)<mx[lst]) return 0;
    }
    return 1;
}
signed main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i].p=read(),b[i]=i;
    for(int i=1;i<=n;i++) a[i].t=read(),a[i].d=1.0*a[i].p/a[i].t;
    sort(a+1,a+n+1,cmp),sort(b+1,b+n+1,cmp2);
    int lst=1;
    for(int i=1;i<=n+1;i++)
    {
        sum[i]=sum[i-1]+a[i].t;
        if(fabs(a[i].d-a[i-1].d)<eps) st[i]=st[i-1];
        else 
        {
            for(int j=lst;j<i;j++) ed[j]=sum[i-1];
            lst=i,st[i]=sum[i-1];
        }
    }
    for(int i=1;i<=n;i++) st[i]+=a[i].t;
    double l=0,r=1;
    while(r-l>1e-6)
    {
        double mid=(l+r)/2;
        if(check(mid)) l=mid;
        else r=mid;
    }
    printf("%.8lf\n",l);
    return 0;
}
```

---

## 作者：tzc_wk (赞：1)

[Codeforces 题目传送门](https://codeforces.com/contest/639/problem/E) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF639E)

~~原来 jxd 作业里也有我会做的题 i 了 i 了~~

首先这种题目的套路就是先考虑对于一个固定的 $c$，怎样求出得分最高的策略，而类似于这样的问题都考虑贪心求解，手玩几组数据就能发现最优方案是将所有题目按照 $\dfrac{p_i}{t_i}$ 从大到小排列。简单证明一下，考虑按照 P4437 排列的套路，假设有两道题 $i,j$ 满足 $\dfrac{p_i}{t_i}>\dfrac{p_j}{t_j}$，那么将 $i$ 放在 $j$ 前面的得分为 $W_1=p_i(1-\dfrac{ct_i}{T})+p_j(1-\dfrac{c(t_i+t_j)}{T})$，将 $i$ 放在 $j$ 后面的得分为 $W_2=p_j(1-\dfrac{ct_j}{T})+p_i(1-\dfrac{c(t_i+t_j)}{T})$，做差可得 $\Delta=W_1-W_2=\dfrac{c(p_it_j-p_jt_i)}{T}$，而由 $\dfrac{p_i}{t_i}>\dfrac{p_j}{t_j}$ 知 $p_it_j-p_jt_i>0$，故 $\Delta>0$，也就是说将 $i$ 放在 $j$ 前面最优，至于 $\dfrac{p_i}{t_i}$ 相同的 $i$，一定有 $\Delta=0$，也就是说 $\dfrac{p_i}{t_i}$ 相同的 $i$ 可以随意交换位置。据说这套路还有个专门名字叫什么 Exchange arguments？不过名字啥的不重要辣，MO 里一般叫它调整法，反正这东西在 OI 和 MO 里都挺有用的就对了（

接下来考虑怎样求答案。首先这个 $c$ 满足单调性，故考虑二分答案，这是题目中疯狂暗示的，再想不到就有些 sb 了罢（~~别打我~~）。考虑检验某个 $c$ 是否合法，我们显然可以确定每道题可能被完成的最靠前的时间，以及每道题可能被完成的最靠后的时间。具体来说，我们将 $(p_i,t_i)$ 按从大到小顺序排序，记 $sum_i$ 为对于排好序的 $t_i$，$\sum\limits_{j=1}^it_j$ 的值。考虑对于一段极长的区间 $[l,r]$ 满足 $\forall x,y\in [l,r]$ 都有 $\dfrac{p_x}{t_x}=\dfrac{p_y}{t_y}$，那么显然对于 $i\in [l,r]$，问题 $i$ 可能被完成的最靠前的时间为 $sum_{l-1}+t_i$，最靠后的时间为 $sum_r$。因此我们只需检验是否 $\exist i,j$ 满足 $p_i>p_j$，完成 $i$ 最少可能的得分 $<$ 完成 $j$ 最大可能的得分，这个可以通过再将所有题目按 $p_i$ 排序并用 two pointers 维护 $mx=\max\limits_{p_j<p_i}p_j(1-\dfrac{c·mxt_j}{T})$，其中 $mxt_j$ 即为上文中所说的问题 $i$ 可能的最靠后的完成时间。并与 $i$ 在可能的最靠前的完成时间的得分比较即可。

时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=1.5e5;
const double EPS=1e-9;
int n;ll T,sum[MAXN+5];
struct data{ll p,t,mn,mx;} a[MAXN+5];
bool cmp1(data lhs,data rhs){return lhs.p*rhs.t>rhs.p*lhs.t;}
bool cmp2(data lhs,data rhs){return lhs.p<rhs.p;}
bool check(double x){
	double mx=0;
	for(int i=1,j=1;i<=n;i++){
		while(a[j].p!=a[i].p) chkmax(mx,1.0*a[j].p*(1-x*a[j].mn/T)),j++;
		if(1.0*a[i].p*(1-x*a[i].mx/T)<mx) return 0;
	} return 1;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i].p);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i].t),T+=a[i].t;
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i].t;
	for(int l=1,r;l<=n;l=r+1){
		r=l;while(r<n&&a[r].p*a[r+1].t==a[r].t*a[r+1].p) r++;
		for(int i=l;i<=r;i++) a[i].mx=sum[r],a[i].mn=sum[l-1]+a[i].t;
	} sort(a+1,a+n+1,cmp2);
	double l=0,r=1.0,x=-114514.1919810;
	while(fabs(r-l)>EPS){
		double mid=(l+r)/2.0;
		if(check(mid)) x=l=mid;
		else r=mid;
	} printf("%.10lf\n",x);
	return 0;
}
```



---

## 作者：大眼仔Happy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF639E)

北文说是一个水题，那我。。。就来水一发题解吧。。。

## Part 1 找出最优顺序

首先我们大胆猜测最优的做题顺序其实和 $c$ 并没有太大关系，并且贪心的思考应该是按照 $\dfrac{p_i}{t_i}$ 降序选取。但是直觉这东西总是不符合的（我又不是 Ramanujan），于是我们考虑证明一下。

考虑相邻的两项 $i$ 和 $j$ 互换，易得只有这两个的分数会发生变化，而其他的题目并没有影响。

1. $i$ 在前，$j$ 在后：$w_i+w_j=p_i(1-\dfrac{c(s+t_i)}{T})+p_j(1-\dfrac{c(s+t_i+t_j)}{T})$

2. $j$ 在前，$i$ 在后：$w_i+w_j=p_i(1-\dfrac{c(s+t_i+t_j)}{T})+p_j(1-\dfrac{c(s+t_j)}{T})$

其中 $s$ 表示做完前面的题目所需要的时间。

通过作差法（$1-2$）就可以得到 $\Delta=\dfrac{c}{T}(p_it_j-p_jt_i)$。假设 1 优于 2 那我们就可以得到 $p_it_j-p_jt_i>0$，进而得到 $\dfrac{p_i}{t_i}>\dfrac{p_j}{t_j}$。这一个东西显然可以推广到全局。于是我们就可以在未确定 $c$ 之前确定一个大概的选取顺序。

~~听说这个技巧叫 `exchange arguments`？[安利 ouuan 大佬的博客](https://ouuan.github.io/post/%E6%B5%85%E8%B0%88%E9%82%BB%E9%A1%B9%E4%BA%A4%E6%8D%A2%E6%8E%92%E5%BA%8F%E7%9A%84%E5%BA%94%E7%94%A8%E4%BB%A5%E5%8F%8A%E9%9C%80%E8%A6%81%E6%B3%A8%E6%84%8F%E7%9A%84%E9%97%AE%E9%A2%98/)~~

## Part 2 二分答案

题目已经给你很大暗示让你二分答案了，事实上这是因为答案具有单调性，那我们只需要写一个 `check()` 看看是否合法即可。

由于 $\dfrac{p}{t}$ 相同的可以随意调换，而题目要求对于**任意的**最优方案都需要满足那个性质。所以一开始是想天真的按照 $p$ 作为第二关键之降序排序，结果因为写法问题死活过不了。

其实不然，对于每一道题目，我们只需要求出最早的完成时间 $t_{\min}(i)$ 和最晚的完成时间 $t_{\max}(i)$，进而得到最多可以得到的分数 ${\rm sc} _ {\max}(i)$ 和最少可以得到的分数 ${\rm sc} _ {\min}(i)$。考虑若 $p_i>p_j$，且 ${\rm sc} _ {\min}(i)<{\rm sc} _ {\max}(j)$，则当前二分的 $c$ 不合法。

对 $p$ 按升序排序之后显然可以用 $O(n)$ 完成。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
const int N=2e5+5;
const db eps=1e-12,inf=1e18;
ll inline read()
{
	ll num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
int n;ll T;db l,r=1.0;
struct node{ll p,t,tmn,tmx;}d[N];
db sc(ll p,db c,ll x){return p*(1-c*x/T);}
bool CmpAvg(node A,node B){return A.p*B.t>B.p*A.t;}
bool CmpRnk(node A,node B){return A.p<B.p;}
bool check(db c)
{
	int pos=n;db s=-inf;
	for(int i=1;i<=n;i++)
	{
		while(d[pos].p!=d[i].p)s=max(s,sc(d[pos].p,c,d[pos].tmn)),pos--;
		if(s-sc(d[i].p,c,d[i].tmx)>-eps)return false;
	}
	return true;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)d[i].p=read();
	for(int i=1;i<=n;i++)d[i].t=read();
	sort(d+1,d+1+n,CmpAvg);
	for(int L=1,R;L<=n;L=R+1)
	{
		R=L;while(R<n&&d[R+1].p*d[L].t==d[L].p*d[R+1].t)R++;
		for(int i=L;i<=R;i++)d[i].tmn=T+d[i].t;
		for(int i=L;i<=R;i++)T+=d[i].t;
		for(int i=L;i<=R;i++)d[i].tmx=T;
	}
	sort(d+1,d+1+n,CmpRnk);
	while(r-l>eps)
	{
		db mid=(l+r)/2.0;
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%.12lf",l);
	return 0;
}
```

---

## 作者：mi_Y13c (赞：0)

### 算法

#### (贪心、二分)  $O(n \log n)$ 

第 $x$ 分钟结束时完成第 $i$ 题会使你获得  $p_{i}\left(1-\frac{c x}{T}\right)$   的分数。

显然我们要分析一下在给定 $c$ 之后，最优策略如何确定。

如果要先做第 $i$ 题再做第 $j$ 题比反过来更优，那么就需要满足：

$p_{i}\left(1-\frac{c\left(x_{0}+t_{i}\right)}{T}\right)+p_{j}\left(1-\frac{c\left(x_{0}+t_{i}+t_{j}\right)}{T}\right)>p_{j}\left(1-\frac{c\left(x_{0}+t_{j}\right)}{T}\right)+p_{i}\left(1-\frac{c\left(x_{0}+t_{i}+t\right)}{T}\right)$

化简得到：$p_{j} t_{i}<p_{i} t_{j}$。

也即 $\frac{t_{i}}{p_{i}}<\frac{t_{j}}{p_{j}}$。

按照 $\frac{t_{i}}{p_{i}}<\frac{t_{j}}{p_{j}}$  排序之后的顺序做题。

但是注意如果 $\frac{t_{i}}{p_{i}}=\frac{t_{j}}{p_{j}}$，那么 $i$  和 $j$ 谁先谁后都是最优解， 但是对于他们的实际得分是不一样的， 越早做分越高， 因此还需特判一下。

题目要求的是符合条件的最大的 $c$。

可以发现答案满足单调性, 所以我们可以二分 $c$。

### 代码
```
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 1; i <= (n); ++i)
using namespace std;
using ll = long long;
struct node {
    ll p, t, sum, mx, mn;
} a[150005];

bool cmp(node x, node y) {
    return x.p*y.t > y.p*x.t;
}
bool cmp2(node x, node y) {
    return x.p < y.p;
}

int main() {
    cin.tie(nullptr) -> sync_with_stdio(false);
    int n;
    cin >> n;
    rep(i, n) cin >> a[i].p;
    ll T = 0;
    rep(i, n) {
        cin >> a[i].t;
        T += a[i].t;
    }
    sort(a+1, a+n+1, cmp);
    rep(i, n) a[i].sum = a[i-1].sum + a[i].t;
    int i = 1;
    while (i <= n) {
        int j = i;
        while (j <= n and !cmp(a[i], a[j]) and !cmp(a[j], a[i])) ++j;
        for (int k = i; k < j; ++k) {
            a[k].mn = a[i-1].sum + a[k].t;
            a[k].mx = a[j-1].sum;

        }
        i = j;
    }
    sort(a+1, a+n+1, cmp2);
    double ac = 0, wa = 1;
    while (fabs(ac-wa) > 1e-10) {
        double wj = (ac+wa)/2;
        auto ok = [&]{
            double mx = 0, last_mx = 0; 
            rep(i, n) {
                if (a[i].p != a[i-1].p) last_mx = mx;
                if ((1-wj*a[i].mx/T)*a[i].p < last_mx) {
                    return false;
                }
                mx = max(mx, (1-wj*a[i].mn/T)*a[i].p);

            }
            return true;
        }();

        (ok ? ac : wa) = wj;
    }

    printf("%.10f\n", ac);
    return 0;

}

```

---

## 作者：关怀他人 (赞：0)

### CF 639E
#### Solution
首先如果我们确定了一个$c$，提出所有常数项之后发现就是要使得$\sum p_ix_i$最小，也就是说一个$t_i$会产生$t_i\times \sum_{k=i+1}^np_i$的贡献，考虑$i$和$i+1$，如果$i$在前则贡献为
$$
t_i\times \sum_{k=i+1}^np_k+t_{i+1}\times \sum_{k=i+2}^np_k
$$如果$i+1$在前则贡献为
$$
t_{i+1}\times \sum_{k=i+1}^np_k+t_{i}\times \sum_{k=i+2}^np_k
$$上面两式做差可得$i$在$i+1$前面的条件是$t_i\times p_{i+1}<t_{i+1}\times p_i$，直接按照$\frac{t_i}{p_i}$排递增序即可。

然后要对于任意最优序列都合法，那么某段连续的$\frac{t_i}{p_i}$相同的可以随便排列，对于每一段算出它最大和最小的$x_i$就行了。对于某个$p_i>p_j$合法的条件是$p_i(1−c\times \frac{xi}{T})\leq p_j(1−c\times \frac{xj}{T})$

最后考虑二分答案，判断当前二分的$c$是否合法即可，具体可以按照$p$排序，对于一段相同的$p$，判断是否满足条件即可。
#### Code
```cpp
const int INF = 0x3f3f3f3f;
const ll llINF = 1e18;
const int MAXN = 2e5 + 5;

int n;
ll T;

struct Node{
    int p,t;
    ll x,max,min;
} a[MAXN];

bool cmp1(const Node &x,const Node &y){
    return 1ll * x.t * y.p < 1ll * y.t * x.p;
}

bool cmp2(const Node &x,const Node &y){
    return x.p < y.p;
}

bool Check(long double c){
    long double curMax = -INF,preMax = -INF;
    for(int i = 1;i <= n;i++){
        if(a[i].p != a[i - 1].p)
            preMax = curMax;
        if((1.0 - c * a[i].max / T) * a[i].p < preMax)
            return false;
        checkMax(curMax,(1.0 - c * a[i].min / T) * a[i].p);
    }
    return true;
}

int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++)
        scanf("%d",&a[i].p);
    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i].t);
        T += a[i].t;
    }
    sort(a + 1,a + 1 + n,cmp1);
    for(int i = 1;i <= n;i++)
        a[i].x = a[i - 1].x + a[i].t;
    for(int i = 1,j;i <= n;i = j){
        j = i;
        while(j <= n && 1ll * a[i].p * a[j].t == 1ll * a[j].p * a[i].t) j += 1;
        for(int k = i;k < j;k++){
            a[k].min = a[i - 1].x + a[k].t;
            a[k].max = a[j - 1].x;
        }
    }
    sort(a + 1,a + 1 + n,cmp2);
    long double l = 0,r = 1,res = 0;
    for(int i = 1;i <= 40;i++){
        long double mid = (l + r) / 2.0;
        if(Check(mid)){
            res = mid;
            l = mid;
        }else
            r = mid;
    }
    printf("%.7Lf\n",res);
    return 0;
}
```

---

