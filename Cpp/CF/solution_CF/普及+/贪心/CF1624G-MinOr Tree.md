# MinOr Tree

## 题目描述

Recently, Vlad has been carried away by spanning trees, so his friends, without hesitation, gave him a connected weighted undirected graph of $ n $ vertices and $ m $ edges for his birthday.

Vlad defined the ority of a spanning tree as the [bitwise OR](https://tiny.cc/bitwise_or) of all its weights, and now he is interested in what is the minimum possible ority that can be achieved by choosing a certain spanning tree. A spanning tree is a connected subgraph of a given graph that does not contain cycles.

In other words, you want to keep $ n-1 $ edges so that the graph remains connected and the bitwise OR weights of the edges are as small as possible. You have to find the minimum bitwise OR itself.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1624G/b7f5b7382b2cbd80980c576ea1b925aa7c500ed8.png)Graph from the first test case.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1624G/43a768dfee0ade0f80ced3a4660bcaac868cc17b.png)Ority of this tree equals to 2 or 2 = 2 and it's minimal.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1624G/c7716ab52b41700a181dd76536e0574654ad531d.png)Without excluding edge with weight $ 1 $ ority is 1 or 2 = 3.

## 样例 #1

### 输入

```
3

3 3
1 2 1
2 3 2
1 3 2

5 7
4 2 7
2 5 8
3 4 2
3 2 1
2 4 2
4 1 2
1 2 2

3 4
1 2 1
2 3 2
1 3 3
3 1 4```

### 输出

```
2
10
3```

# 题解

## 作者：AFewSuns (赞：12)

**CF764 Div.3（VP） 做题记录**

- A. plus One on the Subset

- B. Make AP

- C. Division by Two and Permutation

- D. Palindromes Coloring

- E. Masha-forgetful

- F. Interacdive Problem

- $\color{red}\texttt{G. MinOr Tree}$

### 题目大意

$t$ 组询问，每次询问给你一张 $n$ 个点， $m$ 条边的无向带权连通图，求生成树中所有边权之或的最小值。

$1 \leq t \leq 10^4,3 \leq n \leq 2 \times 10^5,n-1 \leq m \leq 2 \times 10^5,1 \leq w_i \leq 10^9,\sum n \leq 2 \times 10^5$

### 题目分析

考虑二进制拆位。如果答案的第 $i$ 位可以为 $0$，则无论后 $i-1$ 位是多少，都比第 $i$ 位为 $1$ 要优。所以将位数从高到底贪心，判断可不可以为 $0$，可以就直接为 $0$。

要让第 $i$ 位为 $0$，说明选取的所有边的权值第 $i$ 位都为 $0$。在**之前的条件下（后面解释）**，将第 $i$ 位为 $0$ 的边全部加进来，如果最终所有点连通，那么一定可以找到一颗符合条件的生成树，让答案第 $i$ 位为 $0$。否则答案第 $i$ 位只能为 $1$。

举个例子，现在答案是 $(00000)_2$，如果第 $4$ 位可以为 $0$，即可以连通，那么答案就变成了 $(00000)_2$。然后在考虑第 $3$ 位时，我们应该 **在第 $4$ 位为 $0$ 的基础上** 加入符合条件的边，如果一条边的权值为 $(10110)_2$，尽管它第 $3$ 位是 $0$，它仍然不能被加入。加完边之后，如果图不能连通，那么第 $3$ 位只能为 $1$，答案为 $(01000)_2$。

对于判断图是否连通，可以用并查集维护，如果所有节点的父亲相同，就连通，否则不连通。

