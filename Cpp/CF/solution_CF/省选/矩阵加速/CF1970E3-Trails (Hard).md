# Trails (Hard)

## 题目描述

哈利·波特正在日内瓦湖周围的阿尔卑斯山徒步旅行。在这个区域有 $m$ 个小屋，编号为 $1$ 到 $m$。每个小屋都通过一条或多条小路与湖边的一个中心集合点相连。每条小路要么是短路，要么是长路。第 $i$ 个小屋通过 $s_i$ 条短路和 $l_i$ 条长路与湖相连。

每天，哈利会从他当前所在的小屋走一条小路到日内瓦湖，然后从湖边再走一条小路到任意一个小屋（包括他出发的小屋）。但是，由于他必须在一天内完成徒步，所走的两条小路中至少有一条必须是短路。

如果哈利从第 $1$ 个小屋出发，连续徒步 $n$ 天，他一共可以有多少种不同的小路组合？

请将答案对 $10^9+7$ 取模后输出。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2
1 0 1
0 1 1```

### 输出

```
18```

# 题解

## 作者：lvvd (赞：8)

看了眼题解区，好像还没有我这种思路的题解，决定写一份。不需要复杂的 dp 推导或矩阵推导的。

---

需要注意到：如果当前位于湖，再前往一个木屋，接下来就是直接从这个木屋回来了，这个过程的方案计算不受其它木屋的情况影响。

可将问题考虑为：一天的后半天从湖出发，选择一个木屋到达（如果这天的前半天走了短路，那么此时随便选一条路即可，否则只能选短路），第二天前半天再选择一条路走回来。

第一天前半天和最后一天后半天特殊考虑一下即可。

这个计算方法每次的转移都是一样的，可以用矩阵优化。并且状态只有两个（当天后半天必须走短路/长路短路都可以走）。

令 $f_{i, 0 / 1}$ 表示第 $i$ 天后半天长路短路都可以走/必须走短路，可得到转移方程：

$$
dp_{i, 0} = dp_{i - 1, 0} \times \left(\sum\limits_{j = 1}^{m}s_{j}(s_{j} + l_{j})\right) + dp_{i - 1, 1} \times \left(\sum\limits_{j = 1}^{m}s_{j}^{2}\right)\\
dp_{i, 1} = dp_{i - 1, 0} \times \left(\sum\limits_{j = 1}^{m}l_{j}(s_{j} + l_{j})\right) + dp_{i - 1, 1} \times \left(\sum\limits_{j = 1}^{m}s_{j}l_{j}\right)
$$

每次转移的系数都相同，可以提前处理一个转移矩阵然后快速幂优化。

显然 $f_{1, 0} = s_{1}, f_{1, 1} = l_{1}$，对于每个木屋计算一下其作为最后一天到达的木屋的方案数求和即为答案。

时间复杂度 $\mathcal{O}(m + \log n)$，其中 $\log n$ 带了一个 $2^{3}$ 的常数。

Code（省略 `modint` 以及 `matrix` 模板）：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int mod = 1000000007;
matrix base, res;
int m, n, s[100005], l[100005];
modint ans, f0, f1;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> m >> n;
	for(int i = 1; i <= m; ++i) cin >> s[i];
	for(int i = 1; i <= m; ++i) cin >> l[i];
	for(int i = 1; i <= m; ++i) {
		base.val[0][0] += (s[i] + l[i]) * s[i], base.val[0][1] += (s[i] + l[i]) * l[i];
		base.val[1][0] += s[i] * s[i], base.val[1][1] += s[i] * l[i];
	}
	res = ksm(base, n - 1);//这里是快速幂优化
	f0 = s[1] * res.val[0][0] + l[1] * res.val[1][0];
	f1 = s[1] * res.val[0][1] + l[1] * res.val[1][1];
	for(int i = 1; i <= m; ++i) {
		ans += f0 * (s[i] + l[i]) + f1 * s[i];
	}
	cout << ans;
	return 0;
}
```

---

## 作者：inc1ude_c (赞：4)

> 给定一 $m+1$ 个点的菊花图，叶子编号为 $1\sim m$，叶子 $i$ 向根连了 $s_i$ 条双向轻边，$l_i$ 条双向重边，**边都有标号**，第一天在 $1$ 号点，每天可以选一条边上到根再选一条边下到某一个叶子，但这两条边得至少一条是轻边，问走 $n$ 天的方案数。

建议评蓝或紫。

有一显然 DP：$f(i,u)$ 为到了第 $i$ 天，走到叶子 $u$ 的方案数。

$$f(i,u)=\sum_vf(i-1,v)\times (s_u(s_v+l_v)+l_us_v)$$

直接矩阵快速幂只能过 Medium 版本，考虑优化。

$$f(i,u)=\sum_vf(i-1,v)\times (s_us_v+s_ul_v+l_us_v)$$

设 $w_u=s_u+l_u$，则有：

$$f(i,u)=\sum_vf(i-1,v)\times (w_uw_v-l_ul_v)$$

写出其转移矩阵

$$\begin{bmatrix}f(i,1)
 \\f(i,2)
 \\\vdots 
\\f(i,m)
\end{bmatrix}=
\begin{bmatrix}  
  w_1w_1-l_1l_1& w_1w_2-l_1l_2& \cdots  & w_1w_m-l_1l_m \\  
  w_2w_1-l_2l_1& w_2w_2-l_2l_2& \cdots  & w_2w_m-l_2l_m \\  
  \vdots & \vdots & \ddots & \vdots \\  
  w_mw_1-l_ml_1& w_mw_2-l_ml_2& \cdots  & w_mw_m-l_ml_m 
\end{bmatrix}  
\begin{bmatrix}f(i-1,1)
 \\f(i-1,2)
 \\\vdots 
\\f(i-1,m)
\end{bmatrix}$$

注意到转移矩阵有：
$$
\begin{bmatrix}  
  w_1w_1-l_1l_1& w_1w_2-l_1l_2& \cdots  & w_1w_m-l_1l_m \\  
  w_2w_1-l_2l_1& w_2w_2-l_2l_2& \cdots  & w_2w_m-l_2l_m \\  
  \vdots & \vdots & \ddots & \vdots \\  
  w_mw_1-l_ml_1& w_mw_2-l_ml_2& \cdots  & w_mw_m-l_ml_m 
\end{bmatrix} =
\begin{bmatrix}  
  w_1 &l_1\\  
  w_2 &l_2\\  
  \vdots & \vdots\\  
   w_m &l_m 
\end{bmatrix}  
\begin{bmatrix}  
  w_1 &w_2&\cdots &w_m\\  
 -l_1 &-l_2&\cdots &-l_m
\end{bmatrix}  
$$
换元：

$$A=B\times C$$

于是答案为：$A^n=(BC)^n=B(CB)^{n-1}C$。

而 $CB$ 是一个 $2\times 2$ 的矩阵所以复杂度对了，然后直接写会获得 MLE。

