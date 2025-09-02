# 「MCOI-Zero / AC6-M03」 Sipli Field

## 题目背景

You've been ordered to start the mission now. 

The interception op was a success, enemy air units around Khesed have been weakened, and the Republic of Emmeria's military has taken advantage of this prime opportunity to initiate a counterattack operation with all forces participating. 

Enemy forces have established a wide-scale defensive line around Sipli Field, consisting largely of tank battalions.

Our ground forces are set up to cross the river and penetrate it, and eventually gain control of Khesed. 

Garuda Team, we need you to support our advancing ground units, and eliminate all enemy forces. Multiple units will be simultaneously carrying out various operations on the ground. 

Pay attention to the airspace above each operation area, and provide support as needed. 

This must be the first time you've ever participated in a mission of this scale. 

The battle simulator is a good way to get some practical experience under your belt. 

Godspeed.



$$_{{\frac{\large\text{ACE COMBAT }\Large6}{\tiny{\text{F i r e s\quad O f\quad L i b e r a t i o n}}}}}\\ \text{Mission 03} \\\Large\text{Sipli Field}\\\tiny -\textit{ Fortunes of War
 }-$$

![](https://cdn.luogu.com.cn/upload/image_hosting/az0t8iij.png)

## 题目描述

给定一个 $n$ 个点的树，和两个常数 $L,R$。

请对于每一个点 $u$ 求出有多少条路径过 $u$ 且长度 $d\in [L,R]$。

## 说明/提示

样例 1 解释：

- 过 1 的路径：1-2, 1-3, 1-4, 1-5, 2-3, 4-3, 5-3
- 过 2 的路径：2-1, 2-3, 2-4, 2-5, 1-4, 1-5, 3-4, 3-5, 4-5
- 过 3 的路径：3-1, 3-2, 3-4, 3-5
- 过 4 的路径：4-1, 4-2, 4-3, 4-5
- 过 5 的路径：5-1, 5-2, 5-3, 5-4

---

- Subtask 1（3 pts）：$R=1$。
- Subtask 2（7 pts）：$R\leq 2$。
- Subtask 3（10 pts）：$n\leq 100$。
- Subtask 4（10 pts）：$n\leq 2\times 10^3$。
- Subtask 5（15 pts）：$n\leq 10^5,L=1,R=n$。
- Subtask 6（15 pts）：$n\leq 10^5,L=R$。
- Subtask 7（20 pts）：$n\leq 10^5$。
- Subtask 8（20 pts）：无特殊限制。

对于 $100\%$ 的数据，满足 $1\leq n\leq 10^6$，$1\leq L\leq R\leq n$。

idea：\_Solowing\_ClCN，solution：\_Solowing\_ClCN，code：\_Solowing\_ClCN，data：\_Solowing\_ClCN

## 样例 #1

### 输入

```
5 1 3
1 1 2 2```

### 输出

```
7
9
4
4
4```

# 题解

## 作者：Sol1 (赞：9)

假定树以 $1$ 为根，考虑将 $u$ 的答案分为两类：

## I 两端点 LCA 是 $u$ 的路径

长链剖分优化 DP，每一次暴力合并短链的时候到长链里面统计一下答案。

用树状数组维护长链，复杂度为 $O(n\log n)$。

## II 两端点 LCA 不是 $u$ 的路径

将答案记为 $b_u$，考虑 $b_u$ 与 $\sum_{(u,v)\in E}b_v$ 相差多少。

相差的有两部分：

1. 过一个孩子，并且 LCA 是 $u$ 的路径。如果一端是 $u$，则需要减 1 次；否则需要减 2 次。
2. 从 $u$ 开始向上走的路径，需要加上。

将 2 看作是所有从 $u$ 开始的路径减去从 $u$ 开始向下的路径。

将 1 和 2 加起来，$b_u$ 就是 所有从 $u$ 开始的路径数量 减去 所有 LCA 是 $u$ 的路径数量的 2 倍 加上 $\sum_{(u,v)\in E}b_v$。

所有从 $u$ 开始的路径数量使用点分治求出，在合并子树的时候按照子树树高排序之后暴力合并前缀和，即可做到总复杂度 $O(n\log n)$。

好像有个两次点分然后不用做 dp 的方法，比 std 一次点分慢一些但是好写很多，详情请咨询	墨染空 神仙（雾）。

---

## 作者：LFCode (赞：9)

树上路径统计显然是非常经典的点分治模型。与经典问题不同的是，本题需要对每个点求出经过该点的合法路径数。

首先回忆用点分治统计“树上距离在 $[l,r]$ 之间的点对数”的算法，由于一次递归中统计的路径均经过分治重心，这种算法显然具有以下性质：

- 能够与某个点拼出一条路径的点一定与该点来自分治重心的不同子树。
- 统计过程不关心每个点的具体来源，以某一个点作为一个端点的合法路径总数只与其他子树每一层的总点数有关。
- 经过某个点的所有合法路径均经过该点的父亲结点。

因此我们采用这样的策略：点分治过程中用树状数组维护之前扫过的子树中每一层的结点总数，dfs 到某个点作为路径一端点时查询区间和。每个点的贡献都要累加到其父亲结点上，扫描完分治重心的一棵子树后在树状数组上更新对应深度的总结点数。这样会漏掉一些结点与其他更靠后扫描到的子树中的结点构成的路径的贡献，因此扫描完全部子树之后我们倒过来重新扫一遍。注意这一次扫描就不要更新分治重心的答案了。

一个小优化：每次递归扫描完全部子树后都需要清空树状数组，比较费时间。可以使用一种叫做“时间戳”的 trick，即记录树状数组上每个位置最后一次修改的时刻，查询时把修改时刻比当前时刻早的位置都当 0 来处理。

当然了这做法要带两枚 $\log$，没有上面的官方题解优秀。但是个人感觉这种做法思维难度和代码难度都比较小，而且跑得并不慢，因为提交人数现在还比较少的缘故暂居最优解 rank1。

代码：

```c++
#include<cstdio>
const int N=1000086;
int n,l,r,tot,md,ws,nms,tp,h[N],st[N],sze[N],dc[N];
long long cnt[N],ans[N];
bool vis[N];
struct edge{int v,nxt;}e[N<<1];
struct BIT{
	int lt[N],tme;long long c[N];
	int lowbit(int x){return x&(-x);}
	bool updtme(){tme++;return true;}//更新时间戳
	#define gn(x) (c[x]*(lt[x]==tme))//修改早的当0处理
	bool updata(int pos,int num){while(pos<=r)c[pos]=gn(pos)+1ll*num,lt[pos]=tme,pos+=lowbit(pos);return true;}
	long long query(int pos){int ret=0;while(pos>0)ret+=gn(pos),pos-=lowbit(pos);return ret;}
	long long getsum(int l,int r){return query(r)-query(l-1);}
}t;
int Max(int a,int b){return a>b?a:b;}
int Min(int a,int b){return a<b?a:b;}
int read(){
	char ch=getchar();int nn=0,ssss=1;
	while(ch<'0'||ch>'9'){if(ch=='-')ssss*=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){nn=nn*10+(ch-'0');ch=getchar();}
	return nn*ssss;
}
bool add(int u,int v){e[++tot].v=v;e[tot].nxt=h[u];h[u]=tot;return true;}
int getws(int np,int lst,int nsze){
	sze[np]=1;int ms=1;
	for(int i=h[np];i;i=e[i].nxt){
		if(vis[e[i].v]||e[i].v==lst)continue;
		sze[np]+=getws(e[i].v,np,nsze);
		ms=Max(ms,sze[e[i].v]);
	}
	ms=Max(ms,nsze-sze[np]);
	if(ms<nms)nms=ms,ws=np;
	return sze[np];
}
bool dfs(int np,int lst,int dep){
	if(dep>r+1)return false;dc[dep]++;md=Max(md,dep);
	cnt[np]=t.getsum(Max(l-dep+2,1),r-dep+2);
	for(int i=h[np];i;i=e[i].nxt){
		if(e[i].v==lst||vis[e[i].v])continue;
		cnt[e[i].v]=0;
		dfs(e[i].v,np,dep+1);
		cnt[np]+=cnt[e[i].v];cnt[e[i].v]=0;
	}
	ans[np]+=cnt[np];
	return true;
}
bool solve(int np,int lst,int nsze){
	nms=nsze;ws=np;getws(np,lst,nsze);
	t.updtme();t.updata(1,1);tp=0;vis[ws]=true;
	for(int i=h[ws];i;i=e[i].nxt){
		if(e[i].v==lst||vis[e[i].v])continue;
		md=2;cnt[e[i].v]=0;dfs(e[i].v,ws,2);
		for(int j=1;j<=md;j++)t.updata(j,dc[j]),dc[j]=0;
		st[++tp]=e[i].v;ans[ws]+=cnt[e[i].v];//注意更新分治重心的贡献
	}
	t.updtme();
	for(int i=tp;i;i--){//倒过来再扫一遍
		int v=st[i];
		if(v==lst||vis[v])continue;
		md=2;cnt[v]=0;dfs(v,ws,2);
		for(int j=1;j<=md;j++)t.updata(j,dc[j]),dc[j]=0;
		cnt[v]=0;
	}
	int nw=ws;
	for(int i=h[nw];i;i=e[i].nxt)if(!vis[e[i].v])solve(e[i].v,nw,sze[e[i].v]);
	return true;
}
int main(){
	n=read();l=read();r=read();
	for(int i=2;i<=n;i++){
		int u=read();
		add(u,i);add(i,u);
	}
	solve(1,0,n);
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
}
```

蚂蜂略丑求原谅，如果发现有锅求指出。

---

## 作者：CatFromMars (赞：1)

大常数选手惨遭资本做局。$O(n\log n)$ 居然比 $O(n\log^2 n)$ 慢，这究竟是人性的扭曲还是道德的沦丧！

答案看成 $[1, R]$ 减去 $[1, L - 1]$。路径统计显然是点分治，很容易想到对于每个分治中心，统计联通块中每个点到它的距离，以及这个点在哪个子树里面，分别记为 $(d_i, b_i)$。先预处理出来并按照 $d_i$ 排序（bfs 一下加入即可）。分治重心为 $o$，对于 $d_u + d_v \le x, b_u \not = b_v$，我们分别在 $u$ 到 $o$ 的路径上和 $v$ 到 $o$ 的路径上加入贡献。特比的这样 $o$ 点贡献会被算两次，要减去。树上差分即可。这个双指针一下正反扫两次。特别的要特判 $d_u \le x$ 的情况。于是 $O(n\log n)$。

口胡五分钟，卡常五小时。我卡常卡了一个晚上加上早上一个小时，需要注意
1. 可以把一些 dfs 改成 bfs。
2. $n$ 在 $10^6$ 不要再用 vector 存图了。
3. 统计的时候把一些重复的地方合并起来会变快。

代码：
```cpp
int que[N + 10], fr = 1, tl = 0;
int in()
{
    int k=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
    return k*f;
}
void out(ll x)
{
    if(x<0)putchar('-'),x=-x;
    if(x<10)putchar(x+'0');
    else out(x/10),putchar(x%10+'0');
}
bool vis[N + 10];
int siz[N + 10], fatt[N + 10], remain = N, maxpart = N, root = 0;
void getsiz(int u, int fa) {
    siz[u] = 1, fatt[u] = fa;
    for(int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if(v == fa || vis[v]) continue;
        getsiz(v, u);
        siz[u] += siz[v];
    }
}
void getroot(int u, int fa) {
    fr = 1, tl = 0;
    que[++tl] = u;
    while(fr <= tl) {
        int f = que[fr]; fr++;
        int rest = 0;
        for(int i = head[f]; i; i = nxt[i]) {
            int v = to[i];
            if(vis[v] || v == fatt[f]) continue;
            rest = max(rest, siz[v]);
            que[++tl] = v;
        }
        rest = max(rest, remain - siz[f]);
        if(rest < maxpart) {
            maxpart = rest;
            root = f;
        }
    }
}

struct node {
    int val, bel, u;
} vec[N * L + 20];
int ssiz = 0;
int lll[N + 10], rr[N + 10];
int bel, maxn = 0, bl[N + 10];
void getdis(int u, int fat, int dep) {
    fr = 1, tl = 0;
    que[++tl] = u;
    siz[u] = 0;
    fatt[u] = fat;
    lll[u] = rr[u] = -1;
    while(fr <= tl) {
        int f = que[fr]; fr++;
        if(siz[f] > qr) break;
        if(siz[f]) {
            if(lll[u] == -1) lll[u] = ssiz;
            vec[ssiz++] = ((node){siz[f], bl[f], f});
            rr[u] = ssiz - 1;
        }
        maxn = siz[f];
        if(f == u) {
            for(int i = head[f]; i; i = nxt[i]) {
                int v = to[i];
                if(vis[v]) continue;
                bl[v] = v;
                fatt[v] = u;
                siz[v] = 1;
                que[++tl] = v;
            }
            continue;
        }
        for(int i = head[f]; i; i = nxt[i]) {
            int v = to[i];
            if(vis[v] || v == fatt[f]) continue;
            fatt[v] = f;
            siz[v] = siz[f] + 1;
            que[++tl] = v;
            bl[v] = bl[f];
        }
    }
}
void work(int u) {
    // cout << u << endl;
    vis[u] = 1;
    maxn = 0;
    getdis(u, 0, 0);
    for(int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if(vis[v]) continue;
        getsiz(v, 0);
        remain = siz[v], root = 0, maxpart = N;
        getroot(v, 0);
        work(root);
    }
}

namespace lca {
    int fat[N + 10], dep[N + 10], mind[N + 10][21], C = 0, dfn[N + 10];
    void dfs(int u, int fa) {
        dfn[u] = ++C;
        fat[u] = fa;
        mind[C][0] = u;
        dep[u] = dep[fa] + 1;
        for(int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if(v == fa) continue;
            dfs(v, u);
        } 
    }
    void prep() {
        dfs(1, 0);
        for(int j = 1; (1 << j) <= n; j++)
            for(int i = 1; i + (1 << j) - 1 <= n; i++)
                if(dep[mind[i][j - 1]] < dep[mind[i + (1 << (j - 1))][j - 1]])
                    mind[i][j] = mind[i][j - 1];
                else mind[i][j] = mind[i + (1 << (j - 1))][j - 1];
    }
    inline int lca(int u, int v) {
        if(u == v) return u;
        if(dfn[u] > dfn[v]) swap(u, v);
        int L = __lg(dfn[v] - dfn[u]);
        if(dep[mind[dfn[u] + 1][L]] < dep[mind[dfn[v] - (1 << L) + 1][L]])
            return fat[mind[dfn[u] + 1][L]];
        else return fat[mind[dfn[v] - (1 << L) + 1][L]];
    }
}
ll cf[N + 10];
inline void upd(int u, int v, int val) {
    if(!u || !v) return ;
    cf[u] += val;
    cf[v] += val;
    int l = lca::lca(u, v);
    cf[l] -= val;
    cf[lca::fat[l]] -= val;
    // cout << u << ' ' << v << ' ' << val << endl;
}
int tab[N + 10];
void calc(int x, int t) {
    for(int u = 1; u <= n; u++) {
        if(rr[u] < 0 || lll[u] < 0) continue;
        int l = lll[u], r = lll[u];
        for(r = rr[u]; r >= lll[u]; r--) {
            if(vec[r].val > x) continue;
            while(l > r && l > lll[u])
                l--, tab[vec[l].bel]--;
            while(l < r && vec[r].val + vec[l].val <= x)
                tab[vec[l].bel]++, l++;
            upd(vec[r].u, u, t * (l - tab[vec[r].bel] - lll[u]));
        }
        for(r = head[u]; r; r = nxt[r])
            tab[to[r]] = 0;
        for(r = lll[u]; r <= rr[u]; r++)
            tab[vec[r].bel]++;

        r = rr[u];
        for(l = lll[u]; l <= rr[u] - 1; l++) {
            if(vec[l].val > x) break;
            upd(vec[l].u, u, t * 1);
            tab[vec[l].bel]--;
            while(r >= lll[u] && vec[l].val + vec[r].val > x)
                tab[vec[r].bel]--, r--;
            int rest = (r - l) - tab[vec[l].bel]; 
            rest = max(rest, 0);
            upd(vec[l].u, u, t * rest);
            upd(u, u, -t * rest);
        } 
        if(vec[rr[u]].val <= x) upd(vec[rr[u]].u, u, t * 1);
        for(r = head[u]; r; r = nxt[r])
            tab[to[r]] = 0;
    }
}
void dp(int u, int fa) {
    for(int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if(v == fa) continue;
        dp(v, u);
        cf[u] += cf[v];
    }
}
int main() {
    cin >> n >> ql >> qr;
    for(int i = 2, x; i <= n; i++)
        cin >> x, link(i, x), link(x, i);
    lca::prep();
    getsiz(1, 0);
    remain = n, maxpart = n, root = 0;
    getroot(1, 0);
    work(root);

    calc(qr, 1);
    if(ql > 1) calc(ql - 1, -1);
    dp(1, 0);
    for(int i = 1; i <= n; i++)
        cout << cf[i] << '\n';
}
```

---

## 作者：5ab_juruo (赞：1)

给出一种简单一点的 $\mathcal{O}(n\log n)$ 做法。

先拍上去一个点分治。先开桶记录子树内所有点到根节点的距离，然后再遍历每个节点求贡献，用树上差分打上标记再统计，特判根节点一条路径算两次的情况。

发现问题在于直接开桶计算会算上子树内的贡献，而在遍历每个子树前都减去这个子树的方案是要树状数组维护的。考虑在第一遍求完后，再在每个子树内都做一遍，减去多出来的贡献。由于前缀和所需要的时间复杂度是 $O(\text{子树大小})$ 的，所以一次计算是线性的。

写的比较丑，跑得比较慢。

```cpp
/* name: P7782
 * author: 5ab
 * created at: 22-09-29
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
const int max_n = 1000000;

int hd[max_n], des[max_n<<1], nxt[max_n<<1], e_cnt = 0, l, r;
ll ans[max_n], df[max_n], cpf[max_n+1];
int siz[max_n], cnt[max_n+1], cntl;
bool vis[max_n];

void add(int s, int t)
{
	des[e_cnt] = t;
	nxt[e_cnt] = hd[s];
	hd[s] = e_cnt++;
}

void dfs1(int id, int fa)
{
	siz[id] = 1;
	for (int p = hd[id], dst; p != -1; p = nxt[p])
	{
		dst = des[p];
		if (dst != fa && !vis[dst])
		{
			dfs1(dst, id);
			siz[id] += siz[dst];
		}
	}
}

int mn, mnp;

inline void chmax(int& a, int b) { if (a < b) a = b; }
void dfs2(int id, int fa, int tps)
{
	int tmps = tps;
	for (int p = hd[id], dst; p != -1; p = nxt[p])
	{
		dst = des[p];
		if (dst != fa && !vis[dst])
		{
			chmax(tmps, siz[dst]);
			dfs2(dst, id, tps + siz[id] - siz[dst]);
		}
	}
	if (tmps < mn)
	{
		mn = tmps;
		mnp = id;
	}
}

void dfs3(int id, int fa, int dis)
{
	cnt[dis++]++;
	for (int p = hd[id], dst; p != -1; p = nxt[p])
	{
		dst = des[p];
		if (dst != fa && !vis[dst])
			dfs3(dst, id, dis);
	}
}

inline int my_min(int a, int b) { return (a < b)? a:b; }

void dfs4(int id, int fa, int flg, int dis)
{
	df[id] = 0;
	for (int p = hd[id], dst; p != -1; p = nxt[p])
	{
		dst = des[p];
		if (dst != fa && !vis[dst])
		{
			dfs4(dst, id, flg, dis + 1);
			df[id] += df[dst];
		}
	}
	if (dis <= l - 1)
		df[id] -= cpf[my_min(l - 1 - dis, cntl)];
	if (dis <= r)
		df[id] += cpf[my_min(r - dis, cntl)];
	ans[id] += df[id] * flg;
}

void solve(int id)
{
	dfs1(id, -1);
	mn = siz[id] + 1, mnp = -1;
	dfs2(id, -1, 0);
	id = mnp;
	
	dfs1(id, -1);
	
	dfs3(id, -1, 0);
	
	cntl = siz[id], cpf[0] = cnt[0];
	for (int i = 0; i < cntl; i++)
		cpf[i+1] = cpf[i] + cnt[i+1];
	
	df[id] = cpf[my_min(r, cntl)] - cpf[my_min(l-1, cntl)];
	for (int p = hd[id], dst; p != -1; p = nxt[p])
	{
		dst = des[p];
		if (!vis[dst])
		{
			dfs4(dst, id, 1, 1);
			df[id] += df[dst];
		}
	}
	fill(cnt, cnt + cntl + 1, 0);
	
	for (int p = hd[id], dst; p != -1; p = nxt[p])
	{
		dst = des[p];
		if (!vis[dst])
		{
			dfs3(dst, id, 1);
			cntl = siz[dst], cpf[0] = cnt[0];
			for (int i = 0; i < cntl; i++)
				cpf[i+1] = cpf[i] + cnt[i+1];
			dfs4(dst, id, -1, 1);
			df[id] -= df[dst];
			fill(cnt, cnt + cntl + 1, 0);
		}
	}
	
	ans[id] += df[id] / 2;
	
	vis[id] = true;
	for (int p = hd[id], dst; p != -1; p = nxt[p])
	{
		dst = des[p];
		if (!vis[dst])
			solve(dst);
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	
	cin >> n >> l >> r;
	fill(hd, hd + n, -1);
	
	for (int i = 1, x; i < n; i++)
	{
		cin >> x; x--;
		add(x, i), add(i, x);
	}
	
	solve(0);
	for (int i = 0; i < n; i++)
		cout << ans[i] << "\n";
	
	return 0;
}
// started coding at: 18:08
// finished debugging at: 19:45
```

---

## 作者：RainySoul (赞：1)

萌新初学淀粉质，来写一个题解。

这种树上路径计数问题一看就是点分治丫。我们每次取出一个重心 $x$ 进行分治，把树上路径分成经过 $x$ 的与不经过 $x$ 的。本次只处理经过 $x$ 的路径，剩下的递归子树处理就可以了。

接下来讲讲如何算经过 $x$ 的答案。对于重心 $x$ 我们一个一个子树地处理，使用树状数组维护深度相关的信息，一边 $\text{dfs}$ 一边计算答案。具体来说，当前点 $u$ 到 $x$ 的距离为 $dis$，就在树状数组里面查询深度在 $[L-dis,R-dis]$ 内的其他子树的点有多少个，这些点都能与 $u$ 拼成一条长度在 $[L,R]$，以 $u$ 为端点的路径。处理完一个子树之后就把这个子树内的深度信息加入到树状数组里面。

注意到对于同一个重心来说，经过子节点的路径也必然经过父节点，因此父节点要继承子节点的答案。

还没有做完，聪明的小朋友会发现一个问题，因为我们是边 $\text{dfs}$ 边统计答案的，这导致如果先经过子树 $a$ 再经过子树 $b$ 的话，两个端点在 $a$ 和 $b$ 中的路径只在 $b$ 计算了答案，而在 $a$ 把答案漏了。这咋办？好办，正着扫一遍，反着扫一遍就行了，注意反着扫的时候对重心的答案没有贡献。

时间复杂度 $O(n \log^2 n)$，虽然标算是 $O(n \log n)$ 的但是这个做法常数不大，也是能过的。

然后你哐哐写完代码之后交上去发现 $\text{T}$ 了，再一想发现每次清空树状数组非常耗时间，这里可以使用一个叫做“时间戳” 的东西，即对树状数组上每个位置打时间标记，如果这个位置的修改操作是早于当前时间的那么不用管它，直接当成 $0$。这样就无需清空了。

AC code：

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1000010;
int n,L,R,rt,sum,flag;
int sz[N],son[N],fa[N],vis[N],dis[N],ans[N];
vector<int> e[N],distan;
struct BIT{
	int f[N],tim,c[N];
	int lowbit(int x){return x&(-x);}
	int get(int x){
        if(f[x]==tim)return c[x];
        return 0;
    }
	void add(int pos){
        for(int i=pos;i<=R;i+=lowbit(i)){
            c[i]=get(i)+1;
            f[i]=tim;
        }
    }
	int sum(int pos){
        int res=0;
        while(pos>0){
            res+=get(pos);
            pos-=lowbit(pos);
        }
        return res;
    }
	int query(int l,int r){return sum(r)-sum(l-1);}
}t;
void getrt(int now,int fz){
    sz[now]=1,son[now]=0;
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i];
        if(to==fz||vis[to])continue;
        getrt(to,now);
        sz[now]+=sz[to];
        if(sz[to]>son[now])son[now]=sz[to];
    }
    son[now]=max(son[now],sum-sz[now]);
    if(son[now]<son[rt])rt=now;
}
int getdis(int now,int fz){
    distan.push_back(dis[now]);//记录当前子树的深度信息
    int res=0;
    if(R-dis[now]>=1)res+=t.query(max(1ll,L-dis[now]),R-dis[now]);//边dfs就直接算了
    if(dis[now]>=L&&dis[now]<=R&&flag==1)res++;//单独处理一下 (重心--now) 的这样的路径
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i];
        if(to==fz||vis[to])continue;
        dis[to]=dis[now]+1;
        res+=getdis(to,now);//继承子节点的答案
    }
    ans[now]+=res;
    return res;
}
void calc(int now){
    flag=1;
    t.tim++;//时间戳
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i];
        if(vis[to])continue;
        dis[to]=1,distan.clear();
        ans[now]+=getdis(to,now);
        for(int j=0;j<(int)distan.size();j++)t.add(distan[j]);//将当前子树的深度信息加入树状数组
    }
    flag=0;
    t.tim++;
    for(int i=(int)e[now].size()-1;i>=0;i--){//倒着扫
        int to=e[now][i];
        if(vis[to])continue;
        dis[to]=1,distan.clear();
        getdis(to,now);//注意此处对ans[now]没有贡献了
        for(int j=0;j<(int)distan.size();j++)t.add(distan[j]);
    }
}
void solve(int now){
    vis[now]=1;
    calc(now);//处理经过now的路径
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i];
        if(vis[to])continue;
        rt=0,son[rt]=sum=sz[to];
        getrt(to,now);
        solve(rt);//递归子树
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>L>>R;
    for(int i=2;i<=n;i++){
        cin>>fa[i];
        e[fa[i]].push_back(i);
        e[i].push_back(fa[i]);
    }
    son[rt]=n,sum=n;
    getrt(1,0);//找重心
    solve(rt);//点分治
    for(int i=1;i<=n;i++)cout<<ans[i]<<'\n';
    return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：1)

