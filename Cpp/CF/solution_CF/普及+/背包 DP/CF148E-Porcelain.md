# Porcelain

## 题目描述

During her tantrums the princess usually smashes some collectable porcelain. Every furious shriek is accompanied with one item smashed.

The collection of porcelain is arranged neatly on $ n $ shelves. Within each shelf the items are placed in one row, so that one can access only the outermost items — the leftmost or the rightmost item, not the ones in the middle of the shelf. Once an item is taken, the next item on that side of the shelf can be accessed (see example). Once an item is taken, it can't be returned to the shelves.

You are given the values of all items. Your task is to find the maximal damage the princess' tantrum of $ m $ shrieks can inflict on the collection of porcelain.

## 说明/提示

In the first case there are two shelves, each with three items. To maximize the total value of the items chosen, one can take two items from the left side of the first shelf and one item from the right side of the second shelf.

In the second case there is only one shelf, so all three items are taken from it — two from the left side and one from the right side.

## 样例 #1

### 输入

```
2 3
3 3 7 2
3 4 1 5
```

### 输出

```
15
```

## 样例 #2

### 输入

```
1 3
4 4 3 1 2
```

### 输出

```
9
```

# 题解

## 作者：wanggiaoxing (赞：9)

### 分组背包
这道题是一道分组背包，那么我们把什么当成一个小组呢，即第 $i$ 层取了从 $1$ 到 $k$ 的所有情况的最大值，那么我们可以提前处理出来这个，我们设计状态. $dp1[i][j]$ 表示在第 $i$ 行砸了 $j$ 个的最大值。
$ dp1[i][j]=\max(dp1[i][j],sum[l]+sum[k]-sum[r]) $

其中 $l$ 和 $r$ 分别表示左边取到哪，右边取到哪, $sum$ 数组表示前缀和（想一想为啥式子中前缀和下标未减一）。

现在处理完每一个小组，该干什么不用我说了吧. $dp[i][j]$ 表示考虑到第 $i$ 行生气次数为 $j$ 的最大值

$dp[i][j]=\max(dp[i][j],dp[i-1][k-s]+dp1[i][s])$

其中 $k$ 为枚举的总生气次数, $s$ 为枚举的这一层取了几个。

上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[101][10001],dp1[101][101],n,m,v[101],sum[101][101],q[101];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int k;
		cin>>k;
		for(int j=1;j<=k;j++)
			cin>>v[j],sum[i][j]=sum[i][j-1]+v[j];
		for(int j=1;j<=k;j++)
			for(int l=0;l<=j;l++)
			{
				int r=k-(j-l);
				dp1[i][j]=max(dp1[i][j],sum[i][l]+sum[i][k]-(r==0?0:sum[i][r]));//边界处理
			}
		q[i]=k;
	}
	for(int i=1;i<=n;i++)
		for(int k=0;k<=m;k++)
			for(int j=0;j<=q[i];j++)
				if(k>=j)
					dp[i][k]=max(dp[i][k],dp[i-1][k-j]+dp1[i][j]);//分组背包
	cout<<dp[n][m];
}
```



---

## 作者：SSHhh (赞：5)

这道题的思路是分组背包。。。

题意其实就是求在 n 层取 m 个，且每一个只能从左边或右边取时的最大价值和。那么解法就很简单了：

首先预处理出每一层取若干个的最大价值 —— dp1[i][j] 表示在第 i 层取 j 个的最大价值。
很显然，每一次只能从最左边或最右边取，所以问题就变得简单了，每一个 dp1[i][j] 都只能由 dp1[i-1][j] 和 dp1[i][j+1] 转移而来（注意一个小细节，因为 dp1[i][j] 会依靠 dp1[i][j+1] 来计算，所以 j 必须从大到小枚举），转移方程为：dp1[k][l]=max(dp1[k][l], {第k层左边取i个，右边取j个的价值} )。满足 1<=k<=n , 1<=l<={第i层的物品数} , 0<=i<=l , j=l-i

有了 dp1 以后，我们再用一个 dp2[i][j] 表示考虑到了第 i 层柜子，已经取了 j 个物品时的最大总价值。因为每一层要么不取，要么取 1~{第i层的物品数} 个，所以就枚举这一层取了几个物品，然后进行转移即可。转移方程为：
dp2[k][i]=max(dp2[k][i],dp2[k-1][i-j]+dp1[k][j]);。
满足1<=k<=n , 0<=i<=m , 0<=j<=min(i,{第i层的物品数})

最后答案就是 dp[n][m]。

对了还有一点，计算时，使用每一行的前缀和可以快速计算出第k层左边取i个，右边取j个的价值。

```cpp
#include<iostream>
#include<vector>
using namespace std;
int n,m,N,ans,dp1[105][105],sum[105][105]/*每一层的前缀和*/,dp2[105][10005];
vector<int> a[105];
int cal(int k,int i,int j) //第 k 层取了前 i 个和后 j 个的总价值
{
	int N=a[k].size();
	return sum[k][N]-sum[k][N-j]+sum[k][i];
}
int main()
{
	int N,x;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>N;
		for(int k=1;k<=N;k++)
			cin>>x,a[i].push_back(x),sum[i][k]=sum[i][k-1]+x;//因为每一层长度不定，用一个vector保存，同时计算前缀和
	}
	for(int k=1;k<=n;k++)
		for(int l=1;l<=a[k].size();l++)
			for(int i=0;i<=l;i++) {int j=l-i;dp1[k][l]=max(dp1[k][l],cal(k,i,j));}//dp1转移
	for(int k=1;k<=n;k++)
		for(int i=0;i<=m;i++)
			for(int j=0;j<=a[k].size() && j<=i;j++)
				dp2[k][i]=max(dp2[k][i],dp2[k-1][i-j]+dp1[k][j]);//dp2转移
	cout<<dp2[n][m];
	return 0;
}

