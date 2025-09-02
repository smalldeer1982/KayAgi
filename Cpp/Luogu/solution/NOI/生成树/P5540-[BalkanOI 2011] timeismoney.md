# [BalkanOI 2011] timeismoney

## 题目描述

给出一个 $n$ 个点 $m$ 条边的无向图，第 $i$ 条边有两个权值 $a_i$ 和 $b_i$ 。

求该图的一棵生成树 $T$ ，使得

$$\left(\sum_{e\in T}a_e\right)\times\left(\sum_{e\in T}b_e\right)$$

最小。

## 说明/提示

对于 $100\%$ 的数据，$1\leq n\leq 200,1\leq m\leq 10000,0\leq a_i,b_i\leq 255$ 。

## 样例 #1

### 输入

```
4 5
0 1 1 2
0 2 2 3
0 3 1 5
1 3 3 4
2 3 1 3```

### 输出

```
3 10```

# 题解

## 作者：xgzc (赞：24)

将$\sum a_i$和$\sum b_i$分别看成$x$和$y$，并将它投射到平面直角坐标系上，那么我们就是想找到$x \times y$最小的点。

先找出$x$最小的点$\mathrm{A}$以及$y$最小的点$\mathrm B$，接下来我们就需要求出一个点$\mathrm C$，使得$\mathrm C$在$\mathrm {AB}$左侧且$\mathrm C$距离$\mathrm {AB}$最远。

也就是让$S_{\triangle ABC}$最大，即$\overrightarrow{\mathrm{AB}} \times \overrightarrow{\mathrm{AC}}$最小（因为$\overrightarrow{\mathrm{AB}} \times \overrightarrow{\mathrm{AC}} < 0$）

