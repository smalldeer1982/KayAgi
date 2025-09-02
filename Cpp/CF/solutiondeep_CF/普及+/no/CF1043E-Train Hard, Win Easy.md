# 题目信息

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

# AI分析结果

### 题目内容
# 刻苦训练，轻松取胜

## 题目描述
Zibi是一位竞技编程教练。有$n$个参赛者希望做好准备。训练竞赛颇为不同寻常——每队两人，有两道题，且每个参赛者恰好解答其中一道题。当然，同一队的两人会解答不同的题目。

评分规则也非比寻常。第一题始终是一道实现题：你必须非常快速地实现某个知名算法，且打字时间会计入评分。第二题是一道棘手的几何题，你只需在合理时间内使其通过即可。这里，代码的长度和难度很重要。之后，Zibi会为每个解答给出一些罚分（可能为负），团队的最终得分是这些罚分的总和（得分越低越好）。

我们知道，第$i$个参赛者解答第一题时总会得到分数$x_i$，解答第二题时总会得到分数$y_i$。我们可以假设，所有参赛者都了解彼此的技能，并且在竞赛中会以最小化最终得分的方式分配题目。记住，每个人在竞赛中恰好解答一道题。

Zibi希望所有参赛者两两之间都进行一场竞赛。然而，有$m$对人彼此厌恶，绝对不会一起组队竞赛。尽管如此，教练仍打算为所有可能的、彼此不厌恶的两人组合开展训练。教练想知道，对于每个参赛者，他或她在所有参与训练的团队中的得分总和是多少。

## 说明/提示
在第一个示例中，只会有一个由1号和3号组成的团队。他们的最优策略是将第一题分配给3号，第二题分配给1号，这样得分等于$1 + 2 = 3$。

在第二个示例中，没有人喜欢任何人，所以不会有任何训练。看起来在这种情况下Zibi不会获得教练的称号……

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
3 0 3 
```
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
0 0 0 
```
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
4 14 4 16 10 
```

### 算法分类
排序、前缀和、数学

### 题解综合分析与结论
这几道题解思路基本一致，都是基于对两人合作得分公式的推导，得出以$A_i - B_i$（或$B_i - A_i$）为比较条件进行排序，再利用前缀和与后缀和优化计算每个人与其他可合作人的合作价值之和，最后处理不合作的情况。不同之处主要在于代码实现细节，如数据结构的使用、输入输出方式等。

### 所选的题解
 - **作者：Digital_Sunrise（5星）**
    - **关键亮点**：思路清晰，详细推导合作得分的条件，代码注释清晰，使用`map`记录排序后的编号位置，便于处理不合作情况。
    - **重点代码**：
```cpp
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
    - **核心实现思想**：先按`a.x - a.y`排序，计算前缀和`sum1`与后缀和`sum2`，遍历每个人计算其得分，再遍历不合作关系减去相应得分。
 - **作者：liuyz11（4星）**
    - **关键亮点**：代码简洁明了，使用`mp`记录差值，`id`记录排序后位置，直接利用`rep`宏进行循环操作。
    - **重点代码**：
```cpp
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
    - **核心实现思想**：先将`a[i] - b[i]`存入`c`数组并排序，记录排序后位置`id`，计算前缀和与后缀和，遍历计算每个人得分并处理不合作情况。
 - **作者：SunsetSamsara（4星）**
    - **关键亮点**：分析过程详细，先给出前置知识和分析，代码使用`id0`记录原始编号，通过排序后映射到`id`数组，逻辑清晰。
    - **重点代码**：
```cpp
int n, m;
int id0[300010];
int id[300010];
lld x[300010];
lld y[300010];
bool cmp (const int &a, const int b) {
	return x[a] - y[a] < x[b] - y[b];
} 
lld xsum[300010]; 
lld ysum[300010]; 
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
	for (int u, v; m --; ) {
		scanf("%d%d", &u, &v);
		if (id[u] > id[v]) swap(u, v);
		ans[u] -= x[u] + y[v], ans[v] -= x[u] + y[v];
	}
	for (int i = 1; i <= n; ++ i) printf("%lld ", ans[i]);
}
```
    - **核心实现思想**：按`x - y`对编号`id0`排序，映射到`id`数组，计算`x`的前缀和`xsum`与`y`的后缀和`ysum`，遍历计算每个人得分并处理不合作情况。

### 最优关键思路或技巧
1. **排序优化**：通过对$A_i - B_i$（或$B_i - A_i$）进行排序，确定每个人在不同合作组合中的贡献，简化了计算过程。
2. **前缀和与后缀和优化**：利用前缀和与后缀和快速计算特定范围内的总和，避免了每次计算都进行循环累加，降低时间复杂度。
3. **映射处理**：使用`map`或数组记录排序前后的编号映射关系，方便在处理不合作情况时准确找到对应位置。

### 同类型题或类似算法套路拓展
同类型题目通常会涉及到根据某种条件对元素进行排序，再利用前缀和、后缀和等优化手段进行计算，同时可能会有一些限制条件需要额外处理。类似算法套路可应用于一些组队、配对问题，通过对条件的数学推导找到排序依据，进而优化计算。

### 洛谷推荐题目
1. **P1115 最大子段和**：涉及到前缀和思想，通过计算前缀和来优化子段和的计算。
2. **P1993 小K的农场**：需要对给定条件进行数学推导，利用差分约束系统解决问题，与本题对条件的分析推导有相似之处。
3. **P3397 地毯**：运用二维前缀和优化计算，与本题利用前缀和优化计算有类似思路。 

---
处理用时：100.99秒