# New Year and Domino

## 题目描述

They say "years are like dominoes, tumbling one after the other". But would a year fit into a grid? I don't think so.

Limak is a little polar bear who loves to play. He has recently got a rectangular grid with $ h $ rows and $ w $ columns. Each cell is a square, either empty (denoted by '.') or forbidden (denoted by '\#'). Rows are numbered $ 1 $ through $ h $ from top to bottom. Columns are numbered $ 1 $ through $ w $ from left to right.

Also, Limak has a single domino. He wants to put it somewhere in a grid. A domino will occupy exactly two adjacent cells, located either in one row or in one column. Both adjacent cells must be empty and must be inside a grid.

Limak needs more fun and thus he is going to consider some queries. In each query he chooses some rectangle and wonders, how many way are there to put a single domino inside of the chosen rectangle?

## 说明/提示

A red frame below corresponds to the first query of the first sample. A domino can be placed in 4 possible ways.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF611C/f3a65ee4610730ba07c0a0557d0738988b956aa6.png)

## 样例 #1

### 输入

```
5 8
....#..#
.#......
##.#....
##..#.##
........
4
1 1 2 3
4 1 4 1
1 2 4 5
2 5 5 8
```

### 输出

```
4
0
10
15
```

## 样例 #2

### 输入

```
7 39
.......................................
.###..###..#..###.....###..###..#..###.
...#..#.#..#..#.........#..#.#..#..#...
.###..#.#..#..###.....###..#.#..#..###.
.#....#.#..#....#.....#....#.#..#..#.#.
.###..###..#..###.....###..###..#..###.
.......................................
6
1 1 3 20
2 10 6 30
2 10 7 30
2 2 7 7
1 7 7 7
1 8 7 8
```

### 输出

```
53
89
120
23
0
2
```

# 题解

## 作者：Akoasm_X (赞：11)

**我的做法时间复杂度是O（n * m）,O（n * m）预处理，O( 1 )查询。空间复杂度也是O(n * m).**

[CF611C New Year and Domino](https://www.luogu.com.cn/problem/CF611C)

通过观察题目发现，只要连续两格为空那么方案数+1，对此我们可以考虑每个点的贡献值，维护一个二维的前缀和，从而达到我们所期望的结果。

贡献值的设定：我们记下相邻两个空格靠后或靠下的那一格贡献值为1，循环过程中，只需要对当前为空的位判断左一和上一是否为空，加入贡献即可。

二维前缀和求法是
```cpp
ans = sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1]
```

但是此题并不是这么回事，如果照此查询，我们会将以x1为横坐标的纵向贡献，以y1为纵坐标的横向贡献算入答案，事实上是不正确的。（有图为证）

![题解图解](https://cdn.luogu.com.cn/upload/image_hosting/7y1w2s50.png?x-oss-process=image/resize,m_lfit,h_510,w_675)

对此我只好将横向贡献和纵向贡献分开算前缀和，最后查询即可

代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n,m;
int sum1[520][520],sum2[520][520];
char mp[520][520];

int calc(int a,int b,int c,int d)
{
	int ans = 0;
	a++;
	ans += sum1[c][d] - sum1[a-1][d] - sum1[c][b-1] + sum1[a-1][b-1];
	b++,a--;
	ans += sum2[c][d] - sum2[a-1][d] - sum2[c][b-1] + sum2[a-1][b-1];
	return ans;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",mp[i]+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			sum1[i][j] = sum1[i][j-1] + sum1[i-1][j] - sum1[i-1][j-1];
			sum2[i][j] = sum2[i][j-1] + sum2[i-1][j] - sum2[i-1][j-1];
			if(mp[i][j]=='.')
			{
				if(mp[i-1][j]=='.')
					sum1[i][j]++;//纵向贡献 
				if(mp[i][j-1]=='.')
					sum2[i][j]++;//横向贡献 
			}
		}
	}
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		printf("%d\n",calc(a,b,c,d));
	}
	return 0;
}
```

2020 CSP-S rp++!

---

## 作者：luogu_gza (赞：3)

这是一个 $O(n\times m+q)$ 的做法。

考虑一下每个格子可以向下和向右扩展，如果可以，答案加一。

如何查询一个矩阵的和？

使用二维前缀和。

在代码中，我使用 $s$ 数组代表该格子的贡献。

有个细节，就是超出该矩阵的部分需要减掉（就是一半在里面，一般在外面的部分）。

[$\color{red}{\texttt{ACrecord}}$](https://codeforces.com/contest/611/submission/205326978)

$\color{green}{\texttt{ACcode}}$

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pc putchar
#define R read()
#define fo(i,a,b) for(register int i=a;i<=b;i++)
#define rep(i,a,b) for(register int i=a;i>=b;i--)
#define m1(a,b) memset(a,b,sizeof a)
int read()
{
    int x=0;
    char ch=getchar();
    bool f=0;
    while(!isdigit(ch)){if(ch=='-') f=1;ch=getchar();}
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f) x=-x;
    return x;                                       
}
template<typename T> inline void write(T x)
{
    if(x<0)
    {
        pc('-');
        x=-x;
    }
    if(x>9) write(x/10);
    pc(x%10+'0');
}
const int N=510;
int n,m,q;
char a[N][N];
int s[N][N];
signed main(){
	n=R,m=R;
	fo(i,1,n) scanf("%s",a[i]+1);
	fo(i,1,n) fo(j,1,m) if(a[i][j]=='.') s[i][j]=(a[i+1][j]=='.')+(a[i][j+1]=='.');//计算一个格子的贡献
	fo(i,1,n) fo(j,1,m) s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];//二维前缀和
	q=R;
	while(q--)
	{
		int x=R,y=R,xx=R,yy=R;
		int ans=s[xx][yy]-s[x-1][yy]-s[xx][y-1]+s[x-1][y-1];//基础部分
		fo(i,x,xx) ans-=(a[i][yy]=='.'&&a[i][yy+1]=='.'); //减去一半在里面，一般在外面的
		fo(i,y,yy) ans-=(a[xx][i]=='.'&&a[xx+1][i]=='.'); //减去一半在里面，一般在外面的
		write(ans),puts("");
	}
}
```

