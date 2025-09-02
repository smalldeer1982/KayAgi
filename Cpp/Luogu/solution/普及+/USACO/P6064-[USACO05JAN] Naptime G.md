# [USACO05JAN] Naptime G

## 题目描述

贝茜是一只非常缺觉的奶牛．她的一天被平均分割成 $N$ 段（$3 \leq N \leq 3830$），但是她要用其中的 $B$ 段时间（$2 \leq B \lt N$）睡觉。每段时间都有一个效用值 $U_i$（$0 \leq U_i \leq 2 \times 10^5$），只有当她睡觉的时候，才会发挥效用。

有了闹钟的帮助，贝茜可以选择任意的时间入睡，当然，她只能在时间划分的边界处入睡、醒来。

贝茜想使所有睡觉效用的总和最大。不幸的是，每一段睡眠的第一个时间阶段都是“入睡”阶段，而旦不记入效用值。

时间阶段是不断循环的圆（一天一天是循环的嘛），假如贝茜在时间 $N$ 和时间 $1$ 睡觉，那么她将得到时间 $1$ 的效用值。

## 说明/提示

从第 $4$ 个时段入睡，到第 $1$ 个时段结束醒来。

## 样例 #1

### 输入

```
5 3
2
0
3
1
4```

### 输出

```
6```

# 题解

## 作者：_Andy_Lin_ (赞：38)

[双倍经验](https://www.luogu.com.cn/problem/SP283)

------------
先来考虑一个“简化版”：假设第N个小时与次日第一个小时不是相连的，那么这就是一个明显的DP题：

用$dp_{i,j,0/1}$来表示在第i个小时，已经休息了j个小时，0表示这个小时没在休息，1表示这个小时正在休息。

状态转移方程就是：
```cpp
dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]);
dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+u[i]);
```
初值：$dp_{1,1,1}=0$，$dp_{1,0,0}=0$，其余为-INF。

答案：$\max(dp_{n,b,0},dp_{n,b,1})$。

------------
但问题是第N个小时与次日第一个小时是相连的，上面的方法不能直接用。既然这样，那就再来一次强制连接：

强制让第N个小时睡觉，让次日第一个小时熟睡。

状态转移方程如上。

初值：$dp_{1,1,1}=u_{1}$，$dp_{1,0,0}=0$，其余为-INF。

答案：$dp_{n,b,1}$

------------
具体来说，我们可以先将第N个小时与次日第一个小时断开，然后用上面的“简化版”的方法来得到一个答案。再强制让第N个小时睡觉，让次日第一个小时熟睡，用上面讨论的强制连接的方法得到第二个答案，两者取最大值即可。

------------
$AC\ Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[3831][3831][2],n,b,u[3831],ans;
int main() {
	scanf("%d%d",&n,&b);
	for(int i=1;i<=n;i++)scanf("%d",u+i);
	memset(dp,-0x3f,sizeof(dp));
	dp[1][1][1]=dp[1][0][0]=0;
	for(int i=2;i<=n;i++){
		dp[i][0][0]=dp[i-1][0][0];
		for(int j=1;j<=b;j++){
			dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]);
			dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+u[i]);
		}
	}
	ans=max(dp[n][b][0],dp[n][b][1]);
	memset(dp,-0x3f,sizeof(dp));
	dp[1][1][1]=u[1];
	dp[1][0][0]=0;
	for(int i=2;i<=n;i++){
		dp[i][0][0]=dp[i-1][0][0];
		for(int j=1;j<=b;j++){
			dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]);
			dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+u[i]);
		}
	}
	ans=max(ans,dp[n][b][1]);
	printf("%d\n",ans);
	return 0;
}
```
这是一个比较常见的解决环形DP的策略，一定要记住

---

## 作者：MeowScore (赞：6)

## 题目大意


------------
给一个环，有 $N$ 个有权值的节点。选取其中的 $B$ 个，使其权值和最大，但是对于每一段节点连续的区间，第一个点的权值不计入答案（“第一个”当然是从同一个方向而言）。


------------
## 解决方案
很明显是环形 DP 啊。要思考这道题，不妨假设第 $N$ 个点和第 $1$ 个点是断开的。

我们**设 $f_{i,j,1}$ 指前 $i$ 个点中取了 $j$ 个，且当前点选择了。设 $f_{i,j,0}$ 指前 $i$ 个点中取了 $j$ 个，且当前点没有选择**。如果前 $i$ 个点中取了 $j$ 个，且前一个点选上了，那么 $f_{i,j,1}$ 就应该是从以下两种方案取最大值：前一个数没选，当前数是接下来一串元素的首个；前一个数选了，我们把当前数加到前一个数选了的答案中（方程中注意 $j$ 要减 $1$！因为前 $i$ 个数中选的 $j$ 个数包含了当前数字）。如果当前数不选，也差不多，看看方程也好理解。转移方程如下：
```
f[i][j][1]=max(f[i-1][j-1][0],f[i-1][j-1][1]+w[i]);
f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);

