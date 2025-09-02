# House Planning

## 题目描述

There are $ n $ houses in your city arranged on an axis at points $ h_1, h_2, \ldots, h_n $ . You want to build a new house for yourself and consider two options where to place it: points $ p_1 $ and $ p_2 $ .

As you like visiting friends, you have calculated in advance the distances from both options to all existing houses. More formally, you have calculated two arrays $ d_1 $ , $ d_2 $ : $ d_{i, j} = \left|p_i - h_j\right| $ , where $ |x| $ defines the absolute value of $ x $ .

After a long time of inactivity you have forgotten the locations of the houses $ h $ and the options $ p_1 $ , $ p_2 $ . But your diary still keeps two arrays — $ d_1 $ , $ d_2 $ , whose authenticity you doubt. Also, the values inside each array could be shuffled, so values at the same positions of $ d_1 $ and $ d_2 $ may correspond to different houses. Pay attention, that values from one array could not get to another, in other words, all values in the array $ d_1 $ correspond the distances from $ p_1 $ to the houses, and in the array $ d_2 $ — from $ p_2 $ to the houses.

Also pay attention, that the locations of the houses $ h_i $ and the considered options $ p_j $ could match. For example, the next locations are correct: $ h = \{1, 0, 3, 3\} $ , $ p = \{1, 1\} $ , that could correspond to already shuffled $ d_1 = \{0, 2, 1, 2\} $ , $ d_2 = \{2, 2, 1, 0\} $ .

Check whether there are locations of houses $ h $ and considered points $ p_1 $ , $ p_2 $ , for which the founded arrays of distances would be correct. If it is possible, find appropriate locations of houses and considered options.

## 说明/提示

In the image below you can see the sample solutions. Planned houses are shown in bright colours: pink and purple. Existing houses are dim.

In test case $ 1 $ , the first planned house is located at point $ 0 $ , the second at point $ 10 $ . The existing house is located at point $ 5 $ and is at a distance of $ 5 $ from both planned houses.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1735E/24be6c6140dba3b9e3765dad2410e59b0e469172.png)It can be shown that there is no answer for test case $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1735E/44e0ac4869d2d36fece9962d8edb1180f1261843.png)In test case $ 3 $ , the planned houses are located at points $ 33 $ and $ 69 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1735E/e229a09a9182f5afb38575bceecc77c5c2d947c2.png)Note that in test case $ 4 $ , both plans are located at point $ 1 $ , where one of the existing houses is located at the same time. It is a correct placement.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1735E/06ab87496238d1bfcf3ef836bec5400ed16bc958.png)

## 样例 #1

### 输入

```
4
1
5
5
2
10 12
5 20
2
10 33
26 69
4
0 2 1 2
2 2 1 0```

### 输出

```
YES
5 
0 10
NO
YES
0 43 
33 69
YES
1 0 3 3
1 1```

# 题解

## 作者：nkwhale (赞：5)

