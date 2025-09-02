# SAC E#1 - 一道中档题 Factorial

## 题目背景

SOL君（炉石主播）和SOL菌（完美信息教室讲师）是好朋友。


## 题目描述

SOL君很喜欢阶乘。而SOL菌很喜欢研究进制。

这一天，SOL君跟SOL菌炫技，随口算出了n的阶乘。

SOL菌表示不服，立刻就要算这个数在k进制表示下末尾0的个数。

但是SOL菌太菜了于是请你帮忙。


## 说明/提示

对于20%的数据，n <= 1000000， k = 10

对于另外20%的数据，n <= 20， k <= 36

对于100%的数据，n <= 10^12，k <= 10^12

## update

1.一组数据

2.K不会==1

3.现在std没有爆long long

4.对数据有问题联系icy （建议大家不要面向数据编程）


## 样例 #1

### 输入

```
10 40```

### 输出

```
2```

# 题解

## 作者：mrsrz (赞：20)

一个数在十进制转k进制时，我们用短除法来做。容易发现，如果连续整除p个k，则末尾有p个0。


于是问题转化为n!能连续整除几个k。


我们先给k分解质因数，然后对于每个质因数，求出n!里有多少个质因数，然后如果k里有x个这个质因数，则求出的结果除以x。最后的答案为这些结果的最小值。


如何求n!里包含质因数的个数？由于n!是1乘到n，所以每p(p是质数)个数里一定有一个p，然后这些数中每p个里一定还有个p，以此类推即可算出。


时间复杂度约是θ(sqrt(k)log⁡n)。

