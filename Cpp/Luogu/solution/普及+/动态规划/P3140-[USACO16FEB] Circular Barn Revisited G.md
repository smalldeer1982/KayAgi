# [USACO16FEB] Circular Barn Revisited G

## 题目描述

在上一次涉及 Farmer John 的圆形谷仓的惨败之后，人们可能会认为他已经吸取了关于非传统建筑的教训。然而，他认为通过允许每间房间进入多头奶牛，仍然可以让他那个圆形谷仓（来自之前的问题）正常运作。回顾一下，谷仓由 $n$ 个房间组成，这些房间顺时针编号为 $1 \ldots n$，围绕谷仓的周边排列（$3 \leq n \leq 100$）。每个房间都有通往两个相邻房间的门，还有一扇门通向谷仓的外部。

Farmer John 希望最终有恰好 $r_i$ 头奶牛进入房间 $i$（$1 \leq r_i \leq 1,000,000$）。为了让奶牛有序地进入谷仓，他计划解锁 $k$ 扇外部门（$1 \leq k \leq 7$），只允许奶牛通过这些门进入。每头奶牛随后顺时针穿过房间，直到到达合适的目的地。Farmer John 希望解锁那些能让他的奶牛在进入谷仓后总共行走的距离最小的外部门（它们最初可以在 $k$ 扇解锁的门外任意排列；这不会计入总距离）。请确定如果他选择最佳的 $k$ 扇门解锁，他的奶牛需要行走的最小总距离。

## 说明/提示

Farmer John 可以解锁门 2 和门 5。11 头奶牛从门 2 进入，总共行走 8 的距离到达房间 2、3 和 4。10 头奶牛从门 5 进入，总共行走 6 的距离到达房间 5、6 和 1。

## 样例 #1

### 输入

```
6 2
2
5
4
2
6
2```

### 输出

```
14```

# 题解

## 作者：曹老师 (赞：6)

**知识点：DP**

~~做法不太好理解 代码中有注释~~

把环转化为在线性时间内做：**rotate(q,q+1,q+n);** ~~手动调试看看~~

状态转移方程：**f[kk][j]=min(f[kk][j],val+f[kk-1][a]);**

