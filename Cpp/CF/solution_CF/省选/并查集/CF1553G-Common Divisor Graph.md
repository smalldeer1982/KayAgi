# Common Divisor Graph

## 题目描述

Consider a sequence of distinct integers $ a_1, \ldots, a_n $ , each representing one node of a graph. There is an edge between two nodes if the two values are not coprime, i. e. they have a common divisor greater than $ 1 $ .

There are $ q $ queries, in each query, you want to get from one given node $ a_s $ to another $ a_t $ . In order to achieve that, you can choose an existing value $ a_i $ and create new value $ a_{n+1} = a_i \cdot (1 + a_i) $ , with edges to all values that are not coprime with $ a_{n+1} $ . Also, $ n $ gets increased by $ 1 $ . You can repeat that operation multiple times, possibly making the sequence much longer and getting huge or repeated values. What's the minimum possible number of newly created nodes so that $ a_t $ is reachable from $ a_s $ ?

Queries are independent. In each query, you start with the initial sequence $ a $ given in the input.

## 说明/提示

In the first example, you can first create new value $ 2 \cdot 3 = 6 $ or $ 10 \cdot 11 = 110 $ or $ 3 \cdot 4 = 12 $ . None of that is needed in the first query because you can already get from $ a_1 = 2 $ to $ a_2 = 10 $ .

In the second query, it's optimal to first create $ 6 $ or $ 12 $ . For example, creating $ 6 $ makes it possible to get from $ a_1 = 2 $ to $ a_3 = 3 $ with a path $ (2, 6, 3) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1553G/bde4f00f87166b14452d3f5ad3d0af82a1d4f8e5.png)In the last query of the second example, we want to get from $ a_3 = 7 $ to $ a_5 = 25 $ . One way to achieve that is to first create $ 6 \cdot 7 = 42 $ and then create $ 25 \cdot 26 = 650 $ . The final graph has seven nodes and it contains a path from $ a_3 = 7 $ to $ a_5 = 25 $ .

## 样例 #1

### 输入

```
3 3
2 10 3
1 2
1 3
2 3```

### 输出

```
0
1
1```

## 样例 #2

### 输入

```
5 12
3 8 7 6 25
1 2
1 3
1 4
1 5
2 1
2 3
2 4
2 5
3 1
3 2
3 4
3 5```

### 输出

```
0
1
0
1
0
1
0
1
1
1
1
2```

# 题解

## 作者：Alex_Wei (赞：10)

