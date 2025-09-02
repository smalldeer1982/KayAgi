# Persistent Bookcase

## 题目描述

Recently in school Alina has learned what are the persistent data structures: they are data structures that always preserves the previous version of itself and access to it when it is modified.

After reaching home Alina decided to invent her own persistent data structure. Inventing didn't take long: there is a bookcase right behind her bed. Alina thinks that the bookcase is a good choice for a persistent data structure. Initially the bookcase is empty, thus there is no book at any position at any shelf.

The bookcase consists of $ n $ shelves, and each shelf has exactly $ m $ positions for books at it. Alina enumerates shelves by integers from $ 1 $ to $ n $ and positions at shelves — from $ 1 $ to $ m $ . Initially the bookcase is empty, thus there is no book at any position at any shelf in it.

Alina wrote down $ q $ operations, which will be consecutively applied to the bookcase. Each of the operations has one of four types:

- $ 1 $ $ i $ $ j $ — Place a book at position $ j $ at shelf $ i $ if there is no book at it.
- $ 2 $ $ i $ $ j $ — Remove the book from position $ j $ at shelf $ i $ if there is a book at it.
- $ 3 $ $ i $ — Invert book placing at shelf $ i $ . This means that from every position at shelf $ i $ which has a book at it, the book should be removed, and at every position at shelf $ i $ which has not book at it, a book should be placed.
- $ 4 $ $ k $ — Return the books in the bookcase in a state they were after applying $ k $ -th operation. In particular, $ k=0 $ means that the bookcase should be in initial state, thus every book in the bookcase should be removed from its position.

After applying each of operation Alina is interested in the number of books in the bookcase. Alina got 'A' in the school and had no problem finding this values. Will you do so?

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF707D/43cb8952ee4fc8994bedde8168b22c25f3bba0de.png)This image illustrates the second sample case.

## 样例 #1

### 输入

```
2 3 3
1 1 1
3 2
4 0
```

### 输出

```
1
4
0
```

## 样例 #2

### 输入

```
4 2 6
3 2
2 2 2
3 3
3 2
2 2 2
3 2
```

### 输出

```
2
1
3
3
2
4
```

## 样例 #3

### 输入

```
2 2 2
3 2
2 2 1
```

### 输出

```
2
1
```

# 题解

## 作者：wurzang (赞：7)

模拟赛上出了这题然后细节写萎了70分没了就写个题解纪念一下哈哈哈哈


首先考虑没有 $4$ 操作怎么做。

先考虑最难的 $3$ 操作。可以直接用一个 $rev$ 标记来表示当前行是否被反转。至于对答案的影响可以用一个 $s$ 数组来维护，其中 $s$ 数组表示当前行中 $1$ 的个数。

其次就是 $1$ 操作与 $2$ 操作，可以直接开一个二维数组 $vis$ 来维护。


虽然想起来很简单但细节贼多，写萎一个 70 分就没有了。

代码如下：

```cpp
	if(opt[x]==1){
		if(vis[X[i]][Y[i]]==rev[X[i]]) tmp=1,++sum,++s[X[i]],vis[X[i]][Y[i]]=!rev[X[i]];
	}
	if(opt[x]==2){
		if(vis[X[i]][Y[i]]!=rev[X[i]]) tmp=1,--sum,--s[X[i]],vis[X[i]][Y[i]]=rev[X[i]];
	}
	if(opt[x]==3){
		sum+=m-s[X[i]]-s[X[i]]; rev[X[i]]^=1; s[X[i]]=m-s[X[i]];
	}
```

如果有 $4$ 操作怎么办？


发现每一个操作都由上一个操作继承而来，除了 $4$ 操作是直接继承另一个操作。然后就可以考虑在操作与操作之间连边，然后离线用 dfs 去做。


做好一个操作的答案后别忘记回溯，回溯的细节也贼多写萎一个 60 分就没有了


代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300000+5;
bool vis[10005][10005],rev[10005];
struct edge{
	int nxt,to;
}e[N];
int head[N],cnt;
void add(int x,int y){
	e[++cnt].to=y; e[cnt].nxt=head[x]; head[x]=cnt;
}
int opt[N],X[N],Y[N],s[N],m;
long long ans[N];
void dfs(int x,int sum){
	int tmp=0,i=x;
	if(opt[x]==1){
		if(vis[X[i]][Y[i]]==rev[X[i]]) tmp=1,++sum,++s[X[i]],vis[X[i]][Y[i]]=!rev[X[i]];
	}
	if(opt[x]==2){
		if(vis[X[i]][Y[i]]!=rev[X[i]]) tmp=1,--sum,--s[X[i]],vis[X[i]][Y[i]]=rev[X[i]];
	}
	if(opt[x]==3){
		sum+=m-s[X[i]]-s[X[i]]; rev[X[i]]^=1; s[X[i]]=m-s[X[i]];
	}
	ans[x]=sum;
	for(int i=head[x];i;i=e[i].nxt)
		dfs(e[i].to,sum);
	i=x;
	if(opt[x]==1&&tmp){
		--sum;--s[X[i]];vis[X[i]][Y[i]]=rev[X[i]];
	}
	if(opt[x]==2&&tmp){
		++sum;++s[X[i]];vis[X[i]][Y[i]]=!rev[X[i]];
	}
	if(opt[x]==3){
		sum-=m-s[X[i]]-s[X[i]]; rev[X[i]]^=1; s[X[i]]=m-s[X[i]];
	}
}
int main(){
//	freopen("draw.in","r",stdin);
//	freopen("draw.out","w",stdout);
	int n,q;
	cin>>n>>m>>q;
	for(int i=1;i<=q;++i){
		cin>>opt[i]>>X[i];
		if(opt[i]<3) cin>>Y[i];
		if(opt[i]==4) add(X[i],i);
		else add(i-1,i);
	}
	dfs(0,0);
	for(int i=1;i<=q;++i)
		cout<<ans[i]<<endl;
	return 0;
}
```




---

## 作者：Z1qqurat (赞：6)

bitset 的 flip 函数不要乱用。

首先如果没有操作 $4$ 可以直接 bitset 解决，但是有操作 $4$。考虑将操作按照顺序建边，建成一颗树，操作 $4$ 则由之前的状态向询问的状态编号建边，其余的直接由 $i - 1$ 操作向 $i$ 操作建边。其中的过程可以用 bitset 维护。

然后其中有一个翻转的操作，看样子直接用 bitset 的 flip 函数就可以解决，但是其实不行。假设你的 bitset 开的是长度为 $1000$，但是你实际只用了 $5$ 位，如果进行操作 $3$ 中的翻转操作就是只会处理这用到的 $5$ 位，但是如果用 flip 函数则会将整个 $1000$ 位全部翻转，在后来统计答案时用 count 函数就会出错，所以不能这么做，直接给 bitset 异或上一个 $m$ 位都是 $1$ 的数即可。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1005, Q = 1e5 + 5;
int n, m, q, sna[Q];
bool vis[Q];
struct Qr {
    int opt, x, y;
}qr[Q];
vector <int> G[Q];
bitset <N> a[N], All;

void dfs(int u, int ans) {
    //vis[u] = 1;
    int opt = qr[u].opt, x = qr[u].x, y = qr[u].y;
    bitset <N> tmp; int pre;
    if(opt == 1) {
        pre = a[x][y];
        if(!pre) ans++;
        a[x][y] = 1;
    }
    if(opt == 2) {
        pre = a[x][y];
        if(pre) ans--;
        a[x][y] = 0;
    }
    if(opt == 3) {
        tmp = a[x];
        ans += m - 2 * a[x].count();
        a[x] ^= All;
    }
    sna[u] = ans;
    for (int v : G[u]) {
        //if(vis[v]) continue;
        dfs(v, ans);
    }
    if(opt <= 2) a[x][y] = pre;
    if(opt == 3) a[x] = tmp;
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; ++i) All.set(i);
    for (int i = 1; i <= q; ++i) {
        scanf("%d%d", &qr[i].opt, &qr[i].x);
        if(qr[i].opt <= 2) scanf("%d", &qr[i].y);
        if(qr[i].opt == 4) G[qr[i].x].emplace_back(i);
        else G[i - 1].emplace_back(i);
    }
    // for (int i = 0; i <= n; ++i) {
    //     for (int j : G[i]) cout << i << ' ' << j << "\n";
    // }
    dfs(0, 0);
    for (int i = 1; i <= q; ++i) printf("%d\n", sna[i]);
    return 0;
}
```

