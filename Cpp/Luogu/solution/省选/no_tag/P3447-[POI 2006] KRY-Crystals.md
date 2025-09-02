# [POI 2006] KRY-Crystals

## 题目描述

给定 $n$ 个正整数 $m_1$ 到 $m_n$，对长度为 $n$ 且满足以下条件的整数序列 $a$ 计数：
- 对于任意 $1\le i\le n$，$0\le a_i\le m_i$；
- $a_1\oplus a_2\oplus\cdots\oplus a_n=0$，其中 $\oplus$ 为按位异或运算；
- $a_1+a_2+\cdots+a_n\ge1$。

## 说明/提示

$1\le n\le50$。

$1\le m_i\le2^{32}-1$。

数据保证答案小于 $2^{64}$。

感谢 @FZzzz @UnyieldingTrilobite 提供翻译。

## 样例 #1

### 输入

```
3
2 1 3```

### 输出

```
5```

# 题解

## 作者：Silviasylvia (赞：17)

首先有一种暴力方法，就是位数从高到低直接数位 dp，记录当前每一个数的上限是否取满了，但这样复杂度显然是爆炸的。我们考虑有没有什么性质可以优化这个过程。

异或有一个很优秀的性质；$a\oplus b \oplus c=0$，那么 $a\oplus b=c$，所以我们发现，只要确定了前 $n-1$ 个数，第 $n$ 个数也就确定了，只要考虑是否在范围内即可。

然后就容易多了，首先不难发现如果 $a_n=2^{32}-1$ 的话，那么答案就为 $\prod\limits_{i=1}^n(a_i+1)-1$，这还是在引导你从高位到低位考虑：如果你在一个高位没取满，在低位就可以任意取。

于是顺着这个思路从高位考虑，当前在第 $j$ 位（最低位算 $0$），设有 $k$ 个数在当前位是 $1$，那么如果你有任意一个当前位为 $1$ 的数没取 $1$，那么你可以立即用上面的式子算出答案，否则就一定是全部取了 $1$，那就把这位去掉，成为了一个 $j-1$ 位的子问题。

假如有 $t$ 个当前位是 $1$，但是没取 $1$ 的，那么这个集合里面有一个需要用在最后被确定的那个，除了这个之外的都可以任选。这个过程可以 $O(n)$ dp 解决。

具体的，设 $dp_{i,0/1}$ 表示考虑到前 $i$ 个，这一位目前的异或值是 $0/1$ 的答案总和，转移显然。当前位的答案就为 $dp_{n,0}$。

一些细节：

1. 如果当前位为 $1$ 的个数是偶数（第 $0$ 位除外），那么最终的 $dp$ 值就需要减去 $\prod\limits_{i=1}^n((a_i\mod 2^j)+1)$，因为这包含了全部选的方案，但是如果全部选的话实际上应该考虑在 $j-1$ 的子问题中，所以不能算。
2. 你在算**有 $1$ 的最高位**的贡献的时候，会把全部是 $0$ 的方案算进去，因此最终 ans 要减 $1$。
3. 如果当前位有奇数个 $1$，那么统计完就直接退出循环（显然）。
4. 答案会爆 ll，建议开 int128。

复杂度 $O(n\log m)$。

核心代码：

```
rdn;
upn rd(a[i]);
int ans=0;
pu(j,31,0)
{
	int st=0;
	up(i,1,n)
	{
		if(a[i]&(1<<j))++st;
	}
	dp[0][0]=1;
	int ww=1;
	up(i,1,n)
	{
		if(a[i]&(1<<j))
		{
			dp[i][0]=dp[i-1][1]*(a[i]%(1<<j)+1);
			dp[i][1]=dp[i-1][0]*(a[i]%(1<<j)+1);
			dp[i][0]+=dp[i-1][0]*(1<<j);
			dp[i][1]+=dp[i-1][1]*(1<<j);
		}
		else
		{
			dp[i][0]=dp[i-1][0]*(a[i]%(1<<j)+1);
			dp[i][1]=dp[i-1][1]*(a[i]%(1<<j)+1);
		}
		ww*=(a[i]%(1<<j)+1);
	}
	int vl=0;
	vl=dp[n][0];
	if(st%2==0)vl-=ww;
	if(st%2==0&&j==0)vl+=ww;
	vl/=(1<<j);
	ns+=vl;
	if(st&1)
	{
		break;
	}
}
print(ans-1);
```

---

## 作者：Alex_Wei (赞：11)

Upd on 2022.4.3 修改错误。

