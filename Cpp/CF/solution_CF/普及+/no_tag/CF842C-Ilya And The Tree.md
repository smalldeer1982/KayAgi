# Ilya And The Tree

## 题目描述

Ilya is very fond of graphs, especially trees. During his last trip to the forest Ilya found a very interesting tree rooted at vertex $ 1 $ . There is an integer number written on each vertex of the tree; the number written on vertex $ i $ is equal to $ a_{i} $ .

Ilya believes that the beauty of the vertex $ x $ is the greatest common divisor of all numbers written on the vertices on the path from the root to $ x $ , including this vertex itself. In addition, Ilya can change the number in one arbitrary vertex to $ 0 $ or leave all vertices unchanged. Now for each vertex Ilya wants to know the maximum possible beauty it can have.

For each vertex the answer must be considered independently.

The beauty of the root equals to number written on it.

## 样例 #1

### 输入

```
2
6 2
1 2
```

### 输出

```
6 6 
```

## 样例 #2

### 输入

```
3
6 2 3
1 2
1 3
```

### 输出

```
6 6 6 
```

## 样例 #3

### 输入

```
1
10
```

### 输出

```
10 
```

# 题解

## 作者：lx_zjk (赞：8)

这道题目 还是比较水的 一开始读错题目 (我觉得是翻译的锅) 

$f[u][0 / 1]$表示这颗子树是否修改 然后最大的美丽值

好像可以推

然后 又想了一想 对于每颗点 决策 只有两种 要么修改 要么不变

$f[u]$表示以u为节点的最大值

然后就是记忆化搜索了

$dfs(u, fa, opt, cur)$表示当前为$u$节点 $opt$表示是否修改过了 $cur$表示对应的最大值

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF = 2139062143;

#define DEBUG(x) std::cerr << #x << ' = ' << x << std::endl

inline ll read() {
    ll f = 1, x = 0;char ch;
    do {ch = getchar();if (ch == '-')f = -1;} while (ch > '9' || ch < '0');
    do {x = x * 10 + ch - '0';ch = getchar();} while (ch >= '0' && ch <= '9');
    return f * x;
}

const int MAX_N = 2e5 + 7;

int n, a[MAX_N], f[MAX_N];

map < int, bool > vis[MAX_N][2];

struct Edge {
	int to, next;
}edge[MAX_N << 1];

int head[MAX_N], cnt;

void addedge (int u, int v) {
	edge[++cnt].to = v;
	edge[cnt].next = head[u];
	head[u] = cnt;
}

inline int gcd (int a, int b) {
	if (a < b) swap(a, b);
	return b == 0 ? a : gcd (b, a % b);
}

void dfs (int u, int fa, int opt, int cur) {
	if (vis[u][opt][cur]) return;
	vis[u][opt][cur] = true;
	int tmp = gcd (cur, a[u]);
	f[u] = max(f[u], tmp);
	if (opt == 0) f[u] = max(f[u], cur);
	for (int i = head[u]; i; i = edge[i].next ) {
		int v = edge[i].to;
		if (v == fa) continue;
		dfs (v, u, opt, tmp);
		if (opt == 0) dfs (v, u, 1, cur);
	}
}

int main() {
	n = read();
	for (int i = 1; i <= n; i ++ ) a[i] = read();
	for (int i = 1; i < n; i ++ ) {
		int x = read(), y = read();
		addedge (x, y);
		addedge (y, x);
	}
	dfs (1, 0, 0, 0);
	for (int i = 1; i <= n; i ++ )
		printf ("%d ", f[i]);
	return 0;
}