[MLE Code](https://codeforces.com/contest/1970/submission/261996269)

原来 $B(CB)^{n-1}$ 是 $m\times 2$ 的矩阵，而 $C$ 是 $2\times m$ 的矩阵，相乘会得到 $m^2$ 的矩阵。

但不要紧，因为答案只关心该矩阵的第一列。

故最后一次矩阵乘法只算第一列，复杂度就对了。

[AC Code](https://codeforces.com/contest/1970/submission/262002329)

---

## 作者：zhongpeilin (赞：3)

## 题目大意：
山峰脚下有 $m$ 个房子，第 $i$ 个房子与山峰有 $s_{i}$ 条短路，有 $t_{i}$ 条长路，一个人在一天之内要从房子出发到山后再去另一个房子，且走的路至少有一条短路，第一天前这个人在 `1` 号房里，$n$ 天后问他有多少可行方案。  
## 解题思路：
### E1：
我们可以设 $dp_{i, j}$ 表示前 $i$ 天后在第 $j$ 个房子里的方案数。那么枚举前 $i-1$ 天后他在哪个屋里转移即可。  
$$dp_{i, j} = \sum_{k = 1}^{m} dp_{i - 1, k} \times (s_{j} \times s_{k} + s_{j} \times l_{k} + l_{j} \times s_{k})$$  
时间复杂度 $O(n \times m^2)$，可以通过 E1。  

### E2：
由于 E2 中 $n \leq 10^9$，但 $m \times 10^2$，所以可以考虑矩阵快速幂优化 dp，矩阵的数就是转移系数，设 $c_{i} = s_{i} + l_{i}$，那么矩阵如下：
$$
\begin{bmatrix}
c_{1} \times c_{1} - l_{1} \times l_{1} & c_{1} \times c_{2} - l_{1} \times l_{2} & c_{1} \times c_{3} - l_{1} \times l_{3} & \dots \\
c_{2} \times c_{1} - l_{2} \times l_{1} & c_{2} \times c_{2} - l_{2} \times l_{2} & c_{2} \times c_{3} - l_{2} \times l_{3} & \dots \\
c_{3} \times c_{1} - l_{3} \times l_{1} & c_{3} \times c_{3} - l_{3} \times l_{2} & c_{3} \times c_{3} - l_{3} \times l_{3} & \dots \\
\dots & \dots & \dots & \dots
\end{bmatrix}
$$
那么答案就是这个矩阵的 $n$ 次幂后第一列的总和。  
时间复杂度：$O(m^3 \log n)$。  

### E3：
这次 $m$ 变成 $10^5$，矩阵都开不下了。  
我们观察矩阵的系数，发现他等价于：
$$
\begin{bmatrix}
c_{1} & l_{1} \\
c_{2} & l_{2} \\
c_{3} & l_{3} \\
\dots & \dots 
\end{bmatrix}
\times 
\begin{bmatrix}
c_{1} & c_{2} & c_{3} & \dots \\
-l_{1} & -l_{2} & -l_{3} & \dots 
\end{bmatrix}
$$
那么设左边的矩阵为 $A$，右边的为 $B$，答案就是
$$(AB)^n 的最左侧一列的数的和$$
但是这样还是不行，我们将式子转化一下，由于矩阵有结合律，所以 $(AB)^n = A \times (BA)^{n-1} \times B$。  

因为 $AB$ 是一个 $2 \times 2$ 的矩阵，所以就可以直接加速。  

那么设加速后的矩阵为 $C$，则最终矩阵为 $A \times C \times B$，$A \times C$ 是一个 $m \times 2$ 的矩阵，可 $A \times C \times B$ 是一个 $m \times m$ 的矩阵，但答案只考虑第一列的和，所以我们做最后一次矩阵乘法的时候只算第一列的和即可。  
##
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9 + 7;
struct mat{
	int a[2][2];
}ditui, ans;
mat operator * (mat A, mat B){
	mat C;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j< 2; j++){
			C.a[i][j] = 0;
			for(int k = 0; k < 2; k++){
				C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % mod;
			}
		}
	}
	return C;
}
int matrix[100005][2], sum;
int m, n, a[100005], b[100005];
int lie[100005][2], heng[2][100005];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> m >> n;
	for(int i = 1; i <= m; i++) cin >> a[i];
	for(int i = 1; i <= m; i++) cin >> b[i];
	for(int i = 1; i <= m; i++){
		heng[0][i] = a[i] + b[i]; heng[1][i] = ((-b[i]) % mod + mod) % mod;
	}
	for(int i = 1; i <= m; i++){
		lie[i][0] = a[i] + b[i]; lie[i][1] = b[i];
	}
	for(int i = 0; i < 2; i++){
		for(int j = 0; j< 2; j++){
			ditui.a[i][j] = 0;
			for(int k = 1; k <= m; k++){
				ditui.a[i][j] = (ditui.a[i][j] + heng[i][k] * lie[k][j]) % mod;
			}
		}
	}
	ans = ditui;
	int B = n - 2;
	while(B){
		if(B % 2) ans = ans * ditui;
		ditui = ditui * ditui;
		B /= 2;
	}
	for(int i = 1; i<= m; i++){
		for(int j = 0; j < 2; j++){
			for(int k = 0; k < 2; k++){
				matrix[i][j] = (matrix[i][j] + lie[i][k] * ans.a[k][j]) % mod;
			}
		}
	}
	for(int i = 1; i <= m; i++){
		int j = 1;
		for(int k = 0; k < 2; k++){
			sum = (sum + matrix[i][k] * heng[k][j]) % mod;
		}
	}
	cout << sum<< endl;
	return 0;
}

---

## 作者：yingkeqian9217 (赞：3)

# 前置芝士

