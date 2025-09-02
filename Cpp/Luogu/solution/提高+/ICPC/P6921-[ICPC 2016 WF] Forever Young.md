# [ICPC 2016 WF] Forever Young

## 题目描述

# 题目大意

我的生日快到了！唉，但如今我已经老了，我想重新获得年轻的感觉。

幸运的是，我想出了一个让人感觉更年轻的好方法：如果我把我的年龄以适当选择的 $b$ 进制书写，那么它看起来会更小。例如，假设我以 $10$ 进制书写的年龄是 $32$ 岁；以 $16$ 进制书写，它只有 $20$（$\texttt{0x20}$）！

然而，在这样做时，我不能选择任意进制数。如果以 $b$ 进制为数写的我的年龄包含 $0-9$ 以外的数字，那么很明显我在作弊，这违背了目的。此外，如果我的年龄写成 $b$ 进制后数字太小，那么很明显我在作弊。

在我希望我的年龄看起来有多小的问题上，考虑到我的年龄 $y$ 和下限 $l$，找到最大的进制数 $b$，这样写在基数 $b$ 中的 $y$ 只包含十进制数字，并且当将其看做一个十进制数字时至少是 $l$。

## 说明/提示

时间限制：1s，内存限制：1GB。


2016 年国际大学生编程大赛 ACM-ICPC 世界总决赛。

## 样例 #1

### 输入

```
32 20
```

### 输出

```
16
```

## 样例 #2

### 输入

```
2016 100
```

### 输出

```
42
```

# 题解

## 作者：TensorFlow_js (赞：5)

### 0. 题意简述

给定 $y,l$，求最大的 $b$ 使 $(y)_b$ 仅含有数字 $0-9$，且将 $(y)_b$ 看作十进制数字时 $(y)_b >= l$。$(10\le l\le y\le 10^{18})$

### 1. 做法详解

这里是一种基于二分和预处理的做法。

首先很容易想到，对于下限 $l$，可以二分答案。

具体就是把 $l$ 当作 $b$ 进制数，然后把 $l$ 转回 $10$ 进制，看一下是否大于 $y$，若大于则代表此时的 $b$ 不符合条件，然后枚举 $b$ 的上限。对于“只包含十进制数字”这条要求，我们暴力从上限往下枚举即可。时间复杂度 $\mathcal{O}(\log y+b_{max}-b_{ans})$。

如果满足“只包含十进制数字”的答案很稀疏的话，这个时间复杂度显然是过不去的，而事实就是这样。

我们仔细想想，会发现：如果过不去，说明 $b$ 的上限与实际值的差很大。这说明实际值一定大不到哪去。

考虑预处理出从 $10$ 开始的一定范围内中的最大答案，然后再加入卡时，如果枚举到某个时间点时还没有出答案，就直接输出预处理得到的结果。

这显然会牺牲一部分的正确性，但已经足以让我们通过 $48$ 个测试点。

再考虑观察答案可能的分布位置。

我们试着打个暴力，可以发现，当 $n$ 足够大时，答案集中分布在 $\frac{\sqrt n}{2}$ 附近。

于是我们又多通过了两个测试点。

再考虑答案的集中趋势是不行了，于是我们试试看极限情况 $y=10^{18}$ 时的数据。

我们会发现，在 $y$ 足够大，$l$ 略小的时候，答案即为 $\lfloor\frac{y}{k}\rfloor$，其中 $k$ 是一个较小的常数。


加上上述三个预处理即可通过本题。

### 2. 代码

