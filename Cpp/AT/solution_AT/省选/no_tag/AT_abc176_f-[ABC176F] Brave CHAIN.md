# [ABC176F] Brave CHAIN

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc176/tasks/abc176_f

$ 1 $ 以上 $ N $ 以下の整数のうち一つが書かれた $ 3N $ 枚のカードが左右一列に並んでいます。 左から $ i $ 番目のカードに書かれた整数は $ A_i $ です。

以下の操作を $ N-1 $ 回繰り返します。

- 左から $ 5 $ 枚のカードを好きな順に並び替える。その後、左から $ 3 $ 枚のカードを取り除く。このとき、その $ 3 $ 枚のカードに書かれた整数がすべて等しければ $ 1 $ 点を得る。

$ N-1 $ 回の操作の後、残った $ 3 $ 枚のカードに書かれた整数がすべて等しければ追加で $ 1 $ 点を得ます。

得られる得点の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2000 $
- $ 1\ \leq\ A_i\ \leq\ N $

### Sample Explanation 1

左から $ 5 $ 枚のカードを並べ替え、カードに書かれた整数が左から順に $ 2\ 2\ 2\ 1\ 1\ 1 $ となるようにします。 左から $ 3 $ 枚のカードを取り除き、このときこれら $ 3 $ 枚のカードに書かれた整数はすべて $ 2 $ で等しいので $ 1 $ 点を得ます。 カードに書かれた整数は左から順に $ 1\ 1\ 1 $ となります。 残った $ 3 $ 枚のカードに書かれた整数はすべて $ 1 $ でこれも等しいので $ 1 $ 点を得ます。 合計得点は $ 2 $ 点となり、これが最高です。

## 样例 #1

### 输入

```
2
1 2 1 2 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
3
1 1 2 2 3 3 3 2 1```

### 输出

```
1```

## 样例 #3

### 输入

```
3
1 1 2 2 2 3 3 3 1```

### 输出

```
3```

# 题解

## 作者：Rain_javalearner (赞：20)

日志：2023/8/6 一修，删除大 $\mathcal{O}$ 时间复杂度表示中的常数。

---

苏格拉底说，**有系统的问与答**是获取知识的最好办法。我说，本题解就采取这样的方式。

# 0x00

题意清楚，故不赘述。

# 0x01 正传

问：为什么使用 $\text{dp}$ 算法？

答：题目询问最大分数，通常非贪心即 $\text{dp}$。这样的情况下，我们仔细考虑贪心策略，如果难以找到保证正确性的贪心策略，就应该往 $\text{dp}$ 的方向思考了。本题就是这种情乱。

问：$\text{dp}$ 状态怎么定义？

答：设 $dp_{i,t_1,t_2}$ 表示考虑到第 $i$ 张牌，上一轮剩下 $t_1, t_2$，准备与 $card_i, card_{i+1},card_{i+2}$ 一起凑成新的 $5$ 张牌的方案数。空间复杂度 $\Theta (n^3)$，可以用滚动数组优化成 $\Theta (n^2)$。

问：为什么这样定义？

答：考虑为什么使用 $\text{dp}$ 算法，而非贪心策略。一个决策点上，有三张牌是可以确定的，但是前两张牌会被上一个决策点的策略所影响。所以需要记录上一个决策点的所有决策，才能正确地策略当下决策点，而这就是 $\text{dp}$ 算法。所以 $\text{dp}$ 的状态只需要保证达成当下决策点做决策的条件即可，在本题中就是如上所示。

问：如何转移？

答：因为可以确定五张决策牌中的三张，所以枚举转移的复杂度是 $\mathcal{O}(n^3)$。但是很快发现有相当一部分的枚举是毫无用处的，让我们来分类讨论看一看。

设：已知的三张牌为 $p,q,r$。

如果**该轮转移有加分**：

1. $p=q=r$

此时应当直接丢弃 $p,q,r$ 并获得一分，系贪心策略，$\mathcal{O}(1)$。

2. $p=q$ 或 $p=r$ 或 $q=r$，即 $a,a,b$ 的状态

此时三张牌有两张牌相等，就有两种得分的可能：

$(a,c\; |\; a,a,b)$ 或 $(b,b\; |\; a,a,b)$ $\; \; \; \; c\in [1,n]$

我们分别转移，前者枚举 $c$ 可以做到 $\mathcal{O}(n)$；后者 $\mathcal{O}(1)$ 转移。

3. $p \neq q \neq r$

此时有三种得分的可能：

$(p,p\; |\; p,q,r)$ 或 $(q,q\; |\; p,q,r)$ 或 $(r,r\; |\; p,q,r)$

我们依然分别转移，均可以做到 $\mathcal{O}(1)$。

得分的三种情况我们枚举完惹，那么**不得分**的呢？

1. 丢弃 $p,q,r$ 并不得分

整个 $dp$ 数组并不改变，因为我们是滚动数组，所以不做任何操作。

2. 丢弃三个中的任意两个

情况是 $(c,d\; |\; p,q,r)$，我们可以枚举 $c,d$ 找到 $\max\{dp_{last,c,d}\}$ 并转移到 $dp_{now,c,p/q/r}$ 复杂度 $\mathcal{O}(n^2)$；但是我们可以通过维护 $c$ 的行列最大值来做到 $\mathcal{O}(n)$。

3. 丢弃三个中的任意一个

情况依然是 $(c,d\; |\; p,q,r)$，这次我们要转移到 $dp_{now,\{p,q\}/\{p,r\}/\{r,q\}}$，可以维护一个整数表示整个 $dp$ 数组的最大值，做到 $\mathcal{O}(1)$ 转移。

现在并没有其他情况了，综合复杂度是 $\mathcal{O}(n\times n)$，比我们预期的小了很多，这也启发我们 $\text{dp}$ 的复杂度通常只与转移状态中的枚举有关系，转移状态外的枚举通常可以用预处理来优化。

# 0x03 Code

$card[]$ 存储卡牌

$e$ 表示 $dp$ 数组最大值

$c[]$ 维护行列最大值

$\text{vector} \; \; vec$ 是滚动的数组，用以优化 $\mathcal{O}(n\times n^2)$ 的遍历更新。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef long long i64;

namespace code_namespace {
    int n, card[6003];
    int c[2003], dp[2003][2003];
    int e, change;
    struct _{int x, y, z;};
    vector<_> vec;

    int main() {
        scanf("%d", &n);
        for(int i = 1 ; i<= 3*n ; i++)
            scanf("%d", card + i);
        memset(dp, 0xcf, sizeof dp);
        memset(c, 0xcf, sizeof c);
        // Assign minimum value (negative)
        dp[card[1]][card[2]] = dp[card[2]][card[1]] = 0;
        e = change = c[card[1]] = c[card[2]] = 0;

        for(int i = 3 ; i < 3*n ; i += 3) {
            vec.clear();
            int p = card[i], q = card[i+1], r = card[i+2];
            // If searching for points
                if(p == q && q == r) {
                    change++;
                    continue;
                } else if(p == q || p == r || q == r) {
                    int res = p ^ q ^ r;
                    int x = (p+q+r-res) / 2;
                    for(int tmp1 = 1 ; tmp1 <= n ; tmp1++) {
                        vec.push_back({res, tmp1, dp[x][tmp1]+1});
                    }
                    vec.push_back({x, x, dp[res][res]+1});
                } else {
                    vec.push_back({p, q, dp[r][r]+1});
                    vec.push_back({p, r, dp[q][q]+1});
                    vec.push_back({q, r, dp[p][p]+1});
                }
            
            // else (no points)
                vec.push_back({p, q, e});
                vec.push_back({p, r, e});
                vec.push_back({q, r, e});
                // if throw out 1 of 3

                for(int tmp1 = 1 ; tmp1 <= n ; tmp1++) {
                    vec.push_back({p, tmp1, c[tmp1]});
                    vec.push_back({q, tmp1, c[tmp1]});
                    vec.push_back({r, tmp1, c[tmp1]});
                }
                // else throw out 2 of 3

                // else (throw out 3 of 3) -> We do nothing
            
            // Update(use vector)
            for(auto tmp : vec) {
                dp[tmp.x][tmp.y] = dp[tmp.y][tmp.x] = max(dp[tmp.x][tmp.y], tmp.z);
                e = max(e, dp[tmp.x][tmp.y]);
                c[tmp.x] = max(c[tmp.x], dp[tmp.x][tmp.y]);
                c[tmp.y] = max(c[tmp.y], dp[tmp.x][tmp.y]);
            }
        }
        e = max(e, dp[card[3*n]][card[3*n]] + 1);
        printf("%d\n", e + change);
        // system("pause");
        return 0;
    }
}

