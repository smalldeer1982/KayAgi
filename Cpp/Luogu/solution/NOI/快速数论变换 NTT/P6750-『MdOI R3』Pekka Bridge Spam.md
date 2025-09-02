# 『MdOI R3』Pekka Bridge Spam

## 题目背景

JohnVictor 比较喜欢玩 Clash Royale。

他喜欢玩一套叫做 Pekka Bridge Spam 的卡组，然而这卡组被削弱了。现在他天梯已经掉了很多分了，不会玩了，只能在竞技场上给他的攻城锤安排地方了。

于是就有了这道题。

## 题目描述

JohnVictor 的皇室竞技场是一个 $2n \times 2m$（$2n$ 行，$2m$ 列）的方格表，他要在上面放 $n\times m$ 个 $1 \times 2$ 的攻城锤，使得任意两个攻城锤不相交。

然而攻城锤里面的野蛮人靠太近会打架，所以他要求任意一个 $2 \times 2$ 的正方形中有两个相邻的格子没有被任何攻城锤占有。

现在已经摆好了 $k$ 个攻城锤了，JohnVictor 想要知道有多少种方法能摆放这些攻城锤，注意，攻城锤两两之间没有区别。

由于这个答案实在是太大了，JohnVictor 只想知道这个答案对素数 $p$ 取模后的余数。**保证取模前的真实答案大于 $0$**。

为了避免玩过皇室的参赛者对题目理解产生问题，这里的攻城锤看做一个 $1 \times 2$ 的多米诺，翻转后也与自身一样。如果还是不理解可以参考样例。

**由于本题数据范围较大，使用 C++ 的选手可以使用以下代码来加快取模速度。**

代码出自 [KATCL](https://github.com/kth-competitive-programming/kactl/blob/master/content/various/FastMod.h) 。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull reduce(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
};
FastMod F(2);

