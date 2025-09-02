# [ICPC-Beijing 2011] Matrix 矩阵哈希

## 题目描述

给定一个 $M$ 行 $N$ 列的 $01$ 矩阵，以及 $Q$ 个 $A$ 行 $B$ 列的 $01$ 矩阵，你需要求出这 $Q$ 个矩阵哪些在原矩阵中出现过。 

所谓 $01$ 矩阵，就是矩阵中所有元素不是 $0$ 就是 $1$。

## 说明/提示

对于 $100\%$ 的实际测试数据，$1\leq M,N \leq 1000$，$Q = 1000$。 

对于 $40\%$ 的数据，$A = 1$。

对于 $80\%$ 的数据，$A \leq 10$。

对于 $100\%$ 的数据，$A \leq 100$。

## 样例 #1

### 输入

```
3 3 2 2
111
000
111
3
11
00
11
11
00
11```

### 输出

```
1
0
1```

# 题解

## 作者：Taoran_01 (赞：38)

---
### 知识前置
#### 哈希
一种映射，从大值域到小值域。本文中的哈希均指字符串哈希，即将数列 $\{a_n\}$ 视作 $p$ 进制数后对 $M$ 取模的结果，即 $H(a)=(\sum\limits_{i=1}^na_i\times p^{n-i})\operatorname{mod}M$。其中，$p$ 称为底，$M$ 称为模数。有以下性质：
1. 当在数列 $\{a_n\}$ 的末尾插入数 $d$ 时，数列 $\{a_{n+1}\}$ 的哈希值 $H(a+d)=(H(a)\times p+d)\operatorname{mod} M$。
2. 已知数列 $\{c_{n+m}\}$ 的哈希值为 $H(c)$，数列 $\{a_n\}$ 的哈希值为 $H(a)$ ，而数列 $\{c_{n+m}\}$ 由数列 $\{a_n\}$ 和数列 $\{b_m\}$ 拼接而成，则 $H(b)=(H(c)-H(a)\times p^{m})\operatorname{mod}M$。

上述两条性质不难理解，就是 $p$ 进制数的位移运算与加减运算。

