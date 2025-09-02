# Pig and Palindromes

## 题目描述

Peppa the Pig was walking and walked into the forest. What a strange coincidence! The forest has the shape of a rectangle, consisting of $ n $ rows and $ m $ columns. We enumerate the rows of the rectangle from top to bottom with numbers from $ 1 $ to $ n $ , and the columns — from left to right with numbers from $ 1 $ to $ m $ . Let's denote the cell at the intersection of the $ r $ -th row and the $ c $ -th column as $ (r,c) $ .

Initially the pig stands in cell $ (1,1) $ , and in the end she wants to be in cell $ (n,m) $ . Since the pig is in a hurry to get home, she can go from cell $ (r,c) $ , only to either cell $ (r+1,c) $ or $ (r,c+1) $ . She cannot leave the forest.

The forest, where the pig is, is very unusual. Some cells of the forest similar to each other, and some look very different. Peppa enjoys taking pictures and at every step she takes a picture of the cell where she is now. The path through the forest is considered to be beautiful if photographs taken on her way, can be viewed in both forward and in reverse order, showing the same sequence of photos. More formally, the line formed by the cells in order of visiting should be a palindrome (you can read a formal definition of a palindrome in the previous problem).

Count the number of beautiful paths from cell $ (1,1) $ to cell $ (n,m) $ . Since this number can be very large, determine the remainder after dividing it by $ 10^{9}+7 $ .

## 说明/提示

Picture illustrating possibilities for the sample test.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF570E/1750d14a00d2edc9eb520f318da4c67fc4fa62eb.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF570E/ee575715d9252bd2d977566068b38554eae9d823.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF570E/0243c25422c1404c0b2f44223b22fda4e436e3b6.png)

## 样例 #1

### 输入

```
3 4
aaab
baaa
abba
```

### 输出

```
3```

# 题解

## 作者：CYZZ (赞：6)

# [Pig and Palindromes](https://www.luogu.com.cn/problem/CF570E)
首先看到 $n \le 500$ 双向搜索会炸，自然想到 DP。
## 题意
求从 $(1,1)$ 走到 $(n,m)$ 的所有路径中回文串的个数，每步只能向右或向下。

因为是回文串，所以可以把题目转化为：两人从 $(1,1)$ 和 $(n,m)$ 分别出发，在图中某点相遇，两条路径构成的字符串相同，求走法个数。
## 状态设计
可以暴力的设 $dp_{i,j,p,q}$ 为第一个人走到 $(i,j)$，第二个人走到 $(p,q)$ 的方法数，但是四维的状态肯定时空爆炸。

我们发现只要步数和横坐标确定了，纵坐标也就确定了。所以可以把状态压缩为 $dp_{step,i,p}$ 表示走了 $step$ 步，第一和第二个人的横坐标分别为 $i$ 和 $p$。则易得 $j=step-i+1$ 且 $q=n+m-step-p+1$。
## 转移方程
状态转移方程就很好想了。$i$ 和 $p$ 分别可以从 $4$ 个方向上转移过来，条件是 $map_{i,j}=map_{p,q}$。
$$dp_{step,i,p}=dp_{step-1,i-1,p}+dp_{step-1,i,p+1}+dp_{step-1,i-1,p+1}+dp_{step-1,i,p}$$
枚举的范围要考虑步数和横纵坐标的大小，具体见代码。
## 细节处理
初始值：$dp_{1,1,n}=1$。

答案：易知两点相遇的位置总是在矩形的对角线上，所以需要分 $n+m$ 的奇偶讨论。

优化：$dp$ 数组的空间 $500^3=125000000$ 还是会 MLE。我们发现每一步的枚举只需要上一步的答案，所以可以用滚动数组优化。当然倒序枚举也可以优化。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,ans,now=1;
int dp[2][505][505];
char s[505][505];
signed main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)
    {
        getchar();
        for(int j=1;j<=m;j++)
        {
            s[i][j]=getchar();
        }
    }
    if(s[1][1]!=s[n][m])//小特判
    {
        printf("0");
        return 0;
    }
    dp[1][1][n]=1;
    for(int k=2;k<=(n+m)/2;k++)
    {
        now^=1;//滚动数组
        memset(dp[now],0,sizeof dp[now]);//记得清空
        for(int i=1;i<=min(k,n);i++)
        {
            for(int p=n;p>=max(n-k,i);p--)
            {
                int j=k-i+1,q=n+m-k-p+1;
                if(s[i][j]==s[p][q])
                    dp[now][i][p]=(dp[now^1][i-1][p]+dp[now^1][i][p+1]+dp[now^1][i-1][p+1]+dp[now^1][i][p])%1000000007;//状态转移
            }
        }
    }
    if((n+m)&1)//奇数的情况
        for(int i=1;i<=n;i++)
        {
            ans=(ans+dp[now][i][i]+dp[now][i][i+1])%1000000007;
        }
    else//偶数的情况
        for(int i=1;i<=n;i++)
        {
            ans=(ans+dp[now][i][i])%1000000007;
        }
    printf("%lld",ans);
}

