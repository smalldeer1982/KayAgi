# Ice Sculptures

## 题目描述

The Berland University is preparing to celebrate the 256-th anniversary of its founding! A specially appointed Vice Rector for the celebration prepares to decorate the campus. In the center of the campus $ n $ ice sculptures were erected. The sculptures are arranged in a circle at equal distances from each other, so they form a regular $ n $ -gon. They are numbered in clockwise order with numbers from 1 to $ n $ .

The site of the University has already conducted a voting that estimated each sculpture's characteristic of $ t_{i} $ — the degree of the sculpture's attractiveness. The values of $ t_{i} $ can be positive, negative or zero.

When the university rector came to evaluate the work, he said that this might be not the perfect arrangement. He suggested to melt some of the sculptures so that:

- the remaining sculptures form a regular polygon (the number of vertices should be between 3 and $ n $ ),
- the sum of the $ t_{i} $ values of the remaining sculptures is maximized.

Help the Vice Rector to analyze the criticism — find the maximum value of $ t_{i} $ sum which can be obtained in this way. It is allowed not to melt any sculptures at all. The sculptures can not be moved.

## 说明/提示

In the first sample it is best to leave every second sculpture, that is, leave sculptures with attractivenesses: 2, 4, 5 и 3.

## 样例 #1

### 输入

```
8
1 2 -3 4 -5 5 2 3
```

### 输出

```
14
```

## 样例 #2

### 输入

```
6
1 -2 3 -4 5 -6
```

### 输出

```
9
```

## 样例 #3

### 输入

```
6
1 2 3 4 5 6
```

### 输出

```
21
```

# 题解

## 作者：cst_123 (赞：4)

### 题意

有 $n$ 个数，删除若干个数，可成一个正 $m$ 边形，求这些数的最大值。

这就是个枚举题。先枚举 $n$ 的因子，再依次举出每个顶点，最后枚举顶点和。

题目中 $m\le 3$，是因为没有人会认为有正 $1$ 边形或正 $2$ 边形。

当然，这题 $n\le20000$ 。但是，一道 $O(n^2)$ 的题我们也要优化成 $O(\frac{n^2}{3})$ 的。~~这是蒟蒻的梦想~~


话不多说，上代码。

### 代码
```cpp
long long read(){//快读
   long long x=0,sg=1;char cha=getchar();
   while(cha<'0'||cha>'9'){if(cha=='-')sg=-1;cha=getchar();}
   while(cha>='0'&&cha<='9'){x=x*10+cha-'0';cha=getchar();}
   return x*sg;
}
long long n,ans,sum;
long long a[20010];
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		ans+=a[i];
       		//将全部统计
	}
	for(int i=2;i<=n/3;i++){
    		//枚举正 m 边形的边长
		if(!(n%i))
			for(int j=1;j<=i;j++){
            		//枚举起点
				sum=0;//清0
				for(int k=j;k<=n;k+=i)
					sum+=a[k];
                 			//统计该次的结果
				ans=max(ans,sum);//是最大值
			}
	}
	printf("%lld\n",ans);
	return 0;
}


---

## 作者：PR_CYJ (赞：4)

# [题目传送门](https://www.luogu.com.cn/problem/CF158D)
# 思路
这道题很简单。因为观察到 $ 3\le n\le 20000 $，所以使用枚举来解决。

因为要组成一个正多边形，所以它的顶点间的距离相等，且这个距离必须为 $ n $ 的因数。由于没有正一和正二边形，所以这个距离也不能超过 $ \frac{n}{3} $。

考虑枚举这个距离，然后枚举起点，再找出和的最大值。

想不通的可以自己画图想一想。
# 代码
- 切勿抄袭！！！

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,maxx=0;//maxx要设为 0 
	cin>>n;
	int a[n+10]={};
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		maxx+=a[i];//求出距离为 1时的值，即所有数的和 
	for(int i=2;i<=n/3;i++)//枚举距离 
		if (n%i==0)//距离是 n的因数 
			for(int j=1;j<=i;j++)//枚举起点 
			{
				int s=0;
				for(int k=j;k<=n;k+=i)//求和 
					s+=a[k];
				maxx=max(maxx,s);//找出最大值 
			}
	cout<<maxx<<endl;
}
```

---

## 作者：三点水一个各 (赞：3)

### 思路：

直接枚举多边形可能的边长，

注意边长大于等于3。

统计周长可以用for循环累计，

注意计数器使用后要清零。

然后输出。




