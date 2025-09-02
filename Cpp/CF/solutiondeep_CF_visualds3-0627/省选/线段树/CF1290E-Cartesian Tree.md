# 题目信息

# Cartesian Tree

## 题目描述

Ildar is the algorithm teacher of William and Harris. Today, Ildar is teaching Cartesian Tree. However, Harris is sick, so Ildar is only teaching William.

A cartesian tree is a rooted tree, that can be constructed from a sequence of distinct integers. We build the cartesian tree as follows:

1. If the sequence is empty, return an empty tree;
2. Let the position of the maximum element be $ x $ ;
3. Remove element on the position $ x $ from the sequence and break it into the left part and the right part (which might be empty) (not actually removing it, just taking it away temporarily);
4. Build cartesian tree for each part;
5. Create a new vertex for the element, that was on the position $ x $ which will serve as the root of the new tree. Then, for the root of the left part and right part, if exists, will become the children for this vertex;
6. Return the tree we have gotten.

For example, this is the cartesian tree for the sequence $ 4, 2, 7, 3, 5, 6, 1 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/acc7800e10b8c919d4950616a18f2140e891d16a.png)After teaching what the cartesian tree is, Ildar has assigned homework. He starts with an empty sequence $ a $ .

In the $ i $ -th round, he inserts an element with value $ i $ somewhere in $ a $ . Then, he asks a question: what is the sum of the sizes of the subtrees for every node in the cartesian tree for the current sequence $ a $ ?

Node $ v $ is in the node $ u $ subtree if and only if $ v = u $ or $ v $ is in the subtree of one of the vertex $ u $ children. The size of the subtree of node $ u $ is the number of nodes $ v $ such that $ v $ is in the subtree of $ u $ .

Ildar will do $ n $ rounds in total. The homework is the sequence of answers to the $ n $ questions.

The next day, Ildar told Harris that he has to complete the homework as well. Harris obtained the final state of the sequence $ a $ from William. However, he has no idea how to find the answers to the $ n $ questions. Help Harris!

## 说明/提示

After the first round, the sequence is $ 1 $ . The tree is

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/b1534ebc83eb23d6f6505c6a2ab3b3a8035f9fce.png)The answer is $ 1 $ .

After the second round, the sequence is $ 2, 1 $ . The tree is

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/eff7476771d279f495520b7bd67cd481bc4c7064.png)The answer is $ 2+1=3 $ .

After the third round, the sequence is $ 2, 1, 3 $ . The tree is

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/c77bba87ff3ea714273a2609c35f8c7ab239c7fd.png)The answer is $ 2+1+3=6 $ .

After the fourth round, the sequence is $ 2, 4, 1, 3 $ . The tree is

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/dbef4f1eef8c88dd3dafdd5976421a830b9d116e.png)The answer is $ 1+4+1+2=8 $ .

After the fifth round, the sequence is $ 2, 4, 1, 5, 3 $ . The tree is

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/044610082349c82baf738e950f52290ea3f1ea74.png)The answer is $ 1+3+1+5+1=11 $ .

## 样例 #1

### 输入

```
5
2 4 1 5 3```

### 输出

```
1
3
6
8
11```

## 样例 #2

### 输入

```
6
1 2 4 5 6 3```

### 输出

```
1
3
6
8
12
17```

# AI分析结果



**唯一算法分类**：线段树beats（吉司机线段树）

---

### **综合分析与结论**

**核心思路**：  
笛卡尔树的子树大小等于该节点在序列中的极大区间长度（由左右第一个更大元素界定）。动态维护插入过程中每个元素的左右边界，利用线段树beats高效处理区间取min/max和加减操作。

**难点与解决方案**：  
1. **动态维护极大区间**：每次插入最大值，需对左侧元素的右边界取min，右侧元素整体右移（加1）。  
2. **高效数据结构**：吉司机线段树支持区间取min/max、加减和单点修改，保证时间复杂度为O(n log² n)。  
3. **对称性处理**：通过反转数组复用同一套代码处理左边界，避免重复实现。

**可视化设计思路**：  
- **动画方案**：  
  - **步骤分解**：显示插入新元素时，左侧区间取min（红色高亮）、右侧区间加1（绿色高亮）、单点赋值（黄色高亮）。  
  - **线段树节点状态**：用不同颜色区分最大值、次大值区域，动态更新sum和标记。  
