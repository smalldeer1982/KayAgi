# [AGC004E] Salvage Robots

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc004/tasks/agc004_e

縦 $ H $ 行、横 $ W $ 列のマス目があります。 上から $ i $ ($ 1\ <\ =i\ <\ =H $) 行目、左から $ j $ ($ 1\ <\ =j\ <\ =W $) 列目のマスの情報は、文字 $ a_{ij} $ によって次のように表されます。

- `.` : 空きマスである。
- `o` : ロボットが $ 1 $ 個置かれたマスである。
- `E` : 出口のあるマスである。 `E` はマス目全体にちょうど $ 1 $ 個含まれる。

高橋君は次の操作を何回か行い、できるだけ多くのロボットを救出しようとしています。

- 上下左右のうちどれかひとつの向きを選び、すべてのロボットをその向きへ 1 マスだけ移動させる。 このとき、出口のあるマスへ移動したロボットは直ちに救出され、マス目から消える。 また、マス目の外へ移動したロボットは直ちに爆発し、マス目から消える。

高橋君が救出できるロボットの個数の最大値を求めてください。

## 说明/提示

### 制約

- $ 2\ <\ =H，W\ <\ =100 $
- $ a_{ij} $ は `.`，`o`，`E` のどれかである。
- `E` はマス目全体にちょうど $ 1 $ 個含まれる。

### Sample Explanation 1

例えば、左、上、右の順にロボットを移動させればよいです。

### Sample Explanation 3

右、右、右、下、下の順にロボットを移動させればよいです。

## 样例 #1

### 输入

```
3 3
o.o
.Eo
ooo```

### 输出

```
3```

## 样例 #2

### 输入

```
2 2
E.
..```

### 输出

```
0```

## 样例 #3

### 输入

```
3 4
o...
o...
oooE```

### 输出

```
5```

## 样例 #4

### 输入

```
5 11
ooo.ooo.ooo
o.o.o...o..
ooo.oE..o..
o.o.o.o.o..
o.o.ooo.ooo```

### 输出

```
12```

# 题解

## 作者：Reanap (赞：14)

图片搬运来源：官方

首先我们转化问题：

我们让机器人挪动其实等价于我们让出口移动，出口自带一个框，出过框的机器人就死了，终点抵达的机器人就出去了。

如图，我们定义以下$l,r,u,d$四个参数，表示出口$E$向四个方向所能抵达的最远的位置。显然，在最优情况下必然存在出口跑成一个矩形（因为把不规则的最优方案多跑几步变成矩形不影响答案）

我们尝试考虑这么跑所带来的影响。

