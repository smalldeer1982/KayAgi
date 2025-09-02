# Matrix Sorting

## 题目描述

You are given two tables $ A $ and $ B $ of size $ n \times m $ .

We define a sorting by column as the following: we choose a column and reorder the rows of the table by the value in this column, from the rows with the smallest value to the rows with the largest. In case there are two or more rows with equal value in this column, their relative order does not change (such sorting algorithms are called stable).

You can find this behavior of sorting by column in many office software for managing spreadsheets. Petya works in one, and he has a table $ A $ opened right now. He wants to perform zero of more sortings by column to transform this table to table $ B $ .

Determine if it is possible to do so, and if yes, find a sequence of columns to sort by. Note that you do not need to minimize the number of sortings.

## 说明/提示

Consider the second example. After the sorting by the first column the table becomes

 $ $$$\begin{matrix} 1&3&3\\ 1&1&2\\ 2&3&2. \end{matrix} $ $ </p><p>After the sorting by the second column the table becomes</p><p> $ $ \begin{matrix} 1&1&2\\ 1&3&3\\ 2&3&2, \end{matrix} $ $$$

and this is what we need.

In the third test any sorting does not change anything, because the columns are already sorted.

## 样例 #1

### 输入

```
2 2
2 2
1 2
1 2
2 2```

### 输出

```
1
1```

## 样例 #2

### 输入

```
3 3
2 3 2
1 3 3
1 1 2
1 1 2
1 3 3
2 3 2```

### 输出

```
2
1 2```

## 样例 #3

### 输入

```
2 2
1 1
2 1
2 1
1 1```

### 输出

```
-1```

## 样例 #4

### 输入

```
4 1
2
2
2
1
1
2
2
2```

### 输出

```
1
1```

# 题解

## 作者：hsfzLZH1 (赞：17)

## 题目大意

给定两个 $n\times n$ 的矩阵 $a,b$ ，分别表示初末状态，问是否能通过有限步排序操作，使得矩阵从初状态变为末状态。如果有，输出操作序列。

一次排序操作定义为，选择一列，将矩阵的每一行按这一列的值从小到大进行排序，如果两行值相同则不改变它们的相对顺序（即稳定的排序）。

$1\le a_{i,j},b_{i,j}\le n\le 1500$ ，你输出的操作序列长度 $\le 5000$

## 解题思路

一道有趣的思维题。

首先将初始状态的每一行与末状态的每一行进行对应。这一部分可以用哈希来解决。如果有两行相等，那么按从小到大顺序对应每两行。因为在任意操作中，这两行的顺序都不会发生改变。

如果这一步不能对应，直接输出 `-1` 。如果可以对应，在末状态添加新的一列，为对应的编号。这样就可以将初状态转化为一个普通的排序操作。

要使得最后成为末状态，只需满足 **任意相邻两行保持它们在末状态的前后顺序** 。考察对某一列的排序操作对末状态相邻两行的影响，有“与目标顺序相反”“与目标顺序相同”和“没有影响”三种情况，分别对应着两行这一列上的值之间大于、小于和等于的三种关系。

要求相邻两行保持它们在末状态的前后顺序，只需操作序列中 **最后一个对它们有影响的操作** 属于“与目标顺序相同”类型。

所以我们倒着考虑操作序列。对于一个操作，如果它会导致某一行在这次操作之后“与目标顺序相反”，就不能使用该操作。但如果操作序列的后面有“与目标顺序相同”的操作，就可以解除这一对相邻行对这一列进行排序操作的限制。

我们可以用一个类似于拓扑排序的东西，将相邻两行和每一列的操作都对应成一个点，有操作使行满足目标顺序，则操作向行连边；有操作使行不满足目标顺序，则行向操作连边。当一个操作没有入度时，才可以使用；当行入度减少 $1$ 时，就可以使用。最后看能否使用初始状态对应列即可。

时间复杂度 $O(n^2)$ （哈希）， $O(n^2\log n)$ （`map`），空间复杂度 $O(n^2)$ 。

