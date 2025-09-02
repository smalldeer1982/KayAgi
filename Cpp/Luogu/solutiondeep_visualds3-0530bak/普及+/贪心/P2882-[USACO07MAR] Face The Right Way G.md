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



### 题解思路与算法要点

1. **核心贪心策略**  
   从左到右处理每个牛，遇到朝后的牛（B）时，立即翻转从该位置开始的连续K头牛。确保每个B被处理一次，后续操作不影响已处理部分。

2. **差分优化**  
   用差分数组记录翻转操作的起始和结束位置，将区间翻转的时间复杂度从O(K)降至O(1)，整体复杂度优化为O(N²)。

3. **难点解决**  
   - **正确性验证**：翻转顺序不影响结果，贪心策略确保最少操作次数。
   - **边界处理**：翻转区间超出范围时判定为无效K值。

---

### 题解评分 (≥4星)

1. **Delva的题解（★★★★☆）**  
   - 思路清晰，代码简洁，利用异或和差分数组高效处理翻转状态。
   - 核心代码片段：
     ```cpp
     for (int i=1; i<=n; ++i) {
         b ^= B[i];
         if (!(A[i] ^ b)) {
             if (i+len-1 >n) { flag=0; break; }
             b ^=1, B[i+len]^=1;
             ++cnt;
         }
     }
     ```

2. **llzzxx712的题解（★★★★☆）**  
   - 详细注释与逐步分析，适合初学者理解差分和贪心的结合。
   - 关键代码：
     ```cpp
     if ((a[i] + now) % 2 == 0) {
         now ^= 1;
         cha[i + k] ^= 1;
         step++;
     }
     ```

3. **Su_Zipei的题解（★★★★☆）**  
   - 清晰的变量命名和模块化设计，突出差分数组的应用。
   - 代码片段：
     ```cpp
     for (int j=1; j<=n; j++) {
         cf[j] += cf[j-1];
         if ((a[j] + cf[j]) % 2 == 0) {
             cf[j]++, cf[j+k]--, cnt++;
         }
     }
     ```

---

### 最优思路提炼

1. **贪心选择依据**  
   每次遇到B必须翻转，确保后续操作不影响已处理的部分，保证全局最优。

2. **差分数组实现**  
   - 翻转区间[i, i+K-1]时，在差分数组的i处+1，i+K处-1。
   - 通过前缀和计算当前位置的翻转次数，奇数次翻转改变状态。

---

### 类似题目推荐

1. [P2895 Hotel G](https://www.luogu.com.cn/problem/P2895)  
   （区间覆盖与贪心选择）

2. [P1969 积木大赛](https://www.luogu.com.cn/problem/P1969)  
   （贪心处理连续区间差值）

3. [P3870 开关](https://www.luogu.com.cn/problem/P3870)  
   （区间翻转与差分优化）

---

### 可视化设计

1. **动画效果**  
   - **颜色标记**：当前处理的牛（红色），翻转区间（黄色），已处理部分（绿色）。
   - **步进控制**：单步执行观察差分数组更新与牛状态变化。

2. **复古像素风格**  
   - **Canvas网格**：每头牛显示为像素块，翻转时颜色闪烁（红→绿）。
   - **音效触发**：翻转时播放8-bit音效，成功时播放胜利音。

3. **交互示例**  
   ```javascript
   // 伪代码：翻转动画
   function animateFlip(start, k) {
       for (let i = start; i < start + k; i++) {
           highlightCow(i); // 高亮当前牛
           playSound('flip'); // 播放翻转音效
       }
       updateDiffArray(start, start + k); // 更新差分数组显示
   }
   ```

---

### 核心代码实现

```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 5005;
int n, a[MAXN], min_cnt = 1e9, ans_k;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char c; cin >> c;
        a[i] = (c == 'B');
    }

    for (int k = 1; k <= n; k++) {
        int cnt = 0, diff[MAXN] = {0}, flip = 0;
        bool valid = true;
        for (int i = 1; i <= n; i++) {
            flip ^= diff[i]; // 累计差分计算当前翻转状态
            if (a[i] ^ flip) continue; // 已经是F无需操作
            if (i + k - 1 > n) { valid = false; break; }
            cnt++;
            flip ^= 1; // 翻转奇偶性
            diff[i + k] ^= 1; // 差分标记结束位置
        }
        if (valid && cnt < min_cnt) 
            min_cnt = cnt, ans_k = k;
    }
    cout << ans_k << " " << min_cnt << endl;
    return 0;
}
```

---

### 总结

通过贪心策略确保每次翻转的必要性，结合差分数组优化翻转状态的记录，将时间复杂度降至O(N²)。该思路适用于需要固定区间操作的类似题目，是贪心与差分结合的经典应用。

---
处理用时：92.53秒