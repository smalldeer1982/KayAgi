# [USACO18DEC] Balance Beam P

## 题目描述

Bessie为了存钱给她的牛棚新建一间隔间，开始在当地的马戏团里表演，通过在平衡木上小心地来回走动来展示她卓越的平衡能力。

Bessie能够通过表演赚到的钱取决于她最终成功跳下平衡木的位置。平衡木上从左向右的位置记为 $ 0,1,\ldots,N+1 $ 。如果Bessie到达了位置 $ 0 $ 或是 $ N+1 $ ，她就会从平衡木的一端掉下去，遗憾地得不到报酬。

如果Bessie处在一个给定的位置 $ k $ ，她可以进行下面两项中的任意一项：

1. 投掷一枚硬币。如果背面朝上，她前往位置 $ k-1 $ ，如果正面朝上，她前往位置 $ k+1 $ （也就是说，每种可能性 $ 1/2 $ 的概率）。

2. 跳下平衡木，获得 $ f(k) $ 的报酬（ $ 0 \leq f(k) \leq 10^9 $ ）。

Bessie意识到她并不能保证结果能够得到某一特定数量的报酬，这是由于她的移动是由随机的掷硬币结果控制。然而，基于她的起始位置，她想要求出当她进行一系列最优的决定之后，她能够得到的期望报酬（“最优”指的是这些决定能够带来最高可能的期望报酬）。

例如，如果她的策略能够使她以 $ 1/2 $ 的概率获得 $ 10 $ 的报酬，$ 1/4 $ 的概率获得 $ 8 $ 的报酬，$ 1/4 $ 的概率获得 $ 0 $ 的报酬，那么她的期望报酬为加权平均值 $ 10 \times (1/2)+8 \times (1/4)+0 \times (1/4)=7 $ 。

## 样例 #1

### 输入

```
2
1
3```

### 输出

```
150000
300000
```

# 题解

## 作者：Mirach (赞：36)

