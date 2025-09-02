# White Lines

## 题目描述

Gildong has bought a famous painting software cfpaint. The working screen of cfpaint is square-shaped consisting of $ n $ rows and $ n $ columns of square cells. The rows are numbered from $ 1 $ to $ n $ , from top to bottom, and the columns are numbered from $ 1 $ to $ n $ , from left to right. The position of a cell at row $ r $ and column $ c $ is represented as $ (r, c) $ . There are only two colors for the cells in cfpaint — black and white.

There is a tool named eraser in cfpaint. The eraser has an integer size $ k $ ( $ 1 \le k \le n $ ). To use the eraser, Gildong needs to click on a cell $ (i, j) $ where $ 1 \le i, j \le n - k + 1 $ . When a cell $ (i, j) $ is clicked, all of the cells $ (i', j') $ where $ i \le i' \le i + k - 1 $ and $ j \le j' \le j + k - 1 $ become white. In other words, a square with side equal to $ k $ cells and top left corner at $ (i, j) $ is colored white.

A white line is a row or a column without any black cells.

Gildong has worked with cfpaint for some time, so some of the cells (possibly zero or all) are currently black. He wants to know the maximum number of white lines after using the eraser exactly once. Help Gildong find the answer to his question.

## 说明/提示

In the first example, Gildong can click the cell $ (2, 2) $ , then the working screen becomes:

```
<pre class="verbatim">BWWW<br></br>WWWW<br></br>WWWW<br></br>WWWB<br></br>
```

Then there are four white lines — the $ 2 $ -nd and $ 3 $ -rd row, and the $ 2 $ -nd and $ 3 $ -rd column.

In the second example, clicking the cell $ (2, 3) $ makes the $ 2 $ -nd row a white line.

In the third example, both the $ 2 $ -nd column and $ 5 $ -th row become white lines by clicking the cell $ (3, 2) $ .

## 样例 #1

### 输入

```
4 2
BWWW
WBBW
WBBW
WWWB
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 1
BWB
WWB
BWB
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 3
BWBBB
BWBBB
BBBBB
BBBBB
WBBBW
```

### 输出

```
2
```

## 样例 #4

### 输入

```
2 2
BW
WB
```

### 输出

```
4
```

## 样例 #5

### 输入

```
2 1
WW
WW
```

### 输出

```
4
```

# 题解

## 作者：Koakuma (赞：20)

**$\mathcal{Description}$**

给你一个 $n\times n$ 个格点构成的矩阵 , 每个格点只有黑白两种颜色 , 现在你可以使其中一块 $k\times k$ 的区域变成白色 , 求这样操作后最多有多少行和列全是白色

**$\mathcal{Solution}$**

难度主要集中在思维方面 , 其实想进去了代码实现并不难

**约定**：$\mathcal{Matrix[(xa,ya),(xb,yb)]}$ 表示左上角格点坐标为 $(xa,ya)$ , 右下角格点坐标为 $(xb,yb)$ 的矩形

用 $t[i][j]$ 表示第 $i$ 行 $j$ 列格点的染色情况,我们约定黑色为 $1$ , 白色则为 $0$

然后**分别**对行和列进行操作 , 这里只举出行的例子 , 读者可以结合代码食用 , 列亦然

从 $1-n$ 枚举行 , 对于第 $i$ 行 , 我们分别找出在这一行最左和最右的两个黑色格点记作 $l$ 和 $r$ (注意这里的 $l$ 和 $r$ 也有可能指在同一个格点)

如果不存在 , 也就是整行全为白色 , 我们就可以统计到答案中去.

如果存在 $l$ 和 $r$ 但是区间 $[l,r]$ 的长度大于 $k$ , 也就是无论怎么操作都无法使这一行的格点全部变成白色 , 我们选择忽略对此行的操作.

如果 $l$ 和 $r$ 存在且构成的区间长度小于等于 $k$:

