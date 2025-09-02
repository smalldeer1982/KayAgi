# Lunar New Year and Red Envelopes

## 题目描述

新年就要到啦，Bob打算去要很多红包！不过要红包是一件很费时间的事情。

我们假设从第$1$秒开始共有$n$秒，第$i$个红包可以在第$s_i$到$t_i$秒（包括端点）收集，并且其中有$w_i$元。如果Bob拿了第$i$个红包，那么他直到第$d_i$秒后（不包括$d_i$）才可以继续收集红包。其中$s_i \leq t_i \leq d_i$.

Bob是一个贪心的人，他贪心地收集红包：如果他在第$x$秒有红包可以收集，他就会选择其中钱最多的那个红包。如果这样的红包有多个，他就选$d$**最大**的那个红包。如果还是有多个选择，他就随便拿一个。

然而他的女儿Alice并不想他的爸爸拿到太多钱。她可以干扰Bob最多$m$次。如果Alice在第$x$秒干扰Bob，在这一秒Bob就不能收集红包，然后下一秒Bob会继续用自己的策略收集。

现在请你求出如果Alice采用最优的策略，Bob能拿到的最少钱数。

## 样例 #1

### 输入

```
5 0 2
1 3 4 5
2 5 5 8
```

### 输出

```
13```

## 样例 #2

### 输入

```
10 1 6
1 1 2 4
2 2 6 2
3 3 3 3
4 4 4 5
5 5 5 7
6 6 6 9
```

### 输出

```
2```

## 样例 #3

### 输入

```
12 2 6
1 5 5 4
4 6 6 2
3 8 8 3
2 9 9 5
6 10 10 7
8 12 12 9
```

### 输出

```
11```

# 题解

## 作者：花里心爱 (赞：15)

一道非常duliu的dp题。

题意要求我们求出选择最多$m$个时间点打扰Bob（强制让他在某个时间点不能行动）后，Bob按照他的策略捡取红包，能够得到的金币最小值。

首先我们先不考虑$m$次操作和Bob在整个过程中的策略。

考虑在某一个时间点$x$，如果Bob能够行动，那么在这个时间存在的红包（即$x \in [s_i, t_i]$）一定没有被选取。这是因为$s_i \le t_i \le d_i$，也就是如果Bob收集了某个红包，他恢复行动的时间一定在这个红包消失之后。反过来，如果他在这个时间点能行动，这个红包一定还没有被选取。

所以我们可以预处理一下如果Bob在某个时间点能行动，他能够得到的金币数量和他下一步行动的时间位置。

设$g[i]$为下一步行动的时间，$h[i]$为这一步行动能够得到的金币，我们先把所有红包按左端点排序，然后从$1$到$n$把所有时间点扫一遍，按照Bob的策略用一个优先队列模拟即可。注意队列为空的情况，此时$g[i] = i+1, h[i] = 0$（因为Bob什么也干不了）。

然后考虑dp。设$f[i][j]$为在第$i$个时间点，已经用了$j$次机会的方案数（因为状态只与时间和选择打扰Bob的次数有关）。

注意到在某个时间点只有选和不选在这个时间点打扰Bob，所以我们从前面的状态推到后面的状态。如果选的话，那么$f[i+1][j+1] = f[i][j]$。否则，$f[g[i]][j] = f[i][j] + h[i]$。最后的状态会推到时间点$n+1$。

因为$m$次机会不一定会用完（而且题面没有保证$m \le n$， 所以$m$有可能无法用完），所以最终答案为$\min_{0 \le j \le m} \{f[n+1][j]\}$。

代码如下：
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define maxn 100005
#define int long long

int n, m, k;
struct node {
    int s, t, d, w;
    bool operator<(const node &x)const {
    	// 在优先队列里的排序方式
    	// 注意 std::priority_queue 是大根堆，所以排序要反过来qwq
        if(w == x.w) return d < x.d;
        return w < x.w;
    }
}e[maxn];

bool cmp(node x, node y) {
	// 为了方便预处理，先把所有红包按照左端点排序
    return x.s < y.s;
}

std::priority_queue<node> q;
int g[maxn], h[maxn];
int f[maxn][205];

