# 题目信息

# Mike and Fish

## 题目描述

As everyone knows, bears love fish. But Mike is a strange bear; He hates fish! The even more strange thing about him is he has an infinite number of blue and red fish.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF547D/031dc6fdab66492c31079b30a48004c3918930a2.png)He has marked $ n $ distinct points in the plane. $ i $ -th point is point $ (x_{i},y_{i}) $ . He wants to put exactly one fish in each of these points such that the difference between the number of red fish and the blue fish on each horizontal or vertical line is at most 1.

He can't find a way to perform that! Please help him.

## 样例 #1

### 输入

```
4
1 1
1 2
2 1
2 2
```

### 输出

```
brrb
```

## 样例 #2

### 输入

```
3
1 1
1 2
2 1
```

### 输出

```
brr
```

# AI分析结果



# Mike and Fish 题解分析

## 算法分类
图论 - 欧拉回路与二分图染色

---

## 题解思路与核心难点

### 核心思路对比
1. **二分图染色法**（shadowice1984 / StudyingFather）  
   - **配对策略**：对同一横/纵坐标的点两两配对形成边，剩余点单独处理  
   - **染色证明**：证明构造的图是二分图（无奇环），通过黑白染色实现颜色平衡  
   - **复杂度**：O(n)  

2. **欧拉回路法**（tzc_wk / Kinandra）  
   - **图转化**：将每个点 (x,y) 视为连接 x 行与 y 列的边  
   - **度数处理**：添加虚点使所有点度数为偶，通过欧拉回路定向边  
   - **正确性**：回路中每个点入度=出度，奇点差由虚边平衡  
   - **复杂度**：O(n)  

### 解决难点
- **二分图正确性**：需证明横向与纵向边的交替不会形成奇环  
- **欧拉回路构造**：处理奇点时需保证虚边不影响原图结构  
- **颜色平衡保证**：两种方法均保证每行/列颜色差 ≤1  

---

## 题解评分（≥4星）

### 五星题解
1. **StudyingFather（五星）**  
   - **亮点**：严密的二分图证明，代码简洁易读  
   - **代码**：用 `lstu/lstv` 数组处理配对，DFS染色  

2. **tzc_wk（五星）**  
   - **亮点**：清晰的欧拉回路转化思路，虚点处理巧妙  
   - **代码**：通过 `bel[i]` 记录边方向，自动生成颜色  

3. **Kinandra（四星半）**  
   - **亮点**：将问题转化为欧拉回路定向，理论证明完整  
   - **优化**：使用压缩读入加速  

---

## 最优技巧提炼

### 关键技巧
1. **行列转点**  
   - 将坐标轴的行列抽象为顶点，点视为边，构建二分图或混合图  
   ```cpp
   // tzc_wk 代码片段
   add(x, y+DELTA);  // 将行x与列y+DELTA连边
   ```

2. **奇点处理**  
   - 添加虚点连接所有奇度点，使全图度数变为偶数  
   ```cpp
   if(deg[i]&1) add(0,i), add(i,0);  // 虚点0连接奇点
   ```

3. **染色/定向策略**  
   - 二分图染色：通过DFS交替染色保证相邻点颜色不同  
   - 欧拉回路：按回路顺序定向边，保证入度出度平衡  

---

## 同类型题推荐
1. **CF429E（Points and Segments）**  
   - 类似欧拉回路定向，平衡线段覆盖次数  
2. **LG-P3512（导航问题）**  
   - 行列转化建图，二分图染色应用  
3. **ARC092C（2D Plane 2N Points）**  
   - 坐标点配对问题，贪心或图论解法  

---

## 可视化设计

### 核心动画逻辑
1. **图转化阶段**  
   - **像素风格**：行坐标显示为蓝色方块，列坐标显示为绿色方块  
   - **边绘制**：每个点 (x,y) 显示为连接蓝绿方块的黄色线条  

2. **欧拉回路阶段**  
   - **路径追踪**：红色光标沿欧拉路径移动，当前边变为紫色  
   - **定向效果**：边箭头方向实时变化，对应颜色输出（红→右箭头，蓝←左箭头）  

3. **奇点处理**  
   - **虚点特效**：虚点显示为闪烁的白色方块，奇点连边时播放"哔"音效  

### 交互设计
- **步进控制**：空格键单步执行回路构建，方向键调整速度  
- **音效**：  
  - 正确定向时：8-bit 上升音效 (0x0F, 0x1A)  
  - 发现奇点：短促警报音 (0x02, 0x08)  

---

## 核心代码实现

### 欧拉回路法（tzc_wk）
```cpp
void dfs(int x){
    for(int &e=hd[x];e;e=nxt[e])
        if(!vis[e>>1]) 
            vis[e>>1]=1+(x<=DELTA), dfs(to[e]);
}

int main(){
    // 建图
    for(int i=1,x,y;i<=n;i++){
        scanf("%d%d",&x,&y);
        adde(x,y+DELTA); adde(y+DELTA,x);
    }
    // 处理奇点
    for(int i=1;i<=DELTA*2;i++)
        if(deg[i]&1) adde(0,i), adde(i,0);
    // 跑欧拉回路
    for(int i=1;i<=DELTA;i++) dfs(i);
    // 输出颜色
    for(int i=1;i<=n;i++) putchar((vis[i]==1)?'r':'b');
}
```

---

## 个人心得摘录
"第一次尝试直接配对染色时总出现奇环，后来发现必须严格交替横向和纵向的边才能保证二分图性质" —— StudyingFather 调试笔记  

"虚点就像魔法一样，把所有不规则的度数问题都规范化了" —— tzc_wk 实现感想  

---

通过将几何问题转化为图论模型，并巧妙运用欧拉回路或二分图性质，两种方法均以 O(n) 时间复杂度优雅解决此题，展现了图论在坐标问题中的强大应用能力。

---
处理用时：68.60秒