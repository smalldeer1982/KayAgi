# [ABC369D] Bonus EXP

## 题目描述

高桥君遇到了 $N$ 只怪物，依次遇到每一只怪物，第 $i$ 只怪物的强度为 $A_i$。

高桥君可以选择对每只怪物是放走还是击败。  
高桥君通过以下的方式获得经验值：

- 如果选择放走怪物，获得的经验值为 $0$。
- 如果击败强度为 $X$ 的怪物，他可以获得 $X$ 的经验值。但是，如果这是他第偶数次击败怪物（即第 $2$ 次、第 $4$ 次、……），他将额外获得 $X$ 的经验值。

请计算高桥君通过击败怪物可以获得的最大总经验值。

## 说明/提示

### 约束条件

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq A_i \leq 10^9$
- 输入的所有数值均为整数

### 样例解释 1

在击败第 1、2、3、5 只怪物并放走第 4 只怪物时，高桥君可以按如下方式获得经验值： 
- 击败强度为 $A_1=1$ 的怪物，获得 $1$ 的经验值。
- 击败强度为 $A_2=5$ 的怪物，获得 $5$ 的经验值。这是高桥君第 2 次击败怪物，因此额外获得 $5$ 的经验值。
- 击败强度为 $A_3=3$ 的怪物，获得 $3$ 的经验值。
- 放走第 4 只怪物，高桥君不获得经验值。
- 击败强度为 $A_5=7$ 的怪物，获得 $7$ 的经验值。这是高桥君第 4 次击败怪物，因此额外获得 $7$ 的经验值。

因此，总共获得的经验值为 $1+(5+5)+3+0+(7+7)=28$。  
由于无论如何行动，总经验值都不会超过 $28$，所以输出 $28$。

请注意，如果击败所有怪物，获得的经验值为 $1+(5+5)+3+(2+2)+7=25$。

### 样例解释 2

请注意，答案可能会超过 32 位整数型的范围。

## 样例 #1

### 输入

```
5
1 5 3 2 7```

### 输出

```
28```

## 样例 #2

### 输入

```
2
1000000000 1000000000```

### 输出

```
3000000000```

# 题解

## 作者：Alcl000000 (赞：5)

定义状态 $f_{i,0}$ 表示到第 $i$ 个为止，已经选了奇数个数的最大价值，$f_{i,1}$ 表示到第 $i$ 个为止，已经选了偶数个数的最大价值。

对于每个位置可以考虑选或不选，所以有以下转移：

$f_{i,0}=\max(f_{i-1,0},f_{i-1,1}+A_i)$

$f_{i,1}=\max(f_{i-1,1},f_{i-1,0}+2\times A_i)$

本题就做完了。

code：

```cpp
#include<bits/stdc++.h>
#define ios ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
long long f[200005][2],a[200005],n;
int main(){
	cin>>n;
	f[0][0]=-1e15;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		f[i][0]=max(f[i-1][0],f[i-1][1]+a[i]);
		f[i][1]=max(f[i-1][1],f[i-1][0]+2*a[i]);
	}
	cout<<max(f[n][0],f[n][1]);
	return 0;
}
```

---

## 作者：sakura_21 (赞：2)

## 题目大意
有 $n$ 只怪物，按顺序遇到每只怪物。对于第 $i$ 只怪物，打败的总怪物数（不连同它本身）为 $x$ 时,若 $x+1$ 为奇数，则打败它增加的经验值为 $a_i$，若 $x+1$ 为偶数，则打败它增加的经验值为 $2 \times a_i$，放过它增加的经验值为 $0$。求从 $N$ 个怪物身上获得的经验值上限。

## 算法分析
求n个里面的部分和，对于每一个怪物都有选和不选两种方案，~~这不就是个 01 背包嘛！！！~~

诶不对，怎么还要分奇偶？？？

隆重推出一个绝妙的 dp ：分情况考虑。

再看题面：我们可以发现，对于每一只怪物，都可以分如下三种情况考虑。

1. 不选该种怪物。
1. 选择该怪物为第偶数只。
1. 选择该怪物为第奇数只。

同时还可以发现，第一种情况的最大经验可以由选择上一种后的奇数只和偶数只进行转移，因此dp数组只需要考虑两种情况：选择该种怪物为奇数只和选择该种怪物为偶数只。

然后就开始愉快的写 dp 方程啦！（这里我们以 $0$ 为该怪物是第偶数只的情况，$1$ 为该怪物是第奇数只情况）时间复杂度为 $Θ(n)$。

```cpp
dp[0][i]=max(dp[0][i-1],dp[1][i-1]+a[i]*2);
dp[1][i]=max(dp[1][i-1],dp[0][i-1]+a[i]);//悄咪咪提一句：二维数组维度小的放在前面可以省一点点时间哦！
```
再考虑一下，第一只怪物怎么可能是第偶数只被选呢 QAQ ，然后我们的状态边界就成功入选了！（记得更新 $1$ 后循环需要从 $2$ 开始）

```cpp
dp[1][1]=a[1];
```
接下来是愉快的代码环节（相信各位帅哥美女也不用看了吧~）

## code

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

const int N=2e5+100;

int n;

int a[N];
int dp[2][N];//0偶1奇 

