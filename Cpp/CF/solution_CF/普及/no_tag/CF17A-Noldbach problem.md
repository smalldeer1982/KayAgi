# Noldbach problem

## 题目描述

Nick is interested in prime numbers. Once he read about Goldbach problem. It states that every even integer greater than $ 2 $ can be expressed as the sum of two primes. That got Nick's attention and he decided to invent a problem of his own and call it Noldbach problem. Since Nick is interested only in prime numbers, Noldbach problem states that at least $ k $ prime numbers from $ 2 $ to $ n $ inclusively can be expressed as the sum of three integer numbers: two neighboring prime numbers and $ 1 $ . For example, 19 = 7 + 11 + 1, or 13 = 5 + 7 + 1.

Two prime numbers are called neighboring if there are no other prime numbers between them.

You are to help Nick, and find out if he is right or wrong.

## 说明/提示

In the first sample the answer is YES since at least two numbers can be expressed as it was described (for example, 13 and 19). In the second sample the answer is NO since it is impossible to express 7 prime numbers from 2 to 45 in the desired form.

## 样例 #1

### 输入

```
27 2
```

### 输出

```
YES```

## 样例 #2

### 输入

```
45 7
```

### 输出

```
NO```

# 题解

## 作者：Miraik (赞：5)

简单模拟。

题目中求的是：

**若一个素数可以用比它小的两个相邻素数的和+1表示**

因此我们先打出$1$到$n$的质数表，然后枚举即可。