```

upd on 2024/11/23
前面写了篇复杂度玄学的题解 更新一下新的做法 

显然这题出成树和链 做法都是一样的
要么$a_1$选 要么$a_1$不选
$a_1$不选 直接预处理
```cpp
void dfs(int u, int fa, int x) {
    dep[u] = dep[fa] + 1;
    ans[u] = max(ans[u], x);
    for(int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if(v == fa) continue;
        dfs(v, u, gcd(x, a[v]));
    }
}
dfs(1, 0, 0);
```

$a_1$选 那么答案肯定是$a_1$的因子 而因子的个数只有$\sqrt(n)$个 那么我们只需要枚举每个因子能不能成为当前点的答案就行，如果要成为答案 那么$u$和他的祖先 至少有$dep_u - 1$个是$x$的倍数 然后就做完了 类似括号树一样 入栈出栈维护一下即可
```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 7;
struct EDGE {
    int to, nxt;
} edge[N << 1];
int n, cnt, a[N], dep[N], ans[N], head[N];
void addedge(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
void dfs(int u, int fa, int x) {
    dep[u] = dep[fa] + 1;
    ans[u] = max(ans[u], x);
    for(int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if(v == fa) continue;
        dfs(v, u, gcd(x, a[v]));
    }
}
int c;
void redfs(int u, int fa, int x) {
    int y = (a[u] % x == 0);
    c += y;
    if(c == dep[u] || c == dep[u] - 1) ans[u] = max(ans[u], x);
    for(int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if(v == fa) continue;
        redfs(v, u, x);
    }
    c -= y;
}
void solve() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        addedge(u, v); addedge(v, u);
    }
    for(int i = 1; i <= n; i++) ans[i] = 1;
    dfs(1, 0, 0); // a[1]不选的情况
    // a[1]选的情况 一个点能是x的情况 就是[1, x]的路径上 至多有一个不是x的倍数
    redfs(1, 0, a[1]);
    for(int i = 2; i * i <= a[1]; i++) {
        if(a[1] % i == 0) {
            redfs(1, 0, i);
            if(a[1] / i != i) redfs(1, 0, a[1] / i);
        }
    }
    for(int i = 1; i <= n; i++) printf("%d ", ans[i]); puts("");
    return;
}
int main() {
    int T; T = 1;
    for(int _ = 1; _ <= T; _ ++) solve();
    return 0;
}
```

---

## 作者：陆巷北NorthAlley (赞：6)

~~众所周知CF的题目一般都会被恶意评分~~

### 题意

大意如翻译，但要注意三点：

1、可以删除自己

2、可以不删除

3、根为1

### 思路

拿到这类要求gcd的题目，我们一般先考虑质因数分解。

求单个的复杂度是$O(\sqrt{N})$

$dfs$的复杂度是$O(N)$

总的复杂度是$O(N\sqrt{N})$

那么一遍下来就是、、、就是、、、等等我掏个计算器

$200000\times\sqrt{200000}\approx90000000$

给了两秒钟，完全$ok$滴说！

用一个$cnt[i]$数组记录$dfs$到目前$(now)$为止$i$因子出现的个数

如果$cnt[i] = dep[now]$就可以更新正解

但如果是去掉当前点的后得到的$gcd$最大呢？

所以我们在$dfs$的时候还要记录一个东西$(maxf)$，它记录了从根节点到上一个节点$fa$为止不去掉任何一个点的$gcd$

好，差不多都交代完了

那就让我们来看一下本篇的重头戏!

### $dfs$

```cpp
//当时是在比赛完之后写的代码，并没有改过
//所以如果出现了很多没有意义的憨憨定义
//请不要踩窝蟹蟹您٩('ω')و
void dfs(int now,int fa,int maxf){
	dep[now] = dep[fa] + 1;  //同英文，深度
	cnt[col[now]]++;  //如上提到,col是该位置的数字
	int maxnow = 1;  //修改它儿子们的maxf
	Ans[now] = 1;
	if(cnt[col[now]] == dep[now] || cnt[col[now]] == dep[now] - 1)  //其实这里和上文窝提到的一样
		Ans[now] = col[now];						//可以只有当前深度。想一想为什么？
	if(cnt[col[now]] == dep[now]) maxnow = max(maxnow,col[now]); 		//为它的儿子们的修改保证
	Ans[now] = max(Ans[now],maxf);
	for(int i = 2;i * i <= col[now];i++){			//分解质因数
		if(!(col[now] % i)){		
			cnt[i]++;		
			if(col[now]/i != i) cnt[col[now]/i]++;		//当时这里找了好久，我好cai，呜呜呜
			if(cnt[i] == dep[now] || cnt[i] == dep[now] - 1){
				Ans[now] = max(Ans[now],i);			//同上面可以改进，防止多余的计算
			}
			if(cnt[i] == dep[now]) maxnow = max(maxnow,i);		//改maxf的值
			if(cnt[col[now]/i] == dep[now] || cnt[col[now]/i] == dep[now] - 1){
				Ans[now] = max(Ans[now],col[now]/i);
			}
			if(cnt[col[now]/i] == dep[now]) maxnow = max(maxnow,col[now]/i);
		}
	}
	for(int i = fir[now];i;i = nxt[i]){
		if(to[i] == fa) continue;		//前项星可好用了
		dfs(to[i],now,maxnow);			//dfs它的儿子们
	}
	for(int i = 1;i * i <= col[now];i++){  //别忘了回溯哦，反正复杂度也不会增加
		if(!(col[now] % i)){
			cnt[i]--;
			if(col[now]/i != i) 
				cnt[col[now]/i]--;
		}
	}
}
```
希望这篇题解能对您有帮助，如果这亚子的话，就不要吝啬您免费的赞了呦

我的$Blog$传送门[Lu_Mingの宅](https://www.luogu.org/blog/Lu-Ming/)

### AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAX = 200020;
int n,a[MAX],fir[MAX],nxt[MAX << 1],to[MAX << 1],num;
int cnt[MAX],Ans[MAX],col[MAX],dep[MAX];


void dfs(int now,int fa,int maxf);
void init();
void add(int u,int v);
void outit(); 

int main(void){
	init();
	dfs(1,0,1);
	outit();
	return 0;
}

void init(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)
		scanf("%d",&col[i]);
	int x,y;
	for(int i = 1;i < n;i++){
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
}

void outit(){
	for(int i = 1;i < n;i++)
		printf("%d ",Ans[i]);
	printf("%d\n",Ans[n]);
}

void add(int u,int v){
	to[++num] = v;
	nxt[num] = fir[u];
	fir[u] = num;
}

void dfs(int now,int fa,int maxf){
	dep[now] = dep[fa] + 1;  //同英文，深度
	cnt[col[now]]++;  //如上提到,col是该位置的数字
	int maxnow = 1;  //修改它儿子们的maxf
	Ans[now] = 1;
	if(cnt[col[now]] == dep[now] || cnt[col[now]] == dep[now] - 1)  //其实这里和上文窝提到的一样
		Ans[now] = col[now];						//可以只有当前深度。想一想为什么？
	if(cnt[col[now]] == dep[now]) maxnow = max(maxnow,col[now]); 		//为它的儿子们的修改保证
	Ans[now] = max(Ans[now],maxf);
	for(int i = 2;i * i <= col[now];i++){			//分解质因数
		if(!(col[now] % i)){		
			cnt[i]++;		
			if(col[now]/i != i) cnt[col[now]/i]++;		//当时这个错找了好久，我好cai，呜呜呜
			if(cnt[i] == dep[now] || cnt[i] == dep[now] - 1){
				Ans[now] = max(Ans[now],i);			//同上面可以改进，防止多余的计算
			}
			if(cnt[i] == dep[now]) maxnow = max(maxnow,i);		//改maxf的值
			if(cnt[col[now]/i] == dep[now] || cnt[col[now]/i] == dep[now] - 1){
				Ans[now] = max(Ans[now],col[now]/i);
			}
			if(cnt[col[now]/i] == dep[now]) maxnow = max(maxnow,col[now]/i);
		}
	}
	for(int i = fir[now];i;i = nxt[i]){
		if(to[i] == fa) continue;		//前项星可好用了
		dfs(to[i],now,maxnow);			//dfs它的儿子们
	}
	for(int i = 1;i * i <= col[now];i++){  //别忘了回溯哦，反正复杂度也不会增加
		if(!(col[now] % i)){
			cnt[i]--;
			if(col[now]/i != i) 
				cnt[col[now]/i]--;
		}
	}
}
```


---

## 作者：lukelin (赞：6)