```cpp
#include<cstdio>
using namespace std;
long long n,k,p[200002],c[200002],ans;
int cnt;
int main(){
    scanf("%lld%lld",&n,&k);
    cnt=0;
    for(long long i=2;i*i<=k;++i)
    if(k%i==0){
        p[++cnt]=i;
        c[cnt]=0;
        while(k%i==0){
            ++c[cnt];
            k/=i;
        }
    }
    if(k>1){
        p[++cnt]=k;
        c[cnt]=1;
    }
    ans=20000000000000;
    for(int i=1;i<=cnt;++i){
        long long t=0,now=n;
        while(now)t+=now/=p[i];
        t/=c[i];
        if(t<ans)ans=t;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：NightTide (赞：5)

## PART 0 : 题目大意
本题的意思是要我们将一个十进制数转换成 $K$ 进制。

看到题目数据范围，你也许会无从下手，既然理解了题目，我们就开始做题。

## PART 1 : 思路分析
我们看到转换进制的题目，首先想到的肯定是短除法做，很容易的就会发现，末尾有多少个 $0$，也就是能整除 $K$ 的多少次方。

于是问题转化为 $n!$ 能够整除 $K$ 的几次方。

燃鹅，$n$ 最大可以到 $10^{12}$，$n!$ 必然是一个天文数字，于是我们想到唯一分解定理，把 $n!$ 和 $K$ 都分解成质数相乘的形式，再用 $n!$ 和 $K$ 所包含的 $K$ 的质因数的次数相除，取最小值就得到了答案了。

我相信大部分人看到这里就已经可以开始码代码了，如果还有不明白的，往下看。

## PART 2 ：算法实现
有人就问了，哎你那个 $n!$ 的质因数你也求不出来啊。其实这是没有必要的，前面说过，只要求 $n!$ 和 $K$ 所包含的 $K$ 的质因数的次数相除就可以了，所以我们只需要求出 $K$ 的质因数来就可以了。

那么怎么求 $n!$ 中那些质因数的次数呢? 由于 $n!$ 是从 $1$ 一直乘到 $n$，所以每 $p$ 个数里就有一个质数 $p$，所以我们只要用 $n$ 一直除以 $p$ 就可以了，代码如下：

```cpp
long long frequency(long long x,long long y){
    long long cnt=0;
    while(x>=y){
        cnt+=x/y;
        x/=y;
    }
    return cnt;
}
```

实现了这些以后，我们就可以写出 AC 代码了，如果还有不懂的，请看下面。

## PART 3 : AC 代码
下面是 AC 代码，本人码风极丑，请谅解。

```cpp
#include<bits/stdc++.h>
#define INF 10000000000000
using namespace std;
long long n,k,num,ans=INF;
long long p[10000100],p_k[10000100],p_n[10000100];
long long frequency(long long x,long long y){
    long long cnt=0;
    while(x>=y){
        cnt+=x/y;
        x/=y;
    }
    return cnt;
}
int main(){
    cin>>n>>k;
    for(int i=2;i<sqrt(k+0.5);i++){
    	if(k%i==0){
    		p[num]=i;
    		p_k[num]=0;
    		while(k%i==0){
    			p_k[num]++;
    			k/=i;
			}
			num++;
		}
	}
    if(k>1){
        p[num]=k;
        p_k[num++]=1;
    }
    memset(p_n,-1,sizeof(p_n));
    for(int i=0;i<num;i++){
    	p_n[i]=frequency(n,p[i]);
	}
	for(int i=0;i<num;i++){
		ans=min(ans,p_n[i]/p_k[i]);
	}
	cout<<ans;
}
```

本人蒟蒻，第一次发题解，各位巨佬勿喷，有什么问题可以指出啊。

---

## 作者：GoAway (赞：1)

**题意：求$n!$在$k$进制下后缀$0$的个数。**


~~老夫掐指一算，竟然掐到std算法？~~


- **Solution**

讲道理，刚开始看到这道题是不会做的。

但是老夫想想如果$m=10$还是会做的。

数数小于等于$n$有多少个5的倍数就行了。2的倍数绝对比5的倍数多嘛。

于是我就有了一点想法。

首先质因数分解少不了的。$m = \sum_{i = 1}^k s_i^{cnt_i}$

然后，对于每个质因数$s_i$，算一算$[1,n]$能找到多少它的倍数（不过类似计算2时遇到$2^3$这些要算三次的）

怎么计算？容斥一下？应该只有我这种zz一开始这么想？

后来发现计算的时候每次加1就行了，因为前面的都已经计算过了。

算完之后，发现$s_i$在$[1,n]$中找到了$x_i$，但是出现一个$m$至少$s_i$要出现$cnt_i$次。所以最终答案就是$min_{i=1}^{k}\{ \frac{x_i}{cnt_i} \}$


```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std ;
LL n, m, tot ;
LL s[1010], cnt[1010] ;
int main() {
#ifndef ONLINE_JUDGE
    freopen ( "a.in", "r", stdin ) ;
    freopen ( "a.out", "w", stdout ) ;
#endif
    LL i, j, x, ans, gn ;
    while ( scanf ( "%lld%lld", &n, &m ) != EOF ) {
        memset ( s, 0, sizeof s ) ;
        memset ( cnt, tot = 0, sizeof cnt ) ;
        for ( x = m, i = 2 ; i*i <= x ; i ++ ) {
            if (x%i == 0) s[++tot] = i ;
            while (x%i == 0) cnt[tot] ++, x /= i ;
        }
        if (x != 1) s[++tot] = x, cnt[tot] = 1 ;    
        /*printf ( "%lld = ", m ) ;
        for ( i = 1 ; i < tot ; i ++ ) printf ( "%lld^%lld + ", s[i], cnt[i] ) ;
        printf ( "%lld^%lld\n", s[tot], cnt[tot] ) ;*/
        ans = 1LL<<60 ;
        for ( i = 1 ; i <= tot ; i ++ ) {
            gn = 1 ;    
            x = 0 ;    
            for ( j = 1 ; gn <= n ; j ++ ) {
                gn *= s[i] ;
                x += n/gn ;
            }
            //printf ( "time %lld = %lld\n", s[i], x ) ;    
            ans = min(ans, x/cnt[i]) ;    
        }
        printf ( "%lld\n", ans ) ;    
    }
    return 0 ;
}
```

恬不知耻的发个广告：[我的博客](http://blog.csdn.net/WT\_cnyali/article/details/78171779)


---

## 作者：peterwuyihong (赞：1)

问 $n!$ 的 $k$ 进制下有几个后导 $0$。

转化成 $n!$ 能最多除以几次 $k$。

注意到 $k$ 是合数，并不能直接用处理质数的方法做。于是你把 $k$ 分解质因数，把其中 $p_i^{\alpha_i}$ 的项掏出来，我们求出 $n!$ 中有几个 $p_i$ 因子，除以 $\alpha_i$ 取下取整，就能得出这一项能除多少遍，把所有项掏出来求一下，取最小值即可。

从[FACT1](https://www.luogu.com.cn/problem/SP4941)那里贺来了 pollard-rho，复杂度 $O(k^\frac{1}{4}+\beta d(k))$，$\beta$ 是玄学因子。

```cpp
#define int long long
#define maxn 100010
int ksm(int a,int b,int p){
	int ans=1;
	for(;b;b>>=1,a=(__int128)a*a%p)
	if(b&1)ans=(__int128)ans*a%p;
	return ans;
}
bool MR(int p){
    if(p<2)return 0;
    if(p<=3)return 1;
    int d=p-1,r=0;
    while(!(d&1))d>>=1,r++;
    for(int k=1;k<=10;k++){
        int a=rand()%(p-2)+2;
        int x=ksm(a,d,p);
        if(x==1||x==p-1)continue;
        for(int i=0;i<r-1;i++){
            x=(__int128)x*x%p;
            if(x==p-1)break;
        }
        if(x!=p-1)return 0;
    }
    return 1;
}
int f(int x,int c,int n){
	return ((__int128)x*x+c)%n;
}
int PR(int x){
	int s=0,t=0;
	int c=rand()%(x-1)+1;
	for(int goal=1,val=1;;goal<<=1,s=t,val=1){
		for(int step=1;step<=goal;step++){
			t=f(t,c,x);
			val=(__int128)val*abs(t-s)%x;
			if(step%63==0){
				int d=__gcd(val,x);
				if(d>1)return d;
			}
		}
		int d=__gcd(val,x);
		if(d>1)return d;
	}
}
map<int,int>M;
void fac(int x){
	if(MR(x))return M[x]++,void();
	int p=x;
	while(p==x)p=PR(x);
	fac(p),fac(x/p);
}
int n,k;
int ans=LLONG_MAX;
signed main(){
	cin>>n>>k;
	fac(k);
	for(map<int,int>::iterator it=M.begin();it!=M.end();++it){
		int u=it->first;
		int res=0,g=n;
		while(g){
			res+=g/u;
			g/=u;
		}
		ans=min(ans,res/it->second);
	}
	cout<<ans;
}
```
[双倍经验](https://www.luogu.com.cn/problem/CF1114C)

---

## 作者：yinhy09 (赞：0)

## 思路讲解：

本题其实就是在问 $n!$ 中含有多少个 $k$ 因子。

首先考虑将 $k,n$ 质因数分解，不妨设 $k=\prod\limits_{i=1}^n a_i^{\alpha_{i}}$，若 $n$ 中含有这些质因子分别 $\beta_{i}$ 个，那么最终结果就是 $\min(\frac{\beta_{1}}{\alpha_{1}},\frac{\beta_{2}}{\alpha_{2}} \cdots \frac{\beta_{n}}{\alpha_{n}})$（**均向下取整**）

具体写法如下：

先对 $k$ 进行分解，每分解出一个质因数，就计算在 $n!$ 中含有多少个此质因子。最后将他们的商（向下取整）取最小即可。

## AC CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long nm(long long n,long long m)
{
	long long ans=0;
	while(n)
	{
		ans+=n/m;
		n/=m;
	}	
	return ans;
}
int main(){
	long long n,m;
	cin>>n>>m;
	long long ans=0;
	long long res=9e18;
	int max=1;
	for(long long i=max+1;i<=sqrt(m);i++)
	{
		if(m%i)continue;
		max=i; 
		ans=0;
		while(m%i==0)
		{
			ans++;
			m/=i;
		}
		res=min(res,nm(n,i)/ans);
	}
	if(m>1)res=min(res,nm(n,m));
	if(res==9e18)
	{
		cout<<0;
		return 0;
	}
	cout<<res;
	return 0;
}

```

