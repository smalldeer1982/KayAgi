# Pudding Monsters

## 题目描述

In this problem you will meet the simplified model of game Pudding Monsters.

An important process in developing any game is creating levels. A game field in Pudding Monsters is an $ n×n $ rectangular grid, $ n $ of its cells contain monsters and some other cells contain game objects. The gameplay is about moving the monsters around the field. When two monsters are touching each other, they glue together into a single big one (as they are from pudding, remember?).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526F/20aa5815ee72cc21be376a3c3bc47e609a6b5dc1.png)Statistics showed that the most interesting maps appear if initially each row and each column contains exactly one monster and the rest of map specifics is set up by the correct positioning of the other game objects.

A technique that's widely used to make the development process more efficient is reusing the available resources. For example, if there is a large $ n×n $ map, you can choose in it a smaller $ k×k $ square part, containing exactly $ k $ monsters and suggest it as a simplified version of the original map.

You wonder how many ways there are to choose in the initial map a $ k×k $ ( $ 1<=k<=n $ ) square fragment, containing exactly $ k $ pudding monsters. Calculate this number.

## 样例 #1

### 输入

```
5
1 1
4 3
3 2
2 4
5 5
```

### 输出

```
10
```

# 题解

## 作者：xht (赞：47)

> [CF526F Pudding Monsters](https://codeforces.com/contest/526/problem/F)

## 题意

- 给定一个 $n \times n$ 的棋盘，其中有 $n$ 个棋子，每行每列恰好有一个棋子。
- 求有多少个 $k \times k$ 的子棋盘中恰好有 $k$ 个棋子。
- $n \le 3 \times 10^5$。

## 题解

将二维问题转化为一维问题，即构造一个序列 $a_{1\dots n}$，对于一个点 $(x,y)$，$a_x = y$。

则原问题转化为经典的连续段计数问题。

本题没有重复元素，那也就是统计 $\max - \min + 1 = \operatorname{len}$ 的区间个数。

将右端点向右扫，用单调栈维护当前每个后缀的 $\max$ 和 $\min$，然后用线段树维护当前每个后缀的 $\max - \min - \operatorname{len}$ 的值，以及每个后缀区间的值的最小值以及最小值的个数。

显然 $\max - \min - \operatorname{len} \ge -1$，同时对于每个右端点 $r$，至少会有一个后缀的值为 $-1$（$l = r$ 时），因此每个右端点对答案的贡献都是当前后缀区间的值的最小值的个数。

时间复杂度 $\mathcal O(n \log n)$。

下面的代码其实可以处理有重复元素的情况，这时候我们需要统计的就是 $\max - \min + 1 = \operatorname{cnt}$ 的区间个数，其中 $\operatorname{cnt}$ 为区间中不同的数的个数，那么记录一下每个数上一次出现的位置即可。

## 代码

```cpp
const int N = 3e5 + 7;
int n, a[N], sx[N], tx, sn[N], tn;
map <int, int> p;
struct T {
	int l, r, x, c, z;
} t[N<<2];
ll ans;

void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r, t[p].c = r - l + 1;
	if (l == r) return;
	build(ls, l, md), build(rs, md + 1, r);
}

inline void add(int p, int x) {
	t[p].x += x, t[p].z += x;
}

void upd(int p, int l, int r, int x) {
	if (t[p].l >= l && t[p].r <= r) return add(p, x);
	if (t[p].z) add(ls, t[p].z), add(rs, t[p].z), t[p].z = 0;
	if (l <= md) upd(ls, l, r, x);
	if (r > md) upd(rs, l, r, x);
	t[p].x = min(t[ls].x, t[rs].x);
	t[p].c = (t[ls].x == t[p].x ? t[ls].c : 0) + (t[rs].x == t[p].x ? t[rs].c : 0);
}

int main() {
	rd(n);
	for (int i = 1, x, y; i <= n; i++) rd(x), rd(y), a[x] = y;
	build(1, 1, n);
	for (int i = 1; i <= n; i++) {
		while (tx && a[sx[tx]] < a[i]) upd(1, sx[tx-1] + 1, sx[tx], -a[sx[tx]]), --tx;
		while (tn && a[sn[tn]] > a[i]) upd(1, sn[tn-1] + 1, sn[tn], a[sn[tn]]), --tn;
		upd(1, p[a[i]] + 1, i, -1), p[a[i]] = sx[++tx] = sn[++tn] = i;
		upd(1, sx[tx-1] + 1, i, a[i]), upd(1, sn[tn-1] + 1, i, -a[i]);
		ans += t[1].c;
	}
	print(ans);
	return 0;
}
```

---

## 作者：Holy_Push (赞：38)

t举报$CF$自抄现象严重！（$997E$是这道题的加强版）今天看到了这道题就来水一发吧。

题目有一个很好的性质，就是每行每列都有且仅有一个点，所以也就是说，如果一个$k×k$的矩形里有$k$个点$(x_1,y_1),(x_2,y_2)...(x_k,y_k)$，则$max\{ x_k \}-min\{ x_k \}+1=k,max\{ y_k\}-max\{ y_k \}+1=k$。

二维的比较难处理，我们先对$x$这一维排序，那么就只需要处理$y$这一维了。现在问题变成了：给定一个数组（一定为一个排列），求其中子排列（也是排列的子串）的数量。

考虑子排列的性质。记排序好的数组为$\{ a_n\}$，若$[l,r]$为一个子排列，则满足：$Max-Min=r-l$，移项得$Max-Min+l-r=0$。于是我们只要维护$Max-Min+l-r=0$的组数即可。

发现$=0$的数量比较难维护，但我们发现，由于原串是一个排列，所以对于任何一个子串，都有$Max-Min+l-r≥0$。于是维护$0$的数量可以转化为维护最小值以及最小值的数量，这样就比较好维护了。

然后考虑如何维护上面这个东西。

对于子串信息的查询，有一种比较套路的做法就是扫描线。本题中对$r$做扫描线。假设我们右端点扫描到了$r$，记线段树t上的节点$[L,R]$表示原序列中$[L,r],[L+1,r],...,[R,r]$这些区间$Max-Min+l-r$的最小值和最小值出现次数。然后我们分别分析$l,r,Max,Min$这四个量如何维护。

对于$l$：显然，因为是右端点在移动，所以每个维护量的$l$是不会变的，所以可以一开始就把$l$的贡献做掉。

对于$r$：显然，右端点每次向右移一位，所以$Max-Min+l-r$的值都先会减1，因此我们只要区间$-1$即可。

对于$Max$，有点复杂，我们用一个元素单调递减的栈来维护。记栈为$stk$，栈顶编号为$top$。如果$a[stk[top]]$比$a[r]$小，那么显然需要更新线段树上$stk[top-1]+1$至$stk[top]$的这个区间，弹出栈顶元素。最后再把$r$加入到单调栈中。

对于$Min$，处理方法与$Max$一样。

最后扫描线每移动一次，都要统计一次答案。这道题就算做完了。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define ll long long
const int N=500000;
int n,top1,top2;
ll ans;
struct chess
{
	int x,y;
	bool operator <(const chess &P) const {return x<P.x;}
}c[N],stk1[N],stk2[N];
struct node
{
	int Min,tag;ll cnt;
} t[N<<2];

void build(int i,int l,int r)
{
	if (l==r) {t[i].Min=l;t[i].cnt=1;return;}
	int mid=(l+r)>>1;
	build(i<<1,l,mid);build(i<<1|1,mid+1,r);
	t[i]=t[i<<1];
}

void pushdown(int i)
{
	int ls=i<<1,rs=ls|1;
	t[ls].Min+=t[i].tag;t[rs].Min+=t[i].tag;
	t[ls].tag+=t[i].tag;t[rs].tag+=t[i].tag;
	t[i].tag=0;
}

void pushup(int i)
{
	int ls=i<<1,rs=ls|1;
	t[i].Min=min(t[ls].Min,t[rs].Min);t[i].cnt=0;
	if (t[i].Min==t[ls].Min) t[i].cnt+=t[ls].cnt;
	if (t[i].Min==t[rs].Min) t[i].cnt+=t[rs].cnt;
}

void update(int i,int l,int r,int x,int y,int val)
{
	if (l>=x&&r<=y) {t[i].Min+=val;t[i].tag+=val;return;}
	int mid=(l+r)>>1;pushdown(i);
	if (mid>=x) update(i<<1,l,mid,x,y,val);
	if (mid<y) update(i<<1|1,mid+1,r,x,y,val);
	pushup(i);
}

int query(int i,int l,int r,int x,int y)
{
	if (l>=x&&r<=y) return t[i].Min==0?t[i].cnt:0;
	int mid=(l+r)>>1,ans=0;pushdown(i);
	if (mid>=x) ans+=query(i<<1,l,mid,x,y);
	if (mid<y) ans+=query(i<<1|1,mid+1,r,x,y);
	return ans;
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&c[i].x,&c[i].y);
	sort(c+1,c+n+1);build(1,1,n);
	for (int i=1;i<=n;i++)
	{
		update(1,1,n,1,n,-1);
		while (top1&&stk1[top1].y<c[i].y)
			update(1,1,n,stk1[top1-1].x+1,stk1[top1].x,c[i].y-stk1[top1].y),--top1;
		stk1[++top1]={i,c[i].y};
		while (top2&&stk2[top2].y>c[i].y)
			update(1,1,n,stk2[top2-1].x+1,stk2[top2].x,stk2[top2].y-c[i].y),--top2;
		stk2[++top2]={i,c[i].y};
		ans+=query(1,1,n,1,i);
	}
	printf("%lld\n",ans);
}
```



---

## 作者：Vocanda (赞：23)

# 题目
[题目链接](https://www.luogu.com.cn/problem/CF526F)

# 分析
楼下许多大佬都是写的线段树的分析，蒟蒻来一发分治的题解吧。

### 题意
$1$、一个$n\times n$的矩阵里每行每列都只有一个$Pudding Monsters $

$2$、找$k\times k$的矩阵满足其中有$k$个$Pudding Monsters $

$3$、$n\le 3\times 10^5,1\le k \le n $

### 分治
分治思想就是把一段长区间上的问题分到一个个子问题来进行解决，最后分别统计答案。

这个题因为给出的是一个二维平面，所以我们需要转化为一维。题目中有一个很重要的性质：**每一行和每一列都只有一个点**。
所以我们就可以直接把当前列的$Pudding Monsters $在哪一行记录下来，我们就得到了一个序列，然后开始分治解决。我们的问题就简化为了有多少区间$[l,r]$使$Max-Min=l-r$成立，其中$Max,Min$分别为区间$[l,r]$的最大和最小值。

我们把每一个区间分成两部分$[l,mid],[mid+1,r]$，分成一个个的子问题来解决。所以我们在当前情况下只需要考虑跨过$mid$的情况就可以了，其他的都是递归的子问题。

我们需要先预处理最大和最小值。设$mx[i]$和$mn[i]$为最大和最小数组，那么$l\le i\le mid$时，这两个数组表示的是从$i$到$mid$的最大和最小，而$mid+1\le i\le r$时两个数组表示从$mid+1$到$i$的最大和最小。

单个点我们先不必考虑，因为单个点就直接让答案$ans++$就行了，表示一个$1\times 1$的合法状态。

下面我们来分析两个分开的区间合并的问题，那么一共有四种情况：

$1$、最大最小都在左区间，上面已经分析过，如果有区间$[l,r]$使$Max-Min=l-r$成立，那么就是一个情况。所以我们枚举左端点$i$，那么根据上式得到$j=i+mx[i]-mn[i]$。
$2$、最大最小都在右区间，那么枚举右端点$i$，则左端点$j=i-(mx[i]-mn[i])$。

以上两种情况都很好分析，确定了一个端点，那么另一个端点就确定了，我们直接$ans++$就行了。

下边是两种比较复杂的情况：

$1$、最小值在左，最大在右，那么我们就可以根据上边说到的那个式子得出来枚举左端点$i$，那么右端点和其的关系就是$mx[j]-mn[i] = j-i\to mn[i]-i=mx[j]-j$

$2$、与上边相反，最小值在右，最大在左，那么我们枚举右端点$i$，则得到$mx[j]-mn[i] = i-j\to mn[i]+i=mx[j]+j$

这两种情况都是一端确定，但是另一端无法确定，以复杂情况$1$为例，左小右大，那么枚举左端点，右端点并不确定，所以我们每一次向右扫描，$mx[j]$都是会变的，但是不用每一个$i$都扫描一遍$j$。因为当 $i--$ 的时候，如果左侧增加的这个数更新了最小值，则上一轮已经扫描过 $mid+1∼j$ 仍然满足 $mn[j]>mn[i]$ 。如果增加的是一个较大的数且大于了 $mx[j]$ 此时我们也只需往后扫描找到当前的满足条件的 $j$ 即可。

具体实现方式就是我们定义两个指针位置，$j$和$k$都代表右边的点，我们用上边说到的条件$mx[j]-mn[i] = j-i\to mn[i]-i=mx[j]-j$当作下标，如果满足条件就让下标为$mx[j]-j$的那个位置的答案加一。拿情况$1$举例，设记录数组为$jl[i]$，如果右边枚举到的$j$的最小大于$mn[i]$，那么就让$jl[mx[j]-j+n]++$其中加$n$是为了避免出现负的下标。而我们定义的另一个指针$k$是用来善后的，也就是说在$k<j$的情况下，如果$mx[k]$比左边的$mx[i]$还小，那么我们让其对应的下标的$jl[mx[k]-k+n]--$。因为一开始我们记录答案用的是$mx[j]-j+n$，所以最后只需要按照当前状况下的满足条件$mx[j]-j=mn[i]-i$让下标变成$mn[i]-i+n$来记录，这样我们得到的就都是合法情况了，第二种情况和这个是一样的，但是要注意的是每一次都要清空之前的数组，避免出现问题。具体一些会在代码里注释。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 1e5+10;
int mn[maxn],mx[maxn],jl[maxn<<1];
ll ans;
int n,a[maxn];
void fenz(int l,int r){
	if(l == r){//统计1×1的情况
		ans++;
		return;
	}
	int mid = (l+r)>>1;
	fenz(l,mid);//递归处理子序列
	fenz(mid+1,r);
	mx[mid] = mn[mid] = a[mid];//初始化
	mx[mid+1] = mn[mid+1] = a[mid+1];
	for(int i=mid-1;i>=l;--i){//初始化每个左区间端点的最大最小值
		mx[i] = max(mx[i+1],a[i]);
		mn[i] = min(mn[i+1],a[i]);
	}
	for(int i=mid+2;i<=r;++i){//初始化每个右区间端点的最大最小值
		mx[i] = max(mx[i-1],a[i]);
		mn[i] = min(mn[i-1],a[i]);
	}
	for(int i=mid;i>=l;--i){//最大最小都在左边
		int j=mx[i]-mn[i]+i;//直接按照条件进行
		if(j<=r && j>mid && mx[j]<mx[i] && mn[i]<mn[j])ans++;
	}
	for(int i=mid+1;i<=r;++i){//都在右边
        int j=i-mx[i]+mn[i];
        if(j<=mid && j>=l && mx[j]<mx[i] && mn[j]>mn[i])
            ans++;
    }
    int j=mid+1,k=mid+1;
    for(int i=mid;i>=l;--i){//左小右大，mn[i]-i=mx[j]-j
    	while(j<=r && mn[j]>mn[i]){//右边最小比左边最小大
    		jl[mx[j]-j+n]++;//条件作为下标让jl数组++
    		j++;//继续向后枚举
    	}
    	while(k<j && mx[k]<mx[i]){//善后，如果右边最大比左边还小，不符合
    		jl[mx[k]-k+n]--;//直接让当前条件--
    		k++;
    	}
    	ans+=(ll)jl[mn[i]-i+n];//最后用条件的另一边统计答案，这样统计到的就都是满足条件的答案
    }
    while(k<j){//清空，不要用memset，会TLE
    	jl[mx[k]-k+n]--;
    	k++;
    }
    j=mid;
    k=mid;
    for(int i=mid+1;i<=r;++i){//左大右小，以下具体与上边一样
    	while(j>=l && mn[j]>mn[i]){
    		jl[mx[j]+j]++;
    		--j;
    	}
    	while(k>j && mx[k]<mx[i]){
    		jl[mx[k]+k]--;
    		k--;
    	}
    	ans+=(ll)jl[mn[i]+i];
    }
    while(k>j){//再清空
    	jl[mx[k]+k]--;
    	k--;
    }
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		a[x] = y;//将二维平面转到一个序列上
	}
	fenz(1,n);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：ShuYuMo (赞：14)

[MyBlog](https://shuyumo2003.github.io/2020/%E3%80%8C%E9%A2%98%E5%8D%95%E3%80%8DIOI2020%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F%E4%BD%9C%E4%B8%9A-Part-1/#CF526F-Pudding-Monsters)
# CF526F Pudding Monsters

- 给定一个 $n \times n$ 的棋盘，其中有 $n$ 个棋子，每行每列恰好有一个棋子。
- 求有多少个 $k \times k$ 的子棋盘中恰好有 $k$ 个棋子。
- $n \le 3 \times 10^5$。

每行每列**恰好有一个**棋子的棋盘，可以抽象成一个排列。 而操作也是对于一个排列的一段进行操作的。

题意可以转化为：
 - 给出一个排列
 - 求连续段数量，即连续的一段，且段中的元素排好序之后必须是公差为$1$的等差数列.

**连续段计数**

考虑如何刻画“**连续的一段，且段中的元素排好序之后必须是公差为$1$的等差数列**”这个条件，可以形式化的定义：

$$\operatorname{MaxVal} - \operatorname{MinVal} = (R - L)$$

即

$$f_{R}(L) = \operatorname{MaxVal} - \operatorname{MinVal} - (R - L) = 0$$

这个条件成立的基础在于，所求数列不能有重复元素，而且也保证了函数$f_x(L) \ge 0$, 查询时只需要维护**最小值**以及最小值的**数量**即可。

可以考虑枚举一个端点，比如右端点 $R$，然后查找有多少符合条件的左端点 $L$ ，用线段树维护$f_R(x)$在每个点处的函数值。

考虑当$f_x(L)$ 移动到 $f_{x + 1}(L)$ 时， 值的变化。变化的值有 $R$ , 可能变化的有$MaxVal, MinVal$。用单调栈实时维护更新后会波及哪些元素的最小值。事实上，单调栈处理的过程就是在动态维护一个后缀最小\大值数组。

这里有几个与其有相似之处的题目，但是可能做法并不一样，遇到不要想成一样的题目：
 - [算术天才⑨与等差数列](https://www.luogu.com.cn/problem/P5278) (不保证序列中一定元素不重复)
   - 考虑判断一个序列排好序后是否为等差数列
     - 准确做法
       - $\max−\min=(r−l)k$
       - 相邻两数差的绝对值的 $\operatorname{gcd}$是 $k$
       - 区间 $[l,r]$ 内的数不重复
     - 概率性做法
       - hash思想，维护 $n$ 次方和
 - [树上排列(ZROI)](http://www.zhengruioi.com/contest/718/problem/1615)  (同样不保证元素一定不重复) 
   - 给定一颗 $n$ 个点的树。每个点都一个正整数点权 $A_i$ ，你需要支持以下两种操作：
   - 1、询问点 $x$ 和点 $y$ 之间的路径上的所有点（包括点 $x$ 和点 $y$ ）的点权是否构成一个从 $1$ 开始的排列（即若这条链长度为 $len$ ，那么问点权集合为 ${1,2,⋯,len}$ ）。
   - 2、将 $A_x$ 修改为 $y$ 。
   - 由于在树上难以判断某区间内的数字不重复，Hash维护n次方和。
 - 给出一个没有重复元素的序列，询问某区间中的元素是否能加入小于$k$个元素使其拍好序后构成一个等差数列。
   - 条件变成了 $$f_{R}(L) = \operatorname{MaxVal} - \operatorname{MinVal} - (R - L) \ge k$$
 - [count(ZROI)](http://www.zhengruioi.com/problem/1532)已知一个集合$S$中的最大元素为 $N$， 且这个集合中的元素可以构成一个等差数列，给出一些形如$x \in S$、$x \notin S$的限制。求最终的集合有多少种情况。
   - 考虑刻画一个等差数列需要什么参数：公差，和每个元素$\bmod $ 公差的值。枚举这两个参数，依次计数即可。

（引用正睿的两道题目，不知道是不是有版权问题，如果有，会立即删除（~~顺便给正睿OI打个广告~~））。

## code
{% note info CF526F Pudding Monsters %}
```cpp
int n;
int A[_];
#define fir first
#define sec second
namespace SegmentTree{
    const int _ = 3e6 + 100;
    struct Node{
        int MIN;
        int sMIN;
        int tar;
        Node operator + (const Node & rhs) const {
            Node res;
            res.MIN  = min(MIN, rhs.MIN);
            res.sMIN = MIN == rhs.MIN ? ( sMIN + rhs.sMIN) : (MIN < rhs.MIN ? sMIN : rhs.sMIN) ;
            return res;
        }
    }v[_];
    int tot = 0;
    int ch[_][2];
    #define ls(o) (ch[o][0])
    #define rs(o) (ch[o][1])
    #define make (tot++, ch[tot][0] = ch[tot][1] = v[tot].MIN = v[tot].sMIN = 0, tot)
    int Groot() { return make; }
    void maintain(int o) {
        v[o].MIN  = min(v[ls(o)].MIN, v[rs(o)].MIN);
        v[o].sMIN = v[ls(o)].MIN == v[rs(o)].MIN ? v[ls(o)].sMIN + v[rs(o)].sMIN : ( v[ls(o)].MIN < v[rs(o)].MIN ? v[ls(o)].sMIN : v[rs(o)].sMIN );
    }
    void tar(int o, int x) { v[o].MIN += x; v[o].tar += x; }
    void pushdown(int o){
        if(v[o].tar){
            tar(ls(o), v[o].tar); tar(rs(o), v[o].tar);
            v[o].tar = 0;
        }
    }
    void build(int o, int L, int R){
        if(L == R) { v[o].MIN = 0; v[o].sMIN = 1; return; }
        int mid = (L + R) >> 1;
        ls(o) = make; rs(o) = make;
        build(ls(o), L, mid); build(rs(o), mid + 1, R);
        maintain(o);
    }
    void update(int o, int nowl, int nowr, int L, int R, int x){
        if(L > R) return ;
        if(L <= nowl && nowr <= R) return tar(o, x);
        int mid = (nowl + nowr) >> 1;  pushdown(o);
        if(L <= mid) update(ls(o), nowl, mid, L, R, x);
        if(R  > mid) update(rs(o), mid + 1, nowr, L, R, x);
        maintain(o);
    }
    Node query(int o, int nowl, int nowr, int L, int R) {
        if(L <= nowl && nowr <= R) return v[o];
        int mid = (nowl + nowr) >> 1; pushdown(o);
        Node Ans; Ans.MIN = INT_MAX;
        if(L <= mid) Ans = Ans + query(ls(o), nowl, mid, L, R);
        if(R  > mid) Ans = Ans + query(rs(o), mid + 1, nowr, L, R);
        return Ans;
    }
    int query(int o, int L, int R){
        Node res = query(o, 1, n, L, R);
        return res.MIN == 0 ? res.sMIN : 0;
    }
}  using SegmentTree::Groot; using SegmentTree::build; using SegmentTree::query; using SegmentTree::update;
namespace Mon_Stack{
    int t0t = 0, t1t = 0;
    pair<int, int> S0[_], S1[_];
    int work(int *A, int n){
        int Ans = 0;
        int root = Groot();
        build(root, 1, n);
        S0[0].fir = S1[0].fir = 0;
        for(int i = 1; i <= n; i++) {
            update(root, 1, n, 1, i - 1, -1);
            while(t0t != 0 && S0[t0t].sec >= A[i]) { update(root, 1, n, S0[t0t - 1].fir + 1, S0[t0t].fir,  S0[t0t].sec); t0t--; }
            while(t1t != 0 && S1[t1t].sec <= A[i]) { update(root, 1, n, S1[t1t - 1].fir + 1, S1[t1t].fir, -S1[t1t].sec); t1t--; }
            update(root, 1, n, S0[t0t].fir + 1, i, -A[i]);
            update(root, 1, n, S1[t1t].fir + 1, i, A[i]);
            int t = query(root, 1, i);
            Ans += t;
            S0[++t0t] = make_pair(i, A[i]); S1[++t1t] = make_pair(i, A[i]);
        }
        return Ans;
    }
} using Mon_Stack::work;
signed main(){
    n = read(); for(int i = 1; i <= n; i++) { int x = read(), y = read(); A[x] = y; }
    printf("%lld\n", work(A, n));
    return 0;
}
```
{% endnote %}
{% note info count(ZROI) %}
```cpp
#include <climits>
#include <cmath>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define int long long 
const int MOD = 1e9 + 7;
const int _M = 2e5 + 100;
inline int read() { char c = getchar(); int sign = 1; int x = 0; while(c > '9' || c < '0') { if(c=='-')sign = -1; c = getchar(); } while(c <= '9' && c >= '0') { x *= 10; x += c - '0'; c = getchar(); } return x * sign; }
int MAX, m;
int have[_M], tht = 0;
int none[_M], tnt = 0;
int d[_M], tdt = 0; 
int c[_M];//tct = tdt
bool CanBe[_M];
int ToL[_M];
int ToR[_M];
void divide(int s, int x) {
    for(int i = 1; i * i <= x; i++){
        if(x % i == 0) d[++tdt] = i, c[tdt] = s % i;
        if(i * i != x) d[++tdt] = x / i, c[tdt] = s % d[tdt];
    }
    for(int i = 1; i <= tdt; i++) CanBe[i] = true;
}
signed main(){
    int t;
    MAX = read(), m = read();
    for(int i = 1; i <= m; i++){
        int type = read();
        if(type == 1) have[++tht] = read();
        else          none[++tnt] = read();
    }
    sort(have + 1, have + 1 + tht); sort(none + 1, none + 1 + tnt);
    int maxd = INT_MAX, Sta;
    for(int i = 2; i <= tht; i++) {
        if(maxd > have[i] - have[i - 1]){
            maxd = have[i] - have[i - 1];
            Sta = have[i - 1];
        }
    }
    divide(Sta, maxd);

    /* 公差 及 特征 检查   */
    for(int i = 1; i <= tht; i++){
        for(int j = 1; j <= tdt; j++){
            if(!CanBe[j]) continue;
            if(have[i] % d[j] != c[j]) CanBe[j] = false;
        }
    }
    for(int i = 2; i <= tht; i++){
        int D = have[i] - have[i - 1];
        for(int j = 1; j <= tdt; j++){
            if(!CanBe[j]) continue;
            if(D % d[j] != 0) CanBe[j] = false;
        }
    }
    t = 0;
    for(int i = 1; i <= tdt; i++){
        if(!CanBe[i]) continue;
        d[++t] = d[i];
        c[  t] = c[i];
        CanBe[t] = true;
    } tdt = t;
    /* 公差 及 特征 检查   完成*/
    for(int i = 1; i <= tdt; i++) { 
        if(CanBe[i]) {
            ToL[i] = (c[i] == 0 ? d[i] : c[i]) - 1;
            int t = MAX % d[i];
            if(t == c[i]) ToR[i] = MAX + 1;
            if(t  > c[i]) ToR[i] = MAX - (t - c[i]) + 1;
            if(t  < c[i]) ToR[i] = MAX - d[i] + (c[i] - t) + 1;
        }
    }
    t = 0;
    for(int i = 1; i <= tdt; i++){
        if(!CanBe[i]) continue;
        d[++t] = d[i];
        c[  t] = c[i];
        CanBe[t] = true;
    } tdt = t;
    int MINS = have[1], MAXE = have[tht];
    for(int i = 1; i <= tnt; i++){
        int now = none[i];
        for(int j = 1; j <= tdt; j++){
            if(!CanBe[j]) continue;
            if(now % d[j] == c[j]){
                if(now < MINS)
                    ToL[j] = max(ToL[j], now);
                else if(now > MAXE)
                    ToR[j] = min(ToR[j], now);
                else CanBe[j] = false;
            }
        }
    }
    for(int i = 1; i <= tdt; i++) if(ToL[i] > MINS || ToR[i] < MAXE) CanBe[i] = false; else ToL[i]++, ToR[i] --;
    /* 非法数字存在性检查 */
    int ans = 0;
    for(int i = 1; i <= tdt; i++){
        if(!CanBe[i]) continue;
        int k = (  (MINS - ToL[i]) / d[i] + 1) * ( (ToR[i] - MAXE) / d[i] + 1) % MOD; // TODO;
        ans = (ans + k) % MOD;
    }
    printf("%lld", ans);
    return 0;
}
```
{% endnote %}
{% note info A.20联赛集训day3 树上排列(维护15次方和hash) %}
```cpp
#include <climits> 
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
inline int read() { char c = getchar(); int sign = 1; int x = 0; while(c > '9' || c < '0') { if(c=='-')sign = -1; c = getchar(); } while(c <= '9' && c >= '0') { x *= 10; x += c - '0'; c = getchar(); } return x * sign; }
using namespace std;
const int _ = 6e5 + 100;
const int base = 15;
const int MOD = 1020031005;
int SS[_];
int pow(int a, int b = base){ int ans = 1; while(b){ if(b & 1) ans = (ans *1ll* a) % MOD; a = (a *1ll* a) % MOD; b >>= 1; } return ans; }

