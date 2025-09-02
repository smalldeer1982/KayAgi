# [ABC212F] Greedy Takahashi

## 题目描述

### 题目大意

有 $n$ 座城市和 $m$ 辆公交车，第 $i$ 辆公交车会在 $S_i+0.5$ 时从城市 $A_i$ 出发，在 $T_i+0.5$ 时到达城市 $B_i$。

Takahashi 想要在这些城市中旅行。具体的说，当他在 $t$ 时刻时位于城市 $p$ 时，他会按照如下方案移动：

若存在在 $t$ 时刻后从城市 $p$ 出发的公交车，那么选择其中离 $t$ 时刻最近的一辆并乘坐。否则停留在城市 $p$ 不移动。

现在 Takahashi 想要问你 $Q$ 个问题，每个问题的格式如下：

如果 Takahashi 在 $X$ 时刻从城市 $Y$ 出发，那么 $Z$ 时刻时 Takahashi 位于哪辆公交车上或者哪个城市中？

## 样例 #1

### 输入

```
3 2 3
1 2 1 3
2 3 3 5
1 1 5
2 2 3
1 3 2```

### 输出

```
2 3
2
3```

## 样例 #2

### 输入

```
8 10 10
4 3 329982133 872113932
6 8 101082040 756263297
4 7 515073851 793074419
8 7 899017043 941751547
5 7 295510441 597348810
7 2 688716395 890599546
6 1 414221915 748470452
6 4 810915860 904512496
3 1 497469654 973509612
4 1 307142272 872178157
374358788 4 509276232
243448834 6 585993193
156350864 4 682491610
131643541 8 836902943
152874385 6 495945159
382276121 1 481368090
552433623 2 884584430
580376205 2 639442239
108790644 7 879874292
883275610 1 994982498```

### 输出

```
4
6 1
4 1
8
6 1
1
2
2
7 2
1```

# 题解

## 作者：LPhang (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc212_f)

考虑模拟，首先把每一趟巴士和每一个查询拆成两个部分：

- 巴士：上车部分 $($ 类型 $4)$ 和下车部分 $($ 类型 $3)$
- 查询：出发部分 $($ 类型 $1)$ 和结束部分 $($ 类型 $2)$

```cpp
rep1(i, 1, m) {
	int x, y; scanf("%d%d%d%d", l + i, r + i, &x, &y);
	p[++tot] = {l[i], x, i, 4}; p[++tot] = {r[i], y, i, 3};
}
rep1(i, 1, q) {
	int x, y, s; scanf("%d%d%d", &x, &s, &y);
	p[++tot] = {s, x, i, 1}; p[++tot] = {0, y, i, 2};
}
```

然后以时间为第一关键字，类型为第二关键字从小到大排序（因为查询是整点时刻，而巴士则是多了 $0.5$ 小时，所以对于同一个时刻，查询的类型应该在巴士的前面，其次，对于同一时刻的上车和下车，不可能是同一趟巴士，所以为了下车之后能立即上车，应该将下车的类型放在上车的前面）


```cpp
bool cmp(node x, node y) {return x.t == y.t ? x.op < y.op : x.t < y.t;}
```

---

这个时候我们会发现，如果直接模拟，每个查询会从各个城市出发并乘坐各个巴士，最坏情况会移动 $O(n)$ 次，对于 $Q$ 个查询，复杂度为 $O(nQ)$ ，显然会超时。这个时候可以发现一个性质，当有大于一个的行程**同时**处于**同一个**城市的时候，之后这几个行程的行动路线将会**一模一样**，所以，对于所有这样出现在一个城市的行程，我们可以用**并查集**把他们**并做一个行程**，从而避免**多个行程重复移动**的过程，当其中一个行程需要结束的时候，只需要访问祖先节点并记录当前状态，就是答案。具体处理如下：

- 类型一：对于行程 $id$ ，高桥会从 $t$ 时刻从城市 $s$ 出发，此时如果城市 $s$ 已有其他行程，则与这个行程进行合并，否则将此行程记录于城市 $s$ 当中，并更新城市 $s$ 当中的行程状态。

```cpp
if(op == 1) {
	int x = c[s]; if(!x) c[s] = id;
	if(x && fa(x) != fa(id)) hb(x, id);
	c[s] = fa(c[s]); tr[c[s]] = {0, s};
}
```

- 类型二：对于行程 $id$ ，高桥即将于 $t$ 时刻结束行程，访问祖先节点，记录此行程的答案为当前状态。（注意，此时不能删除该行程，因为可能有其他行程跟此行程合并但并未结束行程，所以应让该行程继续行动）

```cpp
if(op == 2) {int x = fa(id); ans[id] = tr[x];}
```

- 类型三：对于巴士 $id$ ，巴士会于 $t$ 时刻把车上的行程送到城市 $s$ ，如果城市 $s$ 已有行程，则进行合并，否则记录，并更新行程状态。（注意，如果巴士上没有行程，不能合并）

