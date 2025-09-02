# 「AWOI Round 2 D」数字三角形

## 题目描述

Glad 发现了一个 $n$ 层数字三角形，他发现可以用魔法来操纵这个三角形！

他可以先消耗 $nk_1$ 点消耗值，让将三角形旋转 $k_1$ 次。其中“旋转”指绕三角形中心顺时针旋转 $120^\circ$。

然后，他可以不停地进行下面操作：

- 消耗 $1$ 点消耗值，选择一层，调换这一层任意两个数的位置。

现在，Glad 要从三角形的最后一层走到最顶层，起点可以为最后一层的任意一个数，行走的每一步只能走到与当前数相邻的数上，且每一行只能经过一个数。

Glad 想在经过数之和最大的前提下让消耗的消耗值最小，你可以帮帮他吗？

## 说明/提示

**【样例解释】**

初始三角形为：

```
    1
   2 3
  4 5 6
10 9 8 7
2 5 2 5 6
```


将其向右翻转 $2$ 次，消耗 $10$ 点调换值，此时三角形变为：

```
    6
   7 5
  6 8 2
 3 5 9 5
1 2 4 10 2
```

无须调换数字，沿着 $6,7,8,9,10$ 走，可以得到最大值 $40$，共耗费 $10$ 点调换值。

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | 数据范围 | 特殊性质 | 分值 |  
| :-----------: | :-----------: | :-----------: | :-----------: |  
| $\text{Subtask1}$ | $1\leqslant n\leqslant 10$ | AB | $10$ |  
| $\text{Subtask2}$ | $1\leqslant n \leqslant 10$ | A | $10$ |  
| $\text{Subtask3}$ | $1\leqslant n \leqslant 10$ | B | $10$ |  
| $\text{Subtask4}$ | $1\leqslant n \leqslant 10$ | 无 | $10$ | 
| $\text{Subtask5}$ | $1\leqslant n \leqslant 40$ | 无 | $20$ | 
| $\text{Subtask6}$ | $1\leqslant n\leqslant 10^3$ | 无 | $40$ |  

特殊性质 A：不需要调换数字就可以得到最优解。

特殊性质 B：不需要向右旋转就可以得到最优解。

对于 $100\%$ 的数据，保证：$1\leqslant n\leqslant 10^3$，$0\leqslant a_i\leqslant10^4$。

**【工作人员】**

| $\text{Idea}$ | $\text{Data}$ | $\text{Check}$ | $\text{Solution}$ |
| :----------: | :----------: | :----------: | :----------: |
|[S__X](/user/310466) |[S__X](/user/310466)|[I_am_AKed_by_NOI](/user/807853) | [I_am_AKed_by_NOI](/user/807853) |

## 样例 #1

### 输入

```
5
1
2 3
4 5 6
10 9 8 7
2 5 2 5 6```

### 输出

```
40 10```

# 题解

## 作者：Aesyl (赞：12)

## Update 2023.8.16：

重新写了一份更格式化，观赏性更强的代码。

## 题意

如果你没有做过 [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)，请先去看看。

本题其实就是 P1216 的升级版，在原本的题目上做出了一下改编：

- 给出的三角形可以顺时针进行 $120$ 度旋转，旋转一次消耗值为 $n$。

- 给出的三角形在旋转过后，可以交换同一层中的任意两个数，交换一次消耗值为 $1$。

然后问你从顶部走到底部，路上经过的数字和最大是多少，此时所用的消耗值最小为多少。

（下文说的所有旋转都指顺时针旋转）

## 分析

不妨单独分析一下这两个新增的条件：

旋转原三角形后无非只存在**三种可能**，分别为旋转了 $0$ 度，$120$ 度，$240$ 度后的结果，消耗值分别为 $0$，$n$，$2 \times n$。我们在后续的操作中可以对这三类进行分类讨论。

交换三角形中同一层的两个数，这两个数中必定**存在且仅存在 $1$ 个本层最大的数**。

因为任意两个数交换的消耗值都是 $1$，跟其他数交换肯定无法比跟最大值交换好，所以其中至少有一个本层最大的数。

同时如果这两个数都是本层最大的数，那就没有交换的必要了，因此交换的两数中仅会存在 $1$ 个本层最大的数。

因此我们可以对旋转后的三角形进行分类讨论，预处理出每层的最大值，然后就是常规的 dp 啦！

## 实现

设 $dp_{i,j}$ 为走到第 $i$ 行，第 $j$ 列时经过数字和的最大值。

$cost_{i,j}$ 为走到第 $i$ 行，第 $j$ 列时满足 $dp_{i,j}$ 最大化的前提下消耗值的最小值。

$m_i$ 为旋转后第 $i$ 行的最大值

-------------------------

对于旋转 $0$ 度的三角形，明显有：

$$dp_{i,j}=\max(dp_{i-1,j-1},dp_{i-1,j})+m_i$$

然后更新 $cost_{i,j}$ 为 $cost_{i-1,j-1}$ 或 $cost_{i-1,j}$。

最后如果 $dp_{i,j} \neq m_i$，$cost_{i,j} \rightarrow cost_{i,j}+1$。

--------------------------

对于旋转 $240$ 度的三角形，我们不需要真正去旋转它，只需要注意它与原三角形的相对位置关系，便可以直接在原三角形上 DP。

容易发现此时原三角形的列变为了行，$m_j$ 就相当于原三角形第 $j$ 列的最大值，有：

$$dp_{i,j}=\max(dp_{i,j+1},dp_{i+1,j+1})+m_j$$

注意上式中的 $i$ 和 $j$ 都要从大到小枚举，外层循环的是 $j$，以防止产生后效性。

