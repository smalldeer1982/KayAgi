# 题目信息

# Dividing Kingdom

## 题目描述

A country called Flatland is an infinite two-dimensional plane. Flatland has $ n $ cities, each of them is a point on the plane.

Flatland is ruled by king Circle IV. Circle IV has 9 sons. He wants to give each of his sons part of Flatland to rule. For that, he wants to draw four distinct straight lines, such that two of them are parallel to the $ Ox $ axis, and two others are parallel to the $ Oy $ axis. At that, no straight line can go through any city. Thus, Flatland will be divided into 9 parts, and each son will be given exactly one of these parts. Circle IV thought a little, evaluated his sons' obedience and decided that the $ i $ -th son should get the part of Flatland that has exactly $ a_{i} $ cities.

Help Circle find such four straight lines that if we divide Flatland into 9 parts by these lines, the resulting parts can be given to the sons so that son number $ i $ got the part of Flatland which contains $ a_{i} $ cities.

## 说明/提示

The solution for the first sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF260E/f25dd1f6e7f7e19d7007bdb9da678c4a92207eda.png)The solution for the second sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF260E/cfb5bf22cb67c702c1b27adab1d86b1bf50d84b5.png)There is no solution for the third sample test.

## 样例 #1

### 输入

```
9
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3
1 1 1 1 1 1 1 1 1
```

### 输出

```
1.5000000000 2.5000000000
1.5000000000 2.5000000000
```

## 样例 #2

### 输入

```
15
4 4
-1 -3
1 5
3 -4
-4 4
-1 1
3 -3
-4 -5
-3 3
3 2
4 1
-4 2
-2 -5
-3 4
-1 4
2 1 2 1 2 1 3 2 1
```

### 输出

```
-3.5000000000 2.0000000000
3.5000000000 -1.0000000000
```

## 样例 #3

### 输入

```
10
-2 10
6 0
-16 -6
-4 13
-4 -2
-17 -10
9 15
18 16
-5 2
10 -5
2 1 1 1 1 1 1 1 1
```

### 输出

```
-1
```

# AI分析结果

# 💡 Kay的C++算法解析：Dividing Kingdom 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：枚举排列 + 二维数点（可持久化线段树/树状数组）


🗣️ **初步分析**：  
我们的任务是用两条竖线、两条横线把平面分成9块，让每块的城市数正好是给定数组`a`的一个排列。听起来有点像“给9个盒子分糖果”——只不过这里的“盒子”是平面区域，“糖果”是城市点。  

### 核心算法的作用
1. **枚举排列**：因为`a`的长度只有9，`9! = 362880`次循环对电脑来说是小case！我们可以逐个试每个排列对应的区域分配方式。  
2. **二维数点**：要快速算“某个矩形区域内有多少点”，就像你想知道“教室前两排左三列有多少同学”——用**可持久化线段树（主席树）**或**树状数组**能在`O(log²n)`时间内给出答案，比逐个点 counting 快得多！


### 算法流程与可视化思路
1. **离散化坐标**：把城市的x、y坐标“压缩”到小范围（比如把100000变成100），避免数组下标过大。  
2. **枚举排列**：用DFS或`next_permutation`试所有`a`的排列，每个排列对应9块的点数要求。  
3. **确定分割线**：比如竖线`Sx1`左边的点数是第1+4+7块的和（假设块的位置是左下到右上的3x3 grid），找到`Sx1`的位置（必须在两个城市的x坐标之间，不能压到点）。  
4. **验证点数**：用二维数点结构检查每个块的点数是否符合排列要求。  


### 可视化设计小预告
我会设计一个**8位像素风的“城市分割游戏”**：  
- 用彩色小方块代表城市，红色竖线、蓝色横线代表分割线；  
- 枚举排列时，屏幕上方的数字会“滚动”切换；  
- 确定分割线时，线会从两侧“滑入”，并高亮对应的x/y坐标；  
- 验证点数时，每个块会闪烁，同时显示当前点数和目标点数——对了就“叮”一声，错了就“咔”一声～  


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性三个维度筛选了3份优质题解，帮你快速抓住核心！
</eval_intro>