![tree.png](https://i.loli.net/2019/08/30/X9FlBnVtmqNi3vx.png)

$$\begin{aligned}\because \overrightarrow{\mathrm{AB}} \times \overrightarrow{\mathrm{AC}} &= (x_{\mathrm{B}} - x_{\mathrm{A}})(y_{\mathrm{C}} - y_{\mathrm{A}}) - (y_{\mathrm{B}} - y_{\mathrm{A}})(x_\mathrm{C} - x_\mathrm{A}) \\&= (x_\mathrm B - x_\mathrm A) \times y_\mathrm C + (y_\mathrm A - y_\mathrm B) \times x_\mathrm C + y_\mathrm B x_\mathrm A - x_\mathrm B y_\mathrm A\end{aligned}$$

所以考虑最小化$(x_\mathrm B - x_\mathrm A) \times y_\mathrm C + (y_\mathrm A - y_\mathrm B) \times x_\mathrm C$。

于是可以直接将边权改为$w_i = (y_\mathrm A - y_\mathrm B) \times a_i + (x_\mathrm B - x_\mathrm A)\times b_i$，跑最小生成树算法即可得到$\mathrm C$点。

接下来递归处理$\mathrm {AC, CB}$即可。

这个过程中我们可以知道，决策点构成了一个含有$n!$个点的凸包。因为在$n$个点的凸包上的点数期望是$\sqrt {\ln n}$的，所以复杂度为$\mathrm{O}(n\log n\sqrt {\ln n!})$。

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>

inline int read()
{
	int data = 0, w = 1; char ch = getchar();
	while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if (ch == '-') w = -1, ch = getchar();
	while (ch >= '0' && ch <= '9') data = data * 10 + (ch ^ 48), ch = getchar();
	return data * w;
}

const int N(205), M(10010);
struct vector { int x, y; }; vector ans = (vector) {(int) 1e9, (int) 1e9};
inline vector operator - (const vector &lhs, const vector &rhs)
	{ return (vector) {lhs.x - rhs.x, lhs.y - rhs.y}; }
inline int operator * (const vector &lhs, const vector &rhs)
	{ return lhs.x * rhs.y - lhs.y * rhs.x; }
void chkmin(vector &x, vector y)
{
	long long _x = 1ll * x.x * x.y, _y = 1ll * y.x * y.y;
	if (_x > _y || (_x == _y && x.x > y.x)) x = y;
}

int n, m, fa[N], rnk[N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int merge(int x, int y)
{
	x = find(x), y = find(y);
	return (rnk[x] == rnk[y] ? fa[x] = y, ++rnk[y] :
			(rnk[x] < rnk[y] ? fa[x] = y : fa[y] = x));
}

struct edge { int x, y, a, b, w; } e[M];
inline int operator < (const edge &lhs, const edge &rhs) { return lhs.w < rhs.w; }
vector Kruskal()
{
	vector res = (vector) {0, 0}; int cnt = 0;
	for (int i = 1; i <= n; i++) fa[i] = i, rnk[i] = 1;
	std::sort(e + 1, e + m + 1);
	for (int i = 1; i <= m && cnt < n - 1; i++)
	{
		int x = find(e[i].x), y = find(e[i].y);
		if (x != y) merge(x, y), res.x += e[i].a, res.y += e[i].b, ++cnt;
	}
	return res;
}

void solve(const vector &A, const vector &B)
{
	for (int i = 1; i <= m; i++)
		e[i].w = e[i].a * (A.y - B.y) + e[i].b * (B.x - A.x);
	vector C = Kruskal(); chkmin(ans, C);
	if ((B - A) * (C - A) >= 0) return;
	solve(A, C), solve(C, B);
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; i++)
		e[i] = (edge) {read() + 1, read() + 1, read(), read(), 0};
	for (int i = 1; i <= m; i++) e[i].w = e[i].a;
	vector A = Kruskal(); chkmin(ans, A);
	for (int i = 1; i <= m; i++) e[i].w = e[i].b;
	vector B = Kruskal(); chkmin(ans, B);
	solve(A, B); printf("%d %d\n", ans.x, ans.y);
	return 0;
}
```

---

## 作者：shenxinge (赞：18)

选自 [浅谈一类最小乘积问题](https://www.luogu.com.cn/blog/shenxinge/qian-tan-yi-lei-zui-xiao-sheng-ji-wen-ti)

>题目描述

>给出一个 $n$ 个点 $m$ 条边的无向图，第 $i$ 条边有两个权值 $a_i$ 和 $b_i$ 。求该图的一棵生成树 $T$ ，使得
$$\left(\sum_{e\in T}a_e\right)\times\left(\sum_{e\in T}b_e\right)$$
>最小。

令 $x=\sum_{e\in T}a_e$ , $y=\sum_{e\in T}$ , 那么每一棵生成树对应二维平面上的点 $x,y$ 。

#### 凸性证明

我们考虑用曲线 $k=xy$ 来截这些点 , 于是需要找到 $k$ 最小的曲线使得有点在这条曲线上 , 容易发现这个点肯定在下凸壳上 , 考虑证明 。

我们设凸包上的点 $(a,b)$ , $(a+c,b+d)$ , 有 $c>0,d<0$ 。

那么我们假定一个凸包内的点 $(a+ct,b+dt)$ , 有 $0 \leq t \leq 1$ 。

那么这个点的代价是 :

$$(a+ct)(b+dt)=cdt^2+(ad+bc)t+ab$$

由于 $cd<0$ , 关于 $t$ 的代价函数是一个开口向下的二次函数 , 那么这个最小值一定存在于边界也就是 $t=0$ 或者是 $t=1$ 的情况 , 由此得证凸性。

#### quick-convex 构造

有该结论以后可以找到 $x$ 最大的点和 $y$ 最大的点 , 使用一步 $quick-convex$ 算法即可完成 。

接下来具体讲述如何使用 `quick-convex` 算法 。

对于目前已有点 $A$ 和 $B$ ， 目的是要求 $AB$ 线段最下方的点 $C$ 。将其分为 $AC$ 和 $CB$ 两段 ， 然后接着分治下去 。

考虑如何找到最下方的点 $C$ ， 可以用面积考虑 。 我们需要找到一个点 $C$ 使得 $S_{\Delta ABC}$ 最小 。

用向量表示 $\vec{AB} , \vec{AC}$ , 面积是 $S=-\frac{\vec{AB}\times \vec{AC}}{2}$ , 考虑打开这个柿子 。

$${\vec{AB}} \times {\vec{AC}}={(x_B-x_A)(y_C-y_A)-(x_C-x_A)(y_B-y_A)}$$

$$=(x_B-x_A)y_C+(y_A-y_B)x_C-(x_B-x_A)y_A+(y_B-y_A)x_A$$

发现后面两项是常数 , 前面两项与 $C$ 有关 。 

考虑将边权改为 $(x_B-x_A)b_i + (y_A-y_B)a_i$ 即可得到 $C$ 的坐标 。

#### 另一种转化

看到这个边权 ， 我们其实发现这是一个最小化和 $AB$ 同斜率在 $y$ 轴截距最小直线的问题 。 令直线 $AB$ 斜率为 $-k$ ， 需要最小化 $kx+y$ 的值 ， 把每条边权替换成 $ka_i+b_i$ 可以得到和上面一样的柿子。

#### 关键代码

```cpp
inline void solve(Point A,Point B)
{
	For(i,1,m)
		e[i].w=e[i].b*(B.x-A.x)+e[i].a*(A.y-B.y);
	Point C=kruskal();
	if(cross((B-A),(C-A))>=0) return;
	solve(A,C),solve(C,B);
}
```


#### 时间复杂度分析

真的没有营养 ， 没有必要去看。

另外这种做法的时间复杂度其实一直是个迷 ， 理论分析比较困难。

接下来将证明 $n$ 个点凸包上的点是 $R^{\frac{2}{3}}$ 级别的 , 其中 $R$ 为点的坐标范围 , 是 $[0-R]$ 的 , 本题中 $R=max(suma,sumb)$。

考虑我们构造出的凸壳大小为 $T$ , 我们得到的凸壳点集为 $V$ , 这个凸壳是一个左下凸壳 。 考虑翻转凸壳变为右下凸壳 , 得到的点集按横坐标进行排序得到 $(x_i,y_i)$ ，由于是右下下凸壳 , 斜率从0开始依次递增 ， 而且斜率两两不相等 。

所以可以设 $v_iv_{i+1}$ 的斜率为 $\frac{p}{q}$ , $p,q$ 为互质的正整数 。 可以得到 :

$\frac{y_{i+1}-y_i}{x_{i+1}-x_i} = \frac{p}{q}$ , 显然是有 $y_{i+1}-y_i=p \times t,x_{i+1}-x_i=q \times t$ , $t \geq 1$ 。

那么就有 $(x_{i+1}+y_{i+1})-(x_i+y_i)=(p+q) \times t \geq p+q$

所有柿子相加 ， 那么就有 $x_T+y_T-(x_1+y_1) \geq \sum_{i=1}^{T-1} p_i+q_i$ 。

容易得知 

$$x_T+y_T-(x_1+y_1) \leq R+R$$ 

$$sum_{i=1}^{T-1} p_i+q_i \leq 2 \times R$$

于是我们需要找到一个最小的 $T'$ 使得对于分子分母和前 $T'$ 小的分子分母均为正整数的既约分数 (注意不是既约真分数) , 其分子分母的和大于 $2 \times R$ , 这个 $T'$ 就是 $T$ 的上界。我们在下文所叙述的 $T$ 的意义即为 $T'$ 也就是 $T$ 的上界。

分子分母均为既约分数的前 $i$ 小分子分母和的大小记为 $F_i$ ,实质上是正整数到正有理数的正则双射中的分母 $\leq 1$ 的情况 [A038567](https://oeis.org/A038567) ，构造序列 $P$ 使得每个数 $i$ 都恰好在 $P$ 中连续出现 $i$ 次 , 也就是数列 [A002024](https://oeis.org/A002024) , 令其前 $i$ 项的和为 $G_i$ 。考虑到分子分母和为 $i$ 且分子分母都为正整数的既约分数不会超过 $i$ 个 , 所以一定有 $F(i) \geq G(i)$ , 要证 $F(T) \geq 2 \times R $ 只需要证明 $G(T) \geq 2 \times R $ 即可 。

考虑如何对于 $G(T)$ 求和 , 我们考虑 $P$ 的详尽定义是对于 $i \geq 1$ , $\frac{i\times (i-1)}{2} < j \le \frac{i \times (i+1)}{2}$ , 有 $P_i=j$ 。

于是对于下标为 $\frac{i \times (i+1)}{2}$ 的 $G(\frac{i \times (i+1)}{2})=\sum_{j=1}^{i} i^2$

考虑令 $t=\lfloor \sqrt{T} \rfloor$ 容易得到 $G(T) \geq G(\frac{t \times (t+1)}{2}) = \sum_{i=1}^{t} i^2$

众所周知平方和等于 :

$$\sum_{i=1}^{t} i^2=\frac{t(t+1)(2t+1)}{6}$$

也就是:

$$\frac{t(t+1)(2t+1)}{6} \geq 2 \times R$$

的最小的 $T$ , 解出来可以近似认为是 $R^{\frac{2}{3}}$ 级别的 (不会真的有人去解吧） ，由于放缩的问题其实离上界有一定的距离 , 其实跑起来效率是很高的 。 

其实对于这个问题我们只取了左下凸壳 , 容易得知对于一个凸包来说 ， 它的大小是 $4T$ ， 其实更接近于 $R^{\frac{2}{3}}$ 。

回到本题 , 这样的话凸包上的点的个数为 $O((na)^{\frac{2}{3}}) $ 级别 ， 所以本体的复杂度事实上是 $O((na)^{\frac{2}{3}}m logm) $ 的 , $logm$ 在于对边排序 , 如果你会 $O(m)$ 线性最小生成树的话那就可以做到 $O((na)^{\frac{2}{3}}m) $ 。

#### 总结与评价
其实能看出来这种套路推广不是很多 , 题目相对较少因为它实在太过于 $educational$ 以至于一道类似的题目只能区分做过这道题目与没有做过这道题目的人 。 是一种图论和计算几何的结合比较好的类型 。

因为二维乘积形式太过于完美联想到二维平面 ， 导致我很难有别的优美的 $idea$ 讲一些代价形成的点映射到二维平面上 。 如果有的话请务必告诉我 (因为笔者是在太菜了,水平真的有限,能力真的不够) 

`quick-convex` 做法是一种增量法 ， 理论上来讲可以推广到高维空间 , 但我觉得没有必要 ， 而且时间复杂度的分析会变得更加困难 , 实现也会很麻烦 , 等我会了三维凸包再来（其实要退役了 , 也没有机会去学了）。

---

## 作者：何俞均 (赞：11)

广告：脱更许久的[$blog$](https://www.cnblogs.com/heyujun/p/10398181.html)

如果我们只有一个条件要满足的话直接最小生成树就可以了，但是现在我们有两维啊。。。

我们将每个方法的**费用和时间**看作一个二维坐标$(x,y)$

则我们要求$x\centerdot y=k$最小即要求反比例函数$y=\frac kx$的图像离坐标轴最近。

那么我们怎么求呢？分下面三步：

* $Step1$

分别求出离$y,x$轴最近的点，这个通过直接最小生成树一维排序可以求出。

* $Step2$

现在我们的情况是这样的：

![img](https://i.loli.net/2019/02/18/5c6ab34002bc8.png)

$A$,$B$是我们刚才固定的，现在我们需要找到一个点$C$，使$C$在$AB$左侧且离$AB$最远。

这个怎么办呢？

其实就是让$S_{\triangle ABC}$的面积最大。

因为有

$\vec {AB}=(B.x-A.x,B.y-A.y)$

$\vec {AC}=(C.x-A.x,C.y-A.y)$

且有$S_{\triangle ABC}=\frac {\vec{AB}*\vec{AC}}2$(但是这个面积是有向的且为负，所以要使这两个向量乘起来最小)

所以我们要最小化：

$\vec{AB}*\vec{AC}$

$=(B.x-A.x)*(C.y-A.y)-(B.y-A.y)*(C.x-A.x)$

$=(B.x-A.x)*C.y+(A.y-B.y)*C.x+...$

因为~~我懒~~后面部分是常数，所以省略了。

那么我直接将改边权为$(B.x-A.x)y[i]+(A.y-B.y)x[i]$，做最小生成树即可。

* $Step3$

现在找到了$C$，递归处理$(A,C)$、$(C,B)$即可。

终止条件$\vec {BA} * \vec{CA}\geq0$，说明此时$C$已经跑到$AB$右侧去了。

代码

```cpp
#include <iostream> 
#include <cstdio> 
#include <cstdlib> 
#include <cstring> 
#include <cmath> 
#include <algorithm> 
using namespace std;  
const int MAX_N = 205; 
const int MAX_M = 1e4 + 5; 
struct Point { int x, y; } ;
Point ans = {(int)1e9, (int)1e9}; 
Point operator - (const Point &l, const Point &r) { return (Point){l.x - r.x, l.y - r.y}; } 
int cross(const Point &l, const Point &r) { return l.x * r.y - l.y * r.x; } 
int N, M, pa[MAX_N], rnk[MAX_N]; 
int getf(int x) { return pa[x] == x ? x : pa[x] = getf(pa[x]); } 
inline void unite(int x, int y) { 
    x = getf(x), y = getf(y); 
    if (rnk[x] == rnk[y]) pa[x] = y, ++rnk[y]; 
    else (rnk[x] < rnk[y]) ? (pa[x] = y) : (pa[y] = x); 
} 
struct Edge { int u, v, c, t, w; } e[MAX_M]; 
inline bool operator < (const Edge &l, const Edge &r) { return l.w < r.w; }
#define RG register 
inline Point kruskal() { 
    Point res = (Point){0, 0}; 
    int tot = 0; 
    for (RG int i = 1; i <= N; ++i) pa[i] = i, rnk[i] = 1; 
    sort(&e[1], &e[M + 1]); 
    for (RG int i = 1; i <= M; ++i) { 
        int u = getf(e[i].u), v = getf(e[i].v); 
        if (u != v) unite(u, v), res.x += e[i].c, res.y += e[i].t, ++tot;
        if (tot == N - 1) break; 
    } 
    long long Ans = 1ll * ans.x * ans.y, now = 1ll * res.x * res.y; 
    if (Ans > now || (Ans == now && res.x < ans.x)) ans = res; 
    return res; 
} 
void Div(const Point &A, const Point &B) { 
    for (RG int i = 1; i <= M; ++i) e[i].w = e[i].t * (B.x - A.x) + e[i].c * (A.y - B.y); 
    Point C = kruskal(); 
    if (cross(B - A, C - A) >= 0) return ; 
    Div(A, C); Div(C, B); 
} 
int main() { 
#ifndef ONLINE_JUDGE 
    freopen("cpp.in", "r", stdin); 
#endif
    scanf("%d%d", &N, &M); 
    for (RG int i = 1; i <= M; i++) scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].c, &e[i].t); 
    for (RG int i = 1; i <= M; i++) ++e[i].u, ++e[i].v, e[i].w = e[i].c; 
    Point A = kruskal(); 
    for (RG int i = 1; i <= M; i++) e[i].w = e[i].t; 
    Point B = kruskal(); 
    Div(A, B); 
    printf("%d %d\n", ans.x, ans.y); 
    return 0; 
} 
```

---

## 作者：Math_rad_round (赞：9)

这道题的具体解法就不在这里重复了，我只在这里说一个被众多人忽略的优化，成倍刷新最优解。

在如下的分治中，如果我们的端点是两个黑点，显然下一步递归到的点在绿色区域内。因此，得到的答案不会少于蓝色区域的面积，如果蓝色区域比当前答案大（或者持平），那自然不用算了。

![](https://cdn.luogu.com.cn/upload/image_hosting/n2d74q3p.png)

就是这样一个难度不高的优化，只需要一行优化，就可以成倍加快搜索效率。
而且在此类题目中都有不俗的表现，不知道之前为什么没有用的

```cpp
void sov(int a1,int b1,int a2,int b2){
    if(a1*b2>=aa*ab)return;//aa和bb是历史答案
	int x=b1-b2,y=a2-a1;ans(x,y);
    //这个函数求解以xa+yb做边权，对应的sum a和sum b返回给x,y
   if(x*y<aa*ab||(x*y==aa*ab&&x<aa)){aa=x;ab=y;}
	if((y-b1)*1LL*(a2-a1)-(b2-b1)*1LL*(x-a1)>=0)return;
	sov(a1,b1,x,y);sov(x,y,a2,b2);
}
```
另外，最小生成树最好选择 prim 的 $O(n^2)$，效率比 $O(m\log m)$ 快不少，（用优先队列维护的 prim 也是 $O(m\log m)$

完整代码贴[剪贴板](https://www.luogu.com.cn/paste/8xurmh00)

---

## 作者：AzusaCat (赞：9)

给定 $n$ 个点 $m$ 条边的无向图，每条边有两个权值 $a_i,b_i$，求一棵生成树使得
$$
\left(\sum\limits_{e\in T} a_e\right)\left(\sum\limits_{e\in T} b_e\right)
$$
最小，输出乘积最小时的 $\sum\limits_{e\in T} a_e$ 和 $\sum\limits_{e\in T} b_e$。$n\leqslant 200$，$m\leqslant 10000$，$0\leqslant a_i,b_i\leqslant 255$，$a_i,b_i\in N$。



对于任意一棵生成树，我们把其映射到平面直角坐标系中的一个点 $(\sum a_e,\sum b_e)$，那么我们所求即为 $xy$ 最小的点。我们不难发现它一定在所有点构成的左下凸壳上。

我们先分别令 $a_e=0$ 和 $b_e=0$，这样求出的是只有一种权值时的最小生成树，故其横/纵坐标一定最小，所以这两个点一定在凸包上（更精确的说，左下凸壳的两个端点）。

然后，我们考虑所有还可能在凸壳上的点，设刚才确定的两个点为 $A,B$，则如果一个点 $C$ 可能成为凸壳上的点，其一定在 $AB$ 的左下方。同时，在 $AB$ 左下方距离 $AB$ 最远的点一定在凸壳上，所以我们考虑求出这个距离 $AB$ 最远的点 $C$。

![](https://s1.ax1x.com/2020/10/16/07LUEV.md.png)

如图所示（其实每个点都应该是整点，我没画好），我们现在已知 $A,B$ 的坐标，想要求出这个点 $C$，换句话说，我们要找到那个使得 $\triangle ABC$ 的面积最大的点。假设 $A,B,C$ 的坐标分别为 $(x_A,y_A),(x_B,y_B),(x_C,y_C)$，则 $S_{\triangle ABC}=-\dfrac{1}{2}(\overrightarrow{AB}\times \overrightarrow{AC})$ ，故我们需要让 $\overrightarrow{AB}\times \overrightarrow{AC}$ 最小。下面我们来推一下式子：
$$
\begin{aligned}
&\overrightarrow{AB}\times \overrightarrow{AC}\\
=&(x_B-x_A)(y_C-y_A)-(x_C-x_A)(y_B-y_A)\\
=&x_By_C-x_By_A-x_Ay_C+x_Ay_A-x_Cy_B+x_Cy_A+x_Ay_B-x_Ay_A\\
=&(x_B-x_A)y_C+(y_A-y_B)x_C-x_By_A+x_Ay_B
\end{aligned}
$$
后两项是常数，所以我们要让 $(x_B-x_A)y_C+(y_A-y_B)x_C$ 最小，只需要对每条边 $e$，将 $v_e$ 设为 $(y_A-y_B)a_e+(x_B-x_A)b_e$，然后求最小生成树得到的那棵树即为点 $C$。这里可能有多个点 $C$ 在同一条直线的情况，但是并不重要。

然后，我们看刚才那张图，$D,E$ 也是凸壳上的点，所以我们要对 $AC,BC$ 递归做下去，直到当前直线左下方没有点，也就是叉积大于等于 $0$，最后取所有点的最小值。

考虑分析复杂度，刚才那个过程实际上是一个叫做 QuickHull 的求凸包算法。不难发现，我们一共做了 $O(凸壳上的点数)$ 次最小生成树。由于所有生成树对应的点都是整点，而且点数远远高于值域范围 $na$，据 EI 说此时凸壳上的点数最大是 $O((na)^{\frac{2}{3}})$ 的，所以总复杂度为 $O(n^{\frac{8}{3}}a^{\frac{2}{3}})$（prim 实现 MST）。

代码（比较懒所以写了 kruskal 多一个 $\log$）：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,fa[205];
ll ans=3e9,ansx,ansy;
struct edge{int s,t,a,b,v;}e[10005];
bool cmp(edge x,edge y){return x.v<y.v;}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void mst(ll &rx,ll &ry)
{
    rx=ry=0;
    for(int i=1;i<=n;i++)fa[i]=i;
    sort(e+1,e+m+1,cmp);
    for(int i=1;i<=m;i++)
    {
        int fx=find(e[i].s),fy=find(e[i].t);
        if(fx==fy)continue;
        rx+=e[i].a,ry+=e[i].b,fa[fx]=fy;
    }
    if(rx*ry<ans)ans=rx*ry,ansx=rx,ansy=ry;
}
void solve(ll ax,ll ay,ll bx,ll by)
{
    for(int i=1;i<=m;i++)e[i].v=(ay-by)*e[i].a+(bx-ax)*e[i].b;
    ll rx,ry;
    mst(rx,ry);
    if((ay-by)*rx+(bx-ax)*ry-bx*ay+ax*by<0)solve(ax,ay,rx,ry),solve(rx,ry,bx,by);
}
int main()
{
    ll ax,ay,bx,by;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)scanf("%d%d%d%d",&e[i].s,&e[i].t,&e[i].a,&e[i].b),e[i].s++,e[i].t++,e[i].v=e[i].a;
    mst(ax,ay);
    for(int i=1;i<=m;i++)e[i].v=e[i].b;
    mst(bx,by);
    solve(ax,ay,bx,by);
    printf("%lld %lld",ansx,ansy);
    return 0;
}
```



