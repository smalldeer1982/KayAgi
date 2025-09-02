# [ARC188C] Honest or Liar or Confused

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc188/tasks/arc188_c

$ 1 $ から $ N $ までの番号がついた $ N $ 人の村人が住む村があります。 各村人は、正直者であるか嘘つきであるかのどちらかです。また、村人のうち何人かは混乱しています。

あなたは、村人による証言を $ M $ 個手に入れました。この証言は、$ i=1,2,\ \ldots\ ,M $ に対して $ A_i,\ B_i,\ C_i $ で与えられ、

- $ C_i=0 $ であれば、村人 $ A_i $ が村人 $ B_i $ を正直者であると証言したこと
- $ C_i=1 $ であれば、村人 $ A_i $ が村人 $ B_i $ を嘘つきであると証言したこと

を表します。

全ての村人は、他の全ての村人について正直者と嘘つきのどちらであるかを知っており、あなたに対して次のような規則で証言を行ったことが分かっています。

- 混乱していない正直者は必ず正しい証言をする。
- 混乱していない嘘つきは必ず嘘の証言をする。
- 混乱している正直者は必ず嘘の証言をする。
- 混乱している嘘つきは必ず正しい証言をする。

すなわち、混乱していなければ正直者は正しい証言を、嘘つきは嘘の証言をしますが、混乱していると逆になります。

あなたは**混乱している村人の組**を予想することにしました。 混乱している村人の組を決めると、与えられた $ M $ 個の証言からなる証言の組が「矛盾する」かどうかが定まります。 ここで、証言の組が「矛盾する」というのは、各村人が正直者であるか嘘つきであるかをどのように決めても、証言の組の中に、村人が行う証言の規則に反するものが存在することを意味します。

与えられた証言の組が矛盾しないような**混乱している村人の組**を $ 1 $ つ見つけてください。 ただし、どのような村人の組が混乱しているとしても与えられた証言の組が矛盾する場合は、そのことを指摘してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ \mathrm{min}\ \lbrace\ 2\ \times\ 10^5,N(N-1)\ \rbrace $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N,\ A_i\ \neq\ B_i $
- $ i\neq\ j $ のとき $ A_i\neq\ A_j $ または $ B_i\neq\ B_j $
- $ C_i=0 $ または $ C_i=1 $
- 入力される値はすべて整数である

### Sample Explanation 1

村人 $ 1 $ が混乱していない正直者、村人 $ 2 $ が混乱している嘘つき、村人 $ 3 $ が混乱していない正直者であると仮定します。 このとき、村人 $ 1 $ は、村人 $ 2 $ が嘘つきである、村人 $ 3 $ が正直者であると正しい証言をします。 また、村人 $ 2 $ は嘘つきですが混乱しているため、村人 $ 3 $ が正直者であると正しい証言をします。 したがって、与えられた証言が全て村人の証言の規則通りに得られるため、村人 $ 2 $ のみ混乱していることを表す `010` は正当な出力の $ 1 $ つです。

### Sample Explanation 2

村人 $ 2,3 $ が混乱していると仮定してみます。 このとき、各村人が正直者であるかどうかについて $ 2^3=8 $ 通りの組み合わせがあります。 このうち、例えば、「村人 $ 1 $ が（混乱していない）正直者、村人 $ 2 $ が（混乱している）嘘つき、村人 $ 3 $ が（混乱している）正直者」であるとすると、村人 $ 2 $ は規則によれば正しい証言をするはずですが、村人 $ 1 $ を嘘つきであると嘘の証言をしています。 他の組み合わせに対しても、同様に規則に反する証言が生じることを確認できます。 したがって、村人 $ 2,3 $ が混乱しているとすると、与えられた証言の組は矛盾します。 実は、このケースでは、どのような村人の組が混乱しているとしても与えられた証言の組は矛盾します。

### Sample Explanation 3

混乱している人数は任意であり、題意の条件が満たされるならば $ 0 $ 人や全員でもよいです。

## 样例 #1

### 输入

```
3 3
1 2 1
1 3 0
2 3 0```

### 输出

```
010```

## 样例 #2

### 输入

```
3 6
1 2 1
1 3 0
2 1 1
2 3 0
3 1 1
3 2 0```

### 输出

```
-1```

## 样例 #3

### 输入

```
3 0```

### 输出

```
000```

# 题解

## 作者：rui_er (赞：12)

乍一看以为是 3-SAT 不可做，动动脑子发现是 2-SAT（

鉴于本题解书写时洛谷题面暂无中文翻译，为避免可能的歧义或困惑，先对本题解中的译法进行约定：

- 英文题面中“honest villager”或日文题面中“正直者”译为“诚实村民”。
- 英文题面中“liar”或日文题面中“嘘つき”译为“撒谎村民”。
- 英文题面中“confused”或日文题面中“混乱している”译为“糊涂的”。
- 英文题面中“not confused”或日文题面中“混乱していない”译为“清醒的”。
- 英文题面中“testimony”或日文题面中“証言”译为“证言”。

设 $P_i$ 表示第 $i$ 位村民是否是撒谎村民，$Q_i$ 表示第 $i$ 位村民是否是糊涂的。根据题意列出证言的真值表：

