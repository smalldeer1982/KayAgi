# [ABC311G] One More Grid Task

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc311/tasks/abc311_g

$ N\ \times\ M $ のグリッドがあり、上から $ i $ 行目、左から $ j $ 列目のマス $ (i,j) $ には非負整数 $ A_{i,j} $ が書かれています。  
 このグリッドのうち長方領域をひとつ選び、それを $ R $ とします。  
 厳密には、長方領域は以下の手順で選ばれます。

- $ 1\ \le\ l_x\ \le\ r_x\ \le\ N,\ 1\ \le\ l_y\ \le\ r_y\ \le\ M $ なる整数 $ l_x,\ r_x,\ l_y,\ r_y $ を選ぶ。
- このとき、整数 $ i,j $ が $ l_x\ \le\ i\ \le\ r_x $ かつ $ l_y\ \le\ j\ \le\ r_y $ を満たす、またその時に限って、マス $ (i,j) $ は $ R $ に含まれる。
 
適切に $ R $ を選ぶことによって、 $ f(R)\ = $ ( $ R $ 内のマスに書かれた整数の総和 ) $ \times $ ( $ R $ 内のマスに書かれた整数の最小値 ) として達成可能な最大値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N,M\ \le\ 300 $
- $ 1\ \le\ A_{i,j}\ \le\ 300 $
 
### Sample Explanation 1

左上がマス $ (1,1) $ 、右下がマス $ (2,2) $ の長方領域を選ぶことで、 $ f(R)\ =\ (5+4+4+3)\ \times\ \min(5,4,4,3)\ =\ 48 $ が達成でき、これが達成可能な最大値です。

## 样例 #1

### 输入

```
3 3
5 4 3
4 3 2
3 2 1```

### 输出

```
48```

## 样例 #2

### 输入

```
4 5
3 1 4 1 5
9 2 6 5 3
5 8 9 7 9
3 2 3 8 4```

### 输出

```
231```

## 样例 #3

### 输入

```
6 6
1 300 300 300 300 300
300 1 300 300 300 300
300 300 1 300 300 300
300 300 300 1 300 300
300 300 300 300 1 300
300 300 300 300 300 1```

### 输出

```
810000```

# 题解

## 作者：EuphoricStar (赞：11)

考虑一维怎么做。

因为 $a_i \ge 1$，所以保持最小值不变的前提下，区间左右端点扩展是更优的。我们使用单调栈求出左边第一个比 $a_i$ 大的数 $a_{l_i}$，以及右边第一个比 $a_i$ 大的数 $a_{r_i}$，答案即为 $\max\limits_{i = 1}^n a_i \times (\sum\limits_{j = l_i + 1}^{r_i - 1} a_j)$。

二维的情况，我们枚举矩形的上下边界 $[x, y]$，令 $b_i = \min\limits_{j = x}^y a_{j, i}$，就转化成了一维的情况。时间复杂度 $O(n^3)$。

