# [ICPC 2022 Xi'an R] Streets

## 题目描述

给定 $n$ 条垂直的线和 $m$ 条水平线，每条线有重量。定义一个矩形是好的，当且仅当矩形的四个边都落在这些线上，好矩形的代价等于其内部四条边的长度与对应线重量的乘积之和。请找出最大面积的好矩形，使得其代价不超过 $c$。注意，矩形的长度和宽度可以为零。

## 样例 #1

### 输入

```
3 4 20
1 3 4
3 1 2
1 3 4 7
4 2 1 2
1
5
6
7
9
10
11
12
15
16
17
22
23
28
30
35
43
47
49
57
```

### 输出

```
0
0
1
1
1
2
2
3
3
4
4
6
6
9
9
12
12
12
18
18
```

# 题解

## 作者：jun头吉吉 (赞：3)

## 题意
给定 $n,m,x_1,\dots,x_n,a_1,\dots,a_n,y_1,\dots,y_m,b_1,\dots,b_m$，有 $T$ 次询问，每次给出 $c$，你需要找到一组 $i_1,i_2,j_1,j_2$ 满足 $1\le i_1\le i_2\le n,1\le j_1\le j_2\le m$，$(x_{i_2}-x_{i_1})(b_{j_1}+b_{j_2})+(y_{j_2}-y_{j_1})(a_{i_1}+a_{i_2})\le c$，使得 $(x_{i_2}-x_{i_1})(y_{j_2}-y_{j_1})$ 最大，并输出最大值。

$1\le n,m\le5000,T\le 100,1\le a_i,b_i\le 10^7,c\le 10^{12}$

$1\le x_1< \dots < x_n\le 10^5,1\le y_1<\dots<y_m\le 10^5$

## 题解

记 $L=10^5$。

设 $va_v$ 表示 $x_{j}-x_i=v$ 的最小的 $a_i+a_j$ 值，$vb$ 同理，这两个显然可以用 $\mathcal O(n^2+m^2)$ 求出。那么我们要做的等价于：

$$
\begin{array}{cc}
\max&i\times j\\
\text{s.t.} &i\times vb_j+j\times va_i\le c
\end{array}
$$

如果给定 $(i,va_i)$ 只需要判断后一个条件是否满足的话，显然可以对 $(i,vb_i)$ 建立下凸壳，在凸包上二分找到最小值，单次查询时间复杂度为 $\mathcal O(\log L)$。

然后我们枚举 $(i,va_i)$，是可以在 $\mathcal O(\log^2 L)$ 的复杂度找到最大的 $j$ 满足条件的，就是我们可以判断存不存在 $j\ge x$ 满足条件，对这个后缀建立凸包，和上面一样二分判断即可。


后缀凸包其实就是从后往前建凸包，往栈里加点和删点就等价于是在树上新增一个儿子或者跳回父亲，最后得到一棵 $\mathcal O(L)$ 个节点的树，每一个后缀凸包就对应一条到根的链。

当然这样单次询问 $\mathcal O(L\log^2L)$ 是过不去的。这个二分看起来很蠢。我们考虑从 $1$ 到 $L$ 枚举 $j$，然后找到最大的 $i$ 使得后缀凸包存在一个点满足 $\le c$，随着 $j$ 的增大 $i$ 是减小的，所以总的判断次数是 $\mathcal O(L)$ 的，也就做到了 $\mathcal O(L\log L)$ 单次询问。

## 代码
```cpp
const int N=5e3+10,L=1e5,M=L+10,K=18;
const int inf=0x3f3f3f3f;
int n,m,T,mx,x[N],a[N],y[N],b[N];
int va[M],vb[M],fa[M][K];ll c;
struct point{
	int x,y;point(int x=0,int y=0):x(x),y(y){}
	point operator-(point rhs){return point(x-rhs.x,y-rhs.y);}
	ll operator*(point rhs){return 1ll*x*rhs.y-1ll*y*rhs.x;}
}st[M];int top;
ll get(int i,int j){return 1ll*i*vb[j]+1ll*j*va[i];}
bool chk(int i,int j){
	// x>=j  i bx + x ai 的最小值
	for(int l=K-1;~l;l--)if(fa[fa[j][l]][0]&&get(i,fa[j][l])>=get(i,fa[fa[j][l]][0]))j=fa[j][l];
	if(fa[j][0]&&get(i,fa[j][0])<=c)return 1;
	return get(i,j)<=c;
}
void work(){
	ll ans=0;
	for(int j=1,i=L;j<=L&&i;)
		if(vb[j]==inf)j++;
		else if(va[i]==inf||!chk(i,j))i--;
		else chkmx(ans,1ll*i*j),j++;
	writeln(ans);
}
signed main(){
	read(n,m,T);memset(va,0x3f,sizeof va);memset(vb,0x3f,sizeof vb);
	readArr(x+1,n);readArr(a+1,n);readArr(y+1,m);readArr(b+1,m);
	for(int i=1;i<n;i++)for(int j=i+1;j<=n;j++)chkmn(va[x[j]-x[i]],a[i]+a[j]);
	for(int i=1;i<m;i++)for(int j=i+1;j<=m;j++)chkmn(vb[y[j]-y[i]],b[i]+b[j]);
	for(int i=L;i;i--)if(vb[i]!=inf){
		point p(i,vb[i]);
		while(top>=2&&(st[top]-p)*(st[top-1]-p)<=0)top--;
		if(top)fa[i][0]=st[top].x;
		st[++top]=p;
	}
	for(int i=1;i<K;i++)for(int j=1;j<=L;j++)fa[j][i]=fa[fa[j][i-1]][i-1];
	while(T--)read(c),work();
}
```

