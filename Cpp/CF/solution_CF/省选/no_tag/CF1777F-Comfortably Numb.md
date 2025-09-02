# Comfortably Numb

## 题目描述

You are given an array $ a $ consisting of $ n $ non-negative integers.

The numbness of a subarray $ a_l, a_{l+1}, \ldots, a_r $ (for arbitrary $ l \leq r $ ) is defined as $\max(a_l, a_{l+1}, \ldots, a_r) \oplus (a_l \oplus a_{l+1} \oplus \ldots \oplus a_r)$, where  $\oplus$ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Find the maximum numbness over all subarrays.

## 说明/提示

For the first test case, for the subarray $ [3, 4, 5] $ , its maximum value is $ 5 $ . Hence, its numbness is $ 3 \oplus 4 \oplus 5 \oplus 5 $ = $ 7 $ . This is the maximum possible numbness in this array.

In the second test case the subarray $ [47, 52] $ provides the maximum numbness.

## 样例 #1

### 输入

```
2
5
1 2 3 4 5
3
10 47 52```

### 输出

```
7
47```

# 题解

## 作者：Masterwei (赞：7)

看到有最值，容易想到最大值分治。

我们可以用一个单调栈求出每一个值成为最大值的区间，然后我们可以枚举短的那一边，再通过可持久化 `trie` 算出对应贡献。最后取最大的即可。

最大值分治的时间复杂度为 $O(n\log n)$，套一个 `trie`，时间两只 $\log$。


```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=2e5+5,W=30;
int n,a[Maxn],sum[Maxn];
int stk[Maxn],len;
int l[Maxn],r[Maxn];
int root[Maxn],cnt;
struct trie{
	int ls,rs,data;
}t[Maxn*50];
void insert(int&x,int y,int w,int a){
	x=++cnt;t[x]=t[y];
	t[x].data++;if(w<0)return;
	if((a>>w)&1)insert(t[x].rs,t[y].rs,w-1,a);
	else insert(t[x].ls,t[y].ls,w-1,a);
}
int query(int x,int y,int w,int a){
	if(w<0)return 0;
	if((a>>w)&1){
		if(t[t[x].ls].data-t[t[y].ls].data>0)return query(t[x].ls,t[y].ls,w-1,a)+(1<<w);
		return query(t[x].rs,t[y].rs,w-1,a);
	}
	if(t[t[x].rs].data-t[t[y].rs].data>0)return query(t[x].rs,t[y].rs,w-1,a)+(1<<w);
	return query(t[x].ls,t[y].ls,w-1,a);
}
inline void solve(){
	n=read();int ans=0;
	for(int i=0;i<=cnt;i++)t[i]={0,0,0};
	cnt=0;len=0;
	for(int i=1;i<=n;i++){
		a[i]=read();r[i]=0;
		sum[i]=sum[i-1]^a[i];insert(root[i],root[i-1],W,sum[i]);
		while(len&&a[stk[len]]<=a[i]){
			r[stk[len]]=i-1;len--;
		}l[i]=stk[len]+1;
		stk[++len]=i;
	}
	for(int i=1;i<=n;i++){
		if(!r[i])r[i]=n;
//		printf("%d:%d %d\n",i,l[i],r[i]);
		if(i-l[i]<r[i]-i){
			for(int j=l[i];j<=i;j++)ans=max(ans,query(root[r[i]],root[i-1],W,sum[j-1]^a[i]));
		}else{
			for(int j=r[i];j>=i;j--){
				if(l[i]==1)ans=max(ans,sum[j]^a[i]);
				ans=max(ans,query(root[i-1],root[max(0,l[i]-2)],W,sum[j]^a[i]));
			}
		}
	}printf("%d\n",ans);
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int T=read();
	while(T--)solve();
	return 0;
}

```

---

## 作者：Ginger_he (赞：5)

考虑分治，对于一个分治区间 $[l,r]$，设其分治中心为 $mid$，不妨设最大值在右区间 $[mid+1,r]$ 中，在左区间时同理。

