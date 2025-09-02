# Letter Picking

## 题目描述

Alice and Bob are playing a game. Initially, they are given a non-empty string $ s $ , consisting of lowercase Latin letters. The length of the string is even. Each player also has a string of their own, initially empty.

Alice starts, then they alternate moves. In one move, a player takes either the first or the last letter of the string $ s $ , removes it from $ s $ and prepends (adds to the beginning) it to their own string.

The game ends when the string $ s $ becomes empty. The winner is the player with a lexicographically smaller string. If the players' strings are equal, then it's a draw.

A string $ a $ is lexicographically smaller than a string $ b $ if there exists such position $ i $ that $ a_j = b_j $ for all $ j < i $ and $ a_i < b_i $ .

What is the result of the game if both players play optimally (e. g. both players try to win; if they can't, then try to draw)?

## 说明/提示

One of the possible games Alice and Bob can play in the first testcase:

1. Alice picks the first letter in $ s $ : $ s= $ "orces", $ a= $ "f", $ b= $ "";
2. Bob picks the last letter in $ s $ : $ s= $ "orce", $ a= $ "f", $ b= $ "s";
3. Alice picks the last letter in $ s $ : $ s= $ "orc", $ a= $ "ef", $ b= $ "s";
4. Bob picks the first letter in $ s $ : $ s= $ "rc", $ a= $ "ef", $ b= $ "os";
5. Alice picks the last letter in $ s $ : $ s= $ "r", $ a= $ "cef", $ b= $ "os";
6. Bob picks the remaining letter in $ s $ : $ s= $ "", $ a= $ "cef", $ b= $ "ros".

Alice wins because "cef" &lt; "ros". Neither of the players follows any strategy in this particular example game, so it doesn't show that Alice wins if both play optimally.

## 样例 #1

### 输入

```
2
forces
abba```

### 输出

```
Alice
Draw```

# 题解

## 作者：MoyunAllgorithm (赞：20)

这是一篇不需要 dp、代码非常短的 $O(N)$ 做法。

**分析**

观察样例，发现 Bob 永远不会赢。因为只剩最后两个字母时，Alice 必然先取走最小的一个。因此要么 Alice 赢，要么平局。~~所以 Bob 为什么还要玩呢？~~

有这个结论，想到：**不如判断何时平局（看起来更简单），其他情况都是 Alice 赢。**

平局意味着：两人的字符串无论何时都是相同的。这是怎么做到的呢？不如手摸一些例子：

$\texttt{abba}$：Alice 拿走外面的一个，Bob 立刻拿走外面的另外一边的。

$\texttt{aabb}$：Alice 拿走最外面的一个，Bob 立刻拿走贴着的第二个。

$\texttt{abccddba}$：Alice 拿走某个 $\texttt{a/b}$ 时 Bob 立即拿走另一边对应的。变成 $\texttt{ccdd}$ 时同上一条。

$\texttt{aacddcbb}$：不行。Alice 拿走 $\texttt{a}$，则 Bob 必须拿走第二个 $\texttt{a}$。此时若 Alice 拿走 $\texttt{c}$，则 Bob 无 $\texttt{c}$ 可拿。

结论：字符串是回文、两两重复或回文套两两重复时，平局。

否则就是 Alice 赢啦。

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,N;
char s[2005];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",s+1);
        int N=strlen(s+1);
        int l=1,r=N;
        while(l<r&&s[l]==s[r]) l++,r--;
        if(l>=r)
        {
            puts("Draw");
            continue;
        }
        bool flag=1;
        for(int i=l;i+1<=r;i+=2)
        {
            if(s[i]!=s[i+1]) flag=0;
        }
        puts(flag?"Draw":"Alice");
    }
    return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：17)

## 思路

简单博弈区间 dp。

设 $f(l,r)$ 表示区间 $[l,r]$ 的结果。1 表示先手必胜。0 表示平局。2 表示后手必胜。

**按顺序**进行以下掘厕：

- 先手选取 $l$，后手不管是选取 $l+1$ 还是 $r$ 都字典序大于先手，
	此处有两种局面两种情况：
	- 后手选取 $l+1$：
		- 要么在前几位决出胜负，即 $f(l+2,r)$ 这个状态先手必胜；
		- 要么前几位一样并且这一位先手字典序小，即 $f(l+2,r)$ 这个状态平，且 $s[l]<s[l+1]$。
	- 后手选取 $r$：
		- 要么在前几位决出胜负，即 $f(l+1,r-1)$ 这个状态先手必胜；
		- 要么前几位一样并且这一位先手字典序小，即 $f(l+1,r-1)$ 这个状态平，且 $s[l]<s[r]$。
		
	两种局面先手都必胜，先手就一定会选取 $l$，于是必胜。
