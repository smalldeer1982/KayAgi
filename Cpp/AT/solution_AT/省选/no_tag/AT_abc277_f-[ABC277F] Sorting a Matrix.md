# [ABC277F] Sorting a Matrix

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc277/tasks/abc277_f

非負整数を要素とする $ H $ 行 $ W $ 列の行列 $ A $ が与えられます。 $ 1\ \leq\ i\ \leq\ H $ かつ $ 1\ \leq\ j\ \leq\ W $ を満たす整数の組 $ (i,\ j) $ について、 $ A $ の $ i $ 行目 $ j $ 列目の要素を $ A_{i,\ j} $ で表します。

$ A $ に対して以下の手順を行います。

- まず、$ A $ の要素のうち $ 0 $ であるものそれぞれを、任意の**正の整数**で置き換える（ $ 0 $ である要素が複数ある場合、それぞれを異なる正の整数で置き換えることもできます）。
- その後、「下記の $ 2 $ つの操作のどちらかを行うこと」を好きな回数（ $ 0 $ 回でも良い）だけ行う。
  
  
  - $ 1\ \leq\ i\ \lt\ j\ \leq\ H $ を満たす整数の組 $ (i,\ j) $ を選び、$ A $ の $ i $ 行目と $ j $ 行目を入れ替える。
  - $ 1\ \leq\ i\ \lt\ j\ \leq\ W $ を満たす整数の組 $ (i,\ j) $ を選び、$ A $ の $ i $ 列目と $ j $ 列目を入れ替える。

$ A $ が次の条件を満たすようにすることができるかどうかを判定してください。

- $ A_{1,\ 1}\ \leq\ A_{1,\ 2}\ \leq\ \cdots\ \leq\ A_{1,\ W}\ \leq\ A_{2,\ 1}\ \leq\ A_{2,\ 2}\ \leq\ \cdots\ \leq\ A_{2,\ W}\ \leq\ A_{3,\ 1}\ \leq\ \cdots\ \leq\ A_{H,\ 1}\ \leq\ A_{H,\ 2}\ \leq\ \cdots\ \leq\ A_{H,\ W} $
- 言い換えると、$ 1\ \leq\ i,\ i'\ \leq\ H $ および $ 1\ \leq\ j,\ j'\ \leq\ W $ を満たす任意の $ 2 $ つの整数の組 $ (i,\ j) $ と $ (i',\ j') $ について、下記の $ 2 $ つの条件がともに成り立つ。
  
  
  - $ i\ \lt\ i' $ ならば $ A_{i,\ j}\ \leq\ A_{i',\ j'} $
  - 「 $ i\ =\ i' $ かつ $ j\ \lt\ j' $ 」ならば $ A_{i,\ j}\ \leq\ A_{i',\ j'} $

## 说明/提示

### 制約

- $ 2\ \leq\ H,\ W $
- $ H\ \times\ W\ \leq\ 10^6 $
- $ 0\ \leq\ A_{i,\ j}\ \leq\ H\ \times\ W $
- 入力はすべて整数

### Sample Explanation 1

以下の手順で操作を行うことで、$ A $ が問題文中の条件を満たすようにすることができるため、`Yes` を出力します。 - まず、$ A $ の $ 0 $ である要素を下記の通りに置き換える。 ``` 9 6 8 5 4 4 3 1 3 ``` - $ 2 $ 列目と $ 3 $ 列目を入れ替える。その結果、$ A $ は下記の通りとなる。 ``` 9 8 6 5 4 4 3 3 1 ``` - $ 1 $ 行目と $ 3 $ 行目を入れ替える。その結果、$ A $ は下記の通りとなる。 ``` 3 3 1 5 4 4 9 8 6 ``` - $ 1 $ 列目と $ 3 $ 列目を入れ替える。その結果、$ A $ は下記の通りとなり、問題文中の条件を満たすようになる。 ``` 1 3 3 4 4 5 6 8 9 ```

### Sample Explanation 2

どのように操作を行っても $ A $ が問題文中の条件を満たすようにすることはできないため、`No` を出力します。

## 样例 #1

### 输入

```
3 3
9 6 0
0 4 0
3 0 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 2
2 1
1 2```

### 输出

```
No```

# 题解

## 作者：Daidly (赞：15)

update：修改了一些逻辑上的不恰当之处。

# 题意

给定大小为 $n\times m$ 由非负整数组成的矩阵 $A$，首先用任意数替换掉 $A$ 中的 $0$，然后进行任意次交换行或列的操作，判断是否能使其满足以下条件：

- $A_{1,1}\leq A_{1,2}\leq \cdots\leq A_{1,m}\leq A_{2,1}\leq A_{2,2}\leq \cdots\leq A_{2,m}\leq A_{3,1}\leq \cdots\leq A_{n,1}\leq A_{n,2}\leq \cdots\leq A_{n,m}$

