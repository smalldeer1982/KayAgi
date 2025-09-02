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

### **题解思路、算法要点与解决难点**

1. **核心思路**  
   - **关键推导**：允许保留最多 `k+1` 种血统（删除 `k` 种），滑动窗口维护当前区间内的血统种类数。若种类超过 `k+1`，左指针右移收缩窗口。
   - **数据结构**：使用 `map` 或数组统计窗口内各血统的出现次数，动态更新种类数。
   - **离散化**：血统 ID 范围大（`1e9`），需离散化为连续整数（如 `map` 或排序后 `lower_bound`）。

2. **解决难点**  
   - **高效维护种类数**：当血统出现次数从 `0→1` 时种类数 `+1`，从 `1→0` 时 `-1`。
   - **答案更新策略**：贪心记录当前右端点血统的最大数量（最优解必然以某个右端点为终点）。

---

### **题解评分 (≥4星)**

| 作者          | 评分 | 亮点                                                                 |
|---------------|------|----------------------------------------------------------------------|
| 牛蛙丶丶      | ⭐⭐⭐⭐ | 代码简洁，双指针逻辑清晰，直接维护 `map` 统计次数。                   |
| 1saunoya      | ⭐⭐⭐⭐ | 最短实现，无冗余步骤，直接映射计数。                                  |
| heyuhhh       | ⭐⭐⭐⭐ | 离散化预处理，滑动窗口与贪心结合，代码可读性强。                      |

---

### **最优思路或技巧提炼**

1. **滑动窗口框架**  
   ```cpp
   int l = 1, ans = 0, kind = 0;
   for (int r = 1; r <= n; r++) {
       if (cnt[a[r]]++ == 0) kind++;       // 新种类
       while (kind > k + 1) {             // 超限时左移
           if (--cnt[a[l]] == 0) kind--;
           l++;
       }
       ans = max(ans, cnt[a[r]]);         // 更新答案
   }
   ```

2. **离散化技巧**  
   ```cpp
   map<int, int> mp;  // 血统ID → 连续整数
   for (int i = 1; i <= n; i++) {
       if (!mp.count(a[i])) mp[a[i]] = ++mxl;
       a[i] = mp[a[i]];  // 替换为离散化后的值
   }
   ```

---

### **同类型题或算法套路**

- **类似题目**：  
  - [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)  
  - [P1712 [NOI2016] 区间](https://www.luogu.com.cn/problem/P1712)  
  - [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)  

- **通用解法**：  
  - **双指针维护区间极值**，结合哈希表统计状态。

---

### **可视化与算法演示**

**动画设计**：  
1. **元素标记**：  
   - 奶牛队列显示为不同颜色的像素方块（颜色代表血统）。  
   - 左右指针 `l` 和 `r` 用箭头标识，移动时有拖影效果。  
   - 当前窗口内血统种类数实时显示，超过 `k+1` 时触发警告音效。  

2. **关键步骤高亮**：  
   - **右指针右移**：新方块进入窗口，颜色渐变。  
   - **左指针收缩**：左侧方块褪色，计数器减少。  
   - **答案更新**：最大连续段闪烁显示，并记录数值。  

**复古像素效果**：  
- **8-bit 音效**：指针移动时播放“哔”声，种类超限时播放低沉音效，答案更新时播放胜利音效。  
- **Canvas 绘制**：基于网格绘制奶牛队列，每步动画更新 `requestAnimationFrame`。  

---

### **推荐相似题目**

1. [P3402 最长可重叠重复子串](https://www.luogu.com.cn/problem/P3402)  
2. [P4085 [USACO17DEC]Haybale Feast G](https://www.luogu.com.cn/problem/P4085)  
3. [P3143 [USACO16OPEN]Diamond Collector S](https://www.luogu.com.cn/problem/P3143)  

---

### **代码片段（滑动窗口核心）**

```cpp
#include <cstdio>
#include <map>
using namespace std;

int n, k, a[100005], cnt[100005], ans;

int main() {
    scanf("%d%d", &n, &k);
    map<int, int> mp;
    int id = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (!mp.count(a[i])) mp[a[i]] = ++id;
        a[i] = mp[a[i]];
    }

    int l = 1, kind = 0;
    for (int r = 1; r <= n; r++) {
        if (++cnt[a[r]] == 1) kind++;
        while (kind > k + 1) {
            if (--cnt[a[l]] == 0) kind--;
            l++;
        }
        ans = max(ans, cnt[a[r]]);
    }
    printf("%d", ans);
    return 0;
}
```

---

### **个人心得摘录**

- **贪心优化**：答案只需关注当前右端点的血统数量，无需全局统计（NTG_Adiord）。  
- **离散化陷阱**：血统 ID 必须压缩为连续值，否则数组越界（Cutest_Junior）。  

---

**总结**：滑动窗口是本题最优解，时间复杂度 `O(n)`，结合离散化处理大数据范围，代码简洁高效。

---
处理用时：79.35秒