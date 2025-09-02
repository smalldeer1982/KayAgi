# Vasya and Endless Credits

## 题目描述

Vasya 想给自己买一辆漂亮的新车。不幸的是，他手头缺钱。目前他正好有 $0$ 布尔。

然而，当地银行有 $n$ 个信贷产品。每个产品可以用三个数字 $a_i$、$b_i$ 和 $k_i$ 来描述。产品编号从 $1$ 到 $n$。如果 Vasya 选择第 $i$ 个产品，那么银行会在本月初给他 $a_i$ 布尔，然后在接下来的 $k_i$ 个月（包括激活该产品的当月）里，每个月月底 Vasya 都要向银行支付 $b_i$ 布尔。Vasya 可以按任意顺序选择这些信贷产品。

每个月 Vasya 最多只能选择一个信贷产品。每个信贷产品也只能使用一次。多个信贷产品可以同时处于激活状态。这意味着，每个月底 Vasya 需要向银行支付所有处于激活状态的信贷产品的 $b_i$ 之和。

Vasya 想在某个月的中旬买车。他会把自己当前拥有的所有钱拿出来，买一辆正好这个价格的车。

Vasya 并不关心买车后还要还银行多少钱。他会开着车离开这个国家，这样银行就再也找不到他了。

请问，这辆车的最大价格是多少？

## 说明/提示

在第一个样例中，最优的信贷产品选择顺序为：4 $\rightarrow$ 3。

Vasya 拥有的布尔数变化如下：5 $\rightarrow$ 32 $\rightarrow$ -86 $\rightarrow$ ...。他在第二个月的中旬拥有 32 布尔，买下了汽车。

负数表示 Vasya 欠银行的钱。

在第二个样例中，最优的信贷产品选择顺序为：3 $\rightarrow$ 1 $\rightarrow$ 2。

