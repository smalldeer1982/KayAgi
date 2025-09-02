# [USACO11NOV] Tile Exchanging S

## 题目描述

Farmer John wants to remodel the floor of his barn using a collection of square tiles he recently purchased from the local square mart store (which of course, only sells square objects).  Unfortunately, he didn't measure the size of the barn properly before making his purchase, so now he needs to exchange some of his tiles for new square tiles of different sizes.

The N square tiles previously purchased by FJ have side lengths A\_1...A\_N. He would like to exchange some of these with new square tiles so that the total sum of the areas of the his tiles is exactly M.  Square mart is currently offering a special deal: a tile of side length A\_i can be exchanged for a new tile of side length B\_i for a cost of

|A\_i-B\_i|\*|A\_i-B\_i| units. However, this deal only applies to 
previously-purchased tiles -- FJ is not allowed to exchange a tile that he has already obtained via exchanging some other tile (i.e., a size-3 tile cannot be exchanged for a size-2 tile, which is then exchanged for a size-1 tile).

Please determine the minimum amount of money required to exchange tiles so that the sum of the areas of the tiles becomes M.  Output -1 if it is impossible to obtain an area of M.



## 说明/提示

There are 3 tiles.  Two are squares of side length 3, and one is a square with side length 1.  We would like to exchange these to make a total area of 6.


Exchange one of the side-3 squares for a side-2 square, and another side-3 square for a side-1 square.  This gives the desired area of 4+1+1=6 and costs 4+1=5 units.

感谢 wjcwinmt 提供翻译


## 样例 #1

### 输入

```
3 6 
3 
3 
1 
```

### 输出

```
5 
```

# 题解

## 作者：winmt (赞：9)

我又来发本题第一个题解～～～～～**算法：DP!**

dp[i][j]代表前i个正方形，面积为j时的最小花费，易得：**dp[i][j]=min(dp[i][j],dp[i-1][j-k\*k]+abs(a[i]-k)\*abs(a[i]-k))**『k为循环的需要换成的正方形』

边界条件要注意！首先dp[0][1-m]=inf，然后每次循环中dp[i][j]=inf。最后若dp[n][m]==inf则输出-1，否则就打dp[n][m]！搞定！！！^\_^

**重要代码【CPP CODE】：**

    
    
```cpp
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)dp[0][i]=inf;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=inf;
            for(int k=1;k*k<=j;k++)
            {
                if(dp[i-1][j-k*k]!=inf)dp[i][j]=min(dp[i][j],dp[i-1][j-k*k]+abs(a[i]-k)*abs(a[i]-k));
            }
        }
    }
    if(dp[n][m]==inf)printf("-1\n"); else printf("%d\n",dp[n][m]);
    return 0;
}

```

---

## 作者：_cmh (赞：6)

没错，这题就是 $DP$ ！

这题只需要依次枚举第 $1\sim n$ 个正方形，$0\sim m$ 的面积和 $0\sim \sqrt j$ 的边长即可。（$j$ 表示 $0\sim m$ 的面积）

我们设计 $dp_{\ i,j}$ 表示在第 $i$ 个正方形，面积为 $j$ 的代价，则 $dp_{\ 0,0}$ 应初始值为 $0$ ，所有的量初始值为一个极大值，则题目让我们求的是 $dp_{\ n,m}$ 的值。状态转移方程：

$$dp_{\ i,j}=\min\{dp_{\ i,j},dp_{\ i-1,j-k\times k}+\mid a_j -k \mid^2 \}$$

