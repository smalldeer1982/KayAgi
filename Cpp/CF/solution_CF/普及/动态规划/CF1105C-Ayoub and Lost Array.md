# Ayoub and Lost Array

## 题目描述

已知有一个长度为$n$($1\leq n\leq 2 \times 10^5$)的数列，每一个数的大小在$[l,r]$($1\leq l \leq r \leq 10^9$)之间。求出有多少种方案使得这个数列的和为$3$的倍数。答案对$10^9+7$取模。当然，如果无法组成任何一个合法的数列，答案即为$0$。

## 样例 #1

### 输入

```
2 1 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 2 2
```

### 输出

```
1
```

## 样例 #3

### 输入

```
9 9 99
```

### 输出

```
711426616
```

# 题解

## 作者：BFLSTiger (赞：31)

虽然这题较简单，但我们还是考虑从暴力一点点优化。

## 做法一

我们考虑枚举每一位是多少，然后判断是否合法。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
namespace Dango
{
	const int MAXN=200005,MOD=1000000007;
	int n,l,r;
	long long ans;
	int read()
	{
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
		while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
		return f?-x:x;
	}
	void dfs(int a)
	{
		static long long sum;
		if(a>n)
		{
			if(!(sum%3))
			{
				ans++;
				if(ans>=MOD)ans-=MOD;
			}
			return;
		}
		for(int i=l;i<=r;i++)
		{
			sum+=i;
			dfs(a+1);
			sum-=i;
		}
	}
	int work()
	{
		n=read();l=read();r=read();
		dfs(1);
		printf("%lld",ans);
		return 0;
	}
}
int main()
{
	return Dango::work();
}
```

时间复杂度：$O((r-l)^n)$

空间复杂度：$O(n)$

## 做法二

我们仔细想了想忽然发现，根据题目要求，所有数可以分成三种：$mod$ $3$ 余 $1$、$2$、$3$。同种数在此题是等价的，且这三种数的数量可以轻松统计。所以我们可以考虑枚举每一位$mod$ $3$的余数，然后统计答案。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
namespace Dango
{
	const int MAXN=200005,MOD=1000000007;
	int n,l,r,cnt[3];
	long long ans;
	int read()
	{
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
		while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
		return f?-x:x;
	}
	long long pow_(long long a,long long b)
	{
		long long res=1;
		while(b)
		{
			if(b&1)res=res*a%MOD;
			a=a*a%MOD;
			b>>=1;
		}
		return res;
	}
	void dfs(int a)
	{
		static long long sum,res=1;
		if(a>n)
		{
			if(!sum)ans=(ans+res)%MOD;
			return;
		}
		for(int i=0;i<3;i++)
		{
			if(!cnt[i])continue;
			sum=(sum+i)%3;
			res=res*cnt[i]%MOD;
			dfs(a+1);
			res=res*pow_(cnt[i],MOD-2)%MOD;
			sum=(sum-i+3)%3;
		}
	}
	int work()
	{
		n=read();l=read();r=read();
		cnt[0]=(r+3)/3-(l+2)/3;
		cnt[1]=(r+2)/3-(l+1)/3;
		cnt[2]=(r+1)/3-l/3;
		dfs(1);
		printf("%lld",ans);
		return 0;
	}
}
int main()
{
	return Dango::work();
}
```

时间复杂度：$O(3^n)$

空间复杂度：$O(n)$

## 做法三

过了几分钟，我们又发现这题可以 $dp$ 。我们设 $dp[i][j]$ 表示前 $i$ 个数的和 $mod$ $3$ 余 $j$。转移显然：
$$dp[i][0]=dp[i-1][0]*cnt[0]+dp[i-1][1]*cnt[2]+dp[i-1][2]*cnt[1]$$

$$dp[i][1]=dp[i-1][0]*cnt[1]+dp[i-1][1]*cnt[0]+dp[i-1][2]*cnt[2]$$

$$dp[i][2]=dp[i-1][0]*cnt[2]+dp[i-1][1]*cnt[1]+dp[i-1][2]*cnt[0]$$

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
namespace Dango
{
	const int MAXN=200005,MOD=1000000007;
	int n,l,r,cnt[3];
	long long dp[MAXN][3];
	long long ans;
	int read()
	{
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
		while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
		return f?-x:x;
	}
	int work()
	{
		n=read();l=read();r=read();
		cnt[0]=(r+3)/3-(l+2)/3;
		cnt[1]=(r+2)/3-(l+1)/3;
		cnt[2]=(r+1)/3-l/3;
		dp[0][0]=1;
		for(int i=1;i<=n;i++)
		{
			dp[i][0]=(dp[i-1][0]*cnt[0]%MOD+dp[i-1][1]*cnt[2]%MOD+dp[i-1][2]*cnt[1]%MOD)%MOD;
			dp[i][1]=(dp[i-1][0]*cnt[1]%MOD+dp[i-1][1]*cnt[0]%MOD+dp[i-1][2]*cnt[2]%MOD)%MOD;
			dp[i][2]=(dp[i-1][0]*cnt[2]%MOD+dp[i-1][1]*cnt[1]%MOD+dp[i-1][2]*cnt[0]%MOD)%MOD;
		}
		printf("%lld",dp[n][0]);
		return 0;
	}
}
int main()
{
	return Dango::work();
}
```

时间复杂度：$O(n)$

空间复杂度：$O(n)$

#### 注：至此你已经可以AC此题，但我们仍将继续优化。

## 做法四

我们仔细看了看做法三里的$dp$转移方程，发现$dp[i]$只与$dp[i-1]$有关，我们可以直接将$dp[i][j]$滚存成$dp[0/1][j]$。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
namespace Dango
{
	const int MAXN=200005,MOD=1000000007;
	int n,l,r,cnt[3];
	long long dp[2][3];
	long long ans;
	int read()
	{
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
		while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
		return f?-x:x;
	}
	int work()
	{
		n=read();l=read();r=read();
		cnt[0]=(r+3)/3-(l+2)/3;
		cnt[1]=(r+2)/3-(l+1)/3;
		cnt[2]=(r+1)/3-l/3;
		dp[0][0]=1;
		for(int i=1;i<=n;i++)
		{
			dp[i&1][0]=(dp[(i&1)^1][0]*cnt[0]%MOD+dp[(i&1)^1][1]*cnt[2]%MOD+dp[(i&1)^1][2]*cnt[1]%MOD)%MOD;
			dp[i&1][1]=(dp[(i&1)^1][0]*cnt[1]%MOD+dp[(i&1)^1][1]*cnt[0]%MOD+dp[(i&1)^1][2]*cnt[2]%MOD)%MOD;
			dp[i&1][2]=(dp[(i&1)^1][0]*cnt[2]%MOD+dp[(i&1)^1][1]*cnt[1]%MOD+dp[(i&1)^1][2]*cnt[0]%MOD)%MOD;
		}
		printf("%lld",dp[n&1][0]);
		return 0;
	}
}
int main()
{
	return Dango::work();
}
```