signed main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	
	dp[1][1]=a[1];//边界条件
	
	for (int i=2;i<=n;i++)//更新完1后需要从2开始，否则1会重复更新
	{
		dp[0][i]=max(dp[0][i-1],dp[1][i-1]+a[i]*2);
//同时更新不选的情况
		dp[1][i]=max(dp[1][i-1],dp[0][i-1]+a[i]);
	}
	
	cout<<max(dp[0][n],dp[1][n]);//比较n为奇数只和偶数只被选的大小
	return 0;
}
```
## 完结撒花！！！

---

## 作者：yegengghost (赞：2)

省流：小日本核废水喝多了题都唐化了。

我们看完题面后，提取下关键词：**放走后的代价为 $0$，击败后代价为题面描述的代价**。

这看完后，一个 dp 不就暴露出来了吗？

考虑到代价的奇偶性，我们定义 $dp_{i,flag}$ 为第 $i$ 个是奇数或偶数的贵物被击败后的最大代价和为多少。$flag$ 为 $0$ 时是偶数，反之则为奇数。

对于该题，我们的边界值为：

$$dp_{0,1}=-\infty$$

$$dp_{1,0}=dp_{0,1}+2a_1$$

$$dp_{1,1}=dp_{0,0}+a_1$$

之后我们的转移方程即为：

$$dp_{i,0}=\max(dp_{i-1,1}+2a_i,dp_{i-2,1}+2a_i)$$

$$dp_{i,1}=\max(dp_{i-1,0}+a_i,dp_{i-2,0}+a_i)$$

最后输出 $\max(dp_{n,0},dp_{n,1})$ 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
const int mod=1;
int ksm(int x,int k)
{
	int ans=1,base=x;
	while(k)
	{
		if(k&1) ans=1ll*ans*base%mod;
		base=1ll*base*base%mod; k>>=1;
	}
	return ans;
}
int read()
{
	int f=1,x=0;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return f*x;
}
int n;
int a[N];
int dp[N][2];
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	dp[0][1]=-LONG_LONG_MAX;
	dp[1][0]=dp[0][1]+a[1]*2;
	dp[1][1]=dp[0][0]+a[1];
	for(int i=2;i<=n;i++)
	{
		dp[i][0]=max(dp[i-1][1]+a[i]*2,dp[i-2][1]+a[i]*2);
		dp[i][1]=max(dp[i-1][0]+a[i],dp[i-2][0]+a[i]);
	}
	cout<<max(dp[n][0],dp[n][1])<<'\n';
	return 0;
}
```

---

## 作者：ma_niu_bi (赞：2)

### D-Bonus EXP

#### 题意

给出一个长度为 $n$ 的序列 $A$，每次有两种选择。

1. 将得分增加 $A_i$，若这是第偶数次执行这个操作，将得分额外增加 $A_i$。
2. 什么也不做。

求最大得分。

#### 思路

定义 $dp_{i,0/1}$ 表示前 $i$ 个数，做了偶数或奇数次操作 $1$ 的最大得分。

初始状态 $dp_{0,0}=0$。

$dp_{i,0}$ 转移方程：

$$
dp_{i,0}=\max(dp_{i-1,0},dp_{i-1,1}+2\times a_i)
$$

$dp_{i,1}$ 转移方程：

$$
dp_{i,1}=\max(dp_{i-1,1},dp_{i-1,0}+a_i)
$$

时间复杂度：$O(n)$。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e5 + 5;
int n, a[N];
ll dp[N][2];
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    memset(dp, -0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i ++) {
        dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + a[i]);
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + 2 * a[i]); 
    }
    cout << max(dp[n][0], dp[n][1]) << "\n";
}
int main() {
    int T = 1;
    // cin >> T;
    while (T --) 
        solve();
    return 0;
}
```

---

## 作者：LuukLuuk (赞：1)

# 题解：AT_abc369_d [ABC369D] Bonus EXP
### 题目大意
给定一个序列 $a_1,\dots,a_n$。对于 $a_i$，你可以选择拿或不拿，如果取了且为第偶数个取了的，贡献翻倍。求最大贡献。
### 思路
对于 $a_i$，只有取它时它是第偶数个取的才会影响它的贡献，所以我们考虑 dp。记录 $a_i$ 之前取了奇数个的最大贡献 $mx0$，和取了偶数个的 $mx1$。

转移时枚举 $a_i$ 的两种情况，为第奇数个还是第偶数个，奇数时从 $mx1$ 转移，反之从 $mx0$ 转移并将当前数的贡献乘 $2$。

另外，初始时将 $mx1$ 赋为无穷小，因为第一个数不可能是第偶数个。
### 代码
```cpp

#include <algorithm>
#include <cstdio>
using namespace std;

#define int long long

int a[200010];
int now0, now1;
int mx0, mx1;
int n;

signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
	}
	mx1 = 0;
	mx0 = -2e9;
	for (int i = 1; i <= n; ++i) {
		now0 = mx1 + a[i];
		now1 = mx0 + 2 * a[i];
		mx0 = max(now0, mx0);
		mx1 = max(now1, mx1);
	}
	printf ("%lld", max(mx0, mx1));
	return 0;
}

```

---

## 作者：chinazhanghaoxun (赞：1)

## 题意

有 $N$ 个怪物，打败第 $i$ 个怪物的收益为 $a_i$，如果当前是第偶数次攻击，那么收益翻倍，求出最大的收益。
## 分析

第一眼看到这种对于第 $i$ 只怪物可以有两种选择的问题，就应该想到可以使用 dp 解决。

我们对 dp 数组 $f$ 的定义为 $f_{i,0}$ 以及 $f_{i,1}$ 分别表示攻击第 $i$ 只怪物后是奇数次或偶数次。这道题的 dp 转移式也非常朴素，就是判断攻不攻击，转移式如下：
$$
f_{i,x}=\max(f_{i-1,x},f_{i-1,x\oplus1}+a_i\times(x\oplus1+1))
$$
这当中的 $x$ 只可能是 0 或 1，因为攻击怪物后只可能是奇数或偶数。而值得注意的是，第一次攻击不可能是偶数，所以 $f_{0,1} = -\infty$，因为这种情况不可能出现。
## 代码+注释

一定要记得开 long long！
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e7+10;
int a[N],f[N][2],n;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
    f[0][1]=INT_MIN;//不可能存在这一种情况 
	for(int i=1;i<=n;i++)
	    for(int j=0;j<2;j++)
	    	//进行dp转移 
	        f[i][j]=max(f[i-1][j],f[i-1][j^1]+a[i]*((j^1)+1)); 
	cout<<max(f[n][0],f[n][1]);//结束时取攻击偶数次与奇数次所获得经验的较大值 
	return 0;
} 
```

---

## 作者：Ivan422 (赞：1)

题目大意：给你 $n$ 个妖怪，第偶数次击败可以获得双倍经验，其他击败可以获得单倍经验，放走不获得经验，也不计入击败，求最大获得经验数。

考虑动态规划。定义 $f_{i,j}$ 为第 $i$ 次击败考虑完前 $j$ 个怪物的答案。我们会发现 $i$ 可以变为只存奇偶次击败，$j$ 可以直接压缩，但是为了好理解这里只优化 $i$ 这一维。

转移方程：$f_{0,j}$ 就在不打这个妖怪 $f_{0,j}$ 与打这妖怪 $f_{1,j-1}+2\times a_j$ 取最大值，注意打的时候必须之前打过妖怪了。$f_{1,j}$ 也是不打 $f_{1,j-1}$ 与打 $f_{0,j-1}+a_j$ 中去最大值，不用判断。