- 先手选取 $r$，后手不管是选取 $l$ 还是 $r-1$ 都烂（依然有两种局面两种情况，不再赘述），那么先手就一定会选取 $r$。
- 先手选取 $l$，后手不管是选取 $l+1$ 还是 $r$ 都不能取胜，
	此处有两种局面两种情况：
	- 后手选取 $l+1$：
		- 要么在前几位决出胜负，即 $f(l+2,r)$ 这个状态先手必胜；
		- 要么前几位一样并且这一位先手字典序小或相等，即 $f(l+2,r)$ 这个状态平，且 $s[l]<=s[l+1]$。
	- 后手选取 $l+1$：
		- 要么在前几位决出胜负，即 $f(l+1,r-1)$ 这个状态先手必胜；
		- 要么前几位一样并且这一位先手字典序小，即 $f(l+1,r-1)$ 这个状态平，且 $s[l]<=s[r]$。
		
	两种局面先手都必胜或平，先手就一定会选取 $l$，于是平。
- 先手选取 $r$，后手不管是选取 $l$ 还是 $r-1$ 都不能取胜，那么先手就一定会选取 $r$。
- 否则先手必败。

CF 场上哪有时间找性质（，就这么硬刚（

虽然先手的确不可能必败。

## code

```cpp
#include<stdio.h>
int t,n,ans[2222][2222];char s[2222];
struct __readt__{inline __readt__(){scanf("%d",&t);}}_readt___;
inline int dfs(const int&l,const int&r)
{
	if(l>r)return 0;
	if(~ans[l][r])return ans[l][r];
	int x=dfs(l+2,r),y=dfs(l+1,r-1),z=dfs(l,r-2);
	if(((x==1)||(!x&&s[l]<s[l+1]))&&((y==1)||(!y&&s[l]<s[r])))
		return ans[l][r]=1;
	if(((z==1)||(!z&&s[r]<s[r-1]))&&((y==1)||(!y&&s[r]<s[l])))
		return ans[l][r]=1;
	if(((x==1)||(!x&&s[l]<=s[l+1]))&&((y==1)||(!y&&s[l]<=s[r])))
		return ans[l][r]=0;
	if(((z==1)||(!z&&s[r]<=s[r-1]))&&((y==1)||(!y&&s[r]<=s[l])))
		return ans[l][r]=0;
	return ans[l][r]=2;
}
main()
{
	scanf("%s",s);for(n=0;s[n];++n);
	for(int i=0;i<n;++i)for(int j=i;j<n;ans[i][j++]=-1);
	int x=dfs(0,n-1);
	if(!x)printf("Draw\n");
	if(x==1)printf("Alice\n");
	if(x==2)printf("Bob\n");
	if(--t)main();
}
```

---

## 作者：DaiRuiChen007 (赞：11)

# CF1728D 题解



## 思路分析

简单博弈论，令 $dp_{l,r}$ 表示对于子串 $s[l\cdots r]$ 时哪一方会获胜，$1$ 表示 Alice，$0$ 表示平局，$-1$ 表示 Bob。

显然，我们只需要对所有 $2|r-l+1$ 的 $s[l\cdots r]$ 计算，考虑这一轮 Alice 和 Bob 的操作。

边界条件：$dp_{i,i+1}=[s_i=s_{i+1}]$。

考虑枚举两人分别选了哪一个字符即可，注意 Bob 会让结果尽量小，而 Alice 会让结果尽量大，因此只需要用 `min`、`max` 操作计算即可。

