# Beavermuncher-0xFF

## 题目描述

"Eat a beaver, save a tree!" — That will be the motto of ecologists' urgent meeting in Beaverley Hills.

And the whole point is that the population of beavers on the Earth has reached incredible sizes! Each day their number increases in several times and they don't even realize how much their unhealthy obsession with trees harms the nature and the humankind. The amount of oxygen in the atmosphere has dropped to 17 per cent and, as the best minds of the world think, that is not the end.

In the middle of the 50-s of the previous century a group of soviet scientists succeed in foreseeing the situation with beavers and worked out a secret technology to clean territory. The technology bears a mysterious title "Beavermuncher-0xFF". Now the fate of the planet lies on the fragile shoulders of a small group of people who has dedicated their lives to science.

The prototype is ready, you now need to urgently carry out its experiments in practice.

You are given a tree, completely occupied by beavers. A tree is a connected undirected graph without cycles. The tree consists of $ n $ vertices, the $ i $ -th vertex contains $ k_{i} $ beavers.

"Beavermuncher-0xFF" works by the following principle: being at some vertex $ u $ , it can go to the vertex $ v $ , if they are connected by an edge, and eat exactly one beaver located at the vertex $ v $ . It is impossible to move to the vertex $ v $ if there are no beavers left in $ v $ . "Beavermuncher-0xFF" cannot just stand at some vertex and eat beavers in it. "Beavermuncher-0xFF" must move without stops.

Why does the "Beavermuncher-0xFF" works like this? Because the developers have not provided place for the battery in it and eating beavers is necessary for converting their mass into pure energy.

It is guaranteed that the beavers will be shocked by what is happening, which is why they will not be able to move from a vertex of the tree to another one. As for the "Beavermuncher-0xFF", it can move along each edge in both directions while conditions described above are fulfilled.

The root of the tree is located at the vertex $ s $ . This means that the "Beavermuncher-0xFF" begins its mission at the vertex $ s $ and it must return there at the end of experiment, because no one is going to take it down from a high place.

Determine the maximum number of beavers "Beavermuncher-0xFF" can eat and return to the starting vertex.

## 样例 #1

### 输入

```
5
1 3 1 3 2
2 5
3 4
4 5
1 5
4
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3
2 1 1
3 2
1 2
3
```

### 输出

```
2
```

# 题解

## 作者：ctq1999 (赞：7)

*突然发现，通过写题解，不仅以后的言语更加专业，思路也更加清晰*

此题我觉得是一道比较裸的模板，很多题都会在此基础上变形或改变

## 题意

有一颗带权的树，初始有一个机器在根节点（一开始并不会吃），每到一个节点，就会把节点上的权值$-1$（前往的节点的权值不可为$0$），要求最终要回到根节点，求出最多可以减去多少权值

## 思路

### 概括：

统计目前节点的子节点的贡献值，更新目前节点的贡献值，同时维护每个节点剩余的权值。

贪心，在子节点的贡献值中取最大的。如果当前节点还有剩余的权值，则在当前节点和其子节点中移动（因为子节点的子节点都遍历完了，无须再往下遍历）

---

一个节点所产生的贡献与且只与它的子节点有关

假设$dfs(x)$为以$x$为根的子树所产生的贡献

那么

$$dfs(x)=\sum_{i\in son(x)}^{}dfs(i)$$

因为每次换一棵子树去遍历都要经过$x$，所以$x$的权值要$-1$。如果不够遍历所以子树，那么先吃子节点贡献大的

如下图，$2,3,4$都已经求出贡献，在求出$1$的贡献时，若$1$的权值还有剩余，并没有计算$1$到其子节点的贡献（路径为$1$）