```
希望本篇题解可以帮到大家！！！

---

## 作者：AbsMatt (赞：2)

## [题目传送器](https://www.luogu.com.cn/problem/CF570E)
## [更爽的阅读体验](https://yaohaoyou.blog.luogu.org/cf570e-pig-and-palindromes-ti-xie)

# 题意
从 $(1,1)$ 到 $(n,m)$，每次只能向下或向右，求使路过的路径为回文串的路径数。

# 思路
$0 \le n,m \le 500$ 的数据可以看出这是一道 dp 题，接下来就是只要思考如何设计 dp 了。

### 状态定义
$dp_{i,j}$ 为从中点出发，走了 $s$ 步后，左上的点的横坐标为 $i$，右下的点横坐标为 $j$ 的回文路径数。

左上角：$(x,s+1-x)$，右下角：$(x,n+m-s-x+1)$。

### 状态转移方程
$dp_{s,i,j}=dp_{s-1,i-1,j}+dp_{s-1,i,j+1}+dp_{s-1,i-1,j+1}+dp_{s-1,i,j}$。

### 初始化
$dp_{1,1,n}=1$。

### 优化
直接 dp 的话空间复杂度将是 $O(n^3)$，会 MLE，所以这里可以用滚动数组和倒序搜索，我使用的是滚动数组，空间复杂度就是 $O(n^2)$。

### 总结
这道题的 dp 思路和状态转移比较复杂，导致我赛时 $21$ 分，推出方程后就比较简单了。不开 ```long long``` 见祖宗，时间复杂度为 $O(n^3)$。

## AC Code
```cpp
#include <bits/stdc++.h>  // 开始了
#define int long long  // 开 long long
using namespace std;
const int maxn = 510, mod = 1e9 + 7;
int n,m, ans,now=1, dp[2][maxn][maxn];  // 滚动数组
string ss[maxn];
signed main() {
	// IO
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> ss[i];
		ss[i]=' '+ss[i];
	}
	if (ss[1][1] == ss[n][m])  // 特判，如果起点不等于终点就输出 0
		dp[1][1][n] = 1;
	else {
		cout << 0;
		return 0;
	}
	for (int i = 2; i <= (n+m)/2; i++) {  // dp 转移
		now = now ^ 1;
		memset(dp[now],0,sizeof(dp[now]));  // 要清空
		for (int nx = 1; nx <= min(i,n); nx++) {
			int ny = i + 1 - nx;
			for (int tx = n; tx >=max(n - i,nx) ; tx--) {
				int ty = n + m - i - tx + 1;
				if (ss[nx][ny] == ss[tx][ty])
					dp[now][nx][tx] = dp[now^1][nx - 1][tx] +
					                    dp[now^1][nx][tx + 1] +
					                    dp[now^1][nx - 1][tx + 1] +
					                    dp[now^1][nx][tx];
					dp[now][nx][tx]%=mod;
			}
		}
	}
	// 统计
	if((n+m)&1) {
		for(int i=1; i<=n; i++) {
			ans += (dp[now][i][i]+dp[now][i][i + 1]);
			ans %= mod;
		}
	} else
		for (int i = 1; i <= n; i++) {
			ans += dp[now][i][i];
			ans %= mod;
		}
	// 输出
	cout << ans;
	return 0; // 拜拜

}
```

---

## 作者：yx666 (赞：1)

# CF570E Pig and Palindromes 题解

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF570E)

[CF 题目传送门](https://codeforces.com/contest/570/problem/E)

## Part 1：题意

### Part 1.1：题干

给定一个 $n$ 行 $m$ 列的填满字符的矩形，从 $(1,1)$ 出发，每次只能向下或向右移动一步。

求出以 $(1,1)$ 为开头，$(n,m)$ 为结尾，且为回文字符串的路径数量（结果对 $10^9+7$ 取模）。

### Part 1.2：限制

- $n,m\footnotesize\in[0,500]$。

- 时限 $4$ 秒。

- 空间 $250$ MB。

## Part 2：分析

$n,m\footnotesize\in[0,500]$，显然不是搜索（~~或者我打不出来~~），尝试分析 DP。

### Part 2.1：定义问题状态

和 [方格取数](https://www.luogu.com.cn/problem/P1004) 类似，均为坐标 DP。

把题意抽象成有两个小人，一个从 $(1,1)$ 出发到 $(i,j)$，一个从 $(n,m)$ 出发到 $(x,y)$ 处，要求两人走过的路径（字符串）相等。

所以，定义 $f_{i,j,x,y}$ 表示两个小人分别在 $(i,j)$ 处与 $(x,y)$ 处时路径相同的情况总数。

显然，$i,j,x,y\footnotesize\in[0,500]$ 空间会爆炸。结合 [方格取数](https://www.luogu.com.cn/problem/P1004) 的思想，开始优化空间复杂度。

重新定义 $f_{s,i,j}$ 表示两个小人走了 $s$ 步后，横坐标分别为 $i,j$ 时路径相同的情况总数。

现在空间复杂度 $O(n^3)$，$n\footnotesize\in[0,500]$，基本不会炸了（下面还会优化）。

### Part 2.2：状态转移方程

#### Part 2.2.1：无滚动优化

稍微推一下，就能得到 $f_{s,i,j}$ 时，小人分别在 $(i,s-i+1)$ 与 $(j,n+m-s-j+1)$ 处。

记 $p= s-i+1$，$q=n+m-s-j+1$，$mp_{i,j}$ 表示 $(i,j)$ 处的字符，则得到状态转移方程：

$$f_{s,i,j}=\begin{cases}0 &mp_{i,p}\ne mp_{j,q}\\f_{s-1,i-1,j}+f_{s-1,i,j+1}+f_{s-1,i-1,j+1}+f_{s-1,i,j}&mp_{i,p}=mp_{j,q}\end{cases}$$

#### Part 2.2.2：有滚动优化

发现 $f_{s,i,j}$ 只依赖于前一项，可滚动优化。

记 $now\gets s\bmod 2$，$bef\gets (s-1)\bmod 2$，这样可以保证 $now,bef\in[0,1]$ 且 $now\neq bef$。

其余不变，得到方程：

$$f_{now,i,j}=\begin{cases}0 &mp_{i,p}\ne mp_{j,q}\\f_{bef,i-1,j}+f_{bef,i,j+1}+f_{bef,i-1,j+1}+f_{bef,i,j}&mp_{i,p}=mp_{j,q}\end{cases}$$

### Part 2.3：初始化与边界状态

1. $f_{1,1,n}\gets1$，其余的初始化为 $0$。

2. 最多能向下走 $n$ 步，向右走 $m$ 步，再加之是双向走，所以 $s\footnotesize\in[1,\lfloor(n+m)\div2\rfloor]$。

### Part 2.4：计算顺序

对于 $f_{s,i,j}$：

1. 外层：$s\footnotesize\in[1,\lfloor(n+m)\div2\rfloor]$，$s$ 递增。特别的，$s=1$ 时，$f_{1,1,n}\gets1$。

2. 中层：$i\footnotesize\in[1,\min(n,s)]$，递增。

3. 内层：$j\footnotesize\in[\max(n-s,i),n]$，递增。

代码写成下面这样：

``` cpp
f[1][1][n]=1;
int final_s=(n+m)/2,now=1,bef=0;
for(int s=2;s<=final_s;++s){
	now^=1;bef=now^1;
	memset(f[now],0,sizeof f[now]);
	
	for(int i=1;i<=min(n,s);++i){
		int p=s-i+1;
		for(int j=n;j>=max(n-s,i);--j){
			int q=n+m-s-j+1;
			
			if(mp[i][p]==mp[j][q]){
				f[now][i][j]=f[bef][i-1][j]+f[bef][i][j+1]+f[bef][i-1][j+1]+f[bef][i][j];
				f[now][i][j]%=MOD;
			}
		}
	}	
}
```
### Part 2.5：答案

1. 如果 $n$，$m$ 奇偶性相同：可以理解为扫一遍对角线。

$$ans=\left(\sum^n_{i=1} f_{now,i,i}\right)\bmod 10^9+7$$

2. 如果 $n$，$m$ 奇偶性不同：可以理解为扫一遍对角线两侧（对角线上的点不在整数点上）。

$$ans=\left(\sum^n_{i=1} f_{now,i,i}+f_{now,i,i+1}\right)\bmod 10^9+7$$

代码如下：

``` cpp
int ans=0;	
if((n+m)&1)
	for(int i=1;i<=n;++i){
		ans=(ans+f[now][i][i]+f[now][i][i+1])%MOD;
	}
