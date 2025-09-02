# [ABC050D] Xor Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc050/tasks/arc066_b

正の整数 $ N $ が与えられます。 $ 2 $ つの整数 $ u,v(0≦u,v≦N) $ であって、ある非負整数 $ a,b $ が存在して、$ a $ $ xor $ $ b=u $、$ a+b=v $ となるようなものが何通りあるかを求めてください。 ここで、$ xor $ はビットごとの排他的論理和を表します。 なお、答えは非常に大きくなることがあるので、$ 10^9+7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1≦N≦10^{18} $

### Sample Explanation 1

$ u,v $ としてありうるものは、以下の $ 5 $ 通りです。 - $ u=0,v=0 $（ $ a=0,b=0 $ とすると、$ 0 $ $ xor $ $ 0=0 $、$ 0+0=0 $ となります。） - $ u=0,v=2 $（ $ a=1,b=1 $ とすると、$ 1 $ $ xor $ $ 1=0 $、$ 1+1=2 $ となります。） - $ u=1,v=1 $（ $ a=1,b=0 $ とすると、$ 1 $ $ xor $ $ 0=1 $、$ 1+0=1 $ となります。） - $ u=2,v=2 $（ $ a=2,b=0 $ とすると、$ 2 $ $ xor $ $ 0=2 $、$ 2+0=2 $ となります。） - $ u=3,v=3 $（ $ a=3,b=0 $ とすると、$ 3 $ $ xor $ $ 0=3 $、$ 3+0=3 $ となります。）

## 样例 #1

### 输入

```
3```

### 输出

```
5```

## 样例 #2

### 输入

```
1422```

### 输出

```
52277```

## 样例 #3

### 输入

```
1000000000000000000```

### 输出

```
787014179```

# 题解

## 作者：皎月半洒花 (赞：12)

这个题有许多有趣的做法，这个地方说一种实现很简单但很有趣的做法。

考虑 

$$
a+b=((a~\mathrm{and}~b)<<1)+(a~\mathrm{xor}~b)
$$

这个式子的意义在于，后半部分是因为异或运算是二进制下不进位的加法，前半部分则是在描述二进制下的进位。反正无论怎么样，我们可以轻松得到 $a+b\geq  a~\mathrm{xor}~b$ 这样的结论。

那么如果由于 $u\leq v$，所以如果 $v$ 不越界那么 $u$ 一定不越界。于是考虑按 $v$ 进行 $dp$。具体的，考虑状态 $f_{i,j}$ 表示考虑了 $a$ 和 $b$ 二进制下的前 $i$ 位，当前 $v=a+b=j$ 的方案数。

考虑如何转移。对于 $a$ 和 $b$ 而言，第 $i$ 位有三种情况，$(0,0),(0,1),(1,1)$ 。那么也就是假设原来的和为 $j'$，和当前的和 $j$ 可能有以下关系：

1、$2\cdot (j'+1)=j$，对应着都补一位 $1$。

2、$2\cdot j'=j$，对应着都补一位 $0$ 。

3、$j'+ (j' + 1)=j$，对应着一个补 $1$ 一个补 $0$ 。

那么也就是

$$f_{i,j}=f_{i-1,\lfloor\frac{j}{2}\rfloor}+f_{i-1,\lfloor\frac{(j-1)}{2}\rfloor}+f_{i-1,\lfloor\frac{(j-2)}{2}\rfloor}$$

发现本质上，第一维状态随着第二维递减，且都是 $\Delta(\log)$ 级别，并且每次计算，必定存在三项中有两项是相等的，所以可知最后状态数一定介于 $\Omega(2\log N)\sim O(\log N)$ 之间，可以通过本题。

考虑把第一维压掉之后，就是另一篇题解的那种做法了。

代码实现十分naive，就不放了。


---

## 作者：Xy_top (赞：11)

题解中好像没怎么详细说明这个神秘的式子是怎么得到的，我就来说下我做这题的整个过程。

显然 $a\oplus b\leq a+b$，于是如果 $a+b\leq n$，那么 $a\oplus b$ 自然也小于等于 $n$。

看到数据范围，容易想让对每个二进制位数位 DP，但不好下手。不妨先设 $f_{i,j}$ 为考虑到二进制下的第 $i$ 位，当前已经考虑的 $a$ $b$ 和为 $j$ 时，有多少种不同的 $v$。

在当前考虑完的后面加一位二进制位的情况：

1. 填两个 $0$。此时和以及异或和都扩大到原来的两倍。

2. 填一个 $1$ 一个 $0$。此时和扩大到原来的两倍加一，异或和也是如此。

3. 填两个 $1$。和扩大到原来的两倍加二，异或和扩大到原来的两倍。

当然你可能会说填一个 $1$ 和一个 $0$ 有两种情况，但是为什么只被统计了一次？

