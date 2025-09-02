# 题目信息

# Phone List

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=25&page=show_problem&problem=2347

[PDF](https://uva.onlinejudge.org/external/113/p11362.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11362/86a9ad22547794c86c707c6301a3959ca76cfd43.png)

## 样例 #1

### 输入

```
2
3
911
97625999
91125426
5
113
12340
123440
12345
98346```

### 输出

```
NO
YES```

# AI分析结果



## 唯一算法分类
Trie树 / 排序法

---

## 综合分析与结论

### 核心思路
题目要求判断是否存在电话号码互为前缀。所有题解可分为两类：
1. **排序法**（doyo、da32s1da）：将字符串按字典序排序，若存在前缀关系，则前缀必然在排序后相邻。只需检查每对相邻字符串即可。
2. **Trie树**（Adaxy、swiftc等）：构建字典树，插入时实时判断两种情况：路径上有其他结束节点（已有前缀）或插入后仍有子节点（成为前缀）。

### 难点对比
- **排序法**需证明排序后只需检查相邻字符串的充分性，通过字典序性质可推导成立。
- **Trie树**需正确处理两种冲突条件，并优化空间（避免静态数组过大导致TLE）。

### 可视化设计
**Trie树构建动画方案：**
1. **节点高亮**：插入字符时当前路径节点用黄色高亮，已存在的结束节点用红色闪烁。
2. **冲突提示**：发现路径上有结束节点时，触发红色边框+失败音效；插入完成时若仍有子节点，触发蓝色边框+警告音效。
3. **像素风格**：每个节点用16x16像素方块表示，数字用8-bit字体，背景音乐为FC风格循环音轨。

---

## 题解清单（≥4星）

### 1. doyo（排序法） ★★★★☆
**亮点**：代码简洁，利用STL排序和字符串函数快速实现。  
**核心逻辑**：排序后相邻字符串前缀检查，时间复杂度O(n log n)。

```cpp
sort(s+1, s+n+1);
for(int i=1; i<=n-1; i++)
    if(s[i+1].find(s[i]) == 0) // 前缀检查
```

### 2. Adaxy（Trie树） ★★★★★
**亮点**：实时冲突检测，空间优化到位。  
**关键变量**：`endd[]`标记结束节点，`vis[]`标记路径存在子节点。

```cpp
void insert(char* a) {
    if(endd[p]) flag=0; // 路径存在结束节点
    if(vis[p]) flag=0;  // 当前节点仍有子节点
}
```

### 3. swiftc（Trie树） ★★★★☆
**亮点**：结构体封装节点，逻辑清晰。  
**冲突检测**：插入时检查路径结束标记，结束时检查子节点存在性。

```cpp
if(a[now].end) flag=1;          // 中途发现结束标记
if(k==s.length() && a[now].son[i]) flag=1; // 结束仍有子节点
```

---

## 最优思路提炼

### 排序法核心技巧
- **字典序性质**：若A是B的前缀，排序后A必然在B前且相邻。
- **STL优化**：`sort` + `find`组合实现O(1)前缀检查。

### Trie树核心技巧
- **实时双检测**：
  - 插入路径中遇到结束标记 → 存在前缀。
  - 插入完成时仍有子节点 → 成为前缀。
- **内存控制**：动态分配节点编号，避免静态数组空间浪费。

---

## 同类型题推荐
1. **前缀统计**：P2580 他「的」续集（Trie统计前缀出现次数）
2. **最长前缀匹配**：P2922 [USACO08DEC] Secret Message（Trie多模式匹配）
3. **异或前缀**：P4551 最长异或路径（Trie处理二进制前缀）

---

## 个人心得摘录
- **Adaxy**：数组大小需精确计算，过大导致TLE（静态数组内存清零耗时）。
- **da32s1da**：排序前处理前导零的技巧（首字符添加非零标记）。
- **谦谦君子**：Trie插入函数返回冲突状态，优化无效插入。

---

## 可视化代码片段（Trie插入逻辑）

```javascript
// 伪代码：Trie插入动画核心逻辑
function insertPixelAnim(s) {
    let node = root;
    for (let c of s) {
        highlight(node, 'yellow'); // 当前节点高亮
        playSound('step');
        if (node.hasEnd) {
            highlight(node, 'red', 1000); // 发现结束节点
            playSound('error');
            return 'NO';
        }
        if (!node.children[c]) {
            node.children[c] = createNode(c); // 创建新节点
            drawPixelNode(node.children[c]);
        }
        node = node.children[c];
    }
    if (node.hasChildren()) {
        highlight(node, 'blue', 1000); // 仍有子节点
        playSound('warning');
        return 'NO';
    }
    node.setEndIcon(); // 标记结束
}
```

---

## 复古游戏化设计
- **像素调色板**：16色FC风格（深蓝背景，亮绿节点，红色警告）。
- **音效设计**：
  - `step.wav`：移动时的8-bit哔声。
  - `error.wav`：冲突时的低音爆破声。
  - `complete.wav`：成功时的上升音阶。
- **自动演示模式**：AI按最佳路径插入，每步延迟可调（100ms~1s）。

---
处理用时：118.71秒