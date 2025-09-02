# Gargari and Bishops

## 题目描述

Gargari is jealous that his friend Caisa won the game from the previous problem. He wants to prove that he is a genius.

He has a $ n×n $ chessboard. Each cell of the chessboard has a number written on it. Gargari wants to place two bishops on the chessboard in such a way that there is no cell that is attacked by both of them. Consider a cell with number $ x $ written on it, if this cell is attacked by one of the bishops Gargari will get $ x $ dollars for it. Tell Gargari, how to place bishops on the chessboard to get maximum amount of money.

We assume a cell is attacked by a bishop, if the cell is located on the same diagonal with the bishop (the cell, where the bishop is, also considered attacked by it).

## 样例 #1

### 输入

```
4
1 1 1 1
2 1 1 0
1 1 1 0
1 0 0 1
```

### 输出

```
12
2 2 3 2
```

# 题解

## 作者：Yizhixiaoyun (赞：12)

[博客园食用](https://www.cnblogs.com/yizhixiaoyun/p/16799109.html)

[题目传送门](https://www.luogu.com.cn/problem/CF463C)

## 题目分析

贪心练手好题。

首先，国际象棋中象的走法是斜着走，也就是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/jkl36vvd.png)

通过上面的图我们不难看出，如果一个象在黑格，另外一个在白格，那么它们之间一定不会互相攻击到。

我们通过染色来确定格子的黑白颜色，一种判定方式是横纵坐标相加，偶数为黑，奇数为白。

然后我们贪心的找出最大收益，即分别找出放在黑格子与白格子的收益，然后两边各取最大值相加即可。

## 贴上代码

```cpp
#include<bits/stdc++.h>
#define lf i+j
#define rt i-j+2500
#define int long long
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0' || c>'9'){if(c=='-') f=-1;c=getchar();}while(c>='0' && c<='9') {x=x*10+c-48;c=getchar();}return x*f;}
const int maxn=5002;
int n;
int tot1,tot2;
int x,y,xx,yy;
int a[maxn][maxn];
int p[maxn],q[maxn];
inline void init(){
	n=read();
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=n;++j) a[i][j]=read();
	}
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=n;++j){
			p[lf]+=a[i][j];q[rt]+=a[i][j];
		}
	}
}
inline void print(){
	cout<<tot1+tot2<<endl;
	cout<<x<<" "<<y<<" "<<xx<<" "<<yy<<" ";
}
signed main(){
	init();
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=n;++j){
			if((i+j)%2==1){
				if(tot1<=p[lf]+q[rt]-a[i][j]){
					tot1=p[lf]+q[rt]-a[i][j];
					x=i;y=j;
				}
			}
			else if(tot2<=p[lf]+q[rt]-a[i][j]){
				tot2=p[lf]+q[rt]-a[i][j];
				xx=i;yy=j;
			}
		}
	}
	print();
}
```

---

## 作者：Nephren_Sakura (赞：6)

题目传送门：[link](https://www.luogu.com.cn/problem/CF463C)。

前言：个人感觉恶评了，应该没到紫，最多蓝。

首先，我们可以发现，因为棋盘的长与宽相等，所以将棋盘黑白染色之后，两个象必定一个在黑色格子上，一个在白色格子上。

然后我们发现这两个象互不干扰，所以考虑分别求出黑色格子与白色格子的最大值，再统计答案。

但是我们发现对于任意一个点，直接求值是 $O(n)$ 的，而共有 $O(n^2)$ 个点，这样时间复杂度是 $O(n^3)$ 的，无法通过此题。

于是我们考虑如何快速求出每一个点的值。

注意到象的攻击方式是其所在点的两条斜线，而我们知道，对于一条左斜线，其 $x+y$ 是相等的。而对于每条右斜线，其 $x-y$ 是相等的。

如果不知道上面那个结论怎么来的可以去看一下八皇后问题。

这样的话我们就直接处理出每一条左斜线与右斜线上所有数的和。

具体地，我们枚举每一个点 $(x,y,w)$，其中 $(x,y)$ 表示点的坐标，$w$ 表示点的权值。

那么我们就将 $s1_{x+y}$ 与 $s2_{x-y}$ 都加上一个 $w$ 就好了。

但是 $x-y$ 可能为负数，此时我们也用类似于八皇后的方法，将所有 $x-y$ 偏移成 $x-y+1+n$。

输出方案在求最大值的时候顺便记一下。

然后注意几点：

一是对于每一个点，在计算自己时会计算两次，所以最后在减去一个 $a_{x,y}$ 就可以了。

二是即使有时候象没有用也要随便放在黑或白的某一个地方，这个初始化一下就好了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[2005][2005],s[4005],S[4005],maxi[2],x[2]={1,1},y[2]={1,2};//2~2*n
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			cin>>a[i][j];
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			s[i+j]+=a[i][j];
			S[i-j+1+n]+=a[i][j];
		}
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(maxi[(i+j)%2]<s[i+j]+S[i-j+1+n]-a[i][j])
				maxi[(i+j)%2]=s[i+j]+S[i-j+1+n]-a[i][j],x[(i+j)%2]=i,y[(i+j)%2]=j;
	cout<<maxi[0]+maxi[1]<<'\n'<<x[0]<<' '<<y[0]<<' '<<x[1]<<' '<<y[1];
	return 0;
}

