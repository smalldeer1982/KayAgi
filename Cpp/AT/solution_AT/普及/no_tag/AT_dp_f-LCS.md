# LCS

## 题目描述

给定一个字符串 $s$ 和一个字符串 $t$ ，输出 $s$ 和 $t$ 的最长公共子序列。

## 说明/提示

数据保证 $s$ 和 $t$ 仅含英文小写字母，并且 $s$ 和 $t$ 的长度小于等于3000。

## 样例 #1

### 输入

```
axyb
abyxb```

### 输出

```
axb```

## 样例 #2

### 输入

```
aa
xayaz```

### 输出

```
aa```

## 样例 #3

### 输入

```
a
z```

### 输出

```
```

## 样例 #4

### 输入

```
abracadabra
avadakedavra```

### 输出

```
aaadara```

# 题解

## 作者：Miracle_ZX (赞：92)

### Part 0

对于 LCS 不太熟悉的同学可以试着自己先学学，本文也讲得挺清楚的，可以学习一下。

求过审，谢谢啦~

upd：图床炸了，重新上传，工作量有点大（）

### Part 1 LCS 的原理

LCS，顾名思义，是最长公共子序列的缩写，属于一种动态规划，如果不知道定义，建议 bdfs。话不多说，进入正题。

最长公共子序列，暴力搜索肯定是可以完成的，步骤如下所述：

1. 枚举序列 $A$ 里的每一个子序列 $a_i$；

2. 检查子序列 $a_i$ 是否也是 $B$ 序列里的子序列；

3. 在每一步记录当前找到的子序列里面的最长的子序列；

暴力法虽然好写，但是效率也非常感人。在第 1 步枚举中所有的子序列有 $2^m$ 个，每个子序列在 $B$ 中检查时间复杂度为 $O(n)$。因此最坏时间复杂度为 $O(n2^m)$，指数级算法，对较长的序列求LCS是不适用的，也不用想着这道题目能过，所以我们选择用动态规划来解决这个问题。

- LCS 具有最有子结构的证明

这是我从 CSDN博主「GNG」搬运来的证明，也加入了我的一些思考，大家可以看一看。

令 $X= <x_1,x_2,...,x_m>$ 和 $Y=<y_1,y_2,...,y_n>$ 为两个序列，$Z=<z_1,z_2,z_3,...,z_k>$ 为 $X$ 和 $Y$ 的任意 LCS。则：

>如果 $x_m = y_n$，则 $z_k=x_m=y_n$ 且 $Z_{k-1}$ 是$X_{m-1}$ 和 $Y_{n-1}$ 的一个 LCS。

>如果 $x_m≠y_n$，那么 $z_k≠x_m$，意味着 $Z$ 是$X_{m-1}$和 $Y$ 的一个 LCS。

>如果 $x_m≠y_n$ 那么 $z_k≠y_n$，意味着 $Z$ 是 $X$ 和 $Y_{n-1}$ 的一个 LCS。

从上述的结论可以看出，两个序列的 LCS 问题包含两个序列的前缀的 LCS，因此，LCS 问题具有最优子结构性质。在设计递归算法时，不难看出递归算法具有子问题重叠的性质。
总之，可以证明 LCS 是所有方法中最快的一种。

根据上文的叙述，LCS 的状态转移方程应该为：

![](https://cdn.luogu.com.cn/upload/image_hosting/7f34qyce.png)



- LCS 的实现

LCS 的本质就是一个填表的过程，从 $dp[0][0]$ 开始，一直到 $dp[n - 1][m - 1]$ 结束，此题我们还要同时考虑输出路径，所以为了下文表达方便，我们不妨设：

1. 在对应字符相等的时候，用 ↖ 标记。

2. 在 $p_1 \geq p_2$ 的时候，用 ↑ 标记。

3. 在 $p_1 < p_2$ 的时候，用←标记

于是有伪代码如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/39zu1u96.png)