---

## 作者：Derpy (赞：3)

## 优雅的前缀和暴力。

这道题我是用了横纵两个方向的前缀和维护一行（或者一列）的一段连续区间内能放下多少个横着（如果是列就是竖着），然后查询的时候就一行一行地扫横着的再一列一列地扫纵行，预处理前缀和时间复杂度h*w,查询总时间复杂度(h*w)*q，算下来就差不多10^8还算是能跑过。~~于是又愉快地水了一道题~~

具体实现还是看代码吧


```cpp
#include<bits/stdc++.h>
#define int long long		//快乐的一行long long(int能不能过不清楚。。没试过） 
#define mx 505
using namespace std;
char mp[mx][mx];//存地图 
int h[mx][mx];//横着的前缀和 
int z[mx][mx];//纵着的前缀和 
signed main()//搭配define食用的signed 
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			char ch=getchar();
			while(ch!='.'&&ch!='#') ch=getchar();//防止读入换行鬼畜什么的 
			mp[i][j]=ch;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=2;j<=m;j++)//横着的从第二列开始算,可以理解为我的判断条件是"如果一个空位左边有空位，那这个空位就可以放下一张多米诺" 
		{
			h[i][j]=h[i][j-1];//基本的前缀和操作 
			if(mp[i][j]=='.'&&mp[i][j-1]=='.') h[i][j]++;//合法就数量++ 
		}
	}
	for(int i=2;i<=n;i++)//和横着一样，判断条件"如果一个空位上分有空位,那这个空位就可以放下一张多米诺" 
	{
		for(int j=1;j<=m;j++)
		{
			z[i][j]=z[i-1][j];
			if(mp[i][j]=='.'&&mp[i-1][j]=='.') z[i][j]++;//同上不赘述 
		}
	}
	int T_T;
	cin>>T_T;
	while(T_T--)
	{
		int c1,c2,c3,c4;
		cin>>c1>>c2>>c3>>c4;
		int ans=0;
		for(int i=c1;i<=c3;i++)//一行一行来 
		{
			ans+=h[i][c4]-h[i][c2];//前缀和之差查询每一行的横着的多米诺 
		}
		for(int i=c2;i<=c4;i++)
		{
			ans+=z[c3][i]-z[c1][i];//每一列竖着的多米诺 
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

## CF611C New Year and Domino 题解

**Upd：修改了错别字。**

### 解题思路

第一眼看上去像暴力枚举，但是枚举的复杂度是 $O(n \times m \times q)$，明显超时。

我用了**前缀和**优化时间复杂度，达到 $O(n \times m + q)$，通过此题。大致思路是先用**二维前缀和**做预处理，然后每一次查询的复杂度就降为了 $O(1)$。

类比一维前缀和，我们可以确定位于 $(r1,c1)$ 到 $(r2,c2)$ 两点之间的这一个长方形可以看作是将从 $(1,1)$ 到 $(r2,c2)$ 这个点的所有放法减去从 $(1,1)$ 到 $(r1,c1)$ 的所有放法。所以，我们可以推出每次查询的结果就是：$x^{r2}_{c2}+x^{r1}_{c1-1}-x^{r1}_{c2}-x^{r2}_{c1-1}+y^{r2}_{c2}+y^{r1-1}_{c1}-y^{r2}_{c1}-y^{r1-1}_{c2}$（在这里，我用 $x$ 表示横着摆的情况，用 $y$ 表示竖着摆的情况）。

注意：在进行前缀和预处理的时候要**考虑多米诺骨牌里面一半外面一半的情况！**

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int h , w , q , b[505][505] , c[505][505] , xa , ya , xb , yb;
char s[505][505];
bool a[505][505];
int main()
{
	ios::sync_with_stdio(0);
	cin >> h >> w;
	for(int i = 1 ; i <= h ; i++)
	{
		for(int j = 1 ; j <= w ; j++)
		{
			cin >> s[i][j];
		}
	}
	for(int i = 1 ; i <= h ; i++)
	{
		for(int j = 1 ; j <= w ; j++)
		{
			if(s[i][j] == '.')
			{
				a[i][j] = 1;
			}
			else
			{
				a[i][j] = 0;
			}
		}
	}
	for(int i = 1 ; i <= h ; i++)
	{
		for(int j = 1 ; j <= w ; j++)
		{
			b[i][j] = b[i][j-1] + b[i-1][j] - b[i-1][j-1];
			c[i][j] = c[i][j-1] + c[i-1][j] - c[i-1][j-1];
			if(a[i][j])
			{
				if(a[i - 1][j])
				{
					b[i][j]++;
				}
				if(a[i][j - 1])
				{
					c[i][j]++;
				}
			}
		}
	}
	cin >> q;
	while(q--)
	{
		cin >> xa >> ya >> xb >> yb;
		cout << b[xb][yb] + b[xa][ya - 1] - b[xa][yb] - b[xb][ya - 1] + c[xb][yb] + c[xa - 1][ya] - c[xb][ya] - c[xa - 1][yb] << endl;
	}
	return 8;
}
```
思路很简单，但是推导过程比较复杂，相信各位神犇也能 $\texttt{AC}$ 这道二维前缀和。

