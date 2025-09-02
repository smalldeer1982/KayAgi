# [ABC342F] Black Jack

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc342/tasks/abc342_f

あなたとディーラーでゲームをします。 ゲームは $ 1 $ 以上 $ D $ 以下の整数が等確率で出る $ D $ 面サイコロ、$ 0 $ で初期化された変数 $ x,y $ を用いて以下のように行われます。

- あなたはサイコロを振り、出た目を $ x $ に加算する操作を好きな回数行える。ここで、あなたは操作を行うたびに次の操作を行うかを選択できる。
- その後、ディーラーは $ y\ <\ L $ を満たす限り、サイコロを振り、出た目を $ y $ に加算する操作を繰り返す。
- $ x\ >\ N $ の場合あなたの負けである。そうでない場合、$ y\ >\ N $ または $ x\ >\ y $ のいずれかを満たす場合あなたの勝ちで、どちらも満たさない場合あなたの負けである。
 
あなたが勝率を最大化するように適切に行動する際、勝率を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\leq\ L\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ D\ \leq\ N $
 
### Sample Explanation 1

$ x $ が $ 2 $ 以下の場合操作を続けるという戦略が最適であることが証明できます。

## 样例 #1

### 输入

```
3 2 2```

### 输出

```
0.468750000000000```

## 样例 #2

### 输入

```
200000 200000 200000```

### 输出

```
0.999986408692793```

# 题解

## 作者：Otue (赞：10)

update at 2024/2/26：修改一处笔误。

---

定义 $dp_i$ 表示 $x$ 当前为 $i$ 时获胜的概率。

有两种选择，投骰子，停止。则 $dp_i=\max\{\dfrac{\sum_{j=i+1}^{i+D}dp_j}{D},\text{slove(i)}\}$。其中 $\text{slove(i)}$ 表示 $x$ 在 $i$ 的时候停止操作，$y$ 接下来操作一波后，$x$ 能够获胜的概率。 

令 $g_i$ 表示 $y$ 最后为 $i$ 的概率，$sum_i$ 表示 $g_i$ 的前缀和。那么 $\text{slove(x)}$ 有两种情况能赢：

* 如果 $y$ 越界了 $y>N$，则获胜，概率为 $1-sum_N$。
* 如果 $y<x$，则获胜，概率为 $sum_{x-1}$。


那么 $g$ 数组如何计算？初始时 $g_0=1$，代码说可能更直接：

```c++
g[0] = 1.0;
for (int i = 0; i <= MAXN; i++) {
	for (int j = i + 1; j <= i + D; j++) g[j] += g[i] / D;
	g[i] = 0;
} 
```

直接这样做会超时，可以用线段树维护，单点查询，区间修改。

### 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 4e5 + 5;

int n, l, d;
double g[N], dp[N], sum[N];

struct fenwick {
	double c[N][2];
	void mo(int x, double v) {
		x += 2;
		for (int i = x; i <= N - 5; i += i & -i) {
			c[i][0] += v;
			c[i][1] += x * v;
		}
	}
	void modify(int l, int r, double v) {
		mo(l, v);
		mo(r + 1, -v);
	}
	double get_sum(int op, int x) {
		x += 2;
		double res = 0.0;
		for (int i = x; i; i -= i & -i) res += c[i][op];
		return res;
	}
	double query(int l, int r) {
		double t1 = get_sum(0, l - 1) * 1.0 * (l + 2) - get_sum(1, l - 1);
		double t2 = get_sum(0, r) * (1.0 * r + 3) - get_sum(1, r);
		return t2 - t1;
	}
}tr;

double slove(int x) {
	if (x > n) return 0.0;
	double res = 1 - g[n];
	if (x >= 1) res += g[x - 1];
	return res;
}

