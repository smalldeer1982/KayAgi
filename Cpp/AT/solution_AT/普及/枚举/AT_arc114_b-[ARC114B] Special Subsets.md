# [ARC114B] Special Subsets

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc114/tasks/arc114_b

$ 1 $ 以上 $ N $ 以下の整数すべてから成る集合を $ S $ とします．

$ f $ は $ S $ から $ S $ への関数であり，$ f(1),\ f(2),\ \cdots,\ f(N) $ の値が $ f_1,\ f_2,\ \cdots,\ f_N $ として与えられます．

$ S $ の空でない部分集合 $ T $ であって，次の両方の条件を満たすものの個数を $ 998244353 $ で割った余りを求めてください．

- 全ての $ a\ \in\ T $ について $ f(a)\ \in\ T $ である．
- 全ての $ a,\ b\ \in\ T $ について $ a\ \neq\ b $ ならば $ f(a)\ \neq\ f(b) $ である．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ f_i\ \leq\ N $
- 入力は全て整数

### Sample Explanation 1

$ f(1)\ =\ 2,\ f(2)\ =\ 1 $ です．$ f(1)\ \neq\ f(2) $ であるため条件の $ 2 $ つ目は常に満たしますが，$ 1 $ つ目の条件より $ 1,\ 2 $ は同時に $ T $ に入っている必要があります．

### Sample Explanation 2

$ f(1)\ =\ f(2)\ =\ 1 $ です．$ 1 $ つ目の条件のため $ 1 $ は $ T $ に属する必要があり，さらに $ 2 $ つ目の条件により $ 2 $ は $ T $ に属することはできません．

### Sample Explanation 3

$ f(1)\ =\ 1,\ f(2)\ =\ 2,\ f(3)\ =\ 3 $ です．$ 1 $ つ目の条件も $ 2 $ つ目の条件も常に満たされるため，$ S $ の空でない部分集合全てが条件を満たします．

## 样例 #1

### 输入

```
2
2 1```

### 输出

```
1```

## 样例 #2

### 输入

```
2
1 1```

### 输出

```
1```

## 样例 #3

### 输入

```
3
1 2 3```

### 输出

```
7```

# 题解

## 作者：Unnamed114514 (赞：2)

假设我们选的子集为 $T={a_1,a_2,\cdots,a_p}$。

我们来考虑一下这个 $T$ 是如何得到的：

首先，我们选定了 $1$ 个 $a_1$，为了保证性质 $1$，那么我们就将 $f_{a_1}$ 加入 $T$，为了方便，我们记作 $a_2$。

引理：若 $a_q$ 在 $T$ 中，那么 $a_{q+1}=f_{a_q}(a_{p+1}=a_1)$。

使用数学归纳法：上面已经证明了 $a_2=f_{a_1}$，即有 $a_{k+1}=f_{a_k}$，须证 $a_{k+2}=f_{a_{k+1}}$。

使用反证法：若 $a_{k+2}\ne f_{a_{k+1}}$，那么则有 $a_w=f_{a_{k+1}}(w<k+1)$，但是此时因为 $\forall i\in[1,k]$ 满足 $a_{i+1}=f_{a_i}$，所以 $a_w=f_{a_{w-1}}$ 那么此时的 $a_w$ 对应 $2$ 个值，与性质 $2$ 矛盾，所以 $a_{k+2}=f_{a_{k+1}}$。

综上，原命题成立。

那么此时我们会发现这个序列构成了一个环，也就是说，在 $i$ 和 $f_i$ 之间建边，那么每个满足的集合都有一个环。

注意到这个环可能有“尾巴”，假设伸出去的节点为 $x$，那么若取了“尾巴”，$a_x$ 就对应了 $2$ 个 $f$ 值，与性质 $2$ 矛盾，所以“尾巴”一定不取。

因为 $1$ 条边只属于 $1$ 个环，而一个 $i$ 唯一对应 $f_i$。所以没有点会属于 $2$ 个环，不存在环与环之间嵌套的情况。所以一个连通块内部只会有 $1$ 个环，所以数环的数量就转化为了数连通块的数量。

