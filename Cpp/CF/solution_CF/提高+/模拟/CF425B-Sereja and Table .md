# Sereja and Table 

## 题目描述

Sereja has an $ n×m $ rectangular table $ a $ , each cell of the table contains a zero or a number one. Sereja wants his table to meet the following requirement: each connected component of the same values forms a rectangle with sides parallel to the sides of the table. Rectangles should be filled with cells, that is, if a component form a rectangle of size $ h×w $ , then the component must contain exactly $ hw $ cells.

A connected component of the same values is a set of cells of the table that meet the following conditions:

- every two cells of the set have the same value;
- the cells of the set form a connected region on the table (two cells are connected if they are adjacent in some row or some column of the table);
- it is impossible to add any cell to the set unless we violate the two previous conditions.

Can Sereja change the values of at most $ k $ cells of the table so that the table met the described requirement? What minimum number of table cells should he change in this case?

## 样例 #1

### 输入

```
5 5 2
1 1 1 1 1
1 1 1 1 1
1 1 0 1 1
1 1 1 1 1
1 1 1 1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 4 1
1 0 0 0
0 1 1 1
1 1 1 0
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3 4 1
1 0 0 1
0 1 1 0
1 0 0 1
```

### 输出

```
0
```

# 题解

## 作者：gyh20 (赞：7)

先考虑一个矩阵怎样是合法的。

由于每一个连通块都要是矩形，所以相邻两行要么完全相同要么完全相反。

所以说，任意两行要么完全相同要么完全相反。

这时可以分类讨论：

若 $k>n$，则一定存在一行没有任何数改变，枚举这一行，让其它所有行变为相同或相反。

若 $k\leq n$，则可以直接枚举第一行每一个数是否翻转，然后强制这一行不变。

这样的复杂度是 $O(n^2m)$ 或 $O(2^k nm)$ 的。

虽然这样已经可过了，但事实上可以把 $n,m$ 开到 $5000$，需要一些优化：

$1.$ 计算变换多少次完全相同或相反可以 bitset 优化。

$2.$ 由于最多翻 $k$ 行，所以前 $k+1$ 行一定有一行没有换，所以只用枚举 $k+1$ 行。

时间复杂度可以优化到 $O(\dfrac {nmk}{\omega})$

放一个 $O(n^2m)$ 的代码：

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,a[102][102],k,t,dp[102][2],ans,b[102][102],f[12][1024],sss;
inline void check(re int x,re int sum=0){
	for(re int i=1;i<=n;++i){
		if(i==x)continue;
		memset(dp,0,sizeof(dp));
		for(re int j=1;j<=m;++j){
			if(a[x][j]^a[x][j-1])dp[j][0]=dp[j-1][1],dp[j][1]=dp[j-1][0];
			else dp[j][0]=dp[j-1][0],dp[j][1]=dp[j-1][1];
			++dp[j][a[i][j]];++sss;
		}
		sum+=min(dp[m][0],dp[m][1]);
		if(sum>k)return;
	}
	ans=min(ans,sum);
}
inline void dfs(re int x,re int y){
	if(x==m+1)return check(1,y);
	dfs(x+1,y),a[1][x]^=1,dfs(x+1,y+1),a[1][x]^=1;
}
int main(){
	t=1;
	while(t--){
		n=read(),m=read(),k=read(),ans=1e9;
		for(re int i=1;i<=n;++i)for(re int j=1;j<=m;++j)a[i][j]=read();
		if(n<m){
			for(re int i=1;i<=m;++i)for(re int j=1;j<=n;++j)b[i][j]=a[j][i];
			swap(n,m);
			for(re int i=1;i<=n;++i)for(re int j=1;j<=m;++j)a[i][j]=b[i][j];
		}
		if(k<n){
			for(re int i=1;i<=n;++i)check(i);
			printf("%d\n",(ans>k)?-1:ans);
		}
		else{
			dfs(1,0);
			printf("%d\n",(ans>k)?-1:ans);
		}
	}
}

```


---

## 作者：Mr_Skirt (赞：2)

很巧妙的一道思维题，首先我们我们把整个table看做黑白色块组成的网格图。如果想要让任何连通块都填满一个矩形，那么一个联通矩形四边一定被边界或者不同色块紧紧包围，这个性质必须对所有矩形生效。那么这样一来，每个连通块左右必须是相同高度的异色矩形，上下同理。

那么我们可以按列考虑，假设现在第一列是这样的
$$
\begin{bmatrix}
0\\
1\\
1\\
0\\
1
\end{bmatrix}	
$$

那么要满足条件第二列只有可能是以下两种情况

$$
\begin{bmatrix}
0 & 1\\
1 & 0\\
1 & 0\\
0 & 1\\
1 & 0
\end{bmatrix}	

\begin{bmatrix}
0 & 0\\
1 & 1\\
1 & 1\\
0 & 0\\
1 & 1
\end{bmatrix}
$$

也就是颜色要么翻转要么不翻转。于是我们只需要枚举第一列的样子，然后根据翻不翻转颜色选择最少的步数即可。

但是现在我们的$n,m$最大可以到100，枚举所有状态显然不可行，但是注意到$k$只有10，这提醒我们如果能将规模缩小到10就可以进行枚举了。

如果行数大于$k$，那么枚举肯定超时，但是不枚举肯定没法得到最优答案，怎么办？

这时候我们换一个角度去想，行数大于$k$，如果这时候每一行都至少需要进行一步修改操作，那么步数肯定大于k，这时候我们直接判不可以就行。

反之，我们知道至少有一行是不变的，这样我们就可以更改枚举策略，既然我知道这一行不会变，我们就该用这行进行刚才的最小步数计算即可。

时间复杂度 $O(nm2^k)$，或者$O(n^2m)$

代码：

```cpp
bitset<102> mat[MAXN];
bitset<102> b;

