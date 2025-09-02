# Sum Balance

## 题目描述

Ujan has a lot of numbers in his boxes. He likes order and balance, so he decided to reorder the numbers.

There are $ k $ boxes numbered from $ 1 $ to $ k $ . The $ i $ -th box contains $ n_i $ integer numbers. The integers can be negative. All of the integers are distinct.

Ujan is lazy, so he will do the following reordering of the numbers exactly once. He will pick a single integer from each of the boxes, $ k $ integers in total. Then he will insert the chosen numbers — one integer in each of the boxes, so that the number of integers in each box is the same as in the beginning. Note that he may also insert an integer he picked from a box back into the same box.

Ujan will be happy if the sum of the integers in each box is the same. Can he achieve this and make the boxes perfectly balanced, like all things should be?

## 说明/提示

In the first sample, Ujan can put the number $ 7 $ in the $ 2 $ nd box, the number $ 2 $ in the $ 3 $ rd box, the number $ 5 $ in the $ 1 $ st box and keep the number $ 10 $ in the same $ 4 $ th box. Then the boxes will contain numbers $ \{1,5,4\} $ , $ \{3, 7\} $ , $ \{8,2\} $ and $ \{10\} $ . The sum in each box then is equal to $ 10 $ .

In the second sample, it is not possible to pick and redistribute the numbers in the required way.

In the third sample, one can swap the numbers $ -20 $ and $ -10 $ , making the sum in each box equal to $ -10 $ .

## 样例 #1

### 输入

```
4
3 1 7 4
2 3 2
2 8 5
1 10
```

### 输出

```
Yes
7 2
2 3
5 1
10 4
```

## 样例 #2

### 输入

```
2
2 3 -2
2 -1 5
```

### 输出

```
No
```

## 样例 #3

### 输入

```
2
2 -10 10
2 0 -20
```

### 输出

```
Yes
-10 2
-20 1
```

# 题解

## 作者：Chaigidel (赞：4)

$k$ 这么小肯定是指数算法 ~~然后 n 太大不会做~~

考虑一个数被拿出来一定会有另一个数被替换，而另一个数是确定的

把数看成节点，每个节点有一条或没有出边

于是就转换成了一个图论问题

当图上有环的时候，并且这些数属于**不同的**盒子时，这几个盒子就能一起选上

于是变成了一个内向基环树找环的问题，加上一个人人都会的状压

```cpp
#include <bits/stdc++.h>
#define R(i, r) for (int i = 0; i < (r); ++i)
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, l, r) for (int i = (l); i >= (r); --i)
using std::cerr; using std::cin; using std::cout; using std::endl;
using std::make_pair; using std::pair; typedef pair<int, int> pii;
typedef long long ll; typedef unsigned int ui; typedef unsigned long long ull;
 
const int K = 15, N = 5010;
 
int n[K]; ll a[K][N], sig[K];
std::map<ll, pii> s;
pii g[K][N]; int clr[K][N];
int f[1<<K], from[1<<K];
pii plan[1<<K]; int origin[1<<K]; pii out[K];
 
void dfs(int state){
    if (origin[state]){
        int x = plan[state].first, y = plan[state].second;
        pii n;
        do {
            n = g[x][y];
            out[n.first] = {a[n.first][n.second], x};
            x = n.first, y = n.second;
        } while(x != plan[state].first);
    } else {
        dfs(from[state]);
        dfs(state^from[state]);
    }
}
 
int main() {
#ifdef LOCAL
    freopen("input", "r", stdin);
#endif
    std::ios::sync_with_stdio(0); cout.tie(0);
    int k; cin >> k; ll avg = 0;
    R(i, k){
        cin >> n[i];
        R(j, n[i]){
            cin >> a[i][j];
            sig[i] += a[i][j];
            s[a[i][j]] = {i,j};
        }
        avg += sig[i];
    }
    if (avg % k != 0){ cout << "No"; return 0; }
    avg /= k;
    R(i, k) R(j, n[i]){
        ll x = avg - sig[i] + a[i][j];
        if (s.count(x)) g[i][j] = s[x];
        else g[i][j].first = -1;
    }
    int x, y, state, flag; pii np; int cnt = 0;
    R(i, k) R(j, n[i]){
        if (clr[i][j]) continue;
        x = i, y = j;
        clr[x][y] = ++cnt;
        while(g[x][y].first != -1){
            np = g[x][y]; x = np.first, y = np.second;
            if (clr[x][y] == cnt){
                state = 0, flag = 1;
                int ox = x, oy = y;
                do {
                    if (state&(1<<x)) { flag = 0; break; }
                    state |= (1<<x);
                    np = g[x][y];
                    x = np.first, y = np.second;
                } while(x != ox || y != oy);
                if (flag) f[state] = origin[state] = 1, plan[state] = {x, y};
                break;
            } else if (clr[x][y] != 0) break;
            clr[x][y] = cnt;
        }
    }
    f[0] = 1;
    for(int i = 1; i < (1<<k); ++i){
        for(int j = i; j && !f[i]; j = ((j-1)&i)){
            if (f[j] && f[i^j]){
                f[i] = 1;
                from[i] = j;
            }
        }
    }
    if(!f[(1<<k)-1]){ cout << "No"; return 0; }
    cout << "Yes\n";
    dfs((1<<k)-1);
    R(i, k){
        cout << out[i].first << ' ' << out[i].second+1 << endl;
    }
    return 0;
}
```

