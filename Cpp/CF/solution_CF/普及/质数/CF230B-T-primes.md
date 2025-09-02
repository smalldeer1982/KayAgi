# T-primes

## 题目描述

我们知道质数是只有两个不同的正数因数的正整数。相似的，我们把一个正整数 _t_ 叫做 T质数，如果 _t_ 恰好有三个不同的正整数因数。 

你被给了一个含有 _n_ 个正整数的数组。你要给其中所有的数判断它是否是 T质数。

## 说明/提示

给定样例有三个数。第一个数4恰好有三个因数--1、2和4，因此对这个数字输出YES。第二个数5有两个因数（1和5），第三个数6有四个因数（1、2、3和6），因此这两个数的答案是NO。

## 样例 #1

### 输入

```
3
4 5 6
```

### 输出

```
YES
NO
NO
```

# 题解

## 作者：Siyuan (赞：9)

> 原来打了个 质数筛法+质因数分解 的暴力，没想到直接TLE了。后来才发现是一道纯数论题。

首先，本题最容易想到的就是 **线性筛素数** 和 **暴力判断质因数** ，这样确实用到了数论，但是会因为枚举而超时。

## 本题思路：
1. 我们考虑有奇数个因数的整数的特点：显然它是一个 **完全平方数** 。而判断完全平方数，只需要判断$\ \sqrt{x}$取整的平方（即$\ |\sqrt{x}|^2$）是否等于$\ x$即可。
2. 接下来考虑有三个因数的整数的特点：易知$\ \sqrt{x}$不可再分解了，也就是质数，因此我们只需要将$\ [1,\sqrt{x}]$范围内的所有质数筛出来即可！

代码如下：

PS：$MAX$表示$\ \sqrt{x}_{max}$，$sqr[i]$表示第$\ i$个数是完全平方数，$np[i]$表示第$\ i$个数不是质数。

```
#include<cstdio>
#include<cmath>
#define MAX 1000005
#define ll long long
using namespace std;

int n,tot;
ll x;
bool np[MAX+10],sqr[MAX+10];
int p[100005];

void prepare()
{
	for(int i=1;i*i<=MAX;i++)  sqr[i*i]=1;
	for(int i=4;i<=MAX;i+=2)  np[i]=1;
	tot=1;  p[1]=2;  np[0]=np[1]=1;
	for(int i=3;i<=MAX;i+=2)
	{
		if(!np[i])  p[++tot]=i;
		for(int j=1;j<=tot&&i*p[j]<=MAX;j++)
		{
			np[i*p[j]]=1;
			if(i%p[j]==0)  break;
		}
	}
}
int main()
{
	prepare();
	scanf("%d",&n);
	while(n--)
	{
		scanf("%lld",&x);
		ll t=sqrt(x);
		if(t*t==x&&!np[t])  puts("YES");
		else  puts("NO");
	}
	return 0;
}
```

---

## 作者：Laser_Crystal (赞：7)

看到好多大佬用了埃氏筛 or 线性筛，本蒟蒻表示没有这个必要（一来太麻烦，暴力能过；二来嘛……我不会呀）

## 那么我们来讲讲暴力

T质数包含三个不同因子，那么那些书包含三个因子呢？

QwQ就是质数的平方啦~

所以我们只要判断一下这个数的平方根是否为质数就OK了

昨天的洛谷日报——《浅谈素数筛优化》中提到了一个小技巧，就是有关6的优化：除2、3外的任何质数，除以6的余数一定是1或5~~~

把这个小技巧用到程序里~~~
```cpp
#include <bits/stdc++.h>
using namespace std;
bool ss(long long a)//判断素数QwQ
{
  if(a==1)return 0;
  if(a==2||a==3)return 1;
  if(a%6!=1&&a%6!=5)return 0;
  for(long long i=5; i<=sqrt(a); i+=6)
    if(a%i==0||a%(i+2)==0)return 0;
  return 1;
}
int main()
{
  long long n,k;//O(1)的空间QwQ
  cin>>n;
  for(int i=0; i<n; i++)
  {
    cin>>k;
    if(k==1)//特判（不加也AC）
    {
      printf("NO\n");
      continue;//跳出当前循环变量（记得老师是这么讲的）
    }
    long long t=(int)sqrt(k);
    if(t==sqrt(k)&&ss(t))//QwQ这个就是判断
    	printf("YES\n");
    else printf("NO\n");
  }
  return 0;
}
```