这道题，我直接暴力+不正确剪枝水过了  
考虑动态规划，f[i]表示删0/1条边的时候GCD最大值，如果直接向上递推会超时，只向上推一层，会WA，然后就发现可以中和一下，向上推10层，错误概率就极低了(然后就水过去了)

最后放个代码：  
注:g[i]是GCD前缀和
```cpp
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int read(){
    int x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

int gcd(int a, int b){
    if (b > a) swap(a, b);
    while (b > 0){
        int tmp = a % b;
        a = b, b = tmp;
    }
    return a;
}

int a[200005];
int f[200005], g[200005];
int fat[200005];
vector<int> edges[200005];

void getf(int u, int fa){
    if (fa == 0)
        g[u] = a[u];
    else
        g[u] = gcd(g[fa], a[u]);
    if (fa != 0){
        f[u] = g[u];
        f[u] = max(g[fa], gcd(f[fa], a[u]));
        int v = fa, gg = a[u], i = 10;
        while (v && i > 0){ 
            f[u] = max(f[u], gcd(gg, f[v]));
            if (fat[v] != 0){
                f[u] = max(f[u], gcd(gg, g[fat[v]]));
            }else{
                f[u] = max(f[u], gg);
            }
            gg = gcd(gg, a[v]);
            v = fat[v];
            --i;
        }
    }
    else
        f[u] = g[u];
    int v, i, u_s = edges[u].size();
    for (i = 0; i < u_s; ++i){
        v = edges[u][i];
        if (v != fa && v != 0){
            fat[v] = u;
            getf(v, u);
        }
    }
}

int main(){
    int n = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    int u, v;
    for (int i = 1; i < n; ++i){
        u = read(), v = read();
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    getf(1, 0);
    for (int i = 1; i <= n; ++i){
        printf("%d", max(f[i], g[i]));
        if (i < n)
            printf(" ");
        else
            printf("\n");
    }
    return 0;
}
```

---

## 作者：luyan (赞：4)

题目大意：
有一个n个节点的数,每个点有一个点权,根到这个点的所有点权(包括这个点和根)的gcd值为这个点的答案. 对于每一个点的答案,你可以删除其到根节点的路径上的至多一个点来使答案最大. 求每个点的答案(最大值). PS:根为1号点.

这道题我刚拿到手的时候还以为这是一道数论的题目，但其实不然，只要暴力搜索即可。

dp记录答案

由于一串数的gcd的计算并没有顺序（gcd(gcd(a,b),c)==gcd(a,gcd(b,c)),所以我们可以对树进行深度优先搜索的时候对于每一个点将从根节点到这个点的这条链中任意一个点变成0后的gcd的可能值记录在一个vector中，这样的话一个节点的vector里面应该有从上一个的最优解传下来的dp以及父节点的vector里面的每一个值与这个点的点权的gcd（具体看代码）

然后对于每一个点我都用它的vector里面的最大值来更新答案。

下附AC代码：

```
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
struct edge{
	int to,next;
}e[400040];
int eid=0,head[200010];
void insert(int u,int v){
	eid++;
	e[eid].to=v;
	e[eid].next=head[u];
	head[u]=eid;
}
int a[200010];
int n;
int fa[200010];
int dp[200010];//某一个点的美丽值 
vector<int>v[200010];//存储每一个点的美丽值的可能值 
int gcd(int a,int b){
	if(b==0)return a;
	return gcd(b,a%b);
}
void dfs(int x,int pre){
	for(int i=head[x];i+1;i=e[i].next){
		int k=e[i].to;
		if(k==pre)continue;
		dp[k]=gcd(dp[x],a[k]);
		v[k].push_back(dp[x]);
		for(int j=0;j<v[x].size();j++){
			v[k].push_back(gcd(v[x][j],a[k]));
		}
		sort(v[k].begin(),v[k].end());//排序+去重，保证最后面的元素最优 
		v[k].erase(unique(v[k].begin(),v[k].end()),v[k].end());
		dfs(k,x);
	}
}
int main(){
	memset(head,-1,sizeof(head));
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		insert(x,y);
		insert(y,x);
		fa[y]=x;
	}
	fa[1]=0;
	dp[1]=a[1];
	v[1].push_back(0);
	dfs(1,0);
	for(int i=1;i<=n;i++){
		dp[i]=max(dp[i],v[i].back());//用vector里面的最优答案更新结果 
	}
	for(int i=1;i<=n;i++){
		cout<<dp[i];
		if(i!=n)cout<<" ";
		else cout<<endl;
	}
}
```


---

## 作者：Mr_罗 (赞：3)

$\tt{upd \ on\ 2022/2/9}$：删除滥用的 $\LaTeX$。

[题目传送门](https://www.luogu.com.cn/problem/CF842C)

提供一个不太一样的思路。

## Part 1：读题

有一棵树，每一个点有一个点权，求对于每一个点，它到根的路径上最多可以删掉 $1$ 个点的情况下所有点权的最大公约数的最大值。

## Part 2：思路

首先可以肯定，暴力查询是绝对过不了的。

由于路径都是到根的，即儿子的路径比父亲的仅多一个点，尝试一种类似于递推的方法。

先看一张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/9qrs43yb.png)

如图，假设 A1 是根节点，当前要求 B 的答案。

对于 B，无非有两种情况：删，或者不删。

1. 删掉 B。

删掉 B 的话，A1 到 A4 就都需要保留。此时答案为 $\gcd (A_1,A_2,A_3,A_4)$。可以在先序遍历途中递推得到。

2. 不删 B。

此时，B 的祖先们有可能删掉一个，也有可能全部保留。此时，我们可以将 B 的祖先们的所有因子求出来，放在一个桶里面。对于每一个 B 的因子，我们先将 B 的因子对应的桶的值加 $1$，再判断桶的值是否不小于 $\text{dep}_B-1$，其中 $\text{dep}_B$ 表示 B 的深度。

因为从 B 到根的点总共有 $\text{dep}_B$ 个，减一后表示这一条路径上会删掉 $1$ 个点。又因为我们查看的都是 B 的因子，所以这个删掉的点一定是 B 的祖先节点。而不小于则对应了这条路径上一个也不删的情况。