---

## 作者：littleseven (赞：5)

# CF 707D Persistent Bookcase

**题目链接：**[洛谷 CF 707D Persistent Bookcase](https://www.luogu.org/problem/CF707D)		[CF 707D Persistent Bookcase](https://codeforces.com/problemset/problem/707/D)

**算法标签:**  `操作树`、`深搜`

## 题目描述：

维护一个二维零一矩阵（$n,m \le 1000$），支持四种操作（不超过 $10^5$ 次）:

- 将 $(i,j)$ 置一

- 将 $(i,j)$ 置零

- 将第 $i$ 行零一反转

- 回到第 $K$ 次操作前的状态

  每次操作后输出全局一共有多少个一

## 题解：

**操作树**（其实写完我也不知道这是啥）

首先我们看看这四个操作：

- A   修改
- B   修改
- C   修改
- D   **恢复**

所以是不是可以看出来这道题毒瘤的是啥了嘛？？？？        —— D操作啊！！！！！

这时候就需要**操作树**，大致就是按照操作来操作出一棵操作树，之后在操作树上操作各种操作，之后记录每次操作操作后的答案。 [滑稽.jpg]  【其实这么说我也看不懂】

额……额……额……额……额……    好了好了说正事。

对于前三种情况，由于我们只是在这次进行修改，显然当前操作之后就是下一个操作，所以我们就在**当前操作**和**下一操作**之间连一条边。

对于第四种情况，我们需要得到第$k$次操作的状态，所以我们就需要在第$k$次操作时候直接得出当前操作的答案，也就是需要在**当前操作**和**第**$k$**次操作**之间连一条边，这样构成了一棵操作树（其实根本不是像上边那么晕）。

之后我们**DFS**这棵树，对每一个点进行该点的操作，之后直接走他的边，得出它的子节点的答案，回溯。最终我们可以得到所有点的答案。

由于**时空问题（踏马乐 TMLE）**开$bitset$这个~~好用且备受喜爱~~的东西来存状态。

P.S.如果还是不懂看代码注释鸭！！！

## AC代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define setI(x) freopen(x".in", "r", stdin); 
#define setO(x) freopen(x".out", "w", stdout); 
#define setIO(x) setI(x) setO(x)

typedef long long ll;

//quick_read

char *p1, *p2, buf[100000];

#define nc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1 ++ ) 

int rd() {
	int x = 0, f = 1;
	char c = nc();
	while (c < 48) {
		if (c == '-') {
			f = -1;
		}
		c = nc();
	}
	while (c > 47) { 
		x = (((x << 2) + x) << 1) + (c ^ 48);
		c = nc();
	}
	return x * f;
}

// quick_read over

const int N = 1010;

const int M = 1e5 + 10;

int n, m, q, tot;

int ans[M], opt[M], x[M], y[M];

bitset <N> all, mp[N];

// all 表示全1状态，用于取反
// mp[N]  存放状态

vector <int> edge[M];

// 存放树边

void dfs(int pos) {
	bool flag = 0;  // 这个点需不需要回溯
	if (opt[pos] == 1 && mp[x[pos]][y[pos]] == 0) { // 操作A
		flag = 1;
		tot ++ ;
		mp[x[pos]][y[pos]] = 1;
	}
	else if (opt[pos] == 2 && mp[x[pos]][y[pos]] == 1) {  // 操作B
		flag = 1;
		tot -- ;
		mp[x[pos]][y[pos]] = 0;
	}
	else if (opt[pos] == 3) {  // 操作C
		flag = 1;
		tot -= mp[x[pos]].count();  // 减去当前1的个数
		mp[x[pos]] ^= all;  // 取反
		tot += mp[x[pos]].count();  // 加上取反后1的个数
	}
	ans[pos] = tot;  // 记录答案
	for (int i = 0; i < (int)edge[pos].size(); i ++ ) {
		dfs(edge[pos][i]);  // 爬子节点
	}
	if (flag) {  // 回溯
		if (opt[pos] == 1) {
			tot -- ;
			mp[x[pos]][y[pos]] = 0;
		}
		else if (opt[pos] == 2) {
			tot ++ ;
			mp[x[pos]][y[pos]] = 1;
		}
		else if (opt[pos] == 3) {
			tot -= mp[x[pos]].count();
			mp[x[pos]] ^= all;
			tot += mp[x[pos]].count();
		}
	}
}

int main() {
	// setIO("now");

	n = rd(), m = rd(), q = rd();
	for (int i = 1; i <= m; i ++ ) {
		all.set(i);
		// 现学bitset，表示把i+1位置成1
	}
	memset(ans, -1, sizeof ans);
	for (int i = 1; i <= q; i ++ ) {
		opt[i] = rd(); // 操作种类
		x[i] = rd();  // 操作第一关键字
		if (opt[i] == 4) {
			edge[x[i]].push_back(i);  // 恢复 建边
		}
		else {
			if (opt[i] < 3) {
				y[i] = rd(); // 操作第二关键字
			} 
		}
		if (opt[i] < 4) {
			edge[i - 1].push_back(i);  // 修改 建边
		}
	}
	dfs(0);  // 爬树
	for (int i = 1; i <= q; i ++ ) {
		printf("%d\n", ans[i]);
	}
	return 0;

}
```



---

## 作者：hgckythgcfhk (赞：3)

看到回到第 $K$ 次操作，想到可持久化，而且是一个非常难写的可持久化，于是不想写了，但仔细想想这个可持久化为什么难写？因为二维本身需要主席树，自带可持久化，可持久化套可持久化好像不太能做，于是开始乱搞，回到历史版本这个操作除了可持久化最先想到离线，发现每次操作都只有一个后继状态，最后一次操作没有后继状态，可以建树，回到历史版本相当于跳到某个节点，到这一步基本上已经快做出来了，但由于本人太菜想到了很多歪路，比如存下一部分状态然后卡常 + 根号分治，由于实在想不出来存哪些节点的状态于是放弃，但这个过程不是没有意义的，这个过程通过想卡常想到了前三个操作的处理方式。

首先暴力维护 ```bitset``` 肯定是能过的，但对于上面那种非常暴力的乱搞肯定别想了，发现操作不能 $O(1)$ 主要是操作 $3$ 不干好事，如果我通过懒标记来维护那会使前两个操作必须暴力检查或者加一堆判断常数很大，但是这里懒标记给了我们一个很大的提示，既然不好检查，那就干脆把反转前后的状态同时维护下来，然后用懒标记表示现在是反转前还是反转后，但这样似乎增加了存状态的开销，于是不会做了，打开题解一眼看到程序普遍很短，突然想到这个树上的过程可以 ```dfs``` 维护，然后就做出来了。

几个要注意的点，一个节点不一定代表一次操作，但一次操作只对应一个节点，且每个节点上的操作的答案一样，所以我们要建立操作到节点的映射，而不是节点对应的操作的编号，当然可以维护边所对应的编号，但是边的性质不如节点好处理，不建议这么写。

为防止因火车头导致被打回，省略了宏定义和头文件，但不影响阅读。~~话说这样也有一定的防止 ctj 的作用吧。~~
```
Bool(a[2][N],1024),b;unsigned ans[N],id,d[N],now,n,m,cnt[N];
struct A{unsigned op,i,j;}c[N];struct B{unsigned v,w;};vector<B>e[N];
void dfs(cit u){ans[u]=now;for(const B&i:e[u]){cit v=i.v;A op=c[i.w];
	cit x=op.i,y=op.j;switch(op.op){
		case 1:{rg const bool t=a[b[x]][x][y];
			if(!t)a[b[x]][x][y]=1,a[b[x]^1][x][y]=0,++now,++cnt[x];
			dfs(v);
			if(!t)a[b[x]][x][y]=0,a[b[x]^1][x][y]=1,--now,--cnt[x];break;
		}case 2:{rg const bool t=a[b[x]][x][y];
			if( t)a[b[x]][x][y]=0,a[b[x]^1][x][y]=1,--now,--cnt[x];
			dfs(v);
			if( t)a[b[x]][x][y]=1,a[b[x]^1][x][y]=0,++now,++cnt[x];break;
		}case 3:{
			b.flip(x);now-=cnt[x],cnt[x]=m-cnt[x];now+=cnt[x];
			dfs(v);
			b.flip(x);now-=cnt[x],cnt[x]=m-cnt[x];now+=cnt[x];break;
		}}}}
signed main(){open;int q;cin>>n>>m>>q;
	for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)a[1][i][j]=1;
	for(int _=1,u=0;_<=q;++_){int op,i,j;cin>>op;
		if(op<=2)cin>>i>>j,c[_]={op,i,j},e[u]+={++id,_},u=id;
		if(op==3)cin>>i,c[_]={3,i},e[u]+={++id,_},u=id;
		if(op==4)cin>>u,u=d[u];d[_]=u;
	}dfs(0);for(int i=1;i<=q;++i)cout<<ans[d[i]]<<"\n";
}
```

---

## 作者：Swirl (赞：2)

我有一计：操作树 + bitset。

---

看到访问历史版本，第一个应该想到操作树，不要跟我提可持久化。

考虑到矩阵只有 $0$ 或 $1$，我们可以用若干个 bitset 来维护 $01$ 矩阵的操作。

这道题就变得非常~~有灵性~~简单了。

先离线把操作树建出来，然后 dfs 扫一遍整棵树，维护每个时刻的数据结构信息，然后对于在这个结点（版本）上的所有询问记录答案。

最后输出即可。

---

遇到操作树出 bug 可以把 $\text{ver, fa}$ 数组输出一下然后画张图模拟一下对不对，之后就能对号入座看哪里出了问题。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
#define FRE(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)
#define ALL(x) x.begin(), x.end()
using namespace std;

inline void cmax(int& x, int c) {
    x = max(x, c);
}
inline void cmin(int& x, int c) {
    x = min(x, c);
}

int _test_ = 1;

const int N = 1e5 + 6, M = 1e3 + 5;

struct edge {
    int u, v;
    int x;
};

int n, m, k, tot, ans, ver[N], fa[N], ret[N];
edge fav[N];
vector<int> g[N];
bitset<M> A[M], lim;
vector<int> q[N];

void dfs(int u, int fa) {
    for (int id : q[u]) {
        ret[id] = ans;
    }
    for (int x : g[u]) {
        if (x == fa)
            continue;
        int X = fav[x].u, Y = fav[x].v;
        bool t = 0;
        int mm = ans;
        if (fav[x].v == -1) {
            int ct = A[X].count();
            ans += -ct + m - ct;
            A[X] ^= lim;
        } else {
            ans -= A[X][Y] - fav[x].x;
            t = A[X][Y];
            A[X][Y] = fav[x].x;
        }
        dfs(x, u);
        if (fav[x].v == -1) {
            ans = mm;
            A[X] ^= lim;
        } else {
            ans = mm;
            A[X][Y] = t;
        }
    }
}

void init() {}

void clear() {}

void solve() {
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++)
        lim.set(i);
    ver[0] = tot = 1;
    for (int i = 1; i <= k; i++) {
        int op;
        cin >> op;
        if (op <= 2) {
            int x, y;
            cin >> x >> y;
            ver[i] = ++tot;
            fa[ver[i]] = ver[i - 1];
            fav[ver[i]] = {x, y, 2 - op};
            g[ver[i]].push_back(ver[i - 1]);
            g[ver[i - 1]].push_back(ver[i]);
        }
        if (op == 3) {
            int x;
            cin >> x;
            ver[i] = ++tot;
            fa[ver[i]] = ver[i - 1];
            fav[ver[i]] = {x, -1, 0};
            g[ver[i]].push_back(ver[i - 1]);
            g[ver[i - 1]].push_back(ver[i]);
        }
        if (op == 4) {
            int k;
            cin >> k;
            ver[i] = ver[k];
        }
        q[ver[i]].push_back(i);
    }
    dfs(1, 0);
    for (int i = 1; i <= k; i++)
        cout << ret[i] << "\n";
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    //	cin >> _test_;
    init();
    while (_test_--) {
        clear();
        solve();
    }
    return 0;
}
```