---

## 作者：Leasier (赞：4)

算是个套路吧。

把最小生成树换成选数使得本质不同子集异或数量最多就成了昨天的模拟赛 T3。~~写起来除了把 Kruskal 换成线性基外就没有任何区别（~~

------------

前置芝士：[最小生成树](https://oi-wiki.org/graph/mst/)、[凸包](https://oi-wiki.org/geometry/convex-hull/)

考虑把所有合法方案 $(\sum a, \sum b)$，我们将其当成一个实数对放在一个二维平面上。

那么我们所求的答案一定在这些点围成的**下凸包上**。

首先我们不难求出离 $x, y$ 轴最近的两个点——对 $a, b$ 两维分别 Kruskal 即可。

下面设当前讨论的两个点为 $P, Q$，其中 $x_P \leq x_Q, y_P \geq y_Q$。

现在我们希望求一个点 $R$，使得 $x_P \leq x_R \leq x_Q, y_P \geq y_R \geq y_Q$ 且 $R$ 到 $PQ$ 的距离最大。

显然这就是要求 $S_{\Delta PQR}$ 最大，即求 $\vec{PQ} \times \vec{PR}$ 最小。

对该式展开，得到：$x_R(y_P - y_Q) + y_R(x_Q - x_P) + (x_P y_Q - x_Q y_P)$。

后面那坨是常数，我们只关心前面那部分。

不难发现我们可以将其分配到每条边中——即令边权为 $a(y_P - y_Q) + b(x_Q - x_P)$，然后求最小生成树即可。

现在我们得到了两个新的子问题：$P, R$ 和 $R, Q$。

分治下去并记录中途得到的所有答案的最小值即可。当 $R = P$ 或 $R = Q$ 停止分治。

现在我们来考虑时间复杂度。不难发现，我们会对下凸包上的每个点进行一次 Kruskal，而（据说）下凸包上点数至多为 $O(\sqrt{w})$，其中 $w = \max(\sum a_i, \sum b_i)$。于是时间复杂度为 $O(\sqrt{w} (n + m \log m))$。

代码：
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef struct {
	int start;
	int end;
	int dis1;
	int dis2;
	int dis3;
} Edge;

int ansx = 0x7fffffff, ansy = 0x7fffffff;
int u[10007], v[10007], a[10007], b[10007], root[207];
Edge edge[10007];

bool operator <(const Edge a, const Edge b){
	if (a.dis3 != b.dis3) return a.dis3 < b.dis3;
	return a.dis1 < b.dis1;
}

inline void init(int n){
	for (register int i = 1; i <= n; i++){
		root[i] = i;
	}
}

int get_root(int x){
	if (root[x] == x) return x;
	return root[x] = get_root(root[x]);
}

inline void update(pair<int, int> pr){
	ll x = (ll)ansx * ansy, y = (ll)pr.first * pr.second;
	if (x > y || (x == y && ansx > pr.first)){
		ansx = pr.first;
		ansy = pr.second;
	}
}

inline pair<int, int> kruskal(int n, int m){
	int dot_cnt = 1;
	pair<int, int> ans(0, 0);
	for (register int i = 1; i <= m; i++){
		int x_root = get_root(edge[i].start), y_root = get_root(edge[i].end);
		if (x_root != y_root){
			root[x_root] = y_root;
			ans.first += edge[i].dis1;
			ans.second += edge[i].dis2;
			if (++dot_cnt == n) break;
		}
	}
	update(ans);
	return ans;
}

inline void solve(int n, int m, pair<int, int> pr1, pair<int, int> pr2){
	int t1 = pr1.second - pr2.second, t2 = pr2.first - pr1.first;
	pair<int, int> pr3;
	init(n);
	for (register int i = 1; i <= m; i++){
		edge[i].start = u[i];
		edge[i].end = v[i];
		edge[i].dis1 = a[i];
		edge[i].dis2 = b[i];
		edge[i].dis3 = t1 * a[i] + t2 * b[i];
	}
	sort(edge + 1, edge + m + 1);
	pr3 = kruskal(n, m);
	if (pr3 != pr1 && pr3 != pr2){
		solve(n, m, pr1, pr3);
		solve(n, m, pr3, pr2);
	}
}

int main(){
	int n, m;
	pair<int, int> pr1, pr2;
	cin >> n >> m;
	for (register int i = 1; i <= m; i++){
		cin >> u[i] >> v[i] >> a[i] >> b[i];
		u[i]++;
		v[i]++;
	}
	init(n);
	for (register int i = 1; i <= m; i++){
		edge[i].start = u[i];
		edge[i].end = v[i];
		edge[i].dis1 = edge[i].dis3 = a[i];
		edge[i].dis2 = b[i];
	}
	sort(edge + 1, edge + m + 1);
	pr1 = kruskal(n, m);
	init(n);
	for (register int i = 1; i <= m; i++){
		edge[i].start = u[i];
		edge[i].end = v[i];
		edge[i].dis1 = a[i];
		edge[i].dis2 = edge[i].dis3 = b[i];
	}
	sort(edge + 1, edge + m + 1);
	pr2 = kruskal(n, m);
	solve(n, m, pr1, pr2);
	cout << ansx << " " << ansy;
	return 0;
}
```

---

## 作者：UltiMadow (赞：3)

神仙题（

对于每一个生成树，我们令 $\sum a=x$，$\sum b=y$，并把 $(x,y)$ 作为坐标放进坐标系里，所以我们要求的就是 $x\cdot y$ 最小的点值

考虑分治

假设我们分治到了左右端点 $A,B$，我们要在横纵坐标都在 $A,B$ 之间尽可能接近坐标轴的点

记 $A(x_a,y_a)$，$B(x_b,y_b)$，设要求的点 $Q(x_0,y_0)$，使得 $S_{\Delta ABQ}$ 最大

则
$$
\begin{aligned}
S_{\Delta ABQ}&=-\frac 1 2 \overrightarrow {AQ}\times \overrightarrow{AB}\cr
&=-\frac 1 2[(x_0-x_a)(y_b-y_a)-(y_0-y_a)(x_b-x_a)]\cr
&=-\frac 1 2(x_0y_b-x_0y_a-x_ay_b+x_ay_a-y_0x_b+y_0x_a+y_ax_b-y_ax_a)
\end{aligned}
$$

把常量去掉，只考虑剩下的 $x_0(y_b-y_a)-y_0(x_b-x_a)$，即要求 $x_0(y_b-y_a)-y_0(x_b-x_a)$ 最小

把 $x_0$ 替换为 $\sum a$，把 $y_0$ 替换为 $\sum b$，于是把边权替换成 $a(y_b-y_a)-b(x_b-x_a)$ 跑 kruskal 即可

跑完需要验证 $Q$ 是否在直线 $AB$ 下侧，在的话以 $A,Q$，$Q,B$ 为左右端点继续分治，不在的话就不继续分治了

还有一个问题，为什么找到 $S_{\Delta ABQ}$ 最大的 $Q$ 之后不直接以 $Q$ 为答案而要分治递归呢？

这里有一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/o57dqizf.png)

图中 $S_{\Delta ABQ}>S_{\Delta ABQ'}$，但是 $x_Qy_Q=2.25>1.5=x_{Q'}y_{Q'}$

也就是说 $Q'$ 比 $Q$ 更优，于是不能直接得到答案

code:
```cpp
#include<bits/stdc++.h>
#define MAXN 10010
#define int long long
const int inf=1e9;
using namespace std;
int n,m;
struct Node{int u,v,a,b,val;}Edge[MAXN];
bool cmp(Node x,Node y){return x.val<y.val;}
struct vect{
	int x,y;
	vect(int xx=0,int yy=0){x=xx;y=yy;}
}ans;
int operator *(vect a,vect b){return a.x*b.y-a.y*b.x;}
vect operator -(vect a,vect b){return vect(a.x-b.x,a.y-b.y);}
bool operator < (vect a,vect b){
	if(a.x*a.y!=b.x*b.y)return a.x*a.y<b.x*b.y;
	return a.x<b.x;
}
int f[MAXN];
int get(int x){return x==f[x]?x:f[x]=get(f[x]);}
vect kruskal(){
	sort(Edge+1,Edge+m+1,cmp);
	for(int i=1;i<=n;i++)f[i]=i;
	vect ret;
	for(int i=1;i<=m;i++){
		int u=Edge[i].u,v=Edge[i].v;
		int a=Edge[i].a,b=Edge[i].b;
		u=get(u);v=get(v);
		if(u==v)continue;
		f[u]=v;ret.x+=a;ret.y+=b;
	}
	if(ret<ans)ans=ret;
	return ret;
}
void solve(vect l,vect r){
	for(int i=1;i<=m;i++)
		Edge[i].val=(r.x-l.x)*Edge[i].b+(l.y-r.y)*Edge[i].a;
	vect mid=kruskal();
	if((r-l)*(mid-l)>=0)return;
	solve(l,mid);solve(mid,r);
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v,a,b;scanf("%lld%lld%lld%lld",&u,&v,&a,&b);
		u++,v++;Edge[i]=(Node){u,v,a,b,0};
	}ans.x=inf;ans.y=inf;
	for(int i=1;i<=m;i++)Edge[i].val=Edge[i].a;
	vect L=kruskal();
	for(int i=1;i<=m;i++)Edge[i].val=Edge[i].b;
	vect R=kruskal();solve(L,R);//L,R为全a和全b，作为递归初始值
	printf("%lld %lld",ans.x,ans.y);
	return 0;
}
```

---

## 作者：Filberte (赞：2)

对于一棵原图的生成树 $T$，令 $X(T) = \left(\sum_{e\in T}a_e\right) $，$Y(T) = \left(\sum_{e\in T}b_e\right)$，题目求的是 $X(T)  \times Y(T) $ 的最小值，将其记为 $W(T)$。对于此类问题，有一个经典的套路，就是把每棵树看成平面上的一个点。此时我们要找到一个点 $i$，使得 $x_i \times y_i$ 最小。

可以证明，这个点 $i$ 一定在下凸壳上。证明如下：如图，对于一条线段 $AB$ ，因为线段的两端都在坐标系第一象限，所以最优的点一定在线段的端点上。而对于下凸壳内每一个点（如图中点 C），过 C 做 AB 的垂线，交于点 D。一条线段上的最小值只会在端点处取到，有 $\min(W(A),W(B)) < W(D) < W (C)$。

因此下凸壳内部的点一定没有用。

![](https://cdn.luogu.com.cn/upload/image_hosting/h12vd4cq.png)

考虑怎么找到下凸壳上的所有点。此题中并不能直接求出所有点的坐标，所以求凸壳的常规方法并不适用。另辟蹊径，先分别找出 $x$ 坐标最小的点 $A$ 以及 $y$ 坐标最小的点 $B	$，接着找出 AB 左下方距离这条线段最短的点 C，然后递归处理 AC、BC。这样就能找到下凸壳上所有的点了。

现在考虑怎么找到一个点，使得它距离某条线段最远。![](https://cdn.luogu.com.cn/upload/image_hosting/agamqu9e.png)

图中的 C 就是满足条件的点。

目标转化：距离最远 $\Rightarrow$ $\Delta ABC$ 的高最长 $\Rightarrow$ $S_{\Delta ABC}$ 最大 $\Rightarrow$ $-\dfrac{1}{2} \overrightarrow{AB} \times \overrightarrow{AC}$ 最大  $\Rightarrow$ $\overrightarrow{AB} \times \overrightarrow{AC}$ 最小。
$$
\begin{aligned}
&\overrightarrow{AB} \times \overrightarrow{AC}\\ 
= &(x_b - x_a)(y_c - y_a) - (x_c - x_a)(y_b - y_a)\\
= &-(x_b - x_a)y_a + (y_{b} - y_{a})x_{a} + (x_{b} - x_{a})y_{c} + (y_a - y_b)x_{c}
\end{aligned}
$$
观察这个式子，前两项只跟 A 和 B 有关，无需考虑。所以我们最小化后边两项就行。我们把每条边的边权设置成 $(x_{b} - x_{a})b_i + (y_a - y_b)a_i$，然后跑一遍最小生成树，就能得到 $x_c$ 和 $y_c$ 了。接着递归处理即可。

**代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int M = 1e4 + 100;
struct Node{
	int x , y;
	friend bool operator == (Node i , Node j){
		return i.x == j.x && i.y == j.y;
	} 
}A , B;
struct E{
	int u , v , a , b;
}e[M];	
bool cmp_x(E i , E j){
	return i.a < j.a;
}
bool cmp_y(E i , E j){
	return i.b < j.b;
}
bool cmp(E i , E j){
	return (B.x - A.x) * i.b + (A.y - B.y) * i.a < (B.x - A.x) * j.b + (A.y - B.y) * j.a;
}
Node nmin(Node x , Node y){
	long long nx = 1LL * x.x * x.y , ny = 1LL * y.x * y.y;
	return (nx != ny) ? ((nx < ny) ? x : y) : ((x.x < y.x) ? x : y);
}
int n , m;
int fa[M];
void init(){for(int i = 0;i < n;i++) fa[i] = i;}
int find(int x){return x == fa[x] ? x : (fa[x] = find(fa[x]));}
Node Kruskal(int opt , Node l ,  Node r){
	Node res = (Node){0,0};
	int cnt = 0;	
	A = l , B = r;
	if(opt == 1) sort(e + 1 ,e + 1 + m , cmp);
	else if(opt == 2) sort(e + 1 ,e + 1 + m , cmp_x);
	else sort(e + 1 ,e + 1 + m , cmp_y);
	init();
	for(int i = 1;i <= m;i++){
		int x = find(e[i].u), y = find(e[i].v);
		if(x == y) continue;
		fa[x] = y;
		res.x += e[i].a , res.y += e[i].b;
		if(++cnt == n - 1) break;
	}
	return res;
}
long long cross(Node i , Node j , Node k){ //AB x AC
	return 1LL * (j.x - i.x) * (k.y - i.y) - 1LL * (j.y - i.y) * (k.x - i.x);
}
Node solve(Node l , Node r){
	Node res = nmin(l , r);
	Node mid = Kruskal(1 , l , r);
	if(cross(l , r , mid) >= 0) return res;
	res = nmin(nmin(solve(l , mid) , solve(mid , r)) , res);
	return res;
}
int main(){
	scanf("%d%d",&n,&m);
	Node ept = (Node){0,0};
	for(int i = 1;i <= m;i++) scanf("%d%d%d%d",&e[i].u,&e[i].v,&e[i].a,&e[i].b);
	Node l = Kruskal(2 , ept , ept) , r = Kruskal(3 , ept , ept);
	Node ans = solve(l , r);
	printf("%d %d\n",ans.x,ans.y); 
	return 0;
} 
```

