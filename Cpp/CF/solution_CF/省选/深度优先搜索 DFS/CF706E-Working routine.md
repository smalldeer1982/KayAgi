# Working routine

## 题目描述

Vasiliy finally got to work, where there is a huge amount of tasks waiting for him. Vasiliy is given a matrix consisting of $ n $ rows and $ m $ columns and $ q $ tasks. Each task is to swap two submatrices of the given matrix.

For each task Vasiliy knows six integers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ , $ d_{i} $ , $ h_{i} $ , $ w_{i} $ , where $ a_{i} $ is the index of the row where the top-left corner of the first rectangle is located, $ b_{i} $ is the index of its column, $ c_{i} $ is the index of the row of the top-left corner of the second rectangle, $ d_{i} $ is the index of its column, $ h_{i} $ is the height of the rectangle and $ w_{i} $ is its width.

It's guaranteed that two rectangles in one query do not overlap and do not touch, that is, no cell belongs to both rectangles, and no two cells belonging to different rectangles share a side. However, rectangles are allowed to share an angle.

Vasiliy wants to know how the matrix will look like after all tasks are performed.

## 样例 #1

### 输入

```
4 4 2
1 1 2 2
1 1 2 2
3 3 4 4
3 3 4 4
1 1 3 3 2 2
3 1 1 3 2 2
```

### 输出

```
4 4 3 3
4 4 3 3
2 2 1 1
2 2 1 1
```

## 样例 #2

### 输入

```
4 2 1
1 1
1 1
2 2
2 2
1 1 4 1 1 2
```

### 输出

```
2 2
1 1
2 2
1 1
```

# 题解

## 作者：小周猪猪 (赞：8)

## $\mathrm{Solution}$
一道非常神奇的题，这道题的解题关键就在于如何解决又换矩阵这一个问题。

一些废话：观察数据范围，我们发现可以用$O((n+m)q)$的复杂度解决问题。

考虑链的做法：怎么做矩阵的交换最方便呢，由于矩阵不想交，我们可以维护一个链表，即对$[l_1,r_1]$和$[l_2,r_2]$进行交换的话，需要将$r_1$和$r_2$的后继交换。

那么维护到矩阵上同理，我们可以维护一个十字链表，对于每一个节点记录右边的点和下面的节点，这样我们就可以可以做到快速交换了。

那么如何交换呢，这里我们需要在$O(n+m)$的时间内完成交换。
- 首先找到$(x_1,y_1)$的编号，再找到$(x_2,y_2)$的编号。
- 先向右$w$时，交换下指针；再向下$h$时，交换右指针。
- 先向下$h$时，交换右指针；再向右$w$时，交换下指针。

最后是输出，这个就很简单了，直接遍历链表即可。

## $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 1200;

int n, m, k;
struct List {
	int val, r, d;
} a[N * N];

int read(void)
{
	int s = 0, w = 0; char c = getchar();
	while (c < '0' || c > '9') w |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') s = s*10+c-48, c = getchar();
	return w ? -s : s;
}

inline int C(int x,int y) {
	return x * (m + 1) + y;
}

void change(void)
{
	int x1 = read(), y1 = read(), x2 = read(), y2 = read();
	int h = read(), w = read(), t1 = 0, t2 = 0;
	for (int i=1;i<x1;++i) t1 = a[t1].d;
	for (int i=1;i<y1;++i) t1 = a[t1].r;
	for (int i=1;i<x2;++i) t2 = a[t2].d;
	for (int i=1;i<y2;++i) t2 = a[t2].r;
	int p1 = t1, p2 = t2;
	for (int i=1;i<=w;++i) {
		p1 = a[p1].r, p2 = a[p2].r;
		swap(a[p1].d,a[p2].d);
	}
	for (int i=1;i<=h;++i) {
		p1 = a[p1].d, p2 = a[p2].d;
		swap(a[p1].r,a[p2].r);
	}
	p1 = t1, p2 = t2;
	for (int i=1;i<=h;++i) {
		p1 = a[p1].d, p2 = a[p2].d;
		swap(a[p1].r,a[p2].r);
	}
	for (int i=1;i<=w;++i) {
		p1 = a[p1].r, p2 = a[p2].r;
		swap(a[p1].d,a[p2].d);
	}
	return;
}

void output(void)
{
	int t = 0;
	for (int i=1;i<=n;++i)
	{
		t = a[t].d;
		int p = t;
		for (int i=1;i<=m;++i) {
			p = a[p].r;
			printf("%d ", a[p].val);
		}
		puts("");
	}
	return;
}

