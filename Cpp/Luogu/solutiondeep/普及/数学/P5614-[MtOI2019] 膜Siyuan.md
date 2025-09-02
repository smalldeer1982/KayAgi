# 题目信息

# [MtOI2019] 膜Siyuan

## 题目背景

你强归你强，$\mathsf S\mathsf{\color{red} iyuan}$ 比你强。——$\mathsf S \mathsf{\color{red} iyuan}$

disangan233 最近发现了一款 OIer 们的游戏：[膜 $\color{black} \mathsf S \mathsf{\color{red} iyuan}$](https://lmoliver.github.io/mosiyuan/index.html)。

他被里面的「真理 IV」所困惑，于是他找到了你寻求帮助。


## 题目描述

给你 $1$ 个正整数 $M$，$n(n\leq 5)$ 个正整数 $3$ 元组 $\{a_i,b_i,c_i\}(a_i,b_i,c_i\leq M\leq 2000)$，请你求出所有满足

$$
\forall i\leq n ,s.t.~|a_i-x|\oplus |b_i-y|\oplus |c_i-z| = 9
$$

的**有序**正整数 $3$ 元组 $\{x,y,z\}(x,y,z \leq M)$的个数。

其中，$\forall$ 表示 "对于所有"，$s.t.$ 表示 "使得"，$A \oplus B \oplus C$ 表示 $A,B,C$ 的异或和。

对于 C++，`A^B^C` 或 `A xor B xor C` 即为 $A \oplus B \oplus C$ 的答案 。

这里提供一份模板：

```cpp
if ((a ^ b ^ c) == 9) 
{
	Your code here...
}
```

对于 $2$ 个有序 $3$ 元组 $A,B$，如果 $x_A \not =x_B$ 或 $y_A \not =y_B$ 或 $z_A \not =z_B$，$A,B$ 即被视为是不同的。


## 说明/提示

#### 样例解释 $1$

所有满足条件的 $\{x,y,z\}$ 有： 

$\{88,88,120\}$，$\{88,104,104\}$，$\{120,120,120\}$ 和 $\{120,136,104\}$。

共 $4$ 个。

### 子任务

对于 $10\%$ 的数据，保证与样例完全一致。

对于 $60\%$ 的数据，保证 $M\leq 200$。

对于所有数据，保证 $a_i,b_i,c_i\leq M\leq 2000$，$n\leq 5$。


### 题目来源

[MtOI2019 Extra Round](https://www.luogu.org/contest/22614) T2

出题人：disangan233

验题人：Studying Father


## 样例 #1

### 输入

```
5 200
21 84 198
38 47 102
44 47 132 
63 150 166
76 79 132```

### 输出

```
4```

# AI分析结果

### 综合分析与结论

本题的核心在于通过异或运算的性质优化枚举过程。大多数题解都从暴力枚举的三重循环出发，通过异或的交换律和逆运算性质，将问题转化为只枚举两个变量，从而将时间复杂度从 \(O(M^3)\) 降低到 \(O(M^2)\)。这一优化思路是解决本题的关键。

### 评分较高的题解

#### 1. 作者：StudyingFather (5星)
- **关键亮点**：思路清晰，代码简洁，优化思路明确。通过枚举两个变量，利用异或的逆运算性质直接求解第三个变量，避免了不必要的枚举。
- **个人心得**：作者提到“绝对值方程可能会出现两个相同解的情况”，并给出了处理这种情况的方法，避免了重复计数。
- **核心代码**：
  ```cpp
  for(int i=1;i<=m;i++)
    for(int j=1;j<=m;j++)
    {
      int tmp=abs(i-a[1])^abs(j-b[1])^9;
      int res1=c[1]+tmp,res2=c[1]-tmp;
      int flag1=(res1>0&&res1<=m),flag2=(res2>0&&res2<=m);
      for(int k=2;k<=n;k++) 
      {
        flag1&=!(abs(i-a[k])^abs(j-b[k])^abs(res1-c[k])^9);
        flag2&=!(abs(i-a[k])^abs(j-b[k])^abs(res2-c[k])^9);
      }
      ans+=flag1+flag2;
    }
  ```

#### 2. 作者：disangan233 (4.5星)
- **关键亮点**：详细解释了异或运算的性质，并给出了优化思路的推导过程。代码实现简洁，逻辑清晰。
- **核心代码**：
  ```cpp
  for(int i=1;i<=m;i++) for(int j=1;j<=m;j++)
  {
    int tmp=(abs(i-a[1])^abs(j-b[1])^9),l=c[1]-tmp,r=c[1]+tmp; 
    int ok1=(l>0&&l<=m),ok2=(r>0&&r<=m&&(l^r));
    for(int k=2;k<=n;k++) 
    {
      ok1&=!(abs(i-a[k])^abs(j-b[k])^abs(l-c[k])^9);
      ok2&=!(abs(i-a[k])^abs(j-b[k])^abs(r-c[k])^9);
    }
    ans+=ok1+ok2;
  }
  ```

#### 3. 作者：zombie462 (4星)
- **关键亮点**：通过异或的逆运算性质优化枚举，代码实现简洁，逻辑清晰。作者还提到“异或的逆运算是其本身”，帮助理解优化思路。
- **核心代码**：
  ```cpp
  for(int i=1;i<=m;i++)
    for(int j=1;j<=m;j++)
    {
      int p=abs(a[1]-i)^abs(b[1]-j)^9;
      if(c[1]+p<=m && c[1]+p>0 && check(i,j,c[1]+p)) ans++;
      if(c[1]-p<=m && c[1]-p>0 && check(i,j,c[1]-p) && p) ans++;
    }
  ```

### 最优关键思路与技巧
- **异或的逆运算性质**：通过 \(A \oplus B \oplus C = D\) 可以推出 \(C = A \oplus B \oplus D\)，从而减少枚举的变量数量。
- **绝对值方程的解**：\(|x - y| = z\) 的解为 \(x = y \pm z\)，需要注意解的范围和重复解的情况。

### 可拓展之处
- **类似问题**：在涉及异或运算的题目中，常常可以通过异或的性质优化枚举过程。例如，给定多个数的异或和，求某个数的值。
- **其他优化思路**：在枚举过程中，可以通过剪枝、预处理等方法进一步优化时间复杂度。

### 推荐题目
1. [P3811 【模板】乘法逆元](https://www.luogu.com.cn/problem/P3811)
2. [P1463 [POI2001] 反素数](https://www.luogu.com.cn/problem/P1463)
3. [P1445 [Violet] 樱花](https://www.luogu.com.cn/problem/P1445)

### 个人心得总结
- **调试经历**：多位作者提到在调试过程中遇到的坑，如忽略绝对值方程的解的范围、重复解的处理等。这些经验教训对于避免类似错误非常有帮助。
- **顿悟感想**：通过异或的逆运算性质，将问题从三重循环优化为二重循环，这一思路的转变是解决本题的关键。

---
处理用时：30.40秒