# [AGC001C] Shorten Diameter

## 题目描述

给你一棵 $N$ 个点的无向树，定义点 $u$ 和 $v$ 之间的距离是从 $u$ 到 $v$ 的简单路径上的边数。

你需要删除一些点，使树的直径小于等于 $K$，当且仅当删除某点不会对树的联通性产生影响时才可以删除。问至少删除多少点才可以满足要求。

## 说明/提示

$2≤N≤2000$，$1≤K≤N-1$，保证给出的图是一棵树。

## 样例 #1

### 输入

```
6 2
1 2
3 2
4 2
1 6
5 6```

### 输出

```
2```

## 样例 #2

### 输入

```
6 5
1 2
3 2
4 2
1 6
5 6```

### 输出

```
0```

# 题解

## 作者：hhoppitree (赞：54)

### 题意简述：  

- 给定一棵大小为 $n$ 的无根树。
- 每次可以删去一个叶节点，要使树的直径长度不超过 $k$，最小化操作次数。
- $n\le2000$。

### 题目解法：

- 对 $k$ 进行奇偶讨论。
- 若 $k$ 为偶数，枚举直径的中点 $x$。
- $\rm dfs$ 出有多少节点可以在经过 $\frac{k}{2}$ 条边内达到。
- 取最小值即可。
- 若 $k$ 为奇数，枚举直径中间的边，对两端分别 $\rm dfs$ 即可。
- 时间复杂度：$\mathcal{O}(n^2)$

