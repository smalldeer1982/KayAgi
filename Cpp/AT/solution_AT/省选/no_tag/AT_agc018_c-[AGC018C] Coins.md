# [AGC018C] Coins

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc018/tasks/agc018_c

$ 1 $ から $ X+Y+Z $ までの番号のついた、$ X+Y+Z $ 人の人がいます。 人 $ i $ は、金のコインを $ A_i $ 枚、銀のコインを $ B_i $ 枚、銅のコインを $ C_i $ 枚持っています。

すぬけ君は、彼らのうち $ X $ 人から金のコイン、$ Y $ 人から銀のコイン、$ Z $ 人から銅のコインをもらおうと考えています。 どの人からも、$ 2 $ 種類以上のコインをもらうことはできません。 また、どの人も、指定された色のコインをすべてあなたに渡してくれます。

すぬけ君は、最終的に持っている全ての色のコインの枚数の合計を最大化したいです。 すぬけ君が最終的に持っている全ての色のコインの枚数の合計の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ X $
- $ 1\ \leq\ Y $
- $ 1\ \leq\ Z $
- $ X+Y+Z\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ B_i\ \leq\ 10^9 $
- $ 1\ \leq\ C_i\ \leq\ 10^9 $

### Sample Explanation 1

人 $ 1 $ から銀のコインを、人 $ 2 $ から銀のコインを、人 $ 3 $ から銅のコインを、人 $ 4 $ から金のコインをもらうと、 コインの枚数の合計は、$ 4+2+7+5=18 $ になります。 $ 19 $ 枚以上のコインを得る方法はないので、この例の答えは $ 18 $ になります。

## 样例 #1

### 输入

```
1 2 1
2 4 4
3 2 1
7 6 7
5 2 3```

### 输出

```
18```

## 样例 #2

### 输入

```
3 3 2
16 17 1
2 7 5
2 16 12
17 7 7
13 2 10
12 18 3
16 15 19
5 6 2```

### 输出

```
110```

## 样例 #3

### 输入

```
6 2 4
33189 87907 277349742
71616 46764 575306520
8801 53151 327161251
58589 4337 796697686
66854 17565 289910583
50598 35195 478112689
13919 88414 103962455
7953 69657 699253752
44255 98144 468443709
2332 42580 752437097
39752 19060 845062869
60126 74101 382963164```

### 输出

```
3093929975```

# 题解

## 作者：Kewth (赞：57)

提供一个用排序 + 优先队列的做法。

首先默认将三元组 $(a, b, c)$ 替换为二元组 $(e=b-a, f=c-a)$ （先默认所有人拿金币）。

然后问题转换为在 $n$ 个二元组中选 $y$ 个获得 $e$ 收益，选 $z$ 个获得 $f$ 收益，最大化总收益。

对于两个二元组 $(e_i, f_i)$, $(e_j, f_j)$ 假设 $i$ 选 $f$ 且 $j$ 选 $e$ ，

考虑什么时候交换他们的选择收益不会变少，也就是 $e_i + f_j \geq e_j + f_i$ ，

移项得 $e_i - f_i \geq e_j - f_j$ ，那么通过排序使得二元组按 $e - f$ 单调不降，

就有对于任意 $i < j$ ，如果 $i$ 选 $f$ 且 $j$ 选 $e$ ，那么交换两者状态一定不会变差。

换言之，存在最优解满足选 $e$ 的全在选 $f$ 的左边，

也就是说存在一个 $k$ 使得有最优解在 1 到 $k$ 中取 $y$ 个 $e$ 在 $k + 1$ 到 $n$ 中取 $z$ 个 $f$ 。

那么只需要通过优先队列预处理出每个前缀前 $y$ 大的 $e$ 的和以及每个后缀前 $z$ 大的 $f$ 的和。

然后枚举 $k$ 即可得出答案。

参考实现（代码中用 $a, b$ 表示的上述的 $e, f$ ）：

```cpp
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005;
struct obj {
	int a, b;
};
obj ob[maxn];
ll lget[maxn], rget[maxn];

int main() {
	int x = read, y = read, z = read;

	int n = x + y + z;
	ll ans = 0;
	for(int i = 1; i <= n; i ++) {
		int v = read;
		ans += v;
		ob[i].a = read - v;
		ob[i].b = read - v;
	}

	std::sort(ob + 1, ob + n + 1, [](obj x, obj y) {
				return x.a - x.b > y.a - y.b;
			});

	std::priority_queue<int, std::vector<int>, std::greater<int> > biggest;

	for(int i = 1; i <= n; i ++) {
		lget[i] = lget[i - 1] + ob[i].a;
		biggest.push(ob[i].a);
		if(int(biggest.size()) > y) {
			lget[i] -= biggest.top();
			biggest.pop();
		}
	}

	while(!biggest.empty()) biggest.pop();
	for(int i = n; i; i --) {
		rget[i] = rget[i + 1] + ob[i].b;
		biggest.push(ob[i].b);
		if(int(biggest.size()) > z) {
			rget[i] -= biggest.top();
			biggest.pop();
		}
	}

	ll max = - 1000000000000000000;
	for(int k = y; k <= n - z; k ++)
		max = std::max(max, lget[k] + rget[k + 1]);

	printf("%lld\n", ans + max);
}
```

---

## 作者：w4p3r (赞：42)



看完题可以发现这是一个类似于[NOI2019]序列的题目，自然考虑反悔贪心。

vp赛时本蒟蒻本来先考虑先选$x$个金币，再选$y$个银币，最后选$z$个铜币，在选每种币的时候把所有可以反悔的情况都开个堆维护，但是发现这样太复杂了，而且根本就没有利用总人数$n=x+y+z$的性质。

