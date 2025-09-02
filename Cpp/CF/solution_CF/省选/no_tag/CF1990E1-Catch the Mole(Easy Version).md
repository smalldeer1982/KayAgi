# Catch the Mole(Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is the limit on the number of queries.

This is an interactive problem.

You are given a tree of $ n $ nodes with node $ 1 $ as its root node.

There is a hidden mole in one of the nodes. To find its position, you can pick an integer $ x $ ( $ 1 \le x \le n $ ) to make an inquiry to the jury. Next, the jury will return $ 1 $ when the mole is in subtree $ x $ . Otherwise, the judge will return $ 0 $ . If the judge returns $ 0 $ and the mole is not in root node $ 1 $ , the mole will move to the parent node of the node it is currently on.

Use at most $ 300 $ operations to find the current node where the mole is located.

## 说明/提示

In the first test case, the mole is in node $ 2 $ initially.

For the query "? 2", the jury returns $ 1 $ because the mole is in subtree $ 2 $ . After this query, the mole does not move.

The answer $ 2 $ is the current node where the mole is located, so the answer is considered correct.

In the second test case, the mole is in node $ 6 $ initially.

For the query "? 2", the jury returns $ 0 $ because the mole is not in subtree $ 2 $ . After this query, the mole moves from node $ 6 $ to node $ 5 $ .

For the query "? 6", the jury returns $ 0 $ because the mole is not in subtree $ 6 $ . After this query, the mole moves from node $ 5 $ to node $ 4 $ .

For the query "? 4", the jury returns $ 1 $ because the mole is in subtree $ 4 $ . After this query, the mole does not move.

The answer $ 4 $ is the current node where the mole is located, so the answer is considered correct.

Please note that the example is only for understanding the statement, and the queries in the example do not guarantee to determine the unique position of the mole.

## 样例 #1

### 输入

```
2
2
1 2

1

6
1 2
1 3
1 4
4 5
5 6

0

0

1```

### 输出

```
? 2

! 2






? 2

? 6

? 4

! 4```

# 题解

## 作者：Federico2903 (赞：5)

## 思路

每一次出现一个失败的操作，鼹鼠会往上跑一步。

也就是说，当有 $k$ 个失败的操作时，鼹鼠一定不会出现在最大深度 $\le k$ 的子树中。

如果树是一条链是简单的，二分即可。

那么我们可以先执行 $\sqrt n$ 次询问叶子的操作，如果返回 $1$ 皆大欢喜，因为答案就在这里。

做完这样的操作会使得最大深度 $\le \sqrt n$ 的子树中没有鼹鼠。接下来我们考虑通过 dfs 把树简化为一条链。

设失败的操作出现了 $x$ 次了。

从 $1$ 号节点开始，我们找出其所有满足最大深度 $> x$ 的子树，依次询问。当得到 $1$ 的答案时直接向其递归，否则我们就排除了至少 $x$ 个节点。

因为我们询问了 $\sqrt n$ 次叶子，所以 $x \ge \sqrt n$，则上述操作至多执行 $\sqrt n$ 次。

非常美妙的做法，但是这会**被链卡操作次数**。

怎么办呢。我们找出儿子的时候只询问前 $siz - 1$ 个，如果都是 $0$ 就直接进入最后一个儿子就能规避这个问题了。

最后到达叶子的时候，从 $1$ 号节点到叶子的这条链上一定有鼹鼠，二分即可。

总操作次数应为 $2 \sqrt n + \log n$。

## AC 代码