int main() {
#ifdef LOCALLL
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x = read<int>();
            if (x) mat[i].set(j);
        }
    }

    int ans = INF2;
    if (n <= k) {
        // 枚举初始状态
        for (int s = 0; s < (1 << n); s++) {
            int t = 0;
            for (int i = 0; i < m; i++) {
                int cnt = 0;
                for (int j = 0; j < n; j++) {
                    cnt += (mat[j][i] != ((s >> j) & 1));
                }
                t += min(cnt, n - cnt);
            }
            ans = min(ans, t);
        }
    } else {
        // 枚举不动行
        for (int i = 0; i < n; i++) {
            int t = 0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    auto t1 = mat[i] ^ mat[j];
                    t += min(t1.count(), m - t1.count());
                }
            }
            ans = min(ans, t);
        }
    }
    if (ans > k) {
        printf("-1");
    } else {
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：Cocoly1990 (赞：1)

提出一种新的思路。

首先寻找“每个同色极大连通块都是矩形”的性质，~~容易发现~~有两种：

1. 等价于每个 $2\times2$ 正方形内黑色和白色格子的个数都是偶数

2. 等价于每一行颜色都与上一行完全相同或相反。

题解区的两篇题解都是关于性质 2 的做法，不如考虑性质 1.

有一个显然的做法，预处理出所有不合法的 $2\times2$ 正方形，暴力搜索+可行性剪枝。可以通过本题。

如何证明性质 1 成立。~~易证。~~

如果某个联通块不是矩形，感性理解就必然有一块突出来，此时突出部分的 $2\times2$ 正方形就必然无法满足都是偶数的限制条件。

如

```
0110
1111
```

显然可以我们选取
```
01
11
```
这样一个小正方形。

代码易实现。

---

## 作者：VitrelosTia (赞：0)

很神奇的题。

观察到对于相邻两列，要么完全相同，要么完全相反，加强这个想法，每一列要么和第一（$i$）列完全相同，要么和第一（$i$）列完全相反。

一个想法是枚举第一列的状态，因为每一列是独立的，直接对于每一列决策相同/相反即可，复杂度 $O(2^nnm)$，不太行。

考虑 $k$ 的性质，注意到 $k < n$ 时，必然有一行不会动的，此时我们把矩形旋转 $90^{\circ}$，按行做这个问题，那我们可以省去枚举第 $i$ 行的状态转而枚举不会动的第 $i$ 行，复杂度 $O(n^2m)$。

当 $n\le k$ 时再做第一个做法，此时 $n\le 10$ 就过了。

---

## 作者：bsTiat (赞：0)

首先考虑最终答案的形式，一定是黑白块块交替出现。

因此，若第一行状态确定了，其余几行要么与第一行的状态相同，要么与第一行状态相反，所以其余每一行的状态只与当前行状态有关，且不会对其他行产生影响，贪心选择即可。

所以我们很容易得出一个朴素的算法，指数枚举第一行的状态，然后对于其余几行贪心地选择，得出最小操作次数，复杂度为 $ O(nm2^m)$ 。

然后我们随便剪个枝，考虑当前的状态枚举到第 $ i $ 列，那么若前 $ i $ 列的每一行都最优选择，需要的操作次数还是会超过 $ k $ ，那么无论后面如何选，也不会更优，所以剪掉就好了，然后剪完枝跑的飞快，就过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 105,inf=0x3f3f3f3f;
int t,n,m,k,a[N][N],ans,b[N]; 
int calc(int l,int r){
	int res=0,cnt,sum=r-l+1;
		for(int i=1;i<=n;++i){
				cnt=0; 
		for(int j=l;j<=r;++j)
			cnt+=(b[j]==a[i][j]);
		res+=min(cnt,sum-cnt);
		if(res>=ans)return inf;
	}
	return res;
}
void solve(int x,int t,int sum){
	if(sum>=ans)return;
	if(x>m){
		ans=sum;
		return;
	}
	int g;
	for(int i=x;i<=m;++i){
		b[i]=t; g=calc(1,i);
		if(g!=inf) solve(i+1,t^1,g);                                                                                                                                                                       
	}
} 
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&a[i][j]);
	ans=k+1;
	solve(1,1,0);
	solve(1,0,0);	
	printf("%d\n",(ans>k?-1:ans));
}
```


---