**开kk道门开第j个房间其他牛的路程=min(其他房间的牛到j房间的路程+上一次开第a道门花费的路程)**

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#define MAXN 100005
#define LL long long
#define INF 2147483647
#define MOD 1000000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
#define debug(x) cout<<x<<endl;
using namespace std;
const int L=1005;
LL int n,k,q[L],ans=INF,f[10][L];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)
		scanf("%d",&q[i]);
  	for(int i=0;i<n;i++)
  	{
		memset(f,0x3f,sizeof(f));
		f[0][n]=0;
		for(int kk=1;kk<=k;kk++)//当前第几道门
		{
   	  		for(int j=0;j<n;j++)//开第j个房间
		  	{
       			long long val=0;
       			for(int a=j+1;a<=n;a++)//j以后的房间到j花费的总路程 
				{
        			 val+=q[a-1]*(a-j-1);
        			 f[kk][j]=min(f[kk][j],val+f[kk-1][a]);
       			}
     		}
  		}
  		ans=min(ans,f[k][0]);
  		rotate(q,q+1,q+n);//顶元素移到末位置：拆环为链 
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Usada_Pekora (赞：4)

我用的是官方题解中提到的利用分治优化 $O(n^3 k)$ 的暴力程序的做法。优化后复杂度为 $O(n^2k \log n)$ 。

设 $f[i][j]$ 表示到了 $j-1$ 位置一共开了 $i$ 扇门。 $f[0][n]$ 初始化为 $0$ 。（有一维起点隐藏掉了） 。

$f[i][j] = \min { \{ f[i-1][k] + sum_{k,j}\} }$ ，其中 $k$ 是开门的位置。

直接跑显然是不行的，枚举起点、开门数、终点、开门点需要 $O(n^3 k)$ 的复杂度。

如果计算第 $i$ 个门在 $f[i][n/2]$ 中的位置，那么对于 $j<n/2$ 的 $f[i][j]$ 必须在其左侧，对于 $j>n/2$ 的 $f[i][j]$ 必须在其右侧。通过这种方式，我们可以在递归的每个级别平均将搜索空间减半。这样就将复杂度降了一个级别。也就是 $O(n^2k \log n)$ 。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1005, K = 10;
#define INF 0x3fffffffffffffff
int t, n, k;
long long a[N], f[K][N], s[N][N];
inline int pos(int x, int y) {
  return x+y>=n?x+y-n:x+y;
}
inline long long calc(int a, int b) {
  return s[pos(a, t)][pos(b, n - a)];
}
inline void dfs(int k, int x1, int x2, int y1, int y2) {
	if (x1 == x2) return;
	int midx = (x1 + x2) >> 1;
	int midy = -1;
	f[k][midx] = INF;
	for (int j = max(midx + 1, y1); j < y2; j++) {
		long long v = f[k - 1][j] + calc(midx, j);
		if (v < f[k][midx]) {
			midy = j;
			f[k][midx] = v;
		}
	}
	dfs(k, x1, midx, y1, midy + 1);
	dfs(k, midx + 1, x2, midy, y2);
	return;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> k;
	for (int i = n - 1; ~i; i--)  cin >> a[i];
	for (int i = 0; i < n; i++) {
    	long long sum = 0;
		for (int j = 1; j <= n; j++) {
			s[i][j] = s[i][j - 1] + sum;
			sum += a[pos(i, j - 1)];
		}
	}
	memset(f, 63, sizeof(f));
	long long ans = INF;
	f[0][n] = 0;
	for (t = 0; t < n; t++) {
		for (int i = 1; i <= k; i++) dfs(i, 0, n, 1, n + 1);
		ans = min(ans, f[k][0]);
	}
	cout << ans << '\n';
	return 0;
}
```


---

## 作者：喝抹茶的布丁 (赞：4)

这种环的题把环打开变成链应该不难想到，就不多说了。（多说一句：N个元素的环变成的链是a[1]到a[N]再由a[1]到a[N-1]，共2\*N-1个元素。算了一会看代码吧。）


题目中说牛们是顺时针进入的谷仓，可以转换成牛们已经在谷仓中站好了，要逆时针出谷仓，这样递推公式更好求，由于本人一奇怪的癖好，不大喜欢从右往左求dp，所以我是反着读入的，就是不实际上的a[i]存在了a[N-i+1]中，这样在求dp是就是一堆牛在谷仓中从左往右走。（个人认为更好理解，如果你不这样认为，就算了。）


之后就是对花费预处理，imp[i][j]表示从i到j区间中的牛都到j的花费。（有递推性。）


状态转移方程在程序里自己看吧，应该能看懂。。。


代码：



```cpp
#include <bits/stdc++.h>
using namespace std;
int N,K;
int a[210];
long long dp[210][10][210];
//dp[p][i][j]表示以p作为开头处理到j并且一定在j开门，在[p,j]的区间内开了i个门时的最小花费
long long imp[210][210];
//imp[i][j]表示[i,j]区间j处开门的花费
int n;
int main()
{
    scanf("%d%d",&N,&K);
    n=N;
    while(n>0)//反着存
    {
        scanf("%d",&a[n]);
        n--;
    }
    for(int i=N+1;i<2*N;i++)//把环打开
    {
        a[i]=a[i-N];
    }
    for(int j=2*N-1;j>=1;j--)//求imp[i][j]
    {
        for(int i=j;i>=max(j-N,1);i--)
        {
            if(i==j)
            {
                imp[i][j]=0;//在本仓库开门本仓库无花费
            }
            else
            {
                imp[i][j]=imp[i+1][j]+a[i]*(j-i);//利用imp的递推性
            }
        }
    }
    for(int p=1;p<=N;p++)//给dp赋初值
    {
        for(int i=1;i<=K;i++)
        {
            for(int j=p+i-1;j<=p+N-1-K+i;j++)
            {
                dp[p][i][j]=100000000000;
            }
        }
    }
    for(int p=1;p<=N;p++)//就开一个门时花费就是imp[p][j]
    {
        for(int j=p;j<=p+N-1;j++)
        {
            dp[p][1][j]=imp[p][j];
        }
    }
    for(int p=1;p<=N;p++)//枚举起点
    {
        for(int i=2;i<=K;i++)//枚举开门数
        {
            for(int j=p+i-1;j<=p+N-1-K+i;j++)//枚举终点
            {
                for(int x=j-1;x>p+i-2;x--)
                {
                    dp[p][i][j]=min(dp[p][i-1][x]+imp[x+1][j],dp[p][i][j]);//状态转移方程
                }
            }
        }
    }
    long long ans=dp[1][K][N];//找以哪个点作为起点结果最小
    for(int p=2;p<=N;p++)
    {
       ans=min(ans,dp[p][K][N+p-1]);
    }
    printf("%d",ans);
    return 0;
}

```

---

## 作者：qwerty12346 (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/P3140)

## 题意

这题就是求奶牛们走到谷仓的最少路程。

## 思路

直接环形动态规划就行。

## 状态定义

$dp_{j,k}$ 表示开启第 $j$ 个门后一共开启 $k$ 个门的奶牛们走的总路程最小值。

## 状态转移方程

$dp_{j,k}=\min(dp_{l,k-1}+b_{l,j})$，其中 $b_{l,j}$ 表示奶牛们从第 $l$ 个门到第 $j$ 个门的路程总和。最后 $ret=\min(dp_{j,m}+b_{j,i+n})$，因为是环形动态规划，所以最后要加上第一个门到最后一个门的路程和。

## 边界条件

每循环一次就给 dp 数组赋一次初始值，建议用 memset 函数，有不会用的也可以循环赋值。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,ret=INT_MAX,a[100005],b[1005][1005],f[10005][105];//定义dp数组
int main(){
    cin>>n>>m;
    for(long long i=1;i<=n;i++)
    {
	cin>>a[i];
	a[i+n]=a[i];
    }
    for(long long i=1;i<=2*n-1;i++)for(long long j=i+2;j<=min(2*n,i+n);j++)b[i][j]=b[i][j-1]+a[j-1]*(j-i-1);//提前处理
    for(long long i=1;i<=n;i++)
    {
	memset(f,105,sizeof(f));//赋初始值
	f[i][1]=0;
	for(long long j=i+1;j<=i+n-1;j++)
	{
	    for(long long k=2;k<=min(j-i+1,m);k++)for(long long l=i;l<j;l++)f[j][k]=min(f[j][k],f[l][k-1]+b[l][j]);//状态转移方程
	}
	for(long long j=i+m-1;j<=i+n-1;j++)ret=min(ret,f[j][m]+b[j][i+n]);//在加上头和尾的路程求最小值
    }
    cout<<ret;
    return 0;
}
```


---

## 作者：ny_jerry2 (赞：1)

## 题意:
即求满足给定序列所需要的最小总代价。

## 做法:  
### 考虑线性 DP  
 因为仓库是圆形的，即构成了一个环。 
####  所以我们应破环成链。

约定 $m$ 为开门数，即文中给出的 $k$。


## 分析:  
1. 状态定义：$f_{i,k}$：开启第 $i$ 扇门时共开了 $k$ 扇门的最小总路程。

2. 状态计算：$f_{i,k}=\min(f_{j-1,k}+g_{i,j})$  
  其中：$l \le i \le r$，$1 \le k \le m$，$l \le j \le i$  
  
    由于我们破环成链，所以应以 $1 \dots n$ 为开头依次遍历，$l$ 指开头，$r$ 指结尾，$g_{i,j}$ 指由 $i$ 门转移到 $j$ 门的路程和。
       
  为了节省时间复杂度，$g_{i,j}$ 可以预处理。
***

## 时间复杂度:

#### 瓶颈在dp部分。  
以 $1 \dots n$ 为开头依次遍历为 $O(n)$。   
计算 $f_{i,k}$ 为三重循环，时间复杂度为 $O(mn^2)$ 。  
总时间复杂度约为 $O(mn^3)$ 。

注意：不开 long long 见祖宗。 

## 代码
```cpp
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
const int N=210;
int n,m;
int a[N];
int f[N][8],g[N][N];
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        a[i+n]=a[i];
    }
    for(int i=1;i<=2*n;i++){
        int x=0;
        int d=min(i+n-1,2*n);
        for(int j=i+1;j<=d;j++){
            x=x+(j-i)*a[j];
            g[i][j]=x;
        }
    }//预处理g数组
    int ans=1e18;
    for(int l=1;l<=n;l++){//遍历开头
        memset(f,0x3f,sizeof f);
        f[l-1][0]=0;//初始化f数组
        
        int r=l+n-1;
        for(int i=l;i<=r;i++){
            for(int j=1;j<=m;j++){
                for(int k=l;k<i;k++){
                    f[i][j]=min(f[i][j],f[k-1][j-1]+g[k][i]);//状态转移
                }
            }
        }
        ans=min(ans,f[r][m]);
    }
    cout<<ans;
}
```

---

## 作者：tian720 (赞：1)

#### 注：这篇题解的思路较为简单，时间复杂度为 $O(n^3k^2)$，更好的算法请看其它题解。
------------
### 简要题意：
**给你一个环，要求将其分为** $k$ **段，使得每段总路程之和最小（注意：奶牛只能按顺时针方向走）。**

------------
## 思路：
首先观察数据范围，发现 $n \le 100$ 且 $k \le 7$，不难想到可以用~~最暴力且传统的~~**区间DP**来做。于是我们便可以设 $f[i][j][k]$ 为在 $[i,j]$ 区间内安置 $k$ 个门的**最小总路程之和**。

那么可得：
$$f[i][j][k] = \min( f[i][j][k],f[i][x][kk]+f[x+1][j][k-kk]) ( i \le x < j , 1 \le kk < k )。$$

解释：在 $[i,j]$ 区间内开 $ k $ 道门的路程 $ = \min ( $在 $[i,x]$ 区间内开 $kk$ 道门的路程 $+$ 在 $[x+1,j]$ 区间内开 $k-kk$ 道门的路程$)$。

## 初始化：
预处理出所有 $f[i][j][1]$ 的情况，将路程累加，其它的初始化成无穷大。
### C++代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long f[210][210][10],a[210];
int n,K;
int main(){
	cin>>n>>K;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i+n]=a[i];//破环为链 
	}
	memset(f,0x3f3f3f3f,sizeof f);
	for(int l=2;l<=n;l++){
		for(int i=1;i+l-1<=2*n;i++){
			int j=i+l-1;
			f[i][j][1]=0;
			for(int k=i+1;k<=j;k++){
				f[i][j][1]+=(a[k]*(k-i));//路程求和
			}
		}
	}
	for(int l=2;l<=n;l++){
		for(int i=1;i+l-1<=2*n;i++){
			int j=i+l-1;
			for(int k=1;k<=min(l,K);k++){
				for(int xx=i;xx<j;xx++){
					for(int kk=1;kk<=min(xx-i+1,k);kk++){
						f[i][j][k]=min(f[i][j][k],f[i][xx][kk]+f[xx+1][j][k-kk]);
					}
				}
			}
		}
	}
	long long ans=INT_MAX;
	for(int i=1;i+n-1<=2*n;i++)//答案为所有长度为n的区间的最小值 
		ans=min(ans,f[i][i+n-1][K]);
	cout<<ans;
	return 0;
}
```
#### 万望管理员大大通过。

---

## 作者：Alex_Eon (赞：1)

[博客内食用效果更佳](https://www.luogu.com.cn/blog/Ksy/solution-p3140)

思路：环形 DP  
时间复杂度：$O(n^3k)$  

**本题解题目中所给最多能打开的门数量用 $K$ 表示，题解中的 $k$ 均为循环变量。**

设 $F_{i,j}$ 为打开 $i$ 号门后一共打开 $j$ 个门的总路程最小值，得到转移方程：  
$$F_{i,j}=\min\left\{F_{k,j-1}+sum_{k,i}\right\}$$
其中 $k$ 为枚举的在 $i$ 之前最近的打开的门，$sum_{k,i}$ 表示从门 $k$ 转移到 $i$ 所产生的路程和，需要进行预处理。

因为是环形 DP，所以考虑将原数组增长一倍进行，并枚举每一个节点作为第一个打开的门进行 DP，最后统计答案时要加上最后一个门到起点门之间的贡献，即：

$$ans=\min\left\{F_{i,K}+sum_{i,st}\right\}$$
其中 $st$ 为枚举的起点。

代码实现需要注意的地方：
- 因为做了增长，所以预处理 $sum_{i,j}$ 时需要考虑 $i\in\left[n+1,2n-1\right]$ 的情况。
- 枚举 $F_{i,j}$ 时，若 $i$ 到 $st$ 的距离小于 $K$，则 $j$ 无需枚举到 $K$，只需要枚举到 $i-st+1$。
- 每次枚举起点 $st$ 要注意给 $F$ 数组赋初值。
- 需要开 long long。

代码中 $sum_{i,j}$ 保证严格 $i<j$。  
参考代码：
```cpp
#define LL long long
#define UN unsigned
#include<bits/stdc++.h>
using namespace std;