---

## 作者：Foreverxxx (赞：0)

### 前置芝士

1. Kruskal 最小生成树算法。

2. 向量叉积计算公式：
	$A \times B = a_x \times b_y - a_y \times b_x$
    
### 思路

假设现在我们有了一颗生成树，分别为 $\displaystyle\sum_{e \in T}{a_1}$ 和 $\displaystyle\sum_{e \in T}{b_1}$，如果此时存在一颗乘积更小的生成树，分别为 $\displaystyle\sum_{e \in T}{a_2}$ 和 $\displaystyle\sum_{e \in T}{b_2}$，那么此时可能会有 $\displaystyle\sum_{e \in T}{a_2} > \displaystyle\sum_{e \in T}{a_1}$ 的情况存在，所以我们不能单独考虑两个值。

所以我们需要一个能够同时顾及到 $a$ 以及 $b$ 的东西来处理它，又因为这是两个值求和后相乘，所以我们想到了坐标轴。

我们现在把 $\displaystyle\sum_{e \in T}{a}$ 和 $\displaystyle\sum_{e \in T}{b}$ 看做坐标系的 $x$ 和 $y$ 坐标，那么每一颗生成树就是坐标系上的一个点。

因为我们不知道最终的答案会是什么样子，有可能 $\displaystyle\sum_{e \in T}{a}$ 很大而 $\displaystyle\sum_{e \in T}{b}$ 接近于零，也有可能 $\displaystyle\sum_{e \in T}{a}$ 接近于零而 $\displaystyle\sum_{e \in T}{b}$ 很大，所以我们首先需要对答案确定一个范围，然后考虑如何缩小点。

