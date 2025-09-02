# DCEPC11J - Jailbreak

## 题目描述

The great King Kapish has prisoned Pushap, for he loves the princess Padmavati. To make sure that Pushap and Padmavati never meet again, King Kapish has kept Pushap in his most mysterious of jail.

This jail is built in a 2D rectangular grid fashion, containing M\*N prison cells. The entrance gate for jail is at bottom left corner (0,0). The mysteriousness of this jail comes from the fact that once a prisoner is taken from entrance gate (0,0) to any prison cell, then that prisoner can escape only if he comes back to the entrance visiting the cells used on his way from entrance to his prison cell. Note that in the escape, it is not required for the prisoner to trace the exact path or visit all the cells used on his way up, rather the condition is to use/visit only those prison cells used on his way up. Additionally, when the prisoner is taken from entrance (0,0) to a prison cell, they can fathom upto 2 cells in a single move/step in either upward direction or right direction. And when the prisoner is escaping, he can fathom upto 2 cells in a single move/step in either downward or left direction.

King Kapish orders to jail prisoner Pushap in cell (M-1,N-1).

You, being a common friend to Pushap and Padmavati, have to help Pushap escape the prison. **Tell him the number of ways in which he can go up to cell (M-1,N-1) and then come back following the procedure described above. Please refer explanation part to know more.**

## 说明/提示

**【样例解释】**

对于第二组数据，一种可能的路径如下：

$(0,0) \to (0,1) \to (0,2) \to (1,2) \to (0,2) \to (0,0)$。

## 样例 #1

### 输入

```
3
2 2
2 3
3 4
```

### 输出

```
2
7
66
```

# 题解

## 作者：OldVagrant (赞：2)

## 题意
[题意传送门](https://www.luogu.com.cn/problem/SP16212)  
~~翻译是我写的，所以可能读起来会很令人费解，请见谅。~~
## Solution
因为题上说的是在 $M\times N$ 的迷宫里从 $(0,0)$ 走到 $(M-1,N-1)$  再回来，不妨转化为从 $(1,1)$ 走到 $(M,N)$ 再回到 $(1,1)$。      
考虑 dp，令 $dp_{i,j}$ 表示从 $(1,1)$ 走到 $(i,j)$ 再走回来的方案数。显而易见，```Pushap```往回走的时候可以沿原路返回，所以就有了 $dp_{i,j}=dp_{i-1,j}+dp_{i-2,j}+dp_{i,j-1}+dp_{i,j-2}$。      
但还要考虑到一种情况，就如样例解释那般，```Pushap```在去的时候走了两步从 $(0,0)$ 到 $(0,1)$ 再到 $(0,2)$，他回来时除了选择走原路之外还可以选择从 $(0,2)$ 一步走到 $(0,0)$，这也是一种不同的方案。       
所以 $dp_{i,j}$ 还应在原来的基础上再加上 $dp_{i-2,j}$ 和 $dp_{i,j-2}$。     
转移方程： $dp_{i,j}=dp_{i-1,j}+2\times dp_{i-2,j}+dp_{i,j-1}+2\times dp_{i,j-2}$。        
边界：
$dp_{1,1}=1,\forall i\in [1,m],dp_{0,i}=0,\forall j\in [1,n],dp_{j,0}=0$。
## Code
记得不停取模，少了可能会炸```int```。
```
#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int dp[501][501];
signed main(){
	int t,n,m;
	dp[1][1]=1,scanf("%d",&t);
	for(int i=1;i<501;i++){
		for(int j=1;j<501;j++){
			if(i==1&&j==1) continue;
			if(j>2) dp[i][j]=(dp[i][j]+(dp[i][j-2]*2%mod))%mod;
			if(j>1) dp[i][j]=(dp[i][j]+dp[i][j-1])%mod;
			if(i>1) dp[i][j]=(dp[i][j]+dp[i-1][j])%mod;
			if(i>2) dp[i][j]=(dp[i][j]+(dp[i-2][j]*2%mod))%mod;
		}
	}while(t--) scanf("%d%d",&n,&m),printf("%d\n",dp[n][m]);
	return 0;
}
```


---

## 作者：lovely_hyzhuo (赞：1)

这是一道比较简单的动态规划问题。

定义 $dp_{i,j}$ 为走到 $(i,j)$ 位置并回去的方案数。

那么转移方程就是 $dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}+dp_{i-2,j}+dp_{i,j-2}$。