---

## 作者：Alex_Wei (赞：2)

### [P9368 [ICPC 2022 Xi'an R] Streets](https://www.luogu.com.cn/problem/P9368)

设 $n, m$ 同阶。

设选取矩形的左右边界横坐标为 $x_1, x_2(x_1\leq x_2)$，权值为 $a_1, a_2$，上下边界的纵坐标为 $y_1, y_2(y_1\leq y_2)$，权值为 $b_1, b_2$，则矩形的代价为 $(x_2 - x_1)(b_1 + b_2) + (y_2 - y_1)(a_1 + a_2)$。

固定 $x_2 - x_1$，为最小化矩形的代价，需要最小化 $a_1 + a_2$。设 $va_i$ 表示当 $x_2 - x_1 = i$ 时 $a_1 + a_2$ 的最小值，同理设 $vb_i$。这部分是 $\mathcal{O}(n ^ 2)$，因为有 $\min + $ 卷积的限制所以做不到更快。

枚举 $i$，则要求最大的 $j$，使得 $f(i, j) = i\times vb_j + j\times va_i\leq c$。

考虑二分答案，相当于对所有 $j\geq mid$ 求 $f(i, j)$ 的最小值。固定 $i$ 之后，$f(i, j) = i(\frac {va_i} i\times j + vb_j)$。把 $(j, vb_j)$ 看成平面上的点，那么就是求一段后缀的点在给定斜率 $\frac {va_i} i$ 下的截距最小值。

用线段树维护区间凸包结合凸包二分，单次询问 $\mathcal{O}(v\log v\log ^ 2n)$，其中 $v$ 是坐标的范围。

对每个 $i$ 都二分太浪费了。注意到答案是 $\max_{f(i, j) \leq c} ij$，考虑从大到小枚举 $i$，并维护指针 $p$ 表示对所有 $j\geq p$，$f(i, j) > c$。当 $i$ 减小的时候，如果存在 $j\geq p$ 使得 $f(i, j) > c$，那么使用 $ij$ 更新答案，并让 $p\gets j + 1$。因为 $i$ 是降序枚举，所以只有 $p$ 增加才有可能更新答案，这保证了正确性。此时单次询问 $\mathcal{O}(v\log ^ 2 n)$。

现在后缀凸包的左端点 $p$ 单调不降，所以先从右往左做一遍凸包，并记录每个点弹出哪些点，这样在左端点右移时即可快速还原凸包。时间复杂度 $\mathcal{O}(n ^ 2 + Tv\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int N = 5e3 + 5;
constexpr int V = 1e5 + 5;

int n, m, T;
ll a[N], b[N], X[N], Y[N], x[V], y[V];

int top, stc[V];
vector<int> buc[V];
ll cross(int i, int j, int k) {
  return (j - i) * (x[k] - x[j]) - (k - j) * (x[j] - x[i]);
}

int main() {
  cin >> n >> m >> T;
  for(int i = 0; i < V; i++) x[i] = y[i] = 1e13;
  for(int i = 1; i <= n; i++) cin >> X[i];
  for(int i = 1; i <= n; i++) cin >> a[i];
  for(int i = 1; i <= m; i++) cin >> Y[i];
  for(int i = 1; i <= m; i++) cin >> b[i];
  for(int i = 1; i <= n; i++) {
    for(int j = i + 1; j <= n; j++) {
      x[X[j] - X[i]] = min(x[X[j] - X[i]], a[i] + a[j]);
    }
  }
  for(int i = 1; i <= m; i++) {
    for(int j = i + 1; j <= m; j++) {
      y[Y[j] - Y[i]] = min(y[Y[j] - Y[i]], b[i] + b[j]);
    }
  }
  stc[1] = V - 1;
  for(int i = V - 2; i; i--) {
    while(top > 2 && cross(i, stc[top], stc[top - 1]) <= 0) {
      buc[i].push_back(stc[top--]);
    }
    reverse(buc[i].begin(), buc[i].end());
    stc[++top] = i;
  }
  while(T--) {
    static int tmp[V];
    memcpy(tmp, stc, V << 2);
    ll c, ans = 0, pt = 1, ttop = top;
    cin >> c;
    auto ok = [&](ll a, ll b) {
      int l = 1, r = top;
      while(l < r) {
        int m = l + r >> 1;
        if(a * x[stc[m]] + b * stc[m] <= a * x[stc[m + 1]] + b * stc[m + 1]) r = m;
        else l = m + 1;
      }
      if(a * x[stc[l]] + b * stc[l] <= c) {
        ans = max(ans, a * pt), top--;
        for(int it : buc[pt]) stc[++top] = it;
        return pt++, 1;
      }
      else return 0;
    };
    for(int i = V - 1; i; i--) {
      while(ok(i, y[i]));
    }
    cout << ans << "\n";
    memcpy(stc, tmp, V << 2), top = ttop;
  }
  return 0;
}
```

---