先解决范围的问题。

很明显，我们先求出离 $x$ 轴最近的一个点 $A$ 以及离 $y$ 轴最近的一个点 $B$，不难发现，在坐标系中，答案更小的一个生成树所对应的点 $C$ 一定位于 $AB$ 的左下方，如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/lh5fsiu1.png)

所以我们需要找到距离 $AB$ 最远的 $C$ 点。

根据三角形面积的公式，假设 $C$ 点距离 $AB$ 的距离为 $h$，那么 $S_{\triangle{ABC}}= \frac{1}{2} \times AB \times h$，所以我们只需要最大化 $S_{\triangle{ABC}}$ 就行了。

不过求出高是很困难的，所以这个时候我们需要搬出另外一个工具：**向量**。

那么这个时候就有了一个公式：

$$
	S_{\triangle{ABC}}= \frac{\overrightarrow{AB} \times \overrightarrow{AC}}{2}
$$

注意此处是向量叉积而不是点积。

我们再来推一波柿子：

$$
 \begin{aligned}\overrightarrow{AB} \times \overrightarrow{AC} &=
 (x_B-x_A)(y_C-y_A)-(x_C-x_A)(y_B-y_A)
 \\&=(x_B-x_A)y_C+(y_A-y_B)x_C-(x_B-x_A)y_A+(y_B-y_A)x_A
 \end{aligned}
