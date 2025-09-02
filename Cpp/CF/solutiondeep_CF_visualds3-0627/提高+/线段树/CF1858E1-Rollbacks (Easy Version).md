# 题目信息

# Rollbacks (Easy Version)

## 题目描述

This is an easy version of this problem. The only difference between the versions is that you have to solve the hard version in online mode. You can make hacks only if both versions of the problem are solved.

You have an array $ a $ , which is initially empty. You need to process queries of the following types:

- + $ x $ — add the integer $ x $ to the end of the array $ a $ .
- - $ k $ — remove the last $ k $ numbers from the array $ a $ .
- ! — roll back the last active change (i.e., make the array $ a $ the way it was before the change). In this problem, only queries of the first two types (+ and -) are considered as changes.
- ? — find the number of distinct numbers in the array $ a $ .

## 说明/提示

In the first example array $ a $ changes as follows:

1. After the first query, $ a=[1] $ .
2. After the second query, $ a=[1,2] $ .
3. After the third query, $ a=[1,2,2] $ .
4. At the moment of the fourth query, there are $ 2 $ distinct intergers in the array $ a $ : $ 1 $ and $ 2 $ .
5. After the fifth query, $ a=[1,2] $ (rolled back the change + 2).
6. After the sixth query, $ a=[1,2,3] $ .
7. After the seventh query, $ a=[1] $ .
8. At the moment of the eigth query, there is only one $ 1 $ in the array $ a $ .
9. After the ninth query, $ a=[1,1] $ .
10. At the moment of the tenth query, there are only two $ 1 $ in the array $ a $ .

In the second example array $ a $ changes as follows:

1. After the first query, $ a=[1] $ .
2. After the second query, $ a=[1,1\,000\,000] $ .
3. At the moment of the third query, there are $ 2 $ distinct intergers in the array $ a $ : $ 1 $ and $ 1\,000\,000 $ .
4. After the fourth query, $ a=[1] $ (rolled back the change + 1000000).
5. After the fifth query, $ a=[] $ (rolled back the change + 1).
6. At the moment of the sixth query, there are no integers in the array $ a $ , so the answer to this query is $ 0 $ .

## 样例 #1

### 输入

```
10
+ 1
+ 2
+ 2
?
!
+ 3
- 2
?
+ 1
?```

### 输出

```
2
1
1```

## 样例 #2

### 输入

```
6
+ 1
+ 1000000
?
!
!
?```

### 输出

```
2
0```

# AI分析结果



---

### 唯一算法分类  
**离线操作树 + 倍增祖先**

---

### 综合分析与结论  

#### **核心问题与难点**  
- **动态版本管理**：需支持增删操作、撤销操作（仅回滚增删）、实时查询不同元素数  
- **高效跳转**：删除 `-k` 需快速跳转到 k 步前的状态  
- **离线统计**：无法在线实时计算不同元素数，需预处理所有操作后的结果  

#### **题解共性思路**  
1. **操作树建模**：将每个增删操作视为树节点，构建操作树  
2. **倍增跳转**：预处理每个节点的 2^k 级祖先，实现 O(logk) 时间删除  
3. **离线 DFS**：遍历操作树，动态维护元素计数（类似莫队思想）  
4. **栈维护历史**：用栈记录操作序列，支持撤销时快速回退  

#### **可视化设计思路**  
- **树形结构展示**：Canvas 绘制操作树，新增节点时生成方块并连线  
- **倍增跳转动画**：删除操作时高亮路径，逐级跳转祖先节点  
- **计数动态显示**：右侧面板实时显示当前元素集合及不同元素数  
- **操作栈可视化**：底部显示操作栈，撤销时弹出栈顶元素并回退指针  

---

### 题解评分 (≥4星)  

#### 1. Hisaishi_Kanade（⭐⭐⭐⭐⭐）  
- **亮点**：  
  - 完整实现操作树 + 倍增跳转逻辑  
  - DFS 离线统计不同元素数，代码简洁  
  - 注释清晰，数据结构设计合理  
