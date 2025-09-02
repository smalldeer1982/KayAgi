# [AGC001F] Wide Swap

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc001/tasks/agc001_f

長さ $ N $ の、$ 1\ ～\ N $ をちょうど $ 1 $ つずつ含む数列 $ P_1\ ...\ P_N $ が与えられます。

あなたはこの数列に対し、以下のような操作を何度でも行えます。

- 整数 $ i,j\ (1\ ≦\ i\ <\ j\ ≦\ N) $ を選ぶ。
- $ P_i $ と $ P_j $ の値を入れ替える。
- ただしこのとき、$ j\ -\ i\ ≧\ K $ かつ $ |P_i\ -\ P_j|\ =\ 1 $ を満たしていなければならない。

このような操作によって作ることのできる数列のうち、辞書順最小のものを求めてください。

## 说明/提示

### 制約

- $ 2≦N≦500,000 $
- $ 1≦K≦N-1 $
- $ P $ は $ 1,\ 2,\ ...,\ N $ の順列である。

### Sample Explanation 1

以下のような手順で操作を行えば良いです。 - $ 4\ 2\ 3\ 1 $ - $ 4\ 1\ 3\ 2 $ - $ 3\ 1\ 4\ 2 $ - $ 2\ 1\ 4\ 3 $

## 样例 #1

### 输入

```
4 2
4 2 3 1```

### 输出

```
2
1
4
3```

## 样例 #2

### 输入

```
5 1
5 4 3 2 1```

### 输出

```
1
2
3
4
5```

## 样例 #3

### 输入

```
8 3
4 5 7 8 3 1 2 6```

### 输出

```
1
2
6
7
5
3
4
8```

# 题解

## 作者：linghuchong_ (赞：74)

一种新的思路。 

考虑构造序列 $Q$ 使得 $Q_{P_i}=i$，变成交换相邻的差值大于等于 $k$ 的数。

先考虑暴力做法，按照冒泡排序，把大的尽可能往右挪。  

然后把冒泡排序改为归并排序。一个右边的数能比左边的数先进行归并就要保证它加 $k$ 小于等于左边的数的后缀最小值即可。每次归并时记录左边的后缀最小值。

代码如下

```cpp
#include<bits/stdc++.h>
#define FOR(i,a,b) for(register int i=a;i<=b;i++)
#define ROF(i,a,b) for(register int i=a;i>=b;i--)
#define isnum(ch) ('0'<=ch&&ch<='9')
#define int long long
#define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
char buf[100000],*p1(buf),*p2(buf);
using namespace std;
inline int read()
{
	int s=0,f=1;char _ch=gc;
	while(!isnum(_ch))(_ch=='-')&&(f=-1),_ch=gc;
	while(isnum(_ch))s=s*10+_ch-48,_ch=gc;
	return s*f;
}
const int N=5e5+10;
int n,k,a[N],id[N];
int Min[N],b[N];
#define mid ((l+r)>>1)
void merge(int l,int r){
	if(l==r)return;
	merge(l,mid),merge(mid+1,r);
	int num=N,now1=l,now2=mid+1,cnt=l;
	ROF(i,mid,l)num=min(num,a[i]),Min[i]=num;
	while(now1<=mid&&now2<=r){
		if(Min[now1]>=a[now2]+k)b[cnt++]=a[now2],now2++;
		else b[cnt++]=a[now1],now1++;
	}
	while(now1<=mid)b[cnt++]=a[now1],now1++;
	while(now2<=r)b[cnt++]=a[now2],now2++;
	FOR(i,l,r)a[i]=b[i];
}
signed main()
{
	n=read(),k=read();
	FOR(i,1,n)a[read()]=i;
	merge(1,n);
	FOR(i,1,n)id[a[i]]=i;
	FOR(i,1,n)cout<<id[i]<<'\n';
	return 0;
}
```



---

## 作者：小粉兔 (赞：56)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/AGC001F.html](https://www.cnblogs.com/PinkRabbit/p/AGC001F.html)。

### 题意简述

有一个 $1 \sim N$ 的排列 $P_1 \sim P_N$，你可以执行如下操作任意多次：

- 选取两个下标 $i, j$（$1 \le i < j \le N$），还需满足 $j - i \ge K$ 且 $|P_i - P_j| = 1$，然后交换 $P_i$ 与 $P_j$ 的值。

请问你能得到的字典序最小的排列是什么？请输出它。

- $1 \le N \le 5 \times {10}^5$。

### 题解

它给了个排列 $P$，然后 $i, j$ 两个位置能交换的条件是 $|i - j| \ge K$ 并且 $|P_i - P_j| = 1$。

这个条件看起来十分的玄妙，考虑 $Q$ 为 $P$ 的逆置换，那么此时就相当于如果 $|Q_i - Q_{i + 1}| \ge K$ 你就可以交换位置 $i$ 和 $(i + 1)$。

看起来舒服多了。我们需要求出字典序最小的 $P$，放到 $Q$ 上就是要让**值**为 $1$ 的**下标**尽量靠前（$Q_x = 1$ 的 $x$ 尽量小），以此类推。

然后再考虑 $Q$ 中的两个值，如果它们的差小于 $K$，那么它们就永远无法交换，也就是顺序就被定死了。

也就是说：对于所有满足 $|u - v| < K$ 的 $(u, v)$，它们在 $Q$ 中出现的相对位置被固定了。

而对于两个排列 $Q, R$，我们可以证明如果每一对 $(u, v)$ 在 $Q, R$ 中的相对位置都相同的话，它们就可以互相转换。限于篇幅不证。

也就是说只要求出满足所有 $(u, v)$ 限制的排列即可。再次回到初始排列 $P$，重写限制为：

对于所有满足 $|i - j| < K$ 的下标 $(i, j)$，如果初始时 $P_i < P_j$，则最终的排列也必须有 $P_i < P_j$，反之亦然。

你可以回去观察一下样例是否满足这个条件，一定是满足的。

然而此时我们需要让 $P_1$ 尽量小，在此条件下让 $P_2$ 尽量小，以此类推。

可以发现我们把不等号写出来后，整个序列就变成了个 DAG，我们要给予每个点适当的拓扑编号，让拓扑编号的字典序尽量小。

这就变成了一个经典问题。**在一般情况下**，它的解决方案**并不是**部分题解所述的：「直接拓扑排序，但每次优先取编号最小的点」。

**而是**：把所有边反向，然后拓扑排序（也就是倒着拓扑排序），但每次优先取编号最大的点，拓扑编号也从 $N$ 往 $1$ 编号。

这两种方法是对称的，但是**在一般情况下**求得的东西并不相同，且第二种才是对的。

无论如何，这张图的边数还是 $\mathcal O (N K)$ 的，不能显式建图做。我们考虑用数据结构优化这个过程：

任意时刻下，入度为 $0$ 的点，即是满足 $P_i$ 为在 $(i - K, i + K)$ 中（注意是开区间）的最大值的 $i$。

删除一个点 $i$ 就相当于把 $P_i$ 改成 $-\infty$，与此同时会影响到周围 $(i - K, i + K)$ 这个区域（开区间）的连边情况。

那么我们可以用线段树维护这个过程，初始时先查一遍每个点是否入度为 $0$，如果是就加入一个大根堆中。

然后每次取出堆顶，删除它然后分别查询 $(i - K, i)$ 和 $(i, i + K)$ 这两个区域中的最大值编号，检查是否入度为 $0$ 入堆。

最后直接输出编号即可，很有趣的一题，时间复杂度为 $\mathcal O (N \log N)$。

**最后**：之所以前文中第一种「错误」的方法也能 AC，是因为本题中特殊的连边形式：

考虑第一种方法第一次错误编号时：假设是把本应给位置 $k$ 的编号给了位置 $j$，根据算法流程，此时有 $j < k$。

现在 $j$ 的编号减小了，但答案却错了，必是因为 $k$ 的编号增大直接或间接导致了某个位置 $i$ 的编号不得不增大。此时有 $i < j < k$。

注意到此时 $j$ 是无入度的位置中最小的，所以比 $j$ 小的位置中如果还有未标号的，一定有 $j$ 向其的连边，这是因为：

一直沿 DAG 中的边往回走（删除已编号的点），最终会走到没有入度的点，如果不是 $j$ 则中间一定跨过 $j$，那时直接到 $j$ 即可。

