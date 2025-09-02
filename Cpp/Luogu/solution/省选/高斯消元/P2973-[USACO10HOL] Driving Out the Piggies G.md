# [USACO10HOL] Driving Out the Piggies G

## 题目描述

奶牛们制造了一种随机臭弹，目的是驱赶小猪。小猪文明由 $ N (2 \leq N \leq 300) $ 个小猪城市组成，这些城市编号为 1 到 N，通过 $ M (1 \leq M \leq 44,850) $ 条双向道路连接，具体由它们的不同端点 $A_j$ 和 $B_j$ 指定 $ (1 \leq A_j \leq N; 1 \leq B_j \leq N) $。小猪城市 $1$ 总是与至少一个其他城市相连。

臭弹在小猪城市 $1$ 部署。每小时（包括第一小时），它有 $P/Q (1 \leq P \leq 1,000,000, 1 \leq Q \leq 1,000,000; P \leq Q) $ 的概率爆炸并污染它所在的城市。如果它没有爆炸，它会随机选择一条通往其他城市的道路并沿着它走，直到到达一个新城市。所有从一个城市出发的道路被选择的概率相同。

由于臭弹的随机性质，奶牛们想知道哪些城市最有可能被污染。给定小猪文明的地图以及臭弹在每个小时内爆炸的概率，计算每个城市被污染的概率。

例如，假设小猪文明由两个城市组成并且相连，臭弹从城市 $1$ 开始，每次进入一个城市时有 $\frac12$ 的概率爆炸：

1--2

我们有以下可能的臭弹路径（最后一个城市是终点城市）：

1: 1

2: 1-2

3: 1-2-1

4: 1-2-1-2

5: 1-2-1-2-1

等等。
要找到臭弹最终停留在城市 $1$ 的概率，我们可以将上述每条路径的概率相加（具体来说，就是上述列表中每一个奇数编号的路径）。选择第 $k$ 条路径的概率正好是 $(1/2)^k$ ——臭弹必须在前 $k-1$ 次不留在它的城市（每次概率为 $1-\frac12=\frac12$），然后在最后一个城市停留（概率为 $\frac12$）。

因此，我们在城市 $1$ 停留的概率由无穷级数 $\displaystyle\sum_{2\nmid k}\left(\frac12\right)^k$ 表示。当我们无限地求和这些项时，最终得到的概率恰好是 $\frac23$，大约为 $0.666666667$。这意味着在城市 $2$ 停留的概率是 $\frac13$，大约为 $0.333333333$。

## 说明/提示