---

## 作者：intel_core (赞：3)

简要题意：有 $k$ 个盒子，每个盒子里有一些数；你要从每个盒子里取出一个数，然后可以将它们放进另一些盒子里（每个盒子里最多只能放回去一个数）。问能不能一次操作之后让所有盒子里的数的和相等。

如果所有数的和不是 $k$ 的倍数，显然不行。

否则求出相等的时候每个盒子里的数的和应该是多少。

对于盒子里的每一个数，如果拿出去的是这个数，那么满足要求拿进来的数只有一个。

这样我们就可以建出一个有向图，每个点指向替换它的那个数。

题目求得是一个合法的置换，置换可以拆成若干个轮换；所以我们把建出的有向图里的所有环找出来。

对于一个环，如果上面有两个在同一个盒子里的数，直接扔掉不管。

对于剩下的环，处理环上有哪些盒子里的数，压进 $S$ 里。

显然，我们要选出若干个环，这些环上的数所属的盒子两两不同，并且每个盒子中都有数在这些环上。

可以状压 $\text{DP}$ 做，复杂度 $O(n+2^k)$。

---

## 作者：Sqrtyz (赞：3)

### 题意

有 $k$ 个盒子，每个盒子里有一堆数，第 $i$ 堆有 $n_i$ 个数，所有盒子的数都互不相同。
你现在需要从每个盒子里拿出一个数，打乱后再每个盒子放回去一个。问是否有方案使得最后每个盒子里的数的和相等？如果有同时还需要给出方案。

+ $k\leq 15, n_i \leq 5000$，数字大小的绝对值在 $10^9$ 以内。

### 解题

首先我们显然可以证明，从某个盒子取出一个数字 $x$，那么再放入这个盒子的数字 $y$ 是一定的，毕竟所有盒子的数都互不相同。

那么显然第一反应可能有这么一个思路：我先确定一个必须要换数字的盒子，枚举取出的数字 $x$，然后就可以得出放入的数字 $y$。紧接对于那个 $y$ 所在的盒子，被取出了一个 $y$，那么肯定还要放入一个数字 $z$。而这些都是可以求出的，最后形成一个「环」回到 $x$，说明找到了一种方案。

我开始也是这么想的，这样的思路其实已经接近正解，然而我们忽略了一个问题——这样的「环」可能存在多个，于是我们必须要把这道题转换成一个便于解决的图论模型。

考虑对于每个数字建一个点，然后连向另外一个与之匹配的点（就像刚才的 $x$ 和 $y$ 那样匹配：我取出了这个数字后，就要再向它所在的盒子里装一个确定的数字）。这样大约会形成一个有 $N$ 个点 $N$ 条边的图。显然，这是一个由内向树和树组成的一个乱七八糟的森林。我们现在要把其中的环揪出来，可以使用拓扑或 tarjan，在此不再赘述。

`update：菜鸟笔者发现其实不用那么麻烦找环，鉴于它是有向图直接遍历就好了……`

把环找出来后仍有一个问题——我们要保证所有的箱子里都取出了数字（对于不用取数字的箱子，我们可以视为取出来又放回去），而每一个环可能只对应了若干个箱子，还可能有重复。

这时注意到数据范围 $k \leq 15$，显然想到状态压缩。我们把每个环涉及到的箱子压成一个最多仅 $15$ 位的二进制数，其中涉及到的箱子那一位就为 $1$。

为了方便表述，我们暂时定义仅一个环状压后的称为“基础箱子序列”，一个或多个环状压后的为“箱子序列”。

由于只需要给出任意一种方案，现在我们只需要解决：如何把不同的环对应的基础箱子序列拼凑在一起，形成一个更大的合并的箱子序列，最后得到一个 $k$ 位全是 $1$ 的二进制串（即所有箱子都取出又放回了数字）。

开始想到了爆搜，但这样复杂度最坏会达到 $15!$，不能接受。因此考虑使用 dp 优化。

我们在第一维枚举状态（箱子序列），第二维枚举它的子集。我们现在只需要考虑这个第一维的箱子序列能否由第二维的子集和它在第一维箱子序列下的补集拼凑而成，注意此时子集和补集都已经在第一维被枚举过了。

