# Dreamoon Likes Sequences

## 题目描述

Dreamoon 非常喜欢数列。因此他出了一道数列问题，保证你在 OEIS 上找不到它。

有两个整数 $d, m$，找到这样的数列 $a$ 的数列，满足以下限制条件：

- 数列 $a$ 的长度为 $n$，$n \ge 1$；
- $1 \le a_i \lt a_2 \lt \cdots \lt a_n \le d$；
- 定义一个长度为 $n$ 的数组 $b$：$b_1 = a_1$，$\forall i \ge 1, b_i  = b_{i - 1} \oplus a_i$，其中 $\oplus$ 表示二进制异或 (xor)。在构建出 $b$ 后，应当满足 $b_1 \lt b_2 \lt \cdots \lt b_{n - 1} \lt b_n$ 的限制条件。

由于满足条件的数列数量可能很多，请输出答案模 $m$ 的结果。

## 样例 #1

### 输入

```
10
1 1000000000
2 999999999
3 99999998
4 9999997
5 999996
6 99995
7 9994
8 993
9 92
10 1```

### 输出

```
1
3
5
11
17
23
29
59
89
0```

# 题解

## 作者：Alex_Wei (赞：9)

> [LG 题面传送门](https://www.luogu.com.cn/problem/CF1329B) & [CF 题面传送门](https://codeforces.ml/problemset/problem/1329/B)

> 题意简述：给定 $d,m$，求满足以下条件的序列 $a$ 存在多少个，对 $m$ 取模：

> - 长度 $n\geq1$。
> - $1\leq a_1< a_2< \cdots<a_n\leq d$。
> - 设 $b$ 为 $a$ 的前缀异或和，则 $b_1< b_2< \cdots<b_n$。

---

引理：设 $c_i$ 为 $a_i$ 在二进制下的位数，则 $c_1<c_2<\cdots<c_n$。

感性证明（并不严谨）：因为 $a_i<a_{i+1}$，所以 $c_i\leq c_{i+1}$。如果 $c_i=c_{i+1}$，那么 $b_i$ 的位数为 $c_i$，$b_{i+1}$ 的位数为 $c_i-1$，不满足 $b_i<b_{i+1}$。所以 $c_i<c_{i+1}$。

因此，枚举位数为 $i$ 的数是否在序列中出现并计算对答案的贡献，根据乘法原理相乘即答案。

- 位数小于 $d$ 的位数，贡献为 $2^i+1$（位数为 $i$ 的数的个数或不出现）。
- 别忘了 $n=0$ 的情况，要减去 $1$。

时间复杂度 $O(\log d)$。

```cpp
void solve(){
    cin>>d>>m; ll ans=1,c=log2(d);
    for(int i=0;i<=c;i++)ans=ans*(i<c?(1<<i)+1:d-(1<<i)+2)%m;
    cout<<(ans-1+m)%m<<endl;
}
```

---

Upd on 2020.4.15：将代码改整洁。

---

## 作者：WYXkk (赞：4)

upd：修改了一处笔误，请管理重新审核。

众所周知，看到数列题，我们应该 **找 规 律**。

虽然题目里面有这么一句：

> that you can't find in OEIS
>
> 翻译：你在 OEIS 上找不到

但万一能呢，所以我们还是去搜一下。

于是我们找到了 [A293711](http://oeis.org/A293711)，但是事实上并没有什么用，因为后一项就错了。

所以我们只能自己找规律了。

暴力应该是非常好写的：

```cpp
void dfs(int a,int b)//now ai and bi
{
	++ans;
	F(i,a+1,d) if((b^i)>b) dfs(i,b^i);
}
ans=-1;//(0,0) not included
dfs(0,0);
```

然后我们把数列的前 $70$ 项跑出来：（为美观，每 $10$ 个换行一次）

```plain
1 3 5 11 17 23 29 59 89 119
149 179 209 239 269 539 809 1079 1349 1619
1889 2159 2429 2699 2969 3239 3509 3779 4049 4319
4589 9179 13769 18359 22949 27539 32129 36719 41309 45899
50489 55079 59669 64259 68849 73439 78029 82619 87209 91799
96389 100979 105569 110159 114749 119339 123929 128519 133109 137699
142289 146879 151469 302939 454409 605879 757349 908819 1060289 1211759
```

啥玩意？

此时我们应该使用 **差 分 大 法**：

```plain
1 2 2 6 6 6 6 30 30 30
30 30 30 30 30 270 270 270 270 270
270 270 270 270 270 270 270 270 270 270
270 4590 4590 4590 4590 4590 4590 4590 4590 4590
4590 4590 4590 4590 4590 4590 4590 4590 4590 4590
4590 4590 4590 4590 4590 4590 4590 4590 4590 4590
4590 4590 4590 151470 151470 151470 151470 151470 151470 151470
```

于是我们发现如下规律：

- $d_{2^i}=d_{2^i+1}=\cdots=d_{2^{i+1}-1}$
- $d_{2^{i+1}}=d_{2^i}\times(2^i+1)$

按照这个规律每段（$2^i,\cdots,2^{i+1}-1$）都是等差数列，所以分别处理即可。

复杂度 $O(t\log d)$。

$\texttt{code:}$

```cpp
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define Set(a) memset(a,0,sizeof(a))
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define openf(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define re register
#define ri re int
#define il inline
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x)
{
	T f=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
	x*=f;
	return x;
}
ll rd(){ll x;rd(x);return x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int inf=1<<30;

ll d,m;
int main()
{
	int t=rd();while(t--)
	{
		rd(d);rd(m);
		ll ans=0,tmp=1;
		F(i,1,32)
		{
			if(d<(1ll<<i))
			{
				ans+=(d-(1ll<<(i-1))+1)*tmp;
				ans%=m;
				break;
			}
			else
			{
				ans+=(1ll<<(i-1))*tmp;
				ans%=m;
				tmp*=((1ll<<(i-1))+1);
				tmp%=m;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

按照惯例，说句闲话：

**找 规 律 t x d y！**

---

## 作者：一扶苏一 (赞：3)

## 【计数 DP】【CF1329B】Dreamoon Likes Sequences

### Analysis

首先一个显然的结论是：合法的数列长度不会超过 $\lfloor\log_2d\rfloor + 1$ 。

证明：数列的最高非零位一定是单调递增的。否则对于一个位置 $i$，设 $a_i$ 的最高非零位是 $p$，且 $a_{i + 1}$ 的最高非零位也是 $p$，而 $a_{i - 1}$ 的最高非零位小于 $p$，则 $b_i$ 的最高非零位一定是 $p$，而 $b_{i + 1}$ 的第 $p$ 位由于是 $b_i$ 的第 $p$ 位异或 $1$，所以为 $0$，且更高位都是 $0$，所以 $b_{i + 1} < b_i$，矛盾。而最大的非零最高位是 $\lfloor\log_2d\rfloor$，加上第 $0$ 位共有 $\lfloor\log_2 d\rfloor + 1$ 位。

考虑枚举序列的长度 $\operatorname{len}$，问题变成求有多少个长度为 $\operatorname{len}$ 的最高位单调递增的序列，dp 即可：设 $f_{i, j}$ 是考虑前 $i$ 个数字，第 $i$ 个数字的最高位是 $j$ 的方案数。转移显然：

$$f_{i, j} = \sum_{k = 0}^{j - 1} f_{i - 1, k}$$

朴素转移的复杂度是 $O(\log d)$，共有 $O(\log ^2 d)$ 的状态，还有 $O(\log d)$ 的枚举，因此总复杂度 $O(\log^4 d)$。

而注意到上式是转移了 $f_{i - 1}$ 的一个前缀，因此维护前缀和可以将转移降至 $O(1)$，时间复杂度 $O(\log^3 d)$。

最后一点细节是，当考虑到第 $\operatorname{len}$ 位时，第 $\operatorname{len}$ 为上的数大于 $d$ 时不能计数，因此对于每个 $\operatorname{len}$，方案数要减去 $\sum_{i = 1}^{\lfloor \log_2 d\rfloor - 1}f_{\operatorname{len} - 1,k} \times (2^{\lfloor\log_2 d\rfloor + 1} -d - 1)$。



### Code

```cpp
const int maxn = 35;

ll d, m;
ll f[maxn][maxn], sum[maxn][maxn];

int lg2(int x) {
  int ret = 1;
  while ((1 << ret) <= x) ++ret;
  return ret - 1;
}

int main() {
  freopen("1.in", "r", stdin);
  int t;
  for (qr(t); t; --t) {
    qr(d); qr(m);
    int n = lg2(d) + 1;
    ll ans = 0;
    for (int len = 1; len <= n; ++len) {
      memset(f, 0, sizeof f);
      memset(sum, 0, sizeof sum);
      f[1][0] = 1;
      sum[1][0] = 1;
      for (int i = 1; i < n; ++i) {
        f[1][i] = (1 << i) % m;
        sum[1][i] = (sum[1][i - 1] + f[1][i]) % m;
      }
      for (int i = 2, di = i - 1; i <= len; di = i++) {
        for (int j = i - 1, dj = j - 1; j < n; dj = j++) {
          f[i][j] = sum[di][dj] * (1 << j) % m;
          sum[i][j] = (sum[i][dj] + f[i][j]) % m;
        }
      }
      for (int i = 0; i <= n; ++i) (ans += f[len][i]) %= m;
      ans -= sum[len - 1][n - 2] * ((1 << n) - d - 1) % m;
      if (ans < 0) ans += m;
    }
    ans -= ((1 << n) - d - 1) % m;
    if (ans < 0) ans += m;
    qw(ans, '\n');
  }
  return 0;
}
```



---

## 作者：BFqwq (赞：3)

同样是打表选手，跟 WYXkk 的做法相似。

但是，我的表似乎更直观。

同样，我们先打出两项差

```
2 2
6 6 6 6
30 30 30 30 30 30 30 30
270 270 270 270 270 270 270 270 270 270 270 270 270 270 270 270
4590……
```

然后，WYXkk 大佬就看出了规律，而我没看出~~这充分说明了我的菜~~。

然后我们似乎啥都得不出来。

那么这条路就行不通了？

答案是：不可能的。

我们再做一次商。

```
6/2=3
30/6=5
270/30=9
4590/270=17
……
```

其实这时候已经比较好发现了。

我们再做一层差。
```
5-3=2
9-5=4
17-9=8
……
```
终于，我们看到了我们想要的东西。

那要是有人说，第二步做商真的想不到怎么办？

没事，我们改成做差。

```
6-2=4
30-6=24
270-30=240
4590-270=4320
……
```
然后，答案又呼之欲出了。
```
24/6=4
240/30=8
4320/270=16
……
```
~~（真是神奇呢）~~


---

## 作者：asdfo123 (赞：1)

# CF1329B题解：异或性质

考虑a序列每个数**二进制下**的最高位。

可以发现每个数的最高位一定严格大于上一个数的最高位：


即大概下面这种

$d=5=(101)_2$

那么所有数可以是(下面列举了一种情况）

$$(001)_2$$
$$(010)_2$$
$$(100)_2$$


如果小于，则 $a$ 序列不递增；如果等于，则 $b$ 序列不递增。

因此可以得出，序列长度 $n$ 最多不超过 $log_2d$ ，最小为 $1$。


代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll ans;
int d,m;
int t; 
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		ans=1;
		scanf("%d%d",&d,&m);
		int c=log2(d);//d最高位 
		for(int i=0;i<=30;i++)
		{
			if(i<c)
			{
				ans=(ans*((1<<i)+1))%m;
			}
			else if(i==c)
			{
				ans=ans*(d-(1<<i)+1+1)%m;//这是为了保证当前数≤d 
			}
		}
		printf("%lld\n",(ans-1+m)%m);
	}
	return 0;
	
	
} 
```

对于转移时：

1.位数小于$c=log_2(d)$的位数，对答案贡献是$2^i+1$（选的该位所有数和不选该位） 

2.这里要注意：如果$i$是$d$的最高位，则转移式里的$2^i$应改为$d−2^i+1$。这是为了保证当前数$≤d$。

3.结尾要减去$1$，因为要排除 $n=0$ 情况

4.取模$(ans-1+m) \ mod\ m $


---

## 作者：tommymio (赞：1)

这题的性质是很好看出来的： $a_i$ 的最高位比 $a_{i-1}$ 的最高位至少大 $1$。（以下均称二进制意义下的最高位）

那么就可以DP求解了，这里给出一种与 @——扶苏—— 不同的计数DP，严格来说是一种不同的统计答案的方法。

DP的状态仍然相同，$f[i,j]$ 为序列第 $i$ 项最高位数为 $j$ 的方案数。

那么有以下状态转移：

$$
\\
f[1,j]=2^j
\\
f[i,j]=\sum_{i=0}^{j-1}f[i-1,k](i>1)
$$

然而上面求出的 $f[i,j]$ 是对于所有第 $i$ 项的值为 $2^j-(2^{j+1}-1)$ 的序列而言。

设 $pw=\lfloor\log_2 d\rfloor$，当我们取到第 $i$ 项，且第 $i$ 项的最高位数为 $pw$ 的时候，事实上第 $i$ 项取不到 $[d,2^{pw+1}-1]$，这样就会计数不存在的情况。

我们考虑不计算 $i\geq pw$ 的 $f[i,j]$，因为这些情况属于特殊情况，对这些情况进行分类讨论，并统计答案：

- 当序列长度为 $1$ 且第 $1$ 项（即唯一一项）最高位数为 $pw$，显然不会被统计到答案里去，因为我们规定不会计算 $i\geq pw$ 的 $f[i,j]$，所以对于这样的情况，我们把它累加到答案里面去，这样的序列一共有 $d-2^{pw}+1$个。
- 当序列长度 $len\in[1,pw]$  且序列最末项最高位不为 $pw$，那我们可以直接把 $f[i,j]$ 累加到答案中，并且这样一定不会重复计数。原因也非常简单，因为 $i,j$ 中任意一项不同，计数的一定是不同种类的序列。这样的序列一共有 $\sum_{i=1}^{pw}\sum_{j=i-1}^{pw-1}f[i,j]$ 个。
- 当序列长度 $len\in[2,pw+1]$，且序列最末项最高位为 $pw$，那自然是考虑在序列长度为 $len-1$ 的序列上加上一项最高位为 $pw$ 的数，发现同第二种情况，这样的序列共有 $\left(\sum_{i=1}^{pw}\sum_{j=i-1}^{pw-1}f[i,j]\right)\times(d-2^{pw}+1)$个。

记序列长度为 $len\in[1,pw]$ 且序列最末项最高位不为 $pw$ 的序列的方案数为 $sum$，则总方案数为 $ans=sum\times(d-2^{pw}+1)+(d-2^{pw}+1)+sum=sum\times(d-2^{pw}+2)+(d-2^{pw}+1)$。

其实计数的思想还是差不多的，不过我是考虑累加答案而@——扶苏——是从容斥去除不合法情况考虑。

**值得注意** 的是，当 $d=1$ 时，$pw=0$，按照上述计算 $sum$ 的方式会 **RE**。因此必须进行特判，当 $d=1$ 时直接输出 $1\bmod m$ 即可（别问窝为啥输出 $1 \bmod m$ ，因为 $\texttt{Codeforces}$ 会给出 $m=1$ 的数据） 

```cpp
#include<cstdio>
#include<cstring>
//最大不超过2^30
//f[i][j] 序列的第i项，最高次幂为 2^j
typedef long long ll;
ll f[35][35];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
int main() {
	int T=read();
	while(T--) {
		int d=read(),m=read();
		int x=1,pw=0;
		ll ans=0;
		memset(f,0,sizeof(f));
		while(x<=d) x<<=1,++pw; x>>=1,--pw; //2^pw=d<=x 
		for(register int i=0;i<=pw-1;++i) f[1][i]=(1<<i);//?
		for(register int i=2;i<=pw;++i) {
			for(register int j=i-1;j<=pw-1;++j) {
				for(register int k=0;k<j;++k) f[i][j]=(f[i][j]+f[i-1][k])%m;
				f[i][j]=f[i][j]*((1<<j)%m)%m;
			}
		}
		if(pw>0) {
			for(register int i=1;i<=pw;++i) for(register int j=i-1;j<=pw-1;++j) ans=(ans+f[i][j])%m;
			printf("%lld\n",(ans*(d-(1<<pw)+2)%m+(d-(1<<pw)+1)%m)%m);
		}
		else printf("%d\n",1%m);
	}
	return 0;
}
```

---

## 作者：nullqtr_pwp (赞：0)

# CF1329B Solution
这篇题解计算方法和别的题解有点不同。
### 题目描述
Dreamoon 非常喜欢数列。因此他出了一道数列问题，保证你在 OEIS 上找不到它。

有两个整数 $d, m$，找到这样的数列 $a$ 的数列，满足以下限制条件：

- 数列 $a$ 的长度为 $n$，$n \ge 1$；
- $1 \le a_i \lt a_2 \lt \cdots \lt a_n \le d$；
- 定义一个长度为 $n$ 的数组 $b$：$b_1 = a_1$，$\forall i \ge 1, b_i  = b_{i - 1} \oplus a_i$，其中 $\oplus$ 表示二进制异或 (xor)。在构建出 $b$ 后，应当满足 $b_1 \lt b_2 \lt \cdots \lt b_{n - 1} \lt b_n$ 的限制条件。

由于满足条件的数列数量可能很多，请输出答案模 $m$ 的结果。
### Solution
容易发现，二进制的位数一定是单调递增的。而且异或前缀和单调递增，数列单调递增是二进制位数单调递增的**充要条件**。反证法可以轻松的证明出来。

那么 $n$ 的最大值就是 $\lfloor\log_2d\rfloor+1$。令 $k=\lfloor\log_2d\rfloor+1$。现在我去构造 $k$ 个数，第 $i$ 个数的二进制从左到右的首位是 $1$。令 $f_i$ 表示第 $i$ 个数有几种情况。

容易发现当 $i\ne k$ 时，$f_i=2^{i-1}$，因为后面的 $i-1$ 位可以任意取 $0$ 或 $1$。当 $i=k$ 时，$f_k=d-2^{k-1}+1$，因为这个数的后面 $k-1$ 位不可以随便取，可能会超过 $d$。对于 $f_k$，符合条件的数是 $[2^{k-1},d]$ 的所有数。

现在我可以从这 $k$ 个数中选取任意个数，这样选出来的数进行从小到大的排序就会自动生成一个符合条件的序列。它满足二进制位数严格单调递增，自然会满足这些性质。因为是充要条件，所以不会漏。设选出来的内部种类数是乘法原理，这些东西再利用加法原理相加。

设 $k=3$，那么答案就是 $f_1+f_2+f_3+f_1f_2+f_3f_1+f_2f_3+f_1f_2f_3$。现在要把 $3$ 拓展到 $\lfloor\log_2d\rfloor+1$，这个式子可以被快速求出。

考虑化简这个式子。每个数对答案的贡献要么是 $f_i$ 要么是 $1$（选或者不选），所以贡献是 $(f_i+1)$。直接相乘，减去全都没选的情况就行，即 $(f_1+1)(f_2+1)(f_3+1)\cdots(f_k+1)-1$。直接计算即可。
```cpp
void solve(){
    int n=read(),ans=1;
    mod=read();
    int mx=log2(n)+1;
    F(i,1,mx-1) f[i]=qpow(2,i-1);
    f[mx]=n-pow(2,mx-1)+1;
    F(i,1,mx) mulmod(ans,f[i]+1);
    addmod(ans,-1);
    printf("%lld\n",ans);
}
```

---

