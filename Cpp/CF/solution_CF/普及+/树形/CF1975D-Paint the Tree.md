# Paint the Tree

## 题目描述

378QAQ has a tree with $ n $ vertices. Initially, all vertices are white.

There are two chess pieces called $ P_A $ and $ P_B $ on the tree. $ P_A $ and $ P_B $ are initially located on vertices $ a $ and $ b $ respectively. In one step, 378QAQ will do the following in order:

1. Move $ P_A $ to a neighboring vertex. If the target vertex is white, this vertex will be painted red.
2. Move $ P_B $ to a neighboring vertex. If the target vertex is colored in red, this vertex will be painted blue.

Initially, the vertex $ a $ is painted red. If $ a=b $ , the vertex $ a $ is painted blue instead. Note that both the chess pieces must be moved in each step. Two pieces can be on the same vertex at any given time.

378QAQ wants to know the minimum number of steps to paint all vertices blue.

## 说明/提示

In the first test case, 378QAQ can paint all vertices blue in the following order:

- Initially, $ P_A $ is located on the vertex $ 1 $ , and $ P_B $ is located on the vertex $ 2 $ . The vertex $ 1 $ is painted red and the vertex $ 2 $ is white.
- 378QAQ moves $ P_A $ to the vertex $ 2 $ and paints it red. Then 378QAQ moves $ P_B $ to the vertex $ 1 $ and paints it blue.
- 378QAQ moves $ P_A $ to the vertex $ 1 $ . Then 378QAQ moves $ P_B $ to the vertex $ 2 $ and paints it blue.

## 样例 #1

### 输入

```
3
2
1 2
1 2
5
1 2
1 2
1 3
1 4
1 5
8
5 4
7 1
1 5
1 8
8 3
7 2
8 6
3 4```

### 输出

```
2
8
13```

# 题解

## 作者：Sine_Func (赞：6)

# [CF1975D](https://www.luogu.com.cn/problem/CF1975D)

## 题意

给出一棵树，初始时每个点都是白色，$A$ 和 $B$ 分别在 $a$ 点和 $b$ 点上。\
如果 $a \ne b$，那么将 $a$ 点染色为红色，如果 $a=b$，那么将 $a$ 点染色为蓝色。

在每秒钟内：\
$A$ 走到与之相邻的点，如果这个点是白色，那么将这个点染色为红色。\
$B$ 走到与之相邻的点，如果这个点是红色，那么将这个点染色为蓝色。

求将整棵树全部染色为蓝色的最短时间。

## 思路

因为要将节点染色为蓝色必须先把此节点染色为红色，所以考虑先让 $A$ 与 $B$ 会合。首先以 $a$ 为根，建立出树。记录 $b$ 的深度为 $dep_b$，找到 $b$ 的祖先中深度为 $\frac{dep_b}{2}$ 的节点，我们将其命名为 $c$。\
$c$ 就是 $A$ 与 $B$ 的会和点。在以 $c$ 点为根建树，记录每个点的深度，由于只需要将树染色为蓝色，因此在染色完成后就不需要返回 $c$ 点，我们找到距离 $c$ 最远的点，在最终答案中减去即可。\
注意处理以 $a$ 为根时，若 $dep_b$ 为奇数则无法重合的情况。

## code

```cpp
#include <bits/stdc++.h>
#define AC return 0
using namespace std;
int t, n, a, b, fa[200010], dep[200010], ans;
vector<int>g[200010];
void dfs(int x) {//以x为根建树
	for (int i = 0; i < g[x].size(); i++) {
		if (g[x][i] == fa[x])continue;
		dep[g[x][i]] = dep[x] + 1;
		fa[g[x][i]] = x;
		dfs(g[x][i]);
	}
}
int main() {
	cin >> t;
	while (t--) {
		ans = 0;
		cin >> n >> a >> b;
		memset(fa, 0, sizeof(fa));
		for (int i = 1; i <= n; i++)
			g[i].clear();
		for (int i = 1; i < n; i++) {
			int u, v;
			cin >> u >> v;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		dep[a] = 0;
		dfs(a);
		int now = b;
		while (dep[now] != ((dep[b] + 1) / 2)) {
			now = fa[now];
			ans++;
		}
		if (dep[b] & 1) {
			ans++;
			now = fa[now];
		}
		memset(fa, 0, sizeof(fa));
		dep[now] = 0;
		dfs(now);
		int mx = 0;
		for (int i = 1; i <= n; i++)
			mx = max(mx, dep[i]);
		cout << ans + 2 * n - 2 - mx << "\n";
	}
	AC;
}
```

