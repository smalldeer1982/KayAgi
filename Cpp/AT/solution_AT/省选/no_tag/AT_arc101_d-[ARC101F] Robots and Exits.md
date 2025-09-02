# [ARC101F] Robots and Exits

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc101/tasks/arc101_d

数直線上に $ N $ 体のロボットと $ M $ 個の出口があります。 これらの $ N\ +\ M $ 個の座標はすべて整数であり、すべて相異なります。 各 $ i $ ($ 1\ \leq\ i\ \leq\ N $) について、左から $ i $ 番目のロボットの座標は $ x_i $ です。 また、各 $ j $ ($ 1\ \leq\ j\ \leq\ M $) について、左から $ j $ 番目の出口の座標は $ y_j $ です。

すぬけ君は、次の $ 2 $ 種類の操作を好きな順序で繰り返し行い、ロボットを一斉に動かすことができます。

- 数直線上のすべてのロボットの座標を $ -1 $ する。
- 数直線上のすべてのロボットの座標を $ +1 $ する。

各ロボットは、いずれかの出口と重なった瞬間、その出口を通って数直線上から消えます。 すぬけ君は、すべてのロボットが消えるまで操作を行い続けます。

すべてのロボットが消えた後、各ロボットがどの出口を通ったかという組合せは何通りありうるでしょうか？ $ 10^9\ +\ 7 $ で割った余りを求めてください。 ただし、$ 2 $ 通りの組合せが異なるとは、あるロボットが存在し、そのロボットの通った出口が異なることを言います。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ M\ \leq\ 10^5 $
- $ 1\ \leq\ x_1\ <\ x_2\ <\ ...\ <\ x_N\ \leq\ 10^9 $
- $ 1\ \leq\ y_1\ <\ y_2\ <\ ...\ <\ y_M\ \leq\ 10^9 $
- 与えられる座標はすべて整数である。
- 与えられる座標はすべて相異なる。

### Sample Explanation 1

左から $ i $ 番目のロボットをロボット $ i $ と呼び、左から $ j $ 番目の出口を出口 $ j $ と呼びます。 $ ( $ロボット $ 1 $ が通った出口$ , $ ロボット $ 2 $ が通った出口$ ) $ の組合せとしてありうるものは、次の $ 3 $ 通りです。 - $ ( $出口 $ 1 $$ , $ 出口 $ 1 $$ ) $ - $ ( $出口 $ 1 $$ , $ 出口 $ 2 $$ ) $ - $ ( $出口 $ 2 $$ , $ 出口 $ 2 $$ ) $

### Sample Explanation 2

各ロボットごと独立に通る出口を決められるので、組合せは $ 2^3\ =\ 8 $ 通りです。

### Sample Explanation 3

どのロボットも出口 $ 1 $ を通ります。

## 样例 #1

### 输入

```
2 2
2 3
1 4```

### 输出

```
3```

## 样例 #2

### 输入

```
3 4
2 5 10
1 3 7 13```

### 输出

```
8```

## 样例 #3

### 输入

```
4 1
1 2 4 5
3```

### 输出

```
1```

## 样例 #4

### 输入

```
4 5
2 5 7 11
1 3 6 9 13```

### 输出

```
6```

## 样例 #5

### 输入

```
10 10
4 13 15 18 19 20 21 22 25 27
1 5 11 12 14 16 23 26 29 30```

### 输出

```
22```

# 题解

## 作者：DreamsChaser (赞：24)

更好的阅读体验：<https://www.cnblogs.com/DreamsChaser/p/15272849.html>

$\large\mathcal{Description}$

在一个数轴上有 $n$ 个 $\texttt{robot}$ 和 $m$ 个 $\texttt{exit}$.

每次操作可以把所有 $\texttt{robot}$ 同时向左或向右移动 $1$ 个单位长度，当一个 $\texttt{robot}$ 遇到了一个 $\texttt{exit}$, 它就会溜走。所有 $\texttt{robot}$ 溜走之后停止操作。

求 $\texttt{robot}$ 从 $\texttt{exit}$ 溜走的方案数。两个方案不同，当且仅当存在至少一个 $\texttt{robot}$ 从不同的 $\texttt{exit}$ 溜走。

答案对 $10^9+7$ 取模，$n, m\le 10^5.$

$\large\mathcal{Solution}$

首先我们可以不管比最左边 $\texttt{exit}$ 还左边的 $\texttt{robot}$, 因为它一定从最左边 $\texttt{exit}$ 溜走，对答案没有影响。同理，我们也可以不管比最右边 $\texttt{exit}$ 还右边的 $\texttt{robot}$.

我们现在单独拎出一个 $\texttt{robot}$ 进行研究。我们发现只有改变他向左或向右的最大值的操作才对这个 $\texttt{robot}$ 有效果。所以我们如果把这个 $\texttt{robot}$ 向左和向右的最大值作为一个平面坐标的两维的话，它的初始值是 $(0, 0)$, 然后不断地向上、向右延伸。

其实所有 $\texttt{robot}$ 的曲线都长一个样对吧。

那一个 $\texttt{robot}$ 何时溜走呢？是不是当他碰到了一个 $\texttt{exit}$ 的时候。也就是说，我们设初始时第 $i$ 个 $\texttt{robot}$ 距离离它最近的两边的 $\texttt{exit}$ 的距离分别是 $a_i, b_i$. 然后这条曲线碰到 $x=a_i$ 或 $y=b_i$ 的时候它就推出历史的舞台了。

而且答案只取决于曲线先碰到 $x=a_i$ 还是 $y=b_i$.