```

---

## 作者：activeO (赞：4)

## 题目大意

有 n 组序列，第 i 组有 $ k_i $ 个元素，每次可以随机选一组拿掉其目前最左边或最右边的元素，问 m 次后，最大拿掉多少。

## 思路

因为每一次都只能去边上的，所以取完后还是一个区间，考虑前缀和。

- $ sum_{i,j} $ 表示第 i 行中前 j 个元素的和。
- $ v_i $ 为第 i 行的物品个数。
- $ f_{i,j} $ 表示第 i 行拿出 j 个元素的最大值。
- $ dp_{i,j} $ 表示前 i 行中拿出 j 个元素的最大值。

易得转移方程 1：$ f_{i,j} = \max(f_{i,j},sum_{i,k}+sum_{i,v_i}-sum_{i,v_i-(j-k)}) $

转移方程 2: $ dp_{i,j} = \max(dp_{i,j},dp_{i-1,j-k}+f_{i,k}) $

i,j,k 需要枚举，总时间复杂度 $ O(n^3) $，足以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快

using namespace std;

const int maxn=110;
int v[maxn],a[maxn][maxn],sum[maxn][maxn*maxn];
int dp[maxn][maxn*maxn],f[maxn][maxn*maxn];

int main(){
	
	int n,m;
	
	scanf("%d %d",&n,&m);
	
	for(int i=1;i<=n;i++){
		scanf("%d",&v[i]);//第 i 行的个数
		for(int j=1;j<=v[i];j++){
			scanf("%d",&a[i][j]);
			sum[i][j]=sum[i][j-1]+a[i][j];//前缀和
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=v[i];j++){
			for(int k=0;k<=j;k++) f[i][j]=max(f[i][j],sum[i][k]+sum[i][v[i]]-sum[i][v[i]-j+k]);//转移1
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=0;k<=min(j,v[i]);k++) dp[i][j]=max(dp[i][j],dp[i-1][j-k]+f[i][k]);//转移2
		}
	}
	
	printf("%d\n",dp[n][m]);
	
	return 0;
}
```


---

## 作者：周子衡 (赞：4)

思路：动态规划

首先，题目规定每次只能取最左边或最右边，那么每次取完之后所剩必然是原来的一个区间（也就是连续的一部分），很容易想到区间$DP$

那么定义状态：$dp[i][j][k][l]$为第$i$层从第$j$个瓶子到第$k$个瓶子，打碎$l$个的最大损坏

显然得到状态转移方程：$dp[i][j][k][l]=max(dp[i][j+1][k][l-1]+v[i][j],dp[i][j][k-1][l-1]+v[i][k])$

（其中$v[i][k]$为第$i$个架子第$k$个物品的价值）

但这样会$MLE$，因为我们最终保留了一些无用状态，其实对于每一层只需要存下从第一个到最后一个的值即可，中间的那些都不必保存

