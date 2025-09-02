# Bicolorings

## 题目描述

**题目大意：**

给定一个$2\times n$的棋盘，可以对上面的格子黑白染色，求染色后棋盘上的联通块的个数正好为$k$的染色方案数

## 样例 #1

### 输入

```
3 4
```

### 输出

```
12
```

## 样例 #2

### 输入

```
4 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1 2
```

### 输出

```
2
```

# 题解

## 作者：ikunTLE (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/CF1051D)

### 思路

可以使用**动态规划**解决此题。

首先定义状态转移数组 $f$。首先定义 $z$ 为两排棋盘上的颜色在二进制下的结果。再定义 $f_{i,j,z}$ 的含义为：在第 $i$ 列，有着 $j$ 个连通块，状态为 $z$ 下的染色方案数。

可以将 $z$ 的 $4$ 种状态分别转移求数量和，初始化 $f_{1,1,1}$，$f_{1,1,2}$，$f_{1,2,0}$ 和 $f_{1,2,3}$ 为 $1$，表示起点有 $1$ 种方案。用 $i$ 作列数枚举从 $2$ 到 $n$，$j$ 枚举连通块从 $0$ 到 $k$。状态转移方程是它各个连通块染色方案数的总和，即为：

$$\begin{cases}
f_{i,j,0}=f_{i-1,j,0}+f_{i-1,j-1,1}+f_{i-1,j-1,2}+f_{i-1,j-2,3}\\
f_{i,j,1}=f_{i-1,j,0}+f_{i-1,j,1}+f_{i-1,j-1,2}+f_{i-1,j,3}\\
f_{i,j,2}=f_{i-1,j,0}+f_{i-1,j-1,1}+f_{i-1,j,2}+f_{i-1,j,3}\\
f_{i,j,3}=f_{i-1,j-2,0}+f_{i-1,j-1,1}+f_{i-1,j-1,2}+f_{i-1,j,3}  
\end{cases}$$

最后输出 $f_{n,k,0}+f_{n,k,1}+f_{n,k,2}+f_{n,k,3}$ 即为答案。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e3+10,MOD=998244353;
long long f[N][N*2][4];
int main(){
	int n=read(),k=read();
	f[1][1][1]=f[1][1][2]=f[1][2][0]=f[1][2][3]=1ll;
	for(int i=2;i<=n;++i)
		for(int j=0;j<=k;++j){
			f[i][j][0]=(f[i-1][j][0]+f[i-1][j-1][1]+f[i-1][j-1][2]+f[i-1][j-2][3])%MOD;
			f[i][j][1]=(f[i-1][j][0]+f[i-1][j][1]+f[i-1][j-1][2]+f[i-1][j][3])%MOD;
			f[i][j][2]=(f[i-1][j][0]+f[i-1][j-1][1]+f[i-1][j][2]+f[i-1][j][3])%MOD;
			f[i][j][3]=(f[i-1][j-2][0]+f[i-1][j-1][1]+f[i-1][j-1][2]+f[i-1][j][3])%MOD;
		}
	printf("%d\n",(f[n][k][0]+f[n][k][1]+f[n][k][2]+f[n][k][3])%MOD);
	return 0;
}
```

---

## 作者：ran_qwq (赞：6)

upd on 2024.5.2：修改了一处笔误，感谢@yonghu_3913 提出。

设 $dp_{i,j,k,l}$ 为前 $i$ 列，连通块数量为 $j$，第一个方块颜色为 $k$（$0$ 或 $1$，$0$ 为白色，$1$ 为黑色，下同），第二个方块颜色为 $l$ 的方案数。

随便推一下可得：

$$dp_{i,j,0,0}=dp_{i-1,j,0,0}+dp_{i-1,j,0,1}+dp_{i-1,j,1,0}+dp_{i-1,j-1,1,1}$$

$$dp_{i,j,0,1}=dp_{i-1,j-1,0,0}+dp_{i-1,j,0,1}+dp_{i-1,j-2,1,0}+dp_{i-1,j-1,1,1}$$

$$dp_{i,j,1,0}=dp_{i-1,j-1,0,0}+dp_{i-1,j-2,0,1}+dp_{i,1,j,1,0}+dp_{i-1,j-1,1,1}$$

$$dp_{i,j,1,1}=dp_{i-1,j-1,0,0}+dp_{i-1,j,0,1}+dp_{i-1,j,1,0}+dp_{i-1,j,1,1}$$

边界就是 $n=1$ 的情况。答案就是 $dp_{n,m,i,j}(i=0/1,j=0/1)$ 加起来。

---

## 作者：flora715 (赞：5)

### 【题意】

一个网格2行n列，此网格的每个单元格应为黑色或白色。


如果两个单元具有共同的边界并且共享相同的颜色，则它们被认为是邻居。
    
如果存在属于与B相同的组件的邻居A，则两个小区A和B属于一个联通。

如果网格具有正好的k个连通，那么我们称之为一个双色块。

计算构成k个双色块的方案数。答案模998244353。 

### 【分析】

**f[i][j][type]** 表示 第i列，已经有j个连通块，状态为上下行间差异。

状态 type：** BW,BB,WW,WB**（ 第i列的 上行~下行 ）

B：black； W：white。

**状态转移方程：**
```cpp
f[i][j][0]=f[i-1][j][0]+f[i-1][j-1][1]+f[i-1][j-1][2]+f[i-1][j-2][3];

f[i][j][1]=f[i-1][j][0]+f[i-1][j][1]+f[i-1][j-1][2]+f[i-1][j][3];

f[i][j][2]=f[i-1][j][0]+f[i-1][j-1][1]+f[i-1][j][2]+f[i-1][j][3];