谢谢观看~

---

## 作者：huangziqin (赞：0)

### 1. 题意
抛去不太长的背景，重点只有一句话——

**一个数的阶乘在 k 进制表示下末尾 0 的个数。**

即为所求。
### 2. 什么是 k 进制下的末尾 0？
假设在 a 进制下有一个数 $x=(1100)_a$。

那么 x 在十进制下的值为 

$ 0\times 1+0\times a+1\times a^2+1\times a^3$。
 
可以简写成 $a^2 \times (1+a)$。

可得出 $x \bmod a^2=0$ 而 $x \bmod a^3 \ne 0$。

我们就可以得出结论——**当一个数模 a 的 x 次方是 0，且模 a 的 (x+1) 次方不等于 0，那么该 a 进制数的末尾有 x 个 0。**

### 3. 末尾 0 怎么求？（难度：小学奥数）
根据上文可知，求有几个 0 即求该数中有几个 a。

那么对于 $n!$ ，我们要求的就是它当中有几个 k。

转换一下思路，相当于求对于 k 的每一个质因数 $a^b$，我们要求出 a 在 $n!$ 中出现的次数 c,

$$ans=\min(ans,\left\lfloor\dfrac{c}{b}\right\rfloor )$$

最后一个问题，对于 $n!$，我们该怎么求它的里面有几个 a?

首先，考虑 $n!$ 中有几个 a 的倍数：
$$n\div a$$ 

然后考虑 $n!$ 中有几个 $a^2$ 的倍数：
$$n\div a^2$$
以此类推，我们可以得出求法：

$$ans=\left\lfloor\dfrac{n}{a}\right\rfloor + \left\lfloor\dfrac{n}{a^2}\right\rfloor+……+\left\lfloor\dfrac{n}{a^b}\right\rfloor(n \ge a^b)$$

代码如下：

```cpp
long long ge(long long x)
{
	long long sum=0;
	long long y=n;
	while(y>=x)
	{
		sum+=y/x;
		y/=x;
	}
	return sum;
}

```
题解部分到此为止。

