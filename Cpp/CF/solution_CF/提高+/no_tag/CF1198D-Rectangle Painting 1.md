# Rectangle Painting 1

## 题目描述

有一个 $n \times n$ 的正方形网格。部分格子被涂成黑色，其余格子为白色。每次操作，你可以选择一个矩形区域，将该区域内的所有格子涂成白色。将一个 $h \times w$ 的矩形区域涂白的代价为 $\max(h, w)$。你的任务是以最小的总代价将所有格子都涂成白色。

## 说明/提示

下图展示了样例以及一些最优解。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1198D/cb07e2ee21adbb1a45d78db7b060446e335ba3ff.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
###
#.#
###
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
...
...
...
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
#...
....
....
#...
```

### 输出

```
2
```

## 样例 #4

### 输入

```
5
#...#
.#.#.
.....
.#...
#....
```

### 输出

```
5
```

# 题解

## 作者：bloodstalk (赞：9)

妙妙区间 DP 题。

我们需要设一个状态，可供我们从小往大推，最终的状态就是全图这个矩形，那么我们可以设 $f(x_a,y_a,x_b,y_b)$ 表示将 $(x_a,y_a)$ 到 $(x_b,y_b)$ 覆盖的最小代价。

并且秉承着大道至简原则，我们要选一个最简易的能够概括这个状态的转移，因此我们枚举一个直线作为分割点，横竖都枚举，然后取一个 $\min$，当然不要忘了不分割也是一种情况，不要忘了它。

因为这个转移顺序不是很固定，所以我们采用记忆化搜索实现。

代码：
```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define next nxt
#define re register
#define il inline
const int N = 50 + 2;
using namespace std;
int max(int x,int y){return x > y ? x : y;}
int min(int x,int y){return x < y ? x : y;}

int n;
int f[N][N][N][N];
char ch;

il int read()
{
	int f=0,s=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f |= (ch=='-');
	for(; isdigit(ch);ch=getchar()) s = (s<<1) + (s<<3) + (ch^48);
	return f ? -s : s;
}

il int dfs(int xa,int ya,int xb,int yb)
{
	if(f[xa][ya][xb][yb] != -1) return f[xa][ya][xb][yb];
	int ans = 1e9;//记f[xa][ya][xb][yb]表示将一个左上角是(xa,ya)，右下角是(xb,yb)的矩形变成0的方案数
	for(re int i=xa;i<xb;i++) ans = min(ans , dfs(xa,ya,i,yb) + dfs(i+1,ya,xb,yb));//分开可以按列切
	for(re int i=ya;i<yb;i++) ans = min(ans , dfs(xa,ya,xb,i) + dfs(xa,i+1,xb,yb));//也可以按行切
	ans = min(ans,max(xb-xa+1,yb-ya+1));//也可以不切
	f[xa][ya][xb][yb] = ans;
	return ans;
}

