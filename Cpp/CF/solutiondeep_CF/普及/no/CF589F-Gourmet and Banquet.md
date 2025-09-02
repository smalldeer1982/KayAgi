# 题目信息

# Gourmet and Banquet

## 题目描述

A gourmet came into the banquet hall, where the cooks suggested $ n $ dishes for guests. The gourmet knows the schedule: when each of the dishes will be served.

For $ i $ -th of the dishes he knows two integer moments in time $ a_{i} $ and $ b_{i} $ (in seconds from the beginning of the banquet) — when the cooks will bring the $ i $ -th dish into the hall and when they will carry it out ( $ a_{i}&lt;b_{i} $ ). For example, if $ a_{i}=10 $ and $ b_{i}=11 $ , then the $ i $ -th dish is available for eating during one second.

The dishes come in very large quantities, so it is guaranteed that as long as the dish is available for eating (i. e. while it is in the hall) it cannot run out.

The gourmet wants to try each of the $ n $ dishes and not to offend any of the cooks. Because of that the gourmet wants to eat each of the dishes for the same amount of time. During eating the gourmet can instantly switch between the dishes. Switching between dishes is allowed for him only at integer moments in time. The gourmet can eat no more than one dish simultaneously. It is allowed to return to a dish after eating any other dishes.

The gourmet wants to eat as long as possible on the banquet without violating any conditions described above. Can you help him and find out the maximum total time he can eat the dishes on the banquet?

## 说明/提示

In the first example the gourmet eats the second dish for one second (from the moment in time 1 to the moment in time 2), then he eats the first dish for two seconds (from 2 to 4), then he returns to the second dish for one second (from 4 to 5). After that he eats the third dish for two seconds (from 6 to 8).

In the second example the gourmet cannot eat each dish for at least one second because there are three dishes but they are available for only one second (from 1 to 2).

## 样例 #1

### 输入

```
3
2 4
1 5
6 9
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3
1 2
1 2
1 2
```

### 输出

```
0
```

# AI分析结果



# 题目中文翻译
## 题目名称：美食家与宴会

### 题目描述

一位美食家进入宴会厅，厨师们为宾客准备了 $n$ 道菜品。美食家知道每道菜的上菜时间表。

对于第 $i$ 道菜，他知道两个整数时间点 $a_i$ 和 $b_i$（从宴会开始后的秒数），分别表示该菜品被送入宴会厅和撤走的时间（$a_i < b_i$）。例如，若 $a_i=10$ 且 $b_i=11$，则第 $i$ 道菜仅在 10 秒到 11 秒之间可用（持续 1 秒）。

所有菜品的供应量极大，只要在可用时间内，菜品不会耗尽。

美食家希望品尝每一道菜且不冒犯厨师，因此要求每道菜品尝的时间相同。他可以在整数时间点瞬间切换菜品，但不能同时吃多道菜。允许吃完其他菜后重新返回某道菜。

求美食家能满足条件的最大总品尝时间（每道菜时间 × 菜品数）。

---

**算法分类**：二分

---

## 题解分析与结论

### 核心思路
1. **二分答案**：通过二分确定每道菜可分配的最大时间 `t`，总时间为 `t*n`。
2. **贪心验证**：对按左端点排序后的区间，用 `vis` 数组标记已用时间点，确保每个区间能选出 `t` 个不冲突的时间点。

### 最优题解

#### 题解作者：Dehydration（★★★★☆）
**关键亮点**：
1. 正确的时间区间处理（左闭右开），判断条件 `a[i].b - a[i].a < time_per_dish` 直接验证区间总时长。
2. 代码简洁，逻辑清晰，通过标记 `vis` 数组避免时间点冲突。

**核心代码**：
```cpp
bool check(int time_per_dish) {
    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= N; i++) {
        if (a[i].b - a[i].a < time_per_dish) return false;
        int occupy = 0;
        for (int j = a[i].a; j < a[i].b; j++) { // 左闭右开处理
            if (!vis[j]) {
                occupy++;
                vis[j] = true;
                if (occupy == time_per_dish) break;
            }
        }
        if (occupy < time_per_dish) return false;
    }
    return true;
}
```

---

### 优化技巧总结
- **时间离散化**：若时间范围过大，可用离散化压缩时间点。
- **贪心优化**：按左端点排序后，维护当前可用时间起点，避免全量遍历时间点，将复杂度优化至 $O(n \log T)$。

---

### 类似题目推荐
1. [P1083 借教室](https://www.luogu.com.cn/problem/P1083)（二分+差分）
2. [P1281 独木桥](https://www.luogu.com.cn/problem/P1281)（贪心决策）
3. [P4344 [SHOI2015] 脑洞治疗仪](https://www.luogu.com.cn/problem/P4344)（区间覆盖与二分）

---
处理用时：248.14秒