### 4. 喜闻乐见的代码部分
```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,m;//注意一定要开 long long。

long long ge(long long x)// n! 中有几个因数 a。
{
	long long sum=0;
	long long y=n;
	while(y>=x)
	{
		sum+=y/x;
		y/=x;
	}
	return sum;
}


void fen(long long x)
{
	long long sum=0;
	long long ans=9223372036854775807;//注意这里不能用 INT_MAX;。
	for(long long i=2;i<=sqrt(x);i++)
	{
		if(x%i==0)
		{
		//	cout<<i<<endl;
			sum=0;
			while(x%i==0)
			{
				sum++;
				x/=i;
			}
			ans=min(ans,ge(i)/sum);
		}
	}
	if(x!=1) ans=min(ans,ge(x));//注意如果没有除尽，要特判。
	printf("%lld",ans);
	return;
}

int main()
{
	scanf("%lld%lld",&n,&m); 
	fen(m);
	return 0;
}

```
蒟蒻第一次写题解，若有建议请毫不留情地提出来，谢谢。

---

## 作者：半仙胡小桃 (赞：0)

思路很简单，先对k分解质因数，存入一个数组中去。

然后对于n的阶乘分解那个数组的质因数，除数量，取最小值！

刚开始忘特判tot==0，ans开的不够大！


更快更稳定的方法RHO大质数分解，我懒的打了。

