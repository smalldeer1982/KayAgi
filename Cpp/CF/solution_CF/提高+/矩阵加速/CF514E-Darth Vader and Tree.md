# Darth Vader and Tree

## 题目描述

When Darth Vader gets bored, he sits down on the sofa, closes his eyes and thinks of an infinite rooted tree where each node has exactly $ n $ sons, at that for each node, the distance between it an its $ i $ -th left child equals to $ d_{i} $ . The Sith Lord loves counting the number of nodes in the tree that are at a distance at most $ x $ from the root. The distance is the sum of the lengths of edges on the path between nodes.

But he has got used to this activity and even grew bored of it. 'Why does he do that, then?' — you may ask. It's just that he feels superior knowing that only he can solve this problem.

Do you want to challenge Darth Vader himself? Count the required number of nodes. As the answer can be rather large, find it modulo $ 10^{9}+7 $ .

## 说明/提示

Pictures to the sample (the yellow color marks the nodes the distance to which is at most three)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF514E/dfa75ce6cc0df1087a16e02cadbd273a08641d03.png)

## 样例 #1

### 输入

```
3 3
1 2 3
```

### 输出

```
8
```

# 题解

## 作者：Engulf (赞：3)

考虑朴素的 dp。

设 $f_i$ 表示到根节点距离恰好为 $i$ 的节点个数，转移 $f_i = \sum\limits_{j = 1}^{n} f_{i - d_j}$。

这样做的复杂度是 $\mathcal{O}(nx)$ 的，无法接受。

注意到 $d_i \le 100$，非常小，考虑设 $t_i$ 表示每个节点距离为 $i$ 的儿子个数，转移变成 $f_i = \sum\limits_{j = 1}^{100}t_j \cdot f_{i - j}$。

这个数列是能矩阵加速的，同时我们还要维护个前缀和 $s_i = \sum\limits_{j = 1}^{i}f_j$。

$$\begin{bmatrix}
s_{i - 1} & f_{i - 1} & f_{i - 2} & \cdots & f_{i - 100}
\end{bmatrix} \times \begin{bmatrix}
1 & 0 & 0 & 0 & \cdots & 0 \\
t_1 & t1 & 1 & 0 & \cdots & 0 \\
t_2  & t_2 & 0 & 1 & \cdots  & 0 \\
\vdots & \vdots & \vdots & 0 & \ddots & 0 \\
t_{100}  & t_{100} & 0 & \cdots & 0 & 1
\end{bmatrix} = \begin{bmatrix}
s_{i} & f_{i} & f_{i - 1} & \cdots & f_{i - 99}
\end{bmatrix}$$

矩阵快速幂即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int inf = 0x3f3f3f3f;
const LL infLL = 0x3f3f3f3f3f3f3f3fLL;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 105, mod = 1e9 + 7;

int n, k;

int t[N];

int ans[N][N], A[N][N];

