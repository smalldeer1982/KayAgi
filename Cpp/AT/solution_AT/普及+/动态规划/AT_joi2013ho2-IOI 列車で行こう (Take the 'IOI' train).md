# IOI 列車で行こう (Take the 'IOI' train)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2013ho/tasks/joi2013ho2

IOI 国ではこのたび新たに鉄道を敷設した．IOI 国の鉄道を走る列車はいくつかの車両が連結されたものであり，車両には `I`，`O` の $ 2 $ 種類がある．車両はそれぞれ異なる種類の車両としか連結できない．また，列車に運転席を設ける関係上，列車の両端の車両は種類 `I` でなければならない．列車は車両の種類を表す文字を順につなげた文字列で表され，列車の長さはその文字列の長さであるとする．たとえば， `IOIOI` の順に車両を連結すると長さ $ 5 $ の列車を編成でき，また車両 `I` は単独で長さ $ 1 $ の列車である．車両を `OIOI` や `IOOI` といった順に並べても列車を編成することはできない．

いくつかの車両が $ 2 $ つの車庫に格納されている．それぞれの車庫の中には車両が一列に並んでいる．列車を編成するときは車庫から車両を出してきて車庫前で連結していく．車庫から出せる車両は最も車庫の入り口に近い車両のみであるが，どちらの車庫から車両を出すかの順番については自由である．

列車を編成する前に，車両を好きなだけ車庫から出して別の待機用レールに移すことができる．一度待機用レールに移した車両は今後列車を編成するために使うことはできない．また，一度列車の編成を始めるとその編成が終わるまでの間は車両を車庫から待機用レールに移すことはできない．

列車を編成するとき，車庫内の全ての車両を使い切る必要はない．すなわち，列車の編成を終えた後，車庫内に使われなかった車両が残っていても構わない．

IOI 国では鉄道に乗る人がとてもたくさんいると考えられているので，できるだけ長い列車を編成したい．

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_joi2013ho2/e7f0a1c5c92198e9f99bd34c7f7c4549df9732c2.png)列車を編成している途中であり，このとき車庫にある車両を待機用レールに移すことはできない．この図は入出力例 $ 1 $ に対応している．

## 说明/提示

### 課題

車庫に格納された車両の情報が与えられたとき，編成できる列車の長さの最大値を求めるプログラムを作成せよ．それぞれの車庫に格納された車両の列は $ 2 $ 種類の文字 `I`，`O` のみからなる文字列で表され，$ 2 $ つの車庫の情報はそれぞれ長さ $ M $ の文字列 $ S $ および長さ $ N $ の文字列 $ T $ として与えられる．各文字が $ 1 $ つの車両を表し，その文字は車両の種類と同じである．文字列の $ 1 $ 文字目は最も車庫の入り口に近い車両を表し，末尾の文字が車庫の最も奥にある車両を表す．

### 制限

$ 1\ \leqq\ M\ \leqq\ 2\,000 $ 文字列 $ S $ の長さ$ 1\ \leqq\ N\ \leqq\ 2\,000 $ 文字列 $ T $ の長さ- - - - - -

### 採点基準

採点用データのうち，配点の $ 20 $ %分については，$ M\ \leqq\ 10 $，$ N\ \leqq\ 10 $ を満たす．

採点用データのうち，配点の $ 50 $ %分については，$ M\ \leqq\ 50 $，$ N\ \leqq\ 50 $ を満たす．

- - - - - -

### Sample Explanation 1

$ S $ によって表される車庫を車庫 S とし，$ T $ によって表される車庫を車庫 T としよう．このとき，たとえば車庫 S から最初の $ 1 $ 車両，車庫 T から最初の $ 2 $ 車両を出して待機させた後，車庫 S，車庫 S，車庫 T，車庫 S，車庫 S，車庫 T，車庫 T の順番に車両を出せば，長さ $ 7 $ の列車 `IOIOIOI` を編成できる． 他にも，車庫 S から最初の $ 1 $ 車両，車庫 T から最初の $ 2 $ 車両を出して待機させた後，車庫 T，車庫 T，車庫 S，車庫 S，車庫 T，車庫 S，車庫 S の順番に車両を出すことでも長さ $ 7 $ の列車を編成できる．これより長い列車を編成することはできないので $ 7 $ を出力する． - - - - - -

