# [Violet] 天使玩偶/SJY摆棋子

## 题目描述


Ayu 在七年前曾经收到过一个天使玩偶，当时她把它当作时间囊埋在了地下。而七年后 的今天，Ayu 却忘了她把天使玩偶埋在了哪里，所以她决定仅凭一点模糊的记忆来寻找它。

我们把 Ayu 生活的小镇看作一个二维平面坐标系，而 Ayu 会不定时地记起可能在某个点 $(x, y)$ 埋下了天使玩偶；或者 Ayu 会询问你，假如她在 $(x,y)$，那么她离近的天使玩偶可能埋下的地方有多远。

因为 Ayu 只会沿着平行坐标轴的方向来行动，所以在这个问题里我们定义两个点之间的距离为 $\operatorname{dist}(A,B)=|A_x-B_x|+|A_y-B_y|$。其中 $A_x$ 表示点 $A$ 的横坐标，其余类似。


## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据 保证 $1 \leq n,m\leq 3 \times 10^5$，$0 \leq x_i,y_i \leq 10^6$。

## 样例 #1

### 输入

```
2 3 
1 1 
2 3 
2 1 2 
1 3 3 
2 4 2```

### 输出

```
1 
2```

# 题解

## 作者：Log_x (赞：66)

## Solution
- 丢一发 CDQ分治 的解法。
- 先考虑回忆出来的点都在询问的点左下方时：（$A$为询问的点）$$Dis(A, B) = |x_A - x_B| + |y_A - y_B| = (x_A + y_A) - (x_B + y_B)$$
- 则当 $x_B + y_B$ 取到最大值时，$Dis(A,B)$ 有最小值。
- 因此问题被转化为：对于一个询问 $(x, y)$，找到满足时间戳在其前且 $x_i \le x, y_i \le y$ 的点中 $x_i + y_i$ 的最大值。
- 这实际上就是三维偏序，用 CDQ分治 解决。
- 对于其它方位的点，只要把坐标统一进行变换即转变为和上面一样的问题。
- 时间复杂度 $O(n \log^2 n)$。
- 然后交上去发现狂T不止，于是在写代码的时候还要注意一些细节：
 - 只有对于右区间的询问，我们才把点加入到树状数组中，不是询问就不加，这里学习了下[dalao的姿势](http://blog.csdn.net/qq_21110267/article/details/44701469)。
 - 每次 CDQ分治 前，先把那些肯定不在所有询问点左下方的点剔除。
 - 每次都按时间戳重新排序很浪费时间，可把一开始的数组备份下来直接复制过去。
 - ~~把 lowbit(i) 用数组存下来竟然挂了~~
- 目前应该是洛谷用 CDQ分治 跑最快的。 
## Code

```cpp
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

using namespace std;

namespace inout
{
    const int S = 1 << 20;
    char frd[S], *ihed = frd + S;
    const char *ital = ihed;
    
    inline char inChar()
    {
        if (ihed == ital)
            fread(frd, 1, S, stdin), ihed = frd;
        return *ihed++;
    }
    
    inline int get()
    {
        char ch; int res = 0; bool flag = false;
        while (!isdigit(ch = inChar()) && ch != '-');
        (ch == '-' ? flag = true : res = ch ^ 48);
        while (isdigit(ch = inChar()))
            res = res * 10 + ch - 48;
        return flag ? -res : res;
    }
};
using namespace inout;

const int Maxn = 0x3f3f3f3f;
const int L = 1e6 + 5;
int n, m, lx, ly, rx, ry;
int c[L], Ans[L];

inline void CkMax(int &x, int y) {if (x < y) x = y;}
inline void CkMin(int &x, int y) {if (x > y) x = y;}

inline void Clear(int x)
{
    for (; x <= ly; x += x & -x)
        if (c[x]) c[x] = 0; 
            else break;
}

inline int Query(int x)
{
    int res = 0;
    for (; x; x ^= x & -x)
        CkMax(res, c[x]);
    return res;
}

inline void Modify(int x, int y)
{
    for (; x <= ly; x += x & -x) 
        CkMax(c[x], y);
}

struct Ask
{
    int x, y, t; bool f;
    
    Ask() {}
    Ask(const int &X, const int &Y, const int &T, const bool &F):
        x(X), y(Y), t(T), f(F) {}

    inline bool operator < (const Ask &a) const
    {
        return x <= a.x;
    }
}q[L], p[L], a[L];

inline void CDQsolve(int l, int r)
{
    if (l == r) return ;
    int mid = l + r >> 1;
    CDQsolve(l, mid); CDQsolve(mid + 1, r);
    
    int j = l;
    for (int i = mid + 1; i <= r; ++i)
    if (!p[i].f)
    {
        for (; j <= mid && p[j].x <= p[i].x; ++j) 
            if (p[j].f) Modify(p[j].y, p[j].x + p[j].y);
        int tmp = Query(p[i].y);
        if (tmp) CkMin(Ans[p[i].t], p[i].x + p[i].y - tmp);
    }
    for (int i = l; i < j; ++i)
        if (p[i].f) Clear(p[i].y);
    
    merge(p + l, p + mid + 1, p + mid + 1, p + r + 1, q + l);
    for (int i = l; i <= r; ++i) p[i] = q[i];
}

inline void Delete()
{
    rx = ry = m = 0;
    for (int i = 1; i <= n; ++i)
        if (!p[i].f) CkMax(rx, p[i].x), CkMax(ry, p[i].y);
    for (int i = 1; i <= n; ++i)
        if (p[i].x <= rx && p[i].y <= ry) q[++m] = p[i];
    for (int i = 1; i <= m; ++i) p[i] = q[i];
}

int main()
{
    n = get(); m = get(); int k, x, y;
    for (int i = 1; i <= n; ++i)
    {
        x = get() + 1; y = get() + 1;
        p[i] = Ask(x, y, i, true);
        CkMax(lx, x); CkMax(ly, y);
    }
    
    while (m--)
    {
        k = get(); x = get() + 1; y = get() + 1;
        ++n; p[n] = Ask(x, y, n, k & 1);
        CkMax(lx, x); CkMax(ly, y);
    }
    for (int i = 1; i <= n; ++i) a[i] = p[i];
    
    memset(Ans, Maxn, sizeof(Ans)); ++lx; ++ly;
    Delete(); CDQsolve(1, m);
    
    for (int i = 1; i <= n; ++i) 
        p[i] = a[i], p[i].x = lx - p[i].x;
    Delete(); CDQsolve(1, m); 
    
    for (int i = 1; i <= n; ++i)
        p[i] = a[i], p[i].y = ly - p[i].y;
    Delete(); CDQsolve(1, m);
    
    for (int i = 1; i <= n; ++i) 
        p[i] = a[i], p[i].x = lx - p[i].x, p[i].y = ly - p[i].y;
    Delete(); CDQsolve(1, m); 
     
    for (int i = 1; i <= n; ++i)
        if (!a[i].f) printf("%d\n", Ans[i]);
    return 0; 
} 
```

---

## 作者：litble (赞：49)

KD-Tree是一个好东西啊......KD-Tree是一种将K维空间里的点规整好的树结构,其实也不复杂,就是第一层按照第一维坐标分成左右两边,第二层再按照第二维坐标,第三再按第三维......当然,本题只有两个维度,这样的KD-Tree又称为2D-Tree 

这样在查询的时候,我们知道,由于我们按当前维度的大小将左右子树分开了,所以我们通过提取两棵子树里的点x坐标最大/最小值,y坐标最大/最小值,可以看作这些点处于两个不相交的矩形里.我们可以算出当前要查询的点到矩形的最短曼哈顿距离,与当前获得的答案比较,决定是否查找那棵子树,达到剪枝的目的.复杂度和带剪枝的搜索一样,是O(玄学)

而插入就按照每个维度往左右子树插就行......可是令人绝望的是,这样子插了若干次之后,可能原树就被退化成一个近似于链的东西了.这个时候,我们就要利用**替罪羊树**的思想,设一个$\alpha=0.75$,如果对于点$x$,$x$的左右子树中的任意一棵的大小大于了$x$子树大小乘以$\alpha$,说明原树已经非常不平衡了,需要将其还原成一个点的序列(这一过程被称为**拍扁**),然后重建一次.当然,你也可以根据你的心情对$\alpha$值做调整.

最后放出代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
    int q=0,w=1;char ch=' ';
    while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
    if(ch=='-') w=-1,ch=getchar();
    while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
    return q*w;
}
#define alph (0.75)
const int N=1000005;
struct point{int x[2];}p[N];
struct node{int mi[2],mx[2],ls,rs,sz;point tp;}tr[N];
int n,m,rt,cur,top,WD,ans,rub[N];
int operator < (point a,point b) {return a.x[WD]<b.x[WD];}
int newnode() {//建立新节点
	if(top) return rub[top--];
	else return ++cur;
}
void up(int k) {
	int l=tr[k].ls,r=tr[k].rs;
	for(int i=0;i<=1;++i) {
		tr[k].mi[i]=tr[k].mx[i]=tr[k].tp.x[i];
		if(l) tr[k].mi[i]=min(tr[k].mi[i],tr[l].mi[i]),tr[k].mx[i]=max(tr[k].mx[i],tr[l].mx[i]);
		if(r) tr[k].mi[i]=min(tr[k].mi[i],tr[r].mi[i]),tr[k].mx[i]=max(tr[k].mx[i],tr[r].mx[i]);
	}
	tr[k].sz=tr[l].sz+tr[r].sz+1;
}
int build(int l,int r,int wd) {
	if(l>r) return 0;
	int k=newnode(),mid=(l+r)>>1;
	WD=wd,nth_element(p+l,p+mid,p+r+1),tr[k].tp=p[mid];
    //nth_element:使得序列某一位置x(此处是p+mid)是该序列的第x大数
	tr[k].ls=build(l,mid-1,wd^1),tr[k].rs=build(mid+1,r,wd^1);
	up(k);return k;
}
void pia(int k,int num) {//拍扁
	if(tr[k].ls) pia(tr[k].ls,num);
	p[num+tr[tr[k].ls].sz+1]=tr[k].tp,rub[++top]=k;
	if(tr[k].rs) pia(tr[k].rs,num+tr[tr[k].ls].sz+1);
}
void check(int &k,int wd) {//检查子树是否不平衡
	if(alph*tr[k].sz<tr[tr[k].ls].sz||alph*tr[k].sz<tr[tr[k].rs].sz)
		pia(k,0),k=build(1,tr[k].sz,wd);
}
void ins(point tmp,int &k,int wd) {//插入
	if(!k) {k=newnode(),tr[k].tp=tmp,tr[k].ls=tr[k].rs=0,up(k);return;}
	if(tr[k].tp.x[wd]<tmp.x[wd]) ins(tmp,tr[k].rs,wd^1);
	else ins(tmp,tr[k].ls,wd^1);
	up(k),check(k,wd);//记得在check之前要先pushup
}
int getdis(point tmp,int k) {//获得当前点到矩形的曼哈顿距离
	int re=0;
	for(int i=0;i<=1;++i)
		re+=max(0,tmp.x[i]-tr[k].mx[i])+max(0,tr[k].mi[i]-tmp.x[i]);
	return re;
}
int dist(point a,point b) {return abs(a.x[0]-b.x[0])+abs(a.x[1]-b.x[1]);}
void query(point tmp,int k) {//查询
	ans=min(ans,dist(tmp,tr[k].tp));
	int dl=INT_MAX,dr=INT_MAX;
	if(tr[k].ls) dl=getdis(tmp,tr[k].ls);
	if(tr[k].rs) dr=getdis(tmp,tr[k].rs);
	if(dl<dr) {
		if(dl<ans) query(tmp,tr[k].ls);
		if(dr<ans) query(tmp,tr[k].rs);
	}
	else {
		if(dr<ans) query(tmp,tr[k].rs);
		if(dl<ans) query(tmp,tr[k].ls);
	}
}
int main() {
	int bj;
	n=read(),m=read();
	for(int i=1;i<=n;++i) p[i].x[0]=read(),p[i].x[1]=read();
	rt=build(1,n,0);
	while(m--) {
		point tmp;
		bj=read(),tmp.x[0]=read(),tmp.x[1]=read();
		if(bj==1) ins(tmp,rt,0);
		else ans=INT_MAX,query(tmp,rt),printf("%d\n",ans);
	}
    return 0;
}
```

---

## 作者：Mogeko (赞：48)

### $cdq$分治

#### 不知道什么是$cdq$分治？欢迎访问[我的博客](https://www.cnblogs.com/mogeko/p/10439209.html)

二维平面修改+查询，$cdq$可以解决。

求关于某个点曼哈顿距离（$x,y$坐标）最近的点——$dis(A,B) = |Ax-Bx|+|Ay-By|$

但是如何去掉绝对值呢？

假设所有的点都在查询点的左下方，$dis(A,B) = (Ax-Bx)+(Ay-By) = (Ax+Ay)-(Bx+By)$

只要求满足$Bx<Ax,By<Ay$ 且 $Bx,By$之和最大的点就好了。

那么如何把所有的点转化到该查询的左下呢？

对于每个查询，可以把一、二、四象限的点都通过对称转移到第三象限。但查询很多，不可能一个个翻转。

换个思路，如果把整个平面翻转三次，进行四次$cdq$分治，每次都只考虑左下的点，所有的点就都遍历到了！

记录最大的$x$或$y$值为边界$len$，每次沿$len$翻转。例如沿y轴翻转时，$x = len-x$

那么每个操作有三维——时间、$x$坐标、$y$坐标

时间在输入时已经排好了；$x$归并排序；$y$仿照[P3810 【模板】三维偏序（陌上花开）](https://www.luogu.org/problemnew/show/P3810)，用树状数组记录。

 

### 优化 & 注意

这道题坑点超级多...而且四次$cdq$分治会得到一个感人的复杂度，所以~~我选择吸氧~~

- $cdq$内的归并排序代替每次$sort$。
- 因为每次$cdq$完顺序会被打乱，如果重新按时间$O(nlogn)$排序，不如每次存入一个临时数组，然后$O(n)$直接复制过去。
- 但是$ans$需要存入初始的数组中，所以结构体需要一个$.id$来记录打乱前的时间，也就是原数组下标。赋值应该写$a[b[t2].id].ans$，而不是$a[t2].ans$。

- 并且，由于每次查询点的$x,y$也会更改，所以$ans$里不能直接存$max(Bx+By)$，而应该为$min((Ax+Ay)-(Bx+By))$。

- 如果某个点在坐标轴上，那么它的$x$或$y$为0。存入树状数组时，会因为$lowbit()==0$而陷入死循环。所以存入时，将$x,y$分别+1。
- 同样的，如果某个点在翻转边界$len$上，翻转时也会变为0。所以$len$也要++。
- 考虑这样一种情况：某一点非常靠近边界，导致某次翻转时，没有点在它的左下。这样查询时默认返回了0。当前的“原点”比实际上的点离该查询点更近，这样最终的距离就成了这个点到原点的距离，但原点是不存在的（经过刚刚的更改，已经没有$x$或$y$坐标为0的点）为避免这种情况，当查询时需要特判，若为0则返回$-INF$。

这道题的代码不难，但是细节特别多,写的时候要仔细一点qwq


```cpp
#include<cstdio>
#include<iostream>
#define MogeKo qwq
using namespace std;
const int maxn = 1e7+10;
const int INF = 2e7+10;
int n,q,opt,x,y,len;

int read() {
	int x = 0,f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9') {
		x = x*10 + ch-'0';
		ch = getchar();
	}
	return x*f;
}

