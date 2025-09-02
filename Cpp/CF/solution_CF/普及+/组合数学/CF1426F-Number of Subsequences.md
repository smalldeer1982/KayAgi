# Number of Subsequences

## 题目描述

You are given a string $ s $ consisting of lowercase Latin letters "a", "b" and "c" and question marks "?".

Let the number of question marks in the string $ s $ be $ k $ . Let's replace each question mark with one of the letters "a", "b" and "c". Here we can obtain all $ 3^{k} $ possible strings consisting only of letters "a", "b" and "c". For example, if $ s =  $ "ac?b?c" then we can obtain the following strings: $ [ $ "acabac", "acabbc", "acabcc", "acbbac", "acbbbc", "acbbcc", "accbac", "accbbc", "accbcc" $ ] $ .

Your task is to count the total number of subsequences "abc" in all resulting strings. Since the answer can be very large, print it modulo $ 10^{9} + 7 $ .

A subsequence of the string $ t $ is such a sequence that can be derived from the string $ t $ after removing some (possibly, zero) number of letters without changing the order of remaining letters. For example, the string "baacbc" contains two subsequences "abc" — a subsequence consisting of letters at positions $ (2, 5, 6) $ and a subsequence consisting of letters at positions $ (3, 5, 6) $ .

## 说明/提示

In the first example, we can obtain $ 9 $ strings:

- "acabac" — there are $ 2 $ subsequences "abc",
- "acabbc" — there are $ 4 $ subsequences "abc",
- "acabcc" — there are $ 4 $ subsequences "abc",
- "acbbac" — there are $ 2 $ subsequences "abc",
- "acbbbc" — there are $ 3 $ subsequences "abc",
- "acbbcc" — there are $ 4 $ subsequences "abc",
- "accbac" — there is $ 1 $ subsequence "abc",
- "accbbc" — there are $ 2 $ subsequences "abc",
- "accbcc" — there are $ 2 $ subsequences "abc".

So, there are $ 2 + 4 + 4 + 2 + 3 + 4 + 1 + 2 + 2 = 24 $ subsequences "abc" in total.

## 样例 #1

### 输入

```
6
ac?b?c```

### 输出

```
24```

## 样例 #2

### 输入

```
7
???????```

### 输出

```
2835```

## 样例 #3

### 输入

```
9
cccbbbaaa```

### 输出

```
0```

## 样例 #4

### 输入

```
5
a???c```

### 输出

```
46```

# 题解

## 作者：灵茶山艾府 (赞：17)

其他的题解好像都很麻烦的样子，这里说下我的思路。

遍历字符串，在每个 b 或 ? 上去计算答案，此时有四种组合成 abc 的方法：

1. 左边的 a 和右边的 c；
2. 左边的 ? 和右边的 c；
3. 左边的 a 和右边的 ?；
4. 左边的 ? 和右边的 ?；

记此时左边有 $a$ 个 a 和 $l$ 个 ?，右边有 $c$ 个 c 和 $r$ 个 ?，则上述四种的方案数为：

1. $a*c*3^{l+r}$
2. $l*c*3^{l-1+r}$
3. $a*r*3^{l+r-1}$
4. $l*r*3^{l+r-2}$

累加即得答案。

AC 代码（Golang）:

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
	"strings"
)

