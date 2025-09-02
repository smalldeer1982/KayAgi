# [IOI 2018] seats 排座位

## 题目背景

本题为交互题，但在此请提交**完整程序**。

## 题目描述

你要在一个长方形大厅里举办国际编程比赛，该大厅共有 $HW$ 个座位（$H$ 行 $W$ 列）。行的编号是从 $0$ 到 $H-1$，列的编号是从 $0$ 到 $W-1$。位于 $r$ 行 $c$ 列的座位用 $(r,c)$ 表示。一共邀请了 $HW$ 位参赛者，编号是从 $0$ 到 $HW-1$。你制定好了一个座位表，第 $i(0 \leq i \leq HW - 1)$ 个参赛者被安排到座位 $(R_i,C_i)$。座位表中参赛者和座位是一一对应的。

大厅中一个座位集合 $S$ 被称为是**长方形的**，如果存在整数 $r_1, r_2, c_1$ 和 $c_2$ 满足下列条件：

- $0 \leq r_1 \leq r_2 \leq H - 1$。
- $0 \leq c_1 \leq c_2 \leq W - 1$。
- $S$ 正好是所有满足 $r_1 \leq r \leq r_2$ 和 $c_1 \leq c \leq c_2$ 的座位 $(r, c)$ 的集合。

如果一个长方形座位集合包含 $k(1 \leq k \leq HW)$ 个座位，并且被分配到这个集合的参赛者的编号恰好是从 $0$ 到 $k-1$，那么该集合是**美妙的**。一个座位表的**美妙度**定义为这个表中美妙的长方形座位集合的个数。

在准备好座位表后，你会收到一些交换两个参赛者座位的请求。具体来说，有 $Q$ 个这样的请求，按时间顺序编号为 $0$ 到 $Q-1$。第 $j(0 \leq j \leq Q - 1)$ 个请求希望交换参赛者 $A_j$ 和 $B_j$ 的座位。你立即接受每个请求并更新座位表。每次更新后，你的目标是计算当前座位表的美妙度。

## 说明/提示

**限制条件**

- $1 \leq H$
- $1 \leq W$
- $HW \leq 1, 000, 000$
- $0 \leq R_i \leq H - 1(0 \leq i \leq HW - 1)$
- $0 \leq C_i \leq W - 1(0 \leq i \leq HW - 1)$
- $(R_i, C_i) \neq (R_j, C_j)(0 \leq i < j \leq HW - 1)$
- $1 \leq Q \leq 50, 000$
- $0 \leq A_j \leq HW - 1(0 \leq j \leq Q - 1)$
- $0 \leq B_j \leq HW - 1(0 \leq j \leq Q - 1)$
- $A_j \neq B_j(0 \leq j \leq Q - 1)$

**子任务**

- 1.（5 分） $HW \leq 100$，$Q \leq 5, 000$
- 2.（6 分） $HW \leq 10, 000$，$Q \leq 5, 000$
- 3.（20 分） $H \leq 1, 000$，$W \leq 1, 000$，$Q \leq 5, 000$
- 4.（6 分） $Q \leq 5, 000$，$|A_j - B_j| \leq 10, 000(0 \leq j \leq Q - 1)$
- 5.（33 分） $H = 1$
- 6.（30 分） 无附加限制条件

## 样例 #1

### 输入

```
2 3 2
0 0
1 0
1 1
0 1
0 2
1 2
0 5
0 5
```

### 输出

```
3
4
```

## 样例 #2

### 输入

```
1 5 3
0 0
0 1
0 2
0 3
0 4
0 1
0 3
4 0
```

### 输出

```
5
3
2
```

# 题解

## 作者：liuzhangfeiabc (赞：32)

题目大意：给定一个n×m的矩阵，矩阵中不重不漏地分布着0~n×m-1的元素。称一个大小为s的连续子矩阵是好的当且仅当其中不重不漏地出现了0~s-1的元素。每次交换矩阵中的两个元素，查询当前有多少个好的子矩阵。强制在线。

这题容易给人一种奇技淫巧的数据结构的感觉。那么到底该用什么数据结构，维护什么信息？

我们发现我们可以通过维护前i个元素在矩阵中位置分布相关的信息，来检验前i个元素是否能组成合法子矩阵。

开一棵线段树，其下标为i的位置维护的是前i个元素的信息。

那么问题来了，我们需要维护什么信息，能够支持修改和快速计算答案？

这确实是一个棘手的问题。估计ioi现场应该很多人都跪在这一步了。

我一开始的想法是，维护前i个元素所组成的图形的周长。后来发现据此并不能直接计算答案（一个大小一定的矩形其周长也可能有多种可能），遂放弃。

后来我想到一种“看似可行”的思路：维护前i个元素的x、y坐标的最小值和最大值，这样前i个元素组成合法子矩形当且仅当(xmax - xmin + 1) × (ymax - ymin + 1) = s。

这样我们将每个位置的值设为(xmax - xmin + 1) × (ymax - ymin + 1) - i，这个数一定非负，当且仅当它为0时答案合法。

然而这个想法在修改时遇到了麻烦：交换两个元素，可能导致一个区间的max和min值发生大规模变化，尤其是当把原来的最值移动到后面时，可能造成区间内最值的多次改变，我们可能面临每次操作O(n)次修改。

目前我还没有想到合适的方法来维护这个东西，如果有大神会维护的话麻烦在评论中留言谢谢。

那怎么办？我们有一个绝妙的思路：通过维护“特殊点”的信息来实现快速修改和判断合法性的目的！

为了方便，我们现在对于一个位置i，将前i个点染成黑色，后面的点为白色。

我们维护这么两个东西：

1、所有的黑点中，有多少个点的左侧和上侧都不挨着黑点（可能是白点或边缘）。

2、所有的白点中，有多少个点的周围四连通地挨着超过2个黑点。

这两个信息能说明什么？

首先，容易证明所有的合法子矩阵都满足：第一个信息为1，第二个信息为0。接下来我们证明：一个非法的图形不可能同时满足以上两个条件。

容易看出，对于每个黑点组成的四连通块，我们总能选出其最左上的点（至少一个，也可能一个连通块中有多个合法点），使得它的左边和上边都不是黑点。也就是说，黑色连通块数量<=信息1。

因此，一个有>=2个连通块的图形不可能满足信息1数量为1。

再来考虑一个连通块但不是矩形的图形。容易发现这个图形一定存在如下的“拐角”：

xxoo

xxoo

xxxx

xxxx

x表示黑点，o表示白点，2行3列那个白点就是“拐角”。而在拐角处的白点满足信息2。

也就是说，存在拐角的图形不可能满足信息2数量为0。

那么同时满足1和2的图形，就只有“一个连通块且不存在拐角”的图形了——也就是矩形！

这样我们就证明了条件的充要性。那么怎么维护呢？

我们直接维护两个信息的和（这个和显然是正整数），然后统计有多少个位置答案为1。

交换两个位置时，我们可以把预制相邻的所有位置都拿出来（最多不超过10个，注意去重），然后暴力地对每个位置，先扣去原来对信息的贡献，再加上操作后对信息的贡献。对应在线段树上就是O(1)次区间修改。

至于查询区间有多少个1，我们可以用类似维护矩形面积并的方式，记录区间最小值和最小值的个数。

于是我们就成功地用九省省选难度的数据结构解决了这道难题！

```cpp
#include<bits/stdc++.h>
using namespace std;
#define gc getchar()
#define pc putchar
#define li long long
li read(){
	li x = 0,y = 0,c = gc;
	while(!isdigit(c)) y = c,c = gc;
	while(isdigit(c)) x = (x << 1) + (x << 3) + (c ^ '0'),c = gc;
	return y == '-' ? -x : x;
}
void print(li q){
	if(q < 0) pc('-'),q = -q;
	if(q >= 10) print(q / 10);
	pc(q % 10 + '0');
}
int n,m,p,k,jz[1000010],vl[1000010];
struct wz{
	int x,y;
}a[1000010];
int t[4000010],s[4000010],c[4000010];
#define ls q << 1
#define rs q << 1 | 1
#define ln ls,l,mid
#define rn rs,mid + 1,r
#define md int mid = l + r >> 1
void build(int q,int l,int r){
	if(l == r){
		t[q] = vl[l];s[q] = 1;return;
	}
	md;
	build(ln);build(rn);
	t[q] = min(t[ls],t[rs]);
	s[q] = 0;if(t[q] == t[ls]) s[q] += s[ls];if(t[q] == t[rs]) s[q] += s[rs];
}
inline void ps(int q){
	t[ls] += c[q];c[ls] += c[q];
	t[rs] += c[q];c[rs] += c[q];
	c[q] = 0;
}
void ins(int q,int l,int r,int al,int ar,int x){
	if(al > ar) return;
	if(l >= al && r <= ar){
		t[q] += x;c[q] += x;return;
	}
	ps(q);md;
	if(mid >= al) ins(ln,al,ar,x);
	if(mid < ar) ins(rn,al,ar,x);
	t[q] = min(t[ls],t[rs]);
	s[q] = 0;if(t[q] == t[ls]) s[q] += s[ls];if(t[q] == t[rs]) s[q] += s[rs];
}
int dx[4] = {0,-1,0,1},dy[4] = {-1,0,1,0};
#define mt(x,y) jz[(x - 1) * m + (y)]
#define lx(x) (x + dx[0])
#define ux(x) (x + dx[1])
#define fx(x,i) (x + dx[i])
#define fy(x,i) (x + dy[i])
#define ly(x) (x + dy[0])
#define uy(x) (x + dy[1])
#define chk(x,y) (x >= 1 && x <= n && y >= 1 && y <= m)
#define ax(q) a[q].x
#define ay(q) a[q].y
#define qwq(x,y) mt(fx(ax(x),y),fy(ay(x),y))
inline int ed(int q){//“黑格左上”性质结束的时间 
	int mn = p + 1;
	if(chk(lx(ax(q)),ly(ay(q)))) mn = min(mn,qwq(q,0));
	if(chk(ux(ax(q)),uy(ay(q)))) mn = min(mn,qwq(q,1));
	return mn;
}
inline int bg(int q){//“白格相邻”性质开始的时间 
	int mn1 = p + 1,mn2 = p + 1;
	for(int i = 0;i < 4;++i) if(chk(fx(ax(q),i),fy(ay(q),i))){
		if(qwq(q,i) < mn1) mn2 = mn1,mn1 = qwq(q,i);
		else if(qwq(q,i) < mn2) mn2 = qwq(q,i);
	} 
	return mn2;
}
int st[15],ft;
int main(){
	int i,j,u,v;
	n = read();m = read();k = read();p = n * m;
	for(i = 1;i <= p;++i){
		a[i].x = read() + 1;a[i].y = read() + 1;mt(ax(i),ay(i)) = i;
	}
	for(i = 1;i <= p;++i){
		vl[i] = vl[i - 1];
		if(bg(i) < i) --vl[i];
		if(ed(i) > i) ++vl[i];
		for(j = 0;j < 4;++j) if(chk(fx(ax(i),j),fy(ay(i),j))){
			if(qwq(i,j) < i && ed(qwq(i,j)) == i) --vl[i];
			else if(qwq(i,j) > i && bg(qwq(i,j)) == i) ++vl[i];
		}
	}
	build(1,1,p);
	for(i = 1;i <= k;++i){
		u = read() + 1;v = read() + 1;if(u > v) swap(u,v);
		if(u == v){
			print(s[1]);pc('\n');continue;
		}
		ft = 0;
		st[++ft] = u;st[++ft] = v;
		for(j = 0;j < 4;++j) if(chk(fx(ax(u),j),fy(ay(u),j))) st[++ft] = qwq(u,j);
		for(j = 0;j < 4;++j) if(chk(fx(ax(v),j),fy(ay(v),j))) st[++ft] = qwq(v,j);
		sort(st + 1,st + ft + 1);
		for(j = 1;j <= ft;++j) if(st[j] != st[j - 1]){
			if(bg(st[j]) < st[j]) ins(1,1,p,max(bg(st[j]),u),min(st[j],v) - 1,-1);
			if(ed(st[j]) > st[j]) ins(1,1,p,max(st[j],u),min(ed(st[j]),v) - 1,-1);
		}
		swap(mt(ax(u),ay(u)),mt(ax(v),ay(v)));swap(a[u],a[v]);
		for(j = 1;j <= ft;++j) if(st[j] != st[j - 1]){
			if(bg(st[j]) < st[j]) ins(1,1,p,max(bg(st[j]),u),min(st[j],v) - 1,1);
			if(ed(st[j]) > st[j]) ins(1,1,p,max(st[j],u),min(ed(st[j]),v) - 1,1);
		}
		print(s[1]);pc('\n');
	}
	return 0;
}
```