signed main() {
    scanf("%I64d%I64d%I64d", &n, &m, &k);
    for(int i = 1; i <= k; ++i)
        scanf("%I64d%I64d%I64d%I64d", &e[i].s, &e[i].t, &e[i].d, &e[i].w);
    
    std::sort(e+1, e+k+1, cmp);
    int cur = 1;
    g[0] = 1;
    for(int i = 1; i <= n; ++i) {
        while(cur <= k && e[cur].s <= i)
            q.push(e[cur++]);
        if(q.empty()) g[i] = i+1;
        else {
            node u = q.top();
            if(u.t < i) {
            	// 当前元素已经过时
                --i;
                q.pop();
                continue;
            }
            g[i] = u.d+1;
            h[i] = u.w;
        }
    }

    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0; // 状态边界
    for(int i = 0; i <= n; ++i)
    for(int j = 0; j <= m; ++j) {
        f[i+1][j+1] = std::min(f[i+1][j+1], f[i][j]);
        f[g[i]][j] = std::min(f[g[i]][j], f[i][j] + h[i]);
    }

    int ans = 0x3f3f3f3f3f3f3f3fll;
    for(int i = 0; i <= m; ++i)
        ans = std::min(ans, f[n+1][i]);
    printf("%I64d", ans);
    return 0;
}
```

---

## 作者：Katsura_Hinagiku (赞：5)

正序dp。。。其实也不是特别难（~~虽然考试时调了2h+~~）

仔细想想就会发现每一个时间要拿的红包是固定的。只要预处理出每一个时间要拿的红包，dp部分也不是特别难，考虑当前时间捣乱或不捣乱两种情况即可。

```cpp
#include<bits/stdc++.h>//万能头文件
#define ll long long
using namespace std;
const ll INF=(1LL<<62);
struct node
{
	int s,t,d;
	ll w;
	node()
	{
	}
	bool operator <(node x)const
	{
		if(w!=x.w)return w>x.w;
		return d>x.d;
	}//重载小于号，使得multiset的第一个元素就是当前要拿的红包
}a[100029];
ll f[100029][205];//f[i][j]：到了第i秒，用了j次捣乱机会的最少钱数 
vector<node>bg[100029],en[100029];//存进队出队的时间 
multiset<node>q;//找当前时间应该拿的红包 
int n,m,k;
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	memset(f,127,sizeof(f));
	for(int i=1;i<=k;++i)
	{
		scanf("%d%d%d%lld",&a[i].s,&a[i].t,&a[i].d,&a[i].w);
		bg[a[i].s].push_back(a[i]);
		en[a[i].t+1].push_back(a[i]);
	}
	for(int i=0;i<=m;++i)
	{
		f[i][i]=0;
	}
	f[1][0]=0;
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<(int)bg[i].size();++j)
		{
			q.insert(bg[i][j]);
		}
		for(int j=0;j<(int)en[i].size();++j)
		{
			q.erase(q.find(en[i][j]));
		}
		node temp;
		if(q.empty())
		{
			temp.d=i;
			temp.w=0;
		}//如果没有可以拿的红包，就跳过 
		else
		{
			temp=*q.begin();
		}//有可以拿的红包，就拿 
		for(int j=0;j<min(m,i);++j)
		{
			f[i+1][j+1]=min(f[i+1][j+1],f[i][j]);//使用一次捣乱机会，拿不到该红包
		}
		for(int j=0;j<=min(m,i);++j)
		{
			f[temp.d+1][j]=min(f[temp.d+1][j],f[i][j]+temp.w);//拿到该红包 
		}
	}
	ll ans=INF;
	for(int j=0;j<=m;++j)
	{
		ans=min(ans,f[n+1][j]);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：DPair (赞：2)

提供一种记忆化搜索的写法。

~~反正记搜本质上也就是dp。~~

~~主要是记搜好懂好写。~~

## 【思路】
首先由于 $s_i \leq t_i \leq d_i$ 。我们不用考虑 **一个物品被选之后不能再被选** 的情况（如果这是你看题解的原因你就可以回去了）。

然后那么每个点 **如果能选** ，那么被选的红包就一定是固定的（因为不受影响）。

考虑用线段树维护每一个点如果被选，会选哪一个红包。

这就是一个区间推平，先以 $w$ 为第一关键字， $d$ 为第二关键字排序即可。（当然也可以用 $ODT$ 什么的，反正我用的是线段树）

然后就可以考虑记搜了。

让 $dp[i][j]$ 表示第 $i$ 秒可以拿红包，且还有 $j$  次操作的机会，能够拿到的最少价值。

那么讨论两种情况，一种是这个节点不让拿，消耗一次机会到下一秒，另一种是拿，不消耗机会到第 $d+1$ 秒。

得到方程：

$$
dp[i][j]=min(dp[i+1][j-1],dp[d_i+1][j]+w_i)
$$

考虑搜索的边界条件。

首先机会不能消耗成负数，所以 $j<0$ 时返回一个极大值。

其次第 $n$ 秒以后显然收获不到任何红包，所以 $i>n$ 时返回 $0$ 。

然后如果这一秒没有红包，那么就直接到下一秒，即 $w_i=0$ 时 $dp[i][j]=dp[i+1][j]$

做完了。

## 【代码】

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair <int, int> pi;
//以下是快读可以不看
template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}

int n, m, k;

//以下是红包
struct Redbag{
    int l, r;
    int val, d;
    inline bool operator < (const Redbag &tmp) const{
        return val < tmp.val || (val == tmp.val && d < tmp.d);
    }
}q[100005];

//以下是线段树
pi t[400005], lazy[400005], a[100005];

inline void pushup(int rt){
    if(t[rt << 1] != t[rt << 1 | 1]) t[rt] = make_pair(0, 0);
    else t[rt] = t[rt << 1];
}

