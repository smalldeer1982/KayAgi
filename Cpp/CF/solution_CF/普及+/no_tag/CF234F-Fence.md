# Fence

## 题目描述

Vasya should paint a fence in front of his own cottage. The fence is a sequence of $ n $ wooden boards arranged in a single row. Each board is a $ 1 $ centimeter wide rectangle. Let's number the board fence using numbers $ 1,2,...,n $ from left to right. The height of the $ i $ -th board is $ h_{i} $ centimeters.

Vasya has a $ 1 $ centimeter wide brush and the paint of two colors, red and green. Of course, the amount of the paint is limited. Vasya counted the area he can paint each of the colors. It turned out that he can not paint over $ a $ square centimeters of the fence red, and he can not paint over $ b $ square centimeters green. Each board of the fence should be painted exactly one of the two colors. Perhaps Vasya won't need one of the colors.

In addition, Vasya wants his fence to look smart. To do this, he should paint the fence so as to minimize the value that Vasya called the fence unattractiveness value. Vasya believes that two consecutive fence boards, painted different colors, look unattractive. The unattractiveness value of a fence is the total length of contact between the neighboring boards of various colors. To make the fence look nice, you need to minimize the value as low as possible. Your task is to find what is the minimum unattractiveness Vasya can get, if he paints his fence completely.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234F/a14b673dce5ebb55793e288f9c6ca9cf6b548bb3.png)The picture shows the fence, where the heights of boards (from left to right) are 2,3,2,4,3,1. The first and the fifth boards are painted red, the others are painted green. The first and the second boards have contact length 2, the fourth and fifth boards have contact length 3, the fifth and the sixth have contact length 1. Therefore, the unattractiveness of the given painted fence is 2+3+1=6.

## 样例 #1

### 输入

```
4
5 7
3 3 4 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
2 3
1 3 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
3 3
2 2 2
```

### 输出

```
-1
```

# 题解

## 作者：ListenSnow (赞：3)

动态规划好题，目测本题难度为绿题左右。

### 题意
给定 $n$ 个相邻的宽度为 $1$ 的栅栏，第 $i$ 个栅栏高度为 $h_i$，每个栅栏必须**全部**刷红色或者绿色。定义难看程度为所有的相邻的**不同**颜色的栅栏之间**较小**栅栏的高度之和。求在满足红色栅栏面积不超过 $a$ ，且绿色栅栏面积不超过 $b$ 的前提下，难看程度的最小值。 

### 思路

初看此题，有一种朴素的想法，定义 $f[i][j][k][l]$ 来表示在前 $i$ 个栅栏中，红色栅栏面积为 $j$，绿色栅栏面积为 $k$，且最后一个栅栏颜色为 $l$ （$0$ 表示红色，$1$ 表示绿色）时的最小难看程度。
于是就可以得出状态转移方程：

$f[i][j][k][0]=min(f[i][j-h[i]][k][0],f[i][j-h[i]][k][1]+min(h[i],h[i-1]))$ 。

$f[i][j][k][1]=min(f[i][j][k-h[i]][1],f[i][j][k-h[i]][1]+min(h[i],h[i-1]))$ 。


但是仔细一看本题数据范围 ：$(0 \leq a,b \leq 40000)$，~~显然~~无法通过。于是需要考虑优化。
 