详见[OI-WIki](https://oi-wiki.org/string/hash/)中的第一种定义，或参考李煜东所著的《算法竞赛进阶指南》第75页。
#### 二维前缀和
二维哈希参考了二维前缀和的思想，使得哈希值可以 $O(1)$ 地从角落哈希值求出。

设 $S'_{x_1,y_1,x_2,y_2}=\sum\limits_{i=x_1}^{x_2}\sum\limits_{j=y_1}^{y_2}a_{i,j}$，$S_{x,y}=S'_{1,1,x,y}=\sum\limits_{i=1}^x\sum\limits_{j=1}^ya_{i,j}$，则有：
$$
S_{x,y}=a_{x,y}+S_{x-1,y}+S_{x,y-1}-S_{x-1,y-1}\\
S'_{x_1,y_1,x_2,y_2}=S_{x_2,y_2}-S_{x_1-1,y_2}-S_{x_2,y_1-1}+S_{x_1-1,y_1-1}
$$
自己画个图证明下就会了，详见[OI-Wiki](https://oi-wiki.org/basic/prefix-sum/#%E4%BA%8C%E7%BB%B4%E5%A4%9A%E7%BB%B4%E5%89%8D%E7%BC%80%E5%92%8C)。

---
### 二维哈希
将一个二维矩阵映射到一个值上，即：
$$
A=\begin{bmatrix}
a_{1,1}&\cdots&a_{1,m}\\
\vdots&\ddots&\vdots\\
a_{n,1}&\cdots&a_{n,m}
\end{bmatrix}\longrightarrow H(A)\in[0,M)\cap\mathbb Z
$$

---
### 整个矩阵哈希值的获取
#### 步骤一 按行哈希
将矩阵 $A$ 按行进行哈希得到矩阵 $F$。  
即，将矩阵 $A$ 视作 $n$ 个长度为 $m$ 的一维数列。
$$
A=\begin{bmatrix}
\color{orange}a_{1,1}&\color{orange}\cdots&\color{orange}a_{1,m}\\
\vdots&\ddots&\vdots\\
a_{n,1}&\cdots&a_{n,m}
\end{bmatrix}\longrightarrow
F=\begin{bmatrix}
f_{1,1}&\cdots&\color{orange}f_{1,m}\\
\vdots&\ddots&\vdots\\
f_{n,1}&\cdots&f_{n,m}
\end{bmatrix}
$$
设底为 $p_1$，模数为 $M$，则转移公式如下：
$$
f_{x,y}=(\sum_{i=1}^ya_{x,i}\times p_1^{y-i})\operatorname{mod}M
$$
根据一维哈希的性质，将公式进行优化：
$$
f_{x,y}=(f_{x,y-1}\times p_1+a_{x,y})\operatorname{mod}M
$$
#### 步骤二 按列哈希
将矩阵 $F$ 按列进行哈希得到矩阵 $G$。  
即，将矩阵 $F$ 视作 $m$ 个长度为 $n$ 的一维数列。
$$
F=\begin{bmatrix}
\color{orange}f_{1,1}&\cdots&f_{1,m}\\
\color{orange}\vdots&\ddots&\vdots\\
\color{orange}f_{n,1}&\cdots&f_{n,m}
\end{bmatrix}\longrightarrow
G=\begin{bmatrix}
g_{1,1}&\cdots&g_{1,m}\\
\vdots&\ddots&\vdots\\
\color{orange}g_{n,1}&\cdots&g_{n,m}
\end{bmatrix}
$$
设底为 $p_2$，模数为 $M$，则转移公式如下：
$$
g_{x,y}=(\sum_{i=1}^xf_{i,y}\times p_2^{x-i})\operatorname{mod}M
$$
根据一维哈希的性质，将公式进行优化：
$$
g_{x,y}=(g_{x-1,y}\times p_2+f_{x,y})\operatorname{mod}M
$$
#### 说明
先按行和先按列都是一样的。总而言之，不管你先做什么，最终的式子代进去都是这样的：
$$
g_{x,y}=(\sum_{i=1}^x\sum_{j=1}^ya_{i,j}\times p_2^{x-i}\times p_1^{y-j})\operatorname{mod}M
$$
依据总公式，仿照前缀和，你也可以在外面循环行，在里面循环列，同时求：
$$
g_{x,y}=(a_{x,y}+g_{x-1,y}\times p_2+g_{x,y-1}\times p_1-g_{x-1,y-1}\times p_1\times p_2)\operatorname{mod}M
$$
这个公式就有一部分包含下文子矩阵的思想了。
#### 第三步 获取哈希值
经过上面两个步骤后，矩阵 $G$ 的右下角 $g_{n,m}$ 就是矩阵 $A$ 的哈希值。

另外，如果对上面的步骤保留矩阵，$G$ 数组的值也是 $A$ 左上角子矩阵的哈希值，如图所示。
$$
A=\begin{bmatrix}
\color{orange}a_{1,1}&\color{orange}a_{1,2}&a_{1,3}&\cdots&a_{1,m}\\
\color{orange}a_{2,1}&\color{orange}a_{2,2}&a_{2,3}&\cdots&a_{2,m}\\
\color{orange}a_{3,1}&\color{orange}a_{3,2}&a_{3,3}&\cdots&a_{3,m}\\
a_{4,1}&a_{4,2}&a_{4,3}&\cdots&a_{4,m}\\
\vdots&\vdots&\vdots&\ddots&\vdots\\
a_{n,1}&a_{n,2}&a_{n,3}&\cdots&a_{n,m}
\end{bmatrix}\longrightarrow
G=\begin{bmatrix}
g_{1,1}&g_{1,2}&g_{1,3}&\cdots&g_{1,m}\\
g_{2,1}&g_{2,2}&g_{2,3}&\cdots&g_{2,m}\\
g_{3,1}&\color{orange}g_{3,2}&g_{3,3}&\cdots&g_{3,m}\\
g_{4,1}&g_{4,2}&g_{4,3}&\cdots&g_{4,m}\\
\vdots&\vdots&\vdots&\ddots&\vdots\\
g_{n,1}&g_{n,2}&g_{n,3}&\cdots&g_{n,m}
\end{bmatrix}
$$
在不发生冲突的情况下，$g_{n,m}$ 表示唯一的矩阵 $A$。可以依据哈希值判断矩阵是否相同。
#### 正确性证明
先对行进行哈希，再对列进行哈希，使得不同位置的元素有不同的权重，确保了较小的冲突概率。
#### 需要知道的风险
在将较大的矩阵处理到较小的值域上时，冲突风险会加大。请选取适当的底和模数以减小出现问题的概率。  
如果不放心，可以使用[双模数哈希](https://oi-wiki.org/string/hash/#%E9%94%99%E8%AF%AF%E7%8E%87)，或不使用二维哈希，考虑其它算法。
#### 代码实现
开 `unsigned long long` 存储，使用自然溢出的方式取模。此时模数 $M=2^{64}$。具体代码见下方例题。

---
### 子矩阵的哈希值获取
这一部分比较难以理解，建议自己算一下看看。

设行数在 $x_1$ 到 $x_2$ 之间、列数在 $y_1$ 到 $y_2$ 之间子矩阵的哈希值为 $H(x_1,y_1,x_2,y_2)$。  
根据上述步骤，我们已经知道了所有的 $H(1,1,x,y)$，其中 $x\in[1,n]$，$y\in[1,m]$。

参考一维哈希的方法，视作 $p$ 进制数。不过这里将不同列视为 $p_1$ 进制数（因为按行哈希时列转移乘了 $p_1$），将不同行视为 $p_2$ 进制数。

这样，在原矩阵的右侧添加一列空列，矩阵的哈希值 $H(A)$ 变为 $(H(A)\times p_1)\operatorname{mod}M$。  
在原矩阵的下方添加一行空行，矩阵的哈希值 $H(A)$ 变为 $(H(A)\times p_2)\operatorname{mod}M$。  
感性理解一下，证明我不会。

虽然矩阵是先对每一行哈希，再对每一列哈希，先以 $p_1$ 为底再以 $p_2$ 为底，但是最后乘上 $p_1$ 依旧是左移。就相当于原本是以第 $x$ 列做哈希，现在以第 $x-1$ 列做哈希，先后顺序不影响。
#### 结论
现在，我们需要 $O(1)$ 求解所有的 $H_(x_1,y_1,x_2,y_2)$。根据上述结论，易推得：
$$
\begin{aligned}
H(x_1&,y_1,x_2,y_2)=\\
&\hspace{0.3cm}(H(1,1,x_2,y_2)&\small\text{全部}\\
&-H(1,1,x_1-1,y_2)\times p_2^{x_2-x_1+1}&\small\text{减上方}\\
&-H(1,1,x_2,y_1-1)\times p_1^{y_2-y_1+1}&\small\text{减左侧}\\
&+H(1,1,x_1-1,y_1-1)\times p_2^{x_2-x_1+1}\times p_1^{y_2-y_1+1}&\small\text{加左上角}\\
&\hspace{0.3cm})\operatorname{mod}M\\
\end{aligned}
$$
画出来是这样的：
$$
\begin{bmatrix}
\color{purple}g_{1,1}&\color{purple}\cdots&\color{purple}g_{1,x_1-1}&\color{red}g_{1,x_1}&\color{red}\cdots&\color{red}g_{1,x_2}&\color{darkgrey}\cdots&\color{darkgrey}g_{1,m}\\
\color{purple}\vdots&\color{purple}\ddots&\color{purple}\vdots&\color{red}\vdots&\color{red}\ddots&\color{red}\vdots&\color{darkgrey}\ddots&\color{darkgrey}\vdots\\
\color{purple}g_{y_1-1,1}&\color{purple}\cdots&\color{purple}g_{y_1-1,x_1-1}&\color{red}g_{y_1-1,x_1}&\color{red}\cdots&\color{red}g_{y_1-1,x_2}&\color{darkgrey}\cdots&\color{darkgrey}g_{y_1-1,m}\\
\color{blue}g_{y_1,1}&\color{blue}\cdots&\color{blue}g_{y_1,x_1-1}&\color{green}g_{y_1,x_1}&\color{green}\cdots&\color{green}g_{y_1,x_2}&\color{darkgrey}\cdots&\color{darkgrey}g_{y_1,m}\\
\color{blue}\vdots&\color{blue}\ddots&\color{blue}\vdots&\color{green}\vdots&\color{green}\ddots&\color{green}\vdots&\color{darkgrey}\ddots&\color{darkgrey}\vdots\\
\color{blue}g_{y_2,1}&\color{blue}\cdots&\color{blue}g_{y_2,x_1-1}&\color{green}g_{y_2,x_1}&\color{green}\cdots&\color{green}g_{y_2,x_2}&\color{darkgrey}\cdots&\color{darkgrey}g_{y_2,m}\\
\color{darkgrey}\vdots&\color{darkgrey}\ddots&\color{darkgrey}\vdots&\color{darkgrey}\vdots&\color{darkgrey}\ddots&\color{darkgrey}\vdots&\color{darkgrey}\ddots&\color{darkgrey}\vdots\\
\color{darkgrey}g_{m,1}&\color{darkgrey}\cdots&\color{darkgrey}g_{m,x_1-1}&\color{darkgrey}g_{m,x_1}&\color{darkgrey}\cdots&\color{darkgrey}g_{m,x_2}&\color{darkgrey}\cdots&\color{darkgrey}g_{n,m}
\end{bmatrix}
$$
其中，绿色为目标区域，(绿色+红色+蓝色+紫色)为全部区域，(红色+紫色)为上方区域，(蓝色+紫色)为左侧区域，紫色为重复的左上角区域，灰色为无关区域。
#### 为什么要乘
此处的颜色标记与上面的不同，请注意区分。  
下面的矩阵在哈希意义下，不是普通的矩阵，详细规则见上。请将矩阵视作哈希。  
为方便理解，矩阵中的 $0$ 记作 $0_{x,y}$ 以标识位置。  
下文证明及其不严谨，仅作理解。

首先，左侧区域原本是这样的：
$$
A=\begin{bmatrix}
\color{blue}g_{1,1}&\color{blue}\cdots&\color{blue}g_{1,x_1-1}\\
\color{blue}\vdots&\color{blue}\ddots&\color{blue}\vdots\\
\color{blue}g_{y_2,1}&\color{blue}\cdots&\color{blue}g_{y_2,x_1-1}
\end{bmatrix}
$$
整体长这样：
$$
C=\begin{bmatrix}
\color{blue}g_{1,1}&\color{blue}\cdots&\color{blue}g_{1,x_1-1}&\color{green}g_{1,x_1}&\color{green}\cdots&\color{green}g_{1,x_2}\\
\color{blue}\vdots&\color{blue}\ddots&\color{blue}\vdots&\color{green}\vdots&\color{green}\ddots&\color{green}\vdots\\
\color{blue}g_{y_2,1}&\color{blue}\cdots&\color{blue}g_{y_2,x_1-1}&\color{green}g_{y_2,x_1}&\color{green}\cdots&\color{green}g_{y_2,x_2}
\end{bmatrix}
$$
我们想要得到：
$$
B=\begin{bmatrix}
\color{green}g_{1,x_1}&\color{green}\cdots&\color{green}g_{1,x_2}\\
\color{green}\vdots&\color{green}\ddots&\color{green}\vdots\\
\color{green}g_{y_2,x_1}&\color{green}\cdots&\color{green}g_{y_2,x_2}
\end{bmatrix}
$$
注意，在上文所述的哈希（视作 $p_1$、$p_2$ 进制）中，可以向上方和左侧补前导零。所以有：
$$
B=\begin{bmatrix}
\color{green}g_{1,x_1}&\color{green}\cdots&\color{green}g_{1,x_2}\\
\color{green}\vdots&\color{green}\ddots&\color{green}\vdots\\
\color{green}g_{y_2,x_1}&\color{green}\cdots&\color{green}g_{y_2,x_2}
\end{bmatrix}=\begin{bmatrix}
\color{darkgrey}0_{1,1}&\color{darkgrey}\cdots&\color{darkgrey}0_{1,x_1-1}&\color{green}g_{1,x_1}&\color{green}\cdots&\color{green}g_{1,x_2}\\
\color{darkgrey}\vdots&\color{darkgrey}\ddots&\color{darkgrey}\vdots&\color{green}\vdots&\color{green}\ddots&\color{green}\vdots\\
\color{darkgrey}0_{y_2,1}&\color{darkgrey}\cdots&\color{darkgrey}0_{y_2,x_1-1}&\color{green}g_{y_2,x_1}&\color{green}\cdots&\color{green}g_{y_2,x_2}
\end{bmatrix}
$$
但不能在下方或右侧补零，因为这样改变了哈希大小。所以：
$$
A=\begin{bmatrix}
\color{blue}g_{1,1}&\color{blue}\cdots&\color{blue}g_{1,x_1-1}\\
\color{blue}\vdots&\color{blue}\ddots&\color{blue}\vdots\\
\color{blue}g_{y_2,1}&\color{blue}\cdots&\color{blue}g_{y_2,x_1-1}
\end{bmatrix}\neq\begin{bmatrix}
\color{blue}g_{1,1}&\color{blue}\cdots&\color{blue}g_{1,x_1-1}&\color{darkgrey}0_{1,x_1}&\color{darkgrey}\cdots&\color{darkgrey}0_{1,x_2}\\
\color{blue}\vdots&\color{blue}\ddots&\color{blue}\vdots&\color{darkgrey}\vdots&\color{darkgrey}\ddots&\color{darkgrey}\vdots\\
\color{blue}g_{y_2,1}&\color{blue}\cdots&\color{blue}g_{y_2,x_1-1}&\color{darkgrey}0_{y_2,x_1}&\color{darkgrey}\cdots&\color{darkgrey}0_{y_2,x_2}
\end{bmatrix}
$$
因此，我们不能直接将 $H(C)-H(A)$ 作为目标 $H(B)$ 的答案，因为 $A$ 没有与 $C$ 对齐。  
要想对齐，就要将 $A$ 左移 $(x_2-x_1+1)$ 列，也就是在 $A$ 的右边插入 $(x_2-x_1+1)$ 个空列。按照上面的证明方式，只需将 $A$ 的哈希值乘 $p_2^{x_2-x_1+1}$ 即可。
$$
A\times p_2^{x_2-x_1+1}=
\begin{bmatrix}
\color{blue}g_{1,1}&\color{blue}\cdots&\color{blue}g_{1,x_1-1}&\color{darkgrey}0_{1,x_1}&\color{darkgrey}\cdots&\color{darkgrey}0_{1,x_2}\\
\color{blue}\vdots&\color{blue}\ddots&\color{blue}\vdots&\color{darkgrey}\vdots&\color{darkgrey}\ddots&\color{darkgrey}\vdots\\
\color{blue}g_{y_2,1}&\color{blue}\cdots&\color{blue}g_{y_2,x_1-1}&\color{darkgrey}0_{y_2,x_1}&\color{darkgrey}\cdots&\color{darkgrey}0_{y_2,x_2}
\end{bmatrix}
$$
这样，$A$ 与 $C$ 对齐后我们就可以相减得到答案。
$$
\begin{aligned}B=&\begin{bmatrix}
\color{green}g_{1,x_1}&\color{green}\cdots&\color{green}g_{1,x_2}\\
\color{green}\vdots&\color{green}\ddots&\color{green}\vdots\\
\color{green}g_{y_2,x_1}&\color{green}\cdots&\color{green}g_{y_2,x_2}
\end{bmatrix}=\begin{bmatrix}
\color{darkgrey}0_{1,1}&\color{darkgrey}\cdots&\color{darkgrey}0_{1,x_1-1}&\color{green}g_{1,x_1}&\color{green}\cdots&\color{green}g_{1,x_2}\\
\color{darkgrey}\vdots&\color{darkgrey}\ddots&\color{darkgrey}\vdots&\color{green}\vdots&\color{green}\ddots&\color{green}\vdots\\
\color{darkgrey}0_{y_2,1}&\color{darkgrey}\cdots&\color{darkgrey}0_{y_2,x_1-1}&\color{green}g_{y_2,x_1}&\color{green}\cdots&\color{green}g_{y_2,x_2}
\end{bmatrix}\\=&\begin{bmatrix}
\color{blue}g_{1,1}&\color{blue}\cdots&\color{blue}g_{1,x_1-1}&\color{green}g_{1,x_1}&\color{green}\cdots&\color{green}g_{1,x_2}\\
\color{blue}\vdots&\color{blue}\ddots&\color{blue}\vdots&\color{green}\vdots&\color{green}\ddots&\color{green}\vdots\\
\color{blue}g_{y_2,1}&\color{blue}\cdots&\color{blue}g_{y_2,x_1-1}&\color{green}g_{y_2,x_1}&\color{green}\cdots&\color{green}g_{y_2,x_2}
\end{bmatrix}-\begin{bmatrix}
\color{blue}g_{1,1}&\color{blue}\cdots&\color{blue}g_{1,x_1-1}&\color{darkgrey}0_{1,x_1}&\color{darkgrey}\cdots&\color{darkgrey}0_{1,x_2}\\
\color{blue}\vdots&\color{blue}\ddots&\color{blue}\vdots&\color{darkgrey}\vdots&\color{darkgrey}\ddots&\color{darkgrey}\vdots\\
\color{blue}g_{y_2,1}&\color{blue}\cdots&\color{blue}g_{y_2,x_1-1}&\color{darkgrey}0_{y_2,x_1}&\color{darkgrey}\cdots&\color{darkgrey}0_{y_2,x_2}
\end{bmatrix}\\=&C-A\times p_2^{x_2-x_1+1}\end{aligned}\\
H(B)=(H(C)-H(A)\times p_2^{x_2-x_1+1})\operatorname{mod}M
$$
同样地，通过位移操作，我们可以完成上方和左上角的矩阵操作，只需要对应乘 $p_1$、$p_2$ 的幂即可。

在程序中，由于会频繁进行 $p_1$、$p_2$ 的幂运算，我们通常会预处理出它们的 $1\sim n$ 次方，并存储到 `unsigned long long` 数组中。

---
### 举例
$p_1=7$，$p_2=239$，$M=+\infin$。
$$
A=\begin{bmatrix}
1&2&3\\4&5&6
\end{bmatrix},\ 
F=\begin{bmatrix}
1&9&66\\4&33&237
\end{bmatrix},\ 
G=\begin{bmatrix}
1&9&66\\
143&2184&16011
\end{bmatrix}\\
\text{对于子矩阵：}
A'=\begin{bmatrix}
2&3\\5&6
\end{bmatrix},\ 
F'=\begin{bmatrix}
2&17\\5&41
\end{bmatrix},\ 
G'=\begin{bmatrix}
2&17\\483&4104
\end{bmatrix}
$$
验证：$16011-0\times57121-243\times49=16011-11907=4104$，成立。

---
### 例题
[洛谷P10474](https://www.luogu.com.cn/problem/P10474) [BeiJing2011] Matrix 矩阵哈希  
注：为方便书写，本文将题目中的 $M$ 和 $N$ 替换为了 $n$ 和 $m$，与原题目有出入。
#### 题目描述
给出一个 $n$ 行 $m$ 列的 $01$ 矩阵，以及 $q$ 个 $A$ 行 $B$ 列的 $01$ 矩阵，你需要求出这 $q$ 个矩阵中有哪些矩阵是大矩阵的子矩阵。

数据范围：$1\le n,m\le1000$，$q=1000$。
#### 思路
先对整体取哈希，把每个大小为 $A\times B$ 的存入 `unordered_map`；然后对每个子矩阵取哈希，判断是否在 `map` 中即可。时间复杂度 $O(n^2)$。
#### 代码
[AC](https://www.luogu.com.cn/record/169139975) 49.65MB 1.08s
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 1010
int n, m, A, B, q;
ull a[N][N];
unordered_map<ull, bool> mp;

namespace tdh {
	#define P1 503ULL
	#define P2 1013ULL
	int n, m;
	ull f[N][N], g[N][N];
	ull p1[N], p2[N];
	void init(ull d[N][N], int n, int m) {
		p1[0]=p2[0]=1;
		for (int i=1; i<N; ++i) p1[i]=p1[i-1]*P1, p2[i]=p2[i-1]*P2;
		for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) {
			f[i][j]=f[i][j-1]*P1+d[i][j];
		}
		for (int j=1; j<=m; ++j) for (int i=1; i<=n; ++i) {
			g[i][j]=g[i-1][j]*P2+f[i][j];
		}
	}
	ull get(int x1, int y1, int x2, int y2) {
		return g[x2][y2]-g[x1-1][y2]*p2[x2-x1+1]-g[x2][y1-1]*p1[y2-y1+1]
		+g[x1-1][y1-1]*p1[y2-y1+1]*p2[x2-x1+1];
	}
}

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), m=read(), A=read(), B=read();
	for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) {
		char ch=getchar(); while (ch<'0'||ch>'1') ch=getchar(); a[i][j]=ch-'0';
	}
	tdh::init(a, n, m);
	for (int i=1; i<=n-A+1; ++i) for (int j=1; j<=m-B+1; ++j) {
		mp[(int)tdh::get(i, j, i+A-1, j+B-1)]=1;
	}
	q=read();
	while (q--) {
		for (int i=1; i<=A; ++i) for (int j=1; j<=B; ++j) {
			char ch=getchar(); while (ch<'0'||ch>'1') ch=getchar(); a[i][j]=ch-'0';
		}
		tdh::init(a, A, B), printf("%d\n", mp[(int)tdh::get(1,1,A,B)]);
	}
	return 0;
}

```

---
### 写在后面
使用 $(x,y)$ 的方式表示行列真的不标准，大家不要学我（  
$p_1$ 表示行内（不同 $y$ 之间）的底，$p_2$ 表示列内（不同 $x$ 之间）的底，为方便理解可自行替换为 $p_x$、$p_y$。

这是蒟蒻的第一篇题解（严格意义上第二篇，因为第一篇没过审），管理员大大手下留情。  
本人高一，因实力太菜马上就要退役了，忽然发现自己一篇题解还没写……于是就有了这篇题解。

这个算法很冷，学了很大概率也用不上，随缘吧。

最后安利一下自己的 [Blog](https://algo-x.cn) QWQ

---

## 作者：JY_cosmos (赞：8)

## 前言
事情的起因是，我在用别的平台上课时碰到了这道题不太会，来这道题在洛谷的题解区转了一圈，发现好像大家的代码都过不了那个平台上的题，有一个点总是 TLE 。在请教完老师后，决定来发一篇题解。
## 本题的主要思路
其实这道题就是一个二维哈希。关于这一点的知识大家可以去看其他的题解，讲的都非常详细。我在这里就只作简单讲解。
```cpp
  //二维 Hash 模板
	p1[0] = p2[0] = 1;
	for (int i = 1; i <= n; i++) p1[i] = p1[i - 1] * P1;
	for (int i = 1; i <= m; i++) p2[i] = p2[i - 1] * P2;
	for (int i = 1; i <= n; i++)
	{
		ULL c = 0;
		scanf("%s", s+1);
		for (int j = 1; j <= m; j++)
		{
		    c = c * P2 + s[j];
		    h[i][j] = h[i - 1][j] * P1 + c;
	    }
	}
//先不用管下面的这个 insert ()
	for (int i = A; i <= n; i++)
		for (int j = B; j <= m; j++)
		    insert(h[i][j] - h[i - A][j] * p1[A] - h[i][j - B] * p2[B] + h[i - A][j - B] * p1[A] * p2[B]);
```
这就是一个很普通的二维 Hash 模板了。二维 Hash 和一维 Hash 大体上是一样的，只不过要采用二维前缀和的思想来运算和求值。
## 时间问题的发现
关于解决时间上的问题，这里使用哈希表会比使用 map 要快，原因也显而易见，map 的每一个操作都有一个无法去除的 log ，这就是导致时间过慢的主要原因。
## 时间问题的解决
上面也说到了，就是使用哈希表。我这里就讲一下本题中使用到的 insert() , 和 find() 函数，对于它的其他用法可以参考 [OI Wiki](https://oi-wiki.org/ds/hash/)。

首先，我要先引入哈希表的概念。哈希表的原理与map类似，都是使用一个关键词（ key ）来查找一个值（ value ）。使用一个数组来建立 key 与 value 的映射关系即可。

  $a[key] = value;$
 
但有些时候 key 并不是一个整数，我们就需要用 Hash 来把它换成整数，可问题出现了。 Hash 值过大时，就没有办法使用数组下标来查找了。因此我们可以取模。


但取模后， key 是很容易重复的（冲突），对于这种情况我们可以这样来办。把同一个 key 的 value 用链表存起来，每次查找值的时候，只需要扫一遍对应 key 的链表即可。


以上所说即为 find() 函数。
```cpp
// find() 函数
int find(ULL x) 
{
	int id = x % mod;
    for (int i = last[id]; i; i = nxt[i])
    	if (num[i] == x) return i;
    return 0;
}
```
好，现在我们把目光移到第一段代码上，注意那个  insert() 函数。 insert() 函数，顾名思义是用来插入的。前面已经提到过，哈希表使用链表来存的，所以此处使用像链表一样的插入方式。
```cpp
// insert() 函数
int insert(ULL x)
{
    //这一步是为了查重，与 find() 函数一致
    int id = x % mod;
    for (int i = last[id]; i; i = nxt[i])
    	if (num[i] == x) return i;

    // num[] 就是存数据的链表， nxt[] 是存指针的， last[] 就是每一个表的头指针。
    num[++cnt] = x;
    nxt[cnt] = last[id];
    last[id] = cnt;
    return cnt;
}
```

**如果你到现在全部看懂了的话，那么恭喜你，你已经会了！**
## 最终代码
这里放上无注释版本的代码，~~方便各位粘贴~~。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;

const int P1 = 10003, P2 = 11117, mod = 1000007, N = 1005;

int n, m, T, A, B;
char s[N];
ULL p1[N], p2[N], h[N][N], num[N * N];
int cnt, last[mod], nxt[N * N];

int find(ULL x) 
{
	int id = x % mod;
    for (int i = last[id]; i; i = nxt[i])
    	if (num[i] == x) return i;
    return 0;
}

int insert(ULL x)
{
    int id = x % mod;
    for (int i = last[id]; i; i = nxt[i])
    	if (num[i] == x) return i;
    num[++cnt] = x;
    nxt[cnt] = last[id];
    last[id] = cnt;
    return cnt;
}

int main()
{
	cin >> n >> m >> A >> B;
	p1[0] = p2[0] = 1;
	for (int i = 1; i <= n; i++) p1[i] = p1[i - 1] * P1;
	for (int i = 1; i <= m; i++) p2[i] = p2[i - 1] * P2;
	for (int i = 1; i <= n; i++)
	{
		ULL c = 0;
		scanf("%s", s+1);
		for (int j = 1; j <= m; j++)
		{
		    c = c * P2 + s[j];
		    h[i][j] = h[i - 1][j] * P1 + c;
	    }
	}
	for (int i = A; i <= n; i++)
		for (int j = B; j <= m; j++)
		    insert(h[i][j] - h[i - A][j] * p1[A] - h[i][j - B] * p2[B] + h[i - A][j - B] * p1[A] * p2[B]);
	
	cin >> T;
	while (T--)
	{
		ULL res = 0;
		for (int i = 1; i <= A; i++)
		{
			scanf("%s", s+1);
			for (int j = 1; j <= B; j++)
				res += s[j] * p1[A - i] * p2[B - j];
		}
		if (find(res)) cout << 1 << endl;
		else cout << 0 << endl;
	}
	return 0;
}
```
## 结语
这是本蒟蒻的第一篇题解，跪求管理员大大给个通过吧！！！如有不当，请各位大佬多多指教！！！！

---

## 作者：harmis_yz (赞：5)

## 分析

二维哈希模板题。

将行和列分开考虑。

先考虑列，则对于不同行，可以将 $n \times m$ 的矩阵看作 $n$ 个长度为 $m$ 的序列，按照一维哈希的方式对其求哈希值。

然后考虑行，则对于不同列，可以将 $n \times m$ 的矩阵看作 $m$ 个长度为 $n$ 的序列。再将上面求的哈希值看作现在每个点的值，按照一维哈希的方式对其求哈希值。

令第一次哈希后点 $(x,y)$ 的哈希值为 $f_{x,y}$，第二次哈希后点 $(x,y)$ 的哈希值为 $g_{x,y}$。则有：

$$f_{x,y}=\sum\limits_{i=1}^{y}a_{x,i} \times P1^{y-i}$$
$$g_{x,y}=\sum\limits_{i=1}^{x}f_{i,y} \times P2^{x-i}$$

求左上角为 $(x1,y1)$，右下角为 $(x2,y2)$ 的矩阵的哈希值，类似于二维前缀和，为：
$$g_{x2,y2}-g_{x1-1,y2}\times P2^{x2-x1+1} - g_{x2,y1-1} \times P1^{y2-y1+1}+g_{x1-1,y1-1} \times P1^{y2-y1+1} \times P2^{x2-x1+1}$$

对于这道题，$A$ 和 $B$ 是一定的，所以就可以将原矩阵中每个 $A \times B$ 的子矩阵的哈希值求出来，拿一个东西把它们标记，然后直接判断这 $Q$ 个矩阵是否被标记过即可。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=1005;
int n,m,q,A,B;
int sP1[N],sP2[N],P1=191,P2=201;
int f[N][N],g[N][N];
int f_[N][N],g_[N][N];
int a[N][N],a_[N][N];
unordered_map<int,bool> vis;

il void solve(){
	n=rd,m=rd,A=rd,B=rd;
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j){
		char ch;cin>>ch;
		a[i][j]=ch-'0'+1; 
	}
	sP1[0]=sP2[0]=1;
	for(re int i=1;i<=max(n,m);++i) 
		sP1[i]=sP1[i-1]*P1,sP2[i]=sP2[i-1]*P2;
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j)
		f[i][j]=(f[i][j-1]*P1+a[i][j]);
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j)
		g[i][j]=(g[i-1][j]*P2+f[i][j]);
	for(re int i=A;i<=n;++i)
	for(re int j=B;j<=m;++j)
		vis[ (g[i][j]) - (g[i-A][j]*sP2[A]) - (g[i][j-B]*sP1[B]) + (g[i-A][j-B]*sP1[B]*sP2[A]) ]=1;
	q=rd;
	for(re int ks=1;ks<=q;++ks){
		for(re int i=1;i<=A;++i)
		for(re int j=1;j<=B;++j){
			char ch;cin>>ch;
			a_[i][j]=ch-'0'+1;
		}
		for(re int i=1;i<=A;++i)
		for(re int j=1;j<=B;++j)
			f_[i][j]=(f_[i][j-1]*P1+a_[i][j]);
		for(re int i=1;i<=A;++i)
		for(re int j=1;j<=B;++j)
			g_[i][j]=(g_[i-1][j]*P2+f_[i][j]);		
		if(vis[g_[A][B]]) puts("1");
		else puts("0");
	}
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}
```

---

## 作者：leiaxiwo (赞：4)

# 题解：P10474 [BeiJing2011] Matrix 矩阵哈希
## 【模版】二维hsah
### [传送门](https://www.luogu.com.cn/problem/P10474)
### 知识点讲解
#### 前置知识
我们先回顾一下**二维前缀和**，例题 [P2280 [HNOI2003] 激光炸弹](https://www.luogu.com.cn/problem/P2280)
，那么我们现在有两个数组要进行差分，不妨令差分数组为 $p$，$a$ 为原数组，由**容斥原理**，我们显然有

$$p[i][j]=p[i-1][j]+p[i][j-1]-p[i-1][j-1]+a[i][j]$$

对于这个公式的证明可以移步 P2280 [HNOI2003] 激光炸弹，里面写的很清楚，笔者就不在赘述了。

那么查询也很显然了，若查询一个子矩阵     $(x_1,x_2,y_1,y_2)$，我们显然有

$$ask(x_1,x_2,y_1,y_2)=p[x_2][y_2]-p[x_1-1][y2]-p[x_2][y_1-1]+p[x_1-1][y_1-1]$$

证明和上述类似。

查询复杂度为 $\Theta(1)$。

#### 二维哈希表的处理方法
我们知道这个之后就好办了，可以将**行和列分开考虑**。

先考虑列，则对于不同行，可以将 $n×m$ 的矩阵看作 $n$ 个长度为 $m$ 的序列，按照一维哈希的方式对其求哈希值。

行也如此，我们就可以解决此题了。

具体的，对于本题，$A$ 和 $B$ 是一定的，所以就可以将原矩阵中每个 $A×B$ 的子矩阵的哈希值求出来，把它们标记，然后直接判断这 
$Q$ 个矩阵是否被标记过即可。

我这里的处理办法和[harmis_yz](https://www.luogu.com.cn/article/ze319g9k)的处理方式一致。

令第一次哈希后点 $(x,y)$ 的哈希值为 $val1_{x,y}$，第二次哈希后点 $(x,y)$ 的哈希值为 $val2_{x,y}$。则有：

$$val1_{x,y}=\sum\limits_{i=1}^{y}a_{x,i} \times base1^{y-i}$$
$$val2_{x,y}=\sum\limits_{i=1}^{x}f_{i,y} \times base2^{x-i}$$

求左上角为 $(x1,y1)$，右下角为 $(x2,y2)$ 的矩阵的哈希值，类似于二维前缀和，为：
$$val2_{x2,y2}-val2_{x1-1,y2}\times base2^{x2-x1+1} - val2_{x2,y1-1} \times base1^{y2-y1+1}+base2_{x1-1,y1-1} \times base1^{y2-y1+1} \times val2^{x2-x1+1}$$

那么这题就结束战斗了。

### 参考代码

```cpp
//-std=c++14
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int base1=13331,base2=131;
int n,m,Q,A,B;
int matrix1[5005],matrix2[5005];
int val1[5005][5005],val2[5005][5005];
int _val1[5005][5005],_val2[5005][5005];
int Original_matrix[5005][5005],_Original_matrix[5005][5005];
map<int,bool> vis;
signed main(){
	matrix1[0]=matrix2[0]=1;
	scanf("%lld%lld%lld%lld",&n,&m,&A,&B);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;++j){
		    char s;
		    cin>>s;
		    Original_matrix[i][j]=s-'0'+1; 
	    }
	}
	for(int i=1;i<=m;i++){
		matrix1[i]=matrix1[i-1]*base1;
		matrix2[i]=matrix2[i-1]*base2;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;++j){
			val1[i][j]=val1[i][j-1]*base1+Original_matrix[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;++j){
		    _val1[i][j]=_val1[i-1][j]*base2+val1[i][j];
	    }
	}
	for(int i=A;i<=n;i++){
		for(int j=B;j<=m;++j){
		    vis[_val1[i][j]-_val1[i-A][j]*matrix2[A]-_val1[i][j-B]*matrix1[B]+_val1[i-A][j-B]*matrix1[B]*matrix2[A]]=1;
	    }
	}	
	scanf("%lld",&Q);
	for(int k=1;k<=Q;k++){
		for(int i=1;i<=A;i++){
			for(int j=1;j<=B;++j){
			    char s;
				cin>>s;
		    	_Original_matrix[i][j]=s-'0'+1;
		    }
		}
		for(int i=1;i<=A;i++){
			for(int j=1;j<=B;++j){
			    val2[i][j]=val2[i][j-1]*base1+_Original_matrix[i][j];
		    }
		}
		for(int i=1;i<=A;i++){
			for(int j=1;j<=B;++j){
			    _val2[i][j]=_val2[i-1][j]*base2+val2[i][j];
		    }
		}			
		if(vis[_val2[A][B]]){
			printf("1\n");
		} 
		else{
			printf("0\n");
		} 
	}
	return 0;
}
```

### 参考文献
[稠密的联通图——二维哈希](https://blog.csdn.net/m0_55678840/article/details/115707519)

[harmis_yz——题解：P10474 [BeiJing2011] Matrix 矩阵哈希](https://www.luogu.com.cn/article/ze319g9k)

---

## 作者：DDD_et (赞：3)

# P10474 Solution

**做法：哈希**

## 题意

（为方便，题目中的变量名从大写字母改为对应的小写字母，并将题目中的 $M$ 和 $N$ **调换**）

给定 $n \times m$ 的 01 矩阵和 $a,b$。有 $q$ 次询问，每次询问给出一个 $a \times b$ 的矩阵，求该矩阵在原矩阵中是否出现过。

## 思路

话说题解区怎么都是双哈希啊，我来一发递推做法。

### 前置芝士

**字符串哈希**：将字符串看做一个 $P$ 进制数并对 $M$ 取模，通常取 $P$ 为一个大质数，取 $M=2^{32}$ 或 $2^{64}$，利用无符号整型自然溢出取模，这里我选 $P=131,M=2^{64}$。

**字符串哈希求法：** 就是类似于转进制，详细见代码。

**字符串哈希用处：** 一般会给定一个字符串 $s$ 和整数 $l,r$，求 $s_l \sim s_r$ 的哈希值，将时间复杂度降为 $\mathcal{O}(1)$。

由于是前置芝士，所以还不懂可以去看[什么是哈希？](https://oi-wiki.org/ds/hash/)

---

现在回到本题。

设 $h(i,l,r)$ 为整个大矩阵第 $i$ 行从下标为 $l$ 的值到下标为 $r$ 的值的哈希值。

要求矩阵是否出现，那么我们可以预处理 $n \times $ 的大矩阵中所有 $a \times b$ 的小矩阵的哈希值，询问时求出给定矩阵的哈希值，放入哈希表看是否出现过就好了。

问题来了：直接枚举所有小矩阵的时间复杂度为 $\mathcal{O}((n-a) \times (m-b))$，即 $\mathcal{O}(nm)$，会超时，怎么办呢？

思考发现可以枚举外层 $i \in [b,m]$，即列数，确定枚举的矩阵的左端点 $l=i-b+1$，右端点 $r=i$。然后在内部枚举 $j \in [1,a]$ 来递推当前哈希值。

由于内部用来递推的是行数，所以相当于一个矩阵在慢慢向下移；就像：

![图 床 又 出 问 题 了](https://cdn.luogu.com.cn/upload/image_hosting/crx5tsca.png)

那么如何通过上一次的值推出该次的值呢？

![图 床 又 出 问 题 了](https://cdn.luogu.com.cn/upload/image_hosting/gpvl8gtx.png)

如图，用「当前求出来的」（设其为 $s$）$-$ ① $+$ ② 就是「要求的」；而根据字符串哈希的定义，① $=h(j-a,l,r)^{a\times b}$，② $=h(j,l,r)$（变量均已在上方定义，乘方为 $P$ 进制下），那么类比进制转换，将 $s$ 变为 $s^b$ 后就留出了 $b$ 个 $P$ 进制下的 $0$，则「要求的」$=s^b+h(j,l,r)-h(j-a,l,r)^{a\times b}$。

**为什么 ① 的指数是 ${a \times b}$ ?** 因为这是个矩阵哈希，$a \times b$ 代表前面的矩阵。

然后结合字符串哈希的基本知识，就可以愉快的写代码啦（更多细节见代码）。

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
//ull是用无符号长整型的自然溢出，即M=2^64
const int N = 1e3 + 10, M = N * N, P = 131;
int m, n, a, b, q;
ull h[N][N], p[M];
char tc[N];

//模版
ull sec_has (ull h[], int l, int r)
{ return h[r] - h[l - 1] * p[r - l + 1]; }

int main ()
{
    cin >> n >> m >> a >> b;
    //注意：n,m颠倒了，但不知道是不是数据过水导致没颠倒好像也能过（
	p[0] = 1;
	for (int i = 1; i <= m * m; i ++) p[i] = p[i - 1] * P;
    //预处理所有乘方
	for (int i = 1; i <= n; i ++)
	{
		cin >> tc + 1;
		for (int j = 1; j <= m; j ++)
			h[i][j] = h[i][j - 1] * P + tc[j] - '0';
	}
	unordered_set <ull> hash;
    //用来去重，unordered是因为这样快一些
	for (int i = b; i <= m; i ++)
	{
		ull sum = 0;
		int l = i - b + 1, r = i;
		for (int j = 1; j <= n; j ++)
		{
			sum = sum * p[b] + sec_has (h[j], l, r);
            //只有j是在能组成a*b的矩阵范围内才相减并记录答案
			if (j > a) sum = sum - sec_has (h[j - a], l, r) * p[a * b];
			if (j >= a) hash.insert (sum);
		}
	}
	cin >> q;
	while (q --)
	{
		ull sum = 0;
		for (int i = 1; i <= a; i ++)
		{
			cin >> tc + 1;
			for (int j = 1; j <= b; j ++)
				sum = sum * P + tc[j] - '0';
		}
		if (hash.count (sum)) puts ("1");
		else puts ("0");
	}
	return 0;
}
```

