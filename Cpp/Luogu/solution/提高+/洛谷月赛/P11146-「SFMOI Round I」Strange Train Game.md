# 「SFMOI Round I」Strange Train Game

## 题目背景

SFM 团队又断网了，于是玩起了 Mini Metro，结果发现游戏更新了，列车要自己组装，于是有了这题。



## 题目描述

**提示**：我们在题目描述的最后提供了一份简要的、形式化描述的题面。

SFM 号列车由 $n$ 节车厢组成，编号为 $1\sim n$。每节车厢有一个舒适度 $a_i\in \{0,1\}$，$0$ 代表不舒适，$1$ 代表舒适。管理组想要让舒适的车厢的编号尽量小，也就是说，让 $a$ 的字典序最大。

为此，管理组运来了一辆 $n$ 节车厢的备用车，舒适度表示为 $b_i\in \{0,1\}$。共有 $m$ 个可进行的操作，第 $i$ 个操作的操作参数为 $l_i,r_i$，表示 $\forall l_i\le k\le r_i$，交换 $a_k,b_k$。

可以**从小到大依次**决定是否执行每个操作，但是一共有 $2^m$ 种方案，于是，管理组找来了你，帮忙选出一种最优的方案，最大化 $a$ 的字典序。只需要输出最终得到的 $a$ 即可。

**形式化地**：给定长度为 $n$ 的 $01$ 串 $a,b$，给定 $2m$ 个正整数 $l_i,r_i$。对于 $i=1,2,\cdots,m$，**依次**执行以下操作：
- 选择是否执行第 $i$ 次操作。
    - 如果执行，则对于 $k=l_i,l_{i}+1,\cdots,r_i$，交换 $a_k,b_k$。

最大化 $a$ 的字典序并输出最终的结果。


## 说明/提示

**本题采用捆绑测试。**

- Subtask 1（20 pts）：$1\le n,m\le 20$；
- Subtask 2（30 pts）：$l_i$ 互不相同，$a_i \ne b_i$；
- Subtask 3（30 pts）：$1 \le n ,m \le 10^3$；
- Subtask 4（20 pts）：无限制；

对于 $100\%$ 的数据，保证：
- $1\le n,m\le 2\times 10^5$；
- $1\le l_i\le r_i\le n$。

## 样例 #1

### 输入

```
10 5
0101011001
0101001110
5 10
2 6
1 10
6 6
3 4```

### 输出

```
0101011110```

# 题解

## 作者：幸存者 (赞：46)

自认为非常好写的做法，凭借这个拿到了 16min 一血。

考虑依次确定每一位，对于第 $i$ 位：

- 如果 $a_i=b_i$，这一位没有影响，可以直接把左端点为 $i$ 的区间左端点改成 $i+1$。

- 如果 $a_i=1,b_i=0$，那么一定选偶数个左端点为 $i$ 的区间，不妨设左端点为 $i$ 的区间中右端点最小的为 $[i,x]$。所以所选的偶数个区间都包含 $[i,x]$，恰好抵消掉了，于是可以直接删掉 $[i,x]$，把剩余的左端点为 $i$ 的区间左端点改成 $x+1$。

- 如果 $a_i=0,b_i=1$，那么一定选奇数个左端点为 $i$ 的区间，不妨设左端点为 $i$ 的区间中右端点最小的为 $[i,x]$。本质上和上面是一样的，只需要类似差分把 $[i,x]$ 区间内打一个交换标记就可以了。

简单思考一下，你会发现这个东西完全可以用 set 维护每个左端点对应的右端点构成的集合，启发式合并即可。

时间复杂度 $O(n\log^2n)$，但代码真的很短。

```cpp
// superyijin AK IOI
// wangsiyuanZP AK IOI
#include <bits/stdc++.h>
#define int long long
using namespace std;
set<int> s[200010];
int p[200010];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int n, m;
	string a, b;
	cin >> n >> m >> a >> b;
	for (int i = 1; i <= m; i++)
	{
		int l, r;
		cin >> l >> r;
		s[l].insert(r);
	}
	a = " " + a, b = " " + b;
	int now = 0;
	for (int i = 1; i <= n; i++)
	{
		now ^= p[i];
		if (now) swap(a[i], b[i]);
		if (a[i] == b[i])
		{
			cout << a[i];
			if (s[i].count(i)) s[i].erase(i);
			if (s[i].size() > s[i + 1].size()) swap(s[i], s[i + 1]);
			s[i + 1].insert(s[i].begin(), s[i].end());
		}
		else
		{
			if (s[i].empty()) cout << a[i];
			else
			{
				cout << "1";
				int x = *s[i].begin();
				s[i].erase(x);
				if (s[i].size() > s[x + 1].size()) swap(s[i], s[x + 1]);
				s[x + 1].insert(s[i].begin(), s[i].end());
				if (b[i] == '1') now ^= 1, p[x + 1] ^= 1;
			}
		}
	}
	cout << endl;
	return 0;
}
// superyijin AK IOI
// wangsiyuanZP AK IOI
```

---

## 作者：Register_int (赞：40)