很简单，这两种情况和以及异或和都是一样的，就被统计了一遍。

不理解的话看张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/d9dgoqb2.png)

所以 $f_{i,j}$ 这样转移：

1. $j\bmod 2=0$：$f_{i,j}\to f_{i,j}+f_{i-1,\frac{j}{2}}+f_{i-1,\frac{j-2}{2}}$。

2. $j\bmod 2=1$：$f_{i,j}\to f_{i,j}+f_{i-1,\frac{j-1}{2}}$。

于是能试着写出代码：

```cpp
#include <cmath>
#include <iostream>
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int f[64][10050];
int n, x, ans;
int main () {
	cin >> n;
	int x = ceil (log (n) / log (2) );
	int pre = 1;
	f[0][0] = f[0][1] = f[0][2] = 1;
	For (i, 1, x) {
		For (j, 0, n) {
			if (j % 2 == 0) {
				f[i][j] += f[i - 1][j / 2];
				if (j) f[i][j] += f[i - 1][(j - 2) / 2];
			} else f[i][j] += f[i - 1][(j - 1) / 2];
		}
	}
	For (i, 0, n) ans += f[x][i];
	cout << ans;
	return 0;
}
```

然后考虑优化，发现最终要求的是 $\sum\limits_{i=1}^n f_{x,i}$，所以设 $S_{i,j}$ 为 $\sum\limits_{k=1}^jf_{i,k}$，然后来考虑怎么转移。

此时直接暴力展开观察：

$S_{i,j}=f_{i,1}+f_{i,2}+f_{i,3}+f_{i,4}+f_{i,5}+f_{i,6}+f_{i,7}....$

$=f_{i-1,0}+f_{i-1,1}+f_{i-1,0}+f_{i-1,1}+f_{i-1,2}+f_{i-1,1}+f_{i-1,2}...$

把奇数和偶数的贡献分开：

$=(f_{i-1,0}+f_{i-1,1}+f_{i-1,2}+...+f_{i,\lfloor\frac{j - 1}{2}\rfloor})+[(f_{i-1,0}+f_{i-1,1}+f_{i-1,2}+f_{i-1,3}+...+f_{i-1,\lfloor\frac{j}{2}\rfloor})+(f_{i-1,0}+f{i-1,1}+f{i-1,2}+f{i-1,3}+...+f_{i-1,\lfloor\frac{j-2}{2}\rfloor})]$

$=S_{i,\lfloor\frac{j - 1}{2}\rfloor}+S_{i,\lfloor\frac{j}{2}\rfloor}+S_{i,\lfloor\frac{j-2}{2}\rfloor}$

这样就能写出递归代码：

```cpp
#include <cmath>
#include <iostream>
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, x;
int S (int x, int y) {
	if (y < 0) return 0;
	if (x == 0) return min (y, 2) + 1; 
	if (y > 1) return S (x - 1, y / 2) + S (x - 1, (y - 1) / 2) + S (x - 1, (y - 2) / 2);
	if (y > 0) return S (x - 1, y / 2) + S (x - 1, (y - 1) / 2);
	return S (x - 1, y / 2);
}
int main () {
	cin >> n;
	x = ceil (log (n) / log (2) );
	cout << S (x, n) << '\n';
	return 0;
}
```

然后继续考虑优化，发现对于 $S_{x,y}$ 而言，绝大多数情况对于一个 $y$，只有一个 $S_{x,y}$ 是在递归时用到的，其他的都没有被用到。

对于那些极少数情况，附上这个代码：

```cpp
#include <set>
#include <cmath>
#include <iostream>
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, x;
set <int> s[100005];
int S (int x, int y) {
	s[y].insert (x);
	if (y < 0) return 0;
	if (x == 0) return min (y, 2) + 1; 
	if (y > 1) return S (x - 1, y / 2) + S (x - 1, (y - 1) / 2) + S (x - 1, (y - 2) / 2);
	if (y > 0) return S (x - 1, y / 2) + S (x - 1, (y - 1) / 2);
	return S (x - 1, y / 2);
}
int main () {
//	cout << S (0, 1) << ' ' <<S (1, 1) << ' ' << S (2, 1) << '\n';
	cin >> n;
	x = ceil (log (n) / log (2) );
	cout << S (x, n) << '\n';
	For (i, 1, n) {
		if (s[i].size() == 2) {
			cout << *s[i].begin () << ' ' << i << "   " << *s[i].rbegin() << ' ' << i << '\n';
		}
	}
	return 0;
}
```

通过运行 $1$ 到 $10000$ 发现对于 $y=1$ 时，$x=0$ $x=1$ $x=2$ 可能同时出现，其他情况下均满足上述规律，而恰巧 $S_{0,1}=S_{1,1}=S_{2,1}$，天助我也。