---

## 作者：MarSer020 (赞：2)

大家好，我很喜欢主席树，所以我用主席树过了这个题。

~~什么？操作树？那是什么（~~

$\Large\text{Solution}$

首先一眼可以用主席树解决。

然后你码了个板子，对于每个节点维护 $[l,r]$ 行的 $1$ 的个数。

这时候发现好像对于每个版本都要维护当前盘面状况，由于我懒，我选择开在线段树的节点上面。

写完之后一看：开 $3\times 10^6$ 个节点，每个节点记录 $10^3$ 个位置，空间炸飞。

然而有我们最好的 `bitset`，把数组换成 `bitset`，算一下，神奇的卡进去了（

于是就用主席树过了。~~甚至可以强制在线（~~

$\Large\text{Code}$

```cpp
#include<bits/stdc++.h>
#define ls t[cur].lc
#define rs t[cur].rc
#define mid ((l+r)>>1)
using namespace std;
int n,rt[100005],tot=1,m,q,op,x,y;
struct node{
	int val,lc,rc;
	bool tag;
	bitset<1005>a;
}t[3000005];
int clone(int k){
	t[++tot]=t[k];
	return tot;
}
int update(int cur,int l,int r,int x,int y,bool val){
	cur=clone(cur);
	if(l==r){
		bool tmp=t[cur].a[y]^t[cur].tag;
		if(tmp&&!val)
			t[cur].val--;
		if(!tmp&&val)
			t[cur].val++;
		t[cur].a[y]=val^t[cur].tag;
		return cur;
	}
	if(x<=mid)
		t[cur].lc=update(ls,l,mid,x,y,val);
	else
		t[cur].rc=update(rs,mid+1,r,x,y,val);
	t[cur].val=t[ls].val+t[rs].val;
	return cur;
}
int update2(int cur,int l,int r,int x){
	cur=clone(cur);
	if(l==r){
		t[cur].val=m-t[cur].val,t[cur].tag^=1;
		return cur;
	}
	if(x<=mid)
		t[cur].lc=update2(ls,l,mid,x);
	else
		t[cur].rc=update2(rs,mid+1,r,x);
	t[cur].val=t[ls].val+t[rs].val;
	return cur;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>n>>m>>q,rt[0]=1;
	for(int i=1;i<=q;i++){
		cin>>op>>x;
		if(op==1)
			cin>>y,rt[i]=update(rt[i-1],1,n,x,y,1);
		else if(op==2)
			cin>>y,rt[i]=update(rt[i-1],1,n,x,y,0);
		else if(op==3)
			rt[i]=update2(rt[i-1],1,n,x);
		else
			rt[i]=rt[x];
		cout<<t[rt[i]].val<<'\n';
	}
	return 0;
}
```

