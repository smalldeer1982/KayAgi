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



## 算法分类
离线处理、树状数组/线段树、单调栈

---

## 题解思路与算法要点

### 核心结论
最优点对只能是每个点与左右最近权值更小/相等的点构成：
- 左最近较小点 $L_i = \max\{j<i \mid w_j \leq w_i\}$
- 右最近较小点 $R_i = \min\{j>i \mid w_j \leq w_i\}$

### 解决难点
1. **候选点对降维**：将 $O(n^2)$ 点对缩减至 $O(n)$ 级别
2. **离线处理技巧**：将查询按右端点排序，扫描线维护区间最小值
3. **高效数据结构**：树状数组维护后缀最小值，单点更新+区间查询

---

## 高星题解推荐（≥4⭐）

### 1. I_am_Accepted（4.5⭐）
**亮点**：  
- 严格数学证明最优性条件  
- 清晰转化二维数点问题  
- 树状数组维护后缀最小值，代码简洁  

### 2. Tyyyyyy（4⭐）  
**亮点**：  
- 双单调栈预处理 L/R 数组  
- 离线查询与候选点对统一处理  
- 树状数组实现极简  

### 3. orz_z（4⭐）  
**亮点**：  
- 离散化权值优化预处理  
- 双向扫描处理左右贡献  
- 线段树实现完整可读  

---

## 最优思路提炼

### 关键步骤
1. **预处理 L/R 数组**  
   - 左向单调栈求 $L_i$（维护递增权值序列）  
   - 右向单调栈求 $R_i$（维护递增权值序列）
   ```cpp
   // 左向单调栈示例
   stack<int> stk;
   for(int i=1; i<=n; ++i){
       while(!stk.empty() && w[stk.top()] > w[i]) stk.pop();
       L[i] = stk.empty() ? 0 : stk.top();
       stk.push(i);
   }
   ```

2. **生成候选点对**  
   - 每个点生成 $(L_i, i)$ 和 $(i, R_i)$ 点对  
   - 计算权值 $(x_j-x_i)(w_i + w_j)$  

3. **离线处理查询**  
   - 按查询右端点排序  
   - 扫描线维护树状数组，边插入候选点对边回答查询  

---

## 同类型题推荐
1. **二维数点问题**：CF522D（Closest Equals）
2. **离线区间最值**：洛谷P1972（HH的项链）
3. **单调栈应用**：LeetCode 84（柱状图最大矩形）

---

## 可视化设计

### 算法演示方案
**步骤分解动画**：  
1. **预处理阶段**  
   - 动态展示单调栈操作：高亮当前点，弹出栈顶元素，标记 L/R 指针  
   - 像素风格绘制坐标轴，用不同颜色标记候选点对  

2. **离线查询阶段**  
   - 树状数组更新：显示候选点对插入位置（红色高亮更新点）  
   - 查询回答：绿色高亮查询区间，显示最小值提取路径  

**交互功能**：  
- **速度调节**：滑块控制动画速度（0.5x~3x）  
- **单步执行**：按钮逐帧查看栈操作/树状数组更新  
- **音效反馈**：  
  - 弹出栈时播放"blip"短音  
  - 找到候选点对时播放"coin"音效  

### 复古风格实现
**Canvas 绘制**：  
```javascript
// 绘制坐标轴与点
ctx.fillStyle = '#8B8B8B';
ctx.fillRect(50, 150, 600, 2); // 横轴
points.forEach((p, i) => {
  drawPixel(p.x*60 + 50, 140 - i*10, '#FF5555'); // 点像素块
});
```

**音效触发**：  
```javascript
function playSound(type) {
  const osc = audioCtx.createOscillator();
  osc.frequency.value = type === 'update' ? 880 : 440;
  osc.connect(audioCtx.destination);
  osc.start(); osc.stop(0.1);
}
```

---

## 核心代码实现

### 树状数组维护最小值
```cpp
struct BIT {
  ll c[N];
  void upd(int x, ll v) { // 逆序更新
    for(; x; x -= x&-x) c[x] = min(c[x], v);
  }
  ll ask(int x) { // 正序查询
    ll res = INF;
    for(; x<=n; x += x&-x) res = min(res, c[x]);
    return res;
  }
};
```

### 主处理逻辑
```cpp
// 预处理候选点对
for(int i=1; i<=n; ++i) {
  if(L[i]) segs.push_back({L[i], i, calc(L[i], i)});
  if(R[i]) segs.push_back({i, R[i], calc(i, R[i)});
}

// 离线查询处理
sort(segs.begin(), segs.end(), [](auto &a, auto &b){
  return a.r < b.r; // 按右端点排序
});
sort(queries.begin(), queries.end(), [](auto &a, auto &b){
  return a.r < b.r;
});

BIT bit;
int ptr = 0;
for(auto &q : queries) {
  while(ptr < segs.size() && segs[ptr].r <= q.r) {
    bit.upd(segs[ptr].l, segs[ptr].val);
    ptr++;
  }
  ans[q.id] = bit.ask(q.l);
}
```

---
处理用时：63.25秒