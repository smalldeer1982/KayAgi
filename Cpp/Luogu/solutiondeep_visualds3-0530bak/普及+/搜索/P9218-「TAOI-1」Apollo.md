# 题目信息

# 「TAOI-1」Apollo

## 题目背景

Execution.

这题原来叫 `std::cout << std::fixed << std::setprecision(1) << 6.5 << '\n';`。

[被当事人删掉的图片.jpg]

**【Upd 2023/04/15 21:42】添加了一组 Hack 数据位于 Subtask 2，#13。现在所有赛时的 $\bm{50}$ 分提交理论上均只能获得 $\bm{30}$ 分。**

## 题目描述

给出 $n$ 个十进制小数 $a_1 \dots a_n$。

对于一个 **数** $a$，定义其精度 $f(a)$ 表示最小的非负整数 $k$ 使得 $10^k\times a$ 为整数；对于整数 $a$，定义 $f(a) = 0$。对于两个十进制小数 $a, b$，定义 $g(a, b)$ 为对于所有 **数** $c \in [\min(a,b), \max(a,b)]$ 的 $f(c)$ 的最小值。

对于所有 $1 \leq i \leq n$，你需要求出 $\sum\limits_{j=1}^ng(a_i, a_j)$ 的值并输出。

定义十进制小数是一个含有整数部分和小数部分的数，其小数部分不为 $0$。之所以描述得这么愚蠢是因为保证输入的每个数都有小数点，但是好像无论什么写法都会有人提出不满，真是抱歉了。~~所以还是得看看被当事人删掉的图片。所以我在这里写闲话有人看得到吗。~~

## 说明/提示

### 数据范围

**本题采用捆绑测试。**

令 $\sum\limits_{i=1}^n f(a_i) = t$。

- Subtask 1（15 points）：$a_i \leq 10$，$n \leq 5$，$t \leq 10$。
- Subtask 2（15 points）：$a_i \leq 10$，$n \leq 100$，$t \leq 1000$。
- Subtask 3（20 points）：$n \leq 1722$。
- Subtask 4（15 points）：$a_i \leq 1$。
- Subtask 5（35 points）：无特殊限制。