```
别忘了初始化！

```
f[1][0][0]=0;
f[1][1][1]=0;
//其余为负无穷
```

然而残酷的是，前面的一切都建立在一个美好的设想上：第 $N$ 个点和第 $1$ 个点是断开的。那么我们应该如何处理这一点呢？


------------

#### 方法一

受[石子合并](https://www.luogu.com.cn/problem/P1880)启发，设第 $N$ 个点和第 $1$ 个点是断开的，我们考虑把这个区间复制一份放到原来的这个区间后面，然后 DP。最后从这个长度为 $2 * N$ 的区间里所有长度为 $N$ 的情况中取最优解。但我没这么搞，而且空间似乎有问题。不知道行不行得通，反正我们有更好的方法！！！

#### 方法二

我们分类讨论DP 两次！

##### 情况一

第 $N$ 个数不选。这样即使选了第 $1$ 个数，它的值也没什么用，所以完全可以假设第 $N$ 个点和第 $1$ 个点是断开的了。

##### 情况二

第 $N$ 个数选。这样就不可以假设第 $N$ 个点和第 $1$ 个点是断开的了。但这样我们可以强制选取第 $N$ 个数。第 $N$ 个数选了，那么第 $1$ 个数的权值就可以发挥作用了。转移方程不变，只要改动一下初始化即可：
```
f[1][0][0]=0;
f[1][1][1]=w[1];
//其余为负无穷
```


------------
## 上代码
```
#include<bits/stdc++.h>
using namespace std;
int w[3840];
int f[3840][3840][2];
int INF=0x3f3f3f3f;
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>w[i];
	memset(f,-0x3f,sizeof f);
	f[1][0][0]=0;
	f[1][1][1]=0;
	for(int i=2;i<=n;i++){
		for(int j=0;j<=m;j++){
			f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);
			f[i][j][1]=-INF;
			if(j)
				f[i][j][1]=max(f[i-1][j-1][0],f[i-1][j-1][1]+w[i]);
		}
	}
	int ans=f[n][m][0];
	memset(f,-0x3f3f3f,sizeof f);
	f[1][0][0]=0;
	f[1][1][1]=w[1];
	for(int i=2;i<=n;i++){
		for(int j=0;j<=m;j++){
			f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);
			f[i][j][1]=-INF;
			if(j)
				f[i][j][1]=max(f[i-1][j-1][0],f[i-1][j-1][1]+w[i]);
		}
	}
	ans=max(f[n][m][1],ans);
	cout<<ans<<endl;
}
```
下面这个加了滚动数组，吸口氧就是目前最优解哦！（~~其实是大佬们懒得吸氧~~）

```
#include<bits/stdc++.h>
using namespace std;
int w[3840];
int f[2][3840][2];
int INF=0x3f3f3f3f;
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>w[i];
	memset(f,-0x3f3f3f,sizeof f);
	f[1][0][0]=0;
	f[1][1][1]=0;
	for(register int i=2;i<=n;i++){
		for(register int j=0;j<=m;j++){
			f[i&1][j][0]=max(f[(i+1)&1][j][0],f[(i+1)&1][j][1]);
			f[i&1][j][1]=-INF;
			if(j)
				f[i&1][j][1]=max(f[(i+1)&1][j-1][0],f[(i+1)&1][j-1][1]+w[i]);
		}
	}
	int ans=f[n&1][m][0];
	memset(f,-0x3f3f3f,sizeof f);
	f[1][0][0]=0;
	f[1][1][1]=w[1];
	for(register int i=2;i<=n;i++){
		for(register int j=0;j<=m;j++){
			f[i&1][j][0]=max(f[(i+1)&1][j][0],f[(i+1)&1][j][1]);
			f[i&1][j][1]=-INF;
			if(j)
				f[i&1][j][1]=max(f[(i+1)&1][j-1][0],f[(i+1)&1][j-1][1]+w[i]);
		}
	}
	ans=max(f[n&1][m][1],ans);
	cout<<ans<<endl;
}
```

---

## 作者：linyinuo2008 (赞：5)

## Update on 2020.12.1
首先，感谢一下大佬们对我的启发。~~（不然我可能一辈子都没法AC）~~

下面开始正题。


------------
# Step 1：分析动归方程
先假设没有一天一天循环。

设$f(i,j,0/1)$表示从第i个小时开始，已经睡了j个小时，当前有没有在睡觉（0表示不在睡觉，1表示在睡觉）。


动归方程：

（初始化为$f(1,1,1)=f(1,1,0)=f(1,0,0)$,其他为-0x3f）
	
    
```cpp
f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);

