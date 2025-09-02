# [TJOI2014] Alice and Bob

## 题目描述

Alice 和 Bob 发明了一个新的游戏。给定一个序列 $\{x_0,x_1,\cdots,x_{n-1}\}$，Alice 得到一个序列 $\{a_0,a_1,\cdots,a_{n-1}\}$，其中 $a_i$ 表示以 $x_i$ 结尾的最长上升子序列的长度；Bob 得到一个序列$\{b_0,b_1,\cdots,b_{n-1}\}$，其中 $b_i$ 表示以 $x_i$ 开头的最长下降子序列的长度。Alice 的得分是序列 $\{a_i\}$ 的和，Bob的得分是序列 $\{b_i\}$ 的和。


## 说明/提示

### 数据范围

对于 $30\%$ 的数据，$N \le 1000$。

对于 $100\%$ 的数据，$N \le 10^5$。


## 样例 #1

### 输入

```
4
1 2 2 3```

### 输出

```
5```

## 样例 #2

### 输入

```
4
1 1 2 3```

### 输出

```
5```

# 题解

## 作者：allqpsi (赞：6)

比赛时没做出来，现在来打题解了。

首先我们拿到一个数组 $a$ 我们便有了一个贪心思路：让 $a_{i}$ 更大的数尽可能小，若两个数的 $a_{i}$ 一样，则让靠后的那个数尽可能小。

为什么是让靠后的那个数尽可能小呢？因为若是前面的数更小，后面的便可从前面的数推过去，就不符合 $a_{i}$ 了。

那我们又推出一个东西：对于一个 $a_{i}$ 它肯定从离它最近的 $a_{i}-1$ 推过来，因为更靠后的那个 $a_{i}-1$ 是最大的。

那我们从那个数推过来知道了，我们便给推过来的那个数与 $i$ 连边，这样便会得到一个树。

这时，我们根据插入边时的顺序的反序跑 dfs 就得到最优的 $x$ 数组了。

为什么呢？别的题解没怎么讲这一点，我来分析一下：插入边的顺序必定是位置在前的数先建边的。我们将此反过来，便可使两个 $a_{i}$ 相等的数更后的数更小。又因为 dfs 的性质，推过来的那个数必定比当前的数更小。因此其 $dfn$ 序便为最优的 $x$ 数组。

如图（有点扭，请别见怪）：