### 写在最后

这题的概念全写出来有些抽象，请读者尽量通过自身理解来做这道题。

~~话说是不是双哈希其实更简单啊。~~

**谢谢观看！**

---

## 作者：xrz114514 (赞：2)

# P10474 题解

## 题面

给定一个 $N$ 行 $M$ 列的 $01$ 矩阵，有 $Q$ 次询问，每次询问给出一个 $A$ 行 $B$ 列的 $01$ 矩阵，问其是否在原矩阵中出现过。

## 思路

以此题解纪念我通过 5 个小时的自学终于学会了二维哈希！！！

### 🧀 1：一维哈希

对于一串序列，如何进行哈希讲它压成一个好处理的数呢。我们可以将其看作是一个 $b$ 进制的数，每一位即使序列中的一个数。不过这样的得出的数为高精数，但是可以对其进行取模。设前 $i$ 得出的哈希值为 ${hash}_i$，根据定义可知，$[i,j]$ 区间的哈希值为 ${hash}_j - {hash}_{i - 1} \times b ^ {j - i + 1}$。

### 🧀 2：二维哈希

回归这道题，可以定义 $H_{i,j}$ 表示右下角为 $(i,j)$ 且大小为 $A \times B$ 的**矩阵哈希**值。但我们不会对矩阵进行哈希啊。不妨这样想，对于一个矩阵，我们先对每行以 $b_1$ 求解一次一维哈希，这样每行就被压成了一个数，把他们组成一个序列再以 $b_2$ 为第做一次一维哈希，所得的结果即是这个矩阵的哈希值。想到这里，$H$ 的转移也出来了：$H_{i,j} = H_{i - 1,j} \times b_2 + hash_{i,[j-b+1,j]} - hash_{i - a,[j-b+1,j]}$。表示右下角为 $(i,j)$ 的矩形的哈希值可以由右下角为 $(i - 1, j)$ 矩形的哈希值左移一位，再加上这一行的哈希值，此时多出了一行，就将其减掉，最后的结果即是右下角为 $(i,j)$ 且大小为 $A \times B$ 的矩阵哈希值。\
可以开个 `map` 记录所有的 $A \times B$ 的矩阵的哈希值，最后查询时对给定的矩形求一遍哈希并输出 `map` 中是否出现这个哈希值即可。