> [题目传送门](https://www.luogu.com.cn/problem/CF1553G)。
>
> 题意简述：给出长度为 $n$ 的序列 $a_i$，两个点 $i,j$ 之间有边当且仅当 $(a_i,a_j)>1$。$q$ 次询问给定 $s,t$，你可以选择一个点 $i$ 并新建节点 $a_i\times (a_i+1)$，求至少要多少次操作才能使 $s,t$ 联通。

不算难的一道题，但是赛时没写出来，与 2500+ 失之交臂/流泪。

首先，一个关键的性质是**答案不超过 $2$**。这很显然，因为 $a_i(a_i+1)$ 一定能被 $2$ 整除。所以 $(a_s(a_s+1),a_t(a_t+1))>1$。

于是可以对三种情况分别讨论：

- 答案为 $0$：此时 $s,t$ 在同一个连通块。连通块的预处理很容易：记 $buc_{a_i}=i$，枚举每个质数 $p$ 及其倍数 $cp$，将所有 $buc_{cp}$ 有值的全部连通即可，可以用并查集实现。
- 答案为 $1$：注意到 **$a_i+1$ 所含有的不同质因子是很少的**，最多只有 $7$，并且**含有相同质因子的数一定在同一个连通块**，这启发我们枚举每个 $a_i$，求出 “$a_i$ 所在的连通块” 与 “$a_i+1$ 所含有的质因子所表示的所有连通块”，并将得到的所有连通块两两标记一下。那么若 $s,t$ 所处的连通块之间有标记，则答案为 $1$。这个可以记录所有标记的连通块对（最多 $21n$ 个），排序一边后每次询问使用 `lower_bound` 查找。
- 否则答案为 $2$。

时间复杂度不太会分析，大概是 $\mathcal{O}(m\log m+d^2n+q\log(d^2n))$，其中 $m$ 为值域，$d$ 为不超过值域的数所含有的最多质因子个数，本题中为 $7$。实际常数会很小，因为首先有一个 $\dfrac{1}{2}$ 的常数，同时显然卡不满。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define pii pair <int,int>

const int N=1e6+5;

int n,q,a[N],buc[N],pr[N];
int f[N],col[N],d[N],c;
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
vector <pii> res;

int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i],f[i]=i,buc[a[i]]=i;
	for(int i=2;i<N;i++){
		if(pr[i])continue;
		for(int j=i,pre=-1;j<N;j+=i){
			if(buc[j]){
				if(pre==-1)col[i]=find(buc[j]);
				else f[find(pre)]=find(buc[j]);
				pre=buc[j];
			} pr[j]=i;
		}
	}
	for(int i=2;i<N;i++)if(pr[i]==i)col[i]=find(col[i]);
	for(int i=1,p=a[1]+1;i<=n;p=a[++i]+1,c=0){
		d[++c]=find(i);
		while(p>1)d[++c]=col[pr[p]],p/=pr[p];
		sort(d+1,d+c+1),c=unique(d+1,d+c+1)-d-1;
		for(int i=1;i<c;i++)
			for(int j=i+1;j<=c;j++)
				res.push_back({d[i],d[j]});
	} sort(res.begin(),res.end());
	for(int i=1;i<=q;i++){
		int x,y; cin>>x>>y,x=find(x),y=find(y);
		if(x==y)puts("0");
		else{
			pii cur={min(x,y),max(x,y)};
			auto it=lower_bound(res.begin(),res.end(),cur);
			puts(it!=res.end()&&*it==cur?"1":"2");
		} 
	}
	return 0;
}
```



---

## 作者：MatrixCascade (赞：8)

当时场上水平特别差，只 pp 了 5 个题还 fst 了两题，现在随到这个题发现非常简单。。

首先可以在一分钟内看出答案必定 $\le2$，你考虑奇偶性，如果两个偶数答案就是 $0$，一奇一偶答案至多是 $1$，两个奇数答案至多是 $2$（一次操作可以把一个奇数变成一个偶数，两个偶数的 $\gcd\ge2$）。

然后考虑怎么判断答案，显然是先判断答案是不是 $0$，再判断 $1$ ，如果都不行的话就是 $2$。

先考虑 $0$ 的情况，根据套路，图上判联通距离之类的先去想想能不能生成树/并查集去搞，发现后者是可行的。由于 $10^6$ 之内的数的质因子个数最多为 $7$ 个（$2\times 3\times5\times7\times11\times13\times17=510510$），于是你可以把每个数的质因子预处理出来，然后对于每个质因子开一个集合，把有这个质因子的数放进去，最后再用并查集把**每个**集合里面的数都合并起来。判断的时候如果两个数在这个图内联通（有同一个祖先）那就是可行的，答案就是 $0$。  
然后考虑 $1$ 的情况。有三种可行的方法：  
1.  对 s 进行操作
2.  对 t 进行操作
3. 对一个别的数进行操作

前两种情况直接判掉，不多赘述。对于第三种情况，同样我们可以把  $a_i\times (a_i+1)$  质因子搞出来（只需要把预处理出的 $a_i$ 和 $a_i+1$ 合并起来就行） 然后考虑如果对他进行操作的话，可以使得 $a_i\times (a_i+1)$ 所含的**任意两个质因子所在的集合的祖先**联通，暴力二重循环，把它们塞进一个哈希表（或者 map）就可以了，查询的时候就看 $(find(s),find(t))$ 是否出现过即可。  
否则答案就是 $2$。

时间复杂度 $O(nx^2\log n)$，x 为质因子个数。

[代码](https://codeforces.com/contest/1553/submission/155021476)

---

## 作者：shenxinge (赞：3)

题目链接：[CF1553G Common Divisor Graph](https://www.luogu.com.cn/problem/CF1553G)

这题目比 $F$ 题好做，也比 $F$ 题好想。。。

首先我们可以观察： **可以发现答案一定不大于2**。

因为对于一个偶数来说，它必有边连向另外一个偶数，所以最坏情况就是两个奇数节点全都靠生成生成出两个偶数节点，这两个偶数节点相互连接使得这两个奇数节点联通。

接下来就是如何判断0和1的问题。

对于如何判断0， **我们只需要判断这两个节点是否在原图中联通即可** 。也就是让我们找出初始图的联通分量。

我们可以为每一个素数 $prime(2 \le prime \le Max+1)$ 建立一个节点，我们用$P$来维护这个数的所有质因数，然后将 $prime$ 与 $P(a[i])$ 的所有元素之间相互连接起来，**这个过程可以使用并查集来实现**。

然后我们判断时只要判断输入的两个值的 $a[s],a[t]$ 是否在同一个联通分量即可。

对于如何判断1，我们假设 $a[s]$ 和 $a[t]$ 处于两个不同的联通分量中，能判断一步能走到的只有三种情况：

1.对于 $a[s]$ 节点进行操作。

2.对于 $a[t]$ 节点进行操作。

3.对于另一个毫不相干的节点进行操作。

~~（这不是显而易见的事情吗）~~


显然对于这些情况，我们把 $a[i]$ 加入到 $P(a[i+1])$ 使得他们能够互相找到，然后暴力枚举 $P(a[i+1])$ 的每个节点，如果能够联通的话就放进一个边集里面（边集用 $set$ 维护）,最后只需要查找边 $a[s]->a[t]$ 是否存在就可以了。

这样的话代码也呼之欲出了。时间复杂度~~大概~~是 $O((n+q)\times\log_2^2(n))$

```cpp
#include<bits/stdc++.h>
#define Debug if(false)
#define rnt register int
using namespace std;
const int maxn=2000010;
inline int read()
{
	int x=0,f=1;char c;
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-f;
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	return x*f;
}
int n,q,Max;
int a[maxn];
struct Unionset
{
	int f[maxn];
	inline void init()
		{for(rnt i=1;i<=Max+1;i++) f[i]=i;}
	inline int Find(int x)
	{
		if(f[x]==x) return x;
		else return f[x]=Find(f[x]);
	}
	inline void Union(int x,int y)
		{f[Find(x)]=Find(y);}
}uni;
vector<int> P[maxn]; //因为我不会估，所以用的vector 
set<pair<int,int> > edgeset;
signed main()
{
	n=read(),q=read();
	for(rnt i=1;i<=n;i++)
		a[i]=read(),Max=max(Max,a[i]);
	//初始化P数组
	uni.init();
	for(rnt prime=2;prime<=Max+1;prime++)	
		if(P[prime].empty())
			for(rnt x=prime;x<=Max+1;x+=prime)
				P[x].push_back(prime);
	//把所有的a[i]与他的质因数压进一个集合里 
	for(rnt i=1;i<=n;i++)
		for(auto prime:P[a[i]])
			uni.Union(a[i],prime);
	for(rnt i=1;i<=n;i++)
	{
		vector<int> nodeset=P[a[i]+1];
		nodeset.push_back(a[i]); //把a[i]压进a[i]+1的集合里面 
		for(rnt i=0;i<nodeset.size();i++)
			for(rnt j=i+1;j<nodeset.size();j++)
			{
				int node1=nodeset[i],node2=nodeset[j];
				node1=uni.Find(node1),node2=uni.Find(node2);
				if(node1!=node2)
				{
					Debug printf("node1: %d node2: %d\n",node1,node2);
					if(node1>node2) swap(node1,node2);
					edgeset.insert({node1,node2}); //连上一条边 
				}
			}
	}
	while(q--)
	{
		int s=read(),t=read();
		s=uni.Find(a[s]),t=uni.Find(a[t]);
		if(s>t) swap(s,t);
		if(s==t) puts("0"); //如果处于一个联通分量就直接输出0 
		else if(edgeset.count({s,t})) puts("1"); //如果能够通过一条边就跳到就输出0 
		else puts("2"); //其余的话就转成偶数，输出2 
	}
	return 0;
}
```


就结束了。。。。。

---

## 作者：Leasier (赞：2)

前置芝士：[最大公约数（gcd）](https://oi-wiki.org/math/number-theory/gcd/)、[线性筛](https://oi-wiki.org/math/number-theory/sieve/#_7)、[并查集](https://oi-wiki.org/ds/dsu/)

通过观察样例，可以猜想：答案为 $[0, 2]$ 内的一个数。证明将会在后面给出。

首先，题目中叙述的连边方式等效于将 $i$ 的联通块与任意包含 $a_i$ 的每个质因数的联通块合并。

于是我们通过线性筛预处理出每个数的最小质因数、通过最小质因数分解质因数并合并即可。

查询时，如果 $s, t$ 已在一个集合里，答案为 $0$；如果 $a_s + 1$ 的质因数所在的集合与 $t$ 所在的集合有相同或 $a_t + 1$ 的质因数所在的集合与 $s$ 所在的集合有相同，答案为 $1$；否则，答案为 $2$。

证明：此时可以新建两个节点，权值为 $a_s(a_s + 1)$ 和 $a_t(a_t + 1)$，此时它们一定有一个 $\gcd$ 为 $2$。

预处理 $a_i + 1$ 的质因数所在的集合即可。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

const int N = 1e6 + 7, M = 1.5e5 + 7;
int prime[N], lpf[N], root[M], a[M], ref[N];
bool p[N], vis[N];
map<int, bool> mp[M];
vector<int> v;

inline void init(int n){
	int cnt = 0;
	p[0] = p[1] = true;
	lpf[1] = 0;
	for (register int i = 2; i < N; i++){
		if (!p[i]){
			prime[++cnt] = i;
			lpf[i] = i;
		}
		for (register int j = 1; j <= cnt && i * prime[j] < N; j++){
			int t = i * prime[j];
			p[t] = true;
			lpf[t] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
	for (register int i = 1; i <= n; i++){
		root[i] = i;
	}
}

int get_root(int x){
	if (root[x] == x) return x;
	return root[x] = get_root(root[x]);
}

inline void merge(int x, int y){
	int x_root = get_root(x), y_root = get_root(y);
	if (x_root != y_root) root[x_root] = y_root;
}

int main(){
	int n, q, ni;
	cin >> n >> q;
	ni = n + 1;
	init(ni);
	for (register int i = 1; i <= n; i++){
		cin >> a[i];
		for (register int j = a[i]; j > 1; ){
			int t = lpf[j];
			if (!vis[t]){
				vis[t] = true;
				ref[t] = i;
			} else {
				merge(i, ref[t]);
			}
			while (j % t == 0){
				j /= t;
			}
		}
	}
	for (register int i = 1; i <= n; i++){
		int size, size_d;
		v.clear();
		v.push_back(get_root(i));
		for (register int j = a[i] + 1; j > 1; ){
			int t = lpf[j];
			if (!vis[t]){
				vis[t] = true;
				ref[t] = ni;
			}
			v.push_back(get_root(ref[t]));
			while (j % t == 0){
				j /= t;
			}
		}
		sort(v.begin(), v.end());
		size = unique(v.begin(), v.end()) - v.begin();
		size_d = size - 1;
		for (register int j = 0; j < size_d; j++){
			for (register int k = j + 1; k < size; k++){
				mp[v[j]][v[k]] = mp[v[k]][v[j]] = true;
			}
		}
	}
	for (register int i = 1; i <= q; i++){
		int s, t;
		cin >> s >> t;
		s = get_root(s);
		t = get_root(t);
		if (s == t){
			cout << 0 << endl;
		} else if (mp[s].count(t) || mp[t].count(s)){
			cout << 1 << endl;
		} else {
			cout << 2 << endl;
		}
	}
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

答案上界显然是 $2$，你可以通过操作 $s$ 和 $t$ 使得它们联通（都有公因子 $2$）。因此我们只需要判断是否为 $0$ 和 $1$。

判断 $0$：原图中是否有 $s$ 和 $t$ 联通？这是非常经典的优化建图：对每个质数 $p$ 建立虚拟点。如果 $p \mid a_s$，则 $u_p$ 和 $s$ 之间连边，使用并查集维护。

判断 $1$：能否增加一个点使 $s$ 和 $t$ 联通？

考虑新加一个点，本质能将 $O(w(V))$ 个联通块合并，其中 $w(V)$ 是 $V$ 的质因数个数。那么暴力维护所有可能的联通块对即可。

> 注意，合并的联通块不是 $a_i$ 和 $a_i+1$ 的质因子之间，而是 $a_i$ 和 $a_i+1$ 的所有质因子之间。因为可能原序列中没有 $a_i+1$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10;
int n,q,tot,a[MAXN],id[MAXN],fa[MAXN],flg[MAXN];
vector<int> pr,frac[MAXN];
map<pair<int,int>,int> mp;
void init(int mx) {
    ffor(i,2,mx) {
        if(!flg[i]) pr.push_back(i);
        for(auto v:pr) {
            if(i*v>mx) break ;
            flg[i*v]=1;
            if(i%v==0) break ;
        }
    }
    for(auto v:pr) ffor(i,1,mx/v) frac[i*v].push_back(v);
    return ;
}
int find(int k) {return (fa[k]==k)?k:(fa[k]=find(fa[k]));}
int main() {
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>n>>q,tot=n,init(1000001);
    ffor(i,1,n) cin>>a[i];
    ffor(i,1,n) for(auto v:frac[a[i]]) if(!id[v]) id[v]=++tot;
    ffor(i,1,tot) fa[i]=i;
    ffor(i,1,n) for(auto v:frac[a[i]]) fa[find(i)]=find(id[v]);
    ffor(i,1,n) {
        for(auto v1:frac[a[i]]) for(auto v2:frac[a[i]+1]) if(id[v1]&&id[v2]) {
            if(find(id[v1])!=find(id[v2])) mp[{find(id[v1]),find(id[v2])}]=mp[{find(id[v2]),find(id[v1])}]=1;
        }
        for(auto v1:frac[a[i]+1]) for(auto v2:frac[a[i]+1]) if(id[v1]&&id[v2]) {
            if(find(id[v1])!=find(id[v2])) mp[{find(id[v1]),find(id[v2])}]=mp[{find(id[v2]),find(id[v1])}]=1;
        }
    }
    ffor(i,1,q) {
        int s,t;
        cin>>s>>t;
        if(find(s)==find(t)) cout<<0<<'\n';
        else if(mp.count({find(s),find(t)})) cout<<1<<'\n';
        else cout<<2<<'\n';
    }
    return 0;
}
```

