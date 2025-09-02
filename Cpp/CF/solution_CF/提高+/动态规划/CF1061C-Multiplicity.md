# Multiplicity

## 题目描述

给定一个整数数组 $a_1, a_2, \ldots, a_n$。

如果可以通过从 $a$ 中删除某些元素（可以不删除）得到数组 $b$，则称 $b$ 是 $a$ 的一个子序列。

如果数组 $b_1, b_2, \ldots, b_k$ 满足非空，且对于每个 $i$（$1 \le i \le k$），$b_i$ 能被 $i$ 整除，则称该数组是“好”的。

请你求出 $a$ 的“好”子序列的个数，答案对 $10^9 + 7$ 取模。

如果两个子序列所包含元素的下标集合不同，则认为它们是不同的子序列。也就是说，元素的值不影响子序列的区分。特别地，长度为 $n$ 的数组 $a$ 一共有 $2^n - 1$ 个不同的非空子序列。

## 说明/提示

在第一个样例中，所有三个非空子序列都是“好”的：$\{1\}$，$\{1, 2\}$，$\{2\}$。

在第二个样例中，所有可能的“好”子序列有：$\{2\}$，$\{2, 2\}$，$\{2, 22\}$，$\{2, 14\}$，$\{2\}$，$\{2, 22\}$，$\{2, 14\}$，$\{1\}$，$\{1, 22\}$，$\{1, 14\}$，$\{22\}$，$\{22, 14\}$，$\{14\}$。

注意，有些子序列会出现多次，因为它们在原数组中出现的位置不同。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
3```

## 样例 #2

### 输入

```
5
2 2 1 22 14
```

### 输出

```
13```

# 题解

## 作者：Realityang (赞：27)

### [题目传送门](https://www.luogu.com.cn/problem/CF1061C)

## [一种更好的题解食用方式](https://www.cnblogs.com/yang-RA-NOI/p/12595597.html)

# 题目大意
$有个长度为n的序列a，你需要统计a中有多少个棒棒的子序列$

$一个序列b被定义为棒棒的，当且仅当：$

对于序列中每一个位置$i，b_i$都能够被i整除

答案对$10^9+7 $取模
### 数据范围
$\circ$ $n\le10^5$

$\circ$ $1\le a_i\le10^6$
# 题解
这题可能是最近几道题里最简单的一道了

不难想到暴力做法：

$dp_{i,j}$指枚举到i点，b序列长度为j的方案个数

$则状态转移方程是：$

$dp_{i,j}=dp_{i-1,j}+(a_i$%$j==0)\times dp_{i-1,j-1}$

这样暴力的复杂度是$O(n^2)$的，会超时

于是考虑一下优化

试着维护一下二维前缀和

然后可以新添的长度$j$要求是$a_i$的因数

于是可以试着枚举$a_i$的所有因数

DP一下这个$a[i]$对所有因数（就是可能长度）的贡献（好吧本人蒟蒻难以准确说明，具体见代码吧）

复杂度是根号级别的

所以总复杂度就会是$O(n\sqrt n)$的了

因为$n$是$10^5$的，于是可以3秒跑过了

具体实现看下面代码↓↓↓

# AC代码：
```
#include<bits/stdc++.h>
#define ll  long long
using namespace std;
ll n,ans,mod=1e9+7;
ll a[1000010],f[1000010];//用于dp的f[i]表示目前为止长度为i的合法序列个数 
ll w[1000010];//存放a[i]的每一个因数 
int main(){
	cin>>n;
	for(ll i=1;i<=n;++i)cin>>a[i];
	f[0]=1;//为了使f能够合乎常理（？）地DP 
	for(ll i=1;i<=n;++i){
		ll qq=sqrt(a[i]),top=0;
		for(ll j=1;j<=qq;j++){
			if(a[i]%j==0){
				w[++top]=j;
				if(j*j!=a[i])//这句缺失会导致错误，如1,1,2->5就WA了 
					w[++top]=a[i]/j;
			}
		}
		sort(w+1,w+top+1);
		for(ll j=top;j>=1;--j){
			f[w[j]]=(f[w[j]]+f[w[j]-1])%mod;
		}
	}
	for(ll i=1;i<=n;++i)ans=(ans+f[i])%mod;
	cout<<ans;
} 
```
### 支持一下吧，点赞，评论都好！

# THE END


---

## 作者：一扶苏一 (赞：16)

## Description

给定一个序列 $a$，求有多少非空序列 $b$ 满足 $b$ 是 $a$ 的子序列并且 $\forall~k~\in~[1,len_b],~~k \mid b_k$，其中 $len_b$ 是 $b$ 的长度。答案对 $1e9+7$ 取模

## Input

第一行是序列 $a$ 的长度 $n$

下面一行 $n$ 个整数，代表序列 $a$

## Output

输出一行一个整数代表答案

## Hint

$1~\leq~n~\leq~100000~,~1~\leq~a_i~\leq~10^6$

## Solution

总觉得这题是假的= =

考虑DP。我们设 $f_{i,j}$ 为考虑 $a$ 中前 $i$ 个数，填充到 $b$ 中 $j$ 个的方案数

方程显然：

当 $j~\nmid~a_i$ 时：

$$f_{i,j}~=~f_{i - 1, j}$$

否则：

$$f_{i,j}~=~f_{i - 1}{j}~+~f_{i - 1}{j - 1}$$

考虑这个方程的状态是 $O(n~\max(a_i))$ 的，显然过不去，于是考虑优化：

我们发现能取到第二条转移方程当且仅当 $j$ 是 $a_i$ 的因数，而第一种第一种转移方程可以使用滚动数组直接省略掉。于是我们直接枚举 $a_i$ 的因数，只在因数位置进行转移。同时注意因为 $i$ 相同时的 $f$ 时不能互相影响，所以对因数的转移要从大到小进行

考虑这么做的复杂度：

一共有 $n$ 个数，每个数的因数是 $O(\sqrt{a_i})$，同时排序需要 $O(\sqrt {a_i}~\times~\log (\sqrt{a_i}))$，总复杂度 $O(n~\sqrt{a_i}~\log (\sqrt{a_i}))$。

看起来根本过不去有木有= =

但是考虑因数个数事实上是一个很松的上界，经过实际测试，$[1,10^6]$ 范围内因数个数最多的数的因数不过 $240$ 个，测试结果如下：

![qwq](https://cdn.luogu.com.cn/upload/pic/47892.png)

于是本题的实际复杂度为 $\Theta(n~\times~d(a_i)~\log (d(a_i)))$，其中 $d(a_i)~\leq~240$

于是就可以轻松通过本题辣

## Code

```cpp
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 100010;
const int maxt = 1000010;
const int MOD = 1000000007;

