# [ABC134F] Permutation Oddness

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc134/tasks/abc134_f

{$ 1,\ 2,\ ...,\ n $} の順列 $ p $ = {$ p_1,\ p_2,\ ...,\ p_n $} の「奇妙さ」を $ \sum_{i\ =\ 1}^n\ |i\ -\ p_i| $ と定義します。

奇妙さが $ k $ であるような {$ 1,\ 2,\ ...,\ n $} の順列の個数を $ 10^9+7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ n\ \leq\ 50 $
- $ 0\ \leq\ k\ \leq\ n^2 $

### Sample Explanation 1

{$ 1,\ 2,\ 3 $} の順列は $ 6 $ 個存在します。その中で奇妙さが $ 2 $ であるのは {$ 2,\ 1,\ 3 $} と {$ 1,\ 3,\ 2 $} の $ 2 $ つです。

## 样例 #1

### 输入

```
3 2```

### 输出

```
2```

## 样例 #2

### 输入

```
39 14```

### 输出

```
74764168```

# 题解

## 作者：Demeanor_Roy (赞：50)

- [原题链接](https://www.luogu.com.cn/problem/AT_abc134_f)

------------

私认为本题目前的大众做法，即：将题目转化成匹配问题，绝对值贡献从跨越水平线的角度计算。它虽然能很好的让读者理解这么做是对的，但不能说清楚为什么要这样做。

而对于这类贡献是绝对值之和的题目，应该是有更系统化的切入方式：拆贡献。

考虑每个元素对怪异度的贡献，显然对于元素 $x$（这里不区分是位置还是值），若最后其作为**小数**，贡献为 $-x$，反之为 $x$。换句话说，每个数为哪种贡献只与另外元素的相对大小有关。

从小到大考虑，不难发现我们很难做到实时匹配算贡献。但延续上面的思路，我们实时决定当前元素是与前面的数配对还是与后面的数配对是容易的，而这已经足够。因为这样我们就可以通过**提前计算贡献的方式**得到怪异度的变化。

不妨完善这个思路，我们发现从前往后考虑到第 $i$ 个元素时，我们需要记录的无非是在它前面决定与后面的数匹配的元素数量，以及当前怪异度。值得注意的是，因为**待匹配的位置和值数量一定相同**，所以我们可以一起记录，于是用 $f_{i,j,k}$ 表示以上状态，我们考虑转移：

- $i$ 号位置与元素自己匹配：$f(i,j,k) \leftarrow f(i-1,j,k)$

- 二者都与后面的数匹配：$f(i,j,k) \leftarrow f(i-1,j-1,k + 2i)$

- 二者都与前面的数匹配：$f(i,j,k) \leftarrow f(i-1,j+1,k - 2i) \times (j+1)^2$

- 二者有一个与前面匹配，有一个与后面匹配：$f(i,j,k) \leftarrow f(i-1,j,k) \times 2j$

值得注意的是，在 dp 转移中，转移系数代表了具体与当前决策中哪个元素匹配（最后一项的 $2$ 是区分位置和值），读者应当不难理解。

一个细节是第三维应当包含负数，且令 $m$ 表示怪异度，上下界不应该是 $[-m,m]$ 而是 $[-n^2,n^2]$，这均是因为在转移过程中怪异度可增可减。

我认为这应该是本题较为自然的解法。如果喜欢请点赞让更多人看见。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=55,mod=1e9+7;
int n,m,f[N][N][N*N*2];
inline void add(int &x,int y){x+=y;x-=(x>=mod)*mod;}
int main()
{
	scanf("%d%d",&n,&m);
	f[0][0][N*N]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=i;j++)
			for(int k=-n*n;k<=n*n;k++)
			{
				add(f[i][j][k+N*N],f[i-1][j][k+N*N]);
				if(j) add(f[i][j][k+N*N],2ll*f[i-1][j][k+N*N]*j%mod);							
				if(j&&k+i*2<=n*n) add(f[i][j][k+N*N],f[i-1][j-1][k+i*2+N*N]);
				if(j<i-1&&k-i*2>=-n*n) add(f[i][j][k+N*N],1ll*(j+1)*(j+1)*f[i-1][j+1][k-i*2+N*N]%mod);
			}
	printf("%d",f[n][0][m+N*N]);
	return 0;
}
```

---

## 作者：Tan_Wei_Ye (赞：25)

## 说在前面
1. 本文部分内容参考了[这篇博客](http://kazunelab.net/contest/2019/07/20/abc134/)和[这篇博客](https://www.cnblogs.com/Patt/p/11763353.html/)。
如有错误请指出。
2. 为了方便起见，本篇博客中的 $m$ 为题目给出的 $k$ 。

## 正题
我们可以把题意转换成球和盒子的配对：

左边的圆形代表球以及球的编号，右边的方形代表盒子，方形右边的数字是盒子的编号。箭头表示将数字放入盒子中。将 $P_i$ 看成数字 $i$ 所在的盒子的编号。
![](https://gitee.com/zjsdut/pic_bed/raw/master/abc134f_permutation_oddness.svg)
比如上图的 $P$ 为 $\{4,3,5,1,2\}$。

在每个球之间画一条水平的线，那么这个排列的怪异度就是“球和盒子的连线”与“水平线”的“交点个数”。

可以把往盒子里放数字的过程看作下述 $n$ 阶段决策过程。也就是说，在第 $i$ 个阶段考虑球 $i$ 和编号为 $i$ 的盒子如何处置。

那么我们可以写出以下状态：

$dp[i][j][k]$ 表示考虑前 $i$ 个球和盒子，还有 $j$ 个球和盒子没有配对，当前的怪异度为 $k$ 。
答案状态为：$dp[n][0][m]$。

然后给出状态转移方程，我们在下面解释：

$$
\begin{aligned}
dp[i][j][k] &= (2\times  j+1)\times dp[i-1][j][k-2\times j] \\
			&+ (j+1)\times(j+1)\times dp[i-1][j+1][k-2\times j]\\ 
         &+ dp[i-1][j-1][k-2\times j]
\end{aligned}
$$

我们把一次配对称为在一个球和盒子之间连线。

第一行表示进行了 $1$ 次配对，那么有 $3$ 种情况
1. 第 $i$ 个球与没配对的 $j$ 个盒子配对 ，共有 $j$ 种。
2. 第 $i$ 个盒子与没配对的 $j$ 个球配对 ，共有 $j$ 种。
3. 第 $i$ 个球与第 $i$ 个盒子配对 ，共有 $1$ 种。

根据加法原理，共有 $2 \times j + 1$ 种方法。

第二行表示进行了 $2$ 次配对，那么有 $2$ 种情况
1. 第 $i$ 个球与没配对的 $j+1$ 个盒子配对 ，共有 $j+1$ 种。
2. 第 $i$ 个盒子与没配对的 $j+1$ 个球配对 ，共有 $j+1$ 种。


根据乘法原理，共有 $(j +1) \times (j + 1)$ 种方法。

第三行表示进行了 $0$ 次配对，那么有 $1$ 种情况， $1$ 种方法。

现在唯一的问题，也是当时我自己做的时候困扰我好久的问题：为什么 $k$ 要从 $k-2\times j$ 转移过来。

我们可以这样想：

因为最终的答案肯定是所有球和盒子都配对完了的，所以状态中的 $j$ 可以有另一种解释: $1 \sim i$ 这些球中有 $j$ 个要放到编号大于 $i$ 的盒子里。

每次转移时，因为我们把第 $i$ 个盒子进行了配对，所以未配对的球连的线会下移一行，会导致多出 $2 \times j$ 个交点，举个例子：

![tj.png](https://i.loli.net/2021/05/14/Nm6EFak7hXreTLj.png)


------------

![tj2.png](https://i.loli.net/2021/05/14/hCE9mujIpryKgBs.png)

（交点从 $2$ 个变成了 $4$ 个，多了 $2$ 个，但还要算反着的，所以多了 $4$ 个）


其他应该没什么问题了。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=55;
const int mod=1e9+7;
int n,m;
int dp[N][N][N*N];
signed main()
{
	cin>>n>>m;
	if(m&1) return puts("0"),0;
	dp[0][0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=i;j++)
			for(int k=2*j;k<=m;k+=2)
			{
				dp[i][j][k]=((2*j+1)*dp[i-1][j][k-2*j]%mod
							+(j+1)*(j+1)*dp[i-1][j+1][k-2*j]%mod)%mod;
				if(j>=1) dp[i][j][k]=(dp[i][j][k]+dp[i-1][j-1][k-2*j])%mod;
			}
	cout<<dp[n][0][m];
}

```
------------
## 时间复杂度: $O(n^4)$