![](https://cdn.luogu.com.cn/upload/image_hosting/ywuv040u.png)

如果将 $\texttt{robot}$ 的左标定义为 $(a_i-0.5, b_i-0.5)$. 那么所有在曲线左上方的 $\texttt{robot}$ 都会从左侧的 $\texttt{exit}$ 溜走，在曲线右下方的 $\texttt{robot}$ 都会从右侧的 $\texttt{exit}$ 溜走。

对于每个从右侧 $\texttt{exit}$ 溜走的 $\texttt{robot}$ 的集合, 容易构造出与之唯一对应的折线：

![](https://cdn.luogu.com.cn/upload/image_hosting/5zungbtb.png)

感性理解一下，就是卡在每个 $\texttt{robot}$ （称为 $\texttt{BR}$）的直线。反之如果不能这样构造直线，我们也可以保证不存在直线使得这些 $\texttt{robot}$ 都在右下方。

那么方案数就等于这样的直线的个数。令 $f_i$ 表示延伸到第 $i$ 个机器人且这是个 $\texttt{BR}$. 转移方程显然：

$$f_i=\sum_{a_j<a_i,\ b_j<b_i}f_j+1$$

然后这是一个 $\mathcal{O}(n^2)$ 的转移式，显然是个二维偏序问题，用树状数组将其优化成 $\mathcal{O}(n\log n)$.

$\large\mathcal{Code}$

```cpp
const int N = 100010, mod = 1000000007;

int n, m, a[N], b[N], Max, dc[N];
pair<int, int> node[N];

struct BIT // 树状数组
{
    int c[N];
    void add(reg int x, reg int d) {for (; x <= Max; x += (x & (-x))) c[x] = (c[x] + d) % mod;}
    int ask(reg int x) {reg int sum = 0; for (; x; x -= (x & (-x))) sum = (sum + c[x]) % mod; return sum;}
} S;

int main()
{
    scanf("%d %d", &n, &m);
    for (reg int i = 1; i <= n; ++ i) scanf("%d", &a[i]);
    for (reg int i = 1; i <= m; ++ i) scanf("%d", &b[i]);
    
    reg int tot = 0;
    for (reg int i = 1; i <= n; ++ i)
    {
        reg int pos = lower_bound(b + 1, b + m + 1, a[i]) - b;
        if (pos == 1 || pos > m) continue;
        node[ ++ tot] = make_pair(a[i] - b[pos - 1], - (b[pos] - a[i]));
        dc[tot] = -node[tot].second;
    }

    // 离散化
    
    sort(node + 1, node + tot + 1);
    for (reg int i = 1; i <= n; ++ i) node[i].second *= -1;
    sort(dc + 1, dc + tot + 1);
    Max = unique(dc + 1, dc + tot + 1) - dc;
    for (reg int i = 1; i <= tot; ++ i) node[i].second = lower_bound(dc + 1, dc + Max, node[i].second) - dc + 1;

    // DP
    
    S.add(1, 1);
    for (reg int i = 1; i <= tot; ++ i)
    {
        if (node[i].first == node[i - 1].first && node[i].second == node[i - 1].second) continue;
        reg int t = S.ask(node[i].second - 1);
        S.add(node[i].second, t);
    }
    
    printf("%d\n", S.ask(Max));
    
    return 0;
}


---

## 作者：Soulist (赞：14)

直观感受是，考虑夹在 $[L,R]$ 两洞内部的点，显然在左边的点如果要从右边的洞出去，那么在其右边的其他点也必须从右边的洞出去。

正确描述出来是，满足 $[L<i<j<R]$ 的点对 $(i,j)$，如果 $i$ 从 R 出来，那么 $j$ 从 R 处出来。

我们发现这似乎意味着如果 $j$ 到 R 的距离比 $i$ 小，且 $j$ 到 L 的距离比 $i$ 大那么 $i$ 从 R 出来意味着 $j$ 从 R 出来。

用 $l_i,r_i$ 分别表示点 $i$ 到两边的距离，那么一个点可以被一个二元组 $(l_i,r_i)$ 描述。

注意到我们实际上只关注向左/向右走过的历史最远距离，所以每次操作可以看作是给历史最远距离$+1$（否则操作无效）然后如果满足当前 $(L,R)$ 有一个比 $(l_i,r_i)$ 大，那么这个点就会从那个方向的洞出去。

将所有二元组按照 $l_i$ 排序，然后令 0 表示这个点从 $l_i$ 出去，1 表示这个点从 $r_i$ 出去，我们发现我们实际上是要求有多少个 01 序列合法，而合法的唯一判定条件为：

- 若 $l_i\le l_j$，且 $r_i\ge r_j$，那么如果 $i$ 为 $1$ ，则 $j$ 为 $1$。另一面类似。

由于我们按照了 $l_i$ 进行排序，所以我们相当于消除了一个限制，对于 $l$ 相同的点我们按照 $r_i$ 进行排序，那么问题等价于如果 $i<j$ 且 $r_i>r_j$ 则若 $i$ 为 $1$ 则 $j$ 为 $1$，求合法的 01 序列数。

我们考虑把未被限制而自主选择了 1 的点拎出来，这样可以看作是选择一个原序列的子序列且其合法，而合法等价于 $r_i$ 单调递增。

所以对这个问题进行 dp 就可以了，由于我比较菜，不会离散化，所以写了一个动态开点的线段树。

值得注意的是空序列也算一个合法的方案。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define int long long
#define ls(x) tr[x].l
#define rs(x) tr[x].r
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int P = 1e9 + 7 ; 
const int N = 2e5 + 5 ; 
int n, m, cnt, num, Rt, M, lef[N], ref[N], dp[N] ;
struct node { int p, f ; } a[N << 1] ;
struct Px { int x, y ; } c[N] ; 
bool cmp( node x, node y ) { return x.p < y.p ; }
bool cmp2( Px a, Px b ) { return ( a.x == b.x ) ? ( a.y > b.y ) : a.x < b.x ; }
struct Tr { int l, r, w ; } tr[N * 20] ;
void insert( int &x, int l, int r, int wh, int val ) {
	if( !x ) x = ++ num ; tr[x].w += val, tr[x].w %= P ; 
	if( l == r ) return ; 
	int mid = ( l + r ) >> 1 ; 
	if( mid >= wh ) insert( ls(x), l, mid, wh, val ) ;
	else insert( rs(x), mid + 1, r, wh, val ) ;
}
int query( int x, int l, int r, int wh ) {
	if( l == r ) return tr[x].w ; 
	int mid = ( l + r ) >> 1 ; 
	if( mid >= wh ) return query( ls(x), l, mid, wh ) ;
	else return ( query( rs(x), mid + 1, r, wh ) + tr[ls(x)].w ) % P ; 
}
signed main()
{
	n = gi(), m = gi() ; int maxn = 0 ;
	rep( i, 1, n ) a[i].p = gi(), maxn = max( maxn, a[i].p ), a[i].f = 1 ; 
	rep( i, 1, m ) a[i + n].p = gi(), maxn = max( maxn, a[i + n].p ) ; 
	M = n + m, ++ maxn ; 
	sort( a + 1, a + M + 1, cmp ) ;
	rep( i, 1, M ) lef[i] = ( a[i].f ) ? lef[i - 1] : a[i].p ; 
	drep( i, 1, M ) ref[i] = ( a[i].f ) ? ref[i + 1] : a[i].p ; 
	rep( i, 1, M ) {
		if( (!lef[i]) || (!ref[i]) || (!a[i].f) ) continue ; 
		++ cnt, c[cnt].x = a[i].p - lef[i], c[cnt].y = ref[i] - a[i].p ; 
	}
	sort( c + 1, c + cnt + 1, cmp2 ) ; int Ans = 1 ; 
	rep( i, 1, cnt ) {	
		if( c[i].x == c[i - 1].x && c[i].y == c[i - 1].y ) continue ; 
		dp[i] = 1 + query( 1, 1, maxn, c[i].y + 1 ) ;
		insert( Rt, 1, maxn, c[i].y + 2, dp[i] ) ;
		Ans = ( Ans + dp[i] ) % P ; 
	}
	cout << Ans << endl ; 
	return 0 ;
}
```

---

## 作者：xht (赞：5)

> [ARC101F Robots and Exits](https://atcoder.jp/contests/arc101/tasks/arc101_d)

## 题意

- 数轴上有 $n$ 个 A 类点 $A_i$，$m$ 个 B 类点 $B_j$，任意两点的坐标都是整数且互不相同。
- 每次操作可以让所有 A 类点同时向左或者向右移动一个单位。
- 如果在某个时刻 $A_i$ 与 $B_j$ 重合，则将 $a_i$ 赋值为 $j$，同时 $A_i$ 立刻消失。
- 当所有 A 类点都消失时不再操作，求此时序列 $a$ 的方案数。
- $n,m \le 10^5$，答案对 $10^9+7$ 取模。

## 题解

首先把最左边的 B 类点左边的 A 类点去掉，最右边的 B 类点右边的 A 类点去掉，这些点完全不影响答案。

对于剩下的 A 类点，设 $A_i$ 与其左边最近的 B 类点的距离为 $x_i$，与其右边最近的 B 类点的距离为 $y_i$，将 $(x_i,y_i)$ 放到平面直角坐标系中。

可以发现题目要求的方案数等于从原点开始画一条单调递增的曲线将这些点划分成两个集合的方案数（不妨设这条曲线不过任何一个点）。这是因为对于每一条曲线，若其先到达 $x_i$ 则意味着 $A_i$ 与左边的 B 类点重合，否则先到达 $y_i$ 则意味着 $A_i$ 与右边的 B 类点重合。

接下来就是计数了，显然考虑 DP。要做到不重不漏，考虑将曲线的每一段拉直，使曲线在任意一个横坐标上的位置尽可能往下。这样曲线变成了若干段折线，且每个从往上改变方向为往右的位置都是某个点所在的位置。

考虑 DP 这个点，设 $f_i$ 表示在点 $i$ 从往上改变方向为往右时的方案数，有转移 $f_{i} = 1 + \sum_{x_j < x_i,y_j < y_i} f_j$，显然可以树状数组优化。

最终的答案为 $1 + \sum f_i$，总时间复杂度 $\mathcal O(n \log n)$。

## 代码

```cpp
const int N = 1e5 + 7;
int n, m, a[N], b[N], x[N], y[N], X[N], Y[N], p[N], t;
struct BIT {
	vector<modint> c;
	inline BIT() {}
	inline BIT(int n) { c.resize(n); }
	inline void add(ui x, modint k) {
		while (x < c.size()) c[x] += k, x += x & -x;
	}
	inline modint ask(ui x) {
		modint k = 0;
		while (x) k += c[x], x -= x & -x;
		return k;
	}
};

int main() {
	rd(n), rd(m), rda(a, n), rda(b, m);
	for (int i = 1; i <= n; i++) {
		if (a[i] < b[1] || a[i] > b[m]) continue;
		int p = upper_bound(b + 1, b + m + 1, a[i]) - b;
		x[++t] = a[i] - b[p-1], y[t] = b[p] - a[i], ::p[t] = t;
		X[t] = x[t], Y[t] = y[t];
	}
	sort(X + 1, X + t + 1), sort(Y + 1, Y + t + 1);
	int u = unique(X + 1, X + t + 1) - X - 1;
	int v = unique(Y + 1, Y + t + 1) - Y - 1;
	for (int i = 1; i <= t; i++)
		x[i] = lower_bound(X + 1, X + u + 1, x[i]) - X,
		y[i] = lower_bound(Y + 1, Y + v + 1, y[i]) - Y;
	sort(p + 1, p + t + 1, [&](int i, int j) {
		return x[i] == x[j] ? y[i] > y[j] : x[i] < x[j];
	});
	t = unique(p + 1, p + t + 1, [&](int i, int j) {
		return x[i] == x[j] && y[i] == y[j];
	}) - p - 1;
	BIT c(v + 1);
	modint ans = 1, now;
	for (int i = 1; i <= t; i++)
		ans += now = c.ask(y[p[i]] - 1) + 1, c.add(y[p[i]], now);
	print(ans);
	return 0;
}
```

---

## 作者：lzk5627 (赞：4)

对于这题,我们首先发现对于一个机器人来说,他能够访问的位置肯定只有左右两个出口(如果左边或右边没有出口可以直接删掉),那么我们就可以对于每个点预处理出来一个 $l_i$ 和 $r_i$ 表示到左边/右边的出口距离是多少

接着我们考虑一下限制条件,发现如果有一个 $i$ ,如果存在 $j$ 满足 $l_i \le  l_j$ 且 $r_i>r_j$ 那么 $j$ 选择左边时, $i$ 也要必须选择左边

发现对于这个限制我们可以抽象成一个网格图,每个点的左边为 $(l_i,r_i)$ ,每次从 $(0,0)$ 开始选择向上或向右走,一个点的选择可以看做最先碰到 $y=l_i$ 还是 $x=r_i$ ,我们发现这样转换问题是可以满足上面的限制的

先把横纵坐标离散化,我们可以考虑用 $dp$ 来求方案数,设 $f_{i,j}$ 表示当前到了 $(i,j)$ 的方案数,然后我们根据前面的限制可以发现,一个点可以由前面 $r_j\le r_i$ 的地方转移过来,用树状数组维护即可
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int P=1e9+7;
int n,m,cnt,num,a[N],b[N],d[N],f[N];
struct each{
	int l,r;
	bool operator == (each k){
		return l==k.l&&r==k.r;
	}
}c[N];
bool com(each x,each y){
	if(x.l==y.l)	return x.r>y.r;
	return x.l<y.l;
}
void add(int x,int y){
	while(x<=num){
		f[x]=(f[x]+y)%P;
		x+=x&-x;
	}
}
int query(int x){
	int ans=0;
	while(x){
		ans=(ans+f[x])%P;
		x-=x&-x;
	}
	return ans;
}
int main(){
	freopen("1.out","w",stdout);
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)	scanf("%d",&b[i]);
	sort(a+1,a+n+1),sort(b+1,b+m+1);
	n=unique(a+1,a+n+1)-a-1;
	m=unique(b+1,b+m+1)-b-1;
	for(int i=1;i<=n;i++){
		if(a[i]<b[1]||a[i]>b[m])	continue;
		int k=lower_bound(b+1,b+m+1,a[i])-b;
		if(b[k]==a[i])	continue;
		c[++cnt].l=a[i]-b[k-1];
		d[cnt]=c[cnt].r=b[k]-a[i];
	}
	d[cnt+1]=0;
	sort(d+1,d+cnt+2);
	sort(c+1,c+cnt+1,com);
	num=unique(d+1,d+cnt+2)-d-1;
	add(1,1);
	for(int i=1;i<=n;i++){
		if(c[i]==c[i-1])	continue;
		int k=lower_bound(d+1,d+num+1,c[i].r)-d;
		add(k,query(k-1));
	}
	printf("%d\n",query(num));
	return 0;
}

```

---

## 作者：Terac (赞：2)

把最左边的洞左边的人和最右边的洞最右边的人去掉，可以用二元组 $(l,r)$ 描述每个人，表示它左边的洞和右边的洞距离分别为 $l,r$，那么 $(l,r)$ 相同的两人显然是等价的。

我们用 $1$ 表示进了右边的洞，$0$ 表示进了左边的洞。对于 $(l_1,r_1),(l_2,r_2)$ 满足 $l_1\le l_2,r_1\ge r_2$，若 $(l_1,r_1)$ 为 $1$ 则 $(l_2,r_2)$ 必为 $1$，$0$ 的情况同理。

把 $(l,r)$ 在平面上表示出来，那么 $(l,r)$ 选 $1$ 即一个 $x\ge l, y\le r$ 的矩形内全部是 $1$，选 $0$ 即一个 $x\le l, y\ge r$ 的矩形内全部是 $0$。

考虑把选 $1$ 的矩形全部拿出来，会构成一个阶梯状物，阶梯对应的折线，折线上的折点满足 $r$ 严格单调递增。而这条折线唯一对应一个阶梯，也即一个合法的 $01$ 序列。

于是我们只需统计将二元组序列按 $l$ 排序后，有多少个单调递增子序列即可。

---

## 作者：xxr___ (赞：1)

首先，一个机器人只会掉到其最靠近的两个洞里面。我们记其左边的洞和右边的洞分别为 $(l_i,r_i)$。

进一步的，我们发现，我们只关心某个方向上历史上最远走过的距离，左右分别为 $(x,y)$。那么如果满足 $x > l_i$ 或者 $y > r_i$ 就会掉到相应的洞里面，当前前提条件是另一个方向掉不到洞里面。

注意到这个特殊的计数方式，是需要满足至少一个球，其掉到洞中不同，并不是我们操作的方案数，所以我们只关心一次操作后那些影响历史最左或者最右的即可，不然操作了无意义，不会影响计数。

所以，我们把 $(l_i,r_i)$ 都放到数轴上，每次对历史有影响的操作就是让 $(x,y)→(x,y + 1)$ 或者 $(x,y) → (x + 1,y)$ 也就是向右或者向上移动一步。此时，每个 $(l_i,r_i)$ 可以看做两条 $x = l_i$ 和 $y = r_i$ 的直线，某个位置的球是向左掉还是向右掉，就是 $(x,y)$ 的轨迹先碰到哪条关于 $i$ 的哪条直线。

并且：如果存在这样的两个二元组 $i,j$ 满足：
1. $l_i < l_j$
2. $r_i \ge r_j$

那么这个时候，如果想让 $i$ 掉到右边，$j$ 也肯定会掉到右边，我们称种二元组为一对限制。

同理，若满足相反的条件，也称作一对限制。

所以，我们就相当于求出有多少 $01$ 序列，如果第 $i$ 位是 $0$ 则满足向左边，反之则相反。一对限制就相当于限制两个位置的值必须相同，这样就有了一种 $\mathcal O(n^2)$ 的解法。

但是这种解法并没有用到我们的坐标系，我们发现，求出序列满足限制相当于求出哪些没有存在互相限制条件的序列！

根据上面提到的两种约束，我们易归纳出没有限制的序列是满足 $i<j,l_i < l_j,r_i < r_j$ 的，所以我们可以按照 $l$ 排序，然后从前往后按照 $r$ 转移。

设 $f_i$ 表示前 $i$ 个没有相互限制的球的掉落方案数，有 $f_i = \sum_{j < i,l_j < l_i,r_j < r_i} f_j$ 初始 $f_i = 1$ 最后答案就是 $(\sum f_i) + 1$ 因为可以是空串。

这样，我们就有了一种 $\mathcal O(n^2)$ 的做法，并且，优化到 $\mathcal O(n\log n)$ 是容易的，由于 $l$ 一维有序，我们只需要二维偏序，动态单点修改，查前缀和即可，由于 $V \leq 10^9$ 所以应该使用动态开点线段树实现。

细节：排序的时候，如果 $l$ 相同则按照 $r$ 从大到小排，这样能防止 $l$ 相同的时候互相贡献。

代码：
```cpp
#include<iostream>
#include<algorithm> 

#define int long long
const int N = 1e5 + 5;
const int mod = 1e9 + 7;

int rt = 0,n,a[N],b[N],m,tot = 0,f[N],sum[N << 5],ls[N << 5],rs[N << 5];

struct node{
	int x,y;
}t[N];

inline void ins(int &u,int l,int r,int x,int k){
	if(!u) u = ++ tot;
	if(l == r){
		(sum[u] += k) %= mod;
		return;
	}
	int mid = (l + r) >> 1;
	(x <= mid ? ins(ls[u],l,mid,x,k) : ins(rs[u],mid + 1,r,x,k));
	sum[u] = (sum[ls[u]] + sum[rs[u]]) % mod;
}
inline int query(int u,int l,int r,int ql,int qr){
	if(ql <= l && qr >= r){
		return sum[u] % mod;
	}
	int mid = (l + r) >> 1,s = 0;
	if(ql <= mid) (s += query(ls[u],l,mid,ql,qr)) %= mod;
	if(qr > mid) (s += query(rs[u],mid + 1,r,ql,qr)) %= mod;
	return s;
}
int32_t main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cin >> n >> m;
	for(int i = 1;i <= n; ++ i){
		std::cin >> a[i];
	}
	for(int i = 1;i <= m; ++ i){
		std::cin >> b[i];
	}
	int cnt = 0;
	for(int i = 1;i <= n; ++ i){
		if(a[i] < b[1] || a[i] > b[m]) continue;
		int pos = std::lower_bound(b + 1,b + m + 1,a[i]) - b;
		t[++ cnt] = {a[i] - b[pos - 1],b[pos] - a[i]};
	}
	std::sort(t + 1,t + cnt + 1,[&](const node & l,const node & r){
		if(l.x == r.x) return l.y > r.y;
		return l.x < r.x;
	});
	cnt = std::unique(t + 1,t + cnt + 1,[&](const node & l,const node & r){
		return l.x == r.x && l.y == r.y;
	}) - t - 1;
	int ans = 0;
	for(int i = 1;i <= cnt; ++ i){
		f[i] = (1 + query(rt,0,1e9,0,t[i].y - 1)) % mod;
		ins(rt,0,1e9,t[i].y,f[i]);
	}
	for(int i = 1;i <= n; ++ i){
		(ans += f[i]) %= mod;
	}
	std::cout << (++ ans) % mod;
	return 0;
}
```

---

## 作者：TTpandaS (赞：1)

对于每个机器人，他肯定只会在距离他最近的左右两个出口离开。而向哪边离开则取决于两边的到达过的最远距离哪个先相等。

具体的，设第 $i$ 个机器人距离最靠近他的左边出口距离为 $l_i$，右边为 $r_i$。我们只关心两边走的最远距离，设为 $x_i$ 和 $y_i$。每一次有效操作即将 $x_i+1$ 或 $y_i+1$。那么如果 $x_i=l_i$ 先发生，即从左出口离开。反之从右出口离开。

我们只需要考虑哪些机器人从右边离开，其余都从左边离开。

我们先将机器人按照 $l_i$ 排序，那么从左边离开的机器人都会按照现在的相对顺序离开。

考虑如果第 $j$ 个机器人比第 $i$ 个先从右边离开，那么一定满足 $r_j<r_i$。

设 $f_i$ 表示第 $i$ 个机器人是最后一个从右边离开的方案数。那么枚举上一个从右边离开的机器人，将方案数累计即可。

而上一个能从右边离开的机器人 $j$ 一定满足 $r_j<r_i$，可以用树状数组优化。

---

## 作者：SunsetSamsara (赞：1)

## 题意

现在有 $n$ 个机器人和 $m$ 个出口在一个数轴上，每个机器人和出口都有一个正整数坐标，并且这 $n+m$ 个坐标都互不相同。

现在执行若干次操作，每次操作可以是：

1. 将所有机器人的坐标减一。
2. 将所有机器人的坐标加一。

当一个机器人移到出口的的时候就会消失，求有多少种所有机器人从出口出来的方案。

## 分析

发现每个机器人只会最多有两个不同的出口可以选择。先把只有一种选择的机器人删除，因为这不影响答案。

对于一个有两个出口方案的机器人，令它到左边出口的距离为 $a$ ，到右边出口的距离为 $b$。那么每个机器人可以看成一个点 $(a, b)$。

令 $x$ 为所有机器人往左移动最远时移动的距离， $y$ 为所有机器人往右移动最远时移动的距离，那么每次操作相当于把 $(x,y)$ 变成 $(x+1,y)$ 或者 $(x,y+1)$。

因为当 $x=a_i$ 时，机器人 $i$ 会走左边出口，而当 $y=b_i$ 时，机器人 $i$ 会走右边出口。所以可以把问题这样转化：从原点开始移动，每次可以往上或者往右走，看先与 $x = a_i$ 和 $y = b_i$ 的哪一条直线先相交。

这时候考虑 `dp`。设 $f_i$ 表示折线最后经过的点是 $i$ 的方案数，那么就有转移式 

$$f_i=1+\sum\limits_{x_j<x_i,y_j<y_i}f_j$$

使用树状数组优化 `dp`，时间复杂度 $\Theta(n\log n)$。

## 代码

```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define lld long long
using namespace std;
inline int min(const int &x, const int &y) { return x < y ? x : y; }
inline int max(const int &x, const int &y) { return x > y ? x : y; }
const int N = 100010;
const int mod = 1e9 + 7;
int n, m;
int cnt, tot;
int a[N], b[N], d[N];
struct node { int l, r; } c[N];
inline bool operator == (const node &x, const node &y) {
	return x.l == y.l && x.r == y.r;
}
inline bool operator < (const node &x, const node &y) {
	return (x.l == y.l) ? (x.r > y.r) : (x.l < y.l);
}
int C[N];
inline void modify(int p, int x) {
	for (; p <= tot; p += p & -p)
		C[p] = (C[p] + x) % mod;
}
inline int query(int p) {
	int ret = 0;
	for (; p; p &= p - 1)
		ret = (ret + C[p]) % mod;
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) scanf("%d", a + i);
	for (int i = 1; i <= m; ++ i) scanf("%d", b + i);
	sort(a + 1, a + n + 1), sort(b + 1, b + m + 1);
	n = unique(a + 1, a + n + 1) - a - 1;
	m = unique(b + 1, b + m + 1) - b - 1;
	for (int i = 1; i <= n; ++ i) {
		if (a[i] < b[1] || a[i] > b[m]) continue;
		int k = lower_bound(b + 1, b + m + 1, a[i]) - b;
		if (b[k] == a[i]) continue;
		c[++ cnt] = (node){a[i] - b[k - 1], b[k] - a[i]};
		d[cnt] = b[k] - a[i];
	}
	d[cnt + 1] = 0;
	sort(c + 1, c + cnt + 1);
	sort(d + 1, d + cnt + 2);
	tot = unique(d + 1, d + cnt + 2) - d - 1;
	modify(1, 1);
	for (int i = 1; i <= n; ++ i) {
		if (c[i] == c[i - 1]) continue;
		int k = lower_bound(d + 1, d + tot + 1, c[i].r) - d;
		modify(k, query(k - 1));
	}
	printf("%d\n", query(tot));
}