![1.png](https://i.loli.net/2019/08/12/HmUsgEMGYQKaLBb.png)

令操作的矩形左上角的点坐标为 $(x,y)$ , 我们发现 , 只要满足 $i-k+1\leq x \leq i$ 且 $r-k+1 \leq y \leq l$, 都可以使第 $i$ 行变为全白行

![2.png](https://i.loli.net/2019/08/12/fAogptJFTURK8My.png)

如上图所示 , 当操作矩形左上角的点在蓝色阴影区域内的时候均可将第 $i$ 行变为全白行（橙色矩形和绿色矩形是**水平方向**上的两个极端情况） , 所以应将此阴影区域内的格点的值均加上 $1$ （这里的**格点值**是指以格点 $(a,b)$ 作为操作矩形的**左上角格点**，能够多形成全白行 $|$ 列的条数）. 我们可以用 $sum[i][j]$ 表示$\mathcal{Matrix}[(1,1),(i,j)]$ 内每个格点的**变化值** , 现在我们要将 $\mathcal{Matrix}[(x,y),(i,l)]\ \ \ (x=i-k+1,y=r-k+1)\ $ 内的格点值均加上 $1$ , 根据容斥原理 , 将 $sum[i][l]$ 加上 $1$ , 然后将 $sum[i][y-1]$ 和 $sum[i-k][l]$ 减去 $1$ , 再将多减了 $1$ 的 $sum[i-k][y-1]$ 加上 $1$ 即可 , 值得注意的是 , **在代码实现的过程中应注意数组越界问题** , 具体细节请见代码 . 

这样行和列均处理完之后 , 我们再用一个二维数组 $pra$ 计算出**最终的每个格点的格点值** , 注意要**倒推** , 因为 $sum[i][j]$ 越靠近右下角说明其对前面格点的影响范围越广

$$pra[i][j]=pra[i+1][j]+pra[i][j+1]-pra[i+1][j+1]+sum[i][j]$$

这里对上面这个式子再解释下 , 我们可以把 $pra[i][j]$ 所储存的值抽象地理解为 $(i,j)$ 这个格点右下方的 $sum$ 对这个格点值影响的总和

![3.png](https://i.loli.net/2019/08/13/pa25wQoFA3CJnuX.png)

从上图我们可以看出 , pra[x][y] 的值就等于上了色的四块矩形的面积 , $pra[x+1][y]$ 储存的值是黄色块下方的矩形加上绿色的矩形 , 而 $pra[x][y+1]$ 储存的值是黄色块右边的矩形加上绿色的矩形 , 所以我们可以根据容斥原理求出这三块矩形的值 , 然后加上黄色格点的 $sum[x][y]$ , 最后算出来的就是 $(x,y)$ 这个格点的格点值了

$\mathcal{Code}$

```cpp
#include <bits/stdc++.h>
#define LL long long
#define reg register

using namespace std;

const int kN = 2e3 + 10;

int sum[kN][kN], pra[kN][kN];
int N, K, Ans = 0, t[kN][kN];
char c;

int main() {
  scanf("%d%d", &N, &K);
  for (reg int i = 1; i <= N; ++i)
    for (reg int j = 1; j <= N; ++j)
      cin >> c, t[i][j] = (c == 'B');
  int tot, l, r;
  /*  Line operation  */
  for (reg int i = 1; i <= N; ++i) {
    tot = r = 0; l = N + 1;
    for (reg int j = 1; j <= N; ++j)
      if (t[i][j]) l = min(l, j), r = max(r, j), tot++;
    if (!tot) Ans++;
    else if (r - l >= K) continue ;
    else {
      int x, y;
      x = max(1, i - K + 1), y = max(1, r - K + 1);
      sum[i][l]++; sum[i][y - 1]--;
      if (i >= K) sum[i - K][l]--, sum[i - K][y - 1]++;
    }
  }
  /*  Column operation  */
  for (reg int i = 1; i <= N; ++i) {
    tot = r = 0; l = N + 1;
    for (reg int j = 1; j <= N; ++j)
      if (t[j][i]) l = min(l, j), r = max(r, j), tot++;
    if (!tot) Ans++;
    else if (r - l >= K) continue ;
    else {
      int x, y;
      x = max(1, i - K + 1), y = max(1, r - K + 1);
      sum[l][i]++; sum[y - 1][i]--;
      if (i >= K) sum[l][i - K]--, sum[y - 1][i - K]++;
    }
  }
  for (reg int i = N; i >= 1; --i)
    for (reg int j = N; j >= 1; --j)
      pra[i][j] = pra[i + 1][j] + pra[i][j + 1] - pra[i + 1][j + 1] + sum[i][j];
  int maxx = 0;
  for (reg int i = 1; i <= N; ++i)
    for (reg int j = 1; j <= N; ++j)
      maxx = max(maxx, pra[i][j]);
  printf("%d\n", Ans + maxx);
  return 0;
}
```


$\mathcal{P.S:}$ 最后说些题外话 , 这是 $\mathcal{CodeForces}$ 结束后 , 准备清任务栏的时候发现打比赛时留下的草稿(见前 $2$ 张图) , 感觉删了可惜 , 所以就想写篇此题的题解 , 说实话 , 想着怎么把此题讲明白倒困扰了我很久 , 所以如果您还有什么不懂的请私信或者在评论区指出 , 我会尽我所能解答的 , 感谢理解

$\mathcal{Update:}$ 修改了题解中的部分小错误

---

## 作者：QwQcOrZ (赞：11)

## 题意：

给出一个$n*n$的$01$矩阵，可以把其中一个$k*k$的子矩阵变成0，求最多可以有多少条白线（即行或列全都是0的行列数量）

## 题解：

来一发代码短的做法 ~~忽略IO只有十几行~~

显然染白后不会影响原先的答案，于是我们可以先预处理出原先的白线数

对于每个染白的方案，我们先预处理，然后可以O(1)计算出出他的贡献

这显然可以想到前缀和

设$a[i][j]$为第j列行上的前缀和

$b[i][j]$为第i行列上的前缀和

$x[i][j]$为去除$[i-k+1$~$i][j]$后对答案的贡献（前缀和）

$y[i][j]$为去除$[i][j-k+1$~$j]$后对答案的贡献（前缀和）

$a$，$b$很好计算，重点是x和y

显然当这些条件都满足时，在$i$，$j$处才会有贡献对$x[i][j]$：

$\begin{cases}a[i-k][j]==0\\a[n][j]-a[i][j]==0\\a[i][j]-a[i-k][j]>0\end{cases}$

即$1$~$i-k+1$，$i$~$n$必须全部是$0$，否则不会有贡献

而第三个条件是避免重复贡献（因为如果原来就是空的那么就已经算在答案里了）

$y$的计算同理

最后寻找最大值，然后输出原答案加最大贡献就好辣

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e3;
 
inline int read()
{
    int s=0;
    char c=getchar(),lc='+';
    while (c<'0'||c>'9') lc=c,c=getchar();
    while (c>='0'&&c<='9') s=s*10+c-'0',c=getchar();
    return lc=='-'?-s:s;
}
void write(int n)
{
    if (n<0)
    {
        putchar('-');
        n=abs(n);
    }
    if (n<10)
    {
        putchar(n+'0');
        return;
    }
    write(n/10);
    putchar(n%10+'0');
}
int a[N][N],b[N][N],x[N][N],y[N][N],ans=0,tot=0;
 
int main()
{
	int n=read(),k=read();
	for (int i=0;i<N;i++)
	for (int j=0;j<N;j++) a[i][j]=b[i][j]=0;
	for (int i=1;i<=n;i++)
	for (int j=1;j<=n;j++)
	{
		char c=getchar();
		while (c!='B'&&c!='W') c=getchar();
		a[i][j]=a[i-1][j]+(c=='B');
		b[i][j]=b[i][j-1]+(c=='B');//处理a、b，前缀和数组
	}
	for (int i=1;i<=n;i++)
	{
		tot+=a[n][i]==0;
		tot+=b[i][n]==0;//计算修改前的答案，正确性显然
	}
	for (int i=k;i<=n;i++)
	for (int j=1;j<=n;j++) x[i][j]=x[i][j-1]+(a[i-k][j]==0&&a[n][j]-a[i][j]==0&&a[i][j]-a[i-k][j]>0);
	for (int j=k;j<=n;j++)
	for (int i=1;i<=n;i++) y[i][j]=y[i-1][j]+(b[i][j-k]==0&&b[i][n]-b[i][j]==0&&b[i][j]-b[i][j-k]>0);//处理x、y，贡献数组
	for (int i=k;i<=n;i++)
	for (int j=k;j<=n;j++) ans=max(ans,x[i][j]-x[i][j-k]+y[i][j]-y[i-k][j]);
	write(tot+ans);
 
	return 0;
}
```

~~个人认为代码可读性较高，，~~

---

## 作者：Soulist (赞：5)

我们发现行和列是单独的，所以分开处理，记$line[i]$为第$i$列是否可行。

接下来我们考虑枚举一个位置$(i,j)$，计算以其为左上角的答案。

现在考虑列，可以发现这个矩形对其外面的列答案不会有影响。

所以未被其影响到的列的答案就是：

$$\sum_{l=1}^{i-1}line[l]+\sum_{r=i+k}^{n}line[r]$$

于是你发现对于其外面的部分我们就做一下$line$的前缀和就能$O(1)$得出答案了。

接下来考虑记一个函数$f_{i,j}$表示将$(i,j)$至$(i,j+k-1)$处全部染白后此列能否可行。

接下来我们考虑记白点为$0$，黑点为$1$。

那么$f_{i,j}$的计算就只要判一下$(i,1)$至$(i,j-1)$和$(i,j+k)$至$(i,n)$处是否有黑点即可。

显然我们可以对每一列记一个前缀和表示黑点的数量(这个前缀和的计算是$n^2$的)，然后$O(1)$计算$f_{i,j}$，于是计算$f_{i,j}$的复杂度也是$O(n^2)$

于是这个矩形影响到的列的答案就是：

$$\sum_{t=i}^{t=i+k-1}f_{t,j}$$

所以再对$f_{i,j}$做一个前缀和就可以将这一部分也变成$O(1)$的了，因为点对总数是$n^2$，总复杂度是$O(n^2)$

行同理。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
int read() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
const int N = 2000 + 5 ;
int n, k, c[N][N], ln1[N], ln2[N], sn1[N], sn2[N] ;
int sum1[N][N], sum2[N][N], dp1[N][N], dp2[N][N], Ans;
char s[N][N] ;
signed main()
{
	n = read(), k = read() ;
	rep( i, 1, n ) scanf("%s", s[i] + 1 ) ;
	rep( i, 1, n ) rep( j, 1, n ) c[i][j] = ( s[i][j] == 'W' ? 0 : 1 ) ;
	rep( i, 1, n ) {
		int flag1 = 0, flag2 = 0 ; 
		rep( j, 1, n ) flag1 = max( flag1, c[i][j] ), flag2 = max( flag2, c[j][i] ) ;
		ln1[i] = flag1 ^ 1, ln2[i] = flag2 ^ 1 ; 
		sn1[i] = sn1[i - 1] + ln1[i]; sn2[i] = sn2[i - 1] + ln2[i] ;
	}
	rep( i, 1, n ) rep( j, 1, n ) {
		sum1[i][j] = sum1[i][j - 1] + c[i][j] ;
		sum2[i][j] = sum2[i - 1][j] + c[i][j] ;
	}
	for( int i = 1; i <= n; ++ i )
		for( int j = 1; j <= n; ++ j ) {
			int k1 = sum1[i][n] + sum1[i][j - 1] - sum1[i][j + k - 1] ; 
			int k2 = sum2[n][j] + sum2[i - 1][j] - sum2[i + k - 1][j] ; 
			dp1[i][j] = ( k1 == 0 ) ;
			dp2[i][j] = ( k2 == 0 ) ;
			dp1[i][j] = dp1[i - 1][j] + dp1[i][j] ;
			dp2[i][j] = dp2[i][j - 1] + dp2[i][j] ;
		}
	for( int i = 1; i <= n - k + 1; ++ i ) {
		for( int j = 1; j <= n - k + 1; ++ j ) {
			int line = sn1[n] - sn1[i + k - 1] + sn1[i - 1] ;
			int line2 = sn2[n] - sn2[j + k - 1] + sn2[j - 1] ;
			line += ( dp1[i + k - 1][j] - dp1[i - 1][j] ) ;
			line2 += ( dp2[i][j + k - 1] - dp2[i][j - 1] ) ;
			Ans = max( Ans, line + line2 ) ;
		}
	}
	printf("%d\n", Ans ) ;
	return 0;
}
```

---

## 作者：Froggy (赞：4)

提供一种~~另类~~的想法

不用dp

### 二维差分!

有做过[窗口的星星](https://www.luogu.org/problem/P1502)么

继承了它的做法

当然不用扫描线(2000*2000很小)

考虑每一行,每一列可以对答案产生贡献时覆盖正方形的左上角的位置

比如:

```
BWWW
WBBW
WBBW
WWWB
```

第二行对答案产生贡献时正方形左上角的位置可以为(O的位置为"可以")
```
XOXX
XOXX
XXXX
XXXX
```

先考虑每一行,如果当行都是W,不用管,直接把答案++

否则,找到当行最左侧的B和最右侧的B,位置设为$l$,$r$

显然,当 $r-l+1>k$ 时,当行永远也不可能对答案产生贡献

否则我们要找到覆正方形左上角可能的位置(显然是个矩形)

目前为第i行,则矩形

左上角坐标:$(max(1,i-k+1),max(1,r-k+1))$

右下角坐标:$(i,l)$

不难理解吧(不理解的可以根据例子想一想)

二维树状数组?

由于时最后一起统计,所以可以用**二维差分**

---

下面是差分

先看看求二维前缀和的式子:

$a_{i,j}=a_{i-1,j}+a_{i,j-1}-a_{i-1,j-1}$

类比一维的差分,不难想到:

```cpp
//左上角:(X1,Y1)  右下角:(X2,Y2)
a[X1][Y1]++;
a[X2+1][Y2+1]++;
a[X2+1][Y1]--;
a[X1][Y2+1]--;
```

最后跑一遍前缀和,取最大值就OK啦!

列的情况类似,不多讲


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define N 2005
const int inf=99999;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
int n,k,a[N][N],mp[N][N],cnt,f[N][N],ans;
char s[N][N];
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=n;j++){
			if(s[i][j]=='W'){
				mp[i][j]=1;
			}
			else{
				mp[i][j]=0;
			}
		}
	}
    //行的情况
	for(int i=1;i<=n;i++){
		int l=inf,r=-inf;
		for(int j=1;j<=n;j++){
			if(mp[i][j]==0){
				l=min(l,j);
				r=max(r,j);
			}
		}
		if(l==inf&&r==-inf){
			cnt++;
		}
		else{
			if(r-l+1>k)continue;
			int X1=max(1,i-k+1),Y1=max(1,r-k+1),X2=i,Y2=l;
			a[X1][Y1]++;
			a[X2+1][Y2+1]++;
			a[X2+1][Y1]--;
			a[X1][Y2+1]--;
		}
	}
    //列的情况
	for(int i=1;i<=n;i++){
		int l=inf,r=-inf;
		for(int j=1;j<=n;j++){
			if(mp[j][i]==0){
				l=min(l,j);
				r=max(r,j);
			}
		}
		if(l==inf&&r==-inf){
			cnt++;
		}
		else{
			if(r-l+1>k)continue;
			int X1=max(1,r-k+1),Y1=max(1,i-k+1),X2=l,Y2=i;
			a[X1][Y1]++;
			a[X2+1][Y2+1]++;
			a[X2+1][Y1]--;
			a[X1][Y2+1]--;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1]+a[i][j];//求二维前缀和
			ans=max(ans,f[i][j]);
		}
	}
	cout<<ans+cnt<<endl;
	return 0;
}