signed main()
{
	memset(f , -1 , sizeof f);
	n = read();
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=n;j++)
		{
			cin >> ch;
			f[i][j][i][j] = (ch == '#');
		}
	cout << dfs(1,1,n,n);
	return 0;
}
```



---

## 作者：_Wind_Leaves_ShaDow_ (赞：5)

### 前言

今天是蒟蒻 Wind_Leaves_ShaDow 尝试狂刷 CF 的第 $2$ 天。

### 正文

一道颜色、题目和代码看上去很恐怖但是非常好写的区间 dp。

首先看数据范围。$n\leq50$。这种数据范围一般都是用来乱搞的。计算一下，$50^5=312,500,000=3.125\times10^8$，对 CF 的评测姬来说根本算不了什么。所以我们考虑 **大力五层循环求解**。

定义 $dp_{a,b,c,d}$ 为覆盖范围为左上角是 $(a,b)$，右下角是 $(c,d)$ 的矩形的最小花费。考虑转移。显然我们 **枚举一个分割点将大矩形分成两块** 然后加法合成。然后有个要注意的点是 **可能合并的价值不如我们直接拿一个大长方形覆盖整个矩形**，在转移的时候要考虑进来这种情况。

但是题目中的价值是取长宽最大值，如果正解覆盖的矩形刚好被分割线分开，这种情况对我们的转移会有影响吗？**不会。**

我们假设在这个矩形在分割线左边有 $a\times b$ 的大小，在分割线右边有 $a\times c$ 的大小，那么有两种可能：

- $a\ge b+c$，此时价值是 $a$。因为是一个一个枚举，在我们枚举的过程中 **一定会有** $a\ge b,c$ 的情况发生。在这个条件下我们确实会得到最小值。

- $a<b+c$，此时价值是 $b+c$。这时候左右枚举是行不通的了。**但是我们还枚举了上下分割线**。在上下枚举的时候很容易找到最小值。

但是通过上证又会得到疑问：如果在左右分割线时有第二种情况发生，这时我们会觉得在上下分割线会得到最小值，如果在上下分割线又出现了第二种情况呢？

比如说下面的样例：

```cpp
7
.......
.#####.
.......
..###..
..###..
..###..
.......
ans:5
```
这时无论怎么枚举分割线都会有 $a<b+c$ 的情况。但是我们如果推一下呢？会发现答案是 $5$。这种情况就是 **覆盖整个矩形**。

至此，应该就没有问题了，给代码：（看上去很长但是很好写，蒟蒻可能有地方写得不好，请各位指正，谢谢啦）

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb(a) push_back(a)
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

using namespace std;
typedef double db;
const int N=60,INF=1e14;

int n,dp[N][N][N][N];
char tmp;
bool a[N][N];

signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)for(int a=1;a<=n;a++)for(int b=1;b<=n;b++)dp[i][j][a][b]=INF;//初始化
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>tmp;
			if(tmp=='#')dp[i][j][i][j]=1;
			else dp[i][j][i][j]=0;//单个点处理
		}
	}
	for(int lx=1;lx<=n;lx++){
		for(int ly=1;ly<=n;ly++){
			for(int a=1;a+lx-1<=n;a++){
				int b=a+lx-1;
				for(int c=1;c+ly-1<=n;c++){//暴力四层枚举
					int d=c+ly-1;
					for(int k=a;k<b;k++)dp[a][c][b][d]=min(dp[a][c][b][d],dp[a][c][k][d]+dp[k+1][c][b][d]);
					for(int k=c;k<d;k++)dp[a][c][b][d]=min(dp[a][c][b][d],dp[a][c][b][k]+dp[a][k+1][b][d]);//枚举分割线
					dp[a][c][b][d]=min(dp[a][c][b][d],max(lx,ly));//与覆盖整个矩形取最小值
				}
			}
		}
	}
	cout<<dp[1][1][n][n];
	return 0;
} 
```

---

## 作者：reyik (赞：3)

显然是一个二维的区间$DP$

十分懒得我使用记忆化搜索实现

我们枚举行和列的分割点，分别递归求解

想普通的记忆化一样遇到搜索过的就不继续

然后

## 注意！

这题的dp数组初始值不能为$0$，因为答案有可能为$0$,所以你要初始值设置成$-1$来判断是否搜索过

code:

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int f[51][51][51][51];
int n,m;
char ch[55][55];
int dfs(int x,int y,int x1,int y1) {//记忆化
	if(f[x][y][x1][y1] != -1) return f[x][y][x1][y1];
	if(x==x1 && y==y1) {
		f[x][y][x1][y1]=(ch[x][y]=='#');
		return f[x][y][x1][y1];
	}
	int res=max(x1-x+1,y1-y+1);
	for (int i=x;i<x1;++i) res=min(res,dfs(x,y,i,y1)+dfs(i+1,y,x1,y1));
	for (int i=y;i<y1;++i) res=min(res,dfs(x,y,x1,i)+dfs(x,i+1,x1,y1));//枚举分割点，分别递归
	f[x][y][x1][y1]=res;
	return res;
}	
int main() {
	memset(f,-1,sizeof(f));
	scanf("%d",&n);
	for (int i=1;i<=n;++i) scanf("%s",ch[i]+1);
	printf("%d\n",dfs(1,1,n,n));
	return 0;
}