### 正确代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int res=0;
    char c;
    bool zf=0;
    while(((c=getchar())<'0'||c>'9')&&c!= '-');
    if(c=='-')zf=1;
    else res=c-'0';
    while((c=getchar())>='0'&&c<='9')res=(res<<3)+(res<<1)+c-'0';
    if(zf)return -res;
    return res;
}
const int maxn=2005;
int cnt;
bool vis[maxn];
vector<int>G[maxn];
void dfs(int x,int p,int fa=-1){
	vis[x]=1;
	++cnt;
	if(!p){
		return;
	}
	for(register int i=0;i<G[x].size();++i){
		int v=G[x][i];
		if(v==fa||vis[v]){
			continue;
		}
		dfs(v,p-1,x);
	}
	return;
}
signed main(){
	int n=read(),k=read();
	for(register int i=1;i<n;++i){
		int x=read(),y=read();
		G[x].push_back(y),
		G[y].push_back(x);
	}
	int ans=1e9;
	if(!(k&1)){
		for(register int i=1;i<=n;++i){
			memset(vis,0,sizeof(vis));
			cnt=0;
			dfs(i,k/2);
			ans=min(ans,n-cnt);
		}
	}
	else{
		for(register int i=1;i<=n;++i){
			for(register int j=0;j<G[i].size();++j){
				int v=G[i][j];
				memset(vis,0,sizeof(vis));
				cnt=0;
				dfs(i,k/2,v),dfs(v,k/2,i);
				ans=min(ans,n-cnt);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
} 
```

如果您没有看懂这篇题解，可以在评论区问我，我将会回答您的问题并且修改这篇题解，使它变得更加通俗易懂，服务更多的 $\text{OIer}$。  
如果您看懂了这篇题解，可以点个赞，使这篇题解的排名上升，服务更多的 $\text{OIer}$。  

---

## 作者：jyz666 (赞：23)

# 题解 AT1981 【Shorten Diameter】

传送门[QwQ](https://www.luogu.com.cn/problem/AT1981)

## 题意

至少删多少个叶子结点（保证剩下的仍是棵树）才能使树的直径$<=k$。

## 分析

因为是要求最少删去的点数，所以可以看做求剩下最多的点数。

那么我们可以分情况讨论：

1. 对于K为偶数，枚举一个点，将距离此点>K/2的全部删掉即可满足条件，取删点数最小值。

1. 对于K为奇数，枚举一条边，树被此边分为两棵，将其深度>(K-1)/2的全部删掉，取删点数最小值。

从数据范围来看$2000$,$O(n^2)$完全可以跑过，
那么就用$DFS$大法就行了。

### Tips

1. 用$int$时会把奇数/2的小数部分约掉，一定要在$DFS$的时候再/2

1. 考试时想复杂了：把直径求出，然后试图从直径两头删点，包含大量特殊情况。。。死路一条

**千丝万缕，均在$Code$中**：

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cmath>
#include<algorithm>
#include<cstring>
#define inf 0x7f7f7f7f
using namespace std;
typedef long long ll;
#define maxn 5000010

void read(int &x){
	int f=1;x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	x*=f;
} 
struct node{
	int to;
	int nxt;
}edge[maxn];
int tot,head[maxn],maxx,vis[maxn],ans,cnt;
void add(int x,int y){edge[cnt].to=y;edge[cnt].nxt=head[x];head[x]=cnt++;}
void dfs(int now,int fa,int stp){
	tot++;
	if(stp==0) return ;
	for(int i=head[now];~i;i=edge[i].nxt){
		if(edge[i].to==fa){
			continue;
		}
		dfs(edge[i].to,now,stp-1);
	}
}
int n,k;
int main(){
	read(n),read(k);
	int u,v,del;
	for(int i=0;i<=n;i++) head[i]=-1;
	for(int i=0;i<n-1;i++){
		read(u),read(v);
		add(u,v);add(v,u);
	}
	ans=0;
	if(k%2==0){//k为偶数，枚举点，跑k/2的边 
		for(int i=1;i<=n;i++){
			tot=0;
			dfs(i,0,k/2);
			ans=max(tot,ans);
		}
	}
	else{//k为奇数，枚举边，跑k/2的点 
		for(u=1;u<=n;u++){
			for(int j=head[u];~j;j=edge[j].nxt){
				tot=0;
				int t=edge[j].to;
				dfs(t,u,k/2);
				dfs(u,t,k/2);
				ans=max(tot,ans);
			}
		}
	}
	cout<<n-ans<<endl;
}


```

求点赞QwQ

---

## 作者：LinkZelda (赞：8)

>给定一棵树，每次你可以删除一个叶子结点，求最小操作次数使得原树直径长度 $\leq k$。$n\leq 2000$。

这里提供一种贪心做法（看上去比分类讨论好想一点）。

我们可以每次找出一条直径，然后分别算一下这条直径的两个端点能到达的距离 $>k$ 的点的个数，将个数较大的那个端点删去。然后继续找直径做这样的操作即可，直到直径长度 $\leq k$。

考虑正确性，首先，端点至少要删一个，不然这条直径肯定不能满足条件。其次，我们的目标是让所有的路径都 $\leq k$，所以算出的点个数较大的，对满足要求的贡献肯定更大，所以这样贪心是对的。

然后是复杂度，每次找直径是 $O(n)$ 的，最多找 $n$ 次，所以总复杂度 $O(n^2)$ 的。

- [代码](https://www.luogu.com.cn/paste/3erhkyny)。

---

## 作者：AsunderSquall (赞：6)



# 题意  
你有一棵大小为 $n$ 的树，你每次可以删去一个叶子节点，请问让这棵树的直径变为 $k$ 至少要删去几个节点？  
$n \le 2000$  

# 题解
这是一道一眼题。不明白为什么有紫题。    
看到 $n\le2000$ 的数据范围就感觉它非常白给。  
- 如果 $k $ 是偶数，那么直径上一定有一个中点，然后树上的所有点与这个点的距离不超过 $\dfrac{k}{2}$  
那么我们枚举这个中点的位置，dfs一下，用个 $vis$ 数组存储从这个点能到的位置，最后加起来。那么答案即为 $n-cnt$，取最小的即可。  

- 如果 $k$ 是奇数，那么直径上一定有两个点（并且他们相邻），然后树上的的所有点到这两个点中之一的距离不超过$\dfrac{k-1}{2}$  
那么我们枚举这条边，同样dfs一下，计算 $cnt$，答案为最小的 $n-cnt$。  
注意一点，如果你遍历树的方式跟我一样是用 $vis$ 数组的，注意 $k$ 为奇数的情况。不能公用一个 $vis$ 数组，而且记得两个 $vis$ 数组都要清空。

时间复杂度为 $O(n^2)$。  

代码
```cpp
#include<bits/stdc++.h>
//#define int long long
#define rd(x) x=read()
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
using namespace std;
const int N=2005;
const int maxn=(1<<18);
const int mod=1e9+7;
inline int read(){int x=0,f=1;char ch=getchar();while (ch>'9'||ch<'0'){if (ch=='-')f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline int ksm(int x,int y,int z){int ret=1;while (y){if (y&1) ret=(ret*x)%z;x=(x*x)%z;y>>=1;}return ret;}
inline int ksm(int x,int y){int ret=1;while (y){if (y&1) ret=(ret*x)%mod;x=(x*x)%mod;y>>=1;}return ret;}
inline int INV(int x){return ksm(x,mod-2);}

bool vis[N];
bool vis2[N];
vector<int> T[N];
void add(int u,int v){T[u].push_back(v);T[v].push_back(u);}
int n,d,ans=2005;
vector<pii> E;
void dfs(int u,int dis,int limit)
{
    if (dis>limit) return;
    vis[u]=1;
    for (int i=0;i<T[u].size();i++)
    {
        int v=T[u][i];if (vis[v]) continue;
        dfs(v,dis+1,limit);
    }
}
void dfs2(int u,int dis,int limit)
{
    if (dis>limit) return;
    vis2[u]=1;
    for (int i=0;i<T[u].size();i++)
    {
        int v=T[u][i];if (vis2[v]) continue;
        dfs2(v,dis+1,limit);
    }
}
signed main()
{
    rd(n);rd(d);
    for (int i=1;i<n;i++) {int u,v;rd(u);rd(v);add(u,v);E.push_back(mp(u,v));}
    if (d%2==0)
    {
        //那么树的直径必然有一个中点，枚举这个中点
        for (int i=1;i<=n;i++)
        {
            memset(vis,0,sizeof(vis));
            dfs(i,0,d/2);
            int cnt=0;
            for (int i=1;i<=n;i++) cnt+=vis[i];
            ans=min(ans,n-cnt);
        }
    } else 
    {
        //那么树的直径必然有两个相对中点，并且他们之间有连边，枚举他们
        for (int i=0;i<n-1;i++)
        {
            memset(vis,0,sizeof(vis));
            memset(vis2,0,sizeof(vis2));
            int u=E[i].fi,v=E[i].se;
            dfs(u,0,d/2);dfs2(v,0,d/2);
            int cnt=0;
            for (int i=1;i<=n;i++) cnt+=vis[i]|vis2[i];
            ans=min(ans,n-cnt);
        }
    }
    cout<<ans<<endl;
}
···

---

## 作者：dcmfqw (赞：4)

为什么翻遍题解区都没有 dp 做法啊。/jk

题目要求的是删掉的最小点数，可以转换成求保留的最大点数。

可以记 $dp_{i,j}$ 表示在以 $i$ 节点为根的子树中，保留 $i$ 节点且保留的联通块以 $i$ 节点为根时的高度为 $j$ 时且联通块合法的最大点数。

（这里高度定义为从根到子树中最远点的距离）

计算一个点 $a$ 的 $dp$ 数组时，可以先递归计算出其子节点的 $dp$ 数组，然后再将子节点的 $dp$ 数组合并到 $a$ 的 $dp$ 数组中。

记当前合并的子节点为 $s$，合并时就有转移方程：

$$dp_{a,i}=\max((dp_{a,i}+dp_{s,j})[i\ge j+1][i+j+1\le k],(dp_{a,j}+dp_{s,i-1})[i\ge j][i+j+1\le k])$$

乍一看这个方程是 $O(n^3)$ 的（枚举 $s$，$i$ 和 $j$），但是可以优化到 $O(n^2)$。

假设在 $s$ 前面的已经合并到 $dp_a$ 里的子节点的最大高度为 $d$，那么 $dp_{a,i\{i>d+1\}}$ 的值在合并之前一定是无效的，可以不管它们。

这样可以直接做到 $O(n^2)$，证明感性理解起来是一棵子树的大小一定大于等于它的高度，所以把前面合并的树的最大深度换成总大小复杂度一定不会更优

然而此时每两对点才会在它们的 LCA 处对复杂度产生 1 的贡献，而总共有 $n^2$ 对点，所以复杂度为 $O(n^2)$

由于下标与深度有关，所以可能可以用长链剖分做到 $O(n)$，但是上面的做法已经足够通过这个题了。

做的时候注意枚举 $i$ 和 $j$ 的顺序。

我的代码可能和上面的方程不一样，不过本质是相同的。

代码：

```cpp
#include<cstdio>
#define rep(i, d, u) for(int i = d; i <= u; ++i)
#define gep(i, a) for(int i = firs[a]; i; i = neig[i])
int ured() {
	int ch, re = 0;
	do {
		ch = getchar();
	} while('9' < ch || ch < '0');
	do {
		re = re * 10 + (ch ^ '0');
	} while('0' <= (ch = getchar()) && ch <= '9');
	return re;
}
void uwit(int da) {
	int ch[21], cn = 0;
	do {
		ch[++cn] = da - da / 10 * 10;
	} while(da /= 10);
	do {
		putchar('0' ^ ch[cn]);
	} while(--cn);
}
inline int max(int le, int ri) {
	return le > ri ? le : ri;
}
const int _maxn = 2011;
int n, m, a, b, firs[_maxn], neig[_maxn << 1], arri[_maxn << 1], high[_maxn], dpot[_maxn][_maxn], cpdp[_maxn], rans;
void dfs1(int at, int fa) {
	dpot[at][0] = 1;
	gep(i, at) {
		if(arri[i] != fa) {
			dfs1(arri[i], at);
			rep(j, 0, high[at]) {
				cpdp[j] = dpot[at][j];
			}
			if(high[at] < high[arri[i]] + 1) {
				rep(j, high[at] + 1, high[arri[i]] + 1) {
					dpot[at][j] = -n;
				}
			}
			rep(j, 0, high[at]) {
				rep(k, 0, high[arri[i]]) {
					if(j + k + 1 <= m && dpot[at][max(j, k + 1)] < cpdp[j] + dpot[arri[i]][k]) {
						dpot[at][max(j, k + 1)] = cpdp[j] + dpot[arri[i]][k];
					}
				}
			}
			if(high[at] < high[arri[i]] + 1) {
				high[at] = high[arri[i]] + 1;
			}
		}
	}
	rep(i, 0, high[at]) {
		if(rans < dpot[at][i]) {
			rans = dpot[at][i];
		}
	}
}
int main() {
	n = ured();
	m = ured();
	rep(i, 1, n - 1) {
		a = ured();
		b = ured();
		neig[i << 1] = firs[a];
		firs[a] = i << 1;
		arri[i << 1] = b;
		neig[i << 1 | 1] = firs[b];
		firs[b] = i << 1 | 1;
		arri[i << 1 | 1] = a;
	}
	dfs1(1, 0);
	uwit(n - rans);
	return 0;
}
```


---

## 作者：foreverlasting (赞：3)

[题面](https://www.luogu.org/problemnew/show/AT1981)

瞎搞法。

暴力枚举每一种有根树，将深度超过$k/2$的点删掉，最后取个$min$就好了。当然，如果$k$是奇数的话，那就枚举两个点，分别求，然后相加就好了。

code:
```
//2018.9.14 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int N=2e3+10;
namespace MAIN{
    int n,m;
    struct E{
        int next,to;
        E() {}
        E(res next,res to):next(next),to(to) {}
    }edge[N<<1];
    int head[N],cnt;
    inline void addedge(res u,res v){
        edge[++cnt]=E(head[u],v),head[u]=cnt;
        edge[++cnt]=E(head[v],u),head[v]=cnt;
    }
    int tot;
    void dfs(res x,res fax,res depx){
        if(depx>m/2)tot++;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==fax)continue;
            dfs(tox,x,depx+1);
        }
    }
    int ans=inf;
    inline void MAIN(){
        memset(head,-1,sizeof(head));
        n=read(),m=read();
        for(res i=1;i<n;i++){
            res u=read(),v=read();
            addedge(u,v);
        }
        if(m&1){
            for(res x=1;x<=n;x++)
                for(res i=head[x];~i;i=edge[i].next){
                    res tox=edge[i].to;
                    tot=0;
                    dfs(tox,x,0);
                    dfs(x,tox,0);
                    ans=_min(ans,tot);
                }
        }
        else {
            for(res x=1;x<=n;x++)
                tot=0,dfs(x,0,0),ans=_min(ans,tot);
        }
        printf("%d\n",ans);
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：huayucaiji (赞：0)

本题不难，不至于紫（

## 解题思路

看到 $n\leq 2000$ 就知道是 $O(n^2)$ 没得跑了。关键如何 $O(n^2)$。

我们可以对 $k$ 进行分类。

如果 $k$ 为偶数，那么我们知道我们删点过后得到的树的直径一定有一个中心点 $u$，为了使得直径为 $k$，那么距离 $u$ 距离大于 $\frac {n}2$ 的点必须删除。我们枚举 $u$，然后 dfs 即可。

如果 $k$ 为奇数，和上面类似的，我们可以枚举中心边，也是一样 dfs 一下就可以知道答案了。取最小值即可。

## 代码

代码很短

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}
char read_char() {
	char ch=getchar();
	while(!isalpha(ch)) {
		ch=getchar();
	}
	return ch;
}

const int MAXN=20000+10;

int n,cnt,k,ans,m,tot;
int h[MAXN],sz[MAXN],dis[MAXN];

struct edge {
	int v,nxt;
}e[MAXN<<1];

void addedge(int u,int v) {
	e[++cnt].nxt=h[u];
	e[cnt].v=v;
	h[u]=cnt;
}
void insert(int u,int v) {
	addedge(u,v);
	addedge(v,u);
}

void dfs1(int u,int fa) {
	dis[u]=dis[fa]+1;
	if(dis[u]-1>k/2) {
		tot++;
	}
	for(int i=h[u];i;i=e[i].nxt) {
		int v=e[i].v;
		if(v!=fa) {
			dfs1(v,u);
		}
	}
}

int main() {
	cin>>n>>k;
	for(int i=1;i<n;i++) {
		insert(read(),read());
	}
	
	ans=1e9+10;
	if(k&1) {
		for(int u=1;u<=n;u++) {
			for(int i=h[u];i;i=e[i].nxt) {
				int v=e[i].v;
				dis[v]=0;
				dfs1(u,v);
				dis[u]=0;
				dfs1(v,u);
				ans=min(ans,tot);
				tot=0;
			}
		}
	}
	else {
		for(int i=1;i<=n;i++) {
			dfs1(i,0);
			ans=min(ans,tot);
			tot=0;
		}
	}
	
	cout<<ans<<endl;
	
	return 0;
}
```



---

## 作者：ImmortalWatcher (赞：0)

- 将问题折半的方法，可以考虑奇偶分开讨论。

可以发现无论 $k$ 是奇数还是偶数，我们都可以找到一个点或一条边来作为中心，这时我们就只需要去除距离中心超过直径一半的点即可。

枚举中心，计算贡献，时间复杂度为 $O(n^2)$

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct node{int last,en,next;} e[4010];
int n,D,x,y,tot,ans;
void add(int x,int y)
{
	e[++tot].en=y;
	e[tot].next=e[x].last;
	e[x].last=tot;
}
int dg(int x,int fa,int dis,int D)
{
	int ret=0;
	for (int i=e[x].last;i;i=e[i].next)
		if (e[i].en!=fa) ret+=dg(e[i].en,x,dis+1,D);
	return ret+(dis>D?1:0);
}
int main()
{
	scanf("%d%d",&n,&D);
	for (int i=1;i<n;i++)
		scanf("%d%d",&x,&y),add(x,y),add(y,x);
	ans=0x3f3f3f3f;
	if (!(D&1))
	{
		for (int i=1;i<=n;i++)
			ans=min(ans,dg(i,0,0,D/2));
	}
	else
	{
		for (int i=1;i<=n;i++)
			for (int j=e[i].last;j;j=e[j].next)
				if (i<e[j].en) ans=min(ans,dg(i,e[j].en,0,(D-1)/2)+dg(e[j].en,i,0,(D-1)/2));
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Fengxiang008 (赞：0)

## 题意分析：
给出一个 N 个点的树，要求删去最少的点使树的直径不超过 K 。
树的直径定义为一棵树中最远两点间的距离。

## 思路：
K 为偶数时，我们很容易发现：随便选一个点，这棵树满足条件的点到那个点的距离不会超过 $ \dfrac {k}{2} $。

因为如果有满足条件的点到那个点的距离超过 $ \dfrac {k}{2} $ 
那么我们把选中的点移动一下，还是满足上述性质。

K 为奇数时我确实走了一些弯路，一开始只是以为上述情况下如果可以再往下扩展一个点就扩展，结果半天没调过 QwQ 。

其实我们可以让一条边当作上述的点，所以距离不会超过 $\dfrac {k-1}{2} $。

然后就可以枚举点或边，然后跑 dfs ，求解即可。


### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 2005
#define min(a,b) ((a)<(b)?(a):(b))
struct node { int v; node *nxt; } edge[maxn*2],*head[maxn],*ncnt;
int n,k,dist[maxn],deg[maxn],d1,d2,ans;
void addedge(int u,int v)
{
	ncnt++;
	ncnt->v=v,ncnt->nxt=head[u];
	head[u]=ncnt;
}
void dfs(int u,int fa,int d)
{
	dist[u]=d;
	for(node *p=head[u];p;p=p->nxt)
	{
		int v=p->v;
		if(v==fa) continue;
		dfs(v,u,d+1);
	}
}
int main()
{
	ncnt=&edge[0];
	scanf("%d%d",&n,&k);
	ans=n;
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addedge(u,v); addedge(v,u);
		deg[u]++,deg[v]++;
	}
	if(k%2)
		for(int i=1;i<=n;i++)
			for(node *p=head[i];p;p=p->nxt)
			{
				if(p->v<i) continue;
				dfs(i,p->v,0); dfs(p->v,i,0);
				int cnt=0,tmp=k/2;
				for(int j=1;j<=n;j++)
					if(dist[j]>tmp) cnt++;
				ans=min(ans,cnt);
			}
	else
		for(int i=1;i<=n;i++)
		{
			dfs(i,0,0);
			int cnt=0,tmp=k/2;
			for(int j=1;j<=n;j++)
				if(dist[j]>tmp) cnt++;
			ans=min(ans,cnt);
		}
	printf("%d\n",ans);
    return 0;
}

```


---

## 作者：Priori_Incantatem (赞：0)

[题目链接](https://atcoder.jp/contests/agc001/tasks/agc001_c)

### 题意

给出一个 $n$ 个节点的树，每次操作可以删除一个叶子节点  
问最少需要进行多少次操作，才能让剩下的树满足直径不超过 $k$

---- 

考虑对答案求补集，也就是考虑留下哪些节点。  
对于一棵树的直径中点，满足所有点到中点的距离不超过直径的一半。注意当直径长度为奇数时，直径中点为一条边  
那么，我们可以枚举每一个点（边）作为直径中点时，直径不超过 $k$ 的树的最大节点数

时间复杂度 $\mathcal O(n^2)$

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int Maxn=2010;
vector <int> e[Maxn];
int d[Maxn];
int n,k,ans,tot;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
inline void add(int x,int y)
{
	e[x].push_back(y);
}
void dfs(int x,int fa)
{
	d[x]=d[fa]+1;
	if(d[x]<=(k>>1))++tot;
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i];
		if(y==fa)continue;
		dfs(y,x);
	}
}
int main()
{
	n=read(),k=read();
	for(int i=1;i<n;++i)
	{
		int x=read(),y=read();
		add(x,y),add(y,x);
	}
	if(k & 1)
	{
		for(int x=1;x<=n;++x)
		for(int i=0;i<e[x].size();++i)
		{
			int y=e[x][i];
			if(x>y)continue;
			tot=0;
			d[y]=-1,dfs(x,y);
			d[x]=-1,dfs(y,x);
			ans=max(ans,tot);
		}
	}
	else
	{
		d[0]=-1;
		for(int i=1;i<=n;++i)
		{
			tot=0,dfs(i,0);
			ans=max(ans,tot);
		}
	}
	printf("%d\n",n-ans);
	return 0;
}
```

---

