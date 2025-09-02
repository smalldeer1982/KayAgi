# [POI 2001] Goldmine

## 题目描述

$\text{Byteman}$ 作为 $\text{Byteland}$ 的 $\text{The Goldmine}$（某一公司厂矿）的最有功的雇员之一，即将在年末退休。

为了表示对他的认真勤恳的工作的承认，$\text{The Goldmine}$ 的管理层愿意奖励他一小块长方形的矿地，此矿地长和宽为 $s$  和 $w$ ，且平行于坐标系统的轴线。长方形矿地的位置可由他自己选。当然，这块地的价值会随着位置的不同而不同。其价值是指这块区域内天然金矿石的数量（若矿石位于这块地的边缘，我们同样认为他是属于这个区域的）。

你们的任务是计算出这块地的最大可能价值（即：为它选择最佳位置）。为简便起见，我们假定整个金矿的矿区是无穷的，但含有天然金矿石的区域却是有限的。

请你编写一个程序：

1. 读入天然金矿石的位置。

2. 计算这块地的最大可能价值（即：求给定大小的这块地所含的天然金矿石的最大数）。

## 说明/提示

对于 $100$ % 的数据：$1 \le s,w \le 10000,1 \le n \le 15000,-30000 \le x,y \le 30000$ 。

## 样例 #1

### 输入

```
1 2
12
0 0
1 1
2 2
3 3
4 5
5 5
4 2
1 4
0 5
5 0
2 3
3 2```

### 输出

```
4```

# 题解

## 作者：Swiftie_wyc22 (赞：5)

这道题其实很考思维的转换。

需要考虑如何将平面转换为线段，从而使用线段树？

