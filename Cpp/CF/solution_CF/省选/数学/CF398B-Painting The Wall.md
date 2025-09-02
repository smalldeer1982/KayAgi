# Painting The Wall

## 题目描述

User ainta decided to paint a wall. The wall consists of $ n^{2} $ tiles, that are arranged in an $ n×n $ table. Some tiles are painted, and the others are not. As he wants to paint it beautifully, he will follow the rules below.

1. Firstly user ainta looks at the wall. If there is at least one painted cell on each row and at least one painted cell on each column, he stops coloring. Otherwise, he goes to step 2.
2. User ainta choose any tile on the wall with uniform probability.
3. If the tile he has chosen is not painted, he paints the tile. Otherwise, he ignores it.
4. Then he takes a rest for one minute even if he doesn't paint the tile. And then ainta goes to step 1.

However ainta is worried if it would take too much time to finish this work. So he wants to calculate the expected time needed to paint the wall by the method above. Help him find the expected time. You can assume that choosing and painting any tile consumes no time at all.

## 样例 #1

### 输入

```
5 2
2 3
4 1
```

### 输出

```
11.7669491886
```

## 样例 #2

### 输入

```
2 2
1 1
1 2
```

### 输出

```
2.0000000000
```

## 样例 #3

### 输入

```
1 1
1 1
```

### 输出

```
0.0000000000
```

# 题解

## 作者：Aoki_灏 (赞：10)

~~今天刚接触期望，借发题解来加深一下期望dp学习~~

这是一道期望dp经典例题

首先所谓期望？
~~不是hope~~这里指的是数学期望

## 数学期望

		在概率论和统计学中，数学期望(mean)（或均值，亦简称期望）是试验中每次可能结果的概率乘以其结果的总和，是最基本的数学特征之一。它反映随机变量平均取值的大小。
        需要注意的是，期望值并不一定等同于常识中的“期望”——“期望值”也许与每一个结果都不相等。期望值是该变量输出值的平均数。期望值并不一定包含于变量的输出值集合里。
        大数定律规定，随着重复次数接近无穷大，数值的算术平均值几乎肯定地收敛于期望值
        
        解释来自百科，总之就是
        某事件期望值=(sigma)所有情况出现的概率*这种情况的结果
        
### 举个栗子

		某城市有10万个家庭，没有孩子的家庭有1000个，有一个孩子的家庭有9万个，有两个孩子的家庭有6000个，有3个孩子的家庭有3000个。
        
        则此城市中任一个家庭中孩子的数目是一个随机变量，记为X。它可取值0，1，2，3
        
        其中，X取0的概率为0.01，取1的概率为0.9，取2的概率为0.06，取3的概率为0.03。
        
        则，它的数学期望
        即此城市一个家庭平均有小孩1.11个。
        大概就是这样
  