所以本题就可以愉快的 AC 了~

## Part 3：代码

```cpp
/**
 * Owner Mr_L
 * Prob  CF842C
 * Lang  C++
 * Date  2022.2.5
**/
#include <bits/stdc++.h>
using namespace std;

int n, a[200010], t[200010], g[200010], gs[200010];
int hd[200010], ed[400010], nt[400010], cnt;

void add_edge (int u, int v)
{
    ed[++cnt] = v;
    nt[cnt] = hd[u];
    hd[u] = cnt;
}

void dfs (int u, int fa, int dep)
{
    //处理不删的情况
    for (int i = 1; i * i <= a[u]; i++)
    {
        if (a[u] % i)
            continue;
        t[i]++;
        if (i * i != a[u])
            t[a[u] / i]++;
        if (t[i] >= dep - 1)
            g[u] = max (g[u], i);
        if (t[a[u] / i] >= dep - 1)
            g[u] = max (g[u], a[u] / i);
    }
    //处理删的情况
    g[u] = max (g[u], gs[fa]);
    //递推整条路径的最大公约数，用的是 C++ 内部的 gcd 函数
    gs[u] = __gcd (a[u], gs[fa]);
    for (int i = hd[u]; i; i = nt[i])
    {
        int v = ed[i];
        if (v == fa)
            continue;
        dfs (v, u, dep + 1);
    }
    //记得回溯
    for (int i = 1; i * i <= a[u]; i++)
    {
        if (a[u] % i)
            continue;
        t[i]--;
        if (i * i != a[u])
            t[a[u] / i]--;
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        add_edge (a, b);
        add_edge (b, a);
    }
    dfs (1, 0, 1);
    for (int i = 1; i <= n; i++)
        cout << g[i] << ' ';
    cout << endl;
    return 0;
}
```

---

## 作者：mulberror (赞：3)

# 题解
不怎么难。  
$f[i][j]$表示$i$为根，然后枚举是否删除改点，如删除过$j=1$否则$j=0$。  
为了防止有全质数的情况。开一个$map$记忆化搜索一下就可以了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IOstream {
    #define gc getchar
    template <typename T> inline void read(T &x) {
        x = 0; T fl = 1; char c = 0;
        for (; c < '0' || c > '9'; c = gc()) if (c == '-') fl = -1;
        for (; c >= '0' && c <= '9'; c = gc()) x = (x << 1) + (x << 3) + (c ^ 48);
        x *= fl;  
    }
    template <typename T> inline T sqr(T x) { return x * x; }
    template <typename T> inline void write(T x) {
        if (x < 0) putchar('-'), x *= -1;
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
    template <typename T> inline T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
    template <typename T> inline void writeln(T x) { write(x); puts(""); }
    template <typename T> inline void writesp(T x) { write(x); putchar(' '); }
    #undef gc
} using namespace IOstream;
typedef long long ll;
const int N = 2e5 + 5;
vector<int> gr[N];
int a[N], ans[N];
int n;
unordered_map<int, bool> f[N][2];
void DP(int u, int fa, int opt, int cum) {
    if (f[u][opt][cum]) return;
    f[u][opt][cum] = true;
    int tmp = gcd(cum, a[u]);
    ans[u] = max(ans[u], tmp);
    if (opt == 0) ans[u] = max(ans[u], cum);
    for (auto v : gr[u]) {
        if (v == fa) continue; 
        DP(v, u, opt, tmp);
        if (opt == 0) DP(v, u, 1, cum);
    }
}
int main() {
    read(n);
    for (int i = 1; i <= n; i ++) read(a[i]);
    for (int i = 1, u, v; i < n; i ++) {
        read(u); read(v); 
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    DP(1, 0, 0, 0);
    for (int i = 1; i <= n; i ++) writesp(ans[i]);
    return 0;
}

```

---

## 作者：xxasmcd (赞：2)

这道题我的思路是对于每一个节点，将它的所有分子都用一个桶数组进行维护，由于可以去掉一个点，所以这一个点的答案就是大于这一个点的深度减去一的最大分子，在回溯时再把所有的分子在桶里去掉，如此递归处理。
 
代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
int head[400005],nxt[400005],edge[400005],num=0,ans[200005],a[200005],n,tong[200005],g[200005];
void add(int x,int y)//建边
{
    num++;
    edge[num]=y;
    nxt[num]=head[x];
    head[x]=num;
    num++;
    edge[num]=x;
    nxt[num]=head[y];
    head[y]=num;
}
int gcd(int x,int y)//最大公因数函数
{
	if(!y)
   {
		return x;
	}
	return gcd(y,x%y);
}
void dfs(int u,int fa,int dep)
{
    for(int i=1;i<=sqrt(a[u]);i++)//将所有分子加入到桶里
    {
        if(a[u]%i==0)
        {
            tong[i]++;
            if(i*i!=a[u])
            {
                tong[a[u]/i]++;
            }
            if(tong[i]>=dep-1)//如果合法
            {
                ans[u]=max(ans[u],i);
            }
            if(tong[a[u]/i]>=dep-1)//同理
            {
                ans[u]=max(ans[u],a[u]/i);
            }
        }
    }
    ans[u]=max(ans[u],g[fa]);//记录答案
    g[u]=gcd(a[u],g[fa]);//记录最大公因子，以便下一次处理
    for(int i=head[u];i>0;i=nxt[i])//递归
    {
        int to=edge[i];
        if(to==fa)continue;
        dfs(to,u,dep+1);
    }
    for(int i=1;i<=sqrt(a[u]);i++)//回溯，将所有分子从桶里去除
    {
        if(a[u]%i==0)
        {
            tong[i]--;
            if(i*i!=a[u])
            {
                tong[a[u]/i]--;
            }
        }
    }
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        add(x,y);
    }
    dfs(1,0,1);
    for(int i=1;i<=n;i++)
    {
        cout<<ans[i]<<" ";
    }
    return 0;
}

```



---

## 作者：泠小毒 (赞：2)

# Ilya And The Tree

给你一棵树，让你求从1号点到所有点经过的点的gcd最大值

有一种操作，可以让一个点的点权变为0，只能使用一次

对于每一个点的答案需要单独计算，即不同点的最大值时变为0的点可以不同

## 广告插入

在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190430/)

## 解法

先来想一想一种暴力，先跑一遍没有变成0操作的dfs，算完初始的gcd

然后枚举每一个点变为0的情况，更新它的子树

这样做的复杂度是什么呢，我们发现同一深度的点不会重复做

所以是O(ndist)，它的期望复杂度就是nlogn，然而一条链就退化成n方了

那怎么优化呢？你可以发现，在枚举修改某一个点时，会在某一个点做很多次重复的操作

所以，如果当前的最大值是现在的gcd的倍数，就可以剪枝掉

为什么不是当前最大值比现在的gcd大就剪枝掉呢？可以举一组反例

9->6->12，这一组，6这里的最优解是将6变成0，答案是9，但是12这里的最优解是将9变成0，答案是6

这时候如果直接剪枝，12的答案就会变成3了

## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
struct node{int to,next;}e[400010];
int n,cnt,x,y,a[200010],dis[200010],ans[200010],head[200010],fa[200010];
void add(){e[++cnt]={y,head[x]},head[x]=cnt,e[++cnt]={x,head[y]},head[y]=cnt;}
void dfs(int u)
{
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(fa[u]==v)continue;
		ans[v]=dis[v]=gcd(dis[u],a[v]),fa[v]=u,dfs(v);
	}
}
void work(int u,int d)
{
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(fa[u]==v)continue;
		int dd=gcd(d,a[v]);
		if(ans[v]%dd==0)continue;
		ans[v]=max(ans[v],dd),work(v,dd);
	}
}
void dfsx(int u)
{
	ans[u]=max(ans[u],dis[fa[u]]),work(u,dis[fa[u]]);
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(fa[u]==v)continue;
		dfsx(v);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<n;i++)scanf("%d%d",&x,&y),add();
	ans[1]=dis[1]=a[1],dfs(1),dfsx(1);
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：FwbAway (赞：1)

