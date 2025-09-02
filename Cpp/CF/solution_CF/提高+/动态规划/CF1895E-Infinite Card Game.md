# Infinite Card Game

## 题目描述

Monocarp and Bicarp are playing a card game. Each card has two parameters: an attack value and a defence value. A card $ s $ beats another card $ t $ if the attack of $ s $ is strictly greater than the defence of $ t $ .

Monocarp has $ n $ cards, the $ i $ -th of them has an attack value of $ \mathit{ax}_i $ and a defence value of $ \mathit{ay}_i $ . Bicarp has $ m $ cards, the $ j $ -th of them has an attack value of $ \mathit{bx}_j $ and a defence value of $ \mathit{by}_j $ .

On the first move, Monocarp chooses one of his cards and plays it. Bicarp has to respond with his own card that beats that card. After that, Monocarp has to respond with a card that beats Bicarp's card. After that, it's Bicarp's turn, and so forth.

After a card is beaten, it returns to the hand of the player who played it. It implies that each player always has the same set of cards to play as at the start of the game. The game ends when the current player has no cards that beat the card which their opponent just played, and the current player loses.

If the game lasts for $ 100^{500} $ moves, it's declared a draw.

Both Monocarp and Bicarp play optimally. That is, if a player has a winning strategy regardless of his opponent's moves, he plays for a win. Otherwise, if he has a drawing strategy, he plays for a draw.

You are asked to calculate three values:

- the number of Monocarp's starting moves that result in a win for Monocarp;
- the number of Monocarp's starting moves that result in a draw;
- the number of Monocarp's starting moves that result in a win for Bicarp.

## 样例 #1

### 输入

```
3
3
8 7 4
7 1 10
2
8 4
5 10
9
8 8 5 5 5 4 4 1 4
2 7 5 2 8 9 7 1 9
10
9 8 7 6 5 5 4 3 2 1
7 1 6 7 5 8 8 4 9 6
1
10
5
1
10
5```

### 输出

```
1 1 1
2 4 3
0 1 0```

# 题解

## 作者：DerrickLo (赞：7)

显然的，如果对方出了一张牌，那么自己一定要出在比这张牌防御值的大的牌中，防御值最大的牌。

如果不是，那么对手所可以接着出的牌就可能变多，那么这显然不优。

所以我们按照攻击值从小到大排序，然后预处理出后缀最大值和其出现位置，然后对于每张牌二分找到对手攻击力比这张牌防御力大的区间，然后找到防御力的最大值，将这两张牌连边。

这样就会构造出一个有向图，然后如果一个点的出度是 $0$，那么这个点必胜。

然后进行一次 `dfs`，因为一个点最多有一条出边，所以这个点的胜负状态就是他所连向的这个点的反面状态。

