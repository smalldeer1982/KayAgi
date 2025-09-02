# Labeling the Tree with Distances

## 题目描述

You are given an unweighted tree of $ n $ vertices numbered from $ 1 $ to $ n $ and a list of $ n-1 $ integers $ a_1, a_2, \ldots, a_{n-1} $ . A tree is a connected undirected graph without cycles. You will use each element of the list to label one vertex. No vertex should be labeled twice. You can label the only remaining unlabeled vertex with any integer.

A vertex $ x $ is called good if it is possible to do this labeling so that for each vertex $ i $ , its label is the distance between $ x $ and $ i $ . The distance between two vertices $ s $ and $ t $ on a tree is the minimum number of edges on a path that starts at vertex $ s $ and ends at vertex $ t $ .

Find all good vertices.

## 说明/提示

This is the tree for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1794E/f54192bbd4a09409727069f5296c3b8069512eac.png)And these are two possible labelings with the elements on the list so that $ 2 $ is a good vertex (left) and $ 4 $ is a good vertex (right).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1794E/e87e5306fe63a198bad6dafe8ce7c0bd63e8d99b.png)The square below each vertex represents its label. The black squares contain the numbers which were on the given list and the only white square contains the only number which was not on the given list.

In the second example, the only good vertex is vertex $ 3 $ .

In the third example, there are no good vertices.

## 样例 #1

### 输入

```
6
2 1 0 1 2
1 2
2 3
2 4
4 5
4 6```

### 输出

```
2
2 4```

## 样例 #2

### 输入

```
5
1 2 1 2
1 2
3 2
3 4
5 4```

### 输出

```
1
3```

## 样例 #3

### 输入

```
3
2 2
1 2
2 3```

### 输出

```
0```

# 题解

## 作者：小木虫 (赞：7)

### Preface  
一道好的换根与哈希相结合的题目。  
### Problem  
给你一棵 $n$ 个点的无根树，树上初始无权值，给你一个大小为 $n-1$ 的可重集 $S$。  

定义一个点 $u$ 是好的，当且仅当你可以用 $S$ 内的数填充树上的 $n-1$ 个点，使得每个被填充的点 $v$ 的权值是 $u$ 到 $v$ 的树上距离。  

请你输出所有的好点。
### Solution  
你发现，如果 $u$ 点为树根，那么每个点的深度就是可以被填的权值。  
让我们先不考虑那剩下的一个点，如果 $S$ 的大小是 $n$，这个题应该怎么解决？  
很显然，就是当 $u$ 为根的时候，如果所有点的深度集合等于 $S$，$u$ 就是好点。  
这启示我们使用哈希来解决这个问题。  
我们考虑哈希函数 $H$：  
$$H=cnt_1+cnt_2\times base+cnt_3\times base^2.....cnt_{n-1}\times base^{n-2} \mod p$$  
这其实是一种字符串哈希的形式，只不过字符集很大，当你的 $base$ 大于 $n$ 的时候这个哈希的碰撞率和字符串哈希一样是正确的，同时进行多次哈希就近乎可以保证正确。  

那么我们现在可以 $O(1)$ 对比集合了，现在的问题是我们不能对每一个点都钦定一次根，这样是 $O(n^2)$ 的，和没有哈希是一样的。  

我们先钦定 1 为根。

哈希值是方便我们换根的，我们发现对于这个哈希函数，换根是很方便的，具体来说，设 $fa$ 为 $u$ 的根，v 为 $u$ 的儿子。  
当我们要去到 $v$ 的时候，$H_u=H_u-H_v\times base$。  
当我们要回到 $u$ 的时候，$H_u=H_u+H_v\times base$。  
当我们刚到达 $u$ 的时候，$H_u=H_u+H_{fa}\times base$。  
当我们要离开 $u$ 的时候，$H_u=H_u-H_{fa}\times base$。  

接下来，我们要解决那个剩下的一个点的问题。  
你发现，这个点造成的影响可以是 $base$ 的小于 $n$ 的任意次数，所以你可以先预处理出 $base$ 的各个幂次，到时候直接观察 $Hash_{S}-H_u$ 是否是一个幂次，这个可以用 map 或者 set 做到。

