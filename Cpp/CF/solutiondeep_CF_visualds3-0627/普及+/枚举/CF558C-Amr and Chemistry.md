# 题目信息

# Amr and Chemistry

## 题目描述

Amr loves Chemistry, and specially doing experiments. He is preparing for a new interesting experiment.

Amr has $ n $ different types of chemicals. Each chemical $ i $ has an initial volume of $ a_{i} $ liters. For this experiment, Amr has to mix all the chemicals together, but all the chemicals volumes must be equal first. So his task is to make all the chemicals volumes equal.

To do this, Amr can do two different kind of operations.

- Choose some chemical $ i $ and double its current volume so the new volume will be $ 2a_{i} $
- Choose some chemical $ i $ and divide its volume by two (integer division) so the new volume will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558C/2af906789c62f9845274f856d2f941f2357aa169.png)

Suppose that each chemical is contained in a vessel of infinite volume. Now Amr wonders what is the minimum number of operations required to make all the chemicals volumes equal?

## 说明/提示

In the first sample test, the optimal solution is to divide the second chemical volume by two, and multiply the third chemical volume by two to make all the volumes equal $ 4 $ .

In the second sample test, the optimal solution is to divide the first chemical volume by two, and divide the second and the third chemical volumes by two twice to make all the volumes equal $ 1 $ .

## 样例 #1

### 输入

```
3
4 8 2
```

### 输出

```
2```

## 样例 #2

### 输入

```
3
3 5 6
```

### 输出

```
5```

# AI分析结果



**唯一算法分类**  
树形动态规划（换根法）

---

### **综合分析与结论**  
#### 核心算法流程  
题目要求通过乘2/除2操作使所有数相等。各题解核心思路是：  
1. **树模型构建**：将数值视为完全二叉树节点（父节点为 `x//2`，左子节点为 `2x`），所有初始数对应树上的叶节点。  
2. **换根DP**：计算每个节点作为汇聚点时，所有数移动到该节点的总操作次数。通过统计子树大小，推导换根公式：  
   `dp[子节点] = dp[父节点] + (n - 2 * 子树大小)`  
3. **贪心优化**：最终汇聚点必须是所有数的最近公共祖先（LCA）或其左子链节点，限制搜索空间。

**可视化设计思路**：  
- **树结构绘制**：用 Canvas 绘制完全二叉树，初始数对应的节点高亮为红色。  
- **换根动画**：从根节点逐步向左子链移动，展示总操作次数的动态变化（如蓝色数值实时更新）。  
- **关键高亮**：当前汇聚点用黄色边框标记，移动路径用绿色线条强调。  

**复古像素风格实现**：  
- **颜色方案**：8-bit 调色板（红/黄/蓝/绿），节点用 16x16 像素方块表示。  
- **音效触发**：  
  - 换根时播放 "beep" 短音  
  - 找到最小值时播放胜利音效  
- **自动演示**：模拟 AI 从根节点自动向左子链遍历，展示最优解搜索过程。

---

### **题解清单（≥4星）**  
1. **Mr_Wu（5星）**  
   - **亮点**：完全二叉树模型 + 换根DP公式推导，代码简洁高效（O(n + max a_i)）。  
   - **关键代码**：  
     ```cpp  
     while ((root << 1) <= M) {  
         tans += -siz[root << 1] + (N - siz[root << 1]);  
         root = root << 1;  
         ans = min(ans, tans);  
     }  
     ```  

2. **Marsrayd（4星）**  
   - **亮点**：清晰图解换根DP的子树贡献差异，配套调试注释。  
   - **个人心得**：  
     > "换根时发现子节点贡献变化公式，避免重复计算是关键。"  

3. **KokiNiwa（4星）**  
   - **亮点**：Trie树结构实现换根，强调二进制位操作与树距离的关系。  
   - **优化**：通过 `getrt` 函数快速定位初始根节点。  

---

### **最优思路与代码实现**  
#### **核心代码片段（Mr_Wu）**  
```cpp  
// 换根DP核心逻辑  
for (root = M; root >= 1; --root)  
    if (siz[root] == N) break; // 初始根为所有数的LCA  
for (i = 1; i <= N; ++i) tans += dep[a[i]] - dep[root];  
while ((root << 1) <= M) {  
    tans += -siz[root << 1] + (N - siz[root << 1]); // 换根公式  
    root = root << 1;  
    ans = min(ans, tans);  
}  
```  

#### **完全体代码（Mr_Wu）**  
```cpp  
#include <cstdio>  
#include <climits>  
typedef long long ll;  
ll min(ll a, ll b) { return a < b ? a : b; }  
const int MAXN = 200005;  
int N, M = 100000, siz[MAXN], dep[MAXN], a[MAXN], root;  
ll ans = LLONG_MAX >> 1, tans;  
int vis[MAXN];  
void dfs(int u) {  
    if (u > M) return;  
    dep[u << 1] = dep[u << 1 | 1] = dep[u] + 1;  
    dfs(u << 1), dfs(u << 1 | 1);  
    siz[u] = siz[u << 1] + siz[u << 1 | 1] + vis[u];  
}  
int main() {  
    scanf("%d", &N);  
    for (int i = 1; i <= N; ++i)  
        scanf("%d", &a[i]), ++vis[a[i]], M = max(M, a[i]);  
    dfs(1);  
    for (root = M; root >= 1; --root)  
        if (siz[root] == N) break;  
    for (int i = 1; i <= N; ++i)  
        tans += dep[a[i]] - dep[root];  
    while ((root << 1) <= M) {  
        tans += -siz[root << 1] + (N - siz[root << 1]);  
        root = root << 1;  
        ans = min(ans, tans);  
    }  
    printf("%lld\n", ans);  
    return 0;  
}  
```  

---

### **同类型题与推荐题目**  
1. **CF519E（树形换根DP）**  
2. **洛谷P1099（树网的核，换根思想）**  
3. **LeetCode 1522（树直径与换根）**  

---

### **复古像素动画实现（JS片段）**  
```javascript  
// Canvas初始化与节点绘制  
const ctx = canvas.getContext('2d');  
function drawNode(x, y, color) {  
    ctx.fillStyle = color;  
    ctx.fillRect(x * 32, y * 32, 24, 24);  
}  

// 自动换根演示  
let currentRoot = initialRoot;  
function autoPlay() {  
    if (currentRoot > maxVal) return;  
    drawTree(currentRoot); // 绘制当前树结构  
    const nextRoot = currentRoot << 1;  
    updateAns(nextRoot); // 计算新总操作次数  
    currentRoot = nextRoot;  
    setTimeout(autoPlay, 1000); // 步进延迟  
}  
```  

---

### **个人心得摘录**  
> "换根DP的公式推导必须结合子树贡献变化，否则容易陷入暴力枚举的泥潭。"  
> —— Marsrayd  

> "完全二叉树模型的左子链性质是限制搜索空间的关键，代码简洁性由此而来。"  
> —— Mr_Wu  

---

**可视化与算法演示**  
- **动画方案**：以完全二叉树为背景，初始数高亮为红色方块。换根时黄色方块逐步左移，绿色路径显示移动方向。  
- **控制面板**：包含「自动播放」「单步执行」「重置」按钮，速度滑块调节步进间隔。  
- **音效设计**：换根时播放电子音效，找到最小值时触发 8-bit 胜利音乐。

---
处理用时：125.94秒