$0\leq A_{i,j}\leq n\times m\leq 10^6$.

# 题解

调了好长时间，题解内有些假做法是本人提供。

可以发现，行与列的操作是互不影响的，即：

- 对于交换行操作，行内数相对位置不变，列内数相对位置改变。
- 对于交换列操作，列内数相对位置不变，行内数相对位置改变。

无论使用多少次操作，一个数所在行与列的数组成的集合不变。

由此可说明：对于任意一个状态到另一个状态只需使用一次行操作和一次列操作时，行列顺序不影响。

通过归纳法即可证明：可以先进行完交换行的操作，再进行交换列的操作。

#### 先考虑没有 $0$ 组成的情况

考虑交换行，交换后的状态需要满足第 $i$ 行的最小值不小于第 $i-1$ 行的最大值。这个 check 操作我们记录最大值最小值排序就能完成。

若已经进行完交换行的操作，考虑把整个大小为 $n\times m$ 的矩阵投影在 $m$ 个点上，这 $m$ 个点的相对大小关系即为 $n$ 行内 $m$ 个数的大小关系，即将 $n$ 行行内大小关系约束附加到这 $m$ 个点上。若用有向边表示小到大，此时 $m$ 个点很多条边组成的图若无环，则满足题意；否则说明一定有至少两组大小关系产生矛盾，无法操作成符合题意的状态。

补充一点，这里的大小关系指的是大于或小于，对于等于的关系，不存在对答案的约束，也不应将等于看成约束。

那么这样直接做边数有多少呢，或者说复杂度是多少呢？

行内每个非零数都与另一个非零数有大小关系，边数是 $nm^2$ 数量级的，复杂度也是，所以考虑优化建图。

有一个很显然的想法是：我只对最小的大于我的点建立有向边，至于次小的大于我的点，最小的大于我的点自然会向他连边。

（为什么是大于而不是等于呢？因为等于不能看成约束。）

（有这种想法的人，如果直接开码，可能过了好长时间才发现自己假了，如果冷静思考，会发现有漏洞！）

对于 $x<y=z$，点 $x$ 会向 $y$ 连边，但是不会向 $z$ 连边，因为他指望着 $y$ 向 $z$ 连边，然而不会，所以就少了 $x<z$ 这个约束。

我们考虑建立虚点，让行内所有值相同的点归属在同一虚点下，以虚点进行行内优化连边。

有人可能会这样做：对于值相同的点向新建虚点连边，然后通过虚点直接进行连边的约束。这样做的话就不可能有环。考虑虚点的意义：只是为了保证该行行内连边的正确性，它的意义只存在于该行，所以每行都要建新的，而行内不可能有环的出现，若只在虚点间进行边的约束，则不会有环。所以，环上必须有初始的 $m$ 个点。

正确做法是，思考好如何连边，方向是什么。我们建立 $\{x\},\{y,z\}$ 的虚点 $X,Y$ 的时候，先从虚点连向覆盖的点，即 $X\to x,Y\to y,Y\to z$，然后再将 $x$ 连到 $\{y,z\}$ 的虚点 $Y$ 上即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/q6a01al8.png)

实现上，遍历每一行，用二元组 $(val,id)$ 储存该行每一个数的大小和位置，将其排序，然后对于值相同的点建立虚点按上述方式建图即可，建图后的有向图判环可以使用拓扑排序或是 dfs。

#### 再考虑有 $0$ 组成的情况

对于判断交换行操作，我们此时需要记录的是非零最大值与最小值。

对于交换列的操作，可以先不管 $0$，若不管 $0$ 不能满足无环，则算上 $0$ 新赋值的数会使约束增多，也肯定不能满足。