void mul(int c[][N], int a[][N], int b[][N]) {
    int t[N][N] = {};
    for (int i = 0; i < 101; i++)
        for (int j = 0; j < 101; j++)
            for (int k = 0; k < 101; k++)
                t[i][j] = (t[i][j] + (LL)a[i][k] * b[k][j] % mod) % mod;
    memcpy(c, t, sizeof t);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        t[x]++;
    }
    ans[0][0] = ans[0][1] = 1;
    A[0][0] = 1;
    for (int i = 1; i <= 100; i++) A[i][0] = A[i][1] = t[i];
    for (int i = 2; i < 101; i++) A[i - 1][i] = 1;
    while (k) {
        if (k & 1) mul(ans, ans, A);
        mul(A, A, A);
        k >>= 1;
    }
    cout << ans[0][0] << endl;
    return 0;
}
```



---

## 作者：Lucky_dpy (赞：2)

[CF514E Darth Vader and Tree](https://www.luogu.com.cn/problem/CF514E)
### **矩阵快速幂优化 DP**

定义 $f_i$ 表示到根距离恰为 $i$ 的点个数。

每个点可以由父亲连接的任意一条边转移，于是有：
$$f_i=\sum_{j=1}^{n} f_{j-d_i}$$
时间复杂度 $O(nx)$，直接 T 飞。

考虑如何优化。

发现 $d_i≤100$ 非常小，所以有很多 $f_{j-d_i}$ 是重复算的。定义 $num_j$ 表示 $d_i=j$ 的点个数，那么状态转移方程就变成了：

$$f_i=\sum_{j=1}^{100}num_j×f_{i-j}$$

最后要求有多少个节点到根节点的距离小于等于 $x$，于是可以维护一个前缀和：
$$sum_i=\sum_{j=1}^{i}f_j$$

考虑到 $x$ 比较大，需要用矩阵快速幂优化。

---

推矩阵：

$$
f_i=\sum_{j=1}^{100}num_j×f_{i-j}
$$

$$
sum_i=\sum_{j=1}^{i}f_j
$$

展开得

$$
f_i=num_1×f_{i-1}+num_2×f_{i-2}+...+num_{100}×f_{i-100}
$$

$$
sum_i=sum_{i-1}+f_i
$$

于是有

$$
\begin{bmatrix}sum_i & f_i\end{bmatrix}=\begin{bmatrix}sum_{i-1} & f_{i-1} & f_{i-2} &\cdots& f_{i-100}\end{bmatrix}\begin{bmatrix}1 & 0\\num_1 &num_1\\ num_2 &num_2\\\vdots&\vdots\\ num_{100}&num_{100}\end{bmatrix}
$$

$$
\begin{bmatrix}sum_i & f_i &f_{i-1}&\cdots&f_{i-99}\end{bmatrix}=\begin{bmatrix}sum_{i-1} & f_{i-1} & f_{i-2} &\cdots& f_{i-100}\end{bmatrix}\begin{bmatrix}1 & 0&0&0&\cdots&0\\num_1 &num_1&1&0&\cdots&0\\ num_2&num_2&0&1&\cdots&0\\\vdots&\vdots&\vdots&\vdots&\ddots&\vdots\\num_{99}&num_{99}&0&0&\cdots&1\\num_{100}&num_{100}&0&0&\cdots&0\end{bmatrix}
$$

$$
\begin{bmatrix}sum_i & f_i &f_{i-1}&\cdots&f_{i-99}\end{bmatrix}=\begin{bmatrix}sum_{100} & f_{100} & f_{99} &\cdots& f_1\end{bmatrix}\begin{bmatrix}1 & 0&0&0&\cdots&0\\num_1 &num_1&1&0&\cdots&0\\ num_2&num_2&0&1&\cdots&0\\\vdots&\vdots&\vdots&\vdots&\ddots&\vdots\\num_{99}&num_{99}&0&0&\cdots&1\\num_{100}&num_{100}&0&0&\cdots&0\end{bmatrix}^{i-100}
$$

那么我们暴力求出前 $100$ 个解和前缀和，然后套矩阵快速幂模板即可。

#### **注意：特判前 $100$ 个。**

---

**CODE:**

```cpp
//f[i]=Σ(1<=j<=n)f[i-a[j]]
//f[i]=Σ(1<=j<=i)num[j]*f[i-j]
//s[i]=Σ(1<=j<=i)f[j] 
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,k;
int f[105],num[105],sum[100005];
struct mat{
	int a[105][105];
	mat(){
		memset(a,0,sizeof(a));
	}
	mat operator*(const mat& b) const{
		mat res;
		int i,j,l;
		for(i=1;i<=101;i++){
			for(j=1;j<=101;j++){
				for(l=1;l<=101;l++){
					res.a[i][j]=(res.a[i][j]+a[i][l]*b.a[l][j])%mod;
				}
			}
		}
		return res;
	}
}s,p;
void init(){
	int i;
	p.a[1][1]=1;
	s.a[1][1]=sum[100];
	for(i=2;i<=101;i++){
		p.a[i][1]=p.a[i][2]=num[i-1];
		p.a[i][i+1]=1;
		s.a[1][i]=f[102-i];
	}
}
void pows(int b){
	while(b){
		if(b&1)s=s*p;
		p=p*p;
		b>>=1;
	}
}
signed main(){
	int i,j,x;
	cin>>n>>k;
	for(i=1;i<=n;i++){
		scanf("%lld",&x);
		num[x]++;
	}
	sum[0]=f[0]=1;
	for(i=1;i<=100;i++){
		for(j=1;j<=i;j++){
			f[i]=(f[i]+num[j]*f[i-j]%mod)%mod;
		}
		sum[i]=(sum[i-1]+f[i])%mod;
	}
	if(k<=100){
		cout<<sum[k];
		return 0;
	}
	init();
	pows(k-100);
	cout<<s.a[1][1]%mod;
}
```

---

## 作者：QwQcOrZ (赞：2)

考虑朴素的 dp。

设 $f_i$ 表示到根节点距离恰好为 $i$ 的点的个数。

显然有 $f_i=\sum\limits_{j=1}^n f_{i-d_j}$，转移之后累加一下即为答案。

再考虑优化这个东西。

因为 $1\leq d_i\leq 100$，所以很多 $f_{i-d_j}$ 都会被重复计算。

于是可以考虑将 $d$ 数组离散化，存到一个桶里。

于是转移方程就变成了 $f_i=\sum\limits_{j=1}^{100} t_j\times f_{i-j}$。

其中 $t_j$ 表示  $d_i=j$ 的个数。

然后这个柿子显然就比之前的那个优美多了，可以用矩阵快速幂优化。

记 $sum_i=\sum\limits_{j=1}^i f_j$。

则有下面的这个转移矩阵：
$$
\begin{bmatrix}1&t_1&t_2&t_3&t_4&\cdots&t_{100}\\0&t_1&t_2&t_3&t_4&\cdots&t_{100}\\0&1&0&0&0&\cdots&0\\0&0&1&0&0&\cdots&0\\0&0&0&1&0&\cdots&0\\\vdots&\ddots&\ddots&\ddots&\ddots&\ddots&\vdots\\0&\cdots&0&0&0&1&0\end{bmatrix}\times\begin{bmatrix}sum_{i-1}\\f_{i-1}\\f_{i-2}\\f_{i-3}\\f_{i-4}\\\vdots\\f_{i-100}\end{bmatrix}=\begin{bmatrix}sum_{i}\\f_{i}\\f_{i-1}\\f_{i-2}\\f_{i-3}\\\vdots\\f_{i-99}\end{bmatrix}
$$
其中矩阵从第 3 行开始到第 101 行是个像单位矩阵一样的东西，也就是斜着的一排 $1$。（可能我文字表述不是很清晰，可以结合代码中的构造方法理解）

构造方法是挺模板的一个东西，因此在这里就不赘述了。

然后就做完了，矩阵快速幂即可。

时间复杂度 $O(100^3\log x)$。

~~PS：vp 时打的代码，时间紧张，写得有点乱，大家凑合着看吧（~~

$\texttt{Code Below}$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e2+5;
const ll p=1e9+7;

inline int read()
{
	register int s=0;
	register char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(register int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
inline void print(const register int x,const register char c='\n')
{
	write(x);
	putchar(c);
}
struct node
{
	ll m[N][N];
}a;
struct node2
{
	ll m[N];
}ans;
node operator *(node a,node b)
{
	node ans;
	for (int i=0;i<=100;i++)
	for (int j=0;j<=100;j++) ans.m[i][j]=0;
	for (int i=0;i<=100;i++)
	for (int j=0;j<=100;j++)
	for (int k=0;k<=100;k++) ans.m[i][j]=(ans.m[i][j]+a.m[i][k]*b.m[k][j]%p)%p;
	return ans;
}
node2 operator *(node2 a,node b)
{
	node2 ans;
	for (int i=0;i<=100;i++) ans.m[i]=0;
	for (int i=0;i<=100;i++)
	for (int k=0;k<=100;k++) ans.m[i]=(ans.m[i]+b.m[i][k]*a.m[k]%p)%p;
	return ans;
}
int t[101];

int main()
{
	memset(t,0,sizeof(t));
	memset(a.m,0,sizeof(a.m));
	memset(ans.m,0,sizeof(ans.m));
	int n=read(),k=read();
	for (int i=1;i<=n;i++)
	{
		int x=read();
		t[x]++;
	}
	a.m[0][0]=1;
	for (int i=1;i<=100;i++) a.m[0][i]=a.m[1][i]=t[i];
	for (int i=2;i<=100;i++) a.m[i][i-1]=1;
	ans.m[0]=1;//sum[0]=1
	ans.m[1]=1;//f[0]=1
	while (k)
	{
		if (k&1) ans=ans*a;
		a=a*a;
		k/=2;
	}
	print(ans.m[0]);

    return 0;
}
```



