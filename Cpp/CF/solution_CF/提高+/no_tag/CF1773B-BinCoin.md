# BinCoin

## 题目描述

BinCoin 公司有 $n$ 个员工，编号为 $1$ 到 $n$。公司的从属结构是一棵有根树，换句话说：

- 公司有一个 CEO —— 老板。

- 其他雇员都有一个直系领导。

- 结构中不存在循环。

另外，由于 CEO 对所有二进制物品的迷之喜爱，公司的结构也是一棵二叉树。也就意味着，每个雇员直接领导着其他 $0$ 或 $2$ 个雇员。

在 CEO 的认知中，在该公司工作的危险程度不亚于挖矿。因此，雇员们有时需要签署放弃索赔承诺书。签署过程如下，

首先，CEO 拿着日志，然后递归进行以下步骤：

- 如果拿到日志的雇员没有下属，他们会在日志上签署自己的名字，然后将其归还给直接领导。该过程在日志传递到 CEO 时结束。

- 否则，

	- 该雇员会随机将日志传递给自己两个下属中的任意一个。

	- 从下属手里收回日志后，他会签上自己的名字，又将其递给另一个下属，

	- 当再一次得到日志，就会把它交给自己的直接领导。

而所有随机选择都是独立的。

一天，CEO 忘记了职员们的从属关系结构，幸运的是，他们留有 k 条记录的日志。每条记录都是一个序列，顺序为职员们的签名顺序。

请帮助 CEO 恢复他们的从属关系。

## 样例 #1

### 输入

```
3 50
1 2 3    1 2 3    3 2 1    1 2 3
3 2 1    1 2 3    1 2 3    1 2 3
1 2 3    3 2 1    1 2 3    3 2 1
1 2 3    3 2 1    1 2 3    3 2 1
1 2 3    1 2 3    3 2 1    1 2 3
3 2 1    1 2 3    3 2 1    1 2 3
1 2 3    3 2 1    1 2 3    1 2 3
1 2 3    1 2 3    3 2 1    1 2 3
3 2 1    3 2 1    1 2 3    3 2 1
1 2 3    3 2 1    3 2 1    1 2 3
1 2 3    3 2 1    1 2 3    3 2 1
3 2 1    3 2 1    1 2 3    1 2 3
3 2 1    3 2 1```

### 输出

```
2 -1 2```

## 样例 #2

### 输入

```
5 60
2 4 3 5 1    1 5 2 4 3    1 5 2 4 3
1 5 2 4 3    1 5 3 4 2    1 5 3 4 2
1 5 3 4 2    1 5 3 4 2    1 5 3 4 2
3 4 2 5 1    2 4 3 5 1    1 5 2 4 3
3 4 2 5 1    2 4 3 5 1    2 4 3 5 1
1 5 2 4 3    3 4 2 5 1    3 4 2 5 1
1 5 2 4 3    2 4 3 5 1    1 5 2 4 3
1 5 3 4 2    3 4 2 5 1    1 5 3 4 2
1 5 2 4 3    1 5 3 4 2    1 5 2 4 3
2 4 3 5 1    2 4 3 5 1    2 4 3 5 1
2 4 3 5 1    2 4 3 5 1    1 5 2 4 3
1 5 3 4 2    1 5 2 4 3    3 4 2 5 1
1 5 3 4 2    3 4 2 5 1    3 4 2 5 1
1 5 2 4 3    2 4 3 5 1    1 5 2 4 3
1 5 3 4 2    2 4 3 5 1    2 4 3 5 1
1 5 2 4 3    1 5 2 4 3    1 5 2 4 3
1 5 2 4 3    1 5 2 4 3    3 4 2 5 1
3 4 2 5 1    3 4 2 5 1    1 5 2 4 3
1 5 3 4 2    1 5 3 4 2    2 4 3 5 1
3 4 2 5 1    1 5 2 4 3    3 4 2 5 1```

### 输出

```
5 4 4 5 -1```

# 题解

## 作者：Alex_Wei (赞：3)

问题等价于给出 $k$ 组有根树 $T$ 的优先访问随机儿子的中序遍历 $A_1, A_2, \cdots, A_k$，要求还原 $T$。