f[i][j][3]=f[i-1][j-2][0]+f[i-1][j-1][1]+f[i-1][j-1][2]+f[i-1][j][3];
```

### 【代码】
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<deque>
#include<cmath>
#include<map>
using namespace std;
typedef unsigned long long ll;

/*【D】
一个网格2行和n列，此网格的每个单元格应为黑色或白色。
如果两个单元具有共同的边界并且共享相同的颜色，则它们被认为是邻居。 
如果存在属于与B相同的组件的邻居A，则两个小区A和B属于一个联通。
如果它具有正好的k个连通，那么我们称之为一个双色块。
计算构成k个双色块的方案数。答案模998244353。 */

//f[i][j][type] 第i列，已经有j个连通块，状态为上下行间差异
//type: BW,BB,WW,WB（ 第i列的 上行~下行 ）
//方程:f[i][j][0]=f[i-1][j][0]+f[i-1][j-1][1]+f[i-1][j-1][2]+f[i-1][j-2][3];
//f[i][j][1]=f[i-1][j][0]+f[i-1][j][1]+f[i-1][j-1][2]+f[i-1][j][3];
//f[i][j][2]=f[i-1][j][0]+f[i-1][j-1][1]+f[i-1][j][2]+f[i-1][j][3];
//f[i][j][3]=f[i-1][j-2][0]+f[i-1][j-1][1]+f[i-1][j-1][2]+f[i-1][j][3];

void reads(int &x){ //读入优化（正负整数）
  int fx=1;x=0;char s=getchar();
  while(s<'0'||s>'9'){if(s=='-')fx=-1;s=getchar();}
  while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
  x*=fx; //正负号
}

const int mod=998244353;
ll f[2001][2001][4];

int main(){
  int n,k; reads(n); reads(k);
  f[1][2][0]=1; f[1][1][1]=1; 
  f[1][1][2]=1; f[1][2][3]=1;
  for(int i=2;i<=n;i++) //注意：初始化第一列，从第二列开始循环
    for(int j=0;j<=k;j++){
      f[i][j][0]=(f[i-1][j][0]%mod+f[i-1][j-1][1]%mod+f[i-1][j-1][2]%mod+f[i-1][j-2][3]%mod)%mod;
      f[i][j][1]=(f[i-1][j][0]%mod+f[i-1][j][1]%mod+f[i-1][j-1][2]%mod+f[i-1][j][3]%mod)%mod;
      f[i][j][2]=(f[i-1][j][0]%mod+f[i-1][j-1][1]%mod+f[i-1][j][2]%mod+f[i-1][j][3]%mod)%mod;
      f[i][j][3]=(f[i-1][j-2][0]%mod+f[i-1][j-1][1]%mod+f[i-1][j-1][2]%mod+f[i-1][j][3]%mod)%mod;
    } 
  ll ans=(f[n][k][0]%mod+f[n][k][1]%mod+f[n][k][2]%mod+f[n][k][3]%mod)%mod;
  cout<<ans<<endl; return 0;
}
```

---

## 作者：Mistybranch (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1051D)

题目大概意思是：给出一个 $2 \times n$ 的矩形，每个格子可以填黑白两种颜色，会形成联通块（黑白都算）。问有多少种填色情况使得最后联通块个数为 $k$。答案对 $998244353$ 取模。

对这么大的数取模，说明暴力一定会爆时间，考虑用 DP 求解。

- 首先我们要知道，填色的每一列只会有四种填色情况，用二进制表示为：00，01，10，11。转化为十进制就是 0 ~ 3。

- 我们设 ```f[i][j][k]``` 为前 $i$ 列，联通块数量为 $j$，最后一列情况为 $k$ 的个数。

- 设定好状态，列状态转移方程，如下：

$$f[i + 1][j][k] += f[i][j][k] (0 \leq k \leq 3)$$
$$f[i + 1][j + 1][k] += f[i][j][0] (1 \leq k \leq 3)$$
$$f[i + 1][j + 1][k] += f[i][j][3] (1 \leq k \leq 2)$$
$$f[i + 1][j][3] += f[i][j][k] (1 \leq k \leq 2)$$
$$f[i + 1][j][0] += f[i][j][k] (1 \leq k \leq 2)$$
$$f[i + 1][j + 1][0] += f[i][j][3]$$
$$f[i + 1][j + 2][1] += f[i][j][2]$$
$$f[i + 1][j + 2][2] += f[i][j][1]$$

完整代码：

```cpp


#include <bits/stdc++.h>

using namespace std;

int n, k;
long long f[1009][2009][4];

int main () {
	scanf("%d%d", &n, &k);
	
	f[1][1][0] = 1;
	f[1][1][3] = 1;
	f[1][2][1] = 1;
	f[1][2][2] = 1;
	
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= (i << 1); j++) {
			for (int k = 0; k < 4; k++) {
				f[i + 1][j][k] = (f[i + 1][j][k] + f[i][j][k]) % 998244353;
			}
			
			for (int k = 1; k < 4; k++) {
				f[i + 1][j + 1][k] = (f[i + 1][j + 1][k] + f[i][j][0]) % 998244353;
			}
			
			for (int k = 1; k < 3; k++) {
				f[i + 1][j + 1][k] = (f[i + 1][j + 1][k] + f[i][j][3]) % 998244353;
				f[i + 1][j][3] = (f[i + 1][j][3] + f[i][j][k]) % 998244353;
				f[i + 1][j][0] = (f[i + 1][j][0] + f[i][j][k]) % 998244353;
			}
			
			f[i + 1][j + 1][0] = (f[i + 1][j + 1][0] + f[i][j][3]) % 998244353;
			f[i + 1][j + 2][1] = (f[i + 1][j + 2][1] + f[i][j][2]) % 998244353;
			f[i + 1][j + 2][2] = (f[i + 1][j + 2][2] + f[i][j][1]) % 998244353;
		}
	} 
	
	printf("%lld\n", (f[n][k][0] + f[n][k][1] + f[n][k][2] + f[n][k][3]) % 998244353);
	
	return 0;
}
```