对于所有数据，$0 \lt a_i \lt 10^9$，$1 \leq n \leq 10^5$，$1 \leq t \leq 3 \times 10^6$，**保证 $\bm{a_i}$ 没有后导 [$\color{black}\bm 0$](https://cdn.luogu.com.cn/upload/image_hosting/pg66fm1z.png)，不保证 $\bm{a_i}$ 互不相同**。

### 样例解释

以 $i = 1$ 为例：

+ $j = 1$：取 $c = 11.4514$，$f(c) = 4$；
+ $j = 2$：取 $c = 11.46$，$f(c) = 2$；
+ $j = 3$：取 $c = 11.2$，$f(c) = 1$；
+ $j = 4$：取 $c = 11.3$，$f(c) = 1$；
+ $j = 5$：取 $c = 11.47$，$f(c) = 2$。

故 $\sum\limits_{j=1}^n g(a_1, a_j) = 4 + 2 + 1 + 1 + 2 = 10$。对于同一个 $j$，上文给出的所有 $c$，都可能有其它的不同的 $c$ 满足 $f(c)$ 同样最小。

## 样例 #1

### 输入

```
5
11.4514
11.4778
11.1338
11.1236
11.4789```

### 输出

```
10
11
9
9
11```

## 样例 #2

### 输入

```
8
1.1145
1.114
1.1145
1.514
1.19198
1.1154
1.114
1.1145```

### 输出

```
24
21
24
10
18
22
21
24```

# AI分析结果



# 算法分类
其他搜索（基于字典树的前缀统计）

---

## 综合分析与结论

### 核心思路
1. **问题转换**：将小数的小数部分视为字符串，g(a,b)等价于两数小数部分的最长公共前缀长度+1
2. **字典树构建**：以每个数的整数部分为分组，小数部分为字符串建立字典树
3. **贡献统计**：
   - 树节点记录经过次数、结束次数、深度
   - 遍历查询路径时，统计分支节点贡献（不同前缀的数量 × 当前深度）
   - 处理比当前数更长的前缀贡献（以当前路径为前缀的延伸）

### 可视化设计
**动画方案**：
1. **树形结构展示**：Canvas绘制字典树，节点显示深度/统计值
2. **插入过程**：
   - 高亮当前处理字符
   - 动态创建新节点（像素爆炸特效）
   - 更新路径上的统计值（计数器跳动）
3. **查询过程**：
   - 沿路径向下移动时显示绿色光标
   - 遇到分支节点时，显示红色高亮分支计数
   - 贡献值以气泡形式从节点弹出
4. **游戏化要素**：
   - 8位音效：插入时"哔"声，查询时不同音调表示路径深度
   - 积分系统：正确计算贡献时获得分数，错误时扣分
   - 关卡模式：按整数部分分组作为独立关卡

---

## 题解清单（≥4星）

### 1. wloving（★★★★☆）
**关键亮点**：
- 清晰分离整数部分与小数部分处理
- 字典树节点记录深度与统计值
- 查询时动态计算分支贡献与延伸贡献
```cpp
void insert(string s) {
  int u = 0;
  for (char c : s) {
    int ch = toNum[c];
    if (!trie[u].son[ch]) trie[u].son[ch] = ++tot;
    u = trie[u].son[ch];
    trie[u].num++; // 统计经过次数
    if (ch == 10) trie[u].dep = i - dot; // 记录小数位数
  }
  trie[u].end++; // 记录结束次数
}
```

### 2. irris（★★★★☆）
**创新点**：
- 将LCA深度映射为贡献值
- 分组处理整数部分相同的数
```cpp
for (auto [idx, i] : floor) // 按整数部分分组
for (int i = l; i <= r; ++i) insert(Q[id[i]]); // 组内插入
```

### 3. Lysea（★★★★☆）
**优化技巧**：
- 预处理小数部分为独立字符串
- 动态维护节点贡献公式
```cpp
ans += dep*(cnt[p]-cnt[t[p][c]]-en[p]+en[t[p][c]]);
```

---

## 核心代码实现
wloving题解核心查询逻辑：
```cpp
int findStr(string s) {
  int sum = 0, re = trie[0].num;
  int u = 0;
  for (int i = 0; i < s.size(); i++) {
    int ch = toNum[s[i]];
    u = trie[u].son[ch];
    
    // 计算分支贡献
    int num = re - trie[u].num + trie[u].end;
    sum += num * trie[u].dep;
    re -= num;
  }
  
  // 处理延伸贡献
  sum += (trie[u].num - trie[u].end) * trie[u].dep;
  return sum;
}
```

---

## 相似题目推荐
1. P2580 于是他错误的点名开始了（字典树基础应用）
2. P8306 【模板】字典树（标准实现练习）
3. P2922 [USACO08DEC]Secret Message（前缀统计问题）

---

## 可视化代码片段（Canvas动画）
```javascript
class TrieAnimator {
  constructor(canvas) {
    this.ctx = canvas.getContext('2d');
    this.nodes = new Map(); // {id: {x,y,children}}
    this.activePath = [];
  }

  drawNode(id, pos) {
    this.ctx.fillStyle = '#8BE9FD';
    this.ctx.beginPath();
    this.ctx.arc(pos.x, pos.y, 15, 0, Math.PI*2);
    this.ctx.fill();
    
    // 播放插入音效
    if(typeof beep === 'function') 
      beep(440 + id*10, 50);
  }

  highlightPath(char, depth) {
    this.ctx.strokeStyle = '#50FA7B';
    this.ctx.lineWidth = 3;
    // 绘制路径高亮动画...
  }
}
```

---

## 总结与心得
**关键突破点**：
1. 发现整数部分相同时问题可转化为前缀匹配
2. 通过字典树统计代替暴力两两比较
3. 贡献值分解为分支贡献和延伸贡献

**调试技巧**：
- 对小数1.114和1.1145的边界测试至关重要
- 使用字符串比较验证树结构正确性

**性能优化**：
- 预处理整数部分分组减少内存消耗
- 节点存储深度而非实时计算

**思维提升**：
- 将数值问题转化为字符串处理是典型降维思想
- 树形结构的统计功能往往比存储功能更有价值

---
处理用时：67.95秒