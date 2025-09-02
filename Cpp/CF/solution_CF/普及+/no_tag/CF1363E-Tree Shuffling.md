# Tree Shuffling

## 题目描述

Ashish has a tree consisting of $ n $ nodes numbered $ 1 $ to $ n $ rooted at node $ 1 $ . The $ i $ -th node in the tree has a cost $ a_i $ , and binary digit $ b_i $ is written in it. He wants to have binary digit $ c_i $ written in the $ i $ -th node in the end.

To achieve this, he can perform the following operation any number of times:

- Select any $ k $ nodes from the subtree of any node $ u $ , and shuffle the digits in these nodes as he wishes, incurring a cost of $ k \cdot a_u $ . Here, he can choose $ k $ ranging from $ 1 $ to the size of the subtree of $ u $ .

He wants to perform the operations in such a way that every node finally has the digit corresponding to its target.

Help him find the minimum total cost he needs to spend so that after all the operations, every node $ u $ has digit $ c_u $ written in it, or determine that it is impossible.

## 说明/提示

The tree corresponding to samples $ 1 $ and $ 2 $ are:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1363E/7a89fb5868f7e2cc9a5cf05da12869789d228775.png)In sample $ 1 $ , we can choose node $ 1 $ and $ k = 4 $ for a cost of $ 4 \cdot 1 $ = $ 4 $ and select nodes $ {1, 2, 3, 5} $ , shuffle their digits and get the desired digits in every node.

In sample $ 2 $ , we can choose node $ 1 $ and $ k = 2 $ for a cost of $ 10000 \cdot 2 $ , select nodes $ {1, 5} $ and exchange their digits, and similarly, choose node $ 2 $ and $ k = 2 $ for a cost of $ 2000 \cdot 2 $ , select nodes $ {2, 3} $ and exchange their digits to get the desired digits in every node.

In sample $ 3 $ , it is impossible to get the desired digits, because there is no node with digit $ 1 $ initially.

## 样例 #1

### 输入

```
5
1 0 1
20 1 0
300 0 1
4000 0 0
50000 1 0
1 2
2 3
2 4
1 5```

### 输出

```
4```

## 样例 #2

### 输入

```
5
10000 0 1
2000 1 0
300 0 1
40 0 0
1 1 0
1 2
2 3
2 4
1 5```

### 输出

```
24000```

## 样例 #3

### 输入

```
2
109 0 1
205 0 1
1 2```

### 输出

```
-1```

# 题解

## 作者：fighter (赞：10)

这个E题怎么比D简单啊……

首先考虑一个节点，显然他的子树中的操作都可以由他的祖先来完成。所以如果他的祖先里有比他花费更小的，那么这个节点就没啥用了。

所以为了方便，我们先把每个节点的花费和祖先取min， 然后我们就可以贪心地完成子树中所有能够完成的操作了。

我们分别记录位置不对的0和1的个数，每次操作选出0,1中错误个数较小的一个，进行重新排列即可。

```cpp
#include <bits/stdc++.h>
#define MAX 500005
#define ll long long
using namespace std;

int n, cnt;
int head[MAX], vet[MAX], Next[MAX], b[MAX], c[MAX], s[MAX][2];
ll a[MAX], ans;

void add(int x, int y){
    cnt++;
    Next[cnt] = head[x];
    head[x] = cnt;
    vet[cnt] = y;
}

void dfs(int x, int fa){
    if(x != 1) a[x] = min(a[x], a[fa]);
    s[x][b[x]] += (b[x]!=c[x]);
    for(int i = head[x]; i; i = Next[i]){
        int v = vet[i];
        if(v == fa) continue;
        dfs(v, x);
        s[x][0] += s[v][0], s[x][1] += s[v][1];
    }
    int t = min(s[x][0], s[x][1]);
    ans += a[x]*t*2;
    s[x][0] -= t, s[x][1] -= t;
}

int main()
{
    cin >> n;
    int s1 = 0, s2 = 0;
    for(int i = 1; i <= n; i++){
        scanf("%lld%d%d", &a[i], &b[i], &c[i]);
        s1 += b[i], s2 += c[i];
    }

    int x, y;
    for(int i = 1; i < n; i++){
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
    }
    if(s1 != s2){
        puts("-1");
        return 0;
    }
    dfs(1, 0);
    cout << ans << endl;

    return 0;
}
```