int main() {
    return code_namespace::main();
}
```


---

## 作者：cxm1024 (赞：8)

[更好的观看体验](https://cxm1024.github.io/2023/01/19/abc176f-brave-chain-ti-jie/)

> 题意：有 $3n$ 张卡片，每张有一个 $1\sim n$ 的数字。每次可以将最左边的 $5$ 张卡片任意排列，删掉前 $3$ 张，如果这三张数字相等则得一分；最后剩下的三张如果相等也的一分。求最大总得分。

模拟一下这个过程可以发现，相当于你有两张“手牌”，每次新加入三张，你从五张中扔掉三张，还是剩下两张。于是可以考虑一个 DP 状态：$f[i][x][y]$ 表示进行 $i$ 次操作，操作后手上剩下的牌为 $x,y$ 的最大得分。转移也不难，枚举下一次新加进来三张后如何选即可。时空复杂度 $O(n^3)$。

仔细想一下，会发现对于相同的 $x,y$，$f[i][x][y]$ 随着 $i$ 的增加永远不会减少，因为最差的情况无非是：每新加三张就把那三张扔掉，永远让 $x,y$ 为手牌，得分永远不会减少。这启发我们考虑 $f[i]\to f[i+1]$ 的变化。

首先，新加入的三张牌 $a,b,c$ 与 $x,y$ 是多少无关，只与当前考虑到哪张牌有关。如果 $a=b=c$，不管 $x,y$ 是多少，一定直接把它扔掉，贪心地立刻得分。正确性容易证明，这里不赘述。接下来考虑不全相等的情况。

如果用上面说的那样“消极”做法，新加入三张牌就扔掉，$f[i+1][x][y]=f[i][x][y]$，这是下限，可以直接从上一维过来，所以只需要考虑哪些 $x,y$ 会发生改变即可。与消极做法相反，要想改变一定要让操作后手牌中有新牌。我们先考虑如何扔牌能造成贡献，再考虑不能造成贡献的情况。

假如三张牌中有两张相等（这里假设是 $a=b$），那么只要 $x,y$ 中有一个与 $a,b$ 相等的牌即可凑起来扔掉，而手牌中的另一张牌与 $c$ 组成新的手牌。此时，我们可以枚举那个“另一张牌”，假设为 $j$，那么有 $f[i][a][j]+1\to f[i+1][j][c]$（这里暂时不考虑两维的手牌的顺序，实现的时候将 $j,c$ 和 $c,j$ 都更改即可）。接下来，考虑两张手牌相等，与另一张相等的新牌配对，可以直接枚举与哪张新牌相等，假设为 $a$，则有 $f[i][a][a]+1\to f[i+1][b][c]$。于是，造成新贡献的考虑完成。

接着考虑不造成新贡献的转移：由于前面说过，新的手牌中必须留新牌，我们可以枚举留哪张新牌，再枚举另一张牌是什么。假设留的新牌是 $a$，另一张牌是 $j$，那么如果 $j=b$ 或 $j=c$，即新的手牌纯用新牌组成，此时旧手牌 $x,y$ 无论是什么都可行。可以维护所有 DP 值的 $\max$。如果 $j$ 不和 $b,c$ 相等，则旧手牌必须有 $j$，我们维护一个数组 $g[j]$ 表示手牌包含 $j$ 的所有 DP 值的 $\max$ 即可。

以上两种转移的次数都是 $O(n)$ 的，接下来说回“继承”：加入三张牌直接扔掉，手牌不变。如果直接枚举 $x,y$，更新 $f[i+1][x][y]=f[i][x][y]$ 的话，复杂度为 $n^2$，所以这里我们偷个懒，省掉第一维 $i$，直接在旧的 $f$ 数组上做修改即可。注意修改必须考虑完所有转移后整体修改，因为原来的转移是 $f[i][x][y]\to f[i+1][x'][y']$，而不能 $f[i+1][x][y]\to f[i+1][x'][y']$。这可以通过 vector 存储 DP 转移实现。具体可以看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
void chkmax(int &a,int b) {a=a>b?a:b;}
void chkmin(int &a,int b) {a=a<b?a:b;}
int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) f=(ch=='-'?-1:f),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return x*f;
}
int a[6010],f[2010][2010],g[2010],mx;
signed main() {
	int n=read(),m=n*3,cnt=0;
	for(int i=1;i<=m;i++)
		a[i]=read();
	memset(f,-0x3f,sizeof(f));
	memset(g,-0x3f,sizeof(g));
	f[a[1]][a[2]]=f[a[2]][a[1]]=0;
	g[a[1]]=g[a[2]]=0,mx=0;
	for(int i=3;i<m;i+=3) {
		array<int,3> p={a[i],a[i+1],a[i+2]};
		sort(p.begin(),p.end());
		if(p[0]==p[2]) {cnt++;continue;}
		vector<pair<pair<int,int>,int> > ch;
		auto add=[&](int x,int y,int val) {
			ch.push_back({{x,y},val});
			ch.push_back({{y,x},val});
		};
		if(p[1]==p[2]) swap(p[0],p[2]);
		if(p[0]==p[1]) {
			for(int i=1;i<=n;i++)
				add(i,p[2],f[i][p[0]]+1);
		}
		for(int i=0;i<3;i++) {
			vector<int> q;
			for(int j=0;j<3;j++)
				if(i!=j) q.push_back(p[j]);
			add(q[0],q[1],f[p[i]][p[i]]+1);
		}
		for(int i=0;i<3;i++) {
			for(int j=1;j<=n;j++) {
				bool flag=0;
				for(int k=0;k<3;k++)
					if(i!=k&&j==p[k]) flag=1;
				if(flag) add(p[i],j,mx);
				else add(p[i],j,g[j]);
			}
		}
		for(auto [x,val]:ch) {
			chkmax(f[x.first][x.second],val);
			chkmax(g[x.first],val),chkmax(g[x.second],val);
			chkmax(mx,val);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			chkmax(ans,f[i][j]+(i==a[m]&&j==a[m]));
	printf("%d\n",ans+cnt);
	return 0;
}
```

---

## 作者：cosf (赞：7)

考虑一个朴素的 $dp$。

令 $dp_{i, a, b}$ 表示处理到第 $3i - 2$ 位，其中第一位为 $a$，第二位为 $b$ 的最大答案。初始时 $dp_{1, v_1, v_2} = 0$，其他为 $-\infty$。

转移时，我们需要第三到五的数 $c, d, e$，它们当前的排列方式是：$a, b, c, d, e, \dots$。

显然，这个式子与 $a, b$ 顺序无关，即总有 $dp_{i, a, b} = dp_{i, b, a}$。

则我们可以有三个式子，其最左侧的 $=$ 都是取 $\max$。

1. $dp_{i, c, d} = dp_{i - 1, a, b} + [a = b = e]$。$dp_{i, d, e}$ 与 $dp_{i, e, c}$ 同理。
2. $dp_{i, a, b} = dp_{i - 1, a, b} + [c = d = e]$。
3. $dp_{i, a, e} = dp_{i - 1, a, b} + [b = c = d]$。$dp_{i, a, c}, dp_{i, a, d}, dp_{i, b, c}, dp_{i, b, d}, dp_{i, b, e}$ 同理。

则答案为 $dp_{n, a, b} + [a = b = v_{3n}]$。

根据 $dp_{i, a, b}$ 转移到的状态只有 $O(5^2)$ 种，这种朴素递推的时间复杂度为 $O(n^3)$，当然过不了。

---

这个式子可以优化。

对于第一个式子，如果我们想要 $[a = b = e] = 1$，则 $a, b$ 的值唯一确定，而 $c, d$ 的值也是确定的，故此种转移的复杂度是 $O(1)$ 的。如果不需要 $[a = b = e] = 1$，则 $a, b$ 可以为任意值，直接取全局 $\max$ 即可。

对于第二个式子，因为 $[c = d = e]$ 的值和 $a, b$ 无关，所以直接全局加法即可。

对于第三个式子，如果 $[b = c = d] = 1$，则需要修改的 $dp$ 值只有 $dp_{i, a, e} = dp_{i, a, c} + 1$，只有一个变量在改变，复杂度 $O(n)$。如果不需 $[b = c = d] = 1$，则右侧相当于求 $dp_{i - 1, a, b}$ 在 $b$ 变化的 $\max$，因此维护一下行的 $\max$ 即可，时间复杂度仍为 $O(n)$。