inline void update(int rt, pi z){
    t[rt] = z;
    lazy[rt] = z;
}

inline void pushdown(int rt){
    if(lazy[rt].first){
        update(rt << 1, lazy[rt]);
        update(rt << 1 | 1, lazy[rt]);
        lazy[rt] = make_pair(0, 0);
    }
}

#define LSON rt << 1, l, mid
#define RSON rt << 1 | 1, mid + 1, r

void modify(int rt, int l, int r, int x, int y, pi z){
    if(x <= l && r <= y) return update(rt, z);
    pushdown(rt);
    int mid = (l + r) >> 1;
    if(x <= mid) modify(LSON, x, y, z);
    if(y > mid) modify(RSON, x, y, z);
    pushup(rt); 
}

pi query(int rt, int l, int r, int x){
    if(t[rt].first) return t[rt];
    if(l == r && l == x) return t[rt];
    pushdown(rt);
    int mid = (l + r) >> 1;
    if(x <= mid) return query(LSON, x);
    else return query(RSON, x);
}

//以下是短到极致的记搜

LL dp[100005][205];

LL dfs(int x, int y){
    if(y < 0) return 0x3f3f3f3f3f3f3f3f;
    if(x > n) return 0;
    if(~dp[x][y]) return dp[x][y];
    if(!a[x].first) return dp[x][y] = dfs(x + 1, y);
    return dp[x][y] = min(dfs(x + 1, y - 1), dfs(a[x].second + 1, y) + a[x].first);
}


int main(){
    read(n);read(m);read(k);
    for (register int i = 1;i <= k;i ++){
        read(q[i].l);read(q[i].r);
        read(q[i].d);read(q[i].val);
    }
    //以下是区间推平操作
    sort(q + 1, q + k + 1);
    for (register int i = 1;i <= k;i ++) modify(1, 1, n, q[i].l, q[i].r, make_pair(q[i].val, q[i].d));
    for (register int i = 1;i <= n;i ++) a[i] = query(1, 1, n, i);
    //以下是记搜
    memset(dp, -1, sizeof(dp));
    fprint(dfs(1, m), 10);
    return 0;
}
```

---

## 作者：zhaotiensn (赞：2)

~~本以为这场Div.2挺水的，是个涨分的好机会，结果竟然因为评测机卡爆变成了unrated的,然后就没有动力做题了，导致我这题竟然调了好久。。~~

因为$s_i>=t_i>=d_i$，导致这个一旦选了，所以不管这个选不选都是不会干扰后面的。然后就可以考虑把$Bob$在某一个时刻要选的全部预处理出来，跑一个dp好了。

预处理一开始写了$O(nk)$的，果然光荣的超时了(考的是一直以为是常数不够优秀的缘故，写题解的时候才发现k是和n一个规模的，不是和m一个规模。。)，然后就改成了$O(klogn)$的线段树。因为不会打取$Min$的线段树，所以要先把红包按照优先级排好序，然后从低到高直接覆盖$s_i$到$t_i$的区间，这样线段树只要支持区间覆盖，单点查询就好了。

$dp$应该是算是比较水的。我是倒着跑的，$f[i][j]$表示从第$i$个时刻开始，再使用$j$次干扰，能获得的最小钱数。$(f[i][j]=min(f[i+1][j-1],f[d[i]+1][j]+w[i]))$

然后代码:
```cpp
#include <bits/stdc++.h>

#define ll long long
#define Max 100005

using namespace std;

inline char gc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define gc getchar
inline ll read(){
    ll x=0;char ch=gc();bool positive=1;
    for(;!isdigit(ch);ch=gc())if(ch=='-')positive=0;
    for(;isdigit(ch);ch=gc())x=x*10+ch-'0';
    return positive?x:-x;
}

inline void write(ll x){
    if(x<0)x=-x,putchar('-');
    if(x>9)write(x/10);putchar(x%10+'0');
}

inline void writeln(ll x){
    write(x);puts("");
}
//以上是在这题中毫无用处的快读快输
struct Node{
    ll s,t,d,w;
}a[Max];
//a用来存红包
struct Segment{
    ll l,r,w,d,id;
    inline bool operator<(const Segment x)const{
        if(w!=x.w)return w<x.w;
        return d<x.d;
    }
}b[Max];

struct Tree{
    ll l,r,id,lazy;
}st[Max*4];

ll n,m,k,size,num[Max],f[Max][205];

inline void build(ll node,ll l,ll r){
    st[node].l=l;st[node].r=r;
    if(l==r){
        st[node].id=0;
        return;
    }
    ll mid=(l+r)>>1;
    build(node<<1,l,mid);
    build(node<<1|1,mid+1,r);
    return;
}

inline void push(ll node){
    if(!st[node].lazy)return;
    st[node<<1].id=st[node<<1|1].id=st[node<<1].lazy=st[node<<1|1].lazy=st[node].lazy;
    st[node].lazy=0;
    return;
}