反之，若不管 $0$ 可以成立，我们只需要保证 $0$ 新赋值的数在非零最大值与最小值之间即可，因为一种可行的构造方法是将 $0$ 赋值为行内出现过的数，因为行内出现过的数若不会成环，则新赋值的数与其他数的大小关系和它一样也不会成环。

 ```cpp
#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=1e6+5;
int n,m,in[N<<1],num,cnt;
vector<int>e[N<<1],tmp[N];
vector<pair<int,int> >a[N];
pair<int,int>b[N];
queue<int>q;

void add(int x,int y){
	e[x].push_back(y);
	in[y]++;
}

bool topo(){
	for(int i=1;i<=cnt;++i)if(!in[i])q.push(i);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(auto v:e[u]){
			in[v]--;
			if(!in[v])q.push(v);
		}
	}
	for(int i=1;i<=cnt;++i)if(in[i]>0)return 1;
	return 0;
}

int main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i){
		a[i].resize(m+1),b[i].fi=1e9;
		for(int j=1;j<=m;++j){
			a[i][j].fi=read(),a[i][j].se=j;
			if(a[i][j].fi)b[i].fi=min(b[i].fi,a[i][j].fi),b[i].se=max(b[i].se,a[i][j].fi);
		}
	}
	sort(b+1,b+n+1);
	for(int i=1;i<n;++i){
		if(b[i].se>b[i+1].fi){
			puts("No");return 0;
		}
	}
	cnt=m;
	for(int i=1;i<=n;++i){
		sort(a[i].begin(),a[i].end());
		int cnt1=0;
		for(int j=1;j<=m;++j){
			if(!a[i][j].fi)continue;
			if(a[i][j].fi!=a[i][j-1].fi||j==1)cnt1++;
			tmp[cnt1].push_back(a[i][j].se);
		}
		for(int j=1;j<=cnt1;++j){
			for(auto k:tmp[j]){
				add(cnt+j,k);
				if(j!=cnt1)add(k,cnt+j+1);
			}
		}
		for(int i=1;i<=cnt1;++i)tmp[i].clear();
		cnt+=cnt1;
	}
	puts(topo()?"No":"Yes");
	return 0;
}
 ```

总结思路：

1. 行列独立性，行的条件；
2. 行内数的相对大小关系；
3. 优化建图，考虑虚点；
4. 判断有向图是否有环。

如果有帮助的话就点个赞吧！

---

## 作者：_SeeleVollerei_ (赞：7)

想投 Ex 题解的发现做法就一句话，交上去肯定过不了审。

早上起来有人问 F 咋做，然后看了一眼。

咋听到的做法都是建图阿，不理解，这里提供一个直接在原矩阵上做的确定性做法。

首先显然只要满足非 0 的数之间满足排序即可，然后 0 是一定有合法填法的。

然后一个最重要的性质是，原本在同一行的数，交换后依然在同一行。列同理。

那么我们可以把行和列分开考虑。

先考虑行。我们对每个行求出非 0 的数中的最大值和最小值，那么排序后要求前一行的最大值 $\le$ 下一行的最小值。直接 sort 即可。

考虑列。我们考虑模拟选择排序的过程，每次选择最小的列放在最前面。为了方便，这里我们将选了的列都视作被删掉了。

那么一个列满足当前条件，它上面的数要么是 0，要么是所在行中未被删掉的数中的最小值。

这启发我们对每个列维护一个数组 $sum_j$，表示第 $j$ 列上有多少个数当前是满足条件的，每次取一个 $sum_j=n$ 的列删掉即可。

然后我们考虑动态的去维护这个过程，类似双指针的形式。

具体地，我们将每个行内部按照权值排序，然后每行维护一个指针 $now_i$ 表示第 $i$ 行的最小值对应的下标。

注意到因为我们要判断某一行当前的最小值是否已经全被删了，来判断是否走到下一个最小值，所以我们需要知道具体删掉了哪些列，所以我们拿一个容器存下未被删的满足 $sum_j=n$ 的列的编号即可。

容器选择栈，队列等等都可以，但是因为我早上有点犯浑所以直接 set 了，栈和队列的复杂度是 $O(nm)$，set 会多一个 $\log$。

https://atcoder.jp/contests/abc277/submissions/36462900

---

## 作者：golden_brick (赞：4)

# Sorting a Matrix

#### solution:

##### 在这里，我们先不考虑 $0$。

我们发现，行之间的交换与列之间的交换互不影响，所以我们分开判断即可。

###### 行判断：

我们可以求出来每一行的最大值与最小值扔进 `vector` 里面排序。

然后看上一行的最大值比下面的最小值大那就输出 `No`。

###### 接下来我们来看列：

我们可以用一个有向图来表示列与列之间的大小关系。

如果有一对 $a_{i,j1} \le a_{i,j2}$ 那我们就让 $j1$ 向 $j2$ 连边。

最后我们只需要判断原图是不是一个 `DAG` 即可。

但这样子的复杂度太大了最高去到了 $O(HW^2)$。

于是我们将前一个数连到一个新建的点上，再从这个点向后一个元素连边。

那这样我们的复杂度就成功的降到了 $O(HW)$。

##### 最后我们来看 $0$：

由于 $0$ 可以变成任何数，所以我们在做的时候直接忽略他就行了。

#### code:

