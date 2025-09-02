# The Game (Easy Version)

## 题目描述

这是该问题的简单版本。与困难版本的区别在于，此版本只需找到 Cirno 可能选择的一个可行节点即可获胜。仅当解决所有版本的问题时方可进行 hack。

Cirno 和 Daiyousei 正在玩一个以节点 $1$ 为根的 $n$ 节点树 $^{\text{∗}}$ 游戏，其中第 $i$ 个节点的权值为 $w_i$。她们轮流行动，Cirno 先手。

每一轮中，假设对手在上轮选择了节点 $j$，当前玩家必须选择一个未被删除的节点 $i$ 满足 $w_i > w_j$，并删除节点 $i$ 的子树 $^{\text{†}}$。特别地，在第一轮中 Cirno 可以选择任意节点并删除其子树。

无法操作的玩家获胜，双方都希望自己获胜。请找出 Cirno 在第一轮可能选择的任意一个节点，使得在双方都采取最优策略时她能获胜。

$^{\text{∗}}$ 树是一个无环的连通图。

$^{\text{†}}$ 若从根节点 $1$ 到节点 $u$ 的所有路径都必须经过节点 $i$，则称节点 $u$ 属于节点 $i$ 的子树。

## 说明/提示

第一个测试用例：
1. 若 Cirno 在第一轮选择节点 $1$ 或 $3$，Daiyousei 无法操作，因此 Daiyousei 获胜。
2. 若 Cirno 在第一轮选择节点 $2$ 或 $4$，Daiyousei 只能选择节点 $3$，操作后 Cirno 无法行动，因此 Cirno 获胜。

因此 Cirno 可能选择的节点为 $2$ 和 $4$。

第二个测试用例中，无论 Cirno 选择哪个节点，Daiyousei 都无法操作，因此 Daiyousei 获胜。

第三和第四个测试用例中，Cirno 唯一可能选择的节点是 $2$。

第五个测试用例中，Cirno 可能选择的节点为 $3,4,6,7$ 和 $10$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
4
2 2 4 3
1 2
1 3
2 4
5
1 2 3 4 5
1 2
2 3
3 4
4 5
3
1 2 3
1 2
1 3
5
3 1 3 4 5
1 2
2 3
3 4
4 5
10
1 2 3 2 4 3 3 4 4 3
1 4
4 6
7 4
6 9
6 5
7 8
1 2
2 3
2 10```

### 输出

```
2
0
2
2
10```

# 题解

## 作者：liyifan202201 (赞：4)

## 思路
1. 我们可以考虑如何必败
> 可以证明，若此时子树外无大于 $w_u$ 的，就会必败

2. 所以很容易得出，要选择一个最大的 $w_i$ 值且若此时子树外无大于 $w_i$，`Cirno` 就可以在第一轮获胜。

## 做法
我们可以使用一个 `dfn`，通过求取一个最大的 $\max(\max ( \{ in_1,in_2, \dots,in_x\} ),\max ( \{ out_1,out_2, \dots,out_x\} )) > w_x$，即可。

我们可以使用线段树来维护求最大值，时间复杂度为 $ 
O(n \log n)$，可以通过。

```
#include<bits/stdc++.h>
#define int long long
#define lr ro*2
#define rr ro*2+1
#define mid (l+r)/2
using namespace std;
const int N=5e6+20; // 最大节点数
// 节点的结构体，保存节点的值和编号
struct node{
    int x,y;
};
node a[N]; // 存储所有节点的值和编号
vector<int>g[N]; // 邻接表，存储树的边
int in[N],out[N],T,id[N]; // DFS遍历时的时间戳，in和out用于记录节点的子树范围
void dfs(int x,int fa){
    in[x]=++T; // 记录进入节点的时间
    id[T]=x;   // 记录进入时间对应的节点编号
    for(auto y:g[x]){ // 遍历邻接节点
        if(y==fa) continue; // 如果是父节点，跳过
        dfs(y,x); // 递归DFS
    }
    out[x]=T; // 记录退出节点的时间
}
int tr[N]; // 线段树数组
int n;
// 线段树合并操作，取区间最大值
void push_up(int ro){
    tr[ro]=max(tr[lr],tr[rr]);
}
// 线段树建树操作
void build(int ro=1,int l=1,int r=n){
    if(l==r){ // 叶子节点
        tr[ro]=a[id[l]].x; // 设置线段树叶子节点的值
        return;
    }
    build(lr,l,mid); // 递归建左子树
    build(rr,mid+1,r); // 递归建右子树
    push_up(ro); // 合并左右子树
}
// 查询区间[L,R]的最大值
int query(int L,int R,int ro=1,int l=1,int r=n){
    if(L>R) return 0; // 无效查询，返回0
    if(L<=l and r<=R) // 当前区间完全包含在查询区间内
        return tr[ro];
    int maxn=0;
    if(L<=mid){
        maxn=query(L,R,lr,l,mid); // 查询左子树
    }
    if(R>mid){
        maxn=max(maxn,query(L,R,rr,mid+1,r)); // 查询右子树，取最大值
    }
    return maxn;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int t;
    cin>>t; // 读取测试用例数
    while(t--){ // 对每个测试用例进行处理
        cin>>n; // 读取节点数
        for(int i=1;i<=n;i++){ // 读取每个节点的值
            g[i].clear(); // 清空邻接表
            cin>>a[i].x; // 读取节点值
            a[i].y=i; // 记录节点编号
        }
        for(int i=1;i<n;i++){ // 读取树的边
            int u,v;
            cin>>u>>v;
            g[u].push_back(v); // 建立双向边
            g[v].push_back(u);
        }
        T=0;
        dfs(1,-1); // 从根节点1开始DFS遍历，计算时间戳
        build(); // 建立线段树

        bool f=0;
        int ans=0;
        for(int i=1;i<=n;i++){ // 遍历所有节点
            // 如果可以找到一个节点，它的值大于其子树外的最大值，且它的值更大，则是可能的答案
            if(max(query(1,in[a[i].y]-1),query(out[a[i].y]+1,n))>a[i].x and a[ans].x<a[i].x){
                f=1; // 标记找到答案
                ans=i; // 记录该节点
            }
        }
        if(f==0)
            cout<<0<<endl; // 如果没有找到答案，输出0
        else cout<<ans<<endl; // 输出找到的节点编号
    }   
    return 0;
}