所以一定有：最终答案中，此时未编号的，比 $j$ 小的位置，其编号一定大于 $j$ 的编号。

所以此时我们如果直接把 $j$ 的编号提到 $k$ 的编号之前，是完全不影响 $j$ 之前的所有点的编号的。

与 $i$ 的标号会增大矛盾，Q.E.D.

```cpp
#include <cstdio>
#include <algorithm>
#include <queue>

const int Inf = 0x3f3f3f3f;
const int MN = 500005, MS = 1 << 20 | 7;

int N, K, P[MN], Ans[MN];

#define li (i << 1)
#define ri (li | 1)
#define mid ((l + r) >> 1)
#define ls li, l, mid
#define rs ri, mid + 1, r
int mxp[MS];
void Build(int i, int l, int r) {
	if (l == r) return mxp[i] = l, void();
	Build(ls), Build(rs);
	mxp[i] = P[mxp[li]] > P[mxp[ri]] ? mxp[li] : mxp[ri];
}
void Del(int i, int l, int r, int p) {
	if (l == r) return mxp[i] = 0, void();
	p <= mid ? Del(ls, p) : Del(rs, p);
	mxp[i] = P[mxp[li]] > P[mxp[ri]] ? mxp[li] : mxp[ri];
}
int Qur(int i, int l, int r, int a, int b) {
	if (r < a || b < l) return 0;
	if (a <= l && r <= b) return mxp[i];
	int v1 = Qur(ls, a, b), v2 = Qur(rs, a, b);
	return P[v1] > P[v2] ? v1 : v2;
}

int inq[MN];
std::priority_queue<int> pq;
inline void check(int id) {
	if (inq[id]) return ;
	if (Qur(1, 1, N, id - K + 1, id + K - 1) == id)
		pq.push(id), inq[id] = 1;
}

int main() {
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; ++i) scanf("%d", &P[i]);
	P[0] = -Inf;
	Build(1, 1, N);
	for (int i = 1; i <= N; ++i) check(i);
	for (int i = N; i >= 1; --i) {
		int u = pq.top(); pq.pop();
		Ans[u] = i;
		Del(1, 1, N, u);
		int pos;
		if ((pos = Qur(1, 1, N, u - K + 1, u - 1))) check(pos);
		if ((pos = Qur(1, 1, N, u + 1, u + K - 1))) check(pos);
	}
	for (int i = 1; i <= N; ++i) printf("%d\n", Ans[i]);
	return 0;
}
```

---

## 作者：Syzygy12 (赞：12)

## F : Wide Swap

### 翻译 :

给出一个元素集合为$\{1,2,\dots,N\}\ (1\leq N\leq 500,000)$的排列P，当有$i,j\ (1\leq i<j\leq N)$满足$j-i\geq K\  (1\leq K\leq N-1)$且$|P_{i}-P_{j}|= 1$时，可以 交换$P_{i}$和$P_{j}$

求：可能排列中字典序最小的排列

### 题解 :

首先，观察到$j-i\geqslant k$非常难搞，但是$|P_{i}-P_{j}|= 1$有很好的性质（相邻自然数），这启发我们想到一个难以想到的想法：令$Q_{P_i}=i$ ，即Q为P的逆序列。

则原问题可以转化为：

- 给出一个排列Q为P的逆序列

- 每次可以交换相邻两个数

- 交换的两个数的差的绝对值$\geqslant k$

- 让最终的排列的逆序列字典序最小

首先，最终的排列的逆序列字典序最小，等价于，最终的排列的反序序列字典序最大。感性理解的话就是先让值大的尽量往后放，让值大的不抢值小的 的位置，这样值小的就会尽量在能达到的最前面，也即逆序列的字典序最小。

举个例子：假如我们从后往前扫到这个位置，假如可以填1 3 4 5，假如填1的话一定不优，因为1一定能填在这前面的位置，从而使最终的排列的逆序列字典序最小，3,4同理，所以一定填5最优。 假如只能填1，那么这个位置一定要填1。

然后，问题转化为：

- 给出一个排列R为Q的反序序列

- 每次可以交换相邻两个数

- 交换的两个数的差的绝对值$\geqslant k$

- 让最终的排列的字典序最大

观察到一个的性质：如果$|R_i-R_j|<k$，那么$R_i,R_j$之间的相对顺序就不会变。这是因为我们最多能把它们交换到相邻位置，而不能再从相邻位置再互相交换从而使相对顺序更改。 反之，如果$|R_i-R_j|\geqslant k$，那么$R_i,R_j$之间的相对顺序就可能会变，取决于$i,j$之间能否一路交换过来。

那么一个朴素的做法出来了：枚举两个位置，假如这两个位置的数的绝对值$<k$，则从前面的位置向后面的位置连边，最终跑一个以当前位置的数为关键字的拓扑排序即可，但是复杂度为$O(n^2)$

我们观察到有很多边是冗余的，比如$a\to b,b\to c,a\to c$三条边中$a\to c$就是冗余的。

下面给出一个一般性的做法：

倒序枚举i，查找$[a_{i+1},a_{i+k-1}]$中有哪些数的下标$>i$，求出它们下标的最小值x，连边$a_i\to a_x$，$[a_{i-k+1},a_{i-1}]$同理。

这个算法的正确性在于，最小值x一定在其他值的前面，并且距离$<k$，那么拓扑序中$a_x$一定在$a_{others}$之前，那么只需要保证$a_i$在$a_x$，之前，就可以保证$a_i$在$a_{others}$之前，$[a_{i-k+1},a_{i-1}]$同理

容易发现这个东西可以用线段树维护，只需单点修改，区间求min。最终拓扑排序用堆即可。

这个转化为逆序列是真巧妙

### 代码 ：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5;
int p[N],a[N],b[N];
struct node{int l,r,mid,mn;}s[N<<2];
void build(int di,int l,int r)
{
    s[di].l=l,s[di].r=r,s[di].mid=l+r>>1,s[di].mn=1e9;
    if(l==r)return;
    build(di<<1,l,s[di].mid),build(di<<1|1,s[di].mid+1,r);
}
void ins(int di,int x,int v)
{
    if(s[di].l==s[di].r){s[di].mn=v;return;}
    if(x<=s[di].mid)ins(di<<1,x,v);
    else ins(di<<1|1,x,v);
    s[di].mn=min(s[di<<1].mn,s[di<<1|1].mn);
}
int qry(int di,int l,int r)
{
    if(l<=s[di].l&&s[di].r<=r)return s[di].mn;
    else if(r<=s[di].mid)return qry(di<<1,l,r);
    else if(l>s[di].mid)return qry(di<<1|1,l,r);
    return min(qry(di<<1,l,r),qry(di<<1|1,l,r));
}
struct edge{int to,nxt;}e[N<<1];
int head[N],tot=1;
void adde(int x,int y){e[tot]=(edge){y,head[x]};head[x]=tot++;}
priority_queue<int>q;
int n,rd[N];
void topo()
{
    for(int i=1;i<=n;i++)
        for(int j=head[i];j;j=e[j].nxt)rd[e[j].to]++;
    for(int i=1;i<=n;i++)if(!rd[i])q.push(i);
    int tt=0;
    while(!q.empty())
    {
        int u=q.top();q.pop(),b[++tt]=u;
        for(int i=head[u];i;i=e[i].nxt)
            if(!(--rd[e[i].to]))q.push(e[i].to);
    }
}
int main()
{
    int k;scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){int x;scanf("%d",&x),a[x]=i;}
    for(int i=1;i<=n/2;i++)swap(a[i],a[n-i+1]);
    build(1,1,n);
    for(int i=n;i>=1;i--)
    {
        int x=qry(1,max(1,a[i]-k+1),a[i]);
        if(x>=1&&x<=n)adde(a[i],a[x]);
        x=qry(1,a[i],min(n,a[i]+k-1));
        if(x>=1&&x<=n)adde(a[i],a[x]);
        ins(1,a[i],i);
    }
    topo();
    for(int i=1;i<=n/2;i++)swap(b[i],b[n-i+1]);
    for(int i=1;i<=n;i++)p[b[i]]=i;
    for(int i=1;i<=n;i++)printf("%d\n",p[i]);
}

