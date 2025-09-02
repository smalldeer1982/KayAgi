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



---

**唯一算法分类**: AC自动机+二进制分组

---

### **综合分析与结论**

**核心思路**:  
1. **动态维护**：通过二进制分组将字符串集划分为多个块（每组大小为2的幂次），每个块维护独立的AC自动机  
2. **高效合并**：当插入新字符串导致相同大小的块存在时，合并块并重建AC自动机，保证每个字符串最多合并O(logn)次  
3. **删除处理**：维护两个独立的AC自动机集合（添加集和删除集），查询时取二者匹配结果之差  
4. **查询优化**：遍历所有块进行匹配，利用预处理的fail指针快速统计总出现次数  

**解决难点**:  
- **动态维护**：传统AC自动机无法处理频繁插入，二进制分组将整体重构复杂度摊平  
- **删除操作**：通过独立维护删除集的AC自动机，巧妙转化为可减性问题  
- **内存管理**：动态合并时需处理Trie节点复用，防止内存爆炸  

**可视化设计要点**:  
1. **合并动画**：用不同颜色方块表示不同分组的AC自动机块，合并时显示块大小翻倍过程  
2. **节点高亮**：查询时用流动光效标记当前遍历的Trie节点路径  
3. **音效反馈**：  
   - 插入/合并时播放"叮"声  
   - 匹配成功时短促"咔"声  
   - 查询结束播放8-bit风格胜利音  
4. **自动演示模式**：  
   - 展示二进制分组的合并过程（如插入第5个字符串时，显示1+4 → 5 → 1+1+4等状态变化）  
   - 用网格显示各块当前维护的字符串数量（2^k显示为二进制位）  

---

### **题解清单 (≥4星)**

1. **super蒟蒻（5星）**  
   - 亮点：完整实现二进制分组合并逻辑，结构清晰的AC自动机类封装  
   - 代码复用性高，独立处理插入/删除集合  
   ```cpp
   // 关键合并逻辑
   while (size[N] == size[N-1]) {
       --N, size[N] += size[N+1];
       rt[N] = merge(rt[N], rt[N+1]);
       build(rt[N]);
   }
   ```

2. **SDqwq（5星）**  
   - 亮点：精简的二进制分组实现，动态节点管理  
   - 使用vector维护不同分组的自动机  
   ```cpp
   void upd(char *s) {
       rt[++pr] = ++idx;
       insert(s, rt[pr]);
       while (sz[pr] == sz[pr-1]) 
           sz[--pr] <<= 1, merge(rt[pr], rt[pr+1]);
   }
   ```

3. **FelFa_1414666（4星）**  
   - 亮点：提供多种解法对比，包含哈希/KMP/AC自动机的实现  
   - 实用调试经验：强调双哈希避免冲突的重要性  

---

### **核心代码实现**

**二进制分组合并核心**：
```cpp
struct ACAM {
    int rt[30], sz[30], cnt; // 维护最多log个块
    
    void insert(string s) {
        rt[++cnt] = new_node();
        sz[cnt] = 1;
        build_trie(rt[cnt], s);
        while (sz[cnt] == sz[cnt-1]) { // 合并相同大小块
            sz[--cnt] *= 2;
            rt[cnt] = merge(rt[cnt], rt[cnt+1]);
            build_fail(rt[cnt]);
        }
    }
    
    int query(string s) {
        int res = 0;
        for(int i=1; i<=cnt; i++) 
            res += ac_query(rt[i], s);
        return res;
    }
};
```

**AC自动机合并**：
```cpp
int merge(int x, int y) {
    if(!x || !y) return x|y;
    end[x] += end[y];
    for(int i=0; i<26; i++)
        tr[x][i] = merge(tr[x][i], tr[y][i]);
    return x;
}
```

---

### **同类型题推荐**
1. **P5357** 【模板】AC自动机（二次加强版）  
2. **P3966** [TJOI2013]单词  
3. **P2414** [NOI2011]阿狸的打字机  

---

### **可视化演示示例**
```javascript
// 伪代码示例：Canvas绘制二进制分组状态
function drawBlocks() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    let x = 10;
    for (let i=0; i<blocks.length; i++) {
        const size = Math.log2(blocks[i].size);
        ctx.fillStyle = hsl(30*size, 70%, 50%); // 按块大小渐变颜色
        ctx.fillRect(x, 100, 40, 40);
        ctx.fillText(`2^${size}`, x+5, 140);
        x += 50;
    }
}

// 合并动画
function animateMerge(block1, block2) {
    block1.size *= 2;
    playSound('merge.wav');
    block2.visible = false;
    addParticleEffect(block1.position); // 粒子特效
}
```

---

### **总结**
通过二进制分组将动态维护的复杂度优化至O(logn)，结合AC自动机的高效多模式匹配，完美解决动态字符串集合的维护问题。关键点在于理解分块合并策略和fail指针的增量构建。此方法可扩展至其他需要动态维护数据结构的场景。

---
处理用时：66.78秒