![image.png](https://i.loli.net/2019/11/28/gnzxjVRWMwt5HPs.png)

此时注意，不需要再到子节点的子节点了，因为之前已经遍历过了，所以现在只需要在$x$和子节点来回移动，看最多可以移动多少次即可

那么此时$x$节点还剩余$k[x] - 1$的权值（因为每遍历到一个节点，都要吃掉一个）,记为$last[x]$

子节点剩余的权值和记为$sum$，$sum = \sum_{i\in son(x)}^{}last[i]$

因为每次移动到子节点后要回到其父节点，所以每次移动所产生的贡献为$2$

那么

 $$dfs(x)=\sum_{i\in son(x)}^{}dfs(i)+ 2 \times min(last[x],sum)$$
 
为什么取$min$可以自己想一下

第一个求和记得同时$last[x]--$，若$last[x]=0$时就没有权值让它遍历其他子树了，应该停止

若$x$的权值不够了就后面的$min$就为了$0$了

## 代码


```cpp
#include <bits/stdc++.h>

#define MAXN 100010
#define ll long long 
#define P pair<ll, ll>

using namespace std;

int n, root, tot;

int k[MAXN], head[MAXN];

struct edge {
	int to, next;
}e[MAXN * 2];

void add(int x, int y) {
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}//前向星存图

P dfs(int x, int fa) {
//每个dfs返回节点个贡献值和剩余权值

	vector<ll> v;//记录x的子树可以吃掉多少海狸 
	//用vectoer是因为vector是动态空间，否则用普通数组会MLE 
	ll sum = 0, have_son = 0;//有没有子节点 
	
	for (int i = head[x]; i; i = e[i].next) {
		int vertex = e[i].to;
		if (vertex == fa) continue;
		have_son = 1;
		P son = dfs(vertex, x);//遍历子节点 
		sum += son.second;//子节点剩余海狸的总和 
		v.push_back(son.first);//把每个子节点可以吃到多少海狸推到里面 
	}
	
	if (!have_son) return make_pair(0, k[x] - 1);//如果是叶节点就直接回溯
	//-1是因为它的父节点会加回来 
	
	ll eat = 0, last = k[x] - (x == root ? 0 : 1);//初始在根节点时不会吃，遍历到其他节点时会吃一个 
	sort(v.begin(), v.end());//排序 
	for (int i = v.size() - 1; i >= 0 && last; i--, last--) eat += v[i] + 2;//从大往小的加，同时x还有剩余 
	eat += 2 * min(last, sum);
	last -= min(last, sum);//还有剩余就在节点和子节点移动
	return make_pair(eat, last);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &k[i]);
	}
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		add(u, v); add(v, u);
	}
	scanf("%d", &root);
	
	cout << dfs(root, 0).first << endl;
	return 0;
} 
```

> 日拱一卒，功不唐捐


---

## 作者：endswitch (赞：3)

trick 题，贪心 + dp。

如何发现 dp 性质呢？

答案一定只会从直系儿子直接转移而来，叶子节点可以划分成一个最小的子问题，因此可以 dp。

设计状态 $dp_i$ 表示以 $i$ 为根的子树可以吃掉的海狸的最大数量，那么有：

$$
dp_x = \sum_{u \in x} dp_u
$$

但是发现一个问题，就是如果直接这么转移的话可能不满足限制并且无法很好的处理每个点剩余海狸的数量。

有什么办法可以同时记录两个信息呢，我们联想到可以把 dp 过程改成搜索的形式，在搜索中传入两个参数即可。

在回溯后，记录当前节点儿子的剩余权值的总和和每个 $dp$ 的值。

我们贪心地想，是要选儿子中 $dp$ 值大的那一些。考虑对 $dp$ 排序。

再考虑儿子剩余权值对当前 $dp$ 值的影响。假定一个点 $x$，那么你可以在 $x$ 和 $x$ 的直系儿子中反复游走，对答案的贡献为：$2 \times \min \left \{ rem, sum \right \}$，其中 $rem$ 表示 $x$ 的剩余权值，$sum$ 表示 $x$ 的直系儿子权值和。

那么状态转移方程可以大致写为：

$$
dp_x = \sum_{u \in x} dp_u + 2 \times \min \left \{ rem, sum \right \}
$$

转移处的细节较多，具体的可以看代码。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define pi pair<int, int>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;

const int N = 1e5 + 5;
int n, u, v, rt, a[N];
vector<int> g[N];

inline pi dfs(int x, int last) {
	// first 表示贡献，second 表示剩余权值 
	
	int sum = 0;
	bool flag = true;
	vector<int> v;
	
	for(auto u : g[x])
		if(u != last) {
			flag = false;
			
			pi son = dfs(u, x);
			
			sum += son.se;
			v.pb(son.fi);
		}
	
	if(flag) return mp(0ll, a[x] - 1);
	
	sort(v.begin(), v.end(), greater<int>());
	
	int res = 0, rem = a[x] - (x != rt);
	
	for(int i = 0 ; i < (int)v.size() && rem ; ++ i, -- rem)
		res += v[i] + 2;
	
	// 统计剩余权值贡献 
	
	res += (min(rem, sum) << 1);
	rem -= min(rem, sum);
	
//	cout << res << ' ' << rem << '\n';
	
	return mp(res, rem);
}

signed main() {
	ios_base :: sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr); 
	
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	for(int i = 1 ; i < n ; ++ i) {
		cin >> u >> v;
		
		g[u].pb(v), g[v].pb(u);
	}
	cin >> rt;
	
	cout << dfs(rt, -1).fi;
	
	return 0;
}