这样对于一个 $i$ 我们所需的复杂度为 $O(n)$，则总复杂度为 $O(n^2)$，可以通过。

具体实现可以开一个 `queue` 或者 `stack` 来保存每次的操作，等每个操作都处理完再统一复制到原来的 $dp$ 数组上。这样可以节省空间，也十分好写。

```cpp
#include <iostream>
#include <cstring>
#include <queue>
#include <array>
using namespace std;

#define MAXN 3005

using tii = array<int, 3>;

int dp[MAXN][MAXN], ps = 0;

int n;

int v[MAXN * 3];

int main()
{
    cin >> n;
    for (int i = 1; i <= 3 * n; i++)
    {
        cin >> v[i];
    }
    memset(dp, -0x3f, sizeof(dp));
    dp[v[1]][v[2]] = dp[v[2]][v[1]] = // dp[i][a][0] 表示第 a 行的 max
    dp[v[1]][0] = dp[v[2]][0] = // dp[i][0][0] 表示全局 max
    dp[0][0] = 0;
    queue<tii> q;
    for (int i = 2; i <= n; i++)
    {
        int c = v[i * 3 - 3], d = v[i * 3 - 2], e = v[i * 3 - 1], cp = 0;
        // dp[i][c][d]
        q.push({c, d, dp[e][e] + 1});
        q.push({c, d, dp[0][0]});
        q.push({d, e, dp[c][c] + 1});
        q.push({d, e, dp[0][0]});
        q.push({e, c, dp[d][d] + 1});
        q.push({e, c, dp[0][0]});
        // dp[i][a][b]
        if (c == d && d == e)
        {
            cp++;
            ps++;
        }
        // dp[i][a][e]
        for (int a = 1; a <= n; a++)
        {
            if (c == d)
            {
                q.push({a, e, dp[a][c] + 1});
            }
            q.push({a, e, dp[a][0]});
            if (d == e)
            {
                q.push({a, c, dp[a][d] + 1});
            }
            q.push({a, c, dp[a][0]});
            if (e == c)
            {
                q.push({a, d, dp[a][e] + 1});
            }
            q.push({a, d, dp[a][0]});
        }
        // postprocessing
        while (!q.empty())
        {
            auto [a, b, w] = q.front();
            q.pop();
            w -= cp; // 不减就相当于全局加之后再转移，答案会错。
            dp[a][b] = dp[b][a] = max(dp[a][b], w);
            dp[a][0] = max(dp[a][0], w);
            dp[b][0] = max(dp[b][0], w);
            dp[0][0] = max(dp[0][0], w);
        }
    }
    int res = 0;
    for (int a = 1; a <= n; a++)
    {
        for (int b = a; b <= n; b++)
        {
            res = max(res, dp[a][b] + (a == b && a == v[3 * n]));
        }
    }
    cout << res + ps << endl;
    return 0;
}

```

---

## 作者：0xyz (赞：7)

感觉这一题不是很难。也许是我运气好，写完就过了。所以来一发自己想出来的，与现有题解、官方题解不同的题解（其实代码短一些）。

容易知道，这就相当于一开始拿了最前面 $2$ 张，然后每一次往手里拿 $3$ 张，任意去掉 $3$ 张并根据去掉的 $3$ 张算分。可以知道，无论前面怎么操作，第 $i$ 次拿到的三张一定是 $a_{3i},a_{3i+1},a_{3i+2}$。所以可以依据第 $i$ 次后手中的牌来设计状态进行 dp。我们令 $f_{i,x,y}$ 代表第 $i$ 次操作后，手里拿着 $x,y$ 两张牌，此时最多能获得多少分。时间、空间复杂度 $O(n^3)$。这样很明显会炸。

然后我们来考虑一下如何优化。我们使用滚动数组优化，令 $f_{x,y}$ 代表当前的 dp 数组，令 $g_{x,y}$ 代表我们要推出来的 dp 数组。

那么我们考虑转移。对这一次我们新纳入的 $3$ 张牌进行讨论。注意到 dp 数组对称，所以我们只考虑一部分转移，如果有变量，我们把它放在前面。同时，维护一个 $c_x$ 代表第 $x$ 行/列最大值，$e$ 代表全局最大值。然后，对于同样位置上值不改变的量，我们不用去更新它。所以可以用一个 `vector` 来存储需要更新的位置，等这一轮所有格子处理完再统一更新 $f,c,e$。

① $p,p,p$。

由贪心可知，最优策略一定是立刻扔掉这 $3$ 张牌并且立刻获得 $1$ 分。所以这时直接让答案 $+1$。时间复杂度 $O(1)$。

② $p,p,q$。

考虑从这 $3$ 张牌里留下哪些牌。

1. 我们可以什么都不留，直接扔掉这 $3$ 张牌。这时 $\forall x,y\in\{1,2,…,n\},g_{x,y}\leftarrow f_{x,y}$。由于值和位置都没有变，不用操作。
2. 我们可以只留下一个 $q$，有时候可以扔掉 $3$ 个 $p$。也就是 $\forall x\in\{1,2,…,n\},x\not\in\{p,q\},g_{x,q}\leftarrow\max(c_x,f_{x,p}+1)$。时间复杂度 $O(n)$。 
3. 我们可以只留下一个 $p$。也就是 $\forall x\in\{1,2,…,n\},x\not\in\{p,q\},g_{x,p}\leftarrow c_x$。时间复杂度 $O(n)$。 
4. 我们可以留下 $p,p$。$g_{p,p}\leftarrow\max(e,f_{q,q}+1)$。时间复杂度 $O(1)$。 
5. 我们可以留下 $p,q$。$g_{p,q}\leftarrow e$。时间复杂度 $O(1)$。 

③ $p,q,r$。

考虑从这 $3$ 张牌里留下哪些牌。注意这里 $p,q,r$ 对称。

1. 什么都不留。同样不需要操作。
2. 只留下 $1$ 个，假设是 $p$。由于一定要扔掉 $q\ne r$，所以一定不得分。也就是 $\forall x\in\{1,2,…,n\},x\not\in\{p,q,r\},g_{x,p}\leftarrow c_x$。时间复杂度 $O(n)$。
3. 留下 $2$ 个，假设是 $p,q$。一定要扔掉 $r$。也就是 $g_{p,q}\leftarrow\max(e,f_{r,r}+1)$。时间复杂度 $O(1)$。

我们讨论完了，初始化 $f_{a_1,a_2}=f_{a_2,a_1}=0$，其余 $f$ 为 $-inf$，对应 $c_{a_1}=c_{a_2}=0$，其余 $c$ 为 $-inf$，$e=0$。

结果就是 $\max(e,f_{a_{3n},a_{3n}}+1)+ans$。

所以我们发现一次转移可以在 $O(n)$ 的时间内完成。总的时间、空间复杂度都是 $O(n^2)$。