---

## 作者：Judgelight (赞：24)

# [ABC134F] Permutation Oddness

## 题面翻译

定义一个 $1 \sim n$ 的排列 $p$ 的「怪异度」为
$$\sum_{i=1}^n|p_i-i|$$
求「怪异度」为 $k$ 的 $1 \sim n$ 的排列数，答案对 $10^9+7$ 取模。

# 题解

妙妙的 DP 题，其实最难的是转化和状态设置，方程很好推。

## 1. 问题转化

粘了一下题面，看着清楚些

考虑转化题目，把题目中的 $p_i$ 和 $i$ 表示成球和盒子，球在左边摆一列，盒子在右边摆一列。如果 $p_i=x$，把左边的第 $i$ 个球和右边的第    $x$ 个盒子连起来。

如：若 $p_{114514}=1919810$，把左边的第 $114514$ 个球和右边的第     $1919810$ 个盒子连**红**线。

这样我们就把一个排列转化为了一个匹配数为 $n$ 的二分图。

现在一共有 $n$ 行，第 $i$ 行的第一个是球，第二个是盒子，在两行之间作一根黑直线。发现每根红线（球和盒子的连线）经过的黑线数量的总和就是怪异度。

如样例 $\lbrace 2,1,3 \rbrace$，指 $p_1=2,p_2=1,p_3=3$，化为下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/jjah7aiz.png)

画得丑见谅 ~~看不懂算了~~。

 $1$ 经过了 $1$ 根黑线，$2$ 经过了 $1$ 根黑线，$3$ 经过了 $0$ 根黑线，所以怪异度 $ = 1+1+0 = 2$。

## 2. 状态设置

那这样肯定用 DP 做。

设状态 $f_{i,j,k}$ 表示前 $i$ 行，有 $j$ 组**球和盒子**没有被连线（用二分图想，这里的意思是本来应该有 $i$ 个匹配，但是只有 $i-j$ 个，剩了 $j$ 个球和 $j$ 个盒子还没有匹配），然后当前的奇异度是 $k$ 的方案数。

那么答案就是 $f_{n,0,k}$（这里 $k$ 是它输入的第二个数），表示前 $n$ 个数，匹配完了，相当于未匹配数是 $0$ ，奇异度是 $k$ 的方案数。 

都看到这里了，是不是点个赞的说。

## 3. 状态转移

我们 $f_{i,j,k}$ 的方案数与 $f_{i-1,anything,anything}$ 的差距只在于第 $i$ 排的盒子和球的选择方案。可以根据这个来分类讨论，因为第 $i$ 排有两个物体，最多匹配两组，所以分类讨论匹配 $0,1,2$ 组的方案数。
#### 1. 只匹配一组

- 把第 $i$ 个球向前 $i-1$ 个盒子中未被连线的盒子连一条线，且第 $i$ 个盒子不动它的方案数，即为 $j \times f_{i-1,j,k-2j}$（乘了一个 $j$ 是因为可以选择没被选的 $j$ 个盒子中的任意一个，第二维是因为这次连了  $1$ 条边，$i$ 也多了 $1$，抵消了；第三维和下面的第三维都后面再解释，先看完分类）。

- 把第 $i$ 个盒子向前 $i-1$ 个球中未被连线的球连一条线，且第 $i$ 个球不动它的方案数，即为 $j \times f_{i-1,j,k-2j}$ （乘了一个 $j$ 是因为可以选择没被选的 $j$ 个球中的任意一个，第二维是因为这次连了 $1$ 条边，$i$ 也多了 $1$，抵消了）。

- 自己连自己的情况：单独讨论，显然是 $f_{i-1,j,k-2j}$。

#### 2. 匹配两组

- 由于要匹配两组，第 $i$ 个球和第 $i$ 个盒子显然就不能互相选了，所以选前面没被选过的就行，即 $(j+1)^2 \times f_{i-1,j+1,k-2j}$（第二维的 $j+1$，因为这次连了 $2$ 条边，$i$ 却只增加了 $1$，前面的 $(j+1)^2$ 意思就是第 $i$ 个球能选前面未被选的 $j+1$ 个盒子，第 $i$ 个盒子同理，然后这样连边是互不干扰的，所以用乘法乘起来）。

#### 3. 不匹配

- 直接就是 $f_{i-1,j+1,k-2j}$（第二维因为边数增加了 $0$， $i$ 却增加了 $1$）。

---

综上所述：

$$f_{i,j,k}=j \times f_{i-1,j,k-2j}+j \times f_{i-1,j,k-2j}+f_{i-1,j,k-2j}+(j+1)^2 \times f_{i-1,j+1,k-2j}+f_{i-1,j+1,k-2j}$$

合并同类项：

$$f_{i,j,k}=(2j+1) \times f_{i-1,j,k-2j}+(j+1)^2 \times f_{i-1,j+1,k-2j}+f_{i-1,j+1,k-2j}$$

## 4. 第三维转移的解释

比如现在有 $f_{i,j,k}$，这里的 $j$ 也有另一种表示：有 $j$ 个球和 $j$ 个盒子要连线到 $i+1 \sim n$ 中去了。

因为最后一定是有 $n$ 个匹配，这 $j$ 个球和 $j$ 个盒子又不往 $1 \sim i$ 中的元素连，那就只能往后面连了。

那么这些球和盒子连的对象行数每多 $1$，就多经过 $1$ 根黑线，奇异度就多 $1$。

本来它们是有可能连到第 $i$ 行的，结果我们把这行的连接确定了，它们的连线对象就只好整体向下移动一行了，这 $j$ 个球和 $j$ 个盒子就让奇异度多了 $j+j=2j$，算回去就是 $k-2j$。