[你真的不想点进来看一看吗](https://www.cnblogs.com/penth/p/10246357.html)

（翻了翻其他的题解，觉得它们没讲清楚为什么一定选择两个点作为决策结束点）

~~我相信很多通过了这道题的人都没有弄清楚这个策略的正确性~~

Problem
-------

题意概要：给定一个长为$n$的序列，可以选择以$\frac 12$的概率进行左右移动，也可以结束并得到当前位置上的收益，求从每个位置开始时使用最优策略的最大期望收益是多少

$n\leq 10^5$

Solution
-------

关键在于需要考虑当前是选择移动还是直接结束。一个很明了的观点：如果当前移动后的收益期望比当前位置的收益大，那么会选择移动；否则选择直接停止。直接停止的贡献已经知道，那么要求的就是当前点选择移动操作后的收益期望

------

有一个结论：在长度为$L$的数轴上的位置$x$处，每次进行左右移动（左右概率都为$\frac 12$），若到达$0$或$L$即停止，则到达$0$停止的概率为$\frac {L-x}L$，到达$L$停止的概率为$\frac xL$

关于这个结论的证明，考虑设在 $i$ 开始，到$L$停止的概率为$f_i$，由题可得$f_i=\frac {f_{i-1}+f_{i+1}}2$，不难发现这个方程是等差数列的描述，又由$f_0=0,f_L=1$可得$f_i=\frac xL$，即可得到上面的结论

这个结论的用处后面再说

-------

假设我们已知一些节点移动的期望收益比当前点停止的收益低，即如果进行随机游走，一旦到达这些点，一个极端聪明的人是绝不会继续移动的，设这些点为停止点

会发现，如果从 $i$ 出发进行移动，那么移动的期望收益一定是由 $i$ 往前数第一个停止点和往后数第一个停止点贡献的

不妨设为 $a$ 和 $b$，由我们之前的结论可以得到到达 $a$ 停止的概率为$\frac {b-i}{b-a}$，到达 $b$ 停止的概率为$\frac {i-a}{b-a}$，由期望公式可得从 $i$ 出发进行随机移动的期望收益为 $E=v_a\cdot \frac {b-i}{b-a}+v_b\cdot \frac {i-a}{b-a}$，比划一下会发现这是满足物理里的杠杆模型的

现在我们得到了一个优秀的做法，就是对于每个点，找到其前后的第一个停止点，得到其移动的期望收益然后与自己的停止收益取最大值

-------

但如何求出所有的停止点呢？

进一步，画个图可知，设 $a$ 坐标为 $(a,v_a)$，$b$ 坐标为 $(b,v_b)$，则从 $i$ 出发进行移动的期望收益是 $a,b$ 所连线段与直线$x=i$的交点纵坐标，所有的停止点会满足在$x=i$时，$v_i$要比这条线段要高

不难发现若将所有停止点 $(i,v_i)$画出来一定成为一个凸包，反证法证明：若存在一个停止点在凸包内，则这个点的移动期望比停止期望大，也就是说这并不是一个停止点，与假设相悖，得证

所以为了得到所有的停止点，只要对所有的$(i,v_i)$求个凸包即可

（要看图的兄弟可以看楼下的~~，逃~~）

~~证明真有趣~~

Code
-------

```cpp
#include <bits/stdc++.h>
typedef long long ll;

inline void read(ll&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N=101000,bs=1e5;
int n,tp;

struct vec{
	int x;ll y;
	inline vec(){}
	inline vec(const int&X,const ll&Y):x(X),y(Y){}
	friend inline vec operator - (const vec&A,const vec&B) {return vec(A.x-B.x,A.y-B.y);}
	friend inline ll operator * (const vec&A,const vec&B) {return A.x*B.y-A.y*B.x;}
}p,st[N];

void push(vec p){
	while(tp&&(p-st[tp])*(st[tp]-st[tp-1])<=0)--tp;
	st[++tp]=p;
}

int main(){
	scanf("%d",&n);vec p;
	for(int i=1;i<=n;++i)p.x=i,read(p.y),p.y*=bs,push(p);
	push(vec(n+1,0));
	for(int i=1,j=0;i<=n;++i){
		while(j<tp&&st[j].x<i)++j;
		if(st[j].x==i)printf("%lld\n",st[j].y);
		else printf("%lld\n",((st[j].x-i)*st[j-1].y+(i-st[j-1].x)*st[j].y)/(st[j].x-st[j-1].x));
	}return 0;
}
```

---

## 作者：i207M (赞：6)

首先计算：从i一直行动，到0或n停止，到n停止的概率？

$f[0]=0,f[n+1]=1,f[i]=(f[i-1]+f[i+1])/2$

解得$f[i]=i/n$

对于每个点，最优策略要么是直接跳下去，要么是疯狂玩，然后直到到达两边某个点，跳下去。把每个点画到坐标轴上，然后发现收益呈现一种线性关系（相似三角形），于是我们求出凸包，对每个点求贡献即可。

![](https://cdn.luogu.com.cn/upload/pic/48119.png)

$a,b$对位置$x$的贡献：$\frac{f(a)(b-x)+f(b)(x-a)}{b-a}$

求凸包。

**注意：下取整对加法没有分配律...**


```cpp
il void ins(const Node &v)
{
	while(tp>1&&cross(st[tp]-st[tp-1],v-st[tp-1])) --tp;
	st[++tp]=v;
}
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
	// freopen("out.out","w",stdout);
#endif
	in(n);
	st[tp=1]=Node(0,0);
	for(ri i=1,t; i<=n; ++i)
	{
		in(t);
		ins(Node(i,t));
	}
	ins(Node(n+1,0));
	int p=1;
	const ull bas=100000;
	for(ri i=1; i<=n; ++i)
	{
		while(p<tp&&st[p+1].x<=i) ++p;
		if(st[p].x==i) printf("%llu\n",st[p].y*bas);
		else
		{
			ull a=st[p].x,b=st[p+1].x;
			ull ans=(st[p].y*bas*(b-i)+st[p+1].y*bas*(i-a))/(b-a);
			printf("%llu\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：_LHF_ (赞：3)

一道比较神仙的题目吧。

钦定 $f_0=f_{n+1}=0$

首先考虑一种特殊情况：当所有的 $f$ 构成了一个上凸函数的时候。

那么有 $f_{n}=\frac{f_{n-1}+f_{n+1}}{2}$，换而言之，不移动比移动一定更优。

于是这时直接 `printf("%d",f[i]);` 即可。

我们因此受到了启发。

考虑将所有的点 $(i,f_i)$ 算出一个凸包来。

那么对于凸包内的点，这个点的最优策略一定是跑到附近的两个凸包上的点。

首先给出一个结论：如果有一条长度为 $L$ 的线段，从 $x$ 出发随机往左或往右，跑到 $0$ 的概率是 $\frac{L-x}{L}$，跑到 $L$ 的概率是 $\frac{x}{L}$。

但为什么是凸包上的点呢？

假如现在有三个点 $a,b,c$，满足 $a<b<c$，其中 $a,c$ 是凸包上的点，而 $b$ 不是，现在有 $a<x<b$，那么假如计算到 $a,b$ 停止的话期望是 $\frac{f_a(b-i)+f_b(i-a)}{b-a}$，而到 $a,c$ 停止的期望是 $\frac{f_a(c-i)+f_c(i-a)}{c-a}$。

我们现在要比较 $\frac{f_a(b-i)+f_b(i-a)}{b-a}$ 和 $\frac{f_a(c-i)+f_c(i-a)}{c-a}$ 的大小关系。

而根据凸包推出来的结论有 $\frac{f_c-f_a}{c-a}>\frac{f_b-f_a}{b-a}$，而 $\frac{bf_a-af_b}{b-a}$ 和 $\frac{cf_a-af_c}{c-a}$ 的关系也可以通过做一点点小变化得出，于是就可以推出：$\frac{f_a(b-i)+f_b(i-a)}{b-a}<\frac{f_a(c-i)+f_c(i-a)}{c-a}$。

然后根据我们之前得出的“特殊情况”所以答案即为往左和往右的属于凸包上的点作为停止点的答案。

---

## 作者：CXY07 (赞：2)

> 题目链接：[\[USACO18DEC\] Balance Beam P](https://www.luogu.com.cn/problem/P5155)

> **本题解同步发布于 [My Blog](http://www.cxy07.blog/index.php/archives/125/)**

题意：

> 给定长度为 $n$ 的序列 $\{a_n\}$，初始有一个棋子在位置 $i$。每一轮可以选择结束游戏，获得当前所在节点的分数 $a_i$，也可以选择继续游戏，则棋子等概率移至 $i-1,i+1$，若走出序列则游戏结束，分数为 $0$。

> 对于 $i\in[1,n]$，求出初始棋子在 $i$，能得到的最大期望分数。

> $1\le n\le 10^5$。

好玩啊这题。

设 $E(x)$ 表示当前棋子在 $x$，所能得到的最大期望分数。那么显然：

$$
E(x)=\max(a_x,\dfrac{1}{2}(E(x-1)+E(x+1)))
$$

好像不是太好入手，那不妨从我们知道的东西来考虑：我们知道所有 $a_x$。

考虑一个集合 $S=\{x\ |\ E(x)=a_x\}$，那么对于集合中相邻两个元素 $p,q\ (p<q)$，所有 $x\in(p,q)$ 有 $E(x)-E(x-1)=E(x+1)-E(x)$。

因此 $E(x)=\dfrac{(x-p)\times a_p+(q-x)\times a_q}{q-p}$，这恰好就是过 $(p,a_p),(q,a_q)$ 两点的函数在 $x$ 处的取值。

所以答案就是点集 $(i,a_i)$ 的上凸壳，时间复杂度 $\mathcal{O}(n)$。

```cpp
//Code By CXY07
#include<bits/stdc++.h>
using namespace std;

//#define FILE
#define int long long
#define file(FILENAME) freopen(FILENAME".in", "r", stdin), freopen(FILENAME".out", "w", stdout)
#define randint(l, r) (rand() % ((r) - (l) + 1) + (l))
#define LINE() cout << "LINE = " << __LINE__ << endl
#define debug(x) cout << #x << " = " << x << endl
#define abs(x) ((x) < 0 ? (-(x)) : (x))
#define inv(x) qpow((x), mod - 2)
#define lowbit(x) ((x) & (-(x)))
#define ull unsigned long long
#define pii pair<int, int>
#define LL long long
#define mp make_pair
#define pb push_back
#define scd second
#define vec vector
#define fst first
#define endl '\n'

const int MAXN = 1e5 + 10;
const int INF = 2e9;
const double eps = 1e-6;
const double PI = acos(-1);
//const int mod = 1e9 + 7;
//const int mod = 998244353;
//const int G = 3;
//const int base = 131;

int n, m;
int s[MAXN], stk[MAXN], top, p = 1;
double Ans[MAXN];

template<typename T> inline bool read(T &a) {
	a = 0; char c = getchar(); int f = 1;
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') {a = a * 10 + (c ^ 48); c = getchar();}
	return a *= f, true;
}

template<typename A, typename ...B>
inline bool read(A &x, B &...y) {return read(x) && read(y...);}

double slope(int a, int b) { return 1. * (s[a] - s[b]) / (a - b); }

signed main () {
#ifdef FILE
	freopen("P5155.in", "r", stdin);
	freopen("P5155.out", "w", stdout);
#endif
	read(n);
	for(int i = 1; i <= n; ++i) read(s[i]), s[i] *= 1e5;
	for(int i = 0; i <= n + 1; ++i) {
		while(top > 1 && slope(stk[top - 1], stk[top]) < slope(stk[top - 1], i)) top--;
		stk[++top] = i;
	}
	for(int i = 1; i <= n; ++i) {
		while(stk[p + 1] <= i) ++p;
		Ans[i] = slope(stk[p], stk[p + 1]) * (i - stk[p]) + s[stk[p]];
		printf("%lld\n", (int)Ans[i]);
	}
	return 0;
}
```

---

## 作者：wenjing233 (赞：2)

分步证明，首先抛出结论：每个点的策略要么是不动，要么是随机移动直到左右两个点中的一个落下。  
#### 结论1：从点x开始在a和b之间移动在b落下的概率为 (x-a)/(b-a)   
设概率为f[x]=k,则f[a]=0,f[b]=1。因为x有1/2几率往左走或往右走，所以  
f[x]=(f[x-1]+f[x+1])/2  
即f(x)满足等差数列的性质，则图像为由(a,0),(b,1)组成的直线，做两条垂线做相似三角形即可。从b到a反过来即可。
#### 结论2：ans(x)=max(val[x],(val[a]×(b-x)/(b-a)+val[b]×(x-a)/(b-a))/2)
期望的基本概念，贡献×概率的平均数
#### 结论3：若最优策略为使一个点在两个停止点之间移动则停止点的连线为一个凸包
若一个在凸包内的点为停止点，则在该停止点的期望计算为它本身的贡献值，但实际上若以原本就在它两侧的停止点计算贡献使贡献更高（凸包的定义）
#### 结论4：最优策略就是在两个停止点之间移动
无论是什么策略，在本题中必然有停止下来的点，而且必然有两个以上。  
若只有一个停止点，可实际上到达0或n+1时点必定会停下来，故至少有两个停止点  
若有大于两个的停止点，则在到达一个停止点（非边界处）可以选择停或不停，若不停相当于这个点不是停止点，若停就相当于这个点就是停止点，无法再延伸。因为在本题中无论你何时到达x点，你的状态都是相同的，不存在根据不同的状态来选则的策略，故不存在大于两个的停止点（会不会有点绕）
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long K=100000;
inline long long read()
{
    long long num=0,fs=1;
    char ch;
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') fs=-1,ch=getchar();
    while(ch>='0'&&ch<='9') num=num*10+ch-'0',ch=getchar();
    return num*fs;
}
struct gzw
{
    long long x,y;	
}p,q[500009];
inline gzw operator -(gzw a,gzw b)
{
    return (gzw){a.x-b.x,a.y-b.y};	
}
inline long long operator *(gzw a,gzw b)
{
    return 	a.x*b.y-a.y*b.x;
}
long long tail;
long long n;
void push(gzw x)
{
    while(tail&&(x-q[tail])*(q[tail]-q[tail-1])<=0) tail--;
    q[++tail]=x;
}
int main()
{
    n=read();
    for(long long i=1;i<=n;i++)
    {
    	p.x=i;
        p.y=read()*K;
        push(p);	
    }
    push((gzw){n+1,0});
    for(long long i=1,j=0;i<=n;i++)
    {
    	while(j<tail&&q[j].x<i) j++;
    	if(q[j].x==i) printf("%lld\n",q[j].y);
    	else printf("%lld\n",((q[j].x-i)*q[j-1].y+(i-q[j-1].x)*q[j].y)/(q[j].x-q[j-1].x));
    }
    return 0;
}
```


---

## 作者：AzusaCat (赞：1)

我们不算那个什么关键点了，直接设 $E_i$ 为最优策略下从 $i$ 开始的报酬。那么我们有 $E_0=E_{n+1}=0$，同时考虑这一步的决策，如果走，那么期望为 $\dfrac{E_{i-1}+E_{i+1}}{2}$，如果不走，报酬是 $f_i$。

所以我们有
$$
E_{i}=\max(\frac{E_{i-1}+E_{i+1}}{2},f_i)\quad (1\leqslant i\leqslant n)
$$
我们有以下定论：点集 $\{(i,E_i)\}$ 在点集 $\{(i,f_i)\}\cup\{(0,0),(n+1,0)\}$ 所构成的凸包上。

我们不难发现 $E_i$ 等于 $(i,f_i)$ 和经过 $(i-1,E_{i-1})$ 与 $(i+1,E_{i+1})$ 两点的直线在 $x=i$ 出的纵坐标的较大值，则其一定是凸的；同时不难发现，$\{(i,f_i)\}\cup\{(0,0),(n+1,0)\}$ 构成的凸包一定满足上述条件。

下面我们证明这样的点集是唯一的。为此我们扩展一下状态：给定平面中 $n$ 个点 $(x_i,y_i)$ 和点 $(x_0,f_0),(x_{n+1},f_{n+1})$，满足 $x_i$ 互不相同且从小到大排列。设$f_i=\max(y_i,\dfrac{x_{i+1}-x_i}{x_{i+1}-x_{i-1}}f_{i-1}+\dfrac{x_i-x_{i-1}}{x_{i+1}-x_{i-1}}f_{i+1})$，从图形意义上依旧是相邻的两个点形成直线和给定点的较高点。则我们只需要证明 $\{(x_i,f_i)\}$ 的每一个顶点都是给定点集中的点。我们考虑归纳证明。

当 $n=1$ 时显然成立。

当 $n>1$ 时，考虑任意添加最后一个点，如果其在前 $n+1$ 个点形成的凸包内部，则继续；反之新形成的凸包一定由原凸包上点的子集和新加入的点组成。这样一定不会有不属于原点集的点。

所以我们只需要维护原点集的凸包，这个可以线性实现。

代码（这题卡精度最后输出的时候不要用 `double` 要用 `__int128`）：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef __int128 ll;
ll a[200005];
int q[200005],tl;
double f[200005];
ll crs(int x,int y,int z){return ((y-x)*(a[y]-a[z])-(y-z)*(a[y]-a[x]));}
void add(int x)
{
    while(tl>1&&crs(q[tl-1],q[tl],x)<=0)tl--;
    q[++tl]=x;
}
void write(__int128 x)
{
    if(x<=9){putchar('0'+x);return;}
    write(x/10);
    putchar('0'+x%10);
}
int main()
{
    int n;
    scanf("%d",&n);
    q[tl=1]=0;
    for(int i=1;i<=n;i++)
    {
        long long x;
        scanf("%lld",&x);
        a[i]=x;
        a[i]*=100000;
        add(i);
    }
    add(n+1);
    int now=1;
    for(int i=1;i<=n;i++)
    {
        while(q[now+1]<=i)now++;
        write(((((q[now+1]-i)*a[q[now]])+(i-q[now])*a[q[now+1]])/(q[now+1]-q[now])));
        puts("");
    }
    return 0;
}
```

---

## 作者：0626SXD (赞：0)

考虑什么时候选择结束。如果有多个结束位置，那么从这些位置开始直接跳下去会最优，其他位置则一直走直到到达一结束位置并跳下去最优。

如果我们已经知道了若干个结束位置，怎么算夹在中间的位置的答案呢？如果记 $dp_i$ 表示 $i$ 位置的答案，两边最近的结束位置为 $l,r$，那么 $dp_l=f(l),dp_r=f(r),f_i=\frac{1}{2}f_{i-1}+\frac{1}{2}f_{i+1}$，发现两边的值已经知道，且函数所有点共线，带入直线就能求出所有值了。

现在只需要判断一个位置是否是结束位置了。以下标为横轴，$f$ 为纵轴建系，如果一个位置是不是结束位置，证明其两边各找一个点，它们的连线在该位置处大于该点的 $f$，即该位置在上凸包之下。那么是结束位置肯定构成了一个上凸包，可以通过找出凸包的方式找到结束位置。

代码如下：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define for_(a,b,c) for(int a=b;a<=c;++a)
using namespace std;
int n;
const int N=1e5+10;
ll w[N],f[N],st[N],tp=1;
bool stp[N];
int main(){
	cin>>n;
	for_(i,1,n)cin>>w[i];
	for_(i,1,n+1){
		while(tp>=2&&(w[i]-w[st[tp]])*(st[tp]-st[tp-1])>=(w[st[tp]]-w[st[tp-1]])*(i-st[tp]))--tp;
		st[++tp]=i;
	}
	for_(i,1,tp)stp[st[i]]=1;
	int cur=1;
	for_(i,1,n){
		if(stp[i]){cout<<w[i]*100000<<"\n";++cur;continue;}
		ll x=st[cur],y=st[cur+1];
		ll ans_i=((y-i)*w[x]+(i-x)*w[y])*100000/(y-x);
		cout<<ans_i<<"\n";
	}
	return 0;
}
```

---