signed main() {
	cin >> n >> l >> d;
	g[0] = 1.0; tr.modify(0, 0, 1.0);
	for (int i = 0; i <= N - 5; i++) {
		double t = tr.query(i, i); g[i] = t;
		if (i < l) {
			tr.modify(i + 1, i + d, t / d);
			g[i] = 0.0;
		}
	}
//	for (int i = 0; i <= 10; i++) cout << g[i] << ' ';
//	puts("");
	for (int i = 1; i <= N - 5; i++) g[i] += g[i - 1];
	for (int i = N - 5; i >= 0; i--) {
		if (i > n) dp[i] = 0.0;
		else dp[i] = max((sum[i + 1] - sum[i + d + 1]) / d, slove(i));
		sum[i] = sum[i + 1] + dp[i];
	}
	printf("%.10lf", dp[0]);
}
```
祝大家学习愉快！

---

## 作者：WaterSun (赞：6)

[更好的阅读体验](https://watersun.top/%5B%E9%A2%98%E8%A7%A3%5DAT_abc342_f%20[ABC342F]%20Black%20Jack)

# 思路

发现自己与庄家的操作是完全独立的，所以考虑分别计算它们。

首先考虑自己的情况，定义 $dp_i$ 表示掷出骰子的和为 $i$ 获胜的概率，并记 $f(i)$ 表示 $x = i$ 时就不掷的获胜概率。

对于每一步我们要么掷骰子（并且掷出的值等概率的在 $1 \sim D$ 中），要么直接结束。两种情况结合容易得出状态转移方程：

$$
dp_i = \max(\frac{\sum_{j = i + 1}^{i + D}{dp_j}}{D},f(i))
$$

于是现在的问题就转化为了如何计算 $f(i)$。根据题目，获胜有两种情况，$y > n$ 或者 $x > y$。现在 $x,n$ 都已知，关键点就在于 $y$。

定义 $g_i$ 表示庄家最终掷出结果为 $i$ 的概率。那么 $y > n$ 的情况就是 $1 - \sum_{i = 1}^{n}{g_i}$；$x > y$ 的情况就是 $\sum_{i = 1}^{x - 1}{g_i}$。显然可以前缀和优化一下。

考虑如何求 $g$。发现 $g_i$ 会等概率地贡献给 $g_{(i + 1) \sim (i + D)}$，因此每次：

$$
\forall j \in [i + 1,i + D],g_j \leftarrow g_j + \frac{g_i}{D}
$$

但是这样转移是 $\Theta(LD)$ 的，同时注意到转移本质上是一个区间修改，单点查询，可以使用树状数组维护。

同时，根据题目，当 $y < L$ 时是还会继续掷骰子的，因此需要将 $g_{1 \sim (L - 1)}$ 在转移完成后清零。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define double long double

using namespace std;

const int N = 4e5 + 10;
int n,l,d;
double g[N],dp[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct BIT{
    #define lowbit(x) (x & -x)

    double tr[N];

    inline void modify(int x,double k){
        for (re int i = x;i <= 4e5;i += lowbit(i)) tr[i] += k;
    }

    inline double query(int x){
        double res = 0.0;
        for (re int i = x;i;i -= lowbit(i)) res += tr[i];
        return res;
    }

    #undef lowbit
}T;

inline double f(int x){
    if (x > n) return 0.0;
    double res = 1.0 - g[n];
    if (x) res += g[x - 1];
    return res;
}

int main(){
    g[0] = 1.0;
    n = read(),l = read(),d = read();
    for (re int i = 0;i <= 4e5;i++){
        if (i) g[i] = T.query(i);
        if (i < l){
            T.modify(i + 1,g[i] / d),T.modify(i + d + 1,-g[i] / d);
            g[i] = 0.0;
        }
    }
    for (re int i = 1;i <= 4e5;i++) g[i] += g[i - 1];
    double sum = 0.0;
    for (re int i = 4e5;~i;i--){
        if (i > n) dp[i] = 0.0;
        else dp[i] = max(sum / d,f(i));
        sum += dp[i];
        if (i + d <= 4e5) sum -= dp[i + d];
    }
    printf("%.15Lf",dp[0]);
    return 0;
}
```

---

## 作者：cancan123456 (赞：4)

首先发现 dealer 的操作是固定的，那么我们设计一个 DP，我们设 $g_i$ 为 dealer 操作到 $i$ 的概率，容易写出边界与转移：

$$g_0=1$$

$$g_{i+j}\gets g_{i+j}+\frac{g_i}d,i<l,i+j<n$$

发现朴素实现是 $O(ld)$ 的，非常不牛，但是对于每个 $g_i$，这个操作等价于 $[i+1,i+d]$ 的区间加 $\dfrac{g_i}d$，容易使用线段树解决。

> PS：赛后发现这个地方前缀和也是 $O(n)$ 的，是我傻了。

然后我们对 $<l$ 的 $i$ 将 $g_i$ 赋值为 $0$ 并求后缀和，现在 $g_i$ 代表 dealer 掷出 $\ge i$ 的点数的概率。

