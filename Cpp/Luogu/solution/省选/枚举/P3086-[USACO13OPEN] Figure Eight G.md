# [USACO13OPEN] Figure Eight G

## 题目描述

Farmer John's cows recently received a large piece of marble, which, unfortunately, has a number of imperfections.  To describe these, we can represent the piece of marble by an N by N square grid (5 <= N <= 300), where the character '\*' represents an imperfection and '.' represents a flawless section of the marble.

The cows want to carve a number "8" in this piece of marble (cows are quite fond of the number "8" since they have cloven hooves on each of their four feet, so they can effectively count up to 8 using their "toes"). However, the cows need your help to determine the optimally placed figure eight in the piece of marble.  Here are a few properties that define a valid figure eight:

\* A figure eight consists of two rectangles, a top and a bottom. \* Both the top and bottom have at least one cell in their interior. \* The bottom edge of the top rectangle is a (not necessarily proper) subset of the top edge of the bottom rectangle.

\* The figure eight can only be carved from flawless regions of the piece of marble.

The aesthetic score of a figure eight is equal to the product of the areas enclosed by its two rectangles.  The cows wish to maximize this score.

```cpp
............... 
............... 
...*******..... 
.*....*.......* 
.*......*....*. 
....*.......... 
...*...****.... 
............... 
..**.*..*..*... 
...*...**.*.... 
*..*...*....... 
............... 
.....*..*...... 
.........*..... 
............... 
```
For example, given this piece of marble 

the optimally placed eight is:

```cpp
..88888888888.. 
..8.........8.. 
..8*******..8.. 
.*8...*.....8.* 
.*8.....*...8*. 
..8.*.......8.. 
..8*...****.8.. 
.88888888888888 
.8**.*..*..*..8 
.8.*...**.*...8 
*8.*...*......8 
.8............8 
.8...*..*.....8 
.8.......*....8 
.88888888888888 
```
The top rectangle has area 6x9=54, and the bottom rectangle has area 12x6=72.  Thus, its aesthetic score is 54x72=3888.

农民约翰的奶牛最近收到了一大块大理石，不幸的是，它有许多缺陷.。为了描述这些，我们可以用n个正方形网格来表示一块大理石（5 < n = n = 300），其中字符“\*”表示一个不完美和“。


母牛想雕刻一个号码“8”在这一块大理石（牛很喜欢数字“8”，因为他们对他们的每一个四英尺，有偶蹄有效地数到8，用“脚”）。然而，奶牛需要你的帮助，以确定最佳放置在图八块大理石。这里有一些属性定义一个有效的数字八：


图八包括两个矩形，一个顶部和一个底部。顶部和底部至少有一个单元在其内部。顶部矩形的底部边缘是底部矩形顶部边缘的一个（不一定是适当的）子集.。


图八只能刻在大理石的无瑕疵区域。


图八的美学得分等于其两个矩形所包围的区域的乘积.。奶牛希望最大限度地提高这一成绩。


## 说明/提示

顶部的矩形面积6X9 = 54，和底部矩形面积12x6 = 72。因此，它的审美评分54x72 = 3888。


给出一个n×n的区域，其中有一些位置有瑕疵。现在要在没有瑕疵的位置中雕一个8”出来。


“8”字的定义为两个矩形框，框内面积均大于0，且一个矩形框的底边是是另一个矩形框的顶边的子集。


最大化两矩形框内面积的积。


感谢 @3505515693qq 提供翻译


## 样例 #1

### 输入

```
15 
............... 
............... 
...*******..... 
.*....*.......* 
.*......*....*. 
....*.......... 
...*...****.... 
............... 
..**.*..*..*... 
...*...**.*.... 
*..*...*....... 
............... 
.....*..*...... 
.........*..... 
............... 
```

### 输出

```
3888 
```

# 题解

## 作者：Iota2029 (赞：6)

这道题其实是一道DP。

首先设$f[k][i][j]$表示到第$k$行上面矩阵的面积。  
设$g[k][i][j]$表示从第$k$行往下的下面矩阵的面积。

然后转移很显然。。。指针$O(n^3)$的时间扫一扫求面积就好了。