时间复杂度：$O(n)$

空间复杂度：$O(1)$

## 做法五

过了几分钟我们发现，$dp$转移方程里$cnt$的值不变，我们可以考虑矩阵快速幂。我们可以构造出：

$$\left[\begin{matrix}dp[i-1][0] & dp[i-1][1] & dp[i-1][2]\end{matrix} \right] \times \left[\begin{matrix}cnt[0] & cnt[1] & cnt[2] \\ cnt[2] & cnt[0] & cnt[1]\\ cnt[1] & cnt[2] & cnt[0] \end{matrix}\right]=\left[\begin{matrix}dp[i][0] & dp[i][1] & dp[i][2]\end{matrix} \right]$$

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
namespace Dango
{
	const int MOD=1000000007;
	struct matrix
	{
		int x,y;
		long long num[3][3];
		matrix operator * (const matrix b)const
		{
			matrix res;
			memset(res.num,0,sizeof(res.num));
			res.x=x;res.y=b.y;
			for(int k=0;k<y;k++)
				for(int i=0;i<x;i++)
					for(int j=0;j<b.y;j++)
						res.num[i][j]=(res.num[i][j]+num[i][k]*b.num[k][j]%MOD)%MOD;
			return res;
		}
	}res,ans;
	int n,l,r;
	int read()
	{
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
		while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
		return f?-x:x;
	}
	matrix pow_(matrix a,long long b)
	{
		matrix res;
		memset(res.num,0,sizeof(res.num));
		res.x=res.y=a.x;
		for(int i=0;i<res.x;i++)
			res.num[i][i]=1;
		while(b)
		{
			if(b&1)res=res*a;
			a=a*a;
			b>>=1;
		}
		return res;
	}
	int work()
	{
		n=read();l=read();r=read();
		res.x=res.y=3;
		res.num[0][0]=res.num[1][1]=res.num[2][2]=(r+3)/3-(l+2)/3;
		res.num[0][1]=res.num[1][2]=res.num[2][0]=(r+2)/3-(l+1)/3;
		res.num[0][2]=res.num[1][0]=res.num[2][1]=(r+1)/3-l/3;
		ans.x=1;ans.y=3;
		ans.num[0][0]=1;
		ans=ans*pow_(res,n);
		printf("%lld",ans.num[0][0]);
		return 0;
	}
}
int main()
{
	return Dango::work();
}
```

时间复杂度：$O(\log n)$

空间复杂度：$O(1)$

### 由于本人水平有限，只能把复杂度优化到这里。欢迎各位大佬提出更优秀的做法。

---

## 作者：ModestCoder_ (赞：8)

哎呦我去，这怕是要笑死我这题目

加起来是3的倍数？一眼水题啊

先算出$[l,r]$中膜3分别为0、1、2的数的个数

然后进行一个DP操作

$dp[i][j]$表示做了i个数，i个数的和膜3为j，的方案数

使用刷表法转移一下就好了

又发现$i$这一维顺手滚动掉，空间复杂度不见了蛤蛤蛤，笑死我了

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 200010
#define LL long long
#define qy 1000000007
using namespace std;
LL n, l, r, num[3], dp[2][3];

int main(){
	scanf("%d%lld%lld", &n, &l, &r);
	num[0] = r / 3 - (l - 1) / 3;
	num[1] = (r + 2) / 3 - (l + 1) / 3;
	num[2] = (r + 1) / 3 - l / 3;
	dp[0][0] = 1;
	for (int i = 1; i <= n; ++i){
		int now = i & 1, pre = now ^ 1;
		memset(dp[now], 0, sizeof(dp[now]));
		for (int j = 0; j <= 2; ++j)
		for (int k = 0; k <= 2; ++k)
			(dp[now][(j + k) % 3] += dp[pre][j] * num[k] % qy) %= qy;	
	}
	printf("%lld\n", dp[n & 1][0]);
	return 0;
}
```


---

## 作者：Sai0511 (赞：6)