---

## 作者：米奇奇米 (赞：4)

## 第一眼看这道题目：哇！蓝题！好题！于是就有了做这道题目的冲动。
### 题意简洁明了，问你是不是一个完全平方数$N$的因子除了$1$,$N$,是不是只含有$sqrt(N)$啦！
### 简单的想一下，比如$16$这个数，的确是$4$的平方，但是其因子却有$[1,16,4,2,8]$,显然不是$T-prime$,那么我们再举一个例子，比如说$49$,是$7$的平方，而他的因子为$[1,49,7]$,随便再找几组：某些是质数的平方数，某些是非质数的平方数，就可以发现一个规律：**如果这个数的平方根是质数，那么他就是$T-prime$,否则就不是了呀！真的是很容易想的！
### 再看一下数据范围：$xi=[1,1e12]$,是非常大的，计算上一下时间复杂度，如果$CF$的数据极大,而且全部都是$T-prime$，那么最差的复杂度也要$O(sqrt(10^6)*10^5)$,但实际上不会有如此毒瘤的数据，必定会有非平方数或，很小的完全平方数，对于判断是不是平方数，只有$O(1)$就行了，对于一个数判是否是质数，也只要$O(sqrt(N))$就行了，所以均摊复杂度大概为$O(10^8)$左右，所以是$O(can pass)$的。下面就贴代码吧，很简单的啦！
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int t,n;
inline bool pd(int x){
	if(x<2) return false;
	for(int i=2;i*i<=x;i++)
	    if(x%i==0) return false;
	return true;
}
signed main(){
	scanf("%I64d",&t);
	while(t--){
		scanf("%I64d",&n);
		if(sqrt(n)!=(int)sqrt(n)){
			puts("NO");
			continue;
		}
		else{
			if(pd(sqrt(n))){
				puts("YES");
			}
			else puts("NO");
		}
	}
	return 0;
}
	
		
```


---

## 作者：Minecraft万岁 (赞：1)

我们~~闲话少叙，进入正题~~  
前置芝士 $:$ 唯一分解定理  
其实这个就是另一个正整数 $N$ $(N>1)$ 有如下柿子   
$$ N={{p_1}^{a_1}}\times{{p_2}^{a_2}}\times{{p_3}^{a_3}}\times......\times{{p_k}^{a_k}}$$       
### 注意，$p_1 p_2 ......p_k$ 都是质数

根据~~显然的~~乘法原理 $N$ 的正整数因子个数 为  
$$ (a_1+1)\times(a_2+1)\times......\times(a_k+1)$$ 
~~很好理解~~ 每一个质数都可以拿其对应指数 $a_j$ $0$ 到 $a_j$个 特殊的 如果每个都是拿了 $0$ 个 那么对应的正整数因子为 $1$ $(1<=j<=k)$

------------
我们把题目中要求的正整数有且只有三个正整数因子带入柿子得到  
$$3=(a_1+1)\times(a_2+1)\times......\times(a_k+1)$$  
~~咦$!$~~ $3$是个质数诶 所以说~~柿子~~方程又可以变成  
$$3=(a_1+1)$$
再根据~~小学知识~~ 解一解 得到
$$a_1=2$$  
假设这个数为 $x$
带入到  原来的柿子中 得到   
$$ x={{p_1}^{2}} $$
所以说你~~发现了什么~~  
首先 如果这个数是题目中的 $T-primes$ 这个数肯定是一个完全平方数 其次 根据唯一分解定理的定义 那么  $\sqrt{x}$ 一定为素数  
所以接下来就~~简单了~~  
因为只需要求 $\sqrt{x}$ 是不是素数 看下 $x$ 范围 在 ${10}^{12}$ 以内 所以说 $\sqrt{x}$ 在 ${10}^{6}$ 之内 
用埃筛筛一下就行了 然后每一个判断一下两个条件就行了  
贴上代码  
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll; 
ll n;//个数 
ll a[100005];//存一下 统一处理 
bool vis[1000006];//筛法的bool数组 true:不是质数 false:是质数 
ll tmp;//用于判断完全平方数 
inline void read(ll &x)//快读 
{
	ll f;char c;
	for (f=1,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for (x=0;c<='9'&&c>='0';c=getchar()) x=x*10+(c&15);x*=f;
}
int main()
{
	read(n);//读入n 
	for(ll i=1;i<=n;i++)
		read(a[i]);//读入a[i] 
	vis[0]=vis[1]=true;//先把不是质数的标记一下 在函数外的bool默认false 
	for(ll i=2;i<=1000000;i++)//标准的筛法 
	{
		if(!vis[i])//是质数 
		{
			for(ll j=2*i;j<=1000000;j+=i)//把质数的倍数筛掉 
				vis[j]=true;
		}
	}
	for(ll i=1;i<=n;i++)
	{
		ll tmp=(ll)(sqrt(a[i]));//根据C++的特性long long取整 
		if(tmp*tmp==a[i]&&(!vis[tmp]))//如果取整后平方还是原数就是完全平方数 
		{//                             看看sqrt(a[i])是不是质数 
			printf("YES\n");//符合条件 
		}
		else
		{
			printf("NO\n");//不符合 
		}
	}
	return 0;
}


```
  