```

---

## 作者：Link_Cut_Y (赞：2)

很好的区间 dp 题。

设 $f_{x_0,y_0, x_1, y_1}$ 表示以将左上角为 $x_0, y_0$，右下角为 $x_1, y_1$ 的矩形全部覆盖成 `.` 的最小代价。

枚举 $x_0, y_0, x_1, y_1$。然后考虑区间 dp 的一贯套路，找到一条直线将这个矩形切成两部分。很明显，这条直线可以横着切也可以竖着切。所以枚举 $x_2 \in [x_0, x_1]$，$y_2 \in [y_0, y_1]$，用切开的子矩形转移即可。

使用记忆化搜索实现比较方便。下面是参考代码：

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int N = 52;
int f[N][N][N][N], n;
char s[N][N];

int dfs(int x0, int y0, int x1, int y1) {
	auto &dp = f[x0][y0][x1][y1];
	if (~dp) return dp;
	if (x0 == x1 and y0 == y1)
		return dp = s[x0][y0] == '#';
	dp = max(x1 - x0 + 1, y1 - y0 + 1);
	for (int i = x0; i < x1; i ++ )
		dp = min(dp, dfs(x0, y0, i, y1) + dfs(i + 1, y0, x1, y1));
	for (int i = y0; i < y1; i ++ )
		dp = min(dp, dfs(x0, y0, x1, i) + dfs(x0, i + 1, x1, y1));
	return dp;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ )
		scanf("%s", s[i] + 1);
	memset(f, -1, sizeof f);
	printf("%d\n", dfs(1, 1, n, n));
	return 0;
}
```

---

## 作者：ccrui (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1198D)

看到区间和极小的数据范围，就想到了区间 DP。

设对 DP 状态是关键，我们可以这样设置状态：$dp_{x,y,z,t}$ 表示左上角为 $(x,y)$ ，右下角为 $(z,t)$ 的矩形中所有的 `#` 都被覆盖的最小代价。

对于每一个 $dp_{x,y,z,t}$，我们把它沿 $k$ 竖着分割为 $dp_{x,y,k,t}$ 和 $dp_{k+1,y,z,t}$ 或横着分为 $dp_{x,y,z,k}$ 和 $dp_{x,k+1,z,t}$。

以样例 1 举例:

```
3
##|#
#.|#
##|#
```

$dp_{1,1,3,3}$ 沿 $k=2$ 竖着分割为 $dp_{1,1,2,3}$ 和 $dp_{3,1,3,3}$。


```
3
###
#.#
---
###
```

也可以把它沿 $k=2$ 横着分割为 $dp_{1,1,3,2}$ 和 $dp_{1,3,3,3}$。

现在题目也转换为了一个 $O(n^5)$ 的区间 DP 了。

### AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[100][100],qz[100][100];
int dp[60][60][60][60];
void ghh(int x,int y){
    for(int l=1;l<=n-x+1;l++){//枚举x
		int l2=l+x-1;//对应z
		for(int r=1;r<=n-y+1;r++){//枚举y
			int r2=r+y-1;//对应t
			for(int k=l;k<l2;k++){
                dp[l][r][l2][r2]=min(dp[l][r][l2][r2],dp[l][r][k][r2]+dp[k+1][r][l2][r2]);
                //竖着分割
            }
			for(int k=r;k<r2;k++){
                dp[l][r][l2][r2]=min(dp[l][r][l2][r2],dp[l][r][l2][k]+dp[l][k+1][l2][r2]);
                //横着分割
            }
			dp[l][r][l2][r2]=min(dp[l][r][l2][r2],max(x,y));//直接覆盖
		}
	}
}
signed main(){
    scanf("%lld",&n);
	memset(dp,0x3f,sizeof(dp));//初始化
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            char c;
            cin>>c;
            if(c=='#')dp[i][j][i][j]=1;
            else dp[i][j][i][j]=0;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            ghh(i,j);
        }
    }//区间DP
    printf("%lld",dp[1][1][n][n]);
    return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/128731480)

