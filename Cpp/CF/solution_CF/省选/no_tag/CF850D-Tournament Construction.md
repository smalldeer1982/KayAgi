# Tournament Construction

## 题目描述

Ivan is reading a book about tournaments. He knows that a tournament is an oriented graph with exactly one oriented edge between each pair of vertices. The score of a vertex is the number of edges going outside this vertex.

Yesterday Ivan learned Landau's criterion: there is tournament with scores $d_1\le d_2\le\dots\le d_n$ if and only if $\sum_{i=1}^kd_i\ge\frac{k(k-1)}2$ for all $1\le k<n$ and $\sum_{i=1}^nd_i=\frac{n(n-1)}2$.

Now, Ivan wanna solve following problem: given a set of numbers $S=\{a_1,a_2,\dots,a_m\}$, is there a tournament with given set of scores? I.e. is there tournament with sequence of scores $ d_1,d_2,\dots,d_n$ such that if we remove duplicates in scores, we obtain the required set $\{a_1,a_2,\dots,a_m\}$ ?

Find a tournament with minimum possible number of vertices.

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
4
0011
1001
0100
0010
```

## 样例 #2

### 输入

```
2
0 3
```

### 输出

```
6
000111
100011
110001
011001
001101
000000
```

# 题解

## 作者：LastOrder_ (赞：5)

具体实现参照了上一篇题解。这里是更详细的解释。

> 一个竞赛图的度数集合是由该竞赛图中每个点的出度所构成的集合。 现给定一个 $m$ 个元素的集合，第 $i$ 个元素是 $a_i$。判断其是否是一个竞赛图的度数集合，如果是，找到点数最小的满足条件的竞赛图。
>
> $1\le m\le 31$ ， $0\le a_i\le 300$，$a_i$ 互不相同。

设原图内总点数为 $n$ 。

**【结论】**$n\leq61$ 。

**【证明】** 根据题意，原图最多有 $30\times n$ 条边。而竞赛图的边数为 $\dfrac {n(n-1)}2$ ，解得 $n\le 61$ 。

下面分为两个步骤来解决。

### 1. 构建出原出度序列

因为题目给的是出度构成的集合，所以我们要根据这个集合构建出满足竞赛图性质的出度序列。

首先我们来看一个定理：

#### 兰道定理

定义一个竞赛图的比分序列 ( score sequence ) ，是把竞赛图的每一个点的出度从小到大排列得到的序列。
一个长度为 $n$ 的序列 $s=(s_1\le s_2\le \dots\le s_n)$ ，是合法的比分序列当且仅当：
$$
\forall 1\le k\le n,\sum\limits_{i=1}^k s_i\ge\dfrac {k(k-1)}2
$$
根据这个定理，我们将原 $a$ 序列排序，并定义 $f(i,j,y)$ 表示集合大小为 $i$ ，构建出原图的点数为 $j$ ，共有边数为 $y$ 。

根据定理，则可知 $y\geq \dfrac{j(j-1)}2$ 恒成立。

我们枚举 $i,j,y$ ，并枚举 $i-1$ 时的状态（例如有 $k$ 个点， $x$ 条边），若 $f(i-1,k,x)$ 可行则 $f(i,j,y)$ 可行。

顺便记录下此时的 $j-k$ （即为有多少个点在出度集合中属于 $i$ ）。

这样便能构造出原出度序列。

### 2. 构建出原图

这一部分就比较简单了。

设在 `1.` 中建立的出度序列为 $d_i$ ，在 `2.` 中建立的为 $u_i$ 。

先假设 $\forall i > j$ ，边的方向都是 $i\to j$ 。则 $u_i = i-1$ 。

每次找到一个三元组 $(i,j,k)$ ，使 $u_i>d_i,u_j=d_j,u_k<d_k$ 且存在 $i\to j$ ，$j\to k$ 的边。

这样，可以取反这两条边，达到的效果是 $u_i\leftarrow u_i-1$ ，$u_j\leftarrow u_j$ ，$u_k\leftarrow u_k-1$ 。

一直循环如上步骤，则可以使 $u$ 逐渐接近 $d$ ，最终完全相同。

```cpp