不会的可以参考我之前的BLOG[（求一个很大数的欧拉函数）](http://blog.csdn.net/qq\_35914587/article/details/78171711)





```cpp
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
const int maxm=1e7;
ll prime[maxm],cnt;
bool vis[maxm];
ll z[maxm],num[maxm],tot;
void pre()
{
    vis[1]=1;
    for(int i=2;i<=1e7;i++)
    {
        if(!vis[i])
         prime[++cnt]=i;
        for(int j=1;j<=cnt&&i*prime[j]<=maxm;j++)
         {
            vis[i*prime[j]]=1;
            if(i%prime[j]==0)
             break;
         }
    }
}
int main()
{
    pre();
    ll n,k;
    scanf("%lld%lld",&n,&k);
    for(int j=1;j<=cnt&&k!=1;j++)
    {
        if(prime[j]>n) break;
        if(k%prime[j]==0)
         {
            z[++tot]=prime[j];
            while(k%prime[j]==0)
             k/=prime[j],num[tot]++;
         }
    }
    ll ans=1e17;
    for(int i=1;i<=tot;i++)
    {
        ll t=n;
        ll sum=0;
        while(t)
        {
            t/=z[i];
            sum+=t;
        }
        //printf("%lld\n",sum);
        ans=min(ans,1ll*sum/num[i]);
    }
    ll w=1e17;
    if(ans==w) ans=0;
    /*printf("%lld\n",tot);
    for(int i=1;i<=tot;i++)
     printf("%lld %lld\n",z[i],num[i]);*/
    printf("%lld",ans);
} 

```

---

## 作者：feecle6418 (赞：0)

解释一下这段玄学统计过程。

```cpp
void prime(long long nn,long long kk){
    long long minn=0;//N以内nn的个数
    for(long long i=nn;i<=n;i*=nn)minn+=n/i;//这里表示先统计N以内nn的个数，再统计N以内nn^2的个数，再统计N以内nn^3的个数。。。一直到nn^k>N为止。
    Min=min(Min,minn/kk);//0的个数取所有包含的因数中包含最小的
}
```
完整过程：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
long long Min=0x7fffffffffff,n,k;
void prime(long long nn,long long kk){
    long long minn=0;
    for(long long i=nn;i<=n;i*=nn)minn+=n/i;
    Min=min(Min,minn/kk);
}
void P(long long int nn){
    for(int i=2;i<=sqrt(nn);i++){
        if(nn%i==0){
            int q=0;
            while(nn%i==0){
                q++;
                nn/=i;
            }
            prime(i,q);
        }
    }
    if(nn!=1)prime(nn,1);
}
int main(){
    //cout<<(long)2*3*5*7*11*13*18*19;
    //freopen("factorial.in","r",stdin);
    //freopen("factorial.out","w",stdout);
    cin>>n;
    cin>>k;
    P(k);
    cout<<Min;
    return 0;
}
```

---

## 作者：Adove (赞：0)




```cpp
#include<cstdio>
long long n,k,minn=0x7fffffffffffffffll,num,w,l,t;
long long ctl(long long n,long long k)
{
    long long m=0;
    if(k==2)
    {
        while(n)
        {
            m+=(n>>1);
            n>>=1;
        }
        return m;
}
//由于考虑到因子2可能有很多，所以用位运算统计
    while(n)
    {
        m+=n/k;
        n/=k;
    }
    return m;
}
int main()
{
    while(scanf("%lld%lld",&n,&k)==2)
    {
        while((k&1)==0)
        {
            k>>=1;
            ++w;
}
//同上 if(w) num=ctl(n,2)/w,(minn=minn>num? num:minn),w=0;
for(long long i=3;i*i<=k;i+=2)
        {
            while(k%i==0)
            {
                k/=i;
                ++w;
}
//统计因子i的个数 
if(w) num=ctl(n,i)/w,(minn=minn>num? num:minn),w=0;
if(k==1) break;
//如果k分解完了，就跳出循环
        }
        if(k>1) num=ctl(n,k),(minn=minn>num? num:minn);//如果k仍有质数因子，必然只有1个 
        printf("%lld\n",minn);//输出 
        minn=0x7fffffffffffffffll;
    }
    return 0;
}
```

---

## 作者：魔芋 (赞：0)

主要利用质因子分解，计算k的质因子p在n中出现的次数，可分解为n!=n\*p^e的形式，e=n/p + n/p^2 + n/p^3+ ……

算是写得清楚了吧。。。

不管，本蒟蒻怕被同学打就拿小号搞个题解

   
   
```cpp
#include<iostream>
#include<cstdio>   
#include<cmath>   
#define N 3000001   
using namespace std;
long long a[N],b[N];//a数组存k的质因子，b数组存k的某质因子的个数 
long long sum;   
long long n,k; 
long long ans=0x7fffffffffffffff,temp;    
void fenjie(long long s)  //求质因子及个数 （大概不需要解释了吧。。。） 
{    
    long long i,j=0;   
    for (i=2;i*i<=s;i++)   
        if (s%i==0)   
        {   
            long long count=0;   
            a[j]=i;   
            while (s%i==0)   
            {   
                count++;   
                s/=i;   
            }   
            b[j++]=count;   
        }   
    if (s>1)   
    {    
        a[j]=s;   
        b[j++]=1;   
    }   //可能容易遗漏，即k本身是质数
    sum=j;   
}   
long long fac(long long x,long long y)   
{   
    if (x<y)   
        return 0;  //判断x是否小于y，若小于，结束统计(否则会一直做下去) 
    else   
        return x/y+fac(x/y,y); //统计n！中a[i]出现的次数 
}   
int main()   
{   
    while (scanf("%lld%lld",&n,&k)==2)  //多组数据嘿嘿嘿（反正有人因为这个没分） 
    {   
        fenjie(k);  
        for(int i=0;i<sum;i++)  
        {  
            temp=fac(n,a[i]); 
            temp/=b[i];  //注意，k可以分解为多个a[i]，所以temp还要再除以a[i]的个数 
            ans=ans>temp?temp:ans;   
        }  
        printf("%lld\n",ans);  
    }   
    return 0;   
}
```

---

## 作者：aface0427 (赞：0)

这道题的思路已经很显然了，但是像刚开始未修改数据时数据很大会T怎么办？

使用 Pollard\_rho大数分解。

Pollard\_rho算法的大致流程是 先判断当前数是否是素数（Miller\_rabin）了，如果是则直接返回。如果不是素数的话，试图找到当前数的一个因子（可以不是质因子）。然后递归对该因子和约去这个因子的另一个因子进行分解。

那么自然的疑问就是，怎么找到当前数n的一个因子？当然不是一个一个慢慢试验，而是一种神奇的想法。其实这个找因子的过程我理解的不是非常透彻，感觉还是有一点儿试的意味，但不是盲目的枚举，而是一种随机化算法。我们假设要找的因子为p，他是随机取一个x1，由x1构造x2，使得｛p可以整除x1-x2 && x1-x2不能整除n｝则p=gcd（x1-x2，n），结果可能是1也可能不是1。如果不是1就找寻成功了一个因子，返回因子；如果是1就寻找失败，那么我们就要不断调整x2，具体的办法通常是x2=x2\*x2+c（c是自己定的）直到出现x2出现了循环==x1了表示x1选取失败重新选取x1重复上述过程。

因为x1和x2再调整时最终一定会出现循环，形成一个类似希腊字母rho的形状，故因此得名。

另外通过find函数来分解素数，如果找到了一个素数因子则加入到因子map中，否则如果用Pollard找到一个因子则递归去找素数因子。

之后就没有啥了

下来是全网理论最快的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 1e5 + 7;
void read(ll &x)
{
    char c = getchar();
    x = 0;
    int flag = 1;
    while (c<'0' || c>'9')
    {
        if (c == '-')flag = -1;
        c = getchar();
    }
    while (c >= '0'&&c <= '9')
    {
        x = x * 10 + c - 48;
        c = getchar();
    }
    x *= flag;
}
const int S = 40;
long long mult_mod(long long a, long long b, long long c)
{
    a %= c;
    b %= c;
    long long ret = 0;
    while (b)
    {
        if (b & 1) { ret += a; ret %= c; }
        a <<= 1;
        if (a >= c)a %= c;
        b >>= 1;
    }
    return ret;
}
long long pow_mod(long long x, long long n, long long mod)
{
    if (n == 1)return x%mod;
    x %= mod;
    long long tmp = x;
    long long ret = 1;
    while (n)
    {
        if (n & 1) ret = mult_mod(ret, tmp, mod);
        tmp = mult_mod(tmp, tmp, mod);
        n >>= 1;
    }
    return ret;
}
bool check(long long a, long long n, long long x, long long t)
{
    long long ret = pow_mod(a, x, n);
    long long last = ret;
    for (int i = 1; i <= t; i++)
    {
        ret = mult_mod(ret, ret, n);
        if (ret == 1 && last != 1 && last != n - 1) return true;
        last = ret;
    }
    if (ret != 1) return true;
    return false;
}
bool Miller_Rabin(long long n)
{
    if (n<2)return false;
    if (n == 2)return true;
    if ((n & 1) == 0) return false;
    long long x = n - 1;
    long long t = 0;
    while ((x & 1) == 0) { x >>= 1; t++; }
    for (int i = 0; i<S; i++)
    {
        long long a = rand() % (n - 1) + 1;
        if (check(a, n, x, t))
            return false;
    }
    return true;
}
long long factor[100];
int tol;
long long gcd(long long a, long long b)
{
    if (a == 0)return 1;
    if (a<0) return gcd(-a, b);
    while (b)
    {
        long long t = a%b;
        a = b;
        b = t;
    }
    return a;
}
long long Pollard_rho(long long x, long long c)
{
    long long i = 1, k = 2;
    long long x0 = rand() % x;
    long long y = x0;
    while (1)
    {
        i++;
        x0 = (mult_mod(x0, x0, x) + c) % x;
        long long d = gcd(y - x0, x);
        if (d != 1 && d != x) return d;
        if (y == x0) return x;
        if (i == k) { y = x0; k += k; }
    }
}
void findfac(long long n)
{
    if (Miller_Rabin(n))
    {
        factor[tol++] = n;
        return;
    }
    long long p = n;
    while (p >= n)p = Pollard_rho(p, rand() % (n - 1) + 1);
    findfac(p);
    findfac(n / p);
}
ll n, k;
struct node
{
    ll zhiyin, is;
}c[maxn], p[maxn];
ll cnt1 = 0;
bool cmp(node a, node b)
{
    return a.is<b.is;
}
int main()
{
    read(n), read(k);
    tol = 0;
    findfac(k);
    for (ll i = 0; i<tol; i++)
    {
        ll kk = factor[i];
        cnt1++;
        c[cnt1].is = kk;
        while (i<tol)
        {
            if (factor[i] != kk)break;
            c[cnt1].zhiyin++;
            i++;
        }
        i--;
    }
    sort(c + 1, c + cnt1 + 1, cmp);
    for (int i = 1; i <= cnt1; i++)
    {
        ll m = n, t = c[i].is;
        p[i].is = t;
        ll w = 0;
        while (m)
        {
            m /= t;
            w += m;
        }
        p[i].zhiyin = w;
    }//
     //    for(int i=1;i<=cnt1;i++)
     //    {
     //        cout<<c[i].is<<" "<<c[i].zhiyin<<"--"<<p[i].is<<" "<<p[i].zhiyin<<endl;
     //    } 
    ll ans = 9999999999999LL;
    for (ll i = 1; i <= cnt1; i++)
    {
        ans = min(ans, p[i].zhiyin / c[i].zhiyin);
    }
cout << ans;
return 0;
}
```

---

## 作者：Chuan_ (赞：0)

根据进制的意义，在k进制的情况下逢k进1，那么末位就变为了0。题目要求求n！在k进制下末位的0，那么我们就可以求n！整除k多少次。该次数记为i。i就是答案。所以k^i<=n!。

由于n非常之大，求n！是不现实的。我们可以把k和n！分解质因数，举个栗子，n！=2^a \* 3^b \* 5^c....k同理。

因为n！是n的阶乘（废话）所以n里面有的质因数在n！里也存在。再思考k与n！的关系可以知道，如果一个质因数存在于n中，但不存在于k中，我们是无需理会的。所以我们只需要分解k的质因数就可以了。之后我们再判断从k分解出来的质因数也是不是n的质因数。如果是的话，假设n!中2的个数为a（同上栗子），k中2的个数为x，那么a整除x就是有可能为答案。因为n！和k的相同质因数可能有多个，所以我们就要找某个a整除某个x的最小值（值大了小的受不了），这个值就是答案了。

‘’‘cpp

```cpp
#include<iostream>
#include<cstdio>
#include<fstream>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
const int maxn=1e6+5;
ll n,k,ans,x,prmnum;
struct yan
{
    ll ds,zsn,zsk;
}t[maxn];
void fss(ll p)
{
    ll temp=(sqrt(p));
    for (ll i=2;i<=temp;i++)
    {
        if (p%i==0)
        {
            ll prm=0;
            while (p%i==0)
            {
                prm++;
                p/=i;
            }
            prmnum++;
            t[prmnum].ds=i;
            t[prmnum].zsk=prm;//记录质因子 
        }
        temp=(sqrt(p));//提高效率。例如k=200时，把2的个数算出来后p=25，可以看作一个新的k再去分解 
    }
    if (p>1)
    {
        prmnum++;
        t[prmnum].ds=p;
        t[prmnum].zsk=1;
```
}//最后剩下来的保证是质数，一对的嘛