但是，这样不对，为什么呢？

就像样例解释里面写的，除过原路返回之外，也有类似像第一篇题解里面说的“跳步”和“分段”现象。

所以再加上 $dp_{i-2,j}+dp_{i,j-2}$ 就是最终结果。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int momo=1e9+7; 
int dp[1010][1010]; 
int main()
{
	
	//由于有多组数据，每回都跑的话，应该会超时，所以放到预处理，输出时O（1）输出就行 
	int t;
	cin>>t;//数据个数
	dp[1][1]=1;//走到1，1点显然只有一种方式 
	for(int i=1;i<=500;i++)
	{
		for(int j=1;j<=500;j++)
		{
			if(i==1&&j==1)
				continue;//假如为左上角，跳出
			if(j>=1)
				dp[i][j]=(dp[i][j]+dp[i][j-1]%momo)%momo;
			if(j>=2)
				dp[i][j]=(dp[i][j]+dp[i][j-2]*2%momo)%momo; 
			if(i>=2)
				dp[i][j]=(dp[i][j]+dp[i-2][j]*2%momo)%momo;
			if(i>=1)
				dp[i][j]=(dp[i][j]+dp[i-1][j]%momo)%momo;
			dp[i][j]%=momo;
		}
	} 
	int n,m;
	while(t--)
	{
		cin>>n>>m;
		cout<<dp[n][m]<<endl;
	}
	return 0;
}
```


---

## 作者：alex_liu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/SP16212)

思路：

首先看到题目中所说的地图是没有改变的，且有多组数据，所以可以尝试预处理。

很明显这是一道 DP 题，按照题意要求设 $f[i][j]$ 表示从起点 $(0,0)$ 走到 $(i,j)$ 的总方案数，则可以从四个方向进行转移，即从 $f[i-1][j]$，$f[i-2][j]$，$f[i][j-1]$，$f[i][j-2]$ 转移而来（当转移点的坐标在地图范围内）。

但有一点是需要注意的：由于走完一遍之后是要原路返回，那么就会出现如下情况

![ ](https://cdn.luogu.com.cn/upload/image_hosting/79nt6eua.png)

当前这是地图中一种可能的路线，我们设红色路线为从起点到终点的路径，蓝色为返回的路径，那么你就会发现：在红色路线中，从 $(2,0)$ 走到 $(2,2)$ 只用了一步，而在蓝色路线中，却用了两步。所以说一次走两步的情况下返回时就会出现两种情况，所以方案数要 $\times \,2$。

初始化：$f[0][0]=1$；答案：$f[n][m]$

最后放一下代码：

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(!(c^'-'))f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c&15),c=getchar();
	return x*f;
}
int n,m,t,f[505][505];
inline bool check(int x,int y){return x>=0&&x<=504&&y>=0&&y<=504;}
int main(){
	t=read();
	f[0][0]=1;
	for(int i=0;i<505;i++){//预处理
		for(int j=0;j<505;j++){//由四个方向转移而来，注意上述的特殊情况
			if(check(i,j-1))(f[i][j]+=f[i][j-1])%=mod;
			if(check(i,j-2))(f[i][j]+=((f[i][j-2]<<1)%mod))%=mod;
			if(check(i-1,j))(f[i][j]+=f[i-1][j])%=mod;
			if(check(i-2,j))(f[i][j]+=((f[i-2][j]<<1)%mod))%=mod;
		}
	}
	while(t--)cout<<f[read()-1][read()-1]<<endl;
	return 0;
}
```


---

