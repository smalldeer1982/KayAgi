# Minimal Labels

## 题目描述

You are given a directed acyclic graph with $ n $ vertices and $ m $ edges. There are no self-loops or multiple edges between any pair of vertices. Graph can be disconnected.

You should assign labels to all vertices in such a way that:

- Labels form a valid permutation of length $ n $ — an integer sequence such that each integer from $ 1 $ to $ n $ appears exactly once in it.
- If there exists an edge from vertex $ v $ to vertex $ u $ then $ label_{v} $ should be smaller than $ label_{u} $ .
- Permutation should be lexicographically smallest among all suitable.

Find such sequence of labels to satisfy all the conditions.

## 样例 #1

### 输入

```
3 3
1 2
1 3
3 2
```

### 输出

```
1 3 2 
```

## 样例 #2

### 输入

```
4 5
3 1
4 1
2 3
3 4
2 4
```

### 输出

```
4 1 2 3 
```

## 样例 #3

### 输入

```
5 4
3 1
2 1
2 3
4 5
```

### 输出

```
3 1 2 4 5 
```

# 题解

## 作者：rui_er (赞：24)

偶然间翻到三个月前写的这个题，发现现有的题解均未给出解法的正确性证明，只是不明不白地写了一些对理解做法毫无帮助的话。我认为解法的正确性并不显然，因此这篇题解主要给出正确性证明，补上逻辑漏洞。

解法与其他题解一样，即：建反图，然后跑拓扑排序，每次优先取出可以取出的编号最大的点，从 $n$ 到 $1$ 赋权值。

这似乎有点反直觉：为什么倒着做就恰好能满足字典序最小呢？相信大多数人的第一反应都是正着做，这也是我认为正确性并不显然的原因。

证明：

以下“入边”“出边”“入度”“出度”等均为原图上的。

考虑整个算法的第一步，也就是分配权值 $n$。显然，权值 $n$ 的点出度必须为 $0$。

我们记在上述算法中，被分配了权值 $n$ 的点的编号为 $u$。利用反证法，假设在另一种分配方案中，$u$ 被分配了权值 $x$（$x < n$），而 $v$ 被分配了权值 $n$。由于算法中取出的 $u$ 是编号最大的出度为 $0$ 的点，而 $v$ 的出度也必须为 $0$，因此我们有 $u > v$。

对于这种分配方案中被分配权值 $x+1\sim n$ 的点，我们可以将它们重新分配 $x\sim n-1$ 的权值，并将 $u$ 重新分配 $n$ 的权值，仍然得到合法的分配方案。这是因为：点 $u$ 出度为 $0$，将 $u$ 的权值增大并不会影响 $u$ 与其余节点的合法性；并且考虑去掉点 $u$ 的其他节点，重新分配权值相当于对原来的权值进行离散化，不改变偏序关系。

因此，我们可以重新分配权值使得 $u$ 的权值为 $n$。并且，由于 $u > v$，重新分配权值后答案的字典序减小。

由于点 $u$ 的出度为 $0$，给它分配了最大的权值 $n$ 之后，其余节点与 $u$ 之间必然合法，只需要求出其余节点的最小字典序答案即可。因此将点 $u$ 以及它的所有入边都删除，得到规模为 $n-1$ 的子问题。又显然当 $n=1$ 时，算法可以给出最小字典序答案，因此算法正确性得证。$\square$

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define likely(exp) __builtin_expect(!!(exp), 1)
#define unlikely(exp) __builtin_expect(!!(exp), 0)
using namespace std;
typedef long long ll;
const int N = 1e5+5; 