```cpp
}
ll f(ll n,ll x)
{
    ll count=0;
    while (n>0)
    {
        n/=x;
        count+=n;
    }
    return count;
```
}/\*好好考虑如下事实：例如
1-N这N个数中有N/5个数是5的倍数

1-N这N个数中有N/5^2个数是5^2的倍数

1-N这N个数中有N/5^3个数是5^3的倍数

...
就应该能理解这个算法了\*/


```cpp
int main()
{
    while (scanf("%lld%lld",&n,&k)!=EOF)
    {
        ans=9223372036854775807;//2^63 - 1 
        fss(k);//分解k的质因数 
        for (int i=1;i<=prmnum;i++)
        {
            t[i].zsn=f(n,t[i].ds);//计算在n！中质因子x的的数量 
            ans=min(ans,(t[i].zsn/t[i].zsk));
        }
        cout<<ans<<endl;
    }
    return 0;
}
'''
```

---

## 作者：abcdhhhh (赞：0)

//对k进行分解，计算因子个数，取最小值。思路同楼下\_（没必要开数组）\_



```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
long long n,k,ans=1e18;
long long sum(long long a,long long b){
    long long cnt=0;
    for(a/=b;a;a/=b) cnt+=a;//统计a！中质数b的因子个数 
    return cnt;
}
int main(){
    scanf("%lld%lld",&n,&k);
    for(long long i=2;i*i<=k;++i){
        long long cnt=0;
        while(k%i==0) ++cnt,k/=i;//获取质因子 
        if(cnt) ans=min(ans,sum(n,i)/cnt);//取最小值 
    }
    if(k>1) ans=min(ans,sum(n,k));//取最小值 
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：新城 (赞：0)

1，从2循环到sqrt（k）求k的所有因数并记录每个因数出现个数（不记录要翻车）（在循环的过程中要随时更新k的值，不然会t）。

2，在n！中找出每个因数出现次数，在所有因数中找到最少的。

3，输出最小：因数/出现次数 的值（注意一进制特判最大值）。


详见代码：


```cpp
#include <cstdio>
#include <iostream>
using namespace std;
long long n,k,len,ans,ys[5000],num[5000];
int main()
{
    while(scanf("%lld%lld",&n,&k)!=EOF)
    {
        ans=0x7fffffffffffffffll;len=0;
        for(register long long i=2;i*i<=k;i++)
            if(k%i==0)
            {
                ys[len]=i;
                num[len]=0;
                 while(k%i==0)
                  {
                       k/=i;
                        num[len]++;
                }
                len++;
            }
        if(k>1)num[len]=1,ys[len++]=k;
        for(register long long i=0;i<len;i++)
        {
            long long nownum=0;
            for(register long long j=ys[i];j<=n;j*=ys[i])
                nownum+=(n/j);
            if(i==0) ans=nownum/num[i];
            ans=min(ans,nownum/num[i]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：Mark_ZZY (赞：0)

思路：对k进行分解，存入a数组中，在统计n!中a[i]因子的个数(相同的时候，统计的个数/相同的个数即可)，从而得到s，最后输出min(s)

看下面~~~

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define LL long long
#define R register
#define I int
#define MAX 0x7fffffffffffffffll
#define min(x,y) ((x)<(y)?(x):(y))
using namespace std;
    LL n,k,a[70];
int main()
{
    while(scanf("%lld %lld",&n,&k)!=EOF)
    {
        memset(a,0,sizeof(a));//注意清空
        LL ans=MAX;
        I t=0;
        for(R LL i=2;i*i<=k;i++)
            while(k%i==0) k/=i,a[++t]=i;//分解k，存入a
        if(k>1) a[++t]=k;//注意，这是k最后分解为素数的情况
        I q=1;
        while(q<=t)
        {
            LL s=0;
            for(R LL i=a[q];i<=n;i*=a[q])//在统计n!中a[i]因子的个数
                s+=n/i;
            I o=q;//注意初始值
            for(R I i=q+1;i<=t+1;i++)//往后找相同和a[i]的数
                if(a[q]!=a[i])
                {
                    o=i-1;
                    break;
                }
            ans=min(ans,s/((LL)o-q+1));//相同的时候，统计的个数/相同的个数即可
            q=o+1;//往后移动
        }
        printf("%lld\n",ans);
    }
}
```

---

## 作者：老K (赞：0)

其实这题一开始k似乎很大，n也很大，不过后来发生了一点事故？然后范围就小了。

几乎是Polland\_Rho裸题，练一下板子。


---
我们发现，设$k=\prod {p_i}^{k_i}$，那么答案就是$\min( \lfloor \frac{S(n,p_i)}{k_i}\rfloor)$


其中$S(n,p)$表示n!质因数分解后p的指数，也就是n!中包含多少个p。


至于为什么呢？

首先考虑k=p的情况（p为质数，下同）

显然每个p表示k进制下的一个10。

所以0的个数就是p个数


然后考虑$k=p^a$。

显然每a个p表示k进制下的一个10。

所以0的个数就是p的个数/a


然后考虑$k=\prod {p_i}^{k_i}$

显然每个$\prod {p_i}^{k_i}$表示一个k进制下的10，

哪一项不够就凑不成。


然后计算$S(n,p)$也很显然，$S(0,p)=0$,$S(n,p)=S(n/p,p)+n/p$

显然下取整。

然后质因数分解可以利用Pollard\_Rho，当然也可以暴力。


```CPP
/*
Author: CNYALI_LK
LANG: C++
PROG: 3927.cpp
Mail: cnyalilk@vip.qq.com
*/
#include<bits/stdc++.h>
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define DEBUG printf("Passing [%s] in LINE %lld\n",__FUNCTION__,__LINE__)
#define Debug debug("Passing [%s] in LINE %lld\n",__FUNCTION__,__LINE__)
#define all(x) x.begin(),x.end()
using namespace std;
const double eps=1e-8;
const double pi=acos(-1.0);
typedef long long ll;
typedef pair<ll,ll> pii;
template<class T>ll chkmin(T &a,T b){return a>b?a=b,1:0;}
template<class T>ll chkmax(T &a,T b){return a<b?a=b,1:0;}
template<class T>T sqr(T a){return a*a;}
template<class T>T mmin(T a,T b){return a<b?a:b;}
template<class T>T mmax(T a,T b){return a>b?a:b;}
template<class T>T aabs(T a){return a<0?-a:a;}
#define min mmin
#define max mmax
#define abs aabs
ll read(){
    ll s=0,base=1;
    char c;
    while(!isdigit(c=getchar()))if(c=='-')base=-base;
    while(isdigit(c)){s=s*10+(c^48);c=getchar();}
    return s*base;
}
char WritellBuffer[1024];
template<class T>void write(T a,char end){
    ll cnt=0,fu=1;
    if(a<0){putchar('-');fu=-1;}
    do{WritellBuffer[++cnt]=fu*(a%10)+'0';a/=10;}while(a);
    while(cnt){putchar(WritellBuffer[cnt]);--cnt;}
    putchar(end);
}
ll fpm(ll a,ll b,ll p){
    ll c=1;
    while(b){
        if(b&1)c=(a*c)%p;
        a=a*a%p;
        b>>=1;
    }
    return c;
}
ll Miller_Rabin(ll a){
    if(a==2)return 1;
    ll s,g,d,n;
    d=a-1;
    g=0;
    while(!(d&1)){
        d>>=1;
        ++g;
    }
    for(ll i=1;i<=50;++i){
        s=((((ll)rand())<<31)|rand())%(a-1)+1;
        n=fpm(s,d,a);    
        for(ll j=1;j<=g;++j){
            s=n;
            n=s*s%a;
            if(n==1&&s!=1&&s!=a-1)return 0;
        }    
        if(n!=1)return 0;
    }
    return 1;
}
ll pri[102424],ps;
ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}
ll f(ll x,ll c,ll p){
    return (x*x+c)%p;
}


void Pollard_Rho(ll a){
    if(Miller_Rabin(a))pri[++ps]=a;
    else{
        for(ll i=1;;++i){
            ll x=1,ok=1,y=f(x,i,a);
            if(x==y)ok=0;
            while(ok&&gcd(abs(y-x),a)==1){
                x=f(x,i,a);
                y=f(y,i,a);
                y=f(y,i,a);
                if(x==y)ok=0;
            }
            if(ok){
                x=gcd(abs(y-x),a);
                Pollard_Rho(x);
                Pollard_Rho(a/x);
                return;
            }
        }
    }

}
ll js(ll n,ll p){
    ll ans=0;
    while(n){
        ans+=n/p;
        n/=p;
    }
    return ans;
}
int p[102424],k[102424],m;
void calc(){
    sort(pri+1,pri+ps+1);
    p[m=1]=pri[1];
    k[1]=1;
    for(int i=2;i<=ps;++i)if(pri[i]==pri[i-1])++k[m];else {p[++m]=pri[i];k[m]=1;}
}
int main(){
#ifdef cnyali_lk
    freopen("3927.in","r",stdin);
    freopen("3927.out","w",stdout);
#endif
    ll n,K;
    n=read();K=read();
    Pollard_Rho(K);
    calc();
    ll ans=0x3f3f3f3f3f3f3f3f;
    for(ll i=1;i<=m;++i){
        chkmin(ans,js(n,p[i])/k[i]);
    }
    printf("%lld\n",ans);
    return 0;
}

```

---

