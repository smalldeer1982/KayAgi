# 题目信息

# Harmony Analysis

## 题目描述

The semester is already ending, so Danil made an effort and decided to visit a lesson on harmony analysis to know how does the professor look like, at least. Danil was very bored on this lesson until the teacher gave the group a simple task: find $ 4 $ vectors in $ 4 $ -dimensional space, such that every coordinate of every vector is $ 1 $ or $ -1 $ and any two vectors are orthogonal. Just as a reminder, two vectors in $ n $ -dimensional space are considered to be orthogonal if and only if their scalar product is equal to zero, that is:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF610C/1ed68100811c8d9a7f92461867e21d565afe33d0.png).Danil quickly managed to come up with the solution for this problem and the teacher noticed that the problem can be solved in a more general case for $ 2^{k} $ vectors in $ 2^{k} $ -dimensinoal space. When Danil came home, he quickly came up with the solution for this problem. Can you cope with it?

## 说明/提示

Consider all scalar products in example:

- Vectors $ 1 $ and $ 2 $ : $ (+1)·(+1)+(+1)·(-1)+(-1)·(+1)+(-1)·(-1)=0 $
- Vectors $ 1 $ and $ 3 $ : $ (+1)·(+1)+(+1)·(+1)+(-1)·(+1)+(-1)·(+1)=0 $
- Vectors $ 1 $ and $ 4 $ : $ (+1)·(+1)+(+1)·(-1)+(-1)·(-1)+(-1)·(+1)=0 $
- Vectors $ 2 $ and $ 3 $ : $ (+1)·(+1)+(-1)·(+1)+(+1)·(+1)+(-1)·(+1)=0 $
- Vectors $ 2 $ and $ 4 $ : $ (+1)·(+1)+(-1)·(-1)+(+1)·(-1)+(-1)·(+1)=0 $
- Vectors $ 3 $ and $ 4 $ : $ (+1)·(+1)+(+1)·(-1)+(+1)·(-1)+(+1)·(+1)=0 $

## 样例 #1

### 输入

```
2
```

### 输出

```
++**
+*+*
++++
+**+```

# AI分析结果

### 题目内容
# 和谐分析

## 题目描述
学期已经快结束了，所以达尼尔努力了一下，决定去上一节和谐分析课，至少去看看教授长什么样。在这节课上，达尼尔一直觉得很无聊，直到老师给小组布置了一个简单的任务：在四维空间中找到4个向量，使得每个向量的每个坐标都是1或 - 1，并且任意两个向量都是正交的。提醒一下，在n维空间中，两个向量被认为是正交的，当且仅当它们的标量积等于零，即：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF610C/1ed68100811c8d9a7f92461867e21d565afe33d0.png)

达尼尔很快就想出了这个问题的解决方案，老师注意到这个问题在更一般的情况下，即在 $2^{k}$ 维空间中找到 $2^{k}$ 个向量，也可以解决。当达尼尔回到家后，他很快就想出了这个更一般问题的解决方案。你能解决吗？

## 说明/提示
考虑示例中的所有标量积：
- 向量1和2：$(+1)·(+1)+(+1)·(-1)+(-1)·(+1)+(-1)·(-1)=0$
- 向量1和3：$(+1)·(+1)+(+1)·(+1)+(-1)·(+1)+(-1)·(+1)=0$
- 向量1和4：$(+1)·(+1)+(+1)·(-1)+(-1)·(-1)+(-1)·(+1)=0$
- 向量2和3：$(+1)·(+1)+(-1)·(+1)+(+1)·(+1)+(-1)·(+1)=0$
- 向量2和4：$(+1)·(+1)+(-1)·(-1)+(+1)·(-1)+(-1)·(+1)=0$
- 向量3和4：$(+1)·(+1)+(+1)·(-1)+(+1)·(-1)+(+1)·(+1)=0$

## 样例 #1
### 输入
```
2
```
### 输出
```
++**
+*+*
++++
+**+
```

### 算法分类
构造

