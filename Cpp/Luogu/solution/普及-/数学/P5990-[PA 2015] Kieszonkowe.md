# [PA 2015] Kieszonkowe

## 题目描述

给定 $n$ 个数，请从中选出若干个数，使得总和为偶数。

请最大化这个总和。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^6$，$1\le a_i\le 10^3$。

## 样例 #1

### 输入

```
5
2 4 3 3 3```

### 输出

```
12```

# 题解

## 作者：MZY666 (赞：21)

[原题传送门](https://www.luogu.com.cn/problem/P5990)。[在窝的博客中食用更佳](https://www.luogu.com.cn/blog/MZY666/solution-p5990)。

### 【 题意概括 】

输入一个正整数 $n$，随后输入 $n$ 个数，求最大的偶数和。

### 【 思路 】

一种较简单的贪心思想。

首先把这些数全部加起来，若和为偶数则和就是我们要的答案。

否则（即和为奇数），就想办法减去一个最小的奇数使这个和变为最大的偶数。

敲代码前先想想：是如何出现不可能的情况的？

当和为偶数时肯定不会不可能。当和为奇数时呢？

再仔细想想？

没错！当 $n=1$ 且唯一的那个数也为奇数时就不可能满足了！

最后，每次想到贪心都得在心里多问几遍自己：能保证这样做的正确性吗？

当然，这次的答案是：Yes.

那么，是时候上代码了！

### 【 代码+注释 】

```cpp
#include<bits/stdc++.h>//万能头文件好 
using namespace std;
#define ll long long//个人习惯 
ll a[1000005];//数组最好放外面
int main(){
	ll n,ans=0,i;//先定义好，ans即答案，i为循环变量
	scanf("%lld",&n);//输入n
	for(i=1;i<=n;i++){
		scanf("%lld",&a[i]);//输入其它数
		ans+=a[i];//边读边加会快些（Maybe?
	}
	if(ans%2==0){//若和已经为偶数了
		printf("%lld\n",ans);//直接输出
		return 0;//提前结束程序
	}
	else{//否则
		if(n==1){
			printf("NIESTETY\n");//输出不可能的情况
			return 0;//提前结束程序
		}//这一步上文有解释
		sort(a+1,a+1+n);//用sort把最小的放前面，好找
		for(i=1;i<=n;i++){
			if(a[i]%2==1){//若是奇数
				printf("%lld\n",ans-a[i]);
				//输出总和减去这个数即为答案，前文有解释
				return 0;//提前结束程序
			}
		}
	}
	return 0;//over~
}
```

对了，由于作者自愿禁言，如果有建议请私信，否则**无法回复**您哦。

完结撒花~（疯狂暗示๑乛◡乛๑

---

## 作者：Yukinoshita_Yukino (赞：8)

这道题其实不用记录奇数个数，只要看累加和是否为奇数。是，减去最小奇数。不是，

直接输出。还有一种情况就是$n$=1且$n$为奇数时，输出NIESTETY。

附AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int N=0x7ffffff;
int a[1000086];
int main()
{
    int n,sum=0,QAQ=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        sum+=a[i];
        if(a[i]%2==1&&a[i]<N) {N=a[i];}
    }
    if(n==1&&a[1]%2==1) {cout<<"NIESTETY";return 0;}
    if(sum%2==1) cout<<sum-N;
    else cout<<sum;
    return 0;
}
```


---

## 作者：PrincessYR✨～ (赞：7)

我们都知道：奇数加奇数等于偶数，偶数加偶数等于偶数，奇数加偶数等于奇数。

那么我们可以先将所有的数都加起来，然后最后在判断一下，如果是偶数，那么证明你脸很白，直接输出就可以了。

但如果是奇数的话，那再进行判断：

由上文我们得知奇数加偶数等于奇数，那么奇数减去奇数就等于偶数，那么就好了，我们可以用sort进行排序（从小到大），如果遇到奇数，那么直接减去，并break，直接输出。

解释：从小大到大排序，那么就保证最后的偶数一定是最大的。

代码：
```
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar(); 
	}
	return x*f;
}
int n,a[1000006],b;
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		b+=a[i];
	}
	if(b%2==1)
	{
	    sort(a+1,a+1+n);
		for(int i=1;i<=n;i++)
		{
			if(a[i]%2==1)
			{
				b-=a[i];
				break;
			}
		 } 
	}
	if(b==0) cout<<"NIESTETY";
	else
	cout<<b;
	return 0;
}

