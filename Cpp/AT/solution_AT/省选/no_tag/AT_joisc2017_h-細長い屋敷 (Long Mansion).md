# 細長い屋敷 (Long Mansion)

## 题目描述

#「JOISC 2017 Day 3」幽深府邸


**题目译自 [JOISC 2017](https://www.ioi-jp.org/camp/2017/2017-sp-tasks/index.html) Day3 T2「[細長い屋敷](https://www.ioi-jp.org/camp/2017/2017-sp-tasks/2017-sp-d3.pdf)（[Long Mansion](https://www.ioi-jp.org/camp/2017/2017-sp-tasks/2017-sp-d3-en.pdf)）」**

$N$ 个房间排列在一条直线上，依次编号为 $1, 2, \ldots, N$。只有编号相邻的房间才相连。相连的房间之间有上锁的门。  
从房间 $i$ 进入房间 $i+1$，或者从房间 $i+1$ 进入房间 $i$，需要类型为 $C_i$ 的钥匙 $(1\le i\le N-1)$。  
进入房间 $i$ 可以捡起房间里的所有钥匙。房间 $i$ 有 $B_i$ 把钥匙，类型分别为 $A[i][1]\dots A[i][B_i]$ 保证对于同一个 $i$，没有两个 $A[i][j]$ 相同。钥匙可以重复使用。你可能会获得相同的钥匙，然并卵。  
现在有 $Q$ 组查询，每组查询用两个整数 $x, y$ 来描述 $(x≠y)$，表示：如果有人被丢进房间 $x$，手上没有任何钥匙，此人能否到达房间 $y$（当然，此人可以捡房间 $x$ 里的钥匙）。  
对于每组查询，如果此人能到达，输出 $\texttt{YES}$，否则输出 $\texttt{NO}$ 。

## 说明/提示

对于所有数据，$2\le N\le 5\times 10^5,$ $1\le Q\le 5\times 10^5,$ $1\le \sum B_i \le 5\times 10^5,$ $1\le B_i, C_i, A[i][j], X_k, Y_k\le N,$ $X_k≠Y_k$。

|子任务 #|分值|$N$|$Q$|$\sum B_i$|$C_i, A[i][j]$|
|-|-|-|-|-|-|
|1|5|$N\le 5000$|$Q\le 5000$|$\sum B_i \le 5000$|.|
|2|5|$N\le 5000$|.|$\sum B_i \le 5000$|.|
|3|15|$N\le 10^5$|.|.|$C_i, A[i][j]\le 20$|
|4|75|.|.|.|.|

感谢 Planet6174 提供的翻译

# 题解

## 作者：Delov (赞：15)

考虑暴力扩展的做法，把当前拥有的钥匙用某种东西维护起来显然是劣的，考虑优化我们判断能不能开一个门的方法。  

假设我从 $x$ 点开始扩展，当前已经扩展到的区间为 $[l,r]$，如果我们想要扩展到 $r+1$，那么 $[l,r]$ 内至少有一个屋子里有 $c_{r+1}$，因为我从左向右走，只要离 $r+1$ 最近的出现了 $c_{r+1}$ 的位置已经被扩展到即可，于是我们只需要维护一个 $L_i$ 表示 $c_i$ 在之前的最近一次出现的位置。向 $l-1$ 扩展同理。

暴力扩展每一个点是 $n^2$ 的，考虑优化它。假设我们现在已经扩展完了一个点，正在扩展的另一个点此时扩展到了它，那么这个点所有能到的位置正在扩展的点一定都能到，于是我们可以直接对两者的答案取并集给当前扩展的点。这样进行类似记忆化搜索，每次我要扩展一侧边界时，就从那个边界开始做一次扩展，然后取并集即可，如果已经扩展过了就直接返回跑路。

实测比随机化快一点


```cpp
#include <bits/stdc++.h>
typedef long long ll;typedef unsigned long long ull; typedef double db;typedef long double ldb;
#define fre(x) freopen(#x ".in","r",stdin),freopen(#x ".out","w",stdout)
#define Rep(i,a,b) for(int i=a;i<=b;++i) 
#define Dwn(i,a,b) for(int i=a;i>=b;--i)
#define pii pair<int,int>
#define mair make_pair
#define fir first
#define sec second
using namespace std;

const int maxn=5e5+10;

int n,q;
int c[maxn];
vector<int>vec[maxn];
int last[maxn];
int L[maxn],R[maxn],p[maxn];
bool vis[maxn];
pii rg[maxn];

void Sol(int x){
	bool flag=false;
	if(vis[x])return void();
	if(rg[x].fir>0)return;
	vis[x]=true;
	int &l =rg[x].fir,&r=rg[x].sec;
	l=x,r=x;flag=true;
	while(flag){
		flag=false;
		if(l>1 && R[l-1]>=l && R[l-1]<=r)
		{ Sol(l-1);flag=true; l=min(l,rg[l-1].fir),r=max(r,rg[l-1].sec); }
		if(r<n && L[r]<=r && L[r]>=l)
		{ Sol(r+1);flag=true; l=min(l,rg[r+1].fir),r=max(r,rg[r+1].sec); }
	}
}

void solve(){
	cin>>n;int x,y;
	for(int i=1;i<n;++i)cin>>c[i];
	Rep(i,1,n){
		cin>>y; Rep(j,1,y){ cin>>x;vec[i].push_back(x);last[x]=i; }
		if(i!=n)L[i]=last[c[i]];
	}
	Rep(i,1,n)last[i]=n+1;
	Dwn(i,n,1){ for(auto it : vec[i])last[it]=i; R[i-1]=last[c[i-1]]; }
	Rep(i,1,n)Sol(i);
	cin>>q;
	while(q--){
		cin>>x>>y;
		if(rg[x].fir<=y && rg[x].sec>=y)cout<<"YES\n";
		else cout<<"NO\n";
	}
}

int main (){ ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);return solve(),0; }
```

---

## 作者：joke3579 (赞：12)

在线处理的复杂度很高，考虑离线处理后 $O(1)$ 查询。

我们设点 $i$ 能够到达的区间为 $[l_i, r_i]$，则 $x$ 点可以到达 $y$ 当且仅当 $l_i \le y \le r_i$。于是问题即为如何快速求解可及区间。

考虑在已经确定 $i$ 节点对应区间为 $[l_i,r_i]$ 的情况下检查 $l_i-1$ 和 $r_i+1$ 的可及性并拓展。这里只讨论右侧的拓展方式，左侧同理。

由于一扇门只需要一把钥匙来打开，不难想到对每扇门 $i$ 维护其前后第一次出现 $C_i$ 这把钥匙的位置，并在判断是否能开门时使用。有少许细节。

需要注意，有可能出现拓展某一侧时暂时无法进行，而拓展完另一侧后便可进行的情况。因此需要在两边均无法拓展后才可结束拓展。

具体实现方面，我们可以将拓展 $r+1$ 视为 $[l,r]$ 的一个子问题，递归求解。函数返回从 $r+1$ 处能拓展到的最大范围，我们便可以将该范围与当前范围取 $\max$ 来更新答案。

通过记忆化手段，不难证明对于每个点总共只会拓展一次区间。   
由于记忆化，一扇门只会被查询 $O(1)$ 次可及性，而单次查询可及性的复杂度是 $O(1)$ 的。因此均摊时间复杂度为 $O(n)$。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for (register int (i) = (a); (i) <= (b); ++(i))
#define pre(i,a,b) for (register int (i) = (a); (i) >= (b); --(i))
using namespace std;
const int N = 5e5 + 10, mod = 1e9 + 7;
int n, q, c[N], t1, t2, pref[N], aft[N], tmp[N];
vector<int> keys[N];
pair<int, int> mem[N];

#ifdef ONLINE_JUDGE
    char buf[1<<21], *p1 = buf, *p2 = buf;  inline char getc() { return (p1 == p2 and (p2 = (p1 = buf) + fread(buf, 1, 1<<21, stdin), p1 == p2) ? EOF : *p1++); }
    #define getchar getc
#endif
template <typename T> inline void get(T & x){
    x = 0; char ch = getchar(); bool f = 0; while (ch < '0' or ch > '9') f = f or ch == '-',  ch = getchar();
    while (ch >= '0' and ch <= '9') x = (x<<1) + (x<<3) + (ch^48), ch = getchar(); f and (x = -x);
} template <typename T, typename ... Args> inline void get(T & x, Args & ... _Args) { get(x); get(_Args...); }

void dfs(int p) {
    if (mem[p].first >= 0) return;

    int & l = mem[p].first, & r = mem[p].second;
    l = p, r = p, t2 = 1;
    while (t2) {
        t2 = 0;
        if (l > 1 and aft[l - 1] <= r) {
            dfs(l - 1); 
            l = min(l, mem[l - 1].first);
            r = max(r, mem[l - 1].second);
            t2 = 1;
        }
        if (r < n and pref[r] >= l) { 
            dfs(r + 1);
            l = min(l, mem[r + 1].first);
            r = max(r, mem[r + 1].second);
            t2 = 1;
        }
    } 

    return ;
} 

int main() {
    get(n);
    rep(i,1,n-1) get(c[i]);
    rep(i,1,n) {
        get(t1);
        keys[i].resize(t1);
        for (int j = 0; j < t1; ++j) get(keys[i][j]);
    } 

    rep(i,1,n) {
        for (auto x : keys[i]) tmp[x] = i;
        pref[i] = tmp[c[i]];
    } 
    rep(i,1,n) tmp[i] = n + 1;
    pre(i,n,1) {
        aft[i] = tmp[c[i]];
        for (auto x : keys[i]) tmp[x] = i;
    } 

    rep(i,1,n) mem[i] = {-1, -1};
    rep(i,1,n) dfs(i);

    get(q);
    while (q--) {
        get(t1, t2); 
        if (mem[t1].first <= t2 and t2 <= mem[t1].second) puts("YES");
        else puts("NO");
    }

    return 0;
}
```

---

## 作者：louhao088 (赞：7)

一道好题。


------------


考虑在线回答询问不好处理，我们可以提前预处理出每个点房间能走到的位置，显然，每个房间能到达的点集是一段连续的区间。

但是，如果我们暴力处理的话，要 $n^2$ 复杂度。


------------


考虑优化。

我们发现如果从 $x$ ，能走到 $y$ ，那么 $x$ 一定能走到 $y$ 能走到的所有地方，这样可以把答案进行较快速的更新。

具体的，我们可以先预处理出每一间房间左边第一把能打开他的钥匙，和右边第一把能打开他的钥匙。其他钥匙对他其实都没有贡献，因为如果能用其他钥匙必然能用这两把。然后判断能不能打开一个门，就判断已经有的区间是否包含钥匙。

然而还是有特殊构造数据，可以卡掉它。


------------


考虑随机化，我们随机选择更新 i 可以到达的区间顺序。

具体的可以用 shuffle 函数实现。

这样每次更新期望只要更新 $\log n$ 次。


------------


这样就能顺利的通过，~~跑的飞快，感觉跑出 O(n)的效果~~。


------------


代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define pi pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define mid (l+r>>1)
#define lowbit (x&-x)
const int maxn=5e5+5,M=34005;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
mt19937 rnd(time(0));
int L[maxn],R[maxn],n,m,ly[maxn],ry[maxn],s[maxn],g,c[maxn],x,y,q,vis[maxn],p[maxn];
vector<int>b[maxn];
void add(int i)
{
	int l=i,r=i;int F=1;vis[i]=1;
	while(F)
	{
		F=0;
		while(l>1&&ry[l-1]>=l&&ry[l-1]<=r)
		{
			l--;F=1;
			if(vis[l])l=min(l,L[l]),r=max(r,R[l]);
		}
		while(r<n&&ly[r]<=r&&ly[r]>=l)
		{
			r++;F=1;
			if(vis[r])l=min(l,L[r]),r=max(r,R[r]);
		}
	}L[i]=l,R[i]=r;
}
signed main()
{
	n=read();
	for(int i=1;i<n;i++)c[i]=read();
	for(int i=1;i<=n;i++)
	{
		x=read();
		for(int j=1;j<=x;j++)
			g=read(),b[i].push_back(g),s[g]=i;
		if(i!=n)ly[i]=s[c[i]];
	}
	for(int i=1;i<=n;i++)s[i]=n+1;
	for(int i=n;i>=1;i--)
	{
		for(auto j:b[i])s[j]=i;
		ry[i-1]=s[c[i-1]];
	}
	for(int i=1;i<=n;i++)p[i]=i;
	shuffle(p+1,p+1+n,rnd);
	for(int i=1;i<=n;i++)add(p[i]);
	q=read();
	for(int i=1;i<=q;i++)
	{
		x=read(),y=read();
		if(L[x]<=y&&R[x]>=y)puts("YES");
		else puts("NO");
	}
 	return 0;
}


/*********************************************************************
    作者:louhao088
    日期: 2021-11-11 11:11
*********************************************************************/

```



---

## 作者：kiritokazuto (赞：3)

 这个题其实挺简单的...就是思路没开化
 
- 我们可以预处理出每一个点向左向右可以扩展到的距离，直接 $O(1)$ 查就行。

- 考虑如何扩展：

    - 对于每一个门，其实对他有用的只有能打开它的第一把钥匙，所以我们维护出每一个门左边最靠近它和右边最靠近它的钥匙在哪里，这个东西可以在读入时处理，因为我是从左到右读入的，有单调性顺序的，右边就倒过来处理就行。即是我对于左边最靠近我的钥匙只需要一直存，当扫到我时上一次存的就是我对应的最近的钥匙，对于右边我将原序列存下来再次倒过来遍历，然后存就行。这显然是 $O(n)$。
    
    - 维护好了之后就可以直接扩展了，例如向左扩展，如果我当前能到达的区间中包含了我现在要扩展的门所需要的右边最靠近它的钥匙，我就可以更新，反之则不行，右边同理，包含最靠左的就行。就是注意向左和向右扩展的时候查的钥匙不一样，因为向右边的时你只需要 $i - 1$ 的钥匙， 而向左扩展的时候确确实实需要的是 $i$ 的钥匙，这里要注意。因为是暴力扩展的，期望的时间复杂度大概是 $O(n \log n)$ 的，具体不太会证，这里只提供思路。

- 对于随机化这个问题，在这个题不随机化跑得比随机化快，所以如果不是遇到了特别恶心的构造数据，不随机化还是跑得起来的。
    




[每日一图](https://www.cnblogs.com/kiritokazuto/p/16719796.html#5104700)
```cpp


#include <bits/stdc++.h>
#define LL long long
#define Re register int
#define LD double
#define mes(x, y) memset(x, y, sizeof(x))
#define cpt(x, y) memcpy(x, y, sizeof(x))
#define fuc(x, y) inline x y
#define fr(x, y, z)for(Re x = y; x <= z; x ++)
#define fp(x, y, z)for(Re x = y; x >= z; x --)
#define frein(x) freopen(#x ".in", "r", stdin)
#define freout(x) freopen(#x ".out", "w", stdout)
#define ki putchar('\n')
#define fk putchar(' ')
#define WMX aiaiaiai~~
#define pr(x, y) pair<x, y>
#define mk(x, y) make_pair(x, y)
#define pb(x) push_back(x)
#define sec second
#define fst first

using namespace std;
namespace kiritokazuto{
    auto read = [](){
        LL x = 0;
        int f = 1;
        char c;
        while (!isdigit(c = getchar())){ if (c == '-')f = -1; }
        do{ x = (x << 1) + (x << 3) + (c ^ 48); } while (isdigit(c = getchar()));
        return x * f;
    };
    template <typename T> fuc(void, write)(T x){
        if (x < 0)putchar('-'), x = -x;
        if (x > 9)write(x / 10); putchar(x % 10 | '0');
    }
}

using namespace kiritokazuto;

const int maxn = 6e5 + 100, Mod = 1e9 + 7;
const LL Inf = 2147483647, ord = 1e10;
int n;
int l[maxn], r[maxn];
int lk[maxn], rk[maxn];
int L, R;
fuc(void, updata)(int x) {
    L = min(l[x], L);
    R = max(r[x], R);
}
int c[maxn];
int tmp[maxn];

int pos[maxn];
int q;

vector <int> Key[maxn];
fuc(bool, lwork)() {
    if(L == 1)return 0;
    if(L <= rk[L - 1] && rk[L - 1] <= R) {
        if(l[--L]) {
            updata(L);
        }
        return 1;
    }
    return 0;
}
fuc(bool, rwork)() {
    if(R == n)return 0;
    if(L <= lk[R] && lk[R] <= R) {
        if(r[++R]) {
            updata(R);
        }
        return 1;
    }
    return 0;
} 
fuc(void, work)(int x){
    L = R = x;
    while(1) {if(!lwork() && !rwork())break;}
    l[x] = L;
    r[x] = R;
}
signed main() { 
    n = read();
    fr(i, 1, n - 1)c[i] = read();
    fr(i, 1, n) {
        pos[i] = i;
        int x = read();
        fr(j, 1, x) {
            int tp = read();
            Key[i].pb(tp);
            tmp[tp] = i;
        }   
        if(i != n)lk[i] = tmp[c[i]];
    }
    fr(i, 1, n)tmp[i] = n + 1;
    fp(i, n, 1) {
        for(auto j : Key[i]) {
            tmp[j] = i;
        }
        rk[i - 1] = tmp[c[i - 1]];
    }
    fr(i, 1, n) {
        work(pos[i]);
    }
    q = read();
    fr(i, 1, q) {
        int x = read(),y = read();
        if(l[x] <= y && y <= r[x]) {
            puts("YES");
            continue;
        }else {
            puts("NO");
        }
    }
  
    return 0;
}  


```



---

## 作者：Graphcity (赞：2)

LOJ 原题链接：[#2397. 「JOISC 2017 Day 3」幽深府邸](https://loj.ac/p/2397)

不会记忆化搜索，麻了。考虑更加人性化的办法。

观察：如果 $c_{x}$ 和 $c_{y-1}$ 均没有在区间 $(x,y)$ 的颜色中出现的话，那么从 $(x,y)$ 中的任何一个点出发都无法走到 $x$ 或 $y$。我们称数对 $(x,y)$ 为障碍数对。

对于一个点 $x$，可以方便求出 $R_x$ 表示它右边第一次出现 $c_x$ 的位置，$L_x$ 同理。数对 $(x,y)$ 为障碍数对，当且仅当 $R_x\ge y$ 且 $L_y\le x$。

考虑询问 $(l,r)$，先假设 $l<r$。我们如果能够找到一对 $(x,y)$ 满足：$x<l< y\le r$，$R_x\ge y$ 并且 $L_y\le x$ 的话，从 $l$ 出发必不可能走到 $r$，否则必然可以。$l>r$ 的情况只需要将整个序列翻转一下。

离线所有询问，然后按照 $l$ 从小往大的顺序扫描线。线段树可以方便处理限制。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=5e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,c[Maxn+5],L[Maxn+5],R[Maxn+5],ans[Maxn+5];
int m,X[Maxn+5],Y[Maxn+5];
int t[Maxn*4+5],tag[Maxn*4+5],mxl[Maxn*4+5],mnr[Maxn*4+5];
vector<int> w[Maxn+5];
vector<pair<int,int>> qr[Maxn+5];
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

inline void push_up(int p) {t[p]|=(t[ls(p)]|t[rs(p)]);}
inline void mk(int p,int k)
{
    mxl[p]=max(mxl[p],k),tag[p]=max(tag[p],k);
    if(mxl[p]>=mnr[p]) t[p]=1;
}
inline void push_down(int p)
{if(tag[p]!=-1) mk(ls(p),tag[p]),mk(rs(p),tag[p]),tag[p]=-1;}
inline void Build(int l,int r,int p)
{
    mxl[p]=mnr[p]=t[p]=0,tag[p]=-1;
    if(l==r) {mnr[p]=L[l]; return;}
    int mid=(l+r)>>1;
    Build(l,mid,ls(p)),Build(mid+1,r,rs(p));
    mnr[p]=min(mnr[ls(p)],mnr[rs(p)]);
}
inline void Modify(int nl,int nr,int l,int r,int p,int k)
{
    if(l<=nl && nr<=r) {mk(p,k); return;}
    int mid=(nl+nr)>>1; push_down(p);
    if(l<=mid) Modify(nl,mid,l,r,ls(p),k);
    if(r>mid) Modify(mid+1,nr,l,r,rs(p),k);
    push_up(p);
}
inline int Count(int nl,int nr,int l,int r,int p)
{
    if(l<=nl && nr<=r) return t[p];
    int mid=(nl+nr)>>1,res=0; push_down(p);
    if(l<=mid) res|=Count(nl,mid,l,r,ls(p));
    if(r>mid) res|=Count(mid+1,nr,l,r,rs(p));
    push_up(p); return res;
}
inline void GetLR()
{
    static int pos[Maxn+5];
    For(i,1,Maxn) pos[i]=n+1; R[0]=n+1;
    Rof(i,n,1) {R[i]=pos[c[i]]; for(auto j:w[i]) pos[j]=i;}
    For(i,1,Maxn) pos[i]=0;
    For(i,1,n) {L[i]=pos[c[i-1]]; for(auto j:w[i]) pos[j]=i;}
}
inline void Solve()
{
    For(i,1,n) qr[i].clear(),qr[i].shrink_to_fit();
    GetLR(),Build(0,n,1);
    For(i,1,m)
    {
        int x=X[i],y=Y[i];
        if(x<y) qr[x].emplace_back(y,i);
    }
    Modify(0,n,1,n,1,0);
    For(i,1,n)
    {
        for(auto [j,id]:qr[i]) ans[id]=Count(0,n,i+1,j,1);
        if(i<R[i]) Modify(0,n,i+1,R[i],1,i);
    }
}

int main()
{
    n=read();
    For(i,1,n-1) c[i]=read();
    For(i,1,n)
    {
        int k=read();
        while(k--) w[i].push_back(read());
    }
    m=read();
    For(i,1,m) X[i]=read(),Y[i]=read();
    Solve();
    For(i,1,m) X[i]=n-X[i]+1,Y[i]=n-Y[i]+1;
    reverse(c+1,c+n);
    For(i,1,n/2) swap(w[i],w[n-i+1]);
    Solve();
    For(i,1,m) printf("%s\n",ans[i]?"NO":"YES");
    return 0;
}
```

---

## 作者：ningago (赞：1)

类似的题：P4436。

不难发现从每个节点开始走，能走到的是一段区间，记作 $S_x=[L_x,R_x]$。

如果已经有一个区间，要判断能不能向左 / 右走一步，可以使用二分 $O(\log n)$ 或预处理后 $O(1)$（虽然二分的实际效率与 $O(1)$ 非常接近）。

考虑用记忆化搜索的方法求出 $S_x$。具体地，如果从区间 $[L_x,R_x]$ 可以走到 $[L_x-1,R_x]$，那么先对 $L_x-1$ 这个点求解（求出 $S_{L_x-1}$），然后更新 $S_x\leftarrow S_x\cup S_{L_x-1}$，然后继续走。$R_x+1$ 同理。

分析复杂度：如果一个 $[L_x,R_x]$ 可以向左走一步，那么一定有 $S_{L_x-1}\subseteq S_x$（右同理）。$x$ 只需要在此基础上继续向两边走。所以一共需要走 $O(n)$ 步。

总复杂度 $O(n+m)$，代码使用二分，最多只慢了 30ms。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define N 500010
int n, m;
int col[N];
std::vector <int> v[N];
int len[N];

inline bool query(int k, int ql, int qr)
{
	int sz = len[k];
	int l = 0, r = sz - 1, res = n + 1;
	while(l <= r && res > qr)
	{
		int mid = (l + r) >> 1;
		if(v[k][mid] >= ql)
			r = mid - 1, res = v[k][mid];
		else
			l = mid + 1;
	}
	return res <= qr;
}
int L[N], R[N];
void dfs(int k)
{
	if(L[k])
		return;
	L[k] = R[k] = k;
	while(1)
	{
		bool flag = 0;
		while(L[k] > 1 && query(col[L[k] - 1], L[k], R[k]))
		{
			L[k]--;
			if(!L[L[k]])
				dfs(L[k]);
			R[k] = std::max(R[k], R[L[k]]);
			L[k] = L[L[k]];
			flag = 1;
		}
		while(R[k] < n && query(col[R[k]], L[k], R[k]))
		{
			R[k]++;
			if(!R[R[k]])
				dfs(R[k]);
			L[k] = std::min(L[k], L[R[k]]);
			R[k] = R[R[k]];
			flag = 1;
		}
		if(!flag)
			break;
	}
}

int read()
{
	int x = 0;
	char c = getchar();
	while(c < '0' || '9' < c)
		c = getchar();
	while('0' <= c && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x;
}

int main()
{
	n = read();
	for(int i = 1; i < n; i++)
		col[i] = read();
	for(int i = 1, x, b; i <= n; i++)
	{
		b = read();
		while(b--)
		{
			x = read();
			v[x].push_back(i);
		}
	}
	for(int i = 1; i <= n; i++)
		len[i] = v[i].size();
	for(int i = 1; i <= n; i++)
		dfs(i);
	m = read();
	for(int i = 1, x, y; i <= m; i++)
	{
		x = read(), y = read();
		if(L[x] <= y && y <= R[x])
			putchar('Y'), putchar('E'), putchar('S'), putchar('\n');
		else
			putchar('N'), putchar('O'), putchar('\n');
	}
	return 0;
}

```

---

