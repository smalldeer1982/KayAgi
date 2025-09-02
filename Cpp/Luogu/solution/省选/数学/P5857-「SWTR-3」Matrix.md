# 「SWTR-3」Matrix

## 题目描述

小 E 有一个 $n \times m$ 的魔法矩阵，每个格子有激活和未激活两个状态。一开始，格子都是未激活的。

小 E 有一个魔法棒，可以使用 $k$ 次魔法。每次使用魔法时小 $\mathrm{E}$ 需选择一个魔法格子 $(x,y)$ 并改变第 $x$ 行和第 $y$ 列的所有魔法格子的状态。**$(x,y)$ 的状态会被改变两次。**

现在小 E 想知道，使用 $k$ 次魔法之后可以得到多少个不同的魔法矩阵。

- 两个魔法矩阵不同，当且仅当两个魔法矩阵中有一个对应格子的状态不同。

由于答案很大，请对 $998244353$ 取模。

## 说明/提示

#### 「样例说明」

- 对于第 1 组测试数据：无论如何使用魔法棒，最多只会有 1 种不同的魔法矩阵。 
- 对于第 3 组测试数据：任选一个格子使用 1 次魔法棒都能得到一个不同的魔法矩阵，共 $2\times 3=6$ 种不同的魔法矩阵。

---

### 数据范围与约定

测试点编号 | $n\leq$ | $m\leq$ | $k\leq$
:-: | :-: | :-: | :-:
$1$ | $1$ | $1$ | $10^9$
$2$ | $4$ | $4$ | $4$
$3-5$ | $200$ | $200$ | $200$
$6-7$ | $1$ | $1000$ | $10^5$
$8$ | $1000$ | $1000$ | $1$
$9-12$ | $1000$ | $1000$ | $10^5$
$13-20$ | $2\times 10^5$ | $2\times 10^5$ | $10^9$

对于 $100\%$ 的数据，$1 \leq T \leq 64$，$\ 1 \leq n,m \leq 2\times 10^5$，$\ 1 \leq k \leq 10^9$。

对于所有测试点，时间限制 1s，空间限制 32MB。

#### 「来源」

