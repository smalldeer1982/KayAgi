# 题目信息

# FASHION - Fashion Shows

## 题目描述

A fashion show rates participants according to their level of hotness. Two different fashion shows were organized, one for men and the other for women. A date for the third is yet to be decided ;) .

Now the results of both fashion shows are out. The participants of both the fashion shows have decided to date each other, but as usual they have difficuly in choosing their partners. The Maximum Match dating serive (MMDS) comes to their rescue and matches them in such a way that that maximizes the hotness bonds for all couples.

If a man has been rated at hotness level x and a women at hotness level y, the value of their hotness bond is x\*y.

Both fashion shows contain **N** participants each. MMDS has done its job and your job is to find the sum of hotness bonds for all the couples that MMDS has proposed.

## 样例 #1

### 输入

```
2

2

1 1

3 2

3

2 3 2

1 3 2```

### 输出

```
5

15```

# AI分析结果



**唯一算法分类**  
贪心

---

### **综合分析与结论**  
**题目核心**：给定两个数组，求重新排列后的对应元素乘积和最大值。  
**核心难点**：证明排序后对应相乘的和最大（排序不等式）。  
**解决方案**：  
1. 将两个数组分别升序排序，对应位置相乘求和。  
2. 关键数学依据为排序不等式，确保大数与大数匹配，小数与小数匹配。  
3. 需注意变量溢出问题，使用 `long long` 存储总和。  

**可视化设计**：  
- **动画步骤**：  
  1. 展示两个数组初始状态。  
  2. 分别对两个数组进行升序排序（动态展示排序过程）。  
  3. 高亮对应位置的元素，计算其乘积并累加到总和。  
- **颜色标记**：排序过程中当前比较的元素用红色标记，对应乘积的元素用绿色高亮。  
- **复古像素风格**：  
  - 使用 8-bit 像素网格展示数组元素，排序时用闪烁动画。  
  - 音效：排序完成时播放上扬音效，计算乘积时触发轻微“点击”声。  
  - Canvas 动态更新每一步的乘积和总和。  

---

### **题解清单 (≥4星)**  
1. **Withers (5星)**  
   - 思路清晰，正确应用排序不等式。  
   - 代码严谨，使用 `long long` 避免溢出，每次循环初始化变量。  
   - 关键代码：  
     ```cpp
     sort(a+1, a+n+1);
     sort(b+1, b+n+1);
     sum += a[i] * b[i];
     ```

2. **PeterBei (5星)**  
   - 明确提到数据溢出问题，使用 `long long` 存储总和。  
   - 代码简洁，包含初始化逻辑。  
   - 关键代码：  
     ```cpp
     memset(a, 0, sizeof(a));
     memset(b, 0, sizeof(b));
     sum = 0;
     ```

---

### **最优思路与技巧**  
- **排序不等式**：两个升序数组对应相乘的和最大。  
- **变量类型**：总和变量需用 `long long` 避免溢出。  
- **多测试用例处理**：每次循环前重置变量和数组。  

---

### **相似题目推荐**  
1. **P1090 [NOIP2004 提高组] 合并果子**（贪心+优先队列）  
2. **P1223 排队接水**（排序不等式应用）  
3. **P1106 删数问题**（贪心策略）  

---

### **个人心得摘录**  
- **调试教训**：未初始化变量会导致多测试用例结果错误（见 YJY0807qwq 的题解）。  
- **数学思维**：通过调整法证明排序策略的最优性。  

---

### **核心代码实现**  
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        long long sum = 0;
        for (int i = 0; i < n; i++) sum += (long long)a[i] * b[i];
        cout << sum << endl;
    }
    return 0;
}
```

---

### **可视化代码片段（Canvas 动画）**  
```javascript
// 伪代码：排序与计算动画
function animateSortAndSum(a, b) {
    sort(a); // 动态展示排序过程
    sort(b);
    let sum = 0;
    for (let i = 0; i < a.length; i++) {
        highlight(a[i], b[i]); // 高亮对应元素
        sum += a[i] * b[i];
        updateSumDisplay(sum); // 更新总和显示
    }
}
```

---
处理用时：149.87秒