# Guards In The Storehouse

## 题目描述

Polycarp owns a shop in the capital of Berland. Recently the criminal activity in the capital increased, so Polycarp is thinking about establishing some better security in the storehouse of his shop.

The storehouse can be represented as a matrix with $ n $ rows and $ m $ columns. Each element of the matrix is either . (an empty space) or x (a wall).

Polycarp wants to hire some guards (possibly zero) to watch for the storehouse. Each guard will be in some cell of matrix and will protect every cell to the right of his own cell and every cell to the bottom of his own cell, until the nearest wall. More formally, if the guard is standing in the cell $ (x_{0},y_{0}) $ , then he protects cell $ (x_{1},y_{1}) $ if all these conditions are met:

- $ (x_{1},y_{1}) $ is an empty cell;
- either $ x_{0}=x_{1} $ and $ y_{0}<=y_{1} $ , or $ x_{0}<=x_{1} $ and $ y_{0}=y_{1} $ ;
- there are no walls between cells $ (x_{0},y_{0}) $ and $ (x_{1},y_{1}) $ . There can be a guard between these cells, guards can look through each other.

Guards can be placed only in empty cells (and can protect only empty cells). The plan of placing the guards is some set of cells where guards will be placed (of course, two plans are different if there exists at least one cell that is included in the first plan, but not included in the second plan, or vice versa). Polycarp calls a plan suitable if there is not more than one empty cell that is not protected.

Polycarp wants to know the number of suitable plans. Since it can be very large, you have to output it modulo $ 10^{9}+7 $ .

## 说明/提示

In the first example you have to put at least one guard, so there are three possible arrangements: one guard in the cell $ (1,1) $ , one guard in the cell $ (1,3) $ , and two guards in both these cells.

## 样例 #1

### 输入

```
1 3
.x.
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 2
xx
xx
```

### 输出

```
1
```

## 样例 #3

### 输入

```
2 2
..
..
```

### 输出

```
10
```

## 样例 #4

### 输入

```
3 1
x
.
x
```

### 输出

```
2
```

# 题解

## 作者：ademik (赞：3)

### [Guards In The Storehouse](https://www.luogu.com.cn/problem/CF845F)