|$A$ 身份|$P_A$|$A$ 状态|$Q_A$|$B$ 身份|$P_B$|$C$ 结果|$C$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|诚实村民|$0$|清醒的|$0$|诚实村民|$0$|诚实村民|$0$|
|诚实村民|$0$|清醒的|$0$|撒谎村民|$1$|撒谎村民|$1$|
|诚实村民|$0$|糊涂的|$1$|诚实村民|$0$|撒谎村民|$1$|
|诚实村民|$0$|糊涂的|$1$|撒谎村民|$1$|诚实村民|$0$|
|撒谎村民|$1$|清醒的|$0$|诚实村民|$0$|撒谎村民|$1$|
|撒谎村民|$1$|清醒的|$0$|撒谎村民|$1$|诚实村民|$0$|
|撒谎村民|$1$|糊涂的|$1$|诚实村民|$0$|诚实村民|$0$|
|撒谎村民|$1$|糊涂的|$1$|撒谎村民|$1$|撒谎村民|$1$|

容易观察到证言 $(A,B,C)$ 实际上限制了 $P_A\oplus Q_A\oplus P_B=C$。

注意到，一位村民是否是撒谎村民和她是否清醒是无关的，并且上式中 $P_A$ 和 $Q_A$ 总是绑定在一起，因此不难想到设 $R_i=P_i\oplus Q_i$。证言 $(A,B,C)$ 的限制转化为 $R_A\oplus P_B=C$，是经典的 2-XOR-SAT 问题。使用扩展域并查集求解出 $P_i$ 和 $R_i$ 的一组解（或判定无解），再根据 $Q_i=P_i\oplus R_i$ 求得并输出 $Q_i$ 即可。

题目要求构造出一组解（而非判定是否有解），构造的过程比较容易想不清楚写错，赛时直接爽吃五发罚时。

核心代码：

```cpp
//By: OIer rui_er
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)

const int N = 8e5 + 5;

int n, m, ans[N];

struct Dsu {
    int fa[N];
    void init(int x) {rep(i, 1, x) fa[i] = i;}
    int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
    bool same(int x, int y) {return find(x) == find(y);}
    bool merge(int x, int y) {
        if(same(x, y)) return false;
        x = find(x); y = find(y);
        fa[x] = y;
        return true;
    }
}dsu;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    dsu.init(4 * n);
    rep(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        if(w == 0) {
            dsu.merge(u + 2 * n, v);
            dsu.merge(u + 2 * n + n, v + n);
        }
        else {
            dsu.merge(u + 2 * n, v + n);
            dsu.merge(u + 2 * n + n, v);
        }
    }
    rep(i, 1, n) {
        if(dsu.same(i, i + n)) {
            cout << "-1" << endl;
            return 0;
        }
        if(dsu.same(i + 2 * n, i + 2 * n + n)) {
            cout << "-1" << endl;
            return 0;
        }
    }
    // rep(i, 1, n) cout << dsu.find(i) << " " << dsu.find(i + n) << " " << dsu.find(i + 2 * n) << " " << dsu.find(i + 3 * n) << endl;
    rep(i, 1, n) {
        if(dsu.same(i, i + 2 * n)) cout << 0;
        else if(dsu.same(i, i + 2 * n + n)) cout << 1;
        else {
            dsu.merge(i + 2 * n, i);
            dsu.merge(i + 2 * n + n, i + n);
            cout << 0;
        }
    }
    cout << endl;
    return 0;
}
```

---

## 作者：rainygame (赞：4)

设一个人是否诚实为 $a_i$，是否迷乱为 $b_i$，令 $f_i=a_i\oplus b_i$（$\oplus$ 为异或），那么每个证词等价于 $f_x \oplus a_y=c$。

当 $c=0$ 时，$f_x$ 和 $a_y$ 要么同为 $0$，要么同为 $1$；当 $c=1$ 时，$f_x$ 和 $a_y$ 必定不同。

考虑扩展域并查集，令 $1\sim n$ 表示 $a_i=0$，$n+1\sim 2n$ 表示 $a_i=1$，$2n+1\sim3n$ 表示 $f_i=0$，$3n+1\sim4n$ 表示 $f_i=1$。按照上述结论合并即可。当 $(i,i+n)$ 或 $(i+2n,i+3n)$ 处于同一集合时，无解。

对于构造方案，直接求出一组合法的 $a_i$ 和 $f_i$ 即可，注意使得 $(i,i+n)$ 或 $(i+2n,i+3n)$ 不能同为真，具体见代码。

