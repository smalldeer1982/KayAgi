# XOR Partition

## 题目描述

For a set of integers $ S $ , let's define its cost as the minimum value of $ x \oplus y $ among all pairs of different integers from the set (here, $ \oplus $ denotes bitwise XOR). If there are less than two elements in the set, its cost is equal to $ 2^{30} $ .

You are given a set of integers $ \{a_1, a_2, \dots, a_n\} $ . You have to partition it into two sets $ S_1 $ and $ S_2 $ in such a way that every element of the given set belongs to exactly one of these two sets. The value of the partition is the minimum among the costs of $ S_1 $ and $ S_2 $ .

Find the partition with the maximum possible value.

## 样例 #1

### 输入

```
5
42 13 1337 37 152```

### 输出

```
10001```

## 样例 #2

### 输入

```
4
1 2 3 4```

### 输出

```
1100```

## 样例 #3

### 输入

```
2
1 2```

### 输出

```
10```

## 样例 #4

### 输入

```
8
7 6 5 4 3 2 1 0```

### 输出

```
10010110```

# 题解

## 作者：stntn (赞：15)

复杂度 $O(n\log V)$ 踩标算。

先想已知 $S$ 怎么算其权值。

考虑建立 01trie，我们找到所有极低（数位最低）的，左右儿子各有一个数的节点，算出其左右儿子的异或，然后取 $\min$ 即可。

我们发现权值的计算可以分为两部分，一个是数位前缀的匹配（即上文找到极低节点，它们的异或为 $0$），一个是剩余位的异或。

于是问题变成这样：给定一棵 01trie，将其分裂为两棵，使得最低的拥有左右儿子的节点最高，在此基础上使其左右儿子异或值最大。

首先解决最低的有双子的节点最高：假如原 trie 上的节点 $u$ 的两个儿子分别满足要么其不存在，要么 $size\le 2$，这样我们可以从该节点分裂，每个儿子内部染色不同，分裂为 $u,u'$ ，二者均满足存在左右儿子，其子树为链，于是它们是极低的点。于是我们从上到下能分裂就尽早分裂，即得到最高。

然后解决儿子异或最大，这个就很简单了，因为左右儿子内的树各不超过 $2$ 个，暴力枚举一下那两个分到一个树内使得异或的最小值最大即可。

表述可能不是很清楚，见代码：

有什么问题欢迎 hack！

