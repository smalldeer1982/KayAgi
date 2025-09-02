# [POI 2009] KON-Ticket Inspector

## 题目描述

有 $n$ 个车站，现在有一辆火车从 $1$ 到 $n$ 驶过，给出 $a_{i,j}$ 代表从 $i$ 站上车 $j$ 站下车的人的个数。列车行驶过程中你有 $K$ 次检票机会，所有当前在车上的人会被检票，问最多能检多少个不同的人的票。

## 样例 #1

### 输入

```
7 2
2 1 8 2 1 0
3 5 1 0 1
3 1 2 2
3 5 6
3 2
1
```

### 输出

```
2 5
```

# 题解

## 作者：lizhous (赞：12)

# [POI2009]KON-Ticket Inspector 题解
[传送门](https://www.luogu.com.cn/problem/P3486)

## 分析
我们发现有些人可能重复检票，统计十分麻烦，所以正难则反，我们求未被检票的人最少有几个。

设 $f_{i,z}$ 表示在站 $i$ 检票，共检票 $z$ 次的最少未检票人数。枚举上次检票的位置 $la$，答案就是 $f_{la,z-1}$ 加上中间漏掉的人数，即这两个站之间上过并下过车的人数。我们发现时间复杂度已经 $O(n^2k)$，所以求人数需要 $O(1)$。

考虑预处理前缀和，设 $sum_{i,z}$ 表示在站 $i,z$ 之间上过且下过车的人数，放到二维数组中考虑。根据输入，$a_{i,z}$ 表示在 $i$ 上车，$z$ 下车。我们发现他会对 $sum_{j,k}$ 做出贡献，当且仅当 $j\le i$ 且 $k\ge z$，前缀和即可。

细节：在统计时，记得加上这站后上车的人数，他们也检不到票。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define int long long
using namespace std;
int n, k, las[701][101], dp[701][101], a[701][701], fun[701], sum[701][701];
signed main() {
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			scanf("%lld", &a[i][j]);
			sum[i][j] = a[i][j];
		}
	}
    //前缀和
	for (int i = 1; i <= n; i++) {
		for (int z = i + 1; z <= n; z++) {
			sum[i][z] += sum[i][z - 1];
		}
	}
	for (int i = n; i >= 1; i--) {
		for (int z = i + 1; z <= n; z++) {
			sum[i][z] += sum[i + 1][z];
		}
	}
	memset(dp, 127, sizeof(dp));
	for (int i = 1; i <= n; i++) { //当前站点
		dp[i][1] = sum[1][i];
		las[i][1] = -1;
		for (int z = 2; z <= k; z++) { //检票次数
			for (int la = 1; la < i; la++) { //上次检票站
				if (dp[la][z - 1] + sum[la + 1][i] < dp[i][z]) {
					dp[i][z] = dp[la][z - 1] + sum[la + 1][i]; //转移
					las[i][z] = la; //记录上次检票站点
				}
			}
		}
	}
	int ans = 10000000000;
	int it = n, cnt = k;
	for (int i = 1; i <= n; i++) {
		if (dp[i][k] + sum[i + 1][n] < ans) { //统计答案
			it = i;
			ans = dp[i][k] + sum[i + 1][n];
		}
	}
	while (it != -1) { //跳站点
		fun[cnt] = it;
		it = las[it][cnt--];
	}
	for (int i = 1; i <= k; i++) { //倒序输出
		printf("%lld ", fun[i]);
	}
}
```


---

## 作者：huyufeifei (赞：9)

~~趁着没人发题解，我来写一篇。~~

这道题对于我这种蒟蒻来说还是十分困难的。

好了，首先，我们发现这题的输入贼别扭...然后我把每一行前面都加了点空格和一个0，大概就是这样：


    0 2 1 8 2 1 0

      0 3 5 1 0 1
   
        0 3 1 2 2
       
          0 3 5 6
         
            0 3 2
            
              0 1

                0

(先做一个二维前缀和再说。sum[i][j]表示i，j右上角的和，注意不是左上角)

这样就很直观了。我们可以发现，如果在第i个站点检票，就能查到sum[i][i+1]个人。特别的，查一个区域两次是不会累加的。

设计状态：f[i][j][0],f[i][j][1]分别表示前i个站台查票j次时，能查到的最大人数  与  第j次查的站。

记录一个f[i][j][1]是因为状态转移方程要用。

然后我默默的拿出草稿纸推演方程，DP题手写比干想可靠多了。

想了一天的状态转移方程，结果在纸上不到10min就ok了。

f[i][j][0]=max(f[i-1][j][0] , f[j-1......i-1][j-1][0]+sum);

令p=j-1......i-1来循环找最大值

取前者时f[i][j][1]=f[i-1][j][1];

取后者时f[i][j][1]=i;

其中sum=sum[i][i+1]-sum[  f[p][j-1][1]  ][i+1]; 看，这里就用到了f[p][j-1][1]。

然后就得出了我们的最大可查人数。

但是输出很坑，于是我写了个from[i][j]表示前i站查j次结果最大时，j-1次查的站。

然后每次记录一下from就行了。

代码如下，可以看到我的调试语句&我改动的痕迹。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[602][602],sum[602][602];
int f[602][52][2];///0 sum 1 last
int from[602][52];
int main()
{
    int n,k;
    scanf ("%d%d",&n,&k);
    for(int i=1;i<n;i++)
    {
        for(int j=i+1;j<=n;j++)///注意这里的j
        {
            scanf ("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=n;i++)///前缀和
    {
        for(int j=n;j>=1;j--)
        {
            sum[i][j]=sum[i-1][j]+sum[i][j+1]-sum[i-1][j+1]+a[i][j];
        }
    }
    ///
    for(int i=1;i<=n;i++) f[i][1][0]=sum[i][i+1],f[i][1][1]=i;///初始化
    ///
    for(int i=2;i<=n;i++)///前i站
    {
        //printf("i=%d\n",i);
        for(int j=1;j<=i && j<=k;j++)///取j次的话
        {
            //printf("j=%d\n",j);
            int large=-1,largep;
            for(int p=j-1;p<i;p++)///是从p跳过来
            {
                //printf("p=%d\n",p);
                ///large=max(large,(f[p][j-1][0]+(sum[i][i+1]-sum[f[p][j-1][1]][i+1])));
                if(large<(f[p][j-1][0]+(sum[i][i+1]-sum[f[p][j-1][1]][i+1])))///跳
                {
                    large=(f[p][j-1][0]+(sum[i][i+1]-sum[f[p][j-1][1]][i+1]));
                    largep=p;
                }
                //printf("%d+(%d-%d)\n",f[p][j-1][0],sum[i][i+1],sum[f[p][j+1][1]][i+1]);
            }
            if(large>f[i-1][j][0]) f[i][j][0]=large,f[i][j][1]=i,from[i][j]=largep;
            else f[i][j][0]=f[i-1][j][0],f[i][j][1]=f[i-1][j][1],from[i][j]=from[i-1][j];
            //printf("%d %d %d %d  %d\n",i,j,f[i][j][0],f[i][j][1],large);
        }
    }
    ///DP完毕
    ///寻找路径
    int d[52],top=0;
    int p=f[n][k][1];
    for(int i=1;i<=k;i++)
    {
        //printf("%d ",p);
        d[++top]=p;
        p=from[p][k-i+1];
    }
    for(int i=top;i>=1;i--) printf("%d ",d[i]);///输出
    //printf("\n%d",f[n][k][0]);
    return 0;
}
/**
7 2
  2 1 8 2 1 0
    3 5 1 0 1
      3 1 2 2
        3 5 6
          3 2
            1
            */

```

