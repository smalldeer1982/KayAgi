# Robots protection

## 题目描述

Company "Robots industries" produces robots for territory protection. Robots protect triangle territories — right isosceles triangles with catheti parallel to North-South and East-West directions.

Owner of some land buys and sets robots on his territory to protect it. From time to time, businessmen want to build offices on that land and want to know how many robots will guard it. You are to handle these queries.

## 样例 #1

### 输入

```
17 10
1 1 3 2 4
1 3 10 3 7
1 2 6 8 2
1 3 9 4 2
2 4 4
1 4 15 10 6
2 7 7
2 9 4
2 12 2
2 13 8
```

### 输出

```
2
2
2
0
1
```

# 题解

## 作者：pufanyi (赞：13)

考虑到四种方向是对称的，我们只考虑其中一种情况，比如说直角顶点在左下角的情况，令三个顶点为 $(x,y), (x+l,y), (x,y+l)$。
	
首先我们发现需要加的所有点 $(x',y')$，都满足 $x+y\le x'+y'\le x+y+l$，这个东西用一棵树状数组就可以维护：

![](https://cdn.luogu.com.cn/upload/image_hosting/adnnjqlf.png)

然后我们就是要减去这两块：

![](https://cdn.luogu.com.cn/upload/image_hosting/vb0lzid2.png)

我们考虑如何减去，观察这些点的性质，首先均满足 $x'+y'\in [x+y,x+y+l]$，然后其还满足 $x'<x$ 或 $y'<y$。于是我们可以考虑开两棵二维树状数组，一棵维护下标 $(x+y,x)$，另一棵维护下标 $(x+y,y)$，然后在这两棵树状数组上矩阵加即可。
	
时间复杂度 $\mathcal{O}(q\log^2n)$，空间 $\mathcal{O}(n^2)$。

---

## 作者：xht (赞：7)

> [CF575I Robots protection](https://codeforces.com/contest/575/problem/I)

## 题意

- 你需要在平面直角坐标系上进行 $q$ 次操作。
- 每次操作有两种，要么放置一个两条直角边平行于坐标轴的等腰直角三角形，要么查询某一个点被多少个三角形覆盖。
- 每个等腰直角三角形可以用四个参数 $dir,x,y,len$ 确定，其中 $dir \in [1,4]$ 表示三角形的方向，$(x,y)$ 表示直角的顶点坐标，$len$ 表示直角边的长度。
- 保证所有点的坐标都是整数且 $\in [1,n]$。
- $n \le 5 \times 10^3$，$q \le 10^5$。

## 题解

$n$ 很小，二维树状数组即可。

注意到要分五类考虑，所以要在时间和空间卡一下常数。

![](http://www.xht37.com/wp-content/uploads/2020/01/1126418-20200108213332804-1585535723.png)

（图来自兔）

## 代码

```cpp
const int N = 1e4 + 7, M = 1e5 + 7;
int n, m, op[M], dir[M], x[M], y[M], c[M], ans[M];
int X, Y, bit[N][N], stx[M], sty[M], stz[M], top;

inline void add(int x, int y, int z) {
	stx[++top] = x, sty[top] = y, stz[top] = z;
	for (int i = x; i <= X; i += i & -i)
		for (int j = y; j <= Y; j += j & -j)
			bit[i][j] += z;
}

inline int ask(int x, int y) {
	int z = 0;
	for (int i = x; i; i -= i & -i)
		for (int j = y; j; j -= j & -j)
			z += bit[i][j];
	return z;
}

inline void clear() {
	while (top) add(stx[top], sty[top], -stz[top]), top -= 2;
}

int main() {
	rd(n), rd(m);
	for (int i = 1; i <= m; i++) {
		rd(op[i]);
		if (op[i] == 1) rd(dir[i]), rd(x[i]), rd(y[i]), rd(c[i]);
		else rd(x[i]), rd(y[i]);
	}

	X = n, Y = n;
	for (int i = 1; i <= m; i++)
		if (op[i] == 1) {
			if (dir[i] == 1) add(x[i], y[i], 1);
			if (dir[i] == 2) add(x[i], y[i] + 1, -1);
			if (dir[i] == 3) add(x[i] + 1, y[i], -1);
			if (dir[i] == 4) add(x[i] + 1, y[i] + 1, 1);
		} else ans[i] += ask(x[i], y[i]);
	clear();

	X = n + n, Y = n;
	for (int i = 1; i <= m; i++)
		if (op[i] == 1) {
			if (dir[i] == 1)
				add(x[i] + y[i] + c[i] + 1, y[i], -1);
			if (dir[i] == 4)
				add(x[i] + y[i] - c[i], y[i] + 1, -1);
		} else ans[i] += ask(x[i] + y[i], y[i]);
	clear();
	
	X = n, Y = n + n;
	for (int i = 1; i <= m; i++)
		if (op[i] == 1) {
			if (dir[i] == 1)
				add(n - x[i] + 2, x[i] + y[i] + c[i] + 1, 1);
			if (dir[i] == 4)
				add(n - x[i] + 1, x[i] + y[i] - c[i], 1);
		} else ans[i] += ask(n - x[i] + 1, x[i] + y[i]);
	clear();

	X = n + n, Y = n;
	for (int i = 1; i <= m; i++)
		if (op[i] == 1) {
			if (dir[i] == 2)
				add(n + x[i] - y[i] + c[i] + 2, y[i] + 1, 1);
			if (dir[i] == 3)
				add(n + x[i] - y[i] - c[i] + 1, y[i], 1);
		} else ans[i] += ask(n + x[i] - y[i] + 1, y[i]);
	clear();

	X = n, Y = n + n;
	for (int i = 1; i <= m; i++)
		if (op[i] == 1) {
			if (dir[i] == 2)
				add(x[i], n - x[i] + y[i] - c[i] + 1, 1);
			if (dir[i] == 3)
				add(x[i] + 1, n - x[i] + y[i] + c[i] + 2, 1);
		} else ans[i] += ask(x[i], n - x[i] + y[i] + 1);
	clear();

	for (int i = 1; i <= m; i++)
		if (op[i] == 2) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：小胖同学 (赞：6)

## CF 575I / 火力规划
----

### 题目简述

传送门 [[Link](https://codeforces.com/problemset/problem/575/I)] 。

两种操作，当 $op = 1$ 时，输入 $dir , x , y , r$ 代表 ，方向、横纵坐标$(x , y)$ 、半径 $r$ 的曼哈顿扇形。

 $dir$ 有四种可能的取值，对于 $(x,y)$ 的 $dir$ 方向的点 $(x',y')$ 定义为 ：

$\bullet$  $dir = 1$ 时 $x' \geqslant x$ 且 $y' \geqslant y$ ；

$\bullet$  $dir = 2$ 时 $x' \geqslant x$ 且 $y' \leqslant y$ ；

$\bullet$  $dir = 3$ 时 $x' \leqslant x$ 且 $y' \geqslant y$ ；

$\bullet$  $dir = 4$ 时 $x' \leqslant x$ 且 $y' \leqslant y$ 。

当$op = 2$ 时，输入 $x , y$ 代表询问 $(x , y)$ 被几个曼哈顿扇形覆盖。

$1 \leqslant n \leqslant 5000$  ，$1 \leqslant q \leqslant 10^5$ 。

注：对于 $(x', y')$ 和 $(x , y)$ ，曼哈顿距离指 $ \mid x - x'\mid + \mid y - y'\mid $ , 曼哈顿扇形指 矩阵中所有到点 $O$ 距离等于定长的点的集合，及对于半径为 $r$ 的扇形 是所有 $ \mid x - x'\mid + \mid y - y'\mid  \leqslant r$ 的集合。  

----

### 解题思路

二维平面规则图形覆盖，~~显然~~ 指向二维差分。由于本题 $1 \leqslant n \leqslant 5000$ ，$1 \leqslant q \leqslant 10^5$ 考虑树状数组求前缀和优化。

举个例子 对于图形 1 4 3 4 2 。



![](https://cdn.luogu.com.cn/upload/image_hosting/8u2s78j2.png)



考虑用 $y =-x + b$ 为线存差分值，由于是曼哈顿距离我们就可以 ~~显然~~ 的观察到顶点为 $(x,y)$ 半径为 2 的图形若要覆盖 $(x',y')$ 就要满足 $x'+ y' \leqslant x + y \leqslant x'+ y'+ r$ 。

对于本例子而言是如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/dfvnyn35.png)



让 $y = -x + 6(x \geqslant 1)$ 的差分 $+1$ ; $y = -x + 9(x \geqslant 4)$ 的差分 $-1$ ;

但这时候我们会发现 有些点多算了，例如  $(2 , 8)$  只算到了 $+$ 没有 $-$   。

考虑再建立一个平行于坐标系的差分将多算的部分删掉，效果如下（注： 左边绿点 $-1$ 右边 $+1$ ）。

![](https://cdn.luogu.com.cn/upload/image_hosting/1haizzob.png)

这样我们就处理好了 $dir = 4$ （开口左下角）的情况；

考虑每次将整张图旋转 90° 对于每一个询问处理。
```cpp
swap(ask[i].x , ask[i].y) , ask[i].x = n - ask[i].x + 1;
```

统计四次答案即可。

----



### 题解



传送门[[Link](https://www.luogu.com.cn/paste/g09cwq34)] 。

---

## 作者：关怀他人 (赞：4)

### CF 575I
#### Solution
由于四种方向是对称的，我们只考虑$dir=1$的情况。

点$(x,y)$在三角形$(x_0,y_0,len)$内部或边界的充要条件为$x\geq x_0$，$y\geq y_0$且$x+y\leq x_0+y_0+len$直接做是一个四维偏序（还有一维时间），无法通过。考虑对$x\geq x_0$和$y\geq y_0$容斥，那么除了$x<x_0,y<y_0,x+y\leq x_0+y_0+len$这种情况外都是三维偏序。对于这种特殊的情况，不难发现若$x<x_0,y<y_0$，由于$len>0$的，所以$x+y$一定是小于$x_0+y_0+len$的。于是这还是一个三维偏序为题。最后只需要处理几个三维偏序即可。

由于$n\leq 5000$，使用二维树状数组维护即可。

时间复杂度$\mathcal O(q\log^2n)$

#### Code
```cpp
int n,Q;
int x[MAXM],y[MAXM],len[MAXM],dir[MAXM],ans[MAXM];

struct BIT{
    int n, m;
    int c[MAXN][MAXN];

    void clear() {memset(c,0,sizeof(c));}
    void resize(int x,int y) {n = x; m = y;}

    void modify(int x,int y,int v){
        for(int i = x;i <= n;i += i & -i)
            for(int j = y;j <= m;j += j & -j)
                c[i][j] += v;
    }

    int query(int x,int y){
        int res = 0;
        for(int i = x;i >= 1;i -= i & -i)
            for(int j = y;j >= 1;j -= j & -j)
                res += c[i][j];
        return res;
    }
} bit;

int main(){
    scanf("%d%d",&n,&Q);
    for(int i = 1,op;i <= Q;i++){
        scanf("%d",&op);
        if(op == 1) scanf("%d%d%d%d",&dir[i],&x[i],&y[i],&len[i]);
        else scanf("%d%d",&x[i],&y[i]), dir[i] = 5;
    }
    bit.resize(n,n);
    for(int i = 1;i <= Q;i++){
        if(dir[i] == 1) bit.modify(x[i],y[i],1), bit.modify(x[i],y[i] + len[i] + 1,-1);
        else if(dir[i] == 2) bit.modify(x[i],y[i] - len[i],1), bit.modify(x[i],y[i] + 1,-1);
        else if(dir[i] == 3) bit.modify(x[i] + 1,y[i] + len[i] + 1,1), bit.modify(x[i] + 1,y[i],-1);
        else if(dir[i] == 4) bit.modify(x[i] + 1,y[i] + 1,1), bit.modify(x[i] + 1,y[i] - len[i],-1);
        else if(dir[i] == 5) ans[i] += bit.query(x[i],y[i]);
    }
    bit.clear(); bit.resize(n + n,n);
    for(int i = 1;i <= Q;i++){
        if(dir[i] == 2){
            bit.modify(x[i] - y[i] + len[i] + n + 2,y[i] + 1,1);
            bit.modify(x[i] - y[i] + len[i] + n + 2,y[i] - len[i],-1);
        }else if(dir[i] == 3){
            bit.modify(x[i] - y[i] - len[i] + n + 1,y[i],1);
            bit.modify(x[i] - y[i] - len[i] + n + 1,y[i] + len[i] + 1,-1);
        }else if(dir[i] == 5)
            ans[i] += bit.query(x[i] - y[i] + n + 1,y[i]);
    }
    bit.clear(); bit.resize(n + n,n);
    for(int i = 1;i <= Q;i++){
        if(dir[i] == 1){
            bit.modify(x[i] + y[i] + len[i] + 1,n - y[i] + 2,1);
            bit.modify(x[i] + y[i] + len[i] + 1,n - y[i] - len[i] + 1,-1);
        }else if(dir[i] == 4){
            bit.modify(x[i] + y[i] - len[i],n - y[i] + 1,1);
            bit.modify(x[i] + y[i] - len[i],n - y[i] + len[i] + 2,-1);
        }else if(dir[i] == 5)
            ans[i] += bit.query(x[i] + y[i],n - y[i] + 1);
    }
    for(int i = 1;i <= Q;i++)
        if(dir[i] == 5) printf("%d\n",ans[i]);
    return 0;
}

---

## 作者：Shxt_Plus (赞：3)

发现题解区都是 $O(q\log^2 n)$ 做法，来写一个 $O(q\sqrt n \log n)$ 做法。

UPD：发现了 $q\sqrt n$ 做法。

先只考虑 $dir=3$ 的三角形，发现可以把这个操作转换为 $len+1$ 个区间加操作，接下来经典套路，把区间加单点查询用差分转化为单点加区间查询。

用树状数组维护，修改复杂度 $O(q n\log n)$，查询复杂度 $O(q\log n)$，发现瓶颈在修改，考虑优化。

尝试用分块优化，对行进行分块，不妨设 $B$ 行为一块，每次修改对于散块直接暴力修改。

接下来的难题在于怎么处理整块，先将整个矩形都画上斜线，并从下到上，从左到右进行编号。

用 $h_{x,y}$ 表示点 $x,y$ 所在斜线编号。

观察整块要加的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/0roxl56l.png)

不难发现所有的点满足两个条件 。（$q_x,q_y$ 表示修改三角形最上方的点）

- $x\ge q_y$

- $h_{x,y} <=h_{q_x,q_y}$

不难证明这是充分必要条件。

对于每个块维护两个树状数组，每次在第一个树状数组的 $q_y$ 位置 $+1$，在第二个树状数组的 $h_{q_x,q_y}+1$ 位置 $-1$。

每次查询先查询前缀和，然后查询整块的贡献即可。

这样，修改的复杂度就变成了 $O(qB\log n+q\frac{n}{B}\log n)$，$B$ 取 $\sqrt n$时有最优复杂度 $q\sqrt n\log n$。

将矩阵进行旋转依次处理其他形状的三角形即可。

发现查询的复杂度远小于修改的复杂度，考虑将 $\log n$ 修改，$\log n$ 查询的树状数组换成 $O(1)$ 修改，$O(\sqrt n)$ 查询的值域分块，这样就平衡了修改与查询的复杂度，总复杂度 $O(q\sqrt n)$。

Code:

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3,"Ofast","inline")
using namespace std;
const int maxn=5005,maxm=1e5+5,gmaxn=105;
int n,m;
struct Query
{
	int op,x,y,len,dir,ans;
}q[maxm];
int L[maxn],R[maxn];
int cx[maxn];
struct Tree_sz
{
	int c[maxn<<1],p[gmaxn];
	void clear()
	{
		for(int i=1;i<=2*n;i++)c[i]=0;
		for(int i=1;i<=cx[2*n];i++)p[i]=0;
	}
	void add(int x,int v)
	{
		c[x]+=v;
		p[cx[x]]+=v;
	}
	int ask(int x)
	{
		int op=cx[x],sum=0;
		for(int i=1;i<op;i++)
		{
			sum+=p[i];
		}
		for(int i=L[op];i<=x;i++)sum+=c[i];
		return sum;
	}
}c[maxn],c1[gmaxn],g[gmaxn];

void solve(int x)
{
	for(int i=1;i<=n;i++)
	{
		c[i].clear();
	}
    for(int i=1;i<=cx[n];i++)
    {
        c1[i].clear();
        g[i].clear();
    }
	for(int i=1;i<=m;i++)
	{
		if(q[i].dir!=0 && q[i].dir!=x)continue;
		if(q[i].op==1)
		{
			int l=q[i].x-q[i].len,r=q[i].x;
			int l1=cx[l],r1=cx[r];
			if(l1==r1)
			{
				for(int j=l;j<=r;j++)
				{
					c[j].add(q[i].y,1);
					c[j].add(q[i].y+(j-l+1),-1);
				}
			}
			else
			{
				int p=q[i].y-l+n;
				for(int j=l;j<=R[l1];j++)
				{
					c[j].add(q[i].y,1);
					c[j].add(q[i].y+(j-l+1),-1);
				}
				for(int j=l1+1;j<r1;j++)
				{
					g[j].add(p+1,-1);
					c1[j].add(q[i].y,1);
				}
				for(int j=L[r1];j<=r;j++)
				{
					c[j].add(q[i].y,1);
					c[j].add(q[i].y+(j-l+1),-1);
				}
			}
		}
		else
		{
			q[i].ans+=c[q[i].x].ask(q[i].y);
			q[i].ans+=g[cx[q[i].x]].ask(q[i].y-q[i].x+n);
			q[i].ans+=c1[cx[q[i].x]].ask(q[i].y);
		}
	}
}
int main(){
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
    scanf("%d%d",&n,&m);
    int block=sqrt(n);
    for(int i=1;i<=2*n;i++)
    {
    	cx[i]=(i-1)/block+1;
    	if(cx[i]!=cx[i-1])
    	{
    		L[cx[i]]=i;
    		R[cx[i-1]]=i-1;
		}
	}
	R[cx[2*n]]=2*n;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&q[i].op);
		if(q[i].op==1)scanf("%d%d%d%d",&q[i].dir,&q[i].x,&q[i].y,&q[i].len);
		else scanf("%d%d",&q[i].x,&q[i].y);
	}
	solve(3);
	for(int i=1;i<=m;i++)
	{
		q[i].x=n-q[i].x+1;
	}
	solve(1);
	for(int i=1;i<=m;i++)
	{
		q[i].y=n-q[i].y+1;
	}
	solve(2);
	for(int i=1;i<=m;i++)
	{
		q[i].x=n-q[i].x+1;
	}
	solve(4);
	for(int i=1;i<=m;i++)
	{
		if(q[i].op==2)printf("%d\n",q[i].ans);
	}
    return 0;
}
```

---

## 作者：樱雪喵 (赞：3)

水篇题解，实际发布时间 2023.10.6。

发现等腰直角三角形有四个方向，而对于不同的方向可以分开考虑，都翻转成第一种，最后统计四次答案。只需要考虑第一种情况怎么做。

如果要修改三角形 $(x,y,len)$，如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/lwypkpwc.png)

发现本质是限制了：

1. $x'+y'\in [x+y,x+y+len]$
2. $x' \in [x,n]$
3. $y' \in [y,n]$

发现同时对三个东西有限制，这是不好做的，考虑拆成两部分。

![](https://cdn.luogu.com.cn/upload/image_hosting/k346mush.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/dwl6chfp.png)

那么黄色和绿色的部分都只有两条限制，分别开两个二维 BIT 维护 $(x+y,x)$ 和 $(x+y,y)$，矩阵修改单点查询，相减即可。

```cpp
const int N=5005,M=1e5+5;
int n,q;
struct BIT
{
    int tr[N<<1][N];
    il void clear() {memset(tr,0,sizeof(tr));}
    il int lowbit(int x) {return x&(-x);}
    void add(int x,int y,int k)
    {
        // cout<<"add "<<x<<" "<<y<<" "<<k<<endl;
        if(x<1||y<1||x>(n<<1)||y>n) return;
        for(int i=x;i<=2*n;i+=lowbit(i))
            for(int j=y;j<=n;j+=lowbit(j)) tr[i][j]+=k;
    }
    il int query(int x,int y) 
    {
        int res=0;
        for(int i=x;i;i-=lowbit(i))
            for(int j=y;j;j-=lowbit(j)) res+=tr[i][j];
        return res;
    }
    il void Add(int a,int b,int c,int d)
    {
        add(a,b,1),add(c+1,b,-1),add(a,d+1,-1),add(c+1,d+1,1);
    }
}tr[2];
struct node
{
    int op,dir,x,y,len;
    int ans;
}a[M];
il void modify(int x,int y,int len)
{
    tr[0].Add(x+y,1,x+y+len,x-1);
    tr[1].Add(x+y,y,x+y+len,n);
}
il int query(int x,int y) {return tr[1].query(x+y,y)-tr[0].query(x+y,x);}
int main()
{
    n=read(),q=read();
    for(int i=1;i<=q;i++)
    {
        a[i].op=read(); 
        if(a[i].op==1)
            a[i].dir=read(),a[i].x=read(),a[i].y=read(),a[i].len=read();
        else a[i].x=read(),a[i].y=read();
    }
    for(int d=1;d<=4;d++)
    {
        tr[0].clear(),tr[1].clear();
        for(int i=1;i<=q;i++)
        {
            if(a[i].op==1&&a[i].dir!=d) continue;
            int x=a[i].x,y=a[i].y;
            if(d==2||d==4) y=n-y+1;
            if(d==3||d==4) x=n-x+1;
            if(a[i].op==1) modify(x,y,a[i].len);
            else a[i].ans+=query(x,y);
        }
    }
    for(int i=1;i<=q;i++) if(a[i].op==2) printf("%d\n",a[i].ans);
    return 0;
}
```

---

## 作者：DeepSeaSpray (赞：2)

四种方向是对称的，因此我们可以统一化归到第一种情况。

我们发现这是一道区修单查。

对于需要修改的三角形 $(a,b,l)$，（$a,b,l$ 分别表示顶点 $(a,b)$ 与直角边长 $l$）。

点 $(x,y)$ 属于此三角形需要满足以下条件。

- $a+b \leq x+y \leq a+b+l$
- $a \leq x$
- $b \leq y$

注意到有三个限制条件，处理比较复杂。

我们可以使用割补法。用：

- $a+b \leq x+y \leq a+b+l$
- $b \leq y$

减去：

- $a+b \leq x+y \leq a+b+l$
- $x < a$

每一次修改都只有两个限制条件，直接二维树状数组就好了。

图实在是懒得画了。

还是讲讲代码实现。

首先对于树状数组，我们可以开两棵，一棵以 $(x+y,x)$ 作为坐标，另一棵以 $(x+y,y)$ 作为坐标，这样我们就好处理了。

接着就是，对于方向不同的三角形，我们可以每一个方向统一处理，免去了开多棵树状数组的麻烦。

对称什么的就不同我教了，看代码吧。

[查看代码](https://codeforces.com/contest/575/submission/251231730)

---

## 作者：jun头吉吉 (赞：2)

## 题意
进行 $q$ 次操作，每次操作有两种，要么放置一个等腰直角三角形，要么查询某一个点被多少个三角形覆盖。

每个等腰直角三角形可以用四个参数 $dir,x,y,len$ 确定，其中 $dir \in [1,4]$ 表示三角形的方向，$(x,y)$ 表示直角的顶点坐标，$len$ 表示直角边的长度。

$x,y\in [1,n]$

$n≤5×10^3,q\le 10^5$

## 题解
~~成功抢到最劣解~~

~~如果想当做思维题做，那么请不要看这篇题解。~~

以下为套路解法。

我们先考虑方向往右上的三角形，就是下面一种：

![](https://cdn.luogu.com.cn/upload/image_hosting/kym6pvyq.png)

如果顶点为$(a,b)$，边长为$r$，那么它上面一条直线的解析式显然为$y=-x+a+b+r$

那么一个点$x,y$在三角形内，则必然有：
$$\begin{cases}a\le x\\ b\le y\\ a+b+r≥ x+y\end{cases}$$
那如果在加入一个时间戳$t$，就变成了
$$\begin{cases}t_1\le t_2\\ a\le x\\ b\le y\\ a+b+r≥ x+y\end{cases}$$
此时就变成一个~~简单的四位偏序~~，但是$\mathcal{O}(n\times\log^3n)$不太可过的样子，于是可以用一些奇奇怪怪的方法降低常数。

于是我们考虑合并$[l,mid]$与$[mid+1,r]$两个区间，那么区间内部的贡献已经统计完了，那么对于$a\in [mid+1,r]$，就是在$[l,mid]$找到第一个$x_b>x_a$，在$[1,b)$ 中计算
$$\begin{cases}y\le y_a
\\ x+y+r≥x_a+y_a\end{cases}$$

由于$y\le 5000,x+y+r\le 5000\times 2$直接上树状数组统计即可。

现在我们已经统计完了一种方向的答案，那么剩下三种的答案。当然可以重新讨论，但我们可以通过旋转变成上面的形式。

~~于是最劣解就被口胡出来了~~

复杂度：$\mathcal{O}(n\times\log_2n\times\log_25000\times\log_210000)$
## ~~丑陋的~~代码
```cpp
#include<bits/stdc++.h>
//#define fast
namespace in{
	#ifdef fast
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
	#else
	inline int getc(){return getchar();}
	#endif
	template <typename T>inline void read(T& t){
		t=0;int f=0;char ch=getc();while (!isdigit(ch)){if(ch=='-')f = 1;ch=getc();}
	    while(isdigit(ch)){t=t*10+ch-48;ch = getc();}if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){read(t);read(args...);}
}
namespace out{
	char buffer[1<<21];int p1=-1;const int p2 = (1<<21)-1;
	inline void flush(){fwrite(buffer,1,p1+1,stdout),p1=-1;}
	inline void putc(const char &x) {if(p1==p2)flush();buffer[++p1]=x;}
	template <typename T>void write(T x) {
		static char buf[15];static int len=-1;if(x>=0){do{buf[++len]=x%10+48,x/=10;}while (x);}else{putc('-');do {buf[++len]=-(x%10)+48,x/=10;}while(x);}
		while (len>=0)putc(buf[len]),--len;
	}
}
using namespace std;
const int N=5e3+1;
int lowbit(int x){return x&-x;}
struct TREE{
	int tree[N*2+1];
	void ins(int x){
		for(int i=x;i<=2*N;i+=lowbit(i))
			tree[i]++;
	}
	void clear(int x){
		for(int i=x;i<=2*N;i+=lowbit(i))
			tree[i]=0;
	}
	int qry(int x){
		int res=0;
		for(int i=x;i;i-=lowbit(i))
			res+=tree[i];
		return res;
	}
	int val(int x){
		return qry(2*N)-qry(x-1);
	}
};
TREE tree[N+1];
void upd(int x,int val){
	for(int i=x;i<=N;i+=lowbit(i))
		tree[i].ins(val);
}
int qry(int x,int val){
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		res+=tree[i].val(val);
	return res;
}
void clear(int x,int val){
	for(int i=x;i<N;i+=lowbit(i))
		tree[i].clear(val);
}
const int Q=1e5+100;
int n,q,ans[Q];
int op[Q],dir[Q],x[Q],y[Q],r[Q];
namespace CDQ{
	struct node{
		int op;
		int id;
		int x,y,r;
	}a[Q];
	int cnt=0;
	#define mid (l+r>>1)
	void cdq(int l,int r){
		//printf("%d %d\n",l,r);
		if(l>=r)return;
		cdq(l,mid);cdq(mid+1,r);
		sort(&a[l],&a[mid+1],[&](node a,node b){return a.x!=b.x?a.x<b.x:(a.y!=b.y?a.y<b.y:a.op<b.op);});
		sort(&a[mid+1],&a[r+1],[&](node a,node b){return a.x!=b.x?a.x<b.x:(a.y!=b.y?a.y<b.y:a.op<b.op);});
		int now=l;//下一个选的
		for(int i=mid+1;i<=r;i++)
			if(a[i].op==2){
				//统计跨块的贡献
				while(now<=mid&&a[now].x<=a[i].x){
					if(a[now].op==2){now++;continue;}
					upd(a[now].y,a[now].x+a[now].y+a[now].r);now++;
				}
				ans[a[i].id]+=qry(a[i].y,a[i].x+a[i].y);
			} 
		for(int i=l;i<now;i++)
			clear(a[i].y,a[i].x+a[i].y+a[i].r);
	}
	void init(){cnt=0;}
	void run(){cdq(1,cnt);}
}
signed main(){
	in::read(n,q);
	for(int i=1;i<=q;i++){
		in::read(op[i]);
		if(op[i]==1)in::read(dir[i],x[i],y[i],r[i]);
		else in::read(x[i],y[i]);
	}
	CDQ::init();
	for(int i=1;i<=q;i++)
		if(op[i]==1&&dir[i]==1)CDQ::a[++CDQ::cnt]=(CDQ::node){1,i,x[i],y[i],r[i]};
		else if(op[i]==2)      CDQ::a[++CDQ::cnt]=(CDQ::node){2,i,x[i],y[i],r[i]};
	CDQ::run();
	CDQ::init();
	for(int i=1;i<=q;i++)
		if(op[i]==1&&dir[i]==2)CDQ::a[++CDQ::cnt]=(CDQ::node){1,i,N-y[i],x[i],r[i]};
		else if(op[i]==2)      CDQ::a[++CDQ::cnt]=(CDQ::node){2,i,N-y[i],x[i],r[i]};
	CDQ::run();
	CDQ::init();
	for(int i=1;i<=q;i++)
		if(op[i]==1&&dir[i]==4)CDQ::a[++CDQ::cnt]=(CDQ::node){1,i,N-x[i],N-y[i],r[i]};
		else if(op[i]==2)      CDQ::a[++CDQ::cnt]=(CDQ::node){2,i,N-x[i],N-y[i],r[i]};
	CDQ::run();
	CDQ::init();
	for(int i=1;i<=q;i++)
		if(op[i]==1&&dir[i]==3)CDQ::a[++CDQ::cnt]=(CDQ::node){1,i,y[i],N-x[i],r[i]};
		else if(op[i]==2)      CDQ::a[++CDQ::cnt]=(CDQ::node){2,i,y[i],N-x[i],r[i]};
	CDQ::run();
	
	for(int i=1;i<=q;i++)
		if(op[i]==2)out::write(ans[i]),out::putc('\n');
	out::flush();
	return 0;
}
```

---

## 作者：bluewindde (赞：1)

离线询问，K-D Tree 维护询问的答案。

以第一种修改 $(x, y, len)$ 为例，记 $z = len$，被三角形覆盖的点 $x', y'$ 满足如下约束条件。

- $x' \geqslant x$；
- $y' \geqslant y$；
- $y' \leqslant -(x' - x) + y + z$，即 $x' + y' \leqslant x + y + z$。

矩形的情况和剩余三类修改可以类比推出，如果不会可以看代码的四个 add 函数。

K-D Tree 的时间复杂度分析见 [OI Wiki](https://oi.wiki/ds/kdt/#%E5%A4%8D%E6%9D%82%E5%BA%A6%E5%88%86%E6%9E%90)。容易说明三角形不影响“最多向下进入两个孙子仍有第 3 类点”的结论，时间复杂度不变劣。

时间复杂度 $O(q \sqrt q)$。

```cpp
#include <algorithm>
#include <iostream>