## 题解

		这题显然是期望dp，于是考虑设计状态。

		dp[i][j]表示还剩i行j列需要填色，期望达到目标状态的步数
        可以推出转移方程
        dp[i][j]=(1(无论怎样都要一步)
        +dp[i-1][j-1]*i*j+(若填充后使需填充的行列个少一个，有i*j种填色方案)
        dp[i][j-1]*j*(n-i)+ (同理只少了一列，有j*(n-i)种选择)
        dp[i-1][j]*i*(n-j)+(同理只少了一行，有i*(n-j)种选择)
        dp[i][j]*(n-i)*(n-j)(并没有少任何一行一列，于是只有(n-i)*(n-j)种选择）
        最后统一除n*n表示每种概率
        移向后得到

        dp[i][j]=(n*n +dp[i-1][j-1]*i*j+dp[i][j-1]*j*(n-i)+dp[i-1][j]*i*(n-j))/(n*n-(n-i)*(n-j))
        完毕
        
## 代码

```
scanf("%lf%d",&n,&m);
    hang=lie=n;//行列两个变量记录目前还剩多少行列需要填充
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(!row[x])row[x]=1,hang--;
        if(!col[y])col[y]=1,lie--;
    }
    dp[0][0]=0;
    for(int i=1;i<=n;i++)//初始化
    {
        dp[i][0]=dp[i-1][0]+double(n/i);
        dp[0][i]=dp[0][i-1]+double(n/i);
    }
    for(int i=1;i<=hang;i++)
        for(int j=1;j<=lie;j++)
    {
        dp[i][j]=n*n+dp[i-1][j-1]*i*j+
                dp[i][j-1]*j*(n-i)+
                dp[i-1][j]*i*(n-j);
        dp[i][j]/=n*n-(n-i)*(n-j);
    }
    printf("%.10lf",dp[hang][lie]);
```

---

## 作者：c202201 (赞：5)

# CF398E Painting The Wall 

### 题目描述

一个 $n \times n$ 的网格中已经有 $m$ 个格子。每次随机在所有格子中选一个涂色。问使网格每行每列都至少有一个格子被涂色的操作次数期望。误差小于 $10^{-4}$。

### 数据范围

$1 \le n \le 2 \times 10^3 , 0 \le m \le \min(n^2 , 2 \times 10^4)$。

## 思路

求操作次数期望，显然期望 dp。

考虑如何设计状态。

因为操作次数期望与还没有涂色的行列有关，那么可以设计 $f_{i,j}$ 为还有 $i$ 行 $j$ 列没有涂色的操作次数期望。

考虑它会由什么状态转移过来。

1. 若随机选到一个点其行列都没有点被涂过色，那么由 $f_{i-1,j-1}$ 转移过来，这样的点有 $i*j$ 个，那么概率为 $\frac{i*j}{n^2}$。
2. 若随机选到一个点其行有点被涂过色，列没有点被涂色，那么由 $f_{i,j-1}$ 转移过来，这样的点有 $(n-i)*j$ 个，那么概率为 $\frac{(n-i)*j}{n^2}$。
3. 若随机选到一个点其列有点被涂过色，行没有点被涂色，那么由 $f_{i-1,j}$ 转移过来，这样的点有 $i*(n-j)$ 个，那么概率为 $\frac{i*(n-j)}{n^2}$。
4. 若随机选到一个点其行列都有点被涂过色，那么由 $f_{i,j}$ 转移过来，这样的点有 $(n-i)*(n-j)$ 个，那么概率为 $\frac{(n-i)*(n-j)}{n^2}$。

那么转移方程就是

$$f_{i,j} = 1 + f_{i-1,j-1} \times \frac{i \times j}{n^2 } + f_{i,j-1} \times \frac{(n-i) \times j}{n^2 } + f_{i-1,j} \times \frac{i \times (n-j)}{n^2} + f_{i,j} \times \frac{(n-i) \times (n-j)}{n^2} $$

通分一下就可以得到：

$$f_{i,j} = \frac{n^2 + f_{i-1,j-1} \times i \times j + f_{i,j-1} \times (n-i) \times j + f_{i-1,j} \times i \times (n-j) + f_{i,j} \times (n-i) \times (n-j)}{n^2}$$

再移项 

$$f_{i,j} \times \frac{n^2 - (n-i) \times (n-j)}{n^2} = \frac{n^2 + f_{i-1,j-1} \times i \times j + f_{i,j-1} \times (n-i) \times j + f_{i-1,j} \times i \times (n-j)}{n^2}$$

两边同时除以 $\frac{n^2 - (n-i) \times (n-j)}{n^2}$，得到 

$$f_{i,j}=\frac{\frac{n^2 + f_{i-1,j-1} \times i \times j + f_{i,j-1} \times (n-i) \times j + f_{i-1,j} \times i \times (n-j)}{n^2}}{\frac{n^2 - (n-i) \times (n-j)}{n^2}}$$

右边分子分母同时乘上 $n^2$，得到 

$$f_{i,j} = \frac{n^2 + f_{i-1,j-1} \times i \times j + f_{i,j-1} \times (n-i) \times j + f_{i-1,j} \times i \times (n-j)}{n^2 - (n-i) \times (n-j)}$$

这个就是最终的柿子。

然后是初始化，$f_{i,0}$ 和 $f_{0,i}$ 是边界情况。

$f_{i,0} = f_{0,i} = \sum\limits_{j=1}^{i} \frac{n}{j}$。

最后答案就是 $f_{x,y}$，其中 $x$ 是还没被点被涂过色的行数，$y$ 是还没被点被涂过色的列数。

## 代码

talking is cheap, show me your code.

```cpp
#include <bits/stdc++.h>
#define db double
using namespace std;
const int N=2e3+5;
int n,m,x,y;
db f[N][N];
bitset<N> vis[2];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;++i){
		scanf("%d %d",&u,&v);
		if(!vis[0][u]) --x,vis[0][u]=1;
		if(!vis[1][v]) --y,vis[1][v]=1;
	}
	x+=n,y+=n;
	for(int i=1;i<=n;++i) f[i][0]=f[i-1][0]+n*1.0/i,f[0][i]=f[0][i-1]+n*1.0/i;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			f[i][j]=(n*n+f[i-1][j]*i*(n-j)+f[i][j-1]*(n-i)*j+f[i-1][j-1]*i*j)/((i+j)*n-i*j);
	printf("%.5lf",f[x][y]);
	return 0;
}
```



---

## 作者：ww3113306 (赞：5)

，，这种一般都要倒推才行。
设$f[i][j]$表示还有$i$行,$j$列未满足的情况下的期望次数。
因为每次选择都是完全随机，不受其他东西的影响。
所以对于题中给出的$m$,实际上就是告诉了我们要求什么东西，假设在已经有那$m$个涂色方块的情况下,我们还有$t1$行，$t2$列未满足，那么我们要求的就是$f[t1][t2]$.
那么我们可以列出转移方程：(一行写不下，分2行写)
$$f[i][j] = 1 + \frac{ij}{n ^ 2} f[i - 1][j - 1] + \frac{(n - i)j}{n ^ 2} f[i][j - 1] $$
$$f[i][j] += \frac{i(n - j)}{n ^ 2} f[i - 1][j] + \frac{(n - i)(n - j)}{n^2} f[i][j]$$
$1$是每次选择的代价，后面的就是进入每一种状态的概率，对于任意后继状态，它对当前状态的贡献就是它的期望 * 进入这个状态的概率(全期望公式)

然后移项化简，对于后面这一堆东西提出一个$\frac{1}{n ^ 2}$，然后把$f[i][j]$放到等式左边，这样就只需要在最后面除一次，可以降低一点精度误差？
$$f[i][j] = \frac{n ^ 2 + ijf[i - 1][j - 1] + (n - i)jf[i][j - 1] + i(n - j)f[i - 1][j]}{[n ^ 2 - (n - i) (n - j)]}$$
然后因为计算的时候，可能会出现为满足行或列的数量为0的情况，这种时候还放在一起计算就不太方便了(需要特判)，因此考虑把这些情况单独拿出来看。
那么因为$f[i][0]$这个状态只受行的影响，所以可以看做一个优惠券收集问题，即:
$$f[i][0] = \sum_{j = 1}^{i} \frac{n}{j}$$
那么由于$$f[i - 1][0] = \sum_{j = 1}^{i - 1} \frac{n}{j}$$
可以得到关于$f[i][0]$和$f[i - 1][0]$的一个递推式，即：
$$f[i][0] = f[i - 1][0] + \frac{n}{i}$$
解释一下那个和式：如果我们现在还有$i$行未满足，共$n$行，那么选一次可以导致一行新的被满足的概率就是$\frac{i}{n}$,那么期望就为$\frac{n}{i}$.
这个东西的感性理解大概是：如果一个事件发生的概率是$\frac{1}{5}$，那么显然期望$5$天这个事件就会发生，所以期望是概率的倒数。。。

不过这个也是可以证明的，只需要将计算式列出，做一个错位相减，利用一下极限的思想，最后可以算出期望确实是概率的倒数。

---

## 作者：codecode (赞：2)

#### 题解：

一道适合练手的简单期望题。

求一个可能操作无穷的期望时，一般的可行做法是找整体，例如下面的例子：

> 抛硬币，正反概率均等，求抛到正面所需的期望次数。

事实上，如果我们朴素地算，也就是枚举所有的情况，可以得到 

$$E=\sum_{i=1}^{\infty}\left[(\frac{1}{2})^{i-1}\times(1-\frac{1}{2})\times i\right]=2$$

但是，对于一些复杂的问题，列出的式子将难以化简，我们需要寻找一个适当的简洁做法，例如：

- 第一次，$\dfrac{1}{2}$ 的概率抛到正面，结束；

- 第一次，$\dfrac{1}{2}$ 的概率抛到反面，继续；

	- 没必要继续分支了，事实上**还需要**期望 $E$ 次。
    
因此，$E=\dfrac{1}{2}\times 1+\dfrac{1}{2}\times(1+E)$，也就是 $E=2$。


------------

包括本题在内的其它很多期望题，都应该充分利用这一方法，这将减少思维难度和操作难度。设 $f(i,j)$ 表示还剩下 $i$ 行 $j$ 列没有格子被涂色，达到每行每列都有格子被涂色所期望花费的涂色次数。则

- 这一次涂色，$\dfrac{i}{n}\times \dfrac{j}{n}$ 的概率涂的是剩下的 $i$ 行 $j$ 列相交区域的格子，**还需要**期望 $f(i-1,j-1)$ 次；

- 这一次涂色，$\dfrac{i}{n}\times \dfrac{n-j}{n}$ 的概率涂的是剩下的 $i$ 行，但不是剩下的 $j$ 列中的格子，**还需要**期望 $f(i-1,j)$ 次；

- 这一次涂色，$\dfrac{n-i}{n}\times \dfrac{j}{n}$ 的概率涂的是剩下的 $i$ 行，但不是剩下的 $j$ 列中的格子，**还需要**期望 $f(i,j-1)$ 次；

- 这一次涂色，$\dfrac{n-i}{n}\times \dfrac{n-j}{n}$ 的概率涂的既不是剩下的 $i$ 行，也不是剩下的 $j$ 列中的格子，**还需要**期望 $f(i,j)$ 次。

因此

$$\begin{aligned}f(i,j)&=1+\frac{ij}{n^2}f(i-1,j-1)+\frac{i(n-j)}{n^2}f(i-1,j)\\&+\frac{(n-i)j}{n^2}f(i,j-1)+\frac{(n-i)(n-j)}{n^2}f(i,j)\end{aligned}$$

这可以看作是关于 $f(i,j)$ 的一元一次方程，我们可以将它解出来，也就得到了递推式

$$\begin{aligned}f(i,j)=\frac{n^2+ijf(i-1,j-1)+i(n-j)f(i-1,j)+(n-i)jf(i,j-1)}{in+jn-ij}\end{aligned}$$

边界条件呢？当 $ij=0$ 时即为边界，这将化简为一维的问题，而这已经是[出烂了的题](https://www.luogu.com.cn/problem/P1291)了。我们有

$$f(i,0)=f(0,i)=nH(i)$$

这里 $H(n)$ 是调和级数 $H(n)=\sum\limits_{i=1}^n \dfrac{1}{i}$。


------------

因此，我们发现答案其实只和最初有多少行多少列还没有被涂色有关，拿数组标记一下即可，总时间复杂度 $O(n^2)$。

#### 代码：

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2333;
int n,m,p,q,r[maxn],c[maxn];
double dp[maxn][maxn];
int main(){
	cin>>n>>m,p=q=n; //p,q 记录还剩多少行/列
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		if(!r[u])p--,r[u]=1;
		if(!c[v])q--,c[v]=1;
	}
	for(int i=1;i<=n;i++)
		dp[0][i]=dp[i][0]=dp[i-1][0]+n*1.0/i;
	for(int i=1;i<=p;i++)
		for(int j=1;j<=q;j++)
			dp[i][j]=(n*n+dp[i-1][j]*i*(n-j)+dp[i][j-1]*(n-i)*j+dp[i-1][j-1]*i*j)*1.0/(i*n+j*n-i*j);
	printf("%.10f",dp[p][q]);
	return 0;
}
```

---

## 作者：chihik (赞：2)


先考虑所有格子均未涂色的情况。

因为格子的涂色只会影响一行一列，所以可以设 $dp(i,j)$ 表示还需要涂 $i$ 行 ， $j$ 列的期望步数。

1.涂色格所在行列均未染色，由 $dp(i-1,j-1)$ 转移，概率为 $\frac{i}{n} \times \frac{j}{n}$

2.涂色格所在行未染色，列已染色，由 $dp(i-1,j) $ 转移，概率为 $\frac{i}{n} \times \frac{n-j}{n}$

3.涂色格所在列未染色，行已染色，由 $dp(i,j-1) $ 转移，概率为 $\frac{n-i}{n} \times \frac{j}{n}$

4.涂色格所在行列均已染色，由 $dp(i,j)$ 转移，概率为 $\frac{n-i}{n} \times \frac{n-j}{n}$

综上得：

$$dp(i,j) = 1 + dp( i - 1 , j ) * \frac{i * ( n - j )}{n^2} + dp( i , j - 1 ) * \frac{( n - i ) * j}{n^2} + dp( i - 1 , j - 1 ) * \frac{i * j}{n^2} + dp(i,j) * \frac{(n-i)*(n-j)}{n^2}$$

移项得：

$$dp(i,j) = \frac{ 1 + dp( i - 1 , j ) * \frac{i * ( n - j )}{n^2} + dp( i , j - 1 ) * \frac{( n - i ) * j}{n^2} + dp( i - 1 , j - 1 ) * \frac{i * j}{n^2} }{1-\frac{(n-i)(n-j)}{n^2}}$$

上下同时乘 $n^2$ 得到：

$$dp(i,j) = \frac{ n^2 + dp( i - 1 , j ) * i * ( n - j ) + dp( i , j - 1 ) * ( n - i ) * j + dp( i - 1 , j - 1 ) * i * j }{n^2-(n-i)(n-j)}$$

边界条件：

1.$dp[0][0]=0$

2.$dp[0][i]/dp[i][0]=\sum_{j=1}^i \lfloor \frac{i}{j} \rfloor $ 经典的[邮票收集问题](https://www.luogu.com.cn/problem/SP1026)。

现在再考虑一开始有涂色的格子，其实只是让其中一些行列提前满足要求，即答案并不是 $dp(n,n)$ ，而是减去已满足数量的结果~~自己意会一下~~。

```cpp
#include <cstdio>

const int MAXN = 2e3;
int n , m , x , y;
bool vis[ 2 ][ MAXN + 5 ];
double dp[ MAXN + 5 ][ MAXN + 5 ];

int main( ) {
	scanf("%d %d",&n,&m);
	for( int i = 1 , u , v ; i <= m ; i ++ ) {
		scanf("%d %d",&u,&v);
		if( !vis[ 0 ][ u ] ) x -= ( vis[ 0 ][ u ] = 1 );
		if( !vis[ 1 ][ v ] ) y -= ( vis[ 1 ][ v ] = 1 );
	}
	x += n , y += n;

	dp[ 0 ][ 0 ] = 0;
	for( int i = 1 ; i <= n ; i ++ ) {
		dp[ i ][ 0 ] = dp[ i - 1 ][ 0 ] + n * 1.0 / i;
		dp[ 0 ][ i ] = dp[ 0 ][ i - 1 ] + n * 1.0 / i;
	}
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 1 ; j <= n ; j ++ )
			dp[ i ][ j ] = ( n * n + dp[ i - 1 ][ j ] * i * ( n - j ) + dp[ i ][ j - 1 ] * ( n - i ) * j + dp[ i - 1 ][ j - 1 ] * i * j ) / ( n * n - ( n - i ) * ( n - j ) );

	printf("%.10f", dp[ x ][ y ] );
	return 0;
}
```


---

## 作者：XL4453 (赞：1)

### 解题思路：

那么这显然是一道比较简单期望 DP。

设 $f_{i,j}$ 表示剩下了 $i$ 行 $j$ 列没有涂过色的期望次数，则根据全期望公式得到：

$f_{i,j}=1+\dfrac{i\times j }{n^2}\times f_{i-1,j-1}+\dfrac{i\times (n-j)}{n^2}\times f_{i-1,j}+\dfrac{(n-i)\times j}{n^2}\times f_{i,j-1}+\dfrac{(n-i)\times (n-j)}{n^2}\times f_{i,j}$

化简一下，立刻有：

$f_{i,j}=\dfrac{n^2+i\times j\times f_{i-1,j-1}+i\times (n-j)\times f_{i-1,j}+(n-i)\times j\times f_{i,j-1}}{n^2-(n-i)\times(n-j)}$

然后就是处理一下初始状态，也就是：

$f_{i,0}=f_{i-1,0}+\dfrac{n}{i}$

以及：

$f_{0,j}=f_{0,j-1}+\dfrac{n}{j}$

---------------
### 代码：

```cpp
#include<cstdio>
using namespace std;
double f[2003][2003];
int n,m,x,y,hx[2003],hy[2003],c,r;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		hx[x]=1;hy[y]=1;
	}
	c=r=n;
	for(int i=1;i<=n;i++)
	c-=hx[i],r-=hy[i];
	for(int i=1;i<=c;i++)
	f[i][0]=f[i-1][0]+(double)n/(double)i;
	for(int i=1;i<=r;i++)
	f[0][i]=f[0][i-1]+double(n)/(double)i;
	for(int i=1;i<=c;i++)
	for(int j=1;j<=r;j++){
		f[i][j]=(1.0*(double)(1.0*n*n+i*j*f[i-1][j-1]+i*(n-j)*f[i-1][j]+(n-i)*j*f[i][j-1]))/(double)(1.0*n*n-(n-i)*(n-j));
	}
	printf("%.10f",f[c][r]);
	return 0;
}
```



---

## 作者：OtterZ (赞：0)

~~都九年级了，还没法搞定马尔科夫链就有问题了，这就是中学生现状。~~
# 题意
在 $n \times n(1 \le n \le 2000)$ 的网格图上，进行所有格子等概率打标记，问期望几次后每行每列都有标记格。
# 多一手
由于每个格子都是等概率的，我们不妨在里面掺一步：每次标记后将标记格子通过行交换和列交换移到左下角，这样不仅不会改变分析的正确性，还能将有标记格的行和列都移到一边，便于分析。

![](https://cdn.luogu.com.cn/upload/image_hosting/hmetedre.png)

# 马尔科夫链和动态规划

由于题目是一道求期望的题，考虑使用马尔科夫链作为接下来的分析方式。

作为~~初中~~高等数学，马尔科夫链并不困难，其原理是：

1. 设状态，及一种状态到一类结束状态的期望或概率；
2. 根据下一步的状态情况得出求此状态的方程式；
3. 若通过转方程得到的转移关系图为有向无环图则用动规，否则上高斯消元。

接下来，我们走一遍流程。

设 $dp_{i,j}$ 表示已经有 $i$ 行 $j$ 列存在标记格，问标记到每行每列都被标记的期望次数。

接下来分析下一个标记的可能情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/b6qxyezi.png)

1. 标记落入红区，对应行对应列都已有标记格，$(i,j) \to (i,j)$，概率为 $\frac{ij}{n ^ 2}$。
2. 标记落入黄区，对应行已被标记，对应列在这次标记后有标记格，$(i,j) \to (i,j + 1)$，概率为 $\frac{i(n - j)}{n ^ 2}$。
3. 标记落入蓝区，对应列已被标记，对应行在这次标记后有标记格，$(i,j) \to (i + 1,j)$，概率为 $\frac{(n - i)j}{n ^ 2}$。
4. 标记落入绿区，对应列、对应行在这次标记后有标记格，$(i,j) \to (i + 1,j + 1)$，概率为 $\frac{(n - i)(n - j)}{n ^ 2}$。

得到转移方程：

$$
dp_{i,j} =
\begin{cases}
  0 & i = n\land j = n \\
  1 + \frac{ij}{n ^ 2}dp_{i,j} + \frac{i(n - j)}{n ^ 2}dp_{i + 1,j} + \frac{(n - i)(n - j)}{n ^ 2}dp_{i + 1,j + 1} & i \neq j \lor j \neq n \\
\end{cases}

$$

对 $(i,j) \neq (n,n)$ 的情况，有：

$$
dp_{i,j} = 1 + \frac{ij}{n ^ 2}dp_{i,j} + \frac{i(n - j)}{n ^ 2}dp_{i + 1,j} + \frac{(n - i)(n - j)}{n ^ 2}dp_{i + 1,j + 1}
$$

即

$$
(1 - \frac{ij}{n ^ 2})dp_{i,j} = 1  + \frac{i(n - j)}{n ^ 2}dp_{i + 1,j} + \frac{(n - i)(n - j)}{n ^ 2}dp_{i + 1,j + 1}
$$

成功处理掉自环，接下来由于转移关系为有向无环图，可以用 $\operatorname{O}(n ^ 2)$ 动态规划解决。

最后对于部分格子已涂的情况，根据这些格子影响的行列数定位状态即可。

# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,cntx,cnty;
bool vis1[2009],vis2[2009];
double dp[2009][2009];
int main(){
	scanf("%d %d",&n,&m);
	for(int i = 1; i <= m; i ++){
		scanf("%d %d",&x,&y);
		if(!vis1[x])
			vis1[x] = true,cntx++;
		if(!vis2[y])
			vis2[y] = true,cnty++;
	}
	dp[n][n] = 0;
	for(int i = n; i >= cntx; i --){
		for(int j = n; j >= cnty; j --){
			if(i == n && j == n)
				continue;
			dp[i][j] = 1;
			if(i < n)
				dp[i][j] += dp[i + 1][j] * (n - i) * j / (n * n);
			if(j < n)
				dp[i][j] += dp[i][j + 1] * (n - j) * i / (n * n);
			if(i < n && j < n)
				dp[i][j] += dp[i + 1][j + 1] * (n - i) * (n - j) / (n * n);
			dp[i][j] = dp[i][j] * (n * n) / (n * n - i * j); 
		}
	}
	printf("%.7lf\n",dp[cntx][cnty]);
}
```

