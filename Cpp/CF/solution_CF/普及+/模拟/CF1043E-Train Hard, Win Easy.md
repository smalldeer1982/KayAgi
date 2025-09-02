# Train Hard, Win Easy

## 题目描述

Zibi is a competitive programming coach. There are $ n $ competitors who want to be prepared well. The training contests are quite unusual – there are two people in a team, two problems, and each competitor will code exactly one of them. Of course, people in one team will code different problems.

Rules of scoring also aren't typical. The first problem is always an implementation problem: you have to implement some well-known algorithm very fast and the time of your typing is rated. The second one is an awful geometry task and you just have to get it accepted in reasonable time. Here the length and difficulty of your code are important. After that, Zibi will give some penalty points (possibly negative) for each solution and the final score of the team is the sum of them (the less the score is, the better).

We know that the $ i $ -th competitor will always have score $ x_i $ when he codes the first task and $ y_i $ when he codes the second task. We can assume, that all competitors know each other's skills and during the contest distribute the problems in the way that minimizes their final score. Remember that each person codes exactly one problem in a contest.

Zibi wants all competitors to write a contest with each other. However, there are $ m $ pairs of people who really don't like to cooperate and they definitely won't write a contest together. Still, the coach is going to conduct trainings for all possible pairs of people, such that the people in pair don't hate each other. The coach is interested for each participant, what will be his or her sum of scores of all teams he trained in?

## 说明/提示

In the first example, there will be only one team consisting of persons $ 1 $ and $ 3 $ . The optimal strategy for them is to assign the first task to the $ 3 $ -rd person and the second task to the $ 1 $ -st person, this will lead to score equal to $ 1 + 2 = 3 $ .

In the second example, nobody likes anyone, so there won't be any trainings. It seems that Zibi won't be titled coach in that case...

## 样例 #1

### 输入

```
3 2
1 2
2 3
1 3
1 2
2 3
```

### 输出

```
3 0 3 ```

## 样例 #2

### 输入

```
3 3
1 2
2 3
1 3
1 2
2 3
1 3
```

### 输出

```
0 0 0 ```

## 样例 #3

### 输入

```
5 3
-1 3
2 4
1 1
3 5
2 2
1 4
2 3
3 5
```

### 输出

```
4 14 4 16 10 ```

# 题解

## 作者：Digital_Sunrise (赞：3)

## CF1043E题解