### 题解综合分析与结论
这几道题解均围绕如何构造出满足条件的向量组展开。主要思路都是通过对低维情况（如k = 1, 2等）的观察，总结出构造高维向量组的规律。
 - **思路方面**：多数题解发现构造出的向量组呈现出类似分形或矩阵变换的规律。如将低维向量组通过复制、取反等操作扩展到高维。
 - **算法要点**：利用数学归纳法证明构造的正确性，通过循环等操作实现向量组的构造。
 - **解决难点**：关键在于发现向量组构造的规律，以及理解和证明不同维度向量之间点积为0的原理。

### 所选的题解
 - **作者：Karry5307 (5星)**
    - **关键亮点**：通过观察样例输出，发现答案具有分形图形的特征，利用数学归纳法严谨证明构造的正确性，代码实现采用递归方式计算向量组。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
inline void calc(ll l,ll r,ll u,ll d,ll sgn)
{
	if(l==r)
	{
		return (void)(ch[l][u]="+*"[sgn]);
	}
	ll mid=(l+r)>>1,mid2=(u+d)>>1;
	calc(l,mid,u,mid2,sgn),calc(l,mid,mid2+1,d,sgn);
	calc(mid+1,r,u,mid2,sgn),calc(mid+1,r,mid2+1,d,sgn^1);
}
```
核心实现思想：以递归方式，根据当前范围和符号标志，将大区域不断划分为小区域，确定每个小区域对应的向量坐标符号。
 - **作者：泠小毒 (4星)**
    - **关键亮点**：通过手动推导低维情况（k为2、3），总结出将低维向量组扩大一倍并对后一半向量偶数位取反的构造规律，代码简洁明了。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
for(int i=1;i<=n;i++)
{
    for(int j=0;j<m;j++)for(int k=m*2-1;k>=0;k--)a[j][k]=a[j][k/2];
    for(int j=m;j<m*2;j++)for(int k=0;k<m*2;k++)a[j][k]=a[j-m][k];
    for(int j=m;j<m*2;j++)for(int k=1;k<m*2;k+=2)a[j][k]^=1;
    m*=2;
}
```
核心实现思想：通过三层循环，先复制前半部分向量，再复制前半部分向量生成后半部分向量，最后对后半部分向量偶数位取反，实现向量组的构造。
 - **作者：snowstorm1939 (4星)**
    - **关键亮点**：指出构造的矩阵为Hadamard矩阵，并依据其性质，利用简单循环实现矩阵构造，代码逻辑清晰。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
for(int i=0;i<n;i++)
{
    x=pow(2,i);
    for(int i=x+1;i<=x+x;i++)
    for(int j=1;j<=x;j++)
    a[i][j]=a[i-x][j];
    for(int i=1;i<=x;i++)
    for(int j=x+1;j<=x+x;j++)
    a[i][j]=a[i][j-x];
    for(int i=x+1;i<=x+x;i++)
    for(int j=x+1;j<=x+x;j++)
    if(a[i-x][j-x]=='+')a[i][j]='*';
    else a[i][j]='+';
}
```
核心实现思想：通过循环，根据Hadamard矩阵的构造性质，先复制左上角矩阵生成左下角和右上角矩阵，再对右下角矩阵根据左上角矩阵对应位置元素取反，实现矩阵构造。

### 最优关键思路或技巧
通过对低维情况的手动推导和观察，发现向量组构造规律，利用数学归纳法证明其正确性，并借助循环或递归实现构造。同时，了解Hadamard矩阵的性质有助于快速解决此类问题。

### 可拓展之处
同类型题可关注其他需要构造特殊矩阵或向量组满足特定条件的题目。类似算法套路是从简单情况入手，寻找规律，再推广到一般情况，并通过数学方法证明规律的正确性。

### 洛谷相似题目推荐
 - [P1962 斐波那契数列](https://www.luogu.com.cn/problem/P1962)：考察递推思想，与本题从低维到高维找规律有相似之处。
 - [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)：通过对简单数字的计算规则观察，总结递推关系，类似本题找规律构造的思路。
 - [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)：同样是通过分析简单情况，得出递推式解决问题，锻炼从特殊到一般的思维能力。 

---
处理用时：58.39秒