## 5. AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 59
using namespace std;
const int mod=1e9+7;
int n,magic,f[N][N][N*N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>magic;
	f[0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			for(int k=j*2;k<=magic;k++){
				if(j>=1){
					f[i][j][k]=(f[i-1][j-1][k-j*2]+f[i-1][j][k-j*2]*(j*2+1)%mod+f[i-1][j+1][k-j*2]*(j+1)%mod*(j+1)%mod)%mod;
				}
				else f[i][j][k]=(f[i-1][j][k-j*2]*(j*2+1)%mod+f[i-1][j+1][k-j*2]*(j+1)%mod*(j+1)%mod)%mod;
			}
		}
	}
	cout<<f[n][0][magic];
	return 0;
}
```

---

## 作者：EnofTaiPeople (赞：9)

本题的巧妙之处在于将绝对值转换成两点距离，然后发现，对于所有的配对 $(l_1,r_1),(l_2,r_2),l_1,l_2\le L<r_1,r_2$，交换 $l_1,l_2$ 答案不变。

于是可以将 $1\sim n$ 依次加入，在加入时考虑会不会与之前的产生配对。

具体地，设 `f[x][l][r][sm]` 表示考虑了前 $x$ 个数，$1\sim x$ 在 $i$ 中保留了 $l$ 个，$p_i$ 中保留了 $r$ 个，之前的答案以及所有保留的数到 $x$ 的距离总和为 $sm$，直接 $\text{dp}$ 可以做到 $O(n^3k)$，可以通过。

但是，并不是没有优化的余地，发现剩余的 $i$ 和 $p_i$，由于已经配对的 $i$ 和 $p_i$ 相等，故不同的也一样，于是可以压掉一位，这样复杂度为 $O(n^2k)$。

代码中有注释：
```cpp
#include<icecream>
using namespace std;
const int N=55,M=1e9+7;
void add(int &x,int y){偷懒开函数
    if((x+=y)>=M)x-=M;
}using ll=long long;
int f[N][N][N*N],n,k,ans;
int main(){
    scanf("%d%d",&n,&k);
    f[0][0][0]=1;
    int i,j,l,r;
    for(i=1;i<=n;++i){
        for(j=1;j<=i;++j)
            for(l=(j-1)*2;l<=k;++l)如果 i 和 (pi=i) 都不配对，就会增加一组没有配对的，距离为 0
                add(f[i][j][l],f[i-1][j-1][l-(j-1)*2]);
        for(j=0;j<i;++j){
            for(l=j*2;l<=k;++l)i 和 pi 会凑出一组
                add(f[i][j][l],ll(j+j+1)*f[i-1][j][l-j*2]%M);
            for(l=(j+1)*2;l<=k;++l)i 和 (pi=i) 均与之前组成一组
                add(f[i][j][l],ll(j+1)*(j+1)*f[i-1][j+1][l-(j+1)*2]%M);
        }
    }
    printf("%d\n",f[n][0][k]);dp 到最后，没有剩余的，sum=k！
    return 0;
}
```

---

## 作者：Soulist (赞：7)


将绝对值拆开，如果 $i$ 对于答案的贡献为 $-1$ 那么记为 L，否则记为 R，将 $p$ 与数列 $\{1,2...n\}$ 分别当作两个排列，那么问题即在两者上连边，满足权值和为 $k$ 的合法方案数。

我们不考虑具体的连边关系，只考虑每个点往前连边还是往后连边，然后将这两个 $\{1\sim n\}$ 的数列写在一起，变成 $\{1,1,2,2...n,n\}$，那么某个点如果是 L，那么它可以向之前的点中位置的奇偶性与其不同的 R 连边。

于是问题变为给定数列 $\{1,1,2,2...n,n\}$，给每个点赋予一个权值 L/R，如果为 L 那么可以向前面的一个 R 连边，一个数列的权值定义为 R 的权值和减去 L 的权值和，求满足权值为 $k$ 的 L/R 数列以及连边方案数。

显然每个 L 的出现都必须伴随着连边，事实上我们只关乎前面的数列中剩余的奇数位与偶数位的 R 的数量，这样直接 dp 就可以做到 $\mathcal O(n^5)$ 了，我们肯定要压缩状态，$k$ 的维度显然无法压缩，那么只能将奇偶数位上的 R 的数量压缩掉一个。

我们注意到一个性质，假设每次决策将 $12,34$ 等位置一起处理，那么设奇数位上剩余的 R 数量为 $j$，当前在第 $i$ 位，那么当前匹配的 L,R 数量必然为 $(i/2-j)$，所以偶数位上会剩余且仅剩余 $i/2-(i/2-j)=j$ 个，换而言之两者的数量时刻保持相同。

所以就可以压缩掉一个维度了，当然更方便的处理方法是记录一下奇数位上的 R 的数量然后统计一下偶数位上与其的数量差，容易注意到差值必然是 $-1,0,1$

---

## 作者：wyw666 (赞：4)

[传送门](https://www.luogu.com.cn/problem/AT_abc134_f)

建议先看其他题解，看不懂再来看我的QWQ，仅作补充或解释。

显然是一个 $n^4$ 的 DP，转换成小球放进盒子里的这样一个二分图模型之后，可以设计状态 $dp[i][j][k]$ 表示前 $i$ 个盒子里有 $j$ 个是空的且当前怪异度为 $k$  的情况下的总方案数。

考虑转移。对于编号为 $i+1$ 的盒子和小球，有以下几种情况：

1. 这两个互相配对。

2. 当前盒子装之前没配对的小球，当前小球暂且保留。

3. 当前盒子暂且保留，当前小球装入之前没配对的盒子。

4. 当前盒子装之前没配对的小球，当前小球装入之前没配对的盒子。

5. 当前盒子和小球都暂且保留。

然后就会出现当前最难以解决的一个问题：

**只知道之前有几个盒子没配对，怎么知道是哪几个？如果不知道怎么转移 k？**

显然，如果 $k$ 只表示已配对的盒子和小球的怪异度，是无法实现接下来的转移的，我们还需要计算没有匹配的盒子小球对 $k$ 的贡献。

但是，**尚未匹配，怎么知道贡献？**

我想提及一个大多数题解都一笔带过的方法：**增量贡献**。

假设 1 号盒子和 1 号小球不匹配，那么 1 号盒子以后可能与其他号小球匹配，1 号小球同理。

在所有的匹配可能中，因为 1 号盒子和 1 号小球不匹配而对整体怪异度造成的**最小**贡献是 2，即 1 号盒子与 2 号小球匹配，2 号盒子与 1 号小球匹配的情况。

我们可以先把这个大小为 2 的最小贡献保存下来，即**暂且**认为最终匹配情况就是上文所说的那种情况，如果情况有变，就再更新贡献。

如果真是假设的情况，那么匹配时不需要再计算贡献，因为之前已经算好了。

什么时候“情况有变”？那当然是 2 号盒子不跟 1 号小球配对，或者 2 号小球不跟 1 号盒子配对啊。

如果 2 号盒子不跟 1 号小球配对而跟 2 号小球配对，我们就又**暂且**认为 1 号小球会跟 3 号小球配对，这时贡献只会增加 1，对 1 号盒子也同理。

如果 2 号盒子既不跟 1 号小球配对，也不跟 2 号小球配对，那我们就也**暂且**认为 1,2 号盒子都与 3 号小球配对，此时 2 号盒子产生 1 的贡献，1 号盒子的贡献加 1。

也就是说，对于 $dp[i][j][k]$，我们可以把它的定义更新为：前 $i$ 个盒子，其中有 $j$ 个**暂且**认为与 $i+1$ 号盒子/小球配对，其他都已配对，且当前怪异度为 $k$ 的情况下的总方案数。

这样是不是好转移多了？来试试，对于上面的几种情况：

1. 这一对盒子和小球不产生贡献，但是之前的所有假设作废，要重新**暂且**认为之前没配对的盒子/小球与编号为 $i+2$ 的小球/盒子配对，贡献会在原来的基础上增加 $2\times j$。

配个图说明，左边是盒子右边是小球，假设虚线是假设的边，实线是确定的边，红色虚线是作废的假设，当前考虑到第 3 组盒子小球。

如果 1 号、2 号小球和盒子都不匹配，是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/y3vgy4fl.png)

他们都暂且认为与 3 号盒子/小球匹配，此时贡献为 6。

转移后，是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/gaullxjj.png)


2. 之前没配对的盒子的假设全部作废，除了选中的小球，其他之前没配对的小球的假设也作废，并且新增一个当前小球的假设。综合起来，贡献还是比之前多了 $2\times j$。

![](https://cdn.luogu.com.cn/upload/image_hosting/8canbyk7.png)

3. 由对称性可知，其实和 2 是一样的，图不配了。

4. $j-1$ 个盒子和小球的假设作废，贡献多 $2\times(j-1)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/4ejvp06m.png)

5. 所有盒子和小球的假设都作废，并且新增一对假设，贡献多 $2\times(j+1)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/jq9hr4ug.png)

代码很容易就写出来了，记得在转移的时候乘上可以选择的种类数。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll P = 1000000007;
ll n, K, dp[55][55][55 * 55];
void add(ll& x, ll y) {
	x = (x + y) % P;
}
int main() {
	cin >> n >> K;
	dp[1][0][0] = dp[1][1][2] = 1;
	for (ll i = 1; i < n; i++) {
		for (ll j = 0; j <= i; j++) {
			for (ll k = 0; k <= n * n; k++) {
				add(dp[i + 1][j][k + 2 * j], dp[i][j][k]); // 情况 1
				if (j) {
					add(dp[i + 1][j][k + 2 * j], j * dp[i][j][k] * 2); // 情况 2,3
					add(dp[i + 1][j - 1][k + 2 * (j - 1)], j * j * dp[i][j][k]); // 情况 4
				}
				add(dp[i + 1][j + 1][k + 2 * (j + 1)], dp[i][j][k]); // 情况 5
			}
		}
	}
	cout << dp[n][0][K] << endl;
	return 0;
}
```