func main() {
	const mod int64 = 1e9 + 7
	var n int
	var s string
	Fscan(bufio.NewReader(os.Stdin), &n, &s)
	pow3 := make([]int64, n)
	pow3[0] = 1
	for i := 1; i < n; i++ {
		pow3[i] = pow3[i-1] * 3 % mod
	}
	c := int64(strings.Count(s, "c"))
	r := int64(strings.Count(s, "?"))
	var ans, a, l int64
	for _, b := range s {
		if b == 'a' {
			a++
		} else if b == 'c' {
			c--
		} else {
			if b == '?' {
				r--
			}
			ans += a * c % mod * pow3[l+r] % mod
			if l > 0 {
				ans += l * c % mod * pow3[l-1+r] % mod
			}
			if r > 0 {
				ans += a * r % mod * pow3[l+r-1] % mod
			}
			if l > 0 && r > 0 {
				ans += l * r % mod * pow3[l+r-2] % mod
			}
			if b == '?' {
				l++
			}
		}
	}
	Print(ans % mod)
}
```


---

## 作者：tommymio (赞：14)

非常套路的计数 $\text{DP}$ 题，不过对于一些 $\text{DP}$ 萌新来说确实很有意思。

设 $f[i,0/1/2]$ 表示前 $i$ 个字符构成的分别以 $a,b,c$ 结尾的子序列的个数，那么 $f[n,2]$ 即为答案。

考虑转移。

当 $a_i\neq \text{?}$ 时：
$$
\begin{cases}
f[i,0]=f[i-1,0]+3^{cnt_{i-1}}
\\
f[i,1]=f[i-1,1]+f[i-1,0]
\\
f[i,2]=f[i-1,2]+f[i-1,1]
\end{cases}
$$

当 $a_i= \text{?}$ 时：
$$
\begin{cases}
f[i,0]=f[i-1,0]\times 3+3^{cnt_{i-1}}
\\
f[i,1]=f[i-1,1]\times 3+f[i-1,0]
\\
f[i,2]=f[i-1,2]\times 3+f[i-1,1]
\end{cases}
$$

按上式转移，这题就做完了。

$cnt_{i}$ 表示前 $i$ 个字符中有 $cnt_i$ 个问号。这里解释一下 $3^{cnt_{i-1}}$ 的意义，之前的 $\text{?}$ 会将一个串变为 $3^{cnt_{i-1}}$ 个不同的串，每个串中都含有 $i$ 这个位置的字符 $\text{a}$（无论是从 $\text{?}$ 变换而来还是原先就是 $\text{a}$），所以需要计算 $3^{cnt_{i-1}}$ 次，其他的意义也是差不多的，都是为了统计 $\text{?}$ 对答案的影响。

记得开 $\text{long long}$ ，菜鸡不开 $\text{long long}$ $\text{WA}$ 了好几发，呜呜呜

**Show the Code**
```
#include<cstdio>
#define int ll
typedef long long ll;
const int mod=1e9+7;
int f[200005][3];
char s[200005];
signed main() {
	int n,pw=1;
	scanf("%lld%s",&n,s+1);
	for(register int i=1;i<=n;++i) {
		if(s[i]=='?') {
			f[i][0]=(3*f[i-1][0]%mod+pw)%mod;
			f[i][1]=(3*f[i-1][1]%mod+f[i-1][0])%mod;
			f[i][2]=(3*f[i-1][2]%mod+f[i-1][1])%mod; 
			pw=(ll)pw*3%mod;
		}
		else {
			f[i][0]=f[i-1][0];
			f[i][1]=f[i-1][1];
			f[i][2]=f[i-1][2];
			if(s[i]=='a') f[i][0]=(f[i][0]+pw)%mod;
			else f[i][s[i]-'a']=(f[i][s[i]-'a']+f[i-1][s[i]-'a'-1])%mod;
		}
	}
	printf("%d\n",f[n][2]);
	return 0;
}
```

---

## 作者：Karry5307 (赞：10)

### 题意

给定一个长度为 $n$ 的串，只包含 `abc` 和通配符。通配符可以替换 `abc` 的一个。求所有得到的字符串中**子序列** `abc` 出现的次数，对 $10^9+7$ 取模。

$\texttt{Data Range:}n\leq 2\times 10^5$

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13751412.html)

哇哈哈哈我智商终于恢复了。

比较套路，但其实这个东西我一开始是用类似于期望的东西来想的。

记通配符的数量为 $m$。

考虑设 $f_{i,j}$ 表示所有 $3^m$ 个字符串的前 $i$ 个字符中，子序列 `a`，`ab`，`abc` 的数量之和。

首先当给定字符串的第 $i$ 个字符为 `a` 的时候，有如下转移：

$$f_{i,1}=f_{i-1,1}+3^m,f_{i,2}=f_{i-1,2},f_{i,3}=f_{i-1,3}$$

为 `b` 的时候有如下转移：

$$f_{i,1}=f_{i-1,1},f_{i,2}=f_{i-1,2}+f_{i-1,1},f_{i,3}=f_{i-1,3}$$

为 `c` 的时候有如下转移：

$$f_{i,1}=f_{i-1,1},f_{i,2}=f_{i-1,2},f_{i,3}=f_{i-1,3}+f_{i-1,2}$$

这三个转移都很平凡，这里不多赘述。

接下来是为通配符的情况，需要讨论一下。

注意到我们肯定可以将所有 $3^{m}$ 个字符串中直到 $i-1$ 的前缀划分为三组，每组的字符串相同。

所以说每组字符串的中的 `a`，`ab`，`abc` 的数量变成了 $\frac{f_{i-1,1}}{3}$，$\frac{f_{i-1,2}}{3}$ 和 $\frac{f_{i-1,3}}{3}$。

于是考虑将第一组的后面加一个 `a`，第二组加一个 `b`，第三组加一个 `c`。这样子我们就可以写出一个转移方程：

$$\begin{cases}f_{i,1}=\frac{f_{i-1,1}+3^m}{3}+\frac{2f_{i-1,1}}{3}\\f_{i,2}=\frac{f_{i-1,2}+f_{i-1,1}}{3}+\frac{2f_{i-1,2}}{3}\\f_{i,3}=\frac{f_{i-1,3}+f_{i-1,2}}{3}+\frac{2f_{i-1,3}}{3}\end{cases}$$

整理一下得到以下转移：

$$f_{i,1}=f_{i-1,1}+3^{m-1},f_{i,2}=f_{i-1,2}+\frac{f_{i-1,1}}{3},f_{i,3}=f_{i-1,3}+\frac{f_{i-1,2}}{3}$$

线性 DP 就没了。

有一个加强版就是说多组询问求任意子段的答案。注意到 $f_{i}$ 只与 $f_{i-1}$ 有关所以可以写成一个 $4\times 4$ 的矩阵，然后用线段树维护矩阵乘积就好了。可能会算重，于是除掉一下就差不多了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51,MOD=1e9+7,INV3=333333336;
ll n,m,pw=1;
char ch[MAXN];
ll f[MAXN][3];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	n=read(),scanf("%s",ch+1);
	for(register int i=1;i<=n;i++)
	{
		ch[i]=='?'?m++,pw=(li)pw*3%MOD:1;
	}
	for(register int i=1;i<=n;i++)
	{
		f[i][1]=f[i-1][1],f[i][2]=f[i-1][2],f[i][3]=f[i-1][3];
		if(ch[i]=='a')
		{
			f[i][1]=(f[i][1]+pw)%MOD;
		}
		if(ch[i]=='b')
		{
			f[i][2]=(f[i][2]+f[i-1][1])%MOD;
		}
		if(ch[i]=='c')
		{
			f[i][3]=(f[i][3]+f[i-1][2])%MOD;
		}
		if(ch[i]=='?')
		{
			f[i][1]=(f[i][1]+(li)pw*INV3%MOD)%MOD;
			f[i][2]=(f[i][2]+(li)f[i-1][1]*INV3)%MOD;
			f[i][3]=(f[i][3]+(li)f[i-1][2]*INV3)%MOD;
		}
	}
	printf("%d\n",f[n][3]);
}
```

