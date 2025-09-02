# [USACO10MAR] Barn Allocation G

## 题目描述

Farmer John recently opened up a new barn and is now accepting stall allocation requests from the cows since some of the stalls have a better view of the pastures.

The barn comprises N (1 <= N <= 100,000) stalls conveniently numbered 1..N; stall i has capacity C\_i cows (1 <= C\_i <= 100,000). Cow i may request a contiguous interval of stalls (A\_i, B\_i) in which to roam (1 <= A\_i <= N; A\_i <= B\_i <= N), i.e., the cow would like to wander among all the stalls in the range A\_i..B\_i (and the stalls must always have the capacity for her to wander).

Given M (1 <= M <= 100,000) stall requests, determine the maximum number of them that can be satisfied without exceeding stall

capacities.

 
农夫约翰最近开了一个新的牲口棚屋，并且现在接受来自奶牛的分配畜栏请求因为其中的一些畜栏有更好风景。

畜栏包括N个畜栏(1 ≤ N ≤ 100,000)，方便起见，我们把它们编号为1..N，畜栏i能容纳Ci只牛(1 ≤ Ci ≤ 100,000)，第i只牛需要连续编号畜栏（从Ai到Bi）来漫步其中，

(1 ≤ Ai ≤ N; Ai ≤ Bi ≤ N)，换言之，这只牛想要在编号范围为Ai..Bi的畜栏漫步（所有它想要畜栏必须实施为它空出位置来供它散步）

给出M个畜栏分配请求（1 ≤ M ≤ 100,000），回答最多能满足多少只牛的要求（不增加另外畜栏）

考虑以下例子：

```cpp
畜栏号:    1   2   3   4   5
           +---+---+---+---+---+
容纳空间:  | 1 | 3 | 2 | 1 | 3 |  
           +---+---+---+---+---+
Cow 1       XXXXXXXXXXX             (1, 3)
Cow 2           XXXXXXXXXXXXXXX     (2, 5)
Cow 3           XXXXXXX             (2, 3)
Cow 4                   XXXXXXX     (4, 5)
```
约翰显然不能满足所有的牛，因为畜栏3，4请求太多了

经过试验，我们发现，我们能满足牛1，3，4需要，所以这组数据答案为3


## 说明/提示

Source: USACO 2010 March Gold

Translator: @chrome01


## 样例 #1

### 输入

```
5 4
1
3
2
1
3
1 3
2 5
2 3
4 5```

### 输出

```
3```

# 题解

## 作者：Fading (赞：25)

相信大家都**猜**得到解法：

将奶牛的路径转化为线段，以右端点为第一关键字，左端点为第二关键字，按第一关键字从小到大排序，若第一关键字相同则按第二关键字从大到小排序。

然后按序枚举线段，看看是否可以放（区间最小值$>0$），如果可以，则区间内所有的数$-1$，答案$+1$，用线段树维护区间最小值。

这为什么是对的呢？



------------

第一个结论证明比较显然，左端点从大到小取最优(假设右端点全都是$r$)。

（因为从小到大取所占用的空间和一定$\geq$从大到小取所占用的空间和，而且从小到大取占用的区间$\in$从大到小取占用的区间）

然后我们证明第二个结论，右端点从小到大取最优。

可以用归纳法。

第一条线段一定要加入。

假设已经到了第$i$条线段，端点为$l_i,r_i$

如果没有冲突，直接算入答案。这样根据归纳假设是最优的。

但如果冲突了，设和第$j$条线段冲突（当然j不唯一）

如果$j$的右端点等于$i$的右端点，可以直接不选$i$（刚才的结论）

否则

```
 -------------             j
    ------------------     i

```

发现如果不选$j$，选择$i$，就会让$[l_i,r_i]$区间全部$-1$，$[l_j,r_j]$全部$+1$

但是发生冲突的区间是$[l_i,r_j]$，之后这段区间最小值依旧为$0$。

显然如果剩下的区间左端点$\leq l_i$，一定不满足条件，这和$[l_j,l_i-1]$的区间$+1$失去了效果。

所以这样对后续的影响可以看成$[r_j+1,r_i]$全部$-1$。

但如果不选$i$呢？

就毫无影响。

所以如果选择$i$，就白白浪费了区间$[r_j+1,r_i]$。

所以我们不选，一定更优。

因此得证。

### 综上，我们证明了贪心的正确性。

---

## 作者：__JR_飘摇__ (赞：19)

看到大家都用线段树，这里写一个优先队列的做法~

首先我们对所有牛以$a_{i}$第一关键字排序，然后再贪心处理怎样才能使答案达到最优。

具体怎么贪呢？

我们从$1->n$扫一遍，假设我们扫到$i$，在这一个空间上已经容纳了$j$头牛，我们把所有$a_{k}=i$的牛先扔进这一个空间，我们假设这个空间可以无限大，那么我们的队列里就存了可能超出空间的牛。

接着我们在考虑容量问题，这个时候我们队列里已经有$r$头牛了，如果$r\leq c_{i}$那么我们可以很和谐的往后跑，如果不是，那我们就要考虑把一部分牛宰掉$qaq$。

##### 注意到我们枚举到$i$点时，队列里的每一头牛都有一个$b_{i}$，表示$b_{i}$之后这头牛就不占空间了，而它们的$a_{i}$已经对答案没有影响了，我们只希望后面对答案的贡献尽可能大，即后面的空间尽可能大，因此如果超出了空间，我们肯定要宰掉队列中$b_{i}$较后的牛。