```

---

## 作者：Acoipp (赞：1)

题意很好理解，这里就不说了。

## 分析

对于每个机器人，它的左右边至少有一个出口，最多有两个出口，因此我们分类讨论。

- 如果左右边一共只有一个出口，那它只能走那个出口。
- 否则可以走两个出口中的任意一个。

不难发现，排除了第一种情况后，剩下一些机器人可以走两个出口，但是这些机器人之间还有一定的限制，例如 A 去了它左边的出口，B 就不能去它右边的出口等。

所以为了方便分析问题，我们设某个机器人距到左边的出口距离为 $x$，到右边的出口距离为 $y$。 

如果存在另外的机器人到左边出口距离为 $x'$，到右边出口距离为 $y'$，那么这两个机器人之间必须满足：

- 如果第一个机器人往左边出口走，第二个机器人如果满足 $x \ge x',y \le y'$ 则也必须往左边出口走。
- 如果第一个机器人往右边出口走，第二个机器人如果满足 $x \le x',y \ge y'$ 则也必须往右边出口走。

手推一下，可以发现除了这两条限制，其他机器人的左右出口是可以随意选择的。

我们把这些点在平面直角坐标系中画出来，就会发现任意一种合法状态都是形如下面这种样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/e8l4mfg1.png)

（红色的点是往右边出口走，蓝色的点是往左边出口走）

即存在一条折线，折线上的点的 $x,y$ 都不下降，且折线下方的点都往右边走，折线上方的点都往左边走。

这样的话就转化成了一个二维偏序的模板题了，只需要把点的坐标找出来，然后用树状数组维护即可。

时间复杂度：$O(n \log n)$；空间复杂度：$O(n)$。

## 代码

代码比较好写，只有一个树状数组。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mod 1000000007
#define N 100005
using namespace std;
struct node{ll x,y;}p[N];
ll n,m,a[N],b[N],i,j,k,l,tot,qzh[N],ttt,tr[N];
bool cmp(node a,node b){
	if(a.x==b.x) return a.y<b.y;
	return a.x<b.x;
}
void add(ll k,ll x){while(k<=ttt) tr[k]+=x,k+=k&(-k),tr[k]%=mod;}
ll query(ll k){
	ll num = 0;
	while(k) num+=tr[k],k-=k&(-k),num%=mod;
	return num;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(i=1;i<=n;i++) cin>>a[i];
	for(i=1;i<=m;i++) cin>>b[i];
	sort(a+1,a+n+1),sort(b+1,b+m+1);
	for(i=1;i<m;i++){
		j = lower_bound(a+1,a+n+1,b[i])-a;
		k = lower_bound(a+1,a+n+1,b[i+1])-a-1;
		for(l=j;l<=k;l++) p[++tot]=(node){a[l]-b[i],b[i+1]-a[l]};
	}
	sort(p+1,p+tot+1,cmp);
	qzh[++ttt] = 0;
	for(i=1;i<=tot;i++) qzh[++ttt] = p[i].y;
	sort(qzh+1,qzh+ttt+1),ttt=unique(qzh+1,qzh+ttt+1)-qzh-1;
	for(i=1;i<=tot;i++) p[i].y=lower_bound(qzh+1,qzh+ttt+1,p[i].y)-qzh;
	add(1,1);
	for(i=1;i<=tot;i=j){
		for(j=i;j<=tot;j++) if(p[i].x!=p[j].x) break;
		for(k=j-1;k>=i;k=l){
			l=k;
			while(l>=i&&p[l].y==p[k].y) l--;
			add(p[k].y,query(p[k].y-1));
		}
	}
	cout<<query(ttt)<<endl;
	return 0;
} 
/*
Input:
2 2
2 3
1 4

Output:
3
*/
```