```

*[Froggy's blog](https://www.luogu.org/blog/1445353309froggy/)*


---

## 作者：kimidonatsu (赞：2)

考虑至少包含一个黑格的单行。

如果第一个黑格出现在第 $l$ 列，最后一个黑格出现在第 $r$ 列，不难想出可以在一些预处理操作（例如二维前缀和）之后以 $O(1)$ 的复杂度确定当点击 $(i, j)$ 时它是否被覆盖成白线。

因为只能覆盖 $k \times k$ 的范围，所以只有当行数在 $[i, i + k - 1]$ 范围内且 $j \le l \le r \le j + k - 1$ 时，它才会变成白线，那就预处理出 $l$ 和 $r$。

再考虑所有的 $n$ 行（而不是列，稍后做法延伸即可，没有太大区别）。首先，计算在点击之前已经是白线的行数，然后从第 $1$ 到 $k$ 行跑一边检查，计算当点击 $(1, 1)$ 时的白行数并去掉之前计算过的已经是白线的行数。

跑完后我们就得到了点击 $(1, 1)$ 时的白线行数。这种问题肯定会想到滑动窗口：将第 $k + 1$ 行滑进来并删掉第 $1$ 行，然后跑一下上面的 check 流程，就可以获得点击 $(2, 1)$ 时的白线行数。

重复直到计算出所有点击第 $1$ 列的 $n - k + 1$ 种情况。然后，对所有的 $n - k + 1$ 列重复整个过程。

计算白色列的方法一样，在知道每个单元格被点击时的白行数和白列数之后选取它们之中和的最大值即可。

时间复杂度为 $O(n^2)$，足以通过。

[Submission](https://codeforces.com/contest/1200/submission/261771450)

---

## 作者：奇米 (赞：2)

# $\mathrm{CF1200D \ White \ Lines}$   题解

[$$\huge\color{blue}\boxed{\color{Violet}\mathfrak{There\ is \ my \ blog}}$$](https://www.luogu.com.cn/blog/wyy2020/)

### 题目意思
* [CF1200D White Lines](https://www.luogu.com.cn/problem/CF1200D)
* $wzbl$做了好久才想出来，比赛可怎么办啊！！

### $\mathrm{Sol}$
* 前置知识：**二维差分**
* 我们首先考虑哪个点为选择正方形的左上角会对改行产生贡献
* 我们对于一行进行考虑，设最左黑格位置为$l$，最右黑格为$r$，那么如果$r-l+1>m$显然无法做出贡献。当我们把一个以$(r-m+1,i-m+1)$为左上角，$(i,l)$为右下角的矩形才会有贡献（我这个考虑了很久，还是$tcl$）。
* 列与行计算贡献方法同理，然后二维前缀和统计最大贡献的位置（选择矩阵左上角）
* 最后我们只要把原本就完整（全部都是白的）计入答案就好了
* 代码会做出清晰的解释

### $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int N=2e3+5;

int n,m,a[N][N],c[N][N],ans;
char ch[N][N];

int main()
{
	n=read();
	m=read();
	for ( int i=1;i<=n;i++ )
		scanf("%s",ch[i]+1);
	for ( int i=1;i<=n;i++ )
	{
		int l=n+1,r=0;
		for ( int j=1;j<=n;j++ )
			if(ch[i][j]=='B')
			{
				l=min(l,j);
				r=max(r,j);//寻找黑块最左以及最右
			}
		if(l==n+1&&!r) ans++;//全部都是白的
		else 
		{
			if(r-l+1>m) continue;//不合法情况
			int sx=max(1,i-m+1),sy=max(1,r-m+1);
			int ex=i,ey=l;
			a[sx][sy]++;
			a[ex+1][ey+1]++;
			a[sx][ey+1]--;
			a[ex+1][sy]--;//二维差分
		}
	}
	for ( int i=1;i<=n;i++ )//列同理
	{
		int l=n+1,r=0;
		for ( int j=1;j<=n;j++ ) 
			if(ch[j][i]=='B')
			{
				l=min(l,j);
				r=max(r,j);
			}
		if(l==n+1&&!r) ans++;
		else 
		{
			if(r-l+1>m) continue;
			int sy=max(1,i-m+1),sx=max(1,r-m+1);
			int ey=i,ex=l;
			a[sx][sy]++;
			a[ex+1][ey+1]++;
			a[sx][ey+1]--;
			a[ex+1][sy]--;
		}
	}
	for ( int i=1;i<=n;i++ ) 
		for ( int j=1;j<=n;j++ ) 
			c[i][j]+=c[i-1][j]+c[i][j-1]-c[i-1][j-1]+a[i][j];//二位前缀和
	int cwy=0;
	for ( int i=1;i+m-1<=n;i++ ) 
		for ( int j=1;j+m-1<=n;j++ ) 
			cwy=max(cwy,c[i][j]);//寻找贡献最大的选择矩形左上角
	ans+=cwy;
	printf("%d\n",ans);
	return 0;
}
			
```


