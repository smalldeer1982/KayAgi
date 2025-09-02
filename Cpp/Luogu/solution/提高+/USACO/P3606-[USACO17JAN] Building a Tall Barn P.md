# [USACO17JAN] Building a Tall Barn P

## 题目描述

### 题目大意
FJ 正在他的 $K$ 头奶牛的帮助下建造一个全新的 $N$ 层谷仓（$1\le N\le K\le 10^{12}，N\le 10^5$)。为了能够尽快的建造它，他需要你帮助他来找出如何在奶牛间分配工作。

每一头牛必须分配到 $N$ 层中的某一个特定楼层中，并且每一层楼必须至少有一头牛在其中工作。第i层楼需要 $a_i$ 个单位的工作，并且每一头牛完成每一单位的工作需要一个单位时间。所以如果有 $C$ 头牛在第 $i$ 层工作，那么第 $i$ 层需要 $\frac{a_i}{c}$ 个单位时间。为了安全起见，在开始施工第 $i+1$ 层楼之前，必须先完成第 $i$ 层。

如果奶牛被分配以最佳方式在楼层上工作，请计算完成谷仓的最小总时间。输出这个时间四舍五入到整数的结果；数据保证答案离两个整数间的中界大于 $0.1$。

## 样例 #1

### 输入

```
2 5
10
4```

### 输出

```
5```

# 题解

## 作者：巨型方块 (赞：7)

这道题目的思路就是楼下大佬的那种，但是在实际的实现上面会有很多问题

首先去看看楼下的题解

然后
我们要明确知道ci代表什么；

ci指的是当前我们对ai放的奶牛个数；

所以这个ci在最后用一元二次方程求解的时候我们是要向上取整数的；

然后还有一个最关键的地方，就是我们虽然二分了这么一个t

但是这并不代表我们把所有的k头奶牛都用上了，所以我们最后还需要吧这k头奶牛的贡献减去，那么他们的贡献是多少呢，就是我们二分的这个t

最后，就是二分的精度问题；

显然l=0,r=1e12

当然我们知道如果把l=0带入check的话，是会除以0 RE的；

所以我们要用1e-9来代替0

一开始用1e-6wa了好几次

```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const Ll N=1e5+5;
double a[N],l,r,mid,ans,T;
Ll x,k,sum,n;
bool check(double t){
    Ll sum=0;
    for(Ll i=1;i<=n;i++){
        double c=(sqrt(1+4*a[i]/t)-1)/2.;
        Ll v=ceil(c);
        sum+=v;
        if(sum>k)return 0;
    }return 1;
}
int main()
{
    scanf("%lld%lld",&n,&k);
    for(Ll i=1;i<=n;i++)scanf("%lld",&x),a[i]=x;
    l=1e-9,r=12;
    while(r-l>1e-9){
        mid=(l+r)/2.;
        if(check(mid))r=mid;else l=mid;
    }
    for(Ll i=1;i<=n;i++){
        double c=(sqrt(1+4*a[i]/r)-1)/2.;
        Ll v=ceil(c);
        sum+=v;
        ans+=a[i]/v;
    }
    printf("%.0lf",ans-(k-sum)*r);
}
```

---

## 作者：BriMon (赞：4)

其实挺不好意思的，我也不是自己想出来的这道题，也是借鉴了题解；

但是我想把我对这道题的理解说出来，这样可以帮助到更多的不理解的人；

这道题其实一眼就知道二分答案， 想都没想直接敲，16分，what...f？

回过头再仔细读题解， 发现这题并不简单；

我们知道a[1],a[2]...a[n],也知道k,我们要求a[1]/b[1]+a[2]/b[2]+...+a[n]/b[n]的最小值,其中Σbi=k;

这仿佛不是一个寻常的二分可以搞定的；

仔细琢磨题解你会发现，我们要让其中每一层楼，不加入一个牛，比加入一个牛更优，什么意思？

就是我们考虑， 如果这个楼层加一个牛比不加一个牛优，那我们肯定会把别的楼层的牛拿过来给他；

那我们该怎么表示这个抽象的东西呢？


我们设:ti = ai / (ci + 1) - ai / ci , ci是第i层楼的牛数量；

这样我们设出来的ti，就表示这个楼层多一只牛的改变量，我们要求的最终答案，肯定是每层楼的ti最接近，否则我们肯定可以找一只牛放里面；

