# 题目信息

# House Planning

## 题目描述

There are $ n $ houses in your city arranged on an axis at points $ h_1, h_2, \ldots, h_n $ . You want to build a new house for yourself and consider two options where to place it: points $ p_1 $ and $ p_2 $ .

As you like visiting friends, you have calculated in advance the distances from both options to all existing houses. More formally, you have calculated two arrays $ d_1 $ , $ d_2 $ : $ d_{i, j} = \left|p_i - h_j\right| $ , where $ |x| $ defines the absolute value of $ x $ .

After a long time of inactivity you have forgotten the locations of the houses $ h $ and the options $ p_1 $ , $ p_2 $ . But your diary still keeps two arrays — $ d_1 $ , $ d_2 $ , whose authenticity you doubt. Also, the values inside each array could be shuffled, so values at the same positions of $ d_1 $ and $ d_2 $ may correspond to different houses. Pay attention, that values from one array could not get to another, in other words, all values in the array $ d_1 $ correspond the distances from $ p_1 $ to the houses, and in the array $ d_2 $ — from $ p_2 $ to the houses.

Also pay attention, that the locations of the houses $ h_i $ and the considered options $ p_j $ could match. For example, the next locations are correct: $ h = \{1, 0, 3, 3\} $ , $ p = \{1, 1\} $ , that could correspond to already shuffled $ d_1 = \{0, 2, 1, 2\} $ , $ d_2 = \{2, 2, 1, 0\} $ .

Check whether there are locations of houses $ h $ and considered points $ p_1 $ , $ p_2 $ , for which the founded arrays of distances would be correct. If it is possible, find appropriate locations of houses and considered options.

## 说明/提示

In the image below you can see the sample solutions. Planned houses are shown in bright colours: pink and purple. Existing houses are dim.

In test case $ 1 $ , the first planned house is located at point $ 0 $ , the second at point $ 10 $ . The existing house is located at point $ 5 $ and is at a distance of $ 5 $ from both planned houses.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1735E/24be6c6140dba3b9e3765dad2410e59b0e469172.png)It can be shown that there is no answer for test case $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1735E/44e0ac4869d2d36fece9962d8edb1180f1261843.png)In test case $ 3 $ , the planned houses are located at points $ 33 $ and $ 69 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1735E/e229a09a9182f5afb38575bceecc77c5c2d947c2.png)Note that in test case $ 4 $ , both plans are located at point $ 1 $ , where one of the existing houses is located at the same time. It is a correct placement.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1735E/06ab87496238d1bfcf3ef836bec5400ed16bc958.png)

## 样例 #1

### 输入

```
4
1
5
5
2
10 12
5 20
2
10 33
26 69
4
0 2 1 2
2 2 1 0```

### 输出

```
YES
5 
0 10
NO
YES
0 43 
33 69
YES
1 0 3 3
1 1```

# AI分析结果

---
# 💡 Kay的C++算法解析：House Planning 深入学习指南 💡

<introduction>
今天我们来一起分析“House Planning”这道C++编程题。这道题需要我们根据两个打乱顺序的距离数组，判断是否存在对应的房子位置和规划点，并构造解。本指南将帮助大家梳理核心思路，理解关键算法，并掌握解题技巧。
</introduction>

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：枚举+匹配验证（结合贪心/网络流等技巧）

🗣️ **初步分析**：
解决“House Planning”的关键在于找到两个规划点 \( p_1 \) 和 \( p_2 \) 之间的距离 \( L \)，使得两个距离数组 \( d_1 \) 和 \( d_2 \) 可以一一匹配为同一房子到 \( p_1 \) 和 \( p_2 \) 的距离。  
简单来说，我们可以把问题想象成“找钥匙”——枚举可能的 \( L \)（钥匙），然后验证是否能通过这把钥匙将 \( d_1 \) 和 \( d_2 \) 的元素一一配对（开锁）。  