- **核心代码**：  
  ```cpp
  void dfs(int id) {
      if(id) add(v[id]); // 进入节点时添加元素
      ans[id] = ret;     // 记录当前答案
      for(auto nxt : e[id]) dfs(nxt);
      del(v[id]);        // 回溯时删除元素
  }
  ```

#### 2. Xy_top（⭐⭐⭐⭐）  
- **亮点**：  
  - 简洁的倍增数组实现  
  - 明确区分操作类型与状态转移  
  - 代码注释详细，易于理解  
- **核心代码**：  
  ```cpp
  foR(j, 20, 0) {        // 倍增跳转祖先
      if(x >= (1 << j)) {
          x -= (1 << j);
          p = f[p][j];
      }
  }
  ```

#### 3. Unnamed114514（⭐⭐⭐⭐）  
- **亮点**：  
  - 明确解释操作树与计数逻辑  
  - 代码结构清晰，变量命名规范  
  - 包含调试心得（链接赛时代码）  

---

### 最优思路或技巧提炼  

#### **关键数据结构**  
- **倍增数组** `f[i][k]`：存储节点 i 的 2^k 级祖先，实现 O(logk) 跳转  
- **操作栈**：记录历史操作序列，支持撤销时回退指针  
- **计数桶** `cnt[]`：哈希表统计元素出现次数，维护全局计数器 `ret`  

#### **核心优化**  
- **离线 DFS 统计**：避免在线计算的复杂度，统一处理所有查询  
- **倍增预处理**：将删除操作的线性跳转优化为对数时间  
- **操作树节点复用**：通过父子关系共享历史状态，减少空间开销  

---

### 同类型题与算法套路  

1. **历史版本查询**：如可持久化数组、回滚莫队  
2. **动态祖先跳转**：如 LCA 倍增算法、跳表  
3. **离线操作处理**：如操作树遍历、逆序处理  

---

### 推荐相似题目  
1. **P3919** - 可持久化数组（模板）  
2. **P5055** - 可持久化平衡树  
3. **P3834** - 静态区间第 k 小（主席树）  

---

### 个人心得摘录  

- **倍增数组初始化**：需注意预处理顺序（先处理低次幂祖先）  
- **DFS 回溯删除**：必须严格对称（进入时 add，退出时 del）  
- **栈维护操作序列**：撤销操作仅影响最近一次增/删，需精准回退  

---

### 可视化与算法演示  

#### **像素风格设计**  
- **颜色方案**：  
  - 新增节点：绿色方块  
  - 删除路径：红色高亮  
  - 当前指针：黄色边框  
- **音效设计**：  
  - 添加/删除：8-bit 点击音  
  - 撤销操作：回声音效  
  - 查询成功：胜利旋律  

#### **Canvas 动画示例**  
```javascript
// 伪代码：绘制操作树节点
function drawNode(node, x, y) {
    ctx.fillStyle = node === current ? '#FFD700' : '#00FF00';
    ctx.fillRect(x, y, 30, 30);
    ctx.strokeStyle = '#000000';
    ctx.strokeText(node.val, x + 10, y + 20);
}
```

#### **自动演示逻辑**  
- **步骤分解**：按输入顺序逐步渲染操作，同步更新指针位置  
- **速度控制**：滑块调节每步间隔（100ms~2000ms）  
- **回滚特效**：撤销时播放逆序动画，栈顶元素渐变消失  

---

### 代码片段（Hisaishi_Kanade 核心部分）  

```cpp
// 操作树构建与倍增预处理
if(op[i] == '+') {
    f[++cq][0] = jmp; // 新节点的父节点为当前指针
    for(k=1; k<=21; k++) 
        f[cq][k] = f[f[cq][k-1]][k-1]; // 倍增预处理
    jmp = cq; // 移动当前指针
    v[cq] = x; 
    q.push(i); // 记录操作序列
}
```

```cpp
// DFS 统计不同元素数
void dfs(int id) {
    if(id) add(v[id]); // 进入节点时添加元素
    ans[id] = ret;     // 记录当前答案
    for(auto nxt : e[id]) dfs(nxt);
    del(v[id]);        // 回溯时删除元素
}
```

---
处理用时：85.81秒