> [*P3447 [POI2006]KRY-Crystals*](https://www.luogu.com.cn/problem/P3447)
>
> [*POI 合集*](https://www.cnblogs.com/alex-wei/p/POI.html)。

读完题目，纷繁复杂的限制让我们无从下手。从哪个条件作为突破口呢？肯定是最严格的异或限制。

异或有性质 $a \oplus b = c\Rightarrow b = a\oplus c$。对应到题目中，就是若序列 $a$ 有 $n - 1$ 个数确定，则未定数只能等于所有确定数的异或和。这启发我们思考，有没有一种可能，未定数对应的限制 $m_i$ 非常大，以至于无论 $n - 1$ 个数怎么选，它们的异或和总不大于 $m_i$，这样我们就可以很方便地用乘法原理求出答案。

实际上有可能！考虑第 $i$ 位，假设存在 $p$ 使得 $m_p$ 这一位为 $1$，但 $a_p$ 为 $0$，说明若所有数字在第 $i$ 位及其高位异或和为 $0$，那么无论其它数字低 $i - 1$ 位怎么填都符合条件，因为 $a_p$ 在第 $i$ 位小于 $m_p$，所以接下来的低 $i - 1$ 位没有限制。

这启发我们直接枚举所有 $a_p$ 与 $m_p$ 的最短 LCP，即 存在 $p$ 使得 $m_p$ 在第 $i$ 位为 $1$ 但 $a_p$ 为 $0$，且 $a$ 高于第 $i$ 位的部分与 $m$ 相同 的位数 $i$。这样，我们只需把任意一个 $p$ 的系数变为 $1$（因为它依赖于剩余数的异或和），剩下的系数用乘法原理乘起来即可。

具体地，考虑我们关心什么：第 $i$ 位异或和为 $0$ 且存在 $p$。这启发我们设计 DP $f_{j, k, l}$ 表示考虑到第 $j$ 个数，第 $i$ 位异或和为 $k$ 且是否存在 $p$。根据乘法原理与实际意义转移：

若 $m_j$ 第 $i$ 位为 $1$，那么 $a_j$ 可以选择 $0 / 1$：选 $0$ 的方案数为 $2^i$，选 $1$ 的方案数为 $m_j$ 在低 $2 ^ {i - 1}$ 位的值加上 $1$，记作 $c_i$，实际上就是 $(m_j \& (2 ^ i - 1)) + 1$。从 $l = 0$ 转移到 $l = 1$ 时，系数为 $1$，表示钦定 $j$ 的系数为 $1$。
$$
\begin{aligned}
& f_{j, 0, 0} = f_{j - 1, 1, 0}\times c_j \\
& f_{j, 1, 0} = f_{j - 1, 0, 0}\times c_j \\
& f_{j, 0, 1} = f_{j - 1, 1, 1}\times c_j + f_{j - 1, 0, 1}\times 2 ^ i + f_{j - 1, 0, 0} \\
& f_{j, 1, 1} = f_{j - 1, 0, 1}\times c_j + f_{j - 1, 1, 1}\times 2 ^ i + f_{j - 1, 1, 0}
\end{aligned}
$$
若 $m_j$ 第 $i$ 位为 $0$，则只能选 $0$ 且方案数为 $c_j$。
$$
f_{j, k, l} = f_{j - 1, k, l}\times c_j
$$
最后，若 $m$ 比 $i$ 高的位的异或和为 $0$ 才能计算当前位贡献 $f_{n, 0, 1}$，因为钦定了高位 $a$ 都取 $m$。注意全零序列会被统计到，因此最后答案减 $1$。时间复杂度是优秀的 $\mathcal{O}(n\log m)$。

总结一下，对于位运算相关 **有限制** 的计数题，首先考虑 **最严格** 的限制，并尽量 **独立每一位**，如果做不到就按顺序考虑每一位的限制。选择本题的原因是希望各位同学能够感受到这种按位枚举什么东西然后再 DP 的套路。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 50 + 5;
unsigned long long n, ans, xs, m[N], f[2][2][2];
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) scanf("%llu", &m[i]), xs ^= m[i];
	ans = !xs, xs = 0;
	for(int i = 31; i >= 0; i--) {
		memset(f, 0, sizeof(f)), f[0][0][0] = 1;
		for(int j = 1, p = 0, q = 1; j <= n; j++, swap(p, q)) {
			unsigned long long coef = (m[j] & ((1 << i) - 1)) + 1;
			xs ^= m[j] >> i + 1;
			for(int c : {0, 1}) for(int d : {0, 1}) f[q][c ^ m[j] >> i & 1][d] = f[p][c][d] * coef;
			if(m[j] >> i & 1) for(int c : {0, 1}) f[q][c][1] += (f[p][c][1] << i) + f[p][c][0];
		}
		if(!xs) ans += f[n & 1][0][1];
		else break;
	}
	cout << ans - 1 << endl;
	return 0;
}
```

---

## 作者：Miko35 (赞：8)

### 题意

给出序列 $a_{1\sim n}$，求满足以下条件的序列 $b$ 的个数：

- $\forall i$，$0 \leq b_i \leq a_i$；
- $b_1\oplus b_2\oplus \ldots\oplus b_n=0$。

$n \leq 50$，$a_i<2^{32}-1$，保证答案小于 $2^{64}$。

### 题解

如果前面 $n-1$ 个数已经填好，那么第 $n$ 个数只有一种选择，但它的上限会限制合法性。如果 $a_n = +\infty$，则方案数就是 $\prod_{i=1}^{n-1}(a_i+1)$。

这启示我们从高位到低位考虑，不妨设所有 $a_i$ 中最高的位为 $w$，$a_i$ 包含最高位的 $i$ 的集合为 $S$。如果存在一个包含最高位的 $a$，它的 $b$ 在 $w$ 这一位不顶上界（即取 $0$），这种情况我们可以快速算出。具体而言，如果 $S$ 的**非空**子集 $T$ 内的 $b_i$ 最高位填的是 $0$，也就是非最高位不受限，那么只需要从 $T$ 集合中任取一个放最后「补漏」，其它随便取即可，方案数就是：
$$
\sum_{T\subseteq S, T \neq \varnothing}[|S|-|T| \text{ is even}](2^w)^{|T|-1}\prod_{i \not\in T}(a_i\bmod 2^w+1)
$$
这个式子可以一遍 DP 简单地 $O(n)$ 算出，不赘述。剩下的情况只有 $S$ 内所有 $b$ 最高位都填 $1$，判断合法性后就是将所有数都去掉最高位之后的子问题了。故我们做 $O(\log m)$ 次 DP 即可求出答案，时间复杂度 $O(n \log m)$。

注意 DP 的过程中会爆 `ull`，可能需要使用 `__int128`。

```cpp
#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a,i##i=b;i<=i##i;++i)
#define ROF(i,a,b) for(int i=a,i##i=b;i>=i##i;--i)
using namespace std;
typedef unsigned long long ull;
typedef __int128 INT;
const int N=57;
ull n,a[N],ans,ct;
INT O,E,y,v,t;
#define G (a[i]+1)
signed main(){
	cin>>n;
	FOR(i,1,n)cin>>a[i];
	ROF(w,31,0){
		E=y=1,v=1ull<<w,ct=O=0;
		FOR(i,1,n){
			if(a[i]&v)a[i]-=v,t=O,O=v*O+G*E,E=v*E+G*t,ct^=1;
			else O*=G,E*=G;
			y*=G,t=O;
		}
		ct&1?O-=y:E-=y,ans+=E/v;
		if(ct&1)cout<<ans-1,exit(0);
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：ppp204 (赞：8)

为加深影响写的题解，大佬看不惯欢迎来喷！

> 做法:找性质，DP

这题的关键就是发现一个性质：如果一个数的最高位取1的话,那么他就受限制，否则接下来几位就可以取任意值，我们在这里先称它为**自由数**(~~哇这么多废话~~)

不难发现，一步步向下并更新最大位后，只要当前最大位为1的个数是奇数个数，那么一定会有一个数是自由数,因此我们可以直接退出

而是偶数个数的话，可以根据次性质进行dp，对每个数在最高位进行讨论(详情见Code)

#### Code:

```
#include<bits/stdc++.h>
using namespace std;
const int M=55;
typedef unsigned long long ull;
ull dp[M][2],A[M],ans;
//dp[i][0/1] --> 当前第某位时,前i个数的当前位异或起来为0/1
int main(){
	int n;
	bool flag;
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%llu",&A[i]);
	for(int i=31; i>=0; i--){
		memset(dp,0,sizeof dp);
		dp[0][0]=1;
		for(int j=1; j<=n; j++){
			if(A[j]&(1<<i)){
				dp[j][0]=dp[j-1][1]*((((1<<i)-1)&A[j])+1)+dp[j-1][0]*((1<<i)); //异或当前位为0，可以前j-1个数为1或0转移而来
				dp[j][1]=dp[j-1][0]*((((1<<i)-1)&A[j])+1)+dp[j-1][1]*((1<<i)); //同上
			}else{
				dp[j][0]=dp[j-1][0]*(A[j]+1); dp[j][1]=dp[j-1][1]*(A[j]+1); //相当于你只能异或0
			}
		}
		flag=0;
		for(int j=1; j<=n; j++) if(A[j]&(1<<i)){
			flag^=1;
			ull res=1,val=0;
			for(int k=j+1; k<=n; k++) res*=(((1<<i)-1)&A[k])+1,val^=A[k]>>i; //前后异或过后要等于0,相当于当前位前后相等
			ans+=res*dp[j-1][val];
		}
		if(flag) break; //奇数个能导致留一个自由数,即接下来怎么放都能变成0
		for(int j=1; j<=n; j++) A[j]&=(1<<i)-1;//更新至下一位
	}
	if(flag) ans--; //如果以奇数为结尾，不能存在所有数字都为0的情况
	printf("%llu\n",ans);
	return 0;
	欢迎来喷！
}
```



---

## 作者：Otomachi_Una_ (赞：5)

出题人就不会取模吗？

虽然但是，这不影响这是一道好题。

## 题目简述

> - 询问有多少长度为 $n$ 的**自然数**数列 $a_1,a_2,\dots a_n$ 满足一下条件：
> - - 对任意的 $i$ 都有 $0\leq a_i\leq b_i$。
>   - $a_1 ⊕a_2⊕a_3⊕\dots⊕a_{n-1}⊕a_n=0$。
>   - $a$ 不全为 $0$。
> - 原题 $n\leq 50$。实际上可以做到 $n\leq 10^6$，只要取个模即可。

## 解题思路

首先条件 $3$ 只要满足前两个条件后输出 $ans-1$ 即可。

然后注意到 $a_i\leq b_i$ 这个条件，很自然的可以想到数位 dp。但是我们要记录每一位的是否顶到，时间复杂度是大于 $O(2^n)$，连原题都过不去。

注意到数位 dp 的过程，不难发现对于一个二进制下是 $\texttt{101110}$ 的数，数位 dp 会把它拆成 $\texttt{0?????},\texttt{100???},\texttt{1010??},\texttt{10110?},\texttt{101110}$。其中 $\texttt ?$ 表示随便选取的位。

观察一个例子，我们对  $\texttt{10???},\texttt{001??},\texttt{111??},\texttt{0100?}$ 当中的 $\texttt ?$ 随便选取使得其异或为 $0$ 的方案数，我们不难想到固定 $\texttt{10???}$ 为**自由元**，对于其他三个数**随意选取**当中的 $\texttt ?$ 即可。因为 $\texttt{10???}$ 后缀的 $\texttt ?$ 很多，所以我们总能调整它使得整体的异或为 $0$。

这启示我们，对上面这类型的问题，我们只需要取后缀 $\texttt ?$ 最多的元素作为自由元即可，其他元素就可以自由选取了。

本题是类似的，原题的数据范围很小，甚至可以直接把每个数拆成数位 dp 的形式，然后枚举每个数作为自由元的贡献，时间复杂度是 $O((n\log V)^2)$ 的。显然还可以枚举自由元的长度再去跑一遍 dp，可以做到 $O(n\log V)$。

## 具体实现

枚举自由元的长度 $i$，维护 dp 数组 $f[i][j][k]$ 表示前 $i$ 个数当中，是否有自由元，并且第 $i$ 位当前的异或。 

那么每个数 $a_j$ 有两种情况：

- $a_j$ 在第 $i$ 位是 $0$：那么它肯定不是自由元，它只有 $a\ \text{and}\  (2^n-1)$ 的贡献给 $f[j][k][t]$ 自己转自己。
- $a_j$ 在第 $i$ 位是 $1$：那么它可以是自由元，枚举两种情况，第一是 $a_j$ 是自由元，那么他是没有贡献的，只能把 $f[j-1][0][]$ 转移到 $f[j][1][]$，第二是 $a_j$ 不是自由元，那么我们只要枚举 $a_j$ 第 $i$ 位的选取情况即可。

需要注意的是可能超过 $i$ 位的部分本身异或就不是 $0$，这样子不能加入答案。

上面的 $f$ 的转移都比较长，具体的可以见代码：

```cpp
const int MAXN=55;
int n;ull a[MAXN];
ull f[MAXN][2][2],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=31;i>=0;i--){
		memset(f,0,sizeof(f));
		f[0][0][0]=1;int flag=0;
		for(int j=1;j<=n;j++){
			flag^=(a[j]>>i+1);
			if(a[j]>>i&1){
				f[j][0][1]=f[j-1][0][0]*((a[j]&((1<<i)-1))+1);
				f[j][0][0]=f[j-1][0][1]*((a[j]&((1<<i)-1))+1);
				f[j][1][0]=f[j-1][0][0]+f[j-1][1][1]*((a[j]&((1<<i)-1))+1)+f[j-1][1][0]*((1<<i));
				f[j][1][1]=f[j-1][0][1]+f[j-1][1][0]*((a[j]&((1<<i)-1))+1)+f[j-1][1][1]*((1<<i));
			}else{
				f[j][0][1]=f[j-1][0][1]*((a[j]&((1<<i)-1))+1);
				f[j][0][0]=f[j-1][0][0]*((a[j]&((1<<i)-1))+1);
				f[j][1][0]=f[j-1][1][0]*((a[j]&((1<<i)-1))+1);
				f[j][1][1]=f[j-1][1][1]*((a[j]&((1<<i)-1))+1);
			}
		} 
		if(!flag) ans+=f[n][1][0];
		if(!flag&&i==0) ans+=f[n][0][0];
	}
	cout<<ans-1;
	return 0;
}
```

 

---

## 作者：Undead2008 (赞：5)

发现 $a_i$ 如果在某一个二进制位为 $1$，$m_i$ 在那一位为 $0$，那么 $a_i$ 后面长什么样都不会超过 $m_i$。

考虑从高到低枚举满足“存在 $j$ 使得 $a_j$ 的第 $i$ 个二进制位小于 $m_j$ 的第 $i$ 个二进制位”的二进制位 $i$，从所有满足上述条件的 $a_j$ 中钦定一个，剩下的在 $\le m_i$ 范围内随便填，因为钦定的 $a_j$ 在 $i$ 后面的所有二进制位都没有上界的限制，无论后面的数异或成什么样都可以用钦定的 $a_j$ 来补成 $0$。每一位的具体方案数可以用 dp 来解决。

时间复杂度 $O(n\log w)$，其中 $w$ 是值域。

---

## 作者：云浅知处 (赞：3)

发现只要有某个 $x_i$ 的第 $j$ 位没有顶到上界，那么其他的 $x_k$ 在第 $j$ 位之后就不需要考虑那个异或的限制了，因为这个 $x_i$ 总能有（也是唯一的）方案来满足其他 $x_k$ 在这一位上的异或约束。

考虑枚举第一次出现某个 $x_i$ 不顶上界的位（那么这要求前面的位上 $m_i$ 各自的前缀异或起来恰好和 $k$ 的前缀一样）。这一位上可能会有不止一个 $x_i$ 不顶上界，并且需要满足这一位上的异或约束。考虑 DP：$f(i,0/1,0/1)$ 表示考虑了前 $i$ 个数，异或和为 $0/1$，是否选过不顶上界的数，的方案数。如果枚举的是第 $j$ 位，有转移：

- $m_{i+1}$ 这一位上是 $0$：那么 $x_{i+1}$ 这一位还得顶上界，有 $f(i,c,x)\times (m_{i+1}\bmod 2^j)\to f(i+1,c,x)$
- $m_{i+1}$ 这一位上是 $1$：那么 $x_{i+1}$ 这一位可以选择顶上界或者不顶上界。如果顶上界也就是这一位选 $1$，有转移 $f(i,c,x)\times(m_{i+1}\bmod 2^j)\to f(i+1,c\oplus 1,x)$；否则有相当于这一位选 $0$，转移式为 $f(i,c,x)\times (\texttt{x==1 ? 1<<j : 1})\to f(i+1,c,1)$。

时间复杂度 $O(n\log m)$。

```cpp
#include<bits/stdc++.h>

#define ull unsigned long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const ull mod=1ull<<64;
int ksm(int x,int y,int p=mod){
	int ans=1;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
int randint(int l,int r){return rand()*rand()%(r-l+1)+l;}
void add(ull &x,ull v){x+=v;if(x>=mod)x-=mod;}
void Mod(ull &x){if(x>=mod)x-=mod;}

const int N=55;
ull f[N][2][2],lim[N],n,X;

void solve(){
    n=read(),X=0;
	ull ans=0,now=0;
	for(int i=1;i<=n;i++)lim[i]=read()+1,now^=lim[i];
	
	for(int w=31;w>=0;w--){
//		cout<<"bit = "<<w<<endl;
		bool chk=1;
		for(int i=31;i>w;i--)if((now^X)&(1<<i)){chk=0;break;}
		if(!chk)break;
		int U=(1<<w)-1;
		memset(f,0,sizeof(f));
		f[0][0][0]=1;
		for(int i=0;i<n;i++)for(int c=0;c<2;c++)for(int x=0;x<2;x++)if(f[i][c][x]){
//			cout<<i<<" "<<c<<" "<<x<<" "<<f[i][c][x]<<endl;
			if(lim[i+1]&(1<<w)){
				add(f[i+1][c^1][x],1ll*f[i][c][x]*((lim[i+1]&U)));
				add(f[i+1][c][1],1ll*f[i][c][x]*(x?(U+1):1ll));
			}
			else add(f[i+1][c][x],1ll*f[i][c][x]*((lim[i+1]&U)));
		}
		if(X&(1<<w))add(ans,f[n][1][1]);
		else add(ans,f[n][0][1]);
//		cout<<"ans = "<<ans<<endl;
	}
	cout<<ans-1<<endl;
}

signed main(void){

#ifdef YUNQIAN
	freopen("1.in","r",stdin);
#endif

    solve();

	return 0;
}
```

---

## 作者：liaiyang (赞：3)

给定 $b_1,b_2,...,b_n$，求有多少个数组满足 $0\le a_i\le b_i$ 且 $\bigoplus_{i=1}^na_i=0$，$1\le n\le 50,1\le V< 2^{32}$。

其实出题人可以加入取模后把 $n$ 开到 $10^6$ 的。

首先 $b_i$ 加一，将条件转化为 $0\le a_i< b_i$。

我们考虑钦定一个二进制位 $i$，在此位选择若干个脱离上界的 $a_j$。

假设存在 $b_j$ 在 $i$ 位是 $1$，$a_j$ 在此位脱离上界的话，那么低于这位的其它值任意取，$a_j$ 都可以通过调整使异或和为 $0$。

所以我们要求在第 $i$ 位刚好脱离上界，这一位的 $1$ 有偶数个，至少有一个脱离上界。

构建多项式 $f(x)=\prod_{[i]b_j=0}(b_j\bmod 2^i)\prod_{[i]b_j=1}((b_j\bmod 2^i)x+2^i)$，那么方案数即为 $\sum_{i=0}^m [2|i]([x^i]f(x))$。

对于这种式子，显然考虑单位根反演。

假设总共有 $m$ 次项，我们有 $[k|n]=\frac 1 k \sum_{i=0}^{k-1}\omega_{k}^{in}$，那么 $\sum_{i=0}^m[k|i][x^i]f(x)=\sum_{i=0}^m(\frac 1 k\sum_{j=0}^{k-1}\omega_{k}^{ij})[x^i]f(x)=\frac 1 k\sum_{i=0}^{k-1}f(\omega_k^i)$。

在这里 $k=2$，那么这一位的答案即为 $\dfrac{\frac{f(-1)+f(1)}2-[2|m]([x^m]f(x))}{2^i}$，原因是需要钦定一个脱离上界的来调整。

这里钦定调整没有选择哪一个数问题，因为对于某个答案，调整 $a_i$ 或调整 $a_j$ 都会到达这个结果，是重复的，所以直接除 $2^i$即可。

注意当某一位的 $1$ 个数为奇数时，那么不可能全都贴上界了，计算完这一位答案就停止继续下一位的计算。

由于本题要求非空，最后答案需要减一，时间复杂度 $O(n\log V)$。

计算时可以考虑对一个比答案大的质数取模。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
// #pragma GCC optimize(1)
// #pragma GCC optimize(2)
// #pragma GCC optimize(3)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
// #define ull unsigned long long
// #define ulll __uint128_t
// struct FastMod{
//     ull p,w;FastMod(ull p=2):p(p),w((ull)(((ulll)(1)<<64)/p)) {}
//     ull reduce(ull x) {ull d=(ull)(((ulll)(w)*x)>>64),r=x-p*d;return r>= p?r-p:r;}
// }FM;
// #define modd FM.reduce
#define int __int128
#define y0 Y0
#define y1 Y1
#define lc (now<<1)
#define rc (now<<1|1)
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
#define P pair<int,int>
#define mkp make_pair
#define x first
#define y second
#define modd(x) (((x)%mod+mod)%mod)
#define rd read()
#define lowbit(x) ((x)&(-(x)))
#define abs(x) ((x)<0?-(x):(x))
#define submod(x,y) (((x-=y)<0)&&(x+=mod))
#define addmod(x,y) (((x+=y)>=mod)&&(x-=mod))
#define addval(x,y) (x+y>=mod?x+y-mod:x+y)
#define subval(x,y) (x-y<0?x-y+mod:x-y)
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
#define fflush() fwrite(obuf,1,O-obuf,stdout),O=obuf
char buf[(1<<21)+10],*p1=buf,*p2=buf,obuf[(1<<21)+10],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#define putchar(x) (O-obuf<(1<<21)?*O++=(x):(fwrite(obuf,1,1<<21,stdout),O=obuf,*O++=(x)))
inline int read(int u=0, char c=getchar(), bool f=false){
    for(;!isdigit(c);c=getchar()) f|=c=='-';
    for(;isdigit(c);c=getchar()) u=(u<<1)+(u<<3)+(c^'0');
    return f?-u:u;
}
inline void read(string &s,char c=getchar()){
    for(;(c<'A'||c>'Z')&&(c<'a'||c>'z')&&(c<'0'||c>'9');c=getchar());s.clear();
    for(;(c>='A'&&c<='Z')||(c>='a'&&c<='z')||(c>='0'&&c<='9');c=getchar()) s.push_back(c);
}
inline void wt(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) wt(x/10);
    putchar((x%10)^'0');
}
inline void wt(string s){for(char c:s) putchar(c);}
inline void wt(int x,char k){wt(x),putchar(k);}
const int mod=(((__int128)(1)<<64)+13);
const int inf=~0U>>1,linf=~0ULL>>1,iinf=1e18;
const int N=1e6+10;
int n,b[N],ans;
int times(int x,int k){int res=0;for(;k;addmod(x,x),k>>=1) if(k&1) addmod(res,x);return res;}
main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=rd;for(int i=1;i<=n;i++) b[i]=rd+1;int inv2=(mod+1)/2,sum=inv2;
    for(int i=1;i<=32;i++) sum=times(sum,inv2);
    for(int i=32;i>=0;i--){
        int sum1=1,sum2=1,cnt=0,res=1;
        for(int j=1;j<=n;j++){
            if(b[j]>>i&1) sum1=sum1*(b[j]%(1ll<<i)+(1ll<<i))%mod,sum2=sum2*(-(b[j]%(1ll<<i))+(1ll<<i))%mod,res=res*(b[j]%(1ll<<i))%mod,cnt++;
            else sum1=sum1*(b[j]%(1ll<<i))%mod,sum2=sum2*(b[j]%(1ll<<i))%mod,res=res*(b[j]%(1ll<<i))%mod;
        }
        if(cnt%2==0) submod(sum1,res),submod(sum2,res);
        ans=(ans+times((sum1+sum2)%mod,sum))%mod;addmod(sum,sum);
        if(cnt&1) break;
    }submod(ans,1);wt(ans,'\n');
    return fflush(),0;
}
```

---

## 作者：zzzyyyyhhhhh (赞：2)

首先看到异或，自然想到由高到低从位数考虑。只需要默认高位能填则都填 1，如果高位全填 1 异或和不为 0 直接中止，否则用 dp 求出从这位开始可填 1 或 0 的方案数和全填 1 的方案数，再用可填 1 或 0 的方案数减去这位全为 1 的方案数（因为会重复计算）即可。

剩下的就是一些细节，首先再一些写法下 dp 过程会爆 long long ，所以记得开 `__int128`。在枚举到第 $i$ 位时，如果这位 1 的个数是偶数，需要减去全选 1 的方案数。在确定了前面的所有数时，最后一位的数也就确定了，所以不用考虑最后一个数。

其他细节见代码吧。

```cpp
#include"bits/stdc++.h"
using namespace std;
#define int __int128//dp过程会爆long long
typedef long long ll;
const int N = 60;
ll n,a[N];
int f[N][2];//表示第i个数，当前这位（下文的j）异或和是否为0，在j以上位能选1就选1的情况下
signed main()
{
	cin>>n;
	int ans=0,tmp=0;
	for(int i=1;i<=n;i++)cin>>a[i];//读入
	for(int j=31;j>=0;j--)//枚举位数，此时对于所有数大于j的位能填则填1
	//从高位向低位枚举,原因时下面当cnt==0时直接break，这是高位全填1异或和不能为0的情况
	{
		int cnt=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]&(1<<j))cnt++;//统计第j位为1ll的数的数量
		}
		memset(f,0,sizeof f);
		f[0][0]=1;
		tmp=1;//记录全填1的方案数
		for(int k=1;k<=n;k++)
		{
			if(a[k]&(1ll<<j))
			{
				//通过取余取后j位
				f[k][0]=f[k-1][1]*(a[k]%(1ll<<j)+1)//这位填1
						+f[k-1][0]*(1ll<<j);//这位填0
				f[k][1ll]=f[k-1][0]*(a[k]%(1ll<<j)+1)
						+f[k-1][1]*(1ll<<j);
			}
			else
			{
				f[k][0]=f[k-1][0]*(a[k]%(1ll<<j)+1);//因为a_k可以为0，所以要加1
				f[k][1]=f[k-1][1]*(a[k]%(1ll<<j)+1);//这位只能填0
			}
			tmp*=(a[k]%(1ll<<j)+1ll);
		}
		int val=0;
		val=f[n][0];//异或和为0的方案数
		if((!(cnt&1ll))&&j!=0)//第j位为1数字数量为偶数，减去全选1的方案数
		{
			val-=tmp;
		}
		val>>=j;//最后一个数不考虑，因为前面的数确定后最后一个数就确定了
		ans+=val;
		if(cnt&1)break;//如果这位1数量为偶数，则后面的都不合法，可以思考一下状态
	}
	cout<<(unsigned long long)(ans-1ull);//滑稽输出
}