const int N=201;

int n,K;
LL a[N],sum[N][N];

LL ans=INT_MAX,f[N][8];

int main()
{
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		a[i+n]=a[i]; //增长
	}
	
	for(int i=1;i<=2*n-1;i++)
		for(int j=i+2;j<=min(2*n,i+n);j++)//注意边界判断
			sum[i][j]=sum[i][j-1]+a[j-1]*(j-i-1);
	for(int st=1;st<=n;st++)
	{
		memset(f,0x3f,sizeof(f));
		f[st][1]=0;
		for(int i=st+1;i<=st+n-1;i++)
		{
			int temp=min(i-st+1,K);//j 枚举范围
			for(int j=2;j<=temp;j++)
				for(int k=st;k<i;k++)
					f[i][j]=min(f[i][j],f[k][j-1]+sum[k][i]);
		}
		for(int i=st+K-1;i<=st+n-1;i++)
			ans=min(ans,f[i][K]+sum[i][st+n]);//st+n 保证 i<st+n
	}

	printf("%lld",ans);
	return 0;
}
```



---

## 作者：cccgift (赞：1)

# pascal的题解好少……

看到其它的题解都是$O(n^3k)$，下面是$O(n^2k)$算法。

原题题意可以转化一下，把牛安排在$k$个房间里，它们可以逆时针走，使得第$i$个位置有$ri$头牛，求最短总路程。

能想的只有$dp$了。

我们先需要破环为链，这是经典环状$dp$思路。

还有，考虑到最小路程，我们肯定是把一段区间的牛全部集中到区间最左端，这样最优。这样$dp$方程就很好想了。

设$f[i,j]$表示安排$i$个门，前$j$头牛所能产生的最短路程。

则$f[i,j]=min(f[i,j],f[i-1,k]+∑(l-k-1)*r[l])(k+1<=l<=j,0<=k<j)$

把后面的（把$[k+1,j]$的牛集中到第$k+1$个位置）化开，用前缀和，$s1[i]=a[1]+a[2]……a[i]$，$s2[i]=a[2]*(2-1)+……a[i]*(i-1)$。

那么，后面的就变成了$s2[j]-s2[k]-k*(s1[j]-s1[k])$。

忽略$i$，发现这是一个斜率优化的经典形式（如果不知道斜率优化可以去看[浅谈斜率优化](https://www.luogu.org/blog/top-oier/qian-tan-xie-shuai-you-hua)）。

那么，设该一次函数为$y=Kx+b$，则

$K=s1[i]$

$x=j$

$y=s1[j]*j+f[l-1,j]-s2[j]$

$b=f[l,i]-s2[i]$

于是，本题结束，其中状态$O(nk)$，破环为链$O(n)$，状态转移$O(1)$，总的时间复杂度$O(n^2k)$。

代码如下：

```pascal
var f:array[0..7,0..1000] of int64;
    s1,s2,a:array[0..1000] of int64;
    q:array[0..1000] of longint;
    n,k,p,l,r,i,j:longint;
    minn:int64;