inline void change(ll node,ll l,ll r,ll x){
    if(st[node].l>r||st[node].r<l)return;
    if(st[node].l>=l&&st[node].r<=r){
        st[node].lazy=x;
        st[node].id=x;
        return;
    }
    push(node);
    change(node<<1,l,r,x);
    change(node<<1|1,l,r,x);
    return;
}

inline ll query(ll node,ll x){
    if(st[node].l==st[node].r)return st[node].id;
    ll mid=(st[node].l+st[node].r)>>1;
    push(node);
    if(x<=mid)return query(node<<1,x);
    return query(node<<1|1,x);
}
//略显鬼畜的线段树
int main(){
    n=read();m=read();k=read();
    build(1,1,n);
    for(int i=1;i<=k;i++){
        a[i].s=read();a[i].t=read();a[i].d=read();a[i].w=read();
        b[i].l=a[i].s;b[i].r=a[i].t;b[i].d=a[i].d;b[i].w=a[i].w;b[i].id=i;
    }
    sort(b+1,b+k+1);
    for(int i=1;i<=k;i++){
        change(1,b[i].l,b[i].r,b[i].id);
    }//排序之后直接用区间覆盖单点查询的线段树
    for(int i=1;i<=n;i++){
        num[i]=query(1,i);
    }//num[i]存时刻i选什么(其实完全不用存)
    for(int i=n;i>=1;i--){
        if(!num[i]){
            for(int j=0;j<=m;j++){
                f[i][j]=f[i+1][j];
            }
            continue;
        }
        f[i][0]=f[a[num[i]].d+1][0]+a[num[i]].w;
        for(int j=1;j<=m;j++){
            f[i][j]=min(f[i+1][j-1],f[a[num[i]].d+1][j]+a[num[i]].w);
        }
    }//简单的dp
    writeln(f[1][m]);
    // f[i][j]=min(f[i+1][j-1],f[d[i]+1][j]+w[i]);
    return 0;
}


```

---

## 作者：HC20050615 (赞：1)

由于 $s_i \le t_i \le d_i$，所以当 Bob 在某个时间点可以行动时，该时间可取的所有红包一定没有被选。因此，我们可以直接求出每个时间点若能行动，可以得到的钱数 $c_i$ 和下一个可以行动的时间 $to_i$。

然后我们直接 DP。设 $f[i][j]$ 表示当前到了时间 $i$（ 还没行动），已经用了 $j$ 次干扰。因为干扰的次数不一定要用完，所以我们要统计所有 $f[n+1][j]$，找到最小值，就是答案。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() 
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9') 
	{
		c=getchar();
	}
	while(c>='0'&&c<='9') 
	{
		x=x*10+(c^48);
		c=getchar();
	}
	return x;
}
int n,m,k;
struct red_bag{
	int s,e;
	int w;
	int d;
}a[100005];
int c[100005];
int to[100005];
long long f[100005][205];
inline bool cmp(red_bag a,red_bag b)
{
	return a.s<b.s;
}
struct com{
	bool operator()(const int x,const int y)
	{
		if(a[x].w==a[y].w)
		{
			return a[x].d<a[y].d;
		}
		return a[x].w<a[y].w;
	}
};
priority_queue<int,vector<int>,com>q;
int main()
{
	n=read();
	m=read();
	k=read();
	for(int i=1;i<=k;i++)
	{
		a[i].s=read();
		a[i].e=read();
		a[i].d=read()+1;
		a[i].w=read();
	}
	sort(a+1,a+k+1,cmp);
	for(int i=1,j=1;i<=n;i++)
	{
		while(j<=k&&i==a[j].s)
		{
			q.push(j++);
		}
		while((!q.empty())&&a[q.top()].e<i)
		{
			q.pop();
		}
		if(q.empty())
		{
			to[i]=i+1;
		}
		else
		{
			int t=q.top();
			c[i]=a[t].w;
			to[i]=a[t].d;
		}
	}
	memset(f,127/3,sizeof(f));
	f[0][0]=0;
	to[0]=1;
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			f[to[i]][j]=min(f[to[i]][j],f[i][j]+c[i]);
			f[i+1][j+1]=min(f[i+1][j+1],f[i][j]);
		}
	}
	long long mins=1e18;
	for(int i=0;i<=m;i++)
	{
		mins=min(f[n+1][i],mins);
	}
	cout<<mins<<endl;
	return 0;
}
```


---

## 作者：Elma_ (赞：1)

