# [湖北省选模拟 2023] 路环群山 / mountain

## 题目描述

某二维世界中有一个山地，山体可以用一个函数 $f(x)$ 描述，其表示横坐标 $x$ 的位置海拔高度为 $h=f(x)$。这个世界里有 $n+m$ 只羊，其中有 $n$ 只山羊和 $m$ 只绵羊。我们知道第 $i$ 只山羊所在的横坐标是 $p_i$，第 $j$ 只绵羊所在的横坐标是 $q_j$，但不知道它们所在的高度。不过，我们知道山羊们所在的位置海拔集中在一个较高的范围，而绵羊们所在的位置海拔集中在一个较矮的范围。你需要根据山羊和绵羊的分布情况猜测山体形态 $f(x)$，使得山羊高度的方差和绵羊高度的方差都尽可能小，同时山羊高度尽可能高于绵羊高度。

形式化地，令

$$
\bar{u}=\frac{1}{n}\sum_{i=1}^n f(p_i)
$$

$$
\bar{v}=\frac{1}{m}\sum_{j=1}^m f(q_i)
$$

表示山羊、绵羊分别的平均高度，你的目标就是构造函数 $f$，最小化代价
$$
\operatorname{cost}(f)=\frac{1}{\bar{u}-\bar{v}}\sqrt{\left[\sum_{i=1}^n (f(p_i)-\bar{u})^2\right]+\left[\sum_{j=1}^m (f(q_j)-\bar{v})^2\right]}
$$
当然，**你还需要保证 $\bar u > \bar v + 10^{-9}$**。

方便起见，你需要使用傅里叶级数描述 $f$。即给定 $k$，你需要求出最优的形如 $f(x)=\sum_{i=1}^k a_i\cos(ix)+b_i\sin(ix)$ 的函数 $f$，并输出 $a_i,b_i$ 表示答案。**请你保证 $10^{-9}\le \max_{i=1}^k\{|a_i|,|b_i|\} \le 10^9$**。**数据保证存在满足上述限制的最优解。**

本题开启 Special Judge。给定容错度 $\epsilon=10^{-E}$。当你给出的函数 $f$ 与答案给出的函数 $f^*$ 满足 $\operatorname{cost}(f)<\max(\epsilon+\operatorname{cost}(f^*),(1+\epsilon)\operatorname{cost}(f^*))$ 时认为你的答案正确。

## 说明/提示

### 样例 1 解释

观察到 $\cos(10838702)=\cos(-10838702)\approx 1 =\cos(0)$，$\cos(1)=\cos(-1)\approx 0.5403023$。即当 $f(x)=\cos(x)$ 时，所有山羊几乎均位于同一海拔、所有绵羊均位于同一海拔、山羊所在位置均高于绵羊所在位置。此时 $\operatorname{cost}(f) \approx 0$ 取得最优解。

值得注意的是，对于任何非零数 $r$，函数 $f(x)=r\cos(x)$ 均可视为最优解。

### 样例 2 解释

最优函数（之一）约为 $f(x)=0.6648289523\cos(x)-0.1433645347\sin(x)+0.6172866488\cos(2x)+1.3647253547\sin(2x)$，其代价约为 $3.908439063011$。

### 子任务

对于所有测试数据，保证 $1 \le n,m \le 600$，$1 \le k \le \min\{\dfrac{n+m}{4},300\}$，$0 \le E \le 9$，$0\le |p_i|,|q_i| \le 10^9$。

**保证每个测试数据中，$p_i$ 和 $q_j$ 均在该测试点数据范围内以及问题有解的条件下均匀随机生成。**

