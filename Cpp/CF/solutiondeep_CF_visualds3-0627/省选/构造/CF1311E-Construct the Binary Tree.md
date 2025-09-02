# 题目信息

# Construct the Binary Tree

## 题目描述

You are given two integers $ n $ and $ d $ . You need to construct a rooted binary tree consisting of $ n $ vertices with a root at the vertex $ 1 $ and the sum of depths of all vertices equals to $ d $ .

A tree is a connected graph without cycles. A rooted tree has a special vertex called the root. A parent of a vertex $ v $ is the last different from $ v $ vertex on the path from the root to the vertex $ v $ . The depth of the vertex $ v $ is the length of the path from the root to the vertex $ v $ . Children of vertex $ v $ are all vertices for which $ v $ is the parent. The binary tree is such a tree that no vertex has more than $ 2 $ children.

You have to answer $ t $ independent test cases.

## 说明/提示

Pictures corresponding to the first and the second test cases of the example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1311E/514e626aa001052fb71d69f413a53a8e6f0cb5f0.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1311E/6407c12a699d89084b087667ed6f21f3aeed074d.png)

## 样例 #1

### 输入

```
3
5 7
10 19
10 18```

### 输出

```
YES
1 2 1 3 
YES
1 2 3 3 9 9 2 1 6 
NO```

# AI分析结果



**唯一算法分类**：构造算法、树结构调整

---

### **题解思路与解决难点**

#### **核心思路**
1. **确定可行范围**：计算最小（完全二叉树）和最大（链状）深度总和，判断d是否在该区间。
2. **调整策略**：从初始结构（链或完全二叉树）出发，通过移动节点调整深度总和至d。
3. **高效实现**：选择线性时间复杂度的方法，如从链或满二叉树开始，逐步调整节点位置。

#### **解决难点**
- **动态调整父节点**：在移动节点时需正确更新父节点，并确保二叉树性质。
- **避免重复计算**：通过维护链尾或分层记录节点，减少无效遍历。
- **边界处理**：如移动节点时深度变化超出预期，需快速修正。

---

### **题解评分（≥4星）**
1. **万弘（★★★★★）**  
   - **亮点**：线性时间复杂度，逻辑清晰，代码简洁。通过维护链尾快速调整节点位置。
2. **CCA（★★★★☆）**  
   - **亮点**：分层管理节点，直观展示每层调整过程，代码可读性强。
3. **syksykCCC（★★★★☆）**  
   - **亮点**：优先队列优化，自动选择深度最大的节点调整，适合教学演示。

---

### **最优思路提炼**
**关键技巧**：
1. **链尾维护法**（万弘）：  
   - 初始构造完全二叉树，记录链尾节点 `pos`。
   - **从大到小遍历节点**，将非链节点挂到链尾，直接计算深度差调整剩余 `d`。
   - **代码片段**：
     ```cpp
     for (ll i = n; i; --i) {
         if ((i & (i - 1)) == 0) continue; // 跳过链上节点
         sum_dep -= dep[pos] + 1 - dep[i];
         if (sum_dep <= 0) {
             while (sum_dep) pos = fa[pos], ++sum_dep; // 修正位置
             fa[i] = pos; break;
         }
         fa[i] = pos; dep[i] = dep[pos] + 1; pos = i;
     }
     ```
2. **分层调整法**（CCA）：  
   - 使用 `vector` 记录每层节点，通过移动节点到下一层逐步增加深度总和。
   - **核心逻辑**：
     ```cpp
     while (sum < d) {
         for (int i = Max; i >= 0; i--) {
             if (cnt[i] >= 2 && cnt[i + 1] < (cnt[i] - 1) * 2) {
                 // 移动节点到下一层
                 tree[i + 1][++cnt[i + 1]] = tree[i][cnt[i]];
                 cnt[i]--; sum++;
                 break;
             }
         }
     }
     ```

---

### **同类型题推荐**
1. **CF 1144F**（图着色构造）
2. **洛谷 P1967**（树结构调整求最大生成树）
3. **LeetCode 655**（二叉树序列化构造）

---

### **可视化设计**
**动画方案**：
1. **初始状态**：展示完全二叉树或链状结构，节点按深度分层，颜色区分不同层。
2. **调整过程**：  
   - **高亮移动节点**：红色标记当前调整的节点，绿色标记目标父节点。
   - **动态更新**：移动时显示深度差变化，右侧面板实时显示当前总深度 `d`。
3. **复古像素风格**：  
   - **Canvas 绘制**：节点用8位像素方块表示，移动时播放“滴”音效。
   - **背景音乐**：循环播放8位风格轻音乐，成功/失败时播放不同音效。

**交互设计**：  
- **步进控制**：支持暂停/继续，拖动进度条观察每一步调整。
- **自动模式**：AI自动选择最优移动顺序，类似贪吃蛇路径规划。

---

### **核心代码实现**
**万弘题解完整代码**：
```cpp
#include<bits/stdc++.h>
#define MAXN 200011
using namespace std;
typedef long long ll;
ll fa[MAXN], dep[MAXN];

void solve() {
    ll n, d, cur = 0, pos;
    cin >> n >> d;
    dep[0] = -1;
    for (ll i = 1; i <= n; ++i) {
        fa[i] = i >> 1;
        dep[i] = dep[i >> 1] + 1;
        cur += dep[i];
        if ((i & (i - 1)) == 0) pos = i;
    }
    d -= cur;
    if (d < 0) { cout << "NO\n"; return; }
    for (ll i = n; i >= 1; --i) {
        if ((i & (i - 1)) == 0) continue;
        d -= dep[pos] + 1 - dep[i];
        if (d <= 0) {
            while (d < 0) pos = fa[pos], d++;
            fa[i] = pos; d = 0; break;
        }
        fa[i] = pos; dep[i] = dep[pos] + 1; pos = i;
    }
    if (d != 0) cout << "NO\n";
    else {
        cout << "YES\n";
        for (int i = 2; i <= n; ++i) cout << fa[i] << " ";
        cout << "\n";
    }
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}
```

---

### **总结**
构造二叉树的核心在于灵活调整节点位置，通过维护链尾或分层管理实现高效操作。万弘的线性方法在时间和空间上均最优，适合竞赛场景。可视化时可结合像素动画和音效增强理解，重点展示节点移动和深度差计算。

---
处理用时：61.10秒