---

## 作者：Fiendish (赞：1)

题意比较明了，也很容易想到如果一个矩形区域想要被覆盖，那么只有以下三种情况：
1. 被两个横着的矩形覆盖；
2. 被两个竖着的矩形覆盖；
3. 被一个矩形直接覆盖。

考虑完以上三种情况，就比较简单了。直接记搜即可。每次枚举到一个矩形区域，就递归上述的第一、二种情况（第三种情况直接计算记录即可）。最后，输出答案。

贴上丑陋的代码：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int n,a[60][60],f[60][60][60][60];
int dfs(int x,int y,int x1,int y1){
	if(f[x][y][x1][y1]!=-1) return f[x][y][x1][y1];//记忆化，如果记录过直接返回，优化时间
	int ans=max(x1-x+1,y1-y+1);//考虑第三种情况
	if(y1==y&&x1==x&&!a[x][y]) ans=0;
	for(int i=x;i<x1;++i) ans=min(ans,dfs(x,y,i,y1)+dfs(i+1,y,x1,y1));//第一种
	for(int i=y;i<y1;++i) ans=min(ans,dfs(x,y,x1,i)+dfs(x,i+1,x1,y1));//第二种
	return f[x][y][x1][y1]=ans;//同样记忆化
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	memset(f,-1,sizeof f);//f数组赋值为-1，方便递归
	scanf("%d\n",&n);//注意要把换行读入，否则直接WA
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			char ch=getchar();
			if(ch=='#') a[i][j]=1;
		}
		getchar();//同样读换行
	}
	cout<<dfs(1,1,n,n);
}
```

若有疏漏、不详之处，恳请大佬指点。

---

## 作者：Zechariah (赞：1)

数据范围小，直接记忆化搜索  
$dp[lx][rx][ly][ry]$表示将对顶点为$(lx,ly)$和$(rx,ry)$的矩形区域全部染成白色需要的最小代价  
然后就很常规地记搜了
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define jh(x, y) x ^= y ^= x ^= y
#define loc(x, y) (x - 1) * m + y
#define rg register
#define inl inline
#define PI 3.141592654
typedef long long ll;
const int N = 50 + 5, INF = 0x3f3f3f3f, mod = 998244353;
using namespace std;
namespace fast_IO {
	inl ll read() {
		rg char c;
		rg ll x = 0;
		rg bool flag = false;
		while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
		if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
		while ((c = getchar()) != ' ' && c != '\n' && c != '\r' && ~c)
			x = (x << 1) + (x << 3) + (c ^ 48);
		if (flag)return -x; return x;
	}
	inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
int n, dp[N][N][N][N];
char s[N][N];
int dfs(rg int lx, rg int rx, rg int ly, rg int ry) {
	if (~dp[lx][rx][ly][ry])return dp[lx][rx][ly][ry];
	if (lx == rx && ly == ry)return s[lx][ly] == '#';
	rg int ans = fast_IO::max(rx - lx + 1, ry - ly + 1);
	for (rg int i = lx; i < rx; ++i)ans = fast_IO::min(ans, dfs(lx, i, ly, ry) + dfs(i + 1, rx, ly, ry));
	for (rg int i = ly; i < ry; ++i)ans = fast_IO::min(ans, dfs(lx, rx, ly, i) + dfs(lx, rx, i + 1, ry));
	return dp[lx][rx][ly][ry] = ans;
}

int main() {
	n = fast_IO::read();
	memset(dp, -1, sizeof(dp));
	for (rg int i = 1; i <= n; ++i)scanf("%s", s[i] + 1);
	fast_IO::write(dfs(1, n, 1, n));
	return 0;
}

```


---