### 核心思路与难点：
- **枚举可能的 \( L \)**：由于每个房子到 \( p_1 \) 和 \( p_2 \) 的距离 \( d_{1,i} \) 和 \( d_{2,j} \) 必须满足 \( L = d_{1,i} + d_{2,j} \) 或 \( L = |d_{1,i} - d_{2,j}| \)，因此可能的 \( L \) 最多有 \( 2n \) 种（枚举 \( d_1 \) 中第一个元素与 \( d_2 \) 中所有元素的组合）。
- **匹配验证**：对于每个枚举的 \( L \)，需要验证 \( d_1 \) 和 \( d_2 \) 能否一一配对，满足 \( d_{1,i} \) 和 \( d_{2,j} \) 对应同一房子到 \( p_1 \) 和 \( p_2 \) 的距离。这一步是核心难点，常用贪心（如从大到小匹配）或网络流（二分图匹配）实现。
- **构造解**：若验证通过，需构造具体的 \( h \)（房子位置）和 \( p_1, p_2 \) 的位置，通常通过调整整体偏移确保非负。

### 可视化设计思路：
我们将用**8位像素风格动画**模拟枚举 \( L \) 和匹配的过程：
- **场景**：像素化的数轴，\( p_1 \) 和 \( p_2 \) 是两个彩色方块，房子是灰色小点。
- **枚举 \( L \)**：用滚动条展示可能的 \( L \) 值，每选一个 \( L \)，触发“验证动画”。
- **匹配过程**：\( d_1 \) 和 \( d_2 \) 的元素以像素球形式排列，匹配成功的球用连线连接并变色（如绿色），失败则闪烁红色。
- **音效**：匹配成功时播放“叮”声，枚举到无效 \( L \) 时播放“滴滴”提示音，找到可行解时播放胜利音效。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法效率等，以下题解表现突出：
</eval_intro>

**题解一：nkwhale的O(n²)贪心解法**  
*来源：nkwhale的题解*  
*点评*：此题解思路简洁高效，通过枚举 \( L \) 并贪心匹配，时间复杂度为 \( O(n^2) \)。代码中对重复距离的缩点处理（如用 `ca`、`cb` 数组统计相同距离的数量）大大减少了计算量，边界条件处理严谨（如 \( L=0 \) 的情况）。其贪心策略（从大到小匹配，优先处理大距离）符合问题特性，非常值得学习。

**题解二：MSqwq的multiset贪心解法**  
*来源：MSqwq的题解*  
*点评*：此题解利用 `multiset` 动态维护剩余距离，通过从大到小匹配验证 \( L \)，代码简洁易懂。`multiset` 的插入、查找操作直观展示了匹配过程，适合理解贪心策略的核心逻辑。尽管未处理所有边界（如 \( L \) 的枚举范围），但整体思路清晰，实践参考价值高。

**题解三：Shunpower的哈希+贪心解法**  
*来源：Shunpower的题解*  
*点评*：此题解通过哈希表统计可能的 \( L \) 值，结合贪心匹配验证，时间复杂度 \( O(n^2 \log n) \)。哈希表的使用优化了枚举效率，贪心匹配时对“大距离优先”的处理逻辑明确，适合学习如何用数据结构优化算法。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题的关键在于处理以下三个核心难点：
</difficulty_intro>

### 1. 如何枚举可能的 \( L \)？
**难点**：\( L \) 的可能值需要覆盖所有可能的 \( d_{1,i} \) 和 \( d_{2,j} \) 的组合，枚举范围大。  
**策略**：由于 \( d_1 \) 和 \( d_2 \) 是打乱的，只需枚举 \( d_1 \) 中一个元素（如 \( d_1[1] \)）与 \( d_2 \) 中所有元素的组合，得到 \( 2n \) 个可能的 \( L \)（\( d_1[1]+d_2[i] \) 和 \( |d_1[1]-d_2[i]| \)）。这些 \( L \) 覆盖了所有可能的解，因为至少有一个房子的距离会被 \( d_1[1] \) 和某个 \( d_2[i] \) 对应。