![](https://cdn.luogu.com.cn/upload/image_hosting/0twlb1ua.png)

此图是样例一建出来的图，显然在图中，点一在 $dfn$ 序中的值小于点三的值，点三的值小于点二的值。以此类推，可见此树的 $dfn$ 序必满足 $a$ 数组。因此 $x$ 数组便为：1 4 2 3 了。

貌似前向星更简单实现插入边时的顺序的反序，不过个人更喜欢向量。

还有一点的话就是树的根节点是零，这会让 $dfn$ 序加一，可显然并不会影响结果。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,n) for(int i=1;i<=n;i++)
#define frep(i,n) for(int i=n;i>=1;i--)
#define zfrep(i,n) for(int i=n-1;i>=0;i--)
#define set(ai) memset(ai,0,sizeof(ai));
using namespace std;
const int N=1e5+5;
int n,a,ai[N],dfn[N],l=0,ans=0,f[N];
vector<int>vi[N];
void dfs(int x,int fa){
	dfn[x]=++l;
	zfrep(i,vi[x].size()){
		int v=vi[x][i];
		if(v==fa)continue;
		dfs(v,x);
	}
}
signed main(){
	cin>>n;
	rep(i,n){
		cin>>a;
		vi[ai[a-1]].push_back(i);
		ai[a]=i;
	}
	dfs(0,0);
	l=0;
	frep(i,n){//cout<<dfn[i]<<' ';
		if(f[l]<dfn[i])a=++l,f[l]=dfn[i];
		else a=upper_bound(f+1,f+1+l,dfn[i])-f;
		f[a]=min(f[a],dfn[i]);
		ans+=a;
	}cout<<ans;
}
```

~~制作不易，点个赞呗。~~

---

## 作者：MorsLin (赞：6)

原序列为$x$，输入的序列为$a$。  
因为题目中是**上升子序列**和**下降子序列**，所以原序列中相同的元素没有贡献，因此不妨设$x$为$1$~$n$的一个排列  
$a_i$是以$x_i$为结尾的最长上升子序列的长度，所以对于所有的$a_k = a_i - 1$，一定存在至少一个$k$使$x_k < x_i$  
如果要使Bob得分尽量高，可以贪心的使$a_i$较大的$x_i$尽量小，$a_i$相同的使$i$较大的$x_i$（即相对靠后的元素）尽量小

考虑如何构造出符合上述条件的$x$  
对于$i$，我们可以向离它最近的满足$a_k = a_i-1$的$k$连一条边，这样可以构造出一棵树（以$0$为根）  
我们直接对这棵树求出它的dfs序数组$dfn$，则$dfn$就是一个满足上述条件的序列  
因为前向星有一个特殊的性质：晚连上的边会被先遍历到。同时因为dfs先序遍历的特性（节点的dfs序小于它的子树中任意点的dfs序），求出来的$dfn$一定是满足上述所有条件的

$0$是虚根，可以方便我们遍历，不过它会使$x_i$全都加$1$，但这样显然不会对答案造成影响

最后对$dfn$数组统计答案就可以了

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
using namespace std;
LL read() {
	LL k = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-') f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
		k = k * 10 + c - 48, c = getchar();
	return k * f;
}
struct zzz {
	int t, nex;
}e[100010 << 1]; int head[100010], tot;
inline void add(int x, int y) {
	e[++tot].t = y;
	e[tot].nex = head[x];
	head[x] = tot;
}
int a[100010], b[100010], dfn[100010], cnt, num;
void dfs(int x, int fa) {
	dfn[x] = ++cnt;
	for(int i = head[x]; i; i = e[i].nex) {
		if(e[i].t == fa) continue;
		dfs(e[i].t, x);
	}
}
int main() {
	int n = read();
	for(int i = 1; i <= n; ++i) {
		int x = read();
		add(a[x-1], i); add(i, a[x-1]); a[x] = i;
	}
	dfs(0, 0); LL ans = 0;
	for(int i = n; i >= 1; --i) {
		int pos = 0;
		if(dfn[i] > b[num]) b[++num] = dfn[i], pos = num;
		else pos = upper_bound(b+1, b+num+1, dfn[i]) - b;
		b[pos] = min(b[pos], dfn[i]);
		ans += (LL)pos;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Mychael (赞：5)

[Mychael的无声乐章](https://i.cnblogs.com/EditPosts.aspx?postid=9035227)

题中所给的最长上升子序列其实就是一个限制条件
我们要构造出最大的以$i$开头的最长下降子序列，就需要编号大的点的权值尽量小

相同时当然就没有贡献，所以我们不妨令权值为一个$1$到$n$的排列

考虑如何满足限制条件

对于所有$a[i] = v$的点，点与点之间一定是单调下降的，连有向边

对于位置$i$，如果$a[i] = v$，那么$i$至少要比上一个$a[j] = v - 1$的位置大，连有向边

然后用大顶堆拓扑排序即可得到每个点最优的权值
$O(nlogn)$求一遍最长下降子序列长度即可

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<cstring>
#include<algorithm>
#define LL long long int
#define Redge(u) for (int k = h[u],to; k; k = ed[k].nxt)
#define REP(i,n) for (int i = 1; i <= (n); i++)
#define cls(s) memset(s,0x3f3f3f3f,sizeof(s))
using namespace std;
const int maxn = 100005,maxm = 100005,INF = 1000000000;
inline int read(){
	int out = 0,flag = 1; char c = getchar();
	while (c < 48 || c > 57){if (c == '-') flag = -1; c = getchar();}
	while (c >= 48 && c <= 57){out = (out << 3) + (out << 1) + c - 48; c = getchar();}
	return out * flag;
}
int h[maxn],ne = 2,de[maxn];
struct EDGE{int to,nxt;}ed[maxn << 1];
inline void build(int u,int v){
	ed[ne] = (EDGE){v,h[u]}; h[u] = ne++;
	de[v]++;
}
int last[maxn],n,a[maxn],cnt,x[maxn],f[maxn],bac[maxn];
priority_queue<int> q;
void work(){
	REP(i,n) if (!de[i]) q.push(i);
	int u;
	while (!q.empty()){
		u = q.top(); q.pop();
		x[u] = ++cnt;
		Redge(u) if (!(--de[to = ed[k].to])) q.push(to);
	}
}
int getn(int t){
	int l = 0,r = n,mid;
	while (l < r){
		mid = (l + r + 1) >> 1;
		if (bac[mid] < t) l = mid;
		else r = mid - 1;
	}
	return l;
}
void cal(){
	cls(bac); bac[0] = 0;
	for (int i = n; i; i--){
		f[i] = getn(x[i]) + 1;
		bac[f[i]] = min(bac[f[i]],x[i]);
	}
	LL ans = 0;
	REP(i,n) ans += f[i];
	printf("%lld\n",ans);
}
int main(){
	n = read();
	REP(i,n) a[i] = read();
	for (int i = 1; i <= n; i++){
		if (a[i] > 1) build(last[a[i] - 1],i);
		if (last[a[i]]) build(i,last[a[i]]);
		last[a[i]] = i;
	}
	work();
	cal();
	return 0;
}

```

