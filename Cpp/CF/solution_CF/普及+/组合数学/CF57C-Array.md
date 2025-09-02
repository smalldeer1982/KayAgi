# Array

## 题目描述

Chris the Rabbit has been interested in arrays ever since he was a child. At the moment he is researching arrays with the length of $ n $ , containing only integers from $ 1 $ to $ n $ . He is not good at math, that's why some simple things drive him crazy. For example, yesterday he grew keen on counting how many different beautiful arrays there are. Chris thinks that an array is beautiful if it meets one of the two conditions:

- each elements, starting from the second one, is no more than the preceding one
- each element, starting from the second one, is no less than the preceding one

Having got absolutely mad at himself and at math, Chris came to Stewie and Brian to ask them for help. However, they only laughed at him and said that the answer is too simple and not interesting. Help Chris the Rabbit to find the answer at last.

## 样例 #1

### 输入

```
2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
```

### 输出

```
17
```

# 题解

## 作者：Prurite (赞：15)

这道题是一道很精妙的**组合数学**。

## 总思想：转化

首先，因为不增和不降是相对称的，所以我们只用从一个角度入手进行计算。
因为题目中保证了原序列只有 $1-n$ 这些数，且它们的顺序是固定的，
所以我们可以用一个集合 $S=\{ x_1, x_2, \ldots, x_i \}$ 来唯一地表示这个序列
（ $x_i$ 表示序列中数字 $i$ 的数量）。
所以 $x_1+x_2+...+x_n = n$ .
因为 $S$ 和原序列存在对应关系，
所以我们只需求出有多少种不同的 $S$ 就能知道有多少种不同的序列。
**【第一次转化】**

因为 $\sum\limits_{i=1}^n x_i=n$，
所以问题又可以转化为有 $n$ 个 $1$ ，在中间插入 $n-1$ 个隔板的方案数。
（每相邻两个隔板间的 $1$ 的个数就是对应的 $x_i$ 的值。）
比如，对于下面这种方案 `| 1  1 || 1 |`，有 $n=3, x_1=2, x_2=0, x_3=1$ .
当然实际计算的时候为了简明就 **不计两端的隔板** 。
**【第二次转化】**  
对于这个问题，可以这么理解：
假设一共有 $2n-1$ 个位置，其中有 $n$ 个位置放1，另外 $n-1$ 个位置放隔板。
这里就显然有 $C_{2n-1}^n$ 种方法放 1 （从 $2n-1$ 个位置里选 $n$ 个位置的方案数）

我们再回到原问题。
由上得到单独的不升/不降序列就有 $C_{2n-1}^n$ 种不同的序列，
那两种情况合并就有 $ 2C_{2n-1}^n$ 种。
注意如 `1 1 1 1` 这种全部相同的情况（共有 $n$ 种）被考虑了两次，还要除去。
最终答案为 $2C_{2n-1}^n-n$ .
注意因为涉及到除法取模需要使用逆元。

思路明确了代码就很简单了，此处就不贴出来了。

---

## 作者：pufanyi (赞：9)

首先，看到这样的问题，我们想到这应该是道dp。

我们设$f[i][j]$表示前$i$个数到达最后一位是$j$的递增序列的方案数，则不难根据对称性得出答案为$2\sum_{i=1}^{n}f[n][i]-n$，减$i$是为了减去递增和递减都包含的情况（即全部相同的请况，那显然是$i$）。

我们发现$f[i][j]$的状态由所有$f[i-1][k](k\le j)$的状态在结尾加上$k$转移过来。故转移方程为：$f[i][j] = \sum_{k=1}^{j}f[i-1][k]$。

于是暴力程序就打出来了，那么让我们打张表：

```cpp
#include <cstdio>

const int n = 10;

int f[n+1][n+1];

int main()
{
	freopen("biao.out", "w", stdout);
	int ans;
	for(int i = 1; i <= n; ++i)
		f[1][i] = 1;
	for(int i = 2; i <= n; ++i)
	{
		ans = 0;
		for(int j = 1; j <= n; ++j)
			for(int k = 1; k <= j; ++k)
				f[i][j] = f[i][j] + f[i-1][k];
		for(int j = 1; j <= i; ++j)
			ans = ans+f[i][j];
	}
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= n; ++j)
			printf("%5d ", f[i][j]);
		puts("");
	}
}
```