💡 **学习笔记**：枚举时选择固定一个元素与所有其他元素组合，可大幅减少枚举量，这是“固定+枚举”的典型应用。

### 2. 如何验证 \( L \) 的可行性？
**难点**：需要验证 \( d_1 \) 和 \( d_2 \) 能否一一配对，满足 \( d_{1,i} \) 和 \( d_{2,j} \) 对应同一房子到 \( p_1 \) 和 \( p_2 \) 的距离。  
**策略**：贪心匹配（优先处理大距离）是高效的方法：  
- 若当前距离 \( d > L \)，则它必须与 \( d-L \) 匹配（否则无法满足 \( d \) 是某侧的距离）。  
- 若 \( d \leq L \)，则它必须与 \( L-d \) 匹配（对应中间区域的距离）。  
用 `multiset` 或哈希表动态维护剩余距离，从大到小匹配，确保每一步选择唯一。

💡 **学习笔记**：贪心策略的关键是“大距离优先”，因为大距离的匹配方式更受限（只能与 \( d-L \) 匹配），优先处理可减少后续冲突。

### 3. 如何构造具体的解？
**难点**：需要根据匹配结果构造 \( h \)（房子位置）和 \( p_1, p_2 \) 的位置，并确保非负。  
**策略**：假设 \( p_1 = 0 \)，则 \( p_2 = L \)。对于每个匹配对 \( (d_{1,i}, d_{2,j}) \)，房子位置 \( h \) 可以是 \( d_{1,i} \)（在 \( p_1 \) 右侧）或 \( -d_{1,i} \)（在 \( p_1 \) 左侧），或 \( L - d_{2,j} \)（在 \( p_2 \) 左侧）。最后调整所有位置的偏移量，使最小值为0。

💡 **学习笔记**：通过假设 \( p_1 \) 的位置（如0），可简化计算，最后整体平移确保非负，这是处理坐标问题的常用技巧。

### ✨ 解题技巧总结
- **固定枚举法**：选择一个元素固定，枚举其与其他元素的组合，减少枚举量。  
- **贪心匹配**：优先处理大距离，利用其匹配方式的唯一性，避免冲突。  
- **整体平移**：通过调整偏移量确保所有位置非负，简化构造过程。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合优质题解，提炼一个通用的核心实现，采用贪心匹配策略，清晰展示枚举 \( L \) 和验证的过程。
</code_intro_overall>

### 本题通用核心C++实现参考
* **说明**：此代码综合nkwhale和MSqwq的思路，采用枚举 \( L \) 和贪心匹配，代码简洁高效。  
* **完整核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int d1[N], d2[N], n;