---

## 作者：Shellchen (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1051D)  

# 正文开始
## 本题核心思路
看到这个题可以想到两种做法：搜索和 DP。对于搜索，有 $1 \le n \le 1000$，肯定会 TLE。于是考虑 DP。

我们用 $ f_{i,j,l} $ 表示考虑到第 $i$ 列，已经有了 $j$ 个连通块的染色方法数，其中 $k$ 表示本列状态：

$l=0$：上下都涂白色。  
$l=1$：上涂黑下涂白。  
$l=2$：上涂白下涂黑。  
$l=3$：上下都涂黑色。  

## 状态转移

我们枚举 $i$ 和 $j$ $(1 \le i \le n , 1 \le j \le k)$，对于每个 $l$ 分别写一个状态转移方程。

### $l=0$

我们只需要关心上一列（对于每个 $l$ 都是，下同）。

对于上一列 $l=0$：没有新的连通块。

```
WW
WW
```
（此处用 W 表示白色，B 表示黑色，下同。）

对于上一列 $l=1$：没有新的连通块。

```
BW
WW
```
对于上一列 $l=2$：没有新的连通块。

```
WW
BW
```
对于上一列 $l=3$：有 1 个新的连通块。

```
BW
BW
```
最终方程：$f_{i,j,0} = f_{i-1,j,0}+f_{i-1,j,1}+f_{i-1,j,2}+f_{i-1,j-1,3}$。

### $l=1$

对于上一列 $l=0$：有 1 个新的连通块。

```
WB
WW
```

对于上一列 $l=1$：没有新的连通块。

```
BB
WW
```
对于上一列 $l=2$：有 2 个新的连通块。

```
WB
BW
```
对于上一列 $l=3$：有 1 个新的连通块。

```
BB
BW
```
最终方程：$f_{i,j,1} = f_{i-1,j-1,0}+f_{i-1,j,1}+f_{i-1,j-2,2}+f_{i-1,j-1,3}$。

### $l=2$

对于上一列 $l=0$：有 1 个新的连通块。

```
WW
WB
```

对于上一列 $l=1$：有 2 个新的连通块。

```
BW
WB
```
对于上一列 $l=2$：没有新的连通块。

```
WW
BB
```
对于上一列 $l=3$：有 1 个新的连通块。

```
BW
BB
```
最终方程：$f_{i,j,2} = f_{i-1,j-1,0}+f_{i-1,j-2,1}+f_{i-1,j,2}+f_{i-1,j-1,3}$。

### $l=3$

对于上一列 $l=0$：有 1 个新的连通块。

```
WB
WB
```

对于上一列 $l=1$：没有新的连通块。

```
BB
WB
```
对于上一列 $l=2$：没有新的连通块。

```
WB
BB
```
对于上一列 $l=3$：没有新的连通块。

```
BB
BB
```
最终方程：$f_{i,j,1} = f_{i-1,j-1,0}+f_{i-1,j-2,1}+f_{i-1,j,2}+f_{i-1,j-1,3}$。

## 结论
把四个状态转移方程合到一起，就得到正解了。  
$f_{i,j,0} = f_{i-1,j,0}+f_{i-1,j,1}+f_{i-1,j,2}+f_{i-1,j-1,3}$  
$f_{i,j,1} = f_{i-1,j-1,0}+f_{i-1,j,1}+f_{i-1,j-2,2}+f_{i-1,j-1,3}$  
$f_{i,j,2} = f_{i-1,j-1,0}+f_{i-1,j-2,1}+f_{i-1,j,2}+f_{i-1,j-1,3}$  
$f_{i,j,3} = f_{i-1,j-1,0}+f_{i-1,j,1}+f_{i-1,j,2}+f_{i-1,j,3}$  
最终代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e3+10;
int f[N][N*2][4];
signed main()
{
	int n,k;
	cin>>n>>k;
	f[1][1][0]=f[1][2][1]=f[1][2][2]=f[1][1][3]=1;
	for(int i=2;i<=n;i++) for(int j=1;j<=k;j++)
	{
		f[i][j][0]=(f[i-1][j][0]+f[i-1][j][1]+f[i-1][j][2]+f[i-1][j-1][3])%998244353;
		f[i][j][1]=(f[i-1][j-1][0]+f[i-1][j][1]+f[i-1][j-2][2]+f[i-1][j-1][3])%998244353;
		f[i][j][2]=(f[i-1][j-1][0]+f[i-1][j-2][1]+f[i-1][j][2]+f[i-1][j-1][3])%998244353;
		f[i][j][3]=(f[i-1][j-1][0]+f[i-1][j][1]+f[i-1][j][2]+f[i-1][j][3])%998244353;
	}
	cout<<(f[n][k][0]+f[n][k][1]+f[n][k][2]+f[n][k][3])%998244353;
	return 0;
}
```

---

## 作者：issue_is_fw (赞：2)

其实还是比较经典的格子dp

这里虽然不是新思路,但是提供一份较为简洁的滚动数组版本

设$dp[i][j][q]$为放完第i列有j个连通块,第i列状态是q的答案数

q取$[0,1,2,3]$,分别表示第i列放黑白，白黑，黑黑，白白

$因为转移比较简单,直接看代码也能看懂,这里不写$

$代码中用了滚动数组,因为当前列只和上一列有关$

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int n,k,ans;
int dp[2][2001][4];//分别表示第几列,几个连通块,哪种状态
//0,1,2,3表示黑白，白黑，黑黑，白白 
signed main()
{
	cin >> n >> k;
	dp[1][2][0]=dp[1][2][1]=1;
	dp[1][1][2]=dp[1][1][3]=1;
	
	for(int i=2;i<=n;i++)
	{
		int u=i%2,v=(i%2)^1;
		for(int j=1;j<=k;j++)
		{
			int s=max(j-2,(int)0);
			dp[u][j][0]=dp[v][j][0]+dp[v][s][1]+dp[v][j-1][2]+dp[v][j-1][3];
			dp[u][j][1]=dp[v][j][1]+dp[v][s][0]+dp[v][j-1][2]+dp[v][j-1][3];
			dp[u][j][2]=dp[v][j][2]+dp[v][j-1][3]+dp[v][j][0]+dp[v][j][1];
			dp[u][j][3]=dp[v][j][3]+dp[v][j-1][2]+dp[v][j][0]+dp[v][j][1];
			for(int q=0;q<=3;q++)
				dp[u][j][q]%=mod;
		}
	}
	for(int i=0;i<=3;i++)
		ans = (ans + dp[n%2][k][i] )%mod;
	cout << ans;
}
```