```


---

## 作者：Regimes (赞：7)

## 标签：

线段树，图论，拓扑排序，转换

## 来源：

$Atcoder \ 1984$

## 题意

给定一个排列，每次可以对于每一个下标$i$.

与下标$j$大于等于$i+K$且$|a_i-a_j|=1$进

行交换。求使字典序最小的排列。

# $solution$

我们发现对于现在的题面，其实并不是很好做，

但是我们发现$|a_i-a_j|=1$，于是我们可以

对于么一个数，把权值看作下标，对于下标，当

作点权。那么现在的问题就转换为，对于一个新的排列，

我们可以交换满足权值在$[b_i+K,n]$或$[1,b_i-K]$的

相邻两个数。但原问题是说在原排列上的字典序最小，

于是，你会发现，由于位置与权值一一对应的关系，

我们在新排列上字典序最小，就会使原排列字典序最小。

那么我们如何保证新排列的字典序呢？我们知道

右边的权值在$[b_i+K,n]$或$[1,b_i-K]$范围的数我们

无法确定它与$i$的先后关系，但是对于在$[b_i-K+1,b_i+K-1]$

这个区间的数我们一定可以确定它们一定就在$i$的后面，

无论怎么交换都无法改变他们的位置关系。

那么刚好我们可以对于每一个点$i$，向后面权值在

$[b_i-K+1,b_i+K-1]$的点连出一条有向边，表示

他们之间的访问顺序。这样我们就得出了一个$O(n^2)$

的做法了。这个显然是个$DAG$,所以我们可以直接跑

拓扑排序了。

然后我们深入思考，就会发现，这里有一些边是没必要的，

比如说$a->b->c$，我们其实已经间接知道$a$与$c$的关系

了，所以，我们改变连边策略，我们从后往前考虑，对于位

置$pos$,我们连两条边，一条向$[b_i+1,b_i+K-1]$中位置

最靠前的,一条向$[b_i-K+1,b_i-1]$中位置最靠前的，这样

我们其实就是间接的让$b_i$连向了下一个位置最靠前的点

的连向的权值在$[b_i-K+1,b_i-1]$的点，于是我们只要

对于新图，跑一遍拓扑排序就行。

人女性化，但常数大的代码

```cpp

#include<bits/stdc++.h>

using namespace std ;

#define inf 99999999
#define N 1000007
#define ls x<<1
#define rs x<<1|1

priority_queue< int , vector<int> , greater<int> > q ;

int tot , n , m , cnt , k ;
int nex[2*N] , fire[N] , to[2*N] ;
int To[N] , Mn[4*N] , in[N] , Ans[N] ;

inline int read()
{
    int x = 0 , f = 1 ; char c = getchar();
    while( c < '0' || c > '9' ) { if( c == '-' ) f = -1; c = getchar() ; }
    while( c >= '0' && c <= '9' ) x = x * 10 + c - 48 , c = getchar() ;
    return x * f ;
}

void add(int u , int v){
    nex[++tot] = fire[u] ;
    fire[u] = tot ;
    to[tot] = v ;
    in[v]++ ;
    return ;
}

void build(int x , int l , int r){
    Mn[x] = inf ;
    if( l == r ) return ;
    int mid = l + r >> 1 ;
    build( ls , l , mid ) ; build( rs , mid + 1 , r ) ;
}

void update(int x , int l , int r , int pos , int t ){
    Mn[x] = min( Mn[x] , t ) ;
    if( l == r ) return ;
    int mid = l + r >> 1 ;
    if( pos <= mid ) update( ls , l , mid , pos , t ) ;
    else update( rs , mid + 1 , r , pos , t ) ;
}

int Ask(int x , int l , int r , int ll , int rr){
    if( ll > rr ) return inf ;
    if( l > rr || r < ll ) return inf ;
    if( ll <= l && r <= rr ) return Mn[x] ;
    int mid = l + r >> 1 ;
    return min( Ask( ls , l , mid , ll , rr ) , Ask( rs , mid + 1 , r , ll , rr ) ) ;
}

void topo(){
    for(int i = 1 ; i <= n ; i++ ) if( !in[i] ) q.push( i ) ;
    while( !q.empty() ){
        int u = q.top() ; q.pop() ;
        Ans[u] = ++cnt ;
        for(int i = fire[u] ; i ; i = nex[i] ){
            int v = to[i] ;
            in[v]-- ;
            if( !in[v] ) q.push( v ) ;
        }
    }
    return ;
}

int main()
{
    scanf("%d%d" , &n , &k ) ;
    for(int i = 1 ; i <= n ; i++ ) To[read()] = i ;
    build( 1 , 1 , n ) ;
    for(int i = n ; i >= 1 ; i-- ){
        int now = Ask( 1 , 1 , n , To[i] + 1 , min( To[i] + k - 1 , n ) ) ;
        if( now != inf ) add( To[i] , To[now] ) ;
        now = Ask( 1 , 1 , n , max( 1 , To[i] - k + 1 ) , To[i] - 1 ) ;
        if( now != inf ) add( To[i] , To[now] ) ;
        update( 1 , 1 , n , To[i] , i ) ;
    }
    topo() ;
    for(int i = 1 ; i <= n ; i++ ) printf("%d\n" , Ans[i] ) ;
    return 0 ;
}

```

---

## 作者：FoXreign (赞：6)

# **题意**

给定一个长度为 $N$ ，正好包含 $1$ ~ $N$ 的序列 $P_1 \cdots P_N$ ，你可以执行以下操作任意次：

- 选取两个下标 $i,j$ ，当满足 $j - i \geq K$ 且 $|P_i-P_j| = 1$ 时，你可以交换 $P_i$ 和 $P_j$ 的值。
​

求最终可能得到的字典序最小的排列。

# **题目分析**

很好的一道题。

## **逆置换**

现在的题面难以下手，因此不妨设 $Q$ 为 $P$ 的逆置换，即 $Q_{Pi} = i$ ，于是题面转化为如果 $|Q_i - Q_{i \pm 1}| \geq K$ ，那么就可以交换 $i$ 与 $i \pm 1$ 这两个相邻的元素。

我觉得这一点的思想类似于多维偏序的问题，前者是由多维向低维的转化，而本题则是对判断条件由多到少的转化。

同时，要使 $P$ 字典序最小，等价于要使 $Q$ 字典序最小，在此给出证明：

假设当前要填的最小数为 $j$ ，现有位置 $i$ 与 $i'$ ，且 $i < i'$ ，对 $Q_i = j$ 与 $Q_{i'} = j$ ，当还原为原序 $P$ 时，有 $P_j = i$ 与 $P_j = i'$ ，显然前者的字典序小于后者，得证。

## **反向拓扑排序**

考虑 $Q$ 中的两个值 $Q_i$ 与 $Q_j$ ，不难发现当 $|Q_i - Q_j| < K$ 时， $Q_i$ 与 $Q_j$ 的相对位置（即先后顺序）无论如何操作都不会发生变化，因为序列 $Q$ 中仅有相邻的两个数可能发生交换，所以 $Q_i$ 与 $Q_j$ 的相对位置要发生改变，两者必须交换一次，否则的话它们的关系就被锁死了，也就是上述说的相对位置固定了。

因此对某个 $Q_i (1 \leq i \leq N) $ ，对其后方的 $Q_j (i < j \leq N)$ ，有：
- 当 $Q_j \in [1,Q_i - k] \bigcup [Q_i + k,n]$ ，我们无法确定二者的相对位置关系
- 当 $Q_j \in [Q_i - k + 1,Q_i - 1] \bigcup [Q_i + 1,Q_i + k + 1]$ ， $Q_j$ 必排在 $Q_i$ 的后方

相对位置无法改变不难想到就是拓扑排序，而要求较小的数下标尽可能小更是经典问题，建反图跑拓扑排序：

[①号传送门](https://acm.dingbacode.com/showproblem.php?pid=4857)

[②号传送门](https://acm.dingbacode.com/showproblem.php?pid=2647)


## **线段树优化建图**

现在我们得到了一个朴素的 $O(nk)$ 算法：对于每个 $Q_i$ ，向其后方所有 $Q_j \in [Q_i - k + 1,Q_i - 1] \bigcup [Q_i + 1,Q_i + k + 1]$ 连一条有向边 $Q_j \rightarrow Q_i$ （注意是反向建图），然后跑一遍拓扑序就能出答案。

但实际上，由于传递性（$a\rightarrow b , b\rightarrow c \Rightarrow a \rightarrow c$），我们是没有必要把边连满的，所以我们从后往前枚举，对于当前位置的 $Q_i$ ,只需分别向在两个范围内最先出现的 $Q_j$ 与 $Q_{j'}$ 连两条边即可，因为两者的区间有重叠，所以 $Q_j$ 与 $Q_{j'}$ 对之后 $[Q_i - k + 1,Q_i - 1]$ 与 $[Q_i + 1,Q_i + k + 1]$ 内的点一定存在连边，从而使得 $Q_i$ 间接地连接了区间内所有符合要求的点，时间复杂度 $O(nlogn)$ 。

最后注意不要忘了还原成原序列。

## **AC代码**：
```
#include <bits/stdc++.h>
#define rep(i, x, y) for (register int i = (x); i <= (y); i++)
#define down(i, x, y) for (register int i = (x); i >= (y); i--)
const int inf = 0x3f3f3f3f;
const int maxn = 5e5 + 5;

