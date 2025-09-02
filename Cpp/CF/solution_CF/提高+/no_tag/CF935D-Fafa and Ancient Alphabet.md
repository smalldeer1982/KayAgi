# Fafa and Ancient Alphabet

## 题目描述

Ancient Egyptians are known to have used a large set of symbols ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/9d7de2306d9a860acda322166418d2eb2e3f0f44.png) to write on the walls of the temples. Fafa and Fifa went to one of the temples and found two non-empty words $ S_{1} $ and $ S_{2} $ of equal lengths on the wall of temple written one below the other. Since this temple is very ancient, some symbols from the words were erased. The symbols in the set ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/9d7de2306d9a860acda322166418d2eb2e3f0f44.png) have equal probability for being in the position of any erased symbol.

Fifa challenged Fafa to calculate the probability that $ S_{1} $ is lexicographically greater than $ S_{2} $ . Can you help Fafa with this task?

You know that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/ef268df96da9b2e5c8e0a535fddc8c6d2cd6ef3b.png), i. e. there were $ m $ distinct characters in Egyptians' alphabet, in this problem these characters are denoted by integers from $ 1 $ to $ m $ in alphabet order. A word $ x $ is lexicographically greater than a word $ y $ of the same length, if the words are same up to some position, and then the word $ x $ has a larger character, than the word $ y $ .

We can prove that the probability equals to some fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/f3d3518082efa9b78c1dfc7f1e277e49a9674698.png), where $ P $ and $ Q $ are coprime integers, and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/9d39e8956ca5ae36ed529a9998b81f8c971b6e39.png). Print as the answer the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/9db35f1977f217526a6ba86931500db815df9867.png), i. e. such a non-negative integer less than $ 10^{9}+7 $ , such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/377c132d9f19a05fde19ac3441d728f7ce7dc195.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/067e520c210c31f6438c25961d459da6fb1e4454.png) means that $ a $ and $ b $ give the same remainders when divided by $ m $ .

## 说明/提示

In the first sample, the first word can be converted into ( $ 1 $ ) or ( $ 2 $ ). The second option is the only one that will make it lexicographically larger than the second word. So, the answer to the problem will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/6816555efb79ba88b199193ab2e0de2995d92d86.png), that is $ 500000004 $ , because ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/6da52dcf52e727f86b710fd73b86d4595daebaef.png).

In the second example, there is no replacement for the zero in the second word that will make the first one lexicographically larger. So, the answer to the problem is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/286eb02d12e6632b3327f1c14fd5fd72758c676f.png), that is $ 0 $ .

## 样例 #1

### 输入

```
1 2
0
1
```

### 输出

```
500000004
```

## 样例 #2

### 输入

```
1 2
1
0
```

### 输出

```
0
```

## 样例 #3

### 输入

```
7 26
0 15 12 9 13 0 14
11 1 0 13 15 12 0
```

### 输出

```
230769233
```

# 题解

## 作者：Acc_Robin (赞：2)

这是一道概率题，其实没必要DP，代码也不长.

首先，我们需要明确一点：

如果在第 $i$ 位有 $a[i]<b[i]$，那么对于$\forall j>i$，$a[j]$ 与 $b[j]$ 的大小关系都没有意义.

我们考虑可能出现哪些情况：

1. 若$a[i]=0 \land b[i]\ne 0$

这种情况下为了使 $a>b$，$a[i]$ 的取值有两种可能：

要么在当前位置让 $a[i]>b[i]$，直接获胜；要么在当前位置先让 $a[i]=b[i]$，留着在之后处理。

对应的概率分别为 $\frac{m-b[i]}{m}$ 和 $\frac 1m$。

2. 若$a[i]\ne0 \land b[i]= 0$

这种情况下还是两种可能，$b[i]<a[i]$ 或者 $b[i]=a[i]$，对应的概率分别为 $\frac{a[i]-1}{m}$ 和 $\frac 1m$。

3. 若$a[i]= 0 \land b[i]=0$

这种情况下，$a[i]>b[i]$ 的概率即为 $\frac{m-1}{2m}$ ，而相等的概率为 $\frac 1{m}$.

4. 若$a[i]\ne 0 \land b[i]\ne 0$

对于这种情况的分析，就引出了一个之前深藏已久的一个问题：

**转移到当前情况的概率是什么？**

