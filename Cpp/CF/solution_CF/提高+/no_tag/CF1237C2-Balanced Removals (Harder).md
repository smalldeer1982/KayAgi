# Balanced Removals (Harder)

## 题目描述

This is a harder version of the problem. In this version, $ n \le 50\,000 $ .

There are $ n $ distinct points in three-dimensional space numbered from $ 1 $ to $ n $ . The $ i $ -th point has coordinates $ (x_i, y_i, z_i) $ . The number of points $ n $ is even.

You'd like to remove all $ n $ points using a sequence of $ \frac{n}{2} $ snaps. In one snap, you can remove any two points $ a $ and $ b $ that have not been removed yet and form a perfectly balanced pair. A pair of points $ a $ and $ b $ is perfectly balanced if no other point $ c $ (that has not been removed yet) lies within the axis-aligned minimum bounding box of points $ a $ and $ b $ .

Formally, point $ c $ lies within the axis-aligned minimum bounding box of points $ a $ and $ b $ if and only if $ \min(x_a, x_b) \le x_c \le \max(x_a, x_b) $ , $ \min(y_a, y_b) \le y_c \le \max(y_a, y_b) $ , and $ \min(z_a, z_b) \le z_c \le \max(z_a, z_b) $ . Note that the bounding box might be degenerate.

Find a way to remove all points in $ \frac{n}{2} $ snaps.

## 说明/提示

In the first example, here is what points and their corresponding bounding boxes look like (drawn in two dimensions for simplicity, as all points lie on $ z = 0 $ plane). Note that order of removing matters: for example, points $ 5 $ and $ 1 $ don't form a perfectly balanced pair initially, but they do after point $ 3 $ is removed.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237C2/7ad611aa18ed85b1538cfecdeefb390344c16862.png)

## 样例 #1

### 输入

```
6
3 1 0
0 3 0
2 2 0
1 0 0
1 3 0
0 1 0
```

### 输出

```
3 6
5 1
2 4
```

## 样例 #2

### 输入

```
8
0 1 1
1 0 1
1 1 0
1 1 1
2 2 2
3 2 2
2 3 2
2 2 3
```

### 输出

```
4 5
1 6
2 7
3 8
```

# 题解

## 作者：Nemlit (赞：7)

这么妙的题怎么没人发题解啊

首先这是三维的，~~我们可以对其进行降维打击~~

先考虑一维怎么做？

我们可以对其该维坐标进行排序，按照顺序输出，可能会多余一个

那拓展到二维呢？

我们可以把它转化成一维，分成很多个一维后执行上述操作，把一维中多的一些点存下来，可以保证这些点的一维值两两不等，于是按照另一维坐标输出就行了

那三维呢？

其实和二维是一样的，用类似操作转化成二维即可

## $Code:$
```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
il int read() {
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define rep(i, s, t) for(re int i = s; i <= t; ++ i)
#define maxn 100005
struct node {
	int x, y, z, id;
}e[maxn], p[maxn], q[maxn], a[maxn], b[maxn];
//e用来存储三维坐标，p用来存储第三维相等时的二维坐标，q用来存储第二三维都相等的一维坐标
//a用来存储二维操作中剩余点的坐标，b则是用来存储三位操作中剩余点的坐标
int n, c2D, c3D;
il bool cmp(node a, node b) { return a.z < b.z; }
il bool cmp1(node a, node b) { return a.y < b.y; }
il bool cmp2(node a, node b) {return a.x < b.x; }
il void solve1D(int x) {
	sort(q + 1, q + x + 1, cmp2);
	for(re int i = 1; i < x; i += 2) printf("%d %d\n", q[i].id, q[i + 1].id);
	if(x & 1) a[++ c2D] = q[x];
}
il void solve2D(int x) {
	sort(p + 1, p + x + 1, cmp1);
	int now = 1, cnt = 0; c2D = 0;
	rep(i, 1, x) {
		now = i;
		while(now <= x && p[i].y == p[now].y) q[++ cnt] = p[now ++];
		i = now - 1, solve1D(cnt), cnt = 0;
	}
	for(re int i = 1; i < c2D; i += 2) printf("%d %d\n", a[i].id, a[i + 1].id);
	if(c2D & 1) b[++ c3D] = a[c2D];
}
il void solve3D() {
	sort(e + 1, e + n + 1, cmp);
	int now = 1, cnt = 0;
	rep(i, 1, n) {
		now = i;
		while(now <= n && e[i].z == e[now].z) p[++ cnt] = e[now ++];
		i = now - 1, solve2D(cnt), cnt = 0;
	}
	for(re int i = 1; i < c3D; i += 2) printf("%d %d\n", b[i].id, b[i + 1].id);
}
int main() {
	n = read();
	rep(i, 1, n) e[i].id = i, e[i].x = read(), e[i].y = read(), e[i].z = read();
	solve3D();
	return 0;
}


```

---

## 作者：heaksicn (赞：3)

## 1 题意
三维平面有 $n$ 个点，$n$ 为偶数。