char buf[1 << 23], *p1 = buf, *p2 = buf, obuf[1 << 23], *O = obuf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int n, k;
int inv[maxn], deg[maxn], ans[maxn];
std::vector<int> e[maxn];
std::priority_queue<int> q;

#define lson k << 1
#define rson k << 1 | 1
struct node
{
    int l, r, min;
} tree[maxn << 2];

inline void pushup(int k) { tree[k].min = std::min(tree[lson].min, tree[rson].min); }

void build(int k, int l, int r)
{
    tree[k].l = l, tree[k].r = r;
    if (l == r)
    {
        tree[k].min = inf;
        return;
    }
    int mid = (l + r) >> 1;
    build(lson, l, mid);
    build(rson, mid + 1, r);
    pushup(k);
}

void update(int k, int p, int x)
{
    if (tree[k].l == tree[k].r)
    {
        tree[k].min = x;
        return;
    }
    int mid = (tree[k].l + tree[k].r) >> 1;
    p <= mid ? update(lson, p, x) : update(rson, p, x);
    pushup(k);
}

int query(int k, int l, int r)
{
    if (l > r)
        return inf;
    if (l <= tree[k].l && tree[k].r <= r)
        return tree[k].min;
    int mid = (tree[k].l + tree[k].r) >> 1;
    if (r <= mid)
        return query(lson, l, r);
    else if (l > mid)
        return query(rson, l, r);
    else
        return std::min(query(lson, l, mid), query(rson, mid + 1, r));
}

void topo()
{
    int cnt = n;
    rep(i, 1, n) if (!deg[i]) q.push(i);
    while (!q.empty())
    {
        int u = q.top();
        q.pop();
        inv[cnt--] = u;
        for (auto v : e[u])
        {
            --deg[v];
            if (!deg[v])
                q.push(v);
        }
    }
}

