# 题目信息

# Lightsabers (medium)

## 题目描述

There is unrest in the Galactic Senate. Several thousand solar systems have declared their intentions to leave the Republic. Master Heidi needs to select the Jedi Knights who will go on peacekeeping missions throughout the galaxy. It is well-known that the success of any peacekeeping mission depends on the colors of the lightsabers of the Jedi who will go on that mission.

Heidi has $ n $ Jedi Knights standing in front of her, each one with a lightsaber of one of $ m $ possible colors. She knows that for the mission to be the most effective, she needs to select some contiguous interval of knights such that there are exactly $ k_{1} $ knights with lightsabers of the first color, $ k_{2} $ knights with lightsabers of the second color, $ ... $ , $ k_{m} $ knights with lightsabers of the $ m $ -th color.

However, since the last time, she has learned that it is not always possible to select such an interval. Therefore, she decided to ask some Jedi Knights to go on an indefinite unpaid vacation leave near certain pits on Tatooine, if you know what I mean. Help Heidi decide what is the minimum number of Jedi Knights that need to be let go before she is able to select the desired interval from the subsequence of remaining knights.

## 样例 #1

### 输入

```
8 3
3 3 1 2 2 1 1 3
3 1 1
```

### 输出

```
1
```

# AI分析结果

### 题目内容
# 光剑（中等）

## 题目描述
银河议会中出现了动荡。数千个太阳系已宣布他们打算脱离共和国。海蒂大师需要挑选绝地武士，让他们前往银河系执行维和任务。众所周知，任何维和任务的成功与否，都取决于执行该任务的绝地武士所使用光剑的颜色。

海蒂面前站着 $n$ 名绝地武士，每位武士的光剑颜色是 $m$ 种可能颜色中的一种。她知道，为了使任务达到最佳效果，她需要挑选出一些连续的武士区间，使得其中持有第一种颜色光剑的武士恰好有 $k_1$ 名，持有第二种颜色光剑的武士恰好有 $k_2$ 名，……，持有第 $m$ 种颜色光剑的武士恰好有 $k_m$ 名。

然而，从上次经历后，她明白并非总能选出这样的区间。因此，她决定让一些绝地武士前往塔图因星球某些坑洞附近进行无限期无薪休假（如果你懂我意思的话）。请帮助海蒂确定，在她能够从剩余武士的子序列中选出所需区间之前，最少需要让多少名绝地武士离开。

## 样例 #1
### 输入
```
8 3
3 3 1 2 2 1 1 3
3 1 1
```
### 输出
```
1
```

### 算法分类
双指针（尺取法本质也是双指针的一种应用，因此归类为双指针）

### 综合分析与结论
这两道题解都采用双指针的方法来解决问题，核心思路都是通过移动左右指针来寻找满足条件的连续子串，并计算需要删除的最少元素个数。
- **思路对比**：
    - **XCH_0803的题解**：使用尺取法，通过一个变量 `sum` 记录当前满足颜色数量要求的颜色种类数，当 `sum == m` 时说明找到了满足条件的子串，然后移动左指针尝试寻找更优解。
    - **SunnyYuan的题解**：通过一个变量 `cnt` 记录当前满足颜色数量要求的颜色种类数，在右指针移动过程中，不仅记录满足条件的种类数，还记录多余的元素个数 `sum`，在找到满足条件的子串后，直接更新最小删除元素个数。
- **算法要点对比**：
    - **XCH_0803的题解**：在右指针移动时，判断当前颜色的计数是否达到目标值来更新 `sum`；左指针移动时，判断当前颜色的计数在减1前是否达到目标值，若达到则更新 `sum`。
    - **SunnyYuan的题解**：右指针移动时，判断当前颜色计数与目标值关系，等于目标值更新 `cnt`，大于目标值更新 `sum`；左指针移动时，同样根据当前颜色计数与目标值关系更新 `sum` 和 `cnt`。
- **解决难点对比**：
    - 两者难点都在于如何通过双指针的移动准确找到满足条件的子串，并在过程中正确统计需要删除的元素个数。XCH_0803的题解更侧重于通过 `sum` 来判断子串是否满足条件，而SunnyYuan的题解在判断子串满足条件的同时，还记录了多余元素，在更新最小删除元素个数时更直接。

### 所选的题解
- **XCH_0803的题解**
  - **星级**：3星
  - **关键亮点**：采用尺取法，逻辑较为清晰，通过 `sum` 变量简洁地判断子串是否满足条件。
  - **重点代码**：
```c
while(r<=n&&sum<m){
    c[a[r]]++;
    if(c[a[r]]==b[a[r]]){
        sum++;
    }
    r++;
}
if(sum<m){
    break;
}
MIN=min(MIN,r-l-pp);
if(c[a[l]]==b[a[l]]){
    sum--;
}
c[a[l]]--;
l++;
```
核心实现思想：右指针移动过程中，统计颜色计数，若达到目标值则更新满足条件的颜色种类数；若找到满足条件子串，计算并更新最小删除元素个数，然后移动左指针，若左指针指向颜色计数减1前为目标值，则更新满足条件的颜色种类数。
- **SunnyYuan的题解**
  - **星级**：3星
  - **关键亮点**：在双指针移动过程中，同时记录多余元素个数，在找到满足条件子串时可直接更新最小删除元素个数。
  - **重点代码**：
```cpp
while (r < n && cnt < m) {
    c[a[++r]]++;
    if (c[a[r]] == b[a[r]]) cnt++;
    if (c[a[r]] > b[a[r]]) sum++;
}
if (cnt == m) ans = min(ans, sum);
else break;
if (c[a[l]] > b[a[l]]) sum--;
c[a[l]]--;
if (c[a[l]] < b[a[l]]) cnt--;
```
核心实现思想：右指针移动时，统计颜色计数，若等于目标值更新满足条件的颜色种类数，若大于目标值更新多余元素个数；若找到满足条件子串，更新最小删除元素个数，左指针移动时，根据颜色计数与目标值关系更新多余元素个数和满足条件的颜色种类数。

### 通用建议与扩展思路
对于此类双指针解决子串问题，关键在于明确指针移动的条件以及如何在指针移动过程中维护相关统计信息。可以拓展到其他需要在序列中寻找满足特定条件子串的题目，例如要求子串和等于某个值、子串中不同元素个数满足特定条件等。在解决这类问题时，要清晰定义统计变量，根据题目条件合理移动指针并更新统计变量。

### 洛谷题目推荐
- [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)：同样使用双指针思想，在序列上滑动窗口并维护窗口内的最值。
- [P3957 [NOIP2017 普及组] 跳房子](https://www.luogu.com.cn/problem/P3957)：可以通过双指针优化暴力枚举的复杂度，寻找满足条件的跳跃方案。
- [P2032 扫描线](https://www.luogu.com.cn/problem/P2032)：利用双指针来处理扫描线问题，统计满足条件的区间。 

---
处理用时：51.32秒