int n;
int MU[maxn];
ll frog[maxt];
std::vector<int>p;

int main() {
	freopen("1.in", "r", stdin);
	qr(n);
	for (rg int i = 1; i <= n; ++i) qr(MU[i]);
	frog[0] = 1;
	for (rg int i = 1; i <= n; ++i) {
		p.clear();
		for (rg int j = 1, sn = sqrt(MU[i]); j <= sn; ++j) if (!(MU[i] % j)) {
			int k = MU[i] / j;
			p.push_back(k); 
			if (k != j) p.push_back(j);
		}
		std::sort(p.begin(), p.end());
		for (rg int j = p.size() - 1; ~j; --j) {
			frog[p[j]] = (frog[p[j]] + frog[p[j] - 1]) % MOD;
		}
	}
	ll ans = 0;
	for (rg int i = 1; i <= n; ++i) ans = (ans + frog[i]) % MOD;
	qw(ans, '\n', true);
	return 0;
}
```

## Summary

一个数的因数个数是 $O(\sqrt{n})$ 是一个非常松的上界，事实上，在100万范围内因数个数最多的数的因数不过240个。遇到更大的范围可以 $O(n \ln n)$ 筛出所有数的因数来取得实际个数。

---

## 作者：CGDGAD (赞：4)

## 题解 CF1061C【Multiplicity】

----

### 题目大意

在长度为 $n$ 的数列 $a$ 中，找出一个非空子序列 $b$，使得 $b$ 中每一个元素的值都能被其对应在 $b$ 中的下标整除。求这样的 $b$ 的个数。

----

### 基础分析

假如我们不看数据范围，很容易直接想到一种最简单的 dp。

设 $f(x,y)$ 为前 $x$ 个数里选 $y$ 个数的方案数，显然：

$$
f(x,y) =
\begin{cases}
f(x-1, y) + f(x-1,y-1) & y \mid a_x \\
f(x-1,y) & otherwise.
\end{cases}
$$

但是由于 $1 \le n \le 10^5$，这种做法的时间复杂度和空间复杂度都会瞬间爆炸，需要进行优化。

----

### 优化空间

很容易看出 dp 的第一维都是由 $x-1$ 推过来，于是可以滚动数组把这一维省略掉。省略后时间复杂度不变，核心代码如下：

```cpp
f[0] = 1;
for (int x = 1; x <= n; ++x)
  for (int y = x; y >= 1; ++y)
    if (a[x] % y == 0)
      f[y] += f[y - 1];