int n, m, deg[N], id[N], tms;
vector<int> e[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
void toposort() {
	priority_queue<int> q;
	rep(i, 1, n) if(!deg[i]) q.push(i);
	while(!q.empty()) {
		int u = q.top(); q.pop();
		id[u] = ++tms;
		for(int v : e[u]) if(!--deg[v]) q.push(v);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, m) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[v].push_back(u);
		++deg[u];
	}
	toposort();
	rep(i, 1, n) printf("%d%c", n+1-id[i], " \n"[i==n]);
	return 0;
}
```

---

## 作者：_liuyi_ (赞：4)

# 思路
拓扑排序好题。

题目保证了有向无环图，我们考虑拓扑排序加贪心，直接开个小根堆然后跑拓扑。不过这题有个有意思的地方，正着跑拓扑其实是假的，为什么呢，正着做其实有后效性，对于一个节点，可能它不是目前编号最小的，但可能存在先填了这个节点，然后去填它的子节点，这种情况字典序最小。

既然正着做有后效性，我们考虑建反图，然后开大根堆，这样就没有后效性。感性证明一下，对于一个编号大的节点先将它填一个大的数一定是优的，因为此时为反图，相当于在原图上先填了子节点，子节点把大的数填完了，那么剩下的就一定是小的了。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define fi first
#define se second
#define pb push_back
#define mem(a,x) memset(a,x,sizeof(a))
#define all(x) x.begin(),x.end()
#define lisan(x) {sort(all(x));x.erase(unique(all(x)),x.end());}
#define SZ(x) ((int)((x).size()))
#define debug(x) cout<<#x<<"="<<x<<"\n";
#define ti (db)((db)clock() / CLOCKS_PER_SEC)
typedef long long ll;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef vector<int> VI;
typedef vector<vector<int>> VII;
typedef vector<ll> VL;
typedef vector<vector<ll>> VLL;
typedef unsigned long long ull;
typedef double db;
template<typename T> inline void cmax(T &a,const T b){if(a<b) a=b;}
template<typename T> inline void cmin(T &a,const T b){if(a>b) a=b;}
template<typename T> inline T gcd(T a,T b){return b?gcd(b,a%b):a;}
template<typename T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}
constexpr int N=1e6+10;
constexpr int mod=1e9+7;
//constexpr int mod=998244353;
int n,m,id[N],in[N],now;
VI e[N];
priority_queue<int> q;
inline void solve(){
    scanf("%d%d",&n,&m);
    rep(i,1,m){
        int x,y;
        scanf("%d%d",&x,&y);
        e[y].pb(x);
        in[x]++;
    }        
    rep(i,1,n) if(!in[i]) q.push(i);
    while(SZ(q)){
        int x=q.top();
        q.pop();
        id[x]=++now;
        for(auto y:e[x])
            if(!(--in[y]))
                q.push(y);
    }
    rep(i,1,n) printf("%d ",n-id[i]+1);
}
int main(){
    int T=1;
    //scanf("%d",&T);
    while(T--) solve();
}
```


---

## 作者：WaterSun (赞：2)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18493149)

LPhang 为什么是神？

# 思路

显然可以想到一个错误的贪心：直接拓扑排序，每一次选择当前可以拓展的点中最小的元素进行编号。

由于可能存在一个值较小的元素被藏在一个较大的元素后面，这种贪心就会出问题。