现在要求取 $\frac{n}{2}$ 次，每次去一对点 $(a,b)$，要求没有未被取走的点在以 $x$ 和 $y$ 为对角点的矩形中。

求任意一组合法方案。

## 2 思路
从低维到高维考虑。
### 2.1 一维
我们可以根据每个点的 $x$ 坐标进行排序，然后成对删除它们。最后最多剩下 $1$ 个点。
### 2.2 二维
对于每个 $y$，找出所有与他 $y$ 坐标相同的点，对此进行与一维相似的操作。

操作完成后，每个 $y$ 上最多有一个点。

在将 $y$ 进行排序，进行一次一维操作即可。
### 2.3 三维
同理，对于每个 $z$，找到所有具有这个 $z$ 坐标的点，并求解其二维形式。

完成此操作后，每个 $z$ 坐标最多剩下一个点。

再对 $z$ 进行一维操作即可。

根据这个方法，我们可以将问题推广到 $k$ 维。

时间复杂度 $O(kn\log n)$。
## 3 code
```
#include<bits/stdc++.h>
using namespace std;
int n;
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
     if(x<0) putchar('-'),x=-x;
     if(x>9) write(x/10);
     putchar(x%10+'0');
}
struct node{
	int x,y,z;
	int id;
}a[50001];
bool cmp(node a,node b){
	if(a.x==b.x){
		if(a.y==b.y){
			return a.z<b.z;
		}
		return a.y<b.y;
	}
	return a.x<b.x;
}
int f[50001];
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i].x=read(),a[i].y=read(),a[i].z=read();
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<n;i++){
		if(f[i]==0){
			int now=i+1;
			if(a[i].x==a[now].x&&a[i].y==a[now].y){
				cout<<a[i].id<<" "<<a[now].id<<"\n";
				f[i]=1;
				f[now]=1;
			}
		}
	}
	for(int i=1;i<n;i++){
		if(f[i]==0){
			int now=i+1;
			while(a[i].x==a[now].x&&f[now]!=0) now++;
			if(a[i].x==a[now].x){
				cout<<a[i].id<<" "<<a[now].id<<"\n";
				f[i]=1;
				f[now]=1;
			}
		}
	}
	for(int i=1;i<n;i++){
		if(f[i]==0){
			int now=i+1;
			while(f[now]!=0) now++;
			cout<<a[i].id<<" "<<a[now].id<<"\n";
			f[i]=1;
			f[now]=1;
		}
	}
	return 0;
}
```




---

## 作者：Flying2018 (赞：3)

提供一种比较方便的做法。

首先显然有一个结论：对于点 $i$，我们找到其向右($x_j\geq x_i$)距离它最近的点集，再找到其中向上($y_j\geq y_i$)最近的点集，再找到其中向右($z_j\geq z_i$)最近的点 $j$。

这样得到的 $(i,j)$ 显然是符合条件的。

那么怎么找到这样的点集呢？我们可以用 $\text{map}$ 套 $\text{map}$ 来实现。

具体来说，我们用 `
map<int,map<int,map<int,int> > >q;` 第一维 $q[x_0]$ 存所有 $x$ 坐标等于 $x_0$ 的点。第二、三维同理。

这样删除的时候只要特判一下，把不存在的维度一起删掉即可。

这样在第一维 `lower_bound` 得到的就是向右($x_j\geq x_i$)距离它最近的点集，第二、三维同理。

特别的，如果不存在 $x_j\geq x_i$ 的点，那我们只要找向左($x_j\leq x_i$)距离它最近的点集即可。其余维度同理。

复杂度同样是 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<set>
#define N 100010
#define fi first
#define se second
using namespace std;
struct node{
    int x,y,z;
}p[N];
bool chs[N];
map<int,map<int,map<int,int> > >q;
void erase(node p)
{
    q[p.x][p.y].erase(p.z);
    if(q[p.x][p.y].empty()) q[p.x].erase(p.y);
    if(q[p.x].empty()) q.erase(p.x);
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].z),q[p[i].x][p[i].y][p[i].z]=i;
    for(int i=1;i<=n;i++)
    if(!chs[i])
    {
        erase(p[i]);
        auto x=q.lower_bound(p[i].x);
        if(x==q.end()) --x;
        auto y=x->se.lower_bound(p[i].y);
        if(y==x->se.end()) --y;
        auto z=y->se.lower_bound(p[i].z);
        if(z==y->se.end()) --z;
        int u=z->se;
        erase(p[u]);
        chs[u]=chs[i]=true;
        printf("%d %d\n",i,u);
    }
    return 0;
}
```

---

## 作者：Imakf (赞：1)

由于本菜菜太菜，（考后）写了一个伪KDT的代码

考虑分治做法，如果我们用一个平面把空间隔开，然后平面两侧的点都分开配对。

最后最多两边各自剩下一个点，而其他的都被消掉了，此时必然可以配对。

然后按照上述思路就一直分治就行了。

借鉴了KDT的思路，每次从 $x,y,z$ 三维找一个方差最小的，然后用中位数该维度上的值把对应的平面把点分成两部分。

但是我比较懒，我直接用的平均数分割。

而且这也不是正常的KDT，我这个KDT只有叶子节点保存真正的节点。

复杂度玄学

```cpp
#include<cstdio>
#include<queue>