---

## 作者：g1ove (赞：0)

题解区怎么全写正推的。写一份倒推的题解。

## Solution
我们发现原问题可以这样看：
+ 有两个数组 $a,b$，每次等概率在 $a,b$ 中各选一个位置染色，求 $a,b$ 数组全部染上色的期望次数。

然后我们发现我们并不关心哪些位置被染色了，只关心数组染色位置的个数。我们不妨设计状态 $f_{i,j}$ 表示 $a$ 数组染了 $i$ 个位置，$b$ 数组染了 $j$ 个位置的操作次数期望。显然，边界条件 $f_{n,n}=0$。

然后根据期望的性质，分四种情况讨论，每次是否染的是新颜色还是旧的颜色，于是我们能写出 dp 式子：

$f_{i,j}=\frac{i\times j}{n^2}f_{i,j}+\frac{(n-i)\times j}{n^2}f_{i+1,j}+\frac{i\times (n-j)}{n^2}f_{i,j+1}+\frac{(n-i)\times (n-j)}{n^2}f_{i+1,j+1}+1$

然后通过通用套路消除两边的 $f_{i,j}$，式子化简通分一下就是：

$f_{i,j}=\frac{f_{i+1,j}\times(n-i)\times j+f_{i,j+1}\times i\times (n-j)+f_{i+1,j+1}\times (n-i)\times (n-j)+n^2}{n^2-i\times j}$