线段树的基本操作就不讲了，可以去网上搜，再做做模板题。[板子](https://whitesails.blog.luogu.org/mu-ban-xian-duan-shu)

---

思路是这样的：

枚举 $x$ 轴，类似固定长度的滑动窗口，左点是 $i$，右点则是 $i+s$

![](https://cdn.luogu.com.cn/upload/image_hosting/kq4j0tox.png)

我们可以忽略高度，将这个图化为一维：

![](https://cdn.luogu.com.cn/upload/image_hosting/319uz4g3.png)

这个窗口（$i$ 下标）从 $-30000$ 开始移动，移动到 $30000-s$ 

我们只需要看的是窗口内的点数，则必然会有去除和加入的操作。去除和加入的操作也需要左右变量来实现。

这样枚举完，只需要算每一次 $i+1$ 更新之后覆盖的最大值就可以！

那么问题来了，区间的覆盖最大值怎么算呢？那很显然，用线段树嘛。

这个树，则需要建在 $y$ 轴上！

![](https://cdn.luogu.com.cn/upload/image_hosting/gjanx0yr.png)

图中两条蓝色竖线即线段树的有效保留位置。在蓝色区间内的这些点，每个点的 $y$ 到 $y+w$ 都是有效覆盖范围，只需要将这些线段在线段树上 加一。然后我圈起来的那条线段，已经不在蓝色区间内，所以需要去除，则在线段树上把那条线段 减一！这种区间修改，需要懒操作。不会的要学学。

以上的操作称为一次更新吧，一次更新会出现一个最大值，我们只需要求每一次更新最后的最大值，就是最大覆盖数！因为有重叠的线段会重复覆盖，比如两条线段有一个覆盖部分，那么这两条线段的最大值都是 2。嗯大概就是这个意思（解释不清楚，逃）

这道题不需要离散化，如果数据量足够大，比如P1502，就需要离散化缩小空间。

代码就来了：

```cpp
#include <iostream>
#include <algorithm>

using namespace std;
#define MAXN 60000
#define LL long long
const int Delta = 30001;

struct Tree
{
    int l, r;
    LL maxv;
    LL tag;
};
Tree tree[4 * MAXN];
pair<int, int> a[15000];
int s, w, n;
void build(int p, int l, int r)
{
    tree[p].l = l;
    tree[p].r = r;
    tree[p].tag = 0;
    if (l == r)
    {
        tree[p].maxv = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    tree[p].maxv = max(tree[2 * p].maxv, tree[2 * p + 1].maxv);
}
void pushdown(int p)
{
    int l = 2 * p, r = 2 * p + 1;
    if (tree[p].tag != 0)
    {
        tree[l].tag += tree[p].tag;
        tree[l].maxv += tree[p].tag;
        tree[r].tag += tree[p].tag;
        tree[r].maxv += tree[p].tag;
        tree[p].tag = 0;
    }
}
void update(int p, int l, int r, LL v)
{
    if (l <= tree[p].l && tree[p].r <= r)
    {
        tree[p].tag += v;
        tree[p].maxv += v;
        return;
    }
    pushdown(p);
    int mid = (tree[p].l + tree[p].r) / 2;
    if (l <= mid)
        update(2 * p, l, r, v);
    if (r >= mid + 1)
        update(2 * p + 1, l, r, v);
    tree[p].maxv = max(tree[2 * p].maxv, tree[2 * p + 1].maxv);
}
LL ask(int p, int l, int r)
{
    if (l <= tree[p].l && tree[p].r <= r)
        return tree[p].maxv;
    pushdown(p);
    int mid = (tree[p].l + tree[p].r) / 2;
    LL ret = 0;
    if (l <= mid)
        ret = max(ret, ask(2 * p, l, r));
    if (r >= mid + 1)
        ret = max(ret, ask(2 * p + 1, l, r));
    return ret;
}
int main()
{
    cin >> s >> w;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].first >> a[i].second;
    }
    build(1, -30000 + Delta, 30000 + Delta);
    sort(a, a + n, cmp); // sorting of pair array is accord '.first' from small to big
    int l = 0, r = -1;
    int ans = 0;
    for (int x = -30000; x <= 30000; x++)
    {
        int xx = x + s;
        while (l < n && a[l].first < x)
        {
            update(1, a[l].second + Delta, a[l].second + w + Delta, -1);
            l++;
        }
        while (r + 1 < n && a[r + 1].first <= xx)
        {
            update(1, a[r + 1].second + Delta, a[r + 1].second + w + Delta, 1);
            r++;
        }
        int tmp = tree[1].maxv;
        ans = max(ans, tmp);
        // cout << "ok" << x << " ";
    }
    printf("%d\n", ans);
    return 0;
}
```


---

## 作者：iyaang (赞：4)

# 【POI2001】Goldmine

[题目链接](https://www.luogu.com.cn/problem/P8370)

扫描线板子题，本质上这个题跟[窗口的星星](https://www.luogu.com.cn/problem/P1502)是一样的，只不过把权值 $k$ 都换成 $1$ 就行。但是需要注意的是这句话：

`（若矿石位于这块地的边缘，我们同样认为他是属于这个区域的）`

因此我们在处理矩形的时候就不需要进行缩小的操作。剩下的就都一样了，这个题 $x$ 和 $y$ 的范围到负数，我们可以先离散化一下，然后将每个“金矿”转化成矩形，排序横坐标，对纵坐标建立扫描线。

这边题解不一样的地方是扫描线使用分块维护，因为我们需要支持的操作包括区间加和区间最大值，分块同样可以做到，不一定非要用线段树。维护整块 $tag$ 加法标记，原始序列 $c$ 和整块 $maxx$ 数组，在整块直接取 $maxx$ 中的值，散块暴力找即可。

~~大常数选手跑得奇慢无比，喜提最劣解。~~

$Code$
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAX 100010
using namespace std;

inline int read()
{
	int s=0,w=1;
	char c=getchar();
	while(!isdigit(c)) {if(c=='-') w=-1;c=getchar();}
	while(isdigit(c)) s=(s<<1)+(s<<3)+(c^48),c=getchar();
	return s*w;
}

int n,w,h;
int ans,cnt;

struct scanline
{
	int x,yup,ydown,k;
}a[MAX<<1];
inline bool cmp(scanline a,scanline b)
{
	if (a.x!=b.x) return a.x<b.x;
	else return a.k>b.k;
}

int d[MAX<<1];
int x,y;
inline void discrete()
{
	w=read(),h=read();
	n=read();
	for(int i=1;i<=n;i++)
	{
		x=read(),y=read();
		a[++cnt].x=x,a[cnt].yup=y+h,a[cnt].ydown=y,a[cnt].k=1; d[cnt]=y;
		a[++cnt].x=x+w,a[cnt].yup=y+h,a[cnt].ydown=y,a[cnt].k=-1; d[cnt]=y+h;
	}
	sort(d+1,d+cnt+1);
	cnt=unique(d+1,d+cnt+1)-d-1;
	n<<=1;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
		a[i].yup=lower_bound(d+1,d+cnt+1,a[i].yup)-d,
		a[i].ydown=lower_bound(d+1,d+cnt+1,a[i].ydown)-d;
	return;
}

int blo,bn;
int l[MAX],r[MAX],pos[MAX],c[MAX],tag[MAX],maxx[MAX];
inline void block()
{
	blo=sqrt(cnt),bn=(cnt-1)/blo+1;
	for(int i=1;i<=bn;i++)
		l[i]=(i-1)*blo+1,r[i]=blo*i;
	r[bn]=cnt;
	for(int i=1;i<=bn;i++)
		for(int j=l[i];j<=r[i];j++)
			pos[j]=i;
	return;
}
inline void check(int x)
{
	maxx[x]=0;
	for(int i=l[x];i<=r[x];i++)
		maxx[x]=max(maxx[x],c[i]);
	return;
}
inline void add(int L,int R,int k)
{
	int p=pos[L],q=pos[R];
	if(p==q)
	{
		for(int i=L;i<=R;i++)
			c[i]+=k,maxx[p]=max(maxx[p],c[i]);		
		if(k==-1) check(p);
	}
	else
	{
		for(int i=p+1;i<=q-1;i++)
			tag[i]+=k;
		for(int i=L;i<=r[p];i++)
			c[i]+=k,maxx[p]=max(maxx[p],c[i]);
		if(k==-1) check(p);
		for(int i=l[q];i<=R;i++)
			c[i]+=k,maxx[q]=max(maxx[q],c[i]);
		if(k==-1) check(q);
	}
	return;
}
inline int getmax(int L,int R)
{
	int p=pos[L],q=pos[R],anss=0;
	if(p==q)
	{
		for(int i=L;i<=R;i++)
			anss=max(anss,c[i]+tag[q]);
	}
	else
	{
		for(int i=p+1;i<=q-1;i++)
			anss=max(anss,maxx[i]+tag[i]);
		for(int i=L;i<=r[p];i++)
			anss=max(anss,c[i]+tag[p]);
		for(int i=l[q];i<=R;i++)
			anss=max(anss,c[i]+tag[q]);
	}
	return anss;
}

signed main()
{
	discrete();
	block();
	for(int i=1;i<=n;i++)
	{
		add(a[i].ydown,a[i].yup,a[i].k);
		ans=max(ans,getmax(1,cnt));
	}
	cout<<ans<<endl;
	return (0-0);
}
```

---

## 作者：Hurraciny (赞：1)

# 做这道题你需要什么

- [一个洛谷账号](https://www.luogu.com.cn/auth/login)
- [扫描线](https://oi-wiki.org/geometry/scanning/)
- [线段树](https://www.luogu.com.cn/problem/P3372)
- 离散化 & 排序

# 思路 & 做法

设想我们如果直接枚举每个矩阵，然后算它们内的点的个数，那就毫无怀疑的会很复杂，更为重要的是，会非常的慢～～～

于是，我们可以将给出的点进行处理。首先，对于 $y$ 轴，非常明显它只能在离它 $h$ 的范围内有效，因此我们在这个点往上 $h$ 个单位的地方再加一个点，这两个点构成一个区间，就是可能包含这个点的一个 $y$ 区间。接着，对于 $x$，同样的这可能在距其 $w$ 个单位范围内，因此在 $w$ 个单位后，需要把这个区间删去。

自此，一个关于点的问题就变成了关于很多个区间加上又删，删了又加上的问题了。非常好想到的数据结构当然是线段树。

把这些加入和删除区间的操作排序，在一一访问并实行，改变线段树的同时更新答案为整个线段树中值的最大值。

# Code（别看我离散化？）

```cpp
#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int N = 1e5+21;
int n, h, w;
int lim;
class Segment_Tree{ // 区间加 + 区间Max
private:
    int tree[N<<2];
    int tag[N<<2];
    inline int lchild(int x){return x<<1;}
    inline int rchild(int x){return x<<1|1;}
    inline void push_up(int x){
        tree[x] = max(tree[lchild(x)], tree[rchild(x)]);
    }
    inline void add_tag(int x, int v){
        tree[x] += v;
        tag[x] += v;
    }
    inline void push_down(int p){
        if(tag[p]){
            add_tag(lchild(p), tag[p]);
            add_tag(rchild(p), tag[p]);
            tag[p] = 0;
        }
    }
    inline void modify(int p, int pl, int pr, int l, int r, int v){
        if(l <= pl && pr <= r){
            add_tag(p, v);
            return;
        }
        push_down(p);
        int mid = (pl+pr) >> 1;
        if(l <= mid)
            modify(lchild(p), pl, mid, l, r, v);
        if(mid < r)
            modify(rchild(p), mid+1, pr, l, r, v);
        push_up(p);
        return;
    }
public:
    inline void modify(int l, int r, int v){
        modify(1, 1, lim, l, r, v);
        return;
    }
    inline int query(){
        return tree[1];
    }
};
Segment_Tree tree;
typedef struct Node{
    int l, r;
    int x;  //x用于排序（其他基本上不需要）
    int v;
    Node(int l, int r, int x, int v) : l(l), r(r), x(x), v(v) {}
    friend bool operator < (Node a, Node b){
        if(a.x != b.x)
            return a.x < b.x;
        return a.v < b.v;
    }
}Node;
vector<Node>v;
map<int, int>mp;
int main(){
    cin >> w >> h;
    cin >> n;
    for(int i = 1; i <= n; i++){
        int x, y;
        cin >> x >> y;
        v.push_back(Node(y, y+h, x, 1));
        v.push_back(Node(y, y+h, x+w+1, -1));
        mp[y] = mp[y+h] = 1;
    }
    sort(v.begin(), v.end());
    //=======一坨离散化突然出现=======
    lim = 0;
    for(auto &[x, y] : mp)
        y = ++lim;
    for(auto &i : v)
        i.l = mp[i.l], i.r = mp[i.r];
    //=============================
    int ans = 0;
    for(auto i : v){
        tree.modify(i.l, i.r, i.v);
        ans = max(ans, tree.query());
    }
    cout << ans << endl;
    return 0;
}

```

---

## 作者：封禁用户 (赞：1)

### 题意
有 $n$ 个点在二维平面上，问长度为 $s$，宽度为 $w$ 的矩形最多能覆盖多少个点。

### 思路
![](https://cdn.luogu.com.cn/upload/image_hosting/bjf73nym.png)

如图，当矩形左下角为 $(2,2)$，右上角为 $(3,4)$ 时为最大价值 $4$。

我们对于二维矩阵，用的方法基本是二维前缀和，发现预处理为 $O(n^2)$，空间也是 $O(n^2)$，这题给的点横纵坐标的上界都为 $10^5$，因此我们需另辟蹊径。

发现前缀和的复杂度过高是由于支持 $O(1)$ 查询，并且在线。于是，我们可以减低询问的性能，来降低时间和空间的消耗。

首先我们需要发现一个性质：一个点对一个矩形有贡献，必要条件为矩形的左下角与这个点的横坐标之差小于等于 $s$，纵坐标之差小于等于 $w$。

设贡献点坐标为 $(x,y)$，矩形左下角为 $(a,b)$，则有：
$$
0 \le x-a \le w\\
0 \le y-b \le s
$$
可得此点作用在：
$$
x-w \le a \le x\\
y-b \le b \le y
$$
于是我们用一个左下角来映射一个矩形，用算法和数据结构来维护。

我们发现区间更新，我们有优秀的差分算法，$O(1)$ 复杂度插入，处理 $O(n)$，询问为 $O(1)$。

但是还有一维区间更新，扛出我们 $\log$ 阶的线段树，总复杂度为 $O(n \log n)$，空间 $O(n \log n)$。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define M 100005
void Max(int &a,int b){if(a<b)a=b;}
int n,S,W,tot;
struct seg{
	struct node {
		int l,r,mx,add;
		void Add(int d){
			mx+=d;
			add+=d;
		}
	}tree[M<<2];
	void down(int p){
		if(tree[p].add==0)return;
		tree[p<<1].Add(tree[p].add);
		tree[p<<1|1].Add(tree[p].add);
		tree[p].add=0;
		return;
	}
	void up(int p){
		tree[p].mx=max(tree[p<<1].mx,tree[p<<1|1].mx);
		return;
	}
	void build(int l,int r,int p){
		tree[p].l=l,tree[p].r=r,tree[p].mx=0;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
	}
	void update(int d,int l,int r,int p){
		if(tree[p].l==l&&tree[p].r==r){
			tree[p].Add(d);
			return;
		}
		down(p);
		int mid=(tree[p].l+tree[p].r)>>1;
		if(r<=mid)update(d,l,r,p<<1);
		else if(l>mid)update(d,l,r,p<<1|1);
		else update(d,l,mid,p<<1),update(d,mid+1,r,p<<1|1);
		up(p);
	}
	int query(int l,int r,int p){
		if(tree[p].l==l&&tree[p].r==r)return tree[p].mx;
		down(p);
		int mid=(tree[p].l+tree[p].r)>>1;
		if(r<=mid)return query(l,r,p<<1);
		else if(l>mid)return query(l,r,p<<1|1);
		else return max(query(l,mid,p<<1),query(mid+1,r,p<<1|1));	
	}
}Tr;
struct node{
	int tim,L,R,add;
	bool operator < (const node &A)const{
		return tim<A.tim;
	}
}Q[M<<1];
int main(){
	scanf("%d %d %d",&n,&S,&W);
	for(int i=1;i<=n;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		Q[++tot]=(node){max(0,a-S),max(0,b-W),b,1};
		Q[++tot]=(node){a+1,max(0,b-W),b,-1};
	}	
	sort(Q+1,Q+1+tot);
	Tr.build(0,M-5,1);
	int l=1,ans=0;
	for(int i=0;i<=M-5;i++){
		while(l<=tot&&Q[l].tim<=i){
			Tr.update(Q[l].add,Q[l].L,Q[l].R,1);
			l++;
		}
		Max(ans,Tr.query(0,M-5,1));
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：xnmzyz (赞：0)

# [P8370 [POI 2001] Goldmine ](https://www.luogu.com.cn/problem/P8370)题解
比较简单的扫描线题。

---------
## 前置芝士

[扫描线](https://oi-wiki.org/geometry/scanning/)、[线段数](https://oi-wiki.org/ds/seg/)~~、[离散化](https://oi-wiki.org/misc/discrete/)（？）~~。

----

## 题目大意

给定平面上的 $n$ 个点坐标 $(x_i, y_i)$ 和矩形尺寸 $s \times w$，求该矩形能覆盖点数的最大值。矩形边平行于坐标轴，点在矩形边上也算被覆盖。

----

## 算法思路
### 扫描线算法
将每个点视为一个矩形区域的起点和终点，转化为事件处理：
每个矿石 $(x, y)$ 生成两个事件：
   - **左事件**：当矩形左边界到达 $x-s$ 时，覆盖区间 $[y-w, y]$ 。
   - **右事件**：当矩形右边界到达 $x$ 时，移除该区间。

示意图
```
矿石点(x, y) → 影响区间[x-s, x] × [y-w, y]
       ↑右事件          ↑左事件
```   
由于数据规模较大，我们还要使用线段树加速以及离散化节约空间（其实可以不用，但是精益求精嘛，这就是为什么有点提交记录用了 10MB 空间而有点只用了 4MB ）。

要注意的点：

  - 一个点对应两个事件，一个事件对应两个 y 坐标，线段树本身要开 $4$ 倍空间，所以 tree 数组要开到 $n_{max} \times 16$ 。
  - 先处理左事件（先加再减）防止提前减少覆盖数（如果边界上的点不算就要先减再加）。所以可以按照 x 坐标排序。

## code
```cpp
#include<bits/stdc++.h>
#ifdef _WIN32
#define gc(c) getchar(c)
#else
#define gc(c) getchar_unlocked(c)
#endif
#define isd(c) (c>='0'&&c<='9')
#define For(i,a,b) for(auto i=(a);i<=(b);i++)
#define ls (node<<1)
#define rs (node<<1|1)
using namespace std;

namespace temp{
template<class T>void read(T &n){
    n=0;char c=gc();int k=1;
    while(!isd(c)){if(c=='-')k*=-1;c=gc();}
    while(isd(c))n=n*10+c-'0',c=gc();
    n*=k;
}
template<class T>void write(T n){
    if(n<0)n=-n,putchar('-');
    if(n>9)write(n/10);
    putchar(n%10+'0');
}
}

namespace Main{
using namespace temp;

const int MAXN=15005;

struct event {
    int x, type;// 事件发生x坐标 事件类型(0:添加区域,1:移除区域)
    int y_low, y_high;//原始y轴下界y-w 原始y轴上界y
    int dl, dr;  //离散化后的上下界索引
    
    bool operator<(const event&oth){
        return x != oth.x ? x < oth.x : type < oth.type;
    }//按 x 坐标排序
};

event evt[MAXN<<1];// 事件数组（每个矿石生成两个事件）
int ys[MAXN<<2], tot;// 离散化坐标数组及计数器

struct sgt {
    int l,r;    
    int add,maxv;
} tree[MAXN<<4]; // 2个事件*2个y坐标*4倍空间线段树

void push_down(int node) {
    if (tree[node].add && tree[node].l < tree[node].r) {
        tree[ls].add+=tree[node].add;
        tree[ls].maxv+=tree[node].add;
        tree[rs].add+=tree[node].add;
        tree[rs].maxv+=tree[node].add;
        
        tree[node].add=0;
    }
}

void build(int node,int l,int r) {
    tree[node].l=l;
    tree[node].r=r;
    tree[node].add=tree[node].maxv=0;
    if (l==r) return;
    
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}

void update(int node,int l,int r,int val){
    if(r<tree[node].l||l>tree[node].r)return;
    if(l<=tree[node].l&&tree[node].r<=r){
        tree[node].add+=val;
        tree[node].maxv+=val;
        return;
    }
    
    push_down(node);
    update(ls,l,r,val);
    update(rs,l,r,val);
    tree[node].maxv=max(tree[ls].maxv,tree[rs].maxv)+tree[node].add;
}

int s,w,n,x,y;
int cnt,ans;
void Main(){
    read(s),read(w),read(n);
    
    For(i,1,n) {
        read(x),read(y);
        evt[cnt++]={x-s,0,y-w,y};
        // 生成左事件（矩形进入）：x-s坐标，类型0
        evt[cnt++]={x,1,y-w,y};
        // 生成右事件（矩形离开）：x坐标，类型1
        ys[tot++]=y-w;
        ys[tot++]=y;
        // 离散化
    }
    
    sort(ys, ys+tot);
    tot=unique(ys, ys+tot)-ys;// 去重
    
    // 离散化
    For(i,0,cnt-1)
        evt[i].dl=lower_bound(ys, ys+tot,evt[i].y_low)-ys,    // 下界对应索引
        evt[i].dr=upper_bound(ys, ys+tot,evt[i].y_high)-ys -1;// 上界对应索引
    
    sort(evt,evt+cnt);
    build(1,0,tot-1);
    
    For(i,0,cnt-1) {
        if(evt[i].dl>evt[i].dr) continue;
        update(1, evt[i].dl,evt[i].dr,evt[i].type ? -1 : 1);
        ans = max(ans, tree[1].maxv);
    }
    write(ans);
}
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Main::Main();
    return 0;
}
```
时间复杂度 $O(n \log n)$ (实际上主要是排序和离散化的时间复杂度)可以通过此题。

[record](https://www.luogu.com.cn/record/218563725)

---

## 作者：__stick (赞：0)

# 题意
平面上有 $n$ 个点，给出一个矩形，问最多能覆盖多少个点。

其实这个题洛谷上有个差不多的： [窗口的星星](https://www.luogu.com.cn/problem/P1502)，但我还是厚颜无耻的写了题解。

# 思路
和那个题一样，使用扫描线来做，我们将一个金矿理解为一个长为 $s $ ，宽为 $w$ ,左下角为金矿所在点的矩形，那问题就转化为了平面上矩形堆叠最多的层数是多少，然后就是经典扫描线问题了，如果不会可以去那个题题解去学习。

我们将一个矩形拆为两条线段，分别对应矩形的下边和上边，我们维护一条扫描线，从下向上扫描，遇到一条下边，我们就将下边对应的区间整体加一，表示现在这里有一层矩形覆盖；而遇到了上边，就整体减一，表示当前矩形已经不能覆盖到这些点了，而线段树里面只需要维护一个区间最大值，表示扫描线上最多的覆盖层数，在每次更新的时候取最值就可以了。

# 代码

比较丑，凑合着看看。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
#define lsh(x) (lower_bound(d.begin(),d.end(),x)-d.begin())
typedef long long ll;
const int MAXN=1e6+10;
ll mmax[MAXN],add[MAXN];
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
void bt(int p,int l,int r)
{
	mmax[p]=add[p]=0;
	if(l==r)return;
	bt(ls,l,mid),bt(rs,mid+1,r);
}
inline void push_up(int p){mmax[p]=max(mmax[ls],mmax[rs]);}
inline void ADD(int p,ll k){mmax[p]+=k,add[p]+=k;}
inline void push_down(int p){if(add[p])ADD(ls,add[p]),ADD(rs,add[p]),add[p]=0;}
inline void update(int p,int ql,int qr,int l,int r,ll k)
{
	if(ql<=l&&r<=qr)return ADD(p,k);
	push_down(p);
	if(ql<=mid)update(ls,ql,qr,l,mid,k);
	if(qr>mid)update(rs,ql,qr,mid+1,r,k);
	push_up(p);
}
struct node{int x,l,r,w;};
inline bool operator<(const node& a,const node& b){return a.x<b.x||a.x==b.x&&a.w>b.w;}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	int n,w,h,x,y,l;cin>>w>>h>>n;
	vector<int>d;vector<node>v;d.push_back(0);
	for(int i=1;i<=n;i++)cin>>x>>y,
	d.push_back(y),d.push_back(y+h),v.push_back((node){x,y,y+h,1}),v.push_back((node){x+w,y,y+h,-1});
	sort(d.begin(),d.end()),d.erase(unique(d.begin(),d.end()),d.end());
	ll ans=0;bt(1,1,n*2);sort(v.begin(),v.end());
	for(const node& p:v)update(1,lsh(p.l),lsh(p.r),1,n<<1,p.w),ans=max(ans,mmax[1]);
	cout<<ans<<'\n';
	return 0;
}
```


---

