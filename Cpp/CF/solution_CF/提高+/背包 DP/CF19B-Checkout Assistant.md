# Checkout Assistant

## 题目描述

Bob 来到一家现购自运商店，将 $n$ 件商品放入了他的手推车，然后到收银台付款。每件商品由它的价格 $c_i$ 和收银员扫描它的时间 $t_i$ 秒定义。

当收银员正在扫描某件商品时，Bob 可以从他的手推车中偷走某些其它商品。Bob 需要恰好 $1$ 秒来偷走一件商品。Bob 需要付给收银员的最少钱数是多少？请记住，收银员扫描商品的顺序由 Bob 决定。

## 样例 #1

### 输入

```
4
2 10
0 20
1 5
1 3
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3
0 1
0 10
0 100
```

### 输出

```
111
```

# 题解

## 作者：Silence_water (赞：113)

**[题目传送门](https://www.luogu.com.cn/problem/CF19B)**


------------

## 题目分析

本题是01背包的变形

从题目中我们可以得知一件商品 $i$ 扫描需要 $t_i$ 时间。

那么在扫描这件物品的同时我们可以偷走 $t_i$ 件物品。

也就是说，扫描物品 $i$ 一共能得到 $t_i+1$ 件物品。

那么问题就可以转化成这样的背包问题：

一共有 $n$ 件物品，第 $i$ 件物品的体积为 $t_i+1$，价值为 $c_i$。

那答案要去求的是什么呢？

假设我们一共付了 $k$ 个物品的钱，那么在前 $k-1$ 件物品中，

我们为了尽可能地得到更多的物品，会将能偷到的 $t_i$ 全部偷过来。

但到了扫描第 $k$ 件物品的时候，我们可能已经不需要全部偷过来了。

所以答案要求的是得到**至少** $n$ 件物品所需的最小价值。

因此我们可以推出背包的最大容量为 $t_{\max}+n$。

然后我们来观察一下数据范围：

$1≤n≤2000$，$1≤c_i≤10^9$
 
考虑当所有物品扫描时间 $t$ 都为 $0$ 时一件都偷不走。
 
此时答案的极限值为：$2000*10^9=2*10^{12}$。
 
因此 $ans$ 的初始值要设置为 $2*10^{12}$，我们需要开 $longlong$。

------------

## 代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm> 
using namespace std;
typedef long long ll;
const int M=2005,N=4005;
int n,t[M],v;
ll c[M],dp[N],ans=2e12;//注意ans的初始值 
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%lld",&t[i],&c[i]);
		t[i]++;//将t数组转换为用来存物品"体积" 
		v=max(v,t[i]);
	}
	v+=n;//算出最大体积 
	memset(dp,0x7f,sizeof(dp));dp[0]=0;//对dp数组进行初始化 
	for(int i=1;i<=n;i++)
		for(int j=v;j>=t[i];j--)
			dp[j]=min(dp[j],dp[j-t[i]]+c[i]);//01背包 
	for(int i=n;i<=v;i++)
		ans=min(ans,dp[i]);//在所有满足条件的物品个数中寻找耗费最少的方案 
	printf("%lld",ans);
    return 0;
}
```


------------
看懂了别忘点个赞在走ya

---

## 作者：这有一只匿 (赞：20)

零一背包的变式。完成任务是使所有物品全部买或偷到，而Bob有多少扫描时间便能偷多少物品，所以扫描了某一物品，能带走的物品便是扫描时间，加上1（也就是你正在扫描的这个物品），在这里可以直接把扫描时间++，那么现在扫描时间就等价与能带走的物品个数了。

之后我们将扫描时间看作体积，价格看作价值。那么题目便等价与把背包体积至少装至n的最小价值，就和01背包一样了。（注意数组初始化和数据范围，有些要开longlong）。还有把最大的体积限制为(t[i].max)+n（最大肯定不超过这个）。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int n,m;
int w[2100],c[2100];
long long f[4100],minn=1e18+7;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&w[i],&c[i]);
		w[i]++;
		m=max(m,w[i]);
	}
	m+=n;
	for(int v=1;v<=m;v++)
	f[v]=1e18+1;
	f[0]=0;
	for(int i=1;i<=n;i++)
	for(int v=m;v>=w[i];v--)
	{
	f[v]=min(f[v],f[v-w[i]]+c[i]);
	if(v>=n)minn=min(minn,f[v]);
	}
	cout<<minn;
	return 0;
}
```

---

## 作者：珅肐 (赞：11)

一道背包题

我们需要花最小代价把所有的物品都买到

稍微思考一下可以得知