代码奉上：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
int n,m,a[11],dp[11][10001];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	memset(dp,54088988,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=m;j++)
			for(int k=0;k<=sqrt(j);k++)
				dp[i][j]=min(dp[i][j],dp[i-1][j-k*k]+abs(a[i]-k)*abs(a[i]-k));
	if(dp[n][m]>=54088988) cout<<-1;
	else cout<<dp[n][m];
    return 0;
}
```

求赞！

---

## 作者：Meowco (赞：4)

### 做法

对于给一堆物品的质量 $a[i]$，问能不能凑出总质量恰好为 $M$，这种类型很显然是一个背包。

只不过这题对于每个物品，可以通过产生开销用于改变物品质量。

因此我们还需要枚举每个物品的所有合法质量以及对应需要的开销。

定义 $dp[i][j]$ 表示前 $i$ 件物品凑出质量 $j$ 的最小开销，则可以写出转移方程：

假设当前枚举到物品 $i$，前 $i-1$ 个物品可以凑出质量 $j$，尝试将物品 $i$ 变成质量 $k^2$，此时开销 $cost$ 为 $(a[i] - k)^2$，此状态的转移为 $dp[i][j + k ^ 2] = \min(dp[i][j + k ^ 2], dp[i - 1][j] + cost)$，

我们用下面这种方式进行转移：

```cpp
    for (int i = 1; i <= n; i++) // 枚举物品
        for (int j = 0; j <= m; j++) // 枚举总质量
            if (dp[i - 1][j] != inf) // 如果前 i-1 个物品能凑出质量 j
                for (int k = 1; k * k + j <= m; k++) // 枚举物品 i 的所有合法质量
                {
                    int x = abs(a[i] - k); // 计算代价，题目要求要平方
                    dp[i][j + k * k] = min(dp[i][j + k * k], dp[i - 1][j] + x * x);
                }
```

### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
const ll MX = 1e18 + 7;
const int mod = 998244353;
const int maxn = 1e5 + 5;
const int inf = 1e9;

int dp[11][10005];

int main()
{
    fastio;
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            dp[i][j] = inf;
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
            if (dp[i - 1][j] != inf)
                for (int k = 1; k * k + j <= m; k++)
                {
                    int x = abs(a[i] - k);
                    dp[i][j + k * k] = min(dp[i][j + k * k], dp[i - 1][j] + x * x);
                }
    cout << (dp[n][m] == inf ? -1 : dp[n][m]);
    return 0;
}
```

---

## 作者：fyx_Catherine (赞：3)

### 这是一道DP题
设f[i][j]为使得前i个正方形总面积为j的**最小代价**。

f[i+1][j+k^2]=min(f[i+1][j+k^2],f[i][j]+(a[i+1]-k)*(a[i+1]-k)); 可能有**无解**的情况。
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
int read(){
    int a=0,k=1;char c=getchar();
    while (!isdigit(c)){if (c=='-')k=-1;c=getchar();}
    while (isdigit(c)){a=a*10+c-'0';c=getchar();}
    return a*k;
}
int f[20][10050],n,m,a[20];
int main(){
    n=read();m=read();
    for(int i=1;i<=n;i++) 
    a[i]=read();
    memset(f,0x3f,sizeof(f));//初始化为无穷大
    f[0][0]=0;
    for(int i=0;i<n;i++)
	for(int j=0;j<=m;j++)
	    for(int k=0;k*k+j<=m;k++)
	    f[i+1][j+k*k]=min(f[i+1][j+k*k],f[i][j]+(a[i+1]-k)*(a[i+1]-k));
    if(f[n][m]==0x3f3f3f3f)printf ("-1\n");//如果f[n][m]仍是无穷大，就说明无解
    else printf("%d\n",f[n][m]);//否则输出f[n][m]
}

