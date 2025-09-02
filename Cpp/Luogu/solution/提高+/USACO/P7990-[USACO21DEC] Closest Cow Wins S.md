# [USACO21DEC] Closest Cow Wins S

## 题目描述

Farmer John 沿着一条高速公路拥有一个很长的农场，可以被看作类似于一维数轴。沿着农场有 $K$ 块草地（$1 \leq K \leq 2\cdot 10^5$）；第 $i$ 块草地位于位置 $p_i$ 并具有美味值 $t_i$（$0\le t_i\le 10^9$）。Farmer John 的死对头 Farmer Nhoj 已经将他的 $M$ 头奶牛（$1 \leq M \leq 2\cdot 10^5$）放在了位置 $f_1 \ldots f_M$ 。所有这些 $K+M$ 个位置均是 $[0,10^9]$ 范围内的不同整数。

Farmer John 需要选择 $N$（$1\le N\le 2\cdot 10^5$）个位置（不一定是整数）放置他的奶牛。这些位置必须与 Farmer Nhoj 的奶牛已经占用的位置不同，但是 Farmer John 可以将他的奶牛放在与草地相同的位置。

拥有最靠近某个草地的奶牛的农夫拥有这一草地。如果来自两方农夫的两头奶牛距这一草地相等，则 Farmer Nhoj 拥有该草地。

给定 Farmer Nhoj 的奶牛的位置以及草地的位置和美味值，求 Farmer John 的奶牛以最优方式放置时可以达到的最大总美味值。

## 说明/提示

【样例解释】

如果 Farmer John 将奶牛放在位置 $11.5$ 和 $8$ 则他可以得到总美味值 $10+12+14=36$。


## 样例 #1

### 输入

```
6 5 2
0 4
4 6
8 10
10 8
12 12
13 14
2
3
5
7
11```

### 输出

```
36```

# 题解

## 作者：泥土笨笨 (赞：37)

今年和学生们一起在机房一起比(tui)赛(fei)，银组三道题都写了，写个题解纪念一下吧。

第一想法是，如果用 $f_i$ 数组表示敌人的牛的位置，一共 %m% 头敌人的牛，可以把整个数轴划分为 $m+1$ 个区间，那么每个区间互不影响，可以单独考虑。比如目前我们考虑 $f_i$ 到 $f_{i+1}$ 这个区间。那么如果在 $f_i$ 左侧放一头自己的牛，这头自己的牛不会影响到 $f_i$ 到 $f_{i+1}$ 这个区间内部的草，因为 $f_i$ 位置敌人的牛离这些草更近。同理，如果在 $f_{i+1}$ 右侧放自己的牛，也不会影响这个区间内部的草。所以我们可以把每个区间单独考虑。

当然， $f_1$ 左侧所有的草，如果我们想要的话，只需贴着 $f_1$ 左边一点点，放我们自己的牛，即可全部收入囊中。同理, $f_m$ 右侧的草，也只需要一头牛即可全部搞定。那么对于每个区间内部的草呢？

先发现一个结论，就是每个区间内部最多放两头牛，就能占掉所有的草。比如下图中所有的草用 $p$ 表示，我们只需把自己的牛放在 $c_1$ 和 $c_2$ 的位置，就能收获所有这个区间内的草。也就是说，每个区间最多放两头牛。

