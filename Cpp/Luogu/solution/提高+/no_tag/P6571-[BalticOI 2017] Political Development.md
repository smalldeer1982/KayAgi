# [BalticOI 2017] Political Development

## 题目描述

某个有 $n$ 个成员的政党想要发展一些全新的政策。为了做到这一点，这个政党计划为了新的政策的发展，建立一个委员会。显然，当所有委员会委员的意见都不一致，并且这个委员会尽量大的时候，政策得以最好地发展。  
为了指出哪一对政治家的意见不一致以及哪一对意见一致，政党安排每一对可能的政治家讨论一个随机选择的话题。无论何时，如果两个政治家不能在指定的话题上达成统一意见，他们就会被记录在政党的功德册上。  
带着这本书，你被指定去完成找出最大的委员会，使得所有的委员的意见都不一致的任务。然而，找到一个大的委员会是非常有挑战的。仔细的分析结果显示，对于任意一个由党员所组成的非空的小组，存在至少一个小组成员，使得小组中与他的意见不一致的成员严格少于 $k$ 个。那么显然委员会不能有多于 $k$ 个成员。但是能够选出一个这个大小的委员会吗？找到最大的委员会的大小，使得其中没有人的意见是一致的。

---

一句话题意：

给一个图，满足对于任意点导出子图，存在一个节点的度数小于 $k$，求原图的最大团。

## 说明/提示

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（4 pts）：$k \le 2$，$n \le 5 \times 10^3$。
- Subtask 2（12 pts）：$k \le 3$，$n \le 5 \times 10^3$。
- Subtask 3（23 pts）：$d_i \le 10$。
- Subtask 4（38 pts）：$n \le 5 \times 10^3$。
- Subtask 5（23 pts）：$ k \le 5$。

对于 $100\%$ 的数据，$0 \le d_i<n\le 5 \times 10^4$，$1 \le k \le 10$。

#### 说明

