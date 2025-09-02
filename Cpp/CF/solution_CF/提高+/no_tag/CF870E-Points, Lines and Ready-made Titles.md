# Points, Lines and Ready-made Titles

## 题目描述

You are given $ n $ distinct points on a plane with integral coordinates. For each point you can either draw a vertical line through it, draw a horizontal line through it, or do nothing.

You consider several coinciding straight lines as a single one. How many distinct pictures you can get? Print the answer modulo $ 10^{9}+7 $ .

## 说明/提示

In the first example there are two vertical and two horizontal lines passing through the points. You can get pictures with any subset of these lines. For example, you can get the picture containing all four lines in two ways (each segment represents a line containing it).

 The first way: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870E/16d9107c00bae4cf5f33754cdc1989ed71bbf8ba.png) The second way: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870E/cc0bfe7f0aace68a3f05623608cb42281913494e.png)In the second example you can work with two points independently. The number of pictures is $ 3^{2}=9 $ .

## 样例 #1

### 输入

```
4
1 1
1 2
2 1
2 2
```

### 输出

```
16
```

## 样例 #2

### 输入

```
2
-1 -1
0 1
```

### 输出

```
9
```

# 题解

## 作者：Code_AC (赞：5)

[更好的阅读体验](https://www.cnblogs.com/yhx-error/p/16757011.html)

## 题目大意

给你平面上 $n(1\leqslant n \leqslant 10^5)$ 个点，给出他们的坐标 $x_i,y_i(-10^9\leqslant x_i,y_i \leqslant 10^9)$。

对于每个点有三种操作：不进行任何操作、过这个点作一条平行于 $x$ 轴的直线、过这个点作一条平行于 $y$ 轴的直线。

问能够形成多少种不同的平面。

## 思路分析

个人认为这道题思维难度还是比较大的，比较难想。

首先很显然的一点，因为每个有三种状态，那么答案的上限就是 $3^n$，即每一行每一列仅有不超过一个点，没有任何两个点在同一行或同一列。

然后我们有一个比较清奇的思路，就是将每个点的 $x,y$ 坐标拆成一个 $x$ 轴上的点和一个 $y$ 轴上的点，每个 $x$ 轴上的点要么不操作，要么画平行于 $y$ 轴的线，每个 $y$ 轴上的点要么不操作，要么画平行于 $x$ 轴的线，那么这就形成了一个天然的二分图，然后将点对应的的 $x,y$ 坐标连边。

举个例子：

$(1,2),(1,4),(3,2),(3,4)$ 四个点，那么图建出来就是这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/n4ubiqp8.png)

左边表示 $x$ 坐标，右边表示 $y$ 坐标。

然后我们以这种方式建完图后，会发现形成了许多连通块，那么根据乘法原理，我们只需要统计每个连同块内的的答案，再累乘起来就行了。

现在我们看一看如何求每个连通块内的答案，先放结论：

设 $tot$ 为连通块内点的数量，$cnt$ 为边的数量，那么有
$$
ans=
\begin{cases}2^{tot}&(cnt\geqslant tot)\\2^{tot}-1&(cnt+1=tot)\end{cases}
$$

然后我们来分析一下结论中的两种情况：

- $cnt+1=tot$

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/t0ubgkud.png)

理论上来说，每个点有两种情况，那么答案应该是 $2^{tot}$，但仔细想一下，我们是把一个点拆开来了，那么就不可能左边的点选择画竖线的同时右边的点画横线，所以要减一。

那么我们可以换个思考方式，因为我们图里的每一条边代表的是一个平面直角坐标系内的坐标，所以我们可以将每一个点的方案放到它所连接的边上，那么这里不管我们 $1$ 点或 $2$ 点放在边上，都有一个点无法放上边，那么就要减一。

![](https://cdn.luogu.com.cn/upload/image_hosting/gn0vq98c.png)

- $cnt \geqslant tot$

同上面例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/n4ubiqp8.png)

这种形成环的情况下，很显然每个点都能够成功的放到一条边上去，并且不会重边，所以答案就是 $2^{tot}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/6efo3o7l.png)

代码实现只需要用并查集这种及其基础的知识点，二分图只是用在思想上，代码就不放了，很简单。

---

## 作者：HansLimon (赞：3)

