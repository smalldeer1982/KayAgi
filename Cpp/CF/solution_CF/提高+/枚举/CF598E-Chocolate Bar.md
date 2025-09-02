# Chocolate Bar

## 题目描述

你有一块由 $n \times m$ 个方块组成的矩形巧克力。你想吃恰好 $k$ 个方块，因此可能需要断裂巧克力。

在一次操作中，你可以将任意一块矩形巧克力断裂成两块矩形。你只能沿着方块之间的线条进行断裂：横向或纵向。断裂的费用等于断裂长度的平方。

例如，若你有一块由 $2 \times 3$ 个方块组成的巧克力，你可以横向断裂将其分成两块 $1 \times 3$ 的矩形（断裂费用为 $3^2 = 9$），或通过两种不同的方式纵向断裂，得到两块 $2 \times 1$ 和 $2 \times 2$ 的矩形（断裂费用为 $2^2 = 4$）。

对于给定的多个 $n$、$m$ 和 $k$ 的值，求断裂巧克力的最小总费用。当且仅当断裂操作结束后存在一组矩形碎片，其总方块数恰好为 $k$ 时，你才能吃掉这 $k$ 个方块。剩余的 $n \cdot m - k$ 个方块不必组成一个完整的矩形。


## 说明/提示

在第一个示例查询中，需要执行两次断裂：
- 将 $2 \times 2$ 的巧克力分成两块 $2 \times 1$（断裂费用为 $2^2 = 4$），
- 将所得的 $2 \times 1$ 分成两块 $1 \times 1$（断裂费用为 $1^2 = 1$）。

在第二个示例查询中，想要吃 $3$ 个方块。可以采用与第一个示例查询相同的策略。

翻译由 QwQ-32B 完成

## 样例 #1

### 输入

```
4
2 2 1
2 2 3
2 2 2
2 2 4
```

### 输出

```
5
5
4
0
```

# 题解

## 作者：Clever_Jimmy (赞：5)

【CodeForces】CF598E Chocolate Bar

### 题意简述：

给定一个 $n\times m$ 的矩阵，将 $r\times c$ 的矩阵切成 $r \times c'$ 和 $r\times (c - c')$ 的矩阵需要 $r^2$ 的花费。

求切出大小和为 $k$ 的矩阵所需最小花费。

多组数据。

$1 \le T \le 40910$，$1 \le n, m \le 30$，$1 \le k \le \min(n\cdot m, 50)$。

[题目链接](https://codeforces.com/contest/598/problem/E)

### 解题思路：

设 $f(x, y, z)$ 表示要从 $x\times y$ 的矩阵中切出大小和为 $z$ 的矩阵所需最小花费。

我们可以枚举要将 $x\times y$ 切成 $x \times y'$ 和 $x\times (y - y')$，还是切成 $x'\times y$ 和 $(x - x')\times y$。

不难发现转移方程为
$$
f(x, y, z) = \min
\begin{cases}
 x^2 + f(x, y', z') + f(x, y - y', z - z') \quad(y' \in [1, \left\lfloor\dfrac{y}{2}\right\rfloor], z' \in [0, z])
 \\\\
 y^2 + f(x', y, z') + f(x - x', y, z - z') \quad(x' \in [1, \left\lfloor\dfrac{x}{2}\right\rfloor], z' \in [0, z])
\end{cases}
$$
答案即为 $f(n, m, k)$。

### 参考代码：

```cpp
#include <bits/stdc++.h>
#define LL long long

const int inf = 0x3f3f3f3f;
const int N = 30 + 5;
const int M = 30 + 5;
const int K = 50 + 5;

int n, m, k, f[N][M][K];

int F(int x, int y, int z) {
	if(f[x][y][z])
		return f[x][y][z];
	if(z == x * y || !z)
		return 0;
	int res = inf;
	for(int i = 1; i <= x - i; ++i)
		for(int j = 0; j <= z; ++j)
			res = std::min(res, y * y + F(i, y, j) + F(x - i, y, z - j));
	for(int i = 1; i <= y - i; ++i)
		for(int j = 0; j <= z; ++j)
			res = std::min(res, x * x + F(x, i, j) + F(x, y - i, z - j));
	return f[x][y][z] = res;
}

int32_t main() {
	int __tests;
	scanf("%d", &__tests);
	while(__tests--) {
		scanf("%d %d %d", &n, &m, &k);
		printf("%d\n", F(n, m, k));
	}
    return 0;
}
```

---

## 作者：Fool_Fish (赞：4)

首先我的方法是搜索，

那么就要想清楚每一次回溯需要哪些信息，

我是存了 $3$ 个信息：

$ (n,m,p)$ 表示要从 $n\times m$ 的矩阵中切出大小和为 $p$ 的矩阵所需最小花费。



两个循环分别枚举横着切还是竖着切。

