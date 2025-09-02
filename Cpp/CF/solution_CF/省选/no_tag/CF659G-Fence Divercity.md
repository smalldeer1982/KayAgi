# Fence Divercity

## 题目描述

Long ago, Vasily built a good fence at his country house. Vasily calls a fence good, if it is a series of $ n $ consecutively fastened vertical boards of centimeter width, the height of each in centimeters is a positive integer. The house owner remembers that the height of the $ i $ -th board to the left is $ h_{i} $ .

Today Vasily decided to change the design of the fence he had built, by cutting his top connected part so that the fence remained good. The cut part should consist of only the upper parts of the boards, while the adjacent parts must be interconnected (share a non-zero length before cutting out of the fence).

You, as Vasily's curious neighbor, will count the number of possible ways to cut exactly one part as is described above. Two ways to cut a part are called distinct, if for the remaining fences there is such $ i $ , that the height of the $ i $ -th boards vary.

As Vasily's fence can be very high and long, get the remainder after dividing the required number of ways by $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

From the fence from the first example it is impossible to cut exactly one piece so as the remaining fence was good.

All the possible variants of the resulting fence from the second sample look as follows (the grey shows the cut out part):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF659G/a2b3bf8825e8935004832f4f03b0b46a19d70316.png)

## 样例 #1

### 输入

```
2
1 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3
3 4 2
```

### 输出

```
13
```

# 题解

## 作者：一濑红莲 (赞：6)

$F[i][j]$表示前 i 列且第i 列保留 j 高度的方案数。

怎么转移？
我们可以发现保留 j 高度的木板，它上面的木板一定已经被砍掉了，所以可以只通过前 i-1 列转移过来。

那么第i-1列砍掉部分是否可以与第i列砍掉的部分相连？分类讨论：

 ①$h[i-1]<=j$ , 第i-1列的高度都达不到第i列被砍掉的高度，这种情况不能转移。 F[i][j]+=0;

②$h[i-1]>j$   第i-1列砍掉的高度将会大于第i列保留的高度。此时F[i][j]+=$\sum_{k=1}^{min(h[i-1]-1,h[i]-1)}F[i-1][k]$
 
初始化：$F[i][j]=1 (1<=i<=n,1<=j<h[i]) $表示仅砍掉这一列，且只保留j的木板时的方案数，显然是1。

那么用ans来记录最终答案，就是：

$ans=sigma(F[i][j]) (1<=i<=n,1<=j<h[i])$

显然$F[i-1][k]$可以用前缀和来记录，所以时间复杂度可以优化到$O（NH）$
又因为dp方程只有上一维更新过来，所以可以用滚动数组或者直接删除第一维，来优化空间

```cpp
for(register int i=1;i<=n;++i){
        for(register int j=1;j<=h[i]-1;++j){
            if(i==1) f[i][j]=1;
                else if(h[i-1]<=j) f[i][j]=1;
                    else {
                        f[i][j]=1;
                        f[i][j]=(f[i][j]+g[i-1][min(h[i-1]-1,h[i]-1)])%mod;
                    }
            g[i][j]=(g[i][j-1]+f[i][j])%mod;
            ans=(ans+f[i][j])%mod;
        }
    }
    printf("%d",ans%mod)
```


但是这样写只能过3个点。

考虑一下特殊情况，每个木板高度相等时，记为H。
只取走第i列的方案数为 （H-1）

取一个区间 L 到 R ，强制其中每块木板都要有部分被砍，则方案数为$(H-1)^{(R-L+1)}$  ，因为其中每一列都有$（H-1）$的方案数，且共有$(R-L+1)$列。

所以总方案数就是枚举区间长度k，并且求和就可以了，用ans记录最终答案：

ans=$\sum_{k=1}^{n}((H-1)^{k}*(n-k+1))$

特判hi相同的情况，可以用快速幂处理一下，发现多AC了7个点，也就是说有7个点是这种特殊情况......（好水）

现在来看一般情况

因为题目要求至少保留1的高度，那么我们将所有的hi减一

根据上面的特殊情况，我们来枚举区间。取区间L到R，求这个区间每一列都必须有被砍的部分的方案数。第L列（左端点）被砍的话要与第L+1列连接起来，则其方案数为min($h\tiny{L}$ , $h\tiny{L+1}$ )

L<i<R 时，第i列被砍的要与第i-1列和第i+1列连接起来，则其方案数为min($h\tiny{i-1}$ , $h\tiny{i}$ , $h\tiny{i+1}$)

所以区间L到R方案数为$(\prod_{i=L+1}^{R-1}min(h\tiny{i-1}$ , $h\tiny{i}$ , $h\tiny{i+1}$))+$min($$h\tiny{L}$ , $h\tiny{L+1}$ )+$min($$h\tiny{R}$ , $h\tiny{R-1}$ )

同样我们可以枚举所有区间来求得总方案数，时间复杂度为O($n^{2}$)，显然会TLE

看了看数据范围，$hi$<=1e9。直觉告诉我们hi不能加入dp维度。这要么是一个O(N)的dp要么是个矩阵优化。

首先排除矩阵优化，F[i]表示前i列且强制第i列要有被砍的部分的方案数。

归纳上述公式，可得$F[i]=min(h[i],h[i-1])*F[i-1]+h[i]$
 
其中加上$h[i]$是表示前$i-1$列不被砍，只有第i列被砍的方案数。

想一想，这个转移方程是不是有不妥之处？

显然，我们并不知道$h[i+1]$的情况，也就是说$F[i+1]$T 中记录的方案数，可能包含了第i列只砍了第i+1列的高度的以上的部分，两列砍的部分不能连接，这样会多记不合法方案数。换句话说，这个dp方程$F[i]$不能用来直接更新$F[i+1]$

要想获得$F[i+1]$正确值，只需要知道在计算$F[i]$时，第$i+1$列是否有被砍的部分。并不需要获得第$i+1$列被砍的具体情况,如果有被砍的部分，第$i$列必须与第$i+1$列连接，而如果没有，就只要与第$i-1$列连接起来就行了。

