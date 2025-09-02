# [ARC152D] Halftree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc152/tasks/arc152_d

頂点に $ 0 $ から $ N-1 $ までの番号がついた $ N $ 頂点の無向グラフがあり、はじめ、辺はありません。 このグラフに、あなたは好きなように辺を追加することができます。 そして、あなたが辺をすべて追加し終えた後に、与えられる $ K $ を用いて以下の操作がちょうど $ 1 $ 回行われます。

- あなたが追加した各辺について、両端の頂点を $ u,v $ とするとき、 $ 2 $ 頂点 $ (u+K) $ $ \mathrm{mod} $ $ N $ と $ (v+K) $ $ \mathrm{mod} $ $ N $ の間に辺が追加される。 ただし、この $ 2 $ 頂点間にもともと辺が存在する場合も新しく辺が追加されるため、その場合は操作後には多重辺となる。
 
与えられた $ N,K $ に対して、操作後のグラフが木となるようにするとき、あなたが追加するべき辺の組を求めてください。 そのような辺の組が存在しない場合はそのことを指摘してください。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ K\leq\ N-1 $
- 入力される値はすべて整数である
 
### Sample Explanation 1

操作を行うと、辺 $ 4 $-$ 0 $ と $ 4 $-$ 1 $ が追加されます。 したがって、木が生成されますので、これは正当な出力の $ 1 $ つとなります。

### Sample Explanation 2

操作後のグラフが木となるような方法が存在しません。

## 样例 #1

### 输入

```
5 2```

### 输出

```
2
2 3
2 4```

## 样例 #2

### 输入

```
2 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
7 1```

### 输出

```
3
0 1
2 3
4 5```

# 题解

## 作者：bobo2007 (赞：14)

### 题意

有 $n$ 个点 $0,1,2 \dots n-1$ 和一个参数 $k$，你需要连接若干条无向边，使得将这些点连成一棵**树**，连边规则如下：

- 选择 $u,v$ 两点，同时连接点 $u$ 和 $v$，点 $(u+k) \bmod n $ 和 $(v+k) \bmod n$ 

注意可能存在重边，这时重边算作多条边。

求一个合法的构造方案或输出无解。

数据范围：$1 \le n \le 2 \times 10^5,1 \le k \le n-1$ 且 $n,k \in Z$ 

### 题解

一个较为易懂的方法。

首先由于每次都要连两条边，$n$ 个点的树有 $n-1$ 条边，所以当点数 $n$ 为偶数时，要连接奇数条边，此时一定无解。

定义点 $x$ 对应的点 $(x+k) \bmod n $ 为 $next_x$，则连边时要同时连接 $x,y$ 和 $next_x,next_y$，选定任意一个 $x$ 不断跳到 $next_x$ 经过若干个点后一定会回到 $x$，这样会形成若干个环，再把环在任意地方断开，列成一个矩阵，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/f2qb3s4g.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这个矩阵有个性质，就是长宽点数一定是奇数，这在后面的做法里起到了作用。

这样我们每连接两个点，就必须连接这条线段向右平移一个的两个点，如果处于边界就回到第一个点。

接下来以 $n=25,k=5$ 为例