[P7782 「MCOI-Zero / AC6-M03」 Sipli Field](https://www.luogu.com.cn/problem/P7782)

[更好的阅读体验]()

单 log 淀粉做法。

回想正常淀粉计算的是树上的路径问题，但题目中要求计算经过每个点的答案，这样我们选取重心后一棵子树对另一棵子树的答案就会少算，所以我们淀粉时不仅要算根的答案，也要考虑子树间的相互贡献。

首先以根为重心 dfs 一遍统计出 $f_i$ 表示深度为 $i$ 的点有多少个，然后直接扫一遍计算根的答案，可以用前缀和优化到 $\mathcal O(n)$。

但是这样会多算两个端点都在同一子树内的答案，所以接下来对于每棵子树做同样的事减去多余的贡献。

对于子树间的答案，一个深度为 $i$ 的点，它的贡献 $d_i=\sum_{j=L-i}^{R-i}f_j$，这个过程也可以用前缀和优化。注意到一个儿子的路径一定也经过它的父亲，所以 $d_i=d_i+\sum_{j\in son_i}d_j$，最后一遍树上差分统计即可。

常数巨大，dfs 了 114514 次，甚至被 $\mathcal O(n\log^2 n)$ 吊着打/kk。

```cpp
int s2[2000001],f[2000001],g[2000001],sum[1000001],ans[1000001],vis[1000001],siz[1000001],head[1000001],nex[2000001],to[2000001];
int dt,cnt,n,root,col,all,tot,L,R;
#define ca(d) (d<0?0:s2[d])
inline void add(int x,int y){to[++cnt]=y,nex[cnt]=head[x],head[x]=cnt;}
void find(int k,int fa)
{
	siz[k]=1;int maxn=0;
	for(int i=head[k];i;i=nex[i])
	{
		if(to[i]==fa||vis[to[i]])continue;
		find(to[i],k),siz[k]+=siz[to[i]],maxn=max(maxn,siz[to[i]]);
	}
	if(max(maxn,all-siz[k])<=all/2)root=k;
}
void dfs1(int k,int fa,int depth,int v)
{
	f[depth]+=v,dt=max(dt,depth);
	for(int i=head[k];i;i=nex[i])if(to[i]!=fa&&!vis[to[i]])dfs1(to[i],k,depth+1,v);
}
void dfs2(int k,int fa,int depth,int v)
{
	sum[k]+=(ca(min(dt,R-depth))-ca(min(dt,L-depth-1)))*v;
	for(int i=head[k];i;i=nex[i])if(to[i]!=fa&&!vis[to[i]])dfs2(to[i],k,depth+1,v);
}
void dfs3(int k,int fa,int depth,int v)
{
	g[depth]+=v,dt=max(dt,depth);
	for(int i=head[k];i;i=nex[i])if(to[i]!=fa&&!vis[to[i]])dfs3(to[i],k,depth+1,v);
}
void up(int k,int fa){for(int i=head[k];i;i=nex[i])if(to[i]!=fa&&!vis[to[i]])up(to[i],k),sum[k]+=sum[to[i]];}
void modify(int k,int fa)
{
	ans[k]+=sum[k],sum[k]=0;
	for(int i=head[k];i;i=nex[i])if(to[i]!=fa&&!vis[to[i]])modify(to[i],k);
}
void getsiz(int k,int fa)
{
	siz[k]=1;
	for(int i=head[k];i;i=nex[i])if(!vis[to[i]]&&to[i]!=fa)getsiz(to[i],k),siz[k]+=siz[to[i]];
}
void starch(int k,int fa)
{
	find(k,fa),k=root,getsiz(k,fa),vis[k]=1,ans[k]*=2;
	dt=0,dfs1(k,fa,0,1),s2[0]=f[0];
	for(int i=1;i<=dt;++i)s2[i]=s2[i-1]+f[i];
	for(int i=0;i<=dt;++i)ans[k]+=f[i]*(ca(min(dt,R-i))-ca(min(dt,L-i-1)));
	for(int i=head[k];i;i=nex[i])if(to[i]!=fa&&!vis[to[i]])dfs2(to[i],k,1,1);
	dfs1(k,fa,0,-1);
	for(int i=head[k];i;i=nex[i])
	{
		if(to[i]==fa||vis[to[i]])continue;
		dt=0,dfs3(to[i],k,1,1),s2[0]=g[0];
		for(int i=1;i<=dt;++i)s2[i]=s2[i-1]+g[i];
		for(int i=1;i<=dt;++i)ans[k]-=g[i]*(ca(min(dt,R-i))-ca(min(dt,L-i-1)));
		dfs3(to[i],k,1,-1);
		dfs2(to[i],k,1,-1);
		up(to[i],k),modify(to[i],k);
	}
	ans[k]/=2;int kk=k;
	for(int i=head[kk];i;i=nex[i])if(!vis[to[i]]&&to[i]!=fa)all=siz[to[i]],starch(to[i],kk);
}
void mian()
{
	read(n,L,R);int x;
	for(int i=2;i<=n;++i)read(x),add(x,i),add(i,x);
	all=n,starch(1,0);
	for(int i=1;i<=n;++i)write(ans[i],'\n');
}
```

---

## 作者：DrDuck (赞：0)

**前置芝士：点分治**

大佬的 $O(n \log n)$ 方法太巨了蒟蒻想不到，这里分享一篇比较好想的 $O(n \log^2 n)$ 做法。

模板的点分治只能求树上是否存在距离为 $k$ 的点对，考虑对其进行扩展。

要求经过点 $u$ 且长度 $d\in [L,R]$ 的路径数量，只需求出经过点 $u$ 且长度 $d\in [1,R]$ 的路径数量再减去经过点 $u$ 且长度 $d\in [1,L-1]$ 的路径数量再作差即可。问题转化为求经过点 $u$ 且长度 $d\in [1,k]$ 的路径数量，$k$ 是某个给定的值。

类似点分治模板，设当前分治到的子树的根为 $p$，每次统计完一个子树中所有点到 $p$ 的距离后扔进一个树状数组里，查询的时候，设点 $p$ 深度为 $dep_p$，只需查询树状数组中 $\le L-1-dep_p$ 和 $\le R-dep_p$ 的元素个数并作差就能求出经过 $p$ 且长度 $d\in [L,R]$ 的路径数量。

不过这样有问题，因为路径上除了 $p$ 以外的点没有统计答案，它们也在路径上，别忘了统计它们的答案。因此每次在遍历子树求到 $p$ 的距离时就顺便把它们的答案查询了，然后把它们的答案汇总加和到父节点，一直到根节点。

不过这样对于一条路径而言，每次只帮半边路径统计了这条路径，还有半边路径没统计上，因此还要反着做一遍。不过这一边就不用把答案汇总加和返回给根节点了，否则会算重。

时间复杂度 $O(n \log^2 n)$，~~比较吃操作~~，略微卡常。

一个卡常小技巧：不用每次都清空树状数组，只需给所有元素打个时间戳，记录元素是否过期即可。

# CODE
~~马蜂较松散，轻喷。~~
```cpp
#include<bits/stdc++.h>
#define ll long long
#define void inline void
using namespace std;
const int maxn = 1e+6 + 6;
int n, L, R, rt, rtsz, totsz, dtot, tim;
int sz[maxn], dis[maxn], dep[maxn], dfn[maxn];
ll ans[maxn], a[maxn];
vector<int> v[maxn];
bool flag;
bitset<maxn> vis;
namespace miHoYo
{
	inline int read()
	{
		int x = 0;
		char c = getchar();
		while (c < '0' || c > '9')
		{
			c = getchar();
		}
		while (c >= '0' && c <= '9')
		{
			x = (x << 3) + (x << 1) + (c & 15);
			c = getchar();
		}
		return x;
	}
	void print(ll x)
	{
		if (x < 10)
		{
			putchar(x + '0');
		}
		else
		{
			print(x / 10);
			putchar(x % 10 + '0');
		}
	}
	void pt(ll x, char c)
	{
		print(x);
		putchar(c);
	}
}
using namespace miHoYo;
#define lowbit(x) (x & -x)
inline ll get(int x)
{
	return dfn[x] == tim ? a[x] : 0;//如果元素未过期则返回元素，否则返回0
}
void add(int x, int y)
{
	for (int i = x; i <= R; i += lowbit(i))
	{
		a[i] = get(i) + y;
		dfn[i] = tim;//给元素打上时间戳
	}
}
inline ll sum(int x)
{
	ll ret = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		ret += get(i);
	}
	return ret;
}
inline ll query(int l, int r)
{
	return sum(r) - sum(l - 1);
}
void get_rt(int p, int fa)//找重心做根
{
	sz[p] = 1;
	int mxsz = 0;
	for (int i : v[p])
	{
		if (i != fa && !vis[i])
		{
			get_rt(i, p);
			sz[p] += sz[i];
			mxsz = max(mxsz, sz[i]);
		}
	}
	mxsz = max(mxsz, totsz - sz[p]);
	if (mxsz < rtsz)
	{
		rtsz = mxsz;
		rt = p;
	}
}
ll get_dis(int p, int fa)
{
	ll ret = 0;
	dis[++dtot] = dep[p];
	(R - dep[p] >= 1) && (ret += query(max(1, L - dep[p]), R - dep[p]));//算答案
	(dep[p] >= L && dep[p] <= R && flag) && (ret++);//别忘了加上从自身到根节点这条路径
	for (int i : v[p])
	{
		if (i != fa && !vis[i])
		{
			dep[i] = dep[p] + 1;
			ret += get_dis(i, p);
		}
	}
	ans[p] += ret;//累加答案
	return ret;//返回
}
void cal(int p)
{
	tim++;
	dep[p] = 0;
	flag = 1;
	for (int i : v[p])
	{
		if (!vis[i])
		{
			dep[i] = 1;
			dtot = 0;
			ans[p] += get_dis(i, p);
			for (int i = 1; i <= dtot; i++)//加入元素
			{
				add(dis[i], 1);
			}
		}
	}
	flag = 0;
	tim++;
	for (int popo = v[p].size() - 1; popo >= 0; popo--)//倒着做一遍
	{
		int i = v[p][popo];
		if (!vis[i])
		{
			dep[i] = 1;
			dtot = 0;
			get_dis(i, p);//这一遍不用给根节点累加答案了
			for (int i = 1; i <= dtot; i++)
			{
				add(dis[i], 1);
			}
		}
	}
}
void divide(int p)//点分治
{
	vis[p] = 1;
	cal(p);
	for (int i : v[p])
	{
		if (!vis[i])
		{
			rtsz = totsz = sz[i];
			get_rt(i, p);
			divide(rt);
		}
	}
}
signed main()
{
	n = read(), L = read(), R = read();
	for (int i = 2; i <= n; i++)
	{
		int x = read();
		v[x].push_back(i);
		v[i].push_back(x);
	}
	rtsz = totsz = n;
	get_rt(1, 0);
	divide(rt);
	for (int i = 1; i <= n; i++)
	{
		pt(ans[i], '\n');
	}
	return 0;
}
```
不知道会不会被后人 hack 呢。

---

## 作者：CommandSR (赞：0)

## 题意

[link](https://www.luogu.com.cn/problem/P7782)

## 题解

看到这种路径计数问题想到点分治。

要求一定要经过 $u$，分治的时候 $u$ 也就是重心，所以可以把统计距离的时候与 $u$ 的距离加入树状数组里，边算边查询区间 $[L-dis_y, R-dis_y]$。并且一个点的答案需要并入它父亲的答案。

然而会出现由于遍历顺序导致的问题，比如先遍历 $u$ 再遍历 $v$，只在 $v$ 中计算了 $u \rightarrow v$ 路径。所以对于一个节点 $x$，需要正反都遍历一遍儿子防止算漏。

特别地，只有跑第一遍的时候需要将答案加入 $ans_x$，且只有第一遍需要加上重心到 $u$，这样经过重心（即当前根）的路径，否则会算重。

清空树状数组应该会 T 飞，所以引入带时间戳的树状数组，只在当前时间戳上修改和查找以代替清空操作。

我个人调的时候加上了一些卡常。

一些重要部分代码注释里也有。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define F(i, a, b) for (int i = (a); i <= (b); ++i)
#define D(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
inline ll rd() {
	ll x = 0; bool f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') f = 0; ch = getchar();}
	while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return (f ? x : (-x));
}
const int N = 1e6 + 5;
int n, L, R, siz[N], SIZ, GM, root, d[N];
ll ans[N];
vector<int> g[N], vd;
bitset<N> del;
namespace BIT { // 带时间戳的树状数组
	int c[N], ct[N], tim = 0;
	inline int nw(int x) {
		return (ct[x] == tim ? c[x] : 0);
	}
	inline void Upd(int p, int x) {
		for (int i = p; i <= R; i += (i & -i)) c[i] = nw(i) + x, ct[i] = tim; 
	}
	inline ll Qry(int p) {
		ll res = 0;
		for (int i = p; i; i -= (i & -i)) res += nw(i);
		return res;
	}
}
using namespace BIT;
int Max(int x, int y) {
	return (x > y ? x : y);
}
void Getroot(int u, int p) {
	int gm = 0;
	siz[u] = 1;
	for (int v : g[u]) {
		if (del[v] || v == p) continue;
		Getroot(v, u), siz[u] += siz[v];
		gm = Max(gm, siz[v]);
	}
	gm = Max(gm, SIZ - siz[u]);
	if (gm < GM) GM = gm, root = u;
}
bool opt;
ll Getdis(int u, int p) { // opt: 是否加入 [重心->u] 这样的路径的贡献
	ll res = 0;
	vd.push_back(d[u]);
	if (R-d[u] >= 1) res += Qry(R-d[u]) - Qry(Max(0, L-d[u]-1)); // 加入树状数组中合法路径数
	if (opt && d[u] >= L && d[u] <= R) ++res; // 加入 [重心->u] 这样的路径的贡献
	for (int v : g[u]) {
		if (del[v] || v == p) continue;
		d[v] = d[u] + 1;
		res += Getdis(v, u); // 子树贡献并入父亲
	}
	ans[u] += res; // 更新 ans
	return res;
}
void Calc(int u) {
	++tim; // 相当于清空树状数组
	opt = 1;
	F(i, 0, g[u].size()-1) {
		int v = g[u][i];
		if (del[v]) continue;
		d[v] = 1, vd.clear();
		ans[u] += Getdis(v, u); // 子树贡献并入父亲
		for (int tmp : vd) Upd(tmp, 1);
	}
	++tim; // 相当于清空树状数组
	opt = 0;
	D(i, g[u].size()-1, 0) {
		int v = g[u][i];
		if (del[v]) continue;
		d[v] = 1, vd.clear();
		Getdis(v, u); // 不用加入 ans，因为前面加过一遍
		for (int tmp : vd) Upd(tmp, 1);
	}
}
void Solve(int u) {
	del[u] = 1;
	Calc(u);
	for (int v : g[u]) {
		if (del[v]) continue;
		GM = SIZ = siz[v], Getroot(v, u);
		Solve(root);
	}
}
int main() {
	n = rd(), L = rd(), R = rd();
	F(i, 2, n) {
		int x = rd();
		g[x].push_back(i), g[i].push_back(x);
	}
	SIZ = GM = n, Getroot(1, 0);
	Solve(root);
	F(i, 1, n) cout << ans[i] << '\n';
	return 0;
}
```

---