扫描一件需要$t$时间的物品，可以得到$t+1$件物品（包括扫描的这件）

那么题目就变成了：n件物品，体积为$t[i]+1$，价值为$c[i]$，求体积至少为$n$的最小价值。

注意：体积最大值应设为$2n$。

#### 代码奉上：
```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
using namespace std;
inline int read(){//快读，可快了
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
int t[2007],c[2007];
long long f[4007],ans=1e18;//数组要开longlong
int main(){
	int n=read();
	for(int i=1;i<=n;++i)t[i]=min(n,read()+1),c[i]=read();//t[i]最大就是n，再多也没用
	for(int i=1;i<=n+n;++i)f[i]=1e18;//f[0]=0,其他赋极大值,保证背包填满
	for(int i=1;i<=n;++i)//普通0/1背包
		for(int j=n+n;j>=t[i];--j)
			f[j]=min(f[j],f[j-t[i]]+c[i]);
	for(int i=n+n;i>=n;--i)ans=min(f[i],ans);//找最小值
	printf("%lld\n",ans);//输出
	return 0;//好习惯
}

```


---

## 作者：formkiller (赞：5)

翻了下题解区怎么人均 01 背包啊，给出一种另类做法吧。
____

设 $f(i,j)$ 为前 $i$ 个物品处理完后剩下 $j$ 的时间的最小花费，那么不难有转移方程 $f(i,j) = \min\{f(i-1,j+1),f(i-1,j-t_i)+c_i\}$。因此答案应该为 $\min\limits_{i=0}\{f(n,i)\}$。同时注意到当 $t_i \ge n$ 时已经可以把所有的物品处理掉，因此 $t_i \ge n$ 时直接把 $t_i$ 赋成 $n$ 即可。

当然，由于物品可以按任意顺序处理，也就是**排在前面的物品可以被排在后面的物品一起处理**，那么我们可以用赊账的思想，先偷，找后面的物品还债。等价于先把后面的物品先处理，再处理当前物品。实现起来也很简单，因为会出现“剩下 $-1$ 的时间”的情况，所以做一个数组偏移即可。
___

### Code:

```cpp
//good luck
# include <iostream>
# include <cstdio>
# include <cmath>
# include <cstdlib>
# include <cstring>
# include <string>
# include <algorithm>
# include <vector>
# include <queue>
# include <ctime>
# include <map>

#define LL long long
#define maxn int(2e3+5)
#define is(a) (a>='0'&&a<='9')
#define iabs(a) ((a)>0?(a):(-a))
#define imax(a,b) ((a)>(b)?(a):(b))
#define imin(a,b) ((a)<(b)?(a):(b))

using namespace std;

const int n = 2000;

int N,c[maxn],t[maxn];
LL ans,f[maxn][maxn*2];

inline void read(int &x)
{
  x=0;bool f=0;char ch=getchar();
  for (;!is(ch);ch=getchar()) f|=ch=='-';
  for (;is(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
  x=f?-x:x;
}

int main()
{
//	freopen("a.in","r",stdin);
	read(N);
	for (int i = 1; i <= N; ++i)
		read(t[i]), read(c[i]), t[i] = imin(t[i],N);
	for (int i = 0; i <= N; ++i) 
		for (int j = 0; j <= N + n + 1; ++j) f[i][j] = 1e18;
	f[0][n] = 0;
	for (int i = 1; i <= N; ++i) {
		for (int j = t[i] - n; j <= N; ++j) {
			f[i][j+n] = imin(f[i-1][j-t[i]+n]+c[i],f[i-1][j+1+n]);
		}
	}
	ans = 1e18;
	for (int j = 0; j <= N; ++j){
		ans = imin(ans,f[N][j+n]);
	}
	printf("%lld\n",ans);
    return 0;
}


```


---

## 作者：2333tech (赞：3)