然后可以发现，方便转移，$f[k][i][j]$可以赋值他所包含的$f[k'][i'][j']$。

最后，我们发现空间炸了！！！（hasikid！！！）

于是，题解在这里产生了分支：

1.把类型转成$short$。然后这样的话就可以拿九十分。

2.考虑到$g$可以不记录，及时枚举和$f$一起求，所以可以把$g$压掉，等到求最终答案的时候再一起求。

上码：
 ```cpp
 #pragma GCC optimize(2)
#include <cstdio>
#include <cstring>
#define N 301
using namespace std;

inline int max(int a,int b) {return a > b ? a : b;} 
int f[N][N][N];
int sum[N][N], map[N][N], n, ans, p;
char s[N];

int main()
{
	scanf("%d", &n);
	for (int i = 1;i <= n; ++i)
	{
		scanf("%s", s + 1);
		for (int j = 1;j <= n; ++j)
			map[i][j] = s[j] == '*' ? 1 : 0, 
			sum[i][j] = sum[i][j - 1] + map[i][j];
	}
	for (int i = 1;i < n - 1; ++i)
		for (int j = i + 2;j <= n; ++j)
		{
			p = 0;
			for (int k = 1;k <= n; ++k)
			{
				if (map[k][i] || map[k][j]) p = 0;
				if (sum[k][i - 1] == sum[k][j]) 
					!p ? p = k : f[k][i][j] = (k - p - 1) * (j - i - 1);
			}
		}
	for (int k = 1;k <= n; ++k)
	{
		for (int j = n;j > 3; --j)
			for (int i = j - 3;i >= 0; --i) 
				if (sum[k][i - 1] == sum[k][j]) f[k][i][j] = max(f[k][i][j], f[k][i + 1][j]);
		for (int i = 1;i < n - 1; ++i)
			for (int j = i + 3;j <= n; ++j) 
				if (sum[k][i - 1] == sum[k][j]) f[k][i][j] = max(f[k][i][j], f[k][i][j - 1]);
	}
	for (int i = 1;i < n - 1; ++i)
		for (int j = i + 2;j <= n; ++j) 
		{
			p = 0;
			for (int k = n;k; --k) 
			{
				if (map[k][i] || map[k][j]) p = 0;
				if (sum[k][i - 1] == sum[k][j]) (!p) ? p = k : ans = max(ans, f[k][i][j] * (p - k - 1) * (j - i - 1));
			}
		}
	if (!ans) printf("-1");
	else printf("%d", ans);
	return 0;
}
 ```

---

## 作者：igAC (赞：3)

# $\text{Describe}$

[link](https://www.luogu.com.cn/problem/P3086)

题意：

给定一个 $n \times n$ 的正方形矩阵，矩阵中的每个元素都是``*``或``.``，``*``表示不完美的大理石，我们要在上面雕刻一个数字 $8$，还要满足以下条件：

- 数字 $8$ 由上下两个矩形组成，每个矩形必须保证有一个单元格在这个矩形里面，即形如：

```
888
8.8
888
```

- 上矩形的底部必须是下矩形顶部的子集：

即：

设上矩形的底部左右端点坐标分别为为 $(l,k),(r,k)$（先列后行）。

那么下矩形的顶部左右端点的坐标分别为 $(l-d,k),(r+d,k)$，其中 $0 \le d $。

形如：

```
.888.
.8.8.
88888
8...8
88888
```

- 数字 $8$ 的边界部分必须刻在``.``上。

- 每个数字 $8$ 的分数是其上矩形的面积乘下矩形的面积。

你需要求出最大的分数。

# $\text{Solution}$

我们过观察发现这是一道 DP 题。

我们再深入思考发现如果我们直接 DP $8$ 字形就非常难做（不可做？）。

于是我们选择将数字 $8$ 分部分做。

因为数字 $8$ 是由上矩形和下矩形合并而成，所以我们将状态设为上矩形的底部和下矩形的顶部。

我们设 $f_{i,l,r}$ 表示上矩形的底部位于第 $i$ 行并且左端点在 $l$ 右端点在 $r$ 时，上矩形的最大面积。

转移时我们还需要上矩形的高度 $j$。

如果发现 $i_1<i_2$，那么对应的，$j_1 \le j_2$，即 $j$ 具有单调性。

转移很显然。

设 $g_{i,l,r}$ 表示下矩形的顶部位于第 $i$ 行并且左端点在 $l$ 右端点在 $r$ 时，下矩形的最大面积。

转移与上矩形类似。

合并后的答案是 $\max(f_{i,l,r} \times g_{i,L,R}),(L \le l < r \le R)$。

我们需要 $O(1)$ 求 $\max$。

于是我们需要 $O(1)$ 判断是否合法。

我们如何判断矩形的端点是否在``.``上呢，这只需要定义两个数组。

$d_{i,j}$ 表示在 $(i,j)$ 向下走能走多远，$r_{i,j}$ 表示在 $(i,j)$ 向右走能走多远。

至此我们的算法的时间复杂度为 $O(n^3)$ 这是我们可以接受的。

但这可恶的空间复杂度我们不能接受，我们开了两个 $n^3$ 的数组。

我们发现在求 $g_{i,l,r}$ 的时候，每个 $g$ 只用了一次，因此我们可以直接省略 $g$ 数组，这样空间复杂度就只有 $O(n^3)$ 了。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 305
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,d[N][N],R[N][N],f[N][N][N];
ll ans;
char c[N][N];
void init(){
	n=read();
	for(int i=1;i<=n;++i) scanf("%s",c[i]+1);
	for(int i=n;i>=1;--i){
		for(int j=n;j>=1;--j){
			if(c[i][j]=='.') d[i][j]=d[i+1][j]+1,R[i][j]=R[i][j+1]+1;
			else d[i][j]=R[i][j]=0;
		}
	}
	for(int l=1;l<=n-2;++l){
		for(int r=l+2;r<=n;++r){
			int j=1;
			for(int i=3;i<=n;++i){
				if(R[i][l]+l-1<r){
					f[i][l][r]=0;
					continue;
				}
				for(;(i>min(d[j][l],d[j][r])+j-1 || R[j][l]+l-1<r) && i-j>=2;++j);
				if(i-j<2) f[i][l][r]=0;
				else f[i][l][r]=(r-l-1)*(i-j-1);
			}
		}
	}
}
void solve(){
	for(int i=1;i<=n;++i){
		for(int len=2;len<=n;++len){
			for(int l=1;l+len<=n;++l){
				int r=l+len;
				f[i][l][r+1]=max(f[i][l][r+1],f[i][l][r]);
				f[i][l-1][r]=max(f[i][l-1][r],f[i][l][r]);
			}
		}
	}
	for(int l=1;l<=n-2;++l){
		for(int r=l+2;r<=n;++r){
			int j=n;
			for(int i=n-2;i>=1;--i){
				if(R[i][l]+l-1<r) continue;
				for(;(j>min(d[i][l],d[i][r])+i-1 || R[j][l]+l-1<r) && j-i>=2;--j);
				if(j-i>=2) ans=max(ans,1ll*f[i][l][r]*(j-i-1)*(r-l-1));
			}
		}
	}
	printf("%lld",!ans?-1:ans);
}
int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：TianTian2008 (赞：1)

（感觉难度绿上位，顶多也就蓝，紫是真不至于）

先观察一下数据范围：$5\leq n\leq300$。那么时间复杂度在 $O(n^3)$ 左右，最多再挂一个 $\log$，那么时间复杂度高于这个的算法就可以直接放弃了。

对于这种一些点可以选、一些点不能选的图形问题，一般都是预处理然后合并计算之类的，这题也不例外。

首先可以发现，两个矩形之间互相影响的唯一限制是上面矩阵的长要被下面矩阵的长包含，于是我们想到枚举交界的行和下矩阵的长区间（当然，枚举上矩阵的长区间也行，但枚举下矩阵的长区间比较好实现些）然后再和合法上矩阵的答案合并。我们先枚举区间再枚举行，这样每次求最大下矩阵可以从当前行的下一行 $O(1)$ 转移过来，代码大概这样：

```cpp
for(int l=1;l<=n;++l)
	for(int r=l+1;r<=n;++r) {
		int las=0;// las 是当前这行能到达的最下的行编号
		for(int i=n;i>=1;--i) {
			if(a[i][l]=='*'||a[i][r]=='*') las=0;// 左右两边断了
			if(s[i][r]-s[i][l-1]!=0) continue;// 这行断了
			if(!las) las=i;
			else // 下矩阵最大面积为 (las-i-1)*(r-l-1)
		}
	}
```

注意现在这段枚举的代码时间复杂度已经 $O(n^3)$ 了，所以求上矩阵的答案应该要预处理做到 $O(1)$ 或者 $O(\log n)$ 查询。

具体来说，我们要预处理一个数组 $f_{i,l,r}$，表示一个矩阵的最大面积，满足这个矩阵的底边为 $i$，长区间被 $[l,r]$ 包含。直接算不好算，考虑一个弱化问题：求一个矩阵的最大面积，满足这个矩阵的底边为 $i$，长区间为 $[l,r]$ 包含。这个显然很好求，和上面枚举的代码差不多。用这个弱化问题的答案随便处理一下就可以得到 $f$ 了。

AC代码如下：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n,s[310][310],f[310][310][310],ans;
char a[310][310];
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%s",a[i]+1);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j) s[i][j]=s[i][j-1]+(a[i][j]=='*');
	for(int l=1;l<=n;++l)
		for(int r=l+1;r<=n;++r) {
			int las=0;
			for(int i=1;i<=n;++i) {
				if(a[i][l]=='*'||a[i][r]=='*') las=0;
				if(s[i][r]-s[i][l-1]!=0) continue;
				if(!las) las=i;
				else f[i][l][r]=(i-las-1)*(r-l-1);
			}
		}
	for(int i=1;i<=n;++i) {
		for(int r=1;r<=n;++r)
			for(int l=r-1;l>=1;--l) f[i][l][r]=max(f[i][l+1][r],f[i][l][r]);
		for(int l=1;l<=n;++l)
			for(int r=l+1;r<=n;++r) f[i][l][r]=max(f[i][l][r-1],f[i][l][r]);
	}
	for(int l=1;l<=n;++l)
		for(int r=l+1;r<=n;++r) {
			int las=0;
			for(int i=n;i>=1;--i) {
				if(a[i][l]=='*'||a[i][r]=='*') las=0;
				if(s[i][r]-s[i][l-1]!=0) continue;
				if(!las) las=i;
				else ans=max(ans,(las-i-1)*(r-l-1)*f[i][l][r]);
			}
		}
	if(!ans) puts("-1");
	else printf("%d",ans);
	return 0;
} 
```

---

## 作者：DengDuck (赞：1)

一道求最值的双指针好题。

首先我们显然要拆这个形状不难想到可以拆成两个矩形维护。

我们发现两个矩形匹配的关键是上矩形的底边，下矩形的顶部，所以我们以此来表示矩形记录最值。

我们可以设 $f_{i,l,r}$ 表示上矩形底边为 $(i,l)$ 至 $(i,r)$ 矩形的最大面积。

显然使其最大只需要找到一个最小的 $j$ 使得 $(i,l)(i,r)(j,l)(j,r)$ 可以构成一个合法的矩形，而对于合法的 $j$ 显然随着 $i$ 变大而变大，所以考虑直接双指针维护。

我们可以具体分析一下，首先我们需要排开自身有问题的 $j$，也就是 $(j,l)$ 无法连接 $(j,r)$，对于剩下的 $j$，如果不合法，一定是在竖的方向被阻碍，所以上面的 $j$ 都不合法，所以只能不断向下找。

在代码实现的时候注意我们的边界可以设为 $j=i-1$，此时显然上矩形面积为 $0$，在这里停下即可。

接下来我们利用 $f$ 可以推出另外的数组 $F$，$F_{i,l,r}$ 表示上矩形底边在 $(i,l)$ 至 $(i,r)$ 之中所有矩形的最大面积。

具体实现方式可以看我代码，简单来说就是区间不断合并求出，还是很简单的。

最后利用同样的方法来维护下矩形即可，对于每个下矩形，我们让其面积与 $F_{i,l,r}$ 相乘即可得到答案，这显然是符合题目要求的。

注意这题卡空间，需要用一些小技巧。

时间复杂度是 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define LL int
using namespace std;
const LL N=305;
LL n,u[N][N],L[N][N],ans,f[N][N][N];
char c[N][N];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",c[i]+1);
		for(int j=1;j<=n;j++)
		{
			if(c[i][j]=='.')u[i][j]=u[i-1][j]+1,L[i][j]=L[i][j-1]+1;		
		}
	}
	for(int l=1;l<=n;l++)
	{
		for(int r=l+2;r<=n;r++)
		{
			LL t=1;
			for(int h=1;h<=n;h++)
			{
				if(l<r-L[h][r]+1)continue;
				while((t<h-min(u[h][l],u[h][r])+1||l<=r-L[t][r]+1)&&t+2<=h)t++;
				if(t+2<=h)f[h][l][r]=(r-l-1)*(h-t-1);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int len=4;len<=n;len++)
		{
			for(int l=1;l+len-1<=n;l++)f[i][l][l+len-1]=max(f[i][l][l+len-1],f[i][l][l+len-2]);
			for(int r=n;r-len+1>=1;r--)f[i][r-len+1][r]=max(f[i][r-len+1][r],f[i][r-len+2][r]);
		}
	}
	for(int l=1;l<=n;l++)
	{
		for(int r=l+2;r<=n;r++)
		{
			LL t=n;
			for(int h=n;h>=1;h--)
			{
				if(l<r-L[h][r]+1)continue;
				while((h<t-min(u[t][l],u[t][r])+1||l<=r-L[t][r]+1)&&h+2<=t)t--;
				if(h+2<=t)ans=max((r-l-1)*(t-h-1)*f[h][l][r],ans);
			}
		}
	}
	if(ans)printf("%d",ans);
	else puts("-1");
}
```

---

## 作者：daniEl_lElE (赞：0)

先考虑下方的一个 `0` 状物。枚举左右端点 $l,r$，从下往上扫，维护最下方的 $l\sim r$ 均为空的行。如果 $l$ 或 $r$ 列此时被占据，那么将目前维护的这个行去掉。这样，我们就可以算出第 $i$ 行，$l\sim r$ 列往下的最大 `0`。记为 $f_{i,l,r}$。

上面一半可以用类似方式求出。接下来，对于每行，我们要求 $l'\leq l,r\leq r'$ 的最大 $f_{i,l,r}$。可以使用二维前缀和解决。

然而这样空间会爆。考虑先对每行做二维前缀和，这样枚举上面一半的时候就不用再记录了。

需要用 `unsigned short` 存 $f_{i,l,r}$。时空复杂度均为 $O(n^3)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
unsigned short maxd[305][305][305];
int gd[305][305],gu[305][305];
bool ok[305][305][305];
bool vis[305][305][305];
char c[305][305];
signed main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%s",c[i]+1);
		for(int j=1;j<=n;j++){
			if(c[i][j]=='.'){
				ok[i][j][j]=1;
				for(int k=j+1;k<=n;k++){
					ok[i][j][k]=ok[i][j][k-1]&(c[i][k]=='.');
				} 
			}
		}
	}
	for(int j=1;j<=n;j++){
		for(int i=1;i<=n;i++) if(c[i][j]=='.') gu[i][j]=gu[i-1][j]+1;
		for(int i=n;i>=1;i--) if(c[i][j]=='.') gd[i][j]=gd[i+1][j]+1;
	}
	for(int j=1;j<=n;j++){
		for(int k=j+2;k<=n;k++){
			int it=n;
			for(int i=n-1;i>=1;i--){
				while(it>i&&(it>=i+min(gd[i][j],gd[i][k])||!ok[it][j][k])) it--;
				if(it>i+1&&ok[i][j][k]) maxd[i][j][k]=(k-j-1)*(it-i-1),vis[i][j][k]=1;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=n;k>=j+1;k--){
				maxd[i][j][k-1]=max(maxd[i][j][k-1],maxd[i][j][k]);
				vis[i][j][k-1]|=vis[i][j][k];
				maxd[i][j+1][k]=max(maxd[i][j+1][k],maxd[i][j][k]);
				vis[i][j+1][k]|=vis[i][j][k];
			}
		}
	}
	int maxv=-1;
	for(int j=1;j<=n;j++){
		for(int k=j+2;k<=n;k++){
			int it=1;
			for(int i=2;i<=n;i++){
				while(it<i&&(it<=i-min(gu[i][j],gu[i][k])||!ok[it][j][k])) it++;
				if(it<i-1&&ok[i][j][k]){
					if(vis[i][j][k]!=0){
						maxv=max(maxv,(int)1*maxd[i][j][k]*(k-j-1)*(i-it-1));
					}
				}
			}
		}
	}
	cout<<maxv;
	return 0;
}
```

---

## 作者：ReTF (赞：0)

### 前言
小蒟蒻在拿了4个CE4个WA，心态被搞崩 $114^{514}$ 次，反复趋势一小时后，终于切了这道题，准备发篇题解纪念一下。
### 解法
![](https://cdn.luogu.com.cn/upload/image_hosting/2xcbk88k.png)

因为 $n$ 的范围只有 $300$，所以考虑直接枚举蓝色部分，枚举这一部分的时间复杂度是 $\Theta(n^3)$。为保证复杂度的正确性，我们需要用 $\Theta(\log n)$ 或 $\Theta(1)$ 的时间求出绿色和红色部分的值。这是不能直接求的，考虑dp。令 $f_{i,j,k}$ 表示左下角端点和右下角端点分别为 $i$ 行 $j$ 列，$i$ 行 $k$ 列的格子的红色部分的最大高度。如果的两个格子中间的格子都没有瑕疵，则 $f_{i,j,k}$ 可以为 $0$。（即当前的左右端点可以是红色的最上面一行）。否则，如果两个格子都没有瑕疵，那么可以从上一行直接转移。否则，当前的状态就是不合法的。判断两个格子之间的格子是否有瑕疵可以用前缀和优化到 $\Theta(1)$，这样整个dp的过程就是 $\Theta(n^3)$ 的。预处理绿色部分的过程同理。$g_{i,j,k}$ 表示左上角端点和右上角端点分别为 $i$ 行 $j$ 列，$i$ 行 $k$ 列的格子的绿色部分的最大高度。

形式化的状态转移方程如下：（$x(i,j)=0$ 等价于 $i$ 行 $j$ 列的格子无瑕疵）
$$f_{i,j,k}= \begin{cases}\max\{0,f_{i-1,j,k}+1\} & (\forall p \in [j,k],x(i,p)=0)\\f_{i-1,j,k}+1 &(x(i,j)=0\ \land\ x(i,k)=0)\\-\text{inf}& \text{otherwise.}\end{cases}$$
还有一个遗留的问题：题目中要求一个矩形框的底边是是另一个矩形框的顶边的子集。在枚举蓝色的时候，绿色部分可以唯一确定（两端点已唯一确定），但是无法确定红色部分的两端点。令 $dp_{(i),j,k}$ 表示第 $i$ 行中，左下角端点和右下角端点在区间 $[j,k]$ 之间的红色部分的最大面积。可以发现，$dp_{(i),j,k}$ 的值可以通过两个长度为 $k-j$ 的子区间转移得到。这本质上是一个区间dp。

形式化的状态转移方程如下：

$$dp_{(i),j,k}=\max\{dp_{(i),j+1,k},dp_{(i),j,k-1},f_{i,j,k}\times(k-j-1)\}$$
### 卡常
都写完了，[自信地往上一交](https://www.luogu.com.cn/record/97372374)

因为 $f$ 数组和 $g$ 数组中的值都不超过 $n$，所以可以使用赛加加的 `short` 类型，该类型存储数据的范围为`-32768~32767`。这样就可以卡过去了。

[代码在这里](https://www.luogu.com.cn/paste/qw0vrl37)

---