```

#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define ll long long
#define INF 1e9
using namespace std;
ll a[20002],n,x,ans=-INF;
int main()
{
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++) 
      scanf("%lld",&a[i]);
    for(ll i=1;i<=round(n/3);i++)//限定边长，>2
      if(n%i==0) for(ll j=1;j<=i;j++)//边长可能
                 { 
                     for(ll k=j;k<=n;k+=i)//枚举每一条边 
                     x+=a[k];//累加边长 
                     ans=max(x,ans);//比较 
	             x=0;//注意清零
                 }
    printf("%lld",ans);
    return 0;
}

```

---

## 作者：LKY928261 (赞：2)

## 题目分析

原题面很长，整整有 14 行的英文，但说到底就是：圆周上有 $n$ 个点，取其中任意个点围成一个点权和最大的正多边形。

由于题目要求的是正多边形，这就意味着所选的点需等距，且点的个数是 $n$ 的因子。而圆周上的每个点等距，所以所选的点的编号等差。

由此，可以非常容易地想到直接枚举 $n$ 的因子，然后再依次枚举多边形的其中一个顶点，最后枚举多边形上的所有点并累加求最值。

除此之外，还需要注意以下两点：

- 为了减小时间复杂度，在举 $n$ 的因子时，需要成对枚举，将单层循环的复杂度由 $O(n)$ 优化到 $O(\sqrt n)$；~~（是个人都想得到）~~

- 由于不会出现正 1 边形和正 2 边形，所以 1 和 2 不能作为边数。

## 参考代码

本人的代码非常精简，欢迎借(chao)鉴(xi)。

```cpp
#include<bits/stdc++.h>
#define ll long long//祖传开ll（虽然本题可以不开）
using namespace std;
ll n,s,t,a[20005],i,j;
void work(ll x,ll y){//枚举以x为间隔，y为编号最小的点的多边形的点权和
	ll t=0,i;
	for(i=y;i<n;i+=x)t+=a[i];
	s=max(s,t);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=0;i<n;i++){cin>>a[i];s+=a[i];}//读入+初始化最值
	if(n%2==0&&n!=4)work(2,0),work(2,1);//判断n能被2整除的情况
	for(i=3;i*i<=n;i++)if(n%i==0){//枚举n的因子
		for(j=0;j<i;j++)work(i,j);
		for(j=0;j<n/i;j++)work(n/i,j);
	}
	cout<<s<<"\n";
}
```

---

## 作者：千秋星辰 (赞：2)

**首先，这是一个暴力枚举题。**

### 思路：
1. 概括题意：在数列中选出几个**间隔相等**的数，使选到的数的和最大。~~虽说原题也够简练了~~

2. 注意到数据范围 $t_i∈[-1000,1000]$，所以全部保留不一定对。

3. 注意到间隔相等，而**边数最少的多边形是三角形**，所以想到枚举**多边形的边长**（数列中数的间隔）。这里的复杂度 $ O(\frac{n}{3}) $。

4. 在边长确定的情况下，可以看到情况并不确定。保留的部分从 $t_1$ 开始或从 $t_2$ 开始是截然不同的结果。因此，在上一步基础上枚举**保留数列的起点**。

5. 枚举数列起点和统计当前情况复杂度总共 $ O(n) $,整体复杂度 $ O(\frac{n^2}{3}) $。数据范围保证  $n ∈ [3,20000]$，所以这是完全不会  _TLE_  的，而且不存在无解的情况。



### AC code:
```cpp
#include<bits/stdc++.h>
#include<algorithm>
#define forever() while(true)
#define out(x) write(x),putchar(' ')
#define writen(x) write(x),putchar('\n')

namespace IO
{
	#define gc getchar
	#define pc putchar
	inline int read()
	{
		int x=0,y=1;char c=gc();
		while(c<'0'||c>'9'){if(c=='-') y=-y;c=gc();}
		while(c>='0'&&c<='9'){x=x*10+(c^'0');c=gc();}
		return x*y;
	}
	void write(int x)
	{
		if(x<0) x=-x,pc('-');
		if(x>9) write(x/10);
		pc(x%10+'0');
	}
	#undef gc
	#undef pc
}

using namespace std;
using namespace IO;
int n,a[20005],tmp,ans;

signed main()
{
	n=read();
	for(int i=1;i<=n;++i)
		a[i]=read(),ans+=a[i];//读入，顺便记录所有元素的和，作为一定发生的情况（也就是一个都不能删）
	for(int l=2;l<=n/3;++l)//枚举删完数后多边形边长
		if(!(n%l))
			for(int st=1;st<=l;++st)//枚举起点
			{
				tmp=0;
				for(int i=st;i<=n;i+=l)//统计当前边长当前起点的结果
					tmp+=a[i];
				ans=max(ans,tmp);
			}
	write(ans);
	return (0^0);
}
```