struct node {
	int x,y,type,id,ans;
} a[maxn],b[maxn],tem[maxn];

struct BIT {
	int m[maxn];
	int lowbit(int x) {
		return x & -x;
	}
	void update(int x,int v) {
		for(; x <= len; x+= lowbit(x))
			m[x] = max(m[x],v);
	}
	int query(int x) {
		int ans = 0;
		for(; x; x-=lowbit(x))
			ans = max(ans,m[x]);
		return ans?ans:-INF;
	}
	void clear(int x) {
		for(; m[x]; x+= lowbit(x))
			m[x] = 0;
	}
} tree;

void cdq(int L,int R) {
	if(L == R) return;
	int mid = L+R >> 1;
	cdq(L,mid),cdq(mid+1,R);
	int t1 = L,t2 = mid+1;
	int k = L;
	while(t2 <= R) {
		while(t1 <= mid && b[t1].x <= b[t2].x) {
			if(b[t1].type == 1)
				tree.update(b[t1].y, b[t1].x+b[t1].y);
			tem[k++] = b[t1++];
		}
		if(b[t2].type == 2)
			a[b[t2].id].ans = min(a[b[t2].id].ans,b[t2].x+b[t2].y-tree.query(b[t2].y));
		tem[k++] = b[t2++];
	}
	for(int i = L; i <= t1-1; i++)
		if(b[i].type == 1) tree.clear(b[i].y);
	while(t1 <= mid) tem[k++] = b[t1++];
	for(int i = L; i <= R; i++) b[i] = tem[i];
}

void solve(int rx,int ry) {
	for(int i = 1; i <= n+q; i++) {
		b[i] = a[i];
		if(rx) b[i].x = len - b[i].x;
		if(ry) b[i].y = len - b[i].y;
	}
	cdq(1,n+q);
}

int main() {
	n = read(),q = read();
	for(int i = 1; i <= n; i++) {
		x = read(),y = read();
		a[i].type = 1;
		a[i].id = i;
		a[i].x = ++x;
		a[i].y = ++y;
		len = max(len,max(x,y));
	}
	for(int i = n+1; i <= n+q; i++) {
		opt = read(),x = read(),y = read();
		a[i].type = opt;
		a[i].id = i;
		a[i].x = ++x;
		a[i].y = ++y;
		a[i].ans = INF;
		len = max(len,max(x,y));
	}
	len++;
	solve(0,0),solve(0,1),solve(1,0),solve(1,1);
	for(int i = n+1; i <= n+q; i++)
		if(a[i].type == 2) printf("%d\n",a[i].ans);
	return 0;
}
```

---

## 作者：tyg这个lajixswl (赞：29)

# **K-D Tree**


 _多维（k维）二叉查找树，也就是我们常说的K-D Tree（k-dimensional（维度）树）。主要应用于多维空间关键数据的搜索（如范围搜索和最近邻搜索）。_ 

------------
### 前置知识：
1. 二叉搜索树（BST）

1. 最好写过替罪羊树（不会也没关系，后面会讲）

1. ~~读过题~~

------------


## 一维K-D Tree
一维K-D Tree 本质就是一棵二叉搜索树（BST），二叉搜索树，具有如下性质：

1. 如果左子树非空，那么左子树上所有的结点的值都小于它根节点上的值
       
1. 如果右子树非空，那么右子树上所有的结点的值都大于它根节点上的值
1. 它的左右子树都满足上述二叉搜索树的性质

### **构建**

一维K- DTree的构建可类比BST或其他平衡树的构建方式。

例如，对于给定序列，如果想得到一棵较为平衡的平衡树，我们可以取出当前序列的中位数作为当前结点的键值，然后将小于等于当前结点键值的扔到左子树（当然，对于等于当前结点键值的，你也可以通过在当前结点记录一个cnt表示重复键值的出现次数，来代替将它扔到左子树），而其余的结点我们可以将它扔到右子树。递归左右子树，重复上述过程即可。

------------
## 二维K-D Tree
现在我们将问题抬升到二维，在构建二维的K-D Tree时，我们发现：
在一维中，由于仅存在一个关键字（即上文的键值），因此只比较仅有的一维即可，但是二维中却有x,y两个维度的关键字，我们该如何比较呢？

秉承上面的思路，不难发现K-D Tree建树的过程核心就在于解决选取哪个维度为主要关键字的问题。对解决该问题，当前主要有如下几种选法：
### 1. 瞎xx选法
从根节点出发，向下递归的过程中，每走到一层我们随机挑选一个维度，以该维度为主要关键字，第二维为次要关键字比较排序，取中位数为当前结点的代表元，递归左右子树。效率玄学，优点是不易被卡，缺点是不稳定。

### 2.交替选法
从根节点出发，向下递归的过程中，我们按顺序轮流选择现有的几个维度做主要关键字，第二维为次要关键字比较排序，取中位数为当前结点的代表元，递归左右子树。

以二维K-D Tree举例，如果上一层以x维作主要关键字，则当前层就以y维作主要关键字，当前层的下一层就以x维作主关键字，交替选择。

这种选法的优点是稳定，实现简单，缺点是~~毒瘤出题人会卡~~。

当前OI竞赛中普遍选择的就是这种选法。
### 3.方差选法

我们拿豆腐与木棍举例，如果我们用交替选法，豆腐横着一刀，竖着一刀，轮流切，最后得到的就是整整齐齐的豆腐块。但如果是小木棍，我们将它拦腰折断，然后要求你竖着切一刀，是不是就很鸡肋。因此为了避免上述情况的发生，就有了普适性更高的方差选法,对于一个序列，方差越大说明数据分布越分散，方差越小说明分布越集中。因此从方差大的维度开始切分可以取得很好的切分效果及平衡性。

优点：效率有保障，适用范围广，缺点是实现较为复杂，这里仅作简单介绍，有兴趣的读者，可以自行查阅实现过程~~~~（逃）。


------------
## 实现

- 一个满足我们按任意维度排序需要的cmp，大概长成这个样子：
```cpp
bool dimension；

inline bool cmp(Point p1, Point p2)
{
	if (dimension == 0)return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
	return p1.y < p2.y || (p1.y == p2.y && p1.x < p2.x);
}
```
- 一个能构造尽可能平衡的build。

由于我们需要完成取中位数，并将序列分为小于中位数，和大于中位数两部分的操作，恰巧algorithm库又提供了能满足我们要求的nth_element函数。代码也很简单：

```cpp
inline Node* build(int l, int r, bool d)
{
	if (l >= r)return null;
	int mid = (l + r) >> 1;
	dimension = d;
	nth_element(a + l, a + mid, a + r, cmp);
	Node *o = new_node(a[mid]);
	o->son[0] = build(l, mid, d ^ 1);
	o->son[1] = build(mid + 1, r, d ^ 1);
	o->maintain();
	return o;
}
```
- 插入

插入操作的大体框架与普通的平衡树近似，要插入的结点与当前遍历的结点作比较，如果要插入的结点较小，就往左子树继续遍历，反之，就往右子树遍历，如果遍历到空结点，说明这个结点不存在，我们就新建一个结点，将要插入结点的信息存入。


```cpp
inline Node** __insert(Node *&o, Point key)//指向指针的指针，最终结果为返回最靠近根的需要重构点。
{
	if (o == null)
	{
		o = new_node(key);
		reg_dimension = dimension;
		return &null;
	}
	else
	{
		o->cover++;
		bool dir = cmp(key, o->p) ^ 1;
		dimension ^= 1;
		Node** res = __insert(o->son[dir], key);
		if (o->is_bad())
		{
			res = &o;
			reg_dimension = dimension;//记录递归过程中最后一个较为不平衡的结点
		}
		o->maintain();
		return res;
	}
}
inline void insert(Point key)
{
	reg_dimension = dimension = 0;
	Node** res = __insert(root, key);
	if (*res != null)rebuild(*res, reg_dimension);
}
```
- 拍扁重构

插入操作会导致一个问题，就是我们辛辛苦苦build出的一个形态优美的平衡树，有可能将再次失衡，为了避免这样的情况，我们引入一个概念，叫做alpha权值平衡。

我们知道，替罪羊树是一种典型的重量平衡树，它并不依赖旋转而维持形态，而是依靠当树的某一部分失衡过于严重时，局部重构维护平衡。而用来衡量一棵树的平衡情况的变量就叫做alpha平衡因子，常见的平衡树，如treap的alpha大多在0.7~0.8之间，红黑树的alpha大多在0.66左右，**alpha越趋近于0.5，树就越平衡，越趋近于1，树就越倾向于链的形态。** 

替罪羊树可以通过手动调节alpha值，以达到更高的效率。拿极端情况举例，如果你将alpha设为0.5，然后你的树稍有失衡就会不断的拍扁重构。如果你将alpha设为1，然后你的树即使退化成链，你的程序也无动于衷。

因此我们通常将alpha设为0.75，这个折中之后的结果。K-D Tree也是同理。
```cpp
inline void travel(Node* p, vector<Node*>&x)//将需要重构的点收集起来
{
	if (p == null)return;
	travel(p->son[0], x);
	x.push_back(p);
	travel(p->son[1], x);
}
inline Node* divide(vector<Node*>&x, int l, int r, bool d)//递归函数
{
	if (l >= r)return null;
	int mid = (l + r) >> 1;
	dimension = d;
	Node *o = x[mid];
	o->son[0] = divide(x, l, mid, d ^ 1);
	o->son[1] = divide(x, mid + 1, r, d ^ 1);
	o->maintain();
	return o;
}
inline void rebuild(Node *&o, bool d)
{
	static vector<Node*>v;
	v.clear();
	travel(o, v);
	o = divide(v, 0, v.size(), d);
}
```

- Push_up

维护以该结点为根的子树覆盖的最大矩形，和该子树包含的所有点的数量（**包括已经被打了删除标记，还没有及时移除结点的数量（本题不需要考虑）和实际存在节点的数量**）
```cpp
inline void maintain()
	{
		r1.x = min(r1.x, min(son[0]->r1.x, son[1]->r1.x));
		r1.y = min(r1.y, min(son[0]->r1.y, son[1]->r1.y));
		r2.x = max(r2.x, max(son[0]->r2.x, son[1]->r2.x));
		r2.y = max(r2.y, max(son[0]->r2.y, son[1]->r2.y));
		cover = son[0]->cover + son[1]->cover + 1;
	}
```
- Query

这个没啥好说的，和平衡树一样的定位结点。需要注意的是，这里有个很重要的剪枝，就是优先递归更可能存在答案的一边，然后判断另外一边是否可能存在答案，如果可能存在就递归，不存在直接剪掉。

```cpp
inline void query(Node *o, Point key)
{
	if (o == null)return;
	ans = min(ans, Manhattan_dis(key, o->p));
	int dir = o->son[0]->dis(key) > o->son[1]->dis(key);
	query(o->son[dir], key);//优先递归更可能存在答案的一边
	if (o->son[dir ^ 1]->dis(key) < ans)
		query(o->son[dir ^ 1], key);//如果另外一边也有可能存在答案，递归
}
```
- 两个Dis函数

这个根据题意写的，本题是要求曼哈顿距离，另外封在结构体里的那个，求的是当前结点，到以该结点为根的子树维护矩形边界的最小曼哈顿距离。

## **整合->O2->AC**

不开O2有一个点会T，不过据说大多数K-D Tree都会T，甚至部分CDQ有一个点也会T，所以就心安理得开了O2.~~逃~~

**(完)**

------------
# Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#define re register
#define alpha (0.75)
using namespace std;
const int N = 6e5 + 5;
const int INF = 0x3f3f3f3f;
bool dimension;
bool reg_dimension;
int n, m, ans;
struct Point
{
	int x, y;
	Point(int X = 0, int Y = 0) :x(X), y(Y) {}
};
Point a[N];
struct Node *null;
struct Node
{
	int cover;
	Point p, r1, r2;
	Node *son[2];
	inline void maintain()
	{
		r1.x = min(r1.x, min(son[0]->r1.x, son[1]->r1.x));
		r1.y = min(r1.y, min(son[0]->r1.y, son[1]->r1.y));
		r2.x = max(r2.x, max(son[0]->r2.x, son[1]->r2.x));
		r2.y = max(r2.y, max(son[0]->r2.y, son[1]->r2.y));
		cover = son[0]->cover + son[1]->cover + 1;
	}
	inline bool is_bad()
	{
		return max(son[0]->cover, son[1]->cover) > cover*alpha + 5;
	}
	inline int dis(Point p)
	{
		if (this == null)return INF;
		int res = 0;
		if (p.x<r1.x || p.x>r2.x)res += p.x < r1.x ? r1.x - p.x : p.x - r2.x;
		if (p.y<r1.y || p.y>r2.y)res += p.y < r1.y ? r1.y - p.y : p.y - r2.y;
		return res;
	}
};
Node mempool[N];
Node *tail;
Node *root;
inline bool cmp(Point p1, Point p2)
{
	if (dimension == 0)return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
	return p1.y < p2.y || (p1.y == p2.y && p1.x < p2.x);
}
inline int Manhattan_dis(Point a, Point b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}
inline void init()
{
	tail = mempool;
	null = tail++;
	null->son[0] = null->son[1] = null;
	null->r1 = Point(INF, INF);
	null->r2 = Point(-INF, -INF);
	null->cover = 0;
	root = null;
}
inline Node* new_node(Point key)
{
	Node *o;
	o = tail++;
	o->son[0] = o->son[1] = null;
	o->cover= 1;
	o->p = o->r1 = o->r2 = key;
	return o;
}
inline void travel(Node* p, vector<Node*>&x)
{
	if (p == null)return;
	travel(p->son[0], x);
	x.push_back(p);
	travel(p->son[1], x);
}
inline Node* divide(vector<Node*>&x, int l, int r, bool d)
{
	if (l >= r)return null;
	int mid = (l + r) >> 1;
	dimension = d;
	Node *o = x[mid];
	o->son[0] = divide(x, l, mid, d ^ 1);
	o->son[1] = divide(x, mid + 1, r, d ^ 1);
	o->maintain();
	return o;
}
inline void rebuild(Node *&o, bool d)
{
	static vector<Node*>v;
	v.clear();
	travel(o, v);
	o = divide(v, 0, v.size(), d);
}
inline Node* build(int l, int r, bool d)
{
	if (l >= r)return null;
	int mid = (l + r) >> 1;
	dimension = d;
	nth_element(a + l, a + mid, a + r, cmp);
	Node *o = new_node(a[mid]);
	o->son[0] = build(l, mid, d ^ 1);
	o->son[1] = build(mid + 1, r, d ^ 1);
	o->maintain();
	return o;
}
inline Node** __insert(Node *&o, Point key)
{
	if (o == null)
	{
		o = new_node(key);
		reg_dimension = dimension;
		return &null;
	}
	else
	{
		o->cover++;
		bool dir = cmp(key, o->p) ^ 1;
		dimension ^= 1;
		Node** res = __insert(o->son[dir], key);
		if (o->is_bad())
		{
			res = &o;
			reg_dimension = dimension;//记录递归过程中最后一个较为不平衡的结点
		}
		o->maintain();
		return res;
	}
}
inline void insert(Point key)
{
	reg_dimension = dimension = 0;
	Node** res = __insert(root, key);
	if (*res != null)rebuild(*res, reg_dimension);
}
inline void query(Node *o, Point key)
{
	if (o == null)return;
	ans = min(ans, Manhattan_dis(key, o->p));
	int dir = o->son[0]->dis(key) > o->son[1]->dis(key);
	query(o->son[dir], key);
	if (o->son[dir ^ 1]->dis(key) < ans)
		query(o->son[dir ^ 1], key);
}
inline int read()
{
	re char ch = getchar(); re int f = 1, x = 0;
	while (ch > '9' || ch < '0') { if (ch == '-')f = -1; ch = getchar(); }
	while (ch >= '0'&&ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
int main()
{
	init();
	n = read(); m = read();
	for (re int i = 0; i < n; i++)a[i].x = read(), a[i].y = read();
	root = build(0, n, 0);
	while (m--)
	{
		re int op = read(), x = read(), y = read();
		if (op == 1)insert(Point(x, y));
		else
		{
			ans = INF;
			query(root, Point(x, y));
			printf("%d\n", ans);
		}
	}
	return 0;
}
```


