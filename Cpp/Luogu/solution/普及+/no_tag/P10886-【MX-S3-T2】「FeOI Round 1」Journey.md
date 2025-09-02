# 【MX-S3-T2】「FeOI Round 1」Journey

## 题目背景

原题链接：<https://oier.team/problems/S3B>。

---

![](bilibili:BV1pv411C7ti)

## 题目描述

小 W 最近正在学习某编程语言。

这个编程语言有个语句如下：

```
range(a,b,c)
```

这个语句表示一个序列，这个序列是这样的：

$$
[a,a+c,a+2c,\cdots,a+kc]
$$

其中，$k$ 是最大的满足 $a+kc<b$ 的非负整数 $k$。例如 `range(1,7,2)` 表示的序列为 $[1,3,5]$。

小 W 想问你一个问题：给你一个长为 $n$ 的序列 $g$（下标从 $1$ 开始），求出下列式子的值，答案模 $10^9 +7$。

$$
\sum_{a=1}^{n}\sum_{b=a+1}^{n+1}\sum_{c=1}^{n}\sum\limits_{i\in \mathrm{range}(a,b,c)} g_i
$$



## 说明/提示

**【样例解释 #1】**

$g=[2,1]$（下标从 $1$ 开始）

令 $ans=\sum\limits_{i\in \mathrm{range}(a,b,c)} g_i$。

当 $a=1,b=2,c=1$ 时，$ans=2$。

当 $a=1,b=2,c=2$ 时，$ans=2$。

当 $a=1,b=3,c=1$ 时，$ans=2+1=3$。

当 $a=1,b=3,c=2$ 时，$ans=2$。

当 $a=2,b=3,c=1$ 时，$ans=1$。

当 $a=2,b=3,c=2$ 时，$ans=1$。

答案为 $\sum ans=2+2+3+2+1+1=11$。

**【样例解释 #2】**

该样例满足特殊性质 A。

**【数据范围】**

对于 $100\%$ 的数据：$1\leq n\leq 2\times 10^7$，$0\leq A,B,C,g_n<10^9 +7$。

| 测试点编号 |       $n=$       | 特殊性质 |
| :--------: | :--------------: | :------: |
|    $1$     |       $1$        |    AB    |
|    $2$     |      $1000$      |    无    |
|    $3$     |      $1000$      |    无    |
|    $4$     |      $5000$      |    无    |
|    $5$     |      $5000$      |    无    |
|    $6$     |      $10^4$      |    A     |
|    $7$     |      $10^5$      |    A     |
|    $8$     |      $10^5$      |    B     |
|    $9$     |      $10^5$      |    无    |
|    $10$    |  $2\times 10^5$  |    A     |
|    $11$    |  $2\times 10^5$  |    B     |
|    $12$    |  $5\times 10^5$  |    无    |
|    $13$    |      $10^6$      |    A     |
|    $14$    |      $10^6$      |    B     |
|    $15$    |  $2\times 10^6$  |    无    |
|    $16$    |  $3\times 10^6$  |    无    |
|    $17$    |  $5\times 10^6$  |    A     |
|    $18$    |      $10^7$      |    A     |
|    $19$    |      $10^7$      |    B     |
|    $20$    | $1.3\times 10^7$ |    无    |
|    $21$    | $1.6\times 10^7$ |    无    |
|    $22$    |  $2\times 10^7$  |    A     |
|    $23$    |  $2\times 10^7$  |    B     |
|    $24$    |  $2\times 10^7$  |    无    |
|    $25$    |  $2\times 10^7$  |    无    |

特殊性质 A：保证所有 $g_i$ 相等。

特殊性质 B：保证只有 $g_n\neq 0$。

## 样例 #1

### 输入

```
2 0 1 1 1```

### 输出

```
11```

## 样例 #2

### 输入

```
9 0 1 0 663```

### 输出

```
422994```

## 样例 #3

### 输入

```
20 1 0 0 998244353```

### 输出

```
560706529```

## 样例 #4

### 输入

```
114514 17723 134 1045 233337```

### 输出

```
442762986```

# 题解

## 作者：Lyz09 (赞：10)

出题人题解。

说实话我是真没想到会有人打表做这一题。

## 暴力

按照题意模拟或直接输出 $g_1$ 可获得 $4\text{pts}$。

实现较优的暴力可以获得 $12\text{pts}$ 或以上。

## 特殊性质 A

所有的 $g_i$ 均相同，此时答案与具体位置无关，只与所有位置被计算次数总和有关。

考虑所有的 `range(a,b,c)` 总共包含多少个位置，答案形如若干个等差数列求和。

## 特殊性质 B

由于只有 $g_n\neq 0$， 考虑计算有多少个 `range(a,b,c)` 包含 $n$。

首先必须满足 $b=n+1$。此时我们只关注 `range(a,b,c)` 中的 $a,c$。具体来说，令 $x=n-a$，若 $c|n-a$，则 $n$ 在 `range(a,b,c)` 中，注意当 $x=0$ 时要特殊处理。

设 $d_x$ 表示 $x$ 的因子个数，则答案为 $g_{n}(n+\sum\limits_{i=1}^{n-1} d_{i})$。



## 正解

特殊性质 B 启发我们对每一个位置计算其被计算的次数。

但与特殊性质 B 有一点不同的是， `range(a,b,c)` 中的 $b$ 并不一定要是 $n+1$。

设 $f_x=n+\sum\limits_{i=1}^{x-1} d_{i}$，则答案为 $\sum\limits_{i=1}^{n} (n-i+1)g_i f_i$。

根据实现方法不同，可获得 $24\text{pts}\sim 100\text{pts}$，以下是一些不同的实现方法：

暴力求因子个数，时间复杂度 $O(n^2)$，可以获得 $24\text{pts}$。

对于每个数直接计算因子个数，时间复杂度 $O(n\sqrt n)$，可以获得 $36\text{pts}\sim 48\text{pts}$。

枚举倍数计算因子个数，时间复杂度 $O(n\ln n)$，可以获得 $76\text{pts}\sim 84\text{pts}$。

注意到一个数的因子个数函数是积性函数，因此可以使用欧拉筛求出因子个数，时间复杂度 $O(n)$，可以获得 $100\text{pts}$。

---

## 作者：gesong1234 (赞：9)

