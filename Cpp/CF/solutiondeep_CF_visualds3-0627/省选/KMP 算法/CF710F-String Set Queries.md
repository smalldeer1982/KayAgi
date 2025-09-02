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



# 算法分类  
**AC自动机 + 二进制分组**

---

## 综合分析与结论  
本题需动态维护字符串集合的多模式匹配，核心难点在于高效处理插入/删除操作与在线查询。二进制分组结合AC自动机是核心解法：  
1. **动态维护**：将插入的字符串按二进制分组为多个AC自动机块，每块大小是2的幂次，合并时重构保证块数O(log n)。  
2. **可减性**：删除操作视为插入负权值字符串，用两个AC自动机分别记录添加和删除，查询时结果相减。  
3. **时间复杂度**：每个字符串最多合并O(log n)次，总复杂度O(L log n)，L为总字符串长度。

### 可视化设计要点  
1. **像素动画**：用Canvas绘制多个AC自动机块，不同颜色表示不同块大小（如2^k用不同色块）。  
2. **合并演示**：插入新块时触发合并动画，高亮相同大小的块合并为更大的块，类似2048游戏。  
3. **音效交互**：块合并时播放“升级”音效，查询时显示各块的匹配路径。  
4. **步进控制**：允许单步执行插入/合并操作，观察fail指针重构过程。

---

## 题解清单 (≥4星)  
### 唐一文（赞55）  
- **亮点**：详细推导二进制分组复杂度，代码结构清晰，处理合并与重建逻辑严谨。  
- **评分**：⭐️⭐️⭐️⭐️⭐️  
- **核心代码**：  
  ```cpp  
  void merge() {  
      --N, size[N] <<= 1;  
      // 合并两个块并重建AC自动机  
  }  
  ```

### super蒟蒻（赞28）  
- **亮点**：引入二进制分组类比2048游戏，代码注释明确，处理删除操作直观。  
- **评分**：⭐️⭐️⭐️⭐️  
- **核心片段**：  
  ```cpp  
  while (siz[top] == siz[top - 1]) {  
      merge(); // 合并相同大小的块  
  }  
  ```

### SDqwq（赞15）  
- **亮点**：简化删除逻辑，直接维护权值（1/-1），代码更简洁。  
- **评分**：⭐️⭐️⭐️⭐️  
- **关键实现**：  
  ```cpp  
  void upd(char *s, int val) {  
      rt[++tot] = ++idx;  
      ins(s, val, rt[tot]);  
      // 合并块后build fail  
  }  
  ```

---

## 最优思路与技巧  
1. **二进制分组**：将插入操作分块为2^k大小，合并时暴力重构AC自动机，保证块数O(log n)。  
2. **Fail指针优化**：预处理每个节点的累计权值（`sum[u] = val[u] + sum[fail[u]]`），避免跳转fail链。  
3. **合并策略**：递归合并相同大小的块，复用Trie结构减少内存消耗。  

---

## 同类型题目  
1. **[P5357] AC自动机（二次加强版）**  
2. **[P3966] [TJOI2013]单词**  
3. **[P2444] [POI2011]病毒**  

---

## 代码核心实现  
**唐一文的合并与查询逻辑**  
```cpp  
struct Group {  
    int stk[maxn], size[maxn], N;  
    void merge() {  
        --N, size[N] <<= 1;  
        // 合并两个块的Trie并重建fail指针  
    }  
    int Count(char *s) {  
        int ans = 0;  
        for (int i = 1; i <= N; i++)  
            ans += search(stk[i], s); // 遍历所有块查询  
        return ans;  
    }  
} Add, Sub;  
```

---

## 可视化方案（Canvas动画）  
```javascript  
// 伪代码：绘制二进制分块  
const colors = ["#FF6B6B", "#4ECDC4", "#45B7D1", "#96CEB4"];  
function drawBlocks() {  
    ctx.clearRect(0, 0, width, height);  
    for (let i = 0; i < blocks.length; i++) {  
        ctx.fillStyle = colors[Math.log2(blocks[i].size) % 4];  
        ctx.fillRect(x, y, 30 * blocks[i].size, 30);  
        ctx.strokeText(`2^${log2(blocks[i].size)}`, x + 5, y + 15);  
        x += 35 * blocks[i].size;  
    }  
}  
// 合并时播放8-bit音效  
function playMergeSound() {  
    const osc = new OscillatorNode(ctx, { frequency: 880 });  
    osc.connect(ctx.destination);  
    osc.start(); osc.stop(ctx.currentTime + 0.1);  
}  
```

---

## 个人心得摘录  
> “第一次写丑了，常数大…用了printf后要加fflush，否则WA到怀疑人生” —— super蒟蒻  
> **教训**：在线题目需及时刷新输出缓冲区，避免因缓存导致超时。  

---

## 总结  
本题通过二进制分组平衡动态操作与查询效率，核心在于分块策略与AC自动机的结合。可视化设计可直观展示分块合并与匹配过程，8-bit风格增强学习趣味性。

---
处理用时：73.82秒