$$

很明显，对于已知的两个点 $A$ 以及 $B$ 和所求的 $C$，后两项为常数，而可能发生改变的，只有前面两项。

所以我们在每一次找最小生成树的时候，只需要按照此时每条边的 $a$ 值和 $b$ 值重新赋值，然后求出尽量远离 $AB$ 的点 $C$，即跑一次最小生成树。

为了保证搜寻到答案，我们在求出 $C$ 后，还要以 $A$ 和 $C$ 以及 $B$ 和 $C$ 分别再次进行递归查找。

对于判断找不到更好的答案的情况，只需要判断找到的点 $C$ 在 $AB$ 右上方，即 $\overrightarrow{AB} \times \overrightarrow{AC} \ge 0$ 就行了。

### 一些细节

1. 注意向量叉积的使用。

2. 注意计算过程中可能出现的爆 ``int`` 的问题。

Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int sss=0;
	char chh=getchar();
	while(chh<'0'||chh>'9') chh=getchar();
	while(chh>='0'&&chh<='9'){
		sss=sss*10+chh-'0';
		chh=getchar();
	}
	return sss;
}
int n,m;
int fa[205];
struct node{
	int u,v,w,a,b;
}edge[10005];
struct point{
	int x,y;
};
point ans={(int)1e15,(int)1e15};
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
bool cmp(const node& x,const node& y){
	return x.w<y.w;
} 
inline point operator - (const point &a,const point &b){ //向量减法 
	return (point){a.x-b.x,a.y-b.y}; 
}
inline int operator * (const point &a,const point &b){//向量差积 
	return a.x*b.y-a.y*b.x; 
}
point kruskal(){
	point now={0,0};
	sort(edge+1,edge+m+1,cmp);
	int tot=0;
	for(register int i=1;i<=n+1;i++) fa[i]=i;
	for(register int i=1;i<=m;i++){
		if(tot==n-1) break;
		int fau=find(edge[i].u),fav=find(edge[i].v);
		if(fau!=fav){
			fa[fau]=fav;
			tot++;
			now.x+=edge[i].a;
			now.y+=edge[i].b;
		}
	}
	int ori_ans=ans.x*ans.y,now_ans=now.x*now.y;//更改答案 
	if(ori_ans>now_ans||(ori_ans==now_ans&&ans.x>now.x)){
		ans=now;
	}
	return now;
}
void solve(const point& A,const point& B){
	for(register int i=1;i<=m;i++){
		edge[i].w=edge[i].a*(A.y-B.y)+edge[i].b*(B.x-A.x);//公式，新的边权 
	}
	point C=kruskal();
	if((B-A)*(C-A)>=0) return;//向量乘法 
	solve(A,C),solve(C,B);
}
signed main(){
	n=read(),m=read();
	for(register int i=1;i<=m;i++){
		edge[i].u=read()+1;
		edge[i].v=read()+1;
		edge[i].a=read();
		edge[i].b=read();
	}
	//找X最小的店 
	for(register int i=1;i<=m;i++){
		edge[i].w=edge[i].a;
	}
	point A=kruskal();
	//找Y最小的点 
	for(register int i=1;i<=m;i++){
		edge[i].w=edge[i].b;
	}
	point B=kruskal();
	solve(A,B);//递归查找 
	cout<<ans.x<<" "<<ans.y;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 前置知识

1. Kruskal 最小生成树
2. 向量的叉积公式： $a \times b = a_x \times b_y - a_y \times b_x$

## 分析

我们将 $\sum_{e\in T}a_e$ 和 $ \sum_{e\in T}b_e$ 放进平面直角坐标系，即每一个点为 $(a_e, b_e)$，现在让你在这些点中找出一个最小的点 $(x, y)$ 使得 $x \times y$ 最小。

我们会发现 $(x, y)$ 的最小值所在的点一定是在左下凸壳中。

生成树的方法虽多，但是在左下凸壳的点比较少，所以现在的问题转化为 **找这个最小值的点**



![](https://cdn.luogu.com.cn/upload/image_hosting/io7j1q1f.png)

假设 $A$ 点为距离 $x$ 轴最靠近的点， $B$ 点位距离 $y$ 轴最靠近的点，为了找到答案 $C$ 点，题目相当于给了我们 $m$ 个点，让我们找一个点 $C_i(1\le i\le m)$ 使得 $C_i$ 点离 $AB$ 最远。


![](https://cdn.luogu.com.cn/upload/image_hosting/55423r0z.png)

让 $C$ 离 $AB$ 最远，即让 $S_\triangle ABC$ 尽量大，因为 $AB$ 长度不变，变的是 $S_\triangle ABC$ 的高 $h$。$h$ 既是 $C$ 离 $AB$ 的距离。

根据三角形的向量公式得：

$$S_\triangle ABC = -\dfrac{\overrightarrow {AB}\times \overrightarrow{AC}}{2}$$

为了让 $S_\triangle ABC$ 尽量大，既让 $\overrightarrow {AB}\times \overrightarrow{AC}$ 尽量小，用叉积表示即可得到：

![](https://cdn.luogu.com.cn/upload/image_hosting/89imuu44.png)

显然只有 $x_C,y_C$ 为变量，其他全为定值。

所以我们将所有的 $(x_B-x_A)\times b_i + (y_A-y_B)\times a_i$ 的权值作为一个图，从中找到一个最小生成树就做完了这一题。

# AC 代码

```cpp
/*****************************************
备注：
******************************************/
#include<queue>
#include<math.h>
#include<stack>
#include<stdio.h>
#include<iostream>
#include<vector>
#include<iomanip>
#include<map>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 1e5 + 10;
const int MR = 10 + 5;
const int INF = 0x3f3f3f3f;
const int MOD = 998244353;
int n, m;
struct _union//并查集
{
	int fa[MAXN];
	void init()//初始化
	{
		for(int i = 0;i < MAXN; i++)
		{
			fa[i] = i;
		}
	}
	int find(int id)
	{
		if(fa[id] == id)return id;
		return fa[id] = find(fa[id]);
	}
	void merge(int x,int y)//合并x,y
	{
		x=find(x);
		y=find(y);
		fa[x]=y;
	}
}unionf;
struct node//存图
{
	int u, v, w;//记录图
	int wa, wb;//记录当前的ai和bi的值
}e[MAXN];
bool cmp(node a,node b)//对这个图排序
{
	return a.w < b.w;
}
struct point//记录一个点
{
	int x, y;
	point(int a,int b)
	{
		x = a;
		y = b;
	}
	point()
	{
		x = y = 0;
	}
	friend point operator -(const point &a,const point &b)
	{
		point ans = point(a.x-b.x, a.y-b.y);
		return ans;
	}
}ans = point(INF, INF);
int chaji(point a,point b)//向量A,B的叉积
{
	return a.x * b.y - a.y * b.x;
}
point kruskal()//最小生成树求出点对
{
	point res = point(0, 0);
	sort(e + 1,e + m + 1, cmp);
	unionf.init();
	int cnt = 0;
	for(int i = 1;i <= m; i++)
	{
		int u = e[i].u;
		int v = e[i].v;
		if(unionf.find(u) == unionf.find(v))continue;
		cnt++;
		unionf.merge(u, v);
		res.x += e[i].wa;
		res.y += e[i].wb;
		if(cnt == n - 1)break;
	}
	int num1 = res.x * res.y;
	int num2 = ans.x * ans.y;
	if(num1 < num2 || (num1 == num2 && res.x < ans.x))
	{
		ans = res;
	}
	return res;
}
void solve(point x,point y)//分治
{
	for(int i = 1;i <= m; i++)
	{
		e[i].w = (y.x - x.x) * e[i].wb + (x.y - y.y) * e[i].wa;
	}
	point tmp = kruskal();
	if(chaji(y - x, tmp - x) >= 0)return ;
	solve(x, tmp);
	solve(tmp, y);
}
signed main()
{
	cin >> n >> m;
	for(int i = 1, u, v, wa, wb;i <= m; i++)
	{
		cin >> u >> v >> wa >> wb;
		u++, v++;
		e[i] = {u, v, 0, wa, wb};
	}
	for(int i = 1;i <= m; i++)e[i].w = e[i].wa;
	point tmpa = kruskal();
	for(int i = 1;i <= m; i++)e[i].w = e[i].wb;
	point tmpb = kruskal();
	solve(tmpa, tmpb);
	cout << ans.x << ' ' << ans.y;
	return 0;
}

```



---

## 作者：happybob (赞：0)

不妨将 $\sum \limits_{e \in T} a_e$ 和 $\sum \limits_{e \in T} b_e$ 分别作为 $x,y$ 放入平面直角坐标系，题目要求即求一个 $x \cdot y$ 最小的点对 $(x,y)$。

不难发现 $(x,y)$ 可能最小值所在的点一定为一个左下凸壳。

虽然生成树的个数极多，但是期望的在左下凸壳的点较少，找到这些最小值点即可。

接下来考虑如何求：

![https://cdn.luogu.com.cn/upload/image_hosting/ev68ov2k.png?x-oss-process=image/resize,m_lfit,h_1170,w_2225](https://cdn.luogu.com.cn/upload/image_hosting/ev68ov2k.png?x-oss-process=image/resize,m_lfit,h_1170,w_2225)

考虑三个点 $A,B,C$。其中 $C$ 点未知，$A,B$ 已知。

我们可以考虑求出离 $AB$ 最远的在其左下的点 $C$，然后分治求 $AC$ 和 $BC$ 的答案。

即最大化 $S_{\triangle ABC}$。

$S_{\triangle ABC} = -\dfrac{\overrightarrow{AB} \times\overrightarrow{AC} }{2}$。

需最大化 $S_{\triangle ABC}$，即考虑最小化 $\overrightarrow{AB} \times\overrightarrow{AC}$。

$\begin{aligned} & \; \; \; \; \;\overrightarrow{AB} \times\overrightarrow{AC} \\&= (x_b - x_a)(y_c-y_a)-(y_b-y_a)(x_c-x_a)\\ &= x_by_c-x_by_a-x_ay_c+x_ay_a-y_bx_c+y_bx_a+y_ax_c-y_ax_a \\ &= (x_b-x_a)y_c + (y_a-y_b)x_c + (x_a-x_b)y_a + (y_b - y_a)x_a\end{aligned}$。

显然只有 $y_c$ 和 $x_c$ 为变量，$a,b$ 均为定值。

所以将 $(x_b-x_a)b_i + (y_a-y_b)a_i$ 作为权值求最小生成树即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1e5 + 5;

class CG
{
public:
	struct Point
	{
		int x, y;
		Point(int _x, int _y): x(_x), y(_y){}
		Point()
		{
			x = y = 0;
		}
	};
	typedef Point Vector;
	friend Vector operator-(const Vector a, const Vector b)
	{
		return Vector(a.x - b.x, a.y - b.y);
	}
};
int cj(CG::Vector a, CG::Vector b)
{
	return a.x * b.y - a.y * b.x;
}
CG::Point ans = CG::Point(1e9, 1e9);

int n, m;
int u[N], v[N], a[N], b[N];

class Union_Find
{
public:
	int fa[N];
	void Init()
	{
		for (int i = 0; i <= n; i++) fa[i] = i;
	}
	int find(int u)
	{
		return fa[u] == u ? u : fa[u] = find(fa[u]);
	}
	void merge(int u, int v)
	{
		fa[find(u)] = find(v);
	}
};

struct Edge
{
	int u, v, w, aaa, bbb;
	bool operator<(const Edge& x) const
	{
		return w < x.w;
	}
}c[N];

Union_Find uf;

class Kruskal
{
public:
	CG::Point kruskal()
	{
		CG::Point res = CG::Point(0, 0);
		sort(c + 1, c + m + 1);
		uf.Init();
		int cnt = 0;
		for (int i = 1; i <= m && cnt < n - 1; i++)
		{
			int u = c[i].u, v = c[i].v;
			if (uf.find(u) != uf.find(v))
			{
				cnt++;
				uf.merge(u, v);
				res.x += c[i].aaa;
				res.y += c[i].bbb;
			}
		}
		if (res.x * res.y < ans.x * ans.y || (res.x * res.y == ans.x * ans.y && res.x < ans.x))
		{
			ans = res;
		}
		return res;
	}
}k;

void solve(CG::Point x, CG::Point y)
{
	for (int i = 1; i <= m; i++)
	{
		c[i].w = (y.x - x.x) * c[i].bbb + (x.y - y.y) * c[i].aaa;
	}
	CG::Point C = k.kruskal();
	if (cj(y - x, C - x) >= 0) return;
	solve(x, C);
	solve(C, y);
}

signed main()
{
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%lld%lld%lld%lld", &u[i], &v[i], &a[i], &b[i]);
		u[i]++;
		v[i]++;
		c[i].aaa = a[i];
		c[i].bbb = b[i];
		c[i].u = u[i], c[i].v = v[i];
	}
	for (int i = 1; i <= m; i++)
	{
		c[i].w = c[i].aaa;
	}
	CG::Point A = k.kruskal();
	for (int i = 1; i <= m; i++)
	{
		c[i].w = c[i].bbb;
	}
	CG::Point B = k.kruskal();
	solve(A, B);
	printf("%lld %lld\n", ans.x, ans.y);
	return 0;
}
```


---

