# [ABC279F] BOX

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc279/tasks/abc279_f

$ N $ 個の箱 $ 1,2,\dots,N $ と、 $ 10^{100} $ 個のボール $ 1,2,\dots,10^{100} $ があります。 最初、箱 $ i $ にはボール $ i $ のみが入っています。

ここに以下の操作が合計 $ Q $ 回行われるので、処理してください。

操作にはタイプ $ 1,2,3 $ の $ 3 $ 種類があります。

タイプ $ 1 $ : 箱 $ X $ に箱 $ Y $ の中身を全て入れる。 この操作では $ X\ \neq\ Y $ が保証される。

> 1 $ X $ $ Y $

タイプ $ 2 $ : 現在いずれかの箱に入っているボールの数の合計を $ k $ とすると、箱 $ X $ にボール $ k+1 $ を入れる。

> 2 $ X $

タイプ $ 3 $ : ボール $ X $ が入っている箱の番号を答える。

> 3 $ X $

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ \le\ N\ \le\ 3\ \times\ 10^5 $
- $ 1\ \le\ Q\ \le\ 3\ \times\ 10^5 $
- タイプ $ 1 $ の操作について、 $ 1\ \le\ X,Y\ \le\ N $ かつ $ X\ \neq\ Y $
- タイプ $ 2 $ の操作について、 $ 1\ \le\ X\ \le\ N $
- タイプ $ 3 $ の操作について、その時点でボール $ X $ がいずれかの箱に入っている
- タイプ $ 3 $ の操作が少なくとも $ 1 $ つ与えられる

### Sample Explanation 1

この入力は $ 10 $ 個の操作を含みます。 - $ 1 $ 回目の操作はタイプ $ 3 $ です。ボール $ 5 $ は箱 $ 5 $ に入っています。 - $ 2 $ 回目の操作はタイプ $ 1 $ です。箱 $ 1 $ に箱 $ 4 $ の中身を全て入れます。 - 箱 $ 1 $ の中身はボール $ 1,4 $ 、箱 $ 4 $ の中身は空になります。 - $ 3 $ 回目の操作はタイプ $ 2 $ です。箱 $ 1 $ にボール $ 6 $ を入れます。 - $ 4 $ 回目の操作はタイプ $ 2 $ です。箱 $ 4 $ にボール $ 7 $ を入れます。 - $ 5 $ 回目の操作はタイプ $ 3 $ です。ボール $ 7 $ は箱 $ 4 $ に入っています。 - $ 6 $ 回目の操作はタイプ $ 1 $ です。箱 $ 3 $ に箱 $ 1 $ の中身を全て入れます。 - 箱 $ 3 $ の中身はボール $ 1,3,4,6 $ 、箱 $ 1 $ の中身は空になります。 - $ 7 $ 回目の操作はタイプ $ 3 $ です。ボール $ 4 $ は箱 $ 3 $ に入っています。 - $ 8 $ 回目の操作はタイプ $ 1 $ です。箱 $ 1 $ に箱 $ 4 $ の中身を全て入れます。 - 箱 $ 1 $ の中身はボール $ 7 $ 、箱 $ 4 $ の中身は空になります。 - $ 9 $ 回目の操作はタイプ $ 3 $ です。ボール $ 7 $ は箱 $ 1 $ に入っています。 - $ 10 $ 回目の操作はタイプ $ 3 $ です。ボール $ 6 $ は箱 $ 3 $ に入っています。

## 样例 #1

### 输入

```
5 10
3 5
1 1 4
2 1
2 4
3 7
1 3 1
3 4
1 1 4
3 7
3 6```

### 输出

```
5
4
3
1
3```

# 题解

## 作者：liangbowen (赞：23)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc279_f)

[或许更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16929056.html)

并查集应用。

## 思路

本题精髓在于：我们可以把箱子与球都看成一个点。

这些点中，一部分指的是箱子，一部分指的是球。

对于操作一，我们合并 $x$ 与 $y$ 对应的箱子编号。此处是将 $y$ 归属于 $x$。

但是，只合并是不行的。例如下图的情景：

![](https://cdn.luogu.com.cn/upload/image_hosting/lcoxdw46.png)

我们现在要将 $1$ 号箱子的球投进 $2$ 号箱子里。那么只需要合并一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/0dd5gt1u.png)

但是！如果我们接下来将 $7$ 号球扔进 $1$ 号箱子时，就会出问题：

