# 题目信息

# After Training

## 题目描述

After a team finished their training session on Euro football championship, Valeric was commissioned to gather the balls and sort them into baskets. Overall the stadium has $ n $ balls and $ m $ baskets. The baskets are positioned in a row from left to right and they are numbered with numbers from $ 1 $ to $ m $ , correspondingly. The balls are numbered with numbers from $ 1 $ to $ n $ .

Valeric decided to sort the balls in the order of increasing of their numbers by the following scheme. He will put each new ball in the basket with the least number of balls. And if he's got several variants, he chooses the basket which stands closer to the middle. That means that he chooses the basket for which ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF195B/a806f5bf21bc9e79268695bcfcf77ba78839a96f.png) is minimum, where $ i $ is the number of the basket. If in this case Valeric still has multiple variants, he chooses the basket with the minimum number.

For every ball print the number of the basket where it will go according to Valeric's scheme.

Note that the balls are sorted into baskets in the order of increasing numbers, that is, the first ball goes first, then goes the second ball and so on.

## 样例 #1

### 输入

```
4 3
```

### 输出

```
2
1
3
2
```

## 样例 #2

### 输入

```
3 1
```

### 输出

```
1
1
1
```

# AI分析结果



# 题目翻译

## 题目描述

Valeric 在球队结束欧洲足球锦标赛的训练后，被委派去收集球并将它们分装到篮子中。体育场共有 $n$ 个球和 $m$ 个篮子，篮子从左到右排成一行，编号为 $1$ 到 $m$。球的编号为 $1$ 到 $n$。

Valeric 决定按以下规则将球按编号递增顺序放入篮子：每个新球放入当前球数最少的篮子。若有多个候选篮子，选择最靠近中间的篮子（即最小化 $|i - \frac{m+1}{2}|$ 的篮子）。若仍有多个选项，选择编号最小的。

请输出每个球最终放入的篮子编号。

## 样例 #1

### 输入
```
4 3
```

### 输出
```
2
1
3
2
```

## 样例 #2

### 输入
```
3 1
```

### 输出
```
1
1
1
```

---

**算法分类**：贪心、构造

---

**题解分析与结论**  
各题解核心思路一致：通过对称性构造放置顺序。最优解法利用数学规律直接计算每个球的位置，无需模拟，时间复杂度 $O(n)$。关键步骤如下：

1. **中间起点**：初始位置为中间篮子 $(m+1)/2$（向下取整）。
2. **左右对称放置**：每次交替选择左右对称位置，形成 `中间 → 左 → 右 → 左 → 右` 的循环。
3. **边界重置**：当放置到最右侧时，重置到中间开始新一轮循环。

---

**精选题解**

1. **题解作者：sxq9（★★★★★）**  
   **关键亮点**：代码简洁，统一处理奇偶情况，利用对称公式直接计算下一个位置。  
   **核心代码**：
   ```cpp
   double mid = (m + 1) * 1.0 / 2;
   int pos = mid;
   for (int i = 1; i <= n; i++) {
       cout << pos << endl;
       if (pos == m) pos = mid;    // 重置到中间
       else if (pos < mid) pos = m - pos + 1; // 左→右
       else pos = m - pos;          // 右→左
   }
   ```
   **代码思想**：通过 `pos` 的对称变换实现左右交替，`pos == m` 时重置为中间。

2. **题解作者：XXh0919（★★★★☆）**  
   **关键亮点**：逻辑清晰，通过判断当前位置与中间的关系切换方向。  
   **个人心得**：强调中间位置的统一处理，通过画图辅助理解对称性。

3. **题解作者：foryou_（★★★★☆）**  
   **关键亮点**：结论式推导，明确优先级处理规则，代码简洁。  
   **核心公式**：左侧对称位置为 $m - pos + 1$，右侧为 $m - pos$。

---

**最优思路总结**  
1. **中间基准点**：计算中间位置 $(m+1)/2$，统一处理奇偶。
2. **对称交替放置**：用数学公式计算下一个位置，避免模拟。
3. **边界处理**：到达最右端时重置，维持循环。

---

**拓展建议**  
- **同类问题**：考察对称构造的题目如循环填充、交替排列等。
- **思维训练**：将复杂规则转化为数学规律，培养观察周期性或对称性的能力。

---

**推荐题目**  
1. [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)（构造与对称处理）
2. [P1327 数列排序](https://www.luogu.com.cn/problem/P1327)（周期性排列）
3. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)（贪心策略与对称移动）

---
处理用时：128.17秒