## 作者：fly_and_goal (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP16212)
# 题目描述
这是一道动态规划。
# 题目思路
要知道到达 $f_{i,j}$ 有几种方法，实际上就是求 $f_{i-1,j}+f_{i-2,j}\times2+f_{i,j-1}+f_{i,j-2}\times2$ 的和，再优化一下，虽然有多组数据，但是都可以用一个图来表示，所以先算出图各个位置的值，最后输入时直接输出。
# 注意
记得取模。
# code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,f[10005][10005];
long long mod=1e9+7;
int main()
{
	cin>>t;
	f[1][1]=1;
	for(int j=1;j<=505;j++)
	{
		for(int k=1;k<=505;k++)
		{
			if(j==1&&k==1) continue;
			if(j>=1) f[j][k]=(f[j][k]+f[j-1][k])%mod;
			if(j>=2) f[j][k]=(f[j][k]+f[j-2][k]*2)%mod;
			if(k>=2) f[j][k]=(f[j][k]+f[j][k-2]*2)%mod;
			if(k>=1) f[j][k]=(f[j][k]+f[j][k-1])%mod;
			f[j][k]%=mod;
		}
	}//先算出各个位置的值
	for(int i=1;i<=t;i++)
	{
		cin>>n>>m;
		cout<<f[n][m]<<endl;
	}//输出
}
```

---

## 作者：_Sky_Dream_ (赞：0)

# [传送门](https://www.luogu.com.cn/problem/SP16212)

显然，这是一题简单的 dp。

我们假设 $dp_{i,j}$ 代表从 $(i,j)$ 走回去的路程。

那么显然 $dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}+dp_{i+1,j}+dp_{i,j+1}+dp_{i,j-2}+dp_{i-2,j}$。

后面两项是分段和跳步。


```cpp
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define int long long
#define MAX 1145141919810
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define dep(i,x,y) for(int i=x;i>=y;--i)
#define N 114514
#define mod 1000000007
using namespace std;
int T,m,n;
int dp[1010][1010]; 
inline void Main(){
	cin>>n>>m;
	cout<<dp[n][m]<<endl;
}
void Enchanted(){
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	dp[1][1]=1;
	rep(i,1,500)
		rep(j,1,500){
			if(i==1&&j==1)continue;
			if(j>=1)dp[i][j]=(dp[i][j]+dp[i][j-1]%mod)%mod;
			if(j>=2)dp[i][j]=(dp[i][j]+dp[i][j-2]*2%mod)%mod; 
			if(i>=2)dp[i][j]=(dp[i][j]+dp[i-2][j]*2%mod)%mod;
			if(i>=1)dp[i][j]=(dp[i][j]+dp[i-1][j]%mod)%mod;
			dp[i][j]%=mod;
		}
	cin>>T;
	while(T--)Main();
	exit(0);
}
signed main(){Enchanted();}



```

---

## 作者：__Sky__Dream__ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/SP16212)

## 题目大意
有一个 $M \times N$ 的迷宫，小 P 要从 $(0,0)$ 走到 $(M-1,N-1)$，再从此处返回，输出对 $10^9+7$ 取模后的路线数。每次小 P 只能向下或右走 $1$ 格或 $2$ 格。

## 解题思路
妥妥的**动态规划**。

我们不妨将从 $(0,0)$ 走到 $(M-1,N-1)$ 转化为从 $(1,1)$ 走到 $(M,N)$。

先开一个数组 $a_i$，很容易知道走到 $a_{1,1}$ 只有一种情况，则在**循环外面**令 $a_{1,1}=1$。

继续，我们考虑一下两种情况：

1. 小 P 原路返回，这是正常情况，那么就有 $a_{i,j}=a_{i-1,j}+a_{i,j-1}+a_{i-2,j}+a_{i,j-2}$。
1. 小 P 在返回时可能将原来需要走两个一步的合并成一步，那么我们就需要再加上一个 $a_{i-2,j}$ 和 $a_{i,j-2}$。

这样我们得出的方程式为 $a_{i,j}=a_{i-1,j}+a_{i,j-1}+2 \times a_{i-2,j}+2 \times a_{i,j-2}$。

注意，一定要**一直取模**，否则会爆掉（其余见代码）！

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MOD=1e9+7; 
int a[501][501]; 
int main()
{
	cin.tie(0);cout.tie(0);
    ios::sync_with_stdio(false);//加速一波~~
	int T,n,m;
	//预处理
	a[1][1]=1;//走到(1,1)点只有一种方式 
	for(int i=1;i<=500;i++)
	{
		for(int j=1;j<=500;j++)
		{
			if(i==1&&j==1)
				continue;//特判，左上角跳出
			if(j>=1)
				a[i][j]=(a[i][j]+a[i][j-1]%MOD)%MOD;
			if(j>=2)
				a[i][j]=(a[i][j]+a[i][j-2]*2%MOD)%MOD; 
			if(i>=2)
				a[i][j]=(a[i][j]+a[i-2][j]*2%MOD)%MOD;
			if(i>=1)
				a[i][j]=(a[i][j]+a[i-1][j]%MOD)%MOD;
			a[i][j]%=MOD;//不停取模，否则会爆掉（当然你也可以开long long）
		}
	} 
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		cout<<a[n][m]<<endl;
	}
	return 0;
}
```
本题坑点多，做时**一定小心**，**拒绝抄袭**！