---

## 作者：LKY928261 (赞：2)

## 题目分析

根据题意及样例解释，只需求出放入一个骨牌的方案数即可，即只需求出给定区间内有连续两个空格的位置数。

计算时，按横放及竖放分类计算。直接枚举并判断连续的两个位置是否都是 `.` 并统计。

由于询问次数较多，所以需要使用二维前缀和进行优化。

时间复杂度和空间复杂度均为 $O(nm)$。

## 参考代码

本人的代码非常精简，欢迎借(chao)鉴(xi)。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,q,x,y,u,v,b[505][505],c[505][505],i,j;char a[505][505];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(i=1;i<=n;i++)for(j=1;j<=m;j++)
		cin>>a[i][j];
	for(i=1;i<=n;i++)for(j=1;j<m;j++)
		if(a[i][j]=='.'&&a[i][j+1]=='.')b[i][j+1]=1;
	for(i=1;i<n;i++)for(j=1;j<=m;j++)
		if(a[i][j]=='.'&&a[i+1][j]=='.')c[i+1][j]=1;
	//单独处理
	for(i=1;i<=n;i++)for(j=1;j<=m;j++)
		b[i][j]+=b[i-1][j]+b[i][j-1]-b[i-1][j-1],
		c[i][j]+=c[i-1][j]+c[i][j-1]-c[i-1][j-1];
	//二维前缀和
	cin>>q;
	for(i=0;i<q;i++){
		cin>>x>>y>>u>>v;
		cout<<b[u][v]-b[x-1][v]-b[u][y]+b[x-1][y]+//横放
			  c[u][v]-c[x][v]-c[u][y-1]+c[x][y-1]<<"\n";//竖放
	}
}
```

---

## 作者：_6_awa (赞：1)

题目大意：$q$ 次询问，每次询问一个子矩阵有多少个 $1 \times 2$ 的矩阵满足那个矩阵全部为 `.`。

思路分析：不难发现，$h,w \le 500,q \le 100000$，所以 $\mathcal{O}(q(h + w))$。的复杂度是可以过的。然后我们遍历横着的和竖着的前缀和（分别代表横过来一行中的方案数和竖过来一行的方案数）即可。这里注意：因为选取的矩阵必须在询问的矩阵内，所以前缀和减去的下标得加上一才能保持完整性。

代码如下。

```cpp
#include <iostream>
using namespace std;
char a[505][505];
int b[505][505],c[505][505],n,m,q;
int main()
{
    cin >> n >> m;
    for(int i = 1;i <= n;i ++)
        for(int j = 1;j <= m;j ++)
        {
            cin >> a[i][j];
            if(a[i][j] == '.' && a[i][j - 1] == '.')b[i][j] = b[i][j - 1] + 1;
            else b[i][j] = b[i][j - 1];
            if(a[i][j] == '.' && a[i - 1][j] == '.')c[i][j] = c[i - 1][j] + 1;
            else c[i][j] = c[i - 1][j];//前缀和
        }
    cin >> q;
    while(q --)
    {
        int x,y,x2,y2,sum = 0;
        cin >> x >> y >> x2 >> y2;
        for(int i = x;i <= x2;i ++)sum += b[i][y2] - b[i][y];//求横向个数
        for(int i = y;i <= y2;i ++)sum += c[x2][i] - c[x][i];//求竖向个数
        cout << sum << '\n';
    }
}