function jiao(s,k1,k2:longint):extended; //求斜率
begin
  exit((s1[k1]*k1-s1[k2]*k2+f[s,k1]-f[s,k2]-s2[k1]+s2[k2])/(k1-k2));
end;
procedure dp; //斜率优化dp
var m,i,j:longint;
begin
  for m:=1 to k do
  begin
    f[m,0]:=0;l:=1;r:=1;q[1]:=0;
    for i:=1 to n do
    begin
      while (l<r) and (jiao(m-1,q[l],q[l+1])<=s1[i]) do inc(l);
      j:=q[l];f[m,i]:=f[m-1,j]+s2[i]-s2[j]-j*(s1[i]-s1[j]);
      while (l<r) and (jiao(m-1,i,q[r-1])<=jiao(m-1,q[r-1],q[r])) do dec(r);
      inc(r);q[r]:=i;
    end;
  end;
end;
begin
  minn:=1000000000000000000;
  readln(n,k);
  for i:=1 to n do readln(a[i]);
  for j:=1 to n do //破环为链
  begin
    fillchar(f[0],sizeof(f[0]),127);f[0,0]:=0;
    s1[0]:=0;s2[0]:=0;
    for i:=1 to n do begin s1[i]:=s1[i-1]+a[i];s2[i]:=s2[i-1]+a[i]*(i-1);end;
    //for i:=1 to n do write(s1[i],' ');writeln;
    //for i:=1 to n do write(s2[i],' ');writeln;
    dp;
    if f[k,n]<minn then minn:=f[k,n];
    p:=a[1];for i:=2 to n do a[i-1]:=a[i];a[n]:=p; //转换到下一个链，把第一个放到最后一个
  end;
  writeln(minn);