所以每一层共用一个$dp$数组，最后把$dp[i][1][num[i]][1...num[i]]$单独用一个$tmp$数组存起来即可

（其中$num[i]$表示第$i$层物品件数）

最后求答案，用一个$ans$数组，枚举每层打碎几个物品即可

附上代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int num[101]={};
int v[101]={};
int dp[102][102][102]={};
int tmp[101][101]={};
int ans[10001]={};

int main()
{
    int n=0,m=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&num[i]);
        memset(dp,0,sizeof(dp));
        for(int j=1;j<=num[i];j++)
        {
            scanf("%d",&v[j]);
        }
        for(int l=1;l<=num[i];l++)
        {
            for(int j=1;j<=num[i]-l+1;j++)
            {
                int k=j+l-1;
                for(int M=1;M<=l;M++)
                {
                    dp[j][k][M]=max(v[j]+dp[j+1][k][M-1],
                    v[k]+dp[j][k-1][M-1]);
                }
            }
        }
        for(int j=1;j<=num[i];j++)
        {
            tmp[i][j]=dp[1][num[i]][j];
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=0;j--)
        {
            for(int k=min(j,num[i]);k>=1;k--)
            {
                ans[j]=max(ans[j],
                ans[j-k]+tmp[i][k]);
            }
        }
    }
    printf("%d",ans[m]);
    return 0;
}
```

---

## 作者：Max_QAQ (赞：3)

**思路：**

看题目，告诉你了每层的数量和每个物品的价值和生气次数，问你最大的价值。

而且每次只能从选每个柜子的最侧边。

看到范围 $n \leqslant 100\ , k \leqslant 100\ ,\ m \leqslant 10000$ ，可以考虑 dp  。

然后就有了个比较 navie 的想法，就是把每个柜子里的物品数都做个前缀和和反向的前缀和，然后再计算出来砸到这个物品用的次数，将两个值一个变成价值一个变成重量，然后就把这个问题转化成了一个背包了，但很明显选择的时候可能会重复选同一个物品，所以这个方法就不行了。

那我们考虑如何把上面的想法变得正确起来。

既然变成了一个背包，我们的关键又是在如何让他不重复，那么我们不妨把每一层来分开算，将每一层取几个物品的最大值记录下来，然后再用这些值去跑个背包，这样我们就避免了取到同样值的情况了。

时间复杂度是 $O(nmk)$ 。

那接下来写一下转移方程。

**设：** 

$dp_{i,j}$ 表示在第 $i$ 层，取 $j$ 个物品所能获得的最大值。

$L_{i}$ 表示在这一层里前 $i$ 个物品的价值后， $R_{i}$ 表示这一层里从后往前 $i$ 个物品的价值和。

$f_{i,j}$ 表示转移到了第 $i$ 层，已经选了 $j$ 个物品所能获得的最大值。

为了避免在同一层里转移所以我开了两维。

$$dp_{i,j}=\sum\limits_{l+r==j}\max (L_l+R_r)$$

$$f_{i,j}=\sum\limits_{s=0}^{j}\max (f_{i-1,j-s}+dp_{i,s})$$

有了这两个式子就可以进行转移了。

那么答案就是 $f_{n,m}$ ，初值全部为 $0$ 。

最后再贴个代码。

```cpp

#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
inline void write(int x){
	static int sta[42];int top=0;
	if(x<0) putchar('-'),x=-x;
	do{sta[++top]=x%10,x/=10;}while(x);
	while(top) putchar(sta[top--]+'0');
	return ;
}
inline void chkmax(int &x,int y){x=(x>y)?x:y;}
inline void chkmin(int &x,int y){x=(x<y)?x:y;}
int n,m,k[110],cnt;
int f[110][10010],dp[110][110];
int v[110],L[110],R[110];
signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		k[i]=read();
		for(int j=1;j<=k[i];j++) v[j]=read();R[k[i]+1]=0;//记得赋 0 ，因为每层的个数可能不一样。
		for(int l=1,r=k[i];l<=k[i];l++,r--) L[l]=L[l-1]+v[l],R[r]=R[r+1]+v[r];//进行预处理。
		for(int j=1;j<=k[i];j++) for(int l=0,r=k[i]-j+1;l<=j;l++,r++) chkmax(dp[i][j],L[l]+R[r]);//处理出每层的最大值。
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) for(int s=0;s<=min(k[i],j);s++) chkmax(f[i][j],f[i-1][j-s]+dp[i][s]);//背包转移
	write(f[n][m]);
	return 0;//拜拜~~
}