```

---

## 作者：_Kenma_ (赞：2)

## 前言

推销博客：[here.](https://www.cnblogs.com/Kenma/p/18697012)

## 正文

经过手玩样例发现，对于 $x$，如果存在 $y$ 不在 $x$ 子树内且 $w_y > w_x$，此时 $w_x$ 最大的 $x$ 一定是必胜点。

原因是，这样的 $x$ 满足，无论后手操作任意 $y$，先手都无法再次操作。

考虑用反证法证明。

假设操作完 $x$ 后，依然存在两点 $y,z$，使得后手操作 $y$ 后，先手依然可以操作 $z$，不难发现 $w_y<w_z$。

考虑分类讨论：

- 如果 $y,z$ 存在子孙关系，那么只能是 $y$ 是 $z$ 的祖先，否则 $x$ 不是 $w_x$ 最大的点，$y$ 才是。而如果 $y$ 是 $z$ 的祖先，那么操作完 $y$ 后无法再操作 $z$，矛盾；

- 如果 $y,z$ 不存在子孙关系，那么 $y$ 一定可以取代 $x$ 成为点权最大的点，矛盾。

所以，我们的结论是正确的。

实现上，可以用树状数组记录不同点权点的出现次数，在 dfs 的过程中差分即可。

总体复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,x,y,ans,a[400005],b[400005],c[400005],dfn[400005];
int head[400005],nxt[800005],target[800005],tot;
void add(int x,int y){
	tot++;
	nxt[tot]=head[x];
	head[x]=tot;
	target[tot]=y;
}
bool cmp(int x,int y){
	return a[x]>a[y];
}
#define lowbit(i) (i&(-i))
void modify(int x,int k){
	for(int i=x;i<=n;i+=lowbit(i)){
		c[i]+=k;
	}
}
int query(int x){
	int ans=0;
	for(int i=x;i;i-=lowbit(i)){
		ans+=c[i];
	}
	return ans;
}
void dfs(int x,int fa){
	int now=query(n)-query(a[x]);
	modify(a[x],1);
	for(int i=head[x];i;i=nxt[i]){
		int y=target[i];
		if(y==fa) continue;
		dfs(y,x); 
	}
	if(b[x]==query(n)-query(a[x])-now) b[x]=0;
	else b[x]=1;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			modify(a[i],1);
			dfn[i]=i;
		}
		for(int i=1;i<=n;i++){
			b[i]=query(n)-query(a[i]);
		}
		for(int i=1;i<n;i++){
			cin>>x>>y;
			add(x,y);
			add(y,x);
		}
		dfs(1,0);
		sort(dfn+1,dfn+1+n,cmp);
		for(int i=1;i<=n;i++){
			if(b[dfn[i]]){
				ans=dfn[i];
				break;
			}
		}
		cout<<ans<<'\n';
		ans=tot=0;
		for(int i=1;i<=n;i++){
			head[i]=b[i]=c[i]=0;
		}
	}
	return 0;
}
```

