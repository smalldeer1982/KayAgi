# 题目信息

# [CCC 2023 S2] Symmetric Mountains

## 题目描述

Rebecca is a tour guide and is trying to market the Rocky Mountains for her magazine. She recently took a beautiful picture consisting of $N$ mountains where the $i\text{-th}$ mountain from the left has a height $h_i$. She will crop this picture for her magazine, by possibly removing some mountains from the left side of the picture and possibly removing some mountains from the right side of the picture. That is, a crop consists of consecutive mountains starting from the $l\text{-th}$ to the $r\text{-th}$ mountain where $l \leq r$. To please her magazine readers, Rebecca will try to find the most symmetric crop.

We will measure the $asymmetric\ value$ of a crop as the sum of the absolute difference for every pair of mountains equidistant from the midpoint of the crop. To help understand that definition, note that the absolute value of $a$ number $v$, written as $|v|$, is the non-negative value of v: for example $\lvert -6 \rvert = 6$ and $|14| = 14$. The asymmetric value of a crop is the sum of all $|h_{l+i} - h_{r-i}|$ for $0 \leq i \leq \frac{r-l}{2}$. To put that formula in a different way, we pair up the mountains working from the outside in toward the centre, calculate the absolute difference in height of each of these pairs, and sum them up.

Because Rebecca does not know how wide the picture needs to be, for all possible crop lengths, find the asymmetric value of the most symmetric crop (the crop with the minimum asymmetric value).

## 说明/提示

Explanation of Output for Sample Input $1$:

We will show why the fifth value from the left is $2$.Let us try to compute all the asymmetric values of crops with length $5$.

The height of the mountains in the first crop is $[3, 1, 4, 1, 5]$. The asymmetric value of this crop is $|3 - 5| + |1 - 1| + |4 - 4| = 2$.

The height of the mountains in the second crop is $[1, 4, 1, 5, 9]$. The asymmetric value of this crop is $|1 - 9| + |4 - 5| + |1 - 1| = 9$.

The height of the mountains in the last crop is $[4, 1, 5, 9, 2]$. The asymmetric value of this crop is $|4 - 2| + |1 - 9| + |5 - 5| = 10$.

Hence, the most symmetric crop of length $5$ is $2$.

Explanation of Output for Sample Input $2$:

This sample satisfies the second subtask. Note that the only crop of length $4$ is $[1, 3, 5, 6]$ which has asymmetric value of $|1 - 6| + |3 - 5| = 7$.

**本题采用捆绑测试**：

- Subtask 1（5 points）：$1\leq N \leq 300$，$0\leq h_i \leq 10^5$。

- Subtask 2（5 points）：$1 \leq N \leq 5000$，$0 \leq h_i \leq 10^5$，保证山的高度从左到右单调不减。

- Subtask 3（5 points）：$1\leq N\leq 5000$，$0 \leq h_i \leq 10^5$。

## 样例 #1

### 输入

```
7
3 1 4 1 5 9 2```

### 输出

```
0 2 0 5 2 10 10```

## 样例 #2

### 输入

```
4
1 3 5 6```

### 输出

```
0 1 3 7```

# AI分析结果



## 唯一算法分类
区间动态规划 / 中心扩展法

---

## 题解思路、算法要点与解决难点

### 核心算法对比分析
1. **区间DP法**（GeXiaoWei、HHC883等）  
   - **递推公式**：`dp[l][r] = dp[l+1][r-1] + abs(h[l]-h[r])`  
   - **优势**：直接体现对称性计算规律，无需考虑奇偶性  
   - **难点**：需要理解区间长度从小到大递推的填充顺序，空间复杂度 O(n²)

2. **中心扩展法**（ZepX_D、songzhixin等）  
   - **核心思想**：枚举每个可能的中心点（单点或双点），向两侧扩展计算不对称值  
   - **优势**：无需存储二维数组，节省空间，代码更简洁  
   - **难点**：需要同时处理奇数长度（单中心）和偶数长度（双中心）的扩展逻辑

3. **记忆化递归**（Jorisy、leiaxiwo等）  
   - **核心思想**：递归计算区间不对称值，用记忆化数组避免重复计算  
   - **劣势**：递归调用栈可能带来额外开销，不如迭代方式高效

### 关键优化点
- **增量计算**：无论DP还是扩展法，都通过`当前差值 = 内层差值 + 外层端点差`实现 O(1) 更新  
- **最小值维护**：在计算过程中实时更新每个长度的最小不对称值，避免二次遍历

---

## 题解评分（≥4星）

1. **ZepX_D（5星）**  
   - 亮点：代码最简洁（仅24行），通过奇偶双循环覆盖所有情况，无需预处理  
   - 代码可读性：极高，变量命名清晰（l,r,s），直接维护全局最小值数组