### Sample Explanation 2

$ 1 $ つの車両のみからなる列車 `I` も列車としての条件を満たすことに注意せよ．

## 样例 #1

### 输入

```
5 5
OIOOI
OOIOI```

### 输出

```
7```

## 样例 #2

### 输入

```
5 9
IIIII
IIIIIIIII```

### 输出

```
1```

# 题解

## 作者：Allan_Xu (赞：1)

#### [题目传送门](https://www.luogu.com.cn/problem/AT_joi2013ho2)

1. **状态设计** ：$f_{i,j,0/1}$ 表示 $a$ 字符串用了（不管组没组装到车上）$i$ 位，$b$ 字符串用了 $j$ 位，以 $O$（0） ，$I$（1）为结尾的能组装的最长车辆；

2. **状态转移** ：我们根据定义，很容易想到式子：

   $$f_{i,j,0}=\operatorname{max}(f_{i-1,j,1}+1,f_{i,j-1,1}) \\f_{i,j,1}=\operatorname{max}(f_{i-1,j,0}+1,f_{i,j-1,0})$$

> 我们还需注意三点：
>
> ①：$i=0$ 时，我们是不能从 $a$ 转移（显然，我们不能从未知空间出拉出一个 $1$ 出来）；
>
> ②：$j=0$ 时，我们是不能从 $b$ 转移（与①同理）；
>
> ③：当我们在转移到 $f_{i,j,0}$ 这个状态时，不能在 $f_{i,j-1,1}/f_{i-1,j,1}=0$ 时转移到这个状态（根据题意）

3. **答案统计** ：根据题意，任意 $f_{i,j,1}$ 都合法，所以我们对它们求出最大值，即是答案；

   *code*

   ```c++
   #include <bits/stdc++.h>//万能头文件
   using namespace std;
   //#define SIZE (1<<20)
   //char in[SIZE],out[SIZE],*p1=in,*p2=in,*p3=out;
   //#define getchar() (p1==p2&&(p2=(p1=in)+fread(in,1,SIZE,stdin),p1==p2)?EOF:*p1++)
   inline long long read(){//快读
   	long long x=0,f=1;char ch=getchar();
   	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
   	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
   	return x*f;
   }
   const int N=2e3+5;
   int n,m;
   string a,b;
   int f[N][N][2];
   int maxn;
   signed main(){
   	//freopen("train.in","r",stdin);
   	//freopen("train.out","w",stdout);
   	n=read(),m=read();
   	cin >> a >> b;
   	a=" "+a;
   	b=" "+b;
   	for(int i=0;i<=n;i++){
   		for(int j=0;j<=m;j++){
   			if(i&&a[i]=='O'&&f[i-1][j][1]>0)f[i][j][0]=max(f[i][j][0],f[i-1][j][1]+1);
   			if(i&&a[i]=='I')f[i][j][1]=max(f[i][j][1],f[i-1][j][0]+1);
   			if(j&&b[j]=='O'&&f[i][j-1][1]>0)f[i][j][0]=max(f[i][j][0],f[i][j-1][1]+1);
   			if(j&&b[j]=='I')f[i][j][1]=max(f[i][j][1],f[i][j-1][0]+1);
   			maxn=max(maxn,f[i][j][1]);
   		}
   	}
   	cout << maxn;
   	return 0;
   }
   ```

---

## 作者：jzjr (赞：1)

# DP做法

## 状态定义

记 $dp[i][j][0/1]$ 来表示 $S$ 出来 $i$ 个，$T$ 出来 $j$ 个，目前结尾为 $0/1$ 的最大长度。

## 状态边界

显然，由于 $|S|=n,|T|=m$，所以 $0\leq i\leq n,0\leq j\leq m$

## 状态转移

显然：

* $dp[i][j][1]=max(dp[i-1][j][0],dp[i][j-1][0])$

* $dp[i][j][0]=max(dp[i-1][j][1],dp[i][j-1][1])$

当然，这并不完整，这需要考虑 $S[i],T[j]$，具体一点的细节为：

## AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[5005][5005][2];
int n,m,dmax;
string a,b; 
int main (){
//	freopen("train.in","r",stdin);
//	freopen("train.out","w",stdout);
	cin>>n>>m;
	cin>>a>>b;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			if(i&&a[n-i]=='O'&&dp[i-1][j][1]>0){
				dp[i][j][0]=max(dp[i][j][0],dp[i-1][j][1]+1);
			}
			if(i&&a[n-i]=='I'){
				dp[i][j][1]=max(dp[i][j][1],dp[i-1][j][0]+1);
			}
			if(j&&b[m-j]=='O'&&dp[i][j-1][1]){
				dp[i][j][0]=max(dp[i][j][0],dp[i][j-1][1]+1);
			}
			if(j&&b[m-j]=='I'){
				dp[i][j][1]=max(dp[i][j][1],dp[i][j-1][0]+1);
			}
			dmax=max(dmax,dp[i][j][1]);
		}
	}
	cout<<dmax<<endl;
	return 0;
}
```

## 其他：

远古的 AT 需要在最后输出 ```'\n'```

---

## 作者：std_qwq (赞：1)

### 思路
凑出 `IOIO...OI`可以当成一个回合游戏：
一开始先从 `I` 开始，然后再 `O`，`I`，`O`，`I..` 依次操作，但是最后一个操作必须是 `I` 。

受此启发，我们可以按照 “当前应该选 `I` 还是 `O` ， 两个栈还有多少元素”进行dp。

### 状态设计
先设两个栈分别为 $a$ 和 $b$ ，下标从底为 $1$ 开始，用 $1$ 和 $0$ 表示 `I` 和 `O` 。


设 $f_{i,j}$ 为 第一个栈有 $i$ 元素，第二个栈有 $j$ 元素，现在要选 `I`，$g_{i,j}$ 为 第一个栈有 $i$ 元素，第二个栈有 $j$ 元素，现在要选 `O`。

答案就是 $\max  {f_{i,j}}$ 。
### 初始化

$f_{1,0}=[a[1]=1],f_{0,1}=[b[1]=1].$

### 转移方程
选择一个 `I` 之后，接下来就要选 `O` ：

$f_{i,j}=\max ((g_{i-1,j}+1) \times [a[i]=1],(g_{i,j-1}+1) \times [b[j]=1])
$

同理，选择一个 `O` 之后，应该选 `I` 。但是注意到我们必须用 `I` 收尾，所以要对应检查 $f_{i-1,j}$ 和 $f_{i,j-1}$ ,如果是 $0$ 就不能用它转移了:

$g_{i,j}=\max (f_{i-1,j} \times [a[i]=0 \space \wedge \space f_{i-1,j}>1],f_{i,j-1} \times [b[j]=0 \space \wedge \space f_{i,j-1}>1])
$
### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2010;
int f[N][N],g[N][N];
int n,m;
int a[N],b[N];
int main(){
    cin>>n>>m;
    for(int i=n;i;i--){
        char c;
        cin>>c;
        a[i]=c=='I';
    }
    for(int i=m;i;i--){
        char c;
        cin>>c;
        b[i]=c=='I';
    }
    //for(int i=1;i<=n;i++)cout<<a[i]<<endl;
    f[1][0]=a[1]==1;
    f[0][1]=b[1]==1;
    for(int i=2;i<=n;i++)f[i][0]=(a[i]==1)*(g[i-1][0]+1),g[i][0]=(a[i]==0&&f[i-1][0])*(f[i-1][0]+1);
    for(int i=2;i<=m;i++)f[0][i]=(b[i]==1)*(g[0][i-1]+1),g[0][i]=(b[i]==0&&f[0][i-1])*(f[0][i-1]+1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            f[i][j]=max((a[i]==1)*(g[i-1][j]+1),(b[j]==1)*(g[i][j-1]+1));
            g[i][j]=max((a[i]==0&&f[i-1][j])*(f[i-1][j]+1),(b[j]==0&&f[i][j-1])*(f[i][j-1]+1));
        }
    int ans=0;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)ans=max(ans,f[i][j]);
    cout<<ans<<endl;
    /*
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++){
            printf("f[%d][%d] = %d, g[%d][%d] = %d\n",i,j,f[i][j],i,j,g[i][j]);
        }
        */
}
```