---

## 作者：rainbow_cat (赞：1)

### 思路：前缀和    
在这里我们只需要定义两个数组：$dpy$ 代表把多米诺骨牌横着放的方案数与 $dpx$ 代表把多米诺骨牌竖着放的方案数，然后对它们进行前缀和。   
首先，我们逐个判断该格能不能竖着或横着放多米诺骨牌：   
```cpp
if(a[i][j]=='.'&&a[i][j+1]=='.')dpy[i][j+1]=1;
if(a[i][j]=='.'&&a[i+1][j]=='.')dpx[i+1][j]=1;
```
接着，我们进行前缀和初始化：    
```cpp
dpx[i][j]+=dpx[i-1][j]+dpx[i][j-1]-dpx[i-1][j-1];
dpy[i][j]+=dpy[i-1][j]+dpy[i][j-1]-dpy[i-1][j-1];
```    
最后到了重中之重，求解：   

注意在这里求解横向可能性时要将 $sty$ 减一，求解纵向可能性时要将 $stx$ 减一，以防一些一半在里面，一半在外面的方案被计算。   
 **完整代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,dpx[510][510],dpy[510][510],stx,sty,edx,edy;
char a[510][510];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
			if(a[i][j]=='.'&&a[i][j+1]=='.')dpy[i][j+1]=1;
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]=='.'&&a[i+1][j]=='.')dpx[i+1][j]=1;			
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			dpx[i][j]+=dpx[i-1][j]+dpx[i][j-1]-dpx[i-1][j-1];
			dpy[i][j]+=dpy[i-1][j]+dpy[i][j-1]-dpy[i-1][j-1];
		}
	}
	cin>>k;
	for(int i=1;i<=k;i++)
	{
		cin>>stx>>sty>>edx>>edy;
		int ay=dpy[edx][edy]-dpy[stx-1][edy]-dpy[edx][sty]+dpy[stx-1][sty];
		int ax=dpx[edx][edy]-dpx[stx][edy]-dpx[edx][sty-1]+dpx[stx][sty-1];
		cout<<ax+ay<<'\n';
	}
	return 0;
}

```

---

## 作者：zym20249_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF611C)
 
## 题意
给定一个 $h×w$ 的网格矩阵，左上角单元格的坐标为 （$r_1,c_1$），右下角单元格的坐标为（$r_2,c_2$），每个单元格中有一个字符，`.`表示该单元格为空，`#` 表示单元格非空。已知一张多米诺骨牌会覆盖相邻的两个空位。陶陶要进行 $q$ 次询问，每次询问一张 $1×2$ 的多米诺骨牌放到一个子矩阵有多少种不同的方案。一次询问会给出子矩阵左上角的坐标为（$r_1,c_1$）和右下角的坐标（$r_2,c_2$）。

