# 【CSGRound2】光骓者的荣耀

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/s6ozu5pj.png)

小 K 又在做白日梦了。他进入到他的幻想中，发现他打下了一片江山。

## 题目描述

小 K 打下的江山一共有 $n$ 个城市，城市 $i$ 和城市 $i+1$ 有一条双向高速公路连接，走这条路要耗费时间 $a_i$。

小 K 为了关心人民生活，决定定期进行走访。他每一次会从 $1$ 号城市到 $n$ 号城市并在经过的城市进行访问。其中终点必须为城市 $n$。

不仅如此，他还有一个传送器，传送半径为 $k$，也就是可以传送到 $i-k$ 和 $i+k$。如果目标城市编号小于 $1$ 则为 $1$，大于 $n$ 则为 $n$。

但是他的传送器电量不足，只能传送一次，况且由于一些原因，他想尽量快的完成访问，于是就想问交通部部长您最快的时间是多少。

注意：**他可以不访问所有的城市，使用传送器不耗费时间**。

## 说明/提示

### 样例解释 1：

样例 1,2 的图示均为以下图片：

![MZbuTK.png](https://s2.ax1x.com/2019/11/08/MZbuTK.png)

不使用传送器直接走，答案为 $6$，可以证明这个是最小值。

### 样例解释 2：

在 $3$ 处使用，传送到 $4$，答案为 $3$，可以证明这个是最小值。

### 数据范围：

对于所有数据，$a_i > 0$

![Kvrl34.jpg](https://s2.ax1x.com/2019/11/04/Kvrl34.jpg)

## 样例 #1

### 输入

```
4 0
1 2 3```

### 输出

```
6```

## 样例 #2

### 输入

```
4 1
1 2 3```

### 输出

```
3```

# 题解

## 作者：Mophie (赞：178)

#### update:修改了格式

## **这道题点进来的大佬 $100%$ 都会做，这里给大家简述一些奇怪的做法......**

### Part1.水的不行的算法

先看一看这道题，他说了在第i个位置上可以选择跳到 $i-k$ ~ $i+k$ ;

那么我们只需要暴力枚举什么时候会跳即可，即枚举 $i$ ，然后再往下做，时间复杂度 $O(n^2m)$ 。

此算法~~竟然~~得 $40$ 分。

### Part2.part1的优化

再仔细看一眼题面，发现每一条路径非负，所以——

#### 跳的越远越好

话说为什么非负就跳的越远越好呢？

```
即得易证显然
可见如上平凡
留作习题答案略
读者自证不难
```

所以每次即从 $i$ 跳到 $i+k$ 即可

时间复杂度为 $O(n^2)$

此算法得 $80$ 分

### Part3.1小小的优化

其实想到Part2就离Part3不远了（~~反正 $80$ 分对我这种蒟蒻来讲足够了~~）

首先需要思考的是：我到底~~我是谁，我在哪，我在干什么~~是在算什么；

首先先枚举i，再算1->i的路径和，再计算i+k+1->n的路径和；

#### 灵光一闪

其实不就是算 $i+1->i+k$ 之间的距离与 $1->n$ 之间的距离差嘛

所以只需枚举 $i+1->i+k$ 即可，时间复杂度为 $O(nk)$

~~虽然一分也没有多拿到~~

### Part3.2诡异的满分优化

由Part3得：枚举 $i+1->i+k$ 即可；

那么上一个是 $i->i+k-1$ ;

#### 只需上一个减去 $i->i+1$ 加上 $i+k-1->i+k$ 不就好了吗？

其时间复杂度为 $O(n)$

此算法得 $100$ 分，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[1000001],k,Max,now,cnt;
int main() 
{
	cin>>n>>k;
	for(int i=1;i<=n-1;i++)
	{
		cin>>a[i];
		cnt+=a[i];
	}
	for(int i=1;i<=k;i++)Max+=a[i],now+=a[i];
	for(int i=2;i<=n-k;i++)
	{
		now=now-a[i-1]+a[i+k-1];//i+1->i+k
		Max=max(Max,now);
	}
	cout<<cnt-Max<<endl;
	return 0; 
}
```


### Part3.3前缀和优化

只需算 $i+1->i+k$ 即可

那么即为 $1->i+k$ 减去 $1->i$ ;

自然而然的想到了前缀和优化

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long sum[1000001];
long long n,k;
int main()
{
	cin>>n>>k;
	if(k>=n-1)
	{
		cout<<0<<endl;
		return 0;
	} 
	for(int i=1;i<=n-1;i++)
	{
		long long x;
		cin>>x;
		sum[i]=sum[i-1]+x;//前缀和
	}
	long long cnt=sum[k];
	for(int i=2;i<=n-k;i++)
	{
		cnt=max(cnt,sum[i+k-1]-sum[i-1]);//i->i+k-1
	}
	cout<<sum[n-1]-cnt<<endl;
	return 0;
}
```


### Part4：dp党的福利——万物皆可dp

话说此题 $dp$ 也不难想

根据Part3可得每次跳k最优；

那么 $dp$ 公式就出来了

$dp[i][0]$ 表示第i个包括前面都不跳

$dp[i][1]$ 表示第i个跳

则状态转移公式就出来了

$dp[i][0]=dp[i-1][0]+a[i]$;

$dp[i][1]=dp[i-k][0]$$(i>=k)$

再扫一遍即可~

故代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long dp[1000009][2],a[1000009],ans;
int n,k;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n-1;i++)
	{
		cin>>a[i];
	}
	for(int i=2;i<=n;i++)
	{
		dp[i][0]=dp[i-1][0]+a[i-1];
		if(i>k)dp[i][1]=dp[i-k][0];
		dp[i][1]=min(dp[i-1][1]+a[i-1],dp[i][1]);//状态转移方程
	}
	cout<<dp[n][1]<<endl;//输出
	return 0;
} 
```
### Part5.尾声

#### 1.开long long！开long long！开long long！

#### 重要的事情说三遍......

#### 2.感谢这一次的出题组为我们这群蒟蒻带来质量如此之高的题，让本蒟蒻有了收获

#### 3.话说dp做法是我在写时想出来的，喜欢吗？


---

## 作者：沉冥Charming (赞：33)

- 这是一道难度入门的良心题~

- 题意很明了，可以传送一次，求1到n耗费的最少时间

- 很明显，可以贪心，最长的k段选择传送，其余步行

- 求两地之间用时使用前缀和，sum[ i ]表示a1到ai之和

- 那么使用传送器可以节省时间可表示为sum[ k + i ] - sum[ i ]

- ### 扫一遍找到节省时间最大值，答案即是1到n之间步行用时减去传送节省时间

- 然而稍不注意就只有92分，似乎坑到了一部分人（比如本蒟蒻）

![](https://cdn.luogu.com.cn/upload/image_hosting/r8tdz4ky.png)

- 原因很简单，sum[ k + i ] - sum[ i ]中的i要从0开始循环而不是从1开始

- 显而易见，若k=1，那么sum[1 +1 ] - sum[1]表示的是2 , 3 两地之间用时

- ### 所以如果从1开始循环就会漏掉从1地到1+k地之间的用时

- 从0开始循环就可以ac了！！！

- ac代码如下：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define ull unsigned long long //防止不开long long见祖宗
#define ll unsigned long long
ull n,k,sum[1000005],cnt;
ll qr()//快读，让您的排名更好看
{
    ll ret=0;
    char c=getchar();
    while (c<'0'||c>'9')
        c=getchar();
    while (c>='0'&&c<='9')
    {
        ret=(ret<<1)+(ret<<3)+c-'0';
        c=getchar();
    }
    return ret;
}
int main()
{
    //cin>>n>>k; //cin太慢了
    n=qr(),k=qr();
    for (int i=1; i<n; i++)
    {
        ull a;
        //cin>>a;
        a=qr();
        sum[i]=sum[i-1]+a; //前缀和
    }
    for (int i=0; i+k<n; i++) //从0开始循环
        cnt=max(cnt,sum[i+k]-sum[i]); //找节省时间最大值
    cout<<sum[n-1]-cnt;
    return 0;
}

```

