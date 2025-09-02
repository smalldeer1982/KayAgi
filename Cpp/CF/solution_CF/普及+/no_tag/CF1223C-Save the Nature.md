# Save the Nature

## 题目描述

You are an environmental activist at heart but the reality is harsh and you are just a cashier in a cinema. But you can still do something!

You have $ n $ tickets to sell. The price of the $ i $ -th ticket is $ p_i $ . As a teller, you have a possibility to select the order in which the tickets will be sold (i.e. a permutation of the tickets). You know that the cinema participates in two ecological restoration programs applying them to the order you chose:

- The $ x\% $ of the price of each the $ a $ -th sold ticket ( $ a $ -th, $ 2a $ -th, $ 3a $ -th and so on) in the order you chose is aimed for research and spreading of renewable energy sources.
- The $ y\% $ of the price of each the $ b $ -th sold ticket ( $ b $ -th, $ 2b $ -th, $ 3b $ -th and so on) in the order you chose is aimed for pollution abatement.

If the ticket is in both programs then the $ (x + y) \% $ are used for environmental activities. Also, it's known that all prices are multiples of $ 100 $ , so there is no need in any rounding.

For example, if you'd like to sell tickets with prices $ [400, 100, 300, 200] $ and the cinema pays $ 10\% $ of each $ 2 $ -nd sold ticket and $ 20\% $ of each $ 3 $ -rd sold ticket, then arranging them in order $ [100, 200, 300, 400] $ will lead to contribution equal to $ 100 \cdot 0 + 200 \cdot 0.1 + 300 \cdot 0.2 + 400 \cdot 0.1 = 120 $ . But arranging them in order $ [100, 300, 400, 200] $ will lead to $ 100 \cdot 0 + 300 \cdot 0.1 + 400 \cdot 0.2 + 200 \cdot 0.1 = 130 $ .

Nature can't wait, so you decided to change the order of tickets in such a way, so that the total contribution to programs will reach at least $ k $ in minimum number of sold tickets. Or say that it's impossible to do so. In other words, find the minimum number of tickets which are needed to be sold in order to earn at least $ k $ .

## 说明/提示

In the first query the total contribution is equal to $ 50 + 49 = 99 < 100 $ , so it's impossible to gather enough money.

In the second query you can rearrange tickets in a following way: $ [100, 100, 200, 200, 100, 200, 100, 100] $ and the total contribution from the first $ 6 $ tickets is equal to $ 100 \cdot 0 + 100 \cdot 0.1 + 200 \cdot 0.15 + 200 \cdot 0.1 + 100 \cdot 0 + 200 \cdot 0.25 = 10 + 30 + 20 + 50 = 110 $ .

In the third query the full price of each ticket goes to the environmental activities.

In the fourth query you can rearrange tickets as $ [100, 200, 100, 100, 100] $ and the total contribution from the first $ 4 $ tickets is $ 100 \cdot 0 + 200 \cdot 0.31 + 100 \cdot 0 + 100 \cdot 0.31 = 62 + 31 = 93 $ .

## 样例 #1

### 输入

```
4
1
100
50 1
49 1
100
8
100 200 100 200 100 200 100 100
10 2
15 3
107
3
1000000000 1000000000 1000000000
50 1
50 1
3000000000
5
200 100 100 100 100
69 5
31 2
90
```

### 输出

```
-1
6
3
4
```

# 题解

## 作者：lgmulti (赞：2)

本题原来题意是
> 在选取个数最小的情况下最大捐赠数额 $\geq k$。

可以看出选取个数越大，最大捐赠数额只会增大，所以我们可以用二分。

然后剩余要解决的问题变成了：
> 选取$pos$张票时最大捐赠数额能否 $\geq k$。

显而易见，该问题的解法是求出这个最大值，然后判断它是否 $\geq k$。

想要值最大，首先得选取价格最贵的票，所以可以将票排序。然后，尽量将价格贵的票给捐赠百分比大的，然后把价格便宜的票给捐赠百分比小的。本题中共有3种百分比
 
 - $(x+y)%$：当该票位置能同时被$a$和$b$整除。即被$\operatorname{lcm}(a,b)$整除（注意不是$ab$)。
 - $x%$：当该票位置只能被$a$整除。
 - $y%$：当该票位置只能被$b$整除。
 
 所以可以算出三种情况的数量，再从大到小分配票。
 
