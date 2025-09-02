# 题目信息

# [USACO08MAR] Pearl Pairing G

## 题目描述

At Bessie's recent birthday party, she received $N(2 \le N \le 10^5,N\equiv0\pmod{2})$ pearls, each painted one of C different colors ($1\le C \le N$).

Upon observing that the number of pearls $N$ is always even, her creative juices flowed and she decided to pair the pearls so that each pair of pearls has two different colors.

Knowing that such a set of pairings is always possible for the supplied testcases, help Bessie perform such a pairing. If there are multiple ways of creating a pairing, any solution suffices.

在 Bessie 最近的生日聚会上，她收到 $N(2\le N \le 10^5,N\equiv0\pmod{2})$ 颗珍珠。一共有 $C$ 种颜色的珍珠（$1\le C \le N$），第 $i$ 种颜色的珍珠有 $C_i$ 颗。


观察到珍珠的数量 $N$ 总是偶数，她的创意来了，决定配对珍珠，使每对珍珠有两种不同的颜色。数据保证存在答案。请帮助 Bessie 执行这样的配对，如果有多种配对的方法，输出任意一种即可。

## 说明/提示

There are $8$ pearls and $3$ different colors. Two pearls have color $\mathrm{I}$; two have color $\mathrm{II}$; four have color $\mathrm{III}$.


Bessie pairs each pearl of color $\mathrm{III}$ with one of color $\mathrm{I}$ and $\mathrm{Ii}$.

说明：有 $8$ 颗珍珠和 $3$ 种不同的颜色。两颗珍珠颜色为 $1$，两颗珍珠颜色为 $2$，四颗珍珠颜色为 $3$。

Bessie 将每颗颜色为 $3$ 的珍珠与颜色为 $1$ 和 $2$ 的珍珠配对。

感谢@[线段木](https://www.luogu.com.cn/user/33930) 提供翻译，@[PineappleSummer](https://www.luogu.com.cn/user/880187) 修正翻译以及提供 $\LaTeX$。

## 样例 #1

### 输入

```
8 3 
2 
2 
4 
```

### 输出

```
1 3 
1 3 
2 3 
3 2 
```

# AI分析结果



### 综合分析与结论

本题要求将珍珠两两配对，保证每对颜色不同。关键在于利用题目条件（每种颜色数量不超过N/2），通过构造数组并前后分半配对，确保颜色不重复。各题解的核心思路一致，直接展开颜色数组后配对前N/2与后N/2元素，时间复杂度O(N)，空间O(N)。

**贪心策略与可视化设计**  
- **贪心选择**：将颜色展开为数组，第i个元素与i+N/2元素配对。  
- **正确性证明**：因每种颜色数量≤N/2，同一颜色无法同时在前后半段出现。  
- **可视化方案**：动画展示颜色数组分块，逐步高亮配对元素，显示颜色差异。  

若采用复古像素风格，可用不同色块表示颜色，配对时动态连接前后元素，配以8-bit音效增强交互。

---

### 题解清单（≥4星）

1. **Waddles（★★★★★）**  
   - **亮点**：无需排序，直接展开数组后配对，代码简洁高效。  
   - **代码可读性**：结构清晰，注释明确，适合快速实现。  

2. **御·Dragon（★★★★★）**  
   - **亮点**：理论分析透彻，强调抽屉原理，代码同样高效。  
   - **个人心得**：“数据太水，不排序也能过”反映实际测试中的优化空间。  

3. **Exber（★★★★★）**  
   - **亮点**：代码极简，直接数组展开配对，适合新手理解。  

---

### 核心代码实现

```cpp
#include <cstdio>
int main() {
    int n, c, tot = 0, num[100005];
    scanf("%d%d", &n, &c);
    for (int i = 1; i <= c; ++i) {
        int x; scanf("%d", &x);
        while (x--) num[++tot] = i;
    }
    for (int i = 1; i <= n/2; ++i)
        printf("%d %d\n", num[i], num[i + n/2]);
    return 0;
}
```

**实现思想**：将颜色依次存入数组，前N/2元素与后N/2元素一一配对，确保颜色不同。

---

### 同类型题目与算法套路

- **贪心构造**：适用于需满足两两配对条件且存在数学保证的题目。  
- **常见场景**：区间调度、资源分配、配对问题（如任务分配、学生分组）。  

**推荐题目**：  
1. [P3143 [USACO16OPEN] Diamond Collector S](https://www.luogu.com.cn/problem/P3143)  
2. [LeetCode 455. 分发饼干](https://leetcode-cn.com/problems/assign-cookies/)  
3. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)  

---

### 个人心得摘录

- **qingfengwuhui**：最初贪心策略因剩余颜色处理不当WA，最终通过调整配对顺序解决，强调正确性证明的重要性。  
- **木木！**：“找不出反例就对了”体现贪心题的经验主义调试思维。  

---

### 可视化设计要点（复古像素风格）

1. **Canvas绘制**：  
   - 珍珠用色块表示，按输入顺序排列成两行（前/后半段）。  
   - 配对时动态绘制连线，高亮当前配对块。  

2. **音效设计**：  
   - 配对成功：清脆“叮”声。  
   - 错误尝试：低沉“哔”声。  

3. **自动演示**：  
   - 按固定速度逐步配对，用户可暂停/调整速度。  

**交互示例**：  
```javascript
// 伪代码：Canvas配对动画
function drawPairing() {
    for (let i = 0; i < n/2; i++) {
        highlight(i);          // 前半段元素
        highlight(i + n/2);    // 后半段元素
        drawLine(i, i + n/2);  // 连接线
        playSound('pair');
        delay(500);
    }
}
```

**游戏化**：每正确配对一对得分，连续正确触发连击奖励，增强学习趣味性。

---
处理用时：64.07秒