时间复杂度 $O(m\log W)$

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,n,m,fa[200020];
struct edge{
	ll u,v,w;
}e[200020];
ll find(ll x){
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
bool solve(ll x,ll k){
	for(ll i=1;i<=n;i++) fa[i]=i;
	for(ll i=1;i<=m;i++){
		if((e[i].w|x)>=(x+(1ll<<(k+1)))) continue;//必须要满足先前的条件 
		if((e[i].w>>k)&1) continue;//第 k 位要为 0 
		ll fax=find(e[i].u),fay=find(e[i].v);//并查集加边 
		if(fax==fay) continue;
		fa[fax]=fay;
	}
	bool ck=1;
	for(ll i=2;i<=n;i++) if(find(1)!=find(i)) ck=0;//判断是否连通 
	return ck;
}
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld %lld",&n,&m);
		for(ll i=1;i<=m;i++) scanf("%lld %lld %lld",&e[i].u,&e[i].v,&e[i].w);
		ll ans=0;
		for(ll i=31;i>=0;i--) if(!solve(ans,i)) ans|=1ll<<i;//如果不连通，就必须为1 
		printf("%lld\n",ans);
	}
}
```

---

## 作者：落海沉 (赞：4)

### 前言
总所周知，最小生成树的路径是加，而本题是进行或运算，所以最小生成树的算法可能需要加一些神奇的东西。
### 题目分析
这题是求或运算下的最小生成树，我们可以类比最小生成树的思想，经典的最小生成树算法 Kruskal 是通过贪心取边，所以我们也考虑或运算下的贪心取边。有个显然的贪心策略，假设这一条边不是必需边，对图进行一次遍历，对于当前位为 $1$ 的都不取，跑图是否能遍历完所有的点，如果可以，$0$ 肯定不劣，如果不行，本位只能为 $1$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e6+10;
const int M = 2e6+10;
const int inf = 1<<30;
struct node {
	int v,w;
	node(int _v,int _w){
		v=_v;
		w=_w;
	}
};
vector<node> G[N];
int Case,n,m,bitt,cot,maxn,A,B,C,ans;
bool vis[N];
void dfs(int x,int k){
	if(vis[x])return ;
	cot++;
	vis[x]=1;
	for(register int i=0;i<G[x].size();i++){
		int uu=G[x][i].v;
		int ww=G[x][i].w;
		if((ww|maxn)!=maxn)continue;//如果这条边也是1，直接continue，不取 
		dfs(uu,k);
	}
}
void solve(){
	ans=0;
	cin>>n>>m;
	for(register int i=1;i<=m;i++){
		cin>>A>>B>>C;
		G[A].push_back(node(B,C));
		G[B].push_back(node(A,C));
	}
	for(register int i=bitt;i>=0;i--){
		//删去这一位，跑图 
		maxn-=(1ll<<i);
		cot=0;
		memset(vis,0,(n+1)*sizeof(int));
		dfs(1,i);
		if(cot!=n)maxn+=(1<<i);//没有遍历完所有的点，所以这一位必须为1，因为这一位为1的某条边是必须的 
	}
	cout<<maxn<<endl;
	for(register int i=1;i<=n;i++)G[i].clear();
}
signed main(){
	ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>Case;
    while(Case--){ 
		bitt=0;   
		for(register int i=1;i<inf;i=i*2+1){
    		maxn=i;
    		++bitt;
		}
		maxn=maxn*2+1;
		//maxn为30位每位为1的数 
    	solve();
	}
	return 0;
}
```


---

## 作者：Xdl_rp (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF1624G)