---

## 作者：Star_Cried (赞：15)

## P4169-CDQ分治/K-D tree（三维偏序）-天使玩偶

~~这是一篇两种做法都有的题解~~

### 题外话

我写吐了……

本着不看题解的原则，没写（不会）K-D tree，就写了个cdq分治的做法。下面是我的写题步骤：

1. 想着树状数组维护不了区间最值，于是写了线段树，因为一个**的错误调了几个小时；

2. cdq只写了两个方向。显然是错的，因为没考虑修改。所以挂了；

3. 加上另外两个方向，正确性终于ok，兴高采烈地交上去然后TLE；

   ```cpp
   #include<iostream>
   #include<cstdio>
   #include<cstring>
   #include<cctype>
   #include<algorithm>
   #include<cmath>
   using namespace std;
   char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
   #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
   inline int read(){
   	int w=0,x=0;char c=getchar();
   	while(!isdigit(c))w|=c=='-',c=getchar();
   	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
   	return w?-x:x;
   }
   void print(long long x) {
       if(x>9) print(x/10);
       *O++=x%10+'0';
   }
   namespace star
   {
   	const int maxn=6e5+10,INF=0x3f3f3f3f;
   	int n,m,ans[maxn],LN=0,RN=1000006;
   	struct query{
   		int x,y,id,op;
   	}q[maxn<<1];
   	inline bool cmp1(query a,query b){return a.x<b.x;}
   	inline bool cmp2(query a,query b){return a.x>b.x;}
   	struct SegmentTree{
   		#define ls (ro<<1)
   		#define rs (ro<<1|1)
   		struct tree{
   			int l,r,mx;
   		}e[16000005];
   		void build(int ro,int l,int r){
   			e[ro].l=l,e[ro].r=r;
   			if(l==r){
   				e[ro].mx=-INF;return;
   			}
   			int mid=l+r>>1;
   			build(ls,l,mid);
   			build(rs,mid+1,r);
   			e[ro].mx=max(e[ls].mx,e[rs].mx);
   		}
   		void update(int ro,int k,int v){
   			int l=e[ro].l,r=e[ro].r;
   			if(l==r){
   				e[ro].mx=max(e[ro].mx,v);return;
   			}
   			int mid=l+r>>1;
   			if(k<=mid)update(ls,k,v);
   			else update(rs,k,v);
   			e[ro].mx=max(e[ls].mx,e[rs].mx);
   		}
   		void update2(int ro,int k,int v){
   			int l=e[ro].l,r=e[ro].r;
   			if(l==r){
   				e[ro].mx=v;return;
   			}
   			int mid=l+r>>1;
   			if(k<=mid)update2(ls,k,v);
   			else update2(rs,k,v);
   			e[ro].mx=max(e[ls].mx,e[rs].mx);
   		}
   		int query(int ro,int x,int y){
   			int l=e[ro].l,r=e[ro].r;
   			if(l==x and r==y)return e[ro].mx;
   			int mid=l+r>>1;
   			if(y<=mid)return query(ls,x,y);
   			else if(x>mid)return query(rs,x,y);
   			else return max(query(ls,x,mid),query(rs,mid+1,y));
   		}
   		#undef ls
   		#undef rs
   	}T;
   	void cdq(int l,int r){
   		if(l==r)return;
   		int mid=l+r>>1;
   		cdq(l,mid),cdq(mid+1,r);
   		int i,j;
   		sort(q+l,q+mid+1,cmp1),sort(q+mid+1,q+r+1,cmp1);
   		for(i=mid+1,j=l;i<=r;i++){
   			while(q[j].x<=q[i].x and j<=mid){
   				if(!q[j].op) T.update(1,q[j].y,q[j].x+q[j].y);j++;
   			}
   			if(q[i].op)ans[q[i].id]=min(ans[q[i].id],q[i].x+q[i].y-T.query(1,LN,q[i].y));
   		}
   		for(i=l;i<j;i++) T.update2(1,q[i].y,-INF);
   		
   		for(i=mid+1,j=l;i<=r;i++){
   			while(q[j].x<=q[i].x and j<=mid){
   				if(!q[j].op) T.update(1,q[j].y,q[j].x-q[j].y);j++;
   			}
   			if(q[i].op)ans[q[i].id]=min(ans[q[i].id],q[i].x-q[i].y-T.query(1,q[i].y,RN));
   		}
   		for(i=l;i<j;i++) T.update2(1,q[i].y,-INF);
   		
   		sort(q+l,q+mid+1,cmp2),sort(q+mid+1,q+r+1,cmp2);
   		for(i=mid+1,j=l;i<=r;i++){
   			while(q[j].x>=q[i].x and j<=mid){
   				if(!q[j].op) T.update(1,q[j].y,q[j].y-q[j].x);j++;
   			}
   			if(q[i].op)ans[q[i].id]=min(ans[q[i].id],q[i].y-q[i].x-T.query(1,LN,q[i].y));
   		}
   		for(i=l;i<j;i++) T.update2(1,q[i].y,-INF);
   		
   		for(i=mid+1,j=l;i<=r;i++){
   			while(q[j].x>=q[i].x and j<=mid){
   				if(!q[j].op) T.update(1,q[j].y,-q[j].y-q[j].x);j++;
   			}
   			if(q[i].op)ans[q[i].id]=min(ans[q[i].id],-q[i].y-q[i].x-T.query(1,q[i].y,RN));
   		}
   		for(i=l;i<j;i++) T.update2(1,q[i].y,-INF);
   	}
   	inline void work(){
   		n=read(),m=read();
   		memset(ans,INF,sizeof ans);
   		for(int i=1;i<=n;i++) q[i].x=read(),q[i].y=read(),LN=min(LN,q[i].y),RN=max(RN,q[i].y),q[i].op=0;
   		for(int i=n+1;i<=n+m;i++){
   			q[i].op=(read()-1);
   			q[i].id=q[i-1].id+q[i].op;
   			q[i].x=read(),q[i].y=read();
   		}
   		int mx=q[n+m].id;
   		T.build(1,LN,RN);
   		cdq(1,n+m);
   		for(int i=1;i<=mx;i++)print(ans[i]),*O++='\n';
   		fwrite(obuf,O-obuf,1,stdout);
   	}
   }
   signed main(){
   	star::work();
   	return 0;
   }
   
   ```

4. 原以为是线段树常数过大，学习了树状数组解法然后WA了；

5. 改回了线段树，把sort换成了merge，又WA；

6. 只有最后一个办法了：改成树状数组+merge，要是再挂我就当场去学KD-tree.

7. 写挂了，我滚去学K-D tree了。

## K-D tree

K-D tree是一种维护多维空间点的数据结构，在这道题上是两维所以也叫作2-D tree。具体实现方式是将每个节点所在的区域切割递归建成二叉树，每一个树上的节点代表一个实际的结点，但又存储着选择这个结点时的区域大小。

#### 建树

KDT在建树时，为了让它保持平衡，我们需要尽量选择所在空间维度的**中位数**，所以在保证时间复杂度正确的情况下我们可以使用nth_element函数，其作用是在线性时间内将一个数摆到它排序后应该在的位置，而将比它小的放在左边，比他大的放在右边（不重载运算符情况下是从小到大），但不是有序排列。

```cpp
int build(int l,int r){
	if(l>r)return 0;
	int mid=l+r>>1;
	double av[2],va[2];
	av[0]=av[1]=va[0]=va[1]=0;
	for(int i=l;i<=r;i++)av[0]+=e[g[i]].x,av[1]+=e[g[i]].y;
	av[0]/=(r-l+1),av[1]/=(r-l+1);
	for(int i=l;i<=r;i++)
		va[0]+=(av[0]-e[g[i]].x)*(av[0]-e[g[i]].x),
		va[1]+=(av[1]-e[g[i]].y)*(av[1]-e[g[i]].y);//寻找应该切割的维度
	if(va[0]>va[1])nth_element(g+l,g+mid,g+r+1,cmpx),e[g[mid]].d=1;//d是维度
	else nth_element(g+l,g+mid,g+r+1,cmpy),e[g[mid]].d=2;
	e[g[mid]].ls=build(l,mid-1);
	e[g[mid]].rs=build(mid+1,r);
	maintain(g[mid]);//pushup函数，更新节点信息。
	return g[mid];
}
```

#### 插入

从root递归下去查找，按照当前节点所在维度向下插入，到达空节点时新建节点存储信息。

注意：当插入节点过多时KDT有可能失衡，此时我们需要将它拍扁重建（pia~）（因为KDT的结构，好像没有别的方法了？）①

```cpp
void insert(int &x,int k){
	if(!x){
		x=k,maintain(k);return;
	}
	if(e[x].d==1){
		if(e[k].x<=e[x].x)insert(e[x].ls,k);
		else insert(e[x].rs,k);
	}else{
		if(e[k].y<=e[x].y)insert(e[x].ls,k);
		else insert(e[x].rs,k);
	}
	maintain(x);
	if(bad(x)) rebuild(x);//pia
}
```

```cpp
inline bool bad(int x){return 0.9*e[x].siz<=(double)max(e[e[x].ls].siz,e[e[x].rs].siz);}
//0.9为拍扁的阈值，越大拍扁越不频繁，但有可能失衡，按照实际情况调整。注意，实测其为0.8时会爆栈。
```

```cpp
void getson(int x){
	if(!x)return;
	getson(e[x].ls);
	g[++t]=x;
	getson(e[x].rs);
}
inline void rebuild(int &x){
	t=0;
	getson(x);//找到所有被拍扁的节点（其实没必要，新建节点也行）
	x=build(1,t);
}
```

#### 查询

此题要求查询距离关键点最近的点的距离。

注意：我们在查询下传的时候需要比较的是区块位置距离关键点的距离，而统计答案是按照当前节点的坐标统计。

```cpp
int ans=INF;//请不要学鄙人用全局变量传参，我被人嘴了
void query(int x){
	cmin(ans,dist(x));
	int dl=INF,dr=INF;
	if(e[x].ls)dl=getdis(e[x].ls);
	if(e[x].rs)dr=getdis(e[x].rs);
	if(dl<dr){
		if(dl<ans)query(e[x].ls);
		if(dr<ans)query(e[x].rs);
	}else{
		if(dr<ans)query(e[x].rs);
		if(dl<ans)query(e[x].ls);
	}
}
```