```cpp
#include<bits/stdc++.h>
#define N 200010
#define M 100010
#define LL long long
#define ULL unsigned long long
#define DB double
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define tep(u) for(int v:e[u])
#define INF 0x3f3f3f3f
#define mp(i,j) make_pair(i,j)
#define fi first
#define se second
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
int n,k=29,a[N]; 
bool ans[N];
vector<int> a1,a2;
struct TRIE//正常的01tire 
{
	int ch[N<<5][2],cnt[N<<5],id[N<<5],dep[N<<5],pcc;
	inline void init(){dep[0]=30;}
	inline void insert(int v,int x)
	{
		int root=0;cnt[0]++;
		per(i,29,0)
		{
			bool c=(v>>i)&1;
			if(!ch[root][c]) dep[ch[root][c]=++pcc]=dep[root]-1;
			cnt[root=ch[root][c]]++;
		}
		id[root]=x;
	}
}t;
inline void dfs(int u)//求出极低点的最高值 
{
	if((!t.ch[u][0]||t.cnt[t.ch[u][0]]<=2)&&(!t.ch[u][1]||t.cnt[t.ch[u][1]]<=2)) 
		return k=min(t.dep[u]-1,k),void();
	if(t.ch[u][0]) dfs(t.ch[u][0]);
	if(t.ch[u][1]) dfs(t.ch[u][1]);
}
inline void dfs3(int u,bool rt)
{
	if(t.id[u]) return (rt?a2:a1).push_back(t.id[u]),void();
	if(t.ch[u][0]) dfs3(t.ch[u][0],rt);
	if(t.ch[u][1]) dfs3(t.ch[u][1],rt);
}
inline void dfs1(int u)//分类讨论每个极低点 
{
	if((!t.ch[u][0]||t.cnt[t.ch[u][0]]<=2)&&(!t.ch[u][1]||t.cnt[t.ch[u][1]]<=2))
	{
		a1.clear();a2.clear();
		rep(i,0,1) if(t.ch[u][i]) dfs3(t.ch[u][i],i);//把子树内的值找到 
		if(a1.size()>a2.size()) swap(a1,a2);
		int sz1=a1.size(),sz2=a2.size(); 
		if(!sz1) rep(i,0,sz2-1) ans[a2[i]]=i;
		else if(sz1==1)//暴力分讨 
		{
			if(sz2==1) ans[a1[0]]=0,ans[a2[0]]=1;
			if(sz2==2)
			{
				ans[a1[0]]=0;
				ans[a2[0]]=((a[a1[0]]^a[a2[0]])<=(a[a1[0]]^a[a2[1]]));
				ans[a2[1]]=((a[a1[0]]^a[a2[0]])>(a[a1[0]]^a[a2[1]]));
			}
		}
		else if(sz1==2)
		{
			if(min(a[a1[0]]^a[a2[0]],a[a1[1]]^a[a2[1]])>min(a[a1[0]]^a[a2[1]],a[a1[1]]^a[a2[0]]))
			{
				ans[a1[0]]=ans[a2[0]]=0;
				ans[a1[1]]=ans[a2[1]]=1;
			}
			else
			{
				ans[a1[0]]=ans[a2[1]]=0;
				ans[a1[1]]=ans[a2[0]]=1;
			}
		}
		return;
	}
	if(t.ch[u][0]) dfs1(t.ch[u][0]);
	if(t.ch[u][1]) dfs1(t.ch[u][1]);
}
signed main()
{
	read(n);t.init();
	rep(i,1,n) read(a[i]),t.insert(a[i],i);
	dfs(0);dfs1(0);
	rep(i,1,n) printf("%d",ans[i]);printf("\n");
	return 0;
}
```

---

## 作者：spdarkle (赞：11)


一个很简朴的思路是：不断找剩下的最小异或对，将其分到两个集合。

划分两个集合的常见套路是二分图。

那么我们换一种角度，将这些最小异或对看作一条边，连成图，直到它不是二分图为止。

则当这张图连通时，二分图的划分就已经确定了，所以只要 $n$ 个点连成一棵树，就可以停止找最小异或对并黑白染色输出方案了。

再转化一下，就是在一张完全图，边 $(i,j)$ 的边权为 $a_i\oplus a_j$ 的情况下，找出这样一颗生成树，使得非树边 $(u,v)$ 的边权大于树上 $(u,v)$ 路径上的任意一条边的边权。 

容易看出，这就是最小异或生成树问题。