蒟蒻的第一篇题解，觉得写得好可以点赞支持，若题解有误还请指教qwq

---

## 作者：charleshe (赞：1)

前言：FOI2023 A 班 D5T1，考场上 dp 挂掉了打了个假搜索跑路（

建议评绿。

大意：给定两个大小分别为 $n$ 和 $m$ 的由 `O` 和 `I` 组成的栈（先输入栈顶，后输入栈底），对这个两个栈做以下操作：

1. 从两个栈中各弹出一些字符。

1. 从两个栈中选一个，弹出一个字符。

1. 重复操作 $\text{2}$ $k$ 次，将**在操作 $\text{2}$ 中弹出的字符**按弹出顺序首位顺次拼接形成字符串 $s$。

操作结束后，两个栈可以空，也可以非空。

已知操作得到的 $s$ 形如 `IOIOI...OIOI`，求 $k$ 的最大值。

$1 \leq n \leq 2000$，$1 \leq m \leq 2000$。

思路：显然整个答案满足无后效性，考虑 dp。但是直接动规无从下手，因此考虑两个方面：

1. 操作 $\text{1}$ 表明字符串的建立是基于没被操作 $\text{1}$ 弹掉的字符的，因此这是一个字符串后缀上的问题，可以从后往前 dp。

1. 容易发现处理 `OIOI...OI` 形的字符串比处理 `IOIOI..OIOI` 形的字符串好处理得多（前者是若干个 `OI` 拼起来的结果），因此可以用 dp 求出前者的可能长度，再补上最前面一个 `I`。

基于此，设 $g_{i,j}$ 表示取栈 $a$ 后缀 $\begin{bmatrix}i,n\end{bmatrix}$，栈 $b$ 后缀 $\begin{bmatrix}j,m\end{bmatrix}$ 操作可得 `OIOI...OI` 字符串最大长度，$f_{i,j}$ 表示取栈 $a$ 后缀 $\begin{bmatrix}i,n\end{bmatrix}$，栈 $b$ 后缀 $\begin{bmatrix}j,m\end{bmatrix}$ 操作可得 `IOIOI...OI` 字符串最大长度，则对于 $f$，显然有：

$f_{i,j} \gets g_{i+1,j} + 1$，其中 $a_i$ 为 `I`。

$f_{i,j} \gets g_{i,j+1} + 1$，其中 $b_j$ 为 `I`。

两者取最大值。

而答案显然是 $\max{f_{i,j}}$。于是关键在于求 $g$。

发现一个 `OI` 有四种贡献方式：

1. 均由栈 $a$ 贡献。

1. 均由栈 $b$ 贡献。

1. 栈 $a$ 贡献 `O`，栈 $b$ 贡献 `I`。

1. 栈 $a$ 贡献 `I`，栈 $b$ 贡献 `O`。

因此四种情况都有可能对 $g$ 产生 $2$ 的贡献。将其取最大值即可。

即， $g_{i,j}$ 可能由 $g_{i,j+2}$，$g_{i+2,j}$，$g_{i+1,j+1}$ 转移来。分类讨论并判断即可。

时间复杂度 $O(nm)$，在 $2000$ 的值域下跑得飞快。

代码：