显然写出 dp 方程：其中 $f[i]$ 有值当且仅当 $i$ 是基础箱子序列，$vis[i]$ 有值当且仅当 $i$ 是箱子序列。
```cpp
for(int i = 0; i < (1 << K); ++i) {
		if(f[i]) vis[i] = 1;
		for(int j = i; j; j = (j - 1) & i) {
			if(vis[j] && vis[i ^ j]) {
				vis[i] = 1;
				bef[i] = j;
			}
			if(vis[i]) break;
		}
	}
```
$bef$ 数组存储了当前箱子序列 $i$ 的一个子集，便于之后的输出。

输出方案部分，只需要递归处理。如果当前 $f[i]$ 有值，说明是基础箱子序列，就要把它对应的环的信息处理后输出。如果没有值，说明这个箱子序列是合并出来的，根据 $bef$ 数组递归解决即可。细节参见代码。

### 程序

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>

#define Maxk 16
#define Maxn 750010
#define LL long long

using namespace std;

int read() {
	int x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-') f = -1;
		c = getchar();
	}
	while('0' <= c && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

LL K, N, tot, sum[Maxk];
LL deg[Maxn], f[1 << Maxk], bef[1 << Maxk];
bool vis[1 << Maxk];

struct Edge {
	int next, to;
}
edge[Maxn];
int head[Maxn], edge_num;

struct Point {
	LL val, bel;
}
point[Maxn];
map <LL, LL> check;

void add_edge(int from, int to) {
	edge[++edge_num].next = head[from];
	edge[edge_num].to = to;
	head[from] = edge_num;
}

void fl(int first, int u, int sta) {
	if(u == first && !deg[u]) {f[sta] = first; return;}
	deg[u] = 0;
	int nowu = 1 << (point[u].bel - 1);
	if(sta & nowu) return;
	fl(first, edge[head[u]].to, sta | nowu);
}

int stack[Maxn], top;
void topsort() {
	for(int i = 1; i <= N; ++i) if(!deg[i]) stack[++top] = i;
	while(top) {
		int u = stack[top--];
		int v = edge[head[u]].to;
		--deg[v];
		if(!deg[v]) stack[++top] = v;
	}
	for(int i = 1; i <= N; ++i) if(deg[i]) fl(i, i, 0);
}

LL out1[Maxk], out2[Maxk];

void output(int sta) {
	if(f[sta]) {
		int u = f[sta];
		while(true) {
			int v = edge[head[u]].to;
			out1[point[v].bel] = point[v].val;
			out2[point[v].bel] = point[u].bel;
			u = v;
			if(u == f[sta]) break;
		}
	}
	else {
		output(bef[sta]);
		output(sta ^ bef[sta]);
	}
}

int main() {
	K = read();
	LL size, val;
	for(int i = 1; i <= K; ++i) {
		size = read();
		for(int j = 1; j <= size; ++j) {
			val = read();
			point[++N].val = val, point[N].bel = i;
			sum[i] += val, tot += val; 
		}
	}
	if(tot % K) {printf("No"); return 0;}
	else tot = tot / K;
	for(int i = 1; i <= N; ++i) check[point[i].val] = i;
	for(int i = 1; i <= N; ++i) {
		int u = i, v = check[tot - sum[point[i].bel] + point[i].val];
		if(!v) continue;
		add_edge(u, v); ++deg[v];
	}
	topsort();
	for(int i = 0; i < (1 << K); ++i) {
		if(f[i]) vis[i] = 1;
		for(int j = i; j; j = (j - 1) & i) {
			if(vis[j] && vis[i ^ j]) {
				vis[i] = 1;
				bef[i] = j;
			}
			if(vis[i]) break;
		}
	}
	if(vis[(1 << K) - 1]) {
		printf("Yes\n");
		output((1 << K) - 1);
		for(int i = 1; i <= K; ++i) printf("%lld %lld\n", out1[i], out2[i]);
	}
	else printf("No");
	return 0;
}
```

可能有人会认为我把一个简单的题目说的比较繁琐，或许吧，不过我认为记录思维的每一点滴何尝不好呢？

---

## 作者：WaterSun (赞：2)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18410221)

妙妙题。

# 思路

注意到题目保证了 $a_i$ 互不相同，所以一个数被踢出一个箱子，最多只能找到一个数加进去满足条件。

考虑直接建图。令最终每个箱子的和为 $num$，第 $i$ 个箱子原来的和为 $sum_i$。

则从一个箱子 $i$ 从选出了一个数 $x$，那么只有把 $y = num - (sum_i - x)$ 从**其他**集合加进来才有可能使得方案合法。然后建一条 $y \to x$ 的边。

观察到在建出的图上，一个环，对应的一个合法的交换方案。但是需要判掉一个环上出现了多个相同箱子的环。

事实上，这是一个内向基环树森林，但是我写的时候并没有注意到，所以我找环写的 tarjan。

然后把每一个环对应的箱子编号状压一下，DP 一下即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define fst first
#define snd second
#define int long long
#define chmin(a,b) (a = min(a,b))

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> pii;
const int N = 24,M = (1 << 15) + 10;
int n,num,tim;
int sum[N];
bool ok[M],pre[N];
vector<pii> dp[M];
vi s[N];
stack<int> st;
unordered_map<int,int> id,dfn,low;
unordered_map<int,bool> vis;
unordered_map<int,vi> g;

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void tarjan(int u){
    dfn[u] = low[u] = ++tim;
    vis[u] = true; st.push(u);
    for (int v:g[u]){
        if (!dfn.count(v)){
            tarjan(v); chmin(low[u],low[v]);
        }
        else if (vis.count(v) && vis[v]) chmin(low[u],dfn[v]);
    }
    if (dfn[u] == low[u]){
        int x,tmp = 0,sz = 0;
        bool falg = true;
        vector<int> pt;
        fill(pre + 1,pre + n + 1,false);
        do{
            x = st.top(); st.pop(); sz++;
            if (pre[id[x]]) falg = false;
            pre[id[x]] = true; vis[x] = false;
            tmp |= (1 << (id[x] - 1));
            pt.push_back(x);
        }while (x != u);
        if (sz > 1 && falg && !ok[tmp]){
            ok[tmp] = true;
            pt.push_back(pt.front());
            for (re int i = 1;i < pt.size();i++) dp[tmp].push_back({pt[i],id[pt[i - 1]]});
        }
    }
}

signed main(){
    n = read();
    for (re int i = 1,len;i <= n;i++){
        len = read();
        while (len--){
            int x; x = read();
            s[i].push_back(x);
            id[x] = i;
            num += x; sum[i] += x;
        }
    }
    if (num % n) return puts("No"),0;
    num /= n;
    for (re int i = 1;i <= n;i++){
        for (int x:s[i]){
            int y = num - (sum[i] - x);
            if (id.count(y)){
                if (id[y] != i) g[y].push_back(x);
                else if (x == y && !ok[1 << (i - 1)]){
                    ok[1 << (i - 1)] = true;
                    dp[1 << (i - 1)].push_back({x,i});
                }
            }
        }
    }
    for (re int i = 1;i <= n;i++){
        for (int x:s[i]){
            if (!dfn.count(x)) tarjan(x);
        }
    }
    ok[0] = true;
    for (re int sti = 1;sti < (1 << n);sti++){
        if (ok[sti]) continue;
        for (re int stj = sti;stj;stj = (stj - 1) & sti){
            if (ok[stj] && ok[sti - stj]){
                ok[sti] = true;
                for (pii x:dp[stj]) dp[sti].push_back(x);
                for (pii x:dp[sti - stj]) dp[sti].push_back(x);
                break;
            }
        }
    }
    const int stn = (1 << n) - 1;
    if (ok[stn]){
        puts("Yes");
        sort(dp[stn].begin(),dp[stn].end(),[](const pii &a,const pii &b){
            return id[a.fst] < id[b.fst];
        });
        for (pii x:dp[stn]) printf("%lld %lld\n",x.fst,x.snd);
    }
    else puts("No");
    return 0;
}
```

---

## 作者：FiraCode (赞：2)

## 题解思路：
无解情况：

>所有的价值和不是 $k$ 的倍数那么他就无解。

我们发现每个合法都是一个环。

那么我们就可以用二进制表示。

然后我们就看这些二进制能否构成全一串就可以了。

具体怎么做：
> 首先判断是否有解，即他们的价值和 $\mod k = 0$。

>预处理环。

>状压 dp $\longrightarrow$ 二进制全 $1$。

## AC CODE:
```cpp
#include <cstring>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
ll sum[15];
vector <int> a[15];
map <ll , pair <int , int>> mp;
bool vis[1 << 15] , dp[1 << 15];
vector <pair <pair<int , int> , int>> mark[1 << 15];
int pre[1 << 15];
pair <int , int> ans[15];
int main() {
    int k;
    scanf ("%d" , &k);
    ll v = 0;
    for (int i = 0; i < k; ++ i) {
        int n;
        scanf ("%d" , &n);
        a[i].resize (n);
        for (int j = 0; j < n; ++ j) {
            scanf ("%d" , &a[i][j]);
            sum[i] += a[i][j];//sum[i]第i组的和
            mp[a[i][j]] = {i , j};//i组j个
        }
        v += sum[i];//总和 
    }
    if (v % k != 0) return puts("No") , 0;//无解
    v /= k;//分成k个小段，每段的和
    for (int i = 0; i < k; ++ i) {//预处理环
        for (int j = 0; j < a[i].size(); ++ j) {
            ll cur = a[i][j];//枚举a[i][j]，复杂度15×5000
            int now = 0;//现在的状态
            bool ok = true;
            vector <pair<pair <int , int> , int>>b;
            while (1) {
                int y = mp[cur].first;//用map记录
                cur = v - sum[y] + cur;//他对应的值：sum[i]+a[i][j]+?=v,我们已知：sum[i],v,
                if (!mp.count(cur)) {
                    ok = false;
                    break;
                }
                auto x = mp[cur];
                if (now & (1 << x.first)) {
                    ok = false;
                    break;
                }
                now |= (1 << x.first);
                b.push_back ({{x.first , x.second} , y});
                if (x.first == i) {//一直往前找，又回到了期点，有环
                    if (x.second != j) ok = false;
                    break;
                }
            }
            if (ok) {
                vis[now] = true;
                mark[now] = b;
            }
        }
    }
    dp[0] = 1;
    for (int s = 0; s < (1 << k); ++ s) {//枚举子集，状压DP
        for (int ns = s; ns; ns = (ns - 1) & s)
            if (vis[ns] && dp[s ^ ns]) {
                dp[s] = 1;
                pre[s] = ns;
                break;
            }
    }
    if (!dp[(1 << k) - 1]) return puts("No") , 0;//没有全1那么也无解
    int s = 1 << k;
    -- s;
    while (s) {
        for (auto &x : mark[pre[s]]) {
            ans[x.first.first] = {a[x.first.first][x.first.second] , x.second};
        }
        s ^= pre[s];
    }
    puts("Yes");
    for (int i = 0; i < k; ++ i)
        printf ("%d %d\n" , ans[i].first , ans[i].second + 1);
    return 0;
}
```
码字不易，求赞！

---

## 作者：红黑树 (赞：1)

**关键性质：在所有的数中，每种权值的出现次数不会 $>1$。**

首先计算出最终每个集合如果是平分的话那么它对应的单个集合内元素之和 $sum$。我们对于每个集合 $i$，考虑其中的每个元素 $a_{i,j}$，如果集合 $i$ 中删掉的是 $a_{i,j}$ 的话，得补进来一个什么数，才能使最终 $i$ 集合内元素和为 $sum$。显然有这个 $w=sum-\sum\limits_{k}a_{i,k}+a_{i,j}$。也就是说，如果 $i$ 集合删掉了 $a_{i,j}$，那么就得给它放入 $w$。

我们记 $b_i$ 表示数 $i$ 一开始所属的集合编号，如果 $i$ 在所有集合中没有出现，那么 $b_i=0$。此时我们考虑 $a_{i,j}\to w$。我们发现，最终我们的构造应该是由若干个简单环组成的。

再理一遍，实际上我们是考虑了这样一个建模：如果最后将集合 $i$ 加入了集合 $j$ 拿出去的那个数，那么 $i\to j$。实际上由于每个点唯一，并且每个点出度 $=1$，你会发现，合法的解最终对应了若干个不交简单环。

那么我们对于这些元素建出来的图，我们要考虑其中的所有简单环。一个简单环可以被选择，当且仅当它满足上面没有原所属集合相同的数。然后我们将这些元素的所属集合编号记为一个集合 $s$。也就是说，选择这个集合的话，可以将 $s$ 内的集合配成 $sum$。

怎么找出这些简单环？考虑到元素是不会重复出现的，所以每个点出度最多为 $1$，这构成了一个这样形态的内向基环树森林。

![](https://z1qqur.at/usr/uploads/2024/09/1409674586.png)

（只由单链后面接一个环的形态的内向基环树组成的森林，单链和环的长度也都可以为 $0$）。

我们考虑找环，tarjan 找环一定是没必要的。可以考虑删掉这些单链的部分，那么剩下的就都是环了。用一个类似于拓扑排序的东西维护，每次删掉入度为 $0$ 的点和它的出边。最终剩下的肯定都是简单环，从每个环上任意找一个点开始走出边 dfs 整个环就好了。

接下来再考虑知道了哪些编号集合 $s$ 可以被一个简单环凑出之后，我们考虑子集 dp，记 $f_s$ 表示集合 $s$ 内的编号能否被若干个简单环不交地凑出。转移直接枚举子集，并且合并方案构造就好了。复杂度 $\mathcal{O}\left(kn\log kn+3^k\right)$，其中带一个 $\log$ 是因为我用 map 维护了元素 $a_{i,j}$。这样也方便删边等转移。

```cpp
int WITHERING([[maybe_unused]] unsigned long long int TEST_NUMBER) {
   tp n, sum = 0; cin >> n;
   vector<tp> m(n + 1, 0);
   vector<vector<tp>> a(n + 1, vector<tp>(5002, 0));
   unordered_map<tp, tp> b, to, in;
   for (tp i = 1; i <= n; ++i) {
      cin >> m[i];
      for (tp j = 1; j <= m[i]; ++j)
         cin >> a[i][j], sum += a[i][j], b[a[i][j]] = i;
   }
   sum /= n;
   for (tp i = 1; i <= n; ++i) {
      tp cur = 0;
      for (tp j = 1; j <= m[i]; ++j) cur += a[i][j];
      for (tp j = 1; j <= m[i]; ++j) {
         tp w = sum - cur + a[i][j];
         if (b.find(w) != end(b)) to[a[i][j]] = w, in[w]++;
      }
   }

   queue<tp> q;
   for (auto [u, v] : to)
      if (!in[u]) q.emplace(u);
   while (!q.empty()) {
      tp u = q.front(); q.pop();
      tp v = to[u]; to.erase(u);
      if (!(--in[v])) q.emplace(v);
   }
   unordered_map<tp, bool> vis;
   vector<bool> f(1 << n, 0);
   vector<vector<tuple<int, int, int>>> g(1 << n);
   for (auto [u, v] : to) {
      if (vis[u] || !in[u]) continue;
      vector<tp> p;
      while (!vis[v]) {
         p.emplace_back(v);
         if (v == u) {
            tp s = 0;
            for (auto w : p) {
               tp i = 1 << b[w] - 1;
               if (s & i) { s = 0; break; }
               s |= i;
            }
            if (s && !f[s]) {
               f[s] = 1;
               for (auto w : p) g[s].emplace_back(b[to[w]], to[w], b[w]);
            }
            break;
         }
         vis[v] = 1;
         if (to.find(v) != end(to)) v = to[v];
         else break;
      }
      vis[u] = 1;
   }

   for (tp s = 1; s < 1 << n; ++s) {
      for (tp t = s & (s - 1); t; t = s & (t - 1)) {
         if (f[t] && f[s - t]) {
            f[s] = 1, g[s] = g[t];
            for (auto u : g[s - t]) g[s].emplace_back(u);
         }
      }
   }
   if (!f[(1 << n) - 1]) return cout << "No\n", 0;
   cout << "Yes\n";
   sort(FULL(g[(1 << n) - 1]));
   for (auto [i, w, j] : g[(1 << n) - 1]) cout << w << ' ' << j << "\n";
   return 0;
}
```

---

## 作者：black_trees (赞：1)


## 题意

有 $k$ 个盒子，每个盒子里面有 $n_i$ 个绝对值小于 $10^9$ 的数（所有数互不相同）。

要求从每个盒子里拿出**刚好一个**元素，将其放入任意的一个盒子当中（可以是自己），并且每一个盒子只会新放入**一个**元素。

问你是否有可能让每一个盒子里的数的和都相等，并给出方案。

## 题解

首先我们可以发现，每一个盒子都只会拿出一个，得到一个，也就是说每个盒子里的元素个数是不变的。

设拿走的元素是 $x$ ，放进来的是 $y$ 。

我们要改变一个盒子的元素之和，就只能靠 $y-x$ 来改变。

而题目里保证不会有重复出现的数。所以对于每一个盒子，如果你拿走的 $x$ 固定，那么想要有解的话，它对应的 $y$ 也应该是固定的。

并且因为元素不会删除或者添加，所以所有元素之和是不变的，也就是，我们要让每一个盒子的和最终变成的那个数 $Goal$ 是固定不变的。

所以说对于每一个数都**可能**存在一对 $x\to y$ 的对应关系。

我们就可以很容易的想到，可以利用有向图来维护这样的关系。

简单来说，对于每一个数字 $x$，我们让他变成一个图上的节点，

并令他连向一个数 $y$ 对应的节点，满足 $x$ 所在的盒子的元素和加上 $y-x$ 能等于 $Goal$。

如果不存在这样的节点 $y$ ，我们令他连向一个实际上不存在的点 $nil$ ，表示没法找到一个可以满足条件的 $y$。 

很明显，因为数是互不相同的，所以每一个点的出度一定为 $1$。

当然，连完边之后是可以出现自环的（比如下面的样例）

手搓一下样例：

[![53TvVJ.png](https://z3.ax1x.com/2021/10/15/53TvVJ.png)](https://imgtu.com/i/53TvVJ)

除去和 $nil$ 相连的节点，你会发现，这实际上是一个内向树森林。

再观察一下输出：

```
Yes
7 2
2 3
5 1
10 4
```

你会很容易发现，答案是由刚好包含每个盒子里的某一个元素的多个环组成的。

就是说，每一个盒子里有且仅有一个节点在这些环上。

因为如果关系构成一个环，那么证明环上的节点能够相互使对方的盒子当中的元素之和等于 $Goal$。

所以，我们就只需要找到几个能满足条件的环就行了。

发现题目给的 $k$ 是 $\le 15$ 的。

并且我们需要的是每个盒子里**只有一个**元素在这些环上。

所以我们可以考虑状压 DP 。

因为盒子只有 $15$ 个，所以环也最多只有 $15$ 个。

用一个二进制数来表示你当前已经满足条件的盒子的状态。

我们设 $f_{msk}$ 表示当你处理到的盒子的状态是 $msk$ 的时候的**方案** （注意是方案，所以我们直接利用 `vector` 记录即可）。

然后我们对于一个**不满足条件**，也就是二进制下有至少一位不是 $1$ 的状态 $msk$ ，我们考虑去找它的补集。

具体来说，我们枚举另外的一个状态 $msk^\prime$ ，看 $\complement_{msk}$ 是不是 $msk^\prime$ 的子集即可。

如果有重复出现同一个盒子里的不同元素，我们就需要排除掉枚举出来的状态 $msk^\prime$。

最后对 $f_{2^k-1}$ 排个序输出就好了。

Code:

```cpp

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define ld long double
#define pii pair<int,int>
#define fr first
#define sc second
#define pb push_back
#define mk make_pair

constexpr int boxsi=20;
constexpr int stasi=(1<<16);
int k,n[boxsi];
int Sum=0,sum[boxsi],Goal;
// bitset<stasi>vis;
bool vis[stasi];
vector<pii>f[stasi];
unordered_map<int,int>rec;
set<int>S,Fr; 

signed main(){
    auto comp=[&](pii a,pii b)->bool{ return rec[a.fr]<rec[b.fr];};
    auto Go=[&](int x)->int{ return x+Goal-sum[rec[x]];};
    scanf("%lld",&k);
    for(register int i=1;i<=k;++i){
        scanf("%lld",&n[i]);
        for(register int j=1,rmp;j<=n[i];++j){
            scanf("%lld",&rmp);
            rec[rmp]=i,Sum+=rmp,sum[i]+=rmp;
        }
    }
    Goal=Sum/k;
    if(Sum%k) return puts("No"),0; //明显无解，直接特判。
    for(auto x:rec){
        register int i=x.fr;
        while(rec.find(i)!=rec.end() && S.find(i)==S.end() && Fr.find(i)==Fr.end()){
            Fr.insert(i),i=Go(i);
        }
        bool fa=false;
        if(Fr.find(i)!=Fr.end()){
            vector<pii>lep;
            register int j=i,msk=0;
            do{int to=Go(i);
               lep.pb(mk(to,rec[i]));
               if(msk&(1<<(rec[i]-1))) fa=true;
               msk^=(1<<(rec[i]-1)),i=to;
            }while(i!=j);
            if(!fa && !vis[msk]) f[msk]=lep,vis[msk]=true;
        }
        for(auto y:Fr) S.insert(y);
        Fr.clear();
    }
    for(register int msk=1;msk<(1<<k);++msk){
        if(!vis[msk]){
            for(register int i=msk;i>0;i=(i-1)&msk){
                if(vis[i] && vis[msk-i]){
                    vis[msk]=true;
                    for(auto x:f[i]) f[msk].pb(x);
                    for(auto x:f[msk-i]) f[msk].pb(x);
                    break;
                }
            }
        }
    }
    if(!vis[(1<<k)-1]) return puts("No"),0;
    else{
        puts("Yes");
        vector<pii>ans=f[(1<<k)-1];
        sort(ans.begin(),ans.end(),comp);
        for(auto x:ans){
            printf("%lld %lld\n",x.fr,x.sc);
        }return 0;
    }
}
```

---

## 作者：Fantasy_Segment_Tree (赞：0)

每个数被移出后肯定会需要移进一个数。这个数就是 $\frac{tot}{k} - sum_i + x$。从移出的数到移进的数连一条有向边，则整个图就是一个基环树森林。

把每个基环树的环找出来，然后把环上的点全部拆出，组合成一个二进制数。枚举子集，进行状压 dp，最后判断 $2^k - 1$ 这个状态就可以了。

注意：实际实现中并不用找环，只要从每一个数开始不停地遍历，遍历回它自己就找到环了。

代码写得挺清楚的，可以看代码中的注释。（请勿抄袭！！）

```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

long long k, cnt, cntt, sum = 0, vit[1 << 20], siz[20], su[20], S[20], p2[20] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768}, num[20][5005], dp[1 << 20];
unordered_map <long long, long long> p, vis, viss;


vector <pair <long long, long long> > SS[1 << 20];
vector <long long> xp;
long long pp[20];

bool cmp(pair <long long, long long> x, pair <long long, long long> y) {
	return p[x.first] < p[y.first];//按照所在集合排序 
}

int main() {
	cin >> k;
	for(long long i = 1; i <= k; i++) {
		long long x;
		cin >> siz[i];
		for(long long j = 1; j <= siz[i]; j++) {
			cin >> x;
			num[i][j] = x;
			if(!p.count(x)) p[x] = i;//记录节点 x 所在集合 
			su[i] += x;//计算某个集合中的数的总和 
			sum += x;//总和 
		}
	}
	if(sum % k) {//很明显无法相等 
		cout << "No";
		return 0;
	}
	sum /= k;
	long long t = 0;
	for(long long i = 1; i <= k; i++) {
		for(long long j = 1; j <= siz[i]; j++) {
			if(!viss.count(num[i][j])) {//不能已经被加入环中的再遍历 
				xp.clear();
				t++;
				long long x = num[i][j], flag = 1;
				while(p.count(x) && (flag || x != num[i][j])) {//如果找到空点或找到环直接退出 
					xp.push_back(x);
					if(vis[p[x]] == t) break;//一个环中每个集合的数只能出现一次，若出现多次，则环不合法 
					vis[p[x]] = t;
					x = sum - (su[p[x]] - x);//对 x 进行转移 
					flag = 0;
				}
				
				if(x == num[i][j]) {//记录环 
					long long sum2 = 0;
					long long ppp = xp.size();
					cntt++;
					xp.push_back(xp[0]);
					for(long long i = 0; i < ppp; i++) sum2 += p2[p[xp[i + 1]] - 1];//计算环所对应的二进制数，第 i 个集合对应的倍率为 2^i - 1 
					if(!vit[sum2]) {//如果没有相同的环 
						vit[sum2] = 1;
						for(long long i = 0; i < ppp; i++) viss[xp[i]] = 1, SS[sum2].push_back(make_pair(xp[i + 1], p[xp[i]]));//把环的信息按照题目的输出格式记录，并将环中的点进行标记，以免再次访问					}
					}
			}
		}
	}
	for(long long i = 0; i < (1 << k); i++) {//状压 dp 
		if(vit[i]) continue;
		for(long long j = i; j > 0; j = (j - 1) & i) {//枚举子集 
			if(vit[j] && vit[i - j]) {//合法 
				vit[i] = 1;
				for(long long tr = 0; tr < SS[j].size(); tr++) SS[i].push_back(SS[j][tr]);//将子集信息记录进本集 
				for(long long tr = 0; tr < SS[i - j].size(); tr++) SS[i].push_back(SS[i - j][tr]);//将子集信息记录进本集 
				break;//只需要记录一次 
			}
		}
	}
	if(vit[(1 << k) - 1]) {//若所有节点都被访问，则输出 Yes 
		cout << "Yes\n";
		sort(SS[(1 << k) - 1].begin(), SS[(1 << k) - 1].end(), cmp);//按照原来所在集合排序 
		for(long long i = 0; i < SS[(1 << k) - 1].size(); i++) cout << SS[(1 << k) - 1][i].first << " " << SS[(1 << k) - 1][i].second << endl;
	} else cout << "No";
}
```

---

## 作者：lsj2009 (赞：0)

> <https://codeforces.com/problemset/problem/1242/C>。
>
> 给定 $k$ 个序列，每个序列有 $n_i$ 个元素，要求从每个序列中取出一个元素，然后按某种顺序丢到另一个序列里面（每个序列恰好丢一个，操作完后序列长度不变）。
>
> 问是否存在一种方案使得操作后各个序列元素之和相同，如果存在，请构造出一组解。
>
> $k\le15$，$n_i\le5000$，$|V|\le 10^9$，所有元素均不相等。

比较套路的建图。

首先算出操作后每个序列的值，即所有元素的平均值，记为 $avg$。

则如果我们从第 $i$ 个序列当中取出 $x$，则我们就需要从令个序列当中取出 $avg-sum_i+x$，又因为题目保证元素互不相同，所以我们可以确定 $avg-sum_i+x$ 所在的序列，我们考虑连一条有向边 $(x,avg-sum_i+x)$。

那么我们也就得到了一个内向基环树森林，对于每棵基环树，其中的环刚好可以对应操作有：

- 把 $u$ 从 $u$ 所在集合丢到 $pre_u$ 所在集合中。

所以每个环就是对于环上所有元素所在序列的一组解。但是需要注意的是，每个序列只能取出一个元素，而环上可能会有多个元素对应同一个序列，所以需要判断环上所有元素是否对应不同的序列。

然后我们记 $f_S$ 表示序列集合 $S$ 对应的解，则 $f_S=f_T+f_{S-T},T\subset S$。

最终复杂度 $\Theta(nk+3^k)$，由于需要离散化，所以应当是 $\Theta(nk\log nk+3^k)$。

---

