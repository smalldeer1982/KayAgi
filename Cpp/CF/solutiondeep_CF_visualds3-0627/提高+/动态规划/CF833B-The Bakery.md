# 题目信息

# The Bakery

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF833B/f46eccace96d929fa4c99a2b4ae6e89027b73fa1.png)Some time ago Slastyona the Sweetmaid decided to open her own bakery! She bought required ingredients and a wonder-oven which can bake several types of cakes, and opened the bakery.

Soon the expenses started to overcome the income, so Slastyona decided to study the sweets market. She learned it's profitable to pack cakes in boxes, and that the more distinct cake types a box contains (let's denote this number as the value of the box), the higher price it has.

She needs to change the production technology! The problem is that the oven chooses the cake types on its own and Slastyona can't affect it. However, she knows the types and order of $ n $ cakes the oven is going to bake today. Slastyona has to pack exactly $ k $ boxes with cakes today, and she has to put in each box several (at least one) cakes the oven produced one right after another (in other words, she has to put in a box a continuous segment of cakes).

Slastyona wants to maximize the total value of all boxes with cakes. Help her determine this maximum possible total value.

## 说明/提示

In the first example Slastyona has only one box. She has to put all cakes in it, so that there are two types of cakes in the box, so the value is equal to $ 2 $ .

In the second example it is profitable to put the first two cakes in the first box, and all the rest in the second. There are two distinct types in the first box, and three in the second box then, so the total value is $ 5 $ .

## 样例 #1

### 输入

```
4 1
1 2 2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7 2
1 3 3 1 4 4 4
```

### 输出

```
5
```

## 样例 #3

### 输入

```
8 3
7 7 8 7 7 8 1 7
```

### 输出

```
6
```

# AI分析结果



# 中文题目重写

## 题目描述

某时，Slastyona 决定开一家蛋糕店！她购买了所需原料和一台能烘焙多种蛋糕的魔法烤箱，正式开业了。

不久后支出超过了收入，Slastyona 决定研究甜品市场。她发现将蛋糕装入盒中销售更有利可图，且一个盒子中不同种类的蛋糕越多（记为该盒子的价值），售价越高。

她需要改进生产技术！问题在于烤箱自行决定蛋糕种类，但 Slastyona 知道今天烤箱将按顺序制作 n 个蛋糕的类型。她必须将这些蛋糕装入恰好 k 个盒子，每个盒子必须包含连续的一段蛋糕（至少一个）。

请帮助她计算所有盒子的总价值最大值。

## 输入格式

第一行两个整数 n 和 k  
第二行 n 个整数表示蛋糕序列

## 输出格式

一个整数表示最大总价值

## 样例 #1

输入：
```
4 1
1 2 2 1
```
输出：
```
2
```

## 样例 #2

输入：
```
7 2
1 3 3 1 4 4 4
```
输出：
```
5
```

---

# 算法分类
线性DP

---

# 综合分析与结论

## 核心思想
采用动态规划配合线段树优化，通过维护每个颜色最新出现位置，将区间贡献转化为线段树区间更新操作。状态转移方程：
$$ dp[i][j] = \max_{0 \le k < i} (dp[k][j-1] + cnt(k+1,i)) $$
其中 cnt(l,r) 表示区间内不同数的个数

## 关键难点与解决方案
1. **cnt计算优化**：  
   使用pre数组记录每个位置的上次出现位置，当处理到i时，线段树对区间[pre[i]+1, i]进行+1操作，通过区间加法维护当前贡献

2. **时间复杂度优化**：  
   将暴力DP的O(n²k)复杂度优化为O(nk logn)：
   - 每次划分用线段树维护当前层的dp值
   - 利用pre数组确定有效更新区间

3. **空间优化**：  
   滚动数组思想，每次只需保留上一层的dp值