## 作者：roger_yrj (赞：1)

此题使用记忆化搜索， $f_{x,y,xx,yy}$ 表示覆盖 $(x,y)$ 到 $(xx,yy)$ 这块矩形的最小代价

覆盖一块矩形有两种方法：直接 **整块覆盖** 或 **切开两块** 分别覆盖

两种方法取最小值即可

（ $f$ 一定要初始化为-1！）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[60][60][60][60];
int a[60][60];
int dfs(int x,int y,int xx,int yy){
	if(f[x][y][xx][yy]!=-1)return f[x][y][xx][yy];//记忆化
	int ans=max(xx-x+1,yy-y+1);
	if(yy==y&&xx==x&&!a[x][y])ans=0;//如果分割到最小且不需要覆盖
	for(int i=x;i<xx;i++)ans=min(ans,dfs(x,y,i,yy)+dfs(i+1,y,xx,yy));//横着切
	for(int i=y;i<yy;i++)ans=min(ans,dfs(x,y,xx,i)+dfs(x,i+1,xx,yy));//竖着切
	return f[x][y][xx][yy]=ans;//记忆化
}
int main(){
	memset(f,-1,sizeof(f));//初始化为-1（因为答案可能有0）
	scanf("%d\n",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char c=getchar();
			if(c=='#')a[i][j]=1;
		}
		getchar();
	}
	cout<<dfs(1,1,n,n);
}
```

---

## 作者：_ZHONGZIJIE0608_ (赞：0)

[**博客食用更佳**](https://www.luogu.com.cn/blog/Administator/cf1198d-ti-xie)

这是一道二维的区间 DP 题。

先看一下数据范围。$1 \le n \le 50$，接近暴力。

手算一下可知 $50^{5} = 3.125 \times 10^{8}$，能在 $1$ 秒内运行完毕，则我们得到了一种解法。

考虑 $f_{x_{1},y_{1},x_{2},y_{2}}$ 表示左上角为 $(x_{1},y_{1})$，右下角为 $(x_{2},y_{2})$ 的矩形内的最小代价，则每次可用一条切割线将一个 $H \times W$ 的矩形横向或纵向分割成 $2$ 个部分。

存在性证明：考虑反证法。不妨设 $H \ge W$，显然全部最小代价不超过 $H$。若存在一切割线使得任意一个连续探测区域被破坏，则该方案覆盖任意一列，代价一定不小于 $H$，一定不为最优，舍去该解。

于是，对于所有矩形，枚举横向和纵向的分割线即可。

复杂度 $O(n^{5})$。上代码。

[AC记录](https://www.luogu.com.cn/record/128747278)

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define min(a,b) (a<b?a:b) 
#define max(a,b) (a>b?a:b) 
int n,f[64][64][64][64];
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>n;memset(f,0x3f,sizeof f);
    for(int i=1;i<=n;++i){for(int j=1;j<=n;++j){char c;cin>>c;f[i][j][i][j]=c=='#';}}
    for(int p=1;p<=n;++p){
        for(int x=1;x+p-1<=n;++x){
            int _x=x+p-1;
            for(int q=1;q<=n;++q){
                for(int y=1;y+q-1<=n;++y){
                    int _y=y+q-1;
                    f[x][y][_x][_y]=min(f[x][y][_x][_y],max(_y-y+1,_x-x+1));
                    for(int i=x;i<_x;++i)f[x][y][_x][_y]=min(f[x][y][_x][_y],f[x][y][i][_y]+f[i+1][y][_x][_y]);
                    for(int i=y;i<_y;++i)f[x][y][_x][_y]=min(f[x][y][_x][_y],f[x][y][_x][i]+f[x][i+1][_x][_y]);
                }
            }
        }
    }
    cout<<f[1][1][n][n];
    return 0;
}

```


---

## 作者：FreedomKing (赞：0)

学 ZR C 做到的题，顺手写一篇题解。

### 题目大意

老师给出的翻译：