不懂最小生成树的可以戳[这里](https://www.luogu.com.cn/blog/Delonxdl-legend/zui-xiao-sheng-cheng-shu)
- 先确定答案最高 $2$ 进制位（第 $30$ 二进制位）是 $0$ 还是$1$：把所有最高位是 $1$ 的边去掉，看剩下的图是否连通（这一步用并查集）， 如果连通，说明答案的最高位是 $0$，就可以把这些最高位是 $1$ 的边去掉；否则答案的最高位是 $1$ 这样每位每位做下去，最后得到答案每位是 $0$ 还是 $1$，也就得到答案。


代码：
------------

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int f[N];//表示第i个节点的祖先节点
bool vis[N];//标记访问（也就是刚刚说的删除的意思）
struct node{
	int fr, to, len;//分别是front,to,length
}ed[N];//结构体
void init(int x) {
	for (int i = 1; i <= x; i++) f[i] = i;
}//初始化每一个祖先节点为自己
int getfa(int x) {
	return f[x] == x ? f[x] : f[x] = getfa(f[x]);
}//路径压缩的寻找祖先
void join(int x, int y, int &k) {
	x = getfa(x), y = getfa(y);
	if (x == y) return;
	else f[x] = y, k--;
}//将x节点所在的连通块和y节点所在的联通块连接起来
signed main() {
	int T;
	scanf("%lld", &T);
	while (T--) {
		int n, m;
		scanf("%lld %lld", &n, &m);
		init(n);//初始化
		for (int i = 1; i <= m; i++) vis[i] = 0;//手动清0
		for (int i = 1; i <= m; i++) {
			scanf("%lld %lld %lld", &ed[i].fr, &ed[i].to, &ed[i].len);
		}
		int ans = 0;
		for (int i = 30; i >= 0; i--) {//最高位是30，所以从30开始
			int cnt = n;//连通块的数量
			for (int j = 1; j <= m; j++) {
				if (vis[j] == 1) continue;//删除后不理
				if (!(ed[j].len & (1 << i))) {
					join(ed[j].fr, ed[j].to, cnt);
				}//判断i位是否为1，不是才加入
			}
			if (cnt == 1) {//如果只剩一个连通块了，说明都和在一起了
				for (int j = 1; j <= m; j++) {
					if (ed[j].len & (1 << i)) {
						vis[j] = 1;
					}
				}//删除所有i位为1的节点
			}
			else {
				ans += (1 << i);//否则第i位必须为1
			}
			init(n);//重新初始化
		}
		printf("%lld\n", ans);//输出
	}
	return 0;//华丽的结束
}
```


---

## 作者：Aw顿顿 (赞：2)

有点妙的一道题。

题意：求或运算下的最小生成树。

## 思路

由于是在位运算下进行处理，很容易能想到按位进行贪心，接下来具体说一下思路。答案最优显然是全 $0$ 的，但是这个最优不一定能时时刻刻都做到，我们考虑怎么样将损失最小化。

对比 $(10000)_2$ 和 $(01111)_2$ 两个答案可以发现，即使后一个数一共有四位是 $1$，它依然比前一个数要大，因此通过比较 $1$ 的个数显然不合适；而同样显而易见的是，较高位取 $0$ 比较低位更优。

于是我们可以从最高位向下贪心，判断每一位是否可以取 $0$，由此得到答案。具体而言，如果第 $i$ 位及以上全部取 $0$ 依然能够构造出合格的生成树，那么显然答案的这一位就可以取到 $0$。

考虑到此题思维难度不高，接下来再具体谈一谈实现方法。

## 实现

对于每一条加进来的边，要进行以下判断：

- 在已经确定为 $0$ 的高位是否出现 $1$，若出现则应抛弃。
- 当前位置是否为 $1$，如果是就抛弃。

然后进行判断，如果加入后依然不能连通，那么这一位就不得不取到 $1$。其余的和普通的 Kruskal 是类似的。进行判断的那一句话不好写，可以参考@AFewSuns 的写法。

代码：https://paste.ubuntu.com/p/CN5xmS8svW/

可能因为 pastebin 的问题导致缩进有点不太对。

---

## 作者：liangbowen (赞：1)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1624G)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17366172.html)

比较好玩的二进制题目。

## 思路

答案最小，也就是说较高位要尽可能小。所以很容易想到从最高位开始枚举。

第 $i$ 位为 $0$，等价于选出的所有边的第 $i$ 位都为 $0$。同时，由于我们是**贪心**，如果之前枚举过的第 $j$ 位可以是 $0$，那么这两个条件要同时满足。

那么怎样才算第 $i$ 位可以是 $0$ 呢？将不满足上述要求的边都排除掉，如果剩下的边可以使得图联通的话，说明必然有一种生成树是合法的，统计即可。

实现并不困难，使用并查集实现。不满足的用一个 $vis_i$ 记录即可。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 2e5 + 5;
struct Edge {int now, nxt;} e[N << 1];
int head[N], cur;
void add(int u, int v)
{
	e[++cur].now = v, e[cur].nxt = head[u];
	head[u] = cur;
}
bool used[N], vis[N]; int vist;
void dfs(int u)
{
	vist++, vis[u] = true;
	for (int i = head[u]; i; i = e[i].nxt)
	{
		int v = e[i].now;
		if (!vis[v]) dfs(v);
	}
}
int uu[N], vv[N], ww[N];
void solve()
{
	int n, m, ans = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &uu[i], &vv[i], &ww[i]), used[i] = false;
	for (int j = 30; ~j; j--) //从高到低枚举每一位 
	{
		cur = 0; for (int i = 1; i <= n; i++) head[i] = 0;
		vist = 0; for (int i = 1; i <= n; i++) vis[i] = false;
		
		for (int i = 1; i <= m; i++)
			if (!used[i] && !(ww[i] & (1 << j)))
				add(uu[i], vv[i]), add(vv[i], uu[i]);
		dfs(1);
		if (vist != n) ans += (1 << j); //不是连通的
		else
		{
			for (int i = 1; i <= m; i++)
				if (ww[i] & (1 << j))
					used[i] = true;
		}
	}
	printf("%d\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--) solve();
	return 0;
}
```

希望能帮助到大家！

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 1900}$

