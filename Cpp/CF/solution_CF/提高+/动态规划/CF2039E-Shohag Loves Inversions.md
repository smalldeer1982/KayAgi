# Shohag Loves Inversions

## 题目描述

# Shohag Loves Inversions


给你一个数列，初始数列为 $ a = [0, 1] $ ，现在重复进行以下操作若干次:
- 将当前数组中逆序对个数k插入当前数组中任意一个位置，包括开头或者结尾。

举个例子, 如果 $ a = [4, 6, 2, 4] $ , 则逆序对个数是 $ k = 3 $ . 所以可以通过操作，得到以下数组: $ [\textbf{3}, 4, 6, 2, 4] $ , $ [4, \textbf{3}, 6, 2, 4] $ , $ [4, 6, \textbf{3}, 2, 4] $ , $ [4, 6, 2, \textbf{3}, 4] $ , 和$ [4, 6, 2, 4, \textbf{3}] $ 。

给一个整数 $ n $，求通过操作可以得到多少种长度为$ n $的不同数列，方案数对对 $ 998\,244\,353 $ 取模。

逆序对的对数就是有多少个二元组，满足  $ i < j $ 并且 $ a_i > a_j $ 。

## 说明/提示

对于第一个样例, 以下$ 5 $种数列可以通过操作得到  
- $ [0, 1] \rightarrow [0, \textbf{0}, 1] \rightarrow [0, 0, 1, \textbf{0}] $ ,
- $ [0, 1] \rightarrow [0, \textbf{0}, 1] \rightarrow [0, 0, \textbf{0}, 1] $ ,
- $ [0, 1] \rightarrow [0, 1, \textbf{0}] \rightarrow [0, 1, 0, \textbf{1}] $ ,
- $ [0, 1] \rightarrow [0, 1, \textbf{0}] \rightarrow [0, 1, \textbf{1}, 0] $ ,
- $ [0, 1] \rightarrow [0, 1, \textbf{0}] \rightarrow [\textbf{1}, 0, 1, 0] $ .

## 样例 #1

### 输入

```
4
4
2
7
69```

### 输出

```
5
1
682
325188814```

# 题解

## 作者：__little__Cabbage__ (赞：4)

挺巧妙的一道数数 dp，不过由于是数列，所以能在 Wolfram Mathematica 上推出来也是好玩的。

设序列 $a$ 的逆序对数量为 $k$，则当 $k > 1$ 时，加入的数一定 $\ge$ 序列中所有的数，~~This gives us a way to control everything！~~

设 $f_i$ 为长度为 $i$ 且 $k > 1$ 的序列能构成多少种最终解（即长度为 $n$ 的序列）。转移是容易的，可以考虑在末尾插入几次 $k$（逆序对数不变）后再在中间插入，假设在末尾插入了 $j$ 次，则在中间插入后就转化为了 $f_{i+j+1}$ 的情况，所以可以推出转移方程：

$$f_i = \sum _{j=0} ^{n-i-1} (i \times f_{i+j+1}) + 1$$

其中，乘上一个 $i$ 是因为在中间插入的时候共有 $i$ 种情况，最后 $+1$ 是因为如果一直在结尾插入，也会构成一个解。

可以后缀和优化做到 $O(n)$。