那么我们可以再加一维，以添加转移的限制。$F[i][0/1]$ , 0表示第$i+1$列不砍，1表示第$i+1$列必须砍，这个dp状态同样表示了前$i$列且第$i$列必须砍的方案数，只不过添加了第$i+1$列的状态。

	初始化：F[1][1]=min(h[1],h[2]);F[1][0]=h[1];

	转移：F[i][1]=min(h[i],h[i+1])+min(h[i],h[i+1],h[i-1])*F[i-1][1]

	其中min(h[i],h[i+1])表示只砍第i列的方案数

	F[i][0]=h[i]+min(h[i],h[i-1])*F[i-1][1]

	其中h[i]表示只砍第i列的方案数

	ans=sum(F[i][0]) 1<=i<=n

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const long long mod=1e9+7;
long long n,ans;
long long h[1000100];
long long f[1000100][2];
int main(){
    scanf("%lld",&n);
    for(register int i=1;i<=n;++i){
        scanf("%lld",&h[i]);
        h[i]--;
    }
    f[1][1]=min(h[1],h[2]);
    f[1][0]=h[1];
    ans=(ans+f[1][0])%mod;
    for(register int i=2;i<=n;++i){
        f[i][1]=((min(h[i],min(h[i-1],h[i+1]))*f[i-1][1])%mod+min(h[i],h[i+1]))%mod;
        f[i][0]=(min(h[i],h[i-1])*f[i-1][1]+h[i])%mod;
        ans=(ans+f[i][0])%mod;
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：WaterSun (赞：4)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18659524)

确实太颓了，在 csp 前教练给的题单里的题，快退役了才做/ll

# 思路

显然切除的一定是一个区间。其次若对于一列达到了他可行的最小的切除高度，那么切得更多一定合法，于是考虑求出这个值。

仔细观察发现，第 $i$ 列至少要把第 $\min(h_{i - 1},h_i,h_{i + 1})$ 行及以上切掉（若 $i - 1,i + 1$ 列都要切）。令这个值为 $a_i$。

枚举区间右端点 $r$，所有合法区间的答案为：

$$
\sum_{l < r}{((\min(h_l,h_{l + 1}) - 1) \times (\min(h_r,h_{r - 1}) - 1) \times \prod_{l < i < r}{(a_i - 1)}})
$$

考虑对 $a_i - 1$ 做前缀积：$s_i = \prod_{j \leq i}{(a_i - 1)}$。得：

$$
\sum_{l < r}(\min(h_l,h_{l + 1} - 1) \times (\min(h_r,h_{r - 1}) - 1) \times \frac{s_{r - 1}}{s_{l}})\\
\Rightarrow \sum_{l < r}{(\frac{\min(h_l,h_{l + 1}) - 1}{s_l}) \times (\min(h_r,h_{r - 1}) - 1) \times s_{r - 1}}
$$

考虑对 $\frac{\min(h_i,h_{i + 1}) - 1}{s_l}$ 做前缀和，记为 $S_i$，得：

$$
(\min(h_r,h_{r + 1}) - 1) \times s_{r - 1} \times S_{r - 1}
$$

需要注意 $h_i = 1$ 的情况，以及在上述情况的基础上加上 $r$ 单独为一段的情况。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long
#define Add(a,b) (((a) + (b)) % mod)
#define Mul(a,b) ((a) * (b) % mod)
#define chAdd(a,b) (a = Add(a,b))
#define chMul(a,b) (a = Mul(a,b))

using namespace std;

const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const int inf = 1e9 + 10;
int n,ans;
int arr[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline int qmi(int a,int b){
    int res = 1;
    while (b){
        if (b & 1) chMul(res,a);
        chMul(a,a); b >>= 1;
    } return res;
}

signed main(){
    n = read();
    for (re int i = 1;i <= n;i++) arr[i] = read();
    for (re int i = 1,s = 1,sum = 0;i <= n;i++){
        int v1 = inf,v2 = inf;
        if (arr[i - 1] > 1) v1 = arr[i - 1];
        if (arr[i + 1] > 1) v2 = arr[i + 1];
        chAdd(ans,Add(arr[i] - 1,Mul(Mul(s,sum),min(arr[i],v1) - 1)));
        chMul(s,min({v1,arr[i],v2}) - 1);
        if (!s) s = 1,sum = 0;
        else chAdd(sum,Mul(qmi(s,mod - 2),min(arr[i],v2) - 1));
    } printf("%lld",ans);
    return 0;
}
```

---

## 作者：_YRH_ (赞：2)

&emsp;今日考试出了这题，被虐的死去活来 ~~(说白了就是不会写)~~ 。在听完讲解后收获颇丰，既然没有题解那就来写 ~~(水)~~ 一篇吧。  
## 题目描述
&emsp;$Vasily$有一个栅栏，你可以将它看做由 $n$ 个垂直的木板组成。每个木板的宽为 $1$ 个单位，从左到右第 $i$ 块木板高为 $hi$ 个单位。现在这些木板都是彼此相连构成了一个完整的栅栏。  
&emsp;由于$Vasily$厌倦了这种布局，他希望将某些木板砍去一部分。要求满足以下限制条件：  
&emsp;1. 砍去的部分只能是木板的上部。(否则栅栏就立不起来了)  
&emsp;2. 砍去的部分必须相连（只有上下左右四个方向算相连，左上角等不算相连）。  
&emsp;3. 每块木板只能砍去整数单位的高度和 $1$ 个单位的宽度。  
&emsp;4. 不能将某块木板全部砍去，即每块木板至少保留 $1$ 个单位的高度。（这样才能保证剩余的木板依旧能构成一个完整的栅栏）  
&emsp;现在$Vasily$想知道他有多少种砍的方案。由于这个数可能很大，你需要输出它对 $1000000007$ 取模后的答案。  

## 分析
&emsp; 对于题目，由于必须保留一行，我们可以事先将所有的 $h$ 减一，就不要考虑最后一行不能拆的限制了。  
&emsp; 然后，对于此题，不难看出是一道动态规划问题，由于 $1<=n<=1000000$ ,我们只能考虑 $O(n)$ 的转移。对于第 $i$ 列 , 如何判断其拆卸的高度？考虑到对于任何一列，只有位于一段中最左端，中间，与最右端，如下图：$l$即左端栅栏，$r$即右端栅栏。  
![](https://ae01.alicdn.com/kf/HTB1658EaND1gK0jSZFK763JrVXaf.png)  

&emsp; 不难得出，当其位于左端时，其可拆除高度仅仅只与本身与下一列的高度的最小值有关，即 $f[l] = min(h[l], h[l + 1])$。易得，当其位于中间时， $f[i] = min(h[i - 1], h[i], h[i + 1])$ ,右端同理。  

&emsp; 由此，转移方程则可推出来，我们可用 $f[i][0/1]$ 代表该栅栏拆的时候，$0/1$表示其后一列是否被拆除，$1$表示其被拆除，$0$表示没有。那么有：  

$$f[1][0] = h[1];$$    

$$f[1][1] = min(h[1], h[2]);$$    

&emsp;而对于余下部分，则可有其位于中间，与位于左端之和得出  
$$f[i][1] = min(h[i - 1], h[i], h[i + 1]) * f[i - 1][1] + min(h[i], h[i + 1])$$   
$$f[i][0] = min(h[i - 1], h[i]) * f[i - 1][1] + h[i]$$   

&emsp;最终， $ans = \sum\limits_{i = 1}^{n}f[i][0]$ 。还有对于此题，由于其数据很大，对于模数的处理还需多加小心。  
&emsp;就这样，愉快的解决了此题，附代码：

```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <cctype>
#include <queue>
#include <algorithm>
using namespace std;

const int mo = 1e9 + 7;
const int maxn = 1000000 + 100;

int n, m, k, ans;
int h[maxn], f[maxn][2];

inline int read() {
    int s = 0, f = 0;
    char ch = getchar();
    while (!isdigit(ch)) f |= ch == '-', ch = getchar();
    while (isdigit(ch)) s = (s<<3) + (s<<1) + (ch^48), ch = getchar();
    return f ? -s : s;
}

int main() {
    n = read();
    for (int i = 1; i <= n; i++)
        h[i] = read() - 1;  // 预先减去1，方便后续操作
    f[1][0] = h[1];
    f[1][1] = min(h[1], h[2]);  //初始化
    for (int i = 2; i <= n; i++) {
        f[i][1] = (1ll * min(h[i - 1], min(h[i], h[i + 1])) * f[i - 1][1] + min(h[i], h[i + 1])) % mo;
        f[i][0] = (1ll * min(h[i - 1], h[i]) * f[i - 1][1] + h[i]) % mo;   //转移
    }
    for (int i = 1; i <= n; i++)
        ans = (ans + f[i][0]) % mo;   //求和
    printf("%d\n", ans);
    return 0;
}
``` 

---

## 作者：Md_Drew (赞：2)

### 题解部分摘自学长 @zmh964685331

### ①部分pts

一个简单的 dp:

f[i][j]表示考虑前 i 列,其中第 i 列拆了最上方 j 个单位的方案数。

转移时枚举第 i−1 列拆的数量, 如果能够连起来就转移。

复杂度 : O(n∗h^2)

------------

### ②大部分部分pts

考虑优化上述算法.

显然合法的 f [i−1,l] 对应的 l 一定是连续的,可以用前缀和优化。

同时可以用滚动数组压去一维空间

复杂度 : O(n∗h)。


放下代码（过程在下方注释中） ：

```cpp
#include<cstdio>
#include<ctype.h>
#define rei register int
#define ll long long
using namespace std;
const int MAXN =  1e6 +5;
const int mod = 1e9 +7;

int n;
int h[MAXN];
int f[5005][5005];
int g[5005][5005];

inline int mod_add(int &a, int &b)
{
    return (a%mod + b%mod)%mod;
    //made by Drew
}

inline int mod_minus(int &a, int &b) 
{
    return (a%mod - b%mod +mod)%mod ;
    //made by Drew
}

inline int	read()
{
	int x=0;bool f=1;char c=getchar();
	for(;!isdigit(c);c=getchar() )	if(c=='-')	f=0;
	for(; isdigit(c);c=getchar() )	x = (x<<3) +(x<<1) +c -48;
 	if(f)	return x;
	return 0-x;
}

int main()
{
	n = read();
	for(rei i=1;i<=n;++i)		h[i] = read(), h[i]--;
	for(rei j=1;j<=h[1];++j)	f[1][j] = 1, g[1][j] = g[1][j-1] +f[1][j];
	for(rei i=2;i<=n;++i)
	{
		int d = h[i]-h[i-1];
		if(d>=0)
		{
			for(rei j=1;j<=d;++j)
			{
				f[i][j] = 1;
				g[i][j] = mod_add( g[i][j-1], f[i][j] );
			}
			for(rei j=d+1;j<=h[i];++j)	
			{
				f[i][j] = (g[i-1][ h[i-1] ]%mod +1)%mod;
				g[i][j] = mod_add( g[i][j-1], f[i][j] );
			}
		}
		else
		{
			d = 0-d;
			for(rei j=1;j<=h[i];j++)
			{
				f[i][j] = mod_minus( g[i-1][ h[i-1] ], g[i-1][d] ) +1;
				g[i][j] = mod_add( g[i][j-1], f[i][j] );
			}
		}
	}
	ll ans = 0;
	for(rei i=1;i<=n;++i)	ans = ( (ans%mod) + (g[i][h[i]]%mod) )%mod;
	printf("%lld",ans);
	return 0;
}

/*

很明显是一道DP题。

dp[i][j]	表示第i行砍掉j个块的总方案数(连在一起的)。

初始化	f[1][ 1-->h[i] ] = 1;	(连在一块)

状态转移有两种情况

①

h[i]>=h[i-1]
{
	d = h[i] -h[i-1];
	f[i][j]	= 1;							(1<=j<=d)		//前面砍了转移不过来，只能自己算一个		
	f[i][j] = 1+ ∑ f[i-1][1-->h[i-1]]		(d<j<=h[i])		//前面的可以都转移过来，全转移 +自己一个
}

h[i]<h[i-1]
{
	d = h[i-1]-h[i];
	f[i][j] = 1+ ∑ f[i-1][d+1-->h[i-1]]						//从比它低就都可以转移过来 +自己一个
}

最后答案为所有f[i][j]之和

可以前缀和优化	g[i][j]表示 g[i][1-->j];

*/

```



------------

### 特殊情况

我们考虑 h[i] 均相同, 此时记为 h 

我们先考虑如果每列都一定要拆的方案。其实如果每列都拆,只要不全拆就一定合法。

那么方案数就是 (h−1)^n 。

其实任何一个方案都是由一段区间每行都拆构成的。长度为 k 的区间对答案的贡献为 (h−1)^k


那么答案就是

![](https://cdn.luogu.com.cn/upload/pic/64422.png)

------------

## 满分做法


我们事先将所有的 h 减一,就不要考虑最后一行不能拆的限制了。

那特殊情况其实是在给我们提示。按照之前的思路如果考虑第 l 到 r 行之间每行都要拆。

那么方案数为 ：

![](https://cdn.luogu.com.cn/upload/pic/64423.png)

理解起来不难,就是为了保证联通,每行的取法是与它相邻行中高度的最小值。因为如果第 i 行拆掉一部分后剩余部分还比周围高,那么这种拆法一定不合法。那么合法的拆法只有 min (hi, hi −1 , hi +1 ) 种。

基于以上思考,我们重新设计一个 dp。

f[i]代表考虑前 i 列, 强制第 i+1 列必须拆的方案。

g[i]表示第 i+1 列不拆时的方案。

这样设计是因为第 i+1 列拆不拆对 i 的方案是有影响的。

接下来考虑转移:


![](https://cdn.luogu.com.cn/upload/pic/64425.png)

(图片下面有部分被水印挡住了。ans = g1+g2+g3+...+gn)
 

这题就完美的 O(n) 解决了。


```cpp

#include<cstdio>
#include<ctype.h>
#include<algorithm>
#define rei register ll
#define ll long long
using namespace std;
const ll MAXN =  1e6 +5;
const ll mod = 1e9 +7;

ll n;
ll h[MAXN];
ll f[MAXN];
ll g[MAXN];

inline ll	read()
{
	ll x=0;bool f=1;char c=getchar();
	for(;!isdigit(c);c=getchar() )	if(c=='-')	f=0;
	for(; isdigit(c);c=getchar() )	x = (x<<3) +(x<<1) +c -48;
 	if(f)	return x;
	return 0-x;
}

main()
{
	n = read();
	for(rei i=1;i<=n;++i)		h[i] = read(), h[i]--;
	f[1] = min(h[1],h[2])%mod, g[1] = h[1];
	for(rei i=2;i<=n;++i)
	{
		ll x = min(h[i],h[i+1]), y = min( h[i], min(h[i+1],h[i-1]) );
		f[i] = ( x + ( y*(f[i-1]%mod) )%mod )%mod;
		ll temp = min(h[i],h[i-1])%mod;
		g[i] = ( h[i] + ( temp*(f[i-1]%mod) )%mod )%mod;
	}
	ll ans = 0;
	for(rei i=1;i<=n;++i)	ans = ( (ans%mod) + (g[i]%mod) )%mod;
	printf("%lld",ans);
	return 0;
}


```


---

## 作者：SilverStar (赞：1)

对于数据范围给出特别约定的题面，不妨先从特殊情况开始分析

对于 $20\%$ 的数据，存在 $h_i$ 相同，记 $H=h_i$ ，考虑分解方案，事实上，我们假设从第 $i$ 列从上方拆除 $p_i\in [\,1,\,H-1\,]$ 个栅栏，即第 $i$ 列存在 $H-1$ 种拆除方案，那么任意一个合法的拆除方案必然是一段连续的 $i$ 拆除组成的，所以若有一类合法方案连续拆除的长度为 $k$ ，那么由计数原理就可以得到这一类拆除的方案总数为 $(H-1)^k$ ，在总长为 $n$ 的栅栏中，一共可以分出 $n-k+1$ 个长度为 $k$ 的连续子段，所以此时总的答案为
$$Ans=\sum\limits_{k=1}^n(H-1)^k\times (n-k+1)$$

将这种做法拓展到 $h_i$ 不同的情况，令 $h_i=h_i-1$ 以排除最后一行不能拆除的情况，对于一类拆除方案 $[\,l,\,r\,]$ ，为了保证其中任意一列都能与相邻的两列联通，那么第 $i\in [\,l,\,r\,]$ 列的合法方案数应为$\min(h_{i-1},\,h_i,\,h_{i+1})$ （ 因为如果第 $i$ 列拆除后剩余部分比周围更高，这种方案显然是不合法的 ）

特别的，对于两端的栅栏，需要单独考虑，则最后该区间内总的合法拆除的方案数为
$$\min(h_l,\,h_{l+1})\times \min(h_{r-1},\,h_r)\times \prod\limits_{i=l+1}^{r-1}\min(h_{i-1},\,h_i,\,h_{i+1})$$
下面我们设一个状态 $f(i)$ 表示在前 $i$ 列中，第 $i+1$ 列强制拆的方案数，状态 $g(i)$ 表示第 $i+1$ 列不拆的方案数，因为第 $i+1$ 拆与不拆的情况是会对 $i$ 产生影响的，那么就能得到转移
$$\begin{aligned}g(1)&=h_1 \\f(1)&=\min(h_1,\,h_2)\\g(i)&=h_i\min(h_i,\,h_{i-1})\times f(i-1) \\f(1)&=\min(h_i,\,h_{i+1})+\min(h_{i-1},\,h_i,\,h_{i+1})\times f(i-1) \\\end{aligned}$$
最终的答案为
$$Ans=\sum\limits_{i=1}^ng_i$$

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn = 1e6+5;
const int mod = 1e9+7;

int n,h[maxn];
int f[maxn],ans;

int min(int a, int b, int c = 1 << 30){
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

int main(){
    scanf("%d",&n);
    for(int i = 1; i<=n; i++){
        scanf("%d",&h[i]);
        h[i] --;
    }
    ans = h[1];
    f[1] = min(h[1], h[2]);
    for(int i = 2; i<=n; i++){
        f[i] = (1ll*min(h[i-1],h[i],h[i+1])*f[i-1]+min(h[i],h[i+1])) % mod;
        if(h[i+1] >= h[i])
            ans = (f[i]+ans) % mod;
        else ans = (ans+1ll*min(h[i],h[i-1])*f[i-1]+h[i]) % mod;
    }
    printf("%d",ans % mod);
    return 0;
}
```

---

## 作者：rubbishZZZ (赞：0)

## CF659G Fence Divercity



### 题意：

- **Vasily** 有一个栅栏，你可以将它看做由 $n$ 个垂直的木板组成。每个木板的宽为 $1$ 个单位，从左到右第 $i$ 块木板高为 $h_i$ 个单位。现在这些木板都是彼此相连构成了一个完整的栅栏。
  由于 **Vasily** 厌倦了这种布局，他希望将某些木板砍去一部分。要求满足以下限制条件：
  1. 砍去的部分只能是木板的上部。(否则栅栏就立不起来了)
  2. 砍去的部分必须相连（只有上下左右四个方向算相连，左上角等不算相连）。
  3. 每块木板只能砍去整数单位的高度和 $1$ 个单位的宽度。
  4. 不能将某块木板全部砍去，即每块木板至少保留 $1$ 个单位的高度。（这样才能保证剩余的木板依旧能构成一个完整的栅栏）
    现在 **Vasily** 想知道他有多少种砍的方案。由于这个数可能很大，你需要输出它对 $10^9+7 $取模后的答案。



### 解法1：

- 我们先让 $h_i\leftarrow h_i-1$，这样就没有保留 $1$ 个单位高度的限制。

  我们设 $f_{i,j}$ 表示第 $i$ 个栅栏保留下 $j$ 个的方案数，转移如下：

  1. 若 $h_i\leq h_{i-1}$，那么对于每个 $1\leq j\leq h_i$ 都有 $f_{i,j}=\sum\limits_{k=1}^{h_i}f_{i-1,k}+1$。
  2. 若 $h_i\gt h_{i-1}$，那么对于每个 $1\leq j\leq h_{i-1}$ 有 $f_{i,j}=\sum\limits_{k=1}^{h_{i-1}}f_{i-1,k}$，对于 $h_{i-1}\lt j\leq h_i$ 有 $f_{i,j}=1$。

  那么就很明显了，对于某个 $i$，$f_{i,j}$ 的值要么是 $1$，要么是某个相同值。

  我们设 $g_i=\sum\limits_{j=1}^{h_i}f_{i,j}$，优化转移。

  1. 若 $h_i\leq h_{i-1}$，那么所有 $f_{i,j}=g_{i-1}+1$。
  2. 若 $h_{i}\gt h_{i-1}$，我们还要对 $h_{i-2}$ 分类讨论一下，确定 $f_{i-1}$ 是否有一段 $1$。
     1. 若 $h_{i-2}\leq h_i$，则多出的部分都是 $1$，有 $f_{i,j}=g_{i-1}-(h_{i-1}-h_i)+1$。
     2. 若 $h_i\lt h_{i-2}\leq h_i$，则有一段 $1$，一段 $f_{i-1}$，有 $f_{i,j}=g_{i-1}-(h_{i-1}-h_{i-2})-f_{i-1,1}(h_{i-2}-h_{i})+1$。
     3. 若 $g_{i-2}\gt h_{i}$，则没有 $1$，有 $f_{i,j}=f_{i-1,1}h_i+1$。

  我们只需要维护 $f_{i,1}$ 就行了，复杂度 $O(n)$。

### 代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <ctime>
#include <random>
#include <cassert>
#include <numeric>
#include <cmath>
#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#define pii pair<int, int>
#define fi first
#define se second
#define MP make_pair
#define ep emplace
#define eb emplace_back
//#define int long long
#define rep(i, j, k) for (int i = (j); i <= (k); i++)
#define per(i, j, k) for (int i = (j); i >= (k); i--)
typedef double db;
typedef long double ldb;
typedef long long ll;
//typedef __int128 lll;
typedef unsigned long long ull;
typedef unsigned int ui;
using namespace std;
using namespace __gnu_pbds;
bool Mbe;

//char buf[1<<20],*p1,*p2;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)
int read() {
	int s = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') f ^= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') s = s * 10 + c - '0', c = getchar();
	return f ? s : -s;
}
template<typename T>void chkmax(T&x,const T&y){if(x<y)x=y;}
template<typename T>void chkmin(T&x,const T&y){if(x>y)x=y;}

const int N=1000005,mod=1e9+7;
int fplus(int x,int y){return x+y>=mod?x+y-mod:x+y;}
void Fplus(int&x,int y){x=fplus(x,y);}
int fminus(int x,int y){return x-y<0?x+mod-y:x-y;}
void Fminus(int&x,int y){x=fminus(x,y);}
int n,a[N],f[N],ans,g[N];

bool Med;
signed main() {
	fprintf(stderr,"%.3lfMb\n",(&Mbe-&Med)/1024./1024.);
	n=read();
	rep(i,1,n)a[i]=read()-1;
	ans=g[1]=a[1];
	rep(i,2,n){
		if(a[i]>=a[i-1]){
			f[i]=g[i-1];
			g[i]=((ll)f[i]*a[i-1]+a[i])%mod;
		}else{
			if(a[i-2]<=a[i])f[i]=((ll)g[i-1]-a[i-1]+a[i]+mod)%mod;
			else if(a[i-2]<=a[i])f[i]=((ll)g[i-1]-a[i-1]+a[i]-(ll)(a[i-2]-a[i])*f[i-1]%mod+mod+mod)%mod;
			else f[i]=(ll)(f[i-1]+1)*a[i]%mod;
			g[i]=((ll)f[i]*a[i]+a[i])%mod;
		}
		Fplus(ans,g[i]);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
有点意思的 dp 题。

摘自[杂题选做 Part 4. dp](https://www.luogu.com.cn/training/660942)。
## 思路分析
因为最底下的木板不让砍，我们不妨就先给最后一排整个砍了再做。

直接大力设计 dp 状态，定义 $f_{i,j}$ 表示第 $i$ 块木板一定要砍，砍了 $j$ 长度的方案数。

那么我们的转移就是是否从上面一个板接过来。

这个时候还要分讨一下：
1. $a_{i-1}\le a_i$，此时 $j$ 至少要为 $a_i-a_{i-1}+1$，贡献就是 $\sum\limits_{j=0}^{a_i-1} f_{i-1,j}$。
2. $a_{i-1}>a_i$，此时任意的 $j$ 都可以转移，转移的贡献为 $\sum\limits_{j=a_{i-1}-a_i+1}^{a_{i-1}}$。

复杂度是 $O(nV)$ 的，显然不知道挂到哪去了。

优化也是比较显然，我们发现这个转移的贡献值只有两种。

或者说，如果你要考虑 $i$ 对于 $i+1$ 的贡献，你只需要考虑将 $i$ **能接** $i+1$ 的贡献算出来就可以了。

那么我们不妨设 $f_i$ 表示 $i$ 能接 $i+1$ 的贡献，$g_i$ 表示木板 $i$ 必须砍的方案数。

那么我们有转移：
$$f_i=\min(a_i,a_{i+1})+\min(a_{i-1},a_i,a_{i+1})\cdot f_{i-1}$$
$$g_i=a_i+\min(a_{i-1},a_i)\cdot f_{i-1}$$

转移的意义就是你考虑接不接，如果要接 $f_{i-1}$ 那么你能砍的高度就要和 $a_{i-1}$ 取 $\min$（因为如果你把更高的地方砍了 $a_{i-1}$ 可能就接不上他了）。

对于 $f$ 而言你要接 $i+1$ 这个板，自然是要取 $\min$ 的。
## 代码
实现也是很简单，感觉不到紫。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
using namespace std;
const int N=1e6+10,M=6e5+10,V=1e5+3,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f;
int n,a[N],f[N],g[N];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(long long x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c=='>'||c=='<'||c=='='||c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline void solve()
{
	n=read();for(int i=1;i<=n;i++) a[i]=read()-1;
	f[1]=min(a[1],a[2])%mod,g[1]=a[1];int ans=a[1];
	for(int i=2;i<=n;i++)
	{
		f[i]=(min(a[i],a[i+1])+min({a[i-1],a[i],a[i+1]})*f[i-1])%mod;
		g[i]=(a[i]+min(a[i],a[i-1])*f[i-1])%mod;ans=(ans+g[i])%mod;
	}print(ans);put('\n');
}
signed main()
{
	int T=1;
	// T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：Shunpower (赞：0)

这题真能紫？

-------------

首先显然必然切一个子区间。假设我们可以枚举全部区间，考虑怎么直接 $\mathcal O(n)$ 统计“每一个栅栏都要切”的方案数。

考虑每个位置上需要切的长度被两侧限制，必须要切到只剩下 $1$ 到 $\min(a_{i-1},a_i,a_{i+1})-1$ 之间的高度（特别地，$a_0=a_{n+1}=+\infty$），并且只要切到这个高度区间就一定合法。因为两侧也必然要切至少一刀，所以就一定连得起来。

那么我们直接先把所有 $1$ 删掉（显然这不影响，因为能产生“每一个栅栏都要切”的区间里一定没有 $1$），然后对于被 $1$ 分出来的每一段计算：

$$
\sum\limits_{l=1}^n a_l-1+\sum\limits_{r=l+1}^n (\min(a_l,a_{l+1})-1)\times (\min(a_r,a_{r-1})-1)\times \prod\limits_{i=l+1}^{r-1}\min(a_{i-1},a_i,a_{i+1})-1
$$

（这里为了规避一些边界把 $l,r$ 的贡献单独拎出来乘，以及把 $l=r$ 的区间产生的贡献单独拿出来算了。）

考虑右侧的 $\prod$ 可以用逆元做（这就是为什么我们要把 $1$ 删掉再做）。不妨记前缀积为 $\{mul_n\}$，那么：

$$
\begin{aligned}
&\sum\limits_{l=1}^n a_l-1+\sum\limits_{r=l+1}^n (\min(a_l,a_{l+1})-1)\times (\min(a_r,a_{r-1})-1)\times \prod\limits_{i=l+1}^{r-1}\min(a_{i-1},a_i,a_{i+1})-1\\
=&\sum\limits_{l=1}^n a_l-1+\sum\limits_{r=l+1}^n (\min(a_l,a_{l+1})-1)\times (\min(a_r,a_{r-1})-1)\times mul_{r-1}\times mul_l^{-1}\\
=&\sum\limits_{l=1}^n a_l-1+mul_l^{-1}\times (\min(a_l,a_{l+1})-1)\times\sum\limits_{r=l+1}^n  (\min(a_r,a_{r-1})-1)\times mul_{r-1}
\end{aligned}
$$

右边的和式与 $l$ 无关，进行前缀和即可。

于是就做完了。写的时候可以不显式把段分出来，但是就会因为 $1$ 产生亿些细节问题。其实还不如写分出来每个单独算再求和。

```cpp
int n;
int a[N];
int coef[N];
ll mul[N],sum[N];
int nxt1[N];
const int mod=1e9+7;
ll qpow(ll b,int p){
	if(!p) return 1;
	ll d=qpow(b,p>>1);
	if(p&1) return d*d%mod*b%mod;
	else return d*d%mod;
}
ll inv(int x){
	return qpow(x,mod-2);
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	fr1(i,1,n) cin>>a[i];
	a[0]=a[n+1]=1e9+1;
	fr1(i,1,n){
		int lim=min({a[i-1],a[i+1],a[i]});
		coef[i]=lim-1;
	}
	nxt1[n]=n+1;
	fr2(i,n-1,1){
		if(a[i]==1) nxt1[i]=i;
		else nxt1[i]=nxt1[i+1];
	}
	mul[0]=1;
	fr1(i,1,n){
		if(a[i]==1){
			mul[i]=1;
			mul[i+1]=1;
			if(a[i+1]!=1) i++;
			continue;
		}
		mul[i]=1ll*mul[i-1]*coef[i]%mod;
	}
	ll res=0;
	fr1(i,1,n) sum[i]=(sum[i-1]+1ll*mul[i-1]*(min(a[i-1],a[i])-1)%mod)%mod;
	fr1(l,1,n){
		if(a[l]==1) continue;
		ll liml=min(a[l+1],a[l])-1;
		ll psum=sum[nxt1[l]-1]+mod-sum[l];
		(res+=psum*liml%mod*inv(mul[l])%mod)%=mod;
	}
	fr1(i,1,n) (res+=a[i]-1)%=mod;
	cout<<res<<'\n';
	ET;
}
//ALL FOR Zhang Junhao.
```

代码仅供参考。化完式子之后的代码可读性并不高。

[AC 记录](https://codeforces.com/contest/659/submission/300029848)。

---

## 作者：lfxxx (赞：0)

不妨 $dp_{i,j}$ 表示第 $i$ 列保留 $j$ 个木板，且钦定第 $i$ 列一定选了木板去除的方案。

有 $dp_{i,j} = 1 + [j \leq a_{i-1}-1] \sum_{j=1}^{a_i-1} dp_{i-1,j}$。

我们发现 dp 数组只有两种取值，分界点为 $a_{i-1}-1$，于是记录 $dp_{i,0/1}$ 分别表示两种取值分别是多少即可做到 $O(n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6+114;
const int mod = 1e9+7;
int dp[maxn][2];//dp[i][0] [1,a[i-1]-1] 的 dp 值 dp[i][1] [1,a[i]-1] 的 dp 值
int n;
int a[maxn];
int ans;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    dp[1][1]=1;
    ans=(ans+(a[1]-1)*dp[1][1]);
    for(int i=2;i<=n;i++){
        int lst=0;
        if(i-1==1||a[i-1-1]-1>=a[i-1]-1){
            lst=min(a[i-1]-1,a[i]-1)*dp[i-1][1]%mod;
        }else{
            lst=(min(a[i]-1,a[i-1-1]-1)*dp[i-1][0]%mod+max(0*1ll,(min(a[i]-1,a[i-1]-1)-a[i-1-1]+1))*dp[i-1][1]%mod)%mod;
        }
        //cout<<lst<<'\n';
        if(a[i-1]-1>=a[i]-1){
            dp[i][1]=(lst+1)%mod;
            //cout<<"A"<<i<<' '<<(a[i]-1)*dp[i][1]%mod<<'\n';
            ans=(ans+(a[i]-1)*dp[i][1]%mod)%mod;
        }else{
            dp[i][0]=(lst+1)%mod,dp[i][1]=1;
            //cout<<"B"<<i<<' '<<(a[i-1]-1)*dp[i][0]%mod+(a[i]-1-a[i-1]+1)*dp[i][1]%mod<<'\n';
            ans=(ans+(a[i-1]-1)*dp[i][0]%mod+(a[i]-1-a[i-1]+1)*dp[i][1]%mod)%mod;
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：thostever (赞：0)

我们在开始时先让`h[i]--` ，去除掉保留 $1$ 个单位高度的条件。

我们令 $f(l,r)$ 表示在区间 $[l,r]$ 内，**如果每个木板都被砍**，那么有多少种砍的方式。

如果 $l==r$，$f(l,r)=h_i$。

如果 $l<r$，则对于每个木板，我们都要让它两边的木板都能够被砍，所以要把它砍到两边木板的顶端以下。区间两头特判一下，则有：
$$
f(l,r)=\min(h_l,h_{l+1})\times (\sum _{i=l+1}^{r-1} \min(h_{i-1},h_i,h_{i+1}))\times \min(h_r,h_{r-1})
$$
显然，$ans=\sum_{l=1}^n\sum_{r=l}^n f(l,r)$。

```cpp
for(int i=1;i<=n;i++)
	for(int j=i;j<=n;j++)
	{
		if(i==j) ans+=h[i];
		else
		{
			int tmp=1;
			for(int k=i+1;k<=j-1;k++) tmp*=min(h[k-1],min(h[k],h[k+1])),tmp%=mod;
			tmp*=min(h[i],h[i+1]),tmp%=mod;
			tmp*=min(h[j],h[j-1]),tmp%=mod;
			ans+=tmp,ans%=mod;
		}
	}
```

~~太暴力了~~

考虑优化：

我们发现第三层 for 循环中可以用前缀积优化一下，设 $b_i=\min(h_{i-1},h_i,h_{i+1})$，$s_i=\prod_{j=1}^i b_i$。计算时直接乘上 $s_{r-1}/s_l$。

然后你就会发现你愉快的挂了。why?

因为 $h_i$ 在自减完后可能会出现 $0$，那直接前缀积肯定挂了呀。

我们稍微改一下，在遇到 $0$ 的时候直接跳过，$s_i=s_{i-1}$。同时新建一个数组 $t$ 来记录前 $i$ 个中有多少个 $0$。这样对于每个区间，我们首先通过 $t$ 查看是否有 $0$ ，有则直接跳过，没有就前缀积相除即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int qpow(int x,int y)
{
	int p=1;
	while(y)
	{
		if(y&1) p*=x,p%=mod;
		x*=x; x%=mod;
		y>>=1;
	}
	return p;
}
int chu(int x,int y)
{
	return x*qpow(y,mod-2)%mod;
}
int n;
int h[1000010];
int s[1000010],t[1000010];
int dp[1000010];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>h[i],h[i]--;
	h[0]=h[n+1]=INT_MAX; s[0]=1; t[0]=0;
	for(int i=1;i<=n;i++)
	{
		int x=min(h[i-1],min(h[i],h[i+1]));
		if(x) s[i]=s[i-1]*x,s[i]%=mod;
		else s[i]=s[i-1];
		t[i]=t[i-1]+(h[i]==0);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		ans+=h[i];
		for(int j=i+1;j<=n;j++)
		{
			int tmp=0;
			if(t[j]-t[i-1]!=0) continue;
			tmp=chu(s[j-1],s[i]); tmp%=mod;
			tmp*=min(h[i],h[i+1]); tmp%=mod;
			tmp*=min(h[j],h[j-1]); tmp%=mod;
			ans+=tmp; ans%=mod;
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

再考虑怎么优化。

我们枚举区间的末尾 $r$，发现对于 $r$ 来说，
$$
\sum_{l=1}^r f(l,r)=\sum_{l=1}^r \min(h_l,h_{l+1})\times\frac{s_{r-1}}{s_l}\times \min(h_r,h_{r-1})
$$
$$
=\sum_{l=1}^r \frac{\min(h_l,h_{l+1})}{s_l}\times s_{r-1}\times \min(h_r,h_{r-1})
$$
$$
=s_{r-1}\times \min(h_r,h_{r-1})\times \sum_{l=1}^r \frac{\min(h_l,h_{l+1})}{s_l}
$$
$s_{r-1}\times \min(h_r,h_{r-1})$ 是定值，而 $\sum_{l=1}^r \frac{\min(h_l,h_{l+1})}{s_l}$ 可以通过前缀和得到，直接记录为 $cnt$ 即可，每次 $cnt=cnt+\frac{\min(h_r,h_{r+1})}{s_r}$。

等一下！遇到 $0$ 了怎么办？我们发现对于末尾 $r$ 来说，$l$ 在 $0$ 左边的部分都没法提供贡献。那么我们就可以理解为每次遇到 $0$ 时都相当于从头开始，直接将 $cnt=0$ 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int qpow(int x,int y)
{
	int p=1;
	while(y)
	{
		if(y&1) p*=x,p%=mod;
		x*=x; x%=mod;
		y>>=1;
	}
	return p;
}
int chu(int x,int y)
{
	return x*qpow(y,mod-2)%mod;
}
int n;
int h[1000010];
int s[1000010];
int dp[1000010];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&h[i]),h[i]--;
	h[0]=h[n+1]=INT_MAX; s[0]=1;
	for(int i=1;i<=n;i++)//预处理前缀积 
	{
		int x=min(h[i-1],min(h[i],h[i+1]));
		if(x) s[i]=s[i-1]*x,s[i]%=mod;
		else s[i]=s[i-1];
	}
	int ans=0;
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(h[i]==0) cnt=0;
		ans+=(cnt*s[i-1])%mod*min(h[i],h[i-1]); ans%=mod;
		cnt+=chu(min(h[i],h[i+1]),s[i]); cnt%=mod;
		ans+=h[i]; ans%=mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：RainFestival (赞：0)

我们先将所有的 $\large h_i\leftarrow h_i-1$。

令 $\large f(x,y)=$ 切掉 $\large x$ 到 $\large y$ 列的方案数，当然 $\large x\le y$。

$\large ans=\sum\limits_{i=1}^{n}\sum\limits_{j=i}^{n}f(i,j)$

当 $\large x=y$ 时比较简单，即 $\large f(x,y)=h_x$

当 $\large x<y$ 时列出~~柿子~~式子，则我们发现：

$\large f(x,y)=\min(h_x,h_{x+1})\times(\prod\limits_{i=x+1}^{y-1}\min(h_{i-1},h_i,h_{i+1}))\times\min(h_{y-1},h_y)$

这里因为每一条留下的长度 $\large d_i$ 一定 $\large\le h_i$，要求切掉的要连在一起，所以并且要 $\large\le h_x$，$\large x$ 是 $\large i$ 相邻的板。

并在一起

$\large ans=\sum\limits_{i=1}^{n}h_i+\sum\limits_{i=1}^{n}\sum\limits_{j=i+1}^{n}\min(h_i,h_{i+1})\times\prod\limits_{k=i+1}^{j-1}\min(h_{k-1},h_k,h_{k+1})\times\min(h_{j-1},h_j)$

稍作调整

$\large ans=\sum\limits_{i=1}^{n}h_i+(\sum\limits_{i=1}^{n}\min(h_i,h_{i+1}))\times(\sum\limits_{j=i+1}^{n}\min(h_{j-1},h_j))\times(\prod\limits_{k=i+1}^{j-1}\min(h_{k-1},h_k,h_{k+1}))$

将 $\large r$ 独立出来

$\large ans=\sum\limits_{i=1}^{n}h_i+(\sum\limits_{j=2}^{n}\min(h_{j-1},h_j))\times(\sum\limits_{i=1}^{j}\min(h_i,h_{i+1}))\times(\prod\limits_{k=i+1}^{j-1}\min(h_{k-1},h_k,h_{k+1}))$

记

$\large p(m)=(\sum\limits_{i=1}^{m}\min(h_i,h_{i+1}))\times(\prod\limits_{k=i+1}^{m-1}\min(h_{k-1},h_k,h_{k+1}))$

则

$\large ans=\sum\limits_{i=1}^{n}h_i+(\sum\limits_{j=2}^{n}\min(h_{j-1},h_j))\times p(j)$

我们发现我们可以求出 $\large p$ 的递推式

$\large p(1)=0,p(m+1)=p(m)\times\min(h_{m-1},h_m,h_{m+1})+\min(h_r,h_{r+1})$

于是很好的一点是 $\large O(n)$ 求出 $\large p$。

然后就可以 $\large O(n)$ 求出 $\large ans$。

记得取模 $\large1000000007$

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#define mod 1000000007 
int n;
long long h[1000005],s[1000005],ans,p;
int main()
{
	scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%lld",&h[i]);
    for (int i=1;i<=n;i++) ans=(ans+h[i]-1)%mod;
    s[1]=0;
    for (int i=1;i<n;i++) s[i+1]=(s[i]*std::min(h[i-1]-1,std::min(h[i]-1,h[i+1]-1))+std::min(h[i]-1,h[i+1]-1))%mod;
    for (int i=2;i<=n;i++) ans=(ans+std::min(h[i-1]-1,h[i]-1)*s[i])%mod;
    printf("%lld\n",ans);
	return 0;
}
```




---

