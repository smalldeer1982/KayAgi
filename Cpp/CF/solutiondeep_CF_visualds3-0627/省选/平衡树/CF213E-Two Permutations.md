# 题目信息

# Two Permutations

## 题目描述

Rubik is very keen on number permutations.

A permutation $ a $ with length $ n $ is a sequence, consisting of $ n $ different numbers from 1 to $ n $ . Element number $ i $ $ (1<=i<=n) $ of this permutation will be denoted as $ a_{i} $ .

Furik decided to make a present to Rubik and came up with a new problem on permutations. Furik tells Rubik two number permutations: permutation $ a $ with length $ n $ and permutation $ b $ with length $ m $ . Rubik must give an answer to the problem: how many distinct integers $ d $ exist, such that sequence $ c $ $ (c_{1}=a_{1}+d,c_{2}=a_{2}+d,...,c_{n}=a_{n}+d) $ of length $ n $ is a subsequence of $ b $ .

Sequence $ a $ is a subsequence of sequence $ b $ , if there are such indices $ i_{1},i_{2},...,i_{n} $ $ (1<=i_{1}&lt;i_{2}&lt;...&lt;i_{n}<=m) $ , that $ a_{1}=b_{i1} $ , $ a_{2}=b_{i2} $ , $ ... $ , $ a_{n}=b_{in} $ , where $ n $ is the length of sequence $ a $ , and $ m $ is the length of sequence $ b $ .

You are given permutations $ a $ and $ b $ , help Rubik solve the given problem.

## 样例 #1

### 输入

```
1 1
1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1 2
1
2 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 3
2 3 1
1 2 3
```

### 输出

```
0
```

# AI分析结果



---

## 算法分类
**滑动窗口哈希 + 线段树/平衡树维护动态序列**

---

## 题解思路与核心难点

### 核心思路
1. **哈希预处理**：计算原始排列 $a$ 的哈希值，推导每个 $x$ 对应的 $a+x$ 的哈希值（可线性推导）。
2. **滑动窗口维护**：在 $b$ 中维护长度为 $n$ 的滑动窗口（值域为 $[x+1, x+n]$），动态插入新元素、删除旧元素。
3. **哈希快速比对**：用线段树/平衡树动态计算窗口内元素的哈希值，与 $a+x$ 的哈希值比对。

### 解决难点
1. **动态哈希更新**：窗口每次移动需要插入 $x+n$ 并删除 $x$，需高效更新哈希（线段树维护区间乘积，平衡树维护有序序列）。
2. **哈希碰撞避免**：双哈希（模数取不同大素数）或自然溢出法（利用 unsigned long long 自动取模）。
3. **子序列顺序验证**：通过维护元素在 $b$ 中的位置顺序，确保相对顺序与 $a$ 一致。

---

## 题解评分 (≥4星)

1. **MorsLin (线段树哈希) ★★★★☆**  
   - 亮点：代码简洁，用线段树维护哈希，预处理幂次优化计算。  
   - 关键代码片段：
     ```cpp
     void up(int l, int r, int p) {
         tree[p].tot = tree[ls].tot + tree[rs].tot;
         tree[p].a = tree[ls].a * qpow[tree[rs].tot] + tree[rs].a;
     }
     ```

2. **Link_Cut_Y (自然溢出哈希) ★★★★☆**  
   - 亮点：自然溢出法提升效率，权值线段树实现清晰。  
   - 关键代码片段：
     ```cpp
     tr[u].hash = (ULL)tr[rs].hash + tr[ls].hash * p[tr[rs].size];
     ```

3. **ywy_c_asm (平衡树哈希) ★★★★☆**  
   - 亮点：平衡树维护有序序列，支持动态插入删除。  
   - 关键代码片段：
     ```cpp
     h1[tree] = (h1[ch[tree][0]] * dk1[sz[ch[tree][1]]] + h1[ch[tree][1]]) % p1;
     ```

---

## 最优技巧提炼

### 关键技巧
1. **双哈希/自然溢出**：避免碰撞，提升计算效率。
2. **滑动窗口优化**：每次移动仅更新一个元素，复杂度 $O(\log n)$。
3. **动态数据结构**：线段树维护区间哈希乘积，平衡树维护有序序列哈希。

### 同类型题套路
- **子串匹配**：如 KMP 扩展问题（哈希替代）。
- **动态序列维护**：如区间最值、区间和的高效查询。

---

## 推荐题目
1. **CF514C**：动态哈希判断字符串修改。
2. **LeetCode 76**：滑动窗口最小覆盖子串。
3. **洛谷 P1381**：哈希表加速单词匹配。

---

## 可视化设计

### 算法动画
1. **滑动窗口移动**：  
   - 红色高亮新插入元素 $x+n$，绿色标记被删除元素 $x$。
   - 线段树节点动态着色，展示哈希值合并过程。
   - 底部状态栏显示当前 $x$ 和哈希比对结果。

2. **像素风格演示**：  
   - 8-bit 像素网格表示 $b$ 序列，窗口移动时有“吃豆人”音效。
   - 成功匹配时播放经典 FC 过关音效，失败时短促“哔”声。

3. **交互控制**：  
   - 速度滑块调节动画速度（1x~10x）。
   - 单步执行按钮观察哈希更新细节。

### 核心代码片段（Canvas 绘制）
```javascript
// 绘制滑动窗口
ctx.fillStyle = "#FF0000"; // 新元素红色
ctx.fillRect(posX, posY, 20, 20);
ctx.fillStyle = "#00FF00"; // 旧元素绿色
ctx.clearRect(oldX, oldY, 20, 20);

// 哈希值更新动画
function updateHashVisual(hashOld, hashNew) {
    animate({hash: hashOld}, {hash: hashNew}, {
        duration: 1000,
        step: (val) => document.getElementById("hash-value").innerText = val
    });
}
```

---

## 代码实现（MorsLin 线段树版）
```cpp
#include <iostream>
#define ULL unsigned long long
using namespace std;
const int N=2e5+5;
ULL p[N]={1},ha,sum;
int n,m,a[N],b[N],pos[N];

struct SegTree {
    ULL val; int cnt;
} tr[N<<2];

void pushup(int u) {
    tr[u].cnt = tr[u<<1].cnt + tr[u<<1|1].cnt;
    tr[u].val = tr[u<<1].val * p[tr[u<<1|1].cnt] + tr[u<<1|1].val;
}

void update(int u,int l,int r,int x,int v) {
    if(l == r) {
        tr[u].cnt = (v != 0);
        tr[u].val = v;
        return;
    }
    int mid = (l+r)>>1;
    if(x <= mid) update(u<<1,l,mid,x,v);
    else update(u<<1|1,mid+1,r,x,v);
    pushup(u);
}

int main() {
    cin >> n >> m;
    for(int i=1;i<=n;i++) {
        cin >> a[i];
        ha = ha * 131 + a[i];
        p[i] = p[i-1] * 131;
        sum += p[i-1];
    }
    for(int i=1;i<=m;i++) {
        cin >> b[i];
        pos[b[i]] = i;
    }
    int ans = 0;
    for(int i=1;i<=m;i++) {
        update(1,1,m,pos[i],i);
        if(i > n) update(1,1,m,pos[i-n],0);
        if(i >= n && tr[1].val == ha + sum*(i-n)) ans++;
    }
    cout << ans;
    return 0;
}
```

---
处理用时：76.76秒