现在考虑普通的博弈论 DP 套路，我们设 $f_i$ 为当前 $x=i$ 时的最大胜率，并倒着转移，边界显然是 $\forall i>n,f_i=0$，考虑 $f_i$ 有两种选择：见好就收或者再掷一次，显然可以写出这个方程：

$$f_i=\max\left(1-g_i,\frac{\sum_{j=1}^df_{i+j}}d\right)$$

发现朴素实现还是 $O(n^2)$ 的，可以使用后缀和优化到 $O(n)$。

时间复杂度为 $O(n\log n)$（或 $O(n)$），可以通过此题。

下面是我的赛事代码：

```cpp
#include <cstdio>
using namespace std;
const int N = 200005;
double f[N], g[N], suf[N * 2];
int n, l, d;
double max(double a, double b) {
	return a > b ? a : b;
}
int min(int a, int b) {
	return a < b ? a : b;
}
struct Node {
	int l, r;
	double w;
} node[4 * N];
void push_down(int p) {
	node[2 * p].w += node[p].w;
	node[2 * p + 1].w += node[p].w;
	node[p].w = 0;
}
void build(int p, int l, int r) {
	node[p].l = l;
	node[p].r = r;
	node[p].w = 0.0;
	if (l != r) {
		int mid = (l + r) / 2;
		build(2 * p, l, mid);
		build(2 * p + 1, mid + 1, r);
	}
}
void add(int p, int l, int r, double w) {
	if (l <= node[p].l && node[p].r <= r) {
		node[p].w += w;
	} else {
		push_down(p);
		int mid = (node[p].l + node[p].r) / 2;
		if (l <= mid) {
			add(2 * p, l, r, w);
		}
		if (mid + 1 <= r) {
			add(2 * p + 1, l, r, w);
		}
	}
}
double query(int p, int pos) {
	if (node[p].l == node[p].r) {
		return node[p].w;
	} else {
		push_down(p);
		int mid = (node[p].l + node[p].r) / 2;
		if (pos <= mid) {
			return query(2 * p, pos);
		} else {
			return query(2 * p + 1, pos);
		}
	}
}
int main() {
	scanf("%d %d %d", &n, &l, &d);
	build(1, 0, n);
	add(1, 0, 0, 1.0);
	for (int i = 0; i < l; i++) {
		add(1, i + 1, i + d, query(1, i) / d);
	}
	for (int i = 0; i <= n; i++) {
		g[i] = query(1, i);
	}
	for (int i = min(l + d, n); i >= 0; i--) {
		if (i < l) {
			g[i] = 0.0;
		}
		g[i] += g[i + 1];
	}
	for (int i = n; i >= 0; i--) {
		f[i] = max((suf[i + 1] - suf[i + 1 + d]) / d, 1.0 - g[i]);
		suf[i] = suf[i + 1] + f[i];
	}
	printf("%.15lf", f[0]);
	return 0;
}
```

---

## 作者：EmptyAlien (赞：4)

## 题意

- 你在跟一个叫庄稼的人玩游戏。

- 有一个有 $d$ 面的色子，它会等概率地摇出 $1$ 到 $d$ 的整数。

- 你先摇，每一次都把摇出来的结果加到 $x$ 上去，你可以选择摇几次。

- 庄稼后摇，只要它摇出来的点数 $< l$，就会继续摇，同样地，它会把每次摇出来的数加到 $y$ 上。

- 如果 $x > n$ 或 $x \le y \le n$ 你就输了，否则你就赢了。

- 求你获胜的概率最大是多少。

## 思想

因为庄稼的策略是固定的，所以我们计算 $g'(i)$ 即庄稼最后摇到了 $x$ 的点数的概率

注意到每次 $i < l$ 再摇时会把概率平均分到 $i + 1$ 到 $i + d$。

我们就从小往大向后贡献。

但是这样会 TLE。

区间加和单点查询。

我们用差分树状数组来维护它。

我们为了计算小于等于的贡献就直接前缀和一下得到 $g(i)$。

我们计算出 $g(i)$ 了之后开始计算答案。

我们先计算在 $i$ 处我们停止摇色子的获胜概率。

若 $i > l$ 则概率为 $g(x - 1) + 1 - g(n)$。

若 $i < l$ 则概率为 $1 - g(n)$。

我们令这个函数为 $calc(i)$。

然后我们令 $f(i)$ 为我们从 $x=i$ 开始摇色子最多的获胜概率。