### **题解一（作者：1234567s，赞6）**
* **点评**：这份题解的思路像“剥洋葱”——一层一层理清楚问题。作者先用离散化处理坐标，再用主席树构建二维数点结构，最后用DFS枚举排列。代码中的`check`函数严谨验证了每个块的点数，甚至考虑了“分割线不能压到点”的细节（比如检查相邻点的x/y坐标是否不同）。变量命名也很直观，比如`rt`数组存主席树的根节点，`SZ`函数直接返回区域点数，新手也能看懂！


### **题解二（作者：流水行船CCD，赞5）**
* **点评**：作者把算法拆成“枚举排列→确定分割线→验证点数”三步，每一步都讲得很透！比如在“确定分割线”时，直接用排序后的坐标数组找到对应的位置（不用二分！），节省了时间。代码中的`Order`函数用DFS枚举排列，`solve`函数集中处理验证逻辑，结构非常清晰。特别是作者提到“分割线要加0.5偏移量”——这是避免压到点的关键技巧！


### **题解三（作者：Hyc_，赞3）**
* **点评**：这份题解用了**树状数组**代替主席树处理二维数点，展示了“同一问题可以用不同数据结构解决”。作者用`add`函数向树状数组中插入y坐标，`query`函数查询区域点数，代码比主席树更简洁。另外，作者用`next_permutation`枚举排列，写法更高效——这也是值得学习的小技巧！


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的“拦路虎”主要有3个，我们一一拆解！
</difficulty_intro>


### 1. 难点1：如何确定分割线的位置？
**问题**：分割线不能压到任何点，还要满足“左边/下边的点数等于排列中的和”。  
**解决策略**：  
- 先对x、y坐标**排序去重**（比如把所有x坐标排好序，去掉重复的）；  
- 根据排列的和，找到对应的坐标位置（比如`Sx1`是第`a1+a4+a7`个点的x坐标）；  
- 检查**相邻点的坐标是否不同**（比如`Sx1`的下一个点的x坐标必须比它大，否则分割线会压到点）。  

💡 **学习笔记**：排序+去重是处理“大坐标”的神器！


### 2. 难点2：如何快速验证区域点数？
**问题**：直接遍历所有点算区域点数会超时（n到1e5）。  
**解决策略**：  
- 用**可持久化线段树（主席树）**：每个版本对应x坐标的前缀，存储y坐标的分布。查询`x∈[l,r]`且`y∈[L,R]`的点数，只需要用第r版本减去第l-1版本的线段树。  
- 或用**树状数组**：按x坐标排序，依次插入y坐标，查询时用前缀和相减。  

💡 **学习笔记**：二维数点的核心是“将二维问题转化为一维前缀和”！


### 3. 难点3：如何处理排列的枚举？
**问题**：9!有36万次循环，会不会写起来很麻烦？  
**解决策略**：  
- 用`next_permutation`函数：直接生成`a`数组的所有排列，代码一行搞定！  
- 用DFS：手动递归枚举每个位置的数，适合理解排列的生成过程。  

💡 **学习笔记**：不要怕“暴力枚举”——只要次数在电脑能处理的范围内，就是好方法！


### ✨ 解题技巧总结
- **离散化**：处理大坐标的必选步骤，用`sort+unique+lower_bound`实现。  
- **二维数点结构选择**：主席树适合在线查询，树状数组适合离线查询，根据题目需求选。  
- **细节处理**：分割线要加0.5偏移量（比如`x=1.5`），避免压到点；验证时要检查所有9块的点数，不能漏！


## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合优质题解的思路，提炼了一份**通用核心代码**，涵盖离散化、主席树构建、枚举排列、验证逻辑！
</code_intro_overall>


### 本题通用核心C++实现参考
* **说明**：本代码综合了题解一、二、三的思路，用主席树处理二维数点，DFS枚举排列，逻辑清晰易读。
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5;
const int M = 1e5 * 20; // 主席树节点数

struct Node { int x, y; };
Node city[N]; // 城市坐标
int a[10], b[10]; // a是输入的数组，b是当前排列
bool vis[10]; // 枚举排列用的标记数组

// 离散化相关
int rx[N], ry[N]; // 原始x、y坐标
int dx[N], dy[N]; // 离散化后的x、y坐标
int cntx, cnty; // 离散化后的坐标数量

// 主席树相关
struct SegmentTree {
    int lson[M], rson[M], sum[M];
    int root[N], idx;

    void init() { idx = 0; }