```

---

## 作者：ChrisK (赞：3)

### 前缀和 和 DP

只能取边上的所以看出是前缀和。   
就让$sum[i][j]$表示第$i$行第$j$个之前的前缀和。     
设$h[i][j]$表示第$i$行取$j$个的最大值。     
那么转移就很简单。   
```cpp
h[i][j]=max(h[i][j],sum[i][k]+sum[i][c[i]]-sum[i][c[i]-j+k]);
```
($c[i]$是第$i$行的元素个数)     

单行的解决了，那么如何处理多行的。     
设$f[i][j]$为到第$i$行取了$j$个的最大值。    
那么就可以和上面一样枚举$k$来转移。     
```cpp
f[i][j]=max(f[i][j],f[i-1][j-k]+h[i][k]);
```
全部代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,c[105];
int sum[105][10005],h[105][10005],f[105][10005];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&c[i]);
        sum[i][0]=0;
        for(int j=1;j<=c[i];j++){
            int x;scanf("%d",&x);
            sum[i][j]=sum[i][j-1]+x;
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=c[i];j++)
            for(int k=0;k<=j;k++)
                h[i][j]=max(h[i][j],sum[i][k]+sum[i][c[i]]-sum[i][c[i]-j+k]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int k=0;k<=min(j,c[i]);k++)
                f[i][j]=max(f[i][j],f[i-1][j-k]+h[i][k]);
    printf("%d\n",f[n][m]);
    return 0;
}
```


---

## 作者：demon_yao (赞：2)

### 题目大意
有一个$n$层的柜子，每层有$k$个物品，每个物品有个价值。 有$m$次选择机会，每次可以从任意一层的最左或最右侧拿一个物品，求最大价值。
### 思路
- 由于是每次只能取最左端或最右端，所以我们想到了前缀和$sum[i][j]$表示第$i$行前$j$个的前缀值。

- 显然是分组背包，所以我们设计状态：$f1[i][j]$表示第$i$行取$j$个的最大值。$f2[i][j]$表示前$i$行，第$i$行取$j$个的最大值。

- 接下来考虑状态转移$f1[i][j]=max(f1[i][j],sum[i][kk]+sum[i][k[i]]-sum[i][k[i]-j+kk])$在这之中$k[i]$表示第$i$行有几个值。$j$表示在这一行总共取$j$个。$kk$表示在左边取$kk$个，那么在右边就会取$j-kk$个。那么预处理出$f1$这个数组之后，我们就很容易推出$f2$了。$f2$就是最简单的01背包问题了！$f2[i][j]=max(f2[i][j],f2[i-1][j-l]+f1[i][l]);$其中$l$表示在第$i$行取$l$个。

于是我i们就愉快的A了这道题！qwq
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=1e2+5;
int n,m;int a[N][N],k[N];
long long f1[N][10001],f2[N][10001],sum[N][10001];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		k[i]=read();
		for(int j=1;j<=k[i];j++){a[i][j]=read();sum[i][j]=sum[i][j-1]+a[i][j];}
		
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=k[i];j++)
			for(int kk=0;kk<=j;kk++) f1[i][j]=max(f1[i][j],sum[i][kk]+sum[i][k[i]]-sum[i][k[i]-j+kk]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int l=0;l<=min(j,k[i]);l++) 
				f2[i][j]=max(f2[i][j],f2[i-1][j-l]+f1[i][l]);
	cout<<f2[n][m]; 
	return 0;
}