---

## 作者：wchengk09 (赞：4)

本题解是对 @Demeanor_Roy 大佬的题解的补充，主要回答了许多人关于此题的一个疑问：

**为什么本题可以不用状压DP？**

如果你之前做过排列有关的 `DP` 题，你会发现，许多排列相关的题都需要记录一个集合 $S$ ，表示当前哪些元素已经选过了，然后使用状压 `DP` 求解。（比如哈密尔顿回路）

但是本题的数据范围是 $n\leq 50$ ，$O(2^n)$ 的状压 `DP` 显然会 `TLE` 。为什么本题可以不用状压呢？

仔细观察一下本题怪异度的式子：

$$\sum_{i=1}^n |p_i-i|$$

发现绝对值不是很好做，于是考虑拆绝对值：

- 如果 $i\leq p_i$ （即 @Demeanor_Roy 的题解中说的“作为小数”），则这一项产生的贡献为 $p_i-i$ 。
- 如果 $i>p_i$，则这一项产生的贡献为 $i-p_i$ 。

我们可以将这个贡献分为两部分，一部分是 $\pm i$ ，一部分是 $\pm p_i$ 。我们注意到一个很关键的性质：**不论 $i$ 和谁匹配**（即 $i$ 这个位置上的数是几），**$i$ 这个位置对答案产生的贡献永远是 $\pm i$ ；无论 $p_i$ 和谁匹配，$p_i$ 对答案产生的贡献永远是 $\pm p_i$ 。**

比如，我们让 $1$ 这个位置和 $3$ 这个值匹配（即 $p_1=3$ ），那么 $1$ 对答案产生的贡献就是 $-1$ ；如果我们让 $1$ 和 $4$ 匹配，$1$ 产生的贡献同样是 $-1$ ，因此与 $3$ 匹配和与 $4$ 匹配没什么区别，可以合并为一种情况。

而哈密尔顿回路则不同，$i\rightarrow j$ 和 $i\rightarrow k$ 是两条不同的路径，它们的边权不一样，产生的贡献也不一样，因此不能归为一种情况。

既然本题中，一个点产生的贡献只和它与 **它匹配的元素的大小** 有关，那么我们只需要记录它 **前面（比它小的）有多少个未被匹配** 的数，就可以知道它能否匹配比它小/大的数了。

而哈密尔顿回路中，一个点产生的贡献与它匹配的点有关。这时匹配不同的点就有不同的答案，就不能简单地记录个数，而是要记录一个集合 $S$ ，表示所有未被选过的点。

综上所述，我认为本题是一道绝世好题，因为它揭示了优化 `DP` 的一种重要方法：**减少不必要的信息，将相同的情况进行合并，来优化复杂度** 。

如果本题按照大众做法，将绝对值转化为与水平线的交点个数，很难解释为什么这题可以不用状压 `DP` 。而按照 @Demeanor_Roy 的“拆贡献”思路，可以非常好地揭示此题的本质。

关于状态的设定和状态转移方程，@Demeanor_Roy 大佬的题解里已经说得很清楚了，故本文不再赘述。

最后附上本题的 `AC` 代码：（**注意取模**）

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;
const int MAXN = 55;
int n,k;
int dp[MAXN][MAXN][MAXN * MAXN * 2];

int main(){
    scanf("%d%d",&n,&k);
    dp[0][0][n * n] = 1;
    for (int i = 1;i <= n;i ++){
        for (int j = 0;j <= i;j ++)
            for (int k = 0;k <= (n * n) << 1;k ++){
                dp[i][j][k] = (ll)(2 * j + 1) * dp[i - 1][j][k] % MOD;
                if (j > 0)(dp[i][j][k] += dp[i - 1][j - 1][k + (i << 1)]) %= MOD;
                if (j + 1 <= i - 1 && k >= (i << 1))(dp[i][j][k] += (ll)dp[i - 1][j + 1][k - (i << 1)] * (j + 1) % MOD * (j + 1) % MOD) %= MOD;
            }
    }
    printf("%d",dp[n][0][k + n * n]);
    return 0;
}
```

---

## 作者：Feyn (赞：4)

比较妙的题。

首先把绝对值的柿子具象化成这样的形式：左边有 $n$ 个球，右边有 $n$ 个盒子；然后每个排列对应一个放球方案，球和盒之间连线，于是那个柿子的值等于这些线和相邻排之间水平线的交点个数。想到用 $f_{x,y,z}$ 代表前 $x$ 排，有 $y$ 对物品（意思是有 $2y$ 个物品没有在前 $x$ 排中配对，不一定是恰好 $y$ 排）还没连线，且目前交点个数是 $z$ 的方案数。

考虑当前这根水平线会产生多少的贡献。有个显然的结论是说 $z$ 这一维其实和第 $x+1$ 排的决策没有关系，因为跨越该水平线的线段肯定满足一个点在水平线上一个点在水平线下。于是 $z$ 这一维的变化量肯定是 $z+2y$，所以唯一需要讨论的就是 $y$ 这一维的变化。

自然以第 $x+1$ 行的决策为基础分类讨论。如果自我消耗，显然失配数不变，系数为 $1$。如果一个物品往回连，失配数显然也不变，系数是 $2y$（事实上上面两种情况可以归成一类）。如果两个物品都往回连，失配数减一，系数是 $y^2$；如果两个物品都不连，失配数加一，系数是 $1$。正常转移即可更新答案即可。复杂度 $O(N^4)$。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
const int N=60;
const int mod=1e9+7;
using namespace std;
inline void read(int &wh){
	wh=0;char w=getchar();int f=1;
	while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
	while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
	wh*=f;return;
}
inline void add(int &s1,int s2){
	s1=(s1+s2)%mod;
}

int m,n,f[N][N][N*N];

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);read(n);f[0][0][0]=1;
	for(int x=0;x<m;x++){
		for(int y=0;y<=x;y++){
			for(int z=0;z<=n;z++){
				int now=f[x][y][z];
				add(f[x+1][y][z+2*y],now*(2*y+1));
				add(f[x+1][y-1][z+2*y],now*y*y);
				add(f[x+1][y+1][z+2*y],now);
			}
		}
	}
	printf("%lld\n",f[m][0][n]);
	
	return 0;
}
```