然后更新 $cost_{i,j}$ 为 $cost_{i,j+1}$ 或 $cost_{i+1,j+1}$。

最后如果 $dp_{i,j} \neq m_j$，$cost_{i,j} \rightarrow cost_{i,j}+1$。

同时要注意，旋转三角形也会产生消耗值，所以这里记录的 $cost$ 数组不是消耗值的真实值，加上 $2 \times n$ 后才是。

--------------------------

对于旋转 $120$ 度的三角形，同样只需要注意它与原三角形的相对位置关系，便可以直接在原三角形上 DP。

此时的一层相当于原三角形一条斜线，很容易发现一条斜线上的 $i-j$ 是一个定值，且两两互不相同。

我们当然可以直接拿 $i-j$ 作为本层 $m$ 数组的下标，但因为上文中规定 $m_i$ 为旋转后第 $i$ 行的最大值，第 $k$ 层的 $i-j$ 实际上并不等于 $k$，所以这里也可以算出 $k$ 和 $i$，$j$ 之间的关系：

$$k=n-i+j$$

$m_{n-i+j}$ 就相当于旋转后第 $n-i+j$ 层的最大值，有：

$$dp_{i,j}=\max(dp_{i,j-1},dp_{i+1,j})+m_{n-i+j}$$

注意上式中的 $i$ 要从大到小枚举，$j$ 要从小到大枚举，外层循环的是 $i$，以防止产生后效性。

然后更新 $cost_{i,j}$ 为 $cost_{i,j-1}$ 或 $cost_{i+1,j}$。

最后如果 $dp_{i,j} \neq m_{n-i+j}$，$cost_{i,j} \rightarrow cost_{i,j}+1$。

同样的，这里记录的 $cost$ 数组也不是消耗值的真实值，加上 $n$ 后才是。

## 代码

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
#define N 2005
using namespace std;
int n,y,z,a[N][N],dp[N][N],cost[N][N],maxn[N],ans,tot;
void Dy_Pr(int i,int j,int i1,int j1,int i2,int j2,int line,int extra){
	// i 和 j 代表现在所处的坐标
	// (i1,j1) 和 (i2,j2) 是可以转移到 (i,j) 的两个坐标
	// line 表示一层
	// extra 表示旋转产生的消耗值 
	if(dp[i1][j1]>dp[i2][j2]||(dp[i1][j1]==dp[i2][j2]&&cost[i1][j1]<cost[i2][j2])){
		cost[i][j]+=cost[i1][j1];
		dp[i][j]=dp[i1][j1];
	}else{
		cost[i][j]+=cost[i2][j2];
		dp[i][j]=dp[i2][j2];
	}
	dp[i][j]+=maxn[line];
	if(a[i][j]!=maxn[line]) cost[i][j]++;
	if(ans<dp[i][j]||(ans==dp[i][j]&&cost[i][j]+extra<tot)){
		ans=dp[i][j];
		tot=cost[i][j]+extra;
	}
}
void solve(int op){
	for(int i=1;i<=n;i++){
		maxn[i]=0;
		for(int j=1;j<=n;j++){
			dp[i][j]=0,cost[i][j]=0;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			if(op==1) maxn[i]=max(maxn[i],a[i][j]);
			if(op==2) maxn[j]=max(maxn[j],a[i][j]);
			if(op==3) maxn[i-j]=max(maxn[i-j],a[i][j]);
		}
	}
	if(op==1){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=i;j++){
				Dy_Pr(i,j,i-1,j-1,i-1,j,i,0);
			}
		}
	}
	if(op==2){
		for(int j=n;j;j--){
			for(int i=n;i>=j;i--){
				Dy_Pr(i,j,i,j+1,i+1,j+1,j,2*n);
			}
		}
	}
	if(op==3){
		for(int i=n;i;i--){
			for(int j=1;j<=i;j++){
				Dy_Pr(i,j,i,j-1,i+1,j,i-j,n);
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			cin>>a[i][j];
		}
	}
	
	solve(1);//旋转 0 度 
	solve(2);//旋转 240 度 
	solve(3);//旋转 120 度 
	
	cout<<ans<<" "<<tot;
    return 0;
}
```

老代码：

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
#define N 2005
using namespace std;
int n,y,z,a[N][N],dp[N][N],cost[N][N],maxn[N],ans,tot;
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			cin>>a[i][j];
		}
	}
	
	//不旋转的情况: 
	
	for(int i=1;i<=n;i++){
		maxn[i]=0;
		for(int j=1;j<=n;j++){
			dp[i][j]=0,cost[i][j]=0; 
		}
	}//初始化 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			maxn[i]=max(maxn[i],a[i][j]);
		}
	}//预处理 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			if(dp[i-1][j-1]>dp[i-1][j]||(dp[i-1][j-1]==dp[i-1][j]&&cost[i-1][j-1]<cost[i-1][j])){
				cost[i][j]+=cost[i-1][j-1];
				dp[i][j]=dp[i-1][j-1];
			}else{
				cost[i][j]+=cost[i-1][j];
				dp[i][j]=dp[i-1][j];
			}
			dp[i][j]+=maxn[i];
			if(a[i][j]!=maxn[i]) cost[i][j]++;
			if(ans<dp[i][j]||(ans==dp[i][j]&&cost[i][j]<tot)){//更新答案 
				ans=dp[i][j];
				tot=cost[i][j];
			}
		}
	}
	
	//旋转 240 度的情况: 
	
	for(int i=1;i<=n;i++){
		maxn[i]=0;
		for(int j=1;j<=n;j++){
			dp[i][j]=0,cost[i][j]=0;
		}
	}//初始化 
	for(int j=1;j<=n;j++){
		for(int i=j;i<=n;i++){
			maxn[j]=max(maxn[j],a[i][j]);
		}
	}//预处理 
	for(int j=n;j;j--){
		for(int i=n;i>=j;i--){//注意这里的循环顺序 
			if(dp[i][j+1]>dp[i+1][j+1]||(dp[i][j+1]==dp[i+1][j+1]&&cost[i][j+1]<cost[i+1][j+1])){
				cost[i][j]+=cost[i][j+1];
				dp[i][j]=dp[i][j+1];
			}else{
				cost[i][j]+=cost[i+1][j+1];
				dp[i][j]=dp[i+1][j+1];
			}
			dp[i][j]+=maxn[j];
			if(a[i][j]!=maxn[j]) cost[i][j]++;
			if(ans<dp[i][j]||(ans==dp[i][j]&&cost[i][j]+n*2<tot)){//更新答案 
				ans=dp[i][j];
				tot=cost[i][j]+n*2;//别忘了加上旋转产生的消耗值 
			}
		}
	}
	
	//旋转 120 度的情况:
	
	for(int i=1;i<=n;i++){
		maxn[i]=0;
		for(int j=1;j<=n;j++){
			dp[i][j]=0,cost[i][j]=0;
		}
	}//初始化 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			maxn[i-j]=max(maxn[i-j],a[i][j]);
		}
	}//预处理(这里为了方便就直接拿 i-j 作为数组下标了) 
	for(int i=n;i;i--){
		for(int j=1;j<=i;j++){//注意这里的循环顺序 
			if(dp[i][j-1]>dp[i+1][j]||(dp[i][j-1]==dp[i+1][j]&&cost[i][j-1]<cost[i+1][j])){
				cost[i][j]+=cost[i][j-1];
				dp[i][j]=dp[i][j-1];
			}else{
				cost[i][j]+=cost[i+1][j];
				dp[i][j]=dp[i+1][j];
			}
			dp[i][j]+=maxn[i-j];
			if(a[i][j]!=maxn[i-j]) cost[i][j]++;
			if(ans<dp[i][j]||(ans==dp[i][j]&&cost[i][j]+n<tot)){//更新答案 
				ans=dp[i][j];
				tot=cost[i][j]+n;//别忘了加上旋转产生的消耗值
			}
		}
	}
	
	
	
	cout<<ans<<" "<<tot;
    return 0;
}
```