---

## 作者：Llf0703 (赞：2)

[更好的阅读体验](https://llf0703.com/p/cf-1200.html#dwhitelines)

## 题意

有一个 $N\times N$ 的矩阵，格点有黑白两种颜色。现在可以把 $K\times K$ 的矩形染白，求最多有多少行和列全为白色。

$K\le N\le 2000$ 。

## 题解

先只考虑行的情况。

用 $s[i][j]$ 存下图的情况，黑色为 $1$ ，白色为 $0$ ，然后对行作前缀和为 $x[i][j]$ 。

这样就可以预处理出在第 $i$ 行，如果选择 $j$ 为左上角，能否把当前行染白。具体方法是判断 $[j,j+k-1]$ 这段区间是否包含了这一行所有的黑色格点，即 $x[i][j+k-1]-x[i][j-1]=x[i][n]$ 。将结果记录在 $vx[i][j]$ 。

然后将 $vx[i][j]$ 作列上的前缀和，记录为 $vxs[i][j]$ 。

可以纵向统计出如果以 $(i,j)$ 为左上角，可以染白的行有多少个。具体的方法为将 $[i,i+k-1]$ 区间上所有的 $vx[i][j]$ 加起来，即 $vxs[i+k-1][j]-vxs[i-1][j]$ ，把这个值重新赋给 $vx[i][j]$ 。

列的情况同理，最后记录在 $vy[i][j]$ 。

答案即为 $\max (vx[i][j]+vy[i][j])$ 。注意**最后统计的时候上界一定是 $n-k+1$** ，我就因为这个导致 `Wrong answer on pretest 12` ，然后结束了才过的。

还有如果某行或列最开始就是白色，那就把它统计进 $cnt$ ，然后在统计 $vx$ 时就跳过。最后把 $cnt$ 加进答案。

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while (ch<'0' || ch>'9')
    {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return f*x;
}

char ch[2005];
int n,k,s[2005][2005],x[2005][2005],y[2005][2005],vx[2005][2005],vy[2005][2005],vxs[2005][2005],vys[2005][2005];

signed main()
{
    n=read(); k=read();
    for (int i=1;i<=n;i++)
    {
        scanf("%s",ch+1);
        for (int j=1;j<=n;j++)
        {
            s[i][j]=ch[j]=='B';
            x[i][j]=x[i][j-1]+s[i][j];
        }
    }
    for (int j=1;j<=n;j++) for (int i=1;i<=n;i++) y[i][j]=y[i-1][j]+s[i][j];
    int cnt=0; //最开始就为白线的个数
    for (int i=1;i<=n;i++)
    {
        if (x[i][n]==0) { cnt++; continue; } //最开始就为白线，跳过
        for (int j=1;j<=n;j++)
        {
            if (x[i][j+k-1]-x[i][j-1]==x[i][n]) vx[i][j]++;
        }
    }
    for (int j=1;j<=n;j++)
    {
        if (y[n][j]==0) { cnt++; continue; }
        for (int i=1;i<=n;i++)
        {
            if (y[i+k-1][j]-y[i-1][j]==y[n][j]) vy[i][j]++;
        }
    }
    for (int j=1;j<=n;j++)
    {
        for (int i=1;i<=n;i++)
        {
            vxs[i][j]=vxs[i-1][j]+vx[i][j]; //vxs是vx的前缀和
        }
    }
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++)
        {
            vys[i][j]=vys[i][j-1]+vy[i][j];
        }
    }
    for (int j=1;j<=n;j++)
    {
        for (int i=1;i<=n-k+1;i++)
        {
            vx[i][j]=vxs[i+k-1][j]-vxs[i-1][j]; //把连续k个的和赋回来
        }
    }
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n-k+1;j++)
        {
            vy[i][j]=vys[i][j+k-1]-vys[i][j-1];
        }
    }
    int ans=0;
    for (int i=1;i<=n-k+1;i++) for (int j=1;j<=n-k+1;j++) ans=max(ans,vx[i][j]+vy[i][j]); //统计答案
    cout<<ans+cnt<<endl;
    return 0;
}
```

---

## 作者：试试事实上吗 (赞：1)

突然发现自己的做法很清奇，于是就来写一篇题解了。

~~觉得自己还是可以，居然没用二维的东西维护答案~~

题意是在一个黑白矩阵上选一个小矩形染色为白，让全白的行列最多。

### Part.1

考虑一种最暴力的做法，我们枚举小矩阵的左上角，暴力染色后统计行列的数量。

这个算法的时间复杂度为$O((n-k)^2*k)$，可以通过$n,k<=400$或$n,k$值接近的点。

但这个算法在$k=\frac{n}{2}$时复杂度会被卡成$O(n^3)$。~~但如果出题人数据水可能可以比正解跑的快~~

### Part.2

先来考虑一列的答案。

如果这一列全是白色，无论在哪里时它都有贡献，先预处理出来。

考虑我们在每次枚举到$i,j$，往$i,j+1$继续枚举时，我们只用转移一列，如图。

![](https://i.loli.net/2020/07/27/HQjrb9cmUAPyRwl.png)

此时只有两边的答案更新了，我们只需要考虑如何更新这两列的答案即可。

考虑对每一列做一个前缀和统计黑点的个数，每次从答案中减去左边那列的贡献，加上右边的贡献就可以了（贡献就是如果这段的黑点个数等于这列的黑点个数，答案就加一）。

### Part.3

我们再来考虑如何统计一行的贡献。

如果这一行全是白色，同理的，先预处理出来。

同样的，我们在从$i$往$i+1$枚举时，也只用更新一行的答案。

考虑如何统计一行的贡献，先只看一行，我们枚举到$i$时包含了$[i,i+k-1]$这个区间。

我们考虑只有这个区间包含了所有黑点时才对答案有贡献，所以我们只用记录下最左边的黑点与最右边的黑点。

如图，只有在包含了整个区间时才有贡献，如果它的区间大小没有整个区间大，那这行就永远没有贡献。

![](https://i.loli.net/2020/07/27/4lL69uj1vQX2oSg.png)

所以拓展到$k$行，我们只需要计算枚举到$i$时每行的一个区间时对答案是否有贡献即可。

但这里是不是要用到数据结构呢，实际上不用，我们这里的问题比这个要弱的多。

显然$[i,i+k-1]$这个区间它只有它的左端点决定，我们可以只统计这个区间的左端点在哪个区间合法。

设左黑点的位置是$L$，右黑点的位置是$R$，那么整个区间能被全覆盖的充要条件是$R-k+1\leq i\leq L$，那么我们只需要对$[R-k+1,L]$区间打标记即可。

这里这个步骤的的实现不需要用任何数据结构，考虑我们只用枚举的每一行进行一次这样的操作，需要$n-k$次，但是我们的查询操作需要每个位置进行一次，即$(n-k)^2$次。所以我们可以直接用一个数组暴力打标记，这样是$O(n)$的，查询查一个点，是$O(1)$的，可以通过。

总时间复杂度除开读入外是$O((n-k)\times n)$的，可以通过。

### $Code$

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int maxn=2005;

char s[maxn][maxn];
int sum[maxn][maxn];
int vis[maxn],n,k;
int L[maxn],R[maxn],hans,lans,ans,llans;

inline int max(const int &x,const int &y)
{
    return x>y?x:y;
}

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
        scanf("%s",s[i]+1);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            if(s[i][j]=='B') {L[i]=j;break;}
    for(int i=1;i<=n;++i)
        for(int j=n;j>0;--j)
            if(s[i][j]=='B') {R[i]=j;break;}
    for(int j=1;j<=n;++j)
    {
        for(int i=1;i<=n;++i)
        {
            sum[i][j]=sum[i-1][j];
            if(s[i][j]=='B') sum[i][j]++;
        }
        if(sum[n][j]==0) llans++;
    }
    for(int i=1;i<=n;++i)
        if(L[i]==0&&R[i]==0) hans++;
    for(int i=1;i<=k;++i)
    {
        if(R[i]-L[i]+1>k) continue;
        for(int j=max(1,R[i]-k+1);j<=L[i];++j)
            ++vis[j];
    }
    for(int i=1;i<=n-k+1;++i)
    {
        if(i!=1)
        {
            for(int j=max(1,R[i-1]-k+1);j<=L[i-1];++j) 
                --vis[j];
            for(int j=max(1,R[i+k-1]-k+1);j<=L[i+k-1];++j) 
                ++vis[j];
        }
        lans=llans;
        for(int j=1;j<=k;++j)
            if(sum[n][j]&&sum[i+k-1][j]-sum[i-1][j]==sum[n][j]) lans++;
        ans=max(ans,lans+vis[1]);
        for(int j=2;j<=n-k+1;++j)
        {
            if(sum[n][j-1]&&sum[i+k-1][j-1]-sum[i-1][j-1]==sum[n][j-1]) lans--;
            if(sum[n][j+k-1]&&sum[i+k-1][j+k-1]-sum[i-1][j+k-1]==sum[n][j+k-1]) lans++;
            ans=max(ans,lans+vis[j]);
        }
    }
    printf("%d\n",ans+hans);
    return 0;
}
```

