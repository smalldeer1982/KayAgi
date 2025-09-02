# [POI 2013] POL-Polarization

## 题目描述

Everyone knew it would only be a matter of time.  So what?

  Faced for years on, a peril becomes the every-day reality.

It loses its meaning...

Today the letter of the Bitotian char Bittard to the Byteotian king Byteasar  was released to the public.

Bitotia requested annexation of the whole Byteotia on pain of using  the Bit Polarizing Magnet (BPM).

If used, the BPM would make each and every road in Byteotia unidirectional.

The enemy knows only too well that this could be a fatal blow to the  minimalist Byteotian infrastructure - there is a unique way between  each pair of towns.

  How badly can the BPM damage the Byteotian infrastructure?

Determine the minimum and the maximum number of such pairs of towns that  it will still be possible to travel from one of them to the other while  observing the new roads orientation.




## 样例 #1

### 输入

```
4
1 2
1 3
1 4
```

### 输出

```
3 5
```

# 题解

## 作者：Tsawke (赞：5)

# [LG-P3563 [POI2013]POL-Polarization](https://www.luogu.com.cn/problem/P3563) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=LG-P3563-Solution)

（建议您从上方链接进入我的个人网站查看此 Blog，在 Luogu 中图片会被墙掉，部分 Markdown 也会失效）

## 题面

给定一棵有 $ n $ 个节点的树，要求将树上所有边变成有向边，求本质不同连通点对的最小和最大对数。

定义本质不同连通点对为对于点 $ a, b $，满足 $ a $ 能到达 $ b $，或 $ b $ 能到达 $ a $。

$ n \le 2.5 \times 10^5 $。

## Solution

该说不说这道题的数据有点水，可以微调块长然后用一个不正确的贪心水过去。。。

首先对于第一个问题应该比较简单，如果说的专业一点就是，树是一个二部图，将其分解为左右部图后，把部图间的无向边全部改为左部图向右部图的有向边（反之亦然），则最小值一定为 $ n - 1 $。

或者通俗地说，把 $ i $ 到 $ i + 1 $ 层之间的边和 $ i + 1 $ 到 $ i + 2 $ 层之间的边反向连结，最终一定有 $ n - 1 $ 对连通点对。

对于第二个问题需要引入几个~~我不会证明~~很神奇的 Lemma：

Lemma 1：对于一个使连通点对数量最多的图，其中一定至少有一个点满足以其为根，所有子树要么是外向的要么是内向的，也就是说要么全部指向根方向，要么全部背向根方向。

Lemma 2：对于一个使连通点对数量最多的图，Lemma 1 的这个点一定在树的任意一个重心上。

证明：The proof is left to the reader. （~~不会证~~）

于是我们便可以发现，这道题的思路就是找到树的重心，然后以重心为根搜一下其每个子树的大小，记录下来之后枚举哪些子树是外向的，哪些是内向的，才会使最终答案最优。

如果是菊花图的话子树个数最多是 $ n $ 级别的，那么嗯枚举的话大概是 $ O(2^n) $ 显然不可以通过，考虑优化。

首先我们接着刚才的思路往下想此时我们根已经确定了，假设我们有这样一个图：