那么我们就能统计出必胜节点和必输节点，然后用总数减去必胜与必输的节点就是平局的节点数。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,d[600005],amax[600005],bmax[600005],posa[600005],posb[600005],ans[600005],vis[600005];
vector<int> ve[600005];
struct nd{
	int x,y;
	friend bool operator<(const nd&a,const nd&b){
		return a.x<b.x;
	}
}a[600005],b[600005];
void dfs(int u){
	if(vis[u])return;
	vis[u]=1;
	for(int v:ve[u]){
		dfs(v);
		ans[u]=-ans[v];
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i].x;
		for(int i=1;i<=n;i++)cin>>a[i].y;
		cin>>m;
		for(int i=1;i<=m;i++)cin>>b[i].x;
		for(int i=1;i<=m;i++)cin>>b[i].y;
		for(int i=1;i<=n+m;i++)ve[i].clear(),d[i]=ans[i]=vis[i]=0;
		sort(a+1,a+n+1);
		sort(b+1,b+m+1);
		amax[n+1]=bmax[m+1]=INT_MIN;
		for(int i=n;i;i--){
			if(amax[i+1]<a[i].y)amax[i]=a[i].y,posa[i]=i;
			else amax[i]=amax[i+1],posa[i]=posa[i+1];
		}
		for(int i=m;i;i--){
			if(bmax[i+1]<b[i].y)bmax[i]=b[i].y,posb[i]=i;
			else bmax[i]=bmax[i+1],posb[i]=posb[i+1];
		}
		for(int i=1;i<=n;i++){
			int aa=upper_bound(b+1,b+m+1,nd{a[i].y,0})-b;
			if(aa!=m+1){
				ve[i].emplace_back(posb[aa]+n);
				d[i]++;
			}
		}
		for(int i=1;i<=m;i++){
			int bb=upper_bound(a+1,a+n+1,nd{b[i].y,0})-a;
			if(bb!=n+1){
				ve[i+n].emplace_back(posa[bb]);
				d[i+n]++;
			}
		}
		for(int i=1;i<=n+m;i++)if(!d[i])ans[i]=1;
		for(int i=1;i<=n+m;i++)if(!vis[i])dfs(i);
		int ans1=0,ans2=0;
		for(int i=1;i<=n;i++)if(ans[i]==1)ans1++;else if(ans[i]==-1)ans2++;
		cout<<ans1<<" "<<n-ans1-ans2<<" "<<ans2<<"\n";
	}
	return 0;
}
```

---

## 作者：LYY_yyyy (赞：3)

貌似是上紫场的上紫题，写个题解纪念一下。

我们考虑你打出一张牌之后对面会拿什么牌回应。贪心地想，对面一定会打出攻击力大于你打出的牌的防御力的所有牌中防御力最大的牌。所以我们模拟这个过程就好了。具体实现是将双方的牌按照攻击力排序然后预处理后缀最大值，每次二分就好了。如果不存在攻击力大于这张牌防御力的就赢了。否则就回应对面的牌，递归到回应的牌就行了。这里记忆化一下，时间复杂度 $O(n\log n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n,m;
struct node
{
	int x,y;int win;
	friend bool operator < (const node &a,const node &b)
	{
		return a.x<b.x;
	}
}a[300010],b[300010];
int hmax1[300010],hmax2[300010];
int dfs(int now)
{
	if(a[now].win!=-1) return a[now].win;
	node o={a[now].y,0,0};
	int p=upper_bound(b+1,b+m+1,o)-b;
	a[now].win=1;
	if(p>m) return a[now].win=0;
	o={hmax2[p],0,0};
	int q=upper_bound(a+1,a+n+1,o)-a;
	if(q>n) return a[now].win=2;
	return a[now].win=dfs(hmax1[q]);
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n;hmax1[n+1]=0;
		for(int i=1;i<=n;i++) cin>>a[i].x,hmax1[i]=0;
		for(int i=1;i<=n;i++) cin>>a[i].y,a[i].win=-1;
		cin>>m;hmax2[m+1]=0;
		for(int i=1;i<=m;i++) cin>>b[i].x,hmax2[i]=0;
		for(int i=1;i<=m;i++) cin>>b[i].y,b[i].win=-1;
		sort(a+1,a+n+1);sort(b+1,b+m+1);int ans[4]={0};
		for(int i=n;i>=1;i--) 
		{
			if(a[i].y>a[hmax1[i+1]].y) hmax1[i]=i;
			else hmax1[i]=hmax1[i+1];
		}for(int i=m;i>=1;i--) hmax2[i]=max(hmax2[i+1],b[i].y); 
		for(int i=1;i<=n;i++)
		{
			if(a[i].win!=-1) continue;
			dfs(i);
		}
		for(int i=1;i<=n;i++) ans[a[i].win]++;
		for(int i=0;i<=2;i++) cout<<ans[i]<<' ';cout<<"\n";
	}
	return 0;
}
```

---

## 作者：modfisher (赞：2)

## 思路
容易想到，如果能第一个人能赢，则他的手牌中必定存在至少一张满足：防御力比第二个人所有手牌的攻击力都高。

所以，满足上述条件的牌必定会被计入第一个答案中，将这些牌记为集合 $A$。现在只需考虑：还有没有别的牌能让第一个人赢？

很明显，只要能出集合 $A$ 中的任意一张牌，就会胜利。可以在第二个人的手牌中找到所有防御力低于 $A$ 中最大攻击力的牌，将这些牌记为集合 $B$，只要让第二个人无论如何都必须出 $B$ 中的牌，第一个人就会赢。

考虑如何让第二个人无论如何都必须出 $B$ 中的牌。将第二个人手牌中除 $B$ 以外的牌记为集合 $C$，则 $B$ 中最大攻击力应**严格大于** $C$ 中最大攻击力。那么第一个人手牌中所有防御力不小于 $C$ 中最大攻击力的牌都能满足条件。

