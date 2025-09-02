# 题目信息

# [USACO09MAR] Sand Castle S

## 题目描述

Farmer John has built a sand castle! Like all good castles, the walls have crennelations, that nifty pattern of embrasures (gaps) and merlons (filled spaces); see the diagram below. The N (1 <= N <= 25,000) merlons of his castle wall are conveniently numbered 1..N; merlon i has height M\_i (1 <= M\_i <= 100,000); his merlons often have varying heights, unlike so many.

He wishes to modify the castle design in the following fashion: he has a list of numbers B\_1 through B\_N (1 <= B\_i <= 100,000), and wants to change the merlon heights to those heights B\_1, ..., B\_N in some order (not necessarily the order given or any other order derived from the data).

To do this, he has hired some bovine craftsmen to raise and lower the merlons' heights. Craftsmen, of course, cost a lot of money. In particular, they charge FJ a total X (1 <= X <= 100) money per unit height added and Y (1 <= Y <= 100) money per unit height

reduced.

FJ would like to know the cheapest possible cost of modifying his sand castle if he picks the best permutation of heights. The answer is guaranteed to fit within a 32-bit signed integer.

Note: about 40% of the test data will have N <= 9, and about 60% will have N <= 18.

## 说明/提示

FJ's castle starts with heights of 3, 1, and 1. He would like to change them so that their heights are 1, 2, and 2, in some order. It costs 6 to add a unit of height and 5 to remove a unit of height.


FJ reduces the first merlon's height by 1, for a cost of 5 (yielding merlons of heights 2, 1, and 1). He then adds one unit of height to the second merlon for a cost of 6 (yielding merlons of heights 2, 2, and 1).


## 样例 #1

### 输入

```
3 6 5 
3 1 
1 2 
1 2 
```

### 输出

```
11 
```

# AI分析结果



### 综合分析与结论

**题目核心**：通过排序原数组和目标数组并一一对应，计算调整成本的最小总和。  
**贪心策略**：将原数组与目标数组分别排序后按升序配对，确保每个位置的调整量最小，从而总成本最低。  
**正确性保证**：通过交换论证法证明，任何逆序配对都会导致更高的总成本，因此排序后的顺序是最优解。  
**时间复杂度**：O(n log n)，主要由两次排序操作决定，适用于题目数据规模。

---

### 题解清单（评分≥4星）

1. **ysy666（5星）**  
   - **亮点**：代码简洁，注释清晰，直接排序后遍历计算差值，逻辑明确。  
   - **代码片段**：  
     ```cpp
     sort(a+1,a+1+n);
     sort(b+1,b+1+n);
     for(int i=1;i<=n;i++) {
         if(a[i]<b[i]) ans+=(b[i]-a[i])*x;
         else ans+=(a[i]-b[i])*y;
     }
     ```

2. **花千树（4星）**  
   - **亮点**：代码可读性高，变量命名规范，适合新手理解。  
   - **关键注释**：“用贪心做，排序两次，对号入座。”

3. **青鸟_Blue_Bird（4星）**  
   - **亮点**：代码附带详细样例分析，帮助理解排序策略的正确性。  
   - **个人心得**：“注意x和y不要打反了，我在这吃了好几次亏。”

---

### 最优思路与技巧提炼

1. **排序配对策略**：  
   - 将原数组 `M` 和目标数组 `B` 分别排序，按升序一一对应。  
   - 每个元素的调整量为 `|M_i - B_i|`，根据大小关系选择增加或减少操作。  
   - **数学证明**：通过交换任意两对元素后的成本对比，证明排序后总成本最小。

2. **实现细节**：  
   - 使用快速排序或优先队列（如 `priority_queue`）均可，时间复杂度相近。  
   - 注意 `X` 和 `Y` 的顺序，避免在计算时混淆增加和减少的单位成本。

---

### 同类型题目与算法套路

**常见贪心场景**：  
- **任务分配**：将两组数据排序后按序配对，最小化总成本。  
- **区间调度**：选择不重叠区间使得数量最多（按结束时间排序）。  
- **最小调整代价**：通过排序处理线性调整问题。

**推荐题目**：  
1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)  
2. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)  
3. [P1842 奶牛玩杂技](https://www.luogu.com.cn/problem/P1842)

---

### 个人心得摘录

- **调试教训**（青鸟_Blue_Bird）：“注意x和y不要打反了，我在这吃了好几次亏。”  
- **优化思路**（autoint）：“优先队列虽直观，但排序更高效，适合大数据。”  
- **贪心验证**（Kio_）：“通过样例反推策略，发现排序后的差值总和最小。”

---

### 可视化与算法演示

**动画设计**：  
1. **复古像素风格**：  
   - **UI**：8-bit 像素块表示原数组和目标数组的高度，颜色区分（原：蓝色，目标：绿色）。  
   - **操作**：排序后对应元素用箭头连接，红色箭头表示减少，黄色箭头表示增加。  
   - **音效**：调整时播放“金币”音效（增加：高音，减少：低音），成功配对后播放胜利音效。

2. **动态计算面板**：  
   - **步骤控制**：支持暂停/继续，步进调整过程。  
   - **成本累计**：实时显示当前总成本，颜色渐变反映增减操作。

**代码片段（JavaScript）**：  
```javascript
// 示例：Canvas绘制排序过程
function drawArrays(ctx, M, B) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    // 绘制原数组M（蓝色）
    M.forEach((height, i) => drawPixelBar(ctx, i * 20, 50, height, 'blue'));
    // 绘制目标数组B（绿色）
    B.forEach((height, i) => drawPixelBar(ctx, i * 20, 150, height, 'green'));
}
```

---

### 核心代码实现

**C++ 代码（关键逻辑）**：  
```cpp
#include <algorithm>
using namespace std;

int main() {
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> M(n), B(n);
    for (int i = 0; i < n; ++i) cin >> M[i] >> B[i];
    sort(M.begin(), M.end());
    sort(B.begin(), B.end());
    long long cost = 0;
    for (int i = 0; i < n; ++i) {
        if (M[i] < B[i]) cost += (B[i] - M[i]) * x;
        else cost += (M[i] - B[i]) * y;
    }
    cout << cost << endl;
    return 0;
}
```

---
处理用时：145.87秒