```cpp
#ifdef ONLINE_JUDGE
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt")
#include <immintrin.h>
#include <emmintrin.h>
#endif

#include <bits/stdc++.h>

#define rep(i, a, b) for(int i = (a), i##end = (b); i <= i##end; i++)
#define _rep(i, a, b) for(int i = (a), i##end = (b); i >= i##end; i--)
#define ec first
#define fb second
#define dl make_pair
#define dk(...) make_tuple(__VA_ARGS__)

using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

int read() {
	int x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}

template <typename _Tp>
void print(_Tp x) {
	if (x < 0) x = (~x + 1), putchar('-');
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int T, n, zc;

void found(int vert) { cout << "! " << vert << endl; }
int ask(int vert) {
	cout << "? " << vert << endl;
	int x = read();
	if (x) return 1;
	else return zc++, 0;
}

const int MAXN = 5005;
vector <int> G[MAXN];
int dep[MAXN], pdep[MAXN];
int s[MAXN << 2], top;

void dfs0(int u, int fa) {
	dep[u] = 1;
	pdep[u] = pdep[fa] + 1;
	for (auto v : G[u]) {
		if (v == fa) continue;
		dfs0(v, u);
		dep[u] = max(dep[u], dep[v] + 1);
	}
}

void dfs1(int u, int fa) {
	s[++top] = u;
	vector <int> son;
	for (auto v : G[u]) {
		if (v == fa || dep[v] <= zc) continue;
		son.push_back(v);
	}
	rep (i, 0, son.size() - 2) {
		if (ask(son[i])) return dfs1(son[i], u);
	}
	if (son.size()) dfs1(son.back(), u);
}


void solve() {
	zc = 0;
	top = 0;
	n = read();
	rep (i, 1, n) vector <int>().swap(G[i]);
	rep (i, 1, n - 1) {
		int u = read(), v = read();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	const int B = 70;
	int leaf = 0;
	dfs0(1, 1);
	rep (i, 1, n) if (dep[i] == 1) leaf = i;
	if (ask(leaf)) return found(leaf);
	else rep (i, 1, B - 1) ask(leaf);
	dfs1(1, 1);
	int l = 1, r = top, mid = 0, cnt = 0, ans = 0;
	while (l <= r) {
		mid = (l + r) >> 1;
		int pt = mid > cnt ? mid - cnt : 0;
		if (!pt) { l = mid + 1; ans = mid; continue; }
		if (ask(s[pt])) l = mid + 1, ans = mid;
		else r = mid - 1, cnt++;
	}
	if (ans > cnt) found(s[ans - cnt]);
	else found(1);
}

signed main() {
	T = read();
	while (T --> 0) solve();
	return 0;
}
```

---

## 作者：cyc001 (赞：3)

### 题目大意

给定一颗有 $n$ 个节点的有根树，有一只鼹鼠在某一个节点。

每次可以进行一种询问 ```? u```，交互库会返回鼹鼠是不是在 $u$ 的子树内，如果是就返回 $1$，否则返回 $0$。

同时如果询问时鼹鼠不在根且交互库返回了 $0$，鼹鼠会移动到父节点。

你有 $300$ 次询问的机会，需要得到鼹鼠**当前**所在的节点。

### 题目解析

**这是一种与官方题解不同的做法**

考虑已经知道鼹鼠 $u$ 的子树里如何处理。

不如将问题简化，假设我们已经知道了鼹鼠在 $u$ 的父节点到 $u$ 的某个祖先 $v$ 的链上如何处理。

如果这条链比较短，我们可以直接每次询问 $u$ 直到鼹鼠不在 $v$ 的子树内，然后显然可以方便地求出鼹鼠的位置，需要 $2*len$ 次询问，其中 $len$ 是链长。

经验告诉我们，链长的 $len$ 应该是 $O(\sqrt n)$ 的。

考虑如何求出这条根号长的链。

我们可以将 $u$ 的子树内距离 $u$ 的距离为 $\sqrt n$ 的节点取出，然后递归到子问题，这样链长度就是根号的了。

然而如果你这样写了并且提交，你会在 pretest $48$ 或 test $71$ 挂掉，因为这个做法实在太好卡了，直接在一个菊花上伸出一条长度为 $\sqrt n-1$ 的链连到根，就可以把询问次数卡到 $n+\sqrt n$，不如暴力，咳咳。

考虑优化这个过程。

因为我们不要求链长度是严格的 $\sqrt n$，所以可以考虑贪心地去扩链的长度，如果深度 $+1$ 可以使得需要询问的点数变少，就贪心的将深度 $+1$，这样链长最多为 $\sqrt n *2$。

然鹅这个做法依然很好卡，考虑每根号个节点挂一个两层的菊花，且第一层的点数是第二层的点数 $-1$，这样大约可以卡到 $\frac n 3$ 次询问左右。

这个贪心做法很有启发性，感觉很有前途，于是我们可以去取一个区间 $[L,R]$，在与当前节点 $u$ 的深度差属于 $[\sqrt n \cdot L,\sqrt n \cdot R]$ 的节点集合里取最小的，这样就卡不掉一丁点了，实测 $L=0.8, R=1.3$ 时询问次数是 $280$ 次左右，可以通过此题。

### Code

赛时代码改的，可能比较混乱。