[Sweet Round 03 C](https://www.luogu.com.cn/contest/24755)。  
idea & solution：ET2006。

## 样例 #1

### 输入

```
11
1 1 3
4 3 5
2 3 1
123 231 132
1 1017 12345
1017 1567 1
1710 1017 999
1987 1789 375168429
101777 171077 99999
123321 200000 321123
2 2 1```

### 输出

```
1
32
6
198296574
832895500
1593639
928595966
438358858
366897935
745426660
2```

# 题解

## 作者：Hexarhy (赞：8)

### Preface

用 cmd 的引言：

> OI 中的四类组合问题 : 判定问题，构造问题，极化问题，计数问题。
> NOIP 命题风向 ： 弱化知识点，强化思维。

这题被 cmd 拿来作 NOIP 模拟赛 T2 了…… orz SWTR。

确实是一道计数好题，考察基本功和思维。

### Solution

部分分参考出题人的题解。

将一次操作分解成一行一列来思考。不难发现一行被操作奇数次时才能改变状态。于是若有 $i$ 行 $j$ 列都被操作了奇数次，那么这次操作产生的答案就是：

$$\binom{n}{i}\binom{m}{j}$$

注意满足恰好总操作数等于 $k$ 的条件为：$0\le i,j\le k,i\equiv k\pmod2,j\equiv k\pmod2$。

那么枚举 $i,j$ ，不难得到总答案：

$$\sum_{i=0}^{\min\{n,k\}}\sum^{\min\{m,k\}}_{j=0}\binom{n}{i}\binom{m}{j}[i\equiv k\pmod 2][j\equiv k\pmod 2]$$

发现两个 $\sum$ 可以乘开，运用乘法分配律就有：

$$(\sum_{i=0}^{\min\{n,k\}}\binom{n}{i}[i\equiv k\pmod 2])\times(\sum^{\min\{m,k\}}_{j=0}\binom{m}{j}[j\equiv k\pmod 2])$$

分别计算乘号两边，时间复杂度 $O(n)$。

然而不同的行列状态可能映射到同一个矩阵上，要减去这些重复的方案。

举个例子：

如果当前行/列状态为 $1$，那么是被操作了奇数次，$0$ 就是操作了偶数次。

下图 $i=2,j=2$。

| 行/列 | 1 | 1 |
| :----------: | :----------: | :----------: |
| **1** | 0 | 0 |
| **1** | 0 | 0 |

下图 $i=0,j=0$。

| 行/列 | 0 | 0 |
| :----------: | :----------: | :----------: |
| **0** | 0 | 0 |
| **0** | 0 | 0 |

两种合法的状态不同，但对应了同一个矩阵。再举例子发现，在 $(i,j)$ 合法的情况下，若 $(n-i),(m-j)\le k,(n-i)\equiv k\pmod 2,(m-j)\equiv k\pmod 2$，则 $(n-i,m-j)$ 也是一个合法的且重复的方案。

统计的时候计算出这些重复的，用总的减去重复的即可。

### Notice

- 不可以在计算合法的时候对重复的方案 $/2$ ，因为在最后乘起来的时候会变成 $/4$，使得答案错误。（如果有误请指出，因为本人在写的时候踩了坑。）

- 注意合适的地方使用`*1ll`。

- 本题涉及到快速求模意义下组合数，预处理阶乘和逆元即可。不过值域略大，因此考虑用 $inv(i)$ 表示 $i!$ 的逆元，用费马小定理与快速幂即可求出。这一步的复杂度是 $O(n\log n)$，本题并不会超时。也可以线性做到 $O(n)$ 推出。


### Code

**本代码需要C++11。**

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
using namespace std;

template<typename tp>
void read(tp& a)
{
    register tp num=0;register int f=1;register char ch=getchar();
    while(!isdigit(ch) && ch!='-') ch=getchar();
    if(ch=='-') f=-1,ch=getchar();
    do
        num=num*10+int(ch-'0'),ch=getchar();
    while(isdigit(ch));
    a=num*f;
}
template<typename tp,typename...Args>
void read(tp& a,Args&...args){	read(a);read(args...);	}

typedef const int cint;
cint MOD=998244353;
cint MAXN=2e5+5;
int n,m,k;
int fact[MAXN],inv[MAXN];

int qpow(int base,int k)
{
    register int res=1;
    while(k)
    {
        if(k&1) res=1ll*res*base%MOD;
        base=1ll*base*base%MOD;
        k>>=1;
    }
    return res;
}

void calc(cint MAX)
{
    fact[0]=inv[0]=1;
    for(int i=1;i<=MAX;i++) fact[i]=1ll*fact[i-1]*i%MOD;
    for(int i=1;i<=MAX;i++) inv[i]=qpow(fact[i],MOD-2);
}

int C(cint n,cint m)
{
    return 1ll*fact[n]*inv[m]%MOD*inv[n-m]%MOD;
}

void solve(void)
{
    auto get=[&](cint l,cint r,cint N)
    {
        int res=0;
        for(int i=l;i<=r;i+=2)  res=(1ll*res+C(N,i))%MOD;
        return res;
    };
    int ans1=0,ans2=0,ans3=0,ans4=0;
    ans1=get(min(k,n)&1,min(k,n),n);
    ans2=get(min(k,m)&1,min(k,m),m);
    if(n%2==0 && m%2==0)
    {
        ans3=get(max(n-k,0),min(k,n),n);
        ans4=get(max(m-k,0),min(k,m),m);
    }
    printf("%lld\n",(1ll*ans1*ans2%MOD-1ll*ans3*ans4%MOD*inv[2]%MOD+MOD)%MOD);
}

int main()
{
    calc(2e5+2);
    int T;read(T);
    while(T--)
    {
        read(n,m,k);
        solve();
    }
    return 0;
}
````

---

## 作者：Alex_Wei (赞：8)

较为基础的数论。

---

$\mathrm{Sol}\ 1:$

对于每一个询问，输出一行 $1$。

- 可通过测试点 $1$ 。

期望得分：$5\%$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t; 
int main(){
	cin>>t;
	for(int i=1;i<=t;i++)cout<<1<<endl;
	return 0;
}
```


---

$\mathrm{Sol}\ 2:$

对于每一个询问，暴力搜索，状压储存。

时间复杂度：$\mathcal O(n^{k+1}m^{k+1})$

- 可通过测试点 $2$ 。

期望得分：$5\%$，结合 $\mathrm{Sol}\ 1$ 可获得 $10\%$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t,ans,n,m,k,q[1<<16],z[6][6];
void dfs(int c){
	if(!c){
		int p=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				p+=z[i][j]<<i*m+j;//状压储存
		q[p]=1;
		return;
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			for(int k=0;k<m;k++)
				z[i][k]=!z[i][k];
			for(int k=0;k<n;k++)
				z[k][j]=!z[k][j];
			dfs(c-1);
			for(int k=0;k<m;k++)
				z[i][k]=!z[i][k];
			for(int k=0;k<n;k++)
				z[k][j]=!z[k][j];
		}
}
int main(){
	cin>>t;
	while(t--){
		memset(q,0,sizeof(q));
		cin>>n>>m>>k;
		dfs(k);//暴力搜索
		ans=0;
		for(int i=0;i<1<<n*m;i++)
			if(q[i])ans++;
		cout<<ans<<endl;
	}
    return 0;
}
```

---

$\mathrm{Sol}\ 3:$

对于每一个询问，输出一行 $n\times m$。

**特判 $n=2,m=2,k=1$ 时答案为 $2$。**

- 可通过测试点 $1,8$ 。

期望得分：$10\%$，结合 $\mathrm{Sol}\ 2$ 可获得 $15\%$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline int read(){
	int x=0,sign=1;char s=getchar();
	while(!isdigit(s)){
		if(s=='-')sign=-1;
		s=getchar();
	}
	while(isdigit(s)){
		x=(x<<1)+(x<<3)+(s^48);
		s=getchar();
	}
	return x*sign;
}
int t,n,m,k;
int main(){
	cin>>t;
	while(t--)cin>>n>>m>>k,cout<<(n==2&&m==2?2:n*m)<<endl;
    return 0;
}
```


---

$\mathrm{Sol}\ 4.0:$

我们知道，一个矩阵状态由它 **每一行被覆盖的次数** 和 **每一列被覆盖的次数** 决定。

- 如果一个行（或列）被点击了偶数次，那么就会变为原来的状态。

我们枚举一共有多少**行**被点击了**奇数**次，记为 $i$，再枚举一共有多少**列**被点击了奇数次，记为 $j$，那么应满足 $0\leq i,j\leq k$ 且 $i,j\equiv k\ (\bmod\ 2)$，然后用组合数计算该方案贡献的答案，即 $C^{i}_{n}\times C^{j}_{m}$。

- **对于该思路**，可通过测试点 $1,6,7$。

时间复杂度：$\mathcal O(nm)$。

期望得分：$15\%$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=998244353;
ll c[2005][2005],t;
void init(){
	c[0][0]=1;
	for(int i=1;i<=2004;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
	}
	scanf("%d",&t);
}
int main(){
	init();
	while(t--){
		ll n,m,k,ans=0;
		scanf("%lld%lld%lld",&n,&m,&k);
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m;j++)
				if(i<=k&&j<=k&&(k-i)%2==0&&(k-j)%2==0)
					ans=(ans+c[n][i]*c[m][j])%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
```

打一遍代码，测一遍样例，发现过了，然后美滋滋地交上去 $\dots$

如果你本来打算用这种思路通过前 $12$ 个测试点，那么恭喜你，你成功地 $\color{red}\mathrm{WA}$ 到不知道哪里去了。

---

$\mathrm{Sol}\ 4.1:$

- 在下文中，你需要知道：乘法逆元，费马小定理求乘法逆元，组合数计算公式 $C^{m}_{n}=\frac{n!}{m!(n-m)!}$。

观察一下 $\mathrm{Sol}\ 4.0$ 通过的测试点，都是 $n=1$，思考一下为什么会发生这种情况。

先来看个例子，假设我们有一个 $3\times 4$ 的矩阵：

行/列|$0$|$1$|$1$|$0$
:-:|:-:|:-:|:-:|:-:
$1$|$1$|$0$|$0$|$1$|
$0$|$0$|$1$|$1$|$0$|
$1$|$1$|$0$|$0$|$1$|

- 在下文中，我们把上面这种改变方式简写为 $(101,0110)$。

- 在该表中，最上面一行为该列被改变的次数 $\bmod\ 2$，最左边一列为该行被改变的次数 $\bmod\ 2$，右下角的 $3\times 4$ 方格为真正的矩阵。

如果把每行，每列被改变的次数 $\bmod\ 2$ 取反，则会变成下面这个样子 $(010,1001)$：

行/列|$1$|$0$|$0$|$1$
:-:|:-:|:-:|:-:|:-:
$0$|$1$|$0$|$0$|$1$|
$1$|$0$|$1$|$1$|$0$|
$0$|$1$|$0$|$0$|$1$|

我们惊奇地发现，矩阵并没有改变！

- 所以对于每一种行，列的点击方式 $(x,y)$，如果把 $x,y$ 的所有数取反，仍能得到相同的矩阵，于是就产生了重复计算。

#### 我们考虑如何去掉重复计算。

仍然枚举有多少**行**和**列**被点击了**奇数**次，分别记为 $i,j$，在符合 $\mathrm{Sol}\ 4.0$ 条件 $0\leq i,j\leq k$ 且 $i,j\equiv k\ (\bmod\ 2)$ 的情况下，如果 $i,j$ 还满足 $n-i,m-j\leq k$ 且 $n-i,m-j\equiv k\ (\bmod\ 2)$（即取反之后仍满足题目条件），那么就会有一半的重复计算，对答案的贡献变为 $\frac{1}{2}\times C^{i}_{n}\times C^{j}_{m}$。

时间复杂度：$\mathcal O(nm)$。

- 可通过前 $12$ 个测试点。

期望得分：$60\%$。

代码，其中：

- $C(i,n)$ 表示 $C^{i}_{n}$。

- $f_i$ 表示 $i!\bmod998244353$。

- $inv_i$ 表示 $i!$ 关于 $998244353$ 的逆元，即 $\frac{1}{i!}\bmod 998244353$。

```cpp
//O(nm)
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod=998244353;
const int N=2e5+5;
int f[N],inv[N],t,n,m,k;
int ksm(int a,int b){
	int s=1,m=a;
	while(b){
		if(b&1)s=1ll*s*m%mod;
		m=1ll*m*m%mod;
		b>>=1;
	}
	return s;
}
void init(){
    inv[0]=f[0]=1;
    for(int i=1;i<N;i++)f[i]=1ll*i*f[i-1]%mod,inv[i]=ksm(f[i],mod-2);
    scanf("%d",&t);
}
int C(int m,int n){
	return 1ll*f[n]*inv[m]%mod*inv[n-m]%mod;
}
int main(){
	init();
	while(t--){
		scanf("%d%d%d",&n,&m,&k);
		int ans=0;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m;j++)
				if(i<=k&&j<=k&&(i-k)%2==0&&(j-k)%2==0){
					ll q=1ll*C(i,n)*C(j,m)%mod;
					if((n-i-k)%2==0&&(m-j-k)%2==0&&n-i<=k&&m-j<=k)q=q*inv[2]%mod;//这里乘inv[2]其实是用了2的阶乘为2的小技巧
					ans=(ans+q)%mod;
				}
		printf("%d\n",ans);
	}
	return 0;
}
```

由上文得到的结论，我们也可以发现当 $n,m$ 都为偶数，且 $k\ge\frac{n}{2},\frac{m}{2}$ 时，才会发生重复的现象。

这就是为什么 $\mathrm{Sol}\ 4.0$ 能够通过样例（样例 $n,m$ 中必有一个奇数）却只能通过 $n=1$ 的测试点。

---

$\mathrm{Sol}\ 5:$

在 $\mathrm{Sol}\ 4.1$ 的基础上，用乘法结合律优化一下即可。

$$\sum_{i=a}^{b}\sum_{j=c}^{d}x_i\times y_j=\Big(\sum_{i=a}^{b}x_i\Big)\times\Big(\sum_{j=c}^{d}y_j\Big)$$

时间复杂度：$\mathcal O(\max(n,m))$。

期望得分：$100\%$。

---

$\mathrm{std:}$

```cpp
//O(n)
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod=998244353;
const int N=2e5+5;
int f[N],inv[N],t,n,m,k;
int ksm(int a,int b){
	int s=1,m=a;
	while(b){
		if(b&1)s=1ll*s*m%mod;
		m=1ll*m*m%mod;
		b>>=1;
	}
	return s;
}
void init(){
    inv[0]=f[0]=1;
    for(int i=1;i<N;i++)f[i]=1ll*i*f[i-1]%mod,inv[i]=ksm(f[i],mod-2);
    scanf("%d",&t);
}
int C(int m,int n){
	return 1ll*f[n]*inv[m]%mod*inv[n-m]%mod;
}
int main(){
	init();
	while(t--){
		scanf("%d%d%d",&n,&m,&k);
		int nn=min(n,k),mm=min(m,k),an=0,am=0,bn=0,bm=0;
		for(int i=nn%2;i<=nn;i+=2)an=(an+C(i,n))%mod;
		for(int i=mm%2;i<=mm;i+=2)am=(am+C(i,m))%mod;
		if(n%2==0&&m%2==0){//减掉重复部分
			int l=max(n-k,0),r=min(n,k);
			for(int i=l;i<=r;i+=2)bn=(bn+C(i,n))%mod;
			l=max(m-k,0),r=min(m,k);
			for(int i=l;i<=r;i+=2)bm=(bm+C(i,m))%mod;
		}
		printf("%lld\n",(1ll*an*am%mod-1ll*bn*inv[2]%mod*bm%mod+mod)%mod);
	}
	return 0;
}
```


---

## 作者：LittleMoMol (赞：1)

### 思路

显而易见地，一个矩阵地状态由它**每一行被覆盖的次数**和**每一列被覆盖的次数**决定。由于是异或运算，所以：一行或一列被覆盖了偶数次，其结果和没有覆盖的一样。这条性质告诉我们，实际上有效的操作次数可能比 $k$ 小。

这道题的另一个重要性质：若有 $r$ 行被覆盖了奇数次，$c$ 列被覆盖了奇数次，那么 $r,c,k$ 同奇偶。这个简单分类讨论即可。那么我们可以枚举 $r$ 和 $c$，其**情况合法**等价于 $0 \le r,c \le k$ 且 $i \equiv j \equiv k \pmod 2$，若满足该条件，则方案数的贡献为 $C_{n}^{r} \times C_m^c$，否则为 $0$  

不幸的是，这个答案并不对，因为会有**算重**的情况，如果所有行和列构成全集 $U$，一种覆盖方案所包含的行和列的集合为 $S$，你会发现 $\complement_U S$ 与 $S$ 构成的矩阵是一模一样的！然而在计算方案的时候把这种情况算了两遍，即按照 $S$ 算了一遍，又按照 $\complement_U S$ 算了一遍。所以？除个 2？发现又错了……

是不是每种情况都被算了两遍呢？并不是的，还记得之前使得该**情况合法**的条件吗？集合 $S$ 合法，并不代表着集合 $\complement_U S$ 一定合法。

再给出一个性质：当且仅当 $n,m$ 均为偶数且 $k \ge \max\left(\dfrac n2, \dfrac m2\right)$ 时，会重复计算。我们证明一下：当 $n$ 是奇数时，$r,n-r$ 是异奇偶的（因为奇数减奇数为偶数，奇数减偶数为奇数），那么必然不会使得“$r,k$ 同奇偶、$n-r,k$ 同奇偶”同时满足，也就是说 $S$ 与 $\complement_U S$ 中有一个是不合法的，自然就不会算重。若 $k < \dfrac n2$，那么“选择 $r$ 行进行覆盖与选择 $n-r$ 行进行覆盖”这两者有一个是不可能满足的，自然也不会算重。当 $m$ 是奇数时，同理。

所以，若 $n,m$ 均为偶数且 $0 \le r,c, n-r, m-c \le k$ 且 $r \equiv c \equiv n-r \equiv n-c \equiv k \pmod 2$，那么会有一半的重复计算，对答案的贡献变为了 $\dfrac 12 C_n^i \times C_m^j$ 

为了优化复杂度，因为 $\sum\limits_{r=1}^n \sum\limits_{c=1}^m C_n^r C_m^c = \left(\sum\limits_{r=1}^n C_n^r \right) \left(\sum\limits_{c=1}^m C_m^c\right)$，所以我们可以先算出 $\sum\limits_{r=1}^n C_n^r$ 和 $\sum\limits_{c=1}^m C_m^c$，然后再相乘即可。

接下来的问题，是最恶心的**边界问题**！这里只说行的边界问题，列是同理的。

在不考虑去重的时候，上界很显然是 $\min(n,k)$，由于 $r$ 需要和 $k$ 的奇偶性相同，所以下界为 $\min(n,k) \bmod 2$，每次 $r$ 增加 $2$。后来发现下界为 $k \bmod 2$ 竟然也可以！经过一段时间的思考，发现罪魁祸首是**组合恒等式**：$\sum_{i=0,\ i \bmod 2=0}^n C_n^i = \sum_{i=1,\ i\bmod 2=1}^n C_n^i$，这个可以用二项式定理证明，就不赘述了。当 $n,k$ 的奇偶性相同时，对答案自然没有影响；当 $n,k$ 的奇偶性不同时，根据这个等式发现，对答案也是没有影响的。

在去重的时候，由于需要满足 $n-r \le k$，所以下界是 $\max(0, n-k)$，上界是 $\min(n,k)$，除此之外，$r$ 还需要满足 $n - r \equiv k \pmod 2$，即 $r \equiv n - k \pmod 2$，所以 $r$ 的下界从 $\max(0, n-k)$，每次加 $2$。

### Code

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long LL;
const LL mod = 998244353;
const LL N = 2e5 + 10;

LL fac[N], inv[N];
LL T, n, m, k;

LL qmi(LL a, LL k)
{
	LL res = 1;
	while (k)
	{
		if (k & 1) res = res * a % mod;
		a = a * a % mod;
		k >>= 1;
	}
	return res;
}

void initiative()
{
	inv[0] = fac[0] = 1;
	for (LL i = 1; i < N; i ++ )
	{
		fac[i] = i * fac[i - 1] % mod;
		inv[i] = qmi(fac[i], mod - 2);
	}
}

LL C(LL n, LL m)
{
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	initiative();
	cin >> T;
	while (T -- )
	{
		cin >> n >> m >> k;
		LL nn = min(n, k), mm = min(m, k);
		LL an = 0, am = 0, bn = 0, bm = 0;
		// cout << nn << ' ' << k << endl << mm << ' ' << k << endl;
		for (LL i = (k & 1); i <= nn; i += 2) an = (an + C(n, i)) % mod;
		for (LL i = (k & 1); i <= mm; i += 2) am = (am + C(m, i)) % mod;
		if (n % 2 == 0 && m % 2 == 0)
		{
			LL l = max(n - k, 0ll), r = min(n, k);
			for (LL i = l; i <= r; i += 2) bn = (bn + C(n, i)) % mod;
			l = max(m - k, 0ll), r = min(m, k);
			for (LL i = l; i <= r; i += 2) bm = (bm + C(m, i)) % mod;
		}
		LL ans = an * am % mod - bn * bm % mod * inv[2] % mod;
		ans = (ans + mod) % mod;
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：PokerKing (赞：0)

## 分析：

首先我们可以肯定的一点就是，我们可以发现，一个矩阵的形态只和他横着和竖着有多少行和列被转化了**奇数次**，而与剩下的都没有关系。

很显然的可以发现行和列是可以独立计算再相乘的，考虑如何计算单行和单列的贡献。

以行为例，我们可以枚举他有多少个奇数的位置，发现奇数位置的数量 $i$ 必须满足如下的性质：

$$i \leq k$$

$$i \leq n$$

$$i \equiv k \pmod 2$$

但是发现可能有一种特殊情况，就是当 $n-i$ 和 $m-j$ 也合法的时候，两者形成的矩形是完全一样的，需要把这一部分的消去。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Lint long long
const int N=2e5+5;
const Lint MOD=998244353;
const Lint Inv=499122177;
int n,m,k;Lint res=0;
Lint fac[N],ifac[N];
Lint cnt1[2],cnt2[2];
Lint ksm(Lint x,int k)
{
	Lint res=1;
	for(;k;k>>=1,x=x*x%MOD)
	if(k&1) res=res*x%MOD;
	return res;
}
Lint cal(int n,int m){return fac[n]*ifac[m]%MOD*ifac[n-m]%MOD;}
void solve()
{
	cin>>n>>m>>k,res=0;
	Lint res1=0,res2=0;
	for(int i=k%2;i<=n&&i<=k;i+=2) res1+=cal(n,i),res1%=MOD;
	for(int i=k%2;i<=m&&i<=k;i+=2) res2+=cal(m,i),res2%=MOD;
	res+=res1*res2%MOD;
	if(n%2==0&&m%2==0)
	{
		res1=res2=0;
		for(int i=max(n-k,k&1);i<=n&&i<=k;i+=2) res1+=cal(n,i),res1%=MOD;
		for(int i=max(m-k,k&1);i<=m&&i<=k;i+=2) res2+=cal(m,i),res2%=MOD;
		res-=res1*res2%MOD*Inv%MOD,res=(res+MOD)%MOD;
	}
	printf("%lld\n",res);
}
int main()
{
	fac[0]=ifac[0]=1;
	for(int i=1;i<N;++i) fac[i]=fac[i-1]*i%MOD;
	for(int i=1;i<N;++i) ifac[i]=ksm(fac[i],MOD-2);
	int T;cin>>T;
	while(T--) solve();
}
```

---

## 作者：Mars_Dingdang (赞：0)

一道不错的组合计数题。 

## 题目大意 
有一个 $n\times m$ 的 $01$ 矩阵，初始时每个元素均为 $0$。 有 $k$ 次操作，每次选择第 $x$ 行和第 $y$ 列，将整行元素取反，再将整列元素取反。求 $k$ 次操作后不同矩阵的种类数，答案对 $998244353$ 取模。 

## 大体思路
很容易发现，其实行与列的操作是互相独立的，因此本题相当于可重复地取反 $k$ 行，并且可重复地取反 $k$ 列。

由于最终某一行（列）有贡献，当且仅当这一行（列）被操作了奇数次，所以我们枚举有 $i$ 行 $j$ 列被操作了奇数次，其中 $i\in [0,\min(n,k)]$，$j\in [0,\min(m,k)]$，并且 $i,j$ 的奇偶性与 $k$ 相同。那么，答案即为

$$A=\sum_{i=0}^{\min(n,k)}\sum_{j=0}^{\min(m,k)} \binom n i \binom m j[i,j\equiv k\bmod 2]\pmod {998244353}$$

但是，我们会发现样例中 $m=n=2$ 的情况便出现了问题。我们思考某一个元素变成 $1$ 的条件。

如果用 $0,1$ 表示某一行 $x$ 被操作偶数次或奇数次，记为 $I_x$，那么 $a_{x,y}=I_x\ \text{xor}\ I_y$。此时，如果将代表每一行列的 $01$ 变量 $I$ 取反，可以证明 $I_x^{'}\ \text{xor}\ I_y^{'}=I_x\ \text{xor}\ I_y$，因此这种情况下整个矩阵是相同的。

我们研究何时这种情况会出现。基于行列情况等价，我们讨论行的情况。由于 $i$ 的奇偶性与 $k$ 相同，即 $i\equiv k\pmod 2$，同时取反后 $n-i\equiv k\pmod 2$，两式相加得 $n\equiv 2k\equiv 0\pmod 2$。也就是说，$n,m$ 均为偶数。

同时，重复部分需要满足 $n-i\le k,i\ge n-k$，所以 $i\in [0,n]\cap [n-k,k]$，$j$ 同理。我们记这一部分的答案为
$$D=\sum_{i=\max(0,n-k)}^{\min(n,k)}\sum_{j=\max(0,m-k)}^{\min(m,k)} \binom n i \binom m j[i,j\equiv k\bmod 2]\pmod {998244353}$$

由于重复部分在 $A,D$ 中均被计算两次，最终答案减去重复部分的一半即可，即 $ans=A-\dfrac D 2$。

由于 $998244353$ 为质数，计算 $\binom n m=\dfrac {n!}{m!(n-m)!}$ 以及使用除法时，利用费马小定理 $a^{p-1}\equiv 1$，$a^{p-2}\equiv a^{-1}\pmod p$ 计算逆元即可。由于 $n,m$ 同阶，总的时间复杂度为 $O(n\log p)$，其中 $\log p$ 来自于预处理阶乘逆元时快速幂的复杂度。

## 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re ll ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 2e5 + 5;
const ll mod = 998244353;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
ll n, m, k, T, inv[maxn], fac[maxn];
inline ll Pow(ll a, ll b) {
	ll res = 1;
	while(b) {
		if(b & 1) res = (res * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return res % mod;
}
inline void init() {
	int N = 2e5;
	fac[0] = inv[0] = 1;
	rep(i, 1, N) {
		fac[i] = (i * fac[i - 1]) % mod;
		inv[i] = Pow(fac[i], mod - 2);
	}
}
inline ll C(ll n, ll m) {
	ll res = fac[n];
	return (((res * inv[m]) % mod) * inv[n - m]) % mod;
}
inline void solve() {
	read(n); read(m); read(k);
	ll c = (k & 1);
	ll sI = 0, sJ = 0;
	for(ll i = c; i <= min(n, k); i += 2) (sI += C(n, i)) %= mod;
	for(ll j = c; j <= min(m, k); j += 2) (sJ += C(m, j)) %= mod;
	ll ans = (sI * sJ) % mod;
	if(!(n & 1) && !(m & 1)) {
		ll dI = 0, dJ = 0;
		for(ll i = max(n - k, 0ll); i <= min(n, k); i += 2) (dI += C(n, i)) %= mod;
		for(ll j = max(m - k, 0ll); j <= min(m, k); j += 2) (dJ += C(m, j)) %= mod;
		ll dlt = ((dI * dJ % mod) * inv[2]) % mod;
		ans = (ans - dlt + mod) % mod;			
	}
	writeln(ans);
}
int main () {
	init();
	read(T);
	while(T --) solve();	
	return 0;
}
```

---

