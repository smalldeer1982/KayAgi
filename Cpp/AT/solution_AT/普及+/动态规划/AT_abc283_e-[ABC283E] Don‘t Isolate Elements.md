# [ABC283E] Don‘t Isolate Elements

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc283/tasks/abc283_e

各要素の値が $ 0 $ または $ 1 $ である $ H $ 行 $ W $ 列の行列 $ A $ が与えられます。 $ 1\ \leq\ i\ \leq\ H $ かつ $ 1\ \leq\ j\ \leq\ W $ を満たす整数の組 $ (i,j) $ について、$ A $ の $ i $ 行目 $ j $ 列目の要素を $ A_{i,j} $ で表します。

行列 $ A $ に対し、以下の操作を $ 0 $ 回以上の好きな回数行うことができます。

- $ 1\ \leq\ i\ \leq\ H $ を満たす整数 $ i $ を選び、$ 1\ \leq\ j\ \leq\ W $ を満たす全ての整数 $ j $ に対して $ A_{i,j} $ の値を $ 1-A_{i,j} $ で置き換える。
 
また、$ A_{i,j} $ は行列において上下左右に同じ値が存在しない、すなわち $ 4 $ つの整数組 $ (x,y)\ =\ (i-1,j),(i+1,j),(i,j-1),(i,j+1) $ のいずれかであって、 $ 1\ \leq\ x\ \leq\ H,\ 1\ \leq\ y\ \leq\ W $ かつ $ A_{i,j}\ =\ A_{x,y} $ を満たすものが存在しないとき、またそのときに限り**孤立した要素**であると定義されます。

操作を繰り返し行列 $ A $ の任意の要素が孤立した要素でない状態にすることが可能か判定し、可能な場合は行う操作回数の最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ H,W\ \leq\ 1000 $
- $ A_{i,j}\ =\ 0 $ または $ A_{i,j}\ =\ 1 $
- 入力はすべて整数
 
### Sample Explanation 1

$ i\ =\ 1 $ を選択し操作を行うと、$ A\ =\ ((0,0,1),(1,0,1),(1,0,0)) $ となり、孤立した要素は存在しなくなります。

## 样例 #1

### 输入

```
3 3
1 1 0
1 0 1
1 0 0```

### 输出

```
1```

## 样例 #2

### 输入

```
4 4
1 0 0 0
0 1 1 1
0 0 1 0
1 1 0 1```

### 输出

```
2```

## 样例 #3

### 输入

```
2 3
0 1 0
0 1 1```

### 输出

```
-1```

# 题解

## 作者：Demeanor_Roy (赞：12)

- 赛时做法，有问题欢迎提出。

------------

首先发现每一行变换的次数只能为 $0$ 或 $1$，并且发现当前这一行变换只会影响旁边两行的合法性。

据此考虑DP。$f(i,0/1,0/1)$ 表示考虑前 $i$ 行，前 $i-1$ 行已确定合法，第 $i-1$ 行和第 $i$ 行分别是否变换的方案数。转移就考虑枚举 $f(i-1,0/1,0/1)$，这时最后三行状态已知，若第 $i-1$ 行合法，则能转移，反之不能。最后的答案就再判断一下 $f(H,0/1,0/1)$ 对第 $H$ 行是否合法就行。

时间复杂度 $O(HW)$