## 题意

有一棵每个点均有一个权值 $a_i$ 的树，对于每一个 $i$（$1\le i\le n$），需要求出 $1\sim i$ 上任意删除 $0\sim 1$ 个节点后，所有 $a_i$ 的 $\gcd$。

## 思路

使用双重数组思路。

我们定义 $dp_u$ 为 $1\sim u$ 的 $\gcd$，滚动数组 $vt_u$ 为 $1\sim u$ 中分别去除每一个节点后的所有 $\gcd$ 集合。对于每一个滚动数组 $vt_i$，在计算时对其排序去重。最后的答案即 $\max{(dp_i, vt_i)}$。考虑具体实现其中操作。

考虑通过一遍 $dfs$ 确定所有的 $dp_i$ 值，即每次让 $dp_i=\gcd(dp_{fa_i},a_i)$，那是否可以同时计算出 $vt_i$ 呢？

我们发现，在向下 $dfs$ 时，若当前为节点 $i$（$i≠1$），则 $fa_i$ 的 $dp$ 值和 $vt$ 值**一定**都是处理好的，故可以用其直接更新 $i$ 的值。

在 $1\sim fa_i$ 这些节点中，$vt_{fa_i}$ 一定记录了分别除去 $1\sim fa_i$ 中每一个点后的答案。所以如果使用 $fa_i$ 来更新 $i$ 的话，可以通过以下操作来更新 $vt_i$：

```c++
vt[i].push_back(dp[fa[i]]);
for (int j = 0; j < vt[fa[i]].size(); j++) {
	vt[i].push_back(gcd(vt[fa[i]][j], a[i]));
}
```

首先，我们将 $dp_{fa_i}$ 放入 $vt_i$ 中，代表去除 $i$ 位置时的答案。

然后，我们对于去除 $1\sim fa_i$ 中的每一种情况，将其映射入 $vt_i$。代表分别去除 $1\sim fa_i$ 位置的答案。

这样就操作完了。

需要特别注意的地方有：在 $i=1$ 时，不存在 $fa_i$，即无法更新 $vt_i$（但可以更新 $dp_i$），这样就无法在 $i=2$ 时的 $vt_i$ 中存入删除节点 $1$ 的答案，故在 $dfs$ 开始之前，需要先将 $0$ 加入 $vt_1$ 中去，这样当 $i=2$ 时，做 $\gcd(0,a_2)$ 就可以获得删除节点 $1$ 的答案了。