[AC 记录](https://atcoder.jp/contests/abc176/submissions/42105754)。

```cpp
#include<bits/stdc++.h>
#define A(x,y,z) v.push_back({x,y,z});
#define T(j) for(int j=0;j<3;j++)
#define N(x) for(int x=1;x<=n;x++)
using namespace std;
int n,a[6010],b[3],f[2010][2010],c[2010],e,ans=0;
struct _{int x,y,z;};
vector<_>v;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=3*n;i++)cin>>a[i];
	memset(f,0xcf,sizeof(f));memset(c,0xcf,sizeof(c));
	f[a[1]][a[2]]=f[a[2]][a[1]]=c[a[1]]=c[a[2]]=e=0;
	for(int i=3;i<3*n;i+=3){
		T(j)b[j]=a[i+j];
		sort(b,b+3);v.clear();
		if(b[0]==b[1]&&b[1]==b[2]){ans++;continue;}
		if(b[0]==b[1]||b[1]==b[2]){
			if(b[1]==b[2])swap(b[0],b[2]);
			N(x)A(x,b[2],max(c[x],f[x][b[0]]+1));
			N(x)A(x,b[0],c[x]);
			A(b[0],b[0],max(e,f[b[2]][b[2]]+1));
			A(b[0],b[2],e);
		}else{
			T(j)N(x)A(x,b[j],c[x]);
			T(j)A(b[j],b[(j+2)%3],max(e,f[b[(j+1)%3]][b[(j+1)%3]]+1));
		}
		for(int j=0;j<v.size();j++){
			c[v[j].x]=max(c[v[j].x],f[v[j].x][v[j].y]=max(f[v[j].x][v[j].y],v[j].z));
			if(v[j].x!=v[j].y)c[v[j].y]=max(c[v[j].y],f[v[j].y][v[j].x]=f[v[j].x][v[j].y]);
			e=max(e,f[v[j].x][v[j].y]);
		}
	}
	cout<<max(e,f[a[3*n]][a[3*n]]+1)+ans<<'\n';
	return 0;
}
```

---

## 作者：Loser_King (赞：6)

古早六题场 ABC 补完计划 ~ -6th。

题外话：打这个题所在的场的时候我（在当时相对来说）很快过掉了前五个题，达到了人生第一个 2k perf，然后 AT rating 上了 1200。做到这个题以后，我罚坐了 1h 不会做，然后等了两年能看懂的题解，过了三年还是不会做。三年一个月后的今天翻到这个题，突然就看懂了，泪目。（甚至感觉这个题可能偏高了点）

这个题两年里一直没什么人补，然后现在看发现被学弟偷过了。

看完题以后发现每次扔掉五张卡里的三张，也就是说每次只需要记录剩下的两张卡就可以了。下面状态记录 $f_{c,i,j}$ 表示第 $c$ 次操作后剩下的两张卡 $i,j$ 最大的贡献次数。

显然我们需要进行 $n$ 轮转移不能省掉，于是只能把每轮转移的时间复杂度降为 $O(n)$。朴素的转移枚举 $i,j$ 和新加的卡 $x,y,z$ 的顺序，每轮 $O(n^2)$ 而且常数巨大。但是因为这题是可做题，我们考虑到每轮有效转移次数显然不多，具体的：

- 如果原来两张卡都留下，那么自 $f_{c-1}$ 直接继承状态，若新加的三张卡相同则全局加一。

- 如果原来两张卡都丢掉，此时当且仅当 $i=j$ 且 $x,y,z$ 中存在数等于 $i$ 时会增加贡献，做 $3$ 次转移即可。

- 如果原来两张卡留下一张，此时当且仅当 $i=j$ 且 $x,y,z$ 中存在两个数（不妨令其为）$x=y$ 且 $x=i$ 时会增加贡献，做 $3n$ 次转移即可。

因为加里敦摆烂 OIer 不会遇到超级答辩题，所以我们丢掉状态中的 $c$，引入 $x=0$ 或 $y=0$ 表示我们不在乎这张卡具体是什么。（注意引入状态后一次转移实际上要做七次，即加上 $x$ 或 $y$ 被忽略的状态）

注意到上面所述，除了这 $3n+3$ 种转移可能增加贡献以外，其他的卡具体是什么不重要，所以如此可以巨大简化转移。总复杂度 $O(n^2)$。

轻度压行代码，大概不压行长度也不超过 1k。常数略大。

```cpp
// by nisansansp (psz2007)
#include<bits/stdc++.h>
#define upd(i,j,w) (f[i][j]<(w)?f[i][j]=(w):0)
using namespace std;
int const N=2010;
int n,s,a[N*3],f[N][N];
vector<array<int,3> >t;
void ins(int i,int j,int k){
	upd(i,j,k),upd(j,i,k),upd(i,0,k),upd(0,i,k);
	upd(j,0,k),upd(0,j,k),upd(0,0,k);
}
void work(int x,int y,int z){
	for(int i=1;i<=n;i++)
		t.push_back({i,x,max(f[i][0],y^z?-N:f[i][y]+1)});
	t.push_back({x,y,max(f[0][0],f[z][z]+1)});
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n*3;i++)
		cin>>a[i];
	memset(f,0xc0,sizeof f);
	ins(a[1],a[2],0);
	for(int i=1;i<n;i++){
		int x=a[i*3],y=a[i*3+1],z=a[i*3+2];
		if(x==y&&y==z){
			s++;
			continue;
		}
		t.clear(),work(x,y,z),work(y,z,x),work(z,x,y);
		for(auto[i,j,k]:t)
			ins(i,j,k);
	}
	cout<<s+max(f[0][0],f[a[n*3]][a[n*3]]+1)<<"\n";
}
```

---

## 作者：shenxinge (赞：6)

题意很简单，这里就不详细叙述了。

我们发现由于每次只拿五个 ， 消掉三个 ， 就相当于每次手牌只有两个 ， 每一轮给三张牌让你消 ， 如果你手牌里有和这三个组成的牌中有三张一样颜色就可以消掉 。

很显然的是由于每一轮给的三个数固定 ， 我只需要用两维分别表示 $x$ 和 $y$ 就可以了 ， 那么显然有 $dp_{i,j,k}$ 代表第 $i$ 轮 ， 手牌有两种颜色一种是 $j$ ， 一种是 $k$ ， 直接枚举 $j,k$ 对于当前三张牌 $A,B,C$ , 直接更新 ，这样的做法是 $O(n^3)$ 的 。

考虑到我们每次更改的东西其实很少 ， 只有少部分的 $j,k$ 对于当前 $A,B,C$ 会进行更新 , 大多数都是继承。

具体而言就是考虑如果消掉的是 $A,B,C$ ， 首先如果说存在 $A=B=C$ 那么显然直接消掉肯定不劣 ， 可以直接统计 。

如果有两个相等的情况 ， 就比如说 $A=B$ 的情况 , 需要枚举一个 $x$ 那么就相当于是 :

$$dp[x][C]=max_{x=1}^n dp'[x][A]+1$$

如果把 $x,y$ 中的一个消掉和 $A,B,C$ 中的两个消掉(假设消掉 $A,B$ , 那么就是 :

$$dp[x][C]=max_{x=1}^n dp[x][y]$$

统计一下 $s[x]=max_{x=1}^n dp[x][y]$ 就可以了 。

剩下的就是将 $x,y$ 和 $A,B,C$ 中的一个消掉 , 如果是当前手上有 $x,y=A$ 那么是可以消掉的 ， 其他的都不会消掉 ， 直接继承上一轮的答案 。

这样每次更新的点的个数是 $O(n)$ 的 , 时间复杂度 $O(n^2)$

可能代码更好理解一点 :

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int maxn=2010,inf=2e9;
inline int read()
{
	int x=0,f=1;char c;
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-f;
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	return x*f;
}
int n,buc[maxn*3],cnt;
bool eq[maxn];int b[4],Max;
int f[2][maxn][maxn],s[maxn];
#define fir first
#define sec second
inline int chkmx(int &a,int b){if(a<b) a=b;return a;}
inline int chkmn(int &a,int b){if(a>b) a=b;return a;}
signed main()
{
	n=read();
	For(i,1,n*3)
		buc[i]=read();
	For(i,1,n-1)
	{
		int p=3+(i-1)*3;
		if(buc[p]==buc[p+1]&&buc[p+1]==buc[p+2])
			cnt++,eq[i]=true;
	}
	int now=1,lst=0;
	For(x,1,n) For(y,1,n)
		f[now][x][y]=s[x]=-inf;
	f[now][buc[1]][buc[2]]=s[buc[1]]=
	f[now][buc[2]][buc[1]]=s[buc[2]]=0;
	memcpy(f[lst],f[now],sizeof f[lst]);
	For(i,1,n-1) if(!eq[i])
	{
		now^=1,lst^=1;
		int p=3+(i-1)*3;vector<pair<int,int> > vec;
//		printf("%d\n",p);
		function<void(int,int,int)> push=[&](int x,int y,int v)
			{f[now][x][y]=chkmx(f[now][y][x],v),vec.push_back({x,y});}; 
		b[1]=buc[p],b[2]=buc[p+1],b[3]=buc[p+2];
		push(b[1],b[2],max(Max,f[lst][b[3]][b[3]]+1));
		push(b[2],b[3],max(Max,f[lst][b[1]][b[1]]+1));
		push(b[1],b[3],max(Max,f[lst][b[2]][b[2]]+1));
		sort(b+1,b+1+3);
		int A=b[1],B=b[2],C=b[3];
		if(B==C) swap(A,C);
//		printf("A: %d B: %d C: %d\n",A,B,C);
		For(x,1,n) if(~s[x])
			push(x,A,s[x]),
			push(x,B,s[x]),
			push(x,C,s[x]);
		if(A==B) For(x,1,n) if(~f[lst][A][x])
			push(x,C,f[lst][A][x]+1);
		for(auto E:vec)
		{
			int x,y;tie(x,y)=E;
			Max=max(Max,f[now][x][y]);
			f[lst][x][y]=f[lst][y][x]=f[now][x][y];
			chkmx(s[x],f[now][x][y]),
			chkmx(s[y],f[now][x][y]);
		}
	}
//	printf("Max: %d cnt: %d\n",Max,cnt);
	printf("%d\n",max(Max,f[now][buc[3*n]][buc[3*n]]+1)+cnt);
	return 0;
}
```


---

## 作者：larsr (赞：2)

校内测试搬了这题，想出了一个和题解区做法都不一样的做法。

首先对序列 $a$ 分组，$a_1$ 和 $a_2$ 为一组，后面每三个一组，最后 $a_{3n}$ 自己为一组，总共 $n+1$ 组。考虑倒着 DP，$h_{i,j,k}$ 代表完成了前 $i$ 组剩下的两个数为 $j$ 和 $k$，继续完成剩下的组的最大分数（不包括前 $i$ 组产生的分数），这样就可以 $O(n^3)$ 完成。

考虑另外一个切入点，如果 $j$ 和 $k$ 其中一个不产生贡献，那么就可以只考虑一个，那么设 $g_{i,j}$ 代表完成了前 $i$ 组，剩下的一个数为 $j$，另一个数没用，完成剩下的组的最大分数。

继续考虑 $j$ 和 $k$ 都会产生贡献，所以在 $j$ 和 $k$ 贡献之前，它们不能被删掉，那么这个过程中删除的数确定了，预处理即可。

假设 $j$ 比 $k$ 先产生贡献，那么一定是后面两个和 $j$ 相同的数在同一个组别，不然 $k$ 无法产生贡献。如果后面和 $j$ 相同的两个数的组别不同，中间肯定要保留第一个和 $j$ 相同的数，那么就要删除 $k$，所以要在同一个组别。

考虑从一开始得到 $j$ 和 $k$ 时就设状态，然后就可以直接跳跃到 $j$ 被贡献的位置。由于是刚得到，那么其中一个数一定是第 $i$ 个组的（只有三个数），那么就可以 DP 了，当然还要特判 $j=k$ 的情况。设 $f_{i,j,k}$ 代表完成了前 $i$ 个组，剩下的两个数为 $j$ 和 $a_{3i-k}(1\le j\le3)$，完成剩下的组的最大分数。

把 $g_{i,j}$ 和 $f_{i,j,k}$ 结合起来，时间复杂度 $O(n^2)$。

```cpp
#include<cstdio>
#define N 6010
#define M 2010
using namespace std;
int n, a[N];
int f[M][M][4], g[M][M];
int fir[N][M], p[N];
void m(int &x, int y) { if(y > x)x = y; }
int noget(int s, int x)
{
	if(a[3 * s] != x)return 3;
	if(a[3 * s + 1] != x)return 2;
	return 1;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= 3 * n; i++)scanf("%d", a + i);
	for(int i = 3 * n; i; i--)
	{
		for(int j = 1; j <= n; j++)
			fir[i][j] = fir[i + 1][j];
		fir[i][a[i]] = i;
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= 3; j++)
			if(a[3 * n - j] == a[3 * n] && i == a[3 * n])
				f[n][i][j] = 1;
	for(int i = 1; i <= n; i++)
		if(a[3 * i] == a[3 * i + 1] && a[3 * i] == a[3 * i + 2])
			p[i] = 1;
	for(int i = 1; i <= n; i++)
		p[i] += p[i - 1];
	for(int s = n - 1; s; s--)
	{
		for(int i = 1; i <= n; i++)
		{
			if(fir[3 * s][i] / 3 == fir[fir[3 * s][i] + 1][i] / 3 && fir[3 * s][i] / 3 == s)
			{
				int k = noget(s, i);
				m(g[s][i], g[s + 1][a[3 * s + 3 - k]] + 1);
			}
			if(a[3 * s] == a[3 * s + 1] && a[3 * s] == a[3 * s + 2])m(g[s][i], g[s + 1][i] + 1);
			m(g[s][i], f[s + 1][a[3 * s]][1]);
			m(g[s][i], f[s + 1][a[3 * s + 1]][1]);
			m(g[s][i], f[s + 1][a[3 * s]][2]);
			for(int k = 1; k <= 3; k++) m(g[s][i], f[s + 1][i][k]);
		}
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= 3; j++)
			{
				int num = a[3 * s - j], x, y;
				m(f[s][i][j], g[s][i]);
				m(f[s][i][j], g[s][num]);
				if(num == i)
				{
					int x = fir[3 * s][i] / 3;
					if(x)
					{
						if(a[3 * x] == num) m(f[s][i][j], f[x + 1][a[3 * x + 1]][1] + 1 + p[x - 1] - p[s - 1]);
						else if(a[3 * x + 1] == num) m(f[s][i][j], f[x + 1][a[3 * x]][1] + 1 + p[x - 1] - p[s - 1]);
						else m(f[s][i][j], f[x + 1][a[3 * x]][2] + 1 + p[x - 1] - p[s - 1]);
					}
				}
				if(fir[3 * s][i] / 3 == fir[fir[3 * s][i] + 1][i] / 3)x = fir[3 * s][i] / 3;
				else x = 1e9;
				if(fir[3 * s][num] / 3 == fir[fir[3 * s][num] + 1][num] / 3)y = fir[3 * s][num] / 3;
				else y = 1e9;
				if(!x)x = 1e9;
				if(!y)y = 1e9;
				if(x < y)
				{
					int k = noget(x, i);
					m(f[s][i][j], f[x + 1][a[3 * s - j]][k] + 1 + p[x - 1] - p[s - 1]);
				}
				else if(x > y)
				{
					int k = noget(y, num);
					m(f[s][i][j], f[y + 1][i][k] + 1 + p[y - 1] - p[s - 1]);
				}
			}
	}
	printf("%d", f[1][a[1]][1]);
	return 0;
}

