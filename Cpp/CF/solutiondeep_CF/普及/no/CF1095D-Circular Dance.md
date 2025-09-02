# 题目信息

# Circular Dance

## 题目描述

There are $ n $ kids, numbered from $ 1 $ to $ n $ , dancing in a circle around the Christmas tree. Let's enumerate them in a clockwise direction as $ p_1 $ , $ p_2 $ , ..., $ p_n $ (all these numbers are from $ 1 $ to $ n $ and are distinct, so $ p $ is a permutation). Let the next kid for a kid $ p_i $ be kid $ p_{i + 1} $ if $ i < n $ and $ p_1 $ otherwise. After the dance, each kid remembered two kids: the next kid (let's call him $ x $ ) and the next kid for $ x $ . Each kid told you which kids he/she remembered: the kid $ i $ remembered kids $ a_{i, 1} $ and $ a_{i, 2} $ . However, the order of $ a_{i, 1} $ and $ a_{i, 2} $ can differ from their order in the circle.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1095D/ba706820d7e68c6ca7fa05954588bb8c356ad841.png)Example: 5 kids in a circle, $ p=[3, 2, 4, 1, 5] $ (or any cyclic shift). The information kids remembered is: $ a_{1,1}=3 $ , $ a_{1,2}=5 $ ; $ a_{2,1}=1 $ , $ a_{2,2}=4 $ ; $ a_{3,1}=2 $ , $ a_{3,2}=4 $ ; $ a_{4,1}=1 $ , $ a_{4,2}=5 $ ; $ a_{5,1}=2 $ , $ a_{5,2}=3 $ .You have to restore the order of the kids in the circle using this information. If there are several answers, you may print any. It is guaranteed that at least one solution exists.

If you are Python programmer, consider using PyPy instead of Python when you submit your code.

## 样例 #1

### 输入

```
5
3 5
1 4
2 4
1 5
2 3
```

### 输出

```
3 2 4 1 5 
```

## 样例 #2

### 输入

```
3
2 3
3 1
1 2
```

### 输出

```
3 1 2 
```

# AI分析结果

### 题目重写
#### 题目描述
有 $n$ 个小朋友，编号从 $1$ 到 $n$，围成一个圈绕着圣诞树跳舞。我们按顺时针方向将他们编号为 $p_1, p_2, \dots, p_n$（这些编号都是 $1$ 到 $n$ 的排列，且互不相同，因此 $p$ 是一个排列）。对于小朋友 $p_i$，如果 $i < n$，则下一个小朋友是 $p_{i+1}$，否则下一个小朋友是 $p_1$。跳舞结束后，每个小朋友记住了两个小朋友：下一个小朋友（记为 $x$）和 $x$ 的下一个小朋友。每个小朋友告诉你他记住的两个小朋友：小朋友 $i$ 记住了 $a_{i,1}$ 和 $a_{i,2}$。然而，$a_{i,1}$ 和 $a_{i,2}$ 的顺序可能与他们在圈中的顺序不同。

你需要根据这些信息恢复出小朋友在圈中的顺序。如果有多个答案，输出任意一个即可。题目保证至少有一个解。

#### 样例 #1
##### 输入
```
5
3 5
1 4
2 4
1 5
2 3
```
##### 输出
```
3 2 4 1 5 
```

#### 样例 #2
##### 输入
```
3
2 3
3 1
1 2
```
##### 输出
```
3 1 2 
```

### 算法分类
**构造**

### 题解分析与结论
题目要求根据每个小朋友记住的两个小朋友的信息，恢复出小朋友在圈中的顺序。由于每个小朋友记住的两个小朋友的顺序可能不同，因此需要通过某种方式确定这两个小朋友的顺序关系。

#### 题解对比
1. **Remilia1023** 的题解：
   - **亮点**：通过判断某个小朋友的后继是否包含另一个小朋友来确定顺序，简洁高效。
   - **难点**：处理特殊情况（如环长为3时）需要特判。
   - **评分**：5星

2. **晴空一鹤** 的题解：
   - **亮点**：通过构建图并遍历环来恢复顺序，思路清晰。
   - **难点**：需要处理遍历顺序，确保方向正确。
   - **评分**：4星

3. **oimaster** 的题解：
   - **亮点**：通过构造图并记录起始点的两个数字，确保遍历方向正确。
   - **难点**：需要处理图的遍历方向，避免走反。
   - **评分**：4星

#### 最优关键思路
- **Remilia1023** 的题解通过判断某个小朋友的后继是否包含另一个小朋友来确定顺序，简洁高效。对于特殊情况（如环长为3时）进行特判，确保正确性。

#### 关键代码
```cpp
bool suf(int u, int v)  // 判断 v 是否为 u 的后继
{
  return a[u] == v || b[u] == v;
}
  
int main()
{
  qcin >> n;
  if (n == 3)
    return printf("1 2 3\n"), 0;
  for (int i = 1; i <= n; i++)
    qcin >> a[i] >> b[i];
  int p = 1;
  for (int i = 1; i <= n; i++) {
    qcout << p << ' ';
    if (suf(a[p], b[p])) p = a[p];
    else p = b[p];
  }
  return 0;
}
```

### 扩展思路
- 类似题目可以通过构建图并遍历环来解决，关键在于确定遍历顺序和方向。
- 对于特殊情况（如环长为3时）需要进行特判，确保算法的鲁棒性。

### 推荐题目
1. [P1351 联合权值](https://www.luogu.com.cn/problem/P1351)
2. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
3. [P1353 跑步](https://www.luogu.com.cn/problem/P1353)

---
处理用时：31.93秒