### 其实是一个01背包
如题，只要想到将题目转换为**标准01背包问题**即可快速解决  
观察题目时，我们会看到“偷”这个与普通背包不同之处，但是本题要求得到**所有**物品。  
题目要求得到所有物品并且求得最小价格。  
所以，我们要利用“偷”来取得**尽可能多**的物品，所以在求值时我们不一定要求正好偷到 $n$ 件，而理论上我们能带走的物品数目在  $n$ 与 $n+max(ti)$ 之间，所以在这个范围之间，我们能得到带走所有物品的最小价格。  
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, price[2020], s[2020];
long long maxN;
long long f[4040];//这里要注意，maxN的最大是会是 n + max(ti)；所以数组要定义为4001以上
long long ans = 2e12;//注意初始化为极大值
int main()
{
    scanf("%lld", &n);
    memset(f, 0x7f, sizeof f);//初始化
    f[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &s[i], &price[i]);
        s[i]++;//将扫描时间转化为可盗（带）走物品数
        maxN = max(maxN, s[i]);//设置背包容量上限
    }
    maxN += n;
    for (int i = 1; i <= n;i++) {
        for (int j = maxN;j >= s[i];j--) {
            f[j] = min(f[j], f[j - s[i]] + price[i]);//注意，本背包求的最小价格，所以“物品数”是重量，价格是“价值”。
        }
    }
    for (int i = n; i <= maxN;i++) {
        ans = min(ans, f[i]);//从最小可带走物品数 n 循环到最大可带走物品数 maxN 寻找最小价格。
    }
    printf("%lld\n", ans);
    return 0;
}
```



---

## 作者：红尘仙 (赞：1)

### 贪心错解 
首先一开始想的贪心。

既然题目支付钱数最小，那么我们就应该去求解偷的价值最大。那么我们就可以考虑，支付价值小的物品，偷价值大的物品。

实现就是按照价值从小到大排个序，购买价值小的物品，利用价值小的物品的时间去偷价值大的。

**不过是错误的**

那为什么是错误的呢？我们来一个极品数据

```
5 
0 1 
0 2
0 3 
0 4
10 5 
```
显然我只需要用 5 的价值就能够得到全部的物品，而贪心则是 15 。

那么也就说明，当前面价值小的物品的时间不足以支撑去偷后面价值大的物品，那么就是错误的。但是错误很显然，代码就不提供了。

### DP 正解

~~准确的来说，当 $n\leq 2000$ , 其实就该想 DP~~

然后转化一下题意，这是 01 背包 ？ 

然后我们直接考虑设 $f_i$ 表示耗时为 i 的获得的最小价值。那么我们显然就有状态转移 ：

$$f_i = \min(f_{i - t_j} + c_j)$$

### 一些坑点 ： （踩雷专家）

![](https://cdn.luogu.com.cn/upload/image_hosting/lzd7nl71.png)

 1. 因为这个物品需要扫描 1 秒后才能带走，所以我们这里背包的最大容量不是 $\max_{i = 1}^{n} t_i$ ，而是应该再加上 1 。
 
 2.  $f_1$ 不一定等于 $c_1$ ，挂了半年。
 
 3. 在最后统计答案的时候，需要将 ans 赋值成更大值，赋了 2147483647 调了半年。
 
 4. 最后统计答案的时候，答案应该是 $\min_{i = n} ^{Max} f_i$。



### Code

```
//支付的钱数最少，即为偷走的东西价值最大。 
/*
Author : Zmonarch
Knowledge :
*/
#include <bits/stdc++.h>
#define inf 2147483647
#define qwq register
#define qaq inline
#define int long long
using namespace std ;
const int kmaxn = 1e6 + 10 ;
const int N = 1e18 + 10 ;  
qaq int read() {
	int x = 0 , f = 1 ; char ch = getchar() ;
	while(!isdigit(ch)) {if(ch == '-') f = - 1 ; ch = getchar() ;}
	while( isdigit(ch)) {x = x * 10 + ch - '0' ; ch = getchar() ;}
	return x * f ;
}
int n , m , Max , sum; 
int t[kmaxn] , c[kmaxn] , f[kmaxn]; 
signed main() {
	n = read() ; 
	for(qwq int i = 1 ; i <= n ; i++) 
	t[i] = read() + 1 , c[i] = read() , Max = max(Max , t[i]); 
	Max += n ; 
	memset(f , 0x7f7f7f7f , sizeof(f)) ;  
	f[0] = 0 ; 
	for(qwq int i = 1 ; i <= n ; i++) 
	{
		for(qwq int j = Max; j >= t[i] ; j--) 
		{
			f[j] = min(f[j] , f[j - t[i]] + c[i]) ; 
		} 
	}
	int ans = N ; 
	for(qwq int i = n ; i <= Max ; i++) ans = min(ans , f[i]) ; 
	printf("%lld\n" , ans) ; 
	return 0 ;
}
```

---

## 作者：Rice_Porridge (赞：1)


这道题和01背包差不多，把一次性能带走的物品个数当做背包空间即可。

所以得到了dp方程：

dp[j]=min(dp[j],dp[max(j-t[i],0)]+c[i]);

所以有dp过程：
```cpp