---
### 解题思路：

首先有一个挺重要的性质（其他地方也可能用到）：$2^n=\sum_{i=1}^{n-1}2^i+1$，换言之，就是 $2^n\ge\sum_{i=1}^{n-1}2^i$。
也就是说二进制下，高位的一要比之后的所有的一的价值都要高。

根据这个，可以考虑从最高位开始向下枚举，如果当前位为 $0$ 依然可以联通（就是所有的这一位边权为 $1$ 的都不取）就将这一位设置为 $0$，并且将所有的这一位为 $1$ 的边都删去，否则将这一位设置为 $1$，并开始考虑下一位。

总复杂度是 $O((n+m)\log a)$ 的，可以接受。

多测，记得清空。

---
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=400005;
int T,head[MAXN],nxt[MAXN],num[MAXN],w[MAXN],del[MAXN],v[MAXN],n,m,cnt,x,y,z,ans;
void add(int x,int y,int z){
	nxt[++cnt]=head[x];head[x]=cnt;num[cnt]=y;w[cnt]=z;
}
void dfs(int now,int d){
	v[now]=1;
	for(int i=head[now];i;i=nxt[i]){
		if(del[i]||(((w[i]>>d)&1)==1))continue;
		if(v[num[i]]==1)continue;
		dfs(num[i],d);
	}
}
bool check(int d){
	for(int i=1;i<=n;i++)
	v[i]=0;
	dfs(1,d);
	for(int i=1;i<=n;i++)
	if(v[i]==0)return 0;
	for(int i=1;i<=cnt;i++)
	if((((w[i]>>d)&1)==1))del[i]=1;
	return 1;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=m;i++){
			scanf("%lld%lld%lld",&x,&y,&z);
			add(x,y,z);add(y,x,z);
		}
		ans=0;
		for(int i=30;i>=0;i--)if(check(i)==0)ans+=(1<<i);
		printf("%lld\n",ans);
		for(int i=1;i<=cnt;i++)
		head[i]=nxt[i]=num[i]=w[i]=del[i]=0;
		cnt=0;
	}
	return 0;
}
```


---

## 作者：ArrogHie (赞：1)

## 题意

求一个生成树使得树上路径 OR 和最小。

## 题解

类似于 AND 和 OR 求最值一般考虑贪心，从高位往低位贪，答案中能不填一就不填一。

设答案为 $ans$，初始时为最大值即所有位上都为 $1$，从高位往低位依次枚举，枚举到第 $i$ 位，若该位为 $1$ 的边都不能选依然能构造出生成树，说明 $ans$ 的第 $i$ 位可以为 $0$，否则 $ans$ 的第 $i$ 位只能为 $1$。



---

## 作者：luan341502 (赞：0)

好题！

首先看到在或运算下，想到一定是贪心来取边，答案越高的位上能不取就不取。

考虑对答案的每一位，判断该位为 $0$ 是否可行，若不可行就只能为 $1$。注意高位上的 $0$ 对低位是有限制的，因为如果高位上可以取 $0$，那么在判断低位是否可行是就不能连上高位为 $1$ 的边。

具体实现时，我们可以用 kruskal 类似的方法用 dsu 维护，如果答案某一位可以取 $0$ 的话把该位为 $1$ 的边筛掉即可。

时间复杂度为 $ O((n+m)\log V )$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans=0,fa[200005];
struct edge{
	int u,v,w;
	bool p;
}e[200005];
int find(int k){
	if(fa[k]==k) return k;
	return fa[k]=find(fa[k]);
}
void calc(int k){
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++){
		if(e[i].p||((e[i].w>>k)&1)) continue;
		int fu=find(e[i].u),fv=find(e[i].v);
		if(fu^fv) fa[fu]=fv;
	}
	int x=find(1);
	for(int i=2;i<=n;i++)
		if(find(i)!=x){ans+=1<<k;return;}
	for(int i=1;i<=m;i++) if((e[i].w>>k)&1) e[i].p=true;
}
void solve(){
	cin>>n>>m;ans=0;
	for(int i=1;i<=m;i++){cin>>e[i].u>>e[i].v>>e[i].w;e[i].p=false;}
	for(int bit=31;bit>=0;bit--) calc(bit);
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int tt;cin>>tt;while(tt--)solve();
	return 0;
}
```