直接 dp 即可。时间复杂度 $O(n^2)$。

最后讲一下怎么找答案，开个标记数组判断要染几个格子就行了。

code

```cpp
#include<bits/stdc++.h>
#define N 2005
#define ll long long
using namespace std;
int n,m,s;
double f[N][N];
int a[N],b[N],s1,s2;
int main() 
{
	scanf("%d%d",&n,&m);
	f[n][n]=0;
	s=n*n;
	for(int i=n;i>=0;i--)
		for(int j=n;j>=0;j--)
		{
			if(i==n&&j==n) continue;
			f[i][j]=(f[i+1][j]*(n-i)*j+f[i][j+1]*i*(n-j)+f[i+1][j+1]*(n-i)*(n-j)+s)*1.0/(s-i*j);
		}	
	while(m--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(!a[x]) a[x]=1,s1++;
		if(!b[y]) b[y]=1,s2++;
	}
	printf("%.8f",f[s1][s2]);
	return 0;
}
```

---

## 作者：Xiao_mo (赞：0)

# Step1
先把被染过色的列和行移到最边上,如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/eq5tutl0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

$i$ 和 $j$ 为剩余的行列数。

抽到白色的概率是 $\frac{i×j}{n×n}$ ，覆盖了 $1$ 行和 $1$ 列。