通过观察可以发现。在前 $i$ 个栅栏中，所有红色栅栏的面积与所有绿色栅栏面积的总和一定为前 $i$ 个栅栏的面积之和。于是可以在转移的时候只枚举红色栅栏的总面积，绿色栅栏的面积可以用总面积减去红色栅栏的面积得到。于是就可以通过本题。
### code：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=210;
const int M=40010;
int abs(int a){return a>0?a:-a;}
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int n,a,b,h[N],f[N][M][2],s[N];//0 a，1 b 
int main()
{
	memset(f,0x3f,sizeof(f));
	f[0][0][0]=f[0][0][1]=0;
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;i++) 
	{
	    scanf("%d",&h[i]);	
	    s[i]=s[i-1]+h[i];
	}
	for(int i=1;i<=n;i++)
	    for(int j=max(0,s[i]-b);j<=min(a,s[i]);j++)
	    {
	    	if(j>=h[i]) f[i][j][0]=min(f[i-1][j-h[i]][1]+min(h[i],h[i-1]),f[i-1][j-h[i]][0]);
	    	f[i][j][1]=min(f[i-1][j][1],f[i-1][j][0]+min(h[i],h[i-1]));
		}
	int ans=INF;
	for(int i=0;i<=a;i++) ans=min(ans,min(f[n][i][1],f[n][i][0]));
	if(ans==INF) puts("-1");
	else printf("%d\n",ans);
	return 0;
}
```


---

## 作者：ran_qwq (赞：2)

设 $dp_{i,j,0/1}$ 为前 $i$ 列，涂了 $j$ 格红色，当前涂的是红色 / 绿色的最小难看程度。

如果该列涂的是红色，则 $dp_{i,j,0}=\min(dp_{i-1,j-h_i,0},dp_{i-1,j-h_i,1}+\min(h_{i-1},h_i))$。

如果该列涂的是绿色，则 $dp_{i,j,1}=\min(dp_{i-1,j,1},dp_{i-1,j,0}+\min(h_{i-1},h_i))$。

边界是 $n=1$ 的情况，答案是所有满足 $sum-i\le b$ 的情况取 min，其中 $sum=\sum h_i$。

---

## 作者：开始新的记忆 (赞：1)

题目大意：给出n个长方形他们的高，宽为1，给出染料可以染的面积（两种，分别为a、b）A值为不同染色之间的面积（就是相邻两个长方形挨着的面积）。问这个值最小多少

思路：dp[i][j][k]代表已经染了i个长方形，用了j个a染料，当前染a、b（用0、1代表）。初始化 dp[0][0][0]=dp[0][0][1]=0;（状态转换方程因为情况较多，可在代码中查看）

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int dp[210][40010][2],n,a,b,h[210], c[210], s[210];

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin>>n>>a>>b;
    for(int i = 1; i<=n; ++i) 
    {
        cin>>h[i];
        c[i] = min(h[i-1], h[i]);
        s[i] = s[i-1] + h[i];
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0] = dp[0][0][1] = 0;
    for(int i = 1; i <= n; ++i) 
    {
        for(int j = 0; j<=s[i]; ++j) 
        {
            if(j > a)
                break;
            if(s[i] - j > b)
                continue;
            if(j >= h[i])
                dp[i][j][0] = min(dp[i-1][j - h[i]][0], dp[i-1][j - h[i]][1] + c[i]);
            dp[i][j][1] = min(dp[i-1][j][0] + c[i], dp[i-1][j][1]);
        }
    }
    int res = INF;
    for(int j = 0; j<=a; ++j) 
        for(int k = 0; k<=1; ++k)
            res = min(res, dp[n][j][k]);
    if(res==INF)
        cout<<-1<<endl;
    else
        cout<<res<<endl;
}
```


---

## 作者：The_foolishest_OIer (赞：0)

DP。

令 $dp_{i,j,k}$ 表示目前涂到第 $i$ 个栅栏，用了 $j$ 的红油漆，$k = 0$ 表示当前栅栏涂红色，$k = 1$ 表示当前栅栏涂绿色。

显然，$dp_{i,j,0} = \min(dp_{i - 1,j - h_i,0},dp_{i - 1,sum_i - j,1} + \min(h_{i - 1},h_i))$。

其中 $sum_i$ 表示 $\sum_{j = 1}^i h_j$。

另一个方程类似。