感谢 @[Alpha](https://www.luogu.com.cn/user/87058) 贡献 Special Judge。

## 样例 #1

### 输入

```
2 1 1 2 
1 2 
```

### 输出

```
0.666666667 
0.333333333 
```

# 题解

## 作者：jun头吉吉 (赞：29)

# P2973 [USACO10HOL]Driving Out the Piggies G
## 题意
给出一张$n$个点，$m$条边的无向图，节点$1$有一个炸弹，在每个单位时间内，有$\dfrac {p}{ q}$的概率在这个节点炸掉，有$1-\dfrac{p}q$的概率随机选择一条出去的路到其他的节点上，去每个节点的概率相等。问最终炸弹在每个节点上爆炸的概率。
## 题解
~~考场上做到这道题，一脸蒙蔽~~

我们看一下下面这个~~与本题无关~~例子：

> 小明、小红、小芳在通过手心手背的游戏来决定哪两个人先出场，若有两个人同时出手心或手背那就让那两个人出场，否则重复游戏。**问：小明与小红先出场的概率是多少？**

>很容易地我们知道，第一局有$\dfrac 1 4$的可能是小明与小红先出场，也有可能是$\dfrac14$的概率重开一局，再下一局也是如此。因此我们可以设小明与小红先出场的概率为$x$，显然：
$$x=\frac14+\frac14x$$


那么这两题有什么相同点呢？由于两题都没有限制次数，因此我们无法通过有限次便利得到答案。那我们就根据上一题的方法：设未知数

我们假设到第$i$个点的概率为$x_i$，入度为$d_i$，那么考虑其是炸弹可以从哪里来：

- 如果这个点是$1$号点，那么其概率是一开始的炸弹爆炸或者是与它相连的点的如果不爆炸就会炸弹就有可能转一到这个点，即：
$$x_1=\dfrac pq+\sum_{(1,j)\in E}x_j \times (1-\dfrac p q)\times\dfrac 1 d_j$$

- 如果这个点是其他点，那就只能从相邻的点转移过来
$$x_i=\sum_{(i,j)\in E}x_j \times (1-\dfrac p q)\times\dfrac 1 d_j$$

式中$p$、$q$、$d$均为常数，因此所有的柿子可以组成一个$n$元一次方程组然后就到了我们喜闻乐见的~~手解300元方程~~高斯消元的过程了

```cpp
#include<bits/stdc++.h> 
#define maxn 310
#define eps (1e-6)
using namespace std;
int n,m,p,q,x,y;
int f[310][310];
int in[310];
double a[maxn][maxn];
void gauss_jordan(){
	for(int i=1;i<=n;++i){
		int r=i;
		for(int j=i+1;j<=n;++j)
			if(fabs(a[r][i])<fabs(a[j][i]))
				r=j;
		if(r!=i)
			for(int j=1;j<=n+1;++j)
			swap(a[i][j],a[r][j]);
			for(int j=1;j<=n;++j)if(j!=i){
		 		double tmp=a[j][i]/a[i][i];
		 		for(int k=i+1;k<=n+1;++k)
	   		   		a[j][k]-=a[i][k]*tmp;
			}
   	}
	for(int i=1;i<=n;++i)
		a[i][n+1]/=a[i][i];
}
int main(){
	//freopen("dotp.in","r",stdin);
	//freopen("dotp.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&p,&q);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		f[x][y]=f[y][x]=true;
		in[x]++;in[y]++;
	}
	a[1][n+1]=1.0*p/q;
	for(int i=1;i<=n;i++){
		a[i][i]=1;
		for(int j=1;j<=n;j++)
			if(f[i][j])
				a[i][j]=-(1-(double)p/q)/in[j];
	}
	gauss_jordan();
	for(int i=1;i<=n;i++)
		printf("%.9lf\n",a[i][n+1]);
	return 0;
}
```

---

## 作者：Siyuan (赞：18)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/articles/problem-Luogu-2973-Dotp/)

---

## Description

> 题目链接：[Luogu 2973](https://www.luogu.org/problemnew/show/P2973)

有一个 $n$ 个点 $m$ 条边的无向图，节点 $1$ 有一个炸弹，在每个单位时间内，这个炸弹有 $\frac{P}{Q}$ 的概率在这个节点炸掉，有 $1-\frac{P}{Q}$ 的概率等概率选择一条与当前节点相连的边到其他的节点上。求炸弹在每个节点上爆炸的概率。

数据范围：$2\le n\le 300$，$1\le m\le 44850$，$1\le P,Q\le 10^6$

------

## Solution

很显然，如果我们设第 $i$ 个点的期望经过次数为 $f_i$，那么第 $i$ 个点的爆炸概率为 $f_i\times\frac{P}{Q}$。那么我们只需要求出这个 $f_i$ 即可。

对于 $f_i$ 我们有如下关系式：
$$f_u=\begin{cases}1& i=1 \\\sum_{(u,v)\in E} (1-\frac{P}{Q})\times \frac{f_v}{deg_v} & \text{otherwise}\end{cases}$$
其中 $deg_i$ 表示第 $i$ 个点的度数。这个式子的含义为：当到达 $u$ 时，当且仅当在 $v$ 的位置不爆炸并且有 $\frac{1}{deg_v}$ 的概率从 $v$ 走到 $u$ 的位置。

我们直接高斯求和一波就好了。

**时间复杂度**：$O(n^3)$

------

## Code

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>

const int N=305;
int n,m,p,q,e[N][N],deg[N];
double a[N][N],b[N],x[N];

void Gauss(int n) {
	for(int i=1;i<=n;++i) {
		int p=i;
		for(int k=i+1;k<=n;++k) if(fabs(a[k][i])>fabs(a[p][i])) p=k;
		if(i!=p) std::swap(a[i],a[p]),std::swap(b[i],b[p]);
		for(int k=i+1;k<=n;++k) {
			double d=a[k][i]/a[i][i];
			b[k]-=d*b[i];
			for(int j=i;j<=n;++j) a[k][j]-=d*a[i][j];
		}
	}
	for(int i=n;i>=1;--i) {
		for(int j=i+1;j<=n;++j) b[i]-=x[j]*a[i][j];
		x[i]=b[i]/a[i][i];
	}
}
int main() {
	scanf("%d%d%d%d",&n,&m,&p,&q);
	double P=1.0*p/q;
	while(m--) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u][v]=e[v][u]=1,++deg[u],++deg[v];
	}
	for(int i=1;i<=n;++i) {
		a[i][i]=1.0;
		for(int j=1;j<=n;++j) {
			if(e[i][j]) a[i][j]-=(1.0-P)/deg[j];
		}
	}
	b[1]=1.0;
	Gauss(n);
	for(int i=1;i<=n;++i) printf("%.9lf\n",x[i]*P);
	return 0;
}
```



---

## 作者：whhsteven (赞：12)

### 题目链接

[**P2973 Driving Out the Piggies G**](/problem/P2973)

&nbsp;

### 题意

给定一张无向图，保证 $1$ 号结点一定连接了至少 $1$ 个结点。现在在 $1$ 号结点放一个炸弹，每个单位时间内，它有 $\frac pq$ 的概率在当前结点爆炸，有 $1 - \frac pq$ 的概率等概率随机选择一条出去的边转移到其它结点。问炸弹最终在每个结点上爆炸的概率。

&nbsp;

### 解

其它题解提到，**在一个点爆炸的概率 $=$ 这个点的期望经过次数 $\times$ 每次炸弹爆炸的概率（即 $\frac pq$）**。

这样感性理解一下可能能觉得是对的。这里写一下一个简单的，不那么偏感性的解释：

显然炸弹爆炸的次数的取值只有 $\{0,1\}$。这样我们发现，炸弹的期望爆炸次数与爆炸概率 **在数值上相等**。从而

在一个点爆炸的概率 $=$ 期望在这个点爆炸的次数 $=$ 期望经过这个点且在这个点爆炸的次数

当随机变量 $X$ 和 $Y$ 互相独立时，$E(XY) = EX \cdot EY$。定义 $X$ 为经过这个点的次数，$Y$ 为每次爆炸次数（显然同样取值 $\{0,1\}$），则所求即

$$E(XY) = EX \cdot EY$$

同样，由 $Y$ 取值 $\{0,1\}$ 知，$EY$ 数值上等于每次爆炸概率，即 $\frac pq$。

所以，在一个点爆炸的概率，数值上等于在这个点的期望爆炸次数 $E(XY)$，数值上等于这个点的期望经过次数 $EX$ 乘每次爆炸概率 $\frac pq$。

&nbsp;

如有错误恳请指正，如有其它见解敬请提出。

---

## 作者：Kelin (赞：9)

## [题意](https://blog.csdn.net/BeNoble_/article/details/79761509)

一开始在$1$有个炸弹,在每个点有$\frac pq$的概率的爆炸,如果不爆炸则等概率地走向相邻的点

---

## 题解

设$f[u]$表示走到$u$的期望次数,$d_u$表示点度,初始$f_1=1$

因为要不爆炸才能往下走,那么有

$$f[u]=\sum_{(u,v)\in E}\frac1{d_v}(1-\frac pq)f[v]$$

在每个点爆炸的概率就是期望走到每个点的次数$\times$爆炸的概率

因为状态转移有环,所以~~按照套路~~高斯消元就好了

注意这题卡精度,$\epsilon\lt10^{-13}$才行

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
const int N=305;
const double eps=1e-15;
typedef int arr[N];
typedef double d;
int n,m,p,q;arr dg,mp[N];d pr,ans[N],G[N][N];
inline int cmp(const d&x){return fabs(x)<eps?0:(x<0?-1:1);}
inline void Gauss(int n){
    int mx;d t;
    fp(i,1,n){mx=i;
        fp(j,i,n)if(cmp(G[mx][i]-G[j][i]))mx=i;
        if(mx^i)fp(j,i,n+1)swap(G[i][j],G[mx][j]);
        fp(j,i+1,n)if(cmp(G[j][i])){
            t=G[j][i]/G[i][i];
            fp(k,i,n+1)G[j][k]-=t*G[i][k];
        }
    }
    fd(i,n,1){
        fp(j,i+1,n)G[i][n+1]-=ans[j]*G[i][j];
        ans[i]=G[i][n+1]/G[i][i];
    }
}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    scanf("%d%d%d%d",&n,&m,&p,&q);pr=1.0*p/q;
    while(m--){
        int u,v;scanf("%d%d",&u,&v);
        mp[u][v]=mp[v][u]=1;++dg[u],++dg[v];
    }
    fp(i,1,n)G[i][i]=1;
    fp(i,1,n)fp(j,1,n)if(mp[i][j])
        G[i][j]+=-(1.0-pr)/dg[j];
    G[1][n+1]=1;Gauss(n);
    fp(i,1,n)printf("%.9lf\n",ans[i]*pr);
return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：7)

设 $\lambda = \dfrac pq$。称现在处于 **存活状态** 当且仅当炸弹未爆炸。现在我们设 $f_{n, i}$ 为走了 $n$ 步，在节点 $i$，且存活的概率。容易发现 $f_{n} \mapsto f_{n+1}$ 的转化是一个线性映射，而且其表示矩阵 $\boldsymbol A$ 可以直接从这个有向图写出（$a_{i,j} = \dfrac{1-\lambda}{\mathrm{deg}^{\rm out}_i}$）。并且有 $f_0 = \boldsymbol e_1$（仅在第一分量为 $1$，后面的分量均为 $0$ 的列向量）。

而一个炸弹在第 $n$ 步爆炸的概率是 $(1-\lambda)^{n-1} \lambda$（注意需要带上在 $n-1$ 步存活的概率），同理得炸弹在第 $n$ 步，节点 $i$ 爆炸的概率为 $f_{n-1,i} \lambda = \lambda (\bm A^{n-1} \bm e_1)_i = \bm A^{n-1}_{1,i}$。

现在当 $n$ 对 $1,2,3,\dots$ 求和：
$$
\begin{aligned}
\mathrm{ans}(i) &= \sum_{n=1}^{+\infty} \lambda (\boldsymbol A^{n-1})_{1,i} \\
&= \lambda \left(\sum_{n=1}^{+\infty} \bm A^{n-1}\right)_{1,i} \\
&= \lambda \left(\sum_{n=0}^{+\infty} \bm A^n\right)_{1,i} \\
&= \lambda (\bm I - \bm A)^{-1}_{1,i}.
\end{aligned}
$$
因此，对 $\bm I - \bm A$ 求逆即可。

---

## 作者：Alkaid_Star (赞：5)

本文同步发表在我的[WordPress博客](https://www.encounter.cool/index.php/2021/03/19/luogu2973%ef%bc%88%e9%ab%98%e6%96%af%e6%b6%88%e5%85%83%ef%bc%89%e9%a2%98%e8%a7%a3/)。
### 题目大意：
> 一个 $n$ 个点 $m$ 条边的无向图，节点 $1$ 有一个炸弹，在每个单位时间内，有 $p/q$ 的概率在这个节点炸掉，有 $1-\frac p q$ 的概率随机选择一条出去的路到其他的节点上。问最终炸弹在每个节点上爆炸的概率。
$ 1 \le  n \le 300$ ，$1\le m \le 50000$ 。

### 样例分析：

对于样例：
> 2 1 1 2 

> 1 2 

在 $1$ 的概率： $(1/2)^1+(1/2)^3+(1/2)^5......(1/2)^{2n+1}=2/3$
（即：一开始就爆炸或者 "1->2->1" 然后爆炸......以此类推，下面同理）
结束在 $2$ 的概率同理，为 $(1/2)^2+(1/2)^4+......+(1/2)^{2n}=1/3$

### 思路：
~~托~~群众：分析一堆看起来很有道理，但是没有用啊？！

咳咳，至少我们可以发现路径的可能条数是无穷的（只要炸弹一直不爆炸，人就可以在两座城市之间反复横跳）。

那么对于这种~~奇怪的~~题目，我们一般考虑 **使用方程来推出相邻两个状态之间的关系，从而解决无穷无尽的路径** 。

我们设 $f_i$ 为炸弹在第 $i$ 座城市爆炸的概率。

那么对于一座城市 $x$ ，我们考虑怎么列出式子：
考虑当前城市的炸弹是从其他城市传过来并且在当前城市爆炸：
$ f_x=\sum_{ 所有满足 x,v有边相连的 v } \frac {(1-\frac p q)} {deg[v]}*f_v $

移项后变为：

$ -f_x+\sum_{ 所有满足 x,v有边相连的 v } \frac {(1-\frac p q)} {deg[v]}*f_v=0 $

也就可以对应进代码里的系数了。

对了，最后还要算上炸弹在第一座城市爆炸的概率嗷，不明白可以看代码。

诶，那我们每个城市一个方程，总共就是 $n$ 元 $n$ 个方程，用高斯消元解就好了（别跟我说你不会高斯消元）。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=305,M=50005;

struct Edge{
	int vet,nxt;
}e[M<<1];

int n,m,edge=0,head[N],deg[N];
double p,q,a[N][N];
bool Free[N];

inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)) { if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

inline void addedge(int x,int y){
	e[++edge].vet=y;
	e[edge].nxt=head[x];
	head[x]=edge;
}

namespace Gauss{

	bool Inf_solution=false,No_Solution=false;

	inline void SwapLine(int x,int y){		//交换第 x 行和第 y 行
		for (int i=1;i<=n+1;++i)
			swap(a[x][i],a[y][i]);
	}

	inline void Mul(int x,double k){		//把第 x 行的值乘上 k
		for (int i=1;i<=n+1;++i)
			a[x][i]*=k;
	}

	inline void Add(int x,double k,int y){		//把第 x 行乘上 k 加到第 y 行上
		for (int i=1;i<=n+1;++i)
			a[y][i]+=(a[x][i]*k);
	}

	inline void Main(){
		for (int i=1;i<=n;++i){
			if (a[i][i]==0){		//如果第 i 行第 i 项系数为 0 则与之后与不为 0 的行交换
				bool flag_free=true;
				for (int j=i+1;j<=n;++j)
					if (a[j][i]){
						SwapLine(i,j);
						flag_free=false;
						break;
					}
				if (flag_free) Free[i]=true;
			}
			if (Free[i]) { Inf_solution=true; continue; }
			Mul(i,1.0/a[i][i]);		//把第 i 行第 i 项系数变成 1 
			for (int j=1;j<=n;++j)		//消去其他行第 i 项的系数
				if (i^j) Add(i,-a[j][i],j);
		}
		for (int i=1;i<=n;++i){
			bool flag_zero=true;
			for (int j=1;j<=n;++j)
				if (a[i][j]){
					flag_zero=false;
					break;
				}
			if ((flag_zero) && (a[i][n+1])){
				No_Solution=true;
				break;
			}
		}
	}

}

int main(){
	//freopen("Luogu2973.in","r",stdin);
	//freopen("Luogu2973.out","w",stdout);
	scanf("%d%d%lf%lf",&n,&m,&p,&q);
	for (int i=1;i<=m;++i){
		int x=read(),y=read();
		addedge(x,y);
		addedge(y,x);
		++deg[x],++deg[y];
	}
	for (register int x=1;x<=n;++x){
		a[x][x]=-1;		//把方程移项，让右边为 0 后第 x 个元的系数为 -1 
		for (int i=head[x];i;i=e[i].nxt){
			int v=e[i].vet;
			a[x][v]=1.0*(q-p)/q/deg[v];		//把方程代进去就可以了
		}
	}
	a[1][n+1]=-p/q;		//算上一开始就爆炸的情况
	Gauss::Main();
	for (int i=1;i<=n;++i)
		printf("%.9lf\n",a[i][n+1]);
	return 0;
}
```
都看到这里了，各位看官是不是可以~~三连~~点个赞呢？

