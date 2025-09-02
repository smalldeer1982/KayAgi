# Bearish Fanpages

## 题目描述

There is a social website with $ n $ fanpages, numbered $ 1 $ through $ n $ . There are also $ n $ companies, and the $ i $ -th company owns the $ i $ -th fanpage.

Recently, the website created a feature called following. Each fanpage must choose exactly one other fanpage to follow.

The website doesn’t allow a situation where $ i $ follows $ j $ and at the same time $ j $ follows $ i $ . Also, a fanpage can't follow itself.

Let’s say that fanpage $ i $ follows some other fanpage $ j_{0} $ . Also, let’s say that $ i $ is followed by $ k $ other fanpages $ j_{1},j_{2},...,j_{k} $ . Then, when people visit fanpage $ i $ they see ads from $ k+2 $ distinct companies: $ i,j_{0},j_{1},...,j_{k} $ . Exactly $ t_{i} $ people subscribe (like) the $ i $ -th fanpage, and each of them will click exactly one add. For each of $ k+1 $ companies $ j_{0},j_{1},...,j_{k} $ , exactly ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643D/21bba61653cf179f89248142af248d7df7419d53.png) people will click their ad. Remaining ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643D/41e88e0191cf8cbf46af6c24ce4f538a6481272e.png) people will click an ad from company $ i $ (the owner of the fanpage).

The total income of the company is equal to the number of people who click ads from this copmany.

Limak and Radewoosh ask you for help. Initially, fanpage $ i $ follows fanpage $ f_{i} $ . Your task is to handle $ q $ queries of three types:

- 1 i j — fanpage $ i $ follows fanpage $ j $ from now. It's guaranteed that $ i $ didn't follow $ j $ just before the query. Note an extra constraint for the number of queries of this type (below, in the Input section).
- 2 i — print the total income of the $ i $ -th company.
- 3 — print two integers: the smallest income of one company and the biggest income of one company.

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643D/d9db9bc44e733c82215e5751c44c438174d7820a.png)In the sample test, there are $ 5 $ fanpages. The $ i $ -th of them has $ i·10 $ subscribers.

On drawings, numbers of subscribers are written in circles. An arrow from $ A $ to $ B $ means that $ A $ follows $ B $ .

The left drawing shows the initial situation. The first company gets income ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643D/66341a4c63fe8dcbff87b6d1efb8920e9cbb8631.png) from its own fanpage, and gets income ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643D/e1ae5946de33df9032cda69753ae955ed119e264.png) from the $ 2 $ -nd fanpage. So, the total income is $ 5+5=10 $ . After the first query ("2 1") you should print $ 10 $ .

The right drawing shows the situation after a query "1 4 2" (after which fanpage $ 4 $ follows fanpage $ 2 $ ). Then, the first company still gets income $ 5 $ from its own fanpage, but now it gets only ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643D/2ec2bf132e45182de4904da17cfe1690c0fccba6.png) from the $ 2 $ -nd fanpage. So, the total income is $ 5+4=9 $ now.

## 样例 #1

### 输入

```
5 12
10 20 30 40 50
2 3 4 5 2
2 1
2 2
2 3
2 4
2 5
1 4 2
2 1
2 2
2 3
2 4
2 5
3
```

### 输出

```
10
36
28
40
36
9
57
27
28
29
9 57
```

# 题解

## 作者：xht (赞：4)