---

## 作者：Asrit (赞：27)

这是比赛的第一题（~~然而我感觉比第二题难~~）

由于小K的不稳定传送器只能传送一次，可以想到用总时间-传送节约的跑的时间

因为总距离是变不了的，所以说求出传送节约时间的最大值即可求出最短需要的时间

如果一个一个枚举的相隔k的城市之间的时间的话，会很慢，于是想到用一个求区间和的好东西：前缀和

前缀和通常用sum[ ]表示，sum[i]表示从1到i之间的总和（这里就是从1跑到i所需的时间），用前缀和求从a地跑到b地所需的时间，求sum[b]-sum[a]即可

这样，找出相距k的点之间跑的时间的最大值就用一遍for就可以过了

并且用前缀和的话，sum[n]就是所要求的总距离

于是问题就解决了

上代码！

```cpp
#include<iostream>
using namespace std;
long long sum[1000001];//因为有10^12的a，所以用long long
int main()
{
	long long n,k,a,maxx=0;
	cin>>n>>k;
	sum[1]=0;
	for(int i=2;i<=n;i++)
	{
		cin>>a;
		sum[i]=sum[i-1]+a;//算前缀和
	}
	for(int i=k+1;i<=n;i++)//这里从1到n-k，下面用sum[i+k]-sum[i]也可以
		maxx=max(maxx,sum[i]-sum[i-k]);
	cout<<sum[n]-maxx;
	return 0;
}
```
我的思路是比较容易想到的思路，没有大佬们的那么快，但是能过。如果想要更快的代码就去看看大佬们代码的吧

（蒟蒻第一次写题解，可能会有些错误，欢迎指出；叙述可能不太清晰，请多多包容）

---

## 作者：Karry5307 (赞：26)

### 题意

题面写的太过直白，不解释。

$\texttt{Data Range:}$