else
	for(int i=1;i<=n;++i){
		ans=(ans+f[now][i][i])%MOD;
	}

cout<<ans;
```

## Part 3：代码

> 十年 oi 一场空，不开 `long long` 见祖宗。

``` cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

#define N 502
const int MOD=1e9+7;

int n,m;
int f[2][N][N];
string mp[N];
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	cin>>n>>m;
	
	string ss;
	for(int i=1;i<=n;++i){
		cin>>ss;
		mp[i]=' '+ss;
	}
	
	// 特判，上面没有提到，但很好理解。
	// 如果开头不一致，肯定无法构成回文。
	if(mp[1][1]!=mp[n][m]){
		cout<<0;
		return 0;
	}
	
	f[1][1][n]=1;

	int final_s=(n+m)/2,now=1,bef=0;
	for(int s=2;s<=final_s;++s){
		now^=1;bef=now^1;
		
		memset(f[now],0,sizeof f[now]);
		
		for(int i=1;i<=min(n,s);++i){
			int p=s-i+1;
			for(int j=n;j>=max(n-s,i);--j){
				int q=n+m-s-j+1;
				
				if(mp[i][p]==mp[j][q]){
					f[now][i][j]=f[bef][i-1][j]+f[bef][i][j+1]+f[bef][i-1][j+1]+f[bef][i][j];
					f[now][i][j]%=MOD;
				}
			}
		}	
	}

	int ans=0;	
	if((n+m)&1)
		for(int i=1;i<=n;++i){
			ans=(ans+f[now][i][i]+f[now][i][i+1])%MOD;
		}
	else
		for(int i=1;i<=n;++i){
			ans=(ans+f[now][i][i])%MOD;
		}
	
	cout<<ans;
	return 0;
}
```

---

## 作者：include13_fAKe (赞：0)

过于降智了，这么简单的题不会做。

一开始想的是 **用哈希表维护 dp**，不用想都过不了。

然后想到了从回文中心往两边走，记录两边位置的方法。感觉不太好操作，并且容易 MLE。

因为只能往下和右两个方向走，所以设从起点和中点出发，两个走到的位置的纵坐标分别为 $i,j$ 即可。设 $dp_{dep,i,j}$ 表示目前的走的步数和两个纵坐标，横坐标可依据其推出。**只有合法状态能够相互转移。**

最后考虑如何统计答案，当 $dp$ 数组巡到两个曼哈顿距离为 $1$ 且顺序正确（指第一个格子的横纵坐标 **分别小于** 第二个格子的横纵坐标）的值时，累计答案。

还要考虑一个坑：如果左上角和右下角的字母不一样，**全局答案都应为 $0$**。（如果你错在第 $5$ 个点上）


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int mod=1e9+7;
int include13=0;
int n,m;
int dp[502][502];
int dp2[502][502];
char maze[502][502];
bool chk(int x,int y){
	return (1<=x)&&(x<=n)&&(1<=y)&&(y<=m);
}
bool check(int x,int y,int x2,int y2){
	if(abs(x2-x)+abs(y2-y)>1)	return false;
	if(x>x2||y>y2)	return false;
	return true;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>maze[i][j];
		}
	}
	if(maze[1][1]==maze[n][m])	dp[1][n]=1;	//记录每一轮的两个值的 i 坐标 ，j 坐标可以推导得到 
	for(int a=1;a<=n+m;a++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				//这里是第 a 层 第一个人在 i 第二个人在 j 
//				int x=i,y=a-x+2,x2=j,y2=;
				//先枚举上一次在的格子 
				int x=i,y=a-x+1;
				int x2=j,y2=m-(a-(n-x2))+1;
//				cout<<a<<' '<<i<<' '<<j<<' '<<x<<' '<<y<<' '<<x2<<' '<<y2<<endl;
				if((!chk(x,y))||(!chk(x2,y2)))	continue;
				//(7,5) 的起点 走了 3 步到 (5,4) 先推上一个格子  
				if(maze[x][y+1]==maze[x2][y2-1]){
					dp2[x][x2]+=dp[x][x2];
				}
				if(maze[x][y+1]==maze[x2-1][y2]){
					dp2[x][x2-1]+=dp[x][x2];
				}
				if(maze[x+1][y]==maze[x2][y2-1]){
					dp2[x+1][x2]+=dp[x][x2];
				}
				if(maze[x+1][y]==maze[x2-1][y2]){
					dp2[x+1][x2-1]+=dp[x][x2];
				}
			} 
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dp[i][j]=dp2[i][j]%mod;
				dp2[i][j]=0;
				int x=i,y=a-x+1+1;
				int x2=j,y2=m-(a-(n-x2))+1-1;
				if((!chk(x,y))||(!chk(x2,y2)))	continue;
//				cout<<a<<' '<<i<<' '<<j<<' '<<dp[i][j]<<" ("<<x<<','<<y<<")("<<x2<<','<<y2<<')'<<endl;
				if(check(x,y,x2,y2)){
					include13+=dp[i][j];
					include13%=mod;
//					cout<<a<<' '<<i<<' '<<j<<' '<<dp[i][j]<<" ("<<x<<','<<y<<")("<<x2<<','<<y2<<')'<<endl;
				}
			}
		} 
		
	} 
	cout<<include13<<endl;
//	cout<<endl;
	return 0;
} //傻傻的还在等待 以为你还要回来  
```