```

**注意：** 以原来二维的 dp 方式，对于 $f(x,y)$ 的更改是不会影响 $f(x-1,y),f(x-1,y-1)$ 的。但现在，没有了第一维 $x$ 和 $x - 1$ 的区分，更改 $f(y)$ 的时候就会影响原来的 $f(y)$ 和 $f(y-1)$，导致计算错误。倒着枚举 $y$ 就不会出现这样的问题。

----

### 优化时间

整个算法时间复杂度最高的地方在哪里？发现一个个判断 $y$ 是否整除 $a_x$ 是很累的，时间复杂度达 $O(n)$。

可以发现，**只有是 $a_x$ 的因数且小于等于 $x$ 的 $y$ 才需要进行特殊处理**，而这类数其实占比很少，一个个判断很耗时间。

于是可以 $O(\sqrt n)$ 提前找出所有 $a_x$ 的因数，再对于 $a_x$ 所有小于等于 $x$ 的因数 $y$ 进行 dp 即可。

输入的时候，把 $a_x$ 的所有因数一一存好，并从大到小排序，等到 dp 的时候可以直接用。当然，也可以在 dp 的第一层循环内对于 $a_x$ 分解因数，两者是一样的。

这一部分可以使用 `std::vector` 来实现。

注意，仍需从大到小遍历 $y$。

----

### 代码实现

```cpp
signed main() {
	n = read();
	for (int i = 1; i <= n; ++i) {
		int a = read();
		for (int p = 1; p * p <= a; ++p)
			if (a % p == 0) {
				factors[i].push_back(p);
				if (p * p != a)
					factors[i].push_back(a / p);
			}
		std::sort(factors[i].rbegin(), factors[i].rend()); // 利用 vector 的 rbegin, rend 从大到小排序。
	}
	f[0] = 1;
	for (int x = 1; x <= n; ++x)
		for (int y : factors[x]) {
			if (y > x) continue; // y <= x 时才需 dp。
			f[y] = (f[y] + f[y - 1]) % MOD;
		}
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		ans = (ans + f[i]) % MOD;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：BoAn (赞：3)

对于任意一个 $a_i$，设它的第 $j$ 个因数为 $y_j$，那么以 $a_i$ 结尾的、长度为 $y_j$ 的合法子序列的个数，由在它之前的长度为 $y_j-1$ 的子序列的个数决定。

设 $f_i$ 表示长度为 $i$ 的合法子序列的个数，结合乘法原理，推出状态转移方程：

$f_{y_j}=f_{y_j}+f_{y_j-1}$

由于是按顺序 $1->n$ 遍历 $a$，所以不会出错。

线性遍历一遍数组，每次用 $\sqrt{a_i}$ 的效率求出 $a_i$ 的因数，所以复杂度是$O(n\sqrt{\max{a_i}})$？错。

对于 $2$ $|$ $j$，有 $y_j=\dfrac{a_i}{y_{j-1}}$，所以 $y$ 并不是递增的，这样会造成一个错误，就是当 $y_j-1$ $|$ $a_i$ 时，答案会多 $+1$，因为 $y_j-1$ 已经作为 $a_i$ 的因数遍历过了，此时长度为 $y_j-1$ 的合法子序列的个数中已经包括以 $a_i$ 结尾的了，如果再计算 $y_j$，就会有多个 $a_i$ 出现在子序列里，这显然是不合法的。

可能有点难理解，举个最简单的例子。数字 $2$，在计算它的第一个因数 $1$ 时，长度为 $1$ 的合法子序列个数为 $1$。计算第二个因数 $2$ 的时候，它一看，诶在我前面已经有一个长度为 $1$ 的合法子序列了，那我就接在它后面吧，所以这时它会认为长度为 $2$ 有一个，这时候 $2$ 就用了两次。

所以找完所有因数后，还要排序，**从大到小**遍历。设 $a$ 中因数最多的数的因数个数为 $x$，所以正确的复杂度应该是 $O(n \max(\sqrt{\max{a_i}},x \log x))$。

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
const int mod=1e9+7;
long long n,a[1000010],f[1000010],ans,y[1000010];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    f[0]=1;//使单独一个数能成为合法子序列
    for(int i=1;i<=n;i++){
    	int top=0;
    	for(int j=1;j<=sqrt(a[i]);j++){
    		if(a[i]%j)continue;
			y[++top]=j;
			if(j*j!=a[i])y[++top]=a[i]/j;
		}//求因数 
		sort(y+1,y+top+1);//排序 
    	for(int j=top;j>=1;j--)
    		f[y[j]]=(f[y[j]]+f[y[j]-1])%mod;//状态转移方程 
	}
	for(int i=1;i<=n;i++)
		ans=(ans+f[i])%mod;
	cout<<ans;
    return 0;
}
```


---

## 作者：尹昱钦 (赞：1)

### 题解中的做法全部多带了一个 log，这里提供省去 log 的方法。

------
## 解题思路
基本的解题思路大致相同，简单说一下。

**最朴素的 dp 为：$dp_{i,j}$ 为前 $i$ 个数选 $j$ 个方案数。**

$O(n^2)$ 的时空复杂度，很显然会炸，所以需要优化。

先考虑空间，第一维可以**滚动数组**滚掉，因为选的第 $j$ 个数与上一个数是什么没关系。

再考虑时间上，尝试对于每个 $a[i]$，**只枚举符合条件的 $j$，即枚举其因数（根号复杂度）。**

注意：因为使用了滚动数组，所以**因数要从大到小枚举**。

题解中都是sort一遍，会多出一个log的复杂度，然而其实**可以用一个栈一个队列维护。**

依次求出来的因数都是**单调**的（一个单调递增，一个单调递减），于是把较小的因数放到一个栈中，把较大的因数放到一个队列里，最后先遍历队列再遍历栈即可完成排序工作，这样就省掉了一个 log，在理论上也可以稳过了。

所以最后**时间复杂度就是 $O(n\sqrt n)$**。
## AC代码
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
using namespace std;
const int maxn=1e6+5;
const int mod=1e9+7;
int n,a[maxn],dp[maxn],ans;
queue<int> q;
stack<int> s;
template<class T>inline void read(T &x)
{
    x=0;register char c=getchar();register bool f=0;
    while(!isdigit(c))f^=c=='-',c=getchar();
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
    if(f)x=-x;
}
int main(){
	ios::sync_with_stdio(false);
	read(n);
	for(int i=1;i<=n;i++) read(a[i]);
	dp[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j*j<=a[i];j++){//求因数并省掉排序的log
			if(a[i]%j==0){
				s.push(j);
				if(j*j!=a[i]) q.push(a[i]/j);
			}
		}
		while(!q.empty()){//先遍历队列，再遍历栈，保证了单调递减
			dp[q.front()]=(dp[q.front()]+dp[q.front()-1])%mod;
			q.pop();
		}
		while(!s.empty()){
			dp[s.top()]=(dp[s.top()]+dp[s.top()-1])%mod;
			s.pop();
		}
	}
	for(int i=1;i<=n;i++) ans=(ans+dp[i])%mod;
	cout<<ans;
    return 0;
}
```

