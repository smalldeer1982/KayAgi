# 题目信息

# Bitwise Queries (Easy Version)

## 题目描述

The only difference between the easy and hard versions is the constraints on the number of queries.

This is an interactive problem.

Ridbit has a hidden array $ a $ of $ n $ integers which he wants Ashish to guess. Note that $ n $ is a power of two. Ashish is allowed to ask three different types of queries. They are of the form

- AND $ i $ $ j $ : ask for the [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) of elements $ a_i $ and $ a_j $ $ (1 \leq i, j \le n $ , $ i \neq j) $
- OR $ i $ $ j $ : ask for the [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) of elements $ a_i $ and $ a_j $ $ (1 \leq i, j \le n $ , $ i \neq j) $
- XOR $ i $ $ j $ : ask for the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of elements $ a_i $ and $ a_j $ $ (1 \leq i, j \le n $ , $ i \neq j) $

Can you help Ashish guess the elements of the array?

In this version, each element takes a value in the range $ [0, n-1] $ (inclusive) and Ashish can ask no more than $ n+2 $ queries.

## 说明/提示

The array $ a $ in the example is $ [0, 0, 2, 3] $ .

## 样例 #1

### 输入

```
4

0

2

3```

### 输出

```
OR 1 2

OR 2 3

XOR 2 4

! 0 0 2 3```

# AI分析结果

### 题目内容（中文重写）
# 位运算查询（简单版本）

## 题目描述
简单版本和困难版本的唯一区别在于查询次数的限制。

这是一个交互式问题。

Ridbit 有一个由 $n$ 个整数组成的隐藏数组 $a$，他想让 Ashish 猜出这个数组。注意，$n$ 是 2 的幂。Ashish 可以询问三种不同类型的问题，形式如下：
- AND $i$ $j$：询问元素 $a_i$ 和 $a_j$ 的按位与（[bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND)），其中 $1 \leq i, j \leq n$ 且 $i \neq j$。
- OR $i$ $j$：询问元素 $a_i$ 和 $a_j$ 的按位或（[bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR)），其中 $1 \leq i, j \leq n$ 且 $i \neq j$。
- XOR $i$ $j$：询问元素 $a_i$ 和 $a_j$ 的按位异或（[bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)），其中 $1 \leq i, j \leq n$ 且 $i \neq j$。

你能帮助 Ashish 猜出数组的元素吗？

在这个版本中，每个元素的值在范围 $[0, n - 1]$ 内（包含边界），并且 Ashish 最多可以询问 $n + 2$ 次。

## 说明/提示
示例中的数组 $a$ 是 $[0, 0, 2, 3]$。

## 样例 #1
### 输入
```
4
0
2
3
```
### 输出
```
OR 1 2
OR 2 3
XOR 2 4
! 0 0 2 3
```

### 算法分类
位运算

### 综合分析与结论
这些题解的核心思路都是先通过异或操作得到数组元素间的异或关系，再利用其他位运算求出一个确定的元素，最后根据异或的自反律推出整个数组。不同题解在选择具体的位运算组合和求解确定元素的方法上有所不同。

### 所选题解
- **作者：henrytb（4星）**
    - **关键亮点**：思路清晰，利用异或性质和位运算公式推导，代码实现简洁明了。
    - **核心实现思想**：先耗费 $n - 1$ 次询问求所有的 $a_i\oplus a_{i + 1}$，再询问 $a_1|a_2$、$a_2|a_3$、$a_1|a_3$，通过推导公式求出 $a_1$，进而推出整个数组。
    - **核心代码**：
```cpp
rep(i,1,n-1) {
    printf("XOR %d %d\n",i,i+1);
    fflush(stdout);
    scanf("%d",&xors[i]);
}
printf("OR 1 2\n");
fflush(stdout);
scanf("%d",&a12);
printf("OR 2 3\n");
fflush(stdout);
scanf("%d",&a23);
printf("OR 1 3\n");
fflush(stdout);
scanf("%d",&a13);
int sum12=a12+a12-xors[1];
int sum23=a23+a23-xors[2];
int sum13=a13+a13-(xors[1]^xors[2]);
int summ=sum12+sum23+sum13;summ/=2;
int now=summ-sum23;
printf("! %d ",now);
rep(i,1,n-1) {
    now^=xors[i];
    printf("%d ",now);
}
```
- **作者：Super_Cube（4星）**
    - **关键亮点**：利用位运算结论，通过询问 $a_1|a_2$、$a_2|a_3$、$a_1|a_3$、$a_1\oplus a_2$、$a_2\oplus a_3$ 求出 $a_2$，进而推出整个数组，思路简洁。
    - **核心实现思想**：先询问必要的位运算结果，根据位运算结论求出 $a_1 + a_2$、$a_2 + a_3$、$a_1 + a_3$，从而求出 $a_2$，再根据异或关系推出其他元素。
    - **核心代码**：