给定一个 $n\times n$ 的矩阵，有一些格子是黑色的，剩下的全是白色的，每次可以花费 $\max(h,w)$ 的代价把 $h\times w$ 的矩形染成白色，求最小的花费能够把所有格子变成白色。

### 思路

一道有意思的二维区间 DP 题，考虑将 $dp_{x1,y1,x2,y2}$ 设为将矩形 $x1,y1,x2,y2$ 内的格子全部变成白色的代价。

- 初始状态，当格子是白色时，不需要任何修改，得 $dp_{x1,y1,x2,y2}=0$；当格子是黑色时，需要花费 $1$ 的代价将其改边为白色，即 $dp_{x1,y1,x2,y2}=1$。

- 状态转移，考虑将 $dp_{x1,y1,x2,y2}$ 拆分成两个子问题，也就是把它所覆盖的矩形切成两块小矩形，由于可以将大矩形竖着或横着切割所以要用两个循环分开求解，最后更新到大矩形。

- 因为顺序并不明确，所以建议使用搜索实现，需要记忆化优化时间复杂度。

一个小坑点：如果使用 `long long` 有可能会得到 TLE。

### AC Code

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int N=55;
int dp[N][N][N][N],n,m,t,k;
char c[N][N];
int dfs(int x1,int y1,int x2,int y2){
	if(dp[x1][y1][x2][y2]!=-1) return dp[x1][y1][x2][y2];//记忆化
	if(x1==x2&&y1==y2) return dp[x1][y1][x2][y2]=(c[x1][y1]=='#');
	dp[x1][y1][x2][y2]=max(x2-x1+1,y2-y1+1);
	//先设为用最大矩形覆盖的代价
	for(int i=x1;i<x2;i++)//分开讨论两种切割方式
		dp[x1][y1][x2][y2]=min(dp[x1][y1][x2][y2],dfs(x1,y1,i,y2)+dfs(i+1,y1,x2,y2));
	for(int i=y1;i<y2;i++)
		dp[x1][y1][x2][y2]=min(dp[x1][y1][x2][y2],dfs(x1,y1,x2,i)+dfs(x1,i+1,x2,y2));
	return dp[x1][y1][x2][y2];
}
signed main(){
	cin>>n;
	memset(dp,-1,sizeof(dp));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>c[i][j];
	cout<<dfs(1,1,n,n);
	return 0;
}
```

---

## 作者：QianianXY (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1198D)

## 题目分析

用记忆化实现的分治思想，跟 [CF598E](https://www.luogu.com.cn/problem/CF598E) 十分类似，建议一同切掉。

对于本题，我们可以采取分而治之的策略，递归将其沿格线分隔至不可分的方块，最后合并贡献。

对于方块 ``#``，贡献为 $1$，方块 ``.`` 贡献为 $0$。

合并贡献时有两种选择，一种是直接沿用两个小方阵的方案，即贡献相加。

另一种是直接围住这个大方阵，贡献为大方阵最长边的长度。

用 ``min`` 选择贡献最少的一种即可。

由于合并时只有当前小方阵的贡献对大方阵有影响，所以无后效性显然。

## code

$f(x_1,y_1,x_2,y_2)$ 表示左上角为 $(x_1,y_1)$，右下角为 $(x_2,y_2)$ 的方阵的贡献。

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 55
using namespace std;

template <typename T> inline void read(T &x)
{
	x = 0; int f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int n, a[N][N], f[N][N][N][N];
char c;

inline int Dfs(int xa, int ya, int xb, int yb)
{
	if (f[xa][ya][xb][yb] != -1) return f[xa][ya][xb][yb];
	int ret = 1e9;
	for (rei i = xa; i < xb; i++) ret = min(ret, Dfs(xa, ya, i, yb) + Dfs(i + 1, ya, xb, yb));
	for (rei i = ya; i < yb; i++) ret = min(ret, Dfs(xa, ya, xb, i) + Dfs(xa, i + 1, xb, yb));
	ret = min(ret, max(abs(xa - xb) + 1, abs(ya - yb) + 1));
	f[xa][ya][xb][yb] = ret;
	return ret;
}

int main()
{
	read(n); memset(f, -1, sizeof(f)); 
	for (rei i = 1; i <= n; i++) for (rei j = 1; j <= n; j++) cin >> c, f[i][j][i][j] = (c == '#') ? 1 : 0;
	printf("%d", Dfs(1, 1, n, n));
	return 0;
}
```


