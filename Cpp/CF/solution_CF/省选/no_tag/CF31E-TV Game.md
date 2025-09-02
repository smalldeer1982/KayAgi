# TV Game

## 题目描述

There is a new TV game on BerTV. In this game two players get a number $ A $ consisting of $ 2n $ digits. Before each turn players determine who will make the next move. Each player should make exactly $ n $ moves. On it's turn $ i $ -th player takes the leftmost digit of $ A $ and appends it to his or her number $ S_{i} $ . After that this leftmost digit is erased from $ A $ . Initially the numbers of both players ( $ S_{1} $ and $ S_{2} $ ) are «empty». Leading zeroes in numbers $ A,S_{1},S_{2} $ are allowed. In the end of the game the first player gets $ S_{1} $ dollars, and the second gets $ S_{2} $ dollars.

One day Homer and Marge came to play the game. They managed to know the number $ A $ beforehand. They want to find such sequence of their moves that both of them makes exactly $ n $ moves and which maximizes their total prize. Help them.

## 样例 #1

### 输入

```
2
1234
```

### 输出

```
HHMM```

## 样例 #2

### 输入

```
2
9911
```

### 输出

```
HMHM```

# 题解

## 作者：Binary_Search_Tree (赞：4)

[题目传送门](https://www.luogu.org/problem/CF31E)

首先，本题暴力肯定过不掉，复杂度$O(C_{2n}^n)$

于是考虑DP。

设$F[i][j]$表示前$i$个数字选择$j$个组成$A$，其余组成$B$所能达到的最大的$A+B$

然而发现这样DP有后效性（即前面选择的$A$，$B$会对后面的选择造成影响）。

那么，如何设状态让它没有后效性呢？

对于一个数字（如$123$)，如果从前到后算是$(1×10+2)×10+3$，而如果从后到前算是$1×10^2+2×10^1+3×10^0$

看似没有变化，实际上用第二种方法是没有后效性的。

所以考虑从后到前DP，设$F[i][j]$表示从$i$到$n$中选择$j$个组成A，其余组成B所能达到的最大的$A+B$

令$jj=2n-i+1-j$即构成B的数字数量，则得到一下转移式：

当$j>0$时，$F[i][j]=max(F[i][j],F[i+1][j-1]+10^j×s[i])$

当$jj>0$时，$F[i][j]=max(F[i][j],F[i+1][j]+10^{jj}×s[i])$

输出方案时就由DP值逆推即可。

注意要用$unsigned\;long\;long$（最大值是$2×(10^{19}-1)$，超出了$long\;long$的范围）

$\text{code:}$

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#define M 105
using namespace std;
int n;
char s[M];
unsigned long long power10[M],F[M][M];//power10[i]是预处理出的10^i
int read(){
	char c=getchar();int ans=0;
	while (c<'0'||c>'9') c=getchar();
	while (c>='0'&&c<='9') ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans;
}
void DFS(int x,int y){//逆推求答案
	if (x>n+n) return;
	if (y&&F[x][y]==F[x+1][y-1]+power10[y]*(s[x]^48)) putchar('H'),DFS(x+1,y-1);
	else putchar('M'),DFS(x+1,y);
	return;
}
int main(){
	n=read();scanf("%s",s+1);power10[0]=1;
	for (register int i=1;i<=n+n;i++) power10[i]=power10[i-1]*10;//预处理
	for (register int i=n+n;i>=1;i--)
		for (register int j=0;j<=n+n-i+1;j++){
			int jj=n+n-i+1-j;
			if (j) F[i][j]=max(F[i][j],F[i+1][j-1]+power10[j]*(s[i]^48));
		        if (jj) F[i][j]=max(F[i][j],F[i+1][j]+power10[jj]*(s[i]^48));
		}
	DFS(1,n);
	return 0;
}
```

看完求赞QwQ

---

## 作者：piggy123 (赞：3)

唐题唐做法。

你考虑 $n\leq 18$，但是串长为 $2n$。我们暴力搜索过不去，但是这提示我们折半。所以我们折半，做完了。

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2400}$
---
### 解题思路：

考虑动态规划，设 $f_{i,j}$ 表示考虑到第 $i$ 个位置，其中 $A$ 数组已经接了 $j$ 个值。

关键是转移，如果直接乘十加上末尾值的话没有办法做，无法分离出两个值各是什么，但是发现所有的值加入的相对顺序是固定的，可以用 $\sum_{i=1}^n 10^i a_i$ 来表示数，根据当前加入值的位置计算即可。注意记录路径。

形式化地，有：

$f_{i,j}=\max(f_{i-1,j-1}+10^{n-j}\times num_i,f_{i,j}=f_{i-1,j}+10^{n-(i-j)}\times num_i)$

需要注意的是，题目中没有保证没有 $0$ 出现，而如果 $f$ 的初始值为 $0$ 可能会导致路径无法被记录的情况出现。

总复杂度为 $O(n^2)$。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int n,num[100],f[100][100],pow[20],fr[100][100],nx,ny,ans[100];
signed main(){
	scanf("%I64d",&n);
	pow[0]=1;
	for(int i=1;i<=n;i++)
	pow[i]=pow[i-1]*10;
	for(int i=1;i<=2*n;i++)
	scanf("%1d",&num[i]);
	for(int i=1;i<=2*n;i++)
	for(int j=0;j<=n;j++)
	f[i][j]=-2147483647;
	f[0][0]=0;
	for(int i=1;i<=2*n;i++){
		for(int j=0;j<=n;j++){
			if(j>i)break;
			if(j>0&&f[i-1][j-1]+pow[n-j]*num[i]>f[i][j]){
				f[i][j]=f[i-1][j-1]+pow[n-j]*num[i];
				fr[i][j]=-1;
			}
			if(i-j<=n&&i-j>0&&f[i-1][j]+pow[n-(i-j)]*num[i]>f[i][j]){
				f[i][j]=f[i-1][j]+pow[n-(i-j)]*num[i];
				fr[i][j]=1;
			}
		}
	}
//	printf("%I64d\n",f[2*n][n]);
	nx=2*n;ny=n;
	while(nx>0){
		if(fr[nx][ny]==1)ans[nx]=1;
		else ans[nx]=-1,ny--;
		nx--;
	}
	for(int i=1;i<=2*n;i++)
	printf("%c",ans[i]==1?'H':'M');
	return 0;
}
```