然后统计答案，我们发现，在长度为 $i$ 的序列中，假设 $k$ 刚刚 $>1$，也就是刚刚满足我们上面 dp 的条件，此时序列为 ${\color{#66CCFF} 0,\ldots,0},{\color{EEAADD} 1},0,1,\ldots,1$ 并在第一个 $\color{EEAADD} 1$ 前面加一个 $0$ 得到，若第一个 $\color{EEAADD} 1$ 的位置为 $j$，则方案数为 $\sum \limits _{j=2} ^{i-2} j = \frac {i \times (i-3)} 2$。

注意到只有长度 $> 3$ 时才会产生 $k > 1$ 的序列。再加上 $k \le 1$ 的序列（$0,\ldots,0,{\color{#66CCFF} 1,0},1,\ldots,1$），则答案为：

$$
n-1 + \sum _{i=4} ^{n} \frac {i \times (i-3)} 2 \times f_i
$$

---

## 作者：Sanyueyetu (赞：2)

听说noip赛前发题解会有好运气，赶紧来一发


---

[题目link](https://codeforces.com/contest/2039/problem/E)

首先我们可以定义逆序对的个数变多为“升级”，发现若将第 $i$ 个数 $x_i$ 放在第 $pos$ 个位置，那逆序对增加的数量就是 $[pos+1,i]$ 区间内小于 $x_i$ 的数的数量，因此将一个数放在序列的末尾并不会“升级”。

我们继续模拟这个过程，会发现此时 $x_{i+1}=x_i$，我们会再次重复这个决策：$[pos+1,i]$ 区间内有小于 $x_i$ 的数就升级，否则下一个数仍然是 $x_i$。我们可以发现，整个过程其实就是不断地重复以下这个循环：把若干个相同的数放在序列的末尾，然后再把一个跟它们相同的是放在满足 $[pos+1,i]$ 区间内有小于 $x_i$ 的数的位置上，接着升级，对下一个数进行操作。

定义 $f_i$ 表示第 $i$ 次操作升级的方案数，我们可以枚举上一次升级时的操作次数 $j$，得到转移方程：
$$
f_i = \sum_{j = 1}^{i-1} f_j\times j
$$

我们只要用一个变量 $sum$ 记录 $\sum_{j = 1}^{i-1} f_j\times j$ 的值就可以轻松完成 $O(1)$ 转移。

但是以上的方程有一个漏洞，就是当前序列只有0和1时的情况。容易发现当前序列只有 $0$ 和 $1$，并且当前并未升级到 $2$ 的情况只有两种：$(0\dots0)1$ 和 $(00\dots00)10(111\dots11)$。我们发现，第一种情况无论下一个操作是什么都无法完成升级，只需要在最后对 $ans$ 加一即可。因此只需要另外用一个 $cnt$ 数组统计第二种情况对 $f$ 数组的贡献即可。

具体来说，只有在第二种序列的那一串 $0$ 中间放入一个 $1$ 才能升级。所以我们用 $j$ 表示当前第二种序列的那一串 $0$ 后面紧跟着的 $1$ 的位置 $cnt_i=\sum_{j = 2}^{i-2} j$，直接等差数列求和即可。

### AC Code

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int f[1000010],sum,cnt[1000010],ans;
int n,q;
signed main(){
	scanf("%lld",&q);
	while(q--){
		scanf("%lld",&n);
		if(n==2){
			printf("1\n");
			continue;
		}
		if(n==3){
			printf("2\n");
			continue;
		}
		for(int i=4;i<=n;i++){
			cnt[i]=i*(i-3)/2;
			cnt[i]%=mod;
		}
		sum=ans=0;
		for(int i=4;i<=n;i++){
			f[i]=(sum+cnt[i])%mod;
			sum=(sum+f[i]*i)%mod;
			ans=(ans+f[i])%mod;
		}
		ans=(ans+n-2+1)%mod;
//这里的n-2表示长度为n的(00.....00)10(111....11)串数量
//+1计算了(00...000)1这种串的情况
		printf("%lld\n",ans);
	}
}
```

---

## 作者：SUNCHAOYI (赞：1)

**题意：** 初始时 $a = [0,1]$，每次更新将 $a$ 逆序对的数量 $k$ 插入其中，求最终长度为 $n$ 的序列的数量。

以下均设当前的序列逆序对的数量为 $k$。

首先需要通过观察得出一个性质，当序列**第一次**出现 $k > 1$ 的时候，若将 $k$ 插在中间的位置，会使得 $k' > k$，在末尾插入则 $k' = k$。设 $f_i$ 表示长度为 $i$ 且当前**第一次**出现 $k > 1$ 时，变为长度为 $n$ 的序列的数量。剩下还有 $n - i$ 次操作，可以将 $k$ 均插入末尾，或者在末尾插入若干个以后再将 $k$ 插入中间的 $i$ 个位置之一，因此可以得到以下转移：

$$
f_i = i \times \sum \limits_{j = 0}^{n - i - 1} f_{i + j + 1} + 1
$$

现在我们讨论整一个序列均为 $k \le 1$ 的情况。显然 $k = 0$ 时就只有 $\underbrace{00 \cdots 0}_{n - 1}1$ 这一种。而 $k = 1$ 时应为 $\underbrace{00 \cdots 0}_{x}010\underbrace{11\cdots1}_{n - x - 3}$，其中 $x \in [0,n - 3]$，故有 $n - 2$ 种。所以说，$k \le 1$ 时，共有 $n - 1$ 种。

最后考虑 $k \le 1$ 转移至 $k > 1$ 的情况，显然只有 $k = 1$ 时才有可能。因此对于 $\underbrace{00 \cdots 0}_{x}010\underbrace{11\cdots1}_{n - x - 3}$ 类型的串，我们需要找到第一个 $1$ 所出现的位置。不难发现第一次出现 $k > 1$ 的序列时至少由长度为 $3$ 的 $010$ 转移而来，共会产生 $2$ 个长度为 $4$ 且 $k > 1$ 的串 $1010,0110$。一般化的，若在长度为 $i$ 时第一次出现 $k > 1$，则这个长度为 $i$ 的串共会有 $\sum \limits_{j = 2}^{i - 1} = \frac{i(i - 3)}{2}$ 种情况。举个例子，若 $i = 5$，则可能由 $0010,0101$ 转移出 $5$ 种情况。

综上所述，最后的答案就是 $n - 1 + \sum \limits _{i = 4}^n \frac{i(i - 3)}{2} f_i$。直接后缀和进行处理即可，时间复杂度 $O(n)$。

----

参考代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e6 + 5;
const int MOD = 998244353;
const ll inv_2 = 499122177;
inline int read ();
int t,n;ll sum,ans,dp[MAX]; 

int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	t = read ();
	while (t--)
	{
		n = read ();
		sum = ans = 0;
		for (int i = n;i >= 4;--i)
		{
			dp[i] = (i * sum % MOD + 1) % MOD;
			sum = (sum + dp[i]) % MOD;
			ans = ans + 1ll * i * (i - 3) % MOD * inv_2 % MOD * dp[i] % MOD;
		}
		ans = (ans + n - 1) % MOD;
		printf ("%lld\n",ans);
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：FugiPig (赞：1)

# 题解 [CF2039E - Shohag Loves Inversions](https://codeforces.com/contest/2039/problem/E)
设当前序列 $a$ 的逆序对数量为 $k$，发现当 $k>1$ 以后，每次的 $k$ 构成一个单调不降序列，如果将 $k$ 插在末尾，则 $k$ 不变，否则 $k$ 一定增加。这启发我们 $a$ 可以生成的长度为 $n$ 的序列的数量与 $a$ 和 $k$ 的具体值都无关，因而我们可以设 $dp_i$ 为长度为 $i$ 的 $k>1$ 的序列 $a$ 可以生成多少种长度为 $n$ 的序列。

发现可以把 $k$ 插在末尾任意 $j\ge0$ 次，而后将 $k$ 插在中间，显然插在中间有 $i$ 种方法，或者每次都加在末尾直到长度为 $n$，因而转移方程为：

$$dp_i=\sum_{j=0}^{n-i-1}(i\cdot dp_{i+j+1})+1$$

可以用后缀和优化计算。

接着我们考虑计算 $k\le1$ 的情况，显然 $k=1$ 的序列形如 $0,\dots,0,[0,1,0],1,\dots,1$，则对于长度为 $i$ 的刚达到 $k>1$ 的**初始**序列，其一定是由长度为 $i-1$ 的 $0,\dots,0,[0,1,0],1,\dots,1$ 序列在第一个 $1$ 前的一个位置再添加一个 $1$ 得来，设第一个 $1$ 的位置为 $j$，则方法数为：

$$\sum_{j=2}^{i-2}j=\frac{i(i-3)}{2}$$

而始终 $k\le1$ 的序列形为 $0,\dots,0,[0,1,0],1,\dots,1$ 或 $0,0,\dots,0,1$ 共 $n-1$ 种，因而答案为：

$$n-1+\sum_{i=4}^{n}\frac{i(i-3)}{2}dp_i$$

时间复杂度 $O(n)$。

代码：
```cpp
#include<iostream>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,l,r) for(int i=(l);i>=(r);i--)
using namespace std;
const int mod=998244353,maxn=1e6+5;
typedef long long ll;
ll dp[maxn];
ll qpow(ll a,int b){
	ll res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int main()
{
	int it;
	cin>>it;
	ll inv=qpow(2,mod-2);
	while(it--){
		int in;
		scanf("%d",&in);
		ll sum=0,ans=0;
		per(v1,in,3){
			dp[v1]=(v1*sum+1)%mod;
			sum=(sum+dp[v1])%mod;
			ans=(ans+dp[v1]*ll(v1-3)%mod*v1%mod*inv%mod);
		}
		ans=(ans+in-1)%mod;
		printf("%lld\n",ans);
	} 
	return 0;
}
```

---

## 作者：arrow_king (赞：1)

~~自己找到的规律才是自己的。OEIS 不算！~~

感谢本题送给我一个 CM。~~要不是 C2 分还能再高点~~

我们可以注意到当此序列有逆序对的时候，逆序对一定大于等于序列中任何一个数。考虑设计一个朴素的 dp 状态，$dp_{i,j}$ 表示考虑到长度为 $i$ 的序列，序列中出现了 $j$ 次 $k$，其中 $k$ 是整个序列的逆序对。

那么当在整个序列的开头添加一个 $k$ 的时候逆序对数量不会发生变化，此时 $j$ 要加 $1$；而在中间添加 $k$ 的时候逆序对数量一定变大，所以在添加完后序列中逆序对数值出现次数会变为 $0$。因此写出转移方程：
$$
dp_{i-1,j}\rightarrow dp_{i,j+1}\\
dp_{i-1,j}\times(i-j-1)\rightarrow dp_{i,0}
$$
之所以乘上 $i-j-1$ 而不是 $i-1$ 是因为要考虑所有和 $k$ 相同的位置，把它们的贡献去掉。

然而这样还不够，我们需要枚举在整个序列逆序对的数量为 $0$ 时序列的长度。因此这样的复杂度是 $O(n^3)$。（

暴力代码：

```cpp
for(int p=3;p<=n;p++) {//p枚举初始 000...0010 的长度
	dp[p][1]=1;
	for(int i=p+1;i<=n;i++) {
		for(int j=0;j<=i;j++) {
			dp[i][0]=(dp[i][0]+dp[i-1][j]*(i-j-1)%mod)%mod;
			dp[i][j+1]=(dp[i][j+1]+dp[i-1][j])%mod;
		}
	}
	ll sum=0;
	for(int j=0;j<=n;j++) sum=(sum+dp[n][j])%mod;
	ans+=sum;
}
printf("%lld\n",ans+1);//ans+1是统计 00...01 的情况
```

然而这样太慢也太没有意义，我们直接从 $f_{i,j}=\sum_{p}dp_{p,j}$ 下手。

我们可以发现，$f_{i,j}$ 有和 $dp_{i,j}$ 相同的转移式子。唯一有不同的是每次转移前我们需要给 $f_{i-1,1}$ 加上 $1$（从 dp 的过程中就可以发现）。因此我们考虑快速转移，所幸这是可以的。

对于第 $i$ 行，除去上面的额外贡献，$f_{i,j}$ 会增加 $f_{i-1,j-1}$；而对于 $f_{i,0}$，对于每个 $i$ 来说转移系数是相同且有规律的，即 $i-1,i-2,i-3,\dots,1$。

所以我们对每一行维护两个和：

- $ans_i$，第 $i$ 行所有 $f$ 的和，同时也是最终的答案（当然不算那个 $000\dots01$ 的特殊情况）；
- $S_i$，$\sum_{j=0}^i(i-j)f_{i,j}$，是为了方便转移而维护的变量。
- 当 $n\le 3$ 时特判，否则初始时 $S_3=7$，$ans_3=3$。

考虑从 $i-1$ 行走到 $i$ 这一行：

- 首先我们要先计算 $f_{i,0}$。由于 $f_{i,0}$ 上贡献系数的特殊性，我们只需要给它补充上 $f_{i-1,0}+f_{i-1,1}+\dots+f_{i-1.i-1}=ans_{i-1}$。由于上面提到的额外贡献，$f_{i,0}$ 要额外增加 $i-2$（$f_{i-1,1}$ 上系数是 $i-2$）。
- 其次我们更新 $ans_i$，而这个很好办，只需要在 $ans_{i-1}$ 的基础上增加 $f_{i,0}+1$ 即可。
- 最后更新 $S_i$。由上面的分析，$S_i$ 的贡献分为三部分：$S_{i-1}$，$(i-1)f_{i,0}$ 和新加的那个 $1$，其系数为 $i-3$。

而最后的答案是 $sum_n+2$，补充了 $000\dots01$ 的情况和额外添加的那个 $1$。

代码炒鸡短。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
#define mod 998244353
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
ll n;
il void mian() {
	n=read();ll S=7,ans=3;
	if(n==2) {printf("1\n");return;}
	if(n==3){printf("2\n");return;}
	for(int i=5;i<=n;i++) {
		ll tmp=S;//其实就是上一行的 S
		S=(S+ans)%mod;
		S=(S+(i-2))%mod;
		ans=(ans+1+S)%mod;
		S=(S*(i-1)%mod+tmp+(i-3))%mod;
	}
	printf("%lld\n",ans+2);
}
int main() {
	int t=read();
	while(t--) {
		mian();
	}
	return 0;
}
```

---

## 作者：sbno333 (赞：0)

赛时没调出来，掉紫。

考虑当逆序对足够大时，每次逆序对都不降，放到最后面是不变，其他位置逆序对数量都要改变，而根据最后序列，不考虑最后头不变的情况，你能知道怎么操作的，所以此时只要不放最后面，每个选择都贡献答案。

考虑如何变成这个？即逆序对数量为 $2$，初始时放在最前面，逆序对为 $0$，但一旦放到最后面，就发生改变，变为 $1$，再放置只要不放最后面，逆序对仍未 $1$，最后是 $1$ 我们放在最前面，考虑这三步我们在几次操作内完成，几次操作只完成第一步显然为 $1$ 种序列，完成到第二步为 $n-2$ 种序列，第三步则是根据最后序列 $0$ 的数量对应贡献答案，序列数量应当是所有 $0$ 数量和（此处证明以及细节请读者自行完成，不难）。

然后考虑只完成第一二步的方案容易统计，考虑统计第三步之后。

枚举第三步完成是的长度，此时贡献为完成这个第三步后序列种类数乘上之后操作的贡献。

先考虑 DP，$dp_i$ 表示第 $i$ 此操作完成后，且最后一步在不在末尾的序列种类数。

设第三步完成后为第 $m$ 步，$dp_m=1$，然后对于 $m<i\le n$，$dp_i=\sum_{j=m}^{i-1}a_j\times j$，为啥呢，设上一次不在末尾为某个位置，然后期间一直放末尾，所以是这个。

考虑这个 DP 本质是啥式子？

如果每一次都是只选取 $i-1$ 转移，最后为 $\prod_{i=m}^{n-1} i$。

但是有多种换衣，考虑每一次求和是多种路径可选，问题转化为从 $m$ 到 $n-1$ 每个格子可以选，获得格子编号的权值，最终权值为路经权值的积。或者跳过，问最后所有方案权值和，也就是每个位置可以变成 $1$，互不影响，所以都加一，但是，发现 DP 种我们必须选第一个格子，所以第一个不加，最后就是 $m\times \prod_{i=m+2}^{n} i$。

然后我们考虑我们状态是最后不放末尾，所以考虑答案为某一部开始一直放末尾，所以就是 $\sum_{s=m+1}^n m\times \prod_{i=m+2}^{s} i$。

其中我们认为 $\prod_{i=m+2}^{m+1} i=1$，但是写程序不能这么写。

所以就好啦。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
using namespace std;
int ksm(int a,int b){
	int ans;
	ans=1;
	while(b){
		if(b&1){
			ans*=a;
			ans%=mod;
		}
		a*=a;
		a%=mod;
		b>>=1;
	}
	return ans;
}
int step[1000009][3];
int jc[1000009];
int ms[1000009];
void _main(){
	int n;
	cin>>n;
	if(n==2){
		cout<<1<<endl;
	}else if(n==3){
		cout<<2<<endl;
	}else{
		int ans;
		ans=0;
		ans=1;
		ans+=step[n][1];
		ans%=mod;
		for(int i=4;i<=n;i++){
			if(n==i){
				ans+=step[i][2]%mod;
				ans%=mod;
			}else if(n==i+1){
				ans+=step[i][2]*n%mod;
			}else{
				ans+=step[i][2]*(ms[n]-ms[i]+mod)%mod*ksm(jc[i+1],mod-2)%mod*i%mod;
				ans+=step[i][2];
				ans%=mod;
			}
			
			ans%=mod;
		}
		ans%=mod;
		cout<<ans<<endl;
	}
}
signed main(){
	jc[0]=1;
	for(int i=1;i<=1000000;i++){
		jc[i]=jc[i-1]*i%mod;
		ms[i]=ms[i-1]+jc[i];
		ms[i]%=mod;
	}
	for(int i=1;i<=1000000;i++){
		step[i][0]=1;
		step[i][1]=i-2;
		int l,r;
		l=2;
		r=i-2;
		step[i][2]=(l+r)*(r-l+1)/2%mod;
	} 
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：Binah_cyc (赞：0)

看见这种输入一个数并输出一个数的，果断考虑打表。先使用暴力计算出前 $9$ 项的值，然后再丢进[oeis](https://oeis.org/)里面，可能要删掉第一项，就有[递推式](https://oeis.org/search?q=1+2+5+19+102+682+5321+47071&language=english&go=Search)了。照这这个递推式写写就过了。

马蜂略丑。
```c
#include<iostream>
long long n,f[1000005],m=998244353;
main()
{
	std::cin>>n;
	for(int i=4;i<=1e6;f[i]=(f[i-1]*i+i-2)%m,i++);
	for(int i=2;i<=1e6;f[i]=(f[i-1]+f[i]+1)%m,i++);
	while(std::cin>>n)std::cout<<f[n]<<'\n';
}
```

---

