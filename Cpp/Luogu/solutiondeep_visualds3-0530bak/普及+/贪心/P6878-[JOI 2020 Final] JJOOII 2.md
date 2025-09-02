# 题目信息

# [JOI 2020 Final] JJOOII 2

## 题目描述

定义有连续 $K$ 个 $\tt J$ 和连续 $K$ 个 $\tt O$ 和连续 $K$ 个 $\tt I$ 组成的字符串为 $K$ 阶 JOI 串。

比如，$\tt JJOOII$ 为 $2$ 阶 JOI 串，**但是，注意要有顺序**，比如 $\tt OOJJII$ 就不是 $2$ 阶 JOI 串。

现在，给定一个长度为 $N$ 的字符串 $S$，可以对他进行 $3$ 种操作：

- 操作 $1$：删除 $S$ 开头的字符
- 操作 $2$：删除 $S$ 结尾的字符
- 操作 $3$：删除 $S$ 除了开头和结尾之外的一个字符

我们要通过这些操作让 $S$ 变为 $K$ 阶 JOI 串。

但是，我们想让操作 $3$ 尽量的少。

所以我们想知道，变为 $K$ 阶 JOI 串操作 $3$ 最少需要进行多少次？

如果不能变为 $K$ 阶 JOI 串，那么输出 $-1$。

## 说明/提示

#### 样例 1 解释

1. 进行一次操作 $1$，变为 $\tt JIJOIOIIJ$。
2. 进行一次操作 $2$，变为 $\tt JIJOIOII$。
3. 进行一次操作 $3$，删掉字符 $2$，变为 $\tt JJOIOII$。
4. 进行一次操作 $3$，删掉字符 $4$，变为 $\tt JJOOII$。

#### 样例 2 解释

$\tt JJJOOOIII$ 已经是 $3$ 阶 JOI 串了，所以不需要进行操作。

#### 样例 3 解释

$\tt IIIOOOJJJ$ 无法变为 $1$ 阶 JOI 串，无解。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（1 pts）：$N \le 21$。
- Subtask 2（12 pts）：$N \le 3000$。
- Subtask 3（87 pts）：无特殊限制。

对于 $100\%$ 的数据：

- $3 \le N \le 2 \times 10^5$。
- $1 \le K \le \dfrac{N}{3}$。
- $S$ 只包含 $\tt J$，$\tt O$，$\tt I$ 且长度为 $N$。

#### 说明

