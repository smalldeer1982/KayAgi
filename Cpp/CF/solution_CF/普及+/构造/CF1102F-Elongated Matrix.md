# Elongated Matrix

## 题目描述

You are given a matrix $ a $ , consisting of $ n $ rows and $ m $ columns. Each cell contains an integer in it.

You can change the order of rows arbitrarily (including leaving the initial order), but you can't change the order of cells in a row. After you pick some order of rows, you traverse the whole matrix the following way: firstly visit all cells of the first column from the top row to the bottom one, then the same for the second column and so on. During the traversal you write down the sequence of the numbers on the cells in the same order you visited them. Let that sequence be $ s_1, s_2, \dots, s_{nm} $ .

The traversal is $ k $ -acceptable if for all $ i $ ( $ 1 \le i \le nm - 1 $ ) $ |s_i - s_{i + 1}| \ge k $ .

Find the maximum integer $ k $ such that there exists some order of rows of matrix $ a $ that it produces a $ k $ -acceptable traversal.

## 说明/提示

In the first example you can rearrange rows as following to get the $ 5 $ -acceptable traversal:

```
<br></br>5 3<br></br>10 8<br></br>4 3<br></br>9 9<br></br>
```

Then the sequence $ s $ will be $ [5, 10, 4, 9, 3, 8, 3, 9] $ . Each pair of neighbouring elements have at least $ k = 5 $ difference between them.

In the second example the maximum $ k = 0 $ , any order is $ 0 $ -acceptable.

In the third example the given order is already $ 3 $ -acceptable, you can leave it as it is.

## 样例 #1

### 输入

```
4 2
9 9
10 8
5 3
4 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2 4
1 2 3 4
10 3 7 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6 1
3
6
2
5
1
4
```

### 输出

```
3
```

# 题解

## 作者：Siyuan (赞：11)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/articles/problem-Codeforces-1102F-Elongated-Matrix/)

---

## Description

