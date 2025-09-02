# [ABC181F] Silver Woods

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc181/tasks/abc181_f

$ xy $ 平面上に $ 2 $ 直線 $ y=-100,\ y=100 $ で囲まれた通路があります。

この通路の中の $ -100\ <\ x\ <\ 100 $ の部分に $ N $ 本の大きさの無視できる釘が打たれており、 $ i $ 本目の釘の座標は $ (x_i,\ y_i) $ です。

高橋くんは実数 $ r\ (0\ <\ r\ \leq\ 100) $ を $ 1 $ つ選び、半径 $ r $ の円を中心が $ (-10^9,\ 0) $ に位置するように置きます。

その後、円を $ (-10^9,\ 0) $ から $ (10^9,\ 0) $ まで移動させます。

このとき、円は通路の境界や釘が円の内部に入らないような範囲で連続的に動かすことができるものとします。

円を $ (10^9,\ 0) $ まで動かせるような最大の $ r $ を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数
- $ 1\ \leq\ N\ \leq\ 100 $
- $ |x_i|,\ |y_i|\ <\ 100 $
- $ i\ \neq\ j $ ならば $ (x_i,\ y_i)\ \neq\ (x_j,\ y_j) $

### Sample Explanation 1

!\[\](https://img.atcoder.jp/ghi/493d8b75d6dd331fcc0f3949f12262b3.jpg) $ r=40 $ の円を図のように $ y=0 $ に沿って動かすと、 $ (-10^9,\ 0) $ から $ (10^9,\ 0) $ まで移動させることができます。 $ x=0 $ のときにちょうど $ 2 $ つの点と接しますが、円の内部には入っていないため問題ありません。 $ r $ を $ 40 $ より大きくすると、円の中心を $ (10^9,\ 0) $ まで動かすことができなくなるため、 $ r=40 $ が最大になります。

## 样例 #1

### 输入

```
2
0 -40
0 40```

### 输出

```
40```

## 样例 #2

### 输入

```
4
0 -10
99 10
0 91
99 -91```

### 输出

```
50.5```

## 样例 #3

### 输入

```
10
-90 40
20 -30
0 -90
10 -70
80 70
-90 30
-20 -80
10 90
50 30
60 -70```

### 输出

```
33.541019662496845446```

## 样例 #4

### 输入

```
10
65 -90
-34 -2
62 99
42 -13
47 -84
84 87
16 -78
56 35
90 8
90 19```

### 输出

```
35.003571246374276203```

# 题解

## 作者：ikunTLE (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc181_f)

### 思路

可以使用**并查集**和**二分**解决此题。

首先发现答案具有单调性，这是因为大的圈一定能包含小的圈。于是可以二分圈的半径 $r$，难点在于二分的判断函数。

只要满足 $2\times r\le\operatorname{dis}(X,Y)$，则半径为 $r$ 的圆可以穿过 $X$ 点和 $Y$ 点。不难想到可以将所有的点全部连接起来。做两层循环的枚举，若 $i$ 点和 $j$ 点满足要求，就将它们连通起来。可以使用**并查集**进行处理。

然后处理上下边界，将能到达上下边界的点与 $L$ 和 $R$ 相连（$L$ 和 $R$ 为自定义的上下边界的点），最后判断 $L$ 和 $R$ 是否连通即可。

**注意事项**

- 为了控制精度，$2\times r\le\operatorname{dis}(X,Y)$ 可以转化为 $4\times r^2\le\operatorname{dis}(X,Y)^2$。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=100+10,L=101,R=102;
const double EPS=1e-13;
int n,x[N],y[N],fa[N];
void _init(){
	for(int i=0;i<N;++i)
		fa[i]=i;
	return;
}
int _find(int x){
	if(x==fa[x])
		return x;
	fa[x]=_find(fa[x]);
	return fa[x];
}
void _merge(int x,int y){
	int xx=_find(x),yy=_find(y);
	if(xx!=yy)
		fa[xx]=yy;
	return;
}
#define y1 y_1
int calc(int x1,int x2,int y1,int y2){
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
bool check(double r){
	_init();
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j)
			if(4*r*r>calc(x[i],x[j],y[i],y[j]))
				_merge(i,j);
		if(100-y[i]<=2*r)
			_merge(i,L);
		if(y[i]+100<=2*r)
			_merge(i,R);
	}
	return _find(L)!=_find(R);
}
int main(){
	n=read();
	for(int i=1;i<=n;++i)
		x[i]=read(),y[i]=read();
	double l=0,r=100;
	while(abs(l-r)>=EPS){
		double mid=(l+r)/2;
		if(check(mid))
			l=mid;
		else r=mid;
	}
	printf("%.12lf\n",r);
	return 0;
}
```

---

## 作者：Rnfmabj (赞：5)

## ABC181F

*2009

### 题意

给你一个平面，上界是直线 $y=100$ 下界是直线 $y=-100$。

在平面上 $n$ 个钉子，钉子不能在圆内。

一个圆从 $x=-\infty$ 开始向右运动，问最大的半径使圆能够到达 $x=\infty$。

 $n,|x|,|y| \le 100$ ，精度误差允许 $10^{-4}$。

### 题解

看到最大化与合法化，考虑二分。

容易发现钉子可以拦住直径为 $d$ 的圆，当且仅当可以用若干条长度不大于 $d$ 的线段从上界途径钉子连接到下界。

这样一来当圆试图经过这条线时，无论如何都会被其中的一条线段拦住。

用并查集维护这个过程。对于每个点 $(x,y)$ ，我们额外添加点 $(x,100)$ 与 $(x,-100)$，用来连接边界。

设当前圆的直径为 $d$ ，我们只需要连接所有距离不大于 $d$ 的点，连接完成后检查上下界是否被连接即可。

时间复杂度 $O(n^2\log v · \alpha(n))$，其中 $v$ 为二分精度需求。

### 代码

```cpp
const ll maxn=105;
ll fa[maxn<<2];//空间开大，因为要额外加两倍的点
const db eps=1e-9;
ll cmp(db x,db y){
	if(x-y>eps)return 2;
	if(y-x>eps)return 1;
	return 0;
}//规避精度误差
struct node{
	ll x,y;
}a[maxn<<2];
ll tot;
db calc(node u,node v){
	return 1.0*(sqrt(1.0*(u.x-v.x)*(u.x-v.x)+1.0*(u.y-v.y)*(u.y-v.y)));
}//计算距离
ll find(ll x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(ll u,ll v){u=find(u),v=find(v);if(u==v)return ;fa[u]=v;}
bool check(db lim){
	for(ll i=1;i<=tot;i++)fa[i]=i;
	for(ll i=1;i<=tot;i++){
		for(ll j=1;j<=tot;j++){
			if(i==j)continue;
			if(cmp(calc(a[i],a[j]),lim)==2)continue;
			merge(i,j);
		}
	}//合并
	for(ll i=1;i<=tot;i++){
		if(a[i].y!=100&&a[i].y!=-100)continue;
		for(ll j=i+1;j<=tot;j++){
			if(a[i].y+a[j].y)continue;
			if(find(i)==find(j))return 0;
		}
	}//检查
	return 1;
}
ll n;
void solve(){
	n=R;
	for(ll i=1;i<=n;i++){
		ll x=R,y=R;
		a[++tot].x=x;
		a[tot].y=y;
		a[++tot].x=x;
		a[tot].y=100;
		a[++tot].x=x;
		a[tot].y=-100;
	}
	db l=0.0,r=200.0;
	while(cmp(l,r)){
		db mid=(l+r)/2.0;
		if(check(mid))l=mid;
		else r=mid;
	}
	//注意我们二分的是直径，所以输出半径要除以 2
	printf("%.8lf\n",l/2.0);//AT中文版的题面中没有注明精度要求，实际上是 1e-4
	//所以这里的保留精度（和上文的eps）都相对取得比较小
	return ;
}
```



---

## 作者：dengchengyu (赞：2)

### abc181_f  Silver Woods Solution

考虑到答案具有单调性，于是二分答案。

考虑一个半径为 $r$ 的圆能从 $(x_A,y_A),(x_B,y_B)$ 之间经过，要满足 $2r\le \sqrt {(x_A-x_B)^2+(y_A-y_B)^2}$。

那么我们就想如果不满足，就说明半径为 $r$ 的圆心不能跨过线段 $AB$。

我们把不能跨过的点连起来，同时连上上边界和下边界。
此时 $r$ 可行当且仅当上边界和下边界不连通，可以用并查集处理连通块。

时间复杂度 $O(n^2 \alpha(n)\log V)$。

AC 代码：

```cpp
const int N=105;
int fa[N];
int getfa(int x){
	if(fa[x]==x)return x;
	return fa[x]=getfa(fa[x]);
}
int X[N],Y[N];
int n;
int check(ld r){
	fo(i,1,n+2)fa[i]=i;
	fo(i,1,n){
		fo(j,i+1,n){
			if(4*r*r>(X[i]-X[j])*(X[i]-X[j])+(Y[i]-Y[j])*(Y[i]-Y[j])){
				int u=getfa(i),v=getfa(j);
				if(u!=v)fa[u]=v;
			}
		}
		if(2*r>100-Y[i]){
			int u=getfa(n+1),v=getfa(i);
			if(u!=v)fa[u]=v;
		}
		if(2*r>Y[i]+100){
			int u=getfa(n+2),v=getfa(i);
			if(u!=v)fa[u]=v;
		}
	}
	return getfa(n+1)!=getfa(n+2);
}
signed main(){
	cin>>n;
	fo(i,1,n)cin>>X[i]>>Y[i];
	ld L=0,R=100;
	ld ans=0;
	while(L<=R){
		ld mid=(L+R)/2;
		if(check(mid))ans=mid,L=mid+1e-11;
		else R=mid-1e-11;
	}
	printf("%.10Lf",ans);
	return 0;
}
```

---

## 作者：ForgetOIDuck (赞：1)

### 思路：
首先考虑判断一个半径 $r$ 是否合法的方法：若在**某条必经之路**上两点之间间隔的距离都小于 $2r$，说明过不去即不合法。

对于这条必经之路，我们不能枚举球的运动路线，因为实在是太多了；但是我们可以枚举一条**连接顶部和底部直线的折线，这条折线内相邻两个点的距离都小于 $2r$**。

由连通性想到并查集，自然想到把每个距离小于 $2r$ 的点对所在并查集合并，到最后查询两条直线是否在同一并查集。

由于半径的合法性具有单调性，可以使用二分确认 $r$。

时间复杂度 $O(n^2\log n)$。

### AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-7;
int n, x[1002], y[1002], fa[1002];
double d(int i, int j) {
	//cout << i << ' ' << j << ":" << sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])) << endl;
	return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
}
int fd(int x) {
	return fa[x] == x ? x : (fa[x] = fd(fa[x]));
}
bool check(double r) {
	for (int i = 1; i <= 3 * n; i ++ ) fa[i] = i;
	for (int i = 1; i < 3 * n; i ++ ) for (int j = i + 1; j <= 3 * n; j ++ ) if (d(i, j) < 2 * r) fa[fd(i)] = fd(j);
	for (int i = n + 1; i <= 2 * n; i ++ ) for (int j = 2 * n + 1; j <= 3 * n; j ++ ) if (fd(i) == fd(j)) return 1;
	return 0;
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i ++ ) cin >> x[i] >> y[i], x[i + n] = x[i + 2 * n] = x[i], y[i + n] = 100, y[i + 2 * n] = -100;
	
	double l = 0, r = 200;
	while (r - l >= eps) {
		double mid = (l + r) / 2.0;
		//cout << l << ' ' << r << ' ' << mid << endl;
		if (check(mid)) r = mid;
		else l = mid;
	}
	cout << l;
}
```

---

## 作者：Badnuker (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc181_f)

## AC证明

![](https://cdn.luogu.com.cn/upload/image_hosting/1za4ep0b.png)

## 思路

询问最大的半径，我们很容易想到二分答案。

设圆的直径为 $d$，将钉子视为点，若两点间距离小于 $d$ 则认为两点联通，可以用并查集维护。

将上下边界转化为点，若上下边界联通，则圆无法通过。

## 注意事项

1. 对于每一个点，我们都应在上下界各有一个点与之 $x$ 坐标相同，如下所示：

~~~cpp
    for (int i = 1; i <= n; i++) {
		cin >> a[i].x >> a[i].y;
		a[n + i] = {a[i].x, -100};
		a[2 * n + i] = {a[i].x, 100};
	}
~~~

2. 注意精度（误差不超过 $10^{-4}$）。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005;//要加点
const double eps = 1e-5;

int n;

struct node {
	double x, y;
} a[maxn];

double ans;
double d[maxn][maxn];

//并查集部分

int fa[maxn];

int find(int x) {
	if (x == fa[x]) {
		return x;
	}
	return fa[x] = find(fa[x]);
}

void join(int x, int y) {
	if (find(x) != find(y)) {
		fa[find(x)] = find(y);
	}
}

//二分 check

int ck(double mid) {
	for (int i = 1; i <= 3 * n; i++) {
		fa[i] = i;
	}
	for (int i = 1; i <= 3 * n; i++) {
		for (int j = 1; j <= 3 * n; j++) {
			if (i == j) {
				continue;
			}
			if (d[i][j] - mid < eps) {
				join(i, j);
			}
		}
	}
	for (int i = n + 1; i <= 2 * n; i++) {//枚举下边界的点
		for (int j = 2 * n + 1; j <= 3 * n; j++) {//枚举上边界的点
			if (find(i) == find(j)) {
				return 0;
			}
		}
	}
	return 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	memset(d, 0x7f, sizeof(d));//不能用0x3f
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].x >> a[i].y;
		a[n + i] = {a[i].x, -100};
		a[2 * n + i] = {a[i].x, 100};
	}
	for (int i = 1; i <= 3 * n; i++) {
		for (int j = 1; j <= 3 * n; j++) {
			d[i][j] = d[j][i] = sqrt((a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y));
		}
	}
	double l = 0, r = 200;
	while (r - l > eps) {
		double mid = (r + l) / 2;
		if (ck(mid)) {
			l = mid;
			ans = mid / 2;
		} else {
			r = mid;
		}
	}
	cout << fixed << setprecision(5) << ans;//保留5位小数输出
	return 0;
}

