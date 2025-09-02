# Bear in the Field

## 题目描述

Our bear's forest has a checkered field. The checkered field is an $ n×n $ table, the rows are numbered from 1 to $ n $ from top to bottom, the columns are numbered from 1 to $ n $ from left to right. Let's denote a cell of the field on the intersection of row $ x $ and column $ y $ by record $ (x,y) $ . Each cell of the field contains growing raspberry, at that, the cell $ (x,y) $ of the field contains $ x+y $ raspberry bushes.

The bear came out to walk across the field. At the beginning of the walk his speed is $ (dx,dy) $ . Then the bear spends exactly $ t $ seconds on the field. Each second the following takes place:

- Let's suppose that at the current moment the bear is in cell $ (x,y) $ .
- First the bear eats the raspberry from all the bushes he has in the current cell. After the bear eats the raspberry from $ k $ bushes, he increases each component of his speed by $ k $ . In other words, if before eating the $ k $ bushes of raspberry his speed was $ (dx,dy) $ , then after eating the berry his speed equals $ (dx+k,dy+k) $ .
- Let's denote the current speed of the bear $ (dx,dy) $ (it was increased after the previous step). Then the bear moves from cell $ (x,y) $ to cell $ (((x+dx-1) mod n)+1,((y+dy-1) mod n)+1) $ .
- Then one additional raspberry bush grows in each cell of the field.

You task is to predict the bear's actions. Find the cell he ends up in if he starts from cell $ (sx,sy) $ . Assume that each bush has infinitely much raspberry and the bear will never eat all of it.

## 说明/提示

Operation $ a mod b $ means taking the remainder after dividing $ a $ by $ b $ . Note that the result of the operation is always non-negative. For example, $ (-1) mod 3=2 $ .

In the first sample before the first move the speed vector will equal (3,4) and the bear will get to cell (4,1). Before the second move the speed vector will equal (9,10) and he bear will get to cell (3,1). Don't forget that at the second move, the number of berry bushes increased by 1.

In the second sample before the first move the speed vector will equal (1,1) and the bear will get to cell (1,1). Before the second move, the speed vector will equal (4,4) and the bear will get to cell (1,1). Don't forget that at the second move, the number of berry bushes increased by 1.

## 样例 #1

### 输入

```
5 1 2 0 1 2
```

### 输出

```
3 1```

## 样例 #2

### 输入

```
1 1 1 -1 -1 2
```

### 输出

```
1 1```

# 题解

## 作者：General0826 (赞：54)

~~蒟蒻第一篇题解~~

 * * *
### 算法分析：


------------
由于 $t$ 过于大，并更新多个状态。这很不然让人想到矩阵快速幂。   
###  坑点：  
$dx$ 和 $dy$ ，不是 $\bmod P$ ，而是 $-1$ 再 $\bmod P$ 然后 $+1$ ，我们平移通过解决 ，并有可能出现负数，因把 $x \bmod P$ ，都换成 $(x \bmod P+P)\bmod P$  。
分析样例和注解发现是先加速度，再移动的。我们为简单先一个一个设计。
#### 状态：
因有当前 $x$ ，$y$ ，$x$ 速度，$y$ 速度，时间，常数 $1$，一个初始向量为:
$$
V=
\begin{pmatrix}
  sx-1 \\
  sy-1 \\
  dx \\
  dy \\
  0  \\
  1  \\
\end{pmatrix}
$$
这里减一，因为平移了。  
#### 2.加速度
$$B=
\begin{bmatrix}
   1 & 0& 0& 0& 0& 0 \\
   0 & 1& 0& 0& 0& 0 \\
   1 & 1& 1& 0& 1& 2 \\
   1 & 1& 0& 1& 1& 2 \\
   0 & 0& 0& 0& 1& 0 \\
   0 & 0& 0& 0& 0& 1 \\ 
\end{bmatrix}
$$
这里要特殊说明一下为什么 $dx,dy$ 需要 $+2$ ，因为 $x,y$ 都往上或左移了一位，需要加回来，权值记得加上时间。
3.移动
$$A=
\begin{bmatrix}
   1 & 0& 1& 0& 0& 0 \\
   0 & 1& 0& 1& 0& 0 \\
   0 & 0& 1& 0& 0& 0 \\
   0 & 0& 0& 1& 0& 0 \\
   0 & 0& 0& 0& 1& 1 \\
   0 & 0& 0& 0& 0& 1 \\ 
