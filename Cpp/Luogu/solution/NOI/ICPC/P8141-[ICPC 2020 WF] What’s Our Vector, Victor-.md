# [ICPC 2020 WF] What’s Our Vector, Victor?

## 题目描述

向量嵌入是机器学习系统中的一种常用工具。现实世界中的某些复杂的概念（例如词典中的单词）通过这种方法可以映射到一个实向量上。如果能让机器正确地训练向量嵌入，由于相关概念在向量空间中保持着紧密的联系，因此像“这两个单词是同义词吗？”这种问题可以简化为简单的数学测试了。

你最近被 Ye Olde 冰淇淋专柜受雇，专门负责为冰淇淋口味创建一个向量嵌入式模型，这样当一种口味的冰淇淋卖完以后，这个嵌入式模型就可以像顾客推荐其它味道相近的冰淇淋。在六个云数据中心里训练了四个月以后，你终于拥有了一个完美的模型，正准备好改变你所在街区的冰淇淋行业，乃至整个街区时，你不小心把一些免费的冰淇淋滴到了键盘上，导致一半的数据被删除。重新训练模型需要花费 300 亿卢布，而专柜显然承受不了这么高的价格，因此你陷入了巨大的麻烦之中。幸运的是，你可以通过剩下的数据来还原出被删除的向量。具体地，对于一个给定的被删除的向量，数据会告诉你它与某些已知的味道向量的接近程度。两个向量 $A,B$ 的接近程度即为这两个向量之间的标准欧几里得距离（即向量 $A-B$ 的长度）。

现在，给定向量所处的空间维度 $d$ 和已知向量个数 $n$，并给定所有 $n$ 个向量的坐标 $(x_{i,1},x_{i,2},\cdots,x_{i,d})$ 和到同一个被删除的向量的标准欧几里得距离 $e_i$，请你编写一个程序，求出被删除的向量的坐标。

## 说明/提示

对于所有数据：

- $1\leqslant d,n\leqslant 500$。
- $-100\leqslant x_{i,j}\leqslant 100$。
- $0\leqslant e_i\leqslant 5000$。

Translated by Eason_AC

## 样例 #1

### 输入

```
2 3
0 0 2.5
3 0 2.5
1.5 0.5 2.5```

### 输出

```
1.5 -2```

## 样例 #2

### 输入

```
2 2
0 0 2
4 -4 6```

### 输出

```
1.414213562373 1.414213562373```

## 样例 #3

### 输入

```
4 3
0 1 2 3 2
1 2 -1 7 5
1 0.3 3.4 1.2 3.3```

### 输出

```
1 2 3 4```

# 题解

## 作者：warzone (赞：13)

## 题目大意

你在一个 $d$ 维空间中。

给出空间中 $n$ 个点的坐标 $\vec{y}_1,\vec{y}_2,\cdots,\vec{y}_n$ 及它们与你的距离 $r_1,r_2,\cdots,r_n$，

请你求出你所在的坐标 $\vec{x}$。

若有多个解，输出任意一个。

$\texttt{Data Range}:1\le n,d\le 500$，坐标范围 $[-100,100]$，保证数据随机且有解。

## 题解

给出一个 naive 的数形结合的做法。

根据题意，不难列出方程

$$
\begin{cases}
	(\vec{x}-\vec{y}_1)^2=r_1^2\\
	(\vec{x}-\vec{y}_2)^2=r_2^2\\
	\cdots  \\
	(\vec{x}-\vec{y}_n)^2=r_n^2
\end{cases}
$$

这个方程含有平方，所以没法直接高斯消元。

但注意到

$$(\vec{x}-\vec{y})^2=\vec{x}^2-2\vec{y}\cdot\vec{x}+\vec{y}^2$$

其中 $\vec{x}^2$ 是相同的。

考虑将原点平移到 $\vec{y}_1$，设 $\vec{x}'=\vec{x}-\vec{y}_1,\forall k,\vec{y}_k'=\vec{y}_k-\vec{y}_1$，则

$$
\begin{cases}
	\vec{x}'^2=r_1^2&(1)\\
	(\vec{x}'-\vec{y}_2')^2=r_2^2\\
	(\vec{x}'-\vec{y}_3')^2=r_3^2\\
	\cdots\\
	(\vec{x}'-\vec{y}_n')^2=r_n^2
\end{cases}
$$

下面 $n-1$ 个式子同时减去 $(1)$，得到

$$
\begin{cases}
-2\vec{y}'_2\cdot\vec{x}+\vec{y}_2'^2=r_2^2-r_1^2\\
-2\vec{y}'_3\cdot\vec{x}+\vec{y}_3'^2=r_3^2-r_1^2\\
\cdots\\
-2\vec{y}'_n\cdot\vec{x}+\vec{y}_n^2=r_n^2-r_1^2
\end{cases}
$$

这等价于线性方程组

$$A\vec{x}=\vec{a}$$