![](https://cdn.luogu.com.cn/upload/image_hosting/2vgdbo7u.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

假设我们连接点 `0` 和点 `1`，那么就会顺带将点 `5` 和点 `6` 连接起来。

第一步，我们斜对角连线，由于另一条边是将连的边每个端点向右平移一格生成的，因此我们可以以一种“奇偶分类”的方式得到如下的连边。

![](https://cdn.luogu.com.cn/upload/image_hosting/1hn7dlsx.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

其中蓝色的边代表先连的边，绿色的代表生成的边，这样，我们就得到了若干条链。

接下来要考虑将这些链连接起来。

一种方法是竖着连，第一二行从第二列开始交替连，这样可以把右上的“链三角”连接上来。

然后从第二行开始，将相邻两行一一配对连接，这样可以把左下角连起来。

根据矩阵点数的性质，第一二行的竖边一定是偶数条，可以两两交替连。

![img](https://cdn.luogu.com.cn/upload/image_hosting/o1xa97n1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

最后注意当只有一行的时候，直接特判连接这一行。

然后就过了这道题。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,nxt[200010];
int main()
{
    scanf("%d%d",&n,&k);
    if(!(n&1)) {printf("-1");return 0;}
    printf("%d\n",n>>1);
    int i,j,len=1,tot,p=k,x,y;
    while(p!=0) len++,p=(p+k)%n;
    tot=n/len;
    for(i=0;i<n;i++) nxt[i]=(i+k)%n;
    if(tot==1)
    {
        for(i=1,x=0;i<len;i+=2,x=nxt[nxt[x]]) printf("%d %d\n",x,nxt[x]);
        return 0;
    }
    for(i=0;i<tot-1;i++)
        for(j=2,x=i,y=nxt[i+1];j<len;j+=2,x=nxt[nxt[x]],y=nxt[nxt[y]])
            printf("%d %d\n",x,y);
    for(i=2,x=nxt[0],y=nxt[1];i<=len;i+=2,x=nxt[nxt[x]],y=nxt[nxt[y]])
        printf("%d %d\n",x,y);
    for(i=1;i<tot;i+=2) printf("%d %d\n",i,i+1);
    return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：7)

## 思路

$n$ 为偶数无解，因为要连奇数条边。

显然会裂成 $\gcd(n,k)$ 个环，每个环 $n\over\gcd(n,k)$ 个点。按以下方式连边：

![图炸了](https://cdn.luogu.com.cn/upload/image_hosting/6hp71qa0.png)

注：

1. 我这样摆放节点，是强调有三个环，每个环有五个点。
1. 红红边要输出，橙橙边是用红红边 $+k$ 自动连的。
1. 只看黑边，会形成红橙两个联通块和散的黑点。
1. 蓝边只在最后两个环之间连。
1. 应该是 $0$ 下标的。。。
1. 有点抽象，建议佐码食用。
1. 建议你自己尝试手画五个环，每个环七个点的情况。

## code

```cpp
#include<stdio.h>
int n,m;
inline int gcd(const int&x,const int&y){if(y)return gcd(y,x%y);return x;}
main()
{
	scanf("%d%d",&n,&m);
	if(!(n&1)){printf("-1");return 0;}
	int g=gcd(n,m);
	printf("%d\n",n-1>>1);
	if(g==1)
	{
		for(int j=0;(j+m)%n;j=(j+m+m)%n)
			printf("%d %d\n",j,(j+m)%n);
		return 0;
	}
	for(int i=0;i<g;++i)
	{
		for(int j=i;(j+m+m+m)%n^i;j=(j+m+m)%n)
			printf("%d %d\n",j,(j+m+m)%n);
		if(i<g-1)
		{
			printf("%d %d\n",i,i+1);
			if(!(i&1)||i==g-2)
				printf("%d %d\n",(i-m-m+n+n)%n,((i-m-m+n+n)%n+m+1)%n);
		}
	}
}
```


---

## 作者：jijidawang (赞：4)

首先 $n$ 是偶数显然无解，下面说明 $n$ 是奇数必然有解 .

直接构造，对于每个数 $x$ 连边 $x\to(x+k)\bmod n$ 形成 $d=\gcd(n,k)$ 个置换环，将每个置换环中最小的一个放到最前面，这样就可以排成一个 $d\times\dfrac nd$ 矩阵 $\{\{a\}\}$ .

考虑最后一列单独处理一下，就先连前 $\dfrac nd-1$ 列，只需要连 $(a_{1,i},a_{2,i}),(a_{2,i},a_{3,i}),\cdots,(a_{d-1,i},a_{d,i})$ 即可，其中 $i$ 是小于 $\dfrac nd$ 的奇数 .

这样就整出来 $\dfrac nd-1$ 条链，考虑把这些链连起来，连 $(a_{1,1},a_{1,2}),(a_{1,3},a_{1,4}),\cdots,(a_{1,n/d-2},a_{1,n/d-1})$ 即可 . 注意这时候我们顺便把最后一列的第一个元素也连了 .

现在最后一列的奇偶性实际上被修正了，这样就可以直接连了，具体构造方案是 $(a_{2,n/d},a_{3,n/d-1}),(a_{4,n/d},a_{5,n/d-1}),\cdots,(a_{d-1,n/d},a_{d,n/d-1})$ .

手玩一个矩阵出来看这个构造方案其实挺直观的，要看图可以去 Official Editorial .

构造的时间复杂度为 $\Theta(n)$（也就是不算求 GCD 的时间复杂度）.

```cpp
const int N = 2e5 + 500;
inline int gcd(int a, int b){return b ? gcd(b, a % b) : a;}
int n, k;
int main()
{
	scanf("%d%d", &n, &k); int d = gcd(n, k);
	if (n & 1 ^ 1){puts("-1"); return 0;}
	printf("%d\n", (n-1) / 2);
	vector<vector<int> > a(d+1, vector<int>(n/d+1));
	for (int i=1; i<=d; i++)
	{
		a[i][1] = i-1;
		for (int j=2; j<=n/d; j++) a[i][j] = (a[i][j-1] + k) % n;
	}
	for (int i=1; i<d; i++)
		for (int j=1; j<n/d; j+=2) printf("%d %d\n", a[i][j], a[i+1][j]);
	for (int i=1; i<=n/d-2; i+=2) printf("%d %d\n", a[1][i], a[1][i+1]);
	for (int i=2; i<d; i+=2) printf("%d %d\n", a[i][n/d], a[i+1][n/d-1]);
	return 0;
}

```

---

## 作者：hxhhxh (赞：1)

## 题意
给定 $n,k$，有一个 $n$ 个点的图，点编号为 $0\sim n-1$.图初始为空，你需要做若干次操作，使得图变为一颗树，或说明无解。

> 操作：选择两个数 $x,y$，连边 $(x,y)$，$((x+k)\bmod n,(y+k)\bmod n)$。

$1\leq n\leq 2\times 10^5$，$1\leq k < n$。

## 做法

$n$ 个点的数有 $n-1$ 条边，而操作每次都会加两条边，所以当 $n$ 为偶数时无解。下记 $d=\gcd(n,k)$。

当 $n$ 为奇数时，考虑将 $i\to (i+k)\bmod n$ 的边加在图上会发生什么。当 $d=1$ 时，裴蜀定理告诉我们所有点都在同一个环上；当 $d>1$ 时，$+\ k$ 对模 $d$ 的余数不会变，它会形成 $d$ 个环。

把他排得好看一点，比如像下面这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/31t7pu1i.png)

这是 $n=35,k=10,d=5$ 的情况。

首先，这样的图一定有奇数个环和奇数条射线（由于 $n$）是奇数。在这样的图上，操作相当于连一条边，将它绕中心顺时针旋转 $\frac{2d\pi}{n}$，然后再连旋转后的边。下面把选的边 $(x,y)$ 标红，$((x+k)\bmod n,(y+k)\bmod n)$ 标蓝。

先把大部分射线上的所有点连起来：

![](https://cdn.luogu.com.cn/upload/image_hosting/x84wftwm.png)

由于射线的个数是奇数，这样一定会剩下一条。考虑如何把这些链连起来：

![](https://cdn.luogu.com.cn/upload/image_hosting/p4os5gth.png)

注意到，这里剩下的那一条射线的第一个点被我们接入树里了。接下来我们还剩偶数个点。像这样构造：

![](https://cdn.luogu.com.cn/upload/image_hosting/6e921acl.png)

到这里我们就完成了 $n=35,k=5$ 的构造。把它加以推广就可以对于任何 $n,k$ 都构造出来了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,d;
vector<array<int,2> >p;
signed main(){
	cin>>n>>k;
	if(n%2==0) return puts("-1"),0;//唯一的无解情况
	d=__gcd(n,k);
	printf("%lld\n",n/2);
	auto add=[&](int x,int y){p.push_back({x,y});};//add(x,y)表示选择 (x,y)
	for(int j=0;j<n/d-1;j+=2) add(j*k%n,(j+n-1)*k%n);//第一个环
	for(int i=1;i<d;i++){
		for(int j=0;j<n/d-1;j+=2) add((j*k+i-1)%n,(j*k+i)%n);//连接第 i-1 个环和第 i 个环
		if(i&1) add((i-k-k+n+n)%n,(i-k+n+1)%n);//最后一步的构造
	}
	for(auto i:p) printf("%lld %lld\n",i[0],i[1]);
}
```

---

## 作者：Nightingale_OI (赞：0)

## 思路

一棵 $n$ 个点的树有 $n-1$ 条边，所以，而我们需要连一半的边，所以 $n$ 是偶数无解。

记 $p_x=(x+k)\bmod n$。当我们连一条边 $(x,y)$，会一并得到边 $(p_x,p_y)$。

将 $x\to p_x$ 构成的环拆出来，每个环点数相同，对应好铺到平面上（同层点逆时针是 $x\to p_x$）。

由于 $n$ 是奇数，所以一定是奇数个环、每个环有奇数个点。下图是 $n=35,k=5$。

![](https://cdn.luogu.com.cn/upload/image_hosting/zicmagjz.png)

当我们连一条边 $(x,y)$，会一并得到边 $(p_x,p_y)$。对应到平面上，当我们连一条边（红色）时，会得到其绕中心逆时针旋转一格对应的边（蓝色）。

![](https://cdn.luogu.com.cn/upload/image_hosting/90qogkfa.png)

如果只有一个环是简单的，构造是：

![](https://cdn.luogu.com.cn/upload/image_hosting/nde00jlp.png)

由于一共有奇数个环，我们每次加入两个环并将其连通：

![](https://cdn.luogu.com.cn/upload/image_hosting/pgfrhlax.png)

有各种加入两个环的方式，但是这样没有斜着的边，比较好看。

![](https://cdn.luogu.com.cn/upload/image_hosting/6whfls54.png)

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(int i=j;i<=k;++i)
#define g(i,j,k) for(int i=j;i>=k;--i)
int n,m,s,l;
const int N=3e5;
vector<int>q[N];
int a[N],b[N],v[N],k;
signed main(){
	cin>>n>>k;
	if(n%2==0)cout<<"-1\n",exit(0);
	f(i,0,n-1)if(!v[i]){
		q[++m]={0};
		for(s=i;!v[s];v[s]=1,s=(s+k)%n)q[m].push_back(s);
	}
	s=q[1].size()-1;
	f(i,1,m){
		if(i&1){
			f(j,1,s/2)a[++l]=q[i][j*2-1],b[l]=q[i][j*2];
		}else{
			f(j,1,s/2)a[++l]=q[i][j*2],b[l]=q[i-1][j*2];
			a[++l]=q[i][s];b[l]=q[i+1][s];
		}
	}
	printf("%lld\n",l);
	f(i,1,l)printf("%lld %lld\n",a[i],b[i]);
	return 0;
}
```

---