const int N = 62, M = 1831;

int n,m,a[N];
bool ck[N][N][M]; int g[N][N][M];
int d[N],u[N];
bitset<N> mp[N];
signed main(){
	m = read();
	for(int i = 1 ; i <= m ; i ++) a[i] = read();
	sort(a+1,a+m+1);
	ck[0][0][0] = 1;
	for(int i = 1 ; i <= m ; i ++)
		for(int j = i ; j < N ; j ++)
			for(int k = i-1 ; k < j ; k ++)
				for(int x = (k-1)*k/2 ; x < M ; x ++){
					int y = x + (j-k) * a[i];
					if(y >= M) break;
					if(ck[i-1][k][x])
						ck[i][j][y] = 1,
						g[i][j][y] = j-k;
				}
	for(n = m ; n < N ; n ++)
		if(ck[m][n][n*(n-1)/2]) break;
	if(n == N) return puts("=(");
	printf("%d\n",n);
	for(int i = m , j = n , k = n*(n-1)/2 ; i ; i --){
		for(int p = 0 ; p <= g[i][j][k] ; p ++)
			d[j-p] = a[i];
		int tmp = j;
		j -= g[i][j][k];
		k -= g[i][tmp][k] * a[i];
	}
	for(int i = 1 ; i <= n ; i ++){
		u[i] = i-1;
		for(int j = 1 ; j < i ; j ++) mp[i][j] = 1;
	}
	while(1){
		bool flag = 0;
		for(int i = 1 ; i <= n ; i ++) if(u[i] > d[i])
			for(int j = 1 ; j <= n ; j ++) if(u[j] == d[j])
				for(int k = 1 ; k <= n ; k ++) if(u[k] < d[k]){
					if(!mp[i][j] || !mp[j][k]) continue;
					flag = 1;
					mp[i][j] = 0, mp[j][i] = 1;
					mp[j][k] = 0, mp[k][j] = 1;
					u[i]--, u[k] ++;
				}
		if(!flag) break;
	}
	for(int i = 1 ; i <= n ; i ++, puts(""))
		for(int j = 1 ; j <= n ; j ++)
			printf("%d",(int)mp[i][j]);
}
```



---

## 作者：Tenderfoot (赞：2)

## 题意
给出点的出度的去重集合，要求构造一个最小点数的竞赛图，并存在一个出度序列 
$(d_1,d_2,d_3\cdots d_n)$ 满足任意前缀 $k$ 项和大于 $\dfrac{k\times(k-1)}2$.

## 分析
我们可以得到 $\max |\ V\ |=61$ 即 $ \dfrac{n\times(n-1)}2\leqslant 30n $.
我们可以定义 $f_{n,m,k}$ 为：能否用集合的前 $m$ 项构造出一个 $n$ 个点 $k$ 条边的图，那么
状态转移方程就是
$$
f_{n,m,k}=f_{n-1,m-1,k-a_m}|f_{n-1,m,k-a_m}
$$
我们找出 $\min n$ 并 DFS 这 $n$ 个点的出度. 最后就可以用这 $n$ 个点构造出一个竞赛图。
可以发现一个竞赛图删除一个点以及它的所有边后仍然是一个竞赛图，那么避免冲突每次选择最小出度的点
更新边以及其他点的出度即可。

## 代码
```cpp
#include <bits/stdc++.h>

#define MAXN 1000010
#define Enter puts("")
#define Space putchar(' ')
#define int long long
#define lint __int128
#define Test puts("This is a Test")
#define Test_Begin Enter , puts("Test----------")
#define Test_End Enter , puts("-------------")

static constexpr const int INF(INT_MAX);
static constexpr const int Mod(1e9 + 7);

namespace IO
{
    static inline int const Read()
    {
        int Ans(0);
        char Ch = getchar() , Las = ' ';

        while(!isdigit(Ch))
        {
            if(Ch == '-')
                Las = Ch;

            Ch = getchar();
        }
        while(isdigit(Ch))
        {
            Ans = Ans * 10 + Ch - '0';
            Ch = getchar();
        }

        if(Las == '-')
            Ans = -Ans;

        return Ans;
    }

