# [LMXOI Round 1] Random

## 题目背景

LMX 给 HQZ 一个有趣的序列，HQZ 为了了解 LMX 的爱好，想要解决下面的问题。  

## 题目描述

给出一个初始全为 $0$ 长为 $n$ 的序列，我们会进行如下操作 $q$ 次。

+ 任意选择一个位置 $t$ 并把上面的数字修改成任意一个 $1$ 到 $k$ 之间的数。

也就是说我们一共会有 $(nk)^q$ 种不同的询问序列，而对于每一种不同的询问序列，对应的也就拥有了 $(nk)^q$ 个结果序列。

接着，给出一个长度为 $m$ 匹配序列 $B$，需要求出这个匹配序列在每一个结果序列中出现的次数和。注意，一个结果序列中若出现多个匹配序列应当重复计算。

由于答案太大，你只需要输出答案对 $998244353$ 取模后的结果。

**本题使用特定方式生成输入数据。**

生成格式如下： $x_i=(a \times i+b)\bmod k +1$ ，其中 $x_i$ 表示序列 $B$ 第 $i$ 位所需求的数字。

## 说明/提示

**样例解释 #1**

下述操作序列，存在序列 $B$：
+ $[1,1],[2,2]$ 序列为 $[1,2,0]$
+ $[2,2],[1,1]$ 序列为 $[1,2,0]$
+ $[2,1],[3,2]$ 序列为 $[0,1,2]$
+ $[3,2],[2,1]$ 序列为 $[0,1,2]$

对于 $100\%$ 的数据，保证 $\forall x_i \in B, 1\le x_i\le k$，$0 \le a,b\le 10^9$，且 $m\le n$。

| 子任务编号 |      $n,q,k$      |    $m$    | 特殊性质 |  分值  |
| :--------: | :------------------: | :----------: | :------: | :----: |
| Subtask #1 |     $\le 10^9$     | $\le 200$ | $q< m$ | $5$ |
| Subtask #2 |      $\le 4$      |  $\le 4$  |    无    | $10$ |
| Subtask #3 |     $\le 500$     | $\le 200$ |    无    | $10$ |
| Subtask #4 | $\le 2\times 10^5$ | $\le 200$ |    无    | $20$ |
| Subtask #5 |     $\le 10^9$     | $\le 200$ |    无    | $20$ |
| Subtask #6 |     $\le 10^9$     | $\le 3\times 10^6$ |    无    |   $35$   |

## 样例 #1

### 输入

```
3 2 2 2
1 1```

### 输出

```
4```

## 样例 #2

### 输入

```
2 1 2 2
1 1```

### 输出

```
12```

## 样例 #3

### 输入

```
10 3 114 51419
19 2```

### 输出

```
266405589```

# 题解

## 作者：_ANIG_ (赞：9)