注意下标越界的细节。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 205;
const int M = 4e4 + 10;
const int inf = 1e12;
const int mod = 1e9 + 7;
int T,n,a,b;
int h[N],sum[N];
int dp[N][M][2];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void Test(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
}
void solve(){
	cin >> n >> a >> b;
	for (int i = 1 ; i <= n ; i++) cin >> h[i];
	for (int i = 1 ; i <= n ; i++) sum[i] = sum[i - 1] + h[i];
	for (int i = 0 ; i <= n ; i++)
		for (int j = 0 ; j <= max(a,b) ; j++)
			dp[i][j][0] = dp[i][j][1] = inf;
	dp[0][0][0] = dp[0][0][1] = 0;
	for (int i = 1 ; i <= n ; i++){
		for (int j = h[i] ; j <= min(sum[i],a) ; j++)
			dp[i][j][0] = min(dp[i - 1][j - h[i]][0],(sum[i] - j <= b ? dp[i - 1][sum[i] - j][1] + min(h[i - 1],h[i]) : inf));
		for (int j = h[i] ; j <= min(sum[i],b) ; j++)
			dp[i][j][1] = min(dp[i - 1][j - h[i]][1],(sum[i] - j <= a ? dp[i - 1][sum[i] - j][0] + min(h[i - 1],h[i]) : inf));
	}
	int ans = inf;
	for (int i = 0 ; i <= a ; i++) ans = min(ans,dp[n][i][0]);
	for (int i = 0 ; i <= b ; i++) ans = min(ans,dp[n][i][1]);
	if (ans == inf) cout << -1 << endl;
	else cout << ans << endl;
}
signed main(){
	Test();
	close();
	T = 1;
	//cin >> T;    
	while (T--) solve();
	return 0;
}
```

---

## 作者：ainivolAGEM (赞：0)

**前排提示：**[更好的阅读体验。](https://www.luogu.com.cn/article/b6kflg3b)

## 题目大意

[题目](https://www.luogu.com.cn/problem/CF234F)很明确了，没看过的可以先尝试做一下。

## 题目分析

初看这道题，可以发现对于每一个栅栏的颜色互不影响，满足无后效性，所以考虑 dp。

那么很容易想到，定义一个二维数组 $dp [ i ] [ j ]$ 表示对于前 $i$ 个栅栏，红色栅栏数量为 $j$ 的情况下，最小的难看程度。绿色栅栏的数量可以通过总栅栏数量减去红色的数量得到，所以无需枚举。

然而发现，对于后一个栅栏需要经前一个栅栏颜色才能得到数量，所以还需要设一维 $k$。最终定义如下：$dp [ i ] [ j ] [ k ]$ 表示表示对于前 $i$ 个栅栏，红色栅栏数量为 $j$ 且最后一个栅栏颜色为 $k$ 的情况下（红、绿分别用 $0$ 和 $1$ 代表），最小的难看程度。

所以易得转移方程如下：（设 $sum [ i ] = sum [ i - 1 ] + h [ i ]$，即前缀和，而 $minx [ i ]$ 代表 $h [ i - 1 ]$ 和 $h [ i ]$ 的最小值）

$$dp [ i ] [ j ] [ 0 ] = \min ( dp [ i - 1 ] [ j - h [ i ] ] [ 0 ] , dp [ i - 1 ] [ j - h [ i ] ] [ 1 ] + minx [ i ] )$$

$$dp [ i ] [ j ] [ 1 ] = \min ( dp [ i - 1 ] [ j ] [ 0 ] + minx [ i ] , dp [ i - 1 ] [ j ] [ 1 ] )$$

注意**特判** $j < a$ 和 $sum [ i ] - j > b$ 和 $j \ge h [ i ]$ 的情况。

最终答案即为对于所有 $0 \leq i \leq a$，最小的 $\min ( dp [ n ] [ i ] [ 0 ] , dp [ n ] [ i ] [ 1 ] )$。

记得数组**空间要开够**。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=204;
const int T=2;
const int inf=0x3f3f3f3f;
ll n,a,b,h[N],dp[N][N*N][T];
ll ans=inf,sum[N],minx[N];
int main(){
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++){
        cin>>h[i];
        sum[i]=sum[i-1]+h[i];
        minx[i]=min(h[i-1],h[i]);
    }
    memset(dp,inf,sizeof(dp));
    dp[0][0][0]=dp[0][0][1]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum[i];j++){
            if(j>a){
                break;
            }
            if(sum[i]-j>b){
                continue;
            }
            if(j>=h[i]){
                dp[i][j][0]=min(dp[i-1][j-h[i]][0],dp[i-1][j-h[i]][1]+minx[i]);
            }
            dp[i][j][1]=min(dp[i-1][j][0]+minx[i],dp[i-1][j][1]);
        }
    }
    for(int i=0;i<=a;i++){
    	ans=min(ans,min(dp[n][i][0],dp[n][i][1]));
    }
    if(ans!=inf){
        cout<<ans;
    }else{
        cout<<"-1";
    }
}
```

本代码**不含**文件读写，请**自行添加**。

---

## 作者：Graph_Theory (赞：0)

### 定义状态 
定义状态 $dp_{i,r,g,b}$ 为木板个数为 $i$ 红色个数为 $r$ 绿色个数为 $g$ 时，上一个木板颜色为 $b(0/1)$ 时的难看程度。

这里 $b=1$ 为红色，$b=0$ 为绿色。

通过数据而知，当四维时超时。此时我们使用前缀和，记录从 $1$ 到 $i$ 木板的面积总值。则我们可以通过前缀和以及 $r$ 推出绿色的面积。

状态为 $dp_{i,r,b}$ 为木板个数为 $i$ 红色个数为 $r$ 时，上一个木板颜色为 $b(0/1)$ 时的难看程度。

最终状态为 $\min dp_{n,i(0 \to n),0/1}$
### 转移

有颜色区分，此时我们分类讨论。

当 $b=1$ 时，

$$ dp_{i,r,1} = \min (dp_{i-1,r-h_i,1},dp_{i-1,r-h_i,0} + \min(h_{i},h_{i}))$$

当前为红色时，需要减去当前的面积。

为了防止报错我们还要特判 $r-h_{i} \ge 0 $。

这里的 $h_{i}$ 实际是 $h_i \times 1$，下面也是。

当 $b=0$ 时，

$$ dp_{i,r,0} = \min (dp_{i-1,r,0},dp_{i-1,r,1} + \min(h_{i},h_{i}))$$

当前为绿色时不影响红色的数量，$r$ 不变。

