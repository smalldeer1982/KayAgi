# Four Divisors

## 题目描述

If an integer $ a $ is divisible by another integer $ b $ , then $ b $ is called the divisor of $ a $ .

For example: $ 12 $ has positive $ 6 $ divisors. They are $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 6 $ and $ 12 $ .

Let’s define a function $ D(n) $ — number of integers between $ 1 $ and $ n $ (inclusive) which has exactly four positive divisors.

Between $ 1 $ and $ 10 $ only the integers $ 6 $ , $ 8 $ and $ 10 $ has exactly four positive divisors. So, $ D(10)=3 $ .

You are given an integer $ n $ . You have to calculate $ D(n) $ .

## 样例 #1

### 输入

```
10
```

### 输出

```
3
```

## 样例 #2

### 输入

```
20
```

### 输出

```
5
```

# 题解

## 作者：EnofTaiPeople (赞：10)

拿到字符串附赠的数论我十分 hahu。

注释（不看可能影响阅读）：

1. $prime$，质数集合；$p_k$，表示第 $k$ 个质数，$p_1=2$，默认 $p_0=1$；
2. $d(n)=\sum\limits_{x=1}^n[x|n]$，即 $n$ 的约数个数；
3. $\pi(n)=\sum\limits_{x=1}^n[x\in prime]$，即 $n$ 以内质数个数；
4. $minp(n)=\min\limits_{x>1\land x|n}x$，即 $n$ 的最小质因数，注意定义域不含 $1$；
5. $f(n,k)=\sum\limits_{x=2}^n[x\in prime\lor minp(x)>p_k]$，即 $n$ 以内质数以及最小质因数大于第 $k$ 个质数的数字个数。
6. 为了避免歧义，称询问的 $n$ 为大写 $N$。

题意要求 $\sum\limits_{x=1}^N[d(x)=4]$，$N\le10^{11}$。

对质因数分解分类讨论可以得到 $d(x)=4$ 的充要条件是 $x=p^3\lor x=pq$，其中 $p,q\in prime,p<q$。

对于 $x=p^3$，其答案为 $\pi(\lfloor\sqrt[3]N\rfloor)$，暴算即可；

对于 $x=pq$，考虑枚举 $\sqrt N$ 以内所有质数 $p$，求合法 $q$ 的个数，即 $\sum\limits_{p_k^2<N}(\pi(\lfloor\dfrac N{p_k}\rfloor)-k)$，之所以要减去 $k$ 是因为 $p<q$，$q$ 是第 $k$ 个之后。

通过整除分块的思想，$\lfloor\dfrac N x\rfloor$ 只会有 $O(\sqrt N)$ 种取值，我们可以将所有的 $\pi(\lfloor\dfrac N x\rfloor)$ 都求出来。

具体地，我们需要利用注释 $6$ 中的 $f(n,k)$ 函数，不难发现 $f(n,0)=n-1$，我们需要进行递推。

考虑 $f(n,k-1)$ 与 $f(n,k)$ 的差，它们的差在于 $f(n,k)$ 去掉了 $minp(x)=p_k$ 的合数 $x$，这样的 $x$ 个数为 $f(\lfloor\dfrac n{p_k}\rfloor,k-1)-(k-1)$。

怎么解释这一步？发现我们提出 $p_k$ 之后需要找的是 $\lfloor\dfrac n{p_k}\rfloor$ 以内最小质因数大于等于 $p_k$ 的数的个数，但 $f(\lfloor\dfrac n{p_k}\rfloor,k-1)$ 还包含了 $p_1$ 到 $p_{k-1}$ 这 $k-1$ 个质数，需要去掉，于是我们有了递推式：$f(n,k)=f(n,k-1)-f(\lfloor\dfrac n{p_k}\rfloor,k-1)+k-1$。