---

## 作者：世末OIer (赞：2)

一道不能再水的水题。

先枚举多边形的边长，然后枚举起点，接着累加，最后去最大值。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[20005];
long long mx=-135355135135;
int main(){
	ios_base::sync_with_stdio(false);
	cin>>n;
	int i,j,k;
	for(i=0;i<n;i++) cin>>a[i];
	for(i=1;i<n/2+n%2;i++){
		if(n%i!=0) continue;
		for(j=0;j<i;j++){
			long long sum=0;
			for(k=j;k<n;k+=i) sum+=a[k];
			mx=max(mx,sum);
		}
	}
	cout<<mx<<endl;
	return 0;
}
```

 

---

## 作者：BADFIVE (赞：2)

**题意**：有 $n$ 个数等距围成一圈，可以删除其中的一些数，使剩下的数围成一个正 $m$ 边形。求剩下的数的和的最大值。    
**思路**：枚举 $n$ 的约数，只有删除某个约数的所有倍数才能使剩下的组成一个正 $m$ 边形。首先顶点的数目必须 $>2$ ，然后是总数 $n$ 必须要是每次步长的整数倍   

参考代码：   
```
#include<bits/stdc++.h>
using namespace std;
int t[100001];
int main() {
    int n,ans = 0;
    cin>>n;
    for (int i = 1; i <= n; ++i){
       	cin>>t[i];
        ans += t[i];
    }
    for (int i = 2; i <= n / 3; ++i){
        if (n % i == 0){
            for (int k = 1; k <= i; ++k){
                int sum = 0;
                for (int j = k; j <= n; j += i)sum += t[j];
                if (sum > ans)ans = sum;
            }
        }
    }
    cout<<ans;
}
```

---

## 作者：灵光一闪 (赞：2)

嗯，第一次写题解，不知道说什么···

重点：如果n是质数或是4，必须全留下！！！~~(你们谁见过1边形或2边形···~~

好的，上代码：
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<stdio.h>//头文件~
using namespace std;
int a[20050];//n的数据是20000，开多50保险
int yinshu(int a,int b)//返回n的因数
{
    for(int i=b;i<a;i++)
        if(a%i==0) return i;
    return 0;
}
bool isprime(int a)//判质数
{
	for(int i=2;i*i<=a;i++)
		if(a%i==0) return false;
	return true;
}
int main()
{
	bool q=false;//判断是不是第一次
    int b=2;
    int ans,num=0;
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    int z=0;
    if(isprime(n))//判质数
    {
    	for(int i=0;i<n;i++) num+=a[i];
    	cout<<num;
    	return 0;
	}
	if(n==4)//4的特判
	{
		cout<<a[0]+a[1]+a[2]+a[3];
		return 0;
	}
    while(1)
    {
    	z=0;
        int t=yinshu(n,b);
        if(t==0) break;//自觉见函数
  		for(int i=0;i<t;i++)
		  {
			z=0;
			for(int j=i;j<=n+2;j+=t)//
            {
				num+=a[j];
				z++;
			}
			if(z<4) num=ans-1;//筛1变形或2变形
			if(q==false)
			{
				ans=num;
				q=true;
			}
			else ans=max(ans,num);
			num=0;
			z=0;
		}
		b=t+1;//要让yinshu这个函数返回值不同。
		z=0;
    }
    num=0;
	for(int i=0;i<n;i++) num+=a[i];//别忘了全留下！
    cout<<max(ans,num);
	return 0;
}

```
88！

---

## 作者：Fa_Nanf1204 (赞：0)

### 题目大意
有 $n$ 个数围一圈，删掉几个数，使剩下的数围成一个正 $m$ 边形，同时要使剩下的数和最大。
### 分析
因为要围成一个正 $m$ 边形，所以 $m$ 必定可以被 $n$ 整除。先枚举 $m$ 可能的值，再枚举每个正 $m$ 边形可能的顶点是哪些数，从中取和的最大值，就是最后的答案。
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,a[1000005],maxn,sum;
int main(){
    cin.tie();
    cout.tie();
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>a[i];//输入 
        maxn+=a[i];
    }
    for (int i=2;i<=n/3;i++){
        if (n%i!=0) continue;//i如果不能被n整除，则构不成正边形。 
        int b=i;
        for (int j=1;j<=b;j++){
        	sum=0;
            for (int k=j;k<=n;k+=b){//枚举顶点 
                sum+=a[k];
            }
            maxn=max(maxn,sum);//取最大值 
        }
    }
    cout<<maxn;
    return 0;
}
```

---