int main(void)
{
	n = read(), m = read(), k = read();
	for (int i=1;i<=n;++i)
	    for (int j=1;j<=m;++j)
	        a[C(i,j)].val = read();
	for (int i=0;i<=n;++i)
	    for (int j=0;j<=m;++j) {
	    	a[C(i,j)].r = C(i,j+1);
	    	a[C(i,j)].d = C(i+1,j);
		}
	while (k --) change();
	output();
	return 0;
}
```


---

## 作者：封禁用户 (赞：7)

# 0.前言
题目链接：[CF的链接，不是洛谷的](http://codeforces.com/contest/706/problem/E)

题目大意：$N\times M$ 的矩阵，共有 $q$ 个询问，每次输入 $a_i, b_i, c_i, d_i, h_i, w_i$，表示起点为 $(a,b)$ 和 $(c,d)$ 的两个大小为 $(w,h)$ 的矩阵进行交换；最后输出变换后矩阵。（两个子矩阵不重叠、没有相交的点）
 
#  1.解析
对于暴力的做法： $a[N][M]$ 来存矩阵，对每个点都交换一遍的话，复杂度应该是： $O(NMQ)$。
而 $N\times M\times Q=10^{10}$ ，这肯定不行。

那我们就走一步看一步：

看一行的情况：

假设这一行有8个数字：$1,2,...,8$ 。做法是交换 $[2,5]$ ，$[3,6]$ 。这是数组做法。

链表的做法：把 $1$ 的下一个指针和 $4$ 的下一个指针交换,$3$ 的下一个指针交换和 $6$ 的下一个指针交换即可。查找的时间是 $O(N)$ 。此时的复杂度为 $O(NQ)=10^7$ ，可以 AC。

具体就是用 stack 把要改的点记录下来。最后再一起改。
 
你以为这样就过了吗，当你高兴地拿着 ~~我的题解~~ 你的程序提交时，会TLE，哪里还要优化吗？当然可以，但是你还不如把 cin 换成 scanf 香。

# 2.code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define dl long long
int N = 1005,n,m,q,i,j,a,b,c,d,s,t;
struct dl{
    int v;
    dl *d,*r;
}e[N][N];

int main(){
    dl *x,*y,*u,*v;
    cin>>n>>m>>q;
    for(i=1;i<=n;++i)
        for(j=1;j<=m;++j) scanf("%d",&e[i][j].v);
    for(i=0;i<=n;++i)
        for(j=0;j<=m;++j) e[i][j].d= &e[i+1][j],e[i][j].r= &e[i][j+1];
    while(q--){
        x= y= &e[0][0];
        scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&s,&t);
        while(--a)x= x->d;
        while(--b)x= x->r;
        while(--c)y= y->d;
        while(--d)y= y->r;
        u = x,v= y;
        for(i=0;i<s;++i)
            u= u->d,v= v->d,
            swap(u->r,v->r);
        for(i=0;i<t;++i)
            x= x->r,y= y->r,
            swap(x->d,y->d);
        for(i=0;i<t;++i)
            u= u->r,v= v->r,
            swap(v->d,u->d);
        for(i=0;i<s;++i)
            x= x->d,y= y->d,
            swap(x->r,y->r);
    }
    x= &e[0][0];x= x->d;
    for(i=0;i<n;++i){
        y= x;
        for(j=0;j<m;++j) y= y->r,printf("%d ",y->v);
        putchar('\n');
        x= x->d;
    }
    return 0;
}
```
参考资料：程序员进阶练习。

---

## 作者：EricWan (赞：3)

~~一开始想歪了，好久才发现虽然矩阵大小很大但行数和列数都不大。~~

## 正解：
链表，本题 $n,m\le1000$，所以维护时只需要更改需要操作的子矩阵的外围一圈即可，时间复杂度为 $O(n\times m+q\times(n+m))$。

这里为了更美观，我把每个位置的上下左右的位置都进行了维护，具体操作请看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
int Eric, Wan, q, WJJAKIOI[1005][1005], a, b, c, d, h, w, /*输入数据（Eric=n，Wan=m，WJJAKIOI=v），看看谁作弊！*/
    ux[1005][1005], uy[1005][1005], dx[1005][1005], dy[1005][1005], lx[1005][1005], ly[1005][1005], rx[1005][1005], ry[1005][1005] /*伪指针*/;