---

## 作者：hcywoi (赞：0)

我们设答案为 $ans$。如果 $ans$ 中，前 $i+1$ 位都已经填好，且是最优的。则 $ans$ 二进制位上第 $i$ 位近可能为 $0$。因为如果第 $i$ 位是 $0$，$i-1$ 为无论怎么选都是 $\le 2^i - 1$，而第 $i$ 位为 $1$ 无论后面怎么选 $\ge 2^i$，所以第 $i$ 为尽可能为 $0$。

那么我们就从高位往前，去判断这个位上填 $0$ 是否合法。

***

#### 判断是否合法
- 维护一个集合 $S$。$S$ 存储的是当前可以用的边的编号;
- 遍历集合 $S$ 判断 $w$ 的第 $i$ 位是否为 $0$。如果为 $0$，就说明这条边可以用;
- 最后判断一下这几条边是否连通(可以用并查集做)。

***

#### Ac Code
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 200010;

int n, m;
struct Edge
{
    int a, b, w;
}e[N];
int p[N];

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    int T;
    scanf("%d", &T);
    
    while (T -- )
    {
        scanf("%d%d", &n, &m);
        vector<int> S;
        for (int i = 0; i < m; i ++ )
        {
            scanf("%d%d%d", &e[i].a, &e[i].b, &e[i].w);
            S.push_back(i); // 先把所有边都加入集合
        }

        int res = 0; // res 记录的是答案
        for (int i = 30; i >= 0; i -- )
        {
            for (int j = 1; j <= n; j ++ ) p[j] = j; // 初始化并查集数组
            
            int cnt = n; // cnt 维护的是集合数量
            for (auto x: S)
            {
                int a = e[x].a, b = e[x].b, w = e[x].w;
                if (w >> i & 1) continue; // 判断该点是否合法
                a = find(a), b = find(b);
                if (a != b) cnt --, p[a] = b; // 如果这边的两端不在同一个集合，且能合并，就把集合-1
            }
            
            if (cnt > 1) // 判断集合的数量是否 >1，如果 >1 就说明不连通
            {
                res += (1 << i); // 累加上答案
                continue;
            }
            
            // 如果合法，则将集合 S 更新
            vector<int> g;
            for (auto x: S) // 当然，这个循环可以到上面的循环中执行
            {
                int a = e[x].a, b = e[x].b, w = e[x].w;
                if (w >> i & 1) continue; // 如果该位为 1，则说明该边不合法，就直接从集合 S 中踢去
                g.push_back(x);
            }

            S = g;
        }
        
        printf("%d\n", res);
    }
    
    return 0;
}
```

---

## 作者：清烛 (赞：0)

## Description
给定一张无向图，定义其生成树的边权为 OR 和，求最小生成树的边权 OR 和。

## Solution
根据 OR 运算的性质，我们注意到只要第 $j$ 位上有被选的数，那么其答案的第 $j$ 位就为 $1$。于是我们有如下的贪心算法。

考虑从高到低按位贪心，用并查集判断该位是不是必须取，不是的话就不取。具体地，令 $ans = 2^{30} - 1$，然后每次先将 $ans$ 的第 $j$ 位去掉，看能否满足存在生成树，若能存在则第 $j$ 位不取。

## Implementation
```cpp
const int maxn = 2e5 + 5;
struct edge {
    int u, v, w;
} e[maxn];
int n, m, fa[maxn];