我们不妨记录一下，从一开始，每一位 $a[i]$ 都等于 $b[i]$ 的概率，记为 $lst$（last）。

因此在之前所有的情况算出的概率都要乘以$lst$.毕竟如果不能转移到这个状态，概率也没什么意义了.

在处理 $a[i]\ne0 \land b[i]\ne 0$ 的情况时，我们需要考虑在这一位上 $a[i]$ 与 $b[i]$ 的大小关系:

若 $a[i]=b[i]$ 则接着比较，对答案没有影响；

若 $a[i]<b[i]$ 那么之前算出的答案直接输出即可.

若 $a[i]>b[i]$ 那么 $a>b$ 的概率就要加上 $lst$.

如果你还是不太懂，可以参考我的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
	#define int long long
	const int mod=1e9+7,N=1e5+10;
	int qpow(int a,int b){
		int res=1;
		for(;b;a=a*a%mod,b>>=1)if(b&1)res=res*a%mod;
		return res;
	}
	int frac(int a,int b){ 
		return a*qpow(b,mod-2)%mod;
	}//frac(a,b)表示分数 a/b
	int n,m,a[N],b[N],ans,lst=1;
	void work(){
		cin>>n>>m;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)cin>>b[i];
		for(int i=1;i<=n;i++){
			if(a[i]&&b[i]&&a[i]!=b[i])cout<<(ans+lst*(a[i]>b[i]))%mod,exit(0);
			else if(!a[i]&&!b[i])ans=(ans+lst*frac(m-1,2*m)%mod)%mod,lst=lst*frac(1,m)%mod;
			else if(!a[i]&&b[i])ans=(ans+lst*frac(m-b[i],m)%mod)%mod,lst=lst*frac(1,m)%mod;
			else if(a[i]&&!b[i])ans=(ans+lst*frac(a[i]-1,m)%mod)%mod,lst=lst*frac(1,m)%mod;
		}
		cout<<ans;
	}
	#undef int
}
int main(){
	return Acc::work(),0;
}
```

---

## 作者：AL76 (赞：2)

题意:给两个长度为n的数列,每个数列的数字范围是1-m,有可能出现缺失的部分(用0表示),在缺失的部分每个数字出现的概率相同(都是1/m),问最后a的字典序比b的大的概率.输入是 n,m 之后两行每行n个数,分别代表序列a,b.最后输出概率对1e9+7取模

提示:分数无法取模,所以要用逆元~另外要注意一下取模不然会爆

貌似有更简单的转移方式,只用一维就可以,也可以滚动数组写,但是我太弱了qwq

分几种情况讨论然后直接转移就行啦,这道题其实就是一个递推
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 100010
#define mod 1000000007 
#define ll long long
using namespace std;
int n,m;
int a[maxn],b[maxn];
ll inv[maxn],f[maxn][2];//f[i][1]表示到i位为止,a>b的概率
ll fp(ll x,ll a){//在jms学到的神奇写法
    ll ret=1;
    for(x%=mod;a;a>>=1,x=x*x%mod)
        if(a&1) ret=ret*x%mod;
    return ret; 
}
int main(){
    scanf("%d%d",&n,&m);//长度为n 字母表中有m个字母
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    f[0][0]=1;
    ll invm=fp(m,mod-2),inv2=fp(2,mod-2);
    for(int i=1;i<=n;i++){
        if(a[i]>b[i]&&b[i]) //这一位都已经确定,直接转移即可
            f[i][1]=(f[i-1][1]+f[i-1][0])%mod;
        else if(a[i]<b[i]&&a[i]) 
            f[i][1]=f[i-1][1];//f[i][0]=0
        else if(a[i]==b[i]&&a[i])
            f[i][1]=f[i-1][1],f[i][0]=f[i-1][0]%mod;
        else if(!a[i]&&!b[i]){
            f[i][0]=f[i-1][0]*invm%mod;
            f[i][1]=(f[i-1][1]+((f[i-1][0]*((1-invm)%mod+mod)%mod)%mod*inv2)%mod)%mod;//相等的概率是1/m,剩下的对半分
        }
        else if(!a[i]){
            f[i][0]=f[i-1][0]*invm%mod;
            f[i][1]=(f[i-1][1]+(f[i-1][0]*(invm*((m-b[i])%mod+mod)%mod)%mod)%mod)%mod;
        }
        else if(!b[i]){
            f[i][0]=f[i-1][0]*invm%mod;
            f[i][1]=(f[i-1][1]+(f[i-1][0]*(invm*((a[i]-1)%mod+mod)%mod)%mod)%mod+mod)%mod;
        }
    }
    printf("%lld\n",(f[n][1]%mod+mod)%mod);
    return 0;
}
```