![Kvrl34.jpg](https://s2.ax1x.com/2019/11/04/Kvrl34.jpg)

### 题解

CSG R2 T1 官方题解

题目过于签到，这里来讲正解。

我们很显然能够打出$\texttt{80 pts}$的暴力呢，就是每一次考虑一个转移点然后每一次都从$1$开始扫。

然后发现我们可以枚举转移点然后跳，由于只能传送一次，所以这个路程一定是某一段前缀加上某一段后缀。

前后缀和优化一下即可。

时间复杂度$O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MAXN=1e6+51;
ll cnt,kk,to,res=0x3f3f3f3f3f3f3f3f;
ll num[MAXN],prefix[MAXN],suffix[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	cnt=read(),kk=read();
	for(register int i=1;i<cnt;i++)
	{
		num[i]=read();
		prefix[i]=prefix[i-1]+num[i];
	}
	for(register int i=cnt;i;i--)
	{
		suffix[i]=suffix[i+1]+num[i];
	}
	for(register int i=1;i<=cnt;i++)
	{
		to=min(cnt,i+kk);
		res=min(res,prefix[i-1]+suffix[to]);
	}
	printf("%lld\n",res);
}
```

---

## 作者：Leaved_ (赞：14)

# 月赛红题

因为只能传送一次而且地图是线型的，所以传送到 i+k 一定比传送到 i-k 接近最优解

所以，利用 ma 数组存从 1 -> i 的距离，用 dis 存 “从 i 传送到 n 所花费用”

Code：
```cpp

#include <bits/stdc++.h>

using namespace std;

long long n,k;
long long ma[1000010];
long long ans=LLONG_MAX;//9223372036854775807

long long dis[1000010];

int main() {
	cin>>n>>k;
	for(int i=2;i<=n;i++) {
		cin>>ma[i];
		ma[i]+=ma[i-1];
		//利用前缀和存储 1 -> i 的距离 
	}
	for(int i=1;i<=n;i++) {
		dis[i]=ma[i]+ma[n]-ma[i+k];//因为 往前传送 i+k 个点 一定比 往前传送 i+m （m < k）个点更接近最优解，所以直接加 
	}
	for(int i=1;i<=n;i++) {
		ans=min(ans,dis[i]);//取最小值 
	}
	cout<<ans<<endl;//输出 
}
```


---

## 作者：vеctorwyx (赞：13)

一道~~简单的~~贪心

枚举每一种传送方式

直接上代码
```cpp
#include<iostream>
using namespace std;
long long n,k,a[1000010],dp[1000010],minx,ji,shi;
int main()
{
	cin>>n>>k;
	for(int i=1;i<n;i++)
	{
		cin>>a[i];
		shi+=a[i];//总时间（不传送）
	}
	if(k>0)
	for(int i=1;i<=n-k;i++)//枚举每一种传送方式
	{
		if(i==1)
		for(int j=i;j<i+k;j++)
		{
			ji+=a[j];//一开始就传送
		}
		else
		{
			ji-=a[i-1];//去掉前一个时间
			ji+=a[i+k-1];//加上后一个时间
		}
		if(ji>minx)
		minx=ji;//寻找最大用时进行传送
	}
	cout<<shi-minx;//减去传送节约的时间
} 
```
求管理员给通过


---

## 作者：love_luke (赞：13)

因为题目保证了边权值大于等于0，而所有城市是一条链，易知只要一直往终点走就行了。而传送器的作用就是帮你跳过一段路，我们要做的就是求出这段跳过的路的最大权值。

用前缀和处理。注意要开long long。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1000005];
int main()
{
	long long n,k,maxx=0;
	scanf("%ld%ld",&n,&k);
	for (int i=1;i<n;++i)
	{
		scanf("%ld",&a[i]);
		a[i]+=a[i-1];//前缀和
	}
	for (int i=1;i<=n-k;++i)
	{
		maxx=max(maxx,a[i+k-1]-a[i-1]);//求最多能越过的权值
	}
	printf("%ld",a[n-1]-maxx);//别忘了用总路程减去能越过的路程
	return 0;
}
```


---

## 作者：zzyeeeh (赞：6)

#### 关于传送，只需要求出能传送的最大时间就可以了

我想到了我的世界里的粘液块电梯


一个活塞向前推一个粘液块，另一个粘性活塞回拉整体，

通过这种方法求出所有的k个值来存储最大值，再把所有的时间和减去最大值就行了
```c
#include<iostream>
#include<cstdio>
using namespace std;
long long n,i,j,k,o,ans;
long long a[1000010];
long long fr() {//使用快读，玄学神器
	char ch=getchar();
	while(ch>'9'||ch<'0')
		ch=getchar();
	long long sum=ch-'0';//数据中没有负号，所以可以不用判断存在负号的情况
	while((ch=getchar())>='0'&&ch<='9')
		sum=(sum<<3)+(sum<<1)+ch-'0';
	return sum;
}
int main() {
	n=fr();
	k=fr();
	for(i=1; i<=n-1; i++) {
		a[i]=fr();
	}//读入数据
    
	long long d;
	for(i=1; i<=k; i++)
		o+=a[i];//计算前k个值的和
	d=o;//将和转存
    
	for(j=1; k<=n-2; j++,k++) {
		o=o-a[j];
		o=o+a[k+1];
		d=max(o,d);
	}//主体部分，不断向前推进，并更新最大的和的值
    
	for(i=1; i<=n-1; i++)
		ans+=a[i];计算总和
        
	if(k==0)
		d=0;//特判
        
	ans=ans-d;
	if(k>=n)
		ans=0;//特判
        
	cout<<ans;
	return 0;
}
```


---

## 作者：_扶笙_ (赞：4)

P党来发一发/kk(C++也会一点，代码贴的时候两种都放了，但是由于C++刚学，所以码风较丑，大佬们凑合一下呗）

~~洛谷月赛的第一题，果然是增加信心题，连我这样的蒟蒻都过了。~~

[题目传送门](https://www.luogu.org/problem/P5638)


题意已经说的非常清楚了。这里不再赘述。

本人忘记传送东西的名字了，就叫传送门好了QAQ


由于是从第一个地方走到第n个地方，而且，$a[i]>=0$所以传送门只有从$i$走到$i+k$才会减少代价,那么我们就可以用一个前缀和优化一下，在第$i$个位置使用时，传送门会把这个人传送到i+k的位置，减少的代价就为$a[i+k]-a[i]$（我们设$a$为前缀和数组），这样找个最大的$a[i+k]-a[i]$，此时$i$就是传送门使用的位置了，距离和即为：从1到i的距离，加上从i+k+1到n的距离，用前缀和数组$a$表示，即为：$a[i]+a[n]-a[i+k]$

坑点：可以在第0个位置使用传送门

看一个例子吧

```
5 2
10 10 1 1
```

显然，这个例子答案为2，但是如果并没有考虑在第0个位置使用传送门的话，答案会变成11，测试数据里就有这种情况，如果没有考虑这个的话，只会得到92分。


另一个坑点是开int64（long long），不然40分


注：代码中m=0的时候特判了一下，实际上没有这个必要。


```
Pascal代码：
var n,i:longint;
m,max,k:int64;
a:array[0..1000000] of int64;

begin
readln(n,m);
n:=n-1;
for i:=1 to n do
  begin
  read(a[i]);a[i]:=a[i-1]+a[i];
  end;
if m=0 then writeln(a[n])
else
  begin
  for i:=0 to n-m do
    if a[i+m]-a[i]>max then
      begin
      max:=a[i+m]-a[i];k:=i;
      end;
  writeln(a[k]+a[n]-a[k+m]);
  end;
end.
C++代码：
#include<cstdio>
long long n,m,k,max,a[1000009];
using namespace std;
int main()
{
	scanf("%lld%lld",&n,&m);
	n--;
	for (long long  i=1;i<=n;i++)
	  {
	  	scanf("%lld",&a[i]);a[i]+=a[i-1];
	  }
    if (m==0) 
	  {
	  	printf("ll%d\n",a[n]);
			 } 	  
	else
	{
		for (long long i=0;i<=n-m;i++)
		  if (a[i+m]-a[i]>max)
		  {
		  	max=a[i+m]-a[i];k=i;
		  }
	printf("%lld\n",a[k]+a[n]-a[k+m]);	  
			 }	
  return 0;			 	 
 } 
```

---

## 作者：Fatalis_Lights (赞：3)

## Solution

由题意知，传送门只能用一次。所以不妨把它用在耗时最久的地方以减短总用时。

所以我们可以先把耗时总和求出来，再把跳过的部分减去。

那跳过的部分如何快速求出？其实也不用前缀和，只需要一个变量。因为跳过的节点数可控，所以我们可以在加上后面一个数的同时减去最前面的一个数。

比如：

Sample input 1:

10 4 

1 2 3 4 5 4 3 2 1

经后脚跟思考得出：

每一次我们所设的变量为：

1 3 6 10 14 16 16 14 10 6 3 1

很明显，我们只需另一个变量保存最大值即可。

没有传送器时怎么办？ 直接一路走过去即可（就是全加起来）

那么代码就可以写了：

code

```cpp
#include<bits/stdc++.h>
#define N 1000009
#define int long long
using namespace std;

int n,k,a[N];

void print(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}

void read(int &x){
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}

void solve1(){
	int res=0;
	for(int i=1;i<n;i++) res+=a[i];
	print(res); 
	return;
}// 没有传送门

void solve2(){
	int ans=0,res=0,tot=0;
	for(int i=1;i<n;i++) tot+=a[i];
	for(int i=1;i<n;i++){
		res+=a[i]; if(i>k) res-=a[i-k]; //有传送门，那么跳掉最长的一段
		ans=max(res,ans);
//		cout<<res<<" qwq"<<endl;
	} tot-=ans; //总路程-跳掉的路程就是最终答案
	print(tot); 
}

signed main(){
	read(n); read(k);
	for(int i=1;i<n;i++) read(a[i]);
	if(k==0) return solve1(), 0;
	else solve2();
	return 0;
}

```

---

## 作者：StudyingFather (赞：3)

一次跳 $k$ 个城市，等价于将 $k$ 个连续的边的长度变成 $0$。

因为总路程是一定的，我们的目标便是让路程减少的尽可能多，也即找到一个长度为 $k$ 的区间的最大连续和。

只需预处理前缀和，即可在 $O(n)$ 的时间内求出答案。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
long long sum[1000005];
int main()
{
 ios::sync_with_stdio(false);
 int n,k;
 cin>>n>>k;
 for(int i=1;i<n;i++)
 {
  long long x;
  cin>>x;
  sum[i]=sum[i-1]+x;
 }
 if(k>=n)cout<<0<<endl;
 else
 {
  long long ans=0;
  for(int i=k;i<n;i++)
   ans=max(ans,sum[i]-sum[i-k]);
  cout<<sum[n-1]-ans<<endl;
 }
 return 0;
}
```


---

## 作者：xh39 (赞：3)

这道题要使时间少,就要使传送的时间多。题目就转化成了要找k个连续的区间,使区间的和尽可能的大。

暴力找和的时间复杂度为o(k(n-k)) 当n=1000000,k=500000时,就会tle

由于是找区间和,我们很快就想到了用一维前缀和来优化。

---

一维前缀和讲解(会的可以跳过这部分,直接去看代码了)

前缀和的思路就是s[i]表示sum{a[j]}(0<=j<=i)

比如,以下这个数组的前缀和是
```cpp
  0 1 2
a:1 2 3
s:1 3 6
```
前缀和的求法

s[0]=a[0],s[i]=s[i-1]+a[i];

求区间和(l,r)

s[r]-s[l-1] 

//s[r]表示从0到i-1的前缀和,s[l-1]表示从0到l-1的前缀和。减去s[l-1]就去掉了0~l-1之内的所有数。剩下的就是区间和了。

---
前缀和讲解完毕,接下来就看代码。
```cpp
#include<iostream>
using namespace std;
long long a[10000005],s[10000005];
long long max(long long a,long long b){
	return a>b?a:b;
}
int main(){
	long long n,m,k,i,sum=0,Max=0;
	cin>>n>>k;
	for(i=1;i<n;++i){ //为了方便,不初始化s[0]=a[0],就从1开始数组。反正a[0]未赋值全局变量默认是0,0+a[1]就是a[1]。
		scanf("%lld",a+i);
		s[i]+=s[i-1]+a[i]; //求前缀和。
	}
	Max=0;
	for(i=k;i<n;++i){
		Max=max(Max,s[i]-s[i-k]);//求(区间和的)最大值
	}
	cout<<s[n-1]-Max; //和-最大值就是最终所需要的时间。
	return 0;
}
```

---

## 作者：Eason_AC (赞：2)

感觉这次月赛的第二题比第一题还简单，但是第一题思路还是比较明晰的。

---

这里我们利用了前缀和的思想，我们可以在边输入的时候边处理前缀和。

那么这里前缀和有什么用呢？我们可以发现，这道题目本质就是让你找到长度为$k$的最大连续子段和。拿总长度减去这个最大连续子段和就是我们想要的答案啦！

代码实现的时候注意，Karry弄的~~非常良心的~~数据范围，不开long long见祖宗！

好了，所以这道题目就做完了，下面奉上AC代码，不懂的可以参考一下：
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;
#define ll long long

ll n, k, a[1000007], s[1000007], tmp;

int main() {
	scanf("%lld%lld", &n, &k);
	for(ll i = 1; i < n; ++i) {
		scanf("%lld", &a[i]);
		s[i] = s[i - 1] + a[i];
//		printf("%lld:%lld\n", i, s[i]);
	} 
//	if(!k) {
//		printf("%lld", s[n - 1]);
//		return 0;
//	}
	ll maxi = s[k];
//	printf("First it was: %lld\n", maxi);
	for(ll i = k + 2; i < n; ++i) {
//		printf("%lld %lld %lld %lld\n", i, k, s[i], s[i - k]);
		maxi = max(maxi, s[i] - s[i - k]);
//		printf("Max changed to %lld\n", maxi);
	}
	printf("%lld", s[n - 1] - maxi);
	return 0;
}
```

---

## 作者：opened (赞：2)

~~文件快读、快输自提~~

首先想 $O(n^2)$ 暴力，枚举在每个点使用传送器，再用前缀和优化一下，复杂度 $O(n)$

注意开 $long\ long$

```
#include<iostream>
#include<cstdio>
#include<cctype>
using namespace std;
typedef long long ll;
ll n,k,s[1000100];
inline char getcha(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline ll read(){
    ll res=0;char ch=getcha();bool XX=false;
    for(;!isdigit(ch);ch=getcha()) (ch=='-') && (XX=true);
    for(;isdigit(ch);ch=getcha()) res=(res<<3)+(res<<1)+(ch^48);
    return XX?-res:res;
}
void write(ll x){
    static int sta[35];
    int top=0;
    do{sta[top++]=x%10,x/=10;}while(x);
    while(top) cout<<sta[--top];
}
int main(){
	ios::sync_with_stdio(0);
	n=read(),k=read();
	for(register int i=1;i<n;i++){
		ll x=read();
		s[i]=s[i-1]+x;
	}
	if(k==0){
		write(s[n-1]);
		return 0;
	}
	ll ans=0;
	for(register int i=1;i+k<=n;i++)
		if(ans<s[i+k-1]-s[i-1]) ans=s[i+k-1]-s[i-1];
	ll a=s[n-1]-ans;
	write(a);
	return 0;
}
```

---

## 作者：USER113968 (赞：2)

题目大意是说，你需要从一个无向图的点1到达点n，n就是最后一个点。这个图是一条直线排列，每个节点（点1，点n除外）都连接了两条边，如果该点编号为k，则两条边分别通向分别通向点k-1以及点k+1。



不过，你还有一个传送半径为s的传送机，它可以将你传送到（设你现在在点f）点f-k或者点f+k，注意，它只能使用一次。



首先，我们要确定的是，绝对不能往前面传送。因为使用后你必须从更远的地方再走到点n，因此，不能向前传送！



那么，这题该怎么办呢？事实上，只需要枚举使用传送器的点f就好了。看一看那个方案最快。这是一份代码:

注意，这里事实上不需要计算不使用传送器的情况。因为所有边权不会为负数，因此，跳过一些边总比不跳过任何边快一些。


```c++
#include<stdio.h>
unsigned long long a[10000001];//记录边的长度
int main()
{
	unsigned long long n,k;//点数以及传送半径
	scanf("%lld %lld",&n,&k);
	unsigned long long i;
	for(i=1;i<=n-1;++i)
		scanf("%lld",&a[i]);//读入
	unsigned long long now=1;
	unsigned long long ans=1000000000000000010;//取可能的最大值，也就是最大点数*最长边长，免得我们想象的最大值实际比答案还小。普通的long long 是无法存储的，需要无符号的long long 
	unsigned long long j;
	unsigned long long sum;
	for(i=1;i<=n-k;++i)//传送的点，即上文所说的点f
	{
		now=i+k;//向后传送后的点编号
		sum=0;
		for(j=1;j<=now-k-1;++j)//累加前面要走的，要从点1枚举到传送点f，由于边存的是从点u到点u+1的距离，只需循环到now-k-1
			sum+=a[j];
		for(j=now;j<n;++j)//累加后面要走的
			sum+=a[j];//统计在这个点传送的长度
		if(sum<ans)
			ans=sum;//如果比答案小就更新
	}
	printf("%lld",ans);//输出结果
	return 0;
} 
```



但是，上面的代码会超时。为什么？因为它每次都要计算从点1到点f，从点now 到点n的距离。



那我们因该如何优化？其实，只需要使用两个数组存储距离。



设f[i]为从点1到点i的距离。设h[i]为从点n到点i的距离。



那么怎么推出f[i]和h[i]呢？递推公式如下



f[i]=f[i-1]+a[i-1]                    也就是说，从点1到点i的距离就是从点i-1加上从点i-1到点i的边长，且f[0]=0



h[i]=h[i+1]+a[i]                      指的是，从点n到点i的距离就是从点i+1加上从点i到点i+1的边长，且f[n]=0,注意，这里我们要逆着推



这样，点now的长度就是f[now-k]     从点1到传送点f         +         h[now]               从点n到现在的点



AC代码如下：



```c++
#include<stdio.h>
unsigned long long a[10000001];
unsigned long long f[10000001];
unsigned long long h[10000001];//意义见上文
int main()
{
	unsigned long long n,k;
	scanf("%lld %lld",&n,&k);
	unsigned long long i;
	for(i=1;i<=n-1;++i)
		scanf("%lld",&a[i]);//读入
	unsigned long long now=1;
	unsigned long long ans=1000000000000000010;
	unsigned long long j;
	unsigned long long sum;
	f[0]=0;
	h[n]=0;
	for(i=n-1;i>=1;--i)
	{
		h[i]=h[i+1]+a[i];//初始化h数组
	}
    for(i=1;i<=n;++i)
    {
        f[i]=f[i-1]+a[i-1];//初始化f数组
    }
	for(i=1;i<=n-k;++i)//由于过了点n-k就无法传送了，所以不用枚举
	{
		now=i+k;
		sum=0;
		sum+=f[i];
		sum+=h[now];
		if(sum<ans)
			ans=sum;
	}
	printf("%lld",ans);//输出答案
	return 0;
} 
```



---

## 作者：文·和 (赞：2)

~~没有传送器就好玩了......~~

传送器是啥？一个帮你取消掉k次走路的东西

如何使用：跳过和最大的连续k个时间

如何计算连续？前缀和！

### 思路：

输入完就用前缀和顶替原数组，扫一遍从哪里开始的连续k个和最大（也就是省的最多）再用原来总的（也就是此时的p[n]）减去省下的，最后输出。

而第i个到第k个省下的时间就是p[i+k]-p[i]

看代码(我这保险开了long long)

```
#include <bits/stdc++.h>
using namespace std;
long long n,k,p[1000001],i,j,ans;
int main(){
	cin>>n>>k;
	ans=2147483647214748364;  //方便取小
	for(i=1;i<n;i++) cin>>p[i];  //输入
	for(i=2;i<n;i++) p[i]+=p[i-1];  //前缀和求取
	for(i=0;i<n-k;i++) ans=min(ans,p[n-1]-p[i+k]+p[i]);  //扫一遍，用从第i个开始跳算起（第i个没有被跳掉）的时间替换ans
	cout<<ans；  //输出
return 0;
}
}
```
珍爱账号，请勿抄袭，抄袭有惊~~吓~~喜哦~





---

## 作者：bcku1 (赞：2)

**题目大意**：  一条链，给定所有边的边权，另外有一个传送器：从点i直接跳到点(i+k)或点(i-k),只能用一次。求从链头到链尾经过的边权之和的最小值。

首先，使用传送器不会往回条，所有只要考虑从i跳到i+k的情况。

我们可以通过   
4 2   
1 2 3   
这个例子更好地思考算法

![example](https://cdn.luogu.com.cn/upload/image_hosting/i8rvdxwf.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


我们很显然发现这题可以用贪心解决。   
令$f[i]$表示从i开始往后的k个边权之和,即在i时使用传送器能跳过的边权和，很显然我们要最大化这个值。   
在上面那个例子中:   
$f[1]=a[1]+a[2]$   
$f[2]=a[2]+a[3]$ 

可以发现：$f[2]=f[1]-a[1]+a[3] $   

我们发现两个区间相交，如果前一个区间的和已经求出，那么后一个区间的和就是前一个区间的和减去前一个区间的头的值（就是不相交的那部分的和）再加上后一个区间的尾（也不相交）。   

通过我们对$f[i]$的定义，可以发现$f[i]$和$f[i-1]$除了$f[i]$的第一个边权和$f[i-1]$的最后一个边权没有相交，其他都重复了。

因此，我们可以推出一个式子：   
$f[i]=f[i-1]+a[i-1]+a[i-k+1]$   
当然f[1]要提前算下   
$f[1]=a[1]+...+a[k]$

最后答案就是所有边权之和减去$f$数组中最大的值。

时间复杂度:O(n) 

**AC代码**:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
long long sum=0,a[1000005],f[1000005];//a[i]<=1e12,要开long long 
int main(){
	scanf("%d%d",&n,&k);
	memset(a,0,sizeof(a));
	for(int i=1;i<n;i++){
		scanf("%lld",&a[i]);
		sum+=a[i];  //算出所有边权的和 
	}
	for(int i=1;i<=k;i++)
		f[1]+=a[i];  //提前算出f[1] 
	long long Max=f[1];  //存储f数组的最大值 
	for(int i=2;i<=n-k;i++){  //因为在n-k开始使用传送器肯定比在之后所有位置使用更优，所有不用计算n-k之后的f值 
		f[i]=f[i-1]-a[i-1]+a[i+k-1];
		if(Max<f[i]) Max=f[i];
	}
	printf("%lld",sum-Max);
	return 0;
}
```

祝大家CSP RP++

---

## 作者：chongxinzailaile (赞：2)

一条链上选择一段长度为r的连续区间，总值减去所选区间总和的最大值即为答案，想到快速计算区间的总和，我们可以用的知识有
1.前缀和
2.树状数组
3.线段树
4.这道题特殊性质（从开头到中点，从中点+1到终点，min即可）

下面给线段树的参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,r;
long long read(){
    long long ret=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
    while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
    return ret*f;
}
long long a[1000020];
struct note {
	int l,r,sum;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define sum(x) tree[x].sum
}tree[8000020];

void build(int x,int l,int r){
	l(x)=l,r(x)=r;
	if(l==r){
		sum(x)=a[l];
		return ;
	}
	int mid=(l+r)/2;
	build(x*2,l,mid);
	build(x*2+1,mid+1,r);
	sum(x)=sum(x*2)+sum(x*2+1);
}
long long query(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r){
		return sum(x);
	}
	int mid=(l(x)+r(x))/2;
	long long val=0;
	if(l<=mid){
		val+=query(x*2,l,r);
	}
	if(r>mid){
		val+=query(x*2+1,l,r);
	}
	return val;
}
signed main(){
	scanf("%lld%lld",&n,&r);
	long long maxn=0;
	long long sum=0;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		sum+=a[i];
	}
	build(1,1,n);
	for(int i=1;i<=n-r+1;i++){
		maxn=max(maxn,query(1,i,i+r-1));
	}
	cout<<sum-maxn<<endl;
}
```

事实上看到“树上的区间”，不要想麻烦，仔细想一想，就会发现有前缀和等快的方法。

---

## 作者：MoXiaodu (赞：2)

### 前言
>让我们一起赞美良心的出题人吧！

------------

### 题目背景
小$K$又在做白日梦了。他进入到他的幻想中，发现他打下了一片江山。

### 题目描述

小$K$打下的江山一共有$n$个城市，城市$i$和城市$i+1$有一条双向高速公路连接，走这条路要耗费时间$a_i$ 

小$K$为了关心人民生活，决定定期进行走访。他每一次会从11号城市到$n$号城市并在经过的城市进行访问。其中终点必须为城市$n$。

不仅如此，他还有一个传送器，传送半径为$k$，也就是可以传送到$i-k$和$i+k$。如果目标城市编号小于$1$则为$1$，大于$n$则为$n$。

但是他的传送器电量不足，只能传送一次，况且由于一些原因，他想尽量快的完成访问，于是就想问交通部部长您最快的时间是多少。

注意：他可以不访问所有的城市，使用传送器不耗费时间

------------
### 解法：
用前缀和记录，再贪心找出区间$k$的最大值就可以惹QwQ（因为传送器只能用一次）

时间复杂度：$O(n)$

### 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[1000005],k,num[1000005],ans;
//十年OI……（我们要开long long
inline long long read(){//读入优化
	long long f=1,out=0;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		out*=10;out+=c-'0';
		c=getchar();
	}
	return f*out;
}
int main(){
	n=read(),k=read();//题面所给
	for(long long i=1;i<=n-1;i++)//读入
		a[i]=read();
	for(long long i=1;i<=n-1;i++)//前缀和记录
		num[i]=num[i-1]+a[i];
	if(k)//如果用不了传送器，就不记录
	for(long long i=k;i<=n-1;i++){
		ans=max(ans,num[i]-num[i-k]);
	}
	cout<<num[n-1]-ans;//总和减去找到的最大值就是答案
	return 0;
} 
```


---

## 作者：ShineEternal (赞：2)

[好东西](https://blog.csdn.net/kkkksc03/article/details/102994395)

## solution：

因为仅仅能传送一次，所以我们只需要枚举传送点，然后通过前缀和判断就行了。

出题人良心的数据范围开``long long``可过
## code：
```cpp
#include<cstdio>
using namespace std;
long long max(long long x,long long y)
{
	if(x>y)return x;
	return y;
}
long long sum[1000005],a[1000005];
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
	{
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	long long ans=0;
	for(int i=k;i<n;i++)
	{
		ans=max(ans,sum[i]-sum[i-k]);
	}
	printf("%lld\n",sum[n-1]-ans);
	return 0;
}
```

---

## 作者：plm123 (赞：1)

在两次“光荣的”爆0后，我终于参透题意，即：
## 在一个数组中找到一段长为k的和最大子序列
证明也十分容易：
#### 要使时间最短，即路程最小，必须使不用转移器的路程尽可能小，即
### 转移器经过路段和尽可能大
那么，我们的思路就清晰了：
### a数组和为sum，即：共sum路程，最长子序列和为ks，两两相减，即为答案。
sum代码为：
```cpp
for(int i=0;i<n-1;i++){
	cin>>a[i];//原谅我不会用scanf;
	sum+=a[i];
	}
ks代码为：
for(int i=0;i<n-1;i++){
	Ms=min(sum-ks,Ms);//Ms即所求值
	ks-=a[i];//更新ks
	ks+=a[i+k];
	} 

```
```cpp
综上，代码即
#include <bits/stdc++.h>
using namespace std;
long long  a[2000001];
long long sum=0,Ms=pow(2,56)-1,ks=0;
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=0;i<n-1;i++){
		cin>>a[i];
		sum+=a[i];
	}
	if(k==0)cout<<sum<<"\n";//特判减少计算负担(虽然并没有什么卵用) 
	else {
	for(int i=0;i<k;i++)ks+=a[i];	
	for(int i=0;i<n-1;i++){
	Ms=min(sum-ks,Ms);//无须判两遍
	ks-=a[i];
	ks+=a[i+k];
	} 
	cout<<Ms<<"\n";
	}
	return 0;
}

---

## 作者：jbc392 (赞：1)

此题非常容易

就是求出最大的连续k + 1个和就可以了

注意2端的情况

思路：

先求出前缀和

然后先把两端的情况处理

在处理中间的

AC code：

```
#include <bits/stdc++.h>
#define r register
using namespace std;

const int MAXN = 1000010;

//不开long long见祖宗
long long n ,k;
long long sum ,ans;//ans用来存所有路径和，sum存最大连续k + 1个和
long long road[MAXN];

inline long long read()//快读
{
	long long x = 0 ,y = 1;
	char c = getchar();
	while(!isdigit(c))
	{
		if(c == '-') y = -1;
		c = getchar();
	}
	while(isdigit(c))
	{
		x = (x << 1) + (x << 3) + (c ^ 48);
		c = getchar();
	}
	return x * y;
}

int main()
{
	n = read(); k = read();
	for(r int i = 1;i < n;i++)
	{
		road[i] = read();
		ans += road[i];
		road[i] += road[i - 1];//前缀和
	}
	
	if(k == 0) cout << ans;//特判
	if(k + 1 >= n - 1) cout << 0;
	else
	{
		sum = max(road[k] ,road[n - 1] - road[n - k]);//先处理2端
		for(r int i = 2;i < n - k;i++) sum = max(sum ,road[i + k] - road[i]);//处理中间
		cout << ans - sum;//答案为总和 - 最大连续k + 1个和
	}
	
	return 0;//好习惯
}
```


---

## 作者：Create_Random (赞：1)

~~本蒟蒻又来水红题题解了~~

思路：

直接算出总长度

然后用前缀和算出最大的长度为k的区间和

然后直接相减即可

贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k;
long long a[1000010];
long long b[1000010];
long long maxn;
long long ans;
long long read()//快读不解释
{
    long long x=0,ch=getchar();
    while(!isdigit(ch))
	{
		ch=getchar();
	}
    while(isdigit(ch)) 
	{
		x=x*10+ch-'0',ch=getchar();
	}
    return x;
}
int main()
{
	n=read();k=read();
	for(long long i=1;i<n;i++)
	{
		a[i]=read();
		ans+=a[i];//统计总路径长度
		b[i]=b[i-1]+a[i];//统计前缀和
	}
	for(long long i=1;i<n;i++)
	{
		maxn=max(maxn,b[i]-b[i-k]);//统计长度为k的区间最大和
	}
	printf("%lld",ans-maxn);//用总长度减去区间最大长度即为答案
	return 0;
}
```

[提交记录](https://www.luogu.org/record/26705657)

---

## 作者：　　　吾皇 (赞：1)

最朴素的暴力做法 由于良心出题人数据范围极小，考虑枚举在2到n-k+1处传送所需的时间 这里使用前缀和维护

至于为什么是到n-k+1 ，因为$a_i>=0$ 所以$sum_{i+1}>=sum_i$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
#define ll long long
ll a[1000001],sum[1000001],ans=1000000000000000000;//这里设一个很大的数 
static char buf[100000],*pa=buf,*pb=buf;
#define gc pa==pb&&(pb=(pa=buf)+fread(buf,1,100000,stdin),pa==pb)?EOF:*pa++
inline ll read(){
    register ll x(0);register char c(gc);
    while(c<'0'||c>'9')c=gc;
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=gc;
    return x;
}//非常好用的读入优化
int main(){
	n=read(),k=read();
	for(register int i=2;i<=n;i++) a[i]=read(),sum[i]=sum[i-1]+a[i];//前缀和处理
	for(register int i=2;i<n-k;i++) ans=min(ans,sum[i-1]+sum[n]-sum[i+k-1]);//求最小值
	printf("%lld",ans);
}
```
$a_i$代表从$i-1$到$i$所需的时间 $sum_i $代表从1到$i$所需的时间

解释其中`sum[i]+sum[n]-sum[i+k]` ：  容易理解,在 $i$处传送时,前面走了一段，后面走了一段。 其中前面走的一段所需要的时间就为1到$i-1$的距离之和即$sum_{i-1}$;而后一段的时间则为$i+k$到$n$的距离之和，既然已经用前缀和维护了，则为$sum_n-sum_{i+k-1}$

---

## 作者：Kevin_Wa (赞：1)

### 题意解析

题目大意就是你有一个传送器，半径为$k$，能支持从$i$点传送到$i+k$或$i-k$，求$1-n$之间的行程最小。

这首先想到是暴力，枚举在每个点使用传送器，时间复杂度$O(n^2)$。

由于是静态所以用前缀和优化一下，时间复杂度$O(n)$。

注意开$long long$

### 评价

总感觉这题比红题要难吧。T2才算红题。

~~我才不会告诉你我开了火车头。~~

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll x,a[1000100],ans;
int n,k;
template <typename T> void read(T &x) {
x = 0; char c = getchar();int f=1;
for (; !isdigit(c); c = getchar()) if (c=='-') f=-1;
for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
x*=f;
}
void work(ll x,ll y)
{
	if (x<0) x=1;
	if (x>n) x=n;
	ll z=a[n]-a[x]+a[y];
	if (ans>z) ans=z;
}
int main()
{
//freopen(".in","r",stdin);
//freopen(".out","w",stdout);
read(n);read(k);
a[1]=0;
for (int i=1;i<=n-1;i++)
  {
  	read(x);
  	a[i+1]=a[i]+x;
  }
ans=1000000000000000000;
for (int i=1;i<=n;i++)
  {
  	work(i+k,i);
  	work(i-k,i);
  }
printf("%lld\n",ans);
return 0;
}
```


---

## 作者：羽儇 (赞：1)

输入的时候作个前缀和，同时比较下，找到耗费时间最大的一段路程，最后用总耗费时间将它减去即可

同时特判下$K == 0$ 的情况


------------


$ACcode$


------------

```cpp
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
int N,K,a,pre[2000000],maxs;
signed main()
{
	scanf("%lld%lld",&N,&K);
	for(int i = 2 ;i <= N ; i ++ )scanf("%lld",&a),pre[i] = pre[i - 1] + a,maxs = max(maxs,pre[i] - pre[max(i - K,0ll)]);
	if(K)printf("%lld",pre[N] - maxs);
	else printf("%lld",pre[N]);
	return 0;
}
```


---

## 作者：Crab_Dave (赞：0)

向左走是没有用的，我们只用考虑向右走

这里我们用一个类似滑动窗口的方法qwq

~~不知道为什么$O(N)$扫描会被卡两个点qwq~~~

我们寻找一段长度为$k$的最大区间，减去就行。

这里我们用一个前缀和优化。

详见代码qwq
```cpp
#include<cstdio>
#include<iostream>//头文件
using namespace std;//命名空间

long long n,k,a[1000005],ans,sum[1000005];

int main()
{
	scanf("%lld%lld",&n,&k);n--;//把n-1（习惯问题，意会就好）
	for(register long long i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];//读入和前缀和
	}
	if(k==0)
	{
		printf("%lld\n",sum[n]);//k==0就是sum[n]
		return 0;
	}
	if(k>=n)
	{
		printf("0\n");//k>=n就是0
		return 0;
	}
	long long l=1,r=l+k-1;//枚举区间[l,l+k-1]
	while(r<=n)
	{
		ans=max(ans,sum[r]-sum[l-1]);//前缀和查询最大区间
		l++,r++;//区间右移
	}
	printf("%lld\n",sum[n]-ans);//结果就是sum[n]减去最大区间
	return 0;//结束了罪恶的一生
}
```
写题解不易，还望支持qwq

---

## 作者：Purple_sword (赞：0)

题解：CSG Round2 T1 光骓者的荣耀

```cpp
本题策略：
贪心
先累加出所有高速公路所需时间之和，再减去长度为k的最大子段和即可
于是我们想到维护一个前缀和序列，遍历长度为k的子串，再找出最大值
```


```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1000005],ans,n,k;//要开longlong，谨记
int main(){
    scanf("%lld%lld",&n,&k);
    for(long long i=1;i<n;++i)
    	scanf("%lld",&a[i]),a[i]+=a[i-1];//输入+维护前缀和
    for(long long i=k;i<n;++i)//遍历子串，是k到n不是k-1到n！这直接导致我一直92分
    	ans=max(a[i]-a[i-k],ans);//更新最大k子串
    ans=a[n-1]-ans;//得到最小值
    printf("%lld",ans);
    return 0;
}
```

感觉比T2难诶，比赛一直92分。。

附比赛时的惨状：

![WA](https://cdn.luogu.com.cn/upload/image_hosting/ut0uvk74.png)

---

## 作者：Starlight237 (赞：0)

T1

本题的数据是保证没有负环的（似乎根本无负权边），故只需考虑从$i$跳到$\min\{n,i+k\}$的情况。

枚举跳跃点，用前缀和的方式求出对应的路径长度（因为整个图就是一条链），求最小值即可。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
#define IOSIZE 20000000
static char in[IOSIZE],*p=in,out[20],*q=out,ch[20],*t=ch;
inline long long read(){
	reg long long x=0;reg char f=0;
	while(*p<48)f|=*p++=='-';
	while(*p>47)x=(x<<1)+(x<<3)+(*p++^48);
	return f?-x:x;
}
inline void write(long long x){
	x<0&&(*q++='-',x=-x);
	!x&&(*q++='0');
	while(x)*t++=x%10+48,x/=10;
	while(t!=ch)*q++=*--t;
}
int n,k;
static long long s[1000001];
int main(){
	fread(in,1,IOSIZE,stdin);
	n=read(),k=read();
	for(reg int i=1;i<n;++i)s[i]=s[i-1]+read();
	long long mi=0x3f3f3f3f3f3f3f3f;
	for(reg int i=1;i<=n-k;++i)mi=min(mi,s[n-1]-s[min(n,i+k-1)]+s[i-1]);
	write(mi);
	fwrite(out,1,q-out,stdout);
	return 0;
}
```