- **复古像素风格**：  
  - **颜色方案**：8位色调（深蓝背景，亮黄线段树节点，红色/绿色操作高亮）。  
  - **音效设计**：操作成功（短促“滴”声），标记下传（轻微“咔嗒”声），错误操作（低沉“嗡”声）。  
- **交互控制**：步进按钮调节插入过程，速度滑块控制动画速度，AI自动模式展示全流程。

---

### **题解清单 (≥4星)**

1. **Kinandra (5星)**  
   - **亮点**：通过两次处理（原数组+反转）简化左右边界维护，清晰的理论推导与代码实现。  
   - **核心代码**：线段树beats维护区间和，结合树状数组确定插入位置。  

2. **摸鱼酱 (4星)**  
   - **亮点**：思维角度直观，将l_i转化为负数避免处理max，代码简洁高效。  
   - **个人心得**：提到“维护相反数”简化区间操作，减少代码冗余。  

3. **JimmyLee (4星)**  
   - **亮点**：平衡树实现替代线段树，提供不同数据结构思路，扩展性强。  
   - **调试提示**：强调“合法点个数”维护的重要性，避免无效操作。

---

### **最优思路提炼**

**关键技巧**：  
1. **对称反转**：处理左边界时反转数组，复用右边界代码。  
2. **线段树beats维护**：  
   - 节点保存最大值、次大值、数量、区间和，处理标记下传逻辑。  
   - 区间取min时仅更新最大值部分，次大值作为递归终止条件。  
3. **树状数组辅助**：快速查询插入位置的前缀计数，确定动态序列中的实际位置。  

**代码片段**（Kinandra的线段树核心逻辑）：  
```cpp
void update(int k) {
    int L = k << 1, R = k << 1 | 1;
    c[k] = c[L] + c[R], len[k] = len[L] + len[R];
    if (v[L] > v[R]) { /* 更新最大值、次大值 */ }
    else if (v[L] < v[R]) { /* ... */ }
    else { /* 相同最大值合并计数 */ }
}

void Tag(int k, int t1, int t2, int ctm) {
    if (!ctm) t1 = t2; // 仅对最大值生效
    v[k] += t1, sum[k] += 1ll * t1 * len[k];
}

void pmin(int l, int r, int k, int st, int en, int tv) {
    if (tv >= v[k]) return;
    if (tv > s[k]) { // 次大值小于tv时直接更新
        Tag(k, tv - v[k], 0, 1);
        return;
    }
    // 递归处理子节点
}
```

---

### **同类题目推荐**

1. **P4198 楼房重建**（线段树维护单调栈）  
2. **P5490 矩形面积并**（扫描线+线段树）  
3. **P6242 线段树练习3**（吉司机线段树模板题）

---

### **个人心得摘录**

> "维护相反数将左边界取max转化为取min，这是代码简化的关键。调试时发现未处理空区间导致WA，添加`!clgr(i)`判断后解决。" —— 摸鱼酱  
> "平衡树的标记下传顺序极易出错，通过单元测试每个操作的前后状态才确保正确。" —— JimmyLee

---

### **可视化与算法演示**

**动画实现方案**：  
```html
<canvas id="demo" width="800" height="400"></canvas>
<script>
// 伪代码示例：8位风格线段树动画
class SegmentTreeViz {
    constructor() {
        this.colors = ["#2C3E50", "#E74C3C", "#27AE60", "#F1C40F"];
        this.speed = 100; // ms/step
        this.ctx = document.getElementById("demo").getContext("2d");
    }
    
    drawNode(x, y, val, color) {
        this.ctx.fillStyle = color;
        this.ctx.fillRect(x, y, 40, 40); // 像素方块表示节点
        this.ctx.fillStyle = "#FFF";
        this.ctx.fillText(val, x+5, y+25);
    }
    
    async animateInsert(pos) {
        // 高亮插入位置，播放音效
        this.drawNode(pos*50, 0, "NEW", this.colors[3]);
        await sleep(this.speed);
        // 更新线段树节点，递归绘制...
    }
}
</script>
```

**交互设计**：  
- **控制面板**：播放/暂停、步进、速度调节。  
- **音效触发**：使用Web Audio API在节点更新时播放8位音效。  
- **自动演示**：模拟插入过程，展示每一步的线段树状态变化。

---
处理用时：73.11秒