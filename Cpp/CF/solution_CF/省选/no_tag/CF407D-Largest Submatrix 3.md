# Largest Submatrix 3

## 题目描述

给定一个$n \times m$的正整数矩阵，求其中最大的满足其中不存在两个位置数值相等的子矩阵大小。

## 样例 #1

### 输入

```
3 3
1 3 1
4 5 6
2 6 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3 4
5 2 3 1
3 3 5 3
4 4 4 5
```

### 输出

```
4
```

## 样例 #3

### 输入

```
2 6
1 2 3 4 5 6
8 6 7 8 9 1
```

### 输出

```
8
```

# 题解

## 作者：Sunny郭 (赞：8)

基于不随机数据和值域大小，正确性在于生日悖论，可以被 hack，但是可以过 cf 数据。

直接枚举每个左上角 $(i,j)$，然后枚举矩形长，矩形宽是随着矩形长递减的，可以维护最大右端点。根据生日悖论，在不均匀不随机数据下，长宽的乘积是 $O(n)$ 的，在时间复杂度表现良好甚至比 $O(n^3)$ 还快。

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define pi pair<int,int>
#define F first
#define S second
#define mp make_pair
using namespace std;
using ll = long long;
using db = double;
const int N = 407, V = N * N;

int i, j, k, n, m, x;
int l, r, s, p;
int a[N][N], u[V];

int main() {
//	freopen("c.in", "r", stdin);
//	freopen("c.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(i = 1; i <= n; i++) for(j = 1; j <= m; j++) scanf("%d", &a[i][j]);
	for(i = 1; i <= n; i++) for(j = 1; j <= m; j++) {
		l = i; r = j - 1;
		while(r < m && !u[a[i][r + 1]]) ++r, ++u[a[i][r]];
		s = max(s, r - j + 1);
		while(l < n && r >= j) {
			++l; p = j - 1;
			while(p < r) {
				while(p < r && !u[a[l][p + 1]]) ++p, ++u[a[l][p]];
				if(p == r) break;
				for(k = i; k <= l - 1; k++) u[a[k][r]]--; --r;
			}
			if(s >= (n - i + 1) * (r - j + 1)) break;
			s = max(s, (l - i + 1) * (r - j + 1));
		}
		while(r >= j) {
			for(k = i; k <= l; k++) u[a[k][r]]--; --r;
		}
	}
	printf("%d\n", s);
	return 0;
}