---

## 作者：封禁用户 (赞：4)

有关此题的数据范围只有 $100$，

而且炸弹会从道路上移来移去，可能会反复徘徊在一条道路上，

设 $dp_i$ 代表炸弹期望经过 $i$ 号结点的次数，那么它的来源有以下两种：

- 首一次被安装在 $1$ 号结点，经过次数加一。

- 以不爆炸概率除以出边数量的概率，从与其相邻的一个结点上移到这个结点。

设 $k_i$ 为 $i$ 号结点的出度，那么：
$$
dp_i=[i=1]+\sum\limits_\text{s与i相连} (1-\frac{p}{q})\frac{1}{k_s}dp_s
$$

由于 $dp$ 方程具有后效性，再加上图并非树形，无法使用换根法，于是考虑使用高斯消元法。时间复杂度 $O(n^3)$。

方程：$dp_i-\sum\limits_\text{s与i相连} (1-\frac{p}{q})\frac{1}{k_s}dp_s=[i=1]$

---

## 作者：louhao088 (赞：4)

# 题意
有 N 个城市，M 条双向道路组成的地图，城市标号为 1 到 N。“西瓜炸弹”放在 1
号城市，保证城市 1 至少连接着一个其他城市。“西瓜炸弹”有 P/Q 的概率会爆炸，每
次进入其它城市时，爆炸的概率相同。如果它没有爆炸，它会随机的选择一条道路到另
一个城市去，对于当前城市所连接的每一条道路都有相同的可能性被选中。对于给定的
地图，求每个城市“西瓜炸弹”爆炸的概率。