    void update(int &now, int pre, int l, int r, int pos) {
        now = ++idx;
        lson[now] = lson[pre];
        rson[now] = rson[pre];
        sum[now] = sum[pre] + 1;
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (pos <= mid) update(lson[now], lson[pre], l, mid, pos);
        else update(rson[now], rson[pre], mid+1, r, pos);
    }

    int query(int now, int pre, int l, int r, int L, int R) {
        if (R < l || L > r) return 0;
        if (L <= l && r <= R) return sum[now] - sum[pre];
        int mid = (l + r) >> 1;
        return query(lson[now], lson[pre], l, mid, L, R) +
               query(rson[now], rson[pre], mid+1, r, L, R);
    }
} tree;

// 计算区域点数：x∈[x1,x2]，y∈[y1,y2]
int count(int x1, int x2, int y1, int y2) {
    return tree.query(tree.root[x2], tree.root[x1-1], 1, cnty, y1, y2);
}

// 验证当前排列是否可行
void check() {
    // 计算竖线位置：Sx1左边是b[1]+b[4]+b[7]，Sx2左边是Sx1 + b[2]+b[5]+b[8]
    int sumx1 = b[1] + b[4] + b[7];
    int sumx2 = sumx1 + b[2] + b[5] + b[8];
    int sx1 = dx[sumx1], sx2 = dx[sumx2];
    // 检查分割线是否压到点（相邻点x坐标不同）
    if (rx[sx1] == rx[sx1+1] || rx[sx2] == rx[sx2+1]) return;

    // 计算横线位置：Sy1下边是b[1]+b[2]+b[3]，Sy2下边是Sy1 + b[4]+b[5]+b[6]
    int sumy1 = b[1] + b[2] + b[3];
    int sumy2 = sumy1 + b[4] + b[5] + b[6];
    int sy1 = dy[sumy1], sy2 = dy[sumy2];
    if (ry[sy1] == ry[sy1+1] || ry[sy2] == ry[sy2+1]) return;

    // 验证所有9块的点数
    if (count(1, sx1, 1, sy1) != b[1]) return;
    if (count(sx1+1, sx2, 1, sy1) != b[2]) return;
    if (count(sx2+1, cntx, 1, sy1) != b[3]) return;
    if (count(1, sx1, sy1+1, sy2) != b[4]) return;
    if (count(sx1+1, sx2, sy1+1, sy2) != b[5]) return;
    if (count(sx2+1, cntx, sy1+1, sy2) != b[6]) return;
    if (count(1, sx1, sy2+1, cnty) != b[7]) return;
    if (count(sx1+1, sx2, sy2+1, cnty) != b[8]) return;
    if (count(sx2+1, cntx, sy2+1, cnty) != b[9]) return;

    // 输出结果（分割线是坐标中间值）
    printf("%.9lf %.9lf\n", (rx[sx1] + rx[sx1+1])/2.0, (rx[sx2] + rx[sx2+1])/2.0);
    printf("%.9lf %.9lf\n", (ry[sy1] + ry[sy1+1])/2.0, (ry[sy2] + ry[sy2+1])/2.0);
    exit(0); // 找到解，直接退出
}