---

## 作者：S__X (赞：7)

如果我们将金字塔翻转 $3$ 次，会变为原金字塔。所以，翻转 $n$ 次，相当于翻转 $n\bmod 3$ 次，为了使用魔法值更小，所以翻转的次数一定 $<3$。

因此，我们讨论不翻转和翻转 $1$ 或 $2$ 次金字塔三种情况，从中取出最优的即可。

现在思考如何如何最优化调换操作。

结论：合法路径所经过的最大和一定是每行最大值之和。

证明：这还是比较显然地，我们设任意一条合法路径为 $A_{1,b_1},A_{2,b_2},\cdots,A_{n,b_n}$，设第 $i$ 行的最大值在第 $mx_i$ 列。那么，交换 $A_{1,b_1},A_{1,mx_1},A_{2,b_2},A_{2,mx_2},\cdots ,A_{n,b_n},A_{n,mx_n}$，那么 $A_{1,mx_1},A_{2,mx_2},\cdots ,A_{n,mx_n}$  这些每一行的最大值就在一条合法路径上了！

我们发现，如果一条合法路径上有一点 $A_{i,j}$，它同时是 $A_{i,mx_i}$，那么这一行就不需要进行调换操作了！

因此，我们要找到一条合法路径让他所包含的最大值最多。如何做到呢？类似于数字金字塔了，不懂同学们可以去学习一下这题。

$f[x][y]$ 表示从金字塔最后一行到 $(x,y)$ 最多会经过几个最大值，$Max[i][j]$ 表示第 $i$ 行的 $j$ 元素是否为最大值。

那么有 DP 方程：$f[x][y]=Max[x][A[x][y]]+\max(f[x+1][y],f[x+1][y+1])$。

那么 $f[1][1]$ 就是一条合法路径所包含的最大值数量最多是多少。那么需要调换的次数就是 $n-f[1][1]$。

总代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000;
int A[MAXN][MAXN], f[MAXN][MAXN], Max[MAXN][MAXN], n, M_num, M_sum, B[MAXN][MAXN];
int MSUM;
void S_max() {
	memset(Max, 0, sizeof(Max));
	MSUM = 0;
	for (int i = 1; i <= n; i++) {
		int Max2 = 0;
		for (int j = 1; j <= i; j++) {
			Max2 = max(Max2, A[i][j]);
		}
		Max[i][Max2] = 1;
		MSUM += Max2;
	}
}
void fz() {
	int num1 = 0, num2 = 0;
	for (int i = n; i >= 1; i--) {
		num2 = 1;
		num1++;
		int w = i;
		for (int j = n; j >= i; j--) {
			B[num1][num2++] = A[j][n - w + 1];
			w++;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			A[i][j] = B[i][j];
		}
	}
	memset(f, -1, sizeof(f));
	memset(Max, 0, sizeof(Max));
	MSUM = 0;
	S_max();
}
int search(int x, int y) {
	if (f[x][y] == -1) {
		if (x == n) f[x][y] = Max[x][A[x][y]];
		else f[x][y] = Max[x][A[x][y]] + max(search(x + 1, y), search(x + 1, y + 1));
	}
	return f[x][y];
}
void gx(int mm) {
	if (MSUM > M_sum) {
		M_sum = MSUM;
		M_num = (n - f[1][1]) + mm;
	}
	else if (MSUM == M_sum) {
		M_num = min(M_num, (n - f[1][1]) + mm);
	}
}
int main() {
	cin >> n;
	memset(f, -1, sizeof(f));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			cin >> A[i][j];
		}
	}
	S_max();
	search(1, 1);
	gx(0);
	fz();
	search(1, 1);
	gx(n);
	fz();
	search(1, 1);
	gx(2 * n);
	cout << M_sum << " " << M_num << endl;
}