int main() {
    int M = 1000000007; F = FastMod(M);
    ull x = 10ULL*M+3; 
    cout << x << " " << F.reduce(x) << "\n"; // 10000000073 3
}
```

使用方法：

假设当前程序中需要取模的数为 $p$，那么就在 `main` 函数开头处调用 `F = FastMod(p);`。

计算 $a\bmod p$ 的时候调用
`
F.reduce(a);
`，
返回值就是 $a\bmod p$ 的值。

## 说明/提示

【样例 1 解释】   
$9$ 种情况如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/0s4px806.png)

【样例 2 解释】   
我有一种绝妙的解释方法，可惜这里位置太小，我写不下。

【样例 3 解释】  
上图中第一行的第 $1,2$ 幅和第二行的第 $1,2$ 幅图就是要求的 $4$ 种情况。

更多样例请[到这里](https://www.luogu.com.cn/paste/b2ad2hoy)领取。

【数据范围】

本题采用捆绑测试，共有 $7$ 个子任务。

对于 $100\%$ 的数据，$1 \le n \le 9 \times 10^3$，$1 \le m \le 10^{18}$，$0 \le k \le  10^5$，$|x_{1i}-x_{2i}|+|y_{1i}-y_{2i}|=1$，$1 \le x_{1i},x_{2i} \le 2n$，$1 \le y_{1i},y_{2i} \le 2m$，$10^7\le p \le 10^9 + 9 $，**输入数据保证有解且 $p$ 为素数**。

|子任务编号|$n\leq$|$m\leq$|其他性质|分值|时间限制|
|:-:|:-:|:-:|:-:|:-:|:-:|
|1|$3$|$3$||$5$|$1.0s$|
|2|$10$|$10$|$k=0$|$10$|$1.0s$|
|3|$5 \times 10^3$|$5 \times 10^3$||$13$|$2.0s$|
|4|$80$|||$17$|$1.0s$|
|5|$2\times 10^3$||$p=998244353$|$20$|$3.0s$|
|6||||$35$|$3.0s$|
【温馨提示】

为了确保卡掉小常数的错解本题开大了数据范围，请注意常数因子对程序运行效率的影响。

## 样例 #1

### 输入

```
1 2 0 19260817```

### 输出

```
9```

## 样例 #2

### 输入

```
2 2 0 19260817```

### 输出

```
36```

## 样例 #3

### 输入

```
1 2 1 19260817
1 1 2 1```

### 输出

```
4```

## 样例 #4

### 输入

```
3 3 1 19260817
1 2 1 1```

### 输出

```
190```

# 题解

## 作者：Karry5307 (赞：42)

### 题意

略。

### 前言

作为验题人，被出题人甩了锅来写标程，在写标程的时候发现这题是真的难写。

所以在讲这个题的时候不仅有出题人的一些方法，也有自己的体会。

某些图是蒯的神仙 JV 的。

### 题解

首先将 $2n\times 2m$ 的方格划分成 $n\times m$ 个 $2\times 2$ 的小方格，注意到由于限制条件，每个 $2\times 2$ 方格里只能摆上一个攻城锤，然后整个图的摆法必须像这样：

![](https://i.loli.net/2020/08/11/o8OqQvDksiWaXPz.jpg)

接下来规定一个 $2\times 2$ 的方格的上下左右，就是这个方格内攻城锤的相对位置。

接下来考虑算这个摆法的方案数。考虑划两条分界线，一条分割上右和下左，另一条是上左和下右，如下图：

![](https://i.loli.net/2020/08/11/O1MYHgXEwQ4CtlN.jpg)

相当于我们只需要算出两条分界线的划法，将这两条分界线的方案数乘起来就可以得到总数。

接下来考虑划分上右和下左的方案数，另一条分界线如法炮制一遍就可以了。

这个分界线其实也可以理解为从左上角走到右下角的方案数，注意到有一些点因为钦定放的位置的限制是不能走的。左和下所在 $2\times 2$ 方格的左下角，右和上所在 $2\times 2$ 方格的右上角都是不能走到的。

接下来注意到 $m$ 很大，因此要一列一列来考虑。我们首先将可以走的点划分成一些矩形，然后考虑使用生成函数。

在矩形的内部，下一列方案数所对应的生成函数就是这一行的生成函数乘上 $\frac{1}{1-x}$。而在矩形的边界处就不一定了。

![](https://i.loli.net/2020/08/11/EBhlTOws4npCV2v.jpg)

在这种情况下，对于左边的矩形的右边界转移到右边矩形的左边界的时候，先将 $h_1\sim h_2-1$ 次项的系数清零，然后做一遍前缀和，再将 $l_1+1\sim l_2$ 次项的系数全部用 $l_1$ 次项的系数填充就好了。

这样，由于矩形最多有 $n$ 个，然后每一次操作是 $O(n)$ 的，所以总时间复杂度为 $O(n^2)$。

大体操作就讲到这里，接下来是代码细节。

首先一个需要注意的点就是到底哪些点是不能走的。还是以左下和右上的分界线为例子，注意到左下的限制和右上的限制其实是一个凸包，所以可以排个序然后单调栈维护一下。

接下来最麻烦的是矩形划分，这里可以考虑使用归并排序的思想。对于每个矩形，我们记录他的左右端点和上下边界。然后对于每个凸包上的点都会造成矩形的边界更新。

然后分 $3$ 种情况下一个左端点和下一个右端点的位置关系。这里有个小细节，就是对于每个上边界的改变来说位置的更新应该是对应的 $y$ 坐标减 $1$。

最后就是维护这个多项式，我们可以不用记录实际的多项式而是记录这个多项式乘上 $(1-x)^t$，然后剩下的就随便做就好了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef unsigned int ul;
typedef long long int li;
typedef unsigned long long int ull;
const ll MAXN=2e5+51;
struct Point{
	li x1,y1,x2,y2;
	ll dir;
};
struct Point2{
	li x,y;
	inline bool operator <(const Point2 &rhs)const
	{
		return x<rhs.x;
	}
	inline bool operator >(const Point2 &rhs)const
	{
		return x>rhs.x;
	}
};
struct Event{
	li y,lx,rx,lp,rp;
};
struct Rect{
	li u,d,ly,ry;
};
inline ll getR(ll MOD)
{
	ul v=MOD;
	return v*=2-MOD*v,v*=2-MOD*v,v*=2-MOD*v,v*=2-MOD*v,v;
}
Point pt[MAXN];
Point2 pt2l[MAXN],pt2r[MAXN],pt3l[MAXN],pt3r[MAXN];
Event ev[MAXN];
Rect rect[MAXN];
ll n,kk,MOD,R,R2;
li m,x,y,xt,yt;
inline ul reduce(ull x)
{
	ull y=ul(x>>32)-ul((ull(ul(x)*R)*MOD)>>32);
	return y+(MOD&-((ll)y<0));
}
struct ModInt{
	ul v;
	ModInt()
	{
		v=0;
	}
	ModInt(ul v)
	{
		this->v=reduce(ull(v)*R2);
	}
	ModInt(const ModInt &rhs)
	{
		this->v=rhs.v;
	}
	inline ModInt operator -()
	{
		ModInt res;
		res.v=(MOD&-(v!=0))-v;
		return res;
	}
	inline ModInt &operator +=(const ModInt &rhs)
	{
		return v+=rhs.v-MOD,v+=MOD&-(ll(v)<0),*this;
	}
	inline ModInt &operator -=(const ModInt &rhs)
	{
		return v-=rhs.v,v+=MOD&-(ll(v)<0),*this;
	}
	inline ModInt &operator *=(const ModInt &rhs)
	{
		return v=reduce(ull(v)*rhs.v),*this;
	}
	inline ll get()
	{
		return reduce(v);
	}
};
inline ModInt operator +(const ModInt &x,const ModInt &y)
{
	return ModInt(x)+=y;
}
inline ModInt operator -(const ModInt &x,const ModInt &y)
{
	return ModInt(x)-=y;
}
inline ModInt operator *(const ModInt &x,const ModInt &y)
{
	return ModInt(x)*=y;
}
ModInt r1,r2;
ModInt f[MAXN],inv[MAXN];
inline li read()
{
    register li num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ModInt get(ModInt *f,ll x,li kk)
{
	ModInt res(0);
	static ModInt p[MAXN];
	for(register int i=0;i<=x;i++)
	{
		p[i]=0;
	}
	p[0]=1,p[1]=(kk%=MOD);
	for(register int i=2;i<=x;i++)
	{
		p[i]=p[i-1]*(ModInt)(kk-1+i)*inv[i];
	}
	for(register int i=0;i<=x;i++)
	{
		res+=f[i]*p[x-i];
	}
	return res;
}
inline void change(ModInt *f,ll x,li kk,ModInt val)
{
	ModInt v=val-get(f,x,kk);
	ll sz=min((li)n,kk);
	static ModInt p[MAXN];
	for(register int i=0;i<=n;i++)
	{
		p[i]=0;
	}
	p[0]=1,kk%=MOD;
	for(register int i=1;i<=sz;i++)
	{
		p[i]=p[i-1]*ModInt(kk-i+1+MOD)*inv[i];
	}
	for(register int i=0;i<=sz;i++)
	{
		p[i]=i&1?p[i]:p[i];
	}
	for(register int i=0;i<=n;i++)
	{
		if(i+x<=n)
		{
			f[i+x]=f[i+x]+v*p[i];
			continue;
		}
		break;
	}
}
inline void clr(ModInt *f,ll x,li kk)
{
	static ModInt p[MAXN],q[MAXN],r[MAXN];
	ll sz=min((li)n,kk);
	for(register int i=0;i<=n;i++)
	{
		p[i]=q[i]=r[i]=0;
	}
	for(register int i=0;i<=sz;i++)
	{
		p[i]=get(f,i,kk);
	}
	q[0]=1,kk%=MOD;
	for(register int i=1;i<=sz;i++)
	{
		q[i]=q[i-1]*ModInt(kk-i+1)*inv[i];
	}
	for(register int i=0;i<=sz;i++)
	{
		q[i]=i&1?-q[i]:q[i];
	}
	for(register int i=0;i<=x;i++)
	{
		for(register int j=0;j<=sz;j++)
		{
			if(i+j<=n)
			{
				r[i+j]+=p[i]*q[j];
                continue;
			}
            break;
		}
	}
	for(register int i=0;i<=n;i++)
	{
		f[i]=f[i]-r[i];
	}
} 
inline void solve()
{
	ll lt=0,rt=0,lt3=0,rt3=0,lct=1,rct=1,rtx=1,u=0,d=0;
	ModInt val=0;
	for(register int i=1;i<=kk;i++)
	{
		if(pt[i].dir==1||pt[i].dir==2)
		{
			pt2l[++lt]=(Point2){(pt[i].x2+1)/2,(pt[i].y2+1)/2-1};
		}
		else
		{
			pt2r[++rt]=(Point2){(pt[i].x2+1)/2-1,(pt[i].y2+1)/2};
		}
	}
	sort(pt2l+1,pt2l+lt+1),sort(pt2r+1,pt2r+rt+1,greater<Point2>());
	pt3l[0].x=0,pt3l[0].y=-1,pt3r[0].x=0,pt3r[0].y=0x3f3f3f3f3f3f3f3f;
	for(register int i=1;i<=lt;i++)
	{
		if(pt2l[i].y>pt3l[lt3].y)
		{
			pt3l[++lt3]=pt2l[i];
		}
	}
	for(register int i=1;i<=rt;i++)
	{
		if(pt2r[i].y<pt3r[rt3].y)
		{
			pt3r[++rt3]=pt2r[i];
		}
	}
	for(register int i=1;i<=rt3;i++)
	{
		pt3r[i].y--;
	}
	reverse(pt3r+1,pt3r+rt3+1),u=0,d=lt3?pt3l[1].x-1:n;
	for(register int i=0;i<=d;i++)
	{
		f[i]=ModInt(1);
	}
	rect[1].u=u,rect[1].d=d,rect[1].ly=0;
	while(1)
	{
		if(lct>lt3||rct>rt3)
		{
			break;
		}
		if(pt3l[lct].y<pt3r[rct].y)
		{
			rect[rtx].ry=pt3l[lct].y,d=lct<lt3?pt3l[lct+1].x-1:n;
			rect[++rtx].u=u,rect[rtx].d=d,rect[rtx].ly=pt3l[lct++].y+1;
		}
		if(pt3l[lct].y>pt3r[rct].y)
		{
			rect[rtx].ry=pt3r[rct].y,u=pt3r[rct].x+1;
			rect[++rtx].u=u,rect[rtx].d=d,rect[rtx].ly=pt3r[rct++].y+1;
		}
		if(pt3l[lct].y==pt3r[rct].y)
		{
			rect[rtx].ry=pt3l[lct].y,u=pt3r[rct].x+1;
			d=lct<lt3?pt3l[lct+1].x-1:n;
			rect[++rtx].u=u,rect[rtx].d=d,rect[rtx].ly=pt3l[lct++].y+1,rct++;
		}
	}
	for(register int i=lct;i<=lt3;i++)
	{
		rect[rtx].ry=pt3l[i].y,rect[++rtx].u=u;
		rect[rtx].d=i<lt3?pt3l[i+1].x-1:n,rect[rtx].ly=pt3l[i].y+1;
	}
	for(register int i=rct;i<=rt3;i++)
	{
		rect[rtx].ry=pt3r[i].y,rect[++rtx].u=pt3r[i].x+1,rect[rtx].d=d;
		rect[rtx].ly=pt3r[i].y+1;
	}
	rect[rtx].ry=m;
	for(register int i=2;i<=rtx;i++)
	{
		clr(f,rect[i].u-1,rect[i-1].ry);
        val=get(f,rect[i-1].d,rect[i].ly);
		for(register int j=rect[i-1].d+1;j<=rect[i].d;j++)
		{
			change(f,j,rect[i].ly,val);
		}
	}
}
int main()
{
	n=read(),m=read(),kk=read(),MOD=read();
	R=getR(MOD),R2=-ull(MOD)%MOD;
	for(register int i=1;i<=kk;i++)
	{
		x=read(),y=read(),xt=read(),yt=read();
		if(x==xt&&y>yt)
		{
			swap(y,yt);
		}
		if(y==yt&&x>xt)
		{
			swap(x,xt);
		}
		pt[i]=(Point){x,y,xt,yt};
		if(y==yt&&x+1==xt)
		{
			pt[i].dir=1+2*((yt&1)^1);
		}
		if(x==xt&&y+1==yt)
		{
			pt[i].dir=2+2*(xt&1);
		}
	}
	inv[1]=ModInt(1);
	for(register int i=2;i<=n;i++)
	{
		inv[i]=-ModInt(MOD/i)*inv[MOD%i];
	}
	solve(),r1=get(f,n,m);
	for(register int i=1;i<=kk;i++)
	{
		pt[i].y1=2*m-pt[i].y1+1,pt[i].y2=2*m-pt[i].y2+1;
		if(pt[i].dir&1)
		{
			pt[i].dir^=2;
		}
		else
		{
			swap(pt[i].y1,pt[i].y2);
		} 
	}
	solve(),r2=get(f,n,m),printf("%d\n",(r1*r2).get());
}
```