简单$\text{dp}$               
我们设$\text{dp[i][j]}$表示前$\text{i}$位除以$\text{3}$的余数为$\text{j}$的个数，那么可以明显的推出状态转移方程           
$\text{dp[i][0]=dp[i-1][1]*mod[2]+dp[i-1][2]*mod[1]+dp[i-1][0]*mod[0]}$         
$\text{dp[i][1]=dp[i-1][0]*mod[1]+dp[i-1][1]*mod[0]+dp[i-1][2]*mod[2]}$         
$\text{dp[i][2]=dp[i-1][1]*mod[1]+dp[i-1][2]*mod[0]+dp[i-1][0]*mod[2]}$         
其中$\text{mod[i]}$表示$\text{l}\sim\text{r}$除以$\text{3}$的余数为$\text{i}$的个数，不难发现这个是可以$\text{O(1)}$算的            
接着我们就可以确定边界条件:         
$\text{dp[1][i]=mod[i]}$                 
### My Code：
```cpp
#include <bits/stdc++.h>
#define int long long
const int MAXN = 1e5 * 2; 
const int P = 1e9 + 7;
using namespace std;
int n,m,i,j,k,l,r;
int dp[MAXN][3],mod[3];
signed main() {
    scanf("%d %d %d",&n,&l,&r);
    mod[0] = dp[1][0] = r / 3 - (l - 1) / 3;
    mod[1] = dp[1][1] = (r + 2) / 3 - (l + 1) / 3;
    mod[2] = dp[1][2] = (r + 1) / 3 - l / 3;
    for(int i = 2;i <= n;i++) {
        dp[i][0] = (dp[i - 1][0] * mod[0] + dp[i - 1][1] * mod[2] + dp[i - 1][2] * mod[1]) % P;
        dp[i][1] = (dp[i - 1][0] * mod[1] + dp[i - 1][1] * mod[0] + dp[i - 1][2] * mod[2]) % P;
        dp[i][2] = (dp[i - 1][0] * mod[2] + dp[i - 1][1] * mod[1] + dp[i - 1][2] * mod[0]) % P;
    }
    printf("%d\n",dp[n][0]);
    return 0;
}
```




---

## 作者：Zechariah (赞：3)

一个很基础的dp，关键在于预处理  
首先状态很好想，dp[n][k]表示前n个数加起来%3是k的方案数，转移方程也很好推  
dp[n][0]=dp[n-1][0]\*yu[0]+dp[n-1][1]\*yu[2]+dp[n-1][2]\*yu[1]  
dp[n][1]=dp[n-1][0]\*yu[1]+dp[n-1][1]\*yu[0]+dp[n-1][2]\*yu[2]  
dp[n][2]=dp[n-1][0]\*yu[2]+dp[n-1][1]\*yu[1]+dp[n-1][2]\*yu[0]  
其中yu[i]表示区间[l,r]内%3是i的数的个数  
可以看出这题关键在于怎么预处理yu[]  
首先我们很容易推出[l,r]内整除3的数的个数应该是⌊r/3⌋-⌊(l-1)/3⌋，这有点类似于分块思想  
再考虑余数是1和2的，我们发现可以把余数是1 2的转成余数是0来做，只需把l和r同时+2或+1（这里不能是-1和-2！因为1<=l,r，如果l取1那么1-2就成-1了，-1/3并不等于⌊-1/3⌋）就和上面整除一样做了  
也就是说  
yu[0]=r/3-(l-1)/3  
yu[1]=(r+2)/3-(l+1)/3
yu[2]=(r+1)/3-l/3  
然后按上面的转移方程递推就行了，边界情况  
dp[1][k]=yu[k]
```cpp
#include <bits/stdc++.h>
#define jh(x,y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
    inl ll read()
    {
        rg ll num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg long long x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
ll f[N][3], yu[3];

int main(void)
{
    rg int n = fast_IO::read(), l = fast_IO::read(), r = fast_IO::read();
    yu[0] = r / 3 - (l - 1) / 3;
    yu[1] = (r + 2) / 3 - (l + 1) / 3;
    yu[2] = (r + 1) / 3 - l / 3;
    f[1][0] = yu[0]; f[1][1] = yu[1]; f[1][2] = yu[2];
    for (rg int i = 2; i <= n; ++i)
    {
        f[i][0] = (f[i - 1][0] * yu[0] % mod + f[i - 1][1] * yu[2] % mod + f[i - 1][2] * yu[1] % mod) % mod;
        f[i][1] = (f[i - 1][0] * yu[1] % mod + f[i - 1][1] * yu[0] % mod + f[i - 1][2] * yu[2] % mod) % mod;
        f[i][2] = (f[i - 1][0] * yu[2] % mod + f[i - 1][1] * yu[1] % mod + f[i - 1][2] * yu[0] % mod) % mod;
    }
    fast_IO::write(f[n][0]);
    return 0;
}

```

---

## 作者：hsfzLZH1 (赞：1)

## 题目大意

有一个长度为 $n$ 的数列 $a_i$ ，其满足如下性质：

1. 数列中的每一个元素都在区间 $[l,r]$ 中；

2. 所有 $a_i$ 的和是 $3$ 的倍数。

给出 $n,l,r$ ，求可能的 $a_i$ 的方案数，答案取模 $10^9+7$ 。

$1\le n\le 2\times 10^5,1\le l\le r\le 10^9$

## 解题思路

DP，记 $f[i][j]$ 表示前 $i$ 个数，总和模 $3$ 余 $j$ 的方案数。

写出状态转移方程 $f[i][j]=\sum_{k=l}^r f[i-1][(j-k)~mod~3]$ 。

我们发现，这样计算的时间复杂度是 $O(n(r-l))$ 的，显然超时。