~~简单的~~[矩阵乘法](https://oi.wiki/math/linear-algebra/matrix/)。

# 题目描述

有 $m$ 个点，编号从 $1$ 到 $m$。每个点都有一条或多条边与中心点相连。$i$ 号点通过 $s_i$ 条短边和 $l_i$ 条长边与中心点相连。

每次，你要从当前点经过边到中心点，再到另一点，但是要保证两边中至少有一个短边。如果你从 $1$ 号点出发，走 $n$ 次，你有多少种走法？

模上 $10^9+7$。

# 题目分析

## Step.0

审题，此处为方案数，并非经过边数。

## Step.1

考虑方案数 `dp`，令 $f_{i,j}$ 表示第 $j$ 次在 $i$ 号点的方案数。

初始化显然，$f_{0,1}=1$，其它均为 $0$。因为初始在 $1$ 点。

转移方程：考虑枚举上一轮所在位置，得

$$f_{i,j}=(s_i+l_i)\sum_{k=1}^{m} s_k\times f_{k,j-1}+s_i\sum_{k=1}^ml_k\times f_{k,j-1}$$

最终答案为 $\sum_{i=1}^m f_{i,n}$。

时间复杂度 $O(nm^2)$。

## Step.2

注意到，$\sum_{k=1}^{m} s_k\times f_{k,j}$ 和 $\sum_{k=1}^ml_k\times f_{k,j}$ 在一次中为定值，分别记为 $S_{j},L_{j}$，于是得到

$$f_{i,j}=(s_i+l_i)S_{j-1}+s_iL_{j-1}$$

$$S_j=\sum_{i=1}^{m}s_if_{i,j}=\sum_{i=1}^{m}s_i[(s_i+l_i)S_{j-1}+s_iL_{j-1}]=\sum_{i=1}^{m}(s_i^2+s_il_i)S_{j-1}+\sum_{i=1}^{m}s_i^2L_{j-1}$$

发现 $\sum_{i=1}^{m}s_i^2$ 和 $\sum_{i=1}^{m}s_il_i$ 均为常数，记为 $s^2$，$sl$。同理记 $\sum_{i=1}^{m}l_i^2$ 为 $l^2$，得

$$S_i=(s^2+sl)\times S_{i-1}+sl\times L_{i-1}$$

$$L_i=(sl+l^2)\times S_{i-1}+l^2\times L_{i-1}$$

记最终答案为 $A_n$，则

$A_i=\sum_{j=1}^{m} f_{j,i}=\sum_{j=1}^{m} (s_j+l_j)S_{i-1}+s_jL_{i-1}$

即最终答案 $A_n=\sum_{j=1}^{m} (s_j+l_j)S_{n-1}+s_jL_{n-1}$。

注意初始 $S_0=s_1,L_0=l_1$。

时间复杂度 $O(m+n)$。

## Step.3

我们发现上面这个式子~~看起来就很矩阵~~，为线性变换，考虑矩阵加速，记录向量  $V_i=\begin{bmatrix}
 S_i & L_i
\end{bmatrix}$，初始 $V_0=\begin{bmatrix}
 s_1 & l_1
\end{bmatrix}$。

由上式知转移矩阵 $P=\begin{bmatrix}
s^2+sl  & sl+l^2 \\
sl  & l^2
\end{bmatrix}$，于是 $V_i=V_0\times P^{i}$。可以矩阵快速幂优化。

因为最终只要算总和即可，所以算 $V_{n-1}=V_0\times P^{n-1}$ 即可，记 $E= \begin{bmatrix}
\sum_{i=1}^{m} (s_i+l_i)  & \sum_{i=1}^{m}s_i\\
 0 &0\end{bmatrix}$，则记 $Ans=V_{n-1}\times E$，即

$$Ans=\begin{bmatrix}
 s_1 & l_1
\end{bmatrix}\times \begin{bmatrix}
s^2+sl  & sl+l^2 \\
sl  & l^2
\end{bmatrix}^{n-1}\times \begin{bmatrix}
\sum_{i=1}^{m} (s_i+l_i)  & \sum_{i=1}^{m}s_i\\
 0 &0\end{bmatrix}$$

答案 $A_n$ 即为 $Ans$ 的第一个数。

时间复杂度 $O(m+\log n)$。

# 代码

本人第一次写矩阵，写的有点丑，凑合一下。

```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 700005
const int Mod=1e9+7;
using namespace std;
int n,m,s[maxn],l[maxn],S,L,ss,sl,ll;
struct mtx{
	int lenx,leny,a[100][100];
	mtx(){
		lenx=leny=2;
		for(int i=0;i<lenx;i++)
		 for(int j=0;j<leny;j++)
		  a[i][j]=0;
	    a[0][0]=a[1][1]=1;
	}
	mtx(int op,int x,int y){
		if(!op){
			lenx=leny=2;
			for(int i=0;i<lenx;i++)
		     for(int j=0;j<leny;j++)
		      a[i][j]=0;
			a[0][0]=x%Mod;
			a[1][1]=y%Mod;
		}
		else{
			lenx=1;
			leny=2;
			for(int i=0;i<lenx;i++)
			 for(int j=0;j<leny;j++)
	   		  a[i][j]=0;
			a[0][0]=x%Mod;
			a[0][1]=y%Mod;
		}
	}
	mtx(int p1,int p2,int p3,int p4){
		lenx=leny=2;
		for(int i=0;i<lenx;i++)
		 for(int j=0;j<leny;j++)
		  a[i][j]=0;
		a[0][0]=p1;
		a[1][0]=p2;
		a[0][1]=p3;
		a[1][1]=p4;
	}
	mtx operator =(mtx x){
		for(int i=0;i<lenx;i++)
		 for(int j=0;j<leny;j++)
		  a[i][j]=0;
		lenx=x.lenx;
		leny=x.leny;
		for(int i=0;i<lenx;i++)
		 for(int j=0;j<leny;j++)
		  a[i][j]=x.a[i][j];
		return x;
	}
};
mtx operator *(mtx x,mtx y){
	mtx sum(0,0,0);
	sum.lenx=x.lenx;
	sum.leny=y.leny;
	for(int i=0;i<x.lenx;i++)
	 for(int j=0;j<y.leny;j++)
	  for(int k=0;k<x.leny;k++)
	   sum.a[i][j]=(sum.a[i][j]+x.a[i][k]*y.a[k][j]%Mod)%Mod;
	return sum;
}
mtx qpow(mtx x,int y){
	mtx res;
    while(y){
		if(y&1) res=res*x;
		x=x*x;
		y>>=1;
	}
	return res;
}
signed main(){
	scanf("%lld%lld",&m,&n);
	for(int i=1;i<=m;i++) scanf("%lld",&s[i]);
	for(int i=1;i<=m;i++){
		scanf("%lld",&l[i]);
		S=(S+s[i])%Mod,L=(L+l[i])%Mod;
		ss=(ss+s[i]*s[i]%Mod)%Mod;
		sl=(sl+s[i]*l[i]%Mod)%Mod;
		ll=(ll+l[i]*l[i]%Mod)%Mod;
	}
	mtx st(1,s[1],l[1]),mul(ss+sl,ss,sl+ll,sl),ed(S+L,S,0,0);
	mul=qpow(mul,n-1);
    st=st*mul*ed;
	printf("%lld\n",st.a[0][0]);
}
```

---

## 作者：I_AM_CIMOTA (赞：2)

#### 题意

有一个湖和 $m$ 个城市，每个城市向湖连了 $a_i$ 条重边和 $b_i$ 条轻边。

定义走一步为经过两条边到达另一个城市（可以是自己），并且最多经过一条重边，问从 $1$ 号城市走 $n$ 步的方案数。

其中 $1\le n\le 10^9,\ 1\le m\le 10^5$ 。

#### 题解

记 $f(i,j)$ 表示从 $i$ 节点出发走 $j$ 步的方案数，不难推出朴素的转移方程：

$$
f(u,i)=\sum_{v}f(v,i-1)\times(a_ub_v+b_u(a_v+b_v))\\\\
=\sum_{v}f(v,i-1)\times(a_ub_v+a_vb_u+b_ub_v+a_ua_v-a_ua_v)\\\\
=\sum_{v}f(v,i-1)\times((a_u+b_u)(a_v+b_v)-a_ua_v)
$$

记 $w_i=a_i+b_i$ ，那么有：

$$
f(u,i)=\sum_{v}f(v,i-1)\times(w_uw_v-a_ua_v)
$$

考虑矩阵快速幂优化，那么转移矩阵为：

$$
\left[
\begin{matrix}
w_1w_1-a_1a_1&...&w_1w_m-a_1a_m\\
w_2w_1-a_2a_1&...&w_2w_m-a_2a_m\\
\vdots&\ddots&\vdots\\
w_mw_1-a_ma_1&...&w_mw_m-a_ma_m
\end{matrix}
\right]
=
\left[
\begin{matrix}
w_1&a_1\\
w_2&a_2\\
\vdots&\vdots\\
w_m&a_m
\end{matrix}
\right]
\left[
\begin{matrix}
w_1&w_2&...&w_m\\
-a_1&-a_2&...&-a_m
\end{matrix}
\right]
$$

设这三个矩阵从左往右分别为 $\mathbf{A},\mathbf{B},\mathbf{C}$ ，那么：

$$
\mathbf{A}^n=(\mathbf{BC})^n=\mathbf{B}(\mathbf{CB})^{n-1}\mathbf{C}
$$

发现中间的 $\mathbf{CB}$ 是一个 $2\times 2$ 的矩阵，所以快速幂不会炸复杂度

代码丑，被 [Hoshino_Inc](https://www.luogu.com.cn/user/537687) 大佬吊打qwq
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=2e5+5,M=5,Mod=1e9+7;
struct Matrix{
    int d[M][M];
    void clear(){memset(d,0,sizeof d);}
    Matrix operator *(const Matrix& a)const{
        Matrix res;
        res.clear();
        for(int i=0;i<2;i++){
            for(int k=0;k<2;k++){
                for(int j=0;j<2;j++)(res.d[i][j]+=d[i][k]*a.d[k][j]%Mod)%=Mod;
            }
        }
        return res;
    }
}CB;
int n,m,s[N],l[N],w[N],B[N][5],C[5][N],f0[N],f1[5],f2[5],f3[N];

Matrix I(){
    Matrix res;
    res.clear();
    res.d[0][0]=res.d[1][1]=1;
    return res;
}

void quick_pow(int y){
    Matrix res=I();
    while(y){
        if(y&1)res=res*CB;
        CB=CB*CB,y>>=1;
    }
    CB=res;
}

signed main(){
    scanf("%lld%lld",&m,&n);
    for(int i=0;i<m;i++)scanf("%lld",&s[i]);
    for(int i=0;i<m;i++)scanf("%lld",&l[i]),w[i]=s[i]+l[i];
    for(int i=0;i<m;i++)B[i][0]=w[i],B[i][1]=l[i],C[0][i]=w[i],C[1][i]=Mod-l[i];
    CB.clear();
    for(int i=0;i<2;i++){
        for(int k=0;k<m;k++){
            for(int j=0;j<2;j++)(CB.d[i][j]+=C[i][k]*B[k][j]%Mod)%=Mod;
        }
    }
    quick_pow(n-1);
    for(int i=0;i<m;i++)f0[i]=1;
    for(int i=0;i<2;i++){
        for(int k=0;k<m;k++){
            (f1[i]+=C[i][k]*f0[k]%Mod)%=Mod;
        }
    }
    for(int i=0;i<2;i++){
        for(int k=0;k<2;k++){
            (f2[i]+=CB.d[i][k]*f1[k]%Mod)%=Mod;
        }
    }
    for(int i=0;i<m;i++){
        for(int k=0;k<2;k++){
            (f3[i]+=B[i][k]*f2[k]%Mod)%=Mod;
        }
    }
    printf("%lld\n",f3[0]);
    return 0;
}
```

---

## 作者：toolong114514 (赞：1)

中考后暑假集训的第一篇题解。

## Easy
考虑 DP。
### Solution 1
定义 $f_{i,j}$ 为第 $i$ 天最后走到 $j$ 号小屋的方案数。

显然，我们可以任意地从前一天最后走到的小屋来转移。

若从上一个小屋走短路径到湖边，那么从湖边到当前小屋，长/短路径都可以走。

若从上一个小屋走长路径到湖边，那么从湖边到当前小屋，只能走短路径。

那么，有状态转移方程如下：

$$f_{i,j}=\sum_{k=1}^m f_{i-1,k}\cdot[(s_j+l_j)\cdot s_k+s_j\cdot l_k]$$

注意 $f_{1,1}=1$，且 $\forall i\neq1,f_{1,i}=0$。

直接写代码，时间复杂度 $O(nm^2)$。
### Solution 2
定义 $f_{i,0/1}$ 为第 $i$ 天走短/长路径到湖边的方案数。

由题意不难得出：

如果今天和昨天都走短路径到湖边，可以走长/短路径到任意小屋，再从小屋走短路径到湖边；

如果昨天走长路径到湖边，今天走短路径到湖边，可以走长/短路径到任意小屋，再从小屋走长路径到湖边；

如果今天和昨天都走长路径到湖边，只能走长路径到任意小屋，再从小屋走长路径到湖边；

如果昨天走短路径到湖边，今天走长路径到湖边，可以走长/短路径到任意小屋，再从小屋走长路径到湖边。

那么，有状态转移方程如下：

$$f_{i,0}=f_{i-1,0}\cdot[\sum_{j=1}^m(s_j+l_j)s_j]+f_{i-1,1}\cdot\sum_{j=1}^m{s_j}^2$$

$$f_{i,1}=f_{i-1,0}\cdot[\sum_{j=1}^m(s_j+l_j)l_j]+f_{i-1,1}\cdot\sum_{j=1}^m{s_j}{l_j}$$

注意初始值：$f_{1,0}=s_1,f_{1,1}=l_1$。

直接写代码，时间复杂度 $O(nm)$，预处理四个 $\sum\cdots$ 的值可以优化到 $O(n+m)$。
## Medium&Hard
**Medium** 部分是给 Solution 1 量身定做的。

注意到，$f$ 的状态转移方程可以写作矩阵乘法的形式。

$$\begin{bmatrix}f_{i,1}&\cdots&f_{i,m}\end{bmatrix}=\begin{bmatrix}f_{i-1,1}&\cdots&f_{i-1,m}\end{bmatrix}\times\begin{bmatrix}(s_1+l_1)\cdot s_1+s_1\cdot l_1&\cdots&(s_m+l_m)\cdot s_1+s_1\cdot l_m\\\vdots&\ddots&\vdots\\(s_1+l_1)\cdot s_m+s_m\cdot l_1&\cdots&(s_m+l_m)\cdot s_m+s_m\cdot l_m\end{bmatrix}$$

即

$$\begin{bmatrix}f_{n,1}&\cdots&f_{n,m}\end{bmatrix}=\begin{bmatrix}1&0&\cdots&0\end{bmatrix}\times\left(\begin{bmatrix}(s_1+l_1)\cdot s_1+s_1\cdot l_1&\cdots&(s_m+l_m)\cdot s_1+s_1\cdot l_m\\\vdots&\ddots&\vdots\\(s_1+l_1)\cdot s_m+s_m\cdot l_1&\cdots&(s_m+l_m)\cdot s_m+s_m\cdot l_m\end{bmatrix}\right)^{n-1}$$

直接跑矩阵快速幂，把最终矩阵中的所有元素值加起来即可。

时间复杂度 $O(m^3\log{n})$，无法应对 Hard 的数据范围。

Solution 2 的转移过程直接优化，可以得到适用于 Hard 的复杂度算法。

原始的 $f$ 矩阵是 $1\times2$ 的，为了更新其本身，转移矩阵是 $2\times2$ 的。

不妨设转移矩阵为 $X=\begin{bmatrix}a&b\\c&d\end{bmatrix}$。

那么显然有

$$\begin{bmatrix}f_{i,0}&f_{i,1}\end{bmatrix}=\begin{bmatrix}f_{i-1,0}&f_{i-1,1}\end{bmatrix}\times X$$

即

$$\begin{bmatrix}f_{i,0}&f_{i,1}\end{bmatrix}=\begin{bmatrix}f_{i-1,0}&f_{i-1,1}\end{bmatrix}\times\begin{bmatrix}a&b\\c&d\end{bmatrix}$$

手动做个矩阵乘法展开，结合上文的状态转移方程，得

$$\begin{bmatrix}f_{i,0}&f_{i,1}\end{bmatrix}=\begin{bmatrix}f_{i-1,0}\cdot a+f_{i-1,1}\cdot c&f_{i-1,0}\cdot b+f_{i-1,1}\cdot d\end{bmatrix}=\begin{bmatrix}f_{i-1,0}\cdot[\sum_{j=1}^m(s_j+l_j)s_j]+f_{i-1,1}\cdot\sum_{j=1}^m{s_j}^2&f_{i-1,0}\cdot[\sum_{j=1}^m(s_j+l_j)l_j]+f_{i-1,1}\cdot\sum_{j=1}^m{s_j}{l_j}\end{bmatrix}$$

解得 $X=\begin{bmatrix}\sum_{j=1}^m(s_j+l_j)s_j&\sum_{j=1}^m{s_j}^2&\\\sum_{j=1}^m(s_j+l_j)l_j&\sum_{j=1}^m{s_j}{l_j}\end{bmatrix}$

所以最终的矩阵转移形式（$A$ 为答案矩阵）为：

$$A=\begin{bmatrix}f_{n,0}&f_{n,1}\end{bmatrix}=\begin{bmatrix}s_1&l_1\end{bmatrix}\times X^{n-1}$$

最后还需要处理最后一天走回小屋的方案数，分别考虑长路径到湖边和短路径到湖边的情况，答案即为 $A_{1,1}[\sum_{j=1}^m(s_j+l_j)]+A_{1,2}(\sum_{j=1}^ms_j)$。

时间复杂度 $O(m+2^3\log{n})$，$2^3$ 是矩乘常数。
## 参考代码
此处只给出 Solution 2 的代码。

```cpp
#include<iostream>
using namespace std;
#define int long long
const int mod=1e9+7;
const int N=1e6+10;
int s[N],l[N];
int n,m,ans;
struct node{
	int r,c,cont[3][3];
	friend node operator*(node a,node b){
		node res;
		res.r=a.r,res.c=b.c;
		for(int i=1;i<=res.r;i++){
			for(int j=1;j<=res.c;j++){
				res.cont[i][j]=0;
			}
		}
		for(int i=1;i<=res.r;i++){
			for(int j=1;j<=res.c;j++){
				for(int k=1;k<=a.c;k++){
					res.cont[i][j]+=a.cont[i][k]*b.cont[k][j]; 
					res.cont[i][j]%=mod;
				}
			}
		}
		return res;
	}
};
node build_1(int x){
	node res;
	res.r=res.c=x;
	for(int i=1;i<=x;i++){
		for(int j=1;j<=x;j++){
			if(i==j) res.cont[i][j]=1;
			else res.cont[i][j]=0;
		}
	}
	return res;
}
node qpow(node a,int b){
	node res=build_1(2);
	while(b){
		if(b&1) res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
node mrx1,mrx2,mrx3;
int f[N][2];
signed main(){
	ios::sync_with_stdio(false);
	cin>>m>>n;
	for(int i=1;i<=m;i++){
		cin>>s[i];
	}	
	for(int i=1;i<=m;i++){
		cin>>l[i];
	}
	mrx1.r=1,mrx1.c=2;
	mrx1.cont[1][1]=s[1],mrx1.cont[1][2]=l[1];
	mrx2.r=mrx2.c=2;
	for(int i=1;i<=m;i++){
		mrx2.cont[1][1]+=(s[i]+l[i])*s[i];
		mrx2.cont[1][1]%=mod;
		mrx2.cont[2][1]+=s[i]*s[i];
		mrx2.cont[2][1]%=mod;
		mrx2.cont[1][2]+=(s[i]+l[i])*l[i];
		mrx2.cont[1][2]%=mod;
		mrx2.cont[2][2]+=s[i]*l[i];
		mrx2.cont[2][2]%=mod;
	}
	f[1][0]=s[1],f[1][1]=l[1];
	mrx3=mrx1*qpow(mrx2,n-1);
	for(int i=1;i<=m;i++){
		ans+=(mrx3.cont[1][1]*(s[i]+l[i])+mrx3.cont[1][2]*s[i])%mod;
		ans%=mod;
	}
	cout<<ans;
	return 0;
}
```
[本代码可以通过CF的评测](https://codeforces.com/problemset/submission/1970/328490515)

Written by [toolong114514](/user/477821) on 2025/7/11.

---

## 作者：_xm_ (赞：1)

# Problem

[CF1970E3](https://codeforces.com/contest/1970/problem/E3)

# Solution

我们令 $f_{i,j}$ 表示第 $i$ 天到达第 $j$ 个房子的方案数，易得：
$$
f_{i,j} = \sum_{k=1}^{m} \left( l_j l_k + s_j l_k + l_j s_k \right) f_{i-1,k}.
$$

从第 $i-1$ 天得到第 $i$ 天的 $f$ 是固定的线性变换，可以用矩阵描述该线性变换，从而运用快速幂加速计算。

我们记：
$$
f_i = [f_{i,1}, f_{i,2}, \dots, f_{i,m}]
$$
令：
$$
f_i = f_{i-1} T
$$
易得转移矩阵 $T$ 的第 $i$ 行第 $j$ 列为：
$$
T_{i,j} = s_i s_j + s_i l_j + l_i s_j
$$

我们将 $l, s$ 记作列向量形式：
$$
l = 
\begin{bmatrix}
l_1 \\ l_2 \\ l_3 \\ \vdots
\end{bmatrix}, \qquad
s =
\begin{bmatrix}
s_1 \\ s_2 \\ s_3 \\ \vdots
\end{bmatrix}
$$

于是可以写出：
$$
T = s s^T + s l^T + l s^T = s(s + l)^T + l s^T=
\begin{bmatrix}
s & l
\end{bmatrix}
\begin{bmatrix}
(s+l)^T \\ s^T
\end{bmatrix}
$$

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long; using ull = unsigned long long; using pll = pair<ll, ll>; using ld = long double;
using i128 = __int128; using u128 = unsigned __int128;
void fileIO(const string& x) { freopen((x + ".in").c_str(), "r", stdin), freopen((x + ".out").c_str(), "w", stdout); }
template<typename T1, typename T2> bool chkmin(T1& x, const T2& y) { bool flag = (y < x); x = (y < x) ? y : x; return flag; }
template<typename T1, typename T2> bool chkmax(T1& x, const T2& y) { bool flag = (y > x); x = (y > x) ? y : x; return flag; }
template<class... T> void debug(T&&... x) { ((cerr << x << " "), ...); cerr << "\n"; }
mt19937_64 rnd(random_device{}());

const ll M = 1e5 + 5, Inf = 1e18, Mod = 1e9 + 7;

ll test_case = 1, n, m, l[M], s[M];

ll f[1][M], A[M][2], B[2][M], res[M][2], g[1][2], F[1][M];

struct Matrix {
	ll r, c, num[2][2];
	Matrix(ll C, ll R) {
		c = C, r = R;
		memset(num, 0, sizeof(num));
	}
};
Matrix operator* (const Matrix &a, const Matrix &b) {
	Matrix ret(a.c, b.r); assert(a.r == b.c);
	for(int i = 0; i < a.c; i++) {
		for(int j = 0; j < a.r; j++) {
			for(int k = 0; k < b.r; k++) {
				(ret.num[i][k] += a.num[i][j] * b.num[j][k]) %= Mod;
			}
		}
	}
	return ret;
}
Matrix expow(Matrix x, ll y) {
	Matrix ret(x.r, x.r), base = x;
	for(int i = 0; i < x.r; i++) ret.num[i][i] = 1;
	while(y > 0) {
		if(y % 2 == 1) ret = ret * base;
		base = base * base;
		y /= 2;
	}
	return ret;
}

void solution() {
	cin >> m >> n;
	for(int i = 0; i < m; i++) cin >> s[i];
	for(int i = 0; i < m; i++) cin >> l[i];
	
	f[0][0] = 1;
	
	Matrix T(2, 2);
	for(int i = 0; i < m; i++) {
		A[i][0] = s[i];
		A[i][1] = l[i];
	}
	for(int i = 0; i < m; i++) {
		B[0][i] = l[i] + s[i];
		B[1][i] = s[i];
	}
	
	for(int i = 0; i < 2; i++) { // B * A
		for(int j = 0; j < m; j++) {
			for(int k = 0; k < 2; k++) {
				(T.num[i][k] += B[i][j] * A[j][k]) %= Mod;
			}
		}
	}
	
	T = expow(T, n - 1); // T = (BA)^{n-1}
	
	for(int i = 0; i < m; i++) { // res = A * T
		for(int j = 0; j < 2; j++) {
			for(int k = 0; k < 2; k++) {
				(res[i][k] += A[i][j] * T.num[j][k]) %= Mod;
			}
		}
	}
	for(int i = 0; i < 1; i++) { // g = f * res
		for(int j = 0; j < m; j++) {
			for(int k = 0; k < 2; k++) {
				(g[i][k] += f[i][j] * res[j][k]) %= Mod;
			}
		}
	}
	for(int i = 0; i < 1; i++) { // F = g * B
		for(int j = 0; j < 2; j++) {
			for(int k = 0; k < m; k++) {
				(F[i][k] += g[i][j] * B[j][k]) %= Mod;
			}
		}
	}
	ll ans = 0;
	for(int i = 0; i < m; i++) (ans += F[0][i]) %= Mod;
	cout << ans;
}

double start_time, end_time;
int main() {
	//fileIO("");
	ios::sync_with_stdio(false), cin.tie(nullptr);
	start_time = clock(); /*cin >> test_case;*/ while(test_case--) solution(); end_time = clock();
	cerr << 1000 * (end_time - start_time) / CLOCKS_PER_SEC << "ms\n";
	return 0;
}
```

---

## 作者：huhangqi (赞：0)

### 对于 Easy 部分的做法：

很容易想到统计下来每个点的位置，枚举到达的点，然后进行转移统计即可。

时间复杂度 $O(m^2n)$。

由于个人习惯，代码中的 $n$ 和 $m$ 与原题目不同。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m,s[100005],l[100005],t[2][100005];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++)cin>>l[i];
	t[0][1]=1;
	int cnt=0;
	for(int i=1;i<=m;i++){
		cnt^=1;
		for(int j=1;j<=n;j++)t[cnt][j]=0;
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				t[cnt][k]+=((t[cnt^1][j]*s[j])%mod*s[k])%mod;
				t[cnt][k]%=mod;
				t[cnt][k]+=((t[cnt^1][j]*s[j])%mod*l[k])%mod;
				t[cnt][k]%=mod;
				t[cnt][k]+=((t[cnt^1][j]*l[j])%mod*s[k])%mod;
				t[cnt][k]%=mod;
			}
		}
	}
	int sum=0;
	for(int i=1;i<=n;i++)sum=(sum+t[cnt][i])%mod;
	cout<<sum;
	return 0;
}