答案：这个结束时是奇数次打 $f_{1,n}$ 或偶数次打 $f_{0,n}$，取最大值。

代码：[赛时提交记录](https://atcoder.jp/contests/abc369/submissions/57299811)。

---

## 作者：caochenkai (赞：1)

# [[ABC369D] Bonus EXP](https://www.luogu.com.cn/problem/AT_abc369_d)
## 题意
有 $N$ 个怪物，打败第 $i$ 个怪物能获得 $a_i$ 的经验，如果第 $i$ 个怪物是第偶数次打败的，经验乘二，求最大经验。
## 思路
看到题目第一眼肯定是爆搜，但 $N$ 是 $2 \times 10^5$，暴力无法通过。

经思考发现可以用动态规划做。先设状态，我们设 $dp_{i,1}$ 为当第 $i$ 个数作为第奇数个去选择的最大价值，反之设 $dp_{i,2}$ 为当第 $i$ 个数作为第偶数个去选的最大价值。

再推方程。经过思考，当前这个数作为奇数去选的最大价值是由上一个数作为偶数的最大价值加上当前数的价值与上一个数作为奇数选的最大价值的最大值，简化一下，缩减为下面这个式子：  
$$dp_{i,1}= \max(dp_{i-1,2}+a_i,dp_{i-1,1})$$
同时偶数奕然：
$$dp_{i,2}= \max(dp_{i-1,1}+a_i \times 2,dp_{i-1,2})$$
初始化时把 $dp_{0,1}$ 初始化为负无穷，$dp_{0,2}$ 初始化为 $0$，因为第一个数只能作为奇数选。
## AC代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define FAST ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
int n,a[200005],dp[200005][5];
signed main()
{
	FAST
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	dp[0][1]=-1e18,dp[0][2]=0;
	for(int i=1;i<=n;i++)
	{
		dp[i][1]=max(dp[i-1][1],dp[i-1][2]+a[i]);
		dp[i][2]=max(dp[i-1][1]+a[i]*2,dp[i-1][2]);
	}
	cout<<max(dp[n][1],dp[n][2]);
	return 0;
}
```

---

## 作者：__AFO__ (赞：0)

# 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc369_d)

## 题目大意

有 $N$ 只怪兽，你有三种操作方式。

1. 放过他获得 $0$ 经验值。
2. 击败他获得 $a_i$ 经验值。
3. 如果这只怪兽是第偶数个被击败的，你可以多获得 $a_i$ 经验值。

## 题目分析
这道题这三种操作我们可以先想到搜索，但是 $N$ 的范围很大，平常的搜索肯定不行，估计是记忆化搜索，这样我们就可以得到动态规划这条思路。

我们开一个二维数组，第一位指的是达到了第几个怪兽，第二位指的是这个怪兽是第奇数个还是偶数个，于是我们可以推出状态转移方程。

状态转移方程：

$$f_{i,1}=\begin{cases}\max(f_{i-1,0}+2\times a_i,f_{i-1,1})&i\ne 1\\-\infty&i=1\end{cases}$$
$$f_{i,0}=\max(f_{i-1,1}+a_i,f_{i-1,0})$$	

因为面对第一个怪兽时，只有两种可能，要么不打，要打这个怪兽也一定是奇数，所以就不用考虑第一个式子的情况了。

## 代码详解


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[200005],f[200005][2];
int main(){
    cin>>n;
    for(long long i=1;i<=n;i++){
    	cin>>a[i];
	}
	for(long long i=1;i<=n;i++){
		if(i!=1) f[i][1]=max(f[i-1][0]+2*a[i],f[i-1][1]);//状态转移 
	    f[i][0]=max(f[i-1][1]+a[i],f[i-1][0]);	
	}
	cout<<max(f[n][0],f[n][1]);
	return 0;
} 
```

---

## 作者：T_TLucas_Yin (赞：0)

简单的线性递推题。简单的此类题目常见要素是“一个序列，每个位置有几种状态，求最优解”，$n$ 的范围较大，且每一个位置的每一种状态都可由上一个位置的状态转移而来（其实是简单的 DP）。最好掌握方法。

对于每一只怪，我们有打死和放走两种操作。所以每一个数就对应选取和不选两种状态。但由于作为第奇数个怪物被打死和作为第偶数个怪物被打死获得的得分是不一样的，所以实际上两种状态要分别分为作为第奇数次发生和第偶数次发生两种情况，共四种状态。

若一个怪是“第奇数个被打死的怪物”，则上一个怪一定是“第偶数个被打死的怪物”或“本来是第奇数个但被放走的怪物”，取两种情况的最大值加上当前位置的得分为最优解。

若一个怪是“第偶数个被打死的怪物”，则上一个怪一定是“第奇数个被打死的怪物”或“本来是第偶数个但被放走的怪物”，取两种情况的最大值加上当前位置**得分的两倍**为最优解。

若一个怪是“本来是第奇数个但被放走的怪物”（$f_{i,2}$），则上一个怪一定是“本来是第奇数个但被放走的怪物”或“第偶数个被打死的怪物”，取两种情况的最大值为最优解。

若一个怪是“本来是第偶数个但被放走的怪物”，原理同上。

转移方程由上形式化可得。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[1000005],f[1000005][4];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	f[1][0]=f[1][2]=f[1][3]=0,f[1][1]=a[1];
	for(int i=2;i<=n;i++){
		f[i][0]=max(f[i-1][1]+a[i]*2,f[i-1][2]+a[i]*2);
		f[i][1]=max(f[i-1][0]+a[i],f[i-1][3]+a[i]);
		f[i][2]=max(f[i-1][1],f[i-1][2]);
		f[i][3]=max(f[i-1][0],f[i-1][3]);
	}
	cout<<max(max(f[n][0],f[n][1]),max(f[n][2],f[n][3]));
	return 0;
}
```

---

## 作者：__Allen_123__ (赞：0)

> 有 $n$ 个数，你可以按顺序选择其中的几个。选择的数组成的序列中，第奇数项会对答案作出一倍于自身的贡献，第偶数项会对答案作出两倍于自身的贡献。求最大答案。

考虑 dp。

设 $dp_{i,0}$ 表示考虑了前 $i$ 个数，选择了偶数个数的最优答案，$dp_{i,1}$ 表示考虑了前 $i$ 个数，选择了奇数个数的最优答案。

如果这个数不选，那么 $dp_{i,0}=dp_{i-1.0}$，$dp_{i,1}=dp_{i-1,1}$；如果这个数被选了，那么 $dp_{i,0}=dp_{i-1,1}+2a_i$（这个数作出了两倍的贡献），$dp_{i,1}=dp_{i-1,0}+a_i$（这个数作出了一倍的贡献）。

初始状态为 $dp_{1,0}=0,dp_{1,1}=a_1$。以此方式 dp 即可。

[AC 记录](https://atcoder.jp/contests/abc369/submissions/57286245)。

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
有 $n$ 个怪物，每个怪物有自己的权值，杀死第奇数个可以获得一倍权值的分数，杀死第偶数个可以获得两倍权值的分数，问最多获得多大的分数。
## 大体思路
考虑一个非常普通的 DP。

### 状态设置
$f_{i,0/1}$ 代表当前是第 $i$ 位，是第偶数个或奇数个怪物。
### 状态转移
由于第一个只能是第一个或不选，不能是第偶数个，所以我们特判一下他只能有 $f_{i,1}$ 的转移。

其他的转移方程：
```cpp
f[i][1]=max(f[i-1][1],f[i-1][0]+a[i]);
f[i][0]=max(f[i-1][0],f[i-1][1]+(a[i]*2));
```
### 答案输出
最后只要输出 `max(f[n][1],f[n][0])` 即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void write(long long x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9){
		write(x/10);
	}
	putchar(x%10+'0');
	return ;
}
long long a[200005];
long long f[200005][2];
int main(){
	int n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	for(int i=1;i<=n;i++){
		if(i==1){
			f[i][1]=max(f[i-1][1],f[i-1][0]+a[i]);
			continue ;
		}
		f[i][1]=max(f[i-1][1],f[i-1][0]+a[i]);
		f[i][0]=max(f[i-1][0],f[i-1][1]+(a[i]*2));
	}
	write(max(f[n][1],f[n][0]));
	return 0; 
}
```

