# European Trip

## 题目描述

The map of Europe can be represented by a set of $ n $ cities, numbered from $ 1 $ through $ n $ , which are connected by $ m $ bidirectional roads, each of which connects two distinct cities. A trip of length $ k $ is a sequence of $ k+1 $ cities $ v_1, v_2, \ldots, v_{k+1} $ such that there is a road connecting each consecutive pair $ v_i $ , $ v_{i+1} $ of cities, for all $ 1 \le i \le k $ . A special trip is a trip that does not use the same road twice in a row, i.e., a sequence of $ k+1 $ cities $ v_1, v_2, \ldots, v_{k+1} $ such that it forms a trip and $ v_i \neq v_{i + 2} $ , for all $ 1 \le i \le k - 1 $ .

Given an integer $ k $ , compute the number of distinct special trips of length $ k $ which begin and end in the same city. Since the answer might be large, give the answer modulo $ 998\,244\,353 $ .

## 说明/提示

In the first sample, we are looking for special trips of length $ 2 $ , but since we cannot use the same road twice once we step away from a city we cannot go back, so the answer is $ 0 $ .

In the second sample, we have the following $ 12 $ special trips of length $ 3 $ which begin and end in the same city: $ (1, 2, 4, 1) $ , $ (1, 3, 4, 1) $ , $ (1, 4, 2, 1) $ , $ (1, 4, 3, 1) $ , $ (2, 1, 4, 2) $ , $ (2, 4, 1, 2) $ , $ (3, 1, 4, 3) $ , $ (3, 4, 1, 3) $ , $ (4, 1, 3, 4) $ , $ (4, 3, 1, 4) $ , $ (4, 1, 2, 4) $ , and $ (4, 2, 1, 4) $ .

## 样例 #1

### 输入

```
4 5 2
4 1
2 3
3 1
4 3
2 4```

### 输出

```
0```

## 样例 #2

### 输入

```
4 5 3
1 3
4 2
4 1
2 1
3 4```

### 输出

```
12```

## 样例 #3

### 输入

```
8 20 12
4 3
6 7
5 7
8 2
8 3
3 1
4 7
8 5
5 4
3 5
7 1
5 1
7 8
3 2
4 2
5 2
1 4
4 8
3 6
4 6```

### 输出

```
35551130```

# 题解

## 作者：周子衡 (赞：12)

不妨设 $F_{t}(i,j)$ 表示从 $i$ 出发走 $t$ 步到达 $j$ 的 *special trip* 数量。记 $E$ 为原图的邻接矩阵，$\mathrm{deg}(i)$ 表示点 $i$ 的度数，我们有：

- $F_0(i,j)=[i=j]$，$F_1(i,j)=E_{i,j}$；
- $F_2(i,j)=\sum_{k=1}^nE_{i,k}E_{k,j}(i\neq j)$，$F_2(i,i)=0$；
- $F_t(i,j)=\sum_{k=1}^nF_{t-1}(i,k)E_{k,j}-F_{t-2}(i,j)\times (\mathrm{deg}(j)-1)(t > 2)$。

解释一下后两条：对 $t\geq 3$，长度为 $t$ 的 *special trip* 一定是从某个长度为 $t-1$ 的 *special trip* 补充一个节点得来的，我们枚举这条路径上 $j$ 的前一个节点 $k$；但还要排除掉所有倒数第三个点恰好也是 $j$ 的方案数，对于这种情况，前 $t-2$ 条边的选法有 $F_{t-2}(i,j)$ 种，而此时倒数第二个点的选法有 $\mathrm{deg}(j)-1$ 种，即可写出上面的式子。

（注意路径倒数第四个点尽管也和 $j$ 相连但不能选，否则长度为 $t-1$ 的路径前缀就不是 *special trip* 了，故要减去 $1$；其余和 $j$ 相连的点都是可选的。另外 $t=2$ 时情况比较特殊，由于不存在所谓“倒数第四个点”，因此这里排除的时候乘的系数不需要减 $1$。如果第二条、第三条追求形式上统一的话，第二条可以写成 $F_t(i,j)=\sum_{k=1}^nF_{t-1}(i,k)E_{k,j}-F_{t-2}(i,j)\times \mathrm{deg}(j)(t = 2)$，注意区别。笔者赛时就卡在这里，所以强调一下。）