``````

### 对于 Medium 部分的做法：

我们不难发现上一步转移形式很固定，甚至正好是乘上某数再加起来，而且正好每次更新同时更新了所有值。

那么我们很容易想到用矩阵优化。

直接模版把上一步的内容放到矩阵中，快速幂即可。

由于个人习惯，代码中的 $n$ 和 $m$ 与原题目不同。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m,s[100005],l[100005],t[2][100005];
struct MT{
	int n,m,c[105][105];
	MT(){
		n=m=0;
		memset(c,0,sizeof(c));
	}
	MT friend operator*(MT a,MT b){
		MT c;
		c.n=a.n,c.m=b.m;
		for(int i=1;i<=a.n;i++){
			for(int j=1;j<=b.m;j++){
				for(int k=1;k<=a.m;k++){
					c.c[i][j]+=(a.c[i][k]*b.c[k][j])%mod;
					c.c[i][j]%=mod;
				}
			}
		}
		return c;
	}
}base,be;
void ksm(MT a,int b){
	while(b){
		if(b&1)be=be*a;
		a=a*a;
		b>>=1;
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++)cin>>l[i];
	be.n=1,be.m=n;
	be.c[1][1]=1;
	base.n=base.m=n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			base.c[i][j]=((s[i]*s[j]%mod+s[i]*l[j]%mod)%mod+l[i]*s[j]%mod)%mod;
		}
	}
	ksm(base,m);
	int sum=0;
	for(int i=1;i<=n;i++)sum=(sum+be.c[1][i])%mod;
	cout<<sum;
	return 0;
}

