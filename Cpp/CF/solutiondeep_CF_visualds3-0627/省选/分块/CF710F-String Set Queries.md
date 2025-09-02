# 题目信息

# String Set Queries

## 题目描述

You should process $ m $ queries over a set $ D $ of strings. Each query is one of three kinds:

1. Add a string $ s $ to the set $ D $ . It is guaranteed that the string $ s $ was not added before.
2. Delete a string $ s $ from the set $ D $ . It is guaranteed that the string $ s $ is in the set $ D $ .
3. For the given string $ s $ find the number of occurrences of the strings from the set $ D $ . If some string $ p $ from $ D $ has several occurrences in $ s $ you should count all of them.

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query of the third type. Use functions fflush in C++ and BufferedWriter.flush in Java languages after each writing in your program.

## 样例 #1

### 输入

```
5
1 abc
3 abcabc
2 abc
1 aba
3 abababc
```

### 输出

```
2
2
```

## 样例 #2

### 输入

```
10
1 abc
1 bcd
1 abcd
3 abcd
2 abcd
3 abcd
2 bcd
3 abcd
2 abc
3 abcd
```

### 输出

```
3
2
1
0
```

# AI分析结果



### 唯一算法分类  
**AC自动机 + 二进制分组**

---

### 综合分析与结论  
#### 核心思路与难点  
1. **动态维护问题**：插入/删除字符串需支持高效的在线多模式匹配，传统AC自动机无法直接支持动态更新。  
2. **二进制分组优化**：将字符串按二进制分组维护多个AC自动机，每次插入合并相同大小的块，保证每个字符串最多合并 $O(\log n)$ 次。  
3. **可减性处理**：维护两个AC自动机（插入集合和删除集合），查询结果相减即可。  

#### 算法流程  
1. **插入操作**：将新字符串作为独立块插入，若相邻块大小相同则递归合并并重建AC自动机。  
2. **查询操作**：遍历所有块的AC自动机，累加匹配结果。  
3. **Fail指针优化**：在合并后重建AC自动机的Fail指针时，预处理每个节点的权值总和，避免暴力跳Fail树。  

#### 可视化设计  
- **像素动画**：用不同颜色方块表示AC自动机块，块大小显示为二进制数（如1/2/4/8）。合并时展示方块合并动画，伴随8-bit音效。  
- **匹配演示**：文本串字符逐个高亮，展示当前匹配路径和权值累加过程。  
- **交互控制**：支持单步执行合并操作，查看Fail指针构建细节。  

---

### 题解清单（评分≥4星）  
1. **super蒟蒻（4.5星）**  
   - **亮点**：详细解释二进制分组原理，代码结构清晰，处理删除逻辑简洁。  
   - **核心代码**：通过`Group`类维护插入和删除的AC自动机，动态合并块并重建Fail树。  
   - **个人心得**：提到“贡献具有可减性”，巧妙避免删除操作的复杂处理。  

2. **SDqwq（4.2星）**  
   - **亮点**：简化代码结构，分离插入/删除的AC自动机，动态合并逻辑清晰。  
   - **关键实现**：用`vector`维护每个块的字符串，合并时暴力重构。  

3. **FelFa_1414666（4.0星）**  
   - **亮点**：提供三种解法对比，根号分治与二进制分组并重，适合多角度学习。  
   - **代码特色**：动态开点避免内存爆炸，Fail树预处理权值总和。  

---

### 最优思路与技巧  
1. **二进制分组**：将动态问题转化为静态块处理，合并复杂度均摊为 $O(\log n)$。  
2. **Fail树权值预处理**：在构建Fail指针时直接计算路径权值总和，查询无需跳转。  
3. **双自动机减法**：维护插入/删除两个独立自动机，利用可减性简化删除操作。  

---

### 类似题目推荐  
1. **P5357【模板】AC自动机（二次加强版）**  
   - 静态多模式匹配，练习Fail树优化。  
2. **P3960 列队**  
   - 动态维护问题，使用类似二进制分组思想。  
3. **P5840 [IOI2019]视觉程序**  
   - 动态数据结构与在线查询结合。  

---

### 个人心得摘录  
> “第一次写写丑了，常数有点大。如果用了`printf`的话在后面记得加上`fflush(stdout)`”——调试时发现输出缓存问题，强制刷新避免超时。  

---

### 核心代码实现  
```cpp
// 二进制分组 + AC自动机（super蒟蒻题解核心片段）
struct Group {
    int ch[maxn][26], cnt[maxn], rt, tot;
    void insert(char *s, int root) {
        int u = root, len = strlen(s);
        for (int i=0; i<len; i++) {
            int c = s[i]-'a';
            if (!ch[u][c]) ch[u][c] = ++tot;
            u = ch[u][c];
        }
        cnt[u]++;
    }
    void build(int root) { // 构建Fail指针并预处理权值
        queue<int> q;
        for (int i=0; i<26; i++) 
            if (ch[root][i]) q.push(ch[root][i]);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i=0; i<26; i++) {
                if (ch[u][i]) {
                    fail[ch[u][i]] = ch[fail[u]][i];
                    cnt[ch[u][i]] += cnt[fail[ch[u][i]]];
                    q.push(ch[u][i]);
                }
            }
        }
    }
    // 合并块并重建AC自动机
    void merge(int x, int y) { 
        for (int i=0; i<26; i++) 
            ch[x][i] = merge(ch[x][i], ch[y][i]);
        cnt[x] += cnt[y];
    }
};
```

---

### 可视化方案（伪代码）  
```javascript
// Canvas绘制二进制分块合并动画
function drawBlocks() {
    ctx.fillStyle = "#8B00FF"; // 紫色像素块
    blocks.forEach((block, idx) => {
        const size = Math.log2(block.size) * 10; // 块大小对应像素尺寸
        ctx.fillRect(idx*50, 100, size, size);
        playSound('merge'); // 合并音效
    });
}

// AC自动机匹配动画
function highlightMatch(s) {
    let currentNodes = groups.map(g => g.rt);
    s.split('').forEach((char, i) => {
        currentNodes = currentNodes.map(node => {
            const next = node.ch[char];
            ctx.fillStyle = "#FF4500"; // 高亮当前节点
            drawNode(next); 
            return next;
        });
        delay(300); // 步进延迟
    });
}
```

---

### 复古游戏化设计  
- **像素风格**：16色调色板，AC自动机节点用8x8像素方块表示，Fail指针用绿色连线。  
- **音效设计**：  
  - **插入/合并**：短促“哔”声（Web Audio生成方波）。  
  - **匹配成功**：8-bit胜利音效（上升琶音）。  
- **自动演示模式**：AI按最优顺序合并块，展示二进制分组过程如“2048”游戏。

---
处理用时：72.02秒