---

## 作者：Genius_Star (赞：0)

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18391497)

### 题意：

有 $n$ 个物品依次从你身边经过，第 $i$ 个物品的贡献为 $a_i$。

若你选择的第 $j$ 个物品是 $i$：

- 当 $j$ 为偶数时：收益为 $a_i \times 2$。

- 否则收益为 $a_i$。

问最大收益。

$1 \le n \times 10^5$。

### 思路：

考虑动态规划算法。

注意到当前位置的取值只跟当前取的个数的奇偶性有关，则定义 $dp_{i,0/1}$ 表示对于前 $i$ 个物品取的物品个数对 $2$ 取余的结果为 $0/1$ 的最大权值，则状态转移方程为：

$$dp_{i,0} = \max(dp_{i-1,1} + 2a_i,dp_{i-1,0})$$

$$dp_{i,1} = \max(dp_{i-1,1},dp_{i-1,0} + a_i)$$

最后的答案是 $\max(dp_{n,0},dp_{n,1})$，时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
#define For(i,l,r) for(int i=l;i<=r;i++)
#define _For(i,l,r) for(int i=r;i>=l;i--)
using namespace std;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=2e5+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n;
ll a[N],dp[N][2];
int main(){
	n=read();
	For(i,1,n)
	  a[i]=read();
	dp[1][1]=a[1],dp[1][0]=0;
	For(i,2,n){
		dp[i][0]=max(dp[i-1][1]+a[i]*2,dp[i-1][0]);
		dp[i][1]=max(dp[i-1][0]+a[i],dp[i-1][1]);
	}
	write(max(dp[n][0],dp[n][1]));
	return 0;
}
```

---

## 作者：_QWQ__QWQ_ (赞：0)

## 题目大意：

有 $n$ 个怪物，每个怪物有一个战力值 $a_i$ ，你可以选择击败他或放走他，放走他没有经验值，击败他可以获得 $a_i$ 的经验值，如果击败的数量是偶数，则还可以获得 $a_i$ 的经验值，求最后能获得多少经验值。


## 分析

一眼 DP，按套路做。

### 定义状态：

$dp_{i,0/1}$：前 $i$ 只怪物，选了奇数个怪物的最大经验值或选了偶数个怪物的最大经验值。

### 答案：

$\max(dp_{n,0},dp_{n,1})$

### 状态转移方程：

$dp_{i,0}$

不选就是继承 $dp{i-1,0}$，选了就是在前 $i-1$ 个中选了偶数个（因为选完这个变奇数了）的最大价值加上 $a_i$，即 $dp_{i-1,1}+a_i$

最后就是 $dp_{i,0}=\max(dp_{i-1,0},dp_{i-1,1}+a_i)$

$dp_{i,1}$

不选就是继承 $dp{i-1,1}$，选了就是在前 $i-1$ 个中选了奇数个（因为选完这个变偶数了）的最大价值加上 $2\times a_i$，即 $dp_{i-1,1}+2\times a_i$

最后就是 $dp_{i,1}=\max(dp_{i-1,1},dp_{i-1,0}+2\times a_i)$

### 边界条件：

由于前 $0$ 个不能选奇数个，所以 $dp_{0,0}=-\infty$


## AC code

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
const int maxn=1e6+5;
int n,a[maxn],dp[maxn][2];
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	dp[0][0]=-1e18;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		dp[i][0]=max(dp[i-1][0],dp[i-1][1]+a[i]);
		dp[i][1]=max(dp[i-1][1],dp[i-1][0]+2*a[i]);
	}
	cout<<max(dp[n][0],dp[n][1]);
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc369_d)

## 思路

线性动态规划。

为了方便理解，我们用四个 dp 数组分别表示四种状态。

$dp_{i,0}$ 表示这个不选，而且上次选的是偶数，下次该奇数了。

$dp_{i,1}$ 表示这个选，而且上次选的是偶数，这次该奇数了。

$dp_{i,2}$ 表示这个选，而且上次选的是奇数，这次该偶数了。

$dp_{i,3}$ 表示这个不选，而且上次选的是奇数，下次该偶数了。

由此得知，$dp_{i,j}$ 的转移方程为：

$$dp_{i,j}=
\begin{equation}
\left\{
\begin{array}{lr}
\max(dp_{i-1,0},dp_{i-1,2}) & (j=0)\\
\max(dp_{i-1,0},dp_{i-1,2})+a_i & (j=1)\\
\max(dp_{i-1,1},dp_{i-1,3})+2\times a_i & (j=2)\\
\max(dp_{i-1,1},dp_{i-1,3}) & (j=3)\\
\end{array}
\right.
\nonumber
\end{equation}
$$

但是此时还有一个小问题，就是当 $j=2$ 的时候，如果 $dp_{i-1,1}$ 或 $dp_{i-1,3}$ 没有值的时候，$dp_{i,j}$ **不应进行对应转移**，所以要特判。

- 答案可能不在 $32$ 位整型范围内，记得开 long long。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
long long n,a[N],dp[N][4];
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1;i<=n;++i){
		dp[i][0]=max(dp[i-1][0],dp[i-1][2]);
		dp[i][1]=max(dp[i-1][0],dp[i-1][2])+a[i];
		if(dp[i-1][1]&&dp[i-1][3])dp[i][2]=max(dp[i-1][1],dp[i-1][3])+a[i]*2;//特判。
		else if(dp[i-1][1])dp[i][2]=dp[i-1][1]+a[i]*2;
		else if(dp[i-1][3])dp[i][2]=dp[i-1][3]+a[i]*2;
		dp[i][3]=max(dp[i-1][1],dp[i-1][3]);
	}
	cout<<max({dp[n][0],dp[n][1],dp[n][2],dp[n][3]});
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/175592038)

---

## 作者：zjj2024 (赞：0)

### 思路

考虑动态规划。

设 $f_{i,0}$ 表示第 $i$ 只怪物不打的最大价值，$f_{i,1}$ 表示第 $i$ 只怪物在第奇数次打的最大价值，$f_{i,2}$ 表示第 $i$ 只怪物在第偶数次打的最大价值。

则有：

$$
f_{i,0}=\max(f_{i-1,0},f_{i-1,1},f_{i-1,2})
$$

$$
f_{i,1}=\max(f_{i-1,0},f_{i-1,2})+A_i
$$

$$
f_{i,2}=\max(f_{i-1,0},f_{i-1,1})+2\times A_i
$$

最后的答案则为 $\max(f_{n,0},f_{n,1},f_{n,2})$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
typedef long long ll;
ll f[N][3];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll n,x;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		f[i][0]=max(f[i-1][0],max(f[i-1][1],f[i-1][2]));//动态规划
		if(i==1)//当i=1时，不存在f[i][2]
		{
			f[i][1]=x;
			continue;
		}
		f[i][1]=max(f[i-1][0],f[i-1][2])+x;
		f[i][2]=max(f[i-1][0],f[i-1][1])+2*x;
	}
	cout<<max(f[n][0],max(f[n][1],f[n][2]))<<'\n';//输出答案
	return 0;
}
```