既然如此，我们的贪心思路已经很明确了，具体分为三步：

1. 我们从$1->n$扫一遍，对于每个$i$，我们把所有$a_{i}$进入队列，从这里开始占用空间。

2. 然后我们开始考虑队列容量不够的问题，我们如果我们超出了容量，我们把所有$b_{i}$大的宰掉

3. 接着释放空间，我们把队列中所有$b_{i}=i$，即不占用空间了的请下去，统计答案。

显然，第二个步骤可以用大根堆实现。

那么第三个步骤呢？我们发现大根堆没法获取最小值。

##### 那么我们就让他放在队列中，我们开一个数组$sum_{i}$表示队列中有多少头牛满足$b_{k}=i$，显然是可以做到同步的，然后统计答案的时候我们就可以知道有多少头牛的空间是已经被释放了的。

具体代码实现很简单：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s[110000],t,sum[110000],ans = 0;
pair <int,int> a[110000];
priority_queue<int> q;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;i ++) scanf("%d", &s[i]);
	for(int i = 1;i <= m;i ++) scanf("%d%d", &a[i].first, &a[i].second);
	sort(a + 1,a + m + 1);
	a[m + 1].first = n + 1;//这一步是为了防止死循环 
	for(int i = 1;i <= n;i ++)
	{
		//分三步： 
		while(a[t + 1].first <= i) q.push(a[++ t].second),sum[a[t].second] ++;//进队 
		while(q.size() > s[i] + ans) sum[q.top()] --,q.pop();//宰牛 
		ans += sum[i];//统计答案，这一个答案也代表队列中有多少头牛是已经被释放了的 
	} 
	printf("%d\n", ans);
 } 
```

---

## 作者：Sincerin (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/P1937)

[更好的阅读体验](https://www.luogu.com.cn/blog/sincerin520/solution-P1937)

顺带一提，这题和[SP8462](https://www.luogu.com.cn/problem/SP8462)重题了。

## 题目描述

一共有 $N$ 个畜栏和 $M$ 头牛，第 $i$ 个畜栏可以住 $C_i$ 头牛。每头牛都需要占用一段连续的畜栏 $A_i$ 到 $B_i$   来休息。问这 $N$ 个畜栏最多可以满足几头牛？

- $1 \leq N,M \leq 10^5.$
- $1 \leq A_i \leq B_i \leq N.$
- $1 \leq C_i \leq 10^5.$

## 题目解析

首先题目要求找出最多方案，显然需要贪心。那么关于贪心的方案，由于其右端点越靠左，对后面的影响越小，所以我们可以按其右端点 $B_i$ 从小到大进行排序，**并且没有必要以左端点为第二关键字进行排序**。


```cpp

             1   2   3   4   5
           +---+---+---+---+---+
           | 1 | 1 | 1 | 2 | 3 |  
           +---+---+---+---+---+           			 
Cow 1       XXXXXXX              (1, 2)
Cow 2               XXXXXXX      (3, 4)
Cow 3           XXXXXXXXXXXXXXXX (2, 5)

