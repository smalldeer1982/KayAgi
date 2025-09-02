# [ARC121D] 1 or 2

## 题目描述

你有 $n$ 个糖果，第 $i$ 个糖果的美味值为 $a_i$。

你需要吃糖，每次你可以选择吃 $1$ 个或 $2$ 个糖，并将你这一次吃的糖的总和写在黑板上。

你需要求出吃完所有糖果的所有可能的情况中，黑板上数字最大值和最小值之差最小是多少。

## 说明/提示

$1\leq n\leq 5\times 10^3,-10^9\leq a_i\leq 10^9$。

---

样例一：

第一次吃第一和第二个，第二次吃第三个，黑板上的数为 $\{3,4\}$，答案为 $1$。

样例二：

第一次全部吃完，黑板上的数为 $\{-150\}$，答案为 $0$。

Translate by Zek3L.

## 样例 #1

### 输入

```
3
1 2 4```

### 输出

```
1```

## 样例 #2

### 输入

```
2
-100 -50```

### 输出

```
0```

## 样例 #3

### 输入

```
20
-18 31 -16 12 -44 -5 24 17 -37 -31 46 -24 -2 11 32 16 0 -39 35 38```

### 输出

```
13```

# 题解

## 作者：Judgelight (赞：7)

# [ARC121D] 1 or 2

## 题面翻译


你有 $n$ 个糖果，第 $i$ 个糖果的美味值为 $a_i$。

你需要吃糖，每次你可以选择吃 $1$ 个或 $2$ 个糖，并将你这一次吃的糖的总和写在黑板上。

你需要求出吃完所有糖果的所有可能的情况中，黑板上数字最大值和最小值之差最小是多少。

# 题解

是一道不错的思维题，值得一做。

后文所说的序列都表示 $n$ 个糖果排成一排所形成的序列 $a$，且序列每一项的值为 $a_i$。

## 1. 题面分析

数据范围 $n \le 5000$，盲猜是 $n^2$ 的做法。

看见最大值和最小值，考虑先将原序列升序排序一定是不亏的。


现在考虑在上面做区间 DP，有了乱搞做法。

这样能在 Atcoder 上获得过掉绝大多数点的好成绩。

但是这样是不够的

## 2. 猜测结论

默认已经对序列排序。

首先，如果当前元素 $a_i$ 选择被单独吃掉，可以看作与一颗值为 $0$ 的糖一起被吃掉。

这样就将所有的被单独吃掉的糖都转化为了两颗一起吃。然而有一个问题：我们不知道应该往序列中加入多少颗值为 $0$ 的糖。这时我们选择暴力枚举 $n'$ 表示添加后的糖果数量（$n \le n' \le 2n$），算出每种 $n'$ 下最小的**最大值与最小值之差**。

所以我们现在需要考虑的问题只是对于一个元素数量为 $n'$ 的升序序列，全部使用两两消除的方式，如何取得最小的最大值与最小值之差。

感性理解一下，我们肯定希望最大值和最小值差距越小越好，所以就让最大和最小匹配、次大和次小匹配……，这样应该可以取得最小的差值。


## 3. 总结

枚举补充的 $0$ 的数量，对于补充好了的序列，对它排序，选两个数时，两头取，最后算出这样的最大值和最小值，做差，用差值更新答案。