![1331002-20181224121129183-2116200572.png](https://i.loli.net/2020/08/03/lxiXVqtn3MPjUmb.png)

如下图，纯红色区域的机器人都死了，红配黄的可能死了，可能被救了，总之，红色区域我们必然已经处理过了，不用管。

现在我们想要转移我们的状态，因此我们可以往上下左右四个方向扩展。

![1331002-20181224121722811-646710850.png](https://i.loli.net/2020/08/03/V5ywHTb7LFzdajX.png)

如下图，这张图中我们往右边和下面进行扩展，我们定义$f_{l,r,u,d}$表示上图的答案，那么下图中就可以转移出两个状态。分别是：

$f_{l,r+1,u,d}=\max(f_{l,r,u,d}+sum_{green})$

$f_{l,r,u,d+1}=\max(f_{l,r,u,d}+sum_{purple})$

![1331002-20181224144446105-147680700.png](https://i.loli.net/2020/08/03/r4pEA2GdDCB9Zmz.png)

显然我们在实际操作中不仅仅需要处理这两种情况，还有上下左右四种情况。

那么我们来根据上图来讨论一下上下左右四个方向出现白色空地的条件：

设$E$坐标为$(x,y)$

上：当且仅当$u+d < x-1$

下：当且仅当$u+d < n-x$

左：当且仅当$l+r < y-1$

右：当且仅当$l+r < m-y$

由于添加的方格必然是连续的行或列，因此，我们可以用前缀和计算（注意不要把红色部分也算进去了~）

在代码实现中，空间显然开不下，我们可以考虑使用$short$储存，然后强制类型转化来卡空间。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int n , m , x , y , v[105][105][2];
short f[105][105][105][105];
signed main() {
	scanf("%d %d" , &n , &m);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			char s = getchar();
			while(s != 'o' && s != '.' && s != 'E') s = getchar();
			if(s == 'E') x = i , y = j;
			else if(s == 'o') {
				v[i][j][0] = v[i - 1][j][0] + 1;
				v[i][j][1] = v[i][j - 1][1] + 1;
			}
			else {
				v[i][j][0] = v[i - 1][j][0];
				v[i][j][1] = v[i][j - 1][1];
			}
		}
	}
	int ans = 0;
	for (int l = 0; l <= y - 1; ++l) {
		for (int r = 0; r <= m - y; ++r) {
			for (int u = 0; u <= x - 1; ++u) {
				for (int d = 0; d <= n - x; ++d) {
					ans = max(ans , (int)f[l][r][u][d]);
					if(l + r < y - 1) f[l + 1][r][u][d] = max((int)f[l + 1][r][u][d] , (int)f[l][r][u][d] + v[min(x + d , n - u)][y - l - 1][0] - v[max(x - u - 1 , d)][y - l - 1][0]);
					if(l + r < m - y) f[l][r + 1][u][d] = max((int)f[l][r + 1][u][d] , (int)f[l][r][u][d] + v[min(x + d , n - u)][y + r + 1][0] - v[max(x - u - 1 , d)][y + r + 1][0]);
					if(u + d < x - 1) f[l][r][u + 1][d] = max((int)f[l][r][u + 1][d] , (int)f[l][r][u][d] + v[x - u - 1][min(y + r , m - l)][1] - v[x - u - 1][max(y - l - 1 , r)][1]);
					if(u + d < n - x) f[l][r][u][d + 1] = max((int)f[l][r][u][d + 1] , (int)f[l][r][u][d] + v[x + d + 1][min(y + r , m - l)][1] - v[x + d + 1][max(y - l - 1 , r)][1]);
				}
			}
		}
	}
	printf("%d" , ans);
	return 0;
}
```


---

## 作者：Ebola (赞：4)

### 题意

你有一个$n\times m$的格子，格子里面有一些是空地，有一些是机器人，还有一个逃生出口。你可以命令所有的机器人一起向某个方向移动一步，移动到格子外面的机器人会死，移动到逃生出口的机器人会得救（得救后这个机器人从格子中消失），请你拯救尽可能多的机器人，输出最多能拯救的数量

### 题解

问题转化一下。我们想象逃生出口拖着一个矩形网格在移动。设$f_{u,d,l,r}$表示这个矩形曾经往上最多走了$u$格，往下最多走了$d$格，往左最多走了$l$格，往右最多走了$r$格。矩形所扩展到的范围，都是能够拯救的范围。

那么每往上扩展一格，我们需要在原矩形的基础上增加一行，行的范围是矩形的宽度，往下同理。往左扩展一格，我们需要在原矩形的基础上增加一列，列的范围是矩形的高度，往右同理。

每扩展一些范围，就要将扩展的范围里面包含的机器人数量加进来。求扩展范围内包含多少机器人，需要一个基于行的前缀和以及基于列的前缀和来优化一下

扩展时需要判断是否能够将扩展范围的机器人数量加上。举一个例子来说，假如我往右扩展了$r$格，那么往左扩展到的列数假如小于等于$r$（注意不是扩展那么多列，而是扩展到第几列），显然这些机器人已经死了，不能加上来。这些判断及其繁琐，需要一些恶心又无聊的推导。具体的还是看代码比较好

```cpp
#include<bits/stdc++.h>
using namespace std;

inline void upmax(short &x,const short &y){if(y>x) x=y;}

const int N=105;
short f[N][N][N][N];
short sum1[N][N],sum2[N][N];
int n,m,tx,ty;

void gao()
{
	int limu=tx-1,limd=n-tx,liml=ty-1,limr=m-ty;
	for(int u=0;u<=limu;u++)
		for(int d=0;d<=limd;d++)
			for(int l=0;l<=liml;l++)
				for(int r=0;r<=limr;r++)
				{
					int L=max(ty-l,r+1),R=min(ty+r,m-l);
					if(L<=R)
					{
						upmax(f[u+1][d][l][r],f[u][d][l][r]+(tx-u-1>=d+1?sum1[tx-u-1][R]-sum1[tx-u-1][L-1]:0));
						upmax(f[u][d+1][l][r],f[u][d][l][r]+(tx+d+1<=n-u?sum1[tx+d+1][R]-sum1[tx+d+1][L-1]:0));
					}
					L=max(tx-u,d+1),R=min(tx+d,n-u);
					if(L<=R)
					{
						upmax(f[u][d][l+1][r],f[u][d][l][r]+(ty-l-1>=r+1?sum2[R][ty-l-1]-sum2[L-1][ty-l-1]:0));
						upmax(f[u][d][l][r+1],f[u][d][l][r]+(ty+r+1<=m-l?sum2[R][ty+r+1]-sum2[L-1][ty+r+1]:0));
					}
				}
	printf("%d\n",f[limu][limd][liml][limr]);
}

int main()
{
	static char s[105];
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)
		{
			if(s[j]=='E') tx=i,ty=j;
			sum1[i][j]=sum1[i][j-1]+(s[j]=='o');
			sum2[i][j]=sum2[i-1][j]+(s[j]=='o');
		}
	}
	gao();
	return 0;
}
```

---

## 作者：jucason_xu (赞：2)

第一步 ~~运用物理上的相对运动~~ 转化题意，我们把“所有机器人移动”转化成“出口带着边框移动”，而在出口运动过程中超出边框的机器人，就“死”了。

然后我们发现，出口运动过程中，假设出口目前走到的最左边的列是 $l$，以此类推定义 $r,u,d$，那么设一开始出口离四个方向边框的距离分别是 $ml,mr,mu,md$，那么对于 __边框之外一定不会已经被遇到__ 的机器人而言，只要大于 $l+mr-1$，其贡献就已经变成 $0$ 了，不会再产生贡献了。而我们目前在 $l,r,u,d$ 限定的范围内运动，__一定不会导致本来存活的机器人在移动后死亡__。

那么，我们就可以设为 $dp_{l,r,u,d}$ 表示当前出口走到的最左边的列是 $l$，类似定义 $r,u,d$，拯救的机器人个数最大值。

然后我们枚举当前往下是往上下左右哪个方向扩展。我们发现，如果我们往 $l-1$ 列扩展，只要 $u$ 和 $d$ 的最值不改变，我们可以在这一列任意移动。所以我们就可以钦定当前机器人已经可以在 $\{l,r,u,d\}$ 限定范围内移动且在这个范围内移动不会造成新贡献，并且往 $l-1$ 转移就计算整个 $l-1$ 列上 $[u,d]$ 的所有格子的贡献。

而 $l-1$ 列上的有贡献的格子是一段区间 $[U,D]$，$U$ 首先要满足大于等于 $u$，其次要满足 $d-mu+1\le U$。$D$ 同理。有且仅有子矩形 $\{l-1,l-1,U,D\}$ 内的点会产生贡献，可以直接使用二维前缀和 $O(1)$ 求出。

然后同理可得 $r,u,d$ 的转移。这样的复杂度是 $O(n^3)$，乍一看常数不小，四次转移，每次做一次二维前缀和。但是实际上，我们只要剪掉所有贡献为 $0$ 的转移，就可以了。因为我们相当于剪掉了所有处在某一端点向机器人已经死绝的方向转移的所有转移，而这类转移在任何的图上都会出现在 $\dfrac{3}{4}$ 的转移里。

```cpp
int n,m,a[105][105],ansx,ansy;
int dp[105][105][105][105];
int ml,mr,mu,md;
int sum[105][105],tmp[105];
st s;
inline void upd(int &x,int y){
	x=max(x,y);
}
inline int query(int x,int y,int xx,int yy){
	if(x>xx||y>yy||x<1||y<1)return 0;
	return sum[xx][yy]-sum[xx][y-1]-sum[x-1][yy]+sum[x-1][y-1];
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m;
	rp(i,n){
		cin>>s;
		rp(j,m){
			if(s[j-1]=='o')a[i][j]=1;
			else if(s[j-1]=='E')ansx=i,ansy=j;
		}
	}
	ml=ansy,mr=m-ansy+1,mu=ansx,md=n-ansx+1;
	rp(i,n){
		rp(j,m){
			tmp[j]=tmp[j-1]+a[i][j];
			sum[i][j]=sum[i-1][j]+tmp[j];
		}
	}int ans=0;
	per(l,1,ansy)rep(r,ansy,m){
		per(u,1,ansx)rep(d,ansx,n){
			int res=dp[l][r][u][d];
			ans=max(ans,res);
			if(l-1>=r-ml+1){
				int U=max(u,d-mu+1),D=min(d,u+md-1);
				upd(dp[l-1][r][u][d],res+query(U,l-1,D,l-1));
			}
			if(r+1<=l+mr-1){
				int U=max(u,d-mu+1),D=min(d,u+md-1);
				upd(dp[l][r+1][u][d],res+query(U,r+1,D,r+1));
			}
			if(u-1>=d-mu+1){
				int L=max(l,r-ml+1),R=min(r,l+mr-1);
				upd(dp[l][r][u-1][d],res+query(u-1,L,u-1,R));
			}
			if(d+1<=u+md-1){
				int L=max(l,r-ml+1),R=min(r,l+mr-1);
				upd(dp[l][r][u][d+1],res+query(d+1,L,d+1,R));
			}
		}
	}cout<<ans<<endl;
	return 0;
}
//Crayan_r
```


---

## 作者：zhiyangfan (赞：1)

推销博客：[qwq](https://www.luogu.com.cn/blog/i-am-zhiyangfan/atcoder-grand-contest-004-zuo-ti-zong-jie)
### 题意
有一个 $n\times m$ 的网格图，其中每个格子可能有以下三种状态：
- 这个格子是空的。
- 这个格子是出口，整个网格图中出口有且仅有一个。
- 这个格子里有一个机器人。

现在想通过以下操作把尽可能多的机器人送到出口：
- 选择上下左右四个方向的一个，然后所有机器人沿着这个方向行进一步。如果一个机器人在到达出口前走到了边界外，它就会爆炸消失。

问最多能把多少机器人送到出口。($2\le n,m\le100$)
### 题解
发现一堆机器人的状态不好描述，所以我们反向考虑，不移动机器人，而是去移动整个网格图和出口，并描述出口的移动情况。注意到描述出口移动情况的关键在于它移动的最远端。具体来讲，我们用一个四元组 $(l,r,d,u)$ 表示出口往左最多移动了 $l$ 格，往右 $r$，往下 $d$，往上 $u$。而这样的话，从上边界往下 $d$ 格，从下边界往上 $u$ 格，从左边界往右 $r$ 格，从右边界往左 $l$ 格都是已经出界过的地方，里面不可能有机器人了，有可能是爆炸了，有可能在爆炸前到出口了。当然，出口经过的地方也没有机器人了，因为它们出去了。总的来说，如下图（又来自 AT），黄色部分是出口到达的地方，红色部分是没有机器人的地方：

![](https://cdn.luogu.com.cn/upload/image_hosting/jqucrd3s.png)

换句话说，上图中所有带颜色的格子都不会有机器人，白色格子里面机器人还是原来的样子。考虑设 $f_{l,r,u,d}$ 表示当前状态用 $(l,r,u,d)$ 描述时能救出多少机器人。则转移即为尝试拓展这个黄色的部分并计算贡献。具体来讲，我们分别尝试把黄色部分往四个方向拓展一格，则新救下的机器人即为新拓展的黄色部分和原来白色部分的交集。如下图（还是来自 AT），当往下拓展一格，可以救下紫色部分的机器人，当往右拓展一格可以救下绿色部分的机器人，往其他方向拓展不能救下新机器人：

![](https://cdn.luogu.com.cn/upload/image_hosting/xpa7yai7.png)

直接 $\mathcal{O}(n^2m^2)$ 转移即可，具体细节见代码。
```cpp
#include <cstdio>
#include <algorithm>
//话说我写题解的时候才发现开了个 1e8 的 int 数组，但居然空间用的不是很大？
const int N = 110; int f[N][N][N][N], v[N][N][2]; char s[N];
int main()
{
	int n, m, x, y, ans = 0; scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%s", s + 1); //计算列/行机器人的前缀和方便计算转移
		for (int j = 1; j <= m; ++j)
		{
			if (s[j] == 'E') x = i, y = j;
			else
			{
				v[i][j][0] = v[i - 1][j][0] + (s[j] == 'o');
				v[i][j][1] = v[i][j - 1][1] + (s[j] == 'o');
			}
		}
	}
    //这里底下转移的时候取 min/max 其实就是计算白色部分。具体来讲就是红色边界和黄色边界取一个 min/max。
	for (int l = 0; l < y; ++l)
		for (int r = 0; r <= m - y; ++r)
			for (int u = 0; u < x; ++u)
				for (int d = 0, s; d <= n - x; ++d)
				{
                                        //最终答案即为所有状态取 max
					ans = std::max(ans, s = f[l][r][u][d]);
					if (l + r < y - 1)
						f[l + 1][r][u][d] = std::max(f[l + 1][r][u][d], 
						s + v[std::min(x + d, n - u)][y - l - 1][0] - 
						v[std::max(x - u - 1, d)][y - l - 1][0]);
					if (l + r < m - y)
						f[l][r + 1][u][d] = std::max(f[l][r + 1][u][d],
						s + v[std::min(x + d, n - u)][y + r + 1][0] - 
						v[std::max(x - u - 1, d)][y + r + 1][0]);
					if (u + d < x - 1)
						f[l][r][u + 1][d] = std::max(f[l][r][u + 1][d],
						s + v[x - u - 1][std::min(y + r, m - l)][1] -
						v[x - u - 1][std::max(y - l - 1, r)][1]);
					if (u + d < n - x)
						f[l][r][u][d + 1] = std::max(f[l][r][u][d + 1],
						s + v[x + d + 1][std::min(y + r, m - l)][1] - 
						v[x + d + 1][std::max(y - l - 1, r)][1]);
				}
	printf("%d\n", ans); return 0;
}
```

---

## 作者：KokiNiwa (赞：1)

[博客园食用体验更佳](https://www.cnblogs.com/YouthRhythms/p/13586271.html)
## 题目链接

[点击打开链接](https://atcoder.jp/contests/agc004/tasks/agc004_e)

## 题解

可以将题目看作出口在移动。如果出口最初的位置为 $(r_0,c_0)$ （第 $r$ 行第 $c$ 列），某一时刻位置为 $(x,y)$ ，那么对于一个机器人 $(p,q)$ ，如果 $p\le x-r_0$ 或者 $p\ge x+H-c_0$ 或者 $q\le y-c_0$ 或者 $q \ge y+W-c_0$ ，那么他已经死掉了。

设 $f_{l,r,u,d}$ 表示历史上出口到达过的最小行坐标为 $r_0-l$ ，最大行坐标为 $r_0+r$ ，最小列坐标为 $c_0-u$ ，最大列坐标为 $c_0+d$ 。我们可以通过 $l,r,u,d$ 计算出哪些范围内的机器人没有被吃掉。

转移直接将 $l,r,u,d$ 之中的一个挪动一格。

具体地，$f_{l,r,u,d}\rightarrow f_{l+1,r,u,d}+s$ ，其中 $s$ 为新拯救的一行的一部分的和。

实现的话，仁者见仁，智者见智了。

这题有点卡空间，可以这样：

+ 用 `short` 存储 `dp` 数组
+ 其实有用的部分只有 $r_0\cdot c_0\cdot (H-r_0)\cdot (W-c_0)$ 这么多个，很明显用均值不等式就可以推出最多 $50^4$ 个有用部分。大概写个哈希就行，不过只用上一个优化就能过了。

## 代码

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NH = 105, NW = 105;
int H, W, r0, c0;
char mp[NH][NW];
short dp[105][105][105][105];
int sum[NH][NW];
int GetSum(int r1, int c1, int r2, int c2) {
	return sum[r2][c2] - sum[r1 - 1][c2] - sum[r2][c1 - 1] + sum[r1 - 1][c1 - 1];
}
int max(int x, int y) { return (x > y) ? x : y; }
int min(int x, int y) { return (x < y) ? x : y; }
int main() {
	scanf("%d%d", &H, &W);
	for (int i = 1; i <= H; ++i) scanf("%s", mp[i] + 1);
	for (int i = 1; i <= H; ++i)
		for (int j = 1; j <= W; ++j)
			if (mp[i][j] == 'E') {
				r0 = i;
				c0 = j;
				break ;
			}
	for (int i = 1; i <= H; ++i)
		for (int j = 1; j <= W; ++j)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (mp[i][j] == 'o');
	memset(dp, 0x8f, sizeof(dp));
	dp[0][0][0][0] = 0;
	int ans = 0;
	for (int s = 0; s <= H - 1 + W - 1; ++s)
		for (int l = 0; l <= c0 - 1; ++l)
			for (int r = 0; r <= W - c0 && l + r <= s; ++r)
				for (int u = 0; u <= r0 - 1 && l + r + u <= s; ++u) {
					int d = s - l - r - u;
					if (r0 + d > H || d < 0) continue ;
					int lu, ld, ll, lr;
					lu = max((r0 + d) - (r0 - 1), 1);
					ld = min((r0 - u) + (H - r0), H);
					ll = max((c0 + r) - (c0 - 1), 1); //这开始写错了
					lr = min((c0 - l) + (W - c0), W);
					int r1, c1, r2, c2;
					r1 = r0 - u;
					c1 = c0 - l;
					r2 = r0 + d;
					c2 = c0 + r;
					if (r1-1 >= 1) {
						int u1 = u + 1;
						if (r1-1 >= lu) {
							dp[l][r][u1][d] = max(dp[l][r][u1][d], dp[l][r][u][d] + GetSum(r1-1, max(ll, c1), r1-1, min(lr, c2)));
						} else dp[l][r][u1][d] = max(dp[l][r][u1][d], dp[l][r][u][d]);
					}
					if (r2+1 <= H) { //这不是 else if
						int d1 = d + 1;
						if (r2+1 <= ld) {
							dp[l][r][u][d1] = max(dp[l][r][u][d1], dp[l][r][u][d] + GetSum(r2+1, max(ll, c1), r2+1, min(lr, c2)));
						} else dp[l][r][u][d1] = max(dp[l][r][u][d1], dp[l][r][u][d]);
					}
					if (c1-1 >= 1) {
						int l1 = l + 1;
						if (c1-1 >= ll) {
							dp[l1][r][u][d] = max(dp[l1][r][u][d], dp[l][r][u][d] + GetSum(max(lu, r1), c1-1, min(ld, r2), c1-1));
																						//这里的取 max要注意
						} else dp[l1][r][u][d] = max(dp[l1][r][u][d], dp[l][r][u][d]);
					}
					if (c2+1 <= W) {
						int rr1 = r + 1;
						if (c2+1 <= lr) {
							dp[l][rr1][u][d] = max(dp[l][rr1][u][d], dp[l][r][u][d] + GetSum(max(lu, r1), c2+1, min(ld, r2), c2+1));
						} else dp[l][rr1][u][d] = max(dp[l][rr1][u][d], dp[l][r][u][d]);
					}
					ans = max(dp[l][r][u][d], ans);
				}
	printf("%d\n", ans);
	return 0;
}

```



