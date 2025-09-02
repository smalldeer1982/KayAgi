# 题目信息

# Diverse Substrings

## 题目描述

A non-empty digit string is diverse if the number of occurrences of each character in it doesn't exceed the number of distinct characters in it.

For example:

- string "7" is diverse because 7 appears in it $ 1 $ time and the number of distinct characters in it is $ 1 $ ;
- string "77" is not diverse because 7 appears in it $ 2 $ times and the number of distinct characters in it is $ 1 $ ;
- string "1010" is diverse because both 0 and 1 appear in it $ 2 $ times and the number of distinct characters in it is $ 2 $ ;
- string "6668" is not diverse because 6 appears in it $ 3 $ times and the number of distinct characters in it is $ 2 $ .

You are given a string $ s $ of length $ n $ , consisting of only digits $ 0 $ to $ 9 $ . Find how many of its $ \frac{n(n+1)}{2} $ substrings are diverse.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

Note that if the same diverse string appears in $ s $ multiple times, each occurrence should be counted independently. For example, there are two diverse substrings in "77" both equal to "7", so the answer for the string "77" is $ 2 $ .

## 说明/提示

In the first test case, the diverse substring is "7".

In the second test case, the only diverse substring is "7", which appears twice, so the answer is $ 2 $ .

In the third test case, the diverse substrings are "0" ( $ 2 $ times), "01", "010", "1" ( $ 2 $ times), "10" ( $ 2 $ times), "101" and "1010".

In the fourth test case, the diverse substrings are "0" ( $ 3 $ times), "01", "011", "0110", "1" ( $ 2 $ times), "10", "100", "110" and "1100".

In the fifth test case, the diverse substrings are "3", "39", "399", "6", "9" ( $ 4 $ times), "96" and "996".

In the sixth test case, all $ 15 $ non-empty substrings of "23456" are diverse.

## 样例 #1

### 输入

```
7
1
7
2
77
4
1010
5
01100
6
399996
5
23456
18
789987887987998798```

### 输出

```
1
2
10
12
10
15
106```

# AI分析结果



---

## **唯一算法分类**  
无算法分类（暴力枚举+剪枝）

---

## **题解思路、算法要点与解决难点**  

### **核心思路**  
所有题解均基于以下关键观察：**任何满足条件的子串长度至多为100**。  
**推导过程**：数字种类最多为10种（0-9），若子串长度超过100，根据鸽巢原理，至少有一个数字出现次数≥11次，此时种类数≤10，故不满足条件。因此只需枚举长度≤100的子串。

### **算法实现要点**  
1. **枚举起点**：遍历每个可能的子串起点i。  
2. **限制终点范围**：对于每个i，仅检查i到i+99（或字符串末尾）之间的子串。  
3. **实时统计**：使用计数数组维护字符出现次数，动态更新最大出现次数（mx）和种类数（dis）。  
4. **即时判断**：对每个子串，当mx ≤ dis时累加答案。

### **解决难点**  
- **时间复杂度优化**：通过限制子串长度将复杂度从O(n²)降至O(n×100)。  
- **空间优化**：仅需长度为10的计数数组，空间复杂度O(1)。

---

## **题解评分 (≥4星)**  

### **1. Xy_top (5星)**  
- **亮点**：代码简洁高效，直接维护mx和dis，避免冗余判断。  
- **代码**：使用`min(i+101, n)`确保不越界，逻辑清晰。  

### **2. Dry_ice (4星)**  
- **亮点**：增加提前终止条件（`a≤10 && b≤10`），进一步优化。  
- **分析**：详细解释鸽巢原理，代码可读性高。  

### **3. shinzanmono (4星)**  
- **亮点**：显式限制子串长度为100，维护方式直观。  
- **缺点**：内层循环中每次全扫描计数数组，略低效。  

---

## **最优思路或技巧提炼**  

### **关键技巧**  
1. **长度限制推导**：利用鸽巢原理得出最大长度100，避免无效枚举。  
2. **动态计数法**：  
   - 维护`mx`（当前子串中某数字的最大出现次数）。  
   - 维护`dis`（当前子串的数字种类数）。  
   - 每次添加新字符时更新这两个值，判断条件`mx ≤ dis`。  

### **代码优化技巧**  
```cpp
// Xy_top的核心代码片段
for (int i=0; i<n; ++i) {
    int cnt[10] = {0}, mx=0, dis=0;
    for (int j=i; j<min(i+101, n); ++j) {
        int num = s[j] - '0';
        if (cnt[num]++ == 0) dis++;  // 首次出现则种类+1
        mx = max(mx, cnt[num]);       // 更新最大值
        if (mx <= dis) ans++;         // 条件判断
    }
}
```

---

## **同类型题或类似算法套路**  
- **子串/子数组统计问题**：当子问题存在隐含长度限制时（如字符种类有限），常可通过限制枚举范围优化时间复杂度。  
- **滑动窗口变种**：结合动态计数与条件判断，如LeetCode 395（至少有K个重复字符的最长子串）。

---

## **推荐相似题目**  
1. **CF 1520D - Similar Pairs**（利用奇偶性剪枝）  
2. **LeetCode 3. 无重复字符的最长子串**（滑动窗口+哈希表）  
3. **Luogu P2926 [USACO08DEC] Patting Heads**（计数与倍数统计）

---

## **可视化与算法演示**  

### **动画方案**  
1. **动态高亮**：  
   - 红色框表示当前子串起点i，蓝色框表示正在检查的终点j。  
   - 右侧显示计数数组，实时更新数字出现次数。  
   - 当`mx`（红色数字）≤ `dis`（绿色数字）时，子串标记为绿色。  

2. **复古像素风格**：  
   - 使用16色调色板，数字字符以8x8像素块显示。  
   - 每次j移动时播放“哔”声，符合条件时播放“叮”声。  

3. **控制面板**：  
   - 速度滑块调节（1x-10x）。  
   - 单步执行按钮观察每个子串的判断过程。  

### **Canvas 实现伪代码**  
```javascript
// 伪代码：绘制子串检查过程
function drawSubstring(i, j, cnt, mx, dis) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    // 绘制字符串s，高亮i到j
    drawString(s, i, j, "#00FF00");
    // 绘制计数数组
    for (let k=0; k<10; k++) {
        drawBar(k, cnt[k], mx);
    }
    // 触发音效
    if (mx <= dis) playSound("success.wav");
}
```

---

## **个人心得摘录**  
- **Xy_top**：*“这道题看似很复杂，其实很简单”* → 强调问题转化的重要性。  
- **Dry_ice**：*“诈骗题”* → 暗示需洞察题目隐藏的数学性质。  

---

## **完整代码参考**  
```cpp
// 基于Xy_top的代码（简洁高效）
#include <iostream>
using namespace std;
int main() {
    int t; cin >> t;
    while (t--) {
        int n; string s;
        cin >> n >> s;
        long long ans = 0;
        for (int i=0; i<n; ++i) {
            int cnt[10] = {0}, mx = 0, dis = 0;
            for (int j=i; j < min(i+101, n); ++j) {
                int num = s[j] - '0';
                if (cnt[num]++ == 0) dis++;
                mx = max(mx, cnt[num]);
                if (mx <= dis) ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---
处理用时：76.67秒