# 题目信息

# New Year Transportation

## 题目描述

New Year is coming in Line World! In this world, there are $ n $ cells numbered by integers from $ 1 $ to $ n $ , as a $ 1×n $ board. People live in cells. However, it was hard to move between distinct cells, because of the difficulty of escaping the cell. People wanted to meet people who live in other cells.

So, user tncks0121 has made a transportation system to move between these cells, to celebrate the New Year. First, he thought of $ n-1 $ positive integers $ a_{1},a_{2},...,a_{n-1} $ . For every integer $ i $ where $ 1<=i<=n-1 $ the condition $ 1<=a_{i}<=n-i $ holds. Next, he made $ n-1 $ portals, numbered by integers from 1 to $ n-1 $ . The $ i $ -th ( $ 1<=i<=n-1 $ ) portal connects cell $ i $ and cell $ (i+a_{i}) $ , and one can travel from cell $ i $ to cell $ (i+a_{i}) $ using the $ i $ -th portal. Unfortunately, one cannot use the portal backwards, which means one cannot move from cell $ (i+a_{i}) $ to cell $ i $ using the $ i $ -th portal. It is easy to see that because of condition $ 1<=a_{i}<=n-i $ one can't leave the Line World using portals.

Currently, I am standing at cell $ 1 $ , and I want to go to cell $ t $ . However, I don't know whether it is possible to go there. Please determine whether I can go to cell $ t $ by only using the construted transportation system.

## 说明/提示

In the first sample, the visited cells are: $ 1,2,4 $ ; so we can successfully visit the cell $ 4 $ .

In the second sample, the possible cells to visit are: $ 1,2,4,6,7,8 $ ; so we can't visit the cell $ 5 $ , which we want to visit.

## 样例 #1

### 输入

```
8 4
1 2 1 2 1 2 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
8 5
1 2 1 2 1 1 1
```

### 输出

```
NO
```

# AI分析结果



# 算法分类
**模拟**

---

## 题解思路与算法分析
### 核心逻辑
题目本质是判断单向路径能否到达终点。所有传送门构成唯一路径，只需模拟跳跃过程：  
1. 从位置1开始跳跃  
2. 每次根据当前位置的传送值跳转  
3. 当到达目标位置或越界时终止  
4. 判断最终位置是否等于目标值  

### 解决难点
- **终止条件**：当跳跃位置 ≥ 目标时立即终止（因无法回退）  
- **边界处理**：需保证传送值满足 `1 <= a_i <= n-i`，防止越界  

### 题解对比
- **循环模拟**（Register/HNYLMS_MuQiuFeng）：直接遍历路径，最优时间复杂度 O(n)  
- **预处理跳转终点**（OdtreePrince）：将 a[i] 预处理为 i+a[i]，简化后续判断  
- **动态规划标记**（RainFestival）：记录可达节点，思路更通用但空间复杂度高  
- **Dijkstra算法**（Lips）：过度设计，正确但效率最低  

---

## 题解评分（≥4星）
1. **Register 题解**（5星）  
   - 简洁高效的循环实现  
   - 巧用空循环体完成跳跃逻辑  
   - 边界条件处理清晰  

2. **empty_zhm 题解**（4.5星）  
   - 极简代码风格（仅4行核心逻辑）  
   - 使用 `while(j<k) j+=a[j]` 直观模拟跳跃  
   - 三目运算符实现快速输出  

3. **OdtreePrince 题解**（4星）  
   - 预处理跳转终点提升可读性  
   - `while(a[j]!=t&&j!=n)` 实现路径追踪  
   - 递归思想直观呈现  

---

## 最优思路提炼
### 关键代码实现
```cpp
int current = 1;
while (current < t) {
    current += a[current];
}
cout << (current == t ? "YES" : "NO");
```
### 核心技巧
- **路径唯一性**：无需复杂搜索，直接顺序跳跃  
- **跳跃终止**：`current >= t` 时立即终止循环  
- **空间优化**：无需存储全部节点，仅维护当前坐标  

---

## 相似题目推荐
1. **[P1002 过河卒](https://www.luogu.com.cn/problem/P1002)**  
   （路径唯一性与动态规划）  
2. **[P1219 八皇后](https://www.luogu.com.cn/problem/P1219)**  
   （状态转移与回溯思想）  
3. **[P1036 选数](https://www.luogu.com.cn/problem/P1036)**  
   （组合路径搜索与剪枝）  

---

## 可视化算法设计
### 动画方案
1. **像素风格呈现**  
   - 使用 16 色调色板绘制牢房编号（类似 FC 游戏）  
   - 当前牢房高亮为黄色，历史路径显示为绿色轨迹  
   - 目标牢房始终显示为红色边框  

2. **跳跃过程演示**  
   ```javascript
   // 伪代码示例
   function animateJump() {
       highlight(currentCell); // 高亮当前格子
       playSound('jump');      // 播放跳跃音效
       currentCell += a[currentCell];
       if (currentCell === t) {
           playSuccessAnimation();
       } else if (currentCell > t) {
           playFailAnimation();
       }
   }
   ```

3. **交互功能**  
   - **速度调节**：滑块控制 0.5x~5x 倍速  
   - **单步执行**：按空格键逐步跳转  
   - **自动模式**：AI 自动完成路径追踪  

### 复古游戏化设计
- **音效设计**  
  - 跳跃：8-bit "beep" 短音  
  - 成功：上升旋律（类似《超级玛丽》过关）  
  - 失败：低沉"boom"音效  

- **积分系统**  
  - 每正确跳跃一次 +10 分  
  - 快速通关（<n/2 步）获得连击奖励  

---

## 个人心得摘录
> "for循环的好处就是三个语句可以执行很多的事" —— Register  
> 强调 C++ 循环语句的灵活性，将初始化、条件判断、迭代操作浓缩为一行  

> "杜绝抄袭，从我做起！！" —— HNYLMS_MuQiuFeng  
> 反映部分题解作者对代码原创性的重视，虽与算法无关但体现社区规范  

---

## 完整参考代码
```cpp
#include <iostream>
using namespace std;

int main() {
    int n, t;
    cin >> n >> t;
    int a[30001];
    for (int i = 1; i < n; ++i) cin >> a[i];
    
    int pos = 1;
    while (pos < t) {
        pos += a[pos];
    }
    cout << (pos == t ? "YES" : "NO");
    return 0;
}
```

---
处理用时：62.01秒