> [CF1106E Lunar New Year and Red Envelopes](https://www.luogu.com.cn/problem/CF1106E)

首先根据题面可以知道，每一秒钟如果 Bob 有红包可以收集，那么 Bob 所收集的红包的 $d$ 和 $w$ 是固定的。所以可以先预处理出每一秒 Bob 会选取的红包，这个东西好像有各种数据结构都可以搞，这里用的是堆。

然后考虑 dp。设 $f_{i,j}$ 为现在在第 $i$ 秒，Alice 干扰了 $j$ 次之后 Bob 所能获得的最小钱数。根据定义有转移如下：

- 干扰：$f_{i,j} \to f_{i+1,j+1}$；
- 不干扰： $f_{i,j} + w_i \to f_{d_i+1, j}$；

还要特判一种情况，即虽然 Alice 这一秒没有干扰，但这一秒也没有红包可供 Bob 收集。转移为： $f_{i,j} \to f_{i+1,j}$。边界为 $f_{0,0}=0$，答案为 $\max\{f_{n+1,i}\}$。

```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

inline int read() {
	int x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}

const int maxn = 1e5 + 5;
const int maxm = 200 + 5;

struct redbag { 
	int s, t, d, w; 
} a[maxn];
bool operator <(redbag a, redbag b) {
	return a.w > b.w || (a.w == b.w && a.d > b.d);
}
bool operator >(redbag a, redbag b) { return b < a; }
inline ll min(ll x, ll y) { return x < y ? x : y; }
inline ll max(ll x, ll y) { return x > y ? x : y; }
inline bool cmp(redbag a, redbag b) { return a.s < b.s; }
priority_queue<redbag, vector<redbag>, greater<redbag>> q;
int n, m, k; ll ans;
int d[maxn], w[maxn];ll f[maxn][maxm];

int main(void) {
	n = read(), m = read(), k = read();
	for (int i = 1;i <= k;i++) {
		a[i].s = read(), a[i].t = read(), a[i].d = read(), a[i].w = read();
	}
	sort(a + 1, a + k + 1, cmp);
	for (int i = 1, j = 0;i <= n;i++) {
		while (j < k && a[j + 1].s <= i) q.push(a[++j]);
		while (!q.empty() && q.top().t < i) q.pop();
		if (!q.empty()) d[i] = q.top().d, w[i] = q.top().w;
	}
	memset(f, 0x3f, sizeof(f)), f[0][0] = 0;
	for (int i = 0;i <= n;i++) {
		for (int j = 0;j <= m;j++) {
			f[i + 1][j + 1] = min(f[i + 1][j + 1], f[i][j]);
			if (d[i]) f[d[i] + 1][j] = min(f[d[i] + 1][j], f[i][j] + w[i]);
			else f[i + 1][j] = min(f[i + 1][j], f[i][j]);
		}
	}
	ans = 2e18;
	for (int i = 0;i <= m;i++) ans = min(ans, f[n + 1][i]);
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：Forg1weN (赞：0)

[题面](https://www.luogu.com.cn/problem/CF1106E)

对于时间点 $i$ 而言，其取到的红包是固定的，想清楚这点就很简单了。

考虑到 $s_i \le t_i \le d_i$，故一个红包不会被重复取到。

记 $f_{i,j}$ 表示在时刻 $i$ 还没有开始取红包时用了 $j$ 次干扰的最小价值。

记当前时刻 $i$ 能取到的红包为 $x$，则有转移：

$$f_{i+1,j+1}=\min(f_{i,j})$$

$$f_{d_x+1,j}=\min(f_{i,j}+val_x)$$

若当前无红包可取，则：

$$f_{i+1,j}=f_{i,j}$$

这里用线段树维护区间修改，单点查询，一个坑点，下传标记的时候要判断当前标记是否比子区间的要优，否则会调一下午，这是因为有可能子区间修改成优的，因为子区间不包含大区间所以大区间没变，大区间下传标记的时候若无特盘会覆盖子区间的优的答案。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define lson now<<1
#define rson now<<1|1
#define mid (l+r)/2
typedef long long LL;
const int maxn=2e5+10;
const int mod =1000000007;
const LL INF =1e17;
int n,m,k;
LL f[100005][205],ans;
int tree[maxn*4],lazy[maxn*4];
struct Data {
	int s,t,d;
	LL val;
}sub[maxn];
void pushdown(int now) {
	if(lazy[now])  {
		if(sub[tree[lson]].val<sub[tree[now]].val)
			tree[lson]=lazy[lson]=tree[now];
		if(sub[tree[lson]].val==sub[tree[now]].val&&sub[tree[lson]].d<sub[tree[now]].d)
			tree[lson]=lazy[lson]=tree[now];
		if(sub[tree[rson]].val<sub[tree[now]].val)
			tree[rson]=lazy[rson]=tree[now];
		if(sub[tree[rson]].val==sub[tree[now]].val&&sub[tree[rson]].d<sub[tree[now]].d)
			tree[rson]=lazy[rson]=tree[now];
		lazy[now] =0;
	}
}
void update(int now,int l,int r,int x,int y,int id) {
	if(y<l || r<x)return;
	if(x<=l && r<=y) {
		if(sub[tree[now]].val<sub[id].val) {
			tree[now]=id,lazy[now]=id;
			return;
		}
		if(sub[tree[now]].val==sub[id].val) 
			if(sub[tree[now]].d<sub[id].d) {
				tree[now]=id,lazy[now]=id;
				return;
			}
		return;
	}
	pushdown(now);
	update(lson,l,mid,x,y,id);
	update(rson,mid+1,r,x,y,id);
}
int query(int now,int l,int r,int x) {
	if(l==r)return tree[now];
	pushdown(now);
	if(x<=mid)return query(lson,l,mid,x);
	else return query(rson,mid+1,r,x);
}
signed main() {
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++) {
		scanf("%d%d%d%lld",&sub[i].s,&sub[i].t,&sub[i].d,&sub[i].val);
		update(1,1,n,sub[i].s,sub[i].t,i);
	}
	memset(f,127,sizeof(f));
	ans=f[1][0];
	f[1][0]=0;
	for(int i=0;i<=n;i++) {
		int to=query(1,1,n,i);
		for(int j=0;j<=m;j++) {
			f[i+1][j+1]=min(f[i+1][j+1],f[i][j]);
			if(to)f[sub[to].d+1][j]=min(f[sub[to].d+1][j],f[i][j]+sub[to].val);
			else f[i+1][j]=min(f[i+1][j],f[i][j]);
		}
	}
	for(int i=0;i<=m;i++)
		ans=min(ans,f[n+1][i]);
	printf("%lld",ans);
	return 0;
} 
```


---

## 作者：Find_Yourself (赞：0)

小清新 DP 题。

定义 $f_{i,j}$ 表示在时刻 $i$，干扰了 $j$ 次，最小贡献。

定义 $nex_i$ 表示在时刻 $i$ 会收集哪个红包。

那么转移方程为：

$$f_{d_{nex_i}+1,j}=\min(f_{i,j}+w_{nex_i})$$

$$f_{i+1,j+1}=\min(f_{i,j})$$

其中，$f_{1,0}=0$，$ans=\min\limits_{j=0}^{m}f_{n+1,j}$。$d_{nex_i}+1$ 为选完编号为 $w_{nex_i}$ 的红包后会跳到那个位置。

现在考虑如何预处理出 $nex_i$。

可以先以 $w$ 为第一关键字，$d$ 为第二关键字从大到小排序。

然后将区间 $[s,t]$ 中的 $nex$ 全部标记为当前编号，之后不再访问。

这里可以用并查集维护已经访问过的区间，遇到访问过的直接查询并查集跳过去即可。

复杂度 $O(nm+n\log n)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e5+5,N2=200+5,inf=LLONG_MAX>>1;
int n,m,k,vis[N],nex[N],fa[N];
ll f[N][N2];
struct node{int s,t,d;ll w;}a[N];
bool cmp(node x,node y){return x.w!=y.w?x.w>y.w:x.d>y.d;}
int ff(int x){return fa[x]==x?x:fa[x]=ff(fa[x]);}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n>>m>>k;
  for(int i=1;i<=k;++i)cin>>a[i].s>>a[i].t>>a[i].d>>a[i].w;
  sort(a+1,a+k+1,cmp);
  for(int i=1;i<=n+1;++i)fa[i]=i;
  for(int i=1;i<=k;++i){
    int j=a[i].s;
    while(j<=a[i].t){
      if(vis[j])j=ff(j);
      else {
        vis[j]=1;
        nex[j]=i;
        fa[ff(j)]=ff(j+1);
        ++j;
      }
    }
  }
  for(int i=1;i<=n+1;++i)for(int j=0;j<=m;++j)f[i][j]=inf;
  f[1][0]=0;
  for(int i=1;i<=n;++i){
    for(int j=0;j<=m;++j){
      f[i+1][j+1]=min(f[i+1][j+1],f[i][j]);
      if(nex[i])f[a[nex[i]].d+1][j]=min(f[a[nex[i]].d+1][j],f[i][j]+a[nex[i]].w);
      else f[i+1][j]=min(f[i+1][j],f[i][j]);
    }
  }
  ll ans=inf;
  for(int j=0;j<=m;++j)ans=min(ans,f[n+1][j]);
  cout<<ans<<endl;
  return 0;
}

