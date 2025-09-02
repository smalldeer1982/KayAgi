# Coloring Brackets

## 题目描述

### 题意描述

给出一个配对的括号序列（如 “$\texttt{(())()}$”、“$\texttt{()}$” 等，“$\texttt{)()}$”、“$\texttt{(()}$”是不符合要求的），对该序列按照以下方法染色。

1. 一个括号可以染成红色、蓝色或者不染色。
2. 一对匹配的括号需要且只能将其中一个染色。
3. 相邻两个括号颜色不能相同（但都可以不染色）。

求符合条件的染色方案数，对 $1000000007$ 取模。

## 说明/提示

样例一可以如下图所示着色（其中两种）：

![](https://espresso.codeforces.com/e3c8e656cbe73b2e4000cf2784d690e7f12bcd95.png)![](https://espresso.codeforces.com/bd8a4d8804385bfb8bc0d551ed02f9d014628051.png)

下面的两种着色方式是不正确的：

![](https://espresso.codeforces.com/469169555ee8d510b0cf141b66c6c9589d20fda2.png)![](https://espresso.codeforces.com/7540d1940118fd14d1540b0b4a40397c588ddf8f.png)

## 样例 #1

### 输入

```
(())
```

### 输出

```
12
```

## 样例 #2

### 输入

```
(()())
```

### 输出

```
40
```

## 样例 #3

### 输入

```
()
```

### 输出

```
4
```

# 题解

## 作者：hhz6830975 (赞：90)

刷区间dp的时候刷到的好题，安利一波这个系列：https://www.luogu.org/blog/hhz6830975/kuangbin-dai-ni-fei-zhuan-ti-er-shi-er-ou-jian-dp

设$dp[l][r][x][y]$为区间$[l,r]$两端颜色分别为$x$、$y$的方案数（0为不染色，1为红色，2为蓝色）

对于$dp[l][r][x][y]$，<font color=#A52A2A>若保证$[l,r]$为一个合法的序列</font>，则：

1.若$l+1=r$，显然序列为

$$()$$

则有

```cpp
dp[l][r][0][1]=dp[l][r][0][2]=dp[l][r][1][0]=dp[l][r][2][0]=1;
```

2.若括号$l$与$r$配对，则对应的序列为

$$(...)$$

那么有

```cpp
for(int i=0;i<=2;i++)
    for(int j=0;j<=2;j++){
        if(j!=1) dp[l][r][0][1]=(dp[l][r][0][1]+dp[l+1][r-1][i][j])%mod;
        if(j!=2) dp[l][r][0][2]=(dp[l][r][0][2]+dp[l+1][r-1][i][j])%mod;
        if(i!=1) dp[l][r][1][0]=(dp[l][r][1][0]+dp[l+1][r-1][i][j])%mod;
        if(i!=2) dp[l][r][2][0]=(dp[l][r][2][0]+dp[l+1][r-1][i][j])%mod;
    }
```

3.若括号$l$与$r$不配对，则对应的序列为

$$(...)...(...)$$

设与括号$l$配对的括号为$match[l]$，则有

```cpp
for(int i=0;i<=2;i++)
    for(int j=0;j<=2;j++)
        for(int p=0;p<=2;p++)
            for(int q=0;q<=2;q++){
                if((j==1&&p==1)||(j==2&&p==2)) continue;
                dp[l][r][i][q]=(dp[l][r][i][q]+dp[l][match[l]][i][j]*dp[match[l]+1][r][p][q]%mod)%mod;
            }
```

以上为状态转移方式

需要注意的是，本题不采用一般的dp顺序，而是使用记忆化搜索

原因在于本题要求配对的括号有且只有一个染色，但按一般的方式难以保证配对的括号在同一区间内，即不能保证转移中用到的序列都是合法的，处理比较麻烦

而采用记忆化搜索的方式，所有操作都是在原来的合法序列上增加/删除一对括号，或是将合法序列分割成两个合法序列/将两个合法序列合并，得到的仍然是合法序列，处理起来就方便得多；而且还不需要考虑不合法的状态，时间上也得到优化

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;
const int maxn=710;
const int mod=1e9+7;
int n,match[maxn];
long long dp[maxn][maxn][3][3];
char s[maxn];
stack <int> St;

void dfs(int l,int r){
	if(l+1==r) dp[l][r][0][1]=dp[l][r][0][2]=dp[l][r][1][0]=dp[l][r][2][0]=1;
	else if(match[l]==r){
		dfs(l+1,r-1);
		for(int i=0;i<=2;i++)
			for(int j=0;j<=2;j++){
		        if(j!=1) dp[l][r][0][1]=(dp[l][r][0][1]+dp[l+1][r-1][i][j])%mod;
		        if(j!=2) dp[l][r][0][2]=(dp[l][r][0][2]+dp[l+1][r-1][i][j])%mod;
		        if(i!=1) dp[l][r][1][0]=(dp[l][r][1][0]+dp[l+1][r-1][i][j])%mod;
		        if(i!=2) dp[l][r][2][0]=(dp[l][r][2][0]+dp[l+1][r-1][i][j])%mod;
			}
	}
	else{
		dfs(l,match[l]),dfs(match[l]+1,r);
		for(int i=0;i<=2;i++)
			for(int j=0;j<=2;j++)
				for(int p=0;p<=2;p++)
					for(int q=0;q<=2;q++){
						if((j==1&&p==1)||(j==2&&p==2)) continue;
						dp[l][r][i][q]=(dp[l][r][i][q]+dp[l][match[l]][i][j]*dp[match[l]+1][r][p][q]%mod)%mod;
					}
	}
}

int main(){
	scanf("%s",s);
	n=strlen(s);
	for(int i=0;i<n;i++){
		if(s[i]=='(') St.push(i);
		else match[St.top()]=i,match[i]=St.top(),St.pop();
	}
	dfs(0,n-1);
	long long ans=0;
	for(int i=0;i<=2;i++)
		for(int j=0;j<=2;j++)
			ans=(ans+dp[0][n-1][i][j])%mod;
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：云浅知处 (赞：55)

一道区间 dp 的好题。

[更好的阅读体验？](http://yunqian-qwq.github.io/post/ti-jie-cf149d-coloring-brackets/)

------------

## 括号配对

这个，不用多说了吧。

令 `right[i]` 为第 $i$ 个括号的配对括号。

代码很好写：

```cpp
scanf("%s",s+1);
int n=strlen(s+1);
for(int i=1;i<=n;i++){
    if(s[i]=='(')stk.push(i);
    else{
        right[stk.top()]=i;
        right[i]=stk.top();
        stk.pop();
    }
}
```

具体原理很简单，可以看 [UVA673 平衡的括号 Parentheses Balance](https://www.luogu.com.cn/problem/UVA673)。

------------


## 设计状态

看到题后第一反应当然是令 `dp[l][r]` 为将区间 $[l,r]$ 内染色的总方案数。

但是题目上说：

>1. 一个括号可以染红色、蓝色或不染色
>2. 一对匹配的括号需要且只能将其中一个染色
>3. 相邻两个括号颜色不能相同（但可以都不染色）

有了这些限制之后，我们发现，如果单纯地定义 `dp[l][r]` 为将区间 $[l,r]$ 内染色的总方案数，很难转移。

换句话说，我们还需要更多的信息来进行转移。

其实只需要增加这个区间两端的括号颜色，就可以进行转移了。

那么就设计 `dp[l][r][p][q]` 为将区间 $[l,r]$ 内染色的总方案数，且最左边的括号颜色为 $p$，最右边的括号颜色为 $q$。

其中 $p,q$ 的值为 $0$ 时代表不染色，为 $1$ 时代表蓝色，为 $2$ 时代表红色。

------------

## 转移方程

首先是初始条件：如果 $r=l+1$，那么 $[l,r]$ 一定是一对匹配的括号。

所以有 `dp[l][r][0][1]=dp[l][r][0][2]=dp[l][r][1][0]=dp[l][r][2][0]=1;`。

毕竟整个区间长度就是 $2$，那么一旦左、右端点的颜色确定了，整个区间的染色方案自然也就确定了，所以只有一种。

由于「一对匹配的括号需要且只能将其中一个染色」，所以 `dp[l][r][0][0]=dp[l][r][1][2]=dp[l][r][2][1]=dp[l][r][1][1]=dp[l][r][2][2]=0`，不必再专门这五种专门赋值了。

然后，转移的时候，需要分类讨论：

- 如果第 $l$ 个括号刚好和第 $r$ 个括号配对：

那么这个区间类似于这样：`(......)`。

所以易知 `dp[l][r][0][0]=dp[l][r][1][2]=dp[l][r][2][1]=dp[l][r][1][1]=dp[l][r][2][2]=0`。原因和上面一样。

所以这五个就不需要再转移了。

至于剩下的四种情况，以 `dp[l][r][0][1]` 为例：

由于左端点不染色，右端点是 $1$                  
所以它不能 `dp[l+1][r-1][·][1]` 转移过来。     
否则相邻两个括号的颜色相同，就不符合条件了。         

那么我们从 $0$ 到 $2$ 枚举 $i,j$，然后看 $i,j$ 的值来一个一个转移即可。

```cpp
for(int i=0;i<=2;i++){
    for(int j=0;j<=2;j++){
        if(j!=1)dp[l][r][0][1]+=dp[l+1][r-1][i][j],dp[l][r][0][1]%=mod;
        if(j!=2)dp[l][r][0][2]+=dp[l+1][r-1][i][j],dp[l][r][0][2]%=mod;
        if(i!=1)dp[l][r][1][0]+=dp[l+1][r-1][i][j],dp[l][r][1][0]%=mod;
        if(i!=2)dp[l][r][2][0]+=dp[l+1][r-1][i][j],dp[l][r][2][0]%=mod;
    }
}
```

- 如果第 $l$ 个括号刚好和第 $r$ 个括号不配对：

那么我们找出与第 $l$ 个括号配对的括号。

区间大概是这样的：`(......)...(`

那么我们分别处理出区间 $[l,\texttt{right[l]}]$ 的方案数和区间 $[\texttt{right[l]}+1,r]$ 的方案数，然后相乘即可。

需要注意的是，$\texttt{right[l]}$ 与 $\texttt{right[l]}+1$ 处的括号颜色不能相同。这种情况需要特判。

```cpp
for(int i=0;i<=2;i++){
    for(int j=0;j<=2;j++){
        for(int p=0;p<=2;p++){
            for(int q=0;q<=2;q++){
                if((j==1&&p==1)||(j==2&&p==2))continue;//right[l] 与 right[l]+1 处的括号颜色相同
                dp[l][r][i][q]+=(dp[l][right[l]][i][j]*dp[right[l]+1][r][p][q]%mod);
                dp[l][r][i][q]%=mod;
            }
        }
    }
}
```

那么，转移方式就弄好啦！

有一个需要注意的点就是：转移顺序最好是以记忆化搜索的顺序来，不然的话会很麻烦。

------------

最后，上代码：

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cstdlib>
#include<stack>

#define MAXN 800
#define int long long

using namespace std;

char s[MAXN];
int dp[MAXN][MAXN][5][5],right[MAXN];
stack<int>stk;

const int mod=1000000007;

void DFS(int l,int r){
    if(r==l+1){
        dp[l][r][0][1]=dp[l][r][0][2]=dp[l][r][1][0]=dp[l][r][2][0]=1;
    }
    else if(right[l]==r){//l,r 配对
        DFS(l+1,r-1);//先处理出来 [l+1,r-1] 的方案数
        for(int i=0;i<=2;i++){
            for(int j=0;j<=2;j++){
                if(j!=1)dp[l][r][0][1]+=dp[l+1][r-1][i][j],dp[l][r][0][1]%=mod;
                if(j!=2)dp[l][r][0][2]+=dp[l+1][r-1][i][j],dp[l][r][0][2]%=mod;
                if(i!=1)dp[l][r][1][0]+=dp[l+1][r-1][i][j],dp[l][r][1][0]%=mod;
                if(i!=2)dp[l][r][2][0]+=dp[l+1][r-1][i][j],dp[l][r][2][0]%=mod;
            }
        }
        //刚才说过的转移方程
    }
    else{
        DFS(l,right[l]);
        DFS(right[l]+1,r);
        //先处理区间 [l,right[l]] 和区间 [right[l]+1,r]。
        for(int i=0;i<=2;i++){
            for(int j=0;j<=2;j++){
                for(int p=0;p<=2;p++){
                    for(int q=0;q<=2;q++){
                        if((j==1&&p==1)||(j==2&&p==2))continue;
                        dp[l][r][i][q]+=(dp[l][right[l]][i][j]*dp[right[l]+1][r][p][q]%mod);
                        dp[l][r][i][q]%=mod;
                    }
                }
            }
        }
    }
}

signed main(void){

    scanf("%s",s+1);
    int n=strlen(s+1);
    for(int i=1;i<=n;i++){
        if(s[i]=='(')stk.push(i);
        else{
            right[stk.top()]=i;
            right[i]=stk.top();
            stk.pop();
        }
    }
    //处理出配对的括号

    DFS(1,n);

    int ans=0;
    for(int i=0;i<=2;i++){
        for(int j=0;j<=2;j++){
            ans+=dp[1][n][i][j];
            ans%=mod;
        }
    }

    printf("%lld\n",ans);

    return 0;
}
```

---

## 作者：Reanap (赞：34)

这道题本质上不难，但是很麻烦，很恶心。

我看了一下，市面上的题解基本都是用$dfs$的方式来演绎这个$dp$,而且有一些雷同于单调，下面，我用区间$dp$的角度来演绎这道题。

我们姑且先定义$dp_{i,j,0}$为对区间$[i,j]$染色的方案数。

我们先考虑转移，然后根据转移再完善我们的定义。

考虑两种情况

1、对于一个括号串，他由一对单调的括号里面加上一些串组成

2、对于一个括号串，他由数对单调的括号里面加上一些串组成

对于第一种情况：

在外面的一对括号串可以有四种方式进行染色，但是却存在冲突。因为相邻的两个括号颜色不能相同，那么根据融斥的思想，我们想要算出冲突的情况。因为对于每一种外层染色的情况，我们都可以把与他相邻的一个括号染成固定的颜色，从而达到冲突的目的。

由此，为了避免计算逆元我们定义$dp_{i,j,1}$为区间$[i,j]$中串首染一种固定颜色的方案总数。得到转移方程如下:

$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ $ $dp_{i,j,0}$ = $4 * (dp_{i+1,j-1,0} - dp_{i+1,j-1,1})$

但是$dp_{i,j,1}$怎么转移呢？我们给串首固定一种颜色，那么包含在里面的串当且仅当在里面的串的串首与他颜色一致，减去即可。

$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ $ $dp_{i,j,1}$ = $dp_{i+1,j-1,0} - dp_{i+1,j-1,1}$

对于第二种情况：

根据乘法原理，先找到第一个单调括号的结尾，然后将两段相乘，再减去冲突部分，即两段相接的地方一样的时候，即为两段首颜色确定且相同的情况，有两种颜色，所以$*2$

令$f$为交界处，则有$dp$式为：

$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ $ $dp_{i,j,0}$ = $dp_{i,f,0} * dp_{f+1,j,0} - dp_{i,f,1} * dp_{f+1,j,1} * 2$


对于$dp_{i,j,1}$很简单，首位确定就与后面没什么关系了，直接乘上即可。

$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ $ $dp_{i,j,1}$ = $dp_{i,f,1} * dp_{f,j,0}$

以上是我根据排列组合的思想推出的$dp$式,希望能对大家的对$dp$的推导与理解有帮助。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int mod = 1000000007;
char s[705];
int dp[705][705][2] , n;
int pd(int x , int y) { // 用栈的方式判断。
	int f = 1 , top = 0;
	for (int i = x; i <= y; ++i) {
		if(s[i] == '(') top ++;
		else top --;
		if(top < 0) return 0;
		if(!top && i != y && f == 1) f = i;
	}
	if(top != 0) return 0;
	return f;
}
int main() {
	scanf("%s" , s + 1);
	n = strlen(s + 1);
	for (int len = 2; len <= n; len += 2) {
		for (int i = 1; i <= n; ++i) {
			int j = i + len - 1;
			if(len == 2) {
				if(s[i] == '(' && s[j] == ')') {
					dp[i][j][0] = 4;
					dp[i][j][1] = 1;//特判
				}
				continue;
			}
			int f = pd(i , j);//这个地方的判断可以在之前预处理出来，但我看见不预处理也能过就不管了。
			if(!f) continue;
			else if(f == 1) {
				dp[i][j][0] = (4ll * (long long)(dp[i + 1][j - 1][0] - dp[i + 1][j - 1][1]) % mod + mod) % mod;
				dp[i][j][1] = ((dp[i + 1][j - 1][0] - dp[i + 1][j - 1][1]) % mod + mod) % mod;
			}
			else {
				dp[i][j][0] = (long long)dp[i][f][0] * (long long)dp[f + 1][j][0] % mod - (long long) dp[i][f][1] * (long long)dp[f + 1][j][1] * 2ll % mod;
				dp[i][j][0] = (dp[i][j][0] % mod + mod) % mod;
				dp[i][j][1] = (long long)dp[i][f][1] * (long long)dp[f + 1][j][0] % mod; 
			}//dp转移
		}
	}
	printf("%d" , dp[1][n][0]);
	return 0;
}

```

---

## 作者：FjswYuzu (赞：8)

$\ \ \ \ \ \ \ $[luogu](https://www.luogu.com.cn/problem/CF149D)

$\ \ \ \ \ \ \ $其实也是裸题，只不过加上了一些预处理和颜色限制。我们首先考虑计算括号对应，很容易打出这样的代码。

```cpp
	for(long long i=1;i<=n;++i)
	{
		if(bracket[i]=='(')	S.push(i);
		else	dy[S.top()]=i,S.pop();
	}
```

$\ \ \ \ \ \ \ $加上颜色限制，定义 $dp_{i,j,0 \ or \ 1 or \ 2,0 \ or \ 1 or \ 2}$ 为区间 $[i,j]$，$i$ 不染/染成红色/染成蓝色，$j$ 同理的方案数，递归长序列，dp 合并小序列：

- 如果 $l+1=r$ ，因为这是一个合法的括号序列，包含下面的操作话这一定是一对括号；

- 如果 $dy_l=r$，递归处理 $l+1,r-1$，合并组成 dp；

- 其他情况是最麻烦的，这是两个或以上的括号序列组成的，分别划分，依次 dp，合并即可。

$\ \ \ \ \ \ \ $详见代码。

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cstring>
#include<stack>
#define MOD 1000000007ll
using namespace std;
stack<long long> S;
long long dp[705][705][3][3],dy[705],n;
char bracket[705];
/*
dp[l][r][0/1/2][0/1/2];
[l,r] l=0/1/2 r=0/1/2
还是写记忆化好理解。xd
*/
void dfs(long long l,long long r)
{
	if(l+1==r)
	{
		dp[l][r][0][1]=dp[l][r][0][2]=dp[l][r][1][0]=dp[l][r][2][0]=1;
		return ;
	}
	if(dy[l]==r)
	{
		dfs(l+1,r-1);
		for(long long i=0;i<=2;++i)
		{
			for(long long j=0;j<=2;++j)
			{
				if(i!=1)	dp[l][r][1][0]+=dp[l+1][r-1][i][j],dp[l][r][1][0]%=MOD;
				if(i!=2)	dp[l][r][2][0]+=dp[l+1][r-1][i][j],dp[l][r][2][0]%=MOD;
				if(j!=1)	dp[l][r][0][1]+=dp[l+1][r-1][i][j],dp[l][r][0][1]%=MOD;
				if(j!=2)	dp[l][r][0][2]+=dp[l+1][r-1][i][j],dp[l][r][0][2]%=MOD;
			}
		}
	}
	else
	{
		dfs(l,dy[l]);
		dfs(dy[l]+1,r);
		for(long long i=0;i<=2;++i)	for(long long j=0;j<=2;++j)	for(long long k=0;k<=2;++k)	for(long long m=0;m<=2;++m)	if(!(j && j==k))	dp[l][r][i][m]+=dp[l][dy[l]][i][j]*dp[dy[l]+1][r][k][m]%MOD,dp[l][r][i][m]%=MOD;
	}
}
int main(){
	// freopen("coloring.in","r",stdin);
	// freopen("coloring.out","w",stdout);
	scanf("%s",bracket+1);
	n=strlen(bracket+1);
	for(long long i=1;i<=n;++i)
	{
		if(bracket[i]=='(')	S.push(i);
		else	dy[S.top()]=i,S.pop();
	}
	dfs(1,n);
	long long ans=0;
	for(long long i=0;i<=2;++i)	for(long long j=0;j<=2;++j)	ans+=dp[1][n][i][j],ans%=MOD;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：slgdsxw (赞：7)

大家好，我非常喜欢分类讨论加暴力，于是我就用一种暴力的分类讨论过了这道题。

题目中有一对匹配括号只能有一个括号染色的限制，考虑通过一对括号为阶段进行转移。对于一个区间 $(l,r)$ , 设它左边 $(l-1)$ 颜色为cl，右边 $(r-1)$ 颜色为cr，设计dp状态 $ f(l,r,cl,cr) $ 为该区间方案在cl，cr限制下的方案数 。显然一个括号匹配的区间 $l$ 为左括号，设与 $l$ 匹配的右括号位置为 $p$。

1. $ p=l+1 $ 讨论 $(l,l+1)$ 这对括号的染色情况，把边界颜色的更改传递给$(l+2,r)$ 即可。

2. $ p=r $ 讨论 $(l,r) $ 这对括号的染色情况，把边界颜色的更改传递给$(l+1,r-1)$ 即可。

3. 把区间分为 $(l,p) (p+1,r)$ 两部分 讨论 $(l,r) $ 这对括号的染色情况 ,分别计算区间 $(l+1,p-1) (p+1,r)$的答案再相乘。

使用记忆化搜索，复杂度正确，代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=705,mod=1e9+7;
int n;
int f[N][N][3][3],pos[N];
char ch[N];
int dp(int l,int r,int cl,int cr)
{
	if(l>r)return cl!=cr||(cl==0&&cr==0);
	if(f[l][r][cl][cr]!=0)return f[l][r][cl][cr];
	int res=0;
	if(pos[l]==-1)
	{
		int sum=1;
		for(int i=l+1;i<=n;i++)
			if(ch[i]=='(')sum++;
			else 
			{
				sum--;
				if(!sum){pos[l]=i;break;}
			}
	}
	if(pos[l]==l+1)
	{
		if(cl!=1)res=(res+dp(l+2,r,0,cr))%mod;
		if(cl!=2)res=(res+dp(l+2,r,0,cr))%mod;
		res=(res+dp(l+2,r,1,cr))%mod;
		res=(res+dp(l+2,r,2,cr))%mod;
		return f[l][r][cl][cr]=res;
	}
	if(pos[l]==r)
	{
		if(cl!=1)res=(res+dp(l+1,r-1,1,0))%mod;
		if(cl!=2)res=(res+dp(l+1,r-1,2,0))%mod;
		if(cr!=1)res=(res+dp(l+1,r-1,0,1))%mod;
		if(cr!=2)res=(res+dp(l+1,r-1,0,2))%mod;
		return f[l][r][cl][cr]=res;
	}
	if(cl!=1)res=(res+1ll*dp(l+1,pos[l]-1,1,0)*dp(pos[l]+1,r,0,cr)%mod)%mod;
	if(cl!=2)res=(res+1ll*dp(l+1,pos[l]-1,2,0)*dp(pos[l]+1,r,0,cr)%mod)%mod;
	res=(res+1ll*dp(l+1,pos[l]-1,0,1)*dp(pos[l]+1,r,1,cr)%mod)%mod;
	res=(res+1ll*dp(l+1,pos[l]-1,0,2)*dp(pos[l]+1,r,2,cr)%mod)%mod;
	return f[l][r][cl][cr]=res;
}
int main()
{
	scanf("%s",ch+1);
	n=strlen(ch+1);
	memset(pos,-1,sizeof(pos));
	printf("%d",dp(1,n,0,0));
	return 0;
}
```


---

## 作者：lgswdn_SA (赞：4)

设计普通状态 $f(l,r)$ 代表区间 l 到 r 的括号序列的情况数。但是这有一个问题：一个点的染色会影响自己所匹配的右括号的染色和自己相邻括号的染色，所以这个自然状态显然有问题。

我们把状态具体化，$f(l,r,0/1/2,0/1/2)$ 代表 l 染黑/蓝/红，r染黑/蓝/红的情况数。

分三种讨论。第一种就是边界情况 （$r-l=1$），比较简单。

第二种是 $l,r$ 是匹配的括号，那么我们递归处理即可，即

$$
f(l,r,0,0)=f(l,r,1/2,1/2)=0
$$
$$
f(l,r,0,1/2)=f(l+1,r-1,1,0)+f(l+1,r-1,2,0)+f(l+1,r-1,0,2/1)
$$
$f(l,r,1/2,0)$ 也一样。

第三种是 $l,r$ 不匹配，我们可以把它划分成一组匹配的括号序列和剩下的部分。我们假设把它分割成 $(l,l$对应的右括号$)$ 和剩下的部分。合并的时候我们只需要关系两个相邻的是否颜色一样即可。由于我懒得展开所以我直接一下子把 $f(l,r,*,*)$ 全部算出来了。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define rev(a) (cr==1?2:1)
#define int long long
#define rep2(i) for(int i=0;i<=2;i++)

using namespace std;
const int N=709,mod=1000000007;

int n,match[N],f[N][N][3][3];
int dfs(int l,int r,int cl,int cr) {
	if(f[l][r][cl][cr]!=-1) return f[l][r][cl][cr]; 
	else if(r-l==1) return f[l][r][cl][cr]=(cl>0)!=(cr>0);
	
	f[l][r][cl][cr]=0;
	if(match[l]==r) {
		if(!cl&&!cr||cl&&cr) return f[l][r][cl][cr]=0;
		else if(cl==0)
			return f[l][r][cl][cr]=(dfs(l+1,r-1,1,0)+dfs(l+1,r-1,2,0)
							+dfs(l+1,r-1,0,rev(cr))
							+dfs(l+1,r-1,1,rev(cr))
							+dfs(l+1,r-1,2,rev(cr))
							+dfs(l+1,r-1,0,0))%mod;
		else if(cr==0)
			return f[l][r][cl][cr]=(dfs(l+1,r-1,0,1)+dfs(l+1,r-1,0,2)
							+dfs(l+1,r-1,rev(cl),0)
							+dfs(l+1,r-1,rev(cl),1)
							+dfs(l+1,r-1,rev(cl),2)
							+dfs(l+1,r-1,0,0))%mod;
	} else {
		rep2(i) rep2(j) f[l][r][i][j]=0;
		rep2(i) rep2(j) rep2(k) rep2(p)
			if(j&&k&&(j==k)) continue;
			else (f[l][r][i][p]+=dfs(l,match[l],i,j)*dfs(match[l]+1,r,k,p))%=mod;
		return f[l][r][cl][cr];
	}
}

char s[N];
signed main() {
	memset(f,-1,sizeof(f));
	scanf("%s",s+1); int n=strlen(s+1);
	stack<int>st;
	for(int i=1;i<=n;i++) {
		if(s[i]=='(') st.push(i);
		else match[st.top()]=i,st.pop();
	}
	int ans=0;
	rep2(i) rep2(j) (ans+=dfs(1,n,i,j))%=mod;
	printf("%lld",ans);
	return 0;
}
```

CF评测记录：https://codeforc.es/problemset/submission/149/85169174  
洛谷评测记录：https://www.luogu.com.cn/record/34682304


---

## 作者：AuSquare (赞：4)

### 记忆化搜索+区间DP

#### 首先明确一下事实:
1.对于任意一个合法的括号序列,**其必以'('开始,以')'结束**

2.对于任意一个合法的括号序列$[l,r]$,存在以下三种拆分情况(这里我们规定以成对出现的括号作为互相匹配的括号对,以大写字母表示合法的括号序列):

(1).若$l+1=r$,则该括号序列一定为$$()$$
(2).若$l$位置的括号与$r$位置的括号恰好成对则该序列形如$$(\underbrace{\ldots}_{\rm A})$$
(若$A$不为合法序列,则其中未匹配的左括号或右括号会与$r$位置或$l$位置的括号发生配对不满足假设), 发现可以将该序列缩小为更小的合法序列A

(3).若$l$位置的左括号与$r$位置的括号分属于两对不同的匹配括号,则该序列形如$$\underbrace{(\ldots)}_{\rm A}\underbrace{\ldots(\ldots)}_{\rm B}$$
发现可以将该序列拆成做合法序列$A$与右合法序列$B$(两括号中间部分可以为空)

至此我们发现,每一个合法的括号序列都可以拆分为更小的合法序列,最终拆分出最小的合法序列单元$"()"$,而较大的合法序列的方案数均需要由较小的合法序列推出,至此这题的方法就非常明确了:用递归拆分较大的合法序列,用区间DP转移较小的序列与较大序列的方案数.

#### 接下来的任务就是状态转移方程了
我们用$dp[l][r][x][y]$表示$l$到$r$的序列左端染色为$x$,右端染色为$y$的方案数(0表示不染色, 1表示染蓝色, 2表示染红色)

(1).对于情况1(边界条件),显然有
```cpp
dp[l][r][1][0]=dp[l][r][2][0]=dp[l][r][0][1]=dp[l][r][0][2]=1;
```
(2).对于情况2,枚举内层左右端染色并根据题目要求(相同染色不能相邻)转移方案
```cpp
for (int i=0; i<=2; i++)
	for (int j=0; j<=2; j++) {
		if (i!=1) dp[l][r][1][0]=(dp[l][r][1][0]+dp[l+1][r-1][i][j])%MOD;
		if (i!=2) dp[l][r][2][0]=(dp[l][r][2][0]+dp[l+1][r-1][i][j])%MOD;
		if (j!=1) dp[l][r][0][1]=(dp[l][r][0][1]+dp[l+1][r-1][i][j])%MOD;
		if (j!=2) dp[l][r][0][2]=(dp[l][r][0][2]+dp[l+1][r-1][i][j])%MOD;//防止被染成相同颜色的两个括号连在一起
	}
```
(3).对于最后一种情况,即将某合法序列拆成左右两个合法序列的情况.我们用$match[l]$表示位置$l$上的左括号匹配的右括号的位置,则转移如下
```cpp
for (int i=0; i<=2; i++) 
	for (int j=0; j<=2; j++)
		for (int p=0; p<=2; p++)
			for (int q=0; q<=2; q++) {
				if ((j==1 && p==1) || (j==2 && p==2)) continue;
				dp[l][r][i][q]=(dp[l][r][i][q]+dp[l][match[l]][i][j]*dp[match[l]+1][r][p][q])%MOD;
			}
```

---

## 作者：Bosun (赞：3)

~~嗯，读完一遍题发现很像CSPd1t2有木有，莫非？~~
好了回归正题qwq

所有的括号序列，都是形如(()()()(()()))(())(()())
很简单，只有两种形态，**一是套上一个括号序列，二是与前面的括号序列相接**。dp状态需要合并哦，这让我们想到了尘封已久的区间dp！

状态转移就可以推出来了哦，设f[l][r]表示l-r区间合法染色的种数，那么有两种情况（l-r默认是合法序列，这个可以通过记忆化搜索来保证）

1.l与r是一对匹配的括号，此时**f[l][r]=(f[l+1][r-1])+限制**

2.l与r不匹配，此时**f[l][r]=f[l][p[l]]×f[p[l]+1][r]+限制**（p[l]表示与l匹配的括号位置）

如果要比较方便地实现，建议再开两维分别表示l，r的颜色。

注意取模和记搜，完结撒花(*^▽^*)！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=705;
char s[N];
typedef long long ll;
const ll mod=1e9+7;
int n;
ll f[N][N][3][3],fl[N][N];
int tot,st[N],q[N];
void dfs(int l,int r){
	int i,j,k,m;
	if(l>r){
		fl[l][r]=1;
		return ;	
	}
	if(l==r){
		for(i=0;i<3;i++)f[l][r][i][i]=1;
		fl[l][r]=1;
		return ;
	}
	if(fl[l][r]){
		return ;	
	}	
	if(q[l]==r){
		if(l==r-1){
			f[l][r][0][1]=1;f[l][r][1][0]=1;
			f[l][r][0][2]=1;f[l][r][2][0]=1;
			fl[l][r]=1;
			return ;
		}
		dfs(l+1,r-1);
		f[l][r][0][1]=(f[l+1][r-1][0][0]+f[l+1][r-1][0][2]+f[l+1][r-1][1][0]
		+f[l+1][r-1][1][2]+f[l+1][r-1][2][0]+f[l+1][r-1][2][2])%mod;
		f[l][r][0][2]=(f[l+1][r-1][0][0]+f[l+1][r-1][0][1]+f[l+1][r-1][1][0]
		+f[l+1][r-1][1][1]+f[l+1][r-1][2][0]+f[l+1][r-1][2][1])%mod;
		f[l][r][1][0]=(f[l+1][r-1][0][0]+f[l+1][r-1][0][1]+f[l+1][r-1][0][2]
		+f[l+1][r-1][2][0]+f[l+1][r-1][2][1]+f[l+1][r-1][2][2])%mod; 
		f[l][r][2][0]=(f[l+1][r-1][0][0]+f[l+1][r-1][0][1]+f[l+1][r-1][0][2]
		+f[l+1][r-1][1][0]+f[l+1][r-1][1][1]+f[l+1][r-1][1][2])%mod; 
		fl[l][r]=1;
		return ;
	}else{
		dfs(l,q[l]),dfs(q[l]+1,r);
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				for(k=0;k<3;k++){
					for(m=0;m<3;m++){
						if(k!=m||(k==0&&m==0)){
							f[l][r][i][j]=(f[l][r][i][j]+(f[l][q[l]][i][k]*f[q[l]+1][r][m][j])%mod)%mod;
						}	
					}
				}
			}
		}
		fl[l][r]=1;
		return ;
	}
}
int main(){
	int i,j;
	scanf("%s",s+1);
	n=strlen(s+1);
	for(i=1;i<=n;i++){
		if(s[i]=='(')st[++tot]=i;
		else {
			int t=st[tot];tot--;
			q[i]=t,q[t]=i;
		} 
	}
	for(i=1;i<=n;i++)
	dfs(1,n);
	ll ans=0;
	for(i=0;i<3;i++)for(j=0;j<3;j++)ans=(ans+f[1][n][i][j])%mod;
	cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：陈彬 (赞：2)

# 思路
## 题目类型
这是一个区间动态规划，但是与以往的有所不同，我们来分析一下

## 题目求解
设题目里的字符串为 $s$ 一看到括号匹配，我们就要想到用栈来获取一下匹配的信息 

我们在这里定义 $match[i]$ 为 括号 $s[i]$ 的 匹配位置下标

(例如" ( ( ) ( ) ) " ,$match = [6,3,2,5,4,1]$)

此时我们设红色为 $1$ ,蓝色为 $2$ ，无色为 $0$ ，

于是我们设 $dp[l][r][i][j]$ 为 区间 $[l - r]$ 左端($l$)颜色为 $i$ ，右端($r$)颜色为 $j$ 的方案数

发现这道题可能无法像以往的区间一样转移了，于是我们把递推改成搜索

容易发现初始化 $dp[i][i + 1][0][1] = dp[i][i + 1][1][0] = dp[i][i + 1][0][2] = dp[i][i + 1][2][0] = 1~~ (i + 1 = match[i])$

此时分类讨论，如果区间 $[l - r]$ 满足 $r = match[l]$ 那么由于相邻颜色不同的原则，可得

当 $i~ != 1$ 时, $dp[l][r][1][0] = dp[l][r][1][0] + dp[l][r][i][j]$

…………
(四种情况分别为左端红色 $i$ 不为 1,左端蓝色 $i$ 不为 2,右端红色 $j$ 不为 1,右端蓝色 $j$ 不为 2)

如果区间 $[l - r]$ 不满足 $r = match[l]$ 那么根据乘法原理

$dp[l][r][i][j] = dp[l][r][i][j] + dp[l][match[l]][i][k] * dp[match[l] + 1][j][p]$ $k$ 和 $j$ 不能同时等于 $1$ 或 $2$ (相邻的颜色不能相同,但是可以同时不染色)

之后求最终解的时候是四种情况

# 代码
## 核心代码
```cpp
void dfs (int l ,int r) {
	if (l + 1 == r) dp[l][r][0][1] = dp[l][r][1][0] = dp[l][r][0][2] = dp[l][r][2][0] = 1;//当他们相邻的时候（匹配），此时 4种情况都是 1 
	else if (match[l] == r) {//如果 l 和 r 匹配 
		dfs (l + 1 ,r - 1);//递归先去寻找里面的 
		for (int q = 0;q <= 2;++ q) {
			for (int w = 0;w <= 2;++ w) {
				if (q != 1) dp[l][r][1][0] = (dp[l][r][1][0] + dp[l + 1][r - 1][q][w]) % mod;//转移状态 
				if (q != 2) dp[l][r][2][0] = (dp[l][r][2][0] + dp[l + 1][r - 1][q][w]) % mod;
				if (w != 1) dp[l][r][0][1] = (dp[l][r][0][1] + dp[l + 1][r - 1][q][w]) % mod;
				if (w != 2) dp[l][r][0][2] = (dp[l][r][0][2] + dp[l + 1][r - 1][q][w]) % mod;
			}
		}
	}
	else {//l 和 r 不匹配 
		dfs (l ,match[l]) ;dfs (match[l] + 1, r);//递归分段，一段是匹配段 l - match[l] ，剩下的一段 
		for (int q = 0;q <= 2;++ q) {
			for (int w = 0;w <= 2;++ w) {
				for (int e = 0;e <= 2;++ e) {
					for (int t = 0;t <= 2;++ t) {
						if ((w == 1 && e == 1) || (w == 2 && e == 2)) continue ;//相邻的颜色不能相同，但是可以同时不染色
						dp[l][r][q][t] = (dp[l][r][q][t] + dp[l][match[l]][q][w] * dp[match[l] + 1][r][e][t] % mod) % mod; 
					}
				}
			}
		}
	}
}

```
## 全部代码
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const int MAXN = 1e2 * 7 + 10;
stack <int > p;
int n ,match[MAXN];
ll ans = 0 ,dp[MAXN][MAXN][3][3];
char s[MAXN];
void dfs (int l ,int r) {
	if (l + 1 == r) dp[l][r][0][1] = dp[l][r][1][0] = dp[l][r][0][2] = dp[l][r][2][0] = 1;//当他们相邻的时候（匹配），此时 4种情况都是 1 
	else if (match[l] == r) {//如果 l 和 r 匹配 
		dfs (l + 1 ,r - 1);//递归先去寻找里面的 
		for (int q = 0;q <= 2;++ q) {
			for (int w = 0;w <= 2;++ w) {
				if (q != 1) dp[l][r][1][0] = (dp[l][r][1][0] + dp[l + 1][r - 1][q][w]) % mod;//转移状态 
				if (q != 2) dp[l][r][2][0] = (dp[l][r][2][0] + dp[l + 1][r - 1][q][w]) % mod;
				if (w != 1) dp[l][r][0][1] = (dp[l][r][0][1] + dp[l + 1][r - 1][q][w]) % mod;
				if (w != 2) dp[l][r][0][2] = (dp[l][r][0][2] + dp[l + 1][r - 1][q][w]) % mod;
			}
		}
	}
	else {//l 和 r 不匹配 
		dfs (l ,match[l]) ;dfs (match[l] + 1, r);//递归分段，一段是匹配段 l - match[l] ，剩下的一段 
		for (int q = 0;q <= 2;++ q) {
			for (int w = 0;w <= 2;++ w) {
				for (int e = 0;e <= 2;++ e) {
					for (int t = 0;t <= 2;++ t) {
						if ((w == 1 && e == 1) || (w == 2 && e == 2)) continue ;//相邻的颜色不能相同，但是可以同时不染色
						dp[l][r][q][t] = (dp[l][r][q][t] + dp[l][match[l]][q][w] * dp[match[l] + 1][r][e][t] % mod) % mod; 
					}
				}
			}
		}
	}
}
int main () {
	scanf ("%s",s + 1);
	n = strlen(s + 1);
	for (int q = 1;q <= n;++ q) {
		if (s[q] == '(') p.push(q);
		else {
			match[p.top()] = q ,match[q] = p.top();//处理匹配的括号 
			p.pop();
		}
	}
//	for (int q = 1;q <= n;++ q) {
//		printf ("%d ",match[q]);
//	}printf ("\n");
	dfs (1 ,n);
	for (int q = 0;q <= 2;++ q) {
		for (int w = 0;w <= 2;++ w) {
			ans += dp[1][n][q][w];//统计四种情况的和 
			ans %= mod;
		}
	}
	printf ("%lld\n",ans);
	return 0;
}

```


---

## 作者：RyexAwl (赞：0)

性质：对于任意一种钦定了 $k$ 个连续段染色的方案，该情况下的方案数为 $2^k$ ，令 $cnt[k]$ 为钦定 $k$ 个连续段染色的方案数，那么总的方案数即 $\sum_k cnt[k]\times 2^k$ 。

（因为我们只要确定每一段第一个位置的颜色，其他位置的颜色一定是唯一确定的，每段第一个位置颜色有两种填法，因此方案数为 $2^k$ 。）

![](https://cdn.luogu.com.cn/upload/image_hosting/32emh259.png)

例如对于上图来说，我们钦定了三段染色，方案数即 $2^3$ 。

若区间 $[l,r]$ 是合法括号段，令 $f[l,r,0/1,0/1]$ 为考虑子段 $[l,r]$ 且左端点不染色 / 染色，右端点不染色/染色的方案数。

若 $r$ 匹配的位置 $pr\not= l$ ，其对应着一个二区间合并。

令区间 $S_1$ 为区间 $[l,pr-1]$ ，区间 $S_2$ 为区间 $[pr,r]$ 。

令 $cnt_1[k,0/1,0/1]$ 为区间 $S_1$ 中钦定 $k$ 段染色且左端点不染色 / 染色，右端点不染色/染色的方案数， $cnt_2[k,0/1,0/1]$ 为区间 $S_2$ 中钦定 $k$ 段染色且左端点不染色 / 染色，右端点不染色/染色的方案数。

令：$cnt_i[k,..,t] = cnt_i[k,0,t] + cnt_i[k,1,t]$

那么根据乘法原理，有 ：

$$
f[l,r,t1,t2] = \sum_{k_1,k_2} (cnt_1[k_1,t1,0] \times cnt_2[k_2,..,t_2] + cnt_1[k_1,t1,1] \times cnt_2[k_2,0,t_2]) * 2^{k_1+k_2} + \sum_{k_1,k_2} cnt_1[k_1,t1,1] \times cnt_2[k_2,1,t_2] * 2^{k_1+k_2-1}
$$

发现是一个卷积的形式。

并且状态间的乘法显然可以看成卷积：

$$
f[l,pr-1,t_1,op_1] \times f[pr,r,op_2,t_2] = \sum_{k_,k_2} cnt_1[k_1,t_1,op_1] \times cnt_2[k_2,op_2,t_2] \times 2^{k_1+k_2}
$$

那么对于前面 $\sum_{k_1,k_2} (cnt_1[k_1,t1,0] \times cnt_2[k_2,..,t_2] + cnt_1[k_1,t1,1] \times cnt_2[k_2,0,t_2]) * 2^{k_1+k_2}$ 的处理是平凡的。

考虑从后面提取一个系数

$$
\sum_{k_1,k_2} cnt_1[k_1,t1,1] \times cnt_2[k_2,1,t_2] * 2^{k_1+k_2-1} = \dfrac{1}{2}\sum_{k_1,k_2} cnt_1[k_1,t1,1] \times cnt_2[k_2,1,t_2] * 2^{k_1+k_2}
$$

那么对应的转移即 $\dfrac{1}{2}\times f[l,pr-1,t_1,1] \times f[pr,r,1,t_2]$ 。

对于 $l$ 和 $r$ 匹配的情况可以看成单点和区间的拼接，思考方式也类似，总的复杂度为 $O(n^3)$ 。

```cpp
#include <bits/stdc++.h>

#define rep(i,l,r) for (int i = l; i <= r; i++)
#define per(i,r,l) for (int i = r; i >= l; i--)
#define fi first
#define se second
#define prt std::cout
#define gin std::cin
#define edl std::endl
#define int long long

namespace wxy{

const int N = 705,mod = 1e9 + 7;

int n,f[N][N][2][2],s[N][N],pos[N];

char str[N];

inline bool check(int l,int r){
	std::stack<int> tt; memset(pos,0,sizeof pos);
	rep(i,l,r){
		if (str[i] == '(') tt.push(i);
		else if (tt.size() == 0) return false;
		else {pos[i] = tt.top(); tt.pop();}
	}
	return tt.size() == 0 ? true : false;
}

inline void add(int &x,int v){x = (x + v) % mod;}

inline int fpow(int a,int b){
	int res = 1;
	for (;b;b>>=1){
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
	}
	return res;
}

inline void update(int l,int r,int k,int ls,int rs){
	add(f[l][r][ls][rs],f[l][k][ls][0] * ((f[k+1][r][1][rs] + f[k+1][r][0][rs]) % mod) % mod);
	add(f[l][r][ls][rs],f[l][k][ls][1] * f[k+1][r][0][rs] % mod);
	add(f[l][r][ls][rs],fpow(2,mod-2) * f[l][k][ls][1] %mod * f[k+1][r][1][rs] %mod);
}

inline void main(){
    #ifndef ONLINE_JUDGE
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif
    gin >> str; n = strlen(str);
    per(i,n,1) str[i] = str[i - 1];
    for (int len = 2; len <= n; len++){
		for (int l = 1; l <= n - len + 1; l++){
			int r = l + len - 1;
			if (!check(l,r)) continue;
			if (len == 2){ 
				f[l][r][1][0] = f[l][r][0][1] = 2;
				add(s[l][r],f[l][r][0][0]); add(s[l][r],f[l][r][0][1]);
				add(s[l][r],f[l][r][1][0]); add(s[l][r],f[l][r][1][1]);
				continue;
			}
			if (pos[r] == l){
				
				add(f[l][r][1][0],2 * ((f[l+1][r-1][0][1] + f[l+1][r-1][0][0]) % mod) % mod);
				add(f[l][r][1][0],(f[l+1][r-1][1][1] + f[l+1][r-1][1][0]) % mod);
				
				add(f[l][r][0][1],2 * ((f[l+1][r-1][1][0] + f[l+1][r-1][0][0]) % mod) % mod);
				add(f[l][r][0][1],(f[l+1][r-1][1][1] + f[l+1][r-1][0][1]) % mod);
				
				add(s[l][r],f[l][r][0][0]); add(s[l][r],f[l][r][0][1]);
				add(s[l][r],f[l][r][1][0]); add(s[l][r],f[l][r][1][1]);
				continue;
			}
			int k = pos[r] - 1;
			if (!check(l,k) || !check(k+1,r)) continue;
			update(l,r,k,0,0); update(l,r,k,0,1);
			update(l,r,k,1,0); update(l,r,k,1,1);
			add(s[l][r],f[l][r][0][0]); add(s[l][r],f[l][r][0][1]);
			add(s[l][r],f[l][r][1][0]); add(s[l][r],f[l][r][1][1]);
		}
	}
	prt << s[1][n];
}

}signed main(){wxy::main(); return 0;}
```


---

## 作者：鹭天 (赞：0)

# [建议到博客中去观看！](https://blog.csdn.net/huang_ke_hai/article/details/108586894)
## [题目传送门](https://codeforces.com/problemset/problem/149/D)
## 题目描述：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200914200757963.png#pic_center)
***
## Solution
我们考虑一对括号能够产生的贡献。
设$dp[l][r][i][j]$表示当前区间为$[l,r]$，第$l$个括号的颜色为$i$，第$r$个括号的颜色为$j$的方案数。($i,j\in [0,1,2]$)

我们设$mat[i]$表示第$i$个括号匹配到的右括号的位置(其中第$i$个括号为左括号)，这里我们需要用一个栈去操作：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200914201540914.png#pic_center)


接着对于问题在$[l,r]$的区间，我们需要分类讨论:
1、$l+1==r$，此时对应这种情况：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200914201815622.png#pic_center)

即只有一个合法括号对，这时候我们直接赋值：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200914201850226.png#pic_center)

注意，同一对括号有且只能有一种颜色，所以两种颜色都有的是无法更新的。

2、$mat[l]==r$，此时对应这种情况：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200914202011496.png#pic_center)

（咳咳，中间的字符就不用管了）
这个时候，我们的答案是能够直接从$[l+1,r-1]$这段区间转移过来的，直接类加上答案即可。需要注意的细节就是相邻的不能重复：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200914202139405.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2h1YW5nX2tlX2hhaQ==,size_16,color_FFFFFF,t_70#pic_center)

3、$mat[l]!=r$，即这种情况：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200914202734319.png#pic_center)


这种情况的时候我们需要先把两边的区间递归求解，然后再来合并答案。

这个时候有点麻烦，因为有四个括号，我们需要用四重循环分别取枚举每个括号的颜色，同时需要注意将重复的给判掉。
由于两个括号序列是独立的，所以是相乘。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200914202911825.png#pic_center)

分类讨论的情况我们结束了，接下来就是累加答案。

分别枚举$1号和n号括号的颜色$然后累加即可。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200914203051806.png#pic_center)

此时不判颜色也没关系，因为贡献就位0，当然判了也没关系。
***
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1e3+10,P = 1e9+7;
int n;
char s[N];
int dp[N][N][3][3];
int mat[N];

void Find(){
	stack < int > q;
	for (int i = 1; i <= n; i++)
	  if (s[i] == '(') q.push(i);
	  else mat[q.top()] = i,q.pop();
}
#define f dp[l][r]
#define f1 dp[l][mat[l]]
#define f2 dp[mat[l]+1][r]
#define f3 dp[l+1][r-1]
void dfs(int l,int r){
	if (l + 1 == r){
		f[0][1] = f[0][2] = f[1][0] = f[2][0] = 1;
		return;
	}
	if (mat[l] == r){
		dfs(l+1,r-1);
		for (int i = 0; i <= 2; i++)
		  for (int j = 0; j <= 2; j++){
		  	  if (i!=1) f[1][0] = (f[1][0] + f3[i][j])%P;
		  	  if (i!=2) f[2][0] = (f[2][0] + f3[i][j])%P;
		  	  if (j!=1) f[0][1] = (f[0][1] + f3[i][j])%P;
		  	  if (j!=2) f[0][2] = (f[0][2] + f3[i][j])%P;
		  }
		  return;
	}
	dfs(l,mat[l]); dfs(mat[l]+1,r);
	for (int il = 0; il <= 2; il++)
	  for (int jl = 0; jl <= 2; jl++)
	    for (int jr = 0; jr <= 2; jr++)
	      for (int ir = 0; ir <= 2; ir++){
	      	if ((jl == jr) && jl != 0) continue;
	      	  f[il][ir] = (f[il][ir] + f1[il][jl] * f2[jr][ir])%P;
	      }
	return;
	  
}

signed main(){
	scanf("%s",s+1);
	n = strlen(s+1);
	Find();
	dfs(1,n);
	int ans = 0;
	for (int i = 0; i <= 2; i++)
	  for (int j = 0; j <= 2; j++) ans = (ans + dp[1][n][i][j])%P;
	cout<<ans;
}
```



---