for(register long long i=1;i<=n;i++){
	for(register long long j=n;j>=1;j--){
		dp[j]=min(dp[j],dp[max(j-t[i],o)]+m[i]);
	}
}
 ```   

关于max(j-t[i],0)的意思就是指当目前的物品结账时间如果已经大于了总物品数时。那么就直接用dp的第i次能拿走的物品数位加当前价值了（dp的第0位不会被访问所以始终为零）。

接下来便是我们可爱的代码

------------

```cpp
#include<bits/stdc++.h>
using namespace std;	

long long dp[2001]={};
long long o=0;
long long n;
long long t[2001]={},m[2001]={};

int main(){	
	scanf("%lld",&n);
	for(register long long i=1;i<=n;i++){
		dp[i]=1e18;
	}
	for(register long long i=1;i<=n;i++){
		scanf("%lld%lld",&t[i],&m[i]);
		t[i]+=1;
	}
	for(register long long i=1;i<=n;i++){
		for(register long long j=n;j>=1;j--){
			dp[j]=min(dp[j],dp[max(j-t[i],o)]+m[i]);
		}
	}
	printf("%lld\n",dp[n]);
	return 0;
} 
```
求过QAQ

---

## 作者：傅思维666 (赞：1)

## 题解：

~~Bob：读书人的事，能叫偷么~~

看到时间和物品数同级别，给了蒟蒻一丝丝灵感。那么很容易设置一个二维状态，$dp[i][j]$表示前i件物品耗时j的最小钱数。蒟蒻一开始以为这样的状态是不合法的，因为蒟蒻以为第二维的枚举范围是$\sum t_i$。但是给了你时间你不去偷，还等着结账，那不是纯傻么。

所以对于一个物品来讲，你交了这一份物品的钱，你能拿走的物品数是$t[i]+1$，也就是结账的时候你尽其所能地偷，最后你还能把这份交了钱的带走。

芜湖？好像像一个背包模型。钱就是价值，体积就是物品数。问题可以转化成至少拿走n个物品的最小价值。为什么是最少而不是恰好呢？因为我们讲对于一份物品的结账过程，最多可以拿$t[i]+1$，我们为了最优肯定往最多了拿，但是可能到最后一件需要结账的物品时，不用拿这么多就可以了。所以是最少，而不是恰好。并且，通过这个思路，我们可以确定最终答案的统计上限是：$t_{\max}+n$。

于是就是~~普普通通~~（fcq警告）的背包了。就是这个问题转化让它变成了蓝题。

警告要开longlong，这个家伙让我在11号点见了好多次祖宗。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
const int maxn=2010;
const int maxm=4010;
const ll INF=9187201950435737471;
int n,maxx;
ll ans=INF;
int t[maxn],c[maxn];
ll dp[maxn][maxm];
//dp[i][j]表示前i件物品耗时j的最小金额
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&t[i],&c[i]);
		t[i]++;
		maxx=max(maxx,t[i]);
	}
	maxx+=n;
	memset(dp,127,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=maxx;j++)
			if(j<t[i])
				dp[i][j]=dp[i-1][j];
			else
				dp[i][j]=min(dp[i-1][j],dp[i-1][j-t[i]]+c[i]);
	for(int i=n;i<=maxx;i++)
		ans=min(ans,dp[n][i]);
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：GGGabc (赞：1)

有一说一这就是一个01背包问题,唯一要注意的是ti需要++，可以理解成带走其他ti件物品后又加上它本身，然后其他都写在代码里了...
```c
#include <stdio.h>
long long min(long long a,long long b)
{
    return a>b?b:a;
}
int main()
{
    int n=0,i=0,j=0;
    long long ti[2005]={0},ci[2005]={0},v[4010]={0},minn=1e18;
    scanf("%d",&n);
    for(i=1;i<=n;i++)//输入每个商品的时间和价值
    {
        scanf("%lld%lld",&ti[i],&ci[i]);
        ti[i]++;//每次扫描都可带走本物品,为了方便理解可以是偷走本物品
    }
    for(i=1;i<=2*n;i++)//先赋予一个极大值,确保背包填满
    {
        v[i]=1e18;
    }
    for(i=1;i<=n;i++)//遍历每一种情况,给出是否填入的意见
    {   //从小到大算防止一个物品多次运算
        for(j=n-1;j>=0;j--)//当其填入时，如果先前该位置已有填入则是他们的和,如没有该位置还是个极大值不影响后面的判断
        {
            v[ti[i]+j]=min(v[ti[i]+j],v[j]+ci[i]);
        }
    }
    for(i=n;i<=2*n;i++)//找出最小值
    {
        minn=min(minn,v[i]);
    }
    printf("%lld",minn);
    return 0;
}
```


---