[code](https://atcoder.jp/contests/abc311/submissions/43849584)

---

## 作者：__Dice__ (赞：4)

第一次赛时切 G ，发个题解纪念下。

---------

枚举 $\min$ 值。把所有小于 $\min$ 的值标记为 $1$，大于等于的标记为 $0$。

题目就转换为：在 $\min$ 值固定的情况下，找到一个和最大的全 $0$ 矩阵。和最大意味着在这个矩阵的下线固定的情况下，这个矩阵的面积最大。我们可以使用悬线法（参考[ P1169 [ZJOI2007] 棋盘制作](https://www.luogu.com.cn/problem/P1169)），我们可以得到矩阵的最大左边界和右边界，然后对矩阵的值取个 $\max$，然后再对这个 $\max\times\min$ 取最大就行了。

[$\text{Code}$](https://atcoder.jp/contests/abc311/submissions/43872253)

---

## 作者：zhongpeilin (赞：3)

## 题目大意：
给你一个 $n \times m$ 的矩阵，一个子矩阵的权值为 $\sum_{l1 \leq i \leq l2}\sum_{r1 \leq j \leq r2} \times min(a_{i,j})$  
请问最大子矩阵权值是多少？

## 解题思路：
首先不难想象假设我们枚举了最小值，那么包含比最小值还小的子矩阵是不能选的，所以先枚举一下最小值。然后贪心的想：因为 $a_{i, j}$ 都大于`0`，那么要尽可能的选，所以最后的子矩阵一定是极大的，就是上下左右再扩展就有比我们枚举的最小值还要小的数了。  
由于上面所说的性质，我们再枚举每个位置，算出如果子矩阵的底是这个位置，那么子矩阵和最大是多少。在此，我们用的策略是：在子矩阵的最上面一行尽可能地向上。这之前，我们预处理出每一个点向上，左，右分别能到哪个点。  
到求矩阵最左最右的时候就是 $\max_{up_{i, j} \leq k \leq i} \ L_{k, j}$ 和 $\min_{up_{i, j} \leq k \leq i} \ R_{k, j}$ 最后算一下二维前缀和就可以。  
但这样为什么对了呢？因为答案的子矩阵一定极大，我们的策略是在上面极大的前提下左右尽可能的大，而答案矩阵一定是对于他某个最底层的点，是尽可能向上的，否则就可以向上扩展了，所以我们一定能算出正确答案。

时间复杂度：$O(n^3)$。  

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int sum[305][305];
int n, m, a[305][305], L[305][305], R[305][305], U[305][305];

int ask(int sx, int sy, int fx, int fy){
	return sum[fx][fy] - sum[fx][sy - 1] - sum[sx - 1][fy] + sum[sx - 1][sy - 1];
}
signed main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> a[i][j];
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
		}
	}
	
	int ans = 0;
	for(int minn = 1; minn <= 300; minn++){
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m; j++){
				L[i][j] = R[i][j] = j;
				U[i][j] = i;
			}
		}
		
		for(int i = 1; i <= n; i++){//向左向右
			for(int j = 2; j <= m; j++){
				if(minn <= a[i][j] && minn <= a[i][j - 1]){
					L[i][j] = L[i][j - 1];
				}
			}
			for(int j = m - 1; j >= 1; j--){
				if(minn <= a[i][j] && minn <= a[i][j + 1]){
					R[i][j] = R[i][j + 1];
				}
			}
		}
		
		for(int i = 2; i <= n; i++){//向上
			for(int j = 1; j <= m; j++){
				if(a[i][j] >= minn && a[i - 1][j] >= minn){
					U[i][j] = U[i - 1][j];
				}
			}
		}
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m; j++){
				if(minn <= a[i][j]){
					if(minn <= a[i - 1][j]){
						L[i][j] = max(L[i][j], L[i - 1][j]);
						R[i][j] = min(R[i][j], R[i - 1][j]);
					}
					ans = max(ans, ask(U[i][j], L[i][j], i, R[i][j]) * minn);
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
//万水千山总是情，给个赞赞行不行。

---

## 作者：CaiZi (赞：2)

## [ABC311G] One More Grid Task 题解
**[题目链接](https://www.luogu.com.cn/problem/AT_abc311_g)**
### 题目分析
题意：求一个矩阵的子矩阵的和乘以最小值的最大值。

注意到 $n,m\le300$，我们应该使用 $3$ 次方级别的算法。

我们考虑枚举矩阵的上界 $x$ 和下界 $y$，于是我们令 $b_i=\min\limits_{j=x}^{y}a_{j,i}$，再令 $c_i=\sum\limits_{j=x}^{y}a_{j,i}$。

我们知道 $x=y$ 时 $b_i=c_i=a_{x,i}$，然后每次把 $y\gets y+1$，相当于将矩阵向下拓宽 $1$ 行。每次操作后，我们令 $b_i\gets\min\{b_i,a_{y,i}\}$，再令 $c_i\gets c_i+a_{y,i}$，每次操作都可以 $O(m)$ 计算。

于是我们现在知道了在枚举的范围内，每列的最小值与和。原来子矩阵的每一列都被压缩成了一个数，整个子矩阵变成一个序列，这是对我们解答没有影响的，因为每一列在计算时都是一个整体。

对于每对 $(x,y)$，我们需要求的就是：
$$\max\limits_{1\le i\le j\le m}(\min\limits_{k=i}^{j}b_k\times\sum\limits_{k=i}^{j}c_k)$$
先使用前缀和，令 $d_i=\sum\limits_{j=1}^{i} c_j$。再使用单调栈即可 $O(m)$ 计算。

最终时间复杂度为 $O(n^2m)$，注意使用栈前先加入一个 $0$，以防 RE。
### 代码展示
代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[301][301],b[301],c[301],d[301],w,t;
stack<int>s;
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	s.push(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	for(int x=1;x<=n;x++){
		for(int i=1;i<=m;i++){
			b[i]=LONG_LONG_MAX;
			c[i]=0;
		}
		for(int y=x;y<=n;y++){
			for(int i=1;i<=m;i++){
				b[i]=min(b[i],a[y][i]);
				c[i]=c[i]+a[y][i];
				d[i]=d[i-1]+c[i];
				while(s.size()>=2&&b[s.top()]>=b[i]){
					w=b[s.top()];
					s.pop();
					t=max(t,w*d[i-1]-w*d[s.top()]);
				}
				s.push(i);
			}
			while(s.size()>=2){
				w=b[s.top()];
				s.pop();
				t=max(t,w*d[m]-w*d[s.top()]);
			}
		}
	}
	cout<<t;
	return 0;
}
```
**[提交记录](https://www.luogu.com.cn/record/163916421)**

---

## 作者：KingPowers (赞：2)

[题目链接](https://www.luogu.com.cn/problem/AT_abc311_g)

感觉是非常典的一道题。

先考虑如果是一个序列而非矩形该怎么做。由于题目中的 $a_i$ 非负，当我们钦定最小值为序列中的某个位置时，区间的左右端点肯定是能扩展就扩展。记 $l_i$ 为 $i$ 左边最靠左的大于等于 $a_i$ 的位置，$r_i$ 为 $i$ 右边最靠右的大于等于 $a_i$ 的位置，那么答案即为：

$$
\max_{i=1}^na_i\times(s_{r_i}-s_{{l_i}-1})
$$

$s$ 为序列的前缀和，$l$ 和 $r$ 均可以使用单调栈轻松维护出来，时间复杂度 $O(n)$。

对于矩形的情况，我们枚举最后答案对应的子矩形的上下边界 $u$ 和 $d$，考虑记 $b_i=\min_{j=u}^da_{j,i}$，不难发现我们其实将问题转化为了一维的情况：维护出每个 $b_i$ 对应的 $l_i$ 和 $r_i$，按照上面的做法统计答案即可，其中 $b_i$ 可以使用 st 表求出。

时间复杂度 $O(n^2m)$。

[代码链接](https://atcoder.jp/contests/abc311/submissions/45506898)

---

## 作者：AC_love (赞：1)

考虑一维怎么做：

用单调栈维护每个数左右第一个比它小的数出现的位置。

每个数作为最小值时的最大答案是这个数乘上它作为最小值的区间的区间和。

对所有数都求一遍取 $\max$ 即可。

这道题是二维，考虑压成一维来做。

只要枚举上下边界，然后把中间压成一维即可。

复杂度 $O(n^3)$。

[code](https://atcoder.jp/contests/abc311/submissions/59996729)

---

## 作者：wth2026 (赞：1)

# 题目大意
给我们一个矩阵，要求一个子矩阵，使得其值的和与最小值的乘积最大。求这个最大值。
# 题目思路
首先你先要保证你会前缀和、单调栈与 ST 表。

使用单调栈维护枚举上下界，再使用前缀和与 ST 表快速求出子矩阵中的值的和与子矩阵中的值的最大值即可。

时间复杂度：$O(\max(n \times m), n \times \max(m, n \times \max(m, m \times \log n))) = O(n^3 \times \log n)$。
# AC Code
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f
#define lnf 0x3f3f3f3f3f3f3f3f

#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Os")
#pragma GCC optimize("Ofast")

using namespace std;

#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1 ++)
char *p1, *p2, buf[(1 << 20) + 5];

inline int read() {
	int x = 0, f = 1;
	char c = gc();
	
	while (!isdigit(c)) {
		if (c == '-') {
			f = -1;
		}
		
		c = gc();
	}
	
	while (isdigit(c)) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = gc();
	}
	
	return x * f;
}

void write(int k) {
	if (k < 0) {
		putchar('-');
		k = -k;
	}
	
	if (k > 9) {
		write(k / 10);
	}
	
	putchar(k % 10 + 48);
}

const int N = 300;

void init();

int n, m, a[N + 5][N + 5], pre[N + 5], erpre[N + 5], minn[N + 5], ans, st[N + 5], r;

signed main() {
//	init();
//	cin >> n >> m;
	n = read();
	m = read();
	
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
//			cin >> a[i][j];
			a[i][j] = read();
		}
	}
	
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			pre[j] = 0;
			minn[j] = lnf;
		}
		
		for (int j = i; j <= n; ++ j) {
			for (int k = 1; k <= m; ++ k) {
				pre[k] += a[j][k];
				erpre[k] = erpre[k - 1] + pre[k];
				minn[k] = min(minn[k], a[j][k]);
			}
			
			for (int k = 1; k <= m + 1; ++ k) {
				while (r && minn[st[r]] >= minn[k]) {
					ans = max(ans, (erpre[k - 1] - erpre[st[r - 1]]) * minn[st[r]]);
					-- r;
				}
				
				st[++ r] = k;
			}
			
			r = 0;
		}
	}
	
	write(ans);
	return 0;
}

void init() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
```

---

## 作者：FBW2010 (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc311_g)

# 题意

给定一个整数矩阵，定义一个子矩阵的权值为它所有数的最小值乘上和，求所有子矩阵权值的最大值。

# 思路

由于要对所有矩阵计数，我们可以使用一个常见的思路：枚举上下端点，将矩阵拍成一个一维数组。令 $sum_i$ 为第 $i$ 列所有数的和，$min_i$ 为第 $i$ 列所有数的最小值。于是问题便转化为了求一个区间上每个子区间的和与最小值的乘积的最大值。

我们考虑贪心一下：一段区间在最小值不变时，向两边拓展一定是更优的。于是当 $min_i$ 为最小值时，求出左边最远能拓展到的 $l_i$，与右边最远能拓展到的 $r_i$，他对答案的贡献便是：
$$
a_i\times\sum_{j=l_i}^{r_i}sum_j
$$
$sum$ 可以用前缀和维护，然后将所有情况取最大值即可。

那怎么线性求 $l_i$ 和 $r_i$ 呢？我们回顾一下定义，$l_i$ 表示从 $min_{l_i}$ 到 $min_{i-1}$ 都小于等于 $min_i$。于是不难想到用单调栈维护。$r_i$ 反过来就行了，这里就不细说。

# 代码

先枚举上下端点，每次 $min$ 和 $sum$ 可以由上次状态 $O(m)$ 转移，再求出 $sum$ 的前缀和，接着正着用单调栈扫一遍求出 $l$，再倒着扫一遍求出 $r$，最后枚举 $1$ 到 $m$ 分别为最小值时的权值，取最大即可。这样复杂度为 $O(n^2m)$，可以通过此题。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=305;
int n,m,top,l[N],r[N],st[N],sum[N],minn[N],a[N][N];
long long ans,sum2[N];
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){ //初始化 
			minn[j]=N;
			sum[j]=0;
		}
		for(int j=i;j<=n;j++){
			for(int k=1;k<=m;k++){
				minn[k]=min(minn[k],a[j][k]); //更新 
				sum[k]+=a[j][k];
				sum2[k]=sum2[k-1]+sum[k]; //求前缀和 
			}
			top=0;
			st[0]=0;
			for(int k=1;k<=m;k++){ //正着单调栈 
				while(top&&minn[st[top]]>=minn[k])top--;
				l[k]=st[top]+1;
				st[++top]=k;
			}
			top=0;
			st[0]=m+1;
			for(int k=m;k>=1;k--){ //倒着单调栈 
				while(top&&minn[st[top]]>=minn[k])top--;
				r[k]=st[top]-1;
				st[++top]=k;
			}
			for(int k=1;k<=m;k++){
				ans=max(ans,minn[k]*(sum2[r[k]]-sum2[l[k]-1])); //统计答案 
			}
		}
	}
	printf("%lld",ans);
	return 0;
}  
```

---

## 作者：123zbk (赞：0)

**题目大意**:

求出在一个矩阵中，所有子矩阵的和乘以最小值的最大值。

**主要思路**:

我们可以枚举最小值 $\min$。因为 $A_{i,j} \ge 1$，此时需要我们找到和最大的一个矩阵，使其每一个元素都大于 $\min$ 。

因为 $n$ 的范围比较小，考虑枚举矩形的上下界，并动态地求出在这中间每一列的最小值，这样我们就可以把矩形压成一行。

之后就简单了，利用单调栈维护出每一列可以延伸到的最左和最右的位置，每一次都求一遍最大值即可。

时间复杂度 $O(n^2)$。

**code**：


```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=505;
int n,m,mn[N],s[N],sum[N],l[N],r[N],st[N],a[N][N];
ll ans;
int main()
{ 		
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
		}
	} 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			mn[j]=1e9;
			s[j]=0;
		} 
		for(int j=i;j<=n;j++){// i~j
			for(int k=1;k<=m;k++){
				mn[k]=min(mn[k],a[j][k]);//第k列最小值
				s[k]+=a[j][k];
				sum[k]=sum[k-1]+s[k];
			} 
			int tp=0;
			for(int k=1;k<=m;k++){
				while(tp and mn[k]<=mn[st[tp]]) tp--;
				l[k]=(tp==0)?1:st[tp]+1;
				st[++tp]=k;//最左边满足>=mn[k]的
			}
			tp=0;
			for(int k=m;k>=1;k--){
				while(tp and mn[k]<=mn[st[tp]]) tp--;
				r[k]=(tp==0)?m:st[tp]-1;
				st[++tp]=k;
			}
			for(int k=1;k<=m;k++){
				ans=max(ans,(ll)mn[k]*(sum[r[k]]-sum[l[k]-1]));
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

记得之前的时候场上已经口胡过这一题了，不知道为什么没补。

很板的悬线法。

枚举最小值 $k$，以 $a_{i,j}$ 是否大于等于 $k$ 将矩阵转变为一个 $01$ 矩阵，枚举一个 $i$，设 $dp_j$ 为 $(i,j)$ 位置与其上方有多少个 $1$，用单调栈处理出左右第一个比 $a_{i,j}$ 小的 $l$ 和 $r$，这是以 $dp_j$ 为高度时矩形的最大宽度，二维前缀和求和即可。

易证明这样转移肯定是最优的。

### $\text{code}$

```cpp
int n,m;

int a[maxn][maxn];

int v[maxn][maxn];

int l[maxn][maxn],r[maxn][maxn],up[maxn][maxn];
int sum[maxn][maxn];
int fl[maxn][maxn],fr[maxn][maxn];

int ans;

int calc(int x1,int y1,int x2,int y2){
	return sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][y1-1];
}

void solve(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
		}
	}
	for(int i=1;i<=300;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=m;k++){
				if(a[j][k]<i){
					v[j][k]=1;
				}
				else{
					v[j][k]=0;
				}
			}
		}
		int res=0;
		for(int k=1;k<=n;k++){
			for(int h=1;h<=m;h++){
				if(!v[k][h]){
					l[k][h]=l[k][h-1]+1;
				}
				else{
					l[k][h]=0;
				}
			}
		}
		for(int k=1;k<=n;k++){
			for(int h=m;h>=1;h--){
				if(!v[k][h]){
					r[k][h]=r[k][h+1]+1;
				}
				else{
					r[k][h]=0;
				}
			}
		}
		for(int k=1;k<=n;k++){
			for(int h=1;h<=m;h++){
				if(!v[k][h]){
					fl[k][h]=l[k][h];
					fr[k][h]=r[k][h];
					up[k][h]=up[k-1][h]+1;
					if(!v[k-1][h]&&k>=2){
						fl[k][h]=min(fl[k][h],fl[k-1][h]);
						fr[k][h]=min(fr[k][h],fr[k-1][h]);
					}
					res=max(res,calc(k-up[k][h]+1,h-fl[k][h]+1,k,h+fr[k][h]-1));
				}
				else up[k][h]=0;
			}
		}
		ans=max(ans,res*i);
	}
	write(ans);
	return ;
}
```

---

## 作者：naroto2022 (赞：0)

# ABC311G 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/AT_abc311_g)

### 题意

给定一个矩阵，求一个子矩阵是的子矩阵中的数字总和与子矩阵中的最小值的乘积最大，输出乘积即可。

### 前置知识

1. 二位前缀和。
2. [单调栈。](https://www.luogu.com.cn/problem/P5788)
3. [单调队列。](https://www.luogu.com.cn/problem/P1886)

对于二位前缀和，其实很简单，看个图就懂了。

![](https://cdn.luogu.com.cn/upload/image_hosting/kqy7ixfj.png)

上图中红色面积=橙色面积+整个的面积-(橙色面积+蓝色面积)-(橙色面积+绿色面积)。

设统计二维前缀和的数组 $s[i][j]$ 为统计 $\begin{aligned} \sum_{i=1}^n\sum_{j=1}^n a[i][j] \end{aligned}$。

则 $sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j]$。

而一个以 $(x,y)$ 为左上的顶点，$(xx,yy)$ 为右下的顶点的矩形的总和为 $sum[x-1][y-1]+sum[x2][y2]-sum[x-1][y2]-sum[x2][y-1]$。

### 思路

首先先考虑一维的，对于一个区间，显然在最小值不变的情况下往左右扩张是最优的，于是就可以用两个单调栈来分别算出左边第一个比 $a_i$ 大的数 $a_{l_i}$，以及右边第一个比 $a_i$ 大的数 $a_{r_i}$，于是这时一维的答案为 $\begin{aligned}\max_{i=1}^n a_i\times\sum_{j=l_i+1}^{r_i-1} a_i\end{aligned}$。

于是开始考虑二维，首先能想到的就是把二维压为一维。

发现题目要求的数只有最小值是变化的，子矩阵的和可以根据前置知识里的二位前缀和来求，接下来考虑如何维护最小值。

其实我们可以模拟下二维里左右扩张的过程，假设有一个第 $i$ 列里从第 $k$ 行到第 $j$ 行的一列，其最小值为 $min_i$，则要找左边第一个最小值比 $min_i$ 大的第 $l_i$ 列，和右边第一个最小值比 $min_i$ 大的第 $r_i$ 列，然后答案即为 $min_i$ 乘上子矩阵中的数字和。

那么 $min$ 数组该怎么求呢？如果暴力遍历的话时间复杂度为 $O(n^4)$，显然会炸，于是考虑设一个数组 $b[i][j][k]$ 表示第 $i$ 列中第 $j$ 个数到第 $k$ 个数的最小值，而这个数组单调队列预处理一下即可将时间复杂度降为 $O(n^3)$，还可以接受。

那么代码应该有能力的人就可以打了。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<stack>
#define ll long long
using namespace std;
const int MN=305;
ll n,m,a[MN][MN],b[MN][MN][MN],s[MN][MN],ans,l,r,p1[MN],p2[MN];
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}return x*f;}
ll gs(ll x, ll y, ll x2, ll y2){return s[x-1][y-1]+s[x2][y2]-s[x-1][y2]-s[x2][y-1];}//求子矩阵的和。 
int main(){
	n=read();m=read();
	for(int i=1; i<=n; i++) for(int j=1; j<=m; j++){
		a[i][j]=read();
		s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];//维护二位前缀和。 
	}
	for(int j=1; j<=m; j++){//单调队列预处理 b 数组。 
		for(int k=1; k<=n; k++){
			deque<ll> q[MN];//再循环里定义可以不用清空，下面单调栈同理。 
			for(int i=1;i<=n;i++){
				while(!q[j].empty()&&a[i][j]<=a[q[j].back()][j]) q[j].pop_back();
				while(!q[j].empty()&&q[j].front()<=i-k) q[j].pop_front();
				q[j].push_back(i);
				if(i>=k) b[j][i-k+1][i]=a[q[j].front()][j];
			}
		}
	}
	for(int k=1; k<=n; k++){//单调栈左右扩张，统计答案 
		for(int j=k; j<=n; j++){
			stack<ll> s1,s2;
			for(int i=m; i>=1; i--){
				while(!s1.empty()&&b[s1.top()][k][j]>=b[i][k][j]) s1.pop();
				s1.empty()?p1[i]=m+1:p1[i]=s1.top();
				s1.push(i);
			}
			for(int i=1; i<=m; i++){
				while(!s2.empty()&&b[s2.top()][k][j]>=b[i][k][j]) s2.pop();
				s2.empty()?p2[i]=0:p2[i]=s2.top();
				s2.push(i);
			}
			for(int i=1; i<=m; i++){
				r=p1[i]-1;
				l=p2[i]+1;
				ans=max(ans,gs(k,l,j,r)*b[i][k][j]);
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：_WHITE_NIGHT_ (赞：0)

~~感觉大佬们讲的都好简略，对于像我这样的菜鸟十分不友好。~~

所以写一篇对~~和我一样的~~小可爱的题解......

本篇题解讲的是个人的思路。


------------

#### 前置知识：

[P5788 【模板】单调栈](https://www.luogu.com.cn/problem/P5788)；

[P3865 【模板】ST 表](https://www.luogu.com.cn/problem/P3865)；

二维前缀和（~~Luogu 怎么没有板子题啊？？？~~）。

------------


首先，观察题目给出的式子：

$$
\max_{1\leq l_1\leq r_1\leq n,1\leq l_2\leq r_2\leq m}
(\sum_{l_1\leq i\leq r_1,l_2\leq j\leq r_2}a_{i,j} \times\min_{l_1\leq i\leq r_1,l_2\leq j\leq r_2}a_{i,j})
$$

思考暴力。如果单纯枚举左上与右下两个点的话就已经有 $O(n^4)$ 的时间复杂度，更别说进行 $\min_{l_1\leq i\leq r_1,l_2\leq j\leq r_2}a_{i,j}$ 与 $\sum_{l_1\leq i\leq r_1,l_2\leq j\leq r_2}a_{i,j}$ 的计算了。

思考优化。首先，很明显，$\min_{l_1\leq i\leq r_1,l_2\leq j\leq r_2}a_{i,j}$ 与 $\sum_{l_1\leq i\leq r_1,l_2\leq j\leq r_2}a_{i,j}$是可以进行预处理，然后 $O(1)$ 进行求解的。$\sum_{l_1\leq i\leq r_1,l_2\leq j\leq r_2}a_{i,j}$ 可以通过**二维前缀和**进行优化，$\min_{l_1\leq i\leq r_1,l_2\leq j\leq r_2}a_{i,j}$ 可以通过 **ST 表（亦或是线段树）** 进行优化。

但是，枚举左上与右下方的端点依然会 TLE，再次思考该如何进一步优化。

观察发现，最外层套的是一个 $\max$，里面是一个 $\min$，并且取值范围是**相同的**，很容易就想到**单调栈**。因为单调栈是一种擅长维护区间最值问题（一般可以通过倒序循环找到每一个数之后的最值）。再次进行优化（用正向循环和逆向循环记录下拥有最值的左端点与右端点的坐标），只需要枚举**一个端点的坐标即可**。

枚举一个端点的时间复杂度为 $O(n^2)$，每次使用单调栈正逆向循环时间复杂度为 $O(n)$。

预处理 ST 表与二维前缀和时间复杂度为 $O(\log_2n \times n^2+n)$，可以通过此题，总共复杂度约为 $O(n^3+\log_2n\times n^2 + n)$。

具体代码其他题解里面大佬们都给出来了，这里就不贴了。



------------

Update：更新了为何能够使用单调栈的原因。

另：感谢管理员[wsc2008](https://www.luogu.com.cn/user/288866)对本人的指导，在此深表谢意。

---

## 作者：0xyz (赞：0)

- 给定一个 $n\times m$ 的矩形 $a$，求其所有子矩阵的元素和乘上最小元素的最大值。$1\le n,m,a_{i,j}\le 300$。

其实这一题思维难度很低，非常板，我觉得甚比 F 题还简单，只是官方题解做法太麻烦了。

注意到 $a_{i,j}\le 300$，所以直接枚举子矩阵的最小值。然后我们容易知道哪些元素不能选入子矩阵。由于 $a_{i,j}$ 都是正数，我们要求最大带权子矩阵，就是要扩展到四个方向都不能再扩展（即再扩展会超过边界或者包含不能选入的元素），这个子矩阵才有可能权值之和最大。

于是想到 $O(nm)$ 的[悬线法](https://www.luogu.com.cn/problem/P4147)。以下介绍一下它的大致流程。我们维护一个阻止矩形向上扩展的 $(x,y)$（或者原本矩形的上边界），那么元素和最大的矩形一定是这样一个 $(x,y)$ 垂下一根线，然后在这根线左右边分别扩展到无法扩展。所以对于一个点 $(i,j)$，令 $h_{i,j}$ 代表从格子 $(i,j)$ 最多能往上多少格（不包括自己），$l_{i,j}$ 代表 $(i,j-h_{i,j})$ 到 $(i,j)$ 这条线最多能往左多少格（包括自己），$r_{i,j}$ 表示这条线最多能往右多少格（包括自己）。我们要怎么求这些值呢？首先我们初始化 $l_{i,j}$ 和 $r_{i,j}$ 分别为第 $i$ 行中格子 $(i,j)$ 能往左/右多少格（包括自己）。然后我们从上往下扫每一行，维护 $h_{i,j}$，并用 $l_{i-1,j}$ 和 $r_{i-1,j}$ 更新 $l_{i,j}$ 和 $r_{i,j}$。

在这题中，此时我们就可以知道这个矩形的四角坐标，然后用二维前缀和 $O(1)$ 算出实际元素之和，进而更新答案。总时间复杂度 $O(vnm)$，其中 $v$ 是 $a_{ij}$ 的值域，轻轻松松通过此题。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll _=310;
ll n,m,a[_][_],s[_][_],h[_][_],l[_][_],r[_][_],ans;
inline ll sum(ll lx,ll rx,ll ly,ll ry){
	return s[rx][ry]+s[lx-1][ly-1]-s[lx-1][ry]-s[rx][ly-1];
}
inline void line(ll x){
	ll res=0;
	memset(l,0,sizeof(l));
	memset(r,0,sizeof(r));
	memset(h,0,sizeof(h));
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			if(a[i][j]>=x)l[i][j]=l[i][j-1]+1;
	for(ll i=1;i<=n;i++)
		for(ll j=m;j>=1;j--)
			if(a[i][j]>=x)r[i][j]=r[i][j+1]+1;
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++){
			if(i>1&&a[i][j]>=x&&a[i-1][j]>=x){
				h[i][j]=h[i-1][j]+1;
				l[i][j]=min(l[i][j],l[i-1][j]);
				r[i][j]=min(r[i][j],r[i-1][j]);
			}
			res=max(res,sum(i-h[i][j],i,j-l[i][j]+1,j+r[i][j]-1));
		}
	ans=max(ans,res*x);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++){
			cin>>a[i][j];
			s[i][j]=a[i][j]+s[i-1][j]+s[i][j-1]-s[i-1][j-1];
		}
	for(ll i=1;i<=300;i++)line(i);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

这次 G 怎么也是典啊。

求一个矩阵和乘上矩阵最小值，很容易想到[棋盘制作](https://www.luogu.com.cn/problem/P1169)。考虑怎么转换到这个问题上，发现可以枚举最小值 $k$，根据 $a_{i,j}$ 是否 $\geq k$ 变成一个 $01$ 矩阵。然后就和上题一样做就行了。

具体做法，考虑枚举一行 $i$，设 $f_j$ 为 $(i,j)$ 位置及它上面有多少个连续的 $1$。$f$ 可以从上一行转移过来。然后用单调栈处理出左右第一个比 $f_j$ 小的位置 $l_j,r_j$。这即为以 $f_j$ 为矩形高度时，矩形最大能取到的宽度。最后再用二维前缀和维护即可。

code：

```cpp
int n,m,e[N][N],f[N],d[N],c[N];
int top,st[N];
ll s[N][N];
bool pd[N][N];
void Yorushika(){
	scanf("%d%d",&n,&m);
	rep(i,1,n){
		rep(j,1,m){
			scanf("%d",&e[i][j]);
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+e[i][j];
		}
	}
	ll ans=0;
	rep(k,1,301){
		rep(i,1,n){
			rep(j,1,m){
				pd[i][j]=e[i][j]<k;
			}
		}
		mems(f,0);
		rep(i,1,n){
			top=0;
			rep(j,1,m){
				d[j]=0,c[j]=m+1;
				if(pd[i][j])
					f[j]=0;
				else 
					f[j]++;
			}
			rep(j,1,m){
				while(top&&f[st[top]]>f[j])
					c[st[top--]]=j;
				st[++top]=j;
			}
			top=0;
			drep(j,m,1){
				while(top&&f[st[top]]>f[j])
					d[st[top--]]=j;
				st[++top]=j;
			}
			rep(j,1,m){
				ans=max(ans,(s[i][c[j]-1]-s[i-f[j]][c[j]-1]-s[i][d[j]]+s[i-f[j]][d[j]])*k);
			}
		}
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：LJ07 (赞：0)

如果是一维就可以直接单调栈。

```cpp
U(i, 1, m) {
  while (top && b[st[top]] >= b[i]) {
    ans = max(ans, (s[i - 1] - s[st[top - 1]]) * b[st[top]]);
    --top;
  }
  st[++top] = i;
}
while (top) {
  ans = max(ans, (s[m] - s[st[top - 1]]) * b[st[top]]);
  --top;
}
```

那怎么把两维转化为一维呢？暴力枚举上边界和下边界，直接将二维状物压成一维解决即可。

```cpp
const int N(300);
int n, m, c[N + 5][N + 5];
long long a[N + 5];
int b[N + 5];
int st[N + 5], top;
long long s[N + 5];

int main() {
//  freopen("input.in", "r", stdin);
  rd(n), rd(m);
  U(i, 1, n) {
    U(j, 1, m) {
      rd(c[i][j]);
    }
  }
  long long ans(0);
  U(l, 1, n) {
    U(i, 1, m) {
      a[i] = 0, b[i] = 1e9;
    }
    U(r, l, n) {
      U(i, 1, m) {
        b[i] = min(b[i], c[r][i]);
        a[i] += c[r][i];
      }
      U(i, 1, m)  {
        s[i] = s[i - 1] + a[i];
      }
      U(i, 1, m) {
        while (top && b[st[top]] >= b[i]) {
          ans = max(ans, (s[i - 1] - s[st[top - 1]]) * b[st[top]]);
          --top;
        }
        st[++top] = i;
      }
      while (top) {
        ans = max(ans, (s[m] - s[st[top - 1]]) * b[st[top]]);
        --top;
      }
    }
  }
  printf("%lld\n", ans);
  return 0;
}

```

---

## 作者：banned_gutongxing (赞：0)

## 题目思路

### 算法一

我们可以考虑直接枚举左上角，枚举右下角，暴力求和以及暴力求最小值。

时间复杂度：$O(n^3m^3)$。

### 算法二

算法一显然不行。我们可以提前预处理，用上数据结构（比如说树状数组、线段树树），直接求最小值和和。

时间复杂度：$O(n^2m^2\log n\log m)$。

### 算法三

算法二显然也不行。考虑优化。

我们知道：任何矩阵的问题都可以压缩成一维问题。即枚举上界、枚举下界，求方案数。

预处理后，我们可以记录 $left_i$、$right_i$ 分别代表能延伸的最左边，能延伸的最右边。

直接使用单调栈维护即可。

时间复杂度：$O(n^2m\log n)$。

## 代码

```cpp
// LUOGU_RID: 161862093
#include<bits/stdc++.h>
#define int long long
#define left _zqh_
#define right flying_hq
using namespace std;
const int MAXN = 320;
const int LOGN = log2(MAXN)+5;
int n,m,matrix[MAXN][MAXN],ans;
void read(int &x){
	x = 0;int p = 1;char ch;
	do{
		ch = getchar();
		if(ch=='-') p = -1;
	}while(!isdigit(ch));
	while(isdigit(ch)){
		x*=10;
		x+=ch-'0';
		ch = getchar();
	}
	x*=p;
}
int sum[MAXN][MAXN],now[MAXN],left[MAXN],right[MAXN],q[MAXN],minn[MAXN];
class Segmenttree{
	private:
		struct segment{
			int l,r,min=0X3F3F3F3F;
		}tree[MAXN<<3];
		void pushup(int id){
			tree[id].min = min(tree[id*2].min,tree[id*2+1].min);
		}
	public:
		void build(int k,int l,int r){
			tree[k].l = l;
			tree[k].r = r;
			if(l==r) return;
			int mid = (l+r)>>1;
			build(k*2,l,mid);
			build(k*2+1,mid+1,r);
		}
		void change(int k,int p,int q){
			if(tree[k].l>p||tree[k].r<p) return;
			if(tree[k].l>=p&&tree[k].r<=p){
				tree[k].min = q;
				return; 
			}
			change(k*2,p,q);
			change(k*2+1,p,q);
			pushup(k);
		}
		int getmin(int k,int l,int r){
			if(tree[k].l>r||tree[k].r<l) return 0x3f3f3f3f;
			if(tree[k].l>=l&&tree[k].r<=r){
				return tree[k].min; 
			}
			return min(getmin(k*2,l,r),getmin(k*2+1,l,r));
		}
}tree[MAXN];
signed main(){
	read(n);read(m);
	for(int i = 1;i<=m;i++) tree[i].build(1,1,n);
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=m;j++){
			read(matrix[i][j]);
			sum[i][j] = sum[i-1][j]+matrix[i][j];
			tree[j].change(1,i,matrix[i][j]);
		}
	}
	for(int i = 1;i<=n;i++){
		for(int j = i;j<=n;j++){
			if(i == 1&&j== 2){
				int k = 0;
			}
			for(int k = 1;k<=m;k++){
				now[k] = sum[j][k]-sum[i-1][k];
				q[k] = q[k-1]+now[k];
				minn[k] = tree[k].getmin(1,i,j);
			}
			stack<pair<int,int>> st;
			for(int k = 1;k<=m;k++){
				while(!st.empty()&&st.top().second>=minn[k]) st.pop();
				if(st.empty()){
					left[k] = 1;
				}else{
					left[k] = st.top().first+1;
				}
				st.push({k,minn[k]});
			}
			while(!st.empty()){
				st.pop();
			}
			for(int k = m;k>=1;k--){
				while(!st.empty()&&st.top().second>=minn[k]) st.pop();
				if(st.empty()){
					right[k] = m;
				}else{
					right[k] = st.top().first-1;
				}
				st.push({k,minn[k]});
			}
			for(int k = 1;k<=m;k++){
				ans = max(ans,(q[right[k]]-q[left[k]-1])*minn[k]);
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