故：我们求出最小异或生成树，然后黑白染色输出方案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 500500
#define int long long
int num,p,ch[N<<4][2],l[N<<4],r[N<<4],n,b[N];
int head[N],ver[N],nxt[N],c[N],tot,id;
struct node{
	int x,id;
	bool operator<(const node b)const {
		return x<b.x;
	}
}a[N];
void ad(int u,int v){
	nxt[++tot]=head[u],ver[head[u]=tot]=v;
}
void add(int u,int v){
	ad(u,v);ad(v,u);
}
void insert(int x,int p,int id,int dep){
	if(dep==-1)return ;
	int s=(x>>dep)&1;
	if(ch[p][s])r[ch[p][s]]=id;
	else ch[p][s]=++num,l[num]=r[num]=id;
	insert(x,ch[p][s],id,dep-1);
}
int query(int x,int p,int dep){
	if(dep==-1){
		id=l[p];return 0;
	}
	int s=(x>>dep)&1;
	if(ch[p][s])return query(x,ch[p][s],dep-1);
	return query(x,ch[p][s^1],dep-1)+(1<<dep);
}
void solve(int p,int dep){
	if(!p||dep==-1)return ;
	int x=ch[p][0],y=ch[p][1];
	if(x&&y){
		if(r[x]-l[x]+1>r[y]-l[y]+1)swap(x,y);
		int ans=0x3f3f3f3f,u=-1,v=-1;
		for(int i=l[x];i<=r[x];i++){
			int k=query(a[i].x,y,dep-1);
			if(ans>k)ans=k,u=i,v=id;
		}
		add(a[u].id,a[v].id);
	}
	solve(x,dep-1);solve(y,dep-1);
}
void dfs(int u,int now){
	c[u]=now;
	for(int i=head[u];i;i=nxt[i]){
		int v=ver[i];if(c[v]!=-1)continue;
		dfs(v,now^1);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;num=1;for(int i=1;i<=n;i++)cin>>a[i].x,b[i]=a[i].x,a[i].id=i;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)insert(a[i].x,1,i,30),c[i]=-1;
	solve(1,30);dfs(1,0);
	for(int i=1;i<=n;i++)cout<<c[i]; 
}
```

至于最小异或生成树的求法，请看 [CF888G题解区](https://www.luogu.com.cn/problem/solution/CF888G)。

时间复杂度： $O(n\log n\log V)$。

---

## 作者：hxhhxh (赞：5)

时间复杂度 $O(n\log n)$，空间线性，瓶颈在排序，再踩一次标算。

### 做法

首先考虑如何已知 $S$ 求权值。一个经典结论是对于一个集合，其不同数两两异或的最小值一定等于将其中元素排序后相邻两项异或的最小值，证明~~留作练习~~可以参考其他题解。所以我们先把原数组排个序。

然后尝试计算答案。首先枚举答案的最高位。假设答案的最高位为 $2^k$，那么对于在 $2^{k+1},2^{k+2}\dots$ 这些位上不同的数之间就一定不会产生贡献。将数组按照 $\lfloor\frac{x}{2^k}\rfloor$ 划分成若干段，那么两段之间互相独立。

如果一段之中有 $\geq 5$ 个数，那么至少有 $3$ 个数的 $2^k$ 位相等，那么 $S$ 和 $U\setminus S$ 中至少有一个包含了两个第 $2^k$ 位相等的数，它们的异或的最高位比 $2^k$ 低，矛盾，所以一段之中最多有四个数。换种说法，就是答案一定在相邻的四个数中产生。

那我们就没有必要枚举答案的最高位了。直接对于每相邻的四个数都枚举所有可能的划分方式并统计答案，得到的就一定是最终的答案。

然后我们需要构造方案。现在我们知道了答案的最高位，可以直接像上面一样分段。之后考虑段的长度：

- 长度为 $1$ 或 $2$：你会的；
- 长度为 $3$：枚举哪个元素在 $S$ 里，取最优的即可；
- 长度为 $4$：可以钦定第一个元素在 $S$ 里，枚举第三个还是第四个元素也在 $S$ 里；
- 长度大于 $4$：你算错了。

由于每一段之间互不影响，所以直接对每段分别构造之后拼起来即可。

时间复杂度瓶颈为一开始的排序 $O(n\log n)$，注意最终我们**没有**枚举答案的最高位，所以剩下的部分是线性的。不过常数有一点大，可能跑不过 $O(n\log V)$。

注意 $n=3$ 时答案会有问题（$n=2$ 没有），建议在序列最后补一个 $2^{30}$。 

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=2e9,c[200005];
struct st{
	int x,id;
}a[200005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i].x),a[i].id=i;
	sort(a+1,a+n+1,[&](st x,st y){return x.x<y.x;});
	a[n+1].x=1<<30;//处理 n=3  
	for(int i=1;i+2<=n;i++){
		int x=a[i].x,y=a[i+1].x,z=a[i+2].x,w=a[i+3].x;
		ans=min(ans,max({
		min(x^y,z^w),//0011 
		min(x^z,y^w),//0101
		min(x^w,y^z),//0110
		min(x^y,y^z),//0001
		min(y^z,z^w)//0111
		//这里有 x^w>min(x^y,y^w)，所以 0100不优，0010 同理。
		}));
	}
	for(int i=1,j=i;i<=n;i=j){//算完答案后就不用管补的 1<<30 了。 
		while(j<=n&&__lg(a[i].x^a[j].x)<=__lg(ans)) j++;
		//这里被划分到的区间是 [i,j)  
		if(j-i==2) c[a[i].id]=1;
		if(j-i==3){
			int x=a[i].x,y=a[i+1].x,z=a[i+2].x;
			if((x^y)>=ans) c[a[i+2].id]=1;//001
			else if((x^z)>=ans) c[a[i+1].id]=1;//010
			else c[a[i].id]=1;//100
		}
		if(j-i==4){
			int x=a[i].x,y=a[i+1].x,z=a[i+2].x,w=a[i+3].x;
			if(min(x^z,y^w)>=ans) c[a[i].id]=c[a[i+2].id]=1;//1010
			else if(min(x^w,y^z)>=ans) c[a[i].id]=c[a[i+3].id]=1;//1001
		}
	}
	for(int i=1;i<=n;i++) cout<<c[i];
	return 0;
}
```

