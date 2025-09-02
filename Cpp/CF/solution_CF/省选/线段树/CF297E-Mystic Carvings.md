# Mystic Carvings

## 题目描述

The polar bears have discovered a gigantic circular piece of floating ice with some mystic carvings on it. There are $ n $ lines carved on the ice. Each line connects two points on the boundary of the ice (we call these points endpoints). The endpoints are numbered $ 1,2,...,2n $ counter-clockwise along the circumference. No two lines share an endpoint.

Now a group of 6 polar bears (Alice, Bob, Carol, Dave, Eve, Frank) are going to build caves on the endpoints. Each polar bear would build a cave and live in it. No two polar bears can build a cave on the same endpoints. Alice and Bob is a pair of superstitious lovers. They believe the lines are carved by aliens (or humans, which are pretty much the same thing to polar bears), and have certain spiritual power. Therefore they want to build their caves on two endpoints which are connected by a line. The same for Carol and Dave, Eve and Frank.

The distance between two caves X and Y is defined as one plus minimum number of other caves one need to pass through in order to travel from X to Y along the boundary of the ice (endpoints without caves are not counted).

To ensure fairness, the distances between the three pairs of lovers have to be the same (that is, the distance between Alice and Bob, the distance between Carol and Dave, and the distance between Eve and Frank are the same).

The figures below show two different configurations, where the dots on the circle are the endpoints. The configuration on the left is not valid. Although each pair of lovers (A and B, C and D, E and F) is connected a line, the distance requirement is not satisfied. The distance between A and B is 2 (one can go from A to B in the clockwise direction passing through F). The distance between E and F is also 2. However, the distance between C and D is 1 (one can go from C to D in the counter-clockwise direction without passing through any other caves). The configuration on the right is valid. All three pairs have the same distance 1.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297E/d4294009e1edf87a8acd5f07b8b6190c53a3334c.png)Count the number of ways to build the caves under the requirements. Two configurations are considered the same if the same set of 6 endpoints are used.

## 说明/提示

The second sample corresponds to the figure in the problem statement.

## 样例 #1

### 输入

```
4
5 4
1 2
6 7
8 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
8
1 7
2 4
3 9
5 11
6 8
10 16
13 15
14 12
```

### 输出

```
6
```

# 题解

## 作者：stoorz (赞：20)

不难发现，在一个圆中任意三条弦的位置关系只有如下五种情况：

![](https://s2.ax1x.com/2020/02/13/1qEbgH.png)

~~图2的不是弦但是意思是一样的。~~

那么如果要满足任意一条弦所连接的两个点之间的点数相同，只有图2和图5满足条件，我们就是要计算这两种情况的方案数。

直接计算不是很好计算，我们考虑用总方案数减去不合法（即图1、3、4）的方案数。

总方案数很简单，就是从$n$条弦中选出 $3$ 条的方案数 $C^3_n$。

对于图1，我们可以枚举每一条弦，把它当做中间的那一条，那么我们只需要求出这条弦左、右分别有多少条与它不相交的弦，记作 $l[i]$ 和 $r[i]$，那么这一条弦在中间的方案数就是 $l[i]\times r[i]$。所以图1的总方案数就是 $\sum^{n}_{i=1}l[i]\times r[i]$。

对于图3和图4，我们把它们放在一起计算。容易发现这两张图的共同点是“三条弦中有两条满足另外的两条弦一条与其相交，一条与其相离”。仔细看一下这句话，应该能看懂的 $:)$ 。

所以我们依然枚举每一条弦，对于任意一条弦，它的方案数就是“与它相交的弦的个数”$\times$ “与它不相交的弦的个数”。而我们知道与它不相交的弦的个数是 $l[i]+r[i]$，那么与它相交的弦的个数就是 $n-l[i]-r[i]-1$了。

考虑到每张图有两条弦满足上述“共同点”，所以这样每张图都会被算两遍，最终除以 $2$ 即为图4和图5的答案。也就是 $\frac{\sum^{n}_{i=1}(l[i]+r[i])(n-l[i]-r[i]-1)}{2}$。

计算答案部分我们已经在 $O(n)$ 的时间复杂度内完成了，现在如果我们可以计算出 $l[i],r[i]$，这道题就解决了。