```cpp
#include <bits/stdc++.h>
#define fi first
#define endl '\n'
#define se second
#define il inline
#define pb push_back
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e6 + 10;
int n, m, a[N];
int l, in[N << 1];
vector<int> G[N << 1];
il int id(int i, int j) { return (i - 1) * m + j; }
bool tpsort()
{
    int cnt = 0;
    queue<int> q;
    for (int i = 1; i <= l; i++)
        if (in[i] == 0)
            q.push(i), cnt++;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto v : G[u])
        {
            in[v]--;
            if (in[v] == 0)
                q.push(v), cnt++;
        }
    }
    return cnt == l;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    vector<pii> v;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int mi = INF, ma = -INF;
        for (int j = 1; j <= m; j++)
        {
            cin >> a[id(i, j)];
            if (a[id(i, j)])
                mi = min(mi, a[id(i, j)]),
                ma = max(ma, a[id(i, j)]);
        }
        if (mi < INF)
            v.pb({mi, ma});
    }
    sort(v.begin(), v.end());
    for (int i = 2; i < v.size(); i++)
        if (v[i - 1].se > v[i].fi)
            return (cout << "No" << endl, 0);
    for (int i = 1; i <= n; i++)
    {
        vector<pii> v2;
        for (int j = 1; j <= m; j++)
            if (a[id(i, j)])
                v2.pb({a[id(i, j)], j});
        sort(v2.begin(), v2.end());
        for (int k = 1; k < v2.size(); k++)
            if (v2[k - 1].fi != v2[k].fi)
            {
                int u = m + v2[k].fi;
                l = max(l, u);
                for (int o = k - 1; v2[o].fi == v2[k - 1].fi && o >= 0; o--)
                    G[v2[o].se].pb(u), in[u]++;
                for (int o = k; v2[o].fi == v2[k].fi && o < v2.size(); o++)
                    G[u].pb(v2[o].se), in[v2[o].se]++;
            }
    }
    cout << (tpsort() ? "Yes" : "No") << endl;
    return 0;
}
```



---

## 作者：SFlyer (赞：3)

## 题目大意

> 你有一个矩阵 $A$, 第 $i$ 行第 $j$ 列的数为 $A_{i,j}$。首先，你要把 $A$ 中数值为 $0$ 的数替换为一个任意正整数。然后，有如下操作：
>
> - 选定 $1\le i\le j \le H$，交换第 $i$ 行和第 $j$ 行。
> - 选定 $1\le i\le j \le W$，交换第 $i$ 列和第 $j$ 列。
>
> 你想要通过若干种这种操作，使得对于每一对 $(i,j)$ 和 $(i',j')$，
>
> - 若 $i<i'$，$A_{i,j}\le A_{i',j'}$。
> - 若 $i=i'$ 且 $j<j'$，$A_{i,j}\le A_{i',j'}$。

## 分析

### 1. 如何处理  $0$

如果我们转换一下题意，让我们可以先操作，后替换 $0$。那么，当我们操作完以后，一定会有解。因此，我们可以忽略 $0$.

证明：我们把操作后的矩阵用一个集合来表示。若去掉数值为 $0$ 的部分，则此集合 $S=\{s_1,s_2,s_3,\cdots, s_k\}$ 满足 $s_1\le s_2\le s_3\le\cdots \le s_k$。假设原始集合中，$s_i$ 与 $s_j$ 之间有若干个 $0$，则把这些 $0$ 均变为 $s_i$ 即可。比如 $S=\{1,0,0,2,0,0,3\}$，就可以替换为 $S'=\{1,1,1,2,2,2,3\}$。

### 2. 如何处理操作

首先，把需要满足的条件转化为

> 对于 $1\le i \le H$，令 $mn_i=\min\{A_{i,1},A_{i,2},\cdots,A_{i,W}\}$，$mx_i=\max\{A_{i,1},A_{i,2},\cdots,A_{i,W}\}$。则，
>
> - $mn_1\le mx_1\le mn_2\le mx_2\le \cdots \le mn_H\le mx_H$。
>
> - $A_{i,1}\le A_{i,2} \le \cdots \le A_{i,W}$。

这样转换的好处是

- 若行与行换，则条件 $2$ 不会变。
- 若列与列换，则条件 $1$ 不会变。

因为行与列的交换互相独立，所以，我们只需要找到一种方法，使得

- 若干次行与行交换后，满足条件 $1$。
- 若干次列与列交换后，满足条件 $2$。

#### 行与行交换

可以贪心，按照 $mn_i$ 从小到大排序，当有 $(i,j)$ 使得 $mn_i=mn_j$ 时，按照 $mx_i$ 从大到小排序。

可以证明，如果有解，这样排完序后，满足条件 $1$.

#### 列与列交换

因为要满足每一行条件 $2$ 都满足，所以不能贪心。

我们先考虑列 $j$ 可以在 $j'$ 前面要满足的条件：