\end{bmatrix}
$$
非常的简单，同时更新时间  
所以更新一次因先乘 $B$ 在乘 $A$ ，那么：$C=AB$ 记住一定是 $AB$，不是 $BA$ ，然后算 $C^t V$ ，去前俩项输出(记得加一)


------------
### 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int VZ=6;
int P;
struct node
{
	long long a[VZ][VZ];
}; 
vector<ll> vec_ts_jz(ll c[],node d)
{
	vector<ll> a;
	for(ll i=0;i<VZ;i++) a.push_back(0);
	for(ll i=0;i<VZ;i++)
		for(ll j=0;j<VZ;j++)
			a[i]=((a[i]+c[j]*d.a[i][j]%P)%P+P)%P;
	return a;	
}
node cf(node a,node b)
{
	node c;
	for(int i=0;i<VZ;i++)
		for(int j=0;j<VZ;j++)
			c.a[i][j]=0;
	for(int i=0;i<VZ;i++)
		for(int j=0;j<VZ;j++)
			for(int k=0;k<VZ;k++)
				c.a[i][j]=((c.a[i][j]+(a.a[i][k]*b.a[k][j]+P)%P)%P+P)%P;
	return c;
}
node vec_pow_q(node n,long long x)
{
	node num=n,cnt;
	for(int i=0;i<VZ;i++)
		for(int j=0;j<VZ;j++)
			cnt.a[i][j]=0;
	for(int i=0;i<VZ;i++)
		cnt.a[i][i]=1;
	while(x)
	{
		if(x&1) cnt=cf(cnt,num);
		x=x>>1;
		num=cf(num,num);
	}
	return cnt;
	
}
ll n;
int sx,sy,dy,dx;
long long t;
void work()
{
	cin>>P>>sx>>sy>>dx>>dy>>t;
  	node A=(node)
	{{
	{1,0,1,0,0,0},
	{0,1,0,1,0,0},
	{0,0,1,0,0,0},
	{0,0,0,1,0,0},
	{0,0,0,0,1,1},
	{0,0,0,0,0,1} 	
	}};
  	node B=(node){{
	{1,0,0,0,0,0},
	{0,1,0,0,0,0},
	{1,1,1,0,1,2},
	{1,1,0,1,1,2},
	{0,0,0,0,1,0},
	{0,0,0,0,0,1} 	
	}};
	node C=cf(A,B);
  	node o=vec_pow_q(C,t);
	ll rt[]={sx-1,sy-1,dx,dy,0,1};
	vector<ll>tu=vec_ts_jz(rt,o);
  	cout<<tu[0]+1<<' '<<tu[1]+1;
}

int main() {
	work();
  	return 0;
}
```

---

## 作者：是个汉子 (赞：4)

呜呜呜，调了我一下午的矩阵快速幂。(；′⌒`)

### Solution

首先，我们将题目的意思模拟一下，可以得到：
$$
dx_i=dx_{i-1}+sx_{i-1}+sy_{i-1}+i-1,\\dy_i=dy_{i-1}+sx_{i-1}+sy_{i-1}+i-1,\\sx_i=sx_{i-1}+dx_i,sy_i=sy_{i-1}+dy_i
$$
但是因为要 $\%n$ ，所以坐标从 $1\sim n$ 到了 $0\sim n-1$ ，那么我们的速度此时会少2，因此再加上一个2。

于是就有：
$$
dx_i=dx_{i-1}+sx_{i-1}+sy_{i-1}+(i-1)+2\\dy_i=dy_{i-1}+sx_{i-1}+sy_{i-1}+(i-1)+2\\sx_i=sx_{i-1}+dx_i=2\times sx_{i-1}+dx_{i-1}+sy_{i-1}+(i-1)+2,\\sy_i=sy_{i-1}+dy_i=2\times sy_{i-1}+dy_{i-1}+sx_{i-1}+(i-1)+2
$$
下一步，我发现 $0\le t\le 10^{18}$ ，于是想到了**矩阵快速幂**，发现的确 $sx,sy,dx,dy,i$ 都和上一步有关系，那么转移矩阵就出来了：
$$
\begin{bmatrix}2~~~1~~~1~~~0~~~1~~~2\\1~~~2~~~0~~~1~~~1~~~2\\1~~~1~~~1~~~0~~~1~~~2\\1~~~1~~~0~~~1~~~1~~~2\\0~~~0~~~0~~~0~~~1~~~1\\0~~~0~~~0~~~0~~~0~~~1\end{bmatrix}
$$

