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



### 算法分类
AC自动机 + 二进制分组

---

### 题解思路与算法要点

#### 核心思路对比
1. **二进制分组+AC自动机**（主流解法）
   - 将插入和删除的字符串分别维护多个AC自动机组
   - 每个组的大小为2的幂次，合并时像二进制加法进位
   - 查询时遍历所有AC自动机组计算结果之和
   - 时间复杂度：插入O(∑|s|logm)，查询O(∑|s|logm)

2. **哈希+分块处理**
   - 按字符串长度分块，维护哈希集合
   - 查询时只检查集合中存在长度的子串
   - 时间复杂度：O(m√m logm)，适用于短字符串场景

3. **根号分治**
   - 短字符串用Trie树，长字符串用KMP单独处理
   - 平衡插入和查询的时间复杂度

#### 解决难点
- **动态维护AC自动机**：通过二进制分组限制重构次数，每个字符串最多被合并logm次
- **删除操作处理**：维护两个独立的AC自动机集合（插入和删除），查询结果相减
- **合并优化**：使用独立trie图（`tr[][]`）避免破坏原有结构，确保合并后正确构建fail指针

---

### 高分题解推荐（≥4★）

1. **super蒟蒻（4.5★）**
   - 亮点：完整实现二进制分组逻辑，支持插入和删除的独立分组
   - 关键代码：使用`merge()`合并Trie树，`getfail()`重构fail指针
   ```cpp
   void merge() {
       --N, size[N] <<= 1;
       // 清空原有结构并合并
       for(int L=fr[N]; L<=n; L++) insert(stk[N], data[L]);
       build(stk[N]);
   }
   ```

2. **SDqwq（4.2★）**
   - 亮点：代码简洁，动态维护多个AC自动机
   - 关键代码：二进制分组合并逻辑
   ```cpp
   while(siz[top] == siz[top-1]) {
       siz[--top] <<= 1;
       rt[top] = merge(rt[top], rt[top+1]);
   }
   ```

3. **tzc_wk（4.0★）**
   - 亮点：根号分治结合KMP，适用于特殊长度分布场景
   - 关键代码：短字符串插入Trie，长字符串单独KMP
   ```cpp
   if(len <= 1000) trie.insert(str, val);
   else lib[cnt] = string(str), cntx[cnt++] = val;
   ```

---

### 最优思路提炼

1. **二进制分组技巧**
   - 每个组维护独立AC自动机，合并时重构时间复杂度可控
   - 插入新字符串时创建新组，合并相邻相同大小的组（类似2048合并）

2. **双AC自动机处理删除**
   - 插入组(`Add`)和删除组(`Sub`)独立维护
   - 查询结果为`Add.query(s) - Sub.query(s)`

3. **Trie图优化**
   - 分离trie结构(`ch[][]`)和转移图(`tr[][]`)
   - 合并时保留原始trie结构，避免破坏已有fail指针

---

### 同类题目推荐
1. [P5357 【模板】AC自动机（二次加强版）](https://www.luogu.com.cn/problem/P5357)
2. [P3960 列队（块状链表思想）](https://www.luogu.com.cn/problem/P3960)
3. [CF817F MEX Queries（动态集合维护）](https://codeforces.com/problemset/problem/817/F)

---

### 可视化设计（AC自动机合并）

#### 动画演示
1. **插入过程**：
   - 新字符串生成独立Trie树（红色高亮）
   - 检测相邻组大小相同则合并（黄色闪烁提示）
   - 合并后重构fail指针（蓝色连线动态生成）

2. **查询过程**：
   - 输入字符串逐个字符流动展示
   - 不同AC自动机组并行匹配（不同颜色背景）
   - 实时统计各组的匹配次数并累加

#### 复古像素风格
```javascript
// Canvas绘制示例（伪代码）
function drawNode(x, y, val) {
    ctx.fillStyle = '#8B8BEF'; // 紫色节点
    ctx.fillRect(x*40, y*60, 30, 30);
    ctx.fillStyle = '#FFFFFF';
    ctx.fillText(val, x*40+10, y*60+20);
}

// 音效触发
function playMergeSound() {
    const beep = new Audio('data:audio/wav;base64,UklGRl9...');
    beep.play(); // 合并时播放8bit音效
}
```

---

### 核心代码实现
```cpp
struct ACAM {
    int tot, rt[20], siz[20], cnt;
    int ch[N][26], tr[N][26], fail[N], sum[N];
    
    void insert(char *s) {
        rt[++cnt] = ++tot;
        int u = rt[cnt];
        for (int i=0; s[i]; i++) {
            int c = s[i]-'a';
            if (!ch[u][c]) ch[u][c] = ++tot;
            u = ch[u][c];
        }
        sum[u]++;
        while (cnt>1 && siz[cnt]==siz[cnt-1]) {
            merge(rt[cnt-1], rt[cnt]);
            siz[cnt-1] *= 2;
            cnt--;
        }
        build(rt[cnt]);
    }
    
    int query(char *s) {
        int res = 0;
        for (int i=1; i<=cnt; i++) {
            int u = rt[i];
            for (int j=0; s[j]; j++) {
                u = tr[u][s[j]-'a'];
                res += sum[u];
            }
        }
        return res;
    }
} Add, Del;

// 主函数查询
printf("%d\n", Add.query(s) - Del.query(s));
```

该代码完整展示了二进制分组的插入和查询逻辑，通过维护多个AC自动机组实现高效动态更新。

---
处理用时：72.29秒