---

## 作者：_abcd_ (赞：2)

## [[CF2062E1] The Game (Easy Version)](https://codeforces.com/problemset/problem/2062/E1)

注意到如果对于某个点 $ x $，所有权值比 $ x $ 大的点都在他的子树内，那么删掉 $ x $ 后就无法操作了。因此考虑按权值从大到小扫一遍，如果扫到了 $ x $，说明所有权值比 $ x $ 大的点都是先手必输的，那么如果 $ x $ 并不满足一开始说的那个条件，则删掉 $ x $ 后再操作任意的点都一定是先手必输的，因此输出 $ x $ 即可。条件的判定可以用 $ \rm BIT $ 实现，复杂度 $ O(n \log n) $。

---

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pn putchar('\n')
#define mset(a,x) memset(a,x,sizeof a)
#define mcpy(a,b) memcpy(a,b,sizeof a)
#define all(a) a.begin(),a.end()
#define fls() fflush(stdout)
using namespace std;
int re()
{
    int x=0;
    bool t=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
        t=ch=='-'?0:t,ch=getchar();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return t?x:-x;
}
const int maxn=4e5+5;
void gx(int &x,int y)
{
    x=max(x,y);
}
void gn(int &x,int y)
{
    x=min(x,y);
}
int n,idx;
int id[maxn],rid[maxn];
vector<int>a[maxn];
vector<int>e[maxn];
int tree[maxn];
void add(int x,int ad)
{
    for(int i=x;i<=n;i+=i&-i)
        tree[i]+=ad;
}
int qry(int x)
{
    int ret=0;
    for(int i=x;i;i-=i&-i)
        ret+=tree[i];
    return ret;
}
int qry(int l,int r)
{
    return qry(r)-qry(l-1);
}
void dfs(int pos,int fa)
{
    id[pos]=++idx;
    for(int v:e[pos])
    {
        if(v==fa)
            continue;
        dfs(v,pos);
    }
    rid[pos]=idx;
}
void solve()
{
    n=re();
    for(int i=1;i<=n;i++)
    {
        tree[i]=0;
        a[i].clear();
        e[i].clear();
    }
    int mx=0;
    for(int i=1;i<=n;i++)
    {
        int x=re();
        gx(mx,x);
        a[x].push_back(i);
    }
    for(int i=1;i<n;i++)
    {
        int u=re(),v=re();
        e[u].push_back(v);
        e[v].push_back(u);
    }
    idx=0;
    dfs(1,0);
    int cnt=0;
    for(int i:a[mx])
    {
        cnt++;
        add(id[i],1);
    }
    for(int i=mx-1;i;i--)
    {
        for(int j:a[i])
        {
            if(qry(id[j],rid[j])<cnt)
            {
                printf("%d\n",j);
                return;
            }
        }
        for(int j:a[i])
        {
            cnt++;
            add(id[j],1);
        }
    }
    puts("0");
}
signed main()
{
    int T=re();
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：dayz_break404 (赞：2)

简单博弈论。

将点从大到小排序，显然取最大的点是先手必败态，考虑从最大的点向小的递推胜负状态。

由于题目要求我们输出一个先手必胜的节点即可，不妨假设我们输出的是符合条件的值最大的那个点。这样有什么好处呢，显然如果存在 $u$ 的子树外的节点最大值小于等于 $u$ 的值，$u$ 一定是先手必败态，那么我们只需要找到满足除它的子树之外还有比他更大的点的值最大的那个点即可，因为选了这个点之后剩余的点一定转给对手先手必败态，Cirno 就赢了。

dfn 序加前后缀最大值维护即可，但是我傻傻地写了一个 st 表。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
const int maxn=4e5+20;
int t,n,a[maxn],dfn[maxn],st[maxn][24],tot,siz[maxn];
struct node{
	int val,id;
}rec[maxn];
inline bool cmp(node x,node y){
	return x.val>y.val;
}
vector<int> e[maxn];
void dfs(int u,int fa){
	dfn[u]=++tot,siz[u]=1;
	for(int v:e[u]){
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
}
struct DS{
	inline void init(){
		for(int i=1;i<=n;i++) st[dfn[i]][0]=a[i];
		for(int i=1;i<=20;i++) for(int j=1;j<=n-(1<<i)+1;j++) st[j][i]=max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
	}
	inline int ask(int x,int y){
		if(x>y) return 0;
		int k=log2(y-x+1);
		return max(st[x][k],st[y-(1<<k)+1][k]);
	}
}S;
inline int check(int x){
	int now=rec[x].id,lim=max(S.ask(1,dfn[now]-1),S.ask(dfn[now]+siz[now],n));
	return lim>rec[x].val;
}
inline void solve(){
	n=read(),tot=0;
	for(int i=1;i<=n;i++) a[i]=read(),e[i].clear(),rec[i]={a[i],i};
	int u,v;sort(rec+1,rec+1+n,cmp);
	for(int i=1;i<n;i++) u=read(),v=read(),e[u].push_back(v),e[v].push_back(u);
	dfs(1,0),S.init();
	for(int i=1;i<=n;i++) if(check(i)) return printf("%d\n",rec[i].id),void();
	printf("0\n");
}
int main(){
	t=read();
	while(t--) solve();
	return 0;
}
```

---

## 作者：Ray662 (赞：2)

很简单。

设所有点的 $w$ 的集合为 $\{W_1, W_2, \cdots, W_m\}$。

输出 $w$ 最大的 $u$（$w_u = W_x$）满足：$\exist v, w_v = W_{x + 1}$，使得 $u, v$ 不存在祖孙关系。

为什么？先手操作了这样的 $u$ 以后，无论后手下一步如何操作，下一次轮到先手时他一定无法做任何事情。

因为这个 $v$ 无法成为答案，一定不满足上面的性质。所以 $v$ 是所有 $w_p > W_{x + 1}$ 的点 $p$ 的祖先。这也导致了后手无论选什么，都会把所有 $w$ 值大于他的全部删去。那先手自然赢了。

考虑如何实现。考虑枚举 $x$，我们需要支持一个数据结构，把 $w_u = W_x$ 的标记为 $1$，然后求一棵子树内标记个数是不是等于某个定值。BIT 或 SGT 均可。

说的不是很清楚。[Code](https://codeforces.com/contest/2062/submission/303121132)。

---

## 作者：shicj (赞：0)

如果存在 $u$ 不在 $v$ 的子树内且 $w_u>w_v$，则最大的 $v$ 一定是可行的点。

此时，选择了这个点后，对方将无法选出一个点使得消除后剩下的点大于选择的点，因此可行。如果选择不出这样一个点，则无解。

首先想到枚举 $v$，并要求在 $O(\log n)$ 时间内完成判断。看到这个时间复杂度以及最大值，我想到的是线段树（BIT 也可以的）。

为了实现查询，要想办法使得区间连续，为了实现这个目标，可以使用 DFS 序，令其为 $dfn$，这时查询的最大值可以分成 $dfn$ 中的两段，前一段是 $[1,dfn_v]$，为了描述后一段，定义当前节点 $v$ 的子树中 $dfn$ 最大的点的下一个点为 $nxt_v$，于是第二段为 $[nxt_v,n]$，$nxt$ 的求法可以在 DFS 中完成，详见代码。

> 提示：注意可能取到空区间，线段树中注意判断！

[code](https://codeforces.com/problemset/submission/2062/305808964)

---