因为两个循环基本上都是一致的，所以我就讲解一下横着切的：

首先看一下我的代码：

```cpp
for(int i=1;i<=n/2;i++){
	for(int j=0;j<=p;j++){
		int ans=m*m+f(i,m,j)+f(n-i,m,p-j);
		smin=min(ans,smin);
	}
}
```

最外层循环都看得懂吧，就是在枚举从哪里“下刀”，然后再枚举我们上下两块分别取用多少巧克力，并相应的进行转移，更新答案

核心部分大概就是这样的，因为每次转移的参数比较少，所以我们可以记忆化，直接对 $n,m,p$ 建立一个三维数组就行了

完整代码

```cpp
#include<cstdio>
#include<iostream>
#include<climits>
#include<algorithm>
#include<cmath>
using namespace std;
int s[55][55][55];
int inf=0x3f3f3f3f;
int f(int n,int m,int p){
	if(n*m==p || p==0){
		return 0;
	}
	if(n>m){
		swap(n,m);
	}
	if(s[n][m][p]>0){
		return s[n][m][p];
	}
	int smin=inf;
	for(int i=1;i<=n/2;i++){
		for(int j=0;j<=p;j++){
			int ans=m*m+f(i,m,j)+f(n-i,m,p-j);
			smin=min(ans,smin);
		}
	}
	for(int i=1;i<=m/2;i++){
		for(int j=0;j<=p;j++){
			int ans=n*n+f(i,n,j)+f(m-i,n,p-j);
			smin=min(smin,ans);
		}
	}
	return s[n][m][p]=smin;
}
int main(){
	int T,n,m,p;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d",&n,&m,&p);
		printf("%d\n",f(n,m,p));
	}
return 0;
}
```

---

## 作者：Yt_pY (赞：2)

更新于2019/7/15
优化了阅读体验

------------

## 暴力dp+五重循环

预处理出dp[i][j][k]所有值，然后O(1)查询即可。

相较于楼下我的代码做了一点优化，比如根据题目所说1<=k<=min(n*m,50)，就可以少循环一些内容，还有在分巧克力时，因为分成两部分，所以只需扫一半巧克力即可，全部扫一遍会重复计算。但总体思路都是一样的

ps:数组赋初值建议从0到31，这样绝对不会因为初值赋不对而导致min函数的问题，不然很容易爆0，~~反正多循环一两遍也不会超时~~
#### 测试点信息
最后一个点最慢，大概是240ms左右，我没开O2
## 代码
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int t;
int n,m,k;
int a[35][35][55];
void dp()
{
	memset(a,0x3f,sizeof(a));
	for(int i=0;i<=30;i++)
	{
		for(int j=0;j<=30;j++)
		{
			a[i][j][0]=0;
			if(i*j<=50)a[i][j][i*j]=0;
		}
	}
	for(int i=1;i<=30;i++)
	{
		for(int j=1;j<=30;j++)
		{
			int p=min(i*j,50);
			for(int k=1;k<=p;k++)//总共要切的份数 
			{
				for(int x=1;x<=i/2;x++)//横着切，扫一半
				{
					int z1=min(x*j,k);
					for(int ch=0;ch<=z1;ch++)
						a[i][j][k]=min(a[i][j][k],a[x][j][ch]+a[i-x][j][k-ch]+j*j); 
				}
				for(int y=1;y<=j/2;y++)//竖着切，同理，扫一半
				{
					int z2=min(y*i,k);
					for(int ch=0;ch<=z2;ch++)
						a[i][j][k]=min(a[i][j][k],a[i][y][ch]+a[i][j-y][k-ch]+i*i);
				}
			}
		}
	}
}
int main()
{
	dp();
	cin>>t;
	while(t--)
	{
		cin>>n>>m>>k;
		cout<<a[n][m][k]<<endl;
	}
    return 0;//结束
}
```

---

## 作者：cold_cold (赞：0)

[安利一波博客](https://www.cnblogs.com/cold-cold/p/10041929.html)

此题n,m范围处于30，显然不可以状压，只能考虑高次方复杂度DP

我们发现一个大的巧克力可以切成 两块宽与它相同，长的和等于它的巧克力 或 两块长与它相同，宽的和等于它的巧克力

状态设计为f[i][j][k]表示i\*j的巧克力得到大小为k的巧克力的最小花费

由此我们可以得到转移复杂度O(n\*m\*k\*(n+m)\*k)

一开始我居然把右移写成左移了，结果RE了

实现如下：

```cpp