biao.out

```
    1     1     1     1     1     1     1     1     1     1 
    1     2     3     4     5     6     7     8     9    10 
    1     3     6    10    15    21    28    36    45    55 
    1     4    10    20    35    56    84   120   165   220 
    1     5    15    35    70   126   210   330   495   715 
    1     6    21    56   126   252   462   792  1287  2002 
    1     7    28    84   210   462   924  1716  3003  5005 
    1     8    36   120   330   792  1716  3432  6435 11440 
    1     9    45   165   495  1287  3003  6435 12870 24310 
    1    10    55   220   715  2002  5005 11440 24310 48620 
```

一看发现：这不是杨辉三角吗？

于是毫不犹豫地打了个$n^2$，然后就T飞了。

竟然没想到$\sum_{i=1}^{n}f[n][i] = f[n+1][n] = C^{n}_{2n}$（可以直接推，也可以看作是在序列结尾加一个$n$进行限制）。

于是答案就变成了$2C^n_{2n}-n$。取模要求逆元，用费马小定理做一下，总时间复杂度为$O(n)$。

当然，杨辉三角也是可以直接推出来的：
$$f[i][j] = \sum_{k=1}^{j}f[i-1][k] = f[i-1][j] + \sum_{k=1}^{j-1}f[i-1][k] = f[i-1][j] + f[i-1][j-1].$$
以下是我的代码（由于模拟赛加了文件读入输出）：

```cpp
#include <fstream>

using namespace std;

typedef long long LL;

ifstream fin("pretty.in");
ofstream fout("pretty.out");

inline LL pow(LL x, LL y, LL mod)
{
	LL ans = 1;
	for(; y; y >>= 1, x = (x*x)%mod)
		if(y & 1)
			ans = (ans*x) % mod;
	return ans % mod;
}

const LL mod = 1000000007;
const int maxn = 100005;

LL fac[maxn<<1];

int main()
{
	LL n;
	fin >> n;
	fac[0] = 1;
	for(int i = 1; i <= (n<<1); ++i)
		fac[i] = fac[i-1] * i % mod;
	fout << (fac[n<<1]* pow(fac[n]*fac[n]%mod, mod-2, mod)) % mod - n << endl;
	return 0;
}
```



---

## 作者：JACK_POT (赞：5)

**~~一道数论题QAQ~~**

建立模型：一个高为$1$ ，长为$2n-1$的矩形，由$1*1$的小方格排列而成，其中$n-1$个是空格，$n$个记录从第一个小方格到当前小方格中，共有多少个空格标志。这些数值组成所求数组，只不过，数字的范围是从0 ~ n-1，与题目从1 ~ n是等价的。

例如n=5，[1,2,2,4,5]（等价于[0,1,1,3,4]）即为
|  0|  | 1 | 1 |  |  | 3 |  |4  |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |

这种序列可以得到$C_{2n-1}^n$个，同样的，满足非升序列的种数也是$C_{2n-1}^n$，

但是，当数组中n个数都相同，是两种序列重复的，共有n种

因此，最终答案是，$2C_{2n-1}^n-n$（或者$C_{2n}^n-n$,可以发现恒等））

由于n和mod的值很大，我们要用逆元对组合数取模

……（此处省略114514字）**~~数论只会GCD的我百度了半天~~**

最终答案为$\left(2*\left(\prod\limits_{i=n+1}^{2n}i\right)*\left((n-1)!\right)^{mod-2}-n+mod\right)\%mod$  

其中乘方用快速幂

时间复杂度$O(2*n+log(1000000007))$

