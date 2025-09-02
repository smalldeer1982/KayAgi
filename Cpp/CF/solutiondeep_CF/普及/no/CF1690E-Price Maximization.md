# 题目信息

# Price Maximization

## 题目描述

A batch of $ n $ goods ( $ n $ — an even number) is brought to the store, $ i $ -th of which has weight $ a_i $ . Before selling the goods, they must be packed into packages. After packing, the following will be done:

- There will be $ \frac{n}{2} $ packages, each package contains exactly two goods;
- The weight of the package that contains goods with indices $ i $ and $ j $ ( $ 1 \le i, j \le n $ ) is $ a_i + a_j $ .

With this, the cost of a package of weight $ x $ is always $ \left \lfloor\frac{x}{k}\right\rfloor $ burles (rounded down), where $ k $ — a fixed and given value.

Pack the goods to the packages so that the revenue from their sale is maximized. In other words, make such $ \frac{n}{2} $ pairs of given goods that the sum of the values $ \left \lfloor\frac{x_i}{k} \right \rfloor $ , where $ x_i $ is the weight of the package number $ i $ ( $ 1 \le i \le \frac{n}{2} $ ), is maximal.

For example, let $ n = 6, k = 3 $ , weights of goods $ a = [3, 2, 7, 1, 4, 8] $ . Let's pack them into the following packages.

- In the first package we will put the third and sixth goods. Its weight will be $ a_3 + a_6 = 7 + 8 = 15 $ . The cost of the package will be $ \left \lfloor\frac{15}{3}\right\rfloor = 5 $ burles.
- In the second package put the first and fifth goods, the weight is $ a_1 + a_5 = 3 + 4 = 7 $ . The cost of the package is $ \left \lfloor\frac{7}{3}\right\rfloor = 2 $ burles.
- In the third package put the second and fourth goods, the weight is $ a_2 + a_4 = 2 + 1 = 3 $ . The cost of the package is $ \left \lfloor\frac{3}{3}\right\rfloor = 1 $ burle.

With this packing, the total cost of all packs would be $ 5 + 2 + 1 = 8 $ burles.

## 说明/提示

The first test case is analyzed in the statement.

In the second test case, you can get a total value equal to $ 4 $ if you put the first and second goods in the first package and the third and fourth goods in the second package.

In the third test case, the cost of each item is $ 0 $ , so the total cost will also be $ 0 $ .

## 样例 #1

### 输入

```
6
6 3
3 2 7 1 4 8
4 3
2 1 5 6
4 12
0 0 0 0
2 1
1 1
6 10
2 0 0 5 9 4
6 5
5 3 8 6 3 2```

### 输出

```
8
4
0
2
1
5```

# AI分析结果

### 题目内容重写
# 价格最大化

## 题目描述

一批 $ n $ 个商品（$ n $ 为偶数）被带到商店，第 $ i $ 个商品的重量为 $ a_i $。在出售之前，这些商品需要被打包成包裹。打包后，将进行以下操作：

- 会有 $ \frac{n}{2} $ 个包裹，每个包裹包含恰好两个商品；
- 包含索引为 $ i $ 和 $ j $（$ 1 \le i, j \le n $）的包裹的重量为 $ a_i + a_j $。

在这种情况下，重量为 $ x $ 的包裹的成本始终为 $ \left \lfloor\frac{x}{k}\right\rfloor $ burles（向下取整），其中 $ k $ 是一个固定的给定值。

将商品打包成包裹，使得它们的销售收入最大化。换句话说，将给定的商品分成 $ \frac{n}{2} $ 对，使得每对包裹的重量 $ x_i $ 的 $ \left \lfloor\frac{x_i}{k} \right \rfloor $ 之和最大。

例如，设 $ n = 6, k = 3 $，商品的重量为 $ a = [3, 2, 7, 1, 4, 8] $。我们将它们打包成以下包裹。

- 第一个包裹包含第三个和第六个商品。它的重量为 $ a_3 + a_6 = 7 + 8 = 15 $。该包裹的成本为 $ \left \lfloor\frac{15}{3}\right\rfloor = 5 $ burles。
- 第二个包裹包含第一个和第五个商品，重量为 $ a_1 + a_5 = 3 + 4 = 7 $。该包裹的成本为 $ \left \lfloor\frac{7}{3}\right\rfloor = 2 $ burles。
- 第三个包裹包含第二个和第四个商品，重量为 $ a_2 + a_4 = 2 + 1 = 3 $。该包裹的成本为 $ \left \lfloor\frac{3}{3}\right\rfloor = 1 $ burle。

通过这种打包方式，所有包裹的总成本为 $ 5 + 2 + 1 = 8 $ burles。

## 说明/提示

第一个测试用例在题目描述中已经分析。

在第二个测试用例中，如果将第一个和第二个商品放入第一个包裹，第三个和第四个商品放入第二个包裹，则总价值为 $ 4 $。

在第三个测试用例中，每个商品的价值为 $ 0 $，因此总价值也为 $ 0 $。

### 算法分类
贪心

### 题解分析与结论
各题解的核心思路基本一致，即通过贪心算法最大化包裹的价值。具体步骤如下：
1. 将每个商品的重量除以 $k$ 的商累加到答案中。
2. 将每个商品的重量对 $k$ 取模，得到余数数组。
3. 对余数数组进行排序，使用双指针法将余数尽可能多地组合成大于等于 $k$ 的对，每成功组合一对，答案加一。

### 所选高星题解
#### 题解作者：strange757 (赞：12)
- **星级**：5星
- **关键亮点**：思路清晰，代码简洁，使用了双指针法优化了组合过程。
- **核心代码**：
  ```cpp
  sort(b + 1, b + 1 + n);
  int l = 1, r = n;
  while(l < r){
      while(b[l] + b[r] < k) l++;
      if(b[l] + b[r] >= k && l < r) ans++, l++, r--;
      else break;
  }
  ```

#### 题解作者：fuxuantong123 (赞：6)
- **星级**：4星
- **关键亮点**：详细解释了贪心策略，代码结构清晰。
- **核心代码**：
  ```cpp
  sort(mod + 1, mod + n + 1);
  int l = 1, r = n;
  while(l < r){
      while(mod[l] + mod[r] < k) l++;
      if(l>=r) break;
      if(mod[l] + mod[r] >= k) ans++, l++, r--;
      else break;
  }
  ```

#### 题解作者：mahaoming (赞：2)
- **星级**：4星
- **关键亮点**：代码简洁，逻辑清晰，直接使用了原数组进行排序和双指针操作。
- **核心代码**：
  ```cpp
  sort(a + 1, a + n + 1);
  while(l < r){
      while(a[l] + a[r] < k) l++;
      if(l>=r) break;
      if(a[l] + a[r] >= k) s++, l++, r--;
      else break;
  }
  ```

### 最优关键思路或技巧
1. **贪心策略**：通过将商品重量对 $k$ 取模，将问题转化为如何最大化余数的组合。
2. **双指针法**：对余数数组排序后，使用双指针法高效地找到满足条件的组合。

### 可拓展之处
类似的问题可以出现在其他需要最大化组合价值的场景中，如最大化某些资源的利用率、最大化某些指标的总和等。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1208 [USACO1.3]混合牛奶 Mixing Milk](https://www.luogu.com.cn/problem/P1208)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得总结
- **调试经历**：在处理余数组合时，双指针的边界条件需要特别注意，避免指针越界或重复计算。
- **顿悟感想**：通过将问题转化为余数的组合，可以大大简化问题的复杂度，贪心策略在此类问题中非常有效。

---
处理用时：41.26秒