考虑定根。如果 $u$ 为根，则 $u$ 在任意 $A_i$ 中不为两端，且两侧集合分别为其两棵子树的所有节点。因此，$u$ 满足如下性质：

- 对于任意 $A_i$，$u$ 不在其两端。
- 对于任意 $A_i$，设 $u$ 两侧集合分别为 $L_i, R_i$，则对于任意 $1\leq i, j\leq k$，要么 $(L_i, R_i) = (L_j, R_j)$，要么 $(L_i, R_i) = (R_j, L_j)$。实际上我们只需用到 $|\bigcup_{i = 1} ^ k \{L_i, R_i\}| = 2$。

因为数据随机，所以其它点极大概率不同时满足这些性质。

定根后递归进入子问题。总共 $\mathcal{O}(n)$ 次定根，$\mathcal{O}(n ^ 2)$ 次检查。单次检查的复杂度为 $\mathcal{O}(nk)$，无法接受。两种方法：

- 预处理后快速求出 $L_i, R_i$ 的 XOR-Hash。
- 先判是否有 $|\bigcup_{i = 1} ^ k \{|L_i|, |R_i|\}| = 2$，若是则进一步检查。

时间复杂度 $\mathcal{O}(n ^ 2k)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using vint = vector<int>;
constexpr int N = 1e3 + 5;
int n, k, p[N], fa[N];
void solve(vector<vint> dat, int ff) {
  int m = dat[0].size();
  if(m == 1) return fa[dat[0][0]] = ff, void();
  vector<vint> pos(k, vint(n + 1));
  for(int i = 0; i < k; i++)
    for(int j = 0; j < m; j++)
      pos[i][dat[i][j]] = j;
  auto split = [&](int u, vint arr, vint &a, vint &b) {
    bool find = 0;
    for(int it : arr)
      if(it == u) find = 1;
      else if(find) b.push_back(it);
      else a.push_back(it);
  };
  auto check = [&](int u) {
    int x = -1, y = -1;
    for(int i = 0, sz; i < k; i++) {
      sz = pos[i][u];
      if(!sz) return false;
      if(x == -1 || x == sz) x = sz;
      else if(y == -1 || y == sz) y = sz;
      else return false;
      sz = m - 1 - sz;
      if(!sz) return false;
      if(x == -1 || x == sz) x = sz;
      else if(y == -1 || y == sz) y = sz;
      else return false;
    }
    vint c, d;
    for(auto &arr : dat) {
      vint a, b;
      split(u, arr, a, b);
      sort(a.begin(), a.end());
      sort(b.begin(), b.end());
      if(c.empty() || c == a) c = a;
      else if(d.empty() || d == a) d = a;
      else return false;
      if(c.empty() || c == b) c = b;
      else if(d.empty() || d == b) d = b;
      else return false;
    }
    return true;
  };
  for(int id : dat[0]) {
    if(!check(id)) continue;
    fa[id] = ff;
    int beg = dat[0][0];
    vector<vint> ldat, rdat;
    for(auto arr : dat) {
      vint a, b;
      split(id, arr, a, b);
      if(find(a.begin(), a.end(), beg) == a.end()) a.swap(b);
      ldat.push_back(a), rdat.push_back(b);
    }
    solve(ldat, id), solve(rdat, id);
  }
}
int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n >> k;
  vector<vector<int>> dat;
  for(int _ = 1; _ <= k; _++) {
    vector<int> arr(n, 0);
    for(int i = 0; i < n; i++) cin >> arr[i];
    dat.push_back(arr);
  }
  solve(dat, -1);
  for(int i = 1; i <= n; i++) cout << fa[i] << (i == n ? '\n' : ' ');
  return 0;
}
/*
g++ B.cpp -o B -std=c++14 -O2 -DALEX_WEI
*/
```

---

## 作者：I_am_Accepted (赞：2)

一场比赛就做两道随，队友都在 D 我。

每次找到区间内的根递归即可。

当区间长度 $>1$ 的时候，根为所有序列中其两侧元素集合均非空且相同（两侧可以交换），错误率 $2^{-50}$。

判集合相等可以用 Hash，我这里用了异或、和、平方和就过了。

时间复杂度 $O(n^2)$。

---