代码就很简单了：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){//快读 
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,k,cnt,ans,p[1005];
bool f[1005];
void init(){//筛法 
	for(int i=2;i<=n;i++)
		if(!f[i]){
			p[++cnt]=i;
			for(int j=i*2;j<=n;j+=i)f[j]=1;
		}
}
int main(){
	n=read(),k=read();
	init();//筛素数 
	for(int i=3;i<=cnt&&ans<k;i++){ //从3开始，只要枚举完或满足条件就退出 
		for(int j=1;j<i-1;j++)//枚举相邻的两个素数 
		    if(p[j]+p[j+1]+1==p[i]){//满足条件 ，是好素数 
		    	ans++;
		    	break;
		    }
	}
	puts(ans==k?"YES":"NO");//输出 
	return 0;
}

```


---

## 作者：_Legacy (赞：2)

#### 分析

既然题目对“好素数”要求为

> 可以用比它小的和它相邻的两个素数的和+1表示。

那么可以先打表把 $n$ 以内的素数全部找出来，再把所有素数挨个看看小于它的素数中加上一个相邻的素数，再加上一等于它的。

所以代码分为两部分：
1. 打表，先把$n$之前的素数找出方便查找。
2. 查找$a_i$是否等于比他小素数的 $+$ 一个和那个数相邻的素数$ + 1$。

#### 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[100000],sum=1,s,ans;
//a[100000]是素数表，sum是n之前素数数量，ans是“好素数”数量
void prime(){
	bool t;
	a[0]=2;
	for(int i=3;i<=n;i+=2){
	//优化(i+=2)，因为素数除 2 外都是单数。
		t=1;
		for(int j=2;j<i;j++){
			if(i%j==0){
				t=0;
				break;
			}
		}
		if(t){
			a[sum]=i;
			sum++;
		}
	}
}//打表部分
int main(){
	cin >> n >> k;
	prime();
	for(int i=0;i<sum;i++){
		for(int j=0;j<i;j++){
//只要号数小于i，那么都是小于a[i]的素数
			s=(a[i]-1)-a[j];
//如果a[j]就是其中的一个素数，那么s就是与其相邻的一个素数。
			if(s==a[j-1]||s==a[j+1]){
//相邻的素数分别有比它大一号和小一号的
				ans++;
				break;
			}
		}
	}
	if(ans>=k) cout << "YES";
	else cout << "NO";
}
//CF17A
```

---

## 作者：WinterRain208 (赞：1)

### 题面分析

这题让我们求$2$到$n$是否有大于等于$k$个的好素数。

好素数的定义：

1.必须本身是一个素数。

2.可以拆分成$a$+$b$+$1$的形式。$a$,$b$为素数，且两个素数之间没有其他素数。或者说是两个相邻的素数。

### 做法

由于这题数据为$1e3$，所以显然，暴力枚举可以过。我们先打表出所有小于$n$的素数。再枚举。开一个计数器即可。

## $CODE$

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;
const int N=1e3+5;

int prime[N],n,k,ans=0,pos=1;

bool ip(int x){
	if(x<2)return 0;
	F(i,2,sqrt(x))
		if(x%i==0)return 0;
	return 1;
}

int main(){
	scanf("%d%d",&n,&k);
	F(i,2,n)
		if(ip(i))
			prime[pos++]=i;
	F(i,2,n)
		if(ip(i))
			F(j,2,pos-1)if(prime[j]+prime[j-1]+1==i){
				ans++;
				break;
			}
	puts(ans>=k?"YES":"NO");
	return 0;
}
```

### 举一反三

在考虑一下，如果出题人没有辣么良心，数据大量一两个百怎么办。

显然，这里求素数就不能一个一个枚举了。

那么怎么办呢？

我们介绍两种素数筛法。

#### 埃氏筛

思想：开一个$bool$数组记录一个数是否是质数，从一开始扫，如果是素数就把其所有$n$以内的倍数标为非素数，这里只需要扫的$n$的平方根，往下就全部是之前标记过的了。这个算法比暴力枚举快。
```cpp
for(int i=2;i*i<=(a+1);i++){
		for(int j=i*2;j<=(a+1);j+=i)p[j]=0;
	}
```
其中$p$数组记录一个数是否为质数。

#### 欧拉筛

欧拉筛的原理是保证在二到$n$范围中的每一个合数都能被唯一分解成它的最小质因数与除自己外最大的因数相乘的形式。

我们枚举二到$n$中的每一个数作为筛法中的除自己外的最大因数,如果它未被标记为合数,就先将它放入素数表内，再将这个最大因数与素数表中已经找到的素数作为最小质因数相乘，将得到的这些数标记为合数。

最后输出即可。

```
/*
for(int i=2;i<=n;i++){
		if(IsPrime[i])
			prime[top]=i,top++;
		for(int j=1;j<top;j++){
			if(i*prime[j]>n)
				break;
			IsPrime[i*prime[j]]=0;
			if(i%prime[j]==0)
				break;
		}
	}

*/
```

如果题解中有错误，欢迎各位苣佬私信批斗。

本人还有很大的进步空间，谢谢。

# $wtrl$

------------
蒟蒻不华丽的分割线。


---

## 作者：_HwH_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF17A)

## 分析
本题就是要求在小于等于 $n$ 的范围内等于相邻两个素数之合加一的素数，那么我们可以将小于等于 $n$ 范围以内的质数都先找到，然后枚举比较即可

## Solution
由于 $n$ 的较小，所以不用线性筛，通过直接枚举素数的方式判断也可以将小于等于 $n$ 范围以内的质数较快地找到，然后直接两重循环，暴力枚举判断即可

## Code
```
#include<iostream>
#include<cstdio>
#include<math.h>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;

ll n,k,ans,tot;
ll a[1100];

inline bool judge(ll x)
{
	if(x==1) return false;
	if(x==2) return true;
	for(int i=2;i<=sqrt(x);i++)
	{
		if(x%i==0) return false;
	}
	
	return true;
}

int main(void)
{
	scanf("%lld %lld",&n,&k);
	
	for(int i=2;i<=n;i++)
	{
		if(judge(i))
		{
			a[++tot]=i;
		}
	}
	
	for(int i=1;i<=tot;i++)
	{
		for(int j=1;a[j]<a[i]&&j<=tot;j++)
		{
			if((a[i]-1-a[j])==a[j+1])
			{
				ans++;
				break;
			}
		}
	}
	
	if(ans>=k) printf("YES\n");
	else printf("NO\n");
	
	return 0;
} 
```

---

## 作者：Eason_AC (赞：0)

## Content
若一个素数可以用比它小的相邻的两个素数的和加 $1$ 表示，那么称这个素数为"好素数"。 给定两个正整数 $n,k$，问从 $2$ 到 $n$ 的好素数个数是否 $\geqslant k$。

**数据范围：$2\leqslant n\leqslant 1000,0\leqslant k\leqslant 1000$。**
## Solution
直接通过埃氏筛得到 $1000$ 以内的素数，再通过直接暴力枚举预处理出 $1000$ 以内的“好素数”，最后再遍历 $2$ 到 $n$ 求得这段区间以内“好素数”的数量，判断即可。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

int n, k, ans, isprime[1007], primes[1007], goodprimes[1007];

int main() {
	for(int i = 2; i <= 1000; ++i) isprime[i] = 1;
	for(int i = 2; i <= 1000; ++i)
		if(isprime[i]) {
			primes[++primes[0]] = i;
			for(int j = i * 2; j <= 1000; j += i)
				isprime[j] = 0;
		}
	for(int i = 1; i <= primes[0]; ++i)
		for(int j = 1; j < i - 1; ++j)
			if(primes[i] == primes[j] + primes[j + 1] + 1) {
				goodprimes[primes[i]] = 1;
				break;
			}
	scanf("%d%d", &n, &k);
	for(int i = 2; i <= n; ++i) {
		if(ans == k) return printf("YES"), 0;
		if(goodprimes[i]) ans++;
	}
	if(ans == k) return printf("YES"), 0;
	printf("NO");
	return 0;
}

```

---

## 作者：Ba_creeper (赞：0)

## CF17A Noldbach problem 题解

## 题目分析

这道题需要运用素数筛的知识。

我们可以用数组 $prime$ 来存储在 $2$~$n$ 中所有的素数。存储素数可以用线性筛素数。

```cpp
void primes(int n)
{
	memset(v,0,sizeof(v));//最小质因子
	cnt=0;//质数个数
	for(int i=2;i<=n;i++)
	{
		if(!v[i])//未被标记，i为质数
		{
			v[i]=i;
			prime[++cnt]=i;
		}
		for(int j=1;j<=cnt;j++)
		{
			if(prime[j]>v[i]||prime[j]>n/i) break;//i有更小的质因子，或者超出n的范围
			v[i*prime[j]]=prime[j];//prime[j]为合数 i*prime[j]的最小质因子
		}
	}
}
```

之后，我们要判断这些素数里哪些是“好素数”。“好素数”是在数值比它小的素数中，只要能找到两个相邻的素数，且这两个相邻素数之和加1 等于 “好素数”的数值，那么它就是好素数。

由于数据范围 $2\leq n\leq 1000$ ，所以我们可以用 $O(n^2)$ 来暴力搜出来好素数。只要搜到，就把它存入数组 $x$ 中。

```cpp
for(int i=3;i<=cnt;++i)
		for(int j=1;j<=i-2;++j) 
		{
			if(prime[j]+prime[j+1]+1 == prime[i])
			x[++tot]=prime[i];
		}
```

最后，我们只要判断 $x$ 数组存储的数的个数是否大于 $k$ 即可。

这道题还有一些细节，详见代码部分。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
int n,k,cnt,ans,prime[1005],tot=0;
int x[1005],v[1005];

void primes(int n)//线性筛素数
{
	memset(v,0,sizeof(v));//最小质因子
	cnt=0;//质数个数
	for(int i=2;i<=n;i++)
	{
		if(!v[i])//未被标记，i为质数
		{
			v[i]=i;
			prime[++cnt]=i;
		}
		for(int j=1;j<=cnt;j++)
		{
			if(prime[j]>v[i]||prime[j]>n/i) break;//i有更小的质因子，或者超出n的范围
			v[i*prime[j]]=prime[j];//prime[j]为合数 i*prime[j]的最小质因子
		}
	}
}

int main()
{
	memset(x,0x3f3f3f,sizeof x);
    /*
    这里把x初始化为一个很大的值，因为最后要判断n和x数组的大小。
    如果x数组中的数都小于n，则下一个数需要为一个最大值，以记录答案个数。
    */
	cin>>n>>k;
	primes(n);	//线性筛素数
	
	for(int i=3;i<=cnt;++i)
		for(int j=1;j<=i-2;++j) 
		{
			if(prime[j]+prime[j+1]+1 == prime[i])
			x[++tot]=prime[i]; //筛出“好素数”
		}
		
	for(int i=1;i<=tot+1;++i)
	if(x[i]>n) 
	{
		ans=i-1; //判断在范围内有几个“好素数”
		break;
	}
	
	if(ans>=k) cout<<"YES"; //最后和k作比较，输出答案
	else cout<<"NO";
}
```



---

## 作者：ygl666666 (赞：0)

这题我最开始做了很久，然后看到了[它](https://www.luogu.com.cn/discuss/show/32496)
原来**翻译不准确**：
题目只要求两个小素数相邻，而不是两个小素数和该素数相邻！！！
## 接下来是思路
首先，判断质数的函数是肯定是要写的。然后用一个数组把2到n的质数存起来（因为2是最小的质数）。再判断是不是好质数，最后和k比较即可。
## Code
```
/**/
#include<bits/stdc++.h>
using namespace std;
int n,k,sum,c[1001],ans;
bool prime(int a){//判断质数
	if(a<2){//最小质数为2，小于二舍去
		return false;
	}
	for(int i=2;i<=sqrt(a);i++){
		if(a%i==0){
			return false;
		}
	}
	return true;
}
int main(){
	ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i=2;i<=n;i++){//把质数存起来
        if(prime(i))//判断是否为质数
          c[++sum]=i;
    }
    for(int i=2;i<=sum;i++){
        if(prime(c[i-1]+c[i]+1)&&c[i-1]+c[i]+1<=n)//若相邻的质数和+1为质数且小于n的为好质数
            ans++; 
    }
    if(ans>=k){//判断
    	cout<<"YES"<<endl;
	}else{
		cout<<"NO"<<endl;
	}
    return 0;
}
```
## The end

---

## 作者：WKAHPM (赞：0)

题目要求的是一个素数与它相邻的素数之和$+1$为素数（注意这个素数要$\le n$）

思路：

- 预处理$2$~$n$的素数

- 暴力枚举

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int p[1010],len,n,sum,k;
bool prime(int num)//素数判断
{
    if(num<2) return 0;
    if(num==2 or num==3) return 1;
    if(num%6!=5 and num%6!=1) return 0;
    for(int i=5;i*i<=num;i+=6)
    {
        if(num%i==0 or num%(i+2)==0)
          return 0;
    }
    return 1;
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i=2;i<=n;i++)//预处理
    {
        if(prime(i))
          p[++len]=i;
    }
    for(int i=2;i<=len;i++)//枚举
    {
        if(prime(p[i-1]+p[i]+1) and p[i-1]+p[i]+1<=n)
            sum++; 
    }
    cout<<(sum>=k?"YES":"NO");//相当于if(sum>=k) cout<<"YES";else cout<<"NO";
    return 0;
}

```
用时：$1024ms$

