# Making Shapes

## 题目描述

给定 $n$ 个两两不共线的二维向量。你可以用以下方式在二维平面上用这些向量构造图形：

1. 从原点 $(0, 0)$ 开始。
2. 选择一个向量，将该向量的线段加到当前点。例如，如果当前点在 $(x, y)$，你选择向量 $(u, v)$，则从当前点画一条线段到 $(x + u, y + v)$，并将当前点更新为 $(x + u, y + v)$。
3. 重复第 2 步，直到你再次回到原点。

每个向量可以重复使用任意多次。

请计算可以用上述步骤构造出的不同的、非退化（面积大于 $0$）且凸的图形的数量，要求这些图形的构成向量按逆时针顺序排列，并且该图形可以通过平移被包含在一个 $m \times m$ 的正方形内。由于答案可能很大，请对 $998244353$ 取模。

如果存在某种平行移动能使第一个图形与第二个图形重合，则认为这两个图形是相同的。

如果存在某种平行移动，使得图形内或边界上的每个点 $(u, v)$ 都满足 $0 \leq u, v \leq m$，则认为该图形可以被包含在 $m \times m$ 的正方形内。

## 说明/提示

第一个样例的所有图形如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290F/1435a49a0854cf885bd0a880b2bd4ec616aaecf0.png)

第二个样例的唯一图形如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290F/c198c6d97ae318f4efbc29b95f2307d41e83d32d.png)