/*
3
2 1 1
3 2
1 2
3
*/
```

---

## 作者：开始新的记忆 (赞：3)

题目大意：给你一颗树，告诉你根节点和每个节点上有多少个海狸，让你从根节点出发，每次去到一个节点都会吃掉目标节点的一个海狸，如果目标节点没有海狸，则没法前往，问你最多能吃到多少个海狸。

大致思路：第一眼看到这道题，第一眼是贪心（虽然CF的标签是dp），然后就有了以下思路：对于每个点，都可以求出当这个点作根节点时它的子树的最优解是多少，然后就只要一次次往上扫，对于每个节点都扫它的子节点然后往优了取最后得到的一定是可以的。

详细过程：一个节点的eat的值就是把当前点看作起点然后往下走最多能吃到多少个海狸，不难发现，对于每个叶子节点，eat=0。一个节点的last值是当前节点已经当过起点并往下扫后还剩下多少个海狸。对于每个不是叶节点的节点我们作如下操作：

1.先遍历所有它的字节点，算出eat和last。

2.按照eat排序，从大往小取。（先取eat的证明：如果有一个s号点可以往下到x号点，那么至少能吃到x的一个和s的一个，而eat代表当x作为起点的值，eat>=0，所以在最坏情况下取eat就相当于下去上来）

3.如果这个节点还有剩余last个海狸，那么我们还要算出所有子树的last的和，为sum，那么我们就至多可以进行min(last,sum)次，得到2*min(sum,last)个海狸，然后我们再更新last，返回值即可。

```
#include<bits/stdc++.h>
using namespace std;
int n,root,val[100010];
vector <int > con[100010];

pair<long long, long long > dfs(int x,int fa)
{
    if(con[x].size()==1 && x!=root)
		return pair<long long, long long >(0,val[x]-1);
    vector <pair<long long, long long > > q;
    long long sum=0,eat=0,last=val[x];
    for(int i=0;i<con[x].size();++i)
    {
        int y=con[x][i];
        if(y==fa)
			continue;
        pair<long long, long long > tmp=dfs(y,x);
        sum+=tmp.second;
        q.push_back(tmp);
    }
    if(x!=root)
    	last--;
    sort(q.begin(),q.end());
    for(int i=q.size()-1;last>0 && i>=0;--last,--i)
		eat+=q[i].first+2;
    eat+=2*min(last,sum);
    last-=min(last,sum);
    return pair<long long, long long >(eat,last);
}