int find(int u) {return fa[u] == u ? u : fa[u] = find(fa[u]);}

int merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    return fa[u] = v, true;
}

int check(int mask) {
    FOR(i, 1, n) fa[i] = i;
    int size = n;
    FOR(i, 1, m) {
        if ((e[i].w | mask) != mask) continue;
        if (merge(e[i].u, e[i].v)) --size;
    }
    return size == 1;
}

int main() {
    int T; read(T);
    while (T--) {
        read(n, m);
        FOR(i, 1, m) read(e[i].u, e[i].v, e[i].w);
        int ans = (1 << 30) - 1;
        DEC(i, 29, 0) {
            ans ^= (1 << i);
            if (!check(ans)) ans ^= (1 << i);
        }
        print(ans);
    }
    return output(), 0;
}
```

---

## 作者：Nephren_Sakura (赞：0)

题目传送门：[link](https://www.luogu.com.cn/problem/CF1624G)。

首先，或运算不太好处理，考虑按位处理。

如果当前这一位能够为 $0$，就不考虑后面的位是否为 $1$，而先让当前位为 $0$。

原因是一个高位为 $1$ 比一大堆低位为 $1$ 的代价都要大。

然后现在的问题就是如何判断当前为能否为 $0$。

首先先把当前位为 $1$ 的边全部删掉，判断图是否连通同时记录下删了那些边。

如果图不连通了就代表当前位不能为 $0$，把刚刚删的边加回去就行了，同时答案更新。

否则当前为可以为 $0$，那就不加刚刚删的边然后让当前位为 $1$。

感觉讲的很清楚了，不理解的看代码吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,m,fa[1000005];
bool f[1000005];
vector<int> v;
int find(int x){
	if(fa[x]==x)
		return x;
	return fa[x]=find(fa[x]);
}//并查集，判断图是否联通
struct node{
	int x,y,w;
}a[1000005];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1; i<=m; i++)
			cin>>a[i].x>>a[i].y>>a[i].w,f[i]=true;
		int ans=0;
		for(int i=30; i>=0; i--){
			v.clear();
			for(int j=1; j<=m; j++)
				if((a[j].w&(1<<i))&&f[j]==true)
					f[j]=false,v.push_back(j);//删除当前位置为 1 的边，注意如果以前删了当前就不能加入v数组，不然会把它重新加回来
			for(int j=1; j<=n; j++)
				fa[j]=j;//重置并查集
			for(int j=1; j<=m; j++)
				if(f[j]==true){
					int fx=find(a[j].x),fy=find(a[j].y);
					if(fx!=fy)
						fa[fx]=fy;
				}//判断剩下的边能否联通
			int s=0;
			for(int j=1; j<=n; j++)
				s+=(find(j)==j);
			if(s!=1){
				ans+=(1<<i);//不能联通把边加回来并且答案加贡献
				for(int j=0; j<v.size(); j++)
					f[v[j]]=true;
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