---

## 作者：zxxzdq (赞：1)

    /*
      说明：本题为水题
      因为只有平方数的因数有奇数个，而只有质数的平方才有3个因数。
    */
    #include<bits/stdc++.h> 
    using namespace std;
    long long pd(long long n)//用来判断质数
    {
        long long p;  
        p=(long long)sqrt(n);
        for(long long i=2;i<=p;i++)        
        if(n%i==0) return 1;
        return 0;
    }
    int main()
    {
        long long s,t,k;
        scanf("%lld",&t);
        while(t--)
        {
            scanf("%lld",&s); 
            if(s==1) printf("NO\n");//1需要特判一下
            else
            {
                k=(long long)sqrt(s);
                if(s==k*k&&pd(k)==0)//前者判断其是否为平方数
                {
                    printf("YES\n");
                }
                else printf("NO\n");
            }
        }
        return 0;//完美的结束了
    }

---

## 作者：封禁用户 (赞：0)

哎。。。这道题目。。。真是让我无语啊。。。

就跑一遍线性筛就好了嘛。。。

不过请牢记：**十年$\rm OI$一场空，不开$\rm long$ $\rm long$见祖宗**（这道题目我就这么错了好几次$\rm QwQ$）

好了，让我们看代码吧
```cpp
#include<cstdio>
#include<cmath>
int n,prime[100000],cnt;
long long x;
bool vis[1000005];
using namespace std;
int main()
{
	scanf("%d",&n);
	vis[1]=1;
	for (int i=2; i<=1000000; i++)
	{
		if (!vis[i]) prime[cnt++] = i;
		for (int j=0; j<cnt&&i*prime[j]<=1000000; j++)
		{
			vis[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
	for (int i=1; i<=n; i++)
	{
		scanf("%lld",&x);
		if (x==0)
		{
			printf("NO\n");
			continue;
		}
		if ((long long)sqrt(x)*(long long)sqrt(x)!=x) printf("NO\n"); else
			if (!vis[int(sqrt(x))]) printf("YES\n");
				else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：pipiispig (赞：0)

###又是个恶意评分的好题（HAPPY）
##这是个欧拉筛水题的说，只需要一点点点..........的数学知识就OK了（很简单呢，只有完全平方数可以有奇数个约数，然后再判断下是否是质数不就ok了？）
```#include<iostream>
#include<queue>
#include<cstring>
#include<cmath>
using namespace std;
int isprime[1000015],sprime[1000015];
void prime(int n){
	isprime[0]=isprime[1]=1;
	int cnt=1;
	for(int i=2;i<=n;i++){
		if(isprime[i]==0)sprime[cnt++]=i;
		for(int j=1;j<cnt&&i*sprime[j]<=n;j++){
			isprime[i*sprime[j]]=1;
			if(i%sprime[j]==0)break;
		}
	}
}//欧拉筛模板~埃氏筛应该也ok~单纯的暴力也ok~毕竟是个大水题吗
int main(){
	prime(1000015);
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		long long x;
		cin>>x;
		long long w=sqrt(x);
		if(w*w!=x){
			cout<<"NO"<<endl;
			continue;
		}
		else if(isprime[w]==0){
			cout<<"YES"<<endl;
			continue;
		}
		cout<<"NO"<<endl;//QWQ本来忘特判了还爆了一次w(ﾟДﾟ)w
	}
}```

---

