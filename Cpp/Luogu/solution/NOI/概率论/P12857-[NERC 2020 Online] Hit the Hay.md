# [NERC 2020 Online] Hit the Hay

## 题目描述

有人认为哄婴儿入睡是一门艺术，但这个问题将证明它其实只是数学。

考虑一个夜晚，父母正试图哄婴儿入睡。闹钟会在夜晚结束时响起，父母不能更改闹钟时间，因此夜晚的时长固定为从现在开始的 $k$ 小时。

婴儿可能处于以下三种状态之一：
- 状态 0 表示婴儿醒着；
- 状态 1 表示婴儿处于浅睡眠；
- 状态 2 表示婴儿处于深睡眠。

婴儿初始状态为 0，状态变化是连续而非离散的。给定三个概率值 $p_0$、$p_1$ 和 $p_2$。当婴儿处于状态 $i$ 时，接下来的 $x$ 小时内不发生状态变化的概率为 $p_i^x$（$x$ 为正实数）。换句话说，下一次状态变化的时间服从**指数分布**，其累积分布函数为 $1 - p_i^x$。

当状态变化发生时：
- 如果婴儿当前处于状态 0，则必定转移到状态 1；
- 如果处于状态 2，也必定转移到状态 1；
- 如果处于状态 1，则以概率 $q_0$ 转移到状态 0，以概率 $1 - q_0$ 转移到状态 2。

父母可以自行决定何时入睡，但只有婴儿处于状态 1 或 2 时才能入睡（状态 0 时婴儿会哭闹吵醒父母）。即使婴儿处于可入睡状态，父母也可以选择保持清醒。若保持清醒，父母可以：
1. 观察婴儿当前状态；
2. 阻止婴儿醒来：如果婴儿根据规则本应从状态 1 转移到状态 0，而父母未入睡，则婴儿会被安抚并保持在状态 1。

父母可以根据婴儿当前状态或时间等因素自由决定何时入睡。一旦入睡，将持续睡眠直到：
- 婴儿醒来（进入状态 0），或
- 闹钟在 $k$ 小时结束时响起。

若被婴儿吵醒，父母可以再次选择入睡时机。

