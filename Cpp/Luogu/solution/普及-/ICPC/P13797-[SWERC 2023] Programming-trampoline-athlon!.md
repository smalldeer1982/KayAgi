# [SWERC 2023] Programming-trampoline-athlon!

## 题目描述

:::align{center}

![](https://espresso.codeforces.com/a75009f1d00a17654c89251bd019d39f1ee01d81.png)

![](https://espresso.codeforces.com/ed274bb41d6938a7fe78ee1e6b6f4ec73754aad8.png)

:::



Programming competitions are fun and exciting. Programming should be an Olympic sport! At least, this is what we believe. However, when we suggested this to some of our friends, they did not seem to share our excitement. So, we decided to suggest a combined sport that will be more interesting to watch. Programming-trampoline-athlon! (we are still working on the name.)


The idea is as follows. This is a team sport, where each team comprises of $3$ members. The team has at its disposal $1$ hour, $1$ computer, and $1$ trampoline. At all times, there must be at most one team member using the computer and at least one team member jumping the trampoline. At the beginning of the competition, the team is given $6$ programming problems, and $6$ trampoline elements (exercises). The team decides how to partition the trampoline elements between its members, such that each team member has to perform $2$ of the given elements on the trampoline. The programming tasks are solved cooperatively by the team members, but no one member can spend more than $25$ minutes on the computer in total. The scoring is comprised of two parts, which are added together:

- The programming score ranges between $0$ and $60$. The team receives $10$ points for every correctly solved problem.
- The trampoline score ranges between $0$ and $40$. Each of the $6$ trampoline elements receives a score from the judges that ranges between $0$ and $10$. The final trampoline execution score is determined by dropping the highest and lowest of the $6$ scores, and then adding up the remaining $4$ scores.

Before we pitch this new sport to the International Olympic Committee, we want everything to be ready in order to show them just how serious we are. Thus, each team should receive a medal when no more than two other teams obtained a strictly higher score. However, in order to cope with a recent shortage of medals, the jury was instructed to make sure that there would be no more than $1~000$ teams deserving a medal. We ask you to write a program that determines the medallists, given the performance of the different teams.

## 样例 #1

### 输入

```
5
EMAIL 3 5 6 7 8 9 10
CRASH 2 7 1 8 2 8 1
MOUSE 4 0 9 3 9 1 7
SWERC 6 3 1 4 1 5 9
PAINT 6 0 0 0 0 0 10```

### 输出

```
SWERC 73
EMAIL 60
MOUSE 60
PAINT 60```

## 样例 #2

### 输入

```
4
CRAZY 4 0 2 4 6 8 10
JAZZY 2 9 9 9 9 9 9
JUICY 3 2 9 10 9 10 1
FUZZY 5 0 1 1 2 3 5```

### 输出

```
CRAZY 60
JUICY 60
FUZZY 57```

# 题解

## 作者：imnotcfz (赞：2)

[
![题目 P13797](https://img.shields.io/badge/题目-P13797-blue)
](https://www.luogu.com.cn/problem/P13797)
[
![作者 imnotcfz](https://img.shields.io/badge/作者-imnotcfz-red)
](https://www.luogu.com.cn/user/776004)

## 0x01 分析

一道简单的模拟题，但本蒟蒻调这题调了一整天，心态都崩了，所以下一个章节中会有「进食后人」。

这题主要分为两个部分：**计算分数**和**发奖牌**。

### 计算分数

我们要去掉蹦床的一个最低分和一个最高分，也就是先将 $E$ 数组排个序，然后求第 $2$ 到第 $5$ 个分数的和。

设 $E'$ 为排序后的 $E$ 数组，一个队伍的分数即为 $\displaystyle 10\times P+\sum_{i=2}^{5} E'_i$。

### 发奖牌

根据题目，第 $i$ 个队伍能发到奖牌当且仅当**分数严格更大的队伍数量 $\le2$**，也就是需要计算排名。

所以我们先按分数**从高到低**排个序，然后用 $cnt$ 记录这个值。

通常情况下，$cnt=i$。但分数一样时排名也一样，所以我们只在**当前队伍分数低于上一个队伍**时更新 $cnt$。

## 0x02 实现

需要注意的是题目并没有给出 $n$ 的范围，所以建议使用动态数组 vector，但实测队伍数量不超过 $10^5$。

进食后人：

- 绝对禁止向燃着的酒精灯里添加酒精（动态数组 resize 后不可使用 push_back）。
- 一定要存队伍编号。

Talk is cheap, show me the code!

```cpp line-numbers
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int n;
struct team {
    string c;
    int score, i;

    bool operator <(team other) {
        if (score != other.score) return score > other.score;
        return i < other.i;  // 分数相同一定要按编号排序
    }
};
vector<team> v;

string c;
int p, score;
int e[11];

int main() {
  cin >> n;
  v.resize(n);  // 预先分配空间
  for (int i = 0; i < n; i++) {
    cin >> c >> p;
    for (int j = 1; j <= 6; j++) {
      cin >> e[j];
    }
    sort(e + 1, e + 7);
    score = p * 10 + accumulate(e + 2, e + 6, 0);  // 注：accumulate 出自 <numeric>，默认为求和
    v[i] = {c, score, i};  // resize 之后直接用下标访问，绝对不要用 push_back
  }
  sort(v.begin(), v.end());
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    // 分数一样排名也一样
    if (i == 0 || v[i].score < v[i - 1].score) {
      cnt = i;
    }
    // 这支队伍太菜了，可以退役了
    if (cnt > 2) {
      break;
    }
    cout << v[i].c << ' ' << v[i].score << endl;
  }
  return 0;
}
```

---