int head[_];
int NodeVal[_];
struct edges{
	int node;
	int nxt;
}edge[_];
int tot = 0;
void add(int u, int v){
	tot++;
	edge[tot].node = v;
	edge[tot].nxt  = head[u];
	head[u]        = tot;
}

int n, q;
int dep[_], fa[_], dfn[_], rnk[_], top[_], son[_], si[_], dfc = 0;
void dfs0(int now, int f, int dp){
	int &S = si[now] = 1; int &Mid = son[now] = 0; fa[now] = f; dep[now] = dp;
	for(int i = head[now]; i ; i = edge[i].nxt){
		int ex = edge[i].node; if(ex == f) continue;
		dfs0(ex, now, dp + 1); S += si[ex];
		if(si[ex] > si[Mid]) Mid = ex;
	} if(!Mid) Mid = 0;
}
void dfs1(int now, int f, int tp){
	dfn[now] = ++dfc; rnk[dfc] = now;
	top[now] = tp;
	if(son[now]) dfs1(son[now], now, tp);
	for(int i = head[now]; i ; i = edge[i].nxt){
		int ex = edge[i].node; if(ex == f || ex == son[now]) continue;
		dfs1(ex, now, ex);
	}
}
void clear(){
	memset(head, 0, sizeof(head));
	dfn[0] = rnk[0] = si[0] = top[0] = fa[0] = son[0] = 0;
	tot = 0;
	dfc = 0; 
}
namespace SegmentTree{
	const int _ = 3e6 + 100;
	int tot = 0;
	int ch[_][2];
	int v[_];
	#define make (tot++, ch[tot][0] = ch[tot][1] = v[tot] = 0, tot);
	#define ls(x) (ch[x][0])
	#define rs(x) (ch[x][1])
	#define maintain(o) (v[o] = (v[ls(o)] +0ll+ v[rs(o)]) % MOD )
	void init_s() { tot = 0; }
	int  Groot(){ return make; }
	void build(int o, int L, int R){
		if(L == R) return (void)(v[o] = pow(NodeVal[rnk[L]]));
		int mid = (L + R) >> 1;
		ls(o) = make; rs(o) = make;
		build(ls(o), L, mid); build(rs(o), mid + 1, R);
		maintain(o);
	}
	void update(int o, int nowl, int nowr, int p, int x){
		if(nowl == nowr) return (void)(v[o] = pow(x));
		int mid = (nowl + nowr) >> 1;
		if(p <= mid) update(ls(o), nowl, mid, p, x);
		if(p  > mid) update(rs(o), mid + 1, nowr, p, x);
		maintain(o);
	}
	int query(int o, int nowl, int nowr, int L, int R){
		if(L > R) return 0;
		if(L <= nowl && nowr <= R) return v[o];
		int mid = (nowl + nowr) >> 1;
		int ans = 0;
		if(L <= mid) ans = (ans +0ll+ query(ls(o), nowl, mid, L, R)) % MOD;
		if(R  > mid) ans = (ans +0ll+ query(rs(o), mid + 1, nowr, L, R)) % MOD;
		return ans;
	}
} using SegmentTree::Groot; using SegmentTree::init_s; using SegmentTree::build; using SegmentTree::update; using SegmentTree::query;
int root = 0;
int LCA;
int QueryOnPath(int x, int y){
	int ans = 0;
	while(top[x] != top[y]){
		if(dep[top[x]] > dep[top[y]]) swap(x, y);
		ans = (ans +0ll+ query(root, 1, n, dfn[top[y]], dfn[y])) % MOD;
		y = fa[top[y]];
	}
	if(dep[x] < dep[y]) swap(x, y); LCA = y;
	ans = (ans +0ll+ query(root, 1, n, dfn[y], dfn[x])) % MOD; 
	return ans;
}
void doit(){
	clear();
	n = read(), q = read();
	for(int i = 1; i <= n; i++) NodeVal[i] = read();
	for(int i = 1; i <  n; i++){ int u = read(), v = read(); add(u, v); add(v, u); }
	dfs0(1, 1, 1);
	dfs1(1, 1, 1);
	init_s(); root = Groot();
	build(root, 1, n);
	while(q--){
		int opt = read(), x = read(), y = read();
		if(opt == 1){
			int r = QueryOnPath(x, y);
			int Len = dep[x] + dep[y] - (dep[LCA] << 1) + 1;
			puts(SS[Len] == r ? "Yes" : "No");
		} else{
			update(root, 1, n, dfn[x], y);
		}
	}
}
int main(){
	for(int i = 1; i <= 3e5; i++) SS[i] = ( SS[i - 1] +0ll+ pow(i) ) % MOD;
	int T = read();
	while(T--) doit();
	return 0;
}
```
{% endnote %}


---

## 作者：龙之吻—水货 (赞：7)

# CF526F Pudding Monsters
## 题目大意
有一个大小为 $n \times n$的网格，每一行每一列都有且仅有一只
$Pudding Monster$，求这个网格有多少个正方形子网格使得这个子网格的每一行每一列都有且仅有一只$Pudding Monster$。
## 解题报告
历史遗留问题终于在今天彻底解决了 QwQ

发现这是一个二维的问题，并不好做，我们尝试把它转化为一个一维的问题。

我们把所有的$Pudding Monster$按照$x$坐标排序，记此时$y$坐标形成数组为$a$，问题就转化为了 :

给出一个排列，求这个排列有多少个区间的值是连续的，也就是求满足一下条件的区间的个数 :

区间最大值 - 区间最小值 = 区间长度 - 1

$n^2$的做法很显然，这里就不说了。

网上有许多分治的做法，但是我并不会，这里也不说了。 QwQ

这里说一种线段树的做法。

要求的是一下区间的个数 : 

$\max_{l,r} - \min_{l,r} = r - l$

也就是求 :

$(\max_{l,r} - \min_{l,r}) - (r - l) = 0$

考虑在线段树上维护$(\max_{l,r} - \min_{l,r}) - (r - l)$这个值的最小值以及最小值的个数，那样我们查询只需要访问根的情况就可以了。

但是发现如果$l,r$都不确定的话这个值很难维护，所以我们选择对$r$作扫描线，每次求出以$r$结尾的合法区间的和，全部加起来就可以了。

发现这样子相比起来就容易多了。

具体如何操作呢?

首先，确定一下线段树节点上维护值的意义，设当前扫到了$r$, 当前线段树节点表示的区间为$[left, right]$，维护一个$min$，表示在当前$r$的情况下，对于所有的 $l \in [left, right]$，$(\max_{l,r} - \min_{l,r}) - (r - l)$的最小值以及最小值的个数 (如果$l > r$则暂时忽略)。发现这样可以很轻松的$update$与$pushdown$。

其次，在初始化的时候，显然表示区间$[left, right]$的最小值为$left$，最小值个数为$1$。

然后，考虑每次将$r$变为$r + 1$的时候如何修改，关于$r$的影响，只需要全局减$1$即可，对于$\max_{l,r}$和$\min_{l,r}$的影响，我们可以使用单调栈来维护(具体详见代码)。

最后，统计答案，显然。 QwQ

附上代码
```cpp
#include<cstdio>
#include<algorithm>