### 完整代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<cmath>
#define cmin(i,j) (i)=min((i),(j))
#define cmax(i,j) (i)=max((i),(j))
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=6e5+10,INF=0x3f3f3f3f;
	int n,m,rt,tot,qx,qy,g[maxn],t;
	struct node{
		int x,y,ls,rs,l[2],r[2],siz,d;
	}e[maxn];
	inline bool cmpx(int a,int b){return e[a].x<e[b].x;}
	inline bool cmpy(int a,int b){return e[a].y<e[b].y;}
	inline void maintain(int x){
		e[x].siz=e[e[x].ls].siz+e[e[x].rs].siz+1;
		e[x].l[0]=e[x].r[0]=e[x].x;
		e[x].l[1]=e[x].r[1]=e[x].y;
		if(e[x].ls)
			cmin(e[x].l[0],e[e[x].ls].l[0]),cmax(e[x].r[0],e[e[x].ls].r[0]),
			cmin(e[x].l[1],e[e[x].ls].l[1]),cmax(e[x].r[1],e[e[x].ls].r[1]);
		if(e[x].rs)
			cmin(e[x].l[0],e[e[x].rs].l[0]),cmax(e[x].r[0],e[e[x].rs].r[0]),
			cmin(e[x].l[1],e[e[x].rs].l[1]),cmax(e[x].r[1],e[e[x].rs].r[1]);
	}
	int build(int l,int r){
		if(l>r)return 0;
		int mid=l+r>>1;
		double av[2],va[2];
		av[0]=av[1]=va[0]=va[1]=0;
		for(int i=l;i<=r;i++)av[0]+=e[g[i]].x,av[1]+=e[g[i]].y;
		av[0]/=(r-l+1),av[1]/=(r-l+1);
		for(int i=l;i<=r;i++)
			va[0]+=(av[0]-e[g[i]].x)*(av[0]-e[g[i]].x),
			va[1]+=(av[1]-e[g[i]].y)*(av[1]-e[g[i]].y);
		if(va[0]>va[1])nth_element(g+l,g+mid,g+r+1,cmpx),e[g[mid]].d=1;
		else nth_element(g+l,g+mid,g+r+1,cmpy),e[g[mid]].d=2;
		e[g[mid]].ls=build(l,mid-1);
		e[g[mid]].rs=build(mid+1,r);
		maintain(g[mid]);
		return g[mid];
	}
	void getson(int x){
		if(!x)return;
		getson(e[x].ls);
		g[++t]=x;
		getson(e[x].rs);
	}
	inline void rebuild(int &x){
		t=0;
		getson(x);
		x=build(1,t);
	}
	inline bool bad(int x){return 0.9*e[x].siz<=(double)max(e[e[x].ls].siz,e[e[x].rs].siz);}
	void insert(int &x,int k){
		if(!x){
			x=k,maintain(k);return;
		}
		if(e[x].d==1){
			if(e[k].x<=e[x].x)insert(e[x].ls,k);
			else insert(e[x].rs,k);
		}else{
			if(e[k].y<=e[x].y)insert(e[x].ls,k);
			else insert(e[x].rs,k);
		}
		maintain(x);
		if(bad(x)) rebuild(x);
	}
	inline int getdis(int x){return max(0,qx-e[x].r[0])+max(0,e[x].l[0]-qx)+max(0,qy-e[x].r[1])+max(0,e[x].l[1]-qy);}
	inline int dist(int x){return abs(qx-e[x].x)+abs(qy-e[x].y);}
	int ans;
	void query(int x){
		cmin(ans,dist(x));
		int dl=INF,dr=INF;
		if(e[x].ls)dl=getdis(e[x].ls);
		if(e[x].rs)dr=getdis(e[x].rs);
		if(dl<dr){
			if(dl<ans)query(e[x].ls);
			if(dr<ans)query(e[x].rs);
		}else{
			if(dr<ans)query(e[x].rs);
			if(dl<ans)query(e[x].ls);
		}
	}
	inline void work(){
		n=read(),m=read();
		while(n--){
			e[++tot].x=read(),e[tot].y=read();
			g[tot]=tot;
		}
		rt=build(1,tot);
		while(m--){
			if(read()==1){
				e[++tot].x=read(),e[tot].y=read();
				insert(rt,tot);
			}else{
				qx=read(),qy=read();ans=INF;query(rt);
				printf("%d\n",ans);
			}
		}
	}
}
signed main(){
	star::work();
	return 0;
}
```

# 注释

①K-D tree的重建方式含争议。事实上，作者是从OIwiki上学习的K-D tree写法，而在当页下方评论区中有人提出KDT不应该像替罪羊一样按照阈值重构，因为这样的话会在极端情况下多次重构导致时间复杂度退化。他提出，应该每插入$\sqrt n$个点后将全树进行重构，这样保证时间复杂度最劣情况下全部插入为$O(n\sqrt n)$，查询最劣情况下单次为$O(\sqrt n)$。但是大家不用担心，愚以为大多数情况下本人这种写法的均摊时间复杂度是比另一种优的，实在不行可以适当调整阈值。欢迎大家~~激烈对线~~。



---

## 作者：FlashHu (赞：11)

不会KDT，然而CDQ当然是有优势的。

第一眼就能发现每一个修改或查询都有三个属性，$x,y$，还有时间戳。那么怎样把它转化为一般的三维偏序问题呢？

假如所有记忆的点都在查询的点的左下角，那么就会只有$x,y$和时间戳三个维度都小于查询点的记忆点可以产生贡献，这就是三维偏序了。

贡献是什么呢？设有若干$j$对$i$产生了贡献，那么直接去绝对值，答案就是$\min\{x_i-x_j+y_i-y_j\}$，也就是$x_i+y_i-\max\{x_j+y_j\}$，这个还是可以用树状数组，只不过改成维护前缀最大值。第一维时间戳，输入已经排好序了；第二位$x$归并；第三位$y$树状数组统计答案。

然而假设并不成立。但是我们可以发现，每个能产生贡献的点只可能会在查询点的四个方向（左下，左上，右下，右上），那么对所有点还要进行$3$遍坐标翻转（新坐标等于值域减去原坐标），做$4$遍CDQ，就可以统计到每个方向的最优答案，最后再取$\min$即可。

$n,m=300000$，值域$1000000$，一看这$O((n+m)\log(n+m)\log k)$好大，还要跑$4$遍，真的不会T么？所以还是要优化一些细节。

首先，蒟蒻仍然沿用[三维偏序模板的做法](https://www.cnblogs.com/flashhu/p/9381075.html)，没有对元素封struct以减少空间交换，这样在做完坐标翻转后也能更快还原，直接`for`一遍初始化。然而也会带来数组的频繁调用，蒟蒻也在怀疑这种优化的可行性，还望Dalao指教。

接着，我们发现左边有$n$个元素都确定了是记忆点。也就是说，我们不必对$n+m$个点都跑CDQ了，只对后面$m$个点跑，前面的$n$个点直接预处理按$x$第一关键字、$y$第二关键字sort，这样复杂度就降到了$O(n\log n+m\log m\log k+n\log k)$了。然而做完坐标翻转后也别忘了处理一下。如果这一次翻转的是$y$，那么$x$不会受到影响；如果翻转的是$x$，那么也直接翻转数组就好啦！

至于fread什么的用上也好。加上这一堆优化，代码就有90行了。

然后一交上去就1A了！？平时习惯了满屏殷红的WA，蒟蒻也不得不感叹，比起不少数据结构，CDQ真是思路板又好写还好调。

然而BZOJ的$n,m$都有$500000$，CDQ过不了。。。。。。还是stO楼上CDQ跑得超快的巨佬吧，蒟蒻不会卡常。
```
#include<cstdio>
#include<cstring>
#include<algorithm>
#define RG register
#define I inline void
#define R RG int
#define gc          if(++pp==pe)fread (pp=buf,1,SZ,stdin)
#define pc(C) *pp=C;if(++pp==pe)fwrite(pp=buf,1,SZ,stdout)
const int N=3e5,D=1e6+2,SZ=1<<19,INF=20020307;
char buf[SZ],*pe=buf+SZ,*pp=pe-1;
int x[N],y[N],p[N],q[N],f[N],ans[N],e[D+1];
bool t[N];
struct NODE{
    int x,y;
    inline bool operator<(RG NODE b)const{
        return x<b.x||(x==b.x&&y<b.y);
    }
}a[N];//前n个点
inline int in(){
    gc;while(*pp<'-')gc;
    R x=*pp&15;gc;
    while(*pp>'-'){x*=10;x+=*pp&15;gc;}
    return x;
}
I out(R x){
    if(x>9)out(x/10);
    pc(x%10|'0');
}
I min(R&x,R y){if(x>y)x=y;}
I upd(R i,R v){for(;i<=D;i+=i&-i)if(e[i]<v)e[i]=v;}
I qry(R i,R&v){for(;i   ;i-=i&-i)if(v<e[i])v=e[i];}
I clr(R i)    {for(;i<=D;i+=i&-i)e[i]=0;}
void cdq(R*p,R m){//三维偏序Dalao们都会吧
    if(m==1)return;
    R n=m>>1,i,j,k;
    cdq(p,n);cdq(p+n,m-n);
    memcpy(q,p,m<<2);
    for(k=i=0,j=n;i<n&&j<m;++k)
        if(x[q[i]]<=x[q[j]]){
            if(!t[q[i]])upd(y[q[i]],x[q[i]]+y[q[i]]);
            p[k]=q[i++];
        }
        else{
            if(t[q[j]])qry(y[q[j]],f[q[j]]);
            p[k]=q[j++];
        }
    for(;j<m;++j)
        if(t[q[j]])qry(y[q[j]],f[q[j]]);
    memcpy(p+k,q+i,(n-i)<<2);//注意收尾和清空
    for(--i;~i;--i)clr(y[q[i]]);
}
int main(){
    R n=in(),m=in(),i,j,k;
    for(i=0;i<n;++i)
        a[i].x=in()+1,a[i].y=in()+1;
    std::sort(a,a+n);//n个点预排序
    for(i=0;i<m;++i){
        if((t[i]=in()-1))ans[i]=INF;//注意给极大值
        x[i]=in()+1;y[i]=in()+1;//BIT不能有0下标，所以改一下
    }
    for(k=1;k<=4;++k){
        for(i=0;i<m;++i)p[i]=i;//很快就可以初始化序列
        cdq(p,m);
        for(i=j=0;i<n&&j<m;){//外面统计还是和CDQ一样，只是不用归并了
            if(a[i].x<=x[p[j]])
                upd(a[i].y,a[i].x+a[i].y),++i;
            else{
                if(t[p[j]])qry(y[p[j]],f[p[j]]);
                ++j;
            }
        }
        for(;j<m;++j)
            if(t[p[j]])qry(y[p[j]],f[p[j]]);
        memset(e,0,sizeof(e));
        for(i=0;i<m;++i)
            if(t[i]&&f[i])min(ans[i],x[i]+y[i]-f[i]),f[i]=0;
        if(k==4)break;
        if(k&1){//第一次、第三次上下翻
            for(i=0;i<n;++i)a[i].y=D-a[i].y;
            for(i=0;i<m;++i)y[i]=D-y[i];
        }
        else{//第二次左右翻
            for(i=0;i<n;++i)a[i].x=D-a[i].x;
            for(i=0;i<m;++i)x[i]=D-x[i];
            for(i=0,j=n-1;i<j;++i,--j)std::swap(a[i],a[j]);//注意仍要保证x不降
        }
    }
    for(pp=buf,i=0;i<m;++i)
        if(t[i]){out(ans[i]);pc('\n');}
    fwrite(buf,1,pp-buf,stdout);
    return 0;
}
```

---

## 作者：mzgwty (赞：5)

~~这题真是太痛苦了~~

看到这种矩阵上询问的题，我们直接上CDQ（~~我也不知道为什么~~）

不难得到，这题求对于每个询问最近的有记忆的点到它的距离，可以转化为求向左上，左下，右上，右下四个区间的离它最近的点到它的距离。然后我们可以通过对坐标进行处理将其余三种转化为左下（或者右上也挺好求的），因为

当$x_i>x_{i-1}$且$y_i>y_{i-1}$时，$i-1,i$的曼哈顿距离$=x_{i}-x_{i-1}+y_{i}-y_{i-1}=x_i+y_i-(x_{i-1}+y_{i-1})$，对于每一个询问$i$，$x$和$y$都是定值，所以我们只需要找到所有在它左下角的点中$x+y$的最大值即可。

~~瞬间变成三维偏序CDQ板子题~~

但是对于这样的数据，我们并不能AC。

我首先进行了一些常规优化（比如快读，$O_2$），后面甚至进行了一些范围缩减的超级工作，最高也只是得到了73分。

后来经$dalao$远程点拨，本蒟蒻解决了一个致命性的问题：CDQ里不能写快排。

这是原来的：

```cpp
void CDQ(int l,int r) {
	int mid=l+r>>1;
	if(l==r) return ;
	CDQ(l,mid),CDQ(mid+1,r);
	sort(a+l,a+mid+1,cmp2);//这很重要
	sort(a+mid+1,a+r+1,cmp2);//它坑害了我
	int i=l,j=mid+1;
	while(j<=r) {
		while(i<=mid&&a[i].x<=a[j].x) {
			if(a[i].op==1) update(a[i].y,a[i].x+a[i].y);
			++i;
		}
		if(a[j].op==0) {
			int tmp=query(a[j].y);
			if(tmp) p[a[j].time].key=min(p[a[j].time].key,a[j].x+a[j].y-tmp);
		}
		++j;
	}
	rep(k,l,i-1) if(a[k].op==1) clear(a[k].y);
}
```
新版本

```cpp
void CDQ(int l,int r) {
	int mid=l+r>>1;
	if(l==r) return ;
	CDQ(l,mid),CDQ(mid+1,r);
	int i=l,j=mid+1;
	while(j<=r) {
		while(i<=mid&&a[i].x<=a[j].x) {
			if(a[i].op==1) update(a[i].y,a[i].x+a[i].y);
			++i;
		}
		if(a[j].op==0) {
			int tmp=query(a[j].y);
			if(tmp) p[a[j].time].key=min(p[a[j].time].key,a[j].x+a[j].y-tmp);
		}
		++j;
	}
	rep(k,l,i-1) if(a[k].op==1) clear(a[k].y);
	i=l,j=mid+1;
	int k=l-1;
	while(j<=r) {
		while(i<=mid&&cmp2(a[i],a[j])) t[++k]=a[i],++i;
		t[++k]=a[j],++j;
	}
	while(j<=r) t[++k]=a[j++];
	while(i<=mid) t[++k]=a[i++];
	rep(i,l,r) a[i]=t[i];
}
```
对于理论复杂度来讲，这个东西并没有太大的影响;毕竟都是$O(nlog^2n)$,但把它改掉之后效果确实会好很多，不用范围缩减都能AC本题（代码里还是用了），所以各位还是要牢记~~文化课~~老师讲的话：~~细节决定成败。~~ 有好的为什么不用呢？

$Code:$ 

```cpp
// luogu-judger-enable-o2
//不要管这种事
#include<bits/stdc++.h>
#define R register
#define INF 0x3fffffff
#define rep(i,a,b) for(R int i=a ; i<=b ; ++i)
#define dwn(i,a,b) for(R int i=a ; i>=b ; --i)
#define go(i,u) for(R int i=head[u] ; i ; i=a[i].next)
#define lowbit(x) (x&-x)
using namespace std;

inline int read() {
	int res=0,f=1;char ch;
	while(!isdigit(ch=getchar())) if(ch=='-') f=-1;
	do {
		res=res*10+ch-'0';
	} while(isdigit(ch=getchar()));
	return res*f;
}

const int N=300005,M=1000005;

int c[M],mx,my,n,m,cnt;

inline void clear(int pos) {
	while(pos<=my) {
		if(!c[pos]) break;
		c[pos]=0;
		pos+=lowbit(pos);
	}
}

inline void update(int pos,int key) {
	while(pos<=my) {
		c[pos]=max(c[pos],key);
		pos+=lowbit(pos);
	}
}

inline int query(int pos) {
	int ans=0;
	while(pos) {
		ans=max(ans,c[pos]);
		pos-=lowbit(pos);
	}
	return ans;
}

struct Q {
	int time,x,y,key,op;
}a[N<<1],p[N<<1],t[N<<1];

inline bool cmp1(Q a,Q b) {
	return a.time<b.time;
}
inline bool cmp2(Q a,Q b) {
	return (a.x!=b.x)?a.x<b.x:a.y<b.y;
}

void CDQ(int l,int r) {
	int mid=l+r>>1;
	if(l==r) return ;
	CDQ(l,mid),CDQ(mid+1,r);
	int i=l,j=mid+1;
	while(j<=r) {
		while(i<=mid&&a[i].x<=a[j].x) {
			if(a[i].op==1) update(a[i].y,a[i].x+a[i].y);
			++i;
		}
		if(a[j].op==0) {
			int tmp=query(a[j].y);
			if(tmp) p[a[j].time].key=min(p[a[j].time].key,a[j].x+a[j].y-tmp);
		}
		++j;
	}
	rep(k,l,i-1) if(a[k].op==1) clear(a[k].y);
	i=l,j=mid+1;
	int k=l-1;
	while(j<=r) {
		while(i<=mid&&cmp2(a[i],a[j])) t[++k]=a[i],++i;
		t[++k]=a[j],++j;
	}
	while(j<=r) t[++k]=a[j++];
	while(i<=mid) t[++k]=a[i++];
	rep(i,l,r) a[i]=t[i];
}

inline void init() {
	rep(i,1,n) a[i]=p[i];
}

int main() {
	n=read(),m=read();
	rep(i,1,n) {
		int x=read()+1,y=read()+1;
		mx=max(mx,x),my=max(my,y);
		p[i]=Q{i,x,y,x+y,1};
	}
	while(m--) {
		int op=read(),x=read()+1,y=read()+1;
		mx=max(mx,x),my=max(my,y);
		if(op==1) p[++n]=Q{n,x,y,x+y,1};
		else p[++n]=Q{n,x,y,INF,0};
	}
	init();
	CDQ(1,n);
	rep(i,1,n) p[i].x=mx-p[i].x+1;
	init();
	CDQ(1,n);
	rep(i,1,n) p[i].y=my-p[i].y+1;
	init();
	CDQ(1,n);
	rep(i,1,n) p[i].x=mx-p[i].x+1;
	init();
	CDQ(1,n);
	rep(i,1,n) if(p[i].op==0) printf("%d\n",p[i].key);
	return 0;
}
```


---

## 作者：EternalEpic (赞：5)

## 《算法竞赛》书上例题（~~可惜原书没代码~~）

天使玩偶，一道好题。（书p243）我就来谈谈自己的想法吧！

而总有人在这种明明可以离线处理的三维偏序问题上投机取巧。

如：KDtree。 蒟蒻想说，KDtree在这题复杂度是不对的。虽有剪枝，可是还是有可能遍历整棵树的（~~期望复杂度不靠谱~~）

对上述看法有争议的，请跳转[KDtree讨论](https://www.luogu.org/discuss/show/94089)。觉得自己KDtree复杂度优美的，可以试试这个[天使玩偶hack版](https://www.luogu.org/problemnew/show/U25704)，对此感谢qqvq大佬的hack数据。

而cdq分治 + bit（树状数组）只要两个log，何乐而不为呢~

cdq不会？三维偏序没学过？树状数组不会用？

~~那你还是去自闭吧，可以AFO了~~

开个玩笑，请左转一位大佬博客[cdq分治入门到精通](https://blog.csdn.net/wu_tongtong/article/details/78785836)

好，那关于这道题，我想说：

先考虑简化版——即不带修改操作

对于每个点，其实是需找左上，左下，右上，右下四个方向最近距离，再取min。

以左下为例：min（1 <= i <= n) {(x - xi) + (y - yi)}

即 x + y - max（1 <= i <= n) {xi + yi} (xi <= x, yi <= y)

四方向类比，用bit维护即可。

考虑待修改，只需再按时间分治。用cdq分治，考虑修改操作在时间轴上对查询操作的影响即可：

## cdq：

```cpp
class rec {
public:
	int x, y, z;
	inline void Init(int _z, int _x, int _y) {
		x = _x; y = _y; z = _z; return;
	}
	inline bool operator < (const rec&opt) {
		return x < opt.x || x == opt.x && y < opt.y;
	}
} a[u], b[u];

