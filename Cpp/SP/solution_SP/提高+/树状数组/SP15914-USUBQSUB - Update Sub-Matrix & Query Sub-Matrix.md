# USUBQSUB - Update Sub-Matrix & Query Sub-Matrix

## 题目描述

Updating and querying 1 dimensional arrays is a popular question. How about updating and quering sub-matrices of a matrix?

A sub-matrix will be depicted as (a, b), (c, d). This implies that it will include all the cells (x, y) such that a<=x<=c and b<=y<=d.

The matrix is indexed from \[1..N\]\[1..N\], where N is the size.

You are given a matrix of size NxN, with each element initially set to 0. There are M queries and each query can be of one of the two types:

1 x1 y1 x2 y2: This query asks you to return the sum of all the elements in the sub-matrix (x1, y1), (x2, y2).

2 x1 y1 x2 y2 K: This query asks you to add K to each element in the sub-matrix (x1, y1), (x2, y2).

# 题解

## 作者：_H17_ (赞：5)

## 题目大意

给定 $N,M$ 表示 $N\times N$ 的矩阵和 $M$ 组询问。

矩阵出使均为 $0$。

操作是 `1 x1 y1 x2 y2` 表示查询子矩阵 $(x1,y1),(x2,y2)$ 的和，`2 x1 y1 x2 y2 k` 表示子矩阵 $(x1,y1),(x2,y2)$ 增加 $k$。

## 题目分析

矩阵查询和矩阵修改的模板问题。

对于这种问题一般我们可以用二维树状数组解决。

[前置知识：树状数组区间修改单点查询](/problem/P3368)。

在二维之前我们首先应当解决区间修改区间查询（[可以用线段树模板题练习](/problem/P3372)）。

既然可以差分那么求 $\sum_{i=l}^{r} a_i$ 的和可以变成求 $(\sum_{i=1}^{r} a_i)-(\sum_{i=1}^{l-1} a_i)$。

所以区间查询就变成求 $\sum_{i=1}^{f} a_i$。

由于单点查区间改的差分，我们的查询就变成 $\sum_{i=1}^{f} \sum_{j=1}^{i} a_i\newline =\sum_{i=1}^{f} a_i\times(f-i+1)\newline =\sum_{i=1}^f a_i \times(f+1)-\sum_{i=1}^f a_i\times i$

于是使用两个树状数组维护 $a_i$ 的和还有 $a_i\times i$ 的和。

## 区间查询区间修改代码

```cpp
#include<bits/stdc++.h>
#define int long long 
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int N=100001;
int n,m,a[N],b[N];
void add1(int x,int k){
    while(x<=n)
        a[x]+=k,x+=lowbit(x);
    return;
}
void add2(int x,int k){
    while(x<=n)
        b[x]+=k,x+=lowbit(x);
    return;
}
int qry1(int k){
    int ans=0;
    for(;k;k-=lowbit(k))
        ans+=a[k];
    return ans;
}
int qry2(int k){
    int ans=0;
    for(;k;k-=lowbit(k))
        ans+=b[k];
    return ans;
}
int qry(int k){
	return qry1(k)*(k+1)-qry2(k);
} 
int qry(int l,int r){
    return qry(r)-qry(l-1);
}
signed main(){
    cin>>n>>m;
    for(int i=1,k;i<=n;i++){
        cin>>k;
        add1(i,k),add1(i+1,-k);
        add2(i,k*i),add2(i+1,-k*(i+1));
    }
    for(int op,x,y,k;m;--m){
        cin>>op>>x>>y;
        if(op==1){
            cin>>k;
            add1(x,k),add1(y+1,-k);
            add2(x,k*x),add2(y+1,-k*(y+1));
        }
        else
            cout<<qry(x,y)<<'\n';
    }
    return 0;
}
```

## 加入二维

