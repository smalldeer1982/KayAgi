# Case of Chocolate

## 题目描述

Andrewid the Android is a galaxy-known detective. Now he does not investigate any case and is eating chocolate out of boredom.

A bar of chocolate can be presented as an $ n×n $ table, where each cell represents one piece of chocolate. The columns of the table are numbered from $ 1 $ to $ n $ from left to right and the rows are numbered from top to bottom. Let's call the anti-diagonal to be a diagonal that goes the lower left corner to the upper right corner of the table. First Andrewid eats all the pieces lying below the anti-diagonal. Then he performs the following $ q $ actions with the remaining triangular part: first, he chooses a piece on the anti-diagonal and either direction 'up' or 'left', and then he begins to eat all the pieces starting from the selected cell, moving in the selected direction until he reaches the already eaten piece or chocolate bar edge.

After each action, he wants to know how many pieces he ate as a result of this action.

## 说明/提示

Pictures to the sample tests:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF555C/68417759be7789b5dc33e557d3b01b391502988d.png)

The pieces that were eaten in the same action are painted the same color. The pieces lying on the anti-diagonal contain the numbers of the action as a result of which these pieces were eaten.

In the second sample test the Andrewid tries to start eating chocolate for the second time during his fifth action, starting from the cell at the intersection of the 10-th column and the 1-st row, but this cell is already empty, so he does not eat anything.

## 样例 #1

### 输入

```
6 5
3 4 U
6 1 L
2 5 L
1 6 U
4 3 U
```

### 输出

```
4
3
2
1
2
```

## 样例 #2

### 输入

```
10 6
2 9 U
10 1 U
1 10 U
8 3 L
10 1 L
6 5 U
```

### 输出

```
9
1
10
6
0
2
```

# 题解

## 作者：Krystallos (赞：6)

看到前面一堆神仙用各种STL爆切此题，我则表示我STL没学好，用不来。

首先，题目说这块巧克力呈三角形，大概就是这个样子：