f[i][j][1]=max(f[i-1][j-1][1]+a[i],f[i-1][j-1][0]);
```



  
结果：$max(f(n,b,0),f(n,b,1))$



------------
# Step 2：改进动归方程
这题一看就能看出来是环形区间dp，而解决这种问题最常见的方法有两种。

- **倍长区间**
- **强制连接**

个人比较推荐第一种
~~（我绝对不会告诉你因为我不会第二种）~~。

但是这题倍长找不出关系，所以只好强制连一下了。

步骤为：先按step 1中的dp一遍，再强制让第一个小时熟睡dp一遍。也就是说第二遍初始化时让$f(1,1,1)$=$a[1]$ 就可以了。

结果：	$f(n,b,1)$ (由于第一个小时必须熟睡）



------------
以上两个结果取最大值就可以了。


------------
# Step 3：Code
下面附上代码：
```cpp
#include <iostream>
#include <cstring>
using namespace std;

int n,b,a[3831],ans;
int f[3831][3831][2];//f[i][j][0、1]表示从第i段开始睡j段当前（没睡、睡）的最大u

int max(int a,int b)//自己写的max，更快
{
	return a>b?a:b;
}

void read()//读入
{
	int i;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
	}
}

void dp()//动归函数
{
	int i,j;
	for(i=2;i<=n;i++)
	{
		f[i][0][0]=f[i-1][0][0];
		for(j=1;j<=b;j++)
		{
			f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);
			f[i][j][1]=max(f[i-1][j-1][1]+a[i],f[i-1][j-1][0]);
		}
	}
}

int main()
{
	int i;
	memset(f,-0x3f,sizeof(f));//初始化为-inf
	cin>>n>>b;
	read();
	f[1][1][1]=0;
	f[1][1][0]=0;
	f[1][0][0]=0;
	dp();
	ans=max(f[n][b][0],f[n][b][1]);
	memset(f,-0x3f,sizeof(f));
	f[1][1][1]=a[1];
	f[1][0][0]=0;
	f[1][1][0]=0;
	dp();
	ans=max(ans,f[n][b][1]);//取最大
	cout<<ans<<endl;//输出
	return 0;
}

	