```

---

## 作者：Unnamed114514 (赞：2)

把前两个割出来，然后 3 个 3 个分成 1 组。

然后你定义 $f_{i,j,k}$ 表示第 i 组，前面留下来的值是 $j,k$。

状态是 $O(n^3)$ 的，考虑优化状态到 $O(n^2)$。

对于每组，如果一个都没留，那么可以用前缀和轻松预处理。

于是我们 $k$ 这一维就可以用 $3$ 个值维护，表示这个组的第几个。

但是这样我们需要枚举上一个有留下来的数的组，转移变成了 $O(n)$。

但是发现转移方程式中，你就 $i,j$ 相互独立，所以直接维护个前缀 `max` 即可，转移就可以做到 $O(1)$ 了。

---

## 作者：DerrickLo (赞：1)

先考虑暴力 dp。记 $f_{i,j,k}$  表示操作了 $i$ 次，剩下的两个数是 $j$ 和 $k$ 的方案数，这样的时间复杂度是 $\mathcal O(n^3)$ 的。

然后你发现进行一次操作之后会改变的状态数只有 $\mathcal O(n)$ 个，那么直接滚动数组之后暴力修改那些应该修改的点即可。注意如果新的那三个数都相同那么是全局 $+1$，直接维护一个全局加的 tag 即可，然后还有一些情况是要求一行的 $\max$，这也是可以动态维护的。

时间复杂度 $\mathcal O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[9005],f[3005][3005],g[3005][3005],ans,flag,maxx,maxn[3005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=3*n;i++)cin>>a[i];
	memset(f,-0x3f,sizeof f),memset(g,-0x3f,sizeof g),memset(maxn,-0x3f,sizeof maxn);
	f[a[1]][a[2]]=f[a[2]][a[1]]=0,maxn[a[1]]=maxn[a[2]]=0;
	for(int i=2;i<=n;i++){
		int x=a[(i-1)*3],y=a[(i-1)*3+1],z=a[(i-1)*3+2];
		if(x==y&&y==z){flag++;continue;} 
		//不贡献，剩后面两个
		g[x][y]=max(g[x][y],maxx),g[y][x]=g[x][y]; 
		g[x][z]=max(g[x][z],maxx);g[z][x]=g[x][z];
		g[z][y]=max(g[z][y],maxx);g[z][y]=g[y][z];
		//不贡献，剩前1+后1
		for(int j=1;j<=n;j++){
			g[j][x]=max(g[j][x],maxn[j]);
			g[x][j]=g[j][x];
		}
		for(int j=1;j<=n;j++){
			g[j][y]=max(g[j][y],maxn[j]);
			g[y][j]=g[j][y];
		}
		for(int j=1;j<=n;j++){
			g[j][z]=max(g[j][z],maxn[j]);
			g[z][j]=g[j][z];
		}
		//贡献，前1+后2
		if(x==y){
			for(int j=1;j<=n;j++)g[j][z]=max(g[j][z],f[x][j]+1),g[z][j]=g[j][z]; 
		}
		if(y==z){
			for(int j=1;j<=n;j++)g[j][x]=max(g[j][x],f[y][j]+1),g[x][j]=g[j][x];
		}
		if(x==z){
			for(int j=1;j<=n;j++)g[j][y]=max(g[j][y],f[z][j]+1),g[y][j]=g[j][y];
		}
		//贡献，前2+后1
		g[x][y]=max(g[x][y],f[z][z]+1),g[y][x]=g[x][y];
		g[y][z]=max(g[y][z],f[x][x]+1),g[z][y]=g[y][z];
		g[z][x]=max(g[z][x],f[y][y]+1),g[x][z]=g[z][x];
		for(int j=1;j<=n;j++){
			f[x][j]=max(f[x][j],g[x][j]),maxx=max(maxx,f[x][j]),maxn[x]=max(maxn[x],f[x][j]);
			f[j][x]=max(f[j][x],g[j][x]),maxx=max(maxx,f[j][x]),maxn[j]=max(maxn[j],f[j][x]);
		}
		for(int j=1;j<=n;j++){
			f[y][j]=max(f[y][j],g[y][j]),maxx=max(maxx,f[y][j]),maxn[y]=max(maxn[y],f[y][j]);
			f[j][y]=max(f[j][y],g[j][y]),maxx=max(maxx,f[j][y]),maxn[j]=max(maxn[j],f[j][y]);
		}
		for(int j=1;j<=n;j++){
			f[z][j]=max(f[z][j],g[z][j]),maxx=max(maxx,f[z][j]),maxn[z]=max(maxn[z],f[z][j]);
			f[j][z]=max(f[j][z],g[j][z]),maxx=max(maxx,f[j][z]),maxn[j]=max(maxn[j],f[j][z]);
		}
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)ans=max(ans,f[i][j]+flag+(i==j&&j==a[3*n]));
	cout<<ans;
	return 0;
}
```

