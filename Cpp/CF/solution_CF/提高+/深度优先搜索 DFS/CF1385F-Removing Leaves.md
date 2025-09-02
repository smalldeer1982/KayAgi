# Removing Leaves

## 题目描述

You are given a tree (connected graph without cycles) consisting of $ n $ vertices. The tree is unrooted — it is just a connected undirected graph without cycles.

In one move, you can choose exactly $ k $ leaves (leaf is such a vertex that is connected to only one another vertex) connected to the same vertex and remove them with edges incident to them. I.e. you choose such leaves $ u_1, u_2, \dots, u_k $ that there are edges $ (u_1,       v) $ , $ (u_2, v) $ , $ \dots $ , $ (u_k, v) $ and remove these leaves and these edges.

Your task is to find the maximum number of moves you can perform if you remove leaves optimally.

You have to answer $ t $ independent test cases.

## 说明/提示

The picture corresponding to the first test case of the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1385F/fe7903e0da91ecf9fbf227489d31d043afa6795a.png)

There you can remove vertices $ 2 $ , $ 5 $ and $ 3 $ during the first move and vertices $ 1 $ , $ 7 $ and $ 4 $ during the second move.

The picture corresponding to the second test case of the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1385F/ea13c19a587b82204bf1bce68e6b98341f0d8036.png)

There you can remove vertices $ 7 $ , $ 8 $ and $ 9 $ during the first move, then vertices $ 5 $ , $ 6 $ and $ 10 $ during the second move and vertices $ 1 $ , $ 3 $ and $ 4 $ during the third move.

The picture corresponding to the third test case of the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1385F/ce4c6255e724b89b3c72d97a56a2ea8265194855.png)

There you can remove vertices $ 5 $ and $ 7 $ during the first move, then vertices $ 2 $ and $ 4 $ during the second move and vertices $ 1 $ and $ 6 $ during the third move.

## 样例 #1

### 输入

```
4
8 3
1 2
1 5
7 6
6 8
3 1
6 4
6 1
10 3
1 2
1 10
2 3
1 5
1 6
2 4
7 10
10 9
8 10
7 2
3 1
4 5
3 6
7 4
1 2
1 4
5 1
1 2
2 3
4 3
5 3```

### 输出

```
2
3
3
4```

# 题解

## 作者：Lily_White (赞：9)

我们需要快速地删除一个节点和与之相连的若干条边，故我们不用一般使用的 vector 来存图，而使用 set。

这样，我们就可以实时地按照与某个点相连的叶子数量多少来排序，并且先处理大的。**注意：每次操作后一个点的优先级别可能会变化，因此需要先从 set 里拿出来，再放回去**