## 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
using namespace std;
const int maxn=1510;
int n,m,a[maxn][maxn],b[maxn][maxn],cnt,crr[maxn],cur,h[maxn*2],nxt[maxn*maxn],p[maxn*maxn],deg[maxn*2];
bool tf[maxn*2];
queue<int>q;
vector<int>ans,g[maxn];
struct node{int a[maxn];bool operator<(node x)const{for(int i=1;i<=m;i++)if(a[i]!=x.a[i])return a[i]<x.a[i];return false;}};
map<node,int>mp;
void add_edge(int x,int y)
{
	//printf("ad %d %d\n",x,y);
	cur++;
	nxt[cur]=h[x];
	h[x]=cur;
	p[cur]=y;
}
signed main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",a[i]+j);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",b[i]+j);
	for(int i=1;i<=n;i++)
	{
		a[i][m+1]=i;
		node x;
		for(int j=1;j<=m;j++)x.a[j]=a[i][j];
		if(mp[x])g[mp[x]].push_back(i);
		else mp[x]=++cnt,g[cnt].push_back(i);
	}
	for(int i=1;i<=n;i++)
	{
		node x;
		for(int j=1;j<=m;j++)x.a[j]=b[i][j];
		if(!mp[x]){printf("-1\n");return 0;}
		else
		{
			if(crr[mp[x]]==g[mp[x]].size()){printf("-1\n");return 0;}
			b[i][m+1]=g[mp[x]][crr[mp[x]]];crr[mp[x]]++;
		}
	}
	for(int i=1;i<n;i++)//i,i+1
	{
		for(int j=1;j<=m+1;j++)
		{
			if(b[i][j]>b[i+1][j])add_edge(m+1+i,j),deg[j]++;
			else if(b[i][j]<b[i+1][j])add_edge(j,m+1+i),deg[m+1+i]++;
		}
	}
	for(int j=1;j<=m+1;j++)if(!deg[j])q.push(j),tf[j]=true;
	while(!q.empty())
	{
		int x=q.front();q.pop();
		if(x<=m+1)
		{
			ans.push_back(x);
			for(int j=h[x];j;j=nxt[j])
			{
				if(!tf[p[j]])tf[p[j]]=true,q.push(p[j]);
			}
		}
		else
		{
			for(int j=h[x];j;j=nxt[j])
			{
				deg[p[j]]--;
				if(!deg[p[j]])tf[p[j]]=true,q.push(p[j]);
			}
		}
		if(tf[m+1])break;
	}
	if(!tf[m+1]){printf("-1\n");return 0;}
	else
	{
		printf("%d\n",ans.size());
		for(int i=ans.size()-1;i>=0;i--)printf("%d ",ans[i]);printf("\n");
	}
	return 0;
}
```

---

## 作者：feecle6418 (赞：15)

显然一列至多只会被操作一次。

观察发现，这个操作其实是基数排序的过程。操作 $a_1,a_2,\dots ,a_k$ 其实是对所有行按照先按 $a_k$ 从小到大，$a_k$ 相同的按 $a_{k-1}$ 从小到大，……，最后再按输入顺序从小到大，排序的过程。

有上述观察后，我们可以从后往前确定所有操作。先在 $B$ 中任意找到一列递增的作为 $a_k$，再任意找一列满足“所有第 $a_k$ 列相同的段”内部都递增的作为 $a_{k-1}$，再任意找一列满足“所有第 $a_k$ 列和第 $a_{k-1}$ 列相同的段”内部都递增的作为 $a_{k-2}$，……假如找不到下一列了，就说明剩下的“第 $a_1,a_2,\dots ,a_k$ 列均相同”的连续段内都满足在 $A$ 中编号递增，扫一遍判断即可。

直接暴力找下一列是 $O(n^3)$ 的不可取。注意到一个相同的段内某一列递增，相当于段内除了开头外都满足 $b_{i,k}\ge b_{i-1,k}$。把每行中 $b_{i,k}\ge b_{i-1,k}$ 的列 $k$ 存进 bitset 里面，每次取出所有不在段开头的行，将其 bitset 与起来就能找到合法下一列的集合。这样，复杂度变为 $O(\dfrac{n^3}{w})$，无压力通过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int base1=233,base2=2011,mod1=1e9+7,mod2=1e9+9;
vector<int> a[1505],b[1505];
int n,m,K,id[1505],hsh1[1505],hsh2[1505],ans[1505],lst[1505][1505],cur1[1505],cur2[1505],used[1505];
bitset<1505> can[1505];
map<pair<int,int>,vector<int> > mp;
bool cmp(const vector<int> &a,const vector<int> &b) {
	return a[K]<b[K];
}
void Sort(int x) {
	K=x,stable_sort(a+1,a+n+1,cmp);
}
int main() {
	srand(time(0));
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++) {
		a[i].resize(m);
		for(int j=0; j<m; j++)scanf("%d",&a[i][j]),hsh1[i]=(1ll*hsh1[i]*base1+a[i][j])%mod1,hsh2[i]=(1ll*hsh2[i]*base2+a[i][j])%mod2;
		mp[make_pair(hsh1[i],hsh2[i])].push_back(i);
	}
	for(int i=1; i<=n; i++) {
		b[i].resize(m);
		for(int j=0; j<m; j++)scanf("%d",&b[i][j]);
	}
	for(int j=0; j<m; j++) {
		for(int i=2; i<=n; i++)if(b[i][j]>=b[i-1][j])can[i][j]=1;
	}
	for(int i=n; i>=1; i--) {
		int h1=0,h2=0;
		for(int j=0; j<m; j++)h1=(1ll*h1*base1+b[i][j])%mod1,h2=(1ll*h2*base2+b[i][j])%mod2;
		if(!mp[make_pair(h1,h2)].size())return puts("-1"),0;
		id[i]=mp[make_pair(h1,h2)].back();
		mp[make_pair(h1,h2)].pop_back();
	}
	while(1) {
		bitset<1505> tmp;
		for(int i=0; i<m; i++)if(!used[i])tmp[i]=1;
		for(int i=1; i<=n; i++) {
			if(i==1||cur1[i]!=cur1[i-1]||cur2[i]!=cur2[i-1])continue;
			tmp&=can[i];
		}
		if(!tmp.count())break;
		int pos=0;
		for(int i=0; i<m; i++)if(tmp[i]) {
				pos=i;
				break;
			}
		used[pos]=1,ans[++ans[0]]=pos;
		for(int i=1; i<=n; i++)cur1[i]=(1ll*cur1[i]*base1+b[i][pos])%mod1,cur2[i]=(1ll*cur2[i]*base2+b[i][pos])%mod2; //,cout<<i<<' '<<cur1[i]<<' '<<cur2[i]<<'\n';
	}
	for(int i=ans[0]; i; i--)Sort(ans[i]);
	for(int i=1; i<=n; i++)for(int j=0; j<m; j++)if(a[i][j]!=b[i][j])return puts("-1"),0;
	cout<<ans[0]<<'\n';
	for(int i=ans[0]; i; i--)cout<<ans[i]+1<<' ';
	return 0;
}
```


---

## 作者：SSerxhs (赞：8)

一种 $O(\frac{nm^2}{w})$ 的做法。

把矩阵看成 $n$ 个行向量，考虑直接观察操作后的结果，可以发现全过程其实就是对行向量排序的过程，输出的序列其实是排序关键字顺序的倒序，而初始矩阵实际上是指定了第 $m+1$ 维的值。在加入这一维的情况下，排序结果是唯一的。