空间大概 400M 左右，反正能过，如果开一半空间就过不了了。

---

## 作者：Zimse (赞：2)

先考虑没有四操作的情况:

维护一个矩阵 A

每一行的反转情况数组 B

每一行 $1$ 的数量数组 C

每一个位置的数字是 $A_{i,j} xor B_i$

对于前两种情况,先判断操作是否有效,如果有效直接将 $A_{i,j}$ 取反。

对于第三种操作,对 $B_i$ 取反,然后 $C_i=m-C_i$

维护当前矩阵中 $1$ 的数量。

------------

如果加上了四操作呢,显然不可以维护每个操作后的情况。

应为没有强制在线,可以离线维护每次操作,发现操作可以构造出一种树的结构。

那么只需要深搜一遍这颗树,离线处理出每个操作后的结果,往上走的时候回溯一下,再输出每个操作后的答案即可。

------------

Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

#define ll long long

using namespace std;

int read(){
	int __x=0,__y=1;char __c=' ';
	while(__c<'0'||__c>'9'){__c=getchar();if(__c=='-'){__y=-1,__c=getchar();break;}}
	while(__c>='0'&&__c<='9')__x=__x*10+__c-'0',__c=getchar();
	return __x*__y;}

const int N=2e3+7,M=1e5+7,Mod=998244353,INF=1e9+7;
int n,m,q,a[N][N],b[N],c[N],ans;
vector<int> ch[M];

struct opt{
	int ty,i,j,ans;
	opt(int ty=0,int i=0,int j=0):ty(ty),i(i),j(j){}
}op[M];

void dfs(int u){
	int ty=op[u].ty,x=op[u].i,y=op[u].j,c1=0,c2=0;
	if(ty==1)if((a[x][y]^b[x])==0)a[x][y]^=1,++ans,++c[x],c1=1;
	if(ty==2)if((a[x][y]^b[x])==1)a[x][y]^=1,--ans,--c[x],c2=1;
	if(ty==3)b[x]^=1,ans+=m-c[x]*2,c[x]=m-c[x];
	op[u].ans=ans;
	
	for(int i=0;i<int(ch[u].size());i++)dfs(ch[u][i]);
	
	if(ty==2&&c2)a[x][y]^=1,++ans,++c[x];
	if(ty==1&&c1)a[x][y]^=1,--ans,--c[x];
	if(ty==3)b[x]^=1,ans+=m-c[x]*2,c[x]=m-c[x];
	return;
}

