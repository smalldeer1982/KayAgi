# 题目信息

# Cells Arrangement

## 题目描述

You are given an integer $ n $ . You choose $ n $ cells $ (x_1,y_1), (x_2,y_2),\dots,(x_n,y_n) $ in the grid $ n\times n $ where $ 1\le x_i\le n $ and $ 1\le y_i\le n $ .

Let $ \mathcal{H} $ be the set of distinct Manhattan distances between any pair of cells. Your task is to maximize the size of $ \mathcal{H} $ . Examples of sets and their construction are given in the notes.

If there exists more than one solution, you are allowed to output any.

Manhattan distance between cells $ (x_1,y_1) $ and $ (x_2,y_2) $ equals $ |x_1-x_2|+|y_1-y_2| $ .

## 说明/提示

In the first testcase we have $ n=2 $ . One of the possible arrangements is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/75dc943a7c64415a7537c95e5a0a8ab6f7bb8c40.png) The arrangement with cells located in $ (1,1) $ and $ (1,2) $ .  In this case $ \mathcal{H}=\{|1-1|+|1-1|,|1-1|+|2-2|,|1-1|+|1-2|\}=\{0,0,1\}=\{0,1\} $ . Hence, the size of $ \mathcal{H} $ is $ 2 $ . It can be shown that it is the greatest possible answer.In the second testcase we have $ n=3 $ . The optimal arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/c33264fb4d38aae733c98659eb0f28334deed2c9.png) The arrangement with cells located in $ (2,1) $ , $ (2,3) $ and $ (3,1) $ . $ \mathcal{H} $ = $ \{|2-2|+|1-1|,|2-2|+|3-3|,|3-3|+|1-1|,|2-2|+|1-3|,|2-3|+|1-1|,|2-3|+|3-1|\} $ = $ \{0,0,0,2,1,3\} $ = $ \{0,1,2,3\} $ .

For $ n=4 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/c8c88e231569a366e81dbe59dfe40f3bca88662e.png)For $ n=5 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/3a3f9b43e6fc8c9643d27a1bfc597d0efe1c8425.png)For $ n=6 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/b0bf5b17a4bc6da02c3ed5a2113cf7373a9e3ccc.png)

## 样例 #1

### 输入

```
5
2
3
4
5
6```

### 输出

```
1 1
1 2

2 1
2 3
3 1

1 1
1 3
4 3
4 4

1 1
1 3
1 4
2 1
5 5

1 4
1 5
1 6
5 2
5 5
6 1```

# AI分析结果



---

## 唯一算法分类：组合数学

---

### **题解思路与算法分析**

**核心问题**：在 $n \times n$ 网格中选择 $n$ 个点，使得两两曼哈顿距离的不同值数量最大。

**关键构造方法**：
1. **前两个点**：选择相邻点 $(1,1)$ 和 $(1,2)$，确保距离 $1$ 存在。
2. **剩余点**：沿主对角线依次放置 $(i,i)$（$i \ge 3$），每个新点 $(i,i)$ 与 $(1,1)$ 的距离为 $2i-2$，与 $(1,2)$ 的距离为 $2i-3$，填充连续的距离值。

**数学证明**：
- **归纳基础**：对于 $n=2$，距离集合为 $\{0,1\}$，已覆盖最大值。
- **归纳步骤**：假设 $n=k$ 时构造有效，则 $n=k+1$ 时新增点 $(k+1,k+1)$ 的距离覆盖 $2k$ 和 $2k-1$，结合已有距离形成 $0 \sim 2k$ 的连续序列。

---

### **题解评分（≥4星）**

1. **JuRuoOIer 的题解（★★★★☆）**  
   - **亮点**：详细推导构造思路，结合数学归纳法证明正确性，代码简洁高效。
   - **代码**：输出前两个点后沿对角线填充，时间复杂度 $O(n)$。

2. **liuhongyang123 的题解（★★★★☆）**  
   - **亮点**：直观解释构造意图，通过移动点打破奇偶限制，代码清晰。
   - **代码**：与前解类似，解释更简洁。

3. **junee 的题解（★★★★☆）**  
   - **亮点**：简明扼要指出构造关键，代码直接体现核心逻辑。
   - **代码**：输出前两点后填充对角线，突出贡献距离的计算。

---

### **最优思路提炼**

**构造技巧**：
- **相邻点**：生成最小非零距离（$1$），避免重复。
- **对角线填充**：每个新点贡献两个连续距离（奇偶交替），覆盖所有中间值。
- **数学归纳**：通过递推验证构造的完备性。

**代码实现**：
```cpp
void solve(int n) {
    cout << "1 1\n1 2\n";
    for (int i = 3; i <= n; ++i) cout << i << ' ' << i << '\n';
}
```

---

### **同类型题与套路**

**常见套路**：
- **极值构造**：通过对称性、相邻性等布局最大化组合属性。
- **数学归纳**：递推验证构造的正确性，确保覆盖所有情况。

**推荐题目**：
1. **洛谷 P1219**：八皇后问题（排列构造与冲突避免）。
2. **洛谷 P1325**：雷达安装（几何覆盖与极值构造）。
3. **洛谷 P1005**：矩阵取数游戏（动态规划与最优化）。

---

### **可视化与算法演示**

**动画设计**：
1. **网格绘制**：在 Canvas 中绘制 $n \times n$ 网格，初始高亮 $(1,1)$ 和 $(1,2)$。
2. **步进填充**：逐帧添加点 $(i,i)$，动态显示与已有点的距离，用不同颜色标记新覆盖的距离值。
3. **音效提示**：每新增一个距离值时播放 8-bit 音效，背景循环轻快芯片音乐。

**复古像素风格**：
- **颜色方案**：使用 16 色调色板，网格线为深灰色，点为亮绿色，距离标记为黄色。
- **交互控制**：支持暂停/继续、步进调整速度，自动播放时展示 AI 推导过程。

---

**总结**：通过巧妙的组合构造和数学归纳法，确保曼哈顿距离的连续覆盖，代码简洁高效，适合快速掌握极值构造的核心思想。

---
处理用时：115.76秒