int tot = 0;
int ans[u], n, m, t;

class BIT {
public:
	int c[u];
	inline void setup(void) {
		Ms(c, 0xcf); return;
	}
	
	inline int query(int x) {
		int y = inf;
		for (; x; x -= lowbit(x)) y = max(y, c[x]);
		return y;
	}
	
	inline void update(int x, int y) {
		for (; x < tot; x += lowbit(x))
			chkmax(c[x], y); return;
	}
	
	inline void modify(int x) {
		for (; x < tot; x += lowbit(x))
			c[x] = inf; return;
	}
} bit;

inline void calc(int st, int ed, int de, int dx, int dy) {
	for (register int i = st; i ^ ed; i += de) {
		int y = dy == 1 ? b[i].y : tot - b[i].y;
		int tmp = dx * b[i].x + dy * b[i].y;
		if (a[b[i].z].z == 1) bit.update(y, tmp);
		else chkmin(ans[b[i].z], abs(tmp - bit.query(y)));
	}
	
	for (register int i = st; i ^ ed; i += de) {
		int y = dy == 1 ? b[i].y : tot - b[i].y;
		if (a[b[i].z].z == 1) bit.modify(y);
	}
}

inline void cdqdiv(int l, int r) {
	int mid = l + r >> 1;
	if (l < mid) cdqdiv(l, mid);
	if (mid + 1 < r) cdqdiv(mid + 1, r);
	t = 0;
	for (register int i = l; i <= r; i++)
		if (i <= mid && a[i].z == 1 || i > mid && a[i].z == 2)
			b[++t] = a[i], b[t].z = i;

	sort(b + 1, b + t + 1);
	calc(1, t + 1, 1, 1, 1), calc(t, 0, -1, -1, -1);
	calc(1, t + 1, 1, 1, -1), calc(t, 0, -1, -1, 1);
}
```


全部代码（参考李煜东光盘）如下

## CODE：

```cpp
//Program written by Liu Zhaozhou ~~~
#include <bits/stdc++.h>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#include <deque>
#include <string>

#define lowbit(x) x & -x

#pragma GCC optimize(3)

using namespace std;

namespace Base {
inline char gc(void)
{
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

#define gc() getchar()

template <class T> inline void read(T &x)
{
	T flag = 1; x = 0; register char ch = gc();
	for (; !isdigit(ch); ch = gc()) if (ch == '-') flag = -1;
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch & 15);
	x *= flag; return;
}

inline int init(void) {
	int x; read(x); return x;
}

template <class T> inline void write(T x) {
	if (x < 0) putchar('-'), x = -x;
	register T y = 1; int len = 1;
	for (; y <= x / 10; y *= 10) ++len;
	for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

template <class T> inline void writeln(T x) {write(x); puts("");}
template <class T> inline void writeln(T x, char c) {write(x); putchar(c);}
template <class T> inline void writeln(char c, T x) {putchar(c); write(x);}

template <class T> inline void chkmax(T &x, const T y) {x > y ? x = x : x = y;}
template <class T> inline void chkmin(T &x, const T y) {x < y ? x = x : x = y;}

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define Ms(arr, opt) memset(arr, opt, sizeof(arr))
#define Mp(x, y) make_pair(x, y)

inline void file(string str) {
	freopen((str + ".in").c_str(), "r", stdin);
	freopen((str + ".out").c_str(), "w", stdout);
}
}

using namespace Base;

namespace CDQsolution {

enum {
	u = 1000010,
	inf = -114783648
};

class rec {
public:
	int x, y, z;
	inline void Init(int _z, int _x, int _y) {
		x = _x; y = _y; z = _z; return;
	}
	inline bool operator < (const rec&opt) {
		return x < opt.x || x == opt.x && y < opt.y;
	}
} a[u], b[u];

int tot = 0;
int ans[u], n, m, t;

class BIT {
public:
	int c[u];
	inline void setup(void) {
		Ms(c, 0xcf); return;
	}
	
	inline int query(int x) {
		int y = inf;
		for (; x; x -= lowbit(x)) y = max(y, c[x]);
		return y;
	}
	
	inline void update(int x, int y) {
		for (; x < tot; x += lowbit(x))
			chkmax(c[x], y); return;
	}
	