---

## 作者：WorldMachine (赞：1)

好简单的题，我这种蒟蒻都能做出来。这个做法貌似不用维护前缀和。

设 $f_x$ 为距离根节点不超过 $x$ 的节点个数，有：
$$
f_x=1+\sum_{i=1}^nf_{x-d_i}
$$
发现这个东西是线性的，意味着我们可以用矩阵快速幂加速递推。转移如下：
$$
\left[
\begin{array}{cccccc}
c_1&c_2&c_3&\dots&c_{100}&1\\
1&0&0&\dots&0&0\\
0&1&0&\dots&0&0\\
\vdots&\vdots&\vdots&\ddots&\vdots&\vdots\\
0&0&0&\dots&0&0\\
0&0&0&\dots&0&1
\end{array}
\right]
\left[
\begin{array}{c}
f_x\\
f_{x-1}\\
f_{x-2}\\
\vdots\\
f_{x-99}\\
1
\end{array}
\right]
=
\left[
\begin{array}{c}
f_{x+1}\\
f_x\\
f_{x-1}\\
\vdots\\
f_{x-98}\\
1
\end{array}
\right]
$$
$c_i$ 表示 $\{d\}$ 中 $i$ 的个数。第 $2\sim 100$ 行中第 $i$ 行的第 $i-1$ 列为 $1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005, M = 102, p = 1000000007;
struct vec {
	int a[M];
	vec() { memset(a, 0, sizeof(a)); }
	int& operator[](int i) { return a[i]; }
} V;
struct mat {
	int a[M][M];
	mat() { memset(a, 0, sizeof(a)); }
	int* operator[](int i) { return a[i]; }
	mat operator*(mat &b) {
		mat c;
		for (int i = 1; i < M; i++) {
			for (int k = 1; k < M; k++) {
				for (int j = 1; j < M; j++) c[i][j] = (c[i][j] + (ll)a[i][k] * b[k][j]) % p;
			}
		}
		return c;
	}
	vec operator*(vec &b) {
		vec c;
		for (int i = 1; i < M; i++) {
			for (int j = 1; j < M; j++) c[i] = (c[i] + (ll)a[i][j] * b[j]) % p;
		}
		return c;
	}
} A;
mat qpow(mat a, int b) {
	mat c;
	for (int i = 1; i < M; i++) c[i][i] = 1;
	while (b) {
		if (b & 1) c = c * a;
		a = a * a, b >>= 1;
	}
	return c;
}
int n, x, a[N];
int main() {
	scanf("%d%d", &n, &x);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), A[1][a[i]]++;
	A[1][101] = 1;
	for (int i = 2; i <= 100; i++) A[i][i - 1] = 1;
	A[101][101] = 1;
	A = qpow(A, x);
	V[1] = 1, V[101] = 1;
	V = A * V;
	printf("%d\n", V[1]);
}
```

---

## 作者：黑影洞人 (赞：1)

矩阵加速优化 DP

第二道独立自主写出来的黑题！

首先推朴素 DP 的方程：

设 $dp_i$ 为到根节点距离为 $i$ 的点：

显然，方程就是累加到他距离为 $d_i$ 的点的 $dp$ 值：

$$dp_i=\sum_{j=1}^{n}dp_{i-d_j}$$

然后对其进行矩阵快速幂优化，$O(n^3\log x)$ 直接 $T$ 飞。

观察数据范围发现 $d_i$ 的值很小，于是考虑对其开一个桶进行统计，桶记为 $tmp$ 数组：

$$dp_i=\sum_{j=1}^{100}tmp_j\times dp_{i-j}$$

最后对其求前缀和，则有：

$$S_i=\sum_{i=1}^{x}dp_i$$

于是进行矩阵加速优化，珂推得：

$$
\begin{bmatrix} 
	1 & tmp_1 & tmp_2 &…… & tmp_{100}
\\	0 & tmp_1 & tmp_2 &…… & tmp_{100}
\\  0 & 1 & 0 & …… & 0
 \\ …… & …… & …… & …… & ……
 \\ 0 & …… & 1 & 0 & 0
 \\	0 & 0 & …… & 1 & 0
\end{bmatrix}\quad
\times
\begin{bmatrix} 
	S_{i-1}
\\	dp_{i-1}
\\  dp_{i-2}
 \\ dp_{i-3}
 \\ ……
 \\	dp_{i-101}
\end{bmatrix}\quad

=

\begin{bmatrix} 
	S_{i}
\\	dp_{i}
\\  dp_{i-1}
 \\ dp_{i-2}
 \\ ……
 \\	dp_{i-100}
\end{bmatrix}\quad
$$

对于前 $100$ 数，直接暴力 DP 预处理出结果即可。

这是暴力 DP 的预处理：
```cpp
dp[0]=1;
s[0]=1;
for(int i=1;i<=100;i++){
	for(int j=1;j<=i;j++)dp[i]=(dp[i]+dp[i-j]*tmp[j]%p)%p;
	s[i]=(s[i-1]+dp[i])%p;
}
```

这是构造矩阵的关键代码（我把矩阵包装在了结构体里，所以略显怪异）：

```cpp
struct matrix{
	int m[105][105];
	matrix(){memset(m,0,sizeof(m));}
	void csh(){for(int i=1;i<=101;i++)m[i][i]=1;}
	void set1(){
		memset(m,0,sizeof(m));
		m[1][1]=1;
		for(int i=2;i<=101;i++)m[1][i]=m[2][i]=tmp[i-1];
		for(int i=3;i<=101;i++)m[i][i-1]=1;
	}
	void set2(){
		m[1][1]=s[100];
		for(int i=2;i<=101;i++)m[i][1]=dp[102-i];
	}
	matrix operator*(const matrix &a)const{
		matrix ans;
		for(int k=1;k<=101;k++){
			for(int i=1;i<=101;i++){
				for(int j=1;j<=101;j++){
					ans.m[i][j]=(ans.m[i][j]+(m[i][k]*a.m[k][j])%p)%p;
				}
			}
		}
		return ans;
	}
	matrix operator^(int b){
		matrix res,a=*this;res.csh(); 
		while(b){
			if(b&1)res=res*a;
			a=a*a;
			b>>=1;
		}
		return res;
	}
	void print(int n){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				printf("%d ",m[i][j]);
			}
			puts("");
		}
	}
};
```

完结撒花！



---

## 作者：Micnation_AFO (赞：1)

## $\texttt{description}$

给定一棵无限大的 $n$ 叉树，对于一个非根节点的节点，它到父节点的距离为 $d_i$，其中，$i$ 表示它是第几个子节点。

现在问一共有多少节点到根节点的距离小于等于 $x$，其中，$n {\color{red} {} \le {}} 10^5$，$x {\color{red} {} \le {}} 10^9$，$d_i {\color{red} {} \le {}} 100$。

## $\texttt{Solution}$

前置知识：简单 DP 和矩阵快速幂。

设 $f_x$ 表示 有多少个节点距离根节点**正好为** $x$，$t_x$ 表示有多少个 $d_i$ 等于 $x$。

由于 $d$ 都在 $100$ 之内，所以有：
$$
f_x = \sum\limits_{y = 1}^{100}t_y \times f_{x - y}
$$
注意边界，$f_0 = 1$，需要求的就是 $\sum\limits_{i= 1}^x f_i$。

可以用 $s$ 数组表示 $f$ 的前缀和。

$f$ 的前一百个元素可以朴素 DP 求出。看到 $x {\color{red} {} \le {}} 10^9$，不难联想到矩阵快速幂。

于是构造一个 $101 \times 101$ 的矩阵，有：
$$
\begin{bmatrix}
1&t_1&t_2&t_3&t_4&\cdots&t_{100}\\
0&t_1&t_2&t_3&t_4&\cdots&t_{100}\\
0&1&0&0&0&\cdots&0\\0&0&1&0&0&\cdots&0\\
0&0&0&1&0&\cdots&0\\
0&0&0&0&1&\cdots&0\\
\vdots&\vdots&\vdots&\vdots&\vdots&\ddots&\vdots\\
0&\cdots&0&0&0&1&0
\end{bmatrix}

\times

\begin{bmatrix}
s_{i-1}\\
f_{i-1}\\
f_{i-2}\\
f_{i-3}\\
f_{i-4}\\
f_{i-5}\\
\vdots\\f_{i-100}
\end{bmatrix}

=

\begin{bmatrix}
s_{i}\\
f_{i}\\
f_{i-1}\\
f_{i-2}\\
f_{i-3}\\
f_{i-4}\\
\vdots\\
f_{i-99}
\end{bmatrix}
$$
其实横着写可能更容易理解，但是洛谷的显示区太窄了，横着写应该会超出显示范围。

后面就是板子题了，如果还不会详见 [P3390 【模板】矩阵快速幂](https://www.luogu.com.cn/problem/P3390)。

完整代码：

```cpp
#include <iostream>
#include <cstring>