```cpp
puts("OR 1 2");fflush(stdout);
scanf("%d",&a);
puts("OR 2 3");fflush(stdout);
scanf("%d",&b);
puts("OR 1 3");fflush(stdout);
scanf("%d",&c);
puts("XOR 1 2");fflush(stdout);
scanf("%d",&d);
puts("XOR 2 3");fflush(stdout);
scanf("%d",&e);
ans[2]=(((a<<1)-d)+((b<<1)-e)-((c<<1)-(d^e))>>1);
ans[1]=((a<<1)-d)-ans[2];
ans[3]=((b<<1)-e)-ans[2];
for(int i=4;i<=n;++i){
    printf("XOR %d %d\n",i-1,i);fflush(stdout);
    scanf("%d",&a);ans[i]=ans[i-1]^a;
}
```
- **作者：pomelo_nene（4星）**
    - **关键亮点**：给出位运算公式 $a \operatorname{xor} b + 2 \times (a \operatorname{and} b) = a + b$，通过查询前三个元素的相关位运算结果，联立方程求解出前三个元素，再根据异或性质推出整个数组。
    - **核心实现思想**：查询前三个元素的 $a_1 \operatorname{xor} a_2$、$a_1 \operatorname{xor} a_3$、$a_1 \operatorname{and} a_2$、$a_1 \operatorname{and} a_3$、$a_2 \operatorname{and} a_3$，根据公式求出 $a_1 + a_2$、$a_1 + a_3$、$a_2 + a_3$，联立方程求解出 $a_1$、$a_2$、$a_3$，再根据异或关系推出其他元素。
    - **核心代码**：
```cpp
puts("XOR 1 2");
fflush(stdout);
int a;
scanf("%d",&a);
puts("XOR 1 3");
fflush(stdout);
int b;
scanf("%d",&b);
int c=a^b;
puts("AND 1 2");
fflush(stdout);
int e;
scanf("%d",&e);
puts("AND 1 3");
fflush(stdout);
int f;
scanf("%d",&f);
puts("AND 2 3");
fflush(stdout);
int g;
scanf("%d",&g);
int x=a+2*e,y=b+2*f,z=c+2*g;
int fuck=(x+y+z)/2;
ans[1]=fuck-z,ans[2]=fuck-y,ans[3]=fuck-x;
for(int i=4;i<=n;++i)
{
    printf("XOR 1 %d\n",i);
    fflush(stdout);
    int p;
    scanf("%d",&p);
    ans[i]=ans[1]^p;
}
```

### 最优关键思路或技巧
- 利用异或的自反律，即已知 $a$ 和 $a\oplus b$ 可推出 $b$，通过求出一个确定的元素，结合异或关系推出整个数组。
- 灵活运用位运算的性质和公式，如 $(a\ | \ b)-(a\ \&\ b)=a\oplus b$，$(a\ | \ b)+(a\ \&\ b)=a+b$，$a \operatorname{xor} b + 2 \times (a \operatorname{and} b) = a + b$ 等，通过联立方程求解元素的值。

### 可拓展之处
同类型题可能会改变查询次数的限制、数组元素的取值范围或查询操作的类型，解题思路仍然是利用位运算的性质和关系，通过合理的查询组合求出数组元素。类似算法套路包括利用位运算的性质进行方程推导和求解，以及根据已知的位运算结果推出其他元素。

### 推荐洛谷题目
- [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)：涉及位运算和队列的应用。
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：可以通过位运算进行状态标记和处理。
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：可以利用位运算优化一些判断和计算。

### 个人心得摘录与总结
- **作者：henrytb**：觉得这题很有趣，通过推导位运算公式解决问题。总结：在解决位运算相关问题时，多推导公式，可能会发现解题的关键。

---
处理用时：58.72秒