至此，这样一道(对于我这种蒟蒻来说)十分困难的题就AC啦！
（没有优化，大家有兴趣可以自己试一下能不能优化）

---

## 作者：Alex_Wei (赞：8)

> [P3486 [POI2009]KON-Ticket Inspector](https://www.luogu.com.cn/problem/P3486)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/poi/html)。

由于我们只关心上一次检票是在什么时候，考虑设计动态规划状态 $f_{i, j}$ 表示第 $i$ 次检票在第 $j$ 站时最多能够查到多少人的票，转移方程即
$$
f_{i, j} = \max_{k = 0} ^ {j - 1} f_{i - 1, k} + \sum_{k < p \leq j < q} a_{p, q}
$$
这是因为新的被查票的人必须得从第 $k$ 站之后上（否则之前就被查了），在过了第 $j$ 站之后下（否则查不到）。直接做复杂度 $\mathcal{O}(k n ^ 4)$，显然无法接受。

$t$D / $1$D 动态规划通常设计贡献函数 $w$，预处理或推柿子从而快速计算 $w$。设 $w(j, i)$ 表示 $\sum\limits_{j < p \leq i < q} a_{p, q}$，朴素预处理后复杂度变成 $kn ^ 2 + n ^ 4$，仍然无法接受。

考虑更快地预处理：我们没有必要为每个 $w$ 都重新算一遍，可以利用已经算过的结果递推。不难发现 $w(j, i) = w(j + 1, i) + \sum\limits_{q > i} a_{j + 1, q}$，这样即可做到 $n ^ 3$，再加个后缀和优化，预处理就是平方的。因此时间复杂度 $\mathcal{O}(kn ^ 2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int K = 55, N = 600 + 5;
int n, k, a[N][N], b[N][N], c[N][N], f[K][N], tr[K][N];
void print(int k, int p) {
	if(!k) return;
	print(k - 1, tr[k][p]);
	cout << p << " ";
}
int main() {
	cin >> n >> k, memset(f, 0xcf, sizeof(f)), f[0][0] = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) scanf("%d", &a[i][j]);
		for(int j = n; j > i; j--) b[i][j] = b[i][j + 1] + a[i][j];
	} for(int j = n - 1; j; j--)
		for(int i = j; i; i--)
			c[i][j] = c[i + 1][j] + b[i][j + 1];
	for(int i = 1; i <= k + 1; i++)
		for(int j = 1; j <= n; j++)
			for(int p = 0; p < j; p++)
				if(f[i - 1][p] + c[p + 1][j] > f[i][j])
					f[i][j] = f[i - 1][p] + c[p + 1][j], tr[i][j] = p;
	print(k, tr[k + 1][n]);
	return 0;
}
```

---

## 作者：菲斯斯夫斯基 (赞：7)

## P3486 [POI2009] KON-Ticket Inspector 题解

一眼 dp，定义 $dp_{i,j}$ 的含义为第 $i$ 次检票在第 $j$ 站。

分析 $dp_{i,j}$ 如何转移，假设第 $i-1$ 次检票在第 $k$ 站，那么现在要求的就是从第 $k$ 站到第 $j$ 站，可以多检票多少乘客。

我们可以提前预处理，定义 $f_{i,j}$ 为从第 $i$ 站到第 $j$ 站多检票的乘客。不难发现对于乘客的数量来说，有三种情况：

+ 从第 $i$ 站一直坐到了第 $j$ 站都没有下车。

+ 在第 $i$ 站或以前就上了车，但在第 $j$ 站前下车。

+ 在第 $i$ 站以后上了车，并在第 $j$ 站后下车。

显然，我们要求的 $f_{i,j}$ 应该是第 3 种情况。

$f_{i,j}$ 直接三重循环以及前缀和的优化来求就好了，需要注意的是端点的处理：假设乘客在第 $x$ 站上了车，那么在第 $x$ 站检票是可以检到票的；但是如果在第 $x$ 站下了车，在第 $x$ 站是无法检到票的。

因为题目要求的是需要检票的站，所以我们直接在转移的过程中标记一下即可，详见代码及注释。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=610;
int n,k;
int a[N][N],dp[N][N],to[N][N],s[N][N],f[N][N];
stack<int>q;
void dfs(int x,int k)
{
	if(x==0)return ;
	q.push(k);
	dfs(x-1,to[x][k]);
}
signed main()
{
	cin>>n>>k;
	for(int i=1;i<n;i++)
		for(int j=1;j<=n-i;j++)
			cin>>a[i][j],s[i][j]=s[i][j-1]+a[i][j];//前缀和（当然也可以使用后缀和）
	for(int i=1;i<n;i++)
		for(int j=i+1;j<n;j++)
			for(int k=i+1;k<=j;k++)
				f[i][j]+=s[k][n-k]-s[k][j-k];//s[k][j-k]即从第k站上车恰好在第j站下车的人数
	for(int i=1;i<n;i++)
		for(int j=1;j<=i;j++)
			for(int k=1;k<=n-j;k++)
				if(j+k>i)dp[1][i]+=a[j][k];//预处理一开始每个车站能检到票的人数
	for(int i=2;i<=k;i++)
		for(int j=1;j<n;j++)
			for(int k=1;k<j;k++)
				if(dp[i-1][k]+f[k][j]>dp[i][j])
					to[i][j]=k,dp[i][j]=dp[i-1][k]+f[k][j];//转移，同时用to数组进行标记车站编号
	int id=0,ma=0;
	for(int i=1;i<=n;i++)
		if(dp[k][i]>ma)
			ma=dp[k][i],id=i;//找到最大人数并记录编号
	dfs(k,id);//寻找标记
	while(!q.empty())
	{
		cout<<q.top()<<' ';
		q.pop();
	}//利用栈先进后出的性质输出答案
	return 0;
}
```