主要代码如下

```cpp
bool judge(long long pos){
	long long i,j;
	long long both=pos/(x*y/gcd(x,y)); 
	long long big=pos/x-both;
	long long small=pos/y-both;
	long long ans=0ll;

	for(i=n-1;i>=n-pos;i--){
		long long amt=(n-1)-i+1;
		if(amt<=both)
			ans+=p[i]/100ll*(a+b);
		else if(amt>both && amt<=both+big)
			ans+=p[i]/100ll*a;
		else if(amt>both+big && amt<=both+big+small)
			ans+=p[i]/100ll*b;
		else
			break;
	}
	return ans>=k;
}
```

---

## 作者：yuzhechuan (赞：2)

承接楼下，我给出$O(nlog^2n)$和$O(nlogn)$的算法

---

二分答案楼下已讲过，由单调性可得，十分好想，一只log

重点在于check部分，有两种思路

---

### 1. 暴力sort两只log (156ms)

思维难度低，代码难度低

关键是出题人没来卡

先O(n)扫一遍，得到每天的贡献（百分比）

O(nlogn)从大到小排序，与每天的值配对

```cpp
bool check(int n){
	int sum=0;
	for(int i=1;i<=n;i++){
		b[i]=0;
		if(i%al==0) b[i]+=x; //有第一种贡献
		if(i%be==0) b[i]+=y; //有第二种贡献
	}
	sort(b+1,b+1+n,greater<int>()); //greater<int>()是自带的一个比较函数，用来从大到小排
	for(int i=1;i<=n;i++) sum+=a[i]*b[i]; //a[]在main()中均已除以100，直接暴力配对
	return sum>=k;
}
```

---

### 2. lcm容斥一只log (62ms)

跑的飞快，毕竟正解

我们发现如果有贡献，只有三种情况，即a的倍数,b的倍数,lcm(a,b)的倍数

方便起见，先做这么一件事：

```cpp
if(x<y) swap(x,y),swap(al,be);
```
这样就保证lcm优于a,a优于b了

用除法算出a,b,lcm各有几个记为xn,yn,xyn

由容斥原理可得xn,yn都要减去xyn

使得可以保证a,b,lcm贡献互不相交

然后分三段按照lcm(x+y),a(x),b(y)的顺序扫一遍即可

```cpp
bool check(int n){
	int sum=0,xn=n/al,yn=n/be,xyn=n/lcm; //除法计算
	xn-=xyn; //容斥
	yn-=xyn;
	for(int i=1;i<=xyn;i++) sum+=(x+y)*a[i]; //lcm段
	for(int i=xyn+1;i<=xyn+xn;i++) sum+=x*a[i]; //a段
	for(int i=xyn+xn+1;i<=xyn+xn+yn;i++) sum+=y*a[i]; //b段
	return sum>=k;
}
```

---

### 代码

#### 两只log

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	x=0;char c=getchar();bool f=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0){putchar('-'),write(-x);}
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}

#define int long long

const int N=2e5+5;
int q,n,a[N],b[N],k,x,y,be,al;

bool check(int n){
	int sum=0;
	for(int i=1;i<=n;i++){
		b[i]=0;
		if(i%al==0) b[i]+=x;
		if(i%be==0) b[i]+=y;
	}
	sort(b+1,b+1+n,greater<int>());
	for(int i=1;i<=n;i++) sum+=a[i]*b[i];
	return sum>=k;
}

void doit(){
	read(n);
	for(int i=1;i<=n;i++) read(a[i]),a[i]/=100;
	sort(a+1,a+1+n,greater<int>());
	read(x);read(al);
	read(y);read(be);
	read(k);
	int l=1,r=n,ans=-1;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	write(ans);puts("");
}