![](https://s2.ax1x.com/2020/02/05/1seQQ1.png)

然后，我们会选择对角线上的某一块，向上或向左一直吃，直到某一块被吃过了。

显然，第一口可以直接吃到底，那么以后呢？会受到之前的影响。

假设前面已经吃掉了红色与橙色两部分，黄色为这一次吃掉的部分。不难看出，黄色在向上延伸的过程中遭到了橙色的阻拦。那么如何迅速找出黄色在哪里被吃掉了呢？

![](https://s2.ax1x.com/2020/02/05/1sm7ut.png)

不难发现，之前与本次食用方向相同的食用所减少的巧克力块一定不会影响到当前食用（从同一块开始吃除外）。同时，我们还有之前所吃的不同向的食用后果。以图中为例，橙色吃掉了后相当于把上边界向下移动了三格。橙色所影响的是一个范围的上边界，查询需要的是查找单列或单行的最近边界。于是问题就转化成了每次食用后是区间修改，把整个区间内更远的边界更新成为更近的边界；每次食用前是单点查询，查找单行或单列的最近边界。而这正好是线段树所擅长的。

需要注意的一点是，我们要维护在两个方向上的食用信息，因此我们需要两颗线段树。另外，$n$最大可以取到$10^9$，需要动态开点。

code:
```cpp
#include<stdio.h>
int n, ans;
int q;
struct SegTree{
	int l, r, lazy;
	int ls, rs;
	#define l(p, i) tree[i][p].l//我喜欢宏定义掉，老老实实写变量名太长了
	#define r(p, i) tree[i][p].r
	#define lazy(p, i) tree[i][p].lazy
	#define ls(p, i) tree[i][p].ls
	#define rs(p, i) tree[i][p].rs
}tree[2][6000005];
int tot[2];
int mid;
#define max(p, q) (p > q ? p : q)
inline void spread(int p, int id) {
	mid = (l(p, id) + r(p, id)) >> 1;
	if (ls(p, id) == 0) {//如果没有儿子就创造儿子
		ls(p, id) = ++tot[id];
		l(ls(p, id), id) = l(p, id);
		r(ls(p, id), id) = mid;
		lazy(ls(p, id), id) = 0;
	}
	if (rs(p, id) == 0) {
		rs(p, id) = ++tot[id];
		l(rs(p, id), id) = mid + 1;
		r(rs(p, id), id) = r(p, id);
		lazy(rs(p, id), id) = 0;
	}
	if (lazy(p, id)) {
		lazy(ls(p, id), id) = max(lazy(ls(p, id), id), lazy(p, id));
		lazy(rs(p, id), id) = max(lazy(rs(p, id), id), lazy(p, id));
		lazy(p, id) = 0;
	}
}
void change(int p, int l, int r, int d, int id) {
	if (lazy(p, id) >= d)
		return;
	if (l <= l(p, id) && r(p, id) <= r) {
		lazy(p, id) = max(lazy(p, id), d);//把权值改为较大值
		return;
	}
	spread(p, id);
	if (l <= r(ls(p, id), id))
		change(ls(p, id), l, r, d, id);
	if (l(rs(p, id), id) <= r)
		change(rs(p, id), l, r, d, id);
	return;
}
int ask(int p, int k, int id) {
	if (l(p, id) == r(p, id))
		return lazy(p, id);//根结点的lazy不可能下放，一定代表自身权值
	spread(p, id);
	if (k <= r(ls(p, id), id))
		return ask(ls(p, id), k, id);
	else
		return ask(rs(p, id), k, id);
}
int main() {
	scanf("%d %d", &n, &q);
	tree[0][++tot[0]] = SegTree{1, n, 0, 0};//定义两个根结点
	tree[1][++tot[1]] = SegTree{1, n, 0, 0};
	int i, j;
	char opt;
	while (q--) {
		scanf("%d %d %c", &i, &j, &opt);
		if (opt == 'U') {
			ans = ask(1, i, 0);//查询边界
			change(1, ans + 1, j, i, 1);//处理本次造成的影响
			change(1, i, i, j, 0);//注意，即使方向相同，同一个位置吃两次也要记录
			printf("%d\n", j - ans);
		} else {
			ans = ask(1, j, 1);//同上
			change(1, ans + 1, i, j, 0);
			change(1, j, j, i, 1);
			printf("%d\n", i - ans);
		}
	}
	return 0;
}

```

---

## 作者：Sooke (赞：6)

### 解题思路

> 引理: 不管怎么分割，任意一块一定形如：
>
> ![](https://i.loli.net/2019/04/01/5ca1af553b983.png)
>
> 简单来说，就是题目里的阶梯状物，右、下可能被切过一刀。

瞪眼观察法、显然法、归纳法皆可证明。

怎么优美地利用这个性质呢？我们给它标些有用的信息。

![](https://i.loli.net/2019/04/01/5ca1b12802e43.png)

在上图中，引用了 $l,\,r,\,x,\,y$ 四个值，这表明了这一块左上角在 $(x,\,y)$ 处，右下角的阶梯属于第 $[l,\,r]$ 行。

**注意，原题的坐标系有点奇怪，故此处使用 OI 最常用的坐标系规则，请读者自行转换。**

这样表示有什么好处？尝试证明：

> 任意一块的 $[l,\,r]$ 互不交。

因此，我们可以用类似 ODT 的平衡树（为了方便，std::set 是不二之选）来维护每一块。

剩下的就非常简单了，每次分割，lowerbound 找到所属块，如果属于其区间，暴力分类讨论并分裂，否则答案为 0。

---

### 代码实现

```cpp
#include <cstdio>
#include <set>

struct Element { int l, r, x, y; } e, u, v;

bool operator <(const Element &u, const Element &v) { return u.l == v.l ? u.r < v.r : u.l < v.l; }

int n, m, x, y, ans;
std::set<Element> set;

int main() {
    scanf("%d %d", &n, &m);
    set.insert((Element) {0, 0, 1, 1});
    set.insert((Element) {1, n, 1, 1});
    for (char opt; m; m--) {
        scanf("%d %d %c", &x, &y, &opt);
        e = *--set.lower_bound((Element) {x, n + 1, 1, 1});
        if (e.l <= x && x <= e.r) {
            set.erase(e);
            if (opt == 'L') {
                ans = x - e.x + 1;
                set.insert((Element) {e.l, x - 1, e.x, y + 1});
                set.insert((Element) {x + 1, e.r, e.x, e.y});
            } else {
                ans = y - e.y + 1;
                set.insert((Element) {e.l, x - 1, e.x, e.y});
                set.insert((Element) {x + 1, e.r, x + 1, e.y});
            }
        } else { ans = 0; }
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：slzs (赞：2)

##### 提供一种离线算法

先按x从小到大排序，有顺序的从下自上处理。

对于往上吃的直接加入另一个队列。当遇到向右吃的时，更新吃的顺序比它大的，弹出，更新本身。

#### 时间:O(qlogq)
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
using namespace std;
const int N=2e5+10;
int n,Q,tp=0,ans[N];
struct A{int x,y,type,d;}a[N],sta[N];
inline int cmp(A x,A y){return (x.x==y.x)?x.type<y.type:x.x<y.x;}
inline int read()
{
	int x=0,minus=0; char ch;
	while (!isdigit(ch=getchar())) minus|=(ch=='-');
	while (isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return minus?-x:x;
}
inline int gc()
{
	char ch=getchar();
	while (ch!='U'&&ch!='L') ch=getchar();
	if (ch=='U') return 1;
	return 0;
}
signed main()
{
	n=read(),Q=read();
	for (register int i=1,x,y,z;i<=Q;++i) x=read(),y=read(),z=gc(),a[i]=(A){x,y,i,z};
	sort(a+1,a+1+Q,cmp);
	sta[0]=(A){0,n+1,0,0};
	a[Q+1]=(A){n+1,0,0,0};
	for (register int i=1;i<=Q+1;++i)
	{
		if (a[i].x==a[i-1].x&&a[i].y==a[i-1].y) continue;
		if (a[i].d) sta[++tp]=a[i];
		else {
			while (sta[tp].type>a[i].type) ans[sta[tp].type]=sta[tp].y-a[i].y,tp--;
			ans[a[i].type]=a[i].x-sta[tp].x;
		}
	}
	for (register int i=1;i<=Q;++i) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：LJC00753 (赞：2)

n很大，我们需要离散化

然后我们维护每一行和每一列的最右边（对于行的情况），或最右边（对于列的情况）的被吃的巧克力


然后我们就可以转换为区间修改，单点求值问题了

开两珂线段树维护即可

具体来说如下

（以U操作为例，L操作同理）

找到在x列的最大行号被吃巧克力的行号p

将第p+1～y的行 对x取max

同时将第x列赋值为y // 最初我忘记写这个了WA on 4

```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 400005
#define lc(i) (i<<1)
#define rc(i) ((i<<1)|1)

int n,m;
struct wen {
	int x,y,opt;
}a[MAXN];
int u[MAXN];

struct aa {
	int l,r,x;
}c[MAXN<<2],d[MAXN<<2];

void jianshu(aa *c,int i,int l,int r) {
	int mid = (l+r)>>1;
	c[i].l = l;
	c[i].r = r;
	if(l == r) {
		return;
	}
	jianshu(c,lc(i),l,mid);
	jianshu(c,rc(i),mid+1,r);
}

namespace lsh//离散化
{
	map<int,int>p;
	int t[MAXN],f[MAXN];
	void QAQ()
	{
		int nn = 0;
		for(int i = 1; i <= m; i ++) {
			nn ++; t[nn] = a[i].x;
			nn ++; t[nn] = a[i].y;
		}
		sort(t+1,t+nn+1);
		for(int i = 1; i <= nn; i ++)
		if(t[i] == t[i-1]) f[i] = f[i-1];
		else f[i] = f[i-1]+1;
		for(int i = 1; i <= nn; i ++) {
			p[t[i]] = f[i];
			u[f[i]] = t[i];
		}
		n = f[nn];
		int i = 1;
		for(i = 1; i <= m; i ++) {
			a[i].x = p[a[i].x];
			a[i].y = p[a[i].y];
		}
	}
}

void rd()
{
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= m; i ++) {
		int x,y;
		string opt;
		scanf("%d%d",&x,&y);
		cin >> opt;
		a[i].x = x;
		a[i].y = y;
		if(opt == "U") a[i].opt = 1;
		else a[i].opt = 2;
	}
	lsh::QAQ();
}

void gai(aa *c,int i,int l,int r,int x)
{
	if(l <= c[i].l && c[i].r <= r) {
		c[i].x = max(c[i].x,x);
		return;
	}
	if(l > c[i].r || r < c[i].l) return;
	gai(c,lc(i),l,r,x);
	gai(c,rc(i),l,r,x);
}

int qiu(aa *c,int i,int l) {
	if(c[i].l == c[i].r) return c[i].x;
	int mid = (c[i].l + c[i].r)>>1;
	if(l > mid) return max(c[i].x , qiu(c,rc(i),l));
	else  return max(c[i].x , qiu(c,lc(i),l));
}

int main()
{
	rd();
	jianshu(c,1,1,n);
	jianshu(d,1,1,n);
	for(int i = 1; i <= m; i ++)
	{
		if(a[i].opt == 1) {
			int p = qiu(d,1,a[i].x);
			printf("%d\n",u[a[i].y] - u[p]);
			gai(c,1,p+1,a[i].y,a[i].x);
			gai(d,1,a[i].x,a[i].x,a[i].y);
		} else {
			int p = qiu(c,1,a[i].y);
			printf("%d\n",u[a[i].x] - u[p]);
			gai(d,1,p+1,a[i].x,a[i].y);
			gai(c,1,a[i].y,a[i].y,a[i].x);
		}
	}
	return 0;
}

```

---

## 作者：Leap_Frog (赞：1)

### Description.
给定一个如题图所示的斜三角，大小为 $10^9\times10^9$ 级别。  
每次从一个点往 上/右 删格子，碰到没格子的地方就停止。  
问第 $i$ 次操作会删掉几个格子。  

### Solution.
我们只考虑横线操作，竖线同理。  
首先，每个横线操作只会和左边的竖线操作有关  
我们对于每个横线，找到之前的最近的竖线。  
那每个竖线能影响的范围是一个区间。  
左端点是竖线当前所在的值，右端点是它撞到的横线所在的位置。  
同时，比如 5U 3U 这样，它影响是取 max，所以不一定能有一整个区间  
所以我们可以考虑直接用区间取 max 的动态开点线段树来维护。  
吉司机？因为是单点查询好像并不需要，直接标记永久化即可。  
然后就做完了  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了……{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}/*}}}*/
struct SegmentTree
{
	struct node{int ls,rs,tg;}T[10000005];int tt,rt;SegmentTree() {rt=tt=1;}
	inline node& New(int &x) {return x?T[x]:(x=++tt,T[x]=(node){0,0,0});}
	inline void allc(int &x,int dc) {New(x),T[x].tg=max(T[x].tg,dc);}
	inline void pushdw(int x) {allc(T[x].ls,T[x].tg),allc(T[x].rs,T[x].tg);}
	inline void modif(int &x,int l,int r,int dl,int dr,int dc)
	{
		if(l>dr||dl>r) return;else if(dl<=l&&r<=dr) return allc(x,dc);else pushdw(x);
		modif(T[x].ls,l,(l+r)>>1,dl,dr,dc),modif(T[x].rs,((l+r)>>1)+1,r,dl,dr,dc);
	}
	inline int query(int x,int l,int r,int dw)
	{
		if(!x) return 0;else if(l==r) return T[x].tg;
		if(dw<=((l+r)>>1)) return max(T[x].tg,query(T[x].ls,l,(l+r)>>1,dw));
		else return max(T[x].tg,query(T[x].rs,((l+r)>>1)+1,r,dw));
	}
}L,U;int n,m;
int main()
{
	set<int>st;for(read(n),read(m);m--;)
	{
		int x,y;char ch[5];read(y),read(x),scanf("%s",ch);
		if(st.count(x)) {puts("0");continue;}else st.insert(x);
		if(*ch=='U')
		{
			int rs=L.query(L.rt,1,n,y);printf("%d\n",x-rs);
			U.modif(U.rt,1,n,rs,x,y);
		}
		else
		{
			int rs=U.query(U.rt,1,n,x);printf("%d\n",y-rs);
			L.modif(L.rt,1,n,rs,y,x);
		}
	}
	return 0;
}
```

---

## 作者：Farkas_W (赞：1)

### 思路：

$\quad$说实话，第一眼看这题想到的是线段树，但无奈 $1<=n<=10^
9$ ，离散化有点复杂，动态开点又不会，所以使用了一种离线做法，跑的还贼快(大雾

$\quad$现将所有操作存起来， $dir$ 表示方向， $1$ 为上， $0$ 为左，然后按 $x$ 为第一关键字， $t$ (时间)为第二关键字排序(我第一次 $WA$ 就是这个原因)

```cpp
struct node{
  int x,y,t,dir;
}a[N],b[N];
il bool cmp(node a1,node a2){return a1.x==a2.x?a1.t<a2.t:a1.x<a2.x;}

  for(re i=1,x,y;i<=m;i++)
    {
      x=read(),y=read();ch=getchar();
      if(ch=='U')a[i]=(node){x,y,i,1};
      else a[i]=(node){x,y,i,0};
     }
  sort(a+1,a+m+1,cmp);
```
$\quad$然后考虑每一种情况，显然，向左的操作会被前面的向上的操作影响(前面的指 $x$ 小于 $TA$ ，且时间 $t$ 也小于 $TA$ 的)，向上的操作会被后面的向左的操作影响(后面指 $x$ 大于 $TA$ ，但时间 $t$ 小于 $TA$ 的)，所以可以发现相邻的向上的操作和向左的操作会互相影响(相邻是指x相邻)，这时候我们就要判断它们的时间先后了。

![](https://cdn.luogu.com.cn/upload/image_hosting/aryy231z.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/8h36goah.png)

$\quad$然后我们就可以发现只有向上的操作在前，才有可能对后面的向左的操作产生影响(先不考虑时间)，另外向上的也只被后面的第一个向左的所影响，所以向上的暂时无法得出答案，先放进一个栈中存储，只有遇到向左的就把栈中的时间大于 $TA$ 的更新答案，遇到一个时间小于 $TA$ 的就被堵住了，这时候就更新它自己的答案。(这里的 $TA$ 指的是向左的操作)

$\quad$现在来模拟一个数据来理解一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/yvb790ad.png)

$\quad$先排序，对于操作 $4$ ，此时栈是空的，直接更新答案，对于操作 $6$ 、操作 $1$ 和操作 $5$ ，直接存进栈里，等到操作 $3$ 时开始退栈，先比较栈顶的时间，更新操作 $5$ 的时间，将 $5$ 退出，然后和操作 $1$ 比较，停止退栈，更新操作 $3$ 本身的答案，最后将操作 $2$ 压进栈中，循环结束，将栈中元素全部退出，这些把一列的巧克力都吃光了。

$\quad$如果还不理解就看看完整代码吧，附带注释。
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
#define re register int
#define int long long
#define il inline
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
il void print(int x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
const int N=2e5+5;
int n,m,ans[N],tot;
struct node{
  int x,y,t,dir;
}a[N],b[N];
il bool cmp(node a1,node a2){return a1.x==a2.x?a1.t<a2.t:a1.x<a2.x;}//注意
signed main()
{
  n=read();m=read();char ch;
  for(re i=1,x,y;i<=m;i++)
    {
      x=read(),y=read();ch=getchar();
      if(ch=='U')a[i]=(node){x,y,i,1};//dir=1表示向上，Up
      else a[i]=(node){x,y,i,0};//dir=0表示向左，Left
    }
  sort(a+1,a+m+1,cmp);//排序
  b[0]=(node){0,n+1,0,1};//处理边界
  for(re i=1;i<=m;i++)
    {
      if(a[i].x==a[i-1].x&&a[i].y==a[i-1].y)continue;//如果遇到相同的就跳过，后面的一个巧克力都吃不到
      if(a[i].dir)b[++tot]=a[i];
      else {
	while(b[tot].t>a[i].t){//条件：时间更大
	  ans[b[tot].t]=b[tot].y-a[i].y;//更新答案
	  tot--;//退栈
	}
	ans[a[i].t]=a[i].x-b[tot].x;//不能再退栈时，更新自己的答案
      }
    }
  while(tot){
    ans[b[tot].t]=b[tot].y;//将还在栈里的退出来
    tot--;
  }
  for(re i=1;i<=m;i++)print(ans[i]),putchar('\n');
  return 0;
}
```

---

## 作者：吹雪吹雪吹 (赞：1)

观察样例，发现格子被吃之后会被分割成这样几种形状：
```cpp
1. 跟原来长得一样
# # # # #
# # # # 
# # #
# #
#
-----------

2.1 比原来多出一块（前几行）：
# # # # #
# # # # #
# # # # #
# # # #
# # #
# #
#
-----------

2.2 比原来多出一块（前几列）：

# # # # # #
# # # # #
# # # #
# # #
-----------

3. 比原来多出两块：
# # # # # # #
# # # # # # #
# # # # # # #
# # # # # #
# # # # #
# # # #
# # #
-----------

4. 某些矩形，肯定不会再被吃到
```

这样一来，一块区域就可以用四个量来表示：左右边界，向上和向左延伸的长度

用set维护即可：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

int n, m, ans;

class Squares
{
public:
    int l, r;
    int len_l, len_u;
    Squares()
    {
        l = r = 0;
        len_l = len_u = 0;
    }
    Squares(int _l, int _r, int _len_l, int _len_u)
    {
        l = _l, r = _r;
        len_l = _len_l, len_u = _len_u;
    }
    bool operator < (const Squares &b)const
    {
        return r < b.r;
    }
} a, res, nxt;

set<Squares> s;
set<Squares>::iterator it;

inline int read()
{
    char ch = getchar();
    int ret = 0, f = 1;
    while (ch > '9' || ch < '0')
    {
        if (ch == '-')
            f = -f;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        ret = ret * 10 + ch - '0', ch = getchar();
    return ret * f;
}

int main()
{
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    n = read(), m = read();
    res = Squares(1, n, 0, 0);
    s.insert(res);
    while (m--)
    {
        int x = read(), y = read();
        char ch = getchar();
        while (ch != 'U' && ch != 'L')
            ch = getchar();
        a = Squares(x, x, 0, 0);
        it = s.lower_bound(a);
        if (it == s.end() || it->l > x || it->r < x)
        {
            printf("0\n");
            continue;
        }
        res = *it;
        s.erase(it);
        if (ch == 'U')
        {
            ans = res.r - x + 1 + res.len_u;
            printf("%d\n", ans);
            if (x != res.l)
            {
                nxt = Squares(res.l, x - 1, res.len_l, ans);
                s.insert(nxt);
            }
            if (x != res.r)
            {
                nxt = Squares(x + 1, res.r, 0, res.len_u);
                s.insert(nxt);
            }
        }
        else
        {
            ans = x - res.l + 1 + res.len_l;
            printf("%d\n", ans);
            if (x != res.l)
            {
                nxt = Squares(res.l, x - 1, res.len_l, 0);
                s.insert(nxt);
            }
            if (x != res.r)
            {
                nxt = Squares(x + 1, res.r, ans, res.len_u);
                s.insert(nxt);
            }
        }
    }
    return 0;
}
```

---

## 作者：Leasier (赞：1)

注意到这玩意本质上就是一个类似区间染色的东西，考虑用一棵 ODT 状物维护若干次操作后每个还可以填的块的情况。

注意到每个块都是阶梯状物，即：

- 左上角是一个坐标 $(x, y)$。
- 右下角会出现一些完整的阶梯，设其区间为 $[l, r]$。
- 不难发现所有 $[l, r]$ 不交。

现在我们就可以用四元组 $(l, r, x, y)$ 描述这个可以访问到的连续段。

初始我们放入一个连续段 $(1, n, 1, 1)$。每次操作时我们先找出一个最大的 $(l, r, x, y)$ 使得 $l \leq x_i \leq r$。此时我们分两种情况讨论：

1. 向左走

此时答案为 $x_i - x + 1$，放入 $(l, x_i - 1, x, y_i + 1), (x_i + 1, r, x, y)$。

2. 向上走

此时答案为 $y_i - y + 1$，放入 $(l, x_i - 1, x, y), (x_i + 1, r, x_i + 1, y)$。

set 维护即可。时间复杂度为 $O(q \log q)$。

代码：
```cpp
#include <iostream>
#include <set>
#include <cstdio>

using namespace std;

typedef struct Node_tag {
	int l;
	int r;
	int x;
	int y;
	Node_tag(){}
	Node_tag(int l_, int r_, int x_, int y_){
		l = l_;
		r = r_;
		x = x_;
		y = y_;
	}
} Node;

char op[7];
set<Node> s;

bool operator <(const Node a, const Node b){
	if (a.l != b.l) return a.l < b.l;
	if (a.r != b.r) return a.r < b.r;
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

inline void insert(Node x){
	if (x.l <= x.r) s.insert(x);
}

int main(){
	int n, q;
	scanf("%d %d", &n, &q);
	s.insert(Node(1, n, 1, 1));
	for (int i = 1; i <= q; i++){
		int x, y, ans;
		scanf("%d %d %s", &x, &y, &op[1]);
		if (s.empty()){
			ans = 0;
		} else {
			set<Node>::iterator it = --s.upper_bound(Node(x, 0x7fffffff, 0, 0));
			if (it == s.end()){
				ans = 0;
			} else {
				Node cur = *it;
				if (cur.l <= x && x <= cur.r){
					s.erase(cur);
					if (op[1] == 'L'){
						ans = x - cur.x + 1;
						insert(Node(cur.l, x - 1, cur.x, y + 1));
						insert(Node(x + 1, cur.r, cur.x, cur.y));
					} else {
						ans = y - cur.y + 1;
						insert(Node(cur.l, x - 1, cur.x, cur.y));
						insert(Node(x + 1, cur.r, x + 1, cur.y));
					}
				} else {
					ans = 0;
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF555C)
## 思路
动态开点线段树入门题。

首先，这个题显然需要线段树做，用线段树来维护每个行和列最右边/最下边能连续吃的点。每吃一次修改一下即可。

但是 $n \le 10^9$，用传统的线段树来做空间爆炸，大约需要 $4 \times 10^9$ 的空间，所以我们选择动态开点。

动态开点的原理就是每次线段树修改的时候至多访问 $2 \times \log n$ 个点，所以我们只需要记录共 $n \log n$ 个点即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=1e7+5e6+10;
#define lls long long
unordered_map< int,unordered_map<int,int> >map1,map2;//map 用来记录这个点是否被吃过
int cnt=1;
struct node{int l,r,x;};
struct Segment_Tree{
	#define mid ((l+r)>>1)
	node c[N];int lazy[N];
	inline void pushdown(int x){
		if (!c[x].l) c[x].l=++cnt;//左儿子没有，开一个新点
		if (!c[x].r) c[x].r=++cnt;//右儿子没有，开一个新点
		c[c[x].l].x=max(c[c[x].l].x,lazy[x]);
		c[c[x].r].x=max(c[c[x].r].x,lazy[x]);
		lazy[c[x].l]=max(lazy[c[x].l],lazy[x]);
		lazy[c[x].r]=max(lazy[c[x].r],lazy[x]);
		lazy[x]=0;
	}
	inline void update(int x,lls l,lls r,lls ll,lls rr,int v){
		if (ll<=l && r<=rr){c[x].x=max(c[x].x,v);lazy[x]=max(lazy[x],v);return;}
		pushdown(x);
		if (ll<=mid){
			if (!c[x].l) c[x].l=++cnt;
			update(c[x].l,l,mid,ll,rr,v);
			c[x].x=max(c[x].x,c[c[x].l].x);
		}
		if (mid<rr){
			if (!c[x].r) c[x].r=++cnt;
			update(c[x].r,mid+1,r,ll,rr,v);
			c[x].x=max(c[x].x,c[c[x].r].x);
		}
	}
	inline int query(int x,lls l,lls r,int k){
		if (l==r) return c[x].x;
		pushdown(x);
		if (k<=mid){
			if (c[x].l) return query(c[x].l,l,mid,k);
			else return 0;
		}
		else{
		 	if (c[x].r) return query(c[x].r,mid+1,r,k);
			else return 0;
		}
	}
}T;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    lls n,q;cin>>n>>q;
    while (q--){
    	int x,y;cin>>x>>y;int z;swap(x,y);
    	char opt;cin>>opt;
    	if (opt=='U'){
    		if (map1[x][y]){cout<<"0\n";continue;}
    		map1[x][y]=1;
			z=x-T.query(1,1,2*n,y);
			cout<<z<<'\n';if (!z) continue;
			T.update(1,1,2*n,x-z+1+n,x+n,y);
		}else{
			if (map2[x][y]){cout<<"0\n";continue;}
    		map2[x][y]=1;
			z=y-T.query(1,1,2*n,x+n);
			cout<<z<<'\n';if (!z) continue;
			T.update(1,1,2*n,y-z+1,y,x);
		}
	}
	return 0;
}
```


---

## 作者：逃课小姐MS (赞：0)

看到没有人用map来写 那本**蒟蒻**来写一个

map的思路其实简单粗暴：

我们看一下样例图片：

![lg](https://cdn.luogu.com.cn/upload/vjudge_pic/CF555C/68417759be7789b5dc33e557d3b01b391502988d.png)

- ### 纵向操作

现在盯牢右边那个图的3号操作看，你会发现，3号操作与1号操作所可以到达的高度一样。

再盯牢6号操作看，又会发现，6号收到横着过来的4号操作的限制，只能在4号说横向过来的高度之下。

然后，你会惊奇的发现，每一次限制一次纵向操作吃掉巧克力的点，其实在它上面的一个位置最接近它的操作，无论是什么操作。如果限制它的是一个横向操作，那么他的最高能到达的地方为其之下的一格；如果为纵向操作，那么他的最高能到达的地方就与它一样高。

证明作者就口胡了qwq 其实这一个很好证明的，可以说是基本不需要证明。（时间紧张就别看了

![lg](https://s2.ax1x.com/2019/06/23/ZCusJI.png)

看这些操作（编号不是顺序 只是作者方便讲一点）

如果一次纵向操作的上面还是纵向操作，那么就成了一个类似递归的过程。纵向操作不断地寻找横向操作，比如2->3，3->4,然后发现4是一个横向操作，3的高度就定了，然后2也随之定了。那么我们简化这个过程，直接让2去继承3的高度，也未尝不可。

那如果是横向操作，那就直接定了，因为一个横向操作上面的横向操作绝对会笔下面的那个要高一些（跳步证明qwq）

- ### 横向操作

这个我不多讲了 你把图片转个90°，这就跟纵向操作一模一样了。

- ### 简述一下大体框架

1.定义两个map，分别代表l，u（向左和向上，left＆up）

2.每一次找到一个操作上面的最近的一次操作（lower_bound）,进行操作

3.别忘了特判一个巧克力也吃不到的情况

代码不写注释了见谅qwq

应该好理解的~

```cpp
#include<bits/stdc++.h>
#define iter map<int,int>::iterator it
#define lb lower_bound
using namespace std;
map<int,int> l,u;
int n,q,ans,x,y;
char opt;
void up(){
    ans=0;
    iter=u.lb(x);

    if(it==u.end()) ans=y;
    else ans=y-(it->second);

    printf("%d\n",ans);

    l[y]=x,u[x]=y-ans;
}
void left(){
    ans=0;
    iter=l.lb(y);

    if(it==l.end()) ans=x;
    else ans=x-(it->second);

    printf("%d\n",ans);

    l[y]=x-ans,u[x]=y;
}
void read(){scanf("%d%d",&x,&y),cin>>opt;}
void out(){puts("0");return;}
int main(){
    while(scanf("%d%d",&n,&q)!=EOF){
        l.clear(),u.clear();
        while(q--){
            read();
            if(opt=='U') u.count(x)?out():up();
            else l.count(y)?out():left();
        }
    }
    return 0;
}
```

---