```


---

## 作者：Warriors_Cat (赞：4)

## 题解 P5990 【[PA2015]Kieszonkowe】

### $Solution$:

其实，这道题的主要公式就这三条：

> 奇数+奇数=偶数

> 奇数+偶数=奇数

> 偶数+偶数=偶数

然后我们一步步来分析：

$i.$ 无解。此时不可能有偶数，而且奇数个数肯定不大于 $2$。所以无解时 $n=1$ 且 $a[1]\equiv1\mod2 $。

$ii.$ 求解。那么首先偶数得全选，然后奇数能选偶数个。如果奇数个数为偶数那就最好了，但奇数个数为奇数时，我们只能将最小的奇数减掉，然后加到 $ans$ 里面就行了0^_^0

所以这道题就做完惹QWQ

最后就上一下代码吧！

### $Code$:

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n, ans, x, cnt, y = 0x3f3f3f3f;//记得初始化最小奇数值
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i){
		scanf("%d", &x);
		ans += x;
		if(x & 1) y = min(y, x);//位运算判断奇数
	}
	if(cnt & 1) ans -= y;//如果奇数有奇数个就把最小的奇数减掉
	if(!ans) printf("NIESTETY");//如果答案为零就无解
	else printf("%d", ans);//否则输出答案
	return 0;//完结撒花-v-
}
```
## End

---

## 作者：cq_loves_Capoo (赞：4)

### 这题非常水，连数组都不用，方法如下：  
### 因为  
#### 奇数加奇数等于偶数  
#### 偶数加偶数还是等于奇数  
#### 只有奇数+偶数才会等于奇数  
#### 所以，我们只需要这样做：  
#### 1.判断数的奇偶性。  
#### 2.如果该数是偶数，直接累加。  
#### 3.如果该数是奇数，累加，并找最小奇数。  
#### 4.判断奇数个数是否为奇数，若是奇数，则减去最小奇数  
最后输出累加和。
  
代码如下：  
```cpp
#include<bits/stdc++.h>//万能头文库
using namespace std;
int t,ans,n,m;
int main()
{
	scanf("%d",&n); //输入数的个数
	int w=999999;//定义一个变量，装奇数的最小值
	for(int i=1;i<=n;i++)//循环
	{
		scanf("%d",&t);//输入单个数
		if(t%2==0) ans+=t;//如果是偶数，直接累加
		else //否则
		{
			m++;//奇数个数+1
			ans+=t;//累加
			w=min(w,t);//找最小
		}
	}
	if(m%2==1) ans-=w;//如果奇数个数为一，减去最小奇数
	if(ans!=0) printf("%d",ans);//如果答案不为0，输出
	else printf("NIESTETY");//如果答案为0，输出NIESTETY
}

```


---

## 作者：james1BadCreeper (赞：3)

我们在小学就知道，若干个偶数加起来，结果必定是个偶数。而偶数个奇数加起来，结果也必定是个偶数。对应到这题，就是要找出所有的偶数，和偶数个最大的奇数，把他们加起来，便可以得到正确答案。

但代码实现上有坑，比如要特判程序一个数都没选的情况（题目说了是若干个，不含0个），细节留给大家思考（~~其实对于像```james1```这样的蒟蒻还挺锻炼代码能力？~~）。

