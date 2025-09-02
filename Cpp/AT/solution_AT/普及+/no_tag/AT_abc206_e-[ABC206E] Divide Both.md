# [ABC206E] Divide Both

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc206/tasks/abc206_e

整数 $ L,R\ (L\ \le\ R) $ が与えられるので、以下の条件を全て満たす整数組 $ (x,y) $ の数を求めてください。

- $ L\ \le\ x,y\ \le\ R $
- $ g $ を $ x,y $ の最大公約数とすると、以下が成立する。
  - $ g\ \neq\ 1 $ かつ $ \frac{x}{g}\ \neq\ 1 $ かつ $ \frac{y}{g}\ \neq\ 1 $

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ L\ \le\ R\ \le\ 10^6 $

### Sample Explanation 1

いくつかの整数組を例として示します。 - $ (x,y)=(4,6) $ は条件を満たします。 - $ (x,y)=(7,5) $ は $ g=1 $ となり、条件に違反します。 - $ (x,y)=(6,3) $ は $ \frac{y}{g}=1 $ となり、条件に違反します。 条件を満たすのは $ (x,y)=(4,6),(6,4) $ の $ 2 $ 組です。

## 样例 #1

### 输入

```
3 7```

### 输出

```
2```

## 样例 #2

### 输入

```
4 10```

### 输出

```
12```

## 样例 #3

### 输入

```
1 1000000```

### 输出

```
392047955148```

# 题解

## 作者：xiaoPanda (赞：8)

## ABC206E - Divide Both(*1745）
### Problem
给出 $L,R$，问满足下列要求的数对 $(x,y)$ 有几个？

+ $L\le x,y\le R$
+ $\gcd(x,y)\not=1$
+ $x$ 不是 $y$ 的倍数并且 $y$ 不是 $x$ 的倍数

### Solution
考虑条件 $2$，不妨设 $f(w)$ 表示使得 $\gcd(x,y)=w$ 的数对个数，很明显答案即为 $\sum_{i=2}^R f(i)$，注意到 $f(w)$ 仍不好求，再设 $g(w)$ 表示使得 $\gcd(x,y)\bmod w=0$ 的数对个数，则有 $f(w)=g(w)-\sum_{i=2}^{\lfloor \frac R w\rfloor}f(iw)$，从大到小枚举计算 $f(i)$ 即可。

求 $g(w)$ 就更简单，注意到 $\forall i\in[\lceil \frac {L} w\rceil,\lfloor \frac R w\rfloor],j\in[\lceil \frac {L} w\rceil,\lfloor \frac R w\rfloor]$ 都有 $\gcd(iw,jw)\bmod w=0$ 并且 $L\le iw,jw\le R$，那么在这之中任意选两个（可重复）的答案即 $g(w)=(\lfloor \frac R w\rfloor-\lceil \frac {L-1} w\rceil)^2$，注意这里是 $L-1$，就像前缀和一样，不是 $L$。

考虑条件 $3$，先看如果 $x$ 是 $y$ 的倍数或 $y$ 是 $x$ 的倍数的个数，暴力枚举 $x$，则 $y$ 可以取 $x,2x,3x,...,\lfloor \frac R x\rfloor x$ 共 $\lfloor \frac R x\rfloor$  个数，注意到 $(x,y)$ 和 $(y,x)$ 算两种，但 $(x,x)$ 只算一种，所以满足条件的个数为 $\sum_{i=L}^R (\lfloor \frac R i\rfloor\times 2-1)$。

注意到如果 $x$ 是 $y$ 的倍数或 $y$ 是 $x$ 的倍数，那么 $\gcd(x,y)\not=1$ （ $x=1$ 是特例，要特判），所以直接拿之前的答案减去上面的式子即可，不会有多余的，综上所述，答案为 

$$\sum_{i=2}^R f(i)-\sum_{i=L}^R (\lfloor \frac R i\rfloor\times2-1)$$