---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/SP16212)

[SPOJ 链接](https://www.spoj.com/problems/DCEPC11J/)

题目大意：

有一个 $m\times n$ 的迷宫，你需要从 $(1,1)$ 走到 $(m,n)$，再返回。你每次可以向下或向右走 $1$ 或 $2$ 格。输出你有多少种路线。请把结果对 $10^9+7$ 取模，然后输出。

思路：

经典的 dp 题。我们先开一个 $dp$ 数组，$dp(i,j)$ 表示从 $(1,1)$ 走到 $(i,j)$。

显然 $dp(1,1)=1$。接下来我们考虑 $dp(i,j)$ 的值。

- 第一种情况：$dp(i,j)=dp(i-2,j)+dp(i-1,j)+dp(i,j-2)+dp(i,j-1)$。
- 第二种情况：我们发现，向下或向右走 $2$ 格时，返回时可能需要 $2$ 步，所以我们需要把 $dp(i-2,j)$ 和 $dp(i,j-2)$ 多加一遍。

由此可以推出状态转移方程：$dp(i,j)=2dp(i-2,j)+2dp(i,j-2)+dp(i-1,j)+dp(i,j-1)$。

因为本题有多组数据，所以我们可以采用先预处理 $500\times 500$ 格子里 $dp$ 数组的值。

坑点：

1. 要一直取模，否则会爆 ```int```！
1. 如果 $i=2$ 或者 $j=2$ 需要做特殊判断，修改状态转移方程！（细节见代码）
1. 初始状态 $dp(1,1)=1$ 不要在状态转移方程里重新计算一遍！

上代码：
```cpp
#include <iostream>
using namespace std;

int dp[501][501];
const int mod = 1e9 + 7;

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout 加速
    // 预处理
    dp[1][1] = 1;
    for (int i = 1; i <= 500; i++){
        for (int j = 1; j <= 500; j++){
            if (i == 1 && j == 1){
                continue;
            }
            // 注意特判
            if (j > 2){
                dp[i][j] = (dp[i][j] + (dp[i][j - 2] << 1) % mod) % mod;
            }
            if (j > 1){
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % mod;
            }
            if (i > 1){
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
            }
            if (i > 2){
                dp[i][j] = (dp[i][j] + (dp[i - 2][j] << 1) % mod) % mod;
            }
        }
    }
    // 边输入边输出
    int t;
    cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        cout << dp[n][m] << "\n";
    }
    return 0;
}
```

---

## 作者：hulu107027 (赞：0)

## 题面简述 

```Pushap``` 要从 $(0,0)$ 到 $(M-1,N-1)$ ，再从 $(M-1,N-1)$ 到 $(0,0)$ ，问你方案数。

当 ```Pushap``` 从 $(0,0)$ 到 $(M-1,N-1)$ 时，他可以在向下或向左一次移动一格或两格；当 ```Pushap``` 从 $(M-1,N-1)$ 到 $(0,0)$ 时，他可以在向上或向右一次移动一格或两格。

## 思路

题目要我们求一来一回的方案数，我们可以只考虑一趟的方案数，因为两趟需要走的路程是一样的。

这题的标算是动态规划，但是我们完全可以用搜索解决。

## 解决办法

### 暴力：直接搜索

从起点开始，每次向两个方向搜索，如果到达终点，计数器加一；如果越出边界，就返回上一层。

但是，这样显然超时，过不了此题，只能过 $2 \le M, N \le 10$ 的数据。

### 正解：记忆化搜索

搜索的基础上添加记忆化数组，搜索完某个状态后记录这个状态的值，后面搜到这个状态就直接返回记录的值，不用重新搜索了，节省了大量时间，可过全部数据。

## 温馨提醒：
1. 记得开 ```long long``` 。
2. 记得取模。
3. 多组数据，记忆化数组记得初始化。

[赶紧去写题吧](https://www.spoj.com/problems/DCEPC11J/)

---