```cpp
if(op == 3) {
	int x = c[s]; if(!x) c[s] = b[id];
	if(x && b[id] && fa(x) != fa(b[id])) hb(x, b[id]);
	c[s] = fa(c[s]); tr[c[s]] = {0, s};
}
```

- 类型四：对于巴士 $id$ ，巴士将于 $t$ 时刻把位于城市 $s$ 的行程带往下一个城市，撤销城市 $s$ 当中的行程状态，添加巴士的行程状态，并更新此行程的状态。

```cpp
if(op == 4) {
	b[id] = c[s]; c[s] = 0;
	tr[b[id]] = {1, id};
}
```

最后根据状态输出答案

```cpp
rep1(i, 1, q) {
	if(ans[i].ft) printf("%d %d\n", l[ans[i].sd], r[ans[i].sd]);
	else printf("%d\n", ans[i].sd);
}
```

---

## 作者：Pengzt (赞：6)

[ABC212F](https://www.luogu.com.cn/problem/AT_abc212_f)

暴力就是直接跳，显然不可过。

考虑对暴力进行优化，发现整个图是不会改变的，容易想到使用倍增。

显然是对边进行倍增的，令 $f_{i, j}$ 表示从第 $i$ 条边开始，跳了 $2^j$ 条边后，到的是哪一条边，如果不存在，则设为 $-1$。

然后就是很显然的倍增了，最后讨论一下即可。

时间复杂度：$\mathcal{O}((m + Q) \log m)$

[评测记录](https://atcoder.jp/contests/abc212/submissions/43537000)

---

## 作者：lflby (赞：2)

# 思路

若起点确定，出发时刻确定，则接下来的每一步行程都是确定的。

但这样会超时，所以不难会想到倍增。

倍增优化这一过程。时刻范围是 $10^9$ ，对时刻倍增是不现实的。应该对车倍增，即处理坐上某辆车后，之后会坐什么车。

具体情况如下：

$f(i,0)$ 表示坐上第 $i$ 辆车后，下 $1$ 辆车是哪辆车。

$f(i,j),j>1$ 表示坐上第 辆车后，下 $2^i$ 辆车是哪辆车。

在细分可以自己思考，或者看代码注释。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, M = 19;
int n, m, q, f[N][M];
struct O
{
    int u, v, t0, t1, id;
    friend bool operator< (const O &lhs, const O &rhs)
    {
        return lhs.t0 < rhs.t0;
    }
} car[N];
vector<O> city[N];
int get(int u, int t)
{
    auto p = lower_bound(city[u].begin(), city[u].end(), O {0, 0, t, 0, 0});
    if (p == city[u].end()) return 0; // 没车可坐
    return p->id;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> q;
    for (int i = 1; i <= m; ++i)
    {
        int u, v, t0, t1;
        cin >> u >> v >> t0 >> t1;
        car[i] = {u, v, t0, t1, i};
        city[u].push_back({u, v, t0, t1, i});
    }
    for (int u = 1; u <= n; ++u)
        sort(city[u].begin(), city[u].end());
// 倍增
    for (int i = 1; i <= m; ++i)
    {
        f[i][0] = get(car[i].v, car[i].t1);
    }
    for (int j = 1; j <= __lg(m); ++j)
        for (int i = 1; i <= m; ++i)
            f[i][j] = f[f[i][j - 1]][j - 1];
    while (q--)
    {
        int u, t0, t1;
        cin >> t0 >> u >> t1;
        int x = get(u, t0); // 找个车坐坐
        if (!x || car[x].t0 >= t1)   // 根本坐不了车
        {
            cout << u << '\n';
        }
        else
        {
            for (int i = __lg(m); i >= 0; --i)   // 开车gogogo
            {
                if (f[x][i] && car[f[x][i]].t0 < t1) x = f[x][i];
            }
            if (car[x].t1 >= t1) cout << car[x].u << ' ' << car[x].v << '\n';
            else cout << car[x].v << '\n';
        }
    }
    return 0;
}
```

---

## 作者：yzysdTNT (赞：1)

## 思路
根据题意我们可以知道，当起点与出发的时间确定时，下面的**每一步路**都是确定的，因为每一次坐车的到达时间都是相同的，即坐上一辆车后的每一步行程都固定。

因此考虑提前预处理出坐上某辆车后的每一步行程，用倍增优化；  
定义 $f_{i,j}$ 表示坐上第 $i$ 辆车后的下 $2^j$ 辆车，正常倍增做即可。  
比较麻烦的是处理询问的部分，先二分找到可以坐的车子，然后再往下凑。具体看代码注释吧（应该还比较清晰吧……）。
## [CODE](https://www.luogu.com.cn/record/162806227)
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5,M = 19;
int n,m,q,f[N][M];

struct O{
	int u,v,t0,t1,id;
	friend bool operator < (O a,O b){
		return a.t0 < b.t0;
	}
}car[N];
vector<O> ct[N];//城市间互通的车

int get(int u,int ti){
	auto p = lower_bound(ct[u].begin(),ct[u].end(),O{0,0,ti,0,0});
	if(p == ct[u].end()) return 0;
	return p->id;
}//二分找车

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> q;
	for(int i = 1;i <= m;i++){
		int u,v,t0,t1;
		cin >> u >> v >> t0 >> t1;
		car[i] = {u,v,t0,t1,i};
		ct[u].push_back({u,v,t0,t1,i});
	}
	for(int u = 1;u <= n;u++){
		sort(ct[u].begin(),ct[u].end());
	}
	
	for(int i = 1;i <= m;i++){
		f[i][0] = get(car[i].v,car[i].t1);
	}
	for(int i = 1;i <= __lg(m);i++){
		for(int j = 1;j <= m;j++){
			f[j][i] = f[f[j][i - 1]][i - 1];
		}
	}
	while(q--){//重点
		int u,t0,t1;
		cin >> t0 >> u >> t1;
		int x = get(u,t0);//二分找符合条件的车
		if(!x || car[x].t0 >= t1) cout << u << '\n';//一辆车都坐不了——当前城市
		else{
			for(int i = __lg(m);i >= 0;--i){
				if(f[x][i] && car[f[x][i]].t0 < t1) x = f[x][i];
			}
			if(car[x].t1 >= t1) cout << car[x].u << ' ' << car[x].v << '\n';//这个时刻还没抵达——在路上
			else cout << car[x].v << '\n';//在景点里
		}
	}
	return 0;
}
```

---

## 作者：As_Snow (赞：1)

## Solution

容易想到对于每一辆公交车，下车后乘坐的下一辆车是固定的，所以向其连一条边。最后可以建出一片森林，然后跑倍增就完了。

### [Code](https://atcoder.jp/contests/abc212/submissions/44134432)

---

## 作者：Expert_Dream (赞：0)

这道题有一个很显然的结论：

- 在坐完每一辆车之后必定会到达离你最近到达的车，因此在每一辆车之后有唯一对应的一辆车作为后继，考虑建图，这就是一条树边。你会发现，这，其实就是一棵树。

然后对于每一个点有 $ T - S$ 的时间代价，他们两辆车之间也有，所以只需要处理出每一条树边的边权，那么你要找一个时刻，相当于在树上进行倍增。

倍增也不是很难。这题就是细节非常的多。

具体看代码，代码比较短。

[link](https://atcoder.jp/contests/abc212/submissions/52288180)。

---

## 作者：WaterSun (赞：0)

# 思路

通常来说，对于倍增问题 $dp_{i,j}$ 表示的是以 $i$ 为起点，走 $2^j$ 步的答案。

但是，对此此题，如果对于点倍增，因为每一个点可能会有多条边经过，所以，不能对点进行倍增。

但如果对边进行倍增，无论怎么走 $2^j$ 步后的位置一定相同，所以考虑对每一条边倍增。

定义 $dp_{i,j}$ 表示，在第 $i$ 个城市，时间为 $j$ 时，第一辆能坐上的车；特别地，如果没有则为 $-1$。

其余的与普通倍增相同。

# code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register

using namespace std;

typedef pair<int,int> pii;
const int N = 1e5 + 10,M = 25;
int n,m,q;
int dp[N][M];
set<pii> st[N];

struct edge{
	int a;
	int b;
	int s;
	int t;
}arr[N];

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

inline int get(int x,int k){
	auto it = st[x].lower_bound({k,0});
	if (it == st[x].end()) return -1;
	return (*it).snd;
}

int main(){
	memset(dp,-1,sizeof(dp));
	n = read();
	m = read();
	q = read();
	for (re int i = 1;i <= m;i++){
		arr[i].a = read();
		arr[i].b = read();
		arr[i].s = read();
		arr[i].t = read();
		st[arr[i].a].insert({arr[i].s,i});
	}
	for (re int i = 1;i <= m;i++) dp[i][0] = get(arr[i].b,arr[i].t);//维护 dp 数组 
	for (re int j = 0;j < 20;j++){
		for (re int i = 1;i <= m;i++){
			if (~dp[i][j - 1]) dp[i][j] = dp[dp[i][j - 1]][j - 1];
		}
	}
	while (q--){
		int x,y,z;
		x = read();
		y = read();
		z = read();
		int p = get(y,x);
		if (!~p) printf("%d\n",y);//无法走动 
		else{
			for (re int i = 19;~i;i--){
				if (~dp[p][i] && arr[dp[p][i]].s < z) p = dp[p][i];//一直往后走 
			}
			if (arr[p].s >= z) printf("%d\n",arr[p].a);
			else if (arr[p].t < z) printf("%d\n",arr[p].b);
			else printf("%d %d\n",arr[p].a,arr[p].b);
		}
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：0)

考虑每条边，因为是静态的，所以可以预处理出 $f_{i,j}, g_{i,j}$ 表示从第 $i$ 条边，往后跳 $2^j$ 条边，跳到边的编号和目前的时间（如果不存在就当作跳到第 $0$ 条边）。直接倍增处理即可。

询问就是找到从 $u$ 开始的出边，能跳尽量跳。

注意一些细节。

[code](https://atcoder.jp/contests/abc212/submissions/41493057)

---