[代码](https://atcoder.jp/contests/abc283/submissions/37511913)

---

## 作者：快乐的大童 (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc283_e)
## 题意
给定一个 $n\times m$ 的 $01$ 矩阵，你可以通过若干次操作（即将一整行的所有数取反），使得对于每个位置，它的上下左右四个数有至少一个数与其相等。求最小操作数，无解输出 `-1`。
## 思路
考虑 dp。

我们设 $f_{i,0/1,0/1,0/1}$ 表示前 $i$ 行，第 $i$ 行是/否被操作过，第 $i-1$ 行是/否被操作过，第 $i-2$ 行是/否被操作过的最小操作次数。

考虑转移第 $i$ 行，枚举第 $i$ 行、$i-1$ 行以及 $i-2$ 行是否被操作（我们分别用 $x,y,z$ 记录，显然 $x,y,z\in\{0,1\}$），通过一个 `check()` 函数判断这三行是否保证**对于第 $i-1$ 行的每个位置，它的上下左右四个数有至少一个数与其相等**。

若保证，$f_{i,x,y,z}=\min(f_{i-1,y,z,0},f_{i-1,y,z,1})+x$。否则不做操作。

初始化则将所有的 $f$ 数组赋值为 `0x3f`，$f_{1,0,0,0}=0,f_{1,1,0,0}=1$（第一行怎么选都不会受到题目条件的影响）。

答案即为 $f_{n,x,y,z}$，其中  $x,y,z\in\{0,1\}$。

最后不要忘记**判断第 $n$ 行是否合法**。
## 代码
只放主要代码（~~之前的各种快读和火车头就不放了~~）

```cpp
/*R()函数是快读函数，write()函数是快输函数*/
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define per(a,b,c) for(int a=b;a>=c;a--)
const int N=1e3+5;
const int dx[5]={0,1,-1,0,0},dy[5]={0,0,0,1,-1};
int n,m,a[N][N];
int f[N][2][2][2];
int box[3][N];
bool check(int l,int x,int y,int z){
	rep(i,1,m){
		if(l-2>=1) box[0][i]=a[l-2][i]^z;
		else box[0][i]=2; 
	}
	rep(i,1,m) box[1][i]=a[l-1][i]^y;
	rep(i,1,m){
		if(l<=n) box[2][i]=a[l][i]^x;
		else box[2][i]=2;
	}
    //这里为了方便将要检查的三行放到一个 3×m 的数组里。
	rep(i,1,m){
		bool flag=0;
		rep(k,1,4){
			int tx=1+dx[k],ty=i+dy[k];
			if(ty<1||ty>m||box[tx][ty]==2) continue;
			if(box[1][i]==box[tx][ty]){
				flag=1;
				break; 
			}
		}
		if(!flag) return 0;
	}
	return 1;
}
int main(){
	n=R(),m=R();
	rep(i,1,n)rep(j,1,m)a[i][j]=R(); 
	memset(f,0x3f,sizeof f);
	f[1][0][0][0]=0,f[1][1][0][0]=1;
	rep(i,2,n){
		rep(x,0,1){//自己本身 
			rep(y,0,1){//前面一行 
				rep(z,0,1){//再前面一行 
					if(check(i,x,y,z)){
						f[i][x][y][z]=min(f[i][x][y][z],min(f[i-1][y][z][0],f[i-1][y][z][1])+x);
					}
				}
			}
		}
	}
	int ans=0x3f3f3f3f;
	rep(x,0,1){
		rep(y,0,1){
			rep(z,0,1){
				if(check(n+1,0,x,y)) ans=min(ans,f[n][x][y][z]);
			}
		}
	}
	if(ans!=0x3f3f3f3f) write(ans);
	else puts("-1");
}

```


---

## 作者：chengning0909 (赞：3)

# abc 283 e

[abc 283 e](https://atcoder.jp/contests/abc283/tasks/abc283_e)

## 题意

给定一个 $h \times w$ 的矩阵 `A`，每个元素要么是 `0`，要么是 `1`。$a_{i, j}$ 表示第 $i$ 行第 $j$ 列的数。

你可以做很多次操作：选择一个 $i$ $(1 \le i \le h)$，将第 $i$ 行的所有 $a_{i, j}$ $(1 \le j \le w)$ 都翻转（`0` 变为 `1`，`1` 变为 `0`）。

当 $a_{i, j}$ 的所有相邻格子都和它不同时，称 $a_{i, j}$ 为孤立的。

请你求出最少需要多少次操作能使得 `A` 中没有孤立的点，如果不能，输出 `-1`。

## 思路

首先，有一个很简单的做法，就是枚举每一行是翻还是不翻，总时间复杂度为 ${2 ^ h} \times w$，当然，这样时间复杂度过大，所以不考虑搜索。

那既然想到搜索，就不难看出，这是个子集搜索。

既然是子集搜索，那是不是可以考虑用 `dp` 来实现呢？（`01` 背包）

`dp[i][0/1][0/1]` 表示第 $i$ 行翻还是不翻，第 $i - 1$ 行翻还是不翻，并且前 $i - 1$ 行没有孤立点的最小翻转次数。

所以就可以得到转移方程为 `dp[i][j][k] = min(dp[i - 1][k][0], dp[i - 1][k][1]) + j`。

当然，在每次取最小值的时候，需要判断是否满足没有孤立点这个条件。

## 时间复杂度

枚举每一行，$O(h)$。

检查是否存在孤立点，$O(w)$。

总时间复杂度为 $O(h \times w)$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int H = 1010, W = 1010;

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int h, w, dp[H][2][2];
bool a[H][W];

bool P(int i, int j) {  // 检查是否为孤立点
  bool flag = 0;
  for (int f = 0; f < 4; f++) {
    int nx = i + dx[f], ny = j + dy[f];
    if (1 <= nx && nx <= h && 1 <= ny && ny <= w && a[i][j] == a[nx][ny]) {
      flag = 1;
      break;
    }
  }
  return flag;
}

bool F(int i, int j, int k, int l) {  // 检查是否不存在孤立点
  for (int f = 1; f <= w; f++) {
    a[i][f] ^= j, a[i - 1][f] ^= k, a[i - 2][f] ^= l;
  }
  bool flag = 1;
  for (int f = 1; f <= w; f++) {
    flag &= P(i - 1, f);
  }
  for (int f = 1; f <= w; f++) {
    a[i][f] ^= j, a[i - 1][f] ^= k, a[i - 2][f] ^= l;
  }
  return flag;
}

int main() {
  cin >> h >> w;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      cin >> a[i][j];
    }
  }
  // 初始化
  for (int i = 1; i <= h; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        dp[i][j][k] = h + 1;
      }
    }
  }
  dp[1][0][0] = 0, dp[1][1][0] = 1;
  for (int i = 2; i <= h; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        for (int l = 0; l < 2; l++) {
          if (dp[i - 1][k][l] != h + 1 && F(i, j, k, l)) {
            dp[i][j][k] = min(dp[i][j][k], dp[i - 1][k][l] + j);
          }
        }
      }
    }
  }
  // 求答案
  int ans = h + 1;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (dp[h][i][j] != h + 1 && F(h + 1, 0, i, j)) {
        ans = min(ans, dp[h][i][j]);
      }
    }
  }
  cout << (ans == h + 1 ? -1 : ans);
  return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc283_e)
