# Ambiguous Dominoes

## 题目描述

Polycarp and Monocarp are both solving the same puzzle with dominoes. They are given the same set of $ n $ dominoes, the $ i $ -th of which contains two numbers $ x_i $ and $ y_i $ . They are also both given the same $ m $ by $ k $ grid of values $ a_{ij} $ such that $ m\cdot k = 2n $ .

The puzzle asks them to place the $ n $ dominoes on the grid in such a way that none of them overlap, and the values on each domino match the $ a_{ij} $ values that domino covers. Dominoes can be rotated arbitrarily before being placed on the grid, so the domino $ (x_i, y_i) $ is equivalent to the domino $ (y_i, x_i) $ .

They have both solved the puzzle, and compared their answers, but noticed that not only did their solutions not match, but none of the $ n $ dominoes were in the same location in both solutions! Formally, if two squares were covered by the same domino in Polycarp's solution, they were covered by different dominoes in Monocarp's solution. The diagram below shows one potential $ a $ grid, along with the two players' solutions.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1695E/ccb87eab878c4ff1d5cb781f15ad4243564c6c79.png)Polycarp and Monocarp remember the set of dominoes they started with, but they have lost the grid $ a $ . Help them reconstruct one possible grid $ a $ , along with both of their solutions, or determine that no such grid exists.

## 说明/提示

Extra blank lines are added to the output for clarity, but are not required.

The third sample case corresponds to the image from the statement.

## 样例 #1

### 输入

```
1
1 2```

### 输出

```
-1```

## 样例 #2

### 输入

```
2
1 1
1 2```

### 输出

```
2 2

2 1
1 1

LR
LR

UU
DD```

## 样例 #3

### 输入

```
10
1 3
1 1
2 1
3 4
1 5
1 5
3 1
2 4
3 3
4 1```

### 输出

```
4 5

1 2 5 1 5
3 4 1 3 1
1 2 4 4 1
1 3 3 3 1

LRULR
LRDLR
ULRLR
DLRLR

UULRU
DDUUD
LRDDU
LRLRD```

# 题解

## 作者：清烛 (赞：5)

题意：有 $n$ 个多米诺骨牌，每张骨牌上有两个数字，要求构造两个将这 $n$ 个骨牌不重叠放入 $m\times k = 2n$ 的棋盘 $a_{m\times k}$ 中的方案，满足对应位置上的数字一样，且要求两种方案中骨牌的位置全部不一样，或报告无解。$n\le 3\times 10^5$。

有点流氓了哈，牛逼构造。

对于每张多米诺骨牌 $(x_i, y_i)$，连一条无向边 $x_i\to y_i$。然后会发现，若一个连通分量里面恰好只有 $1$ 条边，说明这条边代表的多米诺骨牌只有一种摆法，因此无解。

否则总能构造出一个 $2\times k$ 的棋盘（$k$ 为连通分量内边数），见下。

我们随便对这张图进行欧拉遍历（就是 dfs 遍历没有遍历的边，然后将经过的边存下来），然后会发现每条边都恰好在这个欧拉序中出现两次（考虑欧拉序的性质），并且**两次出现的位置的奇偶性不一样**。

如何证明？考虑边 $e=u\to v$，若我们的 dfs 直接返回，则欧拉序列中会形成 $e,e$，两次出现位置的奇偶性显然不同。如果还要继续遍历，由于我们之后遍历的边一定经历了回溯过程，所以两个 $e$ 中间夹着偶数条边，$e$ 出现位置的奇偶性仍然不同。

如果考虑点的遍历序，则我们得到一个长度为 $2k + 1$ 的首尾相接的序列（还是考虑欧拉序的性质），然后将最后一个元素去掉并将其依次顺时针放入 $2\times k$ 的棋盘中，现在骨牌们对应的 $k$ 条边就形成了长 $2n$ 的环。因为每张骨牌**出现位置的奇偶性不一样**，所以下面的两种构造总会是合法的（图源官方题解）：