---

## 作者：小木虫 (赞：1)

### Problem
给定一个长 $2n$ 的数字序列，现在要将其分为两个长度为 $n$ 的子序列，要求这两个子序列所组成的数字加和最大。$(2n \leq 36)$
### Solution
一眼看上去就像一个 dp，设 dp 数组为：  
$dp _{i,j,k}$ 表示现在选到了第 $i$ 个数字，第一个子序列已经选到了第 $j$ 个数字，第二个子序列选到了第 $k$ 个数字。  
由于 $n \leq 18$，不用高精度，可以用 **unsigned long long**，但是~~作者懒~~，直接用了 int 128。  
状态转移方程：  
$dp _{i,j,k} = \max(dp _{i+1,j+1,k}+p_{n-j} ×s_i , dp _{i+1,j,k+1}+p_{n-k} ×s_i)$  
状态结束时候 $i,j,k$ 分别为 $n+1,n+1,n+1$ ，返回 1，对不合法状态返回 $inf$。  
code:  
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n;char s[50];
__int128 p[50];
__int128 dp[50][50][50];
bool vis[50][50][50];
__int128 dfs(int x,int s1,int s2){
//	printf("%d %d %d\n",x,s1,s2);
	if(x==2*n+1&&s1==n+1&&s2==n+1)return 0;
	if(x==2*n+1||s1>n+1||s2>n+1)return -4e22;
	if(vis[x][s1][s2])return dp[x][s1][s2];
	vis[x][s1][s2]=true;
	dp[x][s1][s2]=max(dfs(x+1,s1+1,s2)+p[n-s1]*(__int128)(s[x-1]-'0'),dfs(x+1,s1,s2+1)+p[n-s2]*(__int128)(s[x-1]-'0'));
	return dp[x][s1][s2];
}
int main(){
	cin>>n;p[0]=1;
	for(int i=1;i<=n;i++)p[i]=p[i-1]*10;
	cin>>s;
	dfs(1,1,1);
	int s1=1;int s2=1;
	for(int x=1;x<=2*n;x++){
		if(dp[x][s1][s2]==dfs(x+1,s1+1,s2)+p[n-s1]*(__int128)(s[x-1]-'0')){
			cout<<"H";s1++;
		}else{
			cout<<"M";s2++;
		}
	}
	return 0;
}
```


---

## 作者：luogu_gza (赞：0)

piggy 的题解也太简略了一点吧！

我们考虑折半，预处理出前半部分的所有方案和后半部分的所有方案。

然后我们考虑怎么合并方案，对于每一种方案我们记录一个四元组 $(len,a,b,state)$，表示 $A$ 选了几个，$A$ 是多少，$B$ 是多少，对于 $A$ 来说选定的状态是什么。

你需要保证前半部分和后半部分的 $len$ 加起来是 $n$，j假设前半部分的 $len$ 记作 $l$，前半部分的 $A,B$ 记作 $A_1,B_1$，后半部分的 $A,B$ 记作 $A_2,B_2$，那么最终的 $A+B$ 应当是 $(A_1 \times 10^{n-l}+A_2)+(B_1 \times 10^l+B_2)$，不难注意到可以把仅关于 $A_1$ 和 $B_1$ 的，仅关于 $A_2$ 和 $B_2$ 的拆出来，随意统计一下即可。

具体看[代码](https://codeforces.com/contest/31/submission/294183619)。

---

## 作者：Hoks (赞：0)

## 前言
虽然是远古场的题，但是貌似也不是很好做？

~~好吧还是因为我不会记忆化搜索导致的。~~

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
首先看到 $n$ 很小，考虑直接暴力。

仔细一看复杂度 $O(2^{2n})$，挂飞了。

考虑优化，使用 dp，那么我们就得先找到无后效性。

设计 $f_{i,j}$ 表示前 $i$ 位选出 $j$ 个数字的最大值。

那么转移的时候就是在已经选出来的数字串后再添一位。

这样好做吗？

显然不太好做，因为要先空出来一位 $0$ 再把这位添上，所以前面的值要乘 $10$。

正难则反嘛。

考虑倒着做，那么加进来的每一位的位数都已经确定了，直接转移即可。

最后输出方案再跑一遍转移过程即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
const int N=40,V=5e5,mod=998244353,INF=0x3f3f3f3f3f3f3f3f;
int n,f[N][N],op[N];char s[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void dfs(int x,int y)
{
    if(x>n) return;
    if(y&&f[x][y]==f[x+1][y-1]+op[y]*s[x]) put('H'),dfs(x+1,y-1);
    else put('M'),dfs(x+1,y);
}
signed main()
{
    read();rd(s,n);for(int i=op[0]=1;i<=n;i++) op[i]=op[i-1]*10,s[i]^=48;
    for(int i=n;i>=1;i--)
        for(int j=0;j<=n-i+1;j++)
        {
            int ed=n-i+1-j;
            if(j) f[i][j]=max(f[i][j],f[i+1][j-1]+op[j]*s[i]);
            if(ed) f[i][j]=max(f[i][j],f[i+1][j]+op[ed]*s[i]);
        }
    dfs(1,n/2);
    genshin:;flush();return 0;
}
```