---

## 作者：gavinliu266 (赞：0)

# 思路
定义 $\operatorname{dp}(i, k)$ 表示前 $i$ 个怪兽，打了 $j(j \equiv k \pmod{2})$ 个时的最大收益。

则可以得出状态转移方程。
$$
\operatorname{dp}(i, 0) = \max(\operatorname{dp}(i - 1, 0), \operatorname{dp}(i - 1, 1) + 2a_i)\\
\operatorname{dp}(i, 1) = \max(\operatorname{dp}(i - 1, 1), \operatorname{dp}(i - 1, 0) + a_i)
$$

边界：$\operatorname{dp}(1, 1) = a_1$，$\operatorname{dp}(1, 0) = 0$。

相当于对于选与不选两种情况分别取最大值。

答案就是 $\operatorname{dp}$ 每一项的最大值。

# 代码实现
代码照着敲就可以了。
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5;
int n;
int a[N];
long long dp[N][2], ans;
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    ans = dp[1][1] = a[1];
    for(int i = 2; i <= n; ++i) {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + a[i] * 2);
        dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + a[i]);
        ans = max(ans, max(dp[i][1], dp[i][0]));
    }
    printf("%lld\n", ans);
}
```

---

## 作者：Lele_Programmer (赞：0)

# AT_abc369_d 题解

## 思路

DP，设 $f_{i,j}$ 为到了第 $i$ 只怪兽（第 $i$ 只怪兽不一定要打），目前已经打了 $j$ 的怪兽，这里 $j=0$ 则表示打了偶数个，$j=1$ 表示打了奇数个。

考虑状态转移，对于 $f_{i,0}$，如果第 $i$ 个不打，则 $f_{i,0} = f_{i-1,0}$，如果第 $i$ 个打了，则 $f_{i,0} = f_{i-1,1} + a_i \times 2$。对于 $f_{i,1}$，如果第 $i$ 个不打，则 $f_{i,1} = f_{i-1,1}$，如果第 $i$ 个打了，则 $f_{i,1} = f_{i-1,0}+a_i$。

整理一下，则得到以下两个式子：

$$
f_{i,0} = \max(f_{i-1,0},f_{i-1,1}+a_i \times 2) \\
f_{i,1} = \max(f_{i-1,1},f_{i-1,0}+a_i)
$$

再把两个式子合并一下：

$$
f_{i,j} = \max(f_{i-1,j},f_{i-1,j \oplus 1}+a_i \times ([j = 0] + 1)) \space (j \in [0,1])
$$

初始化 $f$ 数组，$f_{0,0} = 0$，其余 $f_{i.j} = -\infty$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define rint register int
#define LL long long

const int N=200005;
const int inf=9e18;

int n;
int arr[N];
int f[N][2];

signed main() {
    scanf("%lld",&n);
    _rep(i,1,n) scanf("%lld",&arr[i]);
    _rep(i,1,n) _rep(j,0,1) f[i][j]=-inf;
    f[0][1]=-inf;
    _rep(i,1,n) {
        _rep(j,0,1) {
            f[i][j]=max(f[i-1][j],f[i-1][j^1]+arr[i]*(j==1?1:2));
        }
    }
    printf("%lld",max(f[n][0],f[n][1]));
    return 0;
}
```

---

## 作者：under_the_time (赞：0)

## 题意

> 给定长度为 $n$ 的数列 $a$，要求选出一个 $a$ 的**子序列** $b$，对于所有 $b_{2k}$（其中 $k\in \N^*$）它的值将翻倍，求 $\sum b_i$​ 的最大值。
>
> $n\le 2\times 10^5$，$a_i\le 10^9$。