------------


## 样例解释
我们就有以下可能的路径（其中最后一项是结束城市，即“西瓜炸弹”爆炸并污染该城市）

$1: 1$

$2: 1-2$

$3: 1-2-1$

$4: 1-2-1-2$

$5: 1-2-1-2-1$

$......$



------------


为了找出“西瓜炸弹”在城市 1 爆炸的可能性，我们可以把第 $1、3、5......$种路径出现的
概率加起来（在这个例子中即把所有奇数路径出现的可能性加起来）。

对于第 $k$ 种路径出现的可能性为$(\frac 1 2)^k$：

在经过前 $k-1 $次时，炸弹绝对不会在城市 1
爆炸（每一次的概率为 $1 – $ $\frac 1 2 = \frac 1 2$），然后最后在城市 1 爆炸（概率为 $\frac 1 2 $）。

因此，在城市 1 爆炸的可能性就是 $\frac 1 2 $ +  $(\frac 1 2 )^3 $ + 
$($ $\frac 1 2 )^5$+ ...... ，把这些数都加起来就等于 $\frac 2 3$ 约为 $0.666666667$

所以在城市 2 爆炸的可能性就是 $\frac 1 3$ 为 $0.333333333$。



------------


# 思路分析


看着样例我们发现每个点的概率好像与它连出去的点有关。