---

## 作者：yhy2024 (赞：0)

考虑 dp，设 $f_{x1,y1,x2,y2}$ 表示从左上角和右下角分别走到 $(x1,y1),(x2,y2)$ 两点的回文路径方案数。

枚举 $x1,y1,x2,y2$，显然有：

当 $c_{x1,y1}=c_{x2,y2}$ 时：

$f_{x1,y1,x2,y2}=f_{x1,y1,x2,y2}+f_{x1-1,y1,x2+1,y2}+f_{x1-1,y1,x2,y2+1}+f_{x1,y1-1,x2+1,y2}+f_{x1,y1-1,x2,y2+1}$

否则：

$f_{x1,y1,x2,y2}=0$

时空都是 $O(n^4)$，显然不行，考虑优化。

设走了 $k$ 步，注意到 $x1+y1-1=k,(n-x2)+(m-y2)-1=k$。

优化状态 $f_{k,x1,x2}$ 表示走了 $k$ 步，两点纵坐标分别为 $x1,x2$ 的回文路径方案数。

当 $c_{x1,y1}=c_{x2,y2}$ 时：

$f_{k,x1,x2}=f_{k,x1,x2}+f_{k-1,x1-1,x2}+f_{k-1,x1,x2+1}+f_{k,x1-1,x2+1}$