---

## 作者：louhao088 (赞：1)

我们发现，在一个节点处进行操作等价于在它的祖先处进行操作。

于是我们就有一个想法：将每一个节点的费用改成从它到根的路径上点的费用的最小值。

然后我们发现，在深度深的节点处操作肯定比在深度浅的节点处操作更优，证明显然。

那么直接一遍 dfs，在尽量深的节点处操作，最后计算总费用输出即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	char ch=getchar();int x=0;bool f=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
const int maxn=200005;
struct tr
{
	int v,nex;
}e[maxn*2];
struct node
{
	int sum1,val,sum2;
}a[maxn],d[maxn];
int n,b,c,x,y,num=0,num1=0,cnt=0,head[maxn],f[maxn],ans=0,num5=0;
void add(int x,int y)
{
	e[++cnt].v=y,e[cnt].nex=head[x],head[x]=cnt;
}
void dfs(int u,int fa)
{
	//cout<<u<<" "<<fa<<endl;
	if(f[u]==1)a[u].sum1++;
	if(f[u]==2)a[u].sum2++;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(e[i].v==fa)continue;
		dfs(v,u);
		a[u].sum1+=a[v].sum1;
		a[u].sum2+=a[v].sum2;
		d[u]=a[u];
	}
}
void dfs1(int u,int fa,int mi)
{
	if(mi<a[u].val)a[u].val=min(mi,a[u].val);
	if(a[u].sum1<1||a[u].sum2<1)return;
	if(a[u].sum1>=1&&a[u].sum2>=1)
	{
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(e[i].v==fa)continue;
			dfs1(v,u,a[u].val);
			a[u].sum1-=min(d[v].sum1,d[v].sum2);
			a[u].sum2-=min(d[v].sum1,d[v].sum2);
		}
		ans+=a[u].val*min(a[u].sum1,a[u].sum2)*2;
		//num5=num5+min(a[u].sum1,a[u].sum2)*2;
		return;

	}
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i].val=read(),b=read(),c=read();	
		if(b>c)num++,f[i]=1;
		else if(b<c)num1++,f[i]=2;
		else f[i]=0;	
	}
	if(num!=num1)cout<<"-1",exit(0);
	for(int i=1;i<n;i++)
	{
		x=read(),y=read();
		add(x,y),add(y,x);
	}
	dfs(1,0);
	dfs1(1,0,a[1].val);
	cout<<ans;
	return 0;
}
```


---

## 作者：Polaris_Dane (赞：1)

只要需要$1$的数量和已有的$1$数量相等即可

首先，一个点如果已经满足了要求，就不会变第二次

我们求出来每个点子树内匹配的组数，搬上线段树

然后按照$k$排序，从小到大，每次将所选点子树内所有可配对的点全部配对

并用树剖修改祖先子树内配对权值，用树状数组在子树内打一个标记

如果顺序访问时一个点已被标记，说明其子树内已经没有配对的点了

貌似做麻烦了（但是当时想的啥就是啥了

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<set>
#include<queue>
#define M 201000
#define inf 0x3f3f3f3f
#define LL long long
const double eps=1e-6;
const int mod=988244353;
using namespace std;
inline int read(){
	int f=1,x=0;char s=getchar();
	while (!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while (isdigit(s)){x=(x<<1)+(x<<3)+(s^48),s=getchar();}
	return x*f;
}
int n,m,head[M],cnt,col[M],w1,w2,val[M];
LL ans;
struct node{
	int b,c,v,id;
	bool operator <(const node&a)const{
		return v<a.v;	
	}
}p[M];
struct edge{int to,nxt;}e[M<<1];
inline void add_edge(int u,int v){e[++cnt].nxt=head[u],head[u]=cnt,e[cnt].to=v;} 
int dep[M],fa[M],top[M],son[M],siz[M],id[M],ref[M],tot;
int sum[M<<2],tag[M<<2];
int t[M],tt[M];
inline int lowbit(int x){return x&-x;}
inline void change(int a,int x){while (a<=n) t[a]+=x,a+=lowbit(a);}
inline int get_val(int a){int ans=0;while (a>0) ans+=t[a],a-=lowbit(a);return ans;}
inline void update(int rt){sum[rt]=sum[rt<<1]+sum[rt<<1|1];}
inline void push_down(int rt){
    sum[rt<<1]+=tag[rt],sum[rt<<1|1]+=tag[rt];
    tag[rt<<1]+=tag[rt],tag[rt<<1|1]+=tag[rt],tag[rt]=0;    
}
inline void build(int rt,int l,int r){
    int mid=(l+r)>>1;
    if (l==r){return void(sum[rt]=val[ref[l]]);}
    build(rt<<1,l,mid),build(rt<<1|1,mid+1,r);
    update(rt);
}
inline void modify(int rt,int l,int r,int x,int y,int v){
    if (x<=l&&y>=r){
        sum[rt]+=v,tag[rt]+=v;
        return;
    }
    push_down(rt);
    int mid=(l+r)>>1;
    if (x<=mid) modify(rt<<1,l,mid,x,y,v);
    if (y>mid) modify(rt<<1|1,mid+1,r,x,y,v);
    update(rt);
}
inline int query(int rt,int l,int r,int x){
	if (l==r) return sum[rt];
	push_down(rt);
	int mid=(l+r)>>1;
	if (x<=mid) return query(rt<<1,l,mid,x);
	else return query(rt<<1|1,mid+1,r,x);	
}
inline void dfs1(int rt,int f){
    fa[rt]=f,siz[rt]=1;
    if (p[rt].b!=p[rt].c) col[rt]+=(p[rt].b?1:-1);
    else tt[rt]++;
    for (int i=head[rt];i;i=e[i].nxt){
        if (e[i].to==f) continue;dep[e[i].to]=dep[rt]+1;
        dfs1(e[i].to,rt),siz[rt]+=siz[e[i].to];
        col[rt]+=col[e[i].to],tt[rt]+=tt[e[i].to];
        if (siz[e[i].to]>siz[son[rt]]) son[rt]=e[i].to;
    }
    val[rt]=(siz[rt]-tt[rt]-abs(col[rt]));
}
inline void dfs2(int rt,int topf){
    top[rt]=topf,id[rt]=++tot,ref[tot]=rt;
    if (!son[rt]) return;
    dfs2(son[rt],topf);
    for (int i=head[rt];i;i=e[i].nxt){
        if (e[i].to==fa[rt]||e[i].to==son[rt]) continue;
        dfs2(e[i].to,e[i].to);
    }
}
signed main(void){
	n=read();
	for (int i=1;i<=n;i++){
		p[i].v=read(),p[i].b=read(),p[i].c=read(),p[i].id=i;
		w1+=p[i].b,w2+=p[i].c;
	}
	if (w1!=w2){printf("-1");exit(0);}
	for (int i=1;i<=n-1;i++){
		int u=read(),v=read();
		add_edge(u,v),add_edge(v,u);
	}
	dfs1(1,0),dfs2(1,1);
	build(1,1,n),sort(p+1,p+n+1);
	for (int i=1;i<=n;i++){
		if (get_val(id[p[i].id])) continue;
		int num=query(1,1,n,id[p[i].id]);
		ans+=(LL)p[i].v*(LL)num;
		int x=p[i].id;
		while (top[x]!=1){
            modify(1,1,n,id[top[x]],id[x],-num);
            x=fa[top[x]];
        }
        modify(1,1,n,id[1],id[x],-num);
        change(id[p[i].id],1),change(id[p[i].id]+siz[p[i].id],-1);
	}printf("%lld",ans);
	return 0;
}

```