注意到我们只需要处理所有关于 $\lfloor\dfrac N x\rfloor$ 的 $f$ 函数，由于 $\lfloor\dfrac{\lfloor\dfrac N a\rfloor}b\rfloor=\lfloor\dfrac N{ab}\rfloor$，所以 $\dfrac n{p_k}$ 必定也在所求序列中，即 $f(\lfloor\dfrac n{p_k}\rfloor,k-1)$ 已经求出。

递推边界是 $f(n,\pi(\sqrt n))=\pi(n)$，因为所有合数都已经筛掉了，同理有 $f(n,\pi(\sqrt n)+k)=\pi(n),k\ge 0$。

于是我们只需要对于 $\sqrt N$ 以内的质数进行递推，递推时枚举 $\lfloor\dfrac N x\rfloor$，而 $\lfloor\dfrac N x\rfloor$ 是递减的，所以碰到小于 $p_k^2$ 的 `break` 掉就行了。

注意到 $\sqrt[3]N$ 一定能表示为 $\lfloor\dfrac N x\rfloor$，所以不需要单独暴算 $\pi(\sqrt[3]N)$ 了，答案就是 $\pi(\sqrt[3]N)+\sum\limits_{p_k^2<N}(\pi(\lfloor\dfrac N{p_k}\rfloor)-k)$。