就这么一直考虑下去，知道没有满足条件的牌了，第一个答案也就统计完了。

第三个答案也能以类似的方法统计。然后这题就做完了。

最大攻击值可以用 ST 表处理。时间复杂度 $O(n\log n)$。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5 + 5;

struct card{
	int atk, def;
}a[maxn], b[maxn];
int lg[maxn], sta1[maxn][20], stb1[maxn][20];

bool cmp(card x, card y){
	return x.def < y.def;
}
int get(int l, int r, int md){
	if(l > r) return -1;
	int g = lg[r - l + 1];
	if(md == 1) return max(sta1[l][g], sta1[r - (1 << g) + 1][g]);
	else return max(stb1[l][g], stb1[r - (1 << g) + 1][g]);
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		int n, m;
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++) scanf("%d", &a[i].atk);
		for(int i = 1; i <= n; i ++) scanf("%d", &a[i].def);
		sort(a + 1, a + n + 1, cmp);
		scanf("%d", &m);
		for(int i = 1; i <= m; i ++) scanf("%d", &b[i].atk);
		for(int i = 1; i <= m; i ++) scanf("%d", &b[i].def);
		sort(b + 1, b + m + 1, cmp);
		for(int i = 2; i <= max(n, m); i ++) lg[i] = lg[i >> 1] + 1;
		for(int i = 1; i <= n; i ++) sta1[i][0] = a[i].atk;
		for(int i = 1; i <= m; i ++) stb1[i][0] = b[i].atk;
		for(int j = 1; j <= lg[max(n, m)]; j ++){
			for(int i = 1; i + (1 << j) - 1 <= n; i ++) sta1[i][j] = max(sta1[i][j - 1], sta1[i + (1 << j - 1)][j - 1]);
			for(int i = 1; i + (1 << j) - 1 <= m; i ++) stb1[i][j] = max(stb1[i][j - 1], stb1[i + (1 << j - 1)][j - 1]);
		}
		int res1 = 0, res2 = 0;
		int sta = n, eda = n + 1, edb2 = 0;
		while(eda > 1 && a[eda - 1].def >= get(edb2 + 1, m, 2)) eda --, res1 ++;
		while(edb2 < m && b[edb2 + 1].def < get(eda, n, 1)) edb2 ++;
		while(sta >= eda){
			if(get(1, edb2, 2) <= get(edb2 + 1, m, 2)) break;
			sta = eda - 1;
			while(eda > 1 && a[eda - 1].def >= get(edb2 + 1, m, 2)) eda --, res1 ++;
			while(edb2 < m && b[edb2 + 1].def < get(eda, n, 1)) edb2 ++;
		}
		int stb = m, edb = m + 1, eda2 = 0;
		while(edb > 1 && b[edb - 1].def >= get(eda2 + 1, n, 1)) edb --;
		while(eda2 < n && a[eda2 + 1].def < get(edb, m, 2)) eda2 ++, res2 ++;
		while(stb >= edb){
			if(get(1, eda2, 1) <= get(eda2 + 1, n, 1)) break;
			stb = edb - 1;
			while(edb > 1 && b[edb - 1].def >= get(eda2 + 1, n, 1)) edb --;
			while(eda2 < n && a[eda2 + 1].def < get(edb, m, 2)) eda2 ++, res2 ++;
		}
		printf("%d %d %d\n", res1, n - res1 - res2, res2);
		for(int i = 1; i <= max(n, m); i ++){
			a[i].atk = a[i].def = b[i].atk = b[i].def = 0;
			for(int j = 1; j <= lg[max(n, m)]; j ++){
				sta1[i][j] = stb1[i][j] = 0;
			}
		}
	}
	return 0;
}
```


---

## 作者：Lightwhite (赞：1)

[portal](http://codeforces.com/problemset/problem/1895/E)

题意：小 M 和小 B 分别有 $n,m$ 张卡牌，有相应的攻击值和防御值。一开始小 M 选出自己的一张牌打出，下一个人需要给出 攻击值比对方打出的牌的防御值严格更大的卡牌，谁无法按此规则出牌就判作那方战败，持续 $10^{1000}$ 步就平局。问小 M 分别有多少张牌放在最开始给出可以使得最终自己 获胜/平局/战败。$1\leq n,m\leq 3\times 10^5$。

提供一种可能更加优美的做法。

你发现不管是谁，最优策略总是选出攻击值比对方防御值严格更大，且防御值尽量大的卡牌。于是你对于一张牌，对方将会出什么样的牌是可确定的。考虑并查集上将当前牌并向对方会出的牌，一张牌当前连通块的根节点就是你出这张牌最终会以什么牌结束。可以直接判断出这张牌是谁的牌来预测胜负。时间复杂度 $O((n+m)\log n)$，由于无法按秩合并，无法将复杂度优化到反阿克曼级别。


```cpp
// stODDDDDDDDDDDDDDDDDDDDDDDDDDD hzt CCCCCCCCCCCCCCCCCCCCCCCCCOrz

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using LL = long long;
using PII = pair<int, int>;
constexpr int kN = 3e5 + 2;
#define y first
#define x second