## 4. AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 10009
using namespace std;
int nn,a[N],b[N],ans=0x3f3f3f3f;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>nn;
	for(int i=1;i<=nn;i++){
		cin>>a[i];
		b[i]=a[i];
	}
	for(int n=nn;n<=nn*2;n++){
		for(int i=nn+1;i<=n;i++){
			a[i]=0;
		}
		sort(a+1,a+n+1);
		int maxx=-0x3f3f3f3f,minn=0x3f3f3f3f;
		for(int i=1;i<=n/2;i++){
			maxx=max(maxx,a[i]+a[n-i+1]);
			minn=min(minn,a[i]+a[n-i+1]);
		}
		if(n%2==1){
			maxx=max(maxx,a[n/2+1]);
			minn=min(minn,a[n/2+1]);
		}
		ans=min(ans,maxx-minn);
		for(int i=1;i<=nn;i++){
			a[i]=b[i];
		}
	}
	cout<<ans;
	return 0;
}
```

## 5. 结论证明

设元素 $a$，$a+x$，$a+y$，$a+z$，满足 $x \le y 
\le z$，求如何组合成两组每组元素数量为 $2$ 的二元组能让两组的每组和的最大值和最小值之差最小。

有点绕，其实就是有 $4$ 颗糖，如何用吃两颗的方式让题目的要求最小。

设差值为 $t$，有如下分类讨论：

1. $a$ 和 $a+x$ 一组，$a+y$ 和 $a+z$ 一组，这样 $t=y+z-x$。

2. $a$ 和 $a+y$ 一组，$a+x$ 和 $a+z$ 一组，这样 $t=x+z-y$。

3. $a$ 和 $a+z$ 一组，$a+x$ 和 $a+y$ 一组，这样 $t=|x+y-z|$。

显然第三种最小。

---

## 作者：rui_er (赞：5)

诈骗题，竟然评到了 $2784$ 的惊人高分（快到红了），来补个题解。

题意：有两个可重集 $A,B$，$B$ 初始为 $\varnothing$。每次从 $A$ 中删除一个或两个数，并将它们的和加入 $B$ 中，重复操作直到 $A=\varnothing$。最小化 $B$ 的极差。

$1\le |A|\le 5\times 10^3$。

如果每次必须删除两个数，显然最小与最大、次小与次大配对是最优的，可以用交换法证明。观察到删除一个数的操作等价于删除 $0$ 和那个数。因此枚举有多少次删除一个数的操作，补充那么多个 $0$ 之后跑刚刚的贪心即可。

容易做到 $\Theta(n^2)$，但我懒得做到，所以写了一个 $\Theta(n^2\log n)$。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const ll N = 1e4+5, inf = 0x3f3f3f3f3f3f3f3fll;

ll n, a[N], b[N], ans = inf;
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

int main() {
	scanf("%lld", &n);
	rep(i, 1, n) scanf("%lld", &a[i]);
	rep(i, 0, n) {
		ll L = 1, R = n + i;
		if((R - L + 1) & 1) continue;
		rep(j, 1, n) b[j] = a[j];
		rep(j, n+1, n+i) b[j] = 0;
		sort(b+1, b+1+n+i);
		ll mn = inf, mx = -inf;
		while(L < R) {
			chkmin(mn, b[L] + b[R]);
			chkmax(mx, b[L] + b[R]);
			++L; --R;
		}
		chkmin(ans, mx - mn);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Fire_Shadow_Dream (赞：2)

[题目传送门（你谷）](https://www.luogu.com.cn/problem/AT_arc121_d)

[题目传送门（atcoder）](https://atcoder.jp/contests/arc121/tasks/arc121_d)

蒟蒻的第一篇题解，写的不好的地方请见谅并提出

~~废话少说~~

# 题目大意（转换一下）

你拥有 $n$ 个数，第 $i$ 个数为 $a_i$ 每次可以进行一次操作，直到所有数都被操作过。一次操作定义为单独取 $1$ 个数或取 $2$ 个数相加，并将得到的值放入一个集 $A$ 中（开始时 $A=\varnothing$），使用过的数不能再用。

求若干种可能的 $A$ 的极差的最小值。

# 思路

实际上取一个数的操作就相当于取出这个数与一个 $0$ 并相加,所以我们枚举新增多少个 $0$ 即可（相当于枚举有几个数被单独取出）。

由于最多只有 $n$ 个数，所以枚举的范围在 $[0,n]$ 即可。

最后只要将新获得序列的序列升序排序，每次首尾相加（最大值+最小值，次大值+次小值，以此类推），然后按照题意更新答案就行啦（~~是不是很简短~~）。

然而这为什么是正确的呢？

# 证明

设 $a,b,c,d$ 且 $a\le b\le c\le d$，那么就有以下三种组合：
$$
(a+b,c+d)(a+c,b+d)(a+d,b+c)
$$

比较第一种组合与第三种组合，可以发现 $a+b\le a+d\le c+d$ 且 $a+b\le b+c\le c+d$。

这说明在数轴上，$a+d$ 与 $b+c$ 一定在区间 $[a+b,c+d]$ 中，所以一定有 $\lvert(a+d)-(b+c)\rvert\le\lvert(c+d)-(a+b)\rvert$。

同理比较第二种组合与第三种组合，可得 $\lvert(a+d)-(b+c)\rvert\le\lvert(b+d)-(a+c)\rvert$（证明过程同上，在此省略）

因此每次取新序列中的最大值与最小值组合是正确的。

# 上代码

时间复杂度：$\Omicron(n^2\log n)$ 枚举*快排（可以做到 $\Omicron(n^2)$，但是能够 $n^2\log n$ 过就不冒险了）

空间复杂度：$\Omicron(n)$


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e4+90;
ll n,m,a[N],f[N];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	ll ans=LONG_LONG_MAX;
	for(int i=0;i<=n;i++){
		for(int j=1;j<=n;j++) f[j]=a[j];
		for(int j=n+1;j<=n+i;j++) f[j]=0;
		sort(f+1,f+n+i+1);
		ll ma=-LONG_LONG_MAX,mi=-ma;
		for(int j=1;j<=(n+i+1)/2;j++){
			ll x=f[j]+(j==n+i-j+1 ? 0 : f[n+i-j+1]);
			ma=max(ma,x),mi=min(mi,x);
		}
		ans=min(ans,ma-mi);
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：6_curly_L (赞：2)

### 题意

有若干数，每次可以选择一个数或者两个数加和，之后将其写在黑板上。

求最后黑板上所有数的极差的最小值。

### 分析

首先发现要么选一个要么选两个的限制不是很好做，考虑一种弱化情况：总数为偶数个且每次只能选两个。

这时我们有贪心的策略：对原数列排序，每次取首尾两个数加和，可以证明这样一定极差最小。

再回到这个题。可以把选一个的看成是选这个数和一个 $0$ 配对选取，这样就可以看作是在原数列插入若干个 $0$，从而在 $O(n)$ 的时间内算出答案。

那我们怎样知道插入了多少个 $0$ 呢？

哦我们不需要知道，他的数据范围是 $5000$，我们可以直接枚举有多少个 $0$（即选了多少个单个的）最后取 $\min$ 算答案。

### 细节

+ 如果原数列有奇数个数字，则至少要加入一个 $0$。

+ 直接插入 $0$ 之后排序复杂度是 $O(n^2\log n)$ 的，可能会过不去，所以可以维护两个指针，在正负数交接的时候判一下就可以。

然后就可以过了，复杂度是 $O(n^2)$ 的。

### 代码

~~~CPP
//one or two
#include<bits/stdc++.h>
#define N 5010
using namespace std;

int a[N];

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    int ans=INT_MAX;
    for(int i=n%2;i<=n;i+=2){
        int num=i;
        int la=1,lb=n;
        int maxn=INT_MIN,minx=INT_MAX;
        for(int j=1;j<=(i+n)/2;j++){
            int xa,xb;
            if(a[la]>=0&&num){
                xa=0;
                num--;
            }
            else{
                xa=a[la];
                la++;
            }
            if(a[lb]<0&&num){
                xb=0;
                num--;
            }
            else{
                xb=a[lb];
                lb--;
            }
            maxn=max(maxn,xa+xb);
            minx=min(minx,xa+xb);
        }
        ans=min(ans,maxn-minx);
    }
    printf("%d",ans);
    return 0;
}
~~~

---

## 作者：Pretharp (赞：2)

考虑一次只能吃两颗糖果，显然，在最优的情况下每次会吃掉剩下的糖果中最大的和最小的。然后考虑一次吃一颗糖果的情况，每次吃一颗美味值为 $x$ 的糖果可以看作吃美味值为 $x$ 的糖果以及美味值为 $0$ 的糖果，这样问题又转换为了每次只能吃两颗糖果，至于我们要有多少次只吃一个糖果（也就是向集合里插入多少个 $0$），可以枚举。注意代码实现的时候应该将 $i$ 个 $0$ 插入在正数和负数的交界处，而非插入在末尾再排序，这样时间复杂度才是 $O(n^2)$ 否则会带 $\log$（虽然也能过）。

---

## 作者：DengDuck (赞：1)

这题是真正意义的诈骗题，脑电波撞上就会了。

首先两种操作不太好弄，考虑将一种操作转换成另一种操作，我们发现选一个相当于选择这个数字，再选择一个 $0$，这样转换后就只有一种数字了。

考虑在原数组中添加一些 $0$，添加多少？我们枚举添加的 $0$ 的数量 $x\in [0,n]$，再多就不对了。

然后只有一种操作，我们有一个比较显然的贪心，就是直接两边选，就是最大的和最小的一起吃，最大的和最小的一起吃，次大的和次小的一起吃。

咋证呢？考虑对于一个不满足的这个策略的情况，然后选两对不满足策略的配对，设两对中的四个数字从小到大为 $a,b,c,d$。

那么正确的匹配：$a+d,b+c$。

错误的匹配：$a+c,b+d$ 或 $a+b,c+d$。

为什么前者更优？我们用绝对值表示一下贡献：

- 正确匹配：$|a+d-b-c|$。
- 错误匹配：$|a+c-b-d|$。
- 错误匹配：$|a+b-c-d|$。



设 $x=b-a$，$y=d-c$。

那么：

$x>0,y>0$。
- 正确匹配：$|y-x|$。
- 错误匹配：$|-x-y|=x+y$，显然有 $|x-y|\leq x+y$。
- 错误匹配：$|a+b-c-d|=d+c-a-b$，显然 $d-b\geq y$，$c-a\geq x$，跟上一个比输麻了，这位老哥提前退出我们的竞争。

拿错误的匹配和正确的匹配比较大小，你就知道为什么要选择正确的匹配了。

所以啊，这样直接做就行了，每次加入 $0$ 的时候考虑插入排序，可以做到严格 $\mathcal O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
const LL inf=1e10;
const LL N=1e4+5;
//const LL M;
//const LL mod;
//const LF eps;
//const LL P;
LL n,m,a[N],ans=inf;
int main()
{
	scanf("%lld",&n);
	m=n+1;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+n+1);
	while(m--)
	{
		LL mn=inf,mx=-inf;
		for(int i=1,j=n;i<=j;i++,j--)
		{
			if(i!=j)mn=min(mn,a[i]+a[j]),mx=max(mx,a[i]+a[j]);
			else mn=min(mn,a[i]),mx=max(mx,a[i]);
		}
		ans=min(ans,mx-mn);	
		n++;
		for(int i=n;i>1&&a[i-1]>a[i];i--)swap(a[i-1],a[i]);
	}

	printf("%lld",ans);
	return 0;
}
//RP++
```