#define int long long
using namespace std;

const int N = 110;
const int M = 100010;
const int mod = 1000000007;

struct array {
    int n, m;
    int a[N][N];
    array(int x = 0, int y = 0) {
        n = x, m = y;
        memset(a, 0, sizeof(a));
    }
};

int n, x;
int t[N];
int d[M], f[M], sum[M];

array operator * (array x, array y) {
    array ans(x.n, y.m);
    for (int i = 1; i <= x.n; i++)
        for (int j = 1; j <= y.m; j++)
            for (int k = 1; k <= x.m; k++)
                ans.a[i][j] = (ans.a[i][j] + (x.a[i][k] * y.a[k][j]) % mod) % mod;
    return ans;
}

array power(array a, int b) {
    array ans(a.n, a.m);
    for (int i = 1; i <= ans.n; i++) ans.a[i][i] = 1;
    for (; b; b >>= 1) {
        if (b & 1) ans = ans * a;
        a = a * a;
    }
    return ans;
}

signed main() {
    cin >> n >> x;
    for (int i = 1; i <= n; i++) cin >> d[i], t[d[i]]++;
    f[0] = sum[0] = 1;
    for (int i = 1; i <= 101; i++) {
        for (int j = 1; j <= i; j++) f[i] = (f[i] + t[j] * f[i - j]) % mod;
        sum[i] = (sum[i - 1] + f[i]) % mod;
    }
    if (x <= 101) { cout << sum[x] << endl; return 0; }
    array ans(101, 1);
    ans.a[1][1] = sum[100];
    for (int i = 2; i <= 101; i++) ans.a[i][1] = f[101 - (i - 1)];
    array Ans(ans.n, ans.n);
    Ans.a[1][1] = 1, Ans.a[2][1] = 0;
    for (int i = 2; i <= Ans.n; i++) Ans.a[1][i] = Ans.a[2][i] = t[i - 1];
    for (int i = 3; i <= Ans.m; i++) Ans.a[i][i - 1] = 1;
    cout << (power(Ans, x - 100) * ans).a[1][1] << endl;
    return 0;
}
```





---

## 作者：Jay142753869 (赞：0)

一个dp+矩阵快速幂的题目。  
题意：给出一个每个节点有 $n$ 个孩子的多叉树，父亲到第 $i$ 个孩子有固定的长度，问到根节点的距离不超过 $x$ 的节点的数目。

很容易看出当 $x \le 100$ 时，转移方程为：

$dp_i=\sum_{j=1}^{100}dp_{i-j}\times cnt_j$

$ans=\sum_{j=0}^{x}dp_{i}$

那么因为这是线性的，所以我们可以预处理出 $100$ 以内的然后用矩阵快速幂加速，然后就做完啦。  
 _Code_
 ```cpp