维护一个指针 $i$ 表示右端点，同时维护一个指针 $j$ 表示左端点最左能取到的位置（指针 $j$ 需要满足 $\max\limits_{k=j}^{mid}a_k\le \max\limits_{k=mid+1}^ia_k$）。先预处理出分治区间 $[l,r]$ 的异或前缀和 $s$，那当左端点固定时问题就转化为求 $s_i\oplus\max\limits_{k=mid+1}^ia_k$ 与 $s_{j-1},s_j,\dots,s_{mid-1}$ 中某个数异或的最大值，前者为定值，直接上 trie 树即可，时间复杂度 $O(n\log n\log V)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 200005
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int T,n,rt,cnt,a[N],f[N],t[N<<9][2],ans;
inline void insert(int x)
{
	int p=rt;
	for(int i=30;~i;i--)
	{
		int k=(x>>i)&1;
		if(!t[p][k]) t[p][k]=++cnt;
		p=t[p][k];
	}
}
inline int query(int x)
{
	int p=rt,res=0;
	for(int i=30;~i;i--)
	{
		int k=(x>>i)&1;
		if(t[p][k^1]) res^=(1<<i),p=t[p][k^1];
		else p=t[p][k];
	}
	return res;
}
void solve(int l,int r)
{
	if(l==r) return;
	int mid=l+r>>1,p=0;
	solve(l,mid),solve(mid+1,r);
	rt=++cnt,f[l-1]=0;
	for(int i=l;i<=r;i++) f[i]=f[i-1]^a[i];
	for(int i=mid+1,j=mid+1;i<=r;i++)
	{
		p=max(p,a[i]);
		while(j>l&&a[j-1]<=p) j--,insert(f[j-1]);
		ans=max(ans,query(f[i]^p));
	}
	rt=++cnt,p=f[r+1]=0;
	for(int i=r;i>=l;i--) f[i]=f[i+1]^a[i];
	for(int i=mid,j=mid;i>=l;i--)
	{
		p=max(p,a[i]);
		while(j<r&&a[j+1]<p) j++,insert(f[j+1]);
		ans=max(ans,query(f[i]^p));
	}
}
int main()
{
	T=read();
	while(T--)
	{
		cnt=ans=0,n=read();
		for(int i=1;i<=(n<<9);i++) t[i][0]=t[i][1]=0;
		for(int i=1;i<=n;i++) a[i]=read();
		solve(1,n);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：ExplodingKonjac (赞：4)

**[【原题链接】](https://www.luogu.com.cn/problem/CF1777F)**

## 题目分析

首先把序列做一遍前缀异或和得到数组 $s$，把连续的异或和变成两个数异或和。因为式子里有个最大值，对原序列建笛卡尔树，统计固定最大值的答案。

考虑固定最大值 $a_u$，左右儿子分别为 $lc,rc$，$u$ 子树对应序列上的区间为 $[L,R]$。那么最大值为 $a_u$ 的区间就是左端点在 $[L,u]$ 里，右端点在 $[u,R]$ 里的区间。符合这些条件的区间的区间异或和，相当于在 $[L-1,u-1]$ 内选一个 $x$，$[u,R]$ 内选一个 $y$ 得到的 $s_x\oplus s_y$。

这个问题有一个比较套路的解决办法：我们可以对于每个节点 $v$（对应序列的区间 $[l,r]$） ，维护一个 $\text{01-Trie}$，储存 $i\in[l-1,r]$ 的 $s_i$。维护方式是直接把左右儿子的 $\text{Trie}$ 合并，再加上自己。

然后，我们可以枚举左儿子的 $s_i$，在右儿子的 $\text{Trie}$ 上查询，也就是求 $\max_{u\le j\le R}\{a_u\oplus s_i\oplus s_j\}$，这就是一个经典问题了。然而这么做枚举量可以达到 $O(n^2)$。但是只需把枚举左儿子的 $s_i$ 改成枚举 $siz$ 较小的儿子的 $s_i$，就可以把枚举量优化到 $O(n\log n)$，复杂度分析方式和启发式合并一样。

总复杂度 $O(n\log^2n)$。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

// 快读

using LL=long long;
using LD=long double;
using UI=unsigned int;
using ULL=unsigned long long;

int T,n,ans,a[200005],sum[200005],lc[200005],rc[200005];
int top,st[200005];
void build()
{
	int k=top=0;
	for(int i=1;i<=n;i++)
	{
		k=top;
		while(k && a[st[k]]<a[i]) k--;
		if(k) rc[st[k]]=i;
		if(k<top) lc[i]=st[k+1];
		st[top=++k]=i;
	}
}
struct TrieNode{ int ch[2]; }t[6000005];
int cnt,rt[200005];
void insert(int x,int &r)
{
	if(!r) r=++cnt;
	for(int i=30,u=r;i>=0;i--)
	{
		bool v=(x>>i)&1;
		if(!t[u].ch[v])
			t[u].ch[v]=++cnt;
		u=t[u].ch[v];
	}
}
int merge(int x,int y)
{
	if(!x || !y) return x|y;
	t[x].ch[0]=merge(t[x].ch[0],t[y].ch[0]);
	t[x].ch[1]=merge(t[x].ch[1],t[y].ch[1]);
	return x;
}
int query(int x,int &r)
{
	if(!r) return x;
	int res=0;
	for(int i=30,u=r;i>=0;i--)
	{
		bool v=(x>>i)&1;
		res<<=1;
		if(t[u].ch[v^1]) u=t[u].ch[v^1],res++;
		else u=t[u].ch[v^0];
	}
	return res;
}
int siz[200005],L[200005],R[200005];
void dfs(int u)
{
	if(!u) return;
	dfs(lc[u]),dfs(rc[u]);
	int vl=lc[u],vr=rc[u];
	siz[u]=siz[vl]+siz[vr]+1,L[u]=R[u]=u;
	if(vl) L[u]=L[vl];
	if(vr) R[u]=R[vr];
	if(siz[vl]>siz[vr]) swap(vl,vr);
	if(vl) for(int i=L[vl]-1;i<=R[vl];i++) ans=max(ans,query(a[u]^sum[i],rt[vr]));
	else if(vr) ans=max(ans,query(a[u]^(vr==lc[u]?sum[u]:sum[u-1]),rt[vr]));
	rt[u]=merge(rt[lc[u]],rt[rc[u]]);
	insert(sum[u],rt[u]),insert(sum[u-1],rt[u]);
}
int main()
{
	qin>>T;
	while(T--)
	{
		qin>>n;
		for(int i=1;i<=n;i++) qin>>a[i],sum[i]=sum[i-1]^a[i];
		ans=0,build(),dfs(st[1]);
		qout.writeln(ans);
		for(int i=1;i<=n;i++) lc[i]=rc[i]=0,rt[i]=0;
		for(int i=1;i<=cnt;i++) t[i].ch[0]=t[i].ch[1]=0;
		cnt=0;
	}
	return 0;
}
```


---

## 作者：DaiRuiChen007 (赞：4)

# CF1777F 题解



## 思路分析

考虑建立笛卡尔树，得到每个 $a_i$ 作为区间最大值时，区间左右端点的范围。

我们的思路就是枚举其中一个端点，用 01-Trie 维护异或前缀和求解，记 $sum_i=\oplus_{j=1}^i a_j$，即异或意义下的前缀和。

接下来我们假设区间为 $[l,r]$，最大值在 $x$ 上，我们可以分类讨论枚举区间的左端点还是右端点：

- 若 $x-l+1\le r-x+1$，枚举左端点 $i$，等价于在 $sum_x\sim sum_r$ 中找到和 $a_x\oplus sum_{i-1}$ 异或最大的。
- 若 $x-l+1>r-x+1$，枚举右端点 $i$，等价于在 $sum_{l-1}\sim sum_{x-1}$ 中找到和 $a_x\oplus sum_i$ 异或最大的。

注意到这两个问题就是可持久化 01-Trie 的模板，因此用可持久化 01-Trie 回答这些问题即可。

在笛卡尔树上，我们每次枚举其非重儿子的全部子树，因此每个点 $i$ 被枚举的次数等价于其到根的轻边数量，由于每次经过一条轻边，其所在子树大小至少 $\times 2$，因此每个点至多被枚举 $\log_2 n$ 次（这部分的复杂度分析和 DSU on Tree 是相同的）。

时间复杂度 $\Theta(n\log n\log w)$，$w$ 为 $\{a_i\}$ 的值域。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
struct node {
	int son[2],cnt;
	node() { son[0]=son[1]=0,cnt=0; }
	inline int& operator [](const int &i) { return son[i]; }
}	tr[MAXN*35];
int siz;
inline int bit(int x) { return 1<<x; }
inline int dig(int x,int d) { return (x>>d)&1; }
inline void insert(int x,int d,int pre,int now) {
	if(d<0) return ;
	int c=dig(x,d);
	tr[now][c^1]=tr[pre][c^1];
	tr[now][c]=++siz;
	tr[tr[now][c]].cnt=tr[tr[pre][c]].cnt+1;
	insert(x,d-1,tr[pre][c],tr[now][c]);
}
inline int query(int x,int d,int l,int r) {
	if(d<0) return 0;
	int c=dig(x,d);
	if(tr[tr[r][c^1]].cnt-tr[tr[l][c^1]].cnt>0) {
		return (1<<d)|query(x,d-1,tr[l][c^1],tr[r][c^1]);
	}
	return query(x,d-1,tr[l][c],tr[r][c]);
}
int a[MAXN],sum[MAXN],root[MAXN],f[MAXN][20];
inline int pos(int l,int r) {
	int k=__lg(r-l+1);
	return (a[f[l][k]]>a[f[r-bit(k)+1][k]])?f[l][k]:f[r-bit(k)+1][k];
}
inline int dfs(int l,int r) {
	if(l>=r) return 0;
	int mid=pos(l,r);
	int ans=max(dfs(l,mid-1),dfs(mid+1,r));
	if((r-mid+1)<(mid-l+1)) {
		for(int i=mid;i<=r;++i) {
			ans=max(ans,query(sum[i]^a[mid],31,(l==1)?0:root[l-2],root[mid-1]));
		}
	} else {
		for(int i=l;i<=mid;++i) {
			ans=max(ans,query(sum[i-1]^a[mid],31,root[mid-1],root[r]));
		}
	}
	return ans;
}
inline void solve() {
	for(int i=0;i<=siz;++i) tr[i]=node();
	siz=0;
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),sum[i]=sum[i-1]^a[i];
	for(int i=0;i<=n;++i) {
		root[i]=++siz;
		insert(sum[i],31,((i==0)?0:root[i-1]),root[i]);
	}
	for(int i=1;i<=n;++i) f[i][0]=i;
	for(int k=1;k<20;++k) {
		for(int i=1;i+bit(k-1)<=n;++i) {
			f[i][k]=(a[f[i][k-1]]>a[f[i+bit(k-1)][k-1]])?f[i][k-1]:f[i+bit(k-1)][k-1];
		}
	}
	printf("%d\n",dfs(1,n));
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：wcyQwQ (赞：2)

考虑分治，记当前分治区间为 $[l, r]$，首先我们记 $m$ 为 $[l, r]$ 中最大值位置，现在我们要求的就是 $\max_{i \in [l, m], j \in[m, r]} \{a_m \oplus s_{i - 1} \oplus s_j\}$，其中 $s$ 为前缀异或和。我们枚举 $i, j$ 其中一个都可以用可持久化 Trie 做到 $O(\log V)$ 计算，如果我们随机枚举一半可能会被卡成 $O(n^2\log V)$ 的，在这里我们每次枚举长度较小的区间就能做到 $O(n\log n\log V)$。

[Code](https://codeforces.com/contest/1777/submission/224307434)



---

## 作者：_Yonder_ (赞：1)

首先看到贡献涉及到最大值，考虑最值分治。最值分治就是每次分治时以最大值的位置为断点分治下去。

接着我们用异或前缀和简化式子，这时式子可变为 $c_y\oplus c_{x-1}\oplus\max(a_l, a_{l+1}, \ldots, a_r)$。由于最大值已经固定，枚举其中一边，求在剩下一边的最大异或值就可以用 Trie 了。

最值分治经典 trick：分治时，每次固定枚举一边算贡献必然会超时，于是我们每次枚举长度小的一边算贡献。我们知道分治最终会递归到长度为 $1$，回溯往上时可以看成启发式合并。

时间复杂度 $O(n\log^2 n)$。
# Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+5;
int root[N];
struct Trie{
	int son[N*35][2],sum[N*35],cnt;
	inline void clear(){for(int i=1;i<=cnt;i++) son[i][0]=son[i][1]=sum[i]=0;cnt=0;}
	inline void copy(int &x,int y){x=++cnt;son[x][0]=son[y][0],son[x][1]=son[y][1],sum[x]=sum[y]+1;}
	inline void add(int x,int &p,int r){copy(p,r);int l=p;for(int i=31,u;~i;i--) u=x>>i&1,copy(son[l][u],r=son[r][u]),l=son[l][u];}
	inline int ask(int x,int l,int r){int ans=0;for(int i=31,u;~i;i--) u=x>>i&1,u^=(sum[son[l][u^1]]-sum[son[r][u^1]]>0),l=son[l][u],r=son[r][u],ans+=(x>>i&1^u)<<i;return ans;}
}Trie;
int T,n,a[N],st[N][20],lg[N],sum[N],ans;
inline int ask(int l,int r){int u=lg[r-l+1];return a[st[l][u]]>a[st[r-(1<<u)+1][u]]?st[l][u]:st[r-(1<<u)+1][u];}
inline void solve(int l,int r){
	if(l>=r) return;int m=ask(l,r);solve(l,m-1),solve(m+1,r);
	if(m-l<=r-m) for(int i=l;i<=m;i++) ans=max(ans,Trie.ask(sum[i-1]^a[m],root[r],root[m-1]));
	else for(int i=m;i<=r;i++) ans=max(ans,Trie.ask(sum[i]^a[m],root[m-1],l==1?0:root[l-2]));
}
int main(){
	std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	lg[0]=-1;for(int i=1;i<N;i++) lg[i]=lg[i>>1]+1,st[i][0]=i;
	cin>>T;
	while(T--){
		cin>>n;ans=0;Trie.clear();
		for(int i=1;i<=n;i++) cin>>a[i],sum[i]=sum[i-1]^a[i];
		for(int j=1;j<=lg[n];j++)
			for(int i=1;i+(1<<j)-1<=n;i++)
				st[i][j]=a[st[i][j-1]]>a[st[i+(1<<j-1)][j-1]]?st[i][j-1]:st[i+(1<<j-1)][j-1];
		for(int i=0;i<=n;i++) Trie.add(sum[i],root[i],i?root[i-1]:0);
		solve(1,n);cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：1)

upd on 23-8-26：修改了一段不恰当的描述。

+ 约定：$\oplus $ 表示按位异或。

第一步转化是经典的，区间异或转异或前缀和。设前缀异或数组为 $s$，则 $a_l\oplus a_{l+1}\oplus \cdots\oplus a_r=s_r\oplus s_{l-1}$。

既然涉及到最大值，我们不如先确定 $a_i$ 作为最大值时，这个区间的左右端点最远到达的是哪里，分别设为 $L_i,R_i$。

那么我们要求出的是 $\max{s_r\oplus s_l-1}(l\in [L_i-1,i-1], r\in[i, R_i])$。

最大异或的常用技巧是 0-1 trie。具体的，显然的，贪心的会取较高位，所以在 0-1 trie 上尽可能往与参数这一位不同的那一侧跳。这必然是最优的。

而对于这题，即使枚举了 $r\in[i,R_i]$，传统的 0-1 trie 也难以解决区间查询的问题。如果我们能求出从 $s_{L_i-1}$ 到 $s_{i-1}$ 这些数的 0-1 trie 就好了。

如何快速构造这棵树？显然，异或满足可减性，那么我们构造一颗前缀的可持久化 trie 树，每次查询时，我们发现需要考虑跳到了 $L_i-1$ 左边的情况。如何解决？

先看比较简单的可持久化 0-1 trie 的构造过程（假设依次加入 $(001)_2,(101)_2,(010)_2$ 三个数）。设 $rt$ 表示每颗树的根节点。

![](https://cdn.luogu.com.cn/upload/image_hosting/2j5e1wz6.png)

比如这个图，加入了 $(001)_2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/jd0e9o8s.png)

此时加入第二个数，注意这里有两个指针在跳，我们设为 $x,y$。

初始时，$x\gets rt_{i-1}$，$y\gets rt_i$。

先对于 $y$ 的 $1$ 这条边建立一个新的节点，然后 $0$ 就连到 $x$ 的。此时 $y$ 跳到了 $6$ 号，而 $x$ 直接空了。

![](https://cdn.luogu.com.cn/upload/image_hosting/wl2juyc5.png)

考虑加入第三个，先新建 $10$ 号节点作为 $0$ 边，$1$ 边连到上一个的 $6$ 号节点。注意此时 $x,y$ 指针的变化。

$y$ 从 $0$ 边出去了，$x$ 向 $0$ 边走的话，走到了 $2$ 号节点；而第二位建立 $0$ 边时，就连到 $3$ 上面了。

这样一颗 0-1 trie，我们发现从某个 $rt_i$ 开始遍历，显然是可以遍历出 $s_1\sim s_i$ 的。

但是这不足以解决限制的左端点最远点的情况。而限制左端点的情况，只需要将 $rt_r$ 和 $rt_l$ 两棵树相减即可。

至此，我们已经可以处理最大异或的问题，如果我们枚举 $l,r$ 中量级较小的一个，另一个交给可持久化 0-1 trie 处理，就能解决这个题。但是复杂度如何保证？

考虑每个点对于复杂度有怎么样的贡献，每次处理一个 $i$ 相当于合并 $[L_i-1,i-1]$ 和 $[i, R_i]$（因为你考虑 $R_i+1$ 若存在其的 $L$ 显然是会至少囊括到 $L_i$ 的），而枚举 $l,r$ 中量级较小的一个，自然每次区间长度相当于至少翻一番。每个点对于复杂度的贡献是 $\log n$ 的，所以总共是 $n\log n\log V$。

$L_i$ 和 $R_i$ 的求解是非常简单的，两个单调栈前后各跑一次即可。注意一种比较极端的情况，即 $a_i$ 全部相等，如何处理？如果单纯的使用单调栈，会出现全部 $[1,n]$ 的情况，复杂度直接寄了。

为什么复杂度会寄？因为每次都会遍历小的一边复杂度退化了。我们加入第二维位置参与单调栈，对于全等的情况跑出来的 $L_i=1$，$R_i=i$，复杂度就不会寄掉了。

为什么不会出现漏解的情况？当某个连续段全相等的时候，我们枚举到最右端时，可以“跨过”这一个连续段向左边向右边扩展。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
const int N=2e5+5, K=30;
pair<int, int> c[N]; int pre[N], a[N], rt[N], q[N], l[N], r[N], mx[N], t[N*K*3][2], cnt[3*N*K];
int i, j, k, n, tq, tp, tot, ret;
inline void insert(int now, int lst, int dep, int val)
{
	if(dep<0) return ;
	int w=(val>>dep)&1;
	t[now][!w]=t[lst][!w]; t[now][w]=++tot;
	cnt[t[now][w]]=cnt[t[lst][w]]+1; insert(t[now][w], t[lst][w], dep-1, val);
	return ;
}
inline int query(int lmt, int id, int dep, int val)
{
	if(dep<0) return 0;
	int w=(val>>dep)&1;
	if(cnt[t[id][!w]]>cnt[t[lmt][!w]]) return query(t[lmt][!w], t[id][!w], dep-1, val)+(1<<dep);
	else return query(t[lmt][w], t[id][w], dep-1, val);
}
int main()
{
	scanf("%d", &tq); while(tq--)
	{	ret=0;
		scanf("%d", &n); rep(i, 1, n) scanf("%d", a+i);
		rep(i, 1, n) {c[i].first=a[i]; c[i].second=i; pre[i]=a[i]^pre[i-1];}
		memset(mx, -1, sizeof mx);
		tot=0; rt[0]=0; mx[0]=-1; rep(i, 1, n) {rt[i]=++tot; insert(rt[i], rt[i-1], K, pre[i]);}
		tp=0; rep(i, 1, n) {while(tp && c[q[tp]]<=c[i]) --tp; l[i]=tp?(q[tp]+1):1; q[++tp]=i;}
		tp=0; req(i, n, 1) {while(tp && c[q[tp]]<=c[i]) --tp; r[i]=tp?(q[tp]-1):n; q[++tp]=i;}
		rep(i, 1, n)
		{
//			ret=0;
			if(i-l[i]+1 > r[i]-i+1)
			{
				rep(j, i, r[i]) ret=max(max(pre[l[i]-1]^a[i]^pre[j], ret), query(rt[l[i]-1], rt[i-1], K, a[i]^pre[j]));
			}
			else rep(j, l[i]-1, i-1)
                ret = max(ret, query(rt[i - 1], rt[r[i]], K, a[i] ^ pre[j]));;
		}
		printf("%d\n", ret);
	}
}
```

---

## 作者：sim_sugar (赞：1)

纯纯信心 DS 题。来个大常数 $O(n \log^2 n)$ 做法。  

考虑分治，设当前处理区间 $[L,R]$，原序列前缀异或数组为 $pre$，套路预处理左边后缀 $\max$ 和右边前缀 $\max$，倒序枚举左端点 $l \in [L,mid]$，双指针维护 $rig_r \le lef_l$ 的最远 $r$，那么对于 $i \in [mid+1,r]$ 相当于查询 $pre_i$ 与 $pre_{l-1} \oplus lef_l$ 的异或最大值，全局建立一棵可持久化 $\text{0/1 Trie}$ 即可；$i \in [r+1,R]$ 部分则查询 $pre_i \oplus rig_i$ 和 $pre_{l-1}$ 的异或最大值，可以每层重构另一棵可持久化 $\text{0/1 Trie}$（封装一下，码量小）；也可以在枚举左端点的时候从 $L$ 向 $mid$ 扫，这样对应的 $r$ 不增，扫到就插入，用一棵普通 $\text{0/1 Trie}$ 即可（空间小）。  

可持久化 $\text{0/1 Trie}$ 应该都会写吧。这里只放分治的代码。  

```cpp
inline int Deal(int L,int R){
	if(L==R) return 0; int Mid=L+R>>1,res=B.tot=rig[Mid]=0;
	for(int i=Mid+1;i<=R;++i) B.Ins(i-Mid-1,i-Mid,pre[i]^(rig[i]=max(rig[i-1],a[i])));
	for(int l=Mid,r=Mid+1,now=a[l];l>=L;--l,now=max(now,a[l])){
		while(r<=R&&rig[r]<=now) ++r; --r;
		res=max(res,A.Qry(Mid,r,pre[l-1]^now));
		res=max(res,B.Qry(r-Mid,R-Mid,pre[l-1]));
	} return max({res,Deal(L,Mid),Deal(Mid+1,R)});
}
```

---

## 作者：zundamon (赞：0)

# [CF1777F Comfortably Numb](https://www.luogu.com.cn/problem/CF1777F)

启发式合并，思想很简单，但是一时转不过弯的话会有些难以理解。许多题解中这部分讲的有点简略，遂在此进行补充与代码注解。

----------------

看到这篇题解的你或许会有一个疑问：为何要从小区间开始枚举呢？

带着这个问题，我们先来研究一下为何只需要枚举一侧的区间端点就能得到最优值。

![image.png](https://s2.loli.net/2023/05/29/aX4bmkjdVBlzicu.png)

图中，$a[L]$ 与 $a[R]$ 分别是两侧第一个比中间数（记作 $a[i]$ ）要大的数

则 $a[i]$ 作为最大数（即题目中的 $\max\{a[l \cdots r]\}$ ）的最大区间为 $[L+1,R-1]$

我们知道，用可持久化 0-1trie 可以在接近 $O(1)$ 的时间内获得固定一端点区间的最优值（ **固定一端点：** 指区间 $L$ 或 $R$ 任意一端确定，而另一端不确定但有范围限定 ）

但是在这里，我们的 $L$ 和 $R$ 都是不确定的

这时候我们想到，可以利用可持久化 01trie 的 $O(1)$ 性质

去枚举一个区间内的端点，并限定好另一个区间端点的范围，直接得到这次枚举的最优值

在每次枚举中，一端端点可看做确定，另一端的端点就交给 trie 去找，不关我们的事了。

最后统计出每个 $a[i]$ 的所有枚举的最大值，即是我们的答案。

---------------

再回到上面的问题：为何要从小区间开始枚举？

明白原理及正确性后，这个问题就很好解答了：

其实从大小区间枚举都是一样的，只不过小区间枚举次数少，纯粹是一种优化。

下面给出代码注解：

```cpp
#include<iostream>
#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cmath>
#define Debug_Mode true
#define bage(abcd) if(Debug_Mode) cout<<"\nval:"<<abcd<<endl
#define bout(abcd) if(Debug_Mode) cout<<abcd<<" "
#define loop(ii,xx,yy) for(ll ii=xx;ii<=yy;ii++)
#define doop(ii,xx,yy) for(ll ii=xx;ii>=yy;ii--)
#define Max(x,y) ((x)>(y)?(x):(y))
#define Min(x,y) ((x)<(y)?(x):(y))
#define int long long
typedef long long ll;
const int Mod=998244353;
const long long INF = 0x3f3f3f3f;
const long long N=1e6+5;
const long long M=1e5+5;
using namespace std;
ll read(){ll x=0,y=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') y=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+(ch^48);	ch=getchar();}return x*y;}
struct node{
	int cnt;
	int nxt[2];
}trie[31*N];
int a[N],b[N],T,n;
int rt[N];
int tot;
void add(int ver,int id){
	if(ver==0){
		rt[ver]=++tot;
		int now=rt[ver];
		int t;
		doop(i,31,0){
			t=(b[id]>>i)&1;
			if(!trie[now].nxt[t]) trie[now].nxt[t]=++tot;
			trie[now].cnt=1;
			now=trie[now].nxt[t];
		}
		trie[now].cnt=1;
		return;
	}
	rt[ver]=++tot;
	int now=rt[ver],lst=rt[ver-1];
	int t;
	doop(i,31,0){
		t=(b[id]>>i)&1;
		if(!trie[now].nxt[t]) trie[now].nxt[t]=++tot;
		trie[now].nxt[!t]=trie[lst].nxt[!t];
		trie[now].cnt=trie[lst].cnt+1;
		lst=trie[lst].nxt[t];
		now=trie[now].nxt[t];
	}
	trie[now].cnt=trie[lst].cnt+1;
}
int query(int ver1,int ver2,int x){
	int n1=rt[ver1-1],n2=rt[ver2],t;
	int res=0;
	doop(i,31,0){
		t=(x>>i)&1;
		if(trie[trie[n2].nxt[!t]].cnt-trie[trie[n1].nxt[!t]].cnt>0){
			res+=(1<<i);
			n2=trie[n2].nxt[!t];
			n1=trie[n1].nxt[!t];
		}else{
			
			n2=trie[n2].nxt[t];
			n1=trie[n1].nxt[t];
		}
	}
	return res;
}
int stk[N],stp[N],top;
int ans[N];
void init(){
	loop(i,0,tot){
		trie[i].cnt=0;
		trie[i].nxt[0]=trie[i].nxt[1]=0;
	}
	loop(i,0,n+1) rt[i]=0;
	top=0;
	tot=0;
}
int l[N],r[N];
signed main(){
	//	scanf("%lld",&T);
	T=read();
	while(T--){
		int maxans=-1;
		init();
		n=read();
		add(1,0);
		/*由于前缀和可能需要得到第一个数的值，这里加入一个值为0的边界*/
		loop(i,2,n+1){
			a[i]=read();
			
			b[i]=a[i];
			b[i]^=b[i-1];
			
			add(i,i);
		}
		//注意此处版本号整体+1
		
		a[1]=a[n+2]=INF;
		/*两个边界值，用于计算l,r数组*/
		top=0;
		/*单调栈找到每个数左边第一个大于它的数（的位置）*/
		loop(i,1,n+2){
			while(top&&stk[top]<=a[i]) top--;
			l[i]=stp[top];
			stk[++top]=a[i];
			stp[top]=i;
		}
		top=0;
		/*为防止TLE，此处规则稍有改变
		 是找到每个数右边第一个大于等于它的数（的位置）
		 */
		doop(i,n+2,1){
			while(top&&stk[top]<a[i]) top--;
			r[i]=stp[top];
			stk[++top]=a[i];
			stp[top]=i;
		} 

		//记住！整体+1！
		//但是由于边界值，每个数字也向前挪了一个，所以可以认为二者对齐了。
		loop(i,2,n+1){
			//实际有用的值是 2 - (n+1)
			/*
			  l[i]是左边第一个大于a[i]的数的位置，不能取到
			  所以应当+1
			  r[i]-1同理
			 */
			if(i-l[i]-1+1<r[i]-1-i+1){
				/*
				  这里代表左边区间比右边区间小，枚举左边端点
				 */
				loop(j,l[i]+1,i){
					/*
					  注意：由于计算前缀和的原因，我们实际上找的是b[j-1]
					 */
					maxans=Max(maxans,query(i,r[i]-1,b[j-1]^a[i]));
					//i - (r[i]-1)是右端点限制， 此处一定要是b[j-1]
				}
			}else{
				loop(j,i,r[i]-1){
					//同上，我们的左端点限制为(l[i]+1-1) - (i-1)
					maxans=Max(maxans,query(l[i]+1-1,i-1,b[j]^a[i]));
				}
			}
		}
		printf("%lld\n",maxans);
	}
	return 0;
}
```



---

## 作者：封禁用户 (赞：0)

### Door

[洛谷](https://www.luogu.com.cn/problem/CF1777F)

[CF](https://codeforces.com/problemset/problem/1777/F)

### Preparation

+ 可持久化字典树

+ 单调栈

### Analysis

看到异或和，先求一个异或前缀。

我们用单调栈求出 $a_i$ 作为最大值向左最长的延伸位置 $L_i$ 和向右最长的延伸位置 $R_i$。

所以当 $a_i$ 为最大值时，答案就是 $sum_l \oplus sum_r \oplus a_i$，其中 $l \in [L_{i-1},i-1] \ r \in [i,R_i]$，在一个区间内查询，可以用可持久化字典树来维护。

再多看一眼就会发现，这样一个一个查询时间复杂度可能会爆炸，所以我们要再大区间里一个一个查询小区间，即启发式合并。这是由于这个区间比较特殊，我们对全局最大值进行分治，可以证明时间复杂度仅为 $O(n \log{n} \log{N})$，其中 $N$ 是值域范围。

需要注意的是，如果所有都是相同的数字，可能每个的 $[L,R]$ 都是 $[1,n]$，时间复杂度会被卡。所以需要给每个数字加一个不同的第二关键字。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define pii pair<int,int>
#define N 200010
pii a[N];
int t,n,rt[N],L[N],R[N];
stack<int> s;
struct Trie
{
	int son[N<<6][2],sum[N<<6],cnt;
	Trie()
	{
		cnt = 0;
	}
	inline void clear()
	{
		F(i,0,cnt) son[i][0] = son[i][1] = sum[i] = 0;
		cnt = 0;
	}
	int update(int u,int v,int x,int dep)
	{
		if(!u) u = ++cnt;
		sum[u] = sum[v] + 1;
		if(dep < 0) return u;
		int now = (x>>dep)&1;
		son[u][now] = update(son[u][now],son[v][now],x,dep-1);	
		son[u][now^1] = son[v][now^1];
		return u;
	} 
	int query(int u,int v,int x,int dep)
	{
		if(dep < 0) return 0;
		int now = ((x>>dep)&1)^1;
		if(sum[son[v][now] - son[u][now]] > 0) return (1<<dep)+query(son[u][now],son[v][now],x,dep-1);
		return query(son[u][now^1],son[v][now^1],x,dep-1);
	}
}tree;
int main()
{
	read(t);
	while(t--)
	{
		read(n);
		F(i,2,n+1) 
		{
			read(a[i].first);
			a[i].second = i;	
		}
		a[1] = a[n+2] = (pii){1e9,1e9};
		while(s.size()) s.pop();
		s.push(1);
		F(i,2,n+1)
		{
			while(a[s.top()] < a[i]) s.pop();
			L[i] = s.top() + 1;
			s.push(i);
		}
		while(s.size()) s.pop();
		s.push(n+2);
		D(i,n+1,2)
		{
			while(a[s.top()] < a[i]) s.pop();
			R[i] = s.top() - 1;
			s.push(i);
		}
		tree.clear();
		a[1] = a[n+2] = (pii){0,0};
		F(i,2,n+1) a[i].first ^= a[i-1].first;
		F(i,1,n+2) rt[i] = 0,rt[i] = tree.update(rt[i],rt[i-1],a[i].first,30);
		int ans = 0;
		F(i,2,n+1)
		{
			int len1 = i-L[i]+1,len2 = R[i]-i+1;
			if(len1 < len2)
				F(j,L[i]-1,i-1)
					ans = max(ans,tree.query(rt[i-1],rt[R[i]],a[i].first^a[i-1].first^a[j].first,30));
			else 
				F(j,i,R[i])
					ans = max(ans,tree.query(rt[L[i]-2],rt[i-1],a[i].first^a[i-1].first^a[j].first,30));
		}
		write(ans); 
		putchar('\n');
	}
	return 0;
}
```


---