```


---

## 作者：hegm (赞：0)

### [Lunar New Year and Red Envelopes](https://www.luogu.com.cn/problem/CF1106E)

md，被诈骗了。

注意条件 $s_i\le t_i\le d_i$，这说明每个时间点只有一种抉择，而不会因为重叠的红包导致抉择出现其他情况。

准确的来说，如果在 $i$ 时刻，`Bob`可以选择红包了。

那么 $i$ 号时间点的最优红包一定还没有被抢，因为如果被抢了，`Bob`会被送到大于 $t_i$ 的时间点，而此时这个红包已经消失了，所以每个时间点只会有一种抉择，并且不会受到`Alice`的影响。

考虑用优先队列维护出每个时间点的抉择 $nxt_i$ 表示抉择之后的下一个时间点，$c_i$ 表示抉择的价值。

$dp_{i,j}$ 表示在 $i$ 号时间点时，阻拦 $j$ 次的最小权值。

转移也很简单

```cpp
dp[nxt[i]][j]=min(dp[nxt[i]][j],dp[i][j]+c[i]);
dp[i+1][j+1]=min(dp[i][j],dp[i+1][j+1]);
```



---

## 作者：fanypcd (赞：0)

设 $f_{i,j}$ 表示前 $i$ 秒，干扰了 $j$ 次，Bob 能收集到的最少钱数。

那么枚举 $f_{i,j}$：

- 如果不选择干扰，如果当前时间没有红包，则转移到 $f_{i+1,j}$，系数为 0，如果有红包，设取的是第 $x$ 个，则转移到 $f_{d_{x} + 1, j}$，系数为 $w_x$。

- 如果选择干扰，则转移到 $f_{i+1,j+1}$，系数为 0。

至于如何维护当前时间选的红包，开一个 multiset，每次取集合中最优的，然后维护一个单调指针 $pos$ 表示随时间增加第一个可能加进来的元素下标，一个优先队列 $q$ 维护当前在 multiset 中结束时间最早的元素，每次时间增加时判断是否需要从 multiset 中删除，或者加入新的元素。

时间复杂度 $O(nm + n \log n)$。

记得开 ```long long```。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
#define inf 0x3f3f3f3f3f3f3f3f
#define N 100005
struct node
{
	int s, t, d, w;
};
bool cmp1(const node &a, const node &b)
{
	return a.s < b.s;
}
struct cmp2
{
	bool operator () (const node &a, const node &b)
	{
		if(a.w != b.w)
		{
			return a.w < b.w;
		}
		return a.d < b.d;
	}
};
struct cmp3
{
	bool operator () (const node &a, const node &b)
	{
		return a.t > b.t;
	}
};
int V, m, n;
node a[N];
int f[N][205];
multiset<node, cmp2> s;
priority_queue<node, vector<node>, cmp3> q;
signed main()
{
	read(V), read(m), read(n);
	for(int i = 1; i <= n; i++)
	{
		read(a[i].s), read(a[i].t), read(a[i].d), read(a[i].w);
	}
	sort(a + 1, a + n + 1, cmp1);
	memset(f, 0x3f, sizeof(f));
	memset(f[0], 0, sizeof(f[0]));
	int pos = 0;
	for(int i = 0; i <= V; i++)
	{
		while(a[pos + 1].s == i)
		{
			s.insert(a[++pos]);
			q.push(a[pos]);
		}
		while(!q.empty() && q.top().t == i - 1)
		{
			s.erase(s.find(q.top()));
			q.pop();
		}
		for(int j = 0; j <= m; j++)
		{
			if(j < m)
			{
				f[i + 1][j + 1] = min(f[i + 1][j + 1], f[i][j]);
			}
			if(s.empty())
			{
				f[i + 1][j] = min(f[i + 1][j], f[i][j]);
			}
			else
			{
				f[(*--s.end()).d + 1][j] = min(f[(*--s.end()).d + 1][j], f[i][j] + (*--s.end()).w);
			}
		}
	}
	int ans = inf;
	for(int i = 0; i <= m; i++)
	{
		ans = min(ans, f[V + 1][i]);
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Memory_of_winter (赞：0)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/10345347.html)

### 题目大意

有$n(n\leqslant10^5)$个时间点，分别为$1\sim n$，有$k(k\leqslant10^5)$个红包，第$i$个红包可以在$[s_i,t_i]$内领取，有钱$w_i$，领了这个红包，直到$d_i$时间点之后（不包含$d_i$）才可以领取下一个红包。

$Bob$按如下规则领红包：

1. 领当前可以领的最大的红包
2. 若有多个，领$d$最大的红包
3. 若还有多个，随机领一个

$Alice$希望$Bob$领的最少，她可以在最多$m(m\leqslant200)$个时间点打扰$Bob$，使得他不能领红包，问$Bob$最少领到多少钱

谁可以告诉我为什么我交翻译的时候LATEX全部出锅了？

### 题解

发现每个时间点$Bob$领的红包是一定的，可以预处理出来，用$set,map$什么的，注意有重复元素，设第$i$个时间点领的红包为$s_i$。

$f_{i,j}$表示打断了$i$次，现在在第$j$个时间点$Bob$领的最少钱数，转移为$f_{i.j}\to f_{i+1,j+1}$，$f_{i,j}+w_{s_j}\to f_{i,d_{s_j}}$。



### C++ Code：

```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#define maxn 100010
typedef std::pair<int, int> PII;
const long long inf = 0x3f3f3f3f3f3f3f3f;
inline void chkmin(long long &a, long long b) { if (a > b) a = b; }