int main(){
	n=read(),m=read(),q=read();
	
	for(int i=1,ty,x,y;i<=q;i++){
		ty=read(),x=read(),y=0;
		if(ty==4){
			op[i]=opt(4,0,0);
			ch[x].push_back(i);
		}
		else{
			if(ty<3)y=read();
			op[i]=opt(ty,x,y);
			ch[i-1].push_back(i);
		}
	}
	dfs(0);
	for(int i=1;i<=q;i++)printf("%d\n",op[i].ans);
	return 0;
}
```


---

## 作者：MuYC (赞：2)


[$MYCui's$ $blog$](https://www.cnblogs.com/MYCui/p/13997956.html)

#### 题意搬运：

维护一个二维零一矩阵（$n,m<=1000$），支持四种操作（不超过$10^5$次）:

+ 将$(i,j)$置一
+ 将$(i,j)$置零
+ 将第i行$01$反转
+ 回到第$K$次操作后的状态$(K$可以为$0)$
+ 每次操作后输出全局一共有多少个$1$

#### 思路

emmmm,感觉很像某种可持久化数据结构，但是蒟蒻实在想不出来该用啥。

But，操作树可以很轻松的解决这个问题。

**这个问题没有强制在线**

对于一个操作$i$我们发现倘若它不是第四种操作，它可以从自己的上一个操作转移来。

因为你是沿用的上一次操作的状态来对当前状态做出修改。

我们实际上要运用上一次修改后的状态进行修改。

那么对于非操作4的操作，我们想到建一条边$i-1,i$，表示操作$i-1$的状态可以转移到操作$i$，也就是操作$i$仍然需要它的状态。

实际上对于操作$4$也是一样的，我们连一条边$K,i$，不需要连$i-1,i$，这样即可。因为操作4只需要知道第$K$次操作后的状态，于是我们用操作$K$的状态来转移。

我们来模拟一下建树的过程：

先是状态0，全部都是0，没有修改之前。

![](https://cdn.luogu.com.cn/upload/image_hosting/dbnljbng.png)

然后有了操作1,它沿用的操作0的状态（即初始状态）

![](https://cdn.luogu.com.cn/upload/image_hosting/6kqthupf.png)

接着有了操作二，它需要沿用操作$1$的状态

![](https://cdn.luogu.com.cn/upload/image_hosting/edtqx4or.png)

再是操作三,它沿用操作２的状态:

![](https://cdn.luogu.com.cn/upload/image_hosting/wl2u3uio.png)

后来是操作４，注意，它属于操作类型４，它需要访问第１次修改后的状态，于是将操作４连到操作１下面:

![](https://cdn.luogu.com.cn/upload/image_hosting/hdre90le.png)

然后又来了一个操作５，这个操作应该沿用操作４的状态，于是连到操作４的下面。

![](https://cdn.luogu.com.cn/upload/image_hosting/br79a6zl.png)

最后是操作６，注意，它属于操作类型４，它需要沿用操作３的状态，于是将操作６连到操作３的下面

![](https://cdn.luogu.com.cn/upload/image_hosting/hzzs60se.png)

然后就建树完成了！(这是最核心的一部分)

怎么获得答案？对这棵树进行$DFS$，对于操作１，２，３就暴力修改，用$bitset$即可，然后对于操作４我们不需要修改，直接沿用前面的状态即可。

遍历完后记得回溯，具体看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005,MAXM = 1005;
bitset <MAXM> All,P[MAXM];//All全部为１，便于对一整行取反

int n , m , Q;
int start[MAXN],cnt = 0;
int Ans[MAXN];

struct Node {
	int op,x,y,id;
} T[MAXN];

struct Edge {
	int next,to;
} edge[MAXN];

void add(int from,int to)
{
	cnt ++;
	edge[cnt].to = to;
	edge[cnt].next = start[from];
	start[from] = cnt;
	return ;
}

void DFS(int x,int from,int Now)//x表示当前节点，from表示当前节点的父亲节点，Now表示的是当前状态的答案
{
	bool q = 0;
	if(T[x].op == 1)
	{
		q = P[T[x].x][T[x].y];
		if(P[T[x].x][T[x].y] == 0)Now ++;//更新答案
		P[T[x].x][T[x].y] = 1;//直接修改
	}
	if(T[x].op == 2)
	{
		q = P[T[x].x][T[x].y];
		if(P[T[x].x][T[x].y] == 1)Now --;//更新答案
		P[T[x].x][T[x].y] = 0;
	}
	if(T[x].op == 3)
	{
		int A = P[T[x].x].count();//原来有多少个１
		P[T[x].x] ^= All;//暴力修改
		Now += P[T[x].x].count() - A;//统计现在的１的个数减去原来１的个数即是答案
	}
      //对于操作４不需要做出修改，直接沿用上次操作的答案即可
	Ans[T[x].id] = Now;//将答案塞进答案序列
	for(int i = start[x] ; i ; i = edge[i].next)
	{
		int to = edge[i].to;
		if(to != from)DFS(to,x,Now);//遍历
	}
	if(T[x].op <= 2)P[T[x].x][T[x].y] = q;//状态回溯
	if(T[x].op == 3)P[T[x].x] ^= All;//状态回溯
	return ;
}

inline int read()
{
	int x = 0, flag = 1;
	char ch = getchar();
	for( ; ch > '9' || ch < '0' ; ch = getchar())if(ch == '-')flag = -1;
	for( ; ch >= '0' && ch <= '9' ; ch = getchar())x = (x << 3) + (x << 1) + ch - '0';
	return x * flag;
}

int main()
{
	n = read() , m = read() ,Q = read();
	for(int i = 1 ; i <= m ; i ++)All[i] = 1;
	for(int i = 1 ; i <= n ; i ++)P[i].reset();//全部置0
	T[0].x = T[0].y = 0;
	for(int i = 1 ; i <= Q ; i ++)
	{
		T[i].op = read();T[i].id = i;//离线操作的常用套路，记录它的第几个询问
		if(T[i].op <= 2)T[i].x = read(),T[i].y = read();
		else T[i].x = read();
		if(T[i].op <= 3)add(i - 1 , i);//如果不属于操作４就连边i-1 to i
		else add(T[i].x,i);//如果属于操作４就连边K to i
	}
	DFS(0,0,0);//注意要从0开始遍历，因为K可以等于0！
	for(int i = 1 ; i <= Q ; i ++)cout << Ans[i] << endl;//输出答案即可
	return 0;
}
```

---

## 作者：伊地知虹夏 (赞：2)

> 可以离线的版本操作都是假的可持久化 —— 鲁迅

考虑前 $3$ 个操作用 `bitset` 处理都是简单的，具体的：

1. `a[i].set(j)`
2. `a[i].set(j,0)`
3. `a[i] ^= f` (`f` 为一个 $[1,m]$ 都是 $1$ 的 `bitset`)