```


---

## 作者：jdsb (赞：2)

## 题意
有一个 $n$ 层的柜子，每层有 $num_i$ 个物品，每个物品有个价值 $v_{i,j}$，有 $m$ 次选择机会，每次可以从任意一层的最左或最右侧拿一个物品，每个物品只能拿一次，求最大价值。
## 分析
- 每次选择对于不同层的答案是没有影响的，所以可以先对每一层求出选$k$个物品的最大值，然后再考虑 $n$ 层的答案。
- 设 $f[i][j]$ 表示第 $i$ 层选 $j$ 个物品的最大价值，则转移方程为 $f[i][j]=max\{S(i,k,num[i]-j+k)\}(1≤k≤j)$，其中 $S(i,l,r)$ 表示第 $i$ 层取 $[1,l]$ 和 $[r,num[i]]$ 这些数时的价值。
- 设 $dp[i][j]$ 表示前 $i$ 层选 $j$ 个物品的最大价值，则 $dp[i][j]=max\{dp[i-1][j-k]+f[i][k]\}(1≤k≤min(num[i],j))$，来分析一下这个式子，我们枚举第 $i$ 层取 $k$ 个数，则答案此时的答案就为前 $i$ 层取 $j-k$ 个数 的最优解加上这层取 $k$ 个数的最优解。且第 $i$ 层只与第 $i-1$ 层的答案有关,所以第一维可以压掉，但是此时 $j$ 循环就必须从大到小循环，保证能正常覆盖，就跟01背包的思想类似。总的时间复杂度为 $O(nmk)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105,M=1e4+5;
int n,m,num[N],f[N][M],dp[M],v[N][N],sum[N][N];
int S(int i,int l,int r)
{
	return sum[i][l]+sum[i][num[i]]-sum[i][r];
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&num[i]);
		for(int j=1;j<=num[i];j++)
			scanf("%d",&v[i][j]);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=num[i];j++)
			sum[i][j]=sum[i][j-1]+v[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=num[i];j++)
			for(int l=0;l<=j;l++)
			{
				int r=num[i]-j+l;
				f[i][j]=max(f[i][j],S(i,l,r));
			}
	for(int i=1;i<=n;i++)
		for(int j=m;j>=1;j--)
			for(int k=0;k<=min(num[i],j);k++)
				dp[j]=max(dp[j],dp[j-k]+f[i][k]);
	printf("%d\n",dp[m]);
	return 0;
}
```


---

## 作者：_Album_ (赞：1)