先放个 AC 记录，至于为什么不是洛谷记录，那是因为洛谷交不上去。

~~好吧，在我写完这篇题解后洛谷交上去了~~

![qwq](https://cdn.luogu.com.cn/upload/image_hosting/gz6htddw.png)

顺带一提，这道题不应该只有黄色。下面进入正题：

# 分析
首先，题目中的“垂直线”指的是竖直方向的线。

那么显然，n 个点的最大方案数为 $3^n$，并且当且仅当所有点的垂直线或水平线不相重合取最大值。为了方便，我们称有垂直线或水平线相重合的点对为“会互相影响的点对”，并用 $(x, y)$ 表示，而没有相重合的点对称为“互相无关的点对”，并用 $[x, y]$表示。

继续，可以很容易地发现：$(x, y)$ 并不会影响其他与之互相无关的点对(即 $[x, z]$ 或 $[y, z]$)。自然而然能想到将 $(x, y)$ 与这样的点对分开处理。~~说白了就并查集~~

(提示到这里就结束了，下面是详解)

------------


很明显，能互相影响的点可以不仅仅成对，方便起见，用大写字母和“ ' ”表示。即 $(x, y)$ 和 $(y, z)$ 同属点集 $A$。我们分别称这些点集为 $A'$，$B'$，$C'$。相反的，用小写字母和“ ' ”表示互相无关的点对的集合。需要注意的是，$(x, y)$ 和 $[y, z]$ 和 $[x, z]$也可称作互相无关的点对的集合。

## 分析 —— A
我们现在找样例一开刀。~~主要是因为懒~~

从左上角按顺时针给这些点命名为A,B,C,D，称 $A' = \{A, B, C, D\}$。$A'$ 中有4条边，4个点。

**划重点：**

由于判定的标准是**是否有相重合的边**(这里的 边 指一个点的垂直线和水平线)，考虑**维护边**。将这些边视为点(避免混淆，用 $a, b, c, d$ 表示)，那么样例二中，每个点向相邻的两点连了一条边。这样的新图 $G'$ 是一个四元环，它的方案数为16。

------------

在草稿纸上自己弄几个不同的互相影响的点集后，可以发现：

对于任意一个由 $a, b, c, d...$ 组成的图 $G'$，若 $G'$ 有环，那么环的个数即 $G'$ 中互相影响的点集的个数。

很明显，它们(指这些点集)能够贡献的方案数为 $2^n$( $n$ 为原始点集中边的个数)。

补充：帮助理解，样例一的16是由 $2^4$ 得到的。

## 分析 —— a
由上面的经验，发现：

对于任意一个由 $a, b, c, d...$ 组成的图 $G'$，若 $G'$ 无环，甚至存在不连通的情况，那么原始图 $G$ 中任意的点对互相无关。

既然互相无关，那么其对答案的贡献就是 $2^n - 1$ 或 $3^n$。

为什么有两种表达方式呢？因为前面式子的 $n$ 表示新图 $G'$ 中的点数，也就是原图的边数。而后面式子的 $n$ 表示原图 $G$ 中的点数。在这里为了方便，我个人选择了前面的那种。

# 代码

最后的答案显然是两种分析的贡献之积啦，毕竟互相无关。

如果想自己写的话，留些提示：

- 用 map 对不同坐标的线建映射(因为两种线斜率确定，只需要一个点即可完全确定)
- 用并查集来表示在 $G'$ 中是否存在环
- 避免计算时爆掉，用快速幂

代码如下：

```cpp
#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using __gnu_pbds::gp_hash_table;

const int N = 1e5 + 7;const long long MOD = 1e9 + 7;
int n, counter, CPcorder[2][N<<1], x[N], y[N], fa[N<<1];
//counter 是线的编号映射
//CPcorder 有两维，具体使用见后。第二维开了双倍是因为一个点的线有两条
long long otp = 1;//otp 即 output
gp_hash_table<int, int>xcorder, ycorder;//分别表示横向的线和纵向的线

inline int find(int a){return fa[a] == a?a:fa[a] = find(fa[a]);}
inline long long quick_pow(long long p, long long b = 2){//标准快速幂
	register long long ans = 1;
	while (p){
		if (p&1)ans = (ans*b)%MOD;
		b = (b*b)%MOD;
		p >>= 1;
	}
	return ans;
}

int main(){
//	return !printf("%d", xcorder[3]);
	scanf("%d", &n);
	for (register int i = 1;i <= n;i ++)fa[i] = 1;
	for (register int i = 1;i <= n;i ++){
		scanf("%d %d", x + i, y + i);
		if (!xcorder[x[i]])xcorder[x[i]] = ++ counter;
		if (!ycorder[y[i]])ycorder[y[i]] = ++ counter;
	}
	for (register int i = 1;i <= counter;i ++)fa[i] = i;
	for (register int i = 1;i <= n;i ++)fa[find(xcorder[x[i]])] = find(ycorder[y[i]]);
	for (register int i = 1;i <= n;i ++)CPcorder[0][find(xcorder[x[i]])] ++;
	for (register int i = 1;i <= counter;i ++)CPcorder[1][find(i)] ++;
	for (register int i = 1;i <= counter;i ++)//统计答案
		if (i == find(i))
		//为了避免查重，只在这个点为该连通块的 fa 时对该连通块统计
			if (CPcorder[0][i] == CPcorder[1][i] - 1)/*printf("A: %lld\n", quick_pow(CPcorder[1][i]) - 1), */otp = otp*(quick_pow(CPcorder[1][i]) - 1)%MOD;
			else /*printf("F: %lld\n", quick_pow(CPcorder[1][i])), */otp = otp*quick_pow(CPcorder[1][i])%MOD;
		//解释一下，if 语句中的表达式实际是在判环
	return !printf("%lld", otp);
}
```

---

## 作者：鱼跃于渊 (赞：1)

## 1. 题意
平面上有 $n$ 个点，第 $i$ 个点的坐标为 $(x_i,y_i)$，每个点有三种操作：  
1. 什么也不干。
2. 做一条平行于 $x$ 轴的直线。
3. 做一条平行于 $y$ 轴的直线。

其中重合的直线视作一条，问最终能得到多少个不同的图案，答案对 $10^9+7$ 取模。  
取值范围：$1\le n \le 10^5,\lvert x_i \rvert,\lvert y_i \rvert \le 10^9$。
## 2. 做法
首先看到这个取值范围，肯定是要离散化的。  
其次可以发现，每个点有三种选择，而且重合的点视作一条。这启发我们将每个点以 $x$ 坐标和 $y$ 坐标拆成两个点（图论中的点），然后给这两个点连上一条边，于是就形成了一张图。  
在这张图中，我们可以发现，对于每条边，它两端的点要么只能选其中一个要么一个都不选。这显然满足二分图的定义。  
我们令以 $x$ 坐标拆出来的点为左部点，以 $y$ 坐标拆出来的点为右部点，对于一条边，考虑它的意义：  
1. 如果选择了左部点，就相当于在平面中做一条 $y$ 轴的平行线；
2. 如果选择了右部点，就相当于在平面中做一条 $x$ 轴的平行线；
3. 如果什么都不选，就相当于什么线也不做。  

也就是说，这张二分图中的选点方案就是我们要求的答案。  
根据乘法原理可得，最终答案等于各联通块中的答案相乘之积。  
对于联通块 $i$ 来说，若其点数为 $d_i$，边数为 $b_i$，则它的答案 $ans_i$ 就是：  
$$ans_i=
\begin{cases}
2^{d_i}-1 &\text{if } d_i=b_i+1\\
2^{d_i} &\text{if } d_i\le b_i\\
\end{cases}$$
显然，当 $d_i=b_i+1$ 时，联通块会呈现出树或链的形态，我们无法做到使所有的点都被选到，所以要减一。  
而当 $d_i \le b_i$ 时，联通块中会出现环，显然在有环的情况下可以选中每一个点。  
最终答案就等于 $\prod ans_i$，记得取模，另外还要注意数组大小是否开够。
## 3. 代码
丑代码，请见谅。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5,mod=1e9+7;
int n,mx,ax[N],ay[N],fa[N],siz[N],ans=1;
int t[N];
int m,b[N];
vector <int> e[N];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int qpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=(res*a)%mod;
		a=(a*a)%mod;b>>=1;
	}
	return res;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>ax[i]>>ay[i];
		b[++m]=ax[i];
		b[++m]=ay[i];
	}
	sort(b+1,b+m+1);
	m=unique(b+1,b+m+1)-b-1;
	for(int i=1;i<=n;i++){
		ax[i]=lower_bound(b+1,b+m+1,ax[i])-b;
		ay[i]=lower_bound(b+1,b+m+1,ay[i])-b+m;
		mx=max({mx,ax[i],ay[i]});
	}
	iota(fa+1,fa+mx+1,1);
	for(int i=1,x,y;i<=n;i++){
		x=find(ax[i]);y=find(ay[i]);
		if(x!=y){
			fa[y]=x;
			siz[x]+=siz[y];
		}
		siz[x]++;
	}
	for(int i=1;i<=mx;i++) t[find(i)]++;
	for(int i=1;i<=mx;i++){
		if(!t[i]) continue;
		ans=(ans*(qpow(2,t[i])-(siz[i]==t[i]-1)))%mod;
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：whiteqwq (赞：1)

[CF870E Points, Lines and Ready-made Titles](https://www.luogu.com.cn/problem/CF870E)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1795129)

[Codeforces Round 870考试总结](https://zybuluo.com/xiaoziyao/note/1795123)

## 题意

平面上一共有$n$个点，每个点可以作一条平行于$x/y$轴的直线，求能形成的图形数量，对$10^9+7$取模。

（$1\leqslant n\leqslant 10^5$）

## 分析

有意思的题。建议评绿/蓝。

考虑一个套路：将矩阵/平面上的结点看做行与列之间的连边。

对于每个点都这样操作，用并查集维护可以得到若干个连通块，容易知道各个连通块互不影响，因此直接计算每个连通块的答案然后乘法原理就好了。

考虑一个是树的连通块，每一个新结点（也就是原图中的行或列）都可以是$0$或$1$，但是不可能出现全$1$的情况（设新节点的个数为$n$，只有$n-1$个原结点，因此最多有$n-1$个新节点取到$1$），那么一共有$2^n-1$种情况。

考虑一个包含环的连通块，每一个新节点都可以是$0$或$1$，而且任意情况都能出现，那么一共有$2^n$种情况。

乘起来就好了，复杂度：$O(n\log n)$。

## 代码

```
#include<stdio.h>
#include<map>
using namespace std;
const int maxn=200005,mod=1000000007;
int n,cnt,ans;
int a[maxn],b[maxn],fa[maxn],cir[maxn],size[maxn],tot[maxn];
map<int,int>mpx,mpy;
int find(int x){
	return fa[x]==x? x:fa[x]=find(fa[x]);
}
void merge(int a,int b){
	a=find(a),b=find(b);
	if(a!=b)
		size[a]+=size[b],fa[b]=a,cir[a]|=cir[b],tot[a]+=tot[b]+1;
	else cir[a]=1;
}
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)
			res=1ll*res*a%mod;
		a=1ll*a*a%mod,b>>=1;
	}
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&b[i]);
		if(mpx[a[i]]==0)
			mpx[a[i]]=++cnt;
		if(mpy[b[i]]==0)
			mpy[b[i]]=++cnt;
	}
	for(int i=1;i<=cnt;i++)
		fa[i]=i,size[i]=1;
	for(int i=1;i<=n;i++)
		merge(mpx[a[i]],mpy[b[i]]);
	ans=1;
	for(int i=1;i<=cnt;i++)
		if(fa[i]==i){
			if(cir[i])
				ans=1ll*ans*ksm(2,size[i])%mod;
			else ans=1ll*ans*(ksm(2,size[i])-1+mod)%mod;
		}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Tachibana27 (赞：0)

根据乘法原理可得：几个独立的整体组成的图案个数为各个整体组成的方案数做乘积。

如何判断是否是一个**独立的整体**呢？

考虑反向思考：若两个部分互相干扰，则它们是一个整体。而干扰当且仅当两个部分至少有一个点共线于平行于垂直线或平行线。

我们发现这个东西好像可以用并查集维护。将各个边维护在一起，若两条边有交点则它们是整体。此时对于每一个给出的点即为交点。

接下来最后的问题：**独立的整体的方案数**。

每一条边的形态由上一条决定，若形成环，则方案数为 $2^{size}$，其中 $size$ 是该整体的边的数量。若为一棵树则方案数为 $2^{size}-1$。

看了一下有的题解没有很清楚地把这个 $2^{size}-1$ 解释清楚。我们可以构造：

```
3
0 0
0 1
1 0
```

和

```
4
0 0
0 1
1 0
1 1
```

进行对比。画出来可以发现后者较于前者多一个 `#` 型的图案。可以推广，树形总是比环少存在这样一个 `#` 型。



code:

```cpp

int n;
int point;
int f[1000086];
int size[1000086];
bool h[1000086];
int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
void add(int x,int y){
	int fax=find(x);
	int fay=find(y);
	if(fax==fay)
		h[fax]=true;
	else{
		f[fax]=fay;
		size[fay]+=size[fax];
		if(h[x])
			h[y]=true;
	}
	return;
}//并查集模板
int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)
			ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans%mod;
}//快速幂
class node{
	public:
		int x;
		int y;
}a[1000086];
int ans=1;
std::map<int,int>mp1,mp2;
signed main(){
	std::cin>>n;
	for(int i=1;i<=n;i++){
		std::cin>>a[i].x>>a[i].y;
		if(not mp1[a[i].x])
			mp1[a[i].x]=++point;
		if(not mp2[a[i].y])
			mp2[a[i].y]=++point;//编号
	}
	for(int i=1;i<=point;i++){
		f[i]=i;
		size[i]=1;
	}//ini
	for(int i=1;i<=n;i++)
		add(mp1[a[i].x],mp2[a[i].y]);//交点合并
	for(int i=1;i<=point;i++)
		if(f[i]==i)
			if(h[i])//环
				ans=ans*qpow(2,size[i])%mod;
			else
				ans=ans*(qpow(2,size[i])-1)%mod;
		else;
	std::cout<<ans;
	return 0;//撒花
}

```

---

## 作者：Z_AuTwT (赞：0)

## 题意

较为明了。

## 思路

考虑将有可能相交的几个点合并成一个连通块，去逐一统计每个连通块所造成的答案。

为什么可以拆成不同的连通块呢？因为对于不会相交的两个连通块之间不论其中一个怎么变化，另一个都不会受影响。

那怎么统计答案呢？

我们发现，对于任意一个连通块，如果这个连通块内存在环，那么这个连通块的贡献就是 $2$ 的连通块大小次方，否则这个连通块的贡献就是 $2$ 的连通块大小次方减 $1$。最后用乘法原理就行了。

## CODE

```c++
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read() {//快读
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
	return x*f;
}
unordered_map<int,int>mp1,mp2;//用于去重
int fa[1000010],X[1000010],Y[1000010],sf[1000010],Size[1000010];
int find(int x){//并查集
    if(x==fa[x]) return x;
    return fa[x]=find(fa[x]);
}
void merge(int x,int y){
    int X=find(x),Y=find(y);
    if(X==Y){
        sf[X]=1;//判环
    }else{
        if(sf[X]==0&&sf[Y]==1) sf[X]=sf[Y];
        fa[Y]=fa[X];
        Size[X]+=Size[Y];
    }
    return;
}
long long qpow(long long a,long long b){//快速幂
	long long res=1;
	while(b){
		if(b&1){
			res*=a;
			res%=mod;
		}
		a*=a;
		a%=mod;
		b>>=1;
	}
	return res;
}
int tot;
main(){
    int n=read();
    for(int i=1;i<=n;i++){
        X[i]=read(),Y[i]=read();
        if(!mp1[X[i]]) mp1[X[i]]=++tot;
        if(!mp2[Y[i]]) mp2[Y[i]]=++tot;
    }
    for(int i=1;i<=tot;i++) fa[i]=i,Size[i]=1;
    for(int i=1;i<=n;i++){//合并
        merge(mp1[X[i]],mp2[Y[i]]);
    }
    long long ans=1;
    for(int i=1;i<=tot;i++){//统计答案
		if(i==fa[i]){
			if(sf[i]){ans*=qpow(2,Size[i])%mod;ans%=mod;}
			else{ans*=((qpow(2,Size[i])-1)%mod+mod)%mod;ans%=mod;}
		}
	}
	cout<<ans;
}
```

---

