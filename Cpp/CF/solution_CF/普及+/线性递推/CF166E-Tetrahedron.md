# Tetrahedron

## 题目描述

You are given a tetrahedron. Let's mark its vertices with letters $ A $ , $ B $ , $ C $ and $ D $ correspondingly.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166E/40dcfda00eddce9e7e8701e13b2759e732ca40f3.png)An ant is standing in the vertex $ D $ of the tetrahedron. The ant is quite active and he wouldn't stay idle. At each moment of time he makes a step from one vertex to another one along some edge of the tetrahedron. The ant just can't stand on one place.

You do not have to do much to solve the problem: your task is to count the number of ways in which the ant can go from the initial vertex $ D $ to itself in exactly $ n $ steps. In other words, you are asked to find out the number of different cyclic paths with the length of $ n $ from vertex $ D $ to itself. As the number can be quite large, you should print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

The required paths in the first sample are:

- $ D-A-D $
- $ D-B-D $
- $ D-C-D $

## 样例 #1

### 输入

```
2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
```

### 输出

```
21
```

# 题解

## 作者：ModestCoder_ (赞：23)

水DP

设计状态，$f_i$表示走了i步目前在顶端的方案数，$g_i$表示走了i步目前不在顶端的方案数

方程$f_i=3g_{i-1},g_i=f_{i-1}+2g_{i-1}$

发现还可以滚动掉，爽啊

Code：

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const LL qy = 1000000007;

int main(){
	int n;
	scanf("%d", &n);
	LL f = 0, g = 1;
	for (int i = 2; i <= n; ++i){
		LL tmp = f;
		f = 3 * g % qy, g = (tmp + 2 * g) % qy;
	}
	printf("%lld\n", f);
	return 0;
}
```


---

## 作者：Flokirie (赞：12)

这题一上手，WA，裸的dp，先写一波dp方程：    
设$f[i]$,$g[i]$分别表示走了$i$步，最后停在$D$点和不停在$D$点的方案数，那么我们有：    
$f[i]=3g[i-1]...(1)$   
$g[i]=2g[i-1]+f[i-1]...(2)$   
貌似这已经可以了？   
然而，这题是一道$O(\log n)$好题！   

----

我们将$(1)$代入$(2)$：   
$g[i]=2g[i-1]+3g[i-2]$   
这是一个线性递推数列，特征方程$x^2=2x+3$，其两根为$x_{1,2}=-1,3$。   
那么，用待定系数法解得：$g[i]=\frac {3^i-(-1)^i} {4}$。
分子可以用快速幂解决，分母自然转化为乘以4（mod 1e9+7）意义下的逆元啦。   
于是答案就是$3g[i-1]$。
以下代码：
```cpp
#include <iostream>
#include <cstdio>
#define int long long
#define mos (1000000007ll)

using namespace std;

int ksm(int a,int n,int mod){
	int ret=1;
	for(;n;n>>=1){
		if (n&1) ret=(ret*a)%mod;
		a=(a*a)%mod;
	}
	return ret;
}

signed main(){
	int n;
	cin>>n;
	return !printf("%I64d",(750000006ll*(10000000070ll+ksm(3ll,n-1,mos)-ksm(1000000006ll,n-1,mos)))%mos);//4 mod 1e9+7的逆元是250000002
}
```

---

## 作者：lcy_2009 (赞：12)

## 题目分析

一道简单的 DP 题。

1. 定义状态：在这个问题中，我们定义 $dp_{i,j}$ 为蚂蚁在第 $i$ 步时位于顶点 $j$ 的路径数量。

1. 初始化状态：我们将 $dp_{0,3}$ 初始化为 1，表示在 $0$ 步时，蚂蚁在顶点D的路径数为 $1$。其余 $dp_{0,j}$（$j \ne 3$）初始化为  $0$，表示蚂蚁在 $0$ 步时，不能在顶点 $A$、$B$ 或 $C$。

1. 状态转移：对于每一个 $i$（$1 \le i \le n$），我们遍历每个顶点 $j$。对于每个顶点 $j$，我们又遍历所有的其他顶点 $k$。如果 $j \ne k$，那么我们将 $dp_{i-1,k}$ 加到 $dp_{i,j}$ 上。这是因为蚂蚁可以从顶点 $k$ 走到顶点 $j$。我们还需要对结果取模，以防止整数溢出。

1. 输出结果：最后，我们输出 $dp_{n,3}$，这就是蚂蚁在 $n$ 步后回到顶点 $D$ 的路径数。
1. 时间复杂度是 $O(n)$。

## c++ 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e7 + 5;

int dp[MAXN][4];

int main() {
    int n;
    cin >> n;
    dp[0][3] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                if(j != k) {
                    dp[i][j] += dp[i-1][k];
                    if(dp[i][j] >= MOD) {
                        dp[i][j] -= MOD;
                    }
                }
            }
        }
    }
    cout << dp[n][3] << endl;
    return 0;
}
```


