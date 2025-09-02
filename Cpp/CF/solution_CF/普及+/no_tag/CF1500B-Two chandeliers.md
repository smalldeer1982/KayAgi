# Two chandeliers

## 题目描述

Vasya is a CEO of a big construction company. And as any other big boss he has a spacious, richly furnished office with two crystal chandeliers. To stay motivated Vasya needs the color of light at his office to change every day. That's why he ordered both chandeliers that can change its color cyclically. For example: red – brown – yellow – red – brown – yellow and so on.

There are many chandeliers that differs in color set or order of colors. And the person responsible for the light made a critical mistake — they bought two different chandeliers.

Since chandeliers are different, some days they will have the same color, but some days — different. Of course, it looks poor and only annoys Vasya. As a result, at the $ k $ -th time when chandeliers will light with different colors, Vasya will become very angry and, most probably, will fire the person who bought chandeliers.

Your task is to calculate the day, when it happens (counting from the day chandeliers were installed). You can think that Vasya works every day without weekends and days off.

## 说明/提示

In the first example, the chandeliers will have different colors at days $ 1 $ , $ 2 $ , $ 3 $ and $ 5 $ . That's why the answer is $ 5 $ .

## 样例 #1

### 输入

```
4 2 4
4 2 3 1
2 1```

### 输出

```
5```

## 样例 #2

### 输入

```
3 8 41
1 3 2
1 6 4 3 5 7 2 8```

### 输出

```
47```

## 样例 #3

### 输入

```
1 2 31
1
1 2```

### 输出

```
62```

# 题解

## 作者：Lynkcat (赞：8)

题目中有非常关键的信息：

The second line contains n 
**different**
integers a_i.

The third line contains m 
**different**
integers b_i.

也就是说我们找到 $a$ 中 $b_x$ 所在的位置，那么一个时刻 $p$ 在 $a$ 中和 $b$ 中对应的值均为 $a$ 时,其 $\bmod\ n$ 的值必然是固定的。

于是我们可以对于每一种 $p\times m \bmod n$ 的值算出在这一小轮（ 指扫一次 $m$ ）有多少贡献。我们发现 $p \times m \bmod n$ 必然是有循环节并且长度 $\leq n$ ，那么我们只需要算出一大轮 即 $p \leq lcm(n,m)$ 时总共有多少个时刻会让 Vasya 不高兴，然后算答案时刻是在哪一大轮，最后确定那一小轮，然后在那一小轮里确定最终的时刻即可。

时间复杂度为 $O(n)$ 。
 

---

## 作者：Cry_For_theMoon (赞：3)