```

之所以没有 AC 记录的原因，是因为当时 CF 交不上去。

[CF AC 记录](https://codeforces.com/contest/463/submission/212942683)。

---

## 作者：_xbn (赞：4)

下过国际象棋的应该都知道，放在不同颜色的格子里的象一定不会互相攻击到。

那我们可以对棋盘标记黑白格子(横纵坐标之和为偶数的为黑格子，计数为白格子)。

我们分别把两个Bishops 放在一个黑格子上，一个白格子上，既然要取最大值，那我们就选出白格子的最大值，黑格子的最大值，相加就是答案。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2002;
int n, m, l, r, p, t, k, ans, sum, tot, cnt, a[N][N], b[N], c[N], d[N][N], L[N][N], R[N][N], up[N][N], x[2], y[2];
inline int rd()
{
	int x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
signed main()
{
	n = rd();
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) a[i][j] = rd();
	for (int i = 1; i <= n; i++) 
	{
		for (int j = 1; j <= n; j++)
		{
			L[i][j] = L[i - 1][j - 1] + a[i][j];
			R[i][j] = R[i - 1][j + 1] + a[i][j];
		}
	}
	for (int i = n; i>= 1; i--)
	{
		for (int j = 1; j <= n; j++)
		{
			up[i][j] = up[i + 1][j - 1] + a[i][j];
			d[i][j] = d[i + 1][j + 1] + a[i][j];
		}
	}
	int pos[2] = {-1, -1};
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			int now = (i + j) & 1;
			sum = L[i][j] + R[i][j] + up[i][j] + d[i][j] - 3 * a[i][j];
			if(sum > pos[now])
			{
				pos[now] = sum;
				x[now] = i;
				y[now] = j;
			}
		}
	}
	cout << pos[0] + pos[1] << endl;
	cout << x[0] << " " << y[0] << " " << x[1] << " " << y[1] << endl;
	return 0;
}
```


---

## 作者：AKPC (赞：3)

### 思路
玩过国际象棋吗？