---

## 作者：破忆 (赞：4)

### 【题目大意】
有n个车站，现在有一辆火车从1到n驶过，给出aij代表从i站上车j站下车的人的个数。列车行驶过程中你有K次检票 机会，所有当前在车上的人会被检票，问最多能检多少个不同的人的票

要求输出检票最多时的检票方案

### 【分析】
这道题很容易想到DP

考虑DP的定义

$f[i][j]$表示前i站检票j次最多能被检票的人数

肯定要在之前枚举一个时间点t

$f[i][j]=max(f[t][j-1]+g[j][i+1])$

其中g[j][i]表示j之后上车,且i时刻能检票的人数

![](https://cdn.luogu.com.cn/upload/image_hosting/710p5vb9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

也就是需要统计$[l,r]$上车，$[r,n]$下车的人数

这样既不会重复，也不会漏掉

2层循环显然要TLE

考虑采用前缀和优化这个式子

![](https://cdn.luogu.com.cn/upload/image_hosting/g2dr6stj.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

还有一层循环，依然容易超时

同理，可以继续优化

![](https://cdn.luogu.com.cn/upload/image_hosting/77uq83pm.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这样就可以线性构造出g数组

```cpp
for(int i=1;i<=n;i++)
for(int j=n;j>i;j--) s[i][j]=s[i][j+1]+a[i][j];
	
for(int i=n;i;i--)
for(int j=1;j<=n;j++) g[i][j]=g[i+1][j]+s[i][j];
```
可以轻松解决最大值的问题

```cpp
for(int i=1;i<=n;i++)
for(int t=1;t<=k;t++)
for(int j=1;j<=i;j++){
	if(f[j-1][t-1]+g[j][i+1]>f[i][t]){
		f[i][t]=f[j-1][t-1]+g[j][i+1];
		lst[i][t]=j-1;
	} 
} 
```
题目要求的是最优方案

那么在DP的同时用$lst[i][j]$记录$f[i][j]$的上个状态

最后从后往前依次扫过答案

倒着输出

```cpp
for(int i=1;i<=n;i++)
if(f[i][k]>f[ans1][k]) ans1=i;
while(ans1) ans[++ans[0]]=ans1,ans1=lst[ans1][k--];
for(int i=ans[0];i;i--) printf("%d ",ans[i]);
```
### 【坑点】

#### 端点是否可取
联系生活实际

上车需要检票

而下车时人已经不在，所以不用考虑

边界需注意

#### 检票越多是否越优

考虑$k$次检票和$k+1$次检票

$k+1$次检票一定要比$k$次检票优

因为多一次检票不可能让总人数更少

所以统计答案时直接用$k$次检票算即可

### 【代码】
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=605,maxk=55;
int n,k;
int f[maxn][maxk],lst[maxn][maxk],ans1,ans2,ans[maxk];
//f[i][j]表示前i站检票j次最多被检票的人数
//f[i][t]=max(f[j][t-1]+g[j+1][i]) 
int a[maxn][maxn];
int s[maxn][maxn],g[maxn][maxn];
//s[l][r]表示l上车，[r,n]下车的人数
//s[i][j]=s[i][j+1]+a[i][j];
//g[l][r]表示[l,r]上车，[r,n]下车的人数 
//g[i][j]=g[i+1][j]+s[i][j];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
// 	freopen("kon.in","r",stdin);
// 	freopen("kon.out","w",stdout);
	n=read(),k=read();
	for(int i=1;i<n;i++)
	for(int j=i+1;j<=n;j++){
		a[i][j]=read();
	}
	
	for(int i=1;i<=n;i++)
	for(int j=n;j>i;j--) s[i][j]=s[i][j+1]+a[i][j];
	
	for(int i=n;i;i--)
	for(int j=1;j<=n;j++) g[i][j]=g[i+1][j]+s[i][j];
	memset(f,128,sizeof f);
	f[0][0]=0;
	for(int i=1;i<=n;i++)
	for(int t=1;t<=k;t++)
	for(int j=1;j<=i;j++){
		if(f[j-1][t-1]+g[j][i+1]>f[i][t]){
			f[i][t]=f[j-1][t-1]+g[j][i+1];
			lst[i][t]=j-1;
		} 
	} 
	
	for(int i=1;i<=n;i++)
	for(int j=1;j<=k;j++)
	if(f[i][j]>f[ans1][ans2]) ans1=i,ans2=j;
	while(ans1) ans[++ans[0]]=ans1,ans1=lst[ans1][ans2--];
	for(int i=ans[0];i;i--) printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：kkxhh (赞：3)

读入时令 **a[i][j]** 为**i**时刻进入**j**时刻离开的人数，然后再从右上到左下做一个前缀和，此时我们可以发现在第**v**时刻检票检到的人数正好是 **sum[v][v+1]** ，于是我们可以利用这个前缀和来转移方程

定义 **d[i][j]** 为第 **i** 次检票在第 **j** 时刻时的最大人数，那么在转移 **d[i][j]** 时我们就需要枚举每一个 **d[i-1][v]** 然后取其中的最大值。那么重复的部分要怎么处理呢？简单地画个图就可以得知当 **d[i][j]** 由 **d[i-1][v]** 转移来时重叠的部分恰好是 **sum[v][j+1]** ,由此我们可以得出状态转移方程 **d[i][j]=max( d[i][j] , d[i-1][v]+sum[j][j+1]-sum[v][j+1] )** 。需要注意的是题目要求输出的是检票的时间，于是我们还需要一个**p**数组来记录每个状态是由哪个状态转移而来的。最后找出最优解倒序输出路径就行了

代码如下

```cpp
#include <cstdio>
using namespace std;

int n,k,a[610][610],d[610][610]={0},p[610][610]={0},sum[610][610]={0},ans=0,s[610]={0};

inline int read(){
    int num=0,k=1; char c=getchar();
    while(c>'9' || c<'0') k=(c=='-')?-1:k,c=getchar();
    while(c>='0' && c<='9') num=(num<<3)+(num<<1)+c-'0',c=getchar();
    return num*k;
}

int main(){
	n=read(); k=read();
	for(int i=1;i<=n;i++)
	    for(int j=i+1;j<=n;j++)
	        a[i][j]=read();
	for(int i=1;i<=n;i++)
	    for(int j=n;j>=1;j--)
	        sum[i][j]=sum[i-1][j]+sum[i][j+1]-sum[i-1][j+1]+a[i][j];
	for(int i=1;i<=k;i++)
	    for(int j=i;j<=n;j++)
	    	for(int v=i-1;v<j;v++)
	    	    if(d[i-1][v]+sum[j][j+1]-sum[v][j+1]>d[i][j]) p[i][j]=v,d[i][j]=d[i-1][v]+sum[j][j+1]-sum[v][j+1];
	for(int i=k;i<=n;i++)
        if(d[k][i]>d[k][ans]) ans=i;
	for(int i=k,j=ans;i>=1;j=p[i][j],i--) s[i]=j;
	for(int i=1;i<=k;i++) printf("%d ",s[i]);
	return 0;
}
```

---

## 作者：大菜鸡fks (赞：3)

第一眼想到网络流。。。费用取负可以跑费用流？？

简单的dp，需要优化，可以用前缀和优化。发现是求矩阵的前缀和。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=605,K=55;
int n,k,a[N][N];
inline void init(){
	n=read(); k=read();
	for (int i=1;i<n;i++){
		for (int j=i+1;j<=n;j++){
			a[i][j]=read();
		}
	}
}
int dp[N][K],pre[N][K],ans,pos,stack[K];
inline void DP(){
	memset(dp,128,sizeof(dp)); dp[0][0]=0;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=k;j++){
			for (int l=0;l<i;l++){
				int temp=a[i][n]-a[i][i]-a[l][n]+a[l][i];
				if (dp[i][j]<dp[l][j-1]+temp){
					dp[i][j]=dp[l][j-1]+temp;
					pre[i][j]=l;
				}
				if (j==k&&ans<dp[i][j]){
					ans=dp[i][j]; 
					pos=i;
				}
			}
		}
	}
	int top=0,now=k;
	for (;pos;pos=pre[pos][now--]){
		stack[++top]=pos;
	}
	for (int i=top;i;i--){
		write(stack[i]); putchar(' ');
	}
}
inline void solve(){
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			a[i][j]+=a[i-1][j];
		}
	}
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			a[i][j]+=a[i][j-1];
		}
	}
	DP();
}
int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：Luke_li (赞：1)