~~~


---

## 作者：Expert_Dream (赞：0)

首先看到这题就会想到考虑如何让这个圆走，然后图中计算一下最窄的空间，也就是答案了。但是发现了这个非常的繁琐。

然而，又发现如果一个大的圆可以通过，那么一个小的圆也肯定可以通过，这满足**单调性**，因此考虑二分。

接着之前的方向，已知这个圆的大小，看看能不能通过，还是发现比较麻烦。**正难则反**，不妨考虑怎么过不去。如果两个钉子之间的距离小于这个圆的直径，那么圆就无法从中通过。如果有一排钉子密密麻麻，挡住圆的去向，那么就是无法过的。如何考虑上下界？我们只需要在上面一排或者下面一排铺满钉子即可。如果由一排钉子拦住去路，实际上可以认为上界与下界连通。

因此并查集实现。

[link](https://atcoder.jp/contests/abc181/submissions/53980322)。

---

## 作者：Empty_Dream (赞：0)

## ABC181F 解题报告

### 分析

很容易想到二分答案，直接去二分这个半径（显然满足单调性）。

接下来是 check 部分，我们发现很难统计是否能走过去，那么正难则反，考虑什么情况走不过去，对于不能走过，分两点讨论：

- 点与点之间：$dis(i,j) < 2 \times r$。
- 点与边界之间：$100-y < 2 \times r$ 或 $y - (-100)<2\times r$。

什么情况下一定不能通过呢，显然是在某个点集中某些点与两个边界相连了，把整个通路挡住了。

不难想到并查集，如果满足上面条件就合并，对于边界特判一下，给边界编号为 $0$ 和 $n + 1$；最后判断是否能通过就等价于 $0$ 和 $n + 1$ 能否联通。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int x[105], y[105], fa[105];

int find(int x){
	return (x == fa[x] ? fa[x] : fa[x] = find(fa[x]));
}

void merge(int x, int y){
	fa[find(x)] = find(y);
}

double dis(double x0, double y0, double x2, double y2){
	return sqrt((x0 - x2) * (x0 - x2) + (y0 - y2) * (y0 - y2));
}

bool check(double mid){//并查集 check
	for (int i = 0; i <= n + 1; i++) fa[i] = i;
	for (int i = 1; i <= n; i++){
		if (100.0 - (double)y[i] < mid) merge(0, i);//与边之间能不能走过
		if ((double)y[i] + 100.0 < mid) merge(i, n + 1);
	}
	for (int i = 1; i <= n; i++){
		for (int j = i + 1; j <= n; j++){
			if (dis(x[i], y[i], x[j], y[j]) < mid) merge(i, j);//如果点之间不能走过
		}
	}
	return find(0) != find(n + 1);//判断是否在一起，如果在就不能通过
}

int main(int argc, char **argv){
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
	double l = 0, r = 200;
	while (r - l >= 1e-6){//二分半径
		double mid = (l + r) / 2;
		if (check(mid * 2)) l = mid;
		else r = mid;
	}
	printf("%.4lf", l);
	return 0;
}
```

---

## 作者：Lyccrius (赞：0)

合法答案最大化，考虑二分答案。

关于 `check`，记当前答案为 $r$，则 $d = 2r$，当 $dis(i, j) \lt d$ 时，不能从点 $i, j$ 间经过。

考虑什么情况下不能从 $(- \infty, 0)$ 移动到 $(\infty, 0)$，即满足上述条件的点对构成的连通块使得上界 $(x, 100)$ 与下界 $(x, -100)$ 连通。

注意上下界也应当看作钉子处理，比较距离时只考虑 $y$ 轴即可。

记 $w = maxR = 100$，时间复杂度 $\mathcal O(n^2 \log w \alpha(n))$。

```cpp
#include <iostream>

typedef double dbl;

const int maxN = 100;
const dbl eps = 1e-4;

int n;
dbl x[maxN + 10];
dbl y[maxN + 10];

struct DisjointSetUnion {
    struct Node {
        int fa;
    } node[maxN + 10];

    void Init() {
        for (int i = 0; i <= n + 1; i++) node[i].fa = i;
        return;
    }
    
    int Find(int u) {
        if (node[u].fa == u) return u;
        return node[u].fa = Find(node[u].fa);
    }

    void Union(int u, int v) {
        u = Find(u);
        v = Find(v);
        if (u == v) return;
        node[u].fa = v;
        return;
    }
} DSU;

dbl dis2(int i, int j) {
    dbl dx = std::abs(x[i] - x[j]);
    dbl dy = std::abs(y[i] - y[j]);
    return dx * dx + dy * dy;
}

bool check(dbl d) {
    DSU.Init();
    for (int i = 1; i <= n; i++) if (100 - y[i] < d) DSU.Union(n + 1, i);
    for (int i = 1; i <= n; i++) if (y[i] + 100 < d) DSU.Union(0, i);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (dis2(i, j) < d * d) {
                DSU.Union(i, j);
            }
        }
    }
    return DSU.Find(0) != DSU.Find(n + 1);
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> x[i] >> y[i];
    dbl l = 0;
    dbl r = 100;
    while (r - l > eps) {
        dbl mid = (l + r) / 2;
        if (check(mid * 2)) l = mid;
        else r = mid;
    }
    std::cout << l << '\n';
    return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