```

如图，我们把每头牛所需要的区间看做一条条线段。在排序过后，右端点是递增的，我们依次插入每段区间，前两头牛是完全可以住下的。但是在插入第三头牛的时候，会发现它和前两头都存在冲突。它的贡献只有 $1$，所以放弃它保留原来的两头才是更优的策略。

如果是只有一头原先存在的牛和它存在冲突，以上策略仍然成立。因为它一定比原先存在的那头牛右端点更靠右，对后面的牛影响也会更大，故放弃它也是更优策略。

回到排序策略，当有两头牛的右端点**相同**时，大部分题解都采用了左端点为第二关键字从大到小排序。这个思路很好理解，因为左端点更大的线段占的空间更小，对前面影响更小，这样排序一定是最优的。

在这样的情况下，先插入更短的（左端点更大的）线段，它将不会对前面造成影响，所以下一条更长的线段不会被它影响。但是反之，如果先插入较长线段，下一条较短线段在插入时也并不会受到影响，因为它根本就用不到前面被长线段占用的部分，所以没有必要考虑第二关键字。



考虑完贪心策略，我们来想一想代码的实现。对于每次请求 $A_i$ 和 $B_i$ 肯定不可能去遍历它，把区间所有数都加上 $1$，然后再判断有没有超出 $C_i (i \in [A_i,B_i])$。这样的纯暴力做法会让整体时间复杂度来到 $\Theta (nm)$，显然是过不掉这个题的，并且我也没有想到这个思想可以怎么优化 QwQ。

既然这样，我们考虑来把这个过程转换成减法，每次操作把对应的 $C_i (i \in [A_i,B_i])$ 都减去 $1$，表示每个畜栏还能住的牛的头数。这样在判断是否可以满足请求区间的时候，只需要确保区间的最小值 $\min \{C_{A_i} \dots C_{B_i} \} \geq 1$ 即可。区间修改 $+$ 区间最小值查询，很明显可以用一棵[线段树](https://www.cnblogs.com/xenny/p/9801703.html)来维护区间最小值。

- 线段树的单次区间修改会达到 $\Theta (n)$，和暴力没有什么差距。所以需要引入**延迟标记**来实现 $\Theta (\log n)$ 的区间修改。如果你对延迟标记并不熟悉，可以[戳这里](https://blog.csdn.net/qq_20468287/article/details/54584937)，然后做做下面两道练习。


   ##### [P3373 线段树2](https://www.luogu.com.cn/problem/P3373)
   ##### [P1253 扶苏的问题](https://www.luogu.com.cn/problem/P1253)
  
  ~~都来做这个题了，怎么可能不会线段树啊/kk~~


- 本题坑点：每个畜栏最多 $10^5$ 只，共 $10^5$ 个畜栏，要开`long long`。

## AC Code

总体时间复杂度 $\Theta (m \log n)$。


```cpp
#include<iostream>
#include<cstdio> 
#include<algorithm> 
#include<cstring> 
#include<cmath> 
using namespace std;  
const int N=100005;//1e5个畜栏 
#define int long long //防止见祖宗。  
const int INF=0x3f3f3f3f3f3f3f3f;//一定要记得long long是8个字节 
int m,n,ans;
int a[N];//每个畜栏的容量   
struct node{
	int l,r;//记录每头牛活动区间的结构体 
}e[N]; 
inline bool cmp(node a,node b)//按右端点从小到大排序 
{
	return a.r<b.r;
}
#define lson(p) p<<1
#define rson(p) p<<1|1
struct SegmentTree{//线段树的结构体 
    int l,r;
    int dat;
    int add;
    #define l(i) t[i].l
    #define r(i) t[i].r 
    #define dat(i) t[i].dat //最小值 
    #define add(i) t[i].add
}t[N<<2];
inline void pushup(int p)//更新节点信息 
{
	dat(p)=min(dat(lson(p)),dat(rson(p)));
}
inline void build(int p,int l,int r)//建树 
{
    l(p)=l;  r(p)=r;
    if(l==r) //找到节点 
    {
        dat(p)=a[l];//赋值 
        return;
    }
    int mid=(l+r)>>1;
    build(lson(p),l,mid); 
	build(rson(p),mid+1,r);
    pushup(p);//向上传递 
}
inline void spread(int p)//下传 lazy_tag 
{
    if(add(p)) 
    {
        dat(lson(p))+=add(p); dat(rson(p))+=add(p);
        add(lson(p))+=add(p); add(rson(p))+=add(p);
        add(p)=0;//最后别忘了清标记！ 
	}   
} 
inline void change(int p,int l,int r)//区间减1 
{
    if(l<=l(p)&&r>=r(p))
    {
        add(p)--; dat(p)--; //打标记 
        return;
    }
    spread(p);//下传 
    int mid=(l(p)+r(p))>>1;
    if(l<=mid) change(lson(p),l,r);
    if(r>mid) change(rson(p),l,r);
    pushup(p);//更新信息 
} 
inline int query(int p,int l,int r)//查询最小值 
{
    if(l<=l(p)&&r>=r(p)) return dat(p);
    spread(p);
    int mid=(l(p)+r(p))>>1; 
    int ans=INF;//初始化ans为一个极大值 
    if(l<=mid) ans=query(lson(p),l,r);
    if(r>mid) ans=min(ans,query(rson(p),l,r));//左右子树的较小值 
    return ans;
}
signed main(void)
{ 
	freopen("P1937.in","r",stdin);
    scanf("%lld%lld",&n,&m); 
    for(register int i=1;i<=n;++i) scanf("%lld",&a[i]);
	for(register int i=1;i<=m;++i) scanf("%lld%lld",&e[i].l,&e[i].r); //牛爷爷们的要求 
    sort(e+1,e+1+m,cmp);//排序  
    build(1,1,n); ans=0;
	for(register int i=1;i<=m;++i)
	{
		if(query(1,e[i].l,e[i].r)>=1) //如果区间最小值>=1,则还可以再分出一个畜栏 
		{
			change(1,e[i].l,e[i].r);//把该区间的数都减1
			ans++;//统计答案 
		}
	}
	printf("%lld\n",ans); 
    return 0;//完结撒花！
} 
/*
5 3
1 1 1 2 3
1 2
2 5
3 4
*/
```

[AC Record（最优解第一页哦）](https://www.luogu.com.cn/record/100240440)

不要在意我奇怪的码风。


---

## 作者：Created_equal1 (赞：7)

按照B的大小排序（若B相同按A排），然后贪心，能放就放。这个用线段树来维护~

```cpp

#include <cstdio>  
#include <algorithm>  
  
using namespace std;  
  
const size_t Max_N(100050);  
const size_t Max_M(100050);  
  
void Get_Val(int &Ret)  
{  
    Ret = 0;  
    char ch;  
    while ((ch = getchar()), (ch > '9' || ch < '0'))  
        ;  
    do  
    {  
        (Ret *= 10) += ch - '0';  
    }  
    while ((ch = getchar()), (ch >= '0' && ch <= '9'));  
}  
  
struct node  
{  
    int l, r;  
    int Min;  
    int Tag;  
};  
  
struct Segment_Tree  
{  
    node segt[Max_N << 2];  
    void build_tree(const int&, const int&, const int&);  
    void pushdown(const int&);  
    void pushup(const int&);  
    void Add(const int&, const int&, const int&, const int&);  
    int rmq_min(const int&, const int&, const int&);  
};  
Segment_Tree Space;  
  
void Segment_Tree::build_tree(const int &cur, const int &l, const int &r)  
{  
    segt[cur].l = l, segt[cur].r = r, segt[cur].Min = 0;  
    if (l == r)  
        return;  
    int mid = l + ((r - l) >> 1);  
    build_tree(cur << 1, l, mid);  
    build_tree((cur << 1) | 1, mid + 1, r);  
}  
  