int main()
{	cin>>n;
    for(int i=1;i<=n;++i)
		cin>>val[i];
    for(int i=1,x,y;i<n;++i)
    {
        cin>>x>>y;
        con[x].push_back(y),con[y].push_back(x);
    }
    cin>>root;
    pair<long long, long long > ans=dfs(root,0);
    cout<<ans.first<<endl;
    return 0;
}
```


---

## 作者：_Wind_Leaves_ShaDow_ (赞：2)

给翻译捉个虫（也有可能是我自己没有理解）：

- 如果要前往的节点已经没有海狸了是不能选择前往的，即前往一个点的前提是这个点还有海狸剩余。

- 吃掉一个海狸 **不是** 进行移动的前提！第一次行动不需要吃海狸！

看起来就很像 dp 或者贪心，因为见过类似的题目所以往贪心方面去想。

因为出发点就是根节点，我们不考虑往父亲更新答案，认为一个点只能往子节点出发，就可以尝试把问题拆分成子问题解决。

此时分析一下我们可以发现，我们在点 $p$ 的时候，无论选择前往哪一个子节点，花费的贡献只有返回时吃的 $1$ 个海狸，而我们得到的海狸数却是不同的。花费相同而收获不同，告诉我们这题更应该偏向用贪心解决。

因为返回时一定要消耗一个海狸，所以我们更偏向往收获更大的子树吃，吃到不得不返回了再回来。于是我们把问题拆分成了更小的问题。

现在考虑对于一个子树 $p$ 如何求答案。考虑保存其每个子节点 $i$ 的答案 $e_i$，对 $e_i$ 排序，从大到小能吃多少吃多少，统计出当前子树的答案。

就完了吗？

如果有一个子树 $i$ 在吃完之后根节点还有剩余，我们仍然可以选择 $p\to i\to p$ 这样子反复横跳，分析可以发现每进行一次反复横跳收获均为 $1$，而我们在上面访问子树时得到的收获一定不低于 $1$，因此可以把这种情况放到最后讨论。

所以在传返回值的时候额外加一个此时的根节点还剩多少个海狸就可以了。

```cpp
#include <bits/stdc++.h>
#define int long long
#define Il inline
#define Rg register
#define Ri Rg int
#define pb push_back
#define vec vector
#define fi first
#define se second
#define IT ::iterator

using namespace std;
//typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
const int N=1e5,Inf=1e9,mod=1e9+7;
const db eps=1e-9,pi=acos(-1.0);

int n,a[N+5],rt;
vec<int>v[N+5],e[N+5];

Il pii dfs(int p,int fr){//当前子问题答案，根节点剩余海狸数
	if(p==rt&&!a[p])return {0,0};//不知道有没有用的特判
	int c=(p!=rt),x=0;//c 代表答案，x 代表子节点中剩余的可供反复横跳的海狸数
  //如果不是根节点那么访问时就要吃一个
	for(Ri i:v[p]){
		if(i==fr)continue;
		pii ti=dfs(i,p);
		e[p].pb(ti.fi);
		x+=ti.se;
	}
	sort(e[p].rbegin(),e[p].rend());a[p]-=(p!=rt);//如果不是根节点在访问时就消耗了一个
	for(Ri i=0;i<(int)e[p].size()&&a[p]>0;i++,a[p]--)c+=e[p][i]+1;//加上回到 p 的贡献 1
	if(a[p]>0){//处理反复横跳的贡献
		x=min(a[p],x);
		c+=(x<<1);a[p]-=x;
	}
	return {c,a[p]};
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;for(Ri i=1;i<=n;i++)cin>>a[i];
	for(Ri i=1;i<n;i++){
		int x,y;cin>>x>>y;
		v[x].pb(y);v[y].pb(x);
	}
	cin>>rt;
	cout<<dfs(rt,0).fi;
	return 0;
}
```

---

## 作者：pufanyi (赞：2)

不难发现从一个节点出发，没前往它的一棵子树，都要花费$1$的代价（废话）。

回到父亲又要花费$1$的代价。

一个显然的贪心策略就是先花费$k_{i-1}$的代价“游历”各个儿子，然后再返回父亲。

令$dp[i]$表示从$i$节点“游历”儿子后回到父亲最大所能吃掉的海狸数。但有些节点走完所有儿子后海狸数量还是大于$1$。我们记录下每个儿子返回父亲后仍留下的海狸数$kx[i]$，当父亲“游历”完所有儿子后，考虑在父亲与儿子之间往返跑，即$i\to fa[i]\to i\to \cdots$。但有些节点无法“游历”所有儿子，那么就把儿子的$dp$值从大到小排序即可。

```cpp
#include <cctype>
#include <cstdio>