答案即为 $\sum_{i=1}^nF_k(i,i)$。直接 DP 计算时间复杂度 $O(n^3k)$，考虑优化。不难发现计数的式子和矩阵乘法有很大的关系；我们不妨把每个 $F_t$ 看成矩阵，那么有


$$
F_t=F_{t-1}E-F_{t-2}(D-I) \ \ (t > 2)
$$

其中 $E$ 是上文提到过的邻接矩阵，$D$ 是度数矩阵（即仅有对角线上有值，第 $i$ 行第 $i$ 列值为 $\mathrm{deg}(i)$ 的矩阵），$I$ 是单位矩阵。此处 $E,D,I$ 都是固定的，可以观察到矩阵递推的结构，求出 $F_k$ 即可解决此题。

想到这里，做法呼之欲出。我们仿照计算斐波那契数列单项的 $O(\log n)$ 做法，用矩阵快速幂来加速计算；不同点在于，这里我们转移矩阵的每一项又都是一个 $n\times n$ 的矩阵。总共进行 $O(\log k)$ 次 $n\times n$ 矩阵乘法，总时间复杂度 $O(n^3\log k)$，可以通过此题。

下面的实现中，结构体 `mat` 代表一个数值矩阵，而 `MAT` 则代表一个各元素都是 $n\times n$ 数值矩阵的 $2\times 2$ 矩阵。

```cpp
#include<cstdio>
#include<cstring>
 
using namespace std;
 
const long long MOD=998244353,G=3;
int add(int x,int y){return x+y>=MOD?x+y-MOD:x+y;}
int sub(int x,int y){return x>=y?x-y:x+MOD-y;}
 
long long fast_pow(long long b,long long p)
{
	long long ans=1;while(p){if(p&1)ans=ans*b%MOD;b=b*b%MOD;p>>=1;}
	return ans;
}
long long INV(long long x){return fast_pow(x,MOD-2);}
int n,m,k;
 
struct mat
{
	long long num[120][120];
	long long *operator[](int x){return num[x];}
	const long long *operator[](int x)const{return num[x];}
	mat(){memset(num,0,sizeof(num));}
};
 
mat operator*(mat a,mat b)
{
	mat c;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=n;k++)
			{
				c[i][j]=add(c[i][j],(long long)a[i][k]*b[k][j]%MOD);
			}
		}
	}
	return c;
}
mat operator+(mat a,mat b)
{
	mat c;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			c[i][j]=add(a[i][j],b[i][j]);
		}
	}
	return c;
}
struct MAT
{
	mat X[2][2];
};
MAT operator*(MAT a,MAT b)
{
	MAT c;
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			for(int k=0;k<2;k++)
			{
				c.X[i][j]=c.X[i][j]+(a.X[i][k]*b.X[k][j]);
			}
		}
	}
	return c;
}
 
int deg[200];
 
int main()
{
	
	scanf("%d%d%d",&n,&m,&k);
	if(k<=2){printf("0");return 0;}
	mat D,E,I;
	for(int i=1,a=0,b=0;i<=m;i++)
	{
		scanf("%d%d",&a,&b);deg[a]++,deg[b]++;E[a][b]=E[b][a]=1;
	}
	for(int i=1;i<=n;i++)I[i][i]=1;
	for(int i=1;i<=n;i++){D[i][i]=sub(1,deg[i]);}
	mat SC=E*E;for(int i=1;i<=n;i++)SC[i][i]=0;
	MAT F;F.X[0][1]=D,F.X[1][1]=E,F.X[1][0]=I;
	MAT P=F;
	k-=2;
	int B=20;while(!(k&(1<<B)))B--;
	for(int j=B-1;j>=0;j--)
	{
		P=P*P;if(k&(1<<j))P=P*F;
	}
	
	mat FINAL=SC*P.X[1][1]+E*P.X[0][1];
	long long ans=0;for(int i=1;i<=n;i++)ans=add(ans,FINAL[i][i]);printf("%lld",ans);
}
```

**后记**

一道稍微有点无聊的数学题……而且和这场比赛其他几道非常有意思的题目比起来，这道题的差距就非常明显了。不过大体还在可接受范围之内。

---

## 作者：WrongAnswer_90 (赞：5)