这道题在蓝题中实属比较简单的了，唯一的问题就是题干中缺少了一些关键信息。

我们采用最基本的 DP 完成此题。完全不用正难则反之类的技巧。

## 补全题面

题面中没有提及 _如果有多个答案，输出字典序最小的_。

## 分析题意

首先我们注意到当你在第 $x$ 站检票，所有上车时间在 $x$ 前且下车时间在 $x$ 后的人都会被检票。画到矩阵上就是一个右上角的矩形：

![](https://cdn.luogu.com.cn/upload/image_hosting/6iyu1vf5.png)

这张图展示的是在 2 号站检票能检到的范围。

这种形状是很好去重的。如果你检重了一拨人，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/nny7c50d.png)

你会发现你可以把绿色的在红色的边缘处截断，这样就不会重复统计右上角 $2\times 3$ 的矩形内的人了。

更进一步地，矩形求和可以用前缀和优化。

那么我们就有底气做这个 DP 了。

## 状态设计

我们令 $f_{i,j}$ 表示最后一次检票恰好在 $i$ 位置，**最多** 用了 $j$ 次检票机会能检票到的人的总数。

根据定义，初始值全部设置为 $0$ 就可以了。

## 转移方程

由于 $n$ 很小，我们直接枚举上一次检票的位置 $l$。

由于上一次检票会覆盖上车时间在 $l$ 以前的点，我们就要把本次检票的人在 $l$ 的位置截断，也就是只统计上车时间在 $[l+1,i]$ 内的，下车时间在 $[i+1,n]$ 之间的人。

我们找到最优的的 $l$ 中 **最靠前的**，从它转移。

我们从右上角开始做一个前缀和，这样就能维护右上角的矩形的权值和。需要截断的时候，把截断的部分减去即可。

我们的最大值就储存在每个 $i\in[1,n]$ 的 $f_{i,k}$ 中。

如何维护方案呢？这是一个经典的 Trick：对每个状态保存它从哪里转移而来（这里我们只需保存它从哪个 $l$ 转移而来即可）。我们找到最大值之后不断往前跳直到没有上一个转移了（或者说从 $0$ 号站转移而来），再倒着输出即可。

## 额外处理

我们还差临门一脚。如果我们的最优解使用的检票次数不足 $k$（例如有很多位置是 $0$，我们没有管它们）就要补上一些。我们只需找出没有检票的字典序最小的那几个就可以了。