namespace IO
{
    const int maxl = 23333;
    char buf[maxl], *sss = buf, *ttt = buf;

    inline char gc()
    {
        if(sss == ttt)
        {
            ttt = (sss = buf) + fread(buf, 1, maxl, stdin);
            if(sss == ttt)
                return EOF;
        }
        return *sss++;
    }

    #define dd c = gc()
    template <class T>
    inline bool read(T& x)
    {
        x = 0;
        bool f = false;
        char dd;
        for(; !isdigit(c); dd)
        {
            if(c == '-')
                f = true;
            else if(c == EOF)
                return false;
        }
        for(; isdigit(c); dd)
            x = (x << 1) + (x << 3) + (c ^ 48);
        if(f)
            x = -x;
        return true;
    }
    #undef dd
}

using IO::read;

#include <set>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef pair<LL, int> pii;

const int maxn = 100005;

int n, k[maxn], kx[maxn], rt;
LL dp[maxn];

struct Edge
{
    int to, nxt;
} e[maxn << 1];

int first[maxn];

inline void add_edge(int from, int to)
{
    static int cnt = 0;
    e[++cnt].nxt = first[from];
    first[from] = cnt;
    e[cnt].to = to;
    e[++cnt].nxt = first[to];
    first[to] = cnt;
    e[cnt].to = from;
}

inline void dfs(int now, int fa)
{
    set<pii> st;
    st.clear();
    dp[now] = (now != rt);
    k[now] -= (now != rt); // 直接把去父亲的代价减掉
    for(int i = first[now]; i; i = e[i].nxt)
    {
        int to = e[i].to;
        if(fa != to)
        {
            dfs(to, now);
            st.insert(make_pair(dp[to], to));
        }
    }
    int tmp = 0; // 儿子节点kx的sum
    int tmpk = k[now];
    set<pii>::reverse_iterator it; // 倒序遍历set
    for(it = st.rbegin(); tmpk && it != st.rend(); tmpk--, ++it)
    {
        dp[now] += it->first + 1;
        tmp += kx[it->second];
    }
    dp[now] += min(tmpk, tmp) << 1;
    kx[now] = max(tmpk - tmp, 0);
}

int main()
{
    read(n);
    for(int i = 1; i <= n; ++i)
        read(k[i]);
    for(int i = 1, f, t; i < n; ++i)
        read(f), read(t), add_edge(f, t);
    read(rt);
    dfs(rt, 0);
    printf("%lld\n", dp[rt]);
    return 0;
}
```



---

## 作者：qfpjm (赞：1)

# 题解

- 这个题看上去挺有意思，像是 `dp`，但是想想发现贪心好像也行，但有些难理解。

- 我们可以考虑每个子树的答案。维护两个数 `et` 和 `lst`，分别表示以当前节点为起点和根的子树的最优解，还有扫完子树后当前节点剩余的海狸。

- 先从叶子节点考虑，显然叶子节点的 `et` 为 $0$，`lst` 为当前叶子节点的海狸数量 $-1$。

- 对于不是叶子节点的节点，我们遍历其子节点，记录下 `et`，从大往小取，直到当前节点的 `lst` 不足了，注意不能取到 $0$，这样显然是最优的。

- 对于该节点剩余的节点 `lst`，我们可以通过和他的子树来回走消耗掉。我们记下其子节点的 `lst` 的和 `sum`，我们可以进行 $\min(lst,sum)$ 次上述的操作，这样得到的海狸数为 $2\times\min(lst, sum)$。

- 主要是注意一些小地方，没有别的难点。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, rt;
long long a[100005];
vector<int> T[500005];

pair<long long, long long> work(int u, int fa)
{
	if (T[u].size() == 1 && u != rt)
	{
		return make_pair(0, a[u] - 1);
	}
	long long sum = 0;
	vector<pair<long long, long long> > vec;
	for (int i = 0 ; i < T[u].size() ; i ++)
	{
		int v = T[u][i];
		if (v != fa)
		{
			pair<long long, long long> tmp = work(v, u);
			sum += tmp.second;
			vec.push_back(tmp);
		}
	}
	long long lst = a[u];
	if (u != rt)
	{
		lst --;
	}
	sort(vec.begin(), vec.end());
	long long et = 0;
	for (int i = vec.size() - 1 ; i >= 0 && lst > 0 ; i --, lst --)
	{
		et += vec[i].first + 2;
	}
	et += 2 * min(lst, sum);
	lst -= min(lst, sum);
	return make_pair(et, lst);
}

int main()
{
	cin >> n;
	for (int i = 1 ; i <= n ; i ++)
	{
		cin >> a[i];
	}
	for (int i = 1 ; i < n ; i ++)
	{
		int u, v;
		cin >> u >> v;
		T[u].push_back(v);
		T[v].push_back(u);
	}
	cin >> rt;
	cout << work(rt, 0).first;
}
```