---

## 作者：cike_bilibili (赞：0)

# 思路

**贪心地想**，我们把每一个点向左向右的距离记为 $(x_i,y_i)$，我们发现对于两个点 $(x_i,y_i),(x_j,y_j)$，如果 $x_i \ge x_j,y_i \le y_j$，此时 $i$ 向左，$j$ 一定向左，向右则相反。**有二元组与偏序关系时考虑放在坐标系上**，我们选出一个严格上升子序列，上半部分都向右，下半部分都向左，问题转化成了上升子序列计数。

注意相同的点只算一个。

# Code


```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
inline int read(){
    int ans=0,w=1;
    char ch=getchar();
    while(ch<48||ch>57){
       if(ch=='-')w=-1;
       ch=getchar();
    }
    while(ch>=48&&ch<=57){
       ans=(ans<<1)+(ans<<3)+ch-48;
       ch=getchar();
    }
    return w*ans;
}
const int V=1000000000;
const int mod=1000000007;
int n,m;
int a[100005],b[100005];
struct node{
    int x,y;
    bool operator<(const node &a){
        if(x==a.x)return y>a.y;
        return x<a.x;
    }
}d[100005];
int top;
struct Binary_indexed_tree{//单点加区间查询
    unordered_map<int,int>tree;
    int lowbit(int i){return i&-i;}
    void add(int pos,int val){
        for(int i=pos;i<=V;i+=lowbit(i))tree[i]=(tree[i]+val)%mod;
    }
    int ask(int l,int r){
        int ans=0;
        for(int i=r;i;i-=lowbit(i))ans=(ans+tree[i])%mod;
        for(int i=l-1;i;i-=lowbit(i))ans=(ans+mod-tree[i])%mod;
        return ans;
    }
}T;
int f[100005];
signed main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=m;i++)b[i]=read();
    int now=1;
    for(int i=1;i<=n;i++){
        while(now<=m&&b[now]<a[i])++now;
        if(now==1||now>m)continue;
        d[++top]={a[i]-b[now-1],b[now]-a[i]};
    }
    sort(d+1,d+1+top);
    ll ans=1;
    for(int i=1;i<=top;i++){
        if(d[i].x==d[i-1].x&&d[i].y==d[i-1].y)continue;
        f[i]=T.ask(1,d[i].y-1)+1;
        T.add(d[i].y,f[i]);
        ans=(ans+f[i])%mod;
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：Enoch006 (赞：0)

对于每个机器人，我们找到其距离左右的出口的距离。若只有左/右出口则不需要管这个机器人。

按照离左出口的距离排序，这样显然以前左边移动的最大值不会超过自己，那么只需要记 $f_i$ 表示最大往右走了 $i$ 的方案数，为防止算重复，只在所有离右出口的距离处记答案。

假设现在机器人到右出口距离为 $r$，考虑分讨贡献：

- $i<r$，机器人只能去左出口，方案数不变。
- $i=r$，这时机器人即可以去左出口又可以去右出口。
  - 去左出口，此时 $f_r=f_r$，方案数不变。
  - 去右出口，此时 $f_r=\sum_{i<r}+f_r$，相当于一个推平，把以前 $i<r$ 的 $f_i$ 全部累加到 $f_r$ 上。
- $i>r$，机器人只能去右出口，方案数不变。

因此，方程的转移仅为 $f_r=\sum_{i\le r}f_i$，直接用树状数组维护即可。

初始化是把 $f_0$ 设为 $1$ 表示不动的方案数。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define maxm 500005
#define mod 1000000007
using namespace std;
int T,n,m,ans,cnt,N;
int a[maxm],b[maxm];
struct node{
	int l,r;
}d[maxm];
bool cmp(node x,node y){
	if(x.l==y.l)return x.r>y.r; 
	return x.l<y.l;
}
int c[maxm];
int t[maxm];
void add(int x,int y){
	x=lower_bound(c+1,c+N+1,x)-c;
	for(;x<=N;x+=x&-x)t[x]=(t[x]+y)%mod;
}
int ask(int x){
	x=lower_bound(c+1,c+N+1,x)-c;
	int sum=0;
	for(;x;x-=x&-x)sum=(sum+t[x])%mod;
	return sum;
}
signed main(){
//	freopen("1_30.txt","r",stdin);
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=m;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		int x=b[i];
		if(x<=a[1]||x>=a[m])continue;
		int p=lower_bound(a+1,a+m+1,x)-a;
		if(a[p]==x)continue;
//		cerr<<p<<" "<<a[p-1]<<" "<<a[p]<<" "<<x<<"\n";
		d[++cnt]=(node){x-a[p-1],a[p]-x};
		c[++N]=a[p]-x;c[++N]=a[p]-x-1;
	} 
	sort(d+1,d+cnt+1,cmp); 
	c[++N]=0;c[++N]=1000000000;
	sort(c+1,c+N+1); 
	N=unique(c+1,c+N+1)-c-1;
	add(0,1);
	for(int i=1;i<=cnt;i++){
//		cerr<<d[i].l<<" "<<d[i].r<<"\n";
		if(d[i].l==d[i-1].l&&d[i].r==d[i-1].r)continue;
		int sum=ask(d[i].r-1);
		add(d[i].r,sum);
	}
	cout<<ask(1000000000);
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

AT 评分没上 3000，看起来是不怎么难的题。但是为啥我的题解写的这么复杂？

考虑每个机器人，离左边最近的洞的距离为 $x$，离右边最近的洞的距离为 $y$。

考虑第一次移动，使得有机器人掉下去——发现一定是所有 $x$ 最小的机器人掉进了左边的洞口，或者 $y$ 最小的机器人掉进了右边的洞口。

把 $(x,y)$ 描到平面直角坐标系里方便思考。

发现，我们每次可以把**最下边或者最左边的所有点染上相同颜色（颜色取决于染色方向）**，求不同颜色序列的总数。下文设红色是横向染的颜色，蓝色是纵向染的颜色。

考虑所有染成蓝色的点，必定形成一个“阶梯形”，如下图所示：

![](https://s21.ax1x.com/2025/01/08/pECu00A.png)

考虑每一列蓝色点中最靠下的——他们按照列从左到右的顺序依次被染色，所以纵坐标是递增的。

如果若干个蓝色点的纵坐标是相同的，显然只需要关注最右边那一个。因此我们需要求坐标系中两个维度都严格递增的折线个数。

边界情况是容易处理的：建虚拟点 $(N,N)$，如果一个位置左边或右边没有洞，就设距离是 $N+1$。

树状数组加速 DP，复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10,MOD=1e9+7,INF=2e9;
int n,N,M,p[MAXN],q[MAXN],x[MAXN],y[MAXN],tot;
set<int> rx[MAXN];
int tr[MAXN];
void update(int pos,int v) {
	while(pos<=tot) tr[pos]=(tr[pos]+v)%MOD,pos+=pos&-pos;
	return ;	
}
int query(int pos) {
	int ans=0;
	while(pos) ans=(ans+tr[pos])%MOD,pos-=pos&-pos;
	return ans;	
}
int pre[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>N>>M;
	ffor(i,1,N) cin>>p[i];
	ffor(i,1,M) cin>>q[i];
	vector<pair<int,int>> P;
	P.push_back({0,0}),P.push_back({INF,INF}),P.push_back({INF+1,INF});
	ffor(i,1,N) {
		int id=lower_bound(q+1,q+M+1,p[i])-q,xv=0,yv=0;
		if(id<=M) yv=q[id]-p[i];
		else yv=INF+2;
		if(id>1) xv=p[i]-q[id-1];
		else xv=INF+2;
		P.push_back({xv,yv});
	}
	
	sort(P.begin(),P.end()),P.erase(unique(P.begin(),P.end()),P.end());
	for(auto id:P) y[++n]=id.second;
	sort(y+1,y+n+1),n=unique(y+1,y+n+1)-y-1;
	for(auto id:P) x[++tot]=id.first;
	tot=unique(x+1,x+tot+1)-x-1;
	for(auto id:P) rx[lower_bound(y+1,y+n+1,id.second)-y].insert(-(lower_bound(x+1,x+tot+1,id.first)-x));	
	
	update(1,1);
	int id=lower_bound(y+1,y+n+1,INF)-y;
	ffor(i,2,id-1) for(auto j:rx[i]) {
		int v=query(-j-1);
		update(-j,v);	
	}
	cout<<(query(tot-1)%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：zhangboju (赞：0)

绝妙题

我们把机器人视为球，把出口视为洞

首先去掉在洞两边的球和一开始就在洞里的球，注意到无论怎么移动都会使它们进入确定的洞

现在考虑中间的每个球，它们一定会进到左边第一个或右边第一个洞内，对于第 $i$ 个球，令左边第一个洞距离其 $A_i$，右边第一个洞距离其 $B_i$ 

我们发现，由于并不关心每个球具体的移动过程，而只关心这个球最终进入哪个洞，我们并不需要考虑具体的移动过程，只需要考虑其当前最左走了多少，最右走了多少

我们只分析改变了这两个值的操作

发现每个球，只要它当前没有掉下去，那么对于这所有球，它们的这两个值都是一样的

将这样的一个二维的东西放到平面上，考虑一个点 $(x,y)$ 表示最左走了 $x$，最右走了 $y$

那么我们只分析改变这两个值的操作，相当于使 $x+1$ 或使 $y+1$

即在平面上的一条折线

发现这条折线若先碰到 $x=A_i$，则 $i$ 从左侧出，否则先碰到 $y=B_i$ 从右侧出

由于我们只关心每个点从哪出，所以并不关系折线具体怎么走

考虑令 $f_i$ 表示最后出的点是 $i$ 时的方案数

有 $f_i=1+\sum \limits_{A_j<A_i,B_j<B_i} f_j$

树状数组优化二维偏序即可

注意由于坐标值域 $10^9$，需要离散化

复杂度 $O(n\log n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T> inline void read(T &x)
{
	x=0;short f=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x*=f;return;
}
const int N=1e6+5,mod=1e9+7;
int a[N],b[N];
int n,m;
int c[N];
using PII=pair<int,int>;
int lowbit(int x){return x&(-x);}
void add(int x,int v){for(int i=x;i<=n;i+=lowbit(i)) c[i]=(c[i]+v)%mod;}
int query(int x)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res=(res+c[i])%mod;
	return res;
}
vector<PII>p;
int main()
{
	read(n);read(m);
	for(int i=1;i<=n;++i) read(a[i]);
	for(int i=1;i<=m;++i) read(b[i]);
	vector<int>ve;
	for(int i=1;i<=n;++i)
	{
		if(a[i]<=b[1]||a[i]>=b[m]) continue;
		int pos=lower_bound(b+1,b+m+1,a[i])-b;
		if(a[i]==b[pos]) continue;
		p.push_back({a[i]-b[pos-1],b[pos]-a[i]});
		ve.push_back(b[pos]-a[i]);
	}
	sort(ve.begin(),ve.end());
	ve.erase(unique(ve.begin(),ve.end()),ve.end());
	for(int i=0;i<p.size();++i) p[i].second=lower_bound(ve.begin(),ve.end(),p[i].second)-ve.begin()+1;
	sort(p.begin(),p.end(),[&](PII a,PII b){return (a.first!=b.first)?(a.first<b.first):(a.second>b.second);});
	p.erase(unique(p.begin(),p.end()),p.end());
	int ans=0;
	for(int i=0;i<p.size();++i) 
	{
		int x=query(p[i].second-1)+1;
		add(p[i].second,x);
		ans=(ans+x)%mod;
	}
	printf("%d\n",ans+1);
}
```