---

## 作者：cunzai_zsy0531 (赞：0)

### CF1198D题解 by cunzai_zsy0531

------------

[传送门](https://www.luogu.com.cn/problem/CF1198D)

这题是一道典型的区间dp。我们考虑一个矩形 $(x_1,y_1,x_2,y_2)$ (左上和右下角)，它的最小答案显然可以通过从中间切开，左边和右边合并来计算。于是我们得到了一个动态规划基础模型：由小问题得出大问题答案。

设 $f[x_1][y_1][x_2][y_2]$ 为矩形 $(x_1,y_1,x_2,y_2)$ 的最优解。首先初始化 $f[x_1][y_1][x_2][y_2]=\max(x_2-x_1+1,y_2-y_1+1)$

对行列分别考虑有：

对行：$f[x_1][y_1][x_2][y_2]=\max\limits_{k=x_1}^{x_2-1}\{f[x_1][y_1][k][y_2]+f[k+1][y_1][x_2][y_2] \}$

对列：$f[x_1][y_1][x_2][y_2]=\max\limits_{k=y_1}^{y_2-1}\{f[x_1][y_1][x_2][k]+f[x_1][k+1][x_2][y_2] \}$

最后 $f[1][1][n][n]$ 的结果就是整个题的解。

做此类题目要敏锐观察题目中的条件并设计合适合理的状态，看看能否从小状态推至大状态，先通过这个写出暴力dp方程，然后再尝试求解。

AC代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=50+13;
int n,f[N][N][N][N];//f数组就是上面讲的记录答案的数组
char s[N][N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%s",s[i]+1);
		for(int j=1;j<=n;++j) f[i][j][i][j]=(s[i][j]=='#');//对每个点的初始化
	}
	for(int x1=1;x1<=n;++x1)
	for(int y1=1;y1<=n;++y1)
	for(int x2=x1;x2<=n;++x2)//注意x2和y2的下界！
	for(int y2=y1;y2<=n;++y2)
		if(x1!=x2||y1!=y2) f[x1][y1][x2][y2]=max(x2-x1+1,y2-y1+1);
	for(int x1=n;x1>=1;--x1)
	for(int x2=x1;x2<=n;++x2)
	for(int y1=n;y1>=1;--y1)
	for(int y2=y1;y2<=n;++y2){
		for(int k=x1;k<x2;++k) f[x1][y1][x2][y2]=min(f[x1][y1][x2][y2],f[x1][y1][k][y2]+f[k+1][y1][x2][y2]);
		for(int k=y1;k<y2;++k) f[x1][y1][x2][y2]=min(f[x1][y1][x2][y2],f[x1][y1][x2][k]+f[x1][k+1][x2][y2]);
	}
	printf("%d\n",f[1][1][n][n]);
	return 0;
}
```


---

## 作者：xixike (赞：0)

**二维区间DP**

与一维的一样，我们考虑枚举一个区间，用 $lenx$ 枚举行的长度，$lenx$ 枚举列的长度。

再用 $x1$ 枚举行的起点，$y1$ 枚举列的起点，利用长度直接求出行和列的终点 $x2$ 和 $y2$。

里面套两个并列的循环枚举断点，一个枚举行，另一个枚举列。

时间复杂度为 $O(n^5)$，常数较小，可以卡过qwq

行的转移方程为： $dp[x1][y1][x2][y2]=min(dp[x1][y1][x2][y2],dp[x1][y1][k][y2]+dp[k+1][y1][x2][y2])$

列同理。

那么我们该怎样赋初值呢？

- 对于 $a[i][j]=$ $'#'$ ，$dp[i][j][i][j]=1$
- 4层循环枚举每一个区间，对于每一个区间有$dp[x1][y1][x2][y2]=min(x2-x1+1,y2-y1+1)$

**附代码**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

int a[60][60],dp[60][60][60][60];
char s[60];
int n;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=n;j++)
			if(s[j]=='#')
				dp[i][j][i][j]=1; 
	}
	for(int x1=1;x1<=n;x1++)
		for(int y1=1;y1<=n;y1++)
			for(int x2=1;x2<=n;x2++)
				for(int y2=1;y2<=n;y2++){
					if(x1==x2&&y1==y2) continue;
					dp[x1][y1][x2][y2]=max(x2-x1+1,y2-y1+1);
				}
	for(int lenx=1;lenx<=n;lenx++)
		for(int leny=1;leny<=n;leny++)
			for(int x1=1;x1<=n-lenx+1;x1++)
				for(int y1=1;y1<=n-leny+1;y1++){
					int x2=x1+lenx-1;
					int y2=y1+leny-1;
					for(int k=x1;k<x2;k++)
						dp[x1][y1][x2][y2]=min(dp[x1][y1][x2][y2],dp[x1][y1][k][y2]+dp[k+1][y1][x2][y2]);
					for(int k=y1;k<y2;k++)
						dp[x1][y1][x2][y2]=min(dp[x1][y1][x2][y2],dp[x1][y1][x2][k]+dp[x1][k+1][x2][y2]);
				}
	printf("%d\n",dp[1][1][n][n]);
	return 0;
}
```