Vasya 拥有的布尔数变化如下：0 $\rightarrow$ 300 $\rightarrow$ 338 $\rightarrow$ 1337 $\rightarrow$ 236 $\rightarrow$ -866 $\rightarrow$ ...。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
10 9 2
20 33 1
30 115 1
5 3 2
```

### 输出

```
32
```

## 样例 #2

### 输入

```
3
40 1 2
1000 1100 5
300 2 1
```

### 输出

```
1337
```

# 题解

## 作者：tzc_wk (赞：9)

> CF1107F

> 题意：有 $n$ 个贷款，第 $i$ 个贷款可以由三个整数 $a_i,b_i,k_i$ 描述，你可以在任意天**开始**第 $i$ 个贷款，并且在这一天早上你可以获得 $a_i$ 元，不过在接下来 $k_i$ 天晚上你都要付 $b_i$ 元，也可以选择不使用第 $i$ 个贷款。不过有一个要求：一天只能**开始**最多 $1$ 个贷款。有一辆车♂，价格为 $C$，你可以在任意时刻购买，满足你当前拥有的钱数大于等于 $C$，求在能够买下这辆车的前提下，$C$ 的最大值。

> $1 \leq n \leq 500$，$1 \leq a_i,b_i,c_i \leq 10^9$

我们固定住买车的时间，那么这 $n$ 中贷款可能有以下 $3$ 种可能性：

- 不使用

- 使用，在买车很久很久以前就到期了

- 使用，并且在买车的时候已经用了 $j$ 天。

对于第三种情况，根据贪心的思想，$j$ 肯定要越小越好，所以假设我们已经有了 $t-1$ 个正在使用的贷款，准备付第 $t+1$ 个的时候很明显要将它排在买车前第 $t-1$ 天开始使用。

然后就可以 $01$ 背包了，$dp(i,j)$ 表示在前 $i$ 个贷款中选了 $j$ 个正在使用的方案数，那么还是从以下三种情况转移来：

- 不使用，$dp(i-1,j)$

- 使用，但是到期了，$dp(i-1,j)+a_i - b_i \times k_i$。

- 使用，但是没到期。根据上面的推论，将它排在买车前的第 $j-1$ 天开始付，因此就是 $dp(i-1,j-1)+a_i-b_i \times \min(k_i,j-1)$。

最终答案：$\max dp(n,i)$。

然后发现你样例二就 $\texttt{WA}$ 了：

```
3
40 1 2
1000 1100 5
300 2 1
```

比如说我们先暂时忽略第三个贷款，考虑前两个。

在我们上述过程中如果 $1,2$ 都未到期那么默认 $1$ 开始时间晚于 $2$，那么我们就比较一下“ $1$ 早于 $2$ ”与“ $1$ 晚于 $2$ ”两者的大小。

假设我们在买车前 $1$ 使用第一个，买车前 $2$ 天使用第二个，那么代价是 $40-1 \times 1+1000-1100 \times 2=-1161$，而交换过来就是 $40-1 \times 2+1000-1100 \times 1=-62$。

发现了什么？由于 $b_1<b_2$，所以最好的情况是 $1$ 晚于 $2$。因此我们只需将这些贷款按 $b$ 排序然后重复上述过程就可以了。

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
struct A{
	int a,b,k;
	friend bool operator <(A a,A b){
		return a.b>b.b;
	}
} a[505];
int n=read(),dp[505];
signed main(){
	fz(i,1,n)	a[i].a=read(),a[i].b=read(),a[i].k=read();
	sort(a+1,a+n+1);
	fz(i,1,n){
		fd(j,i,0){
			dp[j]=max(dp[j],dp[j]+max(a[i].a-a[i].b*a[i].k,0ll));
			if(j)
				dp[j]=max(dp[j],dp[j-1]+a[i].a-(j-1)*a[i].b);
		}
	}
	int ans=0;
	fz(i,0,n)	ans=max(ans,dp[i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：litble (赞：4)

# 思路

若已经确定了选择哪些方案，那么一定是先买$b$小的再买$b$大的。

将所有方案按照$b$从大到小排序，设$f(i,j)$表示考虑了前$i$种方案，到了买车的时间还有$j$份没有还完，买车时间手里拥有的最大价值。

那么第$i$种方案要么不买:$f(i,j)=f(i-1,j)$

要么买了，并且在买车的时间已经还完了：$f(i,j)=max(f(i,j),f(i-1,j)+a_i-b_jk_j)$

要么没还完，则它一定是没还完的方案中第一个买的：
$f(i,j)=max(f(i,j),f(i-1,j-1)+a_i-b_j(j-1))$

最后答案是$max(f(n,i))$


# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
typedef long long LL;
const int N=505;
struct node{LL a,b;int k;}t[N];
int n;LL f[N][N],ans;
int cmp(node A,node B) {return A.b>B.b;}

int main()
{
	scanf("%d",&n);
	for(RI i=1;i<=n;++i)
		scanf("%lld%lld%d",&t[i].a,&t[i].b,&t[i].k);
	sort(t+1,t+1+n,cmp);
	for(RI i=1;i<=n;++i) f[0][i]=-1e15;
	for(RI i=1;i<=n;++i) {
		LL ww=max(0LL,t[i].a-1LL*t[i].k*t[i].b);
		f[i][0]=f[i-1][0]+ww;
		for(RI j=1;j<=i;++j)
			f[i][j]=max(f[i-1][j]+ww,f[i-1][j-1]+t[i].a-1LL*(j-1)*t[i].b);
	}
	for(RI i=0;i<=n;++i) ans=max(ans,f[n][i]);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：姬小路秋子 (赞：2)

如果我们没有ki的限制，那我们显然按bi排序dp就可以了。

现在考虑ki的限制。

我们所担心的是一种情况中bi大的比bi小的先买，可是bi大的那个的ki比较小，这样就会出现问题了。。

然后我们震惊的发现，当出现这种情况时，直接把这个bi大ki小的物品拎出来单独累加到答案里就可以了！（代码里都有这个操作，但是我不懂）

因为与其交换位置，不如把它拎出来放到最最前面（与后面的分开），然后把它原来的位置腾出来更优

---

## 作者：lalaouye (赞：1)

KM 做法这么简单好想为什么都在 dp？~~我第一次过也是用的 dp。~~

建模非常好想，每天只能收一次钱，最简单的思路是我们枚举第几天开车跑路，但是再一想我们不关心是第几天，只关心每次贷款离开车跑路还差几天，于是我们从 $i$ 向 $j$ 连边，边权是 $a_i+b_i\times\min(k_i,j)$，意义为第 $i$ 种贷款离买车还差 $j$ 天对答案的贡献，当然我们实现时需要对 $0$ 取最大值，因为取 $0$ 的意义为不参与答案贡献，然而我们并不要求在最后一天开车，所以对 $0$ 取最大值是必要的。

并且，容易证明我们不可能在某一天没有进行任何操作。

所以建完模直接跑 KM 算法即可，时间复杂度 $\mathcal{O(n^3)}$。

代码：

```
#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for (int i = l; i <= r; ++ i)
#define rrp(i, l, r) for (int i = r; i >= l; -- i)
#define eb emplace_back
#define inf 1000000000
#define linf 10000000000000000
#define pii pair <int, int>
using namespace std;
constexpr int N = 505, P = 1e9 + 7;
inline int rd ()
{
	int x = 0, f = 1;
	char ch = getchar ();
	while (! isdigit (ch)) { if (ch == '-') f = -1; ch = getchar (); }
	while (isdigit (ch)) { x = (x << 1) + (x << 3) + ch - 48; ch = getchar (); }
	return x * f;
}
int n, sum, ans;
int e[N][N];
int lx[N], ly[N], px[N], py[N], pre[N], slack[N];
bool vx[N], vy[N], flag;
int a[N], b[N], k[N];
queue <int> q;
void aug (int v)
{
  while (v)
  {
    int t = px[pre[v]];
    px[pre[v]] = v;
    py[v] = pre[v];
    v = t;
  }
}
void bfs (int s)
{
  memset (vx, 0, sizeof vx);
  memset (vy, 0, sizeof vy);
  memset (slack, 127, sizeof slack);
  while (! q.empty ()) q.pop ();
  q.push (s);
  while (true)
  {
    while (! q.empty ())
    {
      int u = q.front ();
      q.pop ();
      vx[u] = 1;
      rep (i, 1, n)
      {
        if (vy[i]) continue;
        if (lx[u] + ly[i] - e[u][i] < slack[i])
        {
          slack[i] = lx[u] + ly[i] - e[u][i];
          pre[i] = u;
          if(! slack[i])
          {
            vy[i] = 1;
            if (! py[i])
            {
              aug (i); return ;
            } else q.push (py[i]);
          }
        }  
      } 
    }
    int d = linf;
    rep (i, 1, n) if (! vy[i]) d = min (d, slack[i]);
    rep (i, 1, n)
    {
      if (vx[i]) lx[i] -= d, sum -= d;
      if (vy[i]) ly[i] += d, sum += d;
      else slack[i] -= d;
    }
    rep (i, 1, n)
    {
      if (vy[i]) continue;
      if(! slack[i])
      {
        vy[i] = 1;
        if (! py[i])
        {
          aug (i); return ;
        } else q.push (py[i]);
      }
    }
  }
}
void solve ()
{
  memset (lx, -127, sizeof lx);
  sum = 0;
  rep (i, 1, n) rep (j, 1, n) lx[i] = max (lx[i], e[i][j]);
  rep (i, 1, n) sum += lx[i];
  
  rep (i, 1, n)
    bfs (i);
}
signed main ()
{
  n = rd ();
  rep (i, 1, n)
  {
    a[i] = rd (), b[i] = rd (), k[i] = rd ();
  }
  rep (i, 1, n)
    rep (j, 1, n)
      e[i][j] = max (0ll, a[i] - min (k[i], j - 1) * b[i]);
  solve ();
  printf ("%lld\n", sum);
}
/*

*/
```

---

## 作者：Rosmarinus (赞：1)

[更好的阅读体验](https://www.cnblogs.com/XJ21/p/14659027.html)

## 题意描述

给定 $n$ 种贷款，第 $i$ 种贷款可以让你立即收入 $a_i$ 元，但接下来的 $k_i$ 天内每天末尾你都要支出 $b_i$ 元。你可以在任意时间购买贷款，每个贷款最多可购买一次，**每天最多只能购买一个贷款**。你手中的金钱可以为负。求在任意时间中你所拥有的金钱的最大值。

## 思路分析

设手中的钱在第 $T$ 天达到最大值，贷款 $i$ 购买的日期为第 $T - x_i$ 天。

可以发现，在第 $T$ 天，贷款可以分成三种类型：

- 1：不购买的贷款；
- 2：购买但未还清的贷款；
- 3：购买并且已经还清的贷款。

对于第1种贷款，无需考虑。

对于第2种贷款 $i$，其对答案的贡献 $w_i=a_i - b_i \times x_i$，显然，$w_i$ 随 $x_i$ 的减小而增大。因此，我们应使这些贷款尽可能晚一点购买，即应使 $x_i$ 尽可能小。

对于第3种贷款 $i$，其对答案的贡献 $w_i=a_i-b_i\times k_i$，由于 $w_i$ 与 $x_i$ 无关，我们应该使这些贷款尽可能早点购买，即应使$x_i$ 尽可能大，腾出位置在给第2种贷款以使答案最大化。

---------------

**接下来考虑顺序问题**：

对于所有的第2种贷款，其总收入与购买顺序无关，但其总支出会受其购买顺序影响。显然，我们应当尽可能地让 $b$ 更大的贷款更晚地购买。在此不作证明，相信大家都能理解。而此时，由于购买顺序确定，我们便可以用 DP 来解决此问题。

## 具体做法
维护一个数组 $dp_{i,j}$，表示前 $i$ 个贷款在第 $T-j$ 天购买时在第 $T$ 天所能获得的最大金额。感性地理解：由于 $T$ 不确定，于是我们将整个购买过程反过来，将 $T$ 作为 $0$，将贷款“倒着”购买。

考虑如何维护：

- 1：若贷款 $i$ 不购买，则 $dp_{i,j}=dp_{{i-1},j}$
- 2：若贷款 $i$ 购买且未还清，则 $dp_{i,j}=dp_{{i-1},{j-1}}+a_i-b_i\times (j-1)$
- 3：若贷款 $i$ 购买且已还清，则 $dp_{i,j}=dp_{{i-1},j}+a_i-b_i\times k_i$

重点解释一下第3种：对于购买且已经还清的贷款，我们将其尽可能往后放是为了让其不占用第2中贷款的位置。而取 $dp_{{i-1},j}$ 而不是 $dp_{{i-1},{j-1}}$ 本质上就是不让 $i$ 占有位置，虽然与“尽早购买”不同，但是达到了一样的的目的。

-------------

特别地，若我们将贷款 $i$ 放在最后面购买，即对于 $dp_{{i},1}$，在贷款 $i$ 前面的贷款 $p$，若 $a_p-b_p\times k_p>0$，那么我们还是应该购买此贷款。可能我说的不是很清楚，用代码解释就是：

- $dp_{i,0}=dp_{{i-1},0}+\max(0,a_i-b_i\times k_i)$

我相信你们都会懂的吧……

-------------

最后输出 $\max(dp_{n,0},dp_{n,1},dp_{n,2},\cdots,dp_{n,n})$ 即可。
## 注意点

- 以 $b$ 为关键字从大到小排序；
- DP 中的顺序与真实的购买顺序是相反的；
- 由于手中的金钱可以为负数，请将 $dp$ 数组初始化为负无穷；
- 需要维护 $dp_{i,0}$；
- 记得开 `long long`。

## AC代码
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
const int N = 510;
ll dp[N][N];
struct Node
{
	ll a, b, k;
}f[N];
bool Sort(Node a, Node b)
{
	return a.b > b.b;
}
int main()
{
	ll ans = 0;
	int n;
	cin >> n;
	for(int i = 1; i <= n; i ++)
	{
		cin >> f[i].a >> f[i].b >> f[i].k;
		dp[0][i] = -0x7f;
	}
	sort(f + 1, f + 1 + n, Sort);
	for(int i = 1; i <= n; i ++)
	{
		ll w = 0;
		w = max(w, f[i].a - f[i].b * f[i].k);
		dp[i][0] = dp[i - 1][0] + w;
		for(ll p = 1; p <= n; p ++)
		{
			dp[i][p] = max(dp[i - 1][p] + w, dp[i - 1][p - 1] + f[i].a - f[i].b * (p - 1));
		}
	}
	for(int i = 0; i <= n; i ++) ans = max(ans, dp[n][i]);
	cout << ans << endl;

	return 0;
}
```

Written by $\operatorname{Rosmarinus}$

希望能对你有所帮助

---

## 作者：happybob (赞：0)

容易证明当选出的贷款固定时，必然会在连续的天排并且在最后一天中午跑路。

此时可以将选出的贷款分为两类，分别是之后付完了和没有付满 $k_i$ 天的。

容易发现如果我们钦定哪些付满，那么没付满的必然填满了一个后缀，且这个后缀是按照 $b$ 不降排序的。

先将原序列按照 $b$ 降序排序，然后考虑 DP。记 $f_{i,j}$ 表示当前考虑了前 $i$ 个贷款，有 $j$ 个贷款是钦定填不满的。转移分三类，分别是第 $i$ 个不选，选但是钦定填满，和钦定填不满。取 $\max$ 即可，时间复杂度 $O(n^2)$。

---

