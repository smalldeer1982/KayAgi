# [USACO11DEC] Umbrellas for Cows S

## 题目描述

Today is a rainy day! Farmer John's N (1 <= N <= 5,000) cows, numbered 1..N, are not particularly fond of getting wet. The cows are standing in roofless stalls arranged on a number line. The stalls span X-coordinates from 1 to M (1 <= M <= 100,000). Cow i stands at a stall on coordinate X\_i (1 <= X\_i <= M). No two cows share stalls.

In order to protect the cows from the rain, Farmer John wants to buy them umbrellas. An umbrella that spans coordinates X\_i to X\_j (X\_i <= X\_j) has a width of X\_j - X\_i + 1. It costs C\_W (1 <= C\_W <= 1,000,000) to buy an umbrella of width W.  Larger umbrellas do not necessarily cost more than smaller umbrellas.

Help Farmer John find the minimum cost it takes to purchase a set of umbrellas that will protect every cow from the rain.  Note that the set of umbrellas in an optimal solution might overlap to some extent.


在 X 数轴上有 M 个整数点，点的坐标分别是 1 至 M。有 N（1<= N<= 5000）只奶牛，编号为 1.. N，第 i 只奶牛所在的整数点坐标是 Xi（1<= Xi <= M <= 100,000）, 没有两头奶牛在相同的点上。现在正在下雨，为了保护奶牛，FJ 需要购买很多把雨伞，把所有的奶牛都遮住。如果一把雨伞能遮住坐标是 a 到坐标是 b 的这一段（a<=b），那么这把雨伞的宽度就是 b-a+1。现在我们给出购买宽度是 1 的雨伞的价格，购买宽度是 2 的雨伞的价格，…购买宽度是 M 的雨伞的价格。

这里特别需要注意：宽度更大的雨伞的价格不一定超过宽度较小的雨伞，这完全取决于读入数据。你的任务是帮助 FJ 找到购买雨伞最低的成本，使得这些雨伞能把所有的奶牛遮住，从而不淋雨。需要注意的是最佳的解决方案雨伞可能会重叠。


## 说明/提示

There are 12 stalls, and stalls 1, 2, 4, 8, 11, and 12 contain cows. An umbrella covering one stall costs 2, an umbrella covering two stalls costs 3, and so on.


By purchasing a size 4 umbrella, a size 1 umbrella, and a size 2 umbrella, it is possible to cover all the cows at a cost of 4+2+3=9:

UUUUUUUUUU           U        UUUU

C  C     C           C        C  C

|--|--|--|--|--|--|--|--|--|--|--| 
1  2  3  4  5  6  7  8  9  10 11 12

C represents a cow and U represents a part of an umbrella.


1、 买一把长度是 4 的雨伞去遮住坐标在 1、2、4 的三头奶牛，费用是 4；

2、 买一把长度是 1 的雨伞遮住坐标在 8 的奶牛，费用是 2；

3、 买一把长度是 2 的雨伞遮住坐标在 11、12 的两头奶牛，费用是 3。

总费用是 4 +2+ 3 = 9。


## 样例 #1

### 输入

```
6 12 
1 
2 
11 
8 
4 
12 
2 
3 
4 
4 
8 
9 
15 
16 
17 
18 
19 
19 
```

### 输出

```
9 
```

# 题解

## 作者：LlLlCc (赞：5)

## 题意：
给定n个点，坐标为1~m之间的正整数且互不相同，现在要求用一段或多段线段将n个点覆盖，每种长度的线段都有一个价格（不满足单调性），求出最小价格

------------
看完题目第一想法就应该是DP，贪心应该是不行的

- #### 定义 $f$ 数组：
这题的定义还是很容易想到的，$f[i]$表示将前$i$个的覆盖所需要的最小价值，而答案就是$f[n]$了

- #### 转移方程：
易得：$f[i]$ $=$ $f[j-1]$ $+$ $cost[a[i]-a[j]+1]$

其中$a[i]$表示第$i$个点的位置，$cost[i]$表示长度为$i$的线段的价格

但题目明确指出，长度增加价格未必会增加，也就是说有可能更长的线段的价格反而比长度为$a[i]-a[j]+1$的便宜

因为只要长度比$a[i]-a[j]+1$更长就能覆盖，所以我们只要在$cost[a[i]-a[j]+1]$ ~ $cost[m]$选一个最小值即可，最小值怎么找？每次都$O(n)$找一遍？显然会超时，一个很简单**最小后缀值**提前预处理一遍就行了