更好的阅读：[传送门](https://payphone-x.top/2019/10/29/CF148E/)

------------------------------

## 分析

一道~~毒瘤的~~区间$DP$。

首先，题目中规定只能取边上的物品。因此每次取完之后剩下的必然也是一个区间。

考虑使用前缀和维护。设$sum[i][j]$表示第$i$行中前$j$个物品的价值总和，很容易得到后$k$个物品的价值为$sum[i][num[i] - j]$。其中$num[i]$为第$i$行的物品数量。

之后我们设$dp[i][j]$为在**第**$i$行中拿出$j$个物品的最大价值。易得状态转移方程

$$dp[i][j] = max(dp[i][j] , sum[i][k] + sum[i][num[i]] - sum[i][num[i] - (j - k)])$$

这样我们就可以解决一行了。但是对于多行我们又该怎么办呐？

很简单，我们设$f[i][j]$表示从**前**$i$行中拿出$j$个物品的最大价值。则我们可得状态转移方程

$$f[i][j] = max(f[i][j] , f[i - 1][j - k] + dp[i][k])$$

其中，$i , j , k$需要进行枚举，时间复杂度为$O(n^3)$，足以通过本题。

如果还有什么的话，那就是

**转移时请按照顺序转移，不要随意改变转移顺序**~~(来自考场上随便改变转移顺序而只得了10分的作者)~~

剩下的见代码注释。

--------------------------------------------------

## Code[Accepted]

```Cpp
#include <bits/stdc++.h>

#define ll long long
#define I inline
#define N 101

using namespace std;

int n , m , num[N];

int dp[N][N];   //dp[i][j] 从第i行物品中拿出j个的最大价值
int f[N][10001];    //f[i][j] 从前i行拿出j个物品的最大价值和
int sum[N][N];   //sum[i][j] 第i行前j个物品的价值之和

int a[N][N];

//dp[i][j] = max_element(sum[i][k] + sum[i][n] - sum[i][n - (j - k)])

//f[i][j] = max(f[i][j] , f[i - 1][j - k] + dp[i][k])



int main(){
//	freopen("./porcelain1.in" , "r" , stdin);
    scanf("%d%d" , &n , &m);
    for(int i = 1; i <= n; i ++){
        scanf("%d" , &num[i]);      
        sum[i][0] = 0;
        for(int j = 1; j <= num[i]; j ++){
            scanf("%d" , &a[i][j]);
            sum[i][j] = a[i][j] + sum[i][j - 1];    //计算前缀和
        }
    }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= num[i]; j ++){
            for(int k = 0; k <= j; k ++){   //进行第一遍dp，处理单排情况
                dp[i][j] = max(dp[i][j] , sum[i][k] + sum[i][num[i]] - sum[i][num[i] - j + k]); 
            }
        }
    }
    for(int i = 1;  i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            for(int k = 0; k <= min(j , num[i]); k ++){     //进行第二遍dp，处理多排情况。
                f[i][j] = max(f[i][j] , f[i - 1][j - k] + dp[i][k]);
            }
        }
    }
    printf("%d" , f[n][m]);
    return 0;
}
```

---------------------------------------

# THE END


---

## 作者：_lxy_ (赞：0)

### 题意

略

### 分析

按层处理出来第 $i$ 层扔 $j$ 个物品价值和的最大值，记为 $f_{i,j}$ ，记录每层价值的前缀和和后缀和，枚举左侧扔几个，右侧扔几个，打擂台取最大值即可，$f_{i,l+r}=max \{ pre_{i,l}+suf_{i,k-r+1} \}$。剩下的部分就是一个分组背包板子，枚举每一层扔几个和剩余的空间，直接 dp 即可，假设 $i$ 为层数， $j$ 为剩余空间， $t$ 为第 $i$ 层扔的个数，容易得到 $dp_t=max \{ dp_{j-t}+f_{i,t} \}$ 。最后的答案就是 $dp_m$ 。

### 代码

```cpp
#include <bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int MAXN=107;
const int inf=2139062143;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
	register T1 x=0;register bool f=false;char ch=getchar();
	while(ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch>='0') x=(x*10)+(ch^48),ch=getchar();
	x=(f?-x:x);a=x;qread(b...);
}
template<class T1,class T2>inline T1 qmax(const T1 &x,const T2 &y){return x>y?x:y;}
template<class T1,class T2>inline T1 qmin(const T1 &x,const T2 &y){return x<y?x:y;}
int n,m,a[MAXN][MAXN],k[MAXN];
int pre[MAXN][MAXN],suf[MAXN][MAXN],f[MAXN][MAXN],dp[10007];
int main()
{
	qread(n,m);int i,j,mx=0;
	for(i=1;i<=n;i++)
	{
		qread(k[i]);mx=qmax(mx,k[i]);
		for(j=1;j<=k[i];j++) qread(a[i][j]);
		for(j=1;j<=k[i];j++) pre[i][j]=pre[i][j-1]+a[i][j];
		for(j=k[i];j>=1;j--) suf[i][j]=suf[i][j+1]+a[i][j];
	}
	for(i=1;i<=n;i++)
		for(int l=0;l<=k[i];l++)
			for(int r=0;l+r<=k[i];r++)
				f[i][l+r]=qmax(f[i][l+r],pre[i][l]+suf[i][k[i]-r+1]);
	for(i=1;i<=n;i++)
	{
		for(j=m;j>=0;j--)
		{
			for(int t=1;t<=k[i];t++)
			{
				if(j<t) break;
				dp[j]=qmax(dp[j],dp[j-t]+f[i][t]);
			}
		}
	}
	printf("%d\n",dp[m]);
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

Upd：之前 nt 忘记写时间复杂度，也忘记改格式了，非常抱歉。

## 思路

- ~~dp~~
- ~~再做一次 dp~~

因为发现这道题不太好一次 dp 解决，因此采用两次 dp 来解决，可以让问题变得简单。

首先是第一个 dp。 $dp_{i,j,k}$ 表示第 $i$ 行，一共取 $j$ 个，从左往右取了 $k$ 个。每次的转移很简单，考虑这次砸左边还是右边。左边就是 $dp_{i,j-1,k-1}$ 转移过来，要加上 $a_k$ 的价值；砸右边就是 $dp_{i,j-1,k}$ 转移过来，加上 $a_{K_i-j+k+1}$。其中 $K_i$ 即为每行的物品数量。时间复杂度 $O(n^3)$。转移即为：

$$dp_{i,j,k} = \min(dp_{i,j-1,k-1} + a_k, dp_{i,j-1,k} + a_{K_i - j + k + 1})$$

- dp 要注意考虑 $k=0$ 与 $k=j$ 的时候要单独特判。

为了后续 dp 方便，可以定义 $d$ 数组，$d_{i,j}$ 表示第 $i$ 行砸 $j$ 个砸到的最大值，转移即为：

$$d_{i,j} = \max_{k=0}^{min(j,K_i)} dp_{i,j,k}$$ 

然后第二个 dp 便迎刃而解了。令 $F_{i,j}$ 表示前 $i$ 行砸 $j$ 个时砸掉的最大价值。每次转移考虑当前行砸多少个。枚举 $k$ 是当前这行砸的数量，则转移方程：

$$F_{i,j} = \max_{k=0}^{K_i} F_{i-1,j-k}+dp_{i,k}$$

时间复杂度 $O(n^2m)$。总时间复杂度 $O(n^3 + n^2m)$，即 $O(n^2(n+m))$，可以随便通过此题。


然后这道题大体上就是把一个 dp 解决不了的问题 **转化为两个易于解决的 dp**，这种思想值得我们借鉴。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template <typename T> inline void read(T& x)
{
	x=0;bool f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x; return;
}
template <typename T,typename ...Arg>void read(T& x,Arg& ...arg)
{
	read(x);
	read(arg...);
}
// 省事的快读... 

int dp[105][105][105],d[105][105],f[105][10005];
int a[105][105],K[105];
int main()
{
	int n,m; read(n,m);
	for(int i=1;i<=n;i++)
	{
		read(K[i]);
		for(int j=1;j<=K[i];j++)
			read(a[i][j]);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=K[i];j++)
		{
			for(int k=0;k<=j;k++)
			{
				if(k==0) dp[i][j][k]=dp[i][j-1][k]+a[i][K[i]-j+k+1];
				else if(k==j) dp[i][j][k]=dp[i][j-1][k-1]+a[i][k];
				// 以上为对边界情况的特判 
				else dp[i][j][k]=max(dp[i][j-1][k-1]+a[i][k],dp[i][j-1][k]+a[i][K[i]-j+k+1]);
				// 以上为正经的状态转移 
				d[i][j]=max(d[i][j],dp[i][j][k]);// 方便后续 dp 
			}
		}
	for(int i=1;i<=n;i++)
		for(int j=0;j<=m;j++)
			for(int k=0;k<=min(j,K[i]);k++)
				f[i][j]=max(f[i][j],f[i-1][j-k]+d[i][k]); // 类似背包问题 
	printf("%d",f[n][m]); // 输出 
	return 0;
}
```

$$ \text{\large{———— THE END ————}}$$

$$ \text{\small{Thanks for reading.}} $$

---

## 作者：JWRuixi (赞：0)

细心的 Oler 朋友们会发现这道题其实典藏于“codeforces 2000左右的dp题”中，~~所以直接无脑动规~~，当然还是要分析一下的。

- 题意：

对于每一行能从前后去数，求在 $n$ 行中取 $m$ 个数的最大值。

- 分析：

当 $n=1$ 时：一行中我们可以把 $m$ 当成重量将其转化为一道背包的题。

当 $n>1$ 时：我们可以将一行中的背包动态转移到其他行，转移完全部 $n$ 行后就得到答案了。

- 解法：

设 $f_{i, j}$ 为第 $i$ 行中取 $j$ 个的最大值，设 $g_{i, j}$ 为当前 $i$ 行中取 $j$ 个的最大值，为了实现快速求 $f$ 我们可以用前缀和 $l$ 和后缀和 $r$。

$f_{i,j}=\max\limits_{0\le t\le j}(f_{i,j},l_{t}+r_{j-t})$

$g_{i,j}=\max\limits_{0\le s\le \min(j,k)}(g_{i,j},g_{i-1,s}+f_{i,s})$

- 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace q_wr {
	inline int read() {
		char c = getchar();
		int x = 0, f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (c >= '0' && c <= '9') {
			x = (x << 1) + (x << 3) + c - '0';
			c = getchar();
		}
		return x * f;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace q_wr;
const int maxn = 105;
int n, m, f[maxn][maxn], l[maxn], r[maxn], g[maxn][10005], k;
int main () {
	n = read(), m = read();
	for (int i = 1; i <= n; i++) {
		k = read();
		for (int j = 1; j <= k; j++) l[j] = l[j - 1] + read();//输入中预处理前缀和
		for (int j = 1; j <= k; j++) r[j] = l[k] - l[k - j];//全部减去部分处理后缀和
		for (int j = 1; j <= k; j++) {
			for (int t = 0; t <= j; t++) f[i][j] = max(f[i][j], l[t] + r[j - t]);//处理每一层的最值
		}
		for (int j = 1; j <= m; j++) {
			for (int s = 0; s <= min(j, k); s++)
				g[i][j] = max(g[i][j], g[i - 1][j - s] + f[i][s]);//背包方法求解答案
		}
	}
	write(g[n][m]);
}
```

---