#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
using namespace std;
typedef long long ll;
inline int read()
{
    register int p(1),a(0);register char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') p=-1,ch=getchar();
    while(ch>='0'&&ch<='9') a=a*10+ch-48,ch=getchar();
    return a*p;
}
const int N=40,M=1000;
int f[N][N][M],t,xx,yy,kk;
int main()
{
//	freopen("input","r",stdin);
//	freopen("output","w",stdout);
	memset(f,0x3f,sizeof(f));
	for(int i=0;i<=30;i++) for(int j=0;j<=30;j++) f[i][j][0]=0,f[i][j][i*j]=0;
	for(int i=1;i<=30;i++)
		for(int j=1,big=min(i*j,50);j<=30;j++,big=min(i*j,50))
			for(int k=1;k<=big;k++)
			{
				for(int l=1,lar=min(j*l,k);l<=(i>>1);l++,lar=min(j*l,k))
                    for(int tt=0;tt<=lar;tt++)
                        f[i][j][k]=min(f[i][j][k],f[l][j][tt]+f[i-l][j][k-tt]+j*j); 
                for(int l=1,lar=min(i*l,k);l<=(j>>1);l++,lar=min(i*l,k))
                    for(int tt=0;tt<=lar;tt++)
                        f[i][j][k]=min(f[i][j][k],f[i][l][tt]+f[i][j-l][k-tt]+i*i);
			}
	t=read();
	while(t--)
	{
		xx=read(),yy=read(),kk=read();
		printf("%d\n",f[xx][yy][kk]);
	}
    return 0;
}

```

---

## 作者：AC自动机 (赞：0)

#### 思路
暴力dp 
2333333

禁忌：五重循环

因为每块巧克力都可以看作是两块巧克力拼成的，所以只需要枚举如何分割巧克力，并枚举从分割的两块中每块取的块数，所以通过循环可以求出。

首先dp[i][j][k]表示大小为i*j的巧克力中取k块的代价，首先处理出所有值，然后O（1）查询即可。

#### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int xxx;
int dp[50][50][60];
const int INF=999999999;
int main(){
	for(register int i=0;i<=30;i++){
		for(register int j=0;j<=30;j++){
			for(register int k=0;k<=50;k++){
				dp[i][j][k]=INF;
				if(k==0||k==i*j||i*j==0)dp[i][j][k]=0;
				for(register int a=0;a<=k;a++){
					for(register int b=1;b<i;b++){
						dp[i][j][k]=min(dp[i][j][k],dp[b][j][a]+dp[i-b][j][k-a]+j*j);
					}
					for(register int c=1;c<j;c++){
						dp[i][j][k]=min(dp[i][j][k],dp[i][c][a]+dp[i][j-c][k-a]+i*i);
					}
				}
			}
		}
	}
	cin>>xxx;
	while(xxx){
		register int n,m,k;
		scanf("%d%d%d",&n,&m,&k);
		printf("%d\n",dp[n][m][k]);
		xxx--;
	}
}
```

---

## 作者：xy_xw_for_2024 (赞：0)

这道题。。。只有两篇题解  
此蒟蒻来发一篇深搜+记忆化的题解  
~~自认为速度比较快，总时间184ms~~
我就是用DFS来搜最小值，不信你自己看嘛。。  
前面的read和pr如果不懂可以看这个：  
[对称二叉树的题解中对read和pr的解释](https://www.luogu.org/blog/18723278048hxmz/solution-p5018)
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
inline void read(int &x) {
	x=0;int f=1;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=x*10+s-48;s=getchar();}
	x*=f;
}
inline void pr(int x) {
	if(x<0)x=-x;
	if(x>9)pr(x/10);
	putchar(x%10+48);
}
int dp[35][35][55],n,k,m,t;
inline int dfs(int x,int y,int z) {
	int i,j;
	if(x>y)
		swap(x,y);
	int ans=1000000000;
	if(x*y==z||z==0)//如果全部正好可以和剩下的需求符合或者不需要了就返回
		return 0;
	if(dp[x][y][z])//有值可以直接返回，记忆化
		return dp[x][y][z];
	for(i=1; i<=x/2; i++)//横着切，搜到一半就可以了，再往下是重复的
		for(j=0; j<=z; j++)//深搜切每一种大小
			ans=min(ans,dfs(i,y,j)/*长变了*/+dfs(x-i,y,z-j)/*宽变了*/+y*y/*花费*/);//更新
	for(i=1; i<=y/2; i++)//同上
		for(j=0; j<=z; j++)
			ans=min(ans,dfs(x,i,j)+dfs(x,y-i,z-j)+x*x);
	return dp[x][y][z]=ans;//记忆化
}
int main() {
	read(t);//读入
	while(t--) {
		read(n),read(m),read(k);
		pr(dfs(n,m,k)),putchar('\n');
	}
}
```
附测试点测试结果    
#1
AC
15ms/264KB
 
#2
AC
15ms/268KB
#3
AC
15ms/268KB
#4
AC
78ms/260KB
#5
AC
61ms/256KB  
大概就是这样的，不知道大家能不能看懂，大家可以与我私信，一起讨论讨论

---

