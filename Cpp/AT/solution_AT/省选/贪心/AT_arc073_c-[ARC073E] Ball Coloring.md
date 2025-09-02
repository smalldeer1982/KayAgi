# [ARC073E] Ball Coloring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc073/tasks/arc073_c

$ 2 $ 個の白いボールが入った袋が $ N $ 個あります。$ i $ 個目の袋にはそれぞれ整数 $ x_i $ と $ y_i $ が書かれたボールが $ 1 $ 個ずつ入っています。

あなたはこの袋それぞれについて、片方のボールを赤く塗り、もう片方を青く塗ります。

そのあと $ 2N $ 個のボールを、塗られた色で分類します。

そして

- 赤く塗られたボールに書かれた整数の最大値を $ R_{max} $
- 赤く塗られたボールに書かれた整数の最小値を $ R_{min} $
- 青く塗られたボールに書かれた整数の最大値を $ B_{max} $
- 青く塗られたボールに書かれた整数の最小値を $ B_{min} $

としたときに、$ (R_{max}\ -\ R_{min})\ \times\ (B_{max}\ -\ B_{min}) $ の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 200,000 $
- $ 1\ ≦\ x_i,\ y_i\ ≦\ 10^9 $

### Sample Explanation 1

$ x_1 $, $ x_2 $, $ y_3 $ の書かれたボールを赤色に塗り、 $ y_1 $, $ y_2 $, $ x_3 $ の書かれたボールを青色に塗ると最適解になります。

## 样例 #1

### 输入

```
3
1 2
3 4
5 6```

### 输出

```
15```

## 样例 #2

### 输入

```
3
1010 10
1000 1
20 1020```

### 输出

```
380```

## 样例 #3

### 输入

```
2
1 1
1000000000 1000000000```

### 输出

```
999999998000000001```

# 题解

## 作者：RicardoShips (赞：15)

不得不说一句，~~这题在$AtCoder$里算一道水题~~

但是我时间空间都被同桌巨佬爆踩，还是水得不行啊

首先分类讨论，假设我们把最大值的球涂成蓝色

- 最小值的球涂成红色，那么我们可以贪心

  把每个袋子里面较大值的球涂成蓝色，较小值的球涂成红色
  
  $O$ $($ $n$ $)$就可以求出红蓝球区间的最大差值的最小值
  
  但是这样不一定能使$ans$最小，接着来看另一种情况

- 最小值的球也涂成蓝色，这样$Bmax$ $-$ $Bmin$就已经确定了

  那么我们就要让红球的区间最大差值最小

  所以我们可以在上面的基础上
  
  按照$x$从小到大的顺序，把颜色依次翻转
  
  在翻转的过程中$O$ $($ $n$ $)$求出红球区间的最大差值的最小值
  
最后我们只要把两种答案再取最小值，就是最后的$ans$