---

## 作者：xiaomimxl (赞：4)

写在文章前：似乎大家都在用 dfs，这里介绍一个不同的——拓扑排序 $+$ 贪心

# 题目大意：

给出一个序列的以每一项结尾的 LIS 的长度 $a$，求一个序列，使得以每一项为开头的最长下降子序列的长度之和最大。

$n \le 10^5$。

# 思路分析：

一个结论：最优解一定是一个排列，因为如果两个数字的大小相同，完全可以区别他们的大小，以得到更多的贡献。

考虑的 $a$ 给定的限制，显然对于所有的相同大小的 $a$，前一项 $a_{p1}$ 要大于后一项 $a_{p2}$，否则一定会产生更长的上升子序列。连边 $p1$ $\rightarrow$ $p2$ 表示 $p2$ 的值小于 $p1$。

对于 $i$，找到上一次出现 $a[i]-1$ 的位置，并连边 $ pos_{a[i]-1} $ $\rightarrow$ $i$ ，表示 $i$ 要大于此位置的值。

然后进行贪心的操作，每次在所有入度为 $0$ 的点中选择编号最大的并赋上最小的权值。确定数值之后依次确定 $b$ 的值就好了。

正确性显然，因为对于相同的 $a_x$ 来说我们会优先考虑最靠后的 $last$，同时靠前的不会向 $last$ 后边连边。

总时间复杂度为 $O(n \log n)$，主要是 BIT 的复杂度。