[CF1662C European Trip](https://www.luogu.com.cn/problem/CF1662C)

感觉很不错的矩阵乘法加速题。

从 $n,k$ 的数据范围大致可以看出是矩阵乘法加速递推。

设 $f_{k,u,v}$ 表示从 $u$ 走到 $v$ 走了 $k$ 步的合法方案数，初始状态 $f_1$ 即为邻接矩阵，最终答案为 $\sum_{i=1}^{n} f_{k,i,i}$。

正常的转移方程为 $f_{k,u,v}=\sum_{l=1}^{n}f_{k-1,u,l} \times f_{0,l,v}$，考虑加入限制。

一条边 $(u,v)$ 在被第 $k-1$ 步时从 $u$ 走到 $v$，然后第 $k$ 步又走了回来，那么第 $k-2$ 步一定会走到 $u$ 节点。所以我们转移到底 $k$ 步时先正常的从 $k-1$ 转移过来，然后选择在第 $k-2$ 步时加一些限制条件，减去不合法的方案数，这样所有不合法的方案就会被不重不漏的考减去。

![](https://cdn.luogu.com.cn/upload/image_hosting/4ppef9k1.png)

设第 $k-2$ 步时 走过的边是 $(x,u)$，第 $k-1$ 步不能走回 $x$，因为这种情况在转移 $k-1$ 时已经被减去了，所以非法方案是从 $u$ 走到 $1,2,3,4$ 四个点然后走回来一共四种情况，即为 $f_{k-2,u,v} \times (deg_u-1)$

所以最终的转移方程为

$$
f_{k,u,v}=\sum_{l=1}^{n}f_{k-1,u,l} \times f_{1,l,v}-f_{k-2,u,v} \times (deg_v-1)
$$

考虑优化，$f_k$ 是一个矩阵的形式，变形一下：

$$
f_k=f_{k-1} \times f_1-f_{k-2} \times (DEG-I)
$$

其中 $DEG_{i,i}=deg_i$，其余为 $0$。

是线性递推形式，用矩阵快速幂优化。

$$
\begin{bmatrix}
f_{k-1},f_{k-2}
\end{bmatrix}

\times

\begin{bmatrix}
f_1,I\\
DEG-I,0
\end{bmatrix}
=
\begin{bmatrix}
f_{k},f_{k-1}\\
\end{bmatrix}

$$

注意当 $k=2$ 时 $
f_k=f_{k-1} \times f_1-f_{k-2} \times DEG$，度数不需要减 $1$，因为第 $k-2$ 步并没有从一个 $x$ 走到 $u$。

本题的精髓在于如何不重不漏考虑不合法的方案数，矩阵乘法加速的是外层的递推，只不过里面的转移恰好又需要用到矩阵乘法，需要搞清楚两个矩乘的关系。

核心代码如下：

```cpp
int n,m,q,deg[100];
struct Matrix1{int f[100][100];};
struct Matrix2{Matrix1 f[2][2];}a;
struct Line2{Matrix1 f[2];}b;
Matrix1 operator *(const Matrix1 m1,const Matrix1 m2)
{
	Matrix1 m3;memset(m3.f,0,sizeof(m3.f));
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<n;++j)
		{
			for(int k=0;k<n;++k)
			m3.f[i][j]=(m3.f[i][j]+m1.f[i][k]*m2.f[k][j])%MOD;
		}
	}
	return m3;
}
Matrix1 operator +(const Matrix1 m1,const Matrix1 m2)
{
	Matrix1 m3;memset(m3.f,0,sizeof(m3.f));
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<n;++j)
		m3.f[i][j]=(m1.f[i][j]+m2.f[i][j])%MOD;
	}
	return m3;
}
Matrix2 operator *(const Matrix2 m1,const Matrix2 m2)
{
	Matrix2 m3;memset(m3.f,0,sizeof(m3.f));
	for(int i=0;i<2;++i)
	{
		for(int j=0;j<2;++j)
		{
			for(int k=0;k<2;++k)
			m3.f[i][j]=m3.f[i][j]+m1.f[i][k]*m2.f[k][j];
		}
	}
	return m3;
}
Line2 operator *(const Line2 m1,const Matrix2 m2)
{
	Line2 m3;memset(m3.f,0,sizeof(m3.f));
	m3.f[0]=m1.f[0]*m2.f[0][0]+m1.f[1]*m2.f[1][0];
	m3.f[1]=m1.f[0]*m2.f[0][1]+m1.f[1]*m2.f[1][1];
	return m3;
}
inline void mian()
{
	read(n,m,q),q-=2;int x,y,ans=0;
	while(m--)read(x,y),++deg[x-1],++deg[y-1],b.f[1].f[x-1][y-1]=b.f[1].f[y-1][x-1]=a.f[0][0].f[x-1][y-1]=a.f[0][0].f[y-1][x-1]=1;
	b.f[0]=b.f[1]*b.f[1];
	if(q==-1){for(int i=0;i<n;++i)ans+=b.f[1].f[i][i];write(ans%MOD);return;}
	for(int i=0;i<n;++i)a.f[0][1].f[i][i]=1,a.f[1][0].f[i][i]=1-deg[i]+MOD,b.f[0].f[i][i]=0;
//		for(int i=0;i<n;++i,puts(""))for(int j=0;j<n;++j)write(b.f[0].f[i][j]);
	for(;q;q>>=1,a=a*a)if(q&1)b=b*a;
	for(int i=0;i<n;++i)ans+=b.f[0].f[i][i];
	write(ans%MOD);
}
```

---

## 作者：I_am_Accepted (赞：5)

### Preface

本来想着 naive 的矩阵乘法，结果还要来一层……

### Analysis

没错，这道题是**矩阵乘法套矩阵快速幂**。

简化版：如果不是「special trip」而是「trip」，想想咋做。

这是一个经典的模型。[P6190 [NOI Online #1 入门组] 魔法](https://www.luogu.com.cn/problem/P6190) 做完后就懂了。因为本文主要讲 trip $\to$ special trip，所以这里不再赘述。

由于某道古老的题是边转点做的，而复杂度是 $O(m^3\log m)$ 的，所以我考场上就蒙了。

其实正解还是正常的节点矩阵乘法。

设邻接矩阵为 $G$，$G_{i,j}=1\iff i,j$ 之间有边。

若我们得到了从 $i$ 开始、$j$ 结束的长度为 $k$ 的 special trip 数量为 $S^{(k)}_{i,j}$，则最终答案为 $\sum_{i=1}^{n}S^{(k)}_{i,i}$。

显然 $S^{(1)}=G$。

那 $S^{(2)}$ 呢？若是 $G^2$，多算了两条边相同的情况，所以减掉即可。设矩阵 $D$，其中 $D_{i,i}$ 为 $i$ 节点的度，其他为 $0$，则

$$
S^{(2)}=G^2-D
$$

若 $k\ge 3$，我们分类计数：

* 先不管最后两条边是否相等，数量为 $G\cdot S^{(k-1)}$。

* 再减去最后两条边相等，其他连着的边不同的方案数，为 $(D-I)\cdot S^{(k-2)}$

对于第二类详细说明一下原因：。

所以有

$$
S^{(k)}=
\begin{cases}
G & k=1
\\
G^2-D & k=2
\\
G\cdot S^{(k-1)}-(D-I)\cdot S^{(k-2)} &k>2
\end{cases}
$$

然后就是[P1349 广义斐波那契数列](https://www.luogu.com.cn/problem/P1349)了，只不过元素都是矩阵。

所以是矩阵套矩阵啊……qwq

时间 $O(n^3\log n)$。

### Code

实现中点下标从 $0$ 开始。

本代码用了 struct 套 struct，显然慢，建议直接将小矩阵写进大矩阵。

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")//DONT use rashly,I have suffered
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")//DONT use rashly,I have suffered
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
const long long mod=998244353;
#define N 100
int n,m,k;
struct ma{
	int a[N][N];
	void init(){For(i,0,n-1)For(j,0,n-1)a[i][j]=(i==j);}
	void clear(){For(i,0,n-1)For(j,0,n-1)a[i][j]=0;};
	ma mul(ma x){
		ma res;res.clear();
		For(i,0,n-1)For(j,0,n-1)For(k,0,n-1)res.a[i][j]=(res.a[i][j]+1ll*a[i][k]*x.a[k][j])%mod;
		return res;
	}
	ma del(ma x){
		ma res;
		For(i,0,n-1)For(j,0,n-1)res.a[i][j]=(a[i][j]-x.a[i][j]+mod)%mod;
		return res;
	}
	ma add(ma x){
		ma res;
		For(i,0,n-1)For(j,0,n-1)res.a[i][j]=(a[i][j]+x.a[i][j])%mod;
		return res;
	}
}g,d,I,O,s1,s2;
struct Ma{
	ma a[2][2];
	void clear(){For(i,0,1)For(j,0,1)a[i][j]=O;}
	void init(){For(i,0,1)For(j,0,1)a[i][j]=(i==j?I:O);}
	Ma mul(Ma x){
		Ma res;res.clear();
		For(i,0,1)For(j,0,1)For(k,0,1)res.a[i][j]=res.a[i][j].add(a[i][k].mul(x.a[k][j]));
		return res;
	}
}a,b,c;
void output(ma x){
	int ans=0;
	For(i,0,n-1) ans=(ans+x.a[i][i])%mod;
	cout<<ans<<endl;
}
signed main(){IOS;
	cin>>n>>m>>k;
	g.clear();
	d.clear();
	I.init();
	O.clear();
	int x,y;
	For(i,1,m){
		cin>>x>>y;
		x--;y--;
		g.a[x][y]++;
		g.a[y][x]++;
		d.a[x][x]++;
		d.a[y][y]++;
	}
	s1=g;
	s2=(g.mul(g)).del(d);
	if(k==1) output(s1);
	else if(k==2) output(s2);
	else{
		k-=2;
		a.a[0][0]=g;a.a[0][1]=I.del(d);
		a.a[1][0]=I;a.a[1][1]=O;
		b.init();
		while(k){
			if(k&1) b=b.mul(a);
			k>>=1;
			a=a.mul(a);
		}
		output(b.a[0][0].mul(s2).add(b.a[0][1].mul(s1)));
	} 
return 0;}
```

---

## 作者：phil071128 (赞：1)

## CF1662C 题解

给出一种和现有题解不同的，更 tricky 的做法，并附带更详细的容斥式子。（不过多次询问矩阵转向量 trick 应该已经人尽皆知了吧）。

先考虑确定起点和终点怎么做？如果没有限制的话是传递闭包矩阵乘法的经典例题，既然加入限制，那么首先想到的是增加维度。

设 $g_{t,y,x}$ 表示走了 $t$ 步，当前在 $y$，上一步在 $x$ 的方案数。那么有转移：
$$
g_{t,y,x}=\sum_{z\to x,z\ne y} g_{t-1,x,z}\tag1
$$
由此可以写出一个 $O(n^6\log )$ 复杂度的暴力，如何优化到 $O(n^3\log)$？首先要做的就是**减少状态**。

设 $f_{t,y}$ 表示 $\sum g_{t,y,x}$，我们尝试能否写出转移。
$$
f_{t,y}=\sum_{x\to y} (f_{t-1,x}-g_{t-1,x,y})\tag2
$$
将 $(1)$ 代入 $(2)$，那么有：
$$
f_{t,y}=\sum_{x\to y}(f_{t-1,x}-\sum _{z\to y,z\ne x}g_{t-2,y,z})
\\
=\sum_{x\to y}f_{t-1,x}-(f_{t-2,y}-g_{t-2,y,x})
\\
=\sum f_{t-1,x} -deg_i\times f_{t-2,y}+f_{t-2,y}
\\
=\sum_{x\to y} f_{t-1,x} - (deg_i+1)f_{t-2,y}
$$
至此，我们将 $n^2$ 的状态优化为了 $2n$。再枚举起点和终点，发现这是经典的多次询问，查询矩阵快速幂。用经典的向量 trick 即可做到 $O(n^3\log k)$ 复杂度，预处理转移矩阵的 $2^k$，每次询问相当于一个初始向量乘以 $\log $ 个矩阵，而一次向量和矩阵相乘复杂度是 $O(n^2)$ 的。

注意有细节，直接写过不了样例：起点上一步不确定。因此**需要特殊处理第二步跳回起点的情况**。

内层循环八位展开应该是矩阵乘法性价比很高的卡常技巧了，不过不加也可以轻松过。

```cpp
struct mat{
	int a[N*2][N*2];
	mat() {
		memset(a,0,sizeof a);
	}
	void init() {
		for(int i=0;i<siz;i++) {
			a[i][i]=1;
		}
	}
	int * operator [] (int x) {
		return a[x];
	}
	mat operator * (mat b) const {
		mat c;
		for(int i=0;i<h;i++) {
			for(int j=0;j<siz;j++) {
				ll res=0;
				for(int k=0;k<siz;k+=8) {
					res=0;
					res+=(1ll*a[i][k]*b.a[k][j]);
					res+=(1ll*a[i][k+1]*b.a[k+1][j]);
					res+=(1ll*a[i][k+2]*b.a[k+2][j]);
					res+=(1ll*a[i][k+3]*b.a[k+3][j]);
					res+=(1ll*a[i][k+4]*b.a[k+4][j]);
					res+=(1ll*a[i][k+5]*b.a[k+5][j]);
					res+=(1ll*a[i][k+6]*b.a[k+6][j]);
					res+=(1ll*a[i][k+7]*b.a[k+7][j]);
					c.a[i][j]=(1ll*c.a[i][j]+res)%mod;
				}
			}
		}
		return c;
	}
	void print() {
		for(int i=0;i<h;i++) {
			for(int j=0;j<siz;j++) cout<<a[i][j]<<" ";
			cout<<endl;
		}
		return ;
	}
};
mat ksm(mat a,int b) {
	if(b==1) return a;
	mat s=ksm(a,b/2);s=s*s;
	if(b%2==1) s=s*a;
	return s;
}
mat trans[35];
vector<int>s[N];
int dp[11][N][N],g[N][N];
void work() {
	memset(dp,0,sizeof dp);
	dp[0][st][0]=1;	g[st][0]=1;
	for(int i=1;i<=1;i++) {
		for(int u=1;u<=n;u++) {
			for(int v=1;v<=n;v++) {
				if(!g[u][v]) continue;
				for(int k=0;k<=n;k++) 
					if(k!=u&&g[v][k]) dp[i][u][v]=(dp[i][u][v]+dp[i-1][v][k])%mod;
			}
		}
	}
	g[st][0]=0;
}
int deg[N];
signed main(){
//	fil();
	int k;
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;i++) {
		int u=read(),v=read();
		g[u][v]=g[v][u]=1;
		s[u].push_back(v);s[v].push_back(u);
		deg[u]++,deg[v]++;
	}
	siz=n*2;h=siz;
	for(int y=1;y<=n;y++) {
		for(int x:s[y]) {
			trans[0][x-1][y-1]=1;
		}
		trans[0][y+n-1][y-1]=(-(deg[y]-1)+mod);
		trans[0][y-1][y+n-1]=1;
	}
	for(int i=1;i<=31;i++) trans[i]=trans[i-1]*trans[i-1];
	h=1;
	int ans=0,tmp_k=k;
	for(st=1;st<=n;st++) {
		k=tmp_k;
		ed=st;
		mat res;
		res[0][st-1]=1;
		work();
		if(k<=1) {
			for(int j=1;j<=n;j++) if(j!=ed) ans=(ans+dp[k][ed][j])%mod;
			continue;
		}
		res=res*trans[1];
		res[0][st-1]=0;
		k-=2;
		for(int i=30;i>=0;i--) {
			if((1ll<<i)<=k) res=res*trans[i],k-=(1ll<<i);
		}
		ans=(ans+res[0][ed-1])%mod;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：lsj2009 (赞：1)

### Solution

设 $f_{k,u,v}$ 表示有多少长为 $k$ 且从 $u\to v$ 的路径。

易得 $f_{k,u,v}\to f_{k+1,u,w}$ 和 $-f_{k-1,u,v}\times (deg_v-1)\to f_{k+1,u,v}$。其中前者的转移条件是存在边 $(v,w)$，含义为从 $u$ 走到 $w$；后者含义为 $v$ 通过每条出边反复横跳一遍又重新回来，其中 $-1$ 是减去连续在 $v$ 点待着不动。

不妨将 $f_k$ 看出一个 $n\times n$ 的矩阵，其中第 $i$ 行第 $j$ 列表示 $f_{k,i,j}$ 的值，且设 $G$ 为原图的邻接矩阵，$D$ 为每个点的度数矩阵（即 $D_{u,u}=deg_u$），易得转移方程：

$$f_k=f_{k-1}\times G-f_{k-2}\times (D-I)$$

这显然是一个广义斐波那契数列的形式，只不过系数是矩阵；套路地，考虑矩阵快速幂加速，得：

$$
\begin{bmatrix}
  f_k & f_{k-1}\\
\end{bmatrix}
\times 
\begin{bmatrix}
  G & I\\
  (I-D) & 0\\
\end{bmatrix}
=
\begin{bmatrix}
  f_{k+1} & f_k\\
\end{bmatrix}
$$

然后就做完了，复杂度 $\Theta(n^3\log{k})$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=1e2+5,MOD=998244353;
int n,m,k;
void add(int &a,int b) {
    a+=b;
    if(a>=MOD)
        a-=MOD;
}
struct matrix {
    int c[N][N];
    matrix() {
        cl(c,0);
    }
    void init() {
        rep(i,1,n)
            c[i][i]=1;
    }
    matrix operator * (const matrix &tmp) const {
        matrix res;
        rep(i,1,n) {
            rep(j,1,n) {
                rep(k,1,n)
                    add(res.c[i][j],c[i][k]*tmp.c[k][j]%MOD);     
            }
        }
        return res;
    }
    matrix operator + (const matrix &tmp) const {
        matrix res;
        rep(i,1,n) {
            rep(j,1,n)
                res.c[i][j]=(c[i][j]+tmp.c[i][j])%MOD;
        }
        return res;
    }
    matrix operator - (const matrix &tmp) const {
        matrix res;
        rep(i,1,n) {
            rep(j,1,n)
                res.c[i][j]=(c[i][j]-tmp.c[i][j]+MOD)%MOD;
        }
        return res;
    }
}; matrix g,deg,I;
struct Matrix {
    static const int n=2;
    matrix c[n+1][n+1];
    Matrix operator * (const Matrix &tmp) const {
        Matrix res;
        rep(i,1,n) {
            rep(j,1,n) {
                rep(k,1,n)
                    res.c[i][j]=res.c[i][j]+(c[i][k]*tmp.c[k][j]);
            }
        }
        return res;
    }
};
Matrix qpow(Matrix res,Matrix base,int b) {
    while(b) {
        if(b&1)
            res=res*base;
        base=base*base; b>>=1;
    }
    return res;
}
signed main() {
    scanf("%lld%lld%lld",&n,&m,&k);
	I.init();
    while(m--) {
        int u,v;
        scanf("%lld%lld",&u,&v);
        g.c[u][v]=g.c[v][u]=1;
        ++deg.c[u][u];
        ++deg.c[v][v];
    }
    //f[i]=f[i-1]*g-f[i-2]*(deg-1)
    Matrix res,base;
	res.c[1][2]=g; 
    res.c[1][1]=(g*g)-deg;
	base.c[1][1]=g; 
    base.c[1][2]=I;
	base.c[2][1]=I-deg;
    if(k==1) {
        int ans=0;
        rep(i,1,n)
            add(ans,res.c[1][2].c[i][i]);
        printf("%lld\n",ans);
        return 0;
    }
    res=qpow(res,base,k-2);
    int ans=0;
    rep(i,1,n)
        add(ans,res.c[1][1].c[i][i]);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

考虑 $dp_{i,j}$ 表示长度为 $i$，从 $j$ 到 $k$ 的符合要求的路径数量。

如果没有可以重复经过的要求，转移时容易的。

有要求的话可以使用容斥，减去 $i$ 和 $i+2$ 在同一个位置的方案数，注意到 $i$ 的边时不会被算进去的，故不用减去，也就是系数为 $deg_i-1$，前两轮系数为 $deg_i$。矩阵快速幂优化即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
struct mtx{
	int a[205][205];
}ept;
mtx mul(mtx x,mtx y){
	mtx z=ept;
	for(int i=1;i<=200;i++){
		for(int j=1;j<=200;j++){
			if(x.a[i][j]){
				for(int k=1;k<=200;k++){
					(z.a[i][k]+=x.a[i][j]*y.a[j][k])%=mod;
				}
			}
		}
	}
	return z;
}
mtx qp(mtx a,int b){
	mtx ans=ept; for(int i=1;i<=200;i++) ans.a[i][i]=1;
	while(b){
		if(b&1) ans=mul(ans,a);
		a=mul(a,a);
		b>>=1;
	}
	return ans;
}
int deg[105];
signed main(){
	mtx base0=ept,base1=ept;
    int n,m,k; cin>>n>>m>>k;
    if(k<=2){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=m;i++){
    	int u,v; cin>>u>>v;
    	deg[u]++,deg[v]++;
    	base0.a[u][v]=base0.a[v][u]=base1.a[u][v]=base1.a[v][u]=1;
	}
	for(int i=1;i<=n;i++) base0.a[i][i+n]=base1.a[i][i+n]=1,base0.a[i+n][i]=mod-deg[i],base1.a[i+n][i]=mod-deg[i]+1;
	base0=mul(mul(base0,base0),qp(base1,k-2));
	int ans=0;
	for(int i=1;i<=n;i++) (ans+=base0.a[i][i])%=mod;
	cout<<ans;
	return 0;
}

```

---