这些操作显然是可撤销的，继续考虑操作 $4$，我们发现如果保证 $k_p \ge k_{p+1}$ 的话，我们可以用栈来存储操作，然后一个个撤销。

我们发现这个栈的本质就是在链上走和回退，链对于我们来说没有任何特殊性，所以考虑将这个版本操作的关系建成一棵树，然后使用 `dfs` 求解答案。

实际上这就是所谓的操作树，这样我们就在 $\Theta(\dfrac{n^2}{w})$ 内解决了本题，建议配合[代码](https://www.luogu.com.cn/paste/3jj142xq)食用。

---

## 作者：youdu666 (赞：1)

怎么题解区基本都是离线做法。

分享一个二维主席树的做法。

听上去非常高大上且写起来会很答辩，其实不然，因为每次只会操作一行，故外层只需使用单点修改的主席树，在找到目标位置后，对于前两个操作同样是单点修改，而对于第三个操作，可以进行打标记。这里要注意一下，由于主席树的特性，不能进行标记下传，应当进行标记永久化，然后就结束了，几乎没有思维含量，适合我这种躺平人士使用。~~结果确实有点答辩……~~

AC 链接：

[https://codeforces.com/contest/707/submission/216535589](https://codeforces.com/contest/707/submission/216535589)

---

## 作者：傅思维666 (赞：1)


## 题解：

~~2019.10.22模拟赛T2 50分场感谢出题人@zcs0724~~

PS：洛谷题目翻译有锅，操作1是将$(i,j)$置$1$，操作2是将$(i,j)$置$0$。如果不看$CF$原题的小伙伴肯定会在这里挂掉，请求管理修改。

考场上一看，操作$1,2,3$都会，但是操作$4$毫无思路。所以这题挂了，还好出题人良心，有$50\%$的数据只有操作$1,2,3$，所以让蒟蒻侥幸骗得$50pts$。

这道题的难点就是操作4的处理。对于操作4，我们发现是对其历史的一个回溯，那么就想到了做法1：可持久化数据结构。

但是蒟蒻并不会可持久化数据结构，所以只学了解法2：**离线+操作树**。

一开始操作树这么高端的名词把蒟蒻搞蒙了。（难道，这是比可持久化树套树更难的知识点？瑟瑟发抖）但是后来仔细地揣摩一下思路，发现就是把先离线，输入进来所有询问，然后把操作建成一棵树，在树上进行处理（本题是深搜）的过程。

为什么这么做是对的呢？因为我们的操作4回溯到的是一个操作和其对应的状态。那么，用一个树状的数据结构来存操作次数显然是满足要求的，就拿样例1来举例：

![](https://img2018.cnblogs.com/blog/1738131/201910/1738131-20191022190518284-1911154179.png)

当我们好好地进行1、2操作的时候，第三次操作4回到了操作0（即没有任何操作的情况） ，所以我们依据题意建立了这样一个操作树。

为什么我们在树上进行深搜对答案没有影响、能维护答案的正确性呢？这是深搜的性质决定的。学过深搜的小伙伴知道深搜有"搜索"和“还原现场”两大核心操作。搜索能帮我们得出每一个操作的答案，而还原现场就能保证这些答案互不影响。那么我们离线处理询问构建了这个操作树，这个树上的每个操作只会是操作1、操作2、操作3（操作4就是建这棵树）。那么我们就可以依据题意进行模拟了。

当然，在这里还为大家介绍简洁地解决这个题模拟部分的一个技巧：$bitset$容器。这是一种能够方便地处理01串操作类型题的$STL$大法。本蒟蒻也是用这个东西完成的对操作1、2、3的模拟。如果对$bitset$不太熟悉的小伙伴请移步本蒟蒻的这篇博客：

[浅谈C++bitset容器](https://www.cnblogs.com/fusiwei/p/11720118.html)



代码如下：

```cpp
#include<cstdio>
#include<bitset>
using namespace std;
const int maxn=1010;
const int maxq=1e5+10;
int n,m,q;
int ans[maxq],opt[maxq],x[maxq],y[maxq],cnt;
bitset<maxn> map[maxn],all_one;
int tot,head[maxq],nxt[maxq],to[maxq];
void add(int x,int y)
{
    to[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}
void dfs(int pos)
{
    bool flag=0;
    if(opt[pos]==1 && map[x[pos]][y[pos]]==0)
    {
        flag=1;
        map[x[pos]][y[pos]]=1;
        cnt++;
    }
    if(opt[pos]==2 && map[x[pos]][y[pos]]==1)
    {
        flag=1;
        map[x[pos]][y[pos]]=0;
        cnt--;
    }
    if(opt[pos]==3)
    {
        flag=1;
        cnt-=map[x[pos]].count();
        map[x[pos]]^=all_one;
        cnt+=map[x[pos]].count();
    }
    ans[pos]=cnt;
    for(int i=head[pos];i;i=nxt[i])
        dfs(to[i]);
    if(flag)//flag就是还原现场的操作，如果某一个节点是操作4，那么直接继续就可以
    {
        if(opt[pos]==1)
            cnt--,map[x[pos]][y[pos]]=0;
        if(opt[pos]==2)
            cnt++,map[x[pos]][y[pos]]=1;
        if(opt[pos]==3)
        {
            cnt-=map[x[pos]].count();
            map[x[pos]]^=all_one;
            cnt+=map[x[pos]].count();//数1，取反，统计答案
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++)
        all_one.set(i);//构造一个全1的数列，为操作三所用
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d",&opt[i],&x[i]);
        if(opt[i]==4)
            add(x[i],i);
        else 
            if(opt[i]<3)
                scanf("%d",&y[i]);
        if(opt[i]<4)
            add(i-1,i);
    }
    dfs(0);
    for(int i=1;i<=q;i++)
        printf("%d\n",ans[i]);
    return 0;
}
```



---

## 作者：_Kenma_ (赞：0)

# CF707D 解题报告

## 思路分析

因为是可持久化题，还没有强制在线，那么考虑离线处理。

平凡地，将每次操作视为一个版本，离线建出版本树，在版本树上 dfs 即可。

发现要求支持的三个操作都可以直接 bitset 维护，并且支持撤销。

做完了。

总体复杂度 $O(\frac{mq}{w})$。

为什么 CF 评分高？感觉还是老外不会 ds。

## 代码实现

```cpp

#include<bits/stdc++.h>
using namespace std;
int n,m,q,op[100005],x[100005],y[100005],out[100005],ans;
int head[100005],nxt[200005],target[200005],tot;
void add(int x,int y){
	tot++;
	nxt[tot]=head[x];
	head[x]=tot;
	target[tot]=y;
}
bitset<1005> f[1005],all;
void dfs(int u){
	bool flag=false;
	if(op[u]==1){
		flag=f[x[u]][y[u]];
		ans-=f[x[u]].count(); 
		f[x[u]].set(y[u],true);
		ans+=f[x[u]].count();
	}else if(op[u]==2){
		flag=f[x[u]][y[u]];
		ans-=f[x[u]].count();
		f[x[u]].set(y[u],false);
		ans+=f[x[u]].count();
	}else if(op[u]==3){
		ans-=f[x[u]].count();
		f[x[u]]^=all;
		ans+=f[x[u]].count();
	}
	out[u]=ans;
	for(int i=head[u];i;i=nxt[i]){
		int v=target[i];
		dfs(v);
	}
	if(op[u]==1){
		ans-=f[x[u]].count(); 
		f[x[u]].set(y[u],flag);
		ans+=f[x[u]].count();
	}else if(op[u]==2){
		ans-=f[x[u]].count();
		f[x[u]].set(y[u],flag);
		ans+=f[x[u]].count();
	}else if(op[u]==3){
		ans-=f[x[u]].count();
		f[x[u]]^=all;
		ans+=f[x[u]].count();
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++){
		cin>>op[i];
		if(op[i]==1 || op[i]==2){
			cin>>x[i]>>y[i];
			add(i-1,i);
		}else if(op[i]==3){
			cin>>x[i];
			add(i-1,i);
		}else{
			cin>>x[i];
			add(x[i],i);
		}
	}
	for(int i=1;i<=m;i++){
		all.set(i);
	}
	dfs(0);
	for(int i=1;i<=q;i++){
		cout<<out[i]<<'\n'; 
	}
	return 0;
}

```

---

## 作者：Hoks (赞：0)

## 前言
简单题，还是能一眼秒的喵，不过有的人挂了好几发。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
首先一眼就看到了恶心的回滚，感觉很不可做。

发现没有强制在线，考虑离线。

直接大力建模，把操作的每个时间作为一个节点连边。

那么节点 $i+1$ 的父亲即为 $i$。

对于回滚操作，假设回滚到 $x$，那么 $i+1$ 的父亲即为 $x$。

建出操作树考虑在树上 dfs 遍历记录答案最后输出即可。

接着考虑怎么实现操作，操作 $1,2$ 直接赋值即可，操作 $3$  暴力遍历翻转即可。

暴力实现即可，但是要记得撤销。

**记得记录 $1,2$ 操作是否真正实行了，不要乱撤销。**
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1010,V=1e5+10,mod=998244353,INF=0x3f3f3f3f3f3f3f3f;
struct query{int op,x,y;}q[V];
int n,m,k,ans,res[V],a[N][N];vector<int>e[V];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void add(int u,int v){e[u].emplace_back(v);}
inline void dfs(int u)
{
    int fl=0;if(q[u].op==1) ans+=!a[q[u].x][q[u].y],fl=!a[q[u].x][q[u].y],a[q[u].x][q[u].y]=1;
    if(q[u].op==2) ans-=a[q[u].x][q[u].y],fl=a[q[u].x][q[u].y],a[q[u].x][q[u].y]=0;
    if(q[u].op==3) for(int i=1;i<=m;i++) ans+=(a[q[u].x][i])?-1:1,a[q[u].x][i]^=1;
    res[u]=ans;for(auto v:e[u]) dfs(v),ans=res[u];
    if(q[u].op==1&&fl) a[q[u].x][q[u].y]=0;if(q[u].op==2&&fl) a[q[u].x][q[u].y]=1;
    if(q[u].op==3) for(int i=1;i<=m;i++) a[q[u].x][i]^=1;
}
signed main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=k;i++)
    {
        q[i].op=read();q[i].x=read();
        if(q[i].op==1||q[i].op==2) q[i].y=read();
        if(q[i].op==4) add(q[i].x,i);
        else add(i-1,i);
    }dfs(0);for(int i=1;i<=k;i++) print(res[i]),put('\n');
    genshin:;flush();return 0;
}
```

---

## 作者：LEE114514 (赞：0)

## 思路

**可以离线的可持久化基本都是假的！**

我们直接建出版本树并 dfs 一遍。具体的，如果 $i$ 号是回溯到 $k$ 号操作，那么从 $k$ 向 $i$ 连边，否则 $i-1$ 向 $i$ 连边。

dfs 进入时执行操作，离开时撤销操作。注意，没有成功执行的操作不需要撤销。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1024;
bitset<maxn> a[maxn];
int sz[maxn];
const int maxm=1e5+5;
struct Edge{
	int to,Next;
}G[maxm];
int cnt,head[maxm];
void add(int u,int v){
	G[++cnt]=Edge{v,head[u]};
	head[u]=cnt;
}
int n,m,q;
struct Qry{
	int op,x,y;
}Q[maxm];
int ans[maxm],res;
void dfs(int u){
	bool flag=0;
	if(Q[u].op==1){
		if(!a[Q[u].x][Q[u].y]) ++res,flag=1,a[Q[u].x].set(Q[u].y),++sz[Q[u].x];
	}else if(Q[u].op==2){
		if(a[Q[u].x][Q[u].y]) --res,flag=1,a[Q[u].x].reset(Q[u].y),--sz[Q[u].x];
	}else if(Q[u].op==3){
		flag=1;
		res-=sz[Q[u].x];
		a[Q[u].x].flip();
		sz[Q[u].x]=m-sz[Q[u].x];
		res+=sz[Q[u].x];
	}
	ans[u]=res;
	for(int i=head[u];i;i=G[i].Next) dfs(G[i].to);
	if(flag){
		if(Q[u].op==1) --res,a[Q[u].x].reset(Q[u].y),--sz[Q[u].x];
		else if(Q[u].op==2) ++res,a[Q[u].x].set(Q[u].y),++sz[Q[u].x];
		else if(Q[u].op==3){
			res-=sz[Q[u].x];
			a[Q[u].x].flip();
			sz[Q[u].x]=m-sz[Q[u].x];
			res+=sz[Q[u].x];
		}
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=q;++i){
		scanf("%d%d",&Q[i].op,&Q[i].x);
		if(Q[i].op<=2) scanf("%d",&Q[i].y);
		if(Q[i].op==4) add(Q[i].x,i);
		else add(i-1,i); 
	}
	dfs(0);
	for(int i=1;i<=q;++i) printf("%d\n",ans[i]);
}
```

---

## 作者：osfly (赞：0)

### some interesting things

![](https://cdn.luogu.com.cn/upload/image_hosting/0lc5wow2.png)

这个故事告诉我们主席树的空间复杂度是 $O($ 能开多大开多大 $)$。

### 正文

看一下题解，啥？二维主席树是啥，不会。操作树是啥？不会。

其实直接上普通的主席树就好了。

每一个节点存一个 `bitset` 表示每一行的每一个格的状态。

然后操作 $1,2$ 直接暴力改，操作 $3$ 直接按位取反，操作 $4$ 直接承接第 $k$ 个版本就好了。

注意到每一行最多才 $1000$ 个，`bitset` 处理一次操作时间复杂度为 $\frac{m}{32}$，算一下才 $30$ 多一点，2s 时间足够了。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int N=1e3+10,M=2e6+10,Q=1e5+10;

int n,m,q;

#define rt(x) tree.RT[x]
struct seg
{
	struct node
	{
		int LS,RS;
		bitset<N> val;
		int sum;
	}t[M];
	#define ls t[k].LS
	#define rs t[k].RS
	#define mid ((l+r)>>1)
	int RT[Q],tot;
	int clone(int k)
	{
		t[++tot]=t[k];
		return tot;
	}
	void pushup(int k)
	{
		t[k].sum=t[ls].sum+t[rs].sum;
	}
	int build(int k,int l,int r)
	{
		k=clone(k);
		if(l==r)
		{
			t[k].val=0,t[k].sum=0;
			return k;
		}
		ls=build(ls,l,mid);
		rs=build(rs,mid+1,r);
		pushup(k);
		return k;
	}
	int update1(int k,int l,int r,int x,int pos,int num)
	{
		k=clone(k);
		if(l==r)
		{
			if(t[k].val[pos]!=num) t[k].val[pos]=num,t[k].sum+=(num==1?1:-1);
			return k;
		}
		if(x<=mid) ls=update1(ls,l,mid,x,pos,num);
		if(x>mid) rs=update1(rs,mid+1,r,x,pos,num);
		pushup(k);
		return k;
	}
	int update2(int k,int l,int r,int x)
	{
		k=clone(k);
		if(l==r)
		{
			t[k].val=~t[k].val;
			t[k].sum=m-t[k].sum;
			return k;
		}
		if(x<=mid) ls=update2(ls,l,mid,x);
		if(x>mid) rs=update2(rs,mid+1,r,x);
		pushup(k);
		return k;
	}
	#undef ls
	#undef rs
	#undef mid
}tree;

int main()
{
	scanf("%d%d%d",&n,&m,&q);
	rt(0)=tree.build(rt(0),1,n);
	for(int s=1;s<=q;s++)
	{
		int op,i,j,k;
		scanf("%d",&op);
		if(op==1) scanf("%d%d",&i,&j),rt(s)=tree.update1(rt(s-1),1,n,i,j,1);
		if(op==2) scanf("%d%d",&i,&j),rt(s)=tree.update1(rt(s-1),1,n,i,j,0);
		if(op==3) scanf("%d",&i),rt(s)=tree.update2(rt(s-1),1,n,i);
		if(op==4) scanf("%d",&k),rt(s)=rt(k);
		printf("%d\n",tree.t[rt(s)].sum);
	}
	return 0;
}
```

---

## 作者：Isharmla (赞：0)

操作树板子题。

不难发现如果没有回溯操作的话，版本 $i$ 显然通过版本 $i-1$ 继承而来，这部分直接暴力就好。关键是如何处理回溯操作，如果记录的话空间承受不了。很简单，对于回溯操作，我们直接离线下来，假如我们要求回溯到版本 $k$，那当我们处理到版本 $k$ 的我们就分开处理询问，一个处理不回溯时候的版本也就是正常操作下去，另外一个直接处理后面询问时候的那个操作，这个东西离线下来建边即可轻松实现。下图就给出了一个例子。

![](https://cdn.luogu.com.cn/upload/image_hosting/3zxb5ydn.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这个例子的意思是，我们在版本五的时候回溯到版本二，在版本七的时候回溯到版本四。我们通过前面讲的方法建边，然后遍历一遍即可。

---

## 作者：快斗游鹿 (赞：0)

## 思路

观察到每次操作最多更新 $n$ 个数，所以 $1,2,3$ 直接拿数组暴力更新就行。考虑如何解决操作 $4$。显然可以建一棵操作树，具体过程是对于不是操作 $4$ 的情况，就将 $i-1$ 和 $i$ 连边，表示第 $i$ 个操作前一个操作为第 $i-1$ 个操作。否则就将 $K$ 和 $i$ 连边，表示第 $i$ 个操作前一个操作为第 $K$ 次操作。然后在深搜的过程中更新即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int M=1e3+5;
struct Node{
	int to,nxt;
}e[N];
int n,m,q,cnt,head[N],op[N],x[N],y[N],ans[N],ccc;
bool a[M][M];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs(int u){
	int lst;
	if(op[u]==1){
		lst=a[x[u]][y[u]];
		if(a[x[u]][y[u]]==0)ccc++;
		a[x[u]][y[u]]=1;
	}
	else if(op[u]==2){
		lst=a[x[u]][y[u]];
		if(a[x[u]][y[u]]==1)ccc--;
		a[x[u]][y[u]]=0;
	}
	else if(op[u]==3){
		for(int i=1;i<=m;i++){
			if(a[x[u]][i]==0)ccc++;
			else ccc--;
			a[x[u]][i]^=1;
		}
	}
	ans[u]=ccc;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dfs(v);
	}
	if(op[u]==1){
		a[x[u]][y[u]]=lst;
		if(a[x[u]][y[u]]==0)ccc--;
	}
	else if(op[u]==2){
		a[x[u]][y[u]]=lst;
		if(a[x[u]][y[u]]==1)ccc++;
	}
	else if(op[u]==3){
		for(int i=1;i<=m;i++){
			if(a[x[u]][i]==0)ccc++;
			else ccc--;
			a[x[u]][i]^=1;
		}
	}
}
int main(){
	n=read();m=read();q=read();
	for(int i=1;i<=q;i++){
		op[i]=read();
		if(op[i]==1){
			x[i]=read();y[i]=read();
			add(i-1,i);
		}
		else if(op[i]==2){
			x[i]=read();y[i]=read();
			add(i-1,i);
		}
		else if(op[i]==3){
			x[i]=read();
			add(i-1,i);
		}
		else{
			x[i]=read();
			add(x[i],i);
		}
	}
	dfs(0);
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
	return 0;
}

```


---

