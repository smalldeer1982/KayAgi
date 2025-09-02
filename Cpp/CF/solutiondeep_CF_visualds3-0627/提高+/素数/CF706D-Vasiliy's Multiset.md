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



## **唯一算法分类**  
**01Trie树**

---

## **综合分析与结论**  
题目要求维护可重集并支持最大异或值查询，核心在于利用 **01Trie树** 的贪心特性：从二进制高位到低位逐位选择相反方向以最大化异或结果。  
**关键难点与解决方案**：  
1. **插入与删除的计数维护**：每个节点记录子树中数字的个数，插入时路径节点计数+1，删除时-1。  
2. **动态节点回收**：递归实现中通过维护子树大小，动态回收空节点（如 Zvelig1205 的题解）。  
3. **查询路径选择**：优先选择与当前位相反的子树，若无可用则选择相同子树。  

**可视化设计思路**：  
- **动画方案**：  
  - **Trie树结构**：用节点方块表示，内部显示当前位（0/1），颜色区分路径。  
  - **插入/删除**：路径节点颜色闪烁，计数增减动态显示。  
  - **查询**：高亮每一步选择的分支（红色为相反方向，绿色为相同方向）。  
- **复古像素风格**：  
  - 使用 8-bit 风格颜色（如深蓝背景、亮绿节点），Canvas 绘制网格状 Trie 结构。  
  - **音效**：插入/删除时播放“哔”声，查询成功时播放上扬音调。  
- **交互控制**：支持暂停/继续、单步执行，速度调节滑动条。  

---

## **题解清单 (≥4星)**  
1. **Zvelig1205（5星）**  
   - **亮点**：递归实现 + 动态节点回收，减少内存占用；代码结构清晰，附带垃圾回收机制。  
   - **心得**：通过 `siz` 判断子树是否为空，删除时自动回收节点，避免内存泄漏。  

2. **黑影洞人（4星）**  
   - **亮点**：结构体封装 Trie，代码规范；使用 `num` 数组维护计数，逻辑简洁。  
   - **代码片段**：  
     ```cpp  
     if (ch[u][v^1] && num[ch[u][v^1]]) u = ch[u][v^1]; // 优先选相反方向  
     ```

3. **StupidSeven（4星）**  
   - **亮点**：代码简洁易懂，适合模板学习；删除直接减少计数，无冗余操作。  

---

## **最优思路与技巧提炼**  
1. **核心数据结构**：01Trie树，每个节点维护子树大小 `num` 和值 `val`。  
2. **贪心查询**：从高位到低位优先选择相反方向，若子树为空则妥协。  
3. **递归节点回收**：删除时若子树大小为0，直接断开父节点指针。  
4. **位处理优化**：统一将数字转为固定位数（如32位），避免前导零干扰。  

**代码片段（Zvelig1205 的递归删除）**：  
```cpp  
void remove(int &i, int k, int dep) {  
    T[i].siz--;  
    if (dep == 31) {  
        if (!T[i].siz) bin.push(i), i = 0; // 回收节点  
        return;  
    }  
    remove(T[i].ch[k & 1], k >> 1, dep + 1);  
    if (!T[i].siz) bin.push(i), i = 0; // 回溯时回收  
}  
```  

---

## **同类型题与算法套路**  
1. **异或最值问题**：01Trie 是标准解法，如查询数组中两数最大异或值。  
2. **动态维护集合**：支持插入、删除的统计问题，常用计数标记或延迟删除。  
3. **二进制位贪心**：高位优先决策，如最大异或路径、子集最大异或和。  

**推荐题目**：  
1. [P4551 最长异或路径](https://www.luogu.com.cn/problem/P4551)  
2. [P4735 最大异或和](https://www.luogu.com.cn/problem/P4735)  
3. [P4592 异或](https://www.luogu.com.cn/problem/P4592)  

---

## **个人心得摘录**  
- **Zvelig1205**：递归写法更直观，但需注意栈深度；垃圾回收机制显著优化内存。  
- **堇墨浮华**：手动处理二进制位易出错，需仔细验证每一位的掩码计算。  

---

## **可视化与算法演示**  
**核心流程演示**：  
1. **插入数字 8**：  
   - 二进制：1000 → 路径右→右→右→左（高位到低位）。  
   - 节点计数+1，动画显示路径颜色渐变。  
2. **查询数字 3（二进制 0011）**：  
   - 优先选择高位相反（1→0），最终路径为 1011（11），异或结果 3^11=8。  
3. **删除数字 8**：  
   - 路径节点计数-1，叶子节点计数归零后回收，父节点指针置空。  

**复古像素效果**：  
- **Canvas 绘制**：每个节点为 16x16 像素方块，位值显示在中心。  
- **音效设计**：使用 Web Audio API 播放 8-bit 音效，插入成功时播放“升级”音，删除时“爆炸”音。  
- **自动演示模式**：按固定间隔逐步执行操作，模拟 AI 解题过程。  

**交互代码片段（伪代码）**：  
```javascript  
class TrieVisualizer {  
    constructor(canvas) {  
        this.nodes = new Map(); // 节点位置信息  
        this.drawNode(bit, x, y) { /* 绘制像素方块 */ }  
        this.playSound(effect) { /* 触发音效 */ }  
    }  
    insert(x) {  
        // 递归绘制插入动画，更新节点计数  
    }  
}  
```  

--- 

**总结**：01Trie 是解决动态异或最值问题的标准方法，递归实现与节点回收可优化内存，贪心查询是核心思想。通过可视化可直观理解路径选择与动态维护过程。

---
处理用时：79.29秒