# 0. 题目大意

给定一个 $ n \times m $ 的 01 矩阵，你可以选择一行，翻转该行所有元素。当 $ a_{i-1,j} $，$ a_{i+1,j} $，$ a_{i,j-1} $，$ a_{i,j+1} $ 与 $ a_{i,j} $ 的 01 性不相同时，我们称 $ a_{i,j} $ 为隔离。问最小需要几次操作，使得这个矩阵中没有被隔离的数。

# 1. 解题思路

这题数据范围不大，我们考虑使用 dp。定义 $ f_{i,j,k} $ 表示在遍历到第 $ i $ 行时，$ i-1 $ 行以及 $ i-2 $ 行影响是否操作，因为在遍历到第 $ i $ 行时，只会被 $ i-1 $ 行以及 $ i-2 $ 行影响。所以我们这样定义来统计方案数。dp 方程为 $ f_{i,j,k} = \min (f_{i,j,k},f_{i-1,k,p}+j) $。

# 2. 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3005;
int n,m,ans,mz[N][N];
int f[N][2][2];//dp数组
bool check(int u,int x,int y){//这里用了一个判断，来判断mz[i][j]是否满足隔离条件
	for(int i=1;i<=m;i++){
		if(mz[u][i]!=mz[u][i-1] && mz[u][i]!=mz[u][i+1] && mz[u][i]!=(mz[u-1][i]^x) && mz[u][i]!=(mz[u+1][i]^y)){
			return 0;
		}
	}
	return 1;
}
signed main(){
	scanf("%d%d",&n,&m);
	memset(mz,-1,sizeof mz);//初始化
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&mz[i][j]);
	memset(f,0x3f,sizeof f);//初始化
	f[1][0][0]=0;//初始化
	f[1][1][0]=1;//初始化
	for(int i=2;i<=n+1;i++){
		for(int j=0;j<2;j++){
			for(int k=0;k<2;k++){
				for(int q=0;q<2;q++){//四重循环枚举方案
					if(check(i-1,k^q,j^k)){//判断
						f[i][j][k]=min(f[i][j][k],f[i-1][k][q]+j);//方案数统计
					}
				}
			}
		}
	}
	ans=min(f[n+1][0][0],f[n+1][0][1]);//获取答案
	if(ans>n)
		printf("-1\n");//如果答案已经超过n，则答案无效
	else
		printf("%d\n",ans);//输出
	return 0;//完结撒花
}
```


---

## 作者：Daidly (赞：3)

被降智了。

---

赛时一直在想 $f[i][0/1]$ 不知道咋转移，浪费了一堆时间，实际上只要多加一维就好。

设 $f[i][0/1][0/1]$ 表示在第 $i$ 行是否操作，第 $i-1$ 行是否操作的情况下，使前 $i-1$ 行的所有数满足条件的方案数。这样设的原因是第 $i-1$ 行只会被第 $i$ 行和第 $i-2$ 行影响。

转移考虑枚举第 $i,i-1,i-2$ 行是否操作，判断即可。注意初值的设定。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long 

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=1e3+5;
int n,m,a[N][N],f[N][2][2];
int dx[5]={0,0,1,-1},dy[5]={1,-1,0,0};

bool check1(int x,int y){
	if(1<=x&&x<=n&&1<=y&&y<=m)return 1;
	return 0;
}

void work(int k){
	for(int i=1;i<=m;++i)a[k][i]^=1;
}

bool check(int k){
	for(int i=1;i<=m;++i){
		bool tmp=0;
		for(int j=0;j<4;++j)if(check1(k+dx[j],i+dy[j])&&a[k+dx[j]][i+dy[j]]==a[k][i]){tmp=1;break;}
		if(!tmp)return 0;
	}
	return 1;
}

signed main(){
	n=read(),m=read();
	f[n+1][0][0]=f[n+1][1][0]=f[n+1][0][1]=f[n+1][1][1]=1e9;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			a[i][j]=read();
		}
		f[i][0][0]=f[i][0][1]=f[i][1][0]=f[i][1][1]=1e9;
	}
	f[1][0][0]=0,f[1][1][0]=f[1][0][1]=1,f[1][1][1]=2;
	for(int i=2;i<=n+1;++i){
		for(int j=0;j<=1;++j){
			if(j)work(i);
			for(int k=0;k<=1;++k){
				if(k)work(i-1);
				for(int l=0;l<=1;++l){
					if(l)work(i-2);
					if(check(i-1))f[i][j][k]=min(f[i][j][k],f[i-1][k][l]+j);
					if(l)work(i-2);
				}
				if(k)work(i-1);
			}
			if(j)work(i);
		}
	}
	int ans=min(min(f[n+1][0][0],f[n+1][0][1]),min(f[n+1][1][0],f[n+1][1][1]));
	if(ans>n)puts("-1");
	else print(ans);
	return 0;
}
```

