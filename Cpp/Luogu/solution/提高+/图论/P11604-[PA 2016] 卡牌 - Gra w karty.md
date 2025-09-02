# [PA 2016] 卡牌 / Gra w karty

## 题目背景

译自 [Potyczki Algorytmiczne 2016](https://sio2.mimuw.edu.pl/c/pa-2016-1/p/) R1 Gra w karty [A] (KAR)。$\texttt{1s,256M}$。


## 题目描述


Alice 和 Bob 各有 $n$ 张卡牌。每个人的卡牌都被编号为 $1\sim n$。

现在玩 $(n-1)$ 局游戏：每局游戏中，Alice 先弃掉 Bob 的一张牌，然后 Bob 再弃掉 Alice 的一张牌。

最终两人都只剩下一张牌。

有 $m$ 对关系，形如「若 Alice 最后剩下的牌为 $x$，Bob 最后剩下的牌为 $y$，则 Alice 胜/负 Bob」。特别地，未给出的关系为平局。

若双方都用最优策略游戏，Alice 最终会胜/负 Bob 还是平局？

「最佳策略」指的是：若有必胜策略，则选择必胜策略；否则若有平局策略，选择平局策略。

## 说明/提示


- $1\le T\le 20$；
- $1\le n\le 10^5$；
- $0\le m\le 2\times 10^5$；
- $1\le x,y\le n$；
- $w\in \{\texttt{<},\texttt{>}\}$。

保证不会出现自相矛盾的关系，也不会重复给出一个关系。

## 样例 #1

### 输入

```
3
5 5
5 > 5
1 > 5
3 > 5
4 > 5
2 > 5
2 2
1 > 1
1 > 2
1 1
1 < 1```

### 输出

```
WYGRANA
REMIS
PRZEGRANA```

# 题解

## 作者：Coffee_zzz (赞：9)

这题真的好难好难啊！

首先考虑 A 什么时候赢。

如果存在一个不大于 $n$ 的正整数 $i$，满足 B 的 $i$ 会输给 A 的 $1\sim n$ 的所有数，那么显然 A 把 B 的 $i$ 留下即可做到胜利。

否则，对于任意不大于 $n$ 的正整数 $i$，都满足存在至少一个不大于 $n$ 的正整数 $j$，使得 B 的 $i$ 不输 A 的 $j$。  
这时，我们考虑一个极端情况：现存在一个长度为 $n$ 的序列 $v$，B 的每个 $i$ 都**只**不输 $v_i$，即会输给 $1\sim v_i-1$ 和 $v_i+1 \sim n$。  
我们考虑一个可重集合 $S$，维护当前剩余的 $v_i$。在 A 把 B 的 $i$ 弃掉后，B 只需要把 $v_i$ 从 $S$ 中删掉，并选择一个不在 $S$ 中且还未被弃掉的 $j$，把 A 的 $j$ 弃掉即可。这样，在操作结束后，A 剩下的牌一定在 $S$ 中，即 B 剩下的牌不输给 A 剩下的牌。  
由于在 B 操作时，不在 $S$ 中的数的数量一定不小于当前轮数，所以一定可以找到满足条件的 $j$，这样的构造是合法的。

既然极端情况 B 都可以做到不输，而其他情况显然严格弱于极端情况，所以只要不满足「存在一个不大于 $n$ 的正整数 $i$，满足 B 的 $i$ 会输给 A 的 $1\sim n$ 的所有数」，那么 B 一定不输，即「存在一个不大于 $n$ 的正整数 $i$，满足 B 的 $i$ 会输给 A 的 $1\sim n$ 的所有数」是 A 赢的条件。

接下来考虑 B 什么时候赢。

如果存在一个不大于 $n$ 的正整数 $i$，满足 B 的 $i$ 不赢 A 的 $1\sim n$ 的所有数，那么显然 A 把 B 的 $i$ 留下即可做到不输。

否则，对于任意不大于 $n$ 的正整数 $i$，都满足存在至少一个不大于 $n$ 的正整数 $j$，使得 B 的 $i$ 赢 A 的 $j$，那么我们还是可以考虑一个序列 $v$，满足 B 的每个 $i$ 赢 A 的 $v_i$，并考虑一个可重集合 $S$，维护当前剩余的 $v_i$。  
在 A 把 B 的 $i$ 弃掉后，B 只需要把 $v_i$ 从 $S$ 中删掉，并选择一个不在 $S$ 中且还未被弃掉的 $j$，把 A 的 $j$ 弃掉即可。这样，在操作结束后，A 剩下的牌一定在 $S$ 中，即 B 剩下的牌会赢 A 剩下的牌。  
由于在 B 操作时，不在 $S$ 中的数的数量一定不小于当前轮数，所以一定可以找到满足条件的 $j$，这样的构造是合法的。

于是，我们可以得到，只要不满足「对于任意不大于 $n$ 的正整数 $i$，都满足存在至少一个不大于 $n$ 的正整数 $j$，使得 B 的 $i$ 赢 A 的 $j$」，那么 A 一定不输，即「对于任意不大于 $n$ 的正整数 $i$，都满足存在至少一个不大于 $n$ 的正整数 $j$，使得 B 的 $i$ 赢 A 的 $j$」是 B 赢的条件。

最后，如果 A 和 B 都无法获胜，那么他们只能做到不输，即平局。

代码还挺好写的。

```cpp
#include <bits/stdc++.h>

#define ll long long
#define ull unsigned long long
#define i128 __int128
#define endl '\n'
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define vei vector<int>
#define pq priority_queue
#define yes puts("yes")
#define no puts("no")
#define Yes puts("Yes")
#define No puts("No")
#define YES puts("YES")
#define NO puts("NO")
#define In(x) freopen(x".in","r",stdin)
#define Out(x) freopen(x".out","w",stdout)
#define File(x) (In(x),Out(x))
using namespace std;
const int N=1e5+5;
int a[N],b[N];
void solve(){
	int n,m;
	cin>>n>>m;
	memset(a,0,sizeof a);
	memset(b,0,sizeof b);
	for(int i=1;i<=m;i++){
		int x,y;
		char w;
		cin>>x>>w>>y;
		if(w=='>') a[y]++;
		if(w=='<') b[y]++;
	}
	int cnt=0;
	bool win=0;
	for(int i=1;i<=n;i++){
		if(a[i]==n) win=1;
		if(b[i]) cnt++;
	}
	if(win) puts("WYGRANA");
	else if(cnt==n) puts("PRZEGRANA");
	else puts("REMIS");
}
signed main(){
	ios::sync_with_stdio(0);
	signed T=1;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：ELECTRODE_kaf (赞：1)

把题中的每张牌转化成二分图中的一个点，Alice 的牌为左部点，Bob 的牌为右部点，每一对 ${x,y}$ 连一条边。只考虑 Alice 赢的情况。结论：Alice 的充要条件是右部点中有一个点的度数为 $n$。

证明：充分性显然，只需要证明必要性。考虑反面情况：若右部图中每个点的度数都 $<n$，那么补图中度数 $>1$，只需要说明 Bob 必然有策略使得右部图中一直不存在度为零的点。考虑某一时刻，双方均有 $n_1$ 张牌，Alice 删掉 Bob 的一张牌，Bob 有 $n_1-1$ 张牌。最坏情况下这 $n_1-1$ 个右部点度均为 $1$，此时左部点中必然有一个度为零的点，Bob 把它删去即可。其他情况删去右部点中度数 $>1$ 的点所连的左部点即可。

所以可以判断 Alice 能否获胜，再将 Bob 胜的情况取反跑一遍即可判断 Alice 能否平局。时间复杂度线性。

```cpp
const ll N = 1e5 + 10;
ll Q, n, m;
vector<pll> a1, a2;
vector<ll> g[N * 2];

bool check1() {
	rep(i, n + 1, n * 2) {
		if (g[i].size() == n)
			return 1;
		elif(g[i].size() > n) {
			cout << "#error at " << i << '\n';
			exit(0);
		}
	}

	return 0;
}

bool check2() {
	rep(i, n + 1, n * 2) {
		if (g[i].size() == 0)
			return 1;
	}

	return 0;
}

int main() {
	cin >> Q;

	count(Q) {
		a1.clear();
		a2.clear();
		cin >> n >> m;

		rep(i, 1, n * 2) g[i].clear();

		count(m) {
			ll u, v;
			char c;
			cin >> u >> c >> v;

			if (c == '>')
				a1.pb({u, v});
			else
				a2.pb({u, v});
		}

		for (pll i : a1) {
			g[i.fi].pb(i.se + n);
			g[i.se + n].pb(i.fi);
		}

		if (check1()) {
			cout << "WYGRANA\n";
//			cout << "Alice wins\n";
			ctn;
		}

		rep(i, 1, n * 2) g[i].clear();

		for (pll i : a2) {
			g[i.fi].pb(i.se + n);
			g[i.se + n].pb(i.fi);
		}

		if (check2()) {
			cout << "REMIS\n";
//			cout << "fair\n";
		} else {
			cout << "PRZEGRANA\n";
//			cout << "Alice loses\n";
		}
	}
}
```

代码宏定义在我个人空间自取。

---

## 作者：Sliarae (赞：1)

sk 姐姐亲亲 /qq

我们将问题规约为：有一个二元组集合 $S$，设最终 Alice 剩下一张牌 $x$，Bob 剩下一张牌 $y$，若二元组 $(x, y)$ 在集合 $S$ 中则 Alice 胜。问 Alice 有没有必胜策略。

令 $S$ 为所有 `>` 的状态构成的集合，可以知道 Alice 能否赢。令 $S$ 为所有 `<` 的状态构成的集合的补集，可以知道 Alice 能否平局。

我们称这个问题的结论为：建一张左部点和右部点个数都为 $n$ 的二分图，对于 $S$ 中的所有二元组 $(x, y)$，连一条左部点 $x$ 向右部点 $y$ 的边。存在右部点度数为 $n$，则 Alice 有必胜策略。

充分行显然，来考虑必要性。若不存在这样的右部点，则在补图中每个右部点度数 $\ge 1$。我们证明此时 Bob 一定能让最终状态 $(x, y)$ 在补图中有边。接下来默认在补图中考虑。

考虑归纳，$n = 1$ 显然成立。否则 Alice 会先删掉一个右部点。我们证明无论 Alice 如何操作，Bob 都存在删一个左部点的策略，使得每个右部点仍满足度数 $\ge 1$。

我们发现可以忽略所有度数 $\ge 2$ 的点，因为无论我们怎么删它们都合法。此时图中左部点个数为 $n$，右部点个数 $\le n - 1$，而每个右部点至多让一个左部点不能删，所以 Bob 一定存在删一个左部点的策略。

```cpp
#include <iostream>

using namespace std;

const int kN = 1e5 + 5; 

int n, m;
int a[kN], b[kN];

void Solve () {
	cin >> n >> m;
	fill(a, a + n + 1, 0);
	fill(b, b + n + 1, 0);
	for (int i = 1, x, y; i <= m; ++i) {
		char o;
		cin >> x >> o >> y;
		if (o == '>') ++a[y];
		if (o == '<') ++b[y];
	}
	for (int i = 1; i <= n; ++i)
		if (a[i] == n) 
			return cout << "WYGRANA" << '\n', void();
	for (int i = 1; i <= n; ++i)
		if (!b[i])
			return cout << "REMIS" << '\n', void(); 
	cout << "PRZEGRANA" << '\n';
}

int main () {
	cin.tie(0)->sync_with_stdio(0);
	int T;
	cin >> T;
	while (T--) Solve();
	return 0; 
}
```

---

## 作者：_abcd_ (赞：1)

## [[PA 2016] 卡牌 / Gra w karty](https://www.luogu.com.cn/problem/P11604)

大受震撼，感觉不止黄吧。

分别考虑 $ \rm Bob $ 和 $ \rm Alice $ 能不能赢，如果都不能赢那就是平局。

若 $ a > b $，则令 $ a $ 向 $ b $ 连一条边。这样原图会形成一个两边都是 $ n $ 个点的二分有向图。我们令 $ \rm Alice $ 的点为左部，$ \rm Bob $ 的点为右部。

对于 $ \rm Bob $ 来说，如果说他有某个点没有出边，那么 $ \rm Alice $ 只要一直保留这个点不删，$ \rm Bob $ 就一定赢不了。否则，$ \rm Bob $ 一定可以一直保持每个点都有出边的情况直到最后，也就赢了。考虑归纳证明：假设当前 $ \rm Alice $ 和 $ \rm Bob $ 都有 $ n $ 个点，且 $ \rm Bob $ 的每个点都有出边，那么不论 $ \rm Alice $ 删了哪个点，$ \rm Bob $ 都会剩下 $ n-1 $ 个有出边的点。这时候 $ \rm Alice $ 任然剩下 $ n $ 个点，显然 $ \rm Bob $ 一定能删掉一个点，使得他的 $ n-1 $ 个点任然都有出边，因为最坏情况下是每个点的出度都恰好为 $ 1 $ 且出集互不相同，这样任然存在一个能删的点。

而对于 $ \rm Alice $，由于他是先手删的，因此会很不利。观察样例发现，如果 $ \rm Bob $ 有一个入度为 $ n $ 的点，那么她只需要一直留着这个点，无论 $ \rm Bob $ 怎么删她都能赢。其他情况下 $ \rm Alice $ 一定赢不了，同样考虑归纳证明：假设两人都有 $ n $ 个点，无论 $ \rm Alice $ 删了哪个点，此时 $ \rm Bob $ 会剩下 $ n-1 $ 个点，且每个点的入度最多为 $ n-1 $。我们不妨只考虑入度为 $ n-1 $ 的点（因为对于其他点，无论 $ \rm Bob $ 怎么删，都不会成为满入度的点），如果存在某个入度为 $ n-1 $ 的点 $ i $，而唯一一个没有连向 $ i $ 的点为 $ j $，那么 $ \rm Bob $ 一定不能删除 $ j $，否则 $ i $ 就会成为满入度的点。由于 $ \rm Bob $ 只有 $ n-1 $ 个点，因此这样的 $ i $ 最多只有 $ n-1 $ 个，因此 $ j $ 也最多只有 $ n-1 $ 个。那么只要删掉不是某个 $ j $ 的点就行了。

---

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pn putchar('\n')
#define mset(a,x) memset(a,x,sizeof a)
#define mcpy(a,b) memcpy(a,b,sizeof a)
#define all(a) a.begin(),a.end()
#define fls() fflush(stdout)
using namespace std;
int re()
{
    int x=0;
    bool t=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
        t=ch=='-'?0:t,ch=getchar();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return t?x:-x;
}
const int maxn=2e5+5;
int n,m;
int cd[maxn],rd[maxn];
void solve()
{
    n=re(),m=re();
    mset(cd,0);
    mset(rd,0);
    while(m--)
    {
        int u=re();
        char ch=getchar();
        int v=re();
        if(ch=='>')
            rd[v]++;
        else
            cd[v]++;
    }
    bool ans=1;
    for(int i=1;i<=n;i++)
    {
        if(rd[i]==n)
        {
            puts("WYGRANA");
            return;
        }
        if(!cd[i])
            ans=0;
    }
    puts(ans?"PRZEGRANA":"REMIS");
}
signed main()
{
    int T=re();
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

好难。

遇事不决考虑先打表猜结论，手玩若干组小数据后可以发现下面的结论：

+ 考虑建一张二分图。把 Alice 的点放在左边，Bob 的点放在右边，那么 Alice 必胜，当且仅当存在一个 Bob 的点，使得其和 Alice 所有的点都有连边，即其的度数为 $n$。

这个结论感觉很哇塞，于是考虑证明之。

**I. 证明该情况下 Alice 必胜**

这个还是很显然的。考虑到只要 Bob 的这张牌还留着，Alice 不管留下哪张牌，都是必胜状态。而 Bob 留下哪一张牌是由 Alice 决定的。因此该情况证毕。

**II. 证明若非该情况，则 Alice 一定不会必胜**

考虑建上述二分图的二分补图，即求出原图的补图，然后将该图在同一侧的边全部移出。此时该二分补图所有右侧点的度数均 $\ge 1$。然后可以发现若某个右侧点的度数 $\ge 2$ 那么这个点不论 Alice 最后留下哪一个点都一定合法。此时若不存在度数为 $1$ 的点那么 Alice 一定不能胜，否则 Alice 一定会保留恰好一张 Bob 的牌使得其在二分图中右侧所对应的点的度数为 $1$。此时若至少删去了一个点，则右侧点数量一定严格小于左侧点数量，每一个右侧点最多让一个左侧点不能被删除，而且可能会对应到重复的关系，所以此时 Alice 必然不会获胜。否则补图中必然恰好是一一对应的关系。很显然只要 $n>1$ 那么 Bob 必然有一种可以获胜的方法，即每一次删去 Alice 所要删除的点所唯一对应的点。而 $n=1$ Alice 必胜，但是该情况满足条件。因此该部分证毕。

----

现在判定完 Alice 必胜的情况。在 Alice 无法获胜的情况下，考虑 Bob 什么时候必胜。很显然，若存在一个右侧点 $i$ 使得该点不能战胜任何一个左侧点，那么 Alice 只需要一直不删除 $i$ 这个点，就可以做到 Bob 无法获胜。否则很显然，不存在一个右侧点使得该右侧点无法战胜 Alice 的任何一个左侧点。容易证明，假设 Alice 删除了 Bob 的右侧点 $i$，那么假设本来 $i$ 可以战胜点 $x$，那么若 $x$ 本身已经被删除了，那么根据抽屉原理可知：

+ 此时必然有一个 Alice 的左侧点，使得 Bob 不论选择哪一个结点都无法获胜。
+ Bob 存在一个结点，使得当前这个结点仍然可以战胜至少两个当前 Alice 侧没有被删除的结点。

对于情况 $1$ Bob 删除这个 Alice 的左侧点就是最优情况，对于情况 $2$ Bob 删除这个顶点集合中任意一个结点都可以，都是最优情况。因此执行 $n-1$ 次操作之后，剩下的两个结点必然满足 Bob 的可以击杀 Alice 的结点。

于是该题被做完了。结论为：

+ 建立一张二分图，把所有 Alice 的 $n$ 个点放在图的左侧，Bob 的 $n$ 个点放在图的右侧。
+ 若把所有 Alice 必胜的边连起来，存在 Bob 的一个点 $i$ 使得 $\deg(i)=n$，则 Alice 必胜。
+ 若把所有 Bob 必胜的边连起来，对于任意一个 Bob 的结点 $i$ 都有 $\deg(i)\neq 0$，则 Bob 必胜。
+ 否则 Alice 和 Bob 使用最优策略，必然导致平局。

直接按照上述策略模拟即可，时间复杂度为 $O(n)$，可以通过。

代码：

```cpp
// #pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100010;
int buc[N];
struct Oper {
    int x;
    char o;
    int y;
} oper[N << 1];
signed main() {
    cout << fixed << setprecision(15);
    cin.tie(0)->sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= m; ++i) {
            int x, y;
            char o;
            cin >> x >> o >> y;
            oper[i] = {x, o, y};
        }
        fill(buc + 1, buc + n + 1, 0ll);
        for (int i = 1; i <= m; ++i)
            if (oper[i].o == '>')
                ++buc[oper[i].y];
        if (count(buc + 1, buc + n + 1, n) >= 1) cout << "WYGRANA\n";
        else {
            fill(buc + 1, buc + n + 1, 0ll);
            for (int i = 1; i <= m; ++i)
                if (oper[i].o == '<')
                    ++buc[oper[i].y];
            if (!count(buc + 1, buc + n + 1, 0)) cout << "PRZEGRANA\n";
            else cout << "REMIS\n";
        }
    }
    return 0;
}
```

---

