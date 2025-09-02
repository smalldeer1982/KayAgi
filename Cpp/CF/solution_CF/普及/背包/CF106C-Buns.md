# Buns

## 题目描述

Lavrenty, a baker, is going to make several buns with stuffings and sell them.

Lavrenty has $ n $ grams of dough as well as $ m $ different stuffing types. The stuffing types are numerated from 1 to $ m $ . Lavrenty knows that he has $ a_{i} $ grams left of the $ i $ -th stuffing. It takes exactly $ b_{i} $ grams of stuffing $ i $ and $ c_{i} $ grams of dough to cook a bun with the $ i $ -th stuffing. Such bun can be sold for $ d_{i} $ tugriks.

Also he can make buns without stuffings. Each of such buns requires $ c_{0} $ grams of dough and it can be sold for $ d_{0} $ tugriks. So Lavrenty can cook any number of buns with different stuffings or without it unless he runs out of dough and the stuffings. Lavrenty throws away all excess material left after baking.

Find the maximum number of tugriks Lavrenty can earn.

## 说明/提示

To get the maximum number of tugriks in the first sample, you need to cook 2 buns with stuffing 1, 4 buns with stuffing 2 and a bun without any stuffing.

In the second sample Lavrenty should cook 4 buns without stuffings.

## 样例 #1

### 输入

```
10 2 2 1
7 3 2 100
12 3 1 10
```

### 输出

```
241```

## 样例 #2

### 输入

```
100 1 25 50
15 5 20 10
```

### 输出

```
200```

# 题解

## 作者：0x3F (赞：15)

显然（RXZ 老师上课讲了），**做包子的顺序不会改变答案**。

所以可以**按顺序来**，也就是先做没有馅的第 $0$ 种包子，再做第 $1$ 种，再做第 $2$ 种，一直做到第 $m$ 种。

显然第 $i$ 种包子最多可以做 $\lfloor\frac{a_i}{b_i}\rfloor$ 个，所以跑**这么多遍 $0-1$ 背包**即可。

没有馅的第 $0$ 种包子最多可以做 $\lfloor\frac{n}{c_0}\rfloor$ 个，枚举上来即可。

还有我这里为了~~践行中央提出的“厉行节约，反对浪费”这一要求~~好写，$dp_i$ 表示**恰好**使用 $i$ 克面团最多赚的钱。

所以需要从头到尾**再扫一遍**。

时间复杂度 $\Theta(n\Sigma_{i=1}^{m}\lfloor\frac{a_i}{b_i}\rfloor)$ 约为 $\Theta(10^6)$ 即 $\Theta(\texttt{能过})$。