[传送门](https://codeforces.ml/contest/1500/problem/B)

~~曾经比赛时因为不会 exgcd 列出了方程然后束手无策~~

注意到：

$A,B$ 两个数组都没有重复元素，且 $A,B$ 不完全相同。

后半部分很好理解，就是保证了不存在无解的情况。

前半部分则告诉我们，如果 $a=b$ 的情况出现，如果确定了 $a$ 的出现位置，$b$ 的出现位置唯一。所以我们枚举 $A_i$，设 $B$ 中出现 $A_i$ 的是 $B_j$，则 $A_i,B_j$ 同时取到当且仅当第 $l$ 次操作满足：

$$\begin{cases}l \equiv i\,(\bmod\,n) \\ l \equiv j\,(\bmod\,m)  \end{cases}$$

这个线性方程组可以在 $O(\log n)$ 的时间内求出来。这里我比较菜用了 Excrt，不知道两个方程有没有别的办法，不过 excrt 可以解决这题的拓展，即三个以上数组元素同时相等。至于拓展中国剩余定理就不多说了可以板子区学习这个简单算法。

如果求出了最小的满足条件的**正整数** $l$，我们就可以考虑二分答案 $mid$. 注意到方程组的通解是 $l+klcm(n,m)$ ($k$ 是整数），那么就很好统计了。

总复杂度即是 $O(n\log n)$ 的。~~CF 上最慢点1.76s，一共跑了31s~~

BTW，当然我们是可以进一步抛弃二分的。注意到每 $lcm(n,m)$ 次操作构成一个循环。求出 $lcm(n,m)$ 次操作的贡献，那么剩下 $<lcm(n,m)$ 次操作就是不完整的。如果我们把每对的相遇时间拉出来排序成 $t_1<t_2<...<t_p$，那么第一次相遇发生在 $t_1$，第二次在 $t_2$，第 $p$ 次在 $t_p$，第 $p+1$ 次在 $t_1+lcm(n,m)$...... 以此类推。所以可以 $O(1)$ 计算这部分。（但似乎时间复杂度也没变啊，写起来还麻烦，写不动）。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
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
const int MAXN=1e6+10;
ll n,m,k,a[MAXN],b[MAXN];
ll t[2][MAXN],minn[MAXN],add;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a/gcd(a,b)*b;}
void exgcd(ll a,ll b,ll& x0,ll& y0){
	if(!b){x0=1;y0=0;return;}
	exgcd(b,a%b,x0,y0);
	ll x=y0,y=x0-(a/b)*y0;
	x0=x,y0=y;
}
ll mul(ll a,ll b,ll mod){
	ll res=0;
    while(b>0){
        if(b&1)res=(res+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return (res%mod+mod)%mod;
}
ll Calc(ll i,ll j){
	ll minx=i,add=n; 
	ll c=j-minx,d=gcd(add,m);
	if(c%d)return -1;
	ll x,y;exgcd(add,m,x,y);
	ll add2=m/d,mult=c/d;
	if(mult>=0)mult%=add2;
	else mult=mult+((-mult+add2-1)/add2)*add2;
	x=mul(x,mult,add2);
	if(x>=0)x%=add2;
	else x=x+((-x+add2-1)/add2)*add2;
	minx=minx+add*x;
	add=lcm(n,m);
	if(minx>=0)minx%=add;
	else minx=minx+((-minx+add-1)/add)*add;
	if(!minx)minx=add;
	return minx;
}
bool check(ll mid){
	ll cnt=mid;
	rep(i,1,n){
		if(!t[1][a[i]])continue;
		if(minn[i]>mid || minn[i]==-1)continue;
		cnt-=(1+(mid-minn[i])/add);
	}
	return cnt>=k;
}
int main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	rep(i,1,n){scanf("%lld",&a[i]);t[0][a[i]]=i;}
	rep(i,1,m){scanf("%lld",&b[i]);t[1][b[i]]=i;}
	ll L=1,R=3e18,ans;add=lcm(n,m);
	rep(i,1,n){
		if(!t[1][a[i]])continue;
		minn[i]=Calc(i,t[1][a[i]]); 
	}
	while(L<=R){
		ll mid=(L+R)>>1;
		if(check(mid)){
			ans=mid;R=mid-1;
		}else{L=mid+1;}
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：血色黄昏 (赞：1)

注意到不会有重复的数在一个序列中，于是我们只需遍历 b 找到 a 中是否有这个数，如果有就计算他们第一次相遇的时间，存下来。那么我们就统计出了在一个循环中有几天会让她不高兴，然后对 k 不断取模到小于 一次循环然后根据两盏灯相同的时间遍历输出答案即可，这样查找后复杂度就是 $O(n)$ 的了，与 k 无关。

计算相遇时间只需要判断是否能相遇然后解一个同余方程组即可。

代码赛时没写完，后来补得。

最后统计答案用二分也是可以的，可以看 tourist 的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, k, a[500010], b[500010], tong[500010], ti = 0, maxn = -1;
long long ans = 0;//以上为定义，初始化
int mod;
vector<int>l;
int solve(int day)//统计答案
{
	//solve it;
}
void exgcd(int a,int b,int &x,int &y)//gcd函数
{
    if(b == 0){x = 1;y = 0;return ;}
    exgcd(b, a % b, x, y);
    int z = x;x = y, y = z - y * (a / b);
}
int ex(int a, int b)//求公共解
{
	int d = a - b;
	if(d % __gcd(n, m))return -1;
	d = __gcd(n, m);
	int p1 = n / d, p2 = m / d;
	int r1, r2;
	exgcd(p1, p2, r1, r2);
	int x = a + (b - a) * r1 * n / d;
	return x;
}
int main()
{
	cin>>n>>m>>k;
	mod = n * m;
	for(int i = 1;i <= n;i ++)
	{
		cin>>a[i];
		tong[a[i]] = i;//读入并可以O(1)判断
	}
	for(int i = 1;i <= m;i ++)cin>>b[i];
	for(int i = 1;i <= m;i ++)
	{
		if(! tong[b[i]])continue;
		int cnt = ex(tong[b[i]] - 1, i - 1) + 1;//得出答案
		if(cnt == 0)continue;
		cnt %= mod;
		if(cnt == 0)cnt += mod;//注意如果能整除要加回去mod
		ti ++;
		l.push_back(cnt);//加进去
	}
	sort(l.begin(), l.end());
	int rev = mod - ti;
	while(k >= mod)//取模统计答案
	{
		ans += k - k % mod;
		k -= k / mod * rev;
	}
	cout<<ans + solve(k)<<endl;//输出
	return 0;
}
```


---

## 作者：白鲟 (赞：0)

以 $\operatorname{lcm}(n,m)$ 长度作为循环节，注意到同一个循环节内，对于任意 $a_i$，至多一次与同其相等的 $b_j$ 处在同一位置。该位置可以通过以下同余方程组采用 $\operatorname{exgcd}$ 解出（注意到对于所有的方程组，只需要进行一次 $\operatorname{exgcd}$）：

$$
\begin{cases}
t\equiv i\pmod n\\
t\equiv j\pmod m
\end{cases}
$$

变形为 $nx+my=j-i$ 即为常见形式，所求答案即 $i+nx$ 调正后的值。

预处理出一个循环节中所有出现相等的位置，二分答案即可；不使用二分答案，直接定位到某个循环节再精确定位也是容易的。时间复杂度为 $\operatorname{O}(n\log n)$，瓶颈在排序。
```cpp
#include <algorithm>
#include <cstdio>
const int maxn = 5e5;
using ll = long long;
int n, m, d, common_cnt, solution_cnt, a[maxn + 1], b[maxn + 1], common[maxn + 1], 
    visa[maxn << 1 | 1], visb[maxn << 1 | 1];
ll k, x, y, lcm, ans, l, r, solution[maxn + 1];
void exgcd(int a, int b, ll &x, ll &y, int &d) {
    if (!b) {
        x = 1;
        y = 0;
        d = a;
        return;
    }
    exgcd(b, a%b, x, y, d);
    ll t = x;
    x = y;
    y = t - a / b * y;
    return;
}
bool check(ll mid) {
    return (mid - 1) / lcm * (lcm - solution_cnt) + 
           (mid - 1) % lcm + 1 - 
           (std::upper_bound(solution + 1, solution + solution_cnt + 1, (mid - 1) % lcm + 1) - solution - 1)
           >= k;
}
int main() {
    scanf("%d%d%lld", &n, &m, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        visa[a[i]] = i + 1;
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d", &b[i]);
        visb[b[i]] = i + 1;
        if (visa[b[i]]) {
            common[++common_cnt] = b[i];
        }
    }
    exgcd(n, m, x, y, d);
    lcm = (ll) n * m / d;
    for (int i = 1; i <= common_cnt; ++i) {
        if ((visa[common[i]] - visb[common[i]]) % d == 0) {
            solution[++solution_cnt] = n * x * (visb[common[i]] - visa[common[i]]) / d + visa[common[i]];
            solution[solution_cnt] = (solution[solution_cnt] % lcm + lcm - 1) % lcm + 1;
        }
    }
    std::sort(solution + 1, solution + solution_cnt + 1);
    l = 1;
    r = 1e18;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
``

---

## 作者：enucai (赞：0)

## Preface

莫名卡到了除了一个 Unshow 以外的最优解，复杂度 $O(n\log n+\log k \log n)$，$k$ 为二分上界。（~~所以有题解说 $O(n)$ 的咋还没我快？~~

## Analysis

我们要计算出一个周期（即 $\operatorname{lcm}(n,m)$）内的所有重复位置。由于题目告诉我们 $a$ 序列与 $b$ 序列中的元素互不相同，且值域很小。所以我们可以将 $a$ 序列中的数即位置用桶记录一下，再去枚举 $b$ 中的元素。

假如一个数在 $a$ 序列中出现的位置为 $i$，在 $b$ 序列中出现的位置为 $j$，那么她们在一个周期中重复的位置 $l$ 一定满足：

$$\begin{cases}l\equiv i\pmod n\\l\equiv j\pmod m\end{cases}$$

这用一次 excrt 就可以 $\log n$ 求出答案。

我们将所有这样的 $l$ 塞入一个 vector，进行排序。最后二分答案算出最小的 $q$。在固定 $q$ 计算时，先将完整的周期处理好，最后一个残缺的周期使用 upper_bound 即可 $O(\log n)$ 解决。

## Code

**Talk is cheap, show me the code.**

[Codeforces Status](https://codeforces.com/contest/1500/submission/150223644)

```cpp
// And in that light, I find deliverance.
#define int long long
int n,m,k,a[500010],b[500010],pos[1000010],qa[3],qb[3],Lcm,got;
vector<int> rep;
int exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	int gcd=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return gcd;
}
int excrt(){
	int lcm=1,ans=0;
	For(i,1,2){
		int x,y,gcd=exgcd(lcm,qb[i],x,y),tmp=(qa[i]-ans%qb[i]+qb[i])%qb[i];
		if(tmp%gcd!=0) return -1;
		x=x*tmp/gcd;x%=qb[i]/gcd;
		ans+=x*lcm;
		lcm*=qb[i]/gcd;
	}
	int res=(ans%lcm+lcm)%lcm;
	if(res==0) res=lcm;
	return res;
}
bool check(int q){
	int cnt=(q/Lcm)*got;
	q%=Lcm;
	cnt+=q-(upper_bound(rep.begin(),rep.end(),q)-rep.begin());
	return cnt>=k;
}
signed main(){
	read(n,m,k);
	For(i,1,n) read(a[i]);
	For(i,1,m) read(b[i]);
	For(i,1,n) pos[a[i]]=i;
	For(i,1,m) if(pos[b[i]]){
		int x=pos[b[i]],y=i;
		qa[1]=x,qb[1]=n;
		qa[2]=y,qb[2]=m;
		int crt=excrt();
		if(crt!=-1) rep.pb(crt);
	}
	sort(rep.begin(),rep.end());
	Lcm=n/__gcd(n,m)*m;
	got=Lcm-rep.size();
	int l=1,r=1e18,mid,best=1e18;
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid)) best=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<best<<endl;
}
```

---