当最大的一个点叶子数量小于 $k$ 时，结束循环，输出答案。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200020;
vector<set<int> > g;
int n, k;
vector<set<int> > leaf;
queue<int> q;
struct cmp {
  bool operator()(const int x, const int y) const {
    return (leaf[x].size() == leaf[y].size()) ? x < y
                                              : leaf[x].size() > leaf[y].size();
  }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int tc;
  cin >> tc;
  while (tc--) {
    cin >> n >> k;
    g = leaf = vector<set<int> >(n);
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      cin >> u >> v;
      --u;
      --v;
      g[u].insert(v);
      g[v].insert(u);
    }
    for (int u = 0; u < n; u++)
      if (g[u].size() == 1) leaf[*g[u].begin()].insert(u);
    set<int, cmp> s;
    int ans = 0;
    for (int u = 0; u < n; u++) s.insert(u);
    while (true) {
      int u = *s.begin();
      if (leaf[u].size() < k) break;
      for (int i = 0; i < k; i++) {
        int v = *leaf[u].begin();
        g[v].erase(u);
        g[u].erase(v);
        s.erase(u);
        s.erase(v);
        leaf[u].erase(v);
        if (leaf[v].count(u)) leaf[v].erase(u);
        if (g[u].size() == 1) {
          int w = *g[u].begin();
          s.erase(w);
          leaf[w].insert(u);
          s.insert(w);
        }
        s.insert(v);
        s.insert(u);
      }
      ans++;
    }
    cout << ans << endl;
  }
  return 0;
}
```

---

## 作者：钓鱼王子 (赞：9)

贪心。

令一个点直接连接的叶子节点个数为 $siz_x$。

当一个点 $x$ 只有叶子儿子，且个数为 $k$ 倍数时，那么可以通过 $\dfrac{siz_x}{k}$ 次操作使得 $x$ 变为叶子节点。否则无论对 $x$ 进行什么操作，其他节点的 $siz$ 不会发生改变。

每次把只有叶子儿子，且个数为 $k$ 倍数的节点加入队列，然后依次将这些点标记并删除，且将直接相连的点 $siz+1$。最后记得要加上未标记的点的 $\dfrac{siz_x}{k}$。

当只剩两个点且 $k=1$ 时可能有点小问题，特判一下 $k=1$ 即可。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t,n,m,a[200002],b[200002],ans,head[200002],cnt,rd[200002],siz[200002];
bool vis[200002];
struct edge{
	int to,next;
}e[400002];
inline void add(re int x,re int y){
	e[++cnt]=(edge){y,head[x]};
	head[x]=cnt;++rd[y];
}
queue<int>q;
int main(){
	t=read();
	while(t--){
		re int tot=0;ans=0;
		n=read();m=read();
		for(re int i=1;i<=n;++i)rd[i]=vis[i]=head[i]=siz[i]=0;
		for(re int i=1,x,y,z;i<n;++i){
			x=read(),y=read();
			add(x,y),add(y,x);
		}if(m==1){
			printf("%d\n",n-1);continue;
		}
		for(re int i=1;i<=n;++i)if(rd[i]==1){
		for(re int j=head[i];j;j=e[j].next)++siz[e[j].to];vis[i]=1;}
		for(re int i=1;i<=n;++i)if(siz[i]&&(siz[i]%m==0)&&(rd[i]-siz[i]==1))q.push(i);
		while(!q.empty()){
			re int x=q.front();q.pop();if(vis[x])continue;
			ans+=siz[x]/m;vis[x]=1;
			for(re int i=head[x];i;i=e[i].next)
				if(!vis[e[i].to]){
					++siz[e[i].to];
					if(siz[e[i].to]%m==0&&siz[e[i].to]==rd[e[i].to]-1)q.push(e[i].to);
				}
		}
		for(re int i=1;i<=n;++i)if(!vis[i])ans+=siz[i]/m;
		printf("%d\n",ans);
	}
}
```


---

## 作者：NightDiver (赞：7)

看到题，感觉像树形DP，遂设计DP式子。

$dp_u$ 表示以 $u$ 为根的子树内最多能删多少次（不删 $u$）。

那么每次子节点到父节点增加的贡献就是 $\lfloor\frac{子树大小为1的子节点个数}{k}\rfloor$。

得出式子 $dp_u = \sum_{v\in son_u} dp_v + (\sum_{v\in son_u} [dp_v \times k=siz_v]) \div k$。

为方便，我们把 $\sum_{v\in son_u} [dp_v \times k=siz_v]$ 用 $sum_u$ 表示。

这是一颗无根树，所以我们进行换根。

设从 $u$ 换到 $v$ ，变量 $x$ 换根前为 $x_0$ 换根后为 $x$。

$dp_u=dp_{u0}-dp_{v0}-sum_{u0}\div k+(sum_{u0} - [dp_{v0} \times k = siz_{v0} - 1]) \div k$

$siz_u=n-siz_{v0}$

$siz_v=n$

$dp_v = dp_{v0} + dp_u - sum_{v0} \div k + (sum_{v0} + [dp_u \times k = siz_u - 1]) \div k$

$sum_v=sum_{v0}+[dp_u\times k = siz_u - 1]$

虽然这些式子看起来很复杂，但是是因为我写的屎。

这样我们就得到了一个 $O(n)$ 的解法，虽然 $1e5$ 没必要。