设连通块共计 $t$ 个，每个连通块可取可不取，但是至少取一个，所以减去都不取的 $1$ 种情况，答案就是 $2^t-1$。

时空复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353,maxn=2e5+5;
int n,ans,f[maxn];
vector<int> G[maxn];
bool vis[maxn];
void dfs(int u){
	if(vis[u])
		return;
	vis[u]=1;
	for(auto v:G[u])
		dfs(v);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&f[i]);
		G[i].push_back(f[i]);
		G[f[i]].push_back(i);
	}
	for(int i=1;i<=n;++i)
		if(!vis[i]){
			++ans;
			dfs(i);
		}
	int p=1;
	for(int i=1;i<=ans;++i)
		p=p*2%mod;
	printf("%d\n",(p+mod-1)%mod);
	return 0;
}
```

---

## 作者：_Trangle_ (赞：0)

将 $i$ 向 $f_i$ 连边，发现每个点只有一条出边，意味着该图是一个内向基环树森林。

这时候子集可以转化为导出子图。由于一个点所指向的点要被加入，所以第一个要求转化为所有该结点能到达的结点都要加入；而不能有 $f_a\neq f_b$，相当于不能有子图内不能有两个结点指向同一个点。

由于在基环树上只有环满足这两个条件，所以一棵基环树的子图只有一个子图符合条件。于是求子集数相当于选中非零个基环树的方案数。

先统计统计基环树的数量，也就是连通块的数量，设有 $cnt$ 个基环树，所以方案数为 $2^{cnt}-1$ 种方案。

维护连通块使用并查集。
```
#include <bits/stdc++.h>
#define rep(i, b, e) for (auto i(b); i <= (e); i++)
#define req(i, b, e) for (auto i(b); i >= (e); i--)
#define range(i, b, e) for (auto i(b); i != (e); i++)
using namespace std;

const int N = 2e5, mod = 998244353;
int n, pw = 1;
int fa[N+5];
bool flag[N+5];

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cin >> n;
	iota(fa+1, fa + n+1, 1);

	for (int i = 1, to; i <= n; i++) {
		cin >> to;
		int x = find(i), y = find(to);
		if (x != y) fa[x] = y;
	}

	rep(i, 1, n) if (not flag[find(i)]) {
		flag[find(i)] = true;
		pw = (pw<<1) % mod;
	}
	cout << (pw + mod-1) % mod;
	return 0;
}
```

---

## 作者：ljlawa (赞：0)

这是一道数连通块个数的题。

关于条件一，我们得知 $a$ 和 $f(a)$ 必须在一起出现。而 $f(a)$ 必然会和 $f(f(a))$ 一起出现。以此类推。

而条件二告诉我们每个点的入度不能超过1。

综上，这些数字就会形成很多个环。所以这道题转化为了数环数。而环上的每一条边都是和环对应的。所以数环可以转化为数连通块的个数。

然后对于每一个连通块，我们可取可不取。因为不能为空，所以答案就是 $2^{cnt} - 1$。

~~(赛时有笨蛋写了快速幂。)~~

code:

```cpp
#include <bits/stdc++.h>

using namespace std;

const int p = 998244353;
const int N = 2e5 + 5;

int n, x[N];
int tot, ans = 1;
int h[N], ne[N << 1], to[N << 1], cnt;
void add (int u, int v)
{
	to[++ cnt] = v;
	ne[cnt] = h[u];
	h[u] = cnt;
}
bool vis[N];

void dfs (int u)
{
	vis[u] = 1;
	for (int i = h[u]; i; i = ne[i])
	{
		int j = to[i];
		if (vis[j] == 0) dfs (j);
		vis[j] = 1;
	}
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i ++)
	{
		cin >> x[i];
		add (i, x[i]);
		add (x[i], i);
	}
	for (int i = 1; i <= n; i ++)
		if (vis[i] == 0) tot ++, dfs (i);
	for (int i = 1; i <= tot; i ++)
		ans = 2ll * ans % p;
	cout << ans - 1;
	return 0;
}
```


---

