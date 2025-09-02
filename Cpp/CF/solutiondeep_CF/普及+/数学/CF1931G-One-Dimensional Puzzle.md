# 题目信息

# One-Dimensional Puzzle

## 题目描述

You have a one-dimensional puzzle, all the elements of which need to be put in one row, connecting with each other. All the puzzle elements are completely white and distinguishable from each other only if they have different shapes.

Each element has straight borders at the top and bottom, and on the left and right it has connections, each of which can be a protrusion or a recess. You cannot rotate the elements.

You can see that there are exactly $ 4 $ types of elements. Two elements can be connected if the right connection of the left element is opposite to the left connection of the right element.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1931G/ab3dee044a8e18206fe7c695b7a089bda5931d43.png) All possible types of elements. The puzzle contains $ c_1, c_2, c_3, c_4 $ elements of each type. The puzzle is considered complete if you have managed to combine all elements into one long chain. You want to know how many ways this can be done.

## 样例 #1

### 输入

```
11
1 1 1 1
1 2 5 10
4 6 100 200
900000 900000 900000 900000
0 0 0 0
0 0 566 239
1 0 0 0
100 0 100 0
0 0 0 4
5 5 0 2
5 4 0 5```

### 输出

```
4
66
0
794100779
1
0
1
0
1
36
126```

# AI分析结果



### 题目内容重写
#### 题目描述

你有一个一维拼图，所有元素需要排成一行并相互连接。所有拼图元素均为纯白色，仅通过形状区分。

每个元素的顶部和底部为直线边缘，左右两侧为连接部分，可能是凸起或凹陷。不可旋转元素。

共有4种元素类型（如图）。两个元素可连接的条件是左元素的右连接与右元素的左连接相反。

给定每种类型的元素数量 $c_1, c_2, c_3, c_4$，求将所有元素连成一条长链的方案数。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1931G/ab3dee044a8e18206fe7c695b7a089bda5931d43.png)

#### 样例输入输出
见原题。

---

### 题解综合分析

#### 核心思路
1. **交替条件**：类型1和2必须交替出现，故当 $|c_1 - c_2| > 1$ 时无解
2. **插板法应用**：类型3/4的放置问题转化为将 $n$ 个相同物品放入 $k$ 个盒子的组合问题 $\tbinom{n+k-1}{k-1}$
3. **分类讨论**：
   - $c_1 = c_2$ 时有首元素为1或2两种排列方式
   - $c_1 = c_2 \pm 1$ 时只有一种排列方式
4. **边界处理**：特判 $c_1=c_2=0$ 时的全3/4情况

#### 精选题解
1. **快斗游鹿（★★★★）**
   - **亮点**：清晰的分类讨论框架，高效预处理组合数，边界条件处理完善
   - **代码要点**：
     ```cpp
     // 预处理阶乘与逆元
     fac[0] = 1;
     for(int i=2;i<=8e6;i++) inv[i] = (mod-mod/i)*inv[mod%i]%mod;
     
     // 主要计算逻辑
     if(a == b) {
         ans = (C(a+c-1,a-1)*C(b+d,b) + C(b+d-1,b-1)*C(a+c,a)) % mod;
     } else if(abs(a-b)==1) {
         ans = C(max(a,b)+c-1,max(a,b)-1) * C(max(a,b)+d-1,max(a,b)-1) % mod;
     }
     ```

2. **Register_int（★★★★）**
   - **亮点**：数学推导严谨，代码结构简洁，变量命名清晰
   - **核心公式**：
     ```cpp
     // 类型3的放置数计算
     C(c3 + (c1+c2-1)/2, c3) * C(c4 + (c1+c2)/2, c4)
     ```

#### 关键技巧总结
1. **组合数预处理**：O(n) 预处理阶乘与逆元加速计算
2. **状态压缩**：将类型3/4的放置问题抽象为独立组合数乘积
3. **分类模式**：基于类型1/2的数量关系划分三种情况

#### 拓展应用
- **类似问题**：字符串交替排列中的插空问题（如ABC336G）
- **算法套路**：组合数+分类讨论适用于元素间存在强制顺序约束的计数问题

#### 相似题目推荐
1. [P1655 小球](https://www.luogu.com.cn/problem/P1655)（组合数基础）
2. [CF1929F Sasha and the Wedding](https://www.luogu.com.cn/problem/CF1929F)（组合数+插空）
3. [ABC336G 16 Integers](https://www.luogu.com.cn/problem/AT_abc336_g)（高阶欧拉路径计数）

---

### 题解代码精要
**快斗游鹿的核心代码**：
```cpp
int C(int nn, int mm) {
    return fac[nn] * inv[mm] % mod * inv[nn-mm] % mod;
}

if (c1 == c2) {
    ans = (C(c3 + c1 - 1, c1 - 1) * C(c4 + c1, c1) 
         + C(c4 + c1 - 1, c1 - 1) * C(c3 + c1, c1)) % mod;
} else if (abs(c1-c2) == 1) {
    int a = max(c1, c2);
    ans = C(c3 + a - 1, a - 1) * C(c4 + a - 1, a - 1) % mod;
}
```
**实现要点**：
- 预处理阶乘表加速组合数查询
- 使用max函数统一处理两种相差1的情况
- 模运算保持结果正确性

---
处理用时：53.27秒