以上是个人的拙见，具体解释还需看代码：

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 210000;
int n, a[N], x, y, dp[N];
vector<int> vt[N];
//dp[u]表示1~u的答案
//vt[u]表示1~u删除每个点的答案（去重）
vector<int> e[N];
inline int gcd(int x, int y) {//辗转相除
	return y ? gcd(y, x % y) : x;
}
void dfs(int u, int fa) {
	for (int i = 0; i < e[u].size(); i++) {
		int v = e[u][i];
		if (v != fa) {
			//此时u是v的父亲 
			dp[v] = gcd(dp[u], a[v]);//计算dp值 
			vt[v].push_back(dp[u]);//去除节点v的答案 
			for (int i = 0; i < vt[u].size(); i++) {
				vt[v].push_back(gcd(vt[u][i], a[v]));//分别删除1~u的每一个计算答案 
			}
			sort(vt[v].begin(), vt[v].end());//排序 
			vt[v].erase(unique(vt[v].begin(), vt[v].end()), vt[v].end());//去重 
			dfs(v, u);
		}
	}
}
signed main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dp[1] = a[1];//1~1的gcd是a[1]
	vt[1].push_back(0);//去除节点1的操作 
	dfs(1, -1);
	for (int i = 1; i <= n; i++) {
		dp[i] = max(dp[i], vt[i].back());
		//要么都取，要么少一个，少一个的最大美丽值为vt[i]的最大值
	}
	for (int i = 1; i <= n; i++) {
		printf("%d ", dp[i]);
	}
	return 0;
}
```

注：以上代码已在 CF 测试通过。

## 总结

这道题其实考验的是选手的分析和解决能力，题目很好理解，也用不上什么算法，所谓的 $dp$ 其实就是顺序求解。但是难度却不低，因为使用双重数组的思路很多人想不到，而且这种巧妙的计算方式也考察了选手的思维等级，这道题目还是很适合普及和提高组的选手训练的。

最后祝大家在今年的比赛中取得好成绩，我们下篇题解再见！

---

## 作者：交警 (赞：1)

##  $CodeForces$ $CF842C$ 
#  $Ilya$ $And$ $The$ $Tree$ 


####  $2019.11.5$ 
####  $NanyaOIer$ $:$ $y2j$
### $Time$ $Limit$ $:$ $2.00s$  
### $Memory$ $Limit$ $:$ $256MB$
## $Background$

$CodeForces$ 评分 ： $2000$

## $Simplified$ $Description$

给出一棵 $n$ 个节点的树，根节点为 $1$ 。每个点都存在一个点权 $w_i$ ，根到这个节点的所有点权（包含根节点和该节点）的 $gcd$ 值为这个点的答案。  
对于每个点的答案，可以删除根节点到该节点的路径上至多一个节点来使得答案最大。求每个点的答案（最大值）。

## $Input$

第一行一个整数 $n$ ，表示有 $n$ 个节点。  
第二行 $n$ 个整数，表示每个点的点权 $w_i$ 。  
随后 $n - 1$ 行，每行两个整数 $x,$ $y$ ，表示 $x$ 与 $y$ 之间有一条连边。

## $Output$

一行 $n$ 个整数，为每个点的答案（详见题目描述）。

## $Sample1$ $Input$

```
2
6 2
1 2
```

## $Sample1$ $Output$

```
6 6
```

## $Sample1$ $Explaination$

对于节点 $1$ ：  
$1$ 号节点与根节点的路径为 $1$ ，若删去 $1$ 答案为 $0$ ，若不删去则答案为 $6$ ，故节点 $1$ 的答案为 $max$ $($ $0,$ $6$ $)$ $=$ $6$ 。

对于节点 $2$ ：
$2$ 号节点与根节点的路径为 $1 -> 2$ ，若删去 $1$ 答案为 $2$ ，若删去 $2$ 答案为 $6$ ，若不删去则答案为 $gcd$ $($ $6,$ $2$ $)$ $=$ $2$ ，故节点 $2$ 的答案为 $max$&nbsp;${$ &nbsp;$2,$&nbsp;$2,$&nbsp;$6$&nbsp;$}$&nbsp;$=$&nbsp;$6$ 。

故输出为 ```6 6``` 。

## $Sample2$ $Input$

```
3
6 2 3
1 2
1 3
```

## $Sample2$ $Output$

```
6 6 6
```

## $Sample2$ $Explaination$

对于节点 $1$ ：  
$1$ 号节点与根节点的路径为 $1$ ，若删去 $1$ 答案为 $0$ ，若不删去则答案为 $6$ ，故节点 $1$ 的答案为 $max$ $($ $0,$ $6$ $)$ $=$ $6$ 。

对于节点 $2$ ：
$2$ 号节点与根节点的路径为 $1 -> 2$ ，若删去 $1$ 答案为 $2$ ，若删去 $2$ 答案为 $6$ ，若不删去则答案为 $gcd$ $($ $6,$ $2$ $)$ $=$ $2$ ，故节点 $2$ 的答案为 $max$ ${$ $2,$ $2,$ $6$ $}$ $=$ $6$ 。

对于节点 $3$ ：  
$3$ 号节点与根节点的路径为 $1 -> 3$ ，若删去 $1$ 答案为 $3$ ，若删去 $2$ 答案为 $6$ ，若不删去则答案为 $gcd$ $($ $6,$ $3$ $)$ $=$ $3$ ，故节点 $3$ 的答案为 $max$ ${$ $3,$ $3,$ $6$ $}$ $=$ $6$ 。

故输出为 ```6 6 6``` 。

## $Sample3$ $Input$

```
1
10
```

## $Sample3$ $Output$

```
10
```

## $Sample3$ $Explaination$

对于节点 $1$ ：  
$1$ 号节点与根节点的路径为 $1$ ，若删去 $1$ 答案为 $0$ ，若不删去则答案为 $10$ ，故节点 $1$ 的答案为 $max$ $($ $0,$ $10$ $)$ $=$ $10$ 。

## $Data$ $Constraint$

$1≤n≤2 × 10^5$ , $1≤w_i≤2×10^5$。

数据保证所有节点均与根节点有且只有一条路径。

## $Solution$

思路：  

看到 $gcd$ ，不管有没有用，打上再说。  
然后 ```dfs``` 遍历每一个节点。  
在求每个点答案时，对于每个点有两种决策：  
> 1.路径不更改。  
> 2.路径上删除某个点。

用一个 ```f[N]``` 数组来存下每个节点的答案。也可以用一个 ```f[N][2]``` （ ```f[i][0]``` 表示路径不修改，```f[i][1]``` 表示路径修改 ）的数组来存，只是输出的时候需要输出 ```max ( f[i][0], f[i][1] );```。  
然后用一个 ```vis[N][0][]``` 的 ```bool``` 型存下每种情况的使用情况。因为第三维的数可能会很大，或者说三维数组开不下，所以我们使用 ```STL``` ：```map < int, bool > vis[N][2] ```。  
然后从根节点 ```dfs``` 。  
如果当前节点的 ```vis[i][0][cur]``` 为 $true$ ，那么遍历到它的儿子的时候既可以经过，也可以不经过直接往下走。（\* *```cur``` 表示这种情况的最大值* ）。  
如果当前节点的 ```vis[i][1][cur]``` 为 $true$ ，那么遍历到它的儿子的时候就只能经过了。  
每经过一个点，与父亲节点的 ```cur``` 值取 $gcd$。  
这道题就可以 $A$ 了。

## $std$

```cpp
#include<bits/stdc++.h>
using namespace std;
//<----------------------↓以下为快读快写的封装↓---------------------->
namespace speed {
	