码字不容易，求过$QwQ$。

~~另外图是不是有点丑~~





---

## 作者：学委 (赞：1)

对于每个第 i 行，考虑盖在哪些点可以使这一行变白。（盖在某个点意思是橡皮左上角在这个点）。

如果这一行最左端的黑点是 l，最右端黑点是 r：

- 如果 r - l + 1 > k(橡皮擦宽度)，那么不存在能消除这一行的点。

- 否则，考虑以(i - k + 1, r - k + 1)为左上角，(i, l)为右下角的矩形，其中任何一个点都可以盖。这些点的答案加 1，这个可以用二维前缀和维护。

对于每个第 i 列也用一样的方法。然后暴力更新答案。

```cpp
#include <cstdio>
#include <algorithm>
using std::max;
using std::min;
 
int n, k;
char g[4010][4010];
int ans = 0, c[4010][4010];
 
void add(int x, int y, int w) {
  c[max(x, 1)][max(y, 1)] += w;
}
 
int main() {
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%s", g[i] + 1);
  for (int i = 1; i <= n; ++i) {
    int l = 0, r = 0;
    for (int j = 1; j <= n; ++j)
      if (g[i][j] == 'B') {
        if (l == 0)
          l = j;
        r = j;
      }
    if (r == 0) {
      ++ans;
      continue;
    }
    if (r - l + 1 > k)
      continue;
    
    add(i - k + 1, r - k + 1, 1);
    add(i + 1, r - k + 1, -1);
    add(i - k + 1, l + 1, -1);
    add(i + 1, l + 1, 1);
  }
  for (int j = 1; j <= n; ++j) {
    int u = 0, d = 0;
    for (int i = 1; i <= n; ++i)
      if (g[i][j] == 'B') {
        if (u == 0)
          u = i;
        d = i;
      }
    if (d == 0) {
      ++ans;
      continue;
    }
    if (d - u + 1 > k)
      continue;
    
    add(d - k + 1, j - k + 1, 1);
    add(d - k + 1, j + 1, -1);
    add(u + 1, j - k + 1, -1);
    add(u + 1, j + 1, 1);
  }
  for (int j = 1; j <= n; ++j)
    for (int i = 1; i <= n; ++i)
      c[i][j] += c[i - 1][j];
  int max_c = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      c[i][j] += c[i][j - 1];
      max_c = max(max_c, c[i][j]);
    }
  printf("%d\n", ans + max_c);
  return 0;
}
```