出问题的本质原因就是我们希望字典序最小，就得使得越小的位置分配到更小的值。不妨建反图，进行拓扑排序，每一次将编号最大的点赋值。这样的操作可以规避上述问题，因为字典序最小不代表越大的位置一定要填越大的值，然而我们保证了越小的位置分配不到较大的值，从而满足字典序最小的限制。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1e5 + 10;
int n,m;
int num,ans[N];
int idx,h[N],ne[N],e[N],deg[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void add(int a,int b){
    ne[idx] = h[a];
    e[idx] = b;
    h[a] = idx++;
}

inline void topsort(){
    priority_queue<int> q;
    for (re int i = 1;i <= n;i++){
        if (!deg[i]) q.push(i);
    }
    while (!q.empty()){
        int u = q.top(); q.pop();
        ans[u] = num--;
        for (re int i = h[u];~i;i = ne[i]){
            int v = e[i];
            if (!(--deg[v])) q.push(v);
        }
    }
}

int main(){
    memset(h,-1,sizeof(h));
    n = num = read(),m = read();
    for (re int i = 1,a,b;i <= m;i++){
        a = read(),b = read();
        add(b,a); deg[a]++;
    }
    topsort();
    for (re int i = 1;i <= n;i++) printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：Jay142753869 (赞：2)

~~感觉没有蓝题难度？~~  
一开始想的是拓扑排序+堆就完了，然而并不是，因为拓扑排序在跑的时候每次只会在“当前”的点中排出一个最小/大的字典序，不符合题意。  
正确的做法是反向建图，之后跑一个字典序最大的拓扑序。因为拓扑排序具有后效性，我们并不能直接贪心来做，需要反过来消除后效性。  
code 
``` cpp
#include<bits/stdc++.h>
#define maxn 100010
#define inf 0x3f3f3f3f
using namespace std;
int head[maxn],cnt,a[maxn],vis[maxn],ans[maxn],n,m,temp;
inline int read()
{
    char c=getchar();
    int x=0;
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9')
    	x=(x<<3)+(x<<1)+c-48,c=getchar();
    return x;
}
struct node{
    int u,v,next;
}edge[maxn];
void add(int a,int b)
{
    edge[cnt].u=a;
    edge[cnt].v=b;
    edge[cnt].next=head[a];
    head[a]=cnt++;
}
priority_queue<int> q;
int main()
{
    memset(head,inf,sizeof(head));
    n=read();
    m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read();
        v=read();
        add(v,u);
        a[u]++;
    }
    for(int i=1;i<=n;i++)
        if(!a[i])
            q.push(i);
    temp=n;
    while(!q.empty()){
        int u=q.top();
        ans[u]=temp;
        temp--;
        vis[u]=true;
        q.pop();
        for(int i=head[u];i!=inf;i=edge[i].next){
            int nt=edge[i].v;
            if(vis[nt]==true)
                continue;
            a[nt]--;
            if(a[nt]==0)
                q.push(nt);
        }
    }
    for(int i=1;i<=n;i++)
        printf("%d ",ans[i]);
    puts("");
    return 0;
}
```  
提交的第一篇题解，求过QAQ。

---

## 作者：Hoks (赞：1)

## 前言
比较简单的题，应该还好很好想到的。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
显然的可以想到拓扑。

因为要满足字典序最小，所以我们直接把目前可以拓展的最小点填上最小值即可。

但是这是对的吗？

假设我们目前可以拓展的点有 $2,999$，那么我们肯定会去考虑拓展 $2$ 然后给 $2$ 标最小。

但是如果 $999$ 后面接着的是一个 $1$ 呢？

那就愉快的寄了。

考虑如何把这个后效性去掉。

既然先把小的填到小的位置上去是错的，那我们反向考虑一下，先把大的填到大的位置上去。

因为字典序的比较是从小到大比较过去的，所以我们只要先把大的都在大的位置上消耗了，小的位置就会留下最优解。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,V=1e7,mod=998244353,INF=0x3f3f3f3f3f3f3f3f;
int n,m,ans,tot,a[N],in[N];priority_queue<int>q;vector<int>e[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
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
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
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
inline void solve()
{
    n=read();m=read();for(int i=1,u,v;i<=m;i++) u=read(),v=read(),e[v].emplace_back(u),in[u]++;
    for(int i=1;i<=n;i++) if(!in[i]) q.push(i);tot=n;
    while(!q.empty())
    {
        int u=q.top();a[u]=tot--;q.pop();
        for(auto v:e[u]) if(!--in[v]) q.push(v);
    }for(int i=1;i<=n;i++) print(a[i]),put(' ');
}
signed main()
{
    int T=1;while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：fanfansann (赞：1)

## 给所有点分配编号使得字典序最小（反图、优先队列）
相当于有多组约束条件，要求输出字典序最小的解

> **题目大意**：给出N个节点和M条边的有向图，要你为这N个节点编号为1~N
> - **所有边的子节点的编号要比其父节点大**
> - 最后的编号要是字典序最小。


**也就是需要在满足约束条件的同时尽可能的使序号小排在前面，注意是满足约束条件条件的情况下。**

> **解题思路**：本题是要求我们亲自给所有的点分配新的编号， 使得最后的拓扑序字典序最小。也就是原来的结点编号最后是没有用的，我们这里是先对点进行拓扑排序，因为要最后分配出来的字典序最小，所以我们可以将所有的边全部反向建图，这样会按照逆拓扑序**先给子结点分配编号**，这里我们贪心地从大到小地给子结点分配编号，即大数能往后就往后，也就是子结点把大的编号都占了，前面的父节点编号就会尽可能的小。

```cpp
const int N = 500007, M = 5000007;
int n, m;
int din[N];
int ver[M], nex[M], head[N], tot;
int ans[N], cnt;

void add(int x,int y){
    ver[tot] = y;
    nex[tot] = head[x];
    head[x] = tot ++ ;
    din[y] ++ ;
}

void toposort(){
    priority_queue<int>q;
    for(int i = 1;i <= n;++i)
        if(!din[i])
            q.push(i);
    while(q.size()){
        int x = q.top();
        q.pop();
        ans[x] = cnt -- ;
        for(int i = head[x];~i;i = nex[i]){
            int y = ver[i];
            if(-- din[y] == 0)
                q.push(y);
        }
    }
}

int main(){
    memset(head,-1,sizeof head);
    scanf("%d%d",&n,&m);
    cnt = n;
    for(int i = 1;i <= m;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        add(y,x);
    }
    toposort();

    for(int i = 1;i <= n;++i)
        printf("%d ",ans[i]);
    puts("");
    return 0;
}
```


---

## 作者：_ZHONGZIJIE0608_ (赞：0)

给定一个有向无环图，顶点为 $n$，边为 $m$。无重边自环，不保证连通。

你应该这样给所有顶点分配标签 $label$：

- 标签形成长度为 $n$ 的排列。
- 如果存在从顶点 $v$ 到顶点 $u$ 的边，那么 $label_v$ 应该小于 $label_u$。
- 排列应该在所有合适的字典顺序中最小。

找到满足所有条件的标签序列。

一开始没什么思路，往 DFS 上想，太弱了太弱了。

发现有一种东西可以维护遍历先后顺序，叫“拓扑排序”。

不难发现，出度为 $0$ 的点一定有一个标签是 $N$。如果大的标签放在前面，显然是比放在后面更劣的。所以我们最后遍历到的点编号尽可能大。

所以我们可以建一张反图跑拓扑排序，这样“出度为 $0$”就转化为了“入度为 $0$”。然后我们从 $N$ 到 $1$ 给每遍历到的点打标签。由于我们希望大的标签给编号大的点，我们把拓扑排序使用的队列改为优先队列维护“编号从大到小”。最后直接输出每个点的标签。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,m,ans[N],in[N],cur;
vector<int>e[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n>>m;cur=n;
	for(int i=1;i<=m;++i){
		int u,v;cin>>u>>v;
		e[v].push_back(u);
		++in[u];
	}
	priority_queue<int>q;
	for(int i=1;i<=n;++i)if(!in[i])q.push(i);
	while(!q.empty()){
		int u=q.top();q.pop();
		ans[u]=cur--;
		for(auto v:e[u]){
			if(!--in[v])q.push(v);
		}
	}
	for(int i=1;i<=n;++i)cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：yx666 (赞：0)

# CF825E Minimal Labels 题解
$$\text{Description}$$

有一个 $n$ 个点，$m$ 条边的有向无环图。你需要输出一个 $1$ 到 $n$ 的全排列 $label$，使得：

- 如果从点 $v$ 到点 $u$ 有一条有向边，那么必须满足 $label_v<label_u$ 。

- 在所有满足要求的全排列中，需要满足答案的字典序最小。

输出这个全排列。

（即求“有向图的最小字典序拓扑排序”）

$$\text{Solution}$$

### Part 1：错误解法

先给出我的错误解法：跑一次 topo 排序，把每个要入队的先存下来，排序后打好标签，再入队。

错误代码如下：

``` cpp
while(q.size()){
	int nw=q.front();q.pop();
	vector<int>v;
	for(int i=head[nw];i;i=edge[i].nxt){
		int to=edge[i].to;
		if(--indu[to]==0) v.push_back(to);
	}
	sort(v.begin(),v.end());
	for(auto to:v){
		dfn[to]=++tot;
		q.push(to);
	}
}
```

错误的原因：没有保证该图连通。

这里也提供一组 hack：

input:

```
5 4
2 1
2 4
4 1
5 3
```

output:

```
3 1 5 2 4
```

### Part 2：反思
![](https://cdn.luogu.com.cn/upload/image_hosting/bmzvj5cd.png)

手模一下刚刚的数据，我们发现：$1$ 要打标签，必须要找到 $4$，$4$ 要打上标签，必须要找到 $2$，这是一个反向操作，有后效性。

那我们建上反边，就可以避免这些问题。

![](https://cdn.luogu.com.cn/upload/image_hosting/nbwupad6.png)

再模一下样例（建反图，红字是 $label$ 标签）。

那我们现在就需要解决：

> 在一个有向无环图中，对于一个有向边 $u\to v$，要求 $label_u>label_v$，问最小字典序的 $label$ 排列。

结合样例，我们贪心地发现：

> 在某一时刻，所有入度为 $0$ 的点中（入队的点中），点越靠后（字典序越大），所分到的 $label$ 越大。
>
> 这样，可以做到：越靠后的 $label$ 越大，即 $label$ 字典序越小。

### Part 3：证明
（@[rui_er](https://www.luogu.com/user/122461) 大佬写的[证明](https://www.luogu.com.cn/article/puyayns3)比我好一万倍）。

大白话证明：

1. 在建了反图后，我们只能给入度为 $0$ 的点打标签，其他的会有后效性。

2. 那我们就只考虑入度为 $0$ 的点，要字典序最小，就是要靠后的点 $label$ 越大。

$$\text{Code}$$

``` cpp
#include<bits/stdc++.h>
using namespace std;
/*
快读已省
*/
#define N 100005
#define M 100005

int cnt,head[N],indu[N];
struct{
	int to,nxt;
}edge[M];

static inline void addEdge(int from,int to){
	edge[++cnt]={to,head[from]};
	head[from]=cnt;
	++indu[to];
	return;
}

int n,m,tot,dfn[N];
static inline void toposort(){
	priority_queue<int>q;		// 大根堆
	for(int i=1;i<=n;++i)
		if(!indu[i])
			q.push(i);
	
	while(q.size()){
		int nw=q.top();q.pop();
		dfn[nw]=--tot;           // 打标记
		for(int i=head[nw];i;i=edge[i].nxt){
			int to=edge[i].to;
			if(--indu[to]==0)
				q.push(to);
		}
	}
	return ;
}

signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		int u=read(),v=read();
		addEdge(v,u);				// 建反图
	}
	tot=n+1;   // 时间戳
	toposort();
	for(int i=1;i<=n;++i)
		cout<<dfn[i]<<' ';
	
	return 0;
}
```

---

## 作者：Mortidesperatslav (赞：0)

观察题面，发现其实是对拓扑序的限制。

然后考虑怎么让输出的字典序小。

但是我们不能直接每次选取序号最小的点做。而是建反图跑最大拓扑序。样例很机智，没有给这种数据，这就让我们很容易掉进坑里。

Hack 数据：

```plain
4 3
1 4 
1 3
4 2
```

正确输出应该是 `1 3 4 2`。

这是因为优先选了可以选到的点中最小的，但是可以先选稍大的，而把更小的放在更前面，而建反图选最大的可以使放一个数的时候，该数是能放的数中最大的，只能先放，否则无论如何取都不是最优。

这是为什么呢？

考虑设当前最大的值为 $x$，已经取了 $k$ 个点。那么如果反图中 $y$ 到 $z$ 有一条边（否则先取 $x$ 必然最优），且 $y$ 当前可以取到。那么分为两种情况：

1. $y<x,z<x$，那么必定先取 $x$。

2. $y<x,z>x$，如果先取 $x$，那么答案序列的第 $x$ 项就为 $n-k-1$，第 $y$ 项为 $n-k-2$（$n$ 为节点数）。否则第 $x$ 项为 $n-k-2$，第 $y$ 项为 $n-k-1$。那么显然是先取 $x$ 更优。

简单说就是说因为 $y$ 在比字典序的时候更靠前，所以让 $y$ 比 $x$ 后取，字典序就更小（和我一样不喜欢一大堆公式的理解下这个吧）。

然后就解决了。

代码如下，时间复杂度 $O(n \log n)$：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,in[100005];
vector<int>G[100005];
priority_queue<int>q;
int ans[100005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		G[v].push_back(u);//反图
		in[u]++;
	}
	for(int i=1;i<=n;i++)if(!in[i])q.push(i);//拓扑排序
	int tp=n;
	while(!q.empty()){
		int u=q.top();
		ans[u]=tp--;
		q.pop();
		for(auto &v:G[u]){
			in[v]--;
			if(!in[v])q.push(v);
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
}
```

---

## 作者：Schi2oid (赞：0)

# CF825E Minimal Labels 题解

## 题意简述

求有向图最小字典序拓扑排序。

## 做法

建反图，从小到大赋值，每次取出当前入度为 $0$ 结点中编号最大的点进行赋值，最后反转拓扑序，即 $topo_i\leftarrow n+1-topo_i$。

## 正确性证明

归纳。我们希望原图拓扑排序字典序最小，则其等价于反图字典序最大，这是因为任意一个原图拓扑排序 $topo_i$ 都可以唯一对应一个反图上的拓扑排序 $topo'_i=n+1-topo_i$。首先考虑初始情况，原图上可赋值为 $n$ 的点为所有的出度为零的点，即反图上可赋值为 $1$ 的点为所有的入度为零的点。从感性理解的角度而言，编号较小的结点一定希望编号较大的结点先填好，这样子它能够填上的标记就会更大，从而拓扑序更大。而所有结点都希望编号最大的结点先填好，这不会违背任何结点的“利益”，换句话来说无后效性，即局部最优解不妨碍达成全局最优解，因此，编号最大的结点一定会被优先填入。

理性证明的话，我们考虑设当前出度为 $0$ 的所有点的编号为 $x_1,x_2,x_3,…,x_m$，按照单调递增顺序列出。不妨设我们将 $x_k,k<m$ 位置填成了 $1$，而 $x_m$ 位置填成了 $w$，然后对于剩下的残图按照最优的方式（即字典序尽可能大）完成了整个拓扑排序过程，我们称一个点 $u$ **支配**另一个点 $v$，当且仅当存在一条反图上的路径 $u\rightarrow v$。一个点 $x$ **支配**的所有点构成它的**支配集合** $S_x$。容易发现，$u$ **支配** $v \Leftrightarrow S_v\subset S_u$。现在考虑 $S_{x_k}\cup S_{x_m}$，这一集合中的每一个元素代表一个位置，它们都唯一对应一个填入的值。设位置序列为 $pos_1,pos_2,…,pos_{|S_{x_k}\cup S_{x_m}|}$，值序列为 $val_1,val_2,…,val_{|S_{x_k}\cup S_{x_m}|}$，其中 $pos_i$ 对应 $val_i$，按照值升序进行排序，即 $val_i>val_j\Leftrightarrow i>j$。那么我们从位置序列中去除掉 $x_m$，再从值序列中去除掉 $1$，将去除掉的位置之后的后缀整体在数组中向前挪动一位，得到新的位置序列和值序列  $pos'_1,pos'_2,…,pos'_{|S_{x_k}\cup S_{x_m}|-1}$，$val'_1,val'_2,…,val'_{|S_{x_k}\cup S_{x_m}|-1}$。容易发现，除了位置 $x_w$ 以外，对于一个原本的位置 $p$，其所对应的新的值 $v'$ 一定大于等于其原先所对应的 $v$，又因为存在 $x_k<x_w$ 而 $x_k$ 所填入的值增大，故拓扑序的字典序增大。那么此时考虑这样进行调整后是否仍然满足拓扑关系约束，即若 $u$ 支配 $v$，则 $u$ 填入的值小于 $v$ 填入的值。

- 对于 $x_w$ 之外的位置 $p$：因为 $S_{x_k}\cup S_{x_m}$ 内的所有元素进行的是值域平移，所以对于集合内部的约束关系，其值仍然符合条件；而由于 $u$ **支配** $v \Leftrightarrow S_v\subset S_u$，故在 $S_{x_k}\cup S_{x_m}$ 之外的位置与 $p$ 之间的关系一定是 $p$ 被**支配**，又因为其填入的值没有变小，故仍然符合条件。

- 对于 $x_w$：显然不会变为不合法，因为其入度为 $0$。

特别注意，调整后字典序严格变大。因此，我们说明对于 $n$ 个点的情况，我们必须将 $1$ 填入零度的编号最大的点，显然只有 $1$ 个点的图也应这样做，故不断地将当前的可以赋值的编号最大的点进行赋值即可完成整个过程，证毕。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>edge[100005];
vector<int>fedge[100005];
priority_queue<int>q;
int deg[100005];
int lab[100005];
int main(){
	int n,m,u,v;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		deg[u]++;
		fedge[v].push_back(u);
	}
	int done=0;
	for(int i=1;i<=n;i++) if(!deg[i]) q.push(i);
	while(done<n){
		int qt=q.top();
		q.pop();
		lab[qt]=n-(done++);
		for(int j=0;j<fedge[qt].size();j++){
			int v=fedge[qt][j];
			deg[v]--;
			if(!deg[v]) q.push(v);
		}
	}
	for(int i=1;i<=n;i++) printf("%d ",lab[i]);
	return 0;
}
```

---

