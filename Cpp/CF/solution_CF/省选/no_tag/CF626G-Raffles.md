# Raffles

## 题目描述

Johnny is at a carnival which has $ n $ raffles. Raffle $ i $ has a prize with value $ p_{i} $ . Each participant can put tickets in whichever raffles they choose (they may have more than one ticket in a single raffle). At the end of the carnival, one ticket is selected at random from each raffle, and the owner of the ticket wins the associated prize. A single person can win multiple prizes from different raffles.

However, county rules prevent any one participant from owning more than half the tickets in a single raffle, i.e. putting more tickets in the raffle than all the other participants combined. To help combat this (and possibly win some prizes), the organizers started by placing a single ticket in each raffle, which they will never remove.

Johnny bought $ t $ tickets and is wondering where to place them. Currently, there are a total of $ l_{i} $ tickets in the $ i $ -th raffle. He watches as other participants place tickets and modify their decisions and, at every moment in time, wants to know how much he can possibly earn. Find the maximum possible expected value of Johnny's winnings at each moment if he distributes his tickets optimally. Johnny may redistribute all of his tickets arbitrarily between each update, but he may not place more than $ t $ tickets total or have more tickets in a single raffle than all other participants combined.

## 说明/提示

In the first case, Johnny only has one ticket to distribute. The prizes are worth $ 4 $ and $ 5 $ , and the raffles initially have $ 1 $ and $ 2 $ tickets, respectively. After the first update, each raffle has $ 2 $ tickets, so Johnny has expected value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF626G/6b3899b68ddbbb0f7be3fe6b0138da4ad0a78d00.png) of winning by placing his ticket into the second raffle. The second update adds a ticket to the second raffle, so Johnny can win ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF626G/02a9893655e2526bd8576bc654e9f03be42e84e3.png) in the first raffle. After the final update, Johnny keeps his ticket in the first raffle and wins ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF626G/382e96367d194a03ee920b4d0883f816643d58ba.png).

In the second case, Johnny has more tickets than he is allowed to spend. In particular, after the first update, there are $ 7 $ , $ 6 $ , and $ 6 $ tickets in each raffle, respectively, so Johnny can only put in $ 19 $ tickets, winning each prize with probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF626G/fda96725ccc697b767e5edbf0d5cfb5ba17d9aa2.png). Also, note that after the last two updates, Johnny must remove a ticket from the last raffle in order to stay under ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF626G/fda96725ccc697b767e5edbf0d5cfb5ba17d9aa2.png) the tickets in the third raffle.

## 样例 #1

### 输入

```
2 1 3
4 5
1 2
1 1
1 2
2 1
```

### 输出

```
1.666666667
1.333333333
2.000000000
```

## 样例 #2

### 输入

```
3 20 5
6 8 10
6 6 6
1 1
1 2
1 3
2 3
2 3
```

### 输出

```
12.000000000
12.000000000
11.769230769
12.000000000
12.000000000
```

# 题解

## 作者：xht (赞：21)