见短的不能再短的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a, b, c, d, dp[1010], ans;
int main() {
	cin >> n >> m >> c >> d;
	for (int i = 1; i <= n/c; i++) dp[i*c] = i*d;
	while (m--) {
		cin >> a >> b >> c >> d;
		for (int t = 1; t <= a/b; t++) {
			for (int i = n; i >= c; i--) {
				dp[i] = max(dp[i], dp[i-c] + d);
			}
		}
	}
	for (int i = 1; i <= n; i++) ans = max(ans, dp[i]);
	cout << ans << endl;
	return 0;
}
```

$$\huge{\texttt{\color{white}{求过，求赞}}}$$

---

## 作者：StupidSeven (赞：5)

## Subject
[题目传送门](https://www.luogu.com.cn/problem/CF106C)

## Analysis
这题要我们求出最大收益，考虑动态规划求解。

那么先考虑设计状态， $dp[a][b][c][d]$… 表示还剩第一种馅 $a$ 克，第二种馅 $b$ 克…以此类推。

开了个小玩笑，这么设计状态肯定不行，那我们就根据题目的特性，简化状态，设 $dp[k][now]$ 表示只做前 $k$ 种面包还剩 $now$ 克面团时的最大收益，那么状态转移方程比较好推，每次枚举做多少个当前种类的面包，就是多重背包啦。

- $dp[k][now]=\max(dp[k][now],dp[k-1][now-i*c[k]]+i*d[k])$

记住，每次转移的时候都要确保当前种类的馅料和面团都够，毕竟缺斤少两可不好。

最后还要考虑剩下的面团能做的无馅面包获得的收益，最后循环一遍取最大值就好了。

## Code
```cpp
#include<queue>
#include<cmath>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<functional>
using namespace std;
#define int long long
const int M=1e2+10;
const int N=1e3+10;
const int inf=1e9;
const int Mod=1e9+7;
inline int Read(void){
    int s=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){s=s*10+c-48;c=getchar();}
    return s*f;    
}
int n,m,c0,d0;
int a[M],b[M],c[M],d[M];
int dp[M][N],ans;
signed main(void){
    n=Read();m=Read();c0=Read();d0=Read();
    for(int i=1;i<=m;i++){
        a[i]=Read();b[i]=Read();c[i]=Read();d[i]=Read();
    }
    for(int k=1;k<=m;k++)
        for(int now=0;now<=n;now++)
            for(int i=0;i*b[k]<=a[k]&&i*c[k]<=now;i++)
                dp[k][now]=max(dp[k][now],dp[k-1][now-i*c[k]]+i*d[k]);
    for(int i=0;i<=n;i++) ans=max(ans,dp[m][i]+(n-i)/c0*d0);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Yeji_ (赞：4)

## 前言
背包问题真的难（做的心态崩了）
## 想法
之前，在做背包专题，所以自然而然的就想到混合背包了

这题可以用两种写法来写。

## 第一种
我们将分$f[i]$设为i个c0可产生的价值

再将题意中给的量转换为多重背包的模板，

其实模板大家都会打，但是很多人不会做，是因为不能将题目中给出的量，准确的转换为模板

所以这种能力大家需要根据做题来领会

代码如下
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int f[10010],n,m,c0,d0,a[10200],b[10200],c[10200],d[10200];
int main()
{
    cin>>n>>m>>c0>>d0;
    for (int i=c0;i<=n;i++)
    	f[i]=i/c0*d0;//n个面包的价值比 
    for (int i=1;i<=m;i++)
    {
        cin>>a[i]>>b[i]>>c[i]>>d[i];
        for (int j=1;j<=a[i]/b[i];j++)
        	for (int k=n;k>=c[i];k--)
        	    f[k]=max(f[k-c[i]]+d[i],f[k]);
    }
    cout<<f[n];
}
```
## 第二种
这种方法更适合用于初学者身上

代码还是非常的简单，直接网上套
```cpp
#include <cstdio>
#include <iostream>
using namespace std； 
int n,m,ans,a[2500],b[2500],c[2500],d[2500],f[100][2500];
int main()
{
    scanf("%d%d%d%d",&n,&m,&c[0],&d[0]);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
    for (int i=0;i<=m;i++) 
        for (int j=0;j<=n;j++) 
            for (int k=0;k*c[i]<=n&&k*b[i]<=a[i];k++) 
                if (j>=k*c[i])
                    f[i%2][j]=max(f[i % 2][j],f[(i+1)%2][j-k*c[i]]+k*d[i]); 
    printf("%d",f[m%2][n]);
}
```


---

## 作者：Victorique_De_Blois (赞：2)

这一题目用背包

**dp[ i ][ j ][ k ],表示i种佐料使用j*c克混合k克面粉生成的价值，第i种佐料我们可以使用for循环控制，j*b克的i面粉跟k克的佐料是对应的，也就是说dp的值是由最后一维控制的，所以j*b也可以由循环表示，所以最后的dp是一维的.**

代码：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int dp[12000];
int num[200];
int gram[200];
int value[200];
int n,m;
inline int max(int a,int b)
{
	return a>b?a:b;
}
int main()
{
	int a,b;
	int x,y,z,w;
	scanf("%d%d",&n,&m);
	scanf("%d%d",&a,&b);
	for(register int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&x,&y,&z,&w);
		num[i]=x/y;
		gram[i]=z;
		value[i]=w;
	}
	gram[0]=a;
	value[0]=b;
	num[0]=n/a;
	memset(dp,0,sizeof(dp)); 
	for(register int i=0;i<=m;i++)
	     for(register int j=1;j<=num[i];j++)
	     	for(register int k=n;k>=gram[i];k--)
	     		dp[k]=max(dp[k],dp[k-gram[i]]+value[i]);
	printf("%d\n",dp[n]);
	return 0;
} 	
```



---