---

## 作者：Pyrf_uqcat (赞：1)

动态规划，很有思维含量。

首先看到题还以为打表找规律，但是规律好像是没有的。

注意到棋盘宽为二，那每次往右边摆两个就有四种方式：黑黑，黑白，白黑，白白。那就可以将 $dp_{i,j,k}$ 表示为前 $i$ 列有 $j$ 个连通块时当前为第 $k$ 种摆法的方案数。

初始化：

```cpp
dp[1][1][1]=1;
dp[1][2][2]=1;
dp[1][2][3]=1;
dp[1][1][4]=1;
```
转移方式推的时候可以画图便于推式：


```cpp
//1:X 2:X 3:. 4:.
//X   .   X   .
dp[i][j][1]+=dp[i-1][j][1]+dp[i-1][j][2]+dp[i-1][j][3]+dp[i-1][j-1][4];
dp[i][j][2]+=dp[i-1][j-1][1]+dp[i-1][j][2]+dp[i-1][j-2][3]+dp[i-1][j-1][4];
dp[i][j][3]+=dp[i-1][j-1][1]+dp[i-1][j-2][2]+dp[i-1][j][3]+dp[i-1][j-1][4];
dp[i][j][4]+=dp[i-1][j-1][1]+dp[i-1][j][2]+dp[i-1][j][3]+dp[i-1][j][4];
```
答案就是将所有最后列都加起来。

### 代码


```cpp
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N=1e3+5;
const int mod=998244353;

int n,k;

int dp[N][2*N][5];

inline void init()
{
	dp[1][1][1]=1;
	dp[1][2][2]=1;
	dp[1][2][3]=1;
	dp[1][1][4]=1;
}

signed main()
{
	cin>>n>>k;
	init();
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=k;j++)
		{
//			1:X 2:X 3:. 4:.
//  		  X   .   X   .
			dp[i][j][1]+=dp[i-1][j][1]+dp[i-1][j][2]+dp[i-1][j][3]+dp[i-1][j-1][4];
			dp[i][j][2]+=dp[i-1][j-1][1]+dp[i-1][j][2]+dp[i-1][j-2][3]+dp[i-1][j-1][4];
			dp[i][j][3]+=dp[i-1][j-1][1]+dp[i-1][j-2][2]+dp[i-1][j][3]+dp[i-1][j-1][4];
			dp[i][j][4]+=dp[i-1][j-1][1]+dp[i-1][j][2]+dp[i-1][j][3]+dp[i-1][j][4];
			dp[i][j][1]%=mod,dp[i][j][2]%=mod,dp[i][j][3]%=mod,dp[i][j][4]%=mod;
//			cout<<i<<' '<<j<<' '<<dp[i][j][1]<<' '<<dp[i][j][2]<<' '<<dp[i][j][3]<<' '<<dp[i][j][4]<<endl;
		}
	}
	int ans=0;
	for(int i=1;i<=4;i++)
	{
		ans+=dp[n][k][i];
		ans%=mod;
	}
	cout<<ans<<endl;
    return 0;
}

```

---

## 作者：_Deer_Peach_ (赞：1)

作为模拟赛的第四题，感觉有点水了。

题意：

在一个 $2 \times n$ 的棋盘上染色，可以画成黑色或白色，求画成正好 $k$ 个连通块的方案数。

思路：

一眼动态规划题，分类讨论。

状态定义；$dp_{i,j,k}$ 表示前 $i$ 列画成 $j$ 个连通块第 $k$ 种染色方法时的方案数量。其中，四种染色方法为：
1. 两格白色；
2. 上格白色下格黑色；
3. 上格黑色下格白色；
4. 两格黑色。

初始化：

第 $1$ 列画成 $1$ 个连通块用第 $1$ 种和第 $4$ 种染色方法方案数为 $1$，第 $1$ 列画成 $2$ 个连通块用第 $2$ 种和第 $3$ 种染色方法方案数为 $1$。所以初始化为：
```
dp[1][1][1]=dp[1][2][2]=dp[1][2][3]=dp[1][1][4]=1;
```

状态转移：

每一列都分以下四类讨论：
1. 这一列用第一种画法；
2. 这一列用第二种画法；
3. 这一列用第三种画法；
4. 这一列用第四种画法。

每一类都从上一列的染色方法中转移过来，根据当前这一列的画法与上一列的画法，判断出连通块的数量是否改变，再转移。

当前这一列为第一种画法时：
1. 上一列是第一种画法，连通块数量不变；
2. 上一列是第二种画法，连通块数量不变；
3. 上一列是第三种画法，连通块数量不变；
4. 上一列是第四种画法，连通块数量加一。

当前这一列为第二种画法：
1. 上一列是第一种画法，连通块数量加一；
2. 上一列是第二种画法，连通块数量不变；
3. 上一列是第三种画法，连通块数量加二；
4. 上一列是第四种画法，连通块数量加一。

当前这一列为第三种画法：
1. 上一列是第一种画法，连通块数量加一；
2. 上一列是第二种画法，连通块数量加二；
3. 上一列是第三种画法，连通块数量不变；
4. 上一列是第四种画法，连通块数量加一。