---

## 作者：pitiless0514 (赞：1)

## 题目大意
有一个长度为 $n$ 的序列 $a$，请你计算里面符合要求的子序列 $b$ 的数目。

子序列满足 $\forall\ i \in [1,\ k],\ i\ |\ b_i$ 性质被称为符合要求。 

## 解析

一道普通的 dp 题。

考虑朴素的暴力设计状态，由于题目没有规定长度。

所以可以加一维限制，设立状态 $f_{i,j}$ 表示从前 $i$ 个中选出 $j$ 个构成的合法方案数。

那么状态转移方程就是：

当 $j \ | \  a_i$ 时 $f_{i,j}=f_{i-1,j}+f_{i-1,j-1}$

否则 $f_{i,j}=f_{i-1,j}$

首先空间复杂度就已经爆炸了，不过我们可以通过滚动数组的方法进行优化，于是空间的问题先解决了。

然后考虑时间复杂度，这个时间复杂度为 $n^2$ 的。

我们发现我们的时间主要浪费在的就是第一种情况上。


那么我们可以每次先处理出 $a_i$ 的因数。

但这样仍然不知道怎么做。

因为你每次弄完总得复制一遍，复制的时间弄下来还是 $n^2$ 。

你考虑到第二种的情况其实是值不变的。