int T;
int n, m;
PII a[kN], b[kN];
int ans[2 * kN], v[2 * kN], fa[2 * kN];

int R(int x) {
  if (x == fa[x]) {
    return x;
  }
  fa[x] = R(fa[x]);
  return fa[x];
}
void M(int u, int v) {
  u = R(u), v = R(v);
  if (u == v) {
    return;
  }
  fa[u] = v;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].x;
    }
    for (int i = 1; i <= n; i++) {
      cin >> a[i].y;
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
      cin >> b[i].x;
    }
    for (int i = 1; i <= m; i++) {
      cin >> b[i].y;
    }
    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);

    fill_n(v + 1, n + m, 0);
    fill_n(ans + 1, n + m, 0);
    iota(fa, fa + n + m + 1, 0);
    for (int i = 1, j = m; i <= n; i++) {
      for (; j && b[j].x <= a[i].y; j--) {
      }
      if (j != 0) {
        v[i] = j + n;
        M(i, j + n);
      } else {
        break;
      }
    }
    for (int i = 1, j = n; i <= m; i++) {
      for (; j && a[j].x <= b[i].y; j--) {
      }
      if (j != 0) {
        v[i + n] = j;
        M(i + n, j);
      } else {
        break;
      }
    }
    for (int i = 1; i <= n + m; i++) {
      if (v[i]) {
        continue;
      }
      if (i <= n) {
        ans[R(i)] = -1;
      } else {
        ans[R(i)] = 1;
      }
    }
    int ans1 = 0, ans2 = 0, ans3 = 0;
    for (int i = 1; i <= n; i++) {
      int f = R(i);
      if (ans[f] == -1) {
        ans1++;
      } else if (ans[f] == 0) {
        ans2++;
      } else {
        ans3++;
      }
    }
    cout << ans1 << ' ' << ans2 << ' ' << ans3 << '\n';
  }
  return 0;
}
```

---

## 作者：spdarkle (赞：1)

赛时没过，还是没上紫名，第二天早上爬起来，突然发现自己只是一个读入打错了。

容易发现，由于每个玩家手上的牌永远不变，所以每一轮打出的牌必然是能够打败对方的牌中同时自己防御力最强的一张牌。

如果不是，那么会使得对手可以出的牌的集合变大，可能会变劣。

那么我们可以处理出每张牌打出后，对手最优打出的牌。这一步可以通过对 $a$ 进行排序，再对 $b$ 做最大值，然后二分查找，可以做到 $O((n+m)(\log n+\log m))$

这里简记自己手中是 $1\sim n$，另一个人手中是 $n+1\sim n+m$。

将这样的关系进行建图，即若打出牌 $u$ 后对方立刻打出牌 $v$，则连有向边 $(v,u)$，这样每个点入度小于等于一，并且足以描述这个关系：从一个可能的终点到节点 $x$ 的路径表示了整个决策过程。

通过这样的方式，就可以处理这个题了。设 $f_u$ 表示起点是 $u$ 时先手的胜负状态，胜利为 $1$，失败为 $0$，平局为 $2$。

那么最初入度为零的点，表示对方无法打出牌了，这个牌必胜。

然后我们对图不断拓扑排序，只要一个节点的所有前驱都是必胜，则这个点必败，否则必胜。

至于平局的情况，这显然是拓扑排序后留下的若干环。将环上的点暴力视作平局即可。

[code](https://codeforces.com/contest/1895/submission/231262218)

---

## 作者：喵仔牛奶 (赞：0)

# Solution

- 根据贪心策略，可以发现出完一张牌后对手的出牌是固定的。同理可以算出 Monocarp 出完一张牌 $a$ 后下一次出的牌 $to_a$。
- $a$ 和 $to_a$ 胜负状态相同。可以发现对所有 $a$ 建 $a\to to_a$ 后形成的图是内向基环树，一遍 dfs 即可求出答案。

时间复杂度 $\mathcal{O}(n\log n)$（将 $n,m$ 看作同阶）。

# Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
using namespace std;
namespace Milkcat {
    typedef long long LL;
    typedef pair<LL, LL> pii;
    const int N = 1e6 + 5;
    LL n, m, suf1[N], suf2[N], qwq[N], to[N], ans[N], res[3]; pii a[N], b[N];
    int dfs(int u) {
    	if (ans[u] != -1) return ans[u];
		return ans[u] = 1, ans[u] = dfs(to[u]);
	}
    int main() {
		cin >> n;
		REP(i, 1, n) cin >> a[i].fi;
		REP(i, 1, n) cin >> a[i].se;
		cin >> m;
		REP(i, 1, m) cin >> b[i].fi;
		REP(i, 1, m) cin >> b[i].se;
		sort(a + 1, a + 1 + n);
		sort(b + 1, b + 1 + m);
		
		suf1[n + 1] = suf2[m + 1] = 0; 
		DEP(i, n, 1) suf1[i] = (a[i].se > a[suf1[i + 1]].se ? i : suf1[i + 1]); 
		DEP(i, m, 1) suf2[i] = (b[i].se > b[suf2[i + 1]].se ? i : suf2[i + 1]);
		REP(i, 1, m) qwq[i] = suf1[lower_bound(a + 1, a + 1 + n, pii(b[i].se + 1, 0)) - a];
		
		REP(i, 1, n) {
			int x = suf2[lower_bound(b + 1, b + 1 + m, pii(a[i].se + 1, 0)) - b];
			if (!x) { ans[i] = 0; continue; }
			if (!qwq[x]) { ans[i] = 2; continue; }
			to[i] = qwq[x], ans[i] = -1;
		}
		memset(res, 0, sizeof res);
		REP(i, 1, n) {
			if (ans[i] == -1) dfs(i);
			res[ans[i]] ++;
		}
		REP(i, 0, 2) cout << res[i] << ' ';
		cout << '\n';
		
        return 0;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T = 1; cin >> T;
    while (T --) Milkcat::main();
    return 0;
}
```