pair<int,int> x, y, r, s, t, u, rl, rd, su, sr, tl, td, uu, ur; //临时变量们
pair<int,int> up(pair<int,int> x) {return {ux[x.first][x.second],uy[x.first][x.second]};}
pair<int,int> down(pair<int,int> x) {return {dx[x.first][x.second],dy[x.first][x.second]};}
pair<int,int> left(pair<int,int> x) {return {lx[x.first][x.second],ly[x.first][x.second]};}
pair<int,int> right(pair<int,int> x) {return {rx[x.first][x.second],ry[x.first][x.second]};}
string main(int IAKIOI) //Anti-coping code
{
	scanf("%d%d%d",&Eric,&Wan,&q);
	for (int i = 1; i <= Eric; i++)
		for (int j = 1; j <= Wan; j++)
			scanf("%d",&WJJAKIOI[i][j]);
	for (int i = 0; i <= Eric + 1; i++) {
		for (int j = 0; j <= Wan + 1; j++) {
			ux[i][j] = i - 1;
			uy[i][j] = j;
			dx[i][j] = i + 1;
			dy[i][j] = j;
			lx[i][j] = i;
			ly[i][j] = j - 1;
			rx[i][j] = i;
			ry[i][j] = j + 1;
		}
	}
	while (q--) {
		scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&h,&w);
		x = y = {0,0};
		for (int i = 1; i <= a; i++) //移动到现在的左上角
			x = down(x);
		for (int i = 1; i <= b; i++)
			x = right(x);
		for (int i = 1; i <= c; i++) //移动到现在的左上角
			y = down(y);
		for (int i = 1; i <= d; i++)
			y = right(y);
		r = s = x; t = u = y;
		for (int i = 1; i <= h; i++) { //更新左侧指针
			rl = left(r);
			tl = left(t);
			rx[rl.first][rl.second] = t.first;
			ry[rl.first][rl.second] = t.second;
			rx[tl.first][tl.second] = r.first;
			ry[tl.first][tl.second] = r.second;
			lx[r.first][r.second] = tl.first;
			ly[r.first][r.second] = tl.second;
			lx[t.first][t.second] = rl.first;
			ly[t.first][t.second] = rl.second;
			r = down(r);
			t = down(t);
		}
		r = up(r);
		t = up(t);
		for (int i = 1; i <= w; i++) { //更新下部指针
			rd = down(r);
			td = down(t);
			ux[rd.first][rd.second] = t.first;
			uy[rd.first][rd.second] = t.second;
			ux[td.first][td.second] = r.first;
			uy[td.first][td.second] = r.second;
			dx[r.first][r.second] = td.first;
			dy[r.first][r.second] = td.second;
			dx[t.first][t.second] = rd.first;
			dy[t.first][t.second] = rd.second;
			r = right(r);
			t = right(t);
		}
		r = left(r);
		t = left(t);
		for (int i = 1; i <= w; i++) { //更新上部指针
			su = up(s);
			uu = up(u);
			dx[su.first][su.second] = u.first;
			dy[su.first][su.second] = u.second;
			dx[uu.first][uu.second] = s.first;
			dy[uu.first][uu.second] = s.second;
			ux[s.first][s.second] = uu.first;
			uy[s.first][s.second] = uu.second;
			ux[u.first][u.second] = su.first;
			uy[u.first][u.second] = su.second;
			s = right(s);
			u = right(u);
		}
		s = left(s);
		u = left(u);
		for (int i = 1; i <= h; i++) { //更新右侧指针
			sr = right(s);
			ur = right(u);
			lx[sr.first][sr.second] = u.first;
			ly[sr.first][sr.second] = u.second;
			lx[ur.first][ur.second] = s.first;
			ly[ur.first][ur.second] = s.second;
			rx[s.first][s.second] = ur.first;
			ry[s.first][s.second] = ur.second;
			rx[u.first][u.second] = sr.first;
			ry[u.first][u.second] = sr.second;
			s = down(s);
			u = down(u);
		}
		s = up(s);
		u = up(u);
	}
	x = {0,0};
	x = right(x);
	for (int i = 1; i <= Eric; i++) {
		x = down(x);
		y = x;
		for (int j = 1; j <= Wan; j++) {
			printf("%d ",WJJAKIOI[y.first][y.second]);
			y = right(y);
		}
		printf("\n");
	}
	return 0;
}
```
常数较大，需要卡常。

↓ 既然看完了，点个赞呗。

---

## 作者：leozhang (赞：3)

这题不太好做

对数据结构会有一个更深入的了解

其实上来看到这题觉得应该是要差分，但后来由于太弱不会写...

最后发现要用链表搞（感谢网上其他题解）

链表不要求一定用指针，以下写法是非指针版的

而且也不一定要求二维，事实上一维的写法更简洁一些

首先我们来看，我们仅需修改一个矩阵四周的指针，就能够实现矩阵的交换。

（证明：由于一个矩阵在交换时只有连到这个矩阵的指针需要修改，矩阵内部指针不需修改，故仅需修改四边（矩阵外周）的节点指向，那么剩下的点就会按照边的指针跑过去，也就实现了交换）

那么按指针跳修改就可以了

有几个小细节要注意：

①.在映射的时候，正常我们会选择id=(x-1)·m+y，但在这道题中由于我们需要给四周的0节点留下位置，所以最好选择id=x·m+y之类的

②.在修改指针的时候，我们需要修改的是矩阵左侧边左侧一条边的右指针，矩阵上边上面一条边的下指针，矩阵右侧边的右指针和矩阵下面边的下指针（是不没看懂？没事，画个图就好）

如图所示，要修改的边被涂实了，要修改的指针用灰色标出了。

然后就好办了。

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#define ll long long
#define e 2005 
using namespace std;
struct node
{
	ll val;
	int dir[2];//0为右，1为下 
}A[e*e];
int n,m,q;
ll temp[e*e];
int getid(int x,int y)//二维向一维映射，注意留出一些空格给0指针使用 
{
	return x*m+y;
}
inline int read()
{
	int f=1,x=0;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void getst(int &p,int x,int y)
{
	for(int i=1;i<x;i++)
	{
		p=A[p].dir[1]; 
	}
	for(int i=1;i<y;i++)
	{
		p=A[p].dir[0];
	}
}
void change(int st1,int st2,int l,int w,int typ)
{
	for(int i=1;i<=l;i++) 
	{
		st1=A[st1].dir[typ];
		st2=A[st2].dir[typ];
		swap(A[st1].dir[1-typ],A[st2].dir[1-typ]);//①交换掉第一列向右的指针②交换掉第一行向下的指针 
	}
	typ=1-typ;
	for(int i=1;i<=w;i++) 
	{
		st1=A[st1].dir[typ];
		st2=A[st2].dir[typ];
		swap(A[st1].dir[1-typ],A[st2].dir[1-typ]);//①交换掉最下一行向下的指针②交换掉最右一列向右的指针 
	}
}
void getpoite()
{
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			A[getid(i,j)].dir[0]=getid(i,j+1);
			A[getid(i,j)].dir[1]=getid(i+1,j);
		}
	}
}
int main()
{
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			A[getid(i,j)].val=read();
		}
	}
	getpoite();
 	while(q--)
 	{
	 	int x1,y1,x2,y2,h,w,st1,st2;
	 	x1=read(),y1=read(),st1=0;
	 	x2=read(),y2=read(),st2=0;
	 	h=read(),w=read();
	 	getst(st1,x1,y1);//找出要修改矩阵的起点（准确点说是左上角，因为从（0,0）开始） 
	 	getst(st2,x2,y2);
		change(st1,st2,h,w,1);//修改四边指针即可，因为剩余的都会连在原来的指针上 
		change(st1,st2,w,h,0);	 	
	 }
 	int p=0;
 	for(int i=1;i<=n;i++)
 	{
	 	p=A[p].dir[1];
	 	int p0=p;
		 for(int j=1;j<=m;j++)
		 {
 			p0=A[p0].dir[0];
 			printf("%d ",A[p0].val);
 		}	
 		printf("\n");
 	}
	return 0;
}
```

---

## 作者：Untitled10032 (赞：2)