> 题目链接：[Codeforces 1102F](https://codeforces.com/contest/1102/problem/F)

给你一个 $n$ 行 $m$ 列的矩阵 $a_{i,j}$，其中每个元素都是正整数 。

你可以任意改变行的顺序，但是不能改变同一行中元素的顺序。确定行的顺序后，你可以通过以下方式遍历整个矩阵：首先访问从顶行到底部的第一列的所有元素，然后对第二列进行相同的操作，依此类推。在遍历期间，按照访问它们的顺序记下元素，得到一个序列 $s_i$。设这个序列为 $s_1,s_2,\dots,s_{nm}$。

如果对于任意的 $i(1\le i<nm)$，有 $\vert s_i-s_{i+1}\vert\ge k$ 成立，我们称 $k$ 是合法的。

你要做的是寻找一个 $a_{i,j}$ 的行的排列顺序，使得最大的合法的 $k$ 值最大。

数据范围：$1\le n\le 16$，$1\le m\le 10^4$，$2\le nm$，$1\le a_{i,j}\le 10^9$

------

## Solution

我们发现行的排列顺序的本质是：**哈密顿回路**，即第 $i$ 行接着第 $i+1$ 行并产生贡献，第 $n$ 行接着第 $1$ 行并产生贡献。注意到 $n$ 的范围很小，我们可以考虑**状态压缩**。

由于第一行（哈密顿回路中的**起点**）是不确定的，因此我们首先要枚举起点。定义状态 $f_{i,j}$ 表示已经考虑了 $i$ 集合内的行，最后一行是 $j$ 时，不考虑第一行和最后一行的贡献的**最大贡献**（要求 $\vert s_i-s_{i+1}\vert$ 的最小值最大）。其中第 $i$ 行和第 $j$ 的贡献是指：同一列的元素的的差的绝对值的**最小值**。

状态转移方程如下：
$$f_{S\cup j,j}=\max\{\min(f_{S,i},\text{cost}(i,j))\}\quad (i\in S,j\not\in S) $$
其中 $\text{cost}(i,j)$ 表示第 $i$ 行和第 $j$ 行相邻的贡献。

统计答案时，我们枚举结束点 $i$，根据起点 $k$ 可以得到答案为：
$$\text{Ans}=\max\{\min(f_{2^n-1,i},\text{cost}'(k,i))\}$$
其中 $2^n-1$ 为全集，$\text{cost}'(i,j)$ 表示第 $i$ 行为第一行，第 $j$ 行为最后一行时，第一行和最后一行之间的贡献。

**时间复杂度**：$O(2^nn^3)$

------

## Code

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

const int N=17,M=1e4+5;
const int INF=1<<30;
int n,m,a[N][M],f[1<<N][N],g[N][N],h[N][N];

void init() {
	for(int i=0;i<n;++i) for(int j=0;j<n;++j) {
		g[i][j]=INF,h[i][j]=INF;
		for(int k=1;k<=m;++k) g[i][j]=std::min(g[i][j],std::abs(a[i][k]-a[j][k]));
		for(int k=2;k<=m;++k) h[i][j]=std::min(h[i][j],std::abs(a[i][k-1]-a[j][k]));
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i) for(int j=1;j<=m;++j) scanf("%d",&a[i][j]);
	init();
	int ans=0;
	for(int k=0;k<n;++k) {
		memset(f,0,sizeof(f));
		f[1<<k][k]=INF;
		for(int S=0;S<(1<<n);++S) for(int i=0;i<n;++i) if(S&(1<<i)) {
			for(int j=0;j<n;++j) {
				if(!(S&(1<<j))) f[S|(1<<j)][j]=std::max(f[S|(1<<j)][j],std::min(f[S][i],g[i][j]));
			}
		}
		for(int i=0;i<n;++i) {
			ans=std::max(ans,std::min(f[(1<<n)-1][i],h[k][i]));
		}
	}
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：Eibon (赞：5)

发现 $n \le 16$，自然联想到状压。

设 $f_{i,j}$ 表示二进制状态为 $i$ 时，即已经考虑了集合 $i$ 中的行数，且当前处理到的最后一行为 $j$ 的最大值。

预处理 $g$ 和 $h$ 数组，$g_{i,j}$ 表示第 $i$ 行与第 $j$ 行间上下差值最小值，$h_{i,j}$ 表示第一行为 $i$，最后一行为 $j$，首尾产生的最小 $k$ 值。

然后正常进行状压转移即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=20;
const int maxm=1e4+5;
const int INF=0x3f3f3f3f3f3f3f3f;
int n,m,ans;
int a[maxn][maxm],dp[(1<<16)+5][20],g[maxn][maxn],h[maxn][maxn];
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%lld",&a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			g[i][j]=h[i][j]=INF;
			for(int k=1;k<=m;k++){
				g[i][j]=min(g[i][j],abs(a[i][k]-a[j][k]));
				if(k>=2){
					h[i][j]=min(h[i][j],abs(a[i][k]-a[j][k-1]));
				}
			}
		}
	}
	for(int k=1;k<=n;k++){
		memset(dp,0,sizeof dp);
		dp[(1<<(k-1))][k]=INF;
		for(int s=0;s<(1<<n);s++){
			for(int i=1;i<=n;i++){
				if(s&(1<<(i-1))){
					for(int j=1;j<=n;j++){
						if(!(s&(1<<(j-1)))){
							dp[s|(1<<(j-1))][j]=max(dp[s|(1<<(j-1))][j],min(dp[s][i],g[i][j]));
						}
					}
				}
			}
		}
		for(int i=1;i<=n;i++){
			ans=max(ans,min(dp[(1<<n)-1][i],h[k][i]));
		}
	}
	printf("%lld\n",ans);
	return 0;
}
//dyyyyds
```

---

## 作者：hovny (赞：3)

## [题面](https://www.luogu.org/problemnew/show/CF1102F)

给出$n*m$个矩阵，从第一列开始，一列一列访问元素，依次记元素为$S_1,S_2,…S_{nm}$，则$k$的价值为相邻两个元素差的绝对值的最小值，即$k=min\{|S_1 - S_2|,|S_2 - S_3|,…,|S_{nm-1} - S_{nm}|\}$

现在可以改变任意行的顺序，求$k$的最大值

## 思路：

### 正解应该是状压DP

### 但是以下讲的是另一种玄学做法——搜索

当然啦~，直接爆搜是不行的，在一切之前，我们先研究一下题目

然后做一些预处理

**比如：**

1、改变的是行的顺序，因此任意**两行之间的最小差值**可以预先求出来



|           9           |           9           |
| :-------------------: | :-------------------: |
|        **10**         |         **8**         |
| $\large \color{red}5$ | $\large \color{red}3$ |
| $\large \color{red}4$ | $\large \color{red}3$ |

图中两行的差值就是$0$吧，然后类似处理其他行

就是先把一些**固定的值**处理出来

2、可以把两行分别在头尾的代价处理出来

|           5           | $\large \color{red}3$ |
| :-------------------: | :-------------------: |
|         **9**         |         **9**         |
|        **10**         |         **8**         |
| $\large \color{red}4$ |         **3**         |

这里的顺序和先前不一样是想说明**行的顺序**是可以**改变**的！这时要处理的比较特殊，想象一下转换成一条链后，标红的是相邻的，我们也依次把这样的差值处理出来



**预处理完后**

原本和$m$有关的数据就只和$n$有关了，而$n$的范围有那么小，~~于是开始乱搞~~

然后我们就搜索，~~枚举$n$的全排列~~

当然这是不可能的，~~不炸就怪~~，肯定要加剪枝

然后就加——**最优性剪枝**  ~~其实我没学过深搜的优化技巧~~

并且加入一个线段树的$lowbit$操作，差不多就挺快的了

其实大致算一下：

$$16!=20\ 9227\ 8988\ 8000$$

也不多啦~

加了优化之后，有很大的减少的

先上代码，注释掉的读优不用管

Code：

```cpp
#include<bits/stdc++.h>
#define INF 0x7f7f7f7f
//#define getchar() *(pos++)
#define N 20
#define M 10010
using namespace std;
struct node{
	int to,nxt,cost;
	node(int a,int b):to(a),cost(b){	}
	node(){	}
}b[M<<1];
int head[N],n,m,a[N][M],s[N][N],p[N][N],res,ans,bef,Total;
int f[1<<20][20],C[100010];
//char bf[1<<25],*pos;
//int read(){int s=0;char c=getchar();
//	while(!isdigit(c))c=getchar();
//	while(isdigit(c)){s=(s<<1)+(s<<3)+c-'0';c=getchar();}
//	return s;
//}
void DFS(int k,int res,int t,int last)
{//k表示做
	if(res<=ans) return;//ans表示目前的最大值
	if(k==n){
		ans=max(ans,min(res,p[bef][last]));
		return;
	}
	int cur=Total-t,j;
	while(cur){//树状数组的lowbit
		j=C[cur&(-cur)];//对应到回原来的编号-1，因为第一位 1=2^0
		if(s[last][j+1]>ans) 
			DFS(k+1,min(res,s[last][j+1]),t|(1<<j),j+1);
		cur-=cur&(-cur);
	}
}
int main()
{
	int i,j,k;
//	bf[fread(bf,1,1<<25,stdin)]='\0',pos=bf;
	n=read();m=read();k=1;
	for(i=0;i<=16;i++)//2^k对应到k，方便后面知道是哪一位
		C[k]=i,k<<=1;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			a[i][j]=read();
	for(i=1;i<=n;i++)//预处理 第1条
		for(j=1;j<i;j++)
		{
			res=INF;
			for(k=1;k<=m;k++)
				res=min(res,abs(a[i][k]-a[j][k]));
			s[i][j]=s[j][i]=res;
		}
	for(i=1;i<=n;i++)//预处理 第二条
		for(j=1;j<=n;j++)
		{
			res=INF;
			for(k=1;k<m;k++)
				res=min(res,abs(a[i][k+1]-a[j][k]));
			p[i][j]=res;
		}
	if(n==1){printf("%d",p[1][1]);return 0;}//这种情况不特判也没关系
	Total=(1<<n)-1;//用于DFS中取反操作，是我太菜了，只会这种方法
	for(i=1;i<=n;i++)//bef表示记录首行，方便最后判断
		bef=i,DFS(1,INF,1<<(i-1),i);
	printf("%d",ans);
	return 0;
}
```

### 关于时间复杂度

->Sinner 这位大佬说：时间复杂度是不正确的！ 我（瑟瑟发抖）：根据~~玄学~~，跑得超快的，因为两行之间的最小值比较难卡，所以时间还是比较稳定的~~我们不是理论派~~

~~好吧，此份题解仅供参考~~

---

## 作者：_sys (赞：2)

首先我们发现：$n \leq 16$ ，再看题，我们不难发现，最终的结果我们只考虑第一行是什么，最后一行是什么，中间能构成的**最大值**是什么。我们记$diff[i][j]$表示$i$在第一位，$j$在最后一位，他们俩对答案的限制，记中间的最大值为$ans$。这样的答案就是$\min(diff[i][j],ans)$

$diff[i][j]$直接$n^2m$枚举就好了，我们考虑如何计算$ans$

此时我们就不难想到状压$dp$了

我们用$dp[i][j][k]$状态$i$，第一位是$k$，最后一位是$j$能获得的最大值。再记$mini[i][j]$表示第$i$行与第$j$行的对应数的差的最小值

可以得到转移方程：

$dp[i][j][k]=min(dp[i][j][k],min(dp[i'][j'][k],mini[j][j']))$

其中

$i'\& j=i$

还要注意$dp[i][j][k]$合法的条件是

- 当$i$仅有一位有值时，$j=k$
- 当$i$多位有值时，$j \neq k$

时间复杂度：$2^nn^3$

代码（抱歉这次写得有点丑）：

```cpp
#include <bits/stdc++.h>
const int Maxn=17,Maxm=10005;
using namespace std;
int dp[1<<Maxn][Maxn][Maxn],n,m,val[Maxn][Maxm],diff[Maxn][Maxn],mini[Maxn][Maxn],ans;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&val[i][j]);
    memset(mini,0x3f,sizeof(mini));
    memset(diff,0x3f,sizeof(diff));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=m;k++)
            {
                if(i!=j)
                    mini[i][j]=min(mini[i][j],abs(val[i][k]-val[j][k]));
                diff[i][j]=min(diff[i][j],k==m?0x3f3f3f3f:abs(val[i][k+1]-val[j][k]));
            }
    memset(dp,0x3f,sizeof(dp));
    for(int i=0;i<(1<<n);i++)
        for(int k=1;k<=n;k++)
            if((i>>k-1)&1)
                for(int j=1;j<=n;j++)
                    if(((1<<(j-1))&i)&&j!=k)
                        for(int q=1;q<=n;q++)
                            if((1<<(q-1)&i)&&(q!=k||i==(1<<(j-1))+(1<<(k-1))||i==(1<<(j-1)))&&(q!=j||i==(1<<(q-1))))
                                dp[i][j][q]=max(dp[i][j][q]==0x3f3f3f3f?0:dp[i][j][q],min(dp[i-(1<<(j-1))][k][q],mini[j][k]));
    if(n==1) 
    {
        printf("%d",diff[1][1]);
        return 0;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(i!=j)
                ans=max(ans,min(diff[i][j],dp[(1<<n)-1][i][j]));
    printf("%d",ans);
    return 0;
}
    