```





# 第一篇题解，求通过！




---

## 作者：lndjy (赞：3)

小清新 dp 题。

设 $f_{i,j,0/1}$ 为前 $i$ 段睡了 $j$ 段且目前这段睡没睡，$1$ 表示睡了。

转移方程：

$$f_{i,j,0}=\max(f_{i-1,j,0},f_{i-1,j,1})$$

$$f_{i,j,1}=\max(f_{i-1,j-1,0},f_{i-1,j-1,1}+a_i)$$

$\max(f_{n,b,0},f_{n,b,1})$ 就是答案。

但是，这样不能处理环。可以通过强制选第一个和强制不选第一个这两个情况分别做一次 dp 来解决。

强制不选的初始化是 $f_{1,1,1}=0$，强制选的初始化就是 $f_{1,1,1}=a_1$。

核心代码：

```cpp
void solve()
{
	memset(f,128,sizeof f);
	cin>>n>>b;
	for(int i=1;i<=n;i++)
	cin>>a[i];
	f[1][1][1]=0;
	for(int i=1;i<=n;i++) f[i][0][0]=0;
	for(int i=2;i<=n;i++)
	for(int j=1;j<=b;j++)
	{
		f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);
		f[i][j][1]=max(f[i-1][j-1][0],f[i-1][j-1][1]+a[i]);
	 } 
	 int ans=max(f[n][b][0],f[n][b][1]);
	 memset(f,128,sizeof f);
	 f[1][1][1]=a[1];
	 for(int i=1;i<=n;i++) f[i][0][0]=0;
	 for(int i=2;i<=n;i++)
	 for(int j=1;j<=b;j++)
	 {
		f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);
		f[i][j][1]=max(f[i-1][j-1][0],f[i-1][j-1][1]+a[i]);
	 }
	 cout<<max(ans,f[n][b][1])<<endl;
} 
```


---

## 作者：月雩·薇嫭 (赞：2)

------------


**星影落九天，鱼雁舞千弦。但为君沉吟，落日天涯圆。**

------------
[[题目传送门]](https://www.luogu.com.cn/problem/P6064)

先考虑若不是环的情况

设状态为$dp[i][j][0/1]$：

$dp[i][j][0]$表示前$i$段睡了$j$段且**第**$i$**段没睡**前$i$段的最大效用值

$dp[i][j][1]$表示前$i$段睡了$j$段且**第**$i$**段睡了**前$i$段的最大效用值

那么**状态转移方程**即为：
$$
	dp_{i,j,0}=max(dp_{i-1,j,0},dp_{i-1,j,1})$$
$$
	dp_{i,j,1}=max(dp_{i-1,j-1,0}+0,dp_{i-1,j-1,1}+a_{i})$$
    
$dp_{i,j,0/1}$的初值为-INF

那么**对于环**，只需要强制连接第$n$段与第$1$段

即：将$dp_{1,0,0}$的初值赋为$a_{1}$即可

## Code

```cpp
#include<bits/stdc++.h>
#define FQ(i,a,b) for(register int i=a;i<=b;i++)
#define prf printf
#define scf scanf
#define ll long long
using namespace std;
int INF;
const int N=3835;
int n,m,ans,a[N],F[N][N][2];
ll read()
{
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main()
{
	INF=-128/2;
	n=read(),m=read();memset(F,INF,sizeof(F));
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)F[i][0][0]=0;F[1][1][1]=0;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=m;j++)
		{		
			F[i][j][0]=max(F[i-1][j][0],F[i-1][j][1]);		
			F[i][j][1]=max(F[i-1][j-1][0]+0,F[i-1][j-1][1]+a[i]);		
		}	
	ans=max(F[n][m][1],F[n][m][0]);	
	memset(F,INF,sizeof(F));
	for(int i=1;i<=n;i++)F[i][0][0]=0;F[1][1][1]=a[1];
	for(int i=2;i<=n;i++)
		for(int j=1;j<=m;j++)
		{	
			F[i][j][0]=max(F[i-1][j][0],F[i-1][j][1]);	
			F[i][j][1]=max(F[i-1][j-1][0]+0/*不计i的效用值*/,F[i-1][j-1][1]+a[i]);	
		}
	ans=max(ans,F[n][m][1]);
	printf("%d\n",ans);
	return 0;	
} 
```


---

## 作者：云岁月书 (赞：2)

## 题目分析：

首先是一个线性 DP,这一点很重要，我都不知道一开始我为什么想成了想成了单调队列优化的神仙区间 DP，这就没救了。

考虑一般情况，如果不是在环上的话，DP 状态是很明显的：

首先一定要记录目前的答案是到哪为止的。

其次，必然会记录当前点是否在睡。

最后，必不可少的已经睡了了多长的时间。

综上状态便是一个三维数组 $dp[N][B][2]$。

第一维记录处理到那个点，第二维纪录已睡的时间，第三位就是是否在睡。

状dp态出来了,转移方程也就比较显然:
$$dp[i][j][x]=
\begin{cases}
&max\left(dp[i-1][j][0],dp[i-1][j][1])\right) &x = 0\\
&max\left(dp[i-1][j-1][0],dp[i-1][j-1][1]+a[j])\right)&x = 1\\   
\end{cases}$$

观察到每一层状态只会从上一层转移，故可以使用滚动数组来进一步优化空间。

接下来回到原问题,考虑处理环上问题的办法：
- 倍长
- 强制链接

仔细考虑发现倍长并不好处理，由转移的一些问题导致很难统计答案。

故使用强制链接。

做完上面序列上的 DP 后，强制选择 1 号点睡觉，再 DP 一次，但注意，此时统计的答案就只能是 $dp[n][B][1]$。

Code:
~~~c++
\\ Code by 云岁月书
# include <ctime>
# include <cmath>
# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <algorithm>
# define N 3830
# define max std::max

inline int Read()
{
    register int x = 0;char ch = getchar();

    while(ch < '0' || ch > '9')ch = getchar();

    while(ch >= '0' && ch <= '9'){x = x*10+(ch^48);ch = getchar();}

    return x;
}

inline int Max(const int x,const int y){return x > y ? x : y;}
inline int Min(const int x,const int y){return x < y ? x : y;}

int n,m,f[2][N+5][2],a[N+5],ans;

void DP()
{
    for(int i = 2; i <= n ; ++i)
	{
		f[i&1][0][0] = f[(i^1)&1][0][0];
		for(int j = 1; j <= m ; ++j)
        {
            f[i&1][j][0] = max(f[(i^1)&1][j][0],f[(i^1)&1][j][1]);
            f[i&1][j][1] = max(f[(i^1)&1][j-1][0],f[(i^1)&1][j-1][1]+a[i]);
        }
	}
}

int main()
{
    n = Read();m = Read();
    for(int i = 1; i <= n ; ++i) a[i] = Read();
    if(m == 0) return printf("0\n"),0;
    memset(f,-0x3f,sizeof(f));
    f[1][0][0] = f[1][1][1] = 0;//注意一下初始状态的处理
    DP();
    ans = max(f[n&1][m][0],f[n&1][m][1]);
    memset(f,-0x3f,sizeof(f));
    f[1][1][1] = a[1];
    DP();
    ans = max(ans,f[n&1][m][1]);
    printf("%d\n",ans);
    return 0;
}
~~~

---

## 作者：Mortis_Vampire (赞：1)

参考资料~~抄自~~：《算法竞赛：进阶指南》
## 算法分析
这是一道经典的环形 DP 问题。

环形 DP 的一种经典解决方案是选择一个位置把环断开，变成线性结构进行计算。

对于这道题，我们可以先考虑第 N 个小时和下一天的第 1 个小时不相连的情况，这样着就成了一道线性 DP：

设 $F_{i,j,0/1}$ 表示前 $i$ 个小时休息了 $j$ 个小时，第 $i$ 个小时 没有休息/正在休息。

则有状态转移方程：

$$F_{i,j,0}=max(F_{i-1,j,0},F_{i-1,j,1})$$
$$F_{i,j,1}=max(F_{i-1,j-1,0},F_{i-1,j-1,1}+U_i)$$

在这个简化的问题中，第 1 个小时一定是每天的开始，不可能处于熟睡状态。  
因此 DP 的初值为 $F_{1,0,0}=0,F_{1,1,1}=0$，其余为 $-inf$。

目标为：$max(F_{N,B,0},F_{N,B,1})$。

我们发现此时的线性 DP 问题只比原来的环形 DP 问题少一种情况，即在第 1 个小时熟睡，并且此时可以获得体力，也就是说第 N 天也必须在休息。  
为达到这个目的我们只需要强制修改初值 $F_{1,1,1}=U_1$ ，其余值为 $-inf$ ,所求目标为 $F_{N,B,1}$ 即可。

最终答案为两次 DP 结果的较优者。

本质解法就是把问题拆成两部分进行求解。第一部分不可能在第 1 小时恢复体力，而第二部分强制在第 1 小时获得体力。
## Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define inf 0x7fffffff
using namespace std;
int n,B,a[3831],f[3831][3831][2];
void dp()//DP部分
{
	for(int i=2; i<=n; i++)
		for(int j=0; j<=B; j++) {
			f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);//状态转移方程
			if(j-1>=0) {
				f[i][j][1]=max(f[i-1][j-1][0],f[i-1][j-1][1]+a[i]);
			}
		}
}
int main() {
	cin>>n>>B;
	for(int i=1; i<=n; i++)
		cin>>a[i];
	memset(f,-0x3f,sizeof(f));//第一次DP赋初值
	f[1][0][0]=0;
	f[1][1][1]=0;
	dp();//第一次DP
	int ans=max(f[n][B][1],f[n][B][0]);
	memset(f,-0x3f,sizeof(f));//第二次DP赋初值
	f[1][1][1]=a[1];
	dp();//第二次DP
	cout<<max(ans,f[n][B][1]);//输出两次DP结果较优者
	return 0;
}
```