int main(int argc, char const *argv[])
{
    n = read(), k = read();
    rep(i, 1, n) inv[read()] = i;
    build(1, 1, n);
    down(i, n, 1)
    {
        //分别找两个范围内最先出现的点
        int pos = query(1, inv[i] + 1, std::min(inv[i] + k - 1, n));
        if (pos ^ inf)
            //反向建图，反向连边
            e[inv[pos]].push_back(inv[i]), ++deg[inv[i]];
        pos = query(1, std::max(1, inv[i] - k + 1), inv[i] - 1);
        if (pos ^ inf)
            e[inv[pos]].push_back(inv[i]), ++deg[inv[i]];
        //加入当前点的贡献
        update(1, inv[i], i);
    }
    topo();
    //还原成原序列
    rep(i, 1, n) ans[inv[i]] = i;
    rep(i, 1, n) printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：Thaumaturge (赞：3)

提供一种不一样的写法。

注意到我们交换的数在序列中可能不相邻，但他们的值是相邻的，所以可以对这个排列求一遍它的逆排列，跑一遍原问题，再把它逆回来即可。

现在我们的问题是：对于一个排列$P$，可以交换相邻且差$>=K$的两项，最小化排列字典序。

如果我们交换的是顺序对，就会增大字典序，并且对于减小字典序显然没有帮助，因此每次需要找到一个满足相邻两项差$>=K$的逆序对交换。

暴力是$O(n^2)$，如何优化？考虑按原排列的顺序逐个加数，发现对于一个排好序的前缀，后方有数加入进来时，不断交换逆序对使字典序变小时；这个前缀中的元素的相对顺序不会改变。

所以每次只需要找到一个位置，使得它后方的数与待插入的数的差全部$>=K$，把数插入到这个位置就好了。

序列上二分及动态插入，$Splay$即可。

```cpp
/*************************************************************************
	> File Name: AGC001F.cpp
	> Author: The-Out-Land
	> Mail: 2264454706@qq.com 
	> Created Time: 2021年01月26日 星期二 16时30分08秒
 ************************************************************************/

#include <bits/stdc++.h>

#define enter putchar('\n')
#define space putchar(' ')
#define re register
#define N 501000

using namespace std;

const int inf=0x3f3f3f3f;

inline int max(int x,int y){return (x>y?x:y);}

inline int min(int x,int y){return (x<y?x:y);}

inline int read(){
	int x=0;char c=getchar();bool y=1;
	for(;c<'0' || c>'9';c=getchar()) if(c=='-') y=0;
	for(;c>='0' && c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	if(y) return x;
	return -x;
}

int st[N],top;

int n,K,p[N],q[N];

struct Splay_Tree{
	int mn[N],s[N][2],fa[N],val[N],cnt,rt;
	inline void init(){mn[0]=inf;return;}
	inline bool isright(int x){return s[fa[x]][1]==x;}
	inline void pushup(int x){mn[x]=min(val[x],min(mn[s[x][0]],mn[s[x][1]]));return;}
	inline void rotate(int x){
		int k=isright(x),F=fa[x];
		if(F!=rt) s[fa[F]][isright(F)]=x;fa[x]=fa[F];fa[F]=x;
		fa[s[x][k^1]]=F;s[F][k]=s[x][k^1],s[x][k^1]=F;
		pushup(F);pushup(x);
		return;
	}
	inline void Splay(int x){
		while(fa[x]){
			if(fa[fa[x]])
				rotate(isright(x)==isright(fa[x])?fa[x]:x);
			rotate(x);
		}
		rt=x;
		return;
	}
	inline void insert(int x){
		if(!cnt){cnt=rt=1;val[1]=x;return;}
		int now=rt,las=0;
		while(now){
			las=now;
			if(min(val[now],mn[s[now][1]])>=x+K)	now=s[now][0];
			else									now=s[now][1],las=-las;
		}
		++cnt;fa[cnt]=abs(las);val[cnt]=mn[cnt]=x;s[abs(las)][las<0]=cnt;
		Splay(cnt);
		return;
	}
	inline void Calc(int x){
		if(!x) return;if(x<0) x=rt;
		Calc(s[x][0]);st[++top]=val[x];Calc(s[x][1]);
		return;
	}
}tree;

inline void Input(){
	n=read(),K=read();
	tree.init();
	for(re int i=1;i<=n;++i) q[p[i]=read()]=i;
	return;
}

inline void solve(){
	for(re int i=1;i<=n;++i) tree.insert(q[i]);//enter;
	tree.Calc(-1);
	for(re int i=1;i<=n;++i) p[st[i]]=i;//enter;
	for(re int i=1;i<=n;++i) printf("%d\n",p[i]);
	return;
}

int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	Input();
	solve();
	return 0;
}
```



---

## 作者：Zory (赞：3)

设A[p[i]]=i即某个值的位置，那么就是每次交换相邻的，差>=K的值

注意到如果两个值，$差<K$，则相对位置是不会改变的
即对于A中的数字i，数字(i-K,i+K)与i的相对顺序不能改变

那么就是说我能得出一些顺序的限制条件，在满足这些条件的情况下构造一个拓扑序方案，我们已经获得了一个 $n^2$的做法

这个做法的主要瓶颈在于边数过多，这些边我能用bitset快速获得，但连边还是没办法优化

但这个边多只发生在K比较大的时候，而这种时候其实拓扑排序中没意义的边是很多的，所以思路是尽量减少边数

然后这里我一开始的想法是，对于每个i只考虑i-K部分，原本在前后的限制，然后发现很难做

但如果每个i，考虑i-K和i+K，他们原本在前面的限制，就完全不一样了，因为距离限制是对称的

具体而言，左边大小为K的部分，只需要向比i早而最晚出现的那个连边，因为其他已经出现的，都一定被这个覆盖；右边同理

这样边数是2n级别的，用线段树维护即可

时间复杂度为 nlogn

最后讲讲这个字典序的问题

我不知道为什么说p最小就是让A最小，这个貌似之前也碰到过，忘记是什么题目了，反正当时也没会证

但如果不是求A最小，直接求p最小我不知道怎么求……所以暂时当这个是对的吧

upd:
这并不是个一般性的结论，反例如2 3 1和3 1 2

我并不知道是这道题的转化有问题，还是有什么限制保证了这种情况不会发生

欢迎julao给出解释

那么A最小很容易，就是经典的最小字典序拓扑方案，直接搞个堆贪心即可，字典序这东西显然贪心是对的

```cpp
//Zory-2019
#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<map>
#include<set>
#include<queue>
#include<deque>
#include<stack>
#include<bitset>
#include<vector>
#include<algorithm>
#include<iostream>
#include<deque>
// #include<unordered_map>
using namespace std;
int bin[40],lg[1<<21];
namespace mine
{
	typedef long long ll;
	#define double long double
	const int INF=0x3f3f3f3f;
	const ll LLINF=0x3f3f3f3f3f3f3f3fll;
	ll qread()
	{
		ll ans=0;char c=getchar();int f=1;
		while(c<'0' or c>'9') {if(c=='-') f=-1;c=getchar();}
		while('0'<=c and c<='9') ans=ans*10+c-'0',c=getchar();
		return ans*f;
	}
	void write(ll num)
	{
		if(num<0) {num=-num;putchar('-');}
		if(num>9) write(num/10);
		putchar('0'+num%10);
	}
	void writeln(int num){write(num);puts("");}
	#define FR first
	#define SE second
	#define MP make_pair
	#define pr pair<int,int>
	#define PB push_back
	#define vc vector
	void chmax(int &x,const int y) {x=x>y?x:y;}
	void chmin(int &x,const int y) {x=x<y?x:y;}
	const int MAX_N=5e5+10;
	const int MOD=1e9+7;
	void add(int &x,int y) {x+=y;if(x>=MOD) x-=MOD;if(x<0) x+=MOD;}

	struct SegmentTree
	{
		#define lc 2*x
		#define rc 2*x+1
		#define mid ((l+r)>>1)
		pr mx[MAX_N*4];
		void change(int x,int l,int r,int p,int c)
		{
			mx[x]=max(mx[x],MP(c,p));
			if(l==r) return;
			if(p<=mid) change(lc,l,mid,p,c);
			else change(rc,mid+1,r,p,c);
		}
		pr ask(int x,int l,int r,int fl,int fr)
		{
			if(fl>fr) return MP(0,0);
			if(l==fl and r==fr) return mx[x];
			if(fr<=mid) return ask(lc,l,mid,fl,fr);
			if(fl>mid) return ask(rc,mid+1,r,fl,fr);
			return max(ask(lc,l,mid,fl,mid),ask(rc,mid+1,r,mid+1,fr));
		}
	}sgt;

	int a[MAX_N],ans[MAX_N];
	int ru[MAX_N];vector<int> to[MAX_N];
	void ins(int x,int y) {ru[y]++;to[x].PB(y);}
	priority_queue< int,vector<int>,greater<int> > q;
	void main()
	{
		int n=qread(),K=qread();
		for(int i=1;i<=n;i++) a[qread()]=i;
		for(int i=1;i<=n;i++)
		{
			int num=a[i];sgt.change(1,1,n,num,i);
			pr a=sgt.ask(1,1,n,max(1,num-K+1),num-1);if(a.FR>0) ins(a.SE,num);
			pr b=sgt.ask(1,1,n,num+1,min(num+K-1,n));if(b.FR>0) ins(b.SE,num);
		}
		for(int i=1;i<=n;i++) if(ru[i]==0) q.push(i);
		for(int now=1;now<=n;now++)
		{
			int x=q.top();q.pop();ans[x]=now;
			for(int t=0;t<(int)to[x].size();t++)
			{
				int y=to[x][t];ru[y]--;
				if(ru[y]==0) q.push(y);
			}
		}
		for(int i=1;i<=n;i++) writeln(ans[i]);
	}
};
int main()
{
	srand(time(0));
	bin[0]=1;for(int i=1;i<=30;i++) bin[i]=bin[i-1]<<1;
	lg[1]=0;for(int i=2;i<(1<<21);i++) lg[i]=lg[i>>1]+1;
	mine::main();
}


---

## 作者：wgyhm (赞：2)

大概是对 [**FrSmT**](https://www.luogu.com.cn/user/367687) 题解的补充说明。

## Description

给出一个元素集合为 $\{1,2,3,...,N\}$ 排列 $P$，当且仅当存在 $1\le i\le j\le N,j-i\ge K,|P_i-P_j|=1$ 时，可以交换 $P_i,P_j$。

求可能的排列中字典序最小的排列。

$1\le N\le 5\times 10^5$

## Solution

观察题目，当 $P_j-P_i=1$ 的时候，交换后字典序变小，逆序对减 $1$。

令 $Q_i$ 表示 $i$ 在 $P$ 中的位置，$Q_{p_i}=i$。

问题转化为 ：

* 当且仅当 $Q_i-Q_{i+1}\ge K$ 时交换 $Q_i,Q_{i+1}$。
* 重复上述操作，直到无法操作。
* 求 $Q$。

注意到 $K=1$ 时，就是排序。所以显然有一个 $O(n^2)$ 的冒泡排序算法。

考虑分治优化，类似于归并排序。$Q[l...mid]$ ，$Q[mid+1...r]$ 两个子序列都满足 $Q_i-Q_{i+1}<K$

现在只需要在可以接受的复杂度内合并两个序列即可。

考虑两个不相邻的 $Q_i,Q_j,i<j$ 如果可以让 $Q_j$ 到 $Q_i$ 的位置且使原序列更优，当且仅当 $\min _{l=i}^{j-1} Q_l\ge Q_j+K$ 

大概的意思如下（数字表示原来的下标） :

```
i i+1 i+2 i+3 ... j-1 j
```

因为 $Q_{j-1}-Q_j\ge K$ ，所以可以交换 $Q_{j-1},Q_j$。

然后新的 $Q_{j-2}-Q_{j-1}\ge K$ 。。。以此类推，变成：

```
j i i+1 i+2 ... j-2 j-1
```

 维护左区间的后缀最小值。如果满足上述条件，则把右区间的第一个元素加入队列，注意到左区间剩下的元素集体向右移了一位，所以 $\min _{l=i}^{j-1} Q_l$ 还是不变的。否则把左区间的第一个元素加入队列。

### Code

```cpp
#include<bits/stdc++.h>
#define rg register
#define ll long long 
#define maxn 500005
#define put() putchar('\n')
using namespace std;
inline void read(int &x){
    int f=1;x=0;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
    x*=f;
}
int n,K,a[maxn],g[maxn];
int t[maxn],Min[maxn];
inline void solve(int l,int r){
	if (l==r) return;
	int mid=l+r>>1,i,j,k;
	solve(l,mid);
	solve(mid+1,r);
	Min[mid]=a[mid];
	for (i=mid-1;i>=l;i--) Min[i]=min(Min[i+1],a[i]);
	i=l,j=mid+1,k=l-1;
	while (i<=mid&&j<=r) {
		if (Min[i]>=a[j]+K) t[++k]=a[j],j++;
		else t[++k]=a[i],i++;
	}
	while (i<=mid) t[++k]=a[i],i++;
	while (j<=r) t[++k]=a[j],j++;
	for (i=l;i<=r;i++) a[i]=t[i];
}
signed main(){
    rg int i;
    read(n);read(K);
    for (i=1;i<=n;i++) read(g[i]),a[g[i]]=i;
    solve(1,n);
    for (i=1;i<=n;i++) g[a[i]]=i;
    for (i=1;i<=n;i++) printf("%d\n",g[i]);
	return 0;
}
```



---

## 作者：do_while_true (赞：2)

转化成逆排列（下标和值互换），设其为 $Q$，那么操作就变成了如果 $|Q_i-Q_{i-1}|\geq k$，则可以交换 $Q_i,Q_{i-1}$，也就是对于任意的 $i<j,|Q_i-Q_j|<k$，$Q_i$ 始终要在 $Q_j$ 前面。

如果钦定了某些元素之间的相对顺序，那么任何满足这个相对顺序的序列都能通过不断交换两个相邻的元素互相得到。

假设要让 $A$ 变为 $B$，现将 $A$ 中的元素重标号为其在 $B$ 中的下标，如果其为 $1\sim n$ 的排列那么就得到 $B$ 了。当其不为 $1\sim n$ 时，一定存在相邻的逆序对，交换这个逆序对即可。如果不存在逆序对，说明交换得到了 $B$．由于我们每次交换的是逆序对，并且 $A$ 和 $B$ 的相对顺序限制相同，所以不会存在无法交换的情况。

现在假装得到了这些限制，想要使得原序列的字典序最小，就需要让逆排列的 $1$ 尽可能靠前，在此基础上 $2$ 尽可能靠前，然后是 $3$ 尽可能靠前......

如果只看这些限制，就是[菜肴制作](https://www.luogu.com.cn/problem/P3243)这道题了，将 DAG 的反图建出来之后，拓扑排序时每次选择编号最大的放在序列的最后。但这道题如果正着建图并且每次取编号最小的放在最前面也是对的，小粉兔在[这里](https://www.luogu.com.cn/blog/PinkRabbit/solution-at1984)给了证明我就不另画蛇添足什么了（

证明一下为什么建出 DAG 的反图然后每次选择编号最大的放在序列的最后是对的：

考虑如果不将最大的 $x$ 放在序列的最后，而是放了 $x'$，由于 $x$ 是没有往后移动的限制的，所以将 $x$ 移动到最后，这样本在 $x$ 后且 $<x$ 的编号都往前移动了一个位置（至少有一个 $x'$ 会往前移动一个位置），比原先更优，所以任何一种不是 $x$ 在最后的方案都能如此调整成一个更优的方案，所以 $x$ 一定在序列的最后。处理好 $x$ 之后，变成了一个子问题。得证。

实现上，可以用一个线段树维护原序列的区间还未出队的元素的最大值，来优化找 $0$ 度点的过程。

时间复杂度 $\mathcal{O}(n\log n)$．

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#define pb emplace_back
#define mp std::make_pair
#define fi first
#define se second
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
const ll mod = 998244353;
ll Add(ll x, ll y) { return (x+y>=mod) ? (x+y-mod) : (x+y); }
ll Mul(ll x, ll y) { return x * y % mod; }
ll Mod(ll x) { return x < 0 ? (x + mod) : (x >= mod ? (x-mod) : x); }
ll cadd(ll &x, ll y) { return x = (x+y>=mod) ? (x+y-mod) : (x+y); }
ll cmul(ll &x, ll y) { return x = x * y % mod; }
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template<typename T, typename... T2> T Max(T x, T2 ...y) { return Max(x, y...); }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template<typename T, typename... T2> T Min(T x, T2 ...y) { return Min(x, y...); }
template <typename T> T cmax(T &x, T y) { return x = x > y ? x : y; }
template <typename T> T cmin(T &x, T y) { return x = x < y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
template<typename T1, typename... T2>
void read(T1 &x, T2& ...y) { read(x); read(y...); }
const int N = 500100;
const int inf = 0x7fffffff;
int n, k, a[N], b[N], id[N], ct;
#define ls tree[x].lson
#define rs tree[x].rson
#define tl tree[x].l
#define tr tree[x].r
int trnt;
struct Node {
	int lson, rson, l, r, mx;
}tree[N << 1];
inline void pushup(int x) { tree[x].mx = Max(tree[ls].mx, tree[rs].mx); }
int build(int l, int r) {
	int x = ++trnt; tl = l; tr = r;
	if(l == r) {
		tree[x].mx = a[l];
		return x;
	}
	int mid = (l + r) >> 1;
	ls = build(l, mid); rs = build(mid+1, r);
	pushup(x);
	return x;
}
int qmax(int x, int l, int r) {
	if(tl >= l && tr <= r) return tree[x].mx;
	int mid = (tl + tr) >> 1, s = -inf;
	if(mid >= l) cmax(s, qmax(ls, l, r));
	if(mid < r) cmax(s, qmax(rs, l, r));
	pushup(x);
	return s;
}
void modify(int x, int p, int v) {
	if(tl == tr) {
		tree[x].mx = v;
		return ;
	}
	int mid = (tl + tr) >> 1;
	if(mid >= p) modify(ls, p, v);
	else modify(rs, p, v);
	pushup(x);
}
#undef ls
#undef rs
#undef tl
#undef tr
std::priority_queue<int>q;
bool check(int i) { return qmax(1, i-k+1, i+k-1) == a[i]; }
signed main() {
	read(n); read(k);
	for(int i = 1; i <= n; ++i) read(a[i]), id[a[i]] = i;
	build(1, n);
	for(int i = 1; i <= n; ++i)
		if(check(i))
			q.push(i);
	ct = n;
	while(!q.empty()) {
		int x = q.top(); q.pop();
		b[ct--] = x;
		modify(1, x, -inf);
		int t = 0;
		t = qmax(1, x-k+1, x);
		if(t != -inf && check(id[t]))
			q.push(id[t]);
		t = qmax(1, x, x+k-1);
		if(t != -inf && check(id[t]))
			q.push(id[t]);
	}
	for(int i = 1; i <= n; ++i) a[b[i]] = i;
	for(int i = 1; i <= n; ++i) printf("%d\n", a[i]);
	return 0;
}
```

---

## 作者：crashed (赞：2)

&emsp;&emsp;**去往[原博客](https://www.cnblogs.com/crashed/p/13539735.html)食用更佳。**

# 题目

&emsp;&emsp;[点这里](https://vjudge.net/problem/AtCoder-agc001_f)看题目。  

# 分析

&emsp;&emsp;题目的条件比较奇怪，因为我们交换的要求是：

1. 值 " 相邻 "。
2. 位置的差要 $\ge K$。

&emsp;&emsp;那么第一个条件就可以引导我们想到，我们应该构造出另一个序列 $A$ ，使得在 $A$ 上面交换相邻两个数，就等价于在 $P$ 上做交换。

&emsp;&emsp;不难想到定义： 
$$
A_i=\sum_{k=1}^nk[P_k=i]
$$
&emsp;&emsp;即 $A_i$ 为第 $i$ 个数在 $P$ 中出现的位置。

&emsp;&emsp;此时交换 $A$ 中相邻两个数，就 " 天然地 " 满足了第一个条件。第二个条件就意味着，相邻两个数的差的绝对值 $\ge K$。

&emsp;&emsp;另一方面，最小化 $P$ 的字典序也就意味着要最小化 $A$ 的字典序。

&emsp;&emsp;考虑第二个条件，实际上就意味着，**如果 $|A_i-A_j|< K$，那么 $A_i$ 和 $A_j$ 的相对位置不可能被改变**，但请注意，它的否命题并不成立。

&emsp;&emsp;利用一个常见的技巧：用有向边表示顺序，我们可以对 $|A_i-A_j|< K$ 且 $i<j$，连接一条 $A_i\rightarrow A_j$ 的有向边。考虑这个有向图的拓扑序，就一定满足第二个条件。因此我们现在就要求这个有向图的最小拓扑序。这可以用堆实现。

&emsp;&emsp;但是一不小心这个图就会有 $O(n^2)$ 条边。我们还需要考虑优化边数。

&emsp;&emsp;注意到一点：如果有 $i<j<k,A_i>A_j,A_i>A_k$ 且 $A_i-A_j<K,A_i-A_k<K$，那么必然有 $|A_j-A_k|<K$。这说明我们只需要连接边 $A_i\rightarrow A_j$，而不需要再连接 $A_i\rightarrow A_k$。当 $A_i<A_j,A_i<A_k$ 的时候同理。

&emsp;&emsp;因此我们只需要找到最小的 $j$ 满足 $A_i>A_j$ 和最小的 $k$ 满足 $A_i<A_k$，并连接 $A_i\rightarrow A_j,A_i\rightarrow A_k$ 即可。边数就是 $O(n)$ 的。这个过程可以用权值线段树优化一下。

&emsp;&emsp;时间是 $O(n\log_2n)$。

# 代码

&emsp;&emsp;[ AC 记录](https://vjudge.net/solution/26934733)。

```cpp
#include <queue>
#include <cstdio>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 5e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

struct edge
{
	int to, nxt;
}Graph[MAXN << 1];

priority_queue<int, vector<int>, greater<int> > q;

int mn[MAXN << 2];

int seq[MAXN], ans[MAXN];
int A[MAXN], P[MAXN], head[MAXN], deg[MAXN];
int N, K, cnt;

void addEdge( const int from, const int to )
{
	Graph[++ cnt].to = to, Graph[cnt].nxt = head[from];
	head[from] = cnt, deg[to] ++;
}

void upt( const int x ) { mn[x] = MIN( mn[x << 1], mn[x << 1 | 1] ); }

void build( const int x, const int l, const int r )
{
	if( l > r ) return ; mn[x] = INF;
	if( l == r ) return ;
	int mid = l + r >> 1;
	build( x << 1, l, mid );
	build( x << 1 | 1, mid + 1, r );
}

void update( const int x, const int l, const int r, const int p, const int v )
{
	if( l == r ) { mn[x] = v; return ; }
	int mid = l + r >> 1;
	if( p <= mid ) update( x << 1, l, mid, p, v );
	else update( x << 1 | 1, mid + 1, r, p, v );
	upt( x );
}

int query( const int x, const int l, const int r, const int segL, const int segR )
{
	if( segL <= l && r <= segR ) return mn[x];
	int mid = l + r >> 1, ret = INF;
	if( segL <= mid ) ret = MIN( ret, query( x << 1, l, mid, segL, segR ) );
	if( mid < segR ) ret = MIN( ret, query( x << 1 | 1, mid + 1, r, segL, segR ) );
	return ret;
}

int query( const int l, const int r ) { return query( 1, 1, N, MAX( 1, l ), MIN( N, r ) ); }

int main()
{
	read( N ), read( K );
	for( int i = 1 ; i <= N ; i ++ ) read( P[i] ), A[P[i]] = i;
	build( 1, 1, N );
	for( int i = N ; i ; i -- )
	{
		int pre = query( A[i] - K + 1, A[i] ),
			nxt = query( A[i], A[i] + K - 1 );
		if( pre < INF ) addEdge( A[i], A[pre] );
		if( nxt < INF ) addEdge( A[i], A[nxt] );  
		update( 1, 1, N, A[i], i );
	}
	for( int i = 1 ; i <= N ; i ++ )
		if( ! deg[i] ) q.push( i );
	int u, v, tot = 0;
	while( ! q.empty() )
	{
		u = seq[++ tot] = q.top(), q.pop();
		for( int i = head[u] ; i ; i = Graph[i].nxt )
			if( ! ( -- deg[v = Graph[i].to] ) )
				q.push( v );
	}
	for( int i = 1 ; i <= N ; i ++ ) ans[seq[i]] = i;
	for( int i = 1 ; i <= N ; i ++ ) write( ans[i] ), putchar( '\n' );
	return 0;
}
```

---

## 作者：Kinandra (赞：2)

标签: 转化, 贪心, 线段树, 拓扑排序.

~~题目编号是个很厉害的数字啊~~

定义一个数组 $Q$, 使得 $Q_{P_i}=i$, 即把每一个数字的位置记录在 $Q$ 内, 因为前面的**权值尽量小**等价于**权值小的尽量前**, 所以 $P$ 字典序最小等价于 $Q$ 字典序最小, 只需要考虑求字典序最小的 $Q$ 就好了.

$Q$ 的交换规则是权值差$\geqslant k$的相邻元素可以换顺序, 容易发现若 $abs(Q_i-Q_j) < k$, $Q_i, Q_j$ 的**相对顺序**不会改变, 我们暴力地将这类 $Q_i, Q_j$ 连边, 可以得到一张拓扑图,  用堆来贪心的跑字典序最小的拓扑序就好了.

但是我们注意到上述方法边数是 $\mathcal O(n^2)$ 的, 需要进行优化. 观察发现暴力方法会有很多无用边. 例如三条有向边$(i,j), (j,k),(i,k)$中这条 $(i,k)$ 是无用的.

考虑从后往前遍历 $Q$ , $Q_i$ **连向的数**必然属于 $(Q_i-K, Q_i)\cup(Q_i,Q_i+K)$, 发现 $(Q_i-K, Q_i)$ 内所有元素已经确定了相对顺序, $(Q_i,Q_i+K)$ 也是, 所以我们只需要将 $Q_i$ 分别向两个区间内下标最小的元素连边就行了. 区间内下标最小的元素可以用线段树来维护.

时间复杂度 $\mathcal O(n\log n)$, 空间复杂度 $O(n)$.


---

## 作者：Autre (赞：1)

首先考虑 $P$ 的逆 $p$，将问题转化为每次交换差的绝对值大于等于 $K$ 的相邻位置，使得逆的字典序最小。

---

我们先证明引理：能将一个初始排列 $p$ 经过任意次操作之后变为目标排列 $p'$，当且仅当在两个排列中，所有差的绝对值小于 $K$ 的数对，相对位置都不变。

证明很简单，考虑排列 $\sigma$ 满足 $p=\sigma(p')$。如果每次交换 $\sigma$ 的一对相邻位置，利用归纳易证，存在一种恰好将 $\sigma$ 中的每个逆序对恰交换一次的方案，将 $\sigma$ 排序。由于任意一对差的绝对值小于 $K$ 的数对在 $p,p'$ 中的相对位置相同，换言之，对应在 $\sigma$ 中不为逆序对，那么将这个方案应用到排列 $p$ 上一定合法。

---

我们有一个平凡的调整策略：找到 $i\in[1,n)$ 使得 $p_i\ge p_{i+1}+K$，交换 $p_i,p_{i+1}$。显然经过一次交换之后一定会变得更优。我们证明在经过任意次原题中的操作能得到的所有排列中，不能再进行上述调整的排列是唯一的。

考虑两个能够通过原题中的操作互相变换的排列 $p\not=q$，其中 $i$ 是两者最靠前的不相等的位置，且 $p_i<q_i$，设 $q_j=p_i$（显然 $j>i$）。

因为 $q_{[i,j)}$ 中的每个数在 $q$ 中均在 $q_j$ 前，而在 $p$ 中均在 $p_i$ 后，所以在将 $q$ 变换为 $p$ 的过程中，他们至少要与 $q_j$ 发生一次交换，于是 $q_{[i,j)}$ 中的每个数与 $q_j$ 差的绝对值都大于等于 $K$。

设 $q$ 不能进行贪心的调整。这意味着 $q_{j-1}\le q_j-K$（否则 $j-1,j$ 可调整），且不存在 $k\in(i,j)$ 使得 $q_k\le q_j-K,q_{k-1}\ge q_j+K$（否则 $q_k-q_{k-1}\ge 2K>K$，$k-1,k$ 可调整）。于是 $q_i\le q_j-K<q_j=p_i$，与假设矛盾。

取可以由输入排列变换得到的任意两个排列，字典序较大的总是可以调整变得更优，所以可以由输入排列变换得到的所有排列中，字典序最小的就是答案。这里只是从另一个方面说明了小粉兔题解中这个题的性质，字典序最优的排列，逆的字典序也最优，其实我们只需要用到极值的唯一性，以说明贪心调整的正确性。

---

不难发现这个调整策略类似冒泡排序，将其优化为归并排序即可。这里的道理是，归并排序可以看做冒泡排序的不依赖序性质的直接优化，归并的过程可以看做将一个元素的若干次冒泡合并为一次。

---

## 作者：yijan (赞：1)

首先考虑求出原排列的逆置换，设为 $Q$ ，于是交换就变成了如果 $|Q_i - Q_{i+1}| < k$ 那么可以交换相邻的两个元素。

于是，对于任意 $i,j$ 如果满足 $|Q_i - Q_j| < k$ 那么他们的相对顺序一定无法改变。

而且可以证明，如果两个排列 $Q,P$ 中所有元素的相对位置的关系是一样的，那么一定可以从 $Q$ 移到 $P$ 。考虑这种情况下的一次移动就可以让逆序减少 $1$ 。有限步的操作后一定可以让 $Q$ 成为 $P$ （画一下发现很对）。

于是有了一种做法，对于 $i<j$ 满足 $|Q_i - Q_j| < k$ 我们连一条 $Q_i \to Q_j$ 的有向边表示先 $Q_i$ 后 $Q_j$ ，于是我们要求的就是这个图上的一个拓扑序，满足 $1$ 尽量靠前，在 $1$ 尽量靠前的情况下 $2$ 尽量靠前... 不难发现这样的限制等价于原排列字典序尽量小。这个限制与字典序是没有关系的。比如 $3 \to 1 , 2 \to 4$ 在这个限制下应该拿 $3,1,2,4$ 但是字典序最小的应当是 $2,3,1,4$ 。

求这个拓扑序的方法可以参照 [LOJ2114](https://loj.ac/problem/2114) 这个题。我们每次拿可以放在最后的最大的数放在最后一定不劣。所以我们可以建反图再跑拓扑序，最后把拓扑序倒过来就得到了所求。

现在问题在于这样的边有 $O(n^2)$ 条。优化方法大致有两种。首先可以不建边，直接在线段树上判断一个点的出度来做拓扑排序，这是官方题解的做法。大概还有一个做法是优化边的数量。

考虑我们当前已经通过加边让 $1 \sim i - 1$ 的点对间都满足了之前提到的限制。现在我们加入 $Q_i$ 。我们只给满足 $0< Q_j - Q_i < k$ 以及 $0 < Q_i - Q_j < k$ 且大的两个 $j$ 与 $Q_i$ 连边。由于上下是对称的，我们只考虑 $Q_j > Q_i$ 的情况。因为之前 $1 \sim i - 1$ 中与 $i$ 满足 $Q_t -Q_i < k$ 的位置 与 $Q_j$ 的相对顺序已经是确定好的，并且一定是 $Q_j$ 处于最靠后，所以直接拿 $Q_j$ 向 $Q_i$ 连边即可满足所有的限制。这样连边最多也就连 $2n$ 条，边数变成了 $O(n)$ 级别。连边过程用线段树维护，总复杂度是连边的 $O(n\log n)$。

最后别忘了要还原成原排列。。~~这毒瘤样例全部不还原都能过~~

```cpp

int n , k;
int A[MAXN] , Q[MAXN];

int T[MAXN << 2];
void add( int rt , int l , int r , int x , int c ) {
	if( l == r ) { T[rt] = c; return; }
	int m = l + r >> 1;
	if( x <= m ) add( rt << 1 , l , m , x , c );
	else add( rt << 1 | 1 , m + 1 , r , x , c );
	T[rt] = max( T[rt << 1] , T[rt << 1 | 1] );
}
int que( int rt , int l , int r , int L , int R ) {
	if( L <= l && R >= r ) return T[rt];
	int m = l + r >> 1 , re = 0;
	if( L <= m ) re = max( re , que( rt << 1 , l , m , L , R ) );
	if( R > m ) re = max( re , que( rt << 1 | 1 , m + 1 , r , L , R ) );
	return re;
}

vi G[MAXN];
int deg[MAXN] , as[MAXN];

void solve() {
	cin >> n >> k;
	rep( i , 1 , n ) scanf("%d",A + i) , Q[A[i]] = i;
	rep( i , 1 , n ) {
		int t = que( 1 , 1 , n , Q[i] , min( Q[i] + k - 1 , n ) );
		if( t ) G[Q[i]].pb( Q[t] ) , ++ deg[Q[t]];// , cout << Q[i] << ' ' << Q[t] << endl;
		t = que( 1 , 1 , n , max( 1 , Q[i] - k + 1 ) , Q[i] );
		if( t ) G[Q[i]].pb( Q[t] ) , ++ deg[Q[t]];// , cout << Q[i] << ' ' << Q[t] << endl;
		add( 1 , 1 , n , Q[i] , i );
	}
	priority_queue<int> q;
	rep( i , 1 , n ) if( !deg[i] ) q.push( i );
	vi re;
	while( !q.empty() ) {
		int u = q.top(); q.pop();
		for( int v : G[u] ) {
			-- deg[v];
			if( !deg[v] ) q.push( v );
		}
		re.pb( u );
	}
	reverse( all( re ) );
	rep( i , 1 , n ) as[re[i - 1]] = i;
	rep( i , 1 , n ) printf("%d\n",as[i]);
}

signed main() {
//	freopen("input","r",stdin);
//	freopen("stdout","w",stdout);
//    int T;cin >> T;while( T-- ) solve();
    solve();
}
```



---

## 作者：foreverlasting (赞：1)

![](https://images2018.cnblogs.com/blog/1109445/201711/1109445-20171125163542203-35591385.png)
![](https://images2018.cnblogs.com/blog/1109445/201711/1109445-20171125163601937-349290803.png)

拓扑排序+线段树。

~~为什么这道会是黑题啊~~

首先考虑调换权值与下标的位置，那么就可以把题目转换成：

相邻元素且权值差$>=k$的可以换顺序，让前面的权值尽量小的序列。

这好像是一个明显的拓扑排序。

从位置$i$向后面的位置$j$比较，如果$abs(a[i]-a[j])<k$，那么$i$和$j$的最终位置关系就确定了，于是从$a[i]$向$a[j]$连边就行了。

然而这样的话，边的数量会达到$O(n^2)$，所以需要优化。

因为要求的是前面的权值尽量小，所以应当连向的是最小的边。所以从$a[i]$向$(a[i]+1,a[i]+k-1)$的最小值连边就好了。如果选择的是从前往后，显然这样连边是有重复的。所以从后往前，不仅向后面连边，再向前面$(a[i]-k+1,a[i]-1)$的最小值连边就好了。

注意拓扑的时候用一下小根堆就行了。

code:
```
//2018.9.21 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int N=1e6+10;
namespace MAIN{
    int a[N],n,k;
    namespace Segtree{
        int mn[N<<2];
        inline void pushup(const res &rt){
            mn[rt]=_min(mn[rt<<1],mn[rt<<1|1]);
        }
        void build(const res &rt,const res &l,const res &r){
            mn[rt]=inf;
            if(l==r)return;
            res mid=(l+r)>>1;
            build(rt<<1,l,mid),build(rt<<1|1,mid+1,r);
        }
        void update(const res &rt,const res &l,const res &r,const res &p,const res &va){
            if(l==r){mn[rt]=va;return;}
            res mid=(l+r)>>1;
            if(p<=mid)update(rt<<1,l,mid,p,va);
            else update(rt<<1|1,mid+1,r,p,va);
            pushup(rt);
        }
        int query(const res &rt,const res &l,const res &r,const res &L,const res &R){
            if(L>R)return 0;
            if(L<=l&&r<=R)return mn[rt];
            res mid=(l+r)>>1,ans=inf;
            if(L<=mid)ans=_min(ans,query(rt<<1,l,mid,L,R));
            if(R>mid)ans=_min(ans,query(rt<<1|1,mid+1,r,L,R));
            return ans;
        }
    }
    struct E{
        int next,to;
        E() {}
        E(res next,res to):next(next),to(to) {}
    }edge[N];
    int head[N],cnt,du[N];
    inline void addedge(const res &u,const res &v){
        edge[++cnt]=E(head[u],v),head[u]=cnt,du[v]++;
    }
    int x;
    priority_queue<int,vector<int>,greater<int> >Q;
    int id[N],idx;
    inline void topsort(){
        for(res i=1;i<=n;i++)if(!du[i])Q.push(i);
        while(!Q.empty()){
            res u=Q.top();
            Q.pop();
            id[u]=++idx;
            for(res i=head[u];~i;i=edge[i].next){
                res tox=edge[i].to;
                if(--du[tox]==0)Q.push(tox);
            }
        }
    }
    inline void MAIN(){
        memset(head,-1,sizeof(head));
        n=read(),k=read();
        for(res i=1;i<=n;i++)a[read()]=i;
        Segtree::build(1,1,n);
        for(res i=n;i;i--){
            x=Segtree::query(1,1,n,a[i]+1,_min(a[i]+k-1,n));
            if(x>=1&&x<=n)addedge(a[i],a[x]);
            x=Segtree::query(1,1,n,_max(1,a[i]-k+1),a[i]-1);
            if(x>=1&&x<=n)addedge(a[i],a[x]);
            Segtree::update(1,1,n,a[i],i);
        }
        topsort();
        for(res i=1;i<=n;i++)printf("%d\n",id[i]);
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