---

## 作者：thostever (赞：1)

我们令 $dp_i$ 表示从节点 $i$ 出发（出发时要吃掉 $i$ 上的一个），最终回到 $i$ ，最多能吃几个。

答案即为 $dp_s-1$ 。

令 $a_i$ 表示在 $dp$ 值取最优的情况下节点 $i$ 剩下多少海狸。初始值便是输入的值。

对于每个节点 $u$ 和它的一个儿子 $v$，可以从 $u$ 走到 $v$ 再回来，则有转移：$dp_u\gets dp_u+dp_v+1$ （+1是因为回到 $u$ 的时候会增加一次贡献）

转移时需要保证 $a_u$ 不为 $0$ ，转移后 $a_i$ 自减。

很显然，我们要优先挑选 $dp$ 值大的儿子选，用优先队列维护每个节点所有儿子的 $dp$ 值即可。

然后我们发现若转移后若 $a_u$ 还有剩余，则可以与每个儿子所剩余的值（即 $a_v$）进行来回的折返。由于这样操作对于所有儿子而言是等价的，我们便可以把所有儿子的 $a$ 值合在一起。

令 $sum_i$ 表示节点 $i$ 所有儿子的 $a$ 值的和。再计算儿子时转移即可。

若 $a_u\geq sum_u$，那么最多贡献 $sum\times 2$，$a_u$ 减去 $sum_u$。

