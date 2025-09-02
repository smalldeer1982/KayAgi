# 切蛋糕 Cake slicing

## 题目描述

翻译：有一个n行m列(1<=n,m<=20)的网络蛋糕上有k个樱桃。每次可以用一刀沿着网络线把蛋糕切成两块，并且只能够直切不能拐弯。要求最后每一块蛋糕上恰好有一个樱桃，且切割线总长度最小。

# 题解

## 作者：ygsldr (赞：9)

图的size很小，所以第一眼觉得是dp

想了想状态并不难定义，用四维来表示一个状态：
```cpp
	dp[lx][ly][rx][ry] = 该范围内切割线的最小值
    嗯用四维状态表示一个矩形
```

怎么转移呢，我们可以枚举每一条割线，那么有:

```cpp
	dp[lx][ly][rx][ry] = min(
    dp[lx][ly][cutx][ry] + dp[cutx + 1][ly][rx][ry] + ry - ly + 1,
    dp[lx][ly][rx][cuty] + dp[lx][cuty + 1][rx][ry] + rx - lx + 1
    )
    
    cutx和cuty分别是纵向切和横向切
```

边界条件：
```cpp
	假如里面没有樱桃，返回inf，因为不符合题意
    假如里面有且仅有1颗樱桃，返回0
    这就需要快速计算一个区域内樱桃数量
    二维前缀和嘛
```

时间复杂度：

```cpp
总共有n^2*m^2个状态，有n+m种转移方式，所以：
O(n,m) = n^2*m^2*(n+m)
```
说实话觉得很慢了，但想不到其他方法

还有就是，多样例一定要初始化！！！！

参考代码：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int dp[30][30][30][30];
int sum[30][30];
bool mp[30][30];
int n,m,k;
const int inf = 11234567;
inline int br_num(int lx,int ly,int rx,int ry)
{
    return sum[rx][ry] - sum[rx][ly-1] - sum[lx-1][ry] + sum[lx-1][ly-1];
}
int DP(int lx,int ly,int rx,int ry)
{
    int t = br_num(lx,ly,rx,ry);
    if(t == 1)return 0;
    if(t == 0)return inf;
    int &d = dp[lx][ly][rx][ry];
    if(d != inf)return d;
    //边界
    for(int i(lx);i < rx;++i)
 	{
 		d = min(DP(lx,ly,i,ry) + DP(i+1,ly,rx,ry) + ry - ly + 1,d);
 	}
 	for(int i(ly);i < ry;++i)
 	{
     	d = min(DP(lx,ly,rx,i) + DP(lx,i+1,rx,ry) + rx - lx + 1,d);
 	}
 	return d;
}
int main()
{
    int times(0);
    while(scanf("%d%d%d",&n,&m,&k) != EOF && n && m)
    {
        memset(sum,0,sizeof(sum));
        memset(mp,0,sizeof(mp));
        for(int i(1);i <= k;++i)
        {
            int posx,posy;
            scanf("%d%d",&posx,&posy);
            mp[posx][posy] = true;
        }
        for(int i(1);i <= n;++i)
        {
            for(int j(1);j <= m;++j)
            {
                sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + mp[i][j];
        //        dp[i][j] = inf;
            }
        }
        for(int i(1);i <= n;++i)
        {
            for(int j(1);j <= m;++j)
            {
                for(int i1(1);i1 <= n;++i1)
                {
                    for(int j1(1);j1 <= m;++j1)
                    {
                        dp[i][j][i1][j1] = inf;
                    }
                }
            }
        }
        printf("Case %d: %d\n",++times,DP(1,1,n,m));
    }
    return 0;
}