#include<bits/stdc++.h>
#define ll long long
#define mod 1000000007
using namespace std;
struct matrix{
	ll x,y,a[110][110];
	matrix(){};
	matrix(ll xx,ll yy):x(xx),y(yy){memset(a,0,sizeof(a));}
}s;
ll n,x,cnt[120],sum[120],dp[120];
inline ll read(){
	register ll x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return f?-x:x;
}
inline matrix mul(matrix A,matrix B){
	matrix C=(matrix){A.x,B.y};
	for(int i=1;i<=A.x;i++)
		for(int j=1;j<=B.y;j++)
			for(int k=1;k<=B.x;k++)
				C.a[i][j]=(C.a[i][j]+A.a[i][k]*B.a[k][j])%mod;
	return C;
}
inline void init() {
	n=read(),x=read();
	for(int i=1;i<=n;i++)
		cnt[read()]++;
	dp[0]=1,sum[0]=1;
	for(int i=1;i<=100;i++) {
		for(int j=1;j<=i;j++)
			dp[i]=(dp[i]+dp[i-j]*cnt[j])%mod;
		sum[i]=(sum[i-1]+dp[i])%mod;
	}
	s.x=101,s.y=101;
	for(int i=1;i<=99;i++)
		s.a[i+1][i]=1,s.a[i][100]=cnt[101-i],s.a[i][101]=cnt[101-i];
	s.a[100][100]=s.a[100][101]=cnt[1],s.a[101][101]=1;
}
matrix qpow(matrix s,ll b){
	matrix C=(matrix){s.x,s.y};
	for(int i=1;i<=101;i++) C.a[i][i]=1;
	while(b){
		if(b&1) C=mul(C,s);
		b>>=1;
		s=mul(s,s);
	}
	return C;
}
int main(){
	init();
	matrix A=(matrix){1,101};
	for(int i=1;i<=100;i++)
		A.a[1][i]=dp[i];
	A.a[1][101]=sum[100];
	if(x<=100){
		printf("%lld\n",sum[x]);
		return 0;
	}
	A=mul(A,qpow(s,x-100));
	printf("%lld\n",A.a[1][101]%mod);
	return 0;
}
 ```

---