---

## 作者：liyixin0514 (赞：1)

# [[ABC176F] Brave CHAIN ](https://atcoder.jp/contests/abc176/tasks/abc176_f)

## 题意

给你 $3n$ 个数字。每次你可以选取前 $5$ 个数字，拿走里面任意三个数字，剩下两个，如果拿走的 $3$ 个数字相等，得分 $+1$。问最大得分是多少。

## 思路

首先我们想尝试贪心。然而不好贪心，因为你不知道前面会给你留下哪两张牌，留下的方案数很多。

题目可以看做每次有三个新数字，和前面两个留下的数字进行操作，它们中留下两个。

此时可以考虑 DP。由前面思考或者部分分提示可以设出 $dp_{i,x,y}$ 表示考虑到第 $i$ 组数字（$3$ 个为一组），留下 $x,y$ 的最大分数。

于是我们要枚举前面留下哪两个数字，五个数字中留下哪两个数字，状态是 $O(nV^2)$，转移考虑一下留下哪两个数字，是常数复杂度，总共 $O(nV^2)$。

考虑如何优化。

首先枚举 $i$ 是必须的，不过空间上可以把这一维滚掉。状态感觉都很有用。

考虑优化转移。分为得分和不得分两种情况考虑，这样代码好写一些吧。设新的三个数字为 $a,b,c$。若 $a=b=c$，我们直接删除这三个数字得分 $+1$，且这样是一定不劣的。反正它们迟早都要删掉，就不必留到后面了。因此这种情况全局 $+1$，可以维护一个 tag。虽然存在不得分的更新方式，但是根据贪心，我们最后的最大得分方案中一定没有把这三个新数留下的情况，这是不优的，因此这种情况不用考虑不得分的转移。

若 $a,b,c$ 有两个相等，设 $a=b$。可以在前面找一个 $x=a=b,y\in[1,n]$，进行转移，剩下的牌就是 $c,y$，得分 $+1$。也可以在前面找 $x=y=c$，剩下 $a,b$，得分 $+1$。

若 $a,b,c$ 互不相同，可以在前面找 $x=y=a \operatorname{or} b\operatorname{or} c$，这里假设选择了 $a$。那么剩下的是 $b,c$，得分 $+1$。

以上转移都是 $O(n)$ 或 $O(1)$ 的。下面讨论不得分的情况。

为了方便，不得分的情况可以不用考虑 $a,b,c$ 相等的情况。虽然这样可能会把得分的情况算入不得分，但由于我们的 $dp$ 值是取 $\max$，所以没有关系。

若新数留下两个假设是 $a,b$，那么剩下状态是 $a,b$，得分不变。得分等于 $x,y$ 任取的最大值，可以在上一层 $dp$ 顺便维护，时间复杂度是 $O(1)$ 的。

若剩下 $a,x$，则剩下状态为 $a,x$，我们必须枚举 $x$，毕竟它是目前一层的状态。然后对所有可能的 $y\in[1,n]$ 取最大值，这个也可以在上一层 DP 的时候顺便维护。时间复杂度 $O(n)$。

若剩下 $x,y$，则我们要枚举所有 $x,y$，因为这是状态。但是你发现上面所有的转移都最多只有 $O(n)$，而且这个转移极为美丽，它是由 $x,y\to x,y$ 的。一个小技巧是把上面的转移用临时数组存下来，只有 $O(n)$ 个，做完上面转移后直接把数组盖到原  DP 数组上，这样我们就不用 copy 一遍 $n^2$ 的 DP 数组了。

总时间复杂度 $O(n^2)$。

## code

```cpp
#include<bits/stdc++.h>
//#define LOCAL
#define sf scanf
#define pf printf
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define isdigit(x) (x>='0'&&x<='9')
using namespace std;
typedef long long ll;
const int N=3e3+7;
template <typename T>
inline void read(T &x) {
	x=0;
	char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
}
template <typename T>
inline void write(T x) {
	static int st[10];
	int top=0;
	do {
		st[top++]=x%10;
		x/=10;
	}while(x);
	while(top) putchar(st[--top]+'0');
}
template <typename T>
inline void write(T x,char ch) {
	write(x),putchar(ch);
}
int n;
int a[N*3];
int f[N][N],lamax,g[N],s;
void update(int &mx,int &mx1,int &mx2,int &a,int b,int c) {
	if(b) a=max(a,b+c);
	mx=max(mx,a);mx1=max(mx1,a),mx2=max(mx2,a);
}
struct node{
	int x,y,z,p;
};
vector<node> vec;
int main() {
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("my.out","w",stdout);
	#else
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	#endif
	read(n);
	rep(i,1,n*3) {
		read(a[i]);
	}
	int x=a[1],y=a[2];
	if(x>y) swap(x,y);
	f[x][y]=1;
	lamax=1,g[x]=g[y]=1;
	rep(i,1,n-1) {
		vec.clear();
		int b[3]={a[i*3],a[i*3+1],a[i*3+2]};
		if(b[0]==b[1]&&b[0]==b[2]) { s++;continue;}
		if(b[0]==b[1]||b[0]==b[2]||b[1]==b[2]) {
			int c1=0,c3=0;
			if(b[0]==b[1]) c1=0,c3=2;
			else if(b[0]==b[2]) c1=0,c3=1;
			else c1=1,c3=0;
			rep(k,1,n) {
				int x=k,y=b[c3];
				if(x>y) swap(x,y);
				int xx=k,yy=b[c1];
				if(xx>yy) swap(xx,yy);
				vec.push_back({x,y,f[xx][yy],1});
			}
			vec.push_back({b[c1],b[c1],f[b[c3]][b[c3]],1});
		}else {
			int x=b[1],y=b[2];if(x>y) swap(x,y);
			vec.push_back({x,y,f[b[0]][b[0]],1});
			x=b[0],y=b[2];if(x>y) swap(x,y);
			vec.push_back({x,y,f[b[1]][b[1]],1});
			x=b[0],y=b[1];if(x>y) swap(x,y);
			vec.push_back({x,y,f[b[2]][b[2]],1});
		}
		int x=b[1],y=b[2];if(x>y) swap(x,y);
		vec.push_back({x,y,lamax,0});
		x=b[0],y=b[2];if(x>y) swap(x,y);
		vec.push_back({x,y,lamax,0});
		x=b[0],y=b[1];if(x>y) swap(x,y);
		vec.push_back({x,y,lamax,0});
		rep(k,1,n) {
			rep(c,0,2) {
				int x=b[c],y=k;
				if(x>y) swap(x,y);
				vec.push_back({x,y,g[k],0});
			}
		}
		for(auto tmp : vec) {
			update(lamax,g[tmp.x],g[tmp.y],f[tmp.x][tmp.y],tmp.z,tmp.p);
		}
	}
	int ans=lamax+s;
	if(f[a[n*3]][a[n*3]]) ans=max(ans,f[a[n*3]][a[n*3]]+s+1);
	pf("%d\n",ans-1);
}
```

