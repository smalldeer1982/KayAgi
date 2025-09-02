# [YDOI R1] Lattice

## 题目背景

se 喜欢点阵。

## 题目描述

se 有一个正方形点阵，这个点阵以 $(1,1)$ 为左下角，以 $(n,n)$ 为右上角。

se 还有一条直线，其表达式为 $y=kx$，其中 $k\in(0,\infty)$。

对于任意一个 $k$，设该直线经过了 $cnt$ 个点阵中的点，se 对这条直线有一个喜爱程度，为 $cnt^2$。

se 想知道所有直线的喜爱程度和对 $10^9+7$ 取模的结果，请你告诉 se。

## 说明/提示

### 样例解释 #1
当 $k$ 为 $\frac{1}{2}$ 时，直线过点阵中的点 $(2,1)$，喜爱程度为 $1^2=1$；当 $k$ 为 $1$ 时，直线过点阵中的点 $(1,1)$ 和点 $(2,2)$，喜爱程度为 $2^2=4$；当 $k$ 为 $2$ 时，直线过点阵中的点 $(1,2)$，喜爱程度为 $1^2=1$。喜爱程度和为 $1+4+1=6$。
### 数据范围
**本题采用捆绑测试**。
|子任务编号|$n\le$|分值|
|:--:|:--:|:--:|
|$1$|$8$|$5$|
|$2$|$10^3$|$15$|
|$3$|$10^6$|$30$|
|$4$|$2^{31}-1$|$50$|

对于 $100\%$ 的数据，$1\le n\le 2^{31}-1$。

## 样例 #1

### 输入

```
2```

### 输出

```
6```

## 样例 #2

### 输入

```
1919810```

### 输出

```
107114211```

# 题解

## 作者：Starstream (赞：7)

### 思路

#### 引理 1

在一个 $n\times n$ 的点阵中，如果直线经过的第 $1$ 个点为 $(x, y)$，则它经过的点数目为 $\lfloor \dfrac{n}{\max(x, y)} \rfloor$。

#### 证明

若直线经过的第一个点为 $(x, y)$，则第二个点为 $(2x, 2y)$。

以此类推，经过的最后一个点坐标为 $(kx, ky)(k\in \mathbb N^*)$。

$$1\le kx \le n,1\le ky \le n$$

解得：

$$1\le k \le \min(\lfloor\dfrac{n}{x}\rfloor,\lfloor\dfrac{n}{y}\rfloor)=\lfloor \dfrac{n}{\max(x, y)} \rfloor$$

$k$ 共有 $\lfloor \dfrac{n}{\max(x, y)} \rfloor$ 种取值，即共经过 $\lfloor \dfrac{n}{\max(x, y)} \rfloor$ 个点。

***

#### 引理 2

在一个 $n\times n$ 的点阵中，如果直线经过的第 $1$ 个点为 $(x, y)$，则 $\gcd(x, y)=1$。

#### 证明

假设直线经过的第 $1$ 个点为 $(x, y)$，且 $\gcd(x, y) \ne 1$。

则必定存在一个点 $\left(\dfrac{x}{\gcd(x, y)},\dfrac{y}{\gcd(x, y)}\right)$ 被直线经过。该点横纵坐标互质，且更靠近原点。

这说明点 $(x, y)$ 不是第一个被经过的点。

结论与假设矛盾，引理 2 得证。

***

发现原图贡献是轴对称的，所以我们可以只计算上半边贡献。

$$\sum_{i=2}^n\sum_{j=1}^{i-1}\lfloor \dfrac{n}{\max(i, j)} \rfloor^2[\gcd(i, j) = 1]$$


$$\sum_{i=2}^n\sum_{j=1}^{i-1}\lfloor \dfrac{n}{i} \rfloor^2[\gcd(i, j) = 1]$$

原式可以通过欧拉函数计算，代入得：

$$\sum_{i=2}^n\varphi(i)\times\lfloor \dfrac{n}{i} \rfloor^2$$

再考虑对角线的贡献，共 $n$ 个点，贡献为 $n^2$。

所以答案为：

$$n^2+2\times \sum_{i=2}^n\varphi(i)\times\lfloor \dfrac{n}{i} \rfloor^2$$

尽管 $\lfloor \dfrac{n}{i} \rfloor^2$ 可以整除分块，但是 $2\times 10^9$ 的线性复杂度前缀和不可接受，于是想到用杜教筛计算。

时间复杂度 $O(n^\frac{2}{3})$。

### 代码

```cpp
#include <iostream>
#include <unordered_map>
#define int __int128

using namespace std;

const int N = 6000010, mod = 1e9 + 7;

int n;
long long m;
int primes[N], cnt;
int phi[N], s[N];
unordered_map<long long, int> me;
bool st[N];

inline void get_euler(int n) // 线性筛 6e6 以内的欧拉函数值
{
    st[1] = true, phi[1] = 1;
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i, phi[i] = i - 1;
        for (int j = 0; primes[j] * i <= n; j ++ )
        {
            st[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }
}

int get_sum(int n) // 杜教筛板子
{
    if (n < N) return s[n];
    if (me[n]) return me[n];
    int res = n * (n + 1) / 2;
    for (int l = 2, r = 0; l <= n; l = r + 1)
    {
        r = n / (n / l);
        res = (res - (r - l + 1) * get_sum(n / l) % mod) % mod;
    }
    return me[n] = res;
}

signed main()
{
	get_euler(N - 1);
	for (int i = 1; i < N; i ++ )
		s[i] = (s[i - 1] + phi[i]) % mod;

	scanf("%lld", &m), n = m;
	int res = 0;
	for (int l = 2, r = 0; l <= n; l = r + 1)
	{
		r = n / (n / l); // 整除分块
		res = (res + (n / l) * (n / l) % mod * (get_sum(r) - get_sum(l - 1)) % mod) % mod;
	}

	res = res * 2 % mod;
	res = (res + n * n % mod) % mod;
	printf("%lld\n", (long long)((res + mod) % mod));
	return 0;
}
```

---

## 作者：IceKylin (赞：4)

### P10186 [YDOI R1] Lattice 题解

板。

考虑钦定直线 $y=kx$ 过点 $(i,j)$，显然，这条直线唯一确定了。但是由于贡献可能会算重，所以再限制 $\gcd(i,j)=1$，易知每条过点阵的直线都被不重不漏地计算了一次。

容易写出答案的式子为：

$$\text{ans}=\displaystyle\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)=1]\cdot\min\left\{\big\lfloor\dfrac{n}{i}\big\rfloor^2,\big\lfloor\dfrac{n}{j}\big\rfloor^2\right\}$$

先把后面那坨 $\min$ 拆开：

$$\text{ans}=2\displaystyle\sum_{i<j}^n[\gcd(i,j)=1]\cdot\big\lfloor\dfrac{n}{j}\big\rfloor^2+n^2$$

发现前面的式子很像欧拉函数的定义，所以有：

$$\text{ans}=2\displaystyle\sum_{j=2}^n\varphi(j)\cdot\big\lfloor\dfrac{n}{j}\big\rfloor^2+n^2$$

这样直接做是 $\mathcal{O(n)}$ 的，套个杜教筛可以做到 $\mathcal{O}\left(n^\frac{2}{3}\right)$。

