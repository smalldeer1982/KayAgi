# [POI 2012] WYR-Leveling Ground

## 题目描述

**译自 POI 2012 Stage 3. Day 1「[Leveling Ground](https://szkopul.edu.pl/problemset/problem/W54iZIwStF1TYWRxa1bdVPQo/site/?key=statement)」**

给定一个长度为 $n$ 的数组，每次操作可以将一个区间的数增加或减少 $a$，或将一个区间的数增加或减少 $b$。求使整个数组变为 $0$ 的最小操作次数。若无解请输出 $-1$。

## 说明/提示

对于 $30\%$ 的数据，$n,a,b \le 200,-200 \le h_1,h_2,\ldots,h_n \le 200$.

对于 $60\%$ 的数据，$n,a,b \le 2000,-2000 \le h_1,h_2,\ldots,h_n \le 2000$.

对于 $90\%$ 的数据，$a,b \le 10^6$.

对于所有数据，$1 \le n \le 100\ 000, 1 \le a,b \le 10^9$.

翻译来自于 [LibreOJ](https://loj.ac/p/2701)。

## 样例 #1

### 输入

```
5 2 3
1 2 1 1 -1```

### 输出

```
5```

# 题解

## 作者：Alex_Wei (赞：12)

- Update on 2022.9.29：修改表述。
- Update on 2025.1.22：修订。

### [P3543 [POI2012] WYR-Leveling Ground](https://www.luogu.com.cn/problem/P3543)

区间操作转化为差分数组 $d_i = a_i - a_{i - 1}\ (1\leq i \leq n + 1)$ 的端点操作，其中 $a_{n + 1} = 0$。一次 $+a$ 和一次 $-a$ 抵消，一次 $+b$ 和一次 $-b$ 抵消。设 $A = \frac a d$，$B = \frac b d$。

首先考虑对每个差分值单独求解，解不定方程 $ax + by = d_i$。设 $d = \gcd(a, b)$，根据裴蜀定理，若 $d\nmid d_i$ 则无解。否则用扩欧求得 $ax + by = d$ 的特解，再乘以 $\frac {d_i} d$ 得到 $ax + by = d_i$ 的特解。

先不考虑可行性。因为 $ax_i + by_i = d_i$ 的贡献为 $|x_i| + |y_i|$，而最终答案为所有贡献之和除以 $2$，所以先找到 $|x_i| + |y_i|$ 最小的特解。若 $x_i$ 和 $y_i$ 均不为最小非负整数或最大负整数可行解，则调整法可证 $|x_i| + |y_i|$ 必然不是最优。因此我们只需检查 $x_i$ 和 $y_i$ 分别取到最小非负整数和最大负整数的情况。 

当前 $\frac 1 2\sum (|x_i| + |y_i|)$ 是答案的下界，但不能保证可行性，还需满足 $X = \sum x_i = 0$。当 $X = 0$ 时 $Y = 0$，所以只需考虑 $X$。

根据特解的形式 
$$
\begin{cases}
x = x' + kB \\
y = y' - kA
\end{cases}
$$
当 $X < 0$ 时，我们需要进行 $-\frac X B$ 次将某个 $x_i$ 加上 $B$，并将对应的 $y_i$ 减去 $A$。$\frac X B$ 一定是整数，因为差分数组之和为 $0$。类似的，$X > 0$ 时 $x_i$ 减去 $B$，$y_i$ 加上 $A$。称这样的操作为对 $i$ 进行一次调整，调整的代价等于新的 $|x'_i| + |y'_i|$ 减去原来 $|x_i| + |y_i|$。

容易证明调整一个数的代价随着调整次数增加仅在 $x_i$ 或 $y_i$ 改变符号时增加，其它时候不变，因此我们可以用堆维护这个过程：每次取出代价最小的 $i$ 并弹出，在需求次数与不改变符号的限制下尽可能多地调整。若经过调整后需求次数为 $0$，则算法结束，否则将新的调整代价压入堆。时间复杂度 $\mathcal{O}(n\log n)$，因为 $x_i, y_i$ 中任意一个改变符号才会改变代价，最多发生 $2n$ 次。

一个神奇的性质是 $|\frac X B|$ 在 $\mathcal{O}(n)$ 级别，这使得我们可以从堆中取数时仅进行一次调整就塞回去。证明（来自 [评论区](https://www.luogu.com.cn/discuss/299150)）：当 $|x_i| + |y_i|$ 取到最小值时若 $x_i$ 为最小非负整数或最大负整数，则 $|x_i| \leq B$，则 $|X| \leq nB$。若 $y_i$ 为最小非负整数或最大负整数则 $|y_i| \leq A$，即 $\left| \frac {-XA + \sum d_i} {B} \right| \leq nA$，根据 $\sum d_i = 0$ 得 $|X| \leq nB$。

忽略问题限制得到基本解法再调整，巧妙结合反悔贪心和扩展欧几里得。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using ll = long long;
using uint = unsigned int;
// using lll = __int128;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ull = unsigned long long;
inline ll read() {
  ll x = 0, sgn = 0;
  char s = getchar();
  while(!isdigit(s)) sgn |= s == '-', s = getchar();
  while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
  return sgn ? -x : x;
}
inline void print(ll x) {
  if(x < 0) return putchar('-'), print(-x);
  if(x >= 10) print(x / 10);
  putchar(x % 10 + '0');
}
bool Mbe;
constexpr int N = 1e5 + 5;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
int n, a, b, c[N], d, ad, bd;
ll u, v, x[N], y[N], dx, ans;
int sgn(ll x) {return x < 0 ? -1 : 1;}
void exgcd(ll a, ll b, ll &x, ll &y) {
  if(!b) return x = 1, y = 0, void();
  exgcd(b, a % b, y, x), y -= a / b * x;
}
priority_queue<pii, vector<pii>, greater<pii>> q;
void ins(int i) {q.push({abs(x[i] - sgn(dx) * bd) + abs(y[i] + sgn(dx) * ad) - abs(x[i]) - abs(y[i]), i});}
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n >> a >> b, d = __gcd(a, b);
  ad = a / d, bd = b / d, exgcd(a, b, u, v);
  for(int i = 1; i <= n; i++) c[i] = read();
  for(int i = ++n; i; i--) c[i] -= c[i - 1], x[i] = INF;
  for(int i = 1; i <= n; i++) {
    if(c[i] % d) puts("-1"), exit(0);
    ll p = u * c[i] / d, q = v * c[i] / d, _x, _y;
    auto chk = [&]() {if(abs(_x) + abs(_y) < abs(x[i]) + abs(y[i])) x[i] = _x, y[i] = _y;};
    _x = (p % bd + bd) % bd, _y = (c[i] - _x * a) / b, chk(), _x -= bd, _y += ad, chk();
    _y = (q % ad + ad) % ad, _x = (c[i] - _y * b) / a, chk(), _y -= ad, _x += bd, chk();
    dx += x[i], ans += abs(x[i]) + abs(y[i]);
  }
  for(int i = 1; i <= n; i++) ins(i);
  for(ll i = 0; i < abs(dx); i += bd) {
    pii t = q.top(); q.pop();
    ans += t.fi, x[t.se] -= sgn(dx) * bd, y[t.se] += sgn(dx) * ad, ins(t.se);
  }
  cout << ans / 2 << "\n";
  cerr << TIME << " ms\n";
  return 0;
}
/*
2022/9/29
author: Alex_Wei
start coding at 19:23
finish debugging at 20:07
*/
```

---

## 作者：ywy_c_asm (赞：8)

首先看到随意$+-ab$能从感觉上想到应该是和$gcd(a,b)$有关的东西。

然后这种不断对区间整体加减的套路就是把这玩意的差分序列求出来，然后问题就转化为每次选两个数对他们进行$+-$相反的操作，比如一个$+a$一个$-a$，注意这个差分序列要在末尾添加一个$-a_n$这样就能够处理以结尾为右端点的区间的情况。

我们暂且先不考虑两个一块操作，先对差分序列的每个数独立的进行最优的操作。不难发现对一个数进行操作，本质上是这样一个线性方程：

$ax+by=a_i$

其中$|x|$为加减$a$的次数，$|y|$为加减$b$的次数，于是我们就是要让$|x|+|y|$最小，对于这个方程当然就是扩欧嘛，先求出一组特解$(x',y')$，我们知道，它的通解长这样：

$x=x'+k\frac{b}{gcd(a,b)},y=y'-k\frac{a}{gcd(a,b)}$

那么我们就是要确定一个比较合适的$k$的取值来最小化$|x|+|y|$，容易发现$k$特别大不行特别小也不行，于是这玩意可以三分（~~我太菜了并不会严谨的证明……~~）。

然后我们考虑两两组合的问题，其实我们可以想一下为什么要在上面的基础上考虑这个问题，因为上面解出来的一堆$(x_i,y_i)$并不一定是可以构造成两两组合的形式的（毕竟这才是我们的终极目标，顺便再让代价最小），为什么并不一定可以？其根本原因在于$+a$和$-a$、$+b$和$-b$的操作（就是上面解出的那一堆$x_i$有正的有负的，正的就是$+a$，负的就是$-a$）并不相等，如果相等的话是可以构造出一组合法且代价最小的方案的（毕竟我们的合法方案里就是一个$+a$与一个$-a$、一个$+b$与一个$-b$配对，不相等是配不成对的）。实际上观察到我们的这个差分序列的和为0，如果$+a$与$-a$相等的话，那么此时显然$+b$与$-b$也一定相等，那么我们仅需要考虑让$+a$和$-a$相等就行了。

于是我们便考虑在这个基础上进行调整，假如$+a$操作多于$-a$，那么我们就要改变上面求解出来的某些$(x,y)$，当然我们要调小$x$，我们发现$x$减小1，对于$+a$与$-a$的差值也就会减小1。但是这样就会增大代价，然后有的人就会说了，既然通解长成那样，那代价始终就是$\frac{a}{gcd(a,b)}+\frac{b}{gcd(a,b)}$喽？别忘了我们取的是$|x|+|y|$带个绝对值，所以这就没准了，对每个数更改一次$x$的代价可能是不同的。那么我们可以用堆贪心干这个事，即我们用一个小根堆维护，每次取出一个修改代价最小的把它修改然后把新的代价放到堆里就行了，直到$+a$与$-a$的差值为0为止，这样做的复杂度……比较玄学，但是实际上是能过的（毕竟涉及到$exgcd$的通解的复杂度都比较玄学）。

哦对了，由于我们是一个配对构成一次操作，所以我们最后的答案应该取$\frac{\sum_{i=1}^n|x_i|+|y_i|}{2}$。

上代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cstdlib>
#define ll long long
#define int long long
#define abs(_o) ((_o<0)?-(_o):_o)
using namespace std;
inline int get() {//我的垃圾快读 
	int n=0;
	char c;
	while((c=getchar())||23333) {
		if(c>='0'&&c<='9')break;
		if(c=='-')goto s;
	}
	n=c-'0';
	while((c=getchar())||23333) {
		if(c>='0'&&c<='9')n=n*10+c-'0';
		else return(n);
	}
s:
	while((c=getchar())||23333) {
		if(c>='0'&&c<='9')n=n*10-c+'0';
		else return(n);
	}
}
int exgcd(int a,int b,ll &x,ll &y) {//扩欧 
	if(!b) {
		x=1;
		y=0;
		return(a);
	}
	ll x1,y1;
	int cjr=exgcd(b,a%b,x1,y1);
	x=y1;
	y=x1-(a/b)*y1;
	return(cjr);
}
int ints[100002];//差分序列 
int xs[100001],ys[100001];//解 
typedef struct _n {//堆里放的结构体 
	int pos;//是哪个数 
	int daijia;//修改代价 
	_n(int a,int b) {
		pos=a;
		daijia=b;
	}
	friend bool operator <(const _n &a,const _n &b) {
		return(a.daijia>b.daijia);
	}
} node;
priority_queue<node> que;//堆 
signed main() {
	int n=get(),a=get(),b=get();
	for(register int i=1; i<=n; i++)ints[i]=get();
	n++;
	for(register int i=n; i>=1; i--)ints[i]=ints[i]-ints[i-1];
	int x,y;//通解 
	int g=exgcd(a,b,x,y);
	a/=g;
	b/=g;
	int add=0,sub=0;//+a与-a 
	for(register int i=1; i<=n; i++) {
		if(abs(ints[i])%g!=0) {//这个方程无解 
			printf("-1");
			return(0);
		}
		ints[i]/=g;
		int sx=x*ints[i],sy=y*ints[i];
		int l=-1000000000,r=1000000000;
		while(r-l>5) {//三分，在整数域上直接三分到最后会出一些比较恶心的细节问题，我就在区间比较小的时候上暴力
			int du=(r-l+1)/3;
			int rl=l+du,rr=r-du;
			if(abs(sx+rl*b)+abs(sy-rl*a)>=abs(sx+rr*b)+abs(sy-rr*a))l=rl+1;
			else r=rr-1;
		}
		int minn=0x7fffffffffffffff,best;
		for(register int j=l; j<=r; j++) {
			int dp=abs(sx+j*b)+abs(sy-j*a);
			if(dp<minn)minn=dp,best=j;
		}
		xs[i]=sx+best*b;
		ys[i]=sy-best*a;
		if(xs[i]>0)add+=xs[i];
		else sub-=xs[i];
	}
	int ans=0;
	for(register int i=1; i<=n; i++)ans+=abs(xs[i])+abs(ys[i]);
	int cha=abs(add-sub)/b;
	if(add>sub) {//这里我把+a>-a和+a<-a分开讨论 
		for(register int i=1; i<=n; i++) {
			que.push(_n(i,abs(xs[i]-b)+abs(ys[i]+a)-abs(xs[i])-abs(ys[i])));//把最小修改代价放到堆里 
		}
		while(cha) {
			node cjr=que.top();
			que.pop();
			ans+=cjr.daijia;
			cha--;//减小差值 
			xs[cjr.pos]-=b;
			ys[cjr.pos]+=a;
			que.push(_n(cjr.pos,abs(xs[cjr.pos]-b)+abs(ys[cjr.pos]+a)-abs(xs[cjr.pos])-abs(ys[cjr.pos])));//更新最小修改代价 
		}
	} else {
		for(register int i=1; i<=n; i++) {
			que.push(_n(i,abs(xs[i]+b)+abs(ys[i]-a)-abs(xs[i])-abs(ys[i])));
		}
		while(cha) {
			node cjr=que.top();
			que.pop();
			ans+=cjr.daijia;
			cha--;
			xs[cjr.pos]+=b;
			ys[cjr.pos]-=a;
			que.push(_n(cjr.pos,abs(xs[cjr.pos]+b)+abs(ys[cjr.pos]-a)-abs(xs[cjr.pos])-abs(ys[cjr.pos])));
		}
	}
	ans>>=1;//别忘了最后要除2 
	cout<<ans<<endl;
	return(0);
}
```

---

## 作者：Querainy (赞：5)

这个题感觉很带劲啊。

我们把每个数表示成 $ax_i+by_i$，那么答案就是 $x$，$y$ 两个序列分别做这个问题 : 有一个可能有负数的序列，每次可以给一个区间 $+1$ 或 $-1$，求最小的操作次数把所有数都变成 $0$。考虑差分，可以发现答案就是差分的绝对值的和的一半。这个和 积木大赛 是一致的。

于是首先对每个数 exgcd 求出一组解。然后我们可以 $x_i\leftarrow x_i+k\frac{b}{g}$，$y_i\leftarrow y_i-k\frac{a}{g}$ 生成所有解，其中 $g=\gcd(a$，$b)$。

魔幻地说，我们要在若干斜率同为 $\frac{a}{b}$ 的直线上各选一个整点串起来，答案是在开头结尾各放一个 $(0$，$0)$，相邻两个的曼哈顿距离之和。非常建议想象一下这个画面。

注意到如果我们移动了第 $i$ 条直线上的整点，$>i$ 的部分可以一样地移动(因为斜率相同)，也就是说除了最后跟 $(0$，$0)$ 的贡献，其它贡献都可以不变。

如果没有这个跟 $(0$，$0)$ 的贡献，我们从左往右贪心让相邻两个尽可能近即可。这里也就是最小化一个形如 $\vert x+k\frac{b}{g}\vert+\vert y-k\frac{a}{g}\vert$ 的东西，可以发现的是两者之中较陡的那一个取得最小值时，整个式子也取得最小值，于是检查 $x+k\frac{b}{g}=0$ 附近和 $y-k\frac{a}{g}=0$ 附近即可。

考虑先跑一遍这个贪心，此时问题出在最后跟 $(0$，$0)$ 的贡献可能很大，猜测我们可以通过调整前面的把最后扯回来。具体地，我们每次把一个后缀平移一步，看起来像是 $x_i\leftarrow x_i+k\frac{b}{g}$，$y_i\leftarrow y_i-k\frac{a}{g}$，$k=\pm 1$，$\operatorname{forall}i\geq l)$ 这样的。

容易感觉到最多只会平移 $n$ 步，因为最小化曼哈顿距离时我们总是向上一个点的横坐标或纵坐标(由斜率决定)尽可能靠近，于是 $(x_n$，$y_n)$ 离 $(0$，$0)$ 的横坐标或纵坐标不超过 $n$ 步。这部分可能比较几何直觉。再注意到任意两个位置的移动是独立的，我们依次选择使答案增大最少的 $n$ 次移动，并维护总的答案即可。

由于 exgcd 是瓶颈，用一个堆维护不会增加复杂度，但是还是要说这部分可以对绝对值讨论做到线性。

和大家的题解本质相同。可能就是把那个条件强行先让最后填满了。

```cpp
#include<stdio.h>
#include<queue>
using std::priority_queue;

int n,a,b;
long long x[100002],y[100002];

inline long long abs(long long x){ return x<0?-x:x; }
inline long long min(long long x,long long y){ return x<y?x:y; }
inline int gcd(int a,int b){ return b?gcd(b,a%b):a; }
inline void exgcd(int a,int b,long long &x,long long &y){ b?(exgcd(b,a%b,y,x),y-=a/b*x):(x=1,y=0); }

#define f(k) (abs(x+(k)*sx)+abs(y+(k)*sy))
inline long long calc(long long x,long long y,int sx,int sy,long long &tx,long long &ty)//calc the min dist from (x+k*sx,y+k*sy) to (0,0)
{
    long long p[6]={-(x/sx),0,0,-((y)/sy),0,0};
    p[1]=p[0]-1,p[2]=p[0]+1,p[4]=p[3]-1,p[5]=p[3]+1;
    long long _p=p[0];
    for(int i=1;i<=5;i++) if(f(_p)>f(p[i])) _p=p[i];
    tx+=_p*sx,ty+=_p*sy;
    return f(_p);
}
#undef f

#define norm(x,y) (abs(x)+abs(y))
#define dnorm(x,y,k) (norm((x)+(k)*sx,(y)+(k)*sy)-norm(x,y))

struct Pair{ int v,i; inline bool operator < (Pair p) const { return v>p.v; } };
priority_queue<Pair> q;
int c[100002];

int main()
{
    scanf("%d%d%d",&n,&a,&b);
    long long g=gcd(a,b),sx=b/g,sy=-a/g;
    long long ans=0;
    for(int i=1,t;i<=n;i++)
    {
        scanf("%d",&t);
        if(t%g) return printf("-1\n"),0;
        exgcd(a,b,x[i],y[i]);
        x[i]*=t/g,y[i]*=t/g;
        ans+=calc(x[i]-x[i-1],y[i]-y[i-1],sx,sy,x[i],y[i]);
    }
    long long Ans=(ans+norm(x[n],y[n]));
    int s=dnorm(x[n],y[n],1)<0?1:-1;
    for(int i=1;i<=n;i++) q.push({dnorm(x[i]-x[i-1],y[i]-y[i-1],s),i});
    for(int i=1,d,p;i<=n;i++) d=q.top().v,p=q.top().i,c[p]++,q.pop(),q.push({dnorm(x[p]+s*c[p]*sx-x[p-1],y[p]+s*c[p]*sy-y[p-1],s),p}),ans+=d,Ans=min(Ans,ans+norm(x[n]+s*i*sx,y[n]+s*i*sy));
    printf("%lld\n",Ans/2);
    return 0;
}
```

---

## 作者：AlanSP (赞：4)

### Decsription

> 给定一个长度为 $n$ 的数组，每次操作可以将一个区间的数增加 $a$ 或减少 $b$ ，或将一个区间的数增加 $b$ 或减少 $a$。求使整个数组变为 $0$ 的最小操作次数。若无解请输出 $-1$。

---

### Solution

一道很有意思的思维题。~~不看题解根本不会。~~

看到区间加减一个数的操作，我们可以想到转化为差分数组上单点加减。

我们看到 $a$，$b$ 不难联想到这样一个方程 $ax+by=c$。

是的，我们可以通过exgcd来解决这个问题。

无解的情况很显然：当存在 $c\not \mid \gcd(a,b)$ 时，方程无解。（裴蜀定理） 

我们便找到了一组通解。

考虑最小化操作次数 $|x|+|y|$，不难发现它只有一下几种可能：

- $x$ 为最小非负数，

- $x$ 为最大非正数

- $y$ 为最小非负数

- $y$ 为最大非正数

我们又知道通解 $x=x_0+k\times\frac b {\gcd(a,b)}\  \ y=y_0+k\times \frac a {\gcd(a,b)}$。

所以不难找到这四种解。

---

但我们要注意全局的合法性，我们在差分时选择了两个数，一个加，一个减。

所以我们总的 $\sum\mathrm{sign(a)}=0$，对于 $b$ 也是同理。

显然，我们刚才的贪心并不满足这个性质，所以我们采用反悔堆。

注意到 $x$ 和 $y$ 具有方程关系，所以只要 $x$ 满足条件 $y$ 也一定满足。

我们找出 $x,y$ 中操作总和 $>0$  的一类，考虑如何使它变为 $0$。

（满足了 $ax+by=c$，故一正一负。）令 $\mathrm{cnt_x}>\mathrm{cnt_y}$，

通过上述通解，我们可以尝试每次将 $x$ 减少 $\frac a {gcd(a,b)}$，$y$ 增加 $\frac b {\gcd(a.b)}$。

用大根堆维护代价最大的一组，每次贪心的选它。

再吧反悔的 $now-last$ 加入就好。

在 $\sum x=0$ 时停止即可。

---

### Code：

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
#define int long long 
#define PII pair<int,int>
const int N=100009;
int n,a,b,Ans;
int A[N],X[N],Y[N];
priority_queue<PII> Q;
int exgcd(int a,int b,int &x,int &y)
{
	if(!b){x=1,y=0;return a;}
	int GCD=exgcd(b,a%b,x,y);
	int z=x;x=y,y=z-a/b*y;
	return GCD;
}
inline bool pd(int x,int y,int X,int Y)
{
	return abs(x)+abs(y)<abs(X)+abs(Y);
}
signed main()
{
	scanf("%lld%lld%lld",&n,&a,&b);
	for(int i=1;i<=n;i++) scanf("%lld",&A[i]);
	for(int i=n+1;i>=1;i--) A[i]=A[i]-A[i-1];++n;
	int x,y,d=exgcd(a,b,x,y);a/=d,b/=d;//exgcd特解
	for(int i=1,xx,yy;i<=n;i++)
	{
		if(A[i]%d!=0) return puts("-1"),0;
		xx=X[i]=(x*A[i]/d%b+b)%b;
		yy=Y[i]=(A[i]/d-xx*a)/b;
		xx-=b,yy+=a;
		if(pd(xx,yy,X[i],Y[i])) X[i]=xx,Y[i]=yy;
		yy=(y*A[i]/d%a+a)%a;
		xx=(A[i]/d-yy*b)/a;
		if(pd(xx,yy,X[i],Y[i])) X[i]=xx,Y[i]=yy;
		yy-=a,xx+=b;
		if(pd(xx,yy,X[i],Y[i])) X[i]=xx,Y[i]=yy;
	}
	int rest=0;
	for(int i=1;i<=n;i++) rest+=X[i];
	rest/=b;
	if(rest<0) rest=-rest,swap(a,b),swap(X,Y);
	for(int i=1;i<=n;i++) Q.push( make_pair(-(abs(X[i]-b)+abs(Y[i]+a)-abs(X[i])-abs(Y[i])) ,i));
	while(rest--)
	{
		int u=Q.top().second;Q.pop();
		X[u]-=b,Y[u]+=a;
		Q.push( make_pair(-(abs(X[u]-b)+abs(Y[u]+a)-abs(X[u])-abs(Y[u])) ,u));
	}
	for(int i=1;i<=n;i++) Ans+=abs(X[i])+abs(Y[i]);
	printf("%lld",Ans>>1);
	return 0;
}
```





---

## 作者：Mirasycle (赞：3)

数论和贪心结合，好题！

区间加减是难做的，于是可以转化为差分数组 $d_i=h_i-h_{i+1}$，其中 $d_n=-h_n$。然后我们对于 $h$ 的区间加减就变成了对于 $d$ 数组的两个单点操作一个 $+$，另一个 $-$。我们需要把所有 $d_i$ 都变成 $0$，其中前 $n-1$ 个 $d_i$ 变成 $0$ 代表所有 $h_i$ 都相等，最后一个 $d_n$ 变成 $0$ 代表 $h_n$ 变成了 $0$。所以此时 $h_1=h_2=\dots =h_n=0$。

对于每个点如果想把它操作为 $0$，就是要求 $ax_i+by_i=d_i$，其中 $\lvert x_i\rvert,\lvert y_i\rvert $ 分别表示 $i$ 点两种操作的次数。**因为一次操作是两个单点分别加减，所以必须满足 $\sum x_i=0,\sum y_i=0$。**

因为差分和 $\sum d_i=0$，我们把所有等式累加得到 $a\sum x_i+b\sum y_i=\sum d_i=0$，所以如果满足了第一条限制，就必然会满足第二条。我们要做的就是在满足限制的情况下求出 $\min\{\dfrac{\sum\limits_{i=1}^n\lvert x_i\rvert +\lvert y_i\rvert}{2}\}$。**其实如果直接去构造满足限制，会很难求解最小值。我们考虑求出最小值之后再不断调整使其满足限制。**

先对于每个 $i$，求出 $ax_i+by_i=d_i$ 的最小 $\lvert x_i\rvert +\lvert y_i\rvert$ 解。用 exgcd 解出方程的一个特解 $(x_0,y_0)$ 之后（如果某个方程无解，那么整个问题也是无解），我们可以得到通解的表达式 $\begin{cases} x=x_0+\dfrac{b}{d}k
\\y=y_0-\dfrac{a}{d}k
\end{cases}$。

下面为了探讨问题方便，我们直接令 $A=\dfrac{a}{d},B=\dfrac{b}{d}$。

- 注意我们之前可能听说过 exgcd 求出的方程特解是满足绝对值之和最小的解，但是这个只是在 $ax+by=\gcd(a,b)$ 才满足时候，如果等式右边为 $c$，最后解 $\times \dfrac{c}{\gcd(a,b)}$ 就会不满足了。

最小化 $|x|+|y|$，即最小化 $f(k)=\lvert x_0+kB\rvert+\lvert y_0-kA\rvert$。可以发现 $A,B$ 中必然有一个更大的，**越大的数乘上系数 $k$ 之后变化越大**。不妨设 $A<B$，所以我们考虑让 $x_0+kB$ 向 $0$ 变化，$\lvert y_0-kA\rvert$ 的肯定会增大但是幅度没有另一个减小得大。**故当 $A<B$ 的时候在 $x_0+kB$ 取最小非负解或者最大负解的时候表达式取最小值。** 对于 $A>B$ 的情况同理。

找到最小解之后，为了满足约束条件。我们就要进行调整，使得 $\sum x_i=0$。

我们可以每次选取调整代价最小的 $(x_i,y_i)$ 出来不断调整，可以发现在 $(x_i,y_i)$ 的符号不变的情况下，调整代价也是不变的，也就是 $\lvert A-B\rvert$。只有在某个符号突变的时候发生变化，于是我们可以用堆来维护调整代价最小的位置，然后每次取出后不断调整至符号将要突变，此时代价可能发生变化，我们不能保证最优，于是需要放回堆中重新决策。由于符号只会变 $O(1)$ 次，所以每个点进出堆的次数也是 $O(1)$ 的，不断调整直至 $\sum x_i=0$，时间复杂度 $O(n\log n)$。

不过还有一个观察是（以最小非负整数为例）我们在寻找 $x_i$ 的时候是 $(x_i\bmod B+B)\bmod B$，所以 $x_i<B$，故 $\dfrac{\sum x_i}{B}$ 是在 $O(n)$ 级别的。我们每次调整一次就放回堆中也就是复杂度正确的。


```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
#define int long long
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
int n,a,b,d[maxn],h[maxn],A,B,D;
ll rx[maxn],ry[maxn],ans=0; ll M=0;
priority_queue<pair<int,int> > q;
void exgcd(int a,int b,int &x,int &y){
	if(!b){ x=1; y=0; return ; }
	exgcd(b,a%b,y,x); y-=a/b*x;
}
int get(int x,int y){ return abs(x)+abs(y); }
int val(int x,int y){ return abs(x)+abs(y)-abs(x-B)-abs(y+A); }
signed main(){
	cin>>n>>a>>b; D=__gcd(a,b),A=a/D,B=b/D;
	for(int i=1;i<=n;i++) cin>>h[i]; n++;
	for(int i=1;i<=n;i++) d[i]=h[i]-h[i-1];
	int x0,y0; exgcd(a,b,x0,y0);
	for(int i=1;i<=n;i++){
		if(d[i]%D){ cout<<"-1"; return 0; }
		rx[i]=1ll*x0*d[i]/D; ry[i]=1ll*d[i]*y0/D;
		ll tx,ty;
		if(B<A){// x=x0-kb  y=y0+ka
			ry[i]=(ry[i]%A+A)%A;
			rx[i]=(d[i]-1ll*b*ry[i])/a;
			ty=ry[i]-A; tx=rx[i]+B;
			if(abs(tx)+abs(ty)<abs(rx[i])+abs(ry[i])) swap(tx,rx[i]),swap(ty,ry[i]);
		}else{
			rx[i]=(rx[i]%B+B)%B;
			ry[i]=(d[i]-1ll*a*rx[i])/b;
			tx=rx[i]-B; ty=ry[i]+A;
			if(abs(tx)+abs(ty)<abs(rx[i])+abs(ry[i])) swap(tx,rx[i]),swap(ty,ry[i]);
		}
		ans+=abs(rx[i])+abs(ry[i]); M+=rx[i];
	}
	if(M<0){
		swap(A,B),swap(rx,ry); M=0;
		for(int i=1;i<=n;i++) M+=rx[i];
	}
	for(int i=1;i<=n;i++) q.push(mp(val(rx[i],ry[i]),i));
	for(int i=1;i<=abs(M)/B;i++){
		pair<int,int> cur=q.top(); q.pop();
		ans-=cur.fi; int z=cur.se;
		rx[z]-=B; ry[z]+=A; q.push(mp(val(rx[i],ry[i]),i));
	}
	cout<<ans/2;
	return 0;
}
```

---

## 作者：Purslane (赞：2)

# Solution

写一个非常直观而且非常容易想到，可能有一点难写的题解。

考虑最终每个数和原来必定模 $\gcd(a,b)$ 同余。再根据裴蜀定理的结论，所有数都是 $\gcd(a,b)$ 的倍数为有解的充要条件。所以不妨先把 $\gcd(a,b)$ 都除掉，变成 $\gcd(a,b)=1$ 的情形。

每个数都能用 $\rm ExGcd$ 表示为 $x_i = p_i a + q_i b$ 的形式，则所有解为 $x_i = (p_i+t_ib) a + (q_i - t_ia)b$。

考虑给定了一组这样的 $t$，需要的代价就是：

$$
\sum_{i=1}^{n+1} | p_i - p_{i-1}+(t_i-t_{i-1})b| +|q_i-q_{i-1} + (t_{i-1}-t_i)a|
$$

其中 $p_0 = p_{n+1} = q_0 = q_{n+1} = 0$，$t_0=t_{n+1} = 0$。

如果 $i=n+1$ 不被考虑的话，这个其实是一个非常简单的问题。考虑到如果 $t_i$ 和 $t_{i-1}$ 整体 $\pm 1$ 则这一项不会改变，所以我们对于每个 $i$，在 $i-1$ 的基础上最小化 $i$ 即可（本质上是找到是这个式子最小的 $t_i - t_{i-1}$）。

但是这个做法最大的 bug 就是 $t_{n+1}=0$ 是不可控的，有可能 $t_{n+1} - t_n$ 是一个很不好玩的数值。

考虑函数 $f_i(x) = |p-bx| + |q + ax|$，其中 $p$ 和 $q$ 根据 $i$ 唯一确定。

这个函数必定是长这样的：

![](https://s11.ax1x.com/2024/02/22/pFNBGTK.png)

到底是左边还是右边取决于 $p$ 和 $q$ 的相对大小关系，不过不怎么重要。

所以你在前 $n$ 次确定的时候其实把点全部贪心的放在最底下这个点。

考虑函数 $f_{n+1}(x)$，根据题目限定你就可能无法把 $x$ 放在最底下那个点。

怎么办呢？显然最好的办法是拆东墙补西墙。注意我们当前肯定是优先把 $x$ 往最低点移动，那么必须有一个原来的决策点按照反方向移动。注意，显然不会有决策点同向移动，这样只会更劣。

剩下的套路就有点 slope tricks 的感觉了。枚举所有线段即可。（最后的收益关于移动的次数是凸的，找到这个凸包的最高点。）

感觉按照我这个方法很好把这题做出来，但是真难写。复杂度 $O(n \log n)$。

建议本题加个数据范围：$1 \le n \le 10^5$，$|X_i| \le 10^9$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int n,gcd,ans,a,b,x[MAXN],p[MAXN],q[MAXN],P,Q,dt[MAXN],sum;
int f(int i,int x) {return abs(p[i]-p[i-1]+b*x)+abs(q[i]-q[i-1]-a*x);}
pair<int,int> exgcd(int a,int b) {
	if(!b) return {1,0};
	auto pr=exgcd(b,a%b);
	int X=pr.first,Y=pr.second;
	return {Y,X-(a/b)*Y};
}
pair<int,int> calc_min(int i) {
	pair<int,int> pr={0x3f3f3f3f3f3f3f3f,0};
	int P=p[i-1]-p[i],Q=q[i]-q[i-1];
	pr=min(pr,{f(i,P/b),P/b}),pr=min(pr,{f(i,Q/a),Q/a});
	pr=min(pr,{f(i,P/b+1),P/b+1}),pr=min(pr,{f(i,Q/a+1),Q/a+1});
	pr=min(pr,{f(i,P/b-1),P/b-1}),pr=min(pr,{f(i,Q/a-1),Q/a-1});
	return pr;
}
multiset<pair<int,int>> cv1,cv2;
void add_segs1(int i,int u,multiset<pair<int,int>> &st) {
	while(1) {
		int p1=u,p2=u+1,nxt=p2,slp=f(i,p2)-f(i,p1);
		if(slp==a+b) return ;
		roff(j,25,0) if(f(i,nxt+(1<<j))-f(i,nxt)==slp*(1<<j)) nxt+=(1<<j);
		st.insert({slp,nxt-p1});
		u=nxt;
	}
	return ;
}
void add_segs2(int i,int u,multiset<pair<int,int>> &st) {
	while(1) {
		int p1=u,p2=u-1,nxt=p2,slp=f(i,p2)-f(i,p1);
		if(slp>=0) return ;
		roff(j,25,0) if(f(i,nxt-(1<<j))-f(i,nxt)==slp*(1<<j)) nxt-=(1<<j);
		st.insert({slp,p1-nxt});
		u=nxt;
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>a>>b,gcd=__gcd(a,b),a/=gcd,b/=gcd;
	ffor(i,1,n) cin>>x[i];
	ffor(i,1,n) if(x[i]%gcd) return cout<<-1,0; else x[i]/=gcd;
	auto pr=exgcd(a,b); P=pr.first,Q=pr.second;
	ffor(i,1,n) p[i]=P*x[i],q[i]=Q*x[i];
	ffor(i,1,n) {auto pr=calc_min(i);dt[i]=pr.second,sum+=dt[i],ans+=pr.first;}
	sum=-sum;
	pr=calc_min(n+1); int opt=pr.second; ans+=f(n+1,sum);
	if(sum<opt) {opt=-opt,sum=-sum;ffor(i,1,n) p[i]=-p[i],q[i]=-q[i],dt[i]=-dt[i];}
	ffor(i,1,n) add_segs1(i,dt[i],cv1);
	add_segs2(n+1,sum,cv2);
	while(!cv1.empty()&&!cv2.empty()) {
		int val=cv1.begin()->first+cv2.begin()->first,cnt=min(cv1.begin()->second,cv2.begin()->second);
		if(val>=0) break ;
		ans+=val*cnt;
		auto pr1=*cv1.begin(),pr2=*cv2.begin();
		cv1.erase(cv1.begin()),cv2.erase(cv2.begin());
		if(pr1.second!=cnt) cv1.insert({pr1.first,pr1.second-cnt});
		if(pr2.second!=cnt) cv2.insert({pr2.first,pr2.second-cnt});
	}
	cout<<ans/2;
	return 0;
}
```

---

## 作者：SunsetSamsara (赞：1)

## P3543

### 题意

给定长度为 $n$ 的数列和两个数 $p, q$，每次可以选择一段区间进行 $+p,-p,+q,-q$ 之一的操作，求出全部变成 $0$ 的最小操作次数，如果无解输出 $-1$。

### 标签

思维，数论

### 做法

首先，无解的情况当且仅当至少存在一个 $a_i$ 使得 $\gcd(s_i, t_i) \nmid a_i$。

有解时先让 $p \leftarrow \frac{p}{\gcd(p, q)}$，$q \leftarrow \frac{q}{\gcd(p, q)}$，$a_i \leftarrow \frac{a_i}{\gcd(p, q)}$。接下来令 $a_{n + 1} = 0$，对原序列进行差分得到数列 $b$，就变成了每次选择两个点进行 $+p,-p$ 或 $+q,-q$ 的操作。

考虑其中一个值 $b_i$，就相当于需要 $ps_i + qt_i = b_i$ 的解，用拓展欧几里得算法算出一个解就相当于得出所有解了。对于这一个点的一组解的代价是 $|s_i| + |t_i|$，显然要让代价最小，必须要让 $s_i$ 和 $t_i$ 有一个是绝对值最小的解。因为每次操作都是对两个位置进行同样的操作，所以 $\sum\limits_{i}s_i = \sum\limits_{i}t_i = 0$，而求的最小操作次数就是 $\frac 1 2\sum\limits_{i} (|s_i| + |t_i|)$。

所以要做的就是对一些 $(s_i, t_i)$ 变成 $(s_i + kq, t_i - kp)$ 使得 $\sum\limits_{i}s_i = \sum\limits_{i}t_i = 0$。注意到 $\sum\limits_{i}(s_ip + t_iq) = 0$，所以只需令 $\sum\limits_{i}s_i = 0$ 即可。对于 $\sum\limits_{i}s_i > 0$ 的情况把每次把 $(s_i, t_i)$ 变成 $(s_i - q, t_i + p)$ 减小 $s$ 之和的操作的新增代价放进一个小根堆，每次贪心取出代价最小的操作即可。对于 $\sum\limits_{i}s_i < 0$ 的情况则完全相反。

### 代码

```cpp
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <set>
typedef long long lld;
using namespace std;
#define log() printf("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
const int N = 100010;
int n, p, q;
int a[N];
lld s[N], t[N];
inline int exgcd(int a, int b, int &x, int &y) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	int d = exgcd(b, a % b, y, x); 
	y -= a / b * x;
	return d;
}
priority_queue<pair<lld, int> > pq;
inline lld calc(int i) {
	return abs(s[i]) + abs(t[i]) - abs(s[i] - q) - abs(t[i] + p);
}
int main() {
	scanf("%d%d%d", &n, &p, &q);
	int x = 0, y = 0;
	int g = exgcd(p, q, x, y);
	p /= g, q /= g;
	for (int i = 1; i <= n; ++ i) {
		scanf("%d", a + i);
		if (a[i] % g) {
			puts("-1");
			return 0;
		}
		a[i] /= g;
	}
	++ n;
	for (int i = n; i; -- i) a[i] -= a[i - 1];
	for (int i = 1; i <= n; ++ i) {
		int x1 = (1ll * x * a[i] % q + q) % q, y1 = (a[i] - 1ll * p * x1) / q;
		s[i] = x1, t[i] = y1;
		if (abs(x1 - q) + abs(y1 + p) < abs(s[i]) + abs(t[i])) s[i] = x1 - q, t[i] = y1 + p;
		y1 = (1ll * y * a[i] % p + p) % p, x1 = (a[i] - 1ll * q * y1) / p;
		if (abs(x1) + abs(y1) < abs(s[i]) + abs(t[i])) s[i] = x1, t[i] = y1;
		if (abs(x1 + q) + abs(y1 - p) < abs(s[i]) + abs(t[i])) s[i] = x1 + q, t[i] = y1 - p;
//		printf("%d: %d %d\n", i, s[i], t[i]);
	}
	lld sum = 0;
	for (int i = 1; i <= n; ++ i) sum += s[i];
	sum /= q;
	if (sum < 0) sum = -sum, swap(p, q), swap(s, t);
	for (int i = 1; i <= n; ++ i) pq.push(make_pair(calc(i), i));
	for (; sum --; ) {
		int i = pq.top().second;
		pq.pop();
		s[i] -= q, t[i] += p;
		pq.push(make_pair(calc(i), i));
	}
	lld ans = 0;
	for (int i = 1; i <= n; ++ i) ans += abs(s[i]) + abs(t[i]);
	printf("%lld\n", ans / 2);
}
```

---

## 作者：FjswYuzu (赞：1)

判断有无解，显然就是判断是否 $\forall i \in [1,n]  \gcd(a,b) | h_i$。裴蜀定理随便证证就好了。

然后对于一个序列问题，进行区间加减操作，一个非常简单的套路就是做出其差分数组，然后单点修改即可。为了保证最后一个数修改后为 $0$，所以我们多加一个数 $h_{n+1}=-h_{n}$。

考虑只有两种操作 $a,b$。先想一想一个数的时候我们应该怎么去处理。对于一个数 $s$，对其进行操作，设未知数 $x,y$ 表示 $a$ 操作进行次数和 $b$ 操作进行次数（负数就相当于减 $a$ 或 $b$）相当于解一个等式：

$$
ax+by=s
$$

显然这个问题可以直接用拓展欧几里得算法去做。不赘述。

于是想让 $|x|+|y|$ 最小。这个可以随便分类讨论一发，判断一下 $x,y$ 分别取极值的时候就行了吧。或者说你也可以根据方程通解（看下面！）三分也行：

$$
\begin{cases}
x=x_0 + k \times \dfrac{b}{\gcd(a,b)} \\
y=y_0 + k \times \dfrac{a}{\gcd(a,b)}
\end{cases}
$$

找到这些解之后，我们还要考虑让：


- 所有数变为 $0$；   
- 答案最小。

然而我们之前的做法并不能满足 $n >1$ 的情况。对于这种情况的通用方法就是反悔贪心。

考虑到之前那个方程的性质，$x,y$ 一定满足某种关系（看通解也看的出来吧）。当前的堆里面储存上当前的方程的解的贡献减去修改一次 $x,y$ 之后的贡献。

为了让其满足所有数变为 $0$，更改的时候考虑修改掉其 $x,y$。假设我们现在的 $\sum x >0$，我们取出操作次数最小的那个数，根据之前的方程通解增大 $x$，减小 $y$ 即可，然后再放回去。

这样，当 $\sum x$ 等于 $0$ 的时候，答案就出来了，即为：

$$
\sum_{i=1}^{n+1} \dfrac{x_i+y_i}{2}
$$

注意要除以 $2$，而且要输出答案的时候除。

[反悔贪心博客](https://www.cnblogs.com/amagaisite/p/13537905.html)

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL gcd(LL a,LL b){return !b?a:gcd(b,a%b);}
void exgcd(LL &x,LL &y,LL a,LL b)
{
	if(!b)
	{
		x=1,y=0;
		return ;
	}
	exgcd(x,y,b,a%b);
	LL tmp=x;
	x=y;
	y=tmp-a/b*y;
}
LL Abs(LL x){return x>0?x:-x;}
struct Answer{
	LL x,y;
	Answer(LL X=0,LL Y=0){x=X,y=Y;}
	bool operator < (Answer ano) const {return Abs(x)+Abs(y)<Abs(ano.x)+Abs(ano.y);}
}p[100005];
struct Factor{
	LL val,pos;
	Factor(LL V=0,LL P=0){val=V,pos=P;}
	bool operator < (Factor ano) const {return val>ano.val;}
};
priority_queue<Factor> Q;
LL n,a,b,s[100005];
int main(){
	scanf("%lld %lld %lld",&n,&a,&b);
	for(LL i=1;i<=n;++i)	scanf("%lld",&s[i]);
	LL d=gcd(a,b);
	for(LL i=1;i<=n;++i)	if(s[i]%d)	return puts("-1")&0;
	++n;
	for(LL i=n;i;--i)	s[i]=s[i]-s[i-1];
	LL x,y;
	exgcd(x,y,a,b);
	a/=d,b/=d;
//	printf("%lld %lld %lld %lld\n",x,y,a,b);
//	for(LL i=1;i<=n;++i)	printf("%lld ",s[i]);
//	puts("");
	for(LL i=1;i<=n;++i)
	{
		LL sx=(x*s[i]/d%b+b)%b,sy=(s[i]/d-sx*a)/b;
		p[i]=Answer(sx,sy);
		sx-=b,sy+=a;
		if(Answer(sx,sy)<p[i])	p[i]=Answer(sx,sy);
		sy=(y*s[i]/d%a+a)%a,sx=(s[i]/d-sy*b)/a;
		if(Answer(sx,sy)<p[i])	p[i]=Answer(sx,sy);
		sx+=b,sy-=a;
		if(Answer(sx,sy)<p[i])	p[i]=Answer(sx,sy);
	}
//	for(LL i=1;i<=n;++i)	printf("%lld %lld\n",p[i].x,p[i].y);
	LL lc=0;
	for(LL i=1;i<=n;++i)	lc+=p[i].x;
	lc/=b;
	if(lc<0)
	{
		lc=-lc;
		swap(a,b);
		for(LL i=1;i<=n;++i)	swap(p[i].x,p[i].y);
	}
	for(LL i=1;i<=n;++i)	Q.push(Factor(Abs(p[i].x-b)+Abs(p[i].y+a)-Abs(p[i].x)-Abs(p[i].y),i));
	for(LL i=1;i<=lc;++i)
	{
		Factor k=Q.top();
		Q.pop();
		LL now=k.pos;
		p[now].x-=b,p[now].y+=a;
		Q.push(Factor(Abs(p[now].x-b)+Abs(p[now].y+a)-Abs(p[now].x)-Abs(p[now].y),now));
	}
	LL ans=0;
	for(LL i=1;i<=n;++i)	ans+=(Abs(p[i].x)+Abs(p[i].y));
	printf("%lld",ans/2);
	return 0;
}
```


---

## 作者：FeelGood (赞：1)

对于区间操作加减操作我们可以先对原数组做一个差分。同时为了处理结尾情况我们需要在差分数组尾部插入一个 $-a_n$。

然后我们发现题目的四种操作可以被表示为一个方程：$ax_i + by_i = d_i$。于是我们就可以使用扩展欧几里得算法求出一个特解，然后可以构造出通解 $x_i = x'_{i} + \frac{bt}{\gcd(a,b)}$，$k_2 = k'_2 - \frac{at}{\gcd(a, b)}$。

接下来我们贪心的思考发现只有四种情况答案可能是最优的：$x_i$ 是最大负整数解或最小非负整数解，$y_i$ 是最大负整数解或最小非负整数解

那么答案就是 $\frac{\sum_{i = 1}^{n} |x_i| + |y_i|}{2}$。

但是我们知道差分是要满足 $\sum_{i = 1}^{n} x_i = 0$ 并且 $\sum_{i = 1}^{n} y_i = 0$，所以我们最开始的解可能是不合法的，还需要对答案进行修改。我们发现只需要让$\sum_{i = 1}^{n} x_i = 0$ 即可，因为如果 $x$ 合法了，那么 $y$ 也合法了。我们可以使用反悔贪心来进行修改。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define lll __int128

namespace FastRead
{
    void read() {}

    template <typename T1, typename ...T2>
    void read(T1 &n, T2 &...m)
    {
        T1 op = 1;
        char c;
        while (isdigit(c = getchar()) == false)
            if (c == '-') op = -1;
        n = c - '0';
        while (isdigit(c = getchar()))
            n = (n << 1) + (n << 3) + c - '0';
        n *= op;
        read(m...);
    }
}

using FastRead::read;

namespace Solve
{
	const int MaxN = 1e5;
	
	ll x[MaxN + 10], y[MaxN + 10], d[MaxN + 10];
	
	ll exgcd(ll a, ll b, ll &x, ll &y)
	{
		if (b == 0)
		{
			x = 1, y = 0;
			return a;
		}
		ll x1, y1, d;
		d = exgcd(b, a % b, x1, y1);
		x = y1;
		y = x1 - a / b * y1;
		return d;
	}
	
	priority_queue<pair<ll, ll> > q;

    void Sol()
    {
    	ll n, a, b;
    	read(n, a, b);
    	for (ll i = 1; i <= n; ++i)
    		read(d[i]);
    	++n;
    	for (ll i = n; i >= 1; --i)
    		d[i] = d[i] - d[i - 1];
    	ll X, Y, gcdn;
    	gcdn = exgcd(a, b, X, Y);
    	a /= gcdn, b /= gcdn;
    	for (ll i = 1; i <= n; ++i)
    	{
    		if (d[i] % gcdn != 0)
    		{
    			printf("-1\n");
    			return;
    		}
    		ll tx, ty;
    		tx = X * d[i] / gcdn;
    		x[i] = tx = (tx % b + b) % b;
    		y[i] = ty = (d[i] / gcdn - a * tx) / b;
    		tx -= b, ty += a;
    		if (abs(tx) + abs(ty) < abs(x[i]) + abs(y[i]))
    			x[i] = tx, y[i] = ty;
    		ty = Y * d[i] / gcdn;
    		ty = (ty % a + a) % a;
    		tx = (d[i] / gcdn - b * ty) / a;
    		if (abs(tx) + abs(ty) < abs(x[i]) + abs(y[i]))
    			x[i] = tx, y[i] = ty;
    		ty -= a, tx += b;
    		if (abs(tx) + abs(ty) < abs(x[i]) + abs(y[i]))
    			x[i] = tx, y[i] = ty;
    	}
    	ll sum = 0;
    	for (ll i = 1; i <= n; ++i)
    		sum += x[i];
    	sum /= b;
    	if (sum < 0)
    		swap(a, b), swap(x, y), sum = -sum;
    	for (ll i = 1; i <= n; ++i)
    		q.emplace(abs(x[i]) + abs(y[i]) - abs(x[i] - b) - abs(y[i] + a), i);
    	while (sum)
    	{
    		--sum;
    		ll i = q.top().second;
    		q.pop();
    		x[i] -= b, y[i] += a;
    		q.emplace(abs(x[i]) + abs(y[i]) - abs(x[i] - b) - abs(y[i] + a), i);
    	}
    	ll ans = 0;
    	for (ll i = 1; i <= n; ++i)
    		ans += abs(x[i]) + abs(y[i]);
    	printf("%lld\n", ans >> 1ll);
    }
}

using Solve::Sol;

int main()
{
    Sol();
    return 0;
}
```

---