考虑因为$n=x+y+z$，所以可以先让所有人随便选一种硬币，保证$x$个人选了金币，$y$个人选了银币，$z$个人选了铜币，我们再进行反悔。

为方便，下文用$x->y$表示一个选了金币的人换成了银币，$y->z,z->x$等同理。

此时因为我们并不能改变选某种硬币的人数，所以我们能进行的变换只有类似于$x->y$，$x->z$，$z->x$这种环状的变换。略加思考可以发现只有$5$种情况：

$1.x->y,y->z,z->x$

$2.x->z,z->y,y->x$

$3.x->y,y->x$

$4.y->z,z->y$

$5.x->z,z->x$

然后一个人能进行的变换也只有$6$种，因此维护$6$个堆，然后每次对这$5$种情况找一个最大值即可（最大值$<=0$时答案达到最大值）

```cpp
//W4P3R
#include<bits/stdc++.h>
#define inf 1e9
#define eps 1e-6
#define mp make_pair
#define pb push_back
#define re register ll
#define fr first
#define sd second
#define pa pair<ll,ll>
#define FOR(i,a,b) for(re i=a;i<=b;i++)
#define REP(i,a,b) for(re i=a;i>=b;i--)
#define MEM(a) memset(a,0,sizeof(a))
#define N 100010
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
inline ll read()
{
	char ch=getchar();
	ll s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
inline ll lowbit(ll x){return x&(-x);}
ll n,X,Y,Z;
ll a[N],b[N],c[N];
ll vis[N],ans;
priority_queue<pa,vector<pa>,less<pa> >q1,q2,q3,q4,q5,q6;
inline void add(ll x)
{
	q1.push(mp(b[x]-a[x],x));//x->y
	q2.push(mp(c[x]-b[x],x));//y->z
	q3.push(mp(a[x]-c[x],x));//z->x
	
	q4.push(mp(c[x]-a[x],x));//x->z
	q5.push(mp(b[x]-c[x],x));//z->y
	q6.push(mp(a[x]-b[x],x));//y->x
}
int main()
{
	//ios::sync_with_stdio(false);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	X=read(),Y=read(),Z=read();n=X+Y+Z;
	FOR(i,1,n)a[i]=read(),b[i]=read(),c[i]=read();
	FOR(i,1,X)vis[i]=1,ans+=a[i];
	FOR(i,X+1,X+Y)vis[i]=2,ans+=b[i];
	FOR(i,X+Y+1,X+Y+Z)vis[i]=3,ans+=c[i];
	FOR(i,1,n)add(i);
	while(true)
	{
		while(!q1.empty()&&vis[q1.top().sd]!=1)q1.pop();
		while(!q2.empty()&&vis[q2.top().sd]!=2)q2.pop();
		while(!q3.empty()&&vis[q3.top().sd]!=3)q3.pop();
		
		while(!q4.empty()&&vis[q4.top().sd]!=1)q4.pop();
		while(!q5.empty()&&vis[q5.top().sd]!=3)q5.pop();
		while(!q6.empty()&&vis[q6.top().sd]!=2)q6.pop();//反悔贪心在每次取值时弹出不合法状态往往更好写 
		
		ll v1=(q1.empty()?-inf:q1.top().fr),v2=(q2.empty()?-inf:q2.top().fr),v3=(q3.empty()?-inf:q3.top().fr);
		ll v4=(q4.empty()?-inf:q4.top().fr),v5=(q5.empty()?-inf:q5.top().fr),v6=(q6.empty()?-inf:q6.top().fr);
		ll maxn=0,t=0;
		if(v1+v2+v3>maxn)maxn=v1+v2+v3,t=1;//情况1
		if(v4+v5+v6>maxn)maxn=v4+v5+v6,t=2;//情况2
		if(v1+v6>maxn)maxn=v1+v6,t=3;//情况3
		if(v2+v5>maxn)maxn=v2+v5,t=4;//情况4
		if(v3+v4>maxn)maxn=v3+v4,t=5;//情况5
		if(!maxn)break;ans+=maxn;
		if(t==1)
		{
			ll x=q1.top().sd,y=q2.top().sd,z=q3.top().sd;
			vis[x]=2,vis[y]=3,vis[z]=1;
			add(x);add(y);add(z);
		}
		if(t==2)
		{
			ll x=q4.top().sd,y=q5.top().sd,z=q6.top().sd;
			vis[x]=3;vis[y]=2;vis[z]=1;
			add(x);add(y);add(z);
		}
		if(t==3)
		{
			ll x=q1.top().sd,y=q6.top().sd;
			vis[x]=2;vis[y]=1;
			add(x);add(y);
		}
		if(t==4)
		{
			ll x=q2.top().sd,y=q5.top().sd;
			vis[x]=3;vis[y]=2;
			add(x);add(y);
		}
		if(t==5)
		{
			ll x=q3.top().sd,y=q4.top().sd;
			vis[x]=1;vis[y]=3;
			add(x);add(y);
		}
	}
	cout<<ans<<'\n';
	return 0;
}
//gl

```

**如果你觉得这篇题解对你有帮助，那你可以点个赞支持我一下qwq。如果你对题解有任何问题/认为我的题解有任何问题，可以私信/在评论区发出来，当然如果你对我的题解有任何意见/建议也欢迎指出。我会尽我全力把我题解写到最好的qwq**

---

## 作者：WeLikeStudying (赞：15)