直接在一个数组上去做，只在因数部分修改答案。

但是这么做的话，如果顺序枚举会让我们的答案受影响。

于是倒序枚举，然后就没问题了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline char nc(){
 static char buf[100000],*p1=buf,*p2=buf;
 return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
 char ch=nc();int sum=0;
 while(!isdigit(ch))ch=nc();
 while(isdigit(ch))sum=sum*10+ch-48,ch=nc();
 return sum;
}
const int N  = 2e6,M = 1e6, mod = 1e9+7;
int n,k,ans,a[N],f[N],g[N];
int s[N],num;
void get(int x){
 int lim=sqrt(x);num=0;
 for(int i=1;i<=lim;i++){
  if(x%i==0){
   s[++num]=i;
   if(i*i!=x) s[++num]=x/i;
  }
 }
}
signed main(){
 n=read();
 for(int i=1;i<=n;i++) a[i]=read();f[0]=1;
 for(int i=1;i<=n;i++){
  get(a[i]);
  sort(s+1,s+num+1);
  for(int j=num;j;j--){
   f[s[j]]=(f[s[j]]+f[s[j]-1])%mod;
  }
 }
 for(int i=1;i<=n;i++) ans=(ans+f[i])%mod;
 printf("%lld\n",ans);
 return 0;
}


```

---

## 作者：A_Pikachu (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1061C)
（如果 $\LaTeX$ 炸了，请到博客[观看](https://www.luogu.com.cn/blog/thats-me/ti-xie-cf1061c-multiplicity)）

$\Large\mathscr{Part\,\,1\;\;}\text{基本思路}$

此题方案涉及两个有序数组，不难想到用两维动态规划记录法案数。设 $f[i][j]$ 表示方案计算到 $a_i$，且已经选到 $b_j$ 的方案数。

先考虑状态继承。易得 $f[i][j]=f[i-1][j]$。

再考虑状态转移。因为 $j \mid b_j$ 才算一种合法方案，所以仅当此时，$f[i][j]$ 还要加上 $f[i-1][j-1]$。

这样显然不行，分析转移条件。因为数组是有序的，所以 $a_i$ 必然不能成为 $(j>i)\ b_j$。也就是说，转移时无需判断 $a_i$ 是否被大于 $i$ 的数整除。更进一步地，$a_i$ 只有在当 $j \mid a_i$ 且 $j \leq i$ 时才会对转移有贡献，则可以直接通过 $a_i$ 有序地转移状态。

~~打表发现~~一个百万内的数在十万内的因数是很少的（不到一千），实际上不会超过 $\sqrt{n}$ 个，那么我们的时间复杂度就有了保障，为 $\Theta(n \sqrt{a}+n\sqrt{n})$，包含了找因数和动态规划两部分。

两维的空间貌似有点大，由于转移时仅用到了第一维的前一状态，则将第一维滚动掉，第二维从大到小枚举。

$\Large\mathscr{Part\,\,2\;\;}\text{Code}$

```cpp
#include <cstdio>
const int N=1e5+5,M=1e6+5,B=1e3+5,MOD=1000000007;
int n,u,ans,fc[B],f[N];
int main(){
	scanf("%d",&n);
	f[0]=1;
	for(int i=1; i<=n; i++){
		scanf("%d",&u);
		int cnt=0;
		for(int j=1; j*j<=u&&j<=i; j++){
			if(u%j) continue;
			fc[++cnt]=j;
		}
		for(int j=1; j<=cnt; j++){
			if(u/fc[j]>i) continue;
			f[u/fc[j]]=(f[u/fc[j]]+f[u/fc[j]-1])%MOD;
		}
		for(int j=(fc[cnt]*fc[cnt]==u?cnt-1:cnt); j>=1; j--) f[fc[j]]=(f[fc[j]]+f[fc[j]-1])%MOD;
	}
	for(int i=1; i<=n; i++) ans=(ans+f[i])%MOD;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：1)

Update：上传成 wa 的代码了，已修改。

dp 题。

设 $dp_{i,j}$ 表示从 $a$ 中前 $i$ 个数中选取一个长度为 $j$ 的符合要求的子序列的数量，最终答案显然是 $\sum dp_{n,i}$。