我们设$x_i$为城市$i$的概率，则可以列出一系列的方程

以样历为例
```cpp
2 1 1 2 
1 2 
```
$x_1$ $=$ $\frac 1 2$ $+$ $\frac 1 2$ $x_2$

$x_2$ $=$ $\frac 1 2$ $x_1$

解得

$x_1$ $=$ $\frac 2 3$,
$x_2$ $=$ $\frac 1 3$

与答案一样


------------



再以下面数据为例
```cpp
3 2 1 3
1 2
3 2
```
图形如下

$1-2-3$

我们列出方程

$x_1$ $=$ $\frac 1 3$ $+$ $\frac 1 3$ $x_2$

$x_2$ $=$ $\frac 2 3$ $x_1$ $+$ $\frac 2 3$ $x_3$

$x_3$ $=$ $\frac 1 3 $ $x_2$


解得

$x_1$ $=$ $\frac 7 {15}$,
$x_2$ $=$ $\frac 2 5$,
$x_3$ $=$ $\frac 2 {15}$


我们发现每个点的方程$=$(1$-$概率）$*$连出去的点$/$其度数

第一个点再加上概率


------------


问题就转换为了解方程的问题

我们很快就想到了高斯消元

解出答案问题就解决了

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	char ch=getchar();int x=0;bool f=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
const int maxn=200005;
struct edge
{
	int v,w,nex;
}e[maxn];
int n,x,y,head[maxn],cnt=0,s[505],m;
double ans[505],a[505][505],p,q;
void add(int u,int v)
{
	e[++cnt].v=v;e[cnt].nex=head[u],head[u]=cnt;
}
int main()
{
//	freopen("dotp.in","r",stdin);
//	freopen("dotp.out","w",stdout);
	n=read(),m=read();cin>>p>>q;
	for(int i=1;i<=m;i++)
		x=read(),y=read(),add(x,y),add(y,x),s[x]++,s[y]++;
	a[1][n+1]=-p/q;
	for(int i=1;i<=n;i++)//转化方程
	{
		a[i][i]=-1;
		for(int j=head[i];j;j=e[j].nex)
		{
			int v=e[j].v;
			a[i][v]=1.0*1/s[v]*(q-p)/q;
		}
	}
	for(int i=1;i<=n;++i)//高斯消元
	{
		int max=i;
		for(int j=i+1;j<=n;++j)
		{
			if(fabs(a[j][i])>fabs(a[max][i]))
			{
				max=j;
			}
		}
		for(int j=1;j<=n+1;++j)
		{
			swap(a[i][j],a[max][j]);
		}
		for(int j=1;j<=n;++j)
		{
			if(j!=i)
			{
				double temp=a[j][i]/a[i][i];
				for(int k=i+1;k<=n+1;++k)
				{
					a[j][k]-=a[i][k]*temp;
				}
			}
		}
	}
	for(int i=1;i<=n;++i)
	{
		printf("%.9lf\n",a[i][n+1]/a[i][i]);
	}
	return 0;
}
```









---

## 作者：bsdsdb (赞：3)

题意：一个无向图，$1$ 号节点有个炸弹，每一个时刻他有 $\frac PQ$ 的概率爆炸，此时游戏结束；如果他没爆炸，他会在所有邻点中随机选择一个走过去。对于每个节点 $x$ 求炸弹在 $x$ 爆炸的概率。$n\le300$。

事实上，本篇题解解决的是这个问题的强化版：对每一对 $(x,y)\in[1,n]^2$，求炸弹从 $x$ 开始走到 $y$ 爆炸的概率。但是好像对着原题面也不难想到这个思路（？

为了方便记 $p:=\frac PQ$。设 $\mathrm{dp}_{i,j}$ 表示炸弹从 $i$ 出发在 $j$ 爆炸的概率。容易写出方程：

$$
\mathrm{dp}_{i,j}=[i=j]p+\frac{1-p}{d_i}\sum_{(i,k)\in E}\mathrm{dp}_{k,j}
$$

其中，$E$ 表示边集，$d_i$ 表示点 $i$ 的度。发现方程有点类似矩阵？于是考虑构造两个矩阵 $M,I'$：

$$
M_{i,j}\gets[(i,j\in E)]\frac{1-p}{d_i}\\
I'\gets[i=j]p
$$

然后就有：

$$
\mathrm{dp}=I'+M\mathrm{dp}=(I-M)^{-1}I'
$$

由于 $I,M,I'$ 已知，矩阵求逆即可。

要是 $I-M$ 不可逆呢？

[Gershgorin 圆盘定理](https://en.wikipedia.org/wiki/Gershgorin_circle_theorem)：对于一个复数组成的方阵 $A$，令 $\displaystyle R_i:=\sum_{j\neq i}A_{i,j},D_i:=\{z\in\Complex\mid\lvert z-A_{i,i}\rvert\le R_i\},D:=\bigcup_{i=1}^nD_i$，则对于 $A$ 的每个[特征值](https://www.bilibili.com/video/BV1Ls411b7oL/) $\lambda$，有：

$$
\lambda\in D
$$

特征值的某个性质：一个 $n$ 阶方阵有 $n$ 个特征值。

特征值的另一个性质：设 $A$ 的 $n$ 个特征值为 $\{\lambda_i\}_{i=1}^n$，则：

$$
\prod_{i=1}^n\lambda_i=\det(A)
$$

组合在一起，我们得到：如果 $0\notin D$，则 $\det(A)\neq0$，则 $A$ 可逆。

回到本题，设 $J:=I-M$，由于图没有自环（有也可以直接去掉，不影响答案），$J_{i,i}=1$，又根据定义有 $R_i=\displaystyle\sum_{j\neq i}=p$，所以 $0\in D_i$ 只有可能是 $p=1$，这种情况直接输出答案即可。$p<1$ 时，$0\notin D$，$I-M$ 可逆。

---

## 作者：Purslane (赞：3)

## Solution

讨论区里有人怀疑直接求概率的正确性我来说两句。

这里的概率怎么定义?显然不是古典概型。每一条有向边都有边权 $w=\frac{1}{deg_u}$，表示选择这一条路的概率。同时，每个点还有点权为 $1-\frac{p}{q}$，表示安然无恙离开这个点的概率。所以一个点爆炸的概率就是所有从起点到这个点的路径边权和非终点点权积的和再乘上 $\frac{p}{q}$，不知说的是否清楚。

这个是不能直接求的，因为方案是无限个。所以我们先设 $dp_u$ 表示在 $u$ 爆炸的概率。当 $u\neq 1$ 的时候，既然 $u$ 不是起点，那么它前面必定还有一个点，设为 $v$。那么所有以 $v$ 结尾的路径的边权积与非终点点权的和是 $\frac{q}{p} \times dp_v$。再乘上这个 $v$ 的点权和 $(u,v)$ 的边权，就是 $\frac{q}{p} \times dp_v \times \frac{1}{deg_v} \times (1-\frac{p}{q})$。所以 $dp_u = \frac{p}{q} \sum_{(v,u) \in E} \frac{q}{p} \times dp_v \times \frac{1}{deg_v} \times (1-\frac{p}{q}) = \sum_{(v,u)\in E} dp_v \times \frac{1}{deg_v} \times (1-\frac{p}{q})$ 。 唯一的问题只有 $u=1$ 的时候，它可以不需要经过任何点并爆炸，概率是 $\frac{p}{q}$ 。最后加上即可。

求出所有的 $dp$ 数组的关系式，就可以高斯消元求解。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=300+10;
int n,m,p,q,deg[MAXN]; vector<int> G[MAXN];
double x[MAXN],f[MAXN][MAXN];
void gauss(void) {
	ffor(j,1,n) {
		if(abs(f[j][j])<=1e-6) ffor(i,j+1,n) if(abs(f[i][j])>1e-6) {swap(f[i],f[j]);break;}
		ffor(i,j+1,n) {
			double mul=f[i][j]/f[j][j];
			ffor(k,1,n+1) f[i][k]-=f[j][k]*mul;	
		}
	}
	return;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>p>>q;
	ffor(i,1,m) {
		int u,v; cin>>u>>v;
		G[u].push_back(v),G[v].push_back(u);	
		deg[u]++,deg[v]++;
	}
	ffor(i,1,n) {
		if(i==1) f[1][n+1]=p*1.0/q;
		f[i][i]=1.0;
		for(auto v:G[i]) f[i][v]=-(1-p*1.0/q)*1.0/deg[v]; 	
	}
	gauss();
	roff(i,n,1) {
		ffor(j,i+1,n) f[i][n+1]-=f[i][j]*x[j];
		x[i]=f[i][n+1]/f[i][i];	
	}
	ffor(i,1,n) cout<<fixed<<setprecision(8)<<x[i]<<'\n';
	return 0;
}
```

---

## 作者：dz_ice (赞：2)

[大家可以来看看呀](https://www.cnblogs.com/dzice/)

[题目链接](https://www.luogu.org/problem/P2973)

貌似没有卡我精度？

这道题跟[这道](https://www.luogu.org/problem/P3232)的思路和做法都挺像的，也是期望+高斯消元

设$f_u$为一个点期望的经过次数，那么我们可以发现，炸弹在每个点爆炸的概率其实就是$f_u*p/q$，求出每个点的$f_i$即可得到最终的答案，显然,每个点的期望是由相连的点的期望决定的，$du_x$为点$x$的度数,点$x_1,x_2,x_3....x_k$与点$x$相邻，则$f[x]=\sum_{i=1}^k\frac{fx_i}{dux_i}$

最后用高斯消元解一下每个点的期望即可，上代码

```
#include<bits/stdc++.h>
using namespace std;
int n,m,t,x,y;
double p,q,gai,chu,du[303],a[303][303],b[303],ans[303];
vector<int>l[303];
int main()
{
	scanf("%d%d%lf%lf",&n,&m,&p,&q);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		l[x].push_back(y),l[y].push_back(x),du[x]++,du[y]++;
	}
	gai=p/q,b[1]=-1;
	for(int i=1;i<=n;i++)
	{
		a[i][i]=-1;
		for(int j=0;j<l[i].size();j++)
			a[i][l[i][j]]=(1-gai)*(1/du[l[i][j]]);			
	}
	for(int i=1;i<=n;i++)
	{
		t=i;
		for(int j=i+1;j<=n;j++)
			if(a[j][i]>a[j][t])
				t=j;
		if(t!=i)
		{
			for(int j=i;j<=n;j++)
				swap(a[i][j],a[t][j]);
			swap(b[i],b[t]);
		}
		if(a[i][i]!=0)
			for(int j=i+1;j<=n;j++)
			{
				chu=a[j][i]/a[i][i];
				for(int k=i;k<=n;k++)
					a[j][k]-=a[i][k]*chu;
				b[j]-=b[i]*chu;
			}
	}
	for(int i=n;i>=1;i--)
	{
		ans[i]=b[i]/a[i][i];
		for(int j=1;j<i;j++)
			b[j]-=a[j][i]*ans[i];
	}
	for(int i=1;i<=n;i++)
		printf("%.9lf\n",fabs(ans[i]*gai));
	return 0;
}

```


---

## 作者：Aw顿顿 (赞：1)

这是一道非常传统的高斯消元的题目，需要简单的期望推导。

--------

## 期望推导

无向图，节点 $1$ 是炸弹，每秒都有 $p/q$ 的概率爆炸，否则随机选择一条出边到相邻节点，问每个节点由炸弹爆炸的概率。

这个概率，你会发现写成分数的形式毫无用处，于是直接记 $p/q$ 为实数 $P$。显然每个节点爆炸或者不爆炸的概率，是受到周围节点影响的，那么我们考虑一下转移的方程。

设 $x_i$ 为期望经过点 $i$ 次数，显然答案为 $P\times x_i$ （因为每次经过点 $i$ 的概率都不同，因此能把期望求出来就好了，结合两个点的样例理解），那么应该怎么利用周围节点的数据，来求当前节点的值呢？

首先就是不得不提的，第一个点的经过期望次数要加一，因为一开始就在这里。那么再考虑经过次数期望：从别的地方来，没炸，那么这就牵扯到度数问题，不难写出以下方程：

$$x_u=\sum\limits_{(u,v)}(1-P)\times \dfrac{1}{d_v}\times x_v+[u=1]$$

这意味着，对于每一个能够到达当前节点的节点，如果没有爆炸（也就是式子中 $1-P$ 的意义），那么就一定能安稳的到达该节点，求一下和就好了。而后面的 $[u=1]$ 是一个[艾弗森括号](https://baike.baidu.com/item/艾佛森括号/22361197)，是一个谓词函数。

但是这能够简单地递推吗？显然是不行的，因为这是一个无向连通图，因此必然存在环。而关于这个加一，要意识到，LHS 是 $x_u$ 而无论是 $+1$ 还是上面的递推式，都是 RHS 因此是同号。根据最后你决定把未知数放在 $x_u$ 这边还是 $x_v$ 这边，两者符号有所不同。

因为能够列出 $n$ 个未知数的 $n$ 个递推式，因此可以列出来的是一个方程组用高斯消元，$O(n^3)$，所以可以做。

我们接下来简单介绍一下高斯消元。

## 高斯消元

线性方程组写成增广矩阵的形式（$n$ 个系数一个 $1$ 个常数）$\to n\times (n+1)$ 的矩阵

目标：把一般方程用高斯消元法消成上三角矩阵

$\begin{cases}x+y-4z=-9&\boxed{\text{I.}}\\x+4y+z=6&\boxed{\text{II.}}\\4x-5y+z=-3&\boxed{\text{III.}}\end{cases}$

消去 $x$ 的系数：$\text{II}-\text{I}$ 和 $\text{III}-4\times\text{I}$ 得到一个新矩阵

然后对于消去 $x$ 的两个二元方程组，再消一次元，求出 $z$。

然后一层一层代入回去。

只要次序消元结束然后回代就能得到结果，鉴于篇幅问题，此处不再介绍更简单的高斯-约当消元法。

## 代码思路

高斯消元的大致步骤：

读入矩阵 $\to$ 循环 $n$ 条（从 $1\sim n-1$ 因为最后一个未知量不需要消掉）。内层循环从 $i+1$ 到 $n$（前面的消过了不用消，要从这里处理到最后一行）

若当前数 $a(i,i)$ 是 $0$ 且常数 $c=a(i,n+1)\neq 0$ 就是无解的，因为 $0\cdot x_i=c$ 是不存在的，如果 $c=0$ 那就是多解。然后 $a(i,n+1)$ 即常数项写出来，然后移项求解。

然后系数化为一就解决了（更新到 $ans$ 数组里面）。

## 代码

```cpp
#include<bits/stdc++.h>
#define N 305
using namespace std;
int n,m,p,q,h[N],cnt,d[N];
struct edge{int v,nxt;}e[N*N*2]; 
void add(int u,int v){
	e[++cnt].v=v;e[cnt].nxt=h[u];
	h[u]=cnt;d[v]++;
}long double X,a[N][N],ans[N];//ans 是期望经过次数 
int main(){
	scanf("%d%d%d%d",&n,&m,&p,&q);
	X=(p*1.0)/(q*1.0);
	for(int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}for(int i=1;i<=n;i++){
		for(int j=h[i];j;j=e[j].nxt)
			a[i][e[j].v]=(1.0-X)/(long double)d[e[j].v];//精髓 
		a[i][i]=-1;
		if(i==1)a[i][n+1]=-1;
	}for(int i=1;i<n;i++){//从这开始高消了 
		for(int j=i+1;j<=n;j++){
			long double sum=a[j][i]/a[i][i];
			for(int k=i;k<=n+1;k++)a[j][k]-=sum*a[i][k];
		}
	}for(int i=n;i>0;i--){
		long double sum=a[i][n+1];
		for(int j=i+1;j<=n;j++)sum-=ans[j]*a[i][j];
		ans[i]=sum/a[i][i];
	}for(int i=1;i<=n;i++)
		printf("%.9Lf\n",X*ans[i]);
	return 0;
}
```

---

## 作者：tommymio (赞：1)

直接设在每个点爆炸的概率是不好转移的。不妨设当前在点 $i$ 没有爆炸，期望经过点 $i$ 的次数 $f_i$。

那么有：

$$
\begin{cases}
f_1=1+(1-\frac{P}{Q})\sum_{(1,v)\in E} \frac{1}{du_v}f_v
\\
f_i=(1-\frac{P}{Q})\sum_{(i,v)\in E} \frac{1}{du_v}f_v
\end{cases}
$$

知道了经过每个点 $i$ 的期望次数后，在点 $i$ 爆炸的概率即转化为期望次数 $\times$ 爆炸概率。即，对于每个点 $i$，答案为 $f_i\times \frac{P}{Q}$。

这个 $\text{DP}$ 方程具有后效性，高斯消元一波即可，时间复杂度为 $O(n^3)$。

这道题充分说明了，不仅期望可以转化为概率 $\times$ 权值，概率也可以转化为期望 $\times$ 概率（已知）。

代码太 $\text{Naive}$ 了就不放了。

---

## 作者：cirnovsky (赞：0)

## 题意简述

一个无向图，节点 $1$ 有一个炸弹，在每个单位时间内，有 $\frac{p}{q}$ 的概率在这个节点炸掉，有 $1-\frac{p}{q}$ 的概率随机选择一条出去的路到其他的节点上。

问最终炸弹在每个节点上爆炸的概率。

## 题解

直接设概率做不来的样子。。。

问了一下懂行的人发现需要设期望。

设 $f_{u}$ 为节点经过 $u$ 的期望次数，设 $E$ 为边集，$d_{u}$ 表示节点 $u$ 的度。
$$
f_{u}=(1-\frac{p}{q})\sum_{(u,v)\in E}\frac{1}{d_{v}}f_{v}
$$
因为有环，所以需要高斯消元一下。

那么在每个节点爆炸的概率即为 $f_{u}\times\frac{p}{q}$。

总结一下，这道题告诉了我不仅是期望可以回归本质用概率搞，概率也可以用期望来整。

```cpp
#include <cstdio>

const int MAXN = 300 + 5, MAXM = MAXN * MAXN;

template<typename _T> _T ABS ( const _T x ) { return x > 0 ? x : -x; }
template<typename _T> void swapp ( _T &x, _T &y ) { _T w = x; x = y; y = x; }

struct GraphSet {
	int to, nx;
	GraphSet ( int T = 0, int N = 0 ) { to = T, nx = N; }
} as[MAXM];

int n, m, p, q, cnt, d[MAXN], begin[MAXN];
double mat[MAXN][MAXN], sol[MAXN], boomed, transed;

void makeEdge ( const int u, const int v ) { as[++ cnt] = GraphSet ( v, begin[u] ), begin[u] = cnt; }

void Eradicate () {
	for ( int i = 1; i <= n; ++ i ) {
		int p = i;
		for ( int j = i + 1; j <= n; ++ j ) {
			if ( ABS ( mat[p][i] ) < ABS ( mat[j][i] ) )	p = j;
		}
		for ( int j = 1; j <= n + 1; ++ j )	swapp ( mat[p][j], mat[i][j] );
		for ( int j = 1; j <= n; ++ j ) {
			if ( i == j )	continue;
			double d = mat[j][i] / mat[i][i];
			for ( int k = 1; k <= n + 1; ++ k )	mat[j][k] -= mat[i][k] * d;
		}
	}
	for ( int i = 1; i <= n; ++ i )	sol[i] = mat[i][n + 1] / mat[i][i];
}

int main () {
	scanf ( "%d%d%d%d", &n, &m, &p, &q );
	for ( int i = 1, u, v; i <= m; ++ i ) {
		scanf ( "%d%d", &u, &v );
		makeEdge ( u, v ), makeEdge( v, u );
		d[u] ++, d[v] ++;
	}
	boomed = ( double )p / ( double )q;
	transed = 1 - boomed;
	for ( int _ = 1; _ <= n; ++ _ ) {
		int u = _;
		mat[u][u] = 1;
		for ( int i = begin[u]; i; i = as[i].nx ) {
			int v = as[i].to;
			mat[u][v] -= transed / d[v];
		}
	}
	mat[1][n + 1] = 1;
	Eradicate ();
	for ( int i = 1; i <= n; ++ i )	printf ( "%.9lf\n", sol[i] * boomed );
	return 0;
}
```

---