上代码

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1000000007;
int n;
ll up=1,down=1;
ll inverse(ll x,ll y)//求逆元（快速幂）a关于p的逆元ans=a^(p-2) 
{
    ll ans=1;
    while(y)
    {
        if(y&1)
        ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}
int main()
{
	//freopen("array10.in","r",stdin);
	//freopen("array10.out","w",stdout);
    scanf("%d",&n);
    for(int i=n+1;i<2*n;i++)//分子(2n-1)*……*n+1
        up=up*i%mod;
    for(int i=1;i<=n-1;i++)//分母(n-1)!
        down=down*i%mod;
    printf("%d\n",((2*up*inverse(down,(ll)mod-2))-n+mod)%mod);//变除为乘,求逆元
    return 0;
}
```


---

## 作者：nueryim (赞：4)

## 题解：CF57C Array

### 题意

给定 $n$，求有多少**不同**的序列满足以下条件：

- 长 $n$
- 以**不大于** $n$ 的**正整数**组成
- **单调不降**或**单调不升**

### 分析

显然单调不降的序列个数与单调不升的序列个数**相等**（只要左右翻转过来就能重合）

那么只要我们能求出单调不降的序列个数 $cnt$，答案 $ans=2cnt-n$，即把单调不降的和单调不升的个数加起来再减去 $n$ 条被算 $2$ 次的**水平**序列。

考虑如何求单调不降的序列个数，首先我想到了动态规划。设 $dp_{i,j}$ 表示长度为 $i$，序列最后一项小于等于 $j$ 的序列数量；边界为 $dp_{1,1\sim n}=1$；目标状态为 $dp_{n,n}$；状态转移方程为 $dp_{i,j}=\sum_{k=1}^jdp_{i-1,k}$，即把当前这一项接到序列末项小于等于它的序列后边。

但这样显然会超时，于是我们观察状态转移方程：

$$dp_{i,j}=\sum_{k=1}^jdp_{i-1,k}$$

变形：

$$dp_{i,j}=\sum_{k=1}^{j-1}dp_{i-1,k}+dp_{i-1,j}$$

代入：

$$dp_{i,j}=dp_{i,j-1}+dp_{i-1,j}$$

这个式子和杨辉三角的式子很像，为了更直观，下面给出 $n=4$ 时的 $dp$ 数组的值：

~~~
1  1  1  1
1  2  3  4
1  3  6  10
1  4  10 20
~~~

  这里就很显然了，$dp$ 数组正是杨辉三角旋转 $45^\circ$ 后的样子，手玩一下下标发现 $dp_{n,n}$ 对应杨辉三角中 $2n-1$ 行 $n-1$ 列，即组合数 $C_{2n-1}^{n-1}$，用组合数公式易得 $dp_{n,n}=C_{2n-1}^{n-1}=\frac{(2n-1)!}{n!(n-1)!}$

于是我们可以 $O(n)$ 预处理阶乘，用费马小定理求逆元。

### 代码

~~~cpp
// Array (AC)

#include <iostream>
using namespace std;

typedef long long ll;

const ll mod = 1e9 + 7;
const int N = 1e5 + 5;

ll n, jie[N << 1];

ll ksm(ll a, ll t)
{
    ll res = 1;
    while (t)
    {
        if (t & 1)
            res = res * a % mod;
        a = a * a % mod;
        t >>= 1;
    }
    return (res + mod) % mod;
}

ll c(int n, int m)
{
    return jie[n] * ksm(jie[m], mod - 2) % mod * ksm(jie[n - m], mod - 2) % mod;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    
    jie[0] = 1;
    for (ll i = 1; i <= n * 2; i ++)
        jie[i] = jie[i - 1] * i % mod;
    cout << (c(n * 2 - 1, n - 1) * 2 % mod + mod - n) % mod << endl;

    return 0;
}
~~~

---

## 作者：codecode (赞：4)

#### 题解: 

显然，我们应该分成两部分统计答案，即单调不降的和单调不升的，它们各自的数量应该一样多（$a_i\leftrightarrow n+1-a_i$ 作对应），且恰有 $n$ 个公共的（既单调不降，又单调不增，即全部相等）。于是，我们统计有多少个单调不降的数组 $a$，设有 $S$ 个，则最终答案为 $2S-n$。

$S$ 即为满足 $1\leq a_1\leq a_2\leq\cdots\leq a_n\leq n$ 的正整数组 $(a_1,a_2,\cdots,a_n)$ 的数量。这是一个经典的问题，我们有如下做法：

- 记 $b_i=a_i+i$，则 $2\leq b_1<b_2<\cdots<b_n\leq 2n$；

- 每一组满足条件的数组 $A$ 和满足条件的数组 $B$ 是一一对应的。

我们统计合法的数组 $B$ 的数量，明显的这是组合数的定义（从 $2,3,\cdots,2n$ 这 $2n-1$ 个数中选出 $n-1$ 个不同的作为 $B$ 数组），即 $S=C_{2n-1}^n$。

综上，所求答案即为 $2S-n=2C_{2n-1}^n-n=C_{2n}^n-n$。

我们可以预处理 $1\sim n$ 的逆元，随后 $\Theta(n)$ 暴力求出组合数，总时间复杂度 $\Theta(n)$。

> [如何线性时间求乘法逆元](https://www.luogu.com.cn/problem/P3811)
>


------------

#### 代码：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int maxn=1e5+233;
int n,ans=1,et[maxn];
signed main(){
	cin>>n;
	et[1]=1;
	for(int i=2;i<=n;i++)
		et[i]=(mod-mod/i)*et[mod%i]%mod; //预处理逆元
	for(int i=1;i<=n;i++)
		ans=ans*et[i]%mod*(n+i)%mod; //暴力组合数
	cout<<((ans-n)%mod+mod)%mod;
	return 0;
}

```

---

## 作者：Ryan_Adam (赞：1)

## 题解：CF57C Array
### Tag
组合数学
### Solution
楼上做法有些麻烦了。

首先发现单调不增和单调不降答案是相同的，考虑一种乘 $2$ 再减去所有数相同的 $n$ 种方案即可。

其次我们发现如果确定了每种数选几个，方案是被唯一确定的，换言之，数的选择方式是和最终合法方案一一对应的。题目就转化为了将 $n$ 个数分为 $n$ 堆每堆允许为空的方案数有多少，插板法经典例题，答案为 $\dbinom{2n-1}{n}$。

输出 $2\dbinom{2n-1}{n}-n$ 即可。

---

## 作者：蒟蒻丁 (赞：1)

* 被之前的卡特兰数误导了，写了半天满江红$qwq$

设这个数列为$a$

既然直接求$a$的个数很困难，那么就换一个方向考虑，于是$LH$大佬很快想到了差分数组

设$a$的差分数组为$b$，看来$\sum_{i=1}^{n}{b_i}$就等于$a_n-a_1$，枚举$a_n-a_1$，求出$b$数组，$b$数组的个数正是$a$数组的个数

这里我枚举的是$a_1$(其实$a_1=b_1$的啦)，默认$a_n=n$，所以用插板法可以求出$b$数组个数
```
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define N 3001000
#define mod 1000000007
using namespace std;
ll n,m,inv[N],s[N],ans;

ll ksm(ll x,ll k){
	ll tmp=1;
	while(k){
		if(k%2==1)tmp*=x,tmp%=mod;
		x=x*x%mod;
		k/=2;
	}
	return tmp;
}
//c(a,b)

ll C_c(ll a,ll b){
	if(b<a)return 0;
	if(a==0)return 1;
	if(b==0)return 0;
	return s[b]*inv[b-a]%mod*inv[a]%mod;
}

int main(){
	cin>>n;
	s[0]=1;
	for(ll i=1;i<=2*n;i++){
		s[i]=s[i-1]*i%mod;
		inv[i]=ksm(s[i],mod-2);
	}
	for(ll i=0;i<n;i++){ 
		ans+=C_c(n-1,2*n-i-1);
		ans%=mod;
	}
	cout<<(ans-n+mod+1)%mod;
}
```

---

## 作者：cike_bilibili (赞：0)

首先问题可以转化，不妨只考虑单调不降，因为问题是对称的。我们发现我们需要给每一个位置分配一个非负整数值，这样做一个前缀和就是一个非降序列，并且所有分配的值的和小于等于 $n$，问题等价于给定不等式：

$$$ \sum_{i=1}^n x_i\le n$$$
求出所有非负整数解，我们不妨添加一项 $x_{n+1}$ 让此不等式变成方程 $\sum_{i=1}^{n+1} x_i = n$，我们只需求出所有非负整数解，即 $C_{2n-1}^n$。

答案 $\times 2$ 后并不是正确的答案，因为所有 $x$ 都相同的情况被算了两遍，答案要减去 $n$。

所以最后答案是 $2C_{2n-1}^n - n$。

---