考虑 **字典序最小** 的要求。为什么我们取最后一次检票位置最小的答案就是字典序最小的呢？反证法：假如有一个答案的字典序比你选择的更小（称之为 $B$），那么在你选择的答案序列（称之为 $A$）中，一定存在一个位置 $p$，使得 $A_p>B_p,A_{p+1}\le B_{p+1}$，此时将 $A_p$ 调整为 $B_p$ 一定不劣。而我们的转移中选的是 **最靠前的** $l$，绝不可能出现这种情况。综上，我们证明了此做法得出的是字典序最小的答案序列。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=600+10;
ll n,k;
ll a[N][N],s[N][N],dp[N][N],from[N][N];
bool vis[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(ll i=1;i<=n;i++)
	{
		for(ll j=i+1;j<=n;j++)
			cin>>a[i][j];
	}
    //前缀和
	for(ll i=1;i<=n;i++)
	{
		for(ll j=n;j>=1;j--)
			s[i][j]=s[i-1][j]+s[i][j+1]-s[i-1][j+1]+a[i][j];
	}
    //DP主体
	for(ll i=1;i<=n;i++)
	{
		for(ll j=1;j<=k;j++)
		{
			for(ll l=0;l<i;l++)
			{
				if(dp[l][j-1]+s[i][i+1]-s[l][i+1]>dp[i][j])
				{
					dp[i][j]=dp[l][j-1]+s[i][i+1]-s[l][i+1];
					from[i][j]=l;
				}
			}
		}
	}
    //找到最大值
	ll pos1=0,pos2=0;
	for(ll i=1;i<=n;i++)
	{
		for(ll j=0;j<=k;j++)
		{
			if(dp[i][j]>dp[pos1][pos2])
			{
				pos1=i;
				pos2=j;
			}
		}
	}
    //回溯
	stack<ll> st;
	while(pos1)
	{
		st.push(pos1);
		pos1=from[pos1][pos2];
		pos2--;
	}
	ll cnt=0;
	while(!st.empty())
	{
		cnt++;
		vis[st.top()]=1;
		st.pop();
	}
    //补全到 k
	for(ll i=1;i<=n && cnt<k;i++)
		if(!vis[i])
		{
			vis[i]=1;
			cnt++;
		}
	for(ll i=1;i<=n;i++)
		if(vis[i])
			cout<<i<<" ";
	return 0;
}
```

---

## 作者：ademik (赞：1)

#### 分析:

对于这个问题，我们只关心哪些新上车的人(在上一次检票还没有上车，此次检票前还没有下车的人数)。我们令 $a(i, j)$ 表示在 站点 $i$ 上车，站点 $j$ 下车的人数。我们要求的在 $j$ 到 $i$ 站点间新上车的人数 $w(i, j) = \sum\limits_{x = j + 1}^{i}\sum\limits_{y = i + 1}^{n}a(x, y)$。

如果想到要存储上一次检票的位置，那么 DP 方程状态的定义 和 转移就很容易了。我们令 $dp(i, j, k)$ 表示当前位于站点 $i$，上一次检票位于 站点 $j$，已经有 $k$ 次检票。我们可以直接省略第一维，转移方程即为
$$dp(i, k) = \max\limits_{j = 0}^{i - 1} dp(j, k - 1) + w(i, j)$$

即在 $i$ 位置检票可获得的最大人数。

现在考虑如何快速计算 $w(i, j)$。
$$w(i, j) = \sum\limits_{x = j + 1}^{i}\sum\limits_{y = i + 1}^{n}a(x, y) = \sum\limits_{x = j + 1}^{n}\sum\limits_{y = i + 1}^{n}a(x, y) - \sum\limits_{x = i + 1}^{n}\sum\limits_{y = i + 1}^{n}a(x, y)$$

故而考虑预处理出二维前缀和计算即可。

总时间复杂度为 $O(n^2 k)$。

#### Code:

```cpp
# include <bits/stdc++.h>
# define TIME 1e3 * clock() / CLOCKS_PER_SEC
# define debug(x) cerr <<x <<" ";
using namespace std;
typedef long long i64;
const int N = 605;
int n, ki, cnt;
int dp[N][51], a[N][N], qz[N][N], pre[N][51];
bool vis[N];
void print(int x, int k)
{
	if(ki == 1) return;
	if(pre[x][k]) print(pre[x][k], k - 1);
    if(x != 0) {
        vis[x] = true; cnt ++;
    }
}
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >>n >>ki;
    for(int i = 1; i <= n; i ++) {
        for(int j = i + 1; j <= n; j ++) {
            cin >>a[i][j];
        }
    }
    for(int i = 1; i <= n; i ++) {
        for(int j = n; j >= i + 1; j --) {
            qz[i][j] = qz[i - 1][j] + qz[i][j + 1] - qz[i - 1][j + 1] + a[i][j];
        }
    }
    for(int i = 1; i <= n; i ++) {
        for(int j = 0; j < i; j ++) {
            for(int k = 1; k <= min(i, ki); k ++) {
                //dp[i][k] = max({dp[i][k], dp[i][k], dp[j][k - 1] + qz[i][i + 1] - qz[j][i + 1]});
                if(dp[i][k] < dp[j][k - 1] + qz[i][i + 1] - qz[j][i + 1]) {
                    dp[i][k] = dp[j][k - 1] + qz[i][i + 1] - qz[j][i + 1];
                    pre[i][k] = j;
			    }
            } 
        }
    }
    int pos = 0;
    for(int i = 1; i <= n; i ++) {
    	if(dp[pos][ki] < dp[i][ki]) pos = i;
	}
    print(pos, ki);
    cnt = ki - cnt;
    for(int i = 1; i <= n; i ++) {
        if(vis[i]) {
            cout <<i <<" ";
            continue;
        }
        if(cnt) {
            cout <<i <<" ";
            cnt --;
        }
    }
    return 0;
}
```

---

## 作者：Haoyue_06432 (赞：1)

看到这个奇怪的数据第一步，

首先整理数据：

经过递进分析，每层增加人数都由前面转移增加，应该是线性动态规划，如果用动态规划做的话，先分析 $dp$ 数组含义：

**定义 $dp$ 数组含义为经过第 $i$ 站点后检票 $j$ 次能检到的最多不同人数。**

根据 $dp$ 数组含义，分析能从什么情况转移到当前状态，有两种状态，分别是过了当前站点后检票和不检票两种情况。

那么动态转移方程为：

**前面 $1$ 到 $i-1$ 个站点检票 $j$ 次的最多不同人数和前面 $1$ 到 $i-1$ 个站点检票 $j-1$ 次的最多不同人数加现在检票新增的不同人数的最大值。**

说人话：

$dp_{i,j}=\max(dp_{k,j},dp_{k,j-1}+sum)$

$k$ 取 $1$ 到 $i-1$，$sum$ 为检票新增的不同人数。

那如何求现在检票新增的不同人数呢？

首先，当我们在 $x$ 站点检票后前 $1$ 到 $x$ 行的上下车人数就可以不用看了，因为在 $x$ 检票时已经将前面所有不同人个数算过了，后面再检票我们可以直接跳过前 $x$ 行的数据。

所以，现在检票新增的不同人数实际上是第 $x+1$ 站到第 $i$ 站上车并在 $i$ 站之后下车的人数，如图：

这样，新增的不同人数实际上就是图中矩形所有的数之和。

但是直接暴力的话就变成 $5$ 重循环，时间复杂度直接拉满，导致作者一开始直接 $60$ TLE，于是就要用前缀和来优化。

那么如何用前缀和算出矩阵数字和呢？

**首先定义 $sum$ 为第 $i$ 站上车到第 $j$ 站下车中的所有上车不同的总人数。（这个好理解）**

**$ans$ 为在 $i$ 站检票前 $j$ 站的新增并会一直持续到 $i$ 站不下车的不同总人数。**

举例：

$ans_{5,5}$ 为上图第 $1$ 行到第 $5$ 行，第 $6$ 列到第 $7$ 列的新增不同总人数。

$ans_{5,2}$ 为上图第 $1$ 行到第 $2$ 行，第 $6$ 列到第 $7$ 列的新增不同总人数。

那么第二次检票新增人数为 $ans_{5,5}-ans_{5,2}$。

那么 dp 部分就彻底完成了，接下来是储存路径。

直接用结构体的话时间慢，加上本身代码是 $3$ 重循环，导致作者即使前缀和优化后也只是 $70$ TLE qwq，那么只能用数组了。

如何用数组存路径？直接存 $3$ 维会直接爆掉，那么我们可以想一下数组转移。

定义结构体数组 $b$ 为经过第 $i$ 站后检票 $j$ 次的上一次检票（当前检票不算）是在第几站，当时检了几次票，再判断现在是否检票了。

这样，最后就可以通过函数递归找到先前的所有路径，最后再判断最后一个站点本身有无检票就能将路径全部输出了。

就当作者再次将优化代码交上去后，好消息，没有 TLE 了，坏消息，$90$ WA 了。于是作者检查啊检查，甚至一度怀疑是做法问题，看到了讨论区：

**对答案有贡献的站点数目可能小于 $m$，这时候你就需要从剩下的站点中，选择一些字典序较小的来输出。**

寄，终于改对了 qwq，以后可要警醒自己谨防坑点了。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct site
{
	ll i,j;
	bool bj;
}b[660][660],x;
ll n,m,a[660][660],dp[660][55],sum[660][660],ans[660][660],s[660],k;
void print(site x)
{
	if(x.i==0)return;
	print(b[x.i][x.j]);
	s[++k]=x.i;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			cin>>a[i][j];
			sum[i][j]+=a[i][j]+sum[i][j-1];
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			ans[i][j]+=ans[i][j-1]+sum[j][n]-sum[j][i];
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			for(int k=0;k<i;k++)
			{
				if(dp[k][j]>=dp[i][j])
				{
					dp[i][j]=dp[k][j];
					if(b[k][j].bj==true)
					{
						b[i][j].i=k;
						b[i][j].j=j;				
					}
					else b[i][j]=b[k][j];
					b[i][j].bj=false;
				}
				if(k==0)
				{
					if(dp[0][j-1]+ans[i][i]>dp[i][j])
					{
						dp[i][j]=dp[0][j-1]+ans[i][i];
						b[i][j].i=0;b[i][j].j=0; 
						b[i][j].bj=true;
					}
				}
				else
				{
					if(dp[k][j-1]+ans[i][i]-ans[i][k]>dp[i][j])
					{
						dp[i][j]=dp[k][j-1]+ans[i][i]-ans[i][k];
						b[i][j].i=k;b[i][j].j=j-1;
						b[i][j].bj=true;
					}
				}				
			}
		}
	}
	print(b[n-1][m]);if(b[n-1][m].bj==true)s[++k]=n-1;
	if(m==k)for(int i=1;i<=k;i++)cout<<s[i]<<" ";
	else
	{
		while(m>k)
		{
			for(int i=1;i<=n;i++)
			{
				bool bj=false;
				for(int j=1;j<=k;j++)
					if(i==s[j])
					{
						bj=true;
						break;	
					}
				if(bj==false)s[++k]=i;
				if(k==m)break;
			}
		}
		sort(s+1,s+1+m);
		for(int i=1;i<=m;i++)cout<<s[i]<<" ";
	}
	return 0;
}
```