详见代码：
```
#include<bits/stdc++.h>
#define maxn 200005
using namespace std;
int n,m,f[maxn],Ans,lst[maxn],a[maxn],v[maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-f;ch=getchar();}
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
	n=read(),m=read();memset(f,63,sizeof f);f[0]=0;
	for (int i=1;i<=n;i++) a[i]=read();sort(a+1,a+n+1);
	for (int i=1;i<=m;i++) v[i]=read();v[0]=1<<30;lst[m+1]=1<<30;
	for (int i=m;i>=0;i--) lst[i]=min(v[i],lst[i+1]);
	for (int i=1;i<=n;i++)
		for (int j=i;j;j--) f[i]=min(f[i],f[j-1]+lst[a[i]-a[j]+1]);
	printf("%d",f[n]);
	return 0;
}
```


---

## 作者：双管荧光灯 (赞：3)

很显然的dp

记f[i]为遮住1~i的奶牛最少花费

f[i]=max(f[j-1]+(遮住至少x[i]-x[j]+1个点的花费))

(遮住至少x[i]-x[j]+1个点的花费)怎么算？它等于a[x[i]-x[j]+1]~a[m]的最小值，

那么用一下后缀最小值就行了

Code:
```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include <algorithm>
using namespace std;
int n,i,j,a[100005],m,x[10005],ans[10005];
int main(){
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++)
        scanf("%d",&x[i]);
    sort(x+1,x+1+n);
    for(i=1;i<=m;i++)
        scanf("%d",&a[i]);
    for(i=m-1;i>=1;i--)
        a[i]=min(a[i],a[i+1]);
    for(i=1;i<=n;i++)
    {
        ans[i]=1<<29;
        for(j=i;j>=1;j--)
            ans[i]=min(ans[i],ans[j-1]+a[x[i]-x[j]+1]);
    }
    printf("%d",ans[n]);
}

```

---

## 作者：first_fan (赞：2)

## >此题是一个典型的动态规划
#### >题目翻译：给出数轴上n个点的坐标，用长度为1~m的线段覆盖每个点，每个长度的线段均有一个代价C[i]，求覆盖所有点所需最小代价和。

------------

## >思路
### 1.将牛按照位置顺序sort
### 2.扫一遍雨伞价格，如果一个伞它又短又贵，则同化它，即用比它长且比它便宜的伞的价格 $\color{red}\text{代替其原来价格}$，就是说直接吞掉不划算的伞~~（其实可以不要这一步）~~
### 3.定义dp数组,dp[i]用于表示要盖住第i头牛所需最小代价
### 4.初始化dp[1~n]=∞
### 5.列动态转移方程:

$\color{red}\text{dp[i]=min(dp[i],dp[j-1]+umb[cow[i]-cow[j]+1]);}$
### 这里的 i 从 1 到 n ,而 j 则是从 i 到 1
## DP一遍之后就结束了嗯
### 这是我的代码????注释应该很清楚了
```
#include <bits/stdc++.h>
#define ll long long //I'm lazy QwQ
using namespace std;
const int maxn=10005;
int n,m;//n & m:amount of cows and umbrellas

int umb[maxn*10];//umb[i]:prices of umbrellas covers length of i;
int cow[maxn];//positions of cows
ll dp[maxn];//dp[i]:least cost of covering from 0 to the i th cow
const ll inf=1e12+1;

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++)
	{
		scanf("%d",&cow[i]);
	}
	sort(cow+1,cow+1+n);
	for(int i=1; i<=m; i++)
	{
		scanf("%d",&umb[i]);
	}//input above
	
	for(int i=m; i>=0; i--)
	{
		umb[i-1]=min(umb[i-1],umb[i]);
	}//cut off the useless umbrellas
	
	for(int i=1; i<=n; i++)
	{
		dp[i]=inf;//initate the array dp
		for(int j=i; j>=1; j--)
		{
			dp[i]=min(dp[i],dp[j-1]+umb[cow[i]-cow[j]+1]);
		}//dynamic programming…
	}　
	
	printf("%lld",dp[n]);//output the answer
}
```
# 撒花*★,°*:.☆(￣▽￣)/$:*.°★* 。

---

## 作者：winmt (赞：2)

我来发第一个题解！此题DP!

dp[i]代表覆盖钱i头牛的最小价值。

预处理：先要将牛的位置从小到大排序；val也要相邻比较大小，从而方便处理。。。

然后dp[i]=min(dp[i],dp[j]+val[pos[i-1]-pos[j]]) {j=0~i,pos为牛的位置，val为价值}



    
        