第四个样例的唯一图形如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290F/5612d8b3b2e07c811bb5d8b4ac9e1b97873da5e3.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
-1 0
1 1
0 -1```

### 输出

```
3```

## 样例 #2

### 输入

```
3 3
-1 0
2 2
0 -1```

### 输出

```
1```

## 样例 #3

### 输入

```
3 1776966
-1 0
3 3
0 -2```

### 输出

```
296161```

## 样例 #4

### 输入

```
4 15
-4 -4
-1 1
-1 -4
4 3```

### 输出

```
1```

## 样例 #5

### 输入

```
5 10
3 -4
4 -3
1 -3
2 -3
-3 -4```

### 输出

```
0```

## 样例 #6

### 输入

```
5 1000000000
-2 4
2 -3
0 -4
2 4
-1 -3```

### 输出

```
9248783```

# 题解

## 作者：tzc_wk (赞：18)

[Codeforces 题面传送门](https://codeforces.ml/contest/1290/problem/F) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1290F)

数位 dp 好题。

首先，由于是凸包，一但向量集合确定，凸包的形态肯定就已经确定了。考虑什么样的向量集合能够组成符合条件的凸包，我们假设第 $i$ 个向量选了 $c_i$ 次。因为凸包是首尾相连的，所以必然有 $\sum\limits_{i=1}^nc_ix_i=0,\sum\limits_{i=1}^nc_iy_i=0$。上式也可写作 $\sum\limits_{x_i>0}c_ix_i=\sum\limits_{x_i<0}c_i(-x_i),\sum\limits_{y_i>0}c_iy_i=\sum\limits_{y_i<0}c_i(-y_i)$。其次，由于凸包能够被放到 $m\times m$ 的矩形内，所以凸包横纵坐标的极差必须 $\le m$，以横坐标为例，还是因为原图是一个凸包，所以凸包的横坐标肯定是先涨一段，再跌到最低点，再涨到 $0$，因此横坐标的极差为 $\sum\limits_{x_i<0}c_i(-x_i)$，同理纵坐标的极差为 $\sum\limits_{y_i<0}c_i(-y_i)$，因此一组 $\{c_1,c_2,\cdots,c_n\}$ 符合条件的充要条件是：

- $\sum\limits_{x_i>0}c_ix_i=\sum\limits_{x_i<0}c_i(-x_i),\sum\limits_{y_i>0}c_iy_i=\sum\limits_{y_i<0}c_i(-y_i)$
- $\sum\limits_{x_i<0}c_i(-x_i)\le m,\sum\limits_{y_i<0}c_i(-y_i)\le m$

接下来思考怎样求符合条件的 $\{c_1,c_2,\cdots,c_n\}$ 的个数。注意到 $n$ 很小，值域也很小，因此考虑**数位 DP**，考虑从低到高逐位确定 $c_i$ 每一位的值，记 $dp_{d,px,py,nx,ny,p,q}$ 表示当前确定了最低的 $d$ 位，当前为正的 $x_i$ 的 $\sum c_ix_i$ 产生了 $px$ 的进位，当前为负的 $x_i$ 的 $\sum c_i(-x_i)$ 产生了 $nx$ 的进位，当前为正的 $y_i$ 的 $\sum c_iy_i$ 产生了 $py$ 的进位，当前为负的 $x_i$ 的 $\sum c_i(-y_i)$ 产生了 $ny$ 的进位，当前 $\sum\limits_{x_i>0} c_ix_i$ 的后 $d$ 位是否 $\le m$ 的后 $d$ 位，当前 $\sum\limits_{y_i>0} c_iy_i$ 的后 $d$ 位是否 $\le m$ 的后 $d$ 位的符合条件的 $\{c_i\}$ 的个数，转移就枚举这 $n$ 个数第 $d+1$ 位的值即可。

复杂度 $20^4·2^5·\log m$，可以通过。写成记忆化搜索的形式可能会跑得快一点。

总结：看到求 $\sum\limits_{i=1}^na_ic_i=X$ 的 $\{c_i\}$ 的组数，并且 $n,a_i$ 都很小而 $X$ 很大的题目可以想到数位 DP，类似的还有[这个题](https://acm.hdu.edu.cn/showproblem.php?pid=6953)。

```cpp
const int MOD=998244353;
int n,m,x[7],y[7],dp[34][23][23][23][23][2][2];
void add(int &x,int v){((x+=v)>=MOD)&&(x-=MOD);}
int chk(int dm,int dn,int ori){
	if(dm^dn) return (dn<dm)?0:1;
	return ori;
}
int calc(int p,int ps_x,int ps_y,int ng_x,int ng_y,int xm,int ym){
	if(p==30) return (!ps_x&&!ps_y&&!ng_x&&!ng_y&&!xm&&!ym);
	if(~dp[p][ps_x][ps_y][ng_x][ng_y][xm][ym]) return dp[p][ps_x][ps_y][ng_x][ng_y][xm][ym];
	int d=m>>p&1;dp[p][ps_x][ps_y][ng_x][ng_y][xm][ym]=0;
	for(int s=0;s<(1<<n);s++){
		int tps_x=ps_x,tps_y=ps_y,tng_x=ng_x,tng_y=ng_y;
		for(int i=1;i<=n;i++) if(s>>(i-1)&1){
			(x[i]>0)?(tps_x+=x[i]):(tng_x-=x[i]);
			(y[i]>0)?(tps_y+=y[i]):(tng_y-=y[i]);
		} int d_px=tps_x&1,d_py=tps_y&1,d_nx=tng_x&1,d_ny=tng_y&1;
		if(d_px==d_nx&&d_py==d_ny)
			add(dp[p][ps_x][ps_y][ng_x][ng_y][xm][ym],
			calc(p+1,tps_x>>1,tps_y>>1,tng_x>>1,tng_y>>1,chk(d,d_px,xm),chk(d,d_py,ym)));
	} return dp[p][ps_x][ps_y][ng_x][ng_y][xm][ym];
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
	memset(dp,-1,sizeof(dp));
	printf("%d\n",(calc(0,0,0,0,0,0,0)-1+MOD)%MOD);
	return 0;
}
```



---

## 作者：MatrixCascade (赞：8)

s\*\*\*a 推荐的题。\*3500 还是挺妙的

首先，如果选的向量确定了，若能构成一个凸多边形，那么排列方案也是固定的。然后假设选了 $f_i$ 次第 $i$ 个向量，那么这组向量有唯一一组排列方式的使得可以组成一个凸多边形的要求是 $\sum\limits_{x_i<0}-x_i=\sum\limits_{x_i>0}x_i$ 并且 $\sum\limits_{y_i<0}-y_i=\sum\limits_{y_i>0}y_i$，还需要能被包在 $m*m$ 的正方形内，所以还需要 $\max(\sum\limits_{i\in p}x_i)-\min(\sum\limits_{i\in p}x_i)\leq m$，$\max(\sum\limits_{i\in p}y_i)-\min(\sum\limits_{i\in p}y_i)\leq m$，p 表示多边形上的点集。显然，这条件等价于 $\sum\limits_{x_i>0}x_i\leq m$ 并且 $\sum\limits_{y_i>0}y_i\leq m$

推到这里我就不会了，因为数方案数大概率是 dp，如果要 dp 需要$\sum x_i$ 之类的东西，显然没法做，看了题解才发现这有个转数位 dp 的 trick。。

考虑从小到大枚举二进制位，**这样后面的转移不会影响前面**，这样前面的那个定义 $dp_{p,xx,xy,yx,yy,f1,f2}$ 表示：后 $p$ 位确定当前 $\sum\limits_{x_i>0}x_i$ 的**进位**是 $xx$，$\sum\limits_{x_i<0}-x_i$ 的**进位**是 $xy$，当前 $\sum\limits_{y_i>0}y_i$ 的**进位**是 $yx$，当前 $\sum\limits_{y_i<0}-y_i$ 的**进位**是 $yy$，$f1,f2$ 表示 $\sum\limits_{x_i>0}x_i$ $\sum\limits_{x_i>0}y_i$ 的后 $p$ 与 $m$ 的后 $p$ 位谁大谁小，如果 $m$ 更小的话就是 $1$，否则就是 $0$。

个人觉得记忆化搜索实现起来方便一点，转移的时候 $2^n$ 枚举每一个向量在这一位是 $1$ 还是 $0$，转移的时候需要 $\sum\limits_{x_i>0}x_i$ 的第 $p$ 位等于 $\sum\limits_{x_i<0}-x_i$ 的第 $p$ 位，且 $\sum\limits_{y_i>0}y_i$ 的第 $p$ 位置等于 $\sum\limits_{y_i<0}-y_i$ 的时候可以转移，因为如果第 $p$ 位都不相等了，后面怎么取也不会相等的（**二进制位**）因为 $m$ 最大是 $10^9$，那么到了第 $31$ 位的时候就得判是否合法，显然，如果 $xx,xy,yx,yy,f1,f2$ 全为 $0$ 的时候才是合法的。

设最大进位是 $k$，时间复杂度是 $2^n\log m\times k^4$，显然 $k<25$，可以通过。

感觉这个题的难点就是在这个转数位 dp 的 trick 上，希望下次遇到这类的可以想到数位 dp 吧...

```cpp
//#pragma GCC optimize("Ofast", "unroll-loops")
//#pragma GCC target("sse", "sse2", "sse3", "ssse3", "sse4", "avx")
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define YES puts("YES")
#define NO puts("NO")
#define Yes puts("Yes")
#define No puts("No")
#define edl puts("")
#define mc cerr<<"qwq\n"
#define error goto gg
#define def gg:
#define rd(x) x=read()
#define opl(x) printf("%lld",x)
#define opls(x) printf("%lld ",x)
#define opd(x) printf("%d",x)
#define opds(x) printf("%d ",x)
#define ver(x) for(int i=head[x];i;i=nxt[i])
#define up(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define pu(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define ft(x) for(int i=head[x];i;i=nxt[i])
#define upn up(i,1,n)
#define upm up(j,1,m)
#define pun pu(i,n,1)
#define pum pu(j,m,1)
#define up_(x) up(i,1,x)
#define pu_(x) pu(j,x,1)
#define ep emplace_back
#define fp for(auto to:
#define pf )
#define pii pair<int,int>
#define pis pair<int,string>
#define psi pair<string,int>
#define mkp make_pair
#define fi first
#define se second
#define mii map<int,int>
#define mis map<int,string>
#define msi map<string,int>
#define mvi map<vector<int>,int>
#define miv map<int,vector<int>>
#define rdn rd(n)
#define rdm rd(m)
#define rdk rd(k)
using namespace std;
int n, m, k;
int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}