考虑顺次选取排序关键字，不矛盾的选取都是可行解。当选取第 $i$ 个关键字时，如果前 $i-1$ 个关键字不能把某两个行向量 $\vec{m},\vec{n}$ 区分开而实际上 $\vec{m}$ 应当排在 $\vec{n}$ 前面，则第 $i$ 个关键字 $x$ 必须满足 $\vec{m}_x\le \vec{n}_x$ 才能避免矛盾。

剩下的问题就是如何判断是否存在矛盾了。可以用一个 `bitset` 记录有哪些相邻位置仍然没有被区分，再用 $m$ 个 `bitset` 记录每个关键字的每一位是否存在和下一位成逆序对，则不矛盾当且仅当两个 `bitset` 无交。选取后，将新区分开的位置修改一下就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned int ui;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
std::mt19937 rnd(time(0));
inline int sj(int n)
{
	unsigned int x=rnd();
	return x%n+1;
}
#define rand fst
template<typename typC> void read(register typC &x)
{
	register int c=getchar(),fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
template<typename typC> void write(register typC x)
{
	if (x<0) putchar('-'),x=-x;
	static int st[100];
	register int tp=1;
	register typC y;st[1]=x%10;x/=10;
	while (x) y=x/10,st[++tp]=x-y*10,x=y;++tp;
	while (--tp) putchar(st[tp]|48);
}
template<typename typC> void write(register typC *a,register int num)
{
	for (register int i=1;i<=num;i++) write(a[i]),putchar(i==num?10:32);
}
#define space(x) write(x),putchar(32)
#define enter(x) write(x),putchar(10)
const int N=1.5e3+20,p=383778817;
inline void inc(register int &x,const int y)
{
	if ((x+=y)>=p) x-=p;
}
inline void dec(register int &x,const int y)
{
	if ((x-=y)<0) x+=p;
}
inline int ksm(register int x,register int y)
{
	register int r=1;
	while (y)
	{
		if (y&1) r=(ll)r*x%p;
		x=(ll)x*x%p;
		y>>=1;
	}
	return r;
}
typedef pair<ull,int> pa;
ull hs;
bitset<N> nx[N],bs;
int a[N][N],b[N][N],r[N][N],st[N];
int T,n,m,c,i,j,k,x,y,z,ans,la,cnt,hh,tp;
map<pa,int> mp;
vector<int> s[N];
bool vis[N];
int main()
{
	read(n);read(m);++m;
	for (i=1;i<=n;i++)
	{
		for (j=1;j<m;j++) read(a[i][j]);a[i][m]=i;hs=hh=0;
		for (j=1;j<m;j++) hs=hs*2357ull+a[i][j],hh=(hh*2357ll+a[i][j])%p;
		if (mp.find(pa(hs,hh))!=mp.end())
		{
			s[mp[pa(hs,hh)]].push_back(i);
		} else s[mp[pa(hs,hh)]=++cnt].push_back(i);
	}//printf("%d %d\n",cnt,s[1][0]);
	for (i=1;i<=cnt;i++) reverse(s[i].begin(),s[i].end());
	for (i=1;i<=n;i++)
	{
		for (j=1;j<m;j++) read(b[i][j]);hs=hh=0;
		for (j=1;j<m;j++) hs=hs*2357ull+b[i][j],hh=(hh*2357ll+b[i][j])%p;
		if (mp.find(pa(hs,hh))==mp.end())
		{
			puts("-1");return 0;
		}
		la=mp[pa(hs,hh)];//printf("la=%d\n",la);
		if (!s[la].size()) return puts("-1"),0;
		b[i][m]=s[la][s[la].size()-1];
		s[la].pop_back();
	}
	//printf("%d %d\n",b[1][m],b[2][m]);
	for (j=1;j<=m;j++) for (i=n-1;i;i--) if (b[i][j]>b[i+1][j]) nx[j][i]=1;
	//bs.set();assert(!bs[0]);
	for (i=1;i<n;i++) bs[i]=1;
	for (i=1;i<=m;i++)
	{
		for (j=1;j<=m;j++) if (!vis[j]&&(bs&nx[j]).count()==0)
		{
			st[++tp]=j;vis[j]=1;break;
		}
		if (j>m) return puts("-1"),0;
		if (j==m) {--tp;break;}
		for (k=1;k<n;k++) if (bs[k]&&b[k][j]<b[k+1][j]) bs[k]=0;
		//printf("%d\n",bs.count());
		if (bs.count()==0) break;
	}
	printf("%d\n",tp);
	while (tp) printf("%d ",st[tp--]);
}

```

---

## 作者：7KByte (赞：3)

对于矩阵的每一行重标号，$c_i$ 表示 $A$ 矩阵的第 $i$ 行对应的 $B$ 矩阵的第 $c_i$ 行。

这个过程可以通过哈希表实现，时间复杂度 $\rm O(n^2+nm)$ 。

同时定义 $mat_{c_i}=i$，表示 $B$ 矩阵中在 $A$ 矩阵中对应的行。

那么最终的 $B$ 矩阵，标号一定是 $1,2,\cdots,n$ 。

想要将 $A$ 矩阵排序，只需要最终第 $mat_1$ 在第 $mat_{2}$ 行前面，第 $mat_i$ 在第 $mat_{i+1}$ 行前面 。即使所有相邻行正序。

那么对于一列 $j$ 排序，考虑每个 $1\le i<n$  。

- 如果 $a_{mat_i,j}<a_{mat_{i+1},j}$ ，则能够使这个相邻行正序。
- 如果 $a_{mat_i,j}>a_{mat_{i+1},j}$ ，则能够使这个相邻行反序。
- 如果 $a_{mat_i,j}=a_{mat_{i+1},j}$ ，则对相邻行没有影响。

我们记录下对第 $j$ 列的排序会影响哪些相邻行。如果全部是正序影响，则进行当前列的排序一定不会使答案更劣。

如果存在反序影响，意味着该操作后一定还有另外一个操作是对该相邻行的正序影响。

不难用队列维护目前已经解锁的操作，对于已经解锁的操作，选择一定不会使答案更劣。

如果将所有能进行的操作使用后仍不能排序则无解，两个矩阵的行不能对应也无解。


时间复杂度 $\rm O(n^2+nm)$ 。如果对哈希值离散化可以做到 $\rm O(n\log n+nm)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 3005
#define P 10007
using namespace std;
int n,m,c[N],a[N][N],b[N][N],vis[N],mat[N];unsigned long long u[N],v[N];
typedef pair<int,int> Pr;
queue<int>q;int d[N],h[N],tot,vs[N];
vector<int>ans;
struct edge{int to,nxt;}e[N*N];
void add(int x,int y){e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n)rep(j,1,m)scanf("%d",&a[i][j]);
	rep(i,1,n)rep(j,1,m)scanf("%d",&b[i][j]);
	rep(i,1,n){
		rep(j,1,m)u[i]=u[i]*P+a[i][j];
		rep(j,1,m)v[i]=v[i]*P+b[i][j];
	}
	rep(i,1,n){
		rep(j,1,n)if(u[i]==v[j]&&!vis[j]){
			vis[j]=1,c[i]=j;mat[j]=i;break;
		}
		if(!c[i]){puts("-1");return 0;}
	}
	rep(j,1,m){
		rep(i,1,n-1){
			int l=mat[i],r=mat[i+1];
			if(a[l][j]<a[r][j])add(j,i+m);
			else if(a[l][j]>a[r][j])d[j]++,add(i+m,j);
		}
	}
	rep(i,1,m)if(!d[i])q.push(i);
	while(!q.empty()){
		int x=q.front();q.pop();
		if(x<=m){
			ans.push_back(x);
			for(int i=h[x];i;i=e[i].nxt)if(!vs[e[i].to]){
				vs[e[i].to]=1;q.push(e[i].to);
			}
		}
		else{
			for(int i=h[x];i;i=e[i].nxt){
				d[e[i].to]--;
				if(!d[e[i].to])q.push(e[i].to);
			}
		}
	}
	rep(i,1,n-1)if(mat[i]>mat[i+1]&&!vs[m+i]){puts("-1");return 0;}
	reverse(ans.begin(),ans.end());
	cout<<ans.size()<<endl;
	for(int i=0;i<(int)ans.size();i++)printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：hater (赞：3)

### 思路分析 

枚举最后操作的那一列 , 这一列必须要有序 。 

考虑这一列中 , 相邻元素如果相等 , 那么在上一次操作的列中 , 这些元素必须同样要是不降的 , 也就是 : 

若 $b_{p1,i}=b_{p1,i+1}=...=b_{p1,i+k}$ 则必有 $b_{p2,i}<=b_{p2,i+1}=...=b_{p2,i+k}$ 

( $p1$是最后一次操作的列 , $p2$是前一次操作的列 ）。 

因为根据排序stable性质 这些元素若不满足**已相对有序** 那么在这次操作中也不会满足要求 。

继续倒推 , 考虑操作p2带来的影响 。 

如果 $b_{p2,i}<b_{p2,i+1}$ 那么我们就消去i和i+1的相对大小要求了 。

因为在之前的若干操作后 , 操作p2即可满足要求 。

### 复杂度优化
 
首先我们发现不需要枚举最后一个操作列 , 直接把n-1个相对大小关系丢进去就好了 。

这个东西如果我们枚举 n 轮 就有一个三次方的玩意 。

我们继续优化 , 考虑一个列什么时候能被操作 。

当这个列中所有 $b_{p,i}>b_{p,i+1}$ 的位置 , 在之前的操作中 , 都已经被消去了 , 那就可以操作了 。

我们记录一个num : 表示每列中未被消去的要求数量 。

这样用一个类bfs的算法就可以做到平方复杂度 。

### 具体实现  

每次把 num为零的列 去消除其他列的 num 。 

操作后把num为零的列加入队列 , 倒序输出即是答案 。

但是还有一个问题是最后并不需要把$n-1$个大小关系全部消去 如果$A$已经满足了这些条件也是可以的 。 

### 闲话

~~之后官方题解就丢一句最后检查一下即可~~ 

之后我不会平方的巧妙检查 之后 log排序 ~~憨批石锤~~ ~~xmr用的基数排序才去掉log~~ 

所以这个憨批写的玩意带了一个log 。 

### 代码

```cpp
#include<bits/stdc++.h> 
#define rg register 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i )  
using namespace std ; 
const int N = 1505 ; 
int a[N][N] , b[N][N] , n , m , pa[N] , pb[N] , num[N] , ida[N] , idb[N] ; bool is[N][N] , ned[N] ; 
queue <int> q ; int ans[N] , len ; 
bool cmpa( int A , int B ) {  
  fp( j , 1 , m ) 
    if( a[A][j] != a[B][j] ) return a[A][j] < a[B][j] ; 
  return A < B ;  
} 
bool cmpb( int A , int B ) { 
  fp( j , 1 , m ) 
    if( b[A][j] != b[B][j] ) return b[A][j] < b[B][j] ; 
  return A < B ;  
} 
signed main( ) { 
  ios::sync_with_stdio(false) ; 
  cin.tie(0) ; 
  cin >> n >> m ; 
  fp( i , 1 , n ) fp( j , 1 , m ) cin >> a[i][j] ; 
  fp( i , 1 , n ) fp( j , 1 , m ) cin >> b[i][j] ; 
  fp( i , 1 , n ) pa[i] = pb[i] = i ; 
  sort( pa+1 , pa+1+n , cmpa ) ; sort( pb+1 , pb+1+n , cmpb ) ; 
  fp( i , 1 , n ) ida[pa[i]] = i , idb[pb[i]] = i ; 
  fp( i , 1 , n ) fp( j , 1 , m ) 
    if( a[pa[i]][j] != b[pb[i]][j] ) { cout << "-1" << '\n' ; return 0 ; }  
  fp( i , 2 , n ) { 
    fp( j , 1 , m ) 
      if( b[i-1][j] > b[i][j] ) num[j] ++ , is[i][j] = 1 ; 
  } 
  fp( i , 2 , n ) ned[i] = 1 ; 
  fp( i , 1 , m ) if( !num[i] ) q.push(i) ; 
  while( q.size() ) { 
    int x = q.front() ; q.pop() ; 
    ans[++len] = x ; 
    fp( i , 2 , n ) 
     if( b[i-1][x] < b[i][x] && ned[i] ) { 
       ned[i] = 0 ; 
       fp( j , 1 , m ) 
         if( is[i][j] ) { 
           is[i][j] = 0 ; num[j] -- ; 
           if( !num[j] ) q.push(j) ; 
		 }  
	 } 
  } 
  bool flag = 0 ; 
  fp( i , 2 , n ) if( ned[i] && pa[idb[i-1]] > pa[idb[i]] ) flag = 1 ;    
  if( flag ) { cout << "-1" << '\n' ; return 0 ; } 
  cout << len << '\n' ; 
  fq( i , 1 , len ) cout << ans[i] << ' ' ; cout << '\n' ; 
  return 0 ; 
} 
```



---

## 作者：Maverik (赞：2)

# Matrix Sorting

## statement

给你两个 $n\times m$ 的矩阵 $A,B$（$1\le n,m\le 1500$），矩阵的元素均为 $[1,n]$ 内的整数。

每一次操作你可以选定一列作为每一行的关键字，按照关键字从小到大的顺序把所有行排序得到一个新矩阵。这里使用的排序是稳定的，即如果有两行的关键字相同，则按照在原矩阵的先后顺序排序。你可以进行不超过 $5000$ 次操作，问你能否将 $A$ 变成 $B$。不能变成输出 $-1$，否则输出一种可行的操作序列。

## solution

显然，我可以将两边的行一一对应，对应不上则无解。对于相同的行，按照原顺序对应即可。

发现只需要对 $B$ 矩阵相邻两行加以限制就可以了，即用 $n-1$ 对关系限定结果矩阵。

直观的，对每列之多进行一次操作。考虑一次操作对于一个上述关系的影响，只分为三种：

$1.$ 正 $\to$ 反 

$2.$ 反 $\to$ 正

$3.$ 不改变顺序

对于此关系 ，$2$ 操作后不能有 $1$ 操作。


这种二元关系是容易通过图论描述的：$m$ 个点代表 $m$ 种操作，但发现对于 $m$ 种操作直接连边复杂度无法保证。考虑另外 $n-1$ 个点代表 $n-1$ 对关系。根据拓扑排序的过程，对于一对关系 $i$，$i$ 向它的 $1$ 操作连边，它的 $2$ 操作向它连边。一个操作只有在没有入度时才能入队，一个关系被减掉一次入度就消除限制，直接入队。由此，反拓扑序即为答案。


## code

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int maxn=2e3+10,mod=1e9+7,base=233;
int n,m,adj[maxn<<2],indeg[maxn<<2];
bool vis[maxn<<2];
struct row{int a[maxn],hsh;}r[maxn],t[maxn];
vector<int>ans,e[maxn<<2];
vector<pair<int,int> >hshr,hsht;
inline int id(int flag,int num){return m*flag+num;}
inline void add(int x,int y){e[x].pb(y),indeg[y]++;}
inline void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>r[i].a[j];
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>t[i].a[j];
    for(int i=1;i<=n;i++){int hsh=0;for(int j=1;j<=m;j++)hsh=(hsh*base+r[i].a[j])%mod;hshr.pb({hsh,i});}
    for(int i=1;i<=n;i++){int hsh=0;for(int j=1;j<=m;j++)hsh=(hsh*base+t[i].a[j])%mod;hsht.pb({hsh,i});}
    sort(hshr.begin(),hshr.end()),sort(hsht.begin(),hsht.end());
    for(int i=0;i<n;i++)
        if(hshr[i].first!=hsht[i].first) return cout<<"-1\n",void();
        else adj[hsht[i].second]=hshr[i].second;
    for(int j=1;j<=m;j++) for(int i=1;i<n;i++)
        if(r[adj[i]].a[j]<r[adj[i+1]].a[j]) add(id(0,j),id(1,i));
        else if(r[adj[i]].a[j]>r[adj[i+1]].a[j]) add(id(1,i),id(0,j));
    queue<int>q;for(int st=1;st<=m;st++) if(!indeg[st]) q.push(st);
    while(!q.empty())
    {
        int x=q.front();q.pop(),(x<=m)?ans.pb(x):void();
        for(auto y:e[x]) if(!vis[y])
            if(y>m || !--indeg[y]) q.push(y),vis[y]=1;
    }
    for(int i=1;i<n;i++) if(!vis[id(1,i)] && adj[i]>adj[i+1]) return cout<<"-1\n",void();
    reverse(ans.begin(),ans.end()),cout<<ans.size()<<'\n';
    for(auto x:ans) cout<<x<<" ";cout<<'\n';
}
signed main(){ios::sync_with_stdio(false);cin.tie(NULL);return solve(),0;}
```


---

## 作者：tzc_wk (赞：2)

摘自我的[贪心 & 构造 & DP 杂题选做](https://www.cnblogs.com/ET2006/p/greedy-construction-dp2.html)，第 $30$ 道题

一道非常妙的拓扑排序好题，能出出这道题的人怕不是神仙/bx

首先我们考虑求出矩形 $A$ 中的每一行在进行这些操作后会对应到矩形 $B$ 中的哪一行——显然如果矩形 $A$ 中每行都不相同，那直接相同的行配对即可，如果矩形 $A$ 出现了相同的行，那显然它们的相对位置顺序是不会改变的，直接按照它们在原矩阵中的顺序编号即可。这样我们可以新增一个 $m+1$ 列，$A$ 矩形第 $i$ 行第 $m+1$ 列的元素就是 $i$，而 $B$ 矩形第 $i$ 行第 $m+1$ 列的元素则是 $B$ 矩形第 $i$ 行在 $A$ 矩形中对应的行的编号。当然如果无法对应我们就直接输出 `NO`。

接下来考虑如何求出操作序列，我们倒着考虑操作序列，那么可以发现，我们最后一步可能操作的列，在 $B$ 矩形中都是单调不降的，也就是说对于**任意相邻两行 $i,i+1$**，必须要有 $b_{i,j}\le b_{i+1,j}$ 后，最后一次才有可能操作第 $j$ 列，考虑完了最后一次操作，再考虑倒数第二次操作的列有什么限制，还是必须单调不降吗？非也，不难发现，加入最后一次操作的列为 $x$，倒数第二次操作的列为 $y$，那么如果 $b_{i,y}>b_{i+1,y}$ 但 $b_{i,x}<b_{i+1,x}$，这种情况还是有可能合法的，因为虽然排 $y$ 之后会导致 $i,i+1$ 顺序颠倒，但是下一次排序我们又把它搬回来了，因此这种情况是不影响的，但是如果出现 $b_{i,y}>b_{i+1,y}$ 且 $b_{i,x}=b_{i+1,x}$ 就 GG 了，因为我们的排序是 stable 的，你前一次把 $i,i+1$ 的顺序搞反了，后一次两行的关键字相同，它们的顺序还是反的。

那么我们应该从什么角度思考这个过程呢？不难发现，我们倒着考虑每一次操作 $x$，那么我们考虑完 $x$ 之后，相当于把所有 $a_{i,x}\ne a_{i+1,x}$ 的 $(i,i+1)$ 都“解锁了”，而如果考虑到某一步操作时，第 $y$ 列存在一个 $i$ 使得 $a_{i,y}>a_{i+1,y}$，且 $(i,i+1)$ 没有被“解锁”，那么上一步操作的就不可能是 $y$，因此我们可以考虑拓扑排序的过程，将相邻两行和每一列看作一个点，对于每对 $(a_{i,x},a_{i+1,x})$，如果 $a_{i,x}<a_{i+1,x}$，那么我们连一条第 $x$ 列向第 $i$ 行的边，表示操作完第 $x$ 列后 $(i,i+1)$ 就被解锁了，如果 $a_{i,x}>a_{i+1,x}$，那么我们连一条第 $i$ 行指向第 $x$ 列的边，表示第 $i$ 行被解锁，是第 $x$ 列能够被操作的必要条件，然后跑一遍类似拓扑排序的东西即可。只不过这里与一般的拓扑排序不同的一点是，如果一个点对应的是某一行表示的点，那么只要连向它的点中至少一个被选择，那它就可以设为被访问。

那么怎样统计答案呢？不难发现，初始局面相当于我们强制对 $m+1$ 行排了个序，因此我们只需检验 $m+1$ 列对应的点是否被访问即可，如果被访问了则倒着输出拓扑序列，否则输出 `NO`。

时间复杂度 $\Theta(nm)$。

---

## 作者：EuphoricStar (赞：1)

做了好久。怎么会是呢。

题目的操作可以看成，求出一些关键字，使得 $B$ 矩阵的行是由 $A$ 按照这些第 $1$ 关键字、第 $2$ 关键字一直到第 $k$ 关键字，最后还有一个原来所在行下标的关键字，从小到大排序。

肯定是从排好序的 $B$ 矩阵入手。首先任意找到一个在 $B$ 矩阵中已经排好序的列。然后把这一列极长的相等段拎出来，把 $[1, n]$ 分成了若干个区间 $[l_1, r_1], [l_2, r_2], \ldots, [l_k, r_k]$。发现这是一个递归的过程，我们还要找到一个之前没选过的列，在这些区间分别是升序的。然后可以把这些区间分成一些更小的区间。可以把区间存下来，一轮一轮地判断。

终止条件就是，$[l_1, r_1] \sim [l_k, r_k]$ 都是 $A$ 矩阵的子序列（因为最后一个排序的关键字是行的下标）。这个可以对每行哈希，然后建子序列自动机判断即可。

但是兴冲冲的写了一发，[T 了](https://codeforces.com/problemset/submission/1500/241693208)。发现枚举每一列再判断在这些区间是否分别升序会使得复杂度退化至 $O(n^3)$。想起来有个东西叫 bitset。可以把第 $i$ 行 $B_{i, j} < B_{i + 1, j}$ 的所有列下标 $j$ 开个 bitset 存起来，那么得到所有升序的行，只需把 $[l_1, r_1 - 1] \sim [l_k, r_k - 1]$ 的 bitset 与起来就行了。时间复杂度变为 $O(\frac{n^3}{\omega})$。

子序列自动机部分若开 vector 存位置然后每次二分就是 $O(n^2 \log n)$。但是也能过。跑得还不慢。

[code](https://codeforces.com/problemset/submission/1500/241693964)

---

## 作者：Mirasycle (赞：0)

$n,m$ 同阶，以下时间复杂度均用 $n$ 来表示。

可以发现这是一个稳定的排序。每次排序中值相同的时候，排名大小取决于上一次的排名。

因为后续的操作会影响到前面的操作，因此我们考虑反向思考这个过程，从末状态倒推。

考虑将初始矩阵中的每一行和某矩阵对应起来。然后给末矩阵增加一列，代表初始状态中每一行的排名（相当于第 $0$ 次排序）。这样子我们就可以丢掉初始矩阵了，只用在末矩阵上思考。

如果末矩阵中某一列是单调不减的，那么它就可以当作最后一次操作的列。那么如果处理它其中的相等段呢，我们无法保证相等段就刚好排序成我们想要的，发现这个排序是稳定的，于是我们需要在倒数第二次操作以及之前的操作中将其变成单调递增的。于是倒数第二次操作就是满足在倒数第一次操作中相等段单调不减的。以此类推，最后进行第 $0$ 次排序。

可是每次选择列的时候可能有多种选择，我们该如何处理。

结论就是：可以随便选一列满足要求的。证明很简单，

> 就以最后一个操作的选择为例来证明，假设有列 $i,j$ 均满足单调不减，我们选择了 $i$ 的时候必然不可能出现选 $j$ 可以复原，但是选 $i$ 无法排序完成。假设出现了以上情况，我们在选择了 $i$ 之后，再选择 $j$ 的成功排序操作方法，肯定也是能完成的。本质是我们随便选择了一列单调不减的序列之后，其实是弱化了原问题，比原局面更优了（因为单调递增的行的数量变多了），不存在走向了一个更劣的局面。

暴力寻找可行列的话，时间复杂度是 $O(n^3)$ 的。可以用 bitset 优化，对于每一列 $j$ 维护一个 bitset 表示 $b_{i,j}\le b_{i+1,j}$ 的时候为 $0$，否则为 $1$。每次寻找合法列对于某一列的 $O(n)$ 判定可以变成 $O(\dfrac{n}{\omega})$ 的按位与判定。于是时间复杂度就是 $O(\dfrac{n^3}{\omega})$ 的。

还有一种更快的方法。上述方法其实是依赖于之前的操作，不断往前寻找之前的操作弥补后续的不足。另一种方法是一边倒退一边看看之后哪些操作能够掩盖当前操作的问题。

还是倒着做，假如我们要操作第 $j$ 列，当前列上肯定有一些相邻行是满足 $a_{i,j}>a_{i+1,j}$ 的，如果我们想要操作第 $j$ 列的话需要这些行被之后的操作修正（如果是从倒着做的视角的话，就是那些已经选择了的操作）。在没有修正之前，这些行是 "锁" 着的。

我们建立二分图，左边为列，右边是行。如果 $a_{i,j}>a_{i+1,j}$ 的话，代表 $(i,i+1)$ 是支配 $j$ 的，于是我们连边 $i\to j$。如果 $a_{i,j}<a_{i+1,j}$ 的话，代表对于第 $j$ 列的操作能解锁第 $i$ 行。进行一个特殊的拓扑排序，就是列必须要所有指向它的行都被访问才能进入队列，行只主要指向它的列中有一个被访问就能访问。以那些单调不减列为起点，然后最后看看第 $m+1$ 列能否被遍历到，可以的话就输出逆拓扑序即可。

时间复杂度 $O(n^2)$。

---

## 作者：lfxxx (赞：0)

十分有趣。

首先每一行用哈希映射到一个数，相同的行相对位置显然不会改变，因此可以按照顺序给 $B$ 中每一行确定其是原来 $A$ 中哪一行，不妨令 $rk_i$ 表示 $B$ 中第 $i$ 行是原来 $A$ 中第 $rk_i$ 行。

保证全局有序只需保证相邻有序，因此只需对于每个 $i \in [1,n)$ 保证第 $rk_i$ 行在第 $rk_{i+1}$ 行上面即可保证 $A$ 变成了 $B$。

考察每一列，对其进行排序会导致一些 $rk_i,rk_{i+1}$ 顺序变成正确的或者反着的，你要从 $A$ 矩阵的初始状态出发选出若干列（显然一个列不会被选多次）按某种顺序操作最后使得所有 $rk_{i},rk_{i+1}$ 顺序正确。考虑怎么描述初始状态，不妨加上第 $m+1$ 列，其权值为该行在 $A$ 中的排名，钦定该列必须被操作，操作后即可得到初始状态，此时第一个操作前的初始状态就没有任何意义了，随便设一个就行，你发现不是所有列都会被操作，有点不统一，但是可以钦定所有列必须操作，而在列 $m+1$ 前被操作的其影响刚好会被消去，于是剩下的问题只有给 $m+1$ 列操作确定顺序。

正着确定顺序似乎不好做，我们考虑倒着确定顺序。

当你操作列 $i$ 时，如果其会使得 $rk_{j},rk_{j+1}$ 顺序反过来，那么其后面必须有一个使得 $rk_{j},rk_{j+1}$ 顺序正过来的操作，也就是一个操作能放入操作序列当且仅当某种条件被满足，而将一个操作放入操作序列会使得被满足的条件只增不减。

于是你发现，从什么都没操作的状态出发，每次把所有能操作的操作全部操作了一定最优的，但是暴力模拟复杂度太高了。

考虑把所有操作和限制建出图，用图上的边表示关系，跑一个类似拓扑排序的东西（限制只需要一个入边被满足，操作需要所有入边被满足）即可做到 $O(n \times m)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const long long base = 13361;
const int mod = 998244353;
const int maxn = 1514;
int a[maxn][maxn],b[maxn][maxn],n,m;
long long _pow[maxn];
long long A[maxn],B[maxn];//每行的哈希值 
int rk[maxn];//B 中第 i 行在 A 中的排名
map<int,int> lsh;
queue<int> mp[maxn];
//列 m+1 是原来 A 中每行的排名，我们默认所有相邻行之间的关系都需要被修正，不需要被修正的用最开始修正列 m+1 代替 
vector<int> E[maxn<<1];//[1,m+1] 为 操作 [m+2,m+n] 为限制 
int In[maxn<<1];
stack<int> stk;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	_pow[0]=1;
	for(int i=1;i<maxn;i++) _pow[i]=_pow[i-1]*base%mod;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j],A[i]=(A[i]+a[i][j]*_pow[j]%mod)%mod;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>b[i][j],B[i]=(B[i]+b[i][j]*_pow[j]%mod)%mod;
	}
	for(int i=1;i<=n;i++) 
		if(lsh[A[i]]==0) lsh[A[i]]=lsh.size()+1;
	for(int i=1;i<=n;i++) 
		if(lsh[B[i]]==0) lsh[B[i]]=lsh.size()+1;
	for(int i=1;i<=n;i++){
		A[i]=lsh[A[i]];
		mp[A[i]].push(i);
	}
	for(int i=1;i<=n;i++) B[i]=lsh[B[i]];
	for(int i=1;i<=n;i++){
		if(mp[B[i]].empty()==true){
			cout<<"-1\n";
			return 0;
		}
		rk[i]=mp[B[i]].front();
		mp[B[i]].pop();
	}
	if(n==1){
		cout<<"0\n";
		return 0;
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			if(a[rk[i]][j]>a[rk[i+1]][j]) E[m+2+i-1].push_back(j),In[j]++;
			if(a[rk[i]][j]<a[rk[i+1]][j]) E[j].push_back(m+2+i-1),In[m+2+i-1]++;
			if(rk[i]>rk[i+1]) E[m+2+i-1].push_back(m+1),In[m+1]++;
			if(rk[i]<rk[i+1]) E[m+1].push_back(m+2+i-1),In[m+2+i-1]++;
		}
	}
	queue<int> q;
	int cnt=0;
	for(int i=1;i<=m+1;i++){
		if(In[i]==0){
			q.push(i);
			if(i<=m+1) stk.push(i),cnt++;
		}
	}
	while(q.size()>0){
		int u=q.front();
		q.pop();
		for(int v:E[u]){
			if(v<=m+1){
				In[v]--;
				if(In[v]==0){
					q.push(v);
					stk.push(v);
					cnt++;
				}
			}else{
				if(In[v]!=0){
					In[v]=0;
					q.push(v);
				}
			}
		}
	}
	if(cnt<m+1){
		cout<<"-1\n";
		return 0;
	}
	while(stk.top()!=m+1) stk.pop();
	stk.pop();
	vector<int> ans;
	while(stk.size()>0) ans.push_back(stk.top()),stk.pop();
	cout<<ans.size()<<'\n';
	for(int x:ans) cout<<x<<' ';
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

首先发现行之间的先后顺序之和它在最后一次修改中修改成了什么有关。于是倒序考虑。

倒序考虑一列什么时候可以操作。如果有两行 $i,j$ 的顺序之前没有被确定，在在这次操作被确定，而且不符合最后顺序的要求，那么这一列就是不能在这个时候被操作的。

于是可以对于每一列，记录还有多少对 $(i,j)$，第 $i$ 行和第 $j$ 行间关系如上述。只有当这个值为 $0$ 时这一行才可以操作。这可以类似一个拓扑排序解决。

但是这样要记录所有 $(i,j)$ 行之间的关系，复杂度 $O(n^3)$（$n,m$ 同阶）。我在这里卡住了。事实上只用记录结束状态两行之间的大小关系。这样就是 $O(n^2)$ 的了。

除此之外，初始状态也可能直接影响操作完之后的状态，所以可以将初始的第 $i$ 行后面加上一个 $i$。结束状态对应加上。实现上，要注意如果像样例 $3$ 有若干行完全相同，可以都按从大到小的顺序加数。

code：

```cpp
int n,m,a[N][N],b[N][N],deg[N],c[N][N],d[N],id[N];
ll pw[N],h[N];bool vis[N];
vector<int> ans;queue<int> q;
mt19937 rnd(time(0));
const ll mod=(ll)1e12+39,base=19260817;
map<ll,vector<int>> mp;
map<ll,int> hs;
il ll Mod(ll x,ll y){return x+y>=mod?x+y-mod:x+y;}
il ll qmul(ll x,ll y){
	ll ret=0;
	while(y){
		if(y&1)ret=Mod(ret,x);
		x=Mod(x,x),y>>=1;
	}
	return ret;
}
il ll qpow(ll x,int y){
	ll ret=1;
	while(y){
		if(y&1)ret=qmul(ret,x);
		x=qmul(x,x),y>>=1;
	}
	return ret;
}
void Yorushika(){
	scanf("%d%d",&n,&m);
	rep(i,1,n)rep(j,1,m)a[i][j]=read();
	rep(i,1,n)rep(j,1,m)b[i][j]=read();
	int num=rnd()%(int)1e9+1;
	rep(i,1,n)pw[i]=qpow(i,num);
	rep(i,1,n){
		ll s=0;
		rep(j,1,m)s=Mod(qmul(s,base),pw[b[i][j]]);
		mp[s].eb(i);
	}
	drep(i,n,1){
		ll s=0;
		rep(j,1,m)s=Mod(qmul(s,base),pw[a[i][j]]);
		if(!mp[s].size())return puts("-1"),void();
		id[mp[s].back()]=i,mp[s].pop_back();
		h[i]=Mod(qmul(s,base),pw[i]),a[i][m+1]=i;
	}
	rep(i,1,n){
		b[i][m+1]=id[i];
		ll s=0;
		rep(j,1,m+1)s=Mod(qmul(s,base),pw[b[i][j]]);
		hs[s]=i;
	}
	rep(j,1,m+1){
		rep(i,1,n)d[hs[h[i]]]=a[i][j];
		rep(i,1,n-1)if(d[i]<d[i+1])c[j][i]=1;else if(d[i]==d[i+1])c[j][i]=2;else deg[j]++;
		if(!deg[j])q.push(j);
	}
	while(q.size()){
		int u=q.front();q.pop();
		if(u<=m)ans.eb(u);
		rep(i,1,n-1){
			if(!vis[i]&&c[u][i]==1){
				rep(j,1,m+1)if(!c[j][i]&&!--deg[j])q.push(j);
				vis[i]=1;
			}
		}
		if(u==m+1)break;
	}
	rep(i,1,n-1)if(!vis[i])return puts("-1"),void();
	reverse(ans.begin(),ans.end());
	printf("%d\n",ans.size());
	for(int i:ans)printf("%d ",i);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