---

## 作者：TLEWA (赞：0)

题面所述的情况似乎有点复杂，不妨从较为简单的情况入手，讨论每次只能选择吃两颗糖的答案。

有一个非常符合直觉也非常经典的结论：每次将序列最大值和最小值分为一组组的所产生的方案极差最小，可以通过微扰法证明：

假设我们有两个分组，取值为 $a,b,a',b'$，且 $a>a'$，如果有 $b>b'$，则我们使用 $a,b'$ 一组，$a',b$ 一组的分组方案能使最小值更大，最大值更小，对答案的影响一定不劣 。

再来考虑题面所述的加强版情境，我们发现，只吃一个糖的情况可以被视为吃了两颗糖，但是其中一个美味度为 $0$。考虑往序列里加入 $0$，容易发现总有一个加入 $0$ 的数量可以使情境变为弱化版，且这个数量一定小于等于 $n$。考虑枚举加入 $0$ 的数量并每次进行 dp，每次结果的最小值即为答案。

## AC 代码


```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=5005;

int n,arr[N];
vector<int> vec;

int calc() {
	int l=0,r=vec.size()-1;
	int mx=-2e9,mn=2e9;
	while(l<=r) {
		if(l==r) {
			mx=max(vec[l],mx);
			mn=min(vec[l],mn);
		}else {
			mx=max(vec[l]+vec[r],mx);
			mn=min(vec[l]+vec[r],mn);
		}
		l++,r--;
	}
	return mx-mn;
}

int main() {
	cin >> n;
	
	int num;
	for(int i=1;i<=n;++i) {
		cin >> num;
		vec.push_back(num);
	}
	sort(vec.begin(),vec.end());
	
	int ans=calc();
	for(int i=1;i<=n;++i) {
		vec.insert(lower_bound(vec.begin(),vec.end(),0),0);
		ans=min(ans,calc());
	}
	
	cout << ans;
	
	return 0;
}

```