![](https://cdn.luogu.com.cn/upload/image_hosting/5zi9e10e.png)

象可以斜着走任意格，但是显然它是不能走一些格子的。如图，假设一个象在白色格子上，那么它就无法攻击灰色格子，即只可以走斜线。

而显然如果两个象在同一个颜色格子上，肯定会有同时被两象攻击的格子。所以必须要两个象在不同颜色格子上，假设两象坐标 $(x_1,y_1)$，$(x_2,y_2)$，则需要满足 $(x_1+y_1)\bmod 2\neq(x_2+y_2)\bmod 2$。

然后直接处理每条斜线上的分值，再分别暴力枚举白色格子与灰色格子象的位置，每种格子维护一个得分最大值即可。处理斜线需要分别处理向下向左的斜线得分之和 $f1_{i+j}$ 与向下向右的斜线得分之和 $f2_{i-j+n+1}$，如果要求 $(i,j)$ 的得分，即为上面两个值相加减去这个格子上的分数，因为这个格子上的分数被算了两遍。

对了，这题有点卡常数，建议加快读。
### 代码
```cpp
// LUOGU_RID: 118715295
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int x=0;bool f=1;register char c=getchar();
    while (c<48||c>57){if(c=='-') f=0;c=getchar();}
    while (c>=48&&c<=57){x=x*10+(c^48);c=getchar();}
    return f?x:-x;
}
int n=read(),a[2001][2001],f[2001][3],maxn,maxm,nidx=1,nidy=1,midx=1,midy=2;
inline void Max(int x,int i,int j,int op){
	if (op==1&&x<=maxn) return;
	if (op==2&&x<=maxm) return;
	if (op==1) maxn=x,nidx=i,nidy=j;
	if (op==2) maxm=x,midx=i,midy=j;
}
signed main(){
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) a[i][j]=read();
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) f[i+j][1]+=a[i][j],f[i-j+n+1][2]+=a[i][j];
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) Max(f[i+j][1]+f[i-j+n+1][2]-a[i][j],i,j,(i+j)%2+1);
	cout<<maxn+maxm<<'\n'<<nidx<<' '<<nidy<<' '<<midx<<' '<<midy;
	return 0;
}
```


---

## 作者：I_am_big_SB (赞：2)

## 前言（一些废话）
本蒟蒻的第一篇题解，我看其他题解讲的不是特别清楚（其实就是我太垃了看不懂），于是决定发一篇题解，供像我一样的蒟蒻食用。

[一个推销](https://www.luogu.com.cn/user/746011)
## 正文
[题目传送门](https://www.luogu.com.cn/problem/CF463C)

### 题目分析
首先，我们知道，国际象棋中两个象不能攻击到同一个格子的充要条件是两个象行列数相加的奇偶性不同，证明比较简单，我就不详细证明了。根据题目的意思，在两个象行列数相加的奇偶性确定后，它们就没有其他的约束条件，也就是不再影响了，所以很适合贪心算法。

接下来，我们要考虑如何在平方复杂度内计算每一个格子所在的两个斜行的分数总和。根据象的行走规则，象的行数加上一个数时，列数就要相应地加上或减去这个数。那么我们就可以推出，如果两个格子在同一斜行，它们的行列数相加或相减后的值是一样的。所以，我们可以开两个数组，一个记录行列数相加的值相等的格子的分数总和，另一个记录行列数相减的值相等的格子的分数总和。

最后，我们遍历数组，找出最大值即可。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, x, y, x2, y2, ans1, ans2, a[2005][2005], b[4005], c[4005];//b,c 数组要开两倍，不然会当场 RE
int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) scanf("%lld", &a[i][j]);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            b[i + j - 1] += a[i][j];
            c[n + j - i] += a[i][j];//加 n 防越界
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if ((i + j) % 2) {
                if (b[i + j - 1] + c[n + j - i] - a[i][j] >= ans1) {
                    ans1 = b[i + j - 1] + c[n + j - i] - a[i][j];
                    x = i;
                    y = j;
                }
            } else {
                if (b[i + j - 1] + c[n + j - i] - a[i][j] >= ans2) {
                    ans2 = b[i + j - 1] + c[n + j - i] - a[i][j];
                    x2 = i;
                    y2 = j;
                }
            }
        }
    }
    printf("%lld\n%lld %lld %lld %lld", ans1 + ans2, x2, y2, x, y);
    return 0;
}
```
### 注意事项
1. 一定要开 long long，我没开当场暴毙。
2. 在更新答案时判断条件要用大于等于，不然会被出题人用全 0 数据 hack 掉。（别问我怎么知道的）
3. 在计算得分时，要把该格子的分减掉，因为它加了两次。
4. ~~珍爱账号，远离棕名~~。

## 后记（还是废话）
第一次写题解，没啥经验，有什么问题大家多多指出，本蒟蒻会努力改正的。

---

## 作者：Dehydration (赞：1)

### 前言：

水，主要是难理解，翻译太鬼畜了...

[problem](https://www.luogu.com.cn/problem/CF463C)。

### 翻译：

在一个棋盘中放 $2$ 个斜着攻击的棋子，要求两个棋子不能同时攻击到同一个格子，求所有攻击到的格子累加之和。

### 思路：

考虑给棋盘黑白染色，两个棋子肯定一个在黑，一个在白。

先将所有对角线处理好，在 $n^2$ 枚举，如果为黑考虑 $sum_1$，反之考虑 $sum_2$。

关于处理对角线，显而易见（可以自己推一推）正对角线，就是从左上到右下的每个点的坐标 $x+y$ 均相等，负对角线的每个点坐标 $x-y$ 均相等，则可以进行计算。

### 代码：

**注意：$x-y$ 有可能是负数，需要加 $M$。**

```cpp
#include <bits/stdc++.h>
#define int long long
#define M 2005
using namespace std;
int a[M][M],n,Z[M+M],F[M+M],sum1=-114514,sum2=-114514,x114,x514,y114,y514;
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>a[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)Z[i+j]+=a[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)F[i-j+M]+=a[i][j];//处理对角线
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		if((i+j)%2)
		{
			bool f=sum1<Z[i+j]+F[i-j+M]-a[i][j];
			sum1=f*(Z[i+j]+F[i-j+M]-a[i][j])+sum1*(!f);
			x114=x114*(!f)+i*f,x514=j*f+x514*(!f);//卡常，用bool代替if
		}else
		{
			bool f=sum2<Z[i+j]+F[i-j+M]-a[i][j];
			sum2=f*(Z[i+j]+F[i-j+M]-a[i][j])+sum2*(!f);
			y114=y114*(!f)+i*f,y514=j*f+y514*(!f);
		}
	}
	cout<<sum1+sum2<<'\n';
	cout<<x114<<' '<<x514<<' '<<y114<<' '<<y514<<'\n';//很臭的数字
    return 0;
}
```

---

## 作者：gdf_yhm (赞：1)

[CF463C](https://www.luogu.com.cn/problem/CF463C)

贪心。

可以发现，“要求不能有位置同时被两个象攻击到”，则两象一个是白格象，另一个是黑格象。

所以对棋盘黑白染色，分别处理黑白，是两个独立的问题。当格子横纵坐标和为奇时，是白格。

数组 $x[]$ 记录从右上到左下的斜线，$x[i]$ 表示所有横纵坐标和为i的点的价值和，当象放置位置横纵坐标和为i时，则会选中 $x[i]$ 上所有的点，价值 $+x[i]$ 。同理，$y[i]$ 记录从左上到右下的斜线。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2010;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
int inline read(){
	int x=0;
	char ch=getchar();
	while(ch<'0' || ch>'9')	ch=getchar();
	while(ch>='0' && ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x;
}

int n,a[maxn][maxn],x[maxn<<1],y[maxn<<1];
int mx1=0,mxtx1=1,mxty1=1,mx2=0,mxtx2=1,mxty2=1;

signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=read();
			x[i+j]+=a[i][j];
			y[i-j+n]+=a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int s=x[i+j]+y[i-j+n]-a[i][j];
			if((i+j)&1){
				if(s>=mx1){
					mx1=s;
					mxtx1=i;	mxty1=j;
				}
			}
			else{
				if(s>=mx2){
					mx2=s;
					mxtx2=i;	mxty2=j;
				}
			}
		}
	}
	printf("%lld\n%lld %lld %lld %lld",mx1+mx2,mxtx2,mxty2,mxtx1,mxty1);
}
```


