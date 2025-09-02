# AND Graph

## 题目描述

给定一个 $m$ 个整数的集合，每个整数在 $0$ 到 $2^n-1$ 之间，以每一个整数作为顶点建无向图，当两个点 $x$ 和 $y$ 做与运算值为 $0$ 时，则认为 $x$ 和 $y$ 是连通的，即 $x$ 和 $y$ 之间有一条无向边。请求出图中连通块的个数。

## 样例 #1

### 输入

```
2 3
1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 5
5 19 10 20 12
```

### 输出

```
2
```

# 题解

## 作者：s_r_f (赞：7)

建$O(2^n)$个辅助点$i'$表示$i'$连向所有是$i'$子集的点$,$ $dfs$即可$.$

遍历的过程中如果是$i'$就遍历它的所有去掉一个元素的子集和点$i$本身$,$

如果是点$i$的话就遍历$((2^n-1)\quad xor\quad i)'.$

所以实际上并不需要开$4s,$而且空间也只用开两个$bool\quad vis[1<<22].$

不过有一说一如果想卡空间的话可以手写个$bitset$什么的$($

$code:$

```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T> void read(T &x){
	static char ch; x = 0,ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0',ch = getchar();
}
const int M = 1<<22;
int n,ALL,ans; bool vis1[M],vis2[M];
inline void search(int x,int tp){
	if (tp == 2){ if (vis2[x]) return; vis2[x] = 1,search(ALL^x,1); }
	else{ if (vis1[x]) return; vis1[x] = 1,search(x,2); int s = x; while (s) search(x^(s&-s),1),s^=(s&-s); }
}
int main(){
	int i,x;
	read(n),ALL = (1<<n)-1;
	for (i = 0; i < (1<<n); ++i) vis1[i] = 0,vis2[i] = 1;
	read(i); while (i--) read(x),vis2[x] = 0;
	for (i = 0; i < (1<<n); ++i) if (!vis2[i]) ++ans,search(i,2);
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：Namelessone (赞：6)

考虑某个数x的情况，若有y&x为0，则y必是x按位取反后的数z去掉某些位置的1后形成的数。举个例子x=(1010),则z=(0101),那么y可以为(0101),(0001),(0100),(0000)4个数，若将每个数看成图上的一个点，那么这就是明显的BFS(或者记忆化DFS），这里我使用BFS的方法，扫一遍m个点，每扫到一个点，设这个点为p，将该点按位取反的数放入队列中进行bfs，当前点可以与去掉某些位置的1形成后的数建立关系(参考前面z和y的关系),每搜到一个数，若这个数是m个数里面的数，将其与p点建立关系，并将该数取反后的数放入队列。因为若a与b能通过bfs建立关系，那么b与a也能通过bfs建立关系，所以每个数只需要被扫到一次，这也是bfs(或者记忆化dfs)成立的基础。这样进行m次bfs即可完成所有关系的建立，一共有2^22个数，所以状态数不超过2^22,时间复杂度可以接受。具体可见代码
```cpp
#include<bits/stdc++.h>

using namespace std;
int const maxn=(1<<22)+10;
int vis[maxn],mark[maxn],fa[maxn];
int a[maxn];
queue<int> q;
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++) scanf("%d",&a[i]),mark[a[i]]=1;
    int cnt=0;
    for (int i=0;i<(1<<n);i++) {
        if (!mark[i]||vis[i]) continue;
        cnt++;
        vis[i]=1;
        int ful=(1<<n)-1-i;
        if (!vis[ful]) 
        q.push(ful);
        vis[ful]=1;
        while (!q.empty()) {
            int x=q.front();
            q.pop();
            for (int j=0;j<n;j++) {
                if ((x&(1<<j))) {
                    int tmp=x-(1<<j);
                    if (!vis[tmp]) {
                        vis[tmp]=1;
                        q.push(x-(1<<j));
                        if (mark[tmp]) {
                            int fut=(1<<n)-1-tmp;
                            if (!vis[fut]) 
                                vis[fut]=1,
                                q.push(fut);
                        }
                    }
                }
            }
        }
    }
    printf("%d\n",cnt);
}

