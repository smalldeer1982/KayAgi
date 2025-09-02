# 题目信息

# LCS - Longest Common Substring

## 题目描述

A string is finite sequence of characters over a non-empty finite set Σ.

In this problem, Σ is the set of lowercase letters.

Substring, also called factor, is a consecutive sequence of characters occurrences at least once in a string.

Now your task is simple, for two given strings, find the length of the longest common substring of them.

Here common substring means a substring of two or more strings.

## 样例 #1

### 输入

```
alsdfkjfjkdsal
fdjskalajfkdsla```

### 输出

```
3```

# AI分析结果



## 算法分类
后缀自动机（SAM）/ 后缀数组（SA）

---

## 综合分析与结论

### 核心思路与难点
**问题核心**：寻找两个字符串的最长连续公共子串  
**核心算法**：  
1. **后缀自动机（SAM）**：对第一个字符串构建 SAM，用第二个字符串在 SAM 上进行状态转移匹配，利用 parent 树回溯更新当前匹配长度。  
2. **后缀数组（SA）**：合并两个字符串后构造后缀数组，通过相邻不同源后缀的 height 值求最大值。

**解决难点**：  
- **SAM 匹配策略**：匹配失败时沿 parent 树回溯，维护当前有效长度（`len = l[p] + 1`而非直接取节点长度）  
- **SA 合并处理**：需插入分隔符避免跨字符串的非法匹配，通过相邻后缀判断来源  
- **时间复杂度**：SAM 为 O(n)，SA 为 O(n log n)

---

## 题解评分（≥4星）

### 1. bztMinamoto（5星）
- **亮点**：SAM 标准实现，变量命名清晰，匹配逻辑简洁  
- **关键代码**：
```cpp
void calc(int n) { // 匹配第二个字符串的核心逻辑
    int p = 1;
    for (int i =1; i<=n; i++) {
        int c = t[i]-'a';
        if (ch[p][c]) len++, p=ch[p][c];
        else {
            for (;p && !ch[p][c]; p=fa[p]);
            if (p) len = l[p]+1, p=ch[p][c];
            else len=0, p=1;
        }
        ans = max(ans, len);
    }
}
```

### 2. a1co0av5ce5az1cz0ap_（4星）
- **亮点**：SA 解法完整，处理相邻后缀逻辑严谨  
- **优化点**：需注意分隔符插入位置，代码可读性稍差

### 3. Rainybunny（4星）
- **亮点**：指针式 SAM 实现，注释详细，匹配过程可视化友好  
- **核心片段**：
```cpp
if (p -> ch[c] != NULL) ++now, p = p->ch[c];
else {
    for (; p && !p->ch[c]; p = p->fa);
    if (p) now = p->mx +1, p = p->ch[c];
    else now=0, p=rt;
}
```

---

## 最优思路与技巧提炼

### 关键技巧
1. **SAM 动态匹配**：  
   - 初始状态为根节点，`len=0`  
   - 匹配成功时 `len++`，失败时沿 parent 树回溯至最近可转移节点，更新 `len = l[p]+1`  
   - 每次更新全局最大值 `ans`

2. **Parent 树回溯**：  
   - 每个节点的 parent 指向更短后缀的状态，保证回溯时仍为当前子串的后缀  
   - `l[p]` 表示节点 p 能接受的最长子串长度

3. **SA 相邻检查**：  
   - 仅需检查排名相邻的后缀对，利用 `height` 数组的区间最小值性质  

---

## 同类型题推荐
1. **P3181 [HAOI2016]找相同字符**（广义 SAM 或 SA）  
2. **P3763 [TJOI2017]DNA**（SAM 多模式匹配）  
3. **P3975 [TJOI2015]弦论**（SAM 求第 K 小子串）

---

## 可视化与算法演示

### 核心动画设计（SAM 方案）
1. **SAM 构建阶段**：  
   - 显示第一个字符串的字符逐个插入，动态绘制 SAM 节点和转移边  
   - 用不同颜色区分新节点（绿色）和克隆节点（橙色）

2. **匹配阶段**：  
   - 第二个字符串字符高亮显示（黄色背景）  
   - 当前 SAM 节点用红色边框标记，转移边加粗显示  
   - 匹配失败时沿 parent 树回溯（灰色虚线箭头），节点渐隐效果

3. **关键变量追踪**：  
   - 实时显示 `len` 和 `ans` 的数值变化  
   - 在 parent 树回溯时，显示 `len = l[p] + 1` 的公式推导

### 复古像素风格实现
- **颜色方案**：  
  - SAM 节点：深蓝（正常）、亮红（当前状态）  
  - 转移边：青色（有效）、灰色（无效）  
  - 字符串字符：8-bit 风格像素块（16x16）

- **音效设计**：  
  - 成功转移：短促 "哔" 声（频率 800Hz）  
  - 回溯操作：低音 "咚" 声（频率 200Hz）  
  - 更新最大值：上扬音效（C 大调音节）

---

## 代码核心实现（SAM 匹配）
```javascript
// 模拟 SAM 匹配过程（伪代码）
function simulateSAM(s, t) {
    let p = root, len = 0, ans = 0;
    for (let c of t) {
        if (p.trans[c]) {
            len++;
            p = p.trans[c];
        } else {
            while (p && !p.trans[c]) p = p.parent;
            if (p) {
                len = p.maxLen + 1;
                p = p.trans[c];
            } else {
                p = root;
                len = 0;
            }
        }
        ans = Math.max(ans, len);
        // 更新 Canvas 绘制和音效
        highlightNode(p);
        playSound('move');
    }
    return ans;
}
```

---
处理用时：71.25秒