# abc181_f 解题报告

## 前言

比较经典的模型了。

评分高可能是因为当时不多见。

OI 在进步。

## 思路分析

首先答案具有单调性，考虑二分。

考虑怎样判断答案合不合法。

发现圆能够通过平面当且仅当上边界和下边界有一个长度超过圆的直径的空隙。

考虑在两个距离小于直径的钉子之间连边，则圆能通过当且仅当上边界和下边界不连通。

直径的最大值就是上边界和下边界恰好联通。

用并查集维护一下连通块就行了。

有一些关于边界怎么连边的细节，见代码。

这题放今天绝对没有 *2000。

## 代码实现

```cpp

#include<bits/stdc++.h>
using namespace std;
const double eps=1e-6;
int n,x[105],y[105];
int fa[105];
void init(){
	for(int i=0;i<=n+1;i++){
		fa[i]=i;
	}
}
int find(int x){
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x);
	y=find(y);
	if(x==y) return;
	fa[x]=y;
}
bool check(double a){
	init();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			if(abs(x[i]-x[j])*abs(x[i]-x[j])+abs(y[i]-y[j])*abs(y[i]-y[j])<=4*a*a){
				merge(i,j);
			}
		}
		if(abs(100-y[i])<=2*a) merge(0,i);
		if(abs(-100-y[i])<=2*a) merge(n+1,i);
	}
	return find(0)==find(n+1);
}
double find(double l,double r){
	if(fabs(l-r)<eps) return l;
	double mid=(l+r)/2;
	if(check(mid)) return find(l,mid-eps);
	else return find(mid+eps,r);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}
	printf("%.7lf",find(0,100));
	return 0;
}

```

## 后记

感觉这个模型见了很多次了。

---