时间复杂度 $O(n \log n)$，带 $4$ 倍常数。[submission](https://atcoder.jp/contests/arc188/submissions/60243532)

---

## 作者：ran_qwq (赞：3)

场上手玩 B 手玩吐了，没时间看 C，赛后发现 C 是水题，服了。

考虑并查集，一个点分成四份，分别表示守序善良的，守序邪恶的，证词中善良的（可能守序可能混乱，下同），证词中邪恶的，分别用 $i,i+n,i+2n,i+3n$ 表示。

证词 $(a,b,0)$ 则表示 $a+2n$ 向 $b$ 连边，$a+3n$ 向 $b+n$ 连边。$(a,b,1)$ 则表示 $a+2n$ 向 $b+n$ 连边，$a+3n$ 向 $b$ 连边。

如果此时 $i$ 和 $i+n$ 连通则无解。

否则按顺序处理每个人 $i$。

如果他的非证词部分已经和证词部分连通，则这个人是否混乱已经被确定了。具体地，如果 $i$ 和 $i+2n$ 连通，则他是守序的；如果 $i$ 和 $i+3n$ 连通，则他是混乱的。

如果不连通，可以钦定他守序，并且连上 $i$ 和 $i+2n$ 以及 $i+n$ 和 $i+3n$ 的边。

由对称性可知少连一半的边也是可行的。

```cpp
int n,m;
struct DSU {
	int fa[N*4];
	void init() {for(int i=1;i<=n*4;i++) fa[i]=i;}
	il int fd(int u) {return u==fa[u]?u:fa[u]=fd(fa[u]);}
	il void mg(int u,int v) {u=fd(u),v=fd(v); if(u!=v) fa[u]=v;}
	il int chk(int u,int v) {return fd(u)==fd(v);}
} dsu;
void QwQ() {
	n=rd(),m=rd(),dsu.init();
	for(int u,v,w;m--;) {
		u=rd(),v=rd(),w=rd();
		if(w) dsu.mg(u+n*2,v+n),dsu.mg(u+n*3,v);
		else dsu.mg(u+n*2,v),dsu.mg(u+n*3,v+n);
	}
	for(int i=1;i<=n;i++) if(dsu.chk(i,i+n)) return puts("-1"),void();
	for(int i=1;i<=n;i++) 
		if(dsu.chk(i,i+n*2)||dsu.chk(i,i+n*3)) wr(dsu.chk(i,i+n*3));
		else wr(0),dsu.mg(i,i+n*2),dsu.mg(i+n,i+n*3);
}
```

---

## 作者：DATA_joel (赞：3)

[link: ARC188C Honest or Liar or Confused](https://atcoder.jp/contests/arc188/tasks/arc188_c)

## 题意

共有 $N$ 个人，各具有两个属性：糊涂与否、撒谎与否。现给出 $M$ 条指认关系形如：“$A$ 认为 $B$ 是/否撒谎”。上述指认关系满足：

+ 若发出者不糊涂且不撒谎，那么指认为真（符合事实，即“说真话”）。
+ 若发出者糊涂且不撒谎，那么指认为假（不符合事实，即“说假话”）。
+ 若发出者不糊涂且撒谎，那么指认为假（不符合事实，即“说假话”）。
+ 若发出者糊涂且撒谎，那么指认为真（符合事实，即“说真话”）。

其实就是说：如果发出指认关系的人撒谎，就想说假话，否则想说真话 ~~（废话）~~，如果他糊涂，这句话就变成反话。

根据这些关系推出每个人是否糊涂，求任意一个可行解，或报告无解。

## 分析

我们先记糊涂与否这个变量为 $C=1/0$，撒谎与否这个变量为 $L=1/0$。

观察题目，可以看出每条关系都表示了两个布尔变量的取值关系，但是比较复杂，我们要简化这些关系！

考虑记 $T=1$ 是“说真话”，$T=0$ 是“说假话”。那么四种情况的指认关系立马简化为两种。

+ 若发出者说真话，那么指认为真。
+ 若发出者说假话，那么指认为假。

~~（又是废话）~~

那么对于一条指认关系，“$A$ 认为 $B$ 撒谎”，有这些关系：

+ $B$ 撒谎（$L_B=1$）与 $A$ 说真话（$T_A=1$）互为充要条件。
+ $B$ 不撒谎（$L_B=0$）与 $A$ 说假话（$T_A=0$）互为充要条件。

表达了关系：$L_B$ 与 $T_A$ 取值相同。若是“$A$ 认为 $B$ 不撒谎”，则说明 $L_B$ 与 $T_A$ 取值不同。

题目信息转化为了一堆布尔变量两两之间的取值关系，且只有在 $T$ 与 $L$ 之间连边。一眼 2-SAT 可做！

我们对于一个人建出 $4$ 个点：$L,\neg L,T,\neg T$，表示 $L=1/0,T=1/0$ 并且根据上述转化连边。

对于一条指认关系，“$A$ 认为 $B$ 撒谎”，连这些边：

+ $T_A\rarr L_B$
+ $L_B\rarr T_A$
+ $\neg T_A\rarr \neg L_B$
+ $\neg L_B\rarr \neg T_A$

我们就限制了 $T_A$ 与 $L_B$ 取值相同。

同理连剩下 “$A$ 认为 $B$ 不撒谎” 的边（不清楚可见代码），跑完 2-SAT 后就知道了 $T,L$ 的取值。

我们可以通过 $T,L$，反推出题目要求的 $C$。

具体来说，只要同时满足 $L\wedge T$ 或者 $\neg L \wedge \neg T$（撒谎但说真话或者不撒谎但说假话），则可以说这个人满足 $C=1$，否则 $C=0$。

注意啦！$L$ 与 $T$ 的取值是相互独立的，不会互相影响（因为 $C$ 并未确定，而每个 $L,T$ 取值的可能都对应一个 $C$ 的取值）。所以一个解存在矛盾当且仅当：存在 $i$ 有 $T_i$ 与 $\neg T_i$ 同时成立或 $L_i$ 与 $\neg L_i$ 同时成立。

[赛时AC记录](https://atcoder.jp/contests/arc188/submissions/60128360) ~~（码风注意，垃圾实现注意，下方的代码已经编辑过了码风orz）~~

**Code:** （代码中与上述分析略有不同，将 $\neg T$ 的点记为 `F`、将 $\neg L$ 的点记为 `H`）

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double Lf;
typedef double lf;
const int N = 1e6 + 5, M = 1e6 + 5;
int n, m;
int h[N], ec = -1;
struct Ed
{
	int to, nxt;
} ed[M];
void add(int fr, int to)// 前向星连边
{
	ec++;
	ed[ec] = {to, h[fr]};
	h[fr] = ec;
}
bool T_[N], L_[N];// 记录答案
// 下面四个函数实现了将一个对象建成四个点
int T(int x) { return (x - 1) * 4; }	 //"true"
int F(int x) { return (x - 1) * 4 + 1; } //"false"
int L(int x) { return (x - 1) * 4 + 2; } //"liar"
int H(int x) { return (x - 1) * 4 + 3; } //"honest"
void sta(int x) // 用于统计，将拆开的点记录的信息分开记录
{
	switch (x % 4)
	{
		case 0:
		{
			T_[x / 4 + 1] = true;
			break;
		}
		case 1:
		{
			T_[x / 4 + 1] = false;
			break;
		}
		case 2:
		{
			L_[x / 4 + 1] = true;
			break;
		}
		case 3:
		{
			L_[x / 4 + 1] = false;
			break;
		}
	}
}
int dfn[N], low[N], pvt = 0, sc = 0, s[N];
bool instk[N];
stack<int> S;
void Tarjan(int cur) // Tarjan 缩点
{
	dfn[cur] = low[cur] = ++pvt;
	S.push(cur);
	instk[cur] = true;
	for (int i = h[cur]; i != -1; i = ed[i].nxt)
	{
		int v = ed[i].to;
		if (!dfn[v])
		{
			Tarjan(v);
			low[cur] = min(low[cur], low[v]);
		}
		else if (instk[v])
		{
			low[cur] = min(low[cur], dfn[v]);
		}
	}
	if (low[cur] == dfn[cur])
	{
		sc++;
		while (!S.empty())
		{
			s[S.top()] = sc;
			instk[S.top()] = false;
			if (S.top() == cur)
			{
				S.pop();
				break;
			}
			S.pop();
		}
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);// 将每个点拆为四个点 T,F,L,H 分别表示 T=1,T=0,L=1,L=0
		if (w == 1)
		{
			add(T(u),L(v));
			add(L(v),T(u));
			add(F(u),H(v));
			add(H(v),F(u));
		}
		else
		{
			add(T(u),H(v));
			add(H(v),T(u));
			add(F(u),L(v));
			add(L(v),F(u));
		}
	}
	int cnt = H(n);// 偷懒的写法，记录了拆点后的点数
	for (int i = 0; i <= cnt; i++)// 考虑 2-SAT，Tarjan 缩点求拓扑序
	{
		if (!dfn[i]) // 对于每个连通块都要缩点
		{
			Tarjan(i);
		}
	}
	bool acce = true;
	for (int i = 0; i <= cnt; i++)
	{
		if (s[i] == s[i ^ 1])// 同时取到某个变量的两个值，布尔方程组无解
		{
			acce = false;
			break;
		}
		if (s[i] > s[i ^ 1]) // 用较小拓扑序的取值方案更新答案，注意标号是反拓扑序
		{
			sta(i);
		}
	}
	if (!acce)
	{
		printf("-1\n");
		return 0;
	}
	for (int i = 1; i <= n; i++)// 通过已知信息求取 C 的取值
	{
		if ((T_[i] && L_[i]) || (!T_[i] && !L_[i]))// 老实人说假话，大骗子讲真话，倒反天罡
			putchar('1');
		else
			putchar('0');
	}
	putchar('\n');
	return 0;
}
```

---

## 作者：liuzr156 (赞：1)

### 题意
有 $N$ 个人，其中有的人诚实，有的人撒谎。有 $M$ 份证词，$C_i = 0$ 表示 $A_i$ 说 $B_i$ 是诚实的，反之同理。一个诚实的人一定说真话，一个撒谎的人一定说假话。

现在有若干个人糊涂了，一个诚实的人迷糊了就会说假话，一个撒谎的人迷糊了就会说真话。请构造一个长度为 $N$ 的 $01$ 字符串，第 $i$ 个字符表示这个人是否迷糊了，并且满足证词的要求。

### 解法

参考了官方题解

对于没有迷糊的版本是个经典的问题，可以使用二分图染色或者扩展域并查集完成。本题中，由于一个人迷糊了，其证词就会与其状态相反。所以考虑把这个人的证词拎出来建一个新的点 $i+N$。对于每一条证词，相当于添加一条 $(A_i+N,B_i,C_i)$  的边。表示 $A_i$ 的证词，与 $B_i$ 这个人的状态是否相同。然后这个就回到经典问题了，如果这个图会矛盾，就是无解。如果不矛盾，则我们可以得到 $i$ 以及其证词 $i+N$ 的状态，直接异或即为答案。


```cpp
#include <bits/stdc++.h>

#define LL long long

using namespace std;
const int N = 5e5 + 10 , INF = 0x3f3f3f3f;

int h[N], e[N], nex[N], w[N], idx;
int vis[N], d[N];
void add(int a, int b, int c){
	e[++idx] = b;
	w[idx] = c;
	nex[idx] = h[a];
	h[a] = idx;
}
void dfs(int u){
	vis[u] = 1;
	for(int i = h[u]; i ;i = nex[i]){
		int v = e[i];
		if(vis[v]){
			if(d[u] ^ w[i] != d[v])
				puts("-1"), exit(0);
		}
		else
			d[v] = d[u] ^ w[i], dfs(v);
	}
}
signed main(){
	int n, m;
	cin >> n >> m;
	for(int i = 1;i <= m;i ++){
		int a, b, c;
		cin >> a >> b >> c;
		a += n;
		add(a, b, c);
		add(b, a, c);
	}
	for(int i = 1;i <= n;i ++)
		if(!vis[i])	dfs(i);
	for(int i = 1;i <= n;i ++)
		cout << (d[i] ^ d[i + n]);
	return 0;
}


```

---

## 作者：Hell0_W0rld (赞：1)

第一次表现分 $\color{#FF8000}\text{2400+}$，写篇题解纪念一下。

# ARC188C Honest or Liar or Confused
Difficulty: $\color{#C0C000}\text{2377}$。

## 题目大意
有 $N$ 个人，其中有若干个老实人和若干个骗子。老实人总说真话，骗子总说假话。给出了 $N$ 条证词，第 $i$ 条为：$A_i$ 说 $B_i$ 是骗子（用 $C_i=1$ 表示）或老实人（用 $C_i=0$ 表示）。但每个人都可能被魅惑了，说出的话和他的本意正好相反。给出一个被魅惑的人的集合。

## 解题思路
我们只考虑第 $i$ 个人说出来的是真话还是假话。定义 $tt_i$ 表示第 $i$ 个人说的是真话还是假话，$hl_i$ 表示第 $i$ 个人是老实人还是骗子。

对每一个人，说 $x$ 是老实人的和说他是骗子的，呈现出来的 $tt$ 值必然相同，考虑在并查集上把这些人合并。

合并完之后，记 $S0_x$ 表示说 $x$ 是骗子的人的集合，$S1_x$ 表示说 $x$ 是老实人的人的集合。若 $\exist a\in S0_x,~\exist b\in S1_x$，$a$ 和 $b$ 属于同一个节点下的并查集，则无解。否则将 $a$ 和 $b$ 所在的并查集对应根节点之间连一条边（任选即可，因为 $\forall a,b \in S0_x$ 有 $a$ 和 $b$ 在同一个并查集里，$S1$ 同理）。

而显然连完之后的图应当是一个二分图，否则无法给它们分配 $tt$ 值。跑完之后，对于每一条线索再求出对应的 $hl$ 值，异或一下就是每个人是否被魅惑的答案。

## 代码实现
写起来很舒服。~~应该没人把 B 交到 C 吃罚时吧。~~

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rep(i,l,r) for(register ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(register ll i=(r);i>=(l);--i)
#define all(x) x.begin(),x.end()
#define Set(x,y) memset(x,y,sizeof(x))
#define Cpy(x,y) memcpy(x,y,sizeof(x))
#define cll const long long
using namespace std;
template<class T>
void death(T s){cout<<s<<endl;exit(0);}
cll N=200009,V=600009;
ll n,m;
vector<ll> p[N][2],tl[N][2],grp[V],ldr,to[V];
ll id[V];
ll root(ll u){return id[u]==u?u:id[u]=root(id[u]);}
void merge(ll x,ll y){
	x=root(x),y=root(y);
	if(x==y)return;
	id[x]=y;
}
ll vst[V],tt[N],hl[N];
bool BiG=1;
void dfs(ll u,ll clr){
	if(!BiG)return;
	vst[u]=clr;
	for(auto v:to[u]){
		if(!vst[v])dfs(v,3-clr);
		else if(vst[v]==clr)BiG=0;
	}
}
int main(){
	cin>>n>>m;
	rep(i,1,m){
		ll a,b,x;cin>>a>>b>>x;
		p[b][x].push_back(a);
		tl[a][x].push_back(b);
	}
	rep(i,1,n*3)id[i]=i;
	rep(i,1,n){
		ll t=n+i,f=n+n+i;
		for(auto x:p[i][0])merge(x,t);
		for(auto x:p[i][1])merge(x,f);
	}
	rep(i,1,n){
		set<ll> s[2];
		for(auto x:p[i][0])s[0].insert(root(x));
		for(auto x:p[i][1])s[1].insert(root(x));
		for(auto a:s[0])if(s[1].count(a))death(-1);
		for(auto a:s[0])for(auto b:s[1])to[a].push_back(b),to[b].push_back(a);
	}
	rep(i,1,n*3)if(i==root(i)&&!vst[i])dfs(i,1);
	if(!BiG)death(-1);
	rep(i,1,n){
		ll u=root(i);
		if(vst[u]==1)tt[i]=1;
		else tt[i]=0;
	}
	rep(i,1,n){
		for(auto u:tl[i][0]) hl[u]=tt[i];
		for(auto u:tl[i][1]) hl[u]=1-tt[i];
	}
	rep(i,1,n)cout<<(hl[i]^tt[i]);
	return 0;
}
```

---

## 作者：fight_for_humanity (赞：1)

[cnblogs](https://www.cnblogs.com/fight-for-humanity/p/18565481)。

**扩展域并查集+带权并查集**。

题意中给的是骗子与否和糊涂与否，似乎有多个二元关系。观察结果：如果一个人不糊涂，那么 $C = 0$ 代表他们同是诚实的或者都是骗子；$C = 1$ 代表他们的诚实与否不同。

这时我们就可以不在意这个人是否诚实了，我们就去关系人与人之间的相对关系。若这个人是糊涂的，事实上的 $C$ 就会相反。那么“处理关系”，“关系相反”，想到使用带权并查集，权值为 $01$ 异或。那么如何处理糊涂与否呢？我们可以利用对带权并查集的结果去判断。具体的，每个点 $U$ 都设置一个扩展点 $V$，表示这个人所表述的。每次处理 $a,b,c$，就将 $V_a$ 和 $U_b$ 合并，边权为 $c$。后面遍历下来对 $U,V$ 处理，根据并查集中的权值即可判定 $U_i,V_i$ 之间的边权，若为 $1$，则这个人是糊涂的。

增加 $V$ 点作为扩展域并查集作用的一个体现，即将这个人所说的东西与这个人独立出来，判断是否自洽。再在后面对这个人本身和这个人所说的相关联，判断是否愚蠢，达成目的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 4e5 + 10;
int n,m;
struct DSU{
	int fa[N],val[N];
	inline void init(int _n){
		for(int i = 1;i<=_n;++i)fa[i] = i, val[i] = 0;
	}
	int find(int x){
		if(x == fa[x])return x;
		int pa = find(fa[x]);
		val[x] ^= val[fa[x]];
		return fa[x] = pa;
	}
	inline bool merge(int x,int y,int d){
		int fx = find(x), fy = find(y);
		if(fx == fy)return val[x] ^ d == val[y];
		fa[fx] = fy;
		val[fx] = val[x] ^ val[y] ^ d;
		return true;
	}
	int & operator [](const int i){ return val[i]; }
}dsu;

int main(){
	scanf("%d%d",&n,&m);
	dsu.init(n << 1);
	int a,b,c;
	while(m--){
		scanf("%d%d%d",&a,&b,&c);
		if(!dsu.merge(a+n,b,c))return puts("-1"),0;
	}
	for(int i = 1;i<=n;++i){
		if(dsu.find(i) == dsu.find(i+n)){
			(dsu[i] ^ dsu[i+n]) ? putchar('1') : putchar('0');
		}else{
			dsu.merge(i,i+n,0);
			putchar('0');
		}
	}
	return 0;
}
```

---

## 作者：Albert_van (赞：0)

[题](https://www.luogu.com.cn/problem/AT_arc188_c) [题](https://atcoder.jp/contests/arc188/tasks/arc188_c)。个人感受，ARC 在重构以后质量急转直下，每场都是大 DP + 序列计数 + 奇怪位置的签到题 + 不可做题。且签到都是官解搞复杂了导致的，譬如这题和上场 D。

设 $a_i$ 表示第 $i$ 个人是**诚实的**还是**骗子**（$1/0$），$b_i$ 表示第 $i$ 个人是否**说真话**（$1/0$）。那么“$x$ 宣称 $y$ 是诚实的 / 骗子（$c=0/1$）”描述了一条限制：$b_x\oplus a_y=c$，$\oplus$ 为异或运算。设 $k_i$ 表示第 $i$ 个人是否有障碍（confused），$k_i=a_i\oplus b_i$，问题即构造出一组 $a,b$。也就是有 $2n$ 个布尔变量和 $m$ 条限制形如两个变量相等或不等，用扩展域并查集（种类并查集）直接做。不会的可以看[板子](https://www.luogu.com.cn/problem/P3631)。

```cpp
#include <cstdio>

int anc[231231<<2];//0+:a0 n+:a1 2n+:b0 3n+:b1
int qry(int x){return anc[x]==x?x:anc[x]=qry(anc[x]);}
void mrg(int x,int y){anc[qry(x)]=qry(y);}

int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<n<<2;++i) anc[i]=i;
	while(m--){
		int x,y,c;scanf("%d%d%d",&x,&y,&c);--x;--y;
		mrg(x+n*2,y+c*n);mrg(x+n*3,y+(1-c)*n);
	}
	for(int i=0;i<n;++i) if(qry(i)==qry(i+n)||qry(i+2*n)==qry(i+3*n)) return puts("-1"),0;
	for(int i=0;i<n;++i) putchar('0'+((qry(i)/n)&1^(qry(i+2*n)/n)&1));
}
```

---

## 作者：_lmh_ (赞：0)

首先把这个人“是不是诚实的人”和“是否说真话”的两个状态拆开，也就是说我们要把描述异或上后面那个状态，得到前面的状态。现在把这两个状态简称为 $a$ 和 $b$。

现在用多个人对同一个人的 $a$ 状态的描述可以得出他们的 $b$ 状态的两种可能，也就是说只要决定了一个人的状态其他人的也都决定下来了。

用并查集维护这个等价类（[这道题](https://www.luogu.com.cn/problem/P2024)的技巧），$i,i+n$ 分别代表 $b_i=0$ 和 $b_i=1$ 的可能性。如果最后它们在一个等价类之内自然无解，否则随便钦定一个 $b$ 的值，剩下的可以再枚举一遍 $b$ 状态的限制算出来。

最后 $a$ 显然是好算的。时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=200007;
ll n,m,a[N],ans[N],fa[N<<1];
vector<pair<ll,ll> > vec[N];
ll getfa(ll x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	bool fl=1;
	cin>>n>>m;
	for (int i=1;i<=n;++i){fa[i]=i;fa[i+n]=i+n;}
	for (int a,b,c,i=1;i<=m;++i){
		cin>>a>>b>>c;vec[b].emplace_back(make_pair(a,c));
	}
	for (int i=1;i<=n;++i) if (vec[i].size()){
		int x=vec[i][0].first,y;
		for (int j=1;j<vec[i].size();++j){
			int c=vec[i][j].second^vec[i][0].second;y=vec[i][j].first;
			if (c){
				fa[getfa(y)]=getfa(x+n);fa[getfa(y+n)]=getfa(x);
			}
			else{
				fa[getfa(y)]=getfa(x);fa[getfa(y+n)]=getfa(x+n);
			}
		}
	}
	for (int i=1;i<=n;++i){
		fl&=(getfa(i)!=getfa(i+n));
	}
	if (!fl){
		cout<<-1;return 0;
	}
	for (int i=1;i<=n;++i) if (getfa(i+n)<=n) ans[i]=1;
	for (int i=1;i<=n;++i) if (vec[i].size()) a[i]=ans[vec[i][0].first]^vec[i][0].second;
	for (int i=1;i<=n;++i) cout<<(a[i]^ans[i]);
	return 0;
}
```

---

## 作者：Felix72 (赞：0)

场上对着 A 想了很久，现在发现其实 C 还是很能做的嘛。

混乱的人让我们不好直接确认两个人是否是同一类人。但是我们知道同一个人的行为模式其实是不会改变的，也就是说同一个人指认的一群好人必然是同类，他指认的一群坏人也是同类，并且这两群人必然是异类。

先用并查集把上面这些信息处理好，再进入下一个阶段的判定。我们用边 $x \xrightarrow{w} y$ 表示一个指认关系，并对于每条边单独考虑：

- 如果 $x$ 和 $y$ 是否是同一类人这一事实已确定，又与 $w$ 相吻合，那我们直接考虑下一条边；
- 如果 $x$ 和 $y$ 是否是同一类人这一事实已确定，但与 $w$ 相冲突，说明 $x$ 是混乱的，需要记录一下；
- 如果 $x$ 和 $y$ 是否是同一类人这一事实未确定，那么我们随便钦定他们是否是同一类人，然后考虑下一条边。

下面证明在有解的情况下，我们必然得到一组解。

首先，我们的第一个和第二个策略都没有其他的选择，唯一可能导致无解的举动是这个看似随意的钦定。但是我们注意到，若一个人指认两个人分别为好人和坏人，则它们必然不同类。而在第一阶段中，我们已经把他们用并查集区分开了，也就是说，第二阶段我们处理的边可以视作这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/o3zbe6v5.png)