signed main(){
	read(q);
	while(q--) doit();
}
```

#### 一只log

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	x=0;char c=getchar();bool f=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0){putchar('-'),write(-x);}
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}

#define int long long

const int N=2e5+5;
int q,n,a[N],b[N],k,x,y,be,al,lcm;

bool check(int n){
	int sum=0,xn=n/al,yn=n/be,xyn=n/lcm;
	xn-=xyn;
	yn-=xyn;
	for(int i=1;i<=xyn;i++) sum+=(x+y)*a[i];
	for(int i=xyn+1;i<=xyn+xn;i++) sum+=x*a[i];
	for(int i=xyn+xn+1;i<=xyn+xn+yn;i++) sum+=y*a[i];
	return sum>=k;
}

void doit(){
	read(n);
	for(int i=1;i<=n;i++) read(a[i]),a[i]/=100;
	sort(a+1,a+1+n,greater<int>());
	read(x);read(al);
	read(y);read(be);
	if(x<y) swap(x,y),swap(al,be);
	lcm=al*be/__gcd(al,be);
	read(k);
	int l=1,r=n,ans=-1;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	write(ans);puts("");
}

signed main(){
	read(q);
	while(q--) doit();
}
```

---

## 作者：zzr123bc (赞：1)

# 思路
我用的是二分答案，二分最少使用个数，先把输入进来的票价进行排序，再开一个数组存第 $i$ 张票可以捐赠出去多少。由于票可以随便排序，所以一张票可以选择任意一种捐赠的百分比（之前用过的除外），我们可以将存捐赠百分比的数组进行排序，使得捐赠的钱数最大化，以下是我的代码。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
long long n,k,q,x,y,a1,b1;
long long shu[200050],cnt[200050];
bool cmp(long long a,long long b){
	return a>b;
}
bool check(long long m){
	memset(cnt,0,sizeof(cnt));
	for(long long i=1;i<=m;i++){
		if(i%a1==0){
			cnt[i]+=x;
		}
		if(i%b1==0){
			cnt[i]+=y;
		}
	}
	long long sum=0;
	sort(cnt+1,cnt+m+1,cmp);
	for(int i=1;i<=m;i++) sum+=shu[i]/100*cnt[i];
	return sum>=k;
}
int main(){
	cin>>q;
	while(q--){
		cin>>n;
		for(long long i=1;i<=n;i++){
			cin>>shu[i];
			shu[i];
		}
		sort(shu+1,shu+n+1,cmp);
		cin>>x>>a1>>y>>b1>>k;
		long long l=1,r=n,ans=-1;
		while(l<=r){
			long long mid=l+(r-l)/2;
			if(check(mid)){
				ans=mid;
				r=mid-1;
			}
			else{
				l=mid+1;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
我是蒟蒻，大佬勿喷，谢谢。

---

## 作者：Allanljx (赞：1)

## 题意
有 $n$ 个数。 $a$ 的倍数的数要取其中百分之 $x$ ； $b$ 的倍数的数要取其中百分之 $y$ 。将所有取得的数加起来，总和要求大于 $k$ 。要求取尽量少的数然后排序，使其满足要求。
## 思路
用二分去查取多少个数，要从大到小排序给定的数。难点就在 $check$ 上。 $check$ 里先要求出每个位置上的数要乘几，然后从大到小排序，在和原本这个位置上的数相乘。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,y,a1,b1,k;
int a[200001],b[200001];
bool cmp(int a,int b)//cmp从大到小排序
{
	return a>b;
}
bool check(int z)
{
	int sum=0;
	for(int i=1;i<=z;i++)//要乘几
	{
		b[i]=0;
		if(i%a1==0) b[i]+=x;
		if(i%b1==0) b[i]+=y;
	}
	sort(b+1,b+z+1,cmp);//从大到小排序
	for(int i=1;i<=z;i++) sum+=a[i]*b[i];//相乘
	return sum>=k;
}
main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			a[i]/=100;
		}
		sort(a+1,a+n+1,cmp);//从大到小排序
		cin>>x>>a1>>y>>b1>>k;
		int l=1,r=n,ans=-1;
		while(l<=r)//二分
		{
			int mid=l+r>>1;
			if(check(mid))//满足条件要少取一个数，右端点减少
			{
				ans=mid;
				r=mid-1;
			}
			else//不满足条件要多去一个数，左端点增加
			{
				l=mid+1;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：墨舞灵纯 (赞：1)

没人写题解，我讲个思路。

很显然如果第x天可行，那么第x+1天肯定也可行，因为你往后只会多获得收益不会少获得收益。

那么答案具有单调性，二分一下即可。

实现代码的时候注意一下：

1.先把读进来的每天收益排个序

2.先把可以最大的几天获得（x+y）收益的计算出来

3.然后优先计算x或y中收益较大的一项。

4.最后不要忘记检验答案是否可行要不要输出-1

算是二分答案的基础题吧。代码留给读者。

---

## 作者：Rex01 (赞：0)

## [CF1223B 题目传送门](https://www.luogu.com.cn/problem/CF1223B)

## 题目大意
总共 $q$ 次询问，每次询问有 $n$ 个数，随后四个数 $x,a,y,b$，表示 $n$ 个数中的第 $a,2a,3a\cdots$ 个数有 $x\%$ 的贡献，第 $b,2b,3b\cdots$ 个数有 $y\%$ 的贡献。如果数列中的某一个数是 $a,b$ 的公倍数，则它有$(x+y)\%$ 的贡献。求贡献 $\geq k$ 时，最少用多少个数。

## 解决思路
可以发现选取的数越大，贡献就越大，因此我们可以将数列从大到小排序，并用**二分**，求出贡献最大值，若 $\geq k$ 则输出，否则输出 $-1$。可以发现总共有三种情况（按优先级从大到小讨论）：
- $a_i$ 可以被 $a,b$ 的公倍数整除，有 $(x+y)\%$ 的贡献；
- $a_i$ 可以被 $a$ 整除，有 $x\%$ 的贡献；
- $a_i$ 可以被 $b$ 整除，有 $y\%$ 的贡献。

分别算出三种情况并从大到小分配票即可。

## 代码展示
```cpp
#include <iostream>
#include <algorithm>
//拒绝万能头，从我做起
#define ll long long
//不开 long long 见祖宗
using namespace std;

const int N = 2e5 + 10;
ll q, n, p[N], x, a, y, b, k, p1[N];

bool cmp(ll x, ll y)
{//排序函数
	return x > y;
}

bool check(ll m)
{//二分检查函数
	ll sum = 0;
	for(ll i = 1; i <= m; i++)
	{
		p1[i] = 0;
		if(i % a == 0) p1[i] += x;
		if(i % b == 0) p1[i] += y;
	}
	sort(p1 + 1, p1 + m + 1, cmp);//从大到小排序 
	for(ll i = 1; i <= m; i++)
		sum += p[i] * p1[i];
	return sum >= k;
}

int main()
{
    cin >> q;
    while(q--)
    {
    	cin >> n;
    	for(ll i = 1; i <= n; i++)
        {
            cin >> p[i];
        	p[i] /= 100;//除以100方便计算
        }
    	sort(p + 1, p + n + 1, cmp);//从大到小排序
    	cin >> x >> a >> y >> b >> k;
    	ll l = 1, r = n + 1;
    	while(l < r)
    	{//二分答案
    		ll mid = (l + r) >> 1;
    		if(check(mid)) r = mid;
    		else l = mid + 1;
		}
		if(r == n + 1) cout << -1 << endl;
		else cout << r << endl;
	}
    return 0;
}
```

---

## 作者：Peter20122012 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1223C)

## 思路
题目求捐赠不小于 $k$ 时，**最少**使用多少个数。由于当选的数更少时，捐赠最大值不可能更大，所以考虑使用二分。
可以想到应该把更大的数选在捐献百分比更大的位置，当选择 $k$ 个数时，每个位置有三种捐献：
1. 当 $i \bmod \operatorname{lcm}(a, b) = 0$ 时，增加 $(x + y)\%$，共有 $\big\lfloor \frac{k}{\operatorname{lcm}(a, b)}\big\rfloor$ 个位置是这一种情况，且由于 $1 \le x, y$，所以 $(x + y)\%$ 一定最大。
2. 当 $i \bmod a = 0$ 时，增加 $x\%$，共有 $\big\lfloor \frac{k}{a} \big\rfloor - \big\lfloor \frac{k}{\operatorname{lcm}(a, b)}\big\rfloor$ 个位置是这一种情况。
3. 当 $i \bmod b = 0$ 时，增加 $y\%$，共有 $\big\lfloor \frac{k}{b} \big\rfloor - \big\lfloor \frac{k}{\operatorname{lcm}(a, b)}\big\rfloor$ 个位置是这一种情况。

只需要从大到小对这些数进行排序，然后调用 $\operatorname{check}$ 函数时按捐献百分比从大到小的顺序将从大到小分配这些数即可。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (ll i = st; i <= ed; ++i)
#define RFOR(st, ed, i) for (ll i = ed; i >= st; --i)
#define fir first
#define sec second

//#define debug

typedef long long ll;
typedef double db;
typedef pair<ll, ll> pll;

const ll maxn = 2e5 + 10;
ll gcd (ll x, ll y) {
	if (x < y) {swap(x, y);}
	while (y) {
		x %= y;
		swap(x, y);
	}
	return x;
}
ll lcm (ll x, ll y) {
	return x/gcd(x, y)*y;
}

ll q;
	ll n;
	ll p[maxn];
	ll x, a;
	ll y, b;
	ll k;
bool check (ll mid)/*check(mid) == true:卖出 mid 张票时可以使总的计划贡献达到至少 k，应该向左找*/ {
	ll cntxy = mid/lcm(a, b), cntx = mid/a - cntxy, cnty = mid/b - cntxy;
	ll res = 0;
	FOR (1, cntxy, i) {
		res += (ll)(x + y)*p[i];
	}
	FOR (cntxy + 1, cntxy + cntx, i) {
		res += (ll)(x)*p[i];
	}
	FOR (cntxy + cntx + 1, cntxy + cntx + cnty, i) {
		res += (ll)(y)*p[i];
	}
	
	return res >= k;
}

ll l, r, mid;

void work_q () {
	scanf("%lld", &n);
	FOR (1, n, i) {
		scanf("%lld", &p[i]);
		
		p[i] /= 100;
	}
	scanf("%lld%lld", &x, &a);
	scanf("%lld%lld", &y, &b);
	scanf("%lld", &k);
	
	if (x < y) {
		swap(x, y);
		swap(a, b);
	}
	sort(p + 1, p + n + 1, greater<>());
	l = 1;
	r = n + 1;
	while (l < r) {
		mid = (l + r)/2;
		if (check(mid)) {
			r = mid;
		}else {
			l = mid + 1;
		}
	}
	if (r == n + 1) {printf("-1\n");}
	else {printf("%lld\n", r);}
}
int main () {
	scanf("%lld", &q);
	while (q--) {work_q();}
	return 0;
}
```

---

## 作者：OIerZhang (赞：0)

# [CF1223C Save the Nature](https://www.luogu.com.cn/problem/CF1223C)

## 思路

这道题给出的数都为正整数，且计算总捐赠额用加法，这就意味着选的个数越多，总额越大，满足单调性，我们便可二分答案。

要求捐赠不小于 $k$ 时，最少使用多少个数，我们可以把给出的数从大到小排序，这样选出的数一定最优。

`check` 函数也很好写，我们计算所选数捐赠的百分比，再将百分比从大到小排序（大的百分比配大的数），计算总和并判断是否大于 $k$ 即可。

还有一个翻译没提到的点，给出的数都是 $100$ 的倍数，所以不用四舍五入。

## 核心代码

`check` 函数：

```cpp
bool check(int mid) // p[i] 是所给的数，t[i] 是百分比
{
    for (int i = 1; i <= mid; i++)
        t[i] = 0; // 多测清空！
    for (int i = 1; i <= mid; i++) // 计算所选数捐赠的百分比
    {
        if (i % a == 0)
            t[i] += x;
        if (i % b == 0)
            t[i] += y;
    }
    sort(t + 1, t + 1 + mid, cmp); // 大的百分比配大的数
    int res = 0;
    for (int i = 1; i <= mid; i++)
    {
        res += p[i] / 100 * t[i];
    }
    if (res >= k)
        return true;
    else
        return false;
}
```

主函数：

```cpp
cin >> n;
for (int i = 1; i <= n; i++)
    cin >> p[i];
cin >> x >> a >> y >> b >> k;
sort(p + 1, p + 1 + n, cmp);
int l = 1, r = n, mid, ans = 2e9;
while (l <= r)
{
    mid = (l + r) >> 1;
    if (check(mid))
    {
        r = mid - 1;
        ans = min(ans, mid);
    }
    else
        l = mid + 1;
}
if (ans == 2e9)
    ans = -1;
cout << ans << endl;
```

---