---

## 作者：bochibochi (赞：3)

因为 $k\ge1$ 和 $k\le1$ 是对称的，所以我们只考虑斜率 $k\ge1$ 的情况，不难发现，这样算出的喜爱程度的和乘以 $2$，再减去 $n^2$ 就是答案（因为 $k=1$ 的情况被重复算了两次）。

考虑枚举斜率 $k=\frac yx~(y\ge x,\gcd(x,y)=1)$，则答案为

$$
\begin{aligned}
&\sum_{y=1}^n\sum_{x=1}^y \lfloor\frac ny\rfloor^2[gcd(x,y)=1]\\
=&\sum_{y=1}^n \lfloor\frac ny\rfloor^2 \sum_{x=1}^y[gcd(x,y)=1]\\
=&\sum_{y=1}^n \lfloor\frac ny\rfloor^2 \varphi(y)
\end{aligned}
$$



---

## 作者：System_Error_ (赞：3)

感觉自己的思路不如 @hdkk 的，终究是太蒻了，这里我讲下 @hdkk 的思路。

做这道题前可以先去做一下 [P2158 [SDOI2008] 仪仗队](https://www.luogu.com.cn/problem/P2158)，了解欧拉函数，莫比乌斯反演，数论分块，杜教筛等知识，下面就不过多阐述。

## subtask 1：

留给有耐心的人打表的，下面给出表：

$a_1=1$，$a_2=6$，$a_3=15$，$a_4=32$，$a_5=49$，$a_6=86$，$a_7=111$，$a_8=160$。

## subtask 2：

若一条直线经过了点，那它经过的第一个点 $(i,j)$ 必有 $\gcd(i,j)=1$ 并且它经过的点数应该是 $\lfloor \frac{n}{\max(i,j)} \rfloor$ 因为下一个点横坐标增加 $i$，纵坐标增加 $j$。

可以从 $(1,1)$ 到 $(n,n)$ 画一条对角线，左上部分贡献式子为：

$$ \sum\limits_{i=2}^n \sum\limits_{j=1}^{j<i} [\gcd(i,j)=1]\times\lfloor \frac{n}{i} \rfloor^2 $$

$i$ 是纵坐标，$j$ 是横坐标，因为有对角线，所以 $j<i$。

很明显右下和左上对称，贡献相同，所以把上面那个式子乘二加上对角线贡献就是最终答案，对角线上有 $n$ 个点且对角线上所有点在同一条直线，所以对角线贡献为 $n^2$。

最终等于：

$$ n^2+2\times\sum\limits_{i=2}^n \sum\limits_{j=1}^{j<i} [\gcd(i,j)=1]\times\lfloor \frac{n}{i} \rfloor^2 $$

计算这个式子，时间复杂度为 $O(n^2\log n)$。

## subtask 3：

我们可以简化一下求和符号后的式子，得出：

$$ \sum\limits_{i=2}^n \sum\limits_{j=1}^{j<i} [\gcd(i,j)=1]\times\lfloor \frac{n}{i} \rfloor^2=\sum\limits_{i=2}^n\varphi(i)\times\lfloor \frac{n}{i} \rfloor^2 $$

计算这个式子加上预处理欧拉函数，时间复杂度为 $O(n)$。

## subtask 4：

我们继续优化，对 $\lfloor \frac{n}{i} \rfloor^2$ 进行数论分块，设这个块左端为 $l$，右端为 $r$，则这个块的贡献为：

$$ \lfloor \frac{n}{l} \rfloor^2\times\sum\limits_{i=l}^r\varphi(i)$$

设：

$$ f(x)=\sum\limits_{i=1}^x\varphi(i) $$

则贡献为：

$$ \lfloor \frac{n}{l} \rfloor^2\times(f(r)-f(l-1)) $$

用杜教筛求解 $f(x)$，时间复杂度为 $O(n^{\frac{2}{3}})$。

[这里](https://www.luogu.com.cn/paste/rc5p0r55)是所有除打表外部分分的代码。

本题还可以莫比乌斯反演为主求解，只不过写题解的比较懒，就留给你们自己思考。

~~记得要取模~~。

---

## 作者：Link_Cut_Y (赞：1)

显然，方阵关于对角线对称，我们只考虑对角线下方的部分。

对于对角线下方的部分，直线 $f(x)$ 的斜率显然 $< 1$。不妨设斜率为 $\dfrac{j}{i}$，则 $i > j$，对答案的贡献为 $\left \lfloor \dfrac{n}{i} \right \rfloor ^ 2$。对答案有贡献，当且仅当 $(i, j) = 1$，否则重复计算。

故答案为：

$$\sum_{i = 1}^{n} \sum_{j = 1}^{i - 1} \left \lfloor \dfrac{n}{i} \right \rfloor ^ 2 [(i, j) = 1]$$

发现 $\left \lfloor \dfrac{n}{i} \right \rfloor ^ 2$ 与 $j$ 无关，移到外面来，得到：

$$ = \sum_{i = 1}^{n} \left \lfloor \dfrac{n}{i} \right \rfloor ^ 2 \sum_{j = 1}^{i - 1} [(i, j) = 1]$$

发现 $j$ 枚举的就是 $i$ 的欧拉函数，所以得到：

$$ = \sum_{i = 1}^{n} \left \lfloor \dfrac{n}{i} \right \rfloor ^ 2 \varphi(i)$$

对 $i$ 整除分块，对于一个左端点为 $l$，右端点为 $r$ 的块，其贡献为：

$$\left \lfloor \dfrac{n}{l} \right \rfloor ^ 2 \times \sum_{i = l}^{r} \varphi(i)$$

可以发现我们只需要求 $\left \lfloor \dfrac{n}{i} \right \rfloor$ 处的 $\varphi$ 前缀和。由于是求根号个点值的前缀和，可以直接使用 min-25 筛，如果偷懒也可以直接杜教筛。

复杂度应该是 $O(n ^ {2 / 3})$？

代码放一下：[杜教筛代码](https://www.luogu.com.cn/paste/h2iwx17j)。

---

## 作者：henrytb (赞：1)

好久没做数论题了，刚好有个板子题，就做了下。

相当于枚举一个斜率，然后看这个斜率的直线上面的 $n \times n$ 范围内点的平方。

我们钦定斜率小于 $1$，大于 $1$ 的部分和小于 $1$ 的部分答案是一样的，而且斜率等于 $1$ 的直线也只经过 $n$ 个点。所以答案是仅考虑斜率 $< 1$ 直线的情况的答案乘以 $2$ 再加上 $n^2$。

对于斜率 $< 1$ 的直线，枚举这条直线相当于枚举一个点 $(x, y)$ 满足 $x > y$，使得 $\gcd(x, y) = 1$，这样不重不漏地枚举了符合要求的斜率。对于这样的一条经过 $(0, 0)$ 与 $(x, y)$ 的直线，它经过的横纵坐标都在 $[1, n]$ 范围内的整点总共有 $\left\lfloor\frac{n}{x}\right\rfloor$ 个（因为 $x > y$）。

所以，答案即为

$$
\begin{aligned}
& \sum_{x > y}[\gcd(x, y) = 1]\left\lfloor\frac{n}{x}\right\rfloor^2\\
= & \sum_{x > y}\left\lfloor\frac{n}{x}\right\rfloor^2\sum_{d\mid x, d\mid y} \mu(d)\\
= & \sum_{d}\mu(d)\sum_{d | x} \left\lfloor\frac{n}{x}\right\rfloor^2 \sum_{d|y} [x > y] \\
= & \sum_d \mu(d)\sum_{x}\left\lfloor\frac{n}{dx}\right\rfloor^2(x - 1)\\
= & \sum_{h}\left\lfloor\frac{n}{h}\right\rfloor^2\sum_{t|h}\mu(t)\left(\frac{n}{t} - 1\right) \\
= & \sum_h\left\lfloor\frac{n}{h}\right\rfloor^2(\varphi(h) - [h = 1])
\end{aligned}
$$

然后就做完了，整除分块，用杜教筛就行。

---

## 作者：SamHJD (赞：1)

## [[YDOI R1] Lattice](https://www.luogu.com.cn/problem/P10186)

### Description

有一个 $n\times n$ 的间隔固定的点阵，左下角在坐标轴原点，对于每一个 $y=kx,k\in(0,\infin)$，其价值为经过的点的数量的平方。求所有 $y=kx$ 价值和。

### Solution

显然可以将 $k$ 分为 $(0,1),1,(1,\infin)$ 分开求解，其中 $(0,1).(1,\infin)$ 的答案相等，$y=x$ 的答案为 $n^2$。下面求解 $k\in(0,1)$ 中的答案。

枚举这条直线经过的第一个点，其坐标 $(x,y)$ 需满足 $\gcd(x,y)=1$，这条直线经过的点数则为 $\lfloor\dfrac{n}{x}\rfloor$，则答案为：

$$\sum\limits_{x=2}^{n}\sum\limits_{y=1}^{x-1}[\gcd(x,y)=1]\times\lfloor\dfrac{n}{x}\rfloor$$

其中 $\sum\limits_{y=1}^{x-1}[\gcd(x,y)=1]=\varphi(x)$，于是原式等于：

$$\sum\limits_{x=2}^{n}\varphi(x)\times\lfloor\dfrac{n}{x}\rfloor$$

对 $\lfloor\dfrac{n}{x}\rfloor$ 数论分块：

$$\lfloor\dfrac{n}{l}\rfloor\times\sum\limits_{x=l}^{r}\varphi(x)$$

杜教筛预处理出 $\varphi(i)$ 的前缀和便可计算，最终答案为上式乘 $2$ 加上 $n^2$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
template<typename T>
inline void read(T &x) {
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	x*=f;
}
const int N=1145141,MOD=1e9+7;
int p[N],phi[N],vis[N],cntp,n,ans;
map<int,int> rem,remphi;
void init(int n){
    phi[1]=1;
    for(int i=2;i<=n;++i){
        if(!vis[i]){
            p[++cntp]=i;
            phi[i]=i-1;
        }
        for(int j=1;j<=cntp&&i*p[j]<=n;++j){
            vis[i*p[j]]=1;
            if(i%p[j]!=0) phi[i*p[j]]=phi[i]*phi[p[j]];
            else{phi[i*p[j]]=phi[i]*p[j];break;}
        }
    }
    for(int i=2;i<=n;++i) phi[i]=(phi[i]+phi[i-1])%MOD;
}
int getphi(int x){
    if(x<N) return phi[x];
    if(rem[x]) return remphi[x];
    rem[x]=1;
    int res=x*(x+1)/2%MOD,l,r;
    for(l=2;l<=x;l=r+1){
        r=x/(x/l);
        res=(res-(r-l+1)*getphi(x/l)%MOD+MOD)%MOD;
    }
    remphi[x]=res;
    return res;
}
signed main(){
    read(n);
    init(1145141);
    int l,r;
    for(l=2;l<=n;l=r+1){
        r=n/(n/l);
        ans=(ans+(getphi(r)-getphi(l-1)+MOD)%MOD*(n/l)%MOD*(n/l)%MOD)%MOD;
    }
    ans=(ans*2%MOD+n*n%MOD)%MOD;
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：gyyyyx (赞：0)

莫反模板练手题。

显然一个点 $(a,b)$ 只会对斜率为 $\frac{b}{a}=\frac{\frac{b}{\gcd(a,b)}}{\frac{a}{\gcd(a,b)}}$ 的直线贡献。

考虑枚举 $\gcd(a,b)=1$ 的点，则答案为：

$$\sum\limits_{i=1}^n\sum\limits_{j=1}^n[\gcd(i,j)=1]\lfloor\frac{n}{\max(i,j)}\rfloor^2$$

由于有个 $\max$ 很难受，考虑只枚举 $j<i$：

$$2\sum\limits_{i=1}^n\sum\limits_{j=1}^{i-1}[\gcd(i,j)=1]\lfloor\frac{n}{i}\rfloor^2+n^2$$

加 $n^2$ 是当 $i=j$ 的时候贡献为 $n^2$。

看到这个形式大家应该都很熟悉了，开始推柿子：

$$
\begin{aligned}
&2\sum\limits_{i=1}^n\sum\limits_{j=1}^{i-1}[\gcd(i,j)=1]\lfloor\frac{n}{i}\rfloor^2+n^2\\
=&2\sum\limits_{d=1}^n\mu(d)\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j=1}^{i-1}\lfloor\frac{n}{id}\rfloor^2+n^2\\
=&2\sum\limits_{d=1}^n\mu(d)\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\lfloor\frac{n}{id}\rfloor^2(i-1)+n^2\\
=&2\sum\limits_{T=1}^n\lfloor\frac{n}{T}\rfloor^2\sum\limits_{d\mid T}(d-1)\mu(d)+n^2\\
=&2\sum\limits_{T=1}^n\lfloor\frac{n}{T}\rfloor^2(\sum\limits_{d\mid T}d\mu(d)-\sum\limits_{d\mid T}\mu(d))+n^2\\
=&2\sum\limits_{T=1}^n\lfloor\frac{n}{T}\rfloor^2(\varphi(T)-\varepsilon(T))+n^2\\
=&2\sum\limits_{T=1}^n\lfloor\frac{n}{T}\rfloor^2\varphi(T)-n^2\\
\end{aligned}$$

推到这里就没法推下去了，数论分块加杜教筛即可。

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
#define mod 1000000007
using namespace std;
int T,n,m;
vector <int> prime,phi;
vector <bool> vis;
unordered_map <int,LL> s;
LL Sum(int x){
	if(x<=m) return phi[x];
	if(s[x]) return s[x];
	LL ret(1ll*(x+1)*x/2%mod);
	for(int l(2),r;l<=x;l=r+1){
		r=x/(x/l);
		ret=(ret-(r-l+1)*Sum(x/l)%mod+mod)%mod;
	}
	return s[x]=ret;
}
LL ans;
int main(){
	scanf("%d",&n);
	m=min(n,(int)(6*round(pow(n,2.0/3.0))));
	phi.resize(m+1,0);
	vis.resize(m+1,0);
	phi[1]=1;
	for(int i(2);i<=m;++i){
		if(!vis[i]){
			prime.push_back(i);
			phi[i]=i-1;
		}
		for(auto p:prime){
			if(1ll*i*p>m) break;vis[i*p]=1;
			if(i%p) phi[i*p]=phi[i]*(p-1);
			else{phi[i*p]=phi[i]*p;break;}
		}
	}
	for(int i(1);i<=m;++i) (phi[i]+=phi[i-1])%=mod;
	for(int l(1),r;l<=n;l=r+1){
		r=n/(n/l);
		ans=(ans+(Sum(r)-Sum(l-1))*(n/l)%mod*(n/l)%mod+mod)%mod;
	}
	printf("%lld\n",((ans<<1ll)%mod-1ll*n*n%mod+mod)%mod);
	return 0;
}
```

---

## 作者：Hisy (赞：0)

## 分析
首先，我们设定在 $k$ 意义下的 $x$ 和 $y$，枚举它们。发现每一个贡献都是 $\lfloor\frac{n}{\max(x,y)}\rfloor^2$。设只需要计算一边，我们需要求：
$$\sum_{x=2}^{n}\sum_{y=1}^{i-1}\lfloor\frac{n}{\max(x,y)}\rfloor^2$$
以上式子还算重了很多，考虑限制看到的第一个点计算贡献，即多加一个条件 $[\gcd(x,y)=1]$。
$$\sum_{x=2}^{n}\sum_{y=1}^{x-1}[\gcd(x,y)=1]\lfloor\frac{n}{x}\rfloor^2$$
把第二个 $\sum$ 变成欧拉函数的形式，得：
$$\sum_{x=2}^{n}\varphi(x)\lfloor\frac{n}{x}\rfloor^2$$
最后的答案不是这一个。由于只计算了一边，所以要乘以 $2$。而且中间的对角线也需要算进去，贡献为 $n\times n$。

由于 $n$ 可以达到 $2^{31}-1$，所以欧拉函数需要使用杜教筛优化，整个式子的计算需要使用数论分块。
## 代码
```cpp
#include<bits/stdc++.h>
#define MAXN 1664511
#define MOD 1000000007
using namespace std;
typedef long long ll;
vector<int> prim;
bool flag[MAXN];
int phi[MAXN];
ll pre[MAXN];
map<int,ll> mp;
inline void prework(){
	phi[1]=1;
	for(int i=2;i<MAXN;++i){
		if(!flag[i]){
			prim.push_back(i);
			phi[i]=i-1;
		}
		for(int j=0;j<prim.size()&&i*prim[j]<MAXN;++j){
			flag[i*prim[j]]=true;
			if(i%prim[j]){
				phi[i*prim[j]]=phi[i]*(prim[j]-1);
			}else{
				phi[i*prim[j]]=phi[i]*prim[j];
				break;
			}
		}
	}
	for(int i=1;i<MAXN;++i){
		pre[i]=(pre[i-1]+phi[i])%MOD;
	}
}
ll varphi(int n){
	if(n<MAXN){
		return pre[n];
	}
	if(mp[n]){
		return mp[n];
	}
	ll res=1ll*n*(n+1ll)>>1ll;
	for(int l=2,r=0;l<=n;l=r+1){
		r=n/(n/l);
		(res-=varphi(n/l)*1ll*(r-l+1)%MOD)%=MOD;
	}
	return mp[n]=(res%MOD+MOD)%MOD;
}
int main(){
	prework();
	int n;
	scanf("%d",&n);
	ll res=0;
	for(int l=2,r=0;l<=n;l=r+1){
		r=n/(n/l);
		(res+=1ll*(n/l)*(n/l)%MOD*(varphi(r)-varphi(l-1)))%=MOD; 
	}
	printf("%lld\n",(2ll*res+1ll*n*n)%MOD);
	return 0;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：0)

#手把手教你如何获得最优解倒数第三#

首先显然对于一条符合题意的直线，其一定经过一个点 $(x,y)$ 满足 $\gcd(x,y)=1$。

于是式子可以写成 $\sum\limits_{x}\sum\limits_{y}[\gcd(x,y)=1]\min^2(\lfloor\dfrac nx\rfloor,\lfloor\dfrac ny\rfloor)$。

$\min$ 不太好处理，所以考虑枚举。容易发现 $\min$ 相同的一些 $(x,y)$ 形状相当于是一个大正方形减去一个小正方形，另外由于 $x$ 和 $y$ 是对称的所以可以直接一次整除分块解决。

现在问题变成了求 $\sum\limits_{x=1}^k\sum\limits_{y=1}^k[\gcd(x,y)=1]$。这个很容易：

$$
\begin{array}{cl}
&
\sum\limits_{x=1}^k\sum\limits_{y=1}^k[\gcd(x,y)=1]\\
=&\sum\limits_{x=1}^k\sum\limits_{y=1}^k\sum\limits_{d|x,d|y}\mu(d)\\
=&\sum\limits_{d=1}^k\mu(d)\lfloor\dfrac kd\rfloor^2
\end{array}
$$

直接整除分块+杜教筛即可。

复杂度还是 $O(n^{\frac 23})$ 但是常数较大，通过以下卡常就能解决：

1. 加减运算尽量减少取模而改为直接判断
2. 在两层整除分块中会要用到上一次的值，直接存下来不要重新算
3. 前面线性筛预处理大概 $3\times 10^6$ 跑的最快
4. 整除分块的时候避免 `l=r+1` 溢出使用 `unsigned int` 而非 `long long`，这个能快一倍

```cpp
bool isnp[3000005];
int mu[3000005];
vector<int>pr;
void sieve(int n){// 线性筛 mu
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!isnp[i])pr.push_back(i),mu[i]=mod-1;
		for(auto j:pr){
			if(i*j>n)break;
			isnp[i*j]=1;
			mu[i*j]=sub(0,mu[i]);
			if(i%j==0){
				mu[i*j]=0;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++)Add(mu[i],mu[i-1]);
}
unordered_map<int,int>mp;
int Smu(int n){// 杜教筛算前缀和
	if(n<=3000000)return mu[n];
	if(mp.count(n))return mp[n];
	int ans=1;
	for(unsigned int l=2,r;l<=n;l=r+1)r=n/(n/l),Sub(ans,mul(Smu(n/l),(r-l+1)%mod));
	return mp[n]=ans;
}
int f(int n){// 内层整除分块
	int ans=0;
	for(unsigned int l=1,r,lst=0,tmp;l<=n;l=r+1,lst=tmp){
		r=n/(n/l);
		Add(ans,mul(sub(tmp=Smu(r),lst),mul((n/l)%mod,(n/l)%mod)));
	}
	return ans;
}

void __INIT__(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
void __SOLVE__(int _cs){
	sieve(3000000);
	int n;
	cin>>n;
	int ans=0,lst=0;// 外层整除分块
	for(unsigned int l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		int tmp=(mod-lst)%mod;
		Add(tmp,lst=f(r));
		Add(ans,mul(tmp,qpow(n/l,2)));
	}
	cout<<ans<<"\n";
}
```

---

## 作者：zyn_ (赞：0)

# P10186 [YDOI R1] Lattice

显然斜率 $k$ 是有理数时才能对答案有贡献。设 $k=\dfrac{p}{q}$，且 $\gcd(p,q)=1$，$p,q\le n$，那么 $y=kx$ 经过 $\min\{\lfloor\dfrac{n}{p}\rfloor,\lfloor\dfrac{n}{q}\rfloor\}$ 个整点，贡献为 $(\min\{\lfloor\dfrac{n}{p}\rfloor,\lfloor\dfrac{n}{q}\rfloor\})^2$。

### 情况一：$p=q$

由 $\gcd(p,q)=1$，故 $p=q=1$，贡献为 $n^2$。

### 情况二：$p>q$

$y=kx$ 的贡献为 $\lfloor\dfrac{n}{p}\rfloor^2$。

故所有这种直线的贡献为

$$
\begin{aligned}
\sum_{p=1}^{n}\sum_{q=1}^{p-1}[\gcd(p,q)=1]\lfloor\dfrac{n}{p}\rfloor^2 = \sum_{p=1}^{n}\lfloor\dfrac{n}{p}\rfloor^2\varphi(p)
\end{aligned}
$$

考虑整除分块，设 $l\le p\le r$ 时均有 $\lfloor\dfrac{n}{p}\rfloor=d$。这一块的和为 $\sum_{p=l}^{r}d^2\varphi(p)$，用杜教筛计算 $\varphi(p)$ 的前缀和。

### 情况三：$p<q$

与情况二相同，$p$ 和 $q$ 是对称的。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 3000009ll
#define MX 3000000ll
#define mod 1000000007
#define ump unordered_map
ump<ll,ll> Sphi;
ll n,sphi[N],ans;
int phi[N],prime[N],cnt;
bool p[N];
void sieve(int n){
	cnt=0;phi[1]=1;
	for(int i=2;i<=n;++i)p[i]=1;
	for(int i=2;i<=n;++i){
		if(p[i])prime[++cnt]=i,phi[i]=i-1;
		for(ll j=1;j<=cnt&&i*prime[j]<=n;++j){
			p[i*prime[j]]=0;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	for(int i=1;i<=n;++i)sphi[i]=sphi[i-1]+phi[i];
}
ll getphisum(ll n){
	if(n<=MX)return sphi[n];
	if(Sphi[n])return Sphi[n];
	ll res=n*(n+1)/2;
	for(ll l=2,r;l<=n;l=r+1)r=n/(n/l),res-=(r-l+1)*getphisum(n/l);
	return Sphi[n]=res;
}
int main(){
	sieve(MX);
	scanf("%lld",&n);
	for(ll l=2,r;l<=n;l=r+1)
		r=n/(n/l),ans=(ans+(n/l)*(n/l)*(getphisum(r)-getphisum(l-1)))%mod;
	ans=((ans*2+n*n)%mod+mod)%mod;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：_7thRC_CB_CRP_ (赞：0)

# 前文

前置知识：欧拉函数，杜教筛，整除分块。

# 题解

## 题目转化成式子
	
这个题目很难让人想到怎么做，所以可以用样例分析一下式子。

$ n=5 $ 时，

![](https://cdn.luogu.com.cn/upload/image_hosting/ctve2i19.png)

因为图中黑线将坐标轴分为了对称的两部分，所以，令 $s(k)$ 为 $y=kx$ 的直线对答案的贡献。

$ans=2\times\sum_{i=1}^{i \le n}\sum_{j=i+1}^{j \le n}[\gcd(i,j)=1]s(\frac{i}{j})+ n^2$

首先看一条 $\frac {a}{b}$ 的直线对答案的贡献。

其实就是：

$ s(\frac {a} {b}) = \lfloor \frac{n}{b} \rfloor^2$

## 式子推导
所以 

$ans=2\times\sum_{i=1}^{i \le n}\sum_{j=i+1}^{j \le n}[\gcd(i,j)=1]\lfloor \frac{n}{j} \rfloor^2+ n^2$

改编枚举顺序，

$ans=2\times\sum_{j=2}^{j \le n}\lfloor \frac{n}{j} \rfloor^2\sum_{i=1}^{i\lt j}[\gcd(i,j)=1]+ n^2$

后面那坨就是 $\varphi$。

$ans=2\times\sum_{j=2}^{j \le n}\lfloor \frac{n}{j} \rfloor^2\varphi(j-1)+ n^2$

所以说用整除分块枚举 $j$ 再用杜教筛求 $\varphi$ 函数的前缀和就行了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long prim[900001],cnt,mu[10000001],phi[10000001];
bool vis[10000001];
void get_phi(long long n) {
    phi[1]=1;
    for(int i=2;i<=n;i++) {
        if(!vis[i]) prim[++cnt]=i,phi[i]=i-1;
        for(int j=1;j<=cnt&&prim[j]*i<=n;j++) {
            if(i*prim[j]>n) break;
            vis[i*prim[j]]=1;
            if(i%prim[j]==0) { 
				phi[i*prim[j]]=phi[i]*prim[j]; 
				break;
			} else phi[i*prim[j]]=phi[i]*phi[prim[j]];
        }
    }
    for(int i=1;i<=10000000;i++)
    	phi[i]+=phi[i-1];
}//线性筛预处理欧拉函数 
map<int,long long>sp;
long long gse(long long n) {
	if(n<=10000000)
			return phi[n];
	if(sp[n])
		return sp[n];
	long long ans=(n+1)*n/2;
	long long l=2;
	while(l<=n) {
		long long r=n/(n/l);
		ans-=((r-l+1)*(gse(n/l)));
		l=r+1;
	}
	sp[n]=ans;
	return ans;
}//杜教筛 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	get_phi(10000000);
	long long n;
	cin>>n;
	long long l=2,ans=0;
	while(l<=n) {
		long long r=n/(n/l);
		ans=ans+(gse(r)-gse(l-1))%1000000007*((n/l)%1000000007*(n/l)%1000000007)%1000000007;
		l=r+1;
	}//丑陋的整除分块 
	cout<<(2*ans%1000000007+n*n%1000000007)%1000000007;
} 
```

# 后记

作者这道题想了两个小时如何化简：

$ans=2\times\sum_{j=2}^{j \le n}\lfloor \frac{n}{j} \rfloor^2\sum_{i=1}^{i\lt j}[\gcd(i,j)=1]+ n^2$

最后才发现后一个是欧拉函数，所以信竟中还是要点到为止。

---

## 作者：AAA404 (赞：0)

先考虑计算左上角的贡献，做过 [P1447](https://www.luogu.com.cn/problem/P1447) 的同学应该都看出来，贡献的计算显然是：

$$\sum_{i=1}^{n} \sum_{j=1}^{i-1} [\gcd(i,j)=1] \times \lfloor \frac{n}{i} \rfloor ^2$$

后面一坨可以数论分块，前面一坨可以瞪出其实就是 $\varphi(i)$。

右下角和左上角计算相同，加上对角线贡献为 $n^2$，答案就是：

$$n^2 + 2 \times \sum_{i=1}^{n} \varphi(i) \times \lfloor \frac{n}{i} \rfloor ^2$$

可以数论分块，欧拉函数区间和可以差分成前缀差，用杜教筛即可。

时间复杂度：$O(n^{\frac{2}{3}})$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+5,mod=1e9+7;
int n,phi[N],L,sum[N],pri[N],tot;
bool np[N];
void init(int L)
{
	np[1]=phi[1]=1;
	for(int i=2;i<=L;i++)
	{
		if(!np[i])
		pri[++tot]=i,phi[i]=i-1;
		for(int j=1;j<=tot&&i*pri[j]<=L;j++)
		{
			np[i*pri[j]]=1;
			if(i%pri[j]==0){phi[i*pri[j]]=phi[i]*pri[j];break;}
			phi[i*pri[j]]=phi[i]*phi[pri[j]];
		}
	}
	for(int i=1;i<=L;i++)sum[i]=sum[i-1]+phi[i];
	return;
}
map<long long,long long>sum_map;
int S(int x)
{
	if(x<=L)return sum[x];
	if(sum_map[x])return sum_map[x];
	long long ans=x*(x+1)/2ll;
	for(int i=2;i<=x;)
	{
		int nxt=x/(x/i);
		ans=(ans-(nxt-i+1)*S(x/i)%mod+mod)%mod;
		i=nxt+1;
	}
	return sum_map[x]=ans;
}
signed main()
{
	clock_t c1=clock();
#ifdef LOCAL
 	freopen("1.in","r",stdin);
 	freopen("1.out","w",stdout);
#endif
    ios::sync_with_stdio(0);
 	cin.tie(0);cout.tie(0);
	cin>>n;
	L=(long long)pow(n,0.66666666666);
	init(L);
	int pre=1,ans=0;
	for(int i=1;i<=n;)
	{
		int nxt=n/(n/i);
		int cur=S(nxt);
		(ans+=(n/i)*(n/i)%mod*(cur-pre)%mod)%=mod;
		pre=cur,i=nxt+1;
	}
	cout<<(ans*2+n*n)%mod;
#ifdef LOCAL
	cerr<<"Time used:"<<clock()-c1<<"ms";
#endif
 	return 0;
}
```

---

## 作者：Kreado (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10186)。

简单题。

## 思路

枚举点 $(i,j)$，考虑 $(0,0)$ 到 $(i,j)$ 的直线对答案的贡献，为了不算重，我们钦定 $i\bot j$，那么这对 $(i,j)$ 的贡献就是 $\biggl\lfloor \dfrac{n}{\max(i,j)} \biggl\rfloor^2$，答案就是 

$$\sum_{i=1}^n\sum_{j=i}^n \biggl\lfloor\dfrac{n}{j}\biggl\rfloor^2[i\bot j]\\$$

交换求和顺序得到

$$\sum_{j=1}^n \biggl\lfloor\dfrac{n}{j}\biggl\rfloor^2 \sum_{i=1}^j [i\bot j]$$

后面那个显然是欧拉函数，$\varphi(j)$，最终得到

$$\sum_{j=1}^n\biggl\lfloor\dfrac{n}{j}\biggl\rfloor^2  \varphi(j)$$

杜教筛即可。

---

## 作者：diqiuyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10186)。

不妨设这条直线和点阵的横坐标最小的交点为 $(a,b)$，显然 $\gcd(a,b)=1$，则该直线与点阵的交点数为 $\min(\lfloor\dfrac{n}{a}\rfloor,\lfloor\dfrac{n}{b}\rfloor)$。

那么，答案可以转化为 $\sum_{i=1}^n\sum_{j=1}^n\min(\lfloor\dfrac{n}{i}\rfloor,\lfloor\dfrac{n}{j}\rfloor)^2[\gcd(i,j)=1]$。

考虑分别计算 $\lfloor\dfrac{n}{i}\rfloor$ 和 $\lfloor\dfrac{n}{j}\rfloor$ 的贡献。

设 $f(n)=\sum_{i=1}^n\sum_{j=1}^{i}\lfloor\dfrac{n}{i}\rfloor^2[\gcd(i,j)=1]$，则答案为 $2f(n)-n^2$。

$$\begin{aligned} f(n)&=\sum_{i=1}^n\sum_{j=1}^{i}\lfloor\dfrac{n}{i}\rfloor^2[\gcd(i,j)=1]\\&=\sum_{i=1}^n\lfloor\dfrac{n}{i}\rfloor^2\varphi(i)\end{aligned}$$

使用整除分块和杜教筛维护即可，时间复杂度为 $O(n^\frac{2}{3})$。
```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define uint unsigned int
#define pii pair<int,int>
using namespace std;
inline int read(){
	int x=0;bool f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return f?x:-x;
}
const int mod=1e9+7;
int n,phi[1000005],cnt,prime[100005],ans;
bitset<1000005> vis;
unordered_map<int,int> mp;
int s(int x){
	if(x<=1000000) return phi[x];
	if(mp[x]) return mp[x];
	int res=(1ll*(x+1)*x>>1)%mod,l=2,r;
	while(l<=x)
		r=x/(x/l),res=(res-1ll*(r-l+1)*s(x/l)%mod+mod)%mod,l=r+1;
	return mp[x]=res;
}
int main(){
	n=read(),phi[1]=1;
	for(int i=2;i<=min(n,1000000);i++){
		if(!vis[i]) prime[++cnt]=i,phi[i]=i-1;
		for(int j=1;j<=cnt&&prime[j]<=min(n,1000000)/i;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]) phi[i*prime[j]]=phi[i]*phi[prime[j]];
			else{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
		}
	}
	for(int i=2;i<=min(n,1000000);i++){
		phi[i]+=phi[i-1];
		if(phi[i]>=mod) phi[i]-=mod;
	}
	for(int l=1,r;l<=n;){
		r=n/(n/l),ans=(ans+1ll*(n/l)*(n/l)%mod*(s(r)-s(l-1)+mod)%mod)%mod;
		if(r==INT_MAX) break;
		l=r+1;
	}
	printf("%d\n",(ans*2%mod-1ll*n*n%mod+mod)%mod);
    return 0;
}
```

---

## 作者：modfish_ (赞：0)

考完连夜恶补杜教筛（

## 思路
我第一眼看上去就想起了这题：[P2158 [SDOI2008] 仪仗队](https://www.luogu.com.cn/problem/P2158)。

我们不难发现：如果某条直线穿过了若干个点，那么它第一个穿过的点 $(x,y)$ 一定满足 $\gcd(x,y)=1$。

证明：

假设 $\gcd(x,y)=d(d>1)$，则 $(\frac{x}{d},\frac{y}{d})$ 一定也被该直线穿过，且比 $(x,y)$ 先被穿过。

而且，每一个 $\gcd(x,y)=1$ 的点都唯一对应一条直线。所以，我们可以枚举 $\gcd(x,y)=1$ 的点，并考虑它的贡献。易知这条直线上共有 $\lfloor\frac{n}{\max\{x,y\}}\rfloor$ 个点。所以，我们写出答案的表达式：

$$\sum_{x=1}^n\sum_{y=1}^n[\gcd(x,y)=1]\times\lfloor\frac{n}{\max\{x,y\}}\rfloor^2$$

考虑化简。注意到那个 $\max$ 不好处理，我们不妨先讨论 $x\ge y$ 的情况。$x\le y$ 的情况是对称的，最后减去 $x=y$ 的重复情况即可。

则在 $x\ge y$ 时，答案为：

$$
\begin{aligned}
&\sum_{x=1}^n\sum_{y=1}^x[\gcd(x,y)=1]\times\lfloor\frac{n}{x}\rfloor^2\\
&=\sum_{x=1}^n\lfloor\frac{n}{x}\rfloor^2\sum_{y=1}^x[\gcd(x,y)=1]\\
&=\sum_{x=1}^n\lfloor\frac{n}{x}\rfloor^2\times\varphi(x)\\
\end{aligned}
$$

这样，前三个 Subtask 的部分分就到手了，可以 $O(n)$ 线性处理。

但是，最后一个 Subtask 就不能这么做了。怎么办呢？

注意到 $\lfloor\frac{n}{x}\rfloor^2$ 是一个整除式，可以使用数论分块优化计算。这样就只要枚举 $O(\sqrt n)$ 次了。但是，这样我们就需要求出 $\varphi(x)$ 的前缀和，可以使用杜教筛实现。

## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 1e7 + 5, mod = 1e9 + 7;

int pr[maxn], ntp[maxn], ps = 0;
ll phi[maxn], n2;
map<int, ll> mp;

void prime(int m){
	ntp[1] = phi[1] = 1;
	for(int i = 2; i <= m; i ++){
		if(!ntp[i]) pr[++ ps] = i, phi[i] = i - 1;
		for(int j = 1; j <= ps && i * pr[j] <= m; j ++){
			ntp[i * pr[j]] = 1;
			if(i % pr[j] == 0){
				phi[i * pr[j]] = phi[i] * pr[j];
				break;
			}else phi[i * pr[j]] = phi[i] * phi[pr[j]];
		}
	}
}
ll sum(ll m){
	if(m <= n2) return phi[m];
	if(mp[m]) return mp[m];
	ll l = 2, r;
	ll ans = 0;
	while(l <= m){
		r = m / (m / l);
		ans = (ans + sum(m / r) * (r - l + 1) % mod) % mod;
		l = r + 1;
	}
	ans = ((m * (m + 1) / 2) % mod + (mod - ans)) % mod;
	mp[m] = ans;
	return ans;
}

int main(){
	ll n;
	scanf("%lld", &n);
	n2 = powl(n, 2.0 / 3.0);
	prime(n2);
	for(int i = 1; i <= n2; i ++) phi[i] = (phi[i] + phi[i - 1]) % mod;
	ll ans = 0;
	ll l = 1, r;
	while(l <= n){
		r = n / (n / l);
		ans = (ans + ((n / r) * (n / r) % mod) * (sum(r) + mod - sum(l - 1)) % mod) % mod;
		l = r + 1;
	}
	ans = (ans * 2 % mod + (mod - n * n % mod)) % mod;
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：sbno333 (赞：0)

这道题还是很板的，~~但是让蒟蒻体验到了当神犇的感觉。~~

这道题做过类似题目的都知道，从原点出发，到达任一整点且不经过其它点当且仅当该点横坐标纵坐标互质，下面给出反证法证明。

假设不成立，设这个点为 $(ax,ay)$，$a$ 为两个坐标的最大公因数，$a\not=0$。

则存在 $(x,y)$，因为 $a\not=1$，因此 $(x,y),(ax,ay)$ 不是一个点。

原点的直线到 $(x,y)$ 延长为 $2$ 倍为到 $(2x,2y)$，$3$ 倍为 $(3x,3y)\dots$ 延长 $a$ 倍为 $(ax,ay)$，这之前经过了 $(x,y)$，不成立，因此要求互质。

那么同理，我们同样可以得到有多少经过某个点的直线能经过的点。

显然每个点只会经过一次，可以想象一条直线旋转，表示所有直线，能想象出只会经过一个点。

我们设经过的第一个点为 $(x,y)$，$\gcd(x,y)=1$。

那么经过的第 $k$ 个点为 $(kx,ky)$，显然有 $kx,ky\le n$。

移项得到 $k\le \frac n x,k\le \frac n y$。

由于 $k$　为整数，因此向下取整，$k\le \lfloor\frac n x\rfloor,k\le \lfloor\frac n y\rfloor$。

合并得到 $k\le \min(\lfloor\frac n x\rfloor,\lfloor\frac n y\rfloor)$。

答案为 $\sum\limits_{x=1}^{n}\sum\limits_{y=1}^{x}[\gcd(x,y)=1]\min(\lfloor\frac n x\rfloor,\lfloor\frac n y\rfloor)^2$。

扫兴的是 $\min$ 非常难以消掉，我们不妨设 $y\le x$，显然对于 $x<y$ 和 $y<x$ 答案相同，$x=y$ 也能轻松处理。

则 $k\le \min(\lfloor\frac n x\rfloor,\lfloor\frac n y\rfloor)\to k\le \lfloor\frac n x\rfloor$。

答案变为 $\sum\limits_{x=1}^{n}\sum\limits_{y=1}^{x}[\gcd(x,y)=1]\lfloor\frac n x\rfloor^2$。

显然 $y$ 与 $\lfloor\frac n x\rfloor^2$ 与无关，可以变为 $\sum\limits_{x=1}^{n}(\sum\limits_{y=1}^{x}[\gcd(x,y)=1])\lfloor\frac n x\rfloor^2$。

对于 $(\sum\limits_{y=1}^{x}[\gcd(x,y)=1])$，我们发现这和欧拉函数定义相同，可以写成 $\varphi(x)$。

那么就变成了 $\sum\limits_{x=1}^{n}\varphi(x)\lfloor\frac n x\rfloor^2$。

这时你能拿到 $50$ 分的好成绩。

我们发现如果只有 $\lfloor\frac n x\rfloor^2$，可以整数分块处理。

但是还有 $\varphi(x)$，每一块由于编号是连续的，可以用杜教筛算出每一块的这部分和，另一部分由于块内相同，因此由乘法分配律可以直接乘。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int __int128
map<int,int> b;
const int N=10000000;
bool vis[N+9];
int q[N+9];
int inn;
int bb[N+9];
int phi(int t){//杜教筛
	if(t<=N){
		return bb[t];
	}
	if(t==1){
		return 1;
	}
	if(b[t]){
		return b[t];
	}
	int ans;
	ans=(t*t+t)/2;
	int r;
	r=1;
	for(int l=2;l<=t;l=r+1){
		r=t/(t/l);
		ans-=(r-l+1)*phi(t/l);
	}
	b[t]=ans;
	return ans;
}
void inite(){//杜教筛初始化
	vis[1]=1;
	bb[1]=1;
	for(int i=2;i<=N;i++){
		if(!vis[i]){
			q[++inn]=i;
			bb[i]=i-1;
		}
		for(int j=1;j<=inn&&q[j]*i<=N;j++){
			vis[q[j]*i]=1;
			bb[q[j]*i]=bb[i]*(q[j]-1);
			if(i%q[j]==0){
				bb[q[j]*i]=bb[i]*q[j];
				break;
			}
		}
	}
	for(int i=2;i<=N;i++){
		bb[i]+=bb[i-1];
	}
}
const int mod=1e9+7;
signed main(){
	inite();
	long long n;
	cin>>n;
	int ans;
	ans=0;
	for(int l=1,r=1;l<=n;l=r+1){
		r=n/(n/l);//整数分块
		ans+=(phi(r)%mod-phi(l-1)%mod+(int)(1e9)*mod)%mod*(n/l)%mod*(n/l)%mod;
		ans%=(int)(1e9+7);
	}
	cout<<(long long)((ans*2-n*n%mod+mod*(int)(1000))%(int)(1e9+7));//x<=y 的情况分成 x<y,x=y，翻倍后由于 x<y 与 y<x 答案同，因此为 x!=y,2(x=y)，减去 x=y，这是容易处理的，如代码所示，得到答案。
	return 0;
}
```
代码丑陋勿喷。

---

## 作者：YangJZHello (赞：0)

## [P10186 [YDOI R1] Lattice](https://www.luogu.com.cn/problem/P10186)
### 题目大意
对于直线 $y=kx,k\in(0,\infty)$，其贡献为该直线经过的所有坐标为 $(x,y),x,y\in\{x|x\leq n,x\in\mathbb Z_+\}$ 的点的个数的平方。计算总贡献和对 $10^9+7$ 取模的值。

### 数据范围
$1\leq n\leq2^{31}-1$。

___
首先转化为纯数学问题。我们知道当 $\gcd(x,y)\neq1$ 时，点 $(x,y)$ 一定与一个切比雪夫距离比自己小的点在同一条题中给出的直线上。故所有直线的数量为
$$\sum^n_{i=1}\sum^n_{j=1}\varepsilon[\gcd(i,j)]$$
而该式中过点 $(i,j)$ 的直线经过的点的个数为 $\min\left(\left\lfloor \frac{n}{i}\right\rfloor,\left\lfloor \frac{n}{j}\right\rfloor\right)$。则我们要求的值即为
$$
\sum^n_{i=1}\sum^n_{j=1}\min\left(\left\lfloor \frac{n}{i}\right\rfloor,\left\lfloor \frac{n}{j}\right\rfloor\right)^2\cdot\varepsilon[\gcd(i,j)]
$$
用莫比乌斯反演化式子即可。
$$
\begin{array}{cl}
&\sum^n_{i=1}\sum^n_{j=1}\min\left(\left\lfloor \frac{n}{i}\right\rfloor,\left\lfloor \frac{n}{j}\right\rfloor\right)^2\cdot\varepsilon[\gcd(i,j)]\\
=&\sum^n_{i=1}\sum^n_{j=1}\min\left(\left\lfloor \frac{n}{i}\right\rfloor,\left\lfloor \frac{n}{j}\right\rfloor\right)^2\sum_{d|\gcd(i,j)}\mu(d)\\
=&\sum^n_{d=1}\sum^{\lfloor n/d\rfloor}_{i=1}\sum^{\lfloor n/d\rfloor}_{j=1}\min\left(\left\lfloor \frac{n}{id}\right\rfloor,\left\lfloor \frac{n}{jd}\right\rfloor\right)^2\mu(d)\\
=&\sum^n_{d=1}\mu(d)\left(2\sum^{\lfloor n/d\rfloor}_{i=1}\sum^{i}_{j=1}\left\lfloor \frac{n}{id}\right\rfloor^2-\sum_{i=1}^{\lfloor n/d\rfloor}\left\lfloor \frac{n}{id}\right\rfloor^2\right)\\
=&\sum^n_{d=1}\mu(d)\sum^{\lfloor n/d\rfloor}_{i=1}(2i-1)\left\lfloor \frac{n}{id}\right\rfloor^2\\
=&\sum^n_{T=1}\left\lfloor \frac{n}{T}\right\rfloor^2\sum_{d|T}\mu(d)(2\times\frac{T}{d}-1)\\
=&\sum^n_{T=1}\left\lfloor \frac{n}{T}\right\rfloor^2\left(2\sum_{d|T}\mu(d)\times\frac{T}{d}-\sum_{d|T}\mu(d)\right)\\
=&\sum^n_{T=1}\left\lfloor \frac{n}{T}\right\rfloor^2\left(2N\circ\mu(T)-u\circ\mu(T)\right)\\
=&\sum^n_{T=1}\left\lfloor \frac{n}{T}\right\rfloor^2\left(2\varphi(T)-\varepsilon(T)\right)\\
\end{array}
$$
这样的话我们在外层使用数论分块，外层时间复杂度为 $\mathcal O(\sqrt n)$。内层中 $\varepsilon(T)$ 可以 $\mathcal O(1)$ 求得区间和。 

如果我们预处理 $\varphi(T)$ 以及其前缀和，时间复杂度为 $\mathcal O(n)$，显然只能拿到 50pts。

由于是求数论函数前缀和，想到运用杜教筛求：

由杜教筛可以得到
$$g(1)S_\varphi(n)=\sum_{i=1}^{n}g\circ\varphi(i)-\sum_{i=2}^{n}g(i)S_\varphi\left(\left\lfloor\frac{n}{i}\right\rfloor\right)$$
取 $g=u$，则
$$S_\varphi(n)=\frac{n(n+1)}{2}-\sum_{i=2}^{n}S_\varphi\left(\left\lfloor\frac{n}{i}\right\rfloor\right)$$

预处理 $\mathcal O(n^{\frac{2}{3}})$ 的 $S_\varphi$，则最终的时间复杂度为 $\mathcal O(n^{\frac{2}{3}})$。

参考代码：
```cpp
#include <iostream>
#include <map>
#include <bitset>
#include <vector>

#define ll long long
#define il inline
#define re register
#define rep(i, s, t) for(re ll i=s; i<=t; ++i)
const ll MAXK=1664510, P=1e9+7;

namespace hel {
    std::map<ll, ll> m;
    ll S_mem[MAXK+3];
    std::bitset<MAXK+3> vis;
    std::vector<ll> Pri;

    void init() {
        S_mem[1] = 1;
        rep(i, 2, MAXK) {
            if(!vis[i]) {
                Pri.push_back(i);
                S_mem[i] = i-1;
            }
            for(ll p:Pri) {
                if(i*p>MAXK) break;
                vis[i*p] = 1;
                if(i%p==0) {
                    S_mem[i*p] = S_mem[i]*p%P;
                    break;
                }
                S_mem[i*p] = S_mem[i]*S_mem[p]%P;
            }
        }
        rep(i, 2, MAXK) S_mem[i] = (S_mem[i-1]+S_mem[i])%P;
        return;
    }

    il ll S(re ll n) {
        if(n<=MAXK) return S_mem[n];
        if(m.count(n)) return m[n];
        re ll l, r;
        re ll ans=0;
        for(l=2, r=0; l<=n; l=r+1) {
            r = n/(n/l);
            ans = (ans+(r-l+1)*S(n/l)%P)%P;
        }
        return m[n]=((n*(n+1)/2%P-ans)%P+P)%P;
    }

    il ll S(re ll l, re ll r) {
        return ((S(r)-S(l-1))%P+P)%P;
    }

    void main() {
        re ll n, l, r, ans=0;
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cin >> n;
        init();
        for(l=1, r=0; l<=n; l=r+1) {
            r = n/(n/l);
            ans = (ans+(n/l)*(n/l)%P*(2*S(l, r)%P+(P-(l==1))%P)%P)%P;
        }
        std::cout << ans << '\n';
        return;
    }
}

int main() {
    hel::main();
    return 0;
}
```


---