时间复杂度 $\Theta(n^2)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2001;
char s[MAXN];
int dp[MAXN][MAXN];
inline int comb(char x,char y) {
	if(x>y) return 1;
	if(x<y) return -1;
	return 0;
}
inline void solve() {
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1;i<n;++i) dp[i][i+1]=(s[i]==s[i+1])?0:1;
	for(int len=4;len<=n;len+=2) {
		for(int l=1,r=len;r<=n;++l,++r) {
			dp[l][r]=-1;
			int f1=dp[l+2][r]==0?comb(s[l],s[l+1]):dp[l+2][r];
			int f2=dp[l+1][r-1]==0?comb(s[l],s[r]):dp[l+1][r-1];
			int f3=dp[l][r-2]==0?comb(s[r],s[r-1]):dp[l][r-2];
			int f4=dp[l+1][r-1]==0?comb(s[r],s[l]):dp[l+1][r-1];
			dp[l][r]=max(min(f1,f2),min(f3,f4));
		}
	}
	if(dp[1][n]==1) puts("Alice");
	if(dp[1][n]==0) puts("Draw");
	if(dp[1][n]==-1) puts("Bob");
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
} 
```



---

## 作者：OIer_ACMer (赞：8)

~~再次打开题解编辑面板怎么有些生疏了？~~

------------
注：本题思路较为简单，所以作者不会过多赘述原理以及证明，望周知！

------------
## 大致思路：
因为最后比较的是字典序，所以最后剩下的两个字符非常重要。因为是 Alice 先手，所以对于剩下的两个，Alice 先挑，肯定挑较小的那个，除非两个相同。所以最终的结果只有两种，要么 Alice 赢，要么平局。

好，然后呢？？

官方题解给的做法是这样的：

对于一个大区间是否是平局，可以由小区间来判断。
即，对于一个大区间来说，如果不管 Alice 拿左右端点的哪个，Bob 拿过剩下区间左右端一个和其相同的字符之后，剩下的区间是平局，那么大区间就是平局。

形式化讲，对于大区间 $[l, r]$ 来说，有四种情况：

Alice 拿左端 $a_l$ 时，Bob 能拿剩下区间的左端 $a_{l + 1}$ 并且剩下区间 $[l+2, r]$ 为平局；

Alice 拿左端 $a_l$ 时，Bob 能拿下剩下区间的右端 $a_r$ 并且剩下区间 $[l+1, r-1]$ 为平局；

Alice 拿右端 $a_r$ 时，Bob 能拿剩下区间的右端 $a_{r - 1}$ 并且剩下区间 $[l, r-2]$ 为平局；

Alice 拿右端 $a_r$ 时，Bob 能拿下剩下区间的左端 $a_l$ 并且剩下区间 $[l+1, r-1]$ 为平局；

当 $1$，$2$ 情况出现至少一种，$3$，$4$ 情况出现至少一种时，就说明 Bob 能对 Alice 产生制约，这段大区间就能是平局。

而如果用区间 dp 先将小区间维护出来的话，大区间就能用小区间来更新，从而确定整个字符串是不是平局。

定义 $f_{i,j}$ 表示，区间 $[l, r]$ 最后的结果是否是平局。

初始化的时候，看长度为 $2$ 的区间，如果是两个相同的字符，那么就是平局，赋值为 $1$；否则为 $0$。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int N = 2010, mod = 1e9 + 7;
int T, n, m;
char a[N];
int f[N][N];
bool check(int l, int r)
{
    int pdL = 0, pdR = 0;
    if (a[l] == a[l + 1] && f[l + 2][r] || a[l] == a[r] && f[l + 1][r - 1])
    {
        pdL = 1;
    }
    if (a[r] == a[r - 1] && f[l][r - 2] || a[l] == a[r] && f[l + 1][r - 1])
    {
        pdR = 1;
    }
    if (pdL && pdR)
    {
        return 1;
    }
    return 0;
}
signed main()
{
    T = read();
    while (T--)
    {
        scanf("%s", a + 1);
        n = strlen(a + 1);
        memset(f, 0, sizeof(f));
        for (int i = 1; i < n; i++)
        {
            if (a[i] == a[i + 1])
            {
                f[i][i + 1] = 1;
            }
        }
        for (int len = 4; len <= n; len += 2)
        {
            for (int i = 1; i <= n; i++)
            {
                int j = i + len - 1;
                if (check(i, j))
                {
                    f[i][j] = 1;
                }
            }
        }
        if (f[1][n])
        {
            cout << "Draw\n";
        }
        else
        {
            cout << "Alice\n";
        }
    }
    return 0;
}
```

---

## 作者：pineappler (赞：8)

