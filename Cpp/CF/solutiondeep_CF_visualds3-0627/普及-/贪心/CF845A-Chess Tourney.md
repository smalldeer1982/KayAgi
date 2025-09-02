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



## 唯一算法分类
贪心算法

---

## 综合分析与结论

### 核心思路与难点
题目要求将 2n 个选手分成两组，使得第一组无论怎么配对都能全胜。关键点在于必须保证第一组所有选手的 rating 严格大于第二组所有选手的 rating。

**贪心策略**：将选手 rating 排序后，前 n 个作为第二组，后 n 个作为第一组。此时若第二组的最大值（即排序后的第 n 个元素）严格小于第一组的最小值（即排序后的第 n+1 个元素），则满足条件。否则无法保证必胜。

**难点**：正确推导出中间元素的比较条件，并理解其正确性。需严格保证第一组的最小值大于第二组的最大值。

### 可视化设计思路
1. **排序过程**：用动画展示数组从小到大排序，颜色区分元素大小。
2. **分组高亮**：将前 n 个标为蓝色（第二组），后 n 个标为红色（第一组）。
3. **关键比较**：高亮第 n 和第 n+1 个元素，显示比较结果（绿色箭头表示满足条件，红色叉号表示不满足）。
4. **像素风格**：采用 8-bit 风格，音效提示比较结果（成功播放上升音调，失败播放低沉音效）。

---

## 题解清单 (≥4星)

### 1. ShineEternal（4.5星）
- **亮点**：代码简洁，注释明确，直接调用标准库排序。
- **代码片段**：
  ```cpp
  sort(a+1,a+2*n+1);
  if(a[n]<a[n+1]) printf("YES\n");
  ```

### 2. Elma_（4星）
- **亮点**：思路描述清晰，强调相等情况的处理。
- **代码片段**：
  ```cpp
  sort(a+1, a+2*n+1);
  if(a[n] < a[n+1]) cout<<"YES";
  ```

### 3. Soshine_溯闪（4星）
- **亮点**：详细说明贪心思想，解释分组合理性。
- **代码片段**：
  ```cpp
  sort(a+1,a+1+n+n);
  if(a[n]<a[n+1]) cout<<"YES"<<endl;
  ```

---

## 最优思路提炼
**排序+贪心分界点比较**：
1. 排序所有 rating。
2. 取排序后的第 n 和 n+1 个元素，若 `a[n] < a[n+1]`，则前 n 个为第二组，后 n 个为第一组，确保全胜。

---

## 同类型题与算法套路
**类似题目套路**：
- 将数组分割为两部分，满足极值约束（如最大值最小化）。
- 贪心策略中通过排序寻找分界点。

**推荐题目**：
1. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
2. [P1209 [USACO1.3]修理牛棚](https://www.luogu.com.cn/problem/P1209)
3. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995)

---

## 个人心得摘录
- **王炸拆开打**：首次提交忘记排序，提醒排序是核心步骤。
- **Fat_Fish**：通过具体例子（1,3,4,4）验证思路的正确性。

---

## 可视化与算法演示

### 核心算法动画设计
1. **排序阶段**：
   - 元素逐个冒泡排序，动态显示交换过程。
   - 音效：每次交换播放“哔”声。
2. **分组阶段**：
   - 绘制竖线分割前 n 和后 n 元素，标为蓝/红色块。
3. **比较阶段**：
   - 高亮第 n 和 n+1 元素，显示比较动画。
   - 若满足条件，两元素间显示绿色箭头；否则显示红色屏障。

### 复古游戏化设计
- **像素风格**：16色调色板，元素用 8x8 像素块表示。
- **音效**：
  - 成功：8-bit 胜利音效（短促上升旋律）。
  - 失败：低沉“错误”音效。
- **自动演示**：按空格切换手动/自动模式，自动模式下算法逐步执行。

```javascript
// 伪代码示例（Canvas绘制关键步骤）
function drawArray(arr, n) {
  for (let i = 0; i < arr.length; i++) {
    const color = i < n ? "#0000FF" : "#FF0000"; // 前蓝后红
    drawPixelBlock(i, arr[i], color);
    if (i === n || i === n+1) {
      highlightBlock(i, arr[i]); // 高亮分界点
    }
  }
}
```

---

## 代码实现（关键逻辑）
```cpp
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    int n, a[205];
    cin >> n;
    for (int i = 0; i < 2*n; i++) cin >> a[i];
    sort(a, a + 2*n);
    cout << (a[n-1] < a[n] ? "YES" : "NO"); // 注意下标从0开始
    return 0;
}
```

---
处理用时：129.35秒