![](https://espresso.codeforces.com/8d975bc11693b0864bbc0b6e19423e4954b1b282.png)

于是对于一个连通块我们就搞定了。对于多个连通块的情况，把得到的 $2\times k$ 棋盘们拼一起即可，时间复杂度 $O(n)$。

![](https://espresso.codeforces.com/211398dfdf9487ee70a6b189aa834b35c0dd601f.png)

（可能有上面的图更好理解些）

```cpp
#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
const int maxn = 3e5 + 5;
int head[maxn << 1], to[maxn << 2], nxt[maxn << 2], cnte = 1;
int n, vis[maxn << 1], vise[maxn << 2];

il void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

vector<int> path;

void dfs(int u, int pre) {
    path.push_back(u);
    if (vis[u]) return;
    vis[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) if (!vise[i]) {
        vise[i] = vise[i ^ 1] = 1;
        dfs(to[i], i);
        path.push_back(u);
    }
    return;
}

int ans[2][maxn];
char sol1[2][maxn], sol2[2][maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    FOR(i, 1, n) {
        int x, y; cin >> x >> y;
        add(x, y), add(y, x);
    }
    int col = 0;
    FOR(i, 1, n << 1) if (!vis[i]) {
        vector<int>().swap(path);
        dfs(i, 0);
        if (path.size() == 3) return puts("-1"), 0;
        else if (path.size() < 3) continue;
        path.pop_back();
        int k = path.size() >> 1;
        auto it = path.begin();
        FOR(i, 1, k) ans[0][i + col] = *it++;
        DEC(i, k, 1) ans[1][i + col] = *it++;
        for (int i = 2; i <= k; i += 2) sol1[0][col + i] = sol1[1][col + i] = 'R', sol1[0][col + i - 1] = sol1[1][col + i - 1] = 'L';
        for (int i = 3; i <= k; i += 2) sol2[0][col + i] = sol2[1][col + i] = 'R', sol2[0][col + i - 1] = sol2[1][col + i - 1] = 'L';
        if (k & 1) sol1[0][col + k] = 'U', sol1[1][col + k] = 'D';
        else sol2[0][col + k] = 'U', sol2[1][col + k] = 'D';
        sol2[0][col + 1] = 'U', sol2[1][col + 1] = 'D';
        col += k;
    }
    cout << 2 << ' ' << col << '\n';
    FOR(i, 0, 1) {
        FOR(j, 1, col) cout << ans[i][j] << ' ';
        cout << '\n';
    }
    FOR(i, 0, 1) {
        FOR(j, 1, col) cout << sol1[i][j];
        cout << '\n';
    }
    FOR(i, 0, 1) {
        FOR(j, 1, col) cout << sol2[i][j];
        cout << '\n';
    }
    return 0;
}
```

---

## 作者：BreakPlus (赞：1)

+ *2700 居然有如此原神的构造题，来水一篇题解。

+ 直接把样例 2 的构造中连边方案画出来：

![](https://cdn.luogu.com.cn/upload/image_hosting/tv08qs0x.png)

+ 如图，蓝色是第一种构造的连边，红色是第二种构造的连边，不难发现会形成多个环。

+ 这是因为，恰好有 $2n$ 个点、$2n$ 条边、每个点度数恰好为 $2$。

+ 每个环长度均为偶数且 $\ge 4$，一个环中相邻两条边属于不同的划分方案。

+ 考虑如何保证红边和蓝边刚好覆盖了给定的边集。我们假设当前构造的东西中有一个点 $1$，此时我们加进来一条边连接 $1$ 和 $2$，那么点 $1$ 可以等效替代为 $1 \to 2 \to 1$，发现这两条边必然一红一蓝，符合构造要求，不影响图的基本性质。

+ 于是我们就有了简单的思路：对于同一个连通块里的数字（将每一块多米诺骨牌的两个数字看成同一个连通块中），我们可以先取任意一条边，然后再将其他边依次等效替代进去。

+ 以下模拟一组样例：

```
4
1 2
1 3
1 4
2 4
```

+ 初始有一条边 $(1,2)$，构成一个环 $1 \to 2$。（最后一个点连向第一个点的边省略不写，就是说其实当前还有一条边 $2 \to 1$）；

+ 加入边 $(1,3)$，将 $1$ 替代为 $1 \to 3 \to 1$，构成的环为 $1 \to 3 \to 1 \to 2$。

+ 加入边 $(1,4)$，任取一个 $1$ 替代为 $1 \to 4 \to 1$，构成的环为 $1 \to 3 \to 1 \to 4 \to 1 \to 2$。

+ 加入边 $(2,4)$，取 $2$ 替代为 $2 \to 4 \to 2$，构成的环为 $1 \to 3 \to 1 \to 4 \to 1 \to 2 \to 4 \to 2$。

+ 至此我们完成了对一个连通块内的构造。

+ 如果一个连通块内构造出长度为 $2$ 的环则无解。

+ 构造完环之后就可以简单输出一个 $2 \times n$ 的矩阵了。

+ 可以使用循环链表完成构造。

```cpp
ll n,x[1200005],y[1200005],vis[1200005],vis2[1200005],dy[1200005]; vector<P>E[1200005];
struct Node{
	ll prv, val, nxt;
}node[1200005];
ll id[1200005], cnt;
void Insert(ll x,ll y){
	ll w = id[x];
	if(node[w].nxt == w){
		ll w1 = (++cnt);
		node[w].prv = node[w].nxt = w1;
		node[w1].prv = node[w1].nxt = w; node[w1].val = y;
		id[y] = w1;
	}else{
		ll w1 = (++cnt), w2 = (++cnt);
		node[w1].prv = w, node[w1].val = y, node[w1].nxt = w2;
		node[w2].prv = w1, node[w2].val = x, node[w2].nxt = node[w].nxt;
		node[w].nxt = w1;
		id[y] = w1;
	}
}
void dfs(ll x){
	vis2[x]=1;
	for(auto p: E[x]){
		ll y=p.first, id=p.second;
		if(vis[id]) continue;
		vis[id] = 1;
		Insert(x, y);
		if(!vis2[y]) dfs(y);
	}
}
ll ans[2][300005]; char s[2][300005], t[2][300005];
int main(){
	ios::sync_with_stdio(0);
	n=read();
	for(ll i=1;i<=n;i++){
		x[i]=read(), y[i]=read();
		E[x[i]].pb(y[i], i);
		E[y[i]].pb(x[i], i);
		dy[x[i]]= dy[y[i]] = 1;
	}
	ll Pt = 0;
	for(ll i=1;i<=2*n;i++)
		if(dy[i] && !vis2[i]){
			ll pt = (++cnt);
			node[pt].prv = node[pt].nxt = pt; node[pt].val = i; id[i] = pt;
			dfs(i);
			ll now = id[i];
			vector<ll>vec;
			vec.pb(node[now].val);
			while (node[now].nxt != id[i]){
				now = node[now].nxt;
				vec.pb(node[now].val);
			}
			if(vec.size() <= 2) {
				puts("-1");
				return 0;
			}
			ll k=0;
			for(ll j=Pt+1; j<=Pt+vec.size()/2; j++){
				ans[0][j] = vec[k++];
			}
			for(ll j=Pt+vec.size()/2; j>=Pt+1; j--){
				ans[1][j] = vec[k++];
			}
			if(!(vec.size()&3)){
				for(ll j=Pt+1; j<=Pt+vec.size()/2; j+=2)
					s[0][j] = s[1][j] = 'L', s[0][j+1] = s[1][j+1] = 'R';
				t[0][Pt+1] = 'U'; t[1][Pt+1] = 'D';
				for(ll j=Pt+2; j<=Pt+vec.size()/2; j+=2)
					t[0][j] = t[1][j] = 'L', t[0][j+1] = t[1][j+1] = 'R';
				t[0][Pt+vec.size()/2] = 'U'; t[1][Pt+vec.size()/2] = 'D';
			}else{
				for(ll j=Pt+1; j<=Pt+vec.size()/2; j+=2)
					s[0][j] = s[1][j] = 'L', s[0][j+1] = s[1][j+1] = 'R';
				s[0][Pt+vec.size()/2] = 'U'; s[1][Pt+vec.size()/2] = 'D';
				
				t[0][Pt+1] = 'U'; t[1][Pt+1] = 'D';
				for(ll j=Pt+2; j<=Pt+vec.size()/2; j+=2)
					t[0][j] = t[1][j] = 'L', t[0][j+1] = t[1][j+1] = 'R';
			}
			Pt += vec.size()/2;
		}
	cout<<"2 "<<n<<endl<<endl;
	for(ll i=0;i<=1;i++){
		for(ll j=1;j<=n;j++) cout<<ans[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	for(ll i=0;i<=1;i++){
		for(ll j=1;j<=n;j++) cout<<s[i][j];
		cout<<endl;
	}
	cout<<endl;
	for(ll i=0;i<=1;i++){
		for(ll j=1;j<=n;j++) cout<<t[i][j];
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：HBWH_zzz (赞：1)

# [CF1695E Ambiguous Dominoes](https://codeforces.com/problemset/problem/1695/E)

>如下图，给定 $n$ 个 $1\times 2$ 的多米诺骨牌，每个骨牌两边均写有数字，求一种矩形的构造方案，使得存在 $2$ 种不同的方法将多米诺放进矩形中，使得不存在 $(x_1,y_1)$ 和 $(x_2,y_2)$ 满足：在 $2$ 种方案中它们均在同一个多米诺中。 $n\leq 3\times 10^5$ 。
>
>![39690878422192de705ee07065488f6ef6a452c4.png (1855×425) (codeforces.com)](https://espresso.codeforces.com/39690878422192de705ee07065488f6ef6a452c4.png)

首先考虑建图，将每个 $x_i,y_i$ 连双向边，那么就将 $n$ 个多米诺抽象成了 $n$ 条边。很容易发现，当存在一个连通块使得该连通块中有且仅有 $1$ 条边，那么该情况将无解。

考虑如何构造出一个方案，首先对于每个连通块进行一次 dfs ，记录下每个节点出现的地方，但是细节却不太一样：

对于每个第一次访问的节点遍历每条边，若这条边被经过则不去向下一个节点，否则去向，并在返回后重新将该节点放入答案。

对于每个不是第一次被访问的节点，直接记录一次并返回。

这里放个代码，其中 qwq 是用一个 `vector` 来记录每个节点， `ncnt` 用来记录当前连通块的编号。

```cpp
void dfs(int x){
	qwq[ncnt].push_back(x);
	if(vis[x])
		return;
	vis[x]=1;
	for(int i=head[x];i;i=e[i].nxt){
		if(book[i>>1])
			continue;
		book[i>>1]=1;
		dfs(e[i].to);
		qwq[ncnt].push_back(x);
	}
}
```

然后就会发现一个很有趣的事实，就是这个序列长度为 $2\times k+1$ ，其中 $k$ 表示连通块中边的个数。这是因为在上述 dfs 的过程中 dfs 树上的每一条边都被经过了一次，产生的 $2$ 的贡献，而一开始时还经过了 dfs 树的根节点，所以是 $2\times k+1$ 。

更有意思的是，第一个节点和最后一个节点一定相同，都是根，当对 `qwq[ncnt].pop_back()` 之后就会得到一个长度为 $2\times k$ 的序列。将序列连成环则可以发现环上的每个 $(i,i+1)$ 都构成了原图上的一条边（因为这是在 dfs 树上），并且每条边都出现了 $2$ 次（因为在进 dfs 树和出 dfs 树时都会出现一次）。最后有一个我不太会证的结论，即每条边出现的地方奇偶性不同。（有兴趣的可以参考官方题解）

那么接下来就可以利用这些结论了：对于每个连通块将 dfs 得到的 `qwq` 数组按照顺时针（逆时针也行）绕成一个环（放到网格上是 $2\times k$ 的一段），那么取环上奇偶性不同的 $2$ 个点得到的 $2$ 种方案即为答案（可以参考下图进行理解），那么答案就是将所有连通块的网格都合并一下就好了。

![211398dfdf9487ee70a6b189aa834b35c0dd601f.png (1722×740) (codeforces.com)](https://espresso.codeforces.com/211398dfdf9487ee70a6b189aa834b35c0dd601f.png)

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int head[600005],ecnt=1;
struct edge{
	int to,nxt;
}e[1200005];
void adde(int u,int v){
	e[++ecnt].to=v;
	e[ecnt].nxt=head[u];
	head[u]=ecnt;
}
vector<int> qwq[600005];
int ncnt;
int m[2][600005],qnq[600005];
char M1[2][600005],M2[2][600005];
bool vis[600005],book[600005];

void dfs(int x){
	qwq[ncnt].push_back(x);
	if(vis[x])
		return;
	vis[x]=1;
	for(int i=head[x];i;i=e[i].nxt){
		if(book[i>>1])
			continue;
		book[i>>1]=1;
		dfs(e[i].to);
		qwq[ncnt].push_back(x);
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1,ui,vi;i<=n;++i){
		scanf("%d %d",&ui,&vi);
		adde(ui,vi);
		adde(vi,ui);
		qnq[ui]++;
		qnq[vi]++;
	}
	for(int i=1;i<=2*n;++i){
		if(qnq[i]>2)
			continue;
		if(qnq[i]==2 && e[head[i]].to==i && e[e[head[i]].nxt].to==i){
			printf("-1");
			return 0;
		}
		if(qnq[i]!=1)
			continue;
		for(int j=head[i];j;j=e[j].nxt){
			if(qnq[e[j].to]==1){
				printf("-1");
				return 0;
			}
		}
	}
	for(int i=1;i<=2*n;++i){
		if(vis[i]==0){
			ncnt++;
			dfs(i);
			qwq[ncnt].pop_back();
		}
	}
	for(int i=1,qaq=1;i<=ncnt;++i){
		if(qwq[i].size()==0)
			continue;
		for(int j=0;j<(int)qwq[i].size();++j){
			if(j<(int)qwq[i].size()/2){
				m[0][qaq+j]=qwq[i][j];
			}
			if(j>=(int)qwq[i].size()/2){
				m[1][(int)qwq[i].size()-j-1+qaq]=qwq[i][j];
			}
		}
		if((qwq[i].size()/2)%2==0){
			for(int j=0;j<qwq[i].size()/4;++j){
				M1[0][qaq+2*j]='L';
				M1[0][qaq+2*j+1]='R';
			}
			for(int j=0;j<qwq[i].size()/4;++j){
				M1[1][qaq+2*j]='L';
				M1[1][qaq+2*j+1]='R';
			}
			for(int j=1;j<qwq[i].size()/4;++j){
				M2[0][qaq+2*j-1]='L';
				M2[0][qaq+2*j]='R';
			}
			for(int j=1;j<qwq[i].size()/4;++j){
				M2[1][qaq+2*j-1]='L';
				M2[1][qaq+2*j]='R';
			}
			M2[0][qaq]='U';
			M2[1][qaq]='D';
			M2[0][qaq+qwq[i].size()/2-1]='U';
			M2[1][qaq+qwq[i].size()/2-1]='D';
			
		}
		else{
			for(int j=0;j<qwq[i].size()/4;++j){
				M1[0][qaq+2*j]='L';
				M1[0][qaq+2*j+1]='R';
			}
			for(int j=0;j<qwq[i].size()/4;++j){
				M1[1][qaq+2*j]='L';
				M1[1][qaq+2*j+1]='R';
			}
			for(int j=1;j<qwq[i].size()/4+1;++j){
				M2[0][qaq+2*j-1]='L';
				M2[0][qaq+2*j]='R';
			}
			for(int j=1;j<qwq[i].size()/4+1;++j){
				M2[1][qaq+2*j-1]='L';
				M2[1][qaq+2*j]='R';
			}
			M2[0][qaq]='U';
			M2[1][qaq]='D';
			M1[0][qaq+qwq[i].size()/2-1]='U';
			M1[1][qaq+qwq[i].size()/2-1]='D';
		}
		qaq+=qwq[i].size()/2;
	}
	printf("%d %d\n",2,n);
	for(int i=0;i<=1;++i){
		for(int j=1;j<=n;++j)
			printf("%d ",m[i][j]);
		printf("\n");
	}
	printf("%s\n%s\n",M1[0]+1,M1[1]+1);
	printf("%s\n%s\n",M2[0]+1,M2[1]+1);
	return 0;
}
```

---