> [CF626G Raffles](https://codeforces.com/contest/626/problem/G)

## 题意

- 有 $n$ 个奖池，第 $i$ 个奖池的奖金是 $p_i$，已经有 $l_i$ 张彩票押在上面。
- 现在你有 $t$ 张彩票，你需要将你的彩票分配到这些奖池中，并且保证你在每个奖池中押的彩票数**不能超过该奖池原有的彩票数**。
- 若你在第 $i$ 个奖池中押了 $t_i$ 张彩票，则你中奖的概率为 $\frac{t_i}{t_i + l_i}$，若你中奖，你可以获得这个奖池的全部奖金 $p_i$。
- 一共有 $q$ 次事件，每次事件会使某个 $l_i$ 加 $1$ 或减 $1$。
- 你需要在每个事件后求出在最佳方案下你获得的奖金总数的最大期望值。
- $n,t,q \le 2 \times 10^5$，$p_i,l_i \le 10^3$，答案精度误差 $\le 10^{-6}$。

## 题解

首先考虑没有修改时如何计算。

假设此时对于奖池 $i$，你已经押了 $c_i$ 张彩票上去了，若 $c_i + 1 \le l_i$，则你此时还可以再押一张彩票上去，它对答案的贡献为

$$
p_i(\frac{c_i+1}{c_i+1+l_i} - \frac{c_i}{c_i+l_i}) = \frac{p_il_i}{(c_i+1+l_i)(c_i+l_i)}
$$

注意到这个贡献随着 $c_i$ 的增大会不断变小，因此我们可以得到一个贪心做法：

开一个堆存储对于每个奖池再押一张彩票的贡献，每次取出最大的贡献计入答案，然后加入其对应奖池的新的贡献。

时间复杂度为 $\mathcal O((n + t) \log n)$。

再考虑有修改的情况下如何维护。

当我们修改 $l_i$ 时，第 $i$ 个奖池的贡献会改变，因此当前方案可能就不是最优的了。

一个简单的想法是，如果当前的方案不是最优的方案，那么就不断找回当前方案中贡献最小的彩票，换成贡献更大的彩票。

可以发现，这个看似暴力的做法时间复杂度却是对的，因为每次修改实质上只会最多引起一张彩票的变化。

具体实现上，我们只需要把堆换成 multiset，同时维护当前方案即可。

总时间复杂度 $\mathcal O((n + t + q) \log n)$。

## 代码

```cpp
const int N = 2e5 + 7;
const ld inf = 1e18L, eps = 1e-10L;
int n, t, q, p[N], l[N], c[N];
ld ans;

inline ld f(int x, int c) {
	if (!~c) return inf;
	if (c >= l[x]) return 0L;
	return 1.0L * p[x] * l[x] / (c + 1 + l[x]) / (c + l[x]);
}

inline ld g(int x) {
	return 1.0L * p[x] * min(c[x], l[x]) / (min(c[x], l[x]) + l[x]);
}

struct P {
	ld o;
	int x, c;
	inline P(int x = 0, int c = -1) : x(x), c(c) { o = f(x, c); }
	inline bool operator < (const P w) const {
		return abs(o - w.o) > eps ? o < w.o : x < w.x;
	}
};
multiset<P> s, e;

inline void add() {
	auto it = --s.end();
	ans += it -> o;
	int x = it -> x;
	e.erase(P(x, c[x] - 1)), e.insert(*it);
	s.erase(it), s.insert(P(x, ++c[x]));
}

inline void rmv() {
	auto it = e.begin();
	ans -= it -> o;
	int x = it -> x;
	s.erase(P(x, c[x])), s.insert(*it);
	e.erase(it), e.insert(P(x, (--c[x]) - 1));
}

int main() {
	rd(n), rd(t), rd(q);
	for (int i = 1; i <= n; i++) rd(p[i]);
	for (int i = 1; i <= n; i++) rd(l[i]), s.insert(P(i, 0)), e.insert(P(i));
	while (t--) add();
	for (int i = 1, o, x; i <= q; i++) {
		rd(o), rd(x);
		s.erase(P(x, c[x])), e.erase(P(x, c[x] - 1)), ans -= g(x);
		l[x] += o == 1 ? 1 : -1;
		s.insert(P(x, c[x])), e.insert(P(x, c[x] - 1)), ans += g(x);
		while ((--s.end()) -> o > (e.begin() -> o) + eps) rmv(), add();
		printf("%.10Lf\n", ans);
	}
	return 0;
}
```

---

## 作者：justin_cao (赞：7)

首先考虑对于一种彩票$i$，押一张所增加的期望是多少。假设已经押了$x$张了，现在要押$x+1$张，那么增加的期望奖金就会是：
$$
\frac{(x+1)\times p_i}{x+l_i+1}-\frac{x\times p_i}{x+l_i}=\frac{l_i\times p_i}{(x+l_i)(x+l_i+1)}
$$
发现这个东西是关于$x$的减函数，那么就有了一个不带修改的做法：

维护一个优先队列，每次取出一种增加的期望最大的彩票，然后加进答案之后再放回去，同时更新这种彩票增加的期望。

由于是减函数，所以正确性有保证。

但是带上修改怎么办呢？

考虑修改对求答案过程的影响。假设现在将没有修改的操作全部进行完了，**首先将当前修改对答案的影响先算上，那么这个可能不是最优的解，要考虑调整**。那么调整实际上就是从后到前来撤销，就是删去一个加进答案的最小的期望，然后加上未加进答案的最大的期望，如果这两个操作结束之后最终能使答案增加就操作，否则不操作，那么这种操作进行到不能再进行了之后最终得到的答案肯定是最大的。

那么这个就可以用线段树来维护了，用线段树维护最小的删去的期望和最大的加入的期望，每次只需要修改这两个点即可。（但是首先需要将当前修改对答案的影响算上的）。

这样就可以维护了，由于每次修改因为只有加一和减一，所以实际上最多只会引起一张彩票的变化。

于是总的时间复杂度就会是$O((n+t+q)\log n)$。

code：
```cpp
#include<bits/stdc++.h>
#define maxn 200010
using namespace std;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const double inf=1e9;
int n,T,Q;
int p[maxn],q[maxn],cnt[maxn];
double calc(int x,int id)
{
    return (double)(p[id]*q[id])/(double)(x+q[id])/(double)(x+q[id]-1);
}
double calcx(int x,int id)
{
    return (double)(x*p[id])/(x+q[id]);
}
double ans;
struct Segment_Tree{
    double mx[maxn*4],mn[maxn*4];
    void update(int k)
    {
        mx[k]=max(mx[k*2],mx[k*2+1]);
        mn[k]=min(mn[k*2],mn[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            cnt[l]=0;
            mx[k]=calc(1,l);
            mn[k]=inf;
            return;
        }
        int mid=((l+r)>>1);
        build(k*2,l,mid);
        build(k*2+1,mid+1,r);
        update(k);
    }
    void add(int k,int l,int r)
    {
        if(l==r)
        {
            if(mx[k]!=-inf)   ans+=mx[k];
            cnt[l]++;
            if(cnt[l]>q[l])   mn[k]=-inf;
            else              mn[k]=calc(cnt[l],l);
            if(cnt[l]>=q[l])  mx[k]=-inf;
            else              mx[k]=calc(cnt[l]+1,l);
            return;
        }
        int mid=(l+r)/2;
        if(mx[k*2]>mx[k*2+1])  add(k*2,l,mid);
        else                   add(k*2+1,mid+1,r);
        update(k);
    }
    void del(int k,int l,int r)
    {
        if(l==r)
        {
            if(mn[k]!=-inf)   ans-=mn[k];
            cnt[l]--;
            if(cnt[l]>q[l])   mn[k]=-inf;
            else if(!cnt[l])  mn[k]=inf;
            else              mn[k]=calc(cnt[l],l);
            if(cnt[l]>=q[l])  mx[k]=-inf;
            else              mx[k]=calc(cnt[l]+1,l);
            return;
        }
        int mid=(l+r)/2;
        if(mn[k*2]<mn[k*2+1])  del(k*2,l,mid);
        else                   del(k*2+1,mid+1,r);
        update(k);
    }
    void upgrade(int k,int l,int r,int x,int y)
    {
        if(l==r)
        {
            ans-=calcx(min(cnt[l],q[l]),l);
            q[l]+=y;
            ans+=calcx(min(cnt[l],q[l]),l);
            if(cnt[l]==0)         mn[k]=inf;
            else if(cnt[l]>q[l])  mn[k]=-inf;
            else                  mn[k]=calc(cnt[l],l);
            if(cnt[l]>=q[l])      mx[k]=-inf;
            else                  mx[k]=calc(cnt[l]+1,l);
            return;
        }
        int mid=(l+r)/2;
        if(mid>=x)  upgrade(k*2,l,mid,x,y);
        else        upgrade(k*2+1,mid+1,r,x,y);
        update(k);
    }
}S;
int main()
{
    n=read();T=read();Q=read();
    for(int i=1;i<=n;i++)  p[i]=read();
    for(int i=1;i<=n;i++)  q[i]=read();
    S.build(1,1,n);
    for(int i=1;i<=T;i++)  S.add(1,1,n);
    while(Q--)
    {
        int op=read(),x=read();
        if(op==1)  S.upgrade(1,1,n,x,1);
        if(op==2)  S.upgrade(1,1,n,x,-1);
        while(S.mn[1]<S.mx[1])
        {
            S.add(1,1,n);
            S.del(1,1,n);
        }
        printf("%.9lf\n",ans);
    }
    return 0;
}   
```

---

## 作者：tzc_wk (赞：3)

安利个人 blog：https://www.cnblogs.com/ET2006/

[题面传送门](https://codeforces.ml/contest/626/problem/G)

考虑对于固定的彩票池 $i$，我们假设现在押了 $x$ 张彩票。利用差分的思想，从 $x$ 张彩票变为 $x+1$ 张时，期望的变化量 $\Delta E=\dfrac{p_i(x+1)}{l_i+x+1}-\dfrac{p_ix}{l_i+x}=\dfrac{p_il_i}{(l_i+x+1)(l_i+x)}$。容易发现该函数为关于 $x$ 的减函数，所以考虑直接贪心的做法：建一个堆 $st$，维护所有彩票池由当前彩票数量变为当前彩票数量 $+1$，期望的变化量，贪心 $t$ 轮每次贪心地取出堆中最大的元素就行了。

接下来考虑有修改的情况：首先我们假设对于修改的元素 $x$，$x$ 彩票池押的彩票个数不变，也就是说我们重新计算一遍 $x$ 彩票池押中的彩票价值的期望值。显然这样不一定是最优的，于是我们考虑再建一个堆 $st_2$ 维护已经押入彩票池的彩票的价值，每次贪心地取出 $st_2$ 中最小的元素并加入 $st$ 中最大的元素（类似于反悔贪心），直到不能再操作为止即可。

由于每次操作只有加一和减一，所以最多只会引起一张彩票的变化，故复杂度是正确的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=2e5;
const double EPS=1e-10;
const double INF=1e18;
const int MAGIC=15;
int n,t,qu,p[MAXN+5],l[MAXN+5],c[MAXN+5];
double dif(int x,int c){
	if(!c) return INF;if(c>l[x]) return 0;
	return 1.0*p[x]*l[x]/(c+l[x])/(c-1+l[x]);
}
struct node{
	double val;int x,y;
	node(int _x=0,int _y=0){val=dif(_x,_y);x=_x;y=_y;}
	bool operator <(const node &rhs) const{
		return (fabs(val-rhs.val)>EPS)?(val<rhs.val):(x<rhs.x);
	}
};
double ans=0;
set<node> nw,cur;
void ins(){
	node t=*nw.rbegin();int x=t.x;//assert(fabs(t.val-dif(x,c[x]+1))<EPS);
	nw.erase(nw.find(node(x,c[x]+1)));cur.erase(cur.find(node(x,c[x])));
	ans+=t.val;c[x]++;
	nw.insert(node(x,c[x]+1));cur.insert(node(x,c[x]));
}
void del(){
	node t=*cur.begin();int x=t.x;//assert(fabs(t.val-dif(x,c[x]))<EPS);
	nw.erase(nw.find(node(x,c[x]+1)));cur.erase(cur.find(node(x,c[x])));
	ans-=t.val;c[x]--;
	nw.insert(node(x,c[x]+1));cur.insert(node(x,c[x]));
}
int main(){
	scanf("%d%d%d",&n,&t,&qu);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	for(int i=1;i<=n;i++) scanf("%d",&l[i]);
	for(int i=1;i<=n;i++) nw.insert(node(i,c[i]+1)),cur.insert(node(i,c[i]));
	for(int i=1;i<=t;i++) ins();
	while(qu--){
		int opt,x;scanf("%d%d",&opt,&x);
//		assert(cur.find(node(x,c[x]))!=cur.end());
		nw.erase(nw.find(node(x,c[x]+1)));cur.erase(cur.find(node(x,c[x])));
		ans-=1.0*p[x]*min(c[x],l[x])/(l[x]+min(c[x],l[x]));
		l[x]+=((opt==1)?(1):(-1));
		nw.insert(node(x,c[x]+1));cur.insert(node(x,c[x]));
		ans+=1.0*p[x]*min(c[x],l[x])/(l[x]+min(c[x],l[x]));
		for(int i=1;i<=MAGIC;i++) del(),ins();
		printf("%.15lf\n",ans);
	}
	return 0;
}
```



---

## 作者：关怀他人 (赞：1)

### CF 626G
#### Solution
不难发现在同一个奖池内押彩票的贡献是递减的，如果没有修改，那么有一个非常显然的做法：拿一个堆维护每一个奖池中新增一张彩票对答案的贡献，每次取出期望收益最大的彩票即可。

考虑修改操作，如果将$l_i$减小$1$，那么押在第$i$个奖池的彩票数目可能不变，可能减小$1$（因为原来放了$l_i$张），或者是增加若干张，不难发现最多只会增加$1$张。

证明：假设原来押在第$i$个奖池上的彩票有$c$张，现在若押了$c+1$张以上，那么第$c+2$张一定替换了押在其他奖池的彩票，设被替换掉的彩票的贡献为$w$，由于原来放第$c+1$张是不优的，所以$p_i(\dfrac{c+1}{c+1+l_i}-\dfrac{c}{c+l_i})\leq w$，因此有$p_i(\dfrac{c+2}{c+2+l_i}-\dfrac{c+1}{c+1+l_i})\leq p_i(\dfrac{c+1}{c+1+l_i}-\dfrac{c}{c+l_i})\leq w$，所以替换后答案会变差，故最多只会增加一张彩票。

对于将$l_i$加$1$的情况同理，于是可以得出每次修改后最多变化$1$张彩票，拿线段树维护押哪一张获得的最大贡献和之前押的彩票中贡献最小的一个，每次修改只需要在线段树上更新这两个点即可。

时间复杂度$\mathcal O(n\log n)$
#### Code
```cpp
int n,t,Q;
int a[MAXN],num[MAXN];
double p[MAXN];

struct SegmentTree{
    struct Tree{
        int l,r;
        int minid,maxid;
        double ans,min,max;
    } tree[MAXN << 2];

    #define lson k << 1
    #define rson k << 1 | 1

    void update(int k){
        tree[k].ans = tree[lson].ans + tree[rson].ans;
        if(tree[lson].max > tree[rson].max) tree[k].max = tree[lson].max, tree[k].maxid = tree[lson].maxid;
        else tree[k].max = tree[rson].max, tree[k].maxid = tree[rson].maxid;
        if(tree[lson].min < tree[rson].min) tree[k].min = tree[lson].min, tree[k].minid = tree[lson].minid;
        else tree[k].min = tree[rson].min, tree[k].minid = tree[rson].minid;
    }

    void calc(int k,int i){
        tree[k].ans = min(p[i] * num[i] / (1.0 * (num[i] + a[i])),p[i] / 2.0);
        if(num[i] >= a[i]) tree[k].max = 0;
        else tree[k].max = p[i] * (num[i] + 1) / (1.0 * (num[i] + a[i] + 1)) - p[i] * num[i] / (1.0 * (num[i] + a[i]));
        if(num[i] == 0) tree[k].min = INF;
        else if(num[i] > a[i]) tree[k].min = 0;
        else tree[k].min = p[i] * num[i] / (1.0 * (num[i] + a[i])) - p[i] * (num[i] - 1) / (1.0 * (num[i] + a[i] - 1));
        tree[k].maxid = tree[k].minid = i;
    }

    void build(int k,int l,int r){
        tree[k].l = l; tree[k].r = r;
        if(l == r) {calc(k,l); return;}
        int mid = (l + r) >> 1;
        build(lson,l,mid); build(rson,mid + 1,r);
        update(k);
    }

    void modify(int k,int x){
        if(tree[k].l == tree[k].r) {calc(k,x); return;}
        int mid = (tree[k].l + tree[k].r) >> 1;
        if(x <= mid) modify(lson,x);
        else modify(rson,x);
        update(k);
    }

    double queryans() {return tree[1].ans;}
    pair<double,int> querymax() {return make_pair(tree[1].max,tree[1].maxid);}
    pair<double,int> querymin() {return make_pair(tree[1].min,tree[1].minid);}
} T;

int main(){
    scanf("%d%d%d",&n,&t,&Q);
    for(int i = 1;i <= n;i++) scanf("%lf",&p[i]);
    for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
    T.build(1,1,n);
    for(int i = 1;i <= t;i++){
        int x = T.querymax().second;
        num[x] += 1; T.modify(1,x);
    }
    while(Q--){
        int op,x; scanf("%d%d",&op,&x);
        a[x] += (op == 1 ? 1 : -1);
        T.modify(1,x);
        while(T.querymax().first > T.querymin().first){
            int x = T.querymax().second, y = T.querymin().second;
            num[x] += 1; num[y] -= 1;
            T.modify(1,x); T.modify(1,y);
        }
        printf("%.8f\n",T.queryans());
    }
    return 0;
}
```

---

## 作者：UKE_Automation (赞：0)

### CF626G Raffles

[$\text{Link}$](https://codeforces.com/problemset/problem/626/G)

先考虑没有修改怎么做。考虑增加一张彩票对于答案的贡献，画图分析可知，$\dfrac{x}{x+c}$ 单调递增，且增长速度越来越慢。也就是说我们单次做出的贡献会不断变小，所以我们可以使用贪心，用堆维护往每一个堆上加一张彩票的贡献，每次取最大的即可。

然后考虑修改，我们修改 $l_i$ 之后显然会改变某些堆上的 $t_i$ 值以达到最优解，所以再用一个堆维护每一个堆删除一张彩票的贡献，然后不断挪动彩票直到无法变得更优。不难想到的是，由于 $l$ 每次只会变化 $1$，所以彩票的变化量应该是 $O(1)$ 级别的。事实上每次最多只会变化一张，所以暴力做复杂度就是正确的。

用两个 `multiset` 维护两个堆即可，复杂度 $O((t+q)\log n)$。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

typedef long double db;
const int Maxn = 2e5 + 5;
const int Inf = 2e9;
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int n, m, q, p[Maxn], l[Maxn], t[Maxn];
struct Dat {
	int pos; db val;
	bool operator < (const Dat &t) const {
		if(val == t.val) return pos < t.pos;
		return val > t.val;
	}
};
multiset <Dat> A, D;

il db calc(int x, int t) {
	return 1.0 * t / (t + l[x]) * p[x];
}

db ans = 0;
il void Add(int x) {
	ans += calc(x, t[x] + 1) - calc(x, t[x]);
	A.erase({x, calc(x, t[x] + 1) - calc(x, t[x])});
	if(t[x]) D.erase({x, calc(x, t[x] - 1) - calc(x, t[x])});
	t[x]++;
	if(t[x] < l[x]) A.insert({x, calc(x, t[x] + 1) - calc(x, t[x])});
	D.insert({x, calc(x, t[x] - 1) - calc(x, t[x])});
}

il void Del(int x) {
	ans += calc(x, t[x] - 1) - calc(x, t[x]);
	if(t[x] < l[x]) A.erase({x, calc(x, t[x] + 1) - calc(x, t[x])});
	D.erase({x, calc(x, t[x] - 1) - calc(x, t[x])});
	t[x]--;
	A.insert({x, calc(x, t[x] + 1) - calc(x, t[x])});
	if(t[x]) D.insert({x, calc(x, t[x] - 1) - calc(x, t[x])});
}

il void rb() {
	while(1) {
		if(!m || A.empty()) break;
		int x = (*A.begin()).pos;
		Add(x); m--;
	}
	while(1) {
		if(A.empty() || D.empty()) break;
		int x = (*D.begin()).pos;
		Del(x);
		int y = (*A.begin()).pos;
		Add(y);
		if(x == y) break;
	}
}

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	IOS(); cin >> n >> m >> q;
	for(int i = 1; i <= n; i++) cin >> p[i];
	for(int i = 1; i <= n; i++) cin >> l[i];
	for(int i = 1; i <= n; i++) A.insert({i, calc(i, 1) - calc(i, 0)});
	while(1) {
		if(!m || A.empty()) break;
		int x = (*A.begin()).pos;
		Add(x); m--;
	}
	while(q--) {
		int opt, x;
		cin >> opt >> x;
		switch(opt) {
			case 1: {
				ans -= calc(x, t[x]);
				if(t[x] < l[x]) A.erase({x, calc(x, t[x] + 1) - calc(x, t[x])});
				if(t[x]) D.erase({x, calc(x, t[x] - 1) - calc(x, t[x])});
				l[x]++;
				if(t[x] < l[x]) A.insert({x, calc(x, t[x] + 1) - calc(x, t[x])});
				if(t[x]) D.insert({x, calc(x, t[x] - 1) - calc(x, t[x])});
				ans += calc(x, t[x]);
				break;
			}
			case 2: {
				ans -= calc(x, t[x]);
				if(t[x]) D.erase({x, calc(x, t[x] - 1) - calc(x, t[x])});
				if(t[x] < l[x]) A.erase({x, calc(x, t[x] + 1) - calc(x, t[x])});
				else t[x]--, m++;
				l[x]--;
				if(t[x] < l[x]) A.insert({x, calc(x, t[x] + 1) - calc(x, t[x])});
				if(t[x]) D.insert({x, calc(x, t[x] - 1) - calc(x, t[x])});
				ans += calc(x, t[x]);
				break;
			}
		}
		rb();
		cout << fixed << setprecision(9) << ans << '\n';
	}
    Usd();
	return 0;
}

```

---

## 作者：_ANIG_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF626G)

考虑一张一张地分配。

如果把一张彩票分配到 $i$，则贡献为 

$$\frac{t_i+1}{t_i+l_i+1}-\frac{t_i}{t_i+l_i}=\frac{l_i}{(t_i+l_i)(t_i+l_i+1)}$$

显然，贡献为单调递减的。

所以可以贪心地考虑，每次取贡献最大的。

考虑维护这个过程。

维护两个堆，用一个小根堆维护前 $t$ 大的值，用一个大根堆维护其他值，每次修改后进行调整，把小根堆所有小于大根堆的数弹掉，再把大根堆对应的值加进去。

由于 $l_i$ 每次只变化 $1$，所以修改量很少。

但是总状态是 $2\times 10^8$ 的。

对于每个 $i$，可以维护 $g_i$，使得 $t_i=g_i$ 时贡献在前 $k$ 大里面，且 $t_i=g_i+1$ 时贡献在前 $k$ 大外面。

每次只要弹出 $g_i$ 且 $g_i$ 不为 $0$，就把 $g_i-1$ 加回去。

总复杂度 $O(q\log n+ql)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
const int N=2e5+5;
int n,t,m,p[N],w[N],g[N],sms;
double res;
struct node{
    double sm;int x,y;
    friend bool operator<(node a,node b){
        return a.sm<b.sm;
    }
    friend bool operator>(node a,node b){
        return a.sm>b.sm;
    }
};
priority_queue<node,vector<node>,greater<node> >q1;
priority_queue<node>q2;
struct nodes{
    double sm;
    int x,y;
    friend bool operator<(nodes a,nodes b){
        return a.sm<b.sm;
    }
};
priority_queue<nodes>q;
double gets(int x,int y){
    if(y>p[x])return 0;
    return w[x]*(double)(p[x])/((p[x]+y)*(p[x]+y-1));
}
void solve(){
    while(q.size())q.pop();
    for(int i=1;i<=n;i++)q.push((nodes){w[i]*1.0/(p[i]+1),i,1});
    for(int i=1;i<=t;i++){
        nodes qq=q.top();int x=qq.x;
        q.pop();
        g[x]++;
        res+=qq.sm;
        q.push((nodes){gets(x,qq.y+1),x,qq.y+1});
    }
}
bool eq(double a,double b){
    return abs(a-b)<1e-12;
}
void init(){
    while(!eq(q1.top().sm,gets(q1.top().x,g[q1.top().x]))||q1.top().y!=g[q1.top().x])q1.pop();
    while(!eq(q2.top().sm,gets(q2.top().x,g[q2.top().x]+1))||q2.top().y!=g[q2.top().x])q2.pop();
}
void Solve(){
    init();
    while(q1.top().sm<q2.top().sm){
        node a=q1.top(),b=q2.top();
        q1.pop();q2.pop();
        res-=a.sm;res+=b.sm;
        a.y--;b.y++;
        q2.push(a);q1.push(b);
        g[b.x]++;g[a.x]--;
        if(g[a.x])q1.push((node){gets(a.x,g[a.x]),a.x,g[a.x]});
        q2.push((node){gets(b.x,g[b.x]+1),b.x,g[b.x]});
        init();
    }
}
signed main(){
    cin>>n>>t>>m;
    for(int i=1;i<=n;i++)scanf("%lld",&w[i]);
    for(int i=1;i<=n;i++)scanf("%lld",&p[i]);
    solve();
    for(int i=1;i<=n;i++){if(g[i])q1.push((node){gets(i,g[i]),i,g[i]});q2.push((node){gets(i,g[i]+1),i,g[i]});}
    for(int ii=1;ii<=m;ii++){
        int op,x;
        scanf("%lld%lld",&op,&x);
        for(int i=1;i<=g[x];i++){res-=gets(x,i);if(i>p[x])break;}
        if(op==1)p[x]++;
        else p[x]--;
        if(g[x])q1.push((node){gets(x,g[x]),x,g[x]});
        q2.push((node){gets(x,g[x]+1),x,g[x]});
        for(int i=1;i<=g[x];i++){res+=gets(x,i);if(i>p[x])break;}
        Solve();
        printf("%.15Lf\n",res);
    }
}
```


---