![](https://cdn.luogu.com.cn/upload/image_hosting/91am18bk.png)

## 样例 #1

### 输入

```
3 2 1 0
‐10838702 0 10838702
‐1 1```

### 输出

```
1 0```

## 样例 #2

### 输入

```
4 4 2 0
1 3 5 7
2 4 6 8```

### 输出

```
0.6648289523 ‐0.1433645347
0.6172866488 1.3647253547```

## 样例 #3

### 输入

```
见选手目录下的 mountain/mountain3.in 与 mountain/mountain3.ans。```

### 输出

```
见选手目录下的 mountain/mountain3.in 与 mountain/mountain3.ans。```

# 题解

## 作者：littlez_meow (赞：9)

建议改为，偏导数在 OI 中的运用。

[题目指路](https://www.luogu.com.cn/problem/P9547)。

### 题意

给定 $n,m,k,E$ 和长度分别为 $n,m$ 的序列 $p_1\sim p_n,q_1\sim q_m$，记：

$$f(x)=\sum\limits_{i=1}^k\left(a_i\cos(ix)+b_i\sin(ix)\right)$$

$$\bar{u}=\frac{1}{n} \sum\limits_{i=1}^{n} f\left(p_{i}\right)$$

$$\bar{v}=\frac{1}{m} \sum\limits_{j=1}^{m} f\left(q_{i}\right)$$

$$\operatorname{cost}(f)=\frac{1}{\bar{u}-\bar{v}} \sqrt{\sum\limits_{i=1}^{n}\left(f\left(p_{i}\right)-\bar{u}\right)^{2}+\sum\limits_{j=1}^{m}\left(f\left(q_{j}\right)-\bar{v}\right)^{2}}$$

你需要给出两个长为 $k$ 的序列 $a_1\sim a_k,b_1\sim b_k$，使得 $\bar{u}>\bar{v},\operatorname{cost}(f)$ 最小。绝对误差或相对误差小于 $10^{-E}$。

### 思路

下面简记 $\operatorname{cost}(f)$ 为 $c(f)$。

第一眼，$c$ 是一个函数到实数的映射。泛函？这怎么做？

再想一想，其实 $c$ 的值只和 $a_1\sim a_k,b_1\sim b_k$ 这 $2k$ 个取值有关。也就是说，$c$ 是一个 $2k$ 元函数，记为 $c(f)=c(a_1,b_1,\cdots,a_k,b_k)$。很好，至少是个正常的函数了。

$\bar{u}>\bar{v}$ 的限制太烦了，有没有什么办法能绕开呢？

有！如果 $\bar{u}<\bar{v}$，我们直接把所有 $a_i,b_i$ 全部乘 $-1$。这样，函数值乘 $-1$，方差不变，均值之差乘 $-1$，此时的 $\bar{u}>\bar{v}$。

也就是说，我们可以直接计算 $c^2(f)$。这样，根号去掉了，$\bar{u}<\bar{v}$ 时的负数取值也去掉了。根据上面的论述，让 $c(f)$ 取到最小值的 $f$ 也可以让 $c^2(f)$ 取到最小值。这容易用反证法证明。

设 $C(f)=C(a_1,b_1,\cdots,a_k,b_k)=c^2(f)=\dfrac{\sum\limits_{i=1}^n(f(p_i)-\bar{u})^2+\sum\limits_{i=1}^m(f(q_i)-\bar{v})^2}{(\bar{u}-\bar{v})^2}$，我们只需要研究 $C(f)$ 的最值就好了，且没有 $\bar{u}>\bar{v}$ 的要求。

下一步怎么办呢？直接展开 $\bar{u},\bar{v},f$？这样得到的结果会不会太复杂了呢？

最小二乘法的经验告诉我们，我们可以尝试用向量和矩阵来描述上述式子，往往能大幅简化式子。

设 $2k$ 维向量 $\vec{t}=[a_1,b_1,\cdots,a_k,b_k]^T,\vec{f}(x)=[\cos(x),\sin(x),\cdots,\cos(kx),\sin(kx)]^T$。不难验证 $f(x)=\vec t\cdot\vec f(x)$。下面如果没有特殊说明，向量都是 $2k$ 维的。

现在 $C(f)$ 就是一个关于 $\vec t$ 的函数了，记为 $C(\vec t)$。

设 $\vec p_i=\vec f(p_i),\vec q_i=\vec f(q_i)$。我们可以直接算出所有 $\vec p_i,\vec q_i$，$C(f)$ 就跟 $\cos,\sin$ 没有半点关系了。

现在来看看 $\bar{u}$ 是怎么算出来的吧。

写出原式：$\bar u=\dfrac 1 n\sum\limits_{i=1}^nf(p_i)$。

带入 $f(x)=\vec t\cdot\vec f(x)$，得到：$\bar u=\dfrac 1 n\sum\limits_{i=1}^n\vec t\cdot\vec p_i$。

使用向量点乘和加法的分配律：$\bar u=\vec t\cdot(\dfrac 1 n\sum\limits_{i=1}^n\vec p_i)$

右边就是一个常向量了，记 $\vec r=\dfrac 1 n\sum\limits_{i=1}^n\vec p_i$，则 $\bar u=\vec t\cdot\vec r$。

同理，记 $\vec s=\dfrac 1 m\sum\limits_{i=1}^m\vec q_i$，则 $\bar v=\vec t\cdot\vec s$。

现在，把这些向量带回原式：

$$C(\vec t)=\dfrac{\sum\limits_{i=1}^n(\vec t\cdot(\vec p_i-\vec r))((\vec p_i-\vec r)\cdot\vec t)+\sum\limits_{i=1}^m(\vec t\cdot(\vec q_i-\vec s))((\vec q_i-\vec s)\cdot\vec t)}{(\vec t\cdot(\vec r-\vec s))^2}$$

点积破坏了我们很多美好的性质，可不可以去掉它呢？

对于列向量 $\vec a,\vec b$，容易发现 $\vec a^T\vec b=[\vec a\cdot\vec b]$。我们只要认为 $1\times1$ 的矩阵就是一个数，就可以用矩阵乘法代替点积。

用矩阵乘法代替点积，使用结合律和分配律，得到：

$$C(\vec t)=\dfrac{\vec t^T(\sum\limits_{i=1}^n(\vec p_i-\vec r)(\vec p_i-\vec r)^T+\sum\limits_{i=1}^m(\vec q_i-\vec s)(\vec q_i-\vec s)^T)\vec t}{\vec t^T((\vec r-\vec s)(\vec r-\vec s)^T)\vec t}$$

好！中间括号里面的都变成常矩阵了！设矩阵 $A=\sum\limits_{i=1}^n(\vec p_i-\vec r)(\vec p_i-\vec r)^T+\sum\limits_{i=1}^m(\vec q_i-\vec s)(\vec q_i-\vec s)^T$，矩阵 $B=(\vec r-\vec s)(\vec r-\vec s)^T$，我们就可以化简为：

$$C(\vec t)=\dfrac{\vec t^TA\vec t}{\vec t^TB\vec t}$$

非常美的一个结果。

现在就是多元函数求最值问题了，方法是对每一元求偏导并使其等于 $0$。

设 $A_{i,j}$ 表示 $A$ 第 $i$ 行第 $j$ 列的元素，$B_{i,j}$ 同理。

为了方便，设 $x_{2i+1}=a_i,x_{2i}=b_i$。

展开矩阵并化简，我们有:

$$C(f)=\dfrac{\sum\limits_{i=1}^{2k}\sum\limits_{j=1}^{2k}x_ix_jA_{i,j}}{\sum\limits_{i=1}^{2k}\sum\limits_{j=1}^{2k}x_ix_jB_{i,j}}$$

我们发现分子分母都是关于某个自变量的二次函数，容易求偏导。

求导后，我们的结果中还存在一些高次项。加加减减消掉它们，我们发现系数又变成了矩阵的元素！只是等式右边带一个非零常数。即有以下方程：

$$A\vec t=(\vec r-\vec s)t$$

这也是合理的。因为 $a,b$ 等比例放大，标准差也等比例放大，平均数同样等比例放大，在分式上的比例最后就消掉了。样例解释一也说明了这点。高斯消元解之即可。

最后，还有高斯消元无解的情况。注意到数据范围里说 $p,q$ 随机生成，直接赌不会无解就好。

时间复杂度 $O(k^3)$，$k,n,m$ 视为同阶。

如果你的 $p,q$ 是整型，记得转成浮点型，否则你会因为溢出只有二十四分。

### 代码

```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i)
#define File(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define ll long long
using namespace std;
const int MAXN=601;
int n,m,k,kk,e,p[MAXN],q[MAXN];
double vecp[MAXN][MAXN],vecq[MAXN][MAXN],r[MAXN],s[MAXN];
double factor[MAXN][MAXN+1];
double a[MAXN],b[MAXN];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>k>>e;
	kk=k<<1;
	F(i,1,n){
		cin>>p[i];
		F(j,1,k) r[(j<<1)-1]+=(vecp[i][(j<<1)-1]=cos(j*1.0*p[i])),r[j<<1]+=(vecp[i][j<<1]=sin(j*1.0*p[i]));
	}
	F(i,1,m){
		cin>>q[i];
		F(j,1,k) s[(j<<1)-1]+=(vecq[i][(j<<1)-1]=cos(j*1.0*q[i])),s[j<<1]+=(vecq[i][j<<1]=sin(j*1.0*q[i]));
	}
	F(i,1,kk) r[i]/=n,s[i]/=m,factor[i][kk+1]=r[i]-s[i];
	F(i,1,kk) F(j,1,kk){
		F(t,1,n) factor[i][j]+=(vecp[t][i]-r[i])*(vecp[t][j]-r[j]);
		F(t,1,m) factor[i][j]+=(vecq[t][i]-s[i])*(vecq[t][j]-s[j]);
	}
	F(i,1,kk){
		int mx=i;
		F(j,i+1,kk) fabs(factor[j][i])>fabs(factor[mx][i])&&(mx=j);
		swap(factor[i],factor[mx]);
		F(j,i+1,kk){
			double delta=factor[j][i]/factor[i][i];
			F(t,i,kk+1) factor[j][t]-=factor[i][t]*delta;
		}
	}
	R(i,kk,1){
		if(i&1){
			double&qwq=a[(i+1)>>1];
			qwq=factor[i][kk+1]/factor[i][i];
			R(j,i-1,1) factor[j][kk+1]-=qwq*factor[j][i];
		}
		else{
			double&qwq=b[(i+1)>>1];
			qwq=factor[i][kk+1]/factor[i][i];
			R(j,i-1,1) factor[j][kk+1]-=qwq*factor[j][i];
		}
	}
	double u=0,v=0;
	F(i,1,k){
		u+=r[(i<<1)-1]*a[i]+r[i<<1]*b[i];
		v+=s[(i<<1)-1]*a[i]+s[i<<1]*b[i];
	}
	if(u<v) F(i,1,k) a[i]=-a[i],b[i]=-b[i];
	cout<<fixed<<setprecision(12);
	F(i,1,k) cout<<a[i]<<" "<<b[i]<<"\n";
	return 0;
} 
```

---