---

## 作者：Error_Eric (赞：0)

### 题意

找两个长度相等的子序列使得两者十进制意义下的和最大。

### Sol

这里提供一种记忆化搜索解法。

其他题解提到的状态不好转移其实很好解决，只需要翻转序列从最低位开始取就可以了。

$F(i,j)$ 表示其中一个取了 $i$ 个数字，另一个取 $j$ 个数字的最大总和。

则可以得到当前取的这一位是原序列的第 $i+j$ 个，故 $F(i,j)=\max\{F(i-1,j)+10^i*a[i+j],F(i,j-1)+10^j*a[i+j]\}$。

### Code

~~不知道为什么输出方案会有人用递归~~。

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
typedef unsigned long long ull;
inline const void readln(int&I){
    I=0;char C=getchar();bool f=0;
    while(!isdigit(C))f|=(C=='-'),C=getchar();
    while( isdigit(C))(I*=10)+=(C-'0'),C=getchar();
	if(f)I=-I;
}
int n,p[20][20];
const ull inf=-1ull;
ull f[20][20],p10[20]={1};
char a[38];
queue<char>pans;
ull F(int u,int v){
    if(u==0&&v==0)return 1;
    //printf("%d %d\n",u,v);
    ull&ans=f[u][v],fu=0,fv=0;
    if(ans!=inf)return ans;
    if(u!=0)fu=F(u-1,v)+(a[u+v]-'0')*p10[u-1];
    if(v!=0)fv=F(u,v-1)+(a[u+v]-'0')*p10[v-1];
    if(fu>fv)p[u][v]=1;
    else     p[u][v]=2;
    return ans=max(fu,fv);
}
int main(){
    readln(n),scanf("%s",a+1),reverse(a+1,a+2*n+1);
    for(int i=1;i<=n;i++)p10[i]=p10[i-1]*10;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
            f[i][j]=inf;
    F(n,n);
    int x=n,y=n;
    while(x|y){
        if(p[x][y]&1)--x,pans.push('M');
        else         --y,pans.push('H');
    }
    while(pans.size())
        putchar(pans.front()),pans.pop();
}
```

---

## 作者：Ag2WO4 (赞：0)

水动归一道。根据已填入第一个数的数字和已填入第二个数的数字分别的个数设立状态，注意到两个数都只有 $n$ 位，状态转移方程就是从高位到低位模拟填数时的增量，比较从第一个和第二个数少一个数字往上填哪个大。这种做法没有后效性，复杂度为 $O(n^2)$。记得填数时同时记下值和，同时注意 Python 在本题数据范围下容易出锅。
#### [AC代码](https://codeforces.com/contest/31/submission/276385685)
```python
x=int(input());s=list(map(int,input()));from functools import*
@lru_cache#注意 CF 的Python 版本还没有 functools.cache 函数，小心报错
def f(i,j):
    if i+j==0:return[0,'']
    if i>j or i==0:return[-7<<61,'x'*j]#这个地方尤其注意要和 C++ 一样把负无穷开大，不知为何这里会出现负加正得正的现象
    a=f(i,j-1)[:];b=f(i-1,j-1)[:]#这个地方注意浅拷贝问题，因为 Python 的 lru_cache 存储本质上是字典，返回的列表是有真实指针的
    a[0]+=s[j-1]*10**(x-j+i);a[1]+='M';b[0]+=s[j-1]*10**(x-i);b[1]+='H';return max(a,b)
print(f(x,2*x)[1])
```

---