[更好的阅读体验](https://www.luogu.com.cn/blog/pineappler/cf1728d-letter-picking)
## 题面
Alice 和 Bob 在玩游戏。

给出一个长度为偶数的，非空的且仅含小写字母的字符串 $s$。每个玩家还拥有一个初始为空的字符串。

Alice 先手，两名玩家交替行动。在一次行动中，玩家可以取 $s$ 首或尾字符，将其从 $s$ 中移除后加入到自己的字符串的**最前面**。

当 $s$ 为空时游戏结束，拥有字典序更小的字符串的玩家获胜。若两名玩家的字符串相等则平局。

若 Alice 和 Bob 都足够聪明，判断谁会取胜，或者游戏为平局。

数据组数 $t\leq 10^3$，$\sum|s|\leq 2\times 10^3$。保证所有输入的 $|s|$ 长度都为偶数。
## 思路
**区间 dp+ 简单博弈论**  

感性理解：由于 Alice 先选，当只剩最后两个时 Alice 肯定会选大的，如果最后两个一样大，Alice 在前面的操作中也会选大的。换而言之，Alice 一直有主动权，Bob 的任务是“制约”住Ailce，尽可能达成平局（Bob 永远赢不了）。

为了避免过于复杂的状态，把 Ailce 和 Bob 的各一步操作看成一个整体，一起转移。

### 设状态
设 $dp(i,j)$ 为：在区间 $[i,j]$ 中（不考虑之前取的数），Bob 能否打成平局，若可以则为 $1$，反之为 $0$。
### 初始值与边界
从区间长度为 $2$ 开始枚举，目标为区间 $[1,n]$。对于任意 $1\le i < n$，如果  $s_i = s_{i+1}$，那么 $dp(i,j) \gets 1$，否则 $dp(i,j) \gets 0$（很明显，Alice 取一个，Bob 就可以取另一个）。
### 状态转移
一个状态（设这个状态是 $dp(l,r)$）能打成平局必须满足两个条件：
- **无论 Alice 取区间头还是区间尾，Bob 都能从剩下区间头或区间尾中取出一个一样的字符，保证在这一位上打成平局。**

- **剩下的部分能打成平局。**

对于这个区间，Alice 和 Bob 分别各有两种选择（共四种）：
1. Alice 取区间头 $s_l$，Bob 取剩下的区间头 $s_{l+1}$:  
想打成平局必须满足：  
$s_{l}=s_{l+1}$ 且 $dp(l+2,r)=1$
  
2. Alice 取区间头 $s_l$，Bob 取区间尾 $s_{r}$：  
想打成平局必须满足：  
$s_{l}=s_{r} $ 且 $dp(l+1,r-1)=1$
 
3. Alice 取区间尾 $s_r$，Bob 取区间头 $s_{l}$：  
想打成平局必须满足：  
$s_{r}=s_{l} $ 且 $dp(l+1,r-1)=1$ （没错，跟上一条是一样的）
4. Alice 取区间尾 $s_r$，Bob 取剩下的区间尾 $s_{r-1}$：  
想打成平局必须满足：  
$s_{r}=s_{r-1} $ 且 $dp(l,r-2)=1$

因为 Alice 会做出最优选择，所以**对于 Ailce 的每种选择，Bob 都要有应对之法** ，即：当且仅当**在第一条和第二条中至少有一个成立，且在第三条和第四条中至少有一个成立**之时，Bob 才能在区间 $[l,r]$ 打成平局，即 $dp(l,r)\gets 1$，否则 $dp(l,r) \gets 0$。
### 没什么卵用的常数优化
很容易发现只有长度为 $2$ 的整倍数的区间才会被用到，所以只枚举长度为 $2$ 的整倍数的区间即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2005;
char s[N];
bool dp[N][N];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		memset(s,0,sizeof s);
		scanf("%s",s+1);
		int n=strlen(s+1);
		for(int i=1;i<n;i++) 
			if(s[i] == s[i+1]) dp[i][i+1]=true;
			else dp[i][i+1]=false;//注意：由于每组数据都没有初始化dp数组为false，这里避免上一组数据的答案影响到下一组数据 
		//边界状态 
		for(int len=4;len<=n;len+=2){
			for(int l=1;l<=n-len+1;l++){
				int r=l+len-1;
				if((s[r]==s[l] && dp[l+1][r-1] || s[r]==s[r-1] && dp[l][r-2]) && 
				   (s[l]==s[r] && dp[l+1][r-1] || s[l]==s[l+1] && dp[l+2][r])) dp[l][r]=true;
				else dp[l][r]=false;//这里同理 
				//状态转移 前一行是Alice选s[r]的情况，后一行是 Alice选s[l]的情况 
			}
		}
		if(dp[1][n]) printf("Draw\n");
		else printf("Alice\n");
	}
	return 0;
}
```

---

## 作者：MYJ_aiie (赞：6)

### [CF1728D Letter Picking](https://www.luogu.com.cn/problem/CF1728D)
## 思路：
区间 DP+博弈。  

因为每次取完都放到第一个，所以最后一定是 Alice 赢或者平局。为什么呢？当最后只剩两个时，若两个不同，则 Alice 可以取较小的那个取胜，若相同，Alice 也会在前面的操作中选小的。而且 $n$ 是偶数，所以不存在 Alice 取的字符串比 Bob 长的情况。

阅读题目和数据范围，我们猜测是区间 DP。设 $f_{l,r}$ 表示剩余区间 $[l,r]$ 时，是平局还是 Alice 取胜。因为字典序按位比较，我们一次让双方都操作。  
怎样判断这一次是平局？

- Alice 取 $s_l$：  
  那么 Bob 只能选 $s_{l+1}$ 或 $s_r$ 使得答案尽可能为平局。   
  若 Bob 取 $s_{l+1}$，那么只有 $s_{l+1}$ 和 $s_l$ 相同，并且  $f_{l+2,r}$ 为平局时答案为平局。  
  若 Bob 取 $s_{r}$，那么只有 $s_{r}$ 和 $s_l$ 相同，并且  $f_{l+1,r-1}$ 为平局时答案为平局。  
  任一满足一种即可在 Alice 取 $s_l$ 时平局。
- Alice 取 $s_r$：  
   那么 Bob 只能选 $s_{r-1}$ 或 $s_l$ 使得答案尽可能为平局。  
   若 Bob 取 $s_{r-1}$，那么只有 $s_{r-1}$ 和 $s_r$ 相同，并且 $f_{l,r-2}$ 为平局时答案为平局。  
   若 Bob 取 $s_{r}$，那么只有 $s_{r}$ 和 $s_l$ 相同，并且 $f_{l+1,r-1}$ 为平局时答案为平局。  
   任一满足一种即可在 Alice 取 $s_r$ 平局。
   
对于 Alice 的两种取法，Bob 都要有应对方法。所以这两种要都满足才能取得平局。  
一点小优化：因为每次双方都操作，所以 $f_{l,r}$ 只有在区间长度为偶数时有意义，那我们可以在枚举区间长度时只枚举偶数。
## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2002;
int T;
int f[N][N];//1表示Alice获胜，0表示平局。 
string s,t;
bool check(int l,int r){
	int p1,p2,p3,p4;
	p1=p2=p3=p4=0;
	if(s[l]==s[l+1]&&f[l+2][r]==0) p1=1;
	if(s[l]==s[r]&&f[l+1][r-1]==0) p2=1;
	if(s[r]==s[r-1]&&f[l][r-2]==0) p3=1;
	if(p1+p2>=1&&p2+p3>=1) return 1;//两种情况各至少满足一个
	return 0;
}
int main(){
	scanf("%d",&T);
	while(T--){
		cin>>s;
		int sl=s.size();	
		s='#'+s;
		for(int i=1;i<=sl;i++){
			for(int j=1;j<=sl;j++) f[i][j]=0;//初始化。 
		}
		for(int i=1;i<sl;i++) {
			if(s[i]==s[i+1]) f[i][i+1]=0;
			else f[i][i+1]=1; 
		}
		for(int len=4;len<=sl;len+=2){
			for(int l=1;l+len-1<=sl;l++){
				int r=l+len-1;
				if(check(l,r)) f[l][r]=0;
				else f[l][r]=1;
			}
		}
		if(f[1][sl]==1) printf("Alice\n");
		else printf("Draw\n");
		
	}
	return 0;
}
```