    template <typename T> static inline void const Write(T x)
    {
        if(x < 0)
            putchar('-') , x = -x;
        if(x >= 10)
            Write(x / 10);

        putchar(x % 10 + '0');
    }
}

using namespace IO;
using namespace std;

namespace Main
{   
    static int n , m;
    static int a[MAXN] , Pos[MAXN] , Ans[MAXN];
    static bool Dp[70][50][2010] , G[70][70];

    static inline bool const Cmp(int a , int b)
    {
        return Ans[a] < Ans[b];
    }

    static inline void const DFS(int _a , int b , int c)
    {
        if(!_a)
            return;

        Ans[_a--] = a[b] , c-= a[b];

        if(Dp[_a][b][c])
            return DFS(_a , b , c);

        return DFS(_a , b - 1 , c);
    }

    static inline void const Work()
    {
        for(register int i(1); i <= n; i++)
            Pos[i] = i;

        for(register int i(1); i <= n; i++)
        {
            sort(Pos + i , Pos + n + 1 , Cmp);

            for(register int j(i + 1); j <= i + Ans[Pos[i]]; j++)
                G[Pos[i]][Pos[j]] = true;

            for(register int j(i + Ans[Pos[i]] + 1); j <= n; j++)
                G[Pos[j]][Pos[i]] = true , Ans[Pos[j]]--;

        }
    }

    static inline signed const Main()
    {
        m = Read() , n = 1;

        for(register int i(1); i <= m; i++)
            a[i] = Read();

        sort(a + 1 , a + m + 1);

        Dp[1][1][a[1]] = true;

        while(n < 62 and (n < m or !Dp[n][m][n * (n - 1) / 2]))
        {
            for(register int i(1); i <= m; i++) 
                for(register int j(n * (n - 1) / 2) , 
                    Lim(n * a[m]); j <= Lim; j++)
                    if(Dp[n][i][j])
                        Dp[n + 1][i][j + a[i]] = Dp[n + 1][i + 1][j + a[i + 1]]
                        = true;

            n++;
        }   

        if(n > 61)
        {
            puts("=(");
            return 0;
        }

        DFS(n , m , n * (n - 1) / 2);
        Write(n) , Enter;
        Work();

        for(register int i(1); i <= n; i++)
        {
            for(register int j(1); j <= n; j++)
                putchar(G[i][j] + '0');
            Enter;
        }

        return 0;
    }
}

signed main()
{
    return Main :: Main();
}
```


---

## 作者：Jay142753869 (赞：2)

~~为了做这道题还去瞄了一眼兰道定理。~~  
设 $i$ 的出度为 $d_i$ ，那么对于 $1 \le i \le n$ 时，$\sum^{i}_{j=1}d_i \le \dfrac{i(i-1)}{2}$。并且当且仅当 $i=n$ 是取到等于。  
那么可以考虑构造一个合法的 $d$ 数组。每个数至少用一次，那么可以做一次背包。然后枚举点的个数，判断是否存在即可。  
之后依然是利用兰道定理来构造出竞赛图。大概步骤如下  

1. 对于 $i>j$ ， $i$ 向 $j$ 连边，得到一个最初始的竞赛图，记它的出度数组为 $u$ 。并且给 $d$ 升序排序。  
1. 找到第一个满足 $d_i>u_i$ 的位置，然后找到最大的 $j$ ，满足 $u_i=u_j$ ，接下来找到第一个满足 $d_k<u_k$ 的位置，有 $j<k$ 且  $u_j+2 \le u_k$ ，那么必然存在 $x$ 满足 $k$ 向 $x$ 连边且 $x$ 向 $j$ 连边。把这两条边翻转即可。
1. 重复上面的过程直到 $d$ 数组与 $u$ 数组完全相同。

 _Code_ 
 ```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 62