**问题**：在最优策略下，父母能获得的最大期望睡眠时长是多少？

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
10.0 0.5 0.5 0.5 0.5
8.0 0.1 0.9 0.9 0.1```

### 输出

```
6.5990202123649855
7.540407031059442```

# 题解

## 作者：littlez_meow (赞：1)

算上父母有五种状态：婴儿状态 $0$、父母入睡婴儿状态 $1,2$ 、父母未入睡婴儿状态 $1,2$。我们称为状态 $0,1,2,3,4$。

对于时间离散的情况，我们可以直接设 $f_i(t)$ 表示当前处于状态 $i$，距离夜晚结束还有 $t$ 时刻的最优策略下睡眠的期望时间。

但是非常可惜的是，这里时间是连续的。

不过我们还是可以考虑一个最小时间单位 $\epsilon\to 0$。

以 $f_1$ 为例，写出转移：

$$f_1(t+\epsilon)=\epsilon+p_1^{\epsilon}f_1(t)+(1-p_1^{\epsilon})(q_0f_0(t)+(1-q_0)f_2(t))$$

等式两边同时减掉 $f_1(t)$：

$$f_1(t+\epsilon)-f_1(t)=\epsilon+(p_1^{\epsilon}-1)f_1(t)+(1-p_1^{\epsilon})(q_0f_0(t)+(1-q_0)f_2(t))$$

再同时除掉 $\epsilon$：

$$\dfrac{f_1(t+\epsilon)-f_1(t)}{\epsilon}=1+\dfrac{p_1^{\epsilon}-1}{\epsilon}-\dfrac{p_1^{\epsilon}-1}{\epsilon}(q_0f_0(t)+(1-q_0)f_2(t))$$

左边是导数定义，右边的 $\dfrac{p_1^\epsilon-1}{\epsilon}$ 相当于是函数 $g(x)=p_1^{x}$ 在 $x=0$ 处的导数 $g'(0)=\ln p_1$。带入化简得到：

$$f_1'(t)=1+f_1(t)\ln p_1-(q_0f_0(t)+(1-q_0)f_2(t))\ln p_1$$

同理我们还可以写出 $f_0,f_2$ 的转移：

$$f_0'(t)=f_0(t)\ln p_0-f_3(t)\ln p_0$$

$$f_2'(t)=1+f_2(t)\ln p_2-f_1(t)\ln p_2$$

然后是状态 $4$。现在已经是最佳状态，如果现在不决策入睡其他状态就更不会睡了，所以：

$$f_4(t)=f_2(t)$$

最麻烦的是状态 $3$，因为可以选择是否入睡。具体地：

$$f_3(t+\epsilon)=\max\{f_1(t+\epsilon),p_1^\epsilon f_3(t)+(1-p_1^\epsilon)(q_0f_3(t)+(1-q_0)f_4(t))\}$$

先研究取到第一项的情况，即 $f_3(t)=f_1(t)$。

那么上式即：

$$f_3'(t)=\max\{f_1'(t),f_1(t)\ln p_1-(q_0f_1(t)+(1-q_0)f_2(t))\ln p_1\}$$

把第一项减去第二项得到 $1+q_0(f_1(t)-f_0(t))\ln p_1$。如果取到第二项，则该式 $\le 0$，即：

$$-q_0(f_1(t)-f_0(t))\ln p_1\ge 1$$

感性上，$f_1(t)-f_0(t)$ 应该是单调递增的。所以在解出来 $f_3(t)=f_1(t)$ 的微分方程组之后，我们可以二分出满足上式最小的 $t$，然后在 $t$ 大于这个值的时候解出 $f_3(t)$ 取第二项的微分方程组。

具体地，我们的算法流程应该为：

1. 求解如下常系数一阶线性微分方程组：

  $$\left\{\begin{matrix}f_0'(t)=f_0(t)\ln p_0-f_3(t)\ln p_0 \\f_1'(t)=1+f_1(t)\ln p_1-(q_0f_0(t)+(1-q_0)f_2(t))\ln p_1 \\f_2'(t)=1+f_2(t)\ln p_2-f_1(t)\ln p_2 \\f_3(t)=f_1(t) \\f_4(t)=f_2(t) \\f_0(0)=f_1(0)=f_2(0)=f_3(0)=f_4(0)=0\end{matrix}\right.$$

2. 二分找到满足 $-q_0(f_1(t)-f_0(t))\ln p_1\ge 1$ 的最小的 $t$ 为 $v$，则上述解的定义域为 $[0,l]$。

3. 求解如下常系数一阶线性微分方程组，其中 $t\ge l$，初值为 $t=l$ 时与第一步中的解数值相同：

  $$\left\{\begin{matrix}f_0'(t)=f_0(t)\ln p_0-f_3(t)\ln p_0 \\f_1'(t)=1+f_1(t)\ln p_1-(q_0f_0(t)+(1-q_0)f_2(t))\ln p_1 \\f_2'(t)=1+f_2(t)\ln p_2-f_1(t)\ln p_2 \\f_3'(t)=f_3(t)\ln p_1-(q_0 f_3(t)+(1-q_0)f_4(t))\ln p_1 \\f_4(t)=f_2(t) \end{matrix}\right.$$

4. 答案为 $f_0(k)$。

最后的问题是，如何求解一阶线性微分方程组。

第一种方法是求精确解。我们有：

**【常系数一阶线性微分方程组解的结构】** 对于常系数一阶线性微分方程组 $\dfrac{\mathrm{d}\vec X}{\mathrm{d}t}=A\vec X+F$，其中对向量求导定义为对向量每一维求导，其通解形式为 $\vec X=e^{At}\vec X(0)+\vec \varphi$，其中向量函数定义为对每一维代入自变量，矩阵指数定义为泰勒级数，$\vec\varphi$ 为特解。

至于特解，官方题解说可以观察到 $A$ 每一行的和都是 $0$，所以 $0$ 是 $A$ 的特征值，故特解可以被看成线性函数。

但是这种方法麻烦完了。既然这题概率不取模，我们完全可以用基于精度的方法。

考虑四阶 Runge–Kutta 法。设 $y=y(x)$，下面简述对于微分方程 $y'=f(x,y)$ 如何求，微分方程组改成向量就行。

我们取步长 $h$，设 $x_i=ih+x_0,y_i=y(x_i)$。

使用拉格朗日中值定理，存在 $t\in[x_i,x_{i+1}]$，使得 $y_{i+1}=y_i+hy'(t)$。

我们使用 $[x_i,x_{i+1}]$ 区间上的平均斜率来近似 $y'(t)$。

设 $k_1=f(x_i,y_i),k_2=f(x_i+\frac h 2,y_i+\frac h 2k_1),k_3=f(x_i+\frac h 2,y_i+\frac h 2k_2),k_4=f(x_i+h,y_i+hk_3)$。把它们加权平均得到 $k^*=\frac 1 6(k_1+2k_2+2k_3+k_4)$，直接估算 $y'(t)=k^*$。

取步长 $h=\dfrac k C$，时间复杂度为 $O(TC)$。我取的是 $C=5\times 10^4$。

### 代码

```cpp
#include<bits/stdc++.h>
#define File(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define ll long long
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i)
using namespace std;
const int C=50000;
double k,p0,p1,p2,q0,h;
inline array<double,4> calc1(double x,const array<double,4>&y){
	array<double,4>res;
	res[0]=y[0]*p0-y[3]*p0;
	res[1]=1+y[1]*p1-(q0*y[0]+(1-q0)*y[2])*p1;
	res[2]=1+y[2]*p2-y[1]*p2;
	res[3]=res[1];
	return res;
}
inline array<double,4> calc2(double x,const array<double,4>&y){
	array<double,4>res;
	res[0]=y[0]*p0-y[3]*p0;
	res[1]=1+y[1]*p1-(q0*y[0]+(1-q0)*y[2])*p1;
	res[2]=1+y[2]*p2-y[1]*p2;
	res[3]=y[3]*p1-(q0*y[3]+(1-q0)*y[2])*p1;
	return res;
}
array<double,4> operator+(const array<double,4>&a,const double&b){return {a[0]+b,a[1]+b,a[2]+b,a[3]+b};}
array<double,4> operator+(const array<double,4>&a,const array<double,4>&b){return {a[0]+b[0],a[1]+b[1],a[2]+b[2],a[3]+b[3]};}
array<double,4> operator*(const double&b,const array<double,4>&a){return {a[0]*b,a[1]*b,a[2]*b,a[3]*b};}
double x[C*2];
array<double,4>y[C*2];
inline void solve1(){
	y[0]={0,0,0,0};
	array<double,4>k1,k2,k3,k4;
	F(i,1,C){
		k1=calc1(x[i-1],y[i-1]);
		k2=calc1(x[i-1]+h/2,y[i-1]+h/2*k1);
		k3=calc1(x[i-1]+h/2,y[i-1]+h/2*k2);
		k4=calc1(x[i-1]+h,y[i-1]+h*k3);
		y[i]=y[i-1]+h/6*(k1+2*k2+2*k3+k4);
	}
}
inline void solve2(int l){
	array<double,4>k1,k2,k3,k4;
	F(i,l,C){
		k1=calc2(x[i-1],y[i-1]);
		k2=calc2(x[i-1]+h/2,y[i-1]+h/2*k1);
		k3=calc2(x[i-1]+h/2,y[i-1]+h/2*k2);
		k4=calc2(x[i-1]+h,y[i-1]+h*k3);
		y[i]=y[i-1]+h/6*(k1+2*k2+2*k3+k4);
	}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	int T;
	cout<<fixed<<setprecision(12);
	for(cin>>T;T;--T){
		cin>>k>>p0>>p1>>p2>>q0;
		p0=log(p0),p1=log(p1),p2=log(p2);
		h=k/C;
		F(i,0,C) x[i]=i*h;
		solve1();
		int l=0,r=C+1;
		while(l<r){
			int mid=(l+r)>>1;
			if(-q0*(y[mid][1]-y[mid][0])*p1>=1) r=mid;
			else l=mid+1;
		}
		if(l!=C+1) solve2(l);
		cout<<y[C][0]<<"\n";
	}
	return 0;
}
```

---