```cpp
#include<bits/stdc++.h>
#define INF 1000000007
using namespace std;
struct sakura
{
    long long x;
    long long y;
}
ball[222222];
long long x[222222];
long long y[222222];
long long maxn[222222];
long long minl[222222];
long long n,ans,ans1,ans2,bmax,bmin,rmax,rmin;
inline bool cmp(sakura xx,sakura yy){ return xx.x<yy.x; }
int main()
{
    scanf("%lld",&n);
    bmax=rmax=-1;bmin=rmin=INF;
    for(register int i=1;i<=n;++i)
    {
        scanf("%lld%lld",&x[i],&y[i]);
        if(x[i]>y[i]) swap(x[i],y[i]);
        ball[i].x=x[i];ball[i].y=y[i];
        bmax=max(bmax,y[i]);
        bmin=min(bmin,y[i]);
        rmax=max(rmax,x[i]);
        rmin=min(rmin,x[i]);
    }
    ans1=(bmax-bmin)*(rmax-rmin);
    bmin=rmin;sort(ball+1,ball+n+1,cmp);
    ans2=INF;maxn[1]=minl[1]=ball[1].y;
    for(register int i=2;i<=n;++i)
    {
        maxn[i]=max(maxn[i-1],ball[i].y);
        minl[i]=min(minl[i-1],ball[i].y);
        if(i!=n) ans2=min(ans2,max(maxn[i],ball[n].x)-min(minl[i],ball[i+1].x));
    }
    ans2*=(bmax-bmin);ans=min(ans1,ans2);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：dz_ice (赞：8)

我写一种比较奇怪的方法（说白了就是随机生成序列进行多次贪心）

那么怎么贪心呢？每次取出一组牌，并更新lmax,lmin,rmax,rmin,算出(rmax − rmin)×(lmax − lmin)

不过貌似这样无法直接ac？那我们就可以用随机数来打乱卡牌的顺序再进行贪心，并且多随机几遍（我取得的是30遍）取最小值，这样很大概率能够得出正确答案

接下来上代码
```
#include<bits/stdc++.h>
using namespace std;
long long lmax,lmin,rmax,rmin,lx,lm,rx,rm,lx1,lm1,rx1,rm1,ans1,ans2,sum,n,a[200003],b[200003],hhh[200003],ran,aaa=1e18;
int main()
{
	srand(time(0));
	cin>>n;
	for(long long i=1; i<=n; i++)
		cin>>a[i]>>b[i];
	for(int k=1; k<=30; k++)
	{
		memset(hhh,0,sizeof(hhh));
		ran=rand()%n+1,sum=0,hhh[ran]=1,lmax=a[ran],lmin=a[ran],rmax=b[ran],rmin=b[ran];
		for(long long i=1; i<=n*10; i++)
		{
			ran=rand()%n+1;
			if(hhh[ran]==0)
			{
				hhh[ran]=1,lx=lmax,lm=lmin,rx=rmax,rm=rmin,lx=max(lx,a[ran]),lm=min(lm,a[ran]),rx=max(rx,b[ran]),rm=min(rm,b[ran]),ans1=(lx-lm)*(rx-rm),lx1=lmax,lm1=lmin,rx1=rmax,rm1=rmin,lx1=max(lx1,b[ran]),lm1=min(lm1,b[ran]),rx1=max(rx1,a[ran]),rm1=min(rm1,a[ran]),ans2=(lx1-lm1)*(rx1-rm1);
				if(ans1<=ans2)
					lmax=lx,lmin=lm,rmax=rx,rmin=rm,sum=ans1;
				else
					lmax=lx1,lmin=lm1,rmax=rx1,rmin=rm1,sum=ans2;
			}
		}
		for(long long i=1; i<=n; i++)
		{
			if(hhh[i]==0)
			{
				lx=lmax,lm=lmin,rx=rmax,rm=rmin,lx=max(lx,a[i]),lm=min(lm,a[i]),rx=max(rx,b[i]),rm=min(rm,b[i]),ans1=(lx-lm)*(rx-rm),lx1=lmax,lm1=lmin,rx1=rmax,rm1=rmin,lx1=max(lx1,b[i]),lm1=min(lm1,b[i]),rx1=max(rx1,a[i]),rm1=min(rm1,a[i]),ans2=(lx1-lm1)*(rx1-rm1);
				if(ans1<=ans2)
					lmax=lx,lmin=lm,rmax=rx,rmin=rm,sum=ans1;
				else
					lmax=lx1,lmin=lm1,rmax=rx1,rmin=rm1,sum=ans2;
			}
		}
		aaa=min(aaa,sum);
	}
	cout<<aaa;
	return 0;
}
```


---

## 作者：fade_away (赞：5)

# [ARC073C] Ball Coloring
[安利博客](https://blog.csdn.net/xmr_pursue_dreams/article/details/111824517)

## Solution
我们发现编号的最大值$max$必然会在$R_{max},B_{max}$中至少一个出现，最小值$min$必然会在$R_{min},B_{min}$中至少一个出现。

因此会有四种情况：
1. $R_{max}=max,R_{min}=min$
2. $R_{max}=max,B_{min}=min$
3. $B_{max}=max,R_{min}=min$
4. $B_{max}=max,B_{min}=min$

因为$R,B$等价，所以$condition\;3,4$都可以不考虑。

我们先考虑$condition\;1$，此时答案为$(max-min)(B_{max}-B_{min})$，所以相当于$R$是个垃圾桶，随便什么数都可以放，而$B$中的数必须在$B_{min},B_{max}$之间，于是我们可以枚举$t=B_{min}$，让$B_{max}$尽量小，于是对于一个包$(x,y)$，不妨令$x \leq y$。

- 若$x\leq y<t$，则无解。
- 若$x< t\leq y$，则把$y$涂成$B$。
- 若$t\leq x\leq y$，则把$x$涂成$B$。

可以离散化，然后把所有$(x,y)$按$x$排序，模拟这个变化过程，时间复杂度$O(nlgn)$。

再来考虑$condition\;2$，此时答案为$(max-R_{min})(B_{max}-min)$，我们同样可以枚举$t=R_{min}$，对于每个$(x,y),x<y$，有：

- 若$x\leq y<t$，则无解。
- 若$x< t\leq y$，则把$y$涂成$R$。
- 若$t\leq x\leq y$，则把$y$涂成$R$。

因此我们会只会让$y$涂成$R$，$x$涂成$B$，直接$O(n)$计算即可。

总时间复杂度$O(nlgn)$。
## Code
```cpp
PR a[MAXN];
int b[MAXN];
ll solve1(int n)
{
	int mn=INF,mx=-INF,nw=-INF,lim=INF;
	for (int i=1;i<=n;i++) upmin(mn,a[i].fi),upmax(mx,a[i].se),upmax(nw,a[i].fi),upmin(lim,a[i].se);
	ll ans=loo;

	int num=0;
	for (int i=1;i<=n;i++) b[++num]=a[i].fi,b[++num]=a[i].se;
	sort(b+1,b+num+1);
	num=unique(b+1,b+num+1)-b-1;
	for (int i=1,l=1;i<=num;i++)
	{
		if (b[i]>lim) return ans;
		while (l<=n&&b[i]>a[l].fi) upmax(nw,a[l].se),l++;
		upmin(ans,1ll*(mx-mn)*(nw-b[i]));
	}
}
ll solve2(int n)
{
	int mn1=INF,mn2=INF,mx1=-INF,mx2=-INF;
	for (int i=1;i<=n;i++) upmin(mn1,a[i].fi),upmax(mx1,a[i].fi),upmin(mn2,a[i].se),upmax(mx2,a[i].se);
	return 1ll*(mx1-mn1)*(mx2-mn2);
}
signed main()
{
	int n=read();
	for (int i=1;i<=n;i++) a[i].fi=read(),a[i].se=read();
	for (int i=1;i<=n;i++) if (a[i].fi>a[i].se) swap(a[i].fi,a[i].se);
	sort(a+1,a+n+1);
	printf("%lld\n",min(solve1(n),solve2(n)));
	return 0;
}
```


---

## 作者：ღꦿ࿐ (赞：3)

只会暴躁做法。会不了一点贪心。

分出来的两侧的 $\max,\min$ 一定会包含全局 $\max,\min$，所以考虑全局 $\min,\max$ 的情况。

### 全局 $\min,\max$ 不在同一侧

考虑这个时候将每个二元组较小的那个与 $\min$ 放在一起，较大的那个与 $\max$ 放在一起一定最优，如果交换两个一定不可能是代价变得更小，只会是两侧的极差都变大。

### 全局 $\min,\max$ 在同一侧

这个时候这一侧的 $\max - \min$ 已经是定值了，我们只需要最小化另一侧的极差，现在就变成了如下问题：

每个位置有两种选择 $a_i,b_i$，必须选择二者之一并加入集合中，最小化集合的极差。


考虑二分答案并进行检查，假设目前要检验答案 $d$，我们有一种暴力的做法就是枚举 $l$，然后检查是否所有选项都有一者在 $[l,l+d]$ 里，考虑优化这个过程：对于一组 $a_i,b_i$，考虑可行的 $l$ 是区间 $[a_i-d,a_i]\cup[b_i-d,b_i]$，对这些位置加上 $1$，我们可以求出每个位置可以满足多少个 $i$ 的要求，然后检查一下是否存在一个位置可以满足所有  $i$ 的要求即可。

将区间加拆成端点处加减，不用离散化直接排个序做即可。


瓶颈在每次二分里的排序，复杂度 $O(n\log n\log w)$，可以通过预先排序并归并做到 $O(n(\log n + \log w))$，但是没必要。

[代码](https://atcoder.jp/contests/arc073/submissions/47598669)。

---

## 作者：Kinandra (赞：3)

标签: 贪心.

分两种情况讨论:

1. 最大值和最小值不在同一类中(分别记为**大类**和**小类**),  那么显然某个最优方案满足: 对于一个二元组 $(x,y)(x<y)$ ,  $x$ 分入小类, $y$ 分入大类.

2. 最大值和最小值在同一种类中(记为**大类**, 另一类记为**小类**), 则大类的极差确定. 将所有二元组按 $x$ 由小到大排序(根据二元组在数组中的分布位置, 称一个位置**越左**表示**这个位置**的二元组 $x$ 越小), 则存在一个最优方案满足: $x$ 分入小类的二元组恰好为一段后缀, 枚举这个后缀求答案.

   证明: 小类最小值 $s$ 只与 $x$ 分入小类的最左的位置 $i$ 有关, 即 $s=\min\{x_i,\min_{j<i}y_j\}$ . 假设已知 $i$, 则可以确定 $s$ , 所以只需要最小化小类的最大值就可以达到最优方案. 对于 $i$ 右边的位置, 全部将 $x$ 分入小类显然不比其他方案劣.

两种情况分别计算取最小值就好了.

时间复杂度 $\mathcal O(n\log n)$.

```cpp
#include <bits/stdc++.h>
#define inf 1000000009
using namespace std;
int read();
int n;
struct P {
    int x, y;
    void init() { x = read(), y = read(), x > y ? swap(x, y) : void(); }
} p[200005];