``````

### 对于 Hard 部分的做法：

这里应该才是最难的一步，可以直接将绿题变成紫题。

我们发现矩阵里如果存下所有点的数字，那么矩阵乘法做一次就超时了。

但是这 $n$ 又非常大，也不好直接推导数学做法。

这时候我们想到在第一个点出来以后，我们走到湖中间上时去哪里只受到前面走了什么路的影响。

那么此时有多少种可能的做法就固定了。

走到下一个屋子，还要再回来，那么此时的点也确定了。

我们将这两步放到一起，从湖中间出发再走回来，在矩阵中记录上次走长路和短路的总方案数，这样就可以用矩阵快速求解了。

我们只需要先走到中间，再矩阵求方案数，再枚举回来的点，就可以得到答案了。

关于矩阵的具体推算可以看代码。

由于个人习惯，代码中的 $n$ 和 $m$ 与原题目不同。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m,s[100005],l[100005];
struct MT{
	int c[5][5],n,m;
	MT(){
		n=m=0;
		memset(c,0,sizeof(c));
	}
	MT friend operator*(MT a,MT b){
		MT c;
		c.n=a.n,c.m=b.m;
		for(int i=1;i<=a.n;i++){
			for(int j=1;j<=b.m;j++){
				for(int k=1;k<=a.m;k++)c.c[i][j]=(c.c[i][j]+(a.c[i][k]*b.c[k][j])%mod)%mod;
			}
		}
		return c;
	}
}base,be;
void ksm(MT a,int b){
	while(b){
		if(b&1)be=be*a;
		a=a*a;
		b>>=1;
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++)cin>>l[i];
	be.n=1,be.m=2;
	be.c[1][1]=s[1],be.c[1][2]=l[1];
	base.n=base.m=2;
	int sum=0;
	for(int i=1;i<=n;i++)sum=(sum+((l[i]*s[i])%mod+(s[i]*s[i])%mod)%mod)%mod;
	base.c[1][1]=sum;
	sum=0;
	for(int i=1;i<=n;i++)sum=(sum+(s[i]*s[i])%mod)%mod;
	base.c[2][1]=sum;
	sum=0;
	for(int i=1;i<=n;i++)sum=(sum+((l[i]*s[i])%mod+(l[i]*l[i])%mod)%mod)%mod;
	base.c[1][2]=sum;
	sum=0;
	for(int i=1;i<=n;i++)sum=(sum+(s[i]*l[i])%mod)%mod;
	base.c[2][2]=sum;
	ksm(base,m-1);
	sum=0;
	for(int i=1;i<=n;i++){
		sum+=(s[i]*be.c[1][1])%mod;
		sum%=mod;
		sum+=(l[i]*be.c[1][1])%mod;
		sum%=mod;
		sum+=(s[i]*be.c[1][2])%mod;
		sum%=mod;
	}
	cout<<sum;
	return 0;
}
/*
s->s
s l s
s s s
l->s
l s s
s->l
s l l
s s l
l->l
l s l
*/