[代码在这里](https://www.cnblogs.com/TongKa/p/18184418)

---

## 作者：feecle6418 (赞：3)

用一个队列保存所有叶子数 $\ge k$ 的结点。

每来到一个节点，就删去 $k$ 的倍数个这个节点连接的叶子。假如这样删完后这个节点也成了叶子，并且这个节点连接的那个节点在加上这个节点后叶子个数 $\ge k$ 了，就把连接的那个节点扔进队列。

若队列为空则重新扫描，不停重复上述过程，直到不存在叶子数 $\ge k$ 的结点。

时间复杂度 $O(tn)$，$t$ 是常数，虽然我不会证明，但是目前看来是很小的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,d[200005],s[200005],h[200005],cnt;
struct E{
	int to,next;
}e[400005];
void Clear(){
	for(int i=1;i<=cnt;i++)e[i].to=e[i].next=0;
	cnt=0;
	for(int i=1;i<=n;i++){
		s[i]=d[i]=h[i]=0;
	}
}
void A(int x,int f){
	e[++cnt]={f,h[x]};
	h[x]=cnt;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1,x,y;i<n;i++){
			scanf("%d%d",&x,&y);
			A(x,y),A(y,x),d[x]++,d[y]++;
		}
		if(n==2){
			cout<<1<<endl;
			Clear();
			continue;
		}
		int ss=n,ans=0;
		for(int i=1;i<=n;i++)if(d[i]==1)s[e[h[i]].to]++;
		while(1){
		queue<int> q;
		for(int i=1;i<=n;i++)if(s[i]>=k)q.push(i);
		if(!q.size())break;
		while(!q.empty()){
			int i=q.front();
			q.pop();
			if(s[i]<k||ss<=k)break;
			int p=s[i]/k*k;
			s[i]-=p,d[i]-=p,ss-=p,ans+=p/k;
			for(int j=h[i],lst=0;j;j=e[j].next){
				int y=e[j].to;
				if(d[y]==1){
					d[y]=h[y]=0;
					if(lst)e[lst].next=e[j].next;
					else h[i]=e[j].next;
				}
				else lst=j;
			}
			if(d[i]!=1)continue;
			s[e[h[i]].to]++;
			if(s[e[h[i]].to]>=k)q.push(e[h[i]].to);
		}}
		cout<<ans<<endl;
		Clear();
	}
	return 0;
} 
```

---

## 作者：KellyFrog (赞：3)

不明白这么这么水的题为什么会放在F...

依据题目直接暴力就行了。


对于每个节点$u$，维护一个`set`，为相邻叶子节点的集合，然后把所有`set`按照大小扔进一个`set`（`priority_queue`）里就行了，每次取一个`set`出来删叶子，如果叶子删完了就把这个点也变成叶子节点更新就行了。

由于每个点最多被删除一次，所以总复杂度是$O(n \log n)$乘上一个巨大的大常数，因为CF评测机跑得快所以随便就日过去了。

就是细节有点多，尤其是玄学的`set`，更新一个点之后要重新插♂入。

```cpp
#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 2e5 + 5;

set<int> lf[MAXN], eg[MAXN];

struct Cmp {
	bool operator() (int x, int y) const {
		return lf[x].size() == lf[y].size() ? x > y : lf[x].size() > lf[y].size();
	}
};

set<int, Cmp> tr;