---

## 作者：SnapYust (赞：1)

# 题目传送门

[[ABC283E] Don't Isolate Elements](https://www.luogu.com.cn/problem/AT_abc283_e)

# 思路

我写完这道题才发现我是个小丑，我一看题解，发现大家都用的是 DP，但**没有人**的代码超过百行（）。

我是直接暴力 DP 做的，自然地，我们看到这种题一般会想到设 $dp_i$ 为前 $i$ 行的最小步数。

但是题目的要求矩阵中任意一个元素都**不被孤立**，而孤立的条件是四面的元素性质不同，所以这至少是个三维 DP，设 $dp_{i,j(j\in[0,1]),k(k\in[0,1])}$ 表示前 $i$ 行中，第 $i$ 行是否翻转和第 $i-1$ 行是否翻转，若不能使矩阵合法，则当前记为 $-1$。

在猜转移方程前，我们要先给出两个**命题**：

命题一：对于 $\forall i$ 满足 $1\le i\le n$，若 $dp_{i,j(j\in[0,1]),k(k\in[0,1])}=-1$，则通过这个状态得到的下一个状态也是 $-1$。

证明：因为当前的状态不合法，所以由不合法的状态延申下去的下一个状态必然不合法。

命题二：对于 $i=1$，$dp_{i,j(j\in[0,1]),k(k\in[0,1])}$ 必然合法。

证明：因为我们设计状态时只考虑 $i$ 行及以前的行，而单独一行不能满足孤立一个元素的条件，于是命题得证。

于是：

$$dp_{1,0,0}=dp_{1,0,1}=0$$

$$dp_{1,1,0}=dp_{1,1,1}=1$$

状态转移方程就是**暴力匹配**，**暴力判断**，**暴力取优**。

如果 $i=2$，那一共要转移 $2\times 2=4$ 种情况。

如果 $2<i\le n$，那一共要转移 $2\times 2\times 2=8$ 种情况。

记得最后还要判断最后一行是否合法。

如果像我一样暴力写的话，就会写 $233$ 行（）。

# Code

放代码了。

## 非压行代码

[这里](https://www.luogu.com.cn/paste/a00b653w)

---

## 作者：WaterSun (赞：0)

UPD：23.8.8 更新了对状态定义的描述，感谢 @liaoyichen。

# 思路

$dp_{i,0/1,0/1,0/1}$ 表示第 $i$ 行 是/否 操作，第 $i - 1$ 行 是/否 操作，第 $i - 2$ 行 是/否 操作的最小次数，并且使得前 $i - 1$ 行合法。

每一次转移第 $i$ 行的 $dp$ 时，枚举 $i,i - 1,i - 2$ 行的操作状态。暴力判断这些状态能否满足题意，如果可以，能得到状态转移方程：

$$
dp_{i,x,y,z} = \max(dp_{i - 1,y,z,0},dp_{i - 1,y,z,1}) + x
$$

最终的答案就是满足条件的 $\max(dp_{n,x,y,z})$。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1010,inf = 0x3f3f3f3f;
int n,m,ans = inf;
int dx[] = {0,1,-1,0,0};
int dy[] = {0,0,0,1,-1};
int st[5][N],arr[N][N];
int dp[N][2][2][2];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline bool check_node(int x,int y){
	for (re int i = 1;i <= 4;i++){
		int tx = x + dx[i];
		int ty = y + dy[i];
		if (tx >= 1 && tx <= 3 && ty >= 1 && ty <= m && st[x][y] == st[tx][ty]) return true;
	}
	return false;
}

inline bool check(int x,bool fa,bool fb,bool fc){
	for (re int j = 1;j <= m;j++){
		if (x == 2) st[1][j] = -1;
		else st[1][j] = arr[x - 2][j] ^ fc;
	}
	for (re int j = 1;j <= m;j++) st[2][j] = arr[x - 1][j] ^ fb;
	for (re int j = 1;j <= m;j++){
		if (x == n + 1) st[3][j] = -1;
		else st[3][j] = arr[x][j] ^ fa;
	}
	for (re int j = 1;j <= m;j++){
		if (!check_node(2,j)) return false;
	}
	return true;
}

int main(){
	memset(dp,inf,sizeof(dp));
	dp[1][0][0][0] = 0;
	dp[1][1][0][0] = 1;
	n = read();
	m = read();
	for (re int i = 1;i <= n;i++){
		for (re int j = 1;j <= m;j++) arr[i][j] = read();
	}
	for (re int i = 2;i <= n;i++){
		for (re int x = 0;x <= 1;x++){
			for (re int y = 0;y <= 1;y++){
				for (re int z = 0;z <= 1;z++){
					if (check(i,x,y,z)) dp[i][x][y][z] = min(dp[i - 1][y][z][0],dp[i - 1][y][z][1]) + x;
				}
			}
		}
	}
	for (re int x = 0;x <= 1;x++){
		for (re int y = 0;y <= 1;y++){
			for (re int z = 0;z <= 1;z++){
				if (check(n + 1,0,x,y)) ans = min(ans,dp[n][x][y][z]);
			}
		}
	}
	if (ans == inf) puts("-1");
	else printf("%d",ans);
	return 0;
}
```

---