---

## 作者：EricQian (赞：1)

[P6064 [USACO05JAN]Naptime G](https://www.luogu.com.cn/problem/P6064)

算法：线性 $\operatorname{DP}$

### $step~1$ ：列出基础转移方程

先不考虑第 $n$ 个小时与次日第 $1$ 个小时连续 。

设 $dp[i][j][0/1]$ 表示在第 $i$ 个小时，已经在床上躺了 $j$ 个小时，$0$ 表示这个小时没在床上，$1$ 表示这个小时正躺在床上 。

转移方程：（ 初始值 $dp[1][0][0]=dp[1][1][1]=0$ ，其他为 $-\inf$ ）

$$\begin{cases}dp[i][j][0]=\max{\{dp[i-1][j][0],dp[i-1][j][1]\}}\\dp[i][j][1]=\max{\{dp[i-1][j-1][0],dp[i-1][j-1][1]+u[i]\}}\end{cases}$$

目标：$\min{\{dp[n][b][0],dp[n][b][1]\}}$ 。

### $step~2$ ：完善转移方程

考虑第 $n$ 个小时与次日第 $1$ 个小时连续 ，即强制第第 $n$ 个小时睡觉 。

初始值：$dp[1][0][0]=0,dp[1][1][1]=u[1]$ ，其他为 $-\inf$ 。

目标：$dp[n][m][1]$ 。

最终答案为两种情况的较大值。

~~完整~~代码：

```cpp
#define inf 0x7f7f7f7f
#define Maxn 3835
int n,b,ans,a[Maxn],dp[Maxn][Maxn][2];

// 一下代码片段插入在 main 函数中 
n=rd(),b=rd();
for(int i=1;i<=n;i++) a[i]=rd();
memset(dp,-inf,sizeof(dp)),dp[1][1][1]=dp[1][0][0]=0;
for(int i=2;i<=n;i++)
{
 	 dp[i][0][0]=dp[i-1][0][0];
	 for(int j=1;j<=b;j++)
	 {
	 	 dp[i][j][0]=max(dp[i-1][j][1],dp[i-1][j][0]);
	 	 dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+a[i]);
	 }
}
ans=max(dp[n][b][0],dp[n][b][1]);
memset(dp,-inf,sizeof(dp)),dp[1][1][1]=a[1],dp[1][0][0]=0;
for(int i=2;i<=n;i++)
{
 	 dp[i][0][0]=dp[i-1][0][0];
 	 for(int j=1;j<=b;j++)
 	 {
 	 	 dp[i][j][0]=max(dp[i-1][j][1],dp[i-1][j][0]);
 	 	 dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+a[i]);
	 }
}
ans=max(ans,dp[n][b][1]);
printf("%d\n",ans);
```

[$\leftarrow$ 我的 $\operatorname{DP}$ 杂题专题](https://www.luogu.com.cn/blog/EricQian/dp-za-ti)

---

## 作者：zythonc (赞：1)

## 【分析过程】

我们可以用一个三维数组 $f_{i,o,p}$ 来表示状态

其中 $i$ 表示经过了的时间段，$o$ 表示已经睡了 $o$ 个时间段，$p$ 表示这个时间段有没有在睡觉

**那么对于一个时间段有两种决策：睡觉或是不睡觉**

- 没有睡觉，从上个时间段取最大值

- 睡觉，上一段时间又有两种状况：在睡觉或是没有睡觉；在睡觉即可获得效益值 $v_i$

所以我们可以推出转移方程：

$f_{i,o,0}=\max(f_{i-1,o,0},f_{i-1,o,1})$

$f_{i,o,1}=\max(f_{i-1,o-1,0},f_{i-1,o-1,1}+v_i)$

因为此题是一个环形动态规划，所以我们选择**强制断环然后强制连环**进行两次动态规划来消除后效性

断环，意即在时间 $N$ 不睡觉，所以额外初始化为 $f_{1,1,1}=0$

连环，意即在时间 $N$ 和次日时间 $1$ 的时候强制睡觉，所以额外初始化为 $f_{1,1,1}=v_1$，统计答案的时候为 $ans=\max(ans,f_{n,m,1})$

## 【代码实现】

```
#include<iostream>
#include<cstring>
#define N 4000
#define set(f) memset(f,-0x3f,sizeof(f))
#define cl(a) for(int i=1;i<=n;i++) a[i][0][0]=0;
using namespace std;
int n,in[N],b,ans,f[N][N][2];
signed main(){
	cin>>n>>b;
	for(int i=1;i<=n;i++){
		cin>>in[i];
	}
	set(f);cl(f);
	f[1][1][1]=0;
	for(int i=2;i<=n;i++){
		for(int o=1;o<=i;o++){
			f[i][o][0]=max(f[i-1][o][0],f[i-1][o][1]);
			f[i][o][1]=max(f[i-1][o-1][1]+in[i],f[i-1][o-1][0]);
		}
	}
	ans=max(f[n][b][0],f[n][b][1]);
	set(f);cl(f);
	f[1][1][1]=in[1];
	for(int i=2;i<=n;i++){
		for(int o=1;o<=i;o++){
			f[i][o][0]=max(f[i-1][o][0],f[i-1][o][1]);
			f[i][o][1]=max(f[i-1][o-1][1]+in[i],f[i-1][o-1][0]);
		}
	}
	cout<<max(ans,f[n][b][1]);
}
```

---