![](https://cdn.luogu.com.cn/upload/image_hosting/avuhf1og.png)

下一步考虑，如果这个区间只放一头牛呢？最大收益是多少？首先我们观察有多少个不同的放牛的位置。对于每块草地，它到区间的左右边界的最小值，叫做这个草地的半径，只要我们把牛放在这个半径以内，我们就可以占领这块草，比如下图，对于每个草地，我们把半径画出来。并且把每个区域与这个区间内的交点，用大家最喜欢的黄色标出来，称之为关键点：

![](https://cdn.luogu.com.cn/upload/image_hosting/08znowm7.png)

可以发现，在相邻关键点之间，牛放在什么位置是无所谓的，所以不妨认为牛放在每个关键点左边一点点的位置。但是从一个关键点，走到下一个关键点，能控制的牛的数量就会发生变化了。这里可以用滑窗或者尺取类似的思路，维护一个范围 $left$ 到 $right$ ，是当前位置放牛，可以控制的草的范围。每当牛走到下一个位置的时候，如果发现 $left$ 已经脱离范围了，就把 $left++$ ，如果发现 $right+1$ 进入范围了，就把 $right++$ ，这样我们在 $O(n)$ 时间内能算出来任何一个位置放牛的收益。

好了，现在问题模型已经转化了。变成有 $m+1$ 个区间，每个区间放一头牛的收益记为 $value_i$ ，放两头牛的收益记为 $all_i$ ，总共有 $n$ 头牛，问总收益虽大是多少。

这个问题我们可以用贪心解决。开一个优先队列，把每个区间放进去，优先队列按照当前区间再放一头牛的收益，从大到排序。这样我们相当于每次决策的时候，都选择一个最划算的区间，尽量用手里现在这头牛，获得最大的价值。当一个区间从优先队列里面取出来的时候，我们看一下，如果这个区间是第一次被取出来，我们就把它的 $value$ ，改成 $all-value$ 再放回去。表示这个区间已经放过一头牛了，如果再放一头牛，它的价值就是放两头牛价值的总和，那么第二头牛的价值就是 $all-value$ 。这样一直贪心就可以了。

赛时代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;
const ll MAXN = 2e5 + 5;

struct Grass {
    ll p, t;//位置，价值
    ll l, r;//想占据当前草地，需要放牛的区间，都是开区间
    bool operator<(const Grass &a) const {
        return p < a.p;
    }
} g[MAXN];

struct Node {
    ll value, all, cnt;//在当前区间内再选一头牛的价值，区间总价值，已经拿了几次了
    Node(ll value, ll all, ll cnt) : value(value), all(all), cnt(cnt) {}

    bool operator<(const Node &a) const {
        return value < a.value;
    }
};

ll k, m, n;//草地，敌人牛的数量，自己牛的数量
ll f[MAXN];//敌人的牛的位置
ll p[MAXN << 2], pc;//当前段内关键点，关键点的个数
ll dp[MAXN];
priority_queue<Node> q;

//进行分组
void work() {
    ll all = 0;//当前组内总价值
    ll pi = 1;//下一个还没分配的草地
    //第一头敌人的牛前面的，都可以用一头牛直接拿下
    while (pi <= k && g[pi].p < f[1]) {
        all += g[pi].t;
        pi++;
    }
    q.push(Node(all, all, 0));
    for (int i = 2; i <= m; ++i) {
        //处理f[i-1]到f[i]之间的草
        all = pc = 0;
        ll left = f[i - 1], right = f[i];//左边界，右边界
        ll from = pi;//本组内第1块草
        while (pi <= k && g[pi].p < right) {
            ll ra = min(g[pi].p - left, right - g[pi].p);//当前半径
            g[pi].l = g[pi].p - ra;
            g[pi].r = g[pi].p + ra;
            if (g[pi].l != left) {
                p[pc++] = g[pi].l;
            }
            if (g[pi].r != right) {
                p[pc++] = g[pi].r;
            }
            all += g[pi].t;
            pi++;
        }
        if (from == pi) {
            //这一块内没有草
            continue;
        }
        //对于每个关键点，看看把牛放在关键点左边一点点怎么样
        p[pc++] = right;//右端点也算一个关键点
        sort(p, p + pc);
        ll tt = 0;
        //尺取计算放在每个关键点的答案
        ll tl = from, tr = from - 1, w = 0;
        for (int j = 0; j < pc; ++j) {
            ll pos = p[j];
            while (tr + 1 < pi && pos > g[tr + 1].l) {
                tr++;
                w += g[tr].t;
            }
            while (tl < pi && pos > g[tl].r) {
                w -= g[tl].t;
                tl++;
            }
            tt = max(tt, w);
        }
        q.push(Node(tt, all, 0));
    }
    //最后一个敌人的牛的后面的牛，都可以用一只牛搞定
    all = 0;
    while (pi <= k) {
        all += g[pi].t;
        pi++;
    }
    q.push(Node(all, all, 0));
}

int main() {
    scanf("%lld%lld%lld", &k, &m, &n);
    for (int i = 1; i <= k; ++i) {
        scanf("%lld%lld", &g[i].p, &g[i].t);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%lld", &f[i]);
    }
    sort(g + 1, g + k + 1);
    sort(f + 1, f + m + 1);
    work();
    ll ans = 0;
    while(n>0 && !q.empty()){
        Node t = q.top();
        q.pop();
        ans+=t.value;
        if(t.cnt==0 && t.value!=t.all){
            t.cnt++;
            t.value = t.all-t.value;
            q.push(t);
        }
        n--;
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：nalemy (赞：13)

在每两个相邻坏牛之间，我们可以放 $0,1,2$ 头好牛。

放 $0$ 头好牛即两头坏牛中间所有草地**不要**。

放 $2$ 头好牛即两头坏牛中间所有草地**全要**。

放 $1$ 头好牛较为复杂。我们设左右两头坏牛分别位于 $i,j$，好牛位于 $k$。

$(\frac{i+k}2,k]$ 和 $[k,\frac{j+k}2)$ 中的草地一定距离这头好牛最近，即会产生 $(\frac{i+k}2,\frac{j+k}2)$ 区间内所有草地的价值。我们发现这个开区间的长度恒定为 $\frac{j-i}2$，因此我们让这个区间从 $i$ 开始向右滑动，用双指针维护包含哪些区间，这个区间内草地的价值可以用前缀和维护。

我们用上述方法算出任意两个坏牛之间放 $1$ 个好牛的最大价值。那么如果这个区间中放了 $2$ 个好牛，我们就把 $\text{整个区间价值}-\text{只放第一个牛的最大价值}$ 归为第二个牛的贡献。我们用堆来维护。具体实现见代码。

当然，最左边的坏牛左边和最右边的坏牛右边是没有考虑的，所以我们先在左右放两个假坏牛，因为离得太远，不会对答案产生影响。

```cpp
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
using ll = long long;
using pli = pair<ll, int>;

const int N = 2e5;
struct nd { ll p; int t; } a[N];
ll s[N+1], f[N+2], ans; priority_queue<pli> q;
int main() {
    int n, m, k; cin >> n >> m >> k;
    for (int i=0; i<n; i++) cin >> a[i].p >> a[i].t;
    for (int i=1; i<=m; i++) cin >> f[i];
    sort(a, a+n, [](nd a, nd b){return a.p<b.p;}), sort(f+1, f+m+1), *f = -1e16, f[m+1] = 1e16;
    for (int i=0; i<n; i++) s[i+1]=s[i]+a[i].t; // 我喜欢这么写，左闭右开
    auto cmp = [](nd a, int b){return a.p<b;};
    for (ll i=0, l, r, len, mx; i<=m; i++) {
        l=lower_bound(a, a+n, f[i], cmp)-a, r=lower_bound(a, a+n, f[i+1], cmp)-a-1, len=f[i+1]-f[i], mx=0;
        for (int x=l, y=l; x<=r; mx=max(mx, s[y]-s[x++])) // 更新答案时没有算右端点
            for (; y<=r; y++) if (a[y].p-a[x].p<<1>=len) break; // 开区间，大于等于就要弹
        q.push({mx, s[r+1]-s[l]-mx}); // 把第二只牛的贡献先附在后面
    }
    for (pli t; k--;) t = q.top(), q.pop(), ans += t.first, t.first = t.second, t.second = 0, q.push(t); // 因为先放完第一只牛才能放第二只，所以第一只放完再 push
    cout << ans;
    return 0;
}
```

注意，如果插进去 `pair(5, 10)` 和 `pair(4, 15)`，能拿 $2$ 个牛的话，那么这个程序会拿 $5+10=15$，正确结果是 $4+15=19$。当然，这里贪心的正确性在于第一次 `push` 的 `pair` 满足 $first\ge second$。否则就要用背包 DP 了！

---

## 作者：FreeTimeLove (赞：8)

这是一道**贪心**题。

我们发现，Nhoj 的 $m$ 头奶牛将整个农场分割成了 $(m+1)$ 块。

如果 John 在第 $i$ 块放两头奶牛,他就可以获得这块农场的**全部**草地；如果他不放奶牛，他就（显然）得不到草地。如果 John 只放一头奶牛，他最大收益为这块农场内**长度小于 $\dfrac{len}{2}$ 的最大子区间**的收益。

我们设这一块农场左边 Nhoj 的牛坐标为 $l$，右边的为 $r$，John 的牛坐标为 $p$。因为一块草地属于离得近的牛且**如果双方距离相等属于 Nhoj**，所以属于 John 的范围是 $(\dfrac{l+p}2,\dfrac{r+p}2)$，是一个长度**严格小于** $\dfrac{r-l}2$ 的子区间，利用队列扫一遍即可。

我们设 $s[i][0]$ 表示第 $i$ 块草地放一头牛的**最大收益**， $s[i][1]$ 表示第 $i$ 块草地放两头牛的最大收益，那么 $(s[i][1]-s[i][0])$ 就表示第 $i$ 块草地原有一头牛，再放一头牛**增加的**收益。

我们发现，因为 $s[i][0]\ge (l,\dfrac{l+r}{2}),s[i][0]\ge (\dfrac{l+r}{2},r)$，所以 $2\times s[i][0]\ge (l,r)=s[i][1]$，因此 $s[i][0]\ge s[i][1]-s[i][0]$ 一定成立，具有**收益递减规律**。

那么我们就可以贪心求解。我们将所有 $s[i][0]$ 压入一个大根堆，每次取出堆顶，加在 $ans$ 上，如果堆顶是 $s[i][0]$ 就再压入 $s[i][1]-s[i][0]$。重复执行 $n$ 次后的 $ans$ 即为答案。

### AC code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
#define ll long long
#define db double
using namespace std;
const int N=2e5+5;
int read(){
	int ans=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	if(f)ans=-ans;
	return ans;
}
ll INF=0x3f3f3f3f3f;
int k,m,n,nw=1,head,tail;
ll sum,a[N],q[N],s[N][2],cnt,ans;
struct xxs{
	ll p,t;
}dt[N];
bool cmp(xxs a,xxs b){
	return a.p<b.p;
}
struct node{
	ll id,val,num;
	bool operator <(const node &x)const{
		return val<x.val;
	}
}u;
priority_queue<node>que;
int main(){
	k=read(),m=read(),n=read();
	for(int i=1;i<=k;i++)dt[i].p=read(),dt[i].t=read();
	sort(dt+1,dt+k+1,cmp);
	for(int i=1;i<=m;i++)a[i]=read();
	sort(a+1,a+m+1);
	
	a[0]=-INF,a[m+1]=INF;
	for(int i=1;i<=m+1;i++){//分成(m+1)块
		double len=(double)(a[i]-a[i-1])/2.0;
		sum=head=tail=0;
		while(nw<=k&&dt[nw].p<a[i]){//利用队列求放一头牛的最大收益
			while(head<tail&&dt[q[head]].p+len<=dt[nw].p)sum-=dt[q[head++]].t;
			q[tail++]=nw;
			sum+=dt[nw].t;
			s[i][0]=max(s[i][0],sum);
			s[i][1]+=dt[nw++].t;
		}
		que.push({i,s[i][0],0});
	}
	while(cnt<n&&!que.empty()){//大根堆维护当前可选最大值
		u=que.top();
		que.pop();
		ans+=u.val;
		if(u.num==0)que.push({u.id,s[u.id][1]-s[u.id][0],1});
		cnt++;
	}
	printf("%lld\n",ans);
	return 0;
}
```
### $\text{The End.}$

---

## 作者：_Imaginary_ (赞：6)

## Problem

给定数轴上的一些点，每个点有一个权值，在上面还有一些点构成集合 $A$，请找出一个大小为 $n$ 的点集 $B$，使得前面这些点中更靠近 $B$ 的点的权值和最大。

## Solution

枚举每相邻两个集合 $A$ 的点，看看 FJ 用一头奶牛最多能覆盖多少权值。

事实上，一头奶牛能覆盖的范围是一个区间，我们可以试着用滑动窗口。

从左到右枚举这头奶牛覆盖的区间，看看此时能覆盖多少，取最大值。把所有这些最大值排序。

另外，如果 FJ 用两头奶牛，则一定能覆盖两头 FN 奶牛中间的。

所以，判断即可。

## Code
```cpp

#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod=1000000007;
const int N=200005;
const bool LEFT=0,RIGHT=1;
struct node{
	ll pos,num;
}a[N];
ll f[N],sum[N];
int k,m,n;
bool operator <(node a,node b)
{
	return a.pos<b.pos;
}
int L,R,mid;
int lb_a(int x,bool op)
{
	L=0,R=k+1;
	while(L<=R)
	{
		mid=(L+R)>>1;
		if(a[mid].pos>x) R=mid-1;
		else L=mid+1;
	}
	if(a[R].pos==x) R--;
	return op?L:R;
}
/*int lb_f(int x,bool op)
{
	L=0,R=m+1;
	while(L<=R)
	{
		mid=(L+R)>>1;
		if(f[mid]>x) R=mid-1;
		else L=mid+1;
	}
	return op?L:R;
}*/
priority_queue<ll> q;
int main()
{
	scanf("%d%d%d",&k,&m,&n);
	for(int i=1;i<=k;i++) scanf("%lld%lld",&a[i].pos,&a[i].num);
	sort(a+1,a+k+1);
	a[k+1]=node{0x3f3f3f3f,0};
	a[0]=node{-0x3f3f3f3f,0};
	for(int i=1;i<=k;i++) sum[i]=sum[i-1]+a[i].num;
	for(int i=1;i<=m;i++) scanf("%lld",&f[i]);
	sort(f+1,f+m+1);
	f[m+1]=0x3f3f3f3f;
	f[0]=-0x3f3f3f3f;
	/*while(1)
	{
		int ta,tb,tc;
		scanf("%d%d%d",&ta,&tb,&tc);
		if(ta==1) printf("%d\n",lb_a(tb,tc));
		else printf("%d\n",lb_f(tb,tc));
	}*/
	int aL,aR,pL,pR,vpL,vpR,tp,qp,qR;
	ll mx;
	for(int i=0;i<=m;i++)
	{
		aL=f[i],aR=f[i+1];
		pL=lb_a(aL,RIGHT),pR=lb_a(aR,LEFT);
		vpL=a[pL].pos,vpR=a[pR].pos;
		if(pL>pR) continue;
		mx=0;
		for(int j=pL;j<=pR;j++)
		{
			tp=vpL*2-aL;
			qp=(tp+aR+1)/2;
			qR=min(lb_a(qp,LEFT),pR);
			mx=max(mx,sum[qR]-sum[j-1]);
		}
		q.push(mx);
		q.push(sum[pR]-sum[pL-1]-mx);
	}
	ll ans=0;
	while(!q.empty()&&n--)
	{
		ans+=q.top(); q.pop();
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：xkcdjerry (赞：2)

可以观察到 FJ 对于每一对相邻的 FN 的奶牛有两种选择：

* 放一只奶牛：此时由于能够占领的势力范围为到左边 FN 牛连线的中点和与右边 FN 牛连线的中点，即长度为两个牛距离一半的**开**区间，可以通过滑动窗口来 $O(内部草地数量)$ 处理最大占领草地的美味值

* 放两只奶牛：显然 FJ 可以在区间内侧贴着 FN 的奶牛放两只自己的来占领整个区间

用滑动窗口预处理每对相邻的 FN 的牛之间的最大选择显然只需要 $O(k+m)$ 的时间。

（本蒟蒻赛时刚开始没有想到放两只奶牛的情况，以为代码有问题调了一个半小时差点没写完，吐槽一下坑比样例根本测不出来这个 bug）

先假设只有第一种情况，那么可以排序一下放一只奶牛的所有收益 $g$ 然后取前 $n$ 大，但是有第二种怎么办呢？

由于数据范围有 $10^5$ 所以没法 dp，考虑给贪心打补丁：

定义第二个数组 $h$ 使 $h_i=$ 区间 $i$ 中的总美味值 $-g_i$，那么选择 $g_i$ 之后再选择 $h_i$ 就等于是给它上面分配了 2 只奶牛。

由于只选 $g_i$ 的时候等于第一种情况，某些 $i$ 同时选了 $g_i$ 和 $h_i$ 等效于放两只奶牛，而且每一步一定取最大收益而且互不干扰，所以这么贪心显然正确。

代码如下（注意 $h$ 与 $g$ 被合并到了 `g` 数组中）：

```c++
#include <cstdio>
#include <algorithm>
#define ll long long
#define K 200010
#define M 200010
using std::sort;
int k,m,n,f[M],q[M];
ll g[M*2];
struct pasture
{
	int p,t;
	bool operator<(pasture b) const {return p<b.p;}
}a[K];
int main()
{
	scanf("%d%d%d",&k,&m,&n);
	for(int i=0;i<k;i++) scanf("%d%d",&a[i].p,&a[i].t);
	for(int i=1;i<=m;i++) scanf("%d",f+i);
	sort(a,a+k); sort(f+1,f+m+1);
	
	int p=0;
	while(p<k&&a[p].p<f[1]) g[0]+=a[p++].t;
	//这句可以不用
	//g2[1]=0;
	int end=2;
	for(int i=1;i<m;i++)
	{
		int l=p,head=0,tail=0;
		ll ans=0,tmp=0,mx=0;
		while(p<k&&a[p].p<=f[i+1]) p++;
		for(int j=l;j<p;j++)
		{
			q[head++]=j;
			ans+=a[j].t;
			tmp+=a[j].t;
			while(head!=tail&&(a[j].p-a[q[tail]].p)*2>=f[i+1]-f[i])
				ans-=a[q[tail++]].t;
			if(ans>mx) mx=ans;
		}
		g[end++]=mx;
		g[end++]=tmp-mx;
	}
	while(p<k) g[end]+=a[p++].t;
	end++;
	//这句可以不用
	//g[end++]=0;
	sort(g,g+end);
	ll ans=0;
	for(int i=0;i<n;i++) ans+=g[--end];
	printf("%lld",ans);
}
```

注：这里把 $h_i$ 和 $g_i$ 放进了同一个数组里，那么怎么保证不会先选 $h_i$ 再选 $g_i$ 呢？

不妨假设某个区间 $i$ 中比 $g_i$ 先选了 $h_i$，那么显然有：

* $h_i>g_i$
* $h_i$ 为两个区间（否则求最大区间和的时候取到的就不是 $g$ 而是 $h$ 了）

不妨以区间中点为分界线，称两边的 $h_i$ 分别为 $lh$ 和 $rh$ ，$g$ 显然被中点分割，也称 $lg$ 和 $rg$ ，由于 $g$ 是最大区间和显然有：

* 区间的左半边和 $\leqslant g$，即 $lh+lg \leqslant lg+rg$，则 $lh \leqslant rg$。
* 区间的右半边和 $\leqslant g$，即 $rg+rg \leqslant lg+rg$，则 $rh \leqslant lg$。

综上有 $h=lg+rg \leqslant rg+lg=g$ ，与假设矛盾，故得证。


这道题的启发：如果有许多独立的子问题，对于任意一个子问题花 1 代价能够得到某些回报，花 2 代价获得更多回报，花 3 代价获得更更多回报……那么可以通过这种差分思想使得它可以贪心解决。

---

## 作者：蒻蒟IOOI蒟蒻 (赞：2)

# **一、总体思路**

$FN$ 的奶牛把农场划分为 $M+1$ 个区间（都是开区间），我们用优先队列（大根堆）来统计放置 $N$ 只奶牛可以得到的最大的美味值。

# **二、分析过程**

开头和结尾的两个区间都是只需要放一只奶牛就可以获得其全部美味值。（即放在 $FN$ 第一只奶牛的左边，和放在 $FN$ 第 $M$ 只奶牛的右边）

我们考虑第$i$个区间，即为 ($f_x$,$f_{x+1}$) 的区间，我们可以选择放一只牛或两只牛在该区间上。
如果放两只牛，我们可以得到这个区间的美味值总和；

如果放一只牛，我们假设把牛放在 $P$ 点上，我们可以得到 ($\frac{f_x+P}2$,$\frac{f_{x+1}+P}2$ )的子区间的美味值，
即长度为小于 $\frac{f_{x+1}-f_x}2$ 的子区间的美味值，这个区间的长度与$P$点的位置无关。
 
我们计算出了对于第$i$个区间选择放一只牛得到的答案为 $a$ ,和放两只牛得到的答案为 $b$ 。
要得到原问题的答案（即我们可以在区间中放一头牛或两头牛），我们向优先队列中加入 $a$ 和 $b-a$ 即可。

因为 $2a$ 大于等于 $b$，所以 $b-a$ 小于等于 $a$，因此在优先队列中如果我们选了 $b-a$，我们肯定选过 $a$。

# **三、具体实现**


统计美味值要求一段区间之内的美味值总和，所以首先预处理一个前缀和，然后用二分查找确定这段区间的开头和末尾。

代码：

```cpp
#include <iostream>
#include <queue>
#include <algorithm>
#define lb(x) lower_bound(a+1,a+k+1,Node(x,0))
#define ub(x) upper_bound(a+1,a+k+1,Node(x,0))
#define int long long
using namespace std;
const int M = 2e5 + 1;
struct Node {
    int p, t;
    bool operator <(const Node &y) const {
        return p < y.p;
    }
    Node() {}
    Node (int _p, int _t) : p(_p), t(_t) {}
} a[M];
bool cmp(Node x, Node y) {
    return x.p < y.p;
}
int k, m, n, f[M], ans;
priority_queue<int> q;
signed main() {
    cin >> k >> m >> n;
    for (int i = 1; i <= k; i++) {
        cin >> a[i].p >> a[i].t;
        a[i].p *= 2;
    }
    sort(a + 1, a + k + 1, cmp);
    for (int i = 1; i <= k; i++) {
        a[i].t += a[i - 1].t;
    }
    for (int i = 1; i <= m; i++) {
        cin >> f[i];
        f[i] *= 2;    
    }
    sort(f + 1, f + m + 1);
    q.push(lb(f[1])[-1].t);
    for (int i = 1; i < m; i++) {
        int no1 = ub(f[i]) - a, no2 = lb(f[i + 1]) - a;
        int sum2 = a[no2 - 1].t - a[no1 - 1].t, ttt = (f[i + 1] - f[i]) / 2, sum = 0;
        if (!sum2) continue;
        for (int j = no1; j < no2; j++) {
            sum = max(sum, lb(min(a[j].p + ttt, f[i + 1]))[-1].t - a[j - 1].t);
        }
        q.push(sum);
        q.push(sum2 - sum);
    }
    q.push(a[k].t - ub(f[m])[-1].t);
    for (int i = 1; i <= n && q.size(); i++) {
        ans += q.top();
        q.pop();
    }
    cout << ans << endl;
    return 0;
}
```


~~ps:第一次发题解，语言可能不太流畅，审核大大求过~~

---

## 作者：听取MLE声一片 (赞：2)

USACO的比赛没报，但是让一位神仙把题发过来，写了一发 TLE，然后再改了一下就 AC 了。

~~这题真的很考细节性东西的（迫真）。~~

先看题，然后发现对于每两头 `Nhoj` 的奶牛中间都有**两种情况**，一种是**紧贴**在这两头牛中间放**两头**（对中间的草地形成两面包夹芝士），另一种是在这两头牛之间放最优的**一头**。

证明的话，显然 `John` 两头牛可以把 `Nhoj` 两头奶牛中间的草地全部占据，而还可以在中间只放一头奶牛。

求两只奶牛中间的比较容易，整个指针找就行，关键是放一头奶牛。我的做法是直接枚举每一块地，从这块地开始 `upper_bound` 。我们假设上一头 `Nhoj` 牛位置是 $a_i$，下一头牛位置是 $a_i+1$，我们要占据的草地是 $b_j$，那么 `John` 所放牛的位置就是 $p=2\times b_j-a_i-1$，最远能占据的距离就是 $(p+a_{i+1})\times \frac{1}{2}$。这里的边界判断很玄乎，可以自己再理解一下。这样时间复杂度就是 $m\log m$。

由此我们就可以得到一组类似于物品有两个体积和两个价值，只能选一个的01背包，但是直接算的话时间复杂度就直接到了 $n^2$，我们就要换一下思路。

我们发现，**只要每个物品的一体积的价值不小于二体积价值的一半，就可以直接把二体积拆成两个一体积，一个价值是本来一体积价值，另一个是二体积价值减一体积价值。** 然后直接排序即可。证明的话，就是我先在一个地方放了一头牛，之后干别的事情，后来我发现还可以再往那个地方塞一头牛，这样计算就不受影响了。

最后的问题是证明一体积价值不小于二体积价值的一半。我们假设左边一头 `Nhoj` 牛位置是 $l$，右边一头 `Nhoj` 牛位置是 $r$（跟并查集没关系），显然如果只放一头牛，放在 $l+1$ 的位置比放在 $l$ 的位置更优，放在 $r-1$ 的位置比放在 $r$ 的位置更优。假设能在 `Nhoj` 的牛上放牛，则 $l$ 位置放牛获得的价值为 $p$, $r$ 位置放牛获得的价值为 $q$,在 $l+1$ 和 $r-1$ 放两头牛获得的价值为 $k$，显然 $p+q=k$，由于 $pq$ 都为正整数，所以一定有一个不小于 $k$ 的一半，所以得证。

记得输入的时候排序，因为没保证升序输入。

下面是代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=2e5+10;
struct point{
	int p,t;
}d[N];
int k,m,n,a[N],b[N][2],f[N*2],ss[N],e[N];
int cmp(point a,point b){
	return a.p<b.p;
}
int cmpp(int a,int b){
	return a>b;
}
signed main()
{
	k=read(),m=read(),n=read();
	for(int i=1;i<=k;i++){
		d[i].p=read(),d[i].t=read();
		e[i]=d[i].p;
	}
	for(int i=1;i<=m;i++)
		a[i]=read();
	sort(a+1,a+m+1);
	sort(d+1,d+k+1,cmp);
	sort(e+1,e+k+1);
	for(int i=1;i<=k;i++)
		ss[i]=ss[i-1]+d[i].t;
	int p=1;
	for(int i=1;i<=k&&d[i].p<a[1];i++){
		p++;
		b[0][0]+=d[i].t;
	} 	
	for(int i=1;i<m;i++){
		while(a[i]==d[p].p)
			p++;	
		int s=0,q=p,sum=0,maxn=0;
		for(int j=p;j<=k&&d[j].p<a[i+1];j++){
			b[i][1]+=d[j].t;
			s+=d[j].t;
			q++;
		}
		for(int j=p;j<q;j++){
			int l=2*d[j].p-a[i]-1,r=(l+a[i+1])/2;
			int pp=upper_bound(e+p+1,e+q,r)-e-1;
			maxn=max(maxn,ss[pp]-ss[j-1]);
		}
		p=q;
		b[i][0]=maxn;
	}
	while(a[n]==d[p].p)
		p++;
	for(int i=p;i<=k&&d[i].p>a[m];i++){
		p++;
		b[m][0]+=d[i].t;
	}
	b[m][1]=b[m][0];
	b[0][1]=b[0][0];
	int cnt=0;
	for(int i=0;i<=m;i++){
		f[++cnt]=b[i][0];
		f[++cnt]=b[i][1]-b[i][0];
	}
	sort(f+1,f+cnt+1,cmpp);
	int ans=0;
	for(int i=1;i<=n;i++)
		ans+=f[i];
	printf("%lld",ans);
	return 0;
}
```

结语：这道题练贪心行，还考验边界考虑，~~不过还是一道诈骗题~~。

---

## 作者：lsj2009 (赞：2)

[更好的阅读体验。](https://www.luogu.com.cn/blog/lvsiji/solution-p7990)

赛时看见这题一眼：什么鬼！然后马上去 T2，结果回过头来 30minAC。

现在看是绿很河狸。。。
## 思路
很明显，这是一道****贪心****，那么该怎么贪呢？仔细琢磨样例之后发现一种方法：

首先，求出对每块草地与其最近的 FN 的距离，装入 $dis[]$ 数组，那么则对于草地 $i$ 而言，只有 FJ 将奶牛放在其方圆 $dis_i$ 内（不含），才能占据此草地。

那么，我们对于经典的****区间选点****问题，我们可知，FJ在考虑 $i$ 号草地时，将奶牛放在 $p_i\pm(dis_i-1)$ 处最优。

我们可以将 FJ 在****某地可以放一头奶牛可以占领的草地看做一块“草地”****，则最后将“草地”按 $t_i$ 降序排序，$ans=\sum_{i=1}^{n} t_i$。

更多细节详见代码。
## AC CODE：
```cpp
#include<bits/stdc++.h>
#define pd push_back
#define int long long //十年OI一场空，不开longlong见祖宗
using namespace std;
const int N=2e5+5;
int f[N],d[N],n,m,k,tot;
struct grass {
	int p,t;
	bool operator < (const grass& x) const {
		return p<x.p;
	}
}; grass a[N];
bool cmp(const grass& x,const grass& y) { //草地最后ti降序
	return x.t>y.t;
}
signed main() {
	scanf("%lld%lld%lld",&k,&m,&n);
	for(int i=1;i<=k;i++)
		scanf("%lld%lld",&a[i].p,&a[i].t);
	for(int i=1;i<=m;i++)
		scanf("%lld",&f[i]);
	sort(f+1,f+m+1); sort(a+1,a+k+1);
	memset(d,0x7f,sizeof(d)); //处理dis数组
	for(int i=1;i<=k;i++) {
		int x=lower_bound(f+1,f+m+1,a[i].p)-f;
		if(x!=m+1) d[i]=min(d[i],f[x]-a[i].p);
		if(x!=1) d[i]=min(d[i],a[i].p-f[x-1]);
	}
//	for(int i=1;i<=k;i++)
//		printf("%lld'min_dis = %lld\n",i,d[i]);
	vector<grass> ans;
	ans.pd(grass{a[1].p+d[1]-1,a[1].t}); //一号草地可以覆盖的最远点和当前美味值
	for(int i=2;i<=k;i++)
		if(a[i].p-d[i]<ans.back().p) { //当前草地可以和i号草地“共处一室”
			grass tmp=ans.back(); ans.pop_back(); ans.pd(grass{tmp.p,tmp.t+a[i].t});
		} else //另外开辟草地
			ans.pd(grass{a[i].p+d[i]-1,a[i].t});
	sort(ans.begin(),ans.end(),cmp);
	int tot=0;
	for(int i=0;i<n;i++) //累加前n值
		tot+=ans[i].t;
	printf("%lld",tot);
	return 1;
}

```


---