于是设 $S_{y}$ 为 $S_{x,y}$，其中 $x$ 为唯一对应它的那一个 $x$。（当然对于 $y=1$ 时它的值就是 $2$，不符合这个规律）

那么得到 $S_{x} = S_{\lfloor\frac{x}{2}\rfloor}+S_{\lfloor\frac{x-1}{2}\rfloor}+S_{\lfloor\frac{x-2}{2}\rfloor}$，这就是题解中的式子。

当然其实直接在上面两维的那里记忆化就能过了，我只是证明下题解中的式子。

时间复杂度的证明题解里写的还行故不再证明。

代码：

```cpp
#include <map>
#include <cmath>
#include <iostream>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, x;
map <pair <int, int>, int> m;
const int mod = 1000000007;
int S (int x, int y) {
	if (m[make_pair (x, y)]) return m[make_pair (x, y)];
	if (y < 0) return 0;
	if (x == 0) return m[make_pair (x, y)] = min (y, 2LL) + 1;
	if (y > 1) return m[make_pair (x, y)] = (S (x - 1, y / 2) + S (x - 1, (y - 1) / 2) + S (x - 1, (y - 2) / 2) ) % mod;
	if (y > 0) return m[make_pair (x, y)] = (S (x - 1, y / 2) + S (x - 1, (y - 1) / 2) ) % mod;
	return m[make_pair (x, y)] = (S (x - 1, y / 2) ) % mod;
}
signed main () {
	cin >> n;
	x = ceil (log (n) / log (2) );
	cout << S (x, n) << '\n';
	return 0;
}
```


---

## 作者：MatrixCascade (赞：11)

少有的我能秒的 AT *2600...

首先有个显然的结论  $a+b=(a \land b)\times 2+(a \oplus b )$ 。证明的话可以考虑每一位上 $(0,1),(1,0),(1,1)$ 分别在两边被统计的次数。

设符合条件的一组解为 $(u,v)$，且 $u\ge v$，此时必须要满足的条件就是：设 $k=(u-v)$，那么 $k \mod 2=0$。  
此时你发现 $a\land b=k/2$，那么 $(a,b)$ 就分别为 $(k/2+p,k/2+q),p+q=v$  
于是 v 的每一个 $1$ 的位置必须分配在 $a,b$ 中的一个，且每个 $0$ 的位置 $a,b$ 在那一位也必须为 $0$。  
分析了一下就把条件简化成了 $t\land v=0$。（$t=k/2$）   
然后我们就会了 $n^2$ 的做法，去考虑用 dp 优化这个过程，但我们又不能把 $k,u,v$ 这种很大的变量设计进状态，根据套路很容易想到用 **数位 dp** 来减少记录无用的状态。具体的，设 $dp_{i,j,op}$ 表示考虑到前 $i$ 位，当前需要的**进位**是 $j$，$2\times t+v$ 的前 $i$ 位与 $n$ 的前 $i$ 位哪个更大（因为 $u$ 和 $v$ 要求 $\le n$，而 $u=2\times t+v\ge v$ 所以要记录这么一维状态，表示当前 $u$ 的大小和 $n$ 的大小比较）  
这里顺推比较容易实现，于是我们就直接顺推，转移的时候枚举当前位的 $(t,v)$ 分别是 $(0,0),(1,0),(0,1)$ 的情况分别转移，注意进位和大小要根据之前位和当前位而做改变。  
发现和 [这个题](https://www.luogu.com.cn/problem/CF1290F) 的套路简直是一模一样...

复杂度是 $10\log n$，随便跑跑都能过 ...

代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define int long long
#define YES puts("YES")
#define NO puts("NO")
#define Yes puts("Yes")
#define No puts("No")
#define edl puts("")
#define mc cerr<<"qwq\n"
#define error goto gg
#define def gg:
#define rd(x) x=read()
#define opl(x) printf("%lld",x)
#define opls(x) printf("%lld ",x)
#define opd(x) printf("%d",x)
#define opds(x) printf("%d ",x)
#define ver(x) for(int i=head[x];i;i=nxt[i])
#define up(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define pu(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define ft(x) for(int i=head[x];i;i=nxt[i])
#define upn up(i,1,n)
#define upm up(j,1,m)
#define pun pu(i,n,1)
#define pum pu(j,m,1)
#define up_(x) up(i,1,x)
#define pu_(x) pu(j,x,1)
#define ep emplace_back
#define fp for(auto to:
#define pf )
#define pii pair<int,int>
#define pis pair<int,string>
#define psi pair<string,int>
#define mkp make_pair
#define fi first
#define se second
#define mii map<int,int>
#define mis map<int,string>
#define msi map<string,int>
#define mvi map<vector<int>,int>
#define miv map<int,vector<int>>
#define rdn rd(n)
#define rdm rd(m)
#define rdk rd(k)
#define pb push_back
using namespace std;
int n, m, k;
int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}