---

## 作者：Yizhixiaoyun (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/CF1426F)

今天模拟考第二水的题，应该也算签到了。

## 题目分析

首先这题在读题时就容易出错，请一定注意**子序列**与**字串**的区别，子序列是可以**不连续**的！

接着考虑解题思路，考试时我第一眼觉得是贪心，但是仔细想一想明显不行，所以解题思路考虑**动态规划**。

首先我们定义 $dp_{maxn,3}$ ，其中 $dp_{i,j}$ 表示前 $i$ 位有多少个 $\verb!a!$ 或 $\verb!ab!$ 或 $\verb!abc!$。

再定义一个 $tot$ ，用于存到第 $i$ 位为止**问号的个数**。

## 状态转移方程

**当 $s_i$ 不为 $?$ 时，有：**

$$dp_{i,0} = dp_{i-1,0} + 3^{tot-1}$$

$$dp_{i,1} = dp_{i-1,1} + dp_{i-1,1}$$

$$dp_{i,2} = dp_{i-1,2} + dp_{i-1,1}$$

**当 $s_i$ 为 $?$ 时，有：**

$$dp_{i,0} = 3 \times dp_{i-1,0} + 3^{tot-1}$$

$$dp_{i,1} = 3 \times dp_{i-1,1} + dp_{i-1,1}$$

$$dp_{i,2} = 3 \times dp_{i-1,2} + dp_{i-1,1}$$

其实看到转移方程就很容易了，反正与本蒟蒻同机房的神犇知道思路就可以轻松推出方程。无论对于哪种情况，我们都先求出 $dp_{i,0}$ ，然后后面两种情况直接承接前一种即可。

**本题唯一难度在思维，代码就不放了。**

---

## 作者：QwQcOrZ (赞：6)

考虑没有问号的时候怎么做

显然可以从前往后扫，然后记当前的后缀中，子序列为 `c`，`bc`，`abc` 的个数

然后用 `c` 更新 `bc`，用 `bc` 更新 `abc`。最后答案即为 `abc` 的个数

考虑加入问号后怎么做

可以记当前的后缀中，子序列为 `c`，`bc`，`?`，`??`，`?c`，`b?` 的个数

这个可以简单的维护

那么在统计答案时，如果当前位置为 `a` 或 `?` 时，就意味着当前位置可以作为一个 `abc` 子序列的开头，此时就需要将当前的贡献记入答案了

显然当前的 `a` 或 `?` 可以和后缀中的 `bc`，`??`，`?c`，`b?` 配对，将他们记入答案即可

但显然对于除了作为 `abc` 子序列计入答案的串中的 `?`，在原串内其它的 `?`，无论如何替换，都不会对当前的统计的 `abc` 子序列产生影响

那么将每种配对方案乘上对应的方案数 $3^m$ 即可，其中 $m$ 为除了配对的字符中整个串里 `?` 的个数

$Code\ Below$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
const int p=1e9+7;