---

## 作者：wei2013 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P3486)

## 思路：
~~显然是 dp~~

如果直接按题目进行 dp 的话感觉不太好做，~~我不会~~。

既然是要求最大检票当然可以转化为最小未检票。

那么，可列状态 $dp_{i,j}$ 表示第 $j$ 次检票在 $i$ 站检票的最小未检票人数。

所以转移为：

$$dp_{i,j}=\min{dp_{k,j-1}+x} $$

声明：$k$ 表示 $j-1$ 次检票的站点，$x$ 表示从 $k+1$ 到 $i$ 的车上人数。

$x$ 显然可以用前缀和优化，复杂度 $\mathcal{O(n^2k)}$。

最后记录路径输出即可。

注意：求的是未检票人数。
## code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=605,MAXK=55;
int n,k,dp[MAXN][MAXK],a[MAXN][MAXN],p[MAXN][MAXN],lst[MAXN][MAXK],path[MAXK];
signed main(){
	cin>>n>>k;
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			cin>>a[i][j];
			p[i][j]=a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			p[i][j]+=p[i][j-1];
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=i+1;j<=n;j++){
			p[i][j]+=p[i+1][j];
		}
	}
	for(int i=1;i<=n;i++){
		dp[i][1]=p[1][i];
		for(int j=2;j<=k;j++){
			for(int k=1;k<i;k++){
				if(dp[k][j-1]+p[k+1][i]<dp[i][j]){
					dp[i][j]=dp[k][j-1]+p[k+1][i];
					lst[i][j]=k;
				}
			}
		}
	}
	int ans=1e18,p1=0,tot=k;
	for(int i=1;i<=n;i++){
		if(dp[i][k]+p[i+1][n]<ans){
			ans=dp[i][k]+p[i+1][n];
			p1=i;
		}
	}
	while(p1){
		path[tot]=p1;
		p1=lst[p1][tot--];
	}
	for(int i=1;i<=k;i++){
		cout<<path[i]<<" ";
	}
	return 0;
} 
```

---

## 作者：chenruikai (赞：0)

### 题意
不用多说，但是需要注意检票是在某站后，这一点看似平平无奇，实则关乎程序细节。
### 解
从数据范围上来看，应该是一道动态规划。忽略一些细节，可以很快的写出递推式。设 $f(a,b)$ 为 $[0,a]$ 站内最后一站 $a$ 在**过后**检票且检票次数为 $b$ 次时检查的最多不同人数。
$$
f(a,b)=\max_{0\le i<a}(f(i,b-1)+peo_{new}(i+1,a))\\
f(a,1)=peo_{new}(0,a)
$$
$peo_{new}(l,r)$ 是表示会被统计到的新人。

首先思考 $peo_{new}$ 怎么求。显而易见，一个人会被统计到当且仅当他上车到他下车之间有一次以上被检票。但为了防止情况重复，我们强制要求这个人只有在第一次被统计到时才作数，也就是说，设上下车在第 $x,y$ 站，在 $l,r$ 这两个车站间统计，要满足 $l\le x\le r$ 且 $y>r$ 才会被新统计一次。

由此可以搞出初步代码。这个代码是有问题的。
```cpp
/*
f(a , b) => sta[0<=<=a]{sta[a] check} , use times = b , most peo;
f(a , b) = max(f(i , b - 1) + peo{i<<=a up && a< down}.num)
base case{f(-1 , ...) = 0;}

cal peo
{
    tree array : up += peo , down -= peo;
    ask = sumof(i , a);
}
*/
#include <bits/stdc++.h>
using namespace std;