---

## 作者：bsdsdb (赞：0)

题意：给定一棵树和 $\{a_n\},\{b_n\},\{c_n\}$，其中 $b_i,c_i\in {0,1}$，每个节点上初始写有 $b_i$，你的目标是把他变成 $c_i$。你可以每次选择一个节点 $i$，在 $i$ 子树内选 $k$ 个节点，将他们的 $b$ 按照你想要的方式进行重排，代价为 $ka_i$。求最小代价。

提示：dp，考虑下面这组样例：

```text
5
5 0 0
inf 0 1
inf 1 0
3 0 1
inf 1 0
1 2
2 3
3 4
4 5
```

设 $\mathrm{dp}_{i}$ 表示将 $i$ 子树内不符合的尽可能多的交换完的代价，$\mathrm{cnt}_{i,j}$ 表示 $i$ 子树内 $b_k=j,c_k\neq j$ 的数量，可以想到对于 $x$ 的每个儿子 $i$，他内部的交换要么全部按照 $\mathrm{dp}_i$ 所述方式处理，要么全部交给 $x$ 处理。但是这么贪心是错的，比如对于上面的样例，应该是 $2,3$ 给 $1$ 处理，$4,5$ 给 $4$ 处理，但是我们的方法得到的 $\mathrm{dp}$ 数组是 $[20,\infty,6,6,\infty]$，原因是 $2$ 觉得底下能全处理就全给我处理了，得到 $\mathrm{dp}_2=\infty$，然后 $1$ 看全给 $2$ 处理代价这么大，就让 $2,3,4,5$ 都交给 $1$ 处理了。$2$ 急了，没有把 $2,3$ 放到是他祖先且代价更小的 $1$ 去处理。我们改变 $\mathrm{dp}$ 数组的定义，改成将 $i$ 子树内不符合的尽可能多的在自己下面或者自己的祖先之一交换完的代价，就对了。转移的时候将 $a_i$ 改成 $\min\{a_j\mid j=i\lor j\text{ is an ancestor of }i\}$ 即可。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
random_device rndv;
mt19937 rd(rndv());
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
const double eps = 1e-8;
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const ll MAXN = 2e5 + 5;