## 代码

```cpp
/*#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-funsafe-loop-optimizations")*/
#include <bits/stdc++.h>
#include <bits/extc++.h>
//#include <windows.h>
#define pque priority_queue
#define fi first
#define se second
#define un unsigned
#define si signed
//#define int long long

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using LL = unsigned long long;
using Int = unsigned int;
using ld = double;
using Ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int N = 1e3 + 1, Mod[2] = {998244353, (int)1e9 + 7}, Base[2] = {19260817, 1145141};

int n, m, a, b, q, h[N][N][2], H[N][N][2], Pow[N * N][2];
char c[N][N], qq[N][N];
map<pii, int> mp;

void Init(){
	for(int _ : {0, 1}){
		Pow[0][_] = 1;
	}
	for(int i = 1; i < N * N; ++i){
		for(int _ : {0, 1}){
			Pow[i][_] = 1ll * Pow[i - 1][_] * Base[_] % Mod[_];
		}
	}
}

pii Query(int r, int hl, int hr){
	int res[2] = {0, 0};
	for(int _ : {0, 1}){
		res[_] = (h[r][hr][_] - 1ll * h[r][hl - 1][_] * Pow[hr - hl + 1][_] % Mod[_] + Mod[_]) % Mod[_];
	}
	return {res[0], res[1]};
}

int main(){
	//freopen("","r", stdin);
	//freopen("", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m >> a >> b;
	Init();
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= m; ++j){
			cin >> c[i][j];
			for(int _ : {0, 1}){
				h[i][j][_] = (1ll * h[i][j - 1][_] * Base[_] + c[i][j] - '0' + 1) % Mod[_];
			}
		}
	}
	for(int i = 1; i <= n; ++i){
		for(int j = b; j <= n; ++j){
			int res[2] = {Query(i, j - b + 1, j).fi, Query(i, j - b + 1, j).se};
			int x[2];
			if(i >= a){
				x[0] = Query(i - a, j - b + 1, j).fi, x[1] = Query(i - a, j - b + 1, j).se;
			}else{
				x[0] = 0, x[1] = 0;
			}
			for(int _ : {0, 1}){
				H[i][j][_] = ((1ll * H[i - 1][j][_] * Pow[b][_] % Mod[_] - 1ll * x[_] * Pow[a * b][_] % Mod[_] + Mod[_]) % Mod[_] + res[_]) % Mod[_];
			}
			if(i >= a && j >= b){
				mp[{H[i][j][0], H[i][j][1]}] = 1;
			}
		}
	}
	cin >> q;
	while(q--){
		int has[2] = {0, 0};
		for(int i = 1; i <= a; ++i){
			for(int j = 1; j <= b; ++j){
				cin >> qq[i][j];
				for(int _ : {0, 1}){
					has[_] = (1ll * has[_] * Base[_] + qq[i][j] - '0' + 1) % Mod[_];
				}
			}
		}
		cout << mp[{has[0], has[1]}] << '\n';
	}
	return 0;
}
```