```
#include <iostream>
#define MAXN 2023
using namespace std;
int n,m,ans;
char a[MAXN];
char b[MAXN];
int g[MAXN][MAXN];
int f[MAXN][MAXN];
int main(){
	cin>>n>>m>>a>>b;
	for(int i=n;i>=0;i--){
		for(int j=m;j>=0;j--){
			if((a[i]=='O'&&b[j]=='I')||(a[i]=='I'&&b[j]=='O')) g[i][j]=max(g[i][j],g[i+1][j+1]+2);
			if(a[i]=='O'&&a[i+1]=='I') g[i][j]=max(g[i][j],g[i+2][j]+2);
			if(b[j]=='O'&&b[j+1]=='I') g[i][j]=max(g[i][j],g[i][j+2]+2);
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(a[i]=='I') f[i][j]=max(f[i][j],g[i+1][j]+1);
			if(b[j]=='I') f[i][j]=max(f[i][j],g[i][j+1]+1);
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			ans=max(ans,f[i][j]);
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：jpjpjpjp (赞：0)

首先，很容易想到 $O(nm(n+m))$ 的暴力。枚举两个栈开始弹字符的位置（也就是两个栈完成操作一后的栈顶），然后 dfs 求答案，并记录最大值。


---


考虑正解。观察到 $n$ 和 $m$ 的范围很小。不难想到 dp。

（以下把左边当作栈顶，右边当作栈底，字符 $O$ 为 $0$，$I$ 为 $1$）

$dp_{i,j,0/1}$  代表第一个栈从第 $i$ 位开始，第二个栈从第 $j$ 位开始，第一个弹出的字符为 $0 $ 或 $1$ 的最大长度。接下来就是分类讨论，推转移方程。

若 $s_i$ 为 $1$，`dp[i][j][1]=max(dp[i+1][j][0]+1,dp[i][j][1])`。

意思就是在第一个栈里压入第 $i$ 个元素之前开头为 $0$ 的串的最大长度，在前面加一个 $1$。

若 $s_i$ 为 $0$，`dp[i][j][0]=max(dp[i+1][j][1]+1,dp[i][j][0])`。意思同上。

答案就应该是每个$dp_{i,j,1}$ 取 $\max$。

一些细节：

- 因为两个栈可以为空，所以遍历从 $n+1,m+1$ 开始。同时，不让 $n+1,m+1$ 统计进答案，需要加判断。
- 因为序列的最后一位也必须为 $1$ ，所以在更新 `dp[i][j][0]` 时需判断一下 `s[i+1]` 和 `t[j+1]` 中是否有 $1$。若有，才更新过来。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2005;
int n,m,ans=0;
int s[maxn],t[maxn],d1=0,d2=0;
int dp[maxn][maxn][2];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		char l;cin>>l;
		if(l=='O')s[i]=0,d1++;
		else s[i]=1,d2++;
	}
	for(int i=1;i<=m;i++){
		char l;cin>>l;
		if(l=='O')t[i]=0,d1++;
		else t[i]=1,d2++;
	}
	if(d1==0||d2==0){//特判，实际用处不大
		if(d1==0)cout<<1<<endl;
		else cout<<0<<endl;
		return 0;
	}
	s[n+1]=2;t[m+1]=2;
	for(int i=n+1;i>=1;i--){
		for(int j=m+1;j>=1;j--){
			if(s[i]==0&&i!=n+1&&(s[i+1]==1||t[j]==1))
				dp[i][j][0]=max(dp[i+1][j][1]+1,dp[i][j][0]);
			else if(s[i]==1)
				dp[i][j][1]=max(dp[i+1][j][0]+1,dp[i][j][1]);
            
			if(t[j]==0&&j!=m+1&&(s[i]==1||t[j+1]==1))
				dp[i][j][0]=max(dp[i][j+1][1]+1,dp[i][j][0]);
			else if(t[j]==1)
				dp[i][j][1]=max(dp[i][j+1][0]+1,dp[i][j][1]);
            
			ans=max(ans,dp[i][j][1]);
		}
	}
	cout<<ans<<endl;
	return 0;
}

```

本蒟蒻第一篇在洛谷上的题解，感谢观看。

---

## 作者：Cells (赞：0)

#### 思路

第一眼是结论题，但是后面没有想到，那就确定是 DP 了。

首先有两个栈，又有两种车厢，能够很明显的想到状态，$dp_{i,j,k}$ 表示取第一个栈前 $i$ 个字符，第二个栈取前 $j$ 个字符，构成的序列的最后一个字符是 $k$，其中 $k \in 0/1$，$0$ 表示是 `O`，$1$ 表示是 `I`。那么转移方程就是 应该判断当前字符类型，并与前面不同的字符相匹配。

另外需要注意，有所谓备用车库，但是说白了，在转移的时候就会因为有字符断掉的情况，然后有些状态变成 $0$，解决了这个问题。因为题目并没有要求用完所有车厢，所以我们的答案并不是 $dp_{n,m,1}$，而是需要随时记录。当然，答案也只可能是 $dp_{i,j,1}$，因为要求 `I` 结尾。还有，可能我们只需要一个车库的车厢，所以需要从 $0$ 开始跑 DP，为了防止越界，需要特判是否为 $0$。最后，序列不能以 `O` 开头，所以在上一个转移序列以 $1$ 结尾长度为 $0$ 时，我们不能将长度加 $1$。