// DFS枚举排列
void dfs(int step) {
    if (step == 10) { check(); return; }
    for (int i = 1; i <= 9; i++) {
        if (!vis[i]) {
            vis[i] = true;
            b[step] = a[i];
            dfs(step + 1);
            vis[i] = false;
        }
    }
}

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> city[i].x >> city[i].y;
        rx[i] = city[i].x;
        ry[i] = city[i].y;
    }

    // 离散化x坐标
    sort(rx + 1, rx + n + 1);
    cntx = unique(rx + 1, rx + n + 1) - rx - 1;
    for (int i = 1; i <= n; i++) {
        city[i].x = lower_bound(rx + 1, rx + cntx + 1, city[i].x) - rx;
        dx[i] = city[i].x; // dx数组存排序后的x坐标（用于找分割线）
    }
    sort(dx + 1, dx + n + 1); // dx排序，方便找分割线位置

    // 离散化y坐标
    sort(ry + 1, ry + n + 1);
    cnty = unique(ry + 1, ry + n + 1) - ry - 1;
    for (int i = 1; i <= n; i++) {
        city[i].y = lower_bound(ry + 1, ry + cnty + 1, city[i].y) - ry;
        dy[i] = city[i].y;
    }
    sort(dy + 1, dy + n + 1);

    // 构建主席树（按x坐标排序）
    sort(city + 1, city + n + 1, [](Node a, Node b) { return a.x < b.x; });
    tree.init();
    for (int i = 1; i <= n; i++) {
        tree.update(tree.root[i], tree.root[i-1], 1, cnty, city[i].y);
    }

    // 输入a数组
    for (int i = 1; i <= 9; i++) cin >> a[i];

    // 枚举排列
    dfs(1);

    // 无解
    cout << "-1" << endl;
    return 0;
}
```
* **代码解读概要**：  
  1. **离散化**：把x、y坐标压缩到1~cntx、1~cnty的范围；  
  2. **主席树构建**：按x坐标排序城市，每个主席树版本对应前i个城市的y坐标分布；  
  3. **枚举排列**：用DFS生成所有a的排列；  
  4. **验证**：计算分割线位置，用主席树查询每个块的点数，符合条件就输出结果。


### 针对各优质题解的片段赏析

#### **题解一（作者：1234567s）**
* **亮点**：用`SZ`函数封装主席树查询，代码更简洁。
* **核心代码片段**：
```cpp
int SZ(int x1, int x2, int y1, int y2) {
    return T1.query(rt[x2], rt[x1-1], 1, o, y1, y2);
}
```
* **代码解读**：  
  这个函数直接返回`x∈[x1,x2]`且`y∈[y1,y2]`的点数，把主席树的查询逻辑封装起来，让`check`函数更易读。比如`SZ(1, sx1, 1, sy1)`就是查询左下块的点数——是不是很直观？
* 💡 **学习笔记**：封装重复逻辑是写好代码的关键！


#### **题解二（作者：流水行船CCD）**
* **亮点**：用`next_permutation`枚举排列，代码更高效。
* **核心代码片段**：
```cpp
do {
    solve(); // 验证当前排列
} while (next_permutation(pl + 1, pl + 10));
```
* **代码解读**：  
  `next_permutation`会自动生成`pl`数组的所有排列，比DFS更简洁。比如`pl`数组初始是`[1,2,...,9]`，每次循环都会变成下一个排列——省去了写DFS的麻烦！
* 💡 **学习笔记**：善用STL函数能节省很多时间！


#### **题解三（作者：Hyc_）**
* **亮点**：用树状数组处理二维数点，代码更短小。
* **核心代码片段**：
```cpp
inline int query(int i, int x) {
    int sum = 0;
    for (; i; i ^= i & -i)
        sum += upper_bound(t[i].begin(), t[i].end(), x) - t[i].begin();
    return sum;
}
```
* **代码解读**：  
  这个函数用树状数组查询`x≤i`且`y≤x`的点数。树状数组的每个节点存一个排序后的y坐标数组，用`upper_bound`找小于等于x的y的数量——比主席树更省代码！
* 💡 **学习笔记**：不同数据结构各有优缺点，根据题目选最合适的！


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
我设计了一个**8位像素风的“城市分割小游戏”**，让你直观看到算法的每一步！
</visualization_intro>


### **动画演示主题**：像素城市的“分割大挑战”
**风格**：FC红白机风格，用16色调色板（比如蓝色天空、绿色草地、黄色城市块），背景是简单的网格。


### **核心演示内容**
1. **初始化场景**：  
   - 屏幕左侧显示“城市列表”（用小黄色方块代表，每个方块标有坐标）；  
   - 屏幕右侧是“控制面板”：有“开始”“单步”“重置”按钮，还有“速度滑块”（控制自动播放的速度）；  
   - 背景播放8位风格的BGM（比如《超级马里奥》的轻快旋律）。

2. **离散化过程**：  
   - 所有城市的x坐标“排成一队”，重复的坐标会“合并”成一个（比如x=1、1、2会变成1、2）；  
   - y坐标同理，用动画展示“排序→去重”的过程，旁边有文字提示：“离散化让坐标变小啦！”

3. **枚举排列**：  
   - 屏幕上方的“排列显示区”会滚动数字（比如从`[1,1,...,1]`变成`[1,1,...,2]`），每换一个排列，会有“咔嗒”的音效；  
   - 当前选中的排列会用红色高亮，提示：“正在试这个排列哦～”

4. **确定分割线**：  
   - 竖线从屏幕左右两侧“滑入”，停在对应的x坐标位置（比如`x=1.5`），用红色表示；  
   - 横线从屏幕上下两侧“滑入”，停在对应的y坐标位置（比如`y=2.5`），用蓝色表示；  
   - 分割线会闪烁3次，提示：“分割线在这里！”

5. **验证点数**：  
   - 每个块会依次闪烁（从左下到右上），同时显示“当前点数：3 / 目标点数：3”；  
   - 如果点数对，会播放“叮”的音效，块变成绿色；如果不对，播放“咔”的音效，块变成红色；  
   - 所有块都对的话，屏幕会弹出“胜利！”的字样，播放胜利音效（比如《魂斗罗》的通关音乐）。


### **交互设计**
- **单步执行**：点击“单步”按钮，算法走一步（比如枚举下一个排列、确定分割线、验证一个块）；  
- **自动播放**：点击“开始”，算法自动执行，速度可以用滑块调整（从“慢”到“快”）；  
- **重置**：点击“重置”，回到初始状态，重新开始。


### **为什么这样设计？**
- **像素风格**：复古游戏的感觉能让你更有兴趣，也更易聚焦核心逻辑；  
- **音效提示**：用声音强化关键操作（比如枚举排列、验证点数），帮你记住步骤；  
- **交互控制**：单步执行让你能仔细看每一步，自动播放让你快速看整体流程。


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
学会了“枚举排列+二维数点”，你可以解决很多类似的问题！
</similar_problems_intro>


### **通用思路迁移**
- **场景1**：给二维平面分块，要求每块的元素满足某种数量条件（比如本题的城市数）；  
- **场景2**：统计二维区间内的元素个数（比如“查询矩形内有多少个点”）；  
- **场景3**：枚举小范围的排列/组合，解决“分配问题”（比如“给9个盒子分糖果”）。


### **洛谷练习推荐**
1. **洛谷 P3810 【模板】三维偏序（陌上花开）**  
   🗣️ **推荐理由**：这道题考察“三维偏序”，需要用**分治+树状数组**处理，和本题的二维数点思路类似，能帮你巩固“高维计数”的技巧！

2. **洛谷 P4168 [Violet]蒲公英**  
   🗣️ **推荐理由**：这道题用**可持久化线段树**处理区间众数问题，和本题的主席树用法一致，能帮你熟练掌握主席树的构建和查询！

3. **洛谷 P1972 [SDOI2009] HH的项链**  
   🗣️ **推荐理由**：这道题用**离线处理+树状数组**解决区间不同元素的个数问题，和本题的“计数”思路一致，能帮你理解“离线处理”的优势！


## 7. 学习心得与经验分享 (若有)

<insights_intro>
从题解中，我发现了几个**超有用的经验**，帮你避免踩坑！
</insights_intro>


### **经验1：离散化的细节**
> 很多题解都提到“离散化时要排序+去重”，比如作者1234567s在代码中用了`sort+unique+lower_bound`。  
**点评**：离散化的关键是“把大坐标映射到小范围”，如果漏了`unique`，会导致坐标重复，分割线压到点——这是很多新手会犯的错！


### **经验2：分割线的偏移量**
> 作者流水行船CCD提到“分割线要加0.5偏移量”，比如`x=1.5`而不是`x=1`。  
**点评**：因为城市的坐标是整数，加0.5能保证分割线在两个点之间，不会压到任何点——这是本题的“隐藏条件”，一定要注意！


### **经验3：枚举排列的可行性**
> 作者Hyc_用了`next_permutation`枚举排列，而作者1234567s用了DFS。  
**点评**：两种方法都可行，但`next_permutation`更简洁，适合快速写代码；DFS更灵活，适合理解排列的生成过程——根据自己的习惯选！


## 结语
这道题的核心是“用枚举解决小范围问题，用数据结构解决大范围问题”。虽然看起来步骤多，但拆分成“离散化→枚举排列→确定分割线→验证点数”四步，就变得简单了！  

记住：编程的乐趣在于“拆解问题”——把大问题拆成小问题，一个个解决，你就能成为“算法小能手”！💪  

下次我们再一起探索新的编程挑战～

---
处理用时：192.80秒