#define inf 1000000000000000000ll
ll Max(ll a=-inf,ll b=-inf,ll c=-inf,ll d=-inf,ll e=-inf,ll f=-inf,ll g=-inf,ll h=-inf)
{
	return max(max(max(a,b),max(c,d)),max(max(e,f),max(g,h)));
}
ll Min(ll a=inf,ll b=inf,ll c=inf,ll d=inf,ll e=inf,ll f=inf,ll g=inf,ll h=inf)
{
	return min(min(min(a,b),min(c,d)),min(min(e,f),min(g,h)));
}
#undef inf
void chkmin(int &x,int y)
{
	if(x>y)x=y;
}
void chkmax(int &x,int y)
{
	if(x<y)x=y;
}
const int mod=998244353;
int x[10],y[10];
int dp[32][25][25][25][25][2][2];
//前 p 位，正x 进位 xx，负x 进位 xy，... f1：前 p 位>m or <=m，f2同理。 
int dfs(int p,int xx,int xy,int yx,int yy,int f1,int f2)
{
//	cout<<p;edl;
	if(p==30)
	{
	//	cout<<xx<<" "<<xy<<" "<<yx<<" "<<yy;edl;
		if(xx==0&&xy==0&&yx==0&&yy==0&&f1==0&&f2==0)
		{
			return 1;
		}
		return 0;
	}
	if(dp[p][xx][xy][yx][yy][f1][f2]!=-1)return dp[p][xx][xy][yx][yy][f1][f2];
	int &w=dp[p][xx][xy][yx][yy][f1][f2];
	dp[p][xx][xy][yx][yy][f1][f2]=0; 
	w=0;
	up(i,0,(1<<n)-1)
	{
		int X1=xx,X2=xy,Y1=yx,Y2=yy;
		up(j,0,n-1)
		{
			if(!(i&(1<<j)))continue;
			if(x[j]<0)
			{
				X2-=x[j];
			}
			else X1+=x[j];
			if(y[j]<0)
			{
				Y2-=y[j];
			}
			else Y1+=y[j];
		}
	//	assert(X1>=0);assert(X2>=0);assert(Y1>=0);assert(Y2>=0);
		int ff1=0,ff2;
		if(((X1&1)!=(X2&1))||((Y1&1)!=(Y2&1)))continue;
		if(m&(1ll<<p))
		{
			if(f1)
			{
				if(X1&1)
				{
					ff1=1;
				}
				else ff1=0;
			}
			else
			{
				ff2=0;
			}
			if(f2)
			{
				if(Y1&1)
				{
					ff2=1;
				}
				else ff2=0;
			}
			else
			{
				ff2=0;
			}
		}
		else
		{
			if(f1)
			{
				ff1=1;
			}
			else
			{
				if(X1&1)
				{
					ff1=1;
				}
				else
				{
					ff1=0;
				}
			}
			if(f2)
			{
				ff2=1;
			}
			else
			{
				if(Y1&1)
				{
					ff2=1;
				}
				else
				{
					ff2=0;
				}
			}
		}
		
		dp[p][xx][xy][yx][yy][f1][f2]+=dfs(p+1,X1/2,X2/2,Y1/2,Y2/2,ff1,ff2);w%=mod;
	}
	return dp[p][xx][xy][yx][yy][f1][f2];
}
signed main()
{
	int T=1;
	while(T--)
	{
		rdn;rdm;
		up(i,0,n-1)rd(x[i]),rd(y[i]);
		memset(dp,-1,sizeof(dp));
		int ans=dfs(0,0,0,0,0,0,0);
		ans--;ans+=mod;ans%=mod;
		opd(ans);
	}
}
/*
4 1000000000
-2 4
2 -3
0 -4
-1 -3
1 3 
*/
/*
  When you are coding,remember to:
	   - clear the arrays if a problem has many tasks.
	   - pay attention to some special cases(n=0,1).
	   - Don't code before think completely.
	   - ...
*/