	template < typename T > inline T read() {
		register int f = 1; register T sum = 0; register char ch = getchar();
		while ( !isdigit(ch) ) { if ( !( ch ^ '-' ) ) f = -1; ch = getchar(); }
		while ( isdigit(ch) ) { sum = (sum<<1) + (sum<<3) + (ch^48); ch = getchar(); }
		return f * sum;
	}
	
	template < typename T > inline void write ( register T x ) {
		if ( x < 0 ) { x = -x; putchar ( '-' );	}
		if ( x > 9 ) { write ( x / 10 ); }
		putchar ( x % 10 + '0' );
	}
	
}

using namespace speed;
//<----------------------↑以上为快读快写的封装↑---------------------->
const int N = 2e5 + 5;

int n;
int w[N], f[N];

vector < int > edge[N]; //用vector建图建树又好写又好看。如果有边权的话，应该使用 vector < pair < int, int > > edge[N]; pair的first存点，pair的second存边权
map < int, bool > vis[N][2]; //对于每种情况进行记忆化，vis[i][0] 代表还未修改，vis[i][1] 代表已经修改。
//<----------------------↓gcd↓---------------------->
template < class T > inline T gcd ( register T x, register T y ) {
	return y ? gcd ( y, x % y ) : x;
}
//<----------------------↑gcd↑---------------------->
//以下为dfs: u 表示目前遍历到的节点， fa 表示 u 节点的父亲节点， opt 表示从根节点走到 u 节点时有没有进行过修改， cur 表示的是当前状态下从根节点到父亲节点的 gcd 的最大值。
inline void dfs ( register int u, register int fa, register int opt, register int cur ) {
	if ( vis[u][opt][cur] ) {
		return ;
	} vis[u][opt][cur] = true;
	register int tmp = gcd < int > ( cur, w[u] );
	f[u] = max ( f[u], tmp );
	if ( opt == 0 ) {
		f[u] = max ( f[u], cur );
	} register int size = edge[u].size();
	for ( register int i = 0 ; i < size ; i ++ ) {
		register int v = edge[u][i];
		if ( v == fa ) {
			continue ;
		} dfs ( v, u, opt, tmp );
		if ( opt == 0 ) {
			dfs ( v, u, 1, cur );
		}
	}
}

signed main() {
	n = read < int > ();
	for ( register int i = 1 ; i <= n ; i ++ ) {
		w[i] = read < int > ();
	} for ( register int i = 1 ; i < n ; i ++ ) {
		register int u = read < int > (), v = read < int > ();
		edge[u].push_back ( v );
		edge[v].push_back ( u );
	} dfs ( 1, 0, 0, 0 );
	for ( register int i = 1 ; i <= n ; i ++ ) {
		write < int > ( f[i] );
		putchar ( ' ' );
	} putchar ( '\n' );
	return 0;
}