int stanum , chanum;
int peonum[600][600] , mem[600][2] , be[600][51];
int getpeo(int frompos , int endpos)
{
    int res = 0;
    for(int i = frompos;i <= endpos;i++)
        for(int j = endpos + 1;j < stanum;j++)
            res += peonum[i][j];
    return res;
}
int main()
{
    cin >> stanum >> chanum;
    for(int i = 0;i < stanum;i++)
        for(int j = i + 1;j < stanum;j++)
            scanf("%d" , &peonum[i][j]);
    int a;
    // for(int i = 0;i < stanum;i++)
    //     for(int j = i + 1;j < stanum;j++)
    //     {
    //         scanf("%d" , &a);
    //         add(i , a);add(j , -a);
    //     }
    for(int sta = 0;sta < stanum;sta++)
        mem[sta][1] = getpeo(0 , sta);
    for(int times = 2;times <= chanum;times++)
    {
        // mem[0][times & 1] = getpeo(0 , 0);
        // printf("sta = %d , cha = %d , res = %d\n" , 
        //     0 , times , mem[0][times & 1]);
        for(int sta = 0;sta < stanum;sta++)
        {
            mem[sta][times & 1] = 0;
            // for(int i = 0;i < sta;i++)
            //     mem[sta][times & 1] = max(mem[sta][times & 1] , 
            //         mem[i][1 - (times & 1)] + sumof(i , sta));
            for(int i = 0;i < sta;i++)
            {
                // a = mem[i][1 - (times & 1)] + sumof(i , sta);
                a = mem[i][1 - (times & 1)] + getpeo(i + 1 , sta);
                if(mem[sta][times & 1] < a)
                    mem[sta][times & 1] = a , be[sta][times] = i;
            }
            // printf("sta = %d , cha = %d , res = %d\n" , 
            //     sta , times , mem[sta][times & 1]);
        }
    }
    a = 0;
    for(int i = 1;i < stanum;i++)
        if(mem[i][chanum & 1] > mem[a][chanum & 1])a = i;
    // cout << mem[a][chanum & 1] << '\n';
    stack <int> res;
    for(int i = chanum;i > 0;i--)
    {
        res.push(a);
        a = be[a][i];
    }
    for(;!res.empty();res.pop())cout << res.top() + 1 << ' ';
    puts("");
    return 0;
}
```
时间 4.88s，空间 1.88MB.

就那么暴力，甚至都有 60 分。

再思索一下，为什么会超时。可以发现，很多时间都耗在了获取新统计的人数 $getpeo$ 上。仔细一看，发现每次都会对 $peonum$ 做一次向后求和，于是，取我后缀数组来。

交上去后，超时变蛙叫。仔细一看，忘记特判。
```cpp
/*
f(a , b) => sta[0<=<=a]{sta[a] check} , use times = b , most peo;
f(a , b) = max(f(i , b - 1) + peo{i<<=a up && a< down}.num)
base case{f(-1 , ...) = 0;}

cal peo
{
    tree array : up += peo , down -= peo;
    ask = sumof(i , a);
}
*/
#include <bits/stdc++.h>
using namespace std;