化简一下得到 ti = ai / (ci * (ci + 1)) ,移项得 ci^2 - ci - ai/ti = 0；

发现我们只要枚举ti， 就可以通过简单的小学数学，把ci算出来；

然后开开心心的二分；

最后如果有空闲的牛就直接乘以r，然后减掉就行了，为什么要乘r？

因为我们二分出来了一个ti,这个ti保证是所有楼层的ti（因为他们最接近的时候才是答案），所以直接乘ti，当成他们的贡献！

有几个坑点，首先记得开long long，还得记得二分一个小数一定要设eps...

顺便推广一下[blog](https://www.cnblogs.com/zZh-Brim/p/9135832.html)，欢迎各位大佬拍砖。

Code：下面题解里有


---

## 作者：fan404 (赞：4)

令 ti 表示 第i层多一头牛的改变量

ti = a[i]/ci\*(ci+1)

最终状态中 ti一定是很接近的,否则可以从j拿一头牛到i去,使得结果更优

所以我们就二分 ti

ti = a[i]/ci\*(ci+1) --->ci\*ci+ci-ai/ti=0 反解出ci，然后对ci求和，如果不到k-n则可以缩小上界，否则提高下界


---

## 作者：w33z8kqrqk8zzzx33 (赞：3)

当没有 $K$ 头牛的限制时，答案为 0：你可以招无限多头牛，总共代价接近 0。如果我们引入招一头牛的“代价”，这样就不可能招无限多头牛了。

如果我们固定招一头牛的代价为 $c>0$，那么总共最小代价为：

$$\min_{r\in\mathbb{Z}^n}(\sum_{i=1}^n\frac{a_i}{r_i}+Cr_i)=$$
$$\sum_{i=1}^n\min_{r\in\mathbb{Z}}(\frac{a_i}r+Cr)=$$

对 $r$ 求导：
$$\frac{d}{dr}\frac{a_i}r+Cr=0$$
$$\operatorname{argmin}=r=\sqrt{\frac{a_i}{C}}$$


考虑总共招多少牛：

$$\sum_{i=1}^n\operatorname{argmin}_{r\in\mathbb{Z}}(\frac{a_i}r+Cr)=$$
$$\sum_{i=1}^n(\lfloor\sqrt{\frac{a_i}{C}}\rfloor\text{ or }\lceil\sqrt{\frac{a_i}{C}}\rceil)$$

手玩，可以发现里面 $\operatorname{argmin}$ 递减。递减函数和递减；于是，会有一个或几个 $C$，使得总共招少于 $K$ 头牛。求尽量小的代价时候可以二分这个代价。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, (a))
#define rep1(i, a) iter(i, 1, (a)+1)

long long ar[100005];
int n;
pair<double,long long> wxq(double weight) {
    double ans = 0;
    double tot = 0;
    rep1(i, n) {
        double v = sqrt(ar[i]/weight);
        double lo = floor(v), hi = ceil(v);
        if(lo > 1e-8 && ar[i]/lo+weight*lo < ar[i]/hi+weight*hi) {
            ans += ar[i]/lo + weight * lo;
            tot += lo;
        } else {
            ans += ar[i]/hi + weight * hi;
            tot += hi;
        }
    }
    return {ans, (long long)(round(tot)+1e-8)};
}