#define M 1832
using namespace std;
int n,m,a[N],f[N][N][M],g[N][N][M],d[N],u[N];
bool G[N][N];
int main()
{
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
		scanf("%d",&a[i]);
    sort(a+1,a+m+1);
    f[0][0][0]=1;
    for(int i=1;i<=m;i++)
        for(int j=i;j<N;j++)
            for(int k=i-1;k<j;k++)
                for(int y=k*(k-1)/2,x=(j-k)*a[i]+y;x<M;x++,y++)
					if(f[i-1][k][y]){
                    	f[i][j][x]=1; g[i][j][x]=j-k;
                	}
    for(n=m;n<N&&!f[m][n][n*(n-1)/2];n++);
	    if(n==N){
	        puts("=(");
			return 0;
	    }
    printf("%d\n",n);
    for(int i=m,j=n,k=n*(n-1)/2,x;i;i--)
    {
        for(x=0;x<g[i][j][k];x++)
			d[j-x]=a[i];
        x=k;
		k-=g[i][j][x]*a[i];
		j-=g[i][j][x];
    }
    sort(d+1,d+n+1);
    for (int i=1;i<=n;i++)
    {
        u[i]=i-1;
		for(int j=1;j<i;j++)
			G[i][j]=1;
    }
    while(1){	
		int i,j,k,x;
        for(i=1;i<=n&&d[i]<=u[i];i++);
        if(i>n) break;
        for(j=n;u[j]!=u[i];j--);
        for(k=1;d[k]>=u[k];k++);
        for(x=n;!(G[k][x]&&G[x][j]);x--);
        G[k][x]=0;
		G[x][k]=1;
		G[x][j]=0;
		G[j][x]=1;
		u[k]--;
		u[j]++;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) 
			putchar(G[i][j]+'0');
        printf("\n");
    }
    return 0;
}
 ```

---

## 作者：Caiest_Oier (赞：1)

# [CF850D](https://www.luogu.com.cn/problem/CF850D)

对于竞赛图的一个出度序列 $s$，我们有一个判定合法的条件，即：  

将 $s$ 从小到大排序后，满足对于所有 $j\in[1,n]$，都满足 $\sum_{u=1}^j{sum_u}\ge \frac{j\times(j-1)}{2}$。    

有了这个，我们可以考虑枚举图点数，对其 dp 来检查是否存在相应的出度序列，具体如下：令 $dp_{i,j,k}$ 表示当前枚举到 $i$ 位的出度，$i$ 位出度为 $a_j$，出度和为 $k$，是否存在这样的方案。如果 $dp_{n,m,\frac{n\times(n-1)}{2}}=1$，则合法，否则不合法。  

在找到一个出度序列后，考虑如何构造图。将其从小到大排序，因为竞赛图去一个点还是竞赛图，于是我们去掉出度最小的那个点，只需要让剩下的点仍是竞赛图即可。因为本身这个序列是存在合法的竞赛图方案，所以是一定可以构造出来的。去掉的那个点，它有若干出边和入边，如果将其删掉，则入边起点的出度会减 $1$，而竞赛图的限制是要求前缀和大于某个式子，所以不妨把这几个减出度的放到最后。然而问题在于，如果最后几个减了，排名可能会发生变化。但是因为只减 $1$，所以只用考虑最靠前的那一层点，只有它们减掉 $1$ 后排名会变化，将它们的减 $1$ 提前到对应层最前面即可。   

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[50003],dp[68][32][1803][2],mx,k1,k2,k3,k4,k5;
int v[500003],ans[503][503];
int mk[503];
void calc(int l,int r){
	if(l>r)return;
	memset(mk,0,sizeof(mk));
	for(int i=l+1;i<=l+1+v[l]-1;i++)mk[i]=1;
	for(int i=l+1+v[l];i<=r;i++){
		k5=i;
		while(k5>l+1&&v[k5]==v[k5-1]&&mk[k5-1]==1){
			swap(mk[k5],mk[k5-1]);
			k5--;
		}
	}
	for(int i=l+1;i<=r;i++){
		ans[l][i]=mk[i];
		ans[i][l]=1-mk[i];
	}
	for(int i=l+1;i<=r;i++)v[i]-=(1-mk[i]);
	calc(l+1,r);
	return;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		mx=max(mx,a[i]);
	}
	sort(a+1,a+n+1);
	for(int i=mx+1;;i++){
		if(i>mx*2+2){
			puts("=(");
			return 0;
		}
		dp[1][1][a[1]][0]=1;
		dp[1][1][a[1]][1]=0;
		for(int j=2;j<=i;j++){
			for(int u=1;u<=n;u++){
				for(int p=j*(j-1)/2;p<=i*(i-1)/2;p++){
					dp[j][u][p][0]=dp[j][u][p][1]=0;
					if(p-a[u]<(j-1)*(j-2)/2)continue;
					if(dp[j-1][u][p-a[u]][0]==1){
						dp[j][u][p][0]=1;
						dp[j][u][p][1]=u;
					}
					if(u>1&&dp[j-1][u-1][p-a[u]][0]==1){
						dp[j][u][p][0]=1;
						dp[j][u][p][1]=u-1;
					}
				}
			}
		}
		if(dp[i][n][i*(i-1)/2][0]==0)continue;
		k1=i;
		k2=n;
		k3=i*(i-1)/2;
		while(k1){
			v[k1]=a[k2];
			k2=dp[k1][k2][k3][1];
			k3-=v[k1];
			k1--;
		}
		calc(1,i);
		printf("%d\n",i);
		for(int j=1;j<=i;j++){
			for(int u=1;u<=i;u++)printf("%d",ans[j][u]);
			putchar('\n');
		}
		break;
	}
	return 0;
}
```


