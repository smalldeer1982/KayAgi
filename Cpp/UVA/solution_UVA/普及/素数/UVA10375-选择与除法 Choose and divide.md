# 选择与除法 Choose and divide

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1316

[PDF](https://uva.onlinejudge.org/external/103/p10375.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/f4c82551d4d63248a3265b83e25132b66c043585.png)

## 样例 #1

### 输入

```
10 5 14 9
93 45 84 59
145 95 143 92
995 487 996 488
2000 1000 1999 999
9998 4999 9996 4998```

### 输出

```
0.12587
505606.46055
1.28223
0.48996
2.00000
3.99960```

# 题解

## 作者：封禁用户 (赞：4)

## 背景
这题是关于组合数的，听说他们用唯一分解定理写的，但是我好像发现组合数是可以边乘边除的哈哈。这样就是水题。
## 分析
对于$$C(m,n)=\frac{m!}{(m-n)!n!}$$，分母有$m$项，显然分子有$m-n+n$项，即上下项数相等，当两个组合数相除时，这个性质也满足，所以可以边乘边除。
## 代码
```cpp
#include<cstdio>

inline int max(int a,int b){return a > b ? a : b;}

int main(){
	int p,q,r,s;
	while(scanf("%d %d %d %d",&p,&q,&r,&s) != EOF){
		double ans = 1.00000;
		int max1 = max(p - q,q);
		int max2 = max(r - s,s);
		int max3 = max(max1,max2);
		for(int i = 1;i <= max3;i++){
			if(i <= max1) ans = ans / i * (p - max1 + i);
			if(i <= max2) ans = ans / (r - max2 + i) * i;
		}
		printf("%.5lf\n",ans);
	}
	return 0;
}
```

---

## 作者：duchengjun (赞：1)

# 题意

给你 $p$，$q$，$r$，$s$，让你求 $\dfrac{C(p,q)}{C(r,s)}$ 的值。

# 分析

首先我们先要理解一下 $C(m,n)$ 的含义。

题目中说的 $C(m,n)=\dfrac{m!}{(m-n)!n!}$ 是必须要会的。

我们再把 $\dfrac{C(p,q)}{C(r,s)}$ 化简一下：

$$
\dfrac{C(p,q)}{C(r,s)}=\dfrac{\dfrac{p!}{(p-q)!\cdot q!}}{\dfrac{r!}{(r-s)!\cdot s!}}=\dfrac{p!\cdot(r-s)!\cdot s!}{(p-q)!\cdot q!\cdot r!}
$$

然后用唯一分解定理求解即可。

任何一个大于等于 2 的整数 $n$，都可以写出下面的形式：

$$n=p_1^{a_1}\cdot p_2^{a_2}\cdot p_3^{a_3}……$$

所以这题就可以在分母就减，在分子就加。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+10;
int p,q,r,s;
int a[N];
bool vis[N];
vector<int>prime;
void init(){
	for(int i=2;i<=10000;i++)
		if(!vis[i]){
			prime.push_back(i);
			for(int j=i;j<=10000;j+=i)
				vis[j]=true;
		}
}
void count(int t,int ans){
	for(int i=0;i<prime.size();i++){
		while(t%prime[i]==0){
			t/=prime[i];
			a[i]+=ans;
		}
		if(t==1)break;
	}
}
void add(int n,int ans){
	for(int i=1;i<=n;i++)
		count(i,ans);
}
int main(void){
	init();
	while(scanf("%d%d%d%d",&p,&q,&r,&s)!=EOF){
		memset(a,0,sizeof(a));
		add(p,1),add(r-s,1),add(s,1);
		add(p-q,-1),add(q,-1),add(r,-1);
		double ans=1;
		for(int i=0;i<prime.size();i++)
			ans*=pow(double(prime[i]),a[i]);
		printf("%0.5f\n",ans);
	}
	return 0;
}


```


---

## 作者：SisconHL (赞：1)

直接搞会炸到安详（10000!）。

需要考虑边乘边除，然后好像还是会爆炸。

然后考虑分解质因数。

但是也许可以刻意构造数据使挨着顺序乘因为前面太大爆掉。

想过 `random_shuffle`，但可以使得一个质数的指数特别大，咋乘都要爆炸。 

处理多项式的时候我们有 `ln+exp` 的思路，也可以用来处理大数。 

（注意没有ln函数，只有log，就是自然对数） 

精度容易丢失，要用 `long double`。 
```cpp

#include<cstdio>
#include<cmath>
using namespace std;
long double res=0.0,a,b,c,d;
void add(long double x){while(x>0)res+=log(x--);}
void cut(long double x){while(x>0)res-=log(x--);}
int main(){
	while(scanf("%Lf %Lf %Lf %Lf",&a,&b,&c,&d)==4){
		res=0.0;
		add(a);cut(a-b);cut(b);
		cut(c);add(c-d);add(d);
		printf("%0.5Lf\n",exp(res));
	}
} 

---

## 作者：Eric_hoo (赞：1)

不要被这题的难度标签吓到！！！

其实这是一到很简单的题目（学过数论的应该都会）

这道题也不用什么唯一分解定理。

其实简单地边乘边除就行了。（非常方便）^_^

话不多说，上代码

```cpp
#include <bits/stdc++.h>//万能头文件
using namespace std;
int main(){
	int a, b, x, y;
	while (cin >> a >> b >> x >> y)
	{
		int tmp1 = max(a - b, b);
		int tmp2 = max(x - y, y);
		double sum = 1;
		for (int i = 1; i <= tmp1; i++)
			sum = sum / i * (a - tmp1 + i);
        for (int i = 1; i <= tmp2; i++)
			sum = sum / (x - tmp1 + i) * i;
		printf("%.5lf\n", ans);
	}
	return 0;
}
//完美收工
```

---

## 作者：ShineEternal (赞：1)

# 前言：
获取更佳阅读效果请点击[这里](https://blog.csdn.net/kkkksc03/article/details/87925360),任何疑问欢迎私信作者~
# 题目链接:
https://www.luogu.org/problemnew/show/UVA10375
# 分析：
这道题可以用**唯一分解定理**来做。

什么是唯一分解定理？百度即可，这里也简介一下。

> 对于任意一个自然数，都可以写成一些素数的幂次相乘的结果

比如说，$26=13*2$,$30=2*3*5$.

然后说详细做法：

首先make一个素数表prime，具体怎么做呢？

先用一个模板筛出合数：

```cpp
for(int i=2;i<=100;i++)
{
	if(vis[i]!=1)
		for(int j=i*i;j<=10000;j+=i)
		vis[j]=1;
}
反正蒟蒻孤陋寡闻，这已经是我知道最快的造表法了
```
弄出了合数，我们再把每一个素数记到一个vector里

```cpp
for(int i=2;i<=10000;i++)
	{
		if(vis[i]==0)
		{
			prime.push_back(i);
		}
	}	
```
这样为了之后循环幂次方便（~~一次完成，胜造多组数据~~） 

之后就套公式

### $C(m,n)=^{m!}_{n!(m-n)!}$

~~(中间的除号被吞了~~ 
用唯一分解来表示每个数，方便约分，因为此题的实质就是解决越界问题。

# $End$
# 代码：

```cpp
#include<cstdio>
#include<cmath>
#include<vector>
#include<cstring>
using namespace std;
int vis[10005];
vector<int>prime;
int e[10005];
void search(int n,int d)
{
	for(int i=0;i<prime.size();i++)
	{
		while(n%prime[i]==0)
		{
			n=n/prime[i];
			e[i]+=d;
		}
		if(n==1)break;
	}
}
void pd(int n,int d)
{
	for(int i=1;i<=n;i++)
	{
		search(i,d);
	}
}
int main()
{
	for(int i=2;i<=100;i++)
	{
		if(vis[i]!=1)
		for(int j=i*i;j<=10000;j+=i)
		vis[j]=1;
	}
	for(int i=2;i<=10000;i++)
	{
		if(vis[i]==0)
		{
			prime.push_back(i);
		}
	}	
	int p,q,r,s;
	while(scanf("%d%d%d%d",&p,&q,&r,&s)==4)
	{
		memset(e,0,sizeof(e));
		pd(p,1);
		pd(q,-1);
		pd(p-q,-1);
		pd(r,-1);
		pd(s,1);
		pd(r-s,1);
		double ans=1;
		for(int i=0;i<prime.size();i++)
		{
			ans*=pow(prime[i],e[i]);
		} 
		printf("%.5lf\n",ans);
	}
	return 0;
} 
```



---

## 作者：Aw顿顿 (赞：0)

## 题意

题意：
给定 $p,q,r,s$ 求：

$$\dfrac{C_p^q}{C_r^s}$$

## 解析

众所周知，存在

$$C_m^n=\frac{m!}{(m-n)!n!}$$

原题就是：

$$\dfrac{\quad\dfrac{p!}{(p-q)!q!}\quad}{\quad\dfrac{r!}{(r-s)!s!}\quad}=\dfrac{p!(r-s)!s!}{(p-q)!q!r!}$$

一边乘一边除即可，~~有没有勾起某一年联赛的回忆~~

具体怎么实现呢？我们可以将每个数都分解成唯一确定的一个素数分解方案，譬如：

$$600=2^3\times3\times5^2$$

对于每一个部分，我们都能统计其素数指数的个数。

然后上下进行减法即可。

## 实现思路

这里简单讲下怎么实现：

- 用 $O(n\log\log n)$ 的埃氏筛或 $O(n)$ 的欧拉筛筛出一个质数表。
- 每次对于一个数的各个质因数进行统计。
- 如果该数在分母，累计减法，反之累计加法。

对于每个给定的 $x$，我们可以循环判断 $x$ 的所有因数。

很早以前照着 ShineEternal 的题解写过一遍代码，现在贴一下吧：

```cpp
#include<bits/stdc++.h>
using namespace std;
int vis[10005],cnt[10005];
vector<int>prm;
void count(int n,int d){
	for(int i=0;i<prm.size();i++){
		while(!(n%prm[i])){
			n=n/prm[i];
			cnt[i]+=d;
		}if(n==1)return;
	}
}void judge(int n,int d){
	for(int i=1;i<=n;i++)
		count(i,d);
}int p,q,r,s;
signed main(){
	for(int i=2;i<=100;i++){
		if(vis[i]!=1)
		for(int j=i*i;j<=10000;j+=i)
			vis[j]=1;
	}for(int i=2;i<=10000;i++)
		if(!vis[i])prm.push_back(i);
	while(cin>>p>>q>>r>>s){
		memset(cnt,0,sizeof(cnt));
		judge(p,1);judge(q,-1);judge(p-q,-1);
		judge(r,-1);judge(s,1);judge(r-s,1);
		double ans=1;
		for(int i=0;i<prm.size();i++)
			ans*=pow(prm[i],cnt[i]);
		printf("%.5lf\n",ans);
	}return 0;
} 
```

---

## 作者：地大陈参志 (赞：0)

看了一下没有和我一样的就来发一篇对数处理大组合数的题解吧，详细解释在代码注释，更加好懂。这份代码我在VJ上提交AC过了
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
long double logF[maxn*2+1];//log(n!)数组
long double logc(int n,int m)//计算log( C(n,m) )的方法
{
	return logF[n]-logF[m]-logF[n-m];
}

int main()
{
	int p,q,r,s;
	for(int i=1;i<=2*maxn;i++)logF[i]=logF[i-1]+log(i);
    //对数加法就是真数乘法，所以真数部分是阶乘运算
	while(cin>>p>>q>>r>>s)
	{
		long double v1=logc(p,q);
		long double v2=logc(r,s);
		double ans=exp(v1-v2);//e^log(x)=x
		printf("%.5f\n" , ans);
	}
	return 0;
}
```


---

## 作者：233333q (赞：0)

利用唯一分解定理统计各个素数的指数，其它题解也说了

不同的是我的处理函数是这样写的
```cpp
void add(int n,int d)//把结果乘以(n!)^d
{
	for(int i=0;i<prime.size();i++)
	{
		int p=n;
		while(p)
		{
			p/=prime[i];
			e[i]+=d*p;
		}
	}
}
```

---

## 作者：wzhy (赞：0)

## **题目大意**
有多组数据，每组有四个数，为p，q，r，s，求C（p，q）/C（r，s）。C（m，n）=m！/（n!*(m-n)!)。

## **解析**

裸的唯一分解定理，可预先将1至10000的因数处理好，然后开数组对因数个数进行维护，最后进行乘或除即可，时间大约为10ms。


```cpp
#include<bits/stdc++.h>
using namespace std;
int al[10001],v[10000],prime[3500],m=0;
int pd(int n){
    memset(prime,0,sizeof(prime));
    memset(v,0,sizeof(v));
    for(int i=2;i<=n;i++){
        if(!v[i]){
            v[i]=i;
            prime[++m]=i;
        }
        for(int j=1;j<=m;j++){
            if(prime[j]>v[i]||prime[j]>n/i)
                break;
            v[i*prime[j]]=prime[j];
        }
    }
}
void cl1(int a){
    for(int i=2;i<=a;i++){
        if(i==v[i]){
            al[i]++;
            continue;
        }
        int j=i;
        while(j!=v[j]){
            al[v[j]]++;
            j/=v[j];
        }
        al[j]++;
    }
}
void cl2(int a){
    for(int i=2;i<=a;i++){
        if(i==v[i]){
            al[i]--;
            continue;
        }
        int j=i;
        while(j!=v[j]){
            al[v[j]]--;
            j/=v[j];
        }
        al[j]--;
    }
}
int main(){
    pd(10000);
    int p,q,r,s;
    while(cin>>p>>q>>r>>s){
        memset(al,0,sizeof(al));
        cl1(p);
        cl1(s);
        cl1(r-s);
        cl2(q);
        cl2(r);
        cl2(p-q);
        double ans=1;
        for(int i=1;i<=10000;i++){
            if(!al[i])
                continue;
            ans*=pow(i,al[i]);
        }
        printf("%.5lf\n",ans);
    }
    return 0;
}
```

---

## 作者：小闸蟹 (赞：0)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <array>

constexpr int MaxN = 10000;

std::vector<int> Primes;
std::array<int, MaxN> e;

// d表示幂指数
void AddInteger(int n, int d)
{
    for (std::size_t i = 0; i < Primes.size(); ++i)
    {
        while (n % Primes[i] == 0)  // 用到了唯一分解定理
        {
            n /= Primes[i];
            e[i] += d;
        }

        if (n == 1) // 提前终止循环，节省时间
        {
            break;
        }
    }
}

// 表示把结果乘以(n!)^d
void AddFactorial(int n, int d)
{
    for (int i = 1; i <= n; ++i)
    {
        AddInteger(i, d);
    }
}

// 最传统的试商法判断质数
bool IsPrime(int n)
{
    for (int a = 2; a <= std::sqrt(n); ++a)
    {
        if (n % a == 0)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    for (int i = 2; i <= 10000; ++i)    // 先处理出10000以内的质数
    {
        if (IsPrime(i))
        {
            Primes.push_back(i);
        }
    }

    int p, q, r, s;
    while (std::cin >> p >> q >> r >> s)
    {
        std::fill(e.begin(), e.end(), 0);   // 每次都要初始化一边
        AddFactorial(p, 1);
        AddFactorial(q, -1);
        AddFactorial(p - q, -1); // 以上三步重现了C(p, q) = p! / (q! (p - q)!)
        AddFactorial(r, -1);
        AddFactorial(s, 1);
        AddFactorial(r - s, 1);  // 以上三步重现了C(r, s) = r! / (s! (r - s)!)
                                 // 但要注意这里还要取一个倒数
        double Ans = 1.0;
        for (std::size_t i = 0; i < Primes.size(); ++i)
        {
            Ans *= std::pow(Primes[i], e[i]);
        }

        std::printf("%.5lf\n", Ans);
    }

    return 0;
}
```

---

