# 题目信息

# Game with Two Trees

## 题目描述

The Smart Beaver from ABBYY has come up with a new developing game for children. The Beaver thinks that this game will help children to understand programming better.

The main object of the game is finite rooted trees, each of their edges contains some lowercase English letter. Vertices on any tree are always numbered sequentially from $ 1 $ to $ m $ , where $ m $ is the number of vertices in the tree. Before describing the actual game, let's introduce some definitions.

We'll assume that the sequence of vertices with numbers $ v_{1} $ , $ v_{2} $ , $ ... $ , $ v_{k} $ ( $ k>=1 $ ) is a forward path, if for any integer $ i $ from $ 1 $ to $ k-1 $ vertex $ v_{i} $ is a direct ancestor of vertex $ v_{i+1} $ . If we sequentially write out all letters from the the edges of the given path from $ v_{1} $ to $ v_{k} $ , we get some string ( $ k=1 $ gives us an empty string). We'll say that such string corresponds to forward path $ v_{1} $ , $ v_{2} $ , $ ... $ , $ v_{k} $ .

We'll assume that the sequence of tree vertices with numbers $ v_{1} $ , $ v_{2} $ , $ ... $ , $ v_{k} $ ( $ k>=1 $ ) is a backward path if for any integer $ i $ from $ 1 $ to $ k-1 $ vertex $ v_{i} $ is the direct descendant of vertex $ v_{i+1} $ . If we sequentially write out all the letters from the edges of the given path from $ v_{1} $ to $ v_{k} $ , we get some string ( $ k=1 $ gives us an empty string). We'll say that such string corresponds to backward path $ v_{1} $ , $ v_{2} $ , $ ... $ , $ v_{k} $ .

Now let's describe the game that the Smart Beaver from ABBYY has come up with. The game uses two rooted trees, each of which initially consists of one vertex with number $ 1 $ . The player is given some sequence of operations. Each operation is characterized by three values ( $ t $ , $ v $ , $ c $ ) where:

- $ t $ is the number of the tree on which the operation is executed ( $ 1 $ or $ 2 $ );
- $ v $ is the vertex index in this tree (it is guaranteed that the tree contains a vertex with this index);
- $ c $ is a lowercase English letter.

The actual operation is as follows: vertex $ v $ of tree $ t $ gets a new descendant with number $ m+1 $ (where $ m $ is the current number of vertices in tree $ t $ ), and there should be letter $ c $ put on the new edge from vertex $ v $ to vertex $ m+1 $ .

We'll say that an ordered group of three integers ( $ i $ , $ j $ , $ q $ ) is a good combination if:

- $ 1<=i<=m_{1} $ , where $ m_{1} $ is the number of vertices in the first tree;
- $ 1<=j,q<=m_{2} $ , where $ m_{2} $ is the number of vertices in the second tree;
- there exists a forward path $ v_{1} $ , $ v_{2} $ , $ ... $ , $ v_{k} $ such that $ v_{1}=j $ and $ v_{k}=q $ in the second tree;
- the string that corresponds to the forward path in the second tree from vertex $ j $ to vertex $ q $ equals the string that corresponds to the backward path in the first tree from vertex $ i $ to vertex $ 1 $ (note that both paths are determined uniquely).

Your task is to calculate the number of existing good combinations after each operation on the trees.

## 说明/提示

After the first operation the only good combination was $ (1,1,1) $ . After the second operation new good combinations appeared, $ (2,1,2) $ and $ (1,2,2) $ . The third operation didn't bring any good combinations. The fourth operation added good combination $ (1,3,3) $ . Finally, the fifth operation resulted in as much as three new good combinations — $ (1,4,4) $ , $ (2,3,4) $ and $ (3,1,4) $ .

## 样例 #1

### 输入

```
5
1 1 a
2 1 a
1 2 b
2 1 b
2 3 a
```

### 输出

```
1
3
3
4
7
```

# AI分析结果



## 唯一算法分类  
树上的字符串匹配与动态维护

---

## 综合分析与结论  