```
求管理员通过（QWQ）

---

## 作者：Nuyoah_awa (赞：2)

### 题目大意
给定 $n$ 个正方形，你可以任意改变这些正方形的大小，每次更改的代价为 $(|A_i-B_i|)^2$。请你求出使 $n$ 个正方形的面积和为 $m$ 的最少代价。

### 题目分析

由于题目说 $1 \le n \le 10, 1 \le m \le 10^4, a_i \le 100$，于是容易发现，每个正方形更改后的边长最大为 $100$（因为如果 $b_i > 100$，$b_{i} \times b_i > 10^4$，即 $b_i \times b_i > m$）。考虑到可以更改的情况不多，我们可以考虑 DP 求解。

我们定义状态 $f_{i, j}$ 表示：到第 $i$ 个数，正方形面积总和为 $j$ 的最少代价。对于每个正方形，我们可以枚举它改完后的边长为 $k$。转移方程为：

$$f_{i, j} = \min(f_{i, j}, f_{i - 1, j - k \times k} + |a_i - k| \times |a_i - k|)$$

### code
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const int N = 1e4 + 5, INF = 1e9; 
int n, m, a[N], f[N][N];
int main()
{
    scanf("%d %d", &n, &m);
    for(int i = 1;i <= n;i++)
		scanf("%d", &a[i]);
    for(int i = 1;i <= m;i++)
		f[0][i] = INF;
    for(int i = 1;i <= n;i++)
    {
        for(int j = 0;j <= m;j++)
        {
            f[i][j] = INF;
            for(int k = 1;k * k <= j;k++)
                if(f[i-1][j-k*k] != INF)
					f[i][j] = min(f[i][j], f[i-1][j-k*k] + abs(a[i] - k) * abs(a[i] - k));
        }
    }
    if(f[n][m] == INF)
		printf("-1");
	else
		printf("%d", f[n][m]);
    return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：2)

### 题目简述 
有 $n$ 个正方形,第i个的边长是 $a_i$ ,将其变成一个边长为 $b_i$ 的正方形需要 $(a_i-b_i)^2$ 的代价，将所有正方形改为面积总和为 $m$ 最小要多少代价?

### 题目分析

很简单的dp。

$f_i$表示将正方形改造为面积总和为 $i$ 最小代价，初始化时应将 $f_1$~$f_m$都设为 INF (无穷大)，得到状态转移方程：

$$f_i=min(f_i,f_{i-b×b}+(a-b)^2)$$

题目求的就是 $f_m$ 将其输出即可。

### $CODE$：

```cpp
#include<iostream>
#include<cmath>
using namespace std;
const int INF=1e9;
const int MAXN=1e4+5;
int f[MAXN]={0};
int n,m,a;
int main(){
	for(int i=1;i<MAXN;i++)
		f[i]=INF;//初始化
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a;//省一个数组
		for(int j=m;j>=0;j--){
			f[j]+=a*a;
			for(int k=0;k*k<=j;k++)
				f[j]=min(f[j],f[j-k*k]+(a-k)*(a-k));//状态转移方程
		}
	}
	if(f[m]>=INF) cout<<"-1";
	else cout<<f[m];//输出
}
```



 

---

## 作者：Water_Cows (赞：1)

- $\texttt{P3030}$ [USACO11NOV]Tile Exchanging S

- 算法：DP

- 题目大意：可以把边长为 $a_i$ 的正方形变成边长为 $k$ 的正方形，代价为 $(a_i-k)^2$。求把所有正方形的面积总和变成 $m$ 的最小代价。

- 思路

  - 状态：用 $f_{i,j}$ 表示前 $i$ 个正方形面积总和为 $j$ 时的代价。
  
  - 转移：$f_{i,j}=\min(f_{i,j},f_{i-1,j-k \times k}+(a_i-k)^2)$ ，其中 $k$ 枚举的是目标边长。
  
  - 初始化：$f_{0,0}=0$ 其余为 INF。
  
  - 答案：$f_{n,m}$

- 其实可以压缩空间的，但是没必要。

- $Code$

  ```cpp
  #include <iostream>
  #include <cstring>
  using namespace std;
  
  const int N = 10 + 7;
  const int M = 10000 + 7;
  
  int n, m;
  int a[N], f[N][M];
  
  int main()
  {
      ios::sync_with_stdio(false);
      cin.tie(0); cout.tie(0);
  
      cin >> n >> m;
      for(int i=1; i<=n; i++)
          cin >> a[i];
  
      memset(f, 0x3f, sizeof(f));
      f[0][0] = 0; // 初始化
  
      for(int i=1; i<=n; i++)
      {
          for(int j=0; j<=m; j++) // 枚举大小
          {
              for(int k=0; k*k<=j; k++) // 枚举边长
              {
                  f[i][j] = min(f[i][j], f[i-1][j-k*k] + (a[i] - k) * (a[i] - k));
              }
          }
      }
      cout << (f[n][m] >= 0x3f3f3f3f? -1: f[n][m]) << endl;
  }
  ```




---

## 作者：zgy_123 (赞：0)

简单明了的 DP。

我们可以定义 `f[i][j]` 为前 $i$ 个正方形面积和为 $j$ 的花费。状态转移方程：`f[i+1][j+k*k]=min(f[i][j]+(a[i+1]-k)*(a[i+1]-k),f[i+1][j+k*k])`，与其他题解不同。

由于要区最小值，所以我们提前将 `f` 数组设置为 $\infty$，更好处理。这时还要特判一下是不是 `-1` 的情况。

AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[15][10005],a[15];
int main(){
	memset(f,127,sizeof(f));
	f[0][0]=0;
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=0;i<n;i++)
		for(int j=0;j<=m;j++){
			for(int k=1;k*k<=m-j;k++)
				f[i+1][j+k*k]=min(f[i][j]+(a[i+1]-k)*(a[i+1]-k),f[i+1][j+k*k]);
//			cout<<f[i+1][j]<<' ';
		}
	if(f[n][m]==0x7f7f7f7f) cout<<-1;
	else cout<<f[n][m];
	return 0;
}

```