当前这一列为第四种画法时：
1. 上一列是第一种画法，连通块数量加一；
2. 上一列是第二种画法，连通块数量不变；
3. 上一列是第三种画法，连通块数量不变；
4. 上一列是第四种画法，连通块数量不变。

如果不明白为什么这样，可以自行画图理解。

具体实现：
```
(dp[i][j][1]=dp[i-1][j][1]+dp[i-1][j][2]+dp[i-1][j][3]+dp[i-1][j-1][4])%=Mod;
(dp[i][j][2]=dp[i-1][j-1][1]+dp[i-1][j][2]+dp[i-1][(j-2>=0?j-2:0)][3]+dp[i-1][j-1][4])%=Mod;
(dp[i][j][3]=dp[i-1][j-1][1]+dp[i-1][(j-2>=0?j-2:0)][2]+dp[i-1][j][3]+dp[i-1][j-1][4])%=Mod;
(dp[i][j][4]=dp[i-1][j-1][1]+dp[i-1][j][2]+dp[i-1][j][3]+dp[i-1][j][4])%=Mod;
```

答案：

把最后一列画成 $k$ 个连通块的四种画法相加即可。

完整代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int N=1005,K=2005,Mod=998244353;
int n,k;
int dp[N][K][5];//画前i列有j个连通块，第i列用第k种画法的方案数 
/*
0:WW
1:WB
2:BW
3:BB
*/
signed main(){
    IOS;cin>>n>>k;
	dp[1][1][1]=dp[1][2][2]=dp[1][2][3]=dp[1][1][4]=1;
    for(int i=2;i<=n;i++){
    	for(int j=k;j>=1;j--){
    		(dp[i][j][1]=dp[i-1][j][1]+dp[i-1][j][2]+dp[i-1][j][3]+dp[i-1][j-1][4])%=Mod;
    		(dp[i][j][2]=dp[i-1][j-1][1]+dp[i-1][j][2]+dp[i-1][(j-2>=0?j-2:0)][3]+dp[i-1][j-1][4])%=Mod;
    		(dp[i][j][3]=dp[i-1][j-1][1]+dp[i-1][(j-2>=0?j-2:0)][2]+dp[i-1][j][3]+dp[i-1][j-1][4])%=Mod;
    		(dp[i][j][4]=dp[i-1][j-1][1]+dp[i-1][j][2]+dp[i-1][j][3]+dp[i-1][j][4])%=Mod;
		}
	}
	/*
	for(int i=1;i<=4;i++){
		for(int j=1;j<=k;j++){
			for(int l=1;l<=n;l++){
				cout<<"dp["<<l<<"]["<<j<<"]["<<i<<"]="<<dp[l][j][i]<<" ";
			}cout<<endl;
		}cout<<endl;
	}
	*/
	cout<<(dp[n][k][1]+dp[n][k][2]+dp[n][k][3]+dp[n][k][4])%Mod;
	return 0;
}
```

---

## 作者：SunnyYuan (赞：1)

## 思路

这里给出一种简单的实现方式，首先说一下基本思路：

设 $f_{i, j, k}$ 表示染到了 $i$ 列，共 $j$ 个连通块，第 $i$ 列的状态为 $k$ 的方案数，下图是状态 $k$ 对应的染法：

![](https://cdn.luogu.com.cn/upload/image_hosting/7rrg8mup.png)

然后我们可以记一个 $add$ 数组，$add_{i, j}$ 表示上一列是状态 $i$，这一列状态是 $j$ 对连通块数量的变化。

```cpp
int add[4][4] = {
    0, 1, 1, 1,
    0, 0, 2, 0,
    0, 2, 0, 0,
    1, 1, 1, 0    
};
```

然后，我们枚举列数 $i$，连通块数量为 $cur$，以及上一列的状态为 $k$ 及这一列的状态为 $j$ 然后进行转移即可：

$f_{i, cur, j} = \sum f_{i - 1, cur - add_{k, j}, k}$

初始化：$f_{1, 1, 0} = f_{1, 2, 1} = f_{1, 2, 2} = f_{1, 1, 3} = 1$

结果：$f_{n, k, 0} + f_{n, k, 1} + f_{n, k, 2} + f_{n, k, 3}$。


## 代码

代码非常简单，不知道为什么大佬的代码都很长。

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: Bicolorings
| Contest: Luogu
| URL:     https://www.luogu.com.cn/problem/CF1051D
| When:    2023-10-04 19:36:00
| 
| Memory:  250 MB
| Time:    2000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;

const int N = 1010, M = 2010, mod = 998244353;

int n, k;
int f[N][M][4];
int add[4][4] = {
    0, 1, 1, 1,
    0, 0, 2, 0,
    0, 2, 0, 0,
    1, 1, 1, 0    
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    f[1][1][0] = f[1][2][1] = f[1][2][2] = f[1][1][3] = 1;
    for (int i = 2; i <= n; i++) {
        for (int cur = 1; cur <= k; cur++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    if (cur > add[k][j]) (f[i][cur][j] += f[i - 1][cur - add[k][j]][k]) %= mod;
                }
            }
        }
    }
    cout << ((f[n][k][0] + f[n][k][1]) % mod + (f[n][k][2] + f[n][k][3]) % mod) % mod << '\n';
    return 0;
}
```

---

## 作者：KEBrantily (赞：1)

设 $f_{i,j,c,d}$ 表示到第 $i$ 列有 $j$ 个联通块，且这一列上面颜色为 $c$，下面颜色为 $d$ 的方案数 $(c,d\in\{0,1\},j\le i\times 2)$。

然后考虑这个状态可以从什么转移而来。

显然有：

$$f_{i,j,1,1}=f_{i-1,j,1,0}+f_{i-1,j,0,1}+f_{i-1,j,1,1}+f_{i-1,j-1,0,0}$$