class SegmentTree{
private :
    typedef long long ll;
     
    struct Node{
        Node *child[2];
        int min, push;
        ll cnt; //cnt表示合法的值, val表示 max - min + l
 
        Node() :
            min(0), push(0), cnt(0) {
            child[0] = child[1] = NULL;
        }
    };
    Node *root;
    int n;
 
    void update(Node *now) {
        now->cnt = 0;
        now->min = std :: min(now->child[0]->min, now->child[1]->min);
        if (now->min == now->child[0]->min) {
            now->cnt += now->child[0]->cnt;
        }
        if (now->min == now->child[1]->min) {
            now->cnt += now->child[1]->cnt;
        }
 
        //now->val = now->child[0]->val + now->child[1]->val;
    }
 
    void pushDown(Node *now) {
        if (now->push) {
            for (register int i = 0; i < 2; i++) {
                now->child[i]->min += now->push;
                now->child[i]->push += now->push;
            }
            now->push = 0;
        }
    }
 
    void buildTree(Node *now, int left, int right) {
        now->min = left;
        now->cnt = 1;
        if (left == right) {
            return;
        }
        int mid = (left + right) >> 1;
        buildTree(now->child[0] = new Node(), left, mid);
        buildTree(now->child[1] = new Node(), mid + 1, right);
        update(now);
    }
     
