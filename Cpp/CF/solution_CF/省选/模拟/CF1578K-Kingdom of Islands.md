# Kingdom of Islands

## 题目描述

The Kingdom of Islands consists of $ p $ islands. As the king, you rule over the whole kingdom, while each island is ruled over by one or several jarls under your rule. In total, there are $ n $ jarls under your jurisdiction.

Each island of the kingdom has its own strong traditions, so jarls that rule over the same island support each other and never have conflicts. The downsides of such strength are cultural conflicts between people inhabiting different islands. Thus, two jarls that rule over different islands are in conflict.

However, recent years brought a few changes to traditional relations between the jarls. To your knowledge, there are exactly $ k $ pairs of jarls such that relationships between two jarls in the pair are different from the traditional. That is, if two jarls of the pair you know rule over the same island, these jarls are in conflict. If they rule over different islands, then they overcome cultural disagreement and there is no conflict between them anymore.

As a true responsible king, you are worried about whether the kingdom is close to a major conflict. In order to estimate the current situation, you would like to find the largest possible group of jarls such that every two jarls in the group are in conflict.

## 说明/提示

The conflict graph for the last sample testcase is given below. Each circle represents an island.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1578K/ba4f9569b141be3d0ae563e0067a20822f0c5dc1.png)

## 样例 #1

### 输入

```
4 4
1 2 3 4
1
2 3```

### 输出

```
3
1 4 2```

## 样例 #2

### 输入

```
2 4
1 1 2 2
1
3 4```

### 输出

```
3
2 4 3```

## 样例 #3

### 输入

```
4 8
1 1 1 2 2 3 4 4
7
1 2
2 3
3 6
4 5
5 7
2 7
3 8```

### 输出

```
6
8 6 5 4 2 1```

# 题解

## 作者：wmy_goes_to_thu (赞：5)

题目要求最大团，怎么办呢？答案是：就求最大团！

你会发现 $k$ 非常小，所以有用的点不多，用 `Bron-Kerbosch` 算法求即可。注：以下我写的是最大独立集。

哪些点有用呢？$k$ 条边的所有点肯定要加进去，还要加入所有关键点属于的集合中一个不是关键点的点，因为可能我不选关键点更优。

这样是 $2\times 2\times k=4k=80$ 个点，你会发现它 T 掉了，所以加一个小小的优化：如果一个集合只有一个关键点，如果还有其他点，那我选其他点，一定不选关键点（很容易证明）。

这样就减少到了 $60$ 个点，可以过掉了。

---

## 作者：Cry_For_theMoon (赞：5)

