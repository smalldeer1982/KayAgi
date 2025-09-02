# 题目信息

# [USACO07MAR] Face The Right Way G

## 题目描述

Farmer John has arranged his N (1 ≤ N ≤ 5,000) cows in a row and many of them are facing forward, like good cows. Some of them are facing backward, though, and he needs them all to face forward to make his life perfect.

Fortunately, FJ recently bought an automatic cow turning machine. Since he purchased the discount model, it must be irrevocably preset to turn K (1 ≤ K ≤ N) cows at once, and it can only turn cows that are all standing next to each other in line. Each time the machine is used, it reverses the facing direction of a contiguous group of K cows in the line (one cannot use it on fewer than K cows, e.g., at the either end of the line of cows). Each cow remains in the same \*location\* as before, but ends up facing the \*opposite direction\*. A cow that starts out facing forward will be turned backward by the machine and vice-versa.

Because FJ must pick a single, never-changing value of K, please help him determine the minimum value of K that minimizes the number of operations required by the machine to make all the cows face forward. Also determine M, the minimum number of machine operations required to get all the cows facing forward using that value of K.

$N$ 头牛排成一列 $1 \le N \le 5000$。每头牛或者向前或者向后。为了让所有牛都面向前方，农夫每次可以将 $K$ 头连续的牛转向 $1 \le K \le N$，求使操作次数最小的相应 $K$ 和最小的操作次数 $M$。$F$ 为朝前，$B$ 为朝后。

请在一行输出两个数字 $K$ 和 $M$，用空格分开。

## 说明/提示

For K = 3, the machine must be operated three times: turn cows (1,2,3), (3,4,5), and finally (5,6,7)


## 样例 #1

### 输入

```
7
B
B
F
B
F
B
B```

### 输出

```
3 3```

# AI分析结果



**唯一算法分类**：差分数组 + 贪心

---

### **题解思路与核心难点**

1. **核心思路**  
   - **贪心策略**：从左到右遍历牛群，若当前牛朝后（B），则翻转以它为起点的连续K头牛。  
   - **差分优化**：用差分数组标记翻转区间的起点和终点，避免暴力遍历区间，将翻转操作的时间复杂度从O(N)降为O(1)。  
   - **关键变量**：  
     - `diff[i]`：标记翻转操作的差分数组。  
     - `current_flips`：当前累积的翻转次数（奇偶性决定当前牛的实际朝向）。  

2. **解决难点**  
   - **时间复杂度优化**：直接模拟翻转会导致O(N^3)，差分数组将总复杂度降为O(N^2)。  
   - **边界处理**：当剩余牛数不足K时，当前K值不可行。需提前终止并标记。  

---

### **高星题解推荐（≥4星）**

1. **Delva（★★★★★）**  
   - **亮点**：代码简洁，异或操作高效处理翻转状态，逻辑清晰。  
   - **代码片段**：  
     ```cpp
     if (!(A[i] ^ b)) { // 当前牛朝后
         if (i + len - 1 > n) break; // 边界检查
         b ^= 1, B[i + len] ^= 1; // 差分标记翻转
         ++cnt;
     }
     ```

2. **FallR（★★★★☆）**  
   - **亮点**：详细解释差分数组的原理，调试经验分享（边界条件处理）。  
   - **关键注释**：  
     ```cpp
     // 若剩余长度不足K，直接跳过当前K
     if (i + k - 1 > n) { op = 1; break; }
     ```

3. **llzzxx712（★★★★☆）**  
   - **亮点**：用`sum`变量动态维护当前翻转次数，避免显式差分数组。  
   - **核心代码**：  
     ```cpp
     if ((a[i] + sum) % 2 == 0) {
         sum++; // 翻转次数+1
         cf[i + k]--; // 差分终点标记
     }
     ```

---

### **最优思路提炼**

- **贪心+差分**：从左到右处理，每次遇到B时翻转，保证最少操作次数。  
- **差分数组技巧**：通过标记区间起点和终点，实现O(1)翻转操作。  
- **奇偶性判断**：用异或或模2运算判断当前实际朝向，避免显式修改数组。  

---

### **同类题目推荐**

1. **P1969 积木大赛**（差分数组应用）  
2. **P4552 IncDec Sequence**（差分性质与极值分析）  
3. **P3870 开关**（区间翻转与位运算优化）  

---

### **可视化算法演示**

1. **动画设计**：  
   - **网格表示**：用像素块表示每头牛，绿色为F，红色为B。  
   - **差分标记**：翻转起点显示黄色箭头，终点显示灰色方块。  
   - **步进执行**：点击单步按钮，显示当前处理的牛和差分数组更新。  

2. **复古像素风格**：  
   - **8位音效**：翻转时播放“哔”声，成功时播放胜利音效。  
   - **Canvas动画**：每次翻转后更新网格颜色，显示当前K和操作次数。  

3. **交互功能**：  
   - **参数调节**：滑动条选择K值，自动演示最优解。  
   - **代码同步**：高亮当前执行的代码行，与动画联动。  

---

### **核心代码实现**

```cpp
// 基于Delva题解的优化代码
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 5005;
int n, min_cnt = 1e9, best_k;
bool a[MAXN], diff[MAXN];

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        char c; cin >> c;
        a[i] = (c == 'F');
    }

    for (int k = 1; k <= n; ++k) {
        memset(diff, 0, sizeof(diff));
        int cnt = 0, current = 0;
        bool valid = true;

        for (int i = 1; i <= n; ++i) {
            current ^= diff[i]; // 累积差分标记
            if (a[i] ^ current) continue; // 当前牛已朝前

            if (i + k - 1 > n) { // 剩余长度不足
                valid = false;
                break;
            }
            cnt++;
            current ^= 1; // 翻转奇偶性
            diff[i + k] ^= 1; // 标记差分终点
        }

        if (valid && cnt < min_cnt) {
            min_cnt = cnt;
            best_k = k;
        }
    }

    cout << best_k << " " << min_cnt;
    return 0;
}
```

---

**总结**：通过差分数组优化区间操作，结合贪心策略，确保每次翻转必要且高效。关键点在于差分标记的维护和奇偶性判断。

---
处理用时：85.25秒