$$A=\begin{bmatrix}
	(\vec{y}_2')^T\\
	\hline(\vec{y}_3')^{T^{^{^{}}}}\\
	\hline\vdots \\
	\hline(\vec{y}_n')^{T^{^{^{}}}}
\end{bmatrix},\vec{a}=-\dfrac{1}{2}\begin{bmatrix}
	r_2^2-r_1^2-\vec{y}_2^2\\
	r_3^2-r_1^2-\vec{y}_3^2\\
	\vdots\\
	r_n^2-r_1^2-\vec{y}_n^2
\end{bmatrix}$$

高斯消元求解该线性方程组，若其有唯一解，则解就是答案。

---------------------

如果解不是唯一的怎么办？这时“形”便派上用场。

让我们转换一下题意：给定 $d$ 维空间中 $n$ 个超球，  

球心为 $\vec{y}_1,\vec{y}_2,\cdots,\vec{y}_n$，半径为 $r_1,r_2,\cdots,r_n$，求它们的交点。

![](https://cdn.luogu.com.cn/upload/image_hosting/p1s6vcb3.png)

先把这个问题搁置一边，来看看这个高中文化课常用的 trick：

给定二维空间两个圆的方程：

$$
\begin{cases}
	(x-a_1)^2+(y-b_1)^2=r_1^2&(1)'\\
	(x-a_2)^2+(y-b_2)^2=r_2^2&(2)'
\end{cases}
$$

它们的交线如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/qyimro1a.png)

现在我们要求交线的方程，一般人的想法是将 $(1)',(2)'$ 联立，求得交点后再求交线。

但最快的方法是将 $(1)',(2)'$ 相减，直接求得交线的方程

$$(x-a_1)^2-(x-a_2)^2+(y-b_1)^2-(y-b_2)^2=r_1^2-r_2^2$$

接下来我们简短证明下这么做的正确性：

> - $(1)',(2)'$ 中 $x^2,y^2$ 系数均为 $1$，因此 $(1)'-(2)'$ 一定是个二元一次不定方程，  
  也就一定是一条直线。
> - $(2)'+[(1)'-(2)']=(1)'$，因此圆 $2$ 与该直线的交点一定在圆 $1$ 上。  
  同理，圆 $1$ 与该直线的交点一定在圆 $2$ 上。    
  因此该直线与两个圆中一个的交点等价于两个圆的交点。  
> 综上，$(1)'-(2)'$ 就是两个圆的交线方程。

显然这个结论及其证明可以推广到高维空间，若已知三维空间两个球的方程：

$$
\begin{cases}
	(x-a_1)^2+(y-b_1)^2+(z-c_1)^2=r_1^2&(1)''\\
	(x-a_2)^2+(y-b_2)^2+(z-c_2)^2=r_2^2&(2)''\\
\end{cases}
$$

它们的交面如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/gw7w5m8i.png)

把 $(1)''$ 和 $(2)''$ 相减，可直接得到交面的方程

$$(x-a_1)^2-(x-a_2)^2+(y-b_1)^2-(y-b_2)^2+(z-c_1)^2+(z-c_2)^2=r_1^2-r_2^2$$

且交面与其中一个球的交点等价于两球的交点。

同理，若已知 $d$ 维空间的两个超球：

$$
\begin{cases}
	(\vec{x}-\vec{y}_1)^2=r_1^2\\
	(\vec{x}-\vec{y}_2)^2=r_2^2
\end{cases}
$$

将两个超球的方程相减，可得到 $d-1$ 维超交面的方程

$$(\vec{x}-\vec{y}_1)^2-(\vec{x}-\vec{y}_2)^2=r_1^2-r_2^2$$

且超交面与其中一个超球的交点等价于两个超球的交点。

此时我们已经能解释之前的高斯消元在做什么了：

- 将所有方程减去 $(1)$ 等价于求超球 $1$ 与其他所有超球的超交面方程。
- 高斯消元等价于求这些超交面的交。
- 这些超交面的交与超球 $1$ 的交点都是合法的解，即所有超球的交点。

---------------------------------

分析完这些后，解不唯一的情况变成了一个这样的问题：

设高斯消元后自由元的个数为 $k$，  
则我们需要求解一个 $d$ 维超球和一个 $k$ 维 “平面” （准确的说是线性流形）的交点。

![](https://cdn.luogu.com.cn/upload/image_hosting/jirajkqx.png)

同样考虑二维空间的情况：求解一个圆和一条直线的交点。

![](https://cdn.luogu.com.cn/upload/image_hosting/3ptqq5vf.png)

一个显然的做法是过圆心向直线作垂线，然后勾股定理算出垂足到交点的距离：

![](https://cdn.luogu.com.cn/upload/image_hosting/jv8u8fz5.png)

拓展到三维空间时，情况是类似的：

- 对于三维空间一条直线和球相交，跟刚才的情况是一样的。
  ![](https://cdn.luogu.com.cn/upload/image_hosting/hesarb5n.png)
- 对于三维空间一个平面和球相交，可以确定截面一定是个圆。
  同样作垂线得到圆心后勾股定理求解。
  ![](https://cdn.luogu.com.cn/upload/image_hosting/31yw1dkl.png)

想一想怎么归纳到高维空间，提示一下：一维空间的超球是两个点。

$\qquad$

------------------------------------------

$\qquad$

答案揭晓：$d$ 维空间一个超球与一个 $k(k\le d)$ 维线性流形相交，截面一定是个 $k$ 维超球。  
过原超球球心向线性流形作垂线即可得到截面的球心，再勾股定理即可得到球心的半径。

我们由此得到求解原问题的一个大致的思路：

- 过超球心向线性流形作垂线，求出垂足的坐标 $\vec{p}$。
- 勾股定理算出截面的半径 $r'$。
- 在线性流形上随便找一个长度为 $r'$ 的向量 $\vec{q}$，$\vec{p}+\vec{q}$ 就是一个合法的解。

------------------------------

回到之前的线性方程组。高斯消元后，其一定会变为如下形式：

$$
\left[
\begin{array}{ccccc|}
	1&&&&&v_{1,1}&v_{2,1}&\cdots&v_{k,1}\\
	&1&&&&v_{1,2}&v_{2,2}&\cdots&v_{k,2}\\
	&&\ddots&&&\vdots&\vdots&\vdots&\vdots\\
	&&&1&&v_{1,d-k-1}&v_{2,d-k-1}&\cdots&v_{k,d-k-1}\\
	&&&&1&v_{1,d-k}&v_{2,d-k}&\cdots&v_{k,d-k}\\
	\hline 0&0&0&0&0&0&0&0&0\\
	\vdots&\vdots&\vdots&\vdots&\vdots&\vdots&\vdots&\vdots&\vdots
\end{array}\right]
\begin{bmatrix}
	x_1\\x_2\\\vdots\\x_{d-k}\\\hline x_{d-k+1}\\ x_{d-k+2}\\ \vdots \\x_d
\end{bmatrix}=\begin{bmatrix}
	a_1'\\ a_2'\\ \vdots\\ a_{d-k}'\\\hline 0\\0\\ \vdots \\0
\end{bmatrix}
$$

简记为如下形式：

$$
\left[\begin{array}{c|c|c|c|c}
	I&\vec{v}_1&\vec{v}_2&\cdots&\vec{v}_k\\
	\hline O&\vec{0}&\vec{0}&\vec{0}&\vec{0}
\end{array}\right]
\begin{bmatrix}\vec{x}_0\\ \hline\vec{x}_1\end{bmatrix}
=\begin{bmatrix}\vec{a}'\\ \hline\vec{0}\end{bmatrix}
$$

我们需要确定线性方程组的解集，从而确定整个线性流形。

- 若 $\vec{x}_1=\vec{0}$，显然 $\vec{x}_0=\vec{a}'$。  
  因此 $\begin{bmatrix}\vec{a}'\\ \hline\vec{0}\end{bmatrix}$ 是该线性方程组的一组特解。
- 若 $x_{d-k+1}=\lambda,x_{d-k+2}=x_{d-k+3}=\cdots=x_d=0$，  
  则 $\vec{x}_0+\lambda\vec{v}_1=\vec{a}',\vec{x}_0=\vec{a}-\lambda\vec{v}_1$。   
  因此 $x_{d-k+1}$ 每增加 $\lambda$，$\vec{x}_0$ 就要减去 $\lambda\vec{v}_1$。

综上，设

$$
\vec{u}_1=\begin{bmatrix}-\vec{v}_1\\\hline 1\\0\\0\\0\\ \vdots\end{bmatrix}
,\vec{u}_2=\begin{bmatrix}-\vec{v}_2\\\hline 0\\1\\0\\0\\ \vdots\end{bmatrix},
\vec{u}_3=\begin{bmatrix}-\vec{v}_3\\\hline 0\\0\\1\\0\\ \vdots\end{bmatrix},\cdots
$$

$$
\vec{b}=\begin{bmatrix}
	\vec{a}'\\ \hline \vec{0}
\end{bmatrix},V=\{[\vec{u}_1|\vec{u}_2|\cdots|\vec{u}_k]\vec{x}_1|\vec{x}_1\in\mathbb{R}_k\}
$$

则线性方程组的解集为 

$$X=\{\vec{b}+\vec{\Delta}|\vec{\Delta}\in V\}$$

即线性空间 $V$ 内的所有向量加上特解 $\vec{b}$，与线性流形的定义一致。

接下来考虑作垂线，由于球心为 $\vec{0}$，$V$ 的基底为 $\vec{u}_1,\vec{u}_2,\cdots,\vec{u}_k$，  
我们的目标是找出 $\vec{p}\in X$，使得 $\vec{p}$ 与 $V$ 中所有的基向量垂直，即

$$
\vec{u}_1\cdot \vec{p}=\vec{u}_2\cdot\vec{p}=\cdots=\vec{u}_k\cdot \vec{p}=0
\qquad{(2)}$$

把 $\vec{p}$ 拆开：

$$\vec{p}=\vec{b}+[\vec{u}_1|\vec{u}_2|\cdots|\vec{u}_k]\vec{x}_1\qquad{(3)}$$

然后将 $(2)$ 表示成矩阵形式：

$$
\begin{bmatrix}
	\vec{u}_1^T\\
	\hline\vec{u}_2^{T^{^{^{}}}}\\
	\hline\cdots\\
	\hline\vec{u}_k^{T^{^{^{}}}}
\end{bmatrix}(\vec{b}+[\vec{u}_1|\vec{u}_2|\cdots|\vec{u}_k]\vec{x}_1)=\vec{0}
$$

注意到 $\begin{bmatrix}\vec{u}_1^T\\\hline\vec{u}_2^{T^{^{^{}}}}\\\hline\cdots\\\hline\vec{u}_k^{T^{^{^{}}}}
\end{bmatrix}[\vec{u}_1|\vec{u}_2|\cdots|\vec{u}_k]$ 为 $k$ 阶方阵 ，因此高斯消元解线性方程组

$$
\begin{bmatrix}\vec{u}_1^T\\\hline\vec{u}_2^{T^{^{^{}}}}\\\hline\cdots\\\hline\vec{u}_k^{T^{^{^{}}}}
\end{bmatrix}[\vec{u}_1|\vec{u}_2|\cdots|\vec{u}_k]\vec{x}_1=-\begin{bmatrix}\vec{u}_1^T\\\hline\vec{u}_2^{T^{^{^{}}}}\\\hline\cdots\\\hline\vec{u}_k^{T^{^{^{}}}}
\end{bmatrix}\vec{b}
$$

即可得到 $\vec{x}_1$，代入 $(3)$ 即可求出 $\vec{p}$。

因为过线性流形（直线/平面）上一点有且只有一条直线与该流形（直线/平面）垂直，

这个线性方程组一定有唯一解，也就一定能解出 $\vec{p}$。

解出 $\vec{p}$ 后，勾股定理得到

$$r'=\sqrt{r^2-\vec{p}^2}$$

然后 $\vec{p}+\dfrac{r'}{\sqrt{\vec{u}_1^2}}\vec{u}_1$ 就是一组合法的解了。


------------------------

最后不要忘记，我们一开始将原点平移到了 $\vec{y}_1$，要平移回去才行哦！

## Code
```cpp
/*
this code is made by warzone
2022.3.11 15:30
*/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
typedef double db;
struct READ{//快读
	char c,w;
	inline READ(){c=getchar();}
	template<typename type>
	inline READ& operator >>(type& num){
		for(w=1;'0'>c||c>'9';c=getchar())
			w=c=='-'? -1:1;
		for(num=0;'0'<=c&&c<='9';c=getchar())
			num=num*10+(c-'0');
		if(c=='.') for(db i=1;c=getchar(),'0'<=c&&c<='9';)
			i*=0.1L,num+=i*(c-'0');
		return num*=w,*this;
	}
}cin;
int d,n;
int pos[512],pos_[512];
db y[512],r;
db A[512][512],a[512];
db B[512][512],b[512];
int top,top_;
template<typename type1,typename type2,typename type3>
inline void gauss(type1 &A,type2 &a,type3 &pos,//高斯消元
	int &top,const int d,const int n){
	top=d;
	for(int id=0;id<top&&id<n;++id){
		while(A[id][id]==0){
			for(int i=id+1;i<n;++i) if(A[i][id]){
				for(int j=id;j<d;++j)
					std::swap(A[id][j],A[i][j]);
				std::swap(a[id],a[i]);break;
			}
			if(A[id][id]==0){//把消元失败的维度放到最后面
				if(id>=--top) return;
				std::swap(pos[top],pos[id]);
				for(int i=0;i<n;++i)
					std::swap(A[i][id],A[i][top]);
			}
		}
		if(A[id][id]!=1){
			db get=A[id][id];
			for(int i=id+1;i<d;++i) A[id][i]/=get;
			A[id][id]=1,a[id]/=get;
		}
		for(int i=0;i<n;++i) if(i!=id&&A[i][id]){
			db get=A[i][id];
			for(int j=id+1;j<d;++j) A[i][j]-=A[id][j]*get;
			A[i][id]=0,a[i]-=a[id]*get;
		}
	}
}
inline void print(){//平移回来并输出答案
	for(int i=0;i<d;++i) y[pos[i]]+=a[i];
	for(int i=0;i<d;++i) printf("%0.6lf ",y[i]);
}
int main(){
	cin>>d>>n;
	for(int i=0;i<d;++i) cin>>y[i],pos[i]=i;//输入 (1) 式
	cin>>r,--n;
	for(int id=0;id<n;++id){
		for(int i=0;i<d;++i){//减去 (1) 式
			cin>>A[id][i],A[id][i]-=y[i];
			a[id]+=A[id][i]*A[id][i];
		}
		db get;
		cin>>get,a[id]=(a[id]+r*r-get*get)/2;
	}
	gauss(A,a,pos,top,d,n),top=std::min(top,n);//第一次高斯消元
	if(top==d) return print(),0;//唯一解
	for(int i=top;i<d;++i) A[i][i]=-1;
	const int k=d-top;
	for(int id=0;id<k;++id){//计算 \vec{p} 的线性方程组
		pos_[id]=id;
		for(int i=0;i<k;++i)
			for(int j=0;j<d;++j)
				B[id][i]+=A[j][id+top]*A[j][i+top];
		for(int j=0;j<d;++j)
			b[id]-=A[j][id+top]*a[j];
	}
	gauss(B,b,pos_,top_,k,k);//第二次高斯消元
	for(int id=0;id<k;++id)//将 \vec{x}_1 代回 \vec{p} 
		for(int i=0;i<d;++i)
			a[i]+=b[id]*A[i][id+top];
	db r_=r*r,r__=0;
	for(int i=0;i<d;++i){//勾股定理计算 r'
		r__+=A[i][top]*A[i][top];
		r_-=a[i]*a[i];
	}
	r_=sqrtl(r_/r__);
	for(int i=0;i<d;++i) a[i]+=A[i][top]*r_;
	return print(),0;
}
```

---

## 作者：Alex_Wei (赞：7)

备注：`\pmb` 在题解区可以正常渲染。仅预览不支持。

Update on 2.24：规范数学公式用法（去掉了所有矩阵前面的 `\pmb`）。

Update on 4.14：修改一个 Typo。

> *[P8141 [ICPC2020 WF] What’s Our Vector, Victor?](https://www.luogu.com.cn/problem/P8141)*
>
> 给定 $n$ 个 $d$ 维向量 $v_i$ 与 $e_i$，求 $d$ 维向量 $x$ 满足 $\|x - v_i\| = e_i$。保证有解。$n, d \leq 500$。

根据题意，可以列出以下方程。
$$
\begin{cases}
(x_1 - v_{1, 1}) ^ 2 + (x_2 - v_{1, 2}) ^ 2 + \cdots = e_1 ^ 2 \\
(x_1 - v_{2, 1}) ^ 2 + (x_2 - v_{2, 2}) ^ 2 + \cdots = e_2 ^ 2 \\
\cdots
\end{cases}
$$
将平方项展开后，出现了 $x_i ^ 2$ 项。众所周知高斯消元只能处理线性方程组，所以考虑常用套路 **差分消去平方项**。处理后，我们得到了 $n - 1$ 个 $d$ 元线性方程组，和最开始的一个 $d$ 元二次方程。形如
$$
\begin{cases}
(x_1 - v_{1, 1}) ^ 2 + (x_2 - v_{1, 2}) ^ 2 + \cdots = e_1 ^ 2 \\
2(v_{1, 1} - v_{2, 1})  x_1 + 2(v_{1, 2} - v_{2, 2}) x_2 + \cdots = e_2 ^ 2 - e_1 ^ 2 + v_{1, 1} ^ 2 - v_{2, 1} ^ 2 + v_{1, 2} ^ 2 - v_{2, 1} ^ 2  + \cdots \\
2(v_{2, 1} - v_{3, 1}) x_1 + 2(v_{2, 2} - v_{3, 2}) x_2 + \cdots = e_3 ^ 2 - e_2 ^ 2 + v_{2, 1} ^ 2 - v_{3, 1} ^ 2 + v_{2, 2} ^ 2 - v_{3, 1} ^ 2  + \cdots \\
\cdots
\end{cases}
$$
用向量和矩阵描述 $x$ 前的系数，则有
$$
\begin{cases}
\| \pmb x - \pmb v_1 \| ^ 2 = e_1 ^ 2 \\
A\pmb x = \pmb b
\end{cases}
$$
其中 $A$ 为 $(n - 1) \times d$ 矩阵，$\pmb x$ 为 $d$ 维向量即所求答案，$\pmb b$ 为 $n - 1$ 维向量。

首先考虑化简二次式。令 $\pmb x' = \pmb x - \pmb v_1$。则方程可写为
$$
\begin{cases}
\| \pmb x' \| ^ 2 = e_1 ^ 2 \\
 A\pmb x' = \pmb b - A\pmb {v}_1
\end{cases}
$$
接下来我们用 $\pmb x'$ 代替 $\pmb x$，求解后再加上 $\pmb v_1$。

高斯消元求解线性方程组 $A \pmb x = \pmb b - A\pmb v_1$，得到线性方程组的解集的 **参数向量形式**。即 $\pmb x = \pmb x_{\rm base} + \sum\limits_{i = 1} ^ r c_i\pmb v_i$，其中 $r$ 是 **自由元** 个数。

- 众所周知，对于线性方程组的解集，任何 **主元** 都可以写作自由元的 **线性组合** 形式。考虑令所有自由元等于 $0$，我们得到了 $\pmb x_{\rm base}$。将所有自由元移到方程右侧，我们得到了所有主元关于所有自由元的线性组合的权，稍做变形即可得到对应向量。

    例如一个简化行阶梯型增广矩阵对应的线性方程组
    $$
    \begin{cases}
    x_1 + 6x_2 + 3x_4 = 0 \\
    x_3 - 4x_4 = 5 \\
    x_5 = 7
    \end{cases}
    $$
    其中 $x_1, x_3, x_5$ 是主元，$x_2, x_4$ 是自由元。因此，其解集的参数表示为
    $$
    \begin{cases}
    x_1 = -6x_2 - 3x_4 \\
    x_2 = x_2 \\
    x_3 = 5 + 4x_4 \\
    x_4 = x_4 \\
    x_5 = 7
    \end{cases}
    $$
    即 $\pmb x = \begin{bmatrix} -6x_2 - 3x_4 \\ x_2 \\ 5 + 4x_4 \\ x_4 \\ 7 \end{bmatrix}$。将常数，$x_2$ 和 $x_4$ 分离，得到 $\pmb x = \begin{bmatrix} 0 \\ 0 \\ 5 \\ 0 \\ 7 \end{bmatrix} + x_2\begin{bmatrix} -6 \\ 1 \\ 0 \\ 0 \\ 0 \end{bmatrix} + x_4\begin{bmatrix} -3 \\ 0 \\ 4 \\ 1 \\ 0 \end{bmatrix}$。即方程组的解可写为一个常向量 $\pmb x_{\rm base}$ 加上若干向量的线性组合。线性组合的权对应了自由变量的取值。

为了让 $\pmb x$ 满足 $\| \pmb x \| = e_1$，通常采用的手段是先求出 $\pmb x$ 的 **最小范数解** $\pmb x_{\min}$，再通过调整法求解。显然，如果 $\| \pmb x_{\min}\| > e_1$ 则无解，与题意矛盾，因此 $\| \pmb x_{\min} \| \leq e_1$。而通过加上足够大的 $\pmb v_i$（任意一个均可），我们总能让得到的 $\pmb x$ 的模长趋于无穷大。又因为 $\| \pmb x \|$ 即 $\| \pmb x_{\min} + k\pmb v_i \|$ 的变化随着 $\pmb v_i$ 的权 $k$ 的变化 **连续**，因此调整法正确。

- 关于最小范数解 $\pmb x_{\min}$，它与所有 $\pmb v_i$ 垂直。若不与某个 $\pmb v_i$ 垂直，令 $\pmb x = \pmb x_{\min} + k\pmb v_i$ 且 $\pmb x \perp \pmb v_i$，通过点积的性质和数值分析容易证明 $\| \pmb x \| < \| \pmb x_{\min} \|$。因此可以列出方程 $\pmb x_{\min} \cdot \pmb v_i = 0\ (1\leq i \leq r)$，即 $\pmb v_i ^ T \pmb x_{\min} = 0$。若将 $\pmb v_i$ 看成矩阵 $V = \begin{bmatrix} \pmb v_1 & \pmb v_2 & \cdots & \pmb v_r \end{bmatrix}$，则 $V ^ T \pmb x_{\min} = \pmb 0$。又因为 $\pmb x = \pmb x_{\rm base} + \sum\limits_{i = 1} ^ r c_i \pmb v_i = \pmb x_{\rm base} + V\pmb c$，其中 $\pmb c$ 是 $r\times 1$ 的列向量，因此 $V ^ T (\pmb x_{\rm base} + V\pmb c) = \pmb 0$。据此可高斯消元求得 $\pmb c$，继而求出对应的 $\pmb x_{\min}$。

由于 $\pmb x_{\min}$ 垂直于所有 $\pmb v_i$，所以调整时直接使用勾股定理，随便选出一个向量 $\pmb v_1$，然后令 $\pmb x = \pmb x_{\min} + \sqrt {e_1 ^ 2 - \| \pmb x_{\min} \| ^ 2} \times \dfrac {\pmb v_1} {\| \pmb v_1\|}$ 即可。时间复杂度 $\mathcal{O}(n ^ 3)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 500 + 5;
const double eps = 1e-9;
int n, d, fr, ma, fre[N], mai[N], rev[N];
double v[N][N], A[N][N], dis[N], ans[N];
double b[N], xm[N], co[N][N];

int find(int m, double *A) {
	for(int i = 1; i <= m; i++) if(fabs(A[i]) > eps) return i;
	return -1;
}

template <class T>
	void Gauss(int n, int m, T A) {
		int r = 1;
		for(int c = 1; c < m && r <= n; c++) {
			int p = r;
			for(int i = r + 1; i <= n; i++) if(fabs(A[i][c]) > fabs(A[p][c])) p = i;
			swap(A[r], A[p]);
			if(fabs(A[r][c]) < eps) continue;
			for(int i = m; i >= c; i--) A[r][i] /= A[r][c];
			for(int i = r + 1; i <= n; i++) for(int j = m; j >= c; j--) A[i][j] -= A[r][j] * A[i][c];
			r++;
		}
		
		for(int i = n - 1; i > 0; i--) {
			for(int j = i + 1; j <= n; j++) {
				int main = find(m - 1, A[j]);
				if(main == -1) continue;
				if(fabs(A[i][main]) > eps) for(int k = m; k >= main; k--) A[i][k] -= A[i][main] * A[j][k];
			}
			int main = find(m - 1, A[i]);
			if(main == -1) continue;
			for(int j = m; j >= main; j--) A[i][j] /= A[i][main];
		}
	}

void init() {
	for(int i = 1; i < n; i++) {
		int main = find(d, A[i]);
		if(main != -1) rev[main] = -1, mai[++ma] = main;
	}
	for(int i = 1; i <= d; i++) if(!rev[i]) fre[++fr] = i, co[rev[i] = fr][i] = 1;
}

void solve() {
	for(int i = 1; i < n; i++) {
		int main = find(d, A[i]);
		b[main] = A[i][d + 1];
		for(int j = main + 1; j <= d; j++) if(~rev[j]) co[rev[j]][main] = -A[i][j];
	}

	memset(A, 0, sizeof(A));
	for(int i = 1; i <= fr; i++) for(int j = 1; j <= d; j++) A[i][fr + 1] -= co[i][j] * b[j];
	for(int i = 1; i <= fr; i++) for(int j = 1; j <= d; j++) for(int k = 1; k <= fr; k++) A[i][k] += co[i][j] * co[k][j];
	Gauss(fr, fr + 1, A);
	for(int i = 1; i <= fr; i++) for(int j = 1; j <= d; j++) xm[j] += A[i][fr + 1] * co[i][j];
	for(int i = 1; i <= d; i++) xm[i] += b[i];
	
	double normx = 0, normc = 0;
	for(int i = 1; i <= d; i++) normx += xm[i] * xm[i], normc += co[1][i] * co[1][i];
	normc = sqrt(normc);
	for(int i = 1; i <= d; i++) ans[i] = xm[i] + co[1][i] / normc * sqrt(dis[1] * dis[1] - normx);
	
	
}

int main() {
	cin >> d >> n;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= d; j++) scanf("%lf", &v[i][j]);
		scanf("%lf", &dis[i]);
	}
	for(int i = 1; i < n; i++) {
		A[i][d + 1] = dis[i + 1] * dis[i + 1] - dis[i] * dis[i];
		for(int j = 1; j <= d; j++) {
			A[i][j] = 2 * (v[i][j] - v[i + 1][j]);
			A[i][d + 1] += v[i][j] * v[i][j] - v[i + 1][j] * v[i + 1][j];
		}
	}
	for(int i = 1; i < n; i++) for(int j = 1; j <= d; j++) A[i][d + 1] -= A[i][j] * v[1][j];
	
	Gauss(n - 1, d + 1, A), init();
	if(fr) solve();
	else for(int i = 1; i <= d; i++) ans[i] = A[i][d + 1];
	for(int i = 1; i <= d; i++) printf("%.17lf\n", ans[i] + v[1][i]);
	
	return 0;
}

/*
stupid mistakes:
	forget to check if main is -1
	注意 co[i][j] 的意义，表示 v_{i_{j, 1}}，即第 i 个自由元改变时，x_j 的变化系数 
	勾股定理忘记开根 =.=
	v1 正负搞错 
	求范数忘记开根 
*/
```

---

## 作者：yyyyxh (赞：1)

> 给出 $d$ 维空间的 $n$ 个点及它们到某个定点的距离，你需要解出这个定点的坐标。
> 
> 保证有解，任意输出一组解即可。
> 
> $n,d\le 500$，所有点的坐标（包括定点）随机。

拜谢 zhy 大师！给出了一个十分简单好理解的做法！线代不好怎么办？我们可以猜猜结论！

首先这道题相当于是给了 $n$ 个形如 $\sum_{j=1}^d (a_{i,j}-x_j)^2=b_i^2$ 的方程，我们设 $\sum_{j=1}^d x_j^2=x_{d+1}$，那么这道题的方程可以整理成关于 $d+1$ 维向量 $\vec{x}$ 的线性方程。

注意到这道题数据纯随机，这个条件在线代题中往往意味着每一个方程都是有用的！即，如果 $n>d$，那么我们随便取出其中 $d+1$ 个方程，组成的矩阵极有可能满秩，解之即可得到 $\vec{x}$。

如果 $n=d$，难处在于 $x_{d+1}$ 解不出来，但是我们还有二次方程 $\sum_{j=1}^d x_j^2=x_{d+1}$。所以我们可以先把所有 $x_i(i\le d)$ 表示成关于 $x_{d+1}$ 的线性表达式，然后带入二次方程中解个一元二次方程。

这道题真正的难点便落在 $n<d$ 的情况上了。这种情况下，我们发现 $n$ 个随机 $d$ 维球壳相交（题目保证有交）结果极大概率是一个 $d-n+1$ 维的球壳，也就是说我们有无穷多个解，我们需要任取一个，怎么办呢？

考虑对这个方程组进行基变换减少变量的个数。我们找一个一定包含至少一个答案的子线性空间，即选取 $k$ 个合适的 $d$ 维向量 $\vec{v_i}$ 和一个原点 $\vec{s}$，将 $\vec{x}$ 表示成 $\vec{s}+\sum_{i=1}^k r_i\vec{v_i}$，那么原线性方程就可以整理成关于 $k$ 维向量 $\vec{r}$ 的线性方程。

我们断言，我们可以简单构造一个 $k=n$ 维的线性子空间一定包含至少两个答案！构造的方法意外的简单，我们先找到包含题目给出的 $n$ 个球心的极小子线性空间 $V'$，由于数据随机 $V'$ 的维度也极大概率就是 $n-1$ 维的！然后我们任意寻找一个不在 $V'$ 里的一个点，考虑同时包含了这个点和 $V'$ 的极小线性子空间 $V$，这个 $V$ 一定包含了至少两个答案。

严谨证明似乎我和 zhy 都不太会。但是很好进行感性理解，比如说 $n=1,d=3$ 的情况，$V'$ 仅包含球心，在 $V'$ 外任选一个点，$V$ 就会是一条过圆心的直线，这条直线一定会穿过球壳，交于两个点上。

这个题中如何具体寻找 $V$ 的基向量 $\vec{v_i}$ 非常简单！因为随机数据下原坐标系的原点大概率不在 $V'$ 中，所以取 $\vec{s}=\vec{0}$，取 $\vec{v_i}$ 为原点指向这 $n$ 个点的向量即可。

有了一个 $k=n$ 维且包含答案的子空间后，我们直接运行类似 $n=d$ 情况的算法解二次方程解出 $\vec{r}$，就可以还原出 $\vec{x}$。

解二次方程时，大概率有两个不重的根，选取哪个根都是可以的！因为 $V$ 与答案集合大概率恰好有两个交点！

代码十分好写。由于数据随机，高斯消元时你甚至不用移动方程的位置，直接认为第 $i$ 个方程主元是 $i$ 就可以了！

注意这份代码无法通过样例，因为样例不是随的，样例中原点正好在 $V'$ 中（因为有球心直接落在了原点上！）。当然这个情况你可以自行随机一个向量把球心集体位移一下再位移回来。

```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=505;
int d,n;
inline double dot(double *f,double *g){
	double res=0;
	for(int i=1;i<=d;++i) res+=f[i]*g[i];
	return res;
}
double e[N][N],a[N][N],ra[N],rb[N],s[N][N];
int main(){
	scanf("%d%d",&d,&n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=d+1;++j) scanf("%lf",&e[i][j]);
	if(d<n){
		for(int i=1;i<=d+1;++i){
			for(int j=1;j<=d;++j) a[i][j]=e[i][j]*2;
			a[i][d+1]=-1;
			a[i][d+2]=dot(e[i],e[i])-e[i][d+1]*e[i][d+1];
		}
		for(int i=1;i<=d+1;++i){
			for(int j=d+2;j>=i;--j) a[i][j]/=a[i][i];
			for(int j=i+1;j<=d+1;++j)
				for(int k=d+2;k>=i;--k) a[j][k]-=a[j][i]*a[i][k];
		}
		for(int i=d+1;i;--i)
			for(int j=1;j<i;++j) a[j][d+2]-=a[j][i]*a[i][d+2];
		for(int i=1;i<=d;++i) printf("%.8lf ",a[i][d+2]);
		putchar('\n');
	}
	else{
		for(int i=1;i<=n;++i)
			for(int j=1;j<=i;++j) s[i][j]=dot(e[i],e[j]);
		for(int i=1;i<=n;++i)
			for(int j=i+1;j<=n;++j) s[i][j]=s[j][i];
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j) a[i][j]=s[i][j]*2;
			a[i][n+1]=s[i][i]-e[i][d+1]*e[i][d+1];
			a[i][n+2]=1;
		}
		for(int i=1;i<=n;++i){
			for(int j=n+2;j>=i;--j) a[i][j]/=a[i][i];
			for(int j=i+1;j<=n;++j)
				for(int k=n+2;k>=i;--k) a[j][k]-=a[j][i]*a[i][k];
		}
		for(int i=n;i;--i){
			for(int j=i-1;j;--j){
				a[j][n+1]-=a[j][i]*a[i][n+1];
				a[j][n+2]-=a[j][i]*a[i][n+2];
			}
			for(int j=1;j<=d;++j){
				ra[j]+=e[i][j]*a[i][n+1];
				rb[j]+=e[i][j]*a[i][n+2];
			}
		}
		double A=0,B=0,C=0;
		for(int i=1;i<=d;++i){
			A+=rb[i]*rb[i];
			B+=2*ra[i]*rb[i];
			C+=ra[i]*ra[i];
		}
		--B;
		double r=(-B+sqrt(B*B-4*A*C))/(2*A);
		for(int i=1;i<=d;++i) printf("%.8lf ",ra[i]+rb[i]*r);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：chenxia25 (赞：0)

（`$\pmb$` 在题解区和博客里是可以渲染的！！！）

线性代数好题。

换一下舒服的变量名：设有 $n$ 个向量，空间为 $m$ 维，第 $i$ 个向量为 $\pmb v_i$，距离为 $d_i$。

列得方程：对 $i\in[1,n]$ 都有 $\|\pmb v_i-\pmb x\|=s_i$。展开得到 $\sum\limits_{j=1}^m(v_{i,j}-x_j)^2=d_i^2$，即 $\sum\limits_{j=1}^mv_{i,j}^2-2\sum\limits_{j=1}^mv_{i,j}x_j+\sum\limits_{j=1}^mx_j^2=s_i^2$。等式左边第一项为常数，可以移到右边去；第二项是 $\pmb x$ 各分量的线性组合；第三项是二次的，有点难办。不过观察到第三项虽然是未知量，但是对于所有方程都相等，于是我们可以通过差分将其消去。具体地，对第 $i\in[2,n]$ 个方程，令其减去第一个方程，得到 $n-1$ 个线性方程和一个二次方程。

不妨先将这 $n-1$ 个线性方程高斯消元解一下。如果解是唯一的，由于题目保证有解，那么这组解一定是解，直接输出就可以了（事实上理论上这里不用特判，但是由于后面的做法不太能处理大小为 $0$ 的矩阵，所以……）。否则我们得到解集的参数向量形式 $\pmb x\in\mathrm{Span}\{\pmb u_{1\sim k}\}+\pmb b$，其中 $k$ 为自由变量个数。现在只要找到这个解集 $X+\pmb b$ 中任意一个满足第一个二次方程 $\|\pmb x-\pmb v_1\|=s_1$ 的 $\pmb x$ 即可。求 $\pmb x-\pmb v_1$ 的范数不太好处理，我们不妨在一开始就令 $\pmb x'=\pmb x-\pmb v_1 $，求出 $\pmb x'$ 后还原 $\pmb x$ 即可。设 $n-1$ 个线性方程的矩阵形式为 $Q\pmb x=\pmb d$，由 $\pmb x=\pmb x'+\pmb v_1$ 得 $Q\pmb x'=\pmb d-Q\pmb v_1$，依然是线性方程组，不影响什么。之后都认为 $\pmb x$ 就代指 $\pmb x'$。

于是我们要求一个线性空间 $X$ 平移一个向量 $\pmb b$ 得到的解集中范数等于 $s$ 的向量。注意到：设 $X+\pmb b$ 中的范数最小的向量的范数为 $M$，则 $X+\pmb b$ 中的范数范围为 $[M,+\infty)$。于是我们尝试求出最小范数解，然后调整为范数恰好等于 $s$。

先讲如何调整。假设我们找到了最小范数解 $\pmb x_{\min}$，我们知道 $X+\pmb x_{\min}=X+\pmb b$（跟据若 $\pmb v\in V$ 则 $V+\pmb v=V$（其中 $V$ 是线性空间的性质易证）），于是我们只要求出 $\pmb x\in X$ 使 $\|\pmb x_{\min}+\pmb x\|=s$。乍一看感觉还是不容易，但是注意到我们只要求任意一组解（而不要求所有解），那么容易注意到仅令 $\pmb x$ 取遍 $c\pmb u_1$ 这一条直线便必然能找到解。具体地：我们熟知 $\pmb x_{\min}\perp X$，所以 $\pmb x_{\min},\pmb x+\pmb x_{\min},\pmb 0$ 三点构成直角三角形，已知其中两条边为 $\|\pmb x_{\min}\|,s$，可以通过勾股定理求出 $\pmb x+\pmb x_{\min}$ 与 $\pmb x_{\min}$ 的距离 $D$，于是 $\pmb x=\pm\dfrac{D}{\|\pmb u_1\|}\pmb u_1$，任取一个就好。

下面来讲如何求最小范数解。注意到如果平移一下坐标系，$\pmb x\in X+\pmb b$ 的范数相当于 $\pmb x-\pmb b\in X$ 与 $-\pmb b$ 的距离。由于线性空间关于原点对称，求 $\pmb b$ 到 $X$ 的最近向量，最后取反即可。这显然就是 $\pmb b$ 到 $X$ 的投影 $\mathrm{proj}_X\pmb b$。投影计算公式需要空间的一组正交基，而我们现在只有普通基 $\pmb u_{1\sim k}$，还要通过格拉姆-施密特方法求出一组正交基，有点麻烦，不妨直接考虑用普通基求投影。设 $\pmb p=\mathrm{proj}_X\pmb b$，我们知道 $\pmb b-\pmb p\perp X$ 且 $\pmb p\in X$，并且向量与线性空间垂直当且仅当其与一组基垂直，于是对 $i\in[1,k]$ 有 $\pmb u_i\cdot(\pmb b-\pmb p)=0$。设 $U=\begin{bmatrix}\pmb u_{1\sim k}\end{bmatrix},\pmb p=U\pmb c$，有 $U^{\mathrm T}(\pmb b-U\pmb c)=\pmb 0$，即 $\pmb c=\!\left(U^{\mathrm T}U\right)^{-1}U^{\mathrm T}\pmb b$。

此处有些同学关于方阵 $U^{\mathrm T}U$ 的满秩性有些疑问，事实上这不依赖于随机性。事实上我们有更强的结论：对任意 $m\times n$ 矩阵 $A$，有 $\operatorname{rank}A^{\mathrm T}A=\operatorname{rank}A$。  
随便胡个证明：一方面，若 $A\pmb x=\pmb 0$，则显然 $A^{\mathrm T}A\pmb x=\pmb 0$，所以 $\operatorname{Nul}A\subseteq\operatorname{Nul}A^{\mathrm T}A$；另一方面，若 $A^{\mathrm T}A\pmb x=\pmb 0$，则 $\pmb x^{\mathrm T}A^{\mathrm T}A\pmb x=\pmb 0_1$，即 $(A\pmb x)^2=0$，所以 $A\pmb x=\pmb 0$，所以 $\operatorname{Nul}A^{\mathrm T}A\subseteq \operatorname{Nul}A$。得到 $\operatorname{Nul}A^{\mathrm T}A=\operatorname{Nul}A$。又因为这两个矩阵的列数都为 $n$，秩都为 $n-\dim\operatorname{Nul}$，原命题得证。  
此处 $m\times k$ 矩阵 $U$ 各列是 $X$ 的基，所以各列线性无关，秩为 $k$，所以 $\operatorname{rank} U^{\mathrm T}U=k$，满秩。（所以至此不知道这题数据随机有啥用？可能是为了防爆精度吧）

u1s1 矩阵封装起来写真舒适（

```cpp
constexpr db eps = 1e-8;
constexpr int N = 510;

int n, m, s;
db dis[N];

using vd = vector<db>;
using vvd = vector<vd>;
vd operator-(vd f, vd g) {
	int n = SZ(f) - 1;
	REP(i, 1, n) f[i] -= g[i];
	return f;
}
struct matrix : vvd {
	using vvd::vvd;
	matrix() {}
	matrix(int n, int m) { resize(n + 1, vector<db>(m + 1, 0.)); }
	matrix(int n, int m, auto f) {
		resize(n + 1, vector<db>(m + 1));
		REP(i, 1, n) REP(j, 1, m) (*this)[i][j] = f;
	}
	friend matrix operator~(matrix f) {
		int n = SZ(f) - 1, m = SZ(f[1]) - 1;
		matrix g(m, n);
		REP(i, 1, n) REP(j, 1, m) g[j][i] = f[i][j];
		return g;
	}
	friend matrix operator+(matrix f, matrix g) {
		int n = SZ(f) - 1, m = SZ(f[1]) - 1;
		REP(i, 1, n) REP(j, 1, m) f[i][j] += g[i][j];
		return f;
	}
	friend matrix operator-(matrix f, matrix g) {
		int n = SZ(f) - 1, m = SZ(f[1]) - 1;
		REP(i, 1, n) REP(j, 1, m) f[i][j] -= g[i][j];
		return f;
	}
	friend matrix operator-(matrix f) {
		int n = SZ(f) - 1, m = SZ(f[1]) - 1;
		REP(i, 1, n) REP(j, 1, m) f[i][j] = -f[i][j];
		return f;
	}
	void operator&=(matrix g) {
		matrix &f = *this;
		int n = SZ(f) - 1, m = SZ(g[1]) - 1;
		REP(i, 1, n) REP(j, 1, m) f[i].pb(g[i][j]);
	}
	void gauss() {
		vvd &a = *this;
		int n = SZ(a) - 1, m = SZ(a[1]) - 1;
		auto tadd = [&](int x, db v, int y) {
			REP(i, 1, m) a[y][i] += v * a[x][i];
		};
		auto times = [&](int x, db v) {
			REP(i, 1, m) a[x][i] *= v;
		};
		for(int i = 1; ; ++i) {
			int x = 0, y = 0;
			REP(j, 1, m) REP(k, i, n) if(abs(a[k][j]) > eps) {
				x = k, y = j; 
				db mx = 0;
				REP(k, i, n) if(abs(a[k][j]) > mx) mx = a[k][j], x = k;
				goto edlp;
			} edlp:;
			if(!x) break;
			a[x].swap(a[i]);
			REP(j, 1, n) if(i != j) tadd(i, -a[j][y] / a[i][y], j);
			times(i, 1 / a[i][y]);
		}
	}
	friend matrix operator*(db f, matrix g) {
		int n = SZ(g) - 1, m = SZ(g[1]) - 1;
		REP(i, 1, n) REP(j, 1, m) g[i][j] *= f;
		return g;
	}
	friend matrix operator*(matrix f, matrix g) {
		int n = SZ(f) - 1, m = SZ(g) - 1, s = SZ(g[1]) - 1;
		matrix h(n, s);
		REP(k, 1, m) REP(i, 1, n) REP(j, 1, s) h[i][j] += f[i][k] * g[k][j];
		return h;
	}
	db len2() { return (~*this * *this)[1][1]; }
	db len() { return sqrt(len2()); }
} v[N], Q, d, U, UT, b, xmin, c, ans;

void mian() {
	m = read(), n = read();
	REP(i, 1, n) {
		v[i] = matrix(m, 1);
		REP(j, 1, m) scanf("%Lf", &v[i][j][1]);
		scanf("%Lf", dis + i);
	}
	Q = matrix(n, m), d = matrix(n, 1);
	REP(i, 1, n) {
		d[i][1] = dis[i] * dis[i];
		REP(j, 1, m) d[i][1] -= v[i][j][1] * v[i][j][1];
		REP(j, 1, m) Q[i][j] = -2 * v[i][j][1];
	}
	REP(i, 2, n) Q[i] = Q[i] - Q[1], d[i][1] = d[i][1] - d[1][1];
	Q[1].swap(Q[n]), Q.resize(n); swap(d[1][1], d[n][1]), d.resize(n);
	d = d - Q * v[1];
	Q &= d, Q.gauss();
	static bool isbase[N];
	REP(i, 1, n - 1) {
		int x = 0;
		PER(j, m, 1) if(abs(Q[i][j]) > eps) x = j;
		isbase[x] = true;
	}
	if(count(isbase + 1, isbase + m + 1, true) == m) {
		ans = matrix(m, 1);
		REP(i, 1, m) ans[i][1] = Q[i][m + 1];
		ans = ans + v[1];
		goto skip;
	}
	UT.pb();
	b = matrix(m, 1);
	REP(i, 1, m) if(!isbase[i]) {
		++s;
		UT.pb(m + 1);
		vd &u = UT.back();
		int now = 0;
		REP(j, 1, m) 
			if(j == i) u[j] = 1;
			else if(!isbase[j]) u[j] = 0;
			else u[j] = -Q[++now][i], b[j][1] = Q[now][m + 1];
	}
	U = ~UT;
	Q = UT * U, Q &= -UT * b, Q.gauss();
	c = matrix(s, 1); REP(i, 1, s) c[i][1] = Q[i][s + 1];
	xmin = U * c + b;
	ans = xmin + (sqrt(dis[1] * dis[1] - xmin.len2()) / (~matrix(2, UT[1])).len()) * ~matrix(2, UT[1]), ans = ans + v[1];
	skip: REP(i, 1, m) printf("%.12Lf\n", ans[i][1]);
}
```



---

