# [ARC026D] 道を直すお仕事

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc026/tasks/arc026_4

 ダイナミック王国には $ N $ 個の村があり、$ 0 $ から $ N-1 $ までの番号がついています。それらの村は $ M $ 本の道でひと繋がりになっていました。「ひと繋がりになっている」とは、どの村からどの村へもいくつかの道を辿って行くことが出来る状態のことを指します。ある日大規模な災害によって全ての道が壊れて、村と村の間の移動が出来なくなってしまいました。あなたは王様の高橋君から、道を修理してダイナミック王国の $ N $ 個の村をひと繋がりにする仕事を依頼されました。

 あなたはまず、それぞれの道を修理するため必要な費用と時間を見積もりました。そして、修理する道を適切に選んだ時の「採算がとれる最低限の時給」の最小値を計算することにしました。「採算がとれる最低限の時給」とは、「道を修理するためにかかる時間の合計」×「時給」が「道を修理するためにかかる費用の合計」と等しくなる時の「時給」の金額の値を指します。

 必ずしも全ての道を修理する必要はないことや、村をひと繋がりにするために必要のない道を修理しても良いことに注意して下さい。

## 说明/提示

### 部分点

 この問題には部分点が設定されている。

- $ M\ ≦\ 16 $ を満たすテストケースすべてに正解した場合は $ 20 $ 点が与えられる。

### Sample Explanation 1

このケースでは、町をひと繋がりにするためには全ての道を修理しなければなりません。全ての道を修理するためにかかる費用の合計が $ 10 $ で時間の合計が $ 5 $ であるため、採算がとれる最低限の時給は $ 2 $ となります。 誤差は $ 10^{-2} $ まで許容されるため、$ 2.01 $ や $ 1.99 $ などと出力しても正解となります。

### Sample Explanation 2

このケースでは、$ 1 $ つ目の道と $ 3 $ つ目の道を修理するときに「採算がとれる最低限の時給」が $ 1.5 $ となり、最小となります。

### Sample Explanation 3

このケースでは、全ての道を修理するときに「採算がとれる最低限の時給」が $ 1.333... $ となり、最小となります。

## 样例 #1

### 输入

```
3 2
0 1 5 3
1 2 5 2```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3
0 1 1 1
1 2 3 1
2 0 2 1```

### 输出

```
1.500```

## 样例 #3

### 输入

```
4 4
0 1 1 1
1 2 1 1
2 0 1 1
0 3 5 3```

### 输出

```
1.3333333```

# 题解

## 作者：_Fatalis_ (赞：14)

根据题目的描述，一条边对 $costperhour'$ 的贡献的多少，可以用 $C/T$ 衡量吗？

---

也许，在一定程度上，是可以对比两条边的贡献。

于是，一开始我便想到一种做法，选择所有 $C_i \le T_i$ 的边，剩余的边再以 $C/T$ 比较跑最小生成树。

能保证正确性的一个显然的结论是：**$C_i \le T_i$ 的所有边总对于贡献为负。**（就是能够让 $costperhour'$ 尽可能小）

但是，这显然是**错**的。反例：对于一条边 $C_i=5, T_i=6$，
$$
\frac{1000}{2000}=0.5<\frac{1005}{2006}\approx0.50009
$$
为什么？有一条式子（不妨 $a/b\le c/d$，等号同时取）：
$$
a/b\le\frac{a+c}{b+d}\le c/d
$$
代入到 $costperhour'$ 的变化，同时设 $costperhour' = c/t$，条件是 $C_i/T_i \le 0$（同 $C_i \le T_i$）。

由于题目并未保证 $c/t \ge 1$，所以有可能有 $c/t < C_i / T_i \le 0$。

所以有：
$$
c/t \le \frac{c + C_i}{t + T_i} \le C_i / T_i
$$
观察到 $costperhour' < costperhour''$（结果变大了，贡献非负）。

所以并不是所有 $C_i \le T_i$ 的边都对贡献为负，还需要判断当前 $costperhour$ 与 $1$ 的大小关系等。

考虑到这不好维护，转换以下思路。

---

不能够通过 $c/t$ 来判断边之间的贡献情况。注意到 $n\le10^4$，可以容下 $n\log^2k$。

如何将判断贡献转换为整式的判断呢？

考虑二分最终 $costperhour$。

但是，我们如何判断一个 $costperhour$（简称为 $cph$） 是否能够被构造出来呢？

由于我们的目标是判断是否能构造 $cph' \le cph$。

$$
cph'= \frac{c'}{t'}
$$
（带 $'$ 表示总和）
$$
\frac{c'}{t'} \le cph
$$
$$
c' \le cph\cdot t'
$$
$$
c' - cph\cdot t'\le 0
$$
那么，处理为整式之后，只需要判断当前选择 $c' - cph \cdot t'$ 之和是否小于等于 $0$ 即可。

通过这个变换可以将判断目标变为正负代价的简单判断。

对于每一条边，我们让 **整合代价** $cph_i' = C_i - cph \cdot T_i$。

若 $cph_i'$ 为负，必然对最终的总代价是好的（目标是非正数嘛）。

那么就可以对边按 $cph_i'$ 排序，选完所有 $cph_i'$ 非正的，最终对正数跑最小生成树即可！

如果跑出的生成树结果与之前选择负数贡献边的贡献之和小于等于 $0$，那么必然可以构造！

注意！这里的判断只能判断对应 $cph$ 能否构造出更小的结果（即只能获得上下界信息），所以才只能二分。

时间复杂度：$O(n\log n \log k), k\to(10^{6})^2 \times 10^4$。（$eps\to10^{-4}$）

```cpp
// Copyright 2022 Lotuses
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define maxn 114514
struct union_find_set { // 并查集模板
    #define min(x, y) (((x) < (y)) ? (x) : (y))
    int fa[maxn];
    void init(int n) {
        for (int i = 0; i <= min(maxn, n); i++) {
            fa[i] = i;
        }
    }
    int find(int x) {
        return fa[x] == x ? x : (fa[x] = find(fa[x]));
    }
    void uni(int x, int y) {
        fa[find(x)] = find(y);
    }
}ufs;