例如下图，我们需要求蓝色弦的左右分别与它不相交的弦的条数，黑色弦都不与它相交，其中仅有弦 $4-5$ 在它右边。

![](https://s2.ax1x.com/2020/02/13/1qupcD.png)

观察在蓝色弦左边的弦，设蓝色弦的两个端点为 $x,y$，其他弦的端点为 $x',y'$，（$x<y,x'<y'$）发现需要满足一下三个条件之一：

1. $x'<x$ 且 $y'<x$
2. $x'<x$ 且 $y'>y$
3. $x'>y$ 且 $y'>y$

可以发现，这与二维偏序十分像，用二维偏序即可解决。

同理，右边的弦只需要满足一个条件：$x'>x$ 且 $y'<y$ ，同样可以用二维偏序解决。

至此，这道题的两个部分都已经结束。时间复杂度$O(n\log n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N=300010;
int n,l[N],r[N];
ll ans1,ans2;

struct node
{
    int x,y,id;
}a[N];

struct BIT
{
    int c[N];
    
    void add(int x,int val)
    {
        for (;x<=n*2;x+=x&-x)
            c[x]+=val;
    }
    
    int ask(int x)
    {
        int sum=0;
        for (;x;x-=x&-x)
            sum+=c[x];
        return sum;
    }
}bit;

bool cmp1(node x,node y)
{
    return x.x<y.x;
}

bool cmp2(node x,node y)
{
    return x.y>y.y;
}

int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        if (a[i].x>a[i].y) swap(a[i].x,a[i].y);
        a[i].id=i;
    }
    sort(a+1,a+1+n,cmp1);
    for (int i=1;i<=n;i++)  //二维偏序求每一条弦的 l[i] 和 r[i]
    {
        l[a[i].id]+=bit.ask(a[i].x)+bit.ask(n*2)-bit.ask(a[i].y);
        bit.add(a[i].y,1);
    }
    memset(bit.c,0,sizeof(bit.c));
    for (int i=n;i>=1;i--)
    {
        r[a[i].id]+=bit.ask(a[i].y)-bit.ask(a[i].x);
        bit.add(a[i].y,1);
    }
    memset(bit.c,0,sizeof(bit.c));
    sort(a+1,a+1+n,cmp2);
    for (int i=1;i<=n;i++)
    {
        l[a[i].id]+=bit.ask(n*2)-bit.ask(a[i].y);
        bit.add(a[i].x,1);
    }
    ans1=1LL*n*(n-1)*(n-2)/6;  //C(n,3)
    for (int i=1;i<=n;i++)
    {
        ans1-=1LL*l[i]*r[i];
        ans2+=1LL*(l[i]+r[i])*(n-l[i]-r[i]-1);
    }
    printf("%I64d",ans1-ans2/2);
    return 0;
}
```

---

## 作者：未来姚班zyl (赞：1)

## 题目大意

在一个长度为 $2n$ 的环上有 $n$ 对点，以二元组 $(a_i,b_i)$ 表示。其中，$a_i$ 与 $b_i$ 互不相等。

现在要求标记 $3$ 对点。定义这三对点的权值分别为，在环上从 $a_i$ 到 $b_i$ 经过的最小的被标记的点的数量。若这三对点的权值都相等，则方案是合法的。对合法方案计数。

## 题目分析

首先，选出的点的数量只有 $6$，对于每对被标记的点，其它的点顶多只有 $4$ 个，所以权值也就只有 $2,3,4$。我们对其分别讨论状况即可。

当然，在环上讨论是很麻烦的，我们把环当成 $1\sim 2n$ 的序列。则点对变成了区间，权值也就只跟区间内出现的端点数有关。

因为只有三对数，我们将其端点分别用 $A,B,C$ 表示。

首先，权值都为 $2$，则三对数在环上相离。简单画一画就知道只会有以下两种情况：

> $AABBCC$，$ABBCCA$。

权值都为 $3$，对于 $AA$ 来讲，一定有一个区间和它相交，钦定其为 $BB$，而另一个区间 $CC$，要么被 $AA$ 包含，要么两个端点都不在 $AA$ 内部。对 $BB$ 也是如此。但这会导致 $CC$ 的权值只能是 $2$ 或 $4$。所以不可能出现。

权值都为 $4$，可以以类似的思路简单地推出来，只可能长这样：

> $ABCABC$

所以合法的区间只会长这三样：

> $AABBCC$，$ABBCCA$，$ABCABC$

从区间的角度看，它们是本质不同的，所以一个思路就蹦出来了，对于每种情况找一个关键点来计数。

这就与区间的相对位置有关，很容易想到通过偏序解决。将左端点排序，设三个区间依次为 $i,j,k$。则三种情况分别变为：

> $b_i<a_j,b_j<a_k$

> $b_j<a_k,b_k<b_i$

> $b_i>a_k,b_j>b_i,b_k>b_j$

第一种是可以直接枚举 $j$ 来计数的，但后两种无法用数据结构统计，因为我们无法做到选择了一个区间的同时处理其它两个区间的关系。

仔细思考良久也没有发现什么有用的性质，难道要走到绝境了吗？

正难则反，要不试试容斥？

类似上述的分析，我们可以推出不合法的情况长啥样：

> $ABCCBA$，$ABBACC$，$AABCCB$，$ABACBC$……

这样看起来情况比前面的多得多，也不好计数。但是，仔细思考，发现三个区间的权值要么为 $2,2,4$，要么为 $3,3,4$，要么为 $3,3,2$。它们依旧互相独立。有什么用呢？

首先 $2,2,4$，则对于权值为 $4$ 的区间，一定是包含了其中一个区间，且另一个区间没有端点在当中。这是可以直接计数的。

剩下两种情况，对于其中一个权值为 $3$ 的区间，则一定有一个区间有且仅有一个端点在当中，而另一个区间的端点，要么全在里面，要么全在外面，总之，其它两个区间的相对位置无关紧要！这都可以计数。然后两个 $3$ 会被统计两次，所以这一部分除以 $2$ 即可！

所以对于每个区间记录其包含的区间，被包含的区间，相离的区间，相交的区间，这些全是二维偏序。

这不就做完了吗？真妙！

排序后树状数组统计，复杂度 $O(n\log n)$。

这题很容易因为误认为合法情况很好统计或者认为非法情况会比合法情况复杂很多而忽略了容斥的做法，陷入思考的深渊。如果想到了容斥，那么就豁然开朗。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1LL)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =5e5+5,M=1e6+5,inf=(1LL<<31)-1;
const ll llf=1e18,mod=998244353,bas=131;
const ui base=13331;
using namespace std;
int n;
struct node{
	int l,r;
}a[N];
inline bool cmp(node a,node b){
	return a.l<b.l;
}
ll ans;
int ct3[N],ct1[N],ct2[N],ct4[N],a1,a2,a3;
int t[N<<1];
inline void add(int x,int k){
	while(x<=(n<<1))t[x]+=k,x+=x&-x;
}
inline int query(int x){
	int ans=0;
	while(x)ans+=t[x],x-=x&-x;
	return ans;
}
int main(){
	n=read();
	rep(i,1,n){
		a[i].l=read(),a[i].r=read();
		if(a[i].l>a[i].r)swap(a[i].l,a[i].r);
	}
	sort(a+1,a+n+1,cmp);
	rep(i,1,n)ct1[i]+=query(a[i].l),ct3[i]+=query(a[i].r)-query(a[i].l),add(a[i].r,1);
	rep(i,1,n<<1)t[i]=0;
	per(i,n,1)ct1[i]+=query(n<<1)-query(a[i].r),add(a[i].l,1);
	rep(i,1,n<<1)t[i]=0;
	rep(i,1,n)ct2[i]+=query(n<<1)-query(a[i].r),add(a[i].r,1);
	rep(i,1,n<<1)t[i]=0;
	per(i,n,1)ct4[i]+=query(a[i].r),add(a[i].r,1);
	rep(i,1,n<<1)t[i]=0;
	per(i,n,1)ct3[i]+=query(a[i].r),add(a[i].l,1),add(a[i].r+1,-1);
	//1:相离
	//2:被包含
	//3:交
	//4:包含  
	ll k=0;
	rep(i,1,n)ans+=1LL*ct4[i]*(ct2[i]+ct1[i]),k+=1LL*ct3[i]*(ct1[i]+ct2[i]+ct4[i]);
	ans=ans+k/2LL;
	ans=1LL*n*(n-1)/2LL*(n-2)/3LL-ans;
	pf(ans);
	return 0;
}
```


---