# Code
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<cctype>
#include<queue>
#include<vector>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define go(u) for(int i=head[u],v=e[i].to;i;i=e[i].last,v=e[i].to)
typedef long long LL;
typedef pair<int,int> pii;
inline int gi(){
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
  while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
  return x*f;
}
template<typename T>inline bool Max(T &a,T b){return a<b?a=b,1:0;}
template<typename T>inline bool Min(T &a,T b){return a>b?a=b,1:0;}
const int N=1e5 + 7;
int n,edc;
int head[N],ind[N],lst[N],a[N],b[N],f[N];
struct edge{
	int last,to;
	edge(){}edge(int last,int to):last(last),to(to){}
}e[N*2];
void Add(int a,int b){
	e[++edc]=edge(head[a],b),head[a]=edc;
	++ind[b];
}
int tr[N];
int lowbit(int x){return x&-x;}
void modify(int x,int y){for(int i=x;i<=n;i+=lowbit(i)) Max(tr[i],y);}
int query(int x){int res=0;for(int i=x;i;i-=lowbit(i)) Max(res,tr[i]);return res;}
priority_queue<int>Q;
void topo(){
	rep(i,1,n) if(!ind[i]) Q.push(i);int tmp=0;
	while(!Q.empty()){
		int u=Q.top();Q.pop();
		b[u]=++tmp;
		go(u)
			if(--ind[v]==0) Q.push(v);
	}
}
int main(){
	n=gi();
	rep(i,1,n){
		a[i]=gi();
		if(lst[a[i]]) Add(i,lst[a[i]]);
		if(lst[a[i]-1]) Add(lst[a[i]-1],i);
		lst[a[i]]=i;
	}
	topo();
	LL ans=0;
	for(int i=n;i;--i){
		f[i]=query(b[i]-1)+1;
		modify(b[i],f[i]);
		ans+=f[i];
	}
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：XFlypig (赞：3)

[P3971 [TJOI2014] Alice and Bob](https://www.luogu.com.cn/problem/P3971)

挺奇妙一贪心，思路很流畅，一步步来分析。

首先发现序列 $x$ 如果如果是个排列答案更优，如果有重复元素，那我们找到一个前面已经有过的数字，把他前面所有数都加一，原来的 $b$ 序列肯定不会更劣，又因为题目保证至少可以由一个排列得到，所以我们用排列分析。

然后因为 $a$ 序列对应的 $x$ 排列不唯一，所以我们尝试找到最优的那个排列，然后算出 $b$ 来即可。

这里贪心的想就是越往后的数越小越好，这里严谨证明不是很会，感性理解吧，然后找一找性质。

+ 性质一：$a$ 相同的数，肯定是单调递减的。

+ 性质二：对于每个数 $x_i$，他前面必有一个 $j$ 满足 $a_j = a_i - 1$ 且 $x_j < x_i$。

+ 性质三：对于任意一个 $j$ 满足 $j < i$ 且 $a_j \ge a_i$，必须满足 $x_j > x_i$。

由性质一和性质二可得 $a_i$ 的转移在满足 $j < i$ 且 $a_j = a_i - 1$ 的 $j$ 中，从最靠后的那个转移是一定可行的，由此可以发现每个数都有一个转移前驱，很容易联想到树，然后从前驱向当前点连边，对于 $a_i = 1$ 的点建个虚点 $0$ 方便后续遍历。

至此我们得到了一颗树，如果你按加边顺序倒序遍历一遍后，会发现得到了一个序列 $x$，而他就是我们想要的答案，在上面求个 $b$ 数组就是答案了。

至于证明，我看其他题解没看懂所以才来写的这篇，也不算严谨证明。

**首先遍历这颗树得到的序列是指这个**，为了方便我就这么说了。

```cpp
void dfs(int u)
{
    x[u] = cnt ++ ;
    for (int i = h[u]; ~i; i = ne[i])
        dfs(e[i]);
}
```

首先这颗树画成分层图，其每一层的 $a$ 的值是一样的。

然后可以发现我们得到的序列必然满足性质二，而倒序遍历边会满足性质一和性质三，也就是相同的数先遍历后面的，这些画图都能看出来。

那它是否满足贪心呢？~~画图也能看出来。~~

因为我们建树是找前面满足条件的最靠后的一个数，所以每一层的数是把他们分了几块，互不相交。

比如第一层的 $a_i = 1$ 的点其是就是把这个序列分成了好几块，而他们的子树就代表着它和后一个 $a_i = 1$ 的点之间的区间，下面的几层也是把自己所在的块又分成了更小的几块，有点抽象，你可以把笛卡尔树那张图拿出来，然后把二叉树改成不知道几叉树（每个结点的儿子数不一定一样），差不多就那样。

所以我们倒序遍历边可以时使得越往后的数越小，且同时满足三个性质或者说限制。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010;

int n;
int h[N], e[N], ne[N], idx;
int w[N], p[N], cnt;
int last[N], tr[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

int lowbit(int x)
{
    return x & -x;
}

int query(int x)
{
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res = max(res, tr[i]);
    return res;
}

void update(int x, int v)
{
    for (int i = x; i <= n; i += lowbit(i)) tr[i] = max(tr[i], v);
}

void dfs(int u)
{
    p[u] = cnt ++ ;
    for (int i = h[u]; ~i; i = ne[i])
        dfs(e[i]);
}

int main()
{
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &w[i]), last[w[i]] = i;
        add(last[w[i] - 1], i);
    }
    
    dfs(0);
    
    LL res = 0;
    for (int i = n; i; i -- )
    {
        int t = query(p[i]) + 1;
        update(p[i], t), res += t;
    }
    
    cout << res << endl;
    
    return 0;
}

```

---

## 作者：Little_Cancel_Sunny (赞：2)

## 题意

给一个长度 $n$ 的序列 $a$，其表示一个位置序列 $x$ 以 $x_i$ 为结尾的一个子序列的最长上升子序列的长度。

## 思路

1. 由于这个子序列很好构建所以考虑先构建出原序列 $x$ 再求解。

2. 那么如何构造？观察序列 $a$ 可以发现当 $a_i = a_{i-1}$ 时 $x_i < x_{i-1}$ 那么我们就可以通过这个性质约束序列 $x$。

3. 使用何种顺序构造呢？我们先考虑如何约束序列 $x$ 对于上面的性质，是不是在我们遍历序列 $a$ 时，使 $a_i$ 比 $a_{i-1}$ 先遍历到就行了，并且可以发现 $a_i$ 一定是由最近的 $a_i-1$ 转移，于是考虑在树上得到 dfs 序，利用链式前向星的性质：先插入的边后遍历。就可以满足这个性质，以样例为例：![](https://cdn.luogu.com.cn/upload/image_hosting/paio89of.png)蓝色数字为遍历的顺序，红色为 dfs 序。

4. 如上图，有一个 $0$ 号节点，它也有一个 dfs 序，但是显而易见其对答案没有影响，所以我们不用管它。

5. 得到原序列后对于新序列 $b$ 求以 $b_i$ 为结尾的最长下降子序列的长度和也就没什么难度了。

## code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=1e6+15;

int h[N],to[N],ne[N],idx=0;
int last[N];
int n;
int a[N],b[N];
int dfs[N];
int cnt=0;
int len=0;

void add(int u,int v)
{
	to[++idx]=v;
	ne[idx]=h[u];
	h[u]=idx;
}

void get_dfs(int u,int fa)
{
	dfs[u]=cnt++;
	dfs[u]--;
	for(int i=h[u];i!=-1;i=ne[i])
	{
		int v=to[i];
		if(v==fa)
		{
			continue;
		}
		get_dfs(v,u);
	}
}

signed main()
{
	memset(h,-1,sizeof h);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		add(last[a[i]-1],i);
		add(i,last[a[i]-1]);
		last[a[i]]=i;
	}
	get_dfs(0,-1);
	
	int loc=0;
	int ans=0;
	for(int i=1;i<=n/2;i++)
	{
		int l=dfs[i];
		dfs[i]=dfs[n-i+1];
		dfs[n-i+1]=l;
	}
	for(int i=1;i<=n;i++)
	{
		if(dfs[i]>b[len])
		{
			loc=++len;
			b[len]=dfs[i];
		}
		else
		{
			loc=upper_bound(b+1,b+len+1,dfs[i])-b;
		}
		b[loc]=min(b[loc],dfs[i]);
		ans+=loc;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Thunder_S (赞：2)

## Solution

由于 $x$ 中相同的元素没有贡献，因此我们钦定 $x$ 是 $1\sim n$ 的排列。

题目给出了 $a$ 序列，要最大化 $b$ 序列。那么我们可以根据 $a$ 序列来约束 $x$ 序列，从而得到最大的 $b$ 序列。

对于 $i<j$，如果 $a_i\ge a_j$，则说明 $x_i>x_j$，反之则可以将 $x_j$ 接在 $x_i$ 后面。

如果 $a_i+1=a_j$，则至少有一个 $i$ 满足 $x_i<x_j$。

那我们可以尝试用 $\mathrm{dfs}$ 来解决这个问题。

对于每个 $a_i$，找到最靠近的 $a_j$ 满足 $a_j+1=a_i$，连一条 $(i,j)$ 的边。

注意要使用前向星，因为前向星的特性就是**后加入的边先遍历**。

然后求出 $\mathrm{dfs}$ 序，可以证明 $\mathrm{dfs}$ 序就是 $x$ 序列。

求出 $x$ 序列后，可以用 $\mathcal O(n\log n)$ 求出 $b$ 序列。

## Code

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100005
#define ll long long
using namespace std;
struct node
{
    int to,next;
}a[N<<1];
int n,x,tot,cnt,len,t[N],head[N],dfn[N],b[N],c[N];
ll ans;
void add(int x,int y)
{
    a[++tot].to=y;
    a[tot].next=head[x];
    head[x]=tot;
}
void dfs(int x,int fa)
{
    dfn[x]=++cnt;
    for (int i=head[x];i!=-1;i=a[i].next)
    {
        int v=a[i].to;
        if (v==fa) continue;
        dfs(v,x);
    }
}
int main()
{
    freopen("alice.in","r",stdin);
    freopen("alice.out","w",stdout);
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
    {
        scanf("%d",&x);
        add(t[x-1],i);add(i,t[x-1]);
        t[x]=i;
    }
    dfs(0,-1);
    for (int i=1;i<=n;++i)
        --dfn[i];
    for (int i=1;i<=n;++i)
        b[i]=dfn[n-i+1];
    len=0;
    for (int i=1;i<=n;++i)
    {
        int l=1,r=len,mid;
        while (l<=r)
        {
            mid=(l+r)>>1;
            if (b[i]>c[mid]) l=mid+1;
            else r=mid-1;
        }
        len=max(len,l);
        c[l]=b[i];
        ans=ans+(ll)l;
    }
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：Astatinear (赞：1)

### [P3971 [TJOI2014] Alice and Bob](https://www.luogu.com.cn/problem/P3971)

我感觉我的智商再次受到了严重的侮辱。也有可能是我太困了。

先抓住一些性质，发现对于 $a_i$ 相同的位置，他们对应的 $x$ 必然是单减的，否则就不会是最长上升子序列长度 $=a_i$。

考虑对于每一个 $a_i$，发现他一定是从最近的 $j\in[1,i-1],a_j=a_i-1$ 转移过来的，这个对应上面那个性质应该可以简单证明。

这样我们可以考虑通过 $i\to j$ 连边建出一颗树。（特别的 $a_i=1$ 时，我们建一个虚点 $0$，然后 $0\to i$）。

注意到同层的必然按照我们建边的顺序单调递减，这个是我们最开始的第一个性质。

有一个很显然的填写方式是填入儿子反过来的 $\text{BFS}$ 序。

注意到要让最长下降子序列的总和最大，所以这样肯定是不对的，我们希望层与层之间也要互相产生贡献。注意到最好的办法是填入儿子反过来的 $\text{DFS}$ 序，因为这样可以让前面的尽可能大，而不会按照层一个一个填进去，能够更多的产生下降子序列。

---