![](https://cdn.luogu.com.cn/upload/image_hosting/hx8nwdg3.png)

那么怎么避免这种问题呢？我们应该**新建**一个箱子。在合并时，我们要这样做：

![](https://cdn.luogu.com.cn/upload/image_hosting/tbjapd3i.png)

接下来，将 $7$ 号球扔进 $1$ 号箱子时，我们把它扔进 $6$ 号箱子即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/iily6pzw.png)

这样，查询时，只需要输出 $ans_6 = 1$。

---

另外两种操作则简单多了：

+ 新建小球：直接模拟合并即可。
+ 查询：若 $x$ 号球归属于 $t$ 号箱子，则输出 $ans_t$ 即可。

那么这题就完美做完啦！

## 代码

省去了缺省源。

```cpp
const int N = 9e5 + 5;
namespace UnionSet { //并查集
	int fa[N];
	int get(int x)
	{
		if (fa[x] == x) return x;
		return fa[x] = get(fa[x]);
	}
	void merge(int x, int y)
	{
		int fx = get(x), fy = get(y);
		if (fx != fy) fa[fy] = fx;
	}
}; using namespace UnionSet;
int id[N], ans[N]; //相互映射的关系，id是记录连向哪个箱子，如上面的例子中，id[1]=6
void solve()
{
	int n, q;
	scanf("%d%d", &n, &q);
	int cnt_ball = n, cnt_box = n + q;
	for (int i = 1, mx = n + 2 * q; i <= mx; i++) fa[i] = id[i] = ans[i] = i; //最多会存在 n+2*q 个点
	while (q--)
	{
		int op, x, y;
		scanf("%d%d", &op, &x);
		if (op == 1)
		{
			scanf("%d", &y);
			merge(id[x], id[y]); //合并
			cnt_box++, id[y] = cnt_box, ans[cnt_box] = y;
		}
		else if (op == 2) merge(id[x], ++cnt_ball); //新建
		else printf("%d\n", ans[get(x)]); //查询
	}
}
```

希望能帮助到大家！

---

## 作者：DaydreamWarrior (赞：4)

## 题目分析
由于要支持类似合并集合的操作，首先想到并查集。但是题目中的把 $y$ 倒入 $x$ 之后 $y$ 是空的。按照一般的并查集来做的话，此时原来属于 $y$ 的集合仍属于 $y$，并没有清空。

所以我们对于题目中的每个把 $y$ 倒入 $x$ 中的操作，在合并 $x$ 和 $y$ 之后新建一个并查集节点代替原来代表 $y$ 的并查集节点，这样就实现了清空 $y$。其他的按正常的并查集做就好。

每个合并操作新建一个节点，至多有 $n+q$ 个节点。
## 代码

```cpp
const int N = 1000005;
int c[N],w[N];
//c是每个箱子对应的是哪个并查集节点
//w是每个球对应的是哪个并查集节点
int ans[N];//每个并查集节点对应的是哪个箱子
int fa[N];
int n,q;

int find(int x){
    if(fa[x]==x)
        return fa[x];
    return fa[x]=find(fa[x]);
}

int main(){
    cin >> n >> q;
    for(int k=1;k<=n;k++)
        fa[k] = ans[k] = c[k] = w[k] = k;
    int siz = n,idx = n;
    while(q--){
        int ops;
        cin >> ops;
        if(ops==1){
            int x,y;
            cin >> x >> y;
            fa[c[y]] = c[x];
            c[y] = ++idx;
            fa[idx] = idx;//对于 y 新建一个并查集节点
            ans[idx] = y;
        }
        else if(ops==2){
            int x;
            cin >> x;
            w[++siz] = c[x];
        }
        else{
            int x;
            cin >> x;
            cout << ans[find(w[x])] << endl;
        }
    }
    return 0;
}
```

## 闲话

这可比写个合并平衡树之类的代码短多啦，代码量低于 1kb。

---

## 作者：rui_er (赞：2)

这种合并集合的操作使我们想到并查集，因此我们在并查集算法的基础上进行改造来解决问题。这里使用路径压缩实现的并查集。

在记录并查集的父亲数组的同时，我们还需要记录两个数组 $rt$ 和 $id$，$rt_i$ 表示题目中所说的第 $i$ 个集合的根是哪个元素（若为空则为 $0$），$id_i$ 表示这个元素是哪个集合的根（若不是则为 $0$）。

操作一可以直接合并。操作二在并查集中新建一个节点，若这个集合的 $rt$ 为 $0$，则把它直接设为 $rt$，否则把它挂到 $rt$ 下面作为一个儿子。操作三找到所在集合的根节点然后看 $id$ 即可。

时间复杂度 $\Theta(m\log m)$，$\log$ 是路径压缩并查集的。

```cpp
// Problem: F - BOX
// Contest: AtCoder - TOYOTA SYSTEMS Programming Contest 2022(AtCoder Beginner Contest 279)
// URL: https://atcoder.jp/contests/abc279/tasks/abc279_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int N = 1e6+5;

int n, m;
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
struct Dsu {
	int fa[N], rt[N], id[N];
	int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
	void merge(int x, int y) {
		if(!rt[y]) return;
		if(!rt[x]) {
			id[rt[y]] = x;
			rt[x] = rt[y];
			rt[y] = 0;
			return;
		}
		id[rt[y]] = 0;
		fa[rt[y]] = rt[x];
		rt[y] = 0;
	}
}dsu;

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, n) dsu.fa[i] = dsu.rt[i] = dsu.id[i] = i;
	while(m--) {
		int op, x, y;
		scanf("%d%d", &op, &x);
		if(op == 1) {
			scanf("%d", &y);
			dsu.merge(x, y);
		}
		else if(op == 2) {
			++n;
			if(!dsu.rt[x]) dsu.rt[x] = dsu.fa[n] = n, dsu.id[n] = x;
			else dsu.fa[n] = dsu.rt[x];
		}
		else printf("%d\n", dsu.id[dsu.find(x)]);
	}
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：1)

个人观感：

$T_3>T_4>T_6$

***

我们可以分操作来考虑，首先，我们可以将放入一个盒子看做一个盒子变成另一个盒子的子集，于是可以想到用并查集维护。

- $1\ x\ y$

此时 $y$ 全部进入 $x$，但是后面加入 $y$ 的球是仍然属于 $y$ 的。于是我们可以将 $y$ 放入 $x$ 的集合后新建一个节点，然后我们用这个节点表示 $y$。同时我们可以使用一个 $ans$ 数组表示我们新建的点所对应的答案。

- $2\ x$

此时我们直接加入 $x$ 所对应的盒子的最新的一个，因为它此时是唯一代表 $x$ 的。

- $3\ x$

此时我们可以考虑记录 $p_x$ 表示 $x$ 所在盒子，然后我们找到 $p_x$ 所在并查集的根节点 $root$，那么 $ans_{root}$ 即为答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
int op,x,y,tot,t,ans[maxn<<1],n,q,p[maxn<<1],fa[maxn<<1],N[maxn];
int Find(int x){
	return fa[x]=(fa[x]==x?x:Find(fa[x]));
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i)
		ans[i]=fa[i]=p[i]=N[i]=i;
	tot=t=n;
	while(q--){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d",&x,&y);
			fa[N[y]]=fa[N[x]];
			N[y]=++tot,ans[tot]=y,fa[tot]=tot;
		} else if(op==2){
			scanf("%d",&x);
			p[++t]=N[x];
		} else{
			scanf("%d",&x);
			printf("%d\n",ans[Find(p[x])]);
		}
	}
	return 0;
}
```

---

## 作者：VitrelosTia (赞：0)

操作 2，3 是简单的，问题在操作 1 暴力是 $O(n)$ 的。但这是个合并操作，那自然想到启发式合并。但是合并是有方向的，你的启发式合并必须是小的合到大的上，考虑维护：

- $vector_x$ 表示标号 $x$ 的球。
- $siz_x$ 表示 $vector_x$ 的大小。
- $pos_x$ 表示球 $x$ 的位置的标号。
- $o_x$ 表示标号 $x$ 的实际标号。
- $rnk_x$ 表示标号 $x$ 的编号。

最后询问的答案是 $rnk_{pos_x}$。

对于操作 1，直接把 $siz$ 小的合并到大的上，要修改 $vector$ 和 $pos$，如果 $siz_x > siz_y$，还要交换 $o$ 来改变 $x$，$y$ 实际表示的位置，然后为了记录答案，还要把 $rnk$ 给交换一下。

对于操作 2，直接加入就行了。代码实现比较简单。

```cpp
const int N = 1e6 + 5;
int n, Q, pos[N], o[N], rnk[N]; vector <int> v[N];

signed main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> Q; int k = n;
	for (int i = 1; i <= n; i++) v[i].push_back(i), pos[i] = i, o[i] = i, rnk[i] = i;
	for (int op, x, y; Q--; ) {
		cin >> op >> x;
		if (op == 1) {
			cin >> y;
			if (v[o[x]].size() < v[o[y]].size()) {
				for (int t : v[o[x]]) v[o[y]].push_back(t), pos[t] = o[y];
				v[o[x]].clear(); swap(o[x], o[y]); swap(rnk[o[x]], rnk[o[y]]);
			}
			else {
				for (int t : v[o[y]]) v[o[x]].push_back(t), pos[t] = o[x];
				v[o[y]].clear();
			}
		}
		if (op == 2) k++, v[o[x]].push_back(k), pos[k] = o[x];
		if (op == 3) cout << rnk[pos[x]] << '\n';
	}
	return 0;
}
```

---