inline  
void Segment_Tree::pushdown(const int &cur)  
{  
    if (segt[cur].Tag == 0)  
        return;  
    segt[cur << 1].Min += segt[cur].Tag, segt[(cur << 1) | 1].Min += segt[cur].Tag;  
    segt[cur << 1].Tag += segt[cur].Tag, segt[(cur << 1) | 1].Tag += segt[cur].Tag;  
    segt[cur].Tag = 0;  
}  
  
inline  
void Segment_Tree::pushup(const int &cur)  
{  
    segt[cur].Min = min(segt[cur << 1].Min, segt[(cur << 1) | 1].Min);  
}  
  
void Segment_Tree::Add(const int &cur, const int &l, const int &r, const int &x)  
{  
    if (l <= segt[cur].l && r >= segt[cur].r)  
    {  
        segt[cur].Min += x;  
        segt[cur].Tag += x;  
        return;  
    }  
    int mid = segt[cur].l + ((segt[cur].r - segt[cur].l) >> 1);  
    pushdown(cur);  
    if (r <= mid)  
        Add(cur << 1, l, r, x);  
    else  
        if (l > mid)  
            Add((cur << 1) | 1, l, r, x);  
        else  
        {  
            Add(cur << 1, l, mid, x);  
            Add((cur << 1) | 1, mid + 1, r, x);  
        }  
    pushup(cur);  
}  
  
int Segment_Tree::rmq_min(const int &cur, const int &l, const int &r)  
{  
    if (l <= segt[cur].l && r >= segt[cur].r)  
        return segt[cur].Min;  
    int mid = segt[cur].l + ((segt[cur].r - segt[cur].l) >> 1);  
    pushdown(cur);  
    if (r <= mid)  
        return rmq_min(cur << 1, l, r);  
    else  
        if (l > mid)  
            return rmq_min((cur << 1) | 1, l, r);  
        else  
            return min(rmq_min(cur << 1, l, mid), rmq_min((cur << 1) | 1, mid + 1, r));  
}  
  
struct cow  
{  
    int A, B;  
};  
cow Need[Max_M];  
  
inline  
bool comp(const cow &a, const cow &b)  
{  
    return a.B != b.B ? a.B < b.B : a.A < b.A;  
}  
  
int N, M;  
  
void init()  
{  
    Get_Val(N), Get_Val(M);  
    int C;  
    Space.build_tree(1, 1, N);  
    for (int i = 1;i <= N;++i)  
    {  
        Get_Val(C);  
        Space.Add(1, i, i, C);  
    }  
    for (int i = 1;i <= M;++i)  
        Get_Val(Need[i].A), Get_Val(Need[i].B);  
}  
  
void work()  
{  
    int Ans(0);  
    sort(Need + 1, Need + 1 + M, comp);  
    for (int i = 1;i <= M;++i)  
        if (Space.rmq_min(1, Need[i].A, Need[i].B) > 0)  
        {  
            ++Ans;  
            Space.Add(1, Need[i].A, Need[i].B, -1);  
        }  
    printf("%d", Ans);  
}  
  
int main()  
{  
    init();  
    work();  
    return 0;  
}

```

---

## 作者：VanHelsing (赞：4)

## P1937 Barn Allocation G  	
并不是一眼线段树题，我当时看了好几眼（  
这道题很容易的想到把每头牛的行踪看做一条线段，然后我每次满足一头牛的要求时就是将这条线段上的点区间加 1。  
当然了，我们不可能枚举满足那几头牛的要求，这个方法我早在刚学OI的时候就抛弃了。。。  
而且我们可以发现有的牛的要求很难满足，而另一些牛的要求比较容易满足，所以我们可以考虑按照这种关键字顺序进行排序。  
解法：对于每个线段，考虑以右端点为关键字进行排序。  
原因？右端点靠左的线段显然不会对它右边的点产生一些影响。所以我们先选它的话可以不用考虑对后续的影响，这样我们的复杂度才可以满足 $O(n logn)$ 。  
那么，一个点只能被 $a_i$ 条线段覆盖，所以我每次加入一条线段前查询这段区间中有没有当前已经被覆盖完全的点，修改的时候就在 $Seg_{left}$ 到 $Seg_{right}$ 区间减一，而答案就是我加入了几条线段，完美解决！  
 _**Code**_ :
 ```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+20;