```


---

## 作者：45dino (赞：3)

一开始拿到这个题的时候，就被 1F 和 `*3500` 吓到了，其实这个题目写起来并没有那么难。主要难度体现在一个 trick 上。

可以推出两个等式和两个不等式，但我一开始错误地把不等式推成了：
$$\sum_{i=1,x_i>0}^n c_ix_i-\sum_{i=1,x_i<0}^n c_ix_i\le m\space(\text{y类似})$$
之所以不用考虑 $x_i<0$ 的部分，是因为在选择了一些向量之后，必然有一种组合方法（确切来说，是唯一的）可以使得所有向量都在第一象限。

这个似乎有点难以理解，结合一下 `Sample #4`:

![](https://cdn.luogu.com.cn/upload/image_hosting/15ykmpzs.png)

容易发现，还有一种画法不在第一象限，但也围成了一个凸包：

![](https://cdn.luogu.com.cn/upload/image_hosting/mbkacd8y.png)

不过这个画法可以通过平移与前者重复，所以属于本质相同的图形，不能重复计数。
>Two shapes are considered the same if there exists some parallel translation of the first shape to another.

**2022/1/12注：该证明已被推翻。**

总之，不等式应该是这样的形式：
$$\sum_{i=1,x_i>0}^n c_ix_i\le m\space(\text{y类似})$$
我觉得这个是这个题目难度的一部分，如果这个推错了，整个题目就 gg 了。

接下来考虑进行 dp 转移，因为直接把 $c_i$ 放到状态里会炸，所以考虑将其分组。

令：
$$\sum_{i=1,x_i>0}^n c_ix_i=A$$
$$\sum_{i=1,x_i<0}^n c_ix_i=B$$
$$\sum_{i=1,y_i>0}^n c_iy_i=C$$
$$\sum_{i=1,y_i<0}^n c_iy_i=D$$
然后把每一个 $c_i$ 拆成二进制，最多 $31$ 位，一层一层地算，这样就能用这种方法把 $A,B,C,D$ 拼出来。

dp 状态为七维：
- 目前到第几层。
- 当前这一层要往 $A$ 里面加多少。
- 当前这一层要往 $B$ 里面加多少。
- 当前这一层要往 $C$ 里面加多少。
- 当前这一层要往 $D$ 里面加多少。
- 当前的 $A$ 是否严格小于当前的 $m$。 (就是说，如果后面随便填，是否都能保证不大于 m)
- 当前的 $C$ 是否严格小于当前的 $m$。

转移复杂度为 $\Theta (\log m \times n^4\times 2^n)$，外加 $2^{4\times 2}\times 2^2=1024$ 的常数。

trick 很神奇，不知道是不是只要表示数量的维度装不下，就可以用这个 trick。

## Upd on 2022/1/12
有朋友说不是所有符合条件的凸包都能完全在第一象限，确实啊。

[反例](https://www.geogebra.org/geometry/kpw4hnsq)

事实上，如果改成一二象限（或一四）就是对的。

但是，这个结论仍然是对的。

以 $x$ 值为例，由于
$$\sum_{i=1,x_i>0}^n c_ix_i=-\sum_{i=1,x_i<0}^n c_ix_i\le m$$
而这又是一个凸包，所以说 $x$ 值的极差为 $\sum_{i=1,x_i>0}^n c_ix_i$。因为要被 $m\times m$ 的正方形装下，因此 $x$ 和 $y$ 的极差都不能大于 $m$。

尽管答案没有错，过程却颇有不同，充分体现出我的 naive。

---------
后记：教练讲这个题的时候，基本就照着 Fuyuki 的题解讲的。

~~反转了，教练就是 Fuyuki%%%~~

---

## 作者：Fuyuki (赞：3)

## Description

给定 $n$ 个两两不平行的向量 $(x_i,y_i)$，求这些向量能构成多少个不同的，顶点横纵坐标的极差分别不超过 $m$，面积大于 $0$ 的凸包。

两个凸包被视作相同，当且仅当两个凸包能够通过平移重合。

答案对 $998244353$ 取模。

$n\leq 5,m\leq 10^9,|x_i|,|y_i|\leq 4$ 。

## Solution

因为是凸包，所以如果确定了每个向量的出现次数 $c$，那么这些向量的顺序也就确定了。

换言之，需要进行计数的就是满足下列条件的数组 $c$，其中 $c_i$ 表示向量 $i$ 的出现次数：

$$\sum_{i=1}^{n}c_ix_i=0,\sum_{i=1}^n c_iy_i=0$$

还有一个条件是凸包顶点间的坐标极差不超过 $m$，也就是说：

$$\sum_{i=1,x_i>0}^nc_ix_i\leq m,\sum_{i=1,y_i>0}^nc_iy_i\leq m$$

从常规的角度来设计状态的话无法绕过 $\sum cx$ 这种形式的状态，所以就需要用到一种非常极端的优化方法。

枚举哪些 $c$ 的二进制下第$k$位为 $1$，那么就可以采用类似数位 $dp$ 的办法，从低位向高位转移，只存下 $\frac{\sum c_ix_i}{2^k}$ 这种形式的状态，而且因为不能转移的状态是不需要储存的，所以只需要保留 $\frac{\sum c_ix_i}{2^k}\leq \sum x_i$ 的状态，而这样的状态是只有 $O(nV)$ 种的。再状压一下两维与 $m$ 的关系就可了（后缀是否大于 $m$）。

那么复杂度就是 $O(2^n(nV)^4logm)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=5,M=N<<2,S=1<<N,mod=998244353;
int n,m,l,x,X,y,Y,A,B,ans,dx[N],dy[N];
int nx[S],px[S],ny[S],py[S],f[32][M][M][M][M][2][2];
void check(int&x){x-=mod,x+=x>>31&mod;}
int main(){
	scanf("%d%d",&n,&m),(l=1<<n--)--,*******f=1;
	FOR(i,0,n)scanf("%d%d",dx+i,dy+i);
	FOR(i,0,l)FOR(j,0,n)if(i>>j&1)
		(dx[j]>0?nx:px)[i]+=abs(dx[j]),(dy[j]>0?ny:py)[i]+=abs(dy[j]);
	FOR(t,0,30)FOR(i,0,nx[l])FOR(j,0,px[l])FOR(k,0,ny[l])FOR(p,0,py[l])FOR(a,0,1)FOR(b,0,1)
		FOR(s,0,l)if(!(i+nx[s]+j+px[s]&1)&&!(k+ny[s]+p+py[s]&1)){
			A=a+(i+nx[s]&1)>(m>>t&1),B=b+(k+ny[s]&1)>(m>>t&1);
			x=i+nx[s]>>1,X=j+px[s]>>1,y=k+ny[s]>>1,Y=p+py[s]>>1;
			check(f[t+1][x][X][y][Y][A][B]+=f[t][i][j][k][p][a][b]);
		}
	check(ans=f[31][0][0][0][0][0][0]+mod-1),cout<<ans;
	return 0;
}
```

---

## 作者：ningago (赞：2)

需要生成一个凸多边形，则向量的先后顺序按极角顺序一定是有单调性的，即如果确定了每种向量的个数，其生成的凸包，要么无解，要么唯一。

对于一种选择方案，记第 $i$ 种向量选了 $cnt_i(\geq 0)$ 次。则如果需要生成一个封闭多边形，需满足：

$$\sum_{i=1}^ncnt_i\cdot\vec{v_i}=(0,0)$$

即：

$$\sum_{i=1}^ncnt_i\cdot x_i=\sum_{i=1}^ncnt_i\cdot y_i=0$$

由于有 $m$ 的限制，不妨将 $x,y$ 的正负分开考虑，即：

$$\sum_{i=1,x_i\geq 0}^ncnt_i\cdot x_i=\sum_{i=1,x_i\leq 0}cnt_i\cdot(-x_i)\leq m$$

$$\sum_{i=1,y_i\geq 0}^ncnt_i\cdot y_i=\sum_{i=1,y_i\leq 0}cnt_i\cdot(-y_i)\leq m$$

所以答案即为使得上式成立的 $cnt$ 取值数。

由于 $|x|,|y|,n$ 都极小，考虑数位 DP，从低到高考虑上面四个变量的取值（在这一位上的进位），以及是否抵上限即可。

最后注意减去所有 $cnt_i=0$ 的情况。

进位数的最大值为 $t=\left\lfloor\dfrac{n*|x|+t}{2}\right\rfloor$，约为 $n\cdot |x|=20$。复杂度为 $O(\log m\cdot t^4\cdot 2^n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

#define mod 998244353
void plus_(int &x, int y){x = (x + y) % mod; }
int n, m;
int dp[32][25][25][25][25][2][2];
int x[7], y[7];

int dfs(int d, int px, int py, int nx, int ny, bool f1, bool f2)
{
	if(d == 30)
		return (!px && !py && !nx && !ny && f1 && f2);
	if(~dp[d][px][py][nx][ny][f1][f2])
		return dp[d][px][py][nx][ny][f1][f2];
	int &res = dp[d][px][py][nx][ny][f1][f2];
	res = 0;
	int t = !!(m & (1 << d));
	for(int S = 0; S < (1 << n); S++)
	{
		int px_ = px, py_ = py;
		int nx_ = nx, ny_ = ny;
		for(int i = 1; i <= n; i++)
		{
			if(!(S & (1 << (i - 1))))
				continue;
			if(x[i] > 0)
				px_ += x[i];
			else
				nx_ += -x[i];
			if(y[i] > 0)
				py_ += y[i];
			else
				ny_ += -y[i];
		}
		if((px_ & 1) != (nx_ & 1) || (py_ & 1) != (ny_ & 1))
			continue;
		int tx = (px_ & 1);
		int ty = (py_ & 1);
		int tmp = dfs(d + 1, px_ >> 1, py_ >> 1, nx_ >> 1, ny_ >> 1, 
			tx == t ? f1 : tx < t , ty == t ? f2 : ty < t);
		plus_(res, tmp);
	}
	return res;
}

int main()
{
	memset(dp, -1, sizeof(dp));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &x[i], &y[i]);
	int ans = mod - 1;
	plus_(ans, dfs(0, 0, 0, 0, 0, 1, 1));
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：UKE_Automation (赞：0)

### CF1290F Making Shapes

[$\text{Link}$](https://codeforces.com/problemset/problem/1290/F)

首先容易发现一点：如果每个向量的使用次数 $a_i$ 确定了，那么最后形成的多边形是唯一确定的。所以我们只需要数出合法的 $a_i$ 的数量即可。

考虑合法的 $a_i$ 满足什么条件，第一个条件显然是 $\sum a_i x_i=\sum a_iy_i=0$，因为要回到原点；第二个条件就是多边形能塞进 $m\times m$ 的范围内，这个也很好判断，就是 $\sum a_ix_i[x_i>0]\le m$ 以及 $\sum a_iy_i[y_i>0]\le m$。那么实际上我们可以把第一个条件改写一下，变成 $\sum a_ix_i[x_i>0]+\sum a_ix_i[x_i\le 0]=\sum a_iy_i[y_i>0]+\sum a_iy_i[y_i\le 0]=0$，这样的话条件就只和这四个部分有关了。

不过这个计数貌似还是困难的。注意到 $n,x_i,y_i$ 的范围都不大，考虑数位 dp 求解。为了方便，把所有操作放到二进制下进行，这样我们我们枚举一个长为 $n$ 的串就可以知道每一个 $a_i$ 在当前位上的值。考虑状态，既然我们的条件只和那四个值有关，那就把这些值计入状态，设 $dp(d,dx,dy,nx,ny,p,q)$ 表示当前枚举到从低到高第 $d$ 位，钦定第 $d-1$ 位的 $\sum a_ix_i[x_i>0]$ 的进位为 $dx$、$\sum a_ix_i[y_i>0]$ 的进位为 $dy$、$\sum a_ix_i[x_i\le0]$ 的进位为 $nx$、$\sum a_ix_i[y_i\le0]$ 的进位为 $ny$，同时钦定第 $d-1$ 位及更低位算出的 $\sum a_ix_i[x_i>0]$ 是否 $\le m$ 以及 $\sum a_iy_i[y_i>0]$ 是否 $\le m$ 的方案数。转移的时候枚举当前位的 $a_i$ 的值，然后更新状态即可。

初值为 $dp(t,0,0,0,0,0,0)=1$，最后的答案是 $dp(0,0,0,0,0,0,0)$。嫌枚举状态太长的话可以用记忆化搜索实现。由于进位数量最大值为 $\sum\limits_{i=1}^\infty \lfloor\dfrac{nV}{2^i}\rfloor=nV$，所以总复杂度是 $O((nV)^4\times 2^n\times \log m)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

const int Maxn = 2e5 + 5;
const int Inf = 2e9;
const int Mod = 998244353;
il int Add(int x, int y) {return x + y >= Mod ? x + y - Mod : x + y;} il void pls(int &x, int y) {x = Add(x, y);}
il int Del(int x, int y) {return x - y < 0 ? x - y + Mod : x - y;} il void sub(int &x, int y) {x = Del(x, y);}
il int max(int x, int y) {return x >= y ? x : y;} il void chkmax(int &x, int y) {x = (x >= y ? x : y);}
il int min(int x, int y) {return x <= y ? y : y;} il void chkmin(int &x, int y) {x = (x <= y ? x : y);}
il int qpow(int a, int b) {int res = 1; for(; b; a = 1ll * a * a % Mod, b >>= 1) if(b & 1) res = 1ll * res * a % Mod; return res;}
il int Inv(int a) {return qpow(a, Mod - 2);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool flg = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	flg ? putchar('\n') : putchar(' ');
}

int n, m, x[6], y[6];
int dp[35][25][25][25][25][2][2];
int work(int p1, int p2, int p) {
	if(p1 != p2) return p2 > p1 ? 1 : 0;
	return p;
}

int dfs(int d, int dx, int dy, int nx, int ny, int p, int q) {
	if(d == 30) return (!dx && !dy && !nx && !ny && !p && !q);
	int &ret = dp[d][dx][dy][nx][ny][p][q];
	if(ret != -1) return ret;
	int t = (m >> d) & 1; ret = 0;
	for(int S = 0; S < (1 << n); S++) {
		int _dx = dx, _dy = dy, _nx = nx, _ny = ny;
		for(int i = 1; i <= n; i++) {
			if((S >> i - 1) & 1) {
				if(x[i] > 0) _dx += x[i]; else _nx -= x[i];
				if(y[i] > 0) _dy += y[i]; else _ny -= y[i];
			}
		}
		if((_dx & 1) == (_nx & 1) && (_dy & 1) == (_ny & 1)) {
			int p1 = _dx & 1, p2 = _dy & 1;
			pls(ret, dfs(d + 1, _dx >> 1, _dy >> 1, _nx >> 1, _ny >> 1, work(t, p1, p), work(t, p2, q)));
		}
	}
	return ret;
}

int main() {
	read(n), read(m);
	for(int i = 1; i <= n; i++) read(x[i]), read(y[i]);
	memset(dp, -1, sizeof dp);
	int ans = dfs(0, 0, 0, 0, 0, 0, 0);
	write(Del(ans, 1));
	return 0;
}

```

---

## 作者：Leasier (赞：0)

首先转化一下题意：

- $A$ 中不能全为 $0$。
- $\displaystyle\sum_{i = 1}^n A_i x_i = \sum_{i = 1}^n A_i y_i = 0$。
- $\displaystyle\sum_{x_i > 0} A_i x_i, \sum_{y_i > 0} A_i y_i \leq m$。
- 求非负整数序列 $A$ 的方案数。

考虑在第一条限制中把 $x_i > 0$ 与 $x_i < 0$ 分开（$y_i$ 同理），可知：

- $\displaystyle\sum_{x_i > 0} A_i x_i = \sum_{x_i < 0} A_i (-x_i)$。

但是直接 dp  看上去十分困难。不妨考虑一下 $n, |x_i|, |y_i|$ 为啥这么小。

- trick：**逐位处理，此时我们每次需要讨论的值域缩减至 $O(nw)$**，这里 $w = \max(|x_i|, |y_i|) = 4$。

设 $dp_{a, b, c, d, e, f, g}$ 表示从低到高讨论到第 $a$ 位，$\geq a$ 位的部分（不考虑当前这次新加的）$\displaystyle\sum_{x_i > 0} A_i x_i, \sum_{y_i > 0} A_i y_i, \sum_{x_i < 0} A_i (-x_i), \sum_{y_i < 0} A_i (-y_i)$ 分别为 $b, c, d, e$，只考虑 $< a$ 位的部分 $\displaystyle\sum_{x_i > 0} A_i x_i, \sum_{y_i > 0} A_i y_i$ 是否超过 $m$ 分别为 $f, g$。

转移较为简单，不再赘述。时间复杂度为 $O(2^n (nw)^4 \log m)$，加上记忆化搜索后跑得飞快。

代码：
```cpp
#include <stdio.h>

const int mod = 998244353;
int x[7], y[7], dp[30][21][21][21][21][2][2];
bool vis[30][21][21][21][21][2][2];

inline int trans(int f, int cur, int ref){
	if (cur < ref) return 0;
	if (cur > ref) return 1;
	return f;
}

int dfs(int a, int b, int c, int d, int e, int f, int g, int n, int m){
	if (a == 30) return b == 0 && c == 0 && d == 0 && e == 0 && f == 0 && g == 0 ? 1 : 0;
	if (vis[a][b][c][d][e][f][g]) return dp[a][b][c][d][e][f][g];
	int bit = m >> a & 1, full = (1 << n) - 1;
	vis[a][b][c][d][e][f][g] = true;
	for (int i = 0; i <= full; i++){
		int b_ = b, d_ = d, c_ = c, e_ = e;
		for (int j = 1; j <= n; j++){
			if (i >> (j - 1) & 1){
				if (x[j] > 0){
					b_ += x[j];
				} else {
					d_ -= x[j];
				}
				if (y[j] > 0){
					c_ += y[j];
				} else {
					e_ -= y[j];
				}
			}
		}
		if ((b_ & 1) == (d_ & 1) && (c_ & 1) == (e_ & 1)) dp[a][b][c][d][e][f][g] = (dp[a][b][c][d][e][f][g] + dfs(a + 1, b_ >> 1, c_ >> 1, d_ >> 1, e_ >> 1, trans(f, b_ & 1, bit), trans(g, c_ & 1, bit), n, m)) % mod;
	}
	return dp[a][b][c][d][e][f][g];
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++){
		scanf("%d %d", &x[i], &y[i]);
	}
	printf("%d", ((dfs(0, 0, 0, 0, 0, 0, 0, n, m) - 1) % mod + mod) % mod);
	return 0;
}
```

---

## 作者：漠寒 (赞：0)

## 分析

因为题目要求最终形状为一个凸包，所以你只要确定了要选哪些向量以及每个向量用几次，最终形成的那个多边形就固定了。

所以只需考虑最终式子是什么，得到 $\sum_{i=1}^nx_i=0$，$\sum_{i=1}^ny_i=0$。然后你画出图形后会发现横纵轴的最长扩展长度就是只为正的 $x_i$ 或 $y_i$ 之和，所以我们要求的就是正负 $x$ 值相等且都小于 $m$，$y$ 值亦然。然后发现 $n$ 很小，$x_i$ 和 $y_i$ 也很小，只有 $m$ 和我们求出来的每个向量选择次数会很大，所以我们考虑用数位 dp 去拆分每个向量的选择次数，在选择过程中维护两个坐标轴的正负值大小关系，和正值总值与 $m$ 的关系。

由低位向高位传递过程中维护以下几个值：$p$ 代表到第几位，$zx$ 代表低位的选择得到的值为正的 $x_i$ 总和向本位传递的值，$zy$ 同理，$hx$ 代表负的 $x_i$ 向本位传递的值，$hy$ 同理，$cx$ 代表低位上为正的 $x$ 值是否大于 $m$ 的低位，$cy$ 同理。每到一层时枚举当前层各个 $c_i$ 的子集，以 $s$ 表示，若 $s$ 二进制下第 $i$ 位为 $1$，则说明第 $i$ 个向量要选 $2^p$ 个。

在到达第 $30$ 位时，显然 $m$ 值是不可能有 $2^{30}$ 的，所以我们进行判断，首先那四个代表当前位值的数必须为 $0$。然后低位的为正的 $x$，$y$ 值必须同样小于等于 $m$，都满足的情况下我们才能返回 $1$，视为该情况可行。同时我们发现还有一个要求没处理，就是 $x$，$y$ 为正为负的值需相等，这样才能回到起点，因此在低位向高位传递时，必须正值负值该位同为 $1$ 或同为 $0$ 时才可以向下一层找答案。具体细节可以看代码。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
inline void read(int &res){
	res=0;
	int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
	res*=f;
}
int n,m;
int x[6],y[6];
int f[32][23][23][23][23][2][2];
int check(int x,int y,int z){//m当前位，比较值当前位 
	if(x^y)return x<y?1:0;//若不同，比较当前位的值 
	return z;//若相同，保留低位比较结果 
}
int dp(int p,int zx,int zy,int hx,int hy,int cx,int cy){//题解中说了含义了
	//cx为1代表x和大于m，cy同理 
	if(p==30)return (!zx&&!zy&&!hx&&!hy&&!cx&&!cy);
	if(~f[p][zx][zy][hx][hy][cx][cy])return f[p][zx][zy][hx][hy][cx][cy];
	int d=m>>p&1;//m的当前位，用于后面的比较 
	f[p][zx][zy][hx][hy][cx][cy]=0;
	for(int s=0;s<(1<<n);s++){
		int nwx=zx,nwy=zy,nwhx=hx,nwhy=hy;//存储当前以s的方式选择最终得到怎样的x值和，y值和 
		for(int i=1;i<=n;i++){
			if(s>>(i-1)&1){
				if(x[i]<0)nwhx-=x[i];
				else nwx+=x[i];
				if(y[i]<0)nwhy-=y[i];
				else nwy+=y[i];
			}
		}
		int dqx=nwx&1,dqy=nwy&1,dqhx=nwhx&1,dqhy=nwhy&1;//当前位正负xy值 
		if(dqx==dqhx&&dqy==dqhy){//若该位满足相等条件，向更高位寻找答案 
			f[p][zx][zy][hx][hy][cx][cy]=(f[p][zx][zy][hx][hy][cx][cy]+dp(p+1,nwx>>1,nwy>>1,nwhx>>1,nwhy>>1,check(d,dqx,cx),check(d,dqy,cy)))%mod;
		}
	}
	return f[p][zx][zy][hx][hy][cx][cy];
}
int main()
{
	read(n);read(m);
	for(int i=1;i<=n;i++){
		read(x[i]);read(y[i]);
	}
	memset(f,-1,sizeof(f));
	printf("%d",(dp(0,0,0,0,0,0,0)-1+mod)%mod);
}

```


---

