# 题目信息

# Dancing Lessons

## 题目描述

There are $ n $ people taking dancing lessons. Every person is characterized by his/her dancing skill $ a_{i} $ . At the beginning of the lesson they line up from left to right. While there is at least one couple of a boy and a girl in the line, the following process is repeated: the boy and girl who stand next to each other, having the minimal difference in dancing skills start to dance. If there are several such couples, the one first from the left starts to dance. After a couple leaves to dance, the line closes again, i.e. as a result the line is always continuous. The difference in dancing skills is understood as the absolute value of difference of $ a_{i} $ variable. Your task is to find out what pairs and in what order will start dancing.

## 样例 #1

### 输入

```
4
BGBG
4 2 4 3
```

### 输出

```
2
3 4
1 2
```

## 样例 #2

### 输入

```
4
BBGG
4 6 1 5
```

### 输出

```
2
2 3
1 4
```

## 样例 #3

### 输入

```
4
BGBB
1 1 2 3
```

### 输出

```
1
1 2
```

# AI分析结果



# Dancing Lessons 舞蹈课程

## 题目描述

有 $n$ 个人参加舞蹈课程，每个人有一个舞蹈技能值 $a_i$ 和性别（B 表示男孩，G 表示女孩）。他们初始时从左到右排成一列。每当队列中存在相邻的男女时，重复以下过程：选择技能差值最小的男女组合（若差值相同则选最左边的组合），将其移出队列后两侧自动合并。要求输出所有出列组合的顺序。

## 标签
模拟

---

## 题解分析与结论

### 核心算法对比
所有题解均采用 **优先队列+双向链表** 的核心思路：
1. **优先队列**：维护当前所有相邻异性对的技能差值，快速获取最小值
2. **双向链表**：动态维护人员位置关系，高效处理节点删除与合并
3. **标记数组**：记录已出列人员，避免重复处理

### 最优题解亮点

#### 1. Zskioaert1106（⭐⭐⭐⭐⭐）
**关键亮点**：
- 完整定义结构体处理人员属性，代码可读性强
- 明确处理第二关键字（当差值相同时选最左对）
- 提供双题（CF45C/P1878）AC记录增强可信度

**核心代码**：
```cpp
struct people{ int l,r,a; bool x,vis; };
priority_queue<peoples> q; // 小顶堆

while(!q.empty()){
    int l=q.top().l, r=q.top().r;
    if(a[l].vis||a[r].vis) continue; 
    // 更新链表并处理新形成的相邻对
    a[l].l->r = a[r].r;
    if(新相邻对存在) q.push(...);
}
```

#### 2. Barewalk（⭐⭐⭐⭐）
**关键亮点**：
- 使用简洁的数组实现双向链表
- 边界处理技巧（vis[0]和vis[n+1]预标记）
- 代码结构紧凑，适合快速理解核心逻辑

**调试心得**：
> "重载运算符时要注意堆的比较方向，否则会得到反向排序结果"

#### 3. XiaoXia_uwu（⭐⭐⭐）
**创新点**：
- 使用 `std::map` 模拟链表结构
- 通过迭代器实现前驱后继查询
- 展示 STL 的灵活运用

**性能提示**：
> "路径压缩优化链表查询效率，避免超时"

---

## 关键思路总结
1. **动态维护机制**：优先队列保证每次取最小差值对，链表维护队列连续性
2. **无效对处理**：弹出队列元素时需检查双方是否已被标记
3. **新对生成逻辑**：合并后的左右邻居若为异性则入队
4. **时间复杂度**：O(n log n) 的队列操作主导整体复杂度

---

## 拓展思考
此类 **动态维护极值+快速合并** 的问题常见于：
1. 合并果子问题（洛谷 P1090）
2. 滑动窗口极值问题
3. 实时处理动态变化数据集的最值查询

---

## 推荐习题
1. [P1878 舞蹈课](https://www.luogu.com.cn/problem/P1878)（本题双倍经验）
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（优先队列基础应用）
3. [P2827 蚯蚓](https://www.luogu.com.cn/problem/P2827)（动态维护极值+偏移量技巧）

---
处理用时：47.16秒