观察到无论 $k$ 是多少，其都相当于在模 $3$ 意义下同余的数，那么我们只用预处理出 $[l,r]$ 中模 $3$ 余 $i$ 的个数，记为 $r[i]$ ，状态转移方程改为

$f[i][j]=\sum_{k=0}^2 f[i-1][(j-k)~mod~3]\times r[k]$ 

即可。时间复杂度 $O(n)$ ，空间复杂度 $O(n)$ ，可以用滚动数组法优化到 $O(1)$ 。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=200010;
typedef long long ll;
const ll mod=1000000007;
ll n,l,r,f[maxn][3],a[3];
int main()
{
	scanf("%lld%lld%lld",&n,&l,&r);
	a[0]=r/3-(l-1)/3;
	a[1]=(r+2)/3-(l+1)/3;
	a[2]=(r+1)/3-l/3;
	//printf("%d %d %d\n",a[0],a[1],a[2]);
	f[0][0]=1ll;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<3;j++)for(int k=0;k<3;k++)
		f[i][(j+k)%3]=(f[i][(j+k)%3]+f[i-1][j]*a[k]%mod)%mod;
	}
	/*
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<3;j++)printf("%d ",f[i][j]);
		printf("\n");
	}
	*/
	printf("%lld\n",f[n][0]);
	return 0; 
}
```

---

## 作者：Juanzhang (赞：1)

$dp$，令 $f_{i,j}$ 表示截止第 $j$ 位，整个序列和模 $3$ 的值为 $i$ 的方案数

首先列出状态转移方程，令 $s_0,s_1,s_2$ 表示值域区间 $[l,r]$ 中模 $3$ 余 $0,1,2$ 的数的个数，则 $$f_{i,j}=s_i\times f_{0,j-1}+s_{(i-1)\bmod3}\times f_{1,j-1}+s_{(i-2)\bmod3}\times f_{2,j-1}\pmod {10^9+7}$$

最后答案即为 $f_{0,n}$

代码

``` cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 2e5 + 10, P = 1e9 + 7;
int n, lef, rig, s[3]; ll f[3][maxn];

int main() {
	scanf("%d %d %d", &n, &lef, &rig);
	s[0] = rig / 3 - (lef - 1) / 3;
	s[1] = (rig + 1) / 3 - lef / 3;
	s[2] = (rig + 2) / 3 - (lef + 1) / 3;
	f[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 3; j++) {
			f[j][i] = (s[j] * f[0][i - 1] + s[(j + 2) % 3] * f[1][i - 1] + s[(j + 1) % 3] * f[2][i - 1]) % P;
		}
	}
	printf("%I64d", f[0][n]);
	return 0;
}
```

---

## 作者：sun_of_Ice (赞：1)

题意：
一个整数数组，满足：
 1. 长度为$n$
 2. 所有元素都在$[l, r]$范围内
 3. 所有元素的和能被3整除
给出$n, l, r (1 \leq n \leq 2\cdot10^5,1 \leq l \leq r \leq 10^9)$
请找出符合条件的数组的个数，答案对 $10^9 + 7$取模


首先我们要处理出$[l, r]$中对3取模得结果分别为0，1，2的数的个数，在一个合乎要求的数组中，结果为1和2的数的个数必然一样，由此就可以很方便地得到所有可能的组合的个数。但新的问题来了，由于可以选用相同的数，求出这些组合的排列数几乎是一个不可能完成的任务（对我这种蒟蒻来说）。

换一种思路，我们一个数一个数地添，并把所有可能的情况都考虑进去：

设$dp[i][j]$表示有$i$个数，且它们的和对3取模结果为$j$的数组个数，数组$num[i]$中记录了$[l, r]$中对3取模得结果为$i$的数的个数，显然$dp[1][j] = num[j]$，随后，向已有的数组的尾部添加新的数字，例如：
$$dp[i][0] = dp[i - 1][0] \cdot num[0] + dp[i - 1][1] \cdot num[2]  + dp[i - 1][2] \cdot num[1]$$
$dp[i][1]$和$dp[i][2]$的情况同理，递推到$n$，$dp[n][0]$就是我们要的答案。

为什么是添加到尾部？不能插入到某个数字前吗？这样做会不会漏情况？
实际上，插入到某个数字之前会带来重复（会有另一个数被顶到尾部），举个例子：现在前$i - 1$个数的和对3取模结果为1，要添加一个结果为2的数，即$dp[i - 1][1] \cdot num[2]$，如果把它插入到前面，使一个对3取模结果为1的数被顶到了前面的话，显然就与$dp[i - 1][2] \cdot num[1]$的情况重复了，另外两种情况同理。

附关键部分代码，欢迎纠错。

    ···c++
    const int mod = 1e9 + 7;
    const int maxn = 2e5 + 5;
    ll dp[maxn][3];//有i个数，且它们的和对3取模结果为j的数组个数
    int main()
    {
        //num[i]记录了对3取模结果为i的数的个数
        dp[1][0] = num[0], dp[1][1] = num[1], dp[1][2] = num[2];
        for(int i = 2; i <= n; i++)
        {
            dp[i][0] = (dp[i - 1][0] * num[0]) % mod + (dp[i - 1][1] * num[2]) % mod + (dp[i - 1][2] * num[1]) % mod;
            dp[i][0] %= mod;
            dp[i][1] = (dp[i - 1][0] * num[1]) % mod + (dp[i - 1][1] * num[0]) % mod + (dp[i - 1][2] * num[2]) % mod;
            dp[i][1] %= mod;
            dp[i][2] = (dp[i - 1][0] * num[2]) % mod + (dp[i - 1][1] * num[1]) % mod + (dp[i - 1][2] * num[0]) % mod;
            dp[i][2] %= mod;
        }
        cout << dp[n][0] << endl;
    }


---

## 作者：Parabola (赞：1)

所以我的推法可能与大家微微有点不一样

这题很套路，直接递推

写出式子来发现你需要一个东西

$c_i$代表$∑_{k = l}^{r}[k\ mod\ 3 ==\ i]$

然后这个东西怎么求呢


不妨我们先来写个函数，目的是求$[l,r]$中与$l$对三取模同余的数的个数

即求所有满足$l + 3k <= r \ (k ∈ N)$的$k$

那就是$3k <= r - l \ (k ∈ N)$

然后3除过去，是不是很简单

考虑到$l\ ,\ l+1 ,\ l + 2$对三取模一定不同余。然后直接求就好了。

对了我觉得各位自觉压空间的说，要不然出题人想卡其实随便卡。这样可以养成好习惯。

------------


### Code :
```
#include<iostream>
#include<cstdio>
#define now (i & 1)
#define lst (now ^ 1)