[题目传送门](https://codeforces.com/contest/1735/problem/E)

[阅读体验应该好点吧](https://www.cnblogs.com/whale-at-cola/p/solution-cf1735e.html)

分享一个 $O(n^2)$ 的做法。

首先，不妨假设 $p_1$ 为 $0$，枚举到 $p_1$ 的距离为 $d_{1,1}$ 的房子到 $p_2$ 的距离是哪一个，可以得到 $2n$ 个可能作为答案的 $p_2$ 值，考虑对于每一个 $p_2$ 考虑问题是否有解。

容易想到使用二分图匹配的方式判断，若有 $|p_2-d_{2,i}|=d_{1,j}$ 或 $p_2+d_{2,i}=d_{1,j}$，即存在房子的位置满足 $p_1$ 到它的距离为 $d_{1,i}$，$p_2$ 到它的距离为 $d_{2,j}$，则在左侧 $i$ 点和右侧 $j$ 点之间连边，若对于一个 $p_2$ 建出的二分图有完美匹配则有解，根据有哪些匹配边容易得到房子的位置。

因为对于每个点对 $(i,j)$，其至多在两个可行的 $p_2$ 对应建出的二分图上有连边，所以总边数是 $O(n^2)$ 的，使用 Dinic 实现二分图匹配的话，复杂度为 $O(n^2 \sqrt n)$，足以通过本题。

其实这个思路还可以进一步优化，对 $d$ 序列排序（$d$ 有序方便下文叙述），把所有 $d$ 相同的点缩在一起（两边都这么做）进行多重匹配，该点可参与匹配的边数为原本是这个 $d$ 的点的个数。

那么对于每一个 $p_2$，其构建出的二分图边数都在 $2n$ 以内，并且每个点的度数都不超过 $2$，容易发现在这个限制下，边只会存在链和环形的结构；又因为在 $i$ 增大时，$|p_2-d_{2,i}|$ 是先减小后增大的，$p_2+d_{2,i}$ 是单调增大的，而这又是一个二分图，那么怎么也不可能连出环，这里不详细证明了，可以画图手模理解一下。

那么就只有链了，可以从一端开始对每个左部点直接分配匹配边数，贪心地每次尽量向前（已经分配过的方向）分配，给后面的点留出更多的空间；当一个左部点 $i$ 的限制无法满足时，说明它前面必有一个左部点 $j$（可能就是 $i$ ）使得 $j$ 到 $i$ 的这一段中的左部点（包括 $i,j$）可参与匹配的边数和大于与其相邻的所有右部点的可参与匹配的边数和，根据 Hall 定理，这个图一定没有完美匹配，所以这个贪心方法是正确的。

这个贪心过程显然是线性的，对于 $i$ 寻找两类边对应的 $j$ 也可以使用双指针或哈希表做到线性，则对于每个 $p_2$ 都可以 $O(n)$ 判断和构造，总时间复杂度 $O(n^2)$。

实现的时候，由那个单谷和单调性的性质还可以发现：对于一条链，上面所有左部点也是单谷的，所以可以直接倒过来枚举 $i$ 来做上面那个贪心，相当于从两边向中间做，不用专门把链抠出来搞。

注意 $p_2=0$ 的时候两类边会连到同一个位置上，可以一开始就判掉；还有题目要求要让答案是非负数，把所有点整体位移一下即可。

主要部分参考代码：
```cpp
const int N=1010;
int l,n,m,aa[N],bb[N],a[N],ca[N],b[N],cb[N],c[N],d[N],p[N],cnt,ans[N];

inline void add(int v,int x){while(v--) ans[++cnt]=x;}
inline bool chk(int x){
	if(!x) return 0;
	cnt=0;
	for(re int i=1;i<=n;++i) c[i]=ca[i];
	for(re int i=1;i<=m;++i) d[i]=cb[i],p[i]=0;
	for(re int i=1,j=n;i<=m&&x>=b[i];++i){
		while(j&&x-b[i]<a[j]) --j;
		if(j&&x-b[i]==a[j]) p[i]=j;
	}
	for(re int i=1,j=1;i<=m;++i){
		while(j<=n&&b[i]-x>a[j]) ++j;
		if(j<=n&&b[i]-x==a[j]) p[i]=j;
	}
	for(re int i=m,j=n,v;i>=1;--i){
		while(j&&x+b[i]<a[j]) --j;
		if(j&&x+b[i]==a[j]) v=min(d[i],c[j]),d[i]-=v,c[j]-=v,add(v,x+b[i]);
		if(p[i]) v=min(d[i],c[p[i]]),d[i]-=v,c[p[i]]-=v,add(v,x-b[i]);
		if(d[i]) return 0;
	}
	assert(cnt==l),puts("YES");int v=0;
	for(re int i=1;i<=l;++i) v=min(v,ans[i]);
	for(re int i=1;i<=l;++i) printf("%d%c",ans[i]-v," \n"[i==l]);
	printf("%d %d\n",-v,x-v);
	return 1;
}

inline void sol(){
	l=read(),n=m=0,aa[0]=bb[0]=-1;
	for(re int i=1;i<=l;++i) aa[i]=read();
	for(re int i=1;i<=l;++i) bb[i]=read();
	sort(aa+1,aa+l+1),sort(bb+1,bb+l+1);int fl=1;
	for(re int i=1;i<=l;++i) fl&=aa[i]==bb[i];
	if(fl){
		puts("YES");
		for(re int i=1;i<=l;++i) printf("%d%c",aa[i]," \n"[i==l]);
		puts("0 0");
		return ;
	}
	for(re int i=1;i<=l;++i) if(aa[i]!=aa[i-1]) a[++n]=aa[i],ca[n]=1;else ++ca[n];
	for(re int i=1;i<=l;++i) if(bb[i]!=bb[i-1]) b[++m]=bb[i],cb[m]=1;else ++cb[m];
	for(re int i=1;i<=m;++i) if(chk(abs(aa[1]-b[i]))||chk(aa[1]+b[i])) return ;
	puts("NO");
}
```

---

## 作者：MSqwq (赞：3)

方法挺多的一道题  
题意：在数轴上有 n 个点，每个点为 $h_i$，和两个点 $p_1$，$p_2$。有两个数组 $d_i$ 为 $h$ 到 $p_i$ 的距离。现在你忘记 $h$ 以及 $p_1$，$p_2$，只记得 $d_1$，$d_2$ 并且 $d_1$，$d_2$ 的顺序被打乱了。让你还原出一个可能的 $h$ 以及 $p_1$,$p_2$。

题解：  
先忽略非负这个条件。我们不妨让 $p_1=0$ 或者 $p_2=0$，因为整体平移的距离不变。
对于一个点 x，它到两个点的和分别为$\left|p_1-x \right|$，$\left|p_2-x\right|$。  
要么这两个值的和为 $f=\left|p_1-p_2\right|$（处于中间）要么差的绝对值等于 f（处于一边）。

知道这个性质之后我们可以进行贪心（当然本题也可以网络流或者二分图匹配或者用 map 贪心，这里主要说用 multiset）。   
关于 multiset 不清楚的同学可以看 [multiset用法总结](https://blog.csdn.net/sodacoco/article/details/84798621)  
回到本题，不妨设 $p_1=0$，同样枚举 $p_2$，不过可以只考虑 $p_2\ge 0$ 的情况，即 $p_2=d_1[i] + d_2[0]$ 或者 $p_2 = \left| d_1[i] - d_2[0] \right|$。
    
然后每次考虑 $d_1$，$d_2$ 中剩余的最大的数，这个数如果大于 $p_2$，则说明它不在 $p_1$，$p_2$ 中间，否则说明剩下的所有数都在 $p_1$，$p_2$ 中间。  
所以想到可以用双指针 multiset 来做。  

这里给出 multiset 的代码qwq：
```
#include<cstdio>
#include<cstring>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>
#include<queue>
#include<stack>
#include<math.h>
#define ll long long
using namespace std;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0',c=getchar();}
	return x*f;
}
const int N=1e3+10;
int d1[N],d2[N];
int n;
vector<int>v;
bool check(int x)
{
    multiset<int>se1,se2;
    vector<int>().swap(v);
    
    for(int i=1;i<=n;i++)
    {
        se1.insert(d1[i]);
        se2.insert(d2[i]);
    }
 	
    for (auto it=se1.rbegin();it!=se1.rend();it++)
    {
        if(se2.find(*it+x)!=se2.end())
        {
            se2.erase(se2.find(*it+x));
            v.push_back(-*it);
        }
        else if(se2.find(*it-x)!=se2.end())
        {
            se2.erase(se2.find(*it-x));
            v.push_back(*it);
        }
        else if(se2.find(x-*it)!=se2.end())
        {
            se2.erase(se2.find(x-*it));
            v.push_back(*it);
        }
        else return false;
    }
    return true;
}
void solve()
{
	n=read();
	for(int i=1;i<=n;i++)d1[i]=read();
	for(int i=1;i<=n;i++)d2[i]=read();
	
	bool ans=0;
	int diff=-1;
	for(int i=1;i<=n;i++)
	{
		if(check(abs(d1[1]-d2[i])))
		{
			ans=1;
			diff=abs(d1[1]-d2[i]);
			break;
		}
		if(check(d1[1]+d2[i]))
		{
			ans=1;
			diff=d1[1]+d2[i];
			break;
		}
	}
	if(!ans)
	{
		printf("NO\n");
		return;
	}
	printf("YES\n");
	int mn=0;
	sort(v.begin(),v.end());
	mn=min(mn,v[0]);
	for(int i=0;i<v.size();i++)printf("%d ",v[i]-mn);
	printf("\n");
	printf("%d %d\n",-mn,-mn+diff);
}
int main()
{
	int T=read();
	while(T--)solve();
	return 0;
}
```


---

## 作者：tribool4_in (赞：1)

过于好笑以至于我迫切的想要写一篇题解。

笑点解析：$O(n^3)$ 总时长不到 0.5s 丝毫不虚，$O(n^2)$ `unordered_map` （带自定义哈希）成为全场瓶颈，手写直接取模哈希不判冲突直接跑过。

令两个观测者距离为 $D$，则一对 $d_{0,i},d_{1,j}$ 对应同一个楼房的必要条件为 $d_{0,i}+d_{1,j}=D$ 或 $|d_{0,i}-d_{1,j}|=D$。注意到这样的总对数只有 $O(n^2)$ 对，于是可以将所有这样的点对以 $D$ 为下标存入桶。

考虑固定 $D$ 如何处理。首先如果桶内点对个数 $<n$ 则一定不合法；否则我们相当于需要选出若干点对来给两个观测者眼中的楼房距离一一匹配，这不是我们二分图匹配吗，直接跑匈牙利算法，时间复杂度 $O(n^3)$，常数较小得以通过。

关键之处在于这个桶，使用 `map` $10^6$ 套 `vector` 直接草飞，`unordered_map` 死活卡不过 #48 #49。于是直接开一个大小为 $M=2\times 10^6+3$ 的数组，哈希函数直接设 $h:x \to x \bmod M$ 不带一点冲突判断然后过了。不过这题小冲突大概率不重要就是了！

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10, M = 2e6 + 3;
int n, d[2][N];
struct edge {
    int u, v;
    int tp;
};
vector<edge> mp[M];

namespace Match {
    vector<pair<int, int>> G[N];
    void add_edge(int u, int v, int w) { G[u].emplace_back(v, w); }
    bool vis[N];
    int mat[N], matp[N];
    bool dfs(int x) {
        for (auto [v, w] : G[x]) {
            if (vis[v]) continue;
            if (!mat[v]) {
                mat[v] = x;
                matp[v] = w;
                return 1;
            }
            vis[v] = 1;
            if (dfs(mat[v])) {
                mat[v] = x;
                matp[v] = w;
                return 1;
            }
        }
        return 0;
    }
    int run() {
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) vis[j] = 0;
            cnt += dfs(i);
        }
        return cnt;
    }
    void reset_edge(int u, int v) { G[u].clear(), mat[v] = matp[v] = 0; }
}  // namespace Match
int p[2], h[N];
int mat[2][N], matp[2][N];
void getans() {
    for (int i = 1; i <= n; i++) {
        mat[1][i] = Match::mat[i], mat[0][mat[1][i]] = i;
        matp[1][i] = matp[0][mat[1][i]] = Match::matp[i];
    }
    h[1] = 0;
    p[0] = d[0][1];
    if (matp[0][1]) p[1] = d[1][mat[0][1]];
    else p[1] = -d[1][mat[0][1]];
    for (int i = 2; i <= n; i++) {
        int tp = matp[0][i], di = d[0][i];
        if (p[0] < p[1]) h[i] = p[0] + (tp == 2 ? -di : di);
        else h[i] = p[0] - (tp == 2 ? -di : di);
    }
}
void work() {
    cin >> n;
    for (int o = 0; o < 2; o++)
        for (int i = 1; i <= n; i++) cin >> d[o][i];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            mp[(d[0][i] + d[1][j]) % M].push_back(((edge){i, j, 0}));
            if (d[0][i] >= d[1][j]) mp[(d[0][i] - d[1][j]) % M].push_back(((edge){i, j, 1}));
            else mp[(d[1][j] - d[0][i]) % M].push_back(((edge){i, j, 2}));
        }
    }

    bool ok = 0;

    auto work = [&](vector<edge> &vec) {
        for (auto e : vec) Match::add_edge(e.u, e.v, e.tp);
        int res = Match::run();
        if (res == n) {
            ok = 1;
            getans();
        }
        for (auto e : vec) Match::reset_edge(e.u, e.v);
    };

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x = (d[0][i] + d[1][j]) % M, y = abs(d[0][i] - d[1][j]) % M;
            if (mp[x].size() >= n) {
                work(mp[x]);
                if (ok) break;
            }
            mp[x].clear(), mp[x].shrink_to_fit();
            if (mp[y].size() >= n) {
                work(mp[y]);
                if (ok) break;
            }
            mp[y].clear(), mp[y].shrink_to_fit();
        }
        if (ok) break;
    }

    if (!ok) {
        cout << "NO\n";
        return;
    }
    int D = min(min(p[0], p[1]), 0);
    for (int i = 1; i <= n; i++) D = min(D, h[i]);
    cout << "YES\n";
    for (int i = 1; i <= n; i++) cout << h[i] - D << " \n"[i == n];
    cout << p[0] - D << ' ' << p[1] - D << '\n';

    // Only need to clear when ok=1 YES
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x = (d[0][i] + d[1][j]) % M, y = abs(d[0][i] - d[1][j]) % M;
            mp[x].clear(), mp[x].shrink_to_fit();
            mp[y].clear(), mp[y].shrink_to_fit();
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        work();
    }
    return 0;
}
```

---

## 作者：Reunite (赞：1)

我已经做好调一年的准备了，结果它一发全过了。

---

显然最终情况可以任意平移，不妨设 $p_1=0,p_1\le p_2$，考虑哪些位置的 $p_2$ 可能是合法的，只需要选择任意一个点考虑，对于 $d_{0,1}$ 可能与之对应的任意一种 $d_{1,x}$，其 $p_2$ 只有 $d_{0,1}+d_{1,x},|d_{0,1}-d_{1,x}|$ 两种情况，对应这个点在中间或两侧。也就是说合法的 $p_2$ 总共情况最多只有 $2n$ 个，考虑在 $n\sqrt n$ 的复杂度上界内 check 一个 $(0,p_2)$ 是否合法。

没去想啥高妙做法，考虑到这个其实也是一种匹配，如果在坐标上考虑的话，位置在 $pos$ 的点在 $(0,p_2)$ 意义下也最多只有 $3$ 个能匹配的位置，对应在左边，中间，右边。连边跑最大流即可。

但是直接连边数会退化到 $n^2$，因为一个位置可以套很多相同的点，正确的做法是把相同位置的点缩起来然后连边边数就是 $O(n)$ 的了。

总复杂度 $O(n^2\sqrt n)$。套 STL 的时候要仔细一点。

---

```cpp

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