先删掉所有 $a_i=b_i$ 的位置，那么所有区间操作等价于区间异或。

考虑对这些区间建线性基（天啊怎么想到的），很难不发现线性基里的每一位都是一个区间的形式。考虑归纳，假设当前线性基内每一位都是一个区间，考虑插入区间 $[l,r]$，他会与线性基的第 $l$ 位进行异或。根据线性基的性质，这个区间只能是 $[l,r']$，那么就是空区间、$[r'+1,r]$ 或者 $[r+1,r']$，仍是一个区间。

发现建线性基是 $O(n^2)$ 的，因为会被 $[1,1],[1,2],[1,3]\cdots$ 状物卡，但是你可以把区间 shuffle 一下再优化插入，每次直接跳到 $l$ 对应的位去异或，复杂度是均摊 $O(n)$ 的。那么就能过了。

```cpp
#include <bits/stdc++.h> 

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

mt19937 eng(time(0));

int n, m, p[MAXN], s[MAXN]; pair<int, int> w[MAXN];

char a[MAXN], b[MAXN]; int pos[MAXN], tp;

int main() {
	scanf("%d%d", &n, &m);
	scanf("%s%s", a + 1, b + 1);
	for (int i = 1; i <= n; i++) if (a[i] != b[i]) pos[++tp] = i;
	for (int i = 1, l, r; i <= m; i++) {
		scanf("%d%d", &w[i].first, &w[i].second);
		w[i].first = lower_bound(pos + 1, pos + tp + 1, w[i].first) - pos;
		w[i].second = upper_bound(pos + 1, pos + tp + 1, w[i].second) - pos - 1;
	}
	shuffle(w + 1, w + m + 1, eng);
	for (int i = 1, l, r; i <= m; i++) {
		l = w[i].first, r = w[i].second;
		if (l > r || l > tp || r < 1) continue;
		for (int j = l; j <= tp; j = l) {
			if (!p[j]) { p[j] = r; break; }
			if (r == p[j]) break;
			if (r < p[j]) l = r + 1, r = p[j];
			else l = p[j] + 1;
		}
	}
	for (int i = 1; i <= tp; i++) {
		s[i] ^= s[i - 1];
		if (s[i]) swap(a[pos[i]], b[pos[i]]);
		if (a[pos[i]] < b[pos[i]] && p[i]) {
			s[i] ^= 1, s[p[i] + 1] ^= 1;
			swap(a[pos[i]], b[pos[i]]);
		}
	}
	printf("%s", a + 1);
}
```

---

## 作者：TernaryTree (赞：13)

场外文化课选手口胡，来点不基于随机的线性做法。

首先，那些 $a_i=b_i$ 的位置不可能发生改变，这是显然的。那么，我们将这些位置从整个序列里面去掉，只保留 $a_i\neq b_i$ 的位置，称这些位置是“有效”的；然后预处理出原序列每个位置前一个/后一个有效位置，将我们输入区间转化为“有效”位置依次构成的序列内的区间，线性可以完成上述处理。

这相当于进行了一个简单的转化：给定一个 01 序列 $a$ 与 $m$ 个区间，选择一些区间依次对 a 进行区间 flip，使 a 字典序最大。

使一个 01 串字典序最大自然地能想到按位贪心：假设我们确定了前 $i-1$ 位的最优解，我们只需要判定第 $i$ 位能不能是 $1$。也就是我们确定了一个前缀，问能不能达成这个前缀。

考虑异或差分，$\forall 1\le i\le n+1$，令 $b_i=a_i \oplus a_{i-1}$（$a_0=a_{n+1}=0$）。那么对 $[l,r]$ 进行 flip 等价于，$b_l\gets b_l\oplus 1$，$b_{r+1}\gets b_{r+1}\oplus 1$。

很难不联想到建边。具体地，连 $m$ 条无向边 $(l,r+1)$。那么我们要判定的东西等价于，选出一些边，使得某一些点的出度的奇偶性恰好为指定的。我们对每个连通块考虑：

- 如果一个连通块存在一个奇偶性未被指定的点，这个连通块一定有解。

  证明：拉出这个连通块的一棵生成树，并以一个奇偶性未被指定的点为根；从下往上确定，$f(u)$ 表示满足 $u$ 子树内（不包括 $u$）的所有点的构造，那么只需要根据 $u$ 当前的奇偶性与实际需要的奇偶性决定 $u$ 与父亲的边是否选中，从而推至 $f(fa_u)$；由于根没有被指定，归纳即证毕。

- 否则，一个连通块所有点的奇偶性都被指定，此时有解的充要条件是，恰存在偶数个点的奇偶性被指定为奇数。

  必要性：考虑选中一条边不会改变所有点奇偶性之和的奇偶性，初始状态为 $0$，所以一定存在偶数个点为奇数。

  充分性：同“存在一个奇偶性未被指定的点”的构造，可以证明根结点此时一定满足条件。

综上，我们得到，无解当且仅当存在一个连通块满足：所有点奇偶性都被指定，且恰有奇数个点被指定为奇数。

继续观察我们查询的前缀的变化，不难发现每次 $i-1\to i$ 时只会修改这个前缀的 $\Theta(1)$ 个值，即单点修改。而单点修改，查询全局是否有解，对于每个连通块维护有多少个点被指定奇偶性，以及有多少被指定为奇数的点即可，容易做到 $\Theta(1)$ 修改与查询。于是我们在 $\Theta(n)$ 的线性复杂度内解决了这道题。

[Code](https://www.luogu.com.cn/paste/2zg1o84b)。

---

## 作者：Starrykiller (赞：12)

这里是官方题解。

我是造数据人，没有想到有那么多奇怪的做法，谢罪/dk

### Subtask 1

$\Theta(n\cdot 2^m)$ 暴力做即可。

### Subtask 2

给某些假掉的做法的分。也可以由此启发正解。

### Subtask 3

留给神秘做法的分。

### Subtask 4

把 $a_i=b_i$ 的位置全部删掉。设新的字符串为 $a',b'$，长度为 $N$，相应地更改操作的 $l,r$。

- 令 $c_i=[a'_i>b'_i]$（$1\le i\le N$）表示第 $i$ 个位置的最优策略（交换/不交换）。
- 令 $\mathrm{rev}_i$ 表示我们的实际操作。
- 对于每个操作 $l,r$，连无向边 $l \leftrightarrow r+1$，得到图 $G$。这张图有 $(N+1)$ 个节点。



我们断言：**能够交换区间 $[l,r]$ 且不影响别的位置，当且仅当节点 $l,r+1$ 在同一连通块中。**

> 证明：这意味着存在一条 $l\to r+1$ 的路径。不需要考虑走到编号小于 $l$ 或者大于 $r+1$ 的节点的情况，因为如果走过去了必然会走回来，偶数次操作会 $[l,r+1)$ 外的所有位置的影响抵消。


由于我们要求字典序最大，从小到大考虑 $i=1,2,\ldots,N$。

**我们想要尽量让 $\mathrm{rev}_i=c_i$。**

- 若 $\mathrm{rev}_i=c_i$，无事可做，直接跳过。
- 否则，令 $k=\max\{u|u\text{ is reachable from }i\}$。即 $i$ 能到达的点中编号最大的。
  - 若 $k=i$，这意味着 $\mathrm{rev}_i$ 无法被改变。
  - 否则，我们操作 $[i,k)$。将 $\mathrm{rev}_i \sim \mathrm{rev}_{k-1}$ 全部异或上 $1$。

视 $n,m$ 同阶，这样我们就在 $\Theta(n)$ 或 $\Theta(n \alpha(n))$ 或 $\Theta(n \log n)$ 内解决了本题。

> **证明**：
> 根据贪心性质，我们需要**优先满足较低位**上的 $\mathrm{rev}_i=c_i$。
>
> 在需要操作且可操作的情况下，必然存在若干决策点 $k_1,\ldots,k_p$，不妨令 $i<k_1<\ldots<k_p=k$。**显然它们都在同一个连通块里。**
>
> - 必然存在一个 $1\le j\le p$ 使得操作 $[i,k_j)$ 是最优的。我们操作了 $[i,k_p)$ 后，可以在 $k_j$ 处操作 $[k_j,k_p)$ 来抵消影响（可以理解为**反悔**）。
> - 同时，操作 $[i,k_p)$ 不会影响到之前位置的状态。
>
> 综上，这样的解法是正确的。

---

## 作者：251Sec (赞：7)

C < B2。

---

先把 $a_i=b_i$ 的点删掉然后对所有区间端点重标号。现在我们假定 $a_i \ne b_i$。

定义 $c_i=1$ 代表最终第 $i$ 个位置取 $b_i$，$c_i=0$ 代表取 $a_i$。考虑对 $c_i$ 作差分得到 $d_i$，每次操作就是把 $l$ 和 $(r+1)$ 的 $d$ 异或 $1$。考虑图论建模，$l$ 和 $(r+1)$ 连边，最终一个 $d$ 序列合法当且仅当每个连通块里都有偶数个 $1$。

于是考虑直接从左往右贪心，如果一个点是连通块里标号最大的点那么它的状态已经确定，否则我们选择更优的那一个。

---

## 作者：elbissoPtImaerD (赞：6)

来一个不会证复杂度的 set 启发式合并做法。

首先 $l$ 互不相同是简单的，从高往低按位贪心即可。

记 $S_l$ 表示以 $l$ 为左端点的操作区间的右端点形成的集合。

$l$ 相同时，我们考虑将 $r$ 按升序排序，需要操作时，选择 $r$ 最小的 $r_0$ 进行操作，然后加入区间 $[r_{i-1},r_i)$ 作为反悔操作。

而 $a_i = b_i$ 时，$i$ 位是不需要考虑的，可以 $S_{i+1} \gets S_i \cup S_{i+1}$。

使用 set 维护 $S_i$ 集合启发式合并，跑得飞快。

```cpp
struct BITS {
  ve<int>t;
  void Init(int n) {
    t.assign(n+2,0);
  }
  void _M(int x,int y) {
    for(++x;x<Sz(t);x+=x&-x) t[x]+=y;
  }
  void M(int l,int r) {
    _M(l,1),_M(r,-1);
  }
  int Q(int x) {
    int s=0;
    for(++x;x;x-=x&-x) s+=t[x];
    return s&1;
  }
}T;
void Solve() {
  int n,m; cin>>n>>m; T.Init(n);
  string a,b; cin>>a>>b;
  ve<set<int>>S(n+1);
  for(;m--;) {
    int l,r; cin>>l>>r,--l;
    S[l].ep(r);
  }
  for(int i=0;i<n;++i) if(Sz(S[i])) {
    if(a[i]==b[i]) {
      if(Sz(S[i])>Sz(S[i+1])) S[i].swap(S[i+1]);
      for(int r:S[i]) if(i+1<r) S[i+1].ep(r);
    }
    else {
      int lst=*begin(S[i]);
      for(;i>=lst&&Sz(S[i]);S[i].erase(begin(S[i])),lst=*begin(S[i]));
      if(lst>i) {
        if((a[i]<b[i])!=T.Q(i)) T.M(i,lst);
        for(int r:S[i]) T.M(lst,r),S[lst].ep(r),lst=r;
      }
    }
    S[i].clear();
  }
  for(int i=0;i<n;++i) if(T.Q(i)) swap(a[i],b[i]);
  cout<<a;
  return;
}
```

---

## 作者：takanashi_mifuru (赞：4)

场上写的神秘做法，感觉时间复杂度不是很对，但是跑得飞快。

首先考虑分析子任务 2，容易发现其实就是扫描线一下区间左端点，能换就换。

那我们首先缩掉换不换没影响的段，然后考虑扫描线一下，但是如果左端点相同咋办嘞，我咋知道哪些取哪些不取？

考虑对于相同的左端点，我们把他的影响画出来。

![](https://pic.imgdb.cn/item/66fd2ed3f21886ccc00ae861.png)

那么容易发现，这中间所有带颜色的段都可以用这个左端点来做落差，然后就可以用这些东西来操作区间翻转。

而橙色是来影响翻转当前点的，后面没有人能影响，各个小段各自独立，所以你就按照最优的方案翻橙色，然后把红色全部塞到后面去就可以了。

时间复杂度不会证明，但是好像跑得很快，图省事写了个 BIT，UFS 可以做到线性。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
string A[2];
vector<int> need[200005];
int ans[200005];
int diff[200005];

int seta[2][200005],all;
int rnk[200005];

class BIT{
    public:
    int c[200005];
    int lowbit(int x){return x&-x;}
    void add(int x,int y){
        while(x<=n){
            c[x]+=y;
            x+=lowbit(x);
        }
        return;
    }
    int ask(int x){
        int sum=0;
        while(x){
            sum+=c[x];
            x-=lowbit(x);
        }
        return sum;
    }
}P,Q;

int main(){
    scanf("%d%d",&n,&m);
    cin>>A[0]>>A[1];
    A[0]='?'+A[0],A[1]='?'+A[1];
    for(int i=1;i<=n;i++){
        if(A[0][i]!=A[1][i]){
            P.add(i,1);
            all++;
            seta[0][all]=A[0][i];
            seta[1][all]=A[1][i];
            rnk[all]=i;
        }
    }
    for(int i=1;i<=m;i++){
        int lt,rt;
        scanf("%d%d",&lt,&rt);
        int L=P.ask(lt-1)+1,R=P.ask(rt);
        if(R<L)continue;
        need[L].push_back(R);
    }
    for(int i=1;i<=all;i++){//考虑按照这些把他切成若干个小段，然后把最小的给拿下，考虑对于一个点
        sort(need[i].begin(),need[i].end());
        bool flg=Q.ask(i)&1;
        if(!need[i].size()){
            ans[rnk[i]]=flg;
            continue;
        }
        if(seta[!flg][i]>seta[flg][i]){//需要交换，赶紧来换一下
            Q.add(i,1);
            Q.add(need[i][0]+1,-1);
        }
        flg=Q.ask(i)&1;
        for(int j=0;j+1<need[i].size();j++){//加小段
            int L=need[i][j]+1,R=need[i][j+1];
            if(L>R)continue;
            need[L].push_back(R);
        }
        ans[rnk[i]]=flg;
    }
    for(int i=1;i<=n;i++){
        putchar(A[ans[i]][i]);
    }
    puts("");
    return 0;
}
```

---

## 作者：EricWan (赞：3)

对于两数相等的位，我们忽略。

对没有被忽略的位进行离散化。

首先，我们知道：一个操作执行两次相当于没有操作。

而且，对于头相等尾相等的两个操作，我们可以忽略一个。

对于头相等尾不相等的 $[a,b]$ 和 $[a,c]$ 满足 $b<c$，我们可以证明那两个操作等价于 $[a,b]$ 和 $[b+1,c]$。

然后我们就获得了头不相等的一系列操作，排序操作，从第一个开始枚举即可，优先考虑前面的位置。

输出时把忽略的位置记得也输出了。

code:

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(x) ((x)&-(x))
#define MAXN 1000005
using namespace std;
int n, m, a[MAXN], b[MAXN], olda[MAXN], nn, useful[MAXN], t[MAXN];
struct opera {
	int l, r;
} oldq[MAXN];
vector<int> opvec[MAXN], usefulvec;
char c;
int querya(int x) {
	int rx = x;
	int ans = 0;
	while (x) {
		ans ^= t[x];
		x ^= lowbit(x);
	}
	if (ans == 0)
		return a[rx];
	else
		return b[rx];
}
int queryb(int x) {
	int rx = x;
	int ans = 0;
	while (x) {
		ans ^= t[x];
		x ^= lowbit(x);
	}
	if (ans == 0)
		return b[rx];
	else
		return a[rx];
}
void update(int x) {
	while (x <= nn) {
		t[x] ^= 1;
		x += lowbit(x);
	}
}
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> c;
		olda[i] = a[i] = c - '0';
	}
	for (int i = 1; i <= n; i++) {
		cin >> c;
		b[i] = c - '0';
	}
	for (int i = 1; i <= m; i++) {
		cin >> oldq[i].l >> oldq[i].r;
	}
	for (int i = 1; i <= n; i++) {
		if (a[i] != b[i] && useful[i] == 0)
		{
			useful[i] = 1;
			usefulvec.push_back(i);
			nn++;
			a[nn] = a[i];
			b[nn] = b[i];
		}
	}
	usefulvec.push_back(100000000);
	for (int i = nn + 1; i <= n; i++) {
		a[i] = b[i] = 0;
	}
	for (int i = 1; i <= m; i++) {
		int l = lower_bound(usefulvec.begin(), usefulvec.end(), oldq[i].l) - usefulvec.begin() + 1;
		int r = upper_bound(usefulvec.begin(), usefulvec.end(), oldq[i].r) - usefulvec.begin();
		if (l <= r) {
			opvec[l].push_back(r);
		}
	}
	for (int i = 1; i <= nn; i++) {
		if (opvec[i].empty()) continue;
		sort(opvec[i].begin(), opvec[i].end());
		for (int j = 1; j < opvec[i].size(); j++) {
			if (opvec[i][j - 1] == opvec[i][j]) continue;
			opvec[opvec[i][j - 1] + 1].push_back(opvec[i][j]);
		}
		if (querya(i) == 0 && queryb(i) == 1) {
			update(i);
			update(opvec[i][0] + 1);
		}
	}
	for (int i = 1, j = 0; i <= n; i++) {
		if (useful[i] == 0) {
			cout << olda[i];
		}
		else {
			cout << querya(++j);
		}
	}
	return 0;
}
```

---

## 作者：sbno333 (赞：2)

优秀的题目，可以很好的练习线性基。

思考时发现交换与与异或有着类似的性质，即进行两次相同的操作相对于没操作，同时满足交换律结合律。

于是考虑线性基维护，类似的，我们对于第 $i$ 个位置，表示的是以 $i$ 为左边界的一个区间交换操作，类似于异或的最高位为 $i$ 位。

接着我们尝试存储。

每一次都是按照左边界找到对应位置，然后是当前右边界为 $r$，如果这个位置为 $0$（即没有数）或者和当前一样，就结束，否则设当前位置为 $y$，我们变成了插入区间 $[\min(r,y)+1,\max(r,y)]$。

这个复杂度就是 $O(n^2)$，不能接受，考虑优化。

一个套路是改变插入顺序，需要排序。

发现按照 $r$ 从小到大排序，可以在每次试图插入时处理得到的新区间的右边界与之前相同，因为永远比对应位置的数大或等于。

我们再找位置就只和 $\min(r,y)+1$ 有关，这里变成了 $y+1$，$y$ 显然不会发生改变，所以我们可以并查集状物维护去哪个位置插入。

设线性基第 $i$ 个位置为 $f_i$，指向的就是 $f_{f_i+1}$。

于是我们成功插入。

我们考虑接下来怎么办，按照异或贪心即可，假设 $a_i\not=b_i$，每次按左边界从小到大贪心的异或即可，这里相当于每次区间是否交换的状态改变，每次判断需要判断当前位置是否已经交换，以及 $a_i$ 与 $b_i$ 大小关系判断是否需要交换来判断是否选取，这里可以树状数组。

考虑 $a_i=b_i$ 的位置就是自动忽略，但是插入时也要注意忽略，我们每次插入的区间左边界和右边界都要缩到最近的不等位置，容易处理。

于是代码 $O(n\log n+m\log m)$。

```cpp
#include<bits/stdc++.h>
using namespace std; 
bool a[300009];
bool b[300009];
int z[300009];
int xxj[300009];
int fa[300009];
struct st{
	int l,r;
}q[300009];
bool cmp(st a1,st a2){
	return a1.r<a2.r;
}
int nxt[1000009];
int pre[1000009];
int add(int t,int r){
	t=nxt[t];
	r=pre[r];
	if(t>r){
		return t;
	}
	if(r==xxj[t]){
		return t;
	}
	if(xxj[t]==0||t==r){
		xxj[t]=r;
		return t;
	}
	return fa[t]=add(fa[xxj[t]+1],r);
}
struct szsz{
	int f[300009];
	int lowbit(int x){
		return x&(-x);
	}
	void ad(int x,int y){
		while(x<=300000){
			f[x]+=y;
			x+=lowbit(x);
		}
	}
	int que(int x){
		int ans;
		ans=0;
		while(x){
			ans+=f[x];
			x-=lowbit(x);
		}
		return ans;
	}
	void sp(int l,int r){
		ad(l,1);
		ad(r+1,-1);
	}
	int q(int x){
		return (que(x)&1);
	}
}g;
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		char t;
		cin>>t;
		a[i]=t-'0';
	}
	for(int i=1;i<=n;i++){
		char t;
		cin>>t;
		b[i]=t-'0';
	}
	for(int i=1;i<=n;i++){
		if(a[i]==b[i]){
			z[i]=-1;
		}else if(a[i]>b[i]){
			z[i]=0;
		}else{
			z[i]=1;
		}
	}
	nxt[n+1]=n+1;
	for(int i=n;i>=1;i--){
		nxt[i]=i;
		if(z[i]==-1){
			nxt[i]=nxt[i+1];
		}
	}
	for(int i=1;i<=n;i++){
		pre[i]=i;
		if(z[i]==-1){
			pre[i]=pre[i-1];
		}
	}
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	for(int i=1;i<=m;i++){
		cin>>q[i].l>>q[i].r;
	}
	sort(q+1,q+1+m,cmp);
	for(int i=1;i<=m;i++){
		add(q[i].l,q[i].r);
	}
	for(int i=1;i<=n;i++){
		if(z[i]!=-1){
			if(g.q(i)^z[i]){
				if(xxj[i])
				g.sp(i,xxj[i]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(g.q(i)){
			swap(a[i],b[i]);
		}
	}
	for(int i=1;i<=n;i++){
		cout<<a[i];
	}
	return 0;
}
```

---

## 作者：eastcloud (赞：2)

思考过程写的有点长，但是做法是很好懂的。

字典序最大启发我们从大到小尝试钦定每一位是 1，然后判定其可行性，但是判定这部分好像很不好做。

我们先考虑有特殊性质的第二个 sub，这时候尝试从高到低贪心，你会发现我们的选择是唯一固定的，因为扫到每个节点的时候只可能最多有一种方式改变它的状态。

如何一般化？$a_i \neq b_i$ 直接忽略不满足的点即可，再考虑所有左端点相同的区间的选择的影响，对于一个 $i$，假设其所有作为左端点的区间的右端点是 $r_k$（为了方便，这时的区间是左闭右开的，也就是实际上右端点是 $r_k-1$），这些端点分割出的区间集合的任意一个子集都能被表示。

所以其实你可以把这些区间等价转换成 $[l,r_1],[r_1,r_2],[r_2,r_3] \cdots$（注意还是左闭右开），然后只考虑 $[l,r_1]$，剩下的递归到后面处理。

注意到这样最后会剩下若干个左端点不同的区间，按 sub2 的方法做即可，但是这样消是平方的，不太妙（好像有不是平方的的证明，但我不是很会）。

考虑消区间的过程带来了什么性质，即如果你有 $[l,r_1]$ 和 $[l,r_2]$，那 $[r_1,r_2]$ 你也有。

这好像很能图论建模，考虑对每个 $(l,r)$ 连边，可以得到对于一个 $l$ 它最后消出来的右端点就是同一个联通快编号比它大的最小编号。

至此你只要并查集维护一下联通块并对每个点查一个后继即可，复杂度瓶颈是并查集，我赛时嫌麻烦写了两个 log 的 set 启发式合并，所以代码看个乐就好。


```cpp
char a[N],b[N];
set<int> s,t[N];

int f[N],siz[N];

int find(int x){return (x==f[x]?x:f[x]=find(f[x]));}
void merge(int x,int y){
    x=find(x);y=find(y);if(x==y)return;
    if(siz[x]>siz[y])swap(x,y);
    siz[y]+=siz[x];f[x]=y;
    for(auto v:t[x])t[y].insert(v);
}

int c[N];

int main(){
    #ifdef EAST_CLOUD
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    #endif
    int n=read(),m=read();
    scanf("%s",a+1);scanf("%s",b+1);
    for(int i=1;i<=n;i++){
        if(a[i]!=b[i])s.insert(i);
    }
    if(!s.size()){
        cout<<(a+1);return 0;
    }
    for(int i=1;i<=n+1;i++)f[i]=i,siz[i]=1,t[i].insert(i);
    for(int i=1;i<=m;i++){
        int l=read(),r=read();
        if(l>(*s.rbegin()))continue;
        l=*(s.lower_bound(l));
        if(l>r)continue;
        auto it=s.upper_bound(r);
        if(it==s.end())r=n+1;
        else r=(*it);
        if(l>=r)continue;
        merge(l,r);
    }
    for(int i=1;i<=n;i++){
        c[i]^=c[i-1];
        if(a[i]==b[i]){putchar(a[i]);continue;}
        int now=(a[i]-'0')^(c[i]);
        if(now==1){putchar('1');continue;}
        int rt=find(i);
        auto it=t[rt].upper_bound(i);
        if(it==t[rt].end()){putchar('0');continue;}
        int r=(*it);
        c[i]^=1;c[r]^=1;
        putchar('1');
    }
    return 0;
}
```

---

## 作者：larsr (赞：1)

让我讲一下我的唐氏做法。

对于 $a_i=b_i$ 的可以直接不考虑，删掉，在算完 $a_i\neq b_i$ 后，再把它算进方案即可。

注意到对于 $k$ 个区间 $[l_1,r_1],[l_2,r_2],\ldots,[l_k,r_k]$，如果 $l_1=l_2=\ldots=l_k$，$r_1<r_i(2\le i\le k)$，那么第 $2$ 个到第 $n$ 个区间就可以变成 $[r_1 + 1,r_i]$，并且不影响结果。

从前往后考虑，选择从当前端点开始的区间的最小右端点，再按照刚刚的方法分割这些区间即可，如果左端点需要交换，那么执行这个区间，否则不执行。

那么剩下的只用找最小值，再转移值给指定的端点，显然可以用左偏树，复杂度 $O(n\log n)$。

由于这个做法比较唐氏，所以码量比较大。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200010
#define M 1000010
#define PA pair<int,int>
using namespace std;
int n, m, a[N], b[N];
int pn, pm, pa[N], pb[N], r[N];
int nex[N], pre[N], id[N];
int en[N], sum[N];
PA k[N], pk[N];
int ch[M][2], siz[M], num[M], tot = 0;
int lowbit(int x)
{
	return x&-x;
}
void add(int x)
{
	while(x <= pn)
	{
		sum[x] ^= 1;
		x += lowbit(x);
	}
}
int query(int x)
{
	int ans = 0;
	while(x)
	{
		ans ^= sum[x];
		x -= lowbit(x);
	}
	return ans;
}
int merge(int x, int y)
{
	if(!x || !y)return x + y;
	if(num[x] > num[y])swap(x, y);
	ch[x][1] = merge(ch[x][1], y);
	if(siz[ch[x][1]] > siz[ch[x][0]])swap(ch[x][0], ch[x][1]);
	siz[x] = siz[ch[x][1]] + 1;
	return x;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		char c = getchar();
		while(c != '0' && c != '1')c = getchar();
		a[i] = c - '0';
	}
	for(int i = 1; i <= n; i++)
	{
		char c = getchar();
		while(c != '0' && c != '1')c = getchar();
		b[i] = c - '0';
	}
	for(int i = 1; i <= n; i++)
	{
		if(a[i] != b[i])
		{
			pn++;
			pre[i] = pn;
			pa[pn] = a[i];
			pb[pn] = b[i];
			id[pn] = i;
		}
		else pre[i] = pre[i - 1];
	}
	int pnn = pn;
	for(int i = n; i; i--)
	{
		if(a[i] != b[i])nex[i] = pnn, pnn--;
		else nex[i] = nex[i + 1];
	}
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &k[i].first, &k[i].second);
		k[i].first = nex[k[i].first];
		k[i].second = pre[k[i].second];
		if(k[i].first <= k[i].second && k[i].first && k[i].second) pk[++pm] = k[i];
	}
	sort(pk + 1, pk + 1 + pm);
	int now = 1;
	for(int i = 1; i <= pn; i++)
	{
		int rt = r[i];
		while(rt && num[rt] < i)rt = merge(ch[rt][0], ch[rt][1]);
		while(now <= pm && pk[now].first <= i)
		{
			if(pk[now].first == i)
			{
				tot++;
				num[tot] = pk[now].second;
				siz[tot] = 1;
				rt = merge(rt, tot);
			}
			now++;
		}
//		printf("%d %d %d\n", i, num[rt], a[id[i]]);
		if(rt && !(a[id[i]] ^ query(i)))
		{
			add(i);
			add(num[rt] + 1);
		}
		if(rt) r[num[rt] + 1] = merge(r[num[rt] + 1], rt);
	}
	now = 0;
	for(int i = 1; i <= n; i++)
	{
		if(a[i] != b[i])
		{
			now++;
			printf("%d", a[i] ^ query(now));
		}
		else printf("%d", a[i]);
	}
	return 0;
}
```

---

## 作者：luckydrawbox (赞：0)

[$\text{Link}$](https://www.luogu.com.cn/problem/P11146)

## 题意

题目本身已经够简洁了，故直接搬来。

给定长度为 $n$ 的 $01$ 串 $a,b$，给定 $2m$ 个正整数 $l_i,r_i$。对于 $i=1,2,\cdots,m$，**依次**执行以下操作：
- 选择是否执行第 $i$ 次操作。
    - 如果执行，则对于 $k=l_i,l_{i}+1,\cdots,r_i$，交换 $a_k,b_k$。

最大化 $a$ 的字典序并输出最终的结果。

## 分析

显然，$a,b$ 相同的位怎么操作都不变，可以直接丢掉。

剔除后每个操作相当于给 $a$ 的一个区间异或上 $1$，我们只要贪心地让高位取最大就行了。

考虑部分分的情况：所有的 $l_i$ 互不相同，显然每个操作对第 $l_i$ 位的影响是唯一的，根据 $a$ 贪心地选即可。

若存在 $l_i$ 相同，不妨考虑最简单的情况（有被异或到的用 $1$ 表示，否则用 $0$ 表示）：

```
11100
11111
```

这两个操作选或不选构成的 $4$ 种情况分别是：

```
00000
11100
00011
11111
```

和操作 `11100` 和 `00011` 构成的结果相同！也就是说我们把 `11111` 改成 `00011` 并不影响答案！根据归纳法，这个东西可以扩展到多个的情况，如 $4$ 个：

```
110000 <=> 110000
111000 <=> 001000
111110 <=> 000110
111111 <=> 000001
```
于是我们就能把 $l_i$ 相同的情况转化为 $l_i$ 不同的，若两个操作会变成完全一样则可以去掉一个。这道题就做完了。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch))
	{if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=2e5+10;
int n,m,tn,tm;
string sa,sb;
struct oper{
	int l,r;
}op[N];
int id[N],a[N],b[N];
int mu[N];
vector<int>adl[N];
bool cmp(int x,int y){
	return op[x].r<op[y].r;
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();m=read();
	cin>>sa>>sb;
	for(int i=1;i<=m;i++){
		op[i].l=read();op[i].r=read();
	}
	for(int i=1;i<=n;i++){
		if(sa[i-1]!=sb[i-1]){
			a[++tn]=sa[i-1]-'0';
			b[tn]=sb[i-1]-'0';
			id[tn]=i;
		}
	}
	for(int i=1;i<=m;i++){
		if(op[i].l>id[tn]||op[i].r<id[1])continue;
		op[i].l=lower_bound(id+1,id+tn+1,op[i].l)-id;
		op[i].r=upper_bound(id+1,id+tn+1,op[i].r)-id-1;
		if(1<=op[i].l&&op[i].l<=op[i].r&&op[i].r<=tn){
			adl[op[i].l].push_back(i);
		}
	}
	int now=0,lst=0;
	for(int i=1;i<=tn;i++){
		now^=mu[i];
		if(adl[i].size()){
			sort(adl[i].begin(),adl[i].end(),cmp);
			int x=adl[i][0];
			for(int j=1;j<adl[i].size();j++){
				if(op[adl[i][j]].r==op[adl[i][j-1]].r)continue;
				adl[op[adl[i][j-1]].r+1].push_back(adl[i][j]);
			}
			adl[i].clear();adl[i].push_back(x);
			if(!(now^a[i])){
				mu[op[x].r+1]^=1;
				now^=1;
			}
			sa[id[i]-1]='1';
		}
		else{
			if(now^a[i])sa[id[i]-1]='1';
			else sa[id[i]-1]='0';;
		}
	}
	cout<<sa<<endl;
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：0)

乱搞然后过了.jpg，完全不会证复杂度。

# Solution

将 $a_i=b_i$ 的位置全部删除，操作就变成了区间异或。

Sub2 的做法比较简单，从左往右扫，如果当前位是 0 就翻转。

接下来考虑有多个区间 $[l,r_1],[l,r_2],\cdots,[l,r_k]$ 左端点相同怎么处理。如果当前位是 1，就跳过。如果是 0，先随便选一个区间翻转，然后把 $[r_1+1,r_2],[r_2+1,r_3],\cdots,[r_{n-1}+1,r_n]$ 当作新的区间加入。

正确性就是如果当前选了 $[l,r_x]$，最优解选 $[l,r_y]$，后续选 $[r_x+1,r_y]$ 就可以变成最优解。复杂度不会证。

# Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	LL n, m, l, r, a[N], b[N], d[N], vs[N], R[N]; char x; vector<int> t, g[N];
	int main() {
		cin >> n >> m;
		REP(i, 1, n) cin >> x, a[i] = x - '0';
		REP(i, 1, n) {
			cin >> x, b[i] = x - '0';
			if (a[i] != b[i]) vs[i] = 1, t.pb(i);
		}
		REP(i, 1, m) {
			cin >> l >> r;
			auto x = lower_bound(ALL(t), l), y = upper_bound(ALL(t), r); 
			if (x < y) g[*x].pb(*prev(y));
		}
		REP(i, 1, n) {
			if (!g[i].size()) continue;
			sort(ALL(g[i])), R[i] = g[i][0];
			REP(j, 1, SZ(g[i]) - 1) {
				int x = g[i][j - 1], y = g[i][j];
				if (x < y) {
					auto z = upper_bound(ALL(t), x);
					if (z != t.end()) g[*z].pb(y);
				}
			}
		}
		REP(i, 1, n) {
			d[i] ^= d[i - 1];
			if (!vs[i]) continue;
			if (d[i] == a[i] && R[i] > 0) d[i] ^= 1, d[R[i] + 1] ^= 1;
		}
		REP(i, 1, n) cout << (vs[i] ? a[i] ^ d[i] : a[i]);
		cout << '\n';
		return 0;
	}
}
```

---