时间复杂度 $O(n^2)$

---

## 作者：1234567890sjx (赞：0)

不看题解想不到系列。

其实十分的简单：考虑若当前有偶数个糖而且每一次只能选取两个，那么肯定就是首尾配对最优秀。因此可以考虑补一定数量的 $0$：若当前补了 $i$ 个 $0$ 则就是让 $i$ 对一个数和 $n-i$ 对两个数。因此考虑枚举当前补齐了多少个 $0$，然后按照上述的贪心策略贪心即可。时间复杂度为 $O(n^2)$ 可以通过。

```cpp
const int N=2000100;
int a[N],b[N],n;
int calc(){
	VI v;
	int l=1,r=n;
	while(l<r){
		v.eb(a[l]+a[r]);
		++l,--r;
	}
	if(l==r)v.eb(a[l]);
//	cout<<"qwq "<<l<<' '<<r<<' '<<v.size() <<'\n';
	sort(rng(v));
	return v.back()-v[0];
}
signed main(){
//  freopen("count_in","r",stdin);freopen("count.out","w",stdout);
	// ios_base::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	F(i,1,n)cin>>a[i];
	sort(a+1,a+n+1);
	if(n<=2){
		cout<<"0\n";
		return 0;
	}
	int mi=calc();
	F(i,1,n){
		F(j,1,n)b[i]=a[i];
		F(j,1,i)a[i+n]=0;
		n+=i;
		sort(a+1,a+n+1);
		mi=min(mi,calc());
		n-=i;
		F(j,1,n)a[i]=b[i];
	}
	cout<<mi<<'\n';
	return 0;
}
```