```

---

## 作者：zct_sky (赞：3)

### Solution
-----
三角形旋转次数 $k_1 \in [0,1,2]$。

由于每次形成的数组各自独立，因此要分别考虑。

若 $a_{i,j,k_1}$ 为旋转 $k_1$ 次后 $a$ 数组第 $i$ 行第 $j$ 列的值，则满足 $a_{i,j,k_1}=a_{n-j+1,i-j+1,k_1-1}$。

然后就得到了旋转 $0,1,2$ 次的数组。

由于要求以经过数之和最大为前提，所以可以预处理出每个数组每行的最大值，并对最大值求和，得出最大经过数之和。

~~然后就是动规时间。~~

因为每行可能有多个最大值，所以我们设计一个三维 DP。

记 $f_{i,j,k_1}$ 为从旋转了 $k_1$ 次的 $a$ 数组从第 $n$ 行至 $a_{i,j,k_1}$ 经过数之和最大的最小消耗值。

则有 $f_{i,j,k_1}=\min\{f_{i+1,j,k_1},f_{i+1,j+1,k_1}\}+tmp$。

其中 $tmp$ 表示 $a_{i,j,k_1}$ 是否为当前行最大值，是则为 $0$，否则为 $1$。

初始化 $f_{n,j,k_1}=n\times k_1+tmp(1\le j \le n)$，$tmp$ 含义同上。

遍历顺序为倒序遍历 $i$，顺序遍历 $j$。

为了节省时间，当旋转后数组行最大值和为最大经过数之和时才需要 DP。

时间复杂度 $\mathcal{O}(n^2)$，足以通过本题。
### Code
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return x*y;
}
const int N=1e3+7;
int n;
int a[N][N][3],maxn[N][3];
int dp[N][N][3]; 
int ans1,ans2,s[3];
void solve(int x){
	for(int i=1;i<=n;i++){
		int k=a[i][1][x];
		for(int j=2;j<=i;j++)
			if(a[i][j][x]>k)
				k=a[i][j][x];
		maxn[i][x]=k;
		s[x]+=k;
	}
	ans1=max(ans1,s[x]);
}
void DP(int x){
	for(int i=1;i<=n-1;i++)
		for(int j=1;j<=i;j++)
			dp[i][j][x]=114514;
	for(int i=1;i<=n;i++)
		if(a[n][i][x]==maxn[n][x])
			dp[n][i][x]=x*n;
		else dp[n][i][x]=x*n+1;
	for(int i=n-1;i>=1;i--)
		for(int j=1;j<=i;j++)
			dp[i][j][x]=min(dp[i+1][j][x],dp[i+1][j+1][x])+(a[i][j][x]!=maxn[i][x]);
	ans2=min(ans2,dp[1][1][x]);
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			a[i][j][0]=read();
	solve(0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			a[i][j][1]=a[n-j+1][i-j+1][0];
	solve(1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			a[i][j][2]=a[n-j+1][i-j+1][1];
	solve(2);
	ans2=INT_MAX;
	if(s[0]==ans1)
		DP(0); 
	else if(s[1]==ans1)
		DP(1); 
	else if(s[2]==ans1)
		DP(2); 
	printf("%d %d",ans1,ans2);
	return 0;
}
```

---

## 作者：渡鸦2007 (赞：2)

显然翻转次数只能是 $0,1,2$ 中的一个。接下来我们先分析，对于某一方向的数字三角形，该如何处理。

注意到题面要求**经过数之和最大**的前提下消耗值最小，所以对于每一行，必须经过该行最大数（可能有多个）。所以最大能经过的数之和，就是每行最大数的和。

由于 $n\le 1000$，考虑 DP，记 $f_{i,j}$ 表示第 $i$ 行，第 $j$ 个数所耗的消耗值，$a_{i,j}$ 表示第 $i$ 行，第 $j$ 个数的值。我们约定，若 $a_{i,j}$ 不是第 $i$ 行的最大值，则使位置 $j$ 上的数与该行最大值交换。初始状态为 $f_{1,1}=0$，其余为正无穷。

转移方程为：
- 若 $a_{i,j}$ 是第 $i$ 行的最大值：$f_{i,j}=\min(f_{i,j-1},f_{i,j})$
- 否则：$f_{i,j}=\min(f_{i,j-1},f_{i,j})+1$，这是因为进行交换消耗 $1$ 点消耗值。

答案则是 $\min\{f_n\}$，这是因为我们已经规定每个位置都要是当行最大值。

那么，我们只要将三角形翻转两次，每次分别 DP 即可。注意，要使**经过数之和最大**，所以若某情况中经过数之和大于另一情况，即使消耗更多，都必须选择此情况而非另一情况。