---

## 作者：stywzh (赞：0)

#### 这个红题，卡了我半小时敢信！！！

------------
做法方面，我的做法~~可能很麻烦了~~；
具体做法就是类似于单调队列一样，维护一个窗口，每次把头上的元素去掉，加上尾部的元素，维护这个窗口的和，用取的和去维护一个最大值，用序列总和减掉这个最大值就可以了。。。
```cpp
#include<iostream>
#include<cstdio>
#define N 2000086
#define ll long long
using namespace std;

ll n,k,sum,q[N],head,tail,ans,a[N],tot;

int main()
{
	scanf("%lld%lld",&n,&k);
	for(ll i=1;i<n;i++)
	{
		scanf("%lld",&a[i]);
		sum+=a[i];
	}
	if(k==0)
	{
		printf("%lld\n",sum);
		return 0;
	}
	for(ll i=1;i<n+k;i++)
	{	
		q[++tail]=a[i];
		ans+=a[i];
		tot=max(tot,ans);
		if(tail<k)continue;
		ans-=q[++head];
		tot=max(tot,ans);
	}
	printf("%lld\n",sum-tot);
	return 0;
}
```
最后加了一个对0的特判。。
#### 信心赛警告

---

## 作者：Azazеl (赞：0)

蒟蒻在比赛最后半个小时才开始做的···交的时候数组少开了个0于是92->76