```cpp
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
auto checkml(int u){
    cout<<format("? {}",u)<<'\n';
    cout.flush();
    int tp;cin>>tp;
    return tp;
}
auto answer(int u){
    cout<<format("! {}",u)<<'\n';
    cout.flush();
}
class check{
private:
    vector<vector<int>> gr,hx;
    vector<int> dfn,rdfn,rid,fx,ht;
    int cnt;
    auto dfs(int u,int h=0,int f=1)->void{
        dfn[u]=++cnt;rid[dfn[u]]=u;ht[u]=h;
        hx[h].push_back(dfn[u]);fx[u]=f;
        for(auto&i:gr[u]) if(i!=f) dfs(i,h+1,u);
        rdfn[u]=cnt;
    }
    auto ask(int u,int las,int h,int delta,const int sqr,bool spc=false)->void{
        if(checkml(u)){
            auto nhx=h+(int)(sqr/1.2);
            auto lb=ranges::lower_bound(hx[nhx],dfn[u]);
            auto rb=ranges::upper_bound(hx[nhx],rdfn[u]);
            while(lb==rb){
                --nhx;spc=true;
                lb=ranges::lower_bound(hx[nhx],dfn[u]);
                rb=ranges::upper_bound(hx[nhx],rdfn[u]);
            }
            if(!spc) for(auto i=(int)(sqr/1.2+1);i<(int)(sqr*1.3);++i){
                auto nlb=ranges::lower_bound(hx[h+i],dfn[u]);
                auto nrb=ranges::upper_bound(hx[h+i],rdfn[u]);
                if(nlb==nrb) break;
                if(nrb-nlb<rb-lb) lb=nlb,rb=nrb,nhx=h+i;
            }
            if(nhx!=h){
                auto chs=false;
                const auto clb=lb;
                if(rb-lb<sqr+7) for(;lb<rb;++lb){
                    const auto ux=rid[*lb];
                    if(checkml(ux)){
                        ask(ux,u,nhx,nhx-h,sqr,spc);
                        chs=true;
                        break;
                    }
                }
                if(!chs) ask(rid[*clb],u,nhx,nhx-h,sqr,true);
            }else{
                spc=true;
            }
        }else{
            spc=true;
        }
        if(spc&&checkml(u)) throw u;
        if(!checkml(las)) return;
        checkml(u);
        auto cntx=0;
        while(checkml(las)&&cntx<delta+2) ++cntx,checkml(u);
        assert(las==1||cntx<delta+2);
        throw fx[fx[las]];
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto play(){
        dfs(1);
        #if not defined(ONLINE_JUDGE)
            const auto sqr=3;
        #else
            const auto sqr=50;
        #endif
        try{
            ask(1,1,0,sqr,sqr);
            assert(false);
        }catch(int ans){
            answer(ans);
        }
    }
    check(int n):gr(n+307),hx(n+307),dfn(n+307),rdfn(n+307),rid(n+307),fx(n+307),ht(n+307),cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;check ck(n);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;
            ck.insert(u,v);
        }
        ck.play();
    }();
    return 0;
}

```

---

## 作者：luogu_gza (赞：3)

我们直接来尝试解决 HR。

观察到 $n=5000$，操作次数是 $160$。

发现大致是类似于 $\sqrt n$ 的，尝试了一下发现是 $2 \sqrt n$。

但是貌似还多了 $18$ 次，我们猜测这是 $\log n$。

目标就是 $2 \sqrt n+\log n$。

什么情况下会出现 $2 \sqrt n$ 呢？我猜测这一定是 $B+\frac nB$ 然后均值出来的。

那么目标就是 $\log n+ B + \frac nB$。

---

$\log n$ 明显是二分得到的，不难想到寻找到鼹鼠的行动路径，然后在路径上二分。

我们先让鼹鼠行动 $B$ 次（方法是询问一个叶子 $B$ 次，但是如果我们运气好鼹鼠就在这个叶子上——返回了 $1$，那么直接回答这个叶子即可），这样的话我们搜索时就可以排除掉深度 $<B$ 的子树，因为鼹鼠往上爬了 B 次，不可能在这个子树上。

我们来进行 dfs。

举行了 `dfs(u)` 代表行动路径必定有 $u \to 1$。

+ 如果没有深度 $\geq B$ 的子树，那么其实鼹鼠已经被你抓到了，就在 $u$ 上。

+ 如果有深度 $\geq B$ 的子树，询问子树根，看返回值。如果返回值为 $1$，那么鼹鼠就在这个子树中，继续 dfs 下去。如果搜到最后返回值全部为 $0$，那么很不对劲，其实鼹鼠就在 $u$ 上！

这个方法很深刻，但是会被链干掉，我就是卡在了这一步。

其实你询问到最后一颗子树，如果前面的都“太失望了没有”，那么其实一定在这颗子树上（虽然还可能在 $u$ 上）。

此时理性分析一下发现每次 dfs 可以干掉一个深度 $\geq B$ 的子树（至少有 $B$ 个点）所以这一部分次数是 $\frac nB$。

至此就做完了，算下来的话需要 $155$ 次操作，还留下五次，挺有意思。

代码易，不放了。

---