using namespace std;

typedef long long ll;

int n , l , r;

const int Mod = 1e9 + 7;

ll c[3] , dp[2][3];

inline int cnt(int a , int b) {
	if(a > b) return 0;
	return (b - a) / 3 + 1;
}

int main() {
	cin >> n >> l >> r;
	c[l % 3] = cnt(l++ , r);
	c[l % 3] = cnt(l++ , r);
	c[l % 3] = cnt(l , r);
	dp[0][0] = 1;
	for(int i = 1 ; i <= n ; ++i) {
		for(int k = 0 ; k <= 2 ; ++k) dp[now][k] = 0;
		for(int k = 0 ; k <= 2 ; ++k)
			for(int k2 = 0 ; k2 <= 2 ; ++k2) 
				dp[now][(k + k2) % 3] += c[k] * dp[lst][k2] , dp[now][(k + k2) % 3] %= Mod;
	}
	cout << dp[n & 1][0] << endl;
	return 0;
}
```

---

## 作者：Not_defined (赞：0)

题目大意：求出存在多少个数列中使得数列求和为 $3$ 的倍数，答案对 $10^9+7$ 取模。

这题是一个很明显的计数 DP 题。

## 预处理
任何数 $ \bmod\ 3$ 只有 $0,1,2$ 三种情况，所以我们不妨先算出区间 $[l , r]$ 分别 $\bmod\ 3=1,2,3$ 的数量。

**我们容易得到**

$num_{0}=dp_{1}^{0}=r \div 3-(l-1) \div 3$

$num_{1}=dp_{1}^{1}=(r+2) \div 3-(l+1) \div 3$

$num_{2}=dp_{1}^{2}=(r+1) \div 3-l \div 3$

## 状态设计
$dp_{i}^{j}$ 表示前 $i$ 个数之和 $\bmod\ 3$ 余数为  $j$ 的个数。
## 状态转移方程
$dp_{i}^{0}=dp_{i-1}^{0}\times num_{0}+dp_{i-1}^{1}\times num_{2}+dp_{i-1}^{2} \times num_{1}$

$dp_{i}^{1}=dp_{i-1}^{0}\times num_{1}+dp_{i-1}^{1}\times num_{0}+dp_{i-1}^{2} \times num_{2}$

$dp_{i}^{2}=dp_{i-1}^{0}\times num_{2}+dp_{i-1}^{1}\times num_{1}+dp_{i-1}^{2} \times num_{0}$
### 简单解释一下
$0\equiv0+0\equiv1+2\equiv2+1\pmod3$

$1\equiv0+1\equiv1+0\equiv2+2\pmod3$

$2\equiv0+2\equiv1+1\equiv2+0\pmod3$


### My code
```c
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,mod=1e9+7;
int n,l,r,num[3],dp[N][3];
signed main()
{
	cin>>n>>l>>r;
	num[0]=dp[1][0]=r/3-(l-1)/3;
	num[1]=dp[1][1]=(r+2)/3-(l+1)/3;
	num[2]=dp[1][2]=(r+1)/3-l/3;
	//dp[1][i]=num[i]
	for(int i=2;i<=n;i++)
	{
		dp[i][0]=(dp[i-1][0]*num[0]+dp[i-1][1]*num[2]+dp[i-1][2]*num[1])%mod;
		dp[i][1]=(dp[i-1][0]*num[1]+dp[i-1][1]*num[0]+dp[i-1][2]*num[2])%mod;
		dp[i][2]=(dp[i-1][0]*num[2]+dp[i-1][1]*num[1]+dp[i-1][2]*num[0])%mod;
	}
	printf("%lld",dp[n][0]);
	return 0;
} 
```


---

## 作者：happybob (赞：0)

较为基础的 DP。

考虑 $dp_{i,j}$ 表示前 $i$ 个数中和除 $3$ 余数为 $j$ 的方案数，其中 $j \in \{0, 1, 2\}$。

定义 $f(x)$ 表示 $\sum \limits_{i=l}^r [i \equiv x \pmod 3]$，即 $l$ 至 $r$ 中有多少个数取余 $3$ 余数为 $x$。

显然有转移方程 $dp_{i,j} = \sum_{k=0}^2 dp_{i-1, k} \times f((j+3-k) \bmod 3)$，其中 $\bmod$ 表示取余的结果。

时间复杂度 $O(n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

const int N = 2e5 + 5;
const long long MOD = 1e9 + 7;

long long l, r, dp[N][3];
int n;

inline long long calc(long long x)
{
	long long ll = l, rr = r;
	if (r - l < 3)
	{
		int cnt = 0;
		for (int i = l; i <= r; i++)
		{
			cnt += (i % 3 == x);
		}
		return cnt * 1ll;
	}
	while (rr % 3 != x) rr--;
	while (ll % 3 != x) ll++;
	return (rr / 3 - ll / 3 + 1) % MOD;
}

int main()
{
	scanf("%d%lld%lld", &n, &l, &r);
	long long x = calc(0), y = calc(1), z = calc(2);
	//printf("%lld %lld %lld\n", calc(0), calc(1), calc(2));
	dp[1][0] = x;
	dp[1][1] = y;
	dp[1][2] = z;
	for (int i = 2; i <= n; i++)
	{
		dp[i][0] = (dp[i - 1][0] * x % MOD + dp[i - 1][1] * z % MOD + dp[i - 1][2] * y % MOD) % MOD;
		dp[i][1] = (dp[i - 1][0] * y % MOD + dp[i - 1][1] * x % MOD + dp[i - 1][2] * z % MOD) % MOD;
		dp[i][2] = (dp[i - 1][0] * z % MOD + dp[i - 1][1] * y % MOD + dp[i - 1][2] * x % MOD) % MOD;
	}
	printf("%lld\n", dp[n][0]);
	return 0;
}
```