初始矩阵也有：
$$
\begin{bmatrix}sx_0\\sy_0\\dx_0\\dy_0\\0\\1\end{bmatrix}
$$
然后就是：
$$
\begin{bmatrix}sx_n\\sy_n\\dx_n\\dy_n\\t\\1\end{bmatrix}=\begin{bmatrix}2~~~1~~~1~~~0~~~1~~~2\\1~~~2~~~0~~~1~~~1~~~2\\1~~~1~~~1~~~0~~~1~~~2\\1~~~1~~~0~~~1~~~1~~~2\\0~~~0~~~0~~~0~~~1~~~1\\0~~~0~~~0~~~0~~~0~~~1\end{bmatrix}^t\begin{bmatrix}sx\\sy\\dx\\dy\\0\\1\end{bmatrix}
$$
其实最后只需要 $sx_n,sy_n$ ，所以转移完只需要单独算一下前两个就行了。

### 代码

```C++
#include<bits/stdc++.h>
#define int long long

using namespace std;
const int N=15;
int n,sx,sy,dx,dy,t,mod,y[N];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

inline int add(int a,int b){return a+b<mod?a+b:a+b-mod;}
inline int sub(int a,int b){return a<b?a-b+mod:a-b;}
inline int mul(int a,int b){return 1ll*a*b%mod;}

inline fpow(int a,int b){
    int res=1;
    while(b){   
        if(b&1) res=mul(res,a);
        a=mul(a,a);
        b>>=1;
    }
    return res;
}

struct matrix{
    int a[N][N];
    matrix(){memset(a,0,sizeof(a));}
    matrix operator * (const matrix &x) const {
        matrix ans;
        for(int i=1;i<=6;i++)
            for(int j=1;j<=6;j++)
                for(int k=1;k<=6;k++)
                    ans.a[i][j]=add(ans.a[i][j],mul(a[i][k],x.a[k][j]));
        return ans;
    }
}I;

matrix Fpow(matrix a,int b){
    matrix res;
    for(int i=1;i<=6;i++) res.a[i][i]=1;
    while(b){
        if(b&1) res=res*a;
        a=a*a;
        b>>=1;
    }
    return res;
}

inline void init(){
    y[1]=sx-1,y[2]=sy-1,y[3]=dx,y[4]=dy,y[5]=0,y[6]=1;
    I.a[1][1]=I.a[2][2]=I.a[1][6]=I.a[2][6]=I.a[3][6]=I.a[4][6]=2;
    I.a[1][2]=I.a[1][3]=I.a[1][5]=I.a[2][1]=I.a[2][4]=I.a[2][5]=I.a[3][1]=I.a[3][2]=I.a[3][3]=
    I.a[3][5]=I.a[4][1]=I.a[4][2]=I.a[4][4]=I.a[4][5]=I.a[5][5]=I.a[5][6]=I.a[6][6]=1;
}

signed main(){
    scanf("%lld%lld%lld%lld%lld%lld",&n,&sx,&sy,&dx,&dy,&t);
    if(t==0){
        printf("%lld %lld",sx,sy);
        return 0;
    }
    mod=n;
    init();
    I=Fpow(I,t);
    int ex=0,ey=0;
    for(int i=1;i<=6;i++)
        ex=((ex+I.a[1][i]*y[i])%mod+mod)%mod;
    for(int i=1;i<=6;i++)
        ey=((ey+I.a[2][i]*y[i])%mod+mod)%mod;
    printf("%lld %lld",ex+1,ey+1);
    return 0;
}
```



---

## 作者：OceanLiu (赞：0)

Upd:转移矩阵中最后一个数打错了，已修改。十分抱歉QAQ

好久没有写矩阵了，写挂了好几次QAQ。几乎所有的坑都跳了一遍……

题目大意：给定一个$n \times n$的矩阵，坐标为$(x,y)$的格子的权值为$x+y$。一个人初始在$(sx,sy)$处，初始速度为$(dx,dy)$，他下一秒能到达的地方为$((x+dx-1)\mod n+1,(y+dy-1)\mod n+1)$。当人到达一个地方$(x,y)$时，他的速度将会变为$(dx+x+y,dy+x+y)$。每秒钟所有格子内的权值都会加$1$。问$t$秒后人所在的位置。

正解：矩阵快速幂。

设$sx(i)$表示第$i$秒时人所在格子的横坐标，$sy(i)$表示所在格子的纵坐标；$dx(i)$表示第$i$秒时人的横向速度，$dy(i)$表示第$i$秒时的纵向速度。根据题意有：
$dx(t)=dx(t-1)+sx(t-1)+sy(t-1)+t-1$

