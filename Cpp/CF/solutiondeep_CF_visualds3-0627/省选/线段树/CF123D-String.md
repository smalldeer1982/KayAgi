# 题目信息

# String

## 题目描述

You are given a string $ s $ . Each pair of numbers $ l $ and $ r $ that fulfill the condition $ 1<=l<=r<=|s| $ , correspond to a substring of the string $ s $ , starting in the position $ l $ and ending in the position $ r $ (inclusive).

Let's define the function of two strings $ F(x,y) $ like this. We'll find a list of such pairs of numbers for which the corresponding substrings of string $ x $ are equal to string $ y $ . Let's sort this list of pairs according to the pair's first number's increasing. The value of function $ F(x,y) $ equals the number of non-empty continuous sequences in the list.

For example: $ F(babbabbababbab,babb)=6 $ . The list of pairs is as follows:

 $ (1,4),(4,7),(9,12) $

Its continuous sequences are:

- $ (1,4) $
- $ (4,7) $
- $ (9,12) $
- $ (1,4),(4,7) $
- $ (4,7),(9,12) $
- $ (1,4),(4,7),(9,12) $

Your task is to calculate for the given string $ s $ the sum $ F(s,x) $ for all $ x $ , that $ x $ belongs to the set of all substrings of a string $ s $ .

## 说明/提示

In the first sample the function values at $ x $ equal to "a", "aa", "aaa" and "aaaa" equal 10, 6, 3 and 1 correspondingly.

In the second sample for any satisfying $ x $ the function value is 1.

## 样例 #1

### 输入

```
aaaa
```

### 输出

```
20
```

## 样例 #2

### 输入

```
abcdef
```

### 输出

```
21
```

## 样例 #3

### 输入

```
abacabadabacaba
```

### 输出

```
188
```

# AI分析结果



### 唯一算法分类
**后缀自动机 (SAM)**

---

### 综合分析与结论
#### 核心算法流程
1. **SAM 构建**：将字符串构建为后缀自动机，每个状态表示一组 endpos 相同的子串（等价类）
2. **统计出现次数**：通过 parent 树的子树大小统计每个等价类的出现次数 `ed[p]`
3. **贡献计算**：每个等价类的贡献为 `ed[p]*(ed[p]+1)/2 * (len(p)-len(link(p)))`，累加所有状态贡献

#### 解决难点
- **去重统计**：SAM 天然去重，每个状态对应一组本质不同的子串
- **高效计数**：通过 parent 树的后序遍历统计出现次数，时间复杂度 O(n)

#### 可视化设计
- **动画方案**：
  - 步骤1：动态绘制 SAM 节点，用不同颜色区分新节点与克隆节点
  - 步骤2：高亮 parent 指针链接过程，展示等价类的合并
  - 步骤3：用动态进度条显示每个节点的贡献计算过程
- **复古风格**：
  - 8-bit 音效：插入字符时播放 "哔" 声，克隆节点时播放 "叮" 声
  - 像素化节点：用 16x16 像素块表示状态，转移边用箭头连接

---

### 题解清单 (≥4星)
#### 1. Alex_Wei (⭐⭐⭐⭐⭐)
- **亮点**：直接使用 SAM 特性，代码简洁高效（线性时间复杂度）
- **关键代码**：
```cpp
for(int i=1;i<=cnt;i++) ans += 1ll*ed[i]*(ed[i]+1)/2*(len[i]-len[fa[i]]);
```

#### 2. L_zaa_L (⭐⭐⭐⭐)
- **亮点**：详细注释 SAM 构建过程，适合初学者理解
- **个人心得**："统计出现次数时要注意原串的后缀才会产生贡献"

#### 3. w33z8kqrqk8zzzx33 (⭐⭐⭐⭐)
- **亮点**：使用 map 实现动态转移，处理任意字符集
- **优化**：通过拓扑排序避免递归，避免栈溢出风险

---

### 最优思路提炼
**SAM 贡献公式**：
```math
\sum_{state} \frac{ed_p(ed_p+1)}{2} \times (len(p)-len(link(p)))
```
- **ed_p**：该等价类在字符串中的出现次数
- **len(p)-len(link(p))**：该等价类包含的不同子串数量

---

### 同类型题目推荐
1. [P3804 【模板】后缀自动机](https://www.luogu.com.cn/problem/P3804)
2. [P2178 NOI2015 品酒大会](https://www.luogu.com.cn/problem/P2178)
3. [CF802I Fake News](https://www.luogu.com.cn/problem/CF802I)

---

### 可视化代码片段
```javascript
// 绘制 SAM 节点的 Canvas 示例
function drawState(ctx, node, x, y) {
  ctx.fillStyle = node.isClone ? "#FF9999" : "#99CCFF";
  ctx.fillRect(x, y, 30, 30);
  ctx.strokeStyle = "#000";
  ctx.strokeText(node.len, x+5, y+20);
  
  // 绘制 parent 指针
  if(node.link) {
    ctx.beginPath();
    ctx.moveTo(x+15, y+30);
    ctx.lineTo(linkX+15, linkY);
    ctx.strokeStyle = "#FF0000";
    ctx.stroke();
  }
}

// 贡献计算动画
function animateContribution(node) {
  let formula = `贡献 += ${node.ed}×${node.ed+1}/2 × (${node.len}-${node.linkLen})`;
  document.getElementById("formula").innerHTML = formula;
}
```

---

### 复古游戏化设计
1. **音效设计**：
   - 插入字符：8-bit "哔" 声（频率 800Hz，时长 50ms）
   - 克隆节点：下降音阶（从 600Hz 到 400Hz）
   - 计算完成：经典 FC 过关音效

2. **关卡系统**：
   - 第1关：构建 SAM 基础结构
   - 第2关：统计 parent 树出现次数
   - 第3关：最终贡献计算

3. **积分规则**：
   - 正确插入节点：+100 分
   - 错误转移时：播放爆炸音效并 -50 分

---

### 关键实现代码（SAM 核心）
```cpp
void insert(int c) {
  int p = last, cur = ++cnt;
  len[cur] = len[last] + 1;
  ed[cur] = 1; // 标记终止状态
  
  while(p && !ch[p][c]) {
    ch[p][c] = cur;
    p = link[p];
  }
  
  if(!p) link[cur] = 1;
  else {
    int q = ch[p][c];
    if(len[p]+1 == len[q]) link[cur] = q;
    else {
      int clone = ++cnt; // 克隆节点
      len[clone] = len[p] + 1;
      link[clone] = link[q];
      memcpy(ch[clone], ch[q], sizeof(ch[q]));
      while(p && ch[p][c] == q) {
        ch[p][c] = clone;
        p = link[p];
      }
      link[q] = link[cur] = clone;
    }
  }
  last = cur;
}
```

---
处理用时：65.70秒