---

## 作者：lzyqwq (赞：0)

## 思路

这题是个 $\text{dp}$ 啊，我们用 $f[i][j]$ 表示前 $i$ 个数的和除以 $3$ 余数为 $j$ 的方案数。则状态转移方程为 $f[i][j]+=f[i-1][(j-k+3)\%3]\times a[k]$，其中 $k$ 表示第 $i$ 个数除以 $3$ 的余数，$a[k]$ 表示在 $[L,R]$ 中除以 $3$ 余数为 $k$ 的数的个数。

那么 $a[k]$ 怎么求呢？这就是数学的知识了。请看：

$\because L\leqslant 3x+k\leqslant R$

$\therefore\lceil \frac{L-k}{3}\rceil\leqslant x\leqslant \lfloor\frac{R-k}{3}\rfloor$

推得 $a[k]=\lceil\frac{L-k}{p}\rceil$ 至 $\space\lfloor\frac{R-k}{p}\rfloor$ 之间的自然数个数，即 $a[k]=\lfloor\frac{R-k}{p}\rfloor-\lceil\frac{L-k}{p}\rceil+1$。注意处理 $\lceil\frac{L-k}{p}\rceil$ 的时候要考虑到边界条件，如果这个值小于 $0$ 了，则它就是 $0$。向上取整由于会有精度问题建议自己手写。

最后答案就是 $f[n][0]$。时间复杂度为 $Θ(n)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int a[3],n,p,L,R;
long long f[250005][3];
int main()
{
	scanf("%d%d%d",&n,&L,&R);
	for(int i=0,x,y;i<3;i++)
	{
		x=L-i<0?0:!((L-i)%3)?(L-i)/3:(L-i)/3+1;//向上取整、向下取整如果用库函数会存在精度问题，所以这里手写
		y=(R-i)/3;
		a[i]=x<=y&&R>=i?y-x+1:0;//如果左端点大于右端点，说明不存在这个情况
	}
	f[0][0]=1;//前0个数啥也没有，就相当于和为0，即余数为0
	for(int i=1;i<=n;i++)
		for(int j=0;j<3;j++)//注意余数的范围
			for(int k=0;k<3;k++)
				f[i][j]+=f[i-1][(j-k+3)%3]*a[k],f[i][j]%=mod;//(j-k+3)%3是避免出现负数的请况
	printf("%lld\n",f[n][0]);
	return 0;
} 
```


---

## 作者：_cmh (赞：0)

一道清新的 DP 题。

## $\texttt{Desription}$

给定 $n,l,r$ ，求长度为 $n$ 的一个序列，使得序列中的每一个数在 $[l,r]$ 区间中，并且和为 $3$ 的倍数。

## $\texttt{Solution}$

先预处理出 $tot_i$，表示在 $[l,r]$ 区间中除以 $3$ 余 $i$ 的数的个数。众所周知，计算区间内能整除 $n$ 的方法为：

$$tot=r\div n-(l-1)\div n$$

除以 $n$ 余 $m$ 的公式为：

$$tot=(r+n-m)\div n-(l-1+n-m)\div n$$

代入本题中，即可计算出 $tot_i$ 的值。

求完了 $tot_i$ 的值，接下来应该推状态转移方程了。

我们令 $dp_{i,j}$ 表示序列中前 $i$ 个数的和除以 $3$ 余 $j$ 的方案数，则可以推出 $dp_{i,0}$ 为：

$$dp_{i,0}=dp_{i-1,0}\times tot_0+dp_{i-1,1}\times tot_2+dp_{i-1,2}\times tot_1$$

即，想让前 $i$ 项的和能够整除 $3$，前 $i-1$ 项的和若除以 $3$ 余 $0/1/2$，那么新加入的数必须能够除以 $3$ 余 $0/2/1$ 才可以凑出余数为 $0$ 的方案。

以此类推，可以推出完整的状态转移方程为：

$$dp_{i,0}=dp_{i-1,0}\times tot_0+dp_{i-1,1}\times tot_2+dp_{i-1,2}\times tot_1$$

$$dp_{i,1}=dp_{i-1,0}\times tot_1+dp_{i-1,1}\times tot_0+dp_{i-1,2}\times tot_2$$

$$dp_{i,2}=dp_{i-1,0}\times tot_2+dp_{i-1,1}\times tot_1+dp_{i-1,2}\times tot_0$$

最后输出 $dp_{n,0}$ 就是答案。

你以为这就结束了？并没有！

我们发现 dp 的第一项为 $i \operatorname{or} i-1$ ，所以我们可以用滚动数组进行优化。方程：

$$dp_{i\bmod 2,0}=dp_{(i+1)\bmod2,0}\times tot_0+dp_{(i+1)\bmod2,1}\times tot_2+dp_{(i+1)\bmod2,2}\times tot_1$$

$$dp_{i\bmod 2,1}=dp_{(i+1)\bmod2,0}\times tot_1+dp_{(i+1)\bmod2,1}\times tot_0+dp_{(i+1)\bmod2,2}\times tot_2$$

$$dp_{i\bmod 2,2}=dp_{(i+1)\bmod2,0}\times tot_2+dp_{(i+1)\bmod2,1}\times tot_1+dp_{(i+1)\bmod2,2}\times tot_0$$

最后注意每一项对 $10^9+7$ 取模即可。

**记得开 `long long` ！！！**

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
int tot[3];
long long dp[2][4];
int main(){
	int n,l,r;
	cin>>n>>l>>r;
	dp[1][0]=tot[0]=r/3-(l-1)/3;
	dp[1][1]=tot[1]=(r+2)/3-(l+1)/3;
	dp[1][2]=tot[2]=(r+1)/3-l/3;
	for(int i=2;i<=n;i++){
		dp[i%2][0]=(dp[(i+1)%2][0]*tot[0]+dp[(i+1)%2][1]*tot[2]+dp[(i+1)%2][2]*tot[1])%mod;
		dp[i%2][1]=(dp[(i+1)%2][0]*tot[1]+dp[(i+1)%2][1]*tot[0]+dp[(i+1)%2][2]*tot[2])%mod;
		dp[i%2][2]=(dp[(i+1)%2][0]*tot[2]+dp[(i+1)%2][1]*tot[1]+dp[(i+1)%2][2]*tot[0])%mod;
	}
	cout<<dp[n%2][0];
    return 0;
}
```