---

## 作者：cyffff (赞：8)

[$\text{Link}$](https://www.luogu.com.cn/problem/P4898)
#### 前言
这道题并不是我自己思考出来的，而是借助了其余题解的帮助。

写这个题解主要为了加深理解，想不看题解自己写一遍出来，确认自己已经懂了这道题。您可以将这篇题解看成我的做题记录。

尽可能地写得清晰一些，哪部分看不懂可以留言提醒。

$\text{Update 2022.6.29}$：修正一处笔误。
## 题意
有一个 $n\times m$ 的点构成的 $n\times m$ 的矩阵，设 $S(i)$ 表示编号为 $1$ 至 $i$ 的点是否构成矩形，$q$ 次操作，每次交换两个编号的点的位置，然后求出 $|\{i|S(i)\}|$。

$1\le n\times m\le 10^6,1\leq q\le5\times 10^4$.
## 思路
#### $\text{Section 1}$ 转化
首先我们思考怎么对于一个 $i$ 求出 $S(i)$。

与其他题解一样，我们将前 $i$ 个点染为黑色，其余染成白色。

我们考虑使用染出来的颜色设计出 $S(i)$ 为真的充要条件。

成为矩形的充要条件有：

- 点处于一个连通块内
- 图形不存在“$\text{L}$ 型”。

对于条件 $1$，我们有：

- 对于所有黑点，其左上方两点中均不为黑色的点数为 $1$。

对于条件 $2$，我们有：

- 对于所有白点，与其四连通的点内有不少于两个黑点的个数为 $0$。

于是我们可以依次计算。
#### $\text{Section 2}$ 优化
我们设点 $(i,j)$ 的编号为 $num_{(i,j)}$，编号为 $i$ 的点为 $(x_i,y_i)$。

考虑对于 $\text{Section 1}$ 的算法将 $i$ 由 $1$ 枚举到 $n\times m$，则 $(i,j)$ 被染为黑色的时间点为 $num_{(i,j)}$。

我们考虑对于点 $(a,b)$，其满足条件 $1$、$2$ 的时间段。

设 $i$ 为当前时间点。

此处我们不考虑边缘情况。

若满足条件 $1$，则：

- $(a,b)$ 是黑点，即 $num_{(a,b)}\le i$；
- $(a,b)$ 左方是白点，即 $num_{(a-1,b)}>i$ ;
- $(a,b)$ 上方是白点，即 $num_{(a,b-1)}>i$。

对这些条件取并集，即 $i\in[num_{(a,b)},\min(num_{(a-1,b)},num_{(a,b-1)}))$。

若满足条件 $2$，则：

- $(a,b)$ 是白点，即 $num_{(a,b)}>i$；
- $(a,b)$ 四周 $num$ 次小的值所在的点为黑点，即 $\text{secmin}(num_{(a-1,b)},num_{(a,b-1)},num_{(a+1,b)},num_{(a,b+1)})\le i$。

对这些条件取并集，即 $i\in[\text{secmin}(num_{(a-1,b)},num_{(a,b-1)},num_{(a+1,b)},num_{(a,b+1)}),num_{(a,b)})$。

此处需要搞清楚点被染黑点的条件、点被染成黑色的时间段等概念，不能混淆。
#### $\text{Section 3}$ 数据结构
我们需要一种数据结构，支持上面的操作。

对于每个点我们维护 $[$ 满足条件 $1\,]+[$ 满足条件 $2\,]$，那么我们对于每个合法区间进行 $+1$，查询全局有几个 $1$。

我们可以将满足条件一的点数设为 $x$，满足条件二的点数设为 $y$。

显然 $x\ge 1,y\ge0$，即 $x+y\ge 1$。

所以维护区间最小值及出现次数即答案.
#### $\text{Section 4}$ 实现细节

- 1.线段树初始最小值为 $0$ 情况的处理：

	我这里也采用了维护严格次小值及其出现次数的方法，查询判断最小值是否为 $1$，严格次小值是否为 $1$ 即可。

- 2.修改点集出现重叠情况时需要去重。

- 3.我们将二维的 $num$ 数组重编号为 $1$ 至 $n\times m$ 维护较为方便。

- 4.考虑边界问题，设计的重编号函数检测到越界时可以返回 $n\times m+1$，此时 $num_{n\times m+1}=n\times m+1$，线段树区间修改时判断当修改区间左端点大于右端点是返回即可。

****

最终时间复杂度为 $O((nm+q)\log nm)$，常数巨大就对了，带个线段树的 $4$ 和一次修改的 $2$、修改点数的 $10$。

代码（挺容易写）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define mpr make_pair
namespace IO{//by cyffff

}
const int N=1e6+10,INF=1e7;
int num[N];
pii pos[N];
int n,m,su;
int mx[]={0,1,0,-1,0};
int my[]={1,0,-1,0,0};
inline int number(int x,int y){
	if(min(x,y)<1||x>n||y>m) return su;
	return (x-1)*m+y;
}
struct Segument_Tree{
	struct node{
		int l,r,minn,tag,cnt,secm=INF,sec;
		inline node operator+=(const int &x){
			minn+=x;
			secm+=x;
			tag+=x;
			return *this;
		}
	}a[N<<2];
	#define ls (rt<<1)
	#define rs (rt<<1|1)
	inline void getsec(int &x,int &y,int &sx,int &sy,int a,int b){
		if(x>a){
			sx=x,sy=y,x=a,y=b;
		}else if(x==a){
			y+=b;
		}else if(sx>a){
			sx=a,sy=b;
		}else if(sx==a){
			sy+=b;
		}
	}
	inline void pushup(int rt){
		a[rt].cnt=a[rt].sec=0;
		a[rt].minn=a[rt].secm=INF;
		getsec(a[rt].minn,a[rt].cnt,a[rt].secm,a[rt].sec,a[ls].minn,a[ls].cnt);
		getsec(a[rt].minn,a[rt].cnt,a[rt].secm,a[rt].sec,a[ls].secm,a[ls].sec);
		getsec(a[rt].minn,a[rt].cnt,a[rt].secm,a[rt].sec,a[rs].minn,a[rs].cnt);
		getsec(a[rt].minn,a[rt].cnt,a[rt].secm,a[rt].sec,a[rs].secm,a[rs].sec);
	}
	inline void pushdown(int rt){
		if(!a[rt].tag) return ;
		a[ls]+=a[rt].tag;
		a[rs]+=a[rt].tag;
		a[rt].tag=0;
	}
	inline void build(int rt,int l,int r){
		a[rt].l=l,a[rt].r=r;
		a[rt].cnt=r-l+1;
		if(l==r) return ;
		int mid=l+r>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
	}
	inline void update(int rt,int l,int r,int v){
		if(l>r) return ;
		if(a[rt].l>=l&&r>=a[rt].r){
			a[rt]+=v;
			return ;
		}
		pushdown(rt);
		if(a[ls].r>=l) update(ls,l,r,v);
		if(a[rs].l<=r) update(rs,l,r,v);
		pushup(rt);
	}
	inline int query(){
		return (a[1].minn==1)*a[1].cnt+(a[1].secm==1)*a[1].sec;
	}
}t;
int tind[10];
inline void update(int x,int y,int v){
	int posi=number(x,y);
	if(posi==su) return ;
	t.update(1,num[posi],min(num[number(x-1,y)],num[number(x,y-1)])-1,v);
	for(int i=0;i<4;i++){
		tind[i]=num[number(x+mx[i],y+my[i])];
	}
	sort(tind,tind+4);
	t.update(1,tind[1],num[posi]-1,v);
}
pii tmp[15],tmp1,tmp2;
int q,top;
int main(){
	n=read(),m=read(),q=read();
	num[su=n*m+1]=n*m+1;
	for(int i=1;i<su;i++){
		int x=read()+1,y=read()+1;
		num[number(x,y)]=i;
		pos[i]=mpr(x,y);
	}
	t.build(1,1,su-1);
	for(int i=1;i<su;i++){
		update(pos[i].first,pos[i].second,1);
	}
	while(q--){
		int x=read()+1,y=read()+1;
		tmp1=pos[x],tmp2=pos[y];
		top=0;
		for(int i=0;i<5;i++){
			tmp[++top]=mpr(tmp1.first+mx[i],tmp1.second+my[i]);
			tmp[++top]=mpr(tmp2.first+mx[i],tmp2.second+my[i]);
		}
		sort(tmp+1,tmp+top+1);
		top=unique(tmp+1,tmp+top+1)-tmp;
		for(int i=1;i<top;i++){
			update(tmp[i].first,tmp[i].second,-1);
		}
		swap(num[number(tmp1.first,tmp1.second)],num[number(tmp2.first,tmp2.second)]);
		swap(pos[x],pos[y]);
		for(int i=1;i<top;i++){
			update(tmp[i].first,tmp[i].second,1);
		}
		write(t.query());
		putc('\n');
	}
	flush();
    return 0;
}
```
再见 qwq~

---

## 作者：critnos (赞：7)

相信大家看完题解仍然有些迷惑吧！

我讲一下我的理解。

大家应该是卡在了不会维护这个：

>为了方便，我们现在对于一个位置i，将前i个点染成黑色，后面的点为白色。

>我们维护这么两个东西：

>1、所有的黑点中，有多少个点的左侧和上侧都不挨着黑点（可能是白点或边缘）。

>2、所有的白点中，有多少个点的周围四连通地挨着大于等于2个黑点。

——liuzhangfeiabc

首先我们要搞明白，一个点何时会成为黑点。

点 $(x,y)$ 会成为黑点的时刻（我们设第 $i$ 个时刻将前 $i$ 个点染黑，$t_{x,y}$ 为下标为 $(x,y)$ 的点的编号）$i$，当且仅当 $i\ge t_{x,y}$。因为在第 $t_{x,y}$ 个时刻这个点就被染黑了。反之，当 $i<t_{x,y}$ 时，这个点是白点。

所以，对于第一个信息，对于点 $(x,y)$ 的时刻 $i$，我们需要满足三个条件：

1. $i\ge t_{x,y}$（即这个点是黑点）。

2. $i<t_{x-1,y}$（即上方是白点）

3. $i<t_{x,y-1}$（即左侧是白点）

这三个信息的并集就是 $[t_{x,y},\min(t_{x-1,y},t_{x,y-1}))$ 啦！

同理对于第二个我们也可以得到：

1. $i<t_{x,y}$

2. $i\ge secondmin(t_{x-1,y},t_{x,y-1},t_{x+1,y},t_{x,y+1})$（$secondmin$ 指次小值，意思是，当第二个黑点出现的时候这个时刻就满足条件了）

并集是 $[secondmin(t_{x-1,y},t_{x,y-1},t_{x+1,y},t_{x,y+1}),t_{x,y})$。

所以把时刻放在序列上维护，支持区间加（加入贡献的时候 $+1$，撤销的时候 $-1$），全局求 $1$ 的个数，线段树维护比较方便。

P.S. 题解都是维护最小值。。但是我太笨了以至于不会很好的解决初始序列出现 $0$ 的问题（其实也是可以的。。但是也麻烦。。代码会不美观），于是就维护了最小值，最小值出现次数，严格次小值和严格次小值出现次数。

```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
int t[1000005];
pair<int,int> a[1000005];
int n,m;
const int fx[]={0,-1,1,0,0};
const int fy[]={-1,0,0,1,0};
int f(int x,int y)
{
	if(x<1||y<1||x>n||y>m) return 0;
	return (x-1)*m+y;
}
struct segment_tree
{
	#define ls w<<1
	#define rs ls|1
	struct seg
	{
		int l,r,mn,mn2,s,s2,tag;
	}t[4000005];
	int f[1000005];
	void build(int w,int l,int r)
	{
		t[w].l=l,t[w].r=r;
		t[w].mn2=2e9,t[w].s=r-l+1;
		if(l<r)
		{
			int mid=l+r>>1;
			build(ls,l,mid);
			build(rs,mid+1,r);
		}
	}
	void pushup(int w)
	{
		pair<int,int> s[4]={{t[ls].mn,t[ls].s},{t[ls].mn2,t[ls].s2},{t[rs].mn,t[rs].s},{t[rs].mn2,t[rs].s2}};
		t[w].mn=t[w].mn2=2e9;
		t[w].s=t[w].s2=0;
		for(int i=0;i<4;i++)
			if(s[i].first==t[w].mn)
				t[w].s+=s[i].second;
			else if(s[i].first<t[w].mn)
				t[w].mn2=t[w].mn,t[w].s2=t[w].s,t[w].mn=s[i].first,t[w].s=s[i].second;
			else if(s[i].first==t[w].mn2)
				t[w].s2+=s[i].second;
			else if(s[i].first<t[w].mn2)
				t[w].mn2=s[i].first,t[w].s2=s[i].second;
	}
	void pushdown(int w)
	{
		t[ls].tag+=t[w].tag;
		t[rs].tag+=t[w].tag;
		t[ls].mn+=t[w].tag;
		t[rs].mn+=t[w].tag;
		t[ls].mn2+=t[w].tag;
		t[rs].mn2+=t[w].tag;
		t[w].tag=0;
	}
	void add(int w,int l,int r,int v)
	{
		if(l>r) return;
		if(t[w].l>=l&&t[w].r<=r)
		{
			t[w].mn+=v,t[w].mn2+=v,t[w].tag+=v;
			return;
		}
		pushdown(w);
		if(t[ls].r>=l) add(ls,l,r,v);
		if(t[rs].l<=r) add(rs,l,r,v);
		pushup(w);
	}
	int ask()
	{
		return (t[1].mn==1)*t[1].s+(t[1].mn2==1)*t[1].s2;
	}
}tr;
void add(int x,int y,int v)
{
	if(!f(x,y)) return;
	tr.add(1,t[f(x,y)],min(f(x-1,y)?t[f(x-1,y)]:(n*m+1),f(x,y-1)?t[f(x,y-1)]:(n*m+1))-1,v);
	int s[4],i;
	for(i=0;i<4;i++)
		s[i]=f(x+fx[i],y+fy[i])?t[f(x+fx[i],y+fy[i])]:1e9;
	sort(s,s+4);
	tr.add(1,s[1],t[f(x,y)]-1,v);
}
int main()
{
	int q,i,x,y,cnt;
	pair<int,int> re[15],u,v;
	scanf("%d%d%d",&n,&m,&q);
	for(i=1;i<=n*m;i++)
		scanf("%d%d",&x,&y),t[f(x+1,y+1)]=i,a[i]=make_pair(x+1,y+1);
	tr.build(1,1,n*m);
	for(i=1;i<=n*m;i++)
		add(a[i].x,a[i].y,1);
	while(q--)
	{
		scanf("%d%d",&x,&y);
		x++,y++;
		u=a[x],v=a[y];
		cnt=0;
		for(i=0;i<5;i++)
		{
			re[cnt++]=make_pair(u.x+fx[i],u.y+fy[i]);
			re[cnt++]=make_pair(v.x+fx[i],v.y+fy[i]);
		}
		sort(re,re+cnt);
		cnt=unique(re,re+cnt)-re;
		for(i=0;i<cnt;i++)
			add(re[i].x,re[i].y,-1);
		swap(t[f(u.x,u.y)],t[f(v.x,v.y)]);
		swap(a[x],a[y]);
		for(i=0;i<cnt;i++)
			add(re[i].x,re[i].y,1);
		printf("%d\n",tr.ask());
	}
}
```


---

## 作者：Jay142753869 (赞：5)

[某大佬](https://www.luogu.com.cn/user/154520)：思路理解完就很好做了。   

然后我就看了下题解的思路，结果发现实现还是比较简单的（说明chen_03奆顺带Orz）。  

思路：

1. 显然同样大小的子矩阵中，符合条件的最多一个。  

1. 考虑判断 $[0 \dots i-1]$ 的数是否构成一个矩形，将这些数染成黑的，并且把剩下的和边界外的染成白色。  

1. 假设 $[0 \dots i-1]$ 的数构成矩形，那么这 $i$ 个点中：

	- 左上都是白点。  
   - 上下左右4个点中，是黑点的大于等于2个。  
   
1. 那么把满足第一个的黑点数记为 $x$ ， $x=1$ 并且也满足了这 $i$ 个点处于同一连通块。  

1. 同理满足第二个的白点记为 $y$ ，$y=0$ 并且也满足了这i个点构成一个矩形，不满足则说明存在“拐角”。  

1. 如果只满足第二个，不满足第一个，说明可能构成多个矩形。  

1. 可以从题目中得到如果 $x+y=1$ ，那么这个就是合法的。  

1. 可以用线段树来维护每个 $i$ 和 $x+y$ 的值，并且维护区间最小值及最小值个数（最小值不可能为 $0$ ）。  

1. 对于每个点u，一定是先白后黑。那么就可以设 $u$ 为白点的最晚时刻为$l_u$，为黑点的最早时刻为 $r_u$。  

1. 记 $u$ 周围 $4$ 个点的 $r$ 的**次**小值为 $z$ （越界为$\inf$），记 $v$ 左上的 $l$ 的最小值为 $t$ （越界为 $H \times W-1$ ）。  

1. $u$ 作为满足第二个的点的时段为 $[z,l_u]$（注意有 $z>l_u$ 的情况），$v$ 作为满足第一个的点的时段即 $[r_u,t]$ （一样的注意有 $r_u>t$ 的情况）。  

1. 那么在线段树上给 $[z,l_u]$ 和 $[r_u,t]$ 都 $+1$。  

1. 每次交换时，减掉两个点 $a,b$ 及他们周围4个点（共 $O(10)$ 个点）在两点交换前的贡献，交换 $a,b$ ，加上这些点在两点交换后的贡献。  

1. 注意如果 $10$ 个点中有重复的，不可以重复加减贡献

1. 要记录矩阵中每个位置上的数是什么，以及每个数所在位置是什么。 

做完了。。  
 _Code for luogu_
 ```cpp
#include<bits/stdc++.h>
#define reg register int
#define il inline
#define mid ((l+r)>>1)
#define MAXN 1000010
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
il int read(){
    char c=getchar();
    int x=0;
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9')
    	x=(x<<3)+(x<<1)+c-48,c=getchar();
    return x;
}
int id[MAXN],vis[MAXN],sta[MAXN],top,pos[MAXN][2],n,m,q;
int num(int x,int y){
    return (x-1)*m+y;
}
struct tr{
    int mi,cnt,mx,ad;
}t[4*MAXN];
void pushup(int x){
    t[x].mi=min(t[x<<1].mi,t[x<<1|1].mi);
    t[x].mx=max(t[x<<1].mx,t[x<<1|1].mx);
    t[x].cnt=t[x<<1].cnt*(t[x<<1].mi==t[x].mi)+t[x<<1|1].cnt*(t[x<<1|1].mi==t[x].mi);
}
void pushdown(int x){
    if(!t[x].ad) return;
    t[x<<1].ad+=t[x].ad;
    t[x<<1].mi+=t[x].ad;
    t[x<<1].mx+=t[x].ad;
    t[x<<1|1].ad+=t[x].ad;
    t[x<<1|1].mi+=t[x].ad;
    t[x<<1|1].mx+=t[x].ad;
    t[x].ad=0;
}
void build(int x,int l,int r){
    if(l==r){
        t[x].cnt=1;return;
    }
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    pushup(x);
}
void add(int x,int l,int r,int L,int R,int c){
    if(L<=l&&r<=R){
        t[x].ad+=c;
        t[x].mi+=c;
        t[x].mx+=c;
        if(t[x].mi==t[x].mx) t[x].cnt=r-l+1;
        return;
    }    
    pushdown(x);
    if(L<=mid) add(x<<1,l,mid,L,R,c);
    if(mid<R) add(x<<1|1,mid+1,r,L,R,c);
    pushup(x);
}
int mv[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
void f(int x,int y,int c){
    int mi=inf,cmi=inf;
    for(reg i=0;i<4;++i){
        int dx=x+mv[i][0],dy=y+mv[i][1];
        if(dx>=1&&dx<=n&&dy>=1&&dy<=m){
            if(id[num(dx,dy)]<mi){
                cmi=mi;mi=id[num(dx,dy)];
            }else cmi=min(cmi,id[num(dx,dy)]);
        }
    }
    if(cmi<=id[num(x,y)]-1) {
        add(1,1,n*m,cmi,id[num(x,y)]-1,c);
    }
}
void s(int x,int y,int c){
    int mi=n*m+1;
    int dx=x-1,dy=y;
    if(dx>=1&&dx<=n&&dy>=1&&dy<=m){
        mi=min(mi,id[num(dx,dy)]);
    }
    dx=x,dy=y-1;
    if(dx>=1&&dx<=n&&dy>=1&&dy<=m){
        mi=min(mi,id[num(dx,dy)]);
    }
    if(id[num(x,y)]<=mi-1) add(1,1,n*m,id[num(x,y)],mi-1,c);
}
void sol(int x,int y,int c){
    if(!vis[num(x,y)]) {
        sta[++top]=num(x,y);
        vis[num(x,y)]=1;
        f(x,y,c);
		s(x,y,c);
    }
    for(reg i=0;i<4;++i){
        int dx=x+mv[i][0],dy=y+mv[i][1];
        if(dx>=1&&dx<=n&&dy>=1&&dy<=m&&!vis[num(dx,dy)]){
            vis[num(dx,dy)]=1;
            sta[++top]=num(dx,dy);
            f(dx,dy,c);
			s(dx,dy,c);
        }
    }
}
int main(){
    n=read();m=read();q=read();
    build(1,1,n*m);
    int x,y;
    for(reg i=1;i<=n*m;++i){
        x=read();y=read();
        ++x;++y;
        pos[i][0]=x;pos[i][1]=y;
        id[num(x,y)]=i;
    }
    for(reg i=1;i<=n;++i){
        for(reg j=1;j<=m;++j){
            f(i,j,1);
            s(i,j,1);
        }
    }
    int u,v;
    while(q--){
        u=read();v=read();        
        ++u;++v;
        top=0;
        x=pos[u][0],y=pos[u][1];
        sol(x,y,-1);
        x=pos[v][0],y=pos[v][1];
        sol(x,y,-1);
        while(top) vis[sta[top--]]=0;
        swap(id[num(pos[u][0],pos[u][1])],id[num(pos[v][0],pos[v][1])]);
        swap(pos[u][0],pos[v][0]);
        swap(pos[u][1],pos[v][1]);
        x=pos[u][0],y=pos[u][1];
        sol(x,y,1);
        x=pos[v][0],y=pos[v][1];
        sol(x,y,1);
        while(top) vis[sta[top--]]=0;
        int ans=0;
        if(t[1].mi==1) ans=t[1].cnt;
        printf("%d\n",ans);
    }
    return 0;
}
 ```
_Code for loj_  
```cpp
#include "seats.h"
#include<bits/stdc++.h>
#define reg register int
#define il inline
#define mid ((l+r)>>1)
#define MAXN 1000010
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
il int read(){
    char c=getchar();
    int x=0;
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9')
    	x=(x<<3)+(x<<1)+c-48,c=getchar();
    return x;
}
int id[MAXN],vis[MAXN],sta[MAXN],top,pos[MAXN][2],n,m,q;
int num(int x,int y){
    return (x-1)*m+y;
}
struct tr{
    int mi,cnt,mx,ad;
}t[4*MAXN];
void pushup(int x){
    t[x].mi=min(t[x<<1].mi,t[x<<1|1].mi);
    t[x].mx=max(t[x<<1].mx,t[x<<1|1].mx);
    t[x].cnt=t[x<<1].cnt*(t[x<<1].mi==t[x].mi)+t[x<<1|1].cnt*(t[x<<1|1].mi==t[x].mi);
}
void pushdown(int x){
    if(!t[x].ad) return;
    t[x<<1].ad+=t[x].ad;
    t[x<<1].mi+=t[x].ad;
    t[x<<1].mx+=t[x].ad;
    t[x<<1|1].ad+=t[x].ad;
    t[x<<1|1].mi+=t[x].ad;
    t[x<<1|1].mx+=t[x].ad;
    t[x].ad=0;
}
void build(int x,int l,int r){
    if(l==r){
        t[x].cnt=1;return;
    }
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    pushup(x);
}
void add(int x,int l,int r,int L,int R,int c){
    if(L<=l&&r<=R){
        t[x].ad+=c;
        t[x].mi+=c;
        t[x].mx+=c;
        if(t[x].mi==t[x].mx) t[x].cnt=r-l+1;
        return;
    }    
    pushdown(x);
    if(L<=mid) add(x<<1,l,mid,L,R,c);
    if(mid<R) add(x<<1|1,mid+1,r,L,R,c);
    pushup(x);
}
int mv[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
void f(int x,int y,int c){
    int mi=inf,cmi=inf;
    for(reg i=0;i<4;++i){
        int dx=x+mv[i][0],dy=y+mv[i][1];
        if(dx>=1&&dx<=n&&dy>=1&&dy<=m){
            if(id[num(dx,dy)]<mi){
                cmi=mi;mi=id[num(dx,dy)];
            }else cmi=min(cmi,id[num(dx,dy)]);
        }
    }
    if(cmi<=id[num(x,y)]-1) {
        add(1,1,n*m,cmi,id[num(x,y)]-1,c);
    }
}
void s(int x,int y,int c){
    int mi=n*m+1;
    int dx=x-1,dy=y;
    if(dx>=1&&dx<=n&&dy>=1&&dy<=m){
        mi=min(mi,id[num(dx,dy)]);
    }
    dx=x,dy=y-1;
    if(dx>=1&&dx<=n&&dy>=1&&dy<=m){
        mi=min(mi,id[num(dx,dy)]);
    }
    if(id[num(x,y)]<=mi-1) add(1,1,n*m,id[num(x,y)],mi-1,c);
}
void sol(int x,int y,int c){
    if(!vis[num(x,y)]) {
        sta[++top]=num(x,y);
        vis[num(x,y)]=1;
        f(x,y,c);
		s(x,y,c);
    }
    for(reg i=0;i<4;++i){
        int dx=x+mv[i][0],dy=y+mv[i][1];
        if(dx>=1&&dx<=n&&dy>=1&&dy<=m&&!vis[num(dx,dy)]){
            vis[num(dx,dy)]=1;
            sta[++top]=num(dx,dy);
            f(dx,dy,c);
			s(dx,dy,c);
        }
    }
}
void give_initial_chart(int H,int W,vector<int> R,vector<int> C){
	int x,y;n=H,m=W;
    build(1,1,n*m);
	for(reg i=1;i<=n*m;++i){
		x=R[i-1]+1;
		y=C[i-1]+1;
		id[num(x,y)]=i;
		pos[i][0]=x;
		pos[i][1]=y;
	}
	for(reg i=1;i<=n;++i){
        for(reg j=1;j<=m;++j){
            f(i,j,1);
            s(i,j,1);
        }
    }
}
int swap_seats(int a,int b){
	int u=a,v=b,x,y;        
    ++u;++v;
    top=0;
    x=pos[u][0],y=pos[u][1];
    sol(x,y,-1);
    x=pos[v][0],y=pos[v][1];
    sol(x,y,-1);
    while(top) vis[sta[top--]]=0;
    swap(id[num(pos[u][0],pos[u][1])],id[num(pos[v][0],pos[v][1])]);
    swap(pos[u][0],pos[v][0]);
    swap(pos[u][1],pos[v][1]);
    x=pos[u][0],y=pos[u][1];
    sol(x,y,1);
    x=pos[v][0],y=pos[v][1];
    sol(x,y,1);
    while(top) vis[sta[top--]]=0;
    int ans=0;
    if(t[1].mi==1) ans=t[1].cnt;
    return ans;
}
```

---

## 作者：lzyqwq (赞：3)

在高中写的第一道黑色数据结构题。感觉这种题数据结构题满满的 JOI 风格但没想到是个 IOI 题。

---



**[P4898 [IOI2018] seats 排座位](https://www.luogu.com.cn/problem/P4898)**

> - 有一个 $H$ 行 $W$ 列的网格，记从上往下第 $x$ 行从左往右第 $y$ 列的位置为 $(x,y)$。其上有一个编号为 $\text{id}_{i,j}$ 的点。记编号为 $i$ 的点位置为 $P_i=(X_i,Y_i)$。有 $Q$ 次询问，每次给出两个点的编号 $A,B$，您要先交换这两个点的位置，再求出有多少个 $i$，满足编号为 $1\sim i$ 的点在网格上构成的图形是一个矩形。
> - 形式化地，记网格中的点集为 $U=\{(u,v)\,|\,u\in[1,H]\cap\mathbb{Z},v\in[1,W]\cap\mathbb{Z}\}$。对于某个编号 $i$，记 $S_i=\{(X_j,Y_j)\,|\,j\in[1,i]\cap\mathbb{Z}\}$。若存在 $(x_1,y_1),(x_2,y_2)\in U$，使得 $S_i=\{(u,v)\,|\,u\in[x_1,x_2]\cap\mathbb{Z},v\in[y_1,y_2]\cap\mathbb{Z}\}$，则记 $F_i=1$，否则 $F_i=0$。您要求出 $G=\sum\limits_{i=1}^{H\times W}F_i$。
> - 记 $N=H\times W$，$N\le 10^6$，$Q\le 5\times 10^4$。

下文中，若某个量和一个在 $U$ 中不存在的坐标关联，则在命题和运算中忽略她。

考虑一个点集 $S_i$ 何时能构成一个矩形。对于一个 $i$，我们称在 $S_i$ 中的点为 **黑点**，剩余的点为 **白点**，则 $F_i=1$ 等价于以下两个条件同时满足：

- **仅** 存在 $1$ 个黑点 $(x,y)$，满足性质 $\text{A}$：$(x-1,y)$ 和 $(x+1,y)$ 两个点中任意一个点要么在 $U$ 中不存在，要么为 **白点**。

  可以证明对于任意一个 **黑点** 集一定存在满足性质 $\text{A}$ 的 $(x,y)$，考找到点集中所有点的最小的行号 $r$，再在行号为 $r$ 的点中找到最小的列号 $c$。我们称 $(r,c)$ 为这个 **黑点** 集的 **关键点**。

- 不存在一个白点 $(x,y)$，满足性质 $\text{B}$：在 $(x-1,y),(x,y-1),(x+1,y),(x,y+1)$ 四个点里满足在 $U$ 中存在的点中，存在两个 **黑点**。

> 必要性显然，下证充分性。考虑使用数学归纳法：
>
 > - 记某个点集 $S_i$ 中的 **黑点** 出现过的最小、最大的行号分别为 $h_{\min}$ 和 $h_{\max}$。
> - 对于 $h_{\min}$ 这一行，其中的点的列号一定是连续的整数 $[L,R]\cap\mathbb{Z}$。若不连续，则列号构成了 $\ge 2$ 个不相邻的值域连续段。考虑任意两个值域连续段 $[l_1,r_1]\cap\mathbb{Z},[l_2,r_2]\cap\mathbb{Z}$ 则存在 $(h_{\min},l_1),(h_{\max},l_2)$ 两个 **黑点** 均满足性质 $\text{A}$，与条件一不符。因此 $h_{\min}$ 这一行的点构成了一个以 $(h_{\min},L)$ 为左上角、$(h_{\min},R)$ 为右下角的矩形。
> - 若行号在 $[h_{\min},m]\cap\mathbb{Z}$ 内的构成了以 $(h_{\min},L)$ 为左上角、$(m,R)$ 为右下角的矩形，其中 $m<h_{\max}$。考虑加入 $S_i$ 中 $m+1$ 这一行的 **黑点**。$S_i$ 中必须存在行号为 $m+1$ 的 **黑点**，因为若 $m+1=h_{\max}$ 则已经存在，否则考虑将 $S_i$ 分为行号不超过 $m$ 和行号超过 $m+1$ 的两部分，每部分的 **关键点** 都满足性质 $\text{A}$，导致点集不满足条件一。
>
>   其次，这一行不存在列号小于 $L$ 或列号大于 $R$ 的点。因为若存在列号为 $L-1$ 或 $R+1$ 的 **黑点**，则 $(m,L-1),(m,R+1)$ 两个 **白点** 满足性质 $\text{B}$。否则，考虑这一行列号小于 $L$ 和大于 $R$ 的点构成的点集 $T_L,T_R$，其中至少一个集合不为空。那么 $(h_{\min},L)$ 和 $T_L$ 或 $T_R$ 中的 **关键点** 均满足性质 $\text{A}$。
>   
>   因此，$S_i$ 中行号为 $m+1$ 的点列号都在 $[L,R]\cap\mathbb{Z}$ 内。那么第 $m+1$ 行列号都在 $[L,R]\cap\mathbb{Z}$ 内的点都必须为 **黑点**。否则，可以将这些列号划分成 $\ge 2$ 个 **极长同色连续段**，使得任意相邻两段颜色不同。考虑一个黑色段和一个白色段相邻，则对于白色段位于与黑色段交界处的这个端点 $p$，$(m+1,p)$ 这个 **白点** 满足性质 $\text{B}$。
>   
>   综上，我们得到第 $m+1$ 行的 **黑点** 的列号集合为 $[L,R]\cap\mathbb{Z}$。因此，对于行号在 $[h_{\min},m+1]\cap\mathbb{Z}$ 内的 **黑点**，她们构成了以 $(h_{\min},L)$ 为左上角、$(m+1,R)$ 为右下角的矩形。
>
> $\mathcal{Q.E.D.}$

对于 $i$，我们记 $S_i$ 中满足性质 $\text{A}$ 的 **黑点** 个数为 $b_i$，网格中满足性质 $\text{B}$ 的 **白点** 个数为 $w_i$，根据上面的分析，$F_i=1$ 等价于 $b_i=1$ 且 $w_i=0$。而 $S_i$ 中必有 **关键点**，因此 $b_i\ge 1$；$w_i$ 表示 **白点** 的个数必定有 $w_i\ge 0$。所以 $b_i+w_i\ge 1$，当且仅当 $\begin{cases}b_i=1\\w_i=0\end{cases}$ 时取到等号。因此我们可以考虑将原问题转化为判定 $b_i+w_i$ 是否为 $1$。

记 $k_i=b_i+w_i$，考虑一个点 $(x,y)$ 会对哪些 $k_i$ 产生贡献，分别考虑其作为 **黑点** 和 **白点** 时的贡献。

- 当她作为 **黑点** 时，首先有 $\text{id}_{x,y}\le i$。其次她满足性质 $\text{A}$，则有 $\text{id}_{x-1,y},\text{id}_{x,y-1}>i$。因此得到 $\text{id}_{x,y}\le i<\min\{\text{id}_{x-1,y}\text{id}_{x,y-1}\}$。

  相当于 $(x,y)$ 给下标在 $[\text{id}_{x,y},\min\{\text{id}_{x-1,y}\text{id}_{x,y-1}\}-1]\cap\mathbb{Z}$ 中的 $k_i$ 均贡献 $1$。

- 当她作为 **白点** 时，若 $(x-1,y),(x,y-1),(x+1,y),(x,y+1)$ 中仅有一个点在 $U$ 中存在，则她无贡献。因为一个点构成的集合中不可能存在两个 **黑点**。首先有 $\text{id}_{x,y}>i$。其次她满足性质 $\text{B}$，则有：

  $$[\text{id}_{x-1,y}\le i]+[\text{id}_{x, y - 1}\le i]+[\text{id}_{x+1,y}\le i]+[\text{id}_{x,y+1}\le i]\ge 2$$

  对于某个元素个数 $\ge 2$ 的集合 $M$，记 $\text{secmin} M$ 表示集合 $M$ 中的 **非** 严格次小值，即从小到大排序后的第二个元素。

  则上述条件等价于 $\text{secmin}\{\text{id}_{x-1,y},\text{id}_{x, y - 1},\text{id}_{x+1,y},\text{id}_{x,y+1}\}\le i$。

  相当于 $(x,y)$ 给下标在 $[\text{secmin}\{\text{id}_{x-1,y},\text{id}_{x, y - 1},\text{id}_{x+1,y},\text{id}_{x,y+1}\},\text{id}_{x,y}-1] \cap\mathbb{Z}$ 中的 $k_i$ 贡献 $1$。

先考虑计算第一次操作开始之前的答案。相当于所有点贡献完之后，求有多少 $k_i=1$。由于 $k_i\ge 1$，因此只需要维护区间最小值及个数即可。考虑到 $k_1=1$，因此任意时刻最小值一定为 $1$，答案即为最小值个数。

考虑线段树上标记永久化维护。可以做到 $\mathcal{O}(N\log N)$ 时间维护初始的 $k_i$。但是 $N,Q$ 不同阶显然有意卡这个时间复杂度。考虑到初始状态不需要查询，可以维护一阶差分，每次差分数组单点加，然后 $\mathcal{O}(N)$ 求出其前缀和得到 $k_i$，最后 $\mathcal{O}(N)$ 建树。

接下来考虑交换后 $k_i$ 会发生哪些变化，显然只有 $A,B$ 和与她们四连通相邻的点，产生贡献的区间会发生变化。找到这 $\mathcal{O}(1)$ 个点，然后先删去她们的贡献（即原来被她们 $+1$ 的 $k_i$ 再减 $1$），这样就得到了在交换前剩余点产生贡献后的 $k_i$。由于这些点产生贡献的区间不变，因此此时的 $k_i$ 就是交换后剩余点产生贡献后的 $k_i$。然后交换 $A,B$ 的坐标及她们坐标上的编号信息，再加入重新她们的贡献即可。

每次重新计算贡献后，输出当前最小值个数即为答案。

那么这题就做完了，时间复杂度为 $\mathcal{O}(N+Q\log N)$，空间复杂度为 $\mathcal{O}(N)$。

**[AC Link](https://www.luogu.com.cn/record/172783692)**

**[AC Code](https://www.luogu.com.cn/paste/3oke5tgs)**

---

话说这原来是 2018 年的 IOI 题啊。2018 年的大赛题我做了 [P4768 [NOI2018] 归程](https://www.luogu.com.cn/problem/P4768)、[P4770 [NOI2018] 你的名字](https://www.luogu.com.cn/problem/P4770)、[P4899 [IOI2018] werewolf 狼人](https://www.luogu.com.cn/problem/P4899)和 [P4898 [IOI2018] seats 排座位](https://www.luogu.com.cn/problem/P4898) 四个。她们都是可爱的数据结构题啊！

其中前三题是在 xyd 做的，最后一题（也就是本题）是今天在学车机房做的。我还依稀记得去 xyd 的第一天晚上，在 xjxx 的宿舍用 [zhc](https://www.luogu.com.cn/user/542876) 的电脑调 [P4899 [IOI2018] werewolf 狼人](https://www.luogu.com.cn/problem/P4899) 的经历；记得在听 [lck](https://www.luogu.com.cn/user/592690) 巨佬讲 [P4770 [NOI2018] 你的名字](https://www.luogu.com.cn/problem/P4770) 的后缀自动机做法时我瑟瑟发抖的样子，随后在两个月后用后缀数组切了这题，并由此了解了《你的名字。》这部动漫，然后入坑了二次元，然后在一模时出了一道同名的未公开题目，后来在《你的名字。》重映期间写了数据结构大师 @[critnos](https://www.luogu.com.cn/user/203623) 出的 [P7811 [JRKSJ R2] 你的名字。](https://www.luogu.com.cn/problem/P7811)。写可爱的数据结构题也许真的能给我带来许多快乐吧。

这题怎么还叫排座位啊。2018 年的我似乎在迫切的渴望着和可爱的【】排到四连通的座位吧。当年八连通了一个学期后我和【】的座位的矩形就没有公共点了。记得小学的最后一个学期如愿以偿四连通了然后在期末考试中拿了年一。然而时光荏苒，我和【】也渐行渐远了，至今未再见面。

我想到 NOI2024 D1T1 的一句话：

> 时光荏苒，小 S 和小 Y 也会散去。而我们和一个人保持连接的方式就是记住，仅此而已。

是的，我在尝试记住 OI，记住数据结构，记住【】，永远也不要忘记，即使我在这些方面取得进展的机会十分渺茫。

我又想起 NOI2024D2T1 的一句话：

> 时光走过，小 C 和小 Y 会再遇见。回首往事，大家都过上了各自想要的生活。

如今我不敢奢望再遇见，只是想虔诚地祈祷，能够保持彼此之间的连接，与 OI、数据结构还有【】幸福地生活在同一片美丽的、光明的四连通正交矩形天空下，仅此而已。

---

## 作者：pldzy (赞：3)

- [P4898 [IOI2018] seats 排座位](https://www.luogu.com.cn/problem/P4898)

虽然“当你觉得此题方法很妙时，说明你的能力不足以驾驭这道题”，但是这既然是线段树的一个应用而且破题方法绝妙，所以我还是做了。

本题解讲述思路 + 解说 @[liuzhangfeiabc](https://www.luogu.com.cn/user/45775) 大佬的代码思路（实现方法）。
    
# Solution

## 1
    
如何判断节点集合 $P$ 中的所有节点所组成的图形是否是一矩形？此处采用了一个**染色**的办法。假设我们现在将 $P$ 中的节点全部染成黑色，将其余的节点全部染成白色。然后统计符合一下两个条件之一的点的总数：

- 一个黑点，且它的左方和上方相邻的节点都是白色（或者为空）【条件一】；
- 一个白点，且它的上下左右相邻的节点中有 $\geq2$ 个黑色的节点【条件二】。
   
回过头来，看一个矩形中按上述方式能统计多少个点出来（顺便口胡证明）：

- 若一个黑点的左方和上方相邻的节点都是白色（或为空），则代表有一个连通块。显然，一个矩形中只有一个大连通块，若出现两个这样的黑色节点，那它肯定不是一个矩形。
- 若有一个白点符合第二个条件，通过简单构造可以发现，不论黑色节点以什么方式出现在白点周围都无法在此基础上构造一个矩形。反过来说，当出现一个“L”形拐角时，拐角处的白点就符合第二个条件。综述，一个矩形不存在满足条件二的节点。

所以，一个矩形的两者之和必定为 $1$。

## 2

有了上述的结论与判定方法，我们再看看和这道题有什么关联。

发现我们可以将题目所求转化为：变量 $i$ 从 $1$ 遍历到 $h \times w$，而 $i$ 可以理解为一个时间点，即第 $i$ 个时刻。在每个时刻 $i$，我们会在之前的基础上将第 $i$ 为参赛者的座位染成黑色。即在时刻 $i$，第 $1$ 到 $i$ 位参赛者的座位都会被染上黑色。同时，记 $val_i$ 表示时刻 $i$ 时满足 $1$ 中所述两个条件的总点数。

由此可以得到一个重要性质：白点染色时间必定大于黑点染色时间。

此时就可以统计每个 $val_i$ 的值：（$r(i)$ 表示第 $i$ 位参赛者的座位所在的行数；$c(i)$ 表示所在列数；$i$ 既代表时刻，也代表这个时刻要染色的节点；$num_{x,y}$ 表示座位 $(x,y)$ 的参赛者的编号。）

````cpp
	#define rep(i, a, b) for(register int i = a; i <= b; ++i)
	rep(i, 1, s){ val[i] = val[i - 1];
		if(black(r(i), c(i)) > i) val[i] += 1;
		if(white(r(i), c(i)) < i) val[i] -= 1;
		rep(j, 0, 3) if(legal((xx = r(i) + fx[j][0]), (yy = c(i) + fx[j][1]))){
			if(black(xx, yy) == i and num(xx, yy) < i) val[i] -= 1;
			if(white(xx, yy) == i and num(xx, yy) > i) val[i] += 1;
		}
	}
````

一点点来说，首先 `black()` 函数是返回 $i$ 节点左方和上方相邻节点它们染色时间的最小值。若这个最小值都大于 $i$，那么代表，$i$ 这个节点是符合条件一的节点，所以 $val_i$ 加一。

反之， `white()` 函数是返回 $i$ 节点四方相邻节点它们染色时间的次（第二）小值。若这个次小值小于 $i$，那么代表，$i$ 这个节点此前是一个符合条件二的白点，但是现在它染成黑色，也就不满足条件二了，所以 $val_i$ 减一。

后面循环它的四方节点目的就是处理它是白点时对周围节点的影响。比如说，它曾经是其下方节点的 `black()` 值，当时刻小于 $i$ 且大于等于 $num(r(i) + 1,c(i))$，下方节点就是满足条件一的黑点。但是当节点 $i$ 染成黑色之后，它（$i$ 节点的下方节点）就不再是满足条件一的节点了，所以 $val_i$ 要减一。周围其他方向的节点同理。

## 3

然后再来谈谈交换座位。

这其中也涉及到一开始为什么要以那样的条件去检测所围图形是否为矩形——因为这样的判定方式不仅快和方便，而且交换时也简便容易。

很简单，只需要把将要交换的两个节点及它们周围四联通的节点（即它们会影响到的节点）都存起来，并取消它们对 $val$ 的影响，然后再交换那两个节点，再统计存起来的所有节点对 $val$ 的影响即可。

## 4

综上，考虑我们要进行的操作。显然，我们要实时统计 $val$ 中有多少个 $val_i$ 的值为 $1$，并且在进行交换座位操作时，还要对 $val$ 中某一区间的值进行修改。

一言以蔽之，即全局最小值个数 + 区间修改。

那不就是线段树嘛。

再提一下为什么可以将“统计 $val$ 中有多少个 $val_i$ 的值为 $1$”转换为“全局最小值个数”。因为当只有第一个节点被染成黑色时，它必定是一个矩形，即 $val_1 = 1$。所以直接统计全局最小值个数即可。

注意将下标全部加一之后再统计操作。

# Code

$99$ 行的排座位，你值得拥有。

````cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(register int i = a; i <= b; ++i)
inline int rd(){
    int x = 1, s = 0; char ch = getchar();
    while(ch < '0' or ch > '9'){if(ch == '-') x = -1; ch = getchar();}
    while(ch >= '0' and ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return x * s;
}
const int inf = 2147483647;
const int maxn = 1e6 + 5;
#define num(x, y) ky[(x - 1) * w + y]
#define r(i) a[i].r
#define c(i) a[i].c
int h, w, q, s;
struct seat{
	int r, c;
}a[maxn];
int ky[maxn], val[maxn];
int fx[4][2] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}}, st[maxn], tot;
struct segment_tree{
	#define ls(x) (x << 1)
	#define rs(x) (x << 1 | 1)
	struct tree{
		int mn, sum, lz;
	}t[maxn << 2];
	inline void up(int i){
		int x, y; t[i].sum = 0;
		t[i].mn = min((x = t[ls(i)].mn), (y = t[rs(i)].mn));
		if(t[i].mn == x) t[i].sum += t[ls(i)].sum; 
		if(t[i].mn == y) t[i].sum += t[rs(i)].sum;
	}
	inline void build(int i, int l, int r){
		if(l == r){
			t[i].mn = val[l], t[i].sum = 1;
			return;
		}
		int mid = l + r >> 1;
		build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r), up(i);
	}
	inline void push_down(int i){
		t[ls(i)].mn += t[i].lz, t[rs(i)].mn += t[i].lz;
		t[ls(i)].lz += t[i].lz, t[rs(i)].lz += t[i].lz;
		t[i].lz = 0;
	}
	inline void update(int i, int l, int r, int L, int R, int k){
		if(L > R) return; 
		if(l >= L and r <= R){
			t[i].mn += k, t[i].lz += k;
			return;
		} push_down(i);int mid = l + r >> 1;
		if(L <= mid) update(i << 1, l, mid, L, R, k); if(R > mid) update(i << 1 | 1, mid + 1, r, L, R, k);
		up(i);
	}
}T; 
inline bool legal(int x, int y){ if(x >= 1 and x <= h and y >= 1 and y <= w) return 1; return 0;} 
inline int black(int x, int y){
	int mnn = inf, xx, yy;
	rep(i, 0, 1) if(legal((xx = x + fx[i][0]), (yy = y + fx[i][1])))
		mnn = min(mnn, num(xx, yy)); 
	return mnn;
}
inline int white(int x, int y){
	int mnn = inf, mxn = inf, xx, yy;
	rep(i, 0, 3) if(legal((xx = x + fx[i][0]), (yy = y + fx[i][1])))
		if(num(xx, yy) < mxn) mnn = mxn, mxn = num(xx, yy);
		else if(num(xx, yy) < mnn) mnn = num(xx, yy);
	return mnn;
}
int main(){
	int xx, yy, u, v; h = rd(), w = rd(), q = rd(), s = h * w;
	rep(i, 1, s) num((a[i].r = rd() + 1), (a[i].c = rd() + 1)) = i;
	rep(i, 1, s){ val[i] = val[i - 1];
		if(black(r(i), c(i)) > i) val[i] += 1;
		if(white(r(i), c(i)) < i) val[i] -= 1;
		rep(j, 0, 3) if(legal((xx = r(i) + fx[j][0]), (yy = c(i) + fx[j][1]))){
			if(black(xx, yy) == i and num(xx, yy) < i) val[i] -= 1;
			if(white(xx, yy) == i and num(xx, yy) > i) val[i] += 1;
		}
	} T.build(1, 1, s);
	rep(i, 1, q){
		u = rd() + 1, v = rd() + 1; if(u > v) swap(u, v);
		if(u == v){ printf("%d\n", T.t[1].sum); continue;}
		tot = 0, st[++tot] = u, st[++tot] = v;
		rep(j, 0, 3) if(legal((xx = r(u) + fx[j][0]), (yy = c(u) + fx[j][1]))) st[++tot] = num(xx, yy);
		rep(j, 0, 3) if(legal((xx = r(v) + fx[j][0]), (yy = c(v) + fx[j][1]))) st[++tot] = num(xx, yy);
		sort(st + 1, st + tot + 1);
		rep(j, 1, tot) if(st[j] != st[j - 1]){
			if((xx = white(r(st[j]), c(st[j]))) < st[j]) T.update(1, 1, s, max(u, xx), min(v, st[j]) - 1, -1);
			if((xx = black(r(st[j]), c(st[j]))) > st[j]) T.update(1, 1, s, max(u, st[j]), min(v, xx) - 1, -1);
		}
		swap(num(r(u), c(u)), num(r(v), c(v))), swap(a[u], a[v]);
		rep(j, 1, tot) if(st[j] != st[j - 1]){
			if((xx = white(r(st[j]), c(st[j]))) < st[j]) T.update(1, 1, s, max(u, xx), min(v, st[j]) - 1, 1);
			if((xx = black(r(st[j]), c(st[j]))) > st[j]) T.update(1, 1, s, max(u, st[j]), min(v, xx) - 1, 1);
		}
		printf("%d\n", T.t[1].sum);
	}
}
````


------------
感谢阅读。

辛苦管理员审核，如有问题烦请指出。

---

## 作者：Genius_Star (赞：1)

### 思路：

考虑问题的弱化：给定一些点，判断是否**恰好**构成一个矩形；先染色，将这些点染为黑色，其它点染为白色。

直接暴力判断肯定是可以的，但是我们需要转化为好维护的方式，为本题作出铺垫。

我们先考虑黑色点恰好为矩形的必要条件是什么？

- 首先必然存在左上角一个黑点满足左边和上边都是白点/空。

- 不存在一个白点，挨着大于一个黑点（即上下左右最多只有一个黑点）。

考虑这些必要条件是否是充分的：

- 若出现斜线型 $$\begin{bmatrix} 1 & 0 \\ 0 & 1\end{bmatrix}$$，则这个左下角与右上角若是白点则不符合要求的。

- 所以不能出现斜线型，所以必然为全黑矩形；但是此时可能构成了多个矩形，而每个矩形必然有一个黑色的满足第一个条件的点，故只有一个矩形。

所以我们可以定义：

- 黑点是满足条件的当且仅当：左边和上边都是白色/空。

- 白点是满足条件的当且仅当：上下左右至少有两个点是黑点。

我们需要统计满足条件的点的总数目，如果是 $1$ 则构成了矩形；因为如果有白点满足条件，则必然有至少一个黑点满足条件，所以若两者之间只有一个满足条件的，只能是黑点。

现在就可以做到 $O(HW)$ 判断是否是矩形了；回到原问题，时间复杂度可以直接做到 $O(Q(HW)^2)$，太慢了。

考虑若没有交换操作时，每个时刻相当于将一个白点染成黑点，最后问的是哪些时刻黑点恰好构成一个矩形；注意到很关键的一个性质，即一个点肯定是先白再黑的。

故我们可以考虑一个点 $(i, j)$ 作为黑点/白点时，在哪些时刻是满足条件的，设 $a_{i, j}$ 表示当且点被染成黑色的时刻：

- 黑点：需要满足左边和上边都是白点，即还没有染成黑点，时刻范围是 $[a_{i, j}, \min(a_{i - 1, j}, a_{i, j - 1}) - 1]$。

- 白点：需要满足上下左右至少有两个黑点，考虑找到上下左右第二个被染成黑点的时间 $get(i, j)$，那么时刻范围为 $[get(i, j), a_{i, j} - 1]$。

相当于作若干次区间 $+1$ 操作，最后查询全局为 $1$ 的个数，直接做的话可以差分，时间复杂度为 $O(QHW)$。

继续优化，注意到一个点是满足条件的只和它上下左右的点有关，所以交换两个点被染黑的时刻，只需要把两个点上下左右的点全部拉出来，先把之前的贡献消掉，再添加新的贡献。

这里由于是动态的查询，所以不能使用差分，换成线段树即可，全局 $1$ 的个数就是全局最小值的个数。

时间复杂度为 $O(Q \log (HW))$，注意常数很大。

### 完整代码：

```
 #include<bits/stdc++.h>
#define lowbit(x) x & (-x)
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define ctz(x) __builtin_ctz(x)
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 1e6 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, m, q, x, y;
int a[N], b[N];
int dx[] = {0, 0, 0, 1, -1}, dy[] = {0, 1, -1, 0, 0};
vector<pair<int, int>> V; 
vector<vector<int>> A;
namespace Seg{
	struct Node{
		int l, r;
		int Min, cnt, tag;
	}X[N << 2];
	inline void pushup(int k){
		X[k].cnt = 0;
		X[k].Min = min(X[k << 1].Min, X[k << 1 | 1].Min);
		if(X[k].Min == X[k << 1].Min)
		  X[k].cnt += X[k << 1].cnt;
		if(X[k].Min == X[k << 1 | 1].Min)
		  X[k].cnt += X[k << 1 | 1].cnt;
	}
	inline void add(int k, int v){
		X[k].Min += v;
		X[k].tag += v;
	}
	inline void push_down(int k){
		if(X[k].tag){
			add(k << 1, X[k].tag);
			add(k << 1 | 1, X[k].tag);
			X[k].tag = 0;
		}
	}
	inline void build(int k, int l, int r){
		X[k].l = l, X[k].r = r;
		if(l == r){
			X[k].Min = 0;
			X[k].cnt = 1;
			return ;
		}
		int mid = (l + r) >> 1;
		build(k << 1, l, mid);
		build(k << 1 | 1, mid + 1, r);
		pushup(k);
	}
	inline void update(int k, int l, int r, int v){
		if(X[k].l == l && r == X[k].r){
			add(k, v);
			return ;
		}
		push_down(k);
		int mid = (X[k].l + X[k].r) >> 1;
		if(r <= mid)
		  update(k << 1, l, r, v);
		else if(l > mid)
		  update(k << 1 | 1, l, r, v);
		else{
			update(k << 1, l, mid, v);
			update(k << 1 | 1, mid + 1, r, v);
		}
		pushup(k);
	}
};
int get(int a, int b, int c, int d){
    int min1 = min({a, b, c, d});
    int min2 = numeric_limits<int>::max();
    a = (a == min1) ? numeric_limits<int>::max() : a;
    b = (b == min1) ? numeric_limits<int>::max() : b;
    c = (c == min1) ? numeric_limits<int>::max() : c;
    d = (d == min1) ? numeric_limits<int>::max() : d;
    min2 = std::min({a, b, c, d});
    return min2;
}
inline void add(int l, int r, int v){
	r = min(r, n * m);
	Seg::update(1, l, r, v);
}
inline void calc(int i, int j, int v){
	if(min(A[i - 1][j], A[i][j - 1]) > A[i][j])
	  add(A[i][j], min(A[i - 1][j], A[i][j - 1]) - 1, v);
	int now = 0;
	if((now = get(A[i - 1][j], A[i][j - 1], A[i + 1][j], A[i][j + 1])) < A[i][j])
	  add(now, A[i][j] - 1, v);
}
inline void init(){
	for(int i = 1; i <= n; ++i)
	  for(int j = 1; j <= m; ++j)
		calc(i, j, 1);
}
inline void ins(int x, int y){
	for(int i = 0; i < 5; ++i){
		int zx = x + dx[i], zy = y + dy[i];
		if(zx < 1 || zx > n || zy < 1 || zy > m)
		  continue;
		V.push_back({zx, zy});
	}
}
bool End;
int main(){
//	open("award.in", "award.out");
	n = read(), m = read(), q = read();
	A.resize(n + 2);
	for(int i = 0; i <= n + 1; ++i)
	  A[i].resize(m + 2);
	for(int i = 0; i <= m; ++i)
	  A[0][i] = A[n + 1][i] = 1e9;
	for(int i = 0; i <= n; ++i)
	  A[i][0] = A[i][m + 1] = 1e9;
	for(int i = 1; i <= n * m; ++i){
		a[i] = read() + 1, b[i] = read() + 1;
		A[a[i]][b[i]] = i;
	}
	Seg::build(1, 1, n * m);
	init();
	while(q--){
		V.clear();
		x = read() + 1, y = read() + 1;
		ins(a[x], b[x]), ins(a[y], b[y]);
		sort(V.begin(), V.end());
		V.erase(unique(V.begin(), V.end()), V.end());
		for(auto t : V)
		  calc(t.fi, t.se, -1);
		swap(A[a[x]][b[x]], A[a[y]][b[y]]);
		swap(a[x], a[y]), swap(b[x], b[y]);
		for(auto t : V)
		  calc(t.fi, t.se, 1);
		write(Seg::X[1].cnt);
		putchar('\n');
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：⑨_Cirno_ (赞：1)

正解辣麽神像我这种水平不怎么行的OI选手怎么可能想得到。。。。。。

这里给出一种比较自然的想法

我们观察一下矩形有什么特点，最明显的显然是：它有四个角

所以我们每加入一个点，就维护当前图形左上，左下，右上，右下角分别有多少个

对于一个矩形显然答案都是1，而且最小也只能是1。。。。。。

这样就能分开考虑每一个点在什么时候作为其中一个角

考虑它作为左上角，则它是1且上方和左方的显然是0

这样就很容易求出它作为左上角的时间段

另外三种角也是这样

因为角的个数最小只能是1，所以维护最小值的个数就行了

当我终于调好，满心欢喜地交上去时，发现WA33。。。。。。

Why？？？为什么？？？

仔细观察发现，当它是一个框框时，我就挂了。。。。。。

再来观察它和框有什么区别，矩形中间是没有0的，所以不存在一个0使得左边和上边是1，而框一定存在

这样我们就把框和矩形区别开来辣

修改的时候我们可以先减掉原数的贡献，再对调加进去，然而在这两个数相邻的时候又锅了~~~

删掉一个数的时候，原来位置就成了空位，所以我们要塞一个h\*w+1进去，然后再把它移到目标位置，再删掉这个h\*w+1，再把另一个数塞回来

复杂度O(nlogn)，常数巨大（这样只是想法比较容易，~~线段树维护5个值还不被正解打爆~~

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long LL;
const long long M=1000000007;
#define ri register int 
#define rl register long long
int h,w,q,a[1000005],x[1000005],y[1000005],mnn[4000005],u,v,n;
inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
    char ch=nc();int sum=0;
    while(!(ch>='0'&&ch<='9'))ch=nc();
    while(ch>='0'&&ch<='9')sum=sum*10+ch-48,ch=nc();
    return sum;
}
inline int d(int x,int y)
{
	if(x==0||y==0||x>h||y>w)
		return 0;
	return (x-1)*w+y;
}
struct str{
	int a[5];
}tree[4000005],lazy[4000005];
inline bool cmp(str a,str b)
{
	if(a.a[0]!=b.a[0])
		return a.a[0]<b.a[0];
	if(a.a[1]!=b.a[1])
		return a.a[1]<b.a[1];
	if(a.a[2]!=b.a[2])
		return a.a[2]<b.a[2];
	if(a.a[3]!=b.a[3])
		return a.a[3]<b.a[3];
	return a.a[4]<b.a[4];
}
bool operator ==(str a,str b)
{
	return (a.a[0]==b.a[0])&&(a.a[1]==b.a[1])&&(a.a[2]==b.a[2])&&(a.a[3]==b.a[3])&&(a.a[4]==b.a[4]);
}
void pushup(int i)
{
	if(cmp(tree[i<<1],tree[i<<1|1]))
		tree[i]=tree[i<<1];
	else
		tree[i]=tree[i<<1|1];
	mnn[i]=0;
	if(tree[i]==tree[i<<1])
		mnn[i]=mnn[i<<1];
	if(tree[i]==tree[i<<1|1])
		mnn[i]+=mnn[i<<1|1];
	tree[i].a[0]+=lazy[i].a[0];
	tree[i].a[1]+=lazy[i].a[1];
	tree[i].a[2]+=lazy[i].a[2];
	tree[i].a[3]+=lazy[i].a[3];
	tree[i].a[4]+=lazy[i].a[4];
}
void modify(int i,int l,int r,int ll,int rr,int x,int y)
{
	if(l>=ll&&r<=rr)
	{
		lazy[i].a[x]+=y;
		tree[i].a[x]+=y;
		return;
	}
	int mid=l+r>>1;
	if(mid>=ll)
		modify(i<<1,l,mid,ll,rr,x,y);
	if(mid<rr)
		modify(i<<1|1,mid+1,r,ll,rr,x,y);
	pushup(i);
}
void Cirno(int i,int j,int t)
{
	if(min(a[d(i-1,j)],a[d(i,j-1)])>a[d(i,j)])
		modify(1,1,n,a[d(i,j)],min(a[d(i-1,j)],a[d(i,j-1)])-1,0,t);
	if(min(a[d(i+1,j)],a[d(i,j-1)])>a[d(i,j)])
		modify(1,1,n,a[d(i,j)],min(a[d(i+1,j)],a[d(i,j-1)])-1,1,t);
	if(min(a[d(i-1,j)],a[d(i,j+1)])>a[d(i,j)])
		modify(1,1,n,a[d(i,j)],min(a[d(i-1,j)],a[d(i,j+1)])-1,2,t);
	if(min(a[d(i+1,j)],a[d(i,j+1)])>a[d(i,j)])
		modify(1,1,n,a[d(i,j)],min(a[d(i+1,j)],a[d(i,j+1)])-1,3,t);
	if(max(a[d(i-1,j)],a[d(i,j-1)])<a[d(i,j)])
		modify(1,1,n,max(a[d(i-1,j)],a[d(i,j-1)]),a[d(i,j)]-1,4,t);
	if(i!=h)
	{
		if(min(a[d(i,j)],a[d(i+1,j+1)])>a[d(i+1,j)])
			modify(1,1,n,a[d(i+1,j)],min(a[d(i,j)],a[d(i+1,j+1)])-1,2,t);
		if(min(a[d(i,j)],a[d(i+1,j-1)])>a[d(i+1,j)])
			modify(1,1,n,a[d(i+1,j)],min(a[d(i,j)],a[d(i+1,j-1)])-1,0,t);
		if(max(a[d(i,j)],a[d(i+1,j-1)])>a[d(i+1,j)])
			modify(1,1,n,max(a[d(i,j)],a[d(i+1,j-1)]),a[d(i+1,j)]-1,4,t);
	}
	if(j!=w)
	{
		if(min(a[d(i,j)],a[d(i+1,j+1)])>a[d(i,j+1)])
			modify(1,1,n,a[d(i,j+1)],min(a[d(i,j)],a[d(i+1,j+1)])-1,1,t);
		if(min(a[d(i,j)],a[d(i-1,j+1)])>a[d(i,j+1)])
			modify(1,1,n,a[d(i,j+1)],min(a[d(i,j)],a[d(i-1,j+1)])-1,0,t);
		if(max(a[d(i-1,j+1)],a[d(i,j)])>a[d(i,j+1)])
			modify(1,1,n,max(a[d(i-1,j+1)],a[d(i,j)]),a[d(i,j+1)]-1,4,t);
	}
	if(i!=1)
	{
		if(min(a[d(i,j)],a[d(i-1,j+1)])>a[d(i-1,j)])
			modify(1,1,n,a[d(i-1,j)],min(a[d(i,j)],a[d(i-1,j+1)])-1,3,t);
		if(min(a[d(i,j)],a[d(i-1,j-1)])>a[d(i-1,j)])
			modify(1,1,n,a[d(i-1,j)],min(a[d(i,j)],a[d(i-1,j-1)])-1,1,t);
	}
	if(j!=1)
	{
		if(min(a[d(i,j)],a[d(i+1,j-1)])>a[d(i,j-1)])
			modify(1,1,n,a[d(i,j-1)],min(a[d(i,j)],a[d(i+1,j-1)])-1,3,t);
		if(min(a[d(i,j)],a[d(i-1,j-1)])>a[d(i,j-1)])
			modify(1,1,n,a[d(i,j-1)],min(a[d(i,j)],a[d(i-1,j-1)])-1,2,t);
	}
}
void Build(int i,int l,int r)
{
	if(l==r)
	{
		mnn[i]=1;
		return;
	}
	int mid=l+r>>1;
	Build(i<<1,l,mid);
	Build(i<<1|1,mid+1,r);
	mnn[i]=mnn[i<<1]+mnn[i<<1|1];
}
int main()
{
	h=read(),w=read(),q=read();
	n=h*w;
	for(ri i=1;i<=n;++i)
	{
		x[i]=read(),y[i]=read();
		++x[i],++y[i];
		a[d(x[i],y[i])]=i;
	}
	Build(1,1,n);
	a[0]=n+1;
	for(ri i=1;i<=h;++i)
		for(ri j=1;j<=w;++j)
		{
			if(min(a[d(i-1,j)],a[d(i,j-1)])>a[d(i,j)])
				modify(1,1,n,a[d(i,j)],min(a[d(i-1,j)],a[d(i,j-1)])-1,0,1);
			if(min(a[d(i+1,j)],a[d(i,j-1)])>a[d(i,j)])
				modify(1,1,n,a[d(i,j)],min(a[d(i+1,j)],a[d(i,j-1)])-1,1,1);
			if(min(a[d(i-1,j)],a[d(i,j+1)])>a[d(i,j)])
				modify(1,1,n,a[d(i,j)],min(a[d(i-1,j)],a[d(i,j+1)])-1,2,1);
			if(min(a[d(i+1,j)],a[d(i,j+1)])>a[d(i,j)])
				modify(1,1,n,a[d(i,j)],min(a[d(i+1,j)],a[d(i,j+1)])-1,3,1);
			if(max(a[d(i-1,j)],a[d(i,j-1)])<a[d(i,j)])
				modify(1,1,n,max(a[d(i-1,j)],a[d(i,j-1)]),a[d(i,j)]-1,4,1);
		}
	while(q--)
	{
		u=read(),v=read();
		++u,++v;
		Cirno(x[u],y[u],-1);
		int tmp=a[d(x[u],y[u])];
		a[d(x[u],y[u])]=n+1;
		Cirno(x[u],y[u],1);
		Cirno(x[v],y[v],-1);
		int t=a[d(x[v],y[v])];
		a[d(x[v],y[v])]=tmp;
		Cirno(x[v],y[v],1);
		Cirno(x[u],y[u],-1);
		a[d(x[u],y[u])]=t;
		Cirno(x[u],y[u],1);
		swap(x[u],x[v]);
		swap(y[u],y[v]);
		printf("%d\n",mnn[1]);
	}
}
```




---