---

## 作者：a18981826590 (赞：2)

# [P10474 [BeiJing2011] Matrix 矩阵哈希](https://www.luogu.com.cn/problem/P10474)
## 前置知识
[字符串哈希](https://oi-wiki.org/string/hash/)：  
1. 我们把一个字符串看做一个 $P$ 进制数（$P$ 为质数，如 $131,13331,1145141,1145143$），并给每种字符分配一个 $\ge 0$ 的值。为了将这个很大的 $P$ 进制数映射到一个较小的值域，我们需要将其模一个数 $M$，通常为 $2^{64}$，即直接用 `unsigned long long int` 来进行存储；
2. 已知字符串 $S$ 的哈希值为 $H(S)$，字符串 $T$ 的哈希值为 $H(T)$，字符串 $T$ 的长度为 $|T|$，则字符串 $S+T$ 的哈希值为 $(H(S)\times P^{|T|}+H(T)) \bmod M$；
3. 已知字符串 $S$ 的哈希值为 $H(S)$，字符串 $S+T$ 的哈希值为 $H(S+T)$，则字符串 $T$ 的哈希值为 $H(S+T)-H(S)\times P^{|T|}$；
4. 预处理出字符串 $S$ 的前缀子串 $T_{1,i}(1 \le i \le |S|)$ 的哈希值 $H(T_{1,i})(1 \le i \le |S|)$，$O(1)$ 时间复杂度求 $H(T_{x,y})=H(T_{1,y})-H(T_{1,x-1})\times P^{y-x+1} (1 \le x \le y \le |S|)$。
## 解题思路
结合字符串哈希和二维前缀和来求矩阵哈希，按行哈希底数为 $p_{1}$，按列哈希底数为 $p_{2}$，模数为 $Mod$。

首先求出原矩阵 $a$ 左上角和任一点 $(i,j)(1 \le i \le M,1 \le j \le N)$ 作为右下角的子矩阵的哈希值 $b_{i,j}=(a_{i,j}+b_{i-1,j}*p_{1}+b_{i,j-1}*p_{2}-b_{i-1,j-1}*p_{1}*p_{2}) \bmod Mod$。

枚举原矩阵中每个 $A$ 行 $B$ 列的子矩阵，令其右下角为 $(i,j)(A \le i \le M,B \le j \le N)$，该子矩阵的哈希值 $c_{i,j}=(b_{i,j}-b_{i-A,j} \times {p_{1}}^{A}-b_{i,j-B} \times {p_{2}}^{B}+b_{i-A,j-B} \times {p_{1}}^{A} \times {p_{2}}^{B}) \bmod Mod$，将该子矩阵的哈希值存入 `map`，便于后续比较。

对于询问的每个矩阵，使用和求原矩阵相同的方法求出其哈希值，查找 `map` 中是否存在即可。
## [AC](https://www.luogu.com.cn/record/202625137) 代码
其中 $p_{1}=1145141$，$p_{2}=1145143$，均为质数，$M=2^{64}$，即直接使用 `unsigned long long int` 对哈希值进行存储，使用溢出代替取模。
```cpp
#include<bits/stdc++.h>
#define int unsigned long long int
const int P1=1145141,P2=1145143;
using namespace std;
int a,b,c[1010][1010],d[1010][1010],e[1010][1010],f[1010][1010],m,n,p1[1010]={1},p2[1010]={1},q;
char z;
map<int,bool>zz;
signed main(){
	ios::sync_with_stdio(0);
	cin>>m>>n>>a>>b;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			cin>>z;
			c[i][j]=z-47;
			e[i][j]=c[i][j]+e[i-1][j]*P1+e[i][j-1]*P2-e[i-1][j-1]*P1*P2;
		}
	}
	for(int i=1;i<=a;i++) p1[i]=p1[i-1]*P1;
	for(int i=1;i<=b;i++) p2[i]=p2[i-1]*P2;
	for(int i=a;i<=m;i++){
		for(int j=b;j<=n;j++) zz[e[i][j]+e[i-a][j-b]*p1[a]*p2[b]-e[i-a][j]*p1[a]-e[i][j-b]*p2[b]]=1;
	}
	cin>>q;
	while(q--){
		for(int i=1;i<=a;i++){
			for(int j=1;j<=b;j++){
				cin>>z;
				d[i][j]=z-47;
				f[i][j]=d[i][j]+f[i-1][j]*P1+f[i][j-1]*P2-f[i-1][j-1]*P1*P2;
			}
		}
		cout<<zz[f[a][b]]<<'\n';
	}
	return 0;
}
```

---

## 作者：Clarinet (赞：2)

# 简要题意
给定一个基本 $01$ 矩阵和 $Q$ 个小 $01$ 矩阵，若小的 $01$ 矩阵在大的中出现过则输出 $1$，否则输出 $0$。
# 分析
一道比较模版的二维字符串哈希，如果不懂哈希算法的话可以去试一下[这道模板题](https://www.luogu.com.cn/problem/P3370)。

大致思路就是用两个数组来记录横向的 $base$ 值，然后分别横向竖向更新一下哈希值，最后枚举符合 $A$ 行 $B$ 列的矩阵并用 map 记录一下。

分别计算输入的小矩阵的哈希值并判断一下就可以轻松解决这道题目了。

我发这个题解的目的主要是题解区的码风都很高级，于是蒟蒻想用自己的码风帮助一下大家。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int base1=131,base2=13331;
long long n,m,q,a,b,mt[5010][5010],s[5010][5010],l1[5010],l2[5010];
map<long long,bool> ttpd;
void handle(long long ll,long long rr){
	for(int i=1;i<=ll;i++){
		for(int j=1;j<=rr;j++){
			char s;
			cin>>s;
			mt[i][j]=s-'0'+1;
		}
	}
	for(int i=1;i<=rr;i++){
		l1[i]=l1[i-1]*base1;
		l2[i]=l2[i-1]*base2;
	}
	for(int i=1;i<=ll;i++){
		for(int j=1;j<=rr;j++){
			s[i][j]=s[i][j-1]*base1+mt[i][j];
		}
	}
	for(int i=1;i<=ll;i++){
		for(int j=1;j<=rr;j++){
			s[i][j]+=s[i-1][j]*base2;
		}
	}
}
int main(){
	l1[0]=l2[0]=1;
	cin>>n>>m>>a>>b;
	handle(n,m);
	for(int i=a;i<=n;i++){
		for(int j=b;j<=m;j++){
			ttpd[s[i][j]-s[i-a][j]*l2[a]-s[i][j-b]*l1[b]+s[i-a][j-b]*l2[a]*l1[b]]=1;
		}
	}
	cin>>q;
	for(int k=1;k<=q;k++){
		handle(a,b);
		if(ttpd[s[a][b]])cout<<1<<endl;
		else cout<<0<<endl;
	}
	return 0;
}
```
感谢阅读！

---

## 作者：jiangby2011 (赞：2)

# 题解: P10474 Matrix矩阵哈希
## 前言
#### 可以先做一下这道哈希板子，有助于思考本题。
[P3370传送门](https://www.luogu.com.cn/problem/P3370)
## BKDRHash(会的直接跳）
在两个字符串的比较中，如果我们暴力地比较，效率是很低的。

因此，我们可以通过特定的函数加工，使得这些字符串通过相同方式直接被加密成一个非负整数。用这些数比较、修改十分方便。

举个栗子，在判断是否相同时， abcd 和 abcd 两个串通过加工变成 1234 和 1234，就可以直接比较啦。实际问题往往比这个复杂许多，因此，你只需要知道，哈希十分有用。

然而哈希也有问题，比如哈希冲突(两个不同的串有相同的哈希值)。

#### 那么，如何才能设计错误极少的哈希函数呢？

我们可以将一个字符串视作特定进制数（随便取），并且拿 askII 码转换，取左为高位。

**进制最好取个质数，这里取 131。**

具体操作看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[1010];//字符串
const int B=131;//进制
int ans=0,n;
inline unsigned long long Hash()
{
	unsigned long long k=0;
	for(int i=0;i<strlen(s);i++)
	{
		k+=(k*B+（unsigned long long)(s[i]));
//乘上B就是把B进制数整体左移一位
//加上s[i]就是加上新的一位
	}
	return k;
}
int main()
{
	return 0;
}
```
看懂了话可以回归本题了。


## 题意分析
### 二维哈希板子

通过两次哈希，先将二维序列哈希成一维，再将一维序列哈希成一个数，之后比较就会很方便。

## 具体实现
### 第一部分 双哈希

```cpp
for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			hum1[i][j]=hum1[i][j-1]*B1+ma[i][j];//先把横着的Hash了
		}
	}
	for(int j=1;j<=n;j++)
	{
		for(int i=1;i<=m;i++)
		{
			hum2[i][j]=hum2[i-1][j]*B2+hum1[i][j]; //再把竖着的Hash了
		}
	}	
```
跟上一部分我贴的代码很像吧。
### 第二部分 子矩阵哈希值
不难发现，我们刚才的代码只能求覆盖左上角的二维序列，如果这个二维序列不覆盖左上角，我们怎么办呢？

这一部分是全题思维难度最高的东西，因此其他题解讲的比较完善。大概就是通过一系列二维序列哈希值加减求得，由于我不会做图，这部分具体可以看第一篇题解

看完之后，这里主要解释一下我一开始没看懂时出现的问题，希望有所帮助。

一.为啥二维序列哈希值能加减

哈希值本质上其实就是同一进制的数，所以完全可以加减。

二.为啥加减时要乘进制数

这个和上一个问题有关系。如果我们直接加减，这些二维序列的最高位是不对等的，需要对齐这些哈希值。

### 第三部分 完整代码与注意事项

献上丑陋代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int maxn=1e3+7;
const int B1=131;
const int B2=13331;
int m,n,a,b,p;
ull ma[maxn][maxn];
ull M[maxn][maxn];
ull hum1[maxn][maxn],hum2[maxn][maxn],hum3[maxn][maxn],hum4[maxn][maxn];
ull p1[maxn],p2[maxn];
map<ull,bool> v;
void init(ull ma[maxn][maxn],int m,int n)
{
	p1[0]=p2[0]=1;
	for(int i=1;i<=maxn;i++)
	{
		p1[i]=p1[i-1]*B1;
		p2[i]=p2[i-1]*B2;
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			hum1[i][j]=hum1[i][j-1]*B1+ma[i][j];
		}
	}
	for(int j=1;j<=n;j++)
	{
		for(int i=1;i<=m;i++)
		{
			hum2[i][j]=hum2[i-1][j]*B2+hum1[i][j];
		}
	}	
}
inline ull get(int x1,int y1,int x2,int y2)
	{
		return hum2[x2][y2]-hum2[x1-1][y2]*p2[x2-x1+1]-hum2[x2][y1-1]*p1[y2-y1+1]+hum2[x1-1][y1-1]*p1[y2-y1+1]*p2[x2-x1+1];
//求一个不覆盖左上角的二维序列哈希值
	}
int main()
{
	cin>>m>>n>>a>>b;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			char c;
			cin>>c;
			ma[i][j]=c-'0';
		}
	}
	init(ma,m,n);
	for(int i=1;i+a<=m+1;i++)
	{
		for(int j=1;j+b<=n+1;j++)
		{
			ull k=get(i,j,i+a-1,j+b-1);
			v[k]=1;
		}
	}
	cin>>p;
	while(p--)
	{
		for(int i=1;i<=a;i++)
		{
			for(int j=1;j<=b;j++)
			{
				char c;
				cin>>c;
				M[i][j]=c-'0';
			}
		}
		init(M,a,b);
		ull t=get(1,1,a,b);
		cout<<v[t]<<"\n";
	}
	return 0;
}
```
注意，我一开始查询时间复杂度错了因此得了 91 分，每次查询不应该是 $O(n)$ 的，因此应该用 map 做比较好一些。

---

## 作者：sLMxf (赞：1)

前置：hash。

为什么要二维前缀和？
# P10474 [ICPC-Beijing 2011] Matrix 矩阵哈希
## 1.1 简述题意
给定一个 $M$ 行 $N$ 列的 $01$ 矩阵，以及 $Q$ 个 $A$ 行 $B$ 列的 $01$ 矩阵，你需要求出这 $Q$ 个矩阵哪些在原矩阵中出现过。
## 1.2 算法分析
我们考虑一个这样的做法：暴力枚举 $i,j$，然后每次检查 $(i,j)\sim(i+a-1,i-b+1)$ 这个子矩阵和查询矩阵是否相同。

这样的时间复杂度高达 $O(nmabq)$。必须优化。

首先外面枚举 $i,j$ 至少从现在开始，是不可能优化的，但是里面的判断相等，却可能优化。如果我们能在 $O(1)$ 内判断两个矩阵是否相同，就只有 $O(nmq)$ 了。

$O(1)$ 内判断两个矩阵是否相同？可能吗？回顾之前，我们在判断两个字符串是否相同的时候，也遇到过这个问题，当时我们使用了字符串哈希。

这里是同样的套路，我们将一个矩阵压成一个数就可以了。

可是我们只能将一个序列压成一个数，如何将一个 $a\times b$ 的矩阵压成一个数？

一个矩阵可以看作 $a$ 个长度为 $b$ 的序列构成。我们先将这 $a$ 个序列压成一个数，这样就只剩下一个长度为 $a$ 的序列了，再压一次就可以了。代码实现如下：
```cpp line-numbers
int check()
{
	unsigned long long hsh=0;
	for(int i=1;i<=a;i++)
	{
		for(int j=1;j<=b;j++)
			Hash[i][j]=Hash[i][j-1]*131+mb[i][j]-'0';
	}
	for(int i=1;i<=a;i++)
	{
		hsh=hsh*13331+get(i,1,b);
	}
	return hsh;
}
```
这样我们就只剩下一个 $O(nmq)$ 的问题了，考虑将这个 $n\times m$ 的矩阵所有大小为 $a\times b$ 的矩阵所对应的 hash 值先找出来，时间复杂度 $O(nm)$：
```cpp line-numbers
void init()
{
    mp[0]=1;
	pw[0]=pw1[0]=1;
	for(int i=1;i<=max(m,n);i++) pw[i]=pw[i-1]*131;
	for(int i=1;i<=max(m,n);i++) pw1[i]=pw1[i-1]*13331;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
			Hash[i][j]=Hash[i][j-1]*131+ma[i][j]-'0';
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j+b-1<=n;j++)
		{
			sz[i][j]=get(i,j,j+b-1);
			sz[i][j]=sz[i-1][j]*13331+sz[i][j];
		}
	}
	for(int i=1;i+a-1<=m;i++)
	{
		for(int j=1;j+b-1<=n;j++)
		{
			Sz[i][j]=git(j,i,i+a-1);
			mp[Sz[i][j]]=1;
		}
	}
}
```

这样询问时我们压完的矩阵直接在 map 里找一下即可，时间复杂度 $O(nm+qab)$，可以通过：
## 1.3 代码实现
```cpp line-numbers
#include<bits/stdc++.h>
using namespace std;
char ma[1005][1005],mb[1005][1005];
unsigned long long Hash[1005][1005],pw[1005],sz[1005][1005],Sz[1005][1005],pw1[1005];
int m,n,a,b;
unordered_map<unsigned long long,bool>mp;
unsigned long long get(int w,int l,int r)
{
	return Hash[w][r]-Hash[w][l-1]*pw[r-l+1];
}
unsigned long long git(int w,int l,int r)
{
	return sz[r][w]-sz[l-1][w]*pw1[r-l+1];
}
void init()
{
    mp[0]=1;
	pw[0]=pw1[0]=1;
	for(int i=1;i<=max(m,n);i++) pw[i]=pw[i-1]*131;
	for(int i=1;i<=max(m,n);i++) pw1[i]=pw1[i-1]*13331;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
			Hash[i][j]=Hash[i][j-1]*131+ma[i][j]-'0';
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j+b-1<=n;j++)
		{
			sz[i][j]=get(i,j,j+b-1);
			sz[i][j]=sz[i-1][j]*13331+sz[i][j];
		}
	}
	for(int i=1;i+a-1<=m;i++)
	{
		for(int j=1;j+b-1<=n;j++)
		{
			Sz[i][j]=git(j,i,i+a-1);
			mp[Sz[i][j]]=1;
		}
	}
}
bool check()
{
	unsigned long long hsh=0;
	for(int i=1;i<=a;i++)
	{
		for(int j=1;j<=b;j++)
			Hash[i][j]=Hash[i][j-1]*131+mb[i][j]-'0';
	}
	for(int i=1;i<=a;i++)
	{
		hsh=hsh*13331+get(i,1,b);
	}
	return mp[hsh];
}
signed main()
{
	cin>>m>>n>>a>>b;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			cin>>ma[i][j];
	init();
	int q;
	cin>>q;
	while(q--)
	{
		for(int i=1;i<=a;i++)
			for(int j=1;j<=b;j++)
				cin>>mb[i][j];
		cout<<check()<<'\n'; 
	}
	return 0;
}
```

---

## 作者：Clare613 (赞：1)

## 思路：
一道很好的哈希题，关键在于怎么写。其实我们可以发现，哈希一般都是一维的，而现在发现竟然是二维的。很明显，我们需要将二维的矩阵转为一维。\
怎么转呢？我们先看一下样例，按表格来画像这样：\
![](https://cdn.luogu.com.cn/upload/image_hosting/ggbes2vg.png)\
很明显，虽然一整个矩阵哈希值不好求小矩阵的哈希值，但我们可以对于每一行来求一次，使得每一行都为单独的一个，经过计算可以得到如下的 $a_{i,j}$ 的表格：\
![](https://cdn.luogu.com.cn/upload/image_hosting/7wz39qv6.png)\
接着，假设我现在要求矩阵左上角为 $(1,1)$，右下角为 $(2,2)$ 的小矩形，我们就可以用第一行的前两个和第二行的前两个加起来，如下：\
![](https://cdn.luogu.com.cn/upload/image_hosting/1bqhdury.png)\
那么现在我们再看一下题，它要我们求的是是否存在，也就是说我们需要全部找一遍。但是可以发现，如果每一个都单独算的话会超时，那么我们如何转移？\
转移的关键其实是我们的上下两行，比如说上图的 $1,3$ 行，其实可以直接转下来，也就是变成这样：\
![](https://cdn.luogu.com.cn/upload/image_hosting/ilvsfx1w.png)\
其中红色表示删除部分。那么删除这一行时，就要注意它多乘了多少个 $P$，要删除掉。再次看一下题目，可以发现它的子矩阵大小是固定的，于是我们就需要预处理一下，不然会超时，然后就没有什么了。
## code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1005][1005],pw[1000005];
int hashh(int id,int l,int r){
	return a[id][r]-a[id][l-1]*pw[r-l+1];
}
map<int,int> f;
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0)->sync_with_stdio(0);
	int n,m,A,B;
	cin>>n>>m>>A>>B;
	pw[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char x;
			cin>>x;
			a[i][j]=a[i][j-1]*13331+x;
			pw[(i-1)*m+j]=pw[(i-1)*m+j-1]*13331;
		}
	}
	for(int i=1;i<=m-B+1;i++){
		int num=0;
		for(int j=1;j<=A;j++){
			num=num*pw[B]+hashh(j,i,i+B-1);
		}
		f[num]=1;
		for(int j=A+1;j<=m;j++){
			num=num-pw[(A-1)*B]*hashh(j-A,i,i+B-1);
			num=num*pw[B]+hashh(j,i,i+B-1);
			f[num]=1;
		}
	}
	int q;
	cin>>q;
	while(q--){
		int s=0;
		for(int i=1;i<=A;i++){
			for(int j=1;j<=B;j++){
				char x;
				cin>>x;
				s=s*13331+x;
			}
		}
		if(f[s]==1) cout<<"1\n";
		else cout<<"0\n";
	}
	return 0;
}
```