## 题意

给定一个矩阵，从中选出若干对两两不重合、不相邻的子矩阵先后进行交换，求所有交换完成后的矩阵。

## 思路

数据量较大，暴力修改会超时，考虑使用一些数据结构。

可以使用二维的链表解决问题，矩阵中每个元素记录右方与下方元素地址（或下标）。下图中每个箭头表示一个“指针”，每个元素保存自己右方元素和下方元素的指针。

![](https://cdn.luogu.com.cn/upload/image_hosting/gs4byxzs.png)

当选定一个矩形准备交换时，我们可以发现交换操作只影响了部分靠近矩形边缘的指针（如下图）。我们只需将两个矩形的这些指针一对一交换即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/mr1b721q.png)

## 代码

- `struct Point`：矩阵中的点定义的结构体。
- `Point::init(int)`：初始化矩阵，包括给指向右和下的指针赋值、初始化本元素权值。
- `Point *pointAt(int, int)`：返回当前矩阵中位于位置 $(x, y)$ 的元素，时间复杂度 $O(x + y)$。
- `std::pair<Point *, Point *> modifyLine(Point*, Point*, int)`：横向交换。前两个参数为两个矩阵相应位置的指针，最后一个参数是要连续修改多少个值。返回值为两个矩阵分别从左向右交换到的最后一个值的地址。
- `std::pair<Point *, Point *> modifyColumn(Point*, Point*, int)`：纵向交换。具体与 `modifyLine` 同理。
- `Point matrix[][]`：矩阵数组，有效的下标从 $1$ 开始，但是第 $0$ 行和第 $0$ 列也被初始化，方便修改时处理。而且 `matrix[0][0]` 始终不会被修改，可以以它为起始点向右或向下访问到全部当前矩阵。


```cpp
#include <iostream>

using std::cin;
using std::cout;
using std::pair;
using std::swap;

constexpr int N = 1005, M = 1005;
int n, m;

struct Point {
    int value;
    Point *right, *down;
    void init(int _value) {
        value = _value;
        right = this + 1;
        down = this + M;
    }
} matrix[N][M];

inline Point *pointAt(int x, int y) {
    Point *p = &matrix[0][0];
    while (x--)
        p = p->down;
    while (y--)
        p = p->right;
    return p;
}

inline pair<Point *, Point *> modifyLine(Point *a, Point *b, int len) {
    swap(a->down, b->down);
    while (--len) {
        a = a->right;
        b = b->right;
        swap(a->down, b->down);
    }
    return {a, b};
}
inline pair<Point *, Point *> modifyColumn(Point *a, Point *b, int len) {
    swap(a->right, b->right);
    while (--len) {
        a = a->down;
        b = b->down;
        swap(a->right, b->right);
    }
    return {a, b};
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int q;
    cin >> n >> m >> q;
    for (int j = 0; j <= m; j++)
        matrix[0][j].init(0);
    for (int i = 1; i <= n; i++) {
        matrix[i][0].init(0);
        for (int j = 1; j <= m; j++) {
            int temp;
            cin >> temp;
            matrix[i][j].init(temp);
        }
    }
    while (q--) {
        int x1, x2, y1, y2, h, w;
        cin >> x1 >> y1 >> x2 >> y2 >> h >> w;
        Point *p1 = pointAt(x1 - 1, y1 - 1), *p2 = pointAt(x2 - 1, y2 - 1);
        pair<Point *, Point *> right_top = modifyLine(p1->right, p2->right, w);
        pair<Point *, Point *> left_bottom = modifyColumn(p1->down, p2->down, h);
        modifyLine(left_bottom.first->right, left_bottom.second->right, w);
        modifyColumn(right_top.first->down, right_top.second->down, h);
    }
    Point *temp = (&matrix[0][0])->right->down;
    for (int i = 1; i <= n; i++) {
        Point *cursor = temp;
        for (int j = 1; j <= m; j++) {
            cout << cursor->value << ' ';
            cursor = cursor->right;
        }
        cout << '\n';
        temp = temp->down;
    }
    return 0;
}
```


---

## 作者：cdxxx04 (赞：2)

# 题解：CF706E Working routine