[传送门](https://www.luogu.com.cn/problem/P10116)

首先，假如我们考虑 $B$ 在每个位置的贡献加起来，可以发现答案跟 $B$ 是无关的，所以题目给你的 $B$ 是没有用的。

现在钦定 $B$ 在开头出现了，算出来总方案数乘上 $n-m$ 即可。

设 $f_{a,b}$ 为进行了 $b$ 次操作，这 $b$ 次操作的位置都在前 $m$ 个，并且前 $m$ 个里面已经完工了 $a$ 个的方案数。

枚举第 $a$ 个位置完工被操作的多少次，可得转移方程：

$$f_{a,b}=\sum\limits_{i=1}^b\binom{b}{i}k^{i-1}f_{a-1,b-i}$$

则答案为 $\sum\limits_{i=0}^qf_{m,i}\binom{q}{i}k^{q-i}(n-m)^{q-i}$。

考虑求 $f_m$。

推一推式子：

$$f_{a,b}=\sum\limits_{i=1}^b\frac{b!f_{a-1,b-i}k^{i-1}}{i!(b-i)!}$$

$$=b!\sum\limits_{i=1}^b\frac{f_{a-1,b-i}}{(b-i)!}\times \frac{k^{i-1}}{i!}$$

把 $b!$ 除过去：

$$\frac{f_{a,b}}{b!}=\sum\limits_{i=1}^b\frac{f_{a-1,b-i}}{(b-i)!}\times \frac{k^{i-1}}{i!}$$

令 $g_{a,b}=\frac{f_{a,b}}{b!}$，则：

$$g_{a,b}=\sum\limits_{i=1}^bg_{a-1,b-i}\times\frac{k^{i-1}}{i!}$$

构造多项式 $T(x)=\sum\limits_{i=1}\frac{k^{i-1}}{i!}x^i$，则 $g_a=g_{a-1}\times T$。

于是 $g_m=T^m$。

可以发现，$T(x)=\frac{e^{kx}-1}{k}$。

则 

$$g_m=\frac{(e^{kx}-1)^m}{k^m}$$

$$=\frac{\sum\limits_{i=0}^m\binom{m}{i}(-1)^{m-i}e^{ikx}}{k^m}$$

所以 

$$g_{m,j}=\frac{\sum\limits_{i=0}^m\binom{m}{i}(-1)^{m-i}(ik)^j}{k^mj!}$$

$$f_{m,j}=\frac{\sum\limits_{i=0}^m\binom{m}{i}(-1)^{m-i}(ik)^j}{k^m}$$

带回原式，答案为：

$$\frac1{k^m}\sum\limits_{i=0}^q\binom{q}{i}k^{q-i}(n-m)^{q-i}\sum\limits_{j=0}^m\binom{m}{j}(-1)^{m-j}(jk)^i$$

$$=k^{q-m}\sum\limits_{j=0}^m\binom{m}{j}(-1)^{m-j}\sum\limits_{i=0}^q\binom{q}{i}(n-m)^{q-i}j^i$$

$$=k^{q-m}\sum\limits_{j=0}^m\binom{m}{j}(-1)^{m-j}(n-m+j)^q$$

这样就可以 $O(m\log q)$ 做了。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e6+5,mods=998244353;
int pows(int a,int b){
    if(b==0)return 1;
    int res=pows(a,b>>1);
    res=res*res%mods;
    if(b&1)res=res*a%mods;
    return res;
}
int n,m,qs,k,jc[N],res,ny[N];
int C(int a,int b){
    return jc[a]*ny[b]%mods*ny[a-b]%mods;
}
signed main(){
    jc[0]=ny[0]=1;
    for(int i=1;i<N;i++)jc[i]=jc[i-1]*i%mods;
    ny[N-1]=pows(jc[N-1],mods-2);
    for(int i=N-2;i>=1;i--)ny[i]=ny[i+1]*(i+1)%mods;
    cin>>n>>m>>qs>>k;
    for(int j=0;j<=m;j++){
        res+=pows(-1,m-j)*C(m,j)%mods*pows(n-m+j,qs)%mods;
        res%=mods;
    }
    cout<<(res*(n-m+1)%mods*pows(pows(k,m),mods-2)%mods*pows(k,qs)%mods+mods)%mods;
}
```


---

## 作者：KAxdd (赞：9)

## 前言

感谢 @DaydreamWarrior 踩爆了我的 $O(m^3 \log q )$ 做法，并提供了更优的斯特林数做法。

## 题意

给出一个初始全为 $0$ 长为 $n$ 的序列，我们会进行如下操作 $q$ 次。

+ 选择一个位置 $t$ 并把上面的数字修改成 $x$。

其中，$x$ 的值域为 $[1,k]$ 也就是说我们一共会有$(nk)^q$ 种不同的询问序列，问所有询问序列操作进行后，所有询问序列结果的子串恰好出现 $B$ 的数量。

## 5pts

直接输出 $0$ 即可。

## 15pts

直接爆搜即可。

## 25pts

这里是给那些用整数拆分求方案数的人准备的部分分。

## 45pts

我们注意到这道题目有一个性质：**每个位置的值独立，且只与最后一次修改有关。** 那么对于这样的性质，我们可以发现题目中给的目标序列根本不会在求方案数里面用到，实际上，只要长度相同方案数也是相同的，因为目标相互独立，而每个点的修改次数都是相同的，而且因为是求个数，对于目标序列所在的每一个位置，答案都是相同的。那么我们就可以构造出一个dp式子。

我们设 $f_{i,j}$ 为我们已经做了 $i$ 次询问，且已经有 $j$ 个数字已经满足了要求。

如果我们此次操作选择了目标序列上的点，且我们增加了一个满足要求的点:
$$f_{i,j}=f_{i-1,j}\times(m-j+1)$$

如果我们此次操作把一个目标序列上的点修改成了其他的点：
$$f_{i,j}=f_{i-1,j+1}\times(j+1)\times (k-1)$$

接下来，讨论当前目标序列不变有哪些可能，首先是目标序列重复修改成满足要求的，然后是目标序列以外的点随意修改，接着是目标序列不满足要求的修改成了同样不满足要求的值。整合一下，式子就成了：
$$f_{i,j}=f_{i-1,j}\times(j+(n-m)\times k+(m-j)\times(k-1))$$

接着，我们把代码写出来，就可以获得此分数，时间复杂度$O(qm)$。

## 65pts
我们注意到这道题 $m$ 很小而 $q$ 到达了不可以dp的水平。我们考虑看这个式子的性质。我们发现这个式子每次**转移乘上的系数都是相同的**。也就是说这就是一个递推式，我们可以用矩阵快速幂优化，把不可以dp的 $q$ 去掉，这样子就可以实现时间复杂度 $O(m^3\log q)$。
## 100pts
矩阵已经做不动了，这个矩阵也没有别的优化方式，我们需要考虑组合意义。我们可以发现，假设我们不关注我们不需求修改操作的部分，那么其可以转换成把 $q$ 个操作分成 $m$ 个集合，且最后一个数钦定，其他的都需要带上 $k$ 的常数，我们可以发现这个东西跟斯特林数很像，所以考虑斯特林数，这里的斯特林数是考虑的第二类的。

我们首先考虑写出这个式子，就是枚举操作数，然后可以用第二类斯特林数暴力做。
$$
(n-m+1)m!\sum_{i=m}^qS(i,m)((n-m)k)^{q-i}k^{i-m}\binom{q}{i}
$$

解释一下式子，我们把当前所修改操作的 $i$ 分到了 $m$ 个集合当中，其中不修改到操作集合上的点有 $n-m$ 个位置，其中任意字符集都可以选择， 而在其中的修改也只有 $m$ 个关键操作，然后我们需要把目前枚举的操作分散到 $q$ 之中。

接下来我们先整理一下式子：

$$(n-m+1)k^{q-m}m!\sum_{i=m}^qS(i,m)(n-m)^{q-i}\binom{q}{i}$$

我们发现这个式子并不好快速求值，主要瓶颈在于斯特林数的递推时间复杂度太高，以及我们没有办法把其压缩到跟 $m$ 有关，所以我们考虑拆分斯特林数。

我们考虑这道题的组合意义，相当于我们有两种球 $A,B$，接着每一类球的分别就是是否放到我们的某个盒子里去。但这道题要求不能有空盒子，所以我们考虑容斥，枚举空盒子的大小，然后可以求出没有空盒子的解。然后我们可以获得以下式子。

$$(n-m+1)k^{q-m}\sum_{e=0}^m(-1)^e\binom{m}{e}\sum_{i=0}^q(m-e)^i(n-m)^{q-i}\binom{q}{i}$$

接下来我们发现后面的可以二项式定理合并。后面就简单了，整理以下式子就可以结束本题。

$$(n-m+1)k^{q-m}\sum_{e=0}^m(-1)^e\binom{m}{e}(m-e+n-m)^q$$

$$(n-m+1)k^{q-m}\sum_{e=0}^m(-1)^e\binom{m}{e}(n-e)^q$$

时间复杂度已经做到了 $O(m\log q)$ 可以通过本题。
## AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+5,mod=998244353;
int fac[N],inv[N];
inline int ksm(int x,int y) {
    int ans=1;
    while(y) {
        if(y&1) ans=(ans*x)%mod;
        x=(x*x)%mod;
        y>>=1;
    }
    return ans;
}
int C(int x,int y) {
    return fac[x]*inv[y]%mod*inv[x-y]%mod;
}
signed main() {
    int n,m,q,k,ans=0;
    scanf("%lld %lld %lld %lld",&n,&m,&q,&k);
    if(m>q) {
        printf("0\n");
        return 0;
    }
    fac[0]=1;
    for(int i=1;i<N;i++) fac[i]=(fac[i-1]*i)%mod;
    inv[N-1]=ksm(fac[N-1],mod-2);
    for(int i=N-2;i>=0;i--) inv[i]=(inv[i+1]*(i+1))%mod;
    for(int i=0;i<=m;i++) {
        ans+=(i&1?-1:1)*C(m,i)%mod*ksm(n-i,q)%mod;
        ans=(ans+mod)%mod;
    }
    printf("%lld\n",ans*(n-m+1)%mod*ksm(k,q-m)%mod);
    return 0;
}
```





---

## 作者：int08 (赞：6)

## 前言
~~不知道 [Random](https://music.163.com/#/song?id=1909351846) 是不是指一首曲子。~~

有趣但是简单的数数题，感觉比 T2 简单。

都推式子？那我就从组合意义考虑吧！

# Solution

考虑我们在统计 $B$ 在操作完的所有可能序列中的出现次数，这个是很烦的，比如：

$$
A=[1,2,1,2,1],B=[1,2,1]
$$

发现有重叠部分，但是事实上这里对答案的贡献为 $2$，这是不好快速统计的。

如果考虑操作序列去匹配 $B$ 来更新答案是困难的，那么**正难则反**，考虑 $B$ 序列要出现在某一位置能匹配多少种操作序列。

为什么这是正确的？

因为同一个操作序列中如果多次出现 $B$ 要多次更新答案，反过来在多个位置匹配到同一个操作序列，也会多次更新答案，而且次数相等。

这时候我们惊喜地发现两件事：

第一、$B$ 序列出现在任意位置匹配的操作序列数相等，因为每次操作选择任意位置的概率相等。

所以我们只需要计算 $B$ 出现在 $[1,m]$ 的情况，乘上 $(n-m+1)$ 即可。

第二、类似的，$B$ 序列每个数具体是啥，对答案没有影响，因为修改位置是独立的，我修改某一个位置影响不到别的位置，而且修改为每个数的概率也相等。

~~所以我们压根不用输入第二行。~~

那么现在，修改的位置选择共 $n^q$ 种情况，修改成的数有 $k^q$ 种情况，分开计算，再乘起来即可。

### 修改成的数

要求：**对应的 $m$ 个位置最后一次出现的时候必须修改成对应的数。**

换句话说，不管我前面的修改位置怎么选，总有 $m$ 个操作我的修改成的数是固定的，而剩下的，要么修改位置大于 $m$ 我压根不管（我只统计 $B$ 出现于 $[1,m]$ 的答案）、要么后面这个位置还要改对，总之我想改成哪个数无所谓。

共有 $1^m\times k^{q-m}$ 中合法情况。

### 修改位置

要求：**$1$ 到 $m$ 每个位置至少被选中过一次**。

有多少种情况？~~我又不会了。~~

老规矩考虑**正难则反**，我统计不是每一个位置都出现过的情况。

即：我考虑有 $i$ 个位置没有出现过，选择这 $i$ 个位置有 $\binom{m}{i}$ 种选法，然后每次选位置，除了这 $i$ 个位置皆可选，共 $(n-i)^q$ 种情况。

然后用小学学过的容斥原理，$i$ 为奇数时减去，$i$ 为偶数时加上，就结束了。

最后，答案为：

$$
(n-m+1)\times k^{q-m}\times (n^q-\sum_{i=1}^{m}(-1)^i\binom{m}{i}(n-i)^q) 
$$

式子和其他题解有一点不同。

实现是简单的，$\binom{m}{i}$ 递推，逆元用快速幂实现。

## 后记

听我劝谏：人生苦短，正难则反……

Play like you never did before!

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int qp(int x,int y)
{
	int ans=1;
	for(int i=1,j=x;i<=y;i*=2,j=(j*j)%mod) if(y&i) ans=(ans*j)%mod;
	return ans;
}
int n,m,q,k,i,j,c[3141592],ans,anf;
signed main()
{
	cin>>n>>m>>q>>k;
	if(q>=m)
	{
		ans=((n-m+1)*qp(k,q-m))%mod;
		anf=qp(n,q);
		c[1]=c[m-1]=m;c[0]=c[m]=1;
		for(i=2;i<=(m+1)/2;i++) c[i]=c[m-i]=((c[i-1]*(m+1-i))%mod*qp(i,mod-2))%mod;
		for(i=1;i<=m;i++)
		{
			if(i%2)
				anf=(anf-qp(n-i,q)*c[i])%mod;
			else
				anf=(anf+qp(n-i,q)*c[i])%mod;
		}
		anf=(anf+mod)%mod;
		ans=(ans*anf)%mod;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：冷却心 (赞：3)

宝宝容斥。

考虑统计 $B$ 序列作为以某个位置开头的子串产生的贡献，即有多少个询问序列的结构序列包含这一段。发现 $B$ 不论出现在什么位置的贡献都相同，于是只统计 $B$ 出现在 $[1,m]$ 区间的贡献，然后乘以 $(n-m+1)$ 个位置。

然后考虑权值的分配，假设我们已经得到了一个操作序列 $\{p_q\}$，表示第 $i$ 次操作操作位置 $p_i$，需要对每次操作分配一个修改的权值 $w_i$。显然不在 $[1,m]$ 区间内和 $B$ 无关的位置可以任意填；对于这 $m$ 个关键位置，我们钦定最后一次操作到他的操作 $p$ 的权值 $w_p$ 为 $B_i$，其他操作可以任意。所以有 $m$ 次操作的权值固定，其他任意，方案数 $k^{q-m}$，所以我们只需要统计出合法的操作位置序列个数，然后乘以分配权值的方案。

一个操作位置序列是合法的当且仅当每个 $[1,m]$ 内的位置都被至少操作一次，不好直接统计，考虑容斥。我们钦定 $i$ 个位置没被操作，其他任意，方案数 $\binom{m}{i}(n-i)^q$，容斥系数 $(-1)^i$，然后做完了。答案是：

$$\text{Answer}=(n-m+1)k^{q-m}\sum_{i=0}^m(-1)^i\binom{m}{i}(n-i)^q.$$

代码很简单不放了。

---

## 作者：lailai0916 (赞：1)

## 原题链接

- [洛谷 P10116 [LMXOI Round 1] Random](https://www.luogu.com.cn/problem/P10116)

## 题意简述

初始时，长度为 $n$ 的序列全为 $0$。

进行 $q$ 次操作：每次可以选择一个位置，将其改为 $[1,k]$ 范围内的任意一个数。

给定一个长度为 $m$ 的匹配序列 $B\in[1,k]^m$，统计在所有可能的 $(nk)^q$ 个结果序列中，序列 $B$ 出现的总次数。

## 解题思路

我们注意到答案与 $B$ 无关。固定一个长度为 $m$ 的窗口，窗口总数为：

$$
n-m+1
$$

若窗口内漏掉 $i$ 个格子，则可选位置为 $n-i$，对应下标序列数为 $(n-i)^q$，故有：

$$
\sum_{i=0}^{m}(-1)^i\binom{m}{i}(n-i)^q
$$

在覆盖成立时，为使窗口最终等于给定 $B$，这 $m$ 个格子的最后一次写入被唯一确定，其余 $q-m$ 次任意，因子为：

$$
k^{q-m}
$$

综上，最终答案为：

$$
(n-m+1)\cdot k^{q-m}\cdot\sum_{i=0}^{m}(-1)^i\binom{m}{i}(n-i)^q
$$

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const int mod=998244353;
const int N=3000005;
ll inv[N],fac[N],jv[N];
void init()
{
	fac[0]=jv[0]=1;
	for(int i=1;i<N;i++)
	{
		inv[i]=i==1?1:(mod-mod/i)*inv[mod%i]%mod;
		fac[i]=fac[i-1]*i%mod;
		jv[i]=jv[i-1]*inv[i]%mod;
	}
}
ll C(ll n,ll m)
{
	if(n<m||m<0)return 0;
	return fac[n]*jv[n-m]%mod*jv[m]%mod;
}
ll Pow(ll x,ll y)
{
	x%=mod;
	ll res=1;
	while(y)
	{
		if(y&1)res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	init();
	ll n,m,q,k,a,b;
	cin>>n>>m>>q>>k>>a>>b;
	if(q<m)
	{
		cout<<0<<'\n';
		return 0;
	}
	ll sum=0;
	for(int i=0;i<=m;i++)
	{
		sum=(sum+Pow(-1,i)*C(m,i)%mod*Pow(n-i,q)%mod)%mod;
	}
	ll ans=sum*Pow(k,q-m)%mod*(n-m+1)%mod;
	cout<<(ans%mod+mod)%mod<<'\n';
	return 0;
}
```

---

## 作者：Genius_Star (赞：1)

### 思路：

容易发现 $B$ 是无用的，我们考虑求出钦定 $B$ 放在开头 $[1, m]$ 的贡献，然后成上 $n - m + 1$ 接口。

如何算贡献？分成两部分，一个是赋值序列，一个是赋值的位置序列，两个部分乘起来就是答案。

容易发现，对于所有的合法的赋值位置序列（即这 $m$ 个位置至少出现一次）的所有赋值方案 $k^q$，不管怎么样，我们只需要改这 $m$ 个位置最后一次赋值即可，对于一个赋值位置序列，这 $m$ 个位置一定是固定值，于是方案数是 $k^{q - m}$。

然后需要计算长度为 $q$ 的序列中 $[1, m]$ 至少出现一次的方案数，这是简单的，容斥钦定 $i$ 个没有出现：

$$\sum_{i = 0}^m (-1)^i  \binom{m}{i} (n - i)^q$$

于是答案是：

$$(n - m + 1) \times k^{q - m} \times \left(\sum_{i = 0}^m (-1)^i  \binom{m}{i} (n - i)^q \right)$$

时间复杂度为 $O(m \log n)$。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define add(x, y) ((x + y >= mod) ? (x + y - mod) : (x + y))
#define dec(x, y) ((x - y < 0) ? (x - y + mod) : (x - y))
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 3e6 + 10, mod = 998244353;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, m, q, k, ans;
int fac[N], inv[N];
inline int qpow(int a, int b){
	int ans = 1;
	while(b){
		if(b & 1)
		  ans = 1ll * ans * a % mod;
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return ans;
}
inline void init(){
	fac[0] = fac[1] = 1;
	for(int i = 2; i <= m; ++i)
	  fac[i] = 1ll * i * fac[i - 1] % mod;
	inv[m] = qpow(fac[m], mod - 2);
	for(int i = m - 1; i >= 0; --i)
	  inv[i] = 1ll * (i + 1) * inv[i + 1] % mod;
}
inline int binom(int n, int m){
	return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}
bool End;
int main(){
//	freopen("sequence.in", "r", stdin);
//	freopen("sequence.out", "w", stdout);
	n = read(), m = read(), q = read(), k = read();
	if(q < m){
		puts("0");
		return 0;
	}
	init();
	for(int i = 0; i <= m; ++i){
		int sum = 1ll * binom(m, i) * qpow(n - i, q) % mod;
		if(i & 1)
		  ans = (ans - sum + mod) % mod;
		else
		  ans = (ans + sum) % mod;
	}
	ans = 1ll * ans * (n - m + 1) % mod * qpow(k, q - m) % mod;
	write(ans);
	//cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 思路：

\@ 组合计数

主要难点在于切入点，切入点方向很多，但是只有几个（一个）是正确的方向。

显然 B 数组是不影响的。

然后匹配的位置也是不影响的，最后乘上一个 $n-m+1$ 的系数即可。

值也无所谓，最后乘上 $k^{q-m} $ 即可。

所以现在的条件就是 $[1, m]$ 必须被选到至少一次：

- 这里思考方向就很多了：

  - 一次性选好 $q$ 次操作，然后在其中选出 $m$ 次操作，再算剩余的贡献：
 
    - 不行，会算重。

  - 先提前定好 $m$ 次操作，然后把剩下的 $q-m$ 次操作插进去。
 
    - 可以写出 $mq^2$ 的 dp，稍微优化可得 $mq$，但是似乎很难进一步优化。
   
  - 先提前定好 $q-m$ 次操作，然后把剩下的 $m$ 次操作插进去。
 
    - 可能可行，但是我没写出来正确的式子。
   
- 直接算大概就这些思路，只能考虑容斥了：

  - 我们假设这 $m$ 次中有至少 $i$ 个点没选：
 
    - 则贡献是 $(n-i)^q $。
   
  - 做二项式容斥即可得：
 
    - $\sum_{i=0}^m(-1)^i\cdot C_m^i\cdot (n-i)^q $
   
最后答案即为：$(n-m+1)\cdot k^{q-m}\cdot \sum_{i=0}^m(-1)^i\cdot C_m^i\cdot (n-i)^q $。

### Code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 3e6+5;
const ll MOD = 998244353;

namespace Josh_zmf {
	
	ll N, M, Q, K, fac[Maxn], gac[Maxn];

	inline ll pow(ll a, int b) {
		ll c = 1;
		while(b) {
			if(b&1)	c = c*a %MOD;
			a = a*a %MOD, b >>= 1;
		}
		return c;
	}
	
	inline void init(int limit) {
		fac[0] = 1;
		for(int i=1; i<=limit; i++)	fac[i] = fac[i-1]*i %MOD;
		gac[limit] = pow(fac[limit], MOD-2);
		for(int i=limit; i; i--)	gac[i-1] = gac[i]*i %MOD;
	}
	
	inline ll C(int a, int b) {
		if(a<0 || b-a<0)	return 0;
		return fac[b]*gac[a]%MOD*gac[b-a]%MOD;
	}

	inline int main() {
		cin>> N>> M>> Q>> K, init(M);
		if(N < M or Q < M)	return cout<< "0\n", 0;
		ll ans = 0;
		for(int i=0; i<=M; i++) {
			ans += (i&1 ?-1 :1)*C(i, M)*pow(N-i, Q) %MOD;
			// printf("ans:%lld\n", ans);
		}
		ans = ans%MOD * (N-M+1)%MOD * pow(K, Q-M)%MOD;
		cout<< (ans+MOD)%MOD<< '\n';
		return 0;
	}

} bool ED;

int main() {
	Josh_zmf::main();
	cerr<< "Static Memory:: "<< (int)(abs(&ST-&ED)/1024./1024)<< "MB\n";
	return 0;
}

```

---