代码
```cpp
if(r>=h[i])	dp[i][r][1]=min(dp[i-1][r-h[i]][1],dp[i-1][r][1]+min(h[i],h[i-1]));
			dp[i][r][0]=min(dp[i-1][r][0],dp[i-1][r][1]+min(h[i],h[i-1]));
            
```
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
int n,h[222],a,b,dp[222][40001][2],s[514];
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++) cin>>h[i],s[i]=s[i-1]+h[i];
	memset(dp,0x3f3f3f3f,sizeof(dp));
	dp[0][0][0]=0;
	dp[0][0][1]=0;
	for(int i=1;i<=n;i++)
	{
		for(int r=max(0,s[i]-b);r<=min(s[i],a);r++)
		{
			if(r>=h[i])	dp[i][r][1]=min(dp[i-1][r-h[i]][1],dp[i-1][r-h[i]][0]+min(h[i],h[i-1]));
			dp[i][r][0]=min(dp[i-1][r][0],dp[i-1][r][1]+min(h[i],h[i-1]));
		}
	}
	int ans=0x3f3f3f3f;
	for(int i=0;i<=a;i++)
		ans=min(ans,min(dp[n][i][0],dp[n][i][1]));
	if(ans!=0x3f3f3f3f) cout<<ans;
	else           		cout<<"-1";
	return 0;
}
```


---

## 作者：Clover_BY (赞：0)

# [CF234F  Fence](https://www.luogu.com.cn/problem/CF234F)
## 题目描述
你被要求为 $n$ 个宽为 $1$，高为 $h_i$ 的栅栏染上红、绿两种颜色，要求红色面积不超过 $a$，绿色面积不超过 $b$，且最小化总代价。  
总代价定义为相邻且颜色不同的栅栏相交部分的线段长度之和。
## 题目分析
对于此类具有多个限制条件，仅凭简单枚举难以处理的题目，可以考虑进行动态规划。

不难发现，当我们处理到某一个栅栏时，先前处理过的栅栏的面积是确定的，因此只需要记录一种颜色栅栏的总面积，那么另一种颜色栅栏的总面积即可通过前缀和快速得到。  

设 $dp_{i, j, 0/1}$ 表示处理到第 $i$ 个栅栏，红色面积为 $j$， 且当前栅栏被涂上红色/绿色时的最小代价。  

转移时预先处理出绿色部分的面积，再根据 $a$ 和 $b$ 的限制，分别考虑是否可以对这一根栅栏涂上两种颜色。若当前要涂的颜色和上一根的颜色不同，则代价增加 $\min (h_{i-1}, h_i)$。  

注意文件输入输出以及对无解的判断。  
题目较为简单，建议评黄/绿。

Code Time
```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
using namespace std;

inline int min(int &a, int b){return a < b ? a : b;}
inline int read()
{
    int x = 0; char c;
    while(!isdigit(c = getchar()));
    do{
        x = (x << 1) + (x << 3) + (c ^ 48);
    }while(isdigit(c = getchar()));
    return x;
}

int top = 0, stk[20];
inline void write(int x)
{
    do{
        stk[++top] = x % 10;
        x /= 10;
    }while(x);
    for(register int i = top; i; --i)
        putchar(stk[i] | 48);
    putchar('\n'); top = 0;
    return ;
}

int n, a, b, ans = 2147483647;
int sz[205], sum[205], dp[205][40010][2];
//涂了i块栅栏，有j的面积涂上红色，当前以红/绿结尾的最小不美观度
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);//注意此题文件输入输出
    n = read(); a = read(); b = read();
    for(register int i = 1; i <= n; ++i)
    {
        sz[i] = read();
        sum[i] = sum[i - 1] + sz[i];
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0] = dp[0][0][1] = 0;
    for(register int i = 1; i <= n; ++i)
    {
        for(register int j = sum[i - 1]; j >= 0; --j)
        {
            for(register int k = 0; k <= 1; ++k)
            {
                int l1 = j + sz[i], l2 = sum[i - 1] - j + sz[i];//l1为假设这根栅栏涂红色后红色总面积，l2同理
                if(l1 <= a) dp[i][l1][0] = min(dp[i - 1][j][0], dp[i - 1][j][1] + min(sz[i], sz[i - 1]));
                if(l2 <= b) dp[i][j][1] = min(dp[i - 1][j][1], dp[i - 1][j][0] + min(sz[i - 1], sz[i]));
            }//转移需满足a,b限制
        }
    }
    for(register int i = 0; i <= a; ++i)
        for(register int j = 0; j <= 1; ++j)
            ans = min(ans, dp[n][i][j]);
    if(ans == 0x3f3f3f3f) printf("-1\n");//若目标状态没有被更新，说明不存在合法方案
    else write(ans); return 0;
}
```

---