如果继续摇答案就是 $\dfrac{\sum^d_{j=1}f(i + j)}{d}$。

停下答案就是 $calc(i)$。

所以:

$$
f_i=\max\left\{calc(i), \dfrac{\sum^d_{j=1}f(i + j)}{d}\right\}
$$

我们从后往前扫描，用 $sum$ 来维护 $\sum^d_{j=1}f(i + j)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 4e5 + 5;

int lowbit(int x) {
    return x & -x;
}

struct Fenwick {
    double c[MAXN];

    void upd(int l, int r, double x) {
        for (int i = l + 1; i < MAXN; i += lowbit(i))
            c[i] += x;
        for (int i = r + 2; i < MAXN; i += lowbit(i))
            c[i] -= x;
    }

    double ask(int x) {
        double ans = 0;
        for (int i = x + 1; i > 0; i -= lowbit(i))
            ans += c[i];
        return ans;
    }
} fenwick;

int n, l, d;
double f[MAXN], g[MAXN];

double calc(int x) {
    if (x > n)
        return 0;
    double ans = 1 - g[n];
    if (x > l)
        ans += g[x - 1];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> l >> d;
    fenwick.upd(0, 0, 1);
    for (int i = 0; i <= 4e5; i++) {
        g[i] = fenwick.ask(i);
        if (i < l) {
            fenwick.upd(i + 1, i + d, g[i] / d);
            g[i] = 0;
        }
    }
    for (int i = 1; i <= 4e5; i++)
        g[i] += g[i - 1];

    double sum = 0;
    for (int i = 4e5; i >= 0; i--) {
        if (i > n)
            f[i] = 0;
        else
            f[i] = max(sum / d, calc(i));
        sum += f[i];
        if (i + d <= 4e5)
            sum -= f[i + d];
    }
    cout << fixed << setprecision(15) << f[0] << endl;

    return 0;
}
```

---

## 作者：035966_L3 (赞：3)

根据样例，我们的策略与 Dealer 类似，要找一个 $L'$。

显然 $L'\le 2\times 10^5$，结合线段树枚举即可：

设 $a_i$ 表示当前 $L'$ 下最终得到 $i$ 点的概率。

令当前 $L'=c$，当 $L' \gets c+1$ 时，$a_c$ 需要转移：在此基础上，再掷一次骰子，等概率地加上 $[1,D]$ 点，即将 $a_c$ 的值平分给 $a_{[c+1,c+D]}$。这是区间加操作，用线段树维护即可。

**AC Code：**

```cpp
#include<bits/stdc++.h>
using namespace std;
// 线段树，记得开 long double！！！
const int PTA=524288,PTD=19;
long double a[3300012],all[3300012];
int ll[3300012],rr[3300012],sz[3300012];
void trinit()
{
	for(int i=PTA,j=1;j<=PTA;i++,j++)
		ll[i]=rr[i]=j,sz[i]=1,a[i]=all[i]=0;
	for(int i=PTA-1;i>=1;i--)
		ll[i]=ll[i+i],rr[i]=rr[i+i+1],sz[i]=sz[i+i]+sz[i+i+1],a[i]=all[i]=0;
}
void go(int i)
{
	long double c=a[i];a[i]=0;
	a[i+i]+=c,all[i+i]+=c*sz[i+i];
	a[i+i+1]+=c,all[i+i+1]+=c*sz[i+i+1];
}
void add(int l,int r,long double v,int b)
{
	if(l==ll[b]&&r==rr[b]) {a[b]+=v,all[b]+=sz[b]*v;return;}
	int lm=rr[b+b],rm=ll[b+b+1];go(b);
	if(r<=lm) {add(l,r,v,b+b);}
	else if(l>=rm) {add(l,r,v,b+b+1);}
	else 
	{
	    add(l,lm,v,b+b);
	    add(rm,r,v,b+b+1);
	}
	all[b]=all[b+b]+all[b+b+1];
}
long double fd(int l,int r,int b)
{
	if(l==ll[b]&&r==rr[b]) return all[b];
	int lm=rr[b+b],rm=ll[b+b+1];go(b);
	if(r<=lm) return fd(l,r,b+b);
	if(l>=rm) return fd(l,r,b+b+1);
	return fd(l,lm,b+b)+fd(rm,r,b+b+1);
}
long double x[500012],xx[500012],xxx[500012],xxxx[500012];
int main()
{
    int n,l,d;
    cin>>n>>l>>d;
    // 算出 Dealer 最终点数的分布
    trinit();
    for(int i=1;i<=d;i++)
    	add(i,i,1.0/d,1); // 第一次掷骰子
    for(int i=1;i<=l-1;i++) // 转移，L = i -> L = i + 1
    {
    	long double res=fd(i,i,1);
    	add(i+1,i+d,res/d,1); // 将 i 的概率平分给后面 D 个点数
	}
	for(int i=l;i<=500000;i++)
		x[i]=fd(i,i,1);
    // 最终掷出 i 点的概率
	for(int i=1;i<=500000;i++)
		xx[i]=xx[i-1]+x[i];
	for(int i=1;i<=n;i++)
		xxx[i]=1-(xx[n]-xx[i-1]);
    // 已方掷出 i 点时战胜 Dealer 的概率
	for(int i=1;i<=500000;i++)
		xxxx[i]=xxxx[i-1]+xxx[i];
    trinit();
	long double ans=0,mans=0;
    for(int i=1;i<=d;i++)
    	add(i,i,1.0/d,1),ans+=1.0/d*xxx[i];
    mans=ans;
    for(int i=1;i<=n;i++) // 对已方枚举 L'
    {
    	long double res=fd(i,i,1);
    	ans-=res*xxx[i];
    	add(i+1,i+d,res/d,1);
    	ans+=(xxxx[i+d]-xxxx[i])*res/d;
    	mans=max(ans,mans);
	}
	cout<<fixed<<setprecision(50)<<mans;
    return 0;
}
```

---

## 作者：Neil_Qian (赞：2)

# [ABC342F] Black Jack 题解

## 题目描述

你和一个人玩游戏。给出 $n,L,D$。一个有 $D$ 个面的骰子，每次你可以选择是否继续，如果继续则将结果加在 $x$ 上。另一个人必须一直掷骰子，直到他的和 $y\ge L$。如果 $x>n$ 或者 $x\le y$ 那么你输了，若 $x>y$ 或 $y>n$ 你赢了。求你赢的概率。$n,L,D\le 2\times 10^5$。 

## 解决方案

赛场上就差这题了。好像在一本书上看到过，忘了。

不难发现另一个人的操作可以视为一个程序，与你的操作无关，不妨先求出 $g_i$ 表示另一个人最终 $y=i$ 的概率。这是很好求的。为了方便，先做一个前缀和。

然后考虑 $x=i$ 时你的胜率，首先当另一个人 $y>n$ 时的概率为 $g_{n+1}$，然后如果 $x>y$ 那么概率为 $g_{x-1}$。记这个值为 $t$，在考虑继续掷骰子的概率，得到递推式 $f_i=\max(t,\frac{f_{i+1}+f_{i+2}+\dots+f_{i+D}}D)$。

时间复杂度为 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;const int N=4e5+2;
int n,m=4e5,L,D;double f[N],d[N],g[N],sum,temp;
int main(){
	scanf("%d%d%d",&n,&L,&D),g[0]=1,d[1]=1.0/D,d[D+1]-=1.0/D;
	for(int i=1;i<=m;i++){
		d[i]+=d[i-1],g[i]=d[i];
		if(i<L)d[i+1]+=g[i]/D,d[i+D+1]-=g[i]/D,g[i]=0;
		else g[i]+=g[i-1];
	}
	for(int i=m;i>=0;i--){
		if(i<=n){
			temp=1-g[n];
			if(i>L)temp+=g[i-1];
		}
		f[i]=max(sum/D,temp),sum+=f[i];
		if(i+D<=m)sum-=f[i+D];
	}
	return printf("%.15f\n",f[0]),0;
}
```