---

## 作者：fsy_juruo (赞：0)

### 一些废话

当场打这场 CF 的时候，这题没调出来，C 题又 FST 了，自闭了。

然后这题跑到了模拟赛里，一眼看出原题，结果忘记了做法...

### 题目简述

* 给定一个 $n \times n$ 的 黑-白 矩阵
* 你可以选出一个 $k \times k$ 的子矩阵，将这个子矩阵里的黑格子全部设为白格子
* 求操作一次之后，全是白色的行与全是白色的列之和的最大值
* $n, k \leq 2000$

### 题解

首先，我们设 $l(j)$ 为第 $j$ 行最左边黑格的位置，$r(j)$ 为第 $j$ 行最右边黑格的位置。假设我们选择的子矩阵左上角坐标为 $(x, y)$ 且能覆盖到第 $j$ 行，则第 $j$ 列能全部变成白色，当且仅当 $y \leq l(j) \leq r(j) \leq y+k-1$ 或者这一行一开始就没有黑格。因此，对于每一行，我们可以 $O(1)$ 判断这一行能不能被全部变成白色。

于是，我们可以先用 $O(n)$ 算出若选择的子矩阵左上角是 $(1,1)$ 时，会有多少行全是白色（为什么不是 $O(k)$？因为第 $k+1 \sim n$ 行会有一开始就是全是白色的行），然后使用 **滑动窗口** 的思想，依次算出 $(i,1)$ 的答案。

其余坐标与处理列的方法也如法炮制。具体细节详见代码注释。

### 代码

```cpp
#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define LD long double
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define _per(i, x, y) for(int i = x; i >= y; i--)
template <typename T>
inline void read(T &x) {
	x = 0; T f = (T) 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) {if(c == '-') f = -f;}
	for(; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
template <typename T>
inline void write(T x) {
	if(x < 0) {x = -x; putchar('-');}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T>
inline void writesp(T x, char sp = ' ') {
	write(x); putchar(sp);
}
const int maxN = 2e3 + 10;
int n, k;
int col[maxN][maxN], l_row[maxN], r_row[maxN], l_col[maxN], r_col[maxN]; // l_row：题解内的 l(j)，r_row：题解内的 r(j)
int dp_row[maxN][maxN], dp_col[maxN][maxN];
// dp_row(i,j)：将以 (i,j) 为左上角的 k*k 子矩阵涂白后，全部为白色的行的个数。dp_col(i,j) 同理。
bool is_empty1(int r) {return (!l_row[r] && !r_row[r]);}
bool is_empty2(int c) {return (!l_col[c] && !r_col[c]);}
// is_empty：判断对应行或列是否在一开始就全是白格。
bool is_emptyrow(int st, int k, int r) {return (st <= l_row[r] && r_row[r] <= st + k - 1);}
bool is_emptycol(int st, int k, int c) {return (st <= l_col[c] && r_col[c] <= st + k - 1);}
// is_emptyrow（col）：判断对应行或列是否在涂白 [st,st+k-1] 区间后就全是白格。
int main() {
	read(n); read(k);
	_rep(i, 1, n) {
		std::string s; getline(std::cin, s);
		_rep(j, 1, n) {col[i][j] = (s[j - 1] == 'B');}
	}
	_rep(i, 1, n) {
		_rep(j, 1, n) {if(col[i][j]) {l_row[i] = j; break;}}
		_per(j, n, 1) {if(col[i][j]) {r_row[i] = j; break;}}
	}
	_rep(i, 1, n) {
		_rep(j, 1, n) {if(col[j][i]) {l_col[i] = j; break;}}
		_per(j, n, 1) {if(col[j][i]) {r_col[i] = j; break;}}
	} // 以上为预处理 l(j)，r(j)。
	_rep(i, 1, n - k + 1) {
		int cnt = 0;
		_rep(j, 1, k) {cnt += (is_empty1(j) || is_emptyrow(i, k, j));}
		_rep(j, k + 1, n) cnt += (is_empty1(j));
        // 计算将以 (1,i) 为左上角的 k*k 子矩阵涂白后，全是白格的行数。
		dp_row[1][i] = cnt;
		_rep(j, 2, n - k + 1) { 
			if(is_emptyrow(i, k, j - 1) && !is_empty1(j - 1)) cnt--;
			if(is_emptyrow(i, k, j + k - 1) && !is_empty1(j + k - 1)) cnt++;
            // 滑动窗口部分。注意：不要去掉一开始就已经是全是白格的行 
			dp_row[j][i] = cnt;
		}
	}
	_rep(i, 1, n - k + 1) {
		int cnt = 0;
		_rep(j, 1, k) {cnt += (is_emptycol(i, k, j) || is_empty2(j));}
		_rep(j, k + 1, n) cnt += is_empty2(j);
		dp_col[i][1] = cnt;
		_rep(j, 2, n - k + 1) {
			if(is_emptycol(i, k, j - 1) && !is_empty2(j - 1)) cnt--;
			if(is_emptycol(i, k, j + k - 1) && !is_empty2(j + k - 1)) cnt++;
			dp_col[i][j] = cnt;
		}
	}
	int ans = 0;
	_rep(i, 1, n - k + 1) {
		_rep(j, 1, n - k + 1) {
			ans = std::max(ans, dp_row[i][j] + dp_col[i][j]);
		}
	}
	writesp(ans, '\n');
	return 0;
}
```