**[题目传送门](https://www.luogu.com.cn/problem/CF706E)**

---

## 题目思路

### 暴力
我们可以枚举两个矩形中的每一个元素进行交换，具体实现不再赘叙。

**时间复杂度：$\operatorname{\Theta(n m q)}$。**

### 链表
发现此题中的整块移动，块的内部结构没有改变。如图：\
![](https://s3.bmp.ovh/imgs/2025/01/22/1f7f7d779b969707.png)\
所以我们可以把需要交换的两个块的边缘指针交换来达到整体交换的目的。

**时间复杂度：$\operatorname{\Theta(n q)}$。**

## AC代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n,m,q,fx,fy,sx,sy,h,w;
struct Node {
	int val;
	Node*right,*down;
};
Node *A[1005][1005];
inline void input() {
	ios::sync_with_stdio(false);	cin.tie(nullptr);
	cin>>n>>m>>q;
	for(int i=0; i<=n+1; i++)
		for(int j=0; j<=m+1; j++)
			A[i][j]=new Node();
    //初始化空间
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			int x;	cin>>x;
			A[i][j]->val=x;
		}
    //初始化值
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			A[i][j]->down=A[i+1][j];
			A[i][j]->right=A[i][j+1];
		}
	}
    //初始化值指针
}
inline void print() {
	Node *out=A[0][1]->down;
	for(int i=1; i<=n; i++,cout<<'\n') {
		Node *nh=out->down;
		for(int j=1; j<=m; j++,out=out->right)
			cout<<(out->val)<<' ';
		out=nh;
	}
    //打印链表
}
signed main() {
	input();
	while(q--) {
		cin>>fx>>fy>>sx>>sy>>h>>w;
		Node *a=A[0][fy-1],*b=A[0][sy-1];
		for(int i=1; i<fx; i++)	a=a->down;
		for(int i=1; i<sx; i++)	b=b->down;
		Node *ta=a,*tb=b;
		for(int i=1; i<=w; i++)	ta=ta->right,tb=tb->right,swap(ta->down,tb->down);
		for(int i=1; i<=h; i++)	ta=ta->down,tb=tb->down,swap(ta->right,tb->right);
		ta=a;	tb=b;
		for(int i=1; i<=h; i++)	ta=ta->down,tb=tb->down,swap(ta->right,tb->right);
		for(int i=1; i<=w; i++)	ta=ta->right,tb=tb->right,swap(ta->down,tb->down);
        //交换指针
	}
	print();
	return 0;
}
```

---

## 作者：pikabi (赞：2)

### ~~优雅的~~指针



------------

## 题意
给出矩阵上各点的权值，并给出 $q$ 次左上角坐标 $x_1, y_1$ 、 $x_2, y_2$ 即长宽 $h, w$，交换这两个矩阵，求最后矩阵的上各点的值。

## tips

一开始看到交换一段矩阵，笔者不免想到用 fhq Treap 来维护每一段并交换，可惜复杂度堪忧， “ 猝死 ” 于 #11。有兴趣的小伙伴可以来看一下 $-->$ [here。](https://www.luogu.com.cn/paste/cbtj4hwm) 

其实正解是用指针描述每一个点的信息。我维护的是每个点的上（up）下 ( down ) 左 ( l ) 右 ( r )。

先在原先 $n * m$ 的矩阵周围绕上一圈作为边界 $-->$

```cpp
	for(int i = 0; i <= n + 1 ; i++)//这两个是边界上点与矩阵内点的关系
	a[i][0].r = calc(i, 1), a[i][n + 1].l = calc(i, n);
	for(int i = 0; i <= m + 1; i++)
	a[0][i].down = calc(1, i), a[n + 1][i].up = calc(n, i);
	
	for(int i = 0; i <= m; i++)//这些是边界上各点之间的关系
	a[0][i].r = calc(0, i + 1), a[n + 1][i].r = calc(n + 1, i + 1);
	for(int i = 1; i <= m + 1; i++)
	a[0][i].l = calc(0, i - 1), a[n + 1][i].l = calc(n + 1, i - 1);
	for(int i = 0; i <= n; i++)
	a[i][0].down = calc(i + 1, 0), a[i][n + 1].down = calc(i + 1, n + 1);
	for(int i = 1; i <= n + 1; i++)
	a[i][0].up = calc(i - 1, 0), a[i][n + 1].up = calc(i - 1, n + 1);
```

然后是矩阵内各点的关系 $-->$

```cpp
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			a[i][j].l = calc(i, j - 1);
			a[i][j].r = calc(i, j + 1);
			a[i][j].up = calc(i - 1, j);
			a[i][j].down = calc(i + 1, j);
		}
	}
```

接下来是关键：我们交换的矩阵的内部关系是不变的，而只有最外围会改变对应关系，我们可以做一个简单的模拟 $-->$

![](https://cdn.luogu.com.cn/upload/image_hosting/l3ms9pvy.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

初始每个点的上下左右如图所示，周围的 0 是边界，如果把左上角 $3 * 3$ 矩阵和右下角 $3 * 3$ 矩阵交换，中间的相对位置是不会改变的，如（2， 2）的 1，上还是 1，下还是 4 , 左还是 4，右还是 1。所以我们只需要维护周围一圈的信息好了。但是该如何找到矩阵修改后的左上角端点呢？我们可以从 （0， 0）出发，dfs找到，并逐步 dfs（根据其 r 和 down ） 下去，找到端点，在对调信息即可。我是先一步枚举竖直方向，考虑到可能会改变左右端点，故在枚举水平方向时在 dfs2 中先 dfs 水平方向（其实也没必要，无论水平是否交换矩阵上下交换结果不变 ）。

这是 dfs （dfs2 同理）$-->$

```cpp
inline pair<int, int> dfs(int x, int y, int xx, int yy){//xx，yy 为将要走的步数，x、y 为当前坐标。用 pair 传递目标的坐标
	if(xx){
		pair <int, int> now = re_calc(a[x][y].down );
		return dfs(now.first , now.second , xx - 1, yy);
	}
	if(yy){
		pair <int, int > now = re_calc(a[x][y].r );
		return dfs(now.first , now.second , xx, yy - 1);
	}
	return make_pair(x, y);
}
}
```


由于笔者能力有限，在维护信息时打的~~又臭又长~~，但个人感觉还是比较对称美观的 ~~（逃~~

下面给出矩阵左端的维护代码 $-->$

```
	pair <int, int> now1 = dfs(0, 0, x1 - 1, y1);
	pair <int, int> now2 = dfs(0, 0, x2 - 1, y2);
  	for(int j = 0; j < h; j++){
		now1 = dfs(now1.first , now1.second , 1, 0);
		now2 = dfs(now2.first , now2.second , 1, 0);
		pair <int, int> u = re_calc(a[now1.first][now1.second ].l );
		pair <int, int> v = re_calc(a[now2.first][now2.second ].l );
		a[u.first ][u.second ].r = calc(now2.first, now2.second );
		a[v.first ][v.second ].r = calc(now1.first, now1.second );
		a[now1.first][now1.second ].l = calc(v.first , v.second );
		a[now2.first][now2.second ].l = calc(u.first , u.second );
	}