```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>
#include<deque>
#include<utility>
#include<map>
#include<set>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<sstream>
#include<cstring>
#include<bitset>
#include<stack>
using namespace std;
int n,m;
int pos[5005],val[100005];
long long dp[5005];
int main()
{
    //freopen("umbrella.in","r",stdin);
    //freopen("umbrella.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)scanf("%d",&pos[i]);
    for(int i=0;i<m;i++)scanf("%d",&val[i]);
    sort(pos,pos+n);
    for(int i=1;i<=n;i++)dp[i]=1e18;
    for(int i=m-2;i>=0;i--)val[i]=min(val[i],val[i+1]);
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<i;j++)dp[i]=min(dp[i],dp[j]+val[pos[i-1]-pos[j]]);
    }
    cout<<dp[n]<<endl;
    return 0;
}
```

---

## 作者：King_of_gamers (赞：1)

一个很~~水~~的DP题

f[i]表示用雨伞覆盖前i头牛的最小花费,那么f[i]就由f[j]+cost[c[i]- 
c[j]]得来,其中cost[i]表示长度为i的雨伞花费,c[i]表示第i头牛的位置.

```pascal
f[i]:=min(f[i],f[j-1]+cost[c[i]-c[j]+1]);
```

要注意的一点是当我们覆盖长度为i的一些牛时,可以用长度大于等于i的伞去覆盖,而且长度大于i的居然比长度等于i的便宜......

那么就是
```pascal
for i:=1 to m do
read(cost[i]);
for i:=m-1 downto 1 do
cost[i]:=min(cost[i],cost[i+1]);
```

最后给出我的AC代码

```pascal
var
        i,j:longint;
        n,m:int64;
        c,cost,f:array[0..100000]of int64;
function min(a,b:int64):int64;
begin
        if a<b then exit(a) else exit(b);
end;
procedure swap(var a,b:int64);
var
        c:int64;
begin
        c:=a;
        a:=b;
        b:=c;
end;
procedure sort(l,r:int64);
var
        i,j,mid:int64;
begin
        i:=l;
        j:=r;
        mid:=c[(l+r)>>1];
        repeat
                while c[i]<mid do inc(i);
                while c[j]>mid do dec(j);
                if i<=j then
                begin
                        swap(c[i],c[j]);
                        inc(i);
                        deC(j);
                end;
        until i>j;
        if i<r then sort(i,r);
        if l<j then sort(l,j);
end;
begin
        read(n,m);
        for i:=1 to n do
        read(c[i]);
        for i:=1 to m do
        read(cost[i]);
        for i:=m-1 downto 1 do
        cost[i]:=min(cost[i],cost[i+1]);
        sort(1,n);
        for i:=1 to n do
        begin
                f[i]:=cost[c[i]-c[1]+1];
                for j:=2 to i do
                f[i]:=min(f[i],f[j-1]+cost[c[i]-c[j]+1]);
        end;
        writeln(f[n]);
end.
```

---

## 作者：Unordered_OIer (赞：0)

# P3035 题解
            一道很明显的动归。
不多说，直接分析：  
$dp_i$表前i个的覆盖所需要的最小价值  
答案:$dp_n$  
状态转移方程：
$$dp_i=min(dp_i,dp_{j-1}+CST_{x_i-x_j+1})$$
注意动归的时候$dp_i$要设置成$inf$
```cpp
//
// 前置说明：我写那么多函数，只是为了查错方便而已。 
//
#include<bits/stdc++.h>
// #include<...> 
using namespace std;
// 前置 
const int sz1=10005;
const int sz2=100005;
const int inf=1<<29;
// 数据设置 
int n,i,j,CST[sz2],m,x[sz1],D_P[sz1];
// 定义变量 
void getnm(\)
{
	scanf("%d %d",&n,&m);
}
// getin 
void getx(\int n)
{
	for(i=1;i<=n;i++)scanf("%d",&x[i]);
	sort(x+1,x+1+n);
}
// getin 
void getC(\int m)
{
	for(i=1;i<=m;i++)scanf("%d",&CST[i]);
	for(i=m-1;i>=1;i--)CST[i]=min(CST[i],CST[i+1]);
}
// getin 
void getall(\)
{
	getnm();
	getx(n);
	getC(m);
}
// getin 
void in_and_sort(\){getall();}
// getin 
void Dynamic_Programming(\)
{
	for(i=1;i<=n;i++){
		D_P[i]=inf;
// set D_P[i] 
		for(j=i;j>=1;j--)
			D_P[i]=min(D_P[i],D_P[j-1]+CST[x[i]-x[j]+1]);
// dynamicprogramming 
	}
}
// main↓ 
int main(\)
{
	//////////////
//	freopen("umbrella.in","r",stdin);
//	freopen("umbrella.out","w",stdout);
// file
	//////////////
	in_and_sort(\); // getin
	Dynamic_Programming(\); // dynamicprogramming
	//////////////
	printf("%d",D_P[n]); // print
	//////////////
	return 0; // return
}
```

---