    void addVal(Node *now, int left, int right, int l, int r, int val) {
        if (left >= l && right <= r) {
            now->push += val;
            now->min += val;
            return;
        }
        pushDown(now);
        int mid = (left + right) >> 1;
        if (r <= mid) {
            addVal(now->child[0], left, mid, l, r, val);
        } else if (l > mid) {
            addVal(now->child[1], mid + 1, right, l, r, val);
        } else {
            addVal(now->child[0], left, mid, l, r, val);
            addVal(now->child[1], mid + 1, right, l, r, val);
        }
        update(now);
    }
 
public :
    void init(int x) {
        buildTree(root = new Node(), 1, n = x);
    }
 
    void addVal(int l, int r, int val) {
        addVal(root, 1, n, l, r, val);
    }
 
    ll query() {
        return root->cnt;
    }
};

class Solution{
private :
    static const int maxn = 3e5 + 7;

    struct Node{
        int x, y;

        Node(int x = 0, int y = 0) :
            x(x), y(y) {}

        bool operator < (const Node &x) const {
            return this->x < x.x;
        }
    };

    int n, a[maxn], max[maxn], min[maxn], cntMax, cntMin;
    long long ans;
    Node p[maxn];
    SegmentTree tree;
    
public :
    Solution() {
        Get();
        Solve();
    }

    void Get() {
        scanf("%d", &n);
        for (register int i = 1; i <= n; i++) {
            scanf("%d %d", &p[i].x, &p[i].y);
        }
    }

    void Solve() {
        std::sort(p + 1, p + 1 + n);
        for (register int i = 1; i <= n; i++) {
            a[i] = p[i].y;
            //printf("%d ", a[i]);
        }
        //putchar('\n');
        //++n;//, a[n] = n;
        
        tree.init(n);
        /*
        for (register int i = 1; i <= n; i++) {
            printf("%d ", a[i]);
        }
        putchar('\n');
        */
        for (register int i = 1; i <= n; i++) {
            // do somthing
            tree.addVal(1, n, -1);
 
            for (; cntMax && a[i] > a[max[cntMax]]; cntMax--) {
                // do something
                tree.addVal(max[cntMax - 1] + 1, max[cntMax], a[i] - a[max[cntMax]]);
            }
            max[++cntMax] = i;
 
            for (;cntMin && a[i] < a[min[cntMin]]; cntMin--) {
                // do something
                tree.addVal(min[cntMin - 1] + 1, min[cntMin], a[min[cntMin]] - a[i]);
            }
            min[++cntMin] = i;
            ans += tree.query();
            //printf("%d : %lld\n", i, tree.query());
        }
        printf("%lld\n", ans);
    }
};
Solution sol;

int main() {}

```

---

## 作者：LawrenceSivan (赞：5)

暴力就是枚举长度，左上角，加上二维前缀和即可做到 $\mathcal{O(n^3)}$

$n$ 给到了 $5e4$ ，需要找出低于 $\mathcal{O(n^2)}$ 的做法。

一种套路是二维如果不好统计，那么可以使用映射的方法变成一维的。

同时可以获取双射。

首先考虑如何统计答案。

题目中有一个关键条件是每行每列最多只有一个。

于是可以找到一种方法：

对于每个矩形，如果存在矩形中最右边出现的点的位置减去最左边出现的点的位置等于最下边点的位置减去最上边点的位置，就说明成立。

并且可以发现，由于上面的那个特殊限制，导致每一个 $m\times m$ 的矩阵一定是每一行每一列都要有点出现，所以在值域上，也就是第一维映射上，他们是连续的。

正确性可以画图理解。

具体形式是这样的：

`if(maxn-minn==i-j)ans++;`

部分代码如下：

```cpp
for(re int i=1;i<=n;i++){
    int maxn=a[i],minn=a[i];
    ans++;
    for(re int j=i-1;j;j--){
        maxn=max(a[j],maxn);
        minn=min(a[j],minn);
        if(maxn-minn==i-j)ans++;
    }
}

