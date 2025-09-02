# 题目信息

# Hamburgers

## 题目描述

Polycarpus loves hamburgers very much. He especially adores the hamburgers he makes with his own hands. Polycarpus thinks that there are only three decent ingredients to make hamburgers from: a bread, sausage and cheese. He writes down the recipe of his favorite "Le Hamburger de Polycarpus" as a string of letters 'B' (bread), 'S' (sausage) и 'C' (cheese). The ingredients in the recipe go from bottom to top, for example, recipe "ВSCBS" represents the hamburger where the ingredients go from bottom to top as bread, sausage, cheese, bread and sausage again.

Polycarpus has $ n_{b} $ pieces of bread, $ n_{s} $ pieces of sausage and $ n_{c} $ pieces of cheese in the kitchen. Besides, the shop nearby has all three ingredients, the prices are $ p_{b} $ rubles for a piece of bread, $ p_{s} $ for a piece of sausage and $ p_{c} $ for a piece of cheese.

Polycarpus has $ r $ rubles and he is ready to shop on them. What maximum number of hamburgers can he cook? You can assume that Polycarpus cannot break or slice any of the pieces of bread, sausage or cheese. Besides, the shop has an unlimited number of pieces of each ingredient.

## 样例 #1

### 输入

```
BBBSSC
6 4 1
1 2 3
4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
BBC
1 10 1
1 10 1
21
```

### 输出

```
7
```

## 样例 #3

### 输入

```
BSC
1 1 1
1 1 3
1000000000000
```

### 输出

```
200000000001
```

# AI分析结果



# Hamburgers 的题解分析与总结

## 题目重述

### 题目描述

Polycarpus 非常喜欢汉堡，尤其喜欢自己动手制作。他认为汉堡只能由三种食材组成：面包(B)、香肠(S)和奶酪(C)。他将最爱的汉堡配方记录为一个由 'B'、'S'、'C' 组成的字符串，字符串顺序表示食材从底到顶的堆叠顺序。例如，"BSCBS" 表示底部是面包，接着是香肠、奶酪、面包、香肠。

Polycarpus 现有 $n_b$ 个面包，$n_s$ 个香肠，$n_c$ 个奶酪。商店中三种食材单价分别为 $p_b$、$p_s$、$p_c$ 卢布。他手头有 $r$ 卢布，求最多能制作多少个汉堡。食材不可拆分，商店供应无限。

---

## 算法分类
**二分**

---

## 题解对比与关键思路

### 高分题解推荐

#### 1. 作者：tomhzl（★★★★★）
**核心思路**：二分答案 + 贪心验证  
- **验证函数**：计算制作 `mid` 个汉堡所需购买材料的费用是否在预算内。
- **实现亮点**：
  - 使用二分法高效确定最大汉堡数，时间复杂度 O(log(max_r))。
  - 清晰处理材料不足时的购买逻辑，用 `max` 函数避免负数。
- **代码片段**：
  ```cpp
  bool check(long long mid){
      long long n=0;
      if(mid*b>nb) n+=(mid*b-nb)*pb;
      if(mid*s>ns) n+=(mid*s-ns)*ps;
      if(mid*c>nc) n+=(mid*c-nc)*pc;
      return n<=money;
  }
  ```

#### 2. 作者：tallnut（★★★★★）
**核心思路**：标准二分模板 + 费用累加  
- **验证优化**：逐个检查材料需求，累加总费用时实时判断是否超支。
- **代码优势**：
  - 通过提前终止验证减少计算量。
  - 使用 `max` 确保不购买负数量材料。
- **代码片段**：
  ```cpp
  bool check(long long x){
      tmpmoney = money;
      for (int i=0; i<3; i++){
          if (tmpmoney < (max(cnt[i]*x -n[i],0)*p[i])) 
              return false;
          tmpmoney -= max(cnt[i]*x -n[i],0)*p[i];
      }
      return true;
  }
  ```

#### 3. 作者：封禁用户（★★★★☆）
**核心思路**：二分答案 + 特判材料需求  
- **特殊处理**：对材料需求为0的情况自动跳过计算。
- **代码亮点**：
  - 使用简洁的表达式 `max(0LL, ...)` 避免冗余判断。
  - 初始边界设为 `1e14`，覆盖大范围数据。
- **代码片段**：
  ```cpp
  bool check(long long x){
      long long sumb = max(0LL, b*x - yb);
      long long sums = max(0LL, s*x - ys);
      long long sumc = max(0LL, c*x - yc);
      return sumb*xb + sums*xs + sumc*xc <= n;
  }
  ```

---

## 关键技巧总结
1. **二分答案框架**：通过二分猜测可能的汉堡数量，验证函数计算可行性。
2. **贪心验证**：对每个材料独立计算需求，不足部分购买，总费用不超预算即合法。
3. **数据类型处理**：使用 `long long` 避免整数溢出，特别注意大数运算（如样例3的1e12）。
4. **边界条件处理**：对材料需求为0的情况单独处理，避免无效计算。

---

## 拓展与心得
- **调试经验**：灵光一闪的题解提到未使用 `long long` 导致错误，强调数据类型的重要性。
- **同类题目**：
  - [P2440 木材加工](https://www.luogu.com.cn/problem/P2440)：二分答案判断木材切割可行性。
  - [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：二分最小距离的最大值。
  - [P1182 数列分段](https://www.luogu.com.cn/problem/P1182)：二分最小化段最大值。

---

**推荐练习**：以上题目均涉及二分答案的核心思路，适合巩固此类问题的解法。

---
处理用时：53.72秒