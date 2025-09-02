# [ARC036C] 偶然ジェネレータ

## 题目描述

### 题目简介
有一个长度为$N$的数列，其仅由$0,1$构成。

现在，有一些地方需要填充，这些地方用问号来代替。

需要知道，有几种方案来填充问号，使得无论从数列中取出怎样的**连续的**子数列，其子数列中所包含的$0$的个数和$1$的个数的差都必须在$K$以下。

## 样例 #1

### 输入

```
9 4
?011?1110```

### 输出

```
2```

## 样例 #2

### 输入

```
9 3
?011?1110```

### 输出

```
0```

## 样例 #3

### 输入

```
9 1
???1?????```

### 输出

```
1```

## 样例 #4

### 输入

```
12 5
???0??1??11?```

### 输出

```
172```

# 题解

## 作者：igAC (赞：2)

# $\text{Describe}$

[洛谷 link](https://www.luogu.com.cn/problem/AT_arc036_c)

[ATlink](https://atcoder.jp/contests/arc036/tasks/arc036_c)

[更好的阅读体验](https://www.luogu.com.cn/blog/780168/solution-at-arc036-c)

简要题意：

给定一个只包含 ``1`` ``0`` ``?`` 的字符串，你要用 ``0`` 和 ``1`` 来替换 ``?``。

询问使所有子序列（连续）的 ``0`` ``1`` 字符数量差不超过 $K$ 的填法数量。

# $\text{Solution}$

很考验思维的一道妙妙题。

设 $f_{i,j,k}$ 表示当前枚举到第 $i$ 位，以这一位为终点的子序列 ``1`` 最多比 ``0`` 多 $j$ 个，以这一位为终点的子序列 ``0`` 最多比 ``1`` 多 $k$ 个的填法数量。

这样我们就保证了每一个状态都使合法的。

如下例：

``010101100111100``

对于最后一位来说：

``1`` 最多比 ``0`` 多 $2$ 个：``010101100|111100``。

``0`` 最多比 ``1`` 多 $2$ 个：``0101011001111|00``。

转移十分显然：

如果这一位是 ``1``：那么以这一位为终点的子序列 ``1`` 比 ``0`` 多的个数会大一，而 ``0`` 相反。

即 ```f[i+1][j+1][max(0,k-1)]+=f[i][j][k]```。

如果这一位是 ``0``：同理 ```f[i+1][max(0,j-1)][k+1]+=f[i][j][k]```。

如果这一位是 ``?`` 就包含了以上两种情况，不再多赘述。

这道题的难点就是 $\text{DP}$ 状态的设计比较困难，需要较强的思维能力。

具体实现可以参考代码，代码会给出记忆化搜索和普通 $\text{DP}$ 的实现。

# $\text{Code}$

**注意：输出一定要换行，不换行会 WA。**

$\text{Code1}$：记忆化搜索。

```cpp
#include<bits/stdc++.h>
#define N 305
#define Mod 1000000007
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,k;
int f[N][N][N];
string s;
int dfs(int now,int a,int b){
	if(a>k || b>k) return 0;
	if(~f[now][a][b]) return f[now][a][b]%Mod;
	if(now==n) return 1;
	f[now][a][b]=0;
	if(s[now]=='1') f[now][a][b]+=dfs(now+1,a+1,max(0,b-1))%Mod;
	if(s[now]=='0') f[now][a][b]+=dfs(now+1,max(a-1,0),b+1)%Mod;
	if(s[now]=='?'){
		f[now][a][b]+=dfs(now+1,a+1,max(0,b-1))%Mod;
		f[now][a][b]+=dfs(now+1,max(a-1,0),b+1)%Mod;
	}
	return f[now][a][b]%Mod;
}
int main(){
	n=read(),k=read();
	cin>>s;
	memset(f,-1,sizeof(f));
	printf("%d\n",dfs(0,0,0))%Mod;
	return 0;
}
```

$\text{Code2}$：普通 $\text{DP}$。

```cpp
#include<bits/stdc++.h>
#define N 305
#define Mod 1000000007
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,K,f[N][N][N],ans;
string s;
int main(){
	n=read(),K=read();
	cin>>s;f[0][0][0]=1;
	for(int i=0;i<n;++i){
		for(int j=0;j<=K;++j){
			for(int k=0;k<=K;++k){
				if(s[i]=='0') f[i+1][max(0,j-1)][k+1]=(f[i+1][max(0,j-1)][k+1]+f[i][j][k])%Mod;
				if(s[i]=='1') f[i+1][j+1][max(0,k-1)]=(f[i+1][j+1][max(0,k-1)]+f[i][j][k])%Mod;
				if(s[i]=='?'){
					f[i+1][max(0,j-1)][k+1]=(f[i+1][max(0,j-1)][k+1]+f[i][j][k])%Mod;
					f[i+1][j+1][max(0,k-1)]=(f[i+1][j+1][max(0,k-1)]+f[i][j][k])%Mod;
				}
			}
		}
	}
	for(int i=0;i<=K;++i){
		for(int j=0;j<=K;++j){
			ans=(ans+f[n][i][j])%Mod;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：qnqfff (赞：1)

### 思路

考虑设 $dp_{u,x,y}$ 表示考虑到前 $u$ 位，以当前为结尾的子序列 $0$ 最多比 $1$ 多 $x$ 个，$1$ 最多比 $0$ 多 $y$ 个，每次如果当前这位是 $0$ 就让 $x$ 加一，$y$ 减一，是 $1$ 则相反，直接记搜即可，没什么细节。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
const int mod=1e9+7;
using namespace std;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,k,dp[310][310][310];string s;
signed main(){
	n=read();k=read();cin>>s;s=" "+s;
	function<int(int,int,int)>dfs=[&](int u,int x,int y){
		if(x>k||y>k) return 0ll;if(u>n) return 1ll;if(~dp[u][x][y]) return dp[u][x][y];
		int res=0;if(s[u]^'1') (res+=dfs(u+1,x+1,max(0ll,y-1)))%=mod;if(s[u]^'0') (res+=dfs(u+1,max(0ll,x-1),y+1))%=mod;return dp[u][x][y]=res;
	};
	memset(dp,-1,sizeof(dp));cout<<dfs(1,0,0)<<'\n';
	return 0;
}
```

---