---

## 作者：Mariposa (赞：3)

题意：

Alice 和 Bob 玩游戏。有一个字符串，每人每次可以从边缘拿，并插入自己串的开头。每个人希望自己的字典序比对方小。

题解：

考虑令 Alice 赢为 $0$，平局为 $1$，Bob 赢为 $2$，于是转化为 Alice 希望尽量小，Bob 希望尽量大。

那么我们区间 $dp$，设 $dp_{i,j}$ 表示 Alice 能到的最小值，我们枚举 Alice 选哪边，再看 Bob 选哪边。Bob 肯定是选去掉后 $dp$ 值尽量大的一边，而 Alice 则取 Bob 取完后 $dp$ 值较小的一边。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const int mod=1e9+7;
#define inf 1e9
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
string s;
const int N=2e3+5;
int T,n,m,dp[N][N];
inline int make(int op,int p1,int p2){
	if(op!=1)return op;
	return (s[p1]<s[p2]?0:(s[p1]==s[p2]?1:2));
}
int main(){
	T=read();
	while(T--){
		cin>>s;n=s.size();s=" "+s;
		for(int i=1;i<=n;i++)
			for(int j=i;j<=n;j++)dp[i][j]=3;
		for(int len=2;len<=n;len+=2)
			for(int l=1;l+len-1<=n;l++){
				int r=l+len-1;
				if(len==2){dp[l][r]=(s[l]==s[r]);continue;}
				int res=2;
				res=min(res,max(make(dp[l+1][r-1],l,r),make(dp[l+2][r],l,l+1)));
				res=min(res,max(make(dp[l+1][r-1],r,l),make(dp[l][r-2],r,r-1)));
				dp[l][r]=res;
			}
		if(dp[1][n]==0)puts("Alice");
		else if(dp[1][n]==1)puts("Draw");
		else puts("Bob");
	}
	return 0;
}
```

---

## 作者：panyanppyy (赞：3)

这是一场历练。

## Problem

给你一个序列每次 $A,B$ 可以从序列头或尾选择一个数放到自己的序列**头部**。

$A,B$ 绝顶聪明，最后字典序小的人赢，求最后是 $A$ 赢，$B$ 赢还是平局。

## Solution

然后你会发现一个没什么用的结论，就是后手不可能赢。

但是正解不基于这个结论。

$n\le2000$ 考虑 dp。

设 $f_{l,r}$ 表示 区间 $[l,r]$ 的胜负情况，$0$ 表示 $A 赢$，$1$ 表示平局，$2$ 表示 $B 赢$（虽然不可能但还是假设它有）。

那显然小区间是最后取的，决定答案。

然后 $f_{l,r}$ 可以从 $f_{l+1,r-1},f_{l+2,r},f_{l,r-2}\ A,B$ 各取一次得来。

分开考虑 $A$ 取左边还是右边的情况：

1. 左，考虑 $A$ 取 $a_l$ 能不能胜出：
	
	如果原区间 $A$ 赢了，那就赢了；否则如果平局，就考虑两个字符 $a_r,a_{l+1}$ 都大于 $a_l$ 那么就赢了，如果相等就平局，否则就输了。
    
2. 右，同理，取 $a_r$。

所以分讨一下就可以了，但是确实难调。

尝试证明上面的结论：后手必不胜。

只要证明可以不能转移到赢的状态，那么就转移到平局状态。

考虑不可能的情况：
```
大小...小大
（相同的字代表一样的字母。）
```
当 $A$ 拿了大的时候显然 $B$ 可以拿小的，但是可以一直向右取一旦 $B$ 取了大的 $A$ 就取小的，当最后取完的时候小的一定在 $A$ 那所以一定赢。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) (x).begin(),(x).end()
using namespace std;
const int N=2007;
int T,n,f[N][N];
string a;
inline void work(){
	cin>>a,n=a.size(),a=' '+a;
	for(int i=1;i<n;i++)f[i][i+1]=(a[i]==a[i+1]);
	for(int len=4,x,y,z;len<=n;len+=2)
		for(int l=1,r=len;r<=n;l++,r++){
			x=f[l+2][r],y=f[l+1][r-1],z=f[l][r-2];
			if((((x==1&&a[l]<a[l+1])||x==0)&&
			    ((y==1&&a[l]<a[r]  )||y==0))||
			   (((z==1&&a[r]<a[r-1])||z==0)&&
			    ((y==1&&a[r]<a[l]  )||y==0)))f[l][r]=0;
			else
			if((((x==1&&a[l]<=a[l+1])||x==0)&&
			    ((y==1&&a[l]<=a[r]  )||y==0))||
			   (((z==1&&a[r]<=a[r-1])||z==0)&&
			    ((y==1&&a[r]<=a[l]  )||y==0)))f[l][r]=1;
			else f[l][r]=2,assert(0);
		}
	if(!f[1][n])cout<<"Alice\n";
	else if(f[1][n]&1)cout<<"Draw\n";
	else cout<<"Bob\n";
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)work();
	return 0;
}
```