[AC](https://www.luogu.com.cn/record/169992739)

---

## 作者：SamHJD (赞：4)

# CF1975D Paint the Tree

> 给出一棵树，每个点初始为白色。Alice 在 $P_A$，Bob 在 $P_B$。每次操作两人需要移动到相邻的结点，Alice 会将脚下的白点染成红色，Bob 会将脚下的红点染成蓝色。
>
> 求将整棵树染成蓝色的最小操作次数。

先考虑一个子问题，以某个点作为起点，求出遍历整棵树的最小移动次数。

若规定必须回到起点，那么最优方案下每条边一定被经过两次，答案为 $2\times (n-1)$。若不规定回到起点，我们可以选择一段路径最后走，使得这条路径上的边只经过一次，那么最优方案为选择以起点开始的最长的一条链最后走。因此答案为 $2\times (n-1)-maxl$，其中 $maxl$ 为以起点开始的最长链。

设 Bob 第一个碰到的红点为 $x$，Alice 必然先走到 $x$，那么他可以按照最优方案遍历整棵树，Bob 只需按照 Alice 的路径走。这显然是操作次数最小的方案。

一个自然的想法是 Bob 与 Alice 均向对方移动，尝试证明。Bob 每移动一步至 $p$，以 $p$ 为端点的最长链至多增加 $1$，因此 Bob 每移动一步答案严格不降，因此 Bob 越早到一个红点越好，故两人向对方移动。

找到 $x$ 后，我们只需以 $x$ 为根做一次搜索找出到叶子的最长链，计算遍历整棵树的移动次数，并加上 $P_B$ 和 $x$ 的距离作为答案。

[Code](https://codeforces.com/contest/1975/submission/262816400)

---

## 作者：DeepSeekR1 (赞：1)

发现 $P_B$ 如果走到一个白色的点，那么这次操作是没有贡献的。

如果 $P_B$ 走到了一个红色的点，那么以后它通过跟随 $P_A$ 的走法，可以做到以后的每一步都是有效的。

那么就让 $P_A$ 和 $P_B$ 在 $a$ 和 $b$ 的中点相遇，设相遇点为 $r$。以 $r$ 为根，走完所有点的步数就是两倍的边数减去最远点的深度（因为不需要回到起点）。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a,b;
vector <int> e[200005];
int ans,d[200005],fa[200005];
bool vis[200005];
void f (int x) {
    vis[x] = 1;
    for (auto at : e[x]) {
        if (vis[at]) {
            continue;
        }
        d[at] = d[x] + 1;
        fa[at] = x;
        f(at);
    }
    return;
}
void v (int x) {
    vis[x] = 1;
    for (auto at : e[x]) {
        if (vis[at]) {
            continue;
        }
        d[at] = d[x] + 1;
        v(at);
    }
    return;
}
signed mian () {
    cin >> n;
    cin >> a >> b;
    for (int i = 1;i < n;i++) {
        int u,v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    fa[a] = a;
    f(a);
    int r = b;
    for (int i = 1;i <= (d[b] + 1) / 2;i++) {
        r = fa[r];
    }
    for (int i = 1;i <= n;i++) {
        vis[i] = 0;
        d[i] = 0;
    }
    v(r);
    ans = (n - 1) * 2 + d[b];
    int mx = -1;
    for (int i = 1;i <= n;i++) {
        mx = max(mx,d[i]);
    }
    ans -= mx;
    cout << ans << endl;
    return 0;
}
signed main () {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        mian();
        for (int i = 1;i <= n;i++) {
            e[i].clear();
            vis[i] = 0;
            d[i] = 0;
            fa[i] = 0;
        }
        ans = 0;
    }
	return 0;
}
```

---

## 作者：ben090302 (赞：1)

考虑贪心，因为 $P_b$ 必须走 $P_a$ 走过的点才有效，所以优先让 $P_a$ 和 $P_b$ 汇合。

实现上可以两次 dfs 记录以 $a$ 和 $b$ 为根时的父亲数组，然后两个点分别跳，直到 $a$ 和 $b$ 重合或**彼此越过**，详情参考代码。

我们是希望 $b$ 尽快到达一个红点然后尾随 $a$ 行动，所以要让 $b$ 越过 $a$。

考虑最后 $a$ 的运动轨迹对答案影响，发现每条边都必须被经过两次除了**从起点到刚好完成遍历的那条链**。于是我们以 $b$ 为根，进行深搜，找出最长链(长度为 $L$)，答案就是 $2(n-1)-L$。

code:

```
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
struct edge{
    int v,nxt;
}e[N];
int hd[N];
int T;
int n,a,b;
int F[N],D[N];
int tot;
void add(int u,int v){
    e[++tot]={v,hd[u]},hd[u]=tot;
    e[++tot]={u,hd[v]},hd[v]=tot;
}
void Clear(){
    tot=1;
    for(int i=1;i<=n;i++) hd[i]=F[i]=D[i]=0;
    return ;
}
int ans;
int d[N];
int tim;
void dx(int u,int fa){
    F[u]=fa;
    for(int i=hd[u];i;i=e[i].nxt){
        int v=e[i].v;
        if(v==fa) continue;
        dx(v,u);
    }
}
void dy(int u,int fa){
    D[u]=fa;
    for(int i=hd[u];i;i=e[i].nxt){
        int v=e[i].v;        
        if(v==fa) continue;
        dy(v,u);
    }
}
int TNT=0;
void dfs(int u,int fa){ 
    d[u]=d[fa]+1;TNT=max(TNT,d[u]);
    for(int i=hd[u];i;i=e[i].nxt){
        int v=e[i].v;        
        if(v==fa) continue;
        dfs(v,u);
    }
}

int main(){
    cin>>T;
    while(T--){
        Clear();
        TNT=0;
        cin>>n>>a>>b;
        for(int i=1,u,v;i<n;i++){
            cin>>u>>v;
            add(u,v);
        }   
        dx(a,a);
        dy(b,b);
        ans=(n-1)*2;
        while(a!=b and F[a]!=b){
            a=D[a],b=F[b];ans++;
        }
        // if(F[b]==a) ans++;
        d[b]=-1;
        dfs(b,b);
        
        cout<<ans-TNT<<"\n";   
    }
}
```cpp

---

## 作者：sbno333 (赞：1)

从特殊到一般是很好的解题方法，我们不妨从最简单的情况入手。

注意看，~~这个男人叫小帅~~ $P_A$ 与 $P_B$ 在一起，我们每次可以移动一下 $P_A$，然后 $P_B$ 移到同样的位置，这样就要移动 $2n-2-R$，其中 $R$ 为离原来的点最远的节点的距离（存在性：考虑遍历每个节点都要经过两次它到它父亲的边，即进入子树和离开子树，如果最后回到原点，答案显然为边数，但不需要，所以我们考虑减去回去的步数，显然为某一点到原点的路程，然后取最大即可）。

正确性也是显然意见的，假设只需要 $P_B$，这个答案是显然的，有了 $P_A$，限制条件增加，答案不降，因此正确。

我们考虑稍特殊的情况，两棋子距离为偶数，为了第二个棋子尽快开始遍历染色，显然需要两个棋子快速和到一起，这是容易处理的，接下来你就会了。

考虑距离为奇数，显然首先仍然为快速接近。

接着就考虑怎么跑才最贪心，可以红跑一次，蓝跟到上一个红的地方，这样二者让能相邻，且染色有效，显然要染色都要染成红色，但是最后一次蓝色少走一步，所以要再加上一。

答案为 $2n-1-R(P_A)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int a,b;
int ans;
struct st{
	int v,ne;
}sd[1000009];
int h[1000009];
int inn;
void add(int u,int v){
	sd[++inn].v=v;
	sd[inn].ne=h[u];
	h[u]=inn;
}
int fa[1000009];
int d[1000009];
void dfs(int t){
	d[t]=d[fa[t]]+1;
	for(int i=h[t];i;i=sd[i].ne){
		if(sd[i].v!=fa[t]){
			fa[sd[i].v]=t;
			dfs(sd[i].v);
		}
	}
}
int zj(int t,int fa){
	int ans;
	ans=-1;
	for(int i=h[t];i;i=sd[i].ne){
		if(sd[i].v!=fa){
			ans=max(ans,zj(sd[i].v,t));
		}
	}
	return ans+1;
}
void cl(){
	inn+=10;
	while(inn){
		sd[inn--]={0,0};
	}
	for(int i=0;i<=n+10;i++){
		h[i]=fa[i]=d[i]=0;
	}
	ans=0;
}
void _main(){
	cin>>n;
	cin>>a>>b;
	fa[a]=a;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	fa[a]=0;
	d[0]=-1;
	dfs(a);
	ans+=d[b]/2;
	ans+=2*n-2;
	int z;
	z=d[b];
	//cout<<d[b]<<endl;
	for(int i=1;i<=z/2;i++){
		b=fa[b];
	}

	if(z&1){
		ans-=zj(fa[b],0)-1;
	}else{
		ans-=zj(b,0);
	}
	cout<<ans<<endl;
	cl();
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：liugh_ (赞：0)

## [Paint the Tree](https://codeforces.com/contest/1975/problem/D)

B 对 A 没访问过的点没有影响，贪心地我们想**让 B 尽快走到 A 访问过的点**，考虑提取出初始时从 A 到 B 的路径，对路径长度 $len$ 的奇偶性分讨，若 $len$ 为奇数，代价为 $(len-1)/2$；若 $len$ 为偶数，代价为 $len/2$。当 AB 汇合后，发现 A 始终比 B 快，于是问题转化为从指定点出发走完整棵树（不要求回到起点）的最小代价，dp 是容易的。时间复杂度 $O(n)$。

```cpp
vector<int> li,cur;
function<void(int,int)> find=[&](int u,int lst){
    cur.pb(u);
    if(u==b)return li=cur,void();
    for(auto v:G[u])if(v!=lst){
        find(v,u);
        if(li.size())return;
    }
    cur.pop_back();
};
find(a,0);
vector<vector<int>> f(n+5,vector<int>(2));
function<void(int,int)> dfs=[&](int u,int lst){
    f[u]={};
    for(auto v:G[u])if(v!=lst){
        dfs(v,u);
        f[u][1]=min(f[u][0]+f[v][1]+1,f[u][1]+f[v][0]+2);
        f[u][0]=f[u][0]+f[v][0]+2;
    }
};
int cnt=li.size();
dfs(li[(cnt-1)/2],0);
cout<<f[li[(cnt-1)/2]][1]+cnt/2<<'\n';
```

---

## 作者：CJ_Fu (赞：0)

## [Paint the Tree](https://www.luogu.com.cn/problem/CF1975D)

题意：

给你一棵白色的树，只有 $a$ 为红色，$b$ 为蓝色，树上有两个棋子 $P_A,P_B$ 分别在节点 $a,b$ 上，在每一单位时间内，进行以下操作：
- 将 $P_A$ 移动到相邻节点 $a'$，若 $a'$ 为白色，则将 $a'$ 变为红色；
- 将 $P_B$ 移动到相邻节点 $b'$，若 $b'$ 为红色，则将 $b'$ 变为蓝色。

求将整棵树染成蓝色的最短时间。$n\le 2\times 10^5$。

题解：

首先我们需要知道一点：如果 $P_B$ 走的点是白色的，那么它走的就没意义。

所以我们首先要最小化 $P_B$ 没意义的时间。很简单，就是尽快让 $P_A,P_B$ 相遇，让它们一直走 $(a,b)$ 的最短路径直到互相经过就停下。

从这一刻开始，$P_B$ 走的就有意义了。而且，$P_B$ 只要跟着 $P_A$ 走，就一定是不劣的，因为 $P_B$ 每一步走的都是红点。

接下来就是用最短时间遍历整棵树，除了从出发点到终点的路径，每条边都必须被经过两次。这其实和 [ABC361E](https://www.luogu.com.cn/problem/AT_abc361_e) 的思想很像了，当然本题规定了出发点，就直接以出发点为根 DFS 出最深度最大的点 $x$，让 $P_B$ 的终点为 $x$，即可保证用时最小。

设 $P_A,P_B$ 相遇的时间为 $t$，$x$ 的深度为 $d$，则答案为 $t+2(n-1)-d$，时间复杂度 $O(n)$。

小技巧：设 $a\to b$ 的最短路径长度为 $l$，记录其路径为 $f(f_0=a,f_l=b)$，则相遇后，$P_A=f_{\left\lfloor\frac{l+1}{2}\right\rfloor},P_B=f_{\left\lfloor\frac{l}{2}\right\rfloor},t=\left\lfloor\frac{l+1}{2}\right\rfloor$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+3;
int n,pa,pb,ans,T;
vector<int>e[maxn];
int dep[maxn],stk[maxn],top,f[maxn],len;
void dfs(int u,int fa){
    if(u==pb){
        for(int i=1;i<=top;i++) f[i]=stk[i];
        len=top;
        return;
    }
    for(int v:e[u]){
        if(v!=fa){
            stk[++top]=v;
            dfs(v,u);
            top--;
        }
    }
}
void dfs1(int u,int fa,int depth){
    dep[u]=depth;
    for(int v:e[u]){
        if(v!=fa){
            dfs1(v,u,depth+1);
        }
    }
}
void solve(){
    ans=0;
    cin>>n;
    cin>>pa>>pb;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    dfs(f[0]=pa,0);
    if(len&1){
        ans+=len/2+1;
        pb=f[len/2];
        pa=f[len/2]+1;
    }else{
        ans+=len/2;
        pa=pb=f[len/2];
    }
    dfs1(pb,0,0);
    int mxdep=0;
    for(int i=1;i<=n;i++){
        mxdep=max(mxdep,dep[i]);
        e[i].clear();
    }
    top=0;
    cout<<ans+2*(n-1)-mxdep<<'\n';
}
signed main(){
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
```

---

## 作者：SFlyer (赞：0)

我们先考虑一下 A 和 B 可以集合到一个点的情况。这种情况我们设集合在 $x$，我们造作次数就是 $\max(dis(a,x),dis(b,x))+cal(x)$，$cal(x)$ 的值是以 $x$ 为根的树要遍历到每一个节点的最小造作步数，贪心容易发现是 $2(n-1)-maxdep$，$maxdep$ 是以 $x$ 为根的最大深度。怎么选集合点呢？我们发现，我们集合点 $x$ 移动一步，$maxdep$ 最多 $+1$，所以我们让 $\max(dis(a,x),dis(b,x))$ 最小最好，因为移动不会更优。这个就是 $a,b$ 路径的中点。

如果不能集合到一个点，即 $a,b$ 路径长度为偶数个点。这个我们就移到它们刚刚距离为 $1$ 即可，以 $a$ 作为集合点，最后答案 $+1$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e5+5;

int n,dep[N],fa[N][22],a,b;
vector<int> g[N];

void dfs(int u,int f){
	dep[u]=dep[f]+1;
	fa[u][0]=f;
	for (int i=1; i<22; i++){
		fa[u][i]=fa[fa[u][i-1]][i-1];
	}
	for (auto v : g[u]){
		if (v^f){
			dfs(v,u);
		}
	}
}

void dfs1(int u,int f){
	dep[u]=dep[f]+1;
	for (auto v : g[u]){
		if (v^f){
			dfs1(v,u);
		}
	}
}

int lca(int u,int v){
	if (dep[u]<dep[v]){
		swap(u,v);
	}
	int dif=dep[u]-dep[v];
	for (int i=0; i<20; i++){
		if (dif>>i&1){
			u=fa[u][i];
		}
	}
	if (u==v){
		return u;
	}
	for (int i=19; i>=0; i--){
		if (fa[u][i]!=fa[v][i]){
			u=fa[u][i],v=fa[v][i];
		}
	}
	return fa[u][0];
}

void solve(){
	cin>>n>>a>>b;
	for (int i=1; i<=n; i++){
		g[i].clear();
		dep[i]=0;
		for (int j=0; j<22; j++){
			fa[i][j]=0;
		}
	}
	for (int i=1; i<n; i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	vector<int> p,p1;
	int cur=a,lc=lca(a,b);
	while (cur!=lc){
		p.push_back(cur),cur=fa[cur][0];
	}
	p.push_back(lc);
	cur=b;
	while (cur!=lc){
		p1.push_back(cur),cur=fa[cur][0];
	}
	for (int i=p1.size()-1; i>=0; i--){
		p.push_back(p1[i]);
	}
	if (a==b){
		p={a};
	}
	int ad=(p.size()%2==0)+(p.size()-1)/2;
	int nd=p[(p.size()-1)/2];
	dep[nd]=0;
	dfs1(nd,0);
	int mx=0;
	for (int i=1; i<=n; i++){
		mx=max(mx,dep[i]);
	}
	cout<<2*(n-1)+ad-mx+1<<"\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin>>t;
	while (t--){
		solve();
	}
	return 0;
}
```

---

## 作者：2huk (赞：0)

棋子 $P_A$ 会将 **白** 染成 **红**，棋子 $P_B$ 会将 **红** 染成 **蓝**，显然一个点需要先被 $P_A$ 经过再被 $P_B$ 经过后才能从 **白** 变成 **蓝**。

一个极其自然的想法就是先让 $P_A$ 和 $P_B$ 集合到一个点，然后一起移动。设这个集合的点为 $r$。接下来的问题就是：

- 一个棋子从 $r$ 出发，最少走几步能遍历完所有点。

钦定 $r$ 为根。显然每条边需要被经过 $2$ 次，即 $2(n-1)$。但是我们可以让棋子走到深度最深的叶子节点后停止，即答案为 $2(n - 1) - \max dep_i$。

但是有可能 $P_A$ 和 $P_B$ 不能移动到一个点，该情况发生当且仅当 $a, b$ 路径上边的数量为奇数。不难发现我们可以让这个集合点在靠近 $a$ 的中点处。

所以问题是找到这个 $r$。我们钦定 $a$ 为根，那么 $r$ 需要满足：

- $r$ 在 $a, b$ 路径上。因为 $a$ 是根，所以该条件即 $r$ 是 $b$ 的父亲。
- $dep_r = \lceil dep_b / 2\rceil$。

暴力从 $b$ 往上跳即可。

```cpp
struct Tree {
	vector<int> g[N];
	void add(int a, int b) { g[a].push_back(b); }
	void clear() {
		for (int i = 1; i <= n; ++ i ) g[i].clear();
	}
	
	int dep[N], fa[N];
	void dfs(int u, int f) {
		dep[u] = dep[f] + 1;
		fa[u] = f;
		for (int v : g[u])
			if (v != f) dfs(v, u);
	}
}T;
 
void Luogu_UID_748509() {
	fin >> n >> a >> b;
	
	T.clear();
	for (int i = 1; i < n; ++ i ) {
		int x, y;
		fin >> x >> y;
		T.add(x, y), T.add(y, x);
	}
	
	T.dfs(a, 0);
	
	int res = 0;
	if (a == b) res = 2 * (n - 1) - *max_element(T.dep + 1, T.dep + n + 1);
	else {
		int mid = b;
		while (T.dep[mid] != (T.dep[b] + 1) / 2) mid = T.fa[mid], ++ res;
		T.dfs(mid, 0);
		res += 2 * (n - 1) - *max_element(T.dep + 1, T.dep + n + 1);
	}
	
	fout << res + 1 << '\n';
}
```

---

## 作者：yshpdyt (赞：0)

## 题意
 一棵所有节点都是白色的树。
 
树上有两颗棋子，分别叫做 $P_A$ 和 $P_B$ ，最初分别位于顶点 $a$ 和 $b$ 。

每次操作都要先后移动两颗棋子各一次，即先移动 $P_A$，后移动 $P_B$，视为同一次操作。$P_A$ 可以将移动到的白色节点染红，$P_B$ 可以将移动到的红色节点染蓝。

求最小移动次数，将整棵树染蓝。
## Sol
~~非常好乱猜结论题，使我的 rating 减少。~~

注意到在 $P_B$ 走到红色节点之前都不会对其他节点染色。

不考虑时间复杂度，枚举第一个走到的红色节点，如果为 $x$ ，只需要让 $P_A$ 和 $P_B$ 在接下来的行动中模仿 $P_A$ 之前走过的路径，每次移动一定可以染蓝一个节点，所以在此之后不需要考虑 $P_A$ 。

从任意节点出发再回到该节点的移动次数是 $2(n-1)$，即每条边经过一次，但是没必要回到该节点，染完最后一个点让其待在哪里即可，可以省去 $d$ 步，显然待在最远点最优，$d=\max\limits_{i=1}^n dis(x,i)$。

所以考虑第一个走到的红色节点为 $x$，需要满足 $dis(a,x)\le dis(b,x)$，该点答案为：

$$f_x=dis(b,x)+2(n-1)-\max\limits_{i=1}^n dis(x,i)$$

但是求最远点是 $O(n)$，枚举所有点也是 $O(n)$ 的，算法总的复杂度 $O(n^2)$，无法通过，考虑减少枚举所有点的复杂度。

不妨大胆猜结论：使 $|dis(a,x)- dis(b,x)|$ 最小的点，即 $a,b$ 之间的中间点，设为 $c$ 。

为什么这么想？首先 $x$ 肯定在 $a\rightarrow b$ 的路径上，否则不满足第一个经过的红色节点，又由于 $dis(a,x)\le dis(b,x)$，所以 $x$ 在 $a\rightarrow c$ 的路径上。我们希望尽早走到红色结点，尽早开始染色，$c$ 一定是其中最早可以走到的。

考虑严谨的证明，我们让整棵树以 $a$ 为根节点，
从 $c$ 开始向上考虑，每靠近一次 $a$，$dis(b,x)$ 肯定加一，但是 $\max\limits_{i=1}^n dis(x,i)$ 不一定减少，如果最远点在 $b$ 的子树里面会增加 $1$，整体答案不变，如果在 $a$ 的其它子树上，会减少 $1$，整体答案增加二，变得更劣。

所以最终的答案即为：

$$res=dis(b,c)+2(n-1)-\max\limits_{i=1}^n dis(c,i)$$

至于怎么求，先以 $a$ 为根结点，在遍历完某点子树后，若第一次满足  $dep_x=\left\lfloor \frac{dep_b}{2}\right\rfloor$，退出搜索即可，深度从 $0$ 开始。（在搜索到 $b$ 之前， $dep_b$ 一直为 $0$，第一次满足条件时一定有 $x$ 在 $a\rightarrow b$ 链上）。

求最远点就很容易了。

~~本题结论不算难猜，赛时没想通，没敢写，还是要多相信自己一些。~~

时间复杂度 $O(n)$。

## Code
```cpp
// LUOGU_RID: 160448127
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll n,rx,bx,dep[N],res,pos,ans;
vector<ll>v[N];
void dfs(ll x,ll fa){
    dep[x]=dep[fa]+1;
    for(auto y:v[x]){
        if(y==fa)continue;
        dfs(y,x);
        if(pos)return ;
    }
    if(dep[bx]-dep[x]==dep[x]-dep[rx])pos=x,res+=dep[bx]-dep[x];
    if(dep[bx]-dep[x]==dep[x]-dep[rx]+1)pos=x,res+=dep[bx]-dep[x];
}
void dfs2(ll x,ll fa){
    dep[x]=dep[fa]+1;
    ans=max(dep[x]-1,ans);
    for(auto y:v[x]){
        if(y==fa)continue;
        dfs2(y,x);
    }
}
void sol(){
    cin>>n>>rx>>bx;
    pos=ans=res=0;
    for(int i=1;i<=n;i++){
        v[i].clear();
        dep[i]=0;
    }
    res=2*(n-1);
    for(int i=1;i<n;i++){
        ll x,y;
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(rx,0);
    dfs2(pos,0);
    cout<<res-ans<<endl;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```

---

## 作者：MrPython (赞：0)

本题的最佳移动策略为：
1. 将 $P_A$ 与 $P_B$ 移动到一起（或间隔一条边）。记 $P_A$ 当前所在的点为起点。
2. $P_A$ 与 $P_B$ 从起点一起（或 $P_B$ 追逐 $P_A$）遍历整棵树。由于 $P_B$ 与 $P_A$ 基本同步移动，我们只考虑 $P_A$ 移动的步数。此时，每一条边都需要走 $2$ 次，共 $2(n-1)$ 步；
3. 当 $P_A$ 遍历完所有的树后，无需再返回起点了，答案应减去该点与起点的距离。显然 $P_A$ 在与起点最远的地方结束遍历是最优的。
4. 若 $P_A$ 与 $P_B$ 间有一条边的距离间隔，则 $P_B$ 还需要走完 $P_A$ 的位置，答案还需 $1$。

两遍 BFS 搜出起点，再从起点开始搜一次找到最远的点减去就好了。

```cpp
#include <bits/extc++.h>
using namespace std;
namespace pbds = __gnu_pbds;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
using graph = vector<vector<size_t>>;
vector<size_t> bfs(graph const &mp, size_t s = 0) {
    vector<size_t> ans(mp.size(), ~0);
    ans[s] = 0;
    queue<size_t> q({s});
    while (!q.empty()) {
        size_t p = q.front();
        q.pop();
        for (size_t i : mp[p])
            if (!~ans[i])
                ans[i] = ans[p] + 1, q.push(i);
    }
    return ans;
}
int main(void) {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    size_t T;
    cin >> T;
    while (T--) {
        size_t n, s, t;
        cin >> n >> s >> t;
        --s, --t;
        graph mp(n);
        for (size_t i = 1; i < n; ++i) {
            size_t x, y;
            cin >> x >> y;
            --x, --y;
            mp[x].push_back(y), mp[y].push_back(x);
        }
        vector<size_t> ds = bfs(mp, s), dt = bfs(mp, t);
        size_t mid = ~0;
        for (size_t i = 0; i < n; ++i)
            if (ds[i] == dt[i] || dt[i] - ds[i] == 1) {
                if (ds[i]<ds[mid]) mid = i;
            }
        assert(~mid);
        vector<size_t> dmid = bfs(mp, mid);
        cout<<(n-1)*2-*max_element(dmid.begin(),dmid.end())+max(ds[mid],dt[mid])<<'\n';
    }
    return 0;
}
```

---

