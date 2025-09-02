# Reset K Edges

## 题目描述

给你一棵由 $n$ 个点组成的编号为 $1 \sim n$ 的以 $1$ 为根的有根树，你可以进行 $k$ 次如下操作：

- 断开点 $u$ 与其父亲之间的边，并连接点 $1$ 与点 $u$。

定义树的高度为树上点的深度的最大值，点的深度为点到根的路径上经过的边的数量，问 $k$ 次操作后树的高度的最小值为多少。

## 说明/提示

对于 $100\%$ 的数据：

- $1 \le T \le 10^4$
- $2 \le n \le 2 \cdot 10^5,0 \le k \le n-1$
- $\forall i \in [2,n],1 \le p_i < i$
- 每组数据的 $n$ 的总和不超过 $2 \cdot 10^5$

## 样例 #1

### 输入

```
5
5 1
1 1 2 2
5 2
1 1 2 2
6 0
1 2 3 4 5
6 1
1 2 3 4 5
4 3
1 1 1```

### 输出

```
2
1
5
3
1```

# 题解

## 作者：Sycamore_Ma (赞：12)

## 题目链接
Educational Codeforces Round 136 (Rated for Div. 2), Problem D
[1739D Reset K Edges](https://codeforces.com/problemset/problem/1739/D)

## 题目大意
给定一棵有根树，节点数为 $n$，编号 $1, 2, \dots, n$，根节点编号为 $1$。题目保证 $i$ 节点的父节点编号 $p_i<i$。
给定 $k$ 轮树重构操作，每轮操作可选择一节点 $u$ 断开与父节点 $v$ 连接，点并将 $u$ 与其子树一并连接到根节点 $1$ 上，**即删边 $(v,u)$，增边 $(1,u)$**。
求最终能获得树的最小高度值（根节点高度记为 $0$）。

---
## 解法
### *最值边界二分*

> 较为典型的最大值最小化问题，只是操作对象变为了树的重构。

由于约束较少，优化方向发散，可以通过二分法夹逼树重构后合法的高度值，来获得最小高度值：
- 如测试高度 `mid` 可通过 $k$ 轮树重构操作达到，则更新最小高度 `ans` 答案，高度上界 `biggestHight` 收紧；
- 如测试高度 `mid` 不能通过 $k$ 轮树重构操作达到，则高度下界 `smallestHight` 收紧。

```cpp
int smallestHight = 1, biggestHight = n-1;
int mid;
int ans = n-1;

while (smallestHight <= biggestHight){
    mid = (smallestHight + biggestHight) / 2;
    if (check(mid) == true){
        ans = mid;
        biggestHight = mid - 1;
    }
    else{
        smallestHight = mid + 1;
    }
}
```

> 此过程花费时间复杂度 $O(\log_2n)$.

### *树的搜索与合法检验*
**自底而上（从叶至根）** 搜索整棵树，并在过程中维护 $i$ 号节点的历经的深度 `depth[i]`，并完成对应重构，统计达到测试高度值 $h$ 所需重构操作数 `cnt`，并查验所需操作数是否合法：
- 若向上维护过程中，节点 $i$ 的第 $j$ 个子节点 $v_j$ 累计历经深度达到测试高度值 $h$，则操作数 `cnt` 自加一，后续操作无需进行；

> 代表子节点 $v_j$ 已断开与 $i$ 号节点的连接，重新连接至 $1$ 号根节点，后续节点 $v_j$ 不再参与对父节点 $i$ 的历经深度值贡献。

- 否则更新节点 $i$ 的历经深度值，为所有未断开子节点中最大的历经深度值加一；
- 完成搜索后，若所需重构操作数 `cnt` 不超过题目规定范围 `k`，则测试高度值 `h` 可达。

```cpp
bool check(int h){
    for (int i = 1; i <= n; i ++){
        depth[i] = 1;
    }
    int cnt = 0;
    
    for (int i = n; i >= 2; i --){
        int s = a[i].son.size();
        for (int j = 0; j < s; j ++){
            int v = a[i].son[j];
            if (depth[v] == h){
                cnt ++;
                continue;
            }
            depth[i] = max(depth[v]+1, depth[i]);
        }
    }
    return cnt <= k;
}
```

> 由于题目保证 $i$ 节点的父节点编号 $p_i<i$，所以根据节点编号从后往前扫描即可完成树的遍历，无需递归。此过程由于每个节点仅会向父节点贡献至多一次，所以时间复杂度为 $O(n)$.

---
## 代码
### *易错点*
**不能自顶而下（从根至叶）** 维护整棵树，否则所需操作数不是最优，下图给出了一组反例：

![此问题中自顶而下重构树会使得操作数增多](https://img-blog.csdnimg.cn/450a24afc5a84f24a4625e87189976b8.png#pic_center)


```cpp
/*
    debug: from leaf to root V, from root to leaf X
*/
/*
int cnt;
bool check(int root, int h0, int h){
    bool ok = true;
    if (h0 > h){
        cnt --;
        h0 = 1;
    }
    if (cnt < 0){
        return false;
    }
 
    int s = a[root].son.size();
    for (int i = 0; i < s; i ++){
        int v = a[root].son[i];
        ok &= check(v, h0+1, h);
        if (!ok){
            return ok;
        }
    }
    return ok;
}
*/
```
### *AC代码*

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 200000 + 10;
struct node {
    vector<int> son;
}   a[maxn];
int n, k;

void init(){
    cin >> n >> k;
    for (int i = 1; i <= n; i ++){
        a[i].son.clear();
    }
    for (int i = 2; i <= n; i ++){
        int x;
        cin >> x;
        a[x].son.push_back(i);
    }
}

int depth[maxn];
bool check(int h){
    for (int i = 1; i <= n; i ++){
        depth[i] = 1;
    }
    int cnt = 0;
    
    for (int i = n; i >= 2; i --){
        int s = a[i].son.size();
        for (int j = 0; j < s; j ++){
            int v = a[i].son[j];
            if (depth[v] == h){
                cnt ++;
                continue;
            }
            depth[i] = max(depth[v]+1, depth[i]);
        }
    }
    
    return cnt <= k;
}


int main()
{
    int tt;
    cin >> tt;
    while (tt --){
        init();

        int smallestHight = 1, biggestHight = n-1;
        int mid;
        int ans = n-1;

        while (smallestHight <= biggestHight){
            mid = (smallestHight + biggestHight) / 2;
            // cnt = k;
            // root, h0, h
            // if(check(1, 0, mid)){

            if (check(mid) == true){
                ans = mid;
                biggestHight = mid - 1;
            }
            else{
                smallestHight = mid + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

> 算法时间复杂度为 $O(n\log_2n)$.

---

## 作者：Hisaishi_Kanade (赞：4)

高度是深度的最大值，那么这个东西本质就是最大值最小。

然后就是套路的二分答案，考虑如何 check。可以使用一个贪心的思路，从叶子往上去找，如果碰到某个点，其子树拍到根上面恰好深度是我们的答案那么直接把这个拍上去。这个贪心显然正确吧。

然后是考虑实现，其实因为你只需要维护一个子树深度，所以如果这颗子树拍了上去直接不用它更新父亲的深度即可。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
using ll=long long;
static const int Buf_size=1<<25;
static char _c; static int _x;
static const signed int base_10=10, zero(48), nine(57), flag_signed(45);
static char buf[Buf_size], *p1=buf, *p2=buf;
#define digit() (zero<=_c&&_c<=nine)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,Buf_size,stdin),p1==p2)?EOF:*p1++)
inline int read(){_x=0;_c=getchar();while(!digit()){_c=getchar();}while(digit()){_x=_x*10+(_c^zero);_c=getchar();}return _x;}
const int N=3e5+5, inf=2e9;
const ll illf=1e18;
int a[N], fa[N], dep[N];
vector<int> e[N];
int qt, n, i, j, k, res, mid;
inline const bool check(int x)
{
	rep(i, 1, n) dep[i]=1; res=0;
	req(i, n, 2)
	{
		for(auto nxt : e[i])
		{
			if(dep[nxt]==x) {++res; continue;}
			dep[i]=max(dep[i], dep[nxt]+1);
		}
	}
	return res<=k;
}
int main()
{
	scanf("%d", &qt);
	while(qt--)
	{
		rep(i, 1, n) vector<int>().swap(e[i]);
		n=read(); k=read(); rep(i, 2, n) fa[i]=read();
		rep(i, 2, n) e[fa[i]].emplace_back(i);
		int l=1, r=n;
		while(l<r)
		{
			mid=l+r>>1;
			if(check(mid)) r=mid;
			else l=mid+1;
		}
		printf("%d\n", r);
	}
}

```

---

## 作者：_sunkuangzheng_ (赞：2)

二分答案，考虑如何 check。

从根到儿子贪心，找到第一个深度 $> mid$ 的点断开是显然错误的，考虑深度为 $mid$ 的点下挂了很多儿子，此时直接在 $mid$ 处断最优。

我们从下向上贪心，如果该点深度不满足要求，那么断开其 $mid-1$ 级祖先。倍增维护树上 $k$ 级祖先，线段树 + dfn 序判断点是否已经断开，时间复杂度 $\mathcal O(n \log^2 n)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 26.10.2023 07:29:57
**/
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int T,n,k,d[N],a[N],fa[N][22],t[N*4],p[N],siz[N],dfn[N],tot;vector<int> g[N];
bool cmp(int x,int y){return d[x] > d[y];}
int kfa(int u,int k){
    for(int i = 20;i >= 0;i --) if((k >> i) & 1) u = fa[u][i];
    return u; 
}void upd(int s,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr) return t[s] = 1,void();
    int mid = (l + r) / 2;
    if(ql <= mid) upd(s*2,l,mid,ql,qr); if(qr > mid) upd(s*2+1,mid+1,r,ql,qr);
}int qry(int s,int l,int r,int x){
    if(l == r) return t[s];
    int mid = (l + r) / 2,ans = t[s];
    if(x <= mid) return ans | qry(s*2,l,mid,x);
    else return ans | qry(s*2+1,mid+1,r,x);
}bool ck(int x){
    int sm = 0,u = 0;
    for(int i = 1;i <= 4 * n;i ++) t[i] = 0;
    for(int i = 1;i <= n;i ++) if(!qry(1,1,n,dfn[p[i]]) && d[p[i]] > x)
        u = kfa(p[i],x - 1),sm ++,upd(1,1,n,dfn[u],dfn[u] + siz[u] - 1);
    return sm <= k;
}void dfs(int u){
    dfn[u] = ++tot,siz[u] = 1;
    for(int v : g[u]) dfs(v),siz[u] += siz[v];
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> T;
    while(T --){
        cin >> n >> k,tot = 0;
        for(int i = 1;i <= n;i ++) p[i] = i,g[i].clear();
        for(int i = 2;i <= n;i ++) cin >> fa[i][0],d[i] = d[fa[i][0]] + 1,g[fa[i][0]].push_back(i);
        sort(p+1,p+n+1,cmp),dfs(1);
        for(int j = 1;j <= 20;j ++) for(int i = 1;i <= n;i ++) fa[i][j] = fa[fa[i][j-1]][j-1];
        int l = 1,r = n - 1;
        while(l <= r){
            int mid = (l + r) / 2;
            if(ck(mid)) r = mid - 1; else l = mid + 1;
        }cout << r + 1 << "\n";
    }
}
```

---

## 作者：SamHJD (赞：2)

## [CF1739D Reset K Edges](https://www.luogu.com.cn/problem/CF1739D)

### 题目大意

在树上操作 $k$ 次，每次选择一个点，将以这个点为根的子树从当前位置移开并连向树根 $1$，问 $k$ 次操作后树的最深节点深度最小是多少。

### 解法

二分最深节点的深度 $mid$。

对于一棵以 $s$ 为根的子树，若其最深的叶子节点 $s_x$ 能通过割这棵子树满足最深限制，则其他点均能满足，并将其称为是可以割的子树。

若一棵子树 $s$ 是可以割的子树，其内部也有一棵可以割的子树 $t$，那么优先割 $s$。因为 $s$ 包含 $t$，肯定 $dep_{s_x}\ge dep_{t_x}$。

在代码中，深度数组 $dep_i$ 实际上表示的是 $dep_i-dep_{i_s}+1$，即 $i$ 到以它为根的子树的深度最大点的距离。

根据上述条件，搜索中应从根向叶子搜，才能满足优先割最大的能割的子树。判断 $dep_u$ 等于 $mid$ 时，这棵子树的最深的点割完后恰好深度为 $mid$，满足条件，注意树根和第二层节点的子树不割，因为没用。

割完一棵子树后，将其 $dep$ 设为 $0$，深搜返回计算上一层 $dep$ 时便不会记录这棵子树的信息，也就相当于删去这棵子树。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int T,f[N],head[N],ecnt,dep[N],cnt,n,k;
struct E{
	int v,next;
}e[N];
void add(int u,int v){
	e[++ecnt]={v,head[u]};
	head[u]=ecnt;
}
void dfs(int u,int mid){
	dep[u]=1;//初始为1，叶子节点到自己距离为1
	for(int i=head[u];i;i=e[i].next){
		dfs(e[i].v,mid);//先处理下一层
		dep[u]=max(dep[u],dep[e[i].v]+1);//更新，由于到下一层的每个节点距离都是1
	}
	if(f[u]!=1 && dep[u]==mid){//可以割
		dep[u]=0;
		cnt++;
	}
}
bool ck(int mid){
	cnt=0;
	dfs(1,mid);
	if(cnt<=k) return 1;
	else return 0;
}
void solve(){
	scanf("%d%d",&n,&k);
	ecnt=0;for(int i=1;i<=n;++i) head[i]=0;
	f[1]=1;
	for(int i=2;i<=n;++i){
		scanf("%d",&f[i]);
		add(f[i],i);
	}
	int l=1,r=n;
	while(l<=r){
		int mid=(l+r)>>1;
		if(ck(mid)) r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",l);
}
int main(){
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：luo_shen (赞：1)

### 题意描述
给定一棵大小为 $n$ 的树，可以进行 $k$ 次操作，每次操作将以 $x$ 为根的子树从树割下，并接到 $1$ 号节点下，作为 $1$ 号节点的子树。问经过 $k$ 次操作后，所有节点中深度最大的节点的深度最小为多少。
### 题目分析
看到最大值最小，马上想到二分，问题在于如何写 $check$ 函数。对于在树上二分，一般有两种写法：从根节点到叶节点，从叶节点到根节点。这里如果从根到叶，明显答案会增加。
#### Hack 
```
1 2
2 3
3 4
4 5
3 6
6 7
7 8
7 9
```
对于这棵树，要使其最大深度为 $2$,从根到叶扫需要 $4$ 次操作，从叶往根扫只需要 $3$ 次操作。

所以我二分出一个答案 $x$ 后，考虑如果以某个点为根的子树中有一个叶子节点深度大于等于 $x$，且该节点不为 $1$ 号点子节点（割了和没割一个样），则把这棵子树割下来。
### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
    int s=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=s*10+(ch-'0');
        ch=getchar();
    }
    return s*f;
}
int n,dep[200100],k,mx,ans,fa[200100];
vector<vector<int> >e;
void dfs(int x) {
    dep[x]=1;
    for(auto y:e[x]){
        dfs(y);
        dep[x]=max(dep[x],dep[y]+1);
    }
    if(x!= 1&&fa[x]!=1&&dep[x]==mx){
        dep[x]=0;
        ++ans;
    }
}
bool check(int mid) {
  ans=0;
  mx=mid;
  dfs(1);
  return ans<=k;
}
void solve(){
    n=read(),k=read();
    e.clear();
    e.resize(n+10);
    for(int i=1;i<=n;i++){
        e[i].clear();
    }
    for(int i=2;i<=n;i++){
        fa[i]=read();
        e[fa[i]].push_back(i);
    }
    int l=1,r=n-1,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    printf("%lld\n",ans);
}
signed main(){
    // freopen("1.out","w",stdout);
    int t;
    t=read();
    while(t--){
        solve();
    }
    return 0;
}
```

---

## 作者：Masna_Kimoyo (赞：0)


看完题目，很显然有个单调性。当深度越大时，越难以满足条件。

所以二分一个最小答案。

现在已经确定了最后的深度，接下来难点就在 `check` 函数。

对于当前深度，我们可以求出代价 $res$ 。

现在要想让代价最小，那就要想一个贪心策略。

具象化一些，题目说将一个点的父亲变为根节点，其实可以想象为断开了当前点连父亲的边。那么现在的目的就是求设计的最小的断点数量。

## 实现方法 1

考虑叶子节点一定会在其上方第 $x$ 个点的连父亲边设计一个断点，而中间所经过的点都满足了条件，为了方便，可以打一个标记。

更加普遍化一些，深度更浅的点先更新，然后是深度深的，那么深度深的点就可能在更新时受到不必要的的影响。所以肯定深度深的优先更新。排序即可。

最后一个个向上更新即可，将上方 $x$ 个点更新，如果碰到已经有更新的了，就说明这一段都不需要切了，都已经满足了条件。

注意，深度本身小于等于 $res$ 的点不需要管，因为本身就满足条件，而题目给的样例告诉我们，根节点 $1$ 的深度其实是 $0$ ，所以初始化的时候千万不要把 $1$ 的深度设为 $1$

## code

```cpp
#include<bits/stdc++.h>
#define printlf(x) print(x),putchar('\n')
#define printsp(x) print(x),putchar(' ')
using namespace std;
inline int read(){
    int x=0;
    bool w=0;
    char c=getchar();
    while(!isdigit(c))  w|=c=='-',c=getchar();
    while(isdigit(c))   x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return w?-x:x;
}
inline void print(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) print(x/10);
    putchar('0'+x%10);
}
const int N=2e5+5;
struct edge{
    int to,nxt;
}Edge[N<<1];
struct node{
    int num,dep;
}p[N];
inline bool cmp(node a,node b){
    return a.dep>b.dep;
}
int head[N],vis[N],fa[N],deg[N];
int n,k,tot;
inline void add(int u,int v){
    Edge[++tot].to=v;
    Edge[tot].nxt=head[u];
    head[u]=tot;
}
inline void dfs(int x,int fa){
    p[x].dep=p[fa].dep+1;
    for(register int i=head[x];i;i=Edge[i].nxt){
        int v=Edge[i].to;
        if(v==fa)   continue;
        dfs(v,x);
    }
}
inline bool check(int x){
    memset(vis,0,sizeof(vis));
    int res=0;
    for(register int i=2;i<=n;++i){
        int s=p[i].num;
        if(p[i].dep<=x) continue;
        ++res;
        int now=s;
        for(register int i=1;i<=x;++i){
            if(vis[now]){
                --res;
                break;
            }
            vis[now]=1;
            now=fa[now];
        }
    }
    return res<=k;
}
inline int Solve(){
    n=read(),k=read();
    tot=0;
    memset(deg,0,sizeof(deg));
    memset(head,0,sizeof(head));
    for(register int i=2;i<=n;++i){
        fa[i]=read(),p[i].num=i;
        add(fa[i],i),add(i,fa[i]);
        deg[fa[i]]++,deg[i]++;
    }
    p[0].dep=-1;
    dfs(1,0);
    sort(p+2,p+n+1,cmp);
    int l=1,r=n,ans=0;
    while(l<=r){
        int mid=l+r>>1;
        //cout<<l<<' '<<r<<' '<<mid<<" lrmid\n";
        if(check(mid))  r=mid-1,ans=mid;
        else    l=mid+1;
    }
    return ans;
}
signed main(){
    int T=read();
    while(T--){
        printlf(Solve());
    }
    return 0;
}

```

## 实现方法 2

这个还没有写，玛丽太差，但还是可以讲一下。。

考虑对于每一条单链，其割断方法一定是固定的，一个个来即可，直到剩下的不能单独割出来为止（割到了不是单链上的点，度数不为 $2$）。

剩下的那些点的数量可以作为一个贡献传递给交点 （度数不为 $2$ 的），那么对于这些大小不同且都不超过深度 $x$ 的贡献，取一个最大值 $maxx$ 后，在交点的上方 $x-maxx$ 处又可以割一次，剩下的贡献又传递给深度更浅的上一个交点，如此往复，最后得到答案。

注意的东西同上。



---