感谢观看。

---

## 作者：Christopher_Yan (赞：0)

[题目链接](https://codeforces.com/contest/1105/problem/C)

#### 解题思路
考场上把这个题当成计数题了，一直在想怎么去重，最后发现正解竟是DP。。。还是自己的DP功底太差了。

设状态$dp[i][j]$表示已经选了前i个数字，当前的和%3余j的方案数。数组$num[k]$为$l~r$内%3余k的数字的个数。

我觉得想到这里剩下的就很简单了，转移比较显然，别爆long long就好：
```cpp
dp[i][0] = (1ll * dp[i - 1][0] * num[0] + 1ll * dp[i - 1][1] * num[2] + 1ll * dp[i - 1][2] * num[1]) % M;
dp[i][1] = (1ll * dp[i - 1][0] * num[1] + 1ll * dp[i - 1][1] * num[0] + 1ll * dp[i - 1][2] * num[2]) % M;
dp[i][2] = (1ll * dp[i - 1][0] * num[2] + 1ll * dp[i - 1][1] * num[1] + 1ll * dp[i - 1][2] * num[0]) % M;
```
#### AC代码
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int M = 1e9 + 7;
const int N = 2e5 + 10;

int n, l, r, dp[N][3], num[3];

int main()
{
	dp[0][0] = 1;
	cin >> n >> l >> r;
    num[0] = r / 3 + 1;
    if (r - 1 >= 0) num[1] = (r - 1) / 3 + 1;
    if (r - 2 >= 0) num[2] = (r - 2) / 3 + 1;
    if (l - 1 >= 0) num[0] -= max((l - 1) / 3 + 1, 0);
    if (l - 2 >= 0) num[1] -= max((l - 2) / 3 + 1, 0);
    if (l - 3 >= 0) num[2] -= max((l - 3) / 3 + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
    	dp[i][0] = (1ll * dp[i - 1][0] * num[0] + 1ll * dp[i - 1][1] * num[2] + 1ll * dp[i - 1][2] * num[1]) % M;
    	dp[i][1] = (1ll * dp[i - 1][0] * num[1] + 1ll * dp[i - 1][1] * num[0] + 1ll * dp[i - 1][2] * num[2]) % M;
    	dp[i][2] = (1ll * dp[i - 1][0] * num[2] + 1ll * dp[i - 1][1] * num[1] + 1ll * dp[i - 1][2] * num[0]) % M;
    }
  	cout << dp[n][0];
  	return 0;
}
```

---

## 作者：C_S_X_ (赞：0)

dp[i][j] 其中 j=0/1/2

表示到了第i个数，前面所有数和模3的余数为j有多少种方案



转移方程

dp[i][1]=dp[i-1][0]*a[1]+dp[i-1][1]*a[0]+dp[i-1][2]*a[2];

dp[i][2]=dp[i-1][0]*a[2]+dp[i-1][1]*a[1]+dp[i-1][2]*a[0];

dp[i][0]=dp[i-1][0]*a[0]+dp[i-1][1]*a[2]+dp[i-1][2]*a[1];

```cpp
#include<bits/stdc++.h>
#define N 300000
#define MOD 1000000007
using namespace std;
long long n,l,r,a[3],dp[N][3];
long long find(long long m,long long r)
{
	long long t=m/3;
	m%=3;
	if (r&&m>=r) t++;
	return t;
}
int main()
{
	scanf("%lld%lld%lld",&n,&l,&r);
	a[0]=(find(r,0)-find(l-1,0))%MOD;
	a[1]=(find(r,1)-find(l-1,1))%MOD;
	a[2]=(find(r,2)-find(l-1,2))%MOD;
	dp[1][0]=a[0],dp[1][1]=a[1],dp[1][2]=a[2];
	for (long long i=2;i<=n;i++) 
	{
		dp[i][1]=((((dp[i-1][0]*a[1]%MOD)+(dp[i-1][1]*a[0]%MOD))%MOD)+(dp[i-1][2]*a[2]%MOD))%MOD;
		dp[i][2]=((((dp[i-1][0]*a[2]%MOD)+(dp[i-1][1]*a[1]%MOD))%MOD)+(dp[i-1][2]*a[0]%MOD))%MOD;
		dp[i][0]=((((dp[i-1][0]*a[0]%MOD)+(dp[i-1][1]*a[2]%MOD))%MOD)+(dp[i-1][2]*a[1]%MOD))%MOD;
	}
	printf("%lld\n",dp[n][0]);
	return 0;
}
```

---

## 作者：一扶苏一 (赞：0)

## Description

有一个长度为 $n$ 的序列，其中的数字都在 $[l,r]$ 之间，同时他们的和能被 $3$ 整除。给定 $n,l,r$，求满足要求的序列有多少种。答案对 $1e9 + 7$ 取模

## Input

一行三个整数 $n,l,r$

## Output

一行一个整数代表答案对 $1e9+7$ 取模的结果

## Hint

$1~\leq~n~\leq~2~\times~10^5,~~1~\leq~l~\leq~r~\leq~10^9$

## Solution

数数题，考虑DP。

我们设 $f_{i,j}$ 为前枚举到第 $i$ 个数字，前缀和模 $3$ 余 $j$ 的方案数。转移显然：

$$f_{i,(j + k) \% 3}~+=~f_{i - 1, j}~\times~cnt_k$$

其中 $i,j~\in~[0,3)~,~~cnt_x$ 代表 $[l,r]$ 中模 $3$ 余 $x$ 的数字个数。

我们考虑如何确定 $cnt$ 数组：

由于这个东西满足前缀相减特性，我们只需要求出对于一个数$n$， $[1,n]$ 中的的 $cnt$ 数组，然后将 $r$ 的答案减去 $l-1$ 的答案即可

首先显然余 $0,1,2$ 的情况都至少有 $\left\lfloor\frac{n}{3}\right\rfloor$ 个。考虑边界情况。从 $1$ 到 $n \bmod 3$ 都多出一个。多出的事实上是 $[3~\times~\left\lfloor\frac{n}{3}\right\rfloor~,~n]$ 中的贡献。

然后套路DP一下就好了

## Code

```cpp
#include <cstdio>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
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
	char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	char ch = IPT::GetChar(), lst = ' ';
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
	int top=0;
	do {OPT::buf[++top] = char(x % 10 + '0');} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 200010;
const int MOD = 1000000007;

int n, l, r;
ll frog[maxn][3], z[3], y[3], x[3];

void beginning();

int main() {
	freopen("1.in", "r", stdin);
	qr(n); qr(l); qr(r);
	beginning();
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				frog[i][(j + k) % 3] = (frog[i][(j + k) % 3] + frog[i - 1][j] * x[k] % MOD) % MOD;
			}
		}
	}
	qw(frog[n][0], '\n', true);
	return 0;
}

