# [ABC251G] Intersection of Polygons

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc251/tasks/abc251_g

$ xy $ -平面上の凸 $ N $ 角形 $ P $ の頂点が、**反時計回り**に $ (x_1,\ y_1),\ (x_2,\ y_2),\ \ldots,\ (x_N,\ y_N) $ として与えられます。（ただし、$ x $ 軸の正の方向を右向き、$ y $ 軸の正の方向を上向きとします。）

この多角形 $ P $ に対して、$ M $ 個の凸 $ N $ 多角形 $ P_1,\ P_2,\ \ldots,\ P_M $ を考えます。  
 $ i\ =\ 1,\ 2,\ \ldots,\ M $ について多角形 $ P_i $ は、 多角形 $ P $ を $ x $ 軸の正の方向に $ u_i $ 、$ y $ 軸の正の方向に $ v_i $ だけ平行移動して得られる多角形です。すなわち、$ P_i $ は $ N $ 個の点 $ (x_1+u_i,\ y_1+v_i),\ (x_2+u_i,\ y_2+v_i),\ \ldots,\ (x_N+u_i,\ y_N+v_i) $ を頂点とする凸 $ N $ 角形です。

$ Q $ 個の点 $ (a_1,\ b_1),\ (a_2,\ b_2),\ \ldots,\ (a_Q,\ b_Q) $ のそれぞれについて、 「その点が $ M $ 個の多角形 $ P_1,\ P_2,\ \ldots,\ P_M $ のすべてに含まれるか」を判定してください。

ただし、点が多角形の境界上にある場合も、その点はその多角形に含まれるとみなします。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 50 $
- $ 1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ -10^8\ \leq\ x_i,\ y_i\ \leq\ 10^8 $
- $ -10^8\ \leq\ u_i,\ v_i\ \leq\ 10^8 $
- $ -10^8\ \leq\ a_i,\ b_i\ \leq\ 10^8 $
- 入力はすべて整数
- $ (x_1,\ y_1),\ (x_2,\ y_2),\ \ldots,\ (x_N,\ y_N) $ は反時計回りに凸多角形をなす
- 多角形 $ P $ のそれぞれの内角の大きさは $ 180 $ 度未満

### Sample Explanation 1