---

## 作者：happybob (赞：0)

首先你需要掌握兰道定理，描述如下：

对于一个 $n$ 个点的竞赛图，记 $d_i$ 表示点 $i$ 的出度，不妨设 $d_1 \leq d_2 \leq \cdots \leq d_n$，则一个序列 $d$ 存在符合条件的竞赛图等价于 $\forall 1 \leq i \leq n, \sum \limits_{j=1}^i d_j \geq \dbinom{i}{2}$，且 $i=n$ 时取等。

证明：

必要性显然，因为每个符合条件的竞赛图中选 $i$ 个点，出度之和不小于内部的边数，即 $\dbinom{i}{2}$。

对于充分性，我们给出一个构造性算法。

记目标出度序列从小到大排序后为 $a_1,a_2,\cdots,a_n$。考虑初始图 $G$，对于每个 $i>j$，$i$ 向 $j$ 连一条有向边。则每个点的出度为 $0,1,2,\cdots,n-1$，我们将这个序列记为 $b_1,b_2,\cdots,b_n$。我们需要时刻保证 $\forall 1 \leq i \leq n, \sum \limits_{j=1}^i a_j \geq \sum \limits_{j=1}^i b_j$。显然初始的图符合条件。 接着我们进行若干轮，每轮尝试更改图使得在保证条件成立的前提下逐步调整成目标出度序列。

具体地，每一次，先将 $b$ 从小到大排序，然后找到最小的 $x$ 满足 $a_x > b_x$，找到最小的 $y$ 满足 $a_y < b_y$。$x,y$ 的存在性显然，并且必然有 $y>x$，这是因为考虑第一个 $a_i \neq b_i$ 的位置 $i$，若 $a_i > b_i$ 则 $y>x$，否则 $\sum \limits_{j=1}^i a_j < \sum \limits_{j=1}^i b_j$，与限制矛盾。

进一步地，必然有 $b_y > b_x + 1$，所以必然存在一个点 $z$ 满足目前图中有 $y \rightarrow z$ 并且 $z \rightarrow x$，将两条边反转，$b_x \gets b_x + 1$，$b_y \gets b_y - 1$。容易看出这样操作后仍然符合 $\forall 1 \leq i \leq n, \sum \limits_{j=1}^i a_j \geq \sum \limits_{j=1}^i b_j$。

注意到每次操作后出度序列的曼哈顿距离恰好减 $2$，所以有限次操作内必然会得到一个图的出度序列和目标序列相同。

证毕。

原题在知道前置结论后是很容易的，注意到答案不超过 $61$，考虑记 $f_{i,j,k}$ 表示用了集合从小到大排序的前 $i$ 个数，目前点数为 $j$，目前出度和为 $k$ 是否可行。转移是容易的，记录转移前驱后即可还原可行的出度序列，按照上述定理的构造即可。

---