---

## 作者：binbin_200811 (赞：0)

# [ARC121D 1 or 2](https://www.luogu.com.cn/problem/AT_arc121_d)

诈骗题。

#### 思路

吃一个糖的操作可以看做是和一个 $a_i$ 为 $0$ 的糖一起吃。

可以枚举有多少个糖单独吃来确定要增加多少个 $0$。

问题变为每次吃两颗糖。

根据人类直觉，有一个贪心，最小的糖和最大的糖一起吃最优，次小的糖和次大的糖一起吃最优，依次类推。

怎么证明这个性质呢？

有 $2$ 个理解方法：

感性理解：

使最大值最小，那么最大的数肯定加上最小的数最优；最小值最大，那么最小的数加上最大的数最优；应该可以理解以上结论。

理性理解：

有 $A<B<C<D$。

可以选 $A+D,B+C$，同时也可以选 $A+C,B+D$。（$A+B,C+D$ 肯定不优，故不考虑）

有 $|(A+D)-(B+C)|$ 和 $|(A+C)-(B+D)|$。
$$
|(A+D)-(B+C)|=|A-B+D-C|
$$

$$
|(A+C)-(B+D)|=|A-B+C-D|
$$

设 $T=A-B$。

有 $T<0$。

所以，

$$
|A-B+D-C|=|T+(D-C)|
$$

$$
|A-B+C-D|=|T+(C-D)|
$$

由于 $|D-C|=|C-D|$，且 $D-C>0$，$C-D<0$。

结合 $T<0$，有 $|T+(C-D)|>|T+(D-C)|$。

排序后将 $0$ 加入 $a$ 数组，然后塞到队列里就行，每次取队头队尾。

#### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const ll maxn=6e3;

ll n;

ll ans;
ll a[maxn];

deque<ll>que;

int main()
{
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
    sort(a+1,a+n+1);

    ans=1e18;
    for(ll k=0;k<=n;k++)
    {
        ll tmp=k,has=n+k;
        ll mx=-1e18,mi=1e18;
        for(ll i=1;i<=n;i++)
        {
            if(a[i]>0)
                while(tmp) que.push_back(0),tmp--;
            que.push_back(a[i]);
        }
        while(tmp) que.push_back(0),tmp--;
        while(has>1)
        {
            has-=2;
            ll v=que.front()+que.back();
            que.pop_front();
            que.pop_back();
            mx=max(v,mx);
            mi=min(v,mi);
        }
        if(has) mi=min(mi,que.front()),mx=max(mx,que.front()),que.pop_back();
        ans=min(ans,mx-mi);
    }

    printf("%lld",ans);
}
```

代码比较抽象，看看就好。



---

## 作者：ljjl (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc121_d)

假如这道题只允许一次吃两个糖果，则有贪心策略：按照最大配最小的吃法一定是最优的。

那么对于吃一个糖果的情况，则等价于吃这个糖果和一个价值为 $0$ 的糖果。

于是可以枚举多少次吃一个糖果，将等数量的 $0$ 插入到原序列然后排序，按照上面的方法贪心，最后再取最小值即可。

时间复杂度 $O(n^2 \log{n})$，不过也可以优化到 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+1;
int n,a[N],ma,mi,ans=2e9;
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=0;i<=n;i++){
		if((i+n)%2)
			continue;
		sort(a+1,a+1+n+i);
		mi=2e9,ma=-2e9;
		for(int j=1;j*2<=i+n;j++){
			mi=min(mi,a[i+n-j+1]+a[j]),ma=max(ma,a[i+n-j+1]+a[j]);
		}
		ans=min(ans,ma-mi);
	}
	printf("%d",ans);
	return 0;
}
```

---

