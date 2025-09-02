# The Last Non-zero Digit.

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1153

[PDF](https://uva.onlinejudge.org/external/102/p10212.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10212/4e8f810bc4e7a305f60b05b1e511704f8aa33548.png)

## 样例 #1

### 输入

```
10 10
10 5
25 6```

### 输出

```
8
4
2```

# 题解

## 作者：communist (赞：18)

暴力可做！！！（十秒还不打暴力！！！）

暴力算阶乘

边算边取余

上代码
```
#include<iostream>
#define int long long		//开long long
using namespace std;
const int mod=1e9;
signed main()
{
    int n,m;
    while(scanf("%lld%lld",&n,&m)==2)   //多组数据
    {
        int ans=1;
        while(m--)
        {
            ans*=n--;
            while(ans%10==0)
                ans/=10;	//统计末尾0的个数
            ans%=mod;
        }
        printf("%lld\n",ans%10);
    }
    return 0;
}
```

---

## 作者：yingjingxu_NaS2O3 (赞：3)

## 思路

一种很暴力的做法。

我们注意到每一对 $2$ 和 $5$ 对答案是没有贡献的。

考虑记录 $P_n^m$ 的因子中 $2$ 和 $5$ 的个数，记为

$$P_n^m=2^{\alpha_1}\times 5^{\alpha_2}\times r$$

则最终答案为

$$2^{\max(\alpha_1-\alpha_2,0)}\times 5^{\max(\alpha_2-\alpha_1,0)} \times r$$

对于前两个，快速幂即可。对于 $r$，边乘边模 $10$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define mod 10ll
using namespace std;
int n,m;
int quick_pow(int a,int b,int p)
{
    int ret=1;
    while(b)
    {
        if(b&1)
            ret=ret*a%p;
        a=a*a%p;
        b>>=1;
    }
    return ret;
}
signed main()
{
    while(~scanf("%lld%lld",&n,&m))
    {
        int ans=1,cnta=0,cntb=0;
        for(int i=n-m+1;i<=n;i++)
        {
            int tmp=i;
            while(!(tmp&1))
            {
                tmp>>=1;
                cnta++;
            }
            while(tmp%5==0)
            {
                tmp/=5;
                cntb++;
            }
            if(tmp==1)
                continue;
            ans=ans*tmp%mod;
        }
        cnta-=cntb;
        if(cnta<0)
            ans=ans*quick_pow(5,-cnta,mod)%mod;
        else
            ans=ans*quick_pow(2,cnta,mod)%mod;
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：resftlmuttmotw (赞：1)

## 题意
**[题目链接](https://vjudge.net/problem/OpenJ_Bailian-1150)**
本题大意为 给定m,n

求：$P^m_n$的最后一位非0的数

（P在排列组合中就相当于A）
## （beican）历程
看到题目 什么都不会的我一脸懵

（[洛谷](https://www.luogu.org/problemnew/show/UVA10212)的限制太水了

vjudge上时限1s

我们按严格的来）

但仔细想了一下 我仍然只发现暴力是不可以的

我暴力的思路是 乘起来

但直接乘会爆 就留个9位吧（感觉有点靠运气）

这样的思路肯定是错的 （[像这位小哥](https://www.luogu.org/blog/communist/solution-uva10212)）

也不要想去优化 不然就像我搞了半天 仍然`TLE`


接着 再仔细想想 发现求最后一位非0的数 只需要我们在算的过程中除10

又知道 $P^m_n$ = $\frac{n!}{(n -m)!}$ = $\prod^n_{i=n-m+1}$i



**换言之我们需要将含有因子2和5的除*掉**

BTW将因子2和因子5的数量统计

因为一个10是由一个2和一个5乘得得

直接除*掉不能保证因子2与因子5数量相等

**需要把多的乘回去（用快速幂）**

```cpp
for(i = n;i > n - m;i--)
	 {
	    	int j = i;
	    	while(j % 2 == 0)
	    	{
	    		j /= 2;
	    		d2++;
			}
	    	while(j % 5 == 0)
	    	{
	    		j /= 5;
	    		d5++;
			}
			
			ans = (ans * j) % 10;
		}
if(d2 > d5)
			More = qkpow(2,d2 - d5);
		else if(d5 > d2) More = qkpow(5,d5 - d2);

```

整体的代码大致如下
```cpp
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
 
using namespace std;

long long d2,d5,More,ans;
inline long long qkpow(int val,int n)
{
	long long rest = 1;
	while(n)
	{
		if(n & 1)
			rest = val * rest % 10;
		val = val * val % 10;
		n >>= 1;
	}
	return rest;
}
int main()
{
    int i,n,m;
    while(~scanf("%d%d",&n,&m))
    {
    	d2 = d5 = 0;
    	More = ans = 1;
	    for(i = n;i > n - m;i--)
	    {
	    	int j = i;
	    	while(j % 2 == 0)
	    	{
	    		j /= 2;
	    		d2++;
			}
	    	while(j % 5 == 0)
	    	{
	    		j /= 5;
	    		d5++;
			}
			
			ans = (ans * j) % 10;
		}
		if(d2 > d5)
			More = qkpow(2,d2 - d5);
		else if(d5 > d2) More = qkpow(5,d5 - d2);
		printf("%lld\n",ans * More % 10);
	}
    return 0;
}
```
**然后又`TLE`**了

~~然后我不相信我不能成功~~

又yy出来一个优化版本
```cpp
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
 
using namespace std;

long long d2,d5,More,ans;
inline long long qkpow(int val,int n)
{
	long long rest = 1;
	while(n)
	{
		if(n & 1)
			rest = val * rest % 10;
		val = val * val % 10;
		n >>= 1;
	}
	return rest;
}
int main()
{
    int i,n,m;
    while(~scanf("%d%d",&n,&m))
    {
    	if(m == 0)
    	{
    		printf("1\n");
    		continue;
		}
    	d2 = d5 = 0;
    	More = ans = 1;
	    for(i = n;i > n - m;i--)
	    {
	    	int j = i,k;
	    	for(k = 1;!(j & k);k <<= 1,d2++);
	    	j /= k;
	    	while(j % 5 == 0)
	    	{
	    		j /= 5;
	    		d5++;
			}
			ans = (ans * j) % 10;
		}
		if(d2 > d5)
			More = qkpow(2,d2 - d5);
		else if(d5 > d2) More = qkpow(5,d5 - d2);
		printf("%lld\n",ans * More % 10);
	}
    return 0;
}
```

**又`TLE`**
## 正解1
其实粗略估一下时间复杂度O（n$log_n$m）（m为询问数）

**0 <= N<= 20000000**

明显不行 （这题还有点坑，她没说询问数上线）

然后我又想了下离线优化（没YY出来）

最后 我又搞了搞事情 我写了个预处理

```cpp
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
 
using namespace std;
const int MAXN = 20000001;
int d2,d5,More,ans,a[MAXN][3];
inline int qkpow(int val,int n)
{
	int rest = 1;
	while(n)
	{
		if(n & 1)
			rest = val * rest % 10;
		val = val * val % 10;
		n >>= 1;
	}
	return rest;
}
int main()
{
    int i,n,m;
    for(i = 1;i < MAXN;i++)
    	if(i % 2 != 0&&i % 5 != 0) a[i][2] = i;
    	else {
    		if(i % 2 == 0) a[i][0] = a[i / 2][0] + 1,a[i][2] = a[i / 2][2]; 
    		if(i % 5 == 0) a[i][1] = a[i / 5][1] + 1,a[i][2] = a[i / 5][2];
		}
	a[i][2]存i去掉她的所有2,5因子后的值（如 i = 6 那么a[i][2] = 3）
	a[i][0]存i含的因子2的数量
	a[i][1]存i含的因子5的数量
    while(~scanf("%d%d",&n,&m))
    {
    	if(m == 0)
    	{
    		printf("1\n");
    		continue;
		}
		int i,tot = 1,d2,d5;
		d2 = d5 = 0;
    	for(i = n;i > n - m;i--)
    	{
    		tot = tot *a[i][2] % 10;
    		d2 += a[i][0];
    		d5 += a[i][1];
		}
		int More = 1;
		if(d2 > d5) More = qkpow(2,d2 - d5);
		else More = qkpow(5,d5 - d2);
		tot = tot * More % 10;
		printf("%d\n",tot);
	}
    return 0;
}
```
然后惨痛`MLE`(空间超限)（请妳不要用看hen**tai 的眼神看我）

估一下空间

众所周知 一int占4字节

1b(byte) = 1 字节

我用了20000000 *　3 * 4b

即240000kb

但是题目限制65536 kB

**$\color{red}\text{阿勒}$**

我没超限啊？

不管了 错了就是错了 事实如此 无需诡辩

然后去看题解

好多长得一样的 （我不知道为什么，真de不知道）

然后写得一点都不富有亲和力

（于是我决定详详细细地写一篇（好像已经很长了））

但是 我们可以考虑用`short int`来存

`a[i][2]`只存i去掉她的所有2,5因子后的值的个位

`a[i][0]`存i含的因子2的数量

`a[i][1]`存i含的因子5的数量

a[i][0] 可以 与 a[i][1]相等部分可以抵消（所以a[i][0] 和 a[i][1]中始终有一个是0）

易发现

$2^1$ = 2 $2^2$ = 4 $2^3$ = 8 $2^4 = 6$ $2^5 = 2$

以上都是mod 10后的 可以发现有循环产生 

5也有相同情景 就可以采用某种神奇的存储方式

达到用short int存的效果

这里就点到为止 不再展开（感兴趣的同学可以向这个方向想一下）

~~我是没有想出来的~~

妳才没有被坑

让我们把精力放在~~真正的~~正解上（滑稽
## 正解2

思路不变仍然要统计2,5的个数

不过不枚举 直接从整个阶乘去求

```cpp
inline int kiyo(int n,int div)
{
	if(n == 0) return 0;
	return (n / div + kiyo(n / div,div));
}
```
div为求的数

如 求 5!中含因子2的个数

就` kiyo(5,2)`

`return 0;`很好理解

但 为什么`return (n / div + kiyo(n / div,div));`

n / div 是针对1~n的含div的个数

但考虑到 kiyo(5,2) 中有4这种情况

4中有两个2但n / div只统计了一次

`kiyo(n / div,div)`就是为了统计未统计到的


举个栗子`kiyo(10,2)`

1 2 3 4 5 6 7 8 9 10

0 1 0 1 0 1 0 1 0 1第一次`n / div`

1 2 3 4 5第二次`n / div`
0 1 0 1

**但由于第二次是除了一次2的**

所以实际算的是

2 4 6 8 10
0 1 0 1 0

类似的

最终可得

1 2 3 4 5 6 7 8 9 10

0 1 0 2 0 1 0 3 0 1  8

再用` kiyo(n,div)`- `kiyo(n - m,div)`

在logn的时间复杂度内求出2,5的个数

也许有同学会想到 那么再求出3,7的个数就行了啊

因为 偶数都可以转化为对应的奇数

而 1 3 5 7 9中 

1不管 

9是3的倍数

5已经求了

把7,3求一下

**OK!**

然后  **妳** 就 **华丽**地爆零 瞬间成为奥林匹斯山上的宙斯

Why?

因为 13 17 等虽不是3,7的倍数 却有3,7

所以 求的应该是末位是3,7,9的的数的个数

以下即为求法

`get(a,b)`即求1~a中有多少末位为b的
```cpp
inline int odd(int n,int div)
{
	if(n == 0) return 0;
	return n / 10 + (n % 10 >= div) + odd(n / 5,div);
	按以下分步的
	1  2   3  4  5  6  7  8  9  10
	11 12  13 14 15 16 17 18 19 20
	....
	n+1 n+2...
	所以是先 n / 10 代表有几层就有几个末位是div的
	但考虑到可能n是10a+b（b<10）的形式就有可能还有1个
	 所以(n % 10 >= div)
	但以上没有考虑5
	如15/5=3
	而除以5的操作是之前进行的 这里没有记录15仍然是15
	所以还需 odd(n / 5,div)跟上面kiyo含意类似
	类似地 同学可能会说6不是还要除以2吗 为什么不再调用一个odd(n / 2,div)
	因为get()已经解决了该问题
}
inline int get(int n,int div)
{
	if(n == 0) return 0;
	return (get(n / 2,div) + odd(n,div));
	分成奇偶两个数列
	因为算的都是1~n
	所以只有两种情况
	Case1:n ≡ 0 (mod 2)
	可以分为
	1 3 5...n-1
	这边（上面）的就可以调odd()函数算了
	为什么odd()的不除以2呢？ 因为odd()默认算奇数
	2 4 6...n
	进行除2操作类似于odd的除5操作
	Case2:n ≡ 1 (mod 2)
	1 3 5...n
	2 4 6...n-1
	其实与Case1差不多int a = b / 2;
	b为奇的话 就相当于(b-1)/2
	不影响get(n / 2,div)
	odd(n,div)直接传的n多的那一位也有考虑在内
}
```

由此可以得到含因子2,5的数量

和1~n中末位为3,7,9的数量

还需
```cpp
- get(n - m,3)
```
因为求的是$P^m_n$ = $\frac{n!}{(n -m)!}$ = $\prod^n_{i=n-m+1}$i
## Code（正解2的）
```cpp
#include <cstdio>
#include <vector>
 
using namespace std;

inline int qkpow(int val,int n)
{
	int rest = 1;
	while(n)
	{
		if(n & 1)
			rest = val * rest % 10;
		val = val * val % 10;
		n >>= 1;
	}
	return rest;
}
inline int kiyo(int n,int div)
{
	if(n == 0) return 0;
	return (n / div + kiyo(n / div,div));
}
inline int odd(int n,int div)
{
	if(n == 0) return 0;
	return n / 10 + (n % 10 >= div) + odd(n / 5,div);
}
inline int get(int n,int div)
{
	if(n == 0) return 0;
	return (get(n / 2,div) + odd(n,div));
}
int main()
{
	int n,m;
    while(~scanf("%d%d",&n,&m))
    {
    	无限输入
    	int ans = 1;
    	int t2 = kiyo(n,2) - kiyo(n - m,2);
    	int t5 = kiyo(n,5) - kiyo(n - m,5);
    	计算含2,5因子数
    	int t3 = get(n,3) - get(n - m,3);
    	int t7 = get(n,7) - get(n - m,7);
    	int t9 = get(n,9) - get(n - m,9);
    	算末位为3,7,9的数的个数
    	if(t2 > t5) ans = ans * qkpow(2,t2 - t5) % 10;
    	else ans = ans * qkpow(2,t5 - t2) % 10;
    	ans = ans * qkpow(3,t3) % 10;
    	ans = ans * qkpow(7,t7) % 10;
    	ans = ans * qkpow(9,t9) % 10;
    	套快速幂 logn
    	好像在这里还有O（1）的做法 不太懂 感兴趣的同学可以去看看其它博客
    	printf("%d\n",ans);
	}
    return 0;
}
```

恭喜妳

又能AC一题

---

## 作者：Arcturus1350 (赞：0)

这题在学长讲完之后和看完题解之后才明白函数怎么构造。

这题构造一个$f(n)$

$f(n)$ $=$ $n$除以 $2^{a}$ $*$ $5^{b}$ ，$a$ ， $b$ 分别是 $n$ 质因数分解后$2,5$的个数。

然后就暴力算一算就好了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
//处理出来n的质因子中，x的个数。
int  prime(int n,int x)
{
	int res=0;
	while(n) res+=n/x,n/=x;
	return res;
}
//f(1)到f(n)中不以5结尾的奇数的个数
int expect_5_end_odd(int n,int x)
{
	if(!n) return 0;
	return n/10+(n%10>=x)+expect_5_end_odd(n/5,x); 
}
//以5结尾的数的个数。
int expect_5_end(int n,int x)
{
	if(!n) return 0;
	return expect_5_end(n/2,x)+expect_5_end_odd(n,x);
}

int t[4][4]={
	6,2,4,8,//2^4 2 2^2 2^3 的最后一位
	1,3,9,7,//3^4 3 3^2 3^3 的最后一位
	1,7,9,3,//4……
	1,9,1,9//5……
};

signed main()
{
	int n,m;
	while(~scanf("%d%d",&n,&m))
	{
		m=n-m;
		int prime_2=prime(n,2)-prime(m,2);
		int prime_3=expect_5_end(n,3)-expect_5_end(m,3);
		int prime_5=prime(n,5)-prime(m,5);
		int prime_7=expect_5_end(n,7)-expect_5_end(m,7);
		int prime_9=expect_5_end(n,9)-expect_5_end(m,9);
	
		if(prime_2<prime_5){puts("5");continue;}
	
		int res=1;
		if(prime_2>prime_5) res*=t[0][(prime_2-prime_5)%4];
		res=res*t[1][prime_3%4]*t[2][prime_7%4]*t[3][prime_9%4]%10;
		printf("%lld\n",res);
	}
	return 0;
}
```

---