---

## 作者：Rubyonly (赞：0)

容易发现，这 $m$ 个出口会把 $n$ 个机器人分成若干段

对于某一段的这些机器人，要么从左边最近的出口消失，要么从右边最近的出口消失，从而我们可以得到每个机器人到左边的距离 $x$，到右边的距离 $y$，形成了若干个这样的点对 $(x,y)$

我们考虑两个机器人 $(x_0,y_0),(x_1,y_1)$，如果 $x_0<x_1$，那么只要机器人 $1$ 从左边消失了，那么机器人 $0$ 也一定是从左边消失的

把这些点对放到坐标系上，问题其实就是每次将 $x$ 轴往上移，或者将 $y$ 轴往右移，先被 $x$ 轴覆盖掉的为白色，先被 $y$ 轴覆盖掉的为黑色

我们可以将覆盖掉的点按顺序转化成一条路径，路径上的点满足 $x_{i-1}<x_i\wedge y_{i-1}<y_i$，我们要求的就是不同的路径条数

具体操作时，先将左边和右边只有可能消失在一个出口的机器人去掉，然后求出剩下每个机器人的 $(x,y)$，按照 $x_i$ 排序，因为是严格小于，所以 $x_i$ 相同的按照 $y_i$ 从大到小排序

最后做一遍最长上升子序列即可，用树状数组优化一下可以做到 $\mathcal O({n\log n})$ 的复杂度

