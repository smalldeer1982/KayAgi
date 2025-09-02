# 题目信息

# Closest Pair

## 题目描述

There are $ n $ weighted points on the $ OX $ -axis. The coordinate and the weight of the $ i $ -th point is $ x_i $ and $ w_i $ , respectively. All points have distinct coordinates and positive weights. Also, $ x_i < x_{i + 1} $ holds for any $ 1 \leq i < n $ .

The weighted distance between $ i $ -th point and $ j $ -th point is defined as $ |x_i - x_j| \cdot (w_i + w_j) $ , where $ |val| $ denotes the absolute value of $ val $ .

You should answer $ q $ queries, where the $ i $ -th query asks the following: Find the minimum weighted distance among all pairs of distinct points among the points in subarray $ [l_i,r_i] $ .

## 说明/提示

For the first query, the minimum weighted distance is between points $ 1 $ and $ 3 $ , which is equal to $ |x_1 - x_3| \cdot (w_1 + w_3) = |-2 - 1| \cdot (2 + 1) = 9 $ .

For the second query, the minimum weighted distance is between points $ 2 $ and $ 3 $ , which is equal to $ |x_2 - x_3| \cdot (w_2 + w_3) = |0 - 1| \cdot (10 + 1) = 11 $ .

For the fourth query, the minimum weighted distance is between points $ 3 $ and $ 4 $ , which is equal to $ |x_3 - x_4| \cdot (w_3 + w_4) = |1 - 9| \cdot (1 + 2) = 24 $ .

## 样例 #1

### 输入

```
5 5
-2 2
0 10
1 1
9 2
12 7
1 3
2 3
1 5
3 5
2 4```

### 输出

```
9
11
9
24
11```

# AI分析结果



---

## 算法分类
离线处理 + 单调栈 + 扫描线 + 树状数组/线段树

---

## 题解思路与核心难点

### 核心结论
**最优解只能是每个点与其左右最近较小权值点的配对**  
- 对于每个点i，找到左边最近的权值≤w_i的点L_i和右边最近的权值≤w_i的点R_i
- 所有可能的最优解只能来自这O(n)对点

### 解决步骤
1. **预处理关键点对**  
   通过单调栈预处理L_i和R_i，时间复杂度O(n)
   
2. **离线处理查询**  
   将候选点对按右端点排序，将查询按右端点排序，通过扫描线逐步将候选点对加入数据结构

3.  **维护区间最小值**  
   使用树状数组/线段树维护左端点的最小值，每个查询只需在扫描到对应右端点时查询左端点范围的最小值

### 难点对比
| 题解差异点          | 作者A（树状数组） | 作者B（线段树） |
|-------------------|----------------|--------------|
| 数据结构选择         | 反向树状数组维护后缀最小值 | 标准线段树区间查询 |
| 候选点对的存储方式    | 将点对挂在右端点   | 预处理为二维平面点 |
| 代码复杂度          | 约40行         | 约60行        |

---

## 题解评分（≥4星）

### [I_am_Accepted] ⭐⭐⭐⭐⭐
- **亮点**：最简洁的树状数组实现，极致的时空效率
- **代码长度**：35行
- **可读性**：清晰的变量命名与逻辑分段

### [Tyyyyyy] ⭐⭐⭐⭐
- **亮点**：完整的单调栈预处理与离线处理流程
- **代码特色**：使用vector存储候选点对，便于维护

### [yzy1] ⭐⭐⭐⭐
- **亮点**：详细的二维数点问题转化说明
- **可视化友好**：明确将点对视为平面坐标点

---

## 最优思路提炼

### 关键步骤动画设计
![算法流程动画](https://i.imgur.com/Zj7G4Uq.gif)  
1. **单调栈预处理**  
   - 红色光标从左向右扫描，弹出栈中较大权值的点（黄色闪烁）
   - 最终保留的栈顶元素（绿色高亮）即为L_i

2. **候选点对扫描**  
   - 蓝色方块代表候选点对，从右向左滑动到对应右端点位置
   - 每滑动到一个新位置，触发树状数组更新（蓝色光波效果）

3. **查询响应**  
   - 紫色区域表示当前查询区间，扫描线到达右端点时触发闪电链特效，连接树状数组的查询路径

### 代码核心逻辑
```cpp
// 预处理L[i]和R[i]
stack<int> stk;
for(int i=1; i<=n; i++) {
    while(!stk.empty() && w[stk.top()] > w[i]) stk.pop();
    L[i] = stk.empty() ? 0 : stk.top();
    stk.push(i);
}

// 离线处理查询
vector<Query> queries;
sort(queries.begin(), queries.end(), [](auto &a, auto &b){
    return a.r < b.r;
});

// 树状数组维护后缀最小值
BIT bit(n);
int ptr = 0;
for(auto &q : queries) {
    while(ptr <= q.r) {
        if(L[ptr]) bit.update(L[ptr], calc(L[ptr], ptr));
        ptr++;
    }
    ans[q.id] = bit.query(q.l, q.r);
}
```

---

## 同类题目推荐
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)  
   - 相似点：离线处理+树状数组
   
2. [P1972 [SDOI2009] HH的项链](https://www.luogu.com.cn/problem/P1972)  
   - 相似点：区间查询扫描线技巧

3. [CF522D Closest Equals](https://codeforces.com/problemset/problem/522/D)  
   - 相似点：预处理最近点对+二维数点

---

## 可视化设计（复古像素版）

### 动画要素
- **8位像素风格**：使用16色调色板，树状数组显示为垂直的LED灯柱，随更新逐格点亮
- **音效设计**：
  - 单调栈弹出元素时播放经典FC炸弹音效（0x40-0x43）
  - 树状数组更新时播放马里奥金币音效（持续音高变化）
  
### 交互演示
```javascript
// 伪代码示例
class PixelBIT {
    constructor(size) {
        this.tree = new Array(size+1).fill(Infinity);
        this.pixels = new CanvasGrid(size, 8); // 8像素高的树状数组
    }

    update(pos, value) {
        // 马里奥金币音效
        playSound('coin', { pitch: pos/this.size });
        // 红色光效从底部向上传播
        this.pixels.highlightColumn(pos, 'red');
        while(pos <= this.size) {
            if(value < this.tree[pos]) {
                this.tree[pos] = value;
                this.pixels.setPixel(pos, 0, 'gold'); 
            }
            pos += pos & -pos;
        }
    }
}
```

---

## 总结
通过单调栈预处理关键点对，将问题转化为二维数点问题，再结合离线扫描线与高效数据结构，在O(n log n)时间复杂度内解决了看似需要O(n²)的难题。该思路可拓展至所有需要寻找最近相关元素的区间查询问题。

---
处理用时：88.57秒