---

## 作者：liaoz123 (赞：0)

连开四道 2700 只会这一道，太失败了。

很显然的观察是 $ans\le 2$。你显然可以给 $s,t$ 各操作一次，那么此时会有 $s-s(s+1)-t(t+1)-t$ 的路径，因为中间两个数存在 $2$ 的公因子。

那么我们的任务就是判断在什么时候 $ans=1,0$。想象我们在路径上走的过程，我们持有一个质因子 $x$，那么我们可以在所有包含质因子 $x$ 的数中随意游走（我们只要考虑质因子就可以了）。那么如果一个数同时存在两个质因子 $x,y$，这就相当于在这里，我们可以将持有的质因子由 $x$ 转变为 $y$，并在之后可以在所有包含质因子 $y$ 的数中随意游走。把包含某个质因子的所有数看作一个连通块，那么同时存在两个质因子 $x,y$ 等价于把 $x$ 的连通块和 $y$ 的连通块合并。可以使用并查集维护。

对于一个询问 $s,t$，我们分解质因子，并将两边的质因子两两检查是否属于同一个集合即可判定是否有 $ans=0$。如果 $ans=1$，则说明我们操作了某个数 $x$，并新增了 $x(x+1)$，这可能使得一些连通块合并。那么我们只要类似地分解 $x(x+1)$,那么他的所有质因子两两都可以通过一次操作合并到一个连通块中，这个可以预处理解决。询问的时候和判断 $ans=0$ 类似。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;
int n,q,p[N],cnt,w[N],a[N],fa[N];
bool vis[N];map<int,int> m[N];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void pre(){
	fa[1]=1;
	for(int i=2;i<N;i++){
		if(!vis[i])p[++cnt]=i,w[i]=i;
		fa[i]=i;
		for(int j=1;j<=cnt&&p[j]*i<N;j++){
			vis[p[j]*i]=true;
			w[i*p[j]]=p[j];
			if(i%p[j]==0)break;
		} 
	}
}
void fac(vector<int> &q,int x){
	while(x!=1){
		int p=w[x];
		q.push_back(p);
		while(x%p==0)x/=p;
	}
}
int main(){
	scanf("%d%d",&n,&q);pre();
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		vector<int> p,q;
		fac(q,a[i]);
		for(int x:q)
		for(int y:q)
		fa[find(x)]=find(y);
	}
	for(int i=1;i<=n;i++){
		vector<int> q,p;
		fac(q,a[i]+1);
		fac(p,a[i]);
		for(int x:q)
		for(int y:q)
		m[find(x)][find(y)]=m[find(y)][find(x)]=true;
		for(int x:p)
		for(int y:q)
		m[find(x)][find(y)]=m[find(y)][find(x)]=true;
	}
	while(q--){
		int x,y;
		scanf("%d%d",&x,&y);
		x=a[x],y=a[y];
		vector<int> p,q;
		fac(p,x);fac(q,y);
		int ff=0;
		for(int u:p)
		for(int v:q)
		if(find(u)==find(v)){
			ff=1;
			break;
		}
		if(ff){puts("0");continue;}
		for(int u:p)
		for(int v:q)
		if(m[find(u)][find(v)]){
			ff=1;
			break;
		}
		if(ff){puts("1");continue;}
		puts("2");
	}
	return 0;
}
```

---

## 作者：bryce (赞：0)

## [Common Divisor Graph](https://www.luogu.com.cn/problem/CF1553G)
### 思路
集中注意力发现，最多创造两个新的节点就能使 $s$ 到 $t$，因为 $a_s(a_s + 1)$ 和 $a_t(a_t + 1)$ 都为偶数。

当答案为 $0$ 时，对每个点求其质因数，并查集维护连通块，如果 $s$ 和 $t$ 在同一个连通块内答案就为 $0$。
当答案为 $1$ 时，即不在同一个连通块，对于每一个点求 $a_i + 1$ 的质因数，将 $a_i$ 所在的连通块的代表点与 $a_i + 1$ 的每一个质因数所在的连通块用邻接矩阵连一条边，表示能够到达，再将 $a_i + 1$ 的每一个质因数所在的连通块之间两两连边，表示这些连通块能够通过 $a_i + 1$ 这个点互相到达，判断 $s$ 和 $t$ 所在的连通块有否连边。

当答案为 $2$ 时，即为无连边的情况。
### 代码
```cpp
#include<iostream>
#include<vector>
#include<map>

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}
inline void write(int x){if (x < 0) putchar('-'), x = -x;if (x > 9) write(x / 10);putchar(x % 10 + '0');}