void Solve() {
	int n, k, ans = 0;
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		lf[i].clear(), eg[i].clear();
	}
	tr.clear();
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		eg[u].insert(v), eg[v].insert(u);
	}
	for(int i = 1; i <= n; i++) {
		if(eg[i].size() == 1) {
			lf[*eg[i].begin()].insert(i);
		}
	}
	for(int i = 1; i <= n; i++) {
		tr.insert(i);
	}
	for(;;) {
		int v = *tr.begin();
		if (int(lf[v].size()) < k) break;
		for (int i = 0; i < k; ++i) {
			int leaf = *lf[v].begin();
			eg[leaf].erase(v);
			eg[v].erase(leaf);
			tr.erase(v);
			tr.erase(leaf);
			lf[v].erase(leaf);
			if (lf[leaf].count(v)) lf[leaf].erase(v);
			if (eg[v].size() == 1) {
				int to = *eg[v].begin();
				tr.erase(to);
				lf[to].insert(v);
				tr.insert(to);
			}
			tr.insert(v);
			tr.insert(leaf);

		}
		ans++;
	}
	cout << ans << endl;
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		Solve();
	}
}
```

---

## 作者：lfxxx (赞：1)

换根 dp 基础练习题。

首先最后肯定会留下来一个点，不妨以这个点为根，那么肯定是先将一个子树删成一个点然后对这个点的父亲做删除。

记 $dp_u,vis_u,sum_u,son_u$ 表示子树内操作次数最大值，能否将子树删除成一个点，多少个儿子所在的子树可以被删成一个点，有多少个儿子，转移方程为 $dp_u = \frac{sum_u}{k} + \sum dp_v$，$sum_u = \sum vis_v$ 与 $vis_u = [sum_u \bmod k = 0] \operatorname{and} [sum_u = son_u]$。

然后考虑换根，每次把父亲的一个儿子的贡献去除是简单的，而我们可以暴力地将一个父亲的贡献作为其儿子节点的一个儿子暴力加入，时间复杂度是 $O(\sum d_i) = O(n)$ 的。

总时间复杂度也是 $O(n)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int son[maxn],dp[maxn],vis[maxn];//儿子数量 子树内操作次数 能否将子树删成一个点
int sum[maxn];//多少个儿子满足以其为根的子树可以删除成一个点
vector<int> E[maxn];
int n,k;
void DP1(int u,int fa){
    for(int v:E[u]){
        if(v!=fa){
            DP1(v,u);
            dp[u]+=dp[v];
            sum[u]+=vis[v];
            son[u]++;
        }
    }
    dp[u]+=sum[u]/k;
    if(sum[u]%k==0&&son[u]==sum[u]) vis[u]=1;
    return ;
}
int ans;
void DP2(int u,int fa){
    ans=max(ans,dp[u]);
    for(int v:E[u]){
        if(v!=fa){
            int lstdpu=dp[u],lstvisu=vis[u],lstsumu=sum[u],lstdpv=dp[v],lstvisv=vis[v],lstsumv=sum[v];
            dp[u]-=sum[u]/k;
            vis[u]=0;
            sum[u]-=vis[v];
            dp[u]-=dp[v];
            dp[u]+=sum[u]/k;
            son[u]--;
            if(sum[u]%k==0&&son[u]==sum[u]) vis[u]=1;
            sum[v]=0;
            vis[v]=0;
            dp[v]=0;
            son[v]++;
            for(int nxt:E[v]){
                dp[v]+=dp[nxt];
                sum[v]+=vis[nxt];
            }
            dp[v]+=sum[v]/k;
            if(sum[v]%k==0&&son[v]==sum[v]) vis[v]=1;
            DP2(v,u);
            //复原
            dp[u]=lstdpu;
            vis[u]=lstvisu;
            sum[u]=lstsumu;
            dp[v]=lstdpv;
            vis[v]=lstvisv;
            sum[v]=lstsumv;
            son[u]++;
            son[v]--;
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i=1;i<=n;i++) E[i].clear(),dp[i]=vis[i]=sum[i]=son[i]=0;
        for(int i=2;i<=n;i++){
            int u,v;
            cin>>u>>v;
            E[u].push_back(v);
            E[v].push_back(u);
        }
        ans=0;
        DP1(1,0);
        DP2(1,0);
        cout<<ans<<'\n';
    }
    return 0;
}
/*
1
8 3
1 2
1 5
7 6
6 8
3 1
6 4
6 1
*/
```

---

## 作者：Special_Judge (赞：1)

# CF1385F Removing Leaves 题解

看完题我第一个想到的是树形 DP。我们视这棵树为有根树并且钦定一个点为根。我们可以用树形 DP 很容易地求解出以某个点为根的答案。

为什么说是以某个点为根的答案？因为如果我们以不同的点为根，答案是有可能不一样的。另外我们可以知道，由于最优解也至少有一个点没有删去，我们计算出以所有点为根的答案并且取最大值就是答案。这是很明显的换根 DP。

第一遍 DP 的时候，我们处理出：

1. $f_i$：以 $i$ 为根的子树中，最多可以进行多少次操作。
2. $siz_i$：以 $i$ 为根的子树的节点数。
3. $cnt_i$：$i$ 的所有儿子中，有多少个儿子能被删成叶子。

令 $son_u$ 表示 $u$ 的儿子节点的集合。第一遍 DP 的状态转移方程如下：
$$
siz_{u}=1+\sum_{v \in son_u}siz_v \\
cnt_u=\sum_{v \in son_u}[siz_v-1=f_v \cdot k]  \quad \text{此处中括号为艾佛森括号}\\
f_u=\left \lfloor \frac{cnt_u}{k} \right \rfloor+\sum_{v \in son_u}f_v
$$
然后是第二遍换根 DP，这题的换根 DP 的状态转移不太好用语言描述（因为还涉及到值的临时更改），看代码吧。

