# 题目信息

# [ABC255F] Pre-order and In-order

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc255/tasks/abc255_f

$ 1,\ 2,\ \ldots,\ N $ と番号づけられた $ N $ 個の頂点を持つ**二分木**を考えます。 ここで、二分木とは各頂点が高々 $ 2 $ 個の子を持つ根付き木です。より具体的には、二分木の各頂点は高々 $ 1 $ 個の**左の子**と高々 $ 1 $ 個の**右の子**を持ちます。

頂点 $ 1 $ を根とする二分木であって、下記の条件を満たすものが存在するかを判定し、存在する場合はその一例を示してください。

- すべての頂点を深さ優先探索における[**行きがけ順**](https://ja.wikipedia.org/wiki/%E6%9C%A8%E6%A7%8B%E9%80%A0_(%E3%83%87%E3%83%BC%E3%82%BF%E6%A7%8B%E9%80%A0)#.E6.B7.B1.E3.81.95.E5.84.AA.E5.85.88.E6.8E.A2.E7.B4.A2)（pre-order）で並べた列が $ (P_1,\ P_2,\ \ldots,\ P_N) $ である。
- すべての頂点を深さ優先探索における[**通りがけ順**](https://ja.wikipedia.org/wiki/%E6%9C%A8%E6%A7%8B%E9%80%A0_(%E3%83%87%E3%83%BC%E3%82%BF%E6%A7%8B%E9%80%A0)#.E6.B7.B1.E3.81.95.E5.84.AA.E5.85.88.E6.8E.A2.E7.B4.A2)（in-order）で並べた列が $ (I_1,\ I_2,\ \ldots,\ I_N) $ である。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N $ は整数
- $ (P_1,\ P_2,\ \ldots,\ P_N) $ は $ (1,\ 2,\ \ldots,\ N) $ の順列
- $ (I_1,\ I_2,\ \ldots,\ I_N) $ は $ (1,\ 2,\ \ldots,\ N) $ の順列

### Sample Explanation 1

次の画像に示す、頂点 $ 1 $ を根とする二分木が問題文中の条件を満たします。 !\[\](https://img.atcoder.jp/abc255/b51399e8953ae1723d1d9e83617f9be9.png)

### Sample Explanation 2

問題文中の条件を満たすような頂点 $ 1 $ を根とする二分木は存在しません。よって $ -1 $ を出力します。

## 样例 #1

### 输入

```
6
1 3 5 6 4 2
3 5 1 4 6 2```

### 输出

```
3 6
0 0
0 5
0 0
0 0
4 2```

## 样例 #2

### 输入

```
2
2 1
1 2```

### 输出

```
-1```

# AI分析结果



## 算法分类
DFS

---

## 题解思路与解决难点

### 核心思路
1. **前序确定根，中序分割左右子树**：前序首元素为当前根，中序中找到该根的位置，将数组分为左右子树。
2. **递归构造子树**：根据左右子树大小，分割前序数组，递归处理子问题。
3. **错误处理**：检查根是否在中序的正确区间内，确保前序与中序的匹配性。

### 难点与解决方案
1. **快速定位根节点**：预处理中序数组的哈希表，实现O(1)查找根的位置。
2. **区间分割计算**：通过中序中根的左右子树大小，确定前序的左右子区间。
3. **栈溢出风险**：虽然递归深度可能达O(N)，但题目数据规模下可通过评测（实际测试用例未构造极端退化的树）。

### 关键代码分析（program_xwl）
```cpp
void dfs(int l1, int r1, int l2, int r2) {
    if (l1 >= r1) return;
    int root = mp[a[l1]]; // 当前根在中序的位置
    int sizl = root - l2; // 左子树大小
    if (root < l2 || root > r2) exit(0); // 根位置非法
    // 设置左右子节点
    tree[a[l1]] = {a[l1+1], a[l1+sizl+1]};
    dfs(l1+1, l1+sizl, l2, root-1); // 处理左子树
    dfs(l1+sizl+1, r1, root+1, r2); // 处理右子树
}
```
- **核心逻辑**：递归分割前序和中序数组，动态设置左右子节点。
- **优化点**：哈希表预处理根的位置，避免线性查找。

---

## 题解评分（≥4星）
1. **program_xwl (4星)**  
   - 思路清晰，代码简洁。  
   - 显式处理左右子树为空的情况。  
   - 未处理栈溢出，但能通过测试。  

2. **Tsawke (4星)**  
   - 参数命名明确，逻辑简洁。  
   - 使用结构体存储子树，代码可读性高。  

3. **Meickol (4星)**  
   - 非递归参数设计，减少冗余判断。  
   - 显式处理左右子树存在性。  

---

## 最优思路提炼
1. **预处理哈希表**：快速定位中序中根的位置，避免O(N)查找。
2. **递归分割区间**：通过中序的根位置计算左右子树大小，分割前序数组。
3. **即时错误检查**：递归过程中发现根位置非法立即终止，避免无效计算。

---

## 同类题目推荐
1. **LeetCode 105. Construct Binary Tree from Preorder and Inorder Traversal**  
2. **洛谷 P1030 求先序排列**  
3. **LeetCode 106. Construct Binary Tree from Inorder and Postorder Traversal**

---

## 个人心得摘录
- **program_xwl**：强调递归边界条件，认为区间长度为0时直接返回。
- **Tsawke**：提醒注意根节点的初始检查（必须为1），否则直接无解。
- **Ascnbeta**：通过模拟手动构造过程，发现递归参数设计的灵感。

---

## 可视化算法分析

### 动画设计
1. **节点高亮**：当前根节点用红色标记，左子树区间蓝色，右子树区间绿色。
2. **递归步骤**：展示如何分割数组，并用连线表示父子关系。
3. **错误提示**：根位置非法时，整棵子树标红闪烁，播放错误音效。

### 复古像素风格
- **Canvas绘制**：树结构以网格布局展示，节点为8位像素方块。
- **音效**：访问新节点时播放“哔”声，错误时播放“嗡”声。
- **自动演示**：按DFS顺序自动展开子树，支持暂停/继续。

### 交互示例
```javascript
// 伪代码：递归步骤的可视化
function visualizeDFS(l1, r1, l2, r2) {
    highlightRoot(a[l1]); // 高亮当前根
    let rootPos = inOrderMap.get(a[l1]);
    if (invalid(rootPos, l2, r2)) {
        playSound('error');
        return;
    }
    // 分割左右子树
    drawLineToLeft(a[l1+1]); // 左子节点连线
    drawLineToRight(a[l1+sizl+1]); // 右子节点连线
    // 递归动画延迟
    setTimeout(() => visualizeDFS(l1+1, l1+sizl, l2, rootPos-1), 1000);
    setTimeout(() => visualizeDFS(l1+sizl+1, r1, rootPos+1, r2), 2000);
}
```

---

## 代码实现（program_xwl）
```cpp
#include <bits/stdc++.h>
using namespace std;

struct node {int l, r;} tree[200005];
int n, a[200005], b[200005], mp[200005];

void dfs(int l1, int r1, int l2, int r2) {
    if (l1 >= r1) return;
    int root = mp[a[l1]], sizl = root - l2;
    if (root < l2 || root > r2) {
        cout << -1;
        exit(0);
    }
    tree[a[l1]] = {a[l1+1], a[l1+sizl+1]};
    if (sizl == 0) tree[a[l1]].l = 0;
    if (r2 - root == 0) tree[a[l1]].r = 0;
    dfs(l1+1, l1+sizl, l2, root-1);
    dfs(l1+sizl+1, r1, root+1, r2);
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i], mp[b[i]] = i;
    if (a[1] != 1) {
        cout << "-1\n";
        return 0;
    }
    dfs(1, n, 1, n);
    for (int i = 1; i <= n; i++) 
        cout << tree[i].l << ' ' << tree[i].r << '\n';
    return 0;
}
```

---
处理用时：150.08秒