算法时空复杂度均为 $O(n^2)$。以下代码用时 $47ms$，暂时是最优解。翻转部分与预处理部分参见代码注释。
```cpp

int a[1010][1010];vector<int>pos[1010];
int f[1010][1010];int t[1010][1010];//翻转时用
int dp();int n;int sum=0;
void clear()//翻转部分
{
	sum=0;
	for (int i=1;i<=n;++i) pos[i].clear();
	memset(f,0,sizeof f);
	for (int i=1;i<=n;++i)
	{
		for (int j=1;j<=i;++j)
		{
			t[i][j]=a[i][j];
		}
	}
	for (int i=1;i<=n;++i)//旋转120度，让原左下顶点为新的上顶点
	{
		for (int j=1;j<=i;++j)
		{
			a[i][j]=t[n-j+1][i-j+1];
		}
	}
	for (int i=1;i<=n;++i)//重新预处理出行最大值
	{
		int _mx=0;
		for (int j=1;j<=i;++j)
		{
			if (a[i][j]>_mx)
			{
				_mx=a[i][j];pos[i].clear();pos[i].push_back(j);
			}
			else if (a[i][j]==_mx)
			{
				pos[i].push_back(j);
			}
		}
		sum+=_mx;//该情况经过数之和
	}
}
int main()
{
	n=read();
	for (int i=1;i<=n;++i)
	{
		int _mx=0;
		for (int j=1;j<=i;++j)
		{
			a[i][j]=read();
			if (a[i][j]>_mx)
			{
				_mx=a[i][j];pos[i].clear();pos[i].push_back(j);
			}
			else if (a[i][j]==_mx)
			{
				pos[i].push_back(j);
			}
		}
		sum+=_mx;
	}
	int tot_ans=0x3f3f3f3f;
	int tmp_ans=dp();int tmp_sum=sum;
	tot_ans=min(tot_ans,tmp_ans);
	//--------------以下翻转一次------------------
	tmp_ans=n;//注意翻转是要消耗的
   clear();tmp_ans+=dp();
	if (tmp_sum==sum) tot_ans=min(tot_ans,tmp_ans);
	else if (tmp_sum<sum)//必须先让经过数之和最大
	{
		tot_ans=tmp_ans;tmp_sum=sum;
	}
	//--------------以下翻转两次------------------
	tmp_ans=n<<1;clear();tmp_ans+=dp();
	if (tmp_sum==sum) tot_ans=min(tot_ans,tmp_ans);
	else if (tmp_sum<sum)
	{
		tot_ans=tmp_ans;tmp_sum=sum;
	}
	cout<<tmp_sum<<" "<<tot_ans;
	return 0;
}

int dp()
{
	memset(f,0x3f,sizeof f);f[1][1]=0;
	for (int i=2;i<=n;++i)
	{
		for (int j=0;j<pos[i].size();++j)//为行最大值时
		{
			int xj=pos[i][j];
			f[i][xj]=min(f[i-1][xj-1],f[i-1][xj]);
		}
		for (int j=1;j<=i;++j)//不为行最大值时
		{
			if (f[i][j]==0x3f3f3f3f)//也即未转移过
			{
				f[i][j]=min(f[i-1][j-1],f[i-1][j])+1;
			}
		}
	}
	int ans=0x3f3f3f3f;
	for (int i=1;i<=n;++i)
	{
		ans=min(ans,f[n][i]);
	}
	return ans;
}

```


---

## 作者：Special_Tony (赞：1)

[题目传送门](/problem/P9541)
# 思路
一个三角形转三次会变回原来的样子，所以这题的旋转次数最多只有 $2$ 次，再上去肯定不是最优的，这样我们就可以分成三种情况考虑。但实际上我们只要考虑不旋转的情况，剩余的几乎是 Ctrl+C。

