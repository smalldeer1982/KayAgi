# 题目信息

# MUH and Sticks

## 题目描述

Two polar bears Menshykov and Uslada from the St.Petersburg zoo and elephant Horace from the Kiev zoo got six sticks to play with and assess the animals' creativity. Menshykov, Uslada and Horace decided to make either an elephant or a bear from those sticks. They can make an animal from sticks in the following way:

- Four sticks represent the animal's legs, these sticks should have the same length.
- Two remaining sticks represent the animal's head and body. The bear's head stick must be shorter than the body stick. The elephant, however, has a long trunk, so his head stick must be as long as the body stick. Note that there are no limits on the relations between the leg sticks and the head and body sticks.

Your task is to find out which animal can be made from the given stick set. The zoo keeper wants the sticks back after the game, so they must never be broken, even bears understand it.

## 说明/提示

If you're out of creative ideas, see instructions below which show how to make a bear and an elephant in the first two samples. The stick of length 2 is in red, the sticks of length 4 are in green, the sticks of length 5 are in blue.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF471A/a55b02778d08bde8867cd5aaa95268e697371d67.png)

## 样例 #1

### 输入

```
4 2 5 4 4 4
```

### 输出

```
Bear```

## 样例 #2

### 输入

```
4 4 5 4 4 5
```

### 输出

```
Elephant```

## 样例 #3

### 输入

```
1 2 3 4 5 6
```

### 输出

```
Alien```

# AI分析结果



### 题目内容
# MUH and Sticks

## 题目描述

两只北极熊Menshykov、Uslada和大象Horace拿到了六根木棍，他们要用这些木棍拼成熊或大象。规则如下：

- 四根长度相同的木棍作为动物的腿。
- 剩余两根木棍中，熊的头部木棍必须比身体木棍短；大象的头部和身体木棍必须等长。

请根据给定的六根木棍长度，判断能拼成的动物类型，或输出无法完成（Alien）。

### 样例
#### 输入 #1
```
4 2 5 4 4 4
```
#### 输出 #1
```
Bear
```
#### 输入 #2
```
4 4 5 4 4 5
```
#### 输出 #2
```
Elephant
```

---

### 算法分类
**模拟**

---

### 题解分析与关键思路
#### 核心思路
1. **排序后分组判断**：将木棍排序后，寻找四个连续相同长度的木棍作为腿。
2. **剩余木棍处理**：将四根腿木棍标记后，重新排序剩余木棍，判断头部和身体的关系。
3. **覆盖所有分组情况**：处理四根腿可能出现在前、中、后三种位置，确保剩余两根木棍的正确性判断。

#### 最优题解亮点
1. **zeekliu的解法（4星）**
   - **关键思路**：直接判断四根腿的位置（前四/中间四/后四），剩余两根根据分组位置判断。
   - **代码简洁性**：通过三种条件分支覆盖所有可能情况，逻辑清晰。
   ```cpp
   sort(a+1,a+7);
   if (a[1]==a[4] && a[5]!=a[6] || ...其他情况) cout<<"Bear";
   else if (前四腿且剩余相等 || 后四腿且剩余相等) cout<<"Elephant";
   ```

2. **Arghariza的解法（4星）**
   - **标记法优化**：将四根腿木棍置零后重新排序，剩余木棍自动排列到数组前端。
   - **代码实现**：
   ```cpp
   sort(s+1, s+n+1);
   for (遍历找四连相同数) { 标记为0 }
   sort(剩余木棍);
   if (s[1]==s[2]) 输出Elephant;
   ```

3. **fzj2007的解法（4星）**
   - **分组条件覆盖**：通过三个条件判断四根腿的位置，剩余木棍的分布情况。
   - **边界处理**：正确处理五根或六根相同木棍的特殊情况。

---

### 关键技巧总结
1. **排序预处理**：通过排序简化分组判断。
2. **标记法处理剩余元素**：置零或重新排序可快速分离剩余元素。
3. **条件分支全覆盖**：明确四根腿的可能位置，分类讨论剩余元素关系。

---

### 相似题目推荐
1. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)（排序与去重）
2. [P1781 宇宙总统](https://www.luogu.com.cn/problem/P1781)（统计最大值）
3. [P1152 欢乐的跳](https://www.luogu.com.cn/problem/P1152)（相邻差值覆盖判断）

---
处理用时：246.21秒