2. **GeXiaoWei（4.5星）**  
   - 亮点：标准区间DP模板，递推关系直击问题本质  
   - 改进点：可优化空间复杂度，二维数组在 n=5000 时需约 25MB 内存

3. **Zhl2010（4星）**  
   - 亮点：最简区间DP实现（仅20行），通过枚举长度直接维护答案  
   - 特色：省略显式的初始化步骤，利用递推公式自动处理边界

---

## 最优思路或技巧提炼

### 核心算法流程
```python
初始化 ans 数组为无穷大
for 每个中心点 i:
   # 处理奇数长度
   l = r = i
   while 未越界:
      当前长度 = r - l + 1
      ans[当前长度] = min(ans[当前长度], 当前不对称值)
      l左移，r右移，累加新端点差值
   # 处理偶数长度
   l = i, r = i+1
   while 未越界:
      类似奇数处理，计算并更新偶数长度最小值
```

### 关键技巧
- **双指针扩展**：以中心点为锚点，同步移动左右指针，保证对称性  
- **奇偶分治**：分别处理单中心（奇数长度）和双中心（偶数长度）的扩展逻辑  
- **就地更新**：在扩展过程中直接维护全局最小值数组，避免后续遍历

---

## 同类型题与算法套路
1. **最长回文子串**：同样使用中心扩展法，计算最大对称区间  
2. **回文子序列计数**：基于区间DP的经典解法  
3. **环形数组对称性检测**：将数组视为环形，扩展双指针判断逻辑

---

## 推荐相似题目
1. [P1435 回文字串](https://www.luogu.com.cn/problem/P1435)  
   - 区间DP求最小插入字符数使字符串回文

2. [P1654 乘积最大](https://www.luogu.com.cn/problem/P1654)  
   - 区间DP维护分段乘积极值

3. [CF1326D2 Prefix-Suffix Palindrome (Hard version)](https://www.luogu.com.cn/problem/CF1326D2)  
   - 中心扩展法求最长前后缀回文

---

## 个人心得摘录
> "区间DP的难点在于理解状态转移方程如何分解子问题，这里的不对称值天然具有递归性，非常适合用DP表达。" —— GeXiaoWei

> "调试时发现偶数长度的中心点处理容易越界，后来通过 min(i, n-i) 限制扩展步数解决。" —— songzhixin

---

## 可视化与算法演示

### 动画设计
1. **像素风格渲染**  
   - 使用 8-bit 调色板（红/蓝表示当前端点，黄/绿表示已计算区间）  
   - 山脉高度用不同颜色方块堆叠表示，对称线用闪烁像素点标注

2. **核心步骤演示**  
   ```javascript
   // 伪代码演示中心扩展法
   function animateSymmetricMountains() {
       for (let i = 0; i < n; i++) {
           // 奇数扩展
           let l = i, r = i, s = 0;
           while (l >= 0 && r < n) {
               highlight(l, r, RED);  // 高亮当前端点
               s += Math.abs(h[l] - h[r]);
               updateAnswer(r - l + 1, s);
               l--; r++;
               await sleep(500);      // 步进延迟
           }
           // 偶数扩展（类似逻辑）
       }
   }
   ```

3. **交互功能**  
   - **速度调节**：滑块控制动画速度（0.5x~3x）  
   - **模式切换**：对比区间DP（填充表格）与中心扩展（动态生长）的差异  
   - **音效反馈**：端点扩展时播放 8-bit "beep" 音效，更新最小值时播放金币音效

### 算法比较视图
![可视化对比](https://cdn.luogu.com.cn/upload/image_hosting/3qkz1f2x.png)  
- **左侧**：中心扩展法的动态生长过程，红色箭头表示当前扩展方向  
- **右侧**：区间DP的表格填充过程，绿色表示已计算单元格

---

## 核心代码实现（ZepX_D 版本）
```cpp
#include <iostream>
#include <cstring>
using namespace std;

int h[5010], ans[5010], l, r, s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    memset(ans, 0x3f, sizeof(ans));
    for (int i = 1; i <= n; i++) cin >> h[i];
    
    for (int i = 1; i <= n; i++) {
        // 处理奇数长度
        s = 0, l = r = i;
        while (l >= 1 && r <= n) {
            ans[r - l + 1] = min(ans[r - l + 1], s);
            l--, r++, s += abs(h[r] - h[l]);
        }
        // 处理偶数长度
        s = abs(h[i+1] - h[i]), l = i, r = i + 1;
        while (l >= 1 && r <= n) {
            ans[r - l + 1] = min(ans[r - l + 1], s);
            l--, r++, s += abs(h[r] - h[l]);
        }
    }
    
    for (int i = 1; i <= n; i++) 
        cout << (i == 1 ? 0 : ans[i]) << ' ';
    return 0;
}
```

---
处理用时：98.00秒