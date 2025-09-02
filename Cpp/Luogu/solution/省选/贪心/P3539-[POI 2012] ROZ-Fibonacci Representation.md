# [POI 2012] ROZ-Fibonacci Representation

## 题目描述

**译自 POI 2012 Stage 2. Day 2「[Rozkład Fibonacciego](https://szkopul.edu.pl/problemset/problem/w1QbhPufazp-sH6X-u4pTnNu/site/?key=statement)」**

给定正整数 $k$，求用斐波那契数的和或差表示 $k$ 所需要的斐波那契数数量最小值，例如：
- $10=5+5$
- $19=21-2$
- $17=13+5-1$
- $1070=987+89-5-1$

## 样例 #1

### 输入

```
1
1070```

### 输出

```
4```

# 题解

## 作者：我好蒻呀 (赞：27)

> 给定正整数 $k$，求用斐波那契数的**和或差**表示 $k$ 所需要的斐波那契数数量最小值。
>
> $k \leq 4\times 10^7$
>
> 时空限制：$\texttt{1s/125MB}$

题解界面 LaTeX 渲染可能会有点问题，建议到博客中查看：[题解 P3539 【[POI2012]ROZ-Fibonacci Representation】](https://www.luogu.com.cn/blog/samxiang/solution-p3539)

这题的贪心做法是这样的：**每次找到一个离 $k$ 最近的斐波那契数 $F_i$，令 $k\leftarrow|k-F_i|$，重复若干次直到 $k=0$。（即每次令 $k \leftarrow \min|k-F_i|$）**

但是我在网上一直找不到比较好的证明，非常自闭QAQ。

首先有几个性质：

- 存在最优方案，不会选择重复的一项。

  **证明：** 因为我们有 $2F_i=F_{i+1}+F_{i-2}$。

- 存在最优方案，不会选择相邻的两项。

  **证明：** 通过讨论可以知道
  
  $+F_i+F_{i+1}=+F_{i+2}$
  
  $+F_i-F_{i+1}=-F_{i-1}$
  
  $-F_i+F_{i+1}=+F_{i-1}$
  
  $-F_i-F_{i+1}=-F_{i+2}$

- 若当前 $F_i \leq k \leq F_{i+1}$，那么存在最优方案，一定包含了 $F_i$ 或 $F_{i+1}$。

  **证明：** 反证法。假设不包含 $F_i$ 和 $F_{i+1}$。那么**根据不选相邻和重复的原则**，我们可以证明其他部分的斐波那契数通过加减一定无法凑到 $[F_i,F_{i+1}]$ 内的数。具体地，我们有 $F_{i-1}+F_{i-3}+\cdots<F_i$ 成立，这是因为 $F_1+F_3+\cdots +F_{2n-1}=F_{2n}-1$ 和 $F_2+F_4+\cdots +F_{2n}=F_{2n+1}-1$（为方便设 $F_1=1,F_2=2$）。

  这样一来，$F_1\sim F_{i-1}$ 的数里选出来的和 $S<F_i$。同样我们如果用比 $F_{i+1}$ 大的数拿去减，也会遇到这种的情况： $F_{i+2}-S>F_{i+1}$ ，并且因为不能选相邻的，$F_{i+4}-F_{i+2}>F_{i+3}$ 也是没用的。

  因此我们就证明了，存在最优方案，一定包含了 $F_i$ 或 $F_{i+1}$。

那么接下来，我们就得到了，若当前 $F_{i}\leq k \leq F_{i+1}$，我们一定要从 $F_i,F_{i+1}$ 中选一个。

接下来我们归纳证明，一定是选较近的那个斐波那契数：

- 显然对于满足 $k < F_3$ 的 $k$，结论成立。
- 假设对于满足 $k < F_i$ 的 $k$，结论是成立的，那么接下来考虑证明对于满足 $F_i\leq k<F_{i+1}$ 的 $k$，有结论成立。不妨假设 $k-F_i=a$，$F_{i+1}-k=b$，不失一般性地，设 $a<b$，对于 $a>b$ 同理。
- 接下来证明令 $k\leftarrow a$ 的策略不比 $k \leftarrow b$ 的策略劣。首先有 $a+b=F_{i+1}-F_{i}=F_{i-1}$。根据 $a<b$ 我们有 $b\in (\frac{F_{i-1}}2,F_{i-1}]$，并且因为 $F_{i-3}<\frac{F_{i-1}}{2}<F_{i-2}<F_{i-1}$，而 $\frac{F_{i-1}}2=\frac{F_{i-2}+F_{i-3}}2$，因此离 $b$ 最近的斐波那契数一定是 $F_{i-2},F_{i-1}$ 之一。
- 因为 $b \leq F_{i-1}<F_i$ 满足一定选离 $b$ 较近的斐波那契数，因此我们有 $b$ 的最优表示中一定有 $F_{i-2},F_{i-1}$ 之一。那么 $a=F_{i-1}-b$，所以 $a$ 可以由 $b$ 的表达转化过来，并且 $F_{i-1}$ 可以和 $b$ 的表示中的 $F_{i-2}$ 或是 $F_{i-1}$ 合并/抵消，因此 $a$ 均能得到一种不劣于 $b$ 的表达方式。

至此我们证明了贪心策略的正确性。

显然，$k$ 每次至少减少一半，所以答案是 $\mathcal O(\log k)$ 级别的，这也是时间复杂度的级别。

```cpp
#include <bits/stdc++.h>

typedef long long s64; 

const s64 lim = 4e17; 

int main()
{
	static s64 f[10001];
	
	int m = 2; 
	f[1] = 1, f[2] = 2; 
	while (f[m] <= lim)
	{
		++m; 
		f[m] = f[m - 2] + f[m - 1]; 
	}

	int orzczk; 
	std::cin >> orzczk; 
	while (orzczk--)
	{
		s64 n; 
		int res = 0; 
		std::cin >> n; 
		while (n)
		{
			++res; 
			int suf = std::upper_bound(f + 1, f + m + 1, n) - f; 
			n = std::min(f[suf] - n, n - f[suf - 1]); 
		}
		std::cout << res << '\n'; 
	}
	return 0; 
}
```

---

## 作者：浅色调 (赞：11)

### 思路：

　　首先由于斐波拉契数的前两项是$1,1$，所以易得对于任何整数必能写成多个斐波拉契数加减的形式。

　　对于一个数$x$，我们贪心找到与$x$差值最小的斐波拉契数，将新的$x$赋为差值，每次进行这个操作，统计次数，直到$x$为$0$为止，输出次数。

　　证明上述过程也很简单：由于我们知道任何整数必能写成多个斐波拉契数加减的形式，所以我们显然使$x$每次变得越小越好（即减的越多越好），因为每个斐波拉契数都等于前面两项的和，所以我们完全没必要将一步操作改为两步操作。

　　举个例子：当$n=8$，答案是$1$（即$8=8$，$8$为第6项），而我们不需要将前面的$3,5$什么的记录进去，因为这样会多$1$步操作。当$n=11$，答案是$2$（即$11=8+3$或$11=13-2$），显然不用将$8$拆为更小的斐波拉契数之和，也不用将$13$拆为更小的斐波拉契数之和，这样必然会徒增次数。

　　那么具体实现时，直接预处理斐波拉契数，然后对于每次询问，二分出第一个大于等于该值的位置$p$，然后第一个小于该值的值位置$p-1$，则$x=min(f[p]-x,x-f[p-1])$。
  
   欢迎来踩博客（转载请注明此出处谢谢！）[five20](http://www.cnblogs.com/five20/p/8810419.html)

### 代码：
```cpp
#include<bits/stdc++.h>
#define il inline
#define ll long long
using namespace std;
ll f[100],n,t;
il void getans(ll x){
    ll p=lower_bound(f+1,f+93,x)-f,q=p-1,tot=0;
    while(x){
        x=min(f[p]-x,x-f[q]);
        p=lower_bound(f+1,f+93,x)-f;
        q=p-1;
        tot++;
    }
    cout<<tot<<endl;
}
int main()
{
    ios::sync_with_stdio(0);
    cin>>n;
    f[1]=f[2]=1;
    for(int i=3;i<=100;i++)f[i]=f[i-1]+f[i-2];
    while(n--){
        cin>>t;
        getans(t);
    }
    return 0;
}
```

---

## 作者：Nemlit (赞：4)

# ~~论map（记忆化搜索）的强大~~
![luogu](https://cdn.luogu.com.cn/upload/pic/25311.png)

 70分（没开long long）
 
 0分（注释忘记删掉了）
 
 90分（被卡了16ms）
 
 90分（拼命卡小常数比如  /2 -> >>1, scanf -> qread(), min(a+c,b+c ） -> min(a,b)+c ………………)
 
 结果一共卡了8ms
 
 正当我准备放弃此题时，我突然想到了什么，
 有十组数据，每一组之间都有大量重复计算，难道不可以用记忆化搜索吗？
 
 于是我看了下数据范围：K<1e17 
 (⊙o⊙)…
 
 于是我就开始用了map来进行记忆化搜索。
 
 虽然多了一个log的常数
 
 于是瞬间由 1052ms ->0ms
 
 
 此题的关键在于贪心策略：ans=min(cc[x-fab[t]],cc[fab[t+1]-x])+1
 
 “+1”是因为选了一个数，于是答案就要加一
 
 “t”的意思是斐波那契数列的第t项是比n小的最大fab
 
 所以“t+1”的意思就是fab比n大的最小整数
 
 我们不难发现找到了离n最近的两个数后，只要重新递归x-fab[t]和fab[t+1]-x即可
 
 这个贪心要怎么证明呢？
 
 因为斐波那契数列第n项是等于n-1项和n-2项之和，所以选择离目标数最近的数肯定比选择其他数要好（额，好像是废话）
 
 各位神老也可以用反证法来证明，即如果我们不选择离目标数最近的fab答案还会不会是最优解
 
 贴上AC代码（由于我太弱了，不会用STL二分，于是我写了一个手写二分来找到离目标数最近的fab[t]）：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
inline ll read(){
    register ll c = getchar(), x = 0;
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = getchar();
    return x;
}

ll n,fab[95];
map<ll,ll> cc;

inline ll check(ll t)
{
    int l=1,r=90;
    while(r-l>1)
    {
        int mid=(l+r)>>1;
        //cout<<mid<<' '<<l<<' '<<r<<endl;;
        if(fab[mid]<t)
        {
            l=mid;
        }
        else
        {
            r=mid;
        }
    }
    return l;
}//二分查找离目标数最近的fab[t]

inline int s(ll x)
{
    if(cc[x])
    {
        return cc[x];
    }
    if(x<=0)
    {
        return 0;
    }
    if(x==1)
    {
        return 1;
    }
    ll t=check(x);
    //cout<<"x = "<<x<<"  t = "<<t<<endl;
    cc[x-fab[t]]=s(x-fab[t]);
    cc[fab[t+1]-x]=s(fab[t+1]-x);
    return min(cc[x-fab[t]],cc[fab[t+1]-x])+1;
}//递归函数找出答案

int main()
{
    int T=read();
    fab[1]=fab[2]=1;
    for(register int i=3;i<91;i++)
    {
    	fab[i]=fab[i-1]+fab[i-2];
    	//cout<<fab[i]<<' ';
    }//O(n)预处理出fab
    //cout<<check(4);
    while(T--)
    {
    	n=read();
    	ll t=check(n);
        //cout<<t<<endl;
        printf("%d\n",min(s(n-fab[t]),s(fab[t+1]-n))+1);
    }
    return 0;
}
```
# 复杂度………………大概是O（T n log log n）吧

---

## 作者：StarPatrick (赞：3)

这题本蒟蒻我想了很久。

一开始看到这道题，首先想到的是完全背包，但是由于 $x$ 的值比较大，所以只能水 40 分。

但又一看样例，自己再出一点数据，可以发现分成的数字有一个一定非常接近原来数字，不然会需要更多的数字组成，于是我们就可以递归搜索。

并且，斐波那契数列的增长速度是很快的，所以这题只需要 100 项左右就可以了。

至于到底是加还是减，都试一遍就行了。

代码：
```cpp
#include <iostream>
#include <cstring>
using namespace std;
#define int long long
int n, q, fib[105], ans;
void dfs(int u, int o)
{
	if (o>=ans)
	{
		return ;
	}
	if (u==0)
	{
		ans = o;
		return ;
	}
	for (int p=1;p<=90;p++)
	{
		if (fib[p]>=u)
		{
			dfs(u-fib[p-1], o+1);
			dfs(fib[p]-u, o+1);
			break;
		}
	}
	return ;
}
signed main()
{
	cin>>q;
	fib[0] = 1;
	fib[1] = 1;
	fib[2] = 1;
	for (int p=3;p<=90;p++)
	{
		fib[p] = fib[p-1]+fib[p-2];
	}
	for (int p=1;p<=q;p++)
	{
		ans = 2147483647;
		cin>>n;
		dfs(n, 0);
		cout<<ans<<"\n";
	}
	return 0;
}
```


---

## 作者：Chevalier (赞：2)

		补充一个证明
        （证明中会有一些特例，在这里我们只研究一般情况）

		在这道题中用到的贪心策略实际可以分为两个部分：
 1. 若要表示一个数（比如62），我们一定会用到第一个比它大的斐波那契数（89）（以下简称斐数）和第一个比他小的斐数（55）（为方便理解，下面就用这三个数举例了）。

 2. 设目标数为n，较大斐数为x，较小斐数为y，表示（y-n）与（n-x）中较大者所用的项数一定大于等于表示较小者所用的项数。

		第一个贪心比较显然，其他题解中也有提及，在这里便不再证明并默认其正确。
        



------------


        
下面进行第二个贪心的证明：
 

- 沿用上文对x、y的定义，根据斐数定义，设z=x-y（89-55=34），显然有z为斐数。

	问题即转化为“将一个斐数z切成两个部分，表示其较大的部分（89-62=27）（以下统称为较大数）所用项数一定大于等于表示较小的部分（62-55=7）（以下统称较小数）所用的项数”，易得：较大数+较小数=z。

下面进行分类讨论：

 		1.较大数与较小数中存在斐数 

 推论：若较大数是斐数，则较小数必然是斐数

 证明：若称一个数为较大数，则其必然大于z/2（34/2=17）。根据斐数定义，满足“>z/2且为斐数”的数有且只有第一个比z小的斐数（21），又根据斐数定义，较小数一定为第二个比z小的斐数（13）。

	证毕
        
		根据推论易得结论：存在斐数时贪心成立。
        
 		2.较大数与较小数中不存在斐数
 
 假设我们用···（这是一个多项式，共有n项）成功最小表示了较大数。（27=21+5+1），因为较大数+较小数=z，移项后我们可以用“z- ···”（共n+1项）表示较小数（7=34-21-5-1）。根据第一条贪心，表示较大数时我们一定会用到第一个比较大数大的斐数z（34），或者第一个比较大数小的斐数（21），无论是前者还是后者，都可以将z消掉（7=~~34-21~~13-5-1）使项数达到n。也就是说，无论用多少项最小表示较大数，我们都可以在同样的项数内将较小数表示。
 
### 综上所述，第二条贪心成立

###### 我太蒟了，如有误欢迎指正

---

## 作者：Energy_Making (赞：0)

## 1.前置知识
[贪心](https://oi-wiki.org/basic/greedy/)
## 2.解法
这道题要求最小次数，又因为操作之间是可以合并的。所以说我们要尽量合并，那么很自然我们就想到了贪心。具体做法就是每次都二分找出与 $|x|$ 相差最小的斐波那契数，让 $x$ 加或减掉这个数，且使 $x$ 更接近0即可。

## 3.代码
```cpp
#include<stdio.h>
#include<algorithm>
#define ll long long
using namespace std;
int T;
ll n;
ll feb[105];
int get(ll x)
{
	int ans=0;
	int a,b;
	a=lower_bound(feb+1,feb+93,x)-feb,b=a-1;//由于a是大于x的数字中最接近a的，所以b一定小于x。 
	while(x)
	{
		ans++;
		x=min(feb[a]-x,x-feb[b]);
		a=lower_bound(feb+1,feb+93,x)-feb;
		b=a-1;//显而易见的意思。 
	}
	return ans;
}
int main()
{
	scanf("%d",&T);
	feb[1]=1;
	for(int i=2;i<=92;i++)feb[i]=feb[i-1]+feb[i-2];//预处理 
	while(T--)
	{
		scanf("%lld",&n);
		printf("%d\n",get(n));
	}	
	return 0;
}
```


---

## 作者：傅思维666 (赞：0)

## 题解：

贪心。

由于斐波那契数列有项为1，所以显然任何一个数都可以表示为若干斐波那契数列中项目的和。

那么既然如此，我们每次在斐波那契数列里找一个和$x$最接近的数，然后在$x$上加上/减去这个数，依此迭代直到$x$为0，这样的操作方式一定是最优的。

证明已经说过了，因为任意一个数都可以表示为斐波那契和，所以加减后的数仍然满足这一性质，而我们相当于通过局部最优拼出了全局最优。

所以没什么难点：

```cpp
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
int p;
ll k;
ll fib[90];
void init()
{
    fib[1]=1;
    for(int i=2;i<=86;i++)
        fib[i]=fib[i-1]+fib[i-2];
}
void dfs(ll x)
{
    int p,q;
    int ans=0;
    while(x)
    {
        p=lower_bound(fib+1,fib+87,x)-fib;
        q=p-1;
        x=min(fib[p]-x,x-fib[q]);
        ans++;
    }
    printf("%d\n",ans);
}
int main()
{
    scanf("%d",&p);
    init();
    while(p--)
    {
        scanf("%lld",&k);
        dfs(k);
    }
    return 0;
}
```



---

## 作者：hanzhongtlx (赞：0)

如果  $k\leq 1e6$ 容易想到 dp，但是这个数据范围很不友好。  

考虑到斐波那契数列中一项是由其他多项加和得到的，所以优先选取大一些的一定不亏。  

于是找离本数最近的数，做差然后去绝对值（因为这个过程可以加减，正负不影响结果，全弄成正数），不断毕竟 $0$ 即可得到答案。  

我们用二分实现找离得最近的数的过程，最多迭代 $\mathcal O(\log n)$ 次，故最终复杂度为 $\mathcal O(p\log k\log \log k)$（斐波那契数列大概是 $\mathcal O(\log n)$ 的）。  

```
#include"iostream"
#include"cstdio"
#include"cmath"
using namespace std;

#define read(x) scanf("%d",&x)
#define ll long long 

ll f[100]; 
int p;
ll n;

int main()
{
	f[1]=f[2]=1ll;
	for(int i=3;i<=90;i++) f[i]=f[i-1]+f[i-2];
	read(p);
	while(p--)
	{
		scanf("%lld",&n);
		ll ans=0;
		while(n>0)
		{
			int l=2,r=90,mid;
			while(l<r)
			{
				mid=(l+r)>>1;
				if(f[mid]<=n) l=mid+1;
				else r=mid;
			}
			ll now1=abs(n-f[l]),now2=abs(n-f[l-1]);
			if(now1<now2) n=now1;
			else n=now2;
			ans++;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：EmpyreanCz (赞：0)

这道题本蒟蒻写了一个上午才A，其实就是一个不用剪枝的记忆化搜索。
因为F[k]*2=F[k+1]+F[k-2]，即存在最优解满足同一个FIB数出现次数不超过1

令l表示小等于n且最大的斐波那契数，r为其后一项，可以二分求

可以推出搜索时的规则

dp(n) = min{ dp(n-l) , dp(r-n) } + 1
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<map>
#include<cmath>
#define inf 2e18
using namespace std;
long long f[5001],n;
long long top;
long long k;
map<long long,int>zyc;
int search(long long n)
{
    if(zyc[n]!=0)return zyc[n];
    int yy=lower_bound(f,f+top,n)-f;
    if(f[yy]==n)return 1;
    return zyc[n]=min(search(n-f[yy-1]),search(f[yy]-n))+1;
}
int main()
{
    f[0]=1;
    f[1]=1;
    for(int i=1;f[i-1]<=inf;i++,top++)
        f[i]=f[i-1]+f[i-2];
    cin>>k;
    while(k--)
    {
        cin>>n;
        cout<<search(n)<<endl;
    }
    return 0;
}
```

---

## 作者：Vatyr (赞：0)

思路来源于黄学长.

由于f[i]\*2=f[i]+f[i-1]+f[i-2]=f[i+1]+f[i-1]所以可得一定存在一组解使得每个斐波那契数最多只会出现一次。我们按照这个思路来记忆化搜索。对于一个数可能由比它大的数转移而来也可能由比它小的数转移而来，且~~感性理解~~易证这个数一定是由大于它或小于它的第一个的斐波那契数转移而来。因此我们有转移方程f[x]=min(f[x-x1],f[x2-x])+1(其中x1为小于x的第一个斐波那契数，x2为大于x的第一个斐波那契数)。

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
long long f[100];
map<long long ,int> mp;//数组很明显是存不下10^17的，所以我们用map来存，又向黄学长学了一招qwq
inline void tabl()
{
    f[0]=1;
    f[1]=1;
    for(int i=2;i<=90;i++)//由于斐波那契数列增长很快，所以90就足够用了
        f[i]=f[i-1]+f[i-2];
}
int n;
long long x;
int dp(long long x)
{
    if(mp[x])return mp[x];
    int b=lower_bound(f,f+90,x)-f;
    if(f[b]==x)return 1;
    return mp[x]=min(dp(f[b]-x),dp(x-f[b-1]))+1;
}
int main()
{
    tabl();
    scanf("%d",&n);
    while(n--)
    {
        scanf("%lld",&x);
        printf("%d\n",dp(x));
    }
    return 0;
}
```

---

