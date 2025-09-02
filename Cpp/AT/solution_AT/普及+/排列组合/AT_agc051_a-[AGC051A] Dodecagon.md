# [AGC051A] Dodecagon

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc051/tasks/agc051_a

すぬけ君は、正方形のタイルと正三角形のタイルを無限枚持っています。タイルの辺の長さは全て $ 1 $ です。 これらを使って、辺の長さが $ d $ の正 $ 12 $ 角形を作る方法は何通りあるでしょうか。 この答えを $ 998,244,353 $ で割った余りを計算してください。

厳密に述べると、

- タイルを使う枚数に制限はありません。
- 使ったタイルのうち、どの $ 2 $ 枚も重なっていてはいけません。
- 使ったタイルが覆う領域の和集合は、穴のない正 $ 12 $ 角形でなければなりません。
- 二つの作り方について、一方に回転と平行移動を施す (鏡映は不可) ことでもう一方を得られる、すなわち一方における各タイルがもう一方における同種のタイルと完全に一致するとき、これらの作り方を同一とみなします。

## 说明/提示

### 制約

- $ 1\ \leq\ d\ \leq\ 10^6 $
- 入力中の全ての値は整数である。

### Sample Explanation 1

唯一の作り方を以下の図に示します。 !\[\](https://img.atcoder.jp/agc051/dad0de5f2e5c47119aa1a0da8ed28808.png)

## 样例 #1

### 输入

```
1```

### 输出

```
1```

# 题解

## 作者：墨笙_Mooos (赞：5)

## 翻译

Snuke 有无限个边长为 $1$ 的正方形和正三角形瓷砖。有多少种不同的方法可以用这些瓷砖组成一个边长为 $d$ 的正十二边形？请计算方案数并对 $998\ 244\ 353$ 取模。

具体地说：
* Snuke 可以使用任意数量的瓷砖。
* 方案中没有两块瓷砖是重叠的。
* 瓷砖所填充的区域必须是一个无孔的正十二边形。
* 如果我们可以将一种方案通过旋转和平移得到另一种方案，则这两个方案是相同的。

输入共一行，一个正整数 $d$，表示正十二边形的边长。

输出共一行，一个正整数，表示方案数对 $998\ 244\ 353$ 取模后的结果。

对于 $100\ \%$ 的数据，$1 \le d \le 10^{6}$。

## 思路

是一道思维好题。

尝试从外往内填充这个正十二边形。我们可以发现，正十二边形的顶角大小为 $150\degree$，正好是 $60\degree + 90\degree$，因此一个角就只能由一个正三角形和一个正方形填充，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/4vxbi3ak.png)

这时，如果我们想要在正方形右侧填充正三角形，必定会留出一个 $30\degree$ 的缝隙，所以正方形右侧只能填充正方形。同样的，如果在正三角形左侧填充正方形，也会留出一个 $30\degree$ 的缝隙，所以正三角形左侧仍然是正三角形。

因为每个角都是由正三角形和正方形拼接而成，所以填充正三角形的边相邻的两边都是填充正方形的边，填充正方形的边相邻的两边都是填充正三角形的边。

这样，只要确定一个角，就能确定最外围一圈的填充方案。

考虑最外围一圈填充后，内部的图形要如何填充。