``````

---

## 作者：Shxt_Plus (赞：0)

### 题目大意：

小湖有 $m$ 个休息点，小湖中间有一个小岛，每天小 $A$ 要去中间小岛观赏风景，然后去一个休息点休息。每个休息点离中间小岛有 $a_i$ 条短路和 $b_i$ 条长路。每天小 $A$ 至少要走一条短路，问 $n$ 天总共有多少种路径。

### Easy Version：

首先可以想到最朴素的 DP，设 $f_{i,j}$ 为第 $i$ 天走到第 $j$ 个休息点的方案数。

令 $p_i=a_i+b_i$，显然从 $i$ 号休息点走到 $j$ 号休息点有 $p_i\times p_j-b_i\times b_j$ 种方案。

则有转移式：

$$ f_{i,j}=\sum_{k=1}^n f_{i-1,k} \times (p_j \times p_k-b_j \times b_k) $$

复杂度： $O(n\times m^2)$

因为 $n,m$ 都很小，直接转移即可。

### Middle Version：

显然可以用矩阵快速幂优化。

令 $g_{i,j}=p_i\times p_j-b_i\times b_j$。

构造矩阵：
$$
\begin{bmatrix}
 g_{1,1} & g_{1,2} & g_{1,3} & \cdots\\
 g_{2,1} & g_{2,2} & g_{2,3} & \cdots\\
 g_{3,1} & g_{3,2} & g_{3,3} & \cdots\\
 \cdots & \cdots & \cdots & \cdots
\end{bmatrix}
$$

时间复杂度：$O(m^3 \times \log n)$

因为 $m$ 只有 $100$，可以通过此题。

### Hard Version：
显然 E2 的做法已经难以优化了，考虑从 E1 的做法下手。

首先显然可以把转移式拆成两部分：

$$
\begin{aligned}
f_{i,j}&=\sum_{k=1}^m f_{i-1,k} \times p_j \times p_k -\sum_{k=1}^m  f_{i-1,k} \times b_j \times b_k \\
&=p_j\times \sum_{k=1}^m f_{i-1,k} \times p_k-b_j\times \sum_{k=1}^m f_{i-1,k} \times b_k
\end{aligned}

$$

令 $s_i=\sum_{k=1}^m f_{i,k}\times p_k$，$g_i=\sum_{k=1}^m f_{i,k}\times b_k$。

则 $f_{i,j}=p_j\times s_i-b_j\times g_i$。

显然我们只需要求出 $s_{n-1}$，$g_{n-1}$ 就可以求出 $\sum_{k=1}^m f_{n,k}$ 了。

进一步化式子：

$$
\begin{aligned}
s_i&=\sum_{k=1}^m f_{i,k}\times p_k\\
&=\sum_{k=1}^m p_k\times p_k \times s_{i-1}-p_k \times b_k \times g_{i-1}\\
&=\sum_{k=1}^m p_k^2 \times s_{i-1} -\sum_{k=1}^m p_k \times b_k \times g_{i-1}\\
&=s_{i-1}\times \sum_{k=1}^m p_k^2- g_{i-1}\times \sum_{k=1}^m p_k \times b_k
\end{aligned}
$$

$g_i$ 的转移也同理。

显然可以用矩阵快速幂优化。

构造矩阵：
$$
\begin{bmatrix}
 \sum_{i=1}^m p_i \times p_i & -\sum_{i=1}^m p_i \times b_i\\
 \sum_{i=1}^m p_i \times b_i & -\sum_{i=1}^m b_i \times b_i\\
\end{bmatrix}
$$

时间复杂度： $O(2^3 \log n)$。