再强调一遍，一定要特判一下 $x=1$。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+7;
int f[N];
main() 
{
    int l,r,ans=0;
    scanf("%lld%lld",&l,&r);
    for(int i=r;i>=2;i--) 
	{
        int w=r/i-ceil((l-1)/i);
        f[i]=w*w;
        for(int j=i*2;j<=r;j+=i)
            f[i]-=f[j];
        ans+=f[i];
    }
    for(int i=l;i<=r;++i) 
	{
        if(i==1)continue;
        ans-=r/i*2-1;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Register_int (赞：6)

首先去掉互质对。这个直接钦定 $\gcd(i,j)$ 为 $k$ 的倍数，$f(k)$ 为 $[l,r]$ 中 $\gcd(i,j)=k$ 的数的对数，则要扣掉 $\gcd(i,j)\not=k$ 的情况，有：

$$
\begin{aligned}
f(k)=\left(\left\lfloor\dfrac rk\right\rfloor-\left\lfloor\dfrac{l-1}k\right\rfloor\right)^2-\sum^{\left\lfloor\frac rk\right\rfloor}_{i=2}f(ik)
\end{aligned}
$$

接着减去互为倍数的情况：

$$
\begin{aligned}
\sum^r_{k=\max(l,2)}2\left\lfloor\dfrac rk\right\rfloor-1
\end{aligned}
$$

做完了。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;

int l, r;

ll f[MAXN], ans;

int main() {
	scanf("%d%d", &l, &r);
	for (int i = r; i > 1; i--) {
		f[i] = r / i - (l - 1) / i;
		if (i >= l) ans -= r / i * 2 - 1; f[i] *= f[i];
		for (int j = i << 1; j <= r; j += i) f[i] -= f[j]; ans += f[i];
	}
	printf("%lld", ans);
}
```

---

## 作者：sunzz3183 (赞：5)

# [ABC206E] Divide Both 题解

## 题意

给定 $l,r$，求：

设 $g=\gcd(i,j)$

$$ \sum_{i=l}^r \sum_{j=l}^r [g\ne 1][i\ne g][j\ne g] $$

## 分析

分两部分求，一部分是 $g\ne 1$，另一部分是 $g\ne i$ 和  $g\ne j$。

我们这里默认 $l=\max(2,l)$。

得式子

$$ \sum_{i=l}^r \sum_{j=l}^r [\gcd(i,j)\ne 1]-2\sum_{i=l}^r \sum_{j=l}^i [j|i]+(r-l+1) $$

即

$$ \sum_{k=2}^r \sum_{i=l}^r \sum_{j=l}^r[\gcd(i,j)=k]-\sum_{k=l}^r(2(\left \lfloor \frac{r}{k}  \right \rfloor -\left \lfloor \frac{l-1}{k}  \right \rfloor )-1)$$

对于前面的，记 $l^{\prime}=\left \lfloor \frac{l-1}{k}  \right \rfloor ,r^{\prime}=\left \lfloor \frac{r}{k}  \right \rfloor $

$$
\begin{aligned}
\text { 原式 } & =\sum_{k=2}^{r} \sum_{i=l^{\prime}+1}^{r^{\prime}} \sum_{j=l^{\prime}+1}^{r^{\prime}}[\operatorname{gcd}(i, j)=1] \\
& =\sum_{k=2}^{r} \sum_{i=l^{\prime}+1}^{r^{\prime}} \sum_{j=l^{\prime}+1}^{r^{\prime}} \sum_{d|i, d|j} \mu(d) \\
& =\sum_{k=2}^{r} \sum_{d=1}^{r^{\prime}} \mu(d)\left(\left\lfloor\frac{r^{\prime}}{d}\right\rfloor-\left\lfloor\frac{l^{\prime}}{d}\right\rfloor\right)^2
\end{aligned}
$$

改为枚举 $T=kd$

$$
\begin{aligned}
\text { 原式 } & =\sum_{T=2}^{r}\left(\sum_{d \neq T, d \mid T} \mu(d)\right)\left(\left\lfloor\frac{r}{T}\right\rfloor-\left\lfloor\frac{l-1}{T}\right\rfloor\right)^2 \\
& =\sum_{T=2}^{r}-\mu(T)\left(\left\lfloor\frac{r}{T}\right\rfloor-\left\lfloor\frac{l-1}{T}\right\rfloor\right)^2
\end{aligned}
$$

所以总式子为

$$ \sum_{T=2}^{r}(-\mu(T)\left(\left\lfloor\frac{r}{T}\right\rfloor-\left\lfloor\frac{l-1}{T}\right\rfloor\right)^2-[T\geq l](2(\left \lfloor \frac{r}{T}  \right \rfloor -\left \lfloor \frac{l-1}{T}  \right \rfloor )+1)) $$

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    char ch=getchar();int x=0;bool f=1;
    while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return f?x:-x;
}
const int N=1e6+2,M=8e5;
int cnt,prime[M],mu[N];
bool is_p[N];
void init(int n){
    mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!is_p[i])prime[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            is_p[i*prime[j]]=1;
            if(!(i%prime[j]))break;
            mu[i*prime[j]]=-mu[i];
        }
    }
}
int l,r,ans;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    l=read();r=read();
    init(r);
    for(int i=2;i<=r;i++){
        int t=r/i-(l-1)/i;
        ans-=t*t*mu[i]+(i>=l?(t<<1)-1,0);
    }
    printf("%lld\n",ans);
    return 0;
}
```
## 结尾

感谢 `@icyM3tra` 大佬提供的帮助。

另外他还提到了另外一种方法：

$$ \because \sum_{k=1}^r \sum_{i=l}^r \sum_{j=l}^r [\gcd(i,j)=k]=(r-l+1)^2 $$

$$ 
\begin{aligned}
\therefore &\sum_{k=2}^r \sum_{i=l}^r \sum_{j=l}^r[\gcd(i,j)=k]\\
&=(r-l+1)^2-\sum_{i=l}^r \sum_{j=l}^r[\gcd(i,j)=1]
\end{aligned}
$$

---

## 作者：luuia (赞：3)

来一发莫反的题解。

### Solution

题目要求如下的式子：

$$\sum_{i=l}^r\sum_{j=l}^r[\gcd(i,j) \ne 1][i \nmid j][j\nmid i]$$

首先有一步很显然的容斥，记 

$$f(n,m)=\sum_{i=1}^n\sum_{j=1}^m[\gcd(i,j) \ne 1][i \nmid j][j\nmid i]$$ 

上式的答案为 $f(r,r) - f(l-1,r) - f(r,l - 1) + f(l - 1,l - 1)$，因此我们只需要求出 $f$ 即可。

直接求不好求，我们考虑它的反面：$(i,j)$ 互质或互为倍数。这两种情况只会在 $i=1$ 或 $j=1$ 时同时出现，因此我们枚举倍数时直接从 $2$ 开始枚举即可。

- $\gcd(i,j) = 1$

经典的莫反。

$$
\begin{aligned}

&\,\,\,\,\,\,\,\sum_{i = 1}^n\sum_{j = 1}^m \,\,[\gcd(i,j) = 1] \\

&= \sum_{i = 1}^n\sum_{j = 1}^m\sum_{d \mid \gcd(i,j)}\mu(d) \\ 

&= \sum_{i = 1}^n\sum_{j = 1}^m\sum_{d=1}^{\min(n,m)}\mu(d)[d \mid i][d \mid j] \\ 

&= \sum_{d=1}^{\min(n,m)}\mu(d)\sum_{i = 1}^n\sum_{j = 1}^m[d \mid i][d \mid j] \\

&= \sum_{d=1}^{\min(n,m)}\mu(d)\lfloor\frac{n}{d}\rfloor\lfloor\frac{m}{d}\rfloor \\

\end{aligned}
$$

现在这个式子的计算是 $O(n)$ 的，只需要线性筛出 $\mu$ 然后直接计算即可。

复杂度更优的解法是对 $\lfloor\frac{n}{d}\rfloor\lfloor\frac{m}{d}\rfloor$ 进行整除分块，然后对 $\mu$ 杜教筛即可做到 $O(n^{\frac{2}{3}})$。

- $(i,j)$ 互为倍数

不妨设 $n < m$，枚举每一个数得到式子：$\sum_{i=2}^n \lfloor \frac{m}{i} \rfloor$，这求出了上半部分，加上 $\sum_{i=2}^n \lfloor \frac{n}{i} \rfloor$，再减去两个部分重复的 $n-1$ 个数得到答案，数论分块计算。

于是这题就做完了，预处理复杂度 $O(n^{\frac{2}{3}})$，单次询问 $O(\sqrt n)$。

### Code

截至发文时是最优解。


```cpp
#include<bits/stdc++.h>
using namespace std;

long long read()
{
    long long s = 0,w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        s = (s << 1) + (s << 3) + (ch ^ 48);
        ch = getchar();
    }
    return s * w;
}

const int N = 10010;
long long l,r,ans,sum[N];
int T,n,tot,prime[N],mu[N];
bool vis[N];
map<int,int> m;

long long Mu(long long x) 
{
    if(x < N) return sum[x];
    if(m[x]) return m[x]; 
    int ret = 1;
    for(int i = 2,j;i <= x;i = j + 1) 
    {
        j = x / (x / i);
        ret -= Mu(x / i) * (j - i + 1);
    }
    m[x] = ret;
    return ret;
}

void euler()
{
    mu[1] = 1;
    for(int i = 2;i < N;i++) 
    {
        if(!vis[i]) {prime[++tot] = i;mu[i] = -1;}
        for(int j = 1;j <= tot && i * prime[j] < N;j++) 
        {
            vis[i * prime[j]] = true;
            if(i % prime[j]) mu[i * prime[j]] = -mu[i];
            else{mu[i * prime[j]] = 0;break;}
        }
    }
    for(int i = 1;i < N;i++) sum[i] = sum[i - 1] + mu[i];
}

long long cal(int x,int y)
{
    if(x == 0 || y == 0) return 0;
    long long res = 0;
    int n = min(x,y),m = max(x,y);
    for(int l = 2,r;l <= n;l = r + 1)
    {
        r = min(n,m / (m / l));
        res += (r - l + 1) * (m / l);
    }
    int tmp = 0;
    for(int l = 2,r;l <= n;l = r + 1)
    {
        r = n / (n / l);
        tmp += (r - l + 1) * (n / l);
    }
    res += tmp - n + 1; 
    for(int l = 1,r;l <= n;l = r + 1)
    {
        r = min(n / (n / l),m / (m / l));
        res += (Mu(r) - Mu(l - 1)) * (n / l) * (m / l);
    }
    return res;
}

int main()
{
    // freopen("input.in","r",stdin);
    l = read(),r = read(),euler();
    ans = cal(r,r) - cal(l - 1,r) * 2 + cal(l - 1,l - 1);
    ans = (r - l + 1) * (r - l + 1) - ans;
    cout << ans << endl;
    return 0;
}
```

---

## 作者：do_it_tomorrow (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/abc206e-divide-both-de-ti-jie/)
## 题目大意
求出从 $l$ 至 $r$ 中满足以下条件的 $(x,y)$ 的个数。

- $\gcd(x,y) \ne 1$ 且 $\gcd(x,y)\ne x$ 且 $\gcd(x,y)\ne y$。

其中 $1\le l\le r\le 10^6$。
## 思路
正难则反，所以可以求出所有互质或者是相互倍数的 $(x,y)$ 的对数，在将其减去所有的方案数就是答案。

设 $s_i$ 表示满足 $\gcd(a,b)=i$ 而且 $l\le a,b\le r$ 的数对 $(a,b)$ 的个数。

因为 $\gcd(a,b)=i$，所有有 $a,b\ge i$，而且有 $i \mid a,i \mid b$。

假设满足 $x\in[l,r]$ 且 $i \mid x$ 的数量为 $num$，那么以 $i$ 为**公因数**的个数就是 $num\times (num-1)$。

在以上的计算中 $j\ge i$，且两数满足 $i \mid a,i \mid b$，$j \mid a,j \mid b$ 的情况在计算 $s_i$ 和 $s_j$ 的时候都会计算，所以求出的公因数而不是最小公因数。为了求出 $i$ 为**最大**公因数时数对的个数，$s_i$ 的计算方法应该向下面这样。

$$S_i=(\lfloor r/i\rfloor-\lceil l/i \rceil)\cdot (\lfloor r/i\rfloor-\lceil l/i \rceil-1)-\sum^{\lfloor r/i\rfloor}_{j=\lceil l/i \rceil}S_{j\times i}$$

其中 $s_1$ 表示 $(x,y)$ 的 $\gcd(x,y)=1$ 的数量，即 $x,y$ 互质的数量。

对于是倍数的情况，枚举每一个数 $i$，求出 $j\in[l,r]$ 且 $i \mid j$ 的所有的可能的 $j$ 的数量，将答案减去就可以了。

因为如果 $x \mid y$，那么在 $x\ne 1,y\ne 1$ 的情况下，$\gcd(x,y)=x$ 就不会与互质的情况重复计算。

时间复杂度为：
$$O(\frac{r}{1}+\frac{r}{2}+\frac{r}{3}+\cdots +\frac{r}{r-2}+\frac{r}{r-1}+\frac{r}{r})=O(r \log r)$$

## AC Code
```c++
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e6+6;
int l,r,ans,s[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>l>>r;
	for(int i=r;i>=1;i--){
		int cnt=0,sum=0;
		for(int j=i;j<=r;j+=i){
			sum+=s[j];
			if(j>=l){
				cnt++;
			}
		}
		s[i]=cnt*(cnt-1)/2-sum;
	}
	int cnt=0;
	for(int i=max(l,2ll);i<=r;i++){
		for(int j=2*i;j<=r;j+=i){
			cnt++;
		}
	}
	int n=r-l+1;
	int ans=n*(n-1)/2;
	cout<<(ans-(cnt+s[1]))*2;
	return 0;
}
```

---

## 作者：Autream (赞：0)

#### 题意简述

给定整数 $L,R$，求满足以下条件的数对 $(x,y)$ 的数量。
- $x,y$ 不互质
- $x \nmid y$ 且 $y \nmid x$

---

#### 题目分析
正难则反，考虑用所有的满足第一条性质的数对的数量减去不满足第二条性质的数量。

容易想到，如果不考虑第二条性质，那么我们可以枚举因子 $i \in [2,r]$，求解出 $[l,r]$ 区间内的 $i$ 的倍数的个数 $s$，然后用加法原理，两两配对，累加到答案中。

如何求解 $s$？

不妨设 $x=k \times i+b$，则 $i \mid (x-b)$，即对于每个 $j \in [1,k]$ 都有 $i \mid (x-b-j \times i)$，一共 $k$ 个数，而这个 $k$ 就是 $\lfloor\frac{r}{i}\rfloor$，对于 $k$ 个数字两两配对，即可求解出 $s=\frac{k \times (k-1)}{2}$。但是这样会有重复，如：当 $i=2,3,6$ 时，均会有数对 $(6,12)$，这个时候就需要我们标记了。可以设 $cnt_i$ 表示 $i$ 的质因子的个数，如果 $cnt_i$ 为偶数，就减去当前贡献，否则加上。那么我们对于 $i=2,3$ 的时候加上了$(6,12)$ 的贡献，在 $i=6$ 的时候就会减去一个，这样就保证了贡献不会重复（不清楚的可以手模）。

最后减去不满足第二条限制的贡献：对于每个因子 $i \in [2,r]$，减去 $[l,r]$ 中除 $i$ 外 $i$ 的倍数，即：$\lfloor\frac{r}{i}\rfloor -1$。

---
#### AC Code

```cpp
#include<bits/stdc++.h>
#define arrout(a,n) rep(i,1,n)std::cout<<a[i]<<" "
#define arrin(a,n) rep(i,1,n)std::cin>>a[i]
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define dep(i,x,n) for(int i=x;i>=n;i--)
#define erg(i,x) for(int i=head[x];i;i=e[i].nex)
#define dbg(x) std::cout<<#x<<":"<<x<<" "
#define mem(a,x) memset(a,x,sizeof a)
#define all(x) x.begin(),x.end()
#define arrall(a,n) a+1,a+1+n
#define PII std::pair<int,int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
CI N=1e6+5;
int l,r,ans,cnt[N];
void init() {
    rep(i,2,r) {
        if(cnt[i]!=0) {
            continue;
        }
        for(int j=i;j<=r;j+=i) {
            if(cnt[j]>=0) {
                cnt[j]++;
            }
        }
        for(int j=i*i;j<=r;j+=i*i) {
            cnt[j]=-1;
        }
    }
}
signed main() {
    std::cin>>l>>r;
    init();
    rep(i,2,r) {
        if(cnt[i]<0) {
            continue;
        }
        int s=r/i-(l-1)/i;
        s=s*(s-1)/2;
        if(cnt[i]%2) {
            ans+=s;
        } else {
            ans-=s;
        }

    }
    rep(i,std::max(l,2ll),r) {
        ans-=r/i-1;
    }
    std::cout<<ans*2;
    return 0;
}
```

---

## 作者：xzy090626 (赞：0)

我们不妨先根据 $x,y$ 的大小来做：
- $x>y$ 时，实际上题目条件可以转化为 $x,y > \gcd(x,y) > 1$。结合 $x>y$ 可知，当 $y$ 不是 $x$ 的因数但是与 $x$ 不互质时，条件成立。

- $x=y$ 时，显然不可能满足条件；

- $x<y$ 时，容易知道和 $x>y$ 的答案相同。

于是，我们只需要做 $x>y$ 的这部分即可。

考虑容斥，因为 $y\mid x$ 与 $x\perp y$ 是互斥的，所以我们可以分别计算。于是我们的目标转化为了计算 $[l,x)$ 区间内 $x$ 的因数个数以及与 $x$ 互质的个数。

通过这个转化我们可以写出一个暴力。
```cpp
void solve(){
	int l,r;
	cin>>l>>r;
	for(int x=l;x<=r;++x){
		for(int j=l;j<x;++j){
			if(x%j && __gcd(x,j)>1) ans++;
		}
	}
	cout<<ans*2;
}
```
当然，这样的话复杂度是 $O((r-l)^2)$，需要一些优化。

显然，前者很容易根号枚举判断，后者可以通过容斥来求，具体参考[这个](https://zhuanlan.zhihu.com/p/564419414)（不过这个里面的代码需要优化一下），简要地说就是分解质因数（这篇文章里是 $O(\sqrt n)$ 分解的，但是我们可以通过线性筛之后用质数来分解，可以做到 $O({\sqrt n \over \log n})$ 的复杂度)，然后 dfs 枚举所有的因数，这样的复杂度也是 $O(\sqrt n)$ 的。

然后我们稍（nu）微（li）卡一卡常，就能以 $O((r-l)\sqrt r)$ 的复杂度通过这题啦。

代码太丑了不放了，可以找我私信要。

---