$$f_{i,j,0,0}=f_{i-1,j,0,1}+f_{i-1,j,1,0}+f_{i-1,j,0,0}+f_{i-1,j-1,1,1}$$

$$f_{i,j,1,0}=f_{i-1,j,1,0}+f_{i-1,j-1,1,1}+f_{i-1,j-1,0,0}+f_{i-1,j-2,0,1}$$

$$f_{i,j,0,1}=f_{i-1,j,0,1}+f_{i-1,j-1,0,0}+f_{i-1,j-1,1,1}+f_{i-1,j-2,1,0}$$

这些转移状态。

处理出 $f_{1,1,0,0}=f_{1,1,1,1}=f_{1,2,0,1}=f_{1,2,1,0}=1$ 然后转移即可。

转移时注意边界。

---

## 作者：呼吸之野 (赞：0)

### Solution

每一位的状态只有黑白两种，考虑状态压缩 dp。

$f_{i,j,k}$ 表示第 $i$ 列、第 $j$ 个状态、连通块数目为 $k$ 的方案数。

状态表示：$0$ 表示白色，$1$ 表示黑色，每列有 $2$ 个格子，共 $00,01,10,11$ 四种状态，可用 $[0,3]$ 中的整数来表示。

推导可得：

$f_{i,0,j} = f_{i-1,0,j} + f_{i-1,1,j} + f_{i-1,2,j} + f_{i-1,3,j-1}$

$f_{i,1,j} = f_{i-1,0,j-1} + f_{i-1,1,j} + f_{i-1,2,j-2} + f_{i-1,3,j-1}$

$f_{i,2,j} = f_{i-1,0,j-1} + f_{i-1,1,j-2} + f_{i-1,2,j} + f_{i-1,3,j-1}$

$f_{i,3,j} = f_{i-1,0,j-1} + f_{i-1,1,j} + f_{i-1,2,j} + f_{i-1,3,j}$

最后答案就是第 $n$ 列、连通块数目为 $k$ 的 $4$ 个状态的方案数加起来。