[CF1043题解合集](https://www.luogu.com.cn/blog/yl2330/I-Love-YR-Forever)

[Markdonw源代码](https://yhwh-group.coding.net/public/codingwiki/files/git/files/master/blog/CF1043/E.Markdown)

好像其他题解说得都不太清楚？？？

Update 21.11.17 更正博客地址

### 题意简述

共有 $n$ 个人，第 $i$ 个人有两个属性 $A_i,B_j$ ，

其中如果两个人 $i,j$ 合作，价值为 $\min(A_i+B_j,A_j+B_i)$ 。

还有 $m$ 对关系，其中第 $i$ 对关系 $u_i,v_i$ 表示 $u_i,v_i$ 都不想且不会与对方合作。

让你求的是每一个人与剩余可合作人的合作价值之和。

### 思路

设想有两个人 $i,j$ ，

如果他们的合作价值为 $A_i+B_j$ ，

那么需要满足 $A_i+B_j<A_j+B_i$。

移项得到 $A_i-B_i<A_j-B_j$ 。

那么当满足 $A_i-B_i<A_j-B_j$ 时， $i$ 对 $(i,j)$ 合作价值的贡献是 $A_i$ ，否则为 $B_i$ 。

所以我们以 $A_i-B_i$ 为比较条件将所有数据排序，

对于排序后第 $i$ 个位置的数，

$Ans_i=\sum\limits_{j=1}^{i-1}(A_j + B_i) = \sum\limits_{j=1}^{i-1}A_j + (n - 1) \times B_i$

（因为根据上述推导，对于前 $i - 1$ 个数统称为 $j$ ， $i$ 满足 $A_i-B_i>A_j-B_j$

所以 $i$ 的贡献为 $B_i$ ， $j$ 的贡献为 $A_j$）

但是第 $i$ 个数也会与后 $(n-i)$ 个数合作，

所以同理：

$Ans_i=Ans_i+\sum\limits_{j=i+1}^n(A_i + B_j)=Ans_i+\sum\limits_{j=i+1}^nB_j+(n -i)\times A_i$

整理后：

$Ans_i=\sum\limits_{j=1}^{i-1}A_j + (n - 1) \times B_i + \sum\limits_{j=i+1}^nB_j+(n -i)\times A_i$

$\,\,\,\,\,\,\,\,\,\,\,\,\,\, = \sum\limits_{j=1}^{i-1}A_j + \sum\limits_{j=i+1}^nB_j+ (n - 1) \times B_i+(n -i)\times A_i$

$\sum\limits_{j=1}^{i-1}A_j$ 和 $\sum\limits_{j=i+1}^nB_j$ 显然不能暴力求出来，

所以加一个对于 $A$ 的前缀和和对于 $B$ 的后缀和优化即可。

那么如何处理不合作的情况呢？

我们可以暴力处理每一个人的排斥情况，因为 $1\le n,m\le 3e5$ ，暴力处理的总共复杂度也只有 $O(n+m)$ 。

对于每一个人 $i$ ，遍历所有与之不合作的人 $j$ ， $Ans_i$ 减去 $\min(A_i+B_j,A_j+B_i)$ 。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 300005;

int n,m;
int sum1[maxn],sum2[maxn];
struct node{int x,y,id;}a[maxn];
vector <int> G[maxn];
int ans[maxn];
map <int,int> rnk;

bool cmp(node a,node b)
{return (a.x - a.y) < (b.x - b.y);}

signed main()
{
    cin >> n >> m;
    for(int i = 1;i <= n;i++)
        scanf("%lld%lld",&a[i].x,&a[i].y),a[i].id = i;
    for(int i = 1;i <= m;i++)
    {
        int u,v;
        scanf("%lld%lld",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    sort(a + 1,a + n + 1,cmp);
    for(int i = 1;i <= n;i++)
        rnk[a[i].id] = i;
    for(int i = 1;i <= n;i++)
        sum1[i] = sum1[i - 1] + a[i].x;
    for(int i = n;i >= 1;i--)
        sum2[i] = sum2[i + 1] + a[i].y;
    for(int i = 1;i <= n;i++)
    {
        ans[a[i].id] += sum1[i - 1] + (i - 1) * a[i].y;
        ans[a[i].id] += sum2[i + 1] + (n - i) * a[i].x;
        for(int k = 0;k < G[a[i].id].size();k++)
        {
            int v = rnk[G[a[i].id][k]];
            ans[a[i].id] -= min(a[i].x + a[v].y,a[i].y + a[v].x);
        }
    }
    for(int i = 1;i <= n;i++)
        cout << ans[i] << " ";
    return 0;
}
```

---

## 作者：liuyz11 (赞：1)

广告：[这场比赛的原地址](https://www.cnblogs.com/nblyz2003/p/9868480.html)

上一次看错题了，搞了半天样例打错，之前的题解是错的，抱歉，现在改了。

这题时说有$n$个大佬去打比赛（就两题），第$i$个大佬第一题会得$a[i]$分，第二题会得$b[i]$分，现在每次选俩大佬打模拟赛，每道题各选一个大佬，使获得的总分最少（为啥最少，我也不知道）。然后有m对大佬不会一起打。让你求每个大佬每次比赛中团队的总分。

当$i$和$j$一起打，

假设i做第一道

所以说$a[i] + b[j] < a[j] + b[i]$

那么$a[i] - b[i] < a[i] - b[j]$

所以说我们只要将$a[i] - b[i]$排序，如果$j$在$i$的前面，那么第$i$个人就要做一次第二题，否则做一次第一题。

我们用$id[i]$记录排序后i所在的位置，那么$i$就要做$id[i] - 1$次第二题，$n - id$次第一道，另外因为记录每次比赛团队总分，所以答案还得加上$a[1] ~ a[id[i] - 1]$和$b[id[i] + 1] ~ b[n]$。所以还需要开个前缀和和后缀和。


再判断不会一起打的人在他的前面还是后面，减去。

时间复杂度为$O(log(n) + m)$。

代码如下
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define rep(x, l, r) for(int x = (int)l; x <= (int)r; x++)
#define repd(x, r, l) for(int x = (int)r; x >= (int)l; x--)
#define clr(x,y) memset(x, y, sizeof(x))
#define mp(x, y) make_pair(x, y)
#define all(x) begin(x), end(x)
#define MAXN 500005
#define fi first
#define se second
#define Size(x) ((int)size(x))
using namespace std;
typedef long long LL;
typedef vector<int> vi;
typedef pair<LL, int> pli;
typedef pair<LL, LL>pll;
const int INF = 1 << 30;
const int p = 10000007;

pli c[MAXN];
pll sum[MAXN];
int id[MAXN];
LL a[MAXN], b[MAXN], ans[MAXN];

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    rep(i, 1, n){
        scanf("%I64d%I64d", &a[i], &b[i]);
        c[i] = mp(a[i] - b[i], i);
    }
    sort(c + 1, c + n + 1);
    rep(i, 1, n) id[c[i].se] = i;
    sum[0] = mp(0, 0);
    sum[n + 1] = mp(0, 0);
    rep(i, 1, n) sum[i].fi = sum[i - 1].fi + a[c[i].se];
    repd(i, n, 1) sum[i].se = sum[i + 1].se + b[c[i].se];
    rep(i, 1, n) ans[i] = a[i] * (n - id[i]) + b[i] * (id[i] - 1) + sum[id[i] - 1].fi + sum[id[i] + 1].se;
    rep(times, 1, m){
        int x, y;
        scanf("%d%d", &x, &y);
        if(id[x] < id[y]) ans[x] -= a[x] + b[y], ans[y] -= a[x] + b[y];
        else ans[x] -= a[y] + b[x], ans[y] -= a[y] + b[x];
    }
    rep(i, 1, n) printf("%I64d ", ans[i]);
    puts("");
    return 0;
}
```

---

## 作者：SunsetSamsara (赞：0)

## 前置知识

数学

## 分析

令 $X_x$ 表示第 $x$ 个选手的 $x$ 值，令 $Y_x$ 表示第 $x$ 个选手的 $y$ 值

发现如果有两个人 $x, y$ 的合作价值为 $X_x + Y_y$，那么就有 $X_x + Y_y < X_y + Y_x$，即 $X_x - Y_x < X_y - Y_y$ 。又发现当 $X_x - Y_x < X_y - Y_y$ 时，$x$ 这个人对本次合作价值的贡献是 $X_x$ ，否则为 $Y_x$ 。

于是有个显然的想法，以 $X_x - Y_x$ 为权值排序。

> 注：以下内容中的 $X$ 和 $Y$ 皆为排序后的 $X$ 和 $Y$

### 合作的情况

带入上述结果后得到对于排序后第 $x$ 个位置的人，它前面的人对它的答案的贡献就是
$$\sum\limits_{y = 1} ^ {x - 1}(X_y + Y_x) = \sum\limits_{y = 1} ^ {x - 1}X_y + (x - 1) Y_x$$
类似地，它后面的人对它的答案的贡献就是 
$$\sum\limits_{y = x+1}^n(X_x + Y_y) = \sum\limits_{y = x + 1}^n Y_y+(n - x)X_x$$

整理后不难得到

$$\begin{aligned}\footnotesize\textsf{原式}&=\sum\limits_{y=1}^{x-1}X_y + (n - 1) Y_x + \sum\limits_{y=x+1}^nY_y+(n - x)X_x\\
&= \sum\limits_{y=1}^{x-1}X_y + \sum\limits_{y=x+1}^nY_j+ (n - 1) Y_x+(n - x)X_i\\
\end{aligned}$$

### 不合作的情况

但是，还有不合作的情况待处理。

我们只需要枚举每个不愿意一起训练的选手减去答案即可。

具体地，对于一个人 $x$ 和一个与它不合作的人 $y$，$x$ 的答案得减去 $\min(X_i + Y_j, X_j + Y_i)$ 。

于是这题就做完了，总复杂度 $\Theta(n\log n + m)$。

## 代码

```cpp
#include <stdio.h> 
#include <string.h>
#include <algorithm> 
#define lld long long
using std::sort;
inline void swap(int &x, int &y) { int t = x; x = y; y = t; }
int n, m;
int id0[300010];
int id[300010];
lld x[300010];
lld y[300010];
bool cmp (const int &a, const int b) {
	return x[a] - y[a] < x[b] - y[b];
} // 前面的结论，按照 x - y 排序 
lld xsum[300010]; // x 的前缀和 
lld ysum[300010]; // y 的后缀和
lld ans[300010];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) {
		scanf("%lld%lld", x + i, y + i);
		id0[i] = i;
	}
	sort(id0 + 1, id0 + n + 1, cmp);
	for (int i = 1; i <= n; ++ i) id[id0[i]] = i;
	for (int i = 1; i <= n; ++ i) xsum[i] = xsum[i - 1] + x[id0[i]];
	for (int i = n; i >= 1; -- i) ysum[i] = ysum[i + 1] + y[id0[i]];
	for (int i = 1; i <= n; ++ i)
		ans[i] = x[i] * (n - id[i]) + y[i] * (id[i] - 1) + xsum[id[i] - 1] + ysum[id[i] + 1];
		// 善良的 Codeforces 手把手教你开 long long
	for (int u, v; m --; ) {
		scanf("%d%d", &u, &v);
		if (id[u] > id[v]) swap(u, v);
		ans[u] -= x[u] + y[v], ans[v] -= x[u] + y[v];
	}
	for (int i = 1; i <= n; ++ i) printf("%lld ", ans[i]);
}
```

---

## 作者：MuYC (赞：0)

#### 吐槽
这道题难在题意理解有木有。题目倒是不难。

#### 题意搬运

给定 $n$ 个人的两个属性 :$A_i,B_i$ ，并且给出了 $m$ 个关系 :

$x_i$  $y_i$ 表示第 $x_i$ 个人不能和第 $y_i$ 个人配对。

同时 $i,j$ 二人规定配对的价值为 : $A_i + B_j$ 和 $B_i + A_j$ 中的最小值。

现在你需要回答出**每个人**跟所有人配对（除开不能和自己匹配的人）的价值总和。

#### 解题思路

那么考虑下面式子什么时候成立:

$A_i + B_j < B_i + A_j$

那么我们就得到:

$B_j - A_j < B_i - A_i$

这说明当 $B_j - A_j < B_i - A_i$ 的时候我们应该用 $A_i$ 去匹配 $B_j$ 会得到最小价值。

否则的话我们就应该用 $B_i$ 匹配 $A_j$。

所以按照 $B - A$ 从小到大排序，然后再使用前缀和优化即可，详见代码。

#### Code
(有注释，下面有做题的思路)

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3e5 + 50;
#define int long long
int n,m;
int start[MAXN],tot = 0;
int sum2[MAXN],sum[MAXN],Ans[MAXN],mp[MAXN];

inline int read() {
	int x = 0 , flag = 1;
	char ch = getchar();
	for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
	for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
	return x * flag;
}

struct Node {
	int x,y,id;
} P[MAXN];

struct Edge {
	int next,to;
} edge[MAXN * 2];

void add(int u,int v) {
	edge[++tot].next = start[u];
	edge[tot].to = v;
	start[u] = tot;
	return ;
}

bool cmp(Node A, Node B) {
	return (A.y - A.x) < (B.y - B.x);
}

signed main() {
	n = read() , m = read();
	for(int i = 1 ; i <= n ; i ++) P[i].x = read() , P[i].y = read() , P[i].id = i;
	for(int i = 1 ; i <= m ; i ++) {
		int u = read() , v = read();
		add(u, v); add(v, u);
	}
	sort(P + 1 ,  P + 1 + n , cmp);
	for(int i = 1 ; i <= n ; i ++) sum[i] = sum[i - 1] + P[i].y;
        //上面这个就前缀和处理出了 Bj-Aj < Bi - Ai 的所有人的 y 之和
	for(int i = n ; i >= 1 ; i --) sum2[i] = sum2[i + 1] + P[i].x;
        //上面这个就前缀和处理出了 Bj-Aj > Bi - Ai 的所有人的 x 之和
	for(int i = 1 ; i <= n ; i ++) mp[P[i].id] = i;
	for(int i = 1 ; i <= n ; i ++) { //划重点，这个是计算答案的地方
		Ans[P[i].id] += sum[i - 1] + (i - 1) * P[i].x; 
                // (i - 1) 就是 Bj-Aj < Bi - Ai 的所有人的个数，乘上 P[i].x 就表示用 Bi 去匹配
		Ans[P[i].id] += sum2[i + 1] + (n - i) * P[i].y;
                //这里同理
	}
	for(int j = 1 ; j <= n ; j ++) {
		for(int i = start[j] ; i ; i = edge[i].next) {
			int to = edge[i].to;
			Ans[j] -= min(P[mp[j]].x + P[mp[to]].y , P[mp[j]].y + P[mp[to]].x);//暴力减去就行了
		} 
		cout << Ans[j] << " ";
	}
	return 0;
}
```

---