## 作者：Hoks (赞：0)

## 前言
菜狗的第一场 VP，结果跳到幽默场了，好吧只能说我更幽默。

肯定直接开 hard version 了。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
交互题，没思路咋办。

考虑下按照做交互题的经验，应该就两种了：
1. 把情况逐渐缩小做。
2. 把给我们的操作特异化，取极值特殊化操作。

那这题好像没有熟悉的 $\max,\min$ 这种方便取极值的操作，那应该就是第一种了。

还是不是很好想，我们考虑从询问次数入手。

询问次数 $160$，而 $n$ 的范围是 $5000$，算一下可以接受 $\log^2 n$，而且卡的比较满。

但是我们好像想不到任何有关于 $\log n$ 上再来个 $\log n$ 的思路。

那只能跳出 $\log$ 的思路了，不难发现的是 $\sqrt{n}$ 大约是 $70$。

那么卡满的一个询问次数就是 $2\sqrt{n}$，这个感觉应该是从根号分治里来的。

那考虑下对什么根号分治吧。

我们考虑对于深度根号分治，把深度小于等于阈值 $B$ 的全部搞掉。

那怎么搞掉呢，考虑直接对着一个叶子问 $B$ 次，那么就可以把所有深度小于等于 $B$ 的点都跑到 $1$ 上了。

接着考虑剩下来的部分有什么优势。

我们考虑在这颗树上，把深度小于等于 $B$ 的点全删掉，那么剩下的连通块最多 $\lceil\frac{n}{B}\rceil$。

那么我们只要确定一下在那颗子树里，再往下走确定一条所在的链，剩下的部分就可以 $\log n$ 二分处理，这个时候询问次数是 $2\sqrt{n}+\log n$，$150$ 次左右，刚好卡满。

但这个时候如果树的深度一大就又被创飞了。

这个时候呢，我们可以发现，实际上如果只有一条路可以走了，那么肯定就在这条路上了，此时就不用询问了，这样就完成了这题。

~~有的消愁宏定义 $mid$，然后先给 $l,r$ 赋值再记录答案，难评。~~
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,M=70,INF=0x3f3f3f3f,mod=998244353;
int n,s,st,a[N],dep[N];vector<int>e[N],b;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    // #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='.'||c=='#'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void add(int u,int v){e[u].emplace_back(v),e[v].emplace_back(u);}
inline int query(int x){cout<<"? "<<x<<endl;cin>>x;s+=!x;return x;}
inline void dfs(int u,int ff)
{
    dep[u]=dep[ff]+1;a[u]=1;
    for(auto v:e[u]) if(v!=ff) dfs(v,u),a[u]=max(a[v]+1,a[u]);
}
inline void dfs1(int u,int ff)
{
    b.emplace_back(u);vector<int> c;
    for(auto v:e[u])
    {
        if(v==ff||a[v]<=s) continue;
        c.emplace_back(v);
    }
    for(int i=0;i<(int)c.size()-1;i++) if(query(c[i])) return dfs1(c[i],u);
    if(c.size()) dfs1(c.back(),u);
}
inline void solve()
{
    n=read();for(int i=1;i<=n;i++) e[i].clear();s=0;b.clear();
    for(int i=1,u;i<n;i++) u=read(),add(u,read());dfs(1,0);
    int x=0;for(int i=1;i<=n;i++) if(a[i]==1) x=i;b.emplace_back(1);
    if(query(x)) return cout<<"! "<<x<<endl,void();
    for(int i=1;i<M;i++) query(x);dfs1(1,1);
    int l=1,r=b.size()-1,ss=0,ans=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;x=mid>ss?mid-ss:-1;
        if(x==-1){l=mid+1;ans=mid;continue;}
        if(query(b[x])) l=mid+1,ans=mid;
        else r=mid-1,ss++;
    }
    if(ans>ss) return cout<<"! "<<b[ans-ss]<<endl,void();
    return cout<<"! "<<1<<endl,void();
}
signed main()
{
    int T=read();while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：happybob (赞：0)

赛时差点过了。

考虑树分块。毕竟是 CF 赛制，不考虑随机撒点，考虑使用确定性撒点算法。即 DFS 时每个点处理出最大深度然后进行确定性撒点。

撒点完就好办了。先随便找到一个叶子，先问问这个点是不是叶子。如果不是，按照深度大到小考虑每个关键点，如果在子树内，就交替询问叶子和这个点直到确定答案。

如果这个点不在任何关键点子树内，考虑使用剩下所有操作让这个点跳到根。操作次数卡的不紧，可以轻松通过。不过好像过不去 E2。

[Submission Link](https://codeforces.com/contest/1990/submission/271680757)。

---