```

---

## 作者：Purslane (赞：5)

# Solution

哥你真确定这是 $*\color{red} 2700$ 的题吗。

考虑枚举矩形的左边界和右边界，有 $O(n^2)$ 种情况。枚举下边界时，计算出符合条件的最大的上边界，这一部分必须只用 $O(1)$ 的复杂度计算。

设 $mx_{l,r,h}$ 为第 $h$ 行，$l$ 到 $r$ 列中的所有数，在此段区间内对应的可能的合法上边界的最大值是多少。注意到它可以从 $mx_{l,r-1,h}$ 和 $mx_{l+1,r,h}$ 转移过来，唯一漏掉的情况就是 $a_{h,l}$ 和第 $r$ 列以及 $a_{h,r}$ 和第 $l$ 列之间的重叠情况。可以开一个数组记录 $lst_{col,j}$ 为第 $j$ 列中，颜色 $col$ 出现的最大的行在哪里。

从上往下枚举，即可以做到 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=400+10,MAXM=160000+10;
int n,m,ans,a[MAXN][MAXN],mx[MAXN][MAXN],tu[MAXN][MAXN];
short lst[MAXN][MAXM];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m; ffor(i,1,n) ffor(j,1,m) cin>>a[i][j];
	ffor(i,1,n) {
		ffor(j,1,m) mx[j][j]=lst[j][a[i][j]];
		ffor(j,1,m) lst[j][a[i][j]]=i;
		ffor(len,2,m) for(int l=1,r=len;r<=m;l++,r++) mx[l][r]=max({mx[l+1][r],mx[l][r-1],(int)lst[r][a[i][l]],(int)lst[l][a[i][r]]});
		ffor(l,1,m) ffor(r,l,m) tu[l][r]=max(tu[l][r],mx[l][r]);
		ffor(l,1,m) ffor(r,l,m) ans=max(ans,(r-l+1)*(i-tu[l][r]));
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：Leap_Frog (赞：5)

### P.S.
题解一血

### Description.
给定一个 $n\times m$ 的矩阵，求最大的子矩阵，满足其没有重复元素。  
$n\le 400$  

### Solution1.
复杂度 $O(n^3\log n)$，**无法通过**  

考虑枚举矩阵上边界和下边界。  
对于每个点维护如果它作为右边界所能到达的最左边界。  
然后，每次下边界下移，我们发现会更新一些点的信息。  
就是如果新加入的一行中一个元素在过去出现过，我们就需要跟新它。  
然后直接用一个 `set` 维护，每次查询前驱后继。  

### Solution2.
考虑在 **Solution1** 的基础上优化。  
考虑更换枚举方向，上边界从下往上移动，下边界从上往下移动。  
维护的东西和 **Solution1** 相同，下边界下移，可以利用上一次求出的信息。  
上边界上移，从删数变成了加数，删数的话必须重新处理，加数就可以利用之前的性质了。  
然后相当于每次多出来了最上面一行，根本不需要用 `set`。  

### Coding.
如果真理解了代码写写很快的，就不贴了  
[代码可以看这里](https://www.cnblogs.com/pealfrog/p/15194064.html)  

---

## 作者：DPair (赞：3)

拿到这道题，不难想到一个 $O(n^4)$ 的做法，即枚举行的上下界，然后对列跑双指针

考虑改进这个做法，我们枚举上边界，然后不断扩展下边界，扩展时对右端点进行扫描线

发现这个做法中我们需要用一个数据结构求出某一列往前最远能够走到哪一列，发现需要用一 $O(n^2)$ 个 `std::set` 求出前驱后继，前驱用来维护当前点的信息，后继用来维护 **后继所在列** 的信息

发现这样可以在 $O(n^3\log n)$ 的时间内解决问题，但还是不够

我们发现如果从上到下枚举上边界，我们做的是删除，而删除相对于插入性质可能更差一些

考虑从下到上枚举上边界

不难发现此时我们扩展上边界时，对于每一行，其能到达的最左端点只会因为我们枚举到的这个上边界而发生变化，因此只需要判断两行之间的关系即可

而且不难发现，由于我们只维护两行的信息，我们可以不使用 `std::set` 而直接使用一个数组来处理前驱后继，而且此时我们只需要处理前驱，可以理解为枚举到某一列时，上文所述的需要的后继就是当前列，然后对应取 $\max$ 即可

由此就利用单调性达到了 $O(n^3)$ 的复杂度，可以通过本题

而且空间做到了 $O(n^2)$

只放关键代码

```cpp
const int MAXN = 4e2 + 5;
int n, m, a[MAXN][MAXN], f[MAXN * MAXN], p[MAXN][MAXN];
signed main(){ int ans = 0;
    read(n, m); rep(i, 1, n) read(a[i] + 1, a[i] + m + 1);
    per(k, n, 1) {
        rep(i, 1, m) { const int x = a[k][i]; p[k][i] = mx(p[k][i - 1], f[x]); chmax(ans, i - p[k][i]); f[x] = i; }
        rep(i, 1, m) f[a[k][i]] = 0; 
        rep(j, k + 1, n) {
            int l = 0; rep(i, 1, m) {
                const int x = a[k][i], y = a[j][i];
                chmax(p[j][i], (x == y)? i : mx(f[x], f[y], p[j - 1][i])); chmax(l, p[j][i]);
                f[x] = f[y] = i; chmax(ans, (j - k + 1) * (i - l));
            }
            rep(i, 1, m) f[a[k][i]] = f[a[j][i]] = 0;
        }
    } print(ans);

}
```

---

## 作者：Unnamed114514 (赞：1)

你考虑钦定矩形的上下边界。

然后你用双指针枚举横坐标就可以做到 $O(n^4)$。

考虑优化：

定义 $f_{l,r,x}$ 表示上下边界为 $[l,r]$ 时 $x$ 列往右扩展到的最大列数。

容易找到单调性即 $f_{l,r,x}\le\min\{f[l+1,r,x],f_{l,r-1,x},f_{l,r,x+1}\}$。

容易发现，没有考虑到的就只有 $(l,x)$ 在 $r$ 这一行和 $(r,x)$ 在 $l$ 这一行是否互不相等。

但是这玩意直接在钦定 $l,r$ 的时候 $O(n)$ 初始化就行了。

---

## 作者：Mirasycle (赞：1)

很显然的暴力枚举左右边界，对于上下进行双指针，时间复杂度 $O(n^4)$。

思考一下复杂度花在哪里了，主要是扫描线每次推进的代价太大了，由于左右列间距很大，每次推动指针向下暴力扫描那一行的信息很浪费时间。考虑移动枚举左右边界的时候一点点移动继承上一次的一点信息。

仔细想想好像有点困难，虽然单纯继承前几列的信息很容易，但是加入新的一列面临的是很长一段新的信息如何整合？我们可以同时在每次下移下边界的时候，只计算新移动出来的这一行，然后对于上一行算出来的上边界结果取一下交即可。

总结一下就是我们维护 $f_{h,l,r}$ 表示只考虑第 $h$ 行，列区间在 $[l,r]$ 之内的最多能延生的上边界（上为开区间），行内更新 $\max(f_{h,l+1,r},f_{h,l,r-1}) \to f_{h,l,r}$，同时我们可以发现对于 $a_{h,l}$ 没有统计其在 $r$ 列的情况（$a_{h,r}$ 同理），于是我们维护 $lst_{t,j}$ 表示对于数字 $t$ 在第 $j$ 列上一次出现的位置，然后 $\max(lst_{a(h,l),r},lst_{a(h,r),l}) \to f_{h,l,r}$。最后第 $h$ 行作为下边界能取到最远上边界就是 $\max(f_{h,l,r},\max\limits_{c=1}^{h-1}(f_{c,l,r}))$。

---

## 作者：daniEl_lElE (赞：1)

考虑枚举选出矩形的左右列。

对于一个左右列分别为 $[l,r]$ 的矩形，如果他不合法，那么要么 $[l,r-1]$ 不合法，要么 $[l+1,r]$ 不合法，要么 $l,r$ 两行拼在一起不合法。那么设一个左右列分别为 $[l,r]$，上端点为 $p$ 的矩形，他的下端点的最大值是 $dp_{l,r,p}$，则 $dp_{l,r,p}=\min(dp_{l,r-1,p},dp_{l,r+1,p},f_{l,r,p})$，其中 $f_{l,r,p}$ 为单独考虑 $l,r$ 两列，$p$ 位置对应的最大下端点。$f_{l,r,p}$ 可以在考虑 $[l,r]$ 两列时双指针 $O(n)$ 求出。dp 的转移是 $O(1)$ 的，故总复杂度 $O(nm^2)$。注意处理一下 $l=r$ 的情况的 $f_{l,r,p}$。

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
using namespace std;
int a[405][405];
int dp[405][405][405];
int tag[160005];
signed main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j];
	int ans=0;
	for(int len=1;len<=m;len++) for(int i=1,j=len;j<=m;i++,j++){
		if(i!=j){
			int now=1;
			for(int k=1;k<=n;k++){
				tag[a[k][i]]++,tag[a[k][j]]++;
				while(tag[a[k][i]]>=2||tag[a[k][j]]>=2){
					tag[a[now][i]]--,tag[a[now][j]]--,now++;
				}
				dp[i][j][k]=k-now+1;
				dp[i][j][k]=min(dp[i][j][k],min(dp[i+1][j][k],dp[i][j-1][k]));
				ans=max(ans,(j-i+1)*dp[i][j][k]);
			}
			for(int k=now;k<=n;k++) tag[a[k][i]]--,tag[a[k][j]]--;
		}
		else{
			int now=1;
			for(int k=1;k<=n;k++){
				tag[a[k][i]]++;
				while(tag[a[k][i]]>=2){
					tag[a[now][i]]--,now++;
				}
				dp[i][j][k]=k-now+1;
				ans=max(ans,dp[i][j][k]);
			}
			for(int k=now;k<=n;k++) tag[a[k][i]]--;
		}
	}
	cout<<ans;
	return 0;
}
```

---