若 $a_u<sum_u$，那么最多贡献 $a_u\times 2$，$a_u=0$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[100010];
int head[100010],to[200010],nxt[200010],tot=0;
void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
int f[100010];
void dfs(int u,int fa)
{
	f[u]=fa;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==fa) continue;
		dfs(v,u);
	}
	return;
}
int p[100010];
int dp[100010];
int sum[100010];
queue<int> q;
priority_queue<int,vector<int>,less<int> > que[100010];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i=2;i<=n;i++)
	{
		int x,y;
		scanf("%lld%lld",&x,&y);
		add(x,y);
		add(y,x);
	}
	int S;
	scanf("%lld",&S);
	dfs(S,0);//求父亲 
	a[S]++;//由于根节点一开始不会被吃掉，所以要+1 
	for(int i=1;i<=n;i++)
	{
		p[f[i]]++;//每个点的儿子数量 
	}
	for(int i=1;i<=n;i++) if(p[i]==0) q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		if(a[u]==0)
		{
			dp[u]=0;
			continue;
		}
		a[u]--;//从父亲到达u的时候会吃掉一个 
		dp[u]++;
		while(a[u] && !que[u].empty())
		{
			int t=que[u].top();
			que[u].pop();
			a[u]--;
			dp[u]+=t+1;
		}
		if(a[u]!=0)
		{
			if(a[u]>=sum[u])
			{
				dp[u]+=sum[u]*2;
				a[u]-=sum[u];
			}
			else
			{
				dp[u]+=a[u]*2;
				a[u]=0;
			}
		}
		if(f[u]==0) continue;//若是根节点，则不转移 
		p[f[u]]--;
		que[f[u]].push(dp[u]);
		sum[f[u]]+=a[u];
		if(p[f[u]]==0) q.push(f[u]); 
	}
	printf("%lld",dp[S]-1ll);
	return 0;
}
```


---

## 作者：_ZHONGZIJIE0608_ (赞：0)

『那一天，海狸们想起了……』

好吧，其实啥也没想到。这题思路还挺巧妙的。

首先，一开始在根节点上是不会吃海狸的。所以在统计完答案之后要把答案减掉 $1$。

设 $dp_i$ 表示以点 $i$ 为子树最多能吃到的海狸的数量。后文会把那一只预留的海狸成为“不可食用海狸”。

对 $k_i$ 进行预先修改，使得 $k_i$ 变成以 $i$ 为子树可以往下走的路线数量（其实就是把除了根以外的点的 $k_i$ 减去 $1$ 来预留一只海狸用于回到父亲）。

考虑如何转移。对于一个点 $u$，先把其儿子的 $dp$ 值存下来，并记录吃完后儿子们剩下的可食用海狸数量和 $sm$。

先别急着加。吃海狸机的『能力』是有限的。由于可能无法吃完所有的子树里的海狸，让我们对儿子们的 $dp$ 值从大到小排序。

考虑到你把儿子的子树里的海狸全吃了都只会让 $k_u$ 减少 $1$，你子树里能吃的海狸当然越多越好。

遍历每个值 $val$，如果 $u$ 上的海狸还没吃完，就把 $dp_u$ 加上 $val+1$，然后花费一只海狸。那个增加的 $1$ 就是你吃掉的节点 $u$ 上的海狸。直到儿子遍历完或者 $u$ 上能吃的海狸都吃光了为止。

如果海狸很充足，在跑完子树后海狸还没有吃完，我们可不能『浪费』掉这些海狸。还记得之前存活的海狸吗？如果儿子上面还有海狸剩，我们就可以按照 $u \rarr son_1 \rarr u \rarr son_2 \rarr \cdots$ 的方式在自己和儿子之间『反复横跳』来吃掉这些海狸。如果 $k_u \ge sm$，就可以把这些海狸全吃了（由于 $u$ 上也会吃掉海狸，$dp_u$ 增加 $sm \times 2$），然后 $k_u \gets k_u - sm$。否则就只能吃掉儿子里的 $k_u$ 个（就是吃掉 $2 \times k_u$ 个）然后把 $k_u$ 清零。

真是一道 DP 和贪心结合的好题。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,rt,dp[N],k[N];
vector<int>e[N];
void dfs(int u,int ls){
	dp[u]=1;int sm=0;vector<int>V;
	for(auto v:e[u])if(v!=ls)dfs(v,u),sm+=k[v],V.push_back(dp[v]);
	sort(V.begin(),V.end(),greater<int>());
	for(auto val:V){
		if(k[u]>0){
			dp[u]+=val+1;
			--k[u];
		}
		else break;
	}
	if(k[u]>=sm)dp[u]+=2*sm,k[u]-=sm;
	else dp[u]+=2*k[u],k[u]=0;
} 
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>k[i],--k[i];//留一条边回父亲 
	for(int i=1;i<n;++i){
		int u,v;cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	cin>>rt;++k[rt];//根节点不用回父亲 
	dfs(rt,0);
	cout<<dp[rt]-1;//第一次走不会在根节点上吃 
	return 0;
}
/*
所以海狸能吃吗？怎么吃？好吃吗？
*/
```

---

## 作者：lfxxx (赞：0)

注意到从一个子树离开后实际上只会再次经过这个子树的根。

因为如果还可以经过根再深入子树并返回，那为什么不再离开这棵子树前就这么干呢？