int n, m, k, now = 1, nxt;
long long f[2][maxn], ans = inf;
std::vector<PII> Add[maxn], Del[maxn];
PII Max[maxn];
std::map<PII, int> mp;


int main() {
	std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
	std::cin >> n >> m >> k;
	for (int i = 0, s, t, d, w; i < k; ++i) {
		std::cin >> s >> t >> d >> w;
		Add[s].push_back(std::make_pair(w, d));
		Del[t + 1].push_back(std::make_pair(w, d));
	}
	for (int i = 1; i <= n; ++i) {
		for (PII V : Add[i]) {
			if (mp.count(V)) ++mp[V];
			else mp[V] = 1;
		}
		for (PII V : Del[i]) {
			if (!--mp[V]) mp.erase(V);
		}
		if (mp.size()) Max[i] = (*mp.rbegin()).first;
		else Max[i] = std::make_pair(0, i);
	}

	const int SZ = sizeof f[now];
	__builtin_memset(f[nxt], 0x3f, SZ);
	f[nxt][1] = 0;
	for (int i = 0; i <= m; ++i) {
		std::swap(now, nxt);
		__builtin_memset(f[nxt], 0x3f, SZ);
		f[nxt][1] = 0;
		for (int j = 1; j <= n; ++j) {
			chkmin(f[nxt][j + 1], f[now][j]);
			chkmin(f[now][Max[j].second + 1], f[now][j] + Max[j].first);
		}
		chkmin(ans, f[now][n + 1]);
	}
	std::cout << ans << std::endl;
	return 0;
}