参考代码：
```cpp
//来自james1瞎写一通的代码，请勿吐槽
//请允许我的码风如此之诡异
#include<iostream>
#include<cstdio>
#include<algorithm>

//IO板子
namespace The_Future_Diary
{
	using namespace std;
	int __int;
	long long __LL;

	template<typename T>
	inline T read(T p)
	{
		register T x=0;
		register int c=getchar()/*,f=0*/;
		while(!isdigit(c)) c=getchar();/*{if(c=='-')f=1;c=getchar();}*/
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		//return f?-x:x;
		return x;
	}

	int buf[30];
	template<typename T>
	inline void print(T x,char k)
	{
		//if(x<0) putchar('-'),x=-x;
		register int tot=0;
		if(x==0) buf[++tot]=0;
		while(x)
		{
			buf[++tot]=x%10;
			x/=10;
		}
		for(register int i=tot;i>=1;i--)
			putchar(buf[i]+'0');
		putchar(k);
	}

}

using namespace The_Future_Diary;

int n,x;
int a[1000005],b[1000005],ta=0,tb=0;
int ans=0;
int k=1000,sum=0;

int main(void)
{
	n=read(__int);
	if(n==0)
	{
		puts("NIESTETY");
		return 0;
	}
	for(register int i=1;i<=n;i++)
	{
		x=read(__int);
		if(x&1==0) a[++ta]=x;
		else b[++tb]=x;
	}
	if(ta==0&&tb==1)
	{
		puts("NIESTETY");
		return 0;
	}
	for(register int i=1;i<=ta;i++)
		ans+=a[i];
	if(tb==0)
	{
		if(ans!=0) print(ans,'\n');
		else puts("NIESTETY");
		return 0;
	}
	for(register int i=1;i<=tb;i++)
	{
		sum+=b[i];
		k=min(k,b[i]);
	}
	if(tb&1==1) sum-=k;
	print(ans+sum,'\n');
	return 0;
}
```

---

## 作者：chenbaixi (赞：2)

~~这是我在洛谷看到的最水的黄题~~

### 切入正题

一个很简单的贪心，只要把全部数加起来，如果为偶数，那就直接输出。

如果是奇数，那就减去最小奇数，如果没有，就输出NIESTETY

当然还有特殊情况：当n=1或2时，且答案为奇数，这个程序就会错；

当然了，代码还是要放的

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,ans=0,minn=2000000;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>m;
		ans+=m;
		if(m%2!=0)minn=min(minn,m);//找出最小奇数
	}
	if((n==1||n==2)&&ans%2==1)//特判特殊情况
	{
		cout<<"NIESTETY";
		return 0;
	 } 
	if(ans%2==0)cout<<ans;
	else
	{
		if(minn!=2000000)cout<<ans-minn;
		else cout<<"NIESTETY";
	}
	return 0;
}
```



后来，我又仔细地想了想~~，可能只有特殊情况才会无解~~

---

## 作者：Error_Eric (赞：2)

前言：~~虽然有点水，~~
但这其实是一道很好的题目，有很多种解法，让我们明白其实很多程序都可以再优化。


------------


看到题目，~~蒟蒻（比如我）~~
的第一反应自然是搜索，也就是一个一个枚举该数字是否被选中，一看，
$n<=10^6$
，爆搜的
$n^2$复杂度直接爆炸，显然，搜索是不可能的。

------------
然后我就想到了动态规划，这种线性动规时间复杂度
$O(n)$,确实可以解决。

定义
$f[i]$
表示第i个数结尾，和为偶数的情况下最大的和，而
$g[i]$
表示第i个数结尾，和为奇数的情况下最大的和，那么状态转移方程大概是这个样子：
$if(a[i] \mod 2 =0) f[i]=f[i-1]+a[i],g[i-1]=g[i-1]+a[i]$

$if(a[i] \mod 2=1) f[i]=g[i-1]+a[i],g[i-1]=f[i-1]+a[i]$

答案就是$f[i]$.

小结：使用动规，时间$O(N),$空间$O(N)$.


------------
做到这里，我想到，还能不能再简单一些呢？对了，一个数列的和的奇偶性不是奇数就是偶数，代码如下：

```cpp
int n ;
scanf("%d",&n);
for(int i=1;i<=n;i++){
     scanf("%d",&a[i]);
     tot+=a[i];
}
... ...

