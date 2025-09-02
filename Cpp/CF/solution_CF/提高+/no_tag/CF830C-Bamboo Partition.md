# Bamboo Partition

## 题目描述

Vladimir wants to modernize partitions in his office. To make the office more comfortable he decided to remove a partition and plant several bamboos in a row. He thinks it would be nice if there are $ n $ bamboos in a row, and the $ i $ -th from the left is $ a_{i} $ meters high.

Vladimir has just planted $ n $ bamboos in a row, each of which has height $ 0 $ meters right now, but they grow $ 1 $ meter each day. In order to make the partition nice Vladimir can cut each bamboo once at any height (no greater that the height of the bamboo), and then the bamboo will stop growing.

Vladimir wants to check the bamboos each $ d $ days (i.e. $ d $ days after he planted, then after $ 2d $ days and so on), and cut the bamboos that reached the required height. Vladimir wants the total length of bamboo parts he will cut off to be no greater than $ k $ meters.

What is the maximum value $ d $ he can choose so that he can achieve what he wants without cutting off more than $ k $ meters of bamboo?

## 说明/提示

In the first example Vladimir can check bamboos each $ 3 $ days. Then he will cut the first and the second bamboos after $ 3 $ days, and the third bamboo after $ 6 $ days. The total length of cut parts is $ 2+0+1=3 $ meters.

## 样例 #1

### 输入

```
3 4
1 3 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 40
10 30 50
```

### 输出

```
32
```

# 题解

## 作者：meyi (赞：5)

