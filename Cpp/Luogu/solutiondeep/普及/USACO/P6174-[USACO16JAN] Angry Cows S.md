# 题目信息

# [USACO16JAN] Angry Cows S

## 题目描述

Bessie 设计了一款新游戏：*Angry Cows*。在这个游戏中，玩家发射奶牛，每头奶牛落地时引爆一定范围内的干草。游戏的目标是使用一组奶牛引爆所有干草。

$N$ 捆干草排列在数轴上的不同位置。第 $i$ 捆干草的的位置为 $x_i$。如果一个威力为 $R$ 的奶牛在 $x$ 位置落地，她将引爆 $[x-R,x+R]$ 范围内的所有干草。

你现在可以发射 $K$ 头奶牛，每头奶牛的威力都是 $R$，现在你需要确定 $R$ 的最小值，使得用 $K$ 头奶牛可以引爆所有干草。

## 样例 #1

### 输入

```
7 2
20
25
18
8
10
3
1```

### 输出

```
5```

# AI分析结果



### 综合分析与结论
本题所有题解均采用二分答案法，核心思路是验证给定R的可行性（check函数）。各题解在实现细节上有以下差异：
1. **贪心策略**：多数题解通过排序后贪心放置奶牛，每次尽可能覆盖最长区间。
2. **优化技巧**：部分题解使用`upper_bound`优化跳跃过程，将check复杂度从O(n)降至O(k log n)。
3. **代码简洁性**：部分实现变量命名清晰、逻辑简练，适合学习。

### 高星题解推荐
#### 1. 作者：guoxinyugz（⭐️⭐️⭐️⭐️⭐️）
**关键亮点**：
- 代码简洁易懂，贪心逻辑清晰。
- 正确初始化`p=-2e9`避免边界问题。
- 附带同类题目推荐（P2678、P2759），拓展性强。

**核心代码**：
```cpp
bool che(int x) {
    int s = 0, p = -2000000000;
    for (int i = 1; i <= n; i++) {
        if (p + x < a[i]) {
            s++;
            p = a[i] + x;
        }
        if (s > k) return 0;
    }
    return 1;
}
```

#### 2. 作者：georgehe（⭐️⭐️⭐️⭐️）
**关键亮点**：
- 使用`upper_bound`优化跳跃，降低时间复杂度。
- 详细注释解释`check`函数逻辑，便于理解。

**个人心得**：
> "调判断函数调了1个小时没调出来...转念一想用`upper_bound`，代码顿时简化。"

**核心代码**：
```cpp
bool check(int r) {
    int pos = 1;
    for (int i = 1; i <= k; i++) {
        pos = upper_bound(hay + pos, hay + n + 1, hay[pos] + 2 * r) - hay;
        if (pos > n) return true;
    }
    return false;
}
```

#### 3. 作者：cyrxdzj（⭐️⭐️⭐️⭐️）
**关键亮点**：
- 变量命名清晰（如`use_cow`、`position`），逻辑易读。
- 明确处理排序必要性，强调关键坑点。

**核心代码**：
```cpp
bool check(int x) {
    int use_cow = 0, position = -0x7fffffff;
    for (int i = 1; i <= n; i++) {
        if (position + x < grass[i]) {
            use_cow++;
            position = grass[i] + x;
            if (use_cow > k) return false;
        }
    }
    return true;
}
```

### 关键思路总结
1. **二分答案框架**：确定答案的单调性后，通过二分缩小范围。
2. **贪心覆盖策略**：排序后每次尽可能右移爆炸点，最大化覆盖范围。
3. **STL优化**：利用`upper_bound`快速定位未覆盖点，提升效率。

### 拓展练习
1. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)（二分答案经典题）
2. [P4344 [SHOI2015] 脑洞治疗仪](https://www.luogu.com.cn/problem/P4344)（二分+线段树）
3. [P1902 刺杀大使](https://www.luogu.com.cn/problem/P1902)（二分答案+网格BFS）

---
处理用时：72.29秒