> [CF643D Bearish Fanpages](https://codeforces.com/contest/643/problem/D)

## 题意

- 给定一个 $n$ 个点的基环森林，第 $i$ 个点与 $f_i$ 之间有一条边。
- 保证在任意时刻，这个基环森林中的环长至少为 $3$。
- 当一种「神秘事件」发生时，对于第 $i$ 个点，设与其相邻的点（包括 $f_i$ 和 $f_j = i$ 的 $j$）的个数为 $k$，这 $k$ 个点上都会出现 $\lfloor \frac{t_i}{k+1} \rfloor$ 个人，而 $i$ 上会出现 $t_i - k \cdot \lfloor \frac{t_i}{k+1} \rfloor$ 个人。
- 每次「神秘事件」发生都是互不影响的。
- 有 $q$ 个操作，操作有三种。
  1. `1 i j`：将 $f_i$ 改为 $j$，此操作不超过 $5 \times 10^4$ 个。
  2. `2 i`：询问当「神秘事件」发生时，第 $i$ 个点上出现的人数。
  3. `3`：询问当「神秘事件」发生时，所有点上出现的人数的最小值和最大值。
- $n,q \le 10^5$，$t_i \le 10^{12}$。

## 题解

对于点 $i$，将 $f_j = i$ 的所有 $j$ 的权值去掉 $i$ 的贡献后存到 $i$ 上的一个 `multiset` 里（记为 $s_i$），然后 `multiset` 里的最大最小值加上 $i$ 的贡献存到一个大 `multiset` 里（记为 $s_0$）。

设 $a_i$ 表示 $i$ 去掉 $f_i$ 的贡献后的权值，$d_i$ 表示 $i$ 的度数。

考虑每次修改，即将 $f_i$ 改为 $j$ 的过程：

- 由于修改后 $i$ 不再对 $f_i$ 有贡献，$a_{f_i}$ 要减去修改前来自 $i$ 的贡献 $\lfloor \frac{t_i}{d_i+1} \rfloor$，$s_{f_i}$ 中删除 $a_i$。
- 由于 $d_{f_i}$ 修改后要减去 $1$，$a_{f_i}$ 要减去修改前自身的贡献 $t_{f_i} - d_{f_i} \cdot \lfloor \frac{t_{f_i}}{d_{f_i}+1}\rfloor$，加上修改后自身的贡献 $t_{f_i} - (d_{f_i}-1) \cdot \lfloor \frac{t_{f_i}}{d_{f_i}}\rfloor$，$s_{f_{f_i}}$ 要更新 $a_{f_i}$。
- 由于 $d_{f_i}$ 修改后要减去 $1$，$a_{f_{f_i}}$ 要减去修改前来自 $f_i$ 的贡献 $\lfloor \frac{t_{f_i}}{d_{f_i}+1} \rfloor$，加上修改后来自 $f_i$ 的贡献 $\lfloor \frac{t_{f_i}}{d_{f_i}} \rfloor$，$s_{f_{f_{f_i}}}$ 要更新 $a_{f_{f_i}}$。

此时执行修改，即 $d_{f_i}$ 减去 $1$，$f_i$ 改为 $j$，$d_j$ 加上 $1$，然后将上面的过程反向重复一遍。

- 由于修改前 $i$ 对 $j$ 没有贡献，$a_{j}$ 要加上修改后来自 $i$ 的贡献 $\lfloor \frac{t_i}{d_i+1} \rfloor$，$s_{j}$ 中插入 $a_i$。
- 由于 $d_{j}$ 修改后加上了 $1$，$a_{j}$ 要减去修改前自身的贡献 $t_{j} - (d_{j}-1) \cdot \lfloor \frac{t_{j}}{d_{j}}\rfloor$，加上修改后自身的贡献 $t_{j} - d_{j} \cdot \lfloor \frac{t_{j}}{d_{j}+1}\rfloor$，$s_{f_{j}}$ 要更新 $a_{j}$。
- 由于 $d_{j}$ 修改后加上了 $1$，$a_{f_{j}}$ 要减去修改前来自 $j$ 的贡献 $\lfloor \frac{t_{j}}{d_{j}} \rfloor$，加上修改后来自 $j$ 的贡献 $\lfloor \frac{t_{j}}{d_{j}+1} \rfloor$，$s_{f_{f_{j}}}$ 要更新 $a_{f_{j}}$。

注意每次更新 $s_i$ 的操作实质上是先删除再修改后插入，必须保证删除在修改之前，因此**不能**完全按照上面的顺序来做。

另外，别忘了每次更新 $s_i$ 还要同步更新 $s_0$，同时注意不能重复插入或删除。

所以实际上本题是个模拟题，总时间复杂度 $\mathcal O((n+q) \log n)$。

## 代码

```cpp
const int N = 1e5 + 7;
int n, q, d[N], f[N];
bool v[N];
ll a[N], t[N];
multiset<ll> s[N];

inline void del(int x) {
	if (v[x] && s[x].size())
		v[x] = 0,
		s[0].erase(s[0].find((*s[x].begin()) + t[x] / (d[x] + 1))),
		s[0].erase(s[0].find((*(--s[x].end())) + t[x] / (d[x] + 1)));
}

inline void add(int x) {
	if (!v[x] && s[x].size())
		v[x] = 1,
		s[0].insert((*s[x].begin()) + t[x] / (d[x] + 1)),
		s[0].insert((*(--s[x].end())) + t[x] / (d[x] + 1));
}

inline void work(int i, int j) {
	del(f[i]), del(f[f[i]]), del(f[f[f[i]]]);
	del(j), del(f[j]), del(f[f[j]]);

	s[f[i]].erase(s[f[i]].find(a[i]));

	s[f[f[i]]].erase(s[f[f[i]]].find(a[f[i]]));
	a[f[i]] -= t[i] / (d[i] + 1);
	a[f[i]] -= t[f[i]] - d[f[i]] * (t[f[i]] / (d[f[i]] + 1));
	a[f[i]] += t[f[i]] - (d[f[i]] - 1) * (t[f[i]] / d[f[i]]);
	s[f[f[i]]].insert(a[f[i]]);

	s[f[f[f[i]]]].erase(s[f[f[f[i]]]].find(a[f[f[i]]]));
	a[f[f[i]]] -= t[f[i]] / (d[f[i]] + 1);
	a[f[f[i]]] += t[f[i]] / d[f[i]];
	s[f[f[f[i]]]].insert(a[f[f[i]]]);

	--d[f[i]], ++d[j];

	s[j].insert(a[i]);

	s[f[j]].erase(s[f[j]].find(a[j]));
	a[j] += t[i] / (d[i] + 1);
	a[j] -= t[j] - (d[j] - 1) * (t[j] / d[j]);
	a[j] += t[j] - d[j] * (t[j] / (d[j] + 1));
	s[f[j]].insert(a[j]);

	s[f[f[j]]].erase(s[f[f[j]]].find(a[f[j]]));
	a[f[j]] -= t[j] / d[j];
	a[f[j]] += t[j] / (d[j] + 1);
	s[f[f[j]]].insert(a[f[j]]);

	add(f[i]), add(f[f[i]]), add(f[f[f[i]]]);
	add(j), add(f[j]), add(f[f[j]]);

	f[i] = j;
}

int main() {
	rd(n), rd(q), rda(t, n), rda(f, n);
	for (int i = 1; i <= n; i++) ++d[i], ++d[f[i]];
	for (int i = 1; i <= n; i++)
		a[i] += t[i] - d[i] * (t[i] / (d[i] + 1)),
		a[f[i]] += t[i] / (d[i] + 1);
	for (int i = 1; i <= n; i++) s[f[i]].insert(a[i]);
	for (int i = 1; i <= n; i++) add(i);
	while (q--) {
		int o, i, j;
		rd(o);
		switch (o) {
			case 1 : rd(i), rd(j), work(i, j); break;
			case 2 : rd(i), print(a[i] + t[f[i]] / (d[f[i]] + 1)); break;
			case 3 : print(*s[0].begin(), ' '), print(*(--s[0].end())); break;
		}
	}
	return 0;
}
```



---

## 作者：关怀他人 (赞：2)

### CF 643D
#### Solution
对每个节点 $u$ ，考虑将父亲对$u$和$u$的儿子对它的贡献分开计算，用一个 $\text{multiset}$ 维护其儿子节点，再记录其儿子节点数量 $num_u$ 和该节点所有儿子对它的贡献之和 $sum_u$ ，那么一个节点的总人数为 $sum_u+(f_u\text{对} u \text{的贡献})$。

由于每个点人数的最值必然是某个节点的儿子达到的，所以开一个 $\text{multiset} \ S$ 维护**每个节点的儿子节点最值加上自身对儿子的贡献**，即为儿子的总人数。

对于 $1$ 操作，假设 $u$ 的父亲由 $f_u$ 变成 $v$，那么 $sum$ 改变的只有 $u,f_u,f_{f_u},v,f_v$ 这些节点，对应的要把其父亲节点中儿子节点最值从 $S$ 中删掉，修改对应的 $sum$ 后再把这些点的父亲节点的儿子节点最值插入到 $S$ 中完成修改即可.

对于 $2$ 操作，只需要输出 $sum_u+(f_u\text{对} u \text{的贡献})$ 即可。

对于 $3$ 操作，从 $S$ 中选出最大和最小值即可。

时间复杂度 $\mathcal O(n\log n)$
#### Code
```cpp
int n,Q;
int f[MAXN],num[MAXN];
ll t[MAXN],sum[MAXN];
multiset<ll> s[MAXN], S;

ll calcself(int i) {return t[i] - (t[i] / (num[i] + 2)) * (num[i] + 1);}
ll calcson(int i) {return t[i] / (num[i] + 2);}
void addmax(int i){
	if(s[i].empty()) return;
	S.insert(*(--s[i].end()) + calcson(i));
}
void addmin(int i){
	if(s[i].empty()) return;
	S.insert(*s[i].begin() + calcson(i));
}
void delmax(int i){
	if(s[i].empty()) return;
	S.erase(S.find(*(--s[i].end()) + calcson(i)));
}
void delmin(int i){
	if(s[i].empty()) return;
	S.erase(S.find(*s[i].begin() + calcson(i)));
}

void solve(int x,int y){
    set<int> tmp = {x,f[x],f[f[x]],y,f[y]}, need,fneed;
    for(int i : tmp) if(i) need.insert(i); fneed = need;
    for(int i : need) if(f[i]) fneed.insert(f[i]);
    for(int i : fneed) delmax(i), delmin(i);
    for(int i : need) s[f[i]].erase(s[f[i]].find(sum[i]));
    for(int i : need){
        sum[i] -= calcself(i);
        for(int j : need) if(f[j] == i) sum[i] -= calcson(j);
    }
    num[f[x]] -= 1; f[x] = y; num[y] += 1;
    for(int i : need){
        sum[i] += calcself(i);
        for(int j : need) if(f[j] == i) sum[i] += calcson(j);
    }
    for(int i : need) s[f[i]].insert(sum[i]);
    for(int i : fneed) addmax(i), addmin(i);
}

int main(){
    scanf("%d%d",&n,&Q);
    for(int i = 1;i <= n;i++) scanf("%lld",&t[i]);
    for(int i = 1;i <= n;i++) scanf("%d",&f[i]), num[f[i]] += 1;
    for(int i = 1;i <= n;i++) sum[i] += calcself(i), sum[f[i]] += calcson(i);
    for(int i = 1;i <= n;i++) s[f[i]].insert(sum[i]);
    for(int i = 1;i <= n;i++) addmax(i), addmin(i);
    while(Q--){
        int op,x,y; scanf("%d",&op);
        if(op == 1) scanf("%d%d",&x,&y), solve(x,y);
        else if(op == 2) scanf("%d",&x), printf("%lld\n",sum[x] + calcson(f[x]));
        else if(op == 3) printf("%lld %lld\n",*S.begin(),*(--S.end()));
    }
    return 0;
}
```

---

## 作者：Diwanul (赞：0)

# 题意

## 原意简述版

有 $n$ 个公司，每个公司在某社交媒体拥有一个粉丝专页。该社交媒体推出了“关注”功能，每个粉丝专页必须“关注”一个粉丝专页，保证不会有自己关注自己和互关的事情出现。第 $i$ 个公司的粉丝专页有 $v_i$ 位订阅者。每个粉丝专页上都有一些广告，分别来自：

-   该粉丝专页的所有者公司
-   该粉丝专页“关注”的粉丝专页的所有者公司
-   “关注”该粉丝专页的粉丝专页的所有者公司

当第 $i$ 个公司的粉丝专页上有 $k$ 条广告时，每条广告都会被点击 $\left\lfloor\dfrac {v_i}k\right\rfloor$ 次。每位订阅者会点一条广告，所以多余的还没有点广告的订阅者就会全部点该粉丝专页的所有者公司的广告。每一位订阅者的点击会为广告的所有者公司带来 $1$ 的收益。现在要求你能进行以下三个操作：

1.   `1 x y` 让第 $x$ 个公司的粉丝专页改为“关注”第 $y$ 个公司的粉丝专页。
2.   `2 x` 查询假如每位订阅者按照上述规则进行一次点击，第 $x$ 个公司的收益。
3.   `3` 查询假如每位订阅者按照上述规则进行一次点击，收益最低的公司的收益和收益最高的公司的收益。

## 压缩版

$n$ 个带权点，每个点有一条出边。不会出现自环和互为出边指向点。要查询的值被称为收益。设和点 $u$ 直接有边相连（与边的方向无关）的点数为 $k_u$，点 $u$ 的权值为 $v_u$。则每一个和 $u$ 直接有边相连的点收益增加 $\left\lfloor\dfrac {v_u}{k_u+1}\right\rfloor$，对自己贡献 $v_u-k_u\times\left\lfloor\dfrac {v_u}{k_u+1}\right\rfloor$。注意每个点只会在每个独立询问时对周围的点有收益贡献，收益不会保留到下次询问继续累加，而是会清空。三种操作：

1.   `1 x y` 修改点 $x$ 的出边指向点为 $y$。
2.   `2 x` 查询点 $x$ 的收益。
3.   `3` 查询所有点中的最小收益和最大收益。

# 思路

暴力怎么做？修改时暴力修改对周围所有点的贡献，查询时直接输出或枚举所有点求最值。修改最劣 $O(n)$。

仔细考虑，发现这个 $O(n)$ 来自于该点连接的边数，而边数是 $O(n)$ 级别的。也就是说，随机下均摊是 $O(1)$ 级别的。那我们有没有方法可以平衡复杂度呢？

要做到严格 $O(1)$，可以想到要强制某点修改时只对相连的边中 $O(1)$ 条边进行操作，其他的部分在查询时另行 $O(1)$ 查询。

这时我们就发现每个点只有一条出边，看作基环树就可以理解为每个点只有一个父亲。那么我们就强制他只处理对其父亲的贡献，而对儿子的贡献等查询儿子时再计算。这样一来，每个点只有一个父亲则修改父亲 $O(1)$，查询时也只需要加上父亲的贡献。这下就 $O(n)$ 解决前两个操作了。（很多大佬能一眼看出这是个经典 trick：所有相连点都会造成贡献时，儿子的贡献和父亲的贡献分开计算。）

如何处理 `3` 操作？暴力开 `set` 维护或者暴力扫维护都不可行，怎么办？回到上面的思路，我们只计算儿子对自己的贡献可以做到 $O(1)$ 修改。可是我们不能只看儿子贡献啊？每个点的父亲贡献不同，所以不能单纯用儿子贡献做关键字存 `set`。考虑到一个点的所有儿子的父亲贡献相等，则自然而然想到将该点的儿子们的信息维护在该点的 `set` 中。那么我们只需把该点的 `set` 的最大最小取出，加上该点对儿子的贡献丢进全局 `set`，就能做到 $O(q\log n)$ 了。常数较大。

# 实现

注意到 $n$ 比较小，时间充裕，我们以防万一，也为了代码简洁，维护最大最小值时，可以先把有关点的 `set` 中放入全局 `set` 中的元素删除，修改了该点的 `set` 后再取最大最小值放入全局 `set` 中。善于使用函数的话，可以写的比较简洁。

core code:

```cpp
int n,m;
LL v[N+10],ic[N+10];					//value and income 权值与来自儿子的收益
int fa[N+10],sc[N+10];					//父亲与儿子数
multiset<LL> ch[N+10],mm;				//每个点的儿子 set 与全局 set

inline void Addm(int u){				//将点 u 的 set 取最大最小值加上 u 对其贡献放入全局 set 中
	if(sc[u]){
		mm.insert(*ch[u].begin()+v[u]/(sc[u]+2));
		if(sc[u]>1)
			mm.insert(*--ch[u].end()+v[u]/(sc[u]+2));
	}
}
 
inline void Delm(int u){				//同上函数，但是是删除
	if(sc[u]){
		mm.erase(mm.find(*ch[u].begin()+v[u]/(sc[u]+2)));
		if(sc[u]>1)
			mm.erase(mm.find(*--ch[u].end()+v[u]/(sc[u]+2)));
	}
}

inline void Change(int u,LL x){			//修改一个点的来自儿子的收益
	int f=fa[u];
	Delm(f);
	ch[f].erase(ch[f].find(ic[u]));
	ic[u]+=x;
	ch[f].insert(ic[u]);
	Addm(f);
}
 
inline void Del(int u){					//断开 u 到父亲的边
	int f=fa[u];
	Delm(f);				
	ch[f].erase(ch[f].find(ic[u]));
	Change(fa[f],v[f]/(sc[f]+1)-v[f]/(sc[f]+2));
	Change(f,(sc[f]+1)*(v[f]/(sc[f]+2))-sc[f]*(v[f]/(sc[f]+1))-v[u]/(sc[u]+2));
	--sc[f];
	fa[u]=0;
	Addm(f);
}
 
inline void Link(int u,int f){			//连接 u 到 f 的边，内容与上函数类似，相反而已
	Delm(f);
	fa[u]=f;
	++sc[f];
	Change(f,v[u]/(sc[u]+2)-(sc[f]+1)*(v[f]/(sc[f]+2))+sc[f]*(v[f]/(sc[f]+1)));
	Change(fa[f],v[f]/(sc[f]+2)-v[f]/(sc[f]+1));
	ch[f].insert(ic[u]);
	Addm(f);
}

int main(){
	n=Read(),m=Read();
	for(int i=1;i<=n;++i)
		v[i]=Read();
	for(int i=1;i<=n;++i)
		++sc[fa[i]=Read()];
	for(int i=1;i<=n;++i)
		ic[fa[i]]+=v[i]/(sc[i]+2),ic[i]+=v[i]-(sc[i]+1)*(v[i]/(sc[i]+2));
	for(int i=1;i<=n;++i)
		ch[fa[i]].insert(ic[i]);
	for(int i=1;i<=n;++i)
		Addm(i);
	++m;
	while(--m){
		int op=Read();
		if(op==1){
			int x=Read(),y=Read();
			Del(x);
			Link(x,y);
		}
		else if(op==2){
			int x=Read();
			printf("%lld\n",ic[x]+v[fa[x]]/(sc[fa[x]]+2));
		}
		else
			printf("%lld %lld\n",*mm.begin(),*--mm.end());
	}
	return 0;
}
```



---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
给定一个 $n$ 个点的基环内向树森林，即给定每个点 $i$ 的后继 $f_i$。  
（**特别地，保证在任意时刻，这个基环内向森林中的环长都** $\boldsymbol{\ge 3}$）

在这个限制下，考虑与某个点 $i$ 距离不超过 $1$ 的点，也就是 $i$ 本身，$i$ 的后继 $f_i$ 以及若干个后继为 $i$ 的点。  
不妨假设有 $k$ 个点的后继为 $i$，则我们需要考虑这 $k + 2$ 个点（这是因为环长 $\ge 3$，不会出现重复的点）。  
称这 $k + 2$ 个点分别为 $i, j_0, j_1, j_2, \ldots , j_k$（$j_0$ 为 $i$ 的后继，$j_{1 \ldots k}$ 为后继为 $i$ 的那 $k$ 个点）。

现在假设**神秘事件**发生了，每个点都会进入一些人，第 $i$ 个点会进入 $t_i$ 个人。  
恰好 $\left\lfloor \frac{t_i}{k+2} \right\rfloor$ 个人会进入 $j_0, j_1, j_2, \ldots , j_k$ 号点（每个点都进入 $\left\lfloor \frac{t_i}{k+2} \right\rfloor$ 个人），剩下的 $t_i - (k + 1) \cdot \!\left\lfloor \frac{t_i}{k+2} \right\rfloor$ 个人会留在点 $i$。

你需要依次处理 $q$ 个操作：

`1 i j`：将 $f_i$ 改为 $j$，即把 $i$ 的后继变成 $j$。保证仍然满足上文中的条件。
`2 i`：计算当**神秘事件**发生时，第 $i$ 个点最终会留下多少人。
`3`：计算当**神秘事件**发生时，每个点内最终留下的人数的最小值和最大值。

注意：每次**神秘事件**发生都是互不影响的。

## $\text{Solution}$
阴间大模拟题。  
容易想到，问题可以转化成对亿些集合的集体修改和亿些单点的修改。  
全局 $\min,\max$ 开两个 `set` 维护即可。  
集体修改考虑懒标记，我用的是线段树维护，对于每个点开一棵以它为父亲的线段树，动态开点插入删除修改瞎做即可。  

## $\text{Code}$
~~有的地方为了可读性忽略了代码效率，自带 $24$ 倍常数，成功斩获最劣解~~  
~~极其屎山，不过看几篇题解似乎都差不多...~~
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=1e5+100;
#define ll long long
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m,tim;
ll t[N],w[N],v[N];
int du[N],fa[N];
multiset<ll>mn,mx;

#define mid ((l+r)>>1)
struct tree{
  int ls,rs;
  ll mn,mx,laz;
}tr[N<<6];
int rt[N],tot;
inline int New(){
  ++tim;
  ++tot;tr[tot].mn=2e18;tr[tot].mx=-2e18;
  return tot;
}
inline void pushup(int k){
  ++tim;
  tr[k].mn=min(tr[tr[k].ls].mn,tr[tr[k].rs].mn);
  tr[k].mx=max(tr[tr[k].ls].mx,tr[tr[k].rs].mx);
  return;
}
inline void tag(int k,ll v){
  ++tim;
  if(!k) return;
  tr[k].laz+=v;
  tr[k].mn+=v;tr[k].mx+=v;return;
}
inline void pushdown(int k){
  ++tim;
  ll o=tr[k].laz;tr[k].laz=0;
  if(!o) return;
  tag(tr[k].ls,o);tag(tr[k].rs,o);
  return;
}
void add(int &k,int l,int r,int p,ll v){
  ++tim;
  if(!k) k=New();
  if(l==r){
    tr[k].mn=tr[k].mx=v;return;
  }
  pushdown(k);
  if(p<=mid) add(tr[k].ls,l,mid,p,v);
  else add(tr[k].rs,mid+1,r,p,v);
  pushup(k);
}
ll ask(int k,int l,int r,int p,int op=0){
  ++tim;
  assert(k);
  if(l==r){
    ll res=tr[k].mn;
    if(op) tr[k].mx=-2e18,tr[k].mn=2e18;
    return res;
  }
  pushdown(k);
  ll res(0);
  if(p<=mid) res=ask(tr[k].ls,l,mid,p,op);
  else res=ask(tr[k].rs,mid+1,r,p,op);
  pushup(k);
  return res;
}
void change(int k,int l,int r,int p,ll v){
  ++tim;
  assert(k);
  if(l==r){
    tr[k].mn+=v;tr[k].mx+=v;return;
  }
  pushdown(k);
  if(p<=mid) change(tr[k].ls,l,mid,p,v);
  else change(tr[k].rs,mid+1,r,p,v);
  pushup(k);
  return;
}
void upd(int x,ll w){
  ++tim;
  change(rt[fa[x]],1,n,x,w);return;
}

set<int>s;
ll sef[N];
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  tr[0].mn=2e18;tr[0].mx=-2e18;
  n=read();m=read();
  for(int i=1;i<=n;i++) t[i]=read();
  for(int i=1;i<=n;i++) du[i]=2;
  for(int i=1;i<=n;i++){
    fa[i]=read();
    du[fa[i]]++;
  }
  for(int i=1;i<=n;i++) w[i]=t[i]/du[i];
  for(int i=1;i<=n;i++) v[fa[i]]+=w[i];
  for(int i=1;i<=n;i++){
    ll val=v[i]+w[fa[i]]+t[i]-w[i]*(du[i]-1);
    sef[i]=t[i]-w[i]*(du[i]-1);
    //debug("i=%d val=%lld v=%lld w=%lld du\n",i,val);
    add(rt[fa[i]],1,n,i,val);
  }
  for(int i=1;i<=n;i++){
    mn.insert(tr[rt[i]].mn);
    mx.insert(tr[rt[i]].mx);
  }
  for(int i=1;i<=m;i++){
    int op=read();
    if(op==1){
      int x=read(),y=read(),f=fa[x];
      fa[x]=y;
      //debug("erase: f:(%lld %lld) y:(%lld %lld)\n",
      //    tr[rt[f]].mn,tr[rt[f]].mx,tr[rt[y]].mn,tr[rt[y]].mx);
      s.insert(y);s.insert(f);
      s.insert(fa[y]);s.insert(fa[f]);
      s.insert(fa[fa[y]]);s.insert(fa[fa[f]]);
      for(int now:s){
	mn.erase(mn.find(tr[rt[now]].mn));mx.erase(mx.find(tr[rt[now]].mx));
      }
      ll val=ask(rt[f],1,n,x,1);val-=w[f];
      tag(rt[f],-w[f]);upd(fa[f],-w[f]);upd(f,-sef[f]);
      du[f]--;w[f]=t[f]/du[f];sef[f]=t[f]-w[f]*(du[f]-1);
      tag(rt[f],w[f]);upd(fa[f],w[f]);upd(f,sef[f]);
      
      tag(rt[y],-w[y]);upd(fa[y],-w[y]);upd(y,-sef[y]);
      du[y]++;w[y]=t[y]/du[y];sef[y]=t[y]-w[y]*(du[y]-1);
      tag(rt[y],w[y]);upd(fa[y],w[y]);upd(y,sef[y]);

      upd(f,-w[x]);upd(y,w[x]);
      
      val+=w[y];
      add(rt[y],1,n,x,val);
      for(int now:s){
	//if(n==20000) break;
	mn.insert(tr[rt[now]].mn);mx.insert(tr[rt[now]].mx);
      }      
      //debug("insert: f:(%lld %lld) y:(%lld %lld)\n",
      //    tr[rt[f]].mn,tr[rt[f]].mx,tr[rt[y]].mn,tr[rt[y]].mx);
    }
    else if(op==2){
      int x=read();
      //if(n<20000)
	printf("%lld\n",ask(rt[fa[x]],1,n,x));
    }
    else{
      //if(n<20000)
	printf("%lld %lld\n",(*mn.begin()),(*mx.rbegin()));
    }
    //if(n>=20000) printf("i=%d tot=%d\n",i,tot);
    //if(i%100==0){
    //printf("i=%d tot=%d time=%lf calc=%d\n",i,tot,1.0*clock()/CLOCKS_PER_SEC,tim);
    //}
    //if(1.0*clock()/CLOCKS_PER_SEC>4.9){
    //printf("i=%d tot=%d\n",i,tot);break;
    //}
    s.clear();
  }
  return 0;
}
/*

*/

```



---