前置知识：[数论分块](https://oi-wiki.org/math/number-theory/sqrt-decomposition/)

因为这题和 [ARC126C](https://atcoder.jp/contests/arc126/tasks/arc126_c) 要求的东西本质上是一样的，所以就写了一篇二合一的题解。

- [CF830C Bamboo Partition](http://codeforces.com/problemset/problem/830/C)

题意：

给定 $n$ 个数 $a_1 \sim a_n$，求最大的 $d$，满足 $\sum\limits_{i=1}^n d-(((a_i-1)\bmod d) +1)\le k$。

$n\le 100$，$a_i\le 10^9$，$k\le 10^{11}$。

思路：

令 $mx=\max\{a_i\},sum=\sum\limits_{i=1}^na_i$，先特判掉 $k>n\times mx-sum$的情况，这种情况下答案为 $mx+\lfloor\frac{k-(n\times mx-sum)}{n}\rfloor$。

考虑 $a\bmod b=a-\lfloor \frac{a}{b}\rfloor \times b$，于是可以把原式化为较为可做的形式：

$$\sum\limits_{i=1}^n d-(((a_i-1)\bmod d) +1)$$

$$=nd-\sum\limits_{i=1}^na_i-\lfloor \frac{a_i-1}{d}\rfloor \times d$$

代回原式，则有：

$$nd-sum+\sum\limits_{i=1}^n\lfloor \frac{a_i-1}{d}\rfloor \times d\le k$$

$$(n+\sum\limits_{i=1}^n\lfloor \frac{a_i-1}{d}\rfloor )\times d\le k+sum$$

$n,k$ 为常数，$sum$ 可以 $O(1)$ 求得，$\sum\limits_{i=1}^n\lfloor \frac{a_i-1}{d}\rfloor$ 可以 $O(n)$ 求得，需要考虑的只有 $d$ 的取值问题。

由数论分块相关知识不难知道，$\sum\limits_{i=1}^n\lfloor \frac{a_i-1}{d}\rfloor$ 最多有 $n\sqrt{mx}$ 取值，因此 $d$ 最多也只有 $n\sqrt{mx}$ 种取值（其实远远跑不满这个上界）可能会更新答案。根据我们上面推出来的式子，$d$ 在每一段上可能的最大值即为 $\lfloor \frac{k+sum}{n+\sum\limits_{i=1}^n\lfloor \frac{a_i-1}{d}\rfloor} \rfloor$。

时间复杂度 $O(n^2\sqrt{mx})$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int maxn=210;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
ll ans,k,sum;
int a[maxn],mx,n;
int main(){
	scanf("%d%lld",&n,&k);
	for(ri i=1;i<=n;++i){
		scanf("%d",a+i),ckmax(mx,a[i]);
		sum+=a[i];
	}
	if(k>=1ll*mx*n-sum)return printf("%lld",mx+(k-(1ll*mx*n-sum))/n),0;
	for(ri i=1;i<=mx;){
		ri nxt=0x3f3f3f3f;
		ll tmp=0;
		for(ri j=1;j<=n;++j)
			if(a[j]>i){
				ckmin(nxt,(a[j]-1)/((a[j]-1)/i));
				tmp+=(a[j]-1)/i;
			}
		if((n+tmp)*i<=k+sum)ckmax(ans,(k+sum)/(n+tmp));
		i=nxt+1;
	}
	printf("%lld",ans);
	return 0;
}
```

- [ARC126C Maximize GCD](https://atcoder.jp/contests/arc126/tasks/arc126_c)

题意：

给定 $n$ 个数 $a_1 \sim a_n$，你可以做以下操作最多 $k$ 次：

- 在 $[1,n]$ 中选择一个正整数 $i$，使 $a_i \leftarrow a_i+1$。

求操作结束后 $\gcd\limits_{i=1}^n a_i$ 的最大值。

$a_i,n\le 3\times 10^5$，$k\le 10^{18}$。

思路：

发现想让 $a_i$ 包含因子 $d$，需要做 $d-(((a_i-1)\bmod d)+1)$ 操作，于是问题转换为 求最大的 $d$，满足 $\sum\limits_{i=1}^n d-(((a_i-1)\bmod d) +1)\le k$。这和 [CF830C](http://codeforces.com/problemset/problem/830/C) 的式子是一样的。

直接套用上面的做法是 $O(n^2)$ 的（因为这里 $d$ 的取值最多有 $mx$ 种，而 $mx$ 与 $n$ 同阶），发现效率瓶颈在于求 $\sum\limits_{i=1}^n\lfloor \frac{a_i-1}{d}\rfloor$，令 $cnt_i$ 表示有多少 $j$ 满足 $a_j-1\le i$，那么 $\sum\limits_{i=1}^n\lfloor \frac{a_i-1}{d}\rfloor=\sum\limits_{k=1}^{\lfloor\frac{mx}{d}\rfloor}(cnt_{(k+1)\times d-1}-cnt_{k\times d-1})\times k$，这样做的复杂度是 $O(\lfloor\frac{n}{d}\rfloor)$。

利用调和级数可求出总时间复杂度为 $O(n \ln n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int maxn=3e5+10;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
ll k,sum;
int ans=1,a[maxn],cnt[maxn],mx,n;
int main(){
	scanf("%d%lld",&n,&k);
	for(ri i=1;i<=n;++i){
		scanf("%d",a+i),ckmax(mx,a[i]);
		++cnt[a[i]];
		sum+=a[i];
	}
	if(k>=1ll*mx*n-sum)return printf("%lld",mx+(k-(1ll*mx*n-sum))/n),0;
	for(ri i=1;i<=mx;++i)cnt[i]+=cnt[i-1];
	for(ri i=mx;i>1;--i){
		ll tmp=sum;
		for(ri j=i;j<=mx;j+=i)tmp-=1ll*(cnt[min(mx,j+i)]-cnt[j])*j;
		tmp=1ll*n*i-tmp;
		if(k>=tmp){
			ans=i;
			break;
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：gSE2xWE (赞：3)

[更好的阅读体验](https://www.cnblogs.com/loney-s/p/12939959.html)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF830C)


# 思路

先暴力推式子

$\sum_{i=1}^{n}d-((a_i-1)\%d+1))\le k$

看到$\%$，直接转换成除法

$\sum_{i=1}^{n}d-(a_i-d*\lfloor\frac{a_i-1}{d}\rfloor)\le k$

$\sum_{i=1}^{n}\lfloor\frac{a_i-1}{d}\rfloor\le \frac{k+\sum_{i=1}^na_i-n}{d}$

考虑左边的式子，

根据整除分块的相关知识

我们设$maxx=max(a_i)$

左边的式子最多有$\sqrt {maxx}*n$种取值

如果要变化

每一次移动d一定会使某一项的值$+1$

对于每一个，最多会有$\sqrt n$次

所以总共的取值就有$\sqrt {maxx}*n$种

之后我们对左边进行整除分块，用右边的式子检验$d$是否合法即可

# 代码

```cpp
#include<iostream>
using namespace std;
long long n,k;
long long a[105];
long long maxx;
long long ans;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		k+=a[i];
		maxx=max(maxx,a[i]);
	}
	for(long long l=1,r,s;l<=maxx;l=r+1)
	{
		s=0;
		r=(1ll<<60);
		for(int i=1;i<=n;i++)
			if(a[i]-1>=l)
				r=min(r,(a[i]-1)/((a[i]-1)/l));
		for(int i=1;i<=n;i++)
			s+=(a[i]-1)/r+1;
		long long t=k/s;
		if(l<=t&&t<=r)
			ans=max(ans,t);
		l=r+1;
	}
	if(k/n>maxx)
		ans=max(ans,k/n);
	cout<<ans;
	return 0;
}
```





---

## 作者：Leianha (赞：1)

## 分块

[博客阅读](https://www.cnblogs.com/wljss/p/12447023.html)

### 题目大意

给定 $n$ 个数 $a_1$ ~ $a_n$ ,求最大的 $d$ , 满足 $\displaystyle \sum_{i=1}^{n}d-((a_i-1)\%d + 1) \le k$

#

首先我们看到取模很难化简式子，考虑用除法代替。

$\displaystyle nd-\sum_{i=1}^{n}(a_i- \left \lfloor \frac{a_i-1}{d} \right \rfloor \times d) \le k$

$\displaystyle nd+\sum_{i=1}^{n} \left \lfloor \frac{a_i-1}{d} \right \rfloor \times d \le k + \sum_{i=1}^{n}a_i$

$\displaystyle d(n+\sum_{i=1}^{n} \left \lfloor \frac{a_i-1}{d} \right \rfloor )\le k + \sum_{i=1}^{n}a_i$

右边为定值，左边 $\displaystyle \left \lfloor \frac{a_i-1}{d} \right \rfloor$有根号种取值，我们枚举它来计算符合条件的最大的 $d$  即可。

```cpp
#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
LL n, k, mx, s, tmp, ans;
LL a[105];
int main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; ++i)scanf("%lld", &a[i]), k += a[i], mx = max(mx, a[i] - 1);
	for (LL l = 1, r; l <= mx; l = r + 1)
	{
		r = 1e18; s = 0;
		for (int i = 1; i <= n; ++i)
			if (a[i] - 1 >= l)
			{
				s += (a[i] - 1) / l;
				r = min(r, (a[i] - 1) / ((a[i] - 1) / l));
			}
		tmp = k / (s + n);
		if (l <= tmp)ans = max(ans, min(tmp, r));
	}
	if (mx < k / n)ans = max(ans, k / n);
	cout << ans;
	return 0;
}
```

---

## 作者：cmrhhh (赞：0)

# CF830C Bamboo Partition

## 题意翻译

求最大的 $d$ 满足 
$$
\sum_{i=1}^{n} d-((a_i-1)\bmod d+1)\le k
$$

# solution

$$
\sum_{i=1}^{n} d-(\left(a_i-1\right)\bmod d+1 )\le k\\
\sum_{i=1}^{n} d-\sum_{i=1}^{n}(a_i-1)\bmod d-n  \le k\\ 
n(d-1)-k \le \sum_{i=1}^{n}(a_i-1)\bmod d\\
n(d-1)-k \le \sum_{i=1}^{n}((a_i-1)-\left \lfloor \frac{a_i-1}{d} \right \rfloor\times d )\\
n(d-1)-k \le \sum_{i=1}^{n}(a_i-1)-\sum_{i=1}^{n}\left ( \left \lfloor \frac{a_i-1}{d} \right \rfloor\times d \right )  \\
n(d-1)+d\times \sum_{i=1}^{n}\left \lfloor \frac{a_i-1}{d} \right \rfloor\le \sum_{i=1}^{n}(a_i-1)+k\\
$$

那我们就有思路了，本来是枚举 $d$ ，挑个最大的，我们发现这和数论分块有关，右边是定值，当 $\sum_{i=1}^{n}\left \lfloor \frac{a_i-1}{d} \right \rfloor$ 一定时，左边关于 $d$ 递增，那么我们只需要处理 $\sum_{i=1}^{n}\left \lfloor \frac{a_i-1}{d} \right \rfloor$ 一样的块中最大的满足的 $d$ 就行。

记 $h = \sum_{i=1}^{n}\left \lfloor \frac{a_i-1}{d} \right \rfloor,c=\sum_{i=1}^{n}(a_i-1)+k$，那么 $n(d-1)+dh\le c \Leftrightarrow d\le \left\lfloor\frac{c+n}{n+h}\right\rfloor$

特别的，当 $h=0$ 时 $d$ 最大，此时 $d$ 要大于等于所有数。

### code :

```  cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long 
const ll N=110;
ll n,a[N],k=0,c=0,mx=0;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>k;c=k;
	for(int i=1;i<=n;++i)cin>>a[i],c+=a[i]-1,mx=max(mx,a[i]);
	int ans=0,l=1,r=0,h;
	for(l=1;l<=mx;l=r+1){ 
		r=mx;h=0;
		for(int i=1;i<=n;++i) {
			if((a[i]-1)/l) r=min(r,(a[i]-1)/((a[i]-1)/l));
			h+=(a[i]-1)/r;
		}
		int d=min(r,(c+n)/(n+h));
		if(l<=d) ans=max(d,ans);
	}
	if (mx<=c/n+1)ans = max((ll)ans,(ll)(c/n+1));
	cout<<(ll)ans;
	return 0;
}
```

---

## 作者：yqr123YQR (赞：0)

整除分块板。

### 分析
先 $a_i-1\to a_i$。

题面的式子带取模，考虑将取模 $x\bmod p$ 表示为 $x-p\lfloor\frac xp\rfloor$，原限制化为 $\sum\limits_{i=1}^n\left(d-1-a_i+d\lfloor\frac{a_i}d\rfloor\right)\leqslant k$，该式左式记作 $f(d)$。

想到整除分块，但是每次只能取最小的分界点。此时下取整部分固定，$f$ 在当前段 $[l,r]$ 上单增，可以二分。

时间复杂度 $\Omicron(n\sqrt V\log V)$。
[Submission](https://codeforces.com/contest/830/submission/305420165).

---

## 作者：hzx360 (赞：0)

先化简式子：

$$(a_i-1)\%d=(a_i-1)-\lfloor\frac{a_i-1}{d}\rfloor \times d$$

所以对整个式子化简后得到：

$$n\times d-\sum (a_i-1)+d\times \sum\lfloor\frac{a_i-1}{d}\rfloor-n \le k$$

变形：

$$n+\sum\lfloor\frac{a_i-1}{d}\rfloor \le \frac{n+k+\sum (a_i-1)}{d}$$

注意到只有 $d$ 一个变量，而且不等式右边 $d$ 作为分母，于是可以考虑整数分块。

通过一番细致的观察，又可以注意到对于一个块来说：不等式右边的值是不变的，而不等式左边 $d$ 作为分母，$d$ 越大左边的数值越小（越小就越容易满足条件）。

于是可以得出：对于一个块，只有这个块最大的 $d$ 是有用的，即这个块的右端点。

所以正常整数分块，每次取块的右端点算就行了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,a[1000];
signed main(){
	cin>>n>>k;
	int sum=0;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),a[i]=a[i]-1,sum+=a[i];
	sum+=n+k;
	int ans=0;
	for(int l=1,r;;l=r+1){
		if(l>sum) break;
		r=sum/(sum/l); r=min(r,sum);
		int now=sum/r,res=n;
		for(int i=1;i<=n;i++) res+=a[i]/r;
		if(res<=now) ans=r; 
	}
	cout<<ans;
}
```