否则：

$f_{k,x1,x2}=0$

时空都是 $O(n^3)$，空间不行，使用滚动数组优化。

最后时间是 $O(n^3)$，空间是 $O(n^2)$。

注意特判，当 $m+n$ 是奇数时，最后的答案是:

$$\sum_{i=1}^n{f_{i,i}+f_{i,i+1}}$$


```
#include<bits/stdc++.h>
#define N 505
#define int long long 
using namespace std;
const int md=993244853;
int f[N][N],n,m,ans;
char s[N][N];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>s[i]+1;
	if(s[1][1]==s[n][m]) f[1][n]=1;
	for(int k=1;k<(n+m)/2;k++){
		for(int i=min(n,k+1);i>=1;i--){
			for(int j=max(n-k,i);j<=n;j++){
				if(s[i][k-i+2]==s[j][n+m-k-j]) f[i][j]=(f[i][j]+f[i-1][j]+f[i][j+1]+f[i-1][j+1])%md;
				else f[i][j]=0;
			}
		}
	}
	if((m+n)&1) for(int i=1;i<=n;i++) ans=(ans+f[i][i]+f[i][i+1])%md;
	else for(int i=1;i<=n;i++) ans=(ans+f[i][i])%md;
	cout<<ans;
	return 0;
}
```

---

## 作者：Eterna (赞：0)