---

## 作者：white_tiger_yyyy (赞：1)

讲一个很暴力的方法。

发现假如当前 $a_i\ne b_i$，就不需要再向下枚举了，于是拥有了分类讨论的雏形。

我们设 inv 代表进行到这一步的概率，可分为以下四种情况：

1. $a_i>0,b_i>0$。此时假如 $a_i=b_i$，略过；若 $a_i>b_i$，$ans\to ans+inv$，退出循环；否则直接退出循环。
2. $a_i>0,b_i=0$。此时只需考虑确定的可增加概率和 inv。易得 $inv\to \frac{inv}{m},ans\to ans+(a_i-1)inv$。
3. $a_i=0,b_i>0$。$inv\to\frac{inv}{m},ans\to ans+(m-b_i)inv$。
4. $a_i=0,b_i=0$。$ans\to ans+\frac{m(m-1)}{2m^2}inv,inv\to\frac{inv}{m}$。

以上操作都是在 $\bmod\ p$ 意义下的。时间复杂度 $O(n\log_2n)$，预处理一些快速幂可优化至 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll p=1e9+7;
const int N=1e5+5;
ll qpow(ll x,int y){
	ll re=1;
	while(y){
		if(y&1) re=re*x%p;
		x=x*x%p;
		y>>=1;
	}return re;
}int n,a[N],b[N];
ll ans,inv=1,m;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	for(int i=1;i<=n;i++){
		if(a[i]&&b[i]){
			if(a[i]==b[i])
				continue;
			if(a[i]>b[i])
				ans=(ans+inv)%p;
			break;
		}if(!a[i]&&!b[i]){
			ans=(ans+m*(m-1)%p*qpow(m*m*2%p,p-2)%p*inv%p)%p;
			inv=inv*qpow(m,p-2)%p;
		}else if(!a[i]){
			inv=inv*qpow(m,p-2)%p;
			ans=(ans+(m-b[i])*inv%p)%p;
		}else{
			inv=inv*qpow(m,p-2)%p;
			ans=(ans+(a[i]-1)*inv%p)%p;
		}
	}cout<<ans;
	return 0;
}
```

---

## 作者：Acfboy (赞：1)

看了一眼题，想着这 dp 个锤子，直接计数不就好了？  
然后……从下午交到晚上，终于过了。

如果不 dp 的话还是有些细节的，所以这是一篇不用 dp 的题解，帮帮那些不爱 dp 的选手。

1. 找到第一个两个字符串（记作 $s$ 和 $t$）不同的地方，记作 $fin$。
2. 求一遍 $s$ 和 $t$ 中 $0$ 的个数的后缀和，记作 $f$
2. 对于前 $fin$ 个位置，每个位置 $i$ 满足
	1. $s_i = 0, t_i \ne 0 \to (m-t_i) \cdot m^{f_{i+1}} \cdot m^{pre}$ 其中 $pre$ 指前面出现的两个都为 $0$ 的个数。整个式子应该挺好理解的，即当前位置 $s$ 能填的乘上后面的所有填法，再乘上前面每个全是 $0$ 位能取的方案。如果不是全 $0$ 那么方案唯一。
   2. $s_i \ne 0, t_i = 0$ 和上面相似。
   3. $s_i = 0, t_i = 0$ 那么当前能填的变为 $\frac{m(m-1)}{2}$

可是这样还没完呢，所有的“当前位能填的”为了不重复，没有考虑两个相同的情况，而如果 $s_{fin} > t_{fin}$, 那么前面时可以填成相同的，所以最后还要补上前面都相同的情况。

1. 若 $s_{fin}$ 和 $t_{fin}$ 只有一个是 $0$, 那么当前位只有一种填法，所以答案是 $m^{f_{i+1}} \cdot m^{pre}$。
2. 两个都是 $0$, 当前有 $m$ 种填法。

最后是代码。

```cpp
#include <cstdio>
#define int long long
const int N = 100005, P = 1000000007;
int ans, n, m, s[N], t[N], f[N], pre;
int Pow(int a, int b) {
	int an = 1;
	for( ; b; b >>= 1, a = a * a % P)
		if(b & 1) an = an * a % P;
	return an;
}
signed main() {
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &s[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &t[i]);
	for(int i = n; i >= 1; i--) f[i] = f[i+1] + !s[i] + !t[i];
	int fin = -1;
	for(int i = 1; i <= n; i++)
		if(s[i] != 0 && t[i] != 0 && s[i] != t[i]) { fin = i+1; break; }
	for(int i = 1; i < ((fin > 0) ? fin : (n+1)); i++) 
		if(s[i] == 0 && t[i] != 0) 
			ans = (ans + (m-t[i]) * Pow(m, f[i+1]) % P * Pow(m, pre) % P) % P;
		else if(t[i] == 0 && s[i] != 0) 
			ans = (ans + (s[i]-1) * Pow(m, f[i+1]) % P  * Pow(m, pre) % P) % P;
		else if(t[i] == 0 && s[i] == 0)
			ans = (ans + m*(m-1)/2 % P * Pow(m, f[i+1]) % P * Pow(m, pre) % P) % P, pre++;
	if(fin != -1 && s[fin-1] > t[fin-1]) {
		if(fin-2 && !!s[fin-2] + !!t[fin-2] == 1) ans = (ans + Pow(m, pre) * Pow(m, f[fin-1]) % P) % P;
		else ans = (ans + Pow(m, pre) * Pow(m, f[fin]) % P) % P; 
	}
	printf("%lld", Pow(Pow(m, f[1]), P-2) * ans % P);
	return 0;
}
```

---

## 作者：Chen_Johnny (赞：0)

# CF935D Fafa and Ancient Alphabet 题解
## 题意
这道题的翻译很敷衍，相信很多人都看不懂，那我也是只能花费一个小标题翻译一下了。

这道题是由两个长度为 $n$ 的数字串（每个数字 ${a | 1\leqslant a \leqslant m, a \in Z^+}$ )，如果 $a$ 为 $0$，意味着这个随便填什么都可以。求第一个字符串大于第二个字符串的概率，结果对 $10^9 + 7$ 取余。
## 思路
这道题刚一看到大家估计都会有一点灵感。大家如果还是没有想法的可以回顾去年的 [[CSP-J 2024] 小木棍](https://www.luogu.com.cn/problem/P11229)。如果有的话，相信大家想到的都是两个大字“贪心”。

至于怎么想到的，就只有靠经验了。

贪心策略：对于任意一个 $i$：

1. 如果 $a_i = 0$ 且 $b_i \ne 0$：

看到这种情况，我们不难发现，有两种情况可以让 $a$ 比 $b$ 大，要么直接比他大，或者先一样，后面比他大，概率分别为：$\frac{(m - b_i)}{m}$ 和 $\frac{1}{m}$。

2. 如果 $a_i \ne 0$ 且 $b_i = 0$：

这种情况和之前一样，要么直接比他大，要么先一样，后面比他大，概率分别为：$\frac{(a_i - 1)}{m}$ 和 $\frac{1}{m}$。

3. 如果 $a_i \ne 0$ 且 $b_i \ne 0$：

这种就只能听天尤命了，是怎么样就是怎么样，不是 $0$ 就是 $1$。

4. 如果 $a_i = 0$ 且 $b_i = 0$：

这种就要考虑上一位的情况了，因为这个是不确定的。

如果 $a_{i - 1} < b_{i - 1}$, 那么显然这一位已经没救了，干脆输出结束了。

如果 $a_{i - 1} > b_ {i - 1}$，那么这次的概率就是上次的概率与此次概率的和

如果 $a_ {i - 1} = b_ {i - 1}$，那么可以说这一位是毫无意义的，继续比较就行了
## 总结
可能你并没有听懂上面的，那我总结一下吧，假设估算概率的函数为 $p$，则：
$$p _{(i)} = \begin{cases}
   0 &\text{if } i=n \\
   0 &\text{if } i<n,a_i\ne 0,b_i\ne 0, a_i<b_i\\
   1 &\text{if } i<n,a_i\ne 0,b_i\ne 0, a_i>b_i\\
   p_{(i+1)} &\text{if } i<n,a_i\ne 0,b_i\ne 0, a_i=b_i\\
   \frac{m-b_i}{m} + \frac {p_{(i+1)}}{m}&\text{if } i<n,a_i = 0,b_i\ne 0\\
   \frac{a_i - 1}{m} + \frac {p_{(i+1)}}{m}&\text{if } i<n,a_i \ne 0,b_i= 0\\
   \frac{m-1}{2m} + \frac {p_{(i+1)}}{m}&\text{if } i<n,a_i = b_i= 0\\
\end{cases}$$
## 代码
你只需要按照上面的总结 DFS 或 DP 或 递推就可以了，没有任何技术含量。

---

## 作者：Scrolling_Ball (赞：0)

拿到题目，看到 $P\times Q^{-1}$ 很显然想到是一道概率 DP 或者说是什么推式子的，但是 $n$ 只有 $10^5$ 所以考虑概率 DP。

因为题目要求的是字典序大，所以说如果 $a$ 的第 $i$ 位比 $b$ 的大，那么  $i+1\sim n$ 无论怎么填都是符合条件的，同理，如果 $a_i<b_i$ 那么就肯定不满足条件。（这里的 $i$ 是第一个 $a,b$ 不相同的那一位）

所以 DP 状态即为 $dp_{i,j}$，$i$ 表示现在枚举到第几位，$j=1/0$ 表示 $1\sim i$ 这段区间 $a$ 和 $b$ 是大于还是等于。

然后呢就是讨论 6 种情况了：

1. 对于 $a[i]\ne0$，$b[i]\ne0$，$a[i]>b[i]$：显然前面是大于或者等于都能转移到 `dp[i][1]` 上，而 `dp[i][0]` 不成立。

2. 对于 $a[i]\ne0$，$b[i]\ne0$，$a[i]=b[i]$：$i$ 这个位置对答案没有影响，所以 $dp[i][0]$ 和 $dp[i][1]$ 方案数就跟前面一次的一样。

3. 对于 $a[i]\ne0$，$b[i]\ne0$，$a[i]<b[i]$：只有前面有大的才符合题意，所以 $dp[i][1]$ 就等于 $dp[i-1][1]$。

4. 对于 $a[i]=0$，$b[i]\ne0$：根据题意，0 是任意的一个，所以 $a=b$ 的概率为 $\small\dfrac{1}m$，$a>b$ 的概率为 $\small\dfrac{m-b[i]}m$。

5. 对于 $a[i]\ne0$，$b[i]=0$：同理 $a=b$ 为 $\small\dfrac{1}m$，$a>b$ 为 $\small\dfrac{a[i]-1}m$。

6. 对于 $a[i]=0$，$b[i]=0$：一共有 $m^2$ 种取法，满足相同的有 $m$ 种，大于的有 $0+1+2+\cdots+m-1$ （枚举 $a[i]$ 随机到了哪个数），即 $\small\dfrac{m\times (m-1)}2$ 种。

然后就没了，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
ll p = 1e9 + 7;
int n, m;
int a[N], b[N];
ll f[N][2];
ll ksm(ll a, ll b)
{
	ll ans = 1;
	while(b)
	{
		if(b & 1)ans = ans * a % p;
		a = a * a % p;
		b /= 2;
	}
	return ans;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++ )
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i ++ )
		scanf("%d", &b[i]);
	ll inv = ksm(m, p - 2);
	f[0][0] = 1;
	for(int i = 1; i <= n; i ++ )
		if(a[i] != 0)
		{
			if(b[i] != 0)
			{
				if(a[i] > b[i])f[i][1] = (f[i - 1][1] + f[i - 1][0]) % p;
				else if(a[i] == b[i])
				{
					f[i][1] = f[i - 1][1];
					f[i][0] = f[i - 1][0];
				}
				else f[i][1] = f[i - 1][1];
			}
			else
			{
				f[i][1] = (f[i - 1][1] + f[i - 1][0] * (a[i] - 1) % p * inv) % p;
				f[i][0] = f[i - 1][0] * inv % p;
			}
		}
		else
		{
			if(b[i] != 0)
			{
				f[i][1] = (f[i - 1][1] + f[i - 1][0] * (m - b[i]) % p * inv) % p;
				f[i][0] = f[i - 1][0] * inv % p;
			}
			else
			{
				f[i][1] = (f[i - 1][1] + f[i - 1][0] * (m - 1) % p * 500000004 % p * inv % p) % p;
				f[i][0] = f[i - 1][0] * inv % p;//可以抵消掉一个 m。
			}
		}
	printf("%lld", f[n][1]);
	return 0;
}
```

---