---

## 作者：Register_int (赞：0)

首先推式子：
$$
\begin{aligned}
\sum^n_{i=1}d-((a_i-1)\bmod d+1)&\le k\\
dn-\sum^n_{i=1}((a_i-1)-d\lfloor\dfrac{a_i-1}d\rfloor+1)&\le k\\
dn-(\sum^n_{i=1}a_i-\sum^n_{i=1}d\lfloor\dfrac{a_i-1}d\rfloor)&\le k\\
d(n+\sum^n_{i=1}\lfloor\dfrac{a_i-1}d\rfloor)&\le k+\sum^n_{i=1}a_i\\
\end{aligned}
$$
枚举左半部分的所有可能的 $d$，满足条件时记录最大值即可。复杂度 $O(n\sqrt{k+\sum^n_{i=1}a_i})$。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e2 + 10;

ll a[MAXN], sum, k;

inline 
bool calc(ll n, ll d) {
	ll res = n;
	for (int i = 1; i <= n; i++) res += (a[i] - 1) / d;
	return res * d <= sum;
}

ll n, d;

int main() {
	scanf("%lld%lld", &n, &k), sum = k;
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), sum += a[i];
	for (ll i = 1; i <= sum / i; i++) {
		if (calc(n, i)) d = max(i, d);
		if (calc(n, sum / i)) d = max(sum / i, d);
	}
	printf("%lld", d);
}
```

---

