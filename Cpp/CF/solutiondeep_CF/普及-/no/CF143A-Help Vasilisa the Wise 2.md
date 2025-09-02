# 题目信息

# Help Vasilisa the Wise 2

## 题目描述

Vasilisa the Wise from the Kingdom of Far Far Away got a magic box with a secret as a present from her friend Hellawisa the Wise from the Kingdom of A Little Closer. However, Vasilisa the Wise does not know what the box's secret is, since she cannot open it again. She hopes that you will help her one more time with that.

The box's lock looks as follows: it contains $ 4 $ identical deepenings for gems as a $ 2×2 $ square, and some integer numbers are written at the lock's edge near the deepenings. The example of a lock is given on the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF143A/3afffa6690b0a7fee0cca96fe3fb7d95cf7329f2.png)The box is accompanied with $ 9 $ gems. Their shapes match the deepenings' shapes and each gem contains one number from $ 1 $ to $ 9 $ (each number is written on exactly one gem). The box will only open after it is decorated with gems correctly: that is, each deepening in the lock should be filled with exactly one gem. Also, the sums of numbers in the square's rows, columns and two diagonals of the square should match the numbers written at the lock's edge. For example, the above lock will open if we fill the deepenings with gems with numbers as is shown on the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF143A/3d3ced733d775964ba52205e4c988cebde0d133f.png)Now Vasilisa the Wise wants to define, given the numbers on the box's lock, which gems she should put in the deepenings to open the box. Help Vasilisa to solve this challenging task.

## 说明/提示

Pay attention to the last test from the statement: it is impossible to open the box because for that Vasilisa the Wise would need 4 identical gems containing number "5". However, Vasilisa only has one gem with each number from $ 1 $ to $ 9 $ .

## 样例 #1

### 输入

```
3 7
4 6
5 5
```

### 输出

```
1 2
3 4
```

## 样例 #2

### 输入

```
11 10
13 8
5 16
```

### 输出

```
4 7
9 1
```

## 样例 #3

### 输入

```
1 2
3 4
5 6
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
10 10
10 10
10 10
```

### 输出

```
-1
```

# AI分析结果

### 题目重写
# 帮助瓦西丽莎智者2

## 题目描述
来自遥远王国的智者瓦西丽莎从来自稍近王国的智者海拉维萨那里收到了一个带有秘密的魔法盒子作为礼物。然而，智者瓦西丽莎不知道盒子的秘密是什么，因为她无法再次打开它。她希望你能再帮她一次。

盒子的锁看起来是这样的：它包含4个相同的宝石凹槽，呈2×2的正方形，并且在锁的边缘靠近凹槽处写有一些整数。下面的图片给出了一个锁的示例。
![锁的示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF143A/3afffa6690b0a7fee0cca96fe3fb7d95cf7329f2.png)
盒子配有9颗宝石。它们的形状与凹槽的形状相匹配，并且每颗宝石上都刻有一个从1到9的数字（每个数字恰好写在一颗宝石上）。只有在正确地用宝石装饰盒子后，盒子才会打开：也就是说，锁上的每个凹槽都应该恰好放入一颗宝石。此外，正方形的行、列和两条对角线上的数字之和应该与锁边缘上写的数字相匹配。例如，上面的锁如果我们按照下面图片所示用刻有数字的宝石填充凹槽就会打开。
![正确填充宝石示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF143A/3d3ced733d775964ba52205e4c988cebde0d133f.png)
现在智者瓦西丽莎想确定，给定盒子锁上的数字，她应该把哪些宝石放入凹槽中才能打开盒子。帮助瓦西丽莎解决这个具有挑战性的任务。

## 说明/提示
请注意题目中的最后一个测试用例：不可能打开盒子，因为为了打开它，智者瓦西丽莎需要4颗相同的刻有数字“5”的宝石。然而，智者瓦西丽莎只有从1到9每个数字各一颗的宝石。

## 样例 #1
### 输入
```
3 7
4 6
5 5
```
### 输出
```
1 2
3 4
```

## 样例 #2
### 输入
```
11 10
13 8
5 16
```
### 输出
```
4 7
9 1
```

## 样例 #3
### 输入
```
1 2
3 4
5 6
```
### 输出
```
-1
```

## 样例 #4
### 输入
```
10 10
10 10
10 10
```
### 输出
```
-1
```

### 算法分类
数学

### 综合分析与结论
这几道题解主要呈现了三种解题思路。一种是暴力枚举，通过枚举所有可能的宝石放置情况来判断是否符合条件；一种是深搜，在搜索过程中根据行列及对角线和的条件进行回溯；还有一种是通过数学推导，利用方程之间的关系直接求解。暴力枚举和深搜思路较为直接，但时间复杂度较高，数学推导的方法更具技巧性，时间复杂度为O(1)，在效率上有很大优势。

### 所选的题解
 - **作者：yzy041616 (5星)**
    - **关键亮点**：通过数学方法，利用方程组之间的关系，推导出判断是否有解以及求解的方法，时间复杂度为O(1)，效率高。
    - **重点代码**：
```cpp
int main(){
    int r1,r2,c1,c2,d1,d2,a,b,c,d;
    cin>>r1>>r2>>c1>>c2>>d1>>d2;
    bool possible=1;
    if(r1+r2!=c1+c2||r1+r2!=d1+d2||c1+c2!=d1+d2)possible=0;
    int b_minus_c=r1-c1;
    if((b_minus_c+d2)&1)possible=0;
    b=(d2+b_minus_c)>>1;
    c=d2-b;
    a=r1-b;
    d=r2-c;
    if(a==b||a==c||a==d||b==c||b==d||c==d)possible=0;
    if(a<=0||b<=0||c<=0||d<=0)possible=0;
    if(a>9||b>9||c>9||d>9)possible=0;
    if(possible)cout<<a<<" "<<b<<endl<<c<<" "<<d;
    else cout<<-1;
}
```
    - **核心实现思想**：首先根据方程关系判断$r_1 + r_2$、$c_1 + c_2$、$d_1 + d_2$是否相等，若不相等则无解；接着利用方程相减得到$b - c$的值，结合$b + c$的值判断奇偶性并求解$b$和$c$，进而得到$a$和$d$，最后检查解是否符合条件。

### 最优关键思路或技巧
通过数学推导建立方程并利用方程之间的运算关系来判断是否有解以及求解，这种方法极大地优化了时间复杂度，避免了暴力搜索带来的高时间消耗。

### 拓展
同类型题通常围绕方程组求解、数字组合满足特定条件等场景。类似算法套路是遇到这类问题时，尝试通过建立数学模型，利用数学性质和运算关系来简化问题求解，避免直接暴力搜索。

### 洛谷相似题目推荐
 - P1085 [NOIP2004 普及组] 不高兴的津津
 - P1147 连续自然数和
 - P1217 [USACO1.5]回文质数 Prime Palindromes 

---
处理用时：53.20秒