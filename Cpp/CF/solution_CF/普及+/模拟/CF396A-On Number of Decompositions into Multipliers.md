# On Number of Decompositions into Multipliers

## 题目描述

You are given an integer $ m $ as a product of integers $ a_{1},a_{2},...\ a_{n} $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF396A/511aaee908ff3da31c1047aebc73037f3c2d6e3f.png). Your task is to find the number of distinct decompositions of number $ m $ into the product of $ n $ ordered positive integers.

Decomposition into $ n $ products, given in the input, must also be considered in the answer. As the answer can be very large, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the second sample, the get a decomposition of number 2, you need any one number out of three to equal 2, and the rest to equal 1.

In the third sample, the possible ways of decomposing into ordered multipliers are \[7,5\], \[5,7\], \[1,35\], \[35,1\].

A decomposition of positive integer $ m $ into $ n $ ordered multipliers is a cortege of positive integers $ b={b_{1},b_{2},...\ b_{n}} $ such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF396A/b461305f46e6043012038c3479cb445ca537b144.png). Two decompositions $ b $ and $ c $ are considered different, if there exists index $ i $ such that $ b_{i}≠c_{i} $ .

## 样例 #1

### 输入

```
1
15
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 1 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
2
5 7
```

### 输出

```
4
```

# 题解

## 作者：__LiChangChao__ (赞：1)

## 思路

首先我们已知 $m=\prod_{i=1}^na_i$，而 $1\le a_i \le 10^9,1\le n \le 500$，显然不可能直接将所有 $a_i$ 乘起来，那这一题怎么做呢？

但是题目要求的是所有元素乘起来的值 $\prod_{i=1}^nb_i=m$ 的长度为 $n$ 的数组 $b$ 的总数，而且我们有**唯一分解定理**：

对于任意一个正整数 $d$，有：

$$d=p_1^{s_1}\times p_2^{s_2}\times ...\times p_u^{s_u}$$

其中 $p_1 < p_2 <...<p_u$ 且均为质数，数组 $s$ 均为正整数。

显然，给一个数的因数分解质因数等价于给这个数分解质因数。

所以对数组 $a$ 的每个元素分解质因数，再去计算满足所有元素分解质因数后与数组 $a$ 所有元素分解质因数的结果相同的 $b$ 数组的总数就好了。

然而问题又来了：怎样计算 $b$ 数组的总数？

设数组 $a$ 的每个元素分解质因数后一共有 $p$ 个不同的质数，第 $i$ 个质数出现了 $c_i$ 次。

根据组合数学隔板法，把问题转化为：假设一种质因数有 $q$ 种，现在有 $n$ 个箱子，每个箱子都可以放一些这个质因数或不放，但总数必须是 $q$ 个，则有：$C^{n-q+1}_{n-1}$ 种放法。

所以最终答案为：

$$\prod^{p}_{i=1}C^{n-c_i+1}_{n-1}$$

