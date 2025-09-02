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



**唯一算法分类**：滑动窗口（双指针）

---

### **题解思路与算法要点**

**核心思路**  
题目要求删除最多k种血统后，找到最长的连续同血统段。通过分析，可以将问题转化为：维护一个窗口（区间），窗口内最多包含 `k+1` 种血统（删掉k种后保留一种）。在窗口滑动过程中，统计每个血统的出现次数，并记录最大值。

**解决难点**  
1. **种类统计与窗口维护**：需快速统计窗口内的血统种类数，并在超过 `k+1` 时调整左指针。
2. **高效计数**：直接遍历窗口内元素会导致高复杂度，需用哈希表（或离散化数组）实时记录各血统的出现次数。
3. **最大值更新**：每次右指针移动时，更新当前血统的计数，并比较是否为最大值。

**关键步骤**  
1. **双指针滑动窗口**：右指针不断右移，将新血统加入窗口。
2. **种类超限处理**：当血统种类超过 `k+1` 时，左指针右移直至种类数合法。
3. **动态统计最大值**：每次右指针移动后，用当前血统的出现次数更新答案。

---

### **题解评分 (≥4星)**

1. **NTG_Adiord（5星）**  
   - **亮点**：使用离散化优化内存，代码简洁，逻辑清晰。  
   - **代码可读性**：结构清晰，注释明确。  
   - **核心代码**：  
     ```cpp
     while (r <= n) {
         r++;
         if (hav[a[r]] == 0) typ++;
         hav[a[r]]++;
         while (typ == k+2) {
             hav[a[l]]--;
             if (hav[a[l]] == 0) typ--;
             l++;
         }
         ans = max(ans, hav[a[r]]);
     }
     ```

2. **牛蛙丶丶（5星）**  
   - **亮点**：直接使用 `map` 简化离散化步骤，代码更短。  
   - **核心代码**：  
     ```cpp
     while (r <= n) {
         if (++g[a[++r]] == 1) cnt++;
         while (cnt == k+2)
             if (!(--g[a[l++]])) cnt--;
         ans = max(ans, g[a[r]]);
     }
     ```

3. **1saunoya（4星）**  
   - **亮点**：代码简洁，未显式离散化，但逻辑一致。  
   - **核心代码**：  
     ```cpp
     while (r <= n) {
         if (++cnt[a[++r]] == 1) kind++;
         while (kind == k+2)
             if (--cnt[a[l++]] == 0) kind--;
         ans = max(ans, cnt[a[r]]);
     }
     ```

---

### **最优思路提炼**

1. **滑动窗口维护种类数**  
   窗口内最多允许 `k+1` 种血统，通过哈希表实时统计各血统出现次数。
2. **贪心更新最大值**  
   每次右指针移动时，当前血统的出现次数可能为窗口内最大值，直接更新全局最大值。
3. **离散化优化**  
   当血统编号范围过大时，离散化可降低空间复杂度。

---

### **同类型题与算法套路**

- **滑动窗口/双指针**：适用于求满足条件的连续区间极值问题。  
- **哈希表辅助计数**：实时统计元素频率或种类数。  
- **同类型题目**：  
  1. **P1886** 滑动窗口模板题。  
  2. **P1638** 逛画展（求最小覆盖所有种类的窗口）。  
  3. **P4071** 排列计数（需结合组合数学与滑动窗口）。

---

### **可视化与算法演示**

**动画设计**  
1. **像素风格界面**：  
   - 牛队列以不同颜色方块表示不同血统，窗口左右指针为闪烁箭头。  
   - 右侧面板显示哈希表实时计数和当前最大值。  
2. **关键操作高亮**：  
   - 右指针右移时，新方块加入窗口，对应血统计数+1。  
   - 当血统种类超过 `k+1`，左指针右移，对应计数-1。  
3. **音效与交互**：  
   - 移动指针时触发“滴”声，更新最大值时播放上扬音效。  
   - 支持暂停/步进，观察哈希表变化。

**复古游戏化实现**  
```javascript
// 伪代码示例：Canvas绘制滑动窗口
function drawFrame() {
    clearCanvas();
    for (let i = 0; i < cows.length; i++) {
        drawCow(i, cows[i].type); // 绘制牛方块
        if (i >= left && i <= right) drawHighlight(i); // 高亮窗口
    }
    updateHashTable(); // 显示当前哈希表计数
    playStepSound(); // 步进音效
}
```

---

### **个人心得摘录**

- **NTG_Adiord**：  
  > “一开始看这道题是蓝的，打算先放放，但发现核心只是滑动窗口。”  
  - 提示：不要被题目难度标签吓退，仔细分析后可能发现经典算法套路。

- **Cutest_Junior**：  
  > “贪心正确性证明：以每头牛结尾的区间，其血统的出现次数会被正确捕捉。”  
  - 强调贪心策略的可行性需严格验证。

---

### **核心代码实现（滑动窗口）**

```cpp
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int n, k, ans = 0;
    cin >> n >> k;
    int a[n + 1];
    unordered_map<int, int> cnt;
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    int left = 1, types = 0;
    for (int right = 1; right <= n; right++) {
        if (cnt[a[right]]++ == 0) types++;
        while (types > k + 1) {
            if (--cnt[a[left]] == 0) types--;
            left++;
        }
        ans = max(ans, cnt[a[right]]);
    }
    cout << ans;
    return 0;
}
```

---

**总结**：滑动窗口法是本题最优解，时间复杂度为 `O(n)`，空间复杂度 `O(k)`。通过实时统计窗口内血统种类和贪心更新最大值，高效解决问题。

---
处理用时：170.67秒