```

最后 dfs 并输出即可。

下面给出总代码 $-->$

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define ll long long
#define inf 0x3f3f3f3f

using namespace std;

inline int read(){
	int x=0,w=0;char ch=getchar();
	while (!isdigit(ch))w|=ch=='-',ch=getchar();
	while (isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return w?-x:x;
}

struct node{
	int l, r, up, down;
	int val;
}a[1005][1005];

int n, m, q, b[1005][1005], cnt; 

inline int calc(int x, int y){
	return x * (m + 3) + y;
}

inline pair<int, int> re_calc(int p){
	return make_pair(p / (m + 3), p % (m + 3));
}

inline pair<int, int> dfs(int x, int y, int xx, int yy){
	if(xx){
		pair <int, int> now = re_calc(a[x][y].down );
		return dfs(now.first , now.second , xx - 1, yy);
	}
	if(yy){
		pair <int, int > now = re_calc(a[x][y].r );
		return dfs(now.first , now.second , xx, yy - 1);
	}
	return make_pair(x, y);
}

inline pair<int, int> dfs2(int x, int y, int xx, int yy){
	if(yy){
		pair <int, int> now = re_calc(a[x][y].r );
		return dfs2(now.first , now.second , xx, yy - 1);
	}
	if(xx){
		pair <int, int > now = re_calc(a[x][y].down );
		return dfs2(now.first , now.second , xx - 1, yy);
	}
	return make_pair(x, y);
}

int main(){
	n = read();
	m = read();
	q = read();
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			a[i][j].val = read();
		}
	}
	for(int i = 0; i <= n + 1 ; i++)
	a[i][0].r = calc(i, 1), a[i][n + 1].l = calc(i, n);
	
	for(int i = 0; i <= m + 1; i++)
	a[0][i].down = calc(1, i), a[n + 1][i].up = calc(n, i);
	
	for(int i = 0; i <= m; i++)
	a[0][i].r = calc(0, i + 1), a[n + 1][i].r = calc(n + 1, i + 1);
	
	for(int i = 1; i <= m + 1; i++)
	a[0][i].l = calc(0, i - 1), a[n + 1][i].l = calc(n + 1, i - 1);
	
	for(int i = 0; i <= n; i++)
	a[i][0].down = calc(i + 1, 0), a[i][n + 1].down = calc(i + 1, n + 1);
	
	for(int i = 1; i <= n + 1; i++)
	a[i][0].up = calc(i - 1, 0), a[i][n + 1].up = calc(i - 1, n + 1);
	
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			a[i][j].l = calc(i, j - 1);
			a[i][j].r = calc(i, j + 1);
			a[i][j].up = calc(i - 1, j);
			a[i][j].down = calc(i + 1, j);
		}
	}
	for(int i = 1; i <= q; i++){
		int x1 = read(), y1 = read(), x2 = read(), y2 = read(), h = read(), w = read();
		pair <int, int> now1 = dfs(0, 0, x1 - 1, y1);
		pair <int, int> now2 = dfs(0, 0, x2 - 1, y2);
		pair <int, int> now3 = dfs(0, 0, x1 - 1, y1 + w - 1);
		pair <int, int> now4 = dfs(0, 0, x2 - 1, y2 + w - 1);
		for(int j = 0; j < h; j++){
			now1 = dfs(now1.first , now1.second , 1, 0);
			now2 = dfs(now2.first , now2.second , 1, 0);
			now3 = dfs(now3.first , now3.second , 1, 0);
			now4 = dfs(now4.first , now4.second , 1, 0);
			pair <int, int> u = re_calc(a[now1.first][now1.second ].l );
			pair <int, int> v = re_calc(a[now2.first][now2.second ].l );
			a[u.first ][u.second ].r = calc(now2.first, now2.second );
			a[v.first ][v.second ].r = calc(now1.first, now1.second );
			a[now1.first][now1.second ].l = calc(v.first , v.second );
			a[now2.first][now2.second ].l = calc(u.first , u.second );
			u = re_calc(a[now3.first][now3.second ].r );
			v = re_calc(a[now4.first][now4.second ].r );
			a[u.first ][u.second ].l = calc(now4.first, now4.second);
			a[v.first ][v.second ].l = calc(now3.first, now3.second);
			a[now3.first][now3.second].r = calc(v.first , v.second );
			a[now4.first][now4.second].r = calc(u.first , u.second );
		}
		now1 = dfs2(0, 0, x1, y1 - 1);
		now2 = dfs2(0, 0, x2, y2 - 1);
		now3 = dfs2(0, 0, x1 + h - 1, y1 - 1);
		now4 = dfs2(0, 0, x2 + h - 1, y2 - 1);
		for(int j = 0; j < w; j++){
			now1 = dfs(now1.first , now1.second , 0, 1);
			now2 = dfs(now2.first , now2.second , 0, 1);
			now3 = dfs(now3.first , now3.second , 0, 1);
			now4 = dfs(now4.first , now4.second , 0, 1);
			pair <int, int> u = re_calc(a[now1.first ][now1.second ].up );
			pair <int, int> v = re_calc(a[now2.first ][now2.second ].up );
			a[u.first ][u.second ].down = calc(now2.first , now2.second );
			a[v.first ][v.second ].down = calc(now1.first , now1.second );
			a[now1.first ][now1.second ].up = calc(v.first , v.second );
			a[now2.first ][now2.second ].up = calc(u.first , u.second );
			u = re_calc(a[now3.first ][now3.second ].down );
			v = re_calc(a[now4.first ][now4.second ].down );
			a[u.first ][u.second ].up = calc(now4.first , now4.second );
			a[v.first ][v.second ].up = calc(now3.first , now3.second );
			a[now3.first ][now3.second ].down = calc(v.first , v.second );
			a[now4.first ][now4.second ].down = calc(u.first , u.second );
		}
	}
	for(int i = 1; i <= n; i++){
		pair <int, int> now = dfs(0, 0, i, 0);
		for(int j = 1; j <= m; j++){
			now = dfs(now.first , now.second , 0, 1);
			printf("%d ",a[now.first ][now.second ].val );
		}
		printf("\n");
	}
    return 0;
}

```
完结撒花✿✿ヽ(°▽°)ノ✿