---

## 作者：JohnVictor (赞：19)

放上官方题解，自认为这题还是不错的，主要是对于结构的观察而不是推式子。

**性质 1**

将这个图分成 $nm$ 个 $2 \times 2$ 个正方形，那么每个正方形中恰好有一个 $1 \times 2$。

证明：称 $S$ 为所有被 $1 \times 2$ 覆盖的格子的集合，那么 $|S|=2mn$。每个这样的 $2 \times 2$ 中至多有两个格子属于 $S$。

然而所有 $4mn$ 个格子中，恰好有一半的格子属于 $S$。所以每个 $2 \times 2$ 中恰好 $2$ 个，构成一个 $1 \times 2$。

从左上角的格子开始依次考虑，可以证明这些就是所有的攻城锤。

-----

根据这个性质，称一个上述的分割中的 $2 \times 2$ 的方格为 **上，下，左，右** 之一，取决于 $1 \times 2$ 在它中的位置。

**性质 2**

一个 **上** 的方格的上方的方格也是 **上** 的，右边是 **上** 或者 **右**，左边是 **上** 或者 **左**。其他四种方格类似。

证明显然。

那么，结合以上两条性质，这个图大概是长这样的：

![1.jpg](https://i.loli.net/2020/08/11/o8OqQvDksiWaXPz.jpg)

注意到，如果现在就要推式子等方法计算的话，这个生成函数肯定是二元的形式，难以计算，可以用矩阵做到 $\Theta(n^6 \log m)$ 的复杂度，不详细说明。

这一步需要极高的技巧，相当于因式分解了那个难以刻画的二元生成函数。

用两条路径刻画这个图，一条从左上到右下，一条从左下到右上：

![1.jpg](https://i.loli.net/2020/08/11/O1MYHgXEwQ4CtlN.jpg)

那么分成的四块就恰好是 **上，下，左，右**。

现在这题变成：左上走到右下，每次向右或者向下，有些地方不能走，求方法数。

不能走是因为有 $k$ 个指定的位置，那么这些会限制这条路径。

当然，现在还没有明确说明哪些地方不能走，这里说清楚，下面的例子主要考虑左上到右下的路径。

限制就是，所有 **下** 的方格和所有 **左** 的方格和剩下两种方格被这条路径分成两半，也就是，如果把下和左看成 $1$，其余看成 $2$，那么这条路径将 $1$ 与 $2$ 分成两个部分。

现在让这个方格表左下为 $(0,0)$，右上为  $(m,n)$。如果一个 $1$ 类方格的左下角为 $(p,q)$，那么这条路径不能经过任何 $x\le p$ 并且 $y \le q$ 的点，对于 $2$ 类方格类似。下面的图表明了一种可能的能走与不能走的位置。

![1.jpg](https://i.loli.net/2020/08/11/FdgB7q1iZrxyXfR.jpg)

这里，红色的点表示不能走的点，绿色的线是一条合法的路径，黄色的线把能走到的地方分成了几个矩形。

矩形未必要有长与宽（可以为 $0$），可能用 $s\times t$ 的点阵（$ s,t \ge 1$）来形容更加合适，下面 **点阵** 和 **矩形** 都代表这个意思。

这些矩形是有特殊要求的，不难发现不能走的地方构成了两个简单多边形，这两个多边形的边有水平的和竖直的，用竖直的边分割这个网格图得到了图中所示的矩形，后面的方法会说明为什么要这么分，可以通过上面的图更好的理解这些矩形是怎么刻画出来的。

当然，刻画这些矩形需要将所有放好的块排序并且利用单调栈维护，细节比较多，这里不细说。

考虑最基本的 `dp`  以及一个没有限制的图，令 $dp[i][j]$ 为到 $(i,j)$ 的合法路径数，那么 $dp[i][j]=dp[i][j-1]+dp[i-1][j]$。

这个式子可以化成 $dp[i][j]=\sum_{k=1}^jdp[i-1][k]$，也就是一个前缀和的形式。

注意到，如果按照上面的方式将合法区域划分为矩形，那么每个长为 $t$ 的点阵就相当于做 $t-1$ 次前缀和。

我们用到生成函数的知识，如果假设第 $i$ 列（横坐标为 $i$ 的所有点）从上到下的 $dp[i][j](0 \le j \le n)$ 构成生成函数 $F_i(x)=\sum dp[i][j]x^j$，其中 $0 \le i \le m$，我们有递推式：

$F_{i+1}(x)=\frac{F_i(x)}{1-x}$，如果第 $i$ 列与第 $i+1$ 列在同一个矩形内；

如果不在同一个矩形内，一定在相邻两个矩形内，设这两个矩形的上下高度分别为 $h_1,l_1,h_2,l_2$，如图：

![1.jpg](https://i.loli.net/2020/08/11/EBhlTOws4npCV2v.jpg)

那么，这个生成函数，就是先保留原来 $F_i(x)$ 在 $h_2$ 到 $l_1$ 次项的系数，然后对其做前缀和，为 $G_{i+1}(x)$，然后 $F_{i+1}(x)$ 的系数，不大于 $l_1$ 次项的与 $G_{i+1}(x)$ 相同，$l_1$ 到 $l_2$ 次项用 $G_{i+1}(x)$ 的 $l_1$ 次项系数填充。

这个比较难以用式子进行刻画，所以只能通过文字进行解释。

我们并不需要求出所有的 $F_i(x)$，因为需要的甚至只是 $F_m(x)$ 的一项系数，所以我们求出所有矩形两条宽所在列代表的多项式，相邻多项式之间的转移可以用多项式前缀和以及 $NTT$ 优化就可以在 $n \log n$ 的时间内完成，由于矩形一共 $\Theta(n)$ 个那么这是 $n^2 \log n$ 的，但是这不够优秀，瓶颈在求前缀和上。

如果不用做前缀和，剩下的操作甚至是 $\Theta(n)$ 的。我们考虑一个稍微一般一点的问题：

维护一个多项式，支持三种操作：

（1）做若干次前缀和；（2）查一项系数；（3）加上一个单项式。

（在同一个矩形内的转移规约为（1）操作，相邻矩形转移可以查询 $h_1$ 到 $h_2$ 次项所有系数并依次减掉对应的单项式，然后再做一次前缀和，然后查询 $l_1$ 次项的系数，最后在依次查询 $l_1+1$ 到 $l_2$ 次项的系数，把他们加上与 $l_1$ 次项的系数的差）

此时解法几乎呼之欲出了：

维护一个多项式 $Q(x)$ 与一个整数 $t\ge 0$，我们真实的多项式是 $\dfrac{Q(x)}{(1-x)^t}$，那么对于（1）操作直接修改 $t$，对于 $2$ 操作可以 $O(n)$ 求出卷积的一项，对于 $3$ 操作将这个单项式乘以 $(1-x)^t$ 后加到 $Q(x)$ 上即可，时间复杂度 $O(n^2)$。

作为一道连 `FFT` 都不用的多项式题，快来为良心的出题人点赞吧！

std 供食用，感谢 Kubic,ix35,Karry5307 的付出。

std 进行适当卡常，其实只加上取模优化就能 AC。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 9005
#define M 100005
#define LIM 1000000
#define ull unsigned long long
#define ulll __uint128_t 
#define mod FM.reduce
#define gc() (P1==P2 && (P2=(P1=buf)+fread(buf,1,LIM,stdin),P1==P2)?EOF:*P1++)
char buf[LIM],*P1,*P2; 
int n,c,p,cnt1,cnt2,ans,inv[N],st1[M],st2[M],L[M],R[M];
ull m,d,ds[M],vl[N],z[N];struct Node {int x,v;ull y;}a1[M],a2[M],b1[M],b2[M];
ull rd()
{
	ull res=0;char c=0;while(!isdigit(c)) c=gc();
	while(isdigit(c)) res=(res<<1)+(res<<3)+(c&15),c=gc();return res;
}
struct FastMod
{
	ull b,m;FastMod(ull b=2):b(b),m((ull)(((ulll)(1)<<64)/b)) {}
    ull reduce(ull a) {ull q=(ull)(((ulll)(m)*a)>>64),r=a-q*b;return r>=b?r-b:r;}
}FM;
bool cmp1(Node x,Node y) {return x.y==y.y?x.x<y.x:x.y<y.y;}
bool cmp2(Node x,Node y) {return x.y==y.y?x.x>y.x:x.y<y.y;}
int qPt(int x)
{
	int C=1;ull res=0;d=mod(d);
	for(int i=0;i<=x;++i)
	{
		if(i) C=mod(mod((d+i-1)*C)*inv[i]);z[x-i]=mod(z[x-i]);
		res+=mod(1ull*C*z[x-i]);if(res>=9e18) res=mod(res);
	}return mod(res);
}
void upd(int l,int r,int v)
{
	int C=1;d=mod(d);for(int i=l;i<=r;++i) vl[i]=0;
	for(int i=0;i<=r;++i)
	{
		if(i) C=mod(mod((d+i-1)*C)*inv[i]);
		for(int j=i<l?l:i;j<=r;++j)
		{
			if(z[j-i]>=p) z[j-i]=mod(z[j-i]);
			vl[j]+=mod(1ull*C*z[j-i]);if(vl[j]>=9e18) vl[j]=mod(vl[j]);
		}
	}C=1;for(int i=l;i<=r;++i) vl[i]=mod(vl[i]),vl[i]=v<vl[i]?v-vl[i]+p:v-vl[i];
	for(int i=0,fl=1;i+l<=n && i<=d;++i,fl^=1)
	{
		if(i) C=mod(mod((d+p+1-i)*C)*inv[i]);
		for(int j=l;j<=r && i+j<=n;++j)
		{
			z[i+j]+=fl?mod(1ull*C*vl[j]):p-mod(1ull*C*vl[j]);
			if(z[i+j]>=9e18) z[i+j]=mod(z[i+j]);
		}
	}
}
void slv(Node a[])
{
	cnt1=cnt2=d=st1[0]=st2[0]=ds[0]=0;for(int i=0;i<=n;++i) z[i]=0;
	b1[++cnt1]=(Node) {-1,0,0};b2[++cnt2]=(Node) {n+1,0,m};
	for(int i=1;i<=c;++i)
		if(a[i].v==1 || a[i].v==4) b1[++cnt1]=a[i],++b1[cnt1].y;
		else b2[++cnt2]=a[i],++b2[cnt2].x;
	sort(b1+1,b1+cnt1+1,cmp1);sort(b2+1,b2+cnt2+1,cmp2);
	for(int i=cnt1;i>=1;--i)
	{
		while(st1[0] && b1[i].x>=b1[st1[st1[0]]].x) --st1[0];
		st1[++st1[0]]=i;
	}
	for(int i=1;i<=cnt2;++i)
	{
		while(st2[0] && b2[i].x<=b2[st2[st2[0]]].x) --st2[0];
		st2[++st2[0]]=i;
	}for(int i=1;i<=st1[0];++i) ds[++ds[0]]=b1[st1[i]].y;
	for(int i=1;i<=st2[0];++i) if(b2[st2[i]].y<m) ds[++ds[0]]=b2[st2[i]].y+1;
	ds[++ds[0]]=0;ds[++ds[0]]=m;
	sort(ds+1,ds+ds[0]+1);ds[0]=unique(ds+1,ds+ds[0]+1)-ds-1;
	for(int i=1,t1=st1[0],t2=1,t=0;i<=ds[0];++i)
	{
		while(t1 && b1[st1[t1]].y<=ds[i]) --t1;L[i]=b1[st1[t1+1]].x+1;
		while(t2<=st2[0] && b2[st2[t2]].y<ds[i]) ++t2;R[i]=b2[st2[t2]].x-1;
		if(!ds[i]) {for(int j=L[i];j<=R[i];++j) z[j]=1;continue;}
		d+=ds[i]-ds[i-1]-1;upd(L[i-1],L[i]-1,0);++d;
		if(R[i-1]<R[i]) t=qPt(R[i-1]);upd(R[i-1]+1,R[i],t);
	}
}
int main()
{
	n=rd();m=rd();c=rd();p=rd();FM=FastMod(p);
	for(int i=1;i<=n;++i) inv[i]=i==1?1:mod(1ull*inv[p%i]*(p-p/i));
	for(int i=1,x1,x2;i<=c;++i)
	{
		ull y1,y2;x1=rd();y1=rd();x2=rd();y2=rd();
		a1[i]=(Node) {x1-1>>1,x1==x2?(x1&1?1:3):(y1&1?2:4),y1-1>>1};
		x1=(n<<1)-x1+1;x2=(n<<1)-x2+1;
		a2[i]=(Node) {x1-1>>1,x1==x2?(x1&1?1:3):(y1&1?2:4),y1-1>>1};
	}slv(a1);ans=qPt(n);slv(a2);printf("%llu\n",mod(1ull*ans*qPt(n)));
    puts("I would not copy!");return 0;	
}

---