剩余部分很像[数字三角形](/problem/P1216)，我们也可以往下方走或右下方走。这题中，我们一定存在一种方案，可以使经过的数字总和为 $\sum\limits_{i=0}^{n-1}\max\limits_{j=0}^ia_{i,j}$，所以如果 $a_{i+1,j}\ne\max\limits_{j=0}^{i+1}a_{i+1,j}$，则需要额外消耗 $1$ 点消耗值。$a_{i+1,j+1}$ 同理，最后只要在往下方和右下方方向走的消耗值取个 $\min$ 即可。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int n, a[1005][1005], b[1005][1005], c[1005][1005], dp1[1005][1005], dp2[1005][1005], dp3[1005][1005], sum1, sum2, sum3, max1[1005], max2[1005], max3[1005], maxx, minx = 1e9;
int dfs1 (int x, int y) {
	if (~ dp1[x][y]) //记忆化递归
		return dp1[x][y];
	if (x > n - 2) //最后一行了，结束递归
		return 0;
	return dp1[x][y] = min (dfs1 (x + 1, y) + (a[x + 1][y] != max1[x + 1]), dfs1 (x + 1, y + 1) + (a[x + 1][y + 1] != max1[x + 1]));
}
int dfs2 (int x, int y) { //什么是 Ctrl+C？
	if (~ dp2[x][y])
		return dp2[x][y];
	if (x > n - 2)
		return 0;
	return dp2[x][y] = min (dfs2 (x + 1, y) + (b[x + 1][y] != max2[x + 1]), dfs2 (x + 1, y + 1) + (b[x + 1][y + 1] != max2[x + 1]));
}
int dfs3 (int x, int y) {
	if (~ dp3[x][y])
		return dp3[x][y];
	if (x > n - 2)
		return 0;
	return dp3[x][y] = min (dfs3 (x + 1, y) + (c[x + 1][y] != max3[x + 1]), dfs3 (x + 1, y + 1) + (c[x + 1][y + 1] != max3[x + 1]));
}
int main () {
	cin >> n;
	for (int i = 0; i < n; sum1 += max1[i], ++ i)
		for (int j = 0; j <= i; ++ j)
			cin >> a[i][j], max1[i] = max (max1[i], a[i][j]), dp1[i][j] = dp2[i][j] = dp3[i][j] = -1);
	for (int i = 0; i < n; sum2 += max2[i], ++ i)
		for (int j = 0; j <= i; ++ j)
			max2[i] = max (max2[i], b[i][j] = a[n - j - 1][i - j]);
	for (int i = 0; i < n; sum3 += max3[i], ++ i)
		for (int j = 0; j <= i; ++ j)
			max3[i] = max (max3[i], c[i][j] = b[n - j - 1][i - j]);
	maxx = max ({sum1, sum2, sum3});
	if (maxx == sum1)
		minx = dfs1 (0, 0);
	if (maxx == sum2)
		minx = min (minx, dfs2 (0, 0) + n);
	if (maxx == sum3)
		minx = min (minx, dfs3 (0, 0) + n * 2);
	cout << maxx << ' ' << minx;
	return 0;
}
```

---

## 作者：Genius_Star (赞：1)

~~感觉挺简单的一题，好像不需要怎么推，不过 T3 卡了我半天，第 $81$ 个 AK 的……~~

### 题意：

给定一个 $n$ 层的数字三角形，你要从顶部走到底部，行走的每一步只能走到与当前数相邻的数上，且每一行只能经过一个数，求经过的数字最大值。

并且可以使用 $1$ 点消耗值将其中一层的两个数字调换，也可以使用 $n$ 点消耗值将三角形顺时针旋转 $120^\circ$。

### 思路：

首先考虑既不交换也不旋转的情况，我们可以用简单的 dp 解决，设 $dp_{i,j}$ 为从顶层（即第 $1$ 层）走到第 $i$ 行第 $j$ 个数字的最大值。

因为每次只能走相邻的数，也就是说 $(i,j）$ 可以从 $(i-1,j)$ 和 $(i-1,j-1)$ 这两个位置走来了，我们取其中最大值，得到状态转移方程：

$$dp_{i,j}=\max(dp_{i-1,j},dp_{i-1,j-1})+a_{i,j}$$

以上是我们既不交换也不旋转的情况，这样我们就可以愉快的获得 10pts 了！

然后，我们来考虑可以交换，但是不旋转的情况，这样我们怎么样得到最大值呢？

其实也很好想，我们要再设一个状态 $k_{i,j}$，表示从顶层走到第 $i$ 行第 $j$ 个数在走过的数是最大值的情况下消耗值是多少。

既然我们要交换了，那么得重新定义一下 $dp_{i,j}$ 的状态转移方程，因为我们要最大值，我们肯定希望在当前这一层中我们走里面最大的数，这样我们可以用交换实现，所以我们在定义一个 $t_i$，表示第 $i$ 层中最大的那个数是多少。

这样我们得到状态转移方程：

$$dp_{i,j}=\max(dp_{i-1,j},dp_{i-1,j-1})+t_i$$

这样我们可以直接求出在可以交换的情况下，最大值，现在我们考虑更新 $k_{i,j}$，我们发现如果 $a_{i,j}$ 等于 $t_i$，那么 $a_{i,j}$ 本身就是最大的，不需要消耗值，否则就需要 $1$ 点消耗值交换过来。

那么，可以得到转移方程：

$$k_{i,j}=\begin{cases}k_{i-1,j}+(t_i \ne a_{i,j})&dp_{i,j}-t_i=dp_{i-1,j}\\k_{i-1,j-1}+(t_i \ne a_{i,j})&dp_{i,j}-t_i=dp_{i-1,j-1}\end{cases}$$

同时如果 $dp_{i-1,j}=dp_{i-1,j-1}$，那么我们就取 $\min(k_{i-1,j},k_{i-1,j-1})$，取其中的最小值，这样可以保证消耗值最小。

最后我们统计 $dp_{n,i}$，找到其中的最大值，如果相同的话，那么取 $k_{n,i}$ 的最小值。

这样，我们就又可以愉快的拿到 20pts 了。

现在我们来考虑旋转的情况，也是其中最简单的情况，看一下样例发现，旋转一次，左下角就跑到顶端去了，自己推一下式子，就可以得到旋转一次，三角形是什么样的：

$$b_{i,j}=a_{n-j+1,i-j+1}$$

我们又会发现，这样我们转两次就会回到原来的位置，那么我们可以对于每一次旋转过后的数字三角形，按照上述所说的 DP 计算出最大数字和最小消耗值，我们先在得到了三个答案，取三个答案中最大的数字和，如果相等取消耗值最小的。

这样，我们可以可以 AC 了。

时间复杂度：$O(n^2)$。

~~感觉常数不算大吧，跑了 155 毫秒……~~
### 完整代价：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1010;
inline ll read(){ 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll x,y;
	bool operator<(const Node&rhs)const{
		if(x!=rhs.x)
		  return x>rhs.x;
		return y<rhs.y;
	}
}f[3];
ll n,a[N][N],b[N][N],t[N],dp[N][N],k[N][N];
ll ans=0,p=INT_MAX;
void check(){
	memset(t,0,sizeof(t));
	memset(b,0,sizeof(b));
    for(int i=1;i<=n;i++)
      for(int j=1;j<=i;j++)
        b[i][j]=a[n-j+1][i-j+1];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
        	a[i][j]=b[i][j]; 
        	t[i]=max(t[i],a[i][j]);
		}
	}
}
Node solve(ll s){
	memset(dp,0,sizeof(dp));
	memset(k,0,sizeof(k));
	ans=0,p=INT_MAX;
	dp[1][1]=a[1][1];
	for(int i=2;i<=n;i++){
		for(int j=1;j<=i;j++){
			dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]);
			if(dp[i][j]==dp[i-1][j]&&dp[i][j]==dp[i-1][j-1])
			  k[i][j]=min(k[i-1][j],k[i-1][j-1]);
			else if(dp[i][j]==dp[i-1][j-1])
			  k[i][j]=k[i-1][j-1];
			else
			  k[i][j]=k[i-1][j];
			if(a[i][j]==t[i])
			  dp[i][j]+=a[i][j];
			else{
				dp[i][j]+=t[i];
				k[i][j]++;
			}
			if(i==n){
				if(dp[i][j]>=ans){
					ans=dp[i][j];
					p=min(p,k[i][j]);
				}
			}
		}
	}
	return {ans,p+s};
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			a[i][j]=read();
			t[i]=max(t[i],a[i][j]);
		}
	}
	f[0]=solve(0);
	check();
	f[1]=solve(n);
	check();
	f[2]=solve(2*n);
	sort(f,f+3);
	write(f[0].x);
	putchar(' ');
	write(f[0].y);
	return 0;
}
```


