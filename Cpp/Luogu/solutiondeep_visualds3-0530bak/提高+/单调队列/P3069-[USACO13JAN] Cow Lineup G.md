# 题目信息

# [USACO13JAN] Cow Lineup G

## 题目描述

Farmer John's N cows (1 <= N <= 100,000) are lined up in a row.  Each cow is identified by an integer "breed ID" in the range 0...1,000,000,000; the breed ID of the ith cow in the lineup is B(i).  Multiple cows can share the same breed ID.

FJ thinks that his line of cows will look much more impressive if there is a large contiguous block of cows that all have the same breed ID.  In order to create such a block, FJ chooses up to K breed IDs and removes from his lineup all the cows having those IDs.  Please help FJ figure out the length of the largest consecutive block of cows with the same breed ID that he can create by doing this.

农夫约翰的N(1 <= N <= 100,000)只奶牛排成了一队，每只牛都用编上了一个“血统编号”，该编号为范围0...1,000,000,000的整数。血统相同的奶牛有相同的编号，也就是可能有多头奶牛是相同的"血统编号"。

约翰觉得如果连续排列的一段奶牛有相同的血统编号的话，奶牛们看起来会更具有威猛。为了创造这样的连续段，约翰最多能选出k种血统的奶牛，并把他们全部从队列中赶走。


请帮助约翰计算这样做能得到的由相同血统编号的牛构成的连续段的长度最大是多少？


## 说明/提示

There are 9 cows in the lineup, with breed IDs 2, 7, 3, 7, 7, 3, 7, 5, 7. FJ would like to remove up to 1 breed ID from this lineup.


By removing all cows with breed ID 3, the lineup reduces to 2, 7, 7, 7, 7, 5, 7.  In this new lineup, there is a contiguous block of 4 cows with the same breed ID (7).


## 样例 #1

### 输入

```
9 1 
2 
7 
3 
7 
7 
3 
7 
5 
7 
```

### 输出

```
4 
```

# AI分析结果



## 唯一算法分类
滑动窗口（双指针）

---

## 题解思路与算法要点

### 核心思路
**滑动窗口法**：维护一个区间，使得区间内血统种类数 ≤k+1。通过双指针动态调整区间范围，统计每个合法区间中当前右端点血统的数量最大值。

**关键步骤**：
1. **离散化**：将大范围的 breed ID 映射到连续整数（部分题解用 map 隐式处理）。
2. **哈希表计数**：用 `map/unordered_map` 或数组记录窗口内各血统出现次数。
3. **种类数控制**：当窗口内血统种类超过 k+1 时，左指针右移直到满足条件。
4. **贪心统计**：每次右指针移动后，仅用当前血统数量更新最大值（基于最优解的右端点特性）。

### 解决难点
- **种类数控制**：通过动态调整左指针确保窗口始终合法。
- **贪心正确性**：最优解的最后一个元素必在窗口右端点，因此只需统计右端点血统数量。
- **离散化优化**：显式离散化后用数组计数，减少哈希操作时间。

---

## 题解评分（≥4星）

1. **NTG_Adiord (4.5星)**
   - **亮点**：代码简洁，离散化与滑动窗口结合紧密。
   - **代码片段**：
     ```cpp
     while(r<=n){
         r++;
         if(hav[a[r]]==0)typ++;
         hav[a[r]]++;
         while(typ==k+2){
             hav[a[l]]--;
             if(hav[a[l]]==0)typ--;
             l++;
         }
         ans=max(ans,hav[a[r]]);
     }
     ```

2. **牛蛙丶丶 (4.5星)**
   - **亮点**：极简实现，直接使用 map 隐式离散化。
   - **代码片段**：
     ```cpp
     while(r<=n){
         if(++g[a[++r]]==1) cnt++;
         while(cnt==k+2)
             if(!(--g[a[l++]])) cnt--;
         ans=max(ans,g[a[r]]);
     }
     ```

3. **Cutest_Junior (4星)**
   - **亮点**：清晰的贪心证明，强调“最优解右端点”特性。
   - **心得引用**：  
     > “贪心正确性：当右指针移动到最优解的最后一个元素时，必然会被统计。”

---

## 最优思路提炼
1. **滑动窗口框架**：左右指针维护合法区间，`O(n)` 时间复杂度。
2. **离散化优化**：显式映射血统 ID 到小范围整数，数组计数比哈希表更快。
3. **贪心统计**：仅需关注右端点血统数量，避免维护全局最大值。

---

## 同类型题推荐
1. **P1886 滑动窗口**（模板题，双指针基础）
2. **P0149 最长无重复子串**（种类数控制为1的特殊情况）
3. **P4071 最大连续1的个数 III**（k次操作将0变1，类似血统删除逻辑）

---

## 可视化算法演示

### 动画方案
1. **元素标记**：
   - 牛队列用不同颜色表示不同血统。
   - 左右指针用红色/蓝色箭头标记。
   - 当前窗口高亮为黄色区域。
2. **动态统计**：
   - 右侧面板显示血统计数表，实时更新。
   - 最大长度用绿色进度条展示。
3. **交互设计**：
   - **步进控制**：支持单步/连续播放，速度可调。
   - **音效反馈**：指针移动触发“滴”声，更新最大值时播放“叮”声。

### 复古像素风格
1. **UI设计**：
   - 8-bit 像素牛图标，血统用不同色块表示。
   - 滑动窗口用闪烁的边框动画。
2. **音效设计**：
   - 背景音乐：FC 风格循环旋律。
   - 关键操作：左移时低音“噗”，右移时高音“啾”。

---

## 核心代码片段（滑动窗口法）
```cpp
#include <cstdio>
#include <map>
using namespace std;

map<int, int> cnt;
int n, k, a[100005], ans;

int main() {
    scanf("%d%d", &n, &k);
    int l = 1, types = 0;
    for (int r = 1; r <= n; ++r) {
        scanf("%d", &a[r]);
        if (cnt[a[r]]++ == 0) types++;
        while (types > k + 1) {
            if (--cnt[a[l]] == 0) types--;
            l++;
        }
        ans = max(ans, cnt[a[r]]);
    }
    printf("%d", ans);
    return 0;
}
```

---

## 个人心得摘录
> “第一次想用树状数组+二分，后来发现滑动窗口只需10行代码。优化方向比实现速度更重要。” —— SBofGaySchool

---

## 算法比较与扩展
- **滑动窗口**：最优解，`O(n)` 时间，适合线性遍历。
- **树状数组+二分**：`O(n log²n)`，适用更复杂统计场景。
- **莫队算法**：分块思想，适合离线查询但本题无需。

---
处理用时：171.60秒