- 对于 $1\le i \le H$，$A_{i,j}\le A_{i,j'}$。

通过这个条件可以发现若有 $(j,j')$ 使

- 存在 $1\le i \le H$，$A_{i,j}\le A_{i,j'}$。
- 存在 $1\le i \le H$，$A_{i,j} > A_{i,j'}$。

那么 $j$ 既不能在 $j'$ 前面也不能在 $j'$ 后面，无解。

所以这启发我们构图：对于所有的 $i$，枚举 $(j,k)$（$1\le j,k \le W$），若 $A_{i,j}\le A_{i,k}$，从 $A_{i,j}$ 到 $A_{i,k}$ 连一条边。若这图中无环，也就是有拓扑序，则有解。

但是，这种方法最多会建 $HW^2$ 条边，所以要考虑优化。

**优化**

你想要把 $N$ 个点和 $M$ 个点一一连边。若连 $NM$ 条边，变数会太大。因此，我们可以增加一个点 $u$，把那 $N$ 个点和 $u$ 连接，再把 $u$ 和那 $M$ 个点连接。

在这个题中，我们也可以这样操作，把一行中同样值的点视为一个点。这样，就只会有 $HW$ 条边。

代码略。

---

## 作者：DengDuck (赞：2)

一年前期末考试的题， 现在重新看了看，自己想出来了，现在觉得好简单啊/kk。

我们考虑行操作，列操作对一个行的影响：

- 行操作不会改变任何一个行。
- 列操作只改变行内元素的排列，不改变有哪些元素。

同样的道理适用于列。

所以我们考虑以一行的最小值和最大值当关键字，排序所有的行。

排完之后如果前一行的最大值大于后一行的最小值，那么就无解。

之后我们就是要找到一个交换方法，使得每行变成单调不降的数列。

容易想到建图，我连边表示排列之后我这一列应该在你前面。

由于有相同的值，相同的值内部顺序无法确定，因此你只能让值上相邻的两个点连边，这样边数会很多。

容易想到对于一列的某一个值，建两个点表示坐标的最小值和最大值，然后值域上相邻的值就只用连一条边了。

然后每个点再连接自己值的那两个点。

判判环就行了，时间复杂度为 $\mathcal O(nm)$。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define pb push_back
#define pLL pair<LL,LL>
#define fir first
#define sec second
using namespace std;
const LL N = 3e6 + 5;
LL n, m, p[N], mx[N], mn[N],vis[N],tot;
vector<LL> a[N],v[N],V;
unordered_map<LL,LL>Mn,Mx;
void dfs(LL x)
{
	if(vis[x]==-1)return;
	if(vis[x]==1)
	{
		puts("No");
		exit(0);
	}
	vis[x]=1;
	for(LL i:v[x])
	{
		dfs(i);
	}
	vis[x]=-1;
}
int main() 
{
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) 
	{
		mn[i] = n * m + 1, p[i] = i;
		for (int j = 1; j <= m; j++) 
		{
			LL x;
			scanf("%lld", &x);
			a[i].pb(x);
			if (x)mn[i] = min(mn[i], x), mx[i] = max(mx[i], x);
		}
	}
	sort(p + 1, p + n + 1, [](LL x, LL y) 
	{
		if (mn[x] == mn[y])return mx[x] < mx[y];
		return mn[x] < mn[y];
	});
	for (int i = 2; i <= n; i++) 
	{
		if (mx[p[i - 1]] > mn[p[i]]) 
		{
			puts("No");
			return 0;
		}
	}
	tot=m;
	for(int i=1;i<=n;i++)
	{
		V.clear(),Mx.clear(),Mn.clear();
		for(int j=0;j<m;j++)
		{
			if(a[i][j])V.pb(a[i][j]);
			if(!Mn.count(a[i][j]))
			{
				Mn[a[i][j]]=++tot;
				Mx[a[i][j]]=++tot;
			}
		}
		sort(V.begin(),V.end());
		V.erase(unique(V.begin(),V.end()),V.end());
		int len=V.size();
		for(int j=1;j<len;j++)
		{
			v[Mx[V[j-1]]].pb(Mn[V[j]]);
		}
		for(int j=0;j<m;j++)
		{
			if(a[i][j])
			{
				v[Mn[a[i][j]]].pb(j);
				v[j].pb(Mx[a[i][j]]);
			}
		}		
	}
	for(int i=0;i<m;i++)dfs(i);
	for(int i=m+1;i<=tot;i++)dfs(i);
	puts("Yes");
}
```

---

## 作者：lzqy_ (赞：2)

写篇题解纪念首场ABC就挂的大分。

首先发现行和列相互之间不会影响，所以分开讨论。

对于行来说，$A_{i,j}=0$ 是不会影响最终的答案的，因为它不会使该行的最大值变小，或最小值变大。所以只需要剔除 $0$ 之后按照首元素为第一关键字，末元素为第二关键字排序，看是否单调不降即可。

-----

麻烦一点的是行。容易想到的是对于 $A_{i,x}>A_{i,y}\,(A_{i,x}\not=0,A_{i,y} \not= 0)$ 来说，等价于第 $x$  列必须在第 $y$ 列之前。所以只需要建图判断有没有环即可。

但问题在于这样的边数是 $O((HW)^2)$ 的。考虑对于**排完序**的一行（编号打乱，权值升序），我们发现，每个点连向的点都是一段前缀。所以直接前缀和优化建图就做完了。

具体建图方式的话，就是对于每行的每一个点 $x$ 都额外开一个虚点 $x'$，虚点 $x'$ 连向 $x$ 以及同一行上一个虚点（如果存在）。每个点向前连边的时候，只需要连向前缀的最后一个节点所对应的虚点。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxn=1000010;
il int read(){
	int x=0,f=1;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar())
		if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x*f;
} 
struct edge{
	int v,to;
}e[maxn*30];
int head[maxn*30],ecnt;
void addedge(int u,int v){
	e[++ecnt].v=v,e[ecnt].to=head[u],head[u]=ecnt;
}
struct Imf{
	int id,w;
};
int ru[maxn*30],P[maxn];
int n,m,N,Id[maxn],Fir[maxn];
vector<Imf>v[maxn];
il bool cmp1(Imf a,Imf b){return a.w<b.w;}
il bool cmp2(int x,int y){
	if(v[x][Fir[x]].w^v[y][Fir[y]].w)
		return v[x][Fir[x]].w<v[y][Fir[y]].w;
	else return v[x][m].w<v[y][m].w;
}
queue<int>q;
bool chk(){
	for(int i=1;i<=N;i++)
		for(int j=head[i];j;j=e[j].to)
			ru[e[j].v]++;
	for(int i=1;i<=N;i++)
		if(!ru[i]) q.push(i);
	int t,cn=0;
	while(!q.empty()){
		t=q.front(),q.pop(),cn++;
		for(int i=head[t];i;i=e[i].to){
			ru[e[i].v]--;
			if(!ru[e[i].v]) q.push(e[i].v); 
		}
	}return cn==N;
}
int main(){
//	printf("Yes\n");return 0;
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		v[i].push_back(Imf{0,0}),Id[i]=i;
		for(int j=1;j<=m;j++)
			v[i].push_back(Imf{j,read()});
		sort(v[i].begin()+1,v[i].end(),cmp1);
		for(int j=1;j<=m;j++)
			if(v[i][j].w==0) Fir[i]++;
		Fir[i]++;
	}sort(Id+1,Id+1+n,cmp2);
	for(int i=2;i<=n;i++)
		if(Fir[Id[i]]<=m&&v[Id[i]][Fir[Id[i]]].w<v[Id[i-1]][m].w)
			return printf("No\n"),0;
	N=m;
	for(int i=1;i<=n;i++)
		for(int j=Fir[i],lst=0;j<=m;j++){
			++N,addedge(N,v[i][j].id),P[j]=N;
			if(j!=Fir[i]) addedge(N,N-1);
			if(v[i][j].w!=v[i][j-1].w&&j!=Fir[i]) lst=j-1;
			if(lst) addedge(v[i][j].id,P[lst]); 
		}
	printf("%s\n",chk()?"Yes":"No");
	return 0;
}
```

---

## 作者：chrispang (赞：1)

## 题目大意

给定一个 $H\times W$ 的一个矩阵，其中第 $i$ 行第 $j$ 列的数字为 $A_{i,j}$，如果 $A_{i,j}=0$，那么你需要将其替换为任意正整数。

你现在有两种操作：

- 选择两行 $i,j$，交换这两行的数字。
- 选择两列 $i,j$，交换这两列的数字。

你希望交换之后满足 $A_{1,1}\le A_{1,2}\le A_{1,3}\le ⋯ ≤ A_{1,W}\le A_{2, 1}\le ⋯ \le A_{2,W}\le ⋯ \le A_{H,W}$。

如果存在至少一种替换数字的方案和操作方案，输出 `Yes`，否则输出 `No`。

## 题目分析

在这里，$0$ 这种特殊情况其实可以不需要考虑，因为当最后的矩阵定下之后，最后剩下的 $0$ 只要取旁边的数的值就行了，因此抛弃 $0$ 的操作。

那么只剩下行操作和列操作了。

我们考虑行操作，列操作对一个行的影响：

- 行操作不会改变任何一个行。
- 列操作只改变行内元素的排列，不改变元素的数值。

列同理。

因此可以先进行完交换行操作，再进行交换列操作。

---

接下来，我们将对两种操作依次分析。

行操作：

> 因为行操作不会改变一个行，因此我们只考虑第 $i$ 行到第 $i + 1$ 行的关系就行。
>
> 由于我们最后的矩阵要求第 $i$ 行的最大值 $\le$ 第 $i+1$ 行的最小值。因此我们可以通过求出每一行的最小值与最大值。最后进行排序，看看是否满足要求（注意这里不包括 
> $0$）。

列操作：

> 因为列操作不会改变两个行之间的关系，因此我们只考虑每一行的关系就可以。
>
> 由于题目要求最后的矩阵每一行都是单调不减的，因此我们对每一列操作的时候要保证第 $i$ 列的第 $j$ 个值 $\le$ 第 $i+1$ 列的第 $j$ 个值。也就是进行排序。
>
> 最后再看看排序后的每一列是否满足条件即可。
>
> ---
>
> 这里我使用了排序，而 ATcoder 官方题解与洛谷大部分题解都使用了建图的方法，最后判断是否有拓扑序。这也是一种很好的方法，也值得我们去学习。

---

## 题目代码

```cpp
#include <bits/stdc++.h>
#define maxn 1000010
using namespace std;

int h, w;
map<int, map<int, int> > a; //存下一个矩阵
vector<int> col[maxn];  //按列存储
struct node {
    int maxx, minx; //存储每一行的最大值和最小值
} row[maxn]; //按行存储

bool cmp1(node x, node y) { //按行排序（这里按最大值排序与最小值排序没有区别，都可以使用）
    if (x.maxx != y.maxx)
        return x.maxx < y.maxx; //按最大值排序
    else
        return x.minx < y.minx; //若最大值相等，则按最小值排序
}

bool cmp2(vector<int> x, vector<int> y) { //按列排序
    bool flag = 0;
    for (int i = 0; i < h; i++)
        if (x[i] && y[i] && x[i] != y[i]) { //每一行的数不能是0，如果相等，则可以直接跳过（相等还比啥，接着往下一行比较呀）
            if (x[i] > y[i]) //不符合条件
                return false;
            flag = 1; //符合条件（用flag存起来是怕下面比较行的时候又出岔子）
        }
    return flag;
}

bool check(vector<int> x, vector<int> y) { //对每一列进行检查，判断是否满足题目条件
    for (int i = 0; i < h; i++)
        if (x[i] && y[i] && x[i] > y[i]) //每个数都不是0，且不满足条件
            return false;
    return true;
}

int main() {
    cin >> h >> w;
    for (int i = 1; i <= h; i++) {
        row[i].maxx = -1, row[i].minx = 1e9; //待会要取最大最小值
        for (int j = 1; j <= w; j++) {
            cin >> a[i][j];
            if (a[i][j])
                row[i].maxx = max(row[i].maxx, a[i][j]), row[i].minx = min(row[i].minx, a[i][j]); //取最大值和最小值
        }
    }
    for (int i = 1; i <= w; i++)
        for (int j = 1; j <= h; j++) col[i].push_back(a[j][i]); //存下每一列
    sort(row + 1, row + h + 1, cmp1); //按行排序
    sort(col + 1, col + w + 1, cmp2); //按列排序
    for (int i = 1; i < h; i++)
        if (row[i].maxx > row[i + 1].minx) { //不满足条件
            cout << "No" << endl;
            return 0;
        }
    for (int i = 1; i < w; i++)
        if (!check(col[i], col[i + 1])) { //不满足条件
            cout << "No" << endl;
            return 0;
        }
    cout << "Yes" << endl;
    return 0;
}
```

---

## 作者：Resolute_Faith (赞：1)

观察到行跟列的贡献相互独立，我们先考虑行吧。

行的要求就是排序后这一行的最小值要大于等于上一行的最大值，所以我们记每一行的最小值和最大值，最后全部排序起来，即可先把行判完。

列的要求是对于每一行右边都必须大于等于左边。所以我们把这么多个 `vector` 拿去一起排序，排出来再检查一下就知道了。

提醒：`vector` 要开就要注意很多细节，我本来习惯下标从 $1$ 开始的全都被迫改成 $0$ 开始/ll

好像官解是拓扑，也是一个很不错的解法，本质上是判环，优化建图。

```cpp
vector<pair<int,int> > a;
bool cmp(vector<int> &x,vector<int> &y){
    bool op=false;
    for(register int i=0;i<n;i++){
        if(x[i]&&y[i]&&x[i]!=y[i]){
            if(x[i]>y[i]) return false;
            op=true;
        }
    }
    return op;
}
bool check(vector<int> &x,vector<int> &y){
    for(register int i=0;i<n;i++){
        if(x[i]&&y[i]&&x[i]>y[i]) return false;
    }
    return true;
}
signed main(){
    n=read(),m=read();
    vector<vector<int>> v(m);
    for(register int i=1;i<=n;i++){
        int maxn=-inf,minn=inf;
        for(register int j=0;j<m;j++){
            int x=read();
            v[j].push_back(x);
            if(x!=0){
                maxn=max(maxn,x);
                minn=min(minn,x);
            }
        }
        if(maxn!=0) a.push_back(make_pair(minn,maxn));
    }
    sort(a.begin(),a.end());//解决行
    for(register int i=1;i<a.size();i++){
        if(a[i-1].sec>a[i].fir){
            printf("No");
            return 0;
        }
    }
    sort(v.begin(),v.end(),cmp);//解决列
    for(register int i=0;i<m-1;i++){
        if(!check(v[i],v[i+1])){
            printf("No");
            return 0;
        }
    }
    printf("Yes");
}
```

---

## 作者：翼德天尊 (赞：1)

F 好难调啊……

考虑对于行和列分别判断约束，对于行的约束其实就是，将每一行的最小值最大值看成一个区间后，要求区间不能相交。

除此之外，可能需要特判 $min=max$ 的情况，不然或许会对线段重合的判断造成影响，这点调了俩小时；以及也需要特判一行全 $0$ 的情况。

那对于列的约束怎么处理呢？我们发现对于每一列实际上是给了我们若干形如【第 $i$ 列小于第 $j$ 列】的约束关系。

那么我们不妨将行内元素排序，在忽视 $0$ 的情况下，从较小权值的列向较大权值的列连边，最后看图中有没有环即可判断约束是否矛盾。

不过注意还存在一车元素相等，另一车相邻的元素也相等的情况。

此时如果直接由左侧元素向右侧元素两两连边复杂度显然不对，于是我们可以采用经典的优化建图 trick，将相等的元素统一连到一个新建的虚点上，再从这个虚点向后一个元素连边即可。

时间复杂度 $O(H\log H+H\times W)$.

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
#define st set<node>::iterator
const int N=1e6+5;
const int INF=1e9;
int n,m,cnt,sta[N<<2],stot,dfn[N<<2],tim,qtot;
bool vis[N<<2];
struct Vector{
	int x,id;
	Vector (int x=0,int id=0)
		:x(x),id(id){}
};
vector<Vector> ve[N];
struct node{
	int l,r;
	node (int l=0,int r=0)
		:l(l),r(r){}
}qu[N];
struct node1{
	int head[N<<2],tot,to[N<<2],next[N<<2];
	void adde(int u,int v){
		to[++tot]=v,next[tot]=head[u],head[u]=tot;
	}
}S;
ll read(){
	ll w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
void dfs(int u){
	dfn[u]=++tim;
	sta[++stot]=u,vis[u]=1;
	for (int i=S.head[u];i;i=S.next[i]){
		int v=S.to[i];
		if (!dfn[v]){
			dfs(v);
		}else if (vis[v]){
			if (dfn[v]<dfn[u]){
				puts("No");
				exit(0);
			}
		}
	}
	--stot,vis[u]=0;
}
bool cmp(node x,node y){
	return x.l<y.l;
}
bool cmp1(Vector x,Vector y){
	return x.x<y.x;
}
signed main(){
	n=read(),m=read();
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++){
			int x=read();
			ve[i].push_back(Vector(x,j));
		}
	for (int i=0;i<n;i++){
		int maxn=0,minn=INF;
		for (int j=0;j<m;j++)
			if (ve[i][j].x!=0) maxn=max(maxn,ve[i][j].x),minn=min(minn,ve[i][j].x);
		if (maxn==0) continue;
		if (minn!=maxn) qu[++qtot]=node(minn,maxn);
	}
	sort(qu+1,qu+1+qtot,cmp);
	for (int i=1;i<qtot;i++){
		if (qu[i].r>qu[i+1].l){
			puts("No");
			return 0;
		}
	}
	cnt=m;
	for (int i=0;i<n;i++){
		sort(ve[i].begin(),ve[i].end(),cmp1);
		int la=-1,now=cnt++;
		for (int j=0;j<m;j++){
			if (ve[i][j].x==0) continue;
			if (j!=0&&ve[i][j-1].x!=0&&ve[i][j].x!=ve[i][j-1].x) la=now,now=cnt++;
			S.adde(ve[i][j].id,now); 
			if (la!=-1) S.adde(la,ve[i][j].id);
		}
	}
	for (int i=0;i<cnt;i++)
		if (!dfn[i]) dfs(i);
	puts("Yes");
	return 0;
}
```

---