using namespace std;

int n, q;

struct ques {
    int op, x, y, z, d;
} qs[100005];

struct node {
    int x, y;
    friend inline bool operator<(const node &x, const node &y) {
        return x.x == y.x ? x.y < y.y : x.x < y.x;
    }
    friend inline bool operator==(const node &x, const node &y) {
        return x.x == y.x && x.y == y.y;
    }
} a[100005];
int len;

struct kdt {
    int ls, rs, l, r, d, u, w, tag;
} kd[100005];
static inline void pushtag(int p, int c) {
    if (!p)
        return;
    kd[p].w += c;
    kd[p].tag += c;
}
static inline void pushdown(int p) {
    pushtag(kd[p].ls, kd[p].tag);
    pushtag(kd[p].rs, kd[p].tag);
    kd[p].tag = 0;
}
static inline void maintain(int p) {
    kd[p].l = kd[p].r = a[p].x;
    kd[p].d = kd[p].u = a[p].y;
    if (kd[p].ls) {
        kd[p].l = min(kd[p].l, kd[kd[p].ls].l);
        kd[p].r = max(kd[p].r, kd[kd[p].ls].r);
        kd[p].d = min(kd[p].d, kd[kd[p].ls].d);
        kd[p].u = max(kd[p].u, kd[kd[p].ls].u);
    }
    if (kd[p].rs) {
        kd[p].l = min(kd[p].l, kd[kd[p].rs].l);
        kd[p].r = max(kd[p].r, kd[kd[p].rs].r);
        kd[p].d = min(kd[p].d, kd[kd[p].rs].d);
        kd[p].u = max(kd[p].u, kd[kd[p].rs].u);
    }
}
static inline int build(int l, int r, int op) {
    if (l > r)
        return 0;
    int mid = (l + r) >> 1;
    if (op)
        nth_element(a + l, a + mid, a + r + 1,
                    [](const node &x, const node &y) {
                        return x.x < y.x;
                    });
    else
        nth_element(a + l, a + mid, a + r + 1,
                    [](const node &x, const node &y) {
                        return x.y < y.y;
                    });
    kd[mid].ls = build(l, mid - 1, op ^ 1);
    kd[mid].rs = build(mid + 1, r, op ^ 1);
    maintain(mid);
    return mid;
}
static inline void add1(int x, int y, int z, int p) {
    if (!p || kd[p].r < x || kd[p].u < y || kd[p].l + kd[p].d > x + y + z)
        return;
    if (x <= kd[p].l && y <= kd[p].d && kd[p].r + kd[p].u <= x + y + z) {
        pushtag(p, 1);
        return;
    }
    if (x <= a[p].x && y <= a[p].y && a[p].x + a[p].y <= x + y + z)
        ++kd[p].w;
    pushdown(p);
    add1(x, y, z, kd[p].ls);
    add1(x, y, z, kd[p].rs);
}
static inline void add2(int x, int y, int z, int p) {
    if (!p || kd[p].r < x || kd[p].d > y || kd[p].u - kd[p].l < y - x - z)
        return;
    if (x <= kd[p].l && kd[p].u <= y && kd[p].d - kd[p].r >= y - x - z) {
        pushtag(p, 1);
        return;
    }
    if (x <= a[p].x && a[p].y <= y && a[p].y - a[p].x >= y - x - z)
        ++kd[p].w;
    pushdown(p);
    add2(x, y, z, kd[p].ls);
    add2(x, y, z, kd[p].rs);
}
static inline void add3(int x, int y, int z, int p) {
    if (!p || kd[p].l > x || kd[p].u < y || kd[p].d - kd[p].r > y + z - x)
        return;
    if (kd[p].r <= x && y <= kd[p].d && kd[p].u - kd[p].l <= y + z - x) {
        pushtag(p, 1);
        return;
    }
    if (a[p].x <= x && y <= a[p].y && a[p].y - a[p].x <= y + z - x)
        ++kd[p].w;
    pushdown(p);
    add3(x, y, z, kd[p].ls);
    add3(x, y, z, kd[p].rs);
}
static inline void add4(int x, int y, int z, int p) {
    if (!p || kd[p].l > x || kd[p].d > y || kd[p].r + kd[p].u < x + y - z)
        return;
    if (kd[p].r <= x && kd[p].u <= y && kd[p].l + kd[p].d >= x + y - z) {
        pushtag(p, 1);
        return;
    }
    if (a[p].x <= x && a[p].y <= y && a[p].x + a[p].y >= x + y - z)
        ++kd[p].w;
    pushdown(p);
    add4(x, y, z, kd[p].ls);
    add4(x, y, z, kd[p].rs);
}
static inline int query(int x, int y, int p) {
    if (!p || kd[p].l > x || kd[p].r < x || kd[p].d > y || kd[p].u < y)
        return 0;
    if (a[p].x == x && a[p].y == y)
        return kd[p].w;
    pushdown(p);
    return query(x, y, kd[p].ls) + query(x, y, kd[p].rs);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= q; ++i) {
        int op;
        cin >> op;
        if (op == 1) {
            int d, x, y, z;
            cin >> d >> x >> y >> z;
            qs[i] = {1, x, y, z, d};
        } else {
            int x, y;
            cin >> x >> y;
            qs[i] = {2, x, y, 0, 0};
            a[++len] = {x, y};
        }
    }
    sort(a + 1, a + len + 1);
    len = unique(a + 1, a + len + 1) - a - 1;
    int rt = build(1, len, 1);
    for (int i = 1; i <= q; ++i) {
        int op = qs[i].op;
        if (op == 1) {
            int x = qs[i].x, y = qs[i].y, z = qs[i].z, d = qs[i].d;
            if (d == 1)
                add1(x, y, z, rt);
            else if (d == 2)
                add2(x, y, z, rt);
            else if (d == 3)
                add3(x, y, z, rt);
            else
                add4(x, y, z, rt);
        } else if (op == 2) {
            int x = qs[i].x, y = qs[i].y;
            cout << query(x, y, rt) << '\n';
        }
    }
    cout.flush();
    return 0;
}
```

---

## 作者：zzwdsj (赞：1)

### 思路

我们只考虑第 $dis=1$ 的情况，其余情况翻转即可。

众所周知，$dis=1$ 时，点 $(x,y)$ 在顶点为 $(a,b)$，边长为 $len$ 的三角形内的条件是 $a \le x$，$b \le y$，$a+b \le x+y \le a+b+len$。这不好维护，我们可以它转化成满足 $b \le y$，$a+b \le x+y \le a+b+len$ 且不满足 $a > x$，$a+b \le x+y \le a+b+len$。

对于 $b \le y$，$a+b \le x+y \le a+b+len$，把式子里的 $x+y$ 看成 $x$ 坐标，用 $x_0$ 表示；把式子里的 $y$ 看成 $y$ 坐标，用 $y_0$ 表示。整个式子就变成了 $b \le y_0$，$a+b \le x_0 \le a+b+len$，这恰好就是一个矩形，用树状数组维护即可。

对于 $a > x$，$a+b \le x+y \le a+b+len$，把式子里的 $x+y$ 看成 $x$ 坐标，用 $x_1$ 表示；把式子里的 $x$ 看成 $y$ 坐标，用 $y_1$ 表示。整个式子就变成了 $a > y_1$，$a+b \le x_1 \le a+b+len$，这也是一个矩形，用树状数组维护即可。

现在考虑其他方向的处理方法。我们定义两个翻转操作。

- $x$ 轴翻：以 $n \div 2$ 为对称轴，此时每个点 $y$ 坐标不变，$x$ 坐标变成 $n-x+1$。
- $y$ 轴翻转：以 $n \div 2$ 为对称轴，此时每个点 $x$ 坐标不变，$y$ 坐标变成 $n-y+1$。

$dis=2$ 时进行一次 $y$ 轴翻转，$dis=3$ 时进行一次 $x$ 轴翻转，$dis=4$ 时进行一次 $x$ 轴翻转再进行一次 $y$ 轴翻转。这样所有三角形都会到同一方向。

### code

```
#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) (x&(-x))
int n,q,t,d,x,y,l,tree[10005][5005],tree2[10005][5005];
struct node{int t,d,x,y,l,ans;};
vector<node> a;
void updata(int tree[][5005],int x,int y,int d)
{
	for(int i=x;i<=2*n;i+=lowbit(i))
		for(int j=y;j<=n;j+=lowbit(j))
			tree[i][j]+=d;
}
int getsum(int tree[][5005],int x,int y)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		for(int j=y;j;j-=lowbit(j))
			res+=tree[i][j];
	return res;
}
signed main()//define int long long后遗症。
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	while(q--)
	{
		cin>>t;
		if(t-1)cin>>x>>y,a.push_back({t,0,x,y,0,0});
		else cin>>d>>x>>y>>l,a.push_back({t,d,x,y,l,0});
	}
    //由于需要把点和三角形一起翻转，所以离线处理。
	for(int i=1;i<=4;i++)
	{
		memset(tree,0,sizeof tree);
		memset(tree2,0,sizeof tree2);
		for(node &j:a)
		{
			if(j.d&&j.d!=i)continue;
			int x=j.x,y=j.y,l=j.l;
			if(i==3||i==4)x=n-x+1;
			if(i==2||i==4)y=n-y+1;
			if(j.t-1)j.ans+=getsum(tree,x+y,y)-getsum(tree2,x+y,x);
			else
			{
				updata(tree,x+y,y,1);updata(tree,x+y+l+1,y,-1);
				updata(tree2,x+y,1,1);updata(tree2,x+y,x,-1);
				updata(tree2,x+y+l+1,1,-1);updata(tree2,x+y+l+1,x,1);
                //因为c++数组的两维和平面直角坐标系的两维相反，填进函数里时要反过来。
			}
		}
	}
	for(node i:a)if(i.t-1)cout<<i.ans<<endl;
	return 0;
}
```

---