```

于是发现每次查询找的位置都是区间上查询位置，但是我们熟知的区间数据结构似乎都不太能处理。

但是如果对应一个具体的值那就是好处理的。

可以直接移项。

`if((maxn-minn)-(j-i)==0)ans++;`

回头看我们上面完成的双射。

发现恰好一个是区间长度，另一个是值域上对应的极端位置的距离。

这个值是不会小于 $1$ 的。

原因：

考虑两个极端情况，分别如下图所示：

情况一：当横坐标相差很小，纵坐标相差很大时：

![](https://i.loli.net/2021/08/20/4kGLouCHbAxgpaq.png)

显然不小于0啊。

$(maxn-minn)$ 极大，$(j-i)$ 很小.

情况二：

 横坐标相差很大，但是纵坐标相差很小：

![](https://i.loli.net/2021/08/20/xFqz3oufSiIvdPG.png)

可以发现，虽然他们纵坐标相邻，但是由于横坐标差距过大，并且由于同行同列只有一个，所以中间的位置必定有比最下面这一行更靠右的纵坐标位置，于是这个情况不合法。

并且总能找到合法的差值大于等于 $0$ 的位置。

据以上可知，我们线段树中的值就都是大于等于 $0$ 的。

并且只有位置是 $0$ 的才会造成贡献。

于是，区间最小值！

到底怎么统计呢？一个区间里有多少呢？

多加一个 $cnt$ 同步维护不就好了吗？

于是线段树中就可以维护这个东西。

具体地，我们只要在线段树中找到某个值为 $0$ 的位置，那么就代表存在一个这样的合法矩形，就可以统计进答案。

实际操作中，我们依次考虑加入每个节点。现在我们对是否产生贡献是不确定的，所以考虑加上整体加一（上面说到过，我们通过最小值来判断是否是产生贡献，加一可以避免产生贡献，或者说是理解为假设他们值域不连续）

之后考虑由于要求值域连续，所以我们需要考虑当前节点纵坐标上一位和下一位，如果他们的横坐标已经在之前加入了，那么说明纵坐标就会连续。

那么他可能会贡献，所以区间减 $1$。 

最后就会发现，区间没有减一的部分，必定就是不连续的部分了。

可能存在一种情况，对于一段，上面是连续的，下面是连续的，但是中间没有减掉，导致上面合法，下面合法，中间不合法。

这个时候就能统计上上面的和下面的，而不会多统计中间的。

由于每一行都至少出现一个，所以多加的 $1$ 最后一定会减掉，并且由于上面的限制（不小于 $0$）所以不会减成负数。

为什么不会统计上面的部分呢?

由于我们一开始是 从 $1$ 到 $i-1$ 统一加 $1$ ，所以先加再减，只有一开始的时候第一次能统计才会统计他自己，后面统计的就是对于当前右端点的贡献了。

关于有的点有加有减，为什么不会重复统计贡献：

虽然有的点有加有减并且可能有的区间的 $cnt$ 不会改变。

但是对于整个要查询的大区间，可能发生最小值的变化，所以 $cnt$ 会有变化，

对于当前小区间的 $cnt$ 。由于我们之前统计他的时候查询的肯定是一个较小的区间，比如 $(1,2)$ 这种很小的。

但是对于大的，他不会作为一个小区间产生贡献了，他的 $cnt$ 一定要上传，经过合并以后作为大区间的某一部分一起贡献，所以小的不会重复算。

不重。

至于为什么都能统计上:

当他等于 $0$ 的时候，等价于它满足条件，并且连续（有多方面确定），在线段树上一定被统计到。

不漏。

至此，做法就是这样。

具体实现可以给值加个什么值让他不是 $0$，可能比较方便调试与判断。

---

## 作者：hzoi_liuchang (赞：5)

## 分析
用线段树即可解决

首先，我们发现，如果要满足 $k×k(1≤k≤N)$ 的子网格图包含恰好 $k$ 支军队

那么这 $k$ 只军队的最大横坐标减去最小横坐标恰好等于这 $k$ 只军队的最大纵坐标减最小纵坐标

两维不好处理，因此我们把横坐标作为下标，纵坐标作为权值

这样原问题就变成了在一个排列中有多少区间内的数是连续的

我们发现这可以用线段树去维护

我们把线段树的节点定义为以某个点为左端点，以扫到的点为右端点的区间中连续区间的个数

线段树要维护的信息有连续区间个数的最小值，该最小值的个数，以及区间加和操作中的 $lazy$ 标记

每次从右边新加入一个点 $i$ 时，我们把区间 $[1,i]$ 整体加 $1$

代表此时又多了一个不连续的区间

此时我们去找 $a[i]+1$ 和 $a[i]-1$ 的位置，如果它们的位置在 $i$ 的左边，我们就把 $[1,wz[a[i]-1]]$ 或者 $[1,wz[a[i]+1]]$ 整体减一，代表包含 $a[i]+1$ 或者 $a[i]-1$ 的区间可以与 $a[i]$ 合并形成一个大区间

每次枚举一个右端点时就单独计算一下价值

## 代码
``` cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
const int maxn=1e6+5;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int a[maxn],n,wz[maxn];
struct asd{
	int l,r,min,cnt,laz;
}tr[maxn<<1];
void push_up(int da){
	if(tr[da<<1].min==tr[da<<1|1].min){
		tr[da].min=tr[da<<1].min;
		tr[da].cnt=tr[da<<1].cnt+tr[da<<1|1].cnt;
	} else if(tr[da<<1].min<tr[da<<1|1].min){
		tr[da].min=tr[da<<1].min;
		tr[da].cnt=tr[da<<1].cnt;
	} else {
		tr[da].min=tr[da<<1|1].min;
		tr[da].cnt=tr[da<<1|1].cnt;
	}
}
void push_down(int da){
	if(tr[da].laz==0) return;
	tr[da<<1].min+=tr[da].laz;
	tr[da<<1|1].min+=tr[da].laz;
	tr[da<<1].laz+=tr[da].laz;
	tr[da<<1|1].laz+=tr[da].laz;
	tr[da].laz=0;
}
void build(int da,int l,int r){
	tr[da].l=l,tr[da].r=r;
	if(l==r){
		tr[da].min=1;
		tr[da].cnt=1;
		return;
	}
	int mids=(l+r)>>1;
	build(da<<1,l,mids);
	build(da<<1|1,mids+1,r);
	push_up(da);
}
int cx(int da,int l,int r){
	if(tr[da].l>=l && tr[da].r<=r){
		if(tr[da].min==1) return tr[da].cnt;
		return 0;
	}
	push_down(da);
	int mids=(tr[da].l+tr[da].r)>>1;
	int ans=0;
	if(l<=mids) ans+=cx(da<<1,l,r); 
	if(r>mids) ans+=cx(da<<1|1,l,r);
	return ans;
}
void xg(int da,int l,int r,int val){
	if(tr[da].l>=l && tr[da].r<=r){
		tr[da].min+=val;
		tr[da].laz+=val;
		return;
	}
	push_down(da);
	int mids=(tr[da].l+tr[da].r)>>1;
	if(l<=mids) xg(da<<1,l,r,val);
	if(r>mids) xg(da<<1|1,l,r,val);
	push_up(da);
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		int aa,bb;
		aa=read(),bb=read();
		a[aa]=bb;
		wz[a[aa]]=aa;
	}
	build(1,1,n);
	long long ans=0;	
	for(int i=1;i<=n;i++){
		if(i>1) xg(1,1,i-1,1);
		if(wz[a[i]-1]<=i && wz[a[i]-1]){
			xg(1,1,wz[a[i]-1],-1);
		}
		if(wz[a[i]+1]<=i && wz[a[i]+1]){
			xg(1,1,wz[a[i]+1],-1);
		}
		ans+=(long long)cx(1,1,i);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：potatoler (赞：4)

### [题目](https://www.luogu.com.cn/problem/CF526F)简述：

一个 $n \times n$ 的棋盘上面有 $n$ 个棋子，每行每列恰好有一个棋子，给定棋子的位置，求有多少个 $k \times k$ 的子棋盘上恰好有 $k$ 个棋子。$n ≤ 3 \times 10^{5}$。 

### 思路：

限制是解决题目的突破口，「每行每列恰好有一个棋子」就是这道题中很好的限制。由于这个限制的存在，我们可以构造一个数列 $|a_{n}|$，对于每一个点 $(x,y)$ 命 $a_{x}=y$。这样就将原题中二维空间的问题转化成了一维空间中的问题：「 $|a_{n}|$ 中有多少个区间中的数字是连续的」或者说「 $|a_{n}|$ 中有多少个区间，满足 $max-min = r-l$ 」。

记一个区间的中点为 $mid$，我们可以将一个区间的答案分成三部分：$mid$ 左边，$mid$ 右边，和跨越 $mid$。前两个是区间从中间劈开所产生的子问题，可以递归解决，我们着重考虑一下第三部分。

预处理两个数组 $mx[\ i\ ]$ 和 $mn[\ i\ ]$，分别表示 $mid$ 到 $i$ 这一个区间的最大值和最小值。对于刚才提到的第三部分，我们又可以将它分成两种情况：「最大值和最小值在 $mid$ 的同一侧」和「最大值和最小值在 $mid$ 的两侧」。

如果最大值和最小值在同一侧 (不妨设都在左侧) ，此时整个区间的最大值和最小值都是左侧的最大值和最小值。根据题意，合法的区间满足 $mx[i]-mn[i]=j-i$，移项可得 $j=i+mx[i]-mn[i]$。此时我们发现 $j$ 只与 $i$ 以及 $i$ 那一侧的最值有关，所以只需要枚举 $i$ 就可以确定可以和他构成合法区间的 $j$。当然最值都在右侧同理，我们可以得到 $i=j-mx[j]+mn[j]$。

```cpp
// If the max and min value are both on the left:
    for(int i = mid; i>=l; i--){
        int j = mx[i] - mn[i] + i;
        if(j <= r && j > mid && mx[i] > mx[j] && mn[i] < mn[j]) ans++;
    }
```

如果最大值和最小值在两侧 (不妨设最小值在左侧，最大值在右侧)，根据题意，合法的区间满足 $mx[j]-mn[i]=j-i$，移项得 $mn[i]-i=mx[j]-j$。问题变得棘手起来了：上面的分析的第一种情况，当 $i$ 确定时可以直接计算出一个 $j$ 是使等式成立，但是这里当 $i$ 确定时右边的 $j$ 还是不确定的，即每次扫描一个 $j$，$mx[j]$ 都会变。看上去只能暴力 $O(n^{2})$ 枚举左右端点，其实不然。因为对于一个固定的 $i$，若在某一时刻出现 $mn[j]<mn[i]$ 的情况 (不满足题意)，则无论 $j$ 再怎么扫描，对于扫描到的新点 $j'$ 一定有 $mn[j]’<mn[j]<mn[i]$，即之后的方案一定不合法。这样我们就没有继续枚举下去的必要了，只要在第一次出现不合法方案的时候及时跳出就可以了。对于固定的 $j$ 也是一样，若某一时刻出现 $mx[i]>mx[j]$，则之后的方案一定不合法。

具体该怎么实现呢？我们对于每一种符合题意时等式两边相等的那个值开一个桶，虽然那个值是 $|a_{n}|$ 数列上的位置加上 (或减去) 值，但是由于位置和值都是 $[1,n]$ 范围内的，所以桶的大小不会超过 $2n$。定义三个指针 $i,j,k$，其中 $i$ 是左边的位置，$j$ 和 $k$ 是右边的位置。若枚举到一个 $j$ 有$mn[j]>mn[i]$ (不满足 $mn[j]<mn[i]$ 的约束条件了)，就让 $bucket[mx[j]-j+n]++$，值得注意的是，这里加上 $n$ 是为了防止出现负的下标，由于所有减去的情况都加上了 $n$，所以在修改答案的时候是不会有影响的。$k$ 指针的作用是为了满足另一个约束条件 $mx[j]>mx[i]$。如果某一时刻有 $mx[k]<mx[i]$，那么即使这个位置的 $j$ 使得 $mn[j]<mn[i]$，也不是一个合法的方案。使用 $j$ 指针更新答案的时候我们并没有考虑另一个条件，所以现在我们要把只满足一个条件而不满足另一个条件的方案减掉，即让 $bucket[mx[k]-k+n]--$。

```cpp
// If the min value is on the left while the max value is on the right:
    // We should have "mn[i] - i == mx[j] - j" now.
    j = k = mid+1;
    for(i = mid; i>=l; i--){
        while(j <= r && mn[j] > mn[i]){
            bucket[mx[j]-j+n]++;
            j++;
        }
        // Why do we stop once mn[j] is not greater than mn[i]?
        // Because in this condition, mn[j] have been in the right part of segment, so the mn[j] will always less than mn[i].
        while(k < j && mx[k] < mx[i]){
            bucket[mx[k]-k+n]--;// By the way we'd better plus n to prevent mx[k]-k from being negative.
            k++;
        }
        ans += bucket[mn[i]-i+n];
    }
    // Clear bucket.
    while(k < j){
        bucket[mx[k]-k+n]--;
        k++;
    }
```

上面只分析了最小值在左侧最大值在右侧的情况，但是翻过来也是一样的。记得及时更新 $ans$ 并清空桶。

### Code：

```cpp
//AC?
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 300005;
int n, a[MaxN];
int mn[MaxN], mx[MaxN], bucket[MaxN*2], ans;

inline int Read(){
    int num = 0, op = 1;
    char ch = getchar();
    while(!isdigit(ch)){
        if(ch == '-') op = -1;
        ch = getchar();
    }
    while(isdigit(ch)){
        num = num * 10 + ch - '0';
        ch = getchar();
    }
    return num * op;
}

inline void Divide_and_Conquer(int l, int r){
    if(l == r) return (void)ans++;
    int mid = (l+r)/2;
    Divide_and_Conquer(l, mid);
    Divide_and_Conquer(mid+1, r);
    mx[mid] = mn[mid] = a[mid];
    mx[mid+1] = mn[mid+1] = a[mid+1];
    int i, j, k;
    // Initiate part: calcutale max and min value from middle to the two border.
    for(i = mid-1; i>=l; i--){
        mx[i] = max(mx[i+1], a[i]);
        mn[i] = min(mn[i+1], a[i]);
    }
    for(j = mid+2; j<=r; j++){
        mx[j] = max(mx[j-1], a[j]);
        mn[j] = min(mn[j-1], a[j]);
    }
    // If the max and min value are both on the left:
    for(i = mid; i>=l; i--){
        j = mx[i] - mn[i] + i;
        if(j <= r && j > mid && mx[i] > mx[j] && mn[i] < mn[j]) ans++;
    }
    // If the max and min value are both on the right:
    for(j = mid+1; j<=r; j++){
        i = j - mx[j] + mn[j];
        if(i <= mid && i >= l && mx[j] > mx[i] && mn[j] < mn[i]) ans++;
    }
    // If the min value is on the left while the max value is on the right:
    // We should have "mn[i] - i == mx[j] - j" now.
    j = k = mid+1;
    for(i = mid; i>=l; i--){
        while(j <= r && mn[j] > mn[i]){
            bucket[mx[j]-j+n]++;
            j++;
        }
        // Why do we stop once mn[j] is not greater than mn[i]?
        // Because in this condition, mn[j] have been in the right part of segment, so the mn[j] will always less than mn[i].
        while(k < j && mx[k] < mx[i]){
            bucket[mx[k]-k+n]--;// By the way we'd better plus n to prevent mx[k]-k from being negative.
            k++;
        }
        ans += bucket[mn[i]-i+n];
    }
    // Reset bucket, j and k.
    while(k < j){
        bucket[mx[k]-k+n]--;
        k++;
    }
    i = k = mid;
    // If the min value is on the right while the max value is on the left:
    // We should have "mx[i] - i == mn[j] - j" now.
    for(j = mid+1; j<=r; j++){
        while(i >= l && mn[i] > mn[j]){
            bucket[mx[i]+i]++;
            i--;
        }
        while(k > i && mx[k] < mx[j]){
            bucket[mx[k]+k]--;
            k--;
        }
        ans += bucket[mn[j]+j];
    }
    // Reset again.
    while(k > i){
        bucket[mx[k]+k]--;
        k--;
    }
}

signed main(){
    n = Read();
    for(int i=1; i<=n; i++){
        int u = Read(), v = Read();
        a[u] = v;
    }
    Divide_and_Conquer(1, n);
    printf("%lld\n", ans);
    return 0;
}
```



---

## 作者：FZzzz (赞：4)

好题。

首先把它拍扁到一个序列上应该不难想到，然后就是求满足 $\max[l,r]-\min[l,r]=r-l$ 的 $[l,r]$ 个数，其中 $\max[l,r]$ 表示区间中的最大值。

套路地枚举 $r$。

我们尝试维护 $\max[l,r]-\min[l,r]+l$，然后我们需要支持有多少个这个式子等于 $r$。

这个时候你可以秒出一个算法：用树状数组去维护差分，开两个单调栈，然后退栈就做一个区间修改……

然后就假掉了，因为退栈的时候有可能得遍历一遍另一个栈，复杂度直接被卡成平方带一个 log ~~比暴力还劣~~。

既然不能直接维护出现次数，我们不妨用线段树去维护在 $[1,r]$ 中有多少个 $l$ 满足 $\max[l,r]-\min[l,r]+l=r$，利用单调栈，我们需要的就是区间加和改变等式的右边……

然后就又不会了。

其实我们距离正解只有一步之遥。我们发现 $\max[l,r]-\min[l,r]\ge r-l$，所以我们维护 $\max[l,r]-\min[l,r]+l$ 的最小值及出现次数即可。

code：
```cpp
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-'){
        f=1;
        c=getchar();
    }
	while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return f?-x:x;
}
const int maxn=3e5+5;
int n,a[maxn];
struct node{
	int l,r;
	node* ch[2];
	int minv,cnt,addv;
	void pushup(){
		if(ch[0]->minv<ch[1]->minv){
			minv=ch[0]->minv;
			cnt=ch[0]->cnt;
		}
		else if(ch[0]->minv==ch[1]->minv){
			minv=ch[0]->minv;
			cnt=ch[0]->cnt+ch[1]->cnt;
		}
		else{
			minv=ch[1]->minv;
			cnt=ch[1]->cnt;
		}
	}
	node(int l,int r):l(l),r(r),minv(l),cnt(1),addv(0){
		if(l<r){
			int mid=l+(r-l)/2;
			ch[0]=new node(l,mid);
			ch[1]=new node(mid+1,r);
		}
		else ch[0]=ch[1]=0;
	}
	void pushtag(int k){
		addv+=k;
		minv+=k;
	}
	void pushdown(){
		ch[0]->pushtag(addv);
		ch[1]->pushtag(addv);
		addv=0;
	}
	void modify(int ql,int qr,int k){
		if(ql==l&&qr==r) pushtag(k);
		else{
			pushdown();
			if(qr<=ch[0]->r) ch[0]->modify(ql,qr,k);
			else if(ql>=ch[1]->l) ch[1]->modify(ql,qr,k);
			else{
				ch[0]->modify(ql,ch[0]->r,k);
				ch[1]->modify(ch[1]->l,qr,k);
			}
			pushup();
		}
	}
}*rt;
int s1[maxn],top1=0,s2[maxn],top2=0;
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    for(int i=0;i<n;i++){
    	int x=readint();
    	a[x]=readint();
	}
	rt=new node(1,n);
	long long ans=0;
	for(int i=1;i<=n;i++){
		while(top1&&a[s1[top1]]>a[i]){
			rt->modify(s1[top1-1]+1,s1[top1],a[s1[top1]]);
			top1--;
		}
		while(top2&&a[s2[top2]]<a[i]){
			rt->modify(s2[top2-1]+1,s2[top2],-a[s2[top2]]);
			top2--;
		}
		rt->modify(s1[top1]+1,i,-a[i]);
		rt->modify(s2[top2]+1,i,a[i]);
		if(rt->minv==i) ans+=rt->cnt;
		s1[++top1]=s2[++top2]=i;
	}
	printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：神眷之樱花 (赞：2)

# 更好阅读体验

[My Blog](https://blog.csdn.net/init1064573673/article/details/116997668)

# 问题描述
在一个 $n \times n$ 的矩阵中，求出满足有 $k$ 个棋子的 $k \times k$ 的正方形的个数。
# 题解
因为每行每列有且只有一个棋子，所以明显我们可以把二
维的图映射到一个序列上，将二维问题转化为一维问题。

行号对应每个棋子在序列上的位置，列号对应每个棋子在序列上的权值。

不难发现这 $n$ 个棋子就转化为了一个 $1$~$n$ 的排列。而我们要求的问题，就转化为了满足 $max - min = R - L$ 的区间 [L,R] 的个数为多少。

因为 $max,min$ 分别对应着列号的最大最小值，$R,L$ 分别对应着行号的最大最小值。满足上诉条件的区间就代表一个边长为 $R - L$（或者 $max - min$）的正方形里有 $R - L$（或者 $max - min$）个棋子。

注意我们要把二维矩阵中包含的所有正方形都统计完，而它们在序列上分别对应着区间 [1,1],[1,2]…[1,n]…[n,1],[n,2]…[n,n]。

尝试用线段树 + 扫描线维护。

将上述等式移项，记 $Min = max - min - R + L$，因为这是一个 $1$ ~ $n$ 的排列，根据鸽巢原理，显然有$max - min \geq R - L$，所以有： $Min\geq 0$，那么显然满足条件的序列的 $Min$ 值为 $0$，所以我们只用在线段树上维护 $Min$就好了，因为还要求个数，所以再维护值为 $Min$ 的个数。

当扫描到 $R$ 时，线段树上的单位节点 [l,r] 储存区间 [l,R],[l + 1,R]…[r,R] 对应的 $Min$ 的值，和值为 $Min$ 的区间的个数。

那么我们就得到了下述的基本框架，线段树的细节见代码：
* 当每次 $R+1$ 后，$Min$ 的值显然会减一，区间修改。
* 对于 $max,min$ 的维护，我们可以用两个单调栈。
* 每次单调栈的栈顶元素更新时，显然对于 $sta_{top - 1}$ ~ $sta_{top}$（还未更新）对应的序列的位置的 $Min$ 值都因为 $max$ 或 $min$ 的值的改变而受到了影响需要改变，再次进行区间修改。
* 每次维护结束后再区间查询一次累加入答案。

# 代码

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 3e5 + 5;

struct SegmentTree {
	#define M N << 2
	int l[M],r[M],Min[M],tag[M];
	long long cnt[M];
	void build(int p,int lf,int rg) {
		l[p] = lf,r[p] = rg;
		if(lf == rg) {
			Min[p] = lf; cnt[p] = 1;
			return;
		}
		int mid = (lf + rg) >> 1;
		build(p << 1,lf,mid);
		build(p << 1 | 1,mid + 1,rg);
		Min[p] = Min[p << 1];
	}
	inline void pushdown(int p) {
		if(!tag[p]) return;
		Min[p << 1] += tag[p];
		Min[p << 1 | 1] += tag[p];
		tag[p << 1] += tag[p];
		tag[p << 1 | 1] += tag[p];
		tag[p] = 0;
	}
	inline void pushup(int p) {
		Min[p] = min(Min[p << 1],Min[p << 1 | 1]); cnt[p] = 0;
		if(Min[p] == Min[p << 1]) cnt[p] +=	cnt[p << 1];
		if(Min[p] == Min[p << 1 | 1]) cnt[p] += cnt[p << 1 | 1];
	}
	void add(int p,int L,int R,int k) {
		if(L <= l[p] && r[p] <= R) {
			Min[p] += k; tag[p] += k;
			return;
		}
		pushdown(p);
		int mid = (l[p] + r[p]) >> 1;
		if(L <= mid) add(p << 1,L,R,k);
		if(R >  mid) add(p << 1 | 1,L,R,k);
		pushup(p);
	}
	long long query(int p,int L,int R) {
		if(L <= l[p] && r[p] <= R) return Min[p] == 0 ? cnt[p] : 0;
		int mid = (l[p] + r[p]) >> 1;
		long long ans = 0; pushdown(p);
		if(L <= mid) ans += query(p << 1,L,R);
		if(R >  mid) ans += query(p << 1 | 1,L,R);
		return ans;
	}
}tr;
struct data {
	int x,y;
	bool operator < (const data n) const {
		return x < n.x;		
	}
}a[N],sta1[N],sta2[N];
inline int read() {
	int x = 0,flag = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')flag = -1;ch = getchar();}
	while(ch >='0' && ch <='9'){x = (x << 3) + (x << 1) + ch - 48;ch = getchar();}
	return x * flag;
}
int main() {
	int n = read(); int top1 = 0,top2 = 0;
	for(int i = 1; i <= n; i++)
		a[i].x = read(),a[i].y = read();
	sort(a + 1,a + 1 + n); tr.build(1,1,n);
	long long ans = 0;
	for(int i = 1; i <= n; i++) {
		tr.add(1,1,n,-1);
		while(top1 && sta1[top1].y < a[i].y)
			tr.add(1,sta1[top1 - 1].x + 1,sta1[top1].x,a[i].y - sta1[top1].y),--top1;
		sta1[++top1] = (data) {i,a[i].y};
		while(top2 && sta2[top2].y > a[i].y)
			tr.add(1,sta2[top2 - 1].x + 1,sta2[top2].x,sta2[top2].y - a[i].y),--top2;
		sta2[++top2] = (data) {i,a[i].y};
		ans += tr.query(1,1,i);
	}
	printf("%lld",ans);
	return 0;
}
```




---

## 作者：zhengrunzhe (赞：2)

提供一个析合树的

不会的在oiwiki里学

连续段在树上表现为

$1.\text{析点代表的整个区间}$

$2.\text{合点的所有儿子构成的区间}$

$3.\text{叶子结点(可以视作析点)}$ 

直接统计答案 合点就是儿子对数(k*(k-1)/2) 析点+1
```cpp
#include<cstdio>
#include<vector>
using std::min;
using std::max;
using std::vector;
template<class type>inline const void read(type &in)
{
	in=0;char ch(getchar());
	while (ch<48||ch>57)ch=getchar();
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
}
typedef long long ll;
const int N(3e5+5),maxn(6e5+5),logn(18);
ll ans;
int n,a[N];
struct ST_Table
{
	int log2[N],pow2[logn+1],mx[N][logn+1],mn[N][logn+1];
	inline const void build()
	{
		for (int i(pow2[0]=1);i<=logn;i++)pow2[i]=pow2[i-1]<<1;
		for (int i(2);i<=n;i++)log2[i]=log2[i>>1]+1;
		for (int i(1);i<=n;i++)mn[i][0]=mx[i][0]=a[i];
		for (int j(1);j<=log2[n];j++)
			for (int i(1);i+pow2[j]-1<=n;i++)
				mn[i][j]=min(mn[i][j-1],mn[i+pow2[j-1]][j-1]),
				mx[i][j]=max(mx[i][j-1],mx[i+pow2[j-1]][j-1]);
	}
	inline const int query(const int &l,const int &r)
	{
		const int k(log2[r-l+1]);
		return max(mx[l][k],mx[r-pow2[k]+1][k])-min(mn[l][k],mn[r-pow2[k]+1][k]);
	}
}st;
namespace Segment_Tree
{
	struct tree
	{
		int mn,add;
		tree *lson,*rson;
		void *operator new(size_t size);
		inline tree():mn(0),add(0){}
		inline const void plus(const int &k)
		{
			add+=k;mn+=k;
		}
		inline const void pushdown()
		{
			if (add)
				lson->plus(add),
				rson->plus(add),
				add=0;
		}
		inline const void pushup()
		{
			mn=min(lson->mn,rson->mn);
		}
		inline const void update(const int &l,const int &r,const int &L,const int &R,const int &k)
		{
			if (l>R||r<L)return;
			if (l>=L&&r<=R)return plus(k);
			pushdown();
			const int mid(l+r>>1);
			lson->update(l,mid,L,R,k);
			rson->update(mid+1,r,L,R,k);
			pushup();
		}
		inline const int query(const int &l,const int &r)
		{
			if (l==r)return l;
			pushdown();
			const int mid(l+r>>1);
			if (!lson->mn)return lson->query(l,mid);
			return rson->query(mid+1,r);
		}
	}*root;
	char memory_pool[N*sizeof(tree)<<1],*tail(memory_pool+sizeof(memory_pool));
	inline void *tree::operator new(size_t size){return tail-=size;}
	inline const void build(tree *&p,const int &l,const int &r)
	{
		p=new tree;
		if (l==r)return;
		const int mid(l+r>>1);
		build(p->lson,l,mid);
		build(p->rson,mid+1,r);
	}
	inline const void build()
	{
		build(root,1,n);
	}
	inline const void update(const int &l,const int &r,const int &k)
	{
		root->update(1,n,l,r,k);
	}
	inline const int query()
	{
		return root->query(1,n);
	}
}
#define sgt Segment_Tree
typedef vector<int>Vector;
Vector son[maxn];
bool comb[maxn];
int l[maxn],r[maxn],m[maxn],id[maxn],s[N],s1[N],s2[N],top1,top2,top;
inline const bool judge(const int &l,const int &r)
{
	//printf(":::[%d,%d] %d\n",l,r,st.query(l,r));
	return st.query(l,r)==r-l;
}
inline const void insert(const int &k)
{
	for (;top1&&a[k]<=a[s1[top1]];top1--)sgt::update(s1[top1-1]+1,s1[top1],a[s1[top1]]);
	for (;top2&&a[k]>=a[s2[top2]];top2--)sgt::update(s2[top2-1]+1,s2[top2],-a[s2[top2]]);
	sgt::update(s1[top1]+1,k,-a[k]);s1[++top1]=k;
	sgt::update(s2[top2]+1,k,a[k]);s2[++top2]=k;
	id[k]=++*id;l[*id]=r[*id]=k;
	const int lm(sgt::query());int now(*id);
	while (top&&l[s[top]]>=lm)
	{
		if (comb[s[top]]&&judge(m[s[top]],k))
		{
			r[s[top]]=k;
			m[s[top]]=l[now];
			son[s[top]].push_back(now);
			now=s[(top)--];
			continue;
		}
		if (judge(l[s[top]],k))
		{
			comb[++*id]=1;
			r[*id]=k;l[*id]=l[s[top]];m[*id]=l[now];
			son[*id].push_back(s[(top)--]);
			son[*id].push_back(now);
			now=*id;
			continue;
		}
		static Vector tmp;tmp.clear();
		do tmp.push_back(s[(top)--]);while (top&&!judge(l[s[top]],k));
		l[++*id]=l[s[top]];r[*id]=k;
		son[*id].push_back(s[(top)--]);
		for (Vector::iterator i(tmp.begin());i!=tmp.end();i++)son[*id].push_back(*i);
		son[*id].push_back(now);
		now=*id;
	}
	s[++top]=now;
	sgt::update(1,k,-1);
}
inline const void build()
{
	st.build();
	sgt::build();
	for (int i(1);i<=n;i++)insert(i);
}
int main()
{
	read(n);
	for (int i(1),x,y;i<=n;i++)read(x),read(y),a[x]=y;
	build();
	for (int i(1);i<=*id;i++)
		if (comb[i])ans+=1ll*son[i].size()*(son[i].size()-1)/2;
		else ans++;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：JoaoFelix (赞：2)

对于这个问题我们首先把它转化为序列上的问题

就是一段区间内的从小到大排序以后这段区间的数是连续的

可以理解为最大值-最小值+1=区间长度

这里讲解一种不太常见的做法分治！

分治就是考虑所有左端点对于右端点的贡献。

那么这道题怎么分治呢？

我们刚开始觉得这道题不是特别能分治，因此我们仔细推一下这个min和max，可以大力分类讨论！

然后我们考虑对于每个分治区间[l,r]

我们考虑mid对答案造成的贡献，就是左端点在[l,mid]，右端点在[mid+1,r]的区间有多少个

分成四类：
```
1.最大值和最小值都在[l,mid]，但是由于区间长度的限制，所以必须右端点也要在[mid+1,r]
2.最大值和最小值都在[mid+1,r]，但是由于区间长度的限制，所以必须右端点也要在[l,mid]
3.最小值在[l,mid],最大值在[mid+1,r]
4.最小值在[mid+1,r],最大值在[l,mid]
```
然后我们发现可以先1,3然后再2,4，也就是1,3和2,4是等价的!

我们只需要写一个solve函数，然后把序列一个放左边一个放右边，反之反过来就可以了！
那么我们以1,3为例子分析一下：
看一下这个solve的代码！
```cpp
void solve(int *a,int *b){
	int la=a[0],lb=b[0],nowmi,nowma;
	mi[0]=nowmi=n+1;ma[0]=nowma=0;
	for(int i=1;i<=lb;i++)mi[i]=min(mi[i-1],b[i]),ma[i]=max(ma[i-1],b[i]);
	for(int i=1,nl=1,nr=1,len;i<=la;i++){
		nowmi=min(nowmi,a[i]);nowma=max(nowma,a[i]);len=nowma-nowmi+1;
		if(len>i&&len-i<=lb&&mi[len-i]>nowmi&&ma[len-i]<nowma)ans++;
		while(nr<=lb&&mi[nr]>nowmi)cnt[ma[nr]-nr+1]++,nr++;
		while(nl<nr&&ma[nl]<nowma)cnt[ma[nl]-nl+1]--,nl++;
		//Lma-nowmi+1==Lpos+i->Lma-Lpos+1==i+nowmi
		ans+=(LL)cnt[i+nowmi];
	}
	for(int i=1;i<=lb;i++)cnt[ma[i]-i+1]=0;
}
```
如果是第1类情况，那么我们需要根据序列的长度是nowma-nowmi+1既为len,由于分治我们考虑的是左右端点分别在mid的两侧，那么我们需要判断它的另一个端点是否在另一边，并且不能越界（超出另一边的范围），并且另一边的最大值不得超过当前的最大值，最小值也不得超过当前的最小值，然后如果满足条件我们找到了一个满足条件的，ans++！

然后我们考虑第3类情况，我们用一个类似于two-pointers的东西扫一下另外的那一部分，扫的区间满足我们的最小值不得小于当前的最小值，因为我们钦定最小值来自于当前的这个部分，最大值同理，必须要大于当前的最大值，也是我们钦定的！
然后我们扫出了这个区间的范围，需要满足一个式子就是：
```
Lma-nowmi+1==Lpos+i->Lma-Lpos+1==i+nowmi
```
Lma代表左边的最大值，Lpos是左边的位置

然后等号左边等于最大值-最小值+1，然后右边是Lpos+i就是区间长度，相当于两端区间拼起来这么理解！

然后我们移项就发现我们满足这样一个等式，右边只和i有关，左边只和另一个部分有关，我们这个东西可以一边扫一遍用一个cnt数组记录一下，注意最好要清空。

接着我们考虑完这种情况后，我们分治的时候调用两次这个solve函数就可以，相当于是1,3一起讨论了，2,4一起讨论了！

最后分治的时候如果左端点等于右端点ans++，因为这个我们单独考虑。


代码：
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=3e5+5;
int n,p[N],sl[N],sr[N],cnt[N],mi[N],ma[N];LL ans;
void solve(int *a,int *b){
	int la=a[0],lb=b[0],nowmi,nowma;
	mi[0]=nowmi=n+1;ma[0]=nowma=0;
	for(int i=1;i<=lb;i++)mi[i]=min(mi[i-1],b[i]),ma[i]=max(ma[i-1],b[i]);
	for(int i=1,nl=1,nr=1,len;i<=la;i++){
		nowmi=min(nowmi,a[i]);nowma=max(nowma,a[i]);len=nowma-nowmi+1;
		if(len>i&&len-i<=lb&&mi[len-i]>nowmi&&ma[len-i]<nowma)ans++;
		while(nr<=lb&&mi[nr]>nowmi)cnt[ma[nr]-nr+1]++,nr++;
		while(nl<nr&&ma[nl]<nowma)cnt[ma[nl]-nl+1]--,nl++;
		//Lma-nowmi+1==Lpos+i->Lma-Lpos+1==i+nowmi
		ans+=(LL)cnt[i+nowmi];
	}
	for(int i=1;i<=lb;i++)cnt[ma[i]-i+1]=0;
}
void cdq(int l,int r){
	if(l==r){ans++;return;}
	int mid=(l+r)>>1;sl[0]=sr[0]=0;
	for(int i=mid;i>=l;i--)sl[++sl[0]]=p[i];
	for(int i=mid+1;i<=r;i++)sr[++sr[0]]=p[i];
	solve(sl,sr);solve(sr,sl);
	cdq(l,mid);cdq(mid+1,r);
}
int main(){
	scanf("%d",&n);
	for(int i=1,x,y;i<=n;i++)scanf("%d%d",&x,&y),p[x]=y;
	cdq(1,n);
	printf("%lld\n",ans); 
	return 0;
}

```



---

## 作者：Kinandra (赞：2)

标签: 转化, 线段树

#### Part 1

显然 $k\times k$ 的棋盘也是每行每列恰好一个棋子, 我们记第 $i$ 行的棋子所在列为 $a_i$ .

那么对于行 $[l,r]$ 的棋子能对答案有贡献当且仅当 $max\{a_i|i\in[l,r]\}-min\{a_i|i\in[l,r]\}=r-l$ .

我们要求的就是满足条件的 $[l,r]$ 区间. 这个有一个很经典的做法.

#### Part 2

枚举 $r$ , 对于每个位置 $l\leqslant r$ 都用线段树维护 $f_l=max\{a_i|i\in[l,r]\}-min\{a_i|i\in[l,r]\}+l$ .

显然 $f_l\geqslant r$ , 那么我们用线段树维护区间 $f$ 的最小值和最小值出现的次数即可求得满足条件的 $l$ .

时间复杂度 $\mathcal O(n\log n)$ .

```cpp
#include <bits/stdc++.h>
using namespace std;
int read();
int n;
int a[300005];
#define ls l, mid, k << 1
#define rs mid + 1, r, k << 1 | 1
#define L k << 1
#define R k << 1 | 1
struct Seg {
    int mn[2000006], tag[2000006], c[2000006];
    void update(int k) {
        mn[k] = min(mn[L], mn[R]);
        c[k] = (mn[k] != mn[L] ? 0 : c[L]) + (mn[k] != mn[R] ? 0 : c[R]);
    }
    void build(int l, int r, int k) {
        if (l == r) return mn[k] = l, c[k] = 1, void();
        int mid = l + r >> 1;
        build(ls), build(rs), update(k);
    }
    void Tag(int k, int v) { tag[k] += v, mn[k] += v; }
    void psd(int k) { Tag(L, tag[k]), Tag(R, tag[k]), tag[k] = 0; }
    void add(int l, int r, int k, int st, int en, int v) {
        if (st > r || en < l) return;
        if (st <= l && en >= r) return Tag(k, v);
        psd(k);
        int mid = l + r >> 1;
        add(ls, st, en, v), add(rs, st, en, v), update(k);
    }
} seg;

int st[2][300005], top[2];

int main() {
    n = read();
    for (int i = 1, x; i <= n; ++i) x = read(), a[x] = read();
    long long res = 0;
    seg.build(1, n, 1);
    for (int i = 1, p; i <= n; ++i) {
        p = i;
        while (top[0] && a[i] < a[st[0][top[0]]])
            seg.add(1, n, 1, st[0][top[0] - 1] + 1, p - 1,
                    a[st[0][top[0]]] - a[i]),
                p = st[0][top[0]--];
        p = i;
        while (top[1] && a[i] > a[st[1][top[1]]])
            seg.add(1, n, 1, st[1][top[1] - 1] + 1, p - 1,
                    a[i] - a[st[1][top[1]]]),
                p = st[1][top[1]--];
        st[0][++top[0]] = st[1][++top[1]] = i, res += seg.c[1];
    }
    printf("%lld\n", res);
    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
int read() {
    int x = 0, f = 1;
    char c = gc;
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x * f;
}
```

---

## 作者：1saunoya (赞：1)

真是惭愧…

做不出自己以前会做的题…

我们考虑两个个单调栈扫过去，扫描右端点，这样就能知道以这个端点所在的在某个区间的最小值是多少，最大值是多少，然后就可以找到一个合法区间，数一下一棵线段树有多少个 [-1] 就行了。。

这份代码是在 2019.10 写的（

```cpp
// Isaunoya
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize(Ofast)
#include<bits/stdc++.h>
using namespace std ;
#define int long long
#define fi first
#define se second
#define pb push_back
inline int read() {
  register int x = 0 , f = 1 ;
  register char c = getchar() ;
  for( ; ! isdigit(c) ; c = getchar()) if(c == '-') f = -1 ;
  for( ; isdigit(c) ; c = getchar()) x = (x << 1) + (x << 3) + (c & 15) ;
  return x * f ;
}
template < class T > inline bool cmax(T & x , T y) {
  return x > y ? 1 : x = y , 0 ;
}
template < class T > inline bool cmin(T & x , T y) {
  return x < y ? 1 : x = y , 0 ;
}
const int MAXN = 3e5 + 10 ;
const int mod7 = 1e9 + 7 ;
const int mod9 = 1e9 + 9 ;
const int mod = 998244353 ;
inline int QP(int x , int y , int Mod){ int ans = 1 ;
  for( ; y ; y >>= 1 , x = (x * x) % Mod)
    if(y & 1) ans = (ans * x) % Mod ;
  return ans ;
}
int n , m ;
vector < int > v ;
int a[MAXN] ;
inline void io() {
  ios :: sync_with_stdio(false) ;
  cin.tie(0) , cout.tie(0) ;
}

int mn[MAXN << 2] ;
int len[MAXN << 2] ;
int tag[MAXN << 2] ;
inline void Push_Up(int rt) {
  mn[rt] = min(mn[rt << 1] , mn[rt << 1 | 1]) ;
  if(mn[rt << 1] == mn[rt << 1 | 1]) len[rt] = len[rt << 1] + len[rt << 1 | 1] ;
  else {
    if(mn[rt] == mn[rt << 1]) len[rt] = len[rt << 1] ;
    else len[rt] = len[rt << 1 | 1] ;
  }
}
inline void build(int l , int r , int rt) {
  mn[rt] = 0 ; len[rt] = r - l + 1 ;
  if(l == r) return ;
  int mid = l + r >> 1 ;
  build(l , mid , rt << 1) ;
  build(mid + 1 , r , rt << 1 | 1) ;
}
inline void Push_down(int rt) {
  if(! tag[rt]) return ;
  tag[rt << 1] += tag[rt] ;
  tag[rt << 1 | 1] += tag[rt] ;
  mn[rt << 1] += tag[rt] ;
  mn[rt << 1 | 1] += tag[rt] ;
  tag[rt] = 0 ;
}
inline void Upd(int a , int b , int l , int r , int rt , int val) {
  if(a <= l && r <= b) {
    mn[rt] += val ;
    tag[rt] += val ;
    return ;
  } Push_down(rt) ;
  int mid = l + r >> 1 ;
  if(a <= mid) Upd(a , b , l , mid , rt << 1 , val );
  if(b > mid) Upd(a , b , mid + 1 , r , rt << 1 | 1 , val) ;
  Push_Up(rt) ;
}
typedef pair < int , int > pii ;
#define mp make_pair
inline pii Query(int a , int b ,int l , int r , int rt) {
  if(a <= l && r <= b) {
    return mp(mn[rt] , len[rt]) ;
  } Push_down(rt) ;
  int mid = l + r >> 1 ;
  pii ans1 = mp(INT_MAX , 0) ;
  pii ans2 = mp(INT_MAX , 0) ;
  if(a <= mid) ans1 = Query(a , b , l , mid , rt << 1) ;
  if(b > mid) ans2 = Query(a , b , mid + 1  , r , rt << 1 | 1) ;
  pii ans ;
  if(ans1.fi == ans2.fi) {
    ans = mp(ans1.fi , ans1.se + ans2.se) ;
    return ans ;
  }
  if(ans1.fi < ans2.fi) { ans = ans1 ; return ans ; }
  else { ans = ans2 ; return ans ; }
  return ans ;
}
pii mxs[MAXN] , mns[MAXN] ;
map < int , int > _mp ;
signed main() {
  // io() ;
  n = read() ;
  for(register int i = 1 ; i <= n ; i ++) {
  	int x = read();
  	a[x]=read();
	}
  int ans = 0 ;
  _mp.clear() ;
  build(1 , n , 1) ;
  int maxs = 0 , mins = 0 ;
  for(register int i = 1 ; i <= n ; i ++) {
    while(maxs > 0 && mxs[maxs].fi < a[i]) {
      Upd(mxs[maxs - 1].se + 1 , mxs[maxs].se , 1 , n , 1 , a[i] - mxs[maxs].fi) ;
      maxs -- ;
    }
    mxs[++ maxs] = mp(a[i] , i) ;
    while(mins > 0 && mns[mins].fi > a[i]) {
      Upd(mns[mins - 1].se + 1 , mns[mins].se , 1 , n , 1 , mns[mins].fi - a[i]) ;
      mins -- ;
    }
    mns[++ mins] = mp(a[i] , i) ;
    Upd(_mp[a[i]] + 1 , i , 1 , n , 1 , - 1) ;
    _mp[a[i]] = i ;
    pii flg = Query(1 , i , 1 , n , 1) ;
    if(flg.fi == -1) ans += flg.se ;
  }
  printf("%lld\n" , ans) ;
  return 0 ;
}
```

---