---

## 作者：yanmingqian (赞：2)

非 dp 题解。

贪心考虑，由于 Alice 先取，当最后只剩两个且不同时，必然会取走更小的那个。若两个相同则为倒数第三第四个，同理。所以 Bob 根本赢不了，只可能平局。如何平局呢？只能是每次 Bob 取走的与 Alice 刚刚取走的那个相同。也就是说，每次 Alice 取走一个，字符串的最前面或者最后面一定要有一个与之相同的字符。因此字符串要么是回文，要么是连续重复的，或者是回文中间套了一部分连续重复的。

那么很好实现了。每次读入字符串后，判断回文删掉首尾两个，连续重复删掉最前面两个，能删的全部删完后若字符串为空，则是平局，否则 Alice 赢。

代码：

```cpp
#include<iostream>
using namespace std;
int main(){
    int T;
    cin>>T;
    while(T--){
        string s;
        cin>>s;
        int len;
        while(s.size()&&s[0]==s[len=s.size()-1]){
            s.erase(len,1);s.erase(0,1);
        }
        while(s.size()&&s[0]==s[1]){
            s.erase(0,2);
        }
        if(s.size()){
            cout<<"Alice\n";
        }
        else{
            cout<<"Draw\n";
        }
    }
    return 0;
}
```