## 思路
使用前缀和的思路。考虑一下每个格子可以向下或右扩展，如果可以，计数器加一。在进行前缀和的时候要考虑多米诺骨牌里一半外一半的情况。时间复杂度为 $O(nm)$。

## code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=510;
ll n,m,q,x,y,u,v,b[maxn][maxn],c[maxn][maxn],i,j;char a[maxn][maxn];
int main()
{
	ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(i=1;i<=n;i++)
      for(j=1;j<=m;j++)
  		cin>>a[i][j];
	for(i=1;i<=n;i++)
      for(j=1;j<m;j++)
  		if(a[i][j]=='.'&&a[i][j+1]=='.')b[i][j+1]=1;
	for(i=1;i<n;i++)
      for(j=1;j<=m;j++)
  		if(a[i][j]=='.'&&a[i+1][j]=='.')c[i+1][j]=1;
	for(i=1;i<=n;i++)
    for(j=1;j<=m;j++)
		b[i][j]+=b[i-1][j]+b[i][j-1]-b[i-1][j-1],
		c[i][j]+=c[i-1][j]+c[i][j-1]-c[i-1][j-1];
	cin>>q;
	for(i=0;i<q;i++)
    {
		cin>>x>>y>>u>>v;
		cout<<b[u][v]-b[x-1][v]-b[u][y]+b[x-1][y]+c[u][v]-c[x][v]-c[u][y-1]+c[x][y-1]<<endl;
	}
}
```

---

## 作者：QWQ_123 (赞：0)

显然的，看到只放一个，可以转向，就分别计算横向的和竖向的方案数。

那么实际上就是二维前缀和。

不过查询的时候要注意一下，就是在求横的贡献时左上角 $x$ 要加一，求纵的时候左上角 $y$ 要加一，不然的话就有可能算出去（因为 $f_{i,j}$ 表示的是以 $i,j$ 为终点的，所以若计算横向的时候 $x$ 不加一，那么可能将 $(x,y),(x-1,y)$ 也算到贡献中；纵向同理）。

```cpp
// Problem: C. New Year and Domino
// Contest: Codeforces - Good Bye 2015
// URL: https://codeforces.com/problemset/problem/611/C
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// Begin solve time: 2024-04-14 20:02:09
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

