# [ARC063E] 木と整数

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc063/tasks/arc063_c

$ N $ 頂点の木があり、頂点には $ 1,\ 2,\ ...,\ N $ と番号が振られています。$ i $ ($ 1\ ≦\ i\ ≦\ N\ -\ 1 $) 番目の辺は頂点 $ A_i $ と頂点 $ B_i $ を結んでいます。

高橋君は木の $ K $ 個の頂点に整数を書き込みました。具体的には、各 $ 1\ ≦\ j\ ≦\ K $ について、頂点 $ V_j $ に整数 $ P_j $ を書き込みました。その後、高橋君は居眠りを始めました。

木を見つけた青木君は、残りのすべての頂点に整数を書き込み、高橋君を驚かせようとしています。高橋君を驚かせるためには、木が次の条件を満たさなければなりません。

- 条件: 辺で直接結ばれた $ 2 $ つの頂点に書かれている整数の差がちょうど $ 1 $ である。

残りのすべての頂点に書き込む整数を工夫することで、木が条件を満たすようにできるか判定してください。もし可能な場合は、どのように整数を書き込めばよいかを具体的にひとつ求めて下さい。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ K\ ≦\ N $
- $ 1\ ≦\ A_i,\ B_i\ ≦\ N $ ($ 1\ ≦\ i\ ≦\ N\ -\ 1 $)
- $ 1\ ≦\ V_j\ ≦\ N $ ($ 1\ ≦\ j\ ≦\ K $) (21:18, 制約の誤記を修正)
- $ 0\ ≦\ P_j\ ≦\ 10^6 $ ($ 1\ ≦\ j\ ≦\ K $)
- 与えられるグラフは木になることが保証される
- $ V_j $ はすべて相異なる

### Sample Explanation 1