![](https://cdn.luogu.com.cn/upload/image_hosting/i9hmpsbw.png)

如上图所示，在内部的十二边形里，所有在外层填充了正三角形的边，长度都减短了 $1$，而填充了正方形的边长度不变。

此时同样考虑一个角，由正方形和正三角形填充，所以填充这个内部的十二边形外围一圈的方案也可以由一个角确定。

同样的，对于第二次填充后内部的图形，用正三角形填充的边边长长度仍然会减短 $1$，用正方形填充的边长长度仍然不变。

![](https://cdn.luogu.com.cn/upload/image_hosting/avmh2yg5.png)

哎呀！里面只剩下一个正六边形了怎么办！

这时候，还是考虑一个角。正六边形的一个角是 $120\degree$，想用正方形填充？那就必定会剩下一个 $30\degree$ 的角，所以这个正六边形就只能用正三角形填充，而且有且只有一种方案。（想一想，为什么？）

---

综上，我们可以把十二条边分为两组，$A = \left\{e_1, e_3, e_5, e_7, e_9, e_{11} \right\}$，$B = \left\{e_2, e_4, e_6, e_8, e_{10}, e_{12}\right\}$，其中 $e_i$ 表示逆时针方向第 $i$ 条边。

每填充一层，可以选择 $A$ 或者 $B$ 中所有边上填正三角形，其余边填正方形。或者说，可以选择 $A$ 或者 $B$ 中所有边长度减短 $1$，其他边不变，直到 $A$ 和 $B$ 中的边边长都为 $0$。

于是我们可以建立二维坐标系，$x$ 轴为 $A$ 中边的长度，$y$ 轴为 $B$ 中边的长度，把问题抽象为仅允许向左、向下走时从 $(d, d)$ 走到 $(0, 0)$ 的方案数。

（即将向左走视为 $A$ 中的边长度减 $1$，向下走视为 $B$ 中的边长度减 $1$，而走到边界时，就是上面提到的六边形的情况）

![](https://cdn.luogu.com.cn/upload/image_hosting/9mz4rz8y.png)

如上图，对应了 $d=10$ 的一种方案。

由于一共有 $2d$ 步，其中 $d$ 步是向左的，所以总方案数为 $C_{2d}^d$。

但是因为旋转相同的限制，所以 $A$ 和 $B$ 是可以互换的，也就是说，在二维坐标系里，关于 $y = x$ 对称的路线是等价的！

所以最后的答案是 $\dfrac{1}{2}C^{d}_{2d}$！

## 代码

```cpp
inline ll fstpow (ll a, ll b, ll p = mod)
{
	a %= p; ll Ans = 1;
	while (b)
	{
		if (b & 1) Ans = Ans * a % p;
		a = a * a % p, b >>= 1;
	}
	return Ans;
}
inline ll GetInv (ll x) { return fstpow (x, mod - 2); }
int main ()
{
	cin >> d, Fac = Ans = 1;
	For (i, 1, d) Fac = Fac * i % mod;
	Inv = GetInv (Fac), Fac = 1;
	For (i, d + 1, d + d) Fac = Fac * i % mod;
	Ans = Ans * Fac % mod * Inv % mod;
	cout << Ans * GetInv (2) % mod << endl;
	return 0;
}
```

---

## 作者：MurataHimeko (赞：2)

有点逆天的题。

观察到十二边形的一个内角大小为 $150^{\circ}=60^{\circ}+90^{\circ}$，所以最外一圈一定是一段正方形接一段三角形。

而且一段三角形，如果外部的边长为 $d$，那么内部的边长为 $d-1$。类似于一个上底边比下底边长的等腰梯形。

如果是一段正方形，则外部内部的边长相同。

然后不会做了。

尝试画一下 $d=2$ 的图。

![1](https://cdn.luogu.com.cn/upload/image_hosting/q9rqrpm1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

![2](https://cdn.luogu.com.cn/upload/image_hosting/qntgv2gf.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

![3](https://cdn.luogu.com.cn/upload/image_hosting/zg0tkzr5.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

为了身心健康就只画了一部分。


根据最外层的贴法分类。

设外部一段正方形的底边长为 $d_0$，一段三角形的底边长为 $d_1$。

初始有 $d_0=d,d_1=d-1$。

前两种方案，都属于是内部三角形接外部正方形和内部正方形接外部三角形。


那么有 $d_0' = d_1-1, d_1' = d_0$。

对于第三种方案， 是内部三角形接外部三角形和内部正方形接外部正方形。

那么有 $d_0' = d_0, d_1' = d_1-1$。

同时观察到，如果 $d_0=d_1$，那么此时有两种贴法。相当于将内部的十二边形“旋转”了一下，可以参考前两种方案。

并且，如果 $d_0=0$。那么此时内部为正六边形（参考第三种方案）。因为  $120^{\circ}=60^{\circ}+60^{\circ}$，所以此时只能不断放三角形，所以贴一个正六边形的方案为 $1$。


然后你发现，你其实并不关心到底是怎么贴的，你只关心内部三角形接上的外部边长是多少。

然后我们可以写出一个递推了：

设 $f_{i,j}$ 表示，外部边长较大的一段为 $i$，较小的一段为 $j$ 的方案
数。

那么有：

$f_{0,0}=1$

$i>j: f_{i,j} = f_{i-1,j}+f_{i,j-1}$

$i=j:f_{i,i} = f_{i,i-1}\times 2$


你发现这个形式很像求从 $(0,0)$ 走到 $(d, d-1)$ 且总在 $y=x$ 下方的路径条数。

同时你发现，只有当 $i=j$ 时，才会越过 $y=x$。如果将点沿着 $y=x$ 翻转，那么 $f_{i,i}=f_{i,i-1} \times 2$ 其实就相当于 $f_{i,i} = f_{i,i-1}+f_{i-1,i}$。那么我们就根本不用管会不会越过 $y=x$，直接算 $(0,0)$ 到 $(d,d-1)$ 的路径条数即可。

那么答案就是 $\binom{2d-1}{d}$。



---

## 作者：_Life_ (赞：2)

### 题意
使用边长为 $1$ 的正三角形和正四边形平铺边长为 $d$ 的正十二边形，求方案数量，对 $998244353$ 取模。

如果两种方案经过旋转后相同，那它们被认为是同一种方案。

$1\leq d \leq 10^6$

### 题解

图片拿 Geogebra 画的，去掉了坐标轴网格显示和标签显示。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/snpgyalg.png)

图为一个边长为 $2$ 的正十二边形。

---

按照正常想法，我们考虑从外到内一圈一圈填充。

![](https://cdn.luogu.com.cn/upload/image_hosting/pyigwc4a.png)

手玩一下可以发现每一圈一定有 $6$ 条正三角形组成的边和 $6$ 条正四边形组成的边，而且这两种边交错排布。

为什么呢？因为内角为 $150\degree$，只能凑成 $150\degree=90\degree+60\degree$，所以转角必定由一个正三角形和正四边形组成。

能和正三角形组成一条边的只有正三角形，能和正四边形组成一条边的只有正四边形。

所以每经过一个转角，就会发生一次正三角形和正四边形的切换。这说明了为什么正三角形边和正四边形边轮换排布。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/th0mshuo.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/q03p5ezd.png)

再手玩一下，发现一个重要性质：每条正三角形组成的边可以使十二边形对应的边边长减少 $1$，每条正四边形组成的边不会使边长改变。

考虑怎样才算拼完：每条边的边长都变成 $0$。

每拼一圈的边，都能使一半的边边长减少 $1$，而边长为 $d$，所以答案为 $C_{2d}^d$。

> 如果两种方案经过旋转后相同，那它们被认为是同一种方案。

所以实际答案是原来的一半，$\dfrac{C_{2d}^d}{2}$。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/wivlkt3t.png)

放张图，拼好之后的图形还是很好看的。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
using namespace std;
typedef pair<int,int> pii;
void setIn(string s){freopen(s.c_str(),"r",stdin);}
void setOu(string s){freopen(s.c_str(),"w",stdout);}
void setIO(string s){setIn(s+".in"),setOu(s+".out");}
template<class T>void chkmax(T &a,T b){a=max(a,b);}
template<class T>void chkmin(T &a,T b){a=min(a,b);}
template<class T>T read(T &x)
{
	x=0;T f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*=f;
}
template<class T,class ...L>void read(T &x,L &...l){read(x),read(l...);}
template<class T>void write(T x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9){write(x/10);}putchar(x%10+'0');
}
template<class T>void write(T x,char c){write(x),putchar(c);}
int d,fac[2000005],inv[2000005];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;a=a*a%mod,b>>=1)
		if(b&1)ans=ans*a%mod;
	return ans;
}
int C(int n,int m)
{
	if(n<m)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main()
{
	fac[0]=1;
	rep(i,1,2000000)fac[i]=fac[i-1]*i%mod;
	inv[2000000]=qpow(fac[2000000],mod-2);
	per(i,2000000,1)inv[i-1]=inv[i]*i%mod;
	read(d);
	write(C(2*d,d)*qpow(2,mod-2)%mod);
}
```

---