```

---

## 作者：zhaoyp (赞：5)

#### upd on : 22.04.08 感谢 珂爱的施施子 找出的一处错误。

## Solution

紫书习题 $9 - 3$: 二维区间 $\text{DP}$ 。

用四元组表示矩形。例如一矩形左上角和右下角顶点坐标分别为$(a,b),(c,d)$ 则记该矩形为矩形 $(a,b,c,d)$ 。

设 $dp_{a,b,c,d}$ 表示对矩形 $(a,b,c,d)$ 进行划分的最小代价。

假设所有比矩形 $(a,b,c,d)$ 小的矩形的代价都已经求出来，那么对于矩形 $(a,b,c,d)$ 有两种切法：

1. 横向切一刀，分成两个小矩形。

1. 纵向切一刀，分成两个小矩形。

枚举两种切法的切线的位置，进行转移即可。

边界条件：

1. 矩形 $(a,b,c,d)$ 中没有樱桃，由于题中 **要求最后每一块蛋糕上恰好有一个樱桃** 这种分法不成立，$dp_{a,b,c,d} = inf$。

1. 矩形 $(a,b,c,d)$ 中恰好有一个樱桃，$dp_{a,b,c,d} = 0$。

二维前缀和预处理樱桃数，总时间复杂度 $O(n^5)$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
int n,m,x,y,k,T,a[25][25],pre[25][25],dp[25][25][25][25];
inline int num(int a,int b,int c,int d)
{
	return pre[c][d] - pre[a - 1][d] - pre[c][b - 1] + pre[a - 1][b - 1];
}
void clear()
{
	memset(a,0,sizeof(a));
	memset(pre,0,sizeof(pre));
	memset(dp,0x3f,sizeof(dp));
}
void input()
{
	for(int i = 1;i <= k;i++)
		scanf("%d%d",&x,&y),a[x][y]++;
}
void prefix()
{
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)	
			pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + a[i][j];
}
void DP()
{
	for(int k1 = 1;k1 <= n;k1++)
		for(int k2 = 1;k2 <= m;k2++)
			for(int i = 1;k1 + i - 1 <= n;i++)
				for(int j = 1;j + k2 - 1 <= m;j++)
				{
					int a = i,b = j,c = k1 + i - 1,d = k2 + j - 1;
					if(!num(a,b,c,d))
						dp[a][b][c][d] = inf;
					else if(num(a,b,c,d) == 1)
						dp[a][b][c][d] = 0;
					else
					{
						for(int k = a;k < c;k++)
							dp[a][b][c][d] = min(dp[a][b][c][d],dp[a][b][k][d] + dp[k + 1][b][c][d] + k2);
						for(int k = b;k < d;k++)
							dp[a][b][c][d] = min(dp[a][b][c][d],dp[a][b][c][k] + dp[a][k + 1][c][d] + k1);
					} 
				}
}
void output()
{
	printf("Case %d: %d\n",++T,dp[1][1][n][m]);
}
int main()
{
	while(scanf("%d%d%d",&n,&m,&k) != EOF)
	{
		clear();
		input();
		prefix();
		DP();
		output(); 
	}
	return 0 ; 
}
```

---

## 作者：CQ_Bab (赞：1)