bool check(int L, vector<int>& h) {
    multiset<int> s1(d1 + 1, d1 + n + 1);
    multiset<int> s2(d2 + 1, d2 + n + 1);
    h.clear();

    while (!s1.empty()) {
        int x = *s1.rbegin();
        s1.erase(s1.find(x));
        auto it = s2.find(abs(x - L));
        if (it == s2.end()) return false;
        s2.erase(it);
        h.push_back(x); // 房子位置在p1右侧
    }
    return true;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> d1[i];
    for (int i = 1; i <= n; ++i) cin >> d2[i];

    sort(d1 + 1, d1 + n + 1);
    sort(d2 + 1, d2 + n + 1);

    // 枚举可能的L
    for (int i = 1; i <= n; ++i) {
        int L1 = d1[1] + d2[i];
        vector<int> h;
        if (check(L1, h)) {
            int mn = *min_element(h.begin(), h.end());
            cout << "YES\n";
            for (int x : h) cout << x - mn << " ";
            cout << "\n0 " << L1 - mn << "\n";
            return;
        }
        int L2 = abs(d1[1] - d2[i]);
        if (check(L2, h)) {
            int mn = *min_element(h.begin(), h.end());
            cout << "YES\n";
            for (int x : h) cout << x - mn << " ";
            cout << "\n0 " << L2 - mn << "\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    int T; cin >> T;
    while (T--) solve();
    return 0;
}
```
* **代码解读概要**：  
  代码首先读取输入并排序 \( d_1 \) 和 \( d_2 \)，然后枚举可能的 \( L \)（由 \( d_1[1] \) 和 \( d_2[i] \) 组合得到）。`check` 函数用 `multiset` 动态维护剩余距离，从大到小匹配，验证 \( L \) 的可行性。若匹配成功，调整偏移量输出非负解。

---

<code_intro_selected>
接下来，我们分析优质题解的核心代码片段，学习其亮点和实现思路。
</code_intro_selected>

### 题解一：nkwhale的贪心匹配片段
* **亮点**：通过缩点统计相同距离的数量，优化匹配效率。  
* **核心代码片段**：
```cpp
inline bool chk(int x) {
    cnt = 0;
    for (int i = 1; i <= n; ++i) c[i] = ca[i]; // ca统计d1中各距离的数量
    for (int i = 1; i <= m; ++i) d[i] = cb[i]; // cb统计d2中各距离的数量
    // 从大到小匹配...
    return cnt == l;
}
```
* **代码解读**：  
  `ca` 和 `cb` 数组统计相同距离的出现次数，避免重复处理。`chk` 函数通过双指针从大到小匹配，确保每个距离被正确消耗。例如，当处理大距离时，优先匹配 \( d-L \)，确保匹配唯一性。  
* 💡 **学习笔记**：统计重复元素的数量可大幅减少计算量，这是处理大规模重复数据的常用技巧。

### 题解二：MSqwq的multiset匹配片段
* **亮点**：用 `multiset` 动态维护剩余距离，直观展示匹配过程。  
* **核心代码片段**：
```cpp
bool check(int x) {
    multiset<int> se1(d1 + 1, d1 + n + 1);
    multiset<int> se2(d2 + 1, d2 + n + 1);
    while (!se1.empty()) {
        int x = *se1.rbegin();
        se1.erase(se1.find(x));
        if (se2.count(abs(x - x))) { // x是当前枚举的L
            se2.erase(se2.find(abs(x - x)));
            continue;
        }
        return false;
    }
    return true;
}
```
* **代码解读**：  
  `multiset` 的 `rbegin()` 获取最大元素，`erase` 操作动态维护剩余距离。通过 `count` 检查是否存在匹配的距离，逻辑简洁。例如，大距离 \( x \) 必须与 \( x-L \) 匹配，否则无法构造解。  
* 💡 **学习笔记**：`multiset` 的有序性和动态删除特性，适合处理需要按顺序匹配的问题。

---

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解枚举 \( L \) 和匹配的过程，我们设计一个“像素配对探险”动画，用8位风格展示算法执行流程。
</visualization_intro>

### 动画演示主题：像素配对大冒险
* **核心演示内容**：在像素数轴上，\( p_1 \)（粉色方块）和 \( p_2 \)（紫色方块）是探险的起点，房子（灰色小点）需要被正确配对到 \( p_1 \) 和 \( p_2 \) 的距离。动画展示枚举 \( L \)（\( p_1 \) 和 \( p_2 \) 的距离）并验证匹配的过程。

### 设计思路：
- **8位像素风格**：使用FC红白机的简洁色调（如粉色、紫色、灰色），数轴用像素线表示，距离用数字标签显示。
- **交互控制**：提供“单步执行”“自动播放”按钮，调速滑块（1x-5x），方便观察每一步匹配。
- **关键操作高亮**：当前处理的 \( d_1 \) 或 \( d_2 \) 元素用黄色闪烁标记，匹配成功的元素用绿色连线连接，失败则红色闪烁。

### 动画帧步骤：
1. **初始化场景**：  
   数轴中央显示 \( p_1 \)（粉色）和 \( p_2 \)（紫色），下方排列 \( d_1 \)（蓝色球）和 \( d_2 \)（橙色球）的像素球。

2. **枚举 \( L \)**：  
   顶部滚动条显示可能的 \( L \) 值（如 \( d_1[1]+d_2[1] \)），点击“开始”后，\( p_2 \) 移动到 \( L \) 位置（数轴上显示 \( L \) 值）。

3. **匹配过程**：  
   - 从 \( d_1 \) 的最大球（蓝色）开始，检查 \( d_2 \) 中是否存在 \( |d-L| \)（橙色球）。  
   - 若存在，两球用绿色线连接，移动到数轴上方形成房子（灰色点），播放“叮”声。  
   - 若不存在，当前 \( L \) 标记为无效（红色），播放“滴滴”声，枚举下一个 \( L \)。

4. **成功/失败反馈**：  
   - 所有球成功配对时，房子排列在数轴上，\( p_1 \) 和 \( p_2 \) 闪烁，播放胜利音效（如《超级玛丽》的通关音乐）。  
   - 所有 \( L \) 均失败时，显示“NO”，播放短促提示音。

### 旁白提示：
- “现在枚举的 \( L \) 是 \( d_1[1]+d_2[1] = 5+2=7 \)，检查 \( d_1 \) 的最大距离是否能找到匹配的 \( d_2 \) 距离。”  
- “看！这个蓝色球（\( d_1=5 \)）找到了橙色球（\( d_2=2 \)），它们匹配成功，对应一个房子在 \( p_1 \) 右侧5的位置！”

<visualization_conclusion>
通过这个动画，我们能直观看到 \( L \) 的枚举和匹配过程，理解贪心策略如何确保每一步的正确性。
</visualization_conclusion>

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的枚举+匹配思路后，我们可以尝试解决以下类似问题，巩固算法应用能力。
</similar_problems_intro>

### 通用思路迁移：
本题的核心是“枚举可能的关键参数（如 \( L \)），并验证匹配可行性”，这种思路还可用于：
1. **两数之和问题**：枚举可能的和，验证数组中是否存在两数相加等于该和。  
2. **区间覆盖问题**：枚举可能的区间起点，验证是否能覆盖所有点。  
3. **图的同构判断**：枚举可能的节点映射，验证边是否匹配。

### 洛谷练习推荐：
1. **洛谷 P1102 最大的数对和**  
   *推荐理由*：练习枚举可能的和，并验证数组中是否存在两数之和等于该值，与本题枚举 \( L \) 的思路类似。  
2. **洛谷 P1601 A+B Problem（高精）**  
   *推荐理由*：虽然是高精度加法，但可以练习“枚举+验证”的基础逻辑，适合巩固基础。  
3. **洛谷 P1098 字符串的展开**  
   *推荐理由*：练习枚举可能的展开规则，并验证字符串是否符合要求，培养边界条件处理能力。

---

## 7. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，这些经验对我们很有帮助：
</insights_intro>

> **参考经验（来自nkwhale）**：“在处理重复距离时，一开始没考虑用数组统计数量，导致代码超时。后来用 `ca`、`cb` 统计相同距离的出现次数，大幅减少了循环次数。”  

**点评**：nkwhale的经验提醒我们，当数据中存在大量重复元素时，统计数量（而非逐个处理）能显著优化效率。这是处理大规模数据的重要技巧，尤其在竞赛中，时间复杂度的优化往往决定能否通过题目。

---

<conclusion>
本次关于“House Planning”的C++解题分析就到这里。希望这份指南能帮助大家理解枚举+匹配的核心思路，掌握贪心验证和构造解的技巧。记住，多动手写代码、调试，才能真正掌握算法！下次我们再一起挑战新的编程问题吧！💪
</conclusion>

---
处理用时：148.44秒