---

## 作者：Z_M__ (赞：11)

再介绍一种新的递推方法：
$$
f[i] = (f[i-1]*2)+(f[i-2]*3)
$$

$f[i]$ 表示的是走 $i$ 步的方案数

---
### 1. 当走了 $i-1$ 步时：

- 如果此时在起点， 则不可能用 $1$ 步再回到起点， 所以这种情况不能转移。

- 如果此时不在起点，则用 $1$ 步可以回到起点，但我们没有存储这种状态， 所以这种情况不能转移。

- 那我们现在考虑在 $i-1$ 步能到起点的那些方案中，退 $1$ 步，如图：


![](https://cdn.luogu.com.cn/upload/image_hosting/kl0ncp67.png?x-oss-process=image/resize,m_lfit,h_300)


因为现在是处理 $i$ 步到达起点的方案数， 所以现在在 $f[i-1]$ 方案的基础上还有 $2$ 步，此时到达起点的方案则为 $2$ 种 （向左或向右），如图（蓝色和黄色的为两条路径）：

![](https://cdn.luogu.com.cn/upload/image_hosting/sg53t9ut.png?x-oss-process=image/resize,m_lfit,h_300)

- 所以在 $f[i-1]$ 中的每一种方案都有 $2$ 种方案对 $f[i]$ 产生贡献。

---

### 2. 当走了 $i-2$ 步时：

- 如果此时在起点， 则相对于 $f[i-2]$ 中的每一种方案都有 $3$ 种方案可以再次回到起点， 如图：


![](https://cdn.luogu.com.cn/upload/image_hosting/iwoucjxm.png?x-oss-process=image/resize,m_lfit,h_300)

- 所以在 $f[i-2]$ 中的每一种方案都有 $3$ 种方案对 $f[i]$ 产生贡献。

- **为什么这里不考虑退 $1$ 步了呢？**

这里退一步的方案与不退的方案其实是同一种方案。
退一步后，当前不在起点，还剩 $3$ 步，此时要用完 $3$ 步再回到起点的话，第一步只能先到起点（此时的方案不就与上面不退 $1$ 步的方案一样吗？），第二步走到任意顶点，第三步回到起点。

---
[代码](https://www.luogu.com.cn/paste/o3tr7kpp)

---

## 作者：Haphyxlos (赞：5)

# CF166E Tetrahedron
## 萌新的第一篇题解

[题目传送门](https://www.luogu.com.cn/problem/CF166E)

我们先来把题目翻译一下：

一只蚂蚁站在一个正四面体的顶点D上，求走过n（**1≤n≤1e7**）条棱后回到原顶点的方案总数对**1e9+7**取模。

注意，这里的**n≤1e7**，中文翻译里的n≤1e6翻译错了。

接着，我们再来打个表，推一下式子，用滚动数组优化一下空间，就能得到下面的核心代码。
```cpp
for(int i=1;i<=n;++i){
	int now=i&1,last=(i-1)&1;
	dp[now][0]=(dp[last][1]+dp[last][2]+dp[last][3])%mod;
	dp[now][1]=(dp[last][0]+dp[last][2]+dp[last][3])%mod;
	dp[now][2]=(dp[last][0]+dp[last][1]+dp[last][3])%mod;
	dp[now][3]=(dp[last][0]+dp[last][1]+dp[last][2])%mod; 
}

```
解释：

now指的是当前的位置，last指的是过去的位置，因为本题的状态只与当前和过去两个位置有关，所以就可以用滚动数组来节省空间。

但是，实际上本题并不需要写（当然啦，这么写也能AC）。稍加思考，就不难发现其实本题只有在顶点和不在顶点两个状态，然后稍加推导亿下。

推导（借鉴了其他的题解）：

到D点，距离为1的路径共有三条：A-D  B-D  C-D

同理，到A,B,C点，距离为1的路径共有9条：A-B  A-C  B-A  B-C  C-A  C-B A−B  A−C  B−A  B−C  C−A  C−B  D-A  D-B  D-C  D−A  D−B  D−C

由上面两条可得，now[i]=3 × last[i-1]，last[i]=now[i-1]+2 × last[i-1]。

然后，我们再将now数组和last数组压缩到一个dp数组中。由此，我们就能得到下面的核心代码。
```cpp
dp[1]=0,dp[2]=3;
for(int i=3;i<=n;++i){
	dp[i]=(2*dp[i-1]%mod+3*dp[i-2]%mod)%mod;
}
```
经过优化后，码量是少了，但空间实际上是要开到1e7的，对此，我们还珂以进一步优化。这里的写法其实就是上面的推导，只是将数组的使用也压缩掉了，大大地优化了空间复杂度。
```cpp
ll now,last=1,tmp;
for(int i=2;i<=n;++i){
	tmp=now,now=3*last%mod,last=(tmp+2*last)%mod;	
}
```
本篇题解就到此结束了，如果喜欢，还请点个赞吧。



---

## 作者：0x80 (赞：4)

第一篇题解，若有不足，请指出。

一道简单的DP题

设置两个数组$f$ 和$g$，分别表示在$D$点和不在$D$点。

可以看出到$D$点，距离为$1$的路径共有三条：
$A-D\quad B-D\quad C-D$ 

则可得$f_{i} = g_{i-1} * 3$

同理，到$A,B,C$点，距离为$1$的路径共有$9$条：
$A-B\quad A-C \quad B-A \quad B-C \quad C-A \quad C-B $

$D-A \quad D-B \quad D-C$

则可得$g_i = f_{i-1} + 2*g_{i-1} $

于是便可得以下代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007;
long long f[100000007],g[100000007];
int main(){
	int n;
	cin>>n;
	f[1]=0;
  	g[1]=1;
	for(int i=2;i<=n;i++){
		f[i]=3*g[i-1]%mod;
		g[i]=(f[i]+2*g[i])%mod;
	}
	printf("%lld",f[n]);
	return 0;
}

```
但是这样会MLE，所以我们要滚动优化：
AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007;
int main(){
	long long f=0,g=1;
	int n;
	cin>>n;
	for(int i=2;i<=n;i++){
		long long k=f;
		f=3*g%mod;
		g=(k+2*g)%mod;
	}
	printf("%lld",f);
	return 0;
}
```

---

## 作者：千秋星辰 (赞：3)

~~欸，绿题，1500分，切了~~

### 思路

首先这是一个4面体，记四个顶点为A,B,C,D的话：

![](https://cdn.luogu.com.cn/upload/image_hosting/719ykf6u.png)

可以看到每一个顶点都能**直接**到达其他顶点。

如果画出可能的路径图的话：

![](https://cdn.luogu.com.cn/upload/image_hosting/894kyrev.png)

不难看出，总方案数是$ 3^n $。

>那怎么找到符合条件(返回起点)的方案数呢？

很明显地看到，图中第一层（BCD这层）是没有A的，但是在第二层中有**3**个A，如果继续画图的话，第三层有**6**个A，结合样例中第四层有**21**个A，
规律不就浮出水面了吗？

$ 3+6=9=3^2 $


$ 6+21=27=3^3 $

设$ f[i] $ 为第 i 层中起点的个数 ~~(其实就是最终答案)~~，由上面的规律可知：

$ f[i]+f[i-1] = 3^{i-1} $

变形一下，得到了最终的递推式：

$ f[i]=3^{i-1}-f[i-1] $ , $ f[1]=0 $

### 实现

```cpp
#include<bits/stdc++.h>
#include<algorithm>
#define int long long
#define out(x) write(x),putchar(' ')
#define writen(x) write(x),putchar('\n')
#define forever() while(true)
using namespace std;

inline int read() // 快读 
{
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') y=-y;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<3)+(x<<1)+(c^'0');
	return x*y;
}

inline void write(int x) // 快写 
{
	if(x<0) x=-x,putchar('-');
	if(x>9) write(x/10);
	putchar(x%10+'0');
}

int n,base,ans;
const int mod=1e9+7; // 结果取余 

signed main()
{
	n=read();
	base=3; // base是3^(i-1),这里从3开始乘 
	for(int i=2;i<=n;i++)
	{
		ans=base-ans; // 递推式,这里为了压低空间把数组改成普通变量 
		ans=(ans%mod+mod)%mod; // 好事多模 
		base=base*3%mod; // 在循环中顺便模拟乘方 
	}
	write(ans);
	return 0;
}
```

---

## 作者：EDqwq (赞：3)

### 思路：

**我发现没有任何一篇题解解释为什么会推出这个东西，我这一篇题解就要带大家理性理解这个递推。**

首先，我们设 $dp_i$ 为走 $i$ 步回到原点的情况数。

首先，走 $i$ 步有可能的情况数，显然为 $3^n$ 种。

但是这些情况中，可能有一部分是不能回到原点的，我们要排除。

所以到底是哪一部分呢？

我们会发现， $dp_{i-1}$ 表示的是上一步走到原点的情况数，而你上一步走到了原点，这一步显然必定走出去，所以我们要排除的是这一部分。

所以，我们得出方程：

$$dp_i = 3^n - dp_{i-1}$$

***

### 代码：

```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x) memset(x,0,sizeof(x))
#define mod 1000000007

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int n;
int dp[10000010];
int now = 1;

signed main(){
	cin>>n;
	dp[1] = 0;
	for(int i = 2;i <= n;i ++){
		now *= 3;
		now %= mod;
		dp[i] = (now - dp[i - 1]) % mod;
	}
	cout<<((dp[n] + mod) % mod + mod) % mod;
	return 0;
}
```

---

## 作者：开始新的记忆 (赞：3)

题目大意：现在有一个正四面体，有一个人站在D点，每步他都可以走到另外三个点（不能不走），现在求n步后，这个人有多少种走法使得最后他回到D点。

大致思路：我们一开始可以先打表找规律。发现f[n]=3^n-f[n-1]
```
1  2  3  4  5
0  3  6  21 60
```
我们一一递推发现f[n]=3^n-3^(n-1)+3^(n-2)……(-1)^n*3（蒟蒻不会LaTeX），于是只需On求出即可，如果是1e9的数据，就得用矩阵加速递推了。

###### PS：最后算出来的ans要判断负数的情况，有可能会<0所以我们要先+P再%P!

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define P 1000000007
ll t=1,ans=0;
int n;

int main()
{	cin>>n;
	for(int i=2;i<=n;++i)
	{
		t=t*3%P;
		if(i%2==n%2)
			ans+=t;
		else
			ans-=t;
		ans%=P;
	}
	cout<<(ans+P)%P<<endl;
	return 0;
}
```


---

## 作者：Steadywelkin (赞：3)

题解区中已经有了很多的递推做法，这里给出一个矩阵做法。

四面体有一个非常优良的性质：每一个顶点都可以只通过一条边就达到其他任何一个顶点。所以如果假设四个顶点的编号分别为 $A,B,C,D$ ，在第 $i$ 移动中到达这四个顶点的方案数为 $A_i,B_i,C_i,D_i$ ，则有：

> $A_{i+1}=B_i+C_i+D_i$

> $B_{i+1}=A_i+C_i+D_i$

> $C_{i+1}=A_i+B_i+D_i$

> $D_{i+1}=A_i+B_i+C_i$

将上面的式子转化为矩阵：

$\begin{bmatrix}
0 & 1 & 1 & 1\\
1 & 0 & 1 & 1\\
1 & 1 & 0 & 1\\
1 & 1 & 1 & 0
\end{bmatrix}$

之后用矩阵快速幂就可以实现答案的求解了。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <ctime>
#include <algorithm>
using namespace std;
typedef long long ll;

inline int read()
{
	int a=0,f=1;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar())
		if(ch=='-')f=-1;
	for(;isdigit(ch);ch=getchar())
		a=(a<<3)+(a<<1)+ch-'0';
	return a*f;
}

const int mod=1e9+7;
const int N=1e6+5;

struct matrix
{
	ll m[5][5];
	matrix(){memset(m,0,sizeof(m));}
	inline void start(void)
	{
		memset(m,0,sizeof(m));
		for(int i=1;i<=4;i++)
			m[i][i]=1;
		return;
	}
	inline void build(void)
	{
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
				if(i!=j)m[i][j]=1;
				else m[i][j]=0;
		return;
	}
	inline friend matrix operator*(matrix a,matrix b)
	{
		matrix c;
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
				for(int k=1;k<=4;k++)
					c.m[i][j]=(c.m[i][j]+a.m[i][k]*b.m[k][j]%mod)%mod;
		return c;
	}
}k;

inline ll qpow(matrix a,ll n)
{
	matrix ans;
	ans.start();
	for(;n;n>>=1)
	{
		if(n&1) ans=ans*a;
		a=a*a;
	}
	return ans.m[1][1];
}

signed main()
{
	int n=read();
	k.build();
	printf("%lld\n",qpow(k,n));
	return 0;
}

```


---

## 作者：wz20201136 (赞：3)

# 思路
动态规划：

状态： $dp[i][j]$ 表示第 $i$ 步到达第 $j$ 个顶点的方案数；

初始化： $dp[0][1]=0$ ；

转移： $dp[i][j]+=dp[i-1][k] $ ( $k$ 为1-4除了 $j$ )；

# 代码
根据上述思路，写出以下代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[10000005][5],n;
int main()
{
	cin>>n;
	dp[0][1]=1;
	for(int i=1;i<=n;i++)
	{
    		//转移
		dp[i][1]=(dp[i-1][2]+dp[i-1][3]+dp[i-1][4])%(1000000007);
		dp[i][2]=(dp[i-1][1]+dp[i-1][3]+dp[i-1][4])%(1000000007);
		dp[i][3]=(dp[i-1][2]+dp[i-1][1]+dp[i-1][4])%(1000000007);
		dp[i][4]=(dp[i-1][2]+dp[i-1][3]+dp[i-1][1])%(1000000007);
	}
	cout<<dp[n][1];
	return 0;
}
```
但是， $WA$ 了。。。

原因：三个<= $1e9+7$ 的数加起来爆精度了；

开了 $long$ $long$ :
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int dp[10000005][5],n;
main()
{
	cin>>n;
	dp[0][1]=1;
	for(int i=1;i<=n;i++)
	{
		dp[i][1]=(dp[i-1][2]+dp[i-1][3]+dp[i-1][4])%(1000000007);
		dp[i][2]=(dp[i-1][1]+dp[i-1][3]+dp[i-1][4])%(1000000007);
		dp[i][3]=(dp[i-1][2]+dp[i-1][1]+dp[i-1][4])%(1000000007);
		dp[i][4]=(dp[i-1][2]+dp[i-1][3]+dp[i-1][1])%(1000000007);
	}
	cout<<dp[n][1];
	return 0;
}
```
但是 $MLE$ 了

于是开了滚动数组，就 $AC$ 了

$AC$ 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int dp[3][5]/*滚动数组*/,n;
main()
{
	cin>>n;
	dp[0][1]=1;
	for(int i=1;i<=n;i++)
	{
    		//i%2表示i;(i+1)%2表示i-1
		dp[i%2][1]=(dp[(i+1)%2][2]+dp[(i+1)%2][3]+dp[(i+1)%2][4])%(1000000007);
		dp[i%2][2]=(dp[(i+1)%2][1]+dp[(i+1)%2][3]+dp[(i+1)%2][4])%(1000000007);
		dp[i%2][3]=(dp[(i+1)%2][2]+dp[(i+1)%2][1]+dp[(i+1)%2][4])%(1000000007);
		dp[i%2][4]=(dp[(i+1)%2][2]+dp[(i+1)%2][3]+dp[(i+1)%2][1])%(1000000007);
	}
	cout<<dp[n%2][1];
	return 0;
}
```

---

## 作者：Zhou_Wingay (赞：1)

### 一般情况解决这种方案种数的问题都用DP，所以这题也用DP。

很明显，这题有两种状态：在原顶点或不在原顶点。

设：$f[i]$表示走$i$步回到原点的方案数，$f1[i]$表示走$i$步回到不原点的方案数。

由于原点可以由另外3个点到达，所以$f[i]=f1[i-1]\times 3$。

同理，其他的点可以由原点和另外2个点到达，所以$f1[i]=f[i-1]+f1[i-1]\times2$。

然后可以发现可以使用滚动数组，所以使用滚动数组。

最后就是代码了：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long f1={1};//因为最开始在原点，所以f1初值为1
long long f2;
int main(){
	long long i,j,n;
	cin>>n;
	for(i=1;i<=n;i++){
      		long long x,y;
     		x=f1;y=f2;
		f1=y*3%1000000007;//注意要取模
		f2=(x+y*2)%1000000007;
	}
	cout<<f1;
	return 0;
}
```


---

## 作者：huangruiheng0217 (赞：0)

标签里有逆元，但是想不到和逆元有什么关系。

考虑 dp。

状态的设计：$\mathit{f}_{i,j}$

$i$ 表示顶点的编号即 $1-4$。

$j$ 表示当前走过 $k$ 步。

初始状态 $\mathit{f}_{1,0}=1$。（废话一步不走的方案肯定是 $1$）

转移还是暴力一点好。

$\mathit{f}_{1,k}=\mathit{f}_{2,k-1}+\mathit{f}_{3,k-1}+\mathit{f}_{4,k-1}$

$\mathit{f}_{2,k}=\mathit{f}_{1,k-1}+\mathit{f}_{3,k-1}+\mathit{f}_{4,k-1}$

$\mathit{f}_{3,k}=\mathit{f}_{1,k-1}+\mathit{f}_{2,k-1}+\mathit{f}_{4,k-1}$

$\mathit{f}_{4,k}=\mathit{f}_{1,k-1}+\mathit{f}_{2,k-1}+\mathit{f}_{3,k-1}$

显然一个点能且只能从另外三个点转移过来。

注意还要取模。

然后你以为自己水了一道绿题。

实际上空间炸了。

所以用滚动数组。

还有一种同时优化时空的方式，矩阵。

但是本题不需要。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e7+10,p=1e9+7;
int n,f[5][2];
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	f[1][0]=1;
	for(int i=1;i<=n;i++){
		f[1][i%2]=(f[2][(i+1)%2]+f[3][(i+1)%2]+f[4][(i+1)%2])%p;
		f[2][i%2]=(f[1][(i+1)%2]+f[3][(i+1)%2]+f[4][(i+1)%2])%p;
		f[3][i%2]=(f[1][(i+1)%2]+f[2][(i+1)%2]+f[4][(i+1)%2])%p;
		f[4][i%2]=(f[1][(i+1)%2]+f[2][(i+1)%2]+f[3][(i+1)%2])%p;
	}
	cout<<f[1][n%2]<<endl;
	return 0;
}
```

---

## 作者：Siteyava_145 (赞：0)

大水题。

dp。

把原图转换成

![](https://cdn.luogu.com.cn/upload/image_hosting/8umtlplb.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

（初始状态）

标的数为走到这个点的方案数。

每走一次，点的方案数将变成其他三个点的方案数和。

很好理解：这个图任意两点连通，且没有自环，所以走到这个点，只有从其他三个点出发才能到达。

于是推出转移方程 $dp_i=\sum\limits_{j=1}^4[j\ne i]\cdot dp_j$
。

要新建一个数组，为存储走过以后的状态，然后再平移到 $dp$ 数组里，防止数据互相干扰。

代码：

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
int n;
long long dp[5],nd[5];
int main(){
    cin>>n;
    dp[1]=1;
    for(int i=1;i<=n;i++){
        nd[1]=(dp[2]+dp[3]+dp[4])%mod;
        nd[2]=(dp[1]+dp[3]+dp[4])%mod;
        nd[3]=(dp[2]+dp[1]+dp[4])%mod;
        nd[4]=(dp[2]+dp[3]+dp[1])%mod;
        dp[1]=nd[1];
        dp[2]=nd[2];
        dp[3]=nd[3];
        dp[4]=nd[4];
    }
    cout<<dp[1]%mod<<endl;
}
```


---

## 作者：Aw顿顿 (赞：0)

怎么 DP？设 $a_i$ 表示经过了 $i$ 步后回到了原顶点，而 $b_i$ 表示没回到原顶点。

现在走了 $i-1$ 步，假设想要走到顶点，一共有三条路，全部都是从非顶点出发，因此 $a_i=3b_{i-1}$。

如果不想走到顶点，则可以从两个非顶点出发，或者从顶点出发，所以 $b_i=a_{i-1}+2b_{i-1}$。

写出递推：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define int long long 
int n,a[10000005],b[10000005];
signed main(){
	cin>>n;b[1]=1;
	for(int i=2;i<=n;i++){
		a[i]=3*b[i-1]%mod;
		b[i]=(a[i-1]+2*b[i-1])%mod;
	}printf("%lld\n",a[n]);
	return 0;
}
```

然后就可以 AC 了。另外这个东西可以滚动数组卷掉省空间。

---

## 作者：king_xbz (赞：0)

比较基础的递推题目，偶然做到，发一篇题解分享一下。

由于状态单一（步数），而且数据范围较大($1e7$)所以我们肯定使用一维DP来解决。

那么我们设$f[i]$表示走了$i$步的方案数。

比如说从D出发，走1步，可以走到A，B，C三个位置，方案数三种，其中能回到原点的有零种.

走两步，可以走DAB，DAC，DBC，DBA，DCB，DCA，DAD，DBD，DCD9个方案，其中回到原点的三种.

先分类讨论，用$f[i][0],f[i][1]$分别表示回不到原点的方案数和能回的方案数。

我们记录$f[1][0]=3,f[1][1]=0,f[2][0]=6,f[2][1]=3$

继续手算：

$f[3][0]=21,f[3][1]=6$

由于每一步都可以走向除自身外三个位置的任一个，但是只有本步不是D的方案总数的三分之一能回到D，

所以可以很轻易推出来，走$n$步的总方案数是$3^{n}$种，其中回到原点的有$3^{n-1}-3^{n-2}$种

我们把第二维压掉，也就是只考虑能回到原点的情况

也就是说$f[i]=3^{i-1}-f[i-1]$

那么硬艹就完了。

代码：

```cpp
#include<bits/stdc++.h>
#define fint register int
#define int long long
#define N 11347845
#define H 5001
using namespace std;
const int mods=1e9+7;
int f[N];
signed main()
{
	int n;
	cin>>n;
	f[1]=0;
	int bas=3;
	for(fint i=2;i<=n;i++)
	{
		f[i]=bas-f[i-1];
		f[i]=(f[i]%mods+mods)%mods;
		bas*=3LL;
		bas%=mods;
	}
	cout<<f[n];
	return 0;
}
```



---