end.
```

---

## 作者：functionendless (赞：1)

我不知道各位大犇是怎么做的，反正我用的是动规。

复杂度：O（n3+n3×s）

先破环为链，然后用map数组表示i～j要付出的代价

f[i][j]表示前i个开j个门的最小代价

转移方程在代码里了

    
```cpp
#include<cstdio>
#include<cstring>
#define INF 1000000000
#define ll long long
using namespace std;
ll n,s,a[210],ans=INF;
ll map[110][110],f[110][8];
ll min(ll a,ll b) {return a<b?a:b;} 
int main()
{
    int i,j,k,t;
    scanf("%d %d",&n,&s);
    for(i=1;i<=n;i++) { scanf("%d",&a[i]);a[n+i]=a[i];}
    for(t=1;t<=n;t++)
    {
        memset(f,0,sizeof(f));
        memset(map,0,sizeof(map));
        for(i=t;i<=n+t-1;i++)
            for(j=i+1;j<=n+t-1;j++)
                map[i-t+1][j-t+1]=map[i-t+1][j-t]+a[j]*(j-i);
        /*for(i=1;i<=n;i++)
        {
            for(j=i;j<=n;j++)
                printf("%d ",map[i][j]);
            printf("\n");
        }*///调试map
        for(i=1;i<=n;i++) f[i][1]=map[1][i];
        for(i=1;i<=n;i++)
            for(j=2;j<=min(i,s);j++)
            {
                f[i][j]=INF;
                for(k=j;k<i;k++)
                    f[i][j]=min(f[i][j],f[k][j-1]+map[k+1][i]);//方程
            }
        /*for(i=1;i<=n;i++)
        {
            for(j=1;j<=s;j++)
                printf("%d ",f[i][j]);
            printf("\n");
        }printf("\n");*///调试f
        ans=min(ans,f[n][s]);
    }
    printf("%d",ans);
    return 0;
}
```

---