---

## 作者：Piwry (赞：1)

神奇的链表题

想到链表就不难了

## 解析

题目要求我们交换两个矩阵

可以想到，交换后这两个矩阵内部元素的相对关系是**不变的**；变化的只有和矩阵边缘相邻的矩阵外元素

于是就可以想到维护一个十字链表，储存一个元素右方和下方邻接的元素地址。对于每次询问，只要遍历被交换的矩阵的边邻接的元素，交换它们的指针就可以了。实现细节可以看代码

每次询问的复杂度是 $O(2(n+m))$，总的复杂度是 $O(2(n+m)q)$

## CODE

```cpp
#include <cstdio>
#include <iostream>
using std::swap;

const int MAXN =1000+50;

struct qwq{
	int right, down;
	int val;
}list[MAXN*MAXN];

/*获取矩阵第 x 行第 y 列的元素*/
/*注意有下标为 0 的 index*/
inline int get(int x, int y){
	/*可以知道第一行是不会被修改的*/
	int nw =1;
	for(int i =0; i < y; ++i)
		++nw;
	for(int i =0; i < x; ++i)
		nw =list[nw].down;
	return nw;
}

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

int main(){
	int n =read(), m =read(), q =read();
	for(int i =1; i <= (n+1)*(m+1); ++i){
		if(i > m+1 && (i-1)%(m+1) != 0)
			list[i].val =read();
		if(i%(m+1) != 0)
			list[i].right =i+1;
		if(i <= n*(m+1))
			list[i].down =i+m+1;
	}
	/*保证交换的矩阵不共边不重合*/
	for(int k =0; k < q; ++k){
		int x1 =read(), y1 =read(), x2 =read(), y2 =read(), h =read(), w =read();
		/*h 行 w 列*/
		int ph1 =get(x1-1, y1-1), ph2 =get(x2-1, y2-1);
		int pw1 =list[ph1].right, pw2 =list[ph2].right;
		ph1 =list[ph1].down, ph2 =list[ph2].down;
		int ph3 =get(x1, y1+(w-1)), ph4 =get(x2, y2+(w-1));
		int pw3 =get(x1+(h-1), y1), pw4 =get(x2+(h-1), y2);
		for(int i =0; i < h; ++i){
			swap(list[ph1].right, list[ph2].right);
			ph1 =list[ph1].down, ph2 =list[ph2].down;
			swap(list[ph3].right, list[ph4].right);
			ph3 =list[ph3].down, ph4 =list[ph4].down;
		}
		for(int i =0; i < w; ++i){
			swap(list[pw1].down, list[pw2].down);
			pw1 =list[pw1].right, pw2 =list[pw2].right;
			swap(list[pw3].down, list[pw4].down);
			pw3 =list[pw3].right, pw4 =list[pw4].right;
		}
	}
	int p =1;
	for(int i =0; i < n; ++i){
		p =list[p].down;
		for(int j =0, nw =list[p].right; j < m; ++j){
			printf("%d ", list[nw].val);
			nw =list[nw].right;
		}
		putchar('\n');
	}
}
```

---

## 作者：HECZ (赞：1)

#### 简述题意：

> 给定一个 $1000 \times 1000$ 的矩阵，每次交换任意两个不重合的子矩阵，求最后的结果

#### 思路1（部分分）：

平衡树。复杂度 $O(m \times n \log n)$，但是很遗憾，由于常数实在过大，导致最后得分甚至可能不如暴力 `memcpy`。

#### 思路2（正解）：

链表。大致思路是维护一个矩形的链表，每次交换分别把两块矩阵取出再拼接上去。