### 题意
给了你$n-1$个数，在一个地方$i$能没有花费地直接走到$i+k$或$i-k$(即跳过中间$k$个数),求这个最小花费  

### 题解  
很明显，我们设所有路的长度之和为$tot$,这个可以在输入时顺便统计。  
之后，根据题意跳过中间$k$个数，那么怎么跳呢，很明显的贪心就是跳过$k$条长度之和最长的路径  
这个很好统计，我会~~线段树~~前缀和，挨个统计即可，复杂度为$O(n-k+1)$  

### 代码
```
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
ll a[1000005],d[1000005];
int main() {
	ll n,k,tot=0;
	scanf("%lld %lld",&n,&k);
	for(int i=1;i<n;i++) 
	{
		scanf("%lld",&a[i]);
		tot+=a[i];	
		d[i]=d[i-1]+a[i];
	}
	if(k==0)
	{
		printf("%lld",tot);
		return 0;
	}
	ll maxn=-1;
	for(int i=1;i<=n-k+1;i++) maxn=max(maxn,d[i+k-1]-d[i-1]);
   	//我是不会告诉你之前我写成d[i+k]-d[i]了
	printf("%lld",tot-maxn);
	return 0;
}
```

---

## 作者：lby2006 (赞：0)

这道题的意思是一共有n条边组成的链，并且可以跳过k条边，然后求1到n距离的最小值。
所以我们可以用前缀和跑O(n)算法，毕竟一看n就是O(n)。
```cpp
#include<bits/stdc++.h>//万能头文件
#define ll long long
using namespace std;
const ll SIZE=1<<20;
inline char getch()
{
    static char buf[SIZE],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZE,stdin),p1==p2)?EOF:*p1++;
}//手动getchar();
inline ll rd()
{
    ll s=0,f=1;
    char c=getch();
    while(c>'9'||c<'0'){if(c=='-') f=-1;c=getch();}
    while(c>='0'&&c<='9'){s=(s<<1)+(s<<3)+c-'0';c=getch();}
    return s*f;
}//快读
ll n,k,a[1000010],sum[1000010],ans=1e18;//不开long long后果自负
int main()
{
    n=rd(),k=rd();//输入不解释
    for(int i=1;i<n;i++)a[i]=rd(),sum[i]=sum[i-1]+a[i];//前缀和QAQ
    for(int i=0;i<n;i++)ans=min(ans,sum[i]+(sum[n-1]-sum[min(i+k,n-1)]));//1到i的距离+(i+k)到n的距离，因为题目要求i+k>n时，i+k=n，所以还要加个min。
    printf("%lld\n",ans);
    return 0;
}
```
对于跑0到n-1是为什么，是因为，a[i]存的是i到i+1的距离，所以如果在1就跳过k就要从i=0开始，如果从0开始，92分。~~我被卡了10分钟~~

---