## 可视化设计思路
1. **DP矩阵动画**：  
   ![动态规划矩阵示意图](https://i.postimg.cc/Znx0Kq8H/dp-grid.gif)  
   - 颜色渐变表示数值大小（蓝→黄→红）
   - 高亮当前更新的单元格和对应的线段树区间

2. **线段树操作演示**：  
   - 左侧显示蛋糕序列和pre指针
   - 右侧展示线段树结构，更新时用闪光效果标记受影响的区间

3. **复古像素风格**：
   - 8-bit音效：区间更新时播放"哔"声，找到最优解时播放通关音效
   - 像素化数字显示dp值和cnt值
   - 关卡式进度条展示当前划分次数

---

# 优质题解推荐（★★★★☆）

1. **Styx的线段树优化**  
   - 亮点：清晰展示pre数组与线段树区间更新的映射关系
   - 代码结构：分层维护线段树，逻辑简明
   ```cpp
   for(int j=1;j<=k;j++){
       build(j-1层线段树);
       for(int i=1;i<=n;i++){
           更新[pre[i],i]区间;
           dp[j][i] = 查询[1,i]最大值;
       }
   }
   ```

2. **KevinYu的莫队配合分治**  
   - 亮点：双指针维护cnt值，避免线段树
   - 核心片段：
   ```cpp
   while(指针移动时自动调整cnt值)
   ```

3. **CG__HeavenHealer的决策单调性分治**  
   - 亮点：O(nk logn)时间但常数更小
   - 关键代码：
   ```cpp
   void solve(int l,int r,int ql,int qr){
       int mid = (l+r)/2;
       // 暴力计算mid点的最优决策
       // 递归解决两侧子问题
   }
   ```

---

# 核心代码实现

```cpp
// 线段树节点定义
struct Node {
    int l, r;
    int max_val;
    int lazy;
} tree[N<<2];

void build(int k, int p, int l, int r) {
    if(l == r) {
        tree[p].max_val = dp_prev[l]; // 载入上一层dp值
        return;
    }
    // ...标准建树过程...
}

void update(int p, int l, int r, int val) {
    if(覆盖区间) {
        tree[p].max_val += val;
        tree[p].lazy += val;
        return;
    }
    // ...下传标记并递归更新...
}

int query(int p, int l, int r) {
    // ...区间查询最大值...
}

// 主DP循环
for(int j=1; j<=k; j++) {
    build当前层线段树;
    for(int i=1; i<=n; i++) {
        update线段树区间[pre[i]+1, i];
        dp[j][i] = query线段树[0, i-1];
    }
}
```

---

# 相似题目推荐
1. CF868F - 同样需要计算区间价值的分划问题
2. P1972 [SDOI2009]HH的项链 - 区间不同数个数计算
3. P6240 好吃的题目 - 带权区间分划

---

# 可视化实现要点
1. **Canvas绘制**：  
   ```javascript
   function drawDPGrid() {
       for(let j=0; j<=k; j++) {
           for(let i=0; i<=n; i++) {
               let color = hsl(240 - dp[j][i]*10, 100%, 50%);
               ctx.fillStyle = color;
               ctx.fillRect(i*30, j*30, 28, 28);
           }
       }
   }
   ```

2. **音效系统**：  
   ```javascript
   const audioCtx = new AudioContext();
   function playBeep(freq) {
       let oscillator = audioCtx.createOscillator();
       oscillator.type = 'square';
       oscillator.frequency.setValueAtTime(freq, audioCtx.currentTime);
       oscillator.connect(audioCtx.destination);
       oscillator.start();
       oscillator.stop(audioCtx.currentTime + 0.1);
   }
   ```

3. **自动演示模式**：  
   ```javascript
   let autoPlay = setInterval(() => {
       step++;
       if(step > totalSteps) clearInterval(autoPlay);
       updateVisualization();
   }, 500);
   ```

---

# 总结
本题通过巧妙的pre数组记录和线段树区间操作，将看似复杂的区间价值计算转化为高效的区间维护问题。线段树在此既作为dp值的存储结构，又作为区间贡献的计算工具，体现了数据结构与动态规划的精妙结合。理解这一核心思想后，可将其推广到各类需要维护区间特征的动态规划问题中。

---
处理用时：78.39秒