void beginning() {
	--l;
	for (int i = 0; i < 3; ++i) z[i] = r / 3;
	for (int j = 0; j < 3; ++j) y[j] = l / 3;
	for (int i = 1; i <= r % 3; ++i) ++z[i];
	for (int j = 1; j <= l % 3; ++j) ++y[j];
	for (int i = 0; i < 3; ++i) x[i] = z[i] - y[i];
	frog[0][0] = 1;
}
```



---

## 作者：fmj_123 (赞：0)


题意：从$l$到$r$中选$n$个数，允许相同。要使最终这$n$个数的和是$3$的倍数，求有多少个方案，答案$mod$ $10^9+7$。(若没有方案，输出$0$)

题解：

首先$1\le l\le r\le 10^9$，显然不能从$l$,$r$下手。我们可以从$3$思考一下，显然，求$n$个数的和为$3$的倍数，就是余数加起来为$3$的倍数。所以，对于一个方案，把里面的某一个数换成余数与其相同的数，方案仍然成立。

我们容易想到DP，设$f[i][j]$为到第$i$个数时，前$i$个数的和$mod$ $3$为$j$的方案数。转移这里就不说了，具体见代码。

```c++
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007;
int n,l,r;
long long mod0,mod1,mod2,f[200100][3];//记得开long long
int main()
{
	cin>>n>>l>>r;
	mod0=r/3-l/3;
	mod1=mod0;
	mod2=mod0;
	if (l%3==0) mod0++;
	if (l%3==2) mod1--;
	if (r%3==1) mod1++;
	if (r%3==2) mod1++,mod2++;//求出l到r中模3余数为0、1、2的数
	f[0][0]=1;
	for (int i=1;i<=n;i++)
	{
		f[i][0]=(f[i-1][0]*mod0)%mod+(f[i-1][1]*mod2)%mod+(f[i-1][2]*mod1)%mod;
		f[i][0]%=mod;
		f[i][1]=(f[i-1][1]*mod0)%mod+(f[i-1][2]*mod2)%mod+(f[i-1][0]*mod1)%mod;
		f[i][1]%=mod;
		f[i][2]=(f[i-1][0]*mod2)%mod+(f[i-1][1]*mod1)%mod+(f[i-1][2]*mod0)%mod;
		f[i][2]%=mod;
	}//DP，注意取模
	cout<<f[n][0]<<endl;
	return 0;
}
```



---