---

## 作者：daniEl_lElE (赞：1)

首先有一个暴力的 dp：考虑 $dp_{i,j,k}$ 表示操作 $i$ 次后剩余了 $j,k$，分数最高是多少。转移的时候枚举 $j,k$ 后枚举删除 $5$ 张牌中的哪 $3$ 张。总复杂度 $O(n^3)$，无法通过。

注意到新加的 $3$ 张一定是保留 $0/1/2$ 张。保留 $0$ 张时相当于将所有 $dp_{i,j,k}$ 值赋为 $dp_{i-1,j,k}$ 加上三张是否均相等。保留 $2$ 张时，设删除的一张权值为 $x$，未删除的为 $y,z$，本质上就是 $dp_{i,y,z}\leftarrow\max(dp_{i-1,x,x}+1,dp_{i-1,j,k})$。保留 $1$ 张时，设删除的两张权值为 $x,y$，未删除的为 $z$，本质上就是 $dp_{i,z,k}\leftarrow\max(dp_{i-1,x,k}+[x=y],dp_{i-1,j,k})$。

保留 $0$ 张等价于全局加，可以转化为在后续的新增转移值上扣减。保留 $2$ 张相当于单点查询全局查询单点修改。保留 $1$ 张相当于单点查询列查询单点修改。均可 $O(1)$ 维护。总复杂度 $O(n^2)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define lowbit(i) (i&(-i))
using namespace std;
int a[6005];
int f[2005][2005];
int g[2005];
int h,precnt=0;
void upd(int i,int j,int val){
	f[i][j]=max(f[i][j],val);
	f[j][i]=max(f[j][i],val);
	g[i]=max(g[i],val);
	g[j]=max(g[j],val);
	h=max(h,val);
}
signed main(){
	int n; cin>>n;
	for(int i=1;i<=3*n;i++) cin>>a[i];
	if(n==1){
		cout<<((a[1]==a[2])&(a[2]==a[3]));
		return 0;
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]=-1e18;
	for(int i=1;i<=n;i++) g[i]=-1e18;
	h=-1e18;
	for(int i=1;i<=5;i++){
		for(int j=1;j<=5;j++){
			if(i==j) continue;
			int lst=-1,ok=1;
			for(int k=1;k<=5;k++){
				if(k==i||k==j) continue;
				if(lst!=-1) ok&=(lst==a[k]);
				lst=a[k];
			}
			f[a[i]][a[j]]=max(f[a[i]][a[j]],ok);
			f[a[j]][a[i]]=max(f[a[j]][a[i]],ok);
			g[a[i]]=max(g[a[i]],ok);
			g[a[j]]=max(g[a[j]],ok);
			h=max(h,ok);
		}
	}
	for(int i=6;i<3*n;i+=3){
		int add=(a[i]==a[i+1])&(a[i+1]==a[i+2]);
		int upd1=max(f[a[i]][a[i]]+1-add,h-add);
		int upd2=max(f[a[i+1]][a[i+1]]+1-add,h-add);
		int upd3=max(f[a[i+2]][a[i+2]]+1-add,h-add);
		int upd4[n+1];
		for(int j=1;j<=n;j++){
			upd4[j]=-1e18;
			if(a[i+1]==a[i+2]) upd4[j]=max(upd4[j],f[a[i+1]][j]+1-add);
			upd4[j]=max(upd4[j],g[j]-add);
		}
		int upd5[n+1];
		for(int j=1;j<=n;j++){
			upd5[j]=-1e18;
			if(a[i+2]==a[i]) upd5[j]=max(upd5[j],f[a[i+2]][j]+1-add);
			upd5[j]=max(upd5[j],g[j]-add);
		}
		int upd6[n+1];
		for(int j=1;j<=n;j++){
			upd6[j]=-1e18;
			if(a[i]==a[i+1]) upd6[j]=max(upd6[j],f[a[i]][j]+1-add);
			upd6[j]=max(upd6[j],g[j]-add);
		}
		upd(a[i+1],a[i+2],upd1);
		upd(a[i+2],a[i],upd2);
		upd(a[i],a[i+1],upd3);
		for(int j=1;j<=n;j++){
			upd(a[i],j,upd4[j]);
			upd(a[i+1],j,upd5[j]);
			upd(a[i+2],j,upd6[j]);
		}
		precnt+=add;
	}
	int maxv=0;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) maxv=max(maxv,f[i][j]+precnt+((i==a[3*n])&(j==a[3*n])));
	cout<<maxv;
	return 0;
}
```

---

## 作者：ljjl (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc176_f)

考虑使用 dp。定义 $f_{i,j,k}$ 为第 $i$ 轮消完后手牌为 $j$ 和 $k$ 时最大分数，$ma_{i,j}$ 为第 $i$ 轮后手牌中包含 $j$ 时的最大分数，$e_i$ 为第 $i$ 轮后总的最大分数。三者可用滚动数组降维掉第一维成 $f_{i,j},ma_{i},e$。

关于转移方程，考虑第 $i$ 轮拿到的三张牌 $x,y,z$。

若 $x = y = z$，则将这三张牌消掉，且全局答案加一。

若有两张牌相等，假设为 $x = y$。此时进行分类讨论：

1. 三张牌均不保留，此时价值不变。

2. 留下 $x,y$，此时将 $\max(e,f_{z,z}+1)$ 转移到 $f_{x,y}$。

3. 留下 $x,z$，此时将 $\max(e,f_{y,y}+1)$ 转移到 $f_{x,z}$。

4. 留下 $z$，此时枚举另一张手牌 $k$。最后一次消的是相同的 $x,y$，可能有贡献，所以将 $\max(ma_j,f_{i,x}+1)$ 转移到 $f_{z,k}$。

5. 留下 $x$，此时枚举另一张剩下手牌 $k$。最后一次消的是不相同的 $y,z$，因此不可能有贡献，所以将 $ma_j$ 转移到 $f_{x,k}$。

若三张牌均不等，此时进行分类讨论：

1. 三张牌均不保留，此时价值不变。

2. 留下一张牌，此时枚举另一张手牌 $k$，将 $ma_j$ 转移到 $f_{x,k}$。

3. 留下两张牌，留下 $x,y$ 或留下 $x,z$，转移方程同上。

每一轮将转移用动态数组存起来，到这一轮最后统一处理。

复杂度为 $O(n^2)$。

代码如下

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+1,inf=1e9;
int x,y,z,n,a[N],f[N][N],cnt,e,ma[N];
struct node{
	int x,y,v;
	int make(int a,int b,int c){
		x=a,y=b,v=c;
	}
};
vector<node>v;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		ma[i]=-inf;
		for(int j=1;j<=n;j++)
			f[i][j]=f[j][i]=-inf;
	}
	f[x][y]=f[y][x]=ma[x]=ma[y]=0;
	for(int i=1;i<n;i++){
		cin>>x>>y>>z;
		if(x>y) swap(x,y);
		if(x>z) swap(x,z);
		if(y>z) swap(y,z);
		if(y==z) swap(x,z);
		if(x==z){
			cnt++;
			continue;
		}
		v.clear();
		if(x==y){
			v.push_back({x,y,max(e,f[z][z]+1)});
			v.push_back({x,z,max(e,f[y][y]+1)});
			for(int j=1;j<=n;j++){
				v.push_back({j,z,max(ma[j],f[j][x]+1)});
				v.push_back({j,x,ma[j]});
			}
		}
		else{
			v.push_back({x,y,max(e,f[z][z]+1)});
			v.push_back({x,z,max(e,f[y][y]+1)});
			v.push_back({y,z,max(e,f[x][x]+1)});
			for(int j=1;j<=n;j++){
				v.push_back({j,x,ma[j]});
				v.push_back({j,y,ma[j]});
				v.push_back({j,z,ma[j]});
			}
		}
		for(int j=0;j<v.size();j++){
			x=v[j].x,y=v[j].y,z=v[j].v;
			f[x][y]=f[y][x]=max(f[x][y],z),ma[x]=max(ma[x],z),ma[y]=max(ma[y],z),e=max(e,z);
		}
	}
	cin>>x;
	cout<<max(e,f[x][x]+1)+cnt;
	return 0;
}
```