当 $a_i$ 是 $j$ 的倍数时，显然 $dp_{i, j} = dp_{i - 1,j} + dp_{i - 1,j - 1}$；当 $a_i$ 不是 $j$ 的倍数时，$dp_{i, j} = dp_{i - 1,j}$。

所以状态转移方程是

$dp_{i,j} = \begin{cases} dp_{i - 1, j} + dp_{i - 1, j - 1} &{j\ |\ a_i} \\ dp_{i - 1, j} &{\sf{otherwise}} \end{cases}$

但是注意到这个空间和时间都会寄，所以考虑优化。


我们注意到 $dp_{i, j}$ 只与 $dp_{i - 1, j}$ 有关，所以前面那些就不用保存了。

还可以注意到，$dp_j$ 会变化，当且仅当 $j\ |\ a_i$，而我们可以在 $\mathcal O(\sqrt x)$ 的时间复杂度内找到 $x$ 的因子。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define pb push_back

#define rep(i, l, r) for (auto i = (l); i <= (r); ++i) 

const int N = 1e6 + 5,
          mod = 1e9 + 7;
LL a[N], dp[N];

int main() {
  LL n; cin >> n;
  dp[0] = 1;
  rep (i, 1, n) {
    cin >> a[i];
    vector<LL> v;
    for (LL j = 1; j * j <= a[i]; ++j) {
      if (a[i] % j == 0) {
        v.push_back(j);
        if (j != a[i] / j) v.push_back(a[i] / j);
      }
    }
    sort(v.begin(), v.end(), greater<LL>());
    for (auto i : v) {
    //  (dp[i] += dp[i - 1]) %= mod;
      dp[i] += dp[i - 1]; dp[i] %= mod;
    }
  }
  LL ans = 0;
  rep (i, 1, n) {
    // (ans += dp[i]) %= mod;
    ans += dp[i]; ans %= mod;
  }

  printf("%lld", ans % mod);
}
```

---

## 作者：XiaoQuQu (赞：0)

一道 DP 优化的好题。

## Part 1. 状态

显然我们不能只以 $f_i$ 表示前 $i$ 个数所能产生的最大答案，因为我们无法确定 $a_i$ 到底能插进哪些个好序列的末尾。

考虑到 $a_i$ 在新序列里的位置与序列长度有关，所以我们设 $f_{i,j}$ 为考虑前 $i$ 个数，产生的好序列长度为 $j$ 的方案数。

## Part 2. 转移

$a_i$ 能插进一个好序列的末尾，当且仅当这个序列的长度 $j$ 是 $a_i$ 的一个因子，所以我们有以下转移。

1. $a_i$ 是 $j$ 的倍数，则 $f_{i,j}=f_{i-1,j}+f_{i-1,j-1}$。
2. $a_i$ 不是 $j$ 的倍数，则 $f_{i,j}=f_{i-1,j}$。

## Part 3. 优化

时间复杂度与空间复杂度都是 $\text{O}(n^2)$ 的，显然无法通过。于是考虑优化。

首先是空间，观察转移方程，发现在转移 $f_{i,j}$ 的时候只使用到了 $f_{i-1,j}$ 与 $f_{i-1,j-1}$，考虑把 $i$ 这一维压掉。压掉之后，我们发现了一个比较好的性质，就是 **如果 $j$ 不是 $a_i$ 的因数，则 $f_j$ 不变**。

于是我们只需要管 $j$ 是 $a_i$ 因数的情况，直接枚举 $a_i$ 的每个因子，然后转移就好了，这样时间复杂度也被压到了 $O(n\sqrt n)$，在这里默认 $a_i$ 与 $n$ 同阶。

```cpp
const int MAXN = 1e6 + 5, mod = 1e9 + 7;
int n, f[MAXN], a[MAXN], d[MAXN], t;

signed main(void) {
    ios::sync_with_stdio(false), cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        t = 0;
        for (int j = 1; j * j <= a[i]; ++j) {
            if (a[i] % j) continue;
            d[++t] = j;
            if (j * j != a[i]) d[++t] = a[i] / j;
        }
        sort(d + 1, d + 1 + t, greater<int>());
        for (int j = 1; j <= t; ++j) f[d[j]] = (f[d[j]] + f[d[j] - 1]) % mod;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) ans = (ans + f[i]) % mod;
    cout << ans << endl;
    return 0;
}
```

在以后遇到这种维度较高的情况，可以观察转移方程考虑压维。


---