```

---

## 作者：autumnlove (赞：2)

首先要知道一个东西：若 $n$ 个数中，若有 $1$ 个数的第 $i$ 位没达到上限，那这 $n-1$ 个数的后面 $i-1$ 位就可以随便取，那一个数凑就可以保证后面 $i-1$ 位的异或和为 $0$。

从每一位看，这一位可以分两种情况
1. 这位有数没有取到上限的
2. 这位所有数都取到了上限

对于第二种情况：需要每个数取到上限后异或起来和是 $0$，否则跳出循环就好了，符合条件后直接到下一位即可。

对于第一种情况：需要要做到的是不重不落的枚举完有东西没取到上限的情况。

这里推荐一种枚举的方法：枚举第 $i$ 个数是最后没有到上限的数（当然这个数这一位得是 $1$）$i$ 前的随便有没有取到上限，$i$ 后的都要取到上限。

因为 $i$ 后全要取到上限，所以异或的值是固定的，所以前面任意取的方案数dp就好了，可以看看代码。

最后，如果到了最后都满足的话，记得加上每个数都取到上限的取法。

注意：
1. 记得减去全都是 $0$ 的情况
2. ```long long``` 不够用 得 ```unsigned long long```


```
#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
const int N= 55;
int a[N]; ull dp[N][2];   // dp[i][j]表示第i个数 异或和为j后面的方案数
int main()
{
	int n; cin>> n; int fl= 0;
	for(int i= 1; i<= n; i++ ) scanf("%d", &a[i]);
	ull ans= 0; 
	for(int i= 31; i>= 0; i-- )
	{
		dp[0][0]= 1, dp[0][1]= 0; fl= 0; 
		for(int j= 1; j<= n; j++ )
		{
			if(a[j]>> i& 1) 
			{
				dp[j][0]= (ull)dp[j- 1][1]* ((a[j]& ((1<< i)- 1))+ 1)+ (ull)dp[j- 1][0]* (1<< i);
				dp[j][1]= (ull)dp[j- 1][1]* (1<< i)+ (ull)dp[j- 1][0]* ((a[j]& ((1<< i)- 1))+ 1);
			}
			else dp[j][0]= dp[j- 1][0]* (a[j]+ 1), dp[j][1]= dp[j- 1][1]* (a[j]+ 1);
		}
		for(int j= 1; j<= n; j++ )
		{
			if(! (a[j]>> i& 1)) continue; fl^= 1; ull res= 1, tmp= 0;
			for(int k= j+ 1; k<= n; k++ ) res*= ((a[k]& ((1<< i)- 1))+ 1), tmp^= (a[k]>> i& 1);
			ans+= (ull)res* dp[j- 1][tmp]; 
		}
		if(fl== 1) break;
		for(int j= 1; j<= n; j++ ) a[j]&= (1<< i)- 1; 
	}
	if(fl== 0) ans++ ; cout<< ans- 1<< endl;
	return 0;
}
```

---

## 作者：huhangqi (赞：1)

真的是一道非常逆天的一道题目。

首先我们可以发现直接求解并不方便，考虑如何更加高效地求解答案。

我们无法快速得到答案的原因在于我们前面的选择收到了数字大小的限制，导致了后面数字选择方案数量的不确定，并且后面数字的方案极多，无法直接统计。

那么我们通常需要考虑这道题目有什么特殊之处，第一条式子确定了数值的范围，第二条式子表示所有数字异或和为 $0$，第三条结合取值范围就是不能全部选择 $0$，那么我们在统计完答案以后减去 $1$ 即可。

那么我们明显需要在第二条式子上找性质，学过异或的同学们都知道，如果上述式子 $a_1\oplus a_2\oplus\cdots\oplus a_n=0$ 成立，那么还一定满足式子

$a_2\oplus\cdots\oplus a_{n}=a_1$ 并且不只是取 $a_1$ 到右边成立，而是把任何一个数字移到右边都成立。

那么我们就可以想到，是否存在一种情况，使得无论我们的左边取什么值，右边都可以选择对应的值使结果成立。

样例就是一个例子，我们直接将 $a_3$ 移到右边，此时对于前面的情况都有对应的值，直接根据乘法原理即可得到答案。

这样我们只需要找到一个最高位高于其它数字的数即可。

但是很明显的一个问题，就是不一定存在这么一个数字可以对应在这个范围内的任何一个数字，那么这种方法肯定就没有办法使用了。

此时我们已经和正解非常接近了，对于位运算的题目，我们通常可以考虑按照位来拆开。

但是我们此时求的是方案数，怎么按照位进行拆分呢？

与其它题解一样，我们将这个可以对应范围内任意数字的位置称为自由元，那么我们可以考虑位进行动态规划，得到结果。

我们此时枚举在第 $i$ 位产生了自由元并且有值打破了范围限制，可以随便取后面的值了，然而第 $i$ 位需要满足异或值为 $0$ 的条件，前面几位则必须保持相等，因为前面几位全部受到范围限制，最好计算。

当然如果你后面都没有数字了，那么可以不考虑自由元的问题了。

先解释一下为什么这样统计不会有错误，我们此时只需要确定选择的每一种打破限制的情况都能找到相对应的自由元即可。

第 $i$ 位的自由元需要满足这一位必须有 $1$ 这个数，而这也是打破范围限制的必要条件。

因此，我们不难发现，所谓的自由元出现的基本条件就是在这一位打破了范围限制，导致了后面一定能够取值取到任何值。

然而打破范围的很有可能不止一个，那么我们就选择其中一个位置最靠前的一个作为自由元，因为选择哪个是自由元对于结果是没有影响的，每个情况很有可能对应了多种自由元的选择，因此我们选择其中一种即可。

那么剩下的部分就简单了，只需要记住打破限制了那么就有自由元，没有打破限制就没有自由元，第一个自由元要被另外几个数字的选择摆布，因此不计入贡献即可。

动态规划部分其它题解都很详细，不补充了。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[55];
unsigned long long dp[55][2][2],ans;
//选择到了第 i 位，目前的值为 j，是否有自由元 
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=31;i>=0;i--){
		int f=0;
		for(int j=1;j<=n;j++)f^=(a[j]>>i+1);
		if(f)break;
		dp[0][0][0]=1;
		for(int j=1;j<=n;j++){
			int tmp=(a[j]&((1ll<<i)-1))+1;
			if(a[j]&(1ll<<i)){
				dp[j][0][0]=dp[j-1][1][0]*tmp;
				dp[j][1][0]=dp[j-1][0][0]*tmp;
				dp[j][0][1]=(dp[j-1][0][1]<<i)+dp[j-1][1][1]*tmp+dp[j-1][0][0];
				dp[j][1][1]=(dp[j-1][1][1]<<i)+dp[j-1][0][1]*tmp+dp[j-1][1][0];
			}
			else {
				dp[j][0][0]=dp[j-1][0][0]*tmp;
				dp[j][0][1]=dp[j-1][0][1]*tmp;
				dp[j][1][0]=dp[j-1][1][0]*tmp;
				dp[j][1][1]=dp[j-1][1][1]*tmp;
			}
		}
		ans+=dp[n][0][1];
		if(i==0)ans+=dp[n][0][0];
	}
	cout<<ans-1;
	return 0;
}
``````

---

## 作者：forgotmyhandle (赞：1)

## 分析

首先考虑如果有某一个数的大小不被限制，则其他的数都可以在范围内随便乱填，然后通过那个不被限制的数使得所有数的异或和为 $0$。

接下来把每一位独立开，并且钦定这一位的高位都顶满上界。如果在这一位上有一个 $m_i$ 为 $1$，但是填进去的 $a_i$ 的这一位却为 $0$，那就说明这个数在以后的位上是自由的。这样别的数在以后的位上可以随便乱填，最后通过这个自由的数来满足以后的位上的异或限制。这样就可以分别对每一位进行 dp。设 $dp[i][0/1][0/1]$ 表示前 $i$ 个数，是否已经有自由的数，目前所有数在这一位上的异或和为 $0 / 1$ 时的方案数。转移时考虑加入一个数 $x$，分两种情况讨论：

1. 如果 $x$ 在当前位 $t$ 上为 $0$，则这一位必然填 $0$，接下来的位也要满足 $x$ 的限制。

2. 如果 $x$ 在当前位 $t$ 上为 $1$，则这一位可以填 $0$，也可以填 $1$。如果填 $1$，则接下来的位也要满足 $x$ 的限制。如果填 $0$，则会凭空多出一个自由的数。如果是从一个有自由的数的状态转移而来，则这个数后面的位可以随便乱填。如果是从一个没有自由的数的状态转移而来，则我们在其他的数随便乱填之后拿这个自由的数来满足最后的异或限制，所以只有一种填法。

注意到这个 dp 本质上是在其他的数随便填完之后拿第一个出现的自由的数来满足低位的异或限制，然后通过状态第三维的 $0$ 或 $1$ 来满足当前位的异或限制。对于高位，如果枚举到某一位时发现这一位的高位异或起来不为 $0$，则可以直接退出，因为再往下枚举也不会符合条件。这样就满足了所有位上的异或限制。

注意到我们会把全 $0$ 算进去，而且不会把所有数都取满限制的情况算进去，所以输出答案的时候要额外搞一下。

## 代码
```cpp
#include <iostream>
#include <string.h>
#define int __int128
using namespace std;
long long dp[55][2][2]; // i, whether free, xor sum
unsigned long long ans = 0;
long long a[55], x;
signed main() {
    long long n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], x ^= a[i];
    for (signed i = 31; ~i; i--) {
        int tmp = 0;
        memset(dp, 0, sizeof dp);
        dp[0][0][0] = 1;
        int t = (1 << i);
        for (signed j = 1; j <= n; j++) {
            tmp ^= (a[j] >> (i + 1));
            if ((a[j] >> i) & 1) {
                // put 0
                dp[j][1][0] += dp[j - 1][0][0];
                dp[j][1][0] += dp[j - 1][1][0] * t;
                dp[j][1][1] += dp[j - 1][0][1];
                dp[j][1][1] += dp[j - 1][1][1] * t;
                // put 1
                dp[j][1][0] += dp[j - 1][1][1] * (1 + (a[j] & (t - 1))); // 可以填 0，所以要加 1
                dp[j][1][1] += dp[j - 1][1][0] * (1 + (a[j] & (t - 1)));
                dp[j][0][0] += dp[j - 1][0][1] * (1 + (a[j] & (t - 1)));
                dp[j][0][1] += dp[j - 1][0][0] * (1 + (a[j] & (t - 1)));
            } else {
                dp[j][0][0] += dp[j - 1][0][0] * (1 + (a[j] & (t - 1)));
                dp[j][0][1] += dp[j - 1][0][1] * (1 + (a[j] & (t - 1)));
                dp[j][1][0] += dp[j - 1][1][0] * (1 + (a[j] & (t - 1)));
                dp[j][1][1] += dp[j - 1][1][1] * (1 + (a[j] & (t - 1)));
            }
        }
        if (tmp) 
            break;
        ans += dp[n][1][0];
    }
    cout << ans + (x == 0) - 1 << "\n";
    return 0;
}
```

---

## 作者：honglan0301 (赞：0)

## 题目分析

是好题。虽然数据范围过于小了，让我想了半天。。。

先想数位 $\text{dp}$，感觉不是很好做，因为你需要记录每个数的前 $j$ 高位是否都是顶着 $m_i$ 选的，状压下来直接就炸了。那么考虑异或与大小这两个性质之间的关系，发现更容易处理的是后者对前者的影响，因为当一个数的大小无限制时，其它数随便选都可以用它使异或和变成 $0$。也就是说我们并不需要知道具体是哪些数无限制，只要有一个数可以无限制地选，那么其它数就可以任选。

于是再按位考虑，异或在不同位之间互不影响，而大小当且仅当高位的 $a_i$ 与 $m_i$ 全相等时才受限制，于是我们自然想到枚举从高到低第一次出现 $(a_i\And 2^j)<(m_i\And 2^j)$ 的位数 $j$。此时高于 $j$ 的位是固定的，只需第 $j$ 位的异或和为 $0$ 且 $\exists\ (a_i\And 2^j)<(m_i\And 2^j) $ 即可如上文所说地任选低位。

我们这样想，对于每个 $a_i$ 容易求出第 $j$ 位选 $0,1$ 的方案数 $b_i,c_i$，然后我们求出 $f(x)=\prod\limits_{i=1}^n{(c_ix+b_i)}$，令 $cnt$ 表示 $\sum [m_i\And 2^j]$，于是能使第 $j$ 位异或和为 $0$ 的方案数且存在 $(a_i\And 2^j)<(m_i\And 2^j)$ 的合法方案数是 $\sum [i\bmod 2=0][i\neq cnt][x^i]f(x)$，因为其中有一个低位不受限的数要满足异或和为 $0$ （即相当于它被其它数固定了选法，而它的低位本身有 $2^j$ 种），所以这位的贡献是 $\displaystyle\frac{\sum [i\bmod 2=0][i\neq cnt][x^i]f(x)}{2^j}$。

以上的式子只是方便理解，事实上容易注意到这可以使用 $\text{dp}$ 在 $O(n)$ 的时间复杂度内完成。比如令 $f_{i,0/1,0/1}$ 表示考虑了前 $i$ 个数，异或和为 $0$ 还是 $1$，当前有还是没有 $(a_i\And 2^j)<(m_i\And 2^j)$ 的数。记 $d_i$ 表示 $m_i\bmod 2^j$，有简单的转移：

* 若 $m_i\And 2^j=0$，则对 $\forall j,k$ 有 $f_{i,j,k}=f_{i-1,j,k}\times (d_i+1)$。
* 若 $m_i\And 2^j=1$，则有：

$$
\begin{aligned}
& f_{i,0,0}=f_{i-1,1,0}\times(d_i+1)\\
& f_{i,1,0}=f_{i-1,0,0}\times(d_i+1)\\
& f_{i,0,1}=f_{i-1,1,1}\times(d_i+1)+(f_{i-1,0,0}+f_{i-1,0,1})\times {2^j}\\
& f_{i,1,1}=f_{i-1,0,1}\times(d_i+1)+(f_{i-1,1,0}+f_{i-1,1,1})\times {2^j}
\end{aligned}
$$

易知这一位对 $ans$ 的贡献即为 $\displaystyle\frac{f_{n,0,1}}{2^j}$。注意需要 $\bigoplus\limits_{i=1}^n m_i$ 的高位均为 $0$ 时才能计算此贡献，并且若 $\bigoplus\limits_{i=1}^n m_i$ 本身就为 $0$ 则也对 $ans$ 有 $1$ 的贡献。最后输出 $ans-1$，因为题目要求全 $0$ 不合法。

## 代码

```cpp
/*
  author: PEKKA_l  
 */
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define ll unsigned long long
#define int __int128