---

## 作者：gxp123 (赞：0)

# abc176 F - Brave CHAIN

## 题意

hhoppitree 有 $3n$ 张卡片，其中每张卡片上都写着 $1\sim n$ 中的一个数，他会重复以下操作 $n-1$ 次：

- 将最左侧的 $5$ 张牌**任意排列**，排列后，删去最左侧的 $3$ 张牌，如果这三张牌上写着同样的数，hhoppitree 可以获得 $1$ 分。

最后，如果剩余的 $3$ 张牌上的数字一样，那么他还可以额外得到 $1$ 分。

现在，hhoppitree 想要知道，他得到的分数最高是多少。

$n \le 3000$ 。

## 题意

对于每次删牌，我们考虑删牌的情况。

假设说新加入的三张牌是 $p,q,r$ ，从上次 $5$ 张残留下来的是 $x,y$ 。

则情况就比较简单了。

可以留 $p,q,r$ 中的两张。

也可以留 $p/q/r,x/y$ 。

也可以都扔掉。

如果扔掉的牌中有 $3$ 张相同的，分数就加一。

### dp

根据上面的情形，我们可以设计出 $dp$ 状态来：

我们设 $f_{i,x,y}$ 表示在第 $i$ 次删牌中，留下 $x,y$ 的最大分数。

因为我们是对前面怎么删的牌是不感兴趣的，我们只对那几张牌剩下了感兴趣。

根据 $dp$ 状态，我们就可以分成三大类。

1. 留 $x,y$ 。
2. 留 $p/q/r,x/y$ 。
3. 留 $p,q,r$ 中的两张。

#### 第一类 留 $x,y$

>  第一类显然是好做的，直接有转移方程：
  $$
  f_{i,x,y} = f_{i-1,x,y}
  $$
>  当然，如果 $p=q=r$ ，则有转移方程：
>  $$
  f_{i,x,y} = f_{i - 1,x,y} 。
  $$
>  

******

#### 第二类 留 $p/q/r,x/y$ 。

> 对于第二类，我们分成两组
> 
> - 不可以造成贡献的。
> - 可以造成贡献。
> 
> 对于第一类，我们就直接有转移方程：
> 
> $$
 f_{i,x,p/q/r} = \max\limits_{y=1}^n\ \{f_{i-1,x,y}\}
 $$
> 
> 对于我们来说， $x,y$ 都是未知的，所以需要我们去枚举。
> 
> 对于第二类，我们就选出 $p/q/r$ 中相同的两张，然后再去找一张和他们相同的一张，把这三张丢弃就可以得分。
> 
> 我们在这里钦定 $p = q$ 。（如果不相等，交换一下即可）
> 
> 即有转移方程：
> $$
 f_{i,x,r} = f_{i-1,x,p}
 $$

#### 第三类 留 $p,q,r$ 中的两张。

> 对于第三类，我们仍分成两组。
>
> - 不可以造成贡献的。
> - 可以造成贡献。
>
> 对于第一类，我们枚举剩下那两张即可：
>
> 有转移方程 （以 $p,q$ 为例）：
 $$
 f_{i,p,q} = \max\limits_{x = 1} ^ {n} \{ \max\limits_{ y= 1} ^ {n} \{ f_{i-1,x,y} \} \}
 $$
> 对于第二类，我们需要拿出两张与其中一张相同的。
>
> 即 $x = y = p/q/r$ 。
>
> 则有转移方程：
 $$
 f_{i,p,q} = f_{i-1,r,r}
 $$
>
 $$
 f_{i,p,r} = f_{i-1,q,q}
 $$
 $$
 f_{i,q,r} = f_{i-1,p,p}
 $$

对于最后的一张牌 $z$ ，我们枚举前面 $x = y = z$ 的状态 $f_{n,z,z}$ ，因为它满足了最后三张牌相同的条件，所以我们要把它的分数加一。

我们就解决了 $dp$ 。

### 优化

#### 空间

但是 $n \le 3000$ ，$O(n ^ 3)$  的空间显然是开不下的。

所以我们考虑使用滚动数组。

对于最后一张牌 $z$ 的贡献，我们让 $f_{z,z}$ 加一即可。

空间复杂度：$O(n^2)$ 。

#### 时间

因为有了滚动数组，所以我们转移第一类中第一个方程，我们上面都不需要做。

对于转移第一类中第二个方程，我们只需要打一个标记 $tag$，表示全局都可以加的值。

对于其他的：

求 $\max$ 的操作的时间我们是不可接受的。

比如：

> $$
 f_{i,x,p/q/r} = \max\limits_{y=1}^n\ \{f_{i-1,x,y}\}
$$
> $$
 f_{i,p,q} = \max\limits_{x = 1} ^ {n} \{ \max\limits_{ y= 1} ^ {n} \{ f_{i-1,x,y} \} \}
 $$

但我们可以发现，我们都是需要的是全局的最优解，或 $dp$ 数组中某一行的最大值。

这个显然是好求的，我们每次 $dp$ 方程转移的时候，都统计一下就可以了。

### 细节

对于第二类第三类操作，我们可以先用一个数组把转移的值存下来，等所有的转移结束后，我们在更新 $dp$ 数组。

这样可以极大的让代码变得好写。

初值： $f_{x,y} = -∞,f_{a_1,a_2} = f_{a_2,a_1} = 0$  。

答案：
$$
\max\limits_{x = 1} ^ {n}  \max\limits_{ y= 1} ^ {n} \{ f_{x,y} \} + tag
$$

## code


```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int N = 2000 + 10;
const int maxN = N * 3;
int f[maxN][maxN];
int h[maxN],b[maxN],c[maxN],k[3];
int a[maxN];
int n;

int main(){
    scanf("%d",&n);
    for(int i = 1 ; i <= n * 3 ; ++i){
        scanf("%d",a + i);
    }
    memset(f,0xcf,sizeof(f));
    memset(h,0xcf,sizeof(h));
    int p,q,r,tag = 0,x,y,maxh = 0;
    f[a[2]][a[1]] = f[a[1]][a[2]] = 0;
    h[a[1]] = h[a[2]] = 0;
    for(int i = 1 ; i < n ; ++i){
        p = a[i * 3];
        q = a[i * 3 + 1];
        r = a[i * 3 + 2];
        if(p == q && q == r){
            ++tag;
        }else{
            if(r == p)  swap(r,q);
            if(r == q)  swap(r,p);
            if(p == q){
                x = p;
                for(y = 1 ; y <= n ; ++y)
                    c[y] = max(max(f[x][y],f[y][x]) + 1,f[y][r]);
            }
			for(y = 1 ; y <= n ; ++y)   b[y] = h[y];
            k[0] = k[1] = k[2] = maxh;
            k[0] = max(f[p][p] + 1,k[0]);
            k[1] = max(k[1],f[r][r] + 1);
            k[2] = max(k[2],f[q][q] + 1);

            f[r][q] = f[q][r] = k[0];
            f[p][q] = f[q][p] = k[1];
            f[p][r] = f[r][p] = k[2];
            h[p] = max(h[p],max(f[p][r],f[p][q]));
            h[q] = max(h[q],max(f[q][r],f[q][p]));
            h[r] = max(h[r],max(f[r][q],f[r][p]));
            maxh = max(max(maxh,h[p]),max(h[q],h[r]));

            for(y = 1 ; y <= n ; ++y){
                f[p][y] = f[y][p] = max(f[y][p],b[y]);
                f[q][y] = f[y][q] = max(f[y][q],b[y]);
                f[r][y] = f[y][r] = max(f[y][r],b[y]);
                h[y] = max(max(h[y],f[y][p]),max(f[y][q],f[y][r]));
                h[q] = max(h[q],f[q][y]);
                h[r] = max(h[r],f[r][y]);
                h[p] = max(h[p],f[p][y]);
            }
            if(p == q){
                for(y = 1 ; y <= n ; ++y){
                    f[y][r] = f[r][y] = max(c[y],f[y][r]);
                    maxh = max(maxh,f[y][r]);
                    h[y] = max(h[y],f[y][r]);
                    h[r] = max(h[r],f[r][y]);
                }
            }
        }
    }
    int ans = 0;
    for(int x = 1 ; x <= n ; ++x){
        for(int y = 1 ; y <= n ; ++y){
            if(x == a[n * 3] && y == a[n * 3])
                ans = max(ans,f[x][y] + 1);
            else
                ans = max(ans,f[x][y]);
        }
    }
    printf("%d",ans + tag);
    return 0;
}
```

---

