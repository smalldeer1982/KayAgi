# [USACO19FEB] Painting the Barn G

## 题目描述

Farmer John 不太擅长多任务处理。他经常分心，很难完成一些长期的项目。目前，他正在谷仓的一侧刷油漆，但他一直忙着在很小的区域涂抹油漆，然后由于抚育母牛的需要而陷入困境，使谷仓的某些部分比其他部分涂有更多的油漆。

我们将谷仓的墙描述为一个 X-Y 平面，每次涂油漆的区域都是一个矩形。FJ 在这个平面上绘制了 $N$ 个矩形，每个矩形的边均与坐标轴平行。因此我们用矩形的左下角和右上角坐标来描述一个矩形。

FJ 想在谷仓里涂几层油漆，这样就不需要在不久的将来再次重新涂油漆。但是，他不想浪费时间涂过多的油漆。事实证明，$K$ 层涂料是最佳用量。但是因为涂油漆的面积太小了，FJ 并不太高兴。他决定最多再绘制两个**不相交**的矩形（这里的相交指两个矩形交的面积大于零，即如果两个矩形仅共用一条边或一个点，则不视为相交）来增加面积。当然不绘制新矩形或仅绘制一个新矩形也是允许的。

## 样例 #1

### 输入

```
3 2
1 1 4 4
3 3 7 6
2 2 8 7```

### 输出

```
26```

# 题解

## 作者：Time_tears (赞：10)

提供一篇 $O(200^3+n)$ 的题解

- 首先看完本题，一定知道直接对每个位置加 $1$ 是绝对没有出路的，所以我们首先需要用一个差分处理一下每个位置的值，这部分复杂度是 $O(200^2+n)$  的。

- 然后，我们要想，什么样的位置会对 $answer$ 有影响呢$？$ 当然是值为 $k-1,k$ 的位置，首先我们用一个 $sum$ 记录下值为 $k$ 的位置数量。然后我们就发现，给区间加 $1$ 后，值为 $k$ 的位置贡献为 $-1$ ，值为 $k-1$ 的贡献为 $1$ ，然后我们枚举 $i,j$ 把第 $i$ 至 $j$ 的数给提出来，用一次最大连续子段和，这样就能求出以 $(i,j)$ 为右下节点的最大的值，再反过来做一次，就能求出以 $(i,j)$ 为左上节点的最大的值