```


---

## 作者：派大那个星 (赞：6)

不难发现，在2^n中与x能连边的最大值为x异或2^(n)-1，即y=(x^(2(n)-1))。

比如 x=1010，n=5

所以 y=0101，观察可得 将y的任意一位上的1变为0，仍能与x连边，所以只要

dfs（y），在dfs中将y的子集都遍历一遍，得出答案。
```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt,n,m,a[5000005],ans,En,head[5000005],vis[5000005];
struct Edge
{
    int next,to;
}E[5000005];
void add(int from,int to)
{
    En++;
    E[En].next=head[from];
    E[En].to=to;
    head[from]=En;//前向星存图
}
void dfs(int k)
{
    vis[k]=1;
    for(int i=head[k];i;i=E[i].next)
    {
        int t=E[i].to;
        if(vis[t]==0)dfs(t);//遍历图
    }
    for(int i=1;i<=n;++i)
    if(k&(1<<(i-1))) 
    {
        int t=k^(1<<(i-1));
        if(vis[t]==0)dfs(t);//枚举y每一位
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    cnt=(1<<n)-1;//cnt表示2^(n)-1
    for(int i=1;i<=m;i++)scanf("%d",&a[i]),add(a[i],a[i]^cnt);
    for(int i=1;i<=m;i++)//枚举连通块，累加答案
    	if(vis[a[i]]==0)vis[a[i]]=1,dfs(a[i]^cnt),ans++;
    printf("%d\n",ans);//愉快地输出
}```

---

## 作者：_Cheems (赞：3)

无敌建图题。

如果接触过 $\rm SOSdp$ 之类与子集有关的东东，那么看到 $a \& b=0$，便可想到转换为子集的形式：$b \in \neg a$。

思考怎么将枚举子集表现在图上。发现让每个点 $u$，向所有是 $u$ 子集且只比 $u$ 少一位 $1$ 的点连有向边即可。这样从 $u$ 出发就恰好遍历了其所有子集。

为了体现 $\neg a$，还需让 $a\to \neg a$ 连边。问题解决了吗？没有，因为题目还限定了部分点无法访问，如果直接跳过的话不一定能遍历到所有子集。

于是建立分层图，将“枚举子集”这部分的图单独拎出来，记原图为 $A$，新图为 $B$。按照此规则连边：

$A(u)\to B(\neg u)$。准备进入 $B$ 枚举子集。

$B(u)\to B(v)$。$v$ 满足只比 $u$ 少一个 $1$。开始在 $B$ 中枚举。

$B(u)\to A(u)$。最后返回 $A$，于是实现了 $u$ 和 $u\&v=0$ 的 $v$ 之间连通。
### 代码
其实一个 `bool` 数组就够了，然后用 `bitset` 优化复杂度。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1 << 22, MA = N - 1;
int n, m, a[N + 5], ans; 
bitset<N << 1> vis; 

inline void dfs(int u){
	if(vis[u]) return ;
	vis[u] = 1;
	if(u < N) dfs((MA ^ u) + N);
	else{
		dfs(u - N);
		for(int i = 0; i < 22; ++i) if(((u - N) >> i) & 1) dfs(u - (1 << i));
	}
}
int main(){
	cin >> n >> m;
	for(int i = 0; i < N; ++i) vis[i] = 1;
	for(int i = 1; i <= m; ++i) scanf("%d", &a[i]), vis[a[i]] = 0;
	for(int i = 1; i <= m; ++i) if(!vis[a[i]]) ++ans, dfs(a[i]);
	cout << ans;
	return 0;
}
```

---

## 作者：Tenshi (赞：2)

思想比较有意思的图论题。

> 为了符合习惯，这里约定 $n$​​​ 代表题目所给的点的**编号**，$U=2^m - 1$​​ 是**值域**（同时也代表**全集**）。

 考虑建图。

首先对图进行加点，将点数补至 $2^m$。

记一个点的编号为 $u$​​​，那么它能够到达的**极大的点编号**为 $go = u\oplus U$​​​，并且 $u$​​ 能够到达的所有点编号一定是 $go$​​ 的**子集**，考虑将 $u$ 向 $go$ 连边。

因此对于题目所给的每个点 $u$，我们需要设计一个算法，将它能够到达的所有点进行标记（访问），并相应地更新答案。

具体地，可以从 $go = u\oplus U$ 出发做一遍 dfs：沿着 $go$ 能到达的点继续搜。但同时，$go$ 的子集也需要标记，直接枚举是 $O(2^m)$ 肯定行不通，故考虑对 $go$ 对应的二进制数位进行枚举，这样就能将枚举的复杂度控制在 $O(m)$。

```cpp
inline void read(int &x){
    int s=0; x=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0' && ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=1<<22|1, M=N;

int id[N];
int n, m;

struct Edge{
	int to, next;
}e[M];

int h[N], tot;

void add(int u, int v){
	e[tot].to=v, e[tot].next=h[u], h[u]=tot++;
}

bool vis[N];

void dfs(int u){
	vis[u]=true;
	rep(i,0,m-1) if(u>>i&1){
		int go=u^(1<<i);
		if(!vis[go]) dfs(go);
	}
	
	for(int i=h[u]; ~i; i=e[i].next){
		int go=e[i].to;
		if(!vis[go]) dfs(go);
	}
}

int main(){
	memset(h, -1, sizeof h);
	cin>>m>>n;
	int U=(1<<m)-1;
	rep(i,1,n) read(id[i]);
	
	rep(i,1,n) add(id[i], id[i]^U);
	
	int res=0;
	rep(i,1,n) if(!vis[id[i]]){
		res++;
		vis[id[i]]=true;
		dfs(id[i]^U);
	}
	cout<<res<<endl;
		
	return 0;
}
```

---

## 作者：Vitamin_B (赞：1)

# 思路
这题当然不能暴力建图，会超时。不难发现，$a\&b=0$（此处的 $\&$ 指按位与）时，$\forall b\in\neg a$。于是我们只要枚举每个 $\neg a$ 的子集就行了。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int n, maxx, a[4200005], sum;
bitset <4200005> vis, ina; //bitset 优化，另外切忌用 vector!
void dfs (int x) {
	vis[x] = 1;
	if (ina[x] && ! vis[x ^ maxx]) //如果 x 在 a 中，x ^ maxx 就是 x & b = 0 时 b 能达到最大的值。
		dfs (x ^ maxx);
	for (int i = x; i; i ^= i & -i)
		if (! vis[x ^ (i & -i)])
			dfs (x ^ (i & -i));
	return ;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> maxx >> n;
	maxx = (1 << maxx) - 1;
	for (int i = 0; i < n; ++ i)
		cin >> a[i], ina[a[i]] = 1;
	for (int i = 0; i < n; ++ i)
		if (! vis[a[i]])
			vis[a[i]] = 1, dfs (a[i] ^ maxx), ++ sum;
	cout << sum;
	return 0;
}
```

---

## 作者：Luciylove (赞：1)

讲个笑话，这个是 $*2500$。非常 tricky。

考虑 $x$ 和 $y$ 按位与为 $0$ 如何判定。

把 $01$ 串看成集合，那么就是 $y$ 是 $x$ 按位取反后的一个子集。

那么自然而然想到 SOS DP，我们考虑模仿高维前缀和，每次去掉一位连边即可。

然后我们考虑 $x \to \neg x$，然后我们每次直接染色求连通块，然后从 $x$ 开始 dfs 即可。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; i ++)
#define per(i, r, l) for (int i = r; i >= l; i --)

/*\yhx12243/ 鱼大保佑*/
/*
  你说的对
  但是你将在一场模拟赛中扮演“没有时间，没有实力，没有资源”的信息学竞赛选手
  与没有同情心的出题人共同发掘：“60也算赢，一题夸自己”的奥赛本质。*/

using namespace std;

const int _ = 5e6 + 5;
int lim;
int n, m, cnt, ans;
int vis[_], a[_];
int hd[_], ver[_], nxt[_];
void add (int x, int y) {
	ver[++ cnt] = y, nxt[cnt] = hd[x], hd[x] = cnt; 
}

void dfs (int x) {
	vis[x] = 1;
	for (int i = hd[x]; i; i = nxt[i]) if (! vis[ver[i]]) dfs(ver[i]);
	for (int i = 0; i < n; i ++) {
		if (!(x & (1 << i))) continue ;
		int y = x ^ (1 << i);
		if (! vis[y]) dfs(y);
	}
}
int main () {
	cin >> n >> m;
	lim = (1 << n) - 1;
	rep(i, 1, m) {
		scanf("%d", & a[i]);
		add(a[i], lim ^ a[i]);
	}
	rep(i, 1, m) if (! vis[a[i]]) {
		vis[a[i]] = 1;
		dfs(a[i]);
		ans ++;
	}
	cout << ans;
	return 0;
}
```


---

## 作者：Z1qqurat (赞：0)

非常好 trick 题，爱来自穿越火线。

首先发现 $x$ 能连的边其实就是 $\neg x$ 的所有子集的点。考虑将 $x \rightarrow \neg x$，$x$ 向其所有只比它少一位的点连边，那么直接 dfs 就可以了。但是我们这里取的只有这个大小为 $m$ 的集合内的点，怎么让连的点都在这个集合内并且还能保证原图的性质？

考虑分层图（建一个辅助图，$x$ 对应 $x'$），那么我们连边：

* $x \rightarrow \neg x$。

* $x' \rightarrow$ 所有 $x$ 子集内比它只少一位的点的辅助点。

* $x' \rightarrow x$。

那么我们从原图中所有集合内点出发 dfs，相当于在原图 $\rightarrow$ 辅助图的边都是起到一个限定是在该集合内的作用（相当于原题意中的连边），辅助图内的边表示从一个点到它的子集，类似于建虚点优化建图的处理。

然后直接 dfs，注意边不要提前存下来，dfs 的时候枚举出点就可以了，要不然会 MLE。善用 bitset！！！

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = (1 << 22);
int n, m, a[N], lim, ans;
bitset <N> used;
bitset <N << 1> vis;

void dfs(int u) {
    vis.set(u, 1);
    if(u < lim) {
        if(!used[u]) return ;
        int v = lim + (u ^ (lim - 1));
        if(!vis[v]) dfs(v);
    }
    else {
        u -= lim;
        if(!vis[u] && used[u]) dfs(u);
        for (int i = 0; i < 22; ++i) {
            if((u >> i) & 1) {
                int v = (u ^ (1 << i)) + lim;
                if(!vis[v]) dfs(v);
            }
        }
    }
    return ;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m, lim = (1 << n);
    for (int i = 1; i <= m; ++i) cin >> a[i], used.set(a[i], 1);
    for (int i = 1; i <= m; ++i) if(!vis[a[i]]) dfs(a[i]), ans++;
    cout << ans << "\n";
    return 0;
}

---

## 作者：Zhddd_ (赞：0)

聪明题。

观察题目性质，我们可以把连边转化为 $x$ 向 $\neg x$ 的子集的有向边。

这样的边太多，连不完，于是考虑优化。具体地，采用分层图，连边如下：

- $x$ 向 $\neg x^{\prime}$ 连有向边。
- $x^{\prime}$ 向恰好比自己少一个 $1$ 的子集连有向边。
- $x^{\prime}$ 向 $x$ 连有向边。

最后，对于题目所给的元素，如果没有被访问过，就尝试 DFS，并 $ans\gets ans+1$。

注意到边如果全部连完会 MLE，所以可以在 DFS 里直接处理出连边。

时间复杂度 $O(n\times 2^n)$。

```cpp
const int N = (1 << 22);
int n, m, lim, res, a[N], st[N];
bitset<N * 2> vis;
void dfs(int u) {
	vis[u] = 1;
	if (u < lim) {
		if (st[u]) {
			int v = lim + ((lim - 1) ^ u);
			if (!vis[v]) dfs(v);
		}
	} else {
		for (int s = u - lim; s; s -= (s & (-s))) {
			int v = (u ^ (s & (-s)));
			if (!vis[v]) dfs(v);
		}
		if (!vis[u - lim]) dfs(u - lim);
	}
}
int main() {
	cin >> n >> m;
	lim = (1 << n);
	for (int i = 0; i < m; i++) cin >> a[i], st[a[i]] = 1;
	for (int i = 0; i < m; i++) if (!vis[a[i]]) dfs(a[i]), res++;
	cout << res << "\n";
	return 0;
}
```

---

## 作者：junxis (赞：0)

怎么感觉题解不知所云。

我们发现题目里的连边条件等价于 $x$ 向 $\lnot x$ 的所有子集连边。

那么我们考虑建出这样的一个图：

$(a_i,1) \rightarrow (\lnot a_i, 2)$。

$(x,2) \rightarrow (x-2^b,2)$，需额外满足 $x \operatorname{and} 2^b \not = 0$，表示去掉一位。

$(x,2) \rightarrow (x,1)$。

解释：

我们用两层来刻画“子集”这个事情，第一层都是原数组中的数，第二层是第一层的数取非后的所有子集。

第一行表示从原数组转移到第二层。

第二行是用了 sum over subset dp 的 trick 来在第二层中遍历子集。

第三行表示第二行搞出来的子集随时可能成为一个原数组中的数，所以要回去打标记。

然后只需要遍历所有 $a_i$，一旦发现没打标记就开始沿上面的图 dfs，表示找到了一个新的联通块。

时间复杂度 $O(n2^n)$      。

```cpp
const int V = 1 << 22;
int n, m, a[V + 5], S;
bitset<V> exist, vis0, vis1;

void dfs(int x, int ty) {
	if (ty == 0) {
		if (vis0[x]) return;
		vis0[x] = true;
		if (exist[x]) dfs(S ^ x, 1);
	} else {
		if (vis1[x]) return;
		vis1[x] = true;
		dfs(x, 0);
		int t = x;
		while (t) {
			int low = t & (-t);
			dfs(x - low, 1);
			t -= low;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n >> m;
	S = (1 << n) - 1;
	rep(i, 1, m) {
		cin >> a[i];
		exist[a[i]] = true;
	}
	int ans = 0;
	rep(i, 1, m) if (!vis0[a[i]]) {
		ans++;
		dfs(a[i], 0);
	}
	cout << ans << "\n";
}
```

---

## 作者：Jinzixun (赞：0)

首先，暴力的思路非常好想，两个两个判断是否有边，然后通过暴搜判断连通块，时间复杂度 $O(m^2)$，显然会超时。

假设有一个数 $u$，有一个 $v$ 使得 $u \operatorname{and} v=0$，显然，在二进制下，$u$ 为 $1$ 的位，$v$ 一定为 $0$，如果为 $0$，那么都可以。

根据这个性质，考虑对于某个数 $a_i$，暴搜所有可以连通的数，最后输出连通块个数。

在实现的时候，我们先考虑将这个数的每一位取反，这是最大的可能数，接下来在通过搜索找到每种不一样的方案。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e6 + 5;
int n, m, cnt, ans, a[N], head[N], to[N], nxt[N];
bool vis[N];
void with(int u, int v){
	to[++cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
}//链式前向星
void dfs(int x){
	vis[x] = true;
	for(int i = head[x]; i; i = nxt[i])	if(!vis[to[i]])	dfs(to[i]);
	for(int i = 0; i < n; i++){
		if(x & (1 << i) && !vis[x - (1 << i)])	dfs(x - (1 << i));//依次减少1的个数。
	}
}
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		scanf("%d", &a[i]);
		with(a[i], a[i] ^ ((1 << n) - 1));
	}
	for(int i = 1; i <= m; i++){
		if(!vis[a[i]]){
			vis[a[i]] = true;
			dfs(a[i] ^ ((1 << n) - 1));//最开始搜索这个数的每位取反。
			ans++;//统计连通块个数。
		}
	}
	printf("%d", ans);
	return 0;
}
```

---