代码：

```cpp
#include<bits/stdc++.h>
//#define int long long

#define here(x) {cout<<"here "<<x<<endl;}
#define putlist(x,st,ed) {for(int ind=st;ind<=ed;ind++)cout<<x[ind]<<' ';cout<<endl;}
#define putstl(x) {for(auto TeMp:x)cout<<TeMp<<' ';cout<<endl;}
#define putsize(x) cout<<sizeof(x)*1.0/1024/1024<<" MB"<<endl;

#define cases int __;cin>>__;while(__--)work();

#define MAXN_INT 2147483647
#define MAXN_LL 9223372036854775807ll

#define MOD A_NUMBER
#define N 1000001
#define eps 1e-6

#define mp make_pair
#define pb push_back

using namespace std;

int n,k;
vector<int> e[N];
int f[N],cnt[N];
int siz[N];
int g[N];

bool check(int now) { //检查某个点是否可以被删成叶子节点
	return siz[now]-1==f[now]*k;
}
void dfs1(int now,int fa) {
	siz[now]=1;
	for(int v:e[now]) {
		if(v==fa)continue;
		dfs1(v,now);
		f[now]+=f[v];
		siz[now]+=siz[v];
		if(check(v))cnt[now]++;
	}
	f[now]+=cnt[now]/k;
}
void dfs2(int now,int fa) {
	for(int v:e[now]) {
		if(v==fa)continue;
		int t=g[now];
		
		int o_cntnow=cnt[now],o_cntv=cnt[v]; //这里先备份一下原本的cnt[now]和cnt[v]的值，方便恢复
		
        //从now的答案更新到v的答案时，需要更新cnt[now]和cnt[v]以计算新的答案
        //这里需要临时更改这两者的值，后面继续递归的时候还会用到
        
        //now失去了v这个儿子
		t-=cnt[now]/k;
		if(check(v))cnt[now]--;
		t+=cnt[now]/k;
		
        //v增加了now这个儿子
		t-=cnt[v]/k;
		int NewCntNow=cnt[now]-check(v);
		if(NewCntNow==(int)e[now].size()-1&&NewCntNow%k==0)cnt[v]++; //判断now是否能被删成叶子
		t+=cnt[v]/k;
		
		g[v]=t;
		dfs2(v,now);
		
		cnt[now]=o_cntnow;
		cnt[v]=o_cntv;
	}
}

void work() {
	cin>>n>>k;
	
	for(int i=1;i<=n;i++) {
		e[i].clear();
		g[i]=siz[i]=f[i]=cnt[i]=0;
	}
	
	for(int i=1;i<=n-1;i++) {
		int u,v;
		cin>>u>>v;
		e[u].pb(v);
		e[v].pb(u);
	}
	
	dfs1(1,0);
	g[1]=f[1];
	dfs2(1,0);
	
	cout<<*max_element(g+1,g+1+n)<<endl;
}

signed main() {
	cases;
	return 0;
} 
/*

*/
```





---

## 作者：UncleSam_Died (赞：1)

### 解题思路
简单贪心，优先选择叶子节点最多的，这样能够保证一定能把所有能删的都删了。

因为要建一个可删除的图，所以我们可以使用 set 来存边，不然就需要维护一堆东西……那么我们肯定是从有叶子节点的点向父亲更新的，那么我们每次选择叶子节点最多的点，然后删除 $k$ 个叶子，判断一下删除后该节点是否为叶子节点，如果是，那么更新父亲节点的叶子节点数量，否则把这个节点从新插入 set 中。