然后我们到每个点的时候进行 $O(1)$ 比对，多次哈希后得到答案，复杂度 $O(n\log n)$：  
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,a[N],b[N],u,v,res[N],Hash[N],tar;
vector <int> edge[N];map <int,int> table;
void getHash(int u,int fa,const int base,const int mod){
	Hash[u]=0;
	for(auto v:edge[u]){
		if(v==fa)continue;
		getHash(v,u,base,mod);
		Hash[u]+=Hash[v]*base;
		Hash[u]%=mod;
	}Hash[u]=(Hash[u]+1)%mod;
	//if(!fa)cout<<u<<" "<<Hash[u]<<endl;
}
void dfs(int u,int fa,const int base,const int mod){
	Hash[u]=(Hash[u]+Hash[fa]*base)%mod;
	//cout<<u<<" "<<tar<<" "<<Hash[u]<<" "<<(Hash[u]-tar+mod)%mod<<endl;
	if(table[(Hash[u]-tar+mod)%mod])
		res[u]++;
	for(auto v:edge[u]){
		if(v==fa)continue;
		Hash[u]=(Hash[u]-Hash[v]*base%mod+mod)%mod;
		dfs(v,u,base,mod);
		Hash[u]=(Hash[u]+Hash[v]*base%mod)%mod;
	}Hash[u]=(Hash[u]-Hash[fa]*base%mod+mod)%mod;
}
void solve(const int mod,const int base){tar=0;
	for(int i=0;i<n;i++)b[i]=0;
	for(int i=1;i<n;i++)b[a[i]]++;
	table.clear();int now=1;
	for(int i=0;i<n;i++){
		//cout<<now<<endl;
		table[now]=1;
		tar=(tar+b[i]*now)%mod;
		now*=base;now%=mod;
	}getHash(1,0,base,mod);
	dfs(1,0,base,mod);
}mt19937 rnd(time(0));
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++)cin>>a[i];
	for(int i=1;i<n;i++)
		cin>>u>>v,edge[u].push_back(v),edge[v].push_back(u);
	solve(998244353,n+rnd()%n);
	solve(1000000007,n+rnd()%n);
	solve(1000000009,n+rnd()%n);
	vector <int> ans;
	for(int i=1;i<=n;i++)
		if(res[i]==3)ans.push_back(i);
	cout<<ans.size()<<"\n";
	for(auto now:ans)cout<<now<<" ";
	return 0;
}
```


---

## 作者：CuCl4Loliko (赞：3)

### Problem

给你一棵 $n$ 个节点的树，以及 $n-1$ 个权值，树上有一个好点，每个节点的权值定义为这个节点到好点的最短距离，求哪些节点作为好节点时其他节点的权值集合包含初始给定的权值集合。

### Solution

很好的换根题。

如果我们钦定了一个好节点并以此为根，那么其他节点的权值就是它们的深度。考虑进行换根 / 二次扫描法，快速求出以所有节点为根时，整棵树的深度集合。

设 $cnt_i$ 为深度为 $i$ 的节点出现的数量，那么这个 $cnt$ 数组就可以表示整棵树的深度集合。考虑对这个 $cnt$ 数组进行哈希，便可以 $O(1)$ 比较当前深度集合与题目所给的深度集合是否相符。若相符，两集合哈希值相减应当剩余一个哈希 $base$ 的某个幂次，因为我们求出的集合是 $n$ 个点的深度，而题目所给的是 $n-1$ 个点的深度。

如何换根？

设 $f_u$ 表示以节点 $u$ 为根的子树内的深度哈希值，那么

$$f_u = base + f_v \times base$$

这样写的哈希值是支持差分的，可以随意减去一个子树的哈希值。
设 $g_u$ 表示以节点 $u$ 为根的子树外的深度哈希值，那么

$$g_v = (f_u - f_v \times base + g_u) \times base$$

正常的换根套路，两遍 DFS 即可，注意取模。

题目比较毒瘤，我 $base$ 用的 20200721，写了双模哈希才能过。

### Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
int base=20200721,MOD;
struct egde{
	int to,nxt;
}e[maxn<<1];
int head[maxn],_;
void adde(int u,int v)
{
	e[++_].nxt=head[u];
	e[_].to=v;
	head[u]=_;
}

int qpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1) res=res*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return res;
}

map<int,int>ans;
int f[maxn],g[maxn],target,a[maxn];
set<int>S;
int cnt,n;
int out[maxn];

void dfs1(int u,int fa)
{
	f[u]=base;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dfs1(v,u);
		f[u]=(f[u]+f[v]*base)%MOD;
	}
}

void dfs2(int u,int fa)
{
	int now=(f[u]+g[u])%MOD;
	if(S.find((now-target+MOD)%MOD)!=S.end())
		ans[u]++;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		g[v]=(f[u]-f[v]*base%MOD+g[u]+MOD)%MOD*base%MOD;
		dfs2(v,u);
	}
}

signed main()
{
	cin>>n;
	for(int i=1;i<n;i++)
		cin>>a[i];
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		adde(u,v);
		adde(v,u);
	}
	MOD=1e9+7;
	for(int i=1;i<n;i++)
		target=(target+qpow(base,a[i]+1))%MOD;
	for(int i=1,j=base;i<=n+1;i++,j=j*base%MOD)
		S.insert(j);
	dfs1(1,0);
	dfs2(1,0);
	MOD=1e9+7;
	S.clear();
	target=0;
	for(int i=1;i<n;i++)
		target=(target+qpow(base,a[i]+1))%MOD;
	for(int i=1,j=base;i<=n+1;i++,j=j*base%MOD)
		S.insert(j);
	dfs1(1,0);
	dfs2(1,0);
	for(int i=1;i<=n;i++)
		if(ans[i]==2) out[++cnt]=i;
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)
		cout<<out[i]<<" ";
	return 0;
}
```

---