```

# $End$
# $NanyaOI$ 荣誉出品

---

## 作者：Seauy (赞：0)

~~没看出来记搜的复杂度是啥，那就讲个屑做法吧~~

# 一. 分析

我们可以获得所有数的因子，遍历到结点 $x$ 时累加到根路径上的所有数的因子的出现次数。如果结点 $x$ 深度为 $depth$，那出现了 $depth$ 与 $depth-1$ 次的因子是可以成为答案的因子，我们取这之中最大的。

获取因子的话可以 $O(n\sqrt a)$ 暴力找，或者调和级数预处理一下 $O(a \log a)$。我们又知道 $\max_{i=1}^{2\times 10^5} \tau(i)=160$，因此可以成为答案的因子数不会很多，暴力取 $\max$ 就可以做到 $O(n\tau(a))$。

这是为什么嘞，假设在 $x$ 的父亲上有两类因子，出现了 $depth-2$ 与 $depth-1$ 次的因子，最差的情况是 $x$ 的 $\tau (a)$ 个因子尽可能保留了父亲上可成为答案的因子，但我们知道出现了 $depth-2$ 次的因子一旦不在 $x$ 的因子中就再也不可能成为答案，因此保留下来的因子个数最多为 $O(\tau(a))$。

开个链表维护每个出现了 $i$ 次的因子集合 $S_i$ 就好了，用栈回收废弃的下标可以做到空间 $O(n+a)$。总复杂度最优可以做到 $O(a \log a + n\tau(a))$。

# 二. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=2e5,tou=160;

struct msg
{
	int lst,nxt;
	int data;
}Q[MAXN+5];
stack<int> recyc;

int n,A[MAXN+5];
int loc[MAXN+5],Head[MAXN+5];
vector<int> nxt[MAXN+5];
int mapn[MAXN+5],ans[MAXN+5];

void Insert(int x,int v)//将 v 插入 x 中 
{
	if(!x) return;
	loc[v]=recyc.top(),recyc.pop();
	Q[Head[x]].lst=loc[v];
	Q[loc[v]]=msg{-x,Head[x],v};
	Head[x]=loc[v];
}

void Delete(int v)
{
	if(!loc[v]) return;
	if(Q[loc[v]].lst<=0) Head[-Q[loc[v]].lst]=Q[loc[v]].nxt;
	else Q[Q[loc[v]].lst].nxt=Q[loc[v]].nxt;
	Q[Q[loc[v]].nxt].lst=Q[loc[v]].lst;
	recyc.push(loc[v]);
	loc[v]=0;
}

void Solve(int now,int fa,int depth)
{
	for(int i=1;i*i<=A[now];i++)
		if(A[now]%i==0)
		{
			Delete(i);
			Insert(++mapn[i],i);
			if(i*i<A[now])
			{
				int j=A[now]/i;
				Delete(j);
				Insert(++mapn[j],j);
			}
		}
	/*printf("now at %d\n",now);
	printf("factor an the val:\n");
	for(int i=1;i<=depth;i++)
	{
		for(int j=Head[i];j;j=Q[j].nxt) printf("%d ",Q[j].data);
		printf("\n");
	}*/
	for(int i=Head[depth];i;i=Q[i].nxt) ans[now]=max(ans[now],Q[i].data);
	if(depth>1)
		for(int i=Head[depth-1];i;i=Q[i].nxt)
			ans[now]=max(ans[now],Q[i].data);
	for(int i=0,rear;i<nxt[now].size();i++)
	{
		rear=nxt[now][i];
		if(rear==fa) continue;
		Solve(rear,now,depth+1);
	}
	for(int i=1;i*i<=A[now];i++)
		if(A[now]%i==0)
		{
			Delete(i);
			Insert(--mapn[i],i);
			if(i*i<A[now])
			{
				int j=A[now]/i;
				Delete(j);
				Insert(--mapn[j],j);
			}
		}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	for(int i=1,a,b;i<n;i++)
	{
		scanf("%d %d",&a,&b);
		nxt[a].push_back(b);
		nxt[b].push_back(a);
	}
	for(int i=1;i<=MAXN;i++) recyc.push(i);
	Solve(1,0,1);
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：ttq012 (赞：0)

**题目大意：**

给你一棵树，有 $n$ 个点，以 $1$ 为根，每一个点上有一个值。

现在定义一个点的美丽值为根到这一个点，所在路径上面的所有值的最大公约数。不过，你可以选择一个点，值变为 $0$，也可以什么也不做。

根节点的美丽值就是根节点的值。

每一个点的美丽值是独立的，不受影响。

现在要求你输出 $n$ 个数，代表每一个点最大可能的美丽值。

**思路**

先看一下数据范围

$1\le n\le 2\times 10^5$

$1\le a_i\le 2\times 10^5$

$1\le x, y\le n, x\neq y$

说明这道题目的时间复杂度不能超过 $O(N\log N)$ 这一个级别。

我们只维护当前点到根节点的所有信息。

定义 `dep` 是树的深度。

除了这一条路径的信息都不维护。

这一个是很容易做到的，我们进入这一子树的时候，把它加上，离开这一子树的时候，把它减掉就可以了。

然后为了求解最大公因数，我们将树上的每一个节点的值分解质因数，这样是不会超时的。

假设一个节点的值的质因数有 $v_1, v_2, \cdots, v_m$ 这一些质因数，那么我们将 `cnt[v1]++, cnt[v2]++, ..., cnt[vm]++`。

如果一旦有一个数 $x$，$cnt_x\ge dep-1$，那么就代表这一个因子可以成为这一条链上的一个因数了。

显然，最大的一个次数就是答案。

**代码实现**

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
int a[N];
int head[N], to[N], nxt[N], E;
int ret[N], cnt[N];

void add(int a, int b) // 加边函数，使用邻接表存储答案
{
    to[E] = b;
    nxt[E] = head[a];
    head[a] = E ++;
}

void dfs(int u, int f, int dep, int pre) // 深搜求答案函数
{
    int mx = -1;
    for (int i = 1; i * i <= a[u]; i ++) // 分解质因数
        if (a[u] % i == 0)
        {
            if (++ cnt[i] >= dep - 1)
            {
                ret[u] = max(ret[u], i);
                if (cnt[i] == dep)
                    mx = max(mx, i);
            }
            if (i != a[u] / i && ++ cnt[a[u] / i] >= dep - 1)
            {
                ret[u] = max(ret[u], a[u] / i);
                if (cnt[a[u] / i] == dep)
                    mx = max(mx, a[u] / i);
            }
        }
    for (int v = head[u]; ~v; v = nxt[v]) // 邻接表枚举
    {
        int q = to[v];
        if (q != f)
        {
            ret[q] = max(ret[q], mx);
            dfs(q, u, dep + 1, ret[u]);
        }
    }
    for (int i = 1; i * i <= a[u]; i ++)
        if (a[u] % i == 0)
        {
            -- cnt[i];
            if (i != a[u] / i)
                -- cnt[a[u] / i];
        }
}

int main()
{
    int n;
    cin >> n;
    memset(head, -1, sizeof head);
    for (int i = 1; i <= n; i ++)
        scanf ("%d", &a[i]);
    for (int i = 1; i < n; i ++)
    {
        int x, y;
        scanf ("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    dfs(1, 0, 1, a[1]);
    for (int i = 1; i <= n; i ++)
        printf ("%d%c", ret[i], " \n"[i == n]);
    return 0;
}

```



---

## 作者：极寒神冰 (赞：0)

说一个特别特别特别暴力的思路

1.先将每个点的点权因数分解（不是质因数

2.然后如果一条链上的某个因数的个数==dep-1的话，就是说这个数是这条链上所有（节点-1）个数的一个因数，可以更新这个点答案（因为本题可以删一个点）。如果==dep的话，说明这个数每一个数的一个因数，可以更新最大值。这样从下往上走，就能得出每一个数的答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+33;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int n;
vector<int>v[N];
struct  edge
{
	int nxt,to;
}e[N<<1];
int head[N],E;
int cnt[N],a[N],ans[N];//cnt统计目前这条链上每个因数出现次数 ans[i]表示i节点答案
inline void init()
{
	E=0;
	memset(head,-1,sizeof(head));
}
inline void add_edge(int u,int v)
{
	e[++E].to=v;
	e[E].nxt=head[u];
	head[u]=E;
}
inline void dfs(int u,int f,int dep)
{
	int mx=0;
	for(int i=0;i<v[u].size();i++)
	{
		++cnt[v[u][i]];//统计因数
		int tmp=cnt[v[u][i]];
		if(tmp>=dep-1)//更新每个点的最大值
		{
			ans[u]=max(ans[u],v[u][i]);
			if(tmp==dep) mx=max(mx,v[u][i]);
		}
	}
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v!=f)
		{
			ans[v]=max(ans[v],mx);
			dfs(v,u,dep+1);
		}
	}
	for(int i=0;i<v[u].size();i++)
	{
		--cnt[v[u][i]];
	}
}

int main()
{
	init();
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		for(int j=1;j*j<=a[i];j++)
		{
			if(a[i]%j==0)
			{
				v[i].push_back(j);
				if(j!=a[i]/j)v[i].push_back(a[i]/j); //因数分解
			}
		}
	}
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		add_edge(x,y),add_edge(y,x);
	}
	dfs(1,0,1);
	for(int i=1;i<=n;i++)
	{
		cout<<ans[i]<<" ";
	}
}
```


---