[更好的阅读体验](https://www.luogu.com.cn/blog/bigppwatersun/solution-uva1629)。

# 前言
这道题是我与一位大佬一起做的，还是有一定的难度所以就决定发一篇题解纪念一下，但是不得不说这道题还是泰库啦！不过，TYX 小朋友还是太强啦！
# 思路
这道题其实和 [这道题有一点类似](https://www.luogu.com.cn/problem/P1436)那么我们就可以借用一下那一道题的思路了，我们可以用递归的方式来处理，就是每一次传进去这个要处理的矩阵的左上角和右下角，然后在统计出被包含的樱桃数量，如果为 $0$ 那么就不合法，如果为 $1$ 则代价为 $0$ 然后，我们就可以枚举一下如何进行分割。

- 我们如果是以第 $i$ 条横着的线进行分割的，那么代价就为 $dp_{a,b,i,y}+dp_{i,b,x,y}+y-b$ 假设我们的左上角为 $a,b$ 右下角为 $x,y$，这里我们因为是以线为分界边，那么我们的 $i$ 是需要重合的。
- 我们若是竖着切也与横着切同理，这里就写一下代价方程为 $dp_{a,b,x,i}+dp_{a,i,x,y}+x-a$ 其原理也与上述内容相同，所以不再赘述。

但是这里就有一个细节因为我们输入的 $n,m$ 为格子的数量所以我们在传参是需要将 $n,m$ 都加一，而且因为樱桃的下标是格子的下标所以我们对于一个樱桃被包含需要满足 $yx<x$，$a\leq yx$，$yy<y$，$b\leq yy$。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define w(x)  while(x--)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int n,m;
struct chery{
	int x,y;
}ch[410];
int f[21][21][21][21] ;
int k;
bool cmp(chery a,chery b) {
	if(a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}
int dfs(int a,int b,int x,int y) {
	if( f[a][b][x][y] < 0x3f3f3f3f / 2 ) return f[a][b][x][y] ;
	int cnt=false;
	rep(i,1,k) {
		if(ch[i].x>=a&&ch[i].x<x) {
			if(ch[i].y>=b&&ch[i].y<y){
				cnt ++ ; 
			}
		}
	}
	if(!cnt) return INT_MAX;
	if(cnt==1) return f[a][b][x][y] = false;
	rep(i,a+1,x-1) f[a][b][x][y] = min(f[a][b][x][y],dfs(a,b,i,y)+dfs(i,b,x,y)+y-b);
	rep(i,b+1,y-1) f[a][b][x][y] = min(f[a][b][x][y],dfs(a,b,x,i)+dfs(a,i,x,y)+x-a);
	return f[a][b][x][y];
}
int idx;
fire main() {
	while(cin>>n>>m>>k){
	memset(f,0x3f,sizeof f);
	rep(i,1,k) 
	{
		in(ch[i].x),in(ch[i].y);
	}
	sort(ch+1,ch+1+k,cmp);
	printf("Case %lld: ",++idx);
	cout<<dfs(1,1,n+1,m+1)<<endl;
}
//	cout << f[3][1][4][3] << endl ;
	return false;
}
/*
3 4 3 
1 2 
2 3 
3 2
3 4 3 1 2 2 3 3 2
*/
```

---

## 作者：Code_星云 (赞：1)

由于 $n, m$ 很小，很明显的二维区间 DP。同时，我们把切割倒着处理，即合并蛋糕块会更方便（尤其体现在初始赋值）。

我们用 $dp_{x1, y1, x2, y2}$ 表示把 $(x1, y1),\ (x2, y2)$ 区间合并完的最小花费。转移方程和一维区间 DP 相似，枚举转移点 $k$。然后初始赋值即为把块内樱桃数为一的块的 DP 值设为 0，其余的设为正无穷。

然后统计块内樱桃数可以用二位前缀和预处理，很套路。

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 25;
int n, m, k, idx = 0;
int mp[N][N], sum[N][N], dp[N][N][N][N];

int Min(int x, int y){return x < y ? x : y;}
void chmin(int &x, int y){x = Min(x, y);}
int get(int x1, int y1, int x2, int y2){
	return sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1];
}
void work(){
	++ idx;
	memset(mp, 0, sizeof mp);
	memset(sum, 0, sizeof sum);
	memset(dp, 0x3f, sizeof dp);
	for(register int i = 1; i <= k; i ++){
		int x, y; scanf("%d %d", &x, &y);
		mp[x][y] ++;
	}
	for(register int i = 1; i <= n; i ++)
	  for(register int j = 1; j <= m; j ++)
		sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + mp[i][j];
	for(register int len1 = 1; len1 <= n; len1 ++)
	  for(register int len2 = 1; len2 <= m; len2 ++)
		for(register int x1 = 1; x1 + len1 - 1 <= n; x1 ++)
		  for(register int y1 = 1; y1 + len2 - 1 <= m; y1 ++){
			int x2 = x1 + len1 - 1;
			int y2 = y1 + len2 - 1;
			if(! get(x1, y1, x2, y2)) continue;
			if(get(x1, y1, x2, y2) == 1){
				dp[x1][y1][x2][y2] = 0;
				continue;
			}
			if(len1 > 1){
			  for(register int k = x1; k < x2; k ++)
				chmin(dp[x1][y1][x2][y2], dp[x1][y1][k][y2] + dp[k + 1][y1][x2][y2] + len2);
			}
			if(len2 > 1){
			  for(register int k = y1; k < y2; k ++)
				chmin(dp[x1][y1][x2][y2], dp[x1][y1][x2][k] + dp[x1][k + 1][x2][y2] + len1);
			}
		  }
	printf("Case %d: %d\n", idx, dp[1][1][n][m]);
}
int main(){
	while(scanf("%d %d %d", &n, &m, &k) != EOF) work();
	return 0;
}
/*
3 4 3
1 2
2 3
3 2
*/
```


---

## 作者：Hisaishi_Kanade (赞：0)

首先你考虑一个事情啊，一个蛋糕切开之后是不是就变成两块了，这两块是无关的对不对？

那么我们直接大力 dp，设 $f_{a,b,c,d}$ 表示将左上角 $(a,b)$，右下角 $(c,d)$ 的切好。

首先如果 $(a,b,c,d)$ 这个块只有一个樱桃直接 $f_{a,b,c,d}=0$ 下班回家；如果没有樱桃你怎么切不可能无中生有，所以 $f_{a,b,c,d}=+\infty$。如何求樱桃个数？二维前缀和就行了。

其他情况，直接枚举断点，一种情况是横着切，此时需要花费一个长（钦定横着是长竖着是宽）；竖着切花费一个宽。

如何保证转移没有后效性？类似于传统区间动态规划的，先枚举长宽然后枚举 $a,b$，这样可以保证只调用已经求解的区间。

总复杂度 $O(n^5)$，无所谓因为 $n\le 20$。

```cpp
/*
设 f[a][b][c][d] 表示将 (a,b) 到 (c,d) 切好。
先枚举长和宽然后枚举 a,b 可以求出 c,d。
显然的如果这一块只有一个樱桃不用切，这个直接二维前缀和就行。
那么接下来直接枚举断点做就行了。
*/
#include <bits/stdc++.h>
#define rep(i,l,r) for(i=l;i<=r;++i)
using namespace std;
int n,m,k,i,l1,l2,x,y,c,d,j,a,b,cnt;
const int inf=1<<30;
int f[25][25][25][25],s[25][25];
inline int sum(int a,int b,int c,int d)
{
	return s[c][d]-s[c][b-1]-s[a-1][d]+s[a-1][b-1];
}
void solve()
{
	rep(i,1,n)rep(j,1,m)s[i][j]=0;
	rep(a,1,n)rep(b,1,m)rep(c,1,n)rep(d,1,m)f[a][b][c][d]=inf;
	rep(i,1,k)
	{
		scanf("%d %d",&x,&y);
		++s[x][y];
	}
	rep(i,1,n)rep(j,1,m)s[i][j]+=s[i][j-1]+s[i-1][j]-s[i-1][j-1];
	rep(l1,1,n)rep(l2,1,m)
	rep(a,1,n-l1+1)rep(b,1,m-l2+1)
	{
		c=a+l1-1;d=b+l2-1;
		if(sum(a,b,c,d)<1)f[a][b][c][d]=inf;
		else if(sum(a,b,c,d)==1)f[a][b][c][d]=0;
		else
		{
			f[a][b][c][d]=inf;
			rep(k,a,c-1)f[a][b][c][d]=min(f[a][b][c][d],f[a][b][k][d]+f[k+1][b][c][d]+l2);
			rep(k,b,d-1)f[a][b][c][d]=min(f[a][b][c][d],f[a][b][c][k]+f[a][k+1][c][d]+l1);
		}
//		printf("%d %d %d %d %d %d\n",a,b,c,d,sum(a,b,c,d),f[a][b][c][d]);
	}
	printf("Case %d: %d\n",++cnt,f[1][1][n][m]);}
int main(){while(~scanf("%d %d %d",&n,&m,&k))solve();}
```

---

## 作者：Fzrcy (赞：0)

通过数据范围可知 时间复杂度可以达到 $ O ( n^5 ) $ 也不会超时。

设 $f[i][j][x][y]$ 为 $(i,j)$ 到 $(x,y)$ 这一区域所需的最小切割线总长度。

显然可以同过切一刀使得该范围变为两个更小的两个范围。

- 第一种情况--横着切，即将 $f[i][j][x][y]$ 分为 $ f[i][j][k][y],f[k+1][j][x][y] (i \le k < x) $ 两个区间。

$$ f[i][j][x][y]= \min (f[i][j][x][y],f[i][j][k][y]+f[k+1][j][x][y]+\text{区间长度}) (i \le k < x) $$

- 第二种情况--竖着切，即将 $f[i][j][x][y]$ 分为 $ f[i][j][x][k],f[i][k+1][x][y] (j \le k < y) $ 两个区间。

$$ f[i][j][x][y]= \min (f[i][j][x][y],f[i][j][x][k]+f[i][k+1][x][y]+\text{区间宽度}) (j \le k < y) $$

因此我们可以逆序先求区间小的然后在求区间大的。

若该区间没有樱桃则赋值为一个极大值，只有一个樱桃则无法在分，即赋值为 $0$ 。

其中区间内樱桃个数用二维前缀和来表示。



即

```cpp
for(int len=0; len<n; len++)
for(int lens=0; lens<m; lens++)
for(int i=1; i+len<=n; i++)
for(int j=1; j+lens<=m; j++)
{
	int x=i+len;
	int y=j+lens;
	int z=s(i,j,x,y);//区间樱桃个数。
	if(z==0)f[i][j][x][y]=0x3f3f3f3f;//没有樱桃。
	else if(z==1)f[i][j][x][y]=0;//只有一个樱桃。
	else{//区间长度为 y-j+1=j+lens-j+1=lens+1 ，区间宽度同理。
		for(int k=i; k<x; k++)//横着切。
		f[i][j][x][y]=min(f[i][j][x][y],f[i][j][k][y]+f[k+1][j][x][y]+lens+1);
		for(int k=j; k<y; k++)//竖着切。
		f[i][j][x][y]=min(f[i][j][x][y],f[i][j][x][k]+f[i][k+1][x][y]+len+1);
	}
}
```

总代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
class DP{
private:
int n,m;
    int k;
    int sum[25][25];
    int f[25][25][25][25];
    int a[25][25];

public:
    #define s(i,j,x,y) (sum[x][y]+sum[i-1][j-1]-sum[i-1][y]-sum[x][j-1])
    void work()
    {
        memset(sum,0,sizeof(sum));memset(f,0x3f3f3f3f,sizeof(f));memset(a,0,sizeof(a));
        for(int i=1; i<=k; i++){
            int x,y;
            cin>>x>>y;
	    a[x][y]=1;
        }
	for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
            }
        }
        for(int len=0; len<n; len++)
	{
            for(int lens=0; lens<m; lens++)
            {
		for(int i=1; i+len<=n; i++)
		{
		    for(int j=1; j+lens<=m; j++)
		    {
			int x=i+len;
			int y=j+lens;
			int z=s(i,j,x,y);
			if(z==0)f[i][j][x][y]=0x3f3f3f3f;
			else if(z==1)f[i][j][x][y]=0;
			else{
			    for(int k=i; k<x; k++)
			    {
				f[i][j][x][y]=min(f[i][j][x][y],f[i][j][k][y]+f[k+1][j][x][y]+lens+1);
			    }
			    for(int k=j; k<y; k++)
			    {
				f[i][j][x][y]=min(f[i][j][x][y],f[i][j][x][k]+f[i][k+1][x][y]+len+1);
			    }
			}
		    }
		}
	    }
	}
	cout<<f[1][1][n][m]<<endl;
    }
    void Main()
    {
        int T=0;
        while(scanf("%d%d%d",&n,&m,&k)!=EOF){
            printf("Case %d: ",++T);
            work();
        }
    }

};
int main()
{
    DP x;
    x.Main();
}
```

---

## 作者：CReatiQ (赞：0)

### 题意概述

有一个 $n*m$ 的蛋糕，其上有一些樱桃，每一格上至多有一颗樱桃。

现可对其进行切割，每次切割只能对单独一块切出来的蛋糕进行（未切则为原蛋糕），且需沿网格线将该块蛋糕一分为二，不能拐弯。

求当切出每块蛋糕都有且仅有一颗樱桃时，最短的切割线总长。

---

### 思路

暴搜出奇迹，记忆化搜索！

枚举所有网格矩阵（通过枚举不同的上下左右边界），再枚举每一条网格线对矩阵进行划分，以此进行记忆化搜索。

但是划分与否，是要考虑不同的樱桃数的。

当樱桃数大于 $1$ 时，我们需要对这个矩阵进行划分；

当樱桃数恰好为 $1$ 时，我们不需要对其划分；

当樱桃数为 $0$ 时，这种划分是失败的，我们需要把它毙掉。

所以我们对症下药:

当樱桃数大于 $1$ 时，对网格线枚举，用最小的切割代价和记录该矩阵代价；

当樱桃数恰好为 $1$ 时，记录该矩阵切割至满足条件的代价为 $0$ ；

当樱桃数为 $0$ 时，不能这么切，记该矩阵切割代价为 $inf$ 即可。

问题已经能够解决了，我们来计算一下时间复杂度：

假设我们遇到最坏的情况，整个蛋糕都嵌满了樱桃，那么我们需要切割至每一个网格。

因为 $i*j$ 大小的矩阵有 $(n-i) \cdot (m-j)$ 个，所以分割操作次数是

$$\sum_{i=1}^n\sum_{j=1}^m (n-i) \cdot (m-j) \cdot (i+j)$$

接近 $\mathcal{O}(n^5)$ ，貌似可以接受？

等等，我们还需要计算矩阵中的樱桃个数，如果按照上面的办法计算，那我们就要为了确认樱桃个数而花费高昂的时间代价，让复杂度拉到 $\mathcal{O}(n^6)$ ，这是我们所不能接受的。

所以我们需要利用二维前缀和对矩阵内的樱桃个数预处理，以实现 $\mathcal{O}(1)$ 应答矩阵内的樱桃个数，将复杂度压回 $\mathcal{O}(n^5)$ 。

---

### Code

```cpp
#include <cstdio>
#include <cstring> 

const int MAXN=25,inf=1e9+7;
int n,m,k,x,y,T,ch,sum[MAXN][MAXN],f[MAXN][MAXN][MAXN][MAXN];//ch->cherry.
bool cake[MAXN][MAXN],vis[MAXN][MAXN][MAXN][MAXN];

inline int read()
{
	int x=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x;
}

inline int min(int a,int b) { return a<b?a:b; }

inline void init()
{
	T++,x=y=0;
	memset(f,0x3f,sizeof(f));
	memset(sum,0,sizeof(sum));
	memset(vis,0,sizeof(vis));
	memset(cake,0,sizeof(cake));
}

inline int get_cherry(int u,int d,int l,int r) { return sum[d][r]-sum[d][l-1]-sum[u-1][r]+sum[u-1][l-1]; }

int dfs(int u,int d,int l,int r)//u->up,d->down,l->left,r->right.
{
	if (vis[u][d][l][r]) return f[u][d][l][r];
	vis[u][d][l][r]=1;
	ch=get_cherry(u,d,l,r);
	if (!ch) return f[u][d][l][r]=inf;
	else if (ch==1) return f[u][d][l][r]=0;
	f[u][d][l][r]=inf;
	for (int i=u;i<d;i++)
		f[u][d][l][r]=min(f[u][d][l][r],dfs(u,i,l,r)+dfs(i+1,d,l,r)+r-l+1);
	for (int i=l;i<r;i++)
		f[u][d][l][r]=min(f[u][d][l][r],dfs(u,d,l,i)+dfs(u,d,i+1,r)+d-u+1);
	return f[u][d][l][r];
}

int main()
{
	while (scanf("%d%d%d",&n,&m,&k)!=EOF)
	{
		init();
		for (int i=1;i<=k;i++) scanf("%d%d",&x,&y),cake[x][y]=1;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+cake[i][j];
		printf("Case %d: %d\n",T,dfs(1,n,1,m));
	}
	return 0;
}
```


---

## 作者：_xbn (赞：0)

首先要注意：如果一个切割方案使得切出来的一块蛋糕上**不存在樱桃**，那么这个是**非法**方案。

观察数据范围，注意到 $n,m\leq 20$，我们可以设计出一个四维的状态。

设 $f_{u,d,l,r}$ 表示 $u$ 为上边界，$d$ 为下边界，$l$ 为左边界，$r$ 为右边界的矩形切割成合法状态的最短切割长度。

选择用记搜来进行转移。

对于矩形 $f_{u,d,l,r}$。首先判两种特殊情况：如果 $f_{u,d,l,r} = 0$ 直接回溯。

如果 $f_{u,d,l,r} = 1$，表示这是一个合法方案，返回 $0$。因为合法方案我们不需要进行切割。

接下来考虑切割，我们枚举横竖，从哪一行或哪一列切割。

如果横向切割： $f_{u,d,l,r} = \min(f_{u,d,l,r}, f_{u,i,l,r} + f_{i+1,d,l,r}+r-l+1)$。

如果纵向切割：$f_{u,d,l,r} = \min(f_{u,d,l,r}, f_{u,d,l,i}+f_{u,d,i+1,r}+d-u+1)$。

在转移时记住要判断当前矩形中有几个樱桃。

```cpp
#include <bits/stdc++.h>
#define inf 1e9;
using namespace std;
const int N = 22;
int n, m, k, p, q, ans, t, tot, a[N][N], f[N][N][N][N], b[N], c[N];
inline int rd()
{
	int f = 1, x = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
int F(int u, int d, int l, int r)
{
	int sum = 0;
	for (int i = u; i <= d; i++) for (int j = l; j <= r; j++) if(a[i][j] == 1) sum++;
	return sum;
}
int dfs(int u, int d, int l, int r)
{
	if(f[u][d][l][r] != -1) return f[u][d][l][r];
	int tmp = F(u, d, l, r);
	if(tmp == 0) return f[u][d][l][r] = inf;
	if(tmp == 1) return f[u][d][l][r] = 0;
	f[u][d][l][r] = inf;
	for (int i = u; i < d; i++) f[u][d][l][r] = min(f[u][d][l][r], dfs(u, i, l, r) + dfs(i + 1, d, l, r) + r - l + 1);
	for (int i = l; i < r; i++) f[u][d][l][r] = min(f[u][d][l][r], dfs(u, d, l, i) + dfs(u, d, i + 1, r) + d - u + 1);
	return f[u][d][l][r];
}
int main()
{
	int cas = 0;
	while (~scanf("%d%d%d", &n, &m, &k)) 
	{
		memset(f, -1, sizeof(f)); memset(a, 0, sizeof(a));
		for (int i = 1; i <= k; i++)
		{
			int x = rd(), y = rd();
			a[x][y] = 1;
		}
		ans = dfs(1, n, 1, m); cas++; printf("Case %d: %d\n", cas, ans);
	}
	return 0;
}
```


---