翻译自 [第19回日本情報オリンピック　本選](https://www.ioi-jp.org/joi/2019/2020-ho/index.html) [B JJOOII 2](https://www.ioi-jp.org/joi/2019/2020-ho/2020-ho-t2.pdf)。

## 样例 #1

### 输入

```
10 2
OJIJOIOIIJ```

### 输出

```
2```

## 样例 #2

### 输入

```
9 3
JJJOOOIII
```

### 输出

```
0```

## 样例 #3

### 输入

```
9 1
IIIOOOJJJ
```

### 输出

```
-1```

# AI分析结果



### 综合分析与结论

#### 核心算法与难点
1. **核心思路**：寻找满足顺序的连续 K 个 J/O/I 的最小区间，计算区间总长度与 3K 的差值（即操作3次数）。
2. **算法要点**：
   - 预处理字符位置数组（J/O/I 的位置列表）
   - 三指针法：遍历 J 的起始位置，在 O/I 数组中寻找满足条件的最小区间
   - 时间复杂度 O(n)（三指针）或 O(n log n)（二分）
3. **解决难点**：
   - **顺序性约束**：必须严格先 J 后 O 最后 I
   - **高效定位**：通过指针单调性避免重复遍历（三指针）或二分快速跳跃
   - **边界处理**：当某字符数量不足 K 时及时终止

#### 贪心策略详解
- **贪心选择依据**：对于每个 J 的起始位置，选择最近的 K 个 J 和后续最近的 K 个 O/I，保证整体区间最短。
- **数据结构**：预存 J/O/I 的位置数组，通过下标直接访问第 i+K-1 个元素。
- **优化证明**：更晚的 J 起始点对应的 O/I 起始点必然不早于之前的解，因此指针只需单向移动。

---

### 题解清单（≥4星）

#### 1. NewJeanss（5★）
- **亮点**：最优时间复杂度 O(n)，三指针法实现简洁，预处理数组直接定位区间
- **关键代码**：
  ```cpp
  for(int i=1;i<=cj;i++){
      if(i+k-1>cj) break;
      end=cntj[i+k-1];
      while(cnto[lo]<=end && lo<=co) lo++;
      if(lo+k-1>co) break;
      end=cnto[lo+k-1];
      while(cnti[li]<=end && li<=ci) li++;
      ans=min(ans,cnti[li+k-1]-cntj[i]+1-3*k);
  }
  ```

#### 2. Daniel_7216（4★）
- **亮点**：代码简洁，利用 lower_bound 实现二分查找
- **优化点**：通过前缀和快速计算区间字符数量
- **关键片段**：
  ```cpp
  int a = lower_bound(sumn + i, sumn + n+1, sumn[i-1]+k) - sumn;
  int b = lower_bound(sumo + a, sumo + n+1, sumo[a-1]+k) - sumo;
  int c = lower_bound(sumi + b, sumi + n+1, sumi[b-1]+k) - sumi;
  ```

#### 3. __Watcher（4★）
- **亮点**：维护指针单调性，通过预处理数组直接访问元素
- **创新点**：使用指针数组而非二分，实现更高效的单向扫描

---

### 最优思路提炼

#### 关键步骤
1. **预处理**：分别存储 J/O/I 的所有出现位置到独立数组
2. **遍历 J 段**：对每个可能的 J 段起始点 i，取 j_end = J[i+K-1]
3. **定位 O 段**：从 j_end 之后找到第一个满足 O 数量≥K 的区间
4. **定位 I 段**：从 o_end 之后找到第一个满足 I 数量≥K 的区间
5. **计算代价**：总区间长度 - 3K 即为操作3次数

#### 核心代码实现
```cpp
vector<int> J, O, I;
// 预处理填充 J/O/I 的位置数组
int ans = INF;
int o_ptr = 0, i_ptr = 0;
for (int j=0; j+K<=J.size(); ++j) {
    int j_end = J[j+K-1];
    // 更新 O 指针至第一个在 j_end 后的 O
    while (o_ptr < O.size() && O[o_ptr] <= j_end) o_ptr++;
    if (o_ptr+K > O.size()) break;
    int o_end = O[o_ptr+K-1];
    // 更新 I 指针至第一个在 o_end 后的 I 
    while (i_ptr < I.size() && I[i_ptr] <= o_end) i_ptr++;
    if (i_ptr+K > I.size()) break;
    int i_end = I[i_ptr+K-1];
    ans = min(ans, i_end - J[j] + 1 - 3*K);
}
```

---

### 同类型题目推荐

1. **P1638 滑动窗口**  
   （字符串中连续区间统计，类似滑动窗口思想）

2. **P1496 火烧赤壁**  
   （区间覆盖问题，贪心选择最早结束区间）

3. **P3143 [USACO16OPEN] Diamond Collector**  
   （双指针法寻找最大连续子序列）

---

### 可视化设计：复古像素风格贪心演示

#### 动画设计
1. **像素网格**：  
   - 每个字符显示为 16x16 像素块（J: 蓝色，O: 黄色，I: 绿色）
   - 当前处理的 J/O/I 段高亮显示（闪烁边框）

2. **指针标记**：  
   - 红色箭头表示当前 J 的起始位置
   - 黄色箭头跟踪 O 段指针，绿色箭头跟踪 I 段指针

3. **操作提示**：  
   - 成功找到 K 个字符时播放 8-bit 音效
   - 区间合并时显示爆炸粒子特效

#### 交互功能
```javascript
// 伪代码示例
class PixelAnimator {
  constructor(chars) {
    this.canvas = document.getElementById('pixel-canvas');
    this.jPositions = getJPositions(chars);
    // 初始化指针状态...
  }
  
  nextStep() {
    if (this.state === 'J') {
      this.highlightJBlock();
      playSound('blip');
    } else if (this.state === 'O') {
      this.moveOArrow();
      playSound('success');
    }
    // 更新动画状态...
  }
}
```

#### 音效设计
- **blip.wav**：每次指针移动时播放（短促电子音）
- **success.wav**：找到完整 K 段时播放（上升音阶）
- **error.wav**：无法找到时播放（低沉嗡鸣声）

---

### 个人心得摘录

1. **指针单调性**（NewJeanss）：  
   "注意 lo 和 li 不用每次从 1 开始，位置是单调递增的"  
   → 利用处理顺序保证指针只需单向移动，极大优化时间复杂度

2. **边界处理教训**（zsyzsy_2012）：  
   二分时需严格判断 `sum[mid] - sum[start] >= k`，初始代码因未处理等号导致 WA

3. **贪心验证**（djh0314）：  
   "不会在中间删除同样的字符，否则可以保留这一字符"  
   → 证明选择最小区间的正确性

---

通过上述分析与可视化设计，学习者可深入理解如何通过预处理与指针技巧高效解决顺序区间选择问题，并在交互式动画中直观感受贪心策略的决策过程。

---
处理用时：76.10秒