ll n, a[MAXN], cnt[MAXN][3], dp[MAXN], t[MAXN];
vector<ll> e[MAXN];

void setdp(ll x, ll pr, ll ma) {
    ++cnt[x][t[x]];
    ma = min(ma, a[x]);
    for (ll i : e[x]) {
        if (i == pr) {
            continue;
        }
        setdp(i, x, ma);
        cnt[x][0] += cnt[i][0], cnt[x][1] += cnt[i][1];
    }
    ll k = min(cnt[x][0], cnt[x][1]) * 2;
    for (ll i : e[x]) {
        if (i == pr) {
            continue;
        }
        ll ki = min(cnt[i][0], cnt[i][1]) * 2;
        if (dp[i] < ki * ma) {
            dp[x] += dp[i], k -= ki;
        }
    }
    dp[x] += k * ma;
}

int main() {
    read(n);
    for (ll i = 1, b, c; i <= n; ++i) {
        read(a[i]), read(b), read(c);
        if (b != c) {
            t[i] = b;
        } else {
            t[i] = 2;
        }
    }
    for (ll i = 1; i < n; ++i) {
        ll u, v;
        read(u), read(v);
        e[u].empb(v);
        e[v].empb(u);
    }
    setdp(1, 0, inf);
    for (ll i = 1; i <= n; ++i) {
        cerr << i << ' ' << dp[i] << endl;
    }
    if (cnt[1][0] != cnt[1][1]) {
        puts("-1");
    } else {
        write(dp[1]), enter();
    }
	return 0;
}

;             ;;;;;;;;;;;         ;
;                      ;         ; ;
;                    ;          ;   ;
;                   ;          ;     ;
;                 ;           ;;;;;;;;;
;               ;            ;         ;
;              ;            ;           ;
;;;;;;;;;;;   ;;;;;;;;;;   ;             ;

   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;