$dy(t)=dy(t-1)+sx(t-1)+sy(t-1)+t-1$

（别忘了每秒钟格子的权值会加$1$）

同时根据题意有：

$sx(t)=sx(t-1)+dx(t)$

$sy(t)=sy(t-1)+dy(t)$

考虑取余操作，这使得$\mod n$后的值只可能在$[0,n-1]$中。所以我们不妨平移人，将人的位置分别往上，往左移动一格。这样坐标就变为了$(sx-1,sy-1)$。但这样会导致速度比原来的速度少$2$，所以要在原来的式子中加上$2$。这样我们有：

$dx(t)=dx(t-1)+sx(t-1)+sy(t-1)+t-1+2$

$dy(t)=dy(t-1)+sx(t-1)+sy(t-1)+t-1+2$

将$dx(t),dy(t)$代入$sx(t),sy(t)$中，得到：

$sx(t)=2\times sx(t-1)+dx(t-1)+sy(t-1)+t+1$

$sy(t)=2\times sy(t-1)+dy(t-1)+sx(t-1)+t+1$

考虑构造转移矩阵，我们有：

$\begin{bmatrix} sx(t-1) \\ sy(t-1)\\dx(t-1)\\dy(t-1)\\t-1\\1 \end{bmatrix}$ $\times$ $\begin{bmatrix} 2&1&1&0&1&2  \\ 1&2&0&1&1&2\\1&1&1&0&1&2\\1&1&0&1&1&2\\0&0&0&0&1&1\\0&0&0&0&0&1\end{bmatrix}$ $=$ $\begin{bmatrix} sx(t) \\ sy(t)\\dx(t)\\dy(t)\\t\\1 \end{bmatrix}$

矩阵快速幂处理即可。时间复杂度$O(216\log_2t)$。

代码：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
int n,sx,sy,dx,dy,t,y[10],p;
struct node
{
	int a[10][10];
	node(){
		memset(a,0,sizeof(a));
	}
	inline void build(){
		for (int i=1;i<=6;i++) a[i][i]=1;
	}
}x;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline void init()
{
	x.a[1][1]=2;x.a[1][2]=1;x.a[1][3]=1;x.a[1][4]=0;x.a[1][5]=1;x.a[1][6]=2;
	x.a[2][1]=1;x.a[2][2]=2;x.a[2][3]=0;x.a[2][4]=1;x.a[2][5]=1;x.a[2][6]=2;
	x.a[3][1]=1;x.a[3][2]=1;x.a[3][3]=1;x.a[3][4]=0;x.a[3][5]=1;x.a[3][6]=2;
	x.a[4][1]=1;x.a[4][2]=1;x.a[4][3]=0;x.a[4][4]=1;x.a[4][5]=1;x.a[4][6]=2;
	x.a[5][1]=0;x.a[5][2]=0;x.a[5][3]=0;x.a[5][4]=0;x.a[5][5]=1;x.a[5][6]=1;
	x.a[6][1]=0;x.a[6][2]=0;x.a[6][3]=0;x.a[6][4]=0;x.a[6][5]=0;x.a[6][6]=1;
	y[1]=sx-1;y[2]=sy-1;y[3]=dx;y[4]=dy;y[5]=0;y[6]=1;
}
node operator * (const node x,const node y)
{
	node z;
	for (int i=1;i<=6;i++)
		for (int j=1;j<=6;j++)
			for (int k=1;k<=6;k++)
				z.a[i][j]=(z.a[i][j]+x.a[i][k]*y.a[k][j]%p+p)%p;
	return z;
}
signed main()
{
	//freopen("data.in","r",stdin);
	//freopen("ans.out","w",stdout); 
	n=read(),sx=read(),sy=read(),dx=read(),dy=read(),t=read();p=n;
	if (t==0)
	{
		printf("%lld %lld",sx,sy);
		return 0;
	}
	init();
	node ans;ans.build(); 
	while(t)
	{
		if (t&1) ans=ans*x;
		x=x*x;
		t>>=1;
	}
	int tx=0,ty=0;
	for(int i=1;i<=6;i++)
		tx=(tx+y[i]*ans.a[1][i]%p+p)%p,
		ty=(ty+y[i]*ans.a[2][i]%p+p)%p;
	printf("%lld %lld",tx+1,ty+1);
	return 0;
}
```


---

