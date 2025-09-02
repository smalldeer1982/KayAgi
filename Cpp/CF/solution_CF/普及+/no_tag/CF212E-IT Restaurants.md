# IT Restaurants

## 题目描述

给定一个n，表示有n个节点（1～n）以及接下来n-1条边的树，现用两种颜色（红，蓝）对这颗树的节点染色，染色规则是，每个节点有三种状态，要么染成红色，要么染成蓝色，要么不染色，并且规定用一条边连接的两个节点要么染成颜色相同，要么一个染色一个不染色。问在保证染色节点最多的条件下，红色与蓝色的个数的情况。（要求是至少有一个节点被染成红色，至少一个节点被染成蓝色）。

## 样例 #1

### 输入

```
5
1 2
2 3
3 4
4 5
```

### 输出

```
3
1 3
2 2
3 1
```

## 样例 #2

### 输入

```
10
1 2
2 3
3 4
5 6
6 7
7 4
8 9
9 10
10 4
```

### 输出

```
6
1 8
2 7
3 6
6 3
7 2
8 1
```

# 题解

## 作者：Grisses (赞：8)

[题面](https://www.luogu.com.cn/problem/CF212E)

根据题目的要求。我们先画一颗树来实验一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/d4c480oe.png)

因为题目要求染色的点的数量最多，所以我们考虑全部染成同一个颜色。但是，题目要求红色和蓝色都要出现，所以便有了下一张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/c6z6x9yb.png)

但这样打了绿色圆圈的边的两边就是不一样的颜色了，因此，我们必须不给 4 号点染色，即：