int n, m;
char a[510][510];
int f[510][510], g[510][510];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%s", a[i] + 1);

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			f[i][j] = f[i][j - 1] + f[i - 1][j] - f[i - 1][j - 1] + (a[i][j] == a[i][j - 1]) * (a[i][j] == '.');
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			g[i][j] = g[i][j - 1] + g[i - 1][j] - g[i - 1][j - 1] + (a[i][j] == a[i - 1][j]) * (a[i][j] == '.');
		}
	}
	
	int q; scanf("%d", &q);

	for (int i = 1; i <= q; ++i) {
		int x, y, X, Y; scanf("%d%d%d%d", &x, &y, &X, &Y);
		printf("%d\n", f[X][Y] - f[x - 1][Y] - f[X][y] + f[x - 1][y] + g[X][Y] - g[x][Y] - g[X][y - 1] + g[x][y - 1]);
	}

	return 0;
}
```

---

## 作者：lovely_hyzhuo (赞：0)

很荣幸在 2023 年年末做到了 Good Bye 2015 的题目，在此，Good bye 2023。



------------

以上是题外话。

这题是一个二维前缀和题目。

首先我们需要知道二维前缀和的算法。

定义 $sum_{i,j}$ 表示 $(1,1)$ 到 $(i,j)$ 的和。

对于 $sum_{i,j}$ 和 $sum_{i-1,j-1}$ 和 $sum_{i,j-1}$ 以及 $sum_{i-1,j}$。

可以发现 $sum_{i,j-1}$ 和 $sum_{i-1,j}$ 的和，即 $sum_{i,j-1}+sum_{i-1,j}$ 可以发现这个东西比 $sum_{i,j}$ 多贡献了一个 $sum_{i-1,j-1}$，减掉即可。

最终递推式：

$sum_{i,j}=sum_{i-1,j}+sum_{i,j-1}-sum_{i-1,j-1}+t$。

注：$t$ 是该点的点贡献。

求点 $(a,b)$ 到点 $(c,d)$ 的贡献即为 $sum_{c,d}-sum_{c,b-1}-sum_{a-1,d}+sum_{a-1,b-1}$

所以这题就非常一眼，对于该点只要连续两格为空那么方案数 $+1$，于是我们可以考虑每个点的贡献值，维护一个二维的前缀和。

然而有部分会多算，所以，对于这个题，我们并不能这么算。

~~借用一下第一篇题解的图。~~

![](https://cdn.luogu.com.cn/upload/image_hosting/qlsru1o0.png)

所以可以分开计算横向贡献和纵向贡献，处理询问。

```cpp
#include<bits/stdc++.h>
using namespace std;
char c[1010][1010];
int sum1[1010][1010];
int sum2[1010][1010];
void solve()
{
	int a,b,c,d;
	cin>>a>>b>>c>>d;
	int ans=0;
	a++;
	ans+=sum1[c][d]-sum1[a-1][d]-sum1[c][b-1]+sum1[a-1][b-1];
	b++,a--;
	ans+=sum2[c][d]-sum2[a-1][d]-sum2[c][b-1]+sum2[a-1][b-1];
	cout<<ans<<"\n";
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>c[i][j];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(c[i][j]==c[i-1][j]&&c[i-1][j]=='.')
				sum1[i][j]++;
			if(c[i][j]==c[i][j-1]&&c[i][j-1]=='.')
				sum2[i][j]++;
			sum1[i][j]+=sum1[i][j-1]+sum1[i-1][j]-sum1[i-1][j-1];
			sum2[i][j]+=sum2[i][j-1]+sum2[i-1][j]-sum2[i-1][j-1];
		}
	}
	int q;
	cin>>q;
	while(q--)
		solve();
	return 0;
}
```


---

## 作者：_smart_stupid_ (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF611C)


### 思路：
此题就是一道前缀和，分别考虑横着放骨牌和竖着放骨牌的方法法。

使用两个前缀和数组 $sum1$，$sum2$，$sum1[i][j]$ 记录矩阵第 $1$ 行第 $1$ 列到第 $i$ 行第 $j$ 列横着放骨牌的方法，$sum2[i][j]$ 记录矩阵第 $1$ 行第 $1$ 列到第 $i$ 行第 $j$ 列竖着放骨牌的方法。
计算公式还是和二维前缀和的计算公式一样。

#### 二维前缀和计算公式：

$
sum[i][j] = sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1]+a[i][j];$


然后就是 $x1$，$x2$ 到 $y1$，$y2$ 区间摆放方法计算公式。

先计算横着摆放的方法，再计算竖着摆放的方法。

### 注意：

在计算摆放方法时，横着放要将 $y1$ 减去 $1$，竖着放要将 $x1$ 减去 $1$。

原因：

假如图长这样：
```
....
....
....
....
```
$x1=2,y1=2,x2=3,y2=3$，

那么像这样起始点在 $x1$ 摆放的骨牌：
```
....
.##.
....
....
```

会被忽略掉。

竖着摆放同理。

## Final Code:
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<list>
using namespace std;
int h,w,q;
string a[510];
int sum1[510][510],sum2[510][510];
int main(){
	scanf("%d%d",&h,&w);
	for(int i=1;i<=h;i++){
		a[i].resize(550);
		scanf("%s",&a[i][1]);
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			sum1[i][j] = sum1[i][j-1] + sum1[i-1][j] - sum1[i-1][j-1];
			sum2[i][j] = sum2[i][j-1] + sum2[i-1][j] - sum2[i-1][j-1];
			if(a[i][j]=='.')
			{
				if(a[i-1][j]=='.')
					sum1[i][j]++;
				if(a[i][j-1]=='.')
					sum2[i][j]++;
			}
		}
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		int x1,y1,x2,y2;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		int ans=0;
		ans += sum1[x2][y2] - sum1[x1][y2] - sum1[x2][y1-1] + sum1[x1][y1-1];
		ans += sum2[x2][y2] - sum2[x1-1][y2] - sum2[x2][y1] + sum2[x1-1][y1];
		printf("%d\n",ans);
	}
	return 0;
}
```




这个题我觉得难度才黄题左右。

---

