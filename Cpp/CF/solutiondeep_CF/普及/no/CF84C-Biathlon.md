# 题目信息

# Biathlon

## 题目描述

Perhaps many have heard that the World Biathlon Championship has finished. Although our hero Valera was not present at this spectacular event himself and only watched it on TV, it excited him so much that he decided to enroll in a biathlon section.

Of course, biathlon as any sport, proved very difficult in practice. It takes much time and effort. Workouts, workouts, and workouts, — that's what awaited Valera on his way to great achievements in biathlon.

As for the workouts, you all probably know that every professional biathlete should ski fast and shoot precisely at the shooting range. Only in this case you can hope to be successful, because running and shooting are the two main components of biathlon. Valera has been diligent in his ski trainings, which is why he runs really fast, however, his shooting accuracy is nothing to write home about.

On a biathlon base where Valera is preparing for the competition, there is a huge rifle range with $ n $ targets. Each target have shape of a circle, and the center of each circle is located on the $ Ox $ axis. At the last training session Valera made the total of $ m $ shots. To make monitoring of his own results easier for him, one rather well-known programmer (of course it is you) was commissioned to write a program that would reveal how many and which targets Valera hit. More specifically, for each target the program must print the number of the first successful shot (in the target), or "-1" if this was not hit. The target is considered hit if the shot is inside the circle or on its boundary. Valera is counting on you and perhaps, thanks to you he will one day win international competitions.

## 样例 #1

### 输入

```
3
2 1
5 2
10 1
5
0 1
1 3
3 0
4 0
4 0
```

### 输出

```
2
3 3 -1 
```

## 样例 #2

### 输入

```
3
3 2
7 1
11 2
4
2 1
6 0
6 4
11 2
```

### 输出

```
3
1 2 4 
```

# AI分析结果



### 题目翻译

#### 题目名称：Biathlon

### 题目描述

或许很多人都知道，世界冬季两项锦标赛已经结束。尽管我们的英雄瓦列里亚并未亲临这一壮观赛事现场，只是通过电视观看，但这让他兴奋不已，决定报名参加冬季两项训练。

当然，冬季两项作为一项运动，在实践中非常困难，需要大量时间和努力。训练、训练、再训练——这就是瓦列里亚在通往冬季两项伟大成就之路上所面临的一切。

关于训练，你们可能都知道，每位职业冬季两项运动员必须滑雪速度快且射击精准。只有这样才有希望成功，因为滑雪和射击是冬季两项的两大核心。瓦列里亚在滑雪训练中非常刻苦，因此滑得很快，但他的射击精准度却不尽如人意。

在瓦列里亚备战的基地中，有一个巨大的射击场，包含 $n$ 个目标。每个目标的形状为圆形，且圆心位于 $Ox$ 轴上。在最近一次训练中，瓦列里亚共进行了 $m$ 次射击。为了便于监控他的成绩，一位著名程序员（当然是你）被委托编写一个程序，以确定哪些目标被击中以及各自的首次命中射击编号。具体来说，对于每个目标，程序需输出首次命中该目标的射击编号（若未被命中则输出“-1”）。目标被视为被击中当且仅当射击点位于圆内或边界上。

---

### 算法分类
**模拟**

---

### 解题思路与优化

#### 核心逻辑
题目要求对每个目标找到第一次命中的射击编号。直接模拟每个射击点，检查所有未被击中的目标是否被当前射击点命中即可。

#### 关键步骤
1. **数据存储**：保存每个目标的圆心坐标 `x`、半径 `r` 及其原始顺序。
2. **遍历射击点**：按顺序处理每个射击点，若目标未被击中且满足圆内条件，则记录当前射击编号。
3. **条件检查**：对于每个射击点 `(xs, ys)` 和目标 `(x, r)`，检查是否满足 `(xs - x)^2 + ys^2 ≤ r^2`。

#### 优化点
- **提前终止**：若目标的半径平方小于 `ys^2`，直接跳过该目标。
- **标记已命中**：一旦目标被命中，后续射击点无需再检查。

---

### 代码实现

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct Target {
    int x, r, idx;
    bool hit;
};

int main() {
    int n;
    cin >> n;
    vector<Target> targets;
    for (int i = 0; i < n; ++i) {
        int x, r;
        cin >> x >> r;
        targets.push_back({x, r, i, false});
    }
    vector<int> ans(n, -1);
    int hit_count = 0;
    int m;
    cin >> m;
    for (int shot = 1; shot <= m; ++shot) {
        int xs, ys;
        cin >> xs >> ys;
        for (auto& t : targets) {
            if (t.hit) continue;
            long long ys_sq = (long long)ys * ys;
            if (ys_sq > (long long)t.r * t.r) continue;
            long long dx = xs - t.x;
            if (dx * dx + ys_sq <= (long long)t.r * t.r) {
                ans[t.idx] = shot;
                t.hit = true;
                hit_count++;
            }
        }
    }
    cout << hit_count << endl;
    for (auto num : ans) {
        cout << num << " ";
    }
    return 0;
}
```

#### 代码要点
- **结构体存储**：`Target` 结构体保存目标信息及命中状态。
- **长整型防溢出**：使用 `long long` 计算平方防止数据溢出。
- **顺序处理**：按射击顺序逐个处理，确保首次命中记录正确。

---

### 拓展与总结

#### 同类问题推荐
1. **P1355** 射击游戏：二维平面内的动态目标命中检测。
2. **P1030** 线段相交：几何条件判断的模拟问题。
3. **P1663** 激光炸弹：二维前缀和与覆盖问题。

#### 总结
本题通过模拟每个射击点的暴力解法，直接检查目标是否命中。尽管时间复杂度为 $O(nm)$，但适用于数据量较小的场景。核心在于准确处理几何条件判断，并利用标记优化避免重复计算。

---
处理用时：238.90秒