[传送门](https://codeforces.com/contest/1578/problem/K)

#### 前言：

理论上可以出在普及的题目...

WA 了十一个小时的原因：$k=0$ 的时候直接 ```return printf("%d",p),0;``` 了。

#### 分析：

第一个事情是如果 $k=0$ 答案显然是 $ans=p$：每个集合都取一个点。

发现 $k=20$ ，考虑边是否有一些用 0/1 去枚举的东西。

称连接不同集合的边为“删边”，否则为“加边”。

容易发现一条删边 $(u,v)$ 决定了要么答案团不会有 $u$ 要么不会有 $v$，可以暴力枚举两种情况，即决定删除哪一个点。

发现加边存在的意义是这样的：如果我们在一个集合内选择了多个点，它们必须形成一个由加边产生的完全图。就是说同一集合内如果有两个点被选择进了答案，意味着它们之间一定有一条加边。

换言之我们也可以暴力枚举加边的两种情况：加入答案 / 不加入答案。

然后考虑统计答案，对于一个集合而言：

- 如果它的点被删空了，不对答案造成贡献

- 如果内部有加边被选择，且内部选择的加边形成完全图，答案加上 $sz$，$sz$ 是这个完全图的点数。

- 否则，可以从这个集合内选出一个点，答案 $+1$。

注意到最后会被加边删边牵扯到的集合不超过 $40$ 个所以可以最后 dfs 结束后暴力统计信息。但是存在更快的方法，即在 dfs 的过程中维护信息，最后 $O(1)$ 完成计算：

- 维护一个点是否被删 / 是否被加边覆盖

- 维护一个集合内有多少点被加边覆盖 / 选择了几条加边

- 维护一个集合内有多少点被删除了

这样，我们可以由此同时维护出几个信息：

- 所有集合内的完全图的点数之和 $sum$，即 $\sum sz$

- 被删空的集合的数目 $cnt_1$

- 内部存在加边形成的完全图的点的数目 $cnt_2$

于是一种方案下的答案就变成了 $sum+(p-cnt_1-cnt_2)$。

时间复杂度：$O(2^k+n)$

~~其实我感觉还是最后暴力枚举那 40 个集合方便~~

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=1e5+10,MAXK=25
;
int p,n,k,state,tmp;
int s[MAXN];
int sz[MAXN],delcnt[MAXN],vcov[MAXN],ecov[MAXN],cnt,epty,sum,ans;
int deltag[MAXN],covtag[MAXN],vis[MAXN];
struct cstr{
	int u,v,w;
	bool operator<(const cstr& c2)const{
		return w<c2.w;
	}
}c[MAXK];
void dfs(int r){
	if(r>k){
		//统计答案 
		if(ans<sum+(p-cnt-epty)){
			ans=sum+(p-cnt-epty);
			state=tmp;
		}
		return; 
	}
	if(c[r].w==0){
		//del edge
		int u=c[r].u,v=c[r].v;
		//del u
		if(deltag[u]==0){
			delcnt[s[u]]++;
			if(delcnt[s[u]]==sz[s[u]])epty++;
		}	
		deltag[u]++;
		dfs(r+1);
		deltag[u]--;
		if(deltag[u]==0){
			if(delcnt[s[u]]==sz[s[u]])epty--;
			delcnt[s[u]]--;
		}
		//del v
		if(deltag[v]==0){
			delcnt[s[v]]++;
			if(delcnt[s[v]]==sz[s[v]])epty++;
		}	
		deltag[v]++;
		tmp^=(1<<r);
		dfs(r+1);
		deltag[v]--;
		if(deltag[v]==0){
			if(delcnt[s[v]]==sz[s[v]])epty--;
			delcnt[s[v]]--;
		}
		tmp^=(1<<r);
	}else{
		//add edge
		int u=c[r].u,v=c[r].v;
		//not add (u,v)
		dfs(r+1);
		//add (u,v)
		if(deltag[u] || deltag[v]){return;}
		tmp^=(1<<r);
		if(vcov[s[u]] && (ll)vcov[s[u]]*(vcov[s[u]]-1)/2==ecov[s[u]]){sum-=vcov[s[u]];cnt--;}
		if(covtag[u]==0)vcov[s[u]]++;
		if(covtag[v]==0)vcov[s[v]]++;
		ecov[s[u]]++;
		if(vcov[s[u]] && (ll)vcov[s[u]]*(vcov[s[u]]-1)/2==ecov[s[u]]){sum+=vcov[s[u]];cnt++;}
		covtag[u]++;covtag[v]++;
		dfs(r+1);
		covtag[u]--;covtag[v]--;
		if(vcov[s[u]] && (ll)vcov[s[u]]*(vcov[s[u]]-1)/2==ecov[s[u]]){sum-=vcov[s[u]];cnt--;}
		ecov[s[u]]--;
		if(covtag[u]==0)vcov[s[u]]--;
		if(covtag[v]==0)vcov[s[v]]--;
		if(vcov[s[u]] && (ll)vcov[s[u]]*(vcov[s[u]]-1)/2==ecov[s[u]]){sum+=vcov[s[u]];cnt++;}
		tmp^=(1<<r);
	}
}
void construct(int state){
	memset(delcnt,0,sizeof delcnt);
	memset(deltag,0,sizeof deltag);
	memset(covtag,0,sizeof covtag);
	memset(ecov,0,sizeof ecov);
	memset(vcov,0,sizeof vcov);
	rep(i,1,k){
		int u=c[i].u,v=c[i].v,w=state&(1<<i);
		if(c[i].w==0){
			if(w==0){
				//del u
				if(deltag[u]==0){
					delcnt[s[u]]++;
				}	
				deltag[u]++;
			}else{
				//del v
				if(deltag[v]==0){
					delcnt[s[v]]++;
				}
				deltag[v]++;
			}
		}else{
			if(w==0)continue;
			//add u,v
			if(covtag[u]==0)vcov[s[u]]++;
			if(covtag[v]==0)vcov[s[v]]++;
			ecov[s[u]]++;
			covtag[u]++;covtag[v]++;
		}
	}
	rep(u,1,n){
		if(deltag[u])continue;
		if(vcov[s[u]] && (ll)vcov[s[u]]*(vcov[s[u]]-1)/2==ecov[s[u]]){
			if(covtag[u])printf("%d ",u);
		}else{
			if(vis[s[u]])continue;
			printf("%d ",u);
			vis[s[u]]=1;
		}
		
	}
}
int main(){
	scanf("%d%d",&p,&n);
	rep(i,1,n){scanf("%d",&s[i]);sz[s[i]]++;}
	scanf("%d",&k);
	if(k==0){
		printf("%d\n",p);
		rep(i,1,n){
			if(vis[s[i]])continue;
			printf("%d ",i);vis[s[i]]=1;
		}
		return 0;
	}
	rep(i,1,k){
		scanf("%d%d",&c[i].u,&c[i].v);
		if(s[c[i].u]!=s[c[i].v])c[i].w=0;
		else c[i].w=1;
	}
	sort(c+1,c+1+k);
	dfs(1);
	printf("%d\n",ans);

	construct(state);
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：3)

考虑对于所有 $s_{a_j}=s_{b_j}$，枚举 $a_j$ 和 $b_j$ 是否都被选；对于所有 $s_{a_j}\neq a_{b_j}$，枚举强制不选 $a_j$ 还是强制不选 $b_j$。可以 $O(2^k)$ 枚举。

考虑枚举完如何算答案。首先对于每个出现钦定 $a_j$ 和 $b_j$ 都被选的岛屿，判断其**都被选出的点**之间的连边数量是否形成完全图。不形成完全图或其中有点被强制不选的状态可以忽略。

否则考虑贪心。对于每个出现钦定 $a_j$ 和 $b_j$ 都被选的岛屿，不妨设钦定的集合大小为 $|S|$，我们可以将 $|S|$ 加入答案。对于其他岛屿，如果所有点都被强制不选了，那么无法贡献入答案。否则将 $1$ 加入答案。

将 $2^k$ 种情况取个 $\max$ 即可。总复杂度 $O(2^kk)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
using namespace std;
vector<int> rel;
int relck[10005];
vector<int> bel[10005];
int cnt1[10005],cnt2[10005],ban[100005],cs[100005];
vector<int> vc[10005];
signed main(){
	int p,n; cin>>p>>n;
	int s[n+1]; for(int i=1;i<=n;i++) cin>>s[i],bel[s[i]].push_back(i);
	int k; cin>>k;
	int a[k+1],b[k+1];
	for(int i=1;i<=k;i++){
		cin>>a[i]>>b[i];
		if(!relck[s[a[i]]]) rel.push_back(s[a[i]]),relck[s[a[i]]]=1;
		if(!relck[s[b[i]]]) rel.push_back(s[b[i]]),relck[s[b[i]]]=1;
	}
	int maxv=0,maxp;
	for(int i=0;i<(1<<k);i++){
		int ok=1;
		for(auto v:rel) cnt1[v]=cnt2[v]=0,vc[v].clear();
		for(int j=1;j<=k;j++) ban[a[j]]=ban[b[j]]=cs[a[j]]=cs[b[j]]=0;
		for(int j=1;j<=k;j++){
			if(s[a[j]]!=s[b[j]]){
				if((i>>(j-1))&1){
					if(!ban[a[j]]) ban[a[j]]=1,cnt2[s[a[j]]]++;
				}
				else{
					if(!ban[b[j]]) ban[b[j]]=1,cnt2[s[b[j]]]++;
				}
			}
		}
		for(int j=1;j<=k;j++){
			if(s[a[j]]==s[b[j]]){
				if((i>>(j-1))&1){
					if(!cs[a[j]]) cs[a[j]]=1,vc[s[a[j]]].push_back(a[j]);
					if(!cs[b[j]]) cs[b[j]]=1,vc[s[b[j]]].push_back(b[j]);
					if(ban[a[j]]) ok=0;
					if(ban[b[j]]) ok=0;
					cnt1[s[a[j]]]++;
				}
			}
		}
		for(auto v:rel) if(vc[v].size()*(vc[v].size()-1)/2!=cnt1[v]) ok=0;
		if(!ok) continue;
		int tot=p-rel.size();
		for(auto v:rel){
			if(vc[v].size()){
				tot+=vc[v].size();
			}
			else if(cnt2[v]!=bel[v].size()){
				tot++;
			}
		}
		if(tot>maxv){
			maxv=tot,maxp=i;
		}
	}
	int i=maxp;
	{
		for(auto v:rel) cnt1[v]=cnt2[v]=0,vc[v].clear();
		for(int j=1;j<=k;j++) ban[a[j]]=ban[b[j]]=cs[a[j]]=cs[b[j]]=0;
		for(int j=1;j<=k;j++){
			if(s[a[j]]!=s[b[j]]){
				if((i>>(j-1))&1){
					if(!ban[a[j]]) ban[a[j]]=1,cnt2[s[a[j]]]++;
				}
				else{
					if(!ban[b[j]]) ban[b[j]]=1,cnt2[s[b[j]]]++;
				}
			}
		}
		for(int j=1;j<=k;j++){
			if(s[a[j]]==s[b[j]]){
				if((i>>(j-1))&1){
					if(!cs[a[j]]) cs[a[j]]=1,vc[s[a[j]]].push_back(a[j]);
					if(!cs[b[j]]) cs[b[j]]=1,vc[s[b[j]]].push_back(b[j]);
					cnt1[s[a[j]]]++;
				}
			}
		}
		cout<<maxv<<"\n";
		for(int i=1;i<=p;i++){
			if(!relck[i]){
				cout<<bel[i][0]<<" ";
			}
			else if(vc[i].size()){
				for(auto v:vc[i]) cout<<v<<" ";
			}
			else if(cnt2[i]!=bel[i].size()){
				for(auto v:bel[i]){
					if(!ban[v]){
						cout<<v<<" ";
						break;
					}
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：Alex_Eon (赞：2)

### Change log
- 2024.1.9 修改部分表述。

#### [$\color{blueviolet}\text{CF 杂题集（点我）}$](https://www.cnblogs.com/Eon-Sky/p/17763683.html)
#### [$\color{red}\text{博客内食用效果更佳（点我）}$](https://www.luogu.com.cn/blog/Ksy/solution-cf1578k)

### 简化题意

给定 $n$ 个点，$p$ 个集合，每个点属于且仅属于一个集合，两个点连边（无向边）当且仅当两个点不属于同一个集合。

接下来给定 $k$ 个特殊点对，对于一个特殊点对 $(u, v)$，若原来两者之间存在边，则删去这个边，否则添加边 $(u, v)$。

求最大团大小。

### 主体思路：状压+DFS

### 复杂度：$O(2^k + n)$

### 完整思路

~~让你输出方案，所以是大便题~~，其实感觉不输出答案的话质量还是很高的。

采用了官方题解的方法。

---

**入手**：

$k = 0$ 时，显然答案为 $p$，从每个集合里任意选择一个即可构造出方案。

我们定义特殊点对 $(u, v)$，两者之间存在边（不同集合）为“删边”，不存在边（同一集合）为“加边”。

$2^k$ 看起来像一个比较可行的复杂度，考虑枚举每个删边或者加边的两种状态，**我们优先钦定所有删边的状态，然后才到加边**。

对于一条删边，其两端点不可能同时存在于答案中，考虑枚举删去哪一个（使得其不可能在答案中）。

对于一条加边，其产生贡献当且仅当本身被选中，并且处于的集合内选择的加边组成了一个团，所以可以枚举此加边是否选中。

---

**答案的计算**：

现在考虑每个特殊点对的状态已经确定，如何统计答案。设 $sum$ 为所有集合内选中的完全图点数总和，$eptcnt$ 表示集合内部所有点都被删除的集合数量，$cplcnt$ 表示集合内部选出完全图的集合数量。

集合贡献分为以下三种：

- 删除完的集合无法造成贡献。
- 选出的完全图造成总共 $sum$ 的贡献。
- 不是以上两种，则每个可以选出任意一个未被删除的点，造成 $1$ 的贡献。

有答案为 $sum + p - eptcnt - cplcnt$。

---

**贡献的计算**：

我们期望 $O(1)$ 统计答案，考虑如何在枚举状态时维护上述变量。

对于一个点，维护 $avis_i, dvis_i$，分别表示被**选中的加边**覆盖的次数、被**删边删除**的次数。这两者只有从 $0/1$ 之间转换时会造成贡献，但仍需要计数来保证正确性。

对于一个集合，维护 $acnt_i, dcnt_i, ecnt_i$，分别表示集合内被**选中**的**点数**、被**删除**的**点数**、被**选中**的**边数**。当 $dcnt_i = siz_i$ 时，会对 $eptcnt$ 造成贡献；当 $\frac{dcnt_i\times(dcnt_i - 1)}{2} = ecnt_i$ 时，内部选中了一个合法团，会对 $sum$ 以及 $cplcnt$ 造成贡献。

每次维护只要考虑好变量更改顺序，以及贡献的判定，回溯时删除贡献即可。

---

**方案的输出**：

假设我们已经知道最优答案以及当时的状态，考虑输出方案。

我们需要重新维护出 $dvis_i, acnt_i, ecnt_i$ 来判断每一个点是否被加入，我们只要判断此点符合**“答案的计算”**中三中贡献的哪一点即可。

考虑点 $i$，设 $t = s_i$：

- 第一种有 $dvis_i \not= 0$，不输出。
- 第二种在不满足第一种的情况下，有 $\frac{dcnt_t\times(dcnt_t - 1)}{2} = ecnt_t$，输出。
- 第三种在不满足前两种的情况下，有其集合中还未有被统计进答案点，输出；若已有集合内的点，不输出。（打标记处理即可，详见代码）。

### 代码实现需要注意的地方：

- 分清 $k, p$。

- 注意回溯时撤回贡献的顺序。

### 参考代码：

代码中的 $m$ 为题目中的 $p$，剩下与题目、题解中变量名一致。


```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int UIT;
typedef double DB;
typedef pair<int, int> PII;

#define fi first
#define se second
//--------------------//
const int N = 1e5 + 5, P = 1e4 + 5, K = 20 + 5;

int n, m, k, s[N], siz[P];

struct Node {
    int u, v, typ;
} e[N];

bool cmp(Node x, Node y) { // 排序，优先处理删边
    return x.typ < y.typ;
}

int ans, asta;

int sum, eptcnt, cplcnt;
int dvis[N], avis[N], dcnt[P], ecnt[P], acnt[P];
/*
del 0 = del u,
    1 = del v;

add 0 = add(u, v),
    1 = del(u, v);
*/

void delp(int x) { // 删除一个点
    if (!dvis[x])
        dcnt[s[x]]++, eptcnt += (dcnt[s[x]] == siz[s[x]]);
    dvis[x]++;
}

void addp(int x) { // 加回一个点
    dvis[x]--;
    if (!dvis[x])
        eptcnt -= (dcnt[s[x]] == siz[s[x]]), dcnt[s[x]]--;
}

void adde(int u, int v) { // 选择一个加边
    int t = s[u];
    if (acnt[t] && 1LL * acnt[t] * (acnt[t] - 1) / 2 == ecnt[t])
        sum -= acnt[t], cplcnt--;
    acnt[t] += (!(avis[u]++)) + (!(avis[v]++)), ecnt[t]++;
    if (acnt[t] && 1LL * acnt[t] * (acnt[t] - 1) / 2 == ecnt[t])
        sum += acnt[t], cplcnt++;
}

void dele(int u, int v) { // 不选择一个加边
    int t = s[u];
    if (acnt[t] && 1LL * acnt[t] * (acnt[t] - 1) / 2 == ecnt[t])
        sum -= acnt[t], cplcnt--;
    acnt[t] -= (!(--avis[u])) + (!(--avis[v])), ecnt[t]--;
    if (acnt[t] && 1LL * acnt[t] * (acnt[t] - 1) / 2 == ecnt[t])
        sum += acnt[t], cplcnt++;
}

void DFS(int st, int now) {
    if (now > k) {
        if (ans < sum + m - eptcnt - cplcnt) // 统计答案
            ans = sum + m - eptcnt - cplcnt, asta = st;
        return;
    }
    if (e[now].typ == 0) { // 枚举状态
        delp(e[now].u);
        DFS(st, now + 1);
        addp(e[now].u);
        delp(e[now].v);
        DFS(st | (1 << (now - 1)), now + 1);
        addp(e[now].v);
    } else {
        DFS(st, now + 1);
        if (dvis[e[now].u] || dvis[e[now].v]) // 如果点已经被删去我们就无法选择，所以跳过
            return;
        adde(e[now].u, e[now].v);
        DFS(st | (1 << (now - 1)), now + 1);
        dele(e[now].u, e[now].v);
    }
}

bool kvis[P];

void print_ans() { // 输出答案，方式如题解中所说
    for (int it, x, i = 1; i <= k; i++) {
        it = ((asta >> (i - 1)) & 1);
        if (e[i].typ == 0) {
            x = (it ? e[i].v : e[i].u);
            dvis[x]++;
        } else if (it)
            acnt[s[e[i].u]] += (!(avis[e[i].u]++)) + (!(avis[e[i].v]++)), ecnt[s[e[i].u]]++;
    }
    for (int t, i = 1; i <= n; i++) {
        if (dvis[i])
            continue;
        t = s[i];
        if (acnt[t] && 1LL * acnt[t] * (acnt[t] - 1) / 2 == ecnt[t]) {
            if (avis[i])
                printf("%d ", i);
        } else if (!kvis[s[i]])
            printf("%d ", i), kvis[s[i]] = true;
    }
}
//--------------------//
int main() {
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &s[i]), siz[s[i]]++;
    scanf("%d", &k);
    if (k == 0) { // 特判
        printf("%d\n", m);
        for (int i = 1; i <= n; i++)
            if (!kvis[s[i]])
                printf("%d ", i), kvis[s[i]] = 1;
        return 0;
    }
    for (int u, v, i = 1; i <= k; i++)
        scanf("%d%d", &u, &v), e[i] = {u, v, s[u] == s[v]};
    sort(e + 1, e + k + 1, cmp);
    DFS(0, 1);
    printf("%d\n", ans);
    print_ans();
    return 0;
}

```



---