---

## 作者：slzx2022YuYihan (赞：1)

[CF1728D	Letter Picking](https://www.luogu.com.cn/problem/CF1728D)

# Solution

看到数据范围，首先你会纳闷几秒，过了不到十五秒的思考，你就顿悟：这不就是区间 dp 嘛！

令 $dp_{l,r}$ 表示区间 $l$ 到 $r$ 的获胜情况，$\mathbb 0$ 表示男朋友获胜，$\mathbb 1$ 表示平局，$\mathbb 2$ 表示女朋友获胜。

*	如果女朋友取左边，男朋友取右边，如果 $dp_{l+1,r-1}=1$，那么就由 $s_l$ 与 $s_r$ 的大小决定，否则就由这个值决定。
*	如果女朋友取左边，男朋友也取左边，如果 $dp_{l+2,r}=1$，那么就由 $s_l$ 与 $s_{l+1}$ 的大小决定，否则就由这个值决定。
*	如果女朋友取右边，男朋友取左边，如果 $dp_{l+1,r-1}=1$，那么就由 $s_r$ 与 $s_l$ 的大小决定，否则就由这个值决定。
*	如果女朋友取右边，男朋友也取右边，如果 $dp_{l,r-2}=1$，那么就由 $s_r$ 与 $s_{r-1}$ 的大小决定，否则就由这个值决定。


当然，男朋友肯定希望这个值越小越好，女朋友肯定希望这个值越大越好，最小最大乱搞即可。

~~真是相爱相杀。~~

上一份~~极度舒适~~的代码。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>inline void read(T& x){
    x = 0; T w = 1; char ch = getchar();
    while (!isdigit(ch)){if (ch == '-')	w = -1; ch = getchar();}
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    x *= w;
}
template<typename T>inline void write(T x){
    if (x < 0)	putchar('-'), x = ~(x - 1);
    if (x > 9)	write(x / 10);
    putchar(x % 10 ^ 48);
}

const int N = 2e3 + 5;

int T;

int n;
char s[N];

int dp[N][N];

int main(){
    //ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    read(T);
    while (T--){
        scanf("%s", s + 1), n = strlen(s + 1);
        for (register int len = 2; len <= n; len += 2)
            for (register int l = 1, r = l + len - 1; r <= n; ++l, ++r){
                dp[l][r] = 0;
                if (len == 2){
                    dp[l][r] = (s[l] == s[r]) ? 1 : 2;
                }
                else{
                    int res1, res2, res3, res4;
                    res1 = dp[l + 1][r - 1] == 1 ? (s[l] < s[r] ? 2 : (s[l] == s[r] ? 1 : 0)) : dp[l + 1][r - 1];
                    res2 = dp[l + 2][r] == 1 ? (s[l] < s[l + 1] ? 2 : (s[l] == s[l + 1]) ? 1 : 0) : dp[l + 2][r];
                    res3 = dp[l + 1][r - 1] == 1 ? (s[r] < s[l] ? 2 : (s[l] == s[r] ? 1 : 0)) : dp[l + 1][r - 1];
                    res4 = dp[l][r - 2] == 1 ? (s[r] < s[r - 1] ? 2 : (s[r] == s[r - 1] ? 1 : 0)) : dp[l][r - 2];
                    dp[l][r] = max(min(res1, res2), min(res3, res4));
                }
            }
        puts(dp[1][n] == 0 ? "Bob" : (dp[1][n] == 1) ? "Draw" : "Alice"); 
    }

    return 0;
}
```

---

## 作者：Cheerimy (赞：1)

## 题目简化

Alice 与 Bob 可以轮流取字符串的首尾字符并放到自己字符串的最前面（一次取一个）；

他们希望自己的字符串尽量大；

## 题目思路

区间 DP + 博弈论；

假设 Alice 赢为 -10，平局为 0，Bob 赢为 10；

那么，问题就转换成了 Alice 希望结果尽量小，Bob 希望结果尽量大；

对于这里的推理就基于博弈论。

显而易见，此题是区间类问题，所以使用区间 DP；

设 $dp_{i,j}$ 表示 Alice 能得到的最小值，Bob 能得到的最大值；

基于以上理论，本题只用套用模板即可；

### 博弈论

博弈论，又称为对策论（Game Theory）、赛局理论等，既是现代数学的一个新分支，也是运筹学的一个重要学科。

博弈论主要研究公式化了的激励结构间的相互作用，是研究具有斗争或竞争性质现象的数学理论和方法。博弈论考虑游戏中的个体的预测行为和实际行为，并研究它们的优化策略。生物学家使用博弈理论来理解和预测进化论的某些结果。

博弈论已经成为经济学的标准分析工具之一。在金融学、证券学、生物学、经济学、国际关系、计算机科学、政治学、军事战略和其他很多学科都有广泛的应用。

## 题目代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string x;
long long dp[2500][2500];
long long cmp(long long xum,long long i,long long j)
{
	if(xum==0)
	{
		if(x[i]<x[j])
		{
			return -10;//Alice
		}else if(x[i]==x[j])
		{
			return 0;//Draw
		}else
		{
			return 10;//Bob
		}
	}
	return xum;
}
int main()
{
	long long t;
	cin>>t;
	for(long long i=1;i<=t;i++)
	{
		cin>>x;
		x=" "+x;
		long long len=x.size()-1;
		for(long long j=1;j<=len;j++)
		{
			for(long long k=j;k<=len;k++)
			{
				dp[i][j]=10;//初始化，认为只要Alice没赢，Bob就胜利；
			}
		}
		for(long long j=2;j<=len;j+=2)
		{
			for(long long l=1;l+j-1<=len;l++)
			{
				long long r=l+j-1;
				if(j==2)
				{
					if(x[l]==x[r])
					{
						dp[l][r]=0;
					}else
					{
						dp[l][r]=-10;
					}
				}else
				{
					dp[l][r]=10;
					dp[l][r]=min(dp[l][r],max(cmp(dp[l+1][r-1],l,r),cmp(dp[l+2][r],l,l+1)));
					dp[l][r]=min(dp[l][r],max(cmp(dp[l+1][r-1],r,l),cmp(dp[l][r-2],r,r-1)));
				}
			}
		}
		if(dp[1][len]==-10)cout<<"Alice"<<endl;
		else if(dp[1][len]==0)cout<<"Draw"<<endl;
		else cout<<"Bob"<<endl;
	}
	return 0;
}
```

---

## 作者：nytyq (赞：0)

## 分析

这是一道简单博弈论与区间 DP 的结合。

容易想到是其中一个人胜利，一定是尽量让他取最小值，另外一个人尽量取最大值。

考虑到状态设计为 $dp_{i,j}$，表示在 $s[l \dots r]$ 内选择的胜负情况，$0$ 为 Alice 赢，$1$ 为平局，$2$ 为 Bob 赢。

考虑到 Alice 先手，则先考虑 Alice 是从首拿还是尾拿，接着考虑 Bob，注意 Bob 肯定选在 Alice 选完后的字符串中 DP 值最大的一头。

## ACcode

```
#include<bits/stdc++.h>
using namespace std;

const int N=2e3+10;

int T;

int dp[N][N];
string s;

int cmp(int bo,int x,int y){
	if(bo!=1) return bo;
	return (s[x]<s[y]?0:(s[x]==s[y]?1:2));
}

void solve(){
	cin>>s;
	memset(dp,3,sizeof dp);
	int n=s.size();
	s=" "+s;
	
	for(int i=1;i<n;i++) dp[i][i+1]=(s[i]==s[i+1]);
	
	for(int len=4;len<=n;len+=2){
		for(int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			int cnt=2;
			int c1=max(cmp(dp[l+1][r-1],l,r),cmp(dp[l+2][r],l,l+1));
			int c2=max(cmp(dp[l+1][r-1],r,l),cmp(dp[l][r-2],r,r-1));
			cnt=min(cnt,min(c1,c2));
			dp[l][r]=cnt;
		}
	}
	if(dp[1][n]==0) puts("Alice");
	else if(dp[1][n]==1) puts("Draw");
	else puts("Bob");
}

int main(){
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

