# 题目信息

# Genokraken

## 题目描述

This is an interactive problem.

Upon clearing the Waterside Area, Gretel has found a monster named Genokraken, and she's keeping it contained for her scientific studies.

The monster's nerve system can be structured as a tree $ ^{\dagger} $ of $ n $ nodes (really, everything should stop resembling trees all the time $ \ldots $ ), numbered from $ 0 $ to $ n-1 $ , with node $ 0 $ as the root.

Gretel's objective is to learn the exact structure of the monster's nerve system — more specifically, she wants to know the values $ p_1, p_2, \ldots, p_{n-1} $ of the tree, where $ p_i $ ( $ 0 \le p_i < i $ ) is the direct parent node of node $ i $ ( $ 1 \le i \le n - 1 $ ).

She doesn't know exactly how the nodes are placed, but she knows a few convenient facts:

- If we remove root node $ 0 $ and all adjacent edges, this tree will turn into a forest consisting of only paths $ ^{\ddagger} $ . Each node that was initially adjacent to the node $ 0 $ will be the end of some path.
- The nodes are indexed in a way that if $ 1 \le x \le y \le n - 1 $ , then $ p_x \le p_y $ .
- Node $ 1 $ has exactly two adjacent nodes (including the node $ 0 $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/e8258012a39acd46c9074838efef9914b6897d4b.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/206bea28ad893e4b88d7080ccd68226695dddca4.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/62f37c6d61a34178ff5087ddf19cef6e4de6bb74.png)The tree in this picture does not satisfy the condition, because if we remove node $ 0 $ , then node $ 2 $ (which was initially adjacent to the node $ 0 $ ) will not be the end of the path $ 4-2-5 $ .The tree in this picture does not satisfy the condition, because $ p_3 \le p_4 $ must hold.The tree in this picture does not satisfy the condition, because node $ 1 $ has only one adjacent node.Gretel can make queries to the containment cell:

- "? a b" ( $ 1 \le a, b < n $ , $ a \ne b $ ) — the cell will check if the simple path between nodes $ a $ and $ b $ contains the node $ 0 $ .

However, to avoid unexpected consequences by overstimulating the creature, Gretel wants to query at most $ 2n - 6 $ times. Though Gretel is gifted, she can't do everything all at once, so can you give her a helping hand?

 $ ^{\dagger} $ A tree is a connected graph where every pair of distinct nodes has exactly one simple path connecting them.

 $ ^{\ddagger} $ A path is a tree whose vertices can be listed in the order $ v_1, v_2, \ldots, v_k $ such that the edges are $ (v_i, v_{i+1}) $ ( $ 1 \le i < k $ ).

## 说明/提示

In the first test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/f881123b596891d36ab778596441f15ad95a02ea.png)- The answer to "? 2 3" is $ 1 $ . This means that the simple path between nodes $ 2 $ and $ 3 $ contains node $ 0 $ .

In the second test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/33f1d468944f56ba6a97f7e156678062fb607fea.png)- The answer to "? 2 3" is $ 1 $ . This means that the simple path between nodes $ 2 $ and $ 3 $ contains node $ 0 $ .
- The answer to "? 2 4" is $ 0 $ . This means that the simple path between nodes $ 2 $ and $ 4 $ doesn't contain node $ 0 $ .

In the third test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/80e7fbd696eda68303e33490520aebb364943d67.png)

## 样例 #1

### 输入

```
3
4

1

5

1

0

9```

### 输出

```
? 2 3

! 0 0 1

? 2 3

? 2 4

! 0 0 1 2

! 0 0 0 1 3 5 6 7```

# AI分析结果



**唯一算法分类**  
双指针法 / 贪心算法  

---

**综合分析与结论**  

**核心思路**：利用父节点数组的单调性，通过双指针法或倒序处理确定每个节点的父节点。删除根节点后树变为多条链，节点编号与父节点编号满足非递减关系，故可通过有限次询问确定各节点的归属链。  

**难点与解决方案**：  
1. **父节点单调性**：确保父节点选择时满足p_i ≤ p_j（i ≤ j）。通过维护指针（如倒序处理中的l或正序中的now）逐步缩小候选父节点范围。  
2. **询问次数限制**：通过单次线性遍历或双指针移动，确保总次数≤2n-6。例如，倒序处理每个节点最多询问n-2次，总和符合要求。  
3. **链结构维护**：确定节点是否在同一条链（询问路径是否经过0），从而调整指针位置。  

**可视化设计**：  
- **动画方案**：以网格展示树节点，根节点0位于顶部。倒序处理时，从最大编号节点开始，指针l从n-2左移。每次询问高亮当前节点i和指针l，若返回1（路径经0），则l左移；否则确定父节点为l。  
- **颜色标记**：当前节点（红色）、候选父节点（蓝色）、已确定节点（绿色）。  
- **复古像素风格**：Canvas绘制链结构，每次确定父节点时播放8-bit音效，背景音乐循环。  

---

**题解清单 (≥4星)**  

1. **elpsconr（5星）**  
   - **关键亮点**：倒序处理，维护指针l递减，确保父节点单调性。代码简洁高效，询问次数严格≤n-2。  
   - **个人心得**：初始正向构建受阻，倒序后豁然开朗，强调逆向思维的重要性。  

2. **tai_chi（4星）**  
   - **关键亮点**：分两步处理，先确定节点1的子树，再双指针维护剩余节点。逻辑清晰，代码易读。  
   - **优化**：利用节点1的特殊性减少无效查询。  

3. **arrow_king（4星）**  
   - **关键亮点**：队列维护候选父节点，动态调整链结构。结合单调性优化询问次数。  

---

**核心代码实现**  

**elpsconr的倒序处理**：  
```cpp
int l = n-2;
for (int i = n-1; i >= 1; --i) {
    while (l > 0 && ask(i, l)) l--;
    a[i] = max(l--, 0);
}
```  
**关键逻辑**：对每个节点i，从高位向低位查询，找到最大的合法父节点l，并递减l避免重复。  

**tai_chi的双指针法**：  
```cpp
int now = 2;
for (int i = t+1; i <= n-1; ++i) {
    while (ask(now, i)) now++;
    p[i] = now;
    now++;
}
```  
**关键逻辑**：维护now指针，若当前节点i与now不在同一链，右移now直至找到父节点。  

---

**同类型题推荐**  
1. **洛谷P1232**：树的父节点推断（交互题，利用树性质）  
2. **洛谷P2664**：树上游戏（链结构处理）  
3. **洛谷P3978**：概率充电器（树结构性质应用）  

---

**个人心得摘录**  
- **elpsconr**：赛时正向思维受阻，睡后逆向突破，强调思维灵活性。  
- **tai_chi**：强调节点1的特殊性，优先处理其子树以简化问题。  

---

**可视化与复古动画设计**  
- **Canvas动画**：节点以像素方块显示，倒序处理时i从右向左移动，l指针同步左移。每次询问播放“哔”声，确定父节点时播放“叮”声。  
- **自动演示**：AI按倒序自动运行，用户可暂停/调节速度。过关时显示“STAGE CLEAR”并加分。  
- **8位音效**：使用Web Audio API合成芯片音乐，背景循环轻快旋律。

---
处理用时：68.16秒