如图，红蓝和橙紫表示两批人是异类。

我们按照边权进行钦定，把图变成右边的样子。可以发现，如果原图是二分图，则钦定后的图也是二分图，且如果无解，应该在第一个阶段就被发现。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 200010;
int n, m; vector < int > edge[N][2]; bool res[N];

inline void quit() {cout << -1 << '\n'; exit(0);}
struct DSU
{
	int prt[N * 2], siz[N * 2];
	inline void init(int n) {for(int i = 1; i <= n; ++i) prt[i] = i, siz[i] = 1;}
	inline int find(int x) {return ((prt[x] == x) ? x : (prt[x] = find(prt[x])));}
	inline void merge(int x, int y)
	{
		x = find(x), y = find(y);
		if(x != y)
		{
			if(siz[x] > siz[y]) swap(x, y);
			prt[x] = y, siz[y] += siz[x], siz[x] = 0;
		}
	}
}; DSU dsu;

inline void get(int x, int y, int w)
{
	if(res[x]) w = 1 - w;
	if(w == 0)
	{
		if(dsu.find(x) == dsu.find(y + n))
			res[x] = true;
		else dsu.merge(x, y), dsu.merge(x + n, y + n);
	}
	else
	{
		if(dsu.find(x) == dsu.find(y))
			res[x] = true;
		else dsu.merge(x, y + n), dsu.merge(x + n, y); 
	}
}

