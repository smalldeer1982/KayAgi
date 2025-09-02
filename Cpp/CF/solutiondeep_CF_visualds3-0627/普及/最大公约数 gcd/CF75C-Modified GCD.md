# 题目信息

# Modified GCD

## 题目描述

Well, here is another math class task. In mathematics, GCD is the greatest common divisor, and it's an easy task to calculate the GCD between two positive integers.

A common divisor for two positive numbers is a number which both numbers are divisible by.

But your teacher wants to give you a harder task, in this task you have to find the greatest common divisor $ d $ between two integers $ a $ and $ b $ that is in a given range from $ low $ to $ high $ (inclusive), i.e. $ low<=d<=high $ . It is possible that there is no common divisor in the given range.

You will be given the two integers $ a $ and $ b $ , then $ n $ queries. Each query is a range from $ low $ to $ high $ and you have to answer each query.

## 样例 #1

### 输入

```
9 27
3
1 5
10 11
9 11
```

### 输出

```
3
-1
9
```

# AI分析结果



---

**算法分类**：数论（因数分解与二分查找）

---

### **题解思路与核心难点**

1. **核心思路**  
   所有题解均基于以下关键性质：**a 和 b 的公因数必定是 gcd(a, b) 的因数**。因此，解题步骤为：  
   - **步骤1**：计算 gcd(a, b)  
   - **步骤2**：枚举 gcd(a, b) 的所有因数并排序  
   - **步骤3**：对每个查询，通过二分查找快速确定满足区间 [low, high] 的最大因数  

2. **解决难点**  
   - **因数的高效生成**：通过枚举 1 到 sqrt(gcd) 的整数，每次找到两个因数（i 和 gcd/i），时间复杂度 O(√d)。  
   - **快速查询**：利用排序后的有序性，通过二分查找（如 `upper_bound`）找到不超过 high 的最大因数，时间复杂度 O(log n)。  

---

### **题解评分（≥4星）**

1. **ADay 的题解**（★★★★☆）  
   - **亮点**：使用 `upper_bound` 简化二分逻辑，代码简洁高效。  
   - **核心代码**：  
     ```cpp
     int pos = upper_bound(v.begin(), v.end(), high) - v.begin() - 1;
     if (v[pos] >= low) return v[pos];
     ```

2. **tobie 的题解**（★★★★☆）  
   - **亮点**：手动实现二分查找，避免 STL 依赖，适合教学。  
   - **核心代码**：  
     ```cpp
     while (ll <= rr) {
         mid = (ll + rr) / 2;
         if (ans[mid] <= high) ll = mid + 1;
         else rr = mid - 1;
     }
     ```

3. **李至擎 的题解**（★★★★☆）  
   - **亮点**：详细注释和清晰的代码结构，适合初学者理解。  
   - **核心代码**：  
     ```cpp
     for (int i=1; i*i<=gcd; i++) {
         if (gcd % i == 0) {
             v.push_back(i);
             v.push_back(gcd/i);
         }
     }
     ```

---

### **最优思路与技巧提炼**

1. **因数生成技巧**  
   - 枚举到 sqrt(gcd) 并同时记录 i 和 gcd/i，避免重复计算。  
   - **代码片段**：  
     ```cpp
     for (int i = 1; i*i <= g; i++) {
         if (g % i == 0) {
             v.push_back(i);
             if (i != g/i) v.push_back(g/i);
         }
     }
     ```

2. **二分查找优化**  
   - 使用 `upper_bound` 或手动二分快速定位区间右端点。  
   - **代码片段**：  
     ```cpp
     sort(v.begin(), v.end());
     int pos = upper_bound(v.begin(), v.end(), high) - v.begin() - 1;
     ```

---

### **同类型题目推荐**

1. **P1414 又是毕业季II**：求多个数的最大公因数在区间内的最大值。  
2. **P1072 Hankson的趣味题**：结合因数分解与条件判断。  
3. **P2441 角色属性树**：树形结构中的因数路径问题。  

---

### **可视化与算法演示**

1. **动画设计**  
   - **步骤1**（因数生成）：  
     - 屏幕左侧显示 gcd(a, b) 的值。  
     - 枚举 1 到 sqrt(gcd)，每次找到因数时，右侧列表动态添加 i 和 gcd/i。  
     - **高亮**：当前枚举的 i 和对应的因数对。  
   - **步骤2**（排序）：  
     - 因数列表按从小到大排序，展示冒泡排序或快速排序过程。  
   - **步骤3**（查询处理）：  
     - 输入区间 [low, high]，通过二分查找动态显示指针移动。  
     - **颜色标记**：红色指针表示 high，蓝色指针表示 mid，绿色表示最终结果。  

2. **复古像素风格**  
   - **界面**：8-bit 风格，绿色终端字体，黑色背景。  
   - **音效**：  
     - 找到因数时播放“滴”声。  
     - 查询成功播放上升音调，失败播放下降音调。  
   - **自动演示**：  
     - 按空格键逐步执行因数生成和查询步骤。  

---

### **核心代码实现**

```cpp
#include <vector>
#include <algorithm>
using namespace std;

vector<int> get_factors(int g) {
    vector<int> factors;
    for (int i = 1; i*i <= g; i++) {
        if (g % i == 0) {
            factors.push_back(i);
            if (i != g/i) factors.push_back(g/i);
        }
    }
    sort(factors.begin(), factors.end());
    return factors;
}

int query(vector<int>& factors, int low, int high) {
    auto it = upper_bound(factors.begin(), factors.end(), high);
    if (it == factors.begin()) return -1;
    int val = *(it - 1);
    return val >= low ? val : -1;
}
```

---

**总结**：本题通过因数分解和二分查找的经典组合，展示了数论问题的高效解法。核心在于理解公因数与 gcd 的关系，并通过预处理和二分优化查询速度。

---
处理用时：75.79秒