---

## 作者：_ZSR_ (赞：0)

### [[AGC004E] Salvage Robots](https://www.luogu.com.cn/problem/AT_agc004_e)

一种很常规的套路，考虑机器人的移动太麻烦了，我们考虑出口的移动。显然，出口的最优移动路径一定可以是矩形，因为如果不是矩形，我们可以把它变成矩形，这样遍历过的格子一定更多，答案一定不会更劣。

于是可以令 $f_{l,r,u,d}$ 表示出口遍历完了其初始所在格子上面 $u$ 格，下面 $d$ 格，左边 $l$ 格，右边 $r$ 格的矩形后最多可以救多少机器人。看图会更清楚一些。

![](https://cdn.luogu.com.cn/upload/image_hosting/runqosba.png)

由于出口向上走就相当于所有机器人向下走，其他方向类似，所以我们又可以得到这样一张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/93l7735q.png)

其中只有红色覆盖的区域的机器人一定没有被救，只有黄色覆盖的区域的机器人一定被救了，既被红色覆盖又被黄色覆盖的区域的机器人可能被救，也可能没有。

考虑转移。再放一张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/5z41an2l.png)

如果我们向下转移，我们就可以获得属于紫色区域的机器人，如果向右转移，就可以获得属于绿色区域的机器人。由于一定是连续的，所以可以用前缀和优化。令 $row_{i,j}$ 表示第 $i$ 行，前 $j$ 列有多少个机器人，$col_{i,j}$ 表示第 $j$ 列，前 $i$ 行有多少个机器人。那么什么时候可以向某个方向转移？令出口的起始位置为 $(x,y)$。如果要向左转移，那么必须满足 $l<y-1-r$。这是因为最多能向左边转移 $y-1$ 格，每向右边转移一格左边就有一列消失。其余方向同理。然后考虑转移方程。对于向左右转移的，我们需要考虑上下边界。不难想到，下边界就是 $\min(x+d,n-u)$，上边界就是 $\max(d,x-u-1)$。因为用了前缀和，所以上边界要减一。同理，对于向上下转移的，我们需要考虑左右边界，左边界就是 $\max(r,y-l-1)$，右边界就是 $\min(y+r,m-l)$，同样的，左边界是减了一的。然后每次转移的时候取个 $\max$ 就是答案。