![](https://cdn.luogu.com.cn/upload/image_hosting/4k13k5ot.png)

其余情况可以自己推一下。

不难发现，我们只能将一个结点不染色，然后将其删去，其余的连通块内部染成同一种颜色。

我们可以枚举这个节点，然后 0-1 背包即可。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,cnt,tot,h[5005],w[5005],c[5005];
  bitset<5005>ans,dp;//0-1背包
  struct edge{
      int v,nxt;
  }e[10005];
  void adde(int u,int v){
      e[++cnt].nxt=h[u];
      h[u]=cnt;
      e[cnt].v=v;
  }//链式前向星
  void dfs(int x,int fa){
      w[x]++;
      for(int i=h[x];i;i=e[i].nxt){
          if(e[i].v==fa)continue;
          dfs(e[i].v,x);
          w[x]+=w[e[i].v];
      }
  }//求以1为根时分别以每个点为根的子树的节点数
  void dfs1(int x,int fa){
      int tot=0,sum=0;
      for(int i=h[x];i;i=e[i].nxt){
          if(e[i].v==fa)continue;
          c[++tot]=w[e[i].v];
          sum+=w[e[i].v];
      }
      c[++tot]=n-sum-1;
      dp.reset();
      dp[0]=1;
      for(int i=1;i<=tot;i++){
          for(int j=n;j>=c[i];j--){
              if(dp[j-c[i]])dp[j]=1;
          }
      }
      ans|=dp;//0-1背包
      for(int i=h[x];i;i=e[i].nxt){
          if(e[i].v==fa)continue;
          dfs1(e[i].v,x);
      }
  }
  int main()
  {
      scanf("%d",&n);
      for(int i=2,a,b;i<=n;i++)scanf("%d%d",&a,&b),adde(a,b),adde(b,a);
      dfs(1,0);
      dfs1(1,0);
      tot=0;
      for(int i=1;i<n-1;i++)if(ans[i])tot++;//一共有多少解
      printf("%d\n",tot);
      for(int i=1;i<n-1;i++)if(ans[i])printf("%d %d\n",i,n-i-1);//输出
      return 0;
  }
```

---

## 作者：qwq___qaq (赞：4)

首先我们可以得到答案为 $n-1$，因为我们选定一个点不涂，那么其它的子树就可以涂颜色，所以就只有一个点不涂。

那么剩下的子树求出它的 `size`，每个子树有两种状态：红、蓝。

那么，我们只需要 `01` 背包即可。

至于输出，把可以的情况用 `bool` 标记即可。

时间复杂度 $O(n^2)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> G[5005];
int n,sz[5005],a[5005],tot;
bool dp[5005],f[5005];
void init(int u,int fa){
	sz[u]=1; 
	for(int i=0,len=G[u].size();i<len;++i){
		int v=G[u][i];
		if(v==fa)
			continue;
		init(v,u);
		sz[u]+=sz[v];
	}
}
void dfs(int u){
	for(int i=0,len=G[u].size();i<len;++i){
		int v=G[u][i];
		for(int j=n-1;j>=sz[v];--j)
			dp[j]|=dp[j-sz[v]];
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1,u,v;i<n;++i){
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u); 
	} 
	for(int i=1;i<=n;++i){
		memset(sz,0,sizeof(sz));
		memset(dp,0,sizeof(dp));
		dp[0]=1;
		init(i,0);
		dfs(i);
		for(int j=1;j<=n-2;++j)
			if(dp[j])
				f[j]=1;
	}
	for(int i=1;i<=n-2;++i)
		if(f[i])
			a[++tot]=i;
	printf("%d\n",tot);
	for(int i=1;i<=tot;++i)
		printf("%d %d\n",a[i],n-1-a[i]);
	return 0;
}
```

---

## 作者：小明小红 (赞：2)

# CF212E题解
**关于颜色的分析**：题目要求将一棵树尽量多的节点染上红蓝两种颜色，当然也可以不涂颜色，现在要有颜色的节点多，也就是让没颜色的节点少，显然每个图**至少**需要一个节点不涂色作为红和蓝的**交界**，既然这样那我们就枚举哪个节点不涂颜色。

**可能组成的数量**：确认完哪个节点**不染色**后，我们的剩余结点堆还剩：这个节点的父亲节点以上的连通块和几个子树形成的连通块，我们现在的目标就是计算这几个连通块的数量总共可以组成几种数量并一一输出，那么怎么计算呢？我们知道，直接全排列是要计算 $2^{n}$ 次，肯定不可取，所以我们采用 **01 背包**的思想。

**如何 01 背包**：我们讲每个物品的**容量和价值**都设为这个连通块的**大小**，$dp_j$ 就表示**遍历到**第 $i$ 个物品时容量 $j$ 是否**能被组成**，具体见代码。

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
bool ans[5009];//ans[i]表示容量为i是否能被组成 
ll n,sum,a,b;
ll w[5009],dp[5009],tot;
ll size[5009];
struct edge {//前向星存图 
	ll to,last;
} e[10009];
ll head[5009],cnt=0;
void add(ll x,ll y) {
	e[++cnt].to=y;
	e[cnt].last=head[x];
	head[x]=cnt;
}
void dfs(ll x,ll fa) {//遍历每个点 
	tot=0;
	ll kkk=0;
	memset(dp,0,sizeof(dp));
	memset(w,0,sizeof(w));
	for(ll i=head[x]; i; i=e[i].last) {
		ll v=e[i].to;
		if(v!=fa) {//将每个子树加入成物品 
			w[++tot]=size[v];
			kkk+=size[v];
		}
	}
	w[++tot]=n-kkk-1;//将父亲节点加入成物品 
	dp[0]=1;
	for(ll i=1; i<=tot; i++) {//01背包 
		for(ll j=n; j>=w[i]; j--) {
			if(dp[j-w[i]]==1) {
				dp[j]=1;
				ans[j]=1;
			}
		}
	}
	for(ll i=head[x]; i; i=e[i].last) {
		ll v=e[i].to;
		if(v!=fa) {
			dfs(v,x);
		}
	}
}
void get_size(ll x,ll fa) {//求每个树的大小，初始化 
	size[x]++;
	for(ll i=head[x]; i; i=e[i].last) {
		ll v=e[i].to;
		if(v!=fa) {
			get_size(v,x);
			size[x]+=size[v];
		}
	}
}
int main() {
	memset(ans,0,sizeof(ans));
	cin>>n;
	for(ll i=1; i<=n-1; i++) {
		cin>>a>>b;
		add(a,b);//无向边 
		add(b,a);
	}
	get_size(1,0);
	dfs(1,0);
	for(ll i=1; i<n-1; i++) {
		if(ans[i]==1) {
			sum++;
		}
	}
	cout<<sum<<endl;
	for(ll i=1; i<n-1; i++) {
		if(ans[i]==1) {
			cout<<i<<' '<<n-i-1<<endl;
		}
	}
	return 0;
}
```


---

## 作者：_edge_ (赞：2)

~~题目太不友好了，CF 上没题解，洛谷上只有一篇还看不懂的题解。~~

首先声明一下，这题目和树形 DP 一点关系也没有，纯粹用了 DP 和 树。

那么我们先可以发现一个结论，$a+b$ 最大可以取 $n-1$。

证明？考虑一个节点作为不染色的节点，那么如果它不是叶子节点，它的子树是肯定能满足 $a>0$ 且 $b>0$，因为它的子树个数不可能少于 $2$ 个。

而 $n \ge 3$ ，所以就很显然了。

那么知道了最大可以取 $n-1$，我们可以考虑枚举那个不染色的节点，并且搜出子树大小。

在此基础上，子树大小必定是要染成同样一个颜色的。

所以这个模型就转化为了，给定几个数，求出他们能拼出的数。

当然，知道了 $a$ 之后 $n-1-a$ 即为 $b$。

所以，这题目就很简单的解决了，方案数最大不会超过 $n$，所以可以直接输出。~~不过像这种输出方案的题目，方案数真的会很大么？~~

code：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int INF=5005;
struct _node_edge {
        int to_,next_;
} edge[INF<<1];
int n,head[INF],tot,in[INF],ans1,size1[INF],f[INF],ans[INF];
bool vis[INF];
void add_edge(int x,int y) {
        edge[++tot]=(_node_edge){y,head[x]};
        head[x]=tot; in[y]++; return;
}
int ksm(int x,int y) {
        int ans=1,res=x;
        while (y) {
                if (y&1) ans=(ans*res);
                res*=res;
                y>>=1;
        }
        return ans;
}
int DFS(int x) {
        if (vis[x]) return 0; vis[x]=true;
        int sum=1;
        for (int i=head[x]; i; i=edge[i].next_)
                sum+=DFS(edge[i].to_);
        return sum;
}
signed main()
{
        scanf("%d",&n);
        for (int i=1; i<n; i++) {
                int x=0,y=0; scanf("%d %d",&x,&y);
                add_edge(x,y); add_edge(y,x);
        }
        for (int i=1; i<=n; i++) {
                if (in[i]==1) continue;
                memset(vis,false,sizeof vis);
                memset(f,0,sizeof f);
                memset(size1,0,sizeof size1);
                vis[i]=true; int tot=0;
                for (int j=head[i]; j; j=edge[j].next_) {
                        if (vis[edge[j].to_]) continue;
                        size1[++tot]=DFS(edge[j].to_);
                }
                f[0]=1;
                for (int j=1; j<=tot; j++) {
                        for (int k=n; k>=size1[j]; k--) {
                                f[k]|=f[k-size1[j]];
                                ans[k]|=f[k];
                        }
                }
        }
        for (int i=1; i<n-1; i++) {
                if (!ans[i]) continue;
                ans1++;
        }
        cout<<ans1<<"\n";
        for (int i=1; i<n-1; i++) {
                if (!ans[i]) continue;
                cout<<i<<" "<<n-1-i<<"\n";
        }
        return 0;
}

```


---

## 作者：Hacker_Cracker (赞：0)

## CF212E IT Restaurants
### Solution
简单 dfs 和 0-1 背包。

解法：不难发现最多能开商店之和必然为 $N-1$。因为只要有一个节点不开任何商店，就可以不起冲突。

所以我们枚举每个不开商店的点，然后计算出它的所有子树的大小 $siz_i$。这一步可以通过 dfs 实现。

然后我们对它的子树进行 0-1 背包动态规划，定义 $dp_i$ 为本次动态规划中，通过某些连通块大小加和，能否组成 $i$ 个节点。

然后遍历 $dp$，若 $dp_i$ 为 $1$，就可以组成答案。在一个数组中记录下来，最后全部输出即可。

时间复杂度 $O(N^2)$。

记得每次枚举节点时要清零！
### [Accepted Code](https://codeforces.com/contest/212/submission/305567115)
```cpp
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
const int N=5e3+10;
vector<int>G[N];
int siz[N],n,u,v;
bool dp[N],ok[N];//dp[i]:容量为i的若干连通块能否被当前根节点的部分子树组成 
void dfs(int x,int fa){
	siz[x]=1;
	for(auto i:G[x]){
		if(i==fa) continue;
		dfs(i,x);
		siz[x]+=siz[i];
	}
	return;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		memset(dp,0,sizeof(dp));
		memset(siz,0,sizeof(siz));//每次重新计算以i为根节点的情况 
		dp[0]=1;
		dfs(i,0); 
		for(auto j:G[i]){
			for(int k=n-1;k>=siz[j];k--) dp[k]|=dp[k-siz[j]];
		}
		for(int j=1;j<=n-2/*防止输出答案时越界*/;j++){
			if(dp[j]) ok[j]=1;//只要有一次符合条件，就能当作答案输出 
		} 
	}
	int cnt=0;
	for(int i=1;i<=n-2/*n-i-1>=1,i<=n-2*/;i++) if(ok[i]) cnt++;
	printf("%d\n",cnt);
	for(int i=1;i<=n-2;i++){
		if(ok[i]) printf("%d %d\n",i,n-i-1);
	}
	return 0;
}
```

---

## 作者：Wei_Han (赞：0)

显然可以发现，我们必须且只能让一个点不染色，因为如果不染色的节点再多就不满足染色节点尽量多的要求，不染色所有点就全是一个颜色。那么考虑这一个点就将他的父亲及其上面和他的所有子树分隔开，然后这些连通块分别选择染红/蓝色，而这个染色的过程就相当于令其中一个颜色选哪些连通块，就等价于一个 01 背包的可行性问题，每个点做一遍背包再判断可行性统计答案即可，可以用 bitset 优化。

时间复杂度 $O(\frac{n^2}{w})$。

```cpp
#include<bits/stdc++.h>
#define INF 2147483647
#define pr putchar('\n')
#define pp putchar(' ')
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(register ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(register ll i = a ; i >= b ; -- i )
//#pragma GCC optimize(2)
using namespace std;
typedef long long ll;
const int N=5e5+5,M=1e7+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}

ll n,head[N],tot,siz[N];
bitset<N> f,ans;
vector<ll> g[N];
inline void dfs(ll x,ll fa){siz[x]=1;for(ll y:g[x]) if(y!=fa) dfs(y,x),siz[x]+=siz[y];}
inline void dfs1(ll x,ll fa){
	f.reset();f[0]=1;
	for(int v:g[x]){
		ll w=(v==fa)?n-siz[x]:siz[v];
		for(int i=n-2;i>=w;i--) f[i]=f[i]|f[i-w];
	}
	ans|=f;
	for(int v:g[x]) if(v!=fa) dfs1(v,x);
}
signed main(){
	read(n);
	fo(1,i,n-1){ll u,v;read(u),read(v);g[u].push_back(v),g[v].push_back(u);}
	dfs(1,0);dfs1(1,0);
	ll sum=0;
	fo(1,i,n) sum+=(ans[i]);wr(sum);pr;
	fo(1,i,n) if(ans[i]) wr(i),pp,wr(n-i-1),pr;
	return 0;
}	
``````

---

## 作者：nyC20 (赞：0)

# 思路
首先看如何确定答案。首先红色和蓝色的点的数量相加一定等于 $n-1$，因为一定有一个节点使得去掉它后图不再联通。那么再来看怎么红蓝个数的情况。我们可以枚举点，看去掉该点后是否满足条件，再用它的子树的节点数来确定红蓝的个数。我们可以设 $dp_i$ 表示删掉 $i$ 节点是否满足条件，然后 01 跑背包即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> Map[5003];
int n, x, y, sontree[5003], cnt, ans[5003];
bool dp[5003], mark[5003];

void dfs(int x, int fa){
	sontree[x]=1;
	for(int i=0;i<Map[x].size();i++){
		if(Map[x][i]==fa)continue;
		dfs(Map[x][i],x);
		sontree[x]+=sontree[Map[x][i]];
	}
}

void treedp(int x){
	for(int i=0;i<Map[x].size();i++){
		for(int j=n-1;j>=sontree[Map[x][i]];j--)dp[j]|=dp[j-sontree[Map[x][i]]];
	}
}

int main() {
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		Map[x].push_back(y);
		Map[y].push_back(x);
	}
	for(int i=1;i<=n;i++){
		memset(sontree,0,sizeof sontree);
		memset(dp,0,sizeof dp);
		dp[0]=1;
		dfs(i,0);
		treedp(i);
		for(int j=1;j<=n-2;j++){
			if(dp[j]==true)mark[j]=true;
		}
	}
	for(int i=1;i<=n-2;i++){
		if(mark[i]==true)ans[++cnt]=i;
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++){
		printf("%d %d\n",ans[i],n-1-ans[i]);
	}
	return 0;
}
```

---

## 作者：BigJoker (赞：0)

# Solution

因为要求染色节点多，所以我们考虑只有一个节点不染色，其余节点都需要染色。

假设当前 $u$ 节点不染色。

所以对于 $u$ 它的子树包括了它的本来的子树和除他以外的。

因为只要根节点被染成了什么，那么它的子节点就会染成什么。

我们发现有一点像 $0/1$ 背包。

背包跑的是这个颜色有没有使用过。

然后在对答案进行或运算一下就行了。

# Code

```cpp
#include<cmath>
#include<cstdio>
#include<vector>
#include<iostream>
#include<algorithm>
#define mem(a,x) memset(a,x,sizeof(a))
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define lowbot(x) x&-x
#define inf 0x3f3f3f3f
#define re register
#define il inline
using namespace std;
const int N=5e3+5;
il int qr(){
	int s=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)) ch=='-'?f=-1:1,ch=getchar();
	while(isdigit(ch)) s=s*10+ch-'0',ch=getchar();
	return s*f;
}
il void qw(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) qw(x/10);
	putchar(x%10+'0');
}
int n;
int sz[N];
bool ans[N];
vector<int>G[N];
vector<pair<int,int> >q;
void DFS_SZ(int pos,int fa){
	sz[pos]=1;
	for(int i=0;i<G[pos].size();i++){
		int kid=G[pos][i];
		if(kid!=fa){
			DFS_SZ(kid,pos);
			sz[pos]+=sz[kid];
		} 
	}
}
void DFS(int pos,int fa){
	vector<int>C;
	C.push_back(n-sz[pos]);
	bool dp[N]={0};
	for(int i=0;i<G[pos].size();i++){
		int kid=G[pos][i];
		if(kid!=fa){
			DFS(kid,pos);
			C.push_back(sz[kid]);
		}
	}
	dp[0]=1;
	for(int i=0;i<C.size();i++)
		for(int j=n;j>=C[i];j--) dp[j]|=dp[j-C[i]];
	for(int i=0;i<=n;i++) ans[i]|=dp[i]; 
}
int main(){
	n=qr();
	for(re int i=1;i<n;i++){
		int u,v;
		u=qr(),v=qr();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	DFS_SZ(1,-1);
	DFS(1,-1);
	int res=0;
	for(int i=1;i<n-1;i++) res+=ans[i]; 
	qw(res);
	putchar('\n');
	for(int i=1;i<n-1;i++) ans[i]?(qw(i),putchar(' '),qw(n-i-1),putchar('\n')):1;
	return 0;
}
```

---

## 作者：Harry_Hedwig (赞：0)

# 0x00 思路
先看题。
>给定一个 $n$，表示有 $n$ 个节点（$1\sim n$）以及接下来 $n-1$ 条边的**树**，现用两种颜色（红，蓝）对这颗树的节点染色，染色规则是，每个节点有**三**种状态，**要么染成红色，要么染成蓝色，要么不染色**，并且规定**用一条边连接的两个节点要么染成颜色相同，要么一个染色一个不染色**。问在保证**染色节点最多**的条件下，红色与蓝色的个数的情况。（要求是**至少有一个节点被染成红色，至少一个节点被染成蓝色**）。

据题，两种不同且染了色的节点中间必定有一个未涂色的节点。因此为保证最多且含有两种不同颜色，就有且仅有一个节点不染色。为了让此题易于解决，我们可以让那个不涂色的节点作为根节点（因为无向边），那么它的每一个子树内部颜色一定相同，否则无法满足最大这个条件。当然，每个子树颜色都是可以自选的。所以这个时候我们就可以请出 dp 大法了。

**哦对了，不过不要忘了排除叶子节点，因为叶子节点有且只有一棵子树无法满足至少有一个蓝色节点和一个红色节点。**
# 0x01 定义状态
定义 `dp[i]` ：表示在树上有 `i` 个红色节点是否可行。因此 `dp[i]` 可以为 `bool` 数组节省空间。

# 0x02 状态转移方程
由于我们可以固定一个子树使其颜色为红色。假设此子树大小为 $size$，那么 `dp[k]` 可行当且仅当 `dp[k-size]` 可行（`k` 的大小从 $size$ 到 $n$。）。由于子树很多，有一个 `dp[k-size]==1` 即可，所以用或运算实现（`|`）。

# 0x03 边界情况
- `dp[0]=1`

	这是一定可行的，但由于题目限制而不可输出。
    
## code
```c
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<vector>
using namespace std;
int d[5005],ans[5005],num,size[5005];
bool book[5005];
vector<int>V[5005];//邻接表存图
int Go(int now)//找子树 size
{
    int i,sum=1;
    if(book[now])
        return 0;
    book[now]=1;
    for(i=0;i<V[now].size();i++)
       sum+=Go(V[now][i]);
    return sum;
}
int main()
{
	int n,i,j,u,v,tot,k;
    scanf("%d",&n);
    for(i=1;i<n;i++)
    {
        scanf("%d %d",&u,&v);
        V[u].push_back(v);
        V[v].push_back(u);
    }
    for(i=1;i<=n;i++)
    {
        if(V[i].size()==1)
            continue;
       //每一个节点作为根节点的时候需要清空，因此ans数组用来存储最后的答案
        memset(book,0,sizeof(book));
        memset(d,0,sizeof(d));
        memset(size,0,sizeof(size));
        tot=0;
        book[i]=1;
        for(j=0;j<V[i].size();j++)
        {
            if(book[V[i][j]])
                continue;
            size[++tot]=Go(V[i][j]);
        }
        d[0]=1;
        for(j=1;j<=tot;j++)//dp转移
        {
            for(k=n;k>=size[j];k--)
            {
                d[k]|=d[k-size[j]];
                ans[k]|=d[k];
            }
        }
    }
    for(i=1;i<n-1;i++)
    {
        if(ans[i])
            num++;
    }
    printf("%d\n",num);
    for(i=1;i<n-1;i++)
    {
        if(!ans[i])
            continue;
        printf("%d %d\n",i,n-i-1);
    }
	return 0;
}
```

---

## 作者：__Hacheylight__ (赞：0)

Codeforces 212E IT Restaurants

题意：给你一个无向树，现在用两种颜色去给这颗树上的节点染色。用（a,b）表示两种颜色分别染的节点数。

满足以下条件：

1.任何一种颜色至少使用一次，即$a>=1\&\&b>=1$。

2.两种颜色染的节点不能相邻，即不能有边的两端染不同色。

要你使a+b值最大下输出不同的（a,b),按照a升序输出。