[Link1](https://www.luogu.com.cn/problem/P3126)/[Link2](https://www.luogu.com.cn/problem/CF570E)

每一步都有两种不同的方向，一条路径长 $n+m-1$，所以搜索复杂度是 $O(2^{n+m})$，双向搜索可以做到 $O(2^n)$，但是不可过。

回文串有一个优良的性质，就是从左数第 $i$ 个数与从右数第 $i$ 个数相同，这是定义。同理，想象一下，有两个人分别站在点 $(1,1)$ 和点 $(n,m)$，第一个人每次可以向右或向下走，第二个人每次可以向左或向上，两人每次同时走，两人走了一共走了 $(n+m-1)$ 步自然就不能走了，而两人相遇时就形成一条从 $(1,1)$ 到 $(n,m)$ 的路径。

回文的限制就是要求两人每一步格子上的元素是相等的。不难设计出 dp 的状态 $f_{x,y,u,v}$ 为第一个人走到 $(x,y)$，第二个人走到 $(u,v)$ 的可行路径数。

但是时空都不太行，考虑一个更强大的状态。

因为第一个人每次只能向右或向下，第二个人每次只能向左或向上，如果知道他们走一个方向的次数和总的次数就可以知道他们的坐标，又因为他们是同时走的，所以总的次数是相等的。于是我们将状态简化为 $f_{x,u,t}$，$x,u$ 表示他们的纵坐标，$t$ 表示每个人走的步数。

容易得到转移：$f_{x,u,t}=f_{x,u,t-1}+f_{x+1,u,t-1}+f_{x,u-1,t-1}+f_{x+1,u-1,t-1}(a_{x,y}=a_{u,v})$。

但是空间 $O(n^3)$ 过不了。但是我们发现转移方程只和 $t$ 和 $t-1$ 的情况有关，于是可以滚动，空间就 $O(n^2)$ 了！！！

答案枚举他们相遇的位置求和即可。

---

## 作者：liujiaxi123456 (赞：0)

#### 题意：
一个 $n$ 行 $m$ 列带点权的网格图，起点在 $(1, 1)$，终点在 $(n, m)$，只能向下/向右走，求所有路径中把经过的点权连起来是回文串的路径条数。

$n,m\le500$
#### 思路：
**\*回文问题**，考虑**枚举中心**。

因为总路径长度一定，所以中间点到 (1, 1) 的距离也一定。

以点到起点的距离为顺序 DP，枚举一条路径的两个端点的一个坐标，显然可以求出另外两个，直接 DP 即可。
#### Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 505, MOD = 1e9+7;

namespace Josh_zmf {
	
	int N, M; string a[Maxn];
	ll f[2][Maxn][Maxn];

	inline int main() {
		cin>> N>> M;
		for(int i=1; i<=N; i++) {
			cin>> a[i], a[i] = ' ' + a[i];
		}
		int limit;
		if((N+M-1)&1)	limit = (N+M-1)/2+1;
		else 	limit = (N+M-1)/2;
		bool now = limit&1;
		for(int i=1; i<=N; i++) {
			int y1 = limit+1-i;
			if(y1<1 || M<y1)	continue;
			if((N+M-1)&1)	f[now][i][i] = 1;
			else {
				f[now][i][i] = (a[i][y1] == a[i][y1+1]);
				f[now][i][i+1] = (a[i][y1] == a[i+1][y1]);
			}
			// if(y1 < y2 && 1<=y2 && y2<=M)	f[now][i][i] = (a[i][y1] == a[i][y2]);
			// printf("f[%d][%d][%d][%d]:%lld\n", i, y1, i, y2, f[now][i][i]);
			// y2 = N+M+2-i-y1-i-1;
			// if(y1 < y2 && 1<=y2 && y2<=M)	f[now][i][i+1] = (a[i][y1] == a[i+1][y2]);
			// // if(1<=j+1 && j+1<=M)	f[i][(N+M+1)/2-i+1][i] = 1;
			// printf("f[%d][%d][%d][%d]:%lld\n", i, y1, i+1, y2, f[now][i][i+1]);
		}
		// puts("_________________________");
		now ^= 1;
		for(int len=limit-1; len>=1; len--, now^=1) {
			memset(f[now], 0, sizeof(f[now]));
			for(int x1=1; x1<=N; x1++) {
				int y1 = len+1-x1;
				if(y1<1 || M<y1)	continue;
				// for(int x2=1; x2<=N; x2++) {
				for(int x2=x1; x2<=N; x2++) {
					int y2 = N+M+2-x1-y1-x2;
					if(y2<1 || M<y2 || y2<y1)	continue;
					// if(y2<1 || M<y2)	continue;
					if(a[x1][y1] != a[x2][y2])	continue;
					// if(a[x1][y1+1] == a[x2][y2-1])	f[now][x1][x2] += f[now^1][x1][x2];
					// if(a[x1+1][y1] == a[x2][y2-1])	f[now][x1][x2] += f[now^1][x1+1][x2];
					// if(a[x1][y1+1] == a[x2-1][y2])	f[now][x1][x2] += f[now^1][x1][x2-1];
					// if(a[x1+1][y1] == a[x2-1][y2])	f[now][x1][x2] += f[now^1][x1+1][x2-1];
					// f[now][x1][x2] %= MOD;
					f[now][x1][x2] = (f[now^1][x1][x2] + f[now^1][x1+1][x2] + f[now^1][x1][x2-1] + f[now^1][x1+1][x2-1]) %MOD;
					// printf("f[%d][%d][%d][%d]:%lld\n", x1, y1, x2, y2, f[now][x1][x2]);
				}
			}
			// puts("_________________________");
		}
		cout<< f[1][1][N]<< '\n';
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```

---

## 作者：Antiluna (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF570E)

众所周知，回文串有一个性质：反转串与原串相等。所以我们在求一维序列中的回文串数量时，相当于是求原串与反转串的公共子序列数量。

其实这可以引申到二维地图中的回文串：从 $(1,1)$ 出发和从 $(n,m)$ 出发走该回文串，相遇后，两个串是相等的。

于是可以想到 $dp_{i,j,k,l}$ 表示第一个人走到 $(i,j)$ 第二个人走到 $(k,l)$ 时相等的方案数，此时不难转移，判断 $a_{i,j}=a_{k,l}$ 即可。

但是空间会爆，所以考虑进行优化，容易发现两人走的步数是相等的，而通过步数和 x 坐标可以求出 y 坐标，于是又可以得出 $dp(s,i,k)$ 表示走了 $s$ 步，第一个人走到 $(i,s-i+1)$ 第二个人走到 $(k,n+m-s-k+1)$ 时相等的方案数。

需要注意的是因为我们要求相遇时的方案数，所以在 $n+m$ 为奇数时要算两种情况。

还要注意取模。

代码：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,dp[3][510][510],a[510][510],b[510][510],mod=1000000007,ans;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		for(int j=1;j<=m;j++)a[i][j]=s[j-1]-65;
	}
	if(a[1][1]!=a[n][m])
	{
		cout<<0;
		return 0;
	}
	dp[1][1][n]=1;
	int i=1;
	for(int step=2;step<=(n+m)/2;step++)
	{
		i=i^1;
		memset(dp[i],0,sizeof(dp[i]));
		for(int x1=1;x1<=min(step,n);x1++)
		{
			for(int p=n;p>=max(n-step,i);p--)
			{
				int x2=step-x1+1,q=n+m-step-p+1;
				if(a[x1][x2]==a[p][q])dp[i][x1][p]=(dp[i^1][x1-1][p]+dp[i^1][x1-1][p+1]+dp[i^1][x1][p]+dp[i^1][x1][p+1])%mod; 
			}
		}
	}
	if((n+m)&1)for(int j=1;j<=n;j++)ans=(ans+dp[i][j][j]+dp[i][j][j+1])%mod; 
	else for(int j=1;j<=n;j++)ans=(ans+dp[i][j][j])%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：gdf_yhm (赞：0)

[CF570E](https://www.luogu.com.cn/problem/CF570E)

[Pig and Palindromes](https://codeforces.com/problemset/problem/570/E)

这题是 [P3126](https://www.luogu.com.cn/problem/P3126) 加强版。

### 思路

要走成回文的路径，即从左上角 $(1,1)$ 开始向右下和右下角 $(n,n)$ 开始向左上，走至相字母字母都相同。dp 计数。

设 $dp_{i,j,jj,k,kk}$ 表示走了 $i$ 步后，从左上走到 $(j,jj)$ ，从右下走至 $(k,kk)$ 的方案数。

转移如下：

$dp_{i,j,jj,k,kk}=dp_{i-1,j-1,jj,k+1,kk}+dp_{i-1,j-1,jj,k,kk+1}+dp_{i-1,j,jj-1,k+1,kk}+dp_{i-1,j,jj-1,k,kk+1}$

显然空间受不了。

因为只能向右下或左上走，所以当走了 $i$ 步后两边所在的位置是可以用 $i$ 和横坐标表示的。可以分别表示为 $(j,2+i-1-j)$ 和 $(k,n+m-i+1-k)$ 。

所以状态改为设 $dp_{i,j,k}$ 表示走了 $i$ 步后，从左上走到 $(j,2+i-1-j)$，从右下走至 $(k,n+m-i+1-k)$ 的方案数。

条件是 $c[j][jj]=c[k][kk]$，转移：$dp_{i,j,k}=dp_{i-1,j-1,k+1}+dp_{i-1,j-1,k}+dp_{i-1,j,k+1}+dp_{i-1,j,k}$

$500^3$ 的空间还会爆炸，考试到最后一会才改滚动数组，差点挂掉。

最后可能相遇或相邻，所以，当 $n+m$ 为偶时相遇，答案来自 $dp_{(n+m)/2,i,i}$，否则相邻，答案来自 $dp_{(n+m)/2,i,i}+dp_{(n+m)/2,i,i+1}$。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=510;

int n,m,t,dp[3][maxn][maxn],ans;
char c[maxn][maxn];
void sovle(){
	cin>>n>>m;t=n+m>>1;
	for(int i=1;i<=n;i++)cin>>c[i]+1;
	if(c[1][1]!=c[n][m]){
		cout<<"0\n";
		return ;
	}
	dp[1][1][n]=1;
	for(int i=2;i<=t;i++){
		for(int j=1;j<=min(i,n);j++){
			for(int k=n;k>=max(n-i,j);k--){
				int jj,kk;dp[i&1][j][k]=0;
				jj=2+i-1-j;kk=n+m-i+1-k;
//				cout<<i<<" "<<j<<" "<<jj<<" "<<k<<" "<<kk<<"\n";
				if(c[j][jj]==c[k][kk]){
					dp[i&1][j][k]+=dp[(i-1)&1][j-1][k+1],dp[i&1][j][k]%=mod;
					dp[i&1][j][k]+=dp[(i-1)&1][j-1][k],dp[i&1][j][k]%=mod;
					dp[i&1][j][k]+=dp[(i-1)&1][j][k+1],dp[i&1][j][k]%=mod;
					dp[i&1][j][k]+=dp[(i-1)&1][j][k],dp[i&1][j][k]%=mod;
				}
//				cout<<dp[i&1][j][k]<<"\n";
			}
		}
	}
	if((n+m)&1)for(int i=1;i<=n;i++)ans+=dp[t&1][i][i+1],ans%=mod,ans+=dp[t&1][i][i],ans%=mod;
	else for(int i=1;i<=n;i++)ans+=dp[t&1][i][i],ans%=mod;
	cout<<ans<<"\n";
}

int T;
signed main(){
//	cin.tie(0);cout.tie(0);
//	ios::sync_with_stdio(false);
	T=1;
	while(T--)sovle();
}
```



---

## 作者：f2021ljh (赞：0)

## CF570E and Luogu P3126 题解

### 题目传送门：
[CF570E](https://codeforces.com/contest/570/problem/E) | [CF570E on Luogu](https://www.luogu.com.cn/problem/CF570E) | 
[Luogu P3126](https://www.luogu.com.cn/problem/P3126)

### 题意（CF570E）：

给定一个由小写字母组成的 $n \times m$ 的矩阵 $A$，求从 $A_{1, 1}$ 到 $A_{n, m}$ 的所有路径中，回文串的个数。途中只能向下或向右走一格。

### 思路：

可以将问题理解为：

两个点分别从 $(1, 1)$ 和 $(n, m)$ 出发，同时分别向右 / 下和向左 / 上走，保证同时经过的字母相同，最终相遇（或相邻）。

考虑在矩阵上进行 dp。设状态 `dp[step][i][j][x][y]` 表示走了 $step$ 步，左上的那个点在 $(i, j)$，右下的那个点在 $(x, y)$，容易写出状态转移方程（~~太长了我就不写了~~）。

不过这样直接五维 `for` 循环的话必然会时空双爆炸。由于一步只能向右或向下走一格，$i$ 和 $j$ 与步数 $step$ 存在数量关系，即 $i + j - 1= step$。同理，只要按照所给的样例写几个数，就会发现 $x + y - 1 = n + m - step$。因此对于每一步， $j$ 和 $y$ 分别可以由 $i$ 和 $x$ 计算出来。这样时空复杂度就变成了三维。

状态转移方程：

`dp[step][i][x] = dp[step-1][i-1][x+1] + dp[step-1][i][x+1] + dp[step-1][i-1][x] + dp[step-1][i][x];`

初值：`dp[1][1][n] = 1;`

优化后的空间 $500 ^ 3 = 125,000,000$ 显然会 MLE。注意到状态转移的第一维只用到了 `step-1`，所以可以进行滚动数组优化。（其实剩下两维应该也能优化，代码就交给各位 dalao 啦）

细节：由于 $n + m$ 的奇偶性不同，最终两个点可能会相遇在同一点，也可能会相邻，即路径长度可能为奇数或偶数，这时要进行特判。

### 参考代码：

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#define f(x, y, z) for (int x = (y); (x) <= (z); (x)++)
#define g(x, y, z) for (int x = (y); (x) >= (z); (x)--)
using namespace std;
typedef long long ll;
int const N = 550;
int const MOD = 1e9 + 7;
int n, m, t, step;
ll ans, dp[2][N][N];
char c[N][N];

signed main() {
	
	// CF570E
	scanf("%d%d", &n, &m);
	
	// Luogu P3126
//	scanf("%d", &n);
//	m = n;
	
	f(i, 1, n) scanf("%s", c[i] + 1);
	if (c[1][1] != c[n][m]) { //特判一下
		puts("0");
		return 0;
	}
	step = 1;
	dp[1][1][n] = 1;
	t = (n + m) >> 1;
	f(k, 2, t) {
		step ^= 1;
		memset(dp[step], 0, sizeof dp[step]);
		f(i, 1, min(k, n)) {
			int j = k + 1 - i;
			g(x, n, max(n - k, i)) {
				int y = n + m - k + 1 - x;
				if (c[i][j] == c[x][y]) {
					dp[step][i][x] += dp[step ^ 1][i - 1][x + 1], dp[step][i][x] %= MOD;
					dp[step][i][x] += dp[step ^ 1][i][x + 1], dp[step][i][x] %= MOD;
					dp[step][i][x] += dp[step ^ 1][i - 1][x], dp[step][i][x] %= MOD;
					dp[step][i][x] += dp[step ^ 1][i][x], dp[step][i][x] %= MOD;
				}
			}
		}
	}
    // 对n + m的奇偶性进行特判
	if ((n + m) & 1) f(i, 1, n)
		ans = (ans + dp[step][i][i] + dp[step][i][i + 1]) % MOD;
	else f(i, 1, n) 
		ans = (ans + dp[step][i][i]) % MOD;
	printf("%d\n", ans);
	
	return 0;
}
```

---