#define inf 1000000000000000000ll
ll Max(ll a=-inf,ll b=-inf,ll c=-inf,ll d=-inf,ll e=-inf,ll f=-inf,ll g=-inf,ll h=-inf)
{
	return max(max(max(a,b),max(c,d)),max(max(e,f),max(g,h)));
}
ll Min(ll a=inf,ll b=inf,ll c=inf,ll d=inf,ll e=inf,ll f=inf,ll g=inf,ll h=inf)
{
	return min(min(min(a,b),min(c,d)),min(min(e,f),min(g,h)));
}
#undef inf
void chkmin(int &x,int y)
{
	if(x>y)x=y;
}
void chkmax(int &x,int y)
{
	if(x<y)x=y;
}
int dp[70][5][2];
const int mod=1e9+7;
signed main()
{
	int T=1;
	while(T--)
	{
		rdn;
		dp[0][0][0]=1;
		up(i,1,64)
		{
			int ii=i-1;
			int ps=((n>>(i-1))&1);
			up(j,0,4)
			{
				up(t,0,1)
				{
					int pre=dp[i-1][j][t];
					int nj,nt;
					nj=j+2;
					if(t==0&&(nj%2)>ps)nt=1;
					if(t==0&&(nj%2)<=ps)nt=0;
					if(t==1&&(nj%2)<ps)nt=0;
					if(t==1&&(nj%2)>=ps)nt=1;
					(dp[i][nj/2][nt]+=pre)%=mod;
					nj=j+1;
					if(t==0&&(nj%2)>ps)nt=1;
					if(t==0&&(nj%2)<=ps)nt=0;
					if(t==1&&(nj%2)<ps)nt=0;
					if(t==1&&(nj%2)>=ps)nt=1;
					(dp[i][nj/2][nt]+=pre)%=mod;	
					nj=j+0;
					if(t==0&&(nj%2)>ps)nt=1;
					if(t==0&&(nj%2)<=ps)nt=0;
					if(t==1&&(nj%2)<ps)nt=0;
					if(t==1&&(nj%2)>=ps)nt=1;
					(dp[i][nj/2][nt]+=pre)%=mod;
				}
			}
		}
		cout<<dp[64][0][0];edl;
	}
}
```


---

## 作者：Scintilla (赞：7)

**Description**

给定 $n$，求出有多少对 $(u, v)$ 满足 $u, v \in [0, n]$，且 $\exist a, b$ 满足 $a \oplus b = u$ 且 $a + b = v$。答案对 $10^9 + 7$ 取模。

$n \le 10^{18}$。

**Solution**

比较巧妙的一个题目。

因为异或是不进位的加法，所以 $a \oplus b \le a + b$ 即 $u \le v$。

考虑对应方法。我们不妨钦定一个数对 $(u, v)$ 的贡献由使得 $a \subseteq b$ 的 $(a, b)$ 计算，此处 $a \subseteq b$ 表示对于 $a$ 在二进制下为 $1$ 的每一位，$b$ 在二进制下的这一位也是 $1$，不难证明这样的 $(a, b)$ 是唯一的。上文提到 $u \le v$，所以我们可以枚举 $v$，设 $f_v$ 表示对于所有 $v' \le v$ 一共有多少对 $(u', v')$ 满足条件，我们把此时对应的 $a, b$ 的最低位去掉，因为 $a \subseteq b$，所以 $(a, b)$ 的二进制最低位只有 $(0, 0), (0, 1), (1, 1)$ 三种情况，分别转移，我们就能得到

$$ f_v = f_{\left\lfloor \frac{v}{2} \right\rfloor} + f_{\left\lfloor \frac{v - 1}{2} \right\rfloor} + f_{\left\lfloor \frac{v - 2}{2} \right\rfloor} $$

递归求解即可。时间复杂度 $\mathcal{O}(\log n)$。

---

## 作者：星沐 (赞：6)

### 这是一道数论题
#### 我发在讨论区了[题意翻译](https://www.luogu.org/discuss/show?postid=68860)
#### 大致题意如下：
#### 给定n的值，求有多少对（u，v）的范围满足 0≤u,v≤n，且存在两个非负整数a,b使得a+b=v,a xor（异或）b=u。


------------

#### 初始条件
#### d[0]=1;//(0,0)第一组 
#### d[1]=2; //(0,0)第一组 ，(1,1)第二组；


------------

#### 开始找规律找出递推式
#### d[x]=d[x/2]+d[(x-1)/2]+d[(x-2)/2]
#### 据网上axuhongbo大佬解释：
####   


####   其实在本质上看的二进制操作也比较好理解,要得到小于等于n的数,第一种操作是n/2即先将n>>1,然后n<<1,这样最后得到的数肯定不会超过n,第二种操作是（（N-1）/2）*2+（（N-1）/2），第三种操作是（（N-2）/2）*2+1   + （（N-2）/2）*2+1  ，三种操作目的很明显，完成递推且数对数对(a,b)进行的操作不能使a+b出现大于n的情况。



------------



```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;//不能用define，
//用define的话mod变成了double类型，
//所以要用const 来声明int类型的mod; 
map<int,int>d;//因为数据太大，数组开不下，n^18;
inline int read() //快读，不过多解释
{
    char ch=getchar();
    int x=0,q=1;
    while(ch>'9' || ch<'0')q=ch==45?-1:q,ch=getchar();
    while(ch>='0' && ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
    return x*q;
}
inline int solve(int x)//递归函数
{
	if(d[x]!=0)
		return d[x];
	else
	return d[x]=((solve(x/2)+solve((x-1)/2)+solve((x-2)/2)))%mod;
}
signed main()
{
	//初始条件
	d[0]=1;//a=b=0一组 
	d[1]=2; //a=b=0一组 ，a=b=1第二组； 
	int n;
	n=read(); 
	int ans=solve(n);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：bai_tang (赞：5)

只要有信念，就一定能成功！

### [题意](https://www.luogu.com.cn/problem/AT2272)
求 $0\le u,v\le n$ 满足存在 $x,y$ 异或为 $u$ 和为 $v$，$n\le 10^{18}$。

### 分析
这玩意直接计数比较无从下手，让我们考虑一些简单的性质吧。

我们发现问题作为位运算有着不错的性质，比如一个数对 $(u,v)$ 合法，那么 $(2u,2v),(2u+1,2v+1),(2u,2v+2)$ 也一定合法，而如果一个数对 $(u,v)$ 合法，考虑去掉最低位分类讨论，也必然是由于较低位的某种情况合法，因此，$(u,v)$ 合法的充分必要条件是它能被 $(0,0)$ 由上面的方法构造出来。

因此，设 $f(x)$ 为令 $v=x$，对应的 $u$ 的方案数，你发现 $f(0)=1,f(x)=f(\lfloor x/2\rfloor)+[x\bmod 2=0]f(x/2-1)$，然后我们的答案就是（同时我们有了 $O(n)$ 的做法）：
$$F(n)=\sum_{i=0}^nf(i)$$
咱们进行一次暴力推式子：
$$F(n)=\sum_{i=0}^nf(\lfloor i/2\rfloor)+\sum_{i=1}^n[i\bmod 2=0]f(i/2-1)$$
$$F(n)=[n\bmod 2=0]f(n/2)+2\sum_{i=0}^{\lfloor (n-1)/2\rfloor}f(i)+\sum_{i=0}^{\lfloor n/2\rfloor-1}f(i)$$
$$F(n)=[n\bmod 2=0]f(n/2)+2F(\lfloor (n-1)/2\rfloor)+F(\lfloor n/2\rfloor-1)$$
$$F(n)=F(\lfloor n/2\rfloor)+F(\lfloor (n-1)/2\rfloor)+F(\lfloor n/2\rfloor-1)$$
边界为 $F(0)=1$，用哈希表维护，可以直接计算，[代码](https://www.luogu.com.cn/paste/qqsjt712)。

还有另外一种理解方式：把三种操作形成的操作序列拿出来，发现它与每一个数对是一一对应的，因此你可以枚举最后一个操作是哪一种，可以得到完全相同的式子。

---

## 作者：lgswdn_SA (赞：4)

## ARC066B Xor Sum

首先 $u\le v$ 是非常显然的。

设 $f_v$ 表示对于 $v$ 有多少个符合要求的 $u$。

有一个有趣的性质，就是 $\lfloor\frac{a}{2}\rfloor\oplus\lfloor\frac{b}{2}\rfloor=\lfloor\frac{a\oplus b}{2}\rfloor$。

又因为这个 $10^{18}$ 如果不能 $O(1)$ 算的话应该是个 polylog 状物，所以看能不能从折半后的 $f$ 转移过来。

折半后必然涉及到奇偶不同的问题，于是分奇偶考虑。

如果 $v$ 是奇数，那么 $a,b$ 必定一奇一偶，于是又有 $\lfloor\frac{a}{2}\rfloor+\lfloor\frac{b}{2}\rfloor=\lfloor\frac{a+b}{2}\rfloor$，所以可以直接转移过来，即 $f_{2v+1}=f_v$。

如果 $v$ 是偶数，那么 $a,b$ 可能是全偶可能是全奇数，于是两种情况，其中全奇数的话 $\lfloor\frac{a}{2}\rfloor+\lfloor\frac{b}{2}\rfloor=\lfloor\frac{a+b}{2}\rfloor-1$，全偶的话和一奇一偶是一样的，所以有 $f_{2v}=f_v+f_{v-1}$。

我们要求的答案是 $f$ 的前缀和 $s$，我们不断拆 $f$ 可以得到
$$
s_i=
\begin{cases}
s_{k}+2s_{k-1} & i=2k\\
2s_{k}+s_{k-1} & i=2k+1
\end{cases}
$$
我们发现需要求的 $s$ 的数量在 $O(\log n)$，可以通过此题。

```cpp
int cal(int n) {
	if(s[n]) return s[n];
	if(n<=1) return s[n]=n+1;
	int k=n/2;
	if(n%2==0) return s[n]=(cal(k)+2*cal(k-1))%mod;
	else return s[n]=(2*cal(k)+cal(k-1))%mod;
}
```



---

## 作者：LittleMoMol (赞：3)

## [博客食用](https://www.cnblogs.com/LittleMoMol-kawayi/p/LuoGu_Solution_AT2272.html)

## 结论

1. $a+b = a \oplus b + (a \operatorname{and} b) \times 2$

2. 令 $f_j$ 表示 $a+b=j$ 的方案数，那么状态转移方程为 $f_j = f_{\frac{j}{2}} + f_{\frac{j-1}{2}} + f_{\frac{j-2}{2}}$，答案为 $f_n$.

## 理论基础

### 第一条结论

异或相当于不进位加法，在异或的基础上，考虑进位：对于 $a,b$ 在二进制下的每一位 $a_i, b_i$，$(a_i \operatorname{and} b_i) = 1$ 必然等价于 $a_i = b_i = 1$，那么这一位相加必然要进位，也就是左移一位。所以 $a+b = a \oplus b + (a \operatorname{and} b) \times 2$ （感觉不是很严谨）

### 状态定义

为什么要令 $f[j]$ 表示 $a+b=j$ 的方案数？

由第一条结论可以得到，$a \oplus b \le a + b$。

我们令 $u = a \oplus b,\ v = a + b$，那么满足 $u \le v$，我们只需对 $v$ 进行 DP，求方案数即可。

### 状态转移方程

这一步是重点，在此再提醒一下，$f[j]$ 表示 $a+b=j$ 对应的方案数！

我们令 $(x, y)_i$ 表示 $u,v$ 二进制下的第 $i$ 位数字填什么，那么只可能有三种情况：$(0,0)_i, (0,1)_i, (1,1)_i$。因为要满足 $u \le v$，所以 $(1,0)_i$ 不合法。

接下来我们举一个例子来理解状态转移方程

| 填数       | 二进制 $a$ | 二进制 $b$ | 十进制 $a$ | 十进制 $b$ | 十进制 $a+b$ |
| ---------- | ---------- | ---------- | ---------- | ---------- | ------------ |
| 原数       | $1101$     | $1001$     | $13$       | $9$        | $22$         |
| 填 $(0,0)$ | $11010$    | $10010$    | $26$       | $18$       | $44$         |
| 填 $(0,1)$ | $11010$    | $10011$    | $26$       | $19$       | $45$         |
| 填 $(1,1)$ | $11011$    | $10011$    | $27$       | $19$       | $46$         |

你会发现原数 $j$ 可以转移到 $2j,2j+1,2j+2$，那么状态转移方程就为：$f_j = f_{\frac{j}{2}} + f_{\frac{j-1}{2}} + f_{\frac{j-2}{2}}$

初始化：$f_0 = 1,f_1 = 2$，手算即可。

## 小细节

$N \le 10^{18}$ 存不下，可以用 $\operatorname{map}$ 来实现。

## Code

``` cpp
#include <iostream>
#include <map>

using namespace std;

typedef long long LL;

const LL mod = 1e9 + 7;

LL n, ans;
map<LL, LL> f;

LL clac(LL n)
{
	if (f[n] != 0) return f[n];
	return f[n] = (clac(n / 2) + clac((n - 1) / 2) + clac((n - 2) / 2)) % mod;
}

int main()
{
	cin >> n;
	f[0] = 1;
	f[1] = 2;
	ans = clac(n);
	cout << ans << endl;
	return 0;
}
```

完结撒花！

---

## 作者：NahX_ (赞：2)

# [ABC050D] Xor Sum

### 题意

给定一个数 $n$，求点对形如 $(x,y)$ 满足存在数 $a,b$ 使得 $a \oplus b = x$ 且 $a + b = y$ 的数量。

### 分析

首先分析题目中所给的条件：加法在二进制下能表示为 $a + b = (a \; and \; b) \times 2 + a \oplus b$，所以显然我们能得出结论 $a \oplus b < a + b$。

我们假设数 $a , b$，其中 $a \oplus b = u,a + b = v$，则 $u < v$。此时点对 $(u,v)$ 合法。此时我们考虑点对 $(u,v)$ 合法可以带来什么。将 $a \times 2,b \times 2$，此时无论 $a,b$ 最低位为 $0$ 或 $1$ 最终 $(a \oplus b) \div 2 = (a + b) \div 2$，此时分类讨论$a , b$ 最低位上的数:

用 $(x,y) \;\; (x,y \in [0,1])$ 表示 $a,b$ 最低位上的数分别为 $x,y$

1. $(0 , 0)$：此时 $ a\oplus b = u \times 2,a + b = v \times 2$，则 $(u \times 2,v \times 2)$ 合法。
2. $(1 , 1)$：此时 $ a\oplus b = u \times 2,a + b = v \times 2 + 2$，则 $(u \times 2,v \times 2 + 2)$ 合法。
3. $(1 , 0),(0 , 1)$：这两种情况 $ a\oplus b = u \times 2 + 1,a + b = v \times 2 + 1$，则 $(u \times 2 + 1,v \times 2 + 1)$ 合法。

综上所述，若点对 $(u , v)$ 合法，则点对 $(u \times 2,v \times 2),(u \times 2 + 1,v \times 2 + 1),(u \times 2 , v \times 2 +2)$ 均合法。

## solution

对于求满足条件的点对数，想到 dp。设 $f(x)$ 表示当 $v = x$ 时满足条件的 $u$ 的个数。初始状态 $f(0) = 1$。

根据分析我们可以得出状态转移方程：

$
f(x) = 
\begin{cases}
  x \mod 2 = 0: f(x \div 2) + f(x \div 2 - 1)\\
  x \mod 2 = 1: f((x-1) \div 2)\\
\end{cases}
$

 即 

$f(x) = f(\lfloor x \div 2 \rfloor) + [x \mod 2 =0]f(x \div 2 - 1)$

证明方案不重复计算：

当 $x \mod 2 = 0$：

$x \div 2$ 中必有一段形如 $1000...$ 且 $x \div 2 - 1$ 中此段形如 $0111...$ 则显然不存在数 $u$ 同时对于 $x \div 2$ 与 $x \div 2 - 1$ 满足条件。

题目就是求 $\sum_{i = 1}^{n} f(i)$。

这样做时间复杂度为 $O(n)$，无法通过。

我们设 $g(x)=\sum_{i = 1}^{x}f(i)$，根据状态转移方程可化简： 

$$
g(x)  = 
\sum_{i = 1}^{x} f(\lfloor i \div 2 \rfloor) + \sum_{i = 1}^{x}[i \mod 2 =0]f(i \div 2 - 1) \\ = 
2 \times g(\lfloor x \div 2 \rfloor) - [x \mod 2 = 0]f(x \div 2) + \sum_{i = 0}^{\lfloor x \div 2 \rfloor -1} f(\lfloor i \div 2 \rfloor)  \\=
2 \times g(\lfloor x \div 2 \rfloor) - [x \mod 2 = 0]f(x \div 2) + g(\lfloor x \div 2 \rfloor - 1)\\ \; \\
= g(\lfloor x \div 2 \rfloor) + g(\lfloor (x-1) \div 2 \rfloor) + g(\lfloor x \div 2 \rfloor - 1)
$$

所以我们可以直接对 $g(n)$  做 dp。时间复杂度 $O(log N)$。

---

#### code

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
map<int,int>dp;
int solve(int x){
	if(dp[x])return dp[x]%mod;
	return dp[x]=(solve(x/2)%mod+solve((x-1)/2)%mod+solve((x-2)/2)%mod)%mod;
}
signed main(){int n;cin>>n;
	dp[0]=1,dp[1]=2;
	cout<<solve(n);return 0;
}
```

---

## 作者：Krimson (赞：2)

这里提供一种比较好理解的证明方法  
令$f[i]$表示$v$=i的时候有多少组方案  
将$i$用二进制表示  
如果i是奇数，那应该是XXXXXX1的形式,而前面那一串为$\lfloor \frac{i}{2}\rfloor$,设其为k,即$i=2k+1$  
可以发现，对于任意符合$a+b=2k+1$,$a \ xor \ b=v$  
1.a为奇，b为偶  
$$
\frac{a}{2}+\frac{b}{2}=k 
$$
$$
\frac{a}{2} \ xor \ \frac{b}{2}=\frac{v}{2}
$$
2.a为偶，b为奇  
$$
\frac{a}{2}+\frac{b}{2}=k 
$$
$$
\frac{a}{2} \ xor \ \frac{b}{2}=\frac{v}{2}
$$  
可以发现两种情况是一样的，也就是对于任意的$k$所对应的$v_k$,将其乘2加1之后都可以于$2k+1$组成合法方案  
所以$f[2k+1]=f[k]$  
第二种情况,$i=2k$  
1.a为偶，b为偶  
$$
\frac{a}{2}+\frac{b}{2}=k 
$$
$$
\frac{a}{2} \ xor \ \frac{b}{2}=\frac{v}{2}
$$  

2.a为奇，b为奇
$$
\frac{a}{2}+\frac{b}{2}=k-1 
$$
$$
\frac{a}{2} \ xor \ \frac{b}{2}=\frac{v}{2}
$$  
所以$f[2k]=f[k]+f[k-1]$  
这个时候已经可以做到$O(n)$求出答案了  
接下来是推柿子time  
$$
sum[2k]=sum[2(k-1)]+f[k]+2f[k-1]=...\\ 
=f[k]+3f[k-1]+..+3f[2]+3f[1]+3f[0]=sum[k]+2sum[k-1]
$$  
然后奇数的情况  
$$
sum[2k+1]=sum[2k]+f[2k+1]=sum[2k]+f[k]=2sum[k]+sum[k-1]
$$  
所以只要递归下去做就可以了  
但是要加上记忆化，否则复杂度是错的  
至于复杂度的证明，可以发现每次递归会产生一个$sum[k],sum[k+1]$  
然而$k$和$k+1$除以二的整数部分都是一样的,所以对于$k$和$k+1$递归要求的东西都是一样的(如果没看懂可以自己随便用一个数字推一下)  
复杂度$O(2logn)$

---

## 作者：StarRoam (赞：1)

**[题目传送门](https://www.luogu.com.cn/problem/AT_arc066_b)**

易知 $$ a + b = a \oplus b + 2 \times (a \ \ and \ \ b) $$。

则 $$ a + b \ge a \oplus b $$。

所以我们通过枚举 $a + b$ 的合法方案以求答案。

记 $dp_{i,j}$ 表示：讨论到第 $i$ 位时，$a + b = j$ 的合法方案。

- 当 $j$ 为偶数时，第 $i$ 位可填 $(0,0)$ 或 $(1,1)$，有
$$dp_{i,j} = dp_{i-1,j/2}+dp_{i-1,(j-2)/2}$$ 

- 当 $j$ 奇数时，第 $i$ 位可填 $(0,1)$ 或 $(1,0)$，但是二者本质上是一致的，有

  $$dp_{i,j}=dp_{i-1,(j-1)/2}$$

记 $f_{i,j}$：
$$f_{i,j} = \sum_{k=0}^{j} dp_{i,k}$$

则 

$$ \begin{aligned}
f_{i,j} &= \sum_{k=0}^{j} dp_{i,k} \\
&=(dp_{i-1,0}) + (dp_{i-1,0}) + (dp_{i-1,0}+dp_{i-1,1}) + (dp_{i-1,1}) + \ldots \\
&=
(dp_{i-1,0} + dp_{i-1,1} + \cdots + dp_{i-1,\lfloor \frac{j-1}{2} \rfloor}) + (dp_{i-1,0} + dp_{i-1,1} +  \cdots +dp_{i-1,\lfloor \frac{j}{2} \rfloor }) + (dp_{i-1,0} + dp_{i-1,1} + \cdots +dp_{i-1,\lfloor \frac{j-2}{2} \rfloor}) \\
&=
\sum_{k=0}^{\lfloor \frac{j-1}{2} \rfloor} dp_{i-1,k} + \sum_{k=0}^{\lfloor \frac{j}{2} \rfloor} dp_{i-1,k} + \sum_{k=0}^{\lfloor \frac{j-2}{2} \rfloor} dp_{i-1,k} \\ 
&= f_{i-1,\lfloor \frac{j-1}{2} \rfloor} + f_{i-1,\lfloor \frac{j}{2} \rfloor} + f_{i-1,\lfloor \frac{j-2}{2} \rfloor}
\end{aligned}
$$

第一维可以省略。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD=1e9+7;
ll n;
map<ll,ll> f;
ll solve(ll x)
{
	if(f[x]) return f[x];
	return f[x]=(solve(x/2)+solve((x-1)/2)+solve((x-2)/2))%MOD;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	f[0]=1,f[1]=2;
	cout<<solve(n);
	return 0;
}
```

---

## 作者：Emptilife (赞：0)

这真是蓝？？


首要观察：

$a\operatorname{xor}b\le a+b$，因为异或是不进位的加法。此时只要求 $a+b=v\le n$。

关键观察：

若 $(u,v)$ 合法（即存在 $a,b$），则 $(2u,2v)$，$(2u+1,2v+1)$，$(2u,2v+2)$ 也必定合法。考虑后面新增一位，分讨 $a,b$ 新增 $(0,0),(1,0),(1,1)$ 可得。

设 $f(n)$ 表示 $a+b=v\le n$ 的合法 $(u,v)$ 数。有转移 $f(n)=f(\dfrac{n}{2})+f(\dfrac{n-1}{2})+f(\dfrac{n-2}{2})$，除法下取整。

递归次数 $O(\log n)$。每时刻只有 $x,x+1$ 在递归中。

---

