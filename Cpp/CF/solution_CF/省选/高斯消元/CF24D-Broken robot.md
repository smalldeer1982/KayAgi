# Broken robot

## 题目描述

有一个 $n$ 行 $m$ 列的矩阵，现在有一个机器人在 $(x,y)$，它每一步等概率向左，右，下走或原地不动，但不能走出矩阵，问走到最后一行期望的步数。

注意，$(1,1)$ 是木板的左上角，$(n,m)$ 是木板的右下角。

## 说明/提示

$1\le n,m\le 10^3$，$1\le x\le n$，$1\le y\le m$。

## 样例 #1

### 输入

```
10 10
10 4
```

### 输出

```
0.0000000000
```

## 样例 #2

### 输入

```
10 14
5 14
```

### 输出

```
18.0038068653
```

# 题解

## 作者：aipostan (赞：121)

## **一道高斯消元+dp的好(~~例~~)题**

## But 
这不是重点（滑稽.jpg）

-------------------------------------------重点的分割线-----------------------------------------
### 反复dp就可以做完的题为什么要高斯消元呢？？
~~(才不是因为我高斯消元写炸了还懒得改)~~

上状态转移方程(**拍黑版！！**)：

$$f_{i,j} =\begin{cases}\frac {f_{i,j}+f_{i+1,j}}{2}+1 ,     	& \text {如果$m=1$}\\ \frac {f_{i+1,j}+f_{i,1}+f_{i,2}}{3}+1,	  & \text {如果$j=1$ } \\ \frac {f_{i+1,m}+f_{i,m}+f_{i,m-1}}{3}+1, & \text {如果$j=m$ } \\ \frac {f_{i+1,j}+f_{i,j}+f_{i,j+1}+f_{i,j-1}}{4}+1                & \text {其它} \end{cases} $$

我写的真好 ~~(得意.jpg)~~

考虑到反复横跳的可能不会太大（~~坂本参上！~~），
而且只要精确到小数点后4~5位（真的），
为什么不循环个50来次呢？

不就是慢一点吗？2s的时限虚什么？？