```cpp
#include <bits/stdc++.h>
#typedef long long ll;

int read() {
    int x = 0; bool m = 0; char c = getchar();
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-') m = 1, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (m) return -x; else return x;
}

const int maxn = 1010, maxm = 1000010;

int n, m, q, ax, ay, bx, by, l, c, lst, tmp;
int al[maxn][maxn], ar[maxn][maxn];

char s[10000010];

void reads(int &l, int &r) {
    char c = getchar();
    while (c == ' ' || c == '\n') c = getchar();
    l = ++lst, r = l - 1;
    while (c != ' ' && c != '\n') {
        s[++r] = c;
        c = getchar();
    }
    lst = r;
}

void prints(int l, int r) {
    for (int i = l; i <= r; i++)
        putchar(s[i]);
}

struct node {
    int x, y;
    node () {}
    node (int a, int b) { x = a, y = b; }
};
node au, bu, as, bs;
node ex[maxn][maxn], ey[maxn][maxn];

struct pair {
    node a, b;
    pair () {}
    pair (node x, node y) { a = x, b = y; }
};
std::vector < pair > todo_ex, todo_ey;

node lead_to(int x, int y) {
    node u = node(0, 0);
    while (x--) u = ex[u.x][u.y];
    while (y--) u = ey[u.x][u.y];
    return u;
}

void print() {
    node u(0, 0);
    for (int i = 1; i <= n; i++) {
        node v = u = ex[u.x][u.y];
        for (int j = 1; j <= m; j++) {
            v = ey[v.x][v.y];
            prints(al[v.x][v.y], ar[v.x][v.y]);
            putchar(' ');
        }
        putchar('\n');
    }
}

void swap_ex(node a, node b) {
    todo_ex.push_back(pair(a, b));
}

void swap_ey(node a, node b) {
    todo_ey.push_back(pair(a, b));
}

int main() {

    n = read(), m = read(), q = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            reads(al[i][j], ar[i][j]);
        }
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++) {
            ex[i][j] = node(i + 1, j);
            ey[i][j] = node(i, j + 1);
        }

    for (int t = 1; t <= q; t++) {
        ax = read(), ay = read();
        bx = read(), by = read();
        l = read(), c = read();
        as = lead_to(ax - 1, ay - 1);
        bs = lead_to(bx - 1, by - 1);
        au = as, bu = bs;
        for (int i = 1; i <= l; i++) {
            au = ex[au.x][au.y];
            bu = ex[bu.x][bu.y];
            swap_ey(au, bu);
        }
        au = as, bu = bs;
        for (int i = 1; i <= c; i++) {
            au = ey[au.x][au.y];
            bu = ey[bu.x][bu.y];
            swap_ex(au, bu);
        }
        au = as, bu = bs;
        for (int i = 1; i <= l; i++) {
            au = ex[au.x][au.y];
            bu = ex[bu.x][bu.y];
        }
        for (int i = 1; i <= c; i++) {
            au = ey[au.x][au.y];
            bu = ey[bu.x][bu.y];
            swap_ex(au, bu);
        }
        au = as, bu = bs;
        for (int i = 1; i <= c; i++) {
            au = ey[au.x][au.y];
            bu = ey[bu.x][bu.y];
        }
        for (int i = 1; i <= l; i++) {
            au = ex[au.x][au.y];
            bu = ex[bu.x][bu.y];
            swap_ey(au, bu);
        }
        for (std::vector < pair > ::iterator it = todo_ex.begin();
                it != todo_ex.end();
                it++)
            std::swap(ex[it->a.x][it->a.y], ex[it->b.x][it->b.y]);
        for (std::vector < pair > ::iterator it = todo_ey.begin();
                it != todo_ey.end();
                it++)
            std::swap(ey[it->a.x][it->a.y], ey[it->b.x][it->b.y]);
        todo_ex.clear();
        todo_ey.clear();
    }
    print();

    return 0;
}
```

---

## 作者：lyhqwq (赞：0)

# Solution

每次交换两个矩阵，且没有查询，所以我们可以用双向链表这种数据结构来完成矩阵的交换。

每次交换的时候只需要交换矩阵最外面一圈的结点的指针即可。

复杂度 $O((n+m)q)$。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
struct node{
	int val;
	int r,d;
}a[N*N];
int n,m,q;
int turn(int i,int j){
	return i*m+j;
}
void get(int &p,int x,int y){
	for(int i=1;i<=x;i++) p=a[p].d;
	for(int i=1;i<=y;i++) p=a[p].r;
}
void change1(int p1,int p2,int x,int y){
	for(int i=1;i<=x;i++){
		p1=a[p1].r;
		p2=a[p2].r;
		swap(a[p1].d,a[p2].d);
	}
	for(int i=1;i<=y;i++){
		p1=a[p1].d;
		p2=a[p2].d;
		swap(a[p1].r,a[p2].r);
	}
}
void change2(int p1,int p2,int x,int y){
	for(int i=1;i<=x;i++){
		p1=a[p1].d;
		p2=a[p2].d;
		swap(a[p1].r,a[p2].r);
	}
	for(int i=1;i<=y;i++){
		p1=a[p1].r;
		p2=a[p2].r;
		swap(a[p1].d,a[p2].d);
	}
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[turn(i,j)].val);
		}
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			a[turn(i,j)].r=turn(i,j+1);
			a[turn(i,j)].d=turn(i+1,j);
		}
	}
	while(q--){
		int x1,y1,x2,y2,h,w;
		scanf("%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&h,&w);
		int p1=0,p2=0;
		get(p1,x1-1,y1-1);
		get(p2,x2-1,y2-1);
		change2(p1,p2,h,w);
		change1(p1,p2,w,h);
		
	}
	int p=0;
	for(int i=1;i<=n;i++){
		p=a[p].d;
		int P=p;
		for(int j=1;j<=m;j++){
			P=a[P].r;
			printf("%d ",a[P].val);
		}
		puts("");
	}
	return 0;
}

```



---

## 作者：intel_core (赞：0)

#### 解法一 数据结构

拿一个数据结构把每一行的数维护一下，修改的时候只需要切割/合并一下就行。

如果使用 `FHQ Treap` 或者 `Splay` 的话，切割次数过多导致整棵树被切得支离破碎，深度巨大。本地 `FHQ Treap` 最快跑到 $\text{7.5s}$ ，不是一般的慢。

如果加上替罪羊树的推平操作，那么可以跑到 $\text{4s}$ 左右，还是不够。

换用结构稳定的块状链表，理论复杂度 $O(qm \sqrt{n})$，看起来就过不了。

-------------------------

#### 解法二 十字链表

既然无论 $O(qm \log n)$ 和 $O(qm \sqrt{n})$ 都过不了，那就尝试 $O(q(n+m))$ 的算法。

考虑用十字链表维护矩阵，观察到交换两个矩阵只需要改动边缘的指针就可以。

如果使用链表，就没办法快速得到矩阵上的点在链表内对应的点，因为链表查找单次是 $O(n)$ 的，一次修改只能用常数次。

这里可以先 $O(n)$ 找出矩阵的左上角，再 $O(n+m)$ 把矩形的边缘顶点都找出来。

然后把指针都换一下就行了。

复杂度 $O(q(n+m))$

---