---

## 作者：WaterSky (赞：1)

# [P10474 [BeiJing2011] Matrix 矩阵哈希](https://www.luogu.com.cn/problem/P10474)
这道题是矩阵哈希模板，单讲题目没什么意思，那就讲解一下矩阵哈希。
## 前置知识：
字符串哈希。
## 矩阵哈希：
什么是矩阵哈希（含义）？

在了解什么是**矩阵哈希**之前要先明白**字符串哈希**是什么。
> 我们定义一个把字符串映射到整数的函数 $f$，这个 $f$ 称为是 $\text{Hash}$ 函数，也叫哈希。而哈希的核心思想在于，将输入映射到一个值域较小、可以方便比较的范围。
[具体见这里。](https://oi.wiki/string/hash/#%E6%80%A7%E8%B4%A8)

同理，矩阵哈希就是将一个矩阵映射到整数的函数，也可以称为二维哈希，当我们遇到数据比较大，不允许暴力遍历矩阵的时候就可以使用矩阵哈希优化时间复杂度。

### 如何实现（实现过程）？
矩阵哈希又叫二维哈希，那肯定有一维哈希，那就先看看一维哈希是怎么实现的。

----
#### 一维哈希实现过程：
![](https://cdn.luogu.com.cn/upload/image_hosting/3dzzgpo8.png)

在一维哈希中，我们是将长度为 $m$ 的序列哈希为一个长度为 $m$ 的一个 $P$ 进制数（高位在前）。

----
#### 二维哈希实现过程：
![](https://cdn.luogu.com.cn/upload/image_hosting/r1cl09qw.png)

可以发现，二维哈希实际上就是由 $n$（行数）个一维哈希哈希得到的一个 $n$ 进制数（高位在前）。

---
#### 处理过程：
1. 行哈希：首先对矩阵每一行的 $n$ 个元素分别进行一维哈希。
2. 列哈希：接着将矩阵的每一行视为一位，从上到下视作一个由 $n$ 个元素组成的序列，类比一维哈希。

---

#### 公式推导：求在一个大小为 $n \times m$ 的矩阵中大小为 $a \times b$ 的矩阵哈希值。
1. 预先处理整个矩阵每一行的哈希值。设第 $i$ 行第 $j$ 列的元素为 $a_{i,j}$，则第 $i$ 行前 $j$ 列的哈希值：$h_{i,j}=h_{i,j-1}\times P+a_{i,j}$。
2. 再求 $a \times b$ 矩阵的哈希值。设右下角下标的为 $(i,j)$ 的 $a \times b$ 矩阵的哈希值为 $H_{i,j}$。再用以上方法求出每一行的 $b$ 个元素的哈希值。则其对应的第 $i+1$ 行的 $a \times b$ 的矩阵的哈希值 $H_{i+1,j}$ 可以由该矩阵的所有元素向高位移高 $b$ 位，再加上第 $i+1$ 行的哈希值，再减去第 $i$ 个矩阵的第 $1$ 行的哈希值得到。即：
$$H_{i+1,j}=H_{i,j}\times p^b+h_{i+1,(j-b+1,j)}-h_{i+1-a,(j-b+1,j)}\times p^{ab}$$
![](https://cdn.luogu.com.cn/upload/image_hosting/dbdtyf5r.png)

-----
回归题目，对于这道题，$A$ 与 $B$ 是一定的，所以就可以求出原矩阵中每个 $A\times B$ 的子矩阵的哈希值，将它们标记，然后直接判断这 $Q$ 个矩阵是否被标记过即可。

## 代码实现（~~累了，就~~不打注释了，有疑问私信或评论）：
```
#include<bits/stdc++.h>
using namespace std;
long long n,m,Q,A,B;
long long m1[5015],m2[5015];
long long v1[5015][5015],v2[5015][5015],_v1[5015][5015],_v2[5015][5015];
long long M[5015][5015],_M[5015][5015];
map<long long,bool> vis;
int main(){
	m1[0]=m2[0]=1;
	scanf("%lld%lld%lld%lld",&n,&m,&A,&B);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;++j){
		    char s;
		    cin>>s,M[i][j]=s-'0'+1; 
	    }
	for(int i=1;i<=m;i++)
		m1[i]=m1[i-1]*13331,m2[i]=m2[i-1]*1331;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;++j)
			v1[i][j]=v1[i][j-1]*13331+M[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;++j)
		    _v1[i][j]=_v1[i-1][j]*1331+v1[i][j];
	for(int i=A;i<=n;i++)
		for(int j=B;j<=m;++j)
		    vis[_v1[i][j]-_v1[i-A][j]*m2[A]-_v1[i][j-B]*m1[B]+_v1[i-A][j-B]*m1[B]*m2[A]]=1;
	scanf("%lld",&Q);
	for(int k=1;k<=Q;k++){
		for(int i=1;i<=A;i++)
			for(int j=1;j<=B;++j){
			    char s;
				cin>>s,_M[i][j]=s-'0'+1;
		    }
		for(int i=1;i<=A;i++)
			for(int j=1;j<=B;++j)
			    v2[i][j]=v2[i][j-1]*13331+_M[i][j];
		for(int i=1;i<=A;i++)
			for(int j=1;j<=B;++j)
			    _v2[i][j]=_v2[i-1][j]*1331+v2[i][j];
		if(vis[_v2[A][B]]) cout<<1<<endl;
		else cout<<0<<endl;
	}
	return 0;
}
```
最后：

我也是刚学，所以这篇题解可能会有一些错误，请在评论区指出，感谢！

---

## 作者：Liyunze123 (赞：0)

### 思路和暴力
最暴力的思路：预处理原矩阵每行的哈希值，处理新矩阵每一行的哈希值，枚举匹配位置的左上角，$O(a)$ 的逐行匹配，不卡哈希。$91$ 分，一个点超时。下载数据后实测七秒多一点。
```
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,m,N,M,q,h[1010][1010],h2[110][510],p[1010];
char a[1010],b[510];
int get(int i,int l,int r){return (h[i][r]-1ll*p[r-l+1]*h[i][l-1]%mod+mod)%mod;}
int main(){
	scanf("%d%d%d%d",&n,&m,&N,&M);p[0]=1;
	for(int w=1;w<=1000;w++)p[w]=p[w-1]*2%mod;
	for(int w=1;w<=n;w++){
		scanf("%s",a+1);
		for(int x=1;x<=m;x++)h[w][x]=(2*h[w][x-1]+a[x]-'0')%mod;
	}
	scanf("%d",&q);
	while(q--){
		for(int w=1;w<=N;w++){
			scanf("%s",b+1);
			for(int x=1;x<=M;x++)h2[w][x]=(2*h2[w][x-1]+b[x]-'0')%mod;
		}
		int t=0;
		for(int w=1;w<=n-N+1&&!t;w++)for(int x=1;x<=m-M+1;x++){
			int k=1;
			for(int y=1,z=w;y<=N;y++,z++)if(h2[y][M]!=get(z,x,x+M-1)){k=0;break;}
			if(k){t=1;break;}
		}
		printf("%d\n",t);
	}
	return 0;
}
```
### 优化
读入是可以优化的。询问总读入量 $Q \times a \times b=5 \times 10^7$，用 `getchar` 优化。变量 $k$ 和 $t$ 改成 `bool` 类型，跑了六点五秒多一点。

我在某篇文章里看到 `unsigned` 部分运算会快一点，用 `unsigned` 优化后跑到六点二秒。

对输入原矩阵也用 `getchar`。跑到六秒。

另外 `get` 函数放到主函数，减少函数调用，跑到五点五秒左右。
```
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,m,N,M,q,h[1010][1010],h2[110],p[1010];
char a[1010],b[510];
int main(){
	//freopen("4.in","r",stdin);
	scanf("%d%d%d%d",&n,&m,&N,&M);p[0]=1;
	for(int w=1;w<=M;w++)p[w]=(p[w-1]<<1)%mod;
	int K=p[M],nn=n-N+1,mm=m-M+1;
	for(int w=1;w<=n;w++){
		scanf("%s",a+1);
		for(int x=1;x<=m;x++)h[w][x]=((h[w][x-1]<<1)+(a[x]^48))%mod;
	}
	scanf("%d",&q);
	while(q--){
		for(int w=1;w<=N;w++){
			int x=0;h2[w]=0;
			char c=getchar();
			while(1){
				if(c>='0'&&c<='1'){
					x++;
					h2[w]=((h2[w]<<1)+(c^48))%mod;
					if(x==M)break;
				}
				c=getchar();
			}
		}
		bool t=0;
		for(int w=1;!t&&w<=nn;w++)for(int x=1;x<=mm;x++){//nn=n-N+1,mm=m-M+1，减少运算常数
			bool k=1;
			for(int y=1,z=w;y<=N;y++,z++)if(h2[y]!=(h[z][x+M-1]-1ll*K*h[z][x-1]%mod+mod)%mod){k&=0;break;}
			if(k){t|=1;break;}
		}
		printf("%d\n",t);
	}
	return 0;
}
```
### 关键一步
注意到 `(h[z][x+M-1]-1ll*K*h[z][x-1]%mod+mod)%mod` 只跟 $x$ 和 $z$ 有关，可以用 $O(n^2)$ 的复杂度预处理，跑到四秒，洛谷零点八秒，可过。
```
#include<bits/stdc++.h>
#define int unsigned int
using namespace std;
const int mod=1e9+7;
int n,m,N,M,q,h[1001][1001],h2[101],p[501],f[1010][1010];
signed main(){
	//freopen("4.in","r",stdin);
	scanf("%u%u%u%u",&n,&m,&N,&M);p[0]=1;
	for(int w=1;w<=M;w++)p[w]=(p[w-1]<<1)%mod;
	int K=p[M],nn=n-N+1,mm=m-M+1;
	for(int w=1;w<=n;w++){
		int x=0;
		char c=getchar();
		while(true){
			if(c>='0'&&c<='1'){
				x++,h[w][x]=((h[w][x-1]<<1)+(c^48))%mod;
				if(x==m)break; 
			}
			c=getchar();
		}
	}
	for(int x=1;x<=mm;x++)for(int z=1;z<=n;z++)f[x][z]=(h[z][x+M-1]+mod-1ll*K*h[z][x-1]%mod)%mod;
	scanf("%u",&q);
	while(q--){
		for(int w=1;w<=N;w++){
			int x=0;h2[w]=0;
			char c=getchar();
			while(true){
				if(c>='0'&&c<='1'){
					h2[w]=((h2[w]<<1)+(c^48))%mod;
					if((++x)==M)break;
				}
				c=getchar();
			}
		}
		bool t=0;
		for(int w=1;/*!t&&*/w<=nn&&!t;w++)for(int x=1;x<=mm;x++){
			bool k=1;
			for(int y=1,z=w;y<=N;y++,z++)if(h2[y]!=f[x][z]){k&=0;break;}
			if(k){t|=1;break;}
		}
		cout<<t<<"\n";
	}
	return 0;
}
```
### 注意事项和后记
- 文中提到“时间”，非特殊说明，均为本地时间
- 语言配置：C++ 20/23 O2
- 本题数据较水，应该可以造出数据卡掉本题解，所以本题解仅供参考，若想学习正解请跳过

---

## 作者：Left_i_Forever (赞：0)

> 给定一 $N\times M$ 的矩阵，$Q$ 次询问，每次给定一个 $a\times b$ 的矩阵，求大矩阵中是否存在子矩阵和它相同。
>
> $1\le N,M\le 10^3$。

板子二维哈希，正好复习一下。

我学的二维哈希的方法是类似前缀和的递推从左上角到当前格子的矩阵哈希值。递推方法就是行和列各用一个进制，把二位前缀和稍微改改。

具体可以看代码。

注意因为询问矩阵大小都相同，所以可以预处理，直接查询。

```cpp
#include <bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
typedef pair <int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
const double eps = 1e-10, PI = acos (-1);
const int N = 1e3 + 10, M = 2e5 + 10;
//const int mod = 1e9 + 7;
const int mod = 998244353, base1 = 131, base2 = 481939;

char c[N][N];
int h[N][N], h2[N][N], b1[N], b2[N];
map <int, bool> mp;

int query(int x, int y, int xx, int yy)
{
    return ((h[xx][yy] - h[x - 1][yy] * b1[xx - x + 1] % mod - h[xx][y - 1] * b2[yy - y + 1] % mod + h[x - 1][y - 1] * b1[xx - x + 1] % mod * b2[yy - y + 1] % mod) % mod + mod) % mod;
}

signed main()
{
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> c[i][j];
    b1[0] = b2[0] = 1;
    for (int i = 1; i <= n; i++)
        b1[i] = b1[i - 1] * base1 % mod;
    for (int i = 1; i <= m; i++)
        b2[i] = b2[i - 1] * base2 % mod;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            h[i][j] = ((h[i - 1][j] * base1 % mod + h[i][j - 1] * base2 % mod - h[i - 1][j - 1] * base1 % mod * base2 % mod + c[i][j] - '0') % mod + mod) % mod;
    for (int i = x; i <= n; i++)
        for (int j = y; j <= m; j++)
            mp[query (i - x + 1, j - y + 1, i, j)] = true;
    int q;
    cin >> q;
    while (q--)
    {
        for (int i = 1; i <= x; i++)
            for (int j = 1; j <= y; j++)
            {
                char ch;
                cin >> ch;
                h2[i][j] = ((h2[i - 1][j] * base1 % mod + h2[i][j - 1] * base2 % mod - h2[i - 1][j - 1] * base1 % mod * base2 % mod + ch - '0') % mod + mod) % mod;
            }
        int val = h2[x][y];
        // bool flag = false;
        // for (int i = x; i <= n; i++)    
        //     for (int j = y; j <= m; j++)
        //         if (val == query (i - x + 1, j - y + 1, i, j) == val)
        //         {
        //             flag = true;
        //             break;
        //         }
        cout << mp[val] << "\n";
    }
    return 0;
}
```

---

## 作者：ttq012 (赞：0)

二维哈希模板题。

考虑对于原矩阵使用二位哈希，求出每一个 $a\times b$ 大小的矩阵的哈希值并将其放在一个 `map` 中。查询的时候直接求出这个查询矩阵整体的哈希值，然后判断一下 `map` 里是否有了这一个元素即可。

```cpp
// 核心部分
const int N = 2010;
using ull = unsigned long long;
ull bit131[N], bit13331[N], a[N][N], b[N][N];
ull get(int l, int r, int x, int y) {
    return a[r][y] - a[l - 1][y] * bit131[r - l + 1] - a[r][x - 1] * bit13331[y - x + 1] + a[l - 1][x - 1] * bit131[r - l + 1] * bit13331[y - x + 1];
}

void $() {
    int n, m, A, B;
    cin >> n >> m >> A >> B;
    bit131[0] = bit13331[0] = 1;
    F(i, 1, max(n, m)) {
        bit131[i] = bit131[i - 1] * 131;
        bit13331[i] = bit13331[i - 1] * 13331;
    }
    F(i, 1, n) {
        string s;
        cin >> s;
        F(j, 1, m) {
            a[i][j] = s[j - 1] ^ 48;
        }
    }
    F(i, 1, n) {
        F(j, 1, m) {
            a[i][j] += a[i][j - 1] * 13331;
        }
    }
    F(i, 1, n) {
        F(j, 1, m) {
            a[i][j] += a[i - 1][j] * 131;
        }
    }
    map<ull, int> mp;
    F(i, 1, n - A + 1) {
        F(j, 1, m - B + 1) {
            mp[get(i, i + A - 1, j, j + B - 1)] = 1;
        }
    }
    int q;
    cin >> q;
    while (q--) {
        F(i, 1, A) {
            string s;
            cin >> s;
            F(j, 1, B) {
                b[i][j] = s[j - 1] ^ 48;
            }
        }
        F(i, 1, A) {
            F(j, 1, B) {
                b[i][j] += b[i][j - 1] * 13331;
            }
        }
        F(i, 1, A) {
            F(j, 1, B) {
                b[i][j] += b[i - 1][j] * 131;
            }
        }
        cout << mp[b[A][B]] << '\n';
    }
}

signed main() { $(); }
```

---