	inline void modify(int x) {
		for (; x < tot; x += lowbit(x))
			c[x] = inf; return;
	}
} bit;

inline void calc(int st, int ed, int de, int dx, int dy) {
	for (register int i = st; i ^ ed; i += de) {
		int y = dy == 1 ? b[i].y : tot - b[i].y;
		int tmp = dx * b[i].x + dy * b[i].y;
		if (a[b[i].z].z == 1) bit.update(y, tmp);
		else chkmin(ans[b[i].z], abs(tmp - bit.query(y)));
	}
	
	for (register int i = st; i ^ ed; i += de) {
		int y = dy == 1 ? b[i].y : tot - b[i].y;
		if (a[b[i].z].z == 1) bit.modify(y);
	}
}

inline void cdqdiv(int l, int r) {
	int mid = l + r >> 1;
	if (l < mid) cdqdiv(l, mid);
	if (mid + 1 < r) cdqdiv(mid + 1, r);
	t = 0;
	for (register int i = l; i <= r; i++)
		if (i <= mid && a[i].z == 1 || i > mid && a[i].z == 2)
			b[++t] = a[i], b[t].z = i;

	sort(b + 1, b + t + 1);
	calc(1, t + 1, 1, 1, 1), calc(t, 0, -1, -1, -1);
	calc(1, t + 1, 1, 1, -1), calc(t, 0, -1, -1, 1);
}

}

using namespace CDQsolution;

signed main(void) {
	file("cdq");
	read(n); read(m); m += n;
	for (int i = 1; i <= n; i++)
		read(a[i].x), read(a[i].y), a[i].y++, a[i].z = 1;
	for (int i = n + 1; i <= m; i++)
		read(a[i].z), read(a[i].x), read(a[i].y), a[i].y++;

	for (int i = 1; i <= m; i++)
		chkmax(tot, a[i].y);
	tot++; bit.setup(); Ms(ans, 0x3f);
	cdqdiv(1, m);
	for (int i = 1; i <= m; i++)
		if (a[i].z == 2) writeln(ans[i]);
    return 0;
}

/*cdq*/


```

### cdq大法吼，谢谢兹磁！！！


---

## 作者：Sol1 (赞：4)

介绍一下这个题的思想。

首先绝对值的式子非常难搞，考虑通过零点分段来去掉绝对值。

因为只有两个绝对值，所以分四类情况讨论即可，具体地来说，对于每一个查询，分别查询这个点左下方离它最近的点、左上方离它最近的点、右下方离它最近的点、右上方离它最近的点。

左上、右下、右上可以直接翻转坐标系进行转换，所以下面只讨论左下的情况。

式子被转化成求 $\min \{x-x_i+y-y_i\}$，于是我们发现这个东西统计的点要满足：

- $x_i\leq x$；
- $y_i\leq y$；
- 加入的时间在这次询问之前；
- $x_i+y_i$ 尽量大。

显然，如果把时间考虑为一个维度，那么这个就是个三维偏序问题，直接用 CDQ 来维护。

你问我为啥不用树套树？很简单，这个东西是 $O(n\log ^2 n)$ 的，平衡树还带一个巨大的常数，算法本身还要带 4 倍常数，这些全乘到一起，我不 T 谁 T……

好！愉快地写完了，交上去~

91 分 QAQ

在这里说一下我用到的常数优化：

- 每次询问之后，因为 CDQ 的特性会导致时间轴是乱序的，此时不要排序，直接在询问之前拷贝出去一个临时数组然后询问之后从临时数组里面复制。
- 树状数组清零的时候，如果遍历到了一个空位置直接返回不需要继续遍历。正确性留作习题答案略（大雾）。
- 每次询问翻转完坐标轴之后预处理出查询位置的最大的 $mx$、$my$，然后去掉 $x>mx$ 或 $y>my$ 的点（因为这些点不可能产生贡献）。

加上这些再拉一个比较好用的火车头再加上 O2 就可以爆过去啦~

那么这题就做完啦~

最终的时间复杂度是 $O(n\log ^2 n)$，空间是 $O(n)$。

题外话：

离线分治算法的优点是**空间为线性**、**常数较小**。

缺点的话很明显，就是不支持在线，以及有些时候会特别难写。

代码：

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast", "-funroll-loops")
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

const int INF = 0x3f3f3f3f;

struct Point {
	int _time, x, y, type;
	Point() {}
	Point(int _time, int x, int y, int type) : _time(_time), x(x), y(y), type(type) {}
};
Point p[600005], q[600005];
int n, m, c[2000055], ans[300005], ptop;

inline int Lowbit(int x) {
	return x & -x;
}

inline void Update(int i, int x) {
	//printf("Update(%d,%d)\n", i, x);
	for (register int j = i;j <= 1000010;j += Lowbit(j)) c[j] = Max(c[j], x);
}

inline void Remove(int i) {
	for (register int j = i;j <= 1000010;j += Lowbit(j)) {
		if (c[j] != -INF) c[j] = -INF;
		else return;
	}
}

inline int Query(int i) {
	//printf("Query(%d)", i);
	register int ans = -INF;
	for (register int j = i;j >= 1;j -= Lowbit(j)) ans = Max(ans, c[j]);
	//printf("=%d\n", ans);
	return ans;
}

inline void Read() {
	n = qread(); m = qread();
	for (register int i = 1;i <= n;i++) {
		register int x = qread() + 1, y = qread() + 1;
		q[i] = Point(0, x, y, 1);
	}
	for (register int i = 1;i <= m;i++) {
		register int opt = qread(), x = qread() + 1, y = qread() + 1;
		q[i + n] = Point(i, x, y, opt);
	}
}

inline void cdq1(int l, int r) {
	if (l == r) return;
	register int mid = l + r >> 1;
	cdq1(l, mid);
	cdq1(mid + 1, r);
	register int i = l, j = mid + 1;
	vector <Point> vc;
	//printf("cdq(%d,%d)\n", l, r);
	//puts("{");
	//for (register int i = l;i <= r;i++) printf("%d %d %d\n", p[i].type, p[i].x, p[i].y);
	while (i <= mid && j <= r) {
		if (p[i].x <= p[j].x) {
			if (p[i].type == 1) {
				Update(p[i].y, p[i].x + p[i].y);
			}
			vc.push_back(p[i]);
			i++;
		} else {
			if (p[j].type == 2) {
				//printf("%d %d\n", p[j].x + p[j].y, Query(p[j].y));
				ans[p[j]._time] = Min(ans[p[j]._time], p[j].x + p[j].y - Query(p[j].y));
			}
			vc.push_back(p[j]);
			j++;
		}
	}
	while (i <= mid) vc.push_back(p[i]), i++;
	while (j <= r) {
		if (p[j].type == 2) {
			//printf("%d %d\n", p[j].x + p[j].y, Query(p[j].y));
			ans[p[j]._time] = Min(ans[p[j]._time], p[j].x + p[j].y - Query(p[j].y));
		}
		vc.push_back(p[j]);
		j++;
	}
	//puts("}");
	for (i = l;i <= mid;i++) {
		if (p[i].type == 1) Remove(p[i].y);
	}
	for (i = l;i <= r;i++) p[i] = vc[i - l];
}

inline void Copy() {
	int maxx = 0, maxy = 0;
	for (register int i = 1;i <= n + m;i++) {
		if (q[i].type == 2) {
			maxx = Max(maxx, q[i].x);
			maxy = Max(maxy, q[i].y);
		}
	}
	ptop = 0;
	for (register int i = 1;i <= n + m;i++) {
		if (q[i].type == 2 || (q[i].x <= maxx && q[i].y <= maxy)) p[++ptop] = q[i];
	}
}

inline void Solve() {
	for (register int i = 1;i <= 1000010;i++) c[i] = -INF;
	Copy();
	cdq1(1, ptop);
	//for (register int i = 1;i <= m;i++) {
	//	if (ans[i] != 0x3f3f3f3f) printf("%d\n", ans[i]);
	//}
	for (register int i = 1;i <= n + m;i++) q[i].x = 1000002 - q[i].x;
	Copy();
	cdq1(1, ptop);
	for (register int i = 1;i <= n + m;i++) q[i].y = 1000002 - q[i].y;
	Copy();
	cdq1(1, ptop);
	for (register int i = 1;i <= n + m;i++) q[i].x = 1000002 - q[i].x;
	Copy();
	cdq1(1, ptop);
}

int main() {
	Read();
	memset(ans, 0x3f, sizeof(ans));
	
	// for (register int i = 1;i <= m;i++) {
	// 	if (ans[i] != 0x3f3f3f3f) printf("%d\n", ans[i]);
	// }
	
	// for (register int i = 1;i <= n + m;i++) {
	// 	printf("%d %d %d %d\n", p[i].type, p[i]._time, p[i].x, p[i].y);
	// }
	Solve();
	for (register int i = 1;i <= m;i++) {
		if (ans[i] != 0x3f3f3f3f) printf("%d\n", ans[i]);
	}
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}
```

---

## 作者：ADay (赞：3)

[更好的阅读体验](https://www.cnblogs.com/aday526/p/solution-p4169.html)  
## KD-Tree优化

相信 $\text{KD-Tree}$ 大家都会吧~~不会还来看这篇题解么~~，但普通的 $\text{KD-Tree}$ 并不能AC此题。所以我来讲一些优化。

### 1.建树优化

众所周知，$\text{KD-Tree}$ 是维护切割空间的数据结构，为了保持树高在 $\log n$ 范围，那么要怎么取切的点和切割方向呢？

先判断切割方向。我们要满足其维度的点差异度大，那么能维护的空间就更大了。差异度大就是**方差**大，所以计算两个维度的方差比较即可。

然后选切割的点——当然是中位数。我们可以用STL的`nth_element`来 $\mathcal O(n)$ 求出中位数并把比它小的数放它左边，比它大的数放在右边（即未完成的快排），然后递归建树即可。

Code:

```cpp
il void pushup(int u){
	mxx[u]=max(mxx[u],mxx[now]);mxy[u]=max(mxy[u],mxy[now]);
	mnx[u]=min(mnx[u],mnx[now]);mny[u]=min(mny[u],mny[now]);
}
il bool cmp(node p,node q){
    if(dcmp)return p.x<q.x;
    return p.y<q.y;
}
int build(int l,int r){
    if(l>r)return 0;
    int mid=(l+r)/2;
    double avx=0,avy=0,vax=0,vay=0;
    for(int i=l;i<=r;i++)
        avx+=a[i].x,avy+=a[i].y;
    avx/=1.0*(r-l+1);avy/=1.0*(r-l+1);
    for(int i=l;i<=r;i++)
        vax+=sqr(a[i].x-avx),vay+=sqr(a[i].y-avy);
    dcmp=d[mid]=(vax>vay);nth_element(a+l,a+mid,a+r+1,cmp);
    ls[mid]=build(l,mid-1);rs[mid]=build(mid+1,r);
    mxx[mid]=mnx[mid]=a[mid].x;
    mxy[mid]=mny[mid]=a[mid].y;
    if(ls[mid])now=ls[mid],pushup(mid);
    if(rs[mid])now=rs[mid],pushup(mid);
    return mid;
}
```

### 2.重构优化

即使有了建树优化，我们插入时也只能轮换分割，可能导致树高远远大于 $\log n$ 级别，那么在子树大小过大时，我们就要把这一部分重新分配，进行重构，即重新部分建树。

Code:

```cpp
il void pushup(int u){
	mxx[u]=max(mxx[u],mxx[now]);mxy[u]=max(mxy[u],mxy[now]);
	mnx[u]=min(mnx[u],mnx[now]);mny[u]=min(mny[u],mny[now]);
}
il double sqr(double x){return x*x;}
bool dcmp;
int g[maxn],tot;
il bool cmp(int p,int q){
    if(dcmp)return a[p].x<a[q].x;
    return a[p].y<a[q].y;
}
int build(int l,int r){
    if(l>r)return 0;
    int mid=(l+r)/2;
    double avx=0,avy=0,vax=0,vay=0;
    for(int i=l;i<=r;i++)
        avx+=a[g[i]].x,avy+=a[g[i]].y;
    avx/=1.0*(r-l+1);avy/=1.0*(r-l+1);
    for(int i=l;i<=r;i++)
        vax+=sqr(a[g[i]].x-avx),vay+=sqr(a[g[i]].y-avy);
    dcmp=d[g[mid]]=(vax>vay);nth_element(g+l,g+mid,g+r+1,cmp);
    ls[g[mid]]=build(l,mid-1);rs[g[mid]]=build(mid+1,r);
    mxx[g[mid]]=mnx[g[mid]]=a[g[mid]].x;
    mxy[g[mid]]=mny[g[mid]]=a[g[mid]].y;
    siz[g[mid]]=1;
    if(ls[g[mid]])now=ls[g[mid]],pushup(g[mid]),siz[g[mid]]+=siz[ls[g[mid]]];
    if(rs[g[mid]])now=rs[g[mid]],pushup(g[mid]),siz[g[mid]]+=siz[rs[g[mid]]];
    return g[mid];
}
void print(int u){//中序遍历
    if(!u)return;
    print(ls[u]);
    g[++tot]=u;
    print(rs[u]);
}
il void rebuild(int &u){
    tot=0;print(u);
    u=build(1,tot);
}
il bool bad(int u){
    return 0.725*siz[u]<=1.0*max(siz[ls[u]],siz[rs[u]]);
}
void ins(int &u,bool op){//在子树u中插入
	if(!u)return u=now,siz[u]=1,void();
	if(!op)ins(a[now].x<=a[u].x?ls[u]:rs[u],!d[u]);
	else ins(a[now].y<=a[u].y?ls[u]:rs[u],!d[u]);
	pushup(u);siz[u]=siz[ls[u]]+siz[rs[u]]+1;
    int tmp=now;if(bad(u))rebuild(u);now=tmp;
}
```

### 3.查询优化

剪枝就不用我说了吧，$\text{KD-Tree}$ 必备。

Code:

```cpp
il int dis(int u){
	return abs(a[now].x-a[u].x)+abs(a[now].y-a[u].y);
}
il int mindis(int u){//期望最小距离
    int res=0;
    if(mnx[u]>a[now].x||a[now].x>mxx[u])res+=mnx[u]>a[now].x?mnx[u]-a[now].x:a[now].x-mxx[u];
    if(mny[u]>a[now].y||a[now].y>mxy[u])res+=mny[u]>a[now].y?mny[u]-a[now].y:a[now].y-mxy[u];
    return res;
}
void ask(int u){
    if(!u)return;
    ans=min(ans,dis(u));
    int l=mindis(ls[u]),r=mindis(rs[u]);
    if(l<r){
        if(l<ans)ask(ls[u]);
        if(r<ans)ask(rs[u]);
    }else{
        if(r<ans)ask(rs[u]);
        if(l<ans)ask(ls[u]);
    }
}
```

完整代码：[https://www.luogu.com.cn/paste/9z0gpvy2](https://www.luogu.com.cn/paste/9z0gpvy2)。



---

## 作者：NuoCarter (赞：2)

[更好的阅读体验](https://www.luogu.com.cn/blog/NaCarter/solution-p4169)

# CDQ分治

作为一道离线分治的模板题，（貌似可以KD-Tree在线，但我不会）。

既然要离线做，那么肯定要获取整个操作序列。

## 前置芝士

**CDQ分治** 又叫 **基于时间的分治算法**（？书上这么说的（算法竞赛进阶指南））

对于每一个查询，计算 这个查询 的结果 其实就 等价于 **计算初始数据及在这次查询 之前的 所有修改**所带来的影响

计算方法：（以下来源算法竞赛进阶指南）

1.设 $mid=(l+r)>>1$ ,递归计算 $solve(l,mid)$

2 递归计算 $solve(mid+1,r)$

3 计算第$l~mid$项操作中的所有“修改”对第$mid+1$ ~ $r$ 项操作中所有“查询”造成的影响

**上述方法正确性的证明**

设第$k$项操作是“查询”。根据定义，若$k<=mid$，则$solve(l,mid)$已经计算了第$l$ ~ $k-1$ 项操作中的“修改”对它的影响。若$k>mid$，则$solve(mid+1,r)$计算到了第$mid+1$ ~ $k-1$项操作中的“修改”对它的影响，再加上第3部分的计算，即得到了第$l$ ~ $k-1$项操作中的修改对他的影响，故上述计算方法是正确的

## 题意

大致就是给你 $n$ 个初始点，有 $m$ 个操作，每次操作可以加入一个点或者进行一次查询，每次查询与给定的 $(x,y)$ 最近的点有多远

## 解决方法

曼哈顿距离公式：$\lvert x-x_i \lvert$ + $\lvert y-y_i \lvert$

根据第一我们要求的就是 $\lvert x-x_i \lvert$ + $\lvert y-y_i \lvert$ 的最小值，当然因为这个式子有一个绝对值，我能想到的带绝对值求解的话就一个暴力枚举。

所以为了去掉这个绝对值，我们可以将每一个询问都看作4个问题：

1.在$(x,y)$左上方的点最近的距离为？

2 在$(x,y)$右上方的点最近的距离为？ 

3 在$(x,y)$左下方的点最近的距离为？

4 在$(x,y)$右下方的点最近的距离为？

将上述问题的结果取一个最小值就行了

（将上面4个问题的距离公式化个简）

你就可以发现只用维护$(x+y)_{max}$和$(x-y)_{max}$就可以了


后面就是CDQ板子

唯一的难点就是树状数组维护了吧。。

### 树状数组维护

以下以左下方向计算为例

当然，你要先将整个点集按照 $x$ 坐标升序排序

（在哪里排序可以想想或者直接看代码）

1.扫到一个点$(x_i,y_i)$在树状数组中的第$y_i$个位置上更新值为$(x_i,y_i)$（取max操作）

2.扫到一个询问(x,y)	则在树状数组中查询$[0,y]$上的最大值 $val$
答案就为$x+y-val$

当你想到这剩下的应该就只有写代码的问题了。。

因为树状数组保存的是值域

**所以要开 $10^6$ 的空间，因为我懒，所以我全都开了**

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int c[1000005];
int maxn;
const int INF=0x3f3f3f3f;
struct node{int x,y,op;};
struct rec{int x,y,order;};
node a[1000005];
rec b[1000005];
int ans[1000005];
inline int lowbit(int x){return x&(-x);}
inline bool cmp(rec x,rec y){
	if(x.x!=y.x){
		return x.x<y.x;
	}
	return x.y<y.y;
}
inline void update(int x,int y){
	for(int i=x;i<maxn;i+=lowbit(i)){c[i]=max(c[i],y);}
	return;
}
inline int ask_max(int x){
	int ans=-INF;
	while(x>0){ans=max(ans,c[x]);x-=lowbit(x);}
	return ans;
}
inline void der(){
	for(int i=0;i<=maxn;++i){c[i]=-INF;}
	return;
}
inline void calculate(int fs,int fe,int tep,int bx,int by){
	int query;
	for(int i=fs;i!=fe;i+=tep){
		if(by==1){query=b[i].y;}
		else{query=maxn-b[i].y;}
		int goal=bx*b[i].x+by*b[i].y;
		if(a[b[i].order].op==1){update(query,goal);}
		else{ans[b[i].order]=min(ans[b[i].order],abs(goal-ask_max(query)));}
	}
	for(int i=fs;i!=fe;i+=tep){
		int y= by==1 ? b[i].y : maxn - b[i].y;
		if(a[b[i].order].op==1){
			for(int j=y;j<maxn;j+=lowbit(j))	c[j]=-INF;
		}
	}
	return;
}
inline void cdq(int l,int r){
	int mid=(l+r)>>1;
	if(l<mid){cdq(l,mid);}
	if(r>mid+1){cdq(mid+1,r);}
	int tot=0;
	for(int i=l;i<=r;++i){
		if(a[i].op==1&&i<=mid){
			b[++tot].x=a[i].x;
			b[tot].y=a[i].y;
			b[tot].order=i;
		}
		else if(a[i].op==2&&i>mid){
			b[++tot].x=a[i].x;
			b[tot].y=a[i].y;
			b[tot].order=i;
		}
	}
	sort(b+1,b+tot+1,cmp);
	calculate(1,tot+1,1,1,1);
	
	calculate(tot,0,-1,-1,-1);
	
	calculate(1,tot+1,1,1,-1);
	
	calculate(tot,0,-1,-1,1);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].op=1;
		a[i].y++;
		maxn=max(maxn,a[i].y);
	}

	for(int i=n+1;i<=n+m;++i){
		scanf("%d%d%d",&a[i].op,&a[i].x,&a[i].y);
		a[i].y++;
		maxn=max(maxn,a[i].y);
	}	
	maxn++;	
	memset(ans,0x3f3f3f3f,sizeof(ans));
	memset(c,0xcf,sizeof(c));
	cdq(1,n+m);
	for(int i=n;i<=n+m;++i){
		if(a[i].op==2){
			printf("%d\n",ans[i]);
		}
	}
	return 0;
}
```


---

## 作者：Booksnow (赞：2)

# CDQ分治算法

## 题目大意

有n个初始点，可以进行m次操作，每次操作可以插入一个点或是进行一次查询，问离点(x,y)**距离最近**的点有多远。

## CDQ算法

### 做法：

**若是已经知道这个算法可以跳过此部分**。

CDQ算法其实是一个**基于时间的分治**算法。

计算“**查询**”操作的结果，可以等价于计算“**初始数据**”和“**查询数据之前的所有修改**”对该查询**造成的影响**。

设共有M次操作 $\forall {l,r}\in{[1,M]}$,定义$solve(l,r)$表示第$k(k\in{[l,r]})$项操作是“查询”，则计算第$l~(k-1)$项操作中“**修改**”对它造成的影响。

$solve(l,r)$计算方法如下：

	   1.设mid=(l+r)>>1,递归计算solve(l,mid)。
       2.递归计算solve(mid+1,r)。
       3.计算第l~mid项操作中所有“修改”对第mid+1~r项操作中所有“查询”造成的影响。
       
### 证明：

设第$k$项操作是"查询"，**根据定义**：若$k\le mid$，则$solve(l,mid)$就**已经计算了**第$l~(k-1)$项操作中的 “修改”对它的影响。若$k>mid$，则$solve(mid+1,r)$计算了第$(mid+1)~(k-1)$项操作中的“修改”对它的影响。再加上第$3$部分，得到了$l~(k-1)$项操作中的“修改”对它的影响

### 小结

$solve(l,r)$的计算方法显然是一个**分治的过程**。    $solve(1,M)$是原始问题，当$l=r$时，$solve(l,r)$**只包含一项操作**，不需要进行任何计算，为递归边界。

实际上，该分治算法将一个动态问题划分成了$O(M)$个**静态问题**。

这种离线分治算法时基于“**时间**”顺序对操作序列进行分治的。因此称为基于时间的分治算法，又称为$CDQ$分治。

备注：$CDQ$分治是$IOI$金牌女选手**陈丹琦**在国家集训队中引入的。

## 解决方案

回到正题。

### 具体做法

问题是求离给出点**曼哈顿距离最近**的点，即：

$dis(A,B)=|A_x-B_x|+|A_y-B_y|$

我们可以假设**所有的点都在查询点的左下方**，则可以推得：

$dis(A,B)=(A_x-B_x)+(A_y-B_y)=(A_x+A_y)-(B_x+B_y)$

此时我们可以发现，只要求出$B_x<A_x$，$B_y<A_y$且$B_x+B_y$**最大**的点即可。

对于每个查询，可以把一、二、四象限的点都通过对称转移到第三象限。但**查询很多**，这样做的**时间复杂度**肯定**不对**。

我们可以考虑把整个平面**翻转三次**，进行**四次**$CDQ$分治，**每次都只考虑**第三象限的点，这样就能把**所有的点**都遍历到。

记录**最大**的$x$或$y$值为**边界**$Maxn$，每次沿$Maxn$翻转。例如沿$y$轴翻转时，$x=len-x$

那么每个操作有**三个维度**————时间、$x$坐标、$y$坐标，这个问题就被我们转化为了一个**三维偏序问题**，时间在输入的时候先排好序，$x$在分治的过程中排序，y则仿照三维偏序的模板题P3810 【模板】三维偏序（陌上花开），用**树状数组**记录即可。

### 注意

每次查询点的$x$，$y$会变化，$ans$**不能直接存储**$max(B_x+B_y)$，应该存入$min((A_x+A_y)-(B_x+B_y))$。

如果某个点在坐标轴上，那么它的$x$或$y$就会为$0$，存入树状数组时，会因为$lowbit()==0$陷入**死循环**，所以$x$，$y$要分别$+1$。

同样的，如果某个点**刚好**翻转在边界$Maxn$上，也会变成$0$，所以$Maxn$也要$+1$

若某一点在某次翻转时没有点在它的左下方，就会默认返回$0$。当前的“**原点**”比实际上的点离该查询点都近，这样最终的距离就成了这个点到原点的距离，但是原点经过刚才的更改后已经**不存在**了(不存在$x$，$y$为$0$的点)，为了避免这种情况，当查询时**需要特判**，若为0则返回$-INF$

## 结语

这道题**非常多细节**，写的时候需要**非常仔细**，否则~~一不小心就是一波爆零QwQ~~

还有就是用CDQ的话~~时间复杂度好像卡不过~~，~~常数有点大QwQ~~，可以开个$O_2$优化就过了。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1001001,INF=0x3f3f3f3f;
struct node{
	int x,y,opt;
}a[N];
struct BIT{
	int x,y,point;
}b[N];
int n,m,Maxn;
int tree[N],ans[N];
inline int lowbit(int x) { return x&(-x); }
inline bool cmp(BIT x,BIT y)	//排序 
{
	if(x.x!=y.x) return x.x<y.x;
	return x.y<y.y;
}
//树状数组 
inline void change(int x,int val)
{
	for(int i=x;i<Maxn;i+=lowbit(i))
		tree[i]=max(tree[i],val);
}
inline int Get_max(int x)
{
	int mx=-INF;
	for(int i=x;i;i-=lowbit(i))
		mx=max(mx,tree[i]);
	return mx;
}

inline void solve(int start,int end,int temp,int bx,int by){
	int instead;
	for(int i=start;i!=end;i+=temp){
		if(by==1){instead=b[i].y;}
		else{instead=Maxn-b[i].y;}
		int g=bx*b[i].x+by*b[i].y;
		if(a[b[i].point].opt==1){change(instead,g);}
		else{ans[b[i].point]=min(ans[b[i].point],abs(g-Get_max(instead)));}
	}
	for(int i=start;i!=end;i+=temp){
		int y=by;
		if(y==1&&by==1) y=b[i].y;
		else y=Maxn-b[i].y;
		if(a[b[i].point].opt==1){
			for(int j=y;j<Maxn;j+=lowbit(j))	
				tree[j]=-INF;		//最后一种特殊情况的处理 
		}
	}
	return;
}

inline void CDQ(int l,int r)
{
	int mid=(l+r)>>1;
	if(l<mid) CDQ(l,mid); 	//分治 
	if(r>mid+1) CDQ(mid+1,r);
	int tot=0;
	for(int i=l;i<=r;i++){
		if(a[i].opt==1&&i<=mid){
			b[++tot].x=a[i].x;
			b[tot].y=a[i].y;
			b[tot].point=i;
		}
		else{
			if(a[i].opt==2&&i>mid){
				b[++tot].x=a[i].x;
				b[tot].y=a[i].y;
				b[tot].point=i;
			}
		}
	}
	sort(b+1,b+tot+1,cmp);
	solve(1,tot+1,1,1,1);	//四次翻转平面 
	solve(tot,0,-1,-1,-1);
	solve(1,tot+1,1,1,-1);
	solve(tot,0,-1,-1,1);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].opt=1; a[i].y++;	//把输入也看成时一次修改操作； y++防止为零 
		Maxn=max(Maxn,a[i].y);		//记录边界 
	}
	for(int i=n+1;i<=n+m;i++){
		scanf("%d%d%d",&a[i].opt,&a[i].x,&a[i].y);
		a[i].y++; Maxn=max(Maxn,a[i].y);	//同上 
	}
	Maxn++;		//同样也是防止树状数组死循环 
	memset(ans,0x3f3f3f3f,sizeof(ans));
	memset(tree,0xcf,sizeof(tree));
	CDQ(1,n+m);		//CDQ 
	for(int i=n;i<=n+m;i++)
		if(a[i].opt==2) printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：devout (赞：1)

我们可以把每个点看成 $(x_i,y_i,t_i)$ 的三元组，其中 $t_i$ 表示时间，最开始的那一堆点的时间就是 $0$。

那么我们现在要求的就是对于每一个询问的 $i$，求满足 $t_j< t_i$ 时，$|x_i-x_j|+|y_i-y_j|$ 的最小值。

遇到绝对值，我们可以考虑把他拆开，首先考虑 $x_j\leq x_i,y_j\leq y_i$ 的情况，我们要求 $x_i-x_j+y_i-y_j$ 的最小，相当于在左下角找一个点让 $x_j+y_j$ 最大，这就是一个三位偏序问题，使用 cdq分治 来解决。

考虑其他的情况，我们都可以通过翻转来把他转化成第一个情况。

比如说 $x_j\geq x_i,y_j\leq y_i$ 的情况，就是相当于让每个 $x_i=-x_i$，然后再平移值域，然后再跑一遍 cdq。

所以四次 cdq 我们就可以在 $O(n\log^2n)$ 的时间里解决了。

注意一个坑就是当左下角没有点的时候，也就是我们树状数组查询到 $0$ 的时候，我们不能直接返回 $0$，要不然可能查询到的是从 $(x_i,y_i)$ 到 $(0,0)$ 的曼哈顿距离，这个时候应该返回 -inf。

哦对了，这题卡常（

```cpp
# include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(register int i=a;i<=b;i++)
# define _Rep(i,a,b) for(register int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=6e5+5;
const int W=1e6+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n,m,lx,ly;
int bit[W];
int out[N];

struct misaka{
	int x,y,t,opt;
	bool operator < (const misaka &cmp)const{
		return x<=cmp.x;
	}
}a[N],p[N],q[N];

void add(int o,int x){
	for(;o<=ly;o+=o&-o)bit[o]=max(bit[o],x);	
}

int ask(int o){
	int res=0;
	for(;o;o-=o&-o)res=max(res,bit[o]);
	return res?res:-1e9;	
}

void del(int o){
	for(;o<=ly;o+=o&-o)bit[o]=0;	
}

void CDQ(int l,int r){
	if(l==r)return;
	int mid=l+r>>1;
	CDQ(l,mid),CDQ(mid+1,r);
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r)
		if(p[i]<p[j]){
			if(p[i].opt==1)add(p[i].y,p[i].x+p[i].y);
			q[k++]=p[i++];	
		}
		else{
			if(p[j].opt==2)out[p[j].t]=min(out[p[j].t],p[j].x+p[j].y-ask(p[j].y));
			q[k++]=p[j++];	
		}
	while(i<=mid){
		if(p[i].opt==1)add(p[i].y,p[i].x+p[i].y);
		q[k++]=p[i++];
	}
	while(j<=r){
		if(p[j].opt==2)out[p[j].t]=min(out[p[j].t],p[j].x+p[j].y-ask(p[j].y));
		q[k++]=p[j++];		
	}
	Rep(i,l,mid)if(p[i].opt==1)del(p[i].y);
	Rep(i,l,r)p[i]=q[i]; 
}

int main()
{
	read(n),read(m);
	Rep(i,1,n){
		read(a[i].x),read(a[i].y);
		a[i].opt=1;
		a[i].x++,a[i].y++;
		lx=max(lx,a[i].x),ly=max(ly,a[i].y);	
	}
	Rep(i,1,m){
		read(a[n+i].opt);
		read(a[n+i].x),read(a[n+i].y);
		a[n+i].x++,a[n+i].y++;
		lx=max(lx,a[n+i].x),ly=max(ly,a[n+i].y);
		a[n+i].t=i;
	}
	lx++,ly++;
	memset(out,0x3f,sizeof(out));
	Rep(i,1,n+m)p[i]=a[i];
	CDQ(1,n+m);
	Rep(i,1,n+m)p[i]=a[i];
	Rep(i,1,n+m)p[i].x=lx-p[i].x;
	CDQ(1,n+m);
	Rep(i,1,n+m)p[i]=a[i];
	Rep(i,1,n+m)p[i].y=ly-p[i].y;
	CDQ(1,n+m);
	Rep(i,1,n+m)p[i]=a[i];
	Rep(i,1,n+m)p[i].x=lx-p[i].x;
	Rep(i,1,n+m)p[i].y=ly-p[i].y;
	CDQ(1,n+m);
	Rep(i,n+1,n+m)
		if(a[i].opt==2)printf("%d\n",out[a[i].t]);
	return 0;
}
```


---

## 作者：Celtic (赞：0)

啥优化都没有的 CDQ 分治也能通过本题 [link](https://www.luogu.com.cn/record/45666191)。

这题我们把每次询问和修改都新建一个点，总点数是 $n+m$ 。

然后对于每次询问，找在这个询问点左下角，且时间戳在他之前的点离他最近的点，这是一个三维偏序，用 cdq 分治解决。

但是还有其他三个方向的点呢？

这时候我们来一发黑科技，找到 $x$ 和 $y$ 分别的最大值，将所有点关于这两条直线对称（就是 $x=maxn-x$），然后做 $4$ 次 cdq 就行了。

细节见代码

```cpp
#include<bits/stdc++.h>
#define re register
#define N 1001001
#define MAX 2001
#define inf 1e18
using namespace std;
typedef long long ll;
typedef double db;
inline void read(re ll &ret)
{
	ret=0;re char c=getchar();re bool pd=false;
	while(!isdigit(c)){pd|=c=='-';c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
	ret=pd?-ret:ret;
	return;
}
ll n,m,op[N],fx[N],fy[N],maxnx,maxny;
struct node
{
	ll x,y,tim,ans;
	bool q;
	inline friend bool operator <(re node x,re node y)
	{
		return x.tim<y.tim;
	}
}a[N],tmp[N];
ll tree[N];
inline void update(re ll pos,re ll num)
{
	pos++;
	while(pos<=maxny+1)
	{
		tree[pos]=max(tree[pos],num);
		pos+=pos&-pos;
	}
	return;
}
inline void clear(re ll pos)
{
	pos++;
	while(pos<=maxny+1)
	{
		tree[pos]=-inf;
		pos+=pos&-pos;
	}
	return;
}
inline ll query(re ll pos)
{
	pos++;
	re ll ret=-inf;
	while(pos)
	{
		ret=max(ret,tree[pos]);
		pos-=pos&-pos;
	}
	return ret;
}
inline void cdq(re ll l,re ll r)
{
	if(l>=r)
		return;
	re ll mid=l+r>>1;
	cdq(l,mid);
	cdq(mid+1,r);
	re ll i=l,j=mid+1,k=l;
	while(j<=r)
	{
		while(i<=mid&&a[i].x<=a[j].x)
		{
			if(!a[i].q)
				update(a[i].y,a[i].x+a[i].y);
			tmp[k++]=a[i++];
		}
		a[j].ans=min(a[j].x+a[j].y-query(a[j].y),a[j].ans);
		tmp[k++]=a[j++];
	}
	while(i<=mid)
	{
		if(!a[i].q)
			update(a[i].y,a[i].x+a[i].y);
		tmp[k++]=a[i++];
	}
	for(i=l;i<=mid;i++)
		if(!a[i].q)
			clear(a[i].y);
	for(i=l;i<=r;i++)
		a[i]=tmp[i];
	return;
}
signed main()
{
	read(n);
	read(m);
	for(re int i=1;i<N;i++)
		tree[i]=-inf;
	for(re int i=1;i<=n;i++)
	{
		read(a[i].x);
		read(a[i].y);
		a[i].q=false;
		maxnx=max(maxnx,a[i].x);
		maxny=max(maxny,a[i].y);
		a[i].tim=0;
	}
	for(re int i=1;i<=m;i++)
	{
		read(op[i]);
		read(fx[i]);
		read(fy[i]);
		if(op[i]==1)
			a[n+i].q=false;
		else
			a[n+i].q=true;
		a[n+i].ans=inf;
		a[n+i].x=fx[i],a[n+i].y=fy[i];
		a[n+i].tim=i;
		maxnx=max(maxnx,fx[i]);
		maxny=max(maxny,fy[i]);
	}
	n+=m;
	cdq(1,n);
	sort(a+1,a+n+1);
	for(re int i=1;i<=n;i++)
		a[i].x=maxnx-a[i].x;
	cdq(1,n);
	sort(a+1,a+n+1);
	for(re int i=1;i<=n;i++)
		a[i].x=maxnx-a[i].x,a[i].y=maxny-a[i].y;
	cdq(1,n);
	sort(a+1,a+n+1);
	for(re int i=1;i<=n;i++)
		a[i].x=maxnx-a[i].x;
	cdq(1,n);
	sort(a+1,a+n+1);
	n-=m;
	for(re int i=1;i<=m;i++)
		if(op[i]==2)
			printf("%lld\n",a[n+i].ans);
	exit(0);
}
```


---

## 作者：mohei0 (赞：0)

# 天使玩偶

## 题意

给出一些点，给定坐标求与已有点最短曼哈顿距离，动态添加询问，可离线

$n,m\le 3e5$

## 分析

这题还是很水的，只要方向对了就想得出来

先把曼哈顿距离式子列出来

$$dis(A,B)=|A_x-B_x|+|A_y-B_y| $$

这个绝对值感觉很难处理掉，如果我们单纯去掉绝对值会发生什么呢？

当 $dis(A,B)=A_x-B_x+A_y-B_y$ 时，需要满足的条件是 $B$ 在 $A$ 的左下方，设一个点 $X$ 出现的时间为 $X_t$ ，也就是 $B$ 需要满足 $B_t\le A_t,B_x\le A_x,B_y\le A_y$

怎么这么眼熟？

这不就是三维偏序吗？！这不就是 $cdq$ 分治吗？！

我们考虑 $cdq$ 分治，默认的 $t$ 已经帮你排序好了，用 $cdq$ 排序 $x$ 

考虑如何合并左右 $cdq$ 

首先右侧点 $x$ 大于左侧点，那么我们只要看 $y$ 大小即可

我首先选择了 $cdq$ 套 $cdq$ 来处理 $y$ ，对于一个点记录 $lr$ 在 $cdq_1$ 中是左侧点 $(0)$ 还是右侧点 $(1)$ ，然后 $cdq_2$ 按 $y$ 进行排序

在 $cdq_2$ 的归并中对于所有左侧点中 $lr=0$ 的插入点 $A$ ，记录这些点的 $-A_x-A_y$ 最小值

对于所有右侧点中 $lr=1$ 的询问点 $B$ ，将目前的最小值加上 $+B_x+B_y$ ，和变量 $B_{ans}$ 取 $min$

处理完后 $B_{ans}$ 就是和左下点的最小距离了

记录最小值是 $O(1)$ 的效率， $cdq$ 套 $cdq$ 是 $O(n\log^2 n)$ 的效率，总效率 $O(n\log^2 n)$

那如何处理询问点到其他方向的点的距离呢？

我们把 $cdq$ 的排序改一下就行了，把从小到大变成从大到小之类的，然后再把最小值的计算改一下就好了

由于反复做 $cdq$ 是乘一个常数的复杂度，所以总复杂度还是 $O(n\log^2 n)$

那这样就可以过了吗？

![无标题.png](https://i.loli.net/2019/08/31/jIXLmvZgMnaPsS1.png)

这是已经尽我所能卡常后的代码，各种吸气体都有了

这题本来就卡常，再加上cdq常数比树状数组稍微多了一些，就爆炸了

### 优化

把 $cdq$ 套 $cdq$ 这种奇怪的东西改成 $cdq$ 套树状数组，因为我们要的是前缀最小值，所以不需要线段树

我最开始写嵌套的原因是思路不清，但理论复杂度这两个是一样的，卡常题太恶心了wsl

还有一个降常数的优化是在处理不同方向的点的方法

我最开始是用各种判断来处理不同方向，一个方向一种 $cdq$ ，导致代码中 $if,switch$ 语句众多。但是看完其他题解发现一种更简单的方法，改坐标！

我们直接改坐标即可，像旋转坐标系一样，这里旋转的度数都是直角，所以更简单了

这两个优化就是最有效的优化了

其他优化：

树状数组手动删除时只删插入过的点，不要太暴力的删除

$inline,register,O2,O3,Ofast$ 等常规卡常

理论复杂度优化：

能降理论复杂度的优化！

我们注意到 $n,m$ 的数字都很大，如果加起来处理的话复杂度具体为 $O((n+m)\log(n+m)\log(K))$

注：为了表述方便坐标值域设为 $K$

我们将前 $n$ 个点改完坐标后按 $x$ 第一关键字 $y$ 第二关键字排序。然后遍历一遍 $m$ 看询问点在前 $n$ 个点中的答案，然后 $cdq$ 处理后 $m$ 个点

复杂度为 $O(n\log n+m\log K+m\log m\log K)=O(m\log m\log K)$

前者 $(n+m)\log (n+m)\log K\approx 2.4e8$

后者 $m\log m\log K\approx 1.14e8$

差了一个亿多

但常数之类的影响就很迷了

所以这个优化很迷

AC代码(不带最后一种优化)

```cpp
// luogu-judger-enable-o2
#pragma GCC optimize(3,"Ofast","inline")

#include<bits/stdc++.h>

#define rg register

using namespace std;

const int MAXN=6e5+1,M=1e6+2;

int tr[M+7];
inline void add(rg int pos,rg int X) {
    for(rg int i=pos;i<=M;i+=i&-i) tr[i]=min(tr[i],X);
}
inline void del(rg int pos) {
    for(rg int i=pos;i<=M;i+=i&-i) tr[i]=1e9;
}
inline int find(rg int pos) {
    rg int minn=1e9;
    for(rg int i=pos;i>0;i-=i&-i) minn=min(minn,tr[i]);
    return minn;
}

int n,m;

struct node {
    int x,y,pos,XY;
    bool type,add; //type:0插入点,1询问点
}A[MAXN],B[MAXN],D[MAXN];

int ans[MAXN];

int MINN=1e9,K;

void cdq(rg int l,rg int r) {
    if(l==r) return;
    rg int mid=(l+r)>>1;
    cdq(l,mid);cdq(mid+1,r);
    for(rg int i=l,i2=l,i3=mid+1;i<=r;i++) {
        if((A[i2].x<=A[i3].x&&i2<=mid)||i3>r) {
            B[i]=A[i2];
            if(B[i].type==0) add(B[i].y,-B[i].XY);
            B[i].add=1;
            i2++;
        }
        else {
            B[i]=A[i3];
            if(B[i].type==1) ans[B[i].pos]=min(ans[B[i].pos],find(B[i].y)+B[i].XY);
            i3++;
        }
    }
    for(rg int i=l;i<=r;i++) {
        A[i]=B[i];
        if(B[i].type==0&&B[i].add) del(A[i].y);
        A[i].add=0;
    }
}

inline int read() {
    rg int A=0;
    rg char ch='!';
    while(ch<'0'||ch>'9')
        ch=getchar();
    while(ch>='0'&&ch<='9') {
        A=A*10+ch-'0';
        ch=getchar();
    }
    return A;
}

void out(rg int A) {
    if(A/10) out(A/10);
    putchar(A%10+'0');
}

int main() {
    memset(ans,0x3f,sizeof(ans));
    memset(tr,0x3f,sizeof(tr));
    n=read();m=read();
    for(rg int i=1;i<=n;i++) {
        D[i].x=read();D[i].y=read();
        D[i].x++;D[i].y++;
        D[i].XY=D[i].x+D[i].y;
        D[i].type=0;
    }
    rg int cnt=1;
    for(rg int i=1,i2;i<=m;i++) {
        i2=read();D[i+n].x=read();D[i+n].y=read();
        D[i+n].type=i2-1;
        D[i+n].x++;D[i+n].y++;
        D[i+n].XY=D[i+n].x+D[i+n].y;
        if(D[i+n].type==1) {
            D[i+n].pos=cnt;
            cnt++;
        }
    }

    for(rg int i=1;i<=n+m;i++) {
        A[i]=D[i];
    }
    cdq(1,n+m);
    
    for(rg int i=1;i<=n+m;i++) {
        A[i]=D[i];
        A[i].x=M-D[i].y;A[i].y=D[i].x;
        A[i].XY=A[i].x+A[i].y;
    }
    cdq(1,n+m);

    for(rg int i=1;i<=n+m;i++) {
        A[i]=D[i];
        A[i].x=M-D[i].x;A[i].y=M-D[i].y;
        A[i].XY=A[i].x+A[i].y;
    }
    cdq(1,n+m);

    for(rg int i=1;i<=n+m;i++) {
        A[i]=D[i];
        A[i].x=D[i].y;A[i].y=M-D[i].x;
        A[i].XY=A[i].x+A[i].y;
    }
    cdq(1,n+m);
    
    for(rg int i=1;i<cnt;i++) {
        out(ans[i]);
        putchar('\n');
    }
}
```

---

## 作者：BlankAo (赞：0)

文章刚刚挂了，现已修复。

$\Large\natural$ **P4169 [Violet]天使玩偶,SJY摆棋子 / [原题链接](https://www.luogu.com.cn/problem/P4169) / [更好阅读体验](https://www.cnblogs.com/BlankAo/p/14507879.html)**

## 题意

~~由于特殊原因，加了个题意简述~~

一开始有 $n$ 个关键点 $(a,b)$。然后有 $T$ 个操作：

- 多出一个关键点 $(a,b)$。
- 询问如果我站在 $(x,y)$，最近的关键点距离我多远。（这里的距离是**曼哈顿距离**）

$n,T\le 3\times 10^5$，以及 $0\le a,b,x,y\le 10^6$。

## 解法

一开始的 $n$ 个点直接当修改操作。

曼哈顿距离表示是 $|x_1-x_2|+|y_1-y_2|$，这显然不好算。一般对于曼哈顿距离有两种解决方案，一种是转成切比雪夫距离，另一种是**拆绝对值**。我们看到这题有修改操作，想到拆绝对值更方便一些。

对于询问操作，我们分**四种情况**讨论（最近的点在我的左上 / 右上 / 左下 / 右下）。看到题目有三个维度 $x,y,t$，我们可以想到 **CDQ分治**。

---

下面以**点在我右上角**为例。

对于每一个询问 $(x,y)$，其它点处我的距离是：
$$
|x-a|+|y-b|=a-x+b-y=a+b-x-y
$$
$x,y$ 是不会变的，我们只用找到 $a+b$ 的最小值即可。

按照 **CDQ分治** 的套路，我们已经把区间一分为二。对于每个区间，我们以 $x$ 为第一关键字， $y$ 为第二关键字**排序**操作。

我们的目的是，查询 $(x,y)$ 右上角的点中 $a+b$ 最小值，我们可以用**线段树**维护。

然后每次把 $a\ge x$ 的修改都加入（给 $b$ 这个位置更新 $a+b$ 权值）。这个时候所有的关键点肯定都在 $(x,y)$ 的**右边**。而查询 $y\sim \inf$ 就保证了关键点在 $(x,y)$ 的**上方**，所以就查询到了右上角啦~

最后根据套路，记得**清空线段树**。

---

其它三个方位都是类似的，只用稍微改一下**排序方式、枚举方式、线段树更新权值、线段树查询区间**就行了。看似很复杂，但只要多在纸上画画图就可以清晰地打完题目了。



### 代码

注意因为一开始的关键点都当修改操作了，所以存操作的数组空间得**开两倍**。

数组要清空为极大值。

```c++
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;++i)
using namespace std;
const int n7=601234,t7=4012345,hug=1000000;
struct dino{int sys,x,y,id;}qq[n7];
int n,T,tre[t7],ans[n7];

int rd(){
    int shu=0;char ch=getchar();
    while( !isdigit(ch) )ch=getchar();
    while( isdigit(ch) )shu=(shu<<1)+(shu<<3)+(ch^48),ch=getchar();
    return shu;
}

void updat(int o,int l,int r,int id,int x){
	if(l==r){tre[o]=x;return;}
	int mid=(l+r)>>1;
	if(id<=mid)updat(o<<1,l,mid,id,x);
	else updat(o<<1|1,mid+1,r,id,x);
	tre[o]=min(tre[o<<1],tre[o<<1|1]);
} 

int query(int o,int l,int r,int L,int R){
	if(L<=l&&r<=R)return tre[o];
	int mid=(l+r)>>1,fin=INT_MAX;
	if(L<=mid)  fin=query(o<<1,l,mid,L,R);
	if(R>=mid+1)fin=min(fin, query(o<<1|1,mid+1,r,L,R) );
	return fin;
}

bool cmp1(dino p,dino q){return p.x==q.x?p.y>q.y:p.x>q.x;}

bool cmp2(dino p,dino q){return p.x==q.x?p.y>q.y:p.x<q.x;}

bool cmp3(dino p,dino q){return p.x==q.x?p.y<q.y:p.x<q.x;}

bool cmp4(dino p,dino q){return p.x==q.x?p.y<q.y:p.x>q.x;}

void CDQ(int l,int r){
	if(l==r||r<=n)return;
	int mid=(l+r)>>1,L;
	CDQ(l,mid),CDQ(mid+1,r);

	//点在我站位右上角 
	sort(qq+l,qq+mid+1,cmp1);
	sort(qq+mid+1,qq+r+1,cmp1);
	L=l;
	rep(i,mid+1,r){
		if(qq[i].sys==1)continue;
		while(qq[L].x>=qq[i].x&&L<=mid){
			if(qq[L].sys==1)updat(1,0,hug,qq[L].y,qq[L].x+qq[L].y);
			L++;
		}
		ans[ qq[i].id ]=min(ans[ qq[i].id ],query(1,0,hug,qq[i].y,hug)-qq[i].x-qq[i].y);
	}
	rep(i,l,L-1){
		if(qq[i].sys==1)updat(1,0,hug,qq[i].y,tre[0]);
	}
	
	//点在我站位左上角 
	sort(qq+l,qq+mid+1,cmp2);
	sort(qq+mid+1,qq+r+1,cmp2);
	L=l;
	rep(i,mid+1,r){
		if(qq[i].sys==1)continue;
		while(qq[L].x<=qq[i].x&&L<=mid){
			if(qq[L].sys==1)updat(1,0,hug,qq[L].y,-qq[L].x+qq[L].y);
			L++;
		}
		ans[ qq[i].id ]=min(ans[ qq[i].id ],query(1,0,hug,qq[i].y,hug)+qq[i].x-qq[i].y);
	}
	rep(i,l,L-1){
		if(qq[i].sys==1)updat(1,0,hug,qq[i].y,tre[0]);
	}
	
	//点在我站位左下角 
	sort(qq+l,qq+mid+1,cmp3);
	sort(qq+mid+1,qq+r+1,cmp3);
	L=l;
	rep(i,mid+1,r){
		if(qq[i].sys==1)continue;
		while(qq[L].x<=qq[i].x&&L<=mid){
			if(qq[L].sys==1)updat(1,0,hug,qq[L].y,-qq[L].x-qq[L].y);
			L++;
		}
		ans[ qq[i].id ]=min(ans[ qq[i].id ],query(1,0,hug,0,qq[i].y)+qq[i].x+qq[i].y);
	}
	rep(i,l,L-1){
		if(qq[i].sys==1)updat(1,0,hug,qq[i].y,tre[0]);
	}
	
	//点在我站位右下角 
	sort(qq+l,qq+mid+1,cmp4);
	sort(qq+mid+1,qq+r+1,cmp4);
	L=l;
	rep(i,mid+1,r){
		if(qq[i].sys==1)continue;
		while(qq[L].x>=qq[i].x&&L<=mid){
			if(qq[L].sys==1)updat(1,0,hug,qq[L].y,qq[L].x-qq[L].y);
			L++;
		}
		ans[ qq[i].id ]=min(ans[ qq[i].id ],query(1,0,hug,0,qq[i].y)-qq[i].x+qq[i].y);
	}
	rep(i,l,L-1){
		if(qq[i].sys==1)updat(1,0,hug,qq[i].y,tre[0]);
	}
}

int main(){
	n=rd(),T=rd();
	rep(i,1,n)qq[i]=(dino){1,rd(),rd(),0};
	rep(i,n+1,n+T)qq[i]=(dino){rd(),rd(),rd(),i-n};
	memset(ans,0x3f,sizeof ans);
	memset(tre,0x3f,sizeof tre);
	CDQ(1,n+T);
	rep(i,1,T){
		if(ans[i]^ans[0])printf("%d\n",ans[i]);
	}
	return 0;
}

```



---

## 作者：LevenKoko (赞：0)

#### CDQ分治~~归并排序写错调了一天可海星~~
### [在我的博客查看](https://www.cnblogs.com/zhenglw/p/11238721.html)

考虑哈夫曼距离特点：

$$dis(A,B)=|A_x-B_x|+|A_y-B_y|$$

若能够把绝对值去掉岂不是很妙！

$$dis(A,B)=(A_x+A_y)-(B_x+B_y)$$

由于A坐标已经定下来了，我们只要找B坐标使得$B_x+B_y$ 最大，就可以是距离最小了！

然后套上CDQ三维偏序求解就好了

因为不一定每个点都在当前询问点的左下方

（也就是说绝对值不能直接去掉，我们把所有点转个方向再做3遍就吼了）


Tip:这道题卡常，请使用归并排序，并且求解区间最值时不要使用线段树，改用树状数组！！

（虽然某人说正常人用的都是树状数组，可我开始就是用线段树了..）

```cpp
#include<bits/stdc++.h>
#define lowbit(x) ((x)&(-x))
#define writeln(x)  write(x),puts("")
#define writep(x)   write(x),putchar(' ')
using namespace std;
inline int read(){
    int ans=0,f=1;char chr=getchar();
    while(!isdigit(chr)){if(chr=='-') f=-1;chr=getchar();}
    while(isdigit(chr)){ans=(ans<<3)+(ans<<1)+chr-48;chr=getchar();}
    return ans*f;
}void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}const int M = 1e6+5;
int n,m,tot,s[M],maxx,maxy,maxn,ans[M];
struct P{int x,y,id,type;}q[M],p[M],h[M];
inline void cmax(int &x,int y){if(x<y)x=y;}
inline void cmin(int &x,int y){if(x>y)x=y;}
inline void Add(int x,int y)    {for(;x<=maxn;x+=lowbit(x))cmax(s[x],y);}
inline void Clear(int x)        {for(;x<=maxn;x+=lowbit(x))s[x]=0;}
inline int  Max(int x){int ans=0;for(;x;x-=lowbit(x))cmax(ans,s[x]);return ans;}
void Solve(int l,int r){
    if(l==r) return;
    int mid=l+r>>1;
    Solve(l,mid),Solve(mid+1,r);
    int j=l,ll=l,rr=mid+1,nn=l-1;
    for(int i=mid+1;i<=r;i++){
        while(i<=r&&p[i].type!=2) ++i;if(i>r) break;
        for(;j<=mid&&p[j].x<=p[i].x;++j)if(p[j].type==1)Add(p[j].y,p[j].y+p[j].x);
        int t=Max(p[i].y);
        if(t) cmin(ans[p[i].id],p[i].x+p[i].y-t);
    }
    for(int i=l;i<j;i++)if(p[i].type==1) Clear(p[i].y);
    while(ll<=mid&&rr<=r){
    	if(p[ll].x<=p[rr].x) h[++nn]=p[ll++];
    	else h[++nn]=p[rr++];
	}
	while(ll<=mid) h[++nn]=p[ll++];
	while(rr<=r)   h[++nn]=p[rr++];
	for(int i=l;i<=r;i++) p[i]=h[i];
}
int main(){
    n=read(),m=read();
    for(int x,y,i=1;i<=n;i++)
    	x=read(),y=read(),q[++tot]=(P){x+1,y+1,i,1},cmax(maxx,x+1),cmax(maxy,y+1);
    for(int x,y,opt,i=1;i<=m;i++){
        opt=read(),x=read(),y=read();
        cmax(maxx,x+1),cmax(maxy,y+1);
        if(opt==1)	q[++tot]=(P){x+1,y+1,i+n,1};
        else q[++tot]=(P){x+1,y+1,i+n,2};
    }n+=m;memset(ans,0x3f,sizeof(ans));
    maxn=max(maxx,maxy)+1;
    for(int i=1;i<=n;i++) p[i]=q[i];
	Solve(1,n);
    for(int i=1;i<=n;i++) p[i]=q[i],p[i].x=maxn-p[i].x;
    Solve(1,n);
    for(int i=1;i<=n;i++) p[i]=q[i],p[i].y=maxn-p[i].y;
    Solve(1,n);
    for(int i=1;i<=n;i++) p[i]=q[i],p[i].x=maxn-p[i].x,p[i].y=maxn-p[i].y;
    Solve(1,n);
    for(int i=1;i<=n;i++)if(q[i].type==2) printf("%d\n",ans[i]);
    return 0;
}
```

---