---

## 作者：sbno333 (赞：1)

这道题是旋转一次要 $n$ 的代价，交换一次 $1$ 的代价，最多 $n$ 次，因为每一层都有一个最大值，可以把最大值换到路径上，每一层一次，最多 $n$ 次，因此，由于总和优先级更高，因此我们在确保每一层最大值的情况下，要**尽量少旋转**。
```cpp
	long long n;
	cin>>n;
	long long ans;//计算总和
	ans=0;
	long long an;
	an=0;//计算每次旋转得到的数的最大值
	long long ll;
	ll=0;//旋转次数
	for(long long i=1;i<=n;i++){
		long long k;
		k=0;//计算每层最大值
		for(long long j=1;j<=i;j++){
			cin>>a[i][j];
			k=max(k,a[i][j]);
		}
		an+=k;
	}
	if(ans<an){
		ans=an;
		ll=0;
	}
	an=0;
	for(long long i=1;i<=n;i++){
		long long k;
		k=0;
		for(long long j=1;j<=i;j++){
			k=max(k,a[n-j+1][i+1-j]);
		}
		an+=k;
	}
	if(ans<an){//没有等于号，要尽量少转
		ans=an;
		ll=1;
	}
	an=0;
	for(long long i=1;i<=n;i++){
		long long k;
		k=0;
		for(long long j=1;j<=i;j++){
			k=max(k,a[n-j+1][n-i+1]);
		}
		an+=k;
	}
	if(ans<an){
		ans=an;
		ll=2;
	}
	cout<<ans<<" ";
	memset(b,0x7f,sizeof(b));
	if(ll==0){//旋转，方便下个操作
		for(long long i=1;i<=n;i++){
			long long kk;
			kk=0;
			for(long long j=1;j<=i;j++){
				b[i][j]=a[i][j];
				kk=max(kk,b[i][j]);
			}
			c[i]=kk;//计算每层最大值，具体看下一步操作
		}
	}else if(ll==1){
		for(long long i=1;i<=n;i++){
			long long kk;
			kk=0;
			for(long long j=1;j<=i;j++){
				b[i][j]=a[n-j+1][i+1-j];
				kk=max(kk,b[i][j]);
			}
			c[i]=kk;
		}
	}else{
		for(long long i=1;i<=n;i++){
			long long kk;
			kk=0;
			for(long long j=1;j<=i;j++){
				b[i][j]=a[n-j+1][n-i+1];
				kk=max(kk,b[i][j]);
			}
			c[i]=kk;
		}
	}
```
由于最多只转 $2$ 次，枚举就行啦。

接下来是难点：交换。

我们要尽量少交换，但每次都必须是把最大值放到路径上，考虑动态规划，对于到达每一个数，如果是该层最大值，则为相邻两个数的最小值，否则在这基础上加 $1$。

```cpp
	long long t;//计算消耗
	t=ll*n;
	b[1][1]=0;
	for(long long i=2;i<=n;i++){
		for(long long j=1;j<=i;j++){
			b[i][j]=min(b[i-1][j],b[i-1][j-1])+(b[i][j]!=c[i]);//DP
		}
	}
	long long lk;
	lk=0x7f7f7f7f;
	for(long long i=1;i<=n;i++){
		lk=min(lk,b[n][i]);//计算答案
	}
	cout<<lk+t;
 ```
 因此我们代码就写完啦。
 
 ~~这道题我竟然没发现旋转六十度是错的。~~

---

## 作者：him的自我修养 (赞：1)


本题应该是[数字三角形](www.luogu.com.cn/problem/P1216) 的加强版，也是用动态规划的方式去实现，比较难实现的是模拟反转，所以可以让动态规划的初值设在不同位置，不用模拟翻转，然后翻转造作最多执行两次，所以不会超时。


------------
然后就是进行三次动态规划操作了，和数字三角形那道题很像，但要注意一些细节的处理。我们可以让 $dp_{i,j}$ 代表走到 $(i,j)$ 且是最大值的最小花费。

