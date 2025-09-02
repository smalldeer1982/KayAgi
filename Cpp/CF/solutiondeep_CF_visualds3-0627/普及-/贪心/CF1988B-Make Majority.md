# 题目信息

# Make Majority

## 题目描述

You are given a sequence $ [a_1,\ldots,a_n] $ where each element $ a_i $ is either $ 0 $ or $ 1 $ . You can apply several (possibly zero) operations to the sequence. In each operation, you select two integers $ 1\le l\le r\le |a| $ (where $ |a| $ is the current length of $ a $ ) and replace $ [a_l,\ldots,a_r] $ with a single element $ x $ , where $ x $ is the majority of $ [a_l,\ldots,a_r] $ .

Here, the majority of a sequence consisting of $ 0 $ and $ 1 $ is defined as follows: suppose there are $ c_0 $ zeros and $ c_1 $ ones in the sequence, respectively.

- If $ c_0\ge c_1 $ , the majority is $ 0 $ .
- If $ c_0<c_1 $ , the majority is $ 1 $ .

For example, suppose $ a=[1,0,0,0,1,1] $ . If we select $ l=1,r=2 $ , the resulting sequence will be $ [0,0,0,1,1] $ . If we select $ l=4,r=6 $ , the resulting sequence will be $ [1,0,0,1] $ .

Determine if you can make $ a=[1] $ with a finite number of operations.

## 说明/提示

In the fourth testcase of the example, initially $ a=[1,0,0,0,0,0,0,0,1] $ . A valid sequence of operations is:

1. Select $ l=2,r=8 $ and apply the operation. $ a $ becomes $ [1,0,1] $ .
2. Select $ l=1,r=3 $ and apply the operation. $ a $ becomes $ [1] $ .

## 样例 #1

### 输入

```
5
1
0
1
1
2
01
9
100000001
9
000011000```

### 输出

```
No
Yes
No
Yes
No```

# AI分析结果



# 算法分类
贪心算法

---

# 题解思路与核心难点分析

## 核心思路
所有题解均采用以下贪心策略：
1. **预处理连续0**：将连续的0压缩为单个0，此时字符串形如 101010... 或 0101...
2. **数量比较**：统计压缩后的0块数（cnt0）和原字符串的1总数（cnt1），当 cnt1 > cnt0 时输出 Yes

## 解决难点
- **正确性证明**：需证明任意操作无法比该策略更优。因为合并连续0得到的0块数最少，且每次合并操作会减少元素总数，最终整体合并时0的块数无法更少。
- **边界处理**：统计0块时需要特殊处理首字符和前导非0字符（如 `i==0 || a[i-1] != '0'`）

---

# 题解评分（≥4星）

1. **shiziyu111（4.5星）**
   - 亮点：代码极简，直接统计块数与总数，时间复杂度O(n)
   - 代码风格：清晰易懂，无冗余判断

2. **Z3k7223（4星）**
   - 亮点：详细分析了 c0=c1 的特殊情况，提供数学证明
   - 代码实现：与主流解法一致，注释较少但逻辑严谨

3. **Little_Cabbage（4星）**
   - 亮点：包含字符串预处理的可视化代码片段，便于调试
   - 代码结构：采用分步合并策略，适合教学演示

---

# 最优思路与技巧提炼

## 关键步骤
1. **压缩连续0**：遍历时遇到新0块才计数
   ```cpp
   if (a[i] == '0' && (i == 0 || a[i-1] != '0')) cnt0++;
   ```
2. **直接比较数量**：无需任何复杂操作，只需满足 `cnt1 > cnt0`

## 思维突破点
- **逆向思维**：最终必须整体合并为1 → 需保证合并前的1足够抵消0的影响
- **贪心选择**：合并连续0是最优子结构，后续操作无法得到更少0块

---

# 类似题目推荐
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)  
   （贪心选择最小代价合并）
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)  
   （贪心排序策略）
3. [CF1772D 绝对值排序](https://codeforces.com/problemset/problem/1772/D)  
   （通过预处理简化判断条件）

---

# 个人心得摘录
> "统计连续0块时，必须判断前一个字符是否为1或起始位置，否则会重复计数" —— Z3k7223  
> "合并后的0块数决定了胜负手，1的数量是固定资源" —— _H17_

---

# 可视化算法设计

## 核心逻辑演示
```javascript
// 伪代码示例：使用Canvas绘制合并过程
const canvas = document.getElementById('demo');
const ctx = canvas.getContext('2d');

function drawArray(arr, cnt0, cnt1) {
  // 绘制当前数组状态（像素块形式）
  arr.forEach((num, i) => {
    ctx.fillStyle = num === 1 ? '#FF5555' : '#5555FF';
    ctx.fillRect(i * 30, 0, 25, 25);
  });
  
  // 在右侧显示统计信息
  ctx.fillText(`0-blocks: ${cnt0}`, 300, 20);
  ctx.fillText(`1-count: ${cnt1}`, 300, 40);
}

// 示例数据
let arr = [1,0,0,0,1,1,0];
let cnt0 = 2, cnt1 = 3;
drawArray(arr, cnt0, cnt1); // 初始状态
```

## 复古游戏化设计
- **像素风格**：16x16像素块，0用蓝色（#0000FF），1用红色（#FF0000）
- **音效设计**：
  - 合并连续0时播放 "beep" 音效（Web Audio API生成）
  - 最终成功时播放FC游戏通关音效
- **自动演示模式**：
  ```javascript
  function autoDemo() {
    highlightCurrentBlock(); // 高亮当前处理的0块
    setTimeout(() => mergeBlocks(), 1000); // 延迟合并动画
  }
  ```

---

# 核心代码实现
```cpp
#include <iostream>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n, cnt0 = 0, cnt1 = 0;
        string s;
        cin >> n >> s;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') cnt1++;
            else if (i == 0 || s[i-1] != '0') cnt0++; // 关键统计逻辑
        }
        cout << (cnt1 > cnt0 ? "Yes\n" : "No\n");
    }
    return 0;
}
```

---
处理用时：70.37秒