所以设计状态 $dp_u$ 表示抵达 $u$ 走 $u$ 的子树再回到 $u$ 所能吃掉的海狸数，并用 $a_u$ 表示 $dp_u$ 取最优的策略下点 $u$ 剩余的海狸数，因为留在点 $u$ 的海狸肯定是拿去扩展其子树内路径更优，所以只用考虑 $dp_u$ 最优时的情况即可，然后转移就贪心的选取前若干大。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e5+114;
int a[maxn],n,s;
vector<int> E[maxn];
int dp[maxn];
bool cmp(int x,int y){
	return x>y;
}
void dfs(int u,int fa){
	dp[u]=1;
	int cnt=0;
	vector<int> vec;
	for(int v:E[u]){
		if(v==fa) continue;
		dfs(v,u);
		vec.push_back(dp[v]);
		cnt+=a[v];
	}
	sort(vec.begin(),vec.end(),cmp);
	for(int x:vec){
		if(a[u]>0){
			dp[u]+=(x+1);
			a[u]--;
		}else{
			break;
		}
	}
	dp[u]+=min(cnt,a[u])*2;
	a[u]-=min(cnt,a[u]);
	//cout<<u<<' '<<dp[u]<<'\n';
	return ;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=n;i++){
		int u,v;
		cin>>u>>v;
		E[u].push_back(v);
		E[v].push_back(u);
	} 
	cin>>s;
	for(int i=1;i<=n;i++)
		if(i!=s) a[i]--;
	dfs(s,0);
	cout<<dp[s]-1<<'\n';
	return 0;
}
```

---

## 作者：Jerrywang09 (赞：0)

很不套路的题目，贪心与动态规划的结合。

题目描述有点乱，简练一点，从根开始搜索给定的树，除了根结点，每个点最多访问 $k_i$ 次。问最多可以经过多少条边。

先考虑 DP。定义状态 $f(u)$ 表示 $u$ 子树内的答案，$g(u)$ 表示子树根结点 $u$ 剩余的访问次数。

暂时不考虑根结点。对于结点 $u$，一定要从父亲过来，因此最多访问 $k_i-1$ 个子树。不妨对 $f(v)|v\in son_u$ 排序，选择最大的 $k_i-1$ 个转移。

做完了吗？还没利用 $g(v)$ 呢。如果点 $u$ 剩余的访问次数还很多，就可以与还可以继续访问的子节点反复横跳，比如 $u\rightarrow v_1\rightarrow u\rightarrow v_2\rightarrow u\rightarrow v_2\rightarrow u\rightarrow v_3$。因此，用 $sum$ 累计所有 $g(v)$，记 $rest$ 为结点 $u$ 剩余的访问次数，还可以横跳 $2\times \min(sum, rest)$ 条边。如果跳完所有子结点还有剩余次数，则存作 $g(u)$。

另外，根结点可以多经过一次。本题的思路确实蛮复杂的。

```cpp
#include <bits/stdc++.h>
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=100010;
using namespace std;

int n, k[N], root; ll f[N], g[N]; vector<int> G[N];

void dfs(int u, int fa)
{
    vector<ll> a; ll sum=0;
    for(int v:G[u]) if(v!=fa)
    {
        dfs(v, u);
        a.push_back(f[v]); sum+=g[v];
    }
    sort(a.begin(), a.end(), greater<ll>());
    ll rest=k[u]-1; f[u]=0;
    for(ll x:a)
    {
        if(!rest) break;
        f[u]+=x+2; rest--;
    }
    f[u]+=min(rest, sum)*2;
    g[u]=rest-min(rest, sum);
}

int main()
{
    #ifdef Jerrywang
    freopen("in.txt", "r", stdin);
    #endif
    scanf("%d", &n);
    rep(i, 1, n) scanf("%d", k+i);
    rep(i, 2, n)
    {
        int u, v; scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    scanf("%d", &root); k[root]++;
    dfs(root, 0);
    printf("%lld", f[root]);

    return 0;
}
```

---