const int N = 1.5e5 + 10, M = 1e6 + 10;
int n, m, maxn;
int a[N], prime[M], cnt, fa[M];
bool p[M];
vector<int> v[M];
void init(){
    for (int i = 2; i <= maxn; i++){
        if (!p[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= maxn; j++){
            p[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    for (int i = 1; i <= maxn; i++) fa[i] = i;
}
int find(int x){
    return (x == fa[x] ? fa[x] : fa[x] = find(fa[x]));
}
void merge(int x, int y){
    int fx = find(x), fy = find(y);
    fa[fx] = fy;
}
map<int, map<int, bool> > vis;

int main(){
    n = read(), m = read();
    for (int i = 1; i <= n; i++) a[i] = read(), maxn = max(maxn, a[i] + 1);
    init();
    for (int i = 1; i <= cnt; i++)
        for (int j = prime[i]; j <= maxn; j += prime[i]) v[j].emplace_back(prime[i]);
    for (int i = 1; i <= n; i++)
        for (auto j : v[a[i]]) merge(a[i], j);
    for (int i = 1; i <= n; i++){
        for (int j = 0; j < v[a[i]].size(); j++)
            for (int k = j; k < v[a[i] + 1].size(); k++){
                int fx = find(v[a[i]][j]), fy = find(v[a[i] + 1][k]);
                if (fx == fy) continue;
                vis[fx][fy] = 1;
            }
        for (int j = 0; j < v[a[i] + 1].size(); j++){
            for (int k = j; k < v[a[i] + 1].size(); k++){
                int fx = find(v[a[i] + 1][j]), fy = find(v[a[i] + 1][k]);
                if (fx == fy) continue;
                vis[fx][fy] = 1;
            }
        }
    }
    for (int i = 1; i <= m; i++){
        int s = find(a[read()]), t = find(a[read()]);
        if (s == t) cout << 0 << '\n';
        else if (vis[s][t] || vis[t][s]) cout << 1 << '\n';
        else cout << 2 << '\n';
    }
    return 0;
}
```

---

## 作者：FjswYuzu (赞：0)

显然答案上界为 $2$。确定答案上界在各种地方都有用到。

至于证明，因为对于正整数 $x$，$2 \mid \gcd(x,x+1)$。最坏情况下，我们只需要拓展 $s,t$ 就行了。

如果不拓展或者拓展一次都不行，答案为 $2$。那么如何判断不拓展或拓展一次是否可行？

首先是不拓展：对于每一个 $a_i$ 将其所有质因子全部处理出来。将这个质因子上一次出现的位置与当前位置合并成一个连通块。可以用并查集实现。

拓展一次的话，还是枚举 $a_i+1$。考虑加入 $a_i+1$ 的贡献，我们会连接所有 $a_i+1$ 的质因子代表的连通块以及 $a_i$ 所在连通块。注意到 $\omega(10^6+1)$ 为 $7$，我们将只拓展一次可以连接的每对连通块存下来，如果只需要拓展一次，那么 $s,t$ 所在连通块必然出现在其中。

否则，答案为 $2$。令值域为 $a$，时间复杂度写法比较复杂，能过就对了。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct unionFindSet{
	int fa[150005];
	void makeSet(int up){for(int i=0;i<=up;++i)	fa[i]=i;}
	int findSet(int x)
	{
		if(x==fa[x])	return x;
		return fa[x]=findSet(fa[x]);
	}
	void unionSet(int x,int y)
	{
		int xx=findSet(x),yy=findSet(y);
		if(xx==yy)	return ;
		fa[xx]=yy;
	}
}ufs;
int n,q,a[150005],lst[1000005],pb[25];
#define mp make_pair
int main(){
	scanf("%d %d",&n,&q);
	ufs.makeSet(n);
	for(int i=1;i<=n;++i)	scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)
	{
		int tmp=a[i];
		for(int j=2;j*j<=tmp;++j)
		{
			if(tmp%j==0)
			{
				if(lst[j])	ufs.unionSet(lst[j],i);
				lst[j]=i;
				while(tmp%j==0)	tmp/=j;
			}
		}
		if(tmp!=1)
		{
			if(lst[tmp])	ufs.unionSet(lst[tmp],i);
			lst[tmp]=i;
			tmp=1;
		}
	}
	vector<pair<int,int>> Ret;
	for(int i=1;i<=n;++i)
	{
		int tmp=a[i]+1,cnt=0;
		for(int j=2;j*j<=tmp;++j)
		{
			if(tmp%j==0)
			{
				if(lst[j])	pb[++cnt]=ufs.findSet(lst[j]);
				while(tmp%j==0)	tmp/=j;
			}
		}
		if(tmp!=1)
		{
			if(lst[tmp])	pb[++cnt]=ufs.findSet(lst[tmp]);
			tmp=1;
		}
		pb[++cnt]=ufs.findSet(i);
		sort(pb+1,pb+1+cnt);
		cnt=unique(pb+1,pb+1+cnt)-pb-1;
//		printf("%d\n",cnt);for(int j=1;j<=cnt;++j)	printf("%d ",pb[j]);puts("");
		for(int j=1;j<=cnt;++j)	for(int k=j+1;k<=cnt;++k)	Ret.push_back(mp(min(pb[j],pb[k]),max(pb[j],pb[k])));
	}
	sort(Ret.begin(),Ret.end());
	Ret.erase(unique(Ret.begin(),Ret.end()),Ret.end());
	while(q-->0)
	{
		int s,t;
		scanf("%d %d",&s,&t);
		s=ufs.findSet(s),t=ufs.findSet(t);
		if(s>t)	swap(s,t);
//		printf("%d %d\n",s,t);
		if(s==t)	puts("0");
		else if(lower_bound(Ret.begin(),Ret.end(),mp(s,t))!=Ret.end() && *lower_bound(Ret.begin(),Ret.end(),mp(s,t))==mp(s,t))	puts("1");
		else	puts("2");
	}
	return 0;
}
```

---