## 解法

考虑 dp。令 $f(i,0/1)$ 表示考虑**完** $a_i$ 且已经选了偶数个 / 奇数个元素值，那么有
$$
\begin{cases}f(i,0)=\max\{f(i-1,0),f(i-1,1)+2a_i\}\\f(i,1)=\max\{f(i-1,1),f(i-1,0)+a_i\}\end{cases}
$$
初始有 $f(1,0)=0,f(1,1)=a_1$，最终答案取 $\max\{f(n,0),f(n,1)\}$​ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
#define ll long long
int a[maxn], n; ll f[maxn][2];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	f[1][0] = 0, f[1][1] = a[1];
	for (int i = 2; i <= n; i ++)
		f[i][0] = max(f[i - 1][0], f[i - 1][1] + (a[i] << 1ll)),
		f[i][1] = max(f[i - 1][1], f[i - 1][0] + a[i]);
	printf("%lld\n", max(f[n][0], f[n][1]));
	return 0;
}
```

---

## 作者：2011FYCCCTA (赞：0)

[题目](https://www.luogu.com.cn/problem/AT_abc369_d)

---
### 思路

很明显的 dp，定义 $f_{i,0}$ 表示到第 $i$ 只怪兽时，共打了偶数只怪兽的最大经验值，$f_{i,1}$ 表示到第 $i$ 只怪兽时，共打了奇数只怪兽的最大经验值。

转移并不复杂：对于第 $i$ 只怪兽，如果当前共打了偶数只，且如果不打此怪兽，那么最大经验值为 $f_{i-1,0}$，否则，为 $f_{i-1,1}+2a_i$，两者取最大值。

否则，如果当前共打了奇数只，且如果不打此怪兽，那么最大经验值为 $f_{i-1,1}$，否则，为 $f_{i-1,0}+a_i$，两者取最大值。

最终的结果为：$\max(f_{n,0},f_{n,1})$。

边界条件：$f_{1,0}=0$，$f_{1,1}=a_1$。

---
### [赛后代码](https://atcoder.jp/contests/abc369/submissions/57345685)/[赛时代码](https://atcoder.jp/contests/abc369/submissions/57306688)

两者区别是赛时代码我的状态多定义了一维表示是否选第 $i$ 只怪兽，实际上没必要。

---

## 作者：maokaiyu (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc369_d)
## 题面
你要去讨伐魔王，但是有 $N$ 只怪兽阻拦了你。你可以选择放开怪兽，但什么也不会得到；也可以消灭这只怪兽，并获得 $a_i$ 点经验值，如果这是第偶数次打败怪物，你就能**额外**获得 $a_i$ 点经验。你想最大化经验值。
## 思路
你本能地选择了 dp。设 $dp_{i,1/0}$ 表示第 $i$ 个怪兽时被奇数/偶数次打败时最大的收益。你想的转移是 $dp_{i,j}$ 从 $dp_{k,j\oplus1}$ 处转移过来（$k<i$），但这样无法通过 $N=2\times10^5$ 的数据，你想到用**树状数组**分别维护 dp 奇数/偶数次前缀的最大值，这样算法就成了 $O(N\log N)$，可以通过。
## 做法
用树状数组维护 dp 数组。
## AC Code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be begin()
#define en end()
using namespace std;
typedef long long LL;
typedef int I;
const I N = 2e5 + 10;
const LL inf = 1LL << 60;
I n;
LL a[N],dp[N][2];
struct treea{//树状数组 
    LL a[N];
    void init(){
        memset(a,128,sizeof(a));//都设为负无穷 
    }
    void add(LL x,I pos){
        for(;pos <= n;pos += (pos & (-pos))){
            a[pos] = max(a[pos],x);
        }
    }
    LL query(I x){
        LL ans = -inf;
        for(;x;x -= (x & (-x))){
            ans = max(ans,a[x]);
        }
        return ans;
    }
}c,c2;
//c 维护偶数最大前缀，c2 维护奇数 
I main(){
	scanf("%d",&n);
	for(I i = 1;i <= n;i++){
		scanf("%lld",&a[i]);
	}
	memset(dp,128,sizeof(dp));
	c.init(),c2.init();
	c.add(0,1);//初始设值 
	for(I i = 1;i <= n;i++){
		LL t1 = c2.query(i),t2 = c.query(i);//奇数从偶数转，偶数从奇数转 
		dp[i][0] = t1 + a[i] * 2LL;
		dp[i][1] = t2 + a[i];
		c.add(dp[i][0],i + 1),c2.add(dp[i][1],i + 1);
		//printf("%lld %lld\n",t1,t2);
	}
	printf("%lld\n",max(dp[n][0],dp[n][1]));
	return 0;
}
```
## 致谢
感谢 @__Allen_123__ 提供的写作思路。

---

## 作者：zzhbpyy (赞：0)

### [Bonus EXP](https://atcoder.jp/contests/abc369/tasks/abc369_d)

## 思路

考虑 dp，$dp_{i,0}$ 表示不选取第 $i$ 个怪物，前 $i$ 个怪物能得到的最大经验值，$dp_{i,1}$ 表示选择第 $i$ 只怪物的最大经验值。

容易得到转移方程：

$$dp_{i,0}=\max\{dp_{i,0},dp_{j,1}+A_i\}$$

$$dp_{i,1}=\max\{dp_{i,1},dp_{j,0}+2\times A_i\}$$

直接转移是 $O(N^2)$ 的，但我们可以观察得到不可能隔两个都不选，因为同时选上两个怪不影响后面选择的奇偶性，即无后效性，所以 $dp_{i,0}$ 和 $dp_{i,1}$ 都可以直接从 $i-1$ 和 $i-2$ 转移过来，复杂度 $O(N)$。

## [Code](https://atcoder.jp/contests/abc369/submissions/57343881)

---

## 作者：liruixiong0101 (赞：0)

# D - Bonus EXP
## 题意：
给定一个长度为 $n$（$1\le n\le 2\times 10^5$）的序列 $a$，定义 $\operatorname{f}(b)=\sum_{i=1}^{\lvert b\rvert} b_i\times[(i-1)\bmod 2+1]$。求 $a$ 的所有子序列 $b$，$\operatorname{f}(b)$ 的最大值。