举个例子：
我们如果要求求 ABCBDAB 和 BDCABA 的 LCS:
![](https://cdn.luogu.com.cn/upload/image_hosting/0cch77ug.png)

我当时学习 LCS 的时候，看到了这组图片演示，感觉形象了很多。如果还是不懂，现在演示一遍怎么操作 $dp$ 数组，（以求 ABCB 和 BDCA 的 LCS 长度为例）：

![](https://cdn.luogu.com.cn/upload/image_hosting/qjzm6xxf.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/l0ex2mfm.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/yqxl80wf.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/htompjyk.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/o1p2lm45.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/6gdmv8p1.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/uop1l24r.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/oftrxf3n.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/haknquux.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/4kqcdsqg.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/ddgklzpm.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/mbvwhxhq.png)

啊，~~好累~~，以此类推，最后的表是：

![](https://cdn.luogu.com.cn/upload/image_hosting/o2gc8q3t.png)

右下角的数字 2 即为 LCS 的长度。

- LCS 的路径输出

若想得到路径，则再遍历一次 $dp$ 数组就好了，从最后一个位置开始往前遍历：

如果箭头是 ↖，则代表这个字符是 LCS 的一员，存下来后 ```i--``` , ``j--``

如果箭头是 ←，则代表这个字符不是LCS的一员，```j--```

如果箭头是 ↑，也代表这个字符不是LCS的一员，```i--```

如此直到 ```i = 0``` 或者 ```j = 0``` 时停止，存下来的部分即为 LCS 的路径。

### Part 3 Code

代码分为两个部分：

1. LCS 传统板子，求出答案字符串的长度，便于遍历使用。

2. LCS 路径的遍历，非常基础。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int dp[1010][1010];
char s1[100010], s2[100010], ans[1000010];//两个字符串以及路径

int main()
{
    scanf("%s%s", s1 + 1, s2 + 1);
	int len1 = strlen(s1 + 1), len2 = strlen(s2 + 1);
	for(int i = 1; i <= len1; i++)
	{
		for(int j = 1; j <= len2; j++)
		{
			dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			if(s1[i] == s2[j])
            {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
		}
	}//LCS 板子
	int i = len1, j = len2;//简单的双指针
	while(dp[i][j] > 0)
    {
		if(s1[i] == s2[j])
        {
            ans[dp[i][j]] = s1[i];//反向追踪所有的字符
            i--, j--;
        }
		else
        {
			if(dp[i][j] == dp[i - 1][j]) i--;
			else j--;
		}
	}
	printf("%s", ans + 1);//printf YYDS!
    return 0;
}

```

### Part 3 AC Picture

[731ms，49.62 MB](https://www.luogu.com.cn/record/57732226)


---

## 作者：lottle1212 (赞：24)

# [原题传送门](https://www.luogu.com.cn/problem/AT_dp_f)
## Part0：
首先，我们需要搞明白 LCS 是什么东西。

顾名思义，LCS 即最长公共子序列的缩写。举个简单的例子，字符串 abcd 与 accd，它们的最长公共子序列为 acd。

现在切入正题。
## Part1：
这道题可以分成两个部分，我们可以先求出 LCS 的**长度**。

LCS 的长度求法为暴力 DP，我们可以设置状态 $dp[i][j]$ 为 $s$ 的前 $i$ 项与 $t$ 的前 $j$ 项的 LCS。接下来分类讨论：
	
- 如果 $s[i]=t[j]$ ，则 $dp[i][j]=dp[i-1][j-1]+1$
- 否则， $dp[i][j]=\max\{dp[i-1][j],dp[i][j-1]\}$

由此，我们可以写下代码：
```cpp
for(i=1;i<=n;i++)
	for(j=1;j<=m;j++)
		if(s[i]==t[j]) dp[i][j]=dp[i-1][j-1]+1;//如果两个字符相等，答案为前一项的 LCS+1
		else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);//不相等，在前两个中求最大
```
### **输入：**
```
abracadabra
avadakedavra
```
### **输出：**
```
7
```
至此，LCS 求长度的代码就完成了。

时间复杂度 $O(n \times m)$ 。
## Part2：
题目中让我们求的是 LCS 的**字符串**，且只要是满足是 LCS 的任意字符串即可。那我们在做动态规划时，就要把动态转移的最优路径路径保存下来。

我们可以用布尔 $x[i][j]$ 来表示从上一个状态至此 $i$ 是否增加， $y[i][j]$ 来表示从上一个状态至此 $j$ 是否增加（可以理解为二维坐标）。

由于上面的代码中，我们已经通过判断、求最大，找出了 LCS 长度的最优解，因此只需稍稍修改，即可变为 **AC Code**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,dp[3010][3010];char a[3010],b[3010];bool x[3010][3010],y[3010][3010];
void print(int i,int j){
	if(i==0||j==0) return ;
	print(i-x[i][j],j-y[i][j]);//继续往前找
	if(a[i]==b[j]) cout<<a[i];//如果相等，说明这个字符属于LCS
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>a+1>>b+1;
	n=strlen(a+1);m=strlen(b+1);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(a[i]==b[j]) dp[i][j]=dp[i-1][j-1]+1,x[i][j]=1,y[i][j]=1;
			else if(dp[i-1][j]>dp[i][j-1]) dp[i][j]=dp[i-1][j],x[i][j]=1;
			else dp[i][j]=dp[i][j-1],y[i][j]=1;//LCS
	print(n,m);//以栈的形式输出（逆向输出）
	return 0;
}
```
注：为方便理解，原题中的 $s$、$t$ 数组在本代码中以 $a$、$b$ 代替 ~~（其实就是懒得改了）~~。

---

## 作者：GossWandering (赞：16)

绝非无意义内容。不知道为什么，这篇题解一放到洛谷博客上面就会各种崩：$\LaTeX$崩，$Markdown$崩，图床也崩。所以我只好放在云剪贴板里了：

<https://www.luogu.com.cn/paste/6q1oyrmx>

管理员大大求过qwq

---

## 作者：zhlzt (赞：11)

### 题目
- 给定两个字符序列 $s$ 和 $t$。
- 求 $s$ 和 $t$ 的最长公共子序列。
- $1\le|s|,|t|\le3000$。

### 子序列的定义
一个给定序列的子序列，是在该序列中删去若干元素后得到的序列。一个长度为 $n$ 的序列，有 $2^n$ 个子序列。

### 最长公共子序列
给定两个序列 $X$ 和 $Y$，当另一序列 $Z$ 既是 $X$  的子序列，又是 $Y$ 的子序列时，称 $Z$ 是序列 $X$ 和 $Y$ 的公共子序列。最长公共子序列时长度最长的公共子序列。

### DP 做法
设 $n=|s|$，$m=|t|$。
定义 $dp_{i,j}$ 表示 $s$ 的前 $i$ 个字符构成的序列和 $t$ 的前 $j$ 个字符构成的序列，不难得出以下状态转移方程：

$$dp_{i,j}=\begin{cases}dp_{i-1,j-1}+1 & (s_i= t_j)\\ \max(dp_{i-1,j},dp_{i,j-1}) & (s_i\ne t_j)\end{cases}$$

最终求出 $dp_{n,m}$，也就是 $s$ 和 $t$ 的最长公共子序列的长度。

但这还没有结束，还要把 $s$ 和 $t$ 的最长公共子序列求出来。

之前求长度是从前往后推，那现在求序列就得从后往前推。

由于最长公共子序列的长度掌握在 $dp_{n,m}$ 中，所以得从 $n,m$ 开始往前推。我们设 $ans$ 为 $s$ 和 $t$ 的最长公共子序列，对于每一组 $i,j$，有如下几种情况：

- 当 $s_i=t_j$ 时，$ans_{dp_{i,j}}=s_i(t_j)$，$i\gets i-1$，$j\gets j-1$。
- 当 $s_i\ne t_j$ 时，$\begin{cases}i\gets i-1& (dp_{i-1,j}> dp_{i,j-1})\\j\gets j-1 & (dp_{i-1,j}\le dp_{i,j-1})\end{cases}$ 。

直到 $dp_{i,j}=0$ 就结束。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[3010][3010];
char s[3010],t[3010],ans[3010];
int main(){
	scanf("%s%s",s+1,t+1);
	int n=strlen(s+1),m=strlen(t+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(s[i]==t[j]) dp[i][j]=dp[i-1][j-1]+1;
			else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
	int i=n,j=m;
	while(dp[i][j]>0){
		if(s[i]==t[j]) ans[dp[i][j]]=s[i],i--,j--;
		else if(dp[i-1][j]>dp[i][j-1]) i--;
		else j--;
	}
	for(int i=1;i<=dp[n][m];i++) printf("%c",ans[i]);
	return 0;
}

```

---

## 作者：云浅知处 (赞：5)

经典的「最长公共子序列」问题。

用 $F(i,j)$ 表示 $s[1\dots i]$ 与 $t[1\dots j]$ 的 LCS，那么容易得到转移方程：

$$
F(i,j)=\begin{cases}F(i-1,j-1)+1&,s[i]==t[j]\\\max\{F(i,j-1),F(i-1,j)\}&,s[i]\neq t[j]\end{cases}
$$

边界条件是 $F(0,\cdot)=F(\cdot ,0)=0$。

不过这题要求输出方案，因此我们额外记录一个 $\pi_{i,j}$ 表示 $F(i,j)$ 具体是由什么转移而来的，然后从 $i=n,j=m$ 倒推回去即可。

具体可以看代码。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>

#define int long long
const int MN=3005;

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

char s[MN],t[MN];
int dp[MN][MN],pi[MN][MN],n,m;
char ans[MN];

int cnt=0;
void print(int x,int y){
    if(x==0||y==0)return ;
    if(pi[x][y]==1)ans[cnt++]=s[x],print(x-1,y-1);
    else if(pi[x][y]==2)print(x-1,y);
    else print(x,y-1);
}

signed main(void){

    cin>>(s+1)>>(t+1);
    n=strlen(s+1),m=strlen(t+1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i]==t[j])dp[i][j]=dp[i-1][j-1]+1,pi[i][j]=1;
            else if(dp[i-1][j]>dp[i][j-1])dp[i][j]=dp[i-1][j],pi[i][j]=2;
            else dp[i][j]=dp[i][j-1],pi[i][j]=3;
        }
    }
    print(n,m);
    reverse(ans,ans+cnt);
    cout<<ans<<endl;

    return 0;
}
```

---

## 作者：Haphyxlos (赞：3)

### AT4527 LCS
[题目传送门](https://www.luogu.com.cn/problem/AT4527)

本题是 $LCS$ 的板子，我们设 $s,t$ 的长度分别为$ n, m$ ，现在考虑两个串的最后字符，一共有两种情况：

1. $s_n=t_m$ ，那么答案最末字符显然等于也等于它们俩。
2. $s_n\neq t_m$ ，那么两者必有其一不在答案中，所以答案为 $LCS\left ( s_{1\dots n}, t_{1\dots m-1}\right ) $ 与 $LCS\left ( s_{1\dots n-1}, t_{1\dots m}\right ) $ 之间的较长者。

我们用 $ dp[i][j]$ 表示 $ s$ 的前 $i$ 个字符和 $t$ 的前 $j$ 个字符的 $LCS$ 长度。那么可以得到转移方程：

$dp[i][j]=
\begin{cases}0  & i=0\; or\;j=0  \\
dp[i-1][j-1]+1&s[i]=t[j]\\
\max(dp[i-1][j],dp[i][j-1])&otherwise
\end{cases}$

答案本身只需要通过 $dp[i][j]$ 的转移来源恢复。

本题AC代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//typedef long long ll;
const int mod=1e9+7;
const double eps=1e-8;
const int INF=0x3f3f3f3f;
const int maxn=1e5+5;
const int maxm=1e6+5;
int n,m,f[5005][5005],vis[5005][5005];
char s[5005],t[5005],ans[5005];
signed main(){
//	std::ios::sync_with_stdio(false);
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1),m=strlen(t+1);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(s[i]==t[j]){
				f[i][j]=f[i-1][j-1]+1;
			}else{
				f[i][j]=max(f[i-1][j],f[i][j-1]);
			}
		}
	}	
	int i=n,j=m;
	while(f[i][j]>0){
		if(s[i]==t[j]){
			ans[f[i][j]]=s[i],i--,j--;
		}else{
			if(f[i][j]==f[i-1][j])i--;
			else j--;
		}
	}
	printf("%s",ans+1);
	return 0;
}
```

---

## 作者：lingfunny (赞：3)

# 解决$\text{LCS}$问题必须知道的$3$个性质
注：$A_k$表示序列$A$的前$k$个元素。两个序列可能有多个LCS。

假设两个序列$X=<x_1,x_2,...,x_n>,Y=<y_1,y_2,...,y_m>$，序列$Z=<z_1,z_2,...,z_k>$为这两个序列的LCS。

## 结论
1. 若$x_n=y_m$，则$x_n=y_m=z_k$且$Z_{k-1}$是$X_{n-1}$和$Y_{m-1}$的LCS。
2. 若$x_n\not=y_m$，当$z_k\not=x_n$时，$Z$是$X_{n-1}$和$Y$的LCS。
3. 若$x_n\not=y_m$，当$z_k\not=y_m$时，$Z$是$X$和$Y_{m-1}$的LCS。

## 证明
**结论1**：可以用反证法。如果$x_n=y_m\not=z_k$，那么可以把$x_n$追加到$Z$的后面，得到一个长度为$k+1$的LCS，与题设“$Z$是这两个序列的LCS”不符，所以必有$x_n=y_m=z_k$。

同样，运用反证法，假设有序列$W$为$X_{n-1}$和$Y_{m-1}$的LCS且$W$的长度大于等于$k$，那么可以把$x_n$追加到序列$W$末尾，这样就构成了一个序列长度至少为$k+1$的LCS，与“$Z$是这两个序列的LCS”矛盾。

**结论2**：同样的，用上反证法。如果存在一个$X_{n-1}$和$Y$的公共子序列$W$长度大于$k$，那么$W$也是$X_n$和$Y$的公共子序列，这时与“$Z$是这两个序列的LCS”矛盾。

**结论3**：与结论二同理。
# 递归解法
由性质可得，如果用$C[i,j]$表示$X_i$和$Y_j$的LCS长度，那么可以得到：
$$C[i,j]=\begin{cases}

0 & \text{若}i=0\text{或}j=0\\

C[i-1,j-1]+1 & \text{若}i,j>0\text{且}x_i=y_j\\

\max(C[i,j-1],C[i-1,j]) & \text{若}i,j>0\text{且}x_i\not=y_j

\end{cases}$$
此外，题目要求我们输出这个子序列，所以在每一次做选择的时候，要记下来是从哪里得到这个答案的。可以用一个$pre[i,j]$指向$C[i,j]$得到答案是是从哪里选择的。
# Code
```cpp
#include <iostream>
#include <string>
#include <cstdio>

const int maxn = 3005;

int dp[maxn][maxn],pre[maxn][maxn];
std::string A,B;

int solve(int n,int m){
	if(n<0 || m<0)return 0;
	if(dp[n][m])return dp[n][m];
	if(A[n] == B[m]){
		pre[n][m]=1;
		return dp[n][m] = solve(n-1,m-1)+1;
	} else {
		int ans1 = solve(n-1,m);
		int ans2 = solve(n,m-1);
		if(ans1 > ans2){
			pre[n][m]=2;
			return dp[n][m]=ans1;
		} else {
			pre[n][m]=3;
			return dp[n][m]=ans2;
		}
	}
}
void print(int n,int m){
	if(n<0 || m<0)return;
	if(pre[n][m] == 1){
		print(n-1,m-1);
		printf("%c",A[n]);
	} else if(pre[n][m] == 2) print(n-1,m);
	else print(n,m-1);
}

int main(){
	std::cin>>A>>B;
	solve(A.length()-1,B.length()-1);
	print(A.length()-1,B.length()-1);
	return 0;
}
```

---

## 作者：信守天下 (赞：3)

## [洛谷传送门](https://www.luogu.com.cn/problem/AT4527)
## [AT 传送门](https://atcoder.jp/contests/dp/tasks/dp_f)
## $\text {Update in 2021.9.10}$ 修改了一下代码
## 思路
设 $dp[i][j]$ 表示 $s$ 的前 $i$ 个字符和 $t$ 的前 $j$ 个字符的 LCS。

那么有两种情况：

1. $s$ 的第 $i + 1$ 个字符和 $t$ 的第 $j + 1$ 个字符相等，此时 $dp[i + 1][j + 1] = dp[i][j] + 1$。
1. $s$ 的第 $i + 1$ 个字符和 $t$ 的第 $j + 1$ 个字符不相等，此时为 $dp[i + 1][j + 1] = \max(dp[i + 1][j], dp[i][j + 1])$。

所以：

$dp[i][j] = \begin{cases}dp[i - 1][j - 1] + 1 & s[i] = t[j] \\ \max (dp[i - 1][j], dp[i][j - 1]) & s[i] \ne t[j] \end{cases}$

直接求解即可。

但是，这仅仅只计算了数量，而题目要求输出最长公共子序列。

设 $s$ 长度为 $l_1$，$t$ 长度为 $l_2$。

所以在求解完数量后，可以按照刚才的过程，从 $dp[l_1][l_2]$ 开始逆向转移。

转移方式为：

$\begin{cases}i \Rightarrow i - 1, j \Rightarrow j - 1 & s[i] = t[i] \\ i \Rightarrow i - 1 & s[i] \ne t[i] \ and \ dp[i][j] = dp[i - 1][j] \\ j \Rightarrow j - 1 & s[i] \ne t[i] \ and \ dp[i][j] = dp[i][j - 1] \end{cases}$

在遇到每一个 $s[i] = t[i]$ 时，记录当前字符，最后反向输出即可。
## code
~~~cpp
~~~cpp
#include <iostream>
using namespace std;
const int kMaxL = 3001;
string s1, s2;
int dp[kMaxL][kMaxL];
char ans[kMaxL];
int l1, l2, num;
int main() {
  cin >> s1 >> s2;
  l1 = s1.size(), l2 = s2.size();
  for (int i = 1; i <= l1; i++) {  // 求解字符数
    for (int j = 1; j <= l2; j++) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  num = dp[l1][l2];
  for (int i = l1, j = l2; num;) {  // 反向转移
    if (s1[i - 1] == s2[j - 1]) {
      ans[num--] = s1[--i];        // 记录最长公共子序列
      --j;
    } else if (dp[i][j] == dp[i - 1][j]) {
      i--;
    } else if (dp[i][j] == dp[i][j - 1]) {
      j--;
    }
  }
  for (int i = 1; i <= dp[l1][l2]; i++) {
    cout << ans[i];
  }
  return 0;
}
~~~
~~~

---

## 作者：Allen_yang (赞：2)

## AT4527 LCS
很水，但很**繁琐**的板子题

想要AC这道题，就要用到久违的打法：
# 线性 DP【模板】LCS
~~话说这题我觉得更像矩形~~

咳咳，进入正题…

首先思考一下，这题的 $dp$ 数组怎末用呢？很显然 $dp_{i,j}$ 用来表示一号字符串用到第 $i$ 个，二号字符串用到第 $j$ 个情况下的最长公共子序列长度，还有一个 $lz_{i,j}$ 数组考虑他从哪里来。

但紧接着你会发现，他和（ sang ）蔼（ xin ）可（ bing ）亲（ kuang ）地要求你输出方案，所以还需要另一个字串 $ans$ 来记录答案。

由此得出状态转移方程：
$$
dp_{i,j}=\begin{cases}
  dp_{i-1,j-1}+1&a_i=b_j\\
  \max(dp_{i-1,j},dp_{i,j-1})&a_i\ne b_j\\
\end{cases}
$$

考虑如下图：

$DP$ 样例:

|  | a | x | y | b 
| -----------: | -----------: | -----------: | -----------: | -----------: |
| a | 1 | 1 | 1 | 1 |
| b | 1 | 1 | 1 | 2 |
| y | 1 | 1 | 2 | 2 |
| x | 1 | 2 | 2 | 2 |
| b | 1 | 2 | 2 | 3 |

$lz$ 样例：

1表示从上来，2表示从左来，3表示从斜边来

|  | a | x | y | b |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| a | 3 | 2 | 2 | 2 |
| b | 1 | 2 | 2 | 3 |
| y | 1 | 2 | 3 | 2 |
| x | 1 | 3 | 2 | 2 |
| b | 1 | 2 | 2 | 3 |

最后再从后往前推到 $ans$ 即可
### 无注释code:
```cpp
#include<iostream>
#include<stack>
#include<string>
using namespace std;
int dp[4000][4000],lz[4000][4000];
int main() {
    string s,t;
    cin >> s >> t;
    int x=s.size(),y=t.size();
    s=" "+s;
    t=" "+t;
    for (int i=1; i<=x; ++i) {
        for (int j=1; j<=y; ++j) {
            if (s[i] == t[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                lz[i][j]=3;
            } else {
                if(dp[i - 1][j] < dp[i][j - 1]) {
                    dp[i][j]=dp[i][j - 1];
                    lz[i][j]=2;
                } else {
                    dp[i][j]=dp[i - 1][j];
                    lz[i][j]=1;
                }
            }
        }
    }
    string ans;
    int i=x,j=y;
    while(i>0 &&j>0) {
        if(lz[i][j]==3) {
            ans=s[i]+ans;
            i--;
            j--;
        } else if(lz[i][j]==2) {
            j--;
        } else {
            i--;
        }
    }
    cout << ans;
    return 0;
}
```


---

## 作者：Zq5437 (赞：1)

看到这道题目题干狂喜,我对着题目嘿嘿嘿,看到这个数据范围,题目对着我嘿嘿嘿……

我想着,要不暴力先试试,说不定就过了呢?

这道题主要考察动态规划,写出转移方程即可:

我们虚拟两个分别指向字符串最前面的指针,然后逐一往后去比较.

设 $ s1 $ 字符串的长度记为 $ | s1 | $ 

 当 $ s1[i] = s2[j] $ 时, $ ret[i][j] = ret[i-1][j-1] + s1[i-1] $ 

当 $ s1[i] = s2[j] $ 时:

如果 $ | ret[i-1][j] | \gt | ret[i][j-1] | $ ,  $ ret[i][j] = ret[i-1][j] $ ;

如果 $ | ret[i-1][j] | \le | ret[i][j-1] | $ , $ ret[i][j] = ret[i][j-1] $ ;

当我定义了一个 $ 3005 \times 3005 $ 的 string 数组的时候,直接段错误(╥﹏╥)

就想着能不能从数组的大小那里优化.

然后我看向了滚动数组~~(滚动数组:不要啊……)~~

感觉肯定能过了,然后超时(啪~).

分析思路后,感觉没有问题,后来发现自己的代码实现还可以优化,之前的部分如下:

```cpp
string Max(string s1,string s2)
{
    return s1.size()>s2.size()?s1:s2;
}
```

以及.

```cpp
for(int i=1;i<=s1.size();i++){
        for(int j=1;j<=s2.size();j++){
            if(s1[i-1]==s2[j-1]){
                ret[i&1][j]=ret[(i-1)&1][j-1]+s1[i-1];
            }else {
            ret[i&1][j]=Max(ret[(i-1)&1][j],ret[i&1][j-1]);
            }
        }
    }
```

虽然说封装是个好习惯,但是恰恰是封装成函数,使得这次翻车了……

我掐指一算,发现最坏的情况,调用函数太多导致时间效率过差.

于是我又改进了一下,得到了一下的 AC 代码.

------------

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3005;
string Max(string s1,string s2)
{
    return s1.size()>s2.size()?s1:s2;
}
int main()  
{
    string s1,s2;
    string ret[2][maxn]={};
    cin>>s1>>s2;
    for(int i=1;i<=s1.size();i++){
        for(int j=1;j<=s2.size();j++){
            if(s1[i-1]==s2[j-1]){
                ret[i&1][j]=ret[(i-1)&1][j-1]+s1[i-1];
            }else {
            ret[i&1][j]=(ret[(i-1)&1][j].size()>ret[i&1][j-1].size()?ret[(i-1)&1][j]:ret[i&1][j-1]);
            }
        }
    }
    cout<<Max(ret[0][s2.size()],ret[1][s2.size()])<<endl;
    return 0;
}
```
------------

## 收获

1、 LCS 的状态转移方程.
2、 滚动数组在动态规划的应用.
3、 自己封装的函数要注意时间的优化,感觉不妙就去掉函数.这条规则同样适用于头文件引用的库函数.

---

## 作者：accomplishment (赞：1)

标准 LCS 模板题，只是需要记录路径，下面是我思考这道题的详细过程：

首先就是正常的 LCS，$dp_{i, j}$ 表示 $s$ 中 $[1,i]$ 项形成的子串与 $t$ 中 $[1,j]$ 形成的子串的最长公共子序列长度。

$$dp_{i,j}=\begin{cases}dp_{i-1,j-1}+1&s_i=t_j\\\max(dp_{i-1,j},dp_{i,j-1})&s_i \neq t_j\end{cases}$$

因为如果两项相等，自然就是前一项的长度 $+1$；若不相等，就考虑是舍弃 $s_i$ 还是舍弃 $t_j$，自然最大长度是 $\max(dp_{i-1,j},dp_{i,j-1})$。

然后考虑记录路径，首先需要一个数组 $posX$ 记录上一轮转移过来的 $i$，$posY$ 记录转移过来的 $j$。如果 $s_i = t_j$，记录当前的相同字母（$s_i$ 或 $t_j$ 均可）。

先维护一个栈，然后从 $s$ 和 $t$ 的长度开始，反推回去，只要 $dp_{i,j} > 0$，就继续往前推，只要不是空字符（```'\0'```），就把记录的字符压入栈，然后 $i,j$ 分别更新为 $posX_{i,j}, posY_{i,j}$，继续往前推。

最后只要一个一个把元素从栈里弹出并输出，就得到了答案（由于是倒着压入栈的，所以弹出的时候刚好是正着的）。

下面是我的代码（不喜勿喷）。

Code：

```cpp


#include <iostream>
#include <fstream>
#include <stack>
#include <cstring>

using namespace std;

int _maxi1 = 0;
int _maxi2 = 0;
char _myStr1[3009];
char _myStr2[3009];
int _dpMap[3009][3009];
int _posXMap[3009][3009];
int _posYMap[3009][3009];
char _charMap[3009][3009];
stack<char> _myStack;

int main () {
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> (_myStr1 + 1) >> (_myStr2 + 1);
	
	_myStr1[0] = ' ', _myStr2[0] = ' ';
	_maxi1 = strlen(_myStr1), _maxi2 = strlen(_myStr2);
	
	for (int i = 1; i < _maxi1; i++) {
		for (int m = 1; m < _maxi2; m++) {
			if (_myStr1[i] == _myStr2[m]) {
				_dpMap[i][m] = _dpMap[i - 1][m - 1] + 1;
				_posXMap[i][m] = i - 1, _posYMap[i][m] = m - 1;
				_charMap[i][m] = _myStr1[i];
			}
			
			else {
				if (_dpMap[i - 1][m] > _dpMap[i][m - 1]) {
					_dpMap[i][m] = _dpMap[i - 1][m];
					_posXMap[i][m] = i - 1, _posYMap[i][m] = m;
				}
				
				else {
					_dpMap[i][m] = _dpMap[i][m - 1];
					_posXMap[i][m] = i, _posYMap[i][m] = m - 1;
				}
			}
		}
	}
	
	int posX = _maxi1 - 1;
	int posY = _maxi2 - 1;
	
	while (_dpMap[posX][posY]) {
		if (_charMap[posX][posY] != '\0') {
			_myStack.push(_charMap[posX][posY]);
		}
		
		int nextX = _posXMap[posX][posY];
		int nextY = _posYMap[posX][posY];
		
		posX = nextX;
		posY = nextY;
	}  
	
	while (!_myStack.empty()) {
		cout << _myStack.top();
		
		_myStack.pop();
	}
	
	cout << '\n';
	
	return 0;
	
}
```


---

## 作者：chenxia25 (赞：0)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT4527) & [AtCoder题目页面传送门](https://atcoder.jp/contests/dp/tasks/dp_f)

>给定$2$个字符串$a,b,|a|=n,|b|=m$，求$a,b$的最长公共子序列。若有多解，输出任一。

>$n,m\in[1,3000]$。

LCS模板题。

设$dp_{i,j}$表示$a_{1\sim i},b_{1\sim j}$的LCS长度。边界是$dp_{0,i}=dp_{j,0}=0$，状态转移方程是$dp_{i,j}=\max\begin{cases}dp_{i-1,j}\\dp_{i,j-1}\\dp_{i-1,j-1}+1&a_i=b_j\end{cases}$。记录转移路径即可知道LCS。时间复杂度$\mathrm O(nm)$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=3000,M=3000;
int n,m;
char a[N+5],b[M+5];
int dp[N+1][M+1],pa[N+1][M+1]/*转移路径*/;
int main(){
	int n,m;
	cin>>a+1>>b+1;
	n=strlen(a+1);m=strlen(b+1);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){//转移 
		dp[i][j]=dp[i-1][j];pa[i][j]=1;//第1种转移 
		if(dp[i][j-1]>dp[i][j])dp[i][j]=dp[i][j-1],pa[i][j]=2;//第2种转移 
		if(a[i]==b[j]&&dp[i-1][j-1]+1>dp[i][j])dp[i][j]=dp[i-1][j-1]+1,pa[i][j]=3;//第3种转移 
	}
	int nowi=n,nowj=m;
	string ans; 
	while(nowi&&nowj)//从后往前统计答案 
		if(pa[nowi][nowj]==1)nowi--;
		else if(pa[nowi][nowj]==2)nowj--;
		else ans+=a[nowi],nowi--,nowj--;
	for(int i=ans.size()-1;~i;i--)putchar(ans[i]);//倒序输出答案 
	return 0;
}
```

---