[实测结果](https://www.luogu.org/recordnew/show/19809636)

#### tips:勿抄题解，人人有责
## Code

```cpp
#include<cstdio>
double dp[1005][1005]；
int main(){
	register int n,m,x,y,i,j,t；
	scanf("%d%d%d%d",&n,&m,&x,&y)；
	for(i=n-1;i>=x;--i)
		for(t=1;t<=50;++t)//循环50次就好
			if(m==1)
				dp[i][1]=(dp[i][1]+dp[i+1][1])/2.0+1；
			else{
				dp[i][1]=(dp[i][1]+dp[i][2]+dp[i+1][1])/3.0+1；
				dp[i][m]=(dp[i][m]+dp[i][m-1]+dp[i+1][m])/3.0+1；
				for(j=2;j<m;++j)
					dp[i][j]=(dp[i][j]+dp[i][j-1]+dp[i][j+1]+dp[i+1][j])/4.0+1；
			}
	printf("%.5lf\n",dp[x][y])；//本人实测可过！
	return 0；
}
```

蒟蒻的第一篇题解还请见谅（手动求赞）

---

## 作者：Jμdge (赞：41)



双倍经验 [luogu 治疗之雨](https://www.luogu.org/problemnew/show/P4457)


两题考虑的思路比较类似，操作基本相同。。。就是一个取模一个精度

我们先排除一种特殊情况： m=1 的情况

这个时候我们发现只需要输出 2*(n-1) 就好了，至于具体证明比较显然，留给读者自推吧。。。



我们先考虑根据题意列出 期望的转移式：


$$f[i,j]=\begin{cases} {1\over4 } (f[i,j]+f[i,j-1]+f[i,j+1]+f[i+1][j]) +1 &&   1< j < m \cr {1\over3 } (f[i,j]+f[i,j+1]+f[i+1][j]) +1  &&j=1\cr {1\over3 } (f[i,j]+f[i,j-1]+f[i+1][j]) +1 &&j=m\end{cases}
$$


（至于 m=1 的情况上面已经讨论过了，就不再列入情况内）

于是乎，我们发现这玩意儿是要移项什么的来解的啊。。。

那么我们就处理一下呗~

情况一：$1<j<m$

$$ 3\times f[i,j] - f[i,j-1] - f[i,j+1]- f[i+1][j]  = 4 $$

情况二：$j=1$

$$ 2\times f[i,j] - f[i,j+1]- f[i+1][j]  = 3 $$

情况三：$j=m$

$$ 2\times f[i,j] - f[i,j-1] - f[i+1][j]  = 3 $$


辣么我们就可以高斯消元解出这道题了

等等，别忘了复杂度： $O(n^6)$ ！ 10 分！（好吧真相是 CF 里没分，这里是我自己给的标准分）

>FAQ: 什么鬼！怎么会 $n^6$的，高斯不是三次的么？

>额，这玩意儿是二维的啊，n m 同阶的情况下三次的里面要多个平方


那么我们怎么优化呢？ 我们考虑到每行只与当前层、下一层有关，那么我们可不可以从下到上依次处理每一行呢？

当然可以！处理完第 i+1 行之后 $f[i+1,j]$  就成为了常量，当前行的转移计算只要用到当前行的变量就行了

那么...我们考虑这样的复杂度是 $O(n^4)$

>FAQ: 还是过不了啊，1000 的数据呢

>别着急啊，我们再找找性质

怎么说呢，我们发现每个等式用到的变量少的可怜（woc 我好像提到了什么不得了的名字），如果你吧矩阵画一下就会发现鬼畜的地方了：


$$
\begin{bmatrix} 2 & -1 &0&0&0&0&0&0&0&0&0\\ -1 & 3&-1&0&0&0&0&0&0&0&0\\ 0&-1 & 3&-1&0&0&0&0&0&0&0\\ 0&0&-1 & 3&-1&0&0&0&0&0&0\\ 0&0&0&-1 & 3&-1&0&0&0&0&0\\0&0&0&0& -1 & 3&-1&0&0&0&0\\ 0&0&0&0&0&-1 & 3&-1&0&0&0\\ -0&0&0&0&0&0&-1 & 3&-1&0&0\\ 0&0&0&0&0&0&0&-1 & 3&-1&0\\ 0&0&0&0&0&0&0&0&-1 &3&-1\\ 0&0&0&0&0&0&0&0&0&-1&2\end{bmatrix}
\quad$$

什么你问我累不累？ $Ctrl~ C\ \ \ \ \ \ \  Ctrl~ V$ 是挺累的...

就是为了看的清楚点嘛... 发现了吧？这是个稀疏图哈~


那么我们可以考虑对于 n 行操作每次只操作三个元素： $A[i][i],A[i][i+1],A[i][m+1]$，然后用这三个元素对第 i+1 行操作

当然，如果 i+1 = m 的话就是两个元素了


然后从下向上扫一遍将其消为单位矩阵

这样的话我们每次 Gauss 就是 $O(n)$ 的了，加上我们要操作 n 行，复杂度就达到了令人满意的 $O(n^2)$

~~当然我是不知道有没有 O(1) 公式大毒瘤的~~

如果你做过了之前提过的那道治疗之雨的话就可以切掉这道题了（那道可是黑色的...虽说个人感觉这两道题好像也差不多，那这道就应该是黑题 $QVQ$， 恭喜你将要 A 掉两道黑题）

```
//by Judge
#include<cstdio>
#include<iostream>
#define fp(i,a,b) for(int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(int i=(a),I=(b)-1;i>I;--i)
#define ll long long
using namespace std;
const int mod=998244353;
const int M=1003;
typedef int arr[M];
inline int Mul(int a,int b){return 1ll*a*b%mod;}
inline void Add(int& a,int b){a+=a+b>=mod?b-mod:b;}
inline int qpow(int x,int p=mod-2){ int s=1;
	for(;p;p>>=1,x=Mul(x,x))
		if(p&1) s=Mul(s,x); return s;
} int n,m,x,y; double f[M],A[M][M];
inline void Gauss(int n){
	fp(i,1,n){ if(i<n) A[i][i+1]/=A[i][i];
		A[i][n+1]/=A[i][i],A[i][i]=1;
		A[i+1][i+1]-=A[i][i+1]*A[i+1][i];
		A[i+1][n+1]-=A[i][n+1]*A[i+1][i],A[i+1][i]=0;
	} fd(i,n-1,1) A[i][n+1]-=A[i][i+1]*A[i+1][n+1];
}
int main(){
	cin>>n>>m>>x>>y,n-=x-1,x=1;
	if(m==1) return !printf("%.10lf\n",(double)2*(n-1));
	fp(tim,1,n-1){
		A[1][1]=2,A[1][2]=-1,A[1][m+1]=f[1]+3;
		A[m][m]=2,A[m][m-1]=-1,A[m][m+1]=f[m]+3;
		fp(i,2,m-1) A[i][i-1]=A[i][i+1]=-1;
		fp(i,2,m-1) A[i][i]=3,A[i][m+1]=f[i]+4;
		Gauss(m); fp(i,1,m) f[i]=A[i][m+1];
	} return !printf("%.10lf\n",f[y]);
}
```




---

## 作者：liangzihao (赞：22)

一道比较显然的dp……

我们设f[i][j]为从第i行第j列走到最后一行行动次数的期望值，注意是以(i,j)为起点，那么f[x][y]就是答案。

在第一列时，不能往左走，所以各有1/3的概率原地不动，往下走，往右走，也就是从这三个状态转移过来，

**f[i][1]=(1/3)*(f[i][1]+f[i][2]+f[i+1][1])+1**

第m列同理，不能往右边走，

**f[i][m]=(1/3)*(f[i][m]+f[i][m-1]+f[i+1][m])+1**

其他的位置就有4个方向，也就是4个状态，就是

**f[i][j]=(1/4)*(f[i][j]+f[i][j-1]+f[i][j+1]+f[i+1][j])+1**

显然,**f[n][j]=0 (1<=j<=m)**

然后我们发现，其实每行是不满足无后效性的。

于是就可以用高斯消元来搞。

为了好懂，我们设**M=f[i][j],L=f[i][j-1],R=f[i][j+1],D=f[i+1][j]**。显然D是已知的，因为这个是上一轮的状态，所以考虑转移，有

**M=(1/4)$*$M+(1/4)$*$L+(1/4)$*$R+(1/4)$*$D+1**

移项可得，

**(1/4)$*$L+(1/4)$*$R+(-3/4)$*$M=-(1/4)$*$D-1**

左右两边稍微有点不同，应该能想到。我们把f[i+1][j]看作已知数，于是对于
f[i][1]~f[i][m]这些未知量，可以列出
m个方程，可以用高斯消元求出f[i][1]~f[i][m]。

但是高斯消元是O(n^3)的，我们可以观察系数矩阵，我们发现，每行只有不多于3个系数不为0，而且这些系数都在对角线上，其实这个消元是O(n)的。
比如，当M=4时的系数矩阵。

-2/3 1/3  0  0

1/4  -3/4 1/4 0

0 1/4 -3/4 1/4

0 0 1/3 -2/3

大概就这样的，看看就好。我们消元求出上三角矩阵，每次只需要消掉下一行的系数，而且只需消掉2个系数。而求和时，由于一行只有两个系数不为0，可以直接求出解。

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>

const int maxn=1005;

using namespace std;

double f[maxn],a[maxn][maxn],b[maxn];

int x,y,n,m,i;

void build(int m)
{
    int i;
    if (m==1)
    {
        a[1][1]=(double)-1/2;
        b[1]=(double)-f[1]/2-1;
        return;
    }
    a[1][1]=(double)-2/3; a[1][2]=(double)1/3;
    a[m][m-1]=(double)1/3; a[m][m]=(double)-2/3;
    b[1]=(double)-f[1]/3-1; b[m]=(double)-f[m]/3-1;
    for (i=2;i<m;i++)
    {
        a[i][i-1]=a[i][i+1]=(double)1/4;
        a[i][i]=(double)-3/4;
        b[i]=(double)-f[i]/4-1;
    }
}

void guass()
{
    int i,j;	
    for (i=1;i<m;i++)
    {
        double rate=a[i+1][i]/a[i][i];
        a[i+1][i]-=rate*a[i][i];
        a[i+1][i+1]-=rate*a[i][i+1];
        b[i+1]-=rate*b[i];
    }	
    f[m]=b[m]/a[m][m];	
    for (i=m-1;i>0;i--)
    {
        f[i]=(b[i]-f[i+1]*a[i][i+1])/a[i][i];
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    scanf("%d%d",&x,&y);	
    for (i=n-1;i>=x;i--)
    {
        build(m);
        guass();
    }
    printf("%.10lf",f[y]);
}
```





---

## 作者：hs_black (赞：15)

# CF24D Broken robot(高斯消元)

高斯消元新玩法

一眼期望$dp$, 考虑逆推因为第$n$层的期望是确定的(都是$0$), $F[x][y]$表示从第$x$行第$y$列开始到第$n$层的期望步数

**转移方程**:
$$F[x][y] = (F[x][y] + F[x][y+1] + F[x][y-1] + F[x+1][y]) / 4 + 1 (y != 1 \&y!=m)$$
$$F[x][y] = (F[x][y] + F[x][y+1] + F[x+1][y]) / 3 + 1 (y = 1)$$
$$F[x][y] = (F[x][y] + F[x][y-1] + F[x+1][y]) / 3 + 1 (y = m)$$
应该很好理解⑧, 从左边/右边/下边转移

因为这个$dp$有后效性, 考虑用高斯消元解决, 方程如下:
$$3F[x][i] - F[x][i+1] - F[x][i-1] = 4 + F[x+1][i] ~~(y ~!= 1 \&y~!=m)$$
$$2F[x][i] - F[x][i+1] = F[x+1][i] + 3 ~~(y = 1)$$
$$2F[x][i] - F[x][i-1] = F[x+1][i] + 3 ~~(y = m)$$

因为上一行对下一行没有影响, 所以从下至上每行进行高斯消元, 时间复杂度$\Theta(n^4)$

仔细观察系数矩阵, 发现很稀疏, 应该有更快的消元
$$
\left[ \begin{matrix} 
2 & -1 & 0 & 0 & 0\\ 
-1 & 3 & -1 & 0 & 0\\ 
0 & -1 & 3 & -1 & 0\\ 
0 & 0 & -1 & 3 & -1\\
0 & 0 & 0 & -1 & 2
\end{matrix} \right]
$$
没错, 每次消元时只是上一行把下一行消掉即可, 只需$n$次就可以笑成稀疏的上三角矩阵, 消元时不必整行都消一遍, 因为大部分都是零, 只枚举有数的即可, 最后消成上三角的时候每行只有两个系数, 回代一下就可以了

代码:

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

template <typename T>
void read(T &x) {
    x = 0; bool f = 0;
    char c = getchar();
    for (;!isdigit(c);c=getchar()) if (c=='-') f=1;
    for (;isdigit(c);c=getchar()) x=x*10+(c^48);
    if (f) x=-x;
}

template <typename T>
void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x >= 10) write(x / 10);
    putchar('0' + x % 10);
}

const int N = 1005;
double F[N][N];
int n, m, x, y;

/*

4f[x][i] = (f[x][i] + f[x][i+1] + f[x][i-1] + f[x+1][i]) + 4;
3f[x][i] - f[x][i+1] - f[x][i-1] = 4 + f[x+1][i]

3f[x][i] = (f[x][i] + f[x][i+1] + f[x+1][i]) + 3
2f[x][i] - f[x][i+1] = f[x+1][i] + 3


*/

double M[N][N];
void build(int lin) {
	M[1][1] = M[m][m] = 2, M[1][2] = M[m][m-1] = -1;
	M[1][m+1] = F[lin+1][1] + 3, M[m][m+1] = F[lin+1][m] + 3;
	for (int i = 2;i < m; i++) 
		M[i][i-1] = M[i][i+1] = -1, 
		M[i][i] = 3, M[i][m+1] = F[lin+1][i] + 4;
}

void work(int lin) {
	for (int i = 1;i < m; i++) {
		double k = M[i+1][i] / M[i][i];
		M[i+1][i] = 0, M[i+1][i+1] -= M[i][i+1] * k;
		M[i+1][m+1] -= M[i][m+1] * k;
	}
	
	F[lin][m] = M[m][m+1] / M[m][m];
	for (int i = m - 1;i >= 1; i--) 
		F[lin][i] = (M[i][m+1] - F[lin][i+1] * M[i][i+1]) / M[i][i];
}

int main() {
	read(n), read(m), read(x), read(y);
	
	if (m == 1) return cout << (n - x) * 2 << endl, 0;
	
	for (int i = n - 1;i >= x; i--) 
		build(i), work(i);
	
	printf ("%.10lf", F[x][y]);
	return 0;
}
```



---

## 作者：lyxeason (赞：10)

~~做了这道题才知道高斯消元可以这样用~~

附[ $yxc$ 大佬讲题视频](https://www.acwing.com/video/509/)

------------
### 题意

这题题意很明了，就是在一个 $N * M$ 的矩阵上走，一开始在位置 $(X, Y)$，每次等概率选择以下四种：

- 不动 $(X, Y)$
- 向左移动一格 $(X, Y - 1)$
- 向右移动一格 $(X, Y + 1)$
- 向下移动一格 $(X + 1, Y)$

不能移出矩阵，问从初始位置移动到最后一行的期望步数。

------------
### 算法

这种在矩阵上移动求 $Min, Max, Sum$ 的几乎都是 $DP$，比如去年 [CSP-J 的第 4 题](https://www.luogu.com.cn/problem/P7074)。

既然确认了是 $DP$ 那就推状态转移方程吧，注意这里使用倒推，即设 $dp[i][j]$ 为从 $(i,j)$ 出发，走到第 $N$ 行的期望步数，而不是表示从 $(x,y)$ 到 $(i,j)$ 的期望步数，不然会很麻烦。

$
\begin{cases}
dp[i][j]=\frac{1}{3}(dp[i][j]+dp[i][j+1]+dp[i+1][j])+1 \ \ \ if\ j=1\\
dp[i][j]=\frac{1}{3}(dp[i][j]+dp[i][j-1]+dp[i+1][j])+1 \ \ \ if\ j=M\\
dp[i][j]=\frac{1}{4}(dp[i][j]+dp[i][j-1]+dp[i][j+1]+dp[i+1][j])+1 \ \ \ else
\end{cases}
$

其中，$j=1$ 不能向左移动；$j=M$ 不能向右移动。

特殊情况 $M=1$，只能不动或向下，即 $dp[i][1]=\frac{1}{2}(dp[i][1]+dp[i+1][1])+1$

手动解一下方程，发现有 $dp[i][1]=dp[i+1][1]+2$

那么答案就可以直接算出，为 $2*(N-X)$

但是，发现状态转移方程有后效性，$dp[i][j]$ 会用到 $dp[i][j+1]$，而 $dp[i][j+1]$ 也会用到 $dp[i][j]$，构成了环。

但这题很良心，没有向上移动，行与行之间没有依赖关系，第 $i$ 行只会用到第 $i+1$ 行，不会用到第 $i-1$ 行，所以从 $N$ 开始倒序循环，就可以解决行。

于是，就可以用高斯消元解决列与列之间的依赖关系啦。

高斯消元是用来解决 $N$ 元一次方程组的，需要一个系数矩阵，具体算法过程分三步：

1. 找到第 $i$ 列最大的数并将其所在行挪到当前最靠上的一行，第 $i$ 行。
2. 将该数变为 $1$（将第 $i$ 行所有数除以该数）。
3. 将所有靠下行第 $i$ 列上的数变为 $0$（将所有行数比 $i$ 大的行上的数都减去该行第 $i$ 列数乘以第 $i$ 行上于其在同列的数）。

最后就转化成了一个上三角矩阵，可以轻松求出未知数，且这题不存在无解或有多组解。

$DP$ 状态转移方程在每一行上和高斯消元可以求的一样，是一个 $N$ 元一次方程组。所以可以倒序遍历每一行，每一行再填一下高斯消元系数矩阵就好了。

所以，现在的问题就是，高斯消元的系数矩阵怎么填，其实化简一下状态转移方程就很明了了。

$
\begin{cases}
\frac{2}{3}dp[i][j]=\frac{1}{3}dp[i][j+1]+\frac{1}{3}dp[i+1][j]+1 \ \ \ if\ j=1\\
\frac{2}{3}dp[i][j]=\frac{1}{3}dp[i][j-1]+\frac{1}{3}dp[i+1][j]+1 \ \ \ if\ j=M\\
\frac{3}{4}dp[i][j]=\frac{1}{4}dp[i][j-1]+\frac{1}{4}dp[i][j+1]+\frac{1}{4}dp[i+1][j]+1 \ \ \ else
\end{cases}
$

其中 $dp[i+1][j]$ 是已经算出来的，那么把已知数和未知数分开就变成了：

$
\begin{cases}
\frac{2}{3}dp[i][j]-\frac{1}{3}dp[i][j+1]=\frac{1}{3}dp[i+1][j]+1 \ \ \ if\ j=1\\
\frac{2}{3}dp[i][j]-\frac{1}{3}dp[i][j-1]=\frac{1}{3}dp[i+1][j]+1 \ \ \ if\ j=M\\
\frac{3}{4}dp[i][j]-\frac{1}{4}dp[i][j-1]-\frac{1}{4}dp[i][j+1]=\frac{1}{4}dp[i+1][j]+1 \ \ \ else
\end{cases}
$

但是高斯消元的时间复杂度是 $O(N^3)$ 级别，乘上行数 $N$，$O(N^4)$ 时间复杂度妥妥爆炸。

不慌，来看一下一个 $5*5$ 的系数矩阵：

$
\begin{bmatrix}
\frac{2}{3} & -\frac{1}{3} & 0 & 0 & 0 & \ \vert\ & \frac{1}{3}dp[i+1][1]+1\\
-\frac{1}{4} & \frac{3}{4} & -\frac{1}{4} & 0 & 0 & \vert & \frac{1}{4}dp[i+1][2]+1\\
0 & -\frac{1}{4} & \frac{3}{4} & -\frac{1}{4} & 0 & \vert & \frac{1}{4}dp[i+1][3]+1\\
0 & 0 & -\frac{1}{4} & \frac{3}{4} & -\frac{1}{4} & \vert & \frac{1}{4}dp[i+1][4]+1\\
0 & 0 & 0 & \frac{2}{3} & -\frac{1}{3} & \vert & \frac{1}{3}dp[i+1][5]+1\\
\end{bmatrix}
$

发现只有主对角线和两旁的对角线以及最后一列上的数非 $0$。

再来看一下三个步骤。

1. 找到第 $i$ 列最大的数并将其所在行挪到当前最靠上的一行，第 $i$ 行。
2. 将该数变为 $1$（将第 $i$ 行所有数除以该数）。
3. 将所有靠下行第 $i$ 列上的数变为 $0$（将所有行数比 $i$ 大的行上的数都减去该行第 $i$ 列数乘以第 $i$ 行上于其在同列的数）。

步骤 $1$ 中不用找，就是当前最靠上的一行，已经在最靠上的一行了，不用换。

步骤 $2$ 中该行被除后有变化，即非 $0$ 的，就只有 $(i,i),(i,i+1),(i,M+1)$ (注意 $(i,i-1)$ 虽然一开始非 $0$，但已经被第 $i-1$ 列做的 $3$ 号操作变为 $0$ 了)，所以没次只要动 $3$ 个数就行。

步骤 $3$ 中一个行数比 $i$ 大的行只有第 $i$ 列上的数非 $0$，减的才有意义，而满足这一条件的，靠下的行就只有第 $i+1$ 行，且第 $i$ 行上非 $0$ 的位置只有 $(i,i),(i,i+1),(i,M+1)$，第 $i+1$ 行上的数减后会改变，也只用动 $3$ 个数。

所以，综上所述，就得到了一个时间复杂度 $O(NM)$ 的算法，$1e3*1e3=1e6$，稳过。

------------
### 代码
###### 代码里有注释

```cpp


#include <cmath>
#include <cstdio>

using namespace std;

const double eps = 1e-6;
int N;
int M;
int X;
int Y;
double dp[1009][1009];
double A[1009][1009];
double res;

void In () {
    scanf("%d%d%d%d", &N, &M, &X, &Y);
}

void Gauss () {  //高斯消元
    double t;
    
    for (int i = 1; i <= M; i++) {
        t = A[i][i];
        A[i][i] /= t; A[i][i + 1] /= t;  //第二步
        if (i < M) {   //这里特判是因为如果 i=M 那 A[i][M+1] 已经在 A[i][i + 1] /= t 时除过 t 了，就没必要再除了
            A[i][M + 1] /= t;
        }
        t = A[i + 1][i];
        A[i + 1][i] -= t * A[i][i]; A[i + 1][i + 1] -= t * A[i][i + 1]; A[i + 1][M + 1] -= t * A[i][M + 1];   //第三步
    }
    
    for (int i = M; i; i--) {   //推出答案，存在 A[i][M+1] 中
        A[i - 1][M + 1] -= A[i - 1][i] * A[i][M + 1];
        A[i - 1][i] -= A[i - 1][i] * A[i][i];
    }
}

void Solve () {
    if (M == 1) {   //特判 M=1
        res = 2 * (N - X);
        return;
    }
    
    for (int i = N - 1; i >= X; i--) {
        A[1][1] = A[M][M] = 2.0 / 3;
        A[1][2] = A[M][M - 1] = -1.0 / 3;
        A[1][M + 1] = dp[i + 1][1] / 3 + 1;
        A[M][M + 1] = dp[i + 1][M] / 3 + 1;
        
        for (int m = 2; m < M; m++) {
            A[m][m - 1] = A[m][m + 1] = -1.0 / 4;
            A[m][m] = 3.0 / 4;
            A[m][M + 1] = dp[i + 1][m] / 4 + 1;
        }
        
        Gauss();
        
        for (int m = 1; m <= M; m++) {
            dp[i][m] = A[m][M + 1];
        }
    }
    
    res = dp[X][Y];   //倒推
}

void Out () {
    printf("%.4lf\n", res);
}

int main () {
    
    In();
    Solve();
    Out();
    
    return 0;
}
```

---

## 作者：Huami360 (赞：4)

[博客原文食用更佳(不知道本谷的$markdown$怎么换行)](https://www.cnblogs.com/Qihoo360/p/9606787.html)

题意：给定一个$n\times m$的矩阵，每次可以向→↓←移动一格，也可以原地不动，求从$(x,y)$到最后一行的期望步数。

~~此题标签$DP$~~

~~看到上面这个肯定会想到~~

方法一：   $f[i][j]$表示表示从$(x,y)$走到$(i,j)$的期望步数，正推

方法二：   $f[i][j]$表示从$(i,j)$走到最后一行的期望步数，倒推

事实上，方法二更优秀。

因为如果用方法一，我们要求的答案就是$\frac{\sum f[\text{最后一行}][\text{每个位置}]}{m}$

而如果我们用方法二，答案就是$f[x][y]$，省时又省力。

所以我们就用方法二。

然而上面两种方案都是有后效性的，因为$f[i][j]$取决与$f[i-1][j](\text{或}f[i+1][j],f[i][j-1],f[i][j+1]$甚至他本身，我们无法确定一个正确的递推顺序。

这时就要用$DP$套高斯消元了。

显然$f[\text{最后一行}][\text{每个位置}]$都为$0$，于是枚举行，从$n-1$枚举到$x$。

先把状态转移方程写出来。

$f[i][j]=\begin{cases}\ \frac{1}{3}(f[i][j]+f[i][j+1]+f[i+1][j])\  (j=1)\\\frac{1}{4}(f[i][j-1]+f[i][j]+f[i][j+1]+f[i+1][j])\  (j!=1,j!=m)\\\frac{1}{3}(f[i][j]+f[i][j-1]+f[i+1][j])\  (j=m)\end{cases}$

可以发现，方程中$f[i+1][j]$固定出现，而这是我们已知的（最后一行均为$0$，一行一行往上倒推），于是考虑移项。

以$j=1$为例，
$$f[i][j]=\frac{1}{3}(f[i][j]+f[i][j+1]+f[i+1][j])$$
移项得
$$-\frac{1}{3}f[i+1][j]=\frac{1}{3}(-2f[i][j]+f[i][j+1]+f[i+1][j])$$
于是我们便得到了$m$个一次方程，用高斯消元即可解出每一行所有的$f$值。

高斯消元理论复杂度$O(n^3)$，但是我们仔细观察本题，每行事实上只有两个数需要消元，所以我们可以在$O(m)$的时间复杂度里完成高斯消元，算法总时间复杂度$O(nm^2)$。

```cpp
#include <cstdio>
#include <cstdlib>
const int MAXN = 1010;
double f[MAXN][MAXN];
double M[MAXN][MAXN];
int n, m, x, y;
void Gauss(){            //高斯消元
    for(int i = 1; i <= m; ++i){
       double tmp = 1.0 / M[i][i];        //系数化一
       M[i][i] *= tmp; M[i][m + 1] *= tmp;
       if(i == m) break;
       M[i][i + 1] *= tmp; 
       tmp = M[i + 1][i] / M[i][i];         //下一行消掉该元
       M[i + 1][i] -= tmp * M[i][i]; M[i + 1][i + 1] -= tmp * M[i][i + 1]; M[i + 1][m + 1] -= tmp * M[i][m + 1];
    }
    for(int i = m - 1; i; --i) M[i][m + 1] -= M[i + 1][m + 1] * M[i][i + 1];   //回代
}
int main(){
    scanf("%d%d%d%d", &n, &m, &x, &y);
    for(int i = n - 1; i >= x; --i){
       M[1][1] = -1.0 + 1.0 / 3;         //
       M[1][2] = 1.0 / 3;
       for(int j = 2; j < m; ++j){
          M[j][m + 1] = (-f[i + 1][j]) / 4.0 - 1;
          M[j][j] = -1.0 + 1.0 / 4;
          M[j][j - 1] = M[j][j + 1] = 1.0 / 4;
       }
       M[m][m] = -1.0 + 1.0 / 3;
       M[m][m - 1] = 1.0 / 3;
       if(m == 1) M[1][1] = -1.0 + 1.0 / 2;
       M[1][m + 1] = (-f[i + 1][1]) / 3.0 - 1;
       M[m][m + 1] = (-f[i + 1][m]) / 3.0 - 1;   //构建矩阵
       if(m == 1) M[m][m + 1] = (-f[i + 1][m]) / 2.0 - 1;   //特判$m=1$的情况
       Gauss();
       for(int j = 1; j <= m; ++j)
          f[i][j] = M[j][m + 1];
    }
    printf("%.10lf", f[x][y]);
    return 0;
}
```

---

## 作者：D2T1 (赞：3)

[$\large\text{My blog}$](https://www.luogu.com.cn/blog/390770/blogcenter)

## 题解 CF24D

一道**高斯消元**求解**有后效性 DP** 的题目。

------------

首先考虑 DP。设 $dp[i,j]$ 表示机器人从 $(i,j)$ 走到最后一行的期望步数。转移如下：

$\large\begin{cases}dp[i,1] = \frac13(dp[i,1],dp[i,2],dp[i+1,1])+1 \\ dp[i,j] = \frac14(dp[i,j],dp[i,j-1],dp[i,j+1],dp[i+1,j])+1~~(if~2\leq j\leq m-1) \\ dp[i,m] = \frac13(dp[i,m],dp[i,m-1],dp[i+1,m])+1\end{cases}$

**~~我们要记住dalao Rainbow的一句话：很多数学期望 DP 都会采取倒推的方式执行。~~** 所以从 $n-1$ 行算至第 $x$ 行。初始状态为 $dp[n,i]=0$，目标为 $dp[x,y]$。

可以发现行与行之间满足无后效性，但每行之间的元素不满足。

但是这题就不能用 DP 做吗？不是的。

------------

将上面给出的三个转移方程稍加变形，得到：

$\large\begin{cases}\frac23dp[i,1]-\frac13dp[i,2]=\frac13dp[i+1,1]+1 \\ -\frac14dp[i,j-1]+\frac34dp[i,j]-\frac14dp[i,j+1]=\frac14dp[i+1,j]+1~~(if~2\leq j\leq m-1) \\ -\frac13dp[i,m-1]+\frac23dp[i,m]=\frac13dp[i+1,m]+1\end{cases}$

可以发现等式右边的那些东西 $dp$ 数组的第一维都是 $i+1$，都算过，当常数项处理，就可以用[**高斯消元**](https://www.luogu.com.cn/problem/P3389)求解。

可以列出矩阵（行数为 $m$ ，列数为 $m+1$）（例子中 $m=5$）：

$$ 
\large\begin{pmatrix}
2/3&-1/3&0&0&0&|&\frac13dp[i+1,1]+1 \\
-1/4&3/4&-1/4&0&0&|&\frac14dp[i+1,2]+1 \\ 
0&-1/4&3/4&-1/4&0&|&\frac14dp[i+1,3]+1 \\
0&0&-1/4&3/4&-1/4&|&\frac14dp[i+1,4]+1 \\
0&0&0&-1/3&2/3&|&\frac13dp[i+1,5]+1
\end{pmatrix}
$$

而且可以发现该矩阵 $0$ 很多，可以 $O(m)$ 求解。

------------

最后加了一个 $m=1$ 时的特判：当 $m=1$ 时，只能选择向下走或不走，向下一格期望步数为 $2$，答案就为 $2(n-x)$。

总复杂度 $O(nm)$，能过此题。

## 代码

```cpp
//CF24D
#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
double dp[N][N], mat[N][N];
int n, m, x, y;

void init(int i){
	mat[1][1] = mat[m][m] = 2 / 3.0;
	mat[1][2] = mat[m][m-1] = -1 / 3.0;
	mat[1][m+1] = dp[i+1][1] / 3.0 + 1;
	mat[m][m+1] = dp[i+1][m] / 3.0 + 1;
	for(int j = 2; j < m; ++ j){
		mat[j][j] = 3 / 4.0;
		mat[j][m+1] = dp[i+1][j] / 4.0 + 1;
		mat[j][j-1] = mat[j][j+1] = -1 / 4.0;
	}
}
void gauss(){
	for(int i = 1; i <= m; ++ i){
		double w = 1.0 / mat[i][i];
		mat[i][i] = 1.0;
		mat[i][m+1] *= w;
		if(i != m){
			mat[i][i+1] *= w;
			w = mat[i+1][i] / mat[i][i];
			mat[i+1][i] = 0;
			mat[i+1][i+1] -= w * mat[i][i+1];
			mat[i+1][m+1] -= w * mat[i][m+1];
		}
	}
	for(int i = m - 1; i; -- i)
		mat[i][m+1] -= mat[i+1][m+1] * mat[i][i+1];
}

int main(){
	scanf("%d%d%d%d", &n, &m, &x, &y);
	if(m == 1) return printf("%d\n", 2 * (n - x)) & 0;
	for(int i = n - 1; i >= x; -- i){
		init(i), gauss();
		for(int j = 1; j <= m; ++ j) dp[i][j] = mat[j][m+1];
	}
	printf("%.10f\n", dp[x][y]);
	return 0;
}
```

---

## 作者：_171829 (赞：3)

本题大意总结：给出一个 $n*m$ 的矩阵区域，一个机器人初始在第 $x$  行第 $y$ 列，每一步机器人会等概率地选择停在原地，左移一步，右移一步，下移一步，如果机器人在边界则不会往区域外移动，问机器人到达最后一行的期望步数。

解析如下：

  在 $m = 1$  时每次有 $\dfrac{1}{2}$ 的概率不动，有 $\dfrac{1}{2}$ 的概率向下移动一格，答案为 $2\cdot (n-x)$。 设  为机器人机器人从第 $i$ 行第 $j$ 列出发到达第  行的期望步数，最终状态为 $f_{n,j} = 0$ 。 由于机器人会等概率地选择停在原地，左移一步，右移一步，下移一步，考虑$f_{i,j}$的状态转移：

1.  $f_{i,j}=\dfrac{1}{3}\cdot(f_{i+1,1}+f_{i,2}+f_{i,1})+1$

2. $f_{i,j}=\dfrac{1}{4}\cdot(f_{i,j}+f_{i,j-1}+f_{i,j+1}+f_{i+1,j})+1$

3. $f_{i,m}=\dfrac{1}{3}\cdot(f_{i,m}+f_{i,m-1}+f_{i+1,m})+1$

 在行之间由于只能向下移动，是满足无后效性的。在列之间可以左右移动，在移动过程中可能产生环，不满足无后效性。 将方程变换后可以得到：
1. $2f_{i,1}-f_{i,2}=3+f_{i+1,1}$

2. $3f_{i,j}-f_{i,j-1}-f_{i,j+1}=4+f_{i+1,1}$

3. $2f_{i,m}-f_{i,m-1}=3+f_{i+1,m}$

 由于是逆序的递推，所以每一个 $f_{i+1,j}$ 是已知的。 由于有 $m$ 列，所以右边相当于是一个 $m$ 行的列向量，那么左边就是 $m$  行 $m$ 列的矩阵。使用增广矩阵，就变成了 $m$ 行 $m+1$ 列的矩阵，然后进行 **高斯消元①** 即可解出答案。

注释：

①：**高斯消元法**（Gauss-Jordan elimination）是求解线性方程组的经典算法，它在当代数学中有着重要的地位和价值，是线性代数课程教学的重要组成部分。

  高斯消元法除了用于线性方程组求解外，还可以用于行列式计算、求矩阵的逆，以及其他计算机和工程方面。

  夏建明等人之前提出了应用图形处理器 (GPU) 加速求解线性方程组的高斯消元法，所提出的算法与基于 CPU 的算法相比较取得更快的运算速度。二是提出各种变异高斯消元法以满足特定工作的需要。

 附AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;
double a[maxn][maxn], f[maxn];
int n, m;
void solve(int x) {
  memset(a, 0, sizeof a);
  for (int i = 1; i <= m; i++) {
    if (i == 1) {
      a[i][i] = 2;
      a[i][i + 1] = -1;
      a[i][m + 1] = 3 + f[i];
      continue;
    } else if (i == m) {
      a[i][i] = 2;
      a[i][i - 1] = -1;
      a[i][m + 1] = 3 + f[i];
      continue;
    }
    a[i][i] = 3;
    a[i][i + 1] = -1;
    a[i][i - 1] = -1;
    a[i][m + 1] = 4 + f[i];
  }

  for (int i = 1; i < m; i++) {
    double p = a[i + 1][i] / a[i][i];
    a[i + 1][i] = 0;
    a[i + 1][i + 1] -= a[i][i + 1] * p;
    a[i + 1][m + 1] -= a[i][m + 1] * p;
  }

  f[m] = a[m][m + 1] / a[m][m];
  for (int i = m - 1; i >= 1; i--)
    f[i] = (a[i][m + 1] - f[i + 1] * a[i][i + 1]) / a[i][i];
}
int main() {
  scanf("%d %d", &n, &m);
  int st, ed;
  scanf("%d %d", &st, &ed);
  if (m == 1) {
    printf("%.10f\n", 2.0 * (n - st));
    return 0;
  }
  for (int i = n - 1; i >= st; i--) {
    solve(i);
  }
  printf("%.10f\n", f[ed]);
  return 0;
}
```


---

## 作者：Conan15 (赞：3)

真的是太搞笑了，除了第一篇题解，其它做法全都是大力高斯消元 $O(nm^3)$ 加观察，发现每一行需要消元的元素很少，于是乎就 $O(nm)$ 了。\
感觉应该是把网格看成图，发现边很稀疏才能想到这种做法，但事实上这和树上随机游走几乎是差不多的。\
直接暴力建图高消显然 $O(n^3m^3)$，但是可以做分层，从下往上考虑每一层单独做高消就是 $O(nm^3)$ 了，不再赘述。

----------

提供一种好想好推好写的做法。

首先不能往上走，所以 $n' \leftarrow n - (x-1)$，直接把它提到第一层。\
先特判掉 Corner Case：若 $m=1$，有 $\frac{1}{2}$ 的概率留在原地，$\frac{1}{2}$ 概率往下走，$f_i = \frac{f_{i-1}+f_i}{2}+1$，不难推出 $f_n = 2(n-1)$。

还是考虑从下往上一层一层算期望，**设 $c_i$ 表示下一行的期望值**。\
然后我们发现这一行转化成图（左右相邻元素连边），可以看作**一条链**，相同地，还是设 $f_i$ 表示从这一行第 $i$ 列走到最后一行的期望步数。\
链就是树的特殊形态啊！所以不难想到经典 trick（[题目](https://www.luogu.com.cn/problem/CF1823F)）：设 $f_i = A_i f_{i-1} + B_i$，这个转化本质上就是在用**一个未知数通过系数加乘表示所有方程**。\
然后就不难推式子了：

----------

## $i=1$

显然有 $f_i = \frac{1}{3}(f_i + f_{i+1} + c_i)+1$。
把 $f_{i+1}$ 转化形式：$f_i = \frac{1}{3}(f_i + A_{i+1}f_i + B_{i+1} + c_i)+1$。\
移项化简即可得到 $f_i = \frac{B_{i+1}+c_i+3}{2-A_{i+1}}$。\
所以 $A_i = 0, B_i = \frac{B_{i+1}+c_i+3}{2-A_{i+1}}$。

## $i=m$

朴素转移式：$f_i = \frac{1}{3}(f_i + f_{i-1} + c_i)+1$。\
直接移项就可以得到 $f_i = \frac{1}{2}f_{i-1} + \frac{c_i+3}{2}$。\
所以 $A_i = \frac{1}{2}, B_i = \frac{c_i+3}{2}$。

## $1 \lt i \lt m$

则有 $f_i = \frac{1}{4}(f_i + f_{i-1} + f_{i+1} + c_i)+1$。\
同理地，将 $f_{i+1}$ 先化成用 $f_i$ 表示的形式：$f_i = \frac{1}{4}(f_i + f_{i-1} + A_{i+1}f_i + B_{i+1} + c_i)+1$。\
再移项：$f_i = \frac{1}{3-A_{i+1}} f_{i-1} + \frac{B_{i+1}+c_i+4}{3-A_{i+1}}$。\
所以 $A_i = \frac{1}{3-A_{i+1}}, B_i = \frac{B_{i+1}+c_i+4}{3-A_{i+1}}$。

----------

最后再递推一下 $f$ 数组即可，这不比高斯消元好写好观察？？

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, m, x, y;
double A[N], B[N], c[N];
void dfs(int u) {
    if (u == m) return A[u] = 0.5, B[u] = (c[u] + 3) / 2, void();
    dfs(u + 1);
    if (u == 1) return B[u] = (B[u + 1] + c[u] + 3) / (2 - A[u + 1]), void();
    A[u] = 1.00 / (3 - A[u + 1]), B[u] = (B[u + 1] + c[u] + 4) * 1.00 / (3 - A[u + 1]);
}

int main() {
    scanf("%d%d%d%d", &n, &m, &x, &y), n -= (x - 1);    //强行扔到第一行第 y 列
    if (m == 1) return printf("%.7lf\n", (n - 1) * 2.0), 0;
    
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= m; j++) A[j] = B[j] = 0;
        dfs(1);
        for (int j = 1; j <= m; j++) c[j] = A[j] * c[j - 1] + B[j];
    }
    printf("%.7lf\n", c[y]);
    return 0;
}
```

---

## 作者：ListenSnow (赞：2)

$DP$ 的后效性处理模板题。

## 题意

给定一个 $n$ 行 $m$ 列的棋盘，给出起点 $(x,y)$，要走到棋盘的**最后一行** ，每次等概率向左、右、下走或原地不动，**不能走到棋盘外面** ，求走到最后一步的期望步数。

## 思路
设 $f[i][j]$ 表示从 $(i,j)$ 走到最后一行的期望步数，那么最终的答案就是 $f[x][y]$ ，由于无法走出棋盘，状态转移方程需要分三种情况讨论：

当 $j=1$ 时，$f[i][j]=\dfrac{f[i][j]+f[i+1][j]+f[i][j+1]}{3}+1$。

当 $1<j<m$ 时，$f[i][j]=\dfrac{f[i][j]+f[i+1][j]+f[i][j+1]+f[i][j-1]}{4}+1$。

当 $j=m$ 时，$f[i][j]=\dfrac{f[i][j]+f[i+1][j]+f[i][j-1]}{3}+1$。

同一行中的 $f[i][j]$ 具有**后效性**，无法通过递推的方式直接求出。

通过观察可以发现，一行可以列出 $m$ 个方程。如果先求出下一行的期望步数，那么 $f[i+1][j]$ 就是一个常量，于是就只有 $m$ 个未知数，也就是一个 $m$ 元一次方程组，可以**用高斯消元求解**。

首先对方程进行常数项分离，可以得到增广矩阵：

$\begin{bmatrix}
 \dfrac{2}{3}  & -\dfrac{1}{3} &0  &0  &0  &\dfrac{1}{3}f[i+1][1]+1 \\
  -\dfrac{1}{4} &\dfrac{3}{4}  &-\dfrac{1}{4}&0  &0  &\dfrac{1}{3}f[i+1][2]+1 \\
 0  & -\dfrac{1}{4} &\dfrac{3}{4}  &-\dfrac{1}{4}  &0  &\dfrac{1}{3}f[i+1][3]+1 \\
0  & 0 &-\dfrac{1}{4} &\dfrac{3}{4}  &-\dfrac{1}{4}  &\dfrac{1}{3}f[i+1][4]+1 \\
0& 0 &0  &-\dfrac{1}{3}  &\dfrac{2}{3}  &\dfrac{1}{3}f[i+1][5]+1
\end{bmatrix}$

便于理解，这里给出的是当 $m=5$ 时的特殊情况。

一般的高斯消元时间复杂度为 $O(n^3)$ 。
但是可以发现，这里的一次项系数第一行和最后一行有两个系数不为零，第二行到倒数第二行每一行都有三个系数不为零。那么在高斯消元的过程中就省去了寻找第 $i$ 列最大系数的过程。

同时每次向下消元只需要消除下面一行即可，同时每行只有消除三个数，所以最终本题高斯消元的时间复杂度就只有 $O(m)$。总的时间复杂度就为 $O(nm)$，可以通过本题。

同时需要注意，当 $m=1$ 时，只能向下走或原地不动，于是 $f[i][j]=\dfrac{f[i][j]+f[i+1][j]}{2}+1$。

整理可以得到，$f[i][j]=f[i+1][j]+2$。于是最终的答案就是 $2*(n-x)$ ，特判输出即可。

还有一些高斯消元的细节见代码。

## code:
```cpp
#include<iostream>
using namespace std;
const int M=1010;
int n,m,x,y;
double a[M][M],f[M][M];
void YZXAKIOI()
{
	for(int i=1;i<=m;i++)//这里是m，因为是将每一行做一遍高斯消元 
	{
		double r=a[i][i];//不需要寻找最大系数了 
		a[i][i]/=r,a[i][i+1]/=r;
		if(i<m) a[i][m+1]/=r;//如果不特判，最后一行最后一列就会被除两次 
		int d[3]={i,i+1,m+1};//下一行的本列，下一行本列的右边，和最右边的常数项需要相减 
		double t=a[i+1][i];
		for(int j=0;j<3;j++)
		    a[i+1][d[j]]-=a[i][d[j]]*t;
	}
	for(int i=m;i>=1;i--)
	{
		a[i-1][m+1]-=a[i-1][i]*a[i][m+1];
		a[i-1][i]-=a[i][i]*a[i-1][i];
	}
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&x,&y);
	if(m==1) printf("%.4lf\n",2.0*(n-x));	
	else
	{
		for(int i=n-1;i>=1;i--)//注意倒序，因为第n行的期望步数一定为0，故直接从倒数第二行开始求解
		{
			a[1][1]=2.0/3,a[1][2]=-1.0/3,a[1][m+1]=1+f[i+1][1]/3;
			a[m][m]=2.0/3,a[m][m-1]=-1.0/3,a[m][m+1]=1+f[i+1][m]/3;
			for(int j=2;j<m;j++) a[j][j]=3.0/4,a[j][j-1]=a[j][j+1]=-1.0/4,a[j][m+1]=f[i+1][j]/4+1;
			YZXAKIOI();
			for(int j=1;j<=m;j++) f[i][j]=a[j][m+1];
		}
		printf("%.4lf\n",f[x][y]);
	}
	return 0;
}
```


---

## 作者：Heartlessly (赞：2)

## Description

现在有一个机器人，最初站在 $n \times m\ (1 \leq n,m\leq 1000)$ 矩阵中的 $(x,y)\ (1 \leq x \leq n, 1\leq y \leq m)$ 位置。每次它会等概率的选择 **原地不动，向左移动，向右移动，向下移动** 四种操作。当然，机器人在第 $1$ 列时不会选择向左移动，第 $m$ 列时不会选择向右移动。求机器人到达第 $n$ 行的期望步数，至少精确到 $10^{-4}$ 。


## Source

**[[Luogu]CF24D](https://www.luogu.org/problemnew/show/CF24D)**

**[[Codeforces]24D](http://codeforces.com/problemset/problem/24/D)**

## Solution

求期望步数，很容易想到 **期望DP** 。我们用 $f_{i,j}$ 表示从 $(i,j)$ 走到最后一行的期望步数，那么初始状态就是 $f_{n,i} = 0\ (1 \leq i \leq m)$（从最后一行走到最后一行的期望步数为 $0$），要求的答案就是 $f_{x,y}$（根据状态即能得到），状态转移方程如下（分 $3$ 种情况讨论）：
$$
f_{i,j}=\left\{\begin{matrix}
 \frac{1}{3}\left ( f_{i,j} + f_{i,j+1} + f_{i+1,j} \right )+1& (j=1)\\ 
 \frac{1}{4}\left ( f_{i,j} + f_{i,j+1} + f_{i,j-1} + f_{i+1,j} \right )+1& (1< j< m)  \\ 
 \frac{1}{3}\left ( f_{i,j} + f_{i,j-1} + f_{i+1,j} \right )+1& (j=m) \\ 
\end{matrix}\right.
$$

值得注意的是：$m = 1$ 时比较特殊，因为不能向左和向右移动，此时
$$
f_{i,j}=\frac{1}{2} \left( f_{i,j} + f_{i+1,j} \right) + 1
$$
这个转移方程是倒推的，并且有后效性，所以不能直接转移。在求 $f_{i,j}$ 时，$f_{i+1,j}$ 是 **已知** 的，而 $f_{i,j-1},f_{i,j},f_{i,j+1}$ 都是 **未知** 的，我们把未知量移到左边，把已知量移到右边，可以得到：
$$
\left\{\begin{matrix}
-\frac{2}{3}f_{i,j}+\frac{1}{3}f_{i,j+1}=-\frac{1}{3}f_{i+1,j}-1 & (j=1)\\
\frac{1}{4}f_{i,j-1}-\frac{3}{4}f_{i,j}+\frac{1}{4}f_{i,j+1}=-\frac{1}{4}f_{i+1,j}-1& (1 < j < m)\\
\frac{1}{3}f_{i,j-1}-\frac{2}{3}f_{i,j}=-\frac{1}{3}f_{i+1,j}-1 & (j=m)\\
\end{matrix}\right.
$$

同理，$m = 1​$ 时，
$$
-\frac{1}{2}f_{i,j} = -\frac{1}{2}f_{i+1,j} - 1
$$

我们会发现一共有 $m$ 个未知数和 $m$ 个方程，很容易想到 **高斯消元** 求解未知量 $f_{i,1} \sim f_{i,m}\ (1 \leq i < n)$ 。

比如说，当 $m = 5​$ 时，所构成的矩阵就是：
$$
\begin{bmatrix}
-\frac{2}{3} & \color{blue}{\frac{1}{3}} & 0 & 0 & 0\\ 
 \color{red}{\frac{1}{4}} & -\frac{3}{4} & \color{blue}{\frac{1}{4}} & 0 & 0\\ 
 0 &  \color{red}{\frac{1}{4}} & -\frac{3}{4} & \color{blue}{\frac{1}{4}} & 0\\ 
 0 & 0 &  \color{red}{\frac{1}{4}} & -\frac{3}{4} & \color{blue}{\frac{1}{4}}\\ 
0 & 0 & 0 &  \color{red}{\frac{1}{3}} & -\frac{2}{3}\\ 
\end{bmatrix}
=\begin{bmatrix}
-\frac{1}{3}f_{i+1,j}-1\\
-\frac{1}{4}f_{i+1,j}-1\\
-\frac{1}{4}f_{i+1,j}-1\\
-\frac{1}{4}f_{i+1,j}-1\\
-\frac{1}{3}f_{i+1,j}-1\\
\end{bmatrix}
$$

本来 **高斯消元** 的时间复杂度应该是 $O(n^3)$ 的。但是观察矩阵能够发现，其实这是一个稀疏矩阵，未知数全部集中在对角线上，$0$ 的地方不需要消元，我们需要消元的只有 $m - 1$ 个数（上图 红色 的数字），回带时原方程中也只需要消去 $m - 1$ 个数（上图 蓝色 的数字），所以本题中 **高斯消元** 时间复杂度为 $O(m)$ 。总时间复杂度为 $O(nm)$ 。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
    x = f ? -x : x;
}

const int MAXN = 1000;
int n, m, x, y;
double a[MAXN + 5][MAXN + 5], f[MAXN + 5][MAXN + 5];

inline void Gauss() {
    for (int i = 1; i < m; ++i) {
        double t = a[i][i];
        a[i][i] = 1;
        a[i][i + 1] /= t;
        a[i][m + 1] /= t;
        t = a[i + 1][i];
        a[i + 1][i] = 0;
        a[i + 1][i + 1] -= t * a[i][i + 1];
        a[i + 1][m + 1] -= t * a[i][m + 1];
    }//消元，消去下一行方程开头的未知数 
    a[m][m + 1] /= a[m][m];
    a[m][m] = 1;//求出最后一个未知数的解 
    for (int i = m - 1; i; --i)
        a[i][m + 1] -= a[i + 1][m + 1] * a[i][i + 1];//回带，消去下一行方程末尾的未知数
}

int main() {
    freopen("eat.in", "r", stdin);
    freopen("eat.out", "w", stdout);
    read(n), read(m), read(x), read(y);
    for (int i = n - 1; i >= x; --i) {
        if (m == 1) {
            a[1][1] = -1.0 / 2;
            a[1][m + 1] = -f[i + 1][1] / 2.0 - 1;//特判 m = 1 
        } else {
            a[1][1] = -2.0 / 3;
            a[1][2] = 1.0 / 3;
            a[1][m + 1] = -f[i + 1][1] / 3.0 - 1.0;
            for (int j = 2; j < m; ++j) {
                a[j][j] = -3.0 / 4;
                a[j][j - 1] = a[j][j + 1] = 1.0 / 4;
                a[j][m + 1] = -f[i + 1][j] / 4.0 - 1;
            }
            a[m][m] = -2.0 / 3;
            a[m][m - 1] = 1.0 / 3;
            a[m][m + 1] = -f[i + 1][m] / 3.0 - 1;
        }//构造矩阵 
        Gauss();//高斯消元 
        for (int j = 1; j <= m; ++j) f[i][j] = a[j][m + 1];//赋值求出的解 
    }
    printf("%.10lf\n", f[x][y]);
    return 0;
}
```

---

## 作者：lytqwq (赞：1)


[高斯消元](https://www.luogu.com.cn/problem/P3389)

直接高斯消元 ，时间复杂度 $O(n^6)$

发现对于行从下到上是无后效性的，我们每次高斯消元一行就行了 ，时间复杂度 $O(n^4)$

第 $i$ 行 $(1\le i<n)$：
$$
\left[ \begin{matrix} 
2 & -1 & 0 & 0 &  0 & f_{i+1,1}+3 \\ 
-1 & 3 & -1 & 0 & 0 & f_{i+1,2}+4 \\ 
0 & -1 & 3 & -1 & 0 & f_{i+1,3}+4 \\ 
0 & 0 & -1 & 3 & -1 & f_{i+1,4}+4 \\
0 & 0 & 0 & -1 & 2 & f_{i+1,5}+3 
\end{matrix} \right]
$$




事实上，这个方程组很简单很有特色，我们在 [高斯消元](https://www.luogu.com.cn/problem/solution/P3389) 时一些东西不需要枚举，因为都是 $0$ 

可以 $O(n)$ 解出来

一共 $n$ 行，总复杂度 $O(n^2)$ 

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
int n,m,x,y;
double a[N][N],f[N][N];
int main(){
	scanf("%d%d",&n,&m);
	scanf("%d%d",&x,&y);
	for(int i=1;i<=m;i++)f[n][i]=0;
	for(int o=n-1;o>=1;o--){
		
		for(int i=1;i<=m;i++){
		a[i][i]=3;a[i][i-1]=a[i][i+1]=-1;
		if(i==1)a[i][i]--;
		if(i==m)a[i][i]--;
		a[i][m+1]=4+f[o+1][i];
		if(i==1)a[i][m+1]--;
		if(i==m)a[i][m+1]--;
	}
	for(int i=1;i<=m;i++){
		if(a[i][i]==0){
			printf("No Solution\n");
			return 0;
		}
		else{
			if(i!=m)a[i][i+1]=a[i][i+1]/a[i][i];
			a[i][m+1]=a[i][m+1]/a[i][i];
			a[i][i]=1;
			if(i!=m){
				a[i+1][i+1]=a[i+1][i+1]-a[i+1][i]*a[i][i+1];
				a[i+1][m+1]=a[i+1][m+1]-a[i+1][i]*a[i][m+1];
				a[i+1][i]=0;
			}
		}
	}
	for(int i=m;i>=1;i--){
		f[o][i]=a[i][m+1];
		if(i!=1)a[i-1][m+1]-=a[i-1][i]*f[o][i];
	}
	}
	printf("%.4lf\n",f[x][y]);
	return 0;
}
```



---

## 作者：Yt_pY (赞：1)

（此题中高斯消元是作为工具使用的，非常好）

这道题经过一定分析后可以发现：  
一个点不会走到之前的行中，这就满足了行的无后效性（dp）

设 $f[i][j]$ 表示机器人从 $(i,j)$ 走到最后一行，所需移动次数的期望。

考虑从最后一行向上递推，列出状态转移方程：

1. $j=1$，$f[i,j]=\frac{1}{3}(f[i,1]+f[i,2]+f[i+1,1])+1$
2. $j=m$，$f[i,M]=\frac{1}{3}(f[i,M]+f[i,M-1]+f[i+1,M])+1$
3. $j$ 是其他的，$f[i,j]=\frac{1}{4}(f[i,j]+f[i,j-1]+f[i,j+1]+f[i+1,j])+1$

初值：$f[N,j]=0$

观察这个状态转移，我们假设 $f[i+1,j]$ 是已知的，考虑怎样计算出 $f[i,j]$ 。

可以将这个状态转移方程改变一下：
$$f[i,j]=\frac{1}{4}(f[i,j]+f[i,j-1]+f[i,j+1]+f[i+1,j])+1$$
$$\frac{1}{4}f[i,j-1]-\frac{3}{4}f[i,j]+\frac{1}{4}f[i,j+1]=-\frac{1}{4}f[i+1,M]-1$$

定睛一看，这不就是高斯消元的形式吗？~~秒了~~

不过，问题还没有解决，这个方程怎么在 $\Theta(M)$ 时间内解出来呢？

现在的矩阵是这个样子（ $x$ 只是占位，无实际意义）：
$$
\begin{bmatrix}
x&x&0&0&0\\
x&x&x&0&0\\
0&x&x&x&0\\
0&0&x&x&x\\
0&0&0&x&x\\
\end{bmatrix}
$$

从上至下消一个未知数：

$$
\begin{bmatrix}
x&x&0&0&0\\
0&x&x&0&0\\
0&0&x&x&0\\
0&0&0&x&x\\
0&0&0&0&x\\
\end{bmatrix}
$$

再从下至上解出方程：

$$
\begin{bmatrix}
x&0&0&0&0\\
0&x&0&0&0\\
0&0&x&0&0\\
0&0&0&x&0\\
0&0&0&0&x\\
\end{bmatrix}
$$

差不多就是这个样子的。


------------

实在不行就看代码吧，有注释。

代码中的 $x$ 数组就是 $f$ ，为了表示方便，压成一维了。

代码：
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,r,c;
double a[1005][1005],x[1005];
int main()
{
	scanf("%d%d%d%d",&n,&m,&r,&c);
	if(m==1)//特判
	{
		printf("%d\n",(n-r)*2);
		return 0;
	}
    //初始x数组都是0，因为最后一行到最后一行步数是0
	for(int i=n-1;i>=r;i--)//算到第r行
	{
    	//现在有第i+1行的答案x数组
		for(int j=1;j<=m;j++)//给矩阵赋初值
		{
			if(j==1)
			{
				a[1][1]=-2.0/3;
				a[1][2]=1.0/3;
				a[1][m+1]=-1-1.0/3*x[1];//根据上面的转移方程不难推出
			}
			else if(j==m)
			{
				a[j][m-1]=1.0/3;
				a[j][m]=-2.0/3;
				a[j][m+1]=-1-1.0/3*x[m];
			}
			else
			{
				a[j][j-1]=a[j][j+1]=1.0/4;
				a[j][j]=-3.0/4;
				a[j][m+1]=-1-1.0/4*x[j];
			}
		}
		for(int j=1;j<=m;j++)//第一次消元
		{
			double r=a[j+1][j]/a[j][j];
			a[j+1][j]=0;
			a[j+1][j+1]-=r*a[j][j+1];
			a[j+1][m+1]-=r*a[j][m+1];
		}
		for(int j=m;j>=1;j--)//第二次消元
		{
			double r=a[j-1][j]/a[j][j];
			a[j-1][j]=0;
			a[j-1][m+1]-=r*a[j][m+1];
			x[j]=a[j][m+1]/a[j][j];//更新答案
		}
	}
	printf("%.4lf\n",x[c]);//输出第c列
	return 0;
}
```

---

## 作者：yingjz (赞：1)

小蒟蒻又来写题解啦。。。

考虑 `期望DP`, 设 $f[i][j]$ 表示从 $(i,j)$ 走到最后一行的期望步数，那么可以得到转移方程：

$f[i][j] = {1 \over 4}(f[i][j] + f[i+1][j] + f[i][j-1] + f[i][j+1]) (2 \leq j \leq m-1)$

$f[i][1] = {1 \over 3}(f[i][1] + f[i+1][1] + f[i][2])$

$f[i][m] = {1 \over 3}(f[i][m] + f[i+1][m] + f[i][m-1])$

这几个方程都是有后效性的，也就是是说，在同一行的状态会互相影响，我们很难决定先求出哪一个。

考虑解方程，同一行有 $m$ 个未知数，构成了 $m$ 个线性方程，可以对于每一行都用 `高斯消元` 解出 $f[i][j]$. 时间复杂度 $O(nm^3)$；但是这道题的方程比较特殊，系数矩阵大概是这样的：

$\begin{matrix} -{2\over 3} & {1\over 3} & 0 & 0 & 0\\ {1\over 4} & -{3\over 4} & {1\over 4} & 0 & 0 \\ 0 & {1\over 4} & -{3\over 4} & {1\over 4} & 0 \\ 0 & 0 & {1\over 4} & -{3\over 4} & {1\over 4} \\ 0 & 0 & 0 & {1\over 3} & -{2\over 3}\end{matrix} $

可以看到每一行最多只有 $3$ 个非零项，所以 `高斯消元` 只需要最多对 $3$ 项做消去操作就可以了，单次时间复杂度 $O(m)$，总时间 $O(nm)$.

最后需要注意这道题由于是 **CF** 的题所以有一个奇怪的数据 `m=1` 需要注意（此时答案就是 $2(n-x)$，手动解方程即可）


```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 1007, M = 1007; 
int n, m, x, y;
double f[N][M], mat[M][M];

int main() {
	scanf("%d%d", &n, &m);
	scanf("%d%d", &x, &y);
	if (m == 1) {
		printf("%.6lf\n", (n - x) * 2.0);
		return 0;
	}
	for (int j = 1; j <= m; ++j) f[n][j] = 0.0;
	for (int i = n - 1; i >= 1; --i) {
		mat[1][1] = -2.0/3.0; mat[1][2] = 1.0/3.0; mat[1][m + 1] = -1.0/3.0 * f[i + 1][1] - 1;
		mat[m][m] = -2.0/3.0; mat[m][m-1] = 1.0/3.0; mat[m][m + 1] = -1.0/3.0 * f[i + 1][m] - 1;
		for (int j = 2; j <= m - 1; ++j) {
			mat[j][j] = -3.0/4.0; mat[j][j - 1] = 1.0/4.0;
			mat[j][j + 1] = 1.0/4.0; mat[j][m + 1] = -1.0/4.0 * f[i + 1][j] - 1;
		} 
		//Gauss
		for (int j = 2; j <= m; ++j) {
			double div = mat[j][j - 1] / mat[j - 1][j - 1];
			mat[j][j - 1] -= div * mat[j - 1][j - 1];
			mat[j][j] -= div * mat[j - 1][j];
			mat[j][m + 1] -= div * mat[j - 1][m + 1];
		}
		f[i][m] = mat[m][m + 1] / mat[m][m];
		for (int j = m - 1; j >= 1; --j) {
			mat[j][m + 1] -= mat[j][j + 1] * f[i][j + 1];
			f[i][j] = mat[j][m + 1] / mat[j][j];
		}
	}
	printf("%.6lf\n", f[x][y]);
	return 0;
}
```

---