int stanum , chanum;
int peonum[600][600] , mem[600][2] , be[600][51];
int getpeo(int frompos , int endpos)
{
    int res = 0;
    // for(int i = frompos;i <= endpos;i++)
    //     for(int j = endpos + 1;j < stanum;j++)
    //         res += peonum[i][j];
    if(endpos == stanum - 1)return 0;//Here I forget to judge before.
    for(int i = frompos;i <= endpos;i++)
        res += peonum[i][endpos + 1];
    return res;
}
int main()
{
    cin >> stanum >> chanum;
    for(int i = 0;i < stanum;i++)
    {
        for(int j = i + 1;j < stanum;j++)
            scanf("%d" , &peonum[i][j]);
        for(int j = stanum - 2;j >= 0;j--)
            peonum[i][j] += peonum[i][j + 1];
    }
    int a;
    for(int sta = 0;sta < stanum;sta++)
        mem[sta][1] = getpeo(0 , sta);
    for(int times = 2;times <= chanum;times++)
    {
        for(int sta = 0;sta < stanum;sta++)
        {
            mem[sta][times & 1] = 0;
            for(int i = 0;i < sta;i++)
            {
                a = mem[i][1 - (times & 1)] + getpeo(i + 1 , sta);
                if(mem[sta][times & 1] < a)
                    mem[sta][times & 1] = a , be[sta][times] = i;
            }
        }
    }
    a = 0;
    for(int i = 1;i < stanum;i++)
        if(mem[i][chanum & 1] > mem[a][chanum & 1])a = i;
    stack <int> res;
    for(int i = chanum;i > 0;i--)
    {
        res.push(a);
        a = be[a][i];
    }
    for(;!res.empty();res.pop())cout << res.top() + 1 << ' ';
    puts("");
    return 0;
}
```
时间 2.77s，空间 2.02MB.

虽然此时已经满分~~就这~~但是人生不止眼前的苟且，还有~~天边的苟且~~更低的复杂度。观察代码，发现函数 $getpeo$ 的自变量取值范围不大，但却用了很多次，于是使用预处理。
```cpp
/*
f(a , b) => sta[0<=<=a]{sta[a] check} , use times = b , most peo;
f(a , b) = max(f(i , b - 1) + peo{i<<=a up && a< down}.num)
base case{f(-1 , ...) = 0;}

cal peo
{
    tree array : up += peo , down -= peo;
    ask = sumof(i , a);
}
*/
#include <bits/stdc++.h>
using namespace std;

int stanum , chanum , a;
int peonum[600][600] , mem[600][2] , be[600][51] , mem_peo[600][600];
int getpeo(int frompos , int endpos)
{
    if(endpos == stanum - 1)return 0;
    int res = 0;
    for(int i = frompos;i <= endpos;i++)
        res += peonum[i][endpos + 1];
    return res;
}
int main()
{
    cin >> stanum >> chanum;
    for(int i = 0;i < stanum;i++)
    {
        for(int j = i + 1;j < stanum;j++)
            scanf("%d" , &peonum[i][j]);
        for(int j = stanum - 2;j >= i + 1;j--)
            peonum[i][j] += peonum[i][j + 1];
    }
    for(int frompos = 0;frompos < stanum;frompos++)
        for(int endpos = frompos;endpos < stanum;endpos++)
            mem_peo[frompos][endpos] = getpeo(frompos , endpos);
    for(int sta = 0;sta < stanum;sta++)
        mem[sta][1] = getpeo(0 , sta);
    for(int times = 2;times <= chanum;times++)
    {
        for(int sta = 0;sta < stanum;sta++)
        {
            mem[sta][times & 1] = 0;
            for(int i = 0;i < sta;i++)
            {
                // a = mem[i][1 - (times & 1)] + getpeo(i + 1 , sta);
                a = mem[i][1 - (times & 1)] + mem_peo[i + 1][sta];
                if(mem[sta][times & 1] < a)
                    mem[sta][times & 1] = a , be[sta][times] = i;
            }
        }
    }
    a = 0;
    for(int i = 1;i < stanum;i++)
        if(mem[i][chanum & 1] > mem[a][chanum & 1])a = i;
    stack <int> res;
    for(int i = chanum;i > 0;i--)
    {
        res.push(a);
        a = be[a][i];
    }
    for(;!res.empty();res.pop())cout << res.top() + 1 << ' ';
    puts("");
    return 0;
}
```
把 $getpeo$ 结果存到了 $mem\_peo$ 中。

时间 184ms，空间 3.29MB.

即便已经差不多了，但是我们发现还可以再优化。$getpeo$ 实际上是对数组中的某一块矩形进行了求和，于是实现 $\theta(1)$ 求出 $getpeo$。另外，$mem$ 只用一维就够，可模仿背包。
```cpp
/*
f(a , b) => sta[0<=<=a]{sta[a] check} , use times = b , most peo;
f(a , b) = max(f(i , b - 1) + peo{i<<=a up && a< down}.num)
base case{f(-1 , ...) = 0;}
*/
#include <bits/stdc++.h>
using namespace std;

int stanum , chanum , a;
int peonum[600][600] , mem[600] , be[600][51] , mem_peo[600][600];
int main()
{
    scanf("%d%d" , &stanum , &chanum);
    for(int i = 0;i < stanum;i++)
    {
        for(int j = i + 1;j < stanum;j++)
            scanf("%d" , &peonum[i][j]);
        for(int j = stanum - 2;j >= i + 1;j--)
            peonum[i][j] += peonum[i][j + 1];
    }
    for(int i = stanum - 1;i >= 0;i--)
        for(int j = i + 1;j < stanum;j++)
            peonum[i][j] += peonum[i + 1][j];
    for(int frompos = 0;frompos < stanum;frompos++)
        for(int endpos = frompos;endpos < stanum;endpos++)
            mem_peo[frompos][endpos] = (endpos == stanum - 1 ? 
                peonum[frompos][endpos + 1] : 
                peonum[frompos][endpos + 1] - peonum[endpos + 1][endpos + 1]);
    for(int sta = 0;sta < stanum;sta++)
        mem[sta] = mem_peo[0][sta];
    for(int times = 2;times <= chanum;times++)
    {
        for(int sta = stanum - 1;sta >= 0;sta--)
        {
            mem[sta] = 0;
            for(int i = 0;i < sta;i++)
            {
                a = mem[i] + mem_peo[i + 1][sta];
                if(mem[sta] < a)
                    mem[sta] = a , be[sta][times] = i;
            }
        }
    }
    a = 0;
    for(int i = 1;i < stanum;i++)
        if(mem[i] > mem[a])a = i;
    stack <int> res;
    for(int i = chanum;i > 0;i--)
    {
        res.push(a);
        a = be[a][i];
    }
    for(;!res.empty();res.pop())cout << res.top() + 1 << ' ';
    puts("");
    return 0;
}
```
时间 123ms，空间 3.29MB.

玥玥月月如今朝。

---