```

---

## 作者：攀岩高手 (赞：1)

## 思路 ##
写个不太一样的，二分答案的题解。

考虑二分 $k$ 。为了验证当前答案的可行性，先预处理出矩阵 $c[i][j]$ 表示第 $i$ 行与第 $j$ 行间差的绝对值的最大值是否大于等于 $k$ 。这个可以 $O(n^2m)$ 做到。然后考虑状压 DP 。$f[S][i][j]$ 表示当前处理过的行的状态为 $S$ ，首行是 $i$ ，末行是 $j$ 时答案是否可行。容易推出 DP 方程 $f[S][i][j]=\bigoplus_{k\in S\wedge c[j][k]} f[S\setminus j][i][k]$ ，其中 $\bigoplus$ 表示或，$S\setminus j$ 表示 $S$ 除去 $j$ 的元素。这样就可以 $O(n)$ 转移得到每个状态，最后再暴力枚举首行和末行，总时间复杂度 $O(2^nn^3log10^9)$ ，并不能过。

观察到 $f$ 其实是一个只有 0 和 1 的 bool 数组，而最后一维 $j$ 也是 $O(n)$ 级别的，我们可以考虑把最后一维压掉。$f[S][i]$ 表示当前处理过的行的状态为 $S$ ，首行是 $i$，末行使答案可行的状态。同时我们把最开始预处理的矩阵 $c$ 的每行也压成一个 int 。这样做就可以使状态数少一个 $n$ ，转移仍是 $O(n)$ 的，因此时间复杂度为 $O(2^nn^2log10^9)$ ，能过。

代码中为了优化速度，把 f 数组小的一维放在了前面。

## 代码 ##
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN=20;
const int MAXM=11000;
const int MAXS=70000;
int n, m;
int a[MAXN][MAXM];
int c[MAXN], f[MAXN][MAXS];
bool chk1(int x, int y, int k)
{
	for (int i=1; i<=m; i++)
		if (abs(a[x][i]-a[y][i])<k) return 0;
	return 1;
}
bool chk2(int x, int y, int k)
{
	for (int i=1; i<m; i++)
		if (abs(a[x][i+1]-a[y][i])<k) return 0;
	return 1;
}
bool check(int k)
{
	memset(c, 0, sizeof c);
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++)
			if (chk1(i, j, k)) c[i]|=1<<j-1;
	memset(f, 0, sizeof f);
	for (int i=1; i<=n; i++)
		for (int s=1; s<1<<n; s++)
		{
			if (!(s&1<<i-1)) continue;
			if (s==1<<i-1) f[i][s]=1<<i-1;
			else
			{
				for (int j=1; j<=n; j++)
					if (s&1<<j-1&&f[i][s^1<<j-1]&c[j])
						f[i][s]|=1<<j-1;
			}
		}
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++)
			if (chk2(i, j, k)&&f[i][(1<<n)-1]&1<<j-1) return 1;
	return 0;
}
int main()
{
//	freopen("CF1102F.in", "r", stdin);
//	freopen("CF1102F.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++)
			scanf("%d", &a[i][j]);
	int l=0, r=1E9;
	while (l<r)
	{
		int mid=l+r+1>>1;
		if (check(mid)) l=mid;
		else r=mid-1;
	}
	printf("%d\n", l);
	return 0;
}
```

---

