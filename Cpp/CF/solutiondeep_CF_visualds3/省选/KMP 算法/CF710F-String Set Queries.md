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


### 💡 Kay的C++算法解析：String Set Queries 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`AC自动机 + 二进制分组`  
🗣️ **初步分析**：
> 本题需要动态维护字符串集合并高效处理模式匹配查询。核心思想是将**AC自动机**与**二进制分组**技术结合，解决动态更新问题。想象AC自动机是高效匹配的流水线，二进制分组则是模块化管理的仓库系统——每次新增字符串就像添加新模块，当模块大小相即时自动合并（类似2048游戏），保证整体结构高效。

- **题解思路**：主流解法采用两个AC自动机（插入组和删除组），利用二进制分组管理动态操作。插入/删除时创建新组并递归合并相同大小的组，查询时在两个自动机中分别匹配并求差。
- **核心难点**：动态维护AC自动机的fail指针。二进制分组确保每个字符串最多重构O(log n)次，总复杂度O(L log n)。
- **可视化设计**：采用8位像素风格展示分组合并过程（如模块碰撞合并动画），关键变量（组大小、fail指针）实时高亮，合并时播放"叮"音效，查询时显示扫描进度条。

---

#### 2. 精选优质题解参考
**题解一：二进制分组AC自动机（super蒟蒻）**  
* **点评**：思路清晰（插入/删除独立分组，查询作差），代码规范（分离`tr`和`ch`数组避免重构冲突），算法高效（每组独立fail指针）。亮点在于**双数组设计**解决合并后fail更新问题，实践价值高（可直接用于竞赛）。  
  > 作者心得：注意`fflush(stdout)`防止输出延迟

**题解二：二进制分组优化（SDqwq）**  
* **点评**：代码简洁（单AC自动机结构体封装），内存优化（动态开点），关键创新在`sum`数组预处理fail路径权值和，避免查询时跳转fail链。学习其**空间复用技巧**（del数组回收节点）。

**题解三：哈希+根号分治（FelFa_1414666）**  
* **点评**：独特的分治策略（短串用trie，长串用KMP），适合卡常场景。亮点在**长度阈值设计**（|s|≤1000用trie）平衡复杂度，但理论复杂度O(L√L)稍逊。

---

### 3. 核心难点辨析与解题策略
1. **动态维护fail指针**  
   *分析*：传统AC自动机每次插入需重构fail，二进制分组将总重构次数降至O(n log n)。  
   💡 *学习笔记*：分组大小保持2的幂次，合并时递归合并字典树后重建fail。

2. **删除操作的处理**  
   *分析*：删除视为负权值插入独立分组，查询作差。注意**权值传播**（合并时`val[x] += val[y]`）。  
   💡 *学习笔记*：利用可减性将删除转化为负插入。

3. **查询效率优化**  
   *分析*：预处理`sum[i]`（fail树路径权值和），查询时免跳fail链。  
   💡 *学习笔记*：`sum[u] = val[u] + sum[fail[u]]`的设计是O(1)查询关键。

✨ **解题技巧总结**：
- **分组合并技巧**：合并后立即重建fail，保持组间独立
- **内存回收**：`del`栈回收废弃节点防MLE
- **边界处理**：空组标记`rt[0]=0`，避免非法访问

---

### 4. C++核心代码实现赏析
**通用核心实现（综合优化版）**：
```cpp
struct ACAM {
    int tot, top, rt[20], siz[20]; // 二进制分组管理
    int ch[N][26], tr[N][26];      // ch存树结构，tr存fail转移
    int fail[N], val[N], sum[N];   // sum预处理路径权值和

    void build(int root) { /* BFS构建fail树 */ }
    int merge(int x, int y) { /* 递归合并字典树 */ }
    void insert(char *s) { /* 分组插入与合并 */ }
    int query(char *s) { /* 遍历各组累计匹配值 */ }
} A, B; // A:插入组, B:删除组
```
**代码解读概要**：  
- **分组管理**：`rt/siz`数组维护当前组，`top`为组数
- **双数组设计**：`ch`用于建树，`tr`用于查询（避免合并污染）
- **高效查询**：`sum`数组实现O(1)权值累加

---

### 5. 算法可视化：像素动画演示
🎮 **主题**：8位像素风"AC自动机工厂"  
**核心演示流程**：
1. **初始化**：16色调色板，网格化显示字典树（节点=像素方块）
   - 控制面板：开始/暂停/单步/速度滑块
   - 背景音乐：FC风格BGM循环

2. **插入动画**：
   - 新字符串→黄色方块沿路径点亮
   - 组大小碰撞：相同大小组→红色闪烁→合并动画（像素方块聚合）
   - 音效：合并"叮"，失败"噗"

3. **查询过程**：
   - 文本串字符逐个输入→绿色扫描线
   - 自动机状态变化：当前节点高亮闪烁
   - 实时显示：`sum`累计值（右上角数字跳动）

4. **教学模式**：
   - 按空格单步执行，显示当前逻辑代码行
   - 旁白框："正在合并组大小4+4→8"、"fail指针指向父节点"

---

### 6. 拓展练习与相似问题
**技巧迁移场景**：
1. 动态图连通性（分组+并查集）
2. 在线区间查询（二进制分组+线段树）

**洛谷推荐**：
1. [P5357 AC自动机（二次加强版）](https://www.luogu.com.cn/problem/P5357)  
   → 巩固AC自动机模板
2. [P4219 动态树LCT](https://www.luogu.com.cn/problem/P4219)  
   → 练习二进制分组维护树结构
3. [P3396 哈希冲突](https://www.luogu.com.cn/problem/P3396)  
   → 根号分治思维拓展

---

### 7. 学习心得与经验分享
> **来自super蒟蒻的调试经验**："合并后忘记重建fail指针导致查询错误，建议在`build()`后立即验证简单案例"  
> **Kay总结**：二进制分组的关键在于**及时合并与隔离重构**，调试时可打印分组状态图。

---

通过本指南，希望大家掌握动态字符串处理的利器——二进制分组AC自动机！下次挑战见！🚀

---
处理用时：101.37秒