## 思路：
选取子序列，可以想到动态规划。设 $f_{i,0/1}$ 表示选到了第 $i$ 个数，当前选到新序列中编号模 $2$ 为 $0/1$ 所得到的分数的最大值。$f_{i,0}$ 可以由 $f_{j,1}(0\le j\lt i)$ 转移过来，但是可以发现 $f_{i-3,1}$ 一定比 $f_{i-1,1}$ 更优，因为中间可以在插一个偶数编号。同理，$f_{i-2,1}$ 也一定比 $f_{i-4,1}$ 更优，那么 $f_{i,0}$ 只要从 $f_{i-1,1}$ 和 $f_{i-2,1}$ 转移过来即可。

## 代码：
<https://atcoder.jp/contests/abc369/submissions/57296836>

---

## 作者：Liyunze123 (赞：0)

# 题意
有 $n$ 个人，你可以选择是否跟第 $i$ 个人对弈。如果和第 $i$ 个人对弈，你可以获得 $a_i$ 点经验，且他是你对弈的第偶数个人，你可以额外获得 $a_i$ 点经验值。
# 题解
考虑 DP。

$dp_{i,0}$ 表示和第 $i$ 个人对弈，对弈偶数个人，最大经验值。

$dp_{i,1}$ 表示和第 $i$ 个人对弈，对弈奇数个人，最大经验值。

$dp_{i,2}$ 表示不和第 $i$ 个人对弈，对弈偶数个人，最大经验值。

$dp_{i,3}$ 表示不和第 $i$ 个人对弈，对弈奇数个人，最大经验值。

转移时考虑是否跟第 $i-1$ 个人对弈。

$dp_{1,0}$ 和 $dp_{1,3}$ 是不合法的情况，根据转移方程，要把 $dp_{0,1}$ 和 $dp_{0,3}$ 初始化成负无穷。
# 代码
```
// LUOGU_RID: 175558723
#include<bits/stdc++.h>
using namespace std;
int n,a;
long long dp[200010][4];
int main(){
    scanf("%d",&n),dp[0][1]=dp[0][3]=-(1e18);
    for(int w=1;w<=n;w++){
    	scanf("%d",&a);
    	dp[w][0]=max(dp[w-1][1],dp[w-1][3])+2*a;
    	dp[w][1]=max(dp[w-1][0],dp[w-1][2])+a;
    	dp[w][2]=max(dp[w-1][2],dp[w-1][0]);
    	dp[w][3]=max(dp[w-1][3],dp[w-1][1]);
	}
	printf("%lld",max(max(dp[n][0],dp[n][1]),max(dp[n][2],dp[n][3])));
    return 0;
}
```

---

## 作者：linjinkun (赞：0)

简单 $dp$。

设 $f_{i,0/1}$ 表示当前打到第 $i$ 只怪兽，打的怪兽数量是偶数或奇数是的最大得分（经验）。

那么状态转移容易得出：$f_{i,0} = \max(f_{i-1,0}+f_{i-1,1}+2 \times a_i),f_{i,1} = \max(f_{i-1,1},f_{i-1,0}+a_i)$

其实就是考虑选和不选两种情况，非常简单，这里就不过多阐述了。

**注意：不开 ```long long``` 见祖宗！！**

直接上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
#define int long long 
int a[N];
int f[N][2];
signed main()
{
	int n;
	scanf("%lld",&n);
	for(int i = 1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	f[1][1] = a[1];//初始化
	for(int i = 2;i<=n;i++)
	{
		f[i][0] = max(f[i-1][0],f[i-1][1]+2*a[i]);
		f[i][1] = max(f[i-1][1],f[i-1][0]+a[i]);
	}
	printf("%lld",max(f[n][0],f[n][1]));
	return 0;
}
```

---

## 作者：Elysian_Realme (赞：0)

打眼一看就是一道很裸的 dp，套路的设 $f_{i,j(0/1)}$ 表示考虑前 $i$ 位，消灭怪兽数量的奇偶性为 $j$ 的最大贡献。

转移分取和不取两种情况考虑即可，赋初值时记得将取了 $0$ 个奇偶性为 $1$ 的情况标记为负无穷，这种情况显然不存在。

```cpp
// Problem: D - Bonus EXP
// Contest: AtCoder - AtCoder Beginner Contest 369
// URL: https://atcoder.jp/contests/abc369/tasks/abc369_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// By：lmq
// AC Time：2024-08-31 20:02:23

#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline void print(int x){
	static int s[20],t=0;
	do s[++t]=x%10,x/=10;while(x);
	while(t) putchar(s[t--] + '0');
}
const int N=2e5+5;
int n;
int a[N];
int f[N][2];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		a[i]=read();
	f[0][1]=-2e9;
	for(int i=1;i<=n;i++){
		f[i][0]=max(f[i-1][0],f[i-1][1]+a[i]*2);
		f[i][1]=max(f[i-1][1],f[i-1][0]+a[i]);
	}
	cout<<max(f[n][0],f[n][1]);
	return 0;
}
// 某一日，祂从天坠落。人们抬头仰望，于是看见了星空。
// 星月送来神的女儿，她愿成为人的伴侣。
// 长风化作她的轺车，四海落成她的园圃。鸟雀衔来善的种子，百花编织爱的颂歌。
// 她便是这样降生于世，行于大地，与人类一同长大，与世界一起发芽。
// 而今，「终焉」之时将至。
// 而今，「归去」之时已至。
// 就此告别吧，美丽的世界。
// 此后，将有「群星」闪耀，因为我如今来过。
// 此后，将有「百花」绽放，因为我从未离去。
// 请将我的箭、我的花、与我的爱，织成新生的种子，带向那枯萎的大地。
// 然后，便让它开出永恒而无瑕的…「人性之华」吧。
// 「我名为爱莉希雅……」
// 「最初的律者，人之律者。」
```

---

## 作者：osfly (赞：0)

考虑 dp。

我们设 $dp_{i,0}$ 表示考虑前 $i$ 个怪物，已经打了偶数个怪物。同理，$dp_{i,1}$ 表示考虑前 $i$ 个怪物，已经打了奇数个怪物。

显然有：

$$
\begin{aligned}
dp_{1,1}&=a_1\\
dp_{1,0}&=0\\
dp_{i,0}&=\max(dp_{i-1,1}+2a_i,dp_{i-1,0})\\
dp_{i,1}&=\max(dp_{i-1,0}+a_i,dp_{i-1,1})\\
\end{aligned}
$$

直接转移即可。注意答案要初始化为 $a_1$，时间复杂度为 $O(n)$。

~~可以滚动数组优化空间，但是我懒得写了。~~

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int N=1e6+10;

ll f[N][2];
ll n,a[N],ans;

int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	f[1][1]=ans=a[1];
	for(int i=2;i<=n;i++)
	{
		f[i][0]=max(f[i-1][1]+a[i]*2,f[i-1][0]);
		f[i][1]=max(f[i-1][0]+a[i],f[i-1][1]);
		ans=max(ans,max(f[i][0],f[i][1]));
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：_xxxxx_ (赞：0)

### 题意

给出一个长为 $n$ 的序列 $A$，你可以顺序选择一种取数的方案，在你拿到**偶数个数**的数时可以翻倍，问最大收益。

### 分析

贪心不能考虑跳开一些数，因此我们考虑 dp。

注意到**偶数**，所以我们可以这样定义我们的 dp 数组。

$dp[i][0]$ 表示第 $i$ 位是我们将要取的偶数位（可以翻倍）时的最大收益。

$dp[i][1]$ 表示第 $i$ 位是我们将要取的奇数位时的最大收益。

那我们经过一会思考就能得到：

$$dp[i][0]=\max(dp[i-1][1]+A[i]*2,dp[i-1][0])$$

$$dp[i][1]=\max(dp[i-1][0]+A[i],dp[i-1][1])$$

解释一下，如果现在是偶数，那么上一位肯定是奇数，而当前是偶数时收益可以翻倍。现在是奇数也同理。与前一个取 $\max$ 就表示根本不取这一个数。

另外要注意 $dp[0][1]$ 要设成负无穷，因为第一个就是第一个，不可能翻倍了。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n;
int a[N];
int dp[N][2];
signed main()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    dp[0][1] = -1e18;//负无穷
    for(int i = 1; i <= n; i++)
    {
        dp[i][0] = max(dp[i - 1][1] + a[i] * 2, dp[i - 1][0]);
        dp[i][1] = max(dp[i - 1][0] + a[i], dp[i - 1][1]);
        //转移方程
        // cout << dp[i][0] << " " << dp[i][1] << endl;
    }
    cout << max(dp[n][0], dp[n][1]) << endl;
    return 0;
}
```