于是变为 $\sum_{i=1}^{f}\sum_{j=1}^{g}\sum_{k=1}^{i}\sum_{v=1}^{j} a_{k,v}\newline =\sum_{i=1}^{f}\sum_{j=1}^{g}\sum_{v=1}^{j} a_{i,v}\times(f-i+1)\newline =\sum_{i=1}^{f}\sum_{j=1}^{g} a_{i,v}\times(f-i+1)\times(g-j+1)\newline =\sum_{i=1}^{f}\sum_{j=1}^{g} a_{i,v}\times(f+1)\times(g+1)-\sum_{i=1}^{f}\sum_{j=1}^{g} a_{i,v}\times i\times(g+1)-\sum_{i=1}^{f}\sum_{j=1}^{g} a_{i,v}\times(f+1)\times j+\sum_{i=1}^{f}\sum_{j=1}^{g} a_{i,v}\times i\times j$。

于是开树状数组维护 $a_{i,j},a_{i,j}\times i,a_{i,j} \times j,a_{i,j}\times i \times j$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long 
#define y1 oiajdfoadfsdfafasfasdfas
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int N=(1<<12)+1;
int n,m,q,a[N][N];
long long b[N][N],c[N][N],d[N][N];
void add1(int x,int y,int k){
	int by=y;
    while(x<=n){
    	y=by;
        while(y<=n)
            a[x][y]+=k,y+=lowbit(y);
        x+=lowbit(x);
    }
    return;
}//aij
void add2(int x,int y,int k){
	int by=y;
    while(x<=n){
    	y=by;
        while(y<=n)
            b[x][y]+=k,y+=lowbit(y);
        x+=lowbit(x);
    }
    return;
}//aij*i
void add3(int x,int y,int k){
	int by=y;
    while(x<=n){
    	y=by;
        while(y<=n)
            c[x][y]+=k,y+=lowbit(y);
        x+=lowbit(x);
    }
    return;
}//aij*j
void add4(int x,int y,int k){
	int by=y;
    while(x<=n){
    	y=by;
        while(y<=n)
            d[x][y]+=k,y+=lowbit(y);
        x+=lowbit(x);
    }
    return;
}//aij*i*j
void add(int a,int b,int c,int d,int k){
    add1(a,b,k),add1(c+1,d+1,k),add1(a,d+1,-k),add1(c+1,b,-k);
    add2(a,b,k*a),add2(c+1,d+1,k*(c+1)),add2(a,d+1,-k*a),add2(c+1,b,-k*(c+1));
    add3(a,b,k*b),add3(c+1,d+1,k*(d+1)),add3(a,d+1,-k*(d+1)),add3(c+1,b,-k*b);
    add4(a,b,k*a*b),add4(c+1,d+1,k*(c+1)*(d+1)),add4(a,d+1,-k*a*(d+1)),add4(c+1,b,-k*b*(c+1));
}
int qry1(int x,int y){
    int ans=0,by=y;
    for(;x;x-=lowbit(x)){
        for(y=by;y;y-=lowbit(y))
            ans+=a[x][y];
	}
    return ans;
}
long long qry2(int x,int y){
    int ans=0,by=y;
    for(;x;x-=lowbit(x)){
        for(y=by;y;y-=lowbit(y))
            ans+=b[x][y];
	}
    return ans;
}
long long qry3(int x,int y){
    int ans=0,by=y;
    for(;x;x-=lowbit(x)){
        for(y=by;y;y-=lowbit(y))
            ans+=c[x][y];
	}
    return ans;
}
long long qry4(int x,int y){
    int ans=0,by=y;
    for(;x;x-=lowbit(x)){
        for(y=by;y;y-=lowbit(y))
            ans+=d[x][y];
	}
    return ans;
}
long long qry(int x,int y){
	return (1ll*qry4(x,y)-qry2(x,y)*(y+1))+(1ll*qry1(x,y)*(x+1)*(y+1)-qry3(x,y)*(x+1));
}
long long qry(int x1,int y1,int x2,int y2){
	return 1ll*qry(x1-1,y1-1)-qry(x1-1,y2)-qry(x2,y1-1)+qry(x2,y2);
}
signed main(){
    int op,a,b,c,d,k;
    cin>>n>>m;
    while(m--){
        cin>>op>>a>>b>>c>>d;
        if(op==2){
            cin>>k;
            add(a,b,c,d,k);
        }
        else
            cout<<qry(a,b,c,d)<<'\n';
    }
    return 0;
}
```

## 双倍经验

[上帝造题的七分钟](/problem/P4514)

---

## 作者：封禁用户 (赞：2)

二维树状数组的板子题，双倍经验 P4514，难度 $\color{White}\colorbox{Blue}{提高+/省选-}$。

上周天[教练](https://www.luogu.com.cn/user/224358)让我们自己研究[二维树状数组的区间加区间和](https://oi-wiki.org/ds/fenwick/#%E5%AD%90%E7%9F%A9%E9%98%B5%E5%8A%A0%E6%B1%82%E5%AD%90%E7%9F%A9%E9%98%B5%E5%92%8C)，于是有了这篇题解。

前置知识：初中数学，二维差分，不会自行百度。

## 思路

众所周知，二维差分中 $d$ 数组的定义为：$d_{i,j}=a_{i,j}-a_{i-1,j}-a_{i,j-1}+a_{i-1,j-1}$（因为原数组是差分数组的前缀和）。

点 $(i,j)$ 可以表示为 $\sum\limits_{h=1}^{i}\sum\limits_{k=1}^{j} d(h,k)$。

则区间 $([1,x],[1,y])$（$a_{x,y}$ 的二维前缀和）可以表示为 $\sum\limits_{i=1}^{x}\sum\limits_{j=1}^{y}\sum\limits_{h=1}^{i}\sum\limits_{k=1}^{j} d(h,k)$，不难发现每个 $d(h,k)$ 总共被加了 $(x-h+1)\times (y-k+1)$ 次。

可以使用类似于一维树状数组区间加\和的方式化简上面这个式子：

$$\begin{aligned} \sum\limits_{i=1}^{x}\sum\limits_{j=1}^{y}\sum\limits_{h=1}^{i}\sum\limits_{k=1}^{j} d(h,k) &=
\sum\limits_{i=1}^{x}\sum\limits_{j=1}^{y} d(i,j)\times (x-i+1)\times (y-j+1) \\ &= \sum\limits_{i=1}^{x}\sum\limits_{j=1}^{y} d(i,j)\times(xy+x+y+1)-d(i,j)\times i\times (y+1)-d(i,j)\times j\times (x+1)+d(i,j)\times i\times j\end{aligned}$$

所以我们需要维护 4 个树状数组，分别表示 $d(i,j)$，$d(i,j)\times i$，$d(i,j)\times j$，$d(i,j)\times i\times j$。

注意，在 $\texttt{update}$ 和 $\texttt{query}$ 函数中，需要使用初始的 $x$ 和 $y$ 而**不是**循环里的，因为循环中的 $i$ 和 $j$ 是在变化的。

## 参考网站

[OI Wiki](https://oi-wiki.org)

## 代码

```cpp
#include<iostream>
using namespace std;
#define lowbit(x) x&(-x)
#define int long long
int n,m;
const int N=1005;
int c1[N][N],c2[N][N],c3[N][N],c4[N][N];
void update(int x,int y,int num){
	for(int i=x;i<=n;i+=lowbit(i)){
		for(int j=y;j<=n;j+=lowbit(j)){
			c1[i][j]+=num;
			c2[i][j]+=num*x;
			c3[i][j]+=num*y;
			c4[i][j]+=num*x*y;
		}
	}
	return ; 
}
int query(int x,int y){
	int ans=0;
	for(int i=x;i;i-=lowbit(i)){
		for(int j=y;j;j-=lowbit(j)){
			ans+=(x+1)*(y+1)*c1[i][j]-(y+1)*c2[i][j]-(x+1)*c3[i][j]+c4[i][j];
		}
	}
	return ans;
}
signed main(){
	int x1,y1,x2,y2,z;
	cin>>n>>m;
	int op;
	while(m--){
		cin>>op;
		if(op==2){
			cin>>x1>>y1>>x2>>y2>>z;
			update(x1,y1,z);
			update(x1,y2+1,-z);
			update(x2+1,y1,-z);
			update(x2+1,y2+1,z);
		}
		else{
			cin>>x1>>y1>>x2>>y2;
			cout<<query(x2,y2)-query(x2,y1-1)-query(x1-1,y2)+query(x1-1,y1-1)<<endl;
		}
	}
	return 0;
} 
```

---

## 作者：yxans (赞：1)

## 题目大意
二维平面内 $m$ 次操作，操作分为矩阵修改，矩阵求和。

## 解法

首先不用想，肯定有很多做法是二维的树状数组，那么我来提供一种比较好想的分块做法。

考虑 $n\leq1\times10^3,m\leq1\times10^5$，发现 $m$ 比较大，于是我们考虑对询问分块。

不妨设块长为 $B$。我们每 $B$ 次操作暴力的维护一遍二维前缀和，对于查询操作，我们只需要 $O(1)$ 求和再暴力枚举上一次维护到现在中间的所有修改操作，加上贡献即可。

复杂度分析：$\frac{n}{B}(n^2+B)+mB\geq2\sqrt{m^2n^2}+m=2mn+m$ 差不多是 $2\times 10^8$ 级别的。

代码很简单就不提供了。

---

## 作者：whrwlx (赞：1)

注意到 $n \le 10^3$，发现暴力求二位前缀和过不去，正好最近学了根号分治，和 @yxans 讨论了一下。

我们可以对操作进行分块，每隔 $B$ 次操作用差分数组暴力 $O(n^2)$ 更新二维前缀，在块内的询问可以 $O(B)$ 枚举操作求出操作的贡献，再加上前缀和即为答案。

时间复杂度为 $O(mB+\frac{mn^2}{B}+m)$，取 $B=\sqrt{n}$ 最优，大概是 $2 \times 10^8$ 次运算，而且肯定跑不满。~~卡卡常可过~~

---

## 作者：zhengrunzhe (赞：0)

题意：矩形加，矩形求和

#### 算法1：我会K-D Tree

$$ O(m \sqrt {n^2})=O(nm) $$

~~懒得打~~

#### 算法2：我会二维线段树

$$O(m log^2 n)$$

~~+常数~~

~~打过了，tle~~

###算法3：我会二维树状数组

$$O(m log^2 n)$$

常数小，就过了

```cpp
#include<cstdio>
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
template<class type>inline const void write(type out)
{
	if (out<0)putchar('-'),out=-out;
	if (out>9)write(out/10);
	putchar(out%10+48);
}
typedef long long ll;
const int N=1e3+10;
int n,m;
class Binary_Indexed_Tree
{
	private:
    	ll c[N][N];
		inline const int lowbit(int x)
		{
			return x&-x;
		}
	public:
    	inline const void add(int x,int y,ll w)
    	{
        	for (;x<=n;x+=lowbit(x))
            	for (int i=y;i<=n;i+=lowbit(i))
                	c[x][i]+=w;
    	}
    	inline const ll query(int x,int y)
    	{
        	ll sum=0;
        	for (;x;x-=lowbit(x))
            	for (int i=y;i;i-=lowbit(i))
	                sum+=c[x][i];
    	    return sum;
    	}
}A,Ai,Aj,Aij;
inline const ll sum(int x,int y)
{
    return 
		A.query(x,y)*(x*y+x+y+1)
        -Ai.query(x,y)*(y+1)
        -Aj.query(x,y)*(x+1)
        +Aij.query(x,y);
}
inline const void add(int x,int y,int w)
{
    A.add(x,y,w);
    Ai.add(x,y,(ll)w*x);
    Aj.add(x,y,(ll)w*y);
    Aij.add(x,y,(ll)w*x*y);
}
int main()
{
	read(n);read(m);
	for (int opt,x1,y1,x2,y2,w;m--;)
		if (read(opt),read(x1),read(y1),read(x2),read(y2),opt==2)
			read(w),
        	add(x1,y1,w),
        	add(x1,y2+1,-w),
        	add(x2+1,y1,-w),
        	add(x2+1,y2+1,w);
        else write(sum(x2,y2)-sum(x1-1,y2)-sum(x2,y1-1)+sum(x1-1,y1-1)),putchar('\n');
    return 0;
}
```

---