```

---

## 作者：FlyInTheSky (赞：0)

题意：有$k$个区间 $[s_j, t_j]$ 表示一段时间，每个区间有 $t_j, w_j$ 表示若选择这个区间则 $t_j$ 后才能选其他的区间，选择区间的权为 $w_j$ 。现在有一个人从 $1$ 时刻开始选区间，他会选当前能选的最大权的区间，若存在多个，选 $d_j$ 大的区间。现在有 $m$ 次机会，每次可以使得这个人在某一秒不能选区间。求当这 $m$ 次机会使用得最优时，这个人最小能选择区间权和。

正序DP不太好做。

考虑倒序DP，设$dp(i,j)$为$[i,n]$用了$j$次机会的最小权和。
则

$$dp(i,j)=\min\{dp(i+1,j-1),dp(i+1,j),dp(g, j)\}$$

其中$g=\max\limits_{i \in {[s_j, t_j]}, j\in[1,k]}\{d_j\}$

这个$g$可以用`set`维护。
具体就是将区间端点存起来，然后枚举时间线时看是否超出了，超出即删掉，如果有新的加入，就加入。

```c++
#include<cstdio> 
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
#include<string>
#define ms(i, j) memset(i, j, sizeof i)
#define LL long long
#define db long double
#define fir first
#define sec second
#define mp make_pair
using namespace std;

namespace flyinthesky {

	LL n, m, k;
	vector<pair<LL, LL > > st[100000 + 5], ed[100000 + 5];
	LL dp[100000 + 5][200 + 5];
	multiset<pair<LL, LL > > S;

    void clean() {
    	ms(dp, 0);
	}
    int solve() {
    	
    	clean();
    	cin >> n >> m >> k;
    	for (LL s, t, d, w, i = 1; i <= k; ++i) {
    		scanf("%lld%lld%lld%lld", &s, &t, &d, &w);
    		st[t].push_back(make_pair(-w, -d));
    		ed[s].push_back(make_pair(-w, -d));
		}

		for (LL i = n; i >= 1; --i) {
			for (LL o = 0; o < (LL)st[i].size(); ++o) S.insert(st[i][o]);
			
			pair<LL, LL > whw = make_pair(0, 0);
			if (!S.empty()) whw = *S.begin();
			
			for (LL j = 0; j <= m; ++j) {
				LL hh = i + 1;
				if (whw.first) hh = -whw.second + 1;
				dp[i][j] = dp[hh][j] + (-whw.first);
				if (j) dp[i][j] = min(dp[i + 1][j - 1], dp[i][j]);
			}
			
			for (LL o = 0; o < (LL)ed[i].size(); ++o) S.erase(S.lower_bound(ed[i][o]));
		}

		cout << dp[1][m];

        return 0;
    }
}
int main() {
    flyinthesky::solve();
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

不难发现按照贪心策略，每个时间点拿的红包是固定的。

可以考虑用权值线段树 + 扫描线预处理出来这个东西。

假设第 $i$ 秒应该取 $(W_i,D_i)$ 这个物品。

那么我们设 $dp_{i,j}$ 表示前 $i$ 秒扰乱 $j$ 次的最小值。那么每次考虑是否扰乱，有转移：

$$\begin{cases}dp_{i+D_i,j}=\min\{dp_{i+D_i,j},dp_{i,j}+W_i\}\\dp_{i+1,j+1}=\min\{dp_{i+1,j+1},dp_{i,j}\}\end{cases}$$

最后输出 $\min\limits_{i=n+1}^{2n}\min\limits_{j=0}^{m}dp_{i,j}$ 即可。

也可以在转移的时候把 $i+D_i$ 对 $n+1$ 取 $\min$，答案就可以表示为 $\min\limits_{i=0}^{m}dp_{n+1,i}$。

复杂度 $O(n \log n+nk)$。

---