$\mathcal{Code:}$

```c++
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 50, INF = 0x3f3f3f3f, mod = 1e9 + 7;

inline int read () {
	register int x = 0, w = 1;
	register char ch = getchar ();
	for (; ch < '0' || ch > '9'; ch = getchar ()) if (ch == '-') w = -1;
	for (; ch >= '0' && ch <= '9'; ch = getchar ()) x = x * 10 + ch - '0';
	return x * w;
}

inline int addmod (register int a, register int b) {
	return a += b, a >= mod ? a - mod : a;
}

int n, m, num, ans, lenx, leny, x[maxn], y[maxn], bx[maxn], by[maxn], tree[maxn];

struct Node {
	int x, y;
	inline friend bool operator < (register const Node &a, register const Node &b) { return a.x == b.x ? a.y > b.y : a.x < b.x; }
} a[maxn];

inline void Insert (register int x, register int val) {
	for (; x <= leny; x += x & -x) tree[x] = addmod (tree[x], val);
}

inline int Query (register int x, register int ans = 0) {
	for (; x; x -= x & -x) ans = addmod (ans, tree[x]);
	return ans;
}

int main () {
	n = read(), m = read();
	for (register int i = 1; i <= n; i ++) x[i] = read();
	for (register int i = 1; i <= m; i ++) y[i] = read();
	for (register int i = 1, res; i <= n; i ++) {
		res = upper_bound (y + 1, y + m + 1, x[i]) - y;
		if (res - 1 >= 1 && res <= m) num ++, a[num].x = bx[++ lenx] = x[i] - y[res - 1], a[num].y = by[++ leny] = y[res] - x[i];
	}
	sort (bx + 1, bx + lenx + 1), lenx = unique (bx + 1, bx + lenx + 1) - bx - 1;
	sort (by + 1, by + leny + 1), leny = unique (by + 1, by + leny + 1) - by - 1;
	for (register int i = 1; i <= num; i ++)
		a[i].x = lower_bound (bx + 1, bx + lenx + 1, a[i].x) - bx, a[i].y = lower_bound (by + 1, by + leny + 1, a[i].y) - by;
	sort (a + 1, a + num + 1);
	for (register int i = 1, res; i <= num; i ++) {
		if (a[i].x == a[i - 1].x && a[i].y == a[i - 1].y) continue;
		res = Query (a[i].y) + 1, Insert (a[i].y + 1, res), ans = addmod (ans, res);
	}
	return printf ("%d\n", addmod (ans, 1)), 0;
}
```