**Code**

```c++
//# pragma GCC optimize("Ofast")
# include <bits/stdc++.h>
# define fr front
# define sc scanf
# define pr printf
# define il inline
# define fir first
# define sec second
# define pb push_back
# define eb emplace_back
# define ls(x) (x << 1)
# define rs(x) (x << 1 | 1)
# define lson ls(p), l, mid
# define rson rs(p), mid + 1, r
# define mem(a, b) memset(a, b, sizeof (a))
# define debug(x) cerr << #x << "=" << x << ' '
# define rep(i, a, b) for(int i = a; i <= b; i ++)
# define pre(i, a, b) for(int i = a; i >= b; i --)
using namespace std;

using DB = double;
using LL = long long;
using LDB = long double;
using PII = pair<int, int>;
using ULL = unsigned long long;

const int N = 2e3 + 10;

int n, m, ans;
int dp[N][N][2];

char s1[N], s2[N];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> m;
	
	cin >> s1 + 1 >> s2 + 1;
	
	rep(i, 0, n){
		rep(j, 0, m){
			if(i && s1[i] == 'I') dp[i][j][1] = dp[i - 1][j][0] + 1;//这里dp[i][j][1]没被转移过，可以直接转移，不要取max 
			else if(i) dp[i][j][0] = dp[i - 1][j][1] + (dp[i - 1][j][1] != 0);//为0不加长度 
			if(j && s2[j] == 'I') dp[i][j][1] = max(dp[i][j][1], dp[i][j - 1][0] + 1);//这里需要取max，被转移过了 
			else if(j) dp[i][j][0] = max(dp[i][j][0], dp[i][j - 1][1] + (dp[i][j - 1][1] != 0));//同理 
			
			ans = max(ans, dp[i][j][1]);
		}
	}
	
	cout << ans << "\n";
	
	return 0;
}
```

**感谢你能看到这里！！！**

---

## 作者：RoyWu1207 (赞：0)

写在前面：把题目名称修一下吧 qwq

前置知识：dp，可能会用到？的~~位运算~~

# Solution

先顺着思考问题，但是只用 $i$ 和 $j$ 两位不好设计状态，所以我们需要第三维。

设 $F_{i, j, 0/1}$ 表示选取到第一个栈的第 $i$ 个字符，第二个栈的第 $j$ 个字符，并取出字符 `O` 或 `I` 时的最大长度。

则状态转移方程如下：（其中 $a_i$ 和 $b_j$ 表示两个栈字符的状态，异或作用为取反。）

$$F_{i, j, a_i} \gets F_{i - 1, j, a_i \oplus 1} + 1, F_{i, j, b_j} \gets F_{i, j - 1, b_j \oplus 1} + 1.$$

当然，若 $a_i = b_j$，则需取两者最大值。

同时需要注意从第 $0$ 位开始取。

状态应该还是容易理解的 qwq。

# AC Code

```cpp
#include <bits/stdc++.h>

using namespace std; 

int a[2001], b[2001], n, m, ans;
int dp[2001][2001][2]; 
int main() { 
    cin >> n >> m;
    a[0] = b[0] = 1; 
    getchar();
    for (int i = 1; i <= n; i++) {
        a[i] = getchar() == 'O' ? 0 : 1; 
    } getchar(); 
    for (int i = 1; i <= m; i++) {
        b[i] = getchar() == 'O' ? 0 : 1;
    } getchar();
    for (int i = 0; i <= n; i++) 
        for (int j = 0; j <= m; j++) {
            if (!i && !j) continue; 
            if (j && (dp[i][j - 1][b[j] ^ 1] || b[j])) 
                dp[i][j][b[j]] = dp[i][j - 1][b[j] ^ 1] + 1; 
            if (i && (dp[i - 1][j][a[i] ^ 1] || a[i])) 
                dp[i][j][a[i]] = max(dp[i][j][a[i]], dp[i - 1][j][a[i] ^ 1] + 1);
            ans = max(ans, dp[i][j][1]);
    } cout << ans << endl; 
    return 0;
}
```
# In the End

 _**远古 AT 不写换行见祖宗！**_ 

---