我们可以在原来的程序做一些小小的优化

对枚举部分，我们加入一个边界条件

$p[i-1]+p[i] \le n$（$p[i]$为素数）

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int p[1010],len,n,sum,k;
bool prime(int num)
{
    if(num<2) return 0;
    if(num==2 or num==3) return 1;
    if(num%6!=5 and num%6!=1) return 0;
    for(int i=5;i*i<=num;i+=6)
    {
        if(num%i==0 or num%(i+2)==0)
          return 0;
    }
    return 1;
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i=2;i<=n;i++)
    {
        if(prime(i))
          p[++len]=i;
    }
    for(int i=2;i<=len and p[i-1]+p[i]+1<=n;i++)//边界条件
    {
        if(prime(p[i-1]+p[i]+1))
            sum++; 
    }
    cout<<(sum>=k?"YES":"NO");
    return 0;
}

```

用时：$994ms$ （$emmm$才快了$30ms$）

---

## 作者：Cola (赞：0)

$1000$的数据范围是黄题？？

我的本题主要思路：统计出$n$以内的所有的好素数，用计数器累加，最后与$k$比较。

由于我要找出所有的好素数，所以我要把$n$以内的质数都找出来，~~由于本人不会O(n)的欧拉筛~~，就用$O(nlog^2n)$的埃拉托斯特尼筛法。~~但1000以内的数据范围根本没必要这么干~~，但是$OI$之路有很多有关质数的题目，所有还是敲一遍$O(nlog^2n)$的埃拉托斯特尼筛法再熟悉熟悉，码量多不了多少。~~那你怎么不敲欧拉筛~~

其他说明都在代码里：
```cpp
#include<cstdio>
int prime[171] = {2};//存储质数的数，2是第一个质数（唯一一个偶质数），1000以内有168个质数，但习惯多开几个防爆
bool p[1001] = {true, true};//true指不是质数，false是质数，全局变量初始0.
void find_prime()//预处理1000所有的质数
{
    int t = 1;//存质数的计数器
    for(int i = 4;i < 1001;i += 2) p[i] = true;//2的倍数不是质数
    for(int i = 3;i < 33;i += 2)//sqrt(1001)约等于32，+2避免又筛2的倍数
        if(!p[i])//是质数（为false）
        {
            prime[t++] = i;//第t个质数为i，并将t+1
            for(int j = i * i;j < 1001;j += i) p[j] = true;//t的倍数不是质数
        }
    for(int i = 33;i < 1001;i += 2) if(!p[i]) prime[t++] = i;//将>=33的质数放到存储质数的数组里
}
int main()
{
    find_prime();//预处理
    int n, k, ans = 0;//ans存答案
    scanf("%d%d",&n,&k);
    for(int i = 1;prime[i - 1]  + prime[i] + 1 <= n;i++)//质数和+1要小于等于n
    	if(!p[prime[i] + prime[i - 1] + 1])//质数的和+1是质数,那就是好质数
        	ans++;//就加1
    if(ans >= k) puts("YES");//大写字母！！！
    else puts("NO");//大写字母！！！
    return 0;
}
```
结语：其实还可以进行很多剪枝，但$1000$的数据范围真的没必要优化了

---

## 作者：defense (赞：0)

### 思路：先储存；后判断；
```
#include<cstdio>
#include<algorithm>
#include<iostream>


#include<cmath>

using namespace std;
bool p(int x){
    if(x==1)
        return false;
    if(x==2||x==3)
        return true;
    if(x%6!=1&&x%6!=5)
        return false;
    int s=sqrt(x);
    for(int i=5;i<=s;i+=6)
        if(x%i==0||x%(i+2)==0)
            return false;
    return true;
}
int a[1010];
bool mp[1010];
int main(){
    int n,k,temp=0,ans=0;
    cin>>n>>k;
    for(int i=2;i<=n;i++){
        if(p(i)){
            a[temp]=i;
            temp++;
            mp[i]=true;//用于判断 
        }
    }
    for(int i=0;i<temp;i++){
        if(mp[a[i]+a[i+1]+1]){
            ans++;
        }
    }
    if(ans>=k)
       cout<<"YES";
    else
       cout<<"NO";
    return 0;
}

```

---