抽到蓝色的概率是 $\frac{i×(n-j)}{n×n}$ ，覆盖了 $1$ 行。

抽到红色的概率是 $\frac{(n-i)×j}{n×n}$ ，覆盖了 $1$ 列。

抽到紫色的概率是 $\frac{(n-i)×(n-j)}{n×n}$ ，无覆盖。

所以可以得 $O(n^2)$ 的转移式子。
$f[i][j]=1+\frac{i×j×f[i-1][j-1]+i×(n-j)×f[i-1][j]+(n-i)×j×f[i][j-1]}{n×n}+\frac{(n-i)×(n-j)×f[i][j]}{n×n}$

把右边的 $f[i][j]$ 移到左边。

$\frac{[n×(i+j)-i×j]}{n×n}×f[i][j]=1+\frac{i×j×f[i-1][j-1]+i×(n-j)×f[i-1][j]+(n-i)×j×f[i][j-1]}{n×n}$

$f[i][j]=\frac{n×n+i×j×f[i-1][j-1]+i×(n-j)×f[i-1][j]+(n-i)×j×f[i][j-1]}{n×(i+j)-i×j}$

# Step3
当 $i=0$ 或 $j=0$ 时,就转换成了一个简单的期望问题。

在一个有 $n$ 个不同编号的球的箱子里,抽出后并放回,求抽出过所有编号的球的期望抽取次数。

所以预处理 $f[i][0]=f[0][i]=f[i-1][0]×\frac{n}{i}$ 。

# End
```cpp
#include<bits/stdc++.h>
#define ll long long
#define rg register
using namespace std;
inline ll read() {
	register ll s=0,f=0;
	register char ch=getchar();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f?-s:s;
}
int n,m,h[2001],l[2001],a,b;
double f[2001][2001];
int main() {
	a=b=n=read(),m=read();
	for(int i=1; i<=m; i++) {
		int x=read(),y=read();
		if(!h[x])a--,h[x]=1;
		if(!l[y])b--,l[y]=1;
	}
	for(int i=1;i<=n;i++)f[0][i]=f[i][0]=f[i-1][0]+(1.0*n)/i;
	for(int i=1;i<=a;i++){
		for(int j=1;j<=b;j++){
			double fm=(1.0*(i*n+j*n-i*j));
			f[i][j]=(1.0*(n*n+(1.0*i*j)*f[i-1][j-1]+(1.0*i*(n-j))*f[i-1][j]+(1.0*(n-i)*j)*f[i][j-1]))/fm;
		}
	}
	printf("%.6lf",f[a][b]);
	return 0;
}
```


---