- 因为是求两个区间，所以最后再用一次 dp 即可。

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<cstdio>
#define N 205
using namespace std;
int k,e[N][N],f[N][N],d[N][N],ans;
int n,a[N][N],b[N][N],c[N][N],sum;
const int Mxdt=200000;
inline char gc() {
	static char buf[Mxdt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
inline int read() {
	int res=0,bj=0;
	char ch=gc();
	while(ch<'0'||ch>'9')bj|=(ch=='-'),ch=gc();
	while(ch>='0'&&ch<='9')res=(res<<3)+(res<<1)+(ch^48),ch=gc();
	return bj?-res:res;
}
inline int max(int x,int y) {
	return x>y?x:y;
}
int main() {
	n=read(),k=read();
	for(int i=1,x1,y1,x2,y2; i<=n; ++i)++a[x1=read()+1][y1=read()+1],++a[x2=read()+1][y2=read()+1],--a[x1][y2],--a[x2][y1];
	for(int i=1; i<=200; ++i)
		for(int j=1; j<=200; ++j) {
			a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1],b[i][j]=b[i][j-1];
			if(a[i][j]==k)--b[i][j],++sum;
			if(a[i][j]==k-1)++b[i][j];
		}
	for(int i=1; i<=200; ++i)
		for(int j=i; j<=200; ++j) {
			for(int k=1,len=0; k<=200; ++k)c[k][j]=max(c[k][j],len=max(0,len)+b[k][j]-b[k][i-1]);
			for(int k=200,len=0; k; --k)d[k][i]=max(d[k][i],len=max(0,len)+b[k][j]-b[k][i-1]);
		}
	for(int i=200; i; --i)
		for(int j=200; j; --j)f[i][j]=max(max(f[i+1][j],f[i][j+1]),d[i][j]);
	for(int i=1; i<=200; ++i)
		for(int j=1; j<=200; ++j)e[i][j]=max(max(e[i-1][j],e[i][j-1]),c[i][j]),ans=max(ans,sum+e[i][j]+max(f[i+1][1],f[1][j+1]));
	printf("%d",ans);
	return 0;
}
```


---

## 作者：「　」 (赞：6)

本题解提供的做法思路应该是比较清晰的，可惜代码实现比较繁琐，仅供大家参考。

## 题解
不难发现 $x$ ，$y$ 的取值范围只有 $200$ ，所以我们可以考虑从这里入手。我们可以先通过二维前缀和将每个点的上色次数算出来，然后考虑再画矩形。

我们可以先考虑一个矩形的情况，不难发现，如果矩形内的每有一个 $k-1$ 可以使答案加一，每有一个 $k$ 可以使答案减一。那如果我们要使答案最大，肯定是 $1$ 与 $-1$ 的最大的一个矩阵，发现就是做一个最大矩阵和，可以 $O(200^3)$ 去搞。

我们再来考虑两个矩形的情况，不难发现，如果是两个边与 $x$ 轴和 $y$ 轴平行的不相交的矩形，我们肯定可以用一条平行与 $x$ 轴或 $y$ 轴的直线将其分开。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/h8ipn5ak.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/lfflmvso.png)

所以我们只需要将整个平面通过平行于 $x$ 轴和 $y$ 轴的直线分成两部分，再在其中做最大矩阵和就可以了。

当然直接做是肯定会炸的，所以你需要进行一堆的预处理和前缀和，仔细一点就好了。

以上。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,M=205,K=1e5+5;
int n,m=200,k;
int h[M][M],res=0,ans=0;
int cntx[M][M],cnty[M][M];
int ansx[M][M],ansy[M][M];
int hhhx[2][M],hhhy[2][M];
int main()
{
	cin>>n>>k;
	for(int i=1,x1,y1,x2,y2;i<=n;++i)
	{
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		++x1,++y1,++x2,++y2;
		h[x1][y1]++,h[x2][y2]++;
		h[x1][y2]--,h[x2][y1]--;
	}
	for(int i=1;i<=m;++i)
	{
		for(int j=1;j<=m;++j)
		h[i][j]+=h[i-1][j]+h[i][j-1]-h[i-1][j-1],res+=(h[i][j]==k);
	}
	// for(int i=1;i<=8;++i)
	// {
	// 	for(int j=1;j<=8;++j)
	// 	printf("%d ",h[i][j]);
	// 	printf("\n");
	// }
	// printf("\n");
	for(int i=1;i<=m;++i)
	{
		for(int j=1;j<=m;++j)
		{
			cntx[i][j]=cntx[i-1][j]+(h[i][j]==k-1)-(h[i][j]==k);
			cnty[i][j]=cnty[i][j-1]+(h[i][j]==k-1)-(h[i][j]==k);
		}
	}
	// for(int i=1;i<=8;++i)
	// {
	// 	for(int j=1;j<=8;++j)
	// 	printf("%d ",cntx[i][j]);
	// 	printf("\n");
	// }
	// printf("\n");
	// for(int i=1;i<=8;++i)
	// {
	// 	for(int j=1;j<=8;++j)
	// 	printf("%d ",cnty[i][j]);
	// 	printf("\n");
	// }
	// printf("\n");
	int tmp;
	for(int i=1;i<=m;++i)
	{
		for(int j=1;j<=i;++j)
		{
			tmp=0;
			for(int c=1;c<=m;++c)
			{
				tmp=max(tmp+cntx[i][c]-cntx[j-1][c],0);
				ansx[i][j]=max(ansx[i][j],tmp);
			}
		}
	}
	for(int i=1;i<=m;++i)
	{
		for(int j=1;j<=i;++j)
		{
			tmp=0;
			for(int c=1;c<=m;++c)
			{
				tmp=max(tmp+cnty[c][i]-cnty[c][j-1],0);
				ansy[i][j]=max(ansy[i][j],tmp);
			}
		}
	}
	// for(int i=1;i<=8;++i)
	// {
	// 	for(int j=1;j<=8;++j)
	// 	printf("%d ",ansx[i][j]);
	// 	printf("\n");
	// }
	// printf("\n");
	// for(int i=1;i<=8;++i)
	// {
	// 	for(int j=1;j<=8;++j)
	// 	printf("%d ",ansy[i][j]);
	// 	printf("\n");
	// }
	// printf("\n");
	for(int i=1;i<=m;++i)
	{
		hhhx[0][i]=hhhx[0][i-1];
		for(int j=1;j<=i;++j)
		hhhx[0][i]=max(hhhx[0][i],ansx[i][j]);
	}
	for(int i=m;i>=1;--i)
	{
		hhhx[1][i]=hhhx[1][i+1];
		for(int j=m;j>=i;--j)
		hhhx[1][i]=max(hhhx[1][i],ansx[j][i]);
	}
	for(int i=1;i<=m;++i)
	{
		hhhy[0][i]=hhhy[0][i-1];
		for(int j=1;j<=i;++j)
		hhhy[0][i]=max(hhhy[0][i],ansy[i][j]);
	}
	for(int i=m;i>=1;--i)
	{
		hhhy[1][i]=hhhy[1][i+1];
		for(int j=m;j>=i;--j)
		hhhy[1][i]=max(hhhy[1][i],ansy[j][i]);
	}
	ans=res;
	for(int i=2;i<=m;++i) ans=max(ans,res+hhhx[0][i-1]+hhhx[1][i]);
	for(int i=2;i<=m;++i) ans=max(ans,res+hhhy[0][i-1]+hhhy[1][i]);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：DengDuck (赞：5)

调差分调了半天...

观察数据，发现值域很小，矩形很多，需要转换成一个矩阵上的问题。

首先我们将几何上的矩形转换成矩阵的一个子矩阵，咋弄呢？你把平面直角坐标系每一个 $1\times 1$ 的小方块都按行按列编号成 $(x,y)$ 形式即可。

然后显然可以差分统计每个方块刷了多少次油漆，进一步得到有多少涂了 $k$ 次的方块，记录下来。

考虑我们添加的矩形对答案的贡献，对于 $k-1$ 有 $+1$ 的贡献，对于 $k$ 有 $-1$ 的贡献，我们问题变成找到两个无交的矩阵，使其和最大。

这是一个经典的问题，考虑枚举一行/一列将我们的数组切开，然后在彼此的区间各找一个最大区间。

我们处理 $f_{i,j}$ 表示以 $(i,j)$ 为左上角的最大矩阵，$g_{i,j}$ 表示以 $(i,j)$ 为右下角的最大矩阵。

$\mathcal O(n^3)$ 求法是很多的，我的做法是枚举一短横区间，把横区间内每一行的值的和都求出来，然后就变成了一个一维求最大区间的问题——对于我而言，我选择的左端点必然是前缀和最小的一项。

这么说有点抽象，可以参考代码理解。

利用这两项值可以求出 $F_{i,j}$ 表示 $(i,j)$ 左上角内的最大矩阵，$G_{i,j}$ 表示 $(i,j)$ 右下角内的最大矩阵。

这样切开之后就可以求出最大矩阵了。

时间复杂度为 $O(n^3)$，注意我说的 $n$ 是值域 $200$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=200;
LL n,k,x,y,xx,yy,a[N+5][N+5],sum[N+5][N+5],ans2,ans,f[N+5][N+5],g[N+5][N+5],s[N+5];
LL cal(LL x,LL y,LL xx,LL yy)
{
	return sum[xx][yy]-sum[x-1][yy]-sum[xx][y-1]+sum[x-1][y-1];
}
int main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld%lld",&x,&y,&xx,&yy);
		a[x+1][y+1]++,a[xx+1][yy+1]++;
		a[xx+1][y+1]--,a[x+1][yy+1]--;
	}
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
		{
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
		}
	}
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
		{
			if(sum[i][j]==k-1)a[i][j]=1;
			else if(sum[i][j]==k)ans2++,a[i][j]=-1;
			else a[i][j]=0;
		}
	}
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
		{
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
		}
	}
	memset(f,-127,sizeof(f));
	memset(g,-127,sizeof(g));
	for(int i=1;i<=N;i++)
	{
		for(int j=i;j<=N;j++)
		{
			LL mn=0;
			for(int x=1;x<=N;x++)
			{
				s[x]=s[x-1]+cal(x,i,x,j);
				f[x][j]=max(f[x][j],s[x]-mn);
				mn=min(s[x],mn);
			}
			mn=0;
			for(int x=N;x>=1;x--)
			{
				s[x]=s[x+1]+cal(x,i,x,j);
				g[x][i]=max(g[x][i],s[x]-mn);
				mn=min(s[x],mn);
			}
		}
	}
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
			f[i][j]=max({f[i-1][j],f[i][j-1],f[i][j]});
	}
	for(int i=N;i>=1;i--)
	{
		for(int j=N;j>=1;j--)
			g[i][j]=max({g[i+1][j],g[i][j+1],g[i][j]});
	}
	for(int i=2;i<=N;i++)
	{
		ans=max({ans,f[N][i-1]+g[1][i]});
	}
	for(int i=2;i<=N;i++)
	{
		ans=max({ans,f[i-1][N]+g[i][1]});
	}	
	printf("%lld",ans+ans2);
} 
```

---

## 作者：XGTD (赞：2)

# 题解：P6100 [USACO19FEB] Painting the Barn G

## Preface
好题呀，一九年金组就有这么难了？

## Problem Statement
[P6100](https://www.luogu.com.cn/problem/P6100)。

## Solution
首先有一条非常重要的限制，即两个矩阵**不能相交**，这就说明对于每一格，我们最多在原矩阵的基础上加**一**。

有了上面这条限制我们就能发现其实我们关心的只有原本就有 $K$ 层的，和原本有 $K - 1$ 层的格子，前者被覆盖到会使得答案减一，而后者加一。

这时我们就能想到下面的一种思路。由于矩阵不能相交，我们枚举第一个矩阵的右下角，记录所有左上角坐标不会导致相交的第二个矩阵中最优的一个的贡献，加上对于此时的右下角，最优的第一个矩阵的贡献，就是这个右下角的答案，打擂台，求出最终答案。

此时我们就需要一个算法，求出以任意点为左上角/右下角的**最大子矩阵。**

可以用 dp 实现，过程很像最大字段和，下面我们用找对于一个固定**右下角**的最大子矩阵为例。

为了达到 $n^3$ 而不是 $n^4$ 复杂度，我们只枚举想要的右下角，以及最优矩阵的左上角的 x 坐标，将满足要求的最优矩阵存为 $f_{i,j,k}$ （$i, j$ 表示右下角，$k$ 表示左上角的 x 坐标）

转移过程和最大字段和很像，每次决策是否将这最后以行接在上一行后面，还是这单独一行另起一个矩阵。
$$
\begin{aligned}

f_{i, j, k} = \max(f_{i, j, k - 1}, 0) + val_{i, j} - val_{k - 1, j}

\end{aligned}
$$

$val_{i, j} - val_{k - 1, j}$ 表示的是最后一行的值，$val$是一个预处理好的前缀和。

有了最大子矩阵接下来的过程就比较简单了，细节代码里有很多注释。

## Code

我代码里写的稍微有些不同，最后一步枚举的不是第一个的右下，而是第二个的左上，但是过程基本一样。

```cpp
/*
最大子矩阵 is acutally a little more complicated then I thought,
we need 2 dps for max sub matrix with a fixed bottom right,
and 2 more for such with fixed top left

let's use bottom right as example

first for max subarray(substring), each time the decision we make
with dp is whether to connect with last i - 1, or to start new.

similar here, this time however, 2 dimentional

the key to achieving n^3 not n^4 complexity is that we only
enumerate the coordinate of bottom right(duh, we need that), and
the x(or y if you want) coordinate of the top left of the max
submatrix. what about y? well now we get to use dp and just
decide whether we connect this last row to the matrix above or
just to start a new one with height 1(just this row).

be careful though we need 2 dp arrays, one 3d and one 2d, cuz
2d store answer, but then actually transfering we need to
restrict which j we transfer from, which need to be specified in
the state.(see details in code)also I don't actually have to make
it 3d cuz i can just put j as outer most layer loop. but you
know, we've got space!

brm[i][j] = the max br[k][l] for all k <= i and l <= j
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, k, dif[205][205], pre[205][205];
int ans, orig, op1[205][205], op2[205][205], cnt, chec;
int brf[205][205][205], tlf[205][205][205];
int br[205][205], tl[205][205], brm[205][205];
//这里的一大堆数组，brf就是题解里的f数组，br是对于一对 i, j 所有
//k 找到最优的后存起来了，tl同理，只不过是左上角
//brm 则是在最后需要找到在一个点一下的所有 br 里最大的一个
//相当于一个二维后缀最大值 
int mx, my;
signed main(){
	cin>>n>>k;
	for(int i = 1; i <= n; i++){
		int x, y, x2, y2;
		cin>>x>>y>>x2>>y2;
		x++, y++, x2++, y2++;
		dif[x][y]++;
		dif[x][y2]--;
		dif[x2][y]--;
		dif[x2][y2]++;
		mx = max(mx, x2);
		my = max(my, y2);
		//start from 1 instead of 0, so we don't have RE
	}
	mx = min(mx, 200LL);
	my = min(my, 200LL);
	//MAJOR MAJOR BUG!!!!!!!!
	//cuz our br will consider the border cell painted, but cells
	//at 200(or 201 now that we've added 1) doesn't exist! it's
	//just a line, there's no cells behind the line
	//this stuck me for 50 minutes, and even after discovering
	//this bug I wrote max() instead of min, and stuck me another
	//10 minutes.
	for(int i = 1; i <= mx; i++){
		for(int j = 1; j <= my; j++){
			pre[i][j] = dif[i][j];
			pre[i][j] += pre[i - 1][j]+pre[i][j-1]-pre[i-1][j-1];
			if(pre[i][j] == k)orig++;
		}
	}
	//found prefix sum(silver level end here)
	//ans right now is the answer for adding no rectangles
	//one dimentional prefix sum TOP TO BOTTOM!!!!
	for(int i = 1; i <= mx; i++){
		for(int j = 1; j <= my; j++){
			op1[i][j] = op1[i - 1][j] + (pre[i][j] == (k - 1));
			op1[i][j] -= (pre[i][j] == (k));
		}
	}
	for(int i = 1; i <= mx; i++){
		for(int j = 1; j <= i; j++){
			for(int k = 1; k <= my; k++){
				//bottom right corner is i, k
				int lyc = max(brf[i][j][k - 1], 0LL);
				//last y coordinate(when y was k - 1)
		/*
		if(lyc+op1[i][k]-op1[j-1][k] == 7 && i == mx && k == 3){
			cout<<mx<<" "<<j<<endl;
		}
				//bro above was actually a bug cuz I forgot to
				//comment it off, like out of all these years
				//of programming, this?!?!?!
				*/
				brf[i][j][k] = lyc + op1[i][k] - op1[j - 1][k];
				//we still enumerate the x coordinate of the
				//top left of the best rectange with bottom right
				//i k, but we don't need to enumerate the y
				//coordinate cuz we use dp
				br[i][k] = max(br[i][k], brf[i][j][k]);
				//we had to add a dimension for brf cuz other
				//wise we might choose an L shape around the
				//negatives, so we have to limit the js we can
				//transfer brf from
			}
		}
	}
	//now, we've (finally) found the biggest rectangle with
	//bottom right at i, j, stored in br[i][j]
	//this time BOTTOM TO TOP!!!!
	for(int i = mx; i >= 1; i--){
		for(int j = 1; j <= my; j++){
			op2[i][j] = op2[i + 1][j];
			op2[i][j] += (pre[i][j] == (k - 1));
			op2[i][j] -= (pre[i][j] == (k));
		}
	}
	for(int i = mx; i >= 1; i--){
		for(int j = mx; j >= i; j--){
			for(int k = my; k >= 1; k--){
				int lyc = max(tlf[i][j][k + 1], 0LL);
				//this is actually basically the decision making
				//process of dp
				tlf[i][j][k] = lyc + op2[i][k] - op2[j + 1][k];
				tl[i][k] = max(tl[i][k], tlf[i][j][k]);
			}
		}
	}
	for(int i = 1; i <= mx; i++){
		for(int j = 1; j <= my; j++){
			brm[i][j] = br[i][j];			
			brm[i][j] = max(brm[i][j - 1], brm[i][j]);
			brm[i][j] = max(brm[i - 1][j], brm[i][j]);
		}
	}
	ans = orig;
	for(int i = 1; i <= mx; i++){
		for(int j = 1; j <= my; j++){
			//i, j as the top left of the second rectangle
			ans = max(ans, orig + tl[i][j]);
			ans = max(ans, orig + br[i][j]);
			int mabr = max(brm[i - 1][my], brm[mx][j - 1]);
			//don't forget to do i - 1 and j - 1 not i and j, cuz
			//both br and tl claim the block at their border
			//if we do i,j we have a row overlapping
			ans = max(ans, orig + mabr + tl[i][j]);
		}
	}
	cout<<ans<<endl;
	return 0;
}

```
## After thought

好题呀，建议升紫。

求赞。

---

## 作者：kradcigam (赞：2)



这道题首先考虑把求面积转化成求满足条件的格点数量，接着考虑怎么做。因为这两个矩形没有交，所以一个点最多只会被覆盖一次。于是最终答案中 $K$ 层涂料的只可能是初始下 $K-1$ 层涂料（被涂一层）和 $K$ 层涂料（没有被涂）。

于是就考虑转化，涂了 $K-1$ 层的格子标记为 $1$，即涂了这个格子能是答案加 $1$；涂了 $K$ 层涂料的格子标记为 $-1$，因为涂了这个格子会使答案减少 $1$，最终的答案就是双子矩阵最大和，这可以看作是[双子序列最大和](https://www.luogu.com.cn/blog/zhaohaikun/solution-p2642)的延续和拓展。

考虑两个子矩阵的相对位置：

![Untitled.png](https://i.loli.net/2021/08/07/UqWpcIS7boyNHjT.png)

第三种可以看作是前两种情况的公共部分。

对于前两种情况，我们可以枚举分割线，求出答案。对于分割线的两边，我们可以 $4$ 个方向都做 $dp$，枚举两个边界去求。最后记得前缀 $\max$ 一下，因为不一定一定要贴着分割线，判断没有即对 $0$ 取 $\max$ 即可。

具体看代码（自认为实现非常清晰）：

```cpp
#include<bits/stdc++.h>
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define LL long long
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define DF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read(){char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
const int N=210;
int f[N][N],lf[N][N][N],rf[N][N][N],uf[N][N][N],df[N][N][N],s1[N][N],s2[N][N],lmaxn[N],rmaxn[N],umaxn[N],dmaxn[N],ans,s;
//l表示left（左），r表示right（右），u表示up（上），d表示down（下）
//f[i][j]表示这个格子的值（使用前缀和快速处理）
//l/r/u/df[i][j][k]表示上界为i，下界为j，处理到k
//l/r/u/dmaxn[i]表示前缀/后缀求max到i
//s1[i][j]表示f[1][j]~f[i][j]的和
//s2[i][j]表示f[i][1]~f[i][j]的和
signed main(){
	int n=read(),k=read();
	F(i,1,n){
		int kx=read()+1,ky=read()+1,tx=read(),ty=read();//转换为割点数：kx,ky加上1，让每个点表示它左下角的格子
		f[kx][ky]++;f[kx][ty+1]--;f[tx+1][ky]--;f[tx+1][ty+1]++;//差分
	}
	F(i,1,200)
		F(j,1,200){
			f[i][j]+=f[i-1][j]+f[i][j-1]-f[i-1][j-1];//前缀和即为值
			int t=0;//如果不是k或k-1就为0
			if(f[i][j]==k)t=-1,s++;//处理矩阵元素值
			if(f[i][j]+1==k)t=1;//处理矩阵元素值
			s1[i][j]=s1[i-1][j]+t;//求前缀和
			s2[i][j]=s2[i][j-1]+t;//求前缀和
		}
	F(i,1,200)
		F(j,i,200){
			F(k,1,200){
				lf[i][j][k]=max(lf[i][j][k-1],0)+s1[j][k]-s1[i-1][k];//dp（跟不跟左边相连）
				lmaxn[k]=max(lmaxn[k],lf[i][j][k]);//求这一列为右边界，左边的最大值
			}
			DF(k,200,1){
				rf[i][j][k]=max(rf[i][j][k+1],0)+s1[j][k]-s1[i-1][k];//dp（跟不跟右边相连）
				rmaxn[k]=max(rmaxn[k],rf[i][j][k]);//求这一列为左边界，右边的最大值
			}
			F(k,1,200){
				uf[i][j][k]=max(uf[i][j][k-1],0)+s2[k][j]-s2[k][i-1];//dp（跟不跟上边相连）
				umaxn[k]=max(umaxn[k],uf[i][j][k]);//求这一行为下边界，上面的最大值
			}
			DF(k,200,1){
				df[i][j][k]=max(df[i][j][k+1],0)+s2[k][j]-s2[k][i-1];//dp（跟不跟下边相连）
				dmaxn[k]=max(dmaxn[k],df[i][j][k]);//求这一行为上边界，下面的最大值
			}
		}
	F(i,1,200)lmaxn[i]=max(lmaxn[i-1],lmaxn[i]);//前缀max
	DF(i,200,1)rmaxn[i]=max(rmaxn[i+1],rmaxn[i]);//前缀max
	F(i,1,200)umaxn[i]=max(umaxn[i-1],umaxn[i]);//前缀max
	DF(i,200,1)dmaxn[i]=max(dmaxn[i+1],dmaxn[i]);//前缀max
	F(i,1,200)ans=max(ans,max(lmaxn[i]+rmaxn[i+1],umaxn[i]+dmaxn[i+1]));//枚举分界线求值
	cout<<s+ans;//主要加上初始值
	return 0;
}
```





---

## 作者：Unnamed114514 (赞：0)

首先，用二维差分求出每个位置的油漆的层数。

我们来考虑那些位置会造成贡献：

- 对于此时恰好 $K$ 层的位置：再涂会使答案少 $1$，所以贡献是 $-1$。

- 对于此时恰好 $K-1$ 层的位置，再涂会使答案多 $1$，那么贡献就是 $1$。

那么我们跑两个最大子矩阵即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans,res,s[1005][1005],a[1005][1005],h[1005][1005],w[1005][1005];
int main(){
	cin>>n>>k;
	for(int i=1,x1,x2,y1,y2;i<=n;++i){
		cin>>x1>>y1>>x2>>y2;
		++s[x1+1][y1+1],--s[x2+1][y1+1],--s[x1+1][y2+1],++s[x2+1][y2+1];
	}
	for(int i=1;i<=1000;++i)
		for(int j=1;j<=1000;++j){
			s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
			if(s[i][j]==k)
				++ans,a[i][j]=-1;
			if(s[i][j]==k-1)
				a[i][j]=1;
			a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
		}
	for(int len=1;len<=200;++len)
		for(int l=1,r=len;r<=200;++l,++r){
			h[l][r]=max(h[l][r-1],h[l+1][r]);
			int s=0;
			for(int i=1;i<=200;++i){
				s=max(s,0)+a[i][r]-a[i][l-1]-a[i-1][r]+a[i-1][l-1];
				h[l][r]=max(h[l][r],s);
			}
		}
	for(int len=1;len<=200;++len)
		for(int l=1,r=len;r<=200;++l,++r){
			w[l][r]=max(w[l][r-1],w[l+1][r]);
			int s=0;
			for(int i=1;i<=200;++i){
				s=max(s,0)+a[r][i]-a[l-1][i]-a[r][i-1]+a[l-1][i-1];
				w[l][r]=max(w[l][r],s);
			}
		}
	for(int i=1;i<=200;++i)
		res=max({res,ans+h[1][i]+h[i+1][200],ans+w[1][i]+w[i+1][200]});
	cout<<res<<endl;
	return 0;
}
```

---