int main() {
    ios_base::sync_with_stdio(false); 
	cin.tie(0);
	long long k; cin >> n >> k;
    rep1(i, n) cin >> ar[i];
    double l=1e-9,r=10;
    while(abs(r-l)>1e-9) {
        double m=(l+r)/2;
        auto q=wxq(m);
        if(q.second > k) l=m;
        else r=m;
    }
    auto q=wxq(r);
    cout << (long long)(round(q.first-k*r)+1e-8) << endl;
    return 0;
}
```

这技巧称 "alien's trick" 或者 “apocryphal binary search”。

---

## 作者：raincity (赞：2)

## 分析

一句话题意：已知 $a_1,a_2,\ldots a_n$ 和 $k$，构造 $c_1,c_2,\ldots c_n$ 满足 $\sum_{i=1}^nc_i=k$，且 $\sum_{i=1}^n\dfrac{a_i}{c_i}$ 最小，求这个最小值。

设 $t_i=\dfrac{a_i}{c_i}-\dfrac{a_i}{c_i+1}=\dfrac{a_i}{c_i\times(c_i+1)}$，则 $c_i^2+c_i-\dfrac{a_i}{t_i}$，$c_i=\dfrac{-1\pm\sqrt{1-\dfrac{4a_i}{t_i}}}{2}$。

显然 $c_i>0$，则 $c_i=\dfrac{-1+\sqrt{1+\dfrac{4a_i}{t_i}}}{2}$。

注意到正确的 $c$ 一定让 $\max{|t_i-t_j|}$ 尽量小，因为如果 $t_j-t_i$ 很大，那么让 $c_i\gets c_i-1,c_j\gets c_j+1$，则 $ans'$ 很可能比原答案要大。

这道题只要求最接近的整数，所以可以就当做所有的 $t$ 都相等进行二分，如果 $\sum_{i=1}^n\lceil{\dfrac{-1+\sqrt{1+\dfrac{4a_i}{t_i}}}{2}}\rceil\le k$ 则可以，否则不行。显然前面这个柿子单调递增。

**注意精度！注意精度！注意精度！**

**注意不要用 int/long long 存浮点型数据，就算结果保留整数！**

---

## 作者：JK_LOVER (赞：2)

## 题意
已知：
$$
\sum_i^nC[i] = k,\ ans=\sum_i^n \frac{A[i]}{C[i]}
$$
求 $ans$ 的最小值。
## 分析
令 
$$
T[i] = \frac{A[i]}{C[i]} \Rightarrow \Delta T[i] = \frac{A[i]}{C[i]}-\frac{A[i]}{C[i]+1} 
$$
$$
\Delta T[i] \times C[i]\times (C[i]+1) = A[i]\times (C[i]+1)-A[i]\times C[i] 
$$
$$
C[i]^2+C[i] - \frac{A[i]}{\Delta T[i]} = 0
$$
$$
C[i] = \frac{-1+\sqrt{1+\frac{4\times A[i]}{\Delta T[i]}}}{2}
$$
我们发现只有 $\Delta T[i]$ 有单调性。而结果中的 $\Delta T[i]$ 一定相同，否则我们一定优先放入大的中。而 $\Delta T[i]$ 越小，答案就越小。最后 
$$
ans = \sum_i^n T[i] - (k-\sum_i^nC[i])\times \Delta T
$$
因为我无论往哪里放，都是等效的 $(\Delta T[i] = \Delta T[j])$ 。所以总答案中还要减去多余的贡献。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps = 0.0000000001;
long long read(){
	long long x = 0,f=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
const int N = 1e5+10;
long long A[N],k,n,sum;
double ans,Mid = 1e9;
bool check(double t,int P)
{
	long long tot = 0;
	double S = 0;
	for(int i = 1;i <= n;i++)
	{
		double c=sqrt(0.25+A[i]/t)-0.5;
        long long  v=ceil(c);
		tot += v;
		S += (double)A[i]/v;
		if(tot > k) return 0;
	}
	if(P) sum = tot,ans = S;
	return 1;
}
int main()
{
//	freopen("P3606_2.in","r",stdin);
	n = read();k = read();
	for(int i = 1;i <= n;i++)
	A[i] = read();
	double l = 1e-10,r = 1e10;
	while(r - l >= eps)
	{
		double mid = (l+r)/2;
		if(check(mid,0))
		{
			r = mid;
			Mid = min(mid,Mid);
		}
		else l = mid;
	}
	check(Mid,1);
	printf("%lld\n",(long long)(ans-(k-sum)*Mid+0.5));
}
```
[地址](https://www.luogu.com.cn/blog/xzc/solution-p3606)

---

## 作者：SamariumPhosphide (赞：2)

提供一份比较容易看懂的题解。

首先，我们可以给每个任务各一头牛，然后把剩下的 $n-k$ 头牛贪心地分配给每个任务。具体贪心策略就是，对于某个任务 $i$，目前已经分配了共 $c_i$ 头牛，那么再分配一头牛可以使总时间减少 $\frac{a_i}{c_i + 1} - \frac{a_i}{c_i}$。于是每次加牛使得收益最大就可以了。

但是牛的数量有 $10^{12}$，这样一头一头枚举会超时，于是考虑用二分，二分一下**加牛时收益的最小值的最大值**。

怎样判断一个收益可不可行？对于每个任务，计算最多加多少头牛，使得收益大于等于该值即可，也就是解不等式 $\frac{a_i}{c_i + 1} - \frac{a_i}{c_i} \geq x$，也即 $a_i \geq x \times c[i] \times (c[i] + 1)$，展开后得到 $c[i] ^ 2 + c[i] - \frac{a[i]}{x} \leq 0$，那么它的两个根为 $x_{1,2} = \frac{-1\pm \sqrt{1+\frac{4 \times a[i]}{x}}}{2}$，必然一正一负，所以这个不等式的解集就是 $0 < x < \frac{-1+  \sqrt{1+\frac{4 \times a[i]}{x}}}{2}$。

于是我们就得到了加牛时收益的最小值的最大值，最后一个步骤是统计答案。在统计出每个任务所要花的时间之后，因为我们二分出来的值可能会有一点点误差，所以要统计出来一共使用了多少头牛。注意到我们二分的时候保证我们使用的牛只多不少，因此把多余的贡献要减掉。

代码可以参考一下别的题解。

---

## 作者：a326820068122c (赞：0)

不知道怎么就想到了这个歪解

这题貌似题解里用的都是二分，我有一个多一个 $\log$ 的做法（开 O2 能过）。


------------
### 首先同样的贪心策略：

我们可以给每个任务各一头牛，然后把剩下的  $n−k$ 头牛贪心地分配给每个任务。对于某个任务 i ，目前已经分配了共 $c_i$ 头牛，那么再分配一头牛可以使总时间减少$\frac{a_i}{c_i}-\frac{a_i}{c_i+1}$。于是每次加牛使得贡献最大就可以了。

~~不严谨的~~证明：

设直接产生贡献最高的楼层为 $x$，假设存在一个更优解这次及之后都不分配给 $x$，那么设这次分配给的楼层为 $y$ 。那么显然：

**“这次分配给 $x$ 的贡献" $\ge$ “这次分配给 $y$ 的贡献”$\ge$"最后一次给 $y$ 分配的贡献"**

这时候将最后一次给 $y$ 分配改为给 $x$ 分配肯定不会更差。

这种方法可以用堆求最大值复杂度 $O(k\log_2n)$ 。

------------

### 问题是这题的k很大，直接贪心显然TLE

这时就有一个想法：能不能连续分配给一个楼层很多头牛呢？

显然，假设现在还有 $k$ 头牛未被分配，那么至少有一头层分配了 $\lfloor \frac{k}{n} \rfloor$ 头

有一个想法就是每次贪心分配 $max(\lfloor \frac{k}{n} \rfloor,1)$ 头给能让最后一头贡献最大（注意不是总贡献）

分配次数大概是 $n\log_2k$ （打表打出来的，可能不准确）

这时候如果每一次都 $O(n)$ 查找，复杂度 $O(n^2\log_2k)$ 还是会 TLE

这里可以综合以上两种方法的优点
为了使小根对维护，我们可以分层分配,一层中每次分配一个固定值，这样可以用堆维护，还可以一下加入多个值，复杂度 $O(n\log_2n\log_2k)$

具体我每减少 $\frac{1}{2}$ 分一层，这样每次k下降的值不会少于原来的 $\frac{1}{2}$

### 具体看代码吧：

```cpp
#include <bits/stdc++.h>
#define for1(i,n) for(i=1;i<=(n);i++)
using namespace std;
typedef long double ld;
typedef long long ll;
const int N=100005;
ll n,k,d,c[N],a[N];
ld ans;
ld v(int i){
	ld x=a[i],y=c[i];
	return x/y-x/(y+d);
}
ld g(int i){
	ld x=a[i],y=c[i];
	return x/(y+d-1)-x/(y+d);
}
struct node{
	ld x;
	int i;
	bool operator<(const node &nd)const{
		return x<nd.x;
	}
}w;
priority_queue<node> q;
int main(){
	ll i;
	int x;
	scanf("%lld%lld",&n,&k);
	k-=n;
	for1(i,n){
		scanf("%lld",&a[i]);
		c[i]=1,ans+=a[i];
	}
	while(k){
		while(!q.empty()) q.pop();
		d=max(1ll,(k>>1)/n);
		for1(x,n) q.push({g(x),x});
		for(i=k;d==1?i:i>(k>>1);i-=d){
			x=q.top().i;q.pop();
			ans-=v(x);c[x]+=d;
			q.push({g(x),x});
		}
		k=i;
	}
	printf("%.0Lf",ans);
	return 0;
}
```

（本题复杂度算得不准确，希望有的大佬能求出更精确的复杂度）

---