---

## 作者：Purslane (赞：5)

# Solution

有趣的题目，昨晚写了个 $O(n \log^2 V)$ 的做法，但是人傻常数大过不去。在末尾我稍微提一下吧。感谢[这条评论](https://codeforces.com/blog/entry/118676?#comment-1052157)给我的启发。

考虑异或最基本的一个性质：如果 $a<b<c$ 那么 $a \oplus c > \min\{a \oplus b,b \oplus c\}$，因此一个集合两两异或的最小值为相邻两数异或的最小值，我们不妨把原序列排个序。

很容易想到二分答案之后对于所有 $a_i \oplus a_j < m$ 的 $(i,j)$ 连边，然后判定是不是二分图。但是这样边的数量会达到 $O(n^2)$ ，难以接受。不过很容易发现，如果三个数之间两两连边，那么肯定有奇环，这是不合法的。而且，如果第一个数和最后一个数有连边，这样说明限制非常严，那不合法十之八九对不对。

我们证明一个引理：如果 $x$ 和 $x+4$ 有连边，那么一定不合法。

证明：考虑 $a_x \oplus a_{x+4}$ 的最高位。然后我们把 $a$ 的这几位拿出来看。显然的，比这一位高的位在 $[x,x+4]$ 上都是相同的，所以可以把它们忽略。

那么单独考虑这一位，只可能是 $\{0,1,1,1,1\}$ 或 $\{0,0,1,1,1\}$ 或 $\{0,0,0,1,1\}$ 或 $\{0,0,0,0,1\}$ 四种情况。很容易发现，对于前两种情况，后三个数两两异或的这一位都是 $0$；对于后两种情况，前三个数两两异或的这一位都是 $0$。因为 $x$ 和 $x+4$ 已经有连边了，所以这些异或是 $0$ 的肯定都能连边，那么必定存在为长度是 $3$ 的环，肯定无解。

那么显然，对于 $x+5$ 及以后的肯定还是如此。因此，只要我们连的边跨度不超过 $3$，如果判断出来有解，就不会有跨度很大的边，那么实际图的形态保持不变，正确；如果无解，那么实际图只会有更多的边，一定无解。

因此只有 $O(3n)$ 条有用的边。那么就可以二分答案了。

我的做法是在二分答案后用 Trie 树优化建图，这样最多 $O(n \log V)$ 条边，但是常数太大过不去 /ll

代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=200000+10;
int n,a[MAXN],b[MAXN],rev[MAXN],col[MAXN],tmp; vector<int> G[MAXN]; 
void dfs(int u,int c) {
	if(col[u]!=-1) return tmp&=(col[u]==c),void();
	col[u]=c; for(auto v:G[u]) dfs(v,c^1);
	return ;
}
int solve(int m) {
	tmp=1,memset(col,-1,sizeof(col)); ffor(i,1,n) G[i].clear();
	ffor(i,1,n) ffor(j,i+1,min(n,i+3)) if((b[i]^b[j])<m) G[i].push_back(j),G[j].push_back(i);
	ffor(i,1,n) if(col[i]==-1) dfs(i,1);
	return tmp;
}
int bfind(int l,int r) {
	int ans=-1,mid;
	while(l<=r) {
		mid=l+r>>1;
		if(solve(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; ffor(i,1,n) cin>>a[i];
	vector<pair<int,int>> vc; ffor(i,1,n) vc.push_back({a[i],i});
	sort(vc.begin(),vc.end());
	ffor(i,1,n) b[i]=vc[i-1].first,rev[vc[i-1].second]=i;
	if(n==2) return cout<<10,0;
	int ans=bfind(0,(1<<30)-1),h=solve(ans);
	ffor(i,1,n) cout<<col[rev[i]];
	return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：5)

倍增。

初始化 $p=0$，从高位到低位尝试让 $p$ 的某一位变为 $1$，并检查此时能否使所有满足 $i\neq j,a_i\oplus a_j<p$ 的 $a_i$ 和 $a_j$ 都分到不同的集合，检查失败，则让 $p$ 这一位变回 $0$。

考虑对于非法的 $(i,j)$，在 $i$ 和 $j$ 之间连边，若形成二分图，则合法。想到黑白染色。

枚举 $i$，枚举 $a_i\oplus a_j$ 与 $p$ 的最长公共前缀，然后若 $p$ 的下一位是 $1$，则钦定 $a_i\oplus a_j$ 下一位是 $0$，剩余的位数则随便填。

可以发现对于每一次的最长公共前缀，符合要求的 $a_j$ 都在一个区间之内。于是用 `set` 维护所有 $a_i$，每次暴力 dfs 黑白染色，遇到奇环就报告非法。

但这样的复杂度是错的，每次都 `set` 暴力找相邻点的话一个点被访问的次数可能会很大（没仔细算）。

那么有没有每个点只访问一次的做法呢？

可以先不管奇环的事染色。染完色后，将所有数字按照颜色分成两个集合，检查每个集合中是否存在两个数异或值小于 $p$。

有一个结论：$a_1,a_2,\cdots a_m$ 两两异或的最小值一定等于将 $a_i$ 排序后，相邻数字异或的最小值，证明可以考虑放到 01-trie 来证。

这样就做完了，复杂度 $\mathcal{O}(n\log n\log^2 V)$。

```cpp
#include <bits/stdc++.h>
int n, a[200005], vis[200005], p;
std::set <int> s;
std::map <int, int> mp;
void dfs(int x, int y){
  if(vis[x]) return ;
  vis[x] = y;
  if(s.find(a[x]) != s.end()) s.erase(a[x]);
  int z = a[x]; int cur = 0;
  for(int w = 29; w >= 0; --w){
    if(p & (1 << w)){
      int tmp = cur + (z & (1 << w));
      int mx = tmp + (1 << w) - 1;
      auto it = s.lower_bound(tmp);
      while(it != s.end()){
        int c = *it;
        if(c == z){
          ++it;
          continue;
        }
        if(c > mx) break;
        s.erase(it);
        dfs(mp[c], 3 - vis[x]);
        it = s.lower_bound(tmp);
      }
    }
    cur += ((p & (1 << w)) ^ (z & (1 << w)));
  }
  return ;
}
int d[200005], tot = 0;
inline int check(){
  tot = 0;
  int mi = 2e9;
  for(int i = 1; i <= n; ++i)
    if(vis[i] == 1)
      d[++tot] = a[i];
  std::sort(d + 1, d + tot + 1);
  for(int i = 1; i <= tot - 1; ++i)
    mi = std::min(mi, d[i] ^ d[i + 1]);
  tot = 0;
  for(int i = 1; i <= n; ++i)
    if(vis[i] == 2)
      d[++tot] = a[i];
  std::sort(d + 1, d + tot + 1);
  for(int i = 1; i <= tot - 1; ++i)
    mi = std::min(mi, d[i] ^ d[i + 1]);
  return mi >= p;
}
int main(){
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) scanf("%d", &a[i]), mp[a[i]] = i;
  if(n <= 2){
    printf("10\n");
    return 0;
  }
  p = 0;
  for(int w = 29; w >= 0; --w){
    p ^= (1 << w);
    memset(vis, 0, sizeof vis);
    s.clear();
    for(int i = 1; i <= n; ++i) s.insert(a[i]);
    for(int i = 1; i <= n; ++i)
      if(!vis[i])
        dfs(i, 1);
    if(!check()) p ^= (1 << w);
  }
  memset(vis, 0, sizeof vis);
  s.clear();
  for(int i = 1; i <= n; ++i) s.insert(a[i]);
  for(int i = 1; i <= n; ++i)
    if(!vis[i])
      dfs(i, 1);
  for(int i = 1; i <= n; ++i)
    if(vis[i] == 1) printf("1");
    else printf("0");
  printf("\n");
  return 0;
}
```


---

## 作者：Aria_Math (赞：3)

首先有引理：一个集合两两异或的最小值就是排序后相邻两个数异或的最小值。这启示我们对排序后的 $a$ 考虑。

先二分答案，我们从前往后依次对序列划分，显然任意时刻我们只用考虑两个序列的最后那个数，注意到考虑到 $i$ 时 $a_i$ 一定是其中一个序列的最后，所以设 $f_{i,j}$ 表示此时另一个序列的最后一个数是 $j$ 是否可行。

转移显然：
- 把 $i+1$ 接在 $i$ 后面，此时需要 $a_i \operatorname{xor} a_{i+1} \ge mid$，$f_{i+1}$ 直接继承 $f_i$ 的整个集合。
- 把 $i+1$ 接在 $j$ 后面，此时需要 $j \operatorname{xor} a_{i+1} \ge mid$，在 $f_{i+1}$ 的集合中加入 $a_i$。

因为我们只需要判定是否存在 $j \operatorname{xor} a_{i+1} \ge mid$，所以使用 0-1 Trie 维护当前集合即可。

输出方案比较麻烦，我们从后往前考虑，找出任意一个可以转移到当前状态的状态，然后归纳构造即可，因此我们要保存所有 $f_i$，使用可持久化 0-1 Trie 即可。时间复杂度 $\mathcal{O}(n \log^2 V)$。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
struct Trie {
  int son[2], siz, id;
} t[N * 32];
int n, a[N], rt[N], cnt, pos[N], out[N];
map<int, int> id;
void Mdf(int &u, int val, int k = 30) {
  t[++cnt] = t[u], t[u = cnt].siz++, t[u].id = val;
  if(k == -1) return ;
  int x = val >> k & 1;
  Mdf(t[u].son[x], val, k - 1);
}
int Qry(int u, int val, int k = 30) {
  if(!u || k == -1) return 0;
  int x = (val >> k & 1) ^ 1;
  if(t[u].son[x]) return (1 << k) ^ Qry(t[u].son[x], val, k - 1);
  else return Qry(t[u].son[x ^ 1], val, k - 1);
}
int Qry1(int u, int val, int k = 30) {
  if(k == -1) return t[u].siz;
  return Qry1(t[u].son[val >> k & 1], val, k - 1);
}
bool Check(int mid) {
  for(int i = 1; i <= cnt; ++i)
    t[i].son[0] = t[i].son[1] = t[i].siz = t[i].id = 0;
  cnt = 0;
  for(int i = 1; i <= n; ++i) rt[i] = 0;
  Mdf(rt[1], 1 << 30); // 1 << 30 表示另一个集合为空
  for(int i = 2; i <= n; ++i) {
    if((a[i - 1] ^ a[i]) >= mid)
      rt[i] = rt[i - 1];
    if(Qry1(rt[i - 1], 1 << 30) || Qry(rt[i - 1], a[i]) >= mid)
      Mdf(rt[i], a[i - 1]);
    if(!t[rt[i]].siz) return 0;
  }
  return 1;
}
int Any(int u, int k = 30) {
  if(k == -1) return 0;
  if(t[u].son[0]) return Any(t[u].son[0], k - 1);
  else return (1 << k) ^ Any(t[u].son[1], k - 1);
}
int Qry2(int u, int lim, int ans, int cur, int k = 30) {
  if(k == -1) return cur;
  int p = (lim >> k & 1) ^ 1;
  int ret = 0;
  if(ans >> k & 1) 
    return Qry2(t[u].son[p], lim, ans, cur ^ (p << k), k - 1);
  else {
    if(t[u].son[p]) return t[t[u].son[p]].id;
    return Qry2(t[u].son[p ^ 1], lim, ans, cur ^ ((p ^ 1) << k), k - 1);
  }
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for(int i = 1; i <= n; ++i) 
    cin >> a[i], id[a[i]] = i;
  id[1 << 30] = -1;
  if(n == 2) return puts("01"), 0;
  sort(a + 1, a + n + 1);
  int l = 0, r = 1 << 30, ans = 0;
  while(l <= r) {
    int mid = (long long)l + r >> 1;
    if(Check(mid)) ans = mid, l = mid + 1;
    else r = mid - 1;
  }
  Check(ans);
  int now = n, lst[2] = {-1, -1}, k = 1;
  vector<int> seq[2];
  while(now > 0) {
    int pos;
    if(lst[k ^ 1] == -1) pos = Any(rt[now]);
    else pos = Qry2(rt[now], a[lst[k ^ 1]], ans, 0);
    if(pos >= (1 << 30)) pos = -1;
    for(int i = now; i && a[i] > pos; --i)
      out[id[a[i]]] = k, lst[k] = i, seq[k].push_back(a[i]);
    now = lst[k] - 1, k ^= 1;
  }
  for(int i = 1; i <= n; ++i)
    printf("%d", out[i]);
  return 0;
}
```

---

## 作者：Yansuan_HCl (赞：1)

其他题解咋都这么复杂的。来个 $O(n\log V)$ 简单做法。

从高到低考虑当前最高位 $i$ 是否为 1。能为 $1$ 当且仅当第 $i$ 位的 0、1 个数各不超过两个：此时可以枚举方案。

否则第 $i$ 位一定为 $0$。由于位 $i$ 不同的两个数异或没有贡献，分别向两侧递归子问题，取较小值即可。

显然可以归纳证明，对于集合大小 $> 2$ 的子问题答案不为 $\infty$。

[代码](https://codeforces.com/contest/1849/submission/303195719)

---

## 作者：xiezheyuan (赞：0)

## 简要题意

给定一个大小为 $n$ 的集合 $S$，你需要将其划分为两个集合，使得每一个集合的最小异或对的最小值最大，输出一组合法的方案。

$2\leq n\leq 2\times 10^5,0\leq S_i<2^{30}$。

## 思路

直觉上肯定有一个贪心：每次选出最小异或对，将其拆散，划分到不同的集合，无法操作为止。这个方法的正确性是显然的，因为每次都可以让答案严格减小。

但同时也可以发现一个问题：如何判断划分到哪一个集合？注意到出题人为什么不划分到 $k$ 个集合而是划分到两个集合中呢？故划分到两个集合一定有其特殊性质，那么不难联想到二分图。

对于两个元素 $(S_i,S_j)$，连边 $(i,j)$，边权为 $S_i\oplus S_j$，那么我们需要找一个导出二分子图，使得每个颜色划分成一个集合，答案最大。不过导出二分图我们不大熟悉，而生成树我们熟悉，又因为树已经可以确定染色方法了，因此可以考虑最小生成树。

为什么最小生成树就足够了呢？因为 Kruskal 的过程就是我们的贪心啊！

现在我们只需要求出这个完全图的最小生成树，然后染色就可以得到答案。

如何求出最小生成树？不妨使用 Boruvka 算法，使用可合并的 01 trie 维护。时间复杂度 $O(n\log n\log V)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, a[N];

template<int N>
struct trie {
    int trie[N][2], siz[N], idt[N], tot;

    void insert(int u, int x, int id){
        for(int i=29;~i;i--){
            bool t = (x >> i) & 1;
            if(!trie[u][t]) trie[u][t] = ++tot;
            u = trie[u][t], siz[u]++;
        }
        idt[u] = id;
    }

    pair<int,int> query(int u, int v, int x){
        int val = 0;
        for(int i=29;~i;i--){
            bool t = (x >> i) & 1;
            if(siz[trie[u][t]] - siz[trie[v][t]]) u = trie[u][t], v = trie[v][t];
            else u = trie[u][t ^ 1], v = trie[v][t ^ 1], val |= 1 << i;
        }
        return {idt[u], val};
    }

    int merge(int x, int y){
        if(!x || !y) return x | y;
        trie[x][0] = merge(trie[x][0], trie[y][0]);
        trie[x][1] = merge(trie[x][1], trie[y][1]);
        siz[x] = siz[trie[x][0]] + siz[trie[x][1]];
        idt[x] |= idt[y];
        return x;
    }
};

using i64 = long long;
trie<N << 6> t;
int rt[N];
int fa[N], tag[N], wgt[N];
pair<int,int> edg[N];
bool bel[N];
vector<int> g[N];

int find(int x){ return fa[x] == x ? fa[x] : find(fa[x]); }

void boruvka(){
    iota(fa + 1, fa + n + 1, 1);
    bool flag = 1;
    while(flag){
        flag = 0;
        fill(wgt + 1, wgt + n + 1, INT_MAX);
        for(int i=1;i<=n;i++){
            int fx = find(i);
            auto [y, w] = t.query(rt[0], rt[fx], a[i]);
            if(!y) continue;
            int fy = find(y);
            if(wgt[fx] > w) tag[fx] = fy, wgt[fx] = w, edg[fx] = {i, y};
        }
        for(int i=1;i<=n;i++){
            if(wgt[i] != INT_MAX && find(i) != find(tag[i])){
                rt[find(i)] = t.merge(rt[find(i)], rt[find(tag[i])]);
                fa[find(tag[i])] = find(i), flag = 1;
                g[edg[i].first].push_back(edg[i].second);
                g[edg[i].second].push_back(edg[i].first);
            }
        }
    }
}

void dfs(int u, int fa){
    bel[u] = !bel[fa];
    for(int v : g[u]){
        if(v != fa) dfs(v, u);
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    rt[0] = ++t.tot;
    for(int i=1;i<=n;i++){
        t.insert(rt[i] = ++t.tot, a[i], i);
        t.insert(rt[0], a[i], i);
    }
    boruvka(), dfs(1, 0);
    for(int i=1;i<=n;i++) cout << bel[i];
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：Little09 (赞：0)

依次考虑答案的每一位，考虑当前位能否填 $1$。假设当前答案是 $x$，考虑一个暴力是将满足 $a_i\text{ xor } a_j<x$ 的连边，判断其是否形成二分图，若不形成二分图，则 $x$ 不合法，否则合法。这样做是因为考虑 $a_i\text{ xor } a_j< x$ 的情况，必须要 $i,j$ 不在相同集合里。

我们维护若干个集合。每次先把每个集合按照当前位是 $0$ 和当前位是 $1$ 分裂。考虑怎么判断当前位能否填 $1$ 呢？注意到填 $1$ 相当于当前维护的集合内部全部连边，那么显然如果有集合大小超过 $3$ 就非法了，否则我们用并查集做二分图判定，假设连上边之后看一下是否还是二分图，如果是二分图就可以填 $1$，否则不可以。

如果当前位置填的是 $0$，那么考虑每个集合里当前位是 $0$ 和当前位是 $1$ 的之间永远不能连边，所以保持刚才的分裂。如果当前填的是 $1$，那么我们需要将刚才分裂的集合合并回去，因为当前位是 $0$ 和当前位是 $1$ 的之间能否连边需要看接下来的位。

我们直接维护上述过程，可以做到 $O(n\log n\log V)$ 的复杂度。

---