bool cmp(P a, P b) { return a.x < b.x; }

int main() {
    n = read();
    int mxx = 0, mxy = 0, mnx = inf, mny = inf;
    long long res;
    for (int i = 1; i <= n; ++i) {
        p[i].init();
        mxx = max(mxx, p[i].x), mnx = min(mnx, p[i].x);
        mxy = max(mxy, p[i].y), mny = min(mny, p[i].y);
    }
    res = 1ll * (mxx - mnx) * (mxy - mny);
    long long tmp = mxy - mnx;
    sort(p + 1, p + 1 + n, cmp), mny = inf, mxy = 0;
    res = min(res, tmp * (p[n].x - p[1].x));
    for (int i = 1; i <= n; ++i) {
        mxy = max(mxy, p[i].y), mny = min(mny, p[i].y);
        res = min(res, tmp * (max(mxy, p[n].x) -
                              min(mny, i == n ? inf : p[i + 1].x)));
    }
    printf("%lld\n", res);
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```



---

## 作者：Cry_For_theMoon (赞：1)

[传送门](https://atcoder.jp/contests/arc073/tasks/arc073_c)

感觉其实这题比 D 难。

第一次独立想出这个位置的题...

#### 题意：

给定 $n$ 个正整数二元组 $(a_i,b_i)$ 还有两个空栈 $A,B$。对于每个二元组，选择一个元素加入 $A$ 栈，另外一个元素加入 $B$ 栈。

设 $A$ 栈中最大元素为 $A_{max}$，类似地定义 $A_{min},B_{max},B_{min}$。目标是求出最小可能的 $(A_{max}-A_{min})(B_{max}-B_{min})$ 的值。

Data range：$n\le 2\,\times\,10^5,a_i,b_i\le 10^9$。

#### 分析：

首先颜色具有对偶性，意思是，把原本加入 $A$ 的全部加入 $B$，原本加入 $B$ 的反之，答案不变。

因此我们设全局里最大的数为 $max$，最小的数为 $min$。则可以确定 $A_{max}=max$。我们假设 $min<max$，如果 $min=max$，显然答案为 $0$。

然后分类讨论：

- $B_{min}=min$，此时我们确定了 $A$ 的最大值和 $B$ 的最小值。对于每个二元组 $(a_i,b_i)$，容易发现，我们把大的加入 $A$，小的加入 $B$，答案一定更小。

- $A_{min}=min$，这要求 $max$ 和 $min$ 不能唯一地存在于同一个二元组，意思就是不能说 $max$ 和 $min$ 的出现次数为 $1$，同时他们两个还在同一个二元组里。特判掉这种情况后，我们枚举 $B_{min}$ 的值。那么对于一个二元组 $(a_i,b_i)(a_i\le b_i)$ 来说：

1. 如果 $a_i\le b_i\lt B_{min}$，那么一定无解，因为 $B_{min}$ 不可能是 $B$ 中的最小值。

2. 如果 $a_i\lt B_{min} \le b_i$，那么只能把 $b_i$ 加入 $B$ 中。

3. 如果 $B_{min}\le a_i \le b_i$，那么我们显然把 $a_i$ 加入 $B$ 中。

容易发现这个贪心策略保证了最后会有 $max$ 和 $min$ 进入 $A$ 中，同时 $B_{min}$ 一定会有进入 $B$ 的，而且保证了答案在此时尽可能小。

对于第一个约束，我们求出 $\min\{\max\{a_i,b_i\}\}$ 的值，那么要求 $B_{min}$ 不超过这个值就可以了。来考虑后两条约束，我们发现它实际上就是把二元组对于 $\min\{a_i,b_i\}$ 按照大小分类，所以按照这个关键字排序以后维护前缀 $\max$ 和后缀 $\min$ 的最大值，然后就可以二分了。

时间复杂度 $O(n\log n)$。

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const ll MAXN=2e5+10,INF=1.1e9;
ll n,b[MAXN*2],c[MAXN],tot,ans=INF*INF;
ll premax[MAXN],sufmax[MAXN];
pair<ll,ll>a[MAXN];
bool cmp(const pair<ll,ll>& p1,const pair<ll,ll>&p2){
	return min(p1.fr,p1.se)<min(p2.fr,p2.se);
}
void solve1(){
	//Rmax和Rmin都确定了
	ll rmax=-INF,rmin=INF;
	rmax=b[tot],rmin=b[1];
	sort(a+1,a+1+n,cmp); //按最小值排序
	ll cnt1=0,cnt2=0,cnt3=0;
	rep(i,1,n){
		if((a[i].fr==b[tot] && a[i].se==b[1]) || (a[i].fr==b[1] && a[i].se==b[tot]))cnt3++;
		if(a[i].fr==b[1] || a[i].se==b[1])cnt1++;
		if(a[i].fr==b[tot] || a[i].se==b[tot])cnt2++;
	}
	if(cnt1==1 && cnt2==1 && cnt3==1)return; //最大和最小出现在同一对 
	ll minn=INF;
	rep(i,1,n){
		minn=min(minn,max(a[i].fr,a[i].se));
		c[i]=min(a[i].fr,a[i].se);
	} 
	premax[1]=max(a[1].fr,a[1].se);
	rep(i,2,n){
		premax[i]=max(premax[i-1],max(a[i].fr,a[i].se));
	} 
	sufmax[n]=min(a[n].fr,a[n].se);
	per(i,n-1,1){
		sufmax[i]=max(sufmax[i+1],min(a[i].fr,a[i].se));
	}
	rep(i,1,tot){
		//bmin=b[i]
		ll tmpmin=b[i],tmpmax=b[i];
		if(minn<tmpmin)break;
		//计算tmpmax
		if(c[n]>=tmpmin){
			if(c[1]<tmpmin){
				ll pos=lower_bound(c+1,c+1+n,tmpmin)-c-1;
				tmpmax=max(tmpmax,premax[pos]);
			}
			ll pos=lower_bound(c+1,c+1+n,tmpmin)-c;
			tmpmax=max(tmpmax,sufmax[pos]);
		}else{
			tmpmax=max(tmpmax,premax[n]);
		}
		ans=min(ans,(tmpmax-tmpmin)*(rmax-rmin));
	}
}
void solve2(){
	//Rmax和Bmin都确定了 
	ll rmax=-INF,rmin=INF,bmax=-INF,bmin=INF;
	rmax=rmin=b[tot];bmax=bmin=b[1];
	rep(i,1,n){
		rmin=min(rmin,max(a[i].fr,a[i].se));
		bmax=max(bmax,min(a[i].fr,a[i].se));
	}
	ans=min(ans,(bmax-bmin)*(rmax-rmin));
}
int main(){
	cin>>n;
	rep(i,1,n){
		cin>>a[i].fr>>a[i].se;
		b[++tot]=a[i].fr;b[++tot]=a[i].se;
	}
	sort(b+1,b+1+tot);
	tot=unique(b+1,b+1+tot)-b-1;
	if(tot==1){
		printf("0\n");return 0;
	}
	solve1();
	solve2();
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：cike_bilibili (赞：0)

最优化问题，而且每个元素是二选一，看我乱搞。

如果你做过 P9120 的乱搞做法，你应该可以想到用随机化，首先我们考虑一个简单贪心，直接记录当前当前的两个颜色的最值，然后判断当前这两个元素的染色方式，直接选择对答案影响最小的那个。

但这样显然会 WA，所以我们每次打乱序列顺序，随机化贪心，多贪心几次取最小值就能大概率获得答案。

贴个代码。


```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
inline int read(){
    int ans=0,w=1;
    char ch=getchar();
    while(ch<48||ch>57){
       if(ch=='-')w=-1;
       ch=getchar();
    }
    while(ch>=48&&ch<=57){
       ans=(ans<<1)+(ans<<3)+ch-48;
       ch=getchar();
    }
    return w*ans;
}
mt19937 G(time(0));
int rd(int l,int r){
    return uniform_int_distribution<int>(l,r)(G);
}
int n;
int a[200005],b[200005];
void sf(){
    for(int i=1;i<=n;i++){
        int x=rd(1,n);
        swap(a[i],a[x]),swap(b[i],b[x]);
    }
}
signed main(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
    int T=30;
    ll res=4e18;
    while(T--){
        sf();
        int bl=1e9,br=-1e9,rl=1e9,rr=-1e9;
        ll ans=4e18;
        for(int i=1;i<=n;i++){
            ll dlt1=ans-1ll*(max(br,a[i])-min(bl,a[i]))*(max(rr,b[i])-min(rl,b[i]));
            ll dlt2=ans-1ll*(max(br,b[i])-min(bl,b[i]))*(max(rr,a[i])-min(rl,a[i]));
            if(dlt1>dlt2){
                br=max(br,a[i]),bl=min(bl,a[i]);
                rr=max(rr,b[i]),rl=min(rl,b[i]);
                ans-=dlt1;
            }else{
                br=max(br,b[i]),bl=min(bl,b[i]);
                rr=max(rr,a[i]),rl=min(rl,a[i]);
                ans-=dlt2;
            }
        }
        res=min(res,ans);
    }
    cout<<res<<'\n';
    return 0;
}
```

---

## 作者：cyq32ent (赞：0)

由对称性，不妨把最大值涂成红色。

- 如果最小值是蓝色，那么需要最大化 $R_{min}$，最小化 $B_{max}$，所以把较大的球都涂成红色即可。
- 如果最小值是红色，那么需要最小化 $B_{max}-B_{min}$，那么先令 $x_i \le y_i$，（若 $x_i>y_i$ 就交换），按照 $x$ 升序排序。排序后前 $k$ 个的 $x$ 涂成红色，其余涂成蓝色。暴力算即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define M(a,b) a=max(a,b);
#define N(a,b) a=min(a,b);
#define int long long
pair<int,int>B[214514];
int mn,ml,n,a,rm,rn,bm,bn;
signed main(){
	cin>>n;rn=bn=a=mn=ml=1e9+7;
	for(int i=1,x,y;i<=n;i++){
		cin>>x>>y;
		B[i]={min(x,y),max(x,y)};
		M(rm,max(x,y))
		M(bm,min(x,y))
		N(rn,max(x,y))
		N(bn,min(x,y))
	}
	sort(B+1,B+1+n);
	ml=mn=B[1].second;
	for(int i=2;i<n;i++){
		M(mn,B[i].second)
		N(ml,B[i].second)
		N(a,max(mn,B[n].first)-min(ml,B[i+1].first))
	}
	cout<<min((rm-rn)*(bm-bn),a*(rm-bn));
}
```

---

## 作者：Rusalka (赞：0)

### 简要题意

- $N$ 个盒子，每个盒子里有两个数。现在要把盒子中的数分成两种颜色，满足：

- 1. 每个盒子中的数分别属于两种颜色，每个数恰好属于一种颜色

- 2. 两种颜色的数的极差的乘积最小

- 求这个最小值

- $N \le 200000$

### 分析与解答

考虑极差的乘积的最小值，要么是让其中一个极小；要么是让两个都尽量小，感性理解即可

下文记 $x_i$ 表示第 $i$ 个盒子的较小值，$y_i$ 表示第 $i$ 个盒子的较大值。

分类讨论最大值和最小值是不是同色

#### 1. 最大值和最小值不同色

这时让两个极差都尽量小

所以把所有 $y_i$ 染成同一种颜色，所以 $x_i$ 染成另一种颜色。

证明考虑交换一对 $x_i$、$y_i$，比较简单，也很好理解，这里就不写了。

#### 2. 最大值和最小值同色

此时，其中一种颜色的极差已经固定，为所有数的极差，我们的目标是让另一种颜色的极差尽量小。

下面记 ***选一个盒子*** 表示把这个盒子的 $x_i$ 划分到另一种颜色，这种颜色(即上文另一种颜色)的其余部分由其余盒子的 $y_i$ 组成。

首先将盒子按照 $x_i$ 排序

此时可以证明，选出的盒子一定是从某个位置 $p$ 开始的一段后缀 $(p > 1)$

证明如下：

- 假设当前选了后 $p$ 个盒子。由于按照 $x_i$ 排过序，所以最大值为 $maxx = \max(x_n, \max\{y_i\})$，最小值为 $minn = \min(x_p, \min\{y_i\})$。记此时极差

- 若在前 $n-p$ 个位置中，还选了一个盒子 $k$。则此时最大值 $maxx^{'} = maxx$，最小值 $minn^{'}= \min(x_k, \min\{y_i\})$

- 还是由于 $x_i$ 有序，所以 $minn^{'} \le minn$。所以不选 $k$ 时，极差不会比选 $k$ 更大。

- 所以选的一定是一段后缀

所以枚举 $p$，维护 $y_i$ 的前缀最大值和前缀最小值即可。

记得和第一种情况取最小值。

### Code

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;
const int MAXN = 200010;
const int INF = 0x3f3f3f3f;

int n;
struct ball{
	int x, y;
	ball(int X=0,int Y=0):x(X),y(Y){}
	inline bool operator<(const ball&o)const{return x<o.x;}
}a[MAXN];

int main()
{
//	freopen("ball.in","r",stdin);
//	freopen("ball.out","w",stdout);
	scanf("%d",&n);
	int maxx = 0, minx = INF, maxy = 0, miny = INF;
	for(int i=1,u,v;i<=n;i++)
	{
		scanf("%d%d",&u,&v);
		a[i].x = min(u, v);
		a[i].y = max(u, v);
		maxx = max(maxx, a[i].x);
		minx = min(minx, a[i].x);
		maxy = max(maxy, a[i].y);
		miny = min(miny, a[i].y);
	}
	ll ans = 1ll*(maxx-minx)*(maxy-miny);
	ll val1 = maxy - minx;
	sort(a+1, a+n+1);
	minx = INF; maxx = 0;
	for(int i=1;i<n;i++)
	{
		minx = min(minx, a[i].y);
		maxx = max(maxx, a[i].y);
		ans = min(ans, val1*(max(maxx, a[n].x) - min(minx, a[i+1].x)));
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Ezio__Auditore (赞：0)

## AT2557 [ARC073C] Ball Coloring

[[Statement]](https://www.luogu.com.cn/problem/AT2557)

Date: Nov. 30th

---
#### 题意：
给定 $n$ 个二元组，对组那两个元素分别染成红色，蓝色。要你求出一种染色方案使得同色元素极差相乘最小。

---
#### 思路：
考虑 $R_{max}, R_{min}, B_{max}, B_{min}$ 的取值。

显然全局最值在 $R_{max}, R_{min}, B_{max}, B_{min}$ 中出现至少两次。
  
（下文设全局最值为 $A_{max}, A_{min}$。）
  
**那就分两种情况： (假设 $R_{max} = A_{max}$, 即最大值涂红色)**
  
### 1. $R_{min} = A_{min}$ : 最小值涂红色。

&emsp;则 $R_{max} - R_{min}$ 的值确定， 目标是最小化 $B_{max} - B_{min}$。
   
&emsp;考虑对二元组对 $x$ 值排序，最后 $x$ 涂成蓝色的一定是串从尾部开始连续的区间。
   
&emsp;即从第 $i$ 位及后面 $x$ 涂蓝色， 第 $i$ 位前 $y$ 涂蓝色。
   
&emsp;证明：在 $x \ge B_{min}$ 的时候，将 $x$ 涂成蓝色不会使 $B_{min}$ 更小， 可能使 $B_{max}$ 变小或不变，
   
&emsp;&emsp;&emsp;&emsp;$B_{max} - B_{min}$ 变小或不变。 所以在 $x \ge B_{min}$ 时将 $x$ 涂成蓝色一定不会更劣。
   
&emsp;考虑从后往前枚举 $x_i$ 作为分界点, $Bmax_i, Bmin_i$ 表示以 $x_i$ 作为分界点时的最值，则:
$$
Bmax_i = \max\limits_{1\le j\lt i}{\{y_j, x_{max}\}}
$$
      
&emsp;注意 $Bmax_i$ 可能来自以选择涂成蓝色的 $x$ 中最大值，同理 $Bmin_i$ 也可能来自涂成蓝色的 $y$：
$$
Bmin_i = \min\limits_{1\le j\lt i}{\{y_j, x_{min}\}}
$$
&emsp;过程中记录 $B_{best} = \min\limits_{1\lt i\le n} {Bmax_i - Bmin_i}$, 答案即为 $Ans1 = (A_{max} - A_{min}) \times B_{best}$。
   
&emsp;复杂度：$O(nlogn)$ 排序， $O(n)$ 贪心处理。
### 2. $B_{min} = A_{min}$ : 最小值涂蓝色。
&emsp;贪心将二元组较小值涂成蓝色，较大值涂成红色, 即 $blue \to x$, $red \to y$。
      
&emsp;证明：若交换涂色，会使 $R_{min}$ 减小或不变， $B_{max}$ 增大或不变。
      
&emsp;&emsp;&emsp;&emsp;只可能导致 $R_{max} - R_{min}$, $B_{max} - B_{min}$ 增大或不变， 不会减小，
           
&emsp;&emsp;&emsp;&emsp;不会比把较小值涂蓝色，较大值涂红色更优。
           
&emsp;复杂度：$O(n)$ 即可贪心处理出答案： $Ans2 = (X_{max} - X_{min}) \times (Y_{max} - Y_{min})$。
  
最终答案对两种情况答案取 $min$ 输出即可， $Ans = \min {\{Ans1, Ans2\}}$。
  
  **总复杂度：$O(nlogn)$。**
   
### Code:

```cpp
#include <bits/stdc++.h>
char gc() {
  static const int buff_size = 1e6 + 1;
  static char buff[buff_size], *p1 = nullptr, *p2 = nullptr;
  return p1 == p2 && (p2 = (p1 = buff) + fread(buff, 1, buff_size, stdin), p1 == p2) ? EOF : *p1++;
}
typedef long long ll;
template <class _Tp = ll>
_Tp read() {
  _Tp w = 0;
  bool f = 0;
  char ch = gc();
  while (!isdigit(ch)) f |= ch == '-', ch = gc();
  while (isdigit(ch)) w = (w << 3) + (w << 1) + (ch ^ 48), ch = gc();
  return f ? -w : w;
}
const int kMaxN = 2e5 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n;
struct pair {
  ll x, y;  // x < y
  pair() {}
  pair(ll x_, ll y_) : x(std::min(x_, y_)), y(std::max(x_, y_)) {}
} a[kMaxN];

ll Rmin, Rmax, Bmin, Bmax;
ll max_pre[kMaxN], min_pre[kMaxN];
int main() {
  n = read();
  Bmin = Rmin = INF;
  ll x, y;
  for (int i = 1; i <= n; i++) {
    x = read(), y = read();
    a[i] = pair(x, y);
    /* 处理第二种情况的答案 */
    Bmin = std::min(Bmin, a[i].x);
    Bmax = std::max(Bmax, a[i].x);
    Rmin = std::min(Rmin, a[i].y);
    Rmax = std::max(Rmax, a[i].y);
  }
  /* 计算第二种情况的答案 */
  ll Ans2 = (Rmax - Rmin) * (Bmax - Bmin);
  /* 处理第一种情况的答案 */
  std::sort(a + 1, a + n + 1, [](pair a, pair b) -> bool { return a.x < b.x; }); // 这里用lambda表达式作为cmp函数 按x升序排序
  Rmin = a[1].x;
  max_pre[0] = 0;
  min_pre[0] = INF;
  for (int i = 1; i <= n; i++) {
    max_pre[i] = std::max(max_pre[i - 1], a[i].y); 
    min_pre[i] = std::min(min_pre[i - 1], a[i].y);
  } // 为Bmin_i, Bmax_i做预处理
  ll Bbest = INF;
  for (int i = n; i > 1; i--) { // 由于限制了 Rmin = Amin 所以循环到 2 就可以结束了， 最小的 x 留给 Rmin
    Bbest = std::min(Bbest, std::max(max_pre[i - 1], a[n].x) - std::min(min_pre[i], a[i].x));
    // 注意 Bmax_i Bmin_i 的多种来源
  }
  ll Ans1 = (Rmax - Rmin) * Bbest;
  printf("%lld\n", std::min(Ans1, Ans2));
  return 0;
}
```
---
结语：~~Markdown 缩进真是毒瘤~~ 全面细致的分类讨论有助于解题，当然做不出来也可以适当口胡一下。

---

## 作者：Krimson (赞：0)

分类讨论一下就好了  
先将所有的都用二元组$(x,y)$表示  
1.$min$和$max$不在同一组里  
那么易证把每一个二元组里的$x$扔进$min$里的那一堆肯定是最优的  
2.$min$和$max$在同一组里(左堆)  
首先左堆的$l_{max},l_{min}$都是定值  
那么可以证明按照$x$排序之后一定是一段连续的直到最后一个都是$x$在右边这个堆里最优  
可以用反证法  
用$a_i$表示二元组$(x_i,y_i)$  
首先假设存在一个$a_i$是$x$在右堆,$a_{i+k}$的$x$在右堆  
那么不难发现$r_{max}>=x_{i+k},r_{min}<=x_i$  
即$r_{min}<=x_{i+j}<=r_{max},j<=k$  
所以让$x_{i+j}$放在右堆一定不会对答案产生影响,即$x_{i+j}$放在右堆比$y_{i+j}$放在右堆更优  
同样方法可以证明一直到$a_n$都是$x_i$放在右堆更优  
所以可以直接线性枚举过去,对所有情况取$min$就好了   
这个过程使用set来存储会比较方便
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
/*
分两类讨论罢  
1.最大最小在同一堆里
*/
int n;
struct node
{
    ll l,r;
    int id;
    bool operator<(const node &x)const{
        return l==x.l?r<x.r:l<x.l;
    }
};
struct cmp
{
    bool operator()(const node &x,const node &y)const{
        if(x.r==y.r) return x.l<y.l;
        return x.r>y.r;
    }
};
set<node> s;
set<node,cmp> S;
multiset<ll> sb;
const int MAXN=2e5+7;
node a[MAXN];
ll ans=1e18;
bool mark[MAXN];
int main(){
    // freopen("rand.in","r",stdin);
    // freopen("1.out","w",stdout);
    n=read();
    for(ri i=1;i<=n;++i){
        a[i].l=read(),a[i].r=read();
        if(a[i].l>a[i].r) swap(a[i].l,a[i].r);
    }
    sort(a+1,a+n+1);
    for(ri i=1;i<=n;++i){
        a[i].id=i;
        s.insert(a[i]);
        S.insert(a[i]);
    }
    ll lmin,lmax,rmin,rmax;
    lmin=lmax=a[1].l;    
    rmin=rmax=a[1].r;
    mark[1]=true;
    s.erase(s.lower_bound(a[1]));
    S.erase(S.lower_bound(a[1]));
    if(S.begin()->r>rmax&&n>1){
        mark[S.begin()->id]=true;
        lmax=S.begin()->r;
        rmax=max(rmax,S.begin()->l);
        rmin=min(rmin,S.begin()->l);
        S.erase(S.begin());
        sb.insert(rmin),sb.insert(rmax);
        for(ri i=1;i<=n;++i){
            if(mark[i]) continue;
            sb.insert(a[i].l);
        }
        for(ri i=1;i<=n;++i){
            if(mark[i]) continue;
            ans=min(ans,(lmax-lmin)*(*(--sb.end())-*sb.begin()));
            sb.erase(sb.lower_bound(a[i].l));
            sb.insert(a[i].r);
        }
        // ans=min(ans,(lmax-lmin)*(rmax-rmin));
        memset(mark,false,sizeof(mark));
        // S.clear();
        for(ri i=2;i<=n;++i) S.insert(a[i]);

    }
    mark[1]=true;
    lmin=lmax=a[1].l;    
    rmin=rmax=a[1].r;
    if(n>1){
        node now=*S.begin();
        lmax=now.l;
        rmax=max(rmax,now.r);
        rmin=min(rmin,now.r);
        mark[now.id]=true;
    }
    for(ri i=1;i<=n;++i){
        if(mark[i]) continue;
        lmax=max(a[i].l,lmax);
        rmin=min(rmin,a[i].r);
    }
    ans=min(ans,(lmax-lmin)*(rmax-rmin));
    print(ans);
    return 0;
}
```


---

## 作者：wsk_1202 (赞：0)

考试时考到了这个题，信心满满地写了一个假贪心：开始指定第一组数分别在左、右侧，每次读入时直接判定在目前情况下这组数应该怎么分配。当然，由于输入的顺序的不同，这个算法算出的结果也不同，就愉快WA了。但是只是由于输入顺序的不同才导致结果不同，我就想到了一种玄学的算法：随机。

$C++$的$STL$里有一种函数 $random$$__$$shuffle$ 可以方便的解决本问题。这个函数的用法形同 $sort$ ，可以将一个数组中的元素打乱顺序。于是就可以采用如下步骤：

1.先按之前的算法算出来一个答案；

2.重复数次，每次打乱顺序，再次求答案，每次求出答案时取 $min$ 就好了。

代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef unsigned long long ll;
inline ll rd()
{
	ll x=0,p=1;
	char a=getchar();
	while((a<48||a>57)&&a!='-')a=getchar();
	if(a=='-')p=-p,a=getchar();
	while(a>47&&a<58)
	{
		x=(x<<1)+(x<<3)+(a&15);
		a=getchar();
	}
	return x*p;
}
inline void write(ll x)
{
	if(x<0)x=-x,putchar('-');
	if(x>9)write(x/10);
	putchar(x%10+48);
}
inline void print(ll x,int type=0)
{
	write(x);
	if(!type)putchar(' ');
	else puts("");
}
struct node
{
	ll x,y;
}d[200002];
ll n,lmax,lmin,rmax,rmin;
ll ans;
int main()
{
	srand(time(0));
	n=rd();
	d[1].x=rd();d[1].y=rd();
	lmax=lmin=d[1].x;rmax=rmin=d[1].y;
	for(int i=2;i<=n;i++)
	{
		d[i].x=rd();d[i].y=rd();
		ll a,b;
		if(d[i].x>lmax)
		{
			if(d[i].y>rmax)a=(d[i].x-lmin)*(d[i].y-rmin);
			else if(d[i].y<rmin)a=(d[i].x-lmin)*(rmax-d[i].y);
			else a=(d[i].x-lmin)*(rmax-rmin);
		}
		else if(d[i].x<lmin)
		{
			if(d[i].y>rmax)a=(lmax-d[i].x)*(d[i].y-rmin);
			else if(d[i].y<rmin)a=(lmax-d[i].x)*(rmax-d[i].y);
			else a=(lmax-d[i].x)*(rmax-rmin);
		}
		else
		{
			if(d[i].y>rmax)a=(lmax-lmin)*(d[i].y-rmin);
			else if(d[i].y<rmin)a=(lmax-lmin)*(rmax-d[i].y);
			else a=(lmax-lmin)*(rmax-rmin);
		}//对于放入两侧的数，共有以上9种情况，按题意模拟即可
		swap(d[i].x,d[i].y);//考虑另一种分发，将x,y互换
		if(d[i].x>lmax)
		{
			if(d[i].y>rmax)b=(d[i].x-lmin)*(d[i].y-rmin);
			else if(d[i].y<rmin)b=(d[i].x-lmin)*(rmax-d[i].y);
			else b=(d[i].x-lmin)*(rmax-rmin);
		}
		else if(d[i].x<lmin)
		{
			if(d[i].y>rmax)b=(lmax-d[i].x)*(d[i].y-rmin);
			else if(d[i].y<rmin)b=(lmax-d[i].x)*(rmax-d[i].y);
			else b=(lmax-d[i].x)*(rmax-rmin);
		}
		else
		{
			if(d[i].y>rmax)b=(lmax-lmin)*(d[i].y-rmin);
			else if(d[i].y<rmin)b=(lmax-lmin)*(rmax-d[i].y);
			else b=(lmax-lmin)*(rmax-rmin);
		}
		swap(d[i].x,d[i].y);//交换回来，方便下面分配
		if(a<=b)
		{
			lmax=max(lmax,d[i].x);lmin=min(lmin,d[i].x);
			rmax=max(rmax,d[i].y);rmin=min(rmin,d[i].y);
		}
		else
		{
			lmax=max(lmax,d[i].y);lmin=min(lmin,d[i].y);
			rmax=max(rmax,d[i].x);rmin=min(rmin,d[i].x);
		}//更新max,min
	}//以上为假贪心算法
	ans=(lmax-lmin)*(rmax-rmin);
	for(int q=1;q<=150;q++)//次数150次左右即可
	{
		random_shuffle(d+1,d+n+1);//使用random_shuffle打乱顺序，再次求值
		lmax=lmin=d[1].x;rmax=rmin=d[1].y;//以下为重复
		for(int i=2;i<=n;i++)
		{
			ll a,b;
			if(d[i].x>lmax)
			{
				if(d[i].y>rmax)a=(d[i].x-lmin)*(d[i].y-rmin);
				else if(d[i].y<rmin)a=(d[i].x-lmin)*(rmax-d[i].y);
				else a=(d[i].x-lmin)*(rmax-rmin);
			}
			else if(d[i].x<lmin)
			{
				if(d[i].y>rmax)a=(lmax-d[i].x)*(d[i].y-rmin);
				else if(d[i].y<rmin)a=(lmax-d[i].x)*(rmax-d[i].y);
				else a=(lmax-d[i].x)*(rmax-rmin);
			}
			else
			{
				if(d[i].y>rmax)a=(lmax-lmin)*(d[i].y-rmin);
				else if(d[i].y<rmin)a=(lmax-lmin)*(rmax-d[i].y);
				else a=(lmax-lmin)*(rmax-rmin);
			}
			swap(d[i].x,d[i].y);
			if(d[i].x>lmax)
			{
				if(d[i].y>rmax)b=(d[i].x-lmin)*(d[i].y-rmin);
				else if(d[i].y<rmin)b=(d[i].x-lmin)*(rmax-d[i].y);
				else b=(d[i].x-lmin)*(rmax-rmin);
			}
			else if(d[i].x<lmin)
			{
				if(d[i].y>rmax)b=(lmax-d[i].x)*(d[i].y-rmin);
				else if(d[i].y<rmin)b=(lmax-d[i].x)*(rmax-d[i].y);
				else b=(lmax-d[i].x)*(rmax-rmin);
			}
			else
			{
				if(d[i].y>rmax)b=(lmax-lmin)*(d[i].y-rmin);
				else if(d[i].y<rmin)b=(lmax-lmin)*(rmax-d[i].y);
				else b=(lmax-lmin)*(rmax-rmin);
			}
			swap(d[i].x,d[i].y);
			if(a<=b)
			{
				lmax=max(lmax,d[i].x);lmin=min(lmin,d[i].x);
				rmax=max(rmax,d[i].y);rmin=min(rmin,d[i].y);
			}
			else
			{
				lmax=max(lmax,d[i].y);lmin=min(lmin,d[i].y);
				rmax=max(rmax,d[i].x);rmin=min(rmin,d[i].x);
			}
		}
		ans=min(ans,(lmax-lmin)*(rmax-rmin));//取最小值，得到最佳答案
	}
	print(ans,1);
	return 0;
}
```

---

## 作者：dengjunhaodejia09 (赞：0)

考虑分编号最大与最小是否同色考虑。

若不同色，则让所有小编号与小编号在一起，大编号与大编号在一起。

若同色，枚举另一颜色的最大值，排序下来判断是否合法后求一下对应的最小值即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
    int x,y;
}a[300005],b[300005];
int N=0;
bool cmp(node aa,node bb){
    return aa.y>bb.y;
}
vector<pair<pair<int,int>,int> > vec;
int Minaa[400005];
bool cmpa(pair<pair<int,int>,int> aaa,pair<pair<int,int>,int> bbb){
    return aaa.second<bbb.second;
}
int main(){
    int n;
    cin>>n;
    int Max=0,Max_id=0,Min=2e9,Min_id=0;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y;
        if(a[i].x>a[i].y){
            swap(a[i].x,a[i].y);
        }
        if(a[i].x<Min){
            Min=a[i].x;
            Min_id=i;
        }
        if(a[i].y>Max){
            Max=a[i].y;
            Max_id=i;
        }
    }
    for(int i=1;i<=n;i++){
        if(Min_id!=i && Max_id!=i){
            b[++N]=a[i];
        }
    }
    //异色
    int Minn=a[Min_id].y,Maxx=a[Max_id].x;
    for(int i=1;i<=N;i++){
        Maxx=max(Maxx,b[i].x);
        Minn=min(Minn,b[i].y);
    }
    long long daan=1ll*(Max-Minn)*(Maxx-Min);
    if(Max_id==Min_id){
        cout<<daan;
        return 0;
    }
    //同色
    sort(b+1,b+N+1,cmp);
    for(int i=1;i<=N;i++){
        vec.push_back(make_pair(make_pair(i,1),b[i].x));
        vec.push_back(make_pair(make_pair(i,2),b[i].y));
    }
    sort(vec.begin(),vec.end(),cmpa);
    reverse(vec.begin(),vec.end());
    Minaa[vec.size()]=2e9;
    for(int i=vec.size()-1;i>=0;i--){
        if(vec[i].first.second==2){
            Minaa[i]=min(Minaa[i+1],vec[i].second);
        }else{
            Minaa[i]=Minaa[i+1];
        }
    }
    int yMax=max(a[Max_id].x,a[Min_id].y),yMin=min(a[Max_id].x,a[Min_id].y),Main=2e9;;
    for(int i=0;i<vec.size();i++){
        if(vec[i].second<=yMax){
            daan=min(daan,1ll*(Max-Min)*(yMax-min(yMin,min(Main,Minaa[i]))));
            break;
        }
        Main=min(Main,b[vec[i].first.first].x);
        if(vec[i].first.second==1){
            break;
        }
    }
    for(int i=0;i<vec.size();i++){
        if(vec[i].second<yMax){
            break;
        }
        daan=min(daan,1ll*(Max-Min)*(vec[i].second-min(yMin,Minaa[i])));
        if(vec[i].first.second==1){
            break;
        }
        yMin=min(yMin,b[vec[i].first.first].x);
    }
    cout<<daan;
    return 0;
}
```

---