---

## 作者：BYR_KKK (赞：0)

模拟赛唯唯诺诺，vp arc 重拳出击。

显然每个机器人只能有两个可能走出去的出口。令 $0$ 代表从左边出去，$1$ 代表从右边出去，考虑什么样的一个 $01$ 序列是合法的。

令 $l_i$ 为到第 $i$ 个机器人到左边最近出口的距离，$r_i$ 为到右边最近出口的距离。显然将一个点移动到出口以后移动回初始状态和合法性无关。那么每次就相当于选择一个机器人将它送出去，这个机器人能被送出去的充要条件是 $l_i$ 是当前所有没被送出去的的机器人中最小的，或者 $r_i$ 是当前所有没被送出去的机器人中最小的。

套路地，在坐标系上考虑这个问题，将每个点看作 $(l_i,r_i)$。将从右边出去的点染色，进一步考虑什么样的染色方式是合法的。观察得到如果存在 $(l_i,r_i)$ 染色同时 $(l_j,r_j)$ 没被染色，且 $l_i\le l_j$ 和 $r_i\ge r_j$ 成立则染色方案不合法，否则一定合法，证明是容易的。

这是一个三维偏序的形式，不过好像没有什么用。考虑怎么更好地刻画这个偏序。令 $R(x)=\{i|l_x\le l_i\cup r_x\ge r_i\}$，那么实际上就是选出一些点 $a_1,a_2,\dots,a_k$，使得 $\cup_{i=1}^kR(i)$ 被染色。为了避免重复，必须有 $\forall i,j,R(i)\notin R(j)$。观察到就是要求 $a$ 是一个在二维平面上的严格上升子序列，同时观察到不同的上升子序列带来的贡献是不同的。

所以对严格上升子序列计数即可。这是简单的，考虑根据 $l_i$ 排序后按照 $r_i$ 倒序加入一个新的序列，，求新序列的严格上升子序列数量即可，时间复杂度 $O(n\log n)$。

注意将相同坐标的点去重。对于左/右边不存在出口的点直接删去即可。

---