# code
```
#include <bits/stdc++.h>
using namespace std;
int dp[3005][3005];
int a[3005][3005];
int mx[3005],mx1[3005],mx2[3005];
int n,minn=1e9,minna,cnt,cnta;
int main(){
	cin >>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			cin >>a[i][j];
			mx[i]=max(mx[i],a[i][j]);
		}
		cnt+=mx[i];
	}
	memset(dp,0x3f,sizeof(dp));
	dp[1][1]=0;
	for(int i=1;i<n;i++){
		for(int j=1;j<=i;j++){
			if(a[i+1][j+1]==mx[i+1]){
				dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]);
			}else{
				dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]+1);
			} 
			if(a[i+1][j]==mx[i+1]){
				dp[i+1][j]=min(dp[i+1][j],dp[i][j]);
			}else{
				dp[i+1][j]=min(dp[i+1][j],dp[i][j]+1);
			}
		}
	}
	for(int i=1;i<=n;i++){
		minn=min(minn,dp[n][i]);
	}
	if(cnt>cnta){
		cnta=cnt;
		minna=minn;
	} else if(cnt==cnta){
		minna=min(minna,minn);
	} 
	cnt=0,minn=1e9;
	for(int i=1;i<=n;i++){
		int x=i,y=1;
		for(int j=1;j<=n-i+1;j++){
			mx1[i]=max(mx1[i],a[x][y]);
			x++;
			y++;
		}
		cnt+=mx1[i];
	}
	memset(dp,0x3f,sizeof(dp));
	dp[n][1]=0;
	int x,y;
	for(int i=n;i>=2;i--){
		x=i;
		y=1;
		for(int j=1;j<=n-i+1;j++){
			if(a[x-1][y]==mx1[i-1]){
				dp[x-1][y]=min(dp[x-1][y],dp[x][y]);
			} else {
				dp[x-1][y]=min(dp[x-1][y],dp[x][y]+1);
			}
			if(a[x][y+1]==mx1[i-1]){
				dp[x][y+1]=min(dp[x][y+1],dp[x][y]);
			} else {
				dp[x][y+1]=min(dp[x][y+1],dp[x][y]+1);
			}
			x++;
			y++;
		}
	}
	for(int i=1;i<=n;i++){
		minn=min(minn,dp[i][i]+n);
	}
	if(cnt>cnta){
		cnta=cnt;
		minna=minn;
	} else if(cnt==cnta){
		minna=min(minna,minn);
	} 
	cnt=0,minn=1e9;
	for(int j=n;j>=1;j--){
		for(int i=n;i>=j;i--){
			mx2[j]=max(mx2[j],a[i][j]);
		}
		cnt+=mx2[j];
	}
	memset(dp,0x3f,sizeof(dp));
	dp[n][n]=0;
	for(int j=n;j>=2;j--){
		for(int i=n;i>=j;i--){
			if (a[i-1][j-1]==mx2[j-1]){
				dp[i-1][j-1]=min(dp[i-1][j-1],dp[i][j]);
			} else {
				dp[i-1][j-1]=min(dp[i-1][j-1],dp[i][j]+1);
			}
			if (a[i][j-1]==mx2[j-1]){
				dp[i][j-1]=min(dp[i][j-1],dp[i][j]); 
			} else {
				dp[i][j-1]=min(dp[i][j-1],dp[i][j]+1);
			}
		}
	}
	for(int i=1;i<=n;i++){
		minn=min(minn,dp[i][1]+2*n);
	}
	if(cnt>cnta){
		cnta=cnt;
		minna=minn;
	} else if(cnt==cnta){
		minna=min(minna,minn);
	} 
	cout <<cnta<<" "<<minna<<endl; 
	return 0;
}
```
感觉题目并不难想，但考察代码实现能力，以及对于动态规划问题的边界处理条件。

求通过qwq。

---

## 作者：Tiago (赞：1)

## Solution

通过题目意思发现，有三种情况：

1. 没有旋转的初始情况

2. 旋转一次的情况

3. 旋转两次的情况

我们考虑怎么处理初始情况，其他情况同理。

首先，我们发现经过数和最大一定可以保证是每行的最大值的总和，所以只要计算最小的消耗就可以了。

考虑 DP，设 $dp_{i,j}$ 表示从上往下走到 $i,j$ 时使每行都取最大值时的最小消耗。

容易想到如果当前的数就是当前行的最大值，便可以直接从 $dp_{i-1,j-1}$ 和 $dp_{i-1,j}$ 转移过来；如果不是，则只需再加 $1$ 即可（因为可以调换任意两个数的位置）。

每行的最大值预处理或者动规时处理均可。

注意边界和初始值。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define FOR(i,a,b) for(int i=(a);i>=(b);i--)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define elif else if
// #define int long long

const int N=1e3+4,INF=INT_MAX;
int n,a[N][N],b[N][N],Maxsum,Minmagic,Max[N],dp[N][N];
void work(int sum,int magic)
{
	For(i,1,n)Max[i]=0;
	For(i,1,n)For(j,1,i)dp[i][j]=INF,Max[i]=max(Max[i],a[i][j]);
	For(i,1,n)sum+=Max[i];
	For(i,1,n)
		For(j,1,i)
			if(a[i][j]==Max[i])dp[i][j]=min(dp[i][j],min(dp[i-1][max(1,j-1)],dp[i-1][min(i-1,j)]));
				else dp[i][j]=min(dp[i][j],min(dp[i-1][max(1,j-1)],dp[i-1][min(i-1,j)])+1);
	int Min=INF;
	For(i,1,n)Min=min(Min,dp[n][i]);
	magic+=Min;
	if(sum>Maxsum)Maxsum=sum,Minmagic=magic;
		elif(sum==Maxsum)Minmagic=min(Minmagic,magic);
}
signed main()
{
	IOS;
	cin>>n;
	For(i,1,n)For(j,1,i)cin>>a[i][j];
	work(0,0);
	For(i,1,n)For(j,1,i)b[i][j]=a[i][j];
	For(i,1,n)For(j,1,i)a[i][j]=b[n+1-j][i-j+1];
	// For(i,1,n){For(j,1,i)cout<<a[i][j]<<" ";cout<<"\n";}
	work(0,n);
	For(i,1,n)For(j,1,i)b[i][j]=a[i][j];
	For(i,1,n)For(j,1,i)a[i][j]=b[n+1-j][i-j+1];
	// For(i,1,n){For(j,1,i)cout<<a[i][j]<<" ";cout<<"\n";}
	work(0,2*n);
	cout<<Maxsum<<" "<<Minmagic;

	return 0;
}
```


---