---

## 作者：cjrhahahahaha (赞：0)

想了很久的二维滑动窗口，恍然发现是计算贡献

先对每一行和列处理出最左和右（上和下）的  “B” 点

显然要使这一行（或列）对答案产生贡献只需覆盖这两个点即可

那么这一行就对如下区间产生了贡献(图咕了~~~）

差分修改即可

code

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn=2005; 
int min_l[maxn],min_h[maxn],max_l[maxn],max_h[maxn];//一行或者一列第一个和最后一个出现的黑点 
int n,k;
int sum_h[maxn][maxn],sum_l[maxn][maxn],sum[maxn][maxn];//每一行以及每一列的差分值，以及最后的单点总和 
int ans=-1,temp=0;//答案 ，特殊情况 
int main()
{
scanf("%d %d",&n,&k);
for(int i=1;i<=n;i++)min_h[i]=2001,min_l[i]=2001;//预处理 
for(int i=1;i<=n;i++)
for(int j=1;j<=n;j++)
{
	char x;
	cin>>x;
	if(x=='B')
	{
	min_h[i]=min(min_h[i],j);
	max_h[i]=max(max_h[i],j);
	min_l[j]=min(min_l[j],i);
	max_l[j]=max(max_l[j],i);//每一行出现的最大与最小黑色端点	
	}	
}
for(int i=1;i<=n;i++)
{
	if(min_h[i]==2001)temp++;//特殊情况（全白） 
	else if(max_h[i]-min_h[i]+1<=k)
	{
		int l=max(max_h[i]-k+1,1),r=min_h[i],up=max(1,i-k+1),down=i;
		for(int a=up;a<=down;a++)
		{
			sum_h[a][l]++;sum_h[a][r+1]--;//维护一行的差分 
		}
	}
	if(min_l[i]==2001)temp++;//同上 
	else if(max_l[i]-min_l[i]+1<=k)
	{
		int l=max(max_l[i]-k+1,1),r=min_l[i],up=max(1,i-k+1),down=i;
		for(int a=up;a<=down;a++)
		{
			sum_l[a][l]++;sum_l[a][r+1]--;//维护一列的差分 
		}
	}
	
}
for(int i=1;i<=n;i++)
{
	int haha=0;
	for(int j=1;j<=n;j++)
	{
		haha+=sum_h[i][j];
		sum[i][j]+=haha;
	}
}//枚举每一行的状态，差分和得到当前点每一行的状态 
for(int j=1;j<=n;j++)//因为是列，所以i，j要反着一下，保持和行的编号相同 
{
	int haha=0;
	for(int i=1;i<=n;i++)
	{
		haha+=sum_l[j][i];
		sum[i][j]+=haha;
	}
}//同上加上当前点每一列的状态 
for(int i=1;i<=n;i++)
{
	for(int j=1;j<=n;j++)
	{
		ans=max(ans,sum[i][j]);
	}
}//对于每一个点求得对答案的更新 
cout<<ans+temp<<endl;//记得还有特殊的情况要加上的 
return 0;
}
```

---

## 作者：破壁人五号 (赞：0)

这里介绍一种 $O(\text{玄学})$（应该是 $O(n(n-k)\log k)$？）的做法

> 当时想到此做法时：计算器算一下 $n^2\log n$ 好像过不了？写一下试一下

> 写完之后：试一下极端数据，跑了 2s+怕是过不了，交一发试一下（一不小心忘取消 `freopen`，还好挂在样例不扣分，再交一次）

> 过了 Pretest 之后：这都能 PP？坐等 FST。

> 第二天一看：Accepted

考虑枚举橡皮擦的位置，并分别求出橡皮擦在每个位置时，行和列分别会增加多少个 WL(White Line(s)，下同)

这里以计算行上增加的 WL 为例：

先预处理出每一（有黑色的）行的黑色段的左端与右端

枚举橡皮擦在哪几行，将这几行的黑色段的左端与右端排序。然后从左往右枚举橡皮擦的位置，并维护指针 $pl,pr$，集合 $s$。

当橡皮擦移动到一个新位置时，右移 $pl$ 扫过所有已经退出橡皮擦范围的（行的黑色段的）左端，并从集合 $s$ 中删除这一行（如果 $s$ 中没有这一行就打上标记，代表这一行不可能变成 WL）；然后右移 $pr$ 扫过所有已经进入橡皮擦范围的（行的黑色段的）右端，假如这一行没有标记，便将这一行插入集合 $s$。

最后枚举每一格取 $\max$ 即可

下面代码有些乱，`set<pair<int,pair<int,bool> > >e` 可以直接排序维护，`set<int> s` 可以直接用一个数组记录 tag：

```cpp
#include<bits/stdc++.h>
using namespace std;
 
int getint(){
    int ans=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0'){
        if(c=='-')f=-1;
        c=getchar();
	}
    while(c>='0'&&c<='9'){
        ans=ans*10+c-'0';
        c=getchar();
    }
    return ans*f;
}
bool a[2010][2010];
int rl[2010],rr[2010],cl[2010],cr[2010];//行（列）的黑色段的左（优、上、下端）
int rcnt[2010][2010],ccnt[2010][2010];//橡皮擦在此处时，行、列增加的 WL 数量
int main(){
	int n=getint(),k=getint();
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			char c=getchar();
			while(c>'Z'||c<'A')c=getchar();
			a[i][j]=(c=='B');
		}
	}
	memset(rl,0x3f,sizeof(rl));
	memset(cl,0x3f,sizeof(cl)); 
	int qaq=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(a[i][j]){
				cl[j]=min(cl[j],i);
				cr[j]=max(cr[j],i);
				rl[i]=min(rl[i],j);
				rr[i]=max(rr[i],j);
			}
		}
	}
	for(int i=0;i<n;i++){
		qaq+=(cl[i]>cr[i]);//本身就是 WL
		qaq+=(rl[i]>rr[i]);
	}
	for(int i=0;i<n-k+1;i++){
		set<pair<int,pair<int,bool> > >e;//所有行的黑色段的左（右）端点
		unordered_set<int>s,gg;//gg:被标记的集合
		for(int j=i;j<i+k;j++){
			if(rl[j]>rr[j])continue;//本身就是 WL 的行已经单独计算
			e.insert(make_pair(rl[j],make_pair(j,0)));
			e.insert(make_pair(rr[j],make_pair(j,1)));
			//cout<<"r "<<rl[j]<<" "<<rr[j]<<endl;
		}
		auto itl=e.begin(),itr=e.begin();//即题解中的 pl,pr
		for(int j=0;j<n-k+1;j++){
			//cout<<"?? "<<itr->first<<" "<<itl->first<<endl;
			while(itr!=e.end()&&(itr->second.second==0||itr->first<=j+k-1)){
				//if(itr->second.second)cout<<">. "<<itr->second.first<<endl;
				if(itr->second.second&&!gg.count(itr->second.first))
					s.insert(itr->second.first);
				++itr;//右移 pr
			}
			while(itl!=e.end()&&(itl->second.second==1||itl->first<j)){
				//if(!itl->second.second)cout<<"<. "<<itl->second.first<<endl;
				auto it=s.find(itl->second.first);
				if(itl->second.second==0&&it!=s.end())
					s.erase(it);
				else gg.insert(itl->second.first);
				++itl;//右移 pl
			} 
        //上面两个指针的处理顺序可以交换
			rcnt[i][j]=s.size();
			//cout<<"rcnt "<<i<<" "<<j<<" "<<rcnt[i][j]<<endl;
		}
	}
	for(int i=0;i<n-k+1;i++){//列同理
		set<pair<int,pair<int,bool> > >e;
		set<int>s,gg;
		for(int j=i;j<i+k;j++){
			if(cl[j]>cr[j])continue; 
			e.insert(make_pair(cl[j],make_pair(j,0)));
			e.insert(make_pair(cr[j],make_pair(j,1)));
		}
		auto itl=e.begin(),itr=e.begin();
		for(int j=0;j<n-k+1;j++){
			//cout<<"?? "<<itr->first<<" "<<itl->first<<endl;
			while(itr!=e.end()&&(itr->second.second==0||itr->first<=j+k-1)){
				//if(itr->second.second)cout<<">. "<<itr->second.first<<endl;
				if(itr->second.second&&!gg.count(itr->second.first))
					s.insert(itr->second.first);
				++itr;
			}
			while(itl!=e.end()&&(itl->second.second==1||itl->first<j)){
				//if(!itl->second.second)cout<<"<. "<<itl->second.first<<endl;
				auto it=s.find(itl->second.first);
				if(itl->second.second==0&&it!=s.end())
					s.erase(it);
				else gg.insert(itl->second.first);
				++itl;
			} 
			ccnt[j][i]=s.size();
			//cout<<"ccnt "<<j<<" "<<i<<" "<<ccnt[j][i]<<endl;
		}
	}
	int ans=0;
	for(int i=0;i<n-k+1;i++){
		for(int j=0;j<n-k+1;j++){
			//cout<<i<<" "<<j<<" "<<ccnt[i][j]<<" "<<rcnt[i][j]<<endl;
			ans=max(ans,ccnt[i][j]+rcnt[i][j]);
		}
	}
	cout<<ans+qaq;
	return 0;
}
```


---

## 作者：communist (赞：0)

#### 退役快一年了之后又打了场紧张刺激的$CF$~~（斜眼笑）~~

#### 然后发现$D$题和题解里的大众做法不太一样 ~~（思路清奇）~~

题意不再赘述，我们可以看到这个题~~好做~~在只有一次擦除机会，尝试以此为突破口解决问题

我们考虑擦除某一行（列同理），分别记录这一行最左端和最右端的黑块位置（分别记为$l,r$）

### 这里存在以下三种情况：

1，这一行没有黑块，这时无论在哪擦除，这一行必然全白，记录答案后不再考虑

2，这一行的最左黑块和最右黑块之间的距离$>k$（即$r-l+1>k$），这时无论在哪擦除，这一行必然不会全白，不再考虑

3，这一行最左黑块和最右黑块之间的距离$<=k$，考虑能够使得这一行全为白色的擦除位置（假设我们当前考虑的是第$i$行）

容易得出，对于擦除位置的选择

可行的行：第$i-k+1((i-k+1)+k-1=i)$行到第$i$行

可行的列：第$l-k+1((l-k+1)+k-1=l)$列到第$l$列

即如果擦除位置$(x,y)$满足$i-k+1<=x<=i$且$l-k+1<=y<=l$，这一次擦除可以使第$i$行变白

### 对于答案统计，自然想到二维前缀和

我们只需在位置$(i-k+1,l-k+1),(i+1,l+1)+1$，$(i-k+1,l+1),(i+1,l-k+1)-1$即可（二维差分的常规操作）

差分完了再做前缀和即可得出答案（别忘了累加情况一的答案）

$P.S.i-k+1$和$l-k+1$不要数组越界

### 上代码：

```
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=2010;
int n,k,ans[maxn][maxn],l[2][maxn],r[2][maxn],res,bs;
bool exi[maxn][maxn];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		for(int j=0;j<n;j++)
			if(s[j]=='W')
				exi[i][j+1]=0;
			else
				exi[i][j+1]=1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			if(exi[i][j])
			{
				l[0][i]=j;
				break;
			}
		for(int j=n;j;j--)
			if(exi[i][j])
			{
				r[0][i]=j;
				break;
			}
		if(!l[0][i])
			bs++;
	}
	for(int j=1;j<=n;j++)
	{
		for(int i=1;i<=n;i++)
			if(exi[i][j])
			{
				l[1][j]=i;
				break;
			}
		for(int i=n;i;i--)
			if(exi[i][j])
			{
				r[1][j]=i;
				break;
			}
		if(!l[1][j])
			bs++;
	}
	for(int i=1;i<=n;i++)
	{
		if(l[0][i]&&r[0][i]-l[0][i]+1<=k)
		{
			int minx=max(i-k+1,1),miny=max(1,r[0][i]-k+1);
			ans[minx][miny]++;
			ans[i+1][miny]--;
				ans[minx][l[0][i]+1]--;
				ans[i+1][l[0][i]+1]++;
		}
		if(l[1][i]&&r[1][i]-l[1][i]+1<=k)
		{
			int miny=max(i-k+1,1),minx=max(1,r[1][i]-k+1);
			ans[minx][miny]++;
			ans[minx][i+1]--;
				ans[l[1][i]+1][miny]--;
				ans[l[1][i]+1][i+1]++;
		}
	}
	for(int i=1;i<=n-k+1;i++)
		for(int j=1;j<=n-k+1;j++)
		{
			ans[i][j]+=ans[i-1][j]+ans[i][j-1]-ans[i-1][j-1];
			res=max(res,ans[i][j]);
		}
	printf("%d\n",res+bs);
	return 0;
}
```

---