---

## 作者：masterhuang (赞：3)

同步于[博客园](https://www.cnblogs.com/HaHeHyt/p/17426148.html)。

[$\text{link}$](https://www.luogu.com.cn/problem/AT_abc134_f)。难想的 $\texttt{dp}$。下面用 $m$ 来表示题目中的 $k$，因为 $\texttt{dp}$ 时会用到 $k$。

我们把左侧放 $n$ 个球，右侧放 $n$ 个箱子，则 $|i-p_i|$ 等于第 $i$ 个球与第 $p_i$ 个盒子的连线（下面记作 $i\to p_i$）与**水平线**（两球中间与两箱子中间的连线）的交点。画个图解释一下：

![](https://i.imgtg.com/2023/05/23/OaxdZp.png)（左边是球，右边是箱子，绿色是 $i\to p_i$ 的连线，红色是**水平线**，黑圈是交点）

下面设 $f_{i,j,k}$ 表示考虑第 $i$ 个球以前水平线对怪异度的**贡献**，这时还有 $j$ 个球和盒子没有配对，当前的怪异度为 $k$ 的方案数。

为了好转移，我们把**水平线对怪异度的贡献**这样定义：如果统计到了某条水平线，这时还有 $j$ 个球和盒子没有配对，则水平线对答案的贡献为 $2j$。

因为这时 $j$ 个球会往后连线，经过这个水平线，有 $j$ 的贡献。$j$ 个盒子会往后连线，经过这个水平线，有 $j$ 的贡献。所以贡献为 $2j$。而且最终的答案就是 $f_{n,0,m}$。初值为 $f_{0,0,0}=1$。

先亮一下转移：$f_{i,j,k}=f_{i-1,j-1,k-2j}+(2j+1)f_{i-1,j,k-2j}+(j+1)^2f_{i-1,j+1,k-2j}$。

下面解释一下等号右边的 $3$ 个加数。设做到 $i-1$ 时未匹配的个数为 $J$。 

1. 如果第 $i$ 个球和第 $i$ 个盒子**啥都不做**的话，此时有一种可能，且 $J=j-1$。所以方案数为 $f_{i-1,j-1,k-2j}$.
2. 如果第 $i$ 个球和第 $i$ 个盒子**恰有一个**和之前 $J$ 个未匹配的盒子（或球）匹配，那么此时有 $2j$ 种可能，且 $J=j$。所以方案数为 $2jf_{i-1,j,k-2j}$.
如果第 $i$ 个球和第 $i$ 个盒子之间连线，则此时有一种可能，方案数也为 $f_{i-1,j,k-2j}$，所以第二种情况共贡献了 $(2j+1)f_{i-1,j,k-2j}$ 的方案数。
3. 如果第 $i$ 个球和第 $i$ 个盒子**都**和之前 $J$ 个未匹配的盒子（或球）匹配，那么此时有 $J^2$ 种可能，且 $J=j+1$。所以方案数为 $(j+1)^2f_{i-1,j+1,k-2j}$.

直接按此 $\texttt{dp}$ 即可，注意若枚举到 $j=0$ 时不能有情况 $1$，要特判一下。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=55,M=2505,mod=1e9+7;
int n,m,f[N][N][M];
int main()
{
	scanf("%d%d",&n,&m);if(m&1) return 0*puts("0");f[0][0][0]=1;
	for(int i=1;i<=n;i++) for(int j=0;j<=i;j++) for(int k=2*j;k<=m;k+=2)
		f[i][j][k]=(1ll*(j+1)*(j+1)*f[i-1][j+1][k-2*j]+1ll*(2*j+1)*f[i-1][j][k-2*j]+(j?f[i-1][j-1][k-2*j]:0))%mod;
	printf("%d",f[n][0][m]);
	return 0;
}
```

---

## 作者：RioBlu (赞：2)

首先可以先把题目转化成小球放小盒子里面

根据曾经打模拟赛的经验，我们不妨逐位逐位的来看小盒 $i$ 和小球 $i$ 怎么摆，如果摆不了，先留着，以后再摆

为了表述，不妨把小球放入小盒认为一种**匹配**

那么就可以设计 $dp_{i,j,k}$ 表示前 $i$ 个 小球 放前 $i$ 个 小盒 ，有 $j$ 个 小球 和 $j$ 个 小盒 还没匹配，**已经被处理的** 奇怪度为 $k$ 有多少情况

什么叫已经被处理？和未匹配的小球小盒差不多，但也有不同，看下去就懂了

如果我把 小球 $i$ 和 小盒 $i$ 先轮空（也就是 $i$ 小球小盒 不和前 $i$ 个小球小盒匹配），看影响，首先这些没摆的小球小盒一定只能和 $i$ 以后的小盒小球匹配，那么显然，那些未摆的小球小盒与 $i$ 只能和 $i$ 以后的小球小盒匹配，肯定有 $1$ 点差距，我们把它处理了，就有 $ j\times 2 +2$ 的奇怪度被处理了

![](https://cdn.luogu.com.cn/upload/image_hosting/tjkapgmj.png)

可以看到未摆的和 $i$ 与 $i$ 以后的小球小盒一定有差距 $1$ ，强行把前面的小盒小球都加一，这样我们就处理了一部分奇怪度

$dp_{i,j,k} \to dp_{i+1,j+1,k+(j \times 2+2)}$

还有转移，①小球 $i$ 和小盒 $i$ 匹配，②小球 $i$ 和未匹配的 $j$ 个小盒匹配，③小盒 $i$ 和 未匹配的 $j$ 个小球 匹配，有 $2j+1$ 种情况
 
同上道理

$(2j+1)dp_{i,j,k} \to dp_{i+1,j,k+(j \times 2)}$

还有转移，$i$ 小盒小球同时都有匹配

$j \times j \times dp_{i,j,k} \to dp_{i+1,j-1,k+(j\times 2-2)}$

但其实，最终答案上，一三情况数量是一样的（因为一个导致了 $j+1$ 一个导致了 $j-1$）

所以把 $dp$ 式子写成下面也能过：

* $dp_{i,j,k} \to dp_{i+1,j+1,k+(j \times 2)}$

* $(2j+1)dp_{i,j,k} \to dp_{i+1,j,k+(j \times 2)}$

* $j \times j \times dp_{i,j,k} \to dp_{i+1,j-1,k+(j\times 2)}$

```cpp

ll dp[55][55][2555],n,k;
void add(ll &x,ll y)
{
	x=(x+y)%p;
}
int main()
{
	in(n),in(k);
	dp[0][0][0]=1;
	for(int s=0;s<=n;s++)
	{
		for(int v=0;v<=n;v++)
		{
			for(int z=0;z<=k;z++)
			{
				add(dp[s+1][v+1][z+2*v+2],dp[s][v][z]);
				add(dp[s+1][v][z+2*v],dp[s][v][z]*(2*v+1));
				if(v)add(dp[s+1][v-1][z+2*v-2],dp[s][v][z]*v*v);
			}
		}
	}
	cout<<dp[n][0][k]<<endl;
}

```

---

## 作者：cwfxlh (赞：1)

# [AT_abc134_f](https://www.luogu.com.cn/problem/AT_abc134_f)          

考虑这个绝对值相当于 $p_i$ 与 $i$ 连线段，对线段长度求和。把下标和值分开来，变成一排球和一排盒子，相当于在球和盒子之间连线。绝对值的和转化为线段长度和之后，可以对于每一单位长度，计算覆盖这一单位长度的线段个数来求线段长度和。     

从左往右扫，令 $dp[i][j][p]$ 表示当前考虑了前 $i$ 列，目前还剩 $2j$ 对物件（$j$ 个盒子 $j$ 个球）要连到 $(i,n]$ 去，线段长度和为 $p$。转移考虑新的一列的匹配状态，有五种，分别是：本列内部球盒匹配，球盒均暂不匹配，球不匹配盒匹配，球匹配盒不匹配，球和盒都往前匹配。复杂度 $O(n^4)$。代码：     


```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 1000000007
using namespace std;
int n,k,dp[53][53][2503],ans;
void add(int &x,int y){x=(x+y)%MOD;return;}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	dp[0][0][0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			for(int u=0;u<=k;u++){
				if(dp[i][j][u]==0)continue;
				if(u+2*j>k)continue;
				add(dp[i+1][j][u+2*j],dp[i][j][u]);
				if(j>0)add(dp[i+1][j][u+2*j],2ll*j*dp[i][j][u]%MOD);
				add(dp[i+1][j+1][u+2*j],dp[i][j][u]);
				if(j>0)add(dp[i+1][j-1][u+2*j],(j*j%MOD)*dp[i][j][u]);
			}
		}
	}
	ans=dp[n][0][k];
	ans%=MOD;
	ans+=MOD;
	ans%=MOD;
	cout<<ans;
	return 0;
}
```


---

## 作者：白简 (赞：1)

### 题目大意
定义一个 $1 \sim n$ 的排列 $p$ 的「怪异度」为

$$\sum_{i=1}^n|p_i-i|$$

求「怪异度」为 $m$ 的 $1 \sim n$ 的排列数，答案对 $10^9+7$ 取模。
### 思路
考虑把 $p_i$ 和 $i$ 看作小球与盒子，方便题意理解。

考虑球与盒子的匹配。

假设球在左侧，盒子在右侧，他们构成了一个二分图。

从上到下顺着排列每组球与盒子，球与盒子之间有一条横线。

我们发现，假设第 $i$ 个盒子与 $j$ 个球相连，他们之间的距离为 $\left\lvert i - j \right\rvert$，他们产生的贡献相当于从 $i$ 到 $j$ 的连线穿过的横线的数量。

那么我们考虑状态如何设计，记 $dp_{i,j,k}$ 表示已经匹配了前 $i$ 行，有 $j$ 组球与盒子未匹配，怪异度为 $k$ 的方案数。

那么初始值为 $dp_{0,0,0}=1$，答案为 $dp_{n,0,m}$ 表示匹配了前 $i$ 行，没有球与盒子未匹配，怪异度为 $m$ 的方案数。

考虑转移，对于一行，有一个球和一个盒子，可以匹配 $0,1,2$ 组三种可能，那么就分这三种情况进行转移。
#### 匹配 $0$ 组
都不匹配的话，应该是 $dp_{i-1,j-1,k-2j}$。

考虑第二维为什么是从 $j-1$ 个未匹配组转移过来。

先考虑我们匹配 $1$ 组的情况，我们新加入了 $1$ 组，即第 $i$ 行的球与盒子，又匹配了 $1$ 组，那么新的没有匹配的组数没有发生变化，即第二维从 $j$ 转移到 $j$。

那么匹配 $2$ 组的情况，相比于匹配 $1$ 组的情况多匹配了一组，所以要从 $j + 1$ 转移到 $j$；同理，匹配 $0$ 组的情况就要从 $j-1$ 转移到 $j$。

再考虑第三维。原本前面那些没有被匹配的盒子与球是可能被匹配到第 $i$ 行及以后的，但是现在我们考虑的转移第 $i$ 行并没有匹配这 $j$ 组盒子与球。

那么这 $j$ 组盒子与球只能匹配到第 $i +1$ 行及以后，那么相等于我们前面的 $j$ 组球与盒子又需要多穿过一条横线，那么总共 $2j$ 个物品，就使得怪异值增加了 $2j$，所以从 $k-2j$ 转移过来。
#### 匹配 $1$ 组
将第 $i$ 个球与前面的 $i-1$ 行未被匹配的 $j$ 个盒子进行匹配，有 $j$ 种选择，每种选择的方案数为 $j \times dp_{i-1,j,k-2j}$。

用第 $i$ 个盒子去匹配球的方案数同理。

第 $i$ 个球连第 $i$ 个盒子的方案数单独处理，为 $dp_{i-1,j,k-2j}$。
#### 匹配 $2$ 组
如果要匹配两组，那么第 $i$ 行的球与盒子之间不能相互选择。

第 $i$ 行的球与前 $i-1$ 行的 $j+1$ 个未匹配的盒子转移过来，盒子同理，根据乘法原理，有 $(j + 1)^2dp_{i-1,j+1,k-2j}$ 种方案。 
### 状态转移方程
$$dp_{i,j,k}=j \times dp_{i-1,j,k-2j}+j \times dp_{i-1,j,k-2j}+dp_{i-1,j,k-2j}+(j+1)^2 \times dp_{i-1,j+1,k-2j}+dp_{i-1,j-1,k-2j}$$
### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long MainType;

const int N = 55;
const int Mod = 1e9 + 7;

int n,m;

MainType dp[N][N][N * N];
// dp[i][j][k]
// 对于前 i 组有 j 组没有配对，怪异度为 k 的方案数 

int main() {
#ifdef ONLINE_JUDGE == 1
    freopen("genshin.in","r",stdin);
    freopen("genshin.out","w",stdout);
#endif

    cin >> n >> m;

    dp[0][0][0] = 1;

    for(int i = 1;i <= n; i++) {
        for(int j = 0;j <= i; j++) {
            for(int k = j * 2;k <= m; k++) {
                if(j < 1)
                    dp[i][j][k] = (dp[i - 1][j + 1][k - j * 2] * (j + 1) % Mod * (j + 1) % Mod + dp[i - 1][j][k - j * 2] * (j * 2 + 1) % Mod) % Mod;
                else
                    dp[i][j][k] = (dp[i - 1][j + 1][k - j * 2] * (j + 1) % Mod * (j + 1) % Mod + dp[i - 1][j][k - j * 2] * (j * 2 + 1) % Mod + dp[i - 1][j - 1][k - j * 2] % Mod) % Mod;
            }
        }
    }

    cout << dp[n][0][m] % Mod;

#ifdef ONLINE_JUDGE == 1
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
```

---

## 作者：Expert_Dreamer (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc134_f)

[更好的视觉体验？](https://www.luogu.com.cn/article/vtmjqmhb)

### 题目大意

定义一个 $1∼n$ 的排列 $p$ 的「怪异度」为

$$
\sum_{i=1}^{n}|p_i-i|
$$

求「怪异度」为 $k$ 的 $1∼n$ 的排列数，答案对 $10^9+7$ 取模。

注意到题目里的 $n$ 小于等于 $50$，于是想到用 dp 做。

---

### 思路

我们假设有 $n$ 个球，$n$ 个盒子，那么如果第一个数字是 $2$，就把左边第一个球连到右边第二个盒子，可得答案就是每一条线跨过了多少格，我们拿样例解释：${213}$，$1$ 连 $2$，$2$ 连 $1$，$3$ 连 $3$，$1$ 到 $2$ 跨了 $1$ 格，$2$ 到 $1$ 跨过了 $1$ 格，$3$ 到 $3$ 是直线，这样算答案就是 $1+1+0=2$，推算过程其他大佬都已经写清楚了，这里给出转移方程：

$$
f_{i,j,k}=(2j+1)\times f_{i-1,j,k-2j}+(j+1)^2\times f_{i-1,j+1,k-2j}+f_{i-1,j+1,k-2j}
$$

注意：$j=0$ 时要特判。

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//祖宗问题
#define mod 1000000007
int n,m,f[55][55][3505];//不知道数组为什么要开55，不然会炸。
signed main(){
    cin>>n>>m;
    f[0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=i;j++){
            for(int k=j*2;k<=m;k++){
                if(j<1) f[i][j][k]=(f[i-1][j+1][k-j*2]*(j+1)%mod*(j+1)%mod+f[i-1][j][k-j*2]*(j*2+1)%mod)%mod;
                else f[i][j][k]=(f[i-1][j+1][k-j*2]*(j+1)%mod*(j+1)%mod+f[i-1][j][k-j*2]*(j*2+1)%mod+f[i-1][j-1][k-j*2]%mod)%mod;//屎山代码，转移方程
            }
        }
    }
    cout<<f[n][0][m]%mod;
    return 0;//好习惯
}
```

---

## 作者：WilliamFranklin (赞：0)

一道奇怪的题，奇怪的思路。

### 主要思路

考虑 $\sum_{i=1}^n{\vert p_i - i\vert}$ 可以转化成什么。

用人类智慧，这个东西其实可以转化成在数轴上行走。

详细说，就是有 $n$ 个老鼠在数轴上站成一行，有 $n$ 个洞在数轴上排成一行，然后第 $i$ 个老鼠要到第 $p_i$ 洞中，那么求的就是将这些老鼠走的路径长度和。然后这里就可以将这些路径拍扁，从而变成计算数轴上每一个小单位的贡献之和。

那么就可以设 $f_{i, j, k}$ 表示只考虑前 $i$ 个老鼠和前 $i$ 个洞，有 $j$ 个老鼠要跑入 $> i$ 的洞中，$\left[1, 2\right],\left[2,  3\right],\cdots,\left[i-1, i\right]$ 这些小单位被经过的次数总和为 $k$ 的方案数。

同时还可以发现前 $i$ 只老鼠中有 $j$ 只的目标是 $> i$ 的洞，根据对称性，前 $i$ 个洞中也有 $j$ 个的对应老鼠 $> i$。

然后考虑转移，从考虑前 $i$ 个到考虑前 $i + 1$ 个，总共有 $3$ 中情况，下面对于转移方程一个个讲解。

第一个式子：

$$f_{i, j, k} \rightarrow f_{i + 1, j + 1, k + 2j}$$

这个应该很简单，就是此时第 $i + 1$ 个老鼠要跑到 $> i+1$ 的洞中，那么考虑此时一共有 $2j$ 个路径经过 $\left[i, i + 1\right]$，所以就要直接转移到 $k + 2j$ 的状态。

第二个式子：

$$f_{i, j, k} \times (2j + 1) \rightarrow f_{i + 1, j, k + 2j}$$

这个就是说，如果考虑前 $i$ 个的时候和考虑前 $i + 1$ 个的时候，都是有 $j$ 个老鼠要跑到范围外的洞中，说明要么第 $i + 1$ 个老鼠跑到前 $i + 1$ 个洞中，有 $j + 1$ 种选择，要么就是前 $i$ 个老鼠中要跑到 $> i$ 的洞中的那 $j$ 个老鼠中的任意一个跑到第 $i + 1$ 个洞中。那么所有情况加起来就是 $2j + 1$。

第三个式子：

$$f_{i, j, k} \times j^2 \rightarrow f_{i + 1, j - 1, k + 2j}$$

这个情况就是考虑此时有前 $i$ 个老鼠中的那 $j$ 要跑到 $>i$ 的洞中的老鼠中的任意一个老鼠跑到第 $i + 1$ 个洞，且第 $i + 1$ 个老鼠跑到前 $i$ 个洞剩下的那 $j$ 个洞，那就是共 $j^2$。

看下代码吧。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 55, mod = 1e9 + 7;
long long f[N][N][N * N + 2 * N]; 
int n, k;
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> k;
	f[0][0][0] = 1;
	For(i, 0, n) {
		For(j, 0, i) {
			For(k, 0, n * n) {
				f[i + 1][j + 1][k + 2 * j] = (f[i + 1][j + 1][k + 2 * j] + f[i][j][k]) % mod;
				f[i + 1][j][k + 2 * j] = (f[i + 1][j][k + 2 * j] + f[i][j][k] * (2 * j + 1) % mod) % mod;
				f[i + 1][j - 1][k + 2 * j] = (f[i + 1][j - 1][k + 2 * j] + f[i][j][k] * j % mod * j % mod) % mod;
			}
		}
	}
	cout << f[n][0][k] << '\n';
	return 0;
} 
```

### 谢谢观看

---

## 作者：User_Unauthorized (赞：0)

## 题面

定义一个 $1 \sim n$ 的排列 $p$ 的「怪异度」为

$$\sum_{i=1}^n\left\lvert p_i-i\right\rvert$$

求「怪异度」为 $k$ 的 $1 \sim n$ 的排列数，答案对 $10^9+7$ 取模。

## 题解
考虑转化计算怪异度的过程，我们将值 $p_i$ 排列在左侧，将下标 $i$ 排列在右侧，构成一个 $n \times 2$ 的矩阵。将值和下标一一配对，定义配对一对元素的贡献为 $\left\lvert p_i-i\right\rvert$，求使总贡献为 $m$ 的配对方案。注意，这里的配对要求必须是值和下标配对，换句话说就是这个矩阵不同列的元素配对。

定义 $f_{i, j, k}$ 为前 $i$ 行中有 $j$ 对元素没有进行配对的情况下总贡献为 $k$ 的方案数。

发现 $k$ 的定义不便于维护，考虑转化总贡献的计算方法。在矩阵的每两行之间插入一个计数器，计数器的贡献值为经过这个计数器的配对的数量，可以看出配对的总贡献就是所有计数器的贡献和。发现当前计数器的贡献即前 $i$ 行未配对元素的数量，证明可以考虑在前 $i$ 行没有配对的元素一定会和第 $i + 1 \sim n$ 行的元素配对，那么一定会经过矩阵第 $i$ 行和第 $i + 1$ 行之间的计数器并产生贡献，故可以进行转移。

$f$ 的转移可以考虑在当前矩阵的基础上新增了一行，考虑这一行会产生几个配对，不难发现这一行两个元素可以产生的配对数量为 $0, 1, 2$，考虑枚举这三种情况进行转移。

#### 配对 $0$ 对

在前 $i$ 行有 $j$ 对没有进行配对且第 $i$ 行的两个元素均为配对，所以该状态可以从 $f_{i - 1, j - 1, k - 2j}$ 转移。

#### 配对 $1$ 对

考虑两种情况：

1. 第 $i$ 行的元素与前 $i - 1$ 行未配对的元素进行配对，单个元素的方案为 $j$，因为有两个元素，所以这部分的方案为 $2j$；

2. 第 $i$ 行的两个元素进行配对，方案数为 $1$。

因为第 $i$ 行的元素不会产生新的未配对数量，所以这两种情况均从 $f_{i - 1, j, k - 2j}$ 中转移而来。

#### 配对 $2$ 对

考虑前 $i - 1$ 行有多少对元素未配对，因为第 $i$ 行的两个元素均与前 $i - 1$ 行的元素进行了配对，所以消除了前 $i - 1$ 行的一对未配对元素，因而前 $i - 1$ 行有 $j + 1$ 对未配对元素，故该状态从 $f_{i - 1, j + 1, k - 2j}$ 转移。

对于第 $i$ 行的每个元素，均可以与另一列前 $i - 1$ 行的 $j + 1$ 个未配对元素进行独立配对，故方案数为 $\left(j + 1\right)^2$。

根据加法原理，可以得到总的转移式

$$f_{i, j, k} = f_{i - 1, j - 1, k - 2j} + (2j + 1) \times f_{i - 1, j, k - 2j} + \left(j + 1\right)^2 \times f_{i - 1, j + 1, k - 2j}$$

初始状态为 $f_{0, 0, 0} = 1$，根据该转移式递推即可以 $\mathcal{O}(n^4)$ 的复杂度通过本题。

## Code
```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MAXN = 55;

constexpr valueType MOD = 1e9 + 7;

bool ModOperSafeModOption = true;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= MOD;
        b %= MOD;

        if (a < 0)
            a += MOD;

        if (b < 0)
            b += MOD;
    }

    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= MOD;
        b %= MOD;

        if (a < 0)
            a += MOD;

        if (b < 0)
            b += MOD;
    }

    a = a - b;

    if (a < 0)
        a += mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= MOD;
        b %= MOD;

        if (a < 0)
            a += MOD;

        if (b < 0)
            b += MOD;
    }

    return a + b >= mod ? a + b - mod : a + b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= MOD;
        b %= MOD;

        if (a < 0)
            a += MOD;

        if (b < 0)
            b += MOD;
    }

    return a - b < 0 ? a - b + mod : a - b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= MOD;
        b %= MOD;

        if (a < 0)
            a += MOD;

        if (b < 0)
            b += MOD;
    }

    return (long long) a * b % MOD;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= MOD;
        b %= MOD;

        if (a < 0)
            a += MOD;

        if (b < 0)
            b += MOD;
    }

    a = (long long) a * b % MOD;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= MOD;
        b %= MOD - 1;

        if (a < 0)
            a += MOD;

        if (b < 0)
            b += MOD - 1;
    }

    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

std::array<std::array<std::array<valueType, MAXN * MAXN>, MAXN>, MAXN> dp;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, M;

    std::cin >> N >> M;

    if (M & 1) {
        std::cout << 0 << std::endl;

        return 0;
    }

    dp[0][0][0] = 1;

    for (valueType i = 1; i <= N; ++i) {
        for (valueType j = 0; j <= i; ++j) {
            for (valueType k = 2 * j; k <= M; k += 2) {
                dp[i][j][k] = 0;

                Inc(dp[i][j][k], mul((j + 1) * (j + 1), dp[i - 1][j + 1][k - 2 * j]));

                Inc(dp[i][j][k], mul(2 * j + 1, dp[i - 1][j][k - 2 * j]));

                if (j >= 1) {
                    Inc(dp[i][j][k], dp[i - 1][j - 1][k - 2 * j]);
                }
            }
        }
    }

    std::cout << dp[N][0][M] << std::endl;

    return 0;
}
```

---

## 作者：maple_trees_112 (赞：0)

嗯，这道题说白了就是硬dp，只要把动态转移转移方程都推出来，这道题就做出来了。
# ###题意分析
把这道题转换成数学思想理解起来应该容易些。
我们假设 $p_i$ 是盒子，$i$ 是球。球在左边摆一列，盒子在右边摆一列。如果 $p_i = x$，把左边的 $i$ 个和右边的 $x$ 连起来。
现在问题就变成了如下

现在一共有 $n$ 行，第 $i$ 行的第一个是球，第二个是盒子。再在每行之间画一条黑线，再将两方连起来，红线经过的黑线数量总和就是怪异值

咳咳，这里借用一下 @Judgelight老兄的图，~~毕竟我画不出来~~
![这里](https://cdn.luogu.com.cn/upload/image_hosting/jjah7aiz.png)

来看这里，这里的样例是 $p_1 = 2$,$p_2 = 1$，$p_3 = 3$，$1$ 经过了一条黑 $2$  经过了两条黑线,$3$ 经过了零条黑线。所以怪异值等于 $1 + 1 + 0 = 2$。

### 状态设置

嗯，基本思想说完了，我们来看看状态设置。
没啥好讲的，二分图想想即可，这里边就不过多赘述。
直接上结论：$dp[n][0][m]$。
### 状态转移
其实呢大概有三种情况。

第一种是不匹配，这个最好想，$dp[i - 1][j + 1][k - 2j]$。

第二种是只匹配一种，这个复杂又关键，慢慢往下看。

- 把第 $i$ 个球向前 $i - 1$ 个盒子中没有被连到的盒子连成一条线，第 $i$ 个盒子不动。所以是 $j \times dp[i - 1][j][k - 2j]$。
- 把第 $i$ 个盒子向前 $i - 1$ 个球中没有被连到的球连成一条线，第 $i$ 个球不动。所以是 $j \times dp[i - 1][j][k - 2j]$。
- 根据上面的理论，再加上个自己便是连线目标的问题，不难看出是 $j \times dp[i - 1][j][k - 2j]$。

第三种是匹配两组。

匹配两组是不需要考虑第 $i$ 盒子和第 $i$ 个球互选的情况了。所以只要前面选过即可，得出 $(j + 1)(j + 1) \times dp[i - 1][j + 1][k - 2j]$。

- 综上，$dp[i][j][k] = (2j + 1) \times dp[i - 1][j][k - 2j] + (j + 1)(j + 1) \times dp[i - 1][j + 1][k - 2j] + dp[i - 1][j - 1][k - 2j]$。

大概的讲了一遍，如有不恰当或漏了的请各位大佬不客气地指出

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll P = 1000000007;
ll n, e, dp[55][55][55 * 55];
void add(ll& x, ll y) {
	x = (x + y) % P;//函数更加方便
}
int main() {
	cin >> n >> e;
	dp[1][0][0] = dp[1][1][2] = 1;
	for (ll i = 1; i < n; i++) {
		for (ll j = 0; j <= i; j++) {
			for (ll k = 0; k <= n * n; k++) {
				add(dp[i + 1][j][k + 2 * j], dp[i][j][k]); 
				if (j) {
					add(dp[i + 1][j][k + 2 * j], j * dp[i][j][k] * 2); 
					add(dp[i + 1][j - 1][k + 2 * (j - 1)], j * j * dp[i][j][k]);
				}
				add(dp[i + 1][j + 1][k + 2 * (j + 1)], dp[i][j][k]); 
			}
		}
	}
	cout << dp[n][0][e] << endl;
	return 0;
}
```
时间复杂度挺高的，$n$ 的四次方。



---