计算答案时，可以用 Lucas 定理来求组合数 $C$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+5;//sqrt(1e9)近似等于 4e5，保险起见开到 5e5
const long long mod=1e9+7;
long long N,k,ans=1;
int p[maxn],v[maxn];
map<long long,long long>mp;
void Prime() {//欧拉筛板子
	for (int i=2;i<= maxn;i++) {
		if (!v[i])p[++p[0]] = i;
		for (int j=1;j<=p[0];j++) {
			if (i*p[j]>maxn) break;
			v[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
}
long long KSM(long long a,long long b,long long p) {//快速幂板子
	long long ans=1;
	while(b) {
		if(b&1)ans=(ans*a)%mod;
		a=(a*a)%mod;
		b/=2;
	}
	return ans;
}
long long C(long long a,long long b) {
	if(a<b)return 0;
	if(a==b)return 1;
	if(b>a-b)b=a-b;
	long long A=1,B=1;
	for(long long i=0; i<b; ++i) {
		A=(A*(a-i))%mod;
		B=(B*(b-i))%mod;
	}
	return (A*KSM(B,mod-2,mod));
}
long long Lucas(long long n,long long m) {//Lucas板子
	if(m==0)return 1;
	return C(n%mod,m%mod)*Lucas(n/mod,m/mod)%mod;
}
void fj(long long a) {//分解质因数
	for(int i=1; p[i]<=a&&p[i]; i++) while(a%p[i]==0)mp[p[i]]++,a/=p[i];
	if(a!=1)mp[a]++;
}
int main() {
	Prime();
	scanf("%lld",&N);
	for(int i=1; i<=N; i++) {
		scanf("%lld",&k);
		fj(k);
	}
	for(auto it=mp.begin(); it!=mp.end(); it++)ans=ans*Lucas(N+(it->second)-1,N-1)%mod;//使用指针来遍历整个map
	printf("%lld",ans);//输出
}
```

---

## 作者：Transparent (赞：1)

### 组合数学

------------

可以先把 $a$ 数组中所有数**分解质因数**，
并记录每个质数**出现的次数**。

枚举每个出现了的质因数，
对于**每种**（即值相等的）质因数，
都可以分别放到 $n$ 个位置上去，
可以在某个位置**不放**，
也可以在某个位置**放很多个**。

利用
~~小学奥数中的~~
**隔板法**，
可以得出：
设这种质因数共有 $x$ 个，
那么就有 $\operatorname{C}(n+x-1,n-1)$ 种放法

注：
（若理解上面的放法是怎么来的，可以跳过）
由于可以不放，所以添加 $n$ 个 $1$ ，代表不放。
所以共有 $(n+x)$ 个数，放到 $n$ 个位置上。
所以一共有 $(n+x-1)$ 个隔板，
要分成 $n$ 份，就需要选择 $(n-1)$ 个隔板，
所以每种质因数有的放法总数
就等于从 $(n+x-1)$ 个隔板中随机选取 $(n-1)$ 个，
有多少种选法，即 $\operatorname{C}(n+x-1,n-1)$

$\operatorname{C}\text{(a,b)=}
\dfrac{a! \div b!}{(a-b)!}$

而如果每次计算时都去计算阶乘，
那就浪费了很多时间。
所以应该预处理出 
$\text{1}$ 到 $\sqrt{n}$ 的**整数**的阶乘。
但是预处理时需要对阶乘取模，
之后就**不能直接做除法**，而计算 $\operatorname{C}\text{(a,b)}$
时需要阶乘相除，
所以还需要预处理除阶乘的**逆元**

逆元：若 $a$ 是 $b$ 在模 $p$ 情况下的逆元，则有
$\text{a} \times \text{b} \equiv 1 ~(\mod~p)$
可以理解成一种类似**倒数**的东西。

可以使用费马小定理求逆元：
因为 $a^{p-1} \equiv 1 ~(\mod~p)$ 
（ $p$ 为质数，且 $a$ 不是 $p$ 的倍数），
所以 $a^{p-2} \times a \equiv 1 ~(\mod~p)$
所以逆元就是 $a^{p-2}$

如果每次计算都需要算幂的话，
效率就不是很高。
而逆元可以**看作是倒数**，所以就有
$\dfrac{1}{(n+1)!} \times \text{(n+1)} \text{=} 
\dfrac{1}{n!}$
于是只需要算出一个逆元，
就可以快速得出其它逆元了

最后注意在分解质因数时，
若那个数**本来就是一个质数**，
那么枚举到 $\sqrt{x}$ 就会漏掉这个数本身，
所以最后特判一下。
也因此在存储质因数数量时不能只把数组开到 $\sqrt{a_i}$，
而开到 $a_i$ 开不下，
所以使用 map 来存。

**代码**：
```cpp
#include<bits/stdc++.h> 
using namespace std;
bool pri[400001];
map<int,int>num;//质数出现的次数 
inline void getprime()//预处理质数 
{
	for(register int i=2;i<=400000;i++)
	{
		if(!pri[i])
		{
			for(register int j=i+i;j<=400000;j+=i)
			{
				pri[j]=1;
			}
		}
	}
}
inline void getnum(int x)//分解质因数 
{
	int i=1,ans=0;
	for(register int i=2;i<=sqrt(x);i++)
	{
		if(!pri[i])
		{
			while(x%i==0)
			{
				x/=i;
				num[i]++;
			}
		}
		if(x==1)break;//分解完毕，退出循环 
	}
	if(x!=1)//注意x可能为质数 
	num[x]++;
}
long long fac[40001],invfac[40001];
const long long Mod=1e9+7;
inline long long Pow(long long a,long long b)//快速幂 
{
	if(b==1)return a;
	if(b==2)return a*a%Mod;
	if(b&1)return a*(Pow(a,b-1)%Mod)%Mod;
	else return Pow(Pow(a,b/2)%Mod,2)%Mod;
}
inline void getfac()//预处理阶乘和阶乘逆元 
{
	fac[0]=1;
	for(register int i=1;i<=40000;i++)
	{
		fac[i]=fac[i-1]*(long long)i%Mod;//求阶乘 
	}
	invfac[40000]=Pow(fac[40000],Mod-2);//费马小定理 
	for(register int i=39999;i>=0;i--)
	{
		invfac[i]=invfac[i+1]*(i+1)%Mod;//看作倒数倒推 
	}
}
inline long long C(int a,int b)//计算组合 
{
	if(b==0)return 1;//特判，无论从多少个板子里选0个都只有一种选法 
	return fac[a]*invfac[b]%Mod*invfac[a-b]%Mod;//乘逆元相当于除以原数 
}
int n,tmp;
long long ans=1;
int main()
{
	getprime();
	getfac(); 
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	{
		scanf("%d",&tmp);
		getnum(tmp);
	}
	map<int,int>::iterator it;
	for(it=num.begin();it!=num.end();it++)
	{
		ans*=C(n+(it->second)-1,n-1);//it->second：即it指向的元素的值 
		ans%=Mod;
	}
	printf("%I64d",ans%Mod);//注意CF输出long long不能用%lld 
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```

---

## 作者：orz_z (赞：0)

### 题目大意

给出一个长度为 $n$ 的序列 $a$，令 $m=\prod_{i=1}^na_i$，问有多少个长度为 $n$ 的序列使得序列中的所有数的乘积等于 $m$。

输出方案数模 $10^9+7$。

### 解题思路

前置知识：组合数学，[逆元](https://blog.csdn.net/qq_46258139/article/details/119850642)。

先考虑将 $a_i$ 分解质因数，并记录每个质数出现的质数，用 `map` 维护即可。

假设现在有 $n$ 个箱子。

对于每个质数， 都可以分别放到 $n$ 个箱子上去， 可以在某个箱子不放， 也可以在某个箱子放很多个。

根据隔板法，得：若一种质因数共有 $x$ 个， 那么就有 $\operatorname{C}(n+x-1,n-1)$ 种放法。

设有 $p$ 个不同的质数，第 $i$ 个质数出现了 $q_i$ 次，那么，
$$
ans=\prod_{i=1}^{p}\operatorname{C}(n+q_i-1,n-1)
$$

### CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int _ = 4e5;

bool pri[_ + 7];

map<int, int> num;

int fac[_ + 7], invfac[_ + 7];

const int Mod = 1e9 + 7;

inline void getprime()
{
    for (int i = 2; i <= _; i++)
        if (!pri[i])
            for (int j = i + i; j <= _; j += i)
                pri[j] = 1;
}

inline void getnum(int x)
{
    for (int i = 2; i * i <= x; i++)
        if (!pri[i])
            while (x % i == 0)
            {
                x /= i;
                num[i]++;
            }
    if (x != 1)
        num[x]++;
}

inline int Pow(int x, int y)
{
    int res = 1;
    while(y)
    {
    	if(y & 1) res = res * x % Mod;
    	x = x * x % Mod;
    	y >>= 1;
	}
	return res;
}

inline void getfac()
{
    fac[0] = 1;
    for (int i = 1; i <= _; i++)
        fac[i] = fac[i - 1] * i % Mod;
    invfac[_] = Pow(fac[_], Mod - 2);
    for (int i = _ - 1; i >= 0; i--)
        invfac[i] = invfac[i + 1] * (i + 1) % Mod;
}

inline long long C(int a, int b)
{
    if (b == 0)
        return 1;
    return fac[a] * invfac[b] % Mod * invfac[a - b] % Mod;
}

int n, tmp;

int ans = 1;

signed main()
{
    getprime();
    getfac();
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &tmp);
        getnum(tmp);
    }
    for (auto it = num.begin(); it != num.end(); it++)
    {
        ans *= C(n + (it->second) - 1, n - 1);
        ans %= Mod;
    }
    printf("%lld\n", ans % Mod);
    return 0;
}
```



---

