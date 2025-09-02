# 题目信息

# Chess Tourney

## 题目描述

Berland annual chess tournament is coming!

Organizers have gathered $ 2·n $ chess players who should be divided into two teams with $ n $ people each. The first team is sponsored by BerOil and the second team is sponsored by BerMobile. Obviously, organizers should guarantee the win for the team of BerOil.

Thus, organizers should divide all $ 2·n $ players into two teams with $ n $ people each in such a way that the first team always wins.

Every chess player has its rating $ r_{i} $ . It is known that chess player with the greater rating always wins the player with the lower rating. If their ratings are equal then any of the players can win.

After teams assignment there will come a drawing to form $ n $ pairs of opponents: in each pair there is a player from the first team and a player from the second team. Every chess player should be in exactly one pair. Every pair plays once. The drawing is totally random.

Is it possible to divide all $ 2·n $ players into two teams with $ n $ people each so that the player from the first team in every pair wins regardless of the results of the drawing?

## 样例 #1

### 输入

```
2
1 3 2 4
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
1
3 3
```

### 输出

```
NO
```

# AI分析结果



---

## 唯一算法分类
排序、贪心

---

## 综合分析与结论
**核心思路**：将选手按rating从小到大排序后，将数组分成前n和后n两组。若前n组的最大值（即排序后的第n个元素）严格小于后n组的最小值（即第n+1个元素），则分法可行。  
**关键难点**：如何保证分组的严格性，当存在相邻元素相等时无法满足条件。  
**解决亮点**：通过排序后的中间断点比较，实现了 O(n log n) 时间复杂度的高效判断。

**可视化设计**：
1. **动画流程**：以像素方块表示排序后的数组，用红色高亮第n和n+1号元素，动态比较两者的数值大小。
2. **音效设计**：比较时播放“滴”声，满足条件时播放8-bit胜利音效，否则播放失败音效。
3. **复古风格**：采用16色调色板，用绿色渐变表示排序后的升序排列，分割线用闪烁的黄色像素表示。

---

## 题解清单（评分 ≥4星）
1. **ShineEternal（5星）**  
   - 代码最简洁，直接调用标准库排序，条件判断清晰。  
   - 关键注释点明贪心思想，可读性极佳。

2. **Nivi（4星）**  
   - 用自然语言解释分组逻辑，适合新手理解。  
   - 代码结构规范，包含完整输入输出处理。

3. **Soshine_溯闪（4星）**  
   - 详细分析贪心策略的正确性，补充数学证明思路。  
   - 变量命名清晰，注释完备。

---

## 核心代码实现
```cpp
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    int n, a[201];
    cin >> n;
    for (int i = 0; i < 2 * n; ++i) cin >> a[i];
    sort(a, a + 2 * n);
    cout << (a[n-1] < a[n] ? "YES" : "NO");
    return 0;
}
```

---

## 同类型题与算法套路
1. **有序分组问题**：如CF1526C2（划分非负子序列），同样需要排序后决策分组。  
2. **极值比较模型**：当问题可转化为比较排序后的相邻元素时，均可使用类似策略。

---

## 推荐相似题目
1. P1090 [NOIP2004 提高组] 合并果子（贪心+优先队列）  
2. CF978B File Name（排序后相邻元素处理）  
3. P1106 删数问题（贪心选择极值点）

---

## 个人心得摘录
> 王炸拆开打：  
> “第一遍提交忘记了排序，直接WA。排序是此类问题的核心前置步骤！”  
> **教训**：处理分组前必须确保数据有序。

---

## 可视化算法演示
```html
<!DOCTYPE html>
<div id="canvas-wrapper" style="font-family: 'Courier', monospace;"></div>
<script>
const ratings = [1,3,2,4]; // 示例输入
const n = 2;

// 排序并高亮比较
function visualize() {
    const sorted = [...ratings].sort((a,b) => a-b);
    let display = sorted.map((v,i) => 
        i === n-1 ? `<span style="color:red">${v}</span>` :
        i === n ? `<span style="color:blue">${v}</span>` : v
    ).join(' ');
    document.getElementById('canvas-wrapper').innerHTML = 
        `${display}<br>Result: ${sorted[n-1] < sorted[n] ? 'YES' : 'NO'}`;
}
visualize();
</script>
```

---
处理用时：75.28秒