---

## 作者：RainFestival (赞：1)

首先，我们先将棋盘黑白染色。

我们知道如果两个 bishop 都放在同种颜色格子里时控制点一定会有交点。

所以我们只能将两个 bishop 放在不同颜色格子里，然后就可以分别独立地处理。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#define base 2500
int n,x1,y1,x2,y2;
long long a[5005][5005],f[5005],g[5005],s1,s2;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	    for (int j=1;j<=n;j++)
	        scanf("%lld",&a[i][j]);
	for (int i=1;i<=n;i++)
	    for (int j=1;j<=n;j++)
	        f[i+j]=f[i+j]+a[i][j],g[i-j+base]=g[i-j+base]+a[i][j];
	for (int i=1;i<=n;i++)
	    for (int j=1;j<=n;j++)
		{
			long long s=f[i+j]+g[i-j+base]-a[i][j];
			if ((i+j)&1) {if (s>=s1) s1=s,x1=i,y1=j;}
			else if (s>=s2) s2=s,x2=i,y2=j;
		}
	printf("%lld\n",s1+s2);
	printf("%d %d %d %d\n",x1,y1,x2,y2);
	return 0;
}
```

然后就 AC 了！

---

## 作者：_Flame_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF463C)

## 思路

国际象棋中，象是斜着走的，所以很容易得出，把棋盘黑白染色后，若两个象所在的格子颜色一样，它们能攻击到的位置会重合，若两个象所在的格子颜色不一样，它们能攻击到的位置不会有重合。

所以我们可以处理出每个黑格子的可以得到的分，在里面找到得分最多的那一个格子。对于每个白格子做同样的操作，找得分最多的那个格子。记录这两个格子的位置，最后输出即可。

## Code

```cpp

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2050;