复杂度及证法等价于 $\text{Min\_25}$ 筛的前半部分，即 $O(\dfrac{N^{0.75}}{\ln N})$：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+6;
ll n,b[N],m,S,pm[N],pt,f[N],ans;
ll gid(ll x){
	return x<=S?m-x+1:n/x;
    利用整除分块性质的 O(1) 求法，打哈希表也可以。
}
bitset<N>vs;
int main(){
#ifdef MYdef
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	ll i,l,r,x,y,md,rl;
	scanf("%lld",&n);
	l=1,r=1e5;
	while(l<=r){
		md=l+r>>1;
		if(md*md*md<=n)rl=md,l=md+1;
		else r=md-1;求三次根
	}S=sqrtl(n);
	for(l=1;l<=n;l=r+1)
		r=n/(n/l),b[++m]=n/l;整除分块
	for(x=2;x<=S;++x)
		if(!vs[x]){
			pm[++pt]=x;
			for(y=S/x;y>1;--y)
				vs[x*y]=1;筛质数
		}
	for(l=1;l<=m;++l)f[l]=b[l]-1;
	for(i=1;i<=pt;++i)
		for(x=1;pm[i]*pm[i]<=b[x]&&x<=m;++x){
			y=gid(b[x]/pm[i]);
			f[x]-=f[y]-(i-1);直接套上面推出的式子
		}
//	for(i=1;i<=m;++i)
//		printf("%d %d\n",b[i],f[i]);
	for(i=1;i<=pt;++i)
		ans+=f[gid(n/pm[i])]-i;直接套上面推出的式子
	ans+=f[gid(rl)];
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：duyi (赞：7)

# CF665F Four Divisors

发现一个数 $x$ 恰有 $4$ 个约数，当且仅当是如下两种情况之一：

- 存在两个质数 $p,q$ ($p < q$)，满足 $p\cdot q = x$。
- 存在一个质数 $p$，满足 $p^3 = x$。

第二种情况，只需要在 $\sqrt[3]{n}$ 范围内暴力枚举一下即可。

考虑第一种情况。它对答案的贡献是：
$$
\text{ans}_1 = \sum_{p = 1}^{n}\sum_{q = p + 1}^{n}[p \in \text{prime}]\cdot [q\in\text{prime}]\cdot [p\cdot q \leq n]
$$
要保证 $q > p$ 有些麻烦。不妨先不考虑顺序，即：
$$
\text{ans}_1 = \frac{1}{2}\left(\sum_{p = 1}^{n}\sum_{q = 1}^{n}[p \in \text{prime}]\cdot [q\in\text{prime}]\cdot [p\cdot q \leq n] - \sum_{p = 1}^{\lfloor\sqrt{n}\rfloor}[p \in \text{prime}]\right)
$$
后半部分：$\sum_{p = 1}^{\lfloor\sqrt{n}\rfloor}[p \in \text{prime}]$，即 $1\dots \lfloor\sqrt{n}\rfloor$ 内的质数个数，可以用线性筛求出。

考虑前半部分，记为 $\text{ans}_0$：
$$
\text{ans}_0 = \sum_{p = 1}^{n}\sum_{q = 1}^{n}[p \in \text{prime}]\cdot [q\in\text{prime}]\cdot [p\cdot q \leq n]
$$
设 $1\dots n$ 内的质数数量为 $f(n)$。则：
$$
\text{ans}_0 = \sum_{p = 1}^{n} [p\in\text{prime}] \cdot f(\lfloor\frac{n}{p}\rfloor)
$$
使用[min25 筛法](https://www.cnblogs.com/dysyn1314/p/13449083.html)的前半部分，可以对所有 $m\in\{\lfloor\frac{n}{1}\rfloor,\lfloor\frac{n}{2}\rfloor,...,\lfloor\frac{n}{n}\rfloor\}$，预处理出 $f(m)$。

然后做数论分块。枚举 $\lfloor\frac{n}{p}\rfloor$ 的值，它对应一段区间 $p\in[l,r]$。根据数论分块的写法，一定有 $r\in\{\lfloor\frac{n}{1}\rfloor,\lfloor\frac{n}{2}\rfloor,...,\lfloor\frac{n}{n}\rfloor\}$。于是我们就知道了这段区间里 $p$ 的数量（即 $f(r) - f(l - 1)$），同时又能知道 $f(\lfloor\frac{n}{p}\rfloor)$ 的值，乘一下，加到答案里即可。

时间复杂度瓶颈是 min25 筛法，复杂度 $\mathcal{O}(\frac{n^{\frac{3}{4}}}{\log n})$。

## 参考代码

```cpp
// problem: F
#include <bits/stdc++.h>
using namespace std;

#define mk make_pair
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef __int128 ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 316228; // sqrt(N)

int p[MAXN + 5], cnt_p;
bool v[MAXN + 5];
void sieve(int lim){
	for(int i=2;i<=lim;++i){
		if(!v[i]){
			p[++cnt_p]=i;
		}
		for(int j=1;j<=cnt_p && (ll)i*p[j]<=lim;++j){
			v[i*p[j]]=1;
			if(i%p[j]==0){
				break;
			}
		}
	}
}


struct Min25{
	ll n, sqrt_n;
	ll val[MAXN*2+5];
	int id1[MAXN+5],id2[MAXN+5],tot;
	ll g[MAXN*2+5];
	inline int get_id(ll w){
		if(w<=sqrt_n) return id1[w];
		else return id2[n/w];
	}
	void build(ll _n){
		n=_n;
		tot=0;
		sqrt_n = sqrt((double)n);
		for(ll i = 1, j; i <= n; i = j + 1) {
			j=n/(n/i);
			ll w = n / i;
			val[++tot]=w;
			if(w<=sqrt_n) id1[w]=tot;
			else id2[n/w]=tot;
			
			g[tot]=w-1;
		}
		for(int j=1;j<=cnt_p;++j){
			for(int i=1;i<=tot && (ll)p[j] * p[j] <= val[i];++i){
				int k=get_id(val[i]/p[j]);
				g[i]=g[i]-(g[k]-(j-1));
			}
		}
	}
	ll query(ll x) {
		return g[get_id(x)];
	}
	Min25(){}
} S;


int main() {
	sieve(MAXN);
	ll n;
	cin >> n;
	
	S.build(n);
	ll lst = 0;
	ll ans = 0;
	for (ll i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		ll s = S.query(j);
		ans += (s - lst) * S.query(n / i);
		lst = s;
	}
	
	for (ll i = 2; i * i <= n; ++i) {
		ans -= (!v[i]);
	}
	ans /= 2;
	for (ll i = 2; i * i * i <= n; ++i) {
		ans += (!v[i]);
	}
	cout << ans << endl;
	return 0;
}
```



---

## 作者：peterwuyihong (赞：4)

怎么又有人天天抓車啊。。。

题意：$n\le 10^{11}$，求

$$\sum_{i=1}^n[d(i)=4]$$

分两类讨论，一类是 $p^3$，一类是 $p_1p_2$。

于是你第一项直接做，第二项枚举 $\sqrt n$ 以下的质数，然后用 $\pi(\lfloor\dfrac n p\rfloor)$ 计算即可。

对 $\pi$ 的求解可以用[$\text{Meissel-Lehmer}$ 算法](https://www.luogu.com.cn/paste/41y6oksf)，或者用 $\text{min-25}$ 前体计算所有 $\lfloor\dfrac n i\rfloor$ 处的点值。

剩下简单处理一下即可，令 $p_1<p_2$ 就行了。

```cpp
signed main(){
  cin>>n;
  n_3=pow(n,1.0/3);
  n_2=sqrt(n);     
  shai(n_2);
  for(int i=1;i<=tot;i++)ans+=pi(n/pri[i])-pi(pri[i]);
  ans+=pi(n_3);
  cout<<ans;
}
```

可以思考一下[8个约数怎么做，都是一样的啊](https://www.luogu.com.cn/blog/Peterprpr/ou-la-ji-hua)。

---

## 作者：冷梦233 (赞：3)


###  既然没有人发过，那我就来~~水~~一发吧。
 
 首先看到题意：请找出1到n当中，恰有4个约数的数的个数。
 
 我心想这么水，直接打了个暴力：
 ```
#include<bits/stdc++.h>
using namespace std;
int n,sum;
int qzs(int x){
    int ans=0;
    for(int i=1;i<=n;i++)if(x%i==0)ans++;
    return ans;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        if(qzs(i)==4)sum++;
    }
    printf("%d",sum);
    return 0;
}
```
然后它，理所当然的tle了。
这个时候我就想到一种思路。

众所周知每一个整数都至少有2个约数：1和本身

而要满足仅有4个约数，则应该满足：

1.是某个质数的3次方 2.是2个质数的乘积。

举个例子：
6有4个约数（1，2，3，6），且6=2*3，是2个质数的乘积。

而8也有4个约数（1，2，4，8），且8=2^3,是1个质数的3次方。

在n以内且是某个质数的3次方得到的数，直接将n开立方得到x，求x以内的素数的个数即可。

而2个不同质数的乘积，枚举较小的质数a，得到b=n/a，对于不同的a，求出b以内的质数的个数，相加去重即可。

那么问题就转化成了数m以内的素数个数的问题。

所以我就套用了大质数模板（真是个小机灵鬼）（见hdu 5901）。

附上代码：
```
#include <bits/stdc++.h>
using namespace std;
#define ll __int64 //防炸
const int N=320010;   
ll n,p[10010][110], p2[N], ans[N];  
int len, v[N];  
void qzs(){  
    len = 0;  
    for(int i=2; i<N; i++){  
        if(!v[i]){  
            for(int j=i+i; j<N; j+=i) 
            v[j]=1;  
            p2[len++] = i;  
            ans[i] = ans[i-1]+1;  
            continue;  
        }  
        ans[i] = ans[i-1];  
    }     
    for(int i=0; i<=10000; i++){  
        p[i][0] = (ll)i;  
        for(int j=1; j<=100; j++){  
            p[i][j] = p[i][j-1] - p[i/p2[j-1]][j-1];  
        }  
    }  
}  
  
ll sp(ll m, ll n){  
    if(!n) return m;  
    if(p2[n - 1] >= m) return 1;  
    if(m<=10000 && n<=100) return p[m][n];  
    return sp(m, n-1) - sp(m/p2[n-1], n-1);  
}  
  
ll sp2(ll m){  
    if(m < (ll)N) return ans[m];  
    ll y = (int)cbrt(m*1.0);  
    ll n = ans[y];  
    ll sum = sp(m, n) + n -1;  
    for(ll i=n; p2[i]*p2[i]<=m; i++) 
        sum = sum-sp2(m/p2[i])+sp2(p2[i])-1;  
    return sum;  
}  
//以上为求大质数个数模板
int main(){
	qzs(); 
	scanf("%I64d", &n);
	ll ss = cbrt(n*1.0);//立方根函数
	ss = sp2(ss);
	ll tmp=0;
	for(int i=0; i<len; i++){
		if(p2[i]*p2[i]>=n)break;
		ll x = n/p2[i];
		ll s = sp2(x);
		s-=tmp+1;
		tmp = sp2(p2[i]);
		ss+=s;
	}
	printf("%I64d\n", ss);
	return 0;
}    
```
(注：参考了[这篇](https://blog.csdn.net/noone0/article/details/78149880))








---

## 作者：tder (赞：1)

定义 $\displaystyle\pi(n)=\sum_{i=1}^n~[i\in\mathbb{P}]$。求法是 Min25，参见 [1](https://www.cnblogs.com/dysyn1314/p/13449083.html) [2](https://www.luogu.com.cn/article/vo3q2nq7)。

追加定义区间 $\pi(l,r)=\pi(r)-\pi(l-1)$。

正整数 $x$ 恰有 $4$ 个因数，当且仅当：

- $x=p^3$，其中 $p\in\mathbb{P}$；
- $x=p\cdot q$，其中 $p,q\in\mathbb{P}$ 且 $p<q$。

对于前者，满足条件的 $x$ 的个数即为 $\text{ans}_1=\pi(\sqrt[3]{n})$。

对于后者，考虑每个 $p$，满足的个数为 $\pi(\lfloor\frac np\rfloor)$。但是这样将 $p\cdot q$ 和 $q\cdot p$ 的情况算两次，以及不符合要求的形如 $p\cdot p$。减去多算的后面一种情况的 $\pi(\sqrt n)$ 个，再根据组合意义将答案除上 $2$ 即可。也就是说：

$$
\text{ans}_2=\frac{\sum_{i\in\mathbb{P}}\pi(\lfloor\tfrac np\rfloor)-\pi(\sqrt n)}2
$$

答案是 $\text{ans}_1+\text{ans}_2$。

这样做是 $O(\pi(n))$ 的，不计 Min25 的预处理复杂度。

容易观察到其中有个很显眼的 $\lfloor\frac np\rfloor$，于是考虑数论分块。将 $[1,n]$ 拆为若干段 $[l_i,r_i]$，使得每段内的 $\lfloor\frac np\rfloor$ 均相同，于是这一段的贡献为 $\pi(l_i,r_i)\cdot\pi(\lfloor\tfrac np\rfloor)$。

可以证明分块个数为 $\sqrt n$，故时间复杂度 $O(\sqrt n)$。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e11 + 5, M = sqrt(N) + 5;
namespace Getpi {
	int n, b[M], d[M * 2], f[M], g[M], cnt, s, h[M * 2];
	vector<int> v;
	int& work(int x) {
		if(x <= s) return f[x];
		else return g[n / x];
	}
	void init() {
		s = sqrt(n);
		for(int i = 2; i <= s; i++) {
			if(!b[i]) v.push_back(i);
			for(int j = 0; j < v.size(); j++) {
				int p = v[j];
				if(p * i > s) break;
				b[p * i] = 1;
				if(!(i % p)) break;
			}
		}
		cnt = 0;
		for(int l = 1, r; l <= n; l = r + 1) {
			r = n / (n / l);
			d[work(n / l) = ++cnt] = n / l, h[cnt] = n / l - 1;
		}
		for(int i = 0; i < v.size(); i++) for(int j = 1; d[j] >= v[i] * v[i]; j++) h[j] -= h[work(d[j] / v[i])] - i;
	}
	int getpi(int x) {
		if(!x) return 0;
		return h[work(x)];
	}
	int getpi(int l, int r) {
		return getpi(r) - getpi(l - 1);
	}
};
int n, ans;
signed main() {
	cin>>n; Getpi::n = n; Getpi::init();
	int k = 0;
	for(int l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		// cout<<"l r = "<<l<<" "<<r<<endl;
		ans += Getpi::getpi(l, r) * Getpi::getpi(n / l);
		// cout<<ans<<endl;
	}
	ans -= Getpi::getpi(sqrt(n));
	ans /= 2;
	ans += Getpi::getpi(pow(n, 1.0 / 3));
	cout<<ans<<endl;
	return 0;
}
/*
2 2 = 4
2 3 = 6
2 5 = 10
3 2 = 6
3 3 = 9
5 2 = 10
*/
```

---

## 作者：Link_Cut_Y (赞：1)

### $k = 4$

一个数 $n$ 有四个因数，当且仅当其可以表示为 $n \in \{n\ |\  n = p ^ 3\} \bigcup \{n\ |\ n = pq\}$，$p, q$ 为两个不同质数。

考虑第一种情况，$n = p ^ 3$。求出 $\sqrt[3] n$ 以内的质数个数即可。该部分时间复杂度 $O(\sqrt[3] n)$。

考虑第二种情况。不放假设 $p < q$。则 $p \le \sqrt n$。枚举 $1 \le p \le \sqrt n$，$q$ 即为 $p + 1 \sim \left \lfloor \dfrac{n}{p} \right \rfloor$ 之内的质数。如果我们去掉下界会变得更容易一些。

容斥一下，如果去掉下界：

 - $q \le p$：计算了两遍，分别为 $p, q$ 和 $q, p$，需要减去一遍。
 
 - $q > p$：计算了一遍，对答案没有影响。

设 $\pi(n)$ 表示 $1 \sim n$ 中质数的个数，答案就是

$$\pi(\sqrt[3] n) + \sum_{p \le \sqrt n} \pi\left (\left \lfloor \dfrac{n}{p} \right \rfloor \right ) - \binom{\pi(\sqrt n)}{2}$$

可以使用 [$\texttt{Meissel–Lehmer}$ 算法](https://oi-wiki.org/math/number-theory/meissel-lehmer/) 进行求解。

另外一种方法是通过 dp。设 $p_k$：全体质数中第 $k$ 小的质数，$G(m) = \sum_{i \in P, i \le m} 1$，也就是 $\le m$ 的质数个数。

设 $g(j, m)$ 表示：


$$
\begin{aligned}
g(j, m) &= \sum_{1 \le i \le m} [i \in P \bigcup \text{lp}(i) > p_j] \times 1
\end{aligned}
$$

其中 $\text{lp}(n)$ 表示 $n$ 的最小质因子。

$g$ 就是求 $1 \sim m$ 中质数或者最小质因数大于 $p_j$ 的数的个数。

初始时，$g(0, m) = m - 1$，这是因为 $2 \sim m$ 中，所有合数的最小质因数都大于 $0$。

转移时分为以下两种情况：

 - 若 $p_j ^ 2 > m$：$g(j, m) = g(j - 1, m)$。因为不存在 $i \in [1, m]$，使得 $\text{lp}(i) > p_j$。
 
 - 若 $p_j ^ 2 \le m$：
 
 $$
 \begin{aligned}
 g(j, m) &= g(j - 1, m) - \left ( g(j - 1, \dfrac{m}{p_j}) - g(j - 1, p_{j - 1}) \right ) \\
 
 &= g(j - 1, m) - \left ( g(j - 1, \dfrac{m}{p_j}) - (j - 1) \right )
 \end{aligned}
 $$
 
很显然，上述式子中的第一维是可以滚掉的。$\pi(n) = G(n) = g(\pi(n), n)$。

根据所求以及转移式，我们只需要对于 $m \in A = \{x \ |\ x = \left \lfloor \dfrac{n}{i} \right \rfloor, i \in [1, n] \cap \mathbb{Z}\}$ 求值。而 $A$ 的大小是 $O(\sqrt n)$ 级别的。

以上部分时间复杂度被证明是 $O(\dfrac{n ^ {0.75}}{\ln n})$。这里不写证明过程了。

该 dp 即为 min_25 筛前体。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define int long long

using namespace std;

const int N = 500010;

int p[N], s[N], g[N], id1[N], id2[N];
int cnt, st[N], w[N], n, sq, m, ans;
int id(int x) { return x <= sq ? id1[x] : id2[n / x]; }
void init(int n) {
	for (int i = 2; i <= n; i ++ ) {
		if (!st[i]) p[ ++ cnt] = i;
		for (int j = 1; j <= cnt and p[j] * i <= n; j ++ ) {
			st[p[j] * i] = 1; if (i % p[j] == 0) break;
		}
	}
}
signed main() {
	scanf("%lld", &n); init(sq = sqrt(n));
	for (int l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l); w[ ++ m] = n / l; g[m] = w[m] - 1;
		if (w[m] <= sq) id1[w[m]] = m;
		else id2[n / w[m]] = m;
	}
	for (int i = 1; i <= cnt; i ++ )
		for (int j = 1; j <= m and p[i] * p[i] <= w[j]; j ++ )
			g[j] -= (g[id(w[j] / p[i])] - (i - 1));
	int lim = cbrt(n);
	for (int i = 1; i <= cnt and p[i] <= lim; i ++ ) ans ++ ;
	for (int i = 1; i <= cnt; i ++ ) ans += g[id(n / p[i])];
	ans -= cnt * (cnt - 1) / 2; ans -= cnt; cout << ans;
}
```

---

## 作者：HohleFeuerwerke (赞：1)

### 前言

CF665F - Four Divisors，[link](https://www.luogu.com.cn/problem/CF665F)。

### 正文

题目比较简单，我们做一个数学化的处理，题目要求的是：
$$\sum_{i=1}^n[d(i)=4]$$
这个式子长得非常的难受。我们考虑进行分类讨论。

如果这个 $i$ 对答案没有贡献，那么我们显然可以直接判断掉。所以我们只需要考虑对答案有贡献的这个 $i$。并且我们不需要确切的知道这个 $i$ 是几。我们只需要知道有多少这样的 $i$ 就行了。

一个数的因数个数为 $4$，当且仅当这个数可以表示为 $p^3$（$p$ 为素数）或者 $p\times q$（$p$ 和 $q$ 为素数）。

然后就是愉快的清新~~大力~~分类讨论过程。

先考虑 $i=p^3$（$p$ 为素数）。如果是这样，我们只需要统计一下 $1\sim\sqrt[3]{n}$ 里有多少素数即可。也就是说，我们需要求出的是：$\pi(\sqrt[3]{n})$。这个很简单，可以用欧拉筛，可以用 Meissel-Lehmer 解决。鉴于这个题的数据范围是 $n^{11}$，所以 $\sqrt[3]{n}$ 的范围不是很大，这个是可以用欧拉筛解决的。当然用 Meissel-Lehmer 解决更加快速。

然后考虑 $i=p\times q$（$p,q$ 为素数）。对于这种情况，可以考虑找到 $p∈\{1,2,3,...,\sqrt n\}$。当 $p$ 是确定的时候，$q$ 的取值有 $\pi(\frac{n}{p})-\pi(p)$ 种。

不同的是，这里 $\pi$ 传入的参数最大可能到 $\frac{n}{2}$。所以必须要用 Meissel-Lehmer。如果对 Meissel-Lehmer 有疑惑，可以移步 loj，hdu 或者洛谷上有一题叫“素数个数”。那里的第一篇题解就是 Meissel-Lehmer。

如果实在看不懂，那么用 Min_25 筛求 $\pi(n)$ 也是一个很好的选择。

代码就不放了，我的代码写的又臭又长……

---