---

## 作者：wu13115899522 (赞：0)

看到题目中给的m的范围是 $10000$，就大概率是可以 `DP`。

式子很好理解，每一个对应的位置都是可以改或者不改，由于题目数据较小，可以直接枚举这一更改。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void read(int &x){
    x=0;int f=1;char c=getchar();
    while(!(c<='9'&&c>='0')){if(c=='-')f=-1;c=getchar();}
    while(c<='9'&&c>='0')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x*=f;
}
int n,m,f[15][10005];
int a[15];
int main(){
    read(n);read(m);
    for(int i=1;i<=n;i++){
        read(a[i]);
    }   
    memset(f,63,sizeof(f));
    f[0][0]=0;//初始化 
    int inf=f[1][1];
    for(int i=1;i<=n;i++){//第i个点 
        for(int j=0;j<=m;j++){//面积为j 
            for(int k=0;k*k<=j;k++){//更改k的边长 
                f[i][j]=min(f[i][j],f[i-1][j-k*k]+(a[i]-k)*(a[i]-k));
            }
        }
    }
    if(f[n][m]==inf){
        printf("-1\n");
    }
    else printf("%d\n",f[n][m]);
    return 0;
}
```


---

## 作者：legend_cn (赞：0)

# **解题思路：**

这道题考查的算法是 DP。


**状态定义**：$dp\left ( i,j \right )$ 表示在第 $i$ 个正方形中，分配的面积为 $j$ 的最小花费。


**初始化**：$dp(0,0)= 0$。在代码中，可以把 dp 数组定义为全局变量，这样就可以不初始化了。$dp\left ( 0,1-m \right )$ 需要初始化为 int 最大值，在这里我用的是 $10^9$。

**状态转移方程**：
$$ dp(i,j)=\min \left (dp\left (i,j\right ),dp\left (i-1,j-k \times k\right )+ \left | a\left (i\right )-k \right | \times \left | a\left (i\right )-k\right |\right )  $$

**答案**：
$dp\left ( n,m \right ) $

在特殊情况时，$dp\left ( n,m \right )$ 有可能不符合题目要求，需要输出 -1。

# **AC代码**

```cpp
#include<cstdio>
int n,m,a[15],dp[15][10005];
int min(int a,int b){return a<b?a:b;}
int abs(int a){return a>=0?a:-a;}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)dp[0][i]=1e9;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=1e9;
            for(int k=1;k*k<=j;k++)
                if(dp[i-1][j-k*k]!=1e9)
					dp[i][j]=min(dp[i][j],dp[i-1][j-k*k]+abs(a[i]-k)*abs(a[i]-k));
        }
    }
    if(dp[n][m]==1e9)printf("-1");
	else printf("%d",dp[n][m]);
}
```


---