int n;
int a[maxn][maxn];
int l[maxn][maxn],r[maxn][maxn],u[maxn][maxn],d[maxn][maxn];
int wh[maxn][maxn],bl[maxn][maxn];
int cnt1=INT_MIN,cnt2=INT_MIN;
int bx,by,wx,wy;

void init(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
		}
	}
	
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++){
			l[i][j]=l[i-1][j-1]+a[i][j];
			r[i][j]=r[i-1][j+1]+a[i][j];
		}
	}
	
	for(int i=n;i>=1;i--){
		for(int j=1;j<=n;j++){
			u[i][j]=u[i+1][j-1]+a[i][j];
			d[i][j]=d[i+1][j+1]+a[i][j];
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if((i+j)%2==1){
				bl[i][j]=l[i][j]+r[i][j]+u[i][j]+d[i][j]-3*a[i][j];
			}
			else{
				wh[i][j]=l[i][j]+r[i][j]+u[i][j]+d[i][j]-3*a[i][j];
			}
		}
	}
}

void solve(){
	init();
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if((i+j)%2==1){
				if(cnt1<=bl[i][j]){
					cnt1=bl[i][j];
					bx=i;
					by=j;
				}
			}
			else{
				if(cnt2<=wh[i][j]){
					cnt2=wh[i][j];
					wx=i;
					wy=j;
				}
			}
		}
	}
	
	cout<<cnt1+cnt2<<endl;
	cout<<wx<<" "<<wy<<" "<<bx<<" "<<by;
}


signed main(){
	int T=1;
	while(T--){
		solve();
	}
    return 0;
}