---

## 作者：FReQuenter (赞：2)

观察 $x$ 和 $y$。发现 $y$ 可以独立计算没有影响。所以先把对应的所有 $0\le i<l+d$ 的 $y$ 值的概率算出来。定义其为 $f1$。显然有：

$$f1_{i+1},f1_{i+2},\cdots,f1_{i+d}\gets f1_{i+1},f1_{i+2},\cdots,f1_{i+d}+\frac{f1_{i}}{d}$$

因为 $y>n$ 或 $x>y$ 时获胜，我们可以得到 $x=1,2,\cdots,n$ 时的获胜概率，定义为 $f2$：

$$f2_i=f1_n+f1_{n+1}+\cdots+f1_{n+d}+f1_l+f1_{l+1}+\cdots+f1_{i-1}$$

两行分别对应两种获胜条件。

接下来就可以计算掷色子后 $x=i$ 时的获胜概率了，记为 $f3$：

$$f3_i=\max\{f2_i,\frac{1}{d}\sum_{j=i+1}^{i+d}f3_{j}\}$$

分别对应当前结束不继续掷色子和继续掷色子。

显然 $f3_0$ 就是答案。

以上三个都是顺推，倒推、区间查询单点修改，单点修改区间查询的形式，使用滑动窗口维护转移即可。时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define MAXN 200005
using namespace std;
int n,l,d;
double sum,rst,f1[MAXN<<1],f2[MAXN<<1],f3[MAXN<<1];
signed main(){
	cin>>n>>l>>d;
	f1[0]=1;
	for(int i=0;i<n+d;i++){
		if(i<l) sum+=f1[i]/d;
		if(i>=d&&i<l+d) sum-=f1[i-d]/d;
		f1[i+1]=sum;
	}
	sum=0;
	for(int i=n+1;i<=n+d;i++) rst+=f1[i];
	for(int i=0;i<=n;i++){
		f2[i]=sum+rst;
		if(i>=l) sum+=f1[i];
	}
	sum=0;
	for(int i=n;i>=0;i--){
		sum+=f3[i+1]-f3[i+d+1];
		f3[i]=max(f2[i],sum/d);
	}
	cout<<fixed<<setprecision(10)<<f3[0];
}
```

---

## 作者：ReTF (赞：2)

设 $f_i$ 为在当前局面为 $y=i$ 时的概率。

初始状态为 $f_0=1$，然后对于 $c=0,1,\dots,L-1$，依次按照如下方式模拟题目过程递推：

$$\forall j\in[1,D],f_{c+j}\leftarrow f_{c+j}+\dfrac{f_c}{D}$$

递推结束后，对于点 $i$，我们得到 $x=i$ 时停止的胜率 $\displaystyle w_i=1-\sum_j^n f_j$。

容易发现先手的最优决策一定为“当掷到的点数 $> k$ 时立即停止”。如果最优决策不满足这个条件则可以通过调整得到另一组满足这个条件的更加不劣的决策。

考虑枚举这个 $k$。通过和上面完全一样的递推（只不过 $c$ 的上界为 $n$）可以得到当前局面为 $x=i$ 时的概率 $g_i$。递推完 $c=k$ 之后，我们要求的答案就是 $\displaystyle \sum_{k+1}^{n}g_iw_i$。这可以使用线段树很方便地维护。

[代码](https://atcoder.jp/contests/abc342/submissions/50606621)

---

## 作者：Symbolize (赞：1)

# $\tt{Solution}$
这个题看着眼花缭乱实际上我们可以分两步来解决。

定义 $f_i$ 表示当前为 $i$，继续操作（也可以在现在停下）的获胜概率。很显然我们需要倒序处理，每个 $i$ 可以分两种情况，第一种情况就是继续摇骰子，这个时候会有 $D$ 种等概率情况，也就是 $\sum\limits_{j=1}^{D}\frac{f_{i+j}}{D}$，为了防止精度出现影响，把 $\frac{1}{D}$ 提出来得到 $\frac{\sum\limits_{j=1}^{D}f_{i+j}}{D}$，可以用类似前缀和的方法累加离当前答案最近的 $D$ 个的和 $sum$，换句话说，每次 $sum\gets sum+f_i-f_{i+D}$，减法的前提是不越界。

另一种情况就是马上停下来，这个时候我们定义函数 $get(x)$ 表示在 $x$ 时停下的获胜概率。令 $g_i$ 为对方摇到 $i$ 的概率。

获胜的方法有两种：

1. $y>n$，此时获胜概率为 $1-\sum\limits_{i=0}^{n}g_i$，没有限制；
2. $y<x\leq n$，此时获胜概率为 $\sum\limits_{i=0}^{x-1}g_i$，限制为 $x>0$。

两者加起来就对了，特别的，若 $x>n$，则函数值为 $0$。

以上就是第一个 DP。

接下来思考如何求出 $g$ 数组。

不难列出暴力式子：

$$g_i=\sum\limits_{j=i-D}^{i-1} g_j$$

这就和上面的 $f_i$ 数组一样，直接前缀和优化即可。

最后放出代码。

```cpp
/*
	Luogu name: Symbolize
	Luogu uid: 672793
*/
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,x,y,z) for(register int i=x[y];~i;i=z[i])
#define rep4(i,x) for(auto i:x)
#define debug() puts("----------")
const int N=4e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
using namespace std;
int n,L,D;
double f[N],g[N],s,sum; 
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
double get(int x)
{
	if(x>n) return 0;
	return 1-g[n]+(x>0?g[x-1]:0);
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();
	L=read();
	D=read();
	s=g[0]=1;
	rep1(i,1,N-1)
	{
		g[i]+=s/D;
		if(i-D>=0&&i-D<L) s-=g[i-D];
		if(i<L) s+=g[i];
	}
	rep1(i,0,L-1) g[i]=0;
	rep1(i,1,N-1) g[i]+=g[i-1];
	rep2(i,N-1,0)
	{
		if(i>n) f[i]=0;
		else f[i]=max(sum/D,get(i));
		sum+=f[i];
		if(i+D<=N-1) sum-=f[i+D];
	}
	printf("%.15lf\n",f[0]);
	return 0;
}
```

---

## 作者：happybob (赞：1)

注意到对方的操作与我们选择的无关。故可以直接 DP 求出对方最终点数为 $i$ 的概率。这部分可以前缀和优化。

现在考虑我们怎么做能最优化概率。逆着 DP，$f_i$ 表示假如初始点数为 $i$ 的最优概率。$f_0$ 即为所求。你发现转移分两部分，一部分是，我在 $i$ 不动，另一部分是我扔出骰子。第一部分直接计算概率，第二部分通过后缀和优化。复杂度线性。

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long

const int N = 5e5 + 5, MOD = 1e9 + 7, HSMOD = 1610612741, HSMOD2 = 998244353; // Remember to change

int n, l, d;
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

long long qpow(long long a, long long b)
{
	long long res = 1ll, base = a;
	while (b)
	{
		if (b & 1ll) res = res * base % MOD;
		base = base * base % MOD;
		b >>= 1ll;
	}
	return res;
}

bool isprime(int x)
{
	if (x == 1) return 0;
	for (int i = 2; 1ll * i * i <= x; i++) if (x % i == 0) return 0;
	return 1;
}

namespace FastIo
{
	#define QUICKCIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
	int read()
	{
		char ch = getchar();
		int x = 0, f = 1;
		while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
		while (ch == '-')
		{
			f = -f;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9')
		{
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template<class T>
	void write(T x)
	{
		if (x < 0)
		{
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	template<class T>
	void writeln(T x)
	{
		write(x);
		putchar('\n');
	}
}

template<typename T>
class Bit
{
public:
	T lowbit(T x)
	{
		return x & -x;
	}
	T tr[N];
	void add(T x, T y)
	{
		while (x < N)
		{
			tr[x] += y;
			x += lowbit(x);
		}
	}
	T query(T x)
	{
		T sum = 0;
		while (x)
		{
			sum += tr[x];
			x -= lowbit(x);
		}
		return sum;
	}
};

double f[N];
double sum[N];
double f2[N];
double sf[N];

int main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin>>n>>l>>d;
	f[0]=1;
	sum[0]=1;
	double avg=1.0/d;
	for(int i=1;i<N;i++)
	{
		if(i<l)
		{
			int L=max(0,i-d),R=i-1;
			f[i]=avg*(sum[R]-(L==0?0:sum[L-1]));
		}
		else
		{
			int L=max(0,i-d),R=l-1;
			if(L<=R)
			{
				f[i]=avg*(sum[R]-(L==0?0:sum[L-1]));
			}
		}
		sum[i]=sum[i-1]+f[i];
	}
	for(int i=0;i<N;i++)
	{
		if(i<l)
		{
			f[i]=0;
		}
		sum[i]=(i?sum[i-1]:0)+f[i];
	}
	double sumgn=0;
	for(int i=n+1;i<N;i++) sumgn+=f[i];
	for(int i=n+1;i<N;i++) f2[i]=0;
	for(int i=n;i>=0;i--)
	{
		f2[i]=avg*(sf[i+1]-sf[i+d+1]);
		f2[i]=max(f2[i],sumgn+(i?sum[i-1]:0));
		sf[i]=sf[i+1]+f2[i];
	}
	cout<<fixed<<setprecision(15)<<f2[0]<<"\n";
	return 0;
}



```


---