```

---

## 作者：ZCETHAN (赞：0)

[传送门](https://codeforces.com/problemset/problem/1363/E)

## 题目大意

给一棵树，每个点有初始状态和目标状态，每次可以交换一个子树内的点的状态，如果交换了 $k$ 个节点的状态，那么花费就是 $k\times a_x$，其中 $a_x$ 是子树根节点的权值。问能否达到目标状态，如果能输出最小花费，否则输出 `-1`。

## Solution

这真的是 E 题么（（（

首先考虑树上算花费可能会想到 dp，但是这题根本不用。容易想到，我们决策时唯一的问题就是两对点可能被不同的根作为它的儿子来交换，于是我们把每个点的权值变成它所有祖先的权值的最小值，这是不影响答案的。但这样以来就可以在每个子树中贪心地交换。每次一定是在一棵子树把所有能交换的交换了，然后就跑路。

nice，代码就暴力维护一个点子树中剩下的没达到目标的 $1$ 和 $0$ 的个数就可以了。

## Code

```cpp
// Problem: CF1363E Tree Shuffling
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1363E
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Author: ZCETHAN
// Time: 2021-10-29 15:26:24

#include<bits/stdc++.h>
#define ll long long
#define inf (1<<30)
#define INF (1ll<<60)
using namespace std;
const int MAXN=2e5+10;
ll val[MAXN],ans=0;
int init[MAXN],targ[MAXN];
int mor[2][MAXN],les[2][MAXN];
vector<int> e[MAXN];
void dfs(int x,int fa){
	if(init[x]!=targ[x]){
		mor[init[x]][x]++;
		les[targ[x]][x]++;
	}
	for(int s:e[x]){
		if(s==fa) continue;
		val[s]=min(val[s],val[x]);
		dfs(s,x);
		mor[0][x]+=mor[0][s];
		mor[1][x]+=mor[1][s];
		les[0][x]+=les[0][s];
		les[1][x]+=les[1][s];
	}
	for(int i=0;i<1;i++){
		int mov=min(mor[i][x],les[i][x]);
		ans+=2ll*mov*val[x];mor[i][x]-=mov;les[i][x]-=mov;
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%d%d",&val[i],&init[i],&targ[i]);
	int cnt0=0,cnt1=0,fin0=0,fin1=0;
	for(int i=1;i<=n;i++){
		cnt0+=(init[i]==0);fin0+=(targ[i]==0);
		cnt1+=(init[i]==1);fin1+=(targ[i]==1);
	}
	if(cnt0!=fin0||cnt1!=fin1){
		puts("-1");return 0;
	}
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,0);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：lcc17 (赞：0)

- 我们可以很轻松地看出这是一道树形dp

- 根据套路，设计 $dp[u][0]$ 表示以 $u$ 为节点的子树，原先值为 $0$ 但是目标值为 $1$ 的点的个数， $dp[u][1]$ 同理

- 不妨用$fa$表示$u$的父亲

- 当 $a[fa]<a[u]$ 时，根据贪心我们可以直接在 $fa$ 上做修改，易得解更优

- 所以我们需要自上而下传递，如果碰到 $a[fa]<a[u]$ 的情况就把 $a[u]=a[fa]$

- 在 $a[u]\le a[fa]$ 时，我们可以根据贪心知我们需要在根为 $u$ 的子树上面多做修改才能使解更优

- 所以令 $minn=min(dp[u][0],dp[u][1])$,花费代价 $ans+=minn*2*a[u]$

- 此时$minn*2$个点都已经经过修改变成了目标值，所以 $dp[u][0]-=minn,dp[u][1]-=minn$

- 当原值为 $1$ 目标为 $0$ 的节点数和原值为 $0$ 目标为 $1$ 的节点数不同时，无论如何都不能成功，输出 $-1$ 

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath> 
#define int long long
using namespace std;
inline int read(){
	int f=1,res=0;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=res*10+c-'0',c=getchar();}
	return f*res;
}
const int maxn=2e5+5;
int head[maxn],cnt,dp[maxn][2],n,a[maxn],b[maxn],c[maxn],ans=0;
struct Edge{
	int to,ne;
}e[maxn<<1];
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].ne=head[u];
	head[u]=cnt;
}
void dfs(int u,int fa){
	if(u!=1) a[u]=min(a[u],a[fa]);
	dp[u][b[u]]+=(b[u]!=c[u]);
	for(int i=head[u];i;i=e[i].ne){
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,u);
		dp[u][0]+=dp[v][0];dp[u][1]+=dp[v][1];
	}
	int minn=min(dp[u][0],dp[u][1]);
	ans=ans+2*minn*a[u];
	dp[u][0]-=minn,dp[u][1]-=minn;
}
signed main(){
	int sum1=0,sum2=0;
 	n=read();
 	for(int i=1;i<=n;i++) a[i]=read(),b[i]=read(),c[i]=read(),sum1+=b[i],sum2+=c[i];
 	for(int i=1;i<=n-1;i++){
 		int u,v;
 		u=read(),v=read();
 		add(u,v);add(v,u);
	}
	if(sum1!=sum2) {
		puts("-1");
		return 0;
	}
	dfs(1,-1);
	printf("%lld",ans);
	return 0; 
}
```


---

## 作者：Fairicle (赞：0)

[更好的阅读体验](https://www.luogu.com.cn/blog/Fairicle/solution-cf1363e)

这题主要考的是对性质的探究罢。

可以发现对于一个节点可以完成的操作，他的祖先一定可以完成。

于是可以在 dfs 的过程中一路更新最小值。

说句闲话，这题还有比较显然的树剖做法，即查询和修改，我在比赛时候尝试最后20min写出来然而写挂了...

主要是因为没有想到怎么把修改优雅地上传到祖先，然而这是一个很简单的操作，在该节点 dfs 结束之后把修改减掉即可。

code：

```cpp
#define ll long long
#define ri register int
#define N 200010
int n,wl;ll a[N],b[N],c[N],chk,x,y,ans,s[N][2],head[N];
struct node{
	int nxt,to;
}star[N<<1];
inline void add(int from,int to){
	wl++;
	star[wl].to=to;
	star[wl].nxt=head[from];
	head[from]=wl;
}
void dfs(int now,int fa){
	if(now!=1)
	a[now]=min(a[now],a[fa]);//更新最小值
    s[now][b[now]]=(b[now]!=c[now]);
	for(ri i=head[now];i;i=star[i].nxt){
		int u=star[i].to;
		if(u==fa) continue;
		dfs(u,now);
		s[now][0]+=s[u][0],s[now][1]+=s[u][1];
	}
	ll x=min(s[now][0],s[now][1]);
	ans+=2ll*x*a[now];
	s[now][0]-=x,s[now][1]-=x;//减去已经修改的不配对的数
}
int main(){
	n=rd();
	for(ri i=1;i<=n;++i){
		a[i]=rd(),b[i]=rd(),c[i]=rd();
		chk+=b[i]-c[i];
	}
	for(ri i=1;i<n;++i){
		x=rd(),y=rd();
		add(x,y),add(y,x);
	}
	if(chk){
		puts("-1");
		return 0;
	}
	dfs(1,0);cout<<ans;
	return 0;
} 
```


---

## 作者：ShineEternal (赞：0)

[更佳更完整的阅读效果。](https://vipblog.github.io/F7QMFSJu-/)

## description：

![](https://vipblog.github.io/post-images/1591522797207.png)

## solution：

我们观察到这棵树的一个性质：一个节点可以完成某修改操作，那么它的祖先也可以完成。

所以我们可以先优化题目的策略：遇到祖先节点的 $a$ 值比子节点小的时候直接把子节点的值更新成这个 $a$ 即可。（效果上是相等的）

优化完了之后直接 dp 即可。

我们设 $dp[u][0]$ 表示 $u$ 节点的子树中初始状态为 $0$ 且准备改为 $1$ 的节点的个数。 $dp[u][1]$ 同理。

那么对于子树的更改我们就可以一步一步记录到祖先节点上，最终累加判断就行了。

----


盘点自己的一个很小但找了很久的 bug：

u 和 i 在键盘上离得太近导致在 i 的循环内错打为 u。



## code：
```cpp
#include<cstdio>
//#include<algorithm>
#include<vector>
using namespace std;
struct ben
{
	long long x,y,z;
}a[200005];
vector<long long>e[200005];
long long ans;
long long dp[200005][2];
long long min(long long x,long long y)
{
	if(x>y)return y;
	return x;
}
void dfs(long long u,long long fa,long long sp)
{
	if(a[u].y!=a[u].z)
	{
		dp[u][a[u].y]=1;
	}
	for(int i=0;i<e[u].size();i++)
	{
		int v=e[u][i];
		if(v==fa)continue;
		dfs(v,u,min(a[u].x,sp));
		dp[u][0]+=dp[v][0];
		dp[u][1]+=dp[v][1];
	}
	sp=min(sp,a[u].x);
	long long sum=min(dp[u][0],dp[u][1]);
	ans+=2*sum*sp;
	dp[u][0]-=sum;
	dp[u][1]-=sum;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
	}
	int u,v;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	dfs(1,-1,0x3f3f3f3f);
	if(dp[1][0]||dp[1][1])ans=-1;
	printf("%lld\n",ans);
	return 0;
} 
```

---

## 作者：Fractured_Angel (赞：0)

随机跳题跳到的。太飞舞了这题。

就是首先一样的就不用改。其次是对于 $u$，如果存在一个 $u$ 的祖先 $t$ 使得 $a_t\leq a_u$，那么 $u$ 就是无用的，因为上面严格比你 $u$ 能改动的范围大，且花费还比你少。你一遍 DFS 预处理出这个东西。

如果在 $u$ 点改。每个点记 $p,q,r,s$ 代表下面没排的错误的 $0/1$ 有多少个，然后下面错误的目标的 $0/1$ 有多少个。如果这个点改就匹配然后一减，剩下的就往上传。然后我们做完了。

注意一下如果根的四个数组没消完，也就是存在不是 $0$ 的，那么就说明 $0$ 和 $1$ 个数不一样，直接输出 $-1$。记得开 long long。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MAXN = 200005;
const LL INF = 1e9 + 5;
LL n, A[MAXN], B[MAXN], C[MAXN], cnt0[MAXN], cnt1[MAXN], res0[MAXN], res1[MAXN], ans;
bool vali[MAXN];
vector<LL> G[MAXN];
void DFS(LL u, LL fa, LL val)
{
	if(A[u] < val) vali[u] = true;
	for(LL i = 0; i < G[u].size(); i ++) { LL v = G[u][i]; if(v == fa) continue; DFS(v, u, min(val, A[u])); }
	return;
}
void DFS2(LL u, LL fa)
{
	if(B[u] != C[u])
	{
		if(B[u] == 0) cnt0[u] ++;
		else cnt1[u] ++;
		if(C[u] == 0) res0[u] ++;
		else res1[u] ++;
	}
	for(LL i = 0; i < G[u].size(); i ++)
	{
		LL v = G[u][i]; if(v == fa) continue; DFS2(v, u);
		cnt0[u] += cnt0[v]; cnt1[u] += cnt1[v]; res0[u] += res0[v]; res1[u] += res1[v];
	}
	if(vali[u]) 
	{
		ans += (min(cnt0[u], res0[u]) + min(cnt1[u], res1[u])) * A[u];
		if(cnt0[u] >= res0[u]) { cnt0[u] -= res0[u]; res0[u] = 0; }
		else { res0[u] -= cnt0[u]; cnt0[u] = 0; }
		if(cnt1[u] >= res1[u]) { cnt1[u] -= res1[u]; res1[u] = 0; }
		else { res1[u] -= cnt1[u]; cnt1[u] = 0; }
	}
	return;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for(LL i = 1; i <= n; i ++) cin >> A[i] >> B[i] >> C[i];
	for(LL i = 1; i < n; i ++)
	{
		LL u, v; cin >> u >> v;
		G[u].push_back(v); G[v].push_back(u);
	}
	DFS(1, 0, INF); DFS2(1, 0);
	if(cnt0[1] || cnt1[1] || res0[1] || res1[1]) cout << "-1" << '\n';
	else cout << ans << '\n';
	return 0;
}
```

---