### AC 代码
```cpp
#include<stdio.h>
#include<stdlib.h>
#include<set>
#include <vector>
#define N 200005
int n,k,in[N],son[N];
std::set<int> edge[N];
struct cmp{
    inline bool operator()(
        const int a,
        const int b
    ) const {
        if(son[a]!=son[b])
            return son[a]>son[b];
        return a<b;
    }
};
inline void work(){
    scanf("%d%d",&n,&k);int u,v;
    for(register int i=1;i<=n;++i)
        edge[i].clear(),son[i]=in[i]=0;
    for(register int i=1;i<n;++i){
        scanf("%d%d",&u,&v);
        edge[u].insert(v);
        edge[v].insert(u);
        ++in[u],++in[v];
    }std::set<int,cmp> s;
    for(register int i=1;i<=n;++i){
        if(in[i]>1) continue;
        auto v=*edge[i].begin();
        edge[i].erase(v);
        edge[v].erase(i);
        ++son[v];
    }int ans=0;
    for(register int i=1;i<=n;++i)
        s.insert(i);
    while(!s.empty()){
        auto now=*s.begin();
        if(son[now]<k) break;
        ++ans;s.erase(now);
        son[now]-=k;
        if(!son[now]&&edge[now].size()==1){
            if(edge[now].empty())
                continue;
            auto v=*edge[now].begin();
            edge[now].erase(v);
            edge[v].erase(now);
            s.erase(v);++son[v];
            s.insert(v);
        }else s.insert(now);
    }printf("%d\n",ans);
}
signed main(){
    int T;scanf("%d",&T);
    while(T--) work();
}
```

---

## 作者：RockyYue (赞：0)

### 1385F

给定一棵 $n$ 个点无根树，每次操作为将 $k$ 个度为 $1$ 且连向同一个点的点同时删掉，求最大操作次数，$O(n\log n)$。

### Sol

- 分析知，无论操作顺序，只要操作到不可操作为止，结果是相同的。
- 记 $l_x$ 为节点 $x$ 所连叶子数，则每次随意找 $l_x \ge k$ 的点，删去这 $l_x$ 个点中 $k$ 的倍数个，若最终 $x$ 为叶子，将其记录在所连节点连接的叶子中，直到 $l_{\max}<k$ 。
- 需要记录：每个点连的叶子和现存的所有相邻点，分别使用 `queue` 和 `unordered_set`，同时将所有点放入 `priority_queue`，$l_x$ 越大的点越放在前面，可以快速找能操作的 $x$。
- 写法上，注意：
  1. `set` 的比较函数，一定不能出现同时不满足 $x<y$ 和 $y<x$ 的情况（如 `return x.val<y.val`）。
  2. 其中如果涉及动态变化的量，一定要将这个量改变之前将其影响的元素删除，改变后重新插入。

---

## 作者：_shine_ (赞：0)

因为 $n$ 只有 $2\times 10^5$，所以说随便如何都能过。

用一个队列存一下当前可以一起删除 $xk$ 个点的父节点（$x$ 是一个常数），那么显然可以以此当其父节点一下的任意一点不能再进行任何删除操作时把其父节点入队，以此往复即可。

注意当队列为空时必须要判断是否还有可以进行删除操作的点，有要入队继续循环。

---

## 作者：xzy090626 (赞：0)

总结一下这道题目的几种做法，感觉都挺巧妙的。

## 做法 1
我们考虑贪心，维护一个存结点的 `set`，每次找到拥有是叶子的儿子结点最多的那个结点，并且删除 $k$ 个，再放回去；如果找不到可以删 $k$ 个的就直接跳出循环。由于每次删除至少删 1 个节点，复杂度为 $O(n\log n)$。

贪心正确性的感性证明：发现我们的操作不会使得某一次原本可以操作的删除由于贪心算法的操作而变得不可删除，也就是说我们的算法是不劣的。
## 做法 2
类似的队列做法。但是为了保证效率，我们只对叶子的儿子结点个数为 $\geq k$ 的倍数的结点维护。用队列存，每次暴力枚举可以操作的点，跑得非常快。
## 做法 3
无根树上的操作，考虑换根 dp。

于是考虑从 $u$ 为根换到 $v$ 的为根答案。

式子别的题解都差不多讲过了，我们来仔细理解一下这个思路。首先我们知道对于一个结点，它的答案构成分为三部分贡献：
- 其子树内的贡献，但不包括它的儿子；这部分贡献我们已经预处理过了，但是要注意先行减掉其儿子的贡献。
- 当以它为根时，原本的父亲的子树内的贡献，当然也不包括它的父亲；这部分是换根的重点，其贡献相当于 $dp_u$ 减去 $u$ 子树内的答案；
- 它的所有儿子（包括原来的父亲）的贡献。这部分很容易考虑的，也就是 $\lfloor{son\over k}\rfloor$。

---