**题意**
- [题目](https://www.luogu.com.cn/problem/AT2672)。
- $\text{CCF}$ 举办的 $\text{NOI}$ 开幕了！设立 $x$ 枚金牌，$y$ 枚银牌，$z$ 枚铜牌。
- 有 $x+y+z$ 个 $\text{CCF}$ 的崇拜者立下誓言，只要拿到 $\text{Au/Ag/Cu}$ 就给 $\text{CCF}$ 好多好多 $\text{money}$，分别有 $a_i$ 元，$b_i$ 元，$c_i$ 元！
- 求问 $\text{CCF}$ 最多能拿多少元。
- $x+y+z\le 10^5$。

**分析**
- 套路地给出 $\text{naive}$ 贪心：每次给币最多的那个牌牌（设 $n=x+y+z$）。
- 但是转移的时候可能会有点蒙对吧，因为转移有两个，转移中还可能引发别的转移。
- 幸运的是，这样的担心是不必要的，因为你可以先支付给 $\text{CCF}$ $\sum c_i$ 元，然后就不必考虑拿 $\text{Cu}$ 的情况了。
- 现在变成了选出 $x$ 名 $\text{Au}$ 元获得 $a_i-c_i$，和 $y$ 名 $\text{Ag}$ 获得 $b_i-c_i$ 元。
- 我们很容易知道一个人拿 $\text{Au}$ 更好还是拿 $\text{Ag}$ 更好，度量的方法就是 $a_i-b_i$ 的大小，所以对于已经挑选出的 $x+y$ 人的方案，我们可以将 $a_i-b_i$ 由大到小排序，将前 $x$ 人设为 $\text{Au}$ 一定是较优的方案。
- 那么对于一般的情况，我们也将 $a_i-b_i$ 由大到小排序（这样可以保证我们插入的总是末尾），然后我们需要满足两个基本的性质：每次决策时，都是当前的最优解，更新决策时，只是对当前的解进行微调可以得到新的最优解。
- 我们似乎可以自然地想到一个策略，如果插入的还有空位，直接在空位处插入即可，否则计算换掉一个 $\text{Au}$ 的代价和换掉一个 $\text{Ag}$ 的代价，取较小值更新。
- 这样的操作可能的问题是什么？在于换掉一个 $\text{Au}$ 后，可能增加的 $a_i-b_i$ 又使得之前某个被换掉的 $\text{Ag}$ 选手~~大喊一声优势在我~~然后蹦回来成了 $\text{Au}$。
- 不过这是容易解决的（虽然作者一开始没想到），我们可以按 $a_i-b_i$ 从大到小排序，维护前缀的 $\text{Au}$ 和后缀的 $\text{Ag}$ 然后扫一遍取较小值即可，并不会出现 $\text{Cu}$ 选手诈尸的问题。
- 复杂度 $O(n\log n)$。
- [代码实现](https://www.luogu.com.cn/paste/rdjahvd3)。

---

## 作者：Jsxts_ (赞：13)

这是一个非常暴力无脑的思路。

先把费用流的模型建出来，具体如下图（$S$ 到 $1\sim n$ 其实是 $(1,0)$）：
![](https://cdn.luogu.com.cn/upload/image_hosting/l0lqqz7o.png)

由于 $n$ 很大，不能真的跑费用流，这个时候就需要反悔贪心或者模拟费用流。

这里没看到 $X+Y+Z=n$ 的特殊性质，之前有一道 CF730I 只有两种权值，可以通过维护 $4$ 个堆维护所有路径的最大值，所以这题也可以用类似的方法，用 $k^2=9$ 个堆维护即可！

考虑所有本质不同的路径，分别是经过 A、B、C 中的一个点、两个点和三个点，共有 $3 + 6 + 6 = 15$ 种。我们可以把这些路径拆成几段好维护的路径，把相同类型的路径存在一个堆里，每次增广 $1$ 单位的流量，找到费用最大的一条，再根据这条路径更新堆中的信息，直到 $A,B,C\rightarrow T$ 的三条路径全部满流。

具体的实现比较恶心，强烈建议如果要写的话要自己推，这里给出一些参考的维护方法。
```cpp
priority_queue<node> qa,qb,qc,qab,qac,qba,qbc,qca,qcb;
```

这里的 $9$ 个堆中，qa 存从 $1\sim n$ 到 $A$ 的路径权值，qab 存从 $A$ 到 $B$ 的权值，以此类推。这样就可以通过若干堆的堆顶相加得到一条最优的路径（如 $S\rightarrow A \rightarrow B \rightarrow C \rightarrow T$ 可以用 $a + ab + bc$ 表示，其中 $a,ab,bc$ 分别表示各自堆的最大值），然后将这 $15$ 种拼出来的路径都放在一起取最大值得到这一次增广的答案。注意如果某条路径的结尾已经满流，就不能把这条路径计入最大值。

真正恶心的在得到路径之后如何更新堆中信息。我这里只举一个例子，因为把所有 $15$ 种全部讨论完实在太多了。

例如假设现在选定一条路径 $S\rightarrow A \rightarrow B \rightarrow T$，假设是这一条：
![](https://cdn.luogu.com.cn/upload/image_hosting/eto62lif.png)
那么就会存在 $B \rightarrow 2, 2 \rightarrow A,A\rightarrow 1$ 的反向边，所以会多出的新路径有：$A\rightarrow1\rightarrow B,A\rightarrow1\rightarrow C,B\rightarrow2\rightarrow A,B\rightarrow 2 \rightarrow C$，加入对应堆即可。注意 $A\rightarrow1\rightarrow B$ 的权值为 $b_1-a_1$，因为 $1\sim A$ 这条边是反向的，是反向就说明之前有一个正向的流经过，即 $a_1$ 的权值已经计算进答案内，这里类似一个反悔的操作。其他路径类似。

注意 $1\sim n$ 每个点至多只有 $1$ 条反向边，所以不需要急着删除不合法的路径，我们可以记录每个点的反向边有没有，如果有是从 $ABC$ 哪里来的，就可以在取堆顶的时候直接删除不合法的路径。

代码很丑，调了一个上午，对于这题完全没有必要这么写，但是 $X+Y+Z\neq n$ 的时候就会起到作用。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 1e18;
inline ll read() {
	ll s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
#define mp make_pair
#define se second
typedef pair<ll,int> pli;
int X,Y,Z,n,vis[100010];
//vis[i]:0无反向边 1A的反向边 2B的反向边 3C的反向边 
struct node {
	ll x,i;
	friend node operator - (node a,node b) {
		return (node){a.x - b.x,a.i};
	}
	friend node operator + (node a,node b) {
		return (node){a.x + b.x,a.i};
	}
	bool operator < (const node &a) const {
		return x == a.x ? i < a.i : x < a.x;
	}
//	bool operator > (const node &a) const {
//		return x > a.x;
//	}
}A[100010],B[100010],C[100010];
priority_queue<node> qa,qb,qc,qab,qac,qba,qbc,qca,qcb;
pli Max(int f,node a,node b,node c,node d,node e) {
	return max({mp(a.x,1+f),mp(b.x,2+f),mp(c.x,3+f),mp(d.x,4+f),mp(e.x,5+f)});
}
void ua(int i) {qa.push(A[i]);}//更新堆 
void ub(int i) {qb.push(B[i]);}
void uc(int i) {qc.push(C[i]);}
void uab(int i) {qab.push(B[i] - A[i]);}
void uac(int i) {qac.push(C[i] - A[i]);}
void uba(int i) {qba.push(A[i] - B[i]);}
void ubc(int i) {qbc.push(C[i] - B[i]);}
void uca(int i) {qca.push(A[i] - C[i]);}
void ucb(int i) {qcb.push(B[i] - C[i]);}
int main() {
//	freopen("subtask_1_02.txt","r",stdin);
	X = read(), Y = read(), Z = read();
	n = X + Y + Z;
	for (int i = 1;i <= n;i ++ ) {
		A[i].x = read(), B[i].x = read(),C[i].x = read();
		A[i].i = B[i].i = C[i].i = i;
		qa.push(A[i]), qb.push(B[i]), qc.push(C[i]);//一开始只有到A/B/C的路径，因为反向边还没有出现 
	}
	int la = X,lb = Y,lc = Z;
	ll ans = 0;
	while (la || lb || lc) {
		node a = {-inf,0},b = {-inf,0},c = {-inf,0},ab = {-inf,0},ac = {-inf,0},ba = {-inf,0},bc = {-inf,0},ca = {-inf,0},cb = {-inf,0};
		while (!qa.empty() && vis[qa.top().i] != 0) qa.pop();//去掉不合法 
		while (!qb.empty() && vis[qb.top().i] != 0) qb.pop();
		while (!qc.empty() && vis[qc.top().i] != 0) qc.pop();
		while (!qab.empty() && vis[qab.top().i] != 1) qab.pop();
		while (!qac.empty() && vis[qac.top().i] != 1) qac.pop();
		while (!qba.empty() && vis[qba.top().i] != 2) qba.pop();		
		while (!qbc.empty() && vis[qbc.top().i] != 2) qbc.pop();
		while (!qca.empty() && vis[qca.top().i] != 3) qca.pop();
		while (!qcb.empty() && vis[qcb.top().i] != 3) qcb.pop();
		if (!qa.empty()) a = qa.top();
		if (!qb.empty()) b = qb.top();
		if (!qc.empty()) c = qc.top();
		if (!qab.empty()) ab = qab.top();
		if (!qac.empty()) ac = qac.top();
		if (!qba.empty()) ba = qba.top();
		if (!qbc.empty()) bc = qbc.top();
		if (!qca.empty()) ca = qca.top();
		if (!qcb.empty()) cb = qcb.top();
		pli ta = Max(0,a,b + ba,c + ca,b + bc + ca,c + cb + ba),tb = Max(5,b,a + ab,c + cb,a + ac + cb,c + ca + ab),tc = Max(10,c,a + ac,b + bc,a + ab + bc,b + ba + ac);
		pli res = {-inf,0};
		if (la) res = max(res,ta);//有流量才能贡献到最大值 
		if (lb) res = max(res,tb);
		if (lc) res = max(res,tc);
		if (res.first <= 0) break;
		ans += res.first;
		int x = res.second;//对于选出的路径分类讨论 
		if (x <= 5) {
			la --;
			if (x == 1) uab(a.i), uac(a.i), vis[a.i] = 1;
			if (x == 2) uab(ba.i), uba(b.i), ubc(b.i), vis[b.i] = 2, vis[ba.i] = 1, uac(ba.i);
			if (x == 3) uac(ca.i), uca(c.i), ucb(c.i), vis[c.i] = 3, vis[ca.i] = 1, uab(ca.i);
			if (x == 4) uba(b.i), ubc(b.i), ucb(bc.i), uac(ca.i), vis[b.i] = 2, vis[bc.i] = 3, vis[ca.i] = 1, uca(bc.i), uab(ca.i);
			if (x == 5) uca(c.i), ucb(c.i), ubc(cb.i), uab(ba.i), vis[c.i] = 3, vis[cb.i] = 2, vis[ba.i] = 1, uac(ba.i), uba(cb.i);
		}
		else if (x <= 10) {
			lb --;
			if (x == 6) uba(b.i), ubc(b.i), vis[b.i] = 2;
			if (x == 7) uba(ab.i), uab(a.i), uac(a.i), vis[a.i] = 1, vis[ab.i] = 2, ubc(ab.i);
			if (x == 8) ubc(cb.i), uca(c.i), ucb(c.i), vis[c.i] = 3, vis[cb.i] = 2, uba(cb.i);
			if (x == 9) uab(a.i), uac(a.i), uca(ac.i), ubc(cb.i), vis[a.i] = 1, vis[ac.i] = 3, vis[cb.i] = 2, ucb(ac.i), uca(cb.i);
			if (x ==10) uca(c.i), ucb(c.i), uac(ca.i), uba(ab.i), vis[c.i] = 3, vis[ca.i] = 1, vis[ab.i] = 2, uab(ca.i), ubc(ab.i);
		}
		else if (x <= 15) {
			lc --;
			if (x == 11) uca(c.i), ucb(c.i), vis[c.i] = 3;
			if (x == 12) uca(ac.i), uab(a.i), uac(a.i), vis[a.i] = 1, vis[ac.i] = 3, ucb(ac.i);
			if (x == 13) ucb(bc.i), uba(b.i), ubc(b.i), vis[b.i] = 2, vis[bc.i] = 3, uca(bc.i);
			if (x == 14) uab(a.i), uac(a.i), uba(ab.i), ucb(bc.i), vis[a.i] = 1, vis[ab.i] = 2, vis[bc.i] = 3, ubc(ab.i), uca(bc.i);
			if (x == 15) uba(b.i), ubc(b.i), uab(ba.i), uca(ac.i), vis[b.i] = 2, vis[ba.i] = 1, vis[ac.i] = 3, uac(ba.i), ucb(ac.i);
		}
	}
	cout << ans;
	return 0;
}
```

虽然不是最优解法，但是也有价值。

---

## 作者：Soulist (赞：12)

考虑强制拿走所有人的$c$类币并获得收益，考虑选择其他币种对答案的变化量

可以发现选择$a$和$b$的变化量为$a_i-c_i,b_i-c_i$

于是问题转化为给定$n$个二元组，从中选出$x$个$a$和$y$个$b$使得答案最大

于是可以建出一个网络流的模型：

具体连边是额外建出两个点表示选$a$和选$b$用流量限制次数，跑最大费用最大流即可

然后这样肯定会$T$

仔细思考会发现可以让其单向增广，即每次只额外流$1$的流量，然后每次流最大的代价即可

不难发现目的是要用贪心来模拟网络流，所以写一个反悔型贪心即可

就增加两个堆表示反向边即可，模拟起来就分类讨论：

$1.$直接流

$2.$流反向边

$3.$某一个虚拟点(额外建出的点)达到流量上限

一共是$3*2=6$种情况

复杂度$O(n\log n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long
#define inf 123456789
int read() {
    char cc = getchar(); int cn = 0, flus = 1;
    while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
    while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
    return cn * flus;
}
const int N = 500000 + 5 ; 
int n, A, B, C, Ans, num, vis[N]; 
struct Node {
    int a, b, c ;
} s[N];
struct node {
    int val, id ;
    bool operator < ( const node& x ) const {
        return val < x.val ; 
    }
};
priority_queue<node> qA, qB, QA, QB ;
signed main()
{
	A = read(), B = read(), C = read() ; int x, y, z ; 
	n = A + B + C ; 
    rep( i, 1, n ) x = read(), y = read(), z = read(), num += z,
        s[i].a = x - z, s[i].b = y - z, 
        QA.push((node){ s[i].a, i }), QB.push((node){ s[i].b, i }) ;
    int con = 0 ;
    while( 1 ) {
        node u1 = QA.top(); node u2 = QB.top() ; 
        int cnt1 = 0, cnt2 = 0 ;
        while( vis[u1.id] ) QA.pop(), u1 = QA.top() ;
        while( vis[u2.id] ) QB.pop(), u2 = QB.top() ; 
        int toA = u1.val, frA = u1.id, toB = u2.val, frB = u2.id;
        int f1 = 0, f2 = 0 ; 
        if( qB.size() ) {
            cnt1 = qB.top().val ;
            if( ( toA < cnt1 + u2.val ) ) toA = cnt1 + u2.val, f1 = 1 ;
        }
        if( qA.size() ) {
            cnt2 = qA.top().val ;
            if( ( toB < cnt2 + u1.val ) ) toB = cnt2 + u1.val, f2 = 1 ;
        }
        if( qA.size() == A ) {
            Ans += toB ; 
            if( f2 )
                qA.pop(), qB.push((node){ -cnt2, 0 }), qA.push((node){s[u1.id].b - s[u1.id].a, 0}), vis[u1.id] = 1 ;
            else
                qB.push((node){s[u2.id].a - s[u2.id].b}), vis[u2.id] = 1 ;
        }
        else if( qB.size() == B ) {
            Ans += toA ; 
            if( f1 )
                qB.pop(), qA.push((node){ -cnt1, 0 }), qB.push((node){s[u2.id].a - s[u2.id].b, 0}), vis[u2.id] = 1 ;
            else qA.push((node){s[u1.id].b - s[u1.id].a, 0}), vis[u1.id] = 1 ;
        }
        else if( toA < toB ) {
            Ans += toA ; 
            if( f1 ) 
                qB.pop(), qA.push((node){ -cnt1, 0 }), qB.push((node){s[u2.id].a - s[u2.id].b, 0}), vis[u2.id] = 1 ;
            else qA.push((node){s[u1.id].b - s[u1.id].a, 0}), vis[u1.id] = 1 ; ;
        }
        else {
            Ans += toB ; 
            if( f2 )
                qA.pop(), qB.push((node){ -cnt2, 0 }), qA.push((node){s[u1.id].b - s[u1.id].a, 0}), vis[u1.id] = 1 ;
            else
                qB.push((node){s[u2.id].a - s[u2.id].b}), vis[u2.id] = 1 ;
        }
        if( ( qA.size() == A ) && ( qB.size() == B ) ) break ; 
    }
    printf("%lld\n", Ans + num ) ; 
    return 0;
}
```

---

## 作者：逃离地球 (赞：10)

一道挺不错的贪心题，部分分能很大程度地帮助思考。

### 部分分 1: $X=0$

对于 $X=0$ 的部分，其实就是给你一堆二元组，让你分组，使得 $\sum y_i+\sum z_i$ 最大。

这是一个挺经典的贪心，考虑两个二元组 $(y_i,z_i)$ 和 $(y_j, z_j)$，若 $y_i+z_j>z_i+y_j$，则有 $y_i-z_i>y_j-z_j$，即 $y-z$ 更大的二元组选 $y$ 一定更优。所以把这些二元组按 $y-z$ 从小到大排序，最大的 $Y$ 个选成 $y$，剩下的选成 $z$ 即可。

### 部分分 2：$x_i=0$

这个部分分和上一个的区别，其实就是不需要选所有的二元组，只需要选出 $Y+Z$ 组。

但是上个部分分证明的性质依然成立，即选 $y$ 的二元组的 $y-z$ 一定比选 $z$ 的大。那么如果依旧把这些二元组按 $y-z$ 从小到大排序，一定不会有某个选 $z$ 的二元组在某个选 $y$ 的二元组的右边。

考虑枚举中间点，所有选 $z$ 的都在这个中间点的左边，所有选 $y$ 的都在这个中间点右边。考虑最大化答案，就是在这个中间点左边选出 $z$ 最大的 $Z$ 个二元组，在右边选出 $y$ 最大的 $Y$ 个二元组即可。

计算这玩意是一个曾经见过的 trick，扫一遍，维护一个堆，计算当前选的数中的最小值，和新扫到的数比较大小即可。然后正反都扫一遍就行。~~但我还是想了半天~~

### 正解：

考虑把 $x_i\ne 0$ 的情况转化为 $x_i=0$ 的情况，只需要把所有二元组的 $y$ 和 $z$ 减去 $x$，然后像上一个部分分一样计算，然后最后在答案里加上 $\sum x$ 即可。

---

## 作者：EXODUS (赞：7)

# Part 1：前言
100 年前模拟赛的题，突然随机跳题跳到了 qwq。

下文中，我们称获得金币的人的集合为 $X$，银币的集合为 $Y$，铜币的集合为 $Z$。

# Part 2：正文

首先考虑把三元的限制条件转换为二元的限制条件。注意到最后答案中 $X,Y,Z$ 中的元素**只取决于 $A_i,B_i,C_i$ 的相对大小**，那么不妨让 $A_i=A_i-C_i,B_i=B_i-C_i,C_i=0$，由上可知 $X,Y,Z$ 集合中的元素依然不变。

问题转化成有 $n$ 个二元组，第 $i$ 个为 $(A_i,B_i)$，从中选择 $a$ 个二元组使答案加 $A_i$，$b$ 个二元组使答案加 $B_i$，且每个二元组只能被选择之多一次，求最大价值（最后统计答案只需要加上 $\sum c_i$ 即可）。

再对 $A_i-B_i$ 从大到小排序，则被选入 $X$ 集合的一定在被选进 $Y$ 集合的前边，于是可以枚举分界点 $i$ 使得前 $i$ 个元素均选入 $X$ 集合或 $Z$ 集合，后 $n-i+1$ 的元素全部选入 $Y$ 集合或 $Z$ 集合，这可以用小根堆维护，具体见代码。

# Part 3：代码

早期代码，码风丑陋，讲究着看吧qwq。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+20;
int s;
struct Pre{
	int a,b,c;
}p[N];
int n,a,b,c;
int cnt;
bool cmp(Pre x,Pre y){
	return x.b-x.a<y.b-y.a;
}
int sum,ans;
int fac[N],fbc[N];
priority_queue<int,vector<int>,greater<int>>q;
signed main()
{
	scanf("%lld%lld%lld",&a,&b,&c);
	n=a+b+c;
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&p[i].a,&p[i].b,&p[i].c);
		sum+=p[i].c;
	}
    sort(p+1,p+n+1,cmp);
    cnt=0;
    while(!q.empty()) q.pop();
    for(int i=1;i<=a;i++){
    	q.push(p[i].a-p[i].c);
    	cnt+=p[i].a-p[i].c;
	}
	fac[a]=cnt;
	for(int i=a+1;i<=n;i++){
		cnt+=p[i].a-p[i].c;
		q.push(p[i].a-p[i].c);
		cnt-=q.top();
		q.pop();
		fac[i]=cnt;
	}
	while(!q.empty()){
		q.pop();
	}
	cnt=0;
	for(int i=n;i>=n-b+1;i--){
		q.push(p[i].b-p[i].c);
		cnt+=p[i].b-p[i].c;
	}
	fbc[n-b+1]=cnt;
	for(int i=n-b;i;i--){
		cnt+=p[i].b-p[i].c;
		q.push(p[i].b-p[i].c);
		cnt-=q.top();
		q.pop();
		fbc[i]=cnt;
	}
	for(int i=a;i<=n-b;i++){
		ans=max(ans,sum+fac[i]+fbc[i+1]);
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：Delov (赞：5)

~~这个题我一上来就拿六个堆乱冲然后挂掉了~~

题目里，所有人都是要被选的，三种颜色不是很好做，考虑转化一下，我们先强制所有人都选同一种。例如先强制所有人都选了金，那么接下来要做的就是把 $Y$ 个人变成选银，$Z$ 个人变成选铜。

当所有人都被强制选金后，一个人从金变银的贡献是 $b-a$，从金变铜是 $c-a$，那么现在问题就被转化成了 $n$ 个人中选出 $Y$ 个人做第一种贡献，$Z$ 个人做第二种贡献，于是就可以直接套路用堆维护反悔贪心了，与[CF730I](https://www.luogu.com.cn/problem/CF730I)这道题就是一模一样的了，先按第一种贡献排序钦定 $Y$ 个人，然后再用反悔操作选出第二种贡献的 $Z$ 个人即可。

### Code
```cpp

#include <bits/stdc++.h>
typedef long long ll;typedef unsigned long long ull; typedef double db;typedef long double ldb;
#define fre(x) freopen(#x ".in","r",stdin),freopen(#x ".out","w",stdout)
#define Rep(i,a,b) for(int i=a;i<=b;++i) 
#define Dwn(i,a,b) for(int i=a;i>=b;--i)
#define pii pair<int,int>
#define mair make_pair
#define fir first
#define sec second
#define int ll
using namespace std;

const int maxn=1e5+10,INF=1e15;

int n,X,Y,Z;
ll ans=0;
struct Per{
	int a,b,c,id;
	bool operator<(const Per &rhs)const{return b-a>rhs.b-rhs.a;}
}P[maxn];

struct Ver{ int w,id; bool operator<(const Ver &rhs)const{return w<rhs.w;} };
priority_queue<Ver>q1,q2,q3;
bool ina[maxn],inb[maxn];

void solve(){
	cin>>X>>Y>>Z;n=X+Y+Z;
	Rep(i,1,n)cin>>P[i].a>>P[i].b>>P[i].c,ans+=P[i].a;
	sort(P+1,P+n+1);
	Rep(i,1,Y){
		ans+=P[i].b-P[i].a;
		ina[i]=true;q3.push(Ver{P[i].c-P[i].b,i});
	}
	Rep(i,Y+1,n){ q1.push(Ver{P[i].b-P[i].a,i}),q2.push(Ver{P[i].c-P[i].a,i}); }
	q1.push(Ver{-INF,0}),q2.push(Ver{-INF,0}),q3.push(Ver{-INF,0});
	Rep(i,1,Z){
		while(!q1.empty() &&(ina[q1.top().id] || inb[q1.top().id]))q1.pop();
		while(!q2.empty() &&(inb[q2.top().id] || ina[q2.top().id]))q2.pop();
		while(!q3.empty() &&(!ina[q3.top().id]))q3.pop();
		int val1=q2.top().w,val2=q1.top().w+q3.top().w;
		if(val1>=val2){
			ans+=val1;inb[q2.top().id]=true;
			q2.pop();
		}else{
			ans+=val2;
			ina[q3.top().id]=false,inb[q3.top().id]=true;q3.pop();
			ina[q1.top().id]=true;int x=q1.top().id;q3.push(Ver{P[x].c-P[x].b,x});q1.pop();
		}
	}
	cout<<ans<<"\n";
}
#undef int
int main (){ ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);return solve(),0; }


```

---

## 作者：小木虫 (赞：3)

### Preface  
一道标准的模拟网络流（费用流）题目，蒟蒻第一次做反悔贪心。  
### Problem  
有 $x+y+z$ 个人，第 $i$ 个人有 $A_i$ 个金币，$B_i$ 个银币，$C_i$ 个铜币。 	选出 $x$ 个人获得其金币，选出 $y$ 个人获得其银币，选出 $z$ 个人获得其铜币，在不重复选某个人的情况下，最大化获得的币的总数。 $x+y+z\leq 10^5$
### Solution  
其实看到这种有后效性的决策题目的时候我们首先想到的应该是网络流，比如像这道题，我们就可以立刻建出一个费用流模型，但是这道题的数据范围很鬼畜，很明显朴素的费用流是跑不过去的。  

这个时候我们就不得不仔细思考一下费用流的本质了，对于一个分配完毕的网络，费用流可以通过若干次推流操作来增大收益，这个推流的过程实际上就是对物品进行重分配。  

那我们就有一个问题了，既然费用流要在图上跑很久才能出结果，我们能不能直接模拟物品重分配来减小复杂度呢？根据题意，我们的重分配方案一共五种：  
```
a->b b->c c->a  
a->c c->b b->a  
a->c c->a  
a->b b->a  
b->c c->b 
```
其中三个字母分别代表不同币种。  
其中 -> 表示一个原本用在一个币种的人转换到另外一个币种，很显然这些人对空间是本质相同的，所以我们可以分别选择最优的人进行求解。  

举个例子，上文中第一行重分配方式，我们就可以先选择从金币到银币贡献最大者，然后选择银币到铜币贡献最大者，最后选择铜币到金币贡献最大者。  

然后我们发现这个过程其实可以用六个堆进行模拟，直到无流可退我们就结束计算。  

最后我们还有一个疑问：上述的过程叫反悔贪心，但是普通费用流复杂度为 $O(nmf)$，反悔贪心能减少多少的复杂度，可以降低到通过的级别吗？  

这就不得不说反悔的具体次数了，很显然我们将反悔一次的复杂度降为了 $O(\log n)$，那么只要反悔次数是线性级别我们就可以通过本题，我们分类讨论一下，两个元素相互交换的反悔显然每次会将两个乱序的元素重排，最多执行总人数次。三个元素互相交换的反悔的情况下同样会将三个乱序元素进行重排，同理。  
code：  
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,x,y,z,sum;
int a[N],b[N],c[N];int st[N];
struct node{
	int id,data;
	bool operator <(const node &a)const{
		return data<a.data;
	}
};
node nmax(node a,node b){
	if(a.data<b.data)return b;
	else return a;
}
priority_queue <node> Q[7];
//a->b b->c c->a
//a->c c->b b->a
//a->c c->a
//a->b b->a
//b->c c->b
int mo[N][7];
void update(int x){
	Q[st[x]*2-1].push((node){x,mo[x][st[x]*2-1]});
	Q[st[x]*2].push((node){x,mo[x][st[x]*2]});
}
void modify(int x){
	if(x==1||x==4)st[Q[1].top().id]=2;
	if(x==2||x==3)st[Q[2].top().id]=3;
	if(x==1||x==5)st[Q[4].top().id]=3;
	if(x==2||x==4)st[Q[3].top().id]=1;
	if(x==2||x==5)st[Q[6].top().id]=2;
	if(x==1||x==3)st[Q[5].top().id]=1;
	update(Q[1].top().id);update(Q[2].top().id);
	update(Q[3].top().id);update(Q[4].top().id);
	update(Q[5].top().id);update(Q[6].top().id);
}
signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>x>>y>>z;n=x+y+z;
    for(int i=1;i<=x;i++){
    	cin>>a[i]>>b[i]>>c[i];st[i]=1;sum+=a[i];
		Q[1].push((node){i,b[i]-a[i]});Q[2].push((node){i,c[i]-a[i]});
	}
	for(int i=x+1;i<=x+y;i++){
    	cin>>a[i]>>b[i]>>c[i];st[i]=2;sum+=b[i];
    	Q[3].push((node){i,a[i]-b[i]});Q[4].push((node){i,c[i]-b[i]});
	}
	for(int i=x+y+1;i<=x+y+z;i++){
    	cin>>a[i]>>b[i]>>c[i];st[i]=3;sum+=c[i];
    	Q[5].push((node){i,a[i]-c[i]});Q[6].push((node){i,b[i]-c[i]});
	}
	for(int i=1;i<=n;i++){
		mo[i][1]=b[i]-a[i];mo[i][2]=c[i]-a[i];
		mo[i][3]=a[i]-b[i];mo[i][4]=c[i]-b[i];
		mo[i][5]=a[i]-c[i];mo[i][6]=b[i]-c[i];
	}
	while(true){
		//a->b b->c c->a
		//a->c c->b b->a
		//a->c c->a
		//a->b b->a
		//b->c c->b
		int ab=-1e18;int ac=-1e18;int ba=-1e18;
		int bc=-1e18;int ca=-1e18;int cb=-1e18;
		for(int i=1;i<=6;i++){
			while(!Q[i].empty()&&st[Q[i].top().id]!=((i+1)/2))
				Q[i].pop();
		}
		if(!Q[1].empty())ab=Q[1].top().data;
		if(!Q[2].empty())ac=Q[2].top().data;
		if(!Q[3].empty())ba=Q[3].top().data;
		if(!Q[4].empty())bc=Q[4].top().data;
		if(!Q[5].empty())ca=Q[5].top().data;
		if(!Q[6].empty())cb=Q[6].top().data;
		node res=nmax(nmax(nmax(nmax((node){4,ab+ba},(node){5,bc+cb})
		,(node){3,ac+ca}),(node){2,ac+cb+ba}),(node){1,ab+bc+ca});
		if(res.data<=0)break;sum+=res.data;modify(res.id);
	}
	cout<<sum;
}
```


---

## 作者：Krimson (赞：3)

碰到这种强制选 $k$ 个下的条件，很容易想到~~暴力枚举~~wqs二分。  
此题要求的是强制选 $x$ 个 $a$ ，$y$ 个 $b$,$z$ 个 $c$，发现可以先默认全部选 $c$，再将 $a$ 和 $b$ 改为 $a-c,b-c$ ，就变成了从 $n$个中选 $x$ 个 $a$  和 $y$ 个 $b$，两者是等价的。  
~~感性理解一下~~在$x$ 固定的时候，得到的硬币个数关于 $y$ 是个上凸函数， 而 $y$ 固定的时候 $x$ 同理。  
~~按照套路~~可以去二分最高点的斜率，先二分 $x$ 再二分 $y$ 。  
整个过程是wqs二分的套路，这里就不再赘述了。    

## _Code_  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
#define ui unsigned int
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il int read(char *s){
    int len=0;
    register char ch=getchar();
    while(ch==' '||ch=='\n') ch=getchar();
    while(ch!=' '&&ch!='\n'&&ch!=EOF) s[++len]=ch,ch=getchar();
    return len;
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il ll max(const ll &a,const ll &b){return a>b?a:b;}
il ll min(const ll &a,const ll &b){return a<b?a:b;}
ll x,y,z;
const int MAXN=1e5+7;
ll f,p,q;
ll a[MAXN],b[MAXN],c[MAXN],n,ans,res;
ll ma,mb;
bool checkb(){
    f=p=q=0;
    for(ri i=1;i<=n;++i){
        if(a[i]+ma>b[i]+mb){
            if(a[i]+ma>0) ++p,f+=a[i]+ma;
        }
        else{
            if(b[i]+mb>0) ++q,f+=b[i]+mb;
        }
    }
    return q<=y;
}
bool checka(){
    ll l=-1e9,r=1e9,md=1e9;
    while(l<=r){
        mb=(l+r)>>1;
        if(checkb()){
            md=mb;
            l=mb+1;
        }
        else r=mb-1;
    }
    mb=md;
    checkb();
    return p<=x;
}
int main(){
    x=read(),y=read(),z=read(),n=x+y+z;
    for(ri i=1;i<=n;++i){
        a[i]=read(),b[i]=read(),c[i]=read();
        a[i]-=c[i],b[i]-=c[i],res+=c[i];
    }
    ll l=-1e9,r=1e9;
    while(l<=r){
        ma=(l+r)>>1;
        if(checka()){
            ans=f-x*ma-y*mb;
            l=ma+1;
        }
        else r=ma-1;
    }
    print(ans+res);
    return 0;
}
```



---