struct Segmentree{
	int left,right;
	int sum,tag;
};Segmentree tree[maxn<<2];
struct Segment{
	int left,right;
};Segment Seg[maxn];
int a[maxn],ans,n,m;
bool cmp(Segment x,Segment y)
{
	return x.right<y.right;
}
void build(long long index,long long l,long long r)
{
	tree[index].left=l;
	tree[index].right=r;
	if(l==r)
	{
		tree[index].sum=a[l];
		return ;
	}
	long long mid=(l+r)>>1;
	build(index<<1,l,mid);
	build(index<<1|1,mid+1,r);
	tree[index].sum=min(tree[index<<1].sum,tree[index<<1|1].sum);
}
void pushdown(long long index)
{
	if(tree[index].tag)
	{
		tree[index<<1].tag+=tree[index].tag;
		tree[index<<1|1].tag+=tree[index].tag;
		tree[index<<1].sum-=tree[index].tag;
		tree[index<<1|1].sum-=tree[index].tag;
		tree[index].tag=0;
	}
}
void Modify(long long index,long long l,long long r,long long k)
{
	if(l<=tree[index].left&&r>=tree[index].right)
	{
		tree[index].sum-=k;
		tree[index].tag+=k;
		return;
	}
	pushdown(index);
	long long mid=(tree[index].left+tree[index].right)>>1;
	if(l<=mid)
	{
		Modify(index<<1,l,r,k);
	}
	if(r>mid)
	{
		Modify(index<<1|1,l,r,k);
	}
	tree[index].sum=min(tree[index<<1].sum,tree[index<<1|1].sum);
}
long long Query(long long index,long long l,long long r)
{
	if(l<=tree[index].left&&r>=tree[index].right)
	{
		return tree[index].sum;
	}
	pushdown(index);
	long long mid=(tree[index].left+tree[index].right)>>1;
	long long ret=0x3f3f3f3f;
	if(l<=mid)
	{
		ret=min(ret,Query(index<<1,l,r));
	}
	if(r>mid)
	{
		ret=min(ret,Query(index<<1|1,l,r));
	}
	return ret;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&Seg[i].left,&Seg[i].right);
	}
	sort(Seg+1,Seg+m+1,cmp);
	build(1,1,Seg[m].right);
	for(int i=1;i<=m;i++)
	{
		int tmp=Query(1,Seg[i].left,Seg[i].right);
		if(tmp<=0)
		{
			continue;
		}
		else
		{
			Modify(1,Seg[i].left,Seg[i].right,1);
			ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：小蒟蒻皮皮鱼 (赞：4)

[洛谷P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937)

题意：

有$N$个编号为$1-N$的点，每个点有一个权值$a[i]$。给你$M$个指令，每个指令包含两个数$l,r$表示把区间$[l,r]$的每个点的权值减一。要求每个点的权值不能为负数，求最多能满足几个指令。

题解：

这道题是一道很经典的题"活动安排"的变式，做法和它也很像。

先考虑把所有的指令以右端点为第一关键字从小到大排序，右端点相同则按左端点从小到大排序。遍历排序后的指令，若能满足(即区间$[l,r]$的最小值大于零)就满足他，否则就跳过。

区间修改和区间最值，用线段树就可以了。

正确性证明：

如果线段不矛盾都选上就好了，所以考虑矛盾的线段，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/o8zj2r6m.png)

考虑线段$[l1,r1]$和$[l2,r2]$矛盾，也就是$min([l2,r2])=1$。

此时，如果我们选择区间$[l2,r2]$，并且假设这种方法比$[l1,r1]$更优，那么多出来的线段一定在区间$[l1,l2]$中。由于我们是按照区间右端点排序的，所以在$[l1,l2]$中一定没有别的线段。反观区间$[r1,r2]$由于选择了第二个区间，所以$[r1,r2]$与之前相比是多减了1的，一定不比选择$[l1,r1]$优。

再考虑当两个区间右端点相同，即$[l1,r1],[l2,r1]$，那么此时不论怎么选，都不会对下一条线段产生影响。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m, a[N], ans;
int T[N << 2], minn[N << 2], lazy[N << 2];
struct node
{
	int l, r;
}nod[N];
bool cmp(node a, node b)
{
	if(a.r != b.r) return a.r < b.r;
	else return a.l < b.l;
}
void pushup(int cnt)
{
	minn[cnt] = min(minn[cnt << 1], minn[cnt << 1 | 1]);
}
void build(int cnt, int l, int r)
{
	if(l == r)
	{
		minn[cnt] = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(cnt << 1, l, mid);
	build(cnt << 1 | 1, mid + 1, r);
	pushup(cnt);
}
void pushdown(int cnt, int l, int r)
{
	if(lazy[cnt])
	{
		minn[cnt << 1] += lazy[cnt];
		minn[cnt << 1 | 1] += lazy[cnt];
		lazy[cnt << 1] += lazy[cnt];
		lazy[cnt << 1 | 1] += lazy[cnt];

		lazy[cnt] = 0;
	}
}
void update(int cnt, int l, int r, int nl, int nr)
{
	if(l >= nl && r <= nr)
	{
		lazy[cnt] -= 1;
		minn[cnt] -= 1;
		return;
	}
	int mid = l + r >> 1;
	pushdown(cnt, l, r);
	if(mid >= nl) update(cnt << 1, l, mid, nl, nr);
	if(mid < nr) update(cnt << 1 | 1, mid + 1, r, nl, nr);
	pushup(cnt);
}
int qmin(int cnt, int l, int r, int nl, int nr)
{
	if(l >= nl && r <= nr) return minn[cnt];
	int mid = l + r >> 1;
	pushdown(cnt, l, r);
	int ans = 999999999;
	if(mid >= nl) ans = min(ans, qmin(cnt << 1, l, mid, nl, nr));
	if(mid < nr) ans = min(ans, qmin(cnt << 1 | 1, mid + 1, r, nl, nr));
	return ans;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	build(1, 1, n);
	for(int i = 1; i <= m; i ++) scanf("%d%d", &nod[i].l, &nod[i].r);
	sort(nod + 1, nod + 1 + m, cmp);
	for(int i = 1; i <= m; i ++)
	{
		if(qmin(1, 1, n, nod[i].l, nod[i].r) > 0)
		{
			update(1, 1, n, nod[i].l, nod[i].r);
			ans ++;
		}
	}
	cout << ans;
}
```



---

## 作者：_cmh (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/P1937)

[双倍经验](https://www.luogu.com.cn/problem/SP8462)

## $\texttt{Description}$

有 $n$ 个牛棚，每头牛有想去 $A_i\sim B_i$ 区间编号的牛棚。每个牛棚限制 $C_i$ 头牛，求最多可以满足多少头牛的要求。 

## $\texttt{Solution}$

显然贪心。输入要求后将其排序，排序顺序按照 $A_i$ 从小到大排序，若相等则按 $B_i$ 从大到小的顺序排序。

接下来，我们从 $1\sim n$ 开始循环，遍历每一个牛棚。将所有要求进入这个牛棚的牛加入大根堆中，并将其累加至 $tot$ 数组中。

如果很恰巧，大根堆中的牛的数量 $\le ans+C_i$（大根堆中有之前已经满足要求的 $ans$ 头牛，并且这个牛棚可以容许 $C_i$ 头牛进入），那么就将其累加至 $ans$ 中，满足了他们的要求。

否则，有些牛无法进入牛棚。根据大根堆，我们将其放入大根堆时，是按照 $B_i$ 放的。大的 $B_i$ 在上，我们将堆顶的牛出队（因为后面这头牛还有可能能进入其他牛棚），尽可能让 $B_i$ 小的牛进入牛棚。可以证明，这样的方案最优。

最后 $ans$ 累加 $tot_i$ 中的值，即为答案。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
	int l,r;
	bool operator <(node aa) const{
		return l<aa.l;
	}
}req[N];
int a[N],tot[N];
priority_queue<int>q;
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=m;i++)
		cin>>req[i].l>>req[i].r;
	sort(req+1,req+m+1);
	int now=0,ans=0;
	for(int i=1;i<=n;i++){
		while(now+1<=m&&i>=req[now+1].l){
			now++;
			q.push(req[now].r);
			tot[req[now].r]++;
		}
		while(q.size()-ans>a[i]){
			tot[q.top()]--;
			q.pop(); 
		}
		ans+=tot[i];
	}
	cout<<ans;
    return 0;
}
```

谢谢观看。

---

## 作者：Saber_Master (赞：1)

[P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937)

一道特别经典的贪心题.

根据贪心策略，我们先以右端点为第一关键字，左端点为第二关键字从小到大进行排序.然后依次扫描每一头奶牛，判断其是否能插入，能插入就插入，否则舍弃。这里略证一下其正确性：

排完序后，对于当前奶牛，我们发现如果它不能插入并且非要强行插入的话，那么就得去前面已插入的奶牛中将有冲突的给去掉，但是当前奶牛贡献至多为$1$,去掉前面冲突的奶牛的代价至少为$1$。并且，对于后面的奶牛，由于我们右端点是从小到大排序的，所以去掉前面奶牛且插入当前奶牛的话对后面奶牛的插入更加不利。故当前奶牛不插入才是最优的。

至于判断能否插入，我们可以开一个数据结构维护当前奶牛所对应区间剩余容纳量的最小值，插入后区间集体减$1$。维护区间最小值和区间减法，容易想到线段树，然后直接做就行啦！

复杂度:$O(n \log n)$

```cpp
const ll N=2e5+5;

ll n, m;
ll v[N];

struct node{
	ll l, r;
	
	inline void Read(){
		read(l); read(r);
	}
	
	inline bool operator <(const node &X)const{
		return r==X.r?l<X.l:r<X.r;
	}
}p[N];

namespace seg{
	ll dat[N<<2], lazy[N<<2];
	
	inline void build(ll p, ll l, ll r){
		if (l==r) return (void) (dat[p]=v[l]);
		ll mid=l+r>>1;
		build(p<<1, l, mid); build(p<<1|1, mid+1, r);
		dat[p]=min(dat[p<<1], dat[p<<1|1]);
	}
	
	inline void pushup(ll p, ll val){
		dat[p]+=val; lazy[p]+=val;
	}
	
	inline void pushdown(ll p, ll l, ll r){
		if (lazy[p]==0 || l==r) return;
		pushup(p<<1, lazy[p]); pushup(p<<1|1, lazy[p]);
		return (void) (lazy[p]=0);
	}
	
	inline void update(ll p, ll l, ll r, ll u, ll v, ll val=-1){
		pushdown(p, l, r);
		if (u<=l && r<=v) return pushup(p, val);
		ll mid=l+r>>1;
		if (u<=mid) update(p<<1, l, mid, u, v, val);
		if (v>mid) update(p<<1|1, mid+1, r, u, v, val);
		dat[p]=min(dat[p<<1], dat[p<<1|1]);
	}
	
	inline ll query(ll p, ll l, ll r, ll u, ll v){
		pushdown(p, l, r);
		if (u<=l && r<=v) return dat[p];
		ll mid=l+r>>1, res=0x7fffffff;
		if (u<=mid) chkmin(res, query(p<<1, l, mid, u, v));
		if (v>mid) chkmin(res, query(p<<1|1, mid+1, r, u, v));
		return res;
	}	
}

ll res;
int main(){
	read(n); read(m);
	for (R ll i=1; i<=n; i++) read(v[i]);
	seg::build(1, 1, n);
	for (R ll i=1; i<=m; i++) p[i].Read();
	sort(p+1, p+m+1);
	for (R ll i=1; i<=m; i++){
		if (seg::query(1, 1, n, p[i].l, p[i].r)>0){
			++res;
			seg::update(1, 1, n, p[i].l, p[i].r);
		}
	}
	writeln(res);
}
```


---

## 作者：Adove (赞：1)

思路：贪心+线段树维护区间最小值；

我们将奶牛的路径抽象成线段，然后以右端点为第一关键字从小到大排序，对于右端点相同的，我们按长度从小到大排序。

数据范围告诉我们要用线段树来维护这些信息；

有些同学可能会去想离散化，但实际上，在本题数据范围内，线段非常密集，没有离散化的必要性。

对于优化时间的方案，我们可以标记永久化。

上代码↓

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN=(1<<17)-1;

int n,m,ans;
int a[MAXN],tree[MAXN<<1],add[MAXN<<1];
struct lint{
    int l,r;
}line[MAXN];

void build(int k,int l,int r){
    if(l==r){
        tree[k]=a[l];
        return;
    }int i=k<<1,mid=l+r>>1;
    build(i,l,mid);
    build(i|1,mid+1,r);
    tree[k]=min(tree[i],tree[i|1]);
}

bool cmp(lint a,lint b){
    if(a.r==b.r) return a.l>b.l;
    return a.r<b.r;
}

void cadd(int k,int l,int r,int le,int ri,int x){
    if(le<=l&&r<=ri){
        tree[k]+=x;
        add[k]+=x;
        return;
    }int i=k<<1,mid=l+r>>1;
    if(le<=mid) cadd(i,l,mid,le,ri,x);
    if(mid<ri) cadd(i|1,mid+1,r,le,ri,x);
    tree[k]=min(tree[i],tree[i|1])+add[k];
}

int ask(int k,int l,int r,int le,int ri,int x){
    if(le<=l&&r<=ri) return tree[k]+x;
    int i=k<<1,mid=l+r>>1;
    int num=MAXN;
    if(le<=mid) num=min(num,ask(i,l,mid,le,ri,x+add[k]));
    if(mid<ri) num=min(num,ask(i|1,mid+1,r,le,ri,x+add[k]));
    return num;
}

void init(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        scanf("%d",&a[i]);
    }build(1,1,n);
    for(int i=1;i<=m;++i){
        scanf("%d%d",&line[i].l,&line[i].r);
    }sort(line+1,line+m+1,cmp);
    return;
}

void solve(){
    for(int i=1;i<=m;++i){
        if(ask(1,1,n,line[i].l,line[i].r,0)>0){
            ++ans;
            cadd(1,1,n,line[i].l,line[i].r,-1);
        }
    }return;
}

void write(){
    printf("%d\n",ans);
    return;
}

int main(){
    init();
    solve();
    write();
    return 0;
}
```

---

## 作者：Arghariza (赞：0)

典型的贪心。

用线段树维护整个数列最小值，是否达到请求即判断**区间最小值**是否大于等于 $1$ 。 

将每个请求 $l_i,r_i$ 以右端点 $r_i$ 为第一关键字**从大到小排序** （即找到最右边的请求），再以左端点 $l_i$ 为第二关键字**从小到大排序**（让它们长度递减，便于取最大值，**可以忽略**），得到排序后的请求序列。

这样我们就可以挨个判断每个区间是否能够满足请求，如果可以就区间修改全部 $-1$ ， $ans$ 递增，否则直接跳过。

那么问题是为啥这贪心方案是最优的。

它由 $2$ 条结论组成：

1. 对于右端点相同的两个请求，左端点越大，方案越优。
2. 对于左端点越往右，方案越优。

显然第 $1$ 条结论非常明显，设 $r_i=r_j,l_i<l_j$ ，选 $j$ 显然比选 $i$ 多出来 $l_j-l_i$  的空间。

对于第 $2$ 条结论，设 $i,j$ 两条线段。

- 若 $i,j$ 没有冲突，直接算入答案显然是最优的。
- 如果 $i,j$ 有冲突：
1. 如果 $r_i=r_j$ ，显然选左端点最大最优（结论 $1$ ）。
2. 否则，不妨设 $l_j<l_i<r_j<r_i$ （不影响答案正确性），如果不选 $j$ ，会在现在的基础下使得 $[l_i,r_i]$ 全部 $-1$ ，并且让 $[l_j,r_j]$ 全部 $+1$ 。然而重叠区间 $[l_i,r_j]$ 仍然不变，则如果剩下的 $l$ 全部都小于等于 $l_i$ ，则显然是没有效果的，所以**不选 $j$ 的策略会使重叠部分全部 $-1$** 。反观不选 $i$ 的策略，我们会发现并没啥影响。结论 $2$ 显然成立。

$$\text{\color{white}{这该死的贪心终于证明完了}}$$

因此这个贪心方案是可行的，同时用线段树维护可以达到优秀的 $O(n\log n)$ 。

```cpp
#include <bits/stdc++.h>
#define inf 2147483647
#define maxn 100100
namespace mystd {
	inline int read() {
	    int w = 1, q = 0;
	    char ch = ' ';
	    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	    if (ch == '-') w = -1, ch = getchar();
	    while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
	    return w * q;
	}
	inline void write(int x) {
	    if (x < 0) {
	        x = ~(x - 1);
	        putchar('-');
	    }
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

int n, m, ans, s[maxn];

struct node {// 请求结构体
	int l, r;
	bool operator < (const node &rhs) const {
		if (r < rhs.r) return true;
		else if (r > rhs.r) return false;
		else {
			if (l > rhs.l) return true;
			else return false;
		}
	}
} q[maxn];

// 线段树维护区间最小值

int tree[maxn << 2], mins[maxn << 2], lazy[maxn << 2];

void pushup(int x) {
	tree[x] = tree[x << 1] + tree[(x << 1) | 1];
	mins[x] = min(mins[x << 1], mins[x << 1 | 1]);
}

void pushdown(int l, int r, int x) {
	int mid = (l + r) >> 1;
	tree[x << 1] += lazy[x] * (mid - l + 1);
	mins[x << 1] += lazy[x];
	tree[(x << 1) | 1] += lazy[x] * (r - mid);
	mins[x << 1 | 1] += lazy[x];
	lazy[x << 1] += lazy[x];
	lazy[(x << 1) | 1] += lazy[x];
	lazy[x] = 0;
}

void build(int l, int r, int x) {
	if (l == r) {
		tree[x] = mins[x] = s[l];
		lazy[x] = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, x << 1);
	build(mid + 1, r, (x << 1) | 1);
	pushup(x);
}

void update(int l, int r, int s, int t, int c, int x) {
	if (l <= s && t <= r) {
		tree[x] += (t - s + 1) * c;
		mins[x] += c;
		lazy[x] += c;
		return;
	}
	int mid = (s + t) >> 1;
	if (lazy[x]) pushdown(s, t, x);
	if (l <= mid) update(l, r, s, mid, c, x << 1);
	if (r > mid) update(l, r, mid + 1, t, c, (x << 1) | 1);
	pushup(x);
}

int query(int l, int r, int s, int t, int x) {
	if (l <= s && t <= r) return mins[x];
	int mid = (s + t) >> 1, res = inf;
	if (lazy[x]) pushdown(s, t, x);
	if (l <= mid) res = min(query(l, r, s, mid, x << 1), res);
	if (r > mid) res = min(query(l, r, mid + 1, t, (x << 1) | 1), res);
	return res;
}

int main() {
	n = read();
	m = read();
	for (int i = 1; i <= n; i++) {
		s[i] = read();
	}
	build(1, n, 1);
	for (int i = 1; i <= m; i++) {
		q[i].l = read();
		q[i].r = read();
	}
    // 排序
	sort(q + 1, q + m + 1);
	for (int i = 1; i <= m; i++) {
		if (query(q[i].l, q[i].r, 1, n, 1) >= 1) {// 达到请求
			update(q[i].l, q[i].r, 1, n, -1, 1);
			ans++;
		}
	}
	write(ans);
	return 0;
}
```

---

## 作者：年华天地 (赞：0)

首先 [双倍经验](https://www.luogu.com.cn/problem/SP8462)

## 思路
贪心+线段树维护。\
\
贪心：大家应该做过这个题的简化版把，用线段去覆盖区间要求不重，问最多能用几条线段去覆盖，我们怎么做的，贪心按右端点排序，然后依次选，那么这个题也是如此，只是可以重复，但有次数限制，我们便可以找到次数限制中最小的次数，检查一下能不能选这个线段，能放就放，然后区间次数减一；\
\
线段树：本题需要两个操作 1.区间查询最小值 2.区间加数 那么很显然的是一个线段树的裸题了吧

### 上代码
```
#include<cstdio>
#include<algorithm>
#define mid (l+r)/2
using namespace std;
const int maxn=2e5;
int n,m,a[maxn],ans,maxx;
struct node{
	int l,r;
}s[maxn];
struct tree{
	int l,r,sum,minn,lazy;
}t[maxn*4];
int min(int a,int b)
{
	return a<b?a:b;
}
bool cmp(node a,node b)
{
	return a.r<b.r;
}
void renew(int id)
{
	t[id].minn=min(t[id*2].minn,t[id*2+1].minn);
}
void build(int id,int l,int r)
{
	t[id].l=l;
	t[id].r=r;
	if (l==r)
	{
		t[id].minn=a[l];
		return ;
	}
	build(id*2,l,mid);
	build(id*2+1,mid+1,r);
	renew(id);
}
void pushdown(int id)
{
	t[id*2].minn-=t[id].lazy;
	t[id*2+1].minn-=t[id].lazy;
	t[id*2].lazy+=t[id].lazy;
	t[id*2+1].lazy+=t[id].lazy;
	t[id].lazy=0;
}
int query(int id,int l,int r)
{
	if (t[id].l>r||t[id].r<l)return 0x3f3f3f3f;
	else if (t[id].l>=l&&t[id].r<=r)return t[id].minn;
	else if (t[id].lazy)pushdown(id);
	return min(query(id*2,l,r),query(id*2+1,l,r));
}
void add(int id,int l,int r)
{
	if (t[id].l>r||t[id].r<l)return ;
	if (t[id].lazy)pushdown(id);
	if (t[id].l>=l&&t[id].r<=r)
	{
		t[id].minn--;
		t[id].lazy++;
		return ;
	}
	add(id*2,l,r);add(id*2+1,l,r);
	renew(id);
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)scanf("%d",&a[i]);
	for (int i=1;i<=m;i++)scanf("%d%d",&s[i].l,&s[i].r);
	sort(s+1,s+m+1,cmp);
	build(1,1,s[m].r);
	for (int i=1;i<=m;i++)
	{
		int tmp=query(1,s[i].l,s[i].r);
		if (tmp<=0)continue;
		else add(1,s[i].l,s[i].r),ans++;
	}	
	printf("%d",ans);
	return 0;
}
```


---

