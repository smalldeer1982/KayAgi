# 题目信息

# Vasiliy's Multiset

## 题目描述

Author has gone out of the stories about Vasiliy, so here is just a formal task description.

You are given $ q $ queries and a multiset $ A $ , initially containing only integer $ 0 $ . There are three types of queries:

1. "+ x" — add integer $ x $ to multiset $ A $ .
2. "- x" — erase one occurrence of integer $ x $ from multiset $ A $ . It's guaranteed that at least one $ x $ is present in the multiset $ A $ before this query.
3. "? x" — you are given integer $ x $ and need to compute the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/728a3690d3a76b81fb1ccb07b4c04b8d10b1870d.png), i.e. the maximum value of bitwise exclusive OR (also know as XOR) of integer $ x $ and some integer $ y $ from the multiset $ A $ .

Multiset is a set, where equal elements are allowed.

## 说明/提示

After first five operations multiset $ A $ contains integers $ 0 $ , $ 8 $ , $ 9 $ , $ 11 $ , $ 6 $ and $ 1 $ .

The answer for the sixth query is integer ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/4b442d72cf0f109da9eae35430cf9dc9dfa35fdf.png) — maximum among integers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/c712973b7cb6a6b393c3b423fc78dda636ebb034.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/e9b3f94b7acd1861f4b82fb60d691b2bd163374e.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/1bf5d0b4ff98720973629f7915ae529e790539ba.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/9023c8bab139f08429005ae47d2d497f5795be9b.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/e21b15be88af70287d01c0b8f13ae0d351197a9c.png).

## 样例 #1

### 输入

```
10
+ 8
+ 9
+ 11
+ 6
+ 1
? 3
- 8
? 3
? 8
? 11
```

### 输出

```
11
10
14
13
```

# AI分析结果



---

## **唯一算法分类**  
**01-Trie 树**

---

## **综合分析与结论**  
### **核心思路**  
题目要求维护一个支持插入、删除、求最大异或值的多重集。所有题解均采用 **01-Trie 树**，通过以下步骤实现：  
1. **插入**：将数字按二进制位从高到低插入 Trie，每个节点维护计数器。  
2. **删除**：沿路径递减计数器，若计数器归零则回收节点（部分题解优化）。  
3. **查询**：贪心地选择与当前位相反的路径，最大化异或值。  

### **解决难点**  
- **动态维护可用路径**：通过计数器标记节点是否可用，避免删除后误访问无效路径。  
- **位处理顺序**：必须从最高位到最低位处理，确保贪心策略的正确性。  

### **可视化设计思路**  
- **动画方案**：  
  1. **插入/删除**：显示二进制位逐层插入/删除，高亮当前处理的位（如红色方块），计数器数值动态变化。  
  2. **查询路径**：用绿色箭头标注每一步选择的相反位分支，蓝色箭头表示被迫选择的相同位分支。  
  3. **像素风格**：用 8-bit 风格节点（方格），0/1 分支用不同颜色区分，删除时节点变灰并播放“哔”音效。  
- **交互功能**：  
  - **步进控制**：支持暂停/继续/单步执行，观察每一位处理细节。  
  - **自动演示**：AI 模式自动执行插入、删除、查询操作，展示算法流程。  

---

## **题解清单 (≥4星)**  
### **1. 作者：npqenqpve（5星）**  
- **亮点**：代码简洁，迭代实现易于理解；直接使用计数器标记可用性，逻辑清晰。  
- **关键代码**：  
  ```cpp
  void insert(int x) { /* 按位插入并更新计数器 */ }
  int querymax(int x) { /* 贪心选择相反位 */ }
  ```

### **2. 作者：Zvelig1205（4.5星）**  
- **亮点**：递归实现 + 动态节点回收（栈缓存），优化空间效率；附带调试心得。  
- **心得摘录**：  
  > “动态开点的数据结构需要垃圾回收，否则空间爆炸。栈缓存删除的节点显著优化内存。”  

### **3. 作者：StupidSeven（4星）**  
- **亮点**：完整注释 + 标准模板，适合新手学习；变量命名规范，可读性强。  

---

## **最优思路提炼**  
### **关键技巧**  
1. **位优先策略**：从最高位到最低位处理，确保贪心的正确性。  
2. **计数器维护**：节点计数器标记路径有效性，删除时递减而非直接删除节点。  
3. **动态回收优化**：使用栈回收删除的节点，减少内存占用（Zvelig1205 题解）。  

### **代码片段**  
```cpp
// 插入操作（迭代实现）
void insert(int x) {
    int u = 1;
    for (int i = 30; i >= 0; i--) {
        int v = (x >> i) & 1;
        if (!ch[u][v]) ch[u][v] = ++cnt;
        u = ch[u][v];
        num[u]++;
    }
}
```

---

## **同类型题与算法套路**  
### **类似题目**  
1. **最长异或路径**（洛谷 P4551）：树上前缀异或 + 01-Trie。  
2. **最大异或和**（洛谷 P4735）：可持久化 01-Trie。  

### **通用套路**  
- **异或极值问题**：优先考虑 01-Trie 或线性基。  
- **动态集合维护**：结合计数器和节点回收优化空间。  

---

## **推荐题目**  
1. **P4551**（最长异或路径）  
2. **P4735**（最大异或和）  
3. **P5283**（异或粽子）  

---

## **个人心得摘录**  
- **初始值处理**：初始必须插入 0，否则空集合查询会出错。  
- **位运算优先级**：`x >> i & 1` 需加括号避免优先级错误。  

---

## **可视化实现（伪代码）**  
```javascript
// 绘制 Trie 节点（像素风格）
function drawNode(x, y, count) {
    ctx.fillStyle = count > 0 ? "#00FF00" : "#808080";
    ctx.fillRect(x, y, 32, 32); // 32x32 像素方块
}

// 查询路径动画
function animateQuery(x) {
    let u = 1, path = [];
    for (let i = 30; i >= 0; i--) {
        let bit = (x >> i) & 1;
        let next = hasOppositeBit(u, bit) ? bit ^ 1 : bit;
        path.push({u, bit: next});
        u = ch[u][next];
    }
    playSound("select"); // 触发音效
    highlightPath(path); // 高亮路径
}
```

---

**可视化交互示例**  
- **操作**：点击按钮插入 `9`（二进制 `1001`），观察 Trie 树逐层扩展。  
- **效果**：红色方块表示当前处理位，绿色路径表示最终查询路线。

---
处理用时：70.34秒