题目传送门：[P10886 【MX-S3-T2】「FeOI Round 1」Journey](https://www.luogu.com.cn/problem/P10886)。

# 思路

记 $f_i$ 表示 $i$ 的因数个数，可以用线性筛求出。

可以枚举 $g_i$ 将题目转化成式子有多少个被计算到。

我们发现如果 $a,b,c$ 能被计算到，当且仅当 $a\le i,b> i,c|(i-a)$，分情况讨论：
1. 当 $a<i$ 时，枚举 $a$ 求 $f_{i-a}$ 的和并将其记为 $sum$，那最后的贡献即为 $sum\times (n+1-i)$，但是现在求 $sum$ 是 $O(n)$ 的，因此需要使用前缀和优化。
2. 当 $a=i$ 时，$c$ 可以任取，$b$ 只要 $\ge i$ 即可，这部分的贡献为 $n\times (n+1-i)$。
   
综上，每一个 $g_i$ 的贡献就是 $g_i(sum\times (n+1-i)+n\times (n+1-i))$。

记得取模。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e7+10,mod=1e9+7;
int n,vis[N],pr[N],m,t,a[N],f[N],b[N];
inline void get(int n){
	f[1]=1;
	for (int i=2;i<=n;i++){
		if (!vis[i]) pr[++m]=i,a[i]=1,f[i]=2;
		for (int j=1;i*pr[j]<=n;j++){
			int x=i*pr[j];
			vis[x]=1;
			if (i%pr[j]==0){
				a[x]=a[i]+1,f[x]=f[i]/a[x]*(a[x]+1);
				break;
			} 
			else a[x]=1,f[x]=f[i]*2;
		}
	}
	for (int i=1;i<=n;i++) f[i]+=f[i-1];
}
inline int read(){
	char c=getchar();int f=1;int ans=0;
	while(c<48||c>57) (c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
main(){
	int n=read(),A=read(),B=read(),C=read();b[n]=read();
	get(n);
	for (int i=n-1;i>0;i--)
		b[i]=(1ll*A*b[i+1]%mod*b[i+1]%mod+1ll*B*b[i+1]%mod+C)%mod;
	int ans=0;
	for (int i=1;i<=n;i++){
		int sum=0;
	//	for (int j=1;j<i;j++) sum=(sum+f[i-j])%mod;
		sum=f[i-1];
		ans=(1ll*b[i]*(n+1-i)%mod*sum%mod+ans+1ll*b[i]*n%mod*(n+1-i)%mod)%mod;
	}
	cout <<ans;
	return 0;
}
```

---

## 作者：SunsetVoice (赞：6)

笑点解析：

![](https://cdn.luogu.com.cn/upload/image_hosting/f5xy0c6v.png)

大力推式子。由于 $n \le 2\times 10^7$ 卡掉了 $n \log n$，考虑算出每个 $g_i$ 的贡献。

先不考虑 $b$ 的贡献。

对于 $n=4$ 的情况，我们把 $i=3$ 的情况手推出来。有：

- $a=3$，此时 $c$ 可以乱取。总次数为 $4$。注意到 $a=i$ 时 $c$ 可以乱取，有 $n$ 种，总贡献为 $n$ 种。
- 其他。则若 $i$ 出现于 $\text{range(a,b,c)}$，则应该满足 $a < i-1,c\mid(i-a)$。总贡献为 $j\in \{0,i-1\}\sigma_{0}(j)$。

回来考虑 $b$。对于任意 $i$，都有 $b\in\{i+1,n+1\}$ 时有解。

$\sigma_{0}(j)$ 表示 $j$ 的因数个数。

做一遍欧拉筛，即可求出 $\sigma_{0}$ 的前缀和。

于是对于第 $i$ 位，其贡献为 $(n+bs0_{i-1})\times (n-i+1)\times g_i$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
const int mod = 1000000007;
int n,a,b,c,g;
int cnt,p[20000001] = {0},tu[20000001] = {0},s0[20000001] = {0};
bitset<20000001>pr;
void init(){
	s0[1] = 1;
	for(int i = 2;i<=n;i++){
		if(!pr[i]){
			p[++cnt] = i;
			tu[i] = 1;
			s0[i] = 2;
		}
		for(int j = 1;j<=cnt&&p[j]<=n/i;j++){
			const int nx = i*p[j];
			pr[nx] = 1;
			if(i%p[j]==0){
				tu[nx] = tu[i]+1;
				tu[nx]%=mod;
				s0[nx] = s0[i]/(tu[i]+1)*(tu[nx]+1);
				s0[nx]%=mod;
				break;
			}
			tu[nx] = 1;
			s0[nx] = s0[i]<<1%mod;
		}
	}
	for(int i = 2;i<=n;i++){
		s0[i]+=s0[i-1];
		s0[i]%=mod;
	}
	return;
}
signed main() {
	cin>>n>>a>>b>>c>>g;
	init();
	int ans = 0;
	for(int i = n;i>=1;i--){
		ans+=(n%mod*(n-i+1)%mod+s0[i-1]%mod*(n-i+1)%mod)*g%mod;
		g = g*g%mod*a%mod+g*b%mod+c;
		g%=mod;
		ans%=mod;
	}
	cout<<ans<<endl;
	return 0;
}
```

致谢：@ZeroOf149 将博主从错误的柿子种救了出来。

---

## 作者：suzhikz (赞：3)

我去，我怎么推了个正确的柿子却觉得是错的。

首先转换题目的柿子。套路的把每个 $g_i$ 拆出来，看他会被计算几次。

显然答案是 $\sum_{l=1}^{n}(n-l+1)\times g_l\sum_{c=1}^{n}(\lfloor\frac{l-1}{c}\rfloor+1)$ 。

这样子就优美多了，我们考虑直接枚举 $l$ ，然后考虑如何快速求后面那玩意。

设 $a_l=\sum_{c=1}^{n}(\lfloor\frac{l-1}{c}\rfloor+1)$ ，然后差分一下该数组，想想对于每个 $c$，什么情况下 $\lfloor\frac{l-1}{c}\rfloor$ 和 $\lfloor\frac{l}{c}\rfloor$ 不同，显然此时 $l$ 是 $c$ 的倍数。所以我们用欧拉筛快速求下因数个数做前缀和即可。


```cpp
read(n);read(a);read(b);read(c);read(g[n]);
	for(int i=n-1;i>=1;i--)g[i]=a*g[i+1]%mod*g[i+1]%mod+b*g[i+1]%mod+c,g[i]%=mod;
	summ[1]=1;cnt[1]=1;
	for(int i=2;i<=n;i++){
		if(summ[i]==0){
			summ[i]=2;cnt[i]=1;
			prim[++tot]=i;
		}
		for(int j=1;j<=tot&&1ll*i*prim[j]<=n;j++){
			if(i%prim[j]==0){
				cnt[prim[j]*i]=cnt[i]+1;summ[prim[j]*i]=summ[i]/(cnt[i]+1)*(cnt[i]+2);
				break;
			}
			cnt[prim[j]*i]=1;summ[prim[j]*i]=summ[i]*2;
		}
	}
	for(int i=1;i<=n;i++)summ[i]+=summ[i-1];
	for(int i=1;i<=n;i++)summ[i]+=n;
	summ[0]=n;
	ll ans=0;
	for(int i=1;i<=n;i++){
//		cout<<summ[i]<<endl;
		ans=(ans+g[i]*summ[i-1]%mod*(n-i+1)%mod)%mod;
	}
	cout<<ans;
```

---

## 作者：luxiaomao (赞：2)

## [P10886](https://www.luogu.com.cn/problem/P10886) 小清新数学题

赛时不知道因子数量可以 $O(n)$ 筛所以只拿了八十分嘤嘤嘤。

## Problem

求：

$$
\sum\limits_{a=1}^n
\sum\limits_{b=a+1}^{n+1}
\sum\limits_{c=1}^n
\sum\limits_{i\in \mathrm{range}(a,b,c)}
g_i
$$

其中 $i\in\mathrm{range}(a,b,c)$ 是指 $i=a+kc$ 且满足 $a \le i < b$。

## Solution

形式化地，我们记 $cnt_i$ 为答案中出现了几个 $g_i$。不难看出，题面要求我们 $O(n)$ 求出 $cnt_i$。

对于一个点 $i$，它的右区间端点在 $[i+1,n+1]$ 之间，有 $(n-i+1)$ 种可能，这个比较好算。

那左区间端点有几种可能呢？

我们发现，如果左区间端点为 $A$，要跳到点 $B$，他们之间的距离为 $(B-A)$，跳的方式数量即为 $(B-A)$ 的因子个数。记因子数量为 $d_i$。

那么对于一个点 $i$，左区间端点的可能数量就是 $\sum\limits_{j=0}^{i-1}d_j$。

那么 $cnt_i$ 就等于左端点的可能数量乘上右端点的可能数量，具体请看代码。

先 $O(n)$ 筛出 $d$ 数组，再把 $d$ 数组前缀和一遍，依然可以优化到 $O(n)$，可以通过此题。

## Code

大肠代码，笔者用 C++17 极限 $1.46s$ 卡过。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 20000005
using namespace std;

int mod = 1000000007;
int n,A,B,C,g[N],ans;
int p[N],tot,d[N],cnt[N];

signed main()
{
	scanf("%lld%lld%lld%lld",&n,&A,&B,&C),scanf("%lld",&g[n]);
	for(int i = n-1;i;i--)g[i] = (A*g[i+1]%mod*g[i+1] + B*g[i+1]%mod + C)%mod;
	d[0] = n,d[1] = 1;
	for(int i = 2;i <= n;i++)
	{
		if(!d[i])d[i] = 2,p[++tot] = i,cnt[i] = 1;
		for(int j = 1;j <= tot && i*p[j] <= n;j++)
		{
			if(i%p[j] == 0)
			{
				d[i*p[j]] = d[i] / (cnt[i]+1) * (cnt[i]+2);
				cnt[i*p[j]] = cnt[i] + 1;
				break;
			}
			else
			{
				d[i*p[j]] = d[i] * d[p[j]];
				cnt[i*p[j]] = 1;
			}
		}
	}
	for(int i = 1;i <= n;i++)d[i] += d[i-1];
	for(int i = 1;i <= n;i++)(ans += d[i-1]*(n-i+1)%mod*g[i]%mod)%=mod;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：luanyanjia (赞：2)

我们肯定是要先求出来一个位置被加的次数，然后和权值乘一下就行。

对于一个位置 $i$，右端点 $b$ 肯定是随便选，一共 $n-i+1$ 种情况。再是对于每一种步长 $c$，左端点 $a$ 都有 $\left\lceil\dfrac{i}{c}\right\rceil$ 种取值，暴力计算，时间复杂度 $O(n^2)$。（[提交记录](https://www.luogu.com.cn/record/173251537)）

考虑如何优化，对于第 $i$ 个位置，设 $s_i = \sum\limits_{c=1}^{n}{ \left\lceil\dfrac{i}{c}\right\rceil} $，那对于一个 $c$，如果 $\left\lceil\dfrac{i}{c}\right\rceil > \left\lceil\dfrac{i-1}{c}\right\rceil$，那么 $i-1$ 一定是 $c$ 的倍数。所以，$i-1$ 有几个因数，$s_{i}$ 就会变大多少，即 $s_i = s_{i-1} + d_{i-1}$。直接欧拉筛即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void rd(){}
template<typename T,typename ...U>
inline void rd(T &x,U &...args){
	char ch=getchar();
	T f=1;x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x*=f;rd(args...);
}
const int N=2e7+5,mod=1e9+7;
int n,a,b,c,gn;
int t[N],ans;
int pri[N],cnt,d[N],num[N];
bool vis[N];
inline void Euler(){
	d[1]=num[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			pri[++cnt]=i;
			d[i]=2,num[i]=1;
		}
		for(int j=1;j<=cnt&&pri[j]*i<=n;j++){
			vis[pri[j]*i]=1;
			if(i%pri[j]==0){
				num[i*pri[j]]=num[i]+1;
				d[i*pri[j]]=d[i]/num[i*pri[j]]*(num[i*pri[j]]+1);
				break;
			}
			num[i*pri[j]]=1;
			d[i*pri[j]]=d[i]*2;
		}
	}
}
signed main(){
	rd(n,a,b,c,gn);
	t[1]=n;Euler();
	for(int i=2;i<=n;i++)t[i]=t[i-1]+d[i-1];
	ans=1ll*gn*t[n]%mod;
	for(int i=n-1;i>=1;i--){
		gn=(1ll*a*gn%mod*gn%mod+1ll*b*gn%mod+c)%mod;
		(ans+=1ll*gn*t[i]%mod*(n-i+1)%mod)%=mod;
	}printf("%d\n",ans);
	return 0;
}

```

---

## 作者：_sin_ (赞：2)

看题目有点像根号分治，但是观察数据范围，得出算法时间复杂度应该为 $O(n)$。显然不是根号分治。

再观察 $g$ 的生成方式，比较一般，所以做法跟 $g$ 的生成方式无关。

考虑计算 $g_i$ 会对答案产生多少次贡献。当 $a<i$ 时，对答案的贡献为 $(n-i+1)\lfloor \frac{i-1}{c} \rfloor g_{i}$；当 $a=i$ 时，对答案的贡献为 $(n-i+1)g_i$；当 $a>i$ 时，对答案没有贡献。所以答案为 $\sum_{c=1}^{n}\sum_{i=1}^{n}(n-i+1)(\lfloor \frac{i-1}{c} \rfloor +1)g_i$。这样就有一个 $O(n^2)$ 的做法，可以拿 $24$ 分。

考虑怎么优化，令 $t=\lfloor \frac{i-1}{c} \rfloor$，枚然后举 $c,t$，用类似于整除分块的思想，用差分进行区间修改。由于要要求 $ct\le n$，枚举的代码是调和级数，所以这个解法是 $O(n\ln n)$ 的。核心代码如下：
```cpp
for(int c=1;c<=n;c++)for(int t=1;c*t<=n;t++){
	b[c*t+1]+=t;if(c*(t+1)+1<=n)b[c*(t+1)+1]-=t;
}
```
这样不好优化，但是我们可以观察到这段代码和下面这段代码是等价的：
```cpp
for(int c=1;c<=n;c++)for(int t=1;c*t<=n;t++){
	b[c*t+1]++;
}
```
~~至于为什么是等价的，留作习题答案略，读者自证不难。~~\
其实就是把 $t$ 分成多次计算贡献。

然后上面的代码得出的 $b_i$ 就是 $i-1$ 因数个数，可以线性筛 $O(n)$ 处理。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
#define reg register
#define fmod(x) ((x)>mod?(x)-mod:(x))
using namespace std;

il void fread(ll &X){ll A=1;X=0;char C=getchar();while(!isdigit(C)&&C!='-')C=getchar();if(C=='-')A=-1,C=getchar();while(isdigit(C))X=(X<<1)+(X<<3)+(C^48),C=getchar();X*=A;}
il void fout(ll X){if(X<0)putchar('-'),X=-X;if(!X){putchar('0'),putchar(' ');return;}char C[25]{};int Len=0;while(X)C[++Len]=X%10+'0',X/=10;for(;Len;--Len)putchar(C[Len]);putchar(' ');}

const ll mod = 1e9+7,N=2e7+5;
ll n, A, B, C, g[N],ans=0;
ll sg,sgi,tmp,b[N],cnt=0;
bitset<N>v;int c[N],d[N],pri[N];

int main(){
	fread(n),fread(A),fread(B),fread(C),fread(g[n]);
	for(reg int i=n-1;i>=1;i--)g[i]=fmod(A*g[i+1]%mod*g[i+1]%mod+B*g[i+1]%mod+C);
	d[1]=1;for(reg ll i=2;i<=n;i++){
        if(!v[i]) pri[++cnt]=i,d[i]=2,c[i]=1;
        for(reg ll j=1;j<=cnt&&i*pri[j]<=n;j++){
            v[i*pri[j]]=1;if(i%pri[j]==0){
                c[i*pri[j]]=c[i]+1;d[i*pri[j]]=d[i]/(c[i]+1)*(c[i]+2);break;
            }d[i*pri[j]]=d[i]*2;c[i*pri[j]]=1;
        }
    }
    for(reg int i=1;i<=n;i++){
		sg=fmod(sg+g[i]),sgi=fmod(sgi+g[i]*i%mod);
		b[i]=d[i-1];b[i]=fmod(b[i]+b[i-1]);
		tmp=(n-i+1)*g[i]%mod;
		ans=fmod(ans+tmp*b[i]%mod);
	}ans=fmod(ans+n*(fmod(n*sg%mod+sg)-sgi+mod)%mod);fout(ans);
	return 0;
}
```

---

## 作者：xuan_gong_dong (赞：2)

## 题面
[P10886 【MX-S3-T2】「FeOI Round 1」Journey](https://www.luogu.com.cn/problem/P10886)
## 分析

注意 $n\le 2 \times 10^7$。

对于一个序列中的数 $i$，以 $i$ 为起点，$i$ 被计算的次数为 $(n-i+1) \times n$，以 $k$ 为起点（$1 \le k \lt i$），$i$ 被计算的总次数为 $\sum_{i=1}^n \frac{n}{i}$。

该式子可以用线性筛预处理出来，在查询的时候 $O(1)$ 得到答案。

时间复杂度为 $O(n)$，且为小常数，可以通过。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
int n,A,B,C;
const int p=1e9+7;
int g[20000010];
int ans=0;
int prime[20000010],pn,f[20000010],gg[20000010];
bool vis[20000010];
void sieve(int x)
{
	for(int i = 2;i <= x;++ i)
	{
		if(!vis[i]) prime[++pn] = i,f[i] = 2,gg[i] = 1;
		for(int j = 1;j <= pn && i * prime[j] <= x;++ j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				gg[i * prime[j]] = gg[i] + 1;
				f[i * prime[j]] = f[i] / (gg[i]+1) * (gg[i]+2);
				break;
			}
			gg[i * prime[j]] = 1;
			f[i * prime[j]] = f[i] * 2;
		}
	}
	f[1]=1;
	for(int i=1;i<=x;i++)
	{
		f[i]+=f[i-1];
//		printf("%lld %lld\n",i,f[i]);
	 } 
}
int num(int x)
{
	int res=f[x];
//	printf("%lld ",res);
	int anss=res*(n-x);
	anss=anss%p;
	anss+=((n-x)*n)%p;
	return anss%p;
}
signed main() {
	scanf("%lld%lld%lld%lld",&n,&A,&B,&C);
	sieve(n);
	scanf("%lld",&g[n]);
	g[n]=g[n]%p;
	ans+=g[n]*num(n-1);
	ans=ans%p;
//	printf("QwQ");
	for(int i=n-1; i>=1; i--) {
		g[i]=(A*g[i+1]%p*g[i+1]%p+B*g[i+1]%p)%p+C;
		g[i]%=p;
		ans+=g[i]*(num(i-1));
		ans=ans%p;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：佬头 (赞：2)

## Description
给定一个长为 $n$ 的序列 $g$（下标从 $1$ 开始），求出下列式子的值，答案对 $10^9+7$ 取模。
$$
\sum_{a=1}^n\sum_{b=a+1}^{n+1}\sum_{c=1}^n\sum\limits_{i\in \mathrm{range}(a,b,c)}g_i
$$

## Solution
设 $f(x)$ 表示 $x$ 的因数个数，然后推一下式子：
$$
\begin{aligned}\sum_{a=1}^n\sum_{b=a+1}^{n+1}\sum_{c=1}^n\sum\limits_{i\in \mathrm{range}(a,b,c)}g_i

&=\sum_{a=1}^n\sum_{b=a+1}^{n+1}\sum_{c=1}^n\sum_{i=0}^{\left\lfloor\frac{b-a-1}c\right\rfloor}g_{a+i\times c}

\\&=\sum_{a=1}^n\sum_{b=a+1}^{n+1}\sum_{c=1}^n\sum_{i=a}^{b-1}g_i\times[c\mid(i-a)]

\\&=\sum_{a=1}^n\sum_{b=a+1}^{n+1}\left(g_a\times n+\sum_{i=a+1}^{b-1}g_i\times f(i-a)\right)

\\&=\sum_{a=1}^n\left(g_a\times n\times(n-a+1)+\sum_{b=a+1}^{n}\sum_{i=a+1}^{b}g_i\times f(i-a)\right)

\\&=\sum_{a=1}^n\left(g_a\times n\times(n-a+1)+\sum_{i=a+1}^ng_i\times f(i-a)\times(n-i+1)\right)

\\&=\sum_{a=1}^ng_a\times n\times(n-a+1)+\sum_{a=1}^n\sum_{i=a+1}^ng_i\times f(i-a)\times(n-i+1)

\\&=\sum_{i=1}^{n}g_i\times n\times(n-i+1)+\sum_{i=2}^{n}g_{i}\times(n-i+1)\times\sum_{j=1}^{i-1}f(j)

\\&=\sum_{i=1}^{n}g_i\times(n-i+1)\times\left(\sum_{j=1}^{i-1}f(j)+n\right)
\end{aligned}$$
这里边 $g,f$ 需要预处理一下：序列 $g$ 可以用 $g_n,g_i\equiv Ag_{i+1}^2+Bg_{i+1}+C \pmod {10^9 + 7}$ 倒推；函数 $f$ 可以通过**欧拉筛**实现，然后求个**前缀和**。

简单讲一下欧拉筛求因数个数：首先一个正整数 $x$ 可以表示为 $x=\prod_{i=1}^{k}p_i^{a_i}~(p_i\in\mathbb P,a_i\in\mathbb N^+)$，其中 $\mathbb P$ 是质数集，而 $f(x)=\prod_{i=1}^{k}(a_i+1)$。当我们用 $x~(x\notin \mathbb P)$ 的最小质因子 $p_1$ 将 $x$ 筛除时，枚举到的数 $i=x\div p_1$，设 $num(x)$ 表示 $x$ 的最小质因子的次数：
- 当 $p_1\mid i$ 时，$num(x)=num(i)+1,f(x)=f(i)\times\frac{num(x)+1}{num(i)+1}$；
- 当 $p_1\nmid i$ 时，$num(x)=2,f(x)=f(i)\times2$。

运算的时候要开 `long long`，时间复杂度为 $\mathcal O(n)$。

## Code
```cpp
#include <iostream>
#define ll long long
using namespace std;
const int N = 20000007, mod = 1000000007;
int pri[N], num[N], p, facts[N], n, a, b, c, g[N], d, ans;
bool is_pri[N];
int read(){
	int x = 0;
	char a = getchar();
	while(a < '0' || '9' < a) a = getchar();
	while('0' <= a && a <= '9') x = (x << 1) + (x << 3) + (a ^ 48), a = getchar();
	return x;
}
void write(int x){
	if(x > 9) write(x / 10);
	putchar(x % 10 | 48);
}
void prime(){
	for(int i = 2; i <= n; ++ i){
		if(!is_pri[i]) pri[++ p] = i, facts[i] = 2, num[i] = 2;
		for(int j = 1; j <= p && i * pri[j] <= n; ++ j){
			is_pri[i * pri[j]] = 1;
			if(i % pri[j] == 0){
				num[i * pri[j]] = num[i] + 1;
				facts[i * pri[j]] = facts[i] / num[i] * (num[i] + 1);
				break;
			}
			num[i * pri[j]] = 2;
			facts[i * pri[j]] = facts[i] << 1;
		}
	}
	facts[1] = 1;
}
int main(){
	d = n = read(), a = read(), b = read(), c = read(), g[n] = read();
	prime();
	for(int i = n - 1; i >= 1; -- i) g[i] = (((ll)a * g[i + 1] + b) % mod * g[i + 1] % mod + c) % mod;
	for(int i = 1; i <= n; ++ i) d = (d + facts[i - 1]) % mod, ans = ((ll)d * g[i] % mod * (n - i + 1) + ans) % mod;
	write(ans);
	return 0;
}
```

---

## 作者：block_in_mc (赞：1)

## 题目大意

定义 $\mathrm{range}(a,b,c)=[a,a+c,a+2c,\cdots,a+kc]$，其中 $k$ 是最大的满足 $a+kc<b$ 的非负整数 $k$。求出下列式子的值，对 $10^9+7$ 取模：

$$\sum_{a=1}^{n}\sum_{b=a+1}^{n+1}\sum_{c=1}^{n}\sum\limits_{i\in \mathrm{range}(a,b,c)} g_i$$

## 解题思路

先考虑给定 $a,b$ 时，$\sum_{c=1}^{n}\sum\limits_{i\in \mathrm{range}(a,b,c)} g_i$ 的结果。不难发现，对于整数 $a\le i\le b$：

* 当 $i=a$ 时，对于每一个 $c$，$g_i$ 都会被累加，共计 $n$ 次；
* 当 $i\not=a$ 时，对于每一个 $i-a$ 的因数 $c$，$g_i$ 都会被累加，共计 $cnt_{i-l}$ 次，其中 $cnt_k$ 代表 $k$ 的因数数量。

对于每一个整数 $1\le i\le n$，考虑计算 $g_i$ 的贡献：

* 先考虑 $a=i$ 的区间，共有 $n-i+1$ 个（$b$ 可以取到 $n+1$），贡献为 $n(n-i+1)g_i$；
* 考虑 $a<i<b$ 的区间，由上面的推导可以得到，当 $a=j$ 时（$1\le j<i$），结果为 $cnt_{i-j}$。由于结果与 $b$ 无关，对于每一个可能的 $a$，$b$ 都有 $(n-i+1)$ 种结果相等的可能，因此每一个 $b$ 的结果之和为 $cnt_{i-1}+cnt_{i-2}+\cdots+cnt_{1}=sum_{i-1}$，其中 $sum$ 为 $cnt$ 的前缀和数组。总的结果为 $sum_{i-1}(n-i+1)g_i$。

最终的结果为 $\sum\limits_{i=1}^n(n+sum_{i-1})(n-i+1)g_i$。$cnt$ 数组可通过线性筛得到。总时间复杂度 $O(n)$。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 20000010, P = 1000000007;
ll n, a, b, c, g, ans, cnt[N], num[N];
bool mk[N];
vector<int> ls;
void pre() {
    cnt[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!mk[i]) {
            ls.push_back(i);
            cnt[i] = 2, num[i] = 1;
        }
        for (int j : ls) {
            if (i * j > n) break;
            mk[i * j] = true;
            if (i % j == 0) {
                num[i * j] = num[i] + 1;
                cnt[i * j] = cnt[i] / num[i * j] * (num[i * j] + 1);
                break;
            }
            num[i * j] = 1, cnt[i * j] = cnt[i] * 2;
        }
    }
    for (int i = 1; i <= n; i++)
        cnt[i] += cnt[i - 1];
}
int main() {
    scanf("%d%d%d%d%d", &n, &a, &b, &c, &g);
    pre();
    for (ll i = n; i >= 1; i--) {
        if (i != n) g = ((a * (g * g % P) % P) + (b * g % P) + c) % P;
        ans = (ans + (cnt[i - 1] * (n - i + 1) % P) * g) % P;
        ans = (ans + (n * (n - i + 1) % P) * g) % P;
    }
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：xzf888 (赞：1)

考虑对于每个 $i$，计算有多少对 $\langle a,b,c\rangle$ 满足 $i\in \operatorname{range}(a,b,c)$，记 $\operatorname{d}(n)$ 表示 $n$ 的约数个数，则：

$$
\begin{aligned}
& \sum_{a=1}^{n}\sum_{b=a+1}^{n+1}\sum_{c=1}^{n}\sum_{i\in \operatorname{range}(a,b,c)} g_i\\
=&\sum_{i=1}^{n}g_i\sum_{a=1}^{n}\sum_{b=a+1}^{n+1}\sum_{c=1}^{n}[i\in \operatorname{range}(a,b,c)]\\
=&\sum_{i=1}^{n}g_i\sum_{i<b\leq n+1}\sum_{1\leq a \leq i}\sum_{c=1}^{n}[a\equiv i \pmod c]\\
=&\sum_{i=1}^{n}g_i(\sum_{i<b\leq n+1}1)\sum_{1\leq a \leq i}\sum_{c=1}^{n}[a-i\equiv 0 \pmod c]\\
=&\sum_{i=1}^{n}g_i(n+1-i)(n+\sum_{a=1}^{i-1}\operatorname{d}(a-i))\\
=&\sum_{i=1}^{n}g_i(n-i+1)(n+\sum_{j=1}^{i-1}\operatorname{d}(j))
\end{aligned}
$$

线性筛预处理 $\sum_{j=1}^{i}\operatorname{d}(j)$ 即可，复杂度 $\mathcal{O}(n)$。

Code:
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=1000000007;
int a[20000005],b[1000005],d[20000005],g[20000005];
char cnt[20000005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,a_,b_,c_;
	cin>>n>>a_>>b_>>c_>>g[n];
	for(int i=n-1;i>=1;i--){
		g[i]=(1ll*a_*g[i+1]%mod*g[i+1]+1ll*b_*g[i+1]+c_)%mod;
	}
	d[1]=1;
	for(int i=2,tot=0;i<=n;i++){
		if(a[i]==0){
			b[++tot]=i;
			d[i]=1;
			cnt[i]=1;
		}
		int val=1ll*d[i]*(cnt[i]+1)%mod;
		for(int j=1;j<=tot;j++){
			if(1ll*i*b[j]>n) break;
			a[i*b[j]]=1;
			if(i%b[j]==0){
				d[i*b[j]]=d[i];
				cnt[i*b[j]]=cnt[i]+1;
				break;
			}
			d[i*b[j]]=val;
			cnt[i*b[j]]=1;
		}
		d[i]=val;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		d[i]+=d[i-1];
		ans=(ans+1ll*g[i]*(n-i+1)%mod*(d[i-1]+n))%mod;
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：1)

不难发现一个下标 $i$ 被一个 $c$ 计算到的次数是  $\left\lceil\dfrac{i}{c}\right\rceil$ 而被一个 $b$ 计算到的次数是 $n-i+1$，所以我们要求解的就是 $\sum_{i=1}^n g_i \times (n-i+1) \times \sum_{c=1}^{n} \left\lceil\dfrac{i}{c}\right\rceil$。

注意到 $\left\lceil\dfrac{i+1}{c}\right\rceil = \left\lceil\dfrac{i}{c}\right\rceil + 1$ 当且仅当 $i$ 是 $c$ 的倍数，所以实际上 $f(i) = \sum_{c=1}^n \left\lceil\dfrac{i}{c}\right\rceil$ 是因数个数和函数的前缀和，而因数个数和函数是一个积性函数，直接线性筛即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int mod = 1e9+7;
const int maxn = 2e7+1;
int g[maxn],n,A,B,C;
int pri[maxn],st;
int t[maxn],F[maxn],nP[maxn];
void init(){
    F[1]=1;
    for(int i=2;i<=n;i++){
        if(nP[i]==0){
            F[i]=2;
            pri[++st]=i;
            t[i]=i;
        }
        for(int j=1;j<=st;j++){
        	int x=pri[j];
            if(x*i>n) break;
            //x*i 的最小质因子为 x
            nP[x*i]=x;
            if(nP[i]==x||i==x) t[x*i]=t[i]*x;//求出每个数最小因子的幂次的值
            else t[x*i]=x;
            if(x*i==t[x*i]){
            	F[x*i]=F[i]+1;
            }else{
                //此时 t[x*i] 与 (x*i)/t[x*i] 互质
                F[x*i]=F[t[x*i]]*F[(x*i)/t[x*i]];
            }
            if(i%pri[j]==0) break;
        }
    }
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int ans=0;
	cin>>n>>A>>B>>C;
	cin>>g[n];
	for(int i=n-1;i>=1;i--) g[i]=(1ll*g[i+1]*g[i+1]%mod*A%mod+1ll*g[i+1]*B%mod+1ll*C)%mod;
	init();
	int f=n;
	for(int i=1;i<=n;i++){
		//cout<<i<<' '<<g[i]<<' '<<F[i]<<"\n";
		ans=(1ll*ans+1ll*f*g[i]%mod*(n-i+1)%mod)%mod;
		f=(1ll*f+1ll*F[i])%mod;
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Mr_RoastFish (赞：1)

~~竟跪倒在线性筛因数个数上，悲。~~

这道题可以先徒手试两个看看找规律，我先盯上的是样例二（保证 $g[i]$ 相等不就是说结果是总计个数乘上这个值么）。小列两组 `range` 基本上就能出规律。![](https://cdn.luogu.com.cn/upload/image_hosting/fxre0obb.png)
不难发现，单组内（$a$、$c$ 相同算一组）除去最小数 $a$ 有 $b-a$ 个外，其余各数的个数与**差值的因数个数**相同。这也好理解，你能拆多少个 $c$ 就能加多少次。由于一个排列中数字恒定，差值不变，所以 $a$ 变化也只会带来 `tot` 序列的滚动。结果如下图（写文字不如看图清楚）。![](https://cdn.luogu.com.cn/upload/image_hosting/52269okf.png)
这里展示了 $range(1,b,c)$ 与 $range(2,b,c)$ 的情况。（最下排是差值，上面是每个 `range` 带来的数值变化，范围同题干）。再把差值的关系带入原数列，答案就呼之欲出了。![](https://cdn.luogu.com.cn/upload/image_hosting/kgjs01lh.png)
这里方框着的是数字，下方是个数，最右侧是说有多少个对应的差值序列（同图二）。计算个数是要考虑到他是最小值的情况，即个数栏的第一行。第二行的 `temp` 是因数个数前缀和。

到这里思路已经明晰，可以敲代码了。注意数据范围要求在线性时间复杂度内完成问题，只能用线性筛求因数个数（因数个数是个积性函数，可以用筛法）。不会的[看这里](https://www.cnblogs.com/littlehb/p/16650121.html)。

最后奉上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e7+5,MOD=1e9+7;
long long g[MAXN],ans,temp,d[MAXN],num[MAXN];
vector<int> prime;
bool vis[MAXN];
void pre(){
	d[1]=1;
	for(int i=2;i<MAXN;i++){
		if(!vis[i]){
			d[i]=2;num[i]=1;
			prime.push_back(i);
		}
		for(int j:prime){
			if(i*1LL*j>=MAXN)	break;
			vis[i*1LL*j]=true;
			if(i%j==0){
				num[i*j]=num[i]+1;
				d[i*j]=d[i]/num[i*j]*(num[i*j]+1);
				break;
			}
			d[i*j]=d[i]*2;num[i*j]=1;
		}
	}
}
int main(){
	long long n,A,B,C;
	read(n),read(A),read(B),read(C);read(g[n]);//fast_cin
	for(int i=n-1;i>=1;i--)	g[i]=(A*(g[i+1]*g[i+1]%MOD)+B*g[i+1]+C)%MOD;
	ans=n*n%MOD*g[1]%MOD;
	pre();
	for(int i=1;i<n;i++){
		temp=(temp+d[i])%MOD;//cout<<cnt[i]<<' '<<sqrt(1)<<' ';
		ans=(ans+(n*(n-i)+(n-i)*temp)%MOD*g[i+1]%MOD)%MOD;
	}
	write(ans);//fast_cout
	return 0;
}

```

---

## 作者：lbmzxhb (赞：1)

[题目传送门](/problem/P10886)

## 思路：

（似乎做法跟 std 不太一样）

很一眼的推式子题，所以直接开始推式子：

$$\sum_{a=1}^{n}\sum_{b=a+1}^{n+1}\sum_{c=1}^{n}\sum_{i\in \mathrm{range}(a,b,c)} g_i=\sum_{a=1}^n\sum_{b=a+1}^{n+1}\sum_{c=1}^n\sum_{k=0}^{\lfloor\frac{b-a-1}c\rfloor+1}g_{a+kc}$$

容易发现这样不好往下推，于是考虑只枚举 $c,k,a$，则 $b$ 的范围就能确定了：

$$\begin{aligned}\sum_{c=1}^n\sum_{k=0}^{\lfloor\frac nc\rfloor}\sum_{a=1}^{n-kc}\sum_{b=a+kc+1}^{n+1}g_{a+kc}&=\sum_{c=1}^n\sum_{k=0}^{\lfloor\frac nc\rfloor}\sum_{a=1}^{n-kc}g_{a+kc}\sum_{b=a+kc+1}^{n+1}1\\&=\sum_{c=1}^n\sum_{k=0}^{\lfloor\frac nc\rfloor}\sum_{a=1}^{n-kc}(n-a-kc+1)g_{a+kc}\\&=\sum_{c=1}^n\sum_{k=0}^{\lfloor\frac nc\rfloor}\sum_{a=kc+1}^n(n-a+1)g_a\end{aligned}$$

令 $f_i=\sum\limits_{j=i}^n(n-j+1)g_j$，则显然 $f$ 数组能 $\mathcal O(n)$ 求出。将式子中第三个求和用 $f_{kc+1}$ 替代：

$$\sum_{c=1}^n\sum_{k=0}^{\lfloor\frac nc\rfloor}f_{kc+1}$$

则 $f_{i+1}$ 被统计到了 $d(i)$ 次，特别地，$f_1$ 被统计到了 $n$ 次（因为对于所有的 $c$， $f_1$ 都有被统计）。

而线性筛能 $\mathcal O(n)$ 筛出来 $1\le i\le n$ 的 $d(i)$，所以总时间复杂度 $\mathcal O(n)$。

## 代码：

代码中的 $f_i$ 为上文的 $d_i$，$g_i$ 为上文的 $f_i$，注意区分一下。

```cpp
#include <bits/stdc++.h>
#define int long long
#define _ 0
using namespace std;

template<int P>
struct modint {
private:
	template<typename T> 
	inline static T Down(T x) {return x >= P ? x - P : x;}
public:
	unsigned int v;
	modint(unsigned int v=0) : v(v) {}
	friend ostream&operator<<(ostream&o,modint x) {return o<<x.v;}
	friend istream&operator>>(istream&i,modint&x) {int t; return i>>t,x.v=Down(t%P+P),i;}
	friend modint operator+(modint a, modint b) {return Down(a.v+b.v);}
	friend modint operator-(modint a, modint b) {return Down(a.v-b.v+P);}
	friend modint operator*(modint a, modint b) {return 1ull*a.v*b.v%P;}
	friend modint operator/(modint a, modint b) {return a*~b;}
	friend modint operator^(modint a, int p) {modint r=1; for(; p; p >>= 1, a = a * a) if (p & 1) r = r * a; return r;}
	friend modint operator~(modint a) {return a^(P-2);}
	friend modint operator-(modint a) {return Down(P-a.v);}
	friend modint&operator+=(modint&a, modint b) {return a=a+b;}
	friend modint&operator-=(modint&a, modint b) {return a=a-b;}
	friend modint&operator*=(modint&a, modint b) {return a=a*b;}
	friend modint&operator/=(modint&a, modint b) {return a=a/b;}
	friend modint&operator^=(modint&a, int b) {return a=a^b;}
	friend modint&operator++(modint&a) {return a+=1;}
	friend modint operator++(modint&a, signed) {modint x=a; return ++a,x;}
	friend modint&operator--(modint&a) {return a-=1;}
	friend modint operator--(modint&a, signed) {modint x=a; return --a,x;}
	friend bool operator==(modint a, modint b) {return a.v==b.v;}
	friend bool operator!=(modint a, modint b) {return a.v!=b.v;}
};
typedef modint<(int)1e9 + 7> mint;
const int N(2e7 + 5);
int n, A, B, C;
mint g[N];
int f[N], gg[N], primes[(int)1.5e6 + 5], cnt;
bitset<N> nis;
void work() {
	cin >> n >> A >> B >> C;
	cin >> g[n];
	for (int i = n - 1; i; i--) g[i] = g[i + 1] * g[i + 1] * A + g[i + 1] * B + C;
	for (int i = n - 1; i; i--) g[i] = g[i + 1] + g[i] * (n - i + 1);
	mint ans;
	nis[1] = f[1] = gg[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!nis[i]) primes[++cnt] = i, f[i] = 2, gg[i] = 1;
		for (int j = 1, d = 1; j <= cnt && (d = i * primes[j]) <= n; j++) {
			nis[d] = 1, f[d] = f[i] * 2, gg[d] = 1;
			if (!(i % primes[j])) {gg[d] = gg[i] + 1, f[d] = f[i] / gg[d] * (gg[d] + 1); break;}
		}
	}
	f[0] = n;
	for (int i = 1; i <= n; i++) ans += g[i] * f[i - 1];
	cout << ans;
}

signed main() {
	cin.tie(0), cout.tie(0)->sync_with_stdio(0);
	int T(1);
//	cin >> T;
	while (T--) work();
	return ~~(0^_^0);
}
```

---

## 作者：gghack_Nythix (赞：1)

## 前言：

[题目传送门](https://www.luogu.com.cn/problem/P10886)

## 分析：

考虑大力推式子：

$$
\sum\limits_{a=1}^{n}\sum\limits_{b=a+1}^{n+1}\sum\limits_{c=1}^{n}\sum\limits_{i\in \mathrm{range}(a,b,c)} g_i
$$

$$
=\sum\limits_{i=1}^{n}g_i\sum\limits_{a=1}^{n}\sum\limits_{b=a+1}^{n+1}\sum\limits_{c=1}^{n}i\in \mathrm{range}(a,b,c)
$$

$$
=\sum\limits_{i=1}^{n}(n-i+1)g_i\sum\limits_{a=1}^{n}\sum\limits_{c=1}^{n}i\in \mathrm{range}(a,b,c)
$$

推到这里感觉好像有点问题，那么考虑写出函数原形：

$$
a+kc=i
$$
即：
$$
kc=i-a
$$

那么这时，$c \mid (i-a)$，即 $c$ 的个数为 $d_{i-a}$ 个，其中 $d_{x}$ 表示 $x$ 的因子个数。特别的，当 $i-a=0$ 时，$c$ 的取值任意。

然后继续往下推：

$$
\sum\limits_{i=1}^{n}(n-i+1)g_i\sum\limits_{a=1}^{n}\sum\limits_{c=1}^{n}i\in \mathrm{range}(a,b,c)
$$

$$
=\sum\limits_{i=1}^{n}(n-i+1)g_i[\sum\limits_{a=1}^
{i-1}d_{i-a}+n]
$$

然后就没了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod = 1e9 + 7;
int n,A,B,C,g[20000005];
int d[20000005],M[20000005],sd[20000005];
int pri[20000005],cnt;
bool vis[20000005];
void _(int n) {
	d[1] = 1;
	for(int i = 2;i <= n;++i) {
		if(!vis[i]) {
			pri[++cnt] = i;
			d[i] = 2,M[i] = 1;
		}
		for(int j = 1;j <= cnt && i * pri[j] <= n;++j) {
			vis[i * pri[j]] = 1;
			if(i % pri[j] == 0) {d[i * pri[j]] = d[i] / (M[i] + 1) * (M[i] + 1 + 1),M[i * pri[j]] = M[i] + 1;break;}
			else d[i * pri[j]] = d[i] * 2,M[i * pri[j]] = 1;
		}
	} 
	for(int i = 1;i <= n;++i) sd[i] = sd[i - 1] + d[i];
}
long long ans = 0;
int32_t main() {
	cin >> n >> A >> B >> C;
	cin >> g[n];
	_(n);
	for(int i = n - 1;i >= 1;--i) g[i] = (long long)( ((long long)A % mod * (long long)g[i + 1] % mod * (long long)g[i + 1] % mod) % mod + (long long)(B * (long long)g[i + 1] % mod) + (long long)C % mod) % mod;
	for(int i = 1;i <= n;++i) ans = (ans + (long long)((long long)g[i] * (long long)(n - i + 1) % mod * (long long)(n + sd[i - 1]) % mod) % mod) % mod;
	return cout << ans % mod << '\n',0;
}
```

---

## 作者：Hoks (赞：1)

## 前言
一眼题，但是被机房电脑死机两次硬控。

这个题有点太套路了吧，感觉还不如 T1（）。
## 思路分析
套路的想，我们对于每个位置 $i$ 计算他被计算的次数。

那么首先最好考虑的是 $r$，只要 $r>i$ 即可，直接数就行。

接着考虑左端点 $l$，从 $l$ 跳到 $i$，需要的步数即为 $i-l$，那么只需要 $c$ 是 $i-l$ 的倍数即可。

但这样枚举 $l$ 还是 $O(n^2)$ 的，不难发现，$l\in[1,i]$，也就是 $i-l\in[0,i-1]$，只需要计算这一段的因子个数之和就可以了。

考虑用线性筛筛出来每个数的因子个数，然后做个前缀和直接套公式即可。

注意 $l-i=0$ 时，$c$ 可以取任何数。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e7+10,V=2e7,M=3,INF=0x3f3f3f3f,mod=1e9+7;
int n,A,B,C,tot,ans,f[N],g[N],p[N];bool mp[N];
long long a[N],s[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='?'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void solve()
{
    n=read(),A=read(),B=read(),C=read();a[n]=read();for(int i=n-1;i>=1;i--) a[i]=(A*a[i+1]%mod*a[i+1]%mod+B*a[i+1]%mod+C)%mod;
    for(int i=1;i<=n;i++) ans=(ans+1ll*(s[i-1]+n)*(n-i+1)%mod*a[i]%mod)%mod;print(ans);
}
inline void get_phi(int n)
{
    f[1]=1,p[1]=0;
    for(int i=2;i<=n;i++)
    {
        if(!mp[i]) p[++tot]=i,f[i]=2,g[i]=1;
        for(int j=1;j<=tot&&i*p[j]<=n;j++)
        {
            mp[i*p[j]]=1;
            if(i%p[j]==0){g[i*p[j]]=g[i]+1;f[i*p[j]]=f[i]/(g[i]+1)*(g[i]+2);break;}
            g[i*p[j]]=1;f[i*p[j]]=f[i]*2;
        }
    }
}
signed main()
{
    get_phi(V);for(int i=1;i<=V;i++) s[i]=s[i-1]+f[i],(s[i]>mod)&&(s[i]-=mod);
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：Chenxuhang_play (赞：0)

## 题目链接

<https://www.luogu.com.cn/problem/P10886>

## 题目大意

小 W 最近正在学习某编程语言。

这个编程语言有个语句如下：

```
range(a,b,c)
```

这个语句表示一个序列，这个序列是这样的：

$$
[a,a+c,a+2c,\cdots,a+kc]
$$

其中，$k$ 是最大的满足 $a+kc<b$ 的非负整数 $k$。例如 `range(1,7,2)` 表示的序列为 $[1,3,5]$。

小 W 想问你一个问题：给你一个长为 $n$ 的序列 $g$（下标从 $1$ 开始），求出下列式子的值，答案模 $10^9 +7$。

$$
\sum_{a=1}^{n}\sum_{b=a+1}^{n+1}\sum_{c=1}^{n}\sum\limits_{i\in \mathrm{range}(a,b,c)} g_i
$$



$[a,a+c,a+2c,\cdots,a+kc]$

其中，$k$ 是最大的满足 $a+kc<b$ 的非负整数 $k$。例如 `range(1,7,2)` 表示的序列为 $[1,3,5]$。

## 思路

没错，某语言或许就是 python。 

注意看到，$n\le2\times10^7$，所以对于效率是 $O(n\log n)$的代码是不能过的。

所以追求 $O(n)$ 的代码。

---

先考虑给定 $a,b$ 时，$\sum_{c=1}^{n}\sum\limits_{i\in \mathrm{range}(a,b,c)} g_i$ 的结果。不难发现，对于整数 $a\le i\le b$：

+ 当 $i=a$ 时，对于每一个 $c$，$g_i$ 都会被累加，共计 $n$ 次；

+ 当 $i\not=a$ 时，对于每一个 $i-a$ 的因数 $c$，$g_i$ 都会被累加，共计 $cnt_{i-l}$ 次，其中 $cnt_k$ 代表 $k$ 的因数数量。

 对于每一个整数 $1\le i\le n$，考虑计算 $g_i$ 的贡献：

+ 先考虑 $a=i$ 的区间，共有 $n-i+1$ 个（$b$ 可以取到 $n+1$），贡献为 $n(n-i+1)g_i$；

+ 考虑 $a<i<b$ 的区间，由上面的推导可以得到，当 $a=j$ 时（$1\le j<i$），结果为 $cnt_{i-j}$。由于结果与 $b$ 无关，对于每一个可能的 $a$，$b$ 都有 $(n-i+1)$ 种结果相等的可能，因此每一个 $b$ 的结果之和为 $cnt_{i-1}+cnt_{i-2}+\cdots+cnt_{1}=sum_{i-1}$，其中 $sum$ 为 $cnt$ 的前缀和数组。总的结果为 $sum_{i-1}(n-i+1)g_i$。

最终的结果为 $\sum\limits_{i=1}^n(n+sum_{i-1})(n-i+1)g_i$。$cnt$ 数组可通过线性筛得到。总时间复杂度 $O(n)$。

## 声明

本文思路部分借鉴了 [这篇题解](https://www.luogu.com.cn/problem/solution/P10886) 的部分内容，绝非抄袭。

---

## 作者：ShanQing (赞：0)

upd：由于作者太菜显得写出的题解也过于唐，现在进行较大幅度的修改。

首先这种求和题的经典套路显然是拆贡献，算出每个 $g_i$ 的贡献系数 $f_i$。

所以考虑什么情况下 $g_i$ 会出现在一个等差数列里。显然地，需要满足  $a \leqslant i ，c|(i-a)，b > i$ 。

观察这些限制，从 $b>i$ 可以看出 $f_i$ 带一个乘 $n-i+1$ 。至此我们就不用再管 $b$ 了。

然后观察 $a \leqslant i ，c|(i-a)$ ，一种推法是 $f_i$ 带一个乘 $\sum_{j=1}^{n}\left \lceil \frac{i}{j} \right \rceil $ 。也就是枚举 $c$ 考虑合法的 $a$ 数量，最后就有 $f_i=(n-i+1) \times \sum_{j=1}^{n}\left \lceil \frac{i}{j} \right \rceil$。这个时候观察 $f(n)=\sum_{j=1}^{n}\left \lceil \frac{i}{j} \right \rceil$ 的变化量，由于 $\left \lceil \frac{i+1}{j} \right \rceil = \left \lceil \frac{i}{j} \right \rceil +1$ 仅当 $i$ 为 $j$ 的倍数，所以 $f(n+1)-f(n)$ 正好等于 $d_n$ （ $d_n$ 为 $n$ 的因数个数）。得到 $f(n)=n+\sum_{j=1}^{i-1} d_j$ 。 

这时候肯定会有人问，~~我是唐氏~~，我看不出这坨上取整求和是因数个数前缀和，怎么办？这里再介绍一种理解的办法，即改变枚举量，枚举 $a$ 考虑合法的 $c$ 数量：这个 $n$ 的由来显然，就是 $a=i$ 时的情形，此时 $c$ 可以从 $1$ 至 $n$ 任意选。然后这个 $\sum_{j=1}^{i-1} d_j$ 其实是在枚举 $a$ 。当 $a=i-j$ 时显然可能的 $c$ 取值有 $d_j$ 种。求和即可。也就是说，如果你卡在了上取整求和，从改变枚举量的角度考虑也可以得出最终柿子。事实上两者本质相同。

综上，我们得到 $f_i=(n-i+1) \times (n+\sum_{j=1}^{i-1} d_j)$ 。

到这一步就显然了，因为可以通过 $O(n)$ 的欧拉筛加一个前缀和预处理求出全部 $\sum_{j=1}^{i-1} d_j$ 。最后的计算显然也变成了 $O(n)$ 。

## code

```cpp
//writer:Oier_szc

#include <bits/stdc++.h>
//#include <windows.h>
#define ED cerr<<endl;
#define TS cerr<<"I AK IOI"<<endl;
#define cr(x) cerr<<x<<endl;
#define cr2(x,y) cerr<<x<<" "<<y<<endl;
#define cr3(x,y,z) cerr<<x<<" "<<y<<" "<<z<<endl;
#define cr4(x,y,z,w) cerr<<x<<" "<<y<<" "<<z<<" "<<w<<endl;
#define pii pair<int,int>
#define mk make_pair
#define fi first
#define se second
using namespace std;
const int N=2e7+5,INF=2e9,mod=1e9+7;
int n,a,b,c;
int g[N];
int primes[N],d[N],cnt[N],len=0;
bool st[N];

void init() {
	d[1]=1;
	for(int i=2;i<=n;++i) {
		if(!st[i]) {
			cnt[i]=1,d[i]=2;
			primes[++len]=i;
		}
		for(int j=1;j<=len&&primes[j]<=n/i;++j) {
			int to=i*primes[j];
			st[to]=1;
			if(i%primes[j]==0) {
				cnt[to]=cnt[i]+1;
				d[to]=d[i]/(cnt[i]+1)*(cnt[i]+2);
				break;
			}
			cnt[to]=1;
			d[to]=d[i]*2;
		}
	}
	for(int i=1;i<=n;++i) {
		d[i]=(d[i]+d[i-1])%mod;
	}
}

int main()
{
	scanf("%d%d%d%d",&n,&a,&b,&c);
	scanf("%d",&g[n]);
	for(int i=n-1;i>=1;--i) {
		g[i]=(1ll*a*g[i+1]%mod*g[i+1]+1ll*b*g[i+1]%mod+c)%mod;
	}
	init();
	int ans=0;
	for(int i=1;i<=n;++i) {
		ans=(ans+1ll*(n-i+1)*g[i]%mod*(d[i-1]+n))%mod;
	}
	printf("%d",ans);
	return 0;
}

```

---

## 作者：xiaoshu2010 (赞：0)

我们可以考虑计算 $g_i$ 被统计的次数 $f_i$，答案即为 $\sum_{i=1}^{n}{f_i \times g_i}$。

不妨设 $cnt_i$ 为当公差在 $1$ 到 $n$ 之间时，使 $g_i$ 产生贡献的等差数列区间左端点总数，则有 $cnt_i=n+\sum_{j=1}^{i-1}{(\lfloor \frac{i-1}{j} \rfloor)}$，易得 $f_i=cnt_i \times (n+1-i)$。

注意到，对于 $x \in N^+$，若 $x \mid (i-1)$,则首项为1，公差为 $x$ 的等差数列会使 $g_i$ 产生贡献。显然，$x$ 的数量为 $(i-1)$ 的约数个数。同理，对于 $a \in N^+$，若 $a \mid (i-k)$，则首项为 $k(1 \le k \le i-1)$，公差为a的等差数列会使 $g_i$ 产生贡献。特别地，首项为 $i$，公差为 $b(1 \le b \le n)$ 的等差数列均会使 $g_i$ 产生贡献。

设 $d_i$ 为 $i$ 的约数个数，则有 $cnt_i=n+\sum_{j=1}^{i-1}{d_i}$。

$d_i$ 可由[线性筛](https://oi-wiki.org/math/number-theory/sieve/)得出。

时间复杂度：$O(n)$。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=20000005;
typedef long long ll;
const ll mod=1e9+7;
bool prime[N];
ll n,a,b,c,g[N],ans,d[N],num[N];
vector<ll> pri;
void init(){
	d[1]=1;
	for(ll i=2;i<=n;i++){
		if(!prime[i]){
			pri.push_back(i);
			d[i]=2;
			num[i]=1;
		}
		for(ll j:pri){
			if(i*j>n)break;
			prime[i*j]=1;
			if(i%j==0){
				num[i*j]=num[i]+1;
				d[i*j]=d[i]/num[i*j]*(num[i*j]+1);
				break;
			}
			num[i*j]=1;
			d[i*j]=d[i]*2;
		}
	}
}
int main(){
	cin >>n>>a>>b>>c>>g[n];
	init();
	for(ll i=n-1;i>=1;i--){
		g[i]=(a*g[i+1]%mod*g[i+1]%mod+b*g[i+1]%mod+c)%mod;
	}
	ll sum=0;
	for(ll i=1;i<=n;i++){
		ans%=mod;
		sum+=d[i-1];
		sum%=mod;
		ans+=(sum+n)*(n+1-i)%mod*g[i]%mod;
		ans%=mod;
	}
	cout <<ans;
}
```

---

## 作者：EricWan (赞：0)

我是数学垃圾，因此我不能证明我的方法时间复杂度的正确性，但我的方法在洛谷是可以轻松过的，在萌熊上卡卡常也可以过。

我们看见这个复杂的式子，先转化式子。

原式长这样：

$$\sum_{a=1}^{n}\sum_{b=a+1}^{n+1}\sum_{c=1}^{n}\sum\limits_{i\in \mathrm{range}(a,b,c)} g_i$$

为了方便，我们下面说的 $b$ 都是原题中说的 $b+1$。

原式等于：

$$
\begin{aligned}
&\sum_{a=1}^n\sum_{b=a}^n\sum_{c=1}^n\sum\limits_{i\in\mathrm{range}(a,b,c)}g_i\\
=\ &\sum_{i=1}^n\sum_{b=i}^n\sum_{c=1}^ng_i+\sum_{i=1}^ng_i\times\sum_{a=1}^{i-1}\sum_{b=i}^n\mathrm{count\_factor}(i-a)\\
=\ &\sum_{i=1}^ng_i\times(n-i+1)\times n+\sum_{i=1}^ng_i\times(n-i+1)\times\sum_{j=1}^{i-1}\mathrm{count\_factor}(j)
\end{aligned}
$$

编辑公式不容易啊！

观察上面的式子，我们发现我们只需要求出每一个数的因数个数上面的式子就可求了。

算每个数的因数个数不好算，不如进行递推。

我们设当前正在算 $x$ 的因数个数，我们只需要知道 $x$ 最大的质因数，我们就可以在 $x$ 中不断的被这个数除，当不能再除时，我们设得到了 $y$，一共被除了 $z$ 次，那么，$\mathrm{count\_factor}(x)$ 一定等于 $\mathrm{count\_factor}(y)\times(z+1)$。

我们通过线性筛求每个数最大的质因数，暴力让一个数被它最大的质因数除，就可以成功通过了。

---

## 作者：ZhongYuLin (赞：0)

先转化为闭区间。考虑计算每个点被几个序列覆盖。显然右侧区间的每一个点都能产生贡献，于是要用右侧区间的长度乘上左侧区间的贡献。

考虑枚举 $c$，左侧区间贡献即为：

$$\sum_{c=1}^n \left \lfloor \frac{x-1}{c}  \right \rfloor $$

容易整除分块、调和级数得到部分分。下面来着重分析调和级数的实现过程及其优化。容易写出以下部分分代码：


```cpp
for(int y=1;y<=n;++y)
    for(int x=y-1;x-y<=n;x+=y)
        f[x-y+1]+=x/y,f[x+1]-=x/y;
```

我们利用差分来快速地区间加。注意到差分处的贡献互相抵消，上述代码与下面这一份等效：

```cpp
for(int y=1;y<=n;++y)
    for(int x=y;x<=n;x+=y)
        ++f[x];
```

于是差分数组即为约数。线性筛即可。介绍一种通用筛法，基本不要脑子。

假设我们要筛积性函数 $f(x)$，同时有 $f(p^k)=g(p^k)$（$g(p^k)$ 可以快速计算）。那么我们可以先筛出所有 $f(p^k)$ 与每个数的最小质因子组成的最大的数（例如，$12$ 的最小质因子组成的最大的数为 $4$）。然后利用积性函数的定义递推求出每一项，具体地，记第 $i$ 个数的最小质因子组成的最大的数为 $low_i$，则有：

$$f(i)=f(\frac{i}{low_i})f(low_i)$$

  回到本题。因数个数 $d(x)$ 为积性函数，且 $d(p^k)=k+1$。容易计算。又比如，$\varphi(p^k)=p^{k-1}(k-1)$，也容易计算。

代码：


```cpp
for(int i=2;i<=n;++i){
      if(!vis[i]){
          p[++tot]=i;
          low[i]=i;
          for(ll j=i,k=1;j<=n;j*=i,++k)
              f[j]=k+1;
      }
      for(int j=1;j<=tot&&p[j]*i<=n;++j){
          vis[i*p[j]]=1;
          if(i%p[j]==0){
              low[i*p[j]]=low[i]*p[j];
              break;
          }
          low[i*p[j]]=p[j];
      }
  }
  f[1]=1;
  for(int i=2;i<=n;++i)
      if(vis[i])f[i]=f[i/low[i]]*f[low[i]];
```

---

## 作者：GI录像机 (赞：0)

## 思路

考虑枚举每个 $i$，计算 $g_i$ 的系数。

显然若首项为 $a$，公差为 $c$ 的等差数列包含 $i$，那么 $b$ 只需满足 $b>i$ 即可。故可不枚举 $b$，若枚举的 $a,c$ 满足条件，则答案会加上 $(n-i+1)g_i$。

那么 $a,c$ 如何满足条件呢？就是 $c|(i-a)$，其中 $a\le i$。由于 $i-a<n$，所以其所有因子都是可以作为 $c$ 的，那么满足条件的 $a,c$ 数量为 $n + \sum_{j=1}^{i-1} d_j$ 其中 $d_j$ 表示 $j$ 的因子数。

综上，答案为 $\sum_{i=1}^n (n-i+1)g_i(n + \sum_{j=1}^{i-1} d_j)$。通过欧拉筛求 $d$ 即可 $O(n)$ 解决本题。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	int x = 0, f = 1;
	char c = getchar();
	while(c > '9' || c < '0') {
		if(c == '-')f = -f;
		c = getchar();
	}
	while(c <= '9' && c >= '0') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}
void write(int x) {
	if(x < 0) {
		putchar('-');
		x = -x;
	} if(x > 9)write(x / 10);
	putchar((x % 10) + '0');
}
const int N = 2e7 + 10, INF = 0x3f3f3f3f, MOD = 1e9 + 7;
int n = read(), A = read(), B = read(), C = read(), g[N], cnt, prime[N], tot, minn[N], d[N], ans, num[N], calc;
signed main() {
	g[n] = read();
	for(int i = n - 1; i >= 1; i--)g[i] = (((((1ll * g[i + 1] * g[i + 1]) % MOD) * A) % MOD) + ((1ll * g[i + 1] * B) % MOD) + C) % MOD;
	d[1] = 1, cnt = n;
	ans = (((1ll * n * g[1]) % MOD) * n) % MOD;
	for(int i = 2; i <= n; i++) {
		if(!minn[i]) {
			prime[++tot] = minn[i] = i;
			d[i] = 2, num[i] = 1;
		}
		for(int j = 1; j <= tot; j++) {
			if(i > n / prime[j])break;
			minn[i * prime[j]] = prime[j];
			if(i % prime[j] == 0) {
				num[i * prime[j]] = num[i] + 1;
				d[i * prime[j]] = d[i] / (num[i] + 1) * (num[i * prime[j]] + 1);
				break;
			}
			num[i * prime[j]] = 1, d[i * prime[j]] = d[i] << 1;
		}
		int uni = (1ll * (n - i + 1) * g[i]) % MOD;
		cnt = (cnt + d[i - 1]) % MOD;
		ans = (ans + 1ll * uni * cnt) % MOD;
	}
	write(ans);
	return 0;
}
```

---

## 作者：Lu_xZ (赞：0)

### Journey

题意：
$\text{range}(a, b, c)$ 表示序列
$$
[a, a + c, a + 2c, \cdots, a + kc]
$$
其中 $k$ 是满足 $a + kc < b$ 的最大非负整数。

给定大小为 $n \le 2 \times 10^7$ 的数组 $g$，求
$$
\sum_{a = 1}^n\sum_{b = a + 1}^n\sum_{c = 1}^n\sum_{i \in \text{range}(a, b, c)} g_i
$$

****

数据范围暗示很明显了，只放过线性做法。

每个 $g_i$ 会被 $a + kc = i$ 且 $b > i$ 的三元组贡献到。

设 $f(i)$ 表示 $a + kc = i$ 的 $(a, c)$ 对数
$$
\begin{aligned}
f(i) &= \sum_{a = 1}^n\sum_{c = 1}^n[a + kc = i]\\
\\
&= n + \sum_{a = 1}^{i - 1}d(i - a)\\
\\
&= n + \sum_{a = 1}^{i - 1}d(i)\\
\end{aligned}
$$
因此只要把 $d(i)$ 筛出来然后做一遍前缀和即可。

最后再乘上 $b$ 的 $n - i + 1$ 种取值。

```cpp
#include<bits/stdc++.h>
#define eb emplace_back
#define ep emplace
using namespace std;

using ll = long long;
constexpr int N = 2e7 + 5, P = 1e9 + 7;

int n; ll A, B, C, g[N];

ll d[N], s[N], iv[64];
int v[N], p[N], idx, c[N];

ll qpow(ll a, int b) {
	ll c = 1;
	while(b) {
		if(b & 1) c = c * a % P;
		b >>= 1;
		a = a * a % P;
	}
	return c;
}

void init() {
	for(int i = 1; i <= 60; ++ i) iv[i] = qpow(i, P - 2);
	d[1] = 1;
	for(int i = 2; i <= n; ++ i) {
		if(!v[i]) {
			c[i] = d[i] = 2;
			p[++ idx] = i;
		}
		for(int j = 1, o; j <= idx && p[j] <= n / i; ++ j) {
			o = i * p[j];
			v[o] = 1;
			if(i % p[j] == 0) {
				d[o] = d[i] * iv[c[i]] % P * (c[i] + 1) % P;
				c[o] = c[i] + 1;
				break;
			}
			d[o] = d[i] * 2 % P;
			c[o] = 2;
		}
	}
	for(int i = 2; i <= n; ++ i) d[i] = (d[i] + d[i - 1]) % P;
}

inline int f(int i) {
	return (n + d[i - 1]) % P;
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> A >> B >> C, init();
	cin >> g[n];
	for(int i = n; i > 1; -- i) {
		g[i - 1] = (A * g[i] % P * g[i] + B * g[i] + C) % P;
	}
	ll ans = 0;
	for(int i = 1; i <= n; ++ i) {
		ans = (ans + g[i] * f(i) % P * (n - i + 1)) % P;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：lizhous (赞：0)

题目相当于求每个位置 $i$ 会在多少个等差数列里出现。

对于一个 $i$ 来说，设 $d=i-a$，那么对于一个 $d$ 合法当且仅当它是 $c$ 的倍数。也就是说对于一个 $d$，合法的 $c$ 的个数就是 $d$ 的因数个数。而合法的 $d$ 满足 $d\le i$。合法的 $b$ 满足 $b\ge i$。也就是说设 $sum_i$ 表示前 $i$ 个数的因数个数和，对于 $i$，他被算到的次数就是 $sum_i\times (n-i+1)$。

但是我没有见过线性求因数个数，所以我需要发明一下。

欧拉筛可以求出当前数最小的质因子，那么考虑一个数，每次除掉最小的质因数，那么一个数做为除数肯定是在一个区间里。欧拉筛记录最小因数和他的次数，可以简单递推计算。

---