int read()
{
	int s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
void print(int x,char c='\n')
{
	write(x);
	putchar(c);
}
void add(int &x,int y)
{
	x+=y;
	if (x>=p) x-=p;
}
int power(int a,int b)
{
	int ret=1;
	while (b)
	{
		if (b&1) ret=ret*a%p;
		a=a*a%p;
		b/=2;
	}
	return ret;
}
char a[N];
int c=0,bc=0,x=0,bx=0,xc=0,xx=0;

signed main()
{
	int n=read(),ans=0,cnt=0;
	scanf("%s",a+1);
	for (int i=1;i<=n;i++) cnt+=a[i]=='?';
	for (int i=n;i>=1;i--)
	{
		if (a[i]=='a') add(ans,(bx*power(3,cnt-1)%p+xc*power(3,cnt-1)%p+xx*power(3,cnt-2)%p+bc*power(3,cnt)%p)%p);
		if (a[i]=='?') add(ans,(bx*power(3,cnt-2)%p+xc*power(3,cnt-2)%p+xx*power(3,cnt-3)%p+bc*power(3,cnt-1)%p)%p);
        //统计答案
		if (a[i]=='b')
		{
			add(bc,c);
			add(bx,x);
		}
		if (a[i]=='c') add(c,1);
		if (a[i]=='?')
		{
			add(xc,c);
			add(xx,x);
			add(x,1);
		}
        //统计每种子序列的个数，因为"?"不能作为标识符，所以变量名中的"x"代表"?"
	}
	print(ans);

	return 0;
}
```



---

## 作者：素质玩家孙1超 (赞：5)

内存最少解，只用了4kb （然而内存少并没有用

做法：

统计用了多少个?字符的abc子序列有多少个。


用 $s[i][j]$ 表示当前满足前 $i$ 个值匹配，用了 $j$ 个?的方案数。

(如 $s[2][1]$ 表示当前可以匹配 $ab$ 并且其中有1个?的方案数)

然后考虑转移

1.如果这一位是?，那么 $s[i][j]+=s[i-1][j-1]$ 。

2.如果这一位不是?而是 $X$ ，那么 $s[X-'a'+1][j]+=s[X-'a'][j]$

然后最后统计每一种完全匹配方案的和就好了。（其中用了多少个?，那么相应的乘数就除多少个3）

---

小蒟蒻不太会写题解，大佬轻喷

细节处可以见代码:


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int Maxn=2e5+5;
const int Mo=1e9+7;
int X,s[4][4],num;;
inline int R()
{
	char ch=getchar();int x=0;bool f=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline int ksm(int di,int zi)
{
	int res=1;
	while(zi)
	{
		if(zi&1) res=(res*di)%Mo;
		di=(di*di)%Mo;
		zi>>=1; 
	}
	return res;
}
signed main()
{
	int n=R();
	for(int i=1;i<=n;i++)
	{
		char c;X=0;
		while((c=getchar())!='a'&&c!='b'&&c!='c'&&c!='?');
		if(c=='a')X=1;
		if(c=='b')X=2;
		if(c=='c')X=3;//读入 
		num+=(X==0);//num纪录所有?个数 
		if(X==0)//转移 
		{
			s[3][3]=(s[3][3]+s[2][2])%Mo;
			s[3][2]=(s[3][2]+s[2][1])%Mo;
			s[3][1]=(s[3][1]+s[2][0])%Mo;
			s[2][2]=(s[2][2]+s[1][1])%Mo;
			s[2][1]=(s[2][1]+s[1][0])%Mo;
			s[1][1]++;
		}
		if(X==1)s[1][0]++;
		if(X==2)
		{
			s[2][1]=(s[2][1]+s[1][1])%Mo;
			s[2][0]=(s[2][0]+s[1][0])%Mo;
		}
		if(X==3)
		{
			s[3][2]=(s[3][2]+s[2][2])%Mo;
			s[3][1]=(s[3][1]+s[2][1])%Mo;
			s[3][0]=(s[3][0]+s[2][0])%Mo;
		}
	}
	int ans=0;
	ans+=s[3][0]*ksm(3,num);ans%=Mo;
	if(s[3][1])ans+=s[3][1]*ksm(3,num-1);ans%=Mo;
	if(s[3][2])ans+=s[3][2]*ksm(3,num-2);ans%=Mo;
	if(s[3][3])ans+=s[3][3]*ksm(3,num-3);ans%=Mo;//统计 
	printf("%lld\n",ans);
}


```



---

## 作者：一只书虫仔 (赞：2)

#### Description

> 给定一个字符串 $S$，求将 `?` 替换后的所有字符串中有多少个长度为三的子序列为 `abc`，其中 $S$ 中的 `?` 可以换成 `a` / `b` / `c`。

#### Solution

考虑 dp，设 $f_{i,1/2/3}$ 为截止到第 $i$ 个字符有多少个子序列为 `a` / `ab` / `abc`。

设 $g$ 为 $S$ 有多少个 `?`，则有转移：

- 当 $S_i=$ `a`，`a` 的情况可以进行更新：
	- $f_{i,1}=f_{i-1,1}+3^{g}$；
    - $f_{i,2}=f_{i-1,2}$；
    - $f_{i,3}=f_{i-1,3}$；
- 当 $S_i=$ `b`，`ab` 的情况可以进行更新：
	- $f_{i,1}=f_{i-1,1}$；
    - $f_{i,2}=f_{i-1,2}+f_{i-1,1}$；
    - $f_{i,3}=f_{i-1,3}$；
- 当 $S_i=$ `c`，`abc` 的情况可以进行更新：
	- $f_{i,1}=f_{i-1,1}$；
    - $f_{i,2}=f_{i-1,2}$；
    - $f_{i,3}=f_{i-1,3}+f_{i-1,2}$；
- 当 $S_i=$ `?`，则一共 $3^{g}$ 种情况就划分为了三种，加 `a` 加 `b` 加 `c`，则 `a` `ab` `abc` 三种子序列的转移量也从上一种情况除以 $3$ 得到（可以感性理解为有 $1/3$ 的概率得到这个子序列想要的字符），那剩下的 $2/3$ 就是不符合要求的，直接从第 $i-1$ 项转移过来即可，即为：
	- $f_{i,1}=\frac{f_{i-1,1}+3^{g}} 3+\frac{2f_{i-1,1}} 3=f_{i-1,1}+3^{g-1}$；
    - $f_{i,2}=\frac{f_{i-1,2}+f_{i-1,1}} 3+\frac{2f_{i-1,2}} 3=f_{i-1,2}+\frac{f_{i-1,1}}3$；
    - $f_{i,3}=\frac{f_{i-1,3}+f_{i-1,2}} 3+\frac{2f_{i-1,3}} 3=f_{i-1,3}+\frac{f_{i-1,2}}3$。
    
最后输出 $f_{n,3}$ 即可。

---

## 作者：vеctorwyx (赞：2)

### 模拟就好了，~~能不dp就不dp~~

记录2个前缀和，2个后缀和：$a$个数前缀和$prea$，$?$个数前缀和$pre$，$c$个数后缀和$lasc$，$?$个数后缀和$las$（~~好像不能叫前后缀和~~）


然后扫一遍记录一下就好了：

如果$s_i$(字符串)为$b$或$?$就有一下操作

$ans+=pre_{i-1}*lasc_{i+1}*3^{l-1+r}$

$ans+=prea_{i-1}*lasc_{i+1}*3^{l+r}$

$ans+=prea_{i-1}*las_{i+1}*3^{l-1+r}$

$ans+=pre_{i-1}*las_{i+1}*3^{l-2+r}$

其中3的$x$次幂是指该情况会出现在多少个子序列中；

(别忘了$%100000007$)

时间复杂度$O(nlogn)$（建议使用快速幂）；

code

```
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
#define main signed main
#define vectorwyx 1000000007
using namespace std;
int n,cnt,pl[200010],pra[200010],prc[200010],prf[200010],laf[200010],ans;
char a[200010];
int ksm(int x,int y)
{
	if(y<0)
	return 1;
	int ans=1;
	while(y)
	{
		if(y&1)
		(ans*=x)%=vectorwyx;
		(x*=x)%=vectorwyx;
		y>>=1;
	}
	return ans;
}
main()
{
	cin>>n;
	cin>>a+1;
	for(int i=1;i<=n;i++)//处理前缀和
	{
		prf[i]=prf[i-1];
		if(a[i]=='?')
		pl[++cnt]=i,prf[i]++;
		pra[i]=pra[i-1]+(a[i]=='a'?1:0);
	}
	for(int i=n;i>=1;i--)//处理后缀和
	{
		laf[i]=laf[i+1];
		if(a[i]=='?')
		laf[i]++;
		prc[i]=prc[i+1]+(a[i]=='c'?1:0);
	}
	for(int i=2;i<n;i++)//扫一遍记录答案
	{
		int l=prf[i-1],r=laf[i+1];
		if(a[i]=='b')
		{
			(ans+=prf[i-1]*prc[i+1]*(ksm(3,l-1+r)))%=vectorwyx;
			(ans+=pra[i-1]*prc[i+1]*(ksm(3,l+r)))%=vectorwyx;
			(ans+=pra[i-1]*laf[i+1]*(ksm(3,l+r-1)))%=vectorwyx;
			(ans+=prf[i-1]*laf[i+1]*(ksm(3,l+r-2)))%=vectorwyx;
		}
		if(a[i]=='?')
		{
			(ans+=prf[i-1]*prc[i+1]*(ksm(3,l-1+r)))%=vectorwyx;
			(ans+=pra[i-1]*prc[i+1]*(ksm(3,l+r)))%=vectorwyx;
			(ans+=pra[i-1]*laf[i+1]*(ksm(3,l-1+r)))%=vectorwyx;
			(ans+=prf[i-1]*laf[i+1]*(ksm(3,l-2+r)))%=vectorwyx;
		}
	}
	cout<<ans;
	return 0;
   	//Orz vectorwyx！
}
```
//这真是codeforcesF题难度吗？

---

## 作者：ZigZagKmp (赞：2)

本文同步于我的[cnblog](https://www.cnblogs.com/ZigZagKmp/p/13758252.html)

本场所有题解可见[此](https://www.luogu.com.cn/blog/ZigZagKmp/codeforces-1426-solution)
## CF1426F
### 题意简述
给定一个含有 `abc?` 的字符串，`?` 可能是 `abc` 中的任意一个，求所有可能的无 `?` 字符串中子序列 `abc` 出现的次数。

$3\le |s|\le 2\cdot10^5$。
### 算法标签
组合计数
### 算法分析
因为是 `abc` 的子序列，所以我们考虑在所有可能的 `b` 处统计答案，对于当前的 $b$， 答案为其左侧所有可能的 `a` 的个数和其左侧所有可能的 `c` 的个数。

下面只讨论左边的 `a` 的可能个数，右边的 `c` 同理。

假设左边有 $x$ 个 `a` 和 $y$ 个 `?`。

考虑有 $i$ 个 `?` 变成了 `a` ，则剩余的 $y-i$ 个 `?` 都可以是 `b/c` 共 $2^{y-i}$ 种可能，则所有可能的 `a` 的个数为：

$$\sum_{i=0}^{y}\binom{y}{i}2^{y-i}\cdot\left(x+i\right)$$

拆开括号中两项分别求和：

$$\sum_{i=0}^{y}\binom{y}{i}2^{y-i}x+\sum_{i=0}^{y}\binom{y}{i}2^{y-i}i$$

左式使用二项式定理，右式显然 $i=0$ 时为 $0$ ：

$$x\cdot3^y+\sum_{i=1}^{y}\binom{y}{i}2^{y-i}i$$

拆组合数，约掉 $i!$ 中的一个 $i$：

$$x\cdot3^y+\sum_{i=1}^{y}\frac{y!}{(i-1)!(y-i)!}{i}2^{y-i}$$

提出一个 $y$，再凑组合数：

$$x\cdot3^y+y\sum_{i=1}^{y}\binom{y-1}{y-i}2^{y-i}$$

变成一般的二项式定理形式：

$$x\cdot3^y+y\sum_{i=0}^{y-1}\binom{y-1}{i}2^{i}$$

最终答案为：

$$x\cdot3^y+y\cdot3^{y-1}$$

预处理出 $3^x$ 即可 $O(n)$ 求解。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define int long long
#define mod 1000000007
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int n,m;
int p3[maxn];
char st[maxn];
int sa,sc,bw,sw;
int ans;
signed main(){
	read(n);
	p3[0]=1;
	for(int i=1;i<=n;++i)p3[i]=1ll*p3[i-1]*3%mod;
	scanf("%s",st+1);
	for(int i=1;i<=n;++i){
		if(st[i]=='c')sc++;
		if(st[i]=='?')bw++;
	}
	for(int i=1;i<=n;++i){
		if(st[i]=='c')sc--;
		if(st[i]=='?')bw--;
		if(st[i]=='?'||st[i]=='b'){
			int sum1=0,sum2=0;
			sum1=(sum1+1ll*sa*p3[sw]%mod)%mod;
			if(sw)sum1=(sum1+1ll*sw*p3[sw-1]%mod)%mod;
			sum2=(sum2+1ll*sc*p3[bw]%mod)%mod;
			if(bw)sum2=(sum2+1ll*bw*p3[bw-1]%mod)%mod;
			ans=(ans+1ll*sum1*sum2%mod)%mod;
		}
		if(st[i]=='a')sa++;
		if(st[i]=='?')sw++;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：11D_Beyonder (赞：1)

### Idea  
&emsp;&emsp;用 $a_i,b_i,c_i,x_i$ 分别表示 $s_1\sim s_i$ 中 $a,b,c,?$ 的个数。每次以 $b$ 为中心统计两边 $a,c$ 可取的个数。  
&emsp;&emsp;枚举 $s$ 的第 $i$ 个字符 $s_i$。若 $s_i$ 为 $b$，分四种情况讨论：组成的 $abc$ 无 $?$ 参与，在 $s_1\sim s_{i-1}$ 中取一个 $a$，在 $s_{i+1}\sim s_n$ 中取一个 $c$，此时每个 $?$ 有三种可能，共有 $3^{x_n}$ 个串对此类情况产生贡献，总数为 $a_{i-1}(c_{n}-c_i)\cdot3^{x_n}$；用 $ab?$ 组成 $abc$，在 $s_1\sim s_{i-1}$ 中取一个 $a$，在 $s_{i+1}\sim s_n$ 中取一个 $?$，共有 $3^{x_n-1}$ 个串对此类情况产生贡献，总数为 $a_{i-1}(x_n-x_i)\cdot3^{x_n-1}$；用 $?bc$ 代替 $abc$，在 $s_1\sim s_{i-1}$ 中取一个 $?$，在 $s_{i+1}\sim s_n$ 中取一个 $c$，共有 $3^{x_n-1}$ 个串对此类情况产生贡献，总数为 $x_{i-1}(c_{n}-c_i)\cdot3^{x_n-1}$；用 $?b?$ 代替 $abc$，在 $s_1\sim s_{i-1}$ 中取一个 $?$，在 $s_{i+1}\sim s_n$ 中取一个 $?$，共有 $3^{x_n-2}$ 个串对此类情况产生贡献，总数为 $x_{i-1}(x_{n}-x_i)\cdot3^{x_n-2}$。若 $s_i$ 为 $?$，那么就令 $?$ 为 $b$，此处仍然分四种情况讨论：用 $a?c$ 代替 $abc$，在 $s_1\sim s_{i-1}$ 中取一个 $a$，在 $s_{i+1}\sim s_n$ 中取一个 $c$，共有 $3^{x_n-1}$ 个串对此类情况产生贡献，总数为 $a_{i-1}(c_{n}-c_i)\cdot3^{x_n-1}$；用 $??c$ 代替 $abc$，在 $s_1\sim s_{i-1}$ 中取一个 $?$，在 $s_{i+1}\sim s_n$ 中取一个 $c$，共有 $3^{x_n-2}$ 个串对此类情况产生贡献，总数为 $x_{i-1}(c_{n}-c_i)\cdot3^{x_n-2}$；用 $a??$ 代替 $abc$，在 $s_1\sim s_{i-1}$ 中取一个 $a$，在 $s_{i+1}\sim s_n$ 中取一个 $?$，共有 $3^{x_n-2}$ 个串对此类情况产生贡献，总数为 $a_{i-1}(x_{n}-x_i)\cdot3^{x_n-2}$；用 $???$ 代替 $abc$，在 $s_1\sim s_{i-1}$ 中取一个 $?$，在 $s_{i+1}\sim s_n$ 中取一个 $?$，共有 $3^{x_n-3}$ 个串对此类情况产生贡献，总数为 $x_{i-1}(x_{n}-x_i)\cdot3^{x_n-3}$。
###  Code  
```cpp
/******************************************************************
Copyright: 11D_Beyonder All Rights Reserved
Author: 11D_Beyonder
Problem ID: CF1426F
Date: 10/9/2020
Description: Count
*******************************************************************/
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const int N=200004;
const int mod=1000000007;
ll power[N];
int n;
char s[N];
ll a[N],b[N],c[N],x[N];
int main(){
	cin>>n>>(s+1);
	int i;
	power[0]=1;
	for(i=1;i<N;i++){
		power[i]=power[i-1]*3%mod;
	}
	for(i=1;i<=n;i++){
		a[i]=a[i-1]+(s[i]=='a');
		b[i]=b[i-1]+(s[i]=='b');
		c[i]=c[i-1]+(s[i]=='c');
		x[i]=x[i-1]+(s[i]=='?');
	}
	ll ans=0;
	for(i=1;i<=n;i++){
		if(s[i]=='b'){
			if(x[n]>=0){
				//abc
				ans=(ans+a[i-1]*(c[n]-c[i])%mod*power[x[n]]%mod)%mod;
			}
			if(x[n]>=1){
				//ab? ?bc
				ans=(ans+a[i-1]*(x[n]-x[i])%mod*power[x[n]-1]%mod)%mod;
				ans=(ans+x[i-1]*(c[n]-c[i])%mod*power[x[n]-1]%mod)%mod;
			}
			if(x[n]>=2){
				//?b?
				ans=(ans+x[i-1]*(x[n]-x[i])%mod*power[x[n]-2]%mod)%mod;
			}

		}else if(s[i]=='?'){
			if(x[n]>=1){
				//a?c->abc
				ans=(ans+a[i-1]*(c[n]-c[i])%mod*power[x[n]-1]%mod)%mod;
			}
			if(x[n]>=2){
				//??c->abc
				ans=(ans+x[i-1]*(c[n]-c[i])%mod*power[x[n]-2]%mod)%mod;
				//a??->abc
				ans=(ans+a[i-1]*(x[n]-x[i])%mod*power[x[n]-2]%mod)%mod;
			}
			if(x[n]>=3){
				ans=(ans+x[i-1]*(x[n]-x[i])%mod*power[x[n]-3]%mod)%mod;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：KSToki (赞：1)

dp。

考虑没有问号的情况。这里我们记录前缀和 $a$ 表示 $1$~$i$ 中 $a$ 的个数、前缀和 $ab$ 表示 $1$~$i$ 中 $ab$ 的个数，显然有：
```cpp
a[i]=(a[i-1]+(s[i]=='a')%Mod)%Mod;
ab[i]=(ab[i-1]+(s[i]=='b')*a[i-1]%Mod)%Mod;
```
当我们搜到一个 c 时，统计答案，加 $ab[i]$ 即可。

加上问号，有两种处理方法。一是开一个二维数组 $f[3][200001]$，$f[0/1/2][i]$ 表示在第 $i$ 位以 a/b/c 结尾的答案的数量，如果不是问号的话直接对应加即可，是问号则更新三个位置。二是考虑问号的实质，它实际上是相较于前一个位置的三倍的情况，记录下当前问号**情况数**为 $cnt$，注意不是个数，乘 $3$ 转移即可。

题解采用第二种写法，记得开 `long long`，代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int Mod=1e9+7;
int n,a[200001],ab[200001],cnt=1,ans;
char s[200001];
int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	for(register int i=1;i<=n;++i)
	{
		a[i]=(a[i-1]+(ll)(s[i]=='a')*cnt%Mod)%Mod;
		ab[i]=(ab[i-1]+(ll)(s[i]=='b')*a[i-1]%Mod)%Mod;
		ans=(ans+(ll)(s[i]=='c')*ab[i-1]%Mod)%Mod;
		if(s[i]=='?')
		{
			a[i]=((ll)a[i-1]*3%Mod+cnt)%Mod;
			ab[i]=((ll)ab[i-1]*3%Mod+a[i-1])%Mod;
			ans=((ll)ans*3+ab[i-1])%Mod;
			cnt=(ll)cnt*3%Mod;
		}
	}
	printf("%d\n",ans);
	return 0;
}

```


---

## 作者：ncwzdlsd (赞：0)

### 题干：
给定一个含有 $\texttt{abc?}$ 的字符串,$\texttt{?}$ 可能是 $\texttt{abc}$ 中的任意一个,求所有可能的无 $\texttt{?}$ 字符串中,子序列 $\texttt{abc}$ 出现的次数。

------------

一眼DP。

设 $f(i,0)$ 代表当前序列有多少个“$\texttt{?}$”，$f(i,1)$ 代表当前序列有多少个“$\texttt{a}$”，$f(i,2)$ 代表当前序列有多少个“$\texttt{ab}$”，$f(i,3)$ 代表当前序列有多少个“$\texttt{abc}$”。

“$\texttt{?}$”对“$\texttt{a}$”有贡献，“$\texttt{a}$”对“$\texttt{ab}$”有贡献，“$\texttt{ab}$”对“$\texttt{abc}$”有贡献。

然后就可以快乐地列状态转移方程DP了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 200000 + 5;
const int mod = 1e9 + 7;
char s[maxn];
ll f[maxn][5];

int main() 
{
    int n;
    cin>>n;
    scanf("%s", &s);
    f[0][0] = 1;
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j <= 3; ++j) 
        {
            f[i + 1][j] = f[i][j];
        }
        if (s[i] == 'a') 
        {
            f[i + 1][1] = f[i + 1][1] + f[i][0] % mod;
        } 
        else if (s[i] == 'b') 
        {
            f[i + 1][2] = f[i + 1][2] + f[i][1] % mod;
        } 
        else if (s[i] == 'c') 
        {
            f[i + 1][3] = f[i + 1][3] + f[i][2] % mod;
        } 
        else 
        {
            f[i + 1][0] = f[i][0] * 3 % mod;
            for (int j = 1; j <= 3; ++j) 
            {
                f[i + 1][j] = (f[i][j] * 3 % mod + f[i][j - 1] % mod) % mod;
            }
        }
    }
    printf("%lld\n", f[n][3] % mod);
    return 0;
}
```

---

## 作者：白鲟 (赞：0)

## 前言
被同机房人员骗来打 Div.3，然而写完一道才发现上不了分……

## 题目描述
给出一个仅由 $\texttt{a},\texttt{b},\texttt{c},\texttt{?}$ 组成的字符串，$\texttt{?}$ 可能是 $\texttt{a},\texttt{b},\texttt{c}$ 中的任意一种。求出该字符串所有可能成为的字符串中子序列 $\texttt{abc}$ 出现的次数和。  

## 题目分析
看上去是一道比较简单的计数 DP。做法是遍历字符串时并行累加所有可能情况的贡献。当前字符若不为 $\texttt{?}$，则考虑这个字符与之前的所有情况合起来可构成的子序列 $\texttt{a},\texttt{ab},\texttt{abc}$ 的分别个数；否则，分别考虑当前字符是 $\texttt{a},\texttt{b},\texttt{c}$ 的情况下子序列 $\texttt{a},\texttt{ab},\texttt{abc}$ 的分别个数，并将总情况数扩大至 $3$ 倍。  

具体转移方程见代码。

## 代码
应该是目前题解中比较简洁的代码。

```cpp
#include<cstdio>
using namespace std;
const int maxn=2e5,mod=1e9+7;
long long n,ans,cases=1,a[maxn+1],ab[maxn+1];
char s[maxn+1];
int main()
{
	scanf("%lld%s",&n,s+1);
	for(int i=1;i<=n;++i)
	{
		a[i]=(a[i-1]+(s[i]=='a')*cases)%mod;
		ab[i]=(ab[i-1]+a[i-1]*(s[i]=='b'))%mod;
		ans=(ans+ab[i-1]*(s[i]=='c'))%mod;
		if(s[i]=='?')
		{
			a[i]=(a[i-1]*3+cases)%mod;
			ab[i]=(ab[i-1]*3+a[i-1])%mod;
			ans=(ans*3+ab[i-1])%mod;
			cases=cases*3%mod;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Chinese_zjc_ (赞：0)

$DP$ 水题.

我们进行 $ 3 $ 次 $ DP $ ,每次 $ DP $ 算出 $ dp_{l,i} $ ,其中 $ dp_{l,i} $ 表示原串 $s_1$ 到 $ s_i $ 的子串中,长度为 $ l $ 的前缀答案串总数量.

比如说, $ dp_{2,5} $ 表示 $S$ 串的前五个字符中, `ab` 串的总数量.

看样例#1:

```plain
6
ac?b?c
```

一共 $sum=3^{\text ?个数}=3^2=9$ 种可能的 $ S $ 串.

$ DP $ 数组如下:

| $dp[k][i]$ | 1    | 2    | 3    | 4    | 5    | 6    |
| ---------- | ---- | ---- | ---- | ---- | ---- | ---- |
| **1**      | 9    | 9    | 12   | 12   | 15   | 15   |
| **2**      | 0    | 0    | 3    | 15   | 19   | 19   |
| **3**      | 0    | 0    | 0    | 0    | 5    | 24   |

接下来我们分类讨论 $ 3 $ 种 $ i $ 的情况.

$ k=1 $ 时,考虑`a`和`?`,得到下面三种转移:
$$
dp[1][i]=
\begin{cases}
dp[1][i-1]+sum & s[i]=\text a\\
dp[1][i-1]+\frac{sum}{3} & s[i]=\text ?\\
dp[1][i-1] & otherwise
\end{cases}
$$
得出它们的方法不难,考虑如果本来就是`a`的位置,必定所有串都有这个`a`,因此贡献为 $sum$ ,而`?`则只有 $\frac{sum}3$ 的串有其为`a`的情况,其它情况则没有任何贡献.

$k=2$ 时,考虑`b`和`?`,得到下面三种转移:
$$
dp[2][i]=
\begin{cases}
dp[2][i-1]+dp[1][i-1] & s[i]=\text b\\
dp[2][i-1]+\frac{dp[1][i-1]}{3} & s[i]=\text ?\\
dp[2][i-1] & otherwise
\end{cases}
$$
也不难,考虑如果本来就是`b`的位置,必定所有其之前的`a`都能和其组成`ab`,因此贡献为 $dp[1][i-1]$ ,而`?`同样只有 $\frac13$ 的情况数会是`b`,因而贡献为 $\frac{dp[1][i-1]}3$,其它情况则没有任何贡献.

$k=3$ 时,如同 $k=2$ 一样,考虑`c`和`?`,得到下面三种转移:
$$
dp[3][i]=
\begin{cases}
dp[3][i-1]+dp[2][i-1] & s[i]=\text b\\
dp[3][i-1]+\frac{dp[2][i-1]}{3} & s[i]=\text ?\\
dp[3][i-1] & otherwise
\end{cases}
$$
因此就可以把它们转化成代码实现.

$Code$:

```cpp
//This Code was made by Chinese_zjc_.
//头文件已省略
#define int long long
#define double long double
using namespace std;
const double PI = acos(-1);
const double eps = 0.0000000001;
const int INF = 0x3fffffffffffffff;
const int MOD = 1000000007;
string s;
int dp[4][200005], n, sum;
int power(int A, int B)
{
    int res = 1;
    while (B)
    {
        if (B & 1)
        {
            res = res * A % MOD;
        }
        A = A * A % MOD;
        B >>= 1;
    }
    return res;
}
const int _3 = power(3, MOD - 2);
signed main()
{
    ios::sync_with_stdio(false);
    cin >> n >> s;
    s = ' ' + s;
    sum = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (s[i] == '?')
        {
            sum = sum * 3 % MOD;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (s[i] == 'a')
        {
            dp[1][i] = (dp[1][i - 1] + sum) % MOD;
        }
        else if (s[i] == '?')
        {
            dp[1][i] = (dp[1][i - 1] + sum * _3) % MOD;
        }
        else
        {
            dp[1][i] = dp[1][i - 1];
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (s[i] == 'b')
        {
            dp[2][i] = (dp[2][i - 1] + dp[1][i - 1]) % MOD;
        }
        else if (s[i] == '?')
        {
            dp[2][i] = (dp[2][i - 1] + dp[1][i - 1] * _3) % MOD;
        }
        else
        {
            dp[2][i] = dp[2][i - 1];
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (s[i] == 'c')
        {
            dp[3][i] = (dp[3][i - 1] + dp[2][i - 1]) % MOD;
        }
        else if (s[i] == '?')
        {
            dp[3][i] = (dp[3][i - 1] + dp[2][i - 1] * _3) % MOD;
        }
        else
        {
            dp[3][i] = dp[3][i - 1];
        }
    }
    for (int i = 1; i <= 3; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cout << dp[i][j] << ' ';
        }
        cout << endl;
    }
    cout << dp[3][n] << endl;
    return 0;
}
```



---