はじめ、木は以下の図のような状態である。頂点のそばに書かれた数が頂点番号を、頂点の中に書かれた青い数が元から書き込まれていた整数を表す。 !\[6da26f89839711a520acdf5c3e1cc309.png\](https://atcoder.jp/img/arc063/6da26f89839711a520acdf5c3e1cc309.png) 青木君はたとえば次のように残りの頂点に整数を書き込むことで木が条件を満たすようにできる。これは出力例 $ 1 $ に対応している。 !\[1858d5af5a2c0e51aca39a39d765debb.png\](https://atcoder.jp/img/arc063/1858d5af5a2c0e51aca39a39d765debb.png) 木が条件を満たしていれば、これとは異なった出力でも AC となることに注意せよ。たとえば、入力例 $ 1 $ に対しては ``` Yes 7 6 8 7 7 ``` という出力でも正答となる。

### Sample Explanation 3

新たに書き込む整数は負になったり $ 10^6 $ を超えたりしても構わない。

## 样例 #1

### 输入

```
5
1 2
3 1
4 3
3 5
2
2 6
5 7```

### 输出

```
Yes
5
6
6
5
7```

## 样例 #2

### 输入

```
5
1 2
3 1
4 3
3 5
3
2 6
4 3
5 7```

### 输出

```
No```

## 样例 #3

### 输入

```
4
1 2
2 3
3 4
1
1 0```

### 输出

```
Yes
0
-1
-2
-3```

# 题解

## 作者：Kinandra (赞：7)

标签:构造

有一个很容易想到的构造: 将所有初始点权确定的点放入一个优先对列中(以点权为关键字), 每次从优先队列中取出点权最小的点 $u$, 将与其相连的未确定点权的点**确定**为 $u$ 的点权 $+1$. 构造完后在对每一条边判断合法性即可. 正确性很容易体会到.

由于最大的点权减最小的点权不大于 $n$ , 所以优先队列是不必要的, 可用 `vector` (或链表)来存每种点权有那些点.

时间复杂度 $\mathcal O(n)$ .

```cpp
#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;
int read();

int n, k;
int res[200005], vis[200005];
vector<int> e[200005], dis[200005];
void add(int f, int t) { e[f].push_back(t), e[t].push_back(f); }
bool check(int x, int y) { return x - y == 1 || y - x == 1; }

int main() {
    n = read();
    for (int i = 1, u, v; i < n; ++i) u = read(), v = read(), add(u, v);
    k = read();
    int mn = 100000000;
    for (int i = 1, u; i <= k; ++i)
        u = read(), mn = min(res[u] = read(), mn), vis[u] = 1;
    for (int i = 1; i <= n; ++i)
        if (vis[i]) dis[res[i] - mn].push_back(i);
    for (int i = 0; i < n; ++i)
        for (int j = dis[i].size() - 1, u; j >= 0; --j)
            for (int t = e[u = dis[i][j]].size() - 1, v; t >= 0; --t)
                if (!vis[v = e[u][t]])
                    res[v] = res[u] + 1, dis[i + 1].push_back(v), vis[v] = 1;
    for (int u = 1; u <= n; ++u)
        for (int i = e[u].size() - 1, v; i >= 0; --i)
            if (!check(res[u], res[e[u][i]])) return puts("No"), 0;
    puts("Yes");
    for (int u = 1; u <= n; ++u) printf("%d\n", res[u]);
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}

```

---

## 作者：zhylj (赞：4)

## 分析

考虑一个必要条件是二分图染色后奇数和偶数不能出现在同一个颜色中。

然后我们注意到如果是一条链，确定的数是在其中一个端点，则某个点可以取到的值是某个区间中奇偶性相同的一些值。

于是容易想到，先判掉奇偶性不对的情况，然后定一个根，维护每个点在只考虑子树内的时候能取的值所属的区间。

然后就做完了，时间复杂度 $\mathcal O(n)$.

## 代码

```cpp
const int N = 5e5 + 5, Inf = 0x3f3f3f3f;

int n, m, rev, A[N], L[N], R[N], d[N];
bool flag;
std::vector <int> E[N];
void Add(int u, int v) {
	E[u].push_back(v);
	E[v].push_back(u);
}

void Dfs(int u, int fa) {
	d[u] = d[fa] ^ 1;
	for(int v : E[u]) if(v != fa) {
		Dfs(v, u);
		L[u] = std::max(L[u], L[v] - 1);
		R[u] = std::min(R[u], R[v] + 1);
	}
	if(L[u] > R[u]) flag = false;
	if(A[u] != -1) {
		if(A[u] > R[u] || A[u] < L[u]) flag = false;
		if(rev == -1) rev = (A[u] & 1) ^ d[u];
		else if(rev != ((A[u] & 1) ^ d[u])) flag = false;
		L[u] = R[u] = A[u];
	}
}
void Col(int u, int fa) {
	if(fa) {
		int c1 = A[fa] - 1, c2 = A[fa] + 1;
		A[u] = c1 >= L[u] && c1 <= R[u] ? c1 : c2;
	} else A[u] = L[u];
	for(auto v : E[u]) if(v != fa) {
		Col(v, u);
	}
}

int main() {
	memset(A, 0xff, sizeof(A));
	memset(L, ~0x3f, sizeof(L));
	memset(R, 0x3f, sizeof(R));
	rd(n); flag = true;
	for(int i = 1; i < n; ++i) {
		int u, v; rd(u, v);
		Add(u, v);
	}
	rd(m);
	for(int i = 1; i <= m; ++i) {
		int x, y; rd(x, y);
		A[x] = y;
	}
	rev = -1;
	Dfs(1, 0);
	if(!flag) {
		printf("No\n");
	} else {
		printf("Yes\n");
		Col(1, 0);
		for(int i = 1; i <= n; ++i)
			printf("%d\n", A[i]);
	}
	return 0;
}
```

---

## 作者：Doveqise (赞：2)

STL数据结构水过的一道题...  
用bool数组记录一下  
用优先队列维护一下  
下见代码
```cpp
#include<bits/stdc++.h>
#define pa pair<int,int>
#define maxn 100005
using namespace std;
priority_queue<pa>q;
vector<int>v[maxn];
int A,B,a[maxn];
bool used[maxn],has[maxn];
int main(){
	int n;scanf("%d",&n);for(int i=1;i<n;i++){
		scanf("%d%d",&A,&B);
		v[A].push_back(B);
		v[B].push_back(A);}
	int k;scanf("%d",&k);for(int i=0;i<k;i++){
		scanf("%d%d",&A,&B);
		a[A]=B;has[A]=1;q.push(pa(-B,A));}
	while(!q.empty()){
		B=-q.top().first,A=q.top().second;q.pop();
		used[A]=1;for(int i=0;i<(int)v[A].size();i++)
		if(!used[v[A][i]]&&has[v[A][i]]&&a[v[A][i]]!=B+1){puts("No");return 0;}
		else if(!used[v[A][i]]) used[v[A][i]]=1,a[v[A][i]]=B+1,q.push(pa(-B-1,v[A][i])),has[v[A][i]]=1;}
	puts("Yes");
	for(int i=1;i<=n;i++)printf("%d\n",a[i]);
	return 0;
}

```


---

## 作者：Black_Porridge (赞：0)

感觉其他题解的文字说明都好抽象啊，本篇题解会稍微说的详细一点。

首先有解/无解是容易判断的，考虑将所有指定点按照 ```dfn``` 序排序，若相邻两者权值之差和两者间距离之差奇偶性不同，则说明无解。

接下来提供两个做法。

### Sol1

每次选出当前已经赋值的所有点中权值 $w$ 最小的点 $u$，将其相邻无赋值点 $v$ 赋为 $w_u+1$。

以下为做法正确性证明。

设 $w_u<w_v$，且有解，那么 $u\to v$ 路径上点的权值有两种情况。

- $dis(u, v) = w_v-w_u$，此时路径上点的权值是单增序列，显然使用上述做法可以构造。

- $dis(u,c)=w_v-w_u+2x$，前面提到过奇偶性的问题，由于二者奇偶性相同，所以可以表示成此处的形式。此时路径上的点权可以是一个先增后减的序列，显然上述做法可以构造。

时间复杂度 $O(n\log n)$。

### Sol2

树形dp，设 $[l_u,r_u]$ 表示 $u$ 这个点以及其子树内所有点均合法时， $w_u$ 的取值范围。显然有 $[l_u, r_u]=\bigcap_{v \in son_u}[l_v-1,r_v+1]$，注意 $i \in [l_u,r_u]$ 并不是全部合法的，需要去除奇偶性不同的情况。而后从根节点开始向下构造答案即可。

时间复杂度 $O(n)$。

---