### 核心算法流程  
1. **字符串路径匹配**：将两棵树的路径转化为字符串匹配问题。对树2进行**树上后缀排序**，对树1进行**树链剖分**，通过二分在树2的后缀数组中快速定位匹配区间  
2. **动态维护贡献**：使用**树状数组**维护两种贡献类型：  
   - 树1节点的子树区间加（对应未来树2节点的匹配）  
   - 树2节点的单点加（对应历史树1节点的匹配）  
3. **离线处理**：预先构建两棵树的结构，通过倍增或树剖快速查询k级祖先的字符  

### 可视化设计要点  
1. **像素化树结构**：用不同颜色方块表示两棵树节点，添加新节点时触发像素生长动画  
2. **路径高亮**：匹配路径以闪烁的黄色边框显示，后缀数组区间用绿色覆盖层标识  
3. **音效触发**：  
   - 添加节点时播放8-bit"滴"声  
   - 匹配成功时播放上扬音阶  
   - 树状数组更新时触发电子脉冲音  
4. **自动演示模式**：以0.5秒/步的速度自动执行操作，右侧面板展示当前哈希值、后缀数组区间等关键数据  

---

## 题解清单 (≥4星)  

### myee & MeteorFlower (⭐⭐⭐⭐⭐)  
**亮点**：  
1. 树上后缀排序与树链剖分的完美结合  
2. 双树状数组维护两种贡献  
3. 通过离线处理规避动态树的复杂性  

### 向晚大魔王 (⭐⭐⭐⭐)  
**亮点**：  
1. 纯哈希实现降低代码复杂度  
2. 树剖+倍增实现路径匹配  
3. 单树状数组维护贡献的巧妙设计  

---

## 关键代码实现  

### 树上后缀排序核心  
```cpp
void build(){
    // 倍增法构建后缀数组
    for(uint len=1;len<n;len<<=1){
        std::pair<uint,uint> W[n];
        for(uint i=0;i<n;i++) 
            W[i] = {Rank[i], ~Fath[i]?Rank[Fath[i]]+1:0u};
        // 双关键字基数排序
        radix_sort(W, SA, n); 
        // 更新排名...
    }
}
```

### 树状数组维护贡献  
```cpp
// 维护区间加操作
BIT2::add(L[p1], R[p1], 1); 
// 查询单点值
Ans[i] = BIT2::find(Rank[p2]);
```

---

## 同类型题推荐  
1. P3975 [TJOI2015]弦论（后缀树应用）  
2. CF235C Cyclical Quest（循环串匹配）  
3. P5829 【模板】失配树（Fail树应用）

---

## 个人心得摘录  
> "树上k级祖先查询用重链剖分比长链剖分更实用，虽然理论复杂度稍高，但实测常数更小" —— MeteorFlower  
> "哈希法看似简单，但要注意模数选择。1019260817这个质数实测冲突率最低" —— 向晚大魔王  

---

## 可视化方案设计  

### 核心动画逻辑  
1. **树结构生长**：  
   - 树1用蓝色方块，树2用红色方块  
   - 新节点从父节点位置弹出，带字符标签渐显  
2. **路径匹配过程**：  
   ```javascript
   function highlightPath(node, isTree1) {
       let depth = getDepth(node);
       for(let i=0; i<depth; i++){
           let char = getKthAncestorChar(node, i);
           ctx.fillStyle = i%2 ? '#FFD700' : '#FFA500';
           drawCharAtPosition(node, i, char); // 逐帧绘制字符
       }
   }
   ```
3. **树状数组更新**：  
   - 区间更新时显示绿色光晕波纹  
   - 单点查询时目标位置闪烁红光  

### 交互控制面板  
```html
<div class="control-panel">
    <button onclick="togglePlay()">▶/⏸</button>
    <input type="range" id="speed" min="1" max="10" value="5">
    <label>Hash Mod: 
        <select id="modSel">
            <option>998244353</option>
            <option>1e9+7</option>
        </select>
    </label>
</div>
```

---

通过这种多维度解析与可视化设计，学习者可以直观理解树上字符串匹配的核心机制，同时通过交互式操作深入掌握动态维护贡献的技巧。复古像素风格与即时反馈机制显著提升算法学习体验。

---
处理用时：53.19秒