code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=110;
int n,m,ans,x,y;
char str[N][N];
int sumrow[N][N],sumcol[N][N];
int f[N][N][N][N];
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i)
    {
        scanf("%s",str[i]+1);
        for (int j=1;j<=m;++j)
        {
            if (str[i][j]=='E') x=i,y=j;
            else 
            {
                sumrow[i][j]=sumrow[i][j-1]+(str[i][j]=='o');
                sumcol[i][j]=sumcol[i-1][j]+(str[i][j]=='o');
            }   
        }
    }
    for (int l=0;l<y;++l)
    {
        for (int r=0;r<=m-y;++r)
        {
            for (int u=0;u<x;++u)
            {
                for (int d=0;d<=n-x;++d)
                {
                    ans=max(ans,f[l][r][u][d]);
                    int val=f[l][r][u][d];
                    if (l<y-1-r) f[l+1][r][u][d]=max(f[l+1][r][u][d],val+sumcol[min(x+d,n-u)][y-l-1]-sumcol[max(d,x-u-1)][y-l-1]);
                    if (r<m-y-l) f[l][r+1][u][d]=max(f[l][r+1][u][d],val+sumcol[min(x+d,n-u)][y+r+1]-sumcol[max(d,x-u-1)][y+r+1]);
                    if (u<x-1-d) f[l][r][u+1][d]=max(f[l][r][u+1][d],val+sumrow[x-u-1][min(y+r,m-l)]-sumrow[x-u-1][max(r,y-l-1)]);
                    if (d<n-x-u) f[l][r][u][d+1]=max(f[l][r][u][d+1],val+sumrow[x+d+1][min(y+r,m-l)]-sumrow[x+d+1][max(r,y-l-1)]);
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
```


---