多角形 $ P $ は $ (-2,\ -3),\ (0,\ -2),\ (1,\ 0),\ (0,\ 2),\ (-2,\ 1) $ を頂点とする $ 5 $ 角形です。 - 多角形 $ P_1 $ は、$ P $ を $ x $ 軸の正の方向に $ 0 $ 、$ y $ 軸の正の方向に $ 1 $ だけ平行移動させた、$ (-2,\ -2),\ (0,\ -1),\ (1,\ 1),\ (0,\ 3),\ (-2,\ 2) $ を頂点とする $ 5 $ 角形です。 - 多角形 $ P_2 $ は、$ P $ を $ x $ 軸の正の方向に $ 1 $ 、$ y $ 軸の正の方向に $ 0 $ だけ平行移動させた、$ (-1,\ -3),\ (1,\ -2),\ (2,\ 0),\ (1,\ 2),\ (-1,\ 1) $ を頂点とする $ 5 $ 角形です。 よって、下記の通りに $ 6 $ 行出力します。 - $ (a_1,\ b_1)\ =\ (0,\ 0) $ は $ P_1 $ と $ P_2 $ の両方に含まれるので、$ 1 $ 行目には `Yes` を出力します。 - $ (a_2,\ b_2)\ =\ (1,\ 0) $ は $ P_2 $ には含まれますが $ P_1 $ には含まれないので、$ 2 $ 行目には `No` を出力します。 - $ (a_3,\ b_3)\ =\ (0,\ 1) $ は $ P_1 $ と $ P_2 $ の両方に含まれるので、$ 3 $ 行目には `Yes` を出力します。 - $ (a_4,\ b_4)\ =\ (1,\ 1) $ は $ P_1 $ と $ P_2 $ の両方に含まれるので、$ 4 $ 行目には `Yes` を出力します。 - $ (a_5,\ b_5)\ =\ (-1,\ -1) $ は $ P_1 $ と $ P_2 $ の両方に含まれるので、$ 5 $ 行目には `Yes` を出力します。 - $ (a_6,\ b_6)\ =\ (-1,\ -2) $ は $ P_2 $ には含まれますが $ P_1 $ には含まれないので、$ 6 $ 行目には `No` を出力します。 多角形の境界上にある点も多角形に含まれるとみなすことに注意してください。 !\[\](https://img.atcoder.jp/abc251/8216bd194340d2648ce000e9ac9a203e.png)

## 样例 #1

### 输入

```
5
-2 -3
0 -2
1 0
0 2
-2 1
2
0 1
1 0
6
0 0
1 0
0 1
1 1
-1 -1
-1 -2```

### 输出

```
Yes
No
Yes
Yes
Yes
No```

## 样例 #2

### 输入

```
10
45 100
-60 98
-95 62
-95 28
-78 -41
-54 -92
-8 -99
87 -94
98 23
87 91
5
-57 -40
-21 -67
25 39
-30 25
39 -20
16
4 5
-34 -8
-63 53
78 84
19 -16
64 9
-13 7
13 53
-20 4
2 -7
3 18
-12 10
-69 -93
2 9
27 64
-92 -100```

### 输出

```
Yes
Yes
No
No
Yes
No
Yes
No
Yes
Yes
Yes
Yes
No
Yes
No
No```

# 题解

## 作者：escapist404 (赞：0)

# AT_abc251_g Intersection of Polygons Solution

## Preface

由于某些 $\LaTeX$ 的原因，本文的公式无法正常查看，建议读者访问[博客](https://www.luogu.com.cn/blog/284754/solution-at-abc251-g)以获得正常阅读体验。

## Statement

逆时针地给定一个有 $N$ 个顶点，第 $i$ 个顶点为 $(x_i, y_i)$ 的凸包 $P_0$。

再给出 $M$ 个向量 $(u_i, v_i)$ 代表凸包 $P_1, P_2, \cdots, P_M$，凸包 $P_j$ 有 $N$ 个顶点，第 $i$ 个顶点为 $(x_i + u_j, y_i + v_j)$。

最后有 $Q$ 组询问，每次给定一个点 $(a_i, b_i)$，要求判断这个点是否在每一个凸包的内部。

*注意凸包的边上也算是它的内部。*

保证 $3 \le N \le 50$，$1 \le M, Q \le 2 \cdot {10}^5$，$-{10}^8 \le x_i, y_i, u_i, v_i, a_i, b_i \le {10}^8$。

## Solution

考虑某个询问 $(a, b)$。

注意到 $(a, b)$ 在多边形 $P_j$ 中，当且仅当其被 $N$ 条边“围住”，考虑利用向量的叉积进行判断。具体地：

对于从 $(x_i, y_i)$ 到 $(x_{i + 1}, y_{i + 1})$ 的向量 

$$
\mathbf{f_i}=
\begin{pmatrix}
   x_{i + 1} + u_j - (x_i + u_j) \\
   y_{i + 1} + v_j - (y_i + v_j)
\end{pmatrix}=
\begin{pmatrix}
   x_{i + 1} - x_i \\
   y_{i + 1} - y_i
\end{pmatrix}
$$

考虑另一条从 $(x_i + u_j, y_i + v_j)$ 到 $(a, b)$ 的向量

$$
\mathbf{d_i} = \begin{pmatrix}
   a - (x_i + v_j) \\
   b - (y_i + u_j)
\end{pmatrix}
$$

那么，如果有

$$
\mathbf{f_i} \times \mathbf{d_i} \ge 0
$$

即

$$
\begin{pmatrix}
   x_{i + 1} - x_i \\
   y_{i + 1} - y_i
\end{pmatrix}
\times
\begin{pmatrix}
   a - (x_i + v_j) \\
   b - (y_i + u_j)
\end{pmatrix}
\ge 0
$$

记为 $(S)$ 式。

就可以说明点 $(a, b)$ 在 $\mathbf{f_i}$ 方向的左侧，而顶点是逆时针给出的，因此 $(a, b)$ 必定在凸包内部。

> **向量的叉积**
规定

$$
\begin{pmatrix}
   a \\
   b
\end{pmatrix}
\times
\begin{pmatrix}
   c \\
   d
\end{pmatrix}
= ad - bc
$$
可以使用右手定则判断叉积的正负。

可参考下图进行理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/czw4udr6.png)

这样朴素地求解是 $O\big(Q N M\big)$ 的。考虑进行优化。

由

$$
\begin{pmatrix}
   a - (x_i + v_j) \\
   b - (y_i + u_j)
\end{pmatrix}= 
\begin{pmatrix}
   a \\
   b
\end{pmatrix}-
\begin{pmatrix}
   x_i + v_j \\
   y_i + u_j
\end{pmatrix}
$$

设

$$
\mathbf{g'_{i, j}} = 
\begin{pmatrix}
   x_i + v_j \\
   y_i + u_j
\end{pmatrix}
$$

$(S)$ 式等价于

$$
\begin{pmatrix}
   x_{i + 1} - x_i \\
   y_{i + 1} - y_i
\end{pmatrix}
\times
\begin{pmatrix}
   a \\
   b
\end{pmatrix}
\ge 
\begin{pmatrix}
   x_{i + 1} - x_i \\
   y_{i + 1} - y_i
\end{pmatrix}
\times
\begin{pmatrix}
   x_i + v_j \\
   y_i + u_j
\end{pmatrix}
$$

即

$$
\mathbf{f_i}
\times
\begin{pmatrix}
   a \\
   b
\end{pmatrix} 
\ge
\mathbf{f_i}
\times
\mathbf{g'_{i, j}}
$$

该式对所有 $j$ 成立的充要条件是

$$
\mathbf{f_i}
\times
\begin{pmatrix}
   a \\
   b
\end{pmatrix}
\ge 
\max^M_{\mathbf{j}=1} 
\big\lbrace
\mathbf{f_i}
\times
\mathbf{g'_{i, j}}
\big\rbrace = \mathbf{g_i}
$$

这样，我们预处理出 $\mathbf{f_i}$ 和 $\mathbf{g_i}$，在处理单个询问时枚举 $\mathbf i$ 即可。

时间复杂度为 $N + N M + N Q = O\big(N (M + Q)\big)$。

注意 $(x_N, y_N)$ 到 $(x_1, y_1)$ 的向量应当考虑为 $\mathbf{f_N}$。

## Reference

* [判断一个点在直线的哪边 - OI-wiki](https://oi-wiki.org//geometry/2d/#%E5%88%A4%E6%96%AD%E4%B8%80%E4%B8%AA%E7%82%B9%E5%9C%A8%E7%9B%B4%E7%BA%BF%E7%9A%84%E5%93%AA%E8%BE%B9)
* [向量的叉积（叉乘、外积）- OI-wiki](https://oi-wiki.org//math/linear-algebra/product/#%E5%A4%96%E7%A7%AF)
* [Accepted Submission](https://atcoder.jp/contests/abc251/submissions/42103528)

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class Vector {
    public:
    LL x, y;
    Vector(LL _x, LL _y)    {
        x = _x, y = _y;
    }
};
Vector operator + (const Vector x, const Vector y)  {
    return Vector(x.x + y.x, x.y + y.y);
}
Vector operator - (const Vector x, const Vector y)  {
    return Vector(x.x - y.x, x.y - y.y);
}
LL cross(const Vector x, const Vector y)    {
    return x.x * y.y - x.y * y.x;
}
vector <Vector> p, f;
vector <LL> g;
int n, m, q;
int main()  {
    ios::sync_with_stdio(0);
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        LL _x, _y;
        cin >> _x >> _y;
        Vector tmp(_x, _y);
        p.push_back(tmp);
    }
    p.push_back(p.front());
    for(int i = 0; i < n; ++i) {
        f.push_back(p[i + 1] - p[i]);
    }
    for(int i = 0; i < n; ++i)  {
        g.push_back(-1e18);
    }
    cin >> m;
    for(int i = 1; i <= m; ++i) {
        LL _u, _v;
        cin >> _u >> _v;
        Vector c(_u, _v);
        for(int j = 0; j < n; ++j)  {
            if(cross(f[j], (p[j] + c)) > g[j])  {
                g[j] = cross(f[j], (p[j] + c));
            }
        }
    }
    cin >> q;
    for(int i = 1; i <= q; ++i) {
        LL _a, _b;
        cin >> _a >> _b;
        Vector c(_a, _b);
        bool ans = 1;
        for(int j = 0; j < n && ans; ++j)  {
            ans &= (cross(f[j], c) >= g[j]);
        }
        cout << (ans ? "Yes" : "No") << endl;
    }
    return 0;
}
```

---

## 作者：shinkuu (赞：0)

提供一个本质相同，但是不需要会向量也能做，而且很好想的方法。

首先发现凸包点少，也就意味着边少，考虑从边的方向寻找突破口。

考虑一个凸包的本质：若干个直线划分出若干个半平面，它们的交即为这个凸包。如果一个点对于每一条直线，都在于凸包的同侧，那么这个点就在这个凸包内。

这样直接暴力做仍然是 $O(nmq)$ 的。但是明显发现每条直线相当于限制了，经过一个点 $(x,y)$，斜率为 $k$ 的直线的截距不小于/大于某个数。取其中最大/小的一个限制即可。$O(nm)$ 预处理出来，$O(nq)$ 解决。

要注意的是，这种写法细节比较多。平行于坐标轴的情况建议全部特判，test 5 极度卡精度，可以手写分数类解决。

比向量解法相对复杂，但是也很好写。

code：

```cpp
int n,m,q,a[N],b[N],op[N];
const double eps=1e-8;
struct frac{
	ll a,b;
	frac(ll _a=0,ll _b=1){
		a=_a,b=_b;
		if(b<0)a=-a,b=-b;
	}
	il bool operator<=(const frac &tmp)const{
		return (__int128)a*tmp.b<=(__int128)tmp.a*b;
	}
	il bool operator<(const frac &tmp)const{
		return (__int128)a*tmp.b<(__int128)tmp.a*b;
	}
	il frac operator-(const frac &tmp)const{
		return frac(a*tmp.b-b*tmp.a,b*tmp.b);
	}
	il frac operator*(const frac &tmp)const{
		return frac(a*tmp.a,b*tmp.b);
	}
}f[N],sl[N];
void check(int i,int j){
	if(a[i]==a[j]){
		if(b[i]<b[j])op[i]=2;
		else op[i]=4;
	}else if(b[i]==b[j]){
		if(a[i]>a[j])op[i]=3;
		else op[i]=5;
	}else{
		sl[i]=frac(b[i]-b[j],a[i]-a[j]);
		if(a[i]<a[j])op[i]=0;
		else op[i]=1;
	}
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n){
		scanf("%d%d",&a[i],&b[i]);
		if(i==1)
			continue;
		check(i,i-1);
	}
	check(1,n);
	rep(i,1,n){
		if(op[i]>=1&&op[i]<=3)f[i]=frac(-1ll*inf*inf,1);
		else f[i]=frac(1ll*inf*inf,1);
	}
	scanf("%d",&m);
	rep(j,1,m){
		int x,y;
		scanf("%d%d",&x,&y);
		rep(i,1,n){
			frac nx=frac(x+a[i],1),ny=frac(y+b[i],1);
			if(op[i]==0)f[i]=min(f[i],ny-nx*sl[i]);
			else if(op[i]==1)f[i]=max(f[i],ny-nx*sl[i]);
			else if(op[i]==2)f[i]=max(f[i],nx);
			else if(op[i]==3)f[i]=max(f[i],ny);
			else if(op[i]==4)f[i]=min(f[i],nx);
			else f[i]=min(f[i],ny);
		}
	}
	scanf("%d",&q);
	rep(j,1,q){
		frac x,y;
		scanf("%lld%lld",&x.a,&y.a);
		bool flag=true;
		rep(i,1,n){
			if(op[i]==0)flag&=y-x*sl[i]<=f[i];
			else if(op[i]==1)flag&=f[i]<=y-x*sl[i];
			else if(op[i]==2)flag&=f[i]<=x;
			else if(op[i]==3)flag&=f[i]<=y;
			else if(op[i]==4)flag&=x<=f[i];
			else flag&=y<=f[i];
		}
		if(flag)
			puts("Yes");
		else 
			puts("No");
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```
题外话：

zlt 怎么又做过？zlt 怎么又做过？zlt 怎么又做过？

---