[Code](https://codeforces.com/contest/1970/submission/285973377)

---

## 作者：_Day_Tao_ (赞：0)

闲话：谨以此题解纪念自己切的第二个紫。

首先考虑最朴素的 DP。容易想到设 $f_{i,j}$ 表示第 $i$ 天在第 $j$ 个点的方案数。然后就可以列出 DP 柿子：

$$f_{i,j}=\sum_{k=1}^m f_{i-1,k}(s_ks_j+s_kl_j+l_ks_j)$$

初始化为 $f_{0,1}=1$。

具体的，就是从一个点到另一个点，有三种走法：**短路短路**、**短路长路**以及**长路短路**。这样就可以通过 Esay 了。时间复杂度 $O(nm^2)$。

我们又不难发现，对于这个柿子的 $i$ 好像没什么用，所以说可以矩乘优化一下，将时间复杂度优化成 $O(m^3\log n)$，可以通过 Medium。但是我们的目标是 Hard。

再次观察这个柿子，发现似乎没什么可以优化的地方了，于是考虑能不能列出更优的柿子。我们发现，这种转移其实是在考虑木屋的点，而这样要记录的状态就很多，那么时间复杂度就很唐。我们不妨将考虑木屋转化成考虑中心点。不难发现对于中心点一共有三种转移方式：
> 短 -> 中心 -> 短  
> 短 -> 中心 -> 长  
> 长 -> 中心 -> 短
> 
这样不难再次设出状态：$f_{i,0/1}$ 表示第 $i$ 天中间点是由短边进入的或是长边进入的。设 $ss=\sum\limits_{i=1}^m s_i\times s_i,sl=\sum\limits_{i=1}^m s_i\times l_i,ll=\sum\limits_{i=1}^m l_i\times l_i$。那么转移就是：

$$f_{i,0}=f_{i-1,0}\times(ss+sl)+f_{i-1,1}\times ss$$

$$f_{i,1}=f_{i-1,0}\times(sl+ll)+f_{i-1,1}\times sl$$

初始化为 $f_{1,0}=s_1,f_{1,1}=l_1$。

由于这样转移的话最终还是停在中心点，要回到木屋，那么答案就是：

$$f_{i,0}\times(\sum\limits_{i=1}^m s_i+l_i)+f_{i,1}\times\sum\limits_{i=1}^m s_i$$

又可以发现 $i$ 没啥用，直接矩乘优化掉，得到的矩阵转移是：

$$\begin{bmatrix}ss+sl & ss\\sl+ll & sl\end{bmatrix}\begin{bmatrix}f_{i-1,0}\\f_{i-1,1}\end{bmatrix}=\begin{bmatrix}f_{i,0}\\f_{i,1}\end{bmatrix}$$

时间复杂度 $O(m+\log n)$，后面的 $\log n$ 还要乘上一个矩乘的常数 $2^3$，足以通过 Hard。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define pii pair<int,int>
#define ls (root << 1)
#define rs (root << 1 | 1)
#define mid ((l + r) >> 1)
const int MAX = 2e5 + 5;
const int mod = 1e9+7;
const int INF = 0x7fffffff;
inline int read(){
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
int ss,sl,ll,n,m,s[MAX],l[MAX],sums,suml;
struct Day_Tao
{
	int a[3][3];
	inline void init() {for(int i=1;i<=2;i++) a[i][i]=1;return ;}
	inline void clear() {for(int i=1;i<=2;i++) for(int j=1;j<=2;j++) a[i][j]=0;return ;}
	inline Day_Tao operator*(const Day_Tao&c)
	{
		Day_Tao res; res.clear();
		for(int i=1;i<=2;i++) for(int j=1;j<=2;j++) for(int k=1;k<=2;k++)
		res.a[i][j]=(res.a[i][j]+a[i][k]*c.a[k][j]%mod)%mod;
		return res;
	}
}I,A,ans;
inline Day_Tao qpow(Day_Tao a,int b) {Day_Tao res=I;for(;b;b>>=1,a=a*a)if(b&1)res=res*a;return res;}
inline void init()
{
	A.a[1][1]=(ss+sl)%mod,A.a[1][2]=ss,A.a[2][1]=(sl+ll)%mod,A.a[2][2]=sl,
	I.init(),ans.a[1][1]=s[1],ans.a[2][1]=l[1];return ;
}
inline void solve()
{
	m=read(),n=read();
	for(int i=1;i<=m;i++) s[i]=read(),ss=(ss+s[i]*s[i])%mod,sums=(sums+s[i])%mod;
	for(int i=1;i<=m;i++) l[i]=read(),ll=(ll+l[i]*l[i])%mod,sl=(sl+s[i]*l[i])%mod,suml=(suml+l[i])%mod;
	init(),ans=qpow(A,n-1)*ans;
	printf("%lld\n",(ans.a[1][1]*(sums+suml)%mod+ans.a[2][1]*sums%mod)%mod);
	return ;
}
signed main()
{
//	freopen(".in","r",stdin),freopen(".out","w",stdout);
	int T=1;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Daniel_yao (赞：0)

# Solve

设 $dp_{i,j}$ 表示在第 $i$ 天，最后待在了 $j$ 号房子中的总方案数。

先考虑从 $i$ 号房间走到 $j$ 号房间的方案数如何计算。不考虑限制，单次方案数为 $(s_j+l_j)\times (s_k+l_k)$，然后由于不能存在同时为长路径的情况，于是把 $(l_j \times l_k)$ 减掉即可。

枚举回合 $i$，起点 $j$，终点 $k$，于是有：

$$
dp_{i,j}=\sum\limits_{k=1}^m dp_{i-1,k} \times \max(0, (s_j+l_j)\times (s_k+l_k) - (l_j \times l_k))
$$

答案为 $\sum\limits_{i=1}^m dp_{n,i}$，记得初始化 $dp_{0,1}=1$。

考虑到 $n=10^9$，无法在 $O(nm^2)$ 的时间复杂度下通过此题。

我们令 $r_i=s_i+l_i$，则有：

$$
dp_{i,j}=\sum\limits_{k=1}^m dp_{i-1,k} \times \max(0, r_jr_k-l_jl_k)
$$

发现式子有乘，有加，于是考虑构造矩阵进行加速。

$$
\begin{bmatrix}
r_1r_1-l_1l_1&r_1r_2-l_1l_2&\cdots&r_1r_m-l_1l_m\\
r_2r_1-l_2l_1&r_2r_2-l_2l_2&\cdots&r_2r_m-l_2l_m\\
\vdots&\vdots&\ddots&\vdots\\
r_mr_1-l_ml_1&r_mr_2-l_ml_2&\cdots&r_mr_m-l_ml_m
\end{bmatrix}
$$

对此矩阵进行快速幂（迭代 $n$ 次）的结果矩阵乘上

$$
\begin{bmatrix}
dp_{1,1}\\
dp_{2,1}\\
\vdots\\
dp_{m,1}
\end{bmatrix}
$$

得到矩阵

$$
\begin{bmatrix}
dp_{1,n}\\
dp_{2,n}\\
\vdots\\
dp_{m,n}
\end{bmatrix}
$$

答案便为 $\sum\limits_{i=1}^m dp_{i,n}$，记得初始化矩阵 $dp_{1,1}=1$。

时间复杂度 $O(m^3\log n)$。

然而这样仍然过不了 $m=10^5$ 的情况。考虑原矩阵等价于 $A\times B$，其中：$
A=\begin{bmatrix}
r_1&l_1\\
r_2&l_2\\
\vdots&\vdots\\
r_m&l_m
\end{bmatrix}
$，$B=\begin{bmatrix}
r_1&r_2&\cdots&r_m\\
-l_1&-l_2&\cdots&-l_m\\
\end{bmatrix}$

然后答案为 $(AB)^n$ 的第一列之和。

直接对矩阵 $AB$ 进行快速幂肯定不可行，因为矩阵 $AB$ 是 $m\times m$ 的。考虑到矩阵乘法有结合律，于是就有 $(AB)^n=A\times (BA)^{n-1}\times B$。

第一次先对 $2\times2$ 的 $BA$ 矩阵进行快速幂，然后依次进行 $A\times (BA)^{n-1}$，$A\times (BA)^{n-1} \times B$ 的运算。最后的矩阵大小为 $m\times m$ 所以最后一次矩阵乘法只要算第一列答案即可。

时间复杂度 $O(m + m\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)
#define mod 1000000007

using namespace std;

const int N = 1e5 + 10;

int n, m, s[N], l[N], r[N];

struct Matrix {
  int M[3][3];
  
  void clean() {
    For(i,1,2) For(j,1,2) M[i][j] = 0;
  }

  void init() {
    For(i,1,2) M[i][i] = 1;
  }

  void print() {
    For(i,1,2) {
      For(j,1,2) cout << M[i][j] << ' ';
      cout << endl;
    } 
  }

  Matrix friend operator * (const Matrix a, const Matrix b) {
    Matrix Ans;
    Ans.clean();
    For(i,1,2) {
      For(j,1,2) {
        For(k,1,2) {
          Ans.M[i][j] = (Ans.M[i][j] + (a.M[i][k] % mod * b.M[k][j] % mod) % mod) % mod;
        }
      }
    }
    return Ans;
  }
} Ans;

struct MATRIX1 {
  int M[3][N];
  void clean() {
    For(i,1,2) For(j,1,m) M[i][j] = 0;
  }
  void print() {
    For(i,1,2) {
      For(j,1,m) cout << M[i][j] << ' ';
      cout << endl;
    } 
  }
} B;

struct MATRIX2 {
  int M[N][3];
  void clean() {
    For(i,1,m) For(j,1,2) M[i][j] = 0;
  }
  void print() {
    For(i,1,m) {
      For(j,1,2) cout << M[i][j] << ' ';
      cout << endl;
    } 
  }
} A, Ans1, Ansend;

Matrix qpow(Matrix a, int b) {
  Matrix res; res.clean(); res.init();
  for (; b; a = a * a, b >>= 1) {
    if(b) res = res * a;
  }
  return res;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> m >> n;
  For(i,1,m) cin >> s[i], s[i] %= mod;
  For(i,1,m) cin >> l[i], l[i] %= mod, r[i] = (s[i] + l[i]) % mod;
  Ans.clean(); A.clean(); B.clean(); Ans1.clean(); Ansend.clean();
  For(i,1,2) For(j,1,m) B.M[i][j] = (i == 1 ? r[j] : (-l[j] + mod) % mod);
  For(i,1,m) For(j,1,2) A.M[i][j] = (j == 1 ? r[i] : l[i]);
  For(i,1,2) {
    For(j,1,2) {
      For(k,1,m) {
        Ans.M[i][j] = (Ans.M[i][j] + (B.M[i][k] % mod * A.M[k][j] % mod) % mod) % mod;
      }
    }
  }
  Ans = qpow(Ans, n-1);
  For(i,1,m) {
    For(j,1,2) {
      For(k,1,2) {
        Ans1.M[i][j] = (Ans1.M[i][j] + (A.M[i][k] % mod * Ans.M[k][j] % mod) % mod) % mod;
      }
    }
  }
  int ans = 0;
  For(i,1,m) {
    int j = 1;
    For(k,1,2) {
      ans = (ans + (Ans1.M[i][k] * B.M[k][j]) % mod) % mod;
    }
  }
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：SamHJD (赞：0)

首先可以列出 dp 方程，记 $f_{i,u}$ 为第 $i$ 天走到 $u$ 的方案数，总边数 $w_u=l_u+s_u$，从 $u$ 走到 $v$ 的合法方案数可以由总方案数减去不合法的方案数：
$$
f_{i,u}=\sum\limits_{v=1}^{m} f_{i-1,v}\times(w_uw_v-l_ul_v)
$$
由于 $f_i$ 仅和 $f_{i-1}$ 有关，可以矩乘优化：
$$
\begin{bmatrix}
f_{i,1}\\
f_{i,2}\\
\vdots\\
f_{i,m}
\end{bmatrix}
=
\begin{bmatrix}
w_1w_1-l_1l_1 & w_1w_2-l_1l_2 & \cdots & w_1w_m-l_1l_m\\
w_2w_1-l_2l_1 & w_2w_2-l_2l_2 & \cdots & w_2w_m-l_2l_m\\
\vdots & \vdots & \ddots & \vdots\\
w_mw_1-l_ml_1 & w_mw_2-l_ml_2 & \cdots & w_mw_m-l_ml_m\\
\end{bmatrix}
\times
\begin{bmatrix}
f_{i-1,1}\\
f_{i-1,2}\\
\vdots\\
f_{i-1,m}
\end{bmatrix}
$$
其中中间 $m\times m$ 的矩阵还可以化简为：
$$
\begin{bmatrix}
w_1w_1-l_1l_1 & w_1w_2-l_1l_2 & \cdots & w_1w_m-l_1l_m\\
w_2w_1-l_2l_1 & w_2w_2-l_2l_2 & \cdots & w_2w_m-l_2l_m\\
\vdots & \vdots & \ddots & \vdots\\
w_mw_1-l_ml_1 & w_mw_2-l_ml_2 & \cdots & w_mw_m-l_ml_m\\
\end{bmatrix}
= 
\begin{bmatrix}
w_1 & l_1\\
w_2 & l_2\\
\vdots & \vdots\\
w_m & l_m
\end{bmatrix}
\times
\begin{bmatrix}
w_1 & w_2 & \cdots & w_m\\
-l_1 & -l_2 & \cdots & -l_m\\
\end{bmatrix}
$$
于是有：
$$
\begin{bmatrix}
f_{i,1}\\
f_{i,2}\\
\vdots\\
f_{i,m}
\end{bmatrix}
=
\left(
\begin{bmatrix}
w_1 & l_1\\
w_2 & l_2\\
\vdots & \vdots\\
w_m & l_m
\end{bmatrix}
\times
\begin{bmatrix}
w_1 & w_2 & \cdots & w_m\\
-l_1 & -l_2 & \cdots & -l_m\\
\end{bmatrix}
\right)^n
\times
\begin{bmatrix}
1\\
0\\
\vdots\\
0
\end{bmatrix}
$$


记右式的前两个矩阵为 $A,B$，直接相乘后的大小为 $m\times m$，考虑变为 $A(BA)^{n-1}B$ 计算。$A(BA)^{n-1}$ 可直接计算，矩阵大小为 $m\times 2$，最后一步乘 $B$ 时还会形成 $m\times m$ 的矩阵，但由于初始 $f_0$ 的矩阵只有 $(1,1)$ 的值为 $1$，所以只需计算 $A(BA)^{n-1}B$ 的第一列的值，相加即为答案。

```cpp
#include "bits/stdc++.h"
#define int long long
#define rep(i,s,t) for(int i=s;i<=t;++i)
#define per(i,t,s) for(int i=t;i>=s;--i)
using namespace std;
template<typename T>
inline void read(T &x) {
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	x*=f;
}
const int N=1e5+10,MOD=1e9+7;
int T,n,m,l[N],s[N],w[N];
typedef vector<vector<int> > matrix;
matrix operator *(const matrix &a,const matrix &b){
	matrix res(a.size(),vector<int>(b[0].size()));
	rep(i,0,(int)a.size()-1) rep(j,0,(int)b[0].size()-1){
        rep(k,0,min((int)a[0].size()-1,(int)b.size()-1)) res[i][j]=(res[i][j]+a[i][k]*b[k][j]%MOD)%MOD;
    }
	return res;
}
matrix A,B,C;
void qpow(int k){
	while(k){
		if(k&1) A=A*C;
		k>>=1;
		C=C*C;
	}
}
signed main(){
	read(m);read(n);
	rep(i,1,m) read(s[i]);
	rep(i,1,m) read(l[i]),w[i]=(s[i]+l[i])%MOD;
	A.resize(m,vector<int>(2));B.resize(2,vector<int>(m));
	rep(i,0,m-1) A[i][0]=w[i+1],A[i][1]=l[i+1];
	rep(i,0,m-1) B[0][i]=w[i+1],B[1][i]=-l[i+1];
	C=B*A;
	qpow(n-1);
	int ans=0;
	rep(i,0,m-1) rep(k,0,1) ans=(ans+A[i][k]*B[k][0])%MOD;
	printf("%lld\n",(ans%MOD+MOD)%MOD);
	return 0;
}

//用 vector 存矩阵的时候不能开 vector<int> a[N] 然后传参矩阵乘，会报 RE。
```

---

## 作者：EXODUS (赞：0)

# Part 1：前言

反转了，除了 D3 我还不会 E3。

# Part 2：正文

先从 E1 看起。不难写出一个简单的 dp 做法，令 $f(i,j)$ 表示考虑到第 $i$ 天，当前在 $j$ 号点的方案数。转移枚举这一天怎么走，以及第一条走的路径是哪一条。有转移 $f(i,j)=\sum\limits_{k=1}^m f(i-1,k)\times (s_js_k+s_jl_k+l_js_k)$。暴力即可做到 $O(nm^2)$。

E2 的做法比较简单，直接在 E1 的基础上写出一个 $m\times m$ 的转移矩阵做矩阵快速幂即可。

考虑 E3，令 $i$ 到 $j$ 的转移系数为 $g_{i,j}$，令 $a_i=s_i+l_i$，则 $g_{i,j}=a_ia_j-l_il_j$。令系数矩阵为 $G$，我们发现，$G$ 可以拆成两个矩阵的乘积，设其分别为 $B$ 和 $C$，则其矩阵可写为如下形式。
$$
B=
\begin{pmatrix}
a_1&l_1\\
a_2&l_2\\
\vdots&\vdots\\
a_m&l_m\\
\end{pmatrix}\\
C=
\begin{pmatrix}
a_1&a_2&\ldots&a_m\\
-l_1&-l_2&\ldots&-l_m
\end{pmatrix}
$$
定义一个行向量 $v=\begin{pmatrix}1&0&0&\ldots&0\end{pmatrix}$，考虑我们的答案，实际上是 $(BC)^nv$。现在的问题在于 $BC$ 是一个 $m\times m$ 大小的矩阵。我们考虑将其改写为 $B(CB)^{n-1}Cv$，而 $CB$ 是 $2\times 2$ 的矩阵，我们直接做矩阵快速幂的复杂度是 $O(\log n)$。最后我们多次矩阵右乘即可得到所求。时间复杂度 $O(m+\log n)$。

艾伦罩大婶觉得转移系数只和 $f(i,j),f(i,j)\times s_j,f(i,j)\times t_j$ 有关，所以可以直接写出一个常数大小的矩阵，大家有兴趣可以试一下。

# Part 3：代码

```cpp
// Well one day I'm gonna sell out an arena
// 终有一天 我将在舞台上大放异彩
// I'm gonna fly like I'm a ballarena
// 你将会看见我凌游青空之上
// One day I'm gonna sell out an arena
// 终有一天 我将在舞台上大放异彩
// You'll see me fly like I'm a ballarena
// 你将会看见我如同芭蕾女伶般舞姿飞扬
// 'Cause baby I can dance
// 宝贝 只因我可以尽情舞动
// Baby I can dance
// 宝贝 我可以舞步翩转
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;

#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define File(filename) freopen(filename ".in","r",stdin),freopen(filename ".out","w",stdout)
#define Exit(p) fprintf(stderr,"[exit]: at breakpoint %d\n",p),exit(0);

#ifdef EXODUS
	#define Debug(...) fprintf(stderr,__VA_ARGS__)
#else
	#define Debug(...) 0
#endif

//=========================================================================================================
// Something about IO

template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T>
void seq_read(T bg,T ed){for(auto i=bg;i!=ed;++i)read(*i);}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}

//=========================================================================================================
//Some useful function

template<typename T>
void cmax(T& x,T y){x=max(x,y);}
template<typename T,typename... Args>
void cmax(T& x,T y,Args ...args){cmax(x,y);cmax(x,args...);}
template<typename T>
void cmin(T& x,T y){x=min(x,y);}
template<typename T,typename... Args>
void cmin(T& x,T y,Args ...args){cmin(x,y);cmin(x,args...);}
template<typename T,typename U>
void seq_assign(T bg,T ed,U val){for(auto i=bg;i!=ed;++i)(*i)=val;}
template<typename T,class F,class=enable_if_t<is_invocable_v<F>>>
void seq_assign(T bg,T ed,F func){for(auto i=bg;i!=ed;++i)(*i)=func(i);}
template<typename T>
void seq_copy(T dstbg,T dsted,T srcbg,T srced){for(auto i=dstbg,j=srcbg;i!=dsted&&j!=srced;++i,++j)(*i)=(*j);}

//=========================================================================================================
// Define the global variables here.

bool membg=0;

constexpr int N=1e5+7,mod=1e9+7;
struct matrix{
	int n,m;
	std::vector<vector<int>>mat;
	matrix(){}
	matrix(int _n,int _m):n(_n),m(_m),mat(_n,vector<int>(_m,0)){}
	vector<int>& operator [](int p){return mat[p];}
	const vector<int>& operator [](int p)const{return mat[p];}
	matrix operator* (const matrix& rhs)const{
		assert(m==rhs.n);
		matrix res(n,rhs.m);
		for(int i=0;i<n;i++)
			for(int k=0;k<m;k++)
				for(int j=0;j<rhs.m;j++)
					res.mat[i][j]=(res.mat[i][j]+(ll)mat[i][k]*rhs[k][j])%mod;
		return res;
	}
};

int m,n;
int s[N],l[N];


bool memed=0;

//=========================================================================================================
// Code here.

void solve(){
	read(m,n);
	for(int i=0;i<m;i++)
		read(s[i]);
	for(int i=0;i<m;i++)
		read(l[i]);
	matrix B(m,2),C(2,m),F(m,1),A(2,2);
	for(int u=0;u<m;u++){
		F[u][0]=1;
		B[u][0]=s[u]+l[u],B[u][1]=l[u];
		C[0][u]=s[u]+l[u],C[1][u]=mod-l[u];
	}
	A=C*B;
	matrix res(2,2);
	for(int u=0;u<=1;u++)
		res[u][u]=1;
	for(int p=n-1;p;p>>=1,A=A*A)
		if(p&1)
			res=res*A;
	F=B*(res*(C*F));
	printf("%d\n",F[0][0]);
	return;
}


//=========================================================================================================

int main(){
	Debug("%.3lfMB\n",fabs(&memed-&membg)/1024.0/1024.0);
	int timbg=clock();
	int T=1;
	while(T--)solve();
	int timed=clock();
	Debug("%.3lfs\n",1.0*(timed-timbg)/CLOCKS_PER_SEC);
	fflush(stdout);
	return 0;
}
```

---