---

## 作者：EuphoricStar (赞：0)

容易转化成经典的有向图博弈模型。每张牌建一个点，若 $x$ 能打败 $y$ 就连一条 $x \to y$ 的边。入度为 $0$ 的点为必败态，之后类似拓扑排序倒推即可。

具体就是若存在边 $u \to v$，若 $u$ 为必败态则 $v$ 为必胜态并加入队列；若 $v$ 的所有前驱都是必胜态，那么 $v$ 为必败态并加入队列。最后没考虑到的点即为平局态。有点类似 [P9169 [省选联考 2023] 过河卒](https://www.luogu.com.cn/problem/P9169)。

朴素地做边数 $O(n^2)$，无法承受。注意到若把双方的牌都按防御值排序，那么一个点的出边是一段连续的区间。设点 $u$ 的连边区间为 $[l_u, r_u]$。于是可以直接线段树维护每个点的入度，每当入度最小值为 $0$ 就把对应的点 push 进队列并将这个点的状态设为必败态。线段树需要支持区间加，单点修改，查全局最小值及其位置。

还需要支持当 $u$ 为必败态时把 $u$ 的所有后继都设为必胜态。发现实际上进行操作的只有 $u$ 的之前没设为必胜态的后继的点。套路地使用并查集，并查集上每个点的祖先为它下一个还没被设为必胜态的点，就可以暴力找到要更新的点了。

时间复杂度 $O((n + m) \log (n + m))$。

[code](https://codeforces.com/contest/1895/submission/232842348)

---

## 作者：buaa_czx (赞：0)

## 思路

对于这类问题，可以考虑建立有向关系图，描述每张牌对应的“下一张牌”可能是什么。然而，$O(N^2)$ 的建图时空复杂度均过高，考虑如何将图的边数压缩，只保留有效的边。

不难发现，每张打出的牌的攻击力只需要满足大于场上牌的防御力 $y$ 的条件，而为了使对方尽量不能出牌，贪心的考虑，应当使打出的牌防御力尽可能大。也就是说，每张牌对应的它的“下一张牌”一定是对方所拥有的攻击力大于 $y$ 的牌中，防御力最大的一张。这个操作可以对两个数组排序，然后求解出前缀最大值来完成。

将每张牌被打出的情景视为一个状态，对于每个状态，它的下一个节点都是确定的（出度最大为 1），最终结果也是确定的。

因此不难想到，反向建图后跑一遍拓扑排序，初始入度为 0 的那些点也就是这个点所对应的一条链上的所有点的最终状态，而拓扑排序没有跑到的点（环上的点）即是平局状态。

## 代码

```cpp
int n, m, p;
struct node {
    int atk, def, id;
} a[maxN + 5], b[maxN + 5];
int pre_max[maxN + 5];
vector<int> to[2 * maxN + 5];
int in_deg[2 * maxN + 5], res[2 * maxN + 5];
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].atk;
        a[i].id = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i].def;
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        b[i].id = n + i;
        cin >> b[i].atk;
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i].def;
    }
    for (int i = 1; i <= n + m; i++) {
        to[i].resize(0);
        in_deg[i] = 0, res[i] = 0;
    }
    sort(a + 1, a + n + 1, [](node x, node y) { return x.def > y.def; });
    sort(b + 1, b + m + 1, [](node x, node y) { return x.atk > y.atk; });
    pre_max[1] = 1;
    for (int i = 2; i <= m; i++) {
        if (b[i].def > b[pre_max[i - 1]].def) {
            pre_max[i] = i;
        } else {
            pre_max[i] = pre_max[i - 1];
        }
    }
    p = 1;
    for (int i = 1; i <= n; i++) {
        if (b[p].atk <= a[i].def) {
            continue;
        }
        while (b[p].atk > a[i].def && p <= m) {
            p++;
        }
        p--;
        to[b[pre_max[p]].id].pb(a[i].id); // 反向建边
        //    cerr << b[pre_max[p]].id << " " << a[i].id << endl;
        in_deg[a[i].id]++;
    }
    sort(a + 1, a + n + 1, [](node x, node y) { return x.atk > y.atk; });
    sort(b + 1, b + m + 1, [](node x, node y) { return x.def > y.def; });
    pre_max[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i].def > a[pre_max[i - 1]].def) {
            pre_max[i] = i;
        } else {
            pre_max[i] = pre_max[i - 1];
        }
    }
    p = 1;
    for (int i = 1; i <= m; i++) {
        if (a[p].atk <= b[i].def) {
            continue;
        }
        while (a[p].atk > b[i].def && p <= n) {
            p++;
        }
        p--;
        to[a[pre_max[p]].id].pb(b[i].id); // 反向建边
        //    cerr << a[pre_max[p]].id << " " << b[i].id << endl;
        in_deg[b[i].id]++;
    }
    queue<int> q;
    for (int i = 1; i <= m + n; i++) {
        if (in_deg[i] == 0) {
            q.push(i);
            res[i] = i;
        }
    }
    while (!q.empty()) {
        int xn = q.front();
        q.pop();
        for (auto &it : to[xn]) {
            in_deg[it]--;
            res[it] = res[xn];
            q.push(it);
        }
    }
    int ans[3] = {0};
    for (int i = 1; i <= n; i++) {
        if (res[i] == 0) {
            ans[1]++;
        } else if (res[i] <= n) {
            ans[0]++;
        } else {
            ans[2]++;
        }
    }
    for (int i = 0; i < 3; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}
```

---

## 作者：happybob (赞：0)

赛时差一点过，因为缺少了一个关键性质的观察。

容易发现可以 $O(nm)$ 建图然后跑类似过河卒的有向图博弈。

注意到当我打出这张牌，对手一定会打出攻击力大于这张牌的防御力并且那张牌防御力最大，显然可以二分，然后就可以将图的边数减小了。这就是关键性质。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5, MOD = 1e9 + 7; // Remember to change

int n, m, q, t, a[N];
int ax[N], ay[N], bx[N], by[N];

namespace FastIo
{
	#define QUICKCIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
	int read()
	{
		char ch = getchar();
		int x = 0, f = 1;
		while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
		while (ch == '-')
		{
			f = -f;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9')
		{
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template<class T>
	void write(T x)
	{
		if (x < 0)
		{
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	template<class T>
	void writeln(T x)
	{
		write(x);
		putchar('\n');
	}
}

vector<int> G[N];
int in[N];
int dp[N];
bool vis[N];

struct Node
{
	int x, y, id;
	Node(int _x, int _y, int _i): x(_x), y(_y), id(_i){}
	Node() = default;
	bool operator<(const Node& g) const
	{
		return (x ^ g.x) ? (x < g.x) : (y < g.y);
	}
}g[N], gg[N];
int sufmax[N];

signed main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) cin>>ax[i];
		for(int i=1;i<=n;i++) cin>>ay[i];
		cin>>m;
		vector<pair<int, int>> v;
		for(int i=1;i<=m;i++) cin>>bx[i];
		for(int i=1;i<=m;i++) cin>>by[i];
		for(int i=1;i<=m;i++)
		{
			g[i]=Node(bx[i],by[i],i);
			gg[i]=g[i];
		}
		for(int i=1;i<=n+m;i++) G[i].clear(),in[i]=0,dp[i]=-1,vis[i]=0;
		sort(g+1,g+m+1);
		sufmax[m]=m;
		for(int i=m-1;i>=1;i--)
		{
			if(g[i].y>g[sufmax[i+1]].y) sufmax[i]=i;
			else sufmax[i]=sufmax[i+1];
		}
		for(int i=1;i<=n;i++)
		{
			int maxnid=0; 
			auto j=upper_bound(g+1,g+m+1,Node(ay[i],100000000,0))-g;
			if(j>=1&&j<=m)
			{
				int maxnid=sufmax[j];
				maxnid=g[maxnid].id;
				G[n+maxnid].emplace_back(i),in[i]++;
			}
		}
		/*
		for(int i=1;i<=m;i++)
		{
			int maxnid=0;
			for(int j=1;j<=n;j++)
			{
				if(ax[j]>by[i]) 
				{
					if(ay[j]>ay[maxnid])
					{
						maxnid=j;
					}
				}
			}
			if(maxnid) G[maxnid].emplace_back(i+n),in[i+n]++;
		}*/
		for(int i=1;i<=n;i++) g[i]=Node(ax[i],ay[i],i);
		sort(g+1,g+n+1);
		sufmax[n]=n;
		for(int i=n-1;i>=1;i--)
		{
			if(g[i].y>g[sufmax[i+1]].y) sufmax[i]=i;
			else sufmax[i]=sufmax[i+1];
		}
		for(int i=1;i<=m;i++)
		{
			int maxnid=0; 
			auto j=upper_bound(g+1,g+n+1,Node(by[i],100000000,0))-g;
			if(j>=1&&j<=n)
			{
				int maxnid=sufmax[j];
				maxnid=g[maxnid].id;
				G[maxnid].emplace_back(i+n),in[i+n]++;
			}
		}
		queue<int> q;
		for(int i=1;i<=n+m;i++)
		{
			if(in[i]==0)
			{
				q.push(i);
				dp[i]=1;
			}
		}
		while(q.size())
		{
			auto u = q.front();
			q.pop();
			for(auto&j:G[u])
			{
				if(vis[j]) continue;
				in[j]--;
				if(dp[u]==1)
				{
					dp[j]=0;
					vis[j]=1;
					q.push(j);
				}
				else if(in[j]==0)
				{
					dp[j]=1;
					q.push(j);
					vis[j]=1;
				}
			}
		}
		int a1=0,a2=0,a3=0;
		for(int i=1;i<=n;i++)
		{
			a1+=(dp[i]==1);
			a2+=(dp[i]==-1);
			a3+=(dp[i]==0);
		}
		cout<<a1<< " " << a2 << " " << a3 << "\n";
	}
	return 0;
}

```


---

## 作者：SunnyYuan (赞：0)

## 思路

首先我们初始化出每个人出牌后对手出的牌，因为我们要保证消灭对手的同时最大化自己的防御能力，所以第一件事情就是使用排序 + 二分 + 后缀最大值求出对于每一张牌 $(x, y)$ 的对方出的 $(t, v)$ 使得 $t > x$ 且让 $v$ 最大化，找出后我们将它们连边，即 $(x, y) \rightarrow (t, v)$。

然后我们进行拓扑排序，如果拓扑排序后还有剩余的点，那么这些点会形成环，这些点就会造成平手。

然后对于剩下的部分，我们设 $f_i$ 表示第一次就出牌 $i$ 谁会赢，如果 $f_i = 1$ 那么表示先手 Monocarp 赢，$f_i = 2$ 后手 Bicarp 赢，$f_i = 0$ 表示此点处于一个环中，上面已经讨论过。

我们从后往前遍历拓扑序，对于当前点 $u$，如果存在边 $(u, v)$，就将 $v$ 的状态继承过来，即 $f_u = f_v$，如果 $u$ 的出度为 $0$，那么判断 $u$ 与 $n$ 的关系，如果 $u \le n$，那么 $f_u = 1$，否则 $f_u = 2$。

最后遍历整个 $f$ 数组求助 3 个答案。

## 代码

注意不能用 `memset` 初始化，会 TLE。

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: Infinite Card Game
| OJ:      Luogu
| URL:     https://www.luogu.com.cn/problem/CF1895E
| When:    2023-11-04 15:13:20
| 
| Memory:  500 MB
| Time:    3000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;

const int N = 600010, INF = 0x3f3f3f3f;

struct edge {
    int to, next;
} e[N];

int head[N], in[N], idx;

void add(int u, int v) {
    idx++, e[idx].to = v, e[idx].next = head[u], head[u] = idx, in[v]++;
}

struct node {
    int x, y;
    bool operator<(const node b) const { return x < b.x; }
} p1[N], p2[N];

int n, m;
int max1[N], max2[N];
int f[N];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p1[i].x;
    for (int i = 1; i <= n; i++) cin >> p1[i].y;
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> p2[i].x;
    for (int i = 1; i <= m; i++) cin >> p2[i].y;

    // 初始化
    for (int i = 0; i <= n + m; i++) f[i] = in[i] = 0, head[i] = 0;
    max1[n + 1] = max2[m + 1] = idx = 0;

    sort(p1 + 1, p1 + n + 1);
    sort(p2 + 1, p2 + m + 1);

    for (int i = n; i >= 1; i--) {
        max1[i] = max1[i + 1];
        if (p1[max1[i]].y < p1[i].y) max1[i] = i;
    }
    for (int i = m; i >= 1; i--) {
        max2[i] = max2[i + 1];
        if (p2[max2[i]].y < p2[i].y) max2[i] = i;
    }

    for (int i = 1; i <= n; i++) {
        int l = 1, r = m + 1;
        while (l < r) {
            int mid = l + r >> 1;
            if (p2[mid].x > p1[i].y) r = mid;
            else l = mid + 1;
        }
        if (l > m) continue;
        add(i, max2[l] + n);
    }

    for (int i = 1; i <= m; i++) {
        int l = 1, r = n + 1;
        while (l < r) {
            int mid = l + r >> 1;
            if (p1[mid].x > p2[i].y) r = mid;
            else l = mid + 1;
        }
        if (l > n) continue;
        add(i + n, max1[l]);
    }

    vector<int> ans;
    queue<int> q;

    for (int i = 1; i <= n + m; i++) if (!in[i]) q.push(i);
    while (q.size()) {
        int t = q.front();
        q.pop();
        ans.push_back(t);

        for (int i = head[t]; i; i = e[i].next) {
            int to = e[i].to;
            if (!(--in[to])) q.push(to);
        }
    }
    int ans1 = 0, ans2 = 0, ans3 = 0;
    for (int j = ans.size() - 1; j >= 0; j--) {
        int cur = ans[j];
        for (int i = head[cur]; i; i = e[i].next) {
            int to = e[i].to;
            f[cur] = f[to];
        }
        if (!head[cur]) {
            if (cur > n) f[cur] = 2;
            else f[cur] = 1;
        }
    }
    for (int i = 1; i <= n; i++) { // 注意这里是 n 而不是 n + m
        if (f[i] == 1) ans1++;
        if (f[i] == 0) ans2++;
        if (f[i] == 2) ans3++;
    }
    cout << ans1 << ' ' << ans2 << ' ' << ans3 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
```

---