![The picture is blocked.](http://monkey-hyx.tech/Images/Blog/2022_09_28_1.png)

我们考虑除了根节点外的每一个节点，不难发现我们现在若仅考虑对每一个节点和该节点的所有子节点最高到达该节点的父亲的连通对，那么如果我们令节点 $ i $ 为根的子树大小为 $ siz_i $，那么显然上述的所有联通对的个数为 $ \sum siz_i $。

在这之后我们便不难发现只剩下如 $ (10, 3) $，即 $ 10 \rightarrow 8 \rightarrow 1 \rightarrow 2 \rightarrow 3 $，这种通过根节点的路径形成的连通对没有考虑，于是联想到我们之前的 Lemma，如果我们设所有内向的子树大小之和为 $ k_1 $，所有外向的子树大小之和为 $ k_2 $，且显然有 $ k_1 + k_2 = n - 1 $，不难想到这种情况中的连通对数量即为 $ k_1 \times k_2 $。

于是显然有 $ ans = \sum siz_i + k_1 \times k_2 $，当根确定之后前者一定是固定的，那么我们就只需要考虑什么时候后者最大即可。

我们将所有子树大小抽象成一个序列，那么我们的目标就是要将这个序列分成两部分，使两部分分别求和后乘积最大。两个数和固定，要让积最大，这玩意应该很显然就是要让两个数相等吧，放到这道题上就是让两部分的求和后的差值最小，这东西不觉得非常像搭建双塔吗。。。[关于一个人类智慧的DP - Vijos 1037 搭建双塔](http://blog.monkey-hyx.tech?t=Vijos-1037-Solution)

不过我们仔细观察一下后发现实际上并不一样，本题里我们需要将所有的数都用上，且搭建双塔的时间复杂度放在这题上就很离谱了。

首先这里提供一个奇怪的贪心，据说是 2015 集训队论文里的（~~虽然我没找到~~）（~~而且是错误的~~），大概就是维护一个大根堆，然后每次取堆顶的两个值，计算它们差的绝对值然后再插入堆里，当堆中剩余一个元素的时候这个元素就是差值的最小值，看起来似乎很奇怪，细想一下似乎很正确，但是这是错误的（如果不是我想错了的话）。

这个贪心大概的思路就是每次找最大的两个分别放在两侧，会有一个差值，然后我们可以将这个差值也认为是一个新的数，显然差值也可以和普通的数一样放置，比如说两对差值为 $ 1 $ 的块全部拼在一起最终的差值也就是 $ 0 $ 了，这里如果你做过搭建双塔的话大概也就能看出来错误在哪里了，显然我们贪心地取两个最大的放在两侧并不一定是最优的，比如这样一个序列：$ 3, 3, 3, 3, 3, 3, 3, 3, 8, 8, 8 $，显然 $ 8 $ 放在一起，$ 3 $ 放在一起，最终差值为 $ 0 $，但是按照这个贪心则会优先把两个 $ 8 $ 放在一起抵消，导致最后剩下的差值为 $ 2 $。

但是这个东西是可以过的，可以发现如果进行根号分治，但是不按照 $ \sqrt{n} $ 分治而是固定按照 $ 1000 $ 的话，那么刚好可以把这个贪心不正确的数据点在时间复杂度允许的情况下用正常的 DP + bitset 求解，最后无论是 Luogu 的十个数据点还是原题的六十多个数据点都是可以 Accept 的，就算按照标准的根号分支也可以过接近 $ 90\% $ 的点，不过不能怪数据弱，确实这个是很难卡的。

Code：

```cpp
const int B = 1000;//int(sqrt(N));
if(tot >= B){
    std::priority_queue < int, vector < int >, less < int > > vals;
    for(auto i : subt)vals.push(i);
    while(vals.size() != 1){
        int x = vals.top(); vals.pop();
        int y = vals.top(); vals.pop();
        vals.push(abs(x - y));
    }
    int diff = vals.top();
    int vx = (N - 1 - diff) / 2;
    int vy = vx + diff;
    ans += (ll)vx * vy;
}else{
    dp[0] = true;
    for(auto i : subt)dp |= dp << i;
    for(int i = N / 2 + 1; i >= 0 ; --i)if(dp[i]){ans += (ll)i * (N - i - 1); break;}
}
```

考虑正解，开一个大小为 $ n $ 的 `bool` 类型数组，表示 $ k_1 $ 是否能为 $ i $（或表示 $ k_2 $ 同理）显然是一个 $ O(n^2) $ 的 DP，转移之后从 $ \dfrac{n}{2} $ 开始跑，跑到的第一个可行解一定为最优解，使两者差最小，但是这个复杂度显然不正确。考虑子树的个数，如果小于 $ \sqrt{n} $ 那么显然这个复杂度实际上是 $ O(n\sqrt{n}) $ 的，如果大于 $ \sqrt{n} $，则子树最大值一定是小于 $ \sqrt{n} $ 的，也就是一定有相同大小的子树，且随着子树个数增多，最大值会逐渐变小，导致重复的个数继续增大，此时我们可以以多重背包的思想取考虑，将多个相同大小的子树拆成 $ 2^0, 2^1, 2^1, \cdots $，变成多个背包，令大小为 $ i $ 的子树有 $ cnt_i $ 个，最后的复杂度大概是一个 $ O(n\sum \log cnt_i) $，这个东西大概使介于 $ O(n\log n) $ 和 $ O(n\sqrt{n}) $ 之间的，具体证明我也不知道应该怎么证，感性理解一下吧。

然后发现复杂度依然不正确，考虑把这个数组压成一个 `bitset`，这样在进行或运算的时候还可以大幅降低速度，最终是 $ O(\dfrac{n\sqrt{n}}{\omega}) $，此处的 $ \omega $ 一般为 $ 32 $，显然可以通过。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/extc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;
using namespace __gnu_pbds;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template<typename T = int>
inline T read(void);

struct Edge{
    Edge* nxt;
    int to;
    OPNEW;
}ed[510000];
ROPNEW(ed);
Edge* head[260000];

int N;
int siz[260000], msiz[260000], rt(0);
void dfs(int p, int fa = -1){
    msiz[p] = 0;
    siz[p] = 1;
    for(auto i = head[p]; i; i = i->nxt){
        if(SON == fa)continue;
        dfs(SON, p);
        siz[p] += siz[SON];
        msiz[p] = max(msiz[p], siz[SON]);
    }
    msiz[p] = max(msiz[p], N - siz[p]);
    if(!rt || msiz[p] < msiz[rt])rt = p;
}
int cnt[260000];
int tot(0);
ll ans(0);
bitset < 260000 > dp;
int main(){
    N = read();
    for(int i = 1; i <= N - 1; ++i){
        int s = read(), t = read();
        head[s] = new Edge{head[s], t};
        head[t] = new Edge{head[t], s};
    }
    dfs(1);
    dfs(rt);
    for(int i = 1; i <= N; ++i)if(i != rt)ans += siz[i];
    for(auto i = head[rt]; i; i = i->nxt)cnt[siz[SON]]++;
    for(int i = 1; i <= N / 2; ++i)while(cnt[i] > 2)cnt[i] -= 2, cnt[i * 2]++;
    dp[0] = true;
    for(int i = 1; i <= N; ++i)while(cnt[i]--)dp |= dp << i;
    for(int i = N / 2; i >= 0 ; --i)if(dp[i]){ans += (ll)i * (N - i - 1); break;}
    printf("%d %lld\n", N - 1, ans);

    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template<typename T>
inline T read(void){
    T ret(0);
    short flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_09_28 初稿

---

## 作者：lhm_ (赞：3)

先考虑最小值，因为树是二分图，所以可以进行黑白染色，将其分成左右部图，让左部图向右部图连边即可构造最小值，为 $n-1$。

对于最大值，最优情况一定是以一个点为中心，其各个子树内边的状态为要么该点能到达子树内的每个点，即外向，要么子树内的每个点能到达该点，即内向，且该点为树的重心。

可以简单的进行证明。考虑边的状态让这棵树有了两个上面描述的中心，两个中心之间的路径上一半的边指向第一个中心，一半的边指向第二个中心。发现若这条路径边的方向只指向一个中心，答案会更优，所以就将这两个中心合并为一个，同理，若存在多个中心，合并为一个会更优。因为中心的各个子树的外向个数和内向个数会乘起来贡献给答案，所以中心选取树的重心可以更好的分配外向内向的子树大小。

考虑将中心的各个子树分为外向和内向两个集合，两个集合大小越接近 $\frac{n}{2}$ 越优。可以通过二进制拆分来优化这个多重背包问题，因为只用考虑存在性，所以也采用 $bitset$ 来优化。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 500010
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,root;
ll ans;
int siz[maxn],ma[maxn],cnt[maxn];
bitset<maxn> s;
struct edge
{
    int to,nxt;
}e[maxn];
int head[maxn],edge_cnt;
void add(int from,int to)
{
    e[++edge_cnt]=(edge){to,head[from]};
    head[from]=edge_cnt;
}
void dfs(int x,int fa)
{
    siz[x]=1;
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(y==fa) continue;
        dfs(y,x),siz[x]+=siz[y];
        ma[x]=max(ma[x],siz[y]);
    }
    ma[x]=max(ma[x],n-siz[x]);
    if(ma[x]<ma[root]) root=x;
}
int main()
{
    read(n),ma[0]=n;
    for(int i=1;i<n;++i)
    {
        int x,y;
        read(x),read(y);
        add(x,y),add(y,x);
    }
    dfs(1,0),dfs(root,0);
    for(int i=1;i<=n;++i) ans+=siz[i]-1;
    for(int i=head[root];i;i=e[i].nxt) cnt[siz[e[i].to]]++;
    for(int i=1;i<=n;++i)
        while(cnt[i]>2)
            cnt[i]-=2,cnt[i*2]++;
    s[0]=1;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=cnt[i];++j)
            s|=s<<i;
    for(int i=n/2;i;--i)
    {
        if(!s[i]) continue;
        printf("%d %lld\n",n-1,ans+(ll)i*(n-i-1));
        break;
    }
    return 0;
}
```

---

## 作者：kczno1 (赞：3)

这题两个答案都有一个结论。(第一个很显然，第二个我也不会证啊)

最小值就是下一层全部是上一层的相反方向，就是n-1。

最大值就是选择重心，其他点都和他联通。

之后让到达根的个数和根到达的个数尽量接近。

那这就是一个容量=价值的01背包问题。

首先我们可以用bitset优化，O(n^2/32)。

由于他的物品总体积和物品数是同阶的，都是n，

我们如果把相同体积的物品当做一个体积物品有多个，那么物品种类数就是根号(n)的，

因为最差就是1,2,..n。

这时用多重背包优化，时间O(n根号(n))。

如果用二进制优化，当一个种类的物品数量>2时不断-2，那么物品总数就是根号(n)的，

这时再用bitset优化，时间O(n根号(n)/32)。

而且由于stl有bitset，实现很方便。

```cpp
#include<bitset>
#include<cstdio>
#include<algorithm>
using std::bitset;using std::max;

const int N=250010;
typedef long long ll;
int n,i,x,y;
int t[N];
struct edge
{
    int to,next;
}l[N<<1];int e;
void add_e(int x,int y)
{
    l[++e]=(edge){y,t[x]};t[x]=e;
}

int fa[N],q[N],head,tail,sz[N];
int bfs(int x)
{
    q[tail=1]=x;fa[x]=0;
    for(head=1;head<=tail;++head)
    {
        x=q[head];sz[x]=1;
        for(i=t[x];y=l[i].to;i=l[i].next)
        if(y!=fa[x])
         fa[q[++tail]=y]=x;
    }
    for(i=tail;x=q[i];--i) sz[fa[x]]+=sz[x];
    int need=tail+1>>1;
    for(i=tail;x=q[i];--i)
    if(sz[x]>=need) return x;
}

bitset<N>a;

int main()
{
    freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    scanf("%d",&n);
    for(i=1;i<n;++i)
    {
        scanf("%d%d",&x,&y);
        add_e(x,y);add_e(y,x);
    }
    int rt=bfs(1);
    bfs(rt);
    
    ll ans=0;
    for(i=1;i<=n;++i) ans+=sz[i]-1;
    
    for(i=1;i<=n;++i) q[i]=0;
    for(i=t[rt];y=l[i].to;i=l[i].next) ++q[sz[y]];

    for(i=1;i<=n;++i)
    while(q[i]>2) {q[i]-=2;++q[i<<1];}
    
    a[0]=1;
    for(i=1;i<=n;++i)
    while(q[i]--) a|=a<<i;
    
    for(i=n>>1;!a[i];--i); 
    printf("%d %lld\n",n-1,ans+(ll)i*(n-1-i)); 
}
```

---

## 作者：DYYqwq (赞：2)

### [P3563 [POI2013] POL-Polarization](https://www.luogu.com.cn/problem/P3563)

有两问。一问是问最小是多少。那么自然是  $n-1$。如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/asggjya7.png)

自然的，一直向上指即可。

考虑最大怎么算。

不难想到，自然是围绕树重心进行的。

![](https://cdn.luogu.com.cn/upload/image_hosting/jsb2of3v.png)

如图所示，$1$ 节点为重心。

显然它拥有许多子树，每个子树都可以选择是指向重心或是被重心指向。

我们现在要做的是尽量让指向重心的子树大小之和于被重心指向的子树大小之和几乎相等。

于是变成 0/1 背包问题。

但是考虑一个菊花图，自然如果针对每一个子树作为一个物品，直接炸掉。

考虑可以把两个子树合在一起，这样就变成了类似多重背包的操作（这里感性理解一下，就是相同体积可以视为一种物品）。

因此可以进行二进制优化以及 `bitset` 优化。

考虑到这东西其实本质不劣，没有 `bitset` 最差就是 $O(n\sqrt{n})$，于是有一个 $\frac{1}{32}$ 的常数自然能过。

其实还是很简单嘛，下次不要做不出来了噢 qwq

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int to , nxt;
}e[500010];
int n , tot , head[250010] , root , ans , sz[250010] , mxsz[250010] , cnt[250010];
bitset<250010> dp;
void add(int u , int v)
{
	++ tot;
	e[tot].to = v;
	e[tot].nxt = head[u];
	head[u] = tot;
}
void dfs(int u , int fa)
{
	mxsz[u] = 0 , sz[u] = 1;
	for(int i = head[u] ; i != 0 ; i = e[i].nxt)
	{
		int v = e[i].to;
		if(v == fa) continue;
		dfs(v , u);
		sz[u] += sz[v] , mxsz[u] = max(mxsz[u] , sz[v]);
	}
	mxsz[u] = max(mxsz[u] , n - sz[u]);
	if(root == 0 || mxsz[u] < mxsz[root]) root = u;
}
signed main()
{
	scanf("%lld" , &n);
	for(int i = 1 , u , v ; i < n ; i ++) scanf("%lld%lld" , &u , &v) , add(u , v) , add(v , u);
	dfs(1 , 0) , dfs(root , 0);
//	printf("root:%lld" , root);
	ans = -sz[root];
	for(int i = 1 ; i <= n ; i ++) ans += sz[i];
	for(int i = head[root] ; i != 0 ; i = e[i].nxt) cnt[sz[e[i].to]] ++;
	for(int i = 1 ; i <= n / 2 ; i ++) while(cnt[i] > 2) cnt[i] -= 2 , cnt[i << 1] ++;
	dp[0] = 1;
	for(int i = 1 ; i <= n ; i ++) while(cnt[i] --) dp |= (dp << i);
	int pos;
	for(int i = n / 2 ; i >= 0 ; i --) if(dp[i]){pos = i;break;}
//	printf("pos:%lld\n" , pos);
	printf("%lld %lld" , n - 1 , ans + pos * (n - pos - 1));
	return 0;
}
```

---

## 作者：xxxxxzy (赞：0)

对于点对的最小值，考虑把树二分图染色，然后全部从黑点往白点连边，这样可以达到构造下界 $n-1$。

对于点对的最大值，感性理解，应该选择一个点 $u$，然后一些子树是内向子树，一些子树是外向子树。

考虑简证一下为什么这个构造是对的，假设存在两个中心 $(u,v)$，以 $u$ 为根，首先如果 $u \to v$ 不成立那么一定不优，如果 $v$ 存在子树 $w$ 使得 $w \to v$，那么调整成 $v \to w$ 一定不劣，而这样 $v$ 就不能说成为一个中心，换句话说只有一个中心。

选重心应该是最优的，构造应该是把重心的子树划分成两组，使两组的大小尽可能接近，这个用多重背包做一下，bitset 优化，时间 $O(\dfrac{n \sqrt n}{w})$，这里的根号是因为多重背包给权值去了重。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<ll, ll>
#define mp make_pair
#define pb push_back
#define ld lower_bound
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define drep(i, a, b) for (int i = (a); i >= (b); i--)
#define ud upper_bound
#define mem(s, k) memset(s, k, sizeof(s))
#define fi first
#define se second
#define ull unsigned long long
#define vec vector <int>
#define fv inline void
#define fn inline static
#define cmin(x,y) (x=min(x,y))
#define cmax(x,y) (x=max(x,y))
using u16 = unsigned short; using u32 = unsigned; using u64 = unsigned ll; using u128 = __uint128_t;
using i16 = short; using i32 = ll; using i64 = ll; using i128 = __int128_t;
using db = double;
using namespace std;
const i32 N = 2.5e5 + 5;
i32 ans, n, u, v, rt, num[N], siz[N], mx[N];
vec G[N];
bitset <N> S;
fv findrt(i32 u, i32 fa) {
  siz[u] = 1, mx[u] = -1e9;
  for (i32 v : G[u]) {
    if (v == fa) continue;
    findrt(v, u);
    siz[u] += siz[v];
    mx[u] = max(mx[u], siz[v]);
  }
  mx[u] = max(mx[u], n - siz[u]);
  if (mx[rt] > mx[u]) rt = u;
}
int main() {
  cin >> n, mx[0] = 1e9;
  rep (i, 1, n - 1) cin >> u >> v, G[u].pb(v), G[v].pb(u);
  findrt(1, 0), findrt(rt, 0);
  rep (i, 1, n) ans += siz[i] - 1;
  for (i32 v : G[rt]) num[siz[v]]++;
  rep (i, 1, n) while (num[i] > 2) num[i * 2]++, num[i] -= 2;
  S[0] = 1;
  rep (i, 1, n) rep (j, 1, num[i]) S |= (S << i);
  drep (i, n / 2, 1) {
    if (S[i]) return cout << n - 1 << " " << ans + 1ll * i * (n - i - 1) << "\n", 0;
  }
}
```

---