**翻译自 [BOI 2017 D1](https://boi.cses.fi/files/boi2017_day1.pdf) T1 Political Development。**  
翻译者：@[FZzzz](https://www.luogu.com.cn/user/174045)。   
~~所以这题提供者为什么还是菜鸡书虫呢，小编也不知道，欢迎私下跟小编讨论吖~~

## 样例 #1

### 输入

```
5 3
2 1 2
3 0 2 3
3 0 1 4
2 1 4
2 2 3
```

### 输出

```
3```

## 样例 #2

### 输入

```
5 3
3 1 2 4
1 0
1 0
0
1 0
```

### 输出

```
2```

# 题解

## 作者：FZzzz (赞：5)

翻译者来水个题解。

首先我之前把一句话题意翻错了，翻成了：
>给一个图，每个点的度数不超过 $k$，求最大团。

先考虑这个东西咋做。

~~不是随便暴力吗。~~

就很显然地，钦定最大团里的某个点，然后在所有和它相连的点里枚举子集，判断是否可行，复杂度 $O(nk^22^k)$ ~~过了我请你吃糖~~。

我们预处理出一个点与哪些点连边，压位处理，这样就 $O(nk2^k)$ 了。

然后考虑原问题，我们想要把它转化成上面这个问题。

可以发现上面这个算法是很浪费的，因为一个子集被算了很多次。我们换个思路，可以枚举最大团里最小的节点，然后在它连向的后面的所有点里枚举子集。

问题是这样还是不能保证边数。可以考虑~~根据人类智慧~~构造一个排列，然后按上面的方法搞。

考虑到这个导出子图的度数限制，我们可以想到 dfs 处理，每次 dfs 到一个点就把它所有邻居的 $d$ 值减一，然后如果小于 $k$ 就访问它。

下面证明这个算法一定能得到一个结果：

根据算法可知，如果不能得到一个结果，那么一定是在把所有能访问的点都访问完之后，剩下的点的 $d$ 值全都不小于 $k$。那么这些点的生成子图不满足题中的性质，矛盾。于是命题得证。

然后有了这个我们就可以像上面一样暴力了，时间复杂度 $O(nk2^k)$。
```cpp
#include<algorithm>
#include<vector>
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
const int maxn=5e4+5;
int n,k,d[maxn];
vector<int> g[maxn],g2[maxn];
int pos[maxn],cnt=0;
bool vis[maxn];
void dfs(int u){
	vis[u]=1;
	pos[u]=cnt++;
	for(int i=0;i<(int)g[u].size();i++){
		int v=g[u][i];
		d[v]--;
		if(d[v]<k&&!vis[v]) dfs(v);
	}
}
bool beside(int u,int v){
	for(int i=0;i<(int)g2[u].size();i++)
		if(g2[u][i]==v) return 1;
	for(int i=0;i<(int)g2[v].size();i++)
		if(g2[v][i]==u) return 1;
	return 0;
}
int g3[maxn];
int calc(int u){
	for(int i=0;i<(int)g2[u].size();i++) g3[g2[u][i]]=0;
	for(int i=0;i<(int)g2[u].size();i++)
		for(int j=0;j<(int)g2[u].size();j++)
			if(i==j) g3[i]|=1<<j;
			else g3[i]|=beside(g2[u][i],g2[u][j])<<j;
	int ans=0;
	for(int i=0;i<(1<<g2[u].size());i++){
		int res=i,cnt=0;
		for(int j=0;j<(int)g2[u].size();j++) if(i>>j&1){
			res&=g3[j];
			cnt++;
		}
		if(res==i) ans=max(ans,cnt);
	}
	return ans+1;
}
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	k=readint();
	for(int i=0;i<n;i++){
		d[i]=readint();
		for(int j=0;j<d[i];j++) g[i].push_back(readint());
	}
	for(int i=0;i<n;i++) if(d[i]<k&&!vis[i]) dfs(i);
	for(int i=0;i<n;i++) for(int j=0;j<(int)g[i].size();j++)
		if(pos[g[i][j]]>pos[i]) g2[i].push_back(g[i][j]);
	int ans=0;
	for(int i=0;i<n;i++) ans=max(ans,calc(i));
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：robinyqc (赞：4)

来个乱搞题解。当然，复杂度其实应该没问题，而且它很好写。

### 题意简述

给定一张 $n$ 个点的图，满足任意子图存在至少一个点的度数小于等于 $k$。求其最大团。$n\leq 5\times 10^4, k \leq 10$。

### 解题思路

由于题目中并没有给出 $\sum d_i$ 的范围，可以猜测整张图边数只与 $n, k$ 有关，最多是 $nk$ 条边。进一步地，若一个子图点数为 $q$，那么边数最多 $qk$ 条。赛时你不需要考虑证明，因为边数至少要可以读入。

同时又有一个观察：从最大团中任意一个点开始搜索，得到的结果一样。所以不需要考虑顺序。

这启发我们类似无向图三元环计数，把边定向求解。具体的，若原图中 $\deg(a) < \deg(b)$，那么连一条 $a\to b$ 的有向边；若 $\deg(a) = \deg(b)$，那么编号小的连向编号大的。

对于这张新的图 $(V, E)$，一定有 $\forall a \in V, \operatorname{out}(a) = O\left(\sqrt{|E|}\right)$。原因是，设 $a$ 连向了 $q$ 个点，那么这 $q$ 个点度数都大于 $q$，总共就会贡献 $o(q^2)$ 条边。因为 $o(q^2) = \sqrt{|E|}$，所以 $q = O\left(\sqrt{|E|}\right)$。

然后就可以应用暴力搜索了。设当前图为 $G = (V, E)$。

1. 对当前图定向，设这个定向后的图为 $G' = (V', E')$。
2. 枚举 $V'$ 中的每个点 $p$。
3. 将 $p$ 加入当前搜索的团（当前答案）中。
4. 设 $A = \{v \mid (p, v)\in E'\}, B = \{(u, v)\mid u \in A, v\in A, (u, v)\in E\}$，那么应用 $G\gets (A, B)$。
5. 如果 $G = (\varnothing, \varnothing)$，那么回溯；否则递归地，回到操作 1。

用人话说就是枚举 $p$ 的所有出边，将这些点构成的子图拿出来递归求解。

### 代码实现

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 50050;

int n, k;
int ys[N];
int ans;

void check_ans(int x)
{
    ans = max(ans, x);
    if (ans == k + 1) {
        cout << k + 1;
        exit(0);
    }
}

void solve(int c, vector<vector<int> >& g)
{
    check_ans(c);
    if (g.empty()) return ;
    if (g.size() == 1) {
        check_ans(c + 1);
        return ;
    }
    vector<vector<int> > t;
    vector<int> tnum;
    int m = g.size();
    for (int i = 0; i < m; i++) {
        size_t szn = g[i].size();
        tnum.clear();
        for (int j : g[i]) {
            if (g[j].size() > szn || (g[j].size() == szn && j > i) ) {
                tnum.push_back(j);
                ys[j] = tnum.size();
            }
        }
        int s = tnum.size();
        t.resize(s); 
        for (int j = 0; j < s; j++) {
            t[j].clear();
            for (int to : g[tnum[j]]) {
                if (ys[to]) t[j].push_back(ys[to] - 1);
            }
        }
        for (int j : tnum) ys[j] = 0;
        solve(c + 1, t);
    }
}

signed main() 
{
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    cin >> n >> k;
    vector<vector<int> > e;
    e.resize(n);
    for (int i = 0, d; i < n; i++) {
        cin >> d;
        e[i].resize(d);
        for (int j = 0; j < d; j++) cin >> e[i][j];
    }
    solve(0, e);
    cout << ans << '\n';
    return 0;
}
```

### 复杂度分析

分析复杂度，显然就是每一层递归的点数的乘积。第二层点数是 $O\left(\sqrt {nk}\right)$ 的。第三层点数是 $O\left(\sqrt{\text{第二层点数}\times k}\right) = O\left(\sqrt{k\sqrt {nk}}\right) = O\left(n^{\frac 14}k^{\frac 34}\right)$。以此类推。点数减得很快，在第三层就基本降没了（感觉也卡不了？），然后后面每层都只有两三个点，层数也不深。而且第一层递归和第二层递归的复杂度可以合在一起，是 $O(nk)$ 的（枚举了每一条边）。所以不太严谨地讲，复杂度是 $O\left(n^{\frac {11}{8}} k^{\frac {21}8}\right) $ 的。由于很难卡到上限，可过。如果能卡到更高，然后把我的做法卡爆，可以在评论区里说。

当然，严谨地说，这不是多项式复杂度。其实 $k$ 的那个上标不应该那么写。在 $\frac nk$ 非常大的本题，应该是 $k^{\log\log n}$ 的。然后如果 $\frac nk$ 非常小，比如说 $n = k$，复杂度应该是接近 $k^n$ 的。

最后回收开头提到的结论，具体证明可以类似正解去证：每次拿出度数最小的节点，它在当前图上的度数 $\leq k$，所以贡献最多 $k$；删掉这个点，重复这个过程。发现每个点都最多贡献 $k$。那么边数就是 $\leq nk$ 的。

---

## 作者：HYXLE (赞：1)

## P6571 [BalticOI 2017] Political Development

诈骗题。

注意到题目给出了一个限制：任意一个点集 $S$ 的导出子图都有至少一个点，它的度数 $< k$。

所以不妨用一个类似拓扑排序的方式来求出最大值，每次将度数 $\leq k$ 的点塞进队列。

设 $u$ 为当前遍历到的点，则有 $v_1,v_2,...,v_n$ 表示点 $u$ 连接的还未遍历的点。

因为这样的点不会超过 $k$ 个，而 $k \leq 10$，所以考虑状压 $dp$。

设 $f_s$ 表示当前点集为 $s$ ，其导出子图是否为完全子图。

做 $dp$ 时枚举每一个点，将与其连接的点的点集状压出来。

设当前这个点为 $i$ ，与其连接的点集为 $w$ 。

则可以枚举状态 $s$，有转移方程 $f_{(s\&w)|(1<<i)} |= f_s$

做完 $dp$ 后枚举每一种状态，若点集 $s$ 合法，则其贡献为 $popcount(s) +1$ ，因为还要加上点 $u$。

最后对这些贡献取 $\max$ 即可。

## code:

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define count(x) (__builtin_popcount(x))
#define ll long long
#define R register
using namespace std;
const int N=5e4+5;
struct edge{int u,v,w;}e[2000005],e2[2000005];
int head[N],tot;
__gnu_pbds::gp_hash_table<int,bool> g[N];
int n,k,mx,deg[N],tmp[N];
vector<int> v[N];
namespace SUB3{
	bool view[N],f[1<<10];
	inline void toposort(){
		queue<int> q;
		for(R int i=1;i<=n;++i)if(deg[i]<=k)q.push(i);
		while(!q.empty()){
			int u=q.front();q.pop();
			view[u]=1;
			vector<int> able;
			for(R int i=0;i<tmp[u];++i){
				if(view[v[u][i]])continue;
				able.emplace_back(v[u][i]);
				--deg[v[u][i]];
				if(deg[v[u][i]]==k)q.push(v[u][i]);
			}
			int siz=able.size();
			memset(f,0,sizeof(bool)*(1<<siz));
			f[0]=1;
			for(R int i=0;i<siz;++i){
				int state=0,all=(1<<i)-1;
				for(R int j=0;j<i;++j){
					if(g[able[i]][able[j]])state|=(1<<j);
				}
				for(R int s=0;s<=all;++s){
					f[(s&state)|(1<<i)]|=f[s];
				}
			}
			for(R int i=0;i<(1<<siz);++i){if(f[i])mx=max(mx,count(i)+1);}
		}
	}
	inline void solve(){
		for(R int i=1;i<=n;++i){
			cin>>deg[i];v[i].resize(deg[i]);tmp[i]=deg[i];
			for(R int j=0;j<deg[i];++j)cin>>v[i][j],++v[i][j],g[i][v[i][j]]=1;
		}
		toposort();
		cout<<mx;
	}
}
inline void solve(){
	cin>>n>>k;
	if(n==1)return cout<<1,void();
	SUB3::solve();
}
int main(){
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	int _=1;while(_--)solve();
	return 0;
}
```

---

## 作者：mskqwq (赞：1)

显然原图一定有一个点度数 $<k$，考虑取出与这个点所有相邻的点的点集的导出子图求最大团，可以状压做到 $O(2^k)$。设 $f_{S}$ 表示 $S$ 是否为团，取出两个 $x,y \in S$，那么只需要根据 $f_{S-\{x\}}$ 和 $f_{S-\{y\}}$ 的值以及 $x,y$ 是否连边即可求出 $f_S$。

做完这个点之后把它连出去的边删掉，那么会出现新的度数 $<k$ 的点，用拓扑排序做这个，复杂度 $O(n2^k)$。

```cpp
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cstdio>
#include <vector>
#include <bitset>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#define fi first
#define se second
#define ep emplace
#define MISAKA main
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define lowbit(x) ((x)&(-(x)))
#define rg(x) x.begin(),x.end()
#define pc(x) __builtin_popcount(x)
#define mems(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _rep(i,a,b) for(int i=(a);i>=(b);--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline int read(){
    char c=getchar();int f=1,x=0;
    for(;c<48||c>57;c=getchar())if(c=='-') f=-1;
    for(;47<c&&c<58;c=getchar()) x=(x<<3)+(x<<1)+(c^48);
    return x*f;
}
const int N=5e4+10,mod=998244353;
int n,k,ans,deg[N],vis[N],lg[1<<10];bool f[1<<10];
vector<int> g[N];queue<int> q;
unordered_map<int,int> mp[N];
void misaka(){
    n=read(),k=read();
    if(k==1) puts("1"),exit(0);
    rep(i,1,n){
        deg[i]=read();
        rep(j,1,deg[i]) g[i].eb(read()+1);
    }
    rep(i,1,n)for(int j:g[i]) mp[i][j]=1;
    rep(i,1,n)if(deg[i]<k) q.ep(i);
    rep(i,0,9) lg[1<<i]=i;
    while(!q.empty()){
        int u=q.front();q.pop();
        if(vis[u]) continue;
        vector<int> vt;vis[u]=1;
        for(int v:g[u])if(!vis[v]){
            if((--deg[v])<k) q.ep(v);
            vt.eb(v);
        }
        int k=vt.size();
        rep(i,0,(1<<k)-1) f[i]=0;
        rep(i,0,(1<<k)-1){
            if(pc(i)<2){f[i]=1;continue;}
            int x=lowbit(i),y=lowbit(i^x);
            f[i]=f[i^x]&&f[i^y]&&mp[vt[lg[x]]][vt[lg[y]]];
        }
        rep(i,0,(1<<k)-1)if(f[i]) ans=max(ans,pc(i)+1);
    }
    printf("%d",ans);
}
bool __ed;
signed MISAKA(){
    #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs  ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB\n",abs(&__st-&__ed)/1024./1024);});
    #endif
    FIO("A");
    int T=1;
    while(T--) misaka();
    return 0;
}

```

---

## 作者：Zhao_daodao (赞：1)

# [BalticOI 2017] Political Development

## description

给定一个无权无向简单图，保证任意导出子图中，度数最小的点度数小于 $k$。求原图的最大团的大小。

$n\le 5\times 10^4,k\le 10$。

## solution

首先，求最大团是 `NP-hard` 的，肯定是运用性质。

---

先看一个简单的，考虑 $deg_i\le 10$ 怎么做。

可以枚举每一个点，计算如果当前点被包含在团中，最大团的大小。

枚举每一个邻居是否选入，设邻居个数为 $x$，当前的复杂度 $O(x2^x)$。

---

回到原题，运用性质，在初始的图中，肯定有一个点的度数小于 $k$，我们先统计这个点。

这个点算完之后，其他答案里就不会包含它了，可以直接删掉它。

你发现，删完之后，图是一个原图的导出子图！

也就是说，还会存在一个点，度数小于 $k$。

不断重复这个过程，就做完了。复杂度 $O(nk2^k)$。



## code

```cpp
#include<bits/stdc++.h>
#define Pair pair<int,int>
using namespace std;
const int MAXN=5e4+5;
set<int>G[MAXN];
int n,k;
priority_queue<Pair,vector<Pair>,greater<Pair> >q;
int vis[MAXN],g[MAXN],fl[MAXN];
set<Pair>s;
inline int calc(int x){
	int ans=0,siz=G[x].size()+1;
	int st=0;g[++st]=x;for(int v:G[x])g[++st]=v;
	for(int i=1;i<=siz;i++){
		fl[i]=0;
		for(int j=1;j<=siz;j++){
			fl[i]|=((s.find(Pair(g[i],g[j]))!=s.end())<<(j-1));
		}
	}
	for(int S=1;S<(1<<siz);S+=2){//因为 x 肯定要选，所以最后一位肯定是 1
		bool flag=1;
		for(int i=1;i<=siz;i++)if(S>>(i-1)&1){
			if((fl[i]&S)!=S){flag=0;break;}
		}
		if(flag)ans=max(ans,__builtin_popcount(S));
	}
	return ans;
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		int siz;cin>>siz;
		for(int x,_=1;_<=siz;_++){
			cin>>x;x++;
			G[i].insert(x);s.insert(Pair(i,x));
		}
		q.push(Pair(G[i].size(),i));
	}
	for(int i=1;i<=n;i++)s.insert(Pair(i,i));
	int ans=1;
	while(q.size()){
		int u=q.top().second;q.pop();
		if(vis[u])continue;vis[u]=1;
		ans=max(ans,calc(u));
		for(int v:G[u])G[v].erase(u),q.push(Pair(G[v].size(),v));
	}
	cout<<ans<<"\n";
}
```

---