int t,n,cnt,p1,p2,tt,A,B;
int h[2005];
int cur[2005];
int dep[2005];
bool mp[2005];
int d[2][2005];
int it[2005];
int ti[2005];
struct node{int v,nxt,c;}edge[4000005];
map <int,int> id[2],ct[2];

inline void addedge(int u,int v,int c){
	edge[++cnt]={v,h[u],c};
	h[u]=cnt;
	edge[++cnt]={u,h[v],0};
	h[v]=cnt;
	return ;
}

inline bool bfs(int S,int T){
	memset(dep,-1,sizeof(dep));
	dep[S]=0;
	queue <int> q;
	q.push(S);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=h[u];i;i=edge[i].nxt){
			int v=edge[i].v;
			if(edge[i].c&&dep[v]==-1){
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return (dep[T]!=-1);
}

inline int dfs(int u,int T,int flow){
	if(u==T||!flow) return flow;
	int res=0;
	mp[u]=1;
	for(int i=cur[u];i;i=edge[i].nxt){
		cur[u]=i;
		int v=edge[i].v;
		if(mp[v]||!edge[i].c||dep[v]!=dep[u]+1) continue;
		int d=dfs(v,T,min(flow,edge[i].c));
		res+=d;
		edge[i].c-=d;
		edge[i^1].c+=d;
		flow-=d;
	}
	mp[u]=0;
	return res;
}

inline void init(){
	cnt=1;
	for(int i=1;i<=2*n+3;i++) h[i]=0;
	return ;
}

inline int Dinic(int S,int T){
	int f=0;
	while(bfs(S,T)){
		for(int i=1;i<=T;i++) cur[i]=h[i];
		f+=dfs(S,T,1e9);
	}
	return f;
}

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

int dis[1005];

inline int get(int x,int y){
	if(x+y==p2) return x;
	if(x>y) return x;
	return -x;
}

inline bool check(){
	init();
	int L=p2-p1;
	for(auto tmp:id[0]){
		int x=tmp.first,xdd=tmp.second,y;
		y=L-x;
		if(id[1].count(y)) addedge(xdd,id[1][y],1e9);
		y=x-L;
		if(id[1].count(y)) addedge(xdd,id[1][y],1e9);
		y=L+x;
		if(id[1].count(y)) addedge(xdd,id[1][y],1e9);
	}
	int S=tt+1,T=S+1;
	for(auto tmp:id[0]) addedge(S,tmp.second,ct[0][tmp.first]);
	for(auto tmp:id[1]) addedge(tmp.second,T,ct[1][tmp.first]);
	int f=Dinic(S,T);
	if(f^n) return 0;
	puts("YES");
	int nm=0;
	for(int u=1;u<=A;u++){
		for(int i=h[u];i;i=edge[i].nxt){
			int v=edge[i].v;
			if(v<=B&&edge[i^1].c)
				for(int j=1;j<=edge[i^1].c;j++) dis[++nm]=get(it[u],ti[v]);
		}
	}
	int mn=0;
	for(int i=1;i<=n;i++) mn=min(mn,dis[i]);
	for(int i=1;i<=n;i++) printf("%d ",dis[i]-mn);
	printf("\n%d %d\n",p1-mn,p2-mn);
	return 1;
}

int main(){
	in(t);
	while(t--){
		in(n);
		tt=0;
		id[0].clear(),id[1].clear();
		ct[0].clear(),ct[1].clear();
		for(int i=1;i<=n;i++) in(d[0][i]),ct[0][d[0][i]]++,id[0][d[0][i]]=(id[0][d[0][i]]?id[0][d[0][i]]:++tt);
		A=tt;
		for(int i=1;i<=n;i++) in(d[1][i]),ct[1][d[1][i]]++,id[1][d[1][i]]=(id[1][d[1][i]]?id[1][d[1][i]]:++tt);
		B=tt;
		for(auto tmp:id[0]) it[tmp.second]=tmp.first;
		for(auto tmp:id[1]) ti[tmp.second]=tmp.first;
		p1=0;
		bool ok=0;
		for(int i=1;i<=n;i++){
			p2=d[0][1]+d[1][i];
			if(check()){ok=1;break;}
			p2=abs(d[0][1]-d[1][i]);
			if(check()){ok=1;break;}
		}
		if(!ok) puts("NO");
	}

	return 0;
}

```

---

## 作者：Shunpower (赞：0)

我都会，鉴定为水紫。

## Sol

首先考虑 $p_1,p_2$ 之间的距离 $L$，很容易发现对于真正的配对的 $(d_{1,i},d_{2,j})$，一定要么 $|d_{1,i}-d_{2,j}|=L$，要么 $d_{1,i}+d_{2,j}=L$。由于真正的 $L$ 一定要使得 $n$ 个位置都匹配上，所以我们枚举所有 $(i,j)$，把 $d_{1,i}+d_{2,j}$ 和 $|d_{1,i}-d_{2,j}|$ 都扔进桶里，把桶里所有出现次数 $\geq n$ 的都拿出来当成 $L$ 进行一次检查。

根据抽屉原理，最多只有 $2n$ 个元素拿出来 check。但是“放进桶里”这个操作非常卡常，往 `map` 里面插 $10^6$ 个元素会被 #48 卡得根本过不了，我改成哈希表才跑得飞快。

考虑怎么检查 $L$。事实上这个问题等价于给 $d_1,d_2$ 两两配对，使得恰好全部分完，所以再转化一下可以得到一个 Dinic 做法，但是我太菜了所以我不会。

可以发现 $d$ 可以分为两类。$d\leq L$ 的一类必然要配一个**不同数组中的** $L-d$ 或者 $d+L$，$d>L$ 的一类必然要配一个**不同数组中的** $d-L$ 或者 $d+L$。我们考虑先把 $d>L$ 的一类配了，这样 $d\leq L$ 就没法选择 $d+L$ 这种情况了（一定会被 $d>L$ 配掉），然后就可以直接在 $L$ 里面对折配 $d\leq L$ 的。

最后只需要得知是否所有 $d$ 都不重不漏的配上了就行。

想到这里怎么配完 $d>L$ 也呼之欲出了。我们把所有 $d>L$ 全部拉出来从大到小排序，配完一个再往小了做，这样每次做的都是所有 $d$ 中的最大值，能且只能选择 $d-L$ 这种情况。对于选择 $d+L$ 的情况，可以发现这和在 $d'=d+L$ 处选择 $d-L$ 等价。

容易发现以上配法就是最优的。使用 `map` 维护 $d$ 及其所在数组这两个属性构成的二元组的出现次数就能很方便地实现配对过程。注意配对时的两个 $d$ 需要来自不同的数组。

如果存在任何一次配不上了或者最后没有配完 $n$ 个都可以认定这个 $L$ 是不行的。

配对过程中通过维护房子到 $p_1,p_2$ 各自的距离可以推算出当最左边的房子在 $0$ 处时的 $p_1,p_2$，然后按照这个距离摆放房子即可输出构造方案。

总体来说除了第一步卡常比较恶心以外还挺好写的。

时间复杂度 $\mathcal O(n^2\log n)$。

## Code

```cpp
int T;
int n;
int d[3][N];
const int M=20070737;
int p[M];
map <pii,int,greater<pii>> ct;
vector <pair<pii,int>> house;//d(p1),d(p2),times
int tl;
il bool check(int ans){
    house.clear();
    ct.clear();
    fr1(i,1,n) ct[mp(d[1][i],1)]++,ct[mp(d[2][i],2)]++;
    int sum=0;
    for(auto &i:ct){
        if(!i.se) continue;
        int dis=i.fi.fi,op=i.fi.se;
        if(dis<ans) break;
        if(ct[mp(dis-ans,op^3)]<i.se) return 0;
        ct[mp(dis-ans,op^3)]-=i.se;
        if(op==1) house.pb(mp(mp(dis,dis-ans),i.se));
        if(op==2) house.pb(mp(mp(-(dis-ans),-dis),i.se));
        sum+=i.se;
    }
    for(auto &i:ct){
        if(!i.se) continue;
        int dis=i.fi.fi,op=i.fi.se;
        if(dis>=ans) continue;
        if(ct[mp(ans-dis,op^3)]<i.se) return 0;
        ct[mp(ans-dis,op^3)]-=i.se;
        if(op==1) house.pb(mp(mp(dis,-(ans-dis)),i.se));
        if(op==2) house.pb(mp(mp(ans-dis,-dis),i.se));    
        sum+=i.se;
    }
    if(sum!=n) return 0;
    return 1;
}
il void construct(){
    cout<<"YES\n";
    int p1=0,p2=0;
    for(auto i:house) p1=max(p1,-i.fi.fi);
    p2=p1+house[0].fi.fi-house[0].fi.se;
    for(auto i:house){
        fr1(_,1,i.se) cout<<p1+i.fi.fi<<' ';
    }
    cout<<'\n';
    cout<<p1<<" "<<p2<<'\n';
}
il void solve(){
    cin>>n;
    fr1(i,1,2) fr1(j,1,n) cin>>d[i][j];
    fr1(i,1,n){
        fr1(j,1,n){
            p[(d[1][i]+d[2][j])%M]++;
            p[(max(d[1][i],d[2][j])-min(d[1][i],d[2][j]))%M]++;
        }
    }
    fr1(i,1,n){
        fr1(j,1,n){
            if(p[(d[1][i]+d[2][j])%M]>=n){
                p[(d[1][i]+d[2][j])%M]=0;
                bool f=check(d[1][i]+d[2][j]);
                if(f){
                    construct();
                    return;
                }
            }
            if(p[(max(d[1][i],d[2][j])-min(d[1][i],d[2][j]))%M]>=n){
                p[(max(d[1][i],d[2][j])-min(d[1][i],d[2][j]))%M]=0;
                bool f=check(max(d[1][i],d[2][j])-min(d[1][i],d[2][j]));
                if(f){
                    construct();
                    return;
                }
            }
        }
    }
    cout<<"NO\n";
}
```

---

## 作者：封禁用户 (赞：0)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF1735E)

[CF](https://codeforces.com/problemset/problem/1735/E)

我看题解区很多大佬都用了网络流来匹配，但本人不会。于是就探究了更为易懂的做法。

### 分析

我们令两观测点间的距离为 $L$。首先，由于楼房要么在两观测点的中间，要么在两观测点的两边，所以有 $L = d_1 + d_2$ 或者 $L = |d_1 - d_2|$。我们随便选取一个 $d_1$，显然如果方案可行它必须匹配，所以我们有了 $2n$ 个 $L$ 的可能值，判断是否可行即可。

那如何判断呢：我们把所有的 $d_1$ 和 $d_2$ 都丢进一个 multiset 中，并记录它是 $d_1$ 还是 $d_2$。为了一一匹配，我们按数字从大到小匹配。先取出最大的，如果值为 $x$，但在 multiset 中的另一个部分并不存在值为 $|L-x|$ 数，即为非法。否则，就把这两个数给记下来，并且 erase 掉，继续操作。如果可行，就输出这组解。

时间复杂度为 $O(n^2 \log{n})$，稍微卡一下常就能过。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10); 
	putchar(x%10+48);
}
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define N 1010
int ans[N][2],d1[N],d2[N],t,n;
struct node
{
	int x;
	bool b;
	inline bool friend operator<(const node &X,const node &Y)
	{
		return X.x > Y.x||(X.x == Y.x&&X.b > Y.b);	
	} 
};
multiset<node> s;
bool check(int L)
{
	s.clear();
	F(i,1,n) s.insert((node){d1[i],0}),s.insert((node){d2[i],1});
	int len = 0;
	while(s.size())
	{
		node now = *s.begin();
		s.erase(s.begin());	
		++len;
		auto p = s.find((node){abs(now.x-L),now.b^1});
		if(p == s.end()) return 0;
		ans[len][now.b] = now.x,ans[len][now.b^1] = abs(now.x-L);
		s.erase(p);
	}
	puts("YES");
	int mn = 0;
	F(i,1,n) 
	{
		if((ans[i][0] <= L&&ans[i][1] <= L)||ans[i][0] > ans[i][1]) mn = min(mn,ans[i][0]);
		else mn = min(mn,-ans[i][0]);
	}
	F(i,1,n) 
	{
		if((ans[i][0] <= L&&ans[i][1] <= L)||ans[i][0] > ans[i][1]) write(ans[i][0]-mn);
		else write(-ans[i][0]-mn);
		putchar(' ');
	}
	putchar('\n');
	write(-mn),putchar(' ');
	write(L-mn),putchar('\n');
	return 1;
}
int main()
{
	read(t);
	while(t--)
	{
		read(n);
		F(i,1,n) read(d1[i]);
		F(i,1,n) read(d2[i]);
		bool flag = 1;
		F(i,1,n)
			if(check(d1[1]+d2[i])||check(abs(d1[1]-d2[i])))
			{
				flag = 0;
				break;
			}
		if(flag) puts("NO");
	}
	return 0;
}
```


---

## 作者：HyperSQ (赞：0)

朋友的房子可以在 $p_0,p_1$（下文简称为两原点）的同一侧，也可能在两原点之间。也就是说，对于某个合法情境，两原点之间的距离 $|p_0-p_1|$ 一定为某个房子的 $r_0+r_1$ 和 $|r_0-r_1|$ 其中之一。题目的距离序列是乱序的，这提示我们去匹配 $r_0$ 和 $r_1$ 数组，使得对于所有匹配关系可以对应同一个 $|p_0-p_1|$。

我们可以先考虑枚举 $L=|p_0-p_1|$。考虑 $r_{0,1}$ 和 $r_{1,i}$ 匹配，那么我们可以得到 $L$ 的两种情况 $r_{0,1}+r_{1,i}$ 和 $|r_{0,1}-r_{1,i}|$，可以 $O(n)$ 枚举。接下来就是匹配了。

有两种方法。第一种是暴力网络流，假如我们已经知道了 $L$，那么我们可以让 $r_{0,i}$ 和 $r_1$ 中的 $r_{0,i}+L$ 和 $|r_{0,i}-L|$ 匹配。建图跑 dinic，在残量网络上构造方案即可。虽然建出来的图是二分图，但是到汇点的边并不一定为 $1$ ，并不是二分图匹配模型，所以蒟蒻并不知道此方法的复杂度QwQ。

第二种是正解，更巧妙一点。在确定了 $L$ 后，考虑每次在 $r_0$ 与 $r_1$ 序列中大于 $L$ 的距离中取出最大值 $r_{max}$，那么显然它一定要与 $r_{max}-L$ 匹配。否则假如与 $r_{max}+L$ 匹配，这与当前最大矛盾。对于剩下的小于 $L$ 的距离两两互补匹配即可。随便用什么数据结构维护都可以。复杂度是 $O(n^2\log n)$。

两种方法都推荐写一写 。

[两个参考Code](https://www.luogu.com.cn/paste/1zl188xk)

---

## 作者：OccDreamer (赞：0)

### 题目大意

一条直线上有 $n$ 个房子和两个人，房子的坐标 $d_1,d_2,d_3\dots d_n$，以及两个人坐标为 $p_1,p_2$。

现在会告诉你两个集合 $S_1=\{|p_1-d_i| ,1 \leq i \leq n\}$ 以及 $S_2=\{|p_2-d_i|,1 \leq i \leq n\}$。~~这个写法可能不是很规范，但为了美观就写成这样了。~~

现在需要你确定构造一组方案确定 $p_1,p_2$ 以及 $d_1,d_2,d_3\dots d_n$  的值或者宣告无解。 

数据范围为 $n \leq 1000$。

------------------------------------------------

### 思路

思路还是比较直接的，考虑找到 $S_1$ 中的一个元素 $x$，在 $S_2$ 中枚举哪一个元素与之匹配，不难发现这样 $p_1,p_2$ 的坐标情况数量只有 $2$ 种。

考虑对于这 $2$ 种情况分开考虑，考虑剩下的元素怎么配对，假定 $(p_1,p_2)=(a,b)$。

如果一个元素 $x \in S_1$ 可以和 $y \in S_2$ 配对，即算出来的 $p_1,p_2$ 符合 $a,b$，那么向他们之间连一条边。

然后跑网络流，看是否存在符合条件的解。

时间复杂度 $O(n^2\sqrt n)$。

~~代码写的很难看。~~

```cpp
#include<bits/stdc++.h>

#define int long long

#define vc vector
#define db double
#define fi first
#define se second
#define ll long long
#define mk make_pair
#define pb push_back
#define RI register int
#define PI pair<int,int>
#define ull unsigned long long
#define err cerr << "   -_-   " << endl
#define debug cerr << " ------------------- " << endl

#define NO puts("NO")
#define YES puts("YES")

using namespace std;

namespace IO{
	inline int read(){
		RI X=0, W=0;register char ch=getchar();
		while(!isdigit(ch)) W|=ch=='-', ch=getchar();
		while(isdigit(ch)) X=(X<<1)+(X<<3)+(ch^48), ch=getchar();
		return W?-X:X;
	}
	inline void write(int x){
		if(x<0) x=-x, putchar('-');
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	inline void sprint(int x){write(x), putchar(32);}
	inline void eprint(int x){write(x), putchar(10);}
}using namespace IO;

const int MAXN = 4e5+5;
const int mod1 = 998244353;
const int mod2 = 1e9+7;
const int inf = 1e12;

int head[5004], ne[MAXN<<1], to[MAXN<<1], weight[MAXN<<1], cnt=1;
int hd, tl, Q[MAXN], cur[MAXN], de[5004], s, t, len, c[MAXN], now, a[MAXN], b[MAXN], n, sol, h[MAXN];

inline void add(int x, int y, int w){
	++cnt;to[cnt]=y;ne[cnt]=head[x];head[x]=cnt;weight[cnt]=w;
	return ;
}

inline bool spfa(){
	memset(de,0,sizeof de);de[s]=1;
	Q[hd=tl=1]=s;int now;
	while(hd<=tl){
		now=Q[hd++];cur[now]=head[now];
		if(now==t) return 1;
		for(int i=head[now];i;i=ne[i]){
			if(!weight[i] || de[to[i]]) continue;
			de[to[i]]=de[now]+1;Q[++tl]=to[i];
		}
	}
	return 0;
}

inline int dinic(int now, int flow){
	if(now==t) return flow;
	int maxnflow=0, res;
	for(int i=cur[now];i && flow;i=ne[i]){
		cur[now]=i;
		if(weight[i] && de[to[i]]==de[now]+1){
			res=dinic(to[i],min(flow,weight[i]));
			weight[i]-=res;
			weight[i^1]+=res;
			flow-=res;
			maxnflow+=res;
		}
	}
	if(maxnflow==0) de[now]=0;
	return maxnflow;
}

int tmp;

inline int Get(int v){
	tmp=lower_bound(b+1,b+1+len,v)-b;
	if(b[tmp]==v) return tmp;
	return 2e9;
}

inline void Add(int node, int v){
	if(v>=1e9 || v<0) return ;
	add(node,v,1);
	add(v,node,0);
}

inline void output(int p1, int p2, int dis){
	h[1]=1e9;int r;
	for(int i=2;i<=n;++i){
		for(int j=head[i];j;j=ne[j]){
			if(to[j]!=s){
				if(weight[j]==0){
					r=to[j]-n;
					if(b[r]==a[i]+dis) h[i]=p1-a[i];
					else if(b[r]==a[i]-dis) h[i]=p1+a[i];
					else if(b[r]+a[i]==dis) h[i]=p1+a[i];
					break;
				}
			}
		}
	}
	int minn=3e9;minn=min(minn,p1), minn=min(minn,p2);
	for(int i=1;i<=n;++i) minn=min(minn,h[i]);
	p1-=minn, p2-=minn;
	for(int i=1;i<=n;++i) sprint(h[i]-minn);
	putchar(10);
	sprint(p1), eprint(p2);
}

inline void Judge(int p1, int p2, int dis, int i){
		if(p1>p2) return ;
		int maxnflow=0;
		memset(head,0,sizeof head);cnt=1;
		for(int j=2;j<=n;++j){
			if(a[j]<=dis) {
				Add(j,Get(dis+a[j])+n);
				Add(j,Get(dis-a[j])+n);
			}
			else{
				Add(j,Get(dis+a[j])+n);
				Add(j,Get(a[j]-dis)+n);
			}
			Add(s,j);
		}
		for(int j=1;j<=n;++j){
			if(j==i) continue;
			add(c[j]+n,j+2*n,1);
			add(j+2*n,c[j]+n,0);
			add(j+2*n,t,1);
			add(t,j+2*n,0);
		}
		maxnflow=0;
		while(spfa()) maxnflow+=dinic(s,inf);
		if(maxnflow==n-1){
			YES;
			sol=1;
			output(p1,p2,dis);
			return ;
		}
}

inline void solve(){
	n=read();s=0, t=3*n+1;
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<=n;++i) b[i]=read(), c[i]=b[i];
	sort(a+1,a+1+n);sort(b+1,b+1+n);
	bool flag=0;
	for(int i=1;i<=n;++i){
		if(a[i]==b[i]) continue;
		flag=1;break;
	}
	len=unique(b+1,b+1+n)-b-1;
	b[0]=b[len+1]=-1;b[len+2]=-1;
	for(int i=1;i<=n;++i)
		c[i]=lower_bound(b+1,b+1+len,c[i])-b;
	if(flag==0){
		YES;
		for(int i=1;i<=n;++i) sprint((long long)1e9-a[i]);
		putchar(10);
		sprint(1e9), eprint(1e9);
		return ;
	}
	int p1, p2, pos, dis;
	int maxnflow=0;sol=0;
	for(int i=1;i<=n;++i){
		pos=1e9;
		Judge(pos-a[1],pos+b[c[i]],a[1]+b[c[i]],i);
		if(sol) return ;
		Judge(pos-a[1],pos-b[c[i]],abs(a[1]-b[c[i]]),i);
		if(sol) return ;
		Judge(pos+a[1],pos+b[c[i]],abs(a[1]-b[c[i]]),i);
		if(sol) return ;
	}
	NO;
	return ;
}

signed main(){
	int t=read();
	while(t--) solve();
	return 0;
}
```

---

## 作者：月球小兔 (赞：0)

考虑任意一个点到两个房子的距离应该是什么样的。我们设两个房子之间的距离为 $dis$，该点到两个房子的距离分别为 $d1$，$d2$。那么要么这个点在两个房子的左/右侧，要么在两个房间中间，即满足 $\lvert d1 - d2 \rvert = dis$ 或 $d1 + d2 = dis$ 。这个关系很有用，因此我们要找到 $dis$ 到底是多少。

先将两个数组排序，并且把离点最大距离更大的那个数组放在第一个方便操作。将这两个数组记为 $A$、$B$，对于 $A$ 中最大的距离，$B$ 中必定有一个与之配对的距离，那么我们可以枚举与之配对的元素。此时 $dis$ 为 $A_n - B_i$。对于第一段中的第二种情况， $dis$ 一定为 $A_n + B_1$。

如何判断合法呢？难点在于我们并不知道一个距离到底表示这个点在左侧、右侧、或是中间。但是如果从大到小考虑所有距离就很清晰了。如果当前考虑的距离 $d$ 大于 $dis $，那么我们一定是从另一个数组中找 $ d - dis$ 这个距离，因为这意味着这个点一定在一侧中，而且比它大的距离已经都被考虑过了，另一个距离只能比它小；如果小于，那么肯定是找 $dis - d$ ，因为不会再有在外侧的距离了。分别给 $A$、$B$ 一个指向末尾的指针，我们判断时总是对当前更大的一方判断。用两个map分别存两个数组的存在的边。对于当前的距离（需要未配对过），从另一个map中查找是否存在对应距离，若存在则从两个map中剔除对应的边并使指针 $-1$，否则无解。最后判断是否所有边都被配对过。

思路比较好想，但是细节很多。说一下我的输出过程。在输出时把这个过程重复一遍，设 $h1 = 0$，$h2 = dis$。如果处理的是 $A$ 数组那么这个点在 $A_i$ ，否则在 $h2 - B_i$，因为这个点若在侧面肯定是离当前数组对应的房子更远的，在中间则显然。最后给答案减去出现的最小的负数，由于我们可能交换过 $A$、$B$，还要换回来。

```
#include<bits/stdc++.h>
using namespace std;
const int N=2000;
int t,n,p1[N],p2[N],fi;
map<int,int> mp1,mp2;
int ans[N],h1,h2;
void solve1(int dis){
	cout<<"YES"<<endl;
    h1=0,h2=dis;
    int minn=0;
    mp1.clear(),mp2.clear();
    for(int i=1;i<=n;i++)
        mp1[p1[i]]++,mp2[p2[i]]++;
    int cnt1=n,cnt2=n,cnt=0;
    for(int i=1;i<=2*n;i++)
    {
        if(p1[cnt1]>p2[cnt2]){
            if(!mp1[p1[cnt1]]) {cnt1--; continue;}
            if(p1[cnt1]>dis){
                mp1[p1[cnt1]]--,mp2[p1[cnt1]-dis]--;
				ans[++cnt]=p1[cnt1],cnt1--;
			}
            else{
                mp1[p1[cnt1]]--,mp2[dis-p1[cnt1]]--;
				ans[++cnt]=p1[cnt1],cnt1--;
			}
        }
        else{
            if(!mp2[p2[cnt2]]) {cnt2--; continue;}
            if(p2[cnt2]>dis){
                mp2[p2[cnt2]]--,mp1[p2[cnt2]-dis]--;
				ans[++cnt]=h2-p2[cnt2],minn=min(minn,ans[cnt]),cnt2--;
			}
            else{
                mp2[p2[cnt2]]--,mp1[dis-p2[cnt2]]--;
				ans[++cnt]=h2-p2[cnt2],minn=min(minn,ans[cnt]),cnt2--;
			}
        }
    }
    sort(ans+1,ans+1+n);
    for(int i=1;i<=n;i++) cout<<ans[i]-minn<<' ';
    cout<<endl;
    if(fi==1) cout<<h1-minn<<' '<<h2-minn<<endl;
    else cout<<h2-minn<<' '<<h1-minn<<endl;
}
void solve2(int dis){
    cout<<"YES"<<endl;
    int h1=0,h2=dis;
    for(int i=1;i<=n;i++)
        ans[i]=p1[i];
    sort(ans+1,ans+1+n);
    for(int i=1;i<=n;i++)
        cout<<ans[i]<<' ';
    cout<<endl;
    if(fi==1) cout<<h1<<' '<<h2<<endl;
    else cout<<h2<<' '<<h1<<endl;
}
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>p1[i];
        for(int i=1;i<=n;i++)
            cin>>p2[i];
        sort(p1+1,p1+1+n),sort(p2+1,p2+1+n);
        fi=1;
        if(p1[n]<p2[n]){
            fi=2;
            for(int i=1;i<=n;i++)
                swap(p1[i],p2[i]);
        }
        int f=0,dis;
        for(int i=1;i<=n;i++)
        {
            dis=p1[n]-p2[i];
            mp1.clear(),mp2.clear();
            for(int j=1;j<=n;j++)
                mp1[p1[j]]++,mp2[p2[j]]++;
            int cnt1=n,cnt2=n;
            f=1;
            for(int j=1;j<=2*n;j++)
            {
                if(p1[cnt1]>p2[cnt2]){
                    if(!mp1[p1[cnt1]]) {cnt1--; continue;}
                    if(p1[cnt1]>dis)
                        if(mp2[p1[cnt1]-dis]) mp1[p1[cnt1]]--,mp2[p1[cnt1]-dis]--,cnt1--;
                        else break;
                    else 
                        if(mp2[dis-p1[cnt1]]) mp1[p1[cnt1]]--,mp2[dis-p1[cnt1]]--,cnt1--;
                        else break;
                }
                else{
                    if(!mp2[p2[cnt2]]) {cnt2--; continue;}
                    if(p2[cnt2]>dis)
                        if(mp1[p2[cnt2]-dis]) mp2[p2[cnt2]]--,mp1[p2[cnt2]-dis]--,cnt2--;
                        else break;
                    else 
                        if(mp1[dis-p2[cnt2]]) mp2[p2[cnt2]]--,mp1[dis-p2[cnt2]]--,cnt2--;
                        else break;
                }
            }
            for(int j=1;j<=n;j++)
                if(mp1[p1[j]] || mp2[p2[j]])
                    f=0;
            if(f) break;
        }
        if(f) {solve1(dis); continue;}
        f=1,dis=p1[n]+p2[1];
        mp2.clear();
        for(int i=1;i<=n;i++)
            mp2[p2[i]]++;
        for(int i=1;i<=n;i++)
            if(mp2[dis-p1[i]]) mp2[dis-p1[i]]--;
            else {f=0; break;}
        if(f) solve2(dis);
        else cout<<"NO"<<endl;
    }
    return 0;
}
```


---