inline void debug()
{
	dsu.init(n * 2);
	for(int i = 1; i <= n; ++i)
	{
		for(int op = 0; op <= 1; ++op)
		{
			for(int x : edge[i][op])
			{
				if(op ^ res[i]) dsu.merge(i, x + n), dsu.merge(i + n, x);
				else dsu.merge(i, x), dsu.merge(i + n, x + n);
			}
		}
	}
	for(int i = 1; i <= n; ++i)
		if(dsu.find(i) == dsu.find(i + n))
			{cerr << "Wrong Answer" << '\n'; exit(1);}
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m; dsu.init(n * 2);
	for(int i = 1; i <= m; ++i)
	{
		int x, y, w; cin >> x >> y >> w;
		edge[x][w].push_back(y);
	}
	for(int i = 1; i <= n; ++i)
	{
		int lst = 0;
		for(int x : edge[i][0])
		{
			if(lst)
			{
				dsu.merge(x, lst);
				dsu.merge(x + n, lst + n);
			}
			lst = x;
		}
		lst = 0;
		for(int x : edge[i][1])
		{
			if(lst)
			{
				dsu.merge(x, lst);
				dsu.merge(x + n, lst + n);
			}
			lst = x;
		}
		if(edge[i][0].size() && edge[i][1].size())
		{
			dsu.merge(edge[i][0][0], edge[i][1][0] + n);
			dsu.merge(edge[i][0][0] + n, edge[i][1][0]);
		}
	}
	for(int i = 1; i <= n; ++i) if(dsu.find(i) == dsu.find(i + n)) quit();
	for(int i = 1; i <= n; ++i)
	{
		for(int x : edge[i][0]) get(i, x, 0);
		for(int x : edge[i][1]) get(i, x, 1);
	}
	for(int i = 1; i <= n; ++i) cout << res[i]; cout << '\n';
	
	debug();
	
	return 0;
}
/*

*/
```

---

## 作者：封禁用户 (赞：0)

AtCoder 是精通诈骗的。

为防止还有人没有吃透题目，这里描述一下题面：

> 有 $N$ 个村民，每个村民是诚实者或者谎言者。有 $M$ 条指认关系：第 $i$ 条关系是第 $u_i$ 个村民说第 $v_i$ 个村民是诚实者/谎言者（$w_i=0$ 说明是诚实者，$w_i=1$ 是谎言者）。
>
> 正常情况下诚实者只说实话，谎言者只说谎话，但是有些村民是**混沌**的。一个混沌的村民永远表现出于自己的身份相反的特点（诚实者说谎话，谎言者说实话）。
>
> 请问是否存在一个混沌状态，使得上述 $M$ 条关系均符合上述规则。如果存在，输出任意一个。

令你非常疑惑的一点是：如果你确定了所有村民都不是混沌的，那么很明显这个东西可以使用任何搜索方式去分配每个人的身份关系，或者确认无解。

但是，现在可能有村民是混沌的。我们假设第 $i$ 个村民——如果是诚实者，则记 $c_i=0$，否则记 $c_i=1$；如果是混沌的，记 $m_i=1$，否则记 $m_i=0$。那么第 $i$ 条关系满足：

$$c_{u_i}\oplus m_{u_i}\oplus c_{v_i}=w_i$$

这个 $m_{u_i}$ 太碍事了，一眼消不掉。

正在你仰望星空的时候，你突然找到了两个 $u$ 相同的 $i,j$。你把两个式子异或起来，突然发现：

$$c_{v_i}\oplus c_{v_j}=w_i\oplus w_j$$

$c_{u_i}$ 连同碍事的 $m_{u_i}$，全部被消掉了！

接着，你想到——你仅需把所有指认关系按照 $u$ 值扔到 $N$ 个 vector 中，然后将所有关系式异或上第一个/上一个式子即可！接着，得到两个 $c$ 值的异或关系后，我们可以把它们建成一张图去深搜，或者为了赶时间，直接并查集，去检验这些关系是否矛盾。

最终我们通过上述方式给每个村民分配了一个身份。我们再遍历这些村民自己的发言来确定自己可否是混沌的即可。

深搜做法时间复杂度 $O(N+M)$。并查集时间复杂度 $O(N\alpha(N)+M)$。这里作者为了赶时间写了个 $O(N\log N+M)$ 的路径压缩并查集。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,sett[200005],c[200005];bool tag[200005],ans[200005];
vector<pair<int,bool> >mp[200005];

int Find(int xx){
	if(sett[xx]==xx)return xx;
	int ret=Find(sett[xx]);tag[xx]^=tag[sett[xx]];
	return sett[xx]=ret;
}

int main(){
	cin>>n>>m;
	while(m--){
		int xx,yy;bool zz;cin>>xx>>yy>>zz;
		mp[xx].push_back(make_pair(yy,zz));
	}
	for(int i=1;i<=n;i++){
		sett[i]=i;c[i]=i;
	}
	for(int i=1;i<=n;i++){
		pair<int,bool>lst=make_pair(0,0);
		for(auto uu:mp[i]){
			if(lst.first!=0){
				int fa=Find(lst.first),fb=Find(uu.first);
				if(fa==fb){
					if(tag[lst.first]^tag[uu.first]^lst.second^uu.second){
						cout<<-1;return 0;
					}
					continue;
				}
				sett[fa]=fb;tag[fa]=tag[lst.first]^tag[uu.first]^lst.second^uu.second;
			}
			lst=uu;
		}
	}
	for(int i=1;i<=n;i++){
		bool satis=0;
		for(auto uu:mp[i]){
			int fa=Find(i),fb=Find(uu.first);
			if(fa==fb){
				if(tag[i]^tag[uu.first]^uu.second){
					satis=1;break;
				}
				continue;
			}
			sett[fa]=fb;tag[fa]=tag[i]^tag[uu.first]^uu.second;
		}
		cout<<satis;
	}
	return 0;
}
```

---