```
如果总和是偶数，那么直接输出它的和可以了。
```cpp
if(tot%2==0){
     printf("%d",tot);
     return 0;
}

```


如果是奇数怎么办呢？答案显而易见，有一个奇数不可以被选中，哪个奇数被“驱逐”之后答案最大呢？显然是最小的奇数。
```cpp
if(tot%2!=0){
     for(int i=1;i<=n;i++){
          if(a[i]%2!=0)mn=min(mn,a[i]);
     }
     printf("%d",tot-mn);
     return 0;
}
```
这里要注意，还会有无解的情况（只有一个数并且这是奇数）
```cpp
if(n==1 and tot%2==1)
return 0*printf("NIESTETY");
```
优化一下，取消数组$a$,一边输入一边处理$mn$,
```cpp
for(int i=1;i<=n;i++){
	scanf("%d",&in);
	tot+=in;
	if(in%2==1) mn=min(mn,in);
}
```
最后压行：
```cpp
#include<iostream>
#include<stdio.h>
using namespace std;
int tot=0,mn=999999999,in;
int main(){
     int n;
     scanf("%d",&n);
     for(int i=1;i<=n;i++){
          scanf("%d",&in);
          tot+=in;
          if(in%2==1) mn=min(mn,in);
     }
     if(n==1 and tot%2==1) return 0*printf("NIESTETY");
     else return 0*printf("%d",(tot%2==1)?tot-mn:tot);
}//#code by Error_Eric
```
~~极致压行，你值得拥有~~


------------

总结：这道题目告诉我们，很多时候代码可以优化太多。

---

## 作者：霍士弘 (赞：2)

首先观察到答案要求和**最大化**，并且是偶数。   
我们可以转换思路，考虑从所有数字的和中减去最小的数字使得变成总和变成偶数。  
所以我们需要先将所有数字加起来，如果是个偶数就直接输出，如果是个奇数，就找到最小的奇数减掉即可。  
有一个小坑点，就是答案不可以为0，如果减掉最小奇数后为0，就是无解。  
代码：  
```cpp
#include<iostream>
#include<cstdio>
#define maxn 1000000
using namespace std;
int read()
{
	char c = getchar();
	int s = 0,w = 1;
	while(c < '0' || c > '9')
	{
		if(c == '-') w = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		s = (s * 10) + (c - '0');
		c = getchar();
	}
	return w * s;
}//快速读入，忽略
int n;
int a[maxn + 10];
int main()
{	
	n = read();
	int sum = 0;
	for(int i = 1;i <= n;i++)
	{
		a[i] = read();
		sum += a[i];//求和
	}
   //这里分类讨论
	if(sum % 2 == 0)//偶数直接输出
	{
		cout<<sum;
	}else
	{
		int minn = 100000;
		for(int i = 1;i <= n;i++)
		{
			if(a[i] % 2 == 1)
			{
				minn = min(minn,a[i]);
			}
		}
		if(sum - minn == 0)//判断无解
		{
			cout<<"NIESTETY";
		}
		else cout<<sum - minn;
	}
	return 0;
}
```

---

## 作者：ShineEternal (赞：2)

作为贡题人提供一篇[题解](https://blog.csdn.net/kkkksc03/article/details/104198186)

## solution:

考虑先把所有数都相加，如果是偶数就输出了，如果是奇数要减去最小的奇数。

因为奇数-奇数=偶数。

当只有一个奇数的时候是无解的。

-----

这道题我评分是橙到黄，~~不过其实这题红也不为过~~。

如果有对评分的意见请私信。

## code：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[1000005];
int main()
{
	int n;
	scanf("%d",&n);
	int cnt=1005,sum=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum+=a[i];
		if(a[i]%2==1)cnt=min(cnt,a[i]);
	}
	if(n==1&&a[1]%2==1)
	{
		printf("NIESTETY\n");
		return 0;
	}
	if(cnt==1005)
	{
		printf("%d\n",sum);
		return 0;
	}
	if(sum%2==0)
	{
		printf("%d\n",sum);
		return 0;
	}
	printf("%d\n",sum-cnt);
	return 0;
}
```

---