---

## 作者：Laisira (赞：0)

### 题面
一个人去打怪，打了第 $i$ 个怪收益为 $a_i$，第偶数次打怪收益翻倍，问最大收益。

### 思路
一眼 dp 模板。

设 $f_{i,0/1}$ 表示处理完第 $i$ 只怪（不一定要打掉 Ta）后现在是偶数还是奇数次。

转移：

$$f_{i,p} = \max(f_{i-1,p},f_{i-1,p\oplus 1}+a_i\times (p\oplus 1+1))\ (p\in [0,1])$$

挺好理解的一个状态要么原封不动送过来，要么打怪改状态，特别的，$f_{0,1}$ 显然不合法，初始化 $-\infty$。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
#define Maxn 1000005 
using namespace std;
int a[Maxn],f[Maxn][2];
signed main()
{
	int n,ans = 0;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
    f[0][1] = -INT_MAX;
	for(int i=1;i<=n;i++)
	    for(int p=0;p<2;p++)		
	        f[i][p] = max({f[i-1][p],f[i-1][p^1]+a[i]*((p^1)+1)}); 
	cout<<max(f[n][0],f[n][1]);
	return 0;
 } 
```

---

## 作者：_H17_ (赞：0)

## 题目分析

考虑一个简单的 DP。

设：$f_{i,j\bmod 2}$考虑前 $i$ 个怪兽，打了 $j$ 个怪物时的答案。

对于偶数 $f_{i,0}=\max(f_{i-1,0},f_{i-1,1}+2\times x)$，对于奇数 $f_{i,1}=\max(f_{i-1,1},f_{i-1,0}+x)$。

最终答案是 $\max(f_{n,0},f_{n,1})$。

---

## 作者：stripe_python (赞：0)

简单 DP。

设 $dp_{s,i}$ 表示打到第 $i$ 只怪物，奇偶性为 $s$ 时的最大得分。容易得到：

$$
dp_{s,i}=\max(dp_{1-s,i-1}+a_i+[s=1]a_i,dp_{s,i-1})
$$

看各位大佬都是递推，本蒟蒻给个记搜罢。

```cpp
long long n, a[N], dp[2][N];
long long dfs(long long st, long long i) {
	if (dp[st][i]) return dp[st][i];
	if (i > n) return 0;
	return dp[st][i] = max(dfs(st ^ 1, i + 1) + (st == 1 ? a[i] : 2 * a[i]), dfs(st, i + 1));
}
```

---

## 作者：hjyowl (赞：0)

### 题目大意：

给你一堆怪兽，每个怪兽有一个 $a_i$ 值，打掉第 $i$ 个怪兽可以获得 $a_i$ 的经验，如果是第偶数个的话，额外获得 $a_i$ 的经验，求出最大经验。

### 暴力思路：

二进制枚举，直接枚举第 $i$ 个怪兽打还是不打，但是会超时。

### 正确思路：

定义 dp 数组，设 $f_{i,0}$ 表示第 $i$ 只怪兽是第偶数只怪兽，$f_{i,1}$ 则相反。

#### 转移部分：

```
		f[i][0] = max(f[i - 1][1] + 2 * a[i],f[i - 1][0]);//选/不选
		f[i][1] = max(f[i - 1][0] + a[i],f[i - 1][1]);//选/不选
```
#### 初始值设置：

$f_{0,1}=-10^{18}$，因为没打的情况下不可能能为奇数只怪兽。

### 代码实现：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 300010;
long long f[N][2];
long long a[N];
int n;
int main(){
	cin >> n;
	for (int i = 1; i <= n; i ++ ){
		cin >> a[i];
	}
	f[0][1] = -1e18;
	for (int i = 1; i <= n; i ++ ){
		f[i][0] = max(f[i - 1][1] + 2 * a[i],f[i - 1][0]);
		f[i][1] = max(f[i - 1][0] + a[i],f[i - 1][1]);
	}
	cout << max(f[n][0],f[n][1]);
	return 0;
}
```

---