```cpp
#include<bits/stdc++.h>
template<typename T1, typename T2>
constexpr auto max (T1 a, T2 b) -> decltype(a + b) {
    if (a > b)return a;
    return b;
}
using namespace std;
using ll = long long;
constexpr ll maxn1 = 999999, maxn2 = 1000, maxms = 114.514;
//分别为：从 10 开始枚举时的上限；sqrt(y) 附近的波动范围；暴力枚举的时间上限
ll change (ll l, ll b, ll y) {//把 l 当作 b 进制数，然后把 l 转回 10 进制
    if (l < 10)return l;
    auto a = change (l / 10, b, y);
    if (a >= y / b + 1 || !~a)return -1;//细节：如果直接返回 10 进制的值会溢出，所以判断是否大于 y，若是则直接返回 -1
    return a * b + l % 10;
}
bool check (ll l, ll b) {//判断是否满足“只包含十进制数字”
    if (l < b)return l < 10;
    return check (l / b, b) && l % b < 10;
}
inline auto gettime ( ) {//获取时间（精确到毫秒）
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now ( ).time_since_epoch ( )).count ( );
}
int main ( ) {
    ll y, l, ans = -1, L = 10, R = 1e18, m, beg = gettime ( );
    //分别为：题目中的 y 与 l；预处理的答案；二分答案的上下界；二分答案的中值；程序开始运行的时间
    cin >> y >> l;R = y;
    while (L < R) {//二分答案上界
        m = L + R + 1 >> 1;
        if (change (l, m, y) != -1 && change (l, m, y) <= y)L = m;
        else R = m - 1;
    }
    for (ll i = 10;i <= maxn1 && i <= L;i++)//预处理1
        if (check (y, i))ans = max (ans, i);
    if (sqrt (y) > maxn2)//细节：若 sqrt(y) 小于 maxn2，则二分答案已经可以出结果，预处理反而会 RE
        for (ll i = max (sqrt (y) / 2 - maxn2 / 3, 0);i <= sqrt (y) / 2 + maxn2 / 3 && i <= L;i++)//预处理2
            if (check (y, i))ans = max (ans, i);
    if (y > maxn1)
        for (ll i = maxn1;y / i < L && i>1 && y / i > 10;i--)
            if (check (y, y / i))ans = max (ans, y / i);//预处理3
    while (gettime ( ) - beg < maxms) {//带卡时的暴力枚举
        if (check (y, L)) {
            cout << L << endl;
            return 0;
        }
        L--;
    }
    cout << ans << endl;
    return false;
}
```

### 3.总结

二分答案是一个很好用的方法，并且如果能看出一些答案的分布规律的话可以结合使用。

### 4.UPD

[2022-10-13 22:44] 优化了代码的可读性。

---

## 作者：樱雪喵 (赞：3)

建议评蓝。

### 题意简述

给定两个十进制整数 $y$ 和 $l$，求最大的整数 $b$ 满足：

- $y$ 在 $b$ 进制下每一位的值均不大于 $9$。
- 将 $y$ 在 $b$ 进制下的数看作十进制，该数不小于 $l$。

其中 $10\le l\le y\le10^{18}$
。
### 解题思路

看起来没有使用任何高级算法，但其实不容易想到。

分成两部分来考虑。  
设 $y$ 转化为 $b$ 进制后看做十进制的值为 $x$。  

当 $b>10^6$ 时，$x$ 至多有三位，即 $x<10^3$。  
故我们可以枚举 $x$ 的值，对于确定的 $x$，当 $b$ 越大时还原出的 $y$ 越大，满足单调性。考虑二分 $b$，判断还原出的 $y$ 是否等于题目给定值。

当 $b\le 10^6$ 时，枚举 $b$ 的值暴力进行判断即可。

### 注意
- 特判当 $x>100$ 时的二分边界，否则会爆 `long long`。
- 两个 check 的进制转换都不要用数组+循环一位位存的写法，实测 TLE。
- 避免其它部分的大常数写法。


AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,a,b;
int check2(int k,int x){
	return x%10+(x/10%10)*k+(x/100)*k*k;
}
int check1(int x,int k)
{
	int now,tmp;
	now=0,tmp=1;
	while(x)
	{
		if(x%k>=10) return -1;
		now+=tmp*(x%k);
		x/=k;
		tmp*=10;
	}
	return now;
}
signed main()
{
	int ans=10;
	scanf("%lld%lld",&a,&b);
	for(int i=b;i<=1000;i++)
	{
		int l=10,r=1e18;
		if(i>=100) r=1e9;
		while(l<r)
		{
			int mid=(l+r)>>1;
			int qwq=check2(mid,i); 
			if(qwq>=a) r=mid;
			//else if(qwq==2) {l=mid;break;}
			else l=mid+1; 
		}
		if(check2(l,i)==a) ans=max(ans,l);
	}
	for(int i=1000000;i>=ans;i--)
		if(check1(a,i)>=b) {ans=i;break;}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Sunrise_beforeglow (赞：1)

首先我们要知道，如果进制 $b$ 越大，$y$ 在 $b$ 进制下的数看成 $10$ 进制后，就会越小。（不考虑存在字母的情况）。

我们要先知道 $y\le 10^6$ 的数据怎么过。

其实很简单，枚举进制 $b$，从 $10^6$ 枚举到 $10$，$b$ 肯定会大于等于十，否则还不如原来的数小。

我们可以写一个函数，判断 $y$ 在 $b$ 进制下是否有字母，顺便求出 $y$ 在 $b$ 进制下的数长什么样子。

```cpp
bool cnt(int y,int b)
{
	int u=y;
	ans=0;
	int tmp=1;
	while(u>0)
	{
		if(u%b>=10)return false;
		ans+=(u%b)*tmp;
		u/=b;
		tmp*=10;
	}
	return true;
	
}
```

接下来我们考虑 $y\le 10^{18}$ 怎么做。

如果 $b>10^6$ 那么 $y$ 在 $b$ 进制下的数一定会不到 $10^3$。因为 $(1000)_b=b^3$。

于是我们可以枚举 $y$ 在 $b$ 进制下的数，那我们怎么求出 $b$ 呢？

我们可以二分，因为 $y$ 在 $b$ 进制下的数固定（设为 $x$），$b$ 越大，$y$ 越大。这样我们可以求出使 $(x)_b\ge y$ 最小的 $b$，再检查 $(x)_b$ 是不是等于 $y$ 即可。

两个情况结合一下，就是最终答案。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int y,l,minn=2e18,cur,ans=0;
bool cnt(int y,int b)
{
	int u=y;
	ans=0;
	int tmp=1;
	while(u>0)
	{
		if(u%b>=10)return false;
		ans+=(u%b)*tmp;
		u/=b;
		tmp*=10;
	}
	return true;
	
}
int check(int x,int b)
{
	int u=(x%10)+(x/10%10)*b+(x/100)*b*b;
	return u;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>y>>l;
	for(int b=1e6;b>=10;b--)
	{
		if(cnt(y,b)==false)continue;
		if(ans<l)continue;
		if(ans<minn)
		{
			minn=ans;
			cur=b;
			break;
		}
	}
	for(int i=l;i<=999;i++)
	{
		int l=1e6-1,r=1e18;
		if(i>=100)
		{
			r=1e9;
		}
		while(l<r)
		{
			int mid=(l+r+1)/2;
			if(check(i,mid)<=y)l=mid;
			else r=mid-1;
		}
		if(check(i,l)==y)
		{
			if(i<minn)
			{
				minn=i;
				cur=l;
				break;
			}
		}
	}
	cout<<cur;
	return 0;
}
```

---

## 作者：LJ07 (赞：1)

简单题。

考虑类似 根号分治 的思路。

我们有两种暴力：第一种是枚举进制转换结果，二分出 $b$；第二种是枚举 $b$，求出结果。

那么正解就很显然了，用方法一求出转换结果在 $[b,9999]$ 之间的答案。然后枚举所有在 $[1,\sqrt[4]{n}]$ 的 $b$，去 check 它的转换结果是否合法。两种过程算出的 $b$ 取 max 即可。

[这种写法](https://www.luogu.com.cn/record/90030708) 被 [盐酸的乱搞写法](https://www.luogu.com.cn/record/90030763) 薄纱 qwq

```cpp
#include <bits/stdc++.h>
#define GC c=getchar()
#define IG isdigit(c)
template<class T=int>T frd(T x=0,char GC,bool f=1)
{
    for(;!IG;GC)f=c!='-';for(;IG;GC)x=x*10+(c^48);return f?x:-x;
}
using namespace std;
constexpr int N(1e4);
typedef long long ll;
typedef basic_string<int> SB;
int Task;ll old,lim,ans;SB Ret,Lim;
ll calc(ll x,ll y)
{
	ll les(old),t(1);
	for(int i(1);i<=4;++i,t=t*y)
	{
		if(les/t<x%10) return -1;les-=t*(x%10);
		if(!(x/=10)) break;if(les/y<t) return -1;
	}
	return les;
}
bool doit(SB &t,ll x,ll y)
{
	t.clear();
	do 
	{
		t.push_back(x%y);if(t.back()>9) return 0;
	} while(x/=y);
	return 1;
}
bool cmin(SB a,SB b)
{
	if(a.size()<b.size()) return 1;
	if(a.size()>b.size()) return 0;
	for(int i((signed)a.size()-1);~i;--i)
		if(a[i]<b[i]) return 1;
		else if(a[i]>b[i]) return 0;
	return 0;
}
signed main()
{
	for(Task=1;Task--;)
	{
		old=frd<ll>(),lim=frd<ll>(),ans=10;
		for(ll i(lim),L,R(old);L=0,R>ans&&i<N;++i)
		{
			for(ll mid;L<R;)mid=L+R+1>>1,calc(i,mid)>=0?L=mid:R=mid-1;
			if(R>ans&&!calc(i,L)) {ans=L;break;}
		}
		if(ans==10) 
		{
			doit(Lim,lim,10);
			for(ll i(pow(old,0.26));i>ans;--i)
				if(doit(Ret,old,i)&&!cmin(Ret,Lim))ans=i;
		}
		printf("%lld\n",ans);
	}
    return 0;
}
```

---

## 作者：Yansuan_HCl (赞：1)

[跑得飞快的非正解](https://www.luogu.com.cn/record/90030763)。

先满足第二个限制，看作十进制下大于等于 $l$。这可以二分 $b$。

此后逐步把 $b$ 向下调整以满足每位数字小于等于 $9$ 的限制。多测几组发现 $y$ 较大 $l$ 较小时：

- 调整很慢。
- $b$ 较大时搞出来的数很短。
- 无效调整：同样长度，在第一位或第二位就已经非法的，仍然缓慢地线性调整。

打表发现，同样长度的，在第一位不合法后，继续调整一定会让第一位更大。第二位不合法的，在第一位相同时，继续调整也不合法。因此，可以进行倍增剪枝。

```cpp
// 天若有情天亦老
using VLL = vector<ll>;
VLL sepe(ll x, ll b) {
	if (x == 0) return VLL(1);
	VLL v;
	while (x) {
		v.push_back(x % b);
		x /= b;
	}
	reverse(v.begin(), v.end());
	return v;
}

ll y, l;
VLL sL;
bool check(VLL v) {
	if (v.size() > sL.size()) return 1;
	if (v.size() < sL.size()) return 0;
	for (int x = 0; x != v.size(); ++x) {
		if (v[x] == sL[x]) continue;
		return v[x] > sL[x];
	}
	return 1;
}
bool check2(VLL v) {
	for (ll x : v) if (x > 9) return 0;
	return 1;
}

ll solve() {
	sL = sepe(l, 10);
	ll b = 10, e = y;
	while (b < e) {
		ll mid((b + e + 1) >> 1);
		if (check(sepe(y, mid))) 
			b = mid;
		else
			e = mid - 1;
	}
	VLL sp;
	while (sp = sepe(y, b), !check2(sepe(y, b))) {
		if (b > 10000 && sp[0] > 9) {
			for (ll dif = 1ll << 62; dif; dif >>= 1) if (b - dif > 10) {
				if (sepe(y, b - dif).size() == sp.size())
					b -= dif;
			}
		} else if (b > 10000 && sp.size() >= 2 && sp[1] > 9) {
			for (ll dif = 1ll << 62; dif; dif >>= 1) if (b - dif > 10) {
				VLL gg = sepe(y, b - dif);
				if (gg.size() == sp.size() && gg[0] == sp[0])
					b -= dif;
			}
		}
		--b;
	}
	
	return b;
}

int main() {	
	rd(y, l);
	printf("%lld\n", solve());
	return 0;
}
```

---

## 作者：optimize_2 (赞：1)

这题数据有问题，bzoj 上过了，发一篇题解。

## 题意

给你 $y$ 和 $l$，需要找到一个进制 $b$，使得 $y$ 的 $b$ 进制表示每一位都小于等于 $9$，且把这个数当成十进制（如 $3_{10}$ 转成 $11_2$，然后当成 $11_{10}$ 看待）大于等于 $l$。

## 暴力做法

枚举 $b$，然后把 $y$ 转成 $b$ 进制判断。

这个最多跑到 $10^8$，但是答案 $\leq 10^{18}$。

## 正解

那怎么办呢，因为 $y \leq 10^{18}$，所以对于 $b \ge 10^6$， $y_b$ 的位数一定不超过 $3$ 位，设其为 $\overline{a_1a_2a_3}$，然后有 $y = a_1b^2+a_2b+a_3$，枚举 $a_1, a_2, a_3$ 然后解一元二次方程更新答案即可求出大于 $10^6$ 的 $b$，然后再暴力一下算出小于等于 $10^6$ 的 $b$ 就好了。

## 代码

由于 $a_1, a_2, a_3$ 都是自然数，所以对称轴 $\dfrac{2a_1}{-a_2}$ 一定不在 $y$ 轴右侧，那就可以二分解二次方程，用公式法的时候记得开 `int128` 或 `long double`。 

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll T, y, l;

inline bool check1(ll i) {
    // 把 y 转成 i 进制
    ll base = 1, tmp = y, oct = 0;
    while (tmp) {
        if (tmp % i > 9) { return false; }
        oct += base * (tmp % i);
        tmp /= i; base *= 10;
    }
    if (oct < l) { return false; }
    return true;
}

inline ll solve1() {
    for (int i = 1000000; i >= 10; i--) {
        if (check1(i)) {
            return i;
        }
    }
}

ll eqans;
inline ll solveq(ll a, ll b, ll c) {
    ll l = 1, r = 1e9, ans;
    if (a == 0) { r = 1e18; }
    while (l <= r) {
        ll mid = (l + r) >> 1;
        ll res = a * mid * mid + b * mid +  c;
        if (res < y) {
            l = mid + 1;
        } else if (res == y) {
            return mid;
        } else {
            r = mid - 1;
        }
    }
    return -1;
}

inline ll solve2() {
    ll ans = 10;
    for (ll i = l; i <= 999; i++) {
        eqans = solveq(i / 100, i % 100 / 10, i % 10);
        if (eqans != -1 && eqans > max({i / 100, i % 100 / 10, i % 10})) {
            ans = max(ans, eqans);
        }
    }
    return ans;
}

int main() {
    scanf("%lld%lld", &y, &l);
    printf("%lld\n", max(solve1(), solve2()));
}
```

---

## 作者：FriedrichC (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P6921)

建议评蓝。

蒟蒻太菜了不会写二分，但是提供一种极其**玄学**的数学方法。

这种做法最快总时间可以跑进 $180ms$，~~是目前的最优解~~。
## 题意分析
首先将命题抽象为数学语言：即存在这样的 $b$，使得：

$\begin{cases}\sum\limits_{i=0}^{n}a_ib^i=y\\a_i\in [0,9]\\\overline{a_0a_1\dots a_n}\geqslant ℓ\end{cases}$

现要求求出 $b$ 的**最大值**。

## 解法
我们注意到，$b$ 只与第一个限制有关，我们不妨先将和式展开：

$$a_0b^0+a_1b^1+a_2b^2+\dots +a_nb^n=y$$

（注意：$n$ 并非 $y$ 在 $b$ 进制下的**位数**，由于下标从 $0$ 开始，位数是 $n+1$。）

要求 $b$ 的最值，我们可以尝试先求出 $b$ 的范围，这样就可以在范围内**枚举满足后两个条件**的 $b$ 中的最大值。

可以看到，$b$ 存在于多项式中的每一项，意图直接求 $b$ 的解似乎有点不现实，那么我们可以考虑对 $y$ 进行**放缩**。

容易得到：

$$a_nb^n\leqslant y\leqslant a_nb^n+9\times \sum\limits_{i=0}^{n-1}b^{i}$$

$y$ 的下界我们很容易理解，而 $y$ 的上界的含义是其 $b$ 进制下第 $n$ 位以前每一位的系数都取到**最大值**，这样必然大于 $y$。

这样一来，上界又出现了一个不好处理的和式，但是我们可以使用亿点点数学知识来解决这个问题，

由 $n$ 次方差公式有：

$$a^n-b^n=(a-b)\sum\limits_{i=0}^{n-1}a^{n-1-i}b^i$$

显然上述不等式中的和式是第二个数等于 $1$ 的特殊情况，那么我们有：

$$b^n-1=(b-1)\sum\limits_{i=0}^{n-1}b^{i}$$

那么原不等式变为：

$$a_nb^n\leqslant y\leqslant a_nb^n+9\times \dfrac{b^n-1}{b-1}$$

有了这个式子，我们可以**简单移项**解出 $b$ 的范围：

$$\sqrt[n]{\dfrac{y-9\times \frac{b^n-1}{b-1}}{a_n}}\leqslant b\leqslant \sqrt[n]{\dfrac{y}{a_n}}$$

如此这般，我们就貌似解出了 $b$ 的范围，

为了方便，我们把范围中的上下界分别记为 $r$ 和 $l$。

现在的问题在于，$l$ 仍然带有 $b$ 这个变量，也就是说 $l$ 也是**带有范围**的一个界限，那么该怎么处理呢？

我们只有取得一个**确定**的范围才可以进行枚举，那么我们不妨把 $l$ 中的 $b$ 当成 $r$，

这是因为，我们观察 $l$ 的表达式，我们发现当 $b$ 的值取得**越大**，$l$ 就**越小**，整个范围 $[l,r]$ 所能覆盖的范围也就**越大**，我们就可以覆盖**更多**可能的解，于是干脆让 $b$ 取 $r$。

这样，我们就解决了 $b$ 的范围的问题。

那么实现代码的思路就很清晰了：

在范围的表达式中，尽管 $n$ 和 $a_n$ 的相对于 $b$ 来说是常数，但是我们显然不能确定其确切的值，因此我们多用两层循环来分别枚举 $n$ 和 $a_n$，然后最内层循环贪心地**从大到小**枚举 $b$，第一个满足条件的 $b$ 就是答案了。

显然 $a_n$ 从 $1$ 到 $9$ 枚举，而 $n$ 从 $\lg(ℓ)$ 枚举到 $18$，也就是 $b$ 取 $10$ 时 $n$ 的范围，因为 $b$ 最小取 $10$。

总的来说，我们通过放缩和 $a_n$ 的枚举范围的限定，使得第二个条件满足，然后检查每一次的枚举的 $b$，看看是否可以满足条件三。
## 代码
$L$ 是原题中的 $ℓ$，循环中的 $r$ $l$ 即上下界。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
    int x=0;
    char ch=getchar();
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x;
}
inline int change(int x,int k)//将x转成k进制
{
    int ans=0,base=1;
    do{
        int res=x%k;
        if(res>9)return -1;
        ans+=res*base;
        base*=10;
    }while(x/=k);
    return ans;
}
int solve(int y,int L)
{
    for(int i=log10l(L);i<=18;++i)//i枚举n
        for(int j=1;j<=9;++j)//j枚举an
            for(int r=powl(y/j,1.0l/i),l=
            max(powl((y-9*(powl(r,i)-1)/(r-1))/j,1.0l/i),(long double)10);r>=l;r--)
            //取max是因为合法的b必然不小于10
                if(change(y,r)>=L)return r;
}
signed main()
{
    int y,L;
    y=read(); L=read();
    printf("%lld\n",solve(y,L));
	return 0;
}
```
## 小小的优化
我们发现，当 $b$ 在 $10^3$ 以内时，$y$ 的取值大于 $10^6$，于是我们的 $n$ 可以只枚举到 $6$，然后再从 $10^3$ 往后枚举 $b$。

那么我们的 `solve` 就可以改写成这样：

```cpp
int solve(int y,int L)
{
    for(int i=log10l(L);i<=6;++i)
        for(int j=1;j<=9;++j)
            for(int r=powl(y/j,1.0l/i),l=
            max(powl((y-9*(powl(r,i)-1)/(r-1))/j,1.0l/i),(long double)10);r>=l;r--)
                if(change(y,r)>=L)return r;
    int b=1000;
    while(change(y,b)<L)b--;
    return b;
}
```

这样做有什么意义呢？

在其他的题解之中，把答案 $b$ 分成大于和小于 $10^6$ 两部分（和这里分 $y$ 还不一样），应该是为了契合二分的复杂度，但是上述做法与二分的复杂度截然不同，完全没有分类讨论数据范围的意义，直接枚举到 $18$ 就是最自然的做法。

所以对于这个做法，以不同界限分类讨论都是等效的，大可以 $n$ 枚举到 $7$ 然后 $b$ 从 $100$ 枚举。

虽然但是，分类讨论之后效率确实提升了，算是一点小小的玄学吧。~~虽然也没快多少毫秒。~~

## 其他细节
这是几组不同的随机数据的运行过程中 $l$ $r$ 的值：

```cpp
10
total cases: 10
case 1:
60020426738060053 50051308377938177
l=10 r=11
l=10 r=10
b=10
case 2:
612458770811678548 512796829710033642
l=10 r=11
l=10 r=10
b=10
case 3:
266172360996368146 168570151614898983
l=10 r=10
b=10
case 4:
915304946786352976 590632969401747937
l=10 r=11
l=10 r=10
b=10
case 5:
454964508730118399 254260901411309574
l=10 r=10
b=10
case 6:
749759099039129573 445013129703003682
l=10 r=11
l=10 r=10
b=10
case 7:
419158777677439514 143969159430613757
l=10 r=10
b=10
case 8:
207394525422695346 188350031124348620
l=10 r=10
b=10
case 9:
265611900612917948 172695560922414614
l=10 r=10
b=10
case 10:
9128725194275439 6213904532901355
l=11 r=11
l=10 r=11
l=10 r=10
b=10
```

事实证明，当 $y$ 和 $ℓ$ 取值较大时，$l$ 和 $r$ 的差别非常之小，所以我们使用的各种数学函数比如 `log10` 和 `pow` 很可能会掉精度。~~蒟蒻因为这个调了很久。~~

那么，为了提升精度，我们可以使用这些函数的 `long double` 版本，并且常数 `1` 也要写成 `1.0l`。

（注：关于 `long double` 和 `double` 的精度网上有许多争议，读者可以自行了解，但是本题中最好使用前者。）

最后一点，在 $l$ 和 $10$ 取 max 时，一定要记得 $10$ 的类型转换，否则会 `CE`。













---

## 作者：transitory (赞：0)

由 $y \le 10^{18}$ 可以知道，当 $b > 10^6$ 时，进制转换后看成十进制时位数最多只有 $3$ 位，可以分情况讨论计算。

当 $b \le 10^6$ 时，正常进制转换并计算即可。

当 $b > 10^6$ 时，可以枚举转换后看成十进制的 $y$，接着根据单调性二分计算 $b$，即可求解。

注意边界问题，小心爆 `long long`。

注：代码来自大号 [\_yang_yi_bo_](https://www.luogu.com.cn/user/1265919)，所以大号并不构成抄袭题解。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int getans(int x,int k){
	int now=0,temp=1;
	while(x){
		if(x%k>=10)return -1;
		now+=temp*(x%k);
		x/=k;
		temp*=10;
	}return now;
}
int check(int x,int k){
	return x%10+(x/10%10)*k+x/100*k*k;
}
int n,m,i,ans=10,l,r,mid;
signed main(){
    cin>>n>>m;
    for(int i=m;i<=999;i++){
    	l=0,r=(int)1e18+1;
    	if(i>=100)r=1e9;
    	while(l+1<r){
    		int mid=(l+r)>>1;
    		if(check(i,mid)>=n)r=mid;
    		else l=mid;
		}if(check(i,r)==n)ans=max(ans,r);
	}for(int i=1000000;i>=ans;i--){
		if(getans(n,i)>=m){
			ans=i;
			break;
		}
	}cout<<ans;
    return 0;
}
```

---