int ss,dp[2][2],g[2][2],cf[55];
ll n,m[55],ans;

signed main()
{
	cin>>n; for(int i=1;i<=n;i++) cin>>m[i],ss^=m[i]; if(!ss) ans++;
	cf[0]=1; for(int i=1;i<=40;i++) cf[i]=cf[i-1]*2;
	for(int i=31;i>=0;i--)
	{
		if(ss&cf[i+1]) break; dp[0][0]=1; dp[0][1]=dp[1][0]=dp[1][1]=0;
		for(int j=1;j<=n;j++)
		{
			memcpy(g,dp,sizeof(dp));
			if(m[j]&cf[i])
			{
				dp[0][0]=g[1][0]*((m[j]&(cf[i]-1))+1);
				dp[1][0]=g[0][0]*((m[j]&(cf[i]-1))+1);
				dp[0][1]=g[1][1]*((m[j]&(cf[i]-1))+1)+(g[0][0]+g[0][1])*cf[i];
				dp[1][1]=g[0][1]*((m[j]&(cf[i]-1))+1)+(g[1][0]+g[1][1])*cf[i];
			}
			else
			{
				dp[0][1]=g[0][1]*((m[j]&(cf[i]-1))+1);
				dp[0][0]=g[0][0]*((m[j]&(cf[i]-1))+1);
				dp[1][1]=g[1][1]*((m[j]&(cf[i]-1))+1);
				dp[1][0]=g[1][0]*((m[j]&(cf[i]-1))+1);
			}
		}
		ans+=(ll)((dp[0][1])/cf[i]);
	}
	cout<<ans-1<<endl;
}
```


---