---

## 作者：liaiyang (赞：0)

很明显的区间 dp。

我们设 $dp_{l,r,u,d}$ 表示左下角为 $(d,l)$ 右上角为 $(u,r)$ 的矩形最小代价。

我们要么一遍填充完，要么枚举分界线，可以得到转移方程
$$dp_{l,r,u,d}=\min(\min_{i=l}^{r-1}dp_{l,i,u,d}+dp_{i+1,r,u,d},\min_{i=u}^{d-1}dp_{l,r,u,i}+dp_{l,r,i+1,d},max(r-l+1,d-u+1))$$

时间复杂度 $O(n^5)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define min(a,b) (a<b?a:b) 
#define P pair<int,int>
#define x first
#define y second
#define modd(x) (((x)%mod+mod)%mod) 
#define rd read()
#define lowbit(x) ((x)&(-x))
mt19937 rnd(time(0));
inline int read(int u=0, char c=getchar(), bool f=false){
    for (;!isdigit(c);c=getchar()) f|=c=='-';
    for (;isdigit(c);c=getchar()) u=(u<<1)+(u<<3)+c-'0';
    return f?-u:u;
}
inline void wt(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) wt(x/10);
    putchar(x%10+48);
}
inline void wt(int x,char k){wt(x),putchar(k);}
const int mod=998244353;
const int N=50+10;
int n,f[N][N][N][N];
char a[N][N];
int dfs(int l,int r,int u,int d){
    if(f[l][r][u][d]!=-1) return f[l][r][u][d];
    if(l==r&&u==d){
        f[l][r][u][d]=(a[l][u]=='#');
        return f[l][r][u][d];
    }
    f[l][r][u][d]=max(r-l+1,d-u+1);
    for(int i=l;i<r;i++) f[l][r][u][d]=min(f[l][r][u][d],dfs(l,i,u,d)+dfs(i+1,r,u,d));
    for(int i=u;i<d;i++) f[l][r][u][d]=min(f[l][r][u][d],dfs(l,r,u,i)+dfs(l,r,i+1,d));
    return f[l][r][u][d];
}
main(){
    n=rd;
    memset(f,-1,sizeof f);
    for(int i=1;i<=n;i++) scanf("%s",a[i]+1);
    wt(dfs(1,n,1,n),'\n');
    return 0;
}
```

---