别忘记取模。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005; 
const int mod = 998244353;
int n,k;
long long f[maxn][5][maxn<<1];
int main(){
	cin>>n>>k;
	f[1][0][1] = f[1][3][1] = f[1][1][2] = f[1][2][2] = 1;
	for(int i=2;i<=n;i++){
		for(int j=0;j<=k;j++){
			f[i][0][j] = (f[i-1][0][j]%mod+f[i-1][1][j]%mod+f[i-1][2][j]%mod+f[i-1][3][j-1])%mod; 
			f[i][1][j] = (f[i-1][0][j-1]%mod+f[i-1][1][j]%mod+f[i-1][2][j-2]%mod+f[i-1][3][j-1])%mod;
			f[i][2][j] = (f[i-1][0][j-1]%mod+f[i-1][1][j-2]%mod+f[i-1][2][j]%mod+f[i-1][3][j-1])%mod;
			f[i][3][j] = (f[i-1][0][j-1]%mod+f[i-1][1][j]%mod+f[i-1][2][j]%mod+f[i-1][3][j])%mod;
		}
	}
	long long ans = 0;
	for(int i=0;i<=3;i++){
		ans = (ans+f[n][i][k]%mod)%mod;
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：L_S_ (赞：0)

**题目大意：** 给定一个 $ 2\times n $ 的棋盘，可以对上面的格子黑白染色，求染色后棋盘上的联通块的个数正好为 $ k $ 的染色方案数。

一道状压动规。

由于他只有两行，所以可以枚举状态:
|状态编号| $0$ | $1$ | $2$ | $3$ |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| $i$ | $0$ | $1$ | $0$  | $1$ |
| $j$ | $0$ | $0$ | $1$ | $1$ |

以上 $i$ 为第一行， $j$ 为第二行。

所以我们遍历第 $i$ 和第 $i-1$ 列的状态。 

我们可以提前先预处理好 $z[i][j]$ ，然后遍历这两列状态的时候可以直接用。

期间要枚举连通块的数量，然后转移。

我们可以推理每种状态所对应的连通块**增加**数量，举个例子:

|状态类型 | $1$ | $2$ |
| -----------: | -----------: | -----------: |
| 第一行 | $1$ | $0$ |
| 第二行 | $0$ | $1$ |

我们可以看出，连通块右边比左面增加了 $2$ 个连通块。

**注意**：不仅 $1$ 要算入连通块， $0$ 也要算入。



```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
long long f[1005][4][2005];//列  状态  连通块数  里面存答案
int z[4][4];
int main()
{
	z[0][0]=0,z[0][1]=1,z[0][2]=1,z[0][3]=1;
	z[1][0]=0,z[1][1]=0,z[1][2]=2,z[1][3]=0;
	z[2][0]=0,z[2][1]=2,z[2][2]=0,z[2][3]=0;
	z[3][0]=1,z[3][1]=1,z[3][2]=1,z[3][3]=0;
	int n,kk;
	cin>>n>>kk;
	f[1][0][1]=1;
	f[1][1][2]=1;
	f[1][2][2]=1;
	f[1][3][1]=1;
	for(int i=2;i<=n;i++))//遍历列
	{
		for(int j=0;j<4;j++))//遍历第i列状态
		{
			for(int k=0;k<4;k++)//遍历第i-1列状态
			{
				for(int l=1;l<=kk;l++)//遍历连通块数量
				{
					f[i][j][l]=(f[i][j][l]+f[i-1][k][l-z[k][j]])%mod;//第i行每种状态由第i-1行四种状态转移而来
				}
			} 
		}
	}
	cout<<(f[n][0][kk]+f[n][1][kk]+f[n][2][kk]+f[n][3][kk])%mod;//四种状态加起来
	return 0;
}

```

---

## 作者：mouseboy (赞：0)

觉得巨佬们考虑的太复杂了，其实可以用三维递归 （一维表示第几列，二维记录有多少个连通块，三维两个格子同色或异色），对于第 $i$ 格，连通块的数量取决于第 $i-1$ 个格子，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/f4nehhe3.png)

然后可得递归式:
$$f[i][j][0] = (f[i - 1][j][1] \times 2 + f[i - 1][j][0] + f[i - 1][j - 1][0]);$$

$$f[i][j][1] = (f[i - 1][j - 1][0] \times 2 + f[i - 1][j][1] + f[i - 1][j - 2][1]);$$


最后附上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Maxn = 1005, mod = 998244353;
int f[Maxn][Maxn * 2][2], n, k;//注意二维开两倍
int main() {
  cin >> n >> k;
  f[1][2][0] = f[1][3][1] = 2;//初始化
  for (int i = 2; i <= n; i++) {
    for (int j = 2; j <= k + 1; j++) {//注意这里要加1
      f[i][j][0] = (f[i - 1][j][1] * 2LL + f[i - 1][j][0] + f[i - 1][j - 1][0]) % mod;
      f[i][j][1] = (f[i - 1][j - 1][0] * 2LL + f[i - 1][j][1] + f[i - 1][j - 2][1]) % mod;
    }
  }
  cout << (f[n][k + 1][0] + f[n][k + 1][1]) % mod;
  return 0;//华丽的结束
}
```

---

## 作者：diqiuyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1051D)

**思路**

根据题目标签，不难发现这题是个 dp。题目问什么，就设什么。所以，设 $f_{i,j}$ 表示前 $i$ 列，共有 $j$ 个联通快的方案数。但是转移方程不太好想。

所以我们还要再加上最后一列的状态，一共有 $4$ 种情况。用 $1$ 表示黑色，$0$ 表示白色，就可以分别用 $00,01,10,11$ 表示最后一列的状态了。可以用二进制表示成 $0$ 到 $3$。

**转移方程**

易得：

$f_{i,j,0}=f_{i-1,j,0}+f_{i-1,j,1}+f_{i-1,j,2}+f_{i-1,j-1,3}$

$f_{i,j,1}=f_{i-1,j-1,0}+f_{i-1,j,1}+f_{i-1,j-2,2}+f_{i-1,j-1,3}$

$f_{i,j,2}=f_{i-1,j-1,0}+f_{i-1,j-2,1}+f_{i-1,j,2}+f_{i-1,j-1,3}$

$f_{i,j,3}=f_{i-1,j-1,0}+f_{i-1,j,1}+f_{i-1,j,2}+f_{i-1,j,3}$

**CODE**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define mod 998244353
#define int long long//不开 long long 见祖宗
inline int read(){
	int x=0;bool f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?x:-x;
}
int n,m,f[1005][2005][4];//注意第二维要开 2000
int main(){
	n=read(),m=read();
	f[1][1][0]=f[1][2][1]=f[1][1][3]=f[1][2][2]=1;//初始化第 1 列
	for(int i=2;i<=n;i++)
		for(int j=1;j<=m;j++){
			f[i][j][0]=(f[i-1][j][0]+f[i-1][j][1]+f[i-1][j][2]+f[i-1][j-1][3])%mod,
			f[i][j][3]=(f[i-1][j-1][0]+f[i-1][j][1]+f[i-1][j][2]+f[i-1][j][3])%mod;
			if(j^1)//防越界
				f[i][j][1]=(f[i-1][j-1][0]+f[i-1][j][1]+f[i-1][j-2][2]+f[i-1][j-1][3])%mod,
				f[i][j][2]=(f[i-1][j-1][0]+f[i-1][j-2][1]+f[i-1][j][2]+f[i-1][j-1][3])%mod;
		}
	printf("%lld\n",(f[n][m][0]+f[n][m][1]+f[n][m][2]+f[n][m][3])%mod);
	return 0;
}
```
还可以用滚动数组优化，但是在本题没有必要。

---

## 作者：傅思维666 (赞：0)


## 题解：

思路：计数——思考计数类DP。

既然已经是DP了，考虑设置状态。

直觉设置：$dp[i][j]$表示前i列共有j个连通块的方案数。但是这样没办法转移。

思考转移：如何能够转移呢？显然，当前面的状态已经算出来的时候，当前状态统计答案肯定要和当前这一列的黑白染色情况有关的。

也就是说，和当前状态有关。思考状压。

可以用两位二进制表示当前列的黑白染色情况，分别转移。

两位？......大可不必状压吧。我们发现，这个状态一共只有4种情况，上黑下白，上白下黑，全黑，全白。

那直接多开一维存1~4就行，没必要状压。

转移方程见代码。非常好想。

初值、答案也见代码：

```cpp
#include<cstdio>
#define int long long
using namespace std;
const int mod=998244353;
int n,k;
int dp[1010][2010][5];
//dp[i][j][opt]表示前i列，j个连通块，第i列型号为opt的方案数。
signed main()
{
	scanf("%lld%lld",&n,&k);
	dp[1][1][3]=dp[1][1][4]=dp[1][2][2]=dp[1][2][1]=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=k;j++)
		{
			dp[i][j][3]=(dp[i-1][j][1]+dp[i-1][j][2]+dp[i-1][j][3]+dp[i-1][j-1][4])%mod;
			dp[i][j][4]=(dp[i-1][j][1]+dp[i-1][j][2]+dp[i-1][j-1][3]+dp[i-1][j][4])%mod;
			if(j>1)
			{
				dp[i][j][1]=(dp[i-1][j-1][4]+dp[i-1][j][1]+dp[i-1][j-2][2]+dp[i-1][j-1][3])%mod;
				dp[i][j][2]=(dp[i-1][j-2][1]+dp[i-1][j][2]+dp[i-1][j-1][3]+dp[i-1][j-1][4])%mod;
			}
		}
	int ans=(dp[n][k][1]+dp[n][k][2]+dp[n][k][3]+dp[n][k][4])%mod;
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：localhost (赞：0)

我们设$f[i][k][j]$表示第$i$列状态为$j$,联通块个数为$k$的方案数

我们可以列出个种状态的转移

```plain
00 | 00 | 10 | 10 
00 | 10 | 00 | 10 

00 | 00 | 10 | 10 
01 | 11 | 01 | 11 

01 | 01 | 11 | 11 
00 | 10 | 00 | 10 

01 | 01 | 11 | 11
01 | 11 | 01 | 11
```
增加的联通块数(设这个矩阵为$g$):

| 0     |  01    |  10    |  11    |
| ---- | ---- | ---- | ---- |
| 0    | 0    | 0    | 1    |
| 1    | 0    | 2    | 1    |
| 1    | 2    | 0    | 1    |
| 1    | 0    | 0    | 0    |

那么$f[i][k][j] = \sum f[i-1][k-g[j][t]][t]$

记得取模!

上代码:
```cpp
#include<bits/stdc++.h>
namespace ZDY{
    #pragma GCC optimize(3)
    #define il __inline__ __attribute__ ((always_inline))
    #define rg register
    #define ll long long
    #define ull unsigned long long
    #define db double
    #define sht short
    #define MB template <class T>il
    #define Fur(i,x,y) for(int i(x);i<=y;++i)
    #define Fdr(i,x,y) for(int i(x);i>=y;--i)
    #define fl(i,x) for(int i(head[x]),to;to=e[i].to,i;i=e[i].nxt)
    #define clr(x,y) memset(x,y,sizeof(x))
    #define cpy(x,y) memcpy(x,y,sizeof(x))
    #define fin(s) freopen(s".in","r",stdin)
    #define fout(s) freopen(s".out","w",stdout)
    #define fcin ios::sync_with_stdio(false)
    #define l2(n) ((int)(log2(n)))
    #define inf 2122219134
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;rg char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
#define N 1011
#define int ll
const int mod=998244353;
int n,m,f[N][N*2][4],g[4][4]={
    0,0,0,1,
    1,0,2,1,
    1,2,0,1,
    1,0,0,0
};
signed main(){
    in(n,m);
    f[1][1][0]=f[1][1][3]=f[1][2][1]=f[1][2][2]=1;
    Fur(i,2,n)
        Fur(k,1,2*i)
            Fur(j,0,3)
                Fur(t,0,3)
                if(k-g[j][t]>0)
                    (f[i][k][j]+=f[i-1][k-g[j][t]][t])%=mod;

    int ans=0;
    Fur(t,0,3)(ans+=f[n][m][t])%=mod;
    cout<<ans<<endl;
}
```

---

## 作者：aRenBigFather (赞：0)

考虑到行数只有两行,而且每一列的情况数与前一列密切相关

所以考虑用dp,且将一列的情况压缩成4种(00,01,10,11),然后进行dp

用 $$dp[i][j][sta]$$ 表示 第i列 在列状态为sta的状态下 已有j个联通块的方案数


当然此处实际上是将 $$dp[i][j][upsta][downsta]$$ 后两维给他缩成了一维,实际上也可以不缩

dp转移如下,可以自己在记事本上用00,01,10,11试一下

```cpp
dp[i][j][0] = dp[i-1][j][1]+dp[i-1][j][2]+dp[i-1][j-1][3]+dp[i-1][j][0];
dp[i][j][0] %= mod;
dp[i][j][1] = dp[i-1][j][1] + dp[i-1][j-1][0] + dp[i-1][j-1][3];
dp[i][j][1] %= mod;
if(j >= 2) dp[i][j][1] += dp[i-1][j-2][2];
dp[i][j][1] %= mod;
dp[i][j][2] = dp[i-1][j][2] + dp[i-1][j-1][0] + dp[i-1][j-1][3];
dp[i][j][2] %= mod;
if(j >= 2) dp[i][j][2] += dp[i-1][j-2][1];
dp[i][j][2] %= mod;
dp[i][j][3] = dp[i-1][j-1][0] + dp[i-1][j][1] + dp[i-1][j][2] + dp[i-1][j][3];
dp[i][j][3] %= mod;
```

完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k;
const int mod = 998244353;
const int maxn = 2010;
ll dp[2010][maxn*2][4];//00,01,10,11
int main(){
    cin >> n >> k;
    memset(dp,0,sizeof dp);
    dp[1][1][0] = dp[1][1][3] = 1;
    dp[1][2][1] = dp[1][2][2] = 1;
    for(int i=2;i<=n;i++){
        for(int j=1;j<=i*2;j++){
            dp[i][j][0] = dp[i-1][j][1]+dp[i-1][j][2]+dp[i-1][j-1][3]+dp[i-1][j][0];
            dp[i][j][0] %= mod;
            dp[i][j][1] = dp[i-1][j][1] + dp[i-1][j-1][0] + dp[i-1][j-1][3];
            dp[i][j][1] %= mod;
            if(j >= 2) dp[i][j][1] += dp[i-1][j-2][2];
            dp[i][j][1] %= mod;
            dp[i][j][2] = dp[i-1][j][2] + dp[i-1][j-1][0] + dp[i-1][j-1][3];
            dp[i][j][2] %= mod;
            if(j >= 2) dp[i][j][2] += dp[i-1][j-2][1];
            dp[i][j][2] %= mod;
            dp[i][j][3] = dp[i-1][j-1][0] + dp[i-1][j][1] + dp[i-1][j][2] + dp[i-1][j][3];
            dp[i][j][3] %= mod;
        }
    }
    ll ans = 0;
    for(int i=0;i<4;i++) {
        ans += dp[n][k][i];
        ans %= mod;
    }
    cout << ans;
    return 0;
}
```

---