代码和思路均借鉴于 [Hasan0540](https://codeforces.com/profile/Hasan0540)，请尽情的 %%% 他吧。

-----

我们考虑对于任意一个格子 $(x, y)$，它存在的可能的状态：

+ 当 $(x, y)$ 已经被摄像头覆盖时，那么我们可以选择直接跳过这个位置，也可以选择在当前位置再放置一个摄像头，这是两种不同的方案。
+ 当 $(x, y)$ 没有被摄像头覆盖时，与上面不同的是，我们还可以选择不覆盖当前位置，直接跳过他，也就是使用可以有一个空地不被摄像头覆盖的机会。
+ 如果 $(x, y)$ 是一个障碍物的话，他并不会增加新的方案，只会影响摄像头的监控情况。

这样看来，每个位置最多只有 $3$ 种不同的状态，而我们要维护的信息有：当前的位置，当前的格子是否被覆盖，一个空地不被摄像头覆盖的机会是否已经使用。

当前的位置可以直接从 $(0, 0) \sim (n - 1, m - 1)$ 枚举。

当前格子是否被覆盖可以分成两部分，是否被该列上方的摄像头覆盖和是否被该行左端的摄像头覆盖，该行左端是否存在摄像头可以直接记录状态即可。注意到 $n \times m \le 250$，即 $\min(n, m) \le 15$，我们可以直接用二进制维护每一列是否被覆盖。

至于一个空地不被摄像头覆盖的机会是否已经使用，一个 bool 解决问题。

至于实现方面，感觉用记忆化搜索更为精炼。

----

```cpp
# include <bits/stdc++.h>
# define TIME 1e3 * clock() / CLOCKS_PER_SEC
using std :: cin; using std :: cout; using std :: max;
using std :: min; using std :: cerr; using std :: vector; 
typedef long long i64; 
typedef std :: pair < int, int > pii; 
const int N = 1e5 + 50, Mod = 1e9 + 7;
i64 dp[251][1 << 15][2][2]; 
int n, m; 
char ch[251][251];
// (x, y) 表示当前的坐标， st 表示哪些列已经被上面的摄像头覆盖。 
// hav 表示是否已经有一个没有被覆盖的空格，cover 表示当前行的左端是否存在一个摄像头能覆盖到当前位置。 
i64 dfs(int x, int y, int st, bool hav, bool cover)
{
	if(y == m) return dfs(x + 1, 0, st, hav, false); // 到达一行的末尾，失去行的限制。  
	if(x == n) return 1; 
	i64 &res = dp[x * m + y][st][hav][cover]; 
	if(res != -1) return res; 
	res = 0; 
	if(ch[x][y] == '.') {
		if(cover || ((st >> y) & 1)) res = dfs(x, y + 1, st, hav, cover); // 当前位置已经被覆盖了， 可以直接前往下一个位置 
		res += dfs(x, y + 1, st | (1 << y), hav, true); // 尝试在当前位置放置一个摄像头，这两种是不同的方案 
		res %= Mod; 
		if(hav == false && cover == false && !((st >> y) & 1)) { // 如果当前位置尚没有被覆盖且还有空一格的机会 
			res += dfs(x, y + 1, st, true, cover); // 尝试跳过当前的空格 
			res %= Mod; 
		}
	} else {
		res = dfs(x, y + 1, st & (~(1 << y)), hav, false); // 遇到了一个障碍， 那么当前行的左端和当前列的上端的摄像头被阻断。 
	}
	return res; 
} 
int main()
{
	std :: ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0); 
	cin >>n >>m; 
	for(int i = 0; i < n; i ++) cin >>ch[i]; 
	if(n < m) {
		for(int i = 0; i < n; i ++) {
			for(int j = i; j < m; j ++) std :: swap(ch[i][j], ch[j][i]); 
		}
		std :: swap(n, m); 
	}
	memset(dp, -1, sizeof(dp)); 
	cout <<dfs(0, 0, 0, false, false) <<"\n"; 
	return 0; 
}
```

---

## 作者：极寒神冰 (赞：2)

因为 $n\times m\le 250$，因此总存在 $\min\{n,m\}\le 15$，下面假设 $m\le 15$。

考虑轮廓线 DP

记 $dp_{i,j,S,o1,o2}$ 表示当前扫描到第 $i$ 行第 $j$ 列，前面的所有格子已经确定，上面的看守能覆盖的列的集合为 $S$，左边是否有能覆盖当前位置 $o1$，前面是否已经有没有覆盖的格子 $o2$ 的方案数。

然后考虑转移。

若 $(i,j)$ 是障碍，则转移显然为

$$
dp_{i,j+1,S\backslash \{j\},0,o2 }+=dp_{i,j,S,o1,o2}
$$

否则 $(i,j)$ 为空地，考虑分类讨论：

1. 在这个位置放摄像头，有 $dp_{i,j+1,S\cup\{j\},1,o2}+=dp_{i,j,S,o1,o2}$
  
2. 否则不放摄像头：
  
  1. 如果 $(i,j)$ 没有被覆盖到，有 $dp_{i,j+1,S,o1,1}+=[j\not\in S][!o1][!o2]dp_{i,j,S,o1,o2}$
    
  2. 否则 $(i,j)$ 被覆盖到了，有 $dp_{i,j+1,S,o1,o2}+=[j\in S\lor o1]dp_{i,j,S,o1,o2}$。
    

然后考虑怎么转移到下一行，显然就是 $dp_{i+1,0,S,0,o2}=dp_{i,m,S,1,o2}+dp_{i,m,S,0,o2}$。

答案就是最后位置所有情况的和。

时间复杂度 $\mathcal O(2^mnm)$。

```cpp
#include<bits/stdc++.h>
//#define int long long
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
using namespace std;
const int mod=1e9+7;

char str[266][266];
int n,m;
int dp[266][66666][2][2];
int cur;
inline void add(int &x,const int y)
{
	x+=y;x>=mod?x-=mod:1;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin>>n>>m;
	R(i,0,n-1) cin>>str[i];
	if(n<m) {R(i,0,n-1) R(j,i,m-1) swap(str[i][j],str[j][i]);swap(n,m);}
	dp[0][0][0][0]=1;
	int t,tS,t1,t2;
	R(i,0,n-1) 
	{	
		R(j,0,m-1) R(S,0,(1<<m)-1) R(o1,0,1) R(o2,0,1) if(t=dp[j][S][o1][o2])
		{
			if(str[i][j]=='x')
			{
				tS=S&(~(1<<j)),t1=0,t2=o2;
				add(dp[j+1][tS][t1][t2],t);
			}
			else
			{
				int tt=(o1||(S&(1<<j)));
				tS=S,t1=o1,t2=o2+(1-tt);
				if(t2<=1) add(dp[j+1][tS][t1][t2],t);
				tS|=(1<<j);t1=1,t2=o2;
				add(dp[j+1][tS][t1][t2],t);
 			}
 			dp[j][S][o1][o2]=0;
		}
		R(S,0,(1<<m)-1) R(o1,0,1) R(o2,0,1)
		{
			add(dp[0][S][0][o2],dp[m][S][o1][o2]);
			dp[m][S][o1][o2]=0;
		}
	}
	int ans=0;
	R(S,0,(1<<m)-1) R(o2,0,1) add(ans,dp[0][S][0][o2]);
	cout<<ans<<endl;
}
```

---