## 作者：chenxia25 (赞：0)

>### [CF题目页面传送门](https://codeforces.com/contest/1385/problem/F)

>给定一棵无根树$T=(V,E),|V|=n,|E|=n-1$和一个常数$m$。每次可以选择恰好$m$个唯一连接的节点相同的叶子并删除。求最多能删多少次。本题多测。

>$\sum n\in\left[1,2\times 10^5\right]$。

我记得我在[这篇](https://www.cnblogs.com/ycx-akioi/p/CodeForces-1324.html)里吐槽过打的3次D3F全是树形DP？这次树形DP喜加一。

注意到，对于任何一种删的方案，最终必定会有至少一个节点留下来删不掉。我们可以钦定这个点为根树形DP，最后二次扫描。接下来考虑如何DP。

设$dp0_i$表示子树$i$是否能删得只剩一个$i$，$dp_i$表示子树$i$内最多能删几次。转移挺简单的，设$cnt_i=\sum\limits_{j\in son_i}dp0_j$，则

$$\begin{cases}dp0_i=[cnt_i=|son_i|][m\mid cnt_i]\\dp_i=\sum\limits_{j\in son_i}dp_j+\left\lfloor\dfrac{cnt_i}m\right\rfloor\end{cases}$$

接下来就愉快地做出来了。

然而现场我nt了。我就懒得写严格$\mathrm O(1)$的换根，写了个`calc`函数计算DP值（$\mathrm O(|son_x|)$），然后换根的时候调用这个函数。我当时zz地认为这样是均摊$\mathrm O(1)$的，交上去，TLE13。我就很生气，CF啥时候也卡常了？就算卡，这也要卡？于是吸臭氧码读优还是T。无奈之下只好改成严格$\mathrm O(1)$的换根，这样还需要记录$cnt$数组。然后就A了。赛后才发现一个菊花图就能把我卡没了。。。。。

代码：
```cpp
#pragma GCC optimize(3)///xk
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
void read(int &x){///xk
	x=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
}
void prt(int x){///xk
	if(x>9)prt(x/10);
	putchar(x%10^48);
}
const int N=200000;
int n,m;
vector<int> nei[N+1];
int cnt[N+1];
bool dp0[N+1];
int dp[N+1];
void dfs(int x=1,int fa=0){//初DP 
	cnt[x]=0;dp0[x]=true;dp[x]=0;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(y==fa)continue;
		dfs(y,x);
		cnt[x]+=dp0[y];dp0[x]&=dp0[y];dp[x]+=dp[y];
	}
	dp[x]+=cnt[x]/m;
	dp0[x]&=cnt[x]%m==0;
//	printf("dp[%d]=%d\n",x,dp[x]);
}
int ans;
void dfs0(int x=1,int fa=0){//二次扫描 
//	printf("%d=%d\n",x,dp[x]);
	ans=max(ans,dp[x]);//更新答案 
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(y==fa)continue;
		int cnt_x=cnt[x],dp0_x=dp0[x],dp_x=dp[x],cnt_y=cnt[y],dp0_y=dp0[y],dp_y=dp[y];
		cnt[x]-=dp0[y];dp0[x]=cnt[x]==nei[x].size()-1&&cnt[x]%m==0;dp[x]=dp[x]-dp[y]-(cnt[x]+dp0[y])/m+cnt[x]/m;
		cnt[y]+=dp0[x];dp0[y]=cnt[y]==nei[y].size()&&cnt[y]%m==0;dp[y]=dp[y]+dp[x]-(cnt[y]-dp0[x])/m+cnt[y]/m;//换根 
		dfs0(y,x);
		cnt[x]=cnt_x;dp0[x]=dp0_x;dp[x]=dp_x;cnt[y]=cnt_y;dp0[y]=dp0_y;dp[y]=dp_y;//还原 
	}
}
void mian(){
	read(n);read(m);
	for(int i=1;i<=n;i++)nei[i].clear();
	for(int i=1;i<n;i++){
		int x,y;
		read(x);read(y);
		nei[x].pb(y);nei[y].pb(x);
	} 
	dfs();
	ans=0;dfs0();
	prt(ans);putchar('\n');
}
int main(){
	int testnum;
	cin>>testnum;
	while(testnum--)mian();
	return 0;
}
```

---