分析：

很容易得出一个结论：a+b的最大值就是取n-1，即只有一个点不染色。我们就想到树形dp。

先dfs求出以每个节点为根的树的节点数。

假如我们讨论以u为根的树的染色方案，我们就要知道u的字树与父亲上面的节点数能够凑出的不同a(知道a，就知道了b)。

这个地方就要用到背包了。

代码：

```cpp
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> Vi ;
typedef pair <int, int> Pii ;
typedef pair <ll, ll> Pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;

const int N = 5010 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;

inline int read(){
    int X = 0,w = 0 ;
    char ch = 0;
    while(!isdigit(ch)) {w |= ch == '-';ch = getchar();}
    while(isdigit(ch)) X = (X<<3) + (X<<1) + (ch ^ 48),ch = getchar();
    return w ? -X : X;
}

void write(int x){
     if(x < 0) putchar('-'),x = -x;
     if(x > 9) write(x / 10);
     putchar(x%10 + '0');
}

void print(int x) {
    cout << x << endl ;
    exit(0) ;
}

void PRINT(string x) {
    cout << x << endl ;
    exit(0) ;
}

void douout(double x){
     printf("%lf\n", x + 0.0000000001) ;
}

int flag[N] ;
int dp[N][N] ;  //dp[i][j]表示以i为根的数，是否能够凑出一个a为j的数
int size[N] ;
vector <int> e[N] ;

int n ;

void dfs(int now, int fat) {
    size[now] = 1 ;
    dp[now][0] = 1 ;
    for (int i = 0; i < SZ(e[now]); i++) {
        int to = e[now][i] ;
        if (to == fat) continue ;
        dfs(to, now) ;
        size[now] += size[to] ;
        for (int i = n - 1; i >= 0; i--) dp[now][i + size[to]] |= dp[now][i] ;
    }
    for (int i = n - 1; i >= 0; i--) dp[now][i + n - size[now]] |= dp[now][i] ;
    for (int i = 1; i < n - 1; i++) flag[i] |= dp[now][i] ;
}

int main() {
    scanf("%d", &n) ;
    for (int i = 1; i < n; i++) {
        int a, b ;
        scanf("%d%d", &a, &b) ;
        e[a].pb(b) ;
        e[b].pb(a) ;
    }
    dfs(1, -1) ;
    int ans = 0 ;
    for (int i = 1; i < n; i++) if (flag[i]) ans++ ;
    cout << ans << endl ;
    for (int i = 1; i < n - 1; i++) if (flag[i]) cout << i << " " << n - i - 1 << endl ;
}

```

---