```

---

## 作者：DennyQi (赞：0)

我们将对角线分为两个方向的。定义斜率为正的对角线为$l$对角线，斜率为负的对角线为$r$对角线。我们将同一个方向的所有对角线按从一个角到另一个角按顺序标号，那么两条相邻对角线的标号的奇偶性一定不同。

当我们选择两条$l$对脚线时，一定一条长一条短。而如果两条对角线奇偶性相同，那么他们的$r$对角线`一定会相交`——因为这条$r$对角线一定会经过短的那条，而短的那条可以理解为包含在长的那条里的。

而反过来，如果选择两条奇偶性不同的$l$对角线，那么对应的$r$对角线`一定不会相交`（错开了）。

于是，我们可以选择两条$l$对角线，保证他们的奇偶性不同。对于每一条$l$对角线，$r$对角线可以`任选`。这样，一条$l$就对应了一条$r$，问题就变得`独立`了。既然题目要求最大化答案，那么不妨对于每一条$l$对角线找到最大的那个$r$对角线，最后找到最大的两条一奇一偶得到答案即可。

考虑代码实现，我们可以把对角线的和存在一个数组里，我们观察发现$l$对角线上的点$(x,y)$，有$x+y$为定值；$r$对角线上$(x-y)$为定值（在解决八皇后问题的优化时我们曾经思考过这个问题）。至于两条对角线的交点坐标，解一下方程即可。

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define int long long
using namespace std;
const int N = 2010;
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0' || c>'9')) c = getchar();
    if(c=='-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
    return x*w;
}
int n,a[N][N],l[N<<1],r[N<<1],m,ans,x1,x2,y1,y2,tmp;
signed main(){
	// freopen("file.in","r",stdin);
	n = read();
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= n; ++j){
			a[i][j] = read();
			l[i+j] += a[i][j];
			r[i-j+n] += a[i][j];
		}
	}
	m = -1;
	for(int i = 2; i <= n+n; ++i){
		if(i & 1) continue;
		if(i <= 1+n){
			for(int j = n-i+2; j <= n+i-2; j += 2){
				tmp = l[i]+r[j]-a[(i+j-n)/2][(i-j+n)/2];
				if(tmp > m){
					m = tmp;
					x1 = (i+j-n)/2;
					y1 = (i-j+n)/2;
				}
			}
		}else{
			for(int j = i-n; j <= 3*n-i; j += 2){
				tmp = l[i]+r[j]-a[(i+j-n)/2][(i-j+n)/2];
				if(tmp > m){
					m = tmp;
					x1 = (i+j-n)/2;
					y1 = (i-j+n)/2;
				}
			}
		}
	}
	ans = m, m = -1;
	for(int i = 2; i <= n+n; ++i){
		if((i & 1) == 0) continue;
		if(i <= 1+n){
			for(int j = n-i+2; j <= n+i-2; j += 2){
				tmp = l[i]+r[j]-a[(i+j-n)/2][(i-j+n)/2];
				if(tmp > m){
					m = tmp;
					x2 = (i+j-n)/2;
					y2 = (i-j+n)/2;
				}
			}
		}else{
			for(int j = i-n; j <= 3*n-i; j += 2){
				tmp = l[i]+r[j]-a[(i+j-n)/2][(i-j+n)/2];
				if(tmp > m){
					m = tmp;
					x2 = (i+j-n)/2;
					y2 = (i-j+n)/2;
				}
			}
		}
	}
	ans += m;
	printf("%lld\n%lld %lld %lld %lld",ans,x1,y1,x2,y2);
	return 0;
}
```

---

## 作者：liuyifan (赞：0)

## 暴力（DP）

1.每一条主对角线上的横纵坐标的和相等

2.每一条副对角线上的横纵坐标的差同样相等

所以我们就可以在输入时预处理了

因为发现要获得最大值，那么另一条就不能相交在同一个格子上。

所以仅仅要满足两个bishops的横纵坐标之和互为奇偶即可了。二者的和就是最终答案了

code:
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register
#define ll long long//以后开long long打ll就可以了，更轻松
#define inf 0x3f3f3f3f//无穷大
#define lowbit(x) x&(-x)//树状数组模板
using namespace std;
ll n,num[2005][2005],sumn[1000005],summ[1000005],max1,max2,s,x1,y1,x2,y2;//注意本题卡long long
//CF的很多题都要开LONG LONG,小心
int main()
{
    while(scanf("%lld",&n)==1)//多组数据输入方式
    {
        memset(sumn,0,sizeof sumn);
        memset(summ,0,sizeof summ);//注意数组清零
        for(reg int i=1;i<=n;i++)
        for(reg int j=1;j<=n;j++)
        {
            scanf("%lld",&num[i][j]);
            sumn[i+j]+=num[i][j];
            summ[i-j+n]+=num[i][j];//预处理两条对角线
        }
        max1=max2=-inf;//清空
        for(reg int i=1;i<=n;i++)
        for(reg int j=1;j<=n;j++)
        {
            if((i+j)&1)
            {
                if(max1<(s=sumn[i+j]+summ[i-j+n]-num[i][j]))
                {
                    max1=s;//统计2个最大值,如前面所述
                    x1=i;
                    y1=j;
                }
            }//分奇偶性分别讨论
            else
            {
                if(max2<(s=sumn[i+j]+summ[i-j+n]-num[i][j]))
                {
                    max2=s;//统计2个最大值,如前面所述
                    x2=i;
                    y2=j;
                }
            }//同上
        }
        printf("%lld\n%lld %lld %lld %lld\n",max1+max2,x1,y1,x2,y2);//输出结果
    }
    return 0;
}
```


---