int n, m;
struct Edge {
    int from, to, cost, time, nxt;
};
std::vector<Edge> G[maxn];
std::vector<Edge> GG;
#define eps 1e-4
#define seps 1e-6

std::pair<double, int> ccph[maxn];

bool check(double cph) {
    for (int i = 0; i < m; i++) {
        ccph[i] = std::make_pair(GG[i].cost - cph * GG[i].time, i);
    }
    std::sort(ccph, ccph + m);
    ufs.init(n); int i = 0; double total = 0;
    for (i = 0; i < m && ccph[i].first <= seps; i++) {
        ufs.uni(GG[ccph[i].second].from, GG[ccph[i].second].to);
        total += ccph[i].first;
    }

    for (i; i < m; i++) {
        int fafrom = ufs.find(GG[ccph[i].second].from),
            fato   = ufs.find(GG[ccph[i].second].to);
        if (fafrom != fato) {
            total += ccph[i].first;
            ufs.uni(fafrom, fato);
        }
    }
    return total <= eps;
}

int main() {
    read(n, m);
    for (int i = 0; i < m; i++) {
        static int a, b, c, t;
        read(a, b, c, t);
        Edge e1 = {a, b, c, t, G[b].size()}, 
             e2 = {b, a, c, t, G[a].size()}; // 提前算好
        G[a].push_back(e1);
        G[b].push_back(e2);
        GG.push_back(e1);
    }

    double l = 0, r = 1e13;
    while (fabs(l - r) > eps) {
        double mid = (l + r) / 2;
        bool resu = check(mid);
        if (resu) {
            r = mid;
        } else {
            l = mid;
        }
    }
    printf("%.3lf", l);
    return 0;
}
```

---

说句闲话，AC 这道题的最好方法是：

```cpp
#include<cstdio>
int main(){puts("nan");}
```

By [/record/73889960](/record/73889960)

update: 改了下 $\LaTeX$，删去了一些无用的代码片段 + 翻译

---

## 作者：CWzwz (赞：4)

[ARC026D](https://www.luogu.com.cn/problem/AT_arc026_4) 题解

[AtCoder](https://atcoder.jp/contests/arc026/tasks/arc026_4)

----------

前置知识：01 分数规划，没学的话建议自学后当板子做。

题意：任选选边集 $S$ 使图连通，最小化：

$$\frac{\sum_{i\in S}C_i}{\sum_{i\in S}T_i}$$

发现不好量化每条边的加入对答案的贡献。

（以下省略 $\sum$ 的范围，默认为 $i\in S$）

考虑二分最终答案 $x$，判断是否可以使得这个式子 $<x$。即，我们需要判断，是否可以使得：

$$\frac{\sum C_i}{\sum T_i}<x$$

等价于 

$$\sum C_i<x\sum T_i$$

$$x\sum T_i - \sum C_i >0$$

$$\sum xT_i-C_i>0$$

为了满足上面这个式子，我们需要使**选择的每条边**的新权值 $xT_i-C_i$ 尽量大，然后判断最大值是否大于 $0$ 即可。

对于权值为正的边，显然一定选；选完之后再用最大生成树的思想，把还没连通的地方用负边连起来即可。

这就是 01 分数规划的思想。将不可捉摸的贡献通过实数二分转化为可行性问题，来把每个选择的贡献量化并贪心。

eps 取 1e-3 就行。

[Submission](https://atcoder.jp/contests/arc026/submissions/49660635)

---