#define rg register
#define il inline
#define MX (200000 + 5)

struct point{
	int pos[3] ,id;
}p[MX];

int cnt ,n;
int ch[MX][2] ,fa[MX] ,key[MX];
int build(point *A ,int Len){
	++cnt;
	if(Len == 1){	// 当前平面内只有一个点 
		key[cnt] = A[0].id;
		ch[cnt][0] = ch[cnt][1] = 0;
		return cnt;
	}
	double aver[3] = {0} ,del[3] = {0};
	// aver 是平均数 ,del 是方差*Len
	for(rg int i = 0 ; i < Len ; ++i){
		for(rg int j = 0 ; j < 3 ; ++j)
			aver[j] += A[i].pos[j];
	}
	aver[0] /= Len ,aver[1] /= Len ,aver[2] /= Len;
	for(rg int i = 0 ; i < Len ; ++i){
		for(rg int j = 0 ; j < 3 ; ++j)
			del[j] += (A[i].pos[j] - aver[j])
				* (A[i].pos[j] - aver[j]);
	}
	int type = 0;	// type = 0 ,1 ,2 分别表示从 x ,y ,z 三种平面切开 
	if(del[0] >= del[1] && del[0] >= del[2])	type = 0;
	else if(del[1] >= del[0] && del[1] >= del[2])	type = 1;
	else type = 2;
	aver[type] += 0.00002;	// 为了保证这平面不能碰到点 
	std::queue<point> que[2];	// 存平面两侧的点的 
	for(rg int i = 0 ; i < Len ; ++i){
		// 分割我是用的平均数，有点懒 QAQ 
		que[A[i].pos[type] > aver[type]].push(A[i]);
	}
	int sz = que[0].size();
	for(rg int i = 0 ; i < Len ; ++i){
		A[i] = que[i >= sz].front();
		que[i >= sz].pop();
	}
	int _now = cnt;
	ch[_now][0] = build(A ,sz);
	ch[_now][1] = build(A + sz ,Len - sz);
	return _now;
}

int solve(int x){
	if(!x)	return 0;
	if(!ch[x][0] && !ch[x][1])	return key[x];
	int a = solve(ch[x][0]) ,b = solve(ch[x][1]);
	if(a && b)	return printf("%d %d \n" ,a ,b) ,0;
	if(a)	return a;
	return b;
}

int main(){
	n = read();
	for(rg int i = 1 ,x ,y ,z ; i <= n ; ++i){
		x = read(); y = read(); z = read();
		p[i] = (point){{x ,y ,z} ,i};
	}
	solve(build(p + 1 ,n));
	return 0;
}

```

---

## 作者：401rk8 (赞：0)

这篇题解咕了好久。。。

dalao们都用了神仙做法，发一个最好写的。

先考虑一维怎么做？排序后相邻两个配对

但题中有三维，非常烦，考虑降维。  
发现 $z$ 这一维之所以存在是因为存在 $x,y$ 相同而 $z$ 不同的点，于是想到先把 $x,y$ 相同的点当作只有 $z$ 这一维处理，然后就可以忽略 $z$ 这一维。同理，二维也可以降到一维。

利用好 `sort` 的 `cmp` 函数，可以只排一次序，且三段代码只需要改下 `x y z`，非常好写。

```cpp
const int N = 5e4+5;
int n;
struct Node {
	int x,y,z,id;
} a[N];
bool operator < (const Node &i,const Node &j)
	{ return i.x==j.x ? (i.y==j.y ? i.z<j.z : i.y<j.y) : i.x<j.x; }
 
bool vis[N];
 
int main() {
	read(n);
	For(i,1,n) read(a[i].x,a[i].y,a[i].z), a[i].id = i;
	sort(a+1,a+n+1);
	for(int i = 1; i < n; ++i) if( !vis[i] ) {
		if( a[i].x == a[i+1].x && a[i].y == a[i+1].y ) {
			printf("%d %d\n",a[i].id,a[i+1].id);
			vis[i] = vis[i+1] = 1;
		}
	}
	for(int i = 1; i < n; ++i) if( !vis[i] ) {
		int j = i+1;
		while( a[i].x == a[j].x && vis[j] ) ++j;
		if( a[i].x == a[j].x ) {
			printf("%d %d\n",a[i].id,a[j].id);
			vis[i] = vis[j] = 1;
		}
	}
	for(int i = 1; i < n; ++i) if( !vis[i] ) {
		int j = i+1;
		while( vis[j] ) ++j;
		printf("%d %d\n",a[i].id,a[j].id);
		vis[i] = vis[j] = 1;
	}
	return 0;
}
```

---

顺便宣传一下 [D的题解](https://www.luogu.com.cn/blog/Rings/cf1237d-balanced-playlist#)

---

