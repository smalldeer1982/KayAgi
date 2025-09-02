# Remove the Bracket

## 题目描述

RSJ 得到了一个长为 $n$ 的序列 $a_1,a_2, \ldots, a_n$ 和一个正整数 $s$，他想要计算 $\prod\limits_{i=1}^n a_i$。对于 $a_2,a_3, \ldots, a_{n-1}$ 中的每一个，他都选取了一对**非负整数** $x_i,y_i$ 使得 $x_i + y_i = a_i$ 且 $(x_i-s) \cdot (y_i-s) \geq 0$。他使用如下的方法计算：

$$
\begin{aligned}
\text{Product} &= a_1 \cdot a_2 \cdot a_3 \cdot \ldots \cdot a_n \\
&= a_1 \cdot (x_2+y_2) \cdot (x_3+y_3) \cdot (x_4 + y_4) \cdot \ldots \cdot (x_{n-1}+y_{n-1}) \cdot a_n \\
&\overset{\text{?}}{=} a_1 \cdot x_2+y_2 \cdot x_3+y_3 \cdot x_4 + y_4 \cdot \ldots \cdot x_{n-1}+y_{n-1} \cdot a_n
\end{aligned}
$$

但是他在计算时出现了错误，不小心把括号弄丢了（式子第 $3$ 行）。于是，他想要知道写错了的式子（$F = a_1 \cdot x_2+y_2 \cdot x_3+y_3 \cdot x_4 + y_4 \cdot \ldots \cdot x_{n-1}+y_{n-1} \cdot a_n$）的最小值是多少。

~~这是原本的题面，审核改成了现在的样子（真就 remove the bracket 了，导致赛时式子有歧义，在此向大家道歉~~


第二行 $n$ 个正整数 $a_1,a_2,\ldots,a_n$（$0 \le a_i \le 2 \cdot 10^5$）表示序列 $a$。

保证所有测试数据的 $n$ 之和不超过 $2\cdot 10^5$。

## 样例 #1

### 输入

```
10
5 0
2 0 1 3 4
5 1
5 3 4 3 5
7 2
7 6 5 4 3 2 1
5 1
1 2 3 4 5
5 2
1 2 3 4 5
4 0
0 1 1 1
5 5
4 3 5 6 4
4 1
0 2 1 0
3 99999
200000 200000 200000
6 8139
7976 129785 12984 78561 173685 15480```

### 输出

```
0
18
32
11
14
0
16
0
40000000000
2700826806```

# 题解

## 作者：yimuhua (赞：16)

## 题意：

给你一个长为 $n$ 的序列 $a$ 和一个整数 $s$，对于 $a_2,a_3\dots a_{n-1}$，求出 $x_i$ 和 $y_i$，满足 $x_i+y_i=a_i$ 且 $(x_i-s)(y_i-s)\geq 0$，并使得：

$F=a_1\times x_2+y_2\times x_3+y_3\times \dots \times x_{n-1}+y_{n-1}\times n$

最小。

## 思路：

推式子，发现 $(x_i-s)(y_i-s)\geq 0$ 意味着 $\min(x_i,y_i)\geq s$ 或 $\max(x_i,y_i)\leq s$，于是我们有了上下界。

接着对于 $x_i,y_i$ 我们考虑它对 $F$ 的贡献，其实只有：

$y_{i-1}\times x_i+y_i\times x_{i+1}$

而我们已知上下界，且 $x_i+y_i=a_i$，那么考虑怎样最优：

若 $y_{i-1}<x_{i+1}$，则让 $x_i$ 加一，$y_i$ 减一更优，最后 $x_i$ 会加到上界。反之亦然。则 $x_i,y_i$ 必然在上下界，于是我们可以 dp 了。

设 $dp_{i,0/1}$ 表示处理了前 $i$ 组，第 $i$ 组取上/下界的最小 $F$。

直接转移即可。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long t, n, s, a[200005], maxi[200005], mini[200005], dp[200005][2];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--) {
        cin >> n >> s;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            if(a[i] >= 2 * s)
                maxi[i] = a[i] - s, mini[i] = s;
            else
                mini[i] = max(0ll, a[i] - s), maxi[i] = a[i] - mini[i];
        }
        dp[2][0] = a[1] * mini[2], dp[2][1] = a[1] * maxi[2];
        for(int i = 3; i < n; i++)
            dp[i][0] = min(dp[i - 1][0] + maxi[i - 1] * mini[i], dp[i - 1][1] + mini[i - 1] * mini[i]), dp[i][1] = min(dp[i - 1][0] + maxi[i - 1] * maxi[i], dp[i - 1][1] + mini[i - 1] * maxi[i]);
        cout << min(dp[n - 1][0] + a[n] * maxi[n - 1], dp[n - 1][1] + a[n] * mini[n - 1]) << '\n';
    }
    return 0;
}
```


---

## 作者：KingPowers (赞：5)

## 前言

本文分享一下赛时的思考过程，因此不一定严谨，见谅。

感觉这题难度大概在 1600 或者 1700 上？

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF1787C)

给定你一个长度为 $n$ 的数列 $a$ 和一个整数 $s$，对于任意的 $i\in[2,n-1]$，选择一对整数 $x_i,y_i$，要求 $x_i+y_i=a_i$，并且 $(x_i-s)\cdot (y_i-s)\ge0$，定义一个数：

$$
F=a_1\cdot x_2+y_2\cdot x_3+y_3\cdot x_4+...+y_{n-1}\cdot a_n
$$

要求最小化 $F$。

## 正文

题目其实也可以想象成将 $a_2$ 到 $a_{n-1}$ 每个数拆成两份，全都拆完之后再把序列从头到尾两两相乘累加起来就能得到 $F$。

思考一下，显然如果直接贪心的话是完全没法贪的，因此考虑下 dp。

开始的想法是设 $f[i][j]$ 表示令 $x_{i+1}=j$ 时前 $i$ 项的和的最小值，转移的话就枚举下 $x_i$ 填的是啥，然后如果填的合法（满足 $s$ 的限制）就直接算出来 $y_i$ 是啥，然后就能转移了。

但是这样搞的话复杂度是三次的，$n\le2\times 10^5$，~~极其弱智~~。考虑优化？发现这么想的话好像啥都优化不了，因为不知道 $x_{i+1}$ 和 $x_i$ 的话无论如何都是没法转移的。

这种情况下，一般就要通过特别的结论来进行优化了。什么结论？毕竟是打 CF，直接考虑猜一个。考虑复杂度的瓶颈主要是在枚举每一个 $x_i$ 填啥上，那么就直接猜所有的 $x_i,y_i$ 可能的取值非常少。多少呢？继续猜，应该是一个尽可能的能往大填就往大填，另一个就是尽可能的往小了填。

事实证明这样猜的是对的，至于原因，还记得上面说的吗？大概就是如果把 $a_i$ 拆成 $x_i+y_i$，假如 $x_i$ 和前面的一个 $a$ 相乘，$y_i$ 和后面的一个 $b$ 相乘，如果把 $x_i$ 减去 $1$ 加到 $y_i$ 头上可以使答案更小， 那么我们为什么不在保证满足 $s$ 的限制的情况下，一直如此下去呢？反之亦然。

至于 $x_i$ 或者 $y_i$ 最小和最大具体是多少，如果 $s\ge a_i$ 显然最小能填 $0$，最大能填 $a_i$，否则的话手模一下不难发现最小填 $\min(s,a_i-s)$，最大能填 $\max(s,a_i-s)$。

既然对于每个 $i$，可能的 $x_i,y_i$ 只有两种情况，那么状态就不用像刚才那么多了，定义成 $f[i][0/1]$ 就够了，直接转移就行了。

具体看代码。

```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define PII pair<int,int>
#define fx fixy
#define fy second
#define Mp make_pair
#define umap unordered_map
#define pb push_back
#define all(x) x.begin(),x.end()
#define Debug(x) cerr<<#x<<'='<<x<<endl
using namespace std;

const int N=2e5+5;
const int inf=1e9;
const int mod=1e9+7;
const bool DataS=1;

namespace IOM{
	#define enter putchar(' ')
	#define space putchar('\n')
	int read(){
		int ans=0,flag=1;char ch=getchar();
		for(;!isdigit(ch);ch=getchar()) if(ch=='-') flag=-1;
		for(;isdigit(ch);ch=getchar()) ans=ans*10+(ch^48);
		return ans*flag;
	}
	template<class T>
	void read(T& x){
		x=read();
	}
	template<class T1,class... T2>
	void read(T1& Arg,T2&... Args){
		read(Arg);read(Args...);
	}
	void write(int x){
		if(x<0) putchar('-'),x=-x;
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	int MOD(int x){
		return (x%mod+mod)%mod;
	}
	int qpow(int x,int y=mod-2){
		int res=1;
		while(y){
			if(y&1) res=(res*x)%mod;
			x=(x*x)%mod,y>>=1;
		}
		return res;
	}
}using namespace IOM;

int n,s,a[N],f[N][2],xy[N][2];

void Main(){
	read(n,s);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=2;i<n;i++){
		if(a[i]<s) xy[i][0]=0,xy[i][1]=a[i];
		else xy[i][0]=s,xy[i][1]=a[i]-s;
	}
	for(int i=2;i<n;i++){
		if(i==2){
			f[i][0]=a[1]*xy[i][0];
			f[i][1]=a[1]*xy[i][1];
		}
		else{
			f[i][0]=min({f[i-1][0]+xy[i-1][1]*xy[i][0],f[i-1][1]+xy[i-1][0]*xy[i][0]});
			f[i][1]=min({f[i-1][0]+xy[i-1][1]*xy[i][1],f[i-1][1]+xy[i-1][0]*xy[i][1]});
		}
	}
	int F=min(f[n-1][0]+xy[n-1][1]*a[n],f[n-1][1]+xy[n-1][0]*a[n]);
	printf("%lld\n",F);
}

signed main(){
	int T=DataS?read():1;
	while(T--) Main();
	return 0;
}
```


---

## 作者：hcywoi (赞：2)

### 【题意】

- 给定一个序列 $\{a_n\}$。

- 对于 $\forall i(2\le i\le n-1)$ 求出数对 $(x_i, y_i)$ 满足 $x_i+y_i=a_i, (x_i-s)(y_i-s)\ge 0$。

- 求 $a_1\times x_2 + y_2\times x_3 +\cdots + y_{n-1}\times a_n$ 的最小值。

---

### Solution

满足 $(x_i-s)(y_i-s)\ge 0$，即满足 $a_i\le s, b_i\le s$ 或者 $a_i\ge s, b_i\ge s$。

我们令 $\min_i$ 表示 $\min\{x_i, y_i\}$ 的最小值。

再令 $\max_i$ 表示 $\max\{x_i, y_i\}$ 的最大值。

则 $x_i$ 和 $y_i$ 一定为 $x_i\to\min_i, y_i\to\max_i$ 或者 $x_i\to\max_i, y_i\to\min_i$。

---

#### 【证明】：

先得出 $(x_i, y_i)$ 的贡献，$y_{i-1}\times x_i+y_i\times x_{i+1}$。

如果 $y_{i-1}<x_{i+1}$ 那么必然是 $x_i$ 尽可能大，反之亦然。

---

综上，我们可以 DP，令 $f_{i, 0/1}$ 表示到了第 $i$ 个位置，$x_{i}$ 的值为 $\min_{i}/\max_{i}$ 的最小值。

状态转移：

$$
\begin{cases}
f_{i, 0}=\min\{f_{i-1, 0}+\max_{i-1}\cdot\min_i, f_{i-1, 1}+\min_{i-1}\cdot\min_i\}\\
f_{i, 1}=\min\{f_{i-1, 0}+\max_{i-1}\cdot\max_i, f_{i-1, 1}+\min_{i-1}\cdot\max_i\}
\end{cases}
$$

[代码。](https://codeforces.com/contest/1787/submission/196266352)

---

## 作者：qzhwlzy (赞：2)

## 题目大意

RSJ 得到了一个长为 $n$ 的序列 $a_1,a_2, \ldots, a_n$ 和一个正整数 $s$。对于 $a_2,a_3, \ldots, a_{n-1}$ 中的每一个，他都选取了一对**非负整数** $x_i,y_i$ 使得 $x_i + y_i = a_i$ 且 $(x_i-s) \cdot (y_i-s) \geq 0$。他想要知道 $F = a_1 \cdot x_2+y_2 \cdot x_3+y_3 \cdot x_4 + y_4 \cdot \ldots \cdot x_{n-1}+y_{n-1} \cdot a_n$ 的最小值是多少。

## 思路

对于 $x_i$ 和 $y_i$，因为和的保证，所以二者的取值范围都是连续的一段，我们可以处理出来这一段，记为 $[\text{min},\text{max}]$。关于如何计算，处理方法很多，~~这里选择了最抽象的一种~~。$(x_i-s) \cdot (y_i-s) \geq 0$ 即 $x_i$ 和 $y_i$ 同时大于等于或同时小于等于 $s$。因为 $a_i = \dfrac{a_i}{2} + \dfrac{a_i}{2}$，想象 $x_i$ 与 $y_i$ 分别从 $\dfrac{a_i}{2}$ 分别加和减一个数 $\Delta$。故若 $s > \dfrac{a_i}{2}$，$\text{max} = s$；否则 $\text{min} = s$。注意特判前一种情况的 $\text{min}$ 是否小于 $0$。

对于式子，考虑 $x_i$ 和 $y_i$ 的具体取值。考虑其中的两项 $y_{i-1}\cdot x_i + y_i\cdot x_{i+1}$，贪心地发现把较大值分配给 $y_{i-1}$ 和 $x_{i+1}$ 中较大的那一个一定是最优的。证明很简单，假设 $y_{i-1} > x_{i+1}$，则 $y_{i-1}\cdot x_i + y_i\cdot x_{i+1} > y_{i-1}\cdot x_i + y_i\cdot x_{i+1} - \Delta(y_{i-1} - x_{i+1}) = y_{i-1}\cdot (x_i - \Delta) + (y_i + \Delta)\cdot x_{i+1}$。

所以，$x_i$ 和 $y_i$ 有且仅有两种取值：$\text{max},\text{min}$ 或 $\text{min},\text{max}$。于是，我们可以 DP 求解。例如令 $f_{i,0}$ 表示 $x_i$ 取 $\text{min}$ 时前 $i$ 个数的答案最小值，$f_{i,1}$ 表示 $x_i$ 取 $\text{max}$ 时前 $i$ 个数的答案最小值。式子也不难写，枚举 $i-1$ 选哪一种情况，计算并取较小值即可：

$$
f_{i,0} = \min(f_{i-1,0}+\text{max}_{i-1}*\text{min}_i,f_{i-1,1}+\text{min}_{i-1}*\text{min}_i)
$$
$$
f_{i,1} = \min(f_{i-1,0}+\text{max}_{i-1}*\text{max}_i,f_{i-1,1}+\text{min}_{i-1}*\text{max}_i)
$$

### 代码

```cpp
#include<iostream>
#include<cstdio>
#define maxn 200005
#define ll long long
using namespace std;
int T,n,s,a[maxn],mmin[maxn],mmax[maxn]; ll f[maxn][2]; // 0:min-max 1:max-min 
void set(){for(int i=1;i<=n;i++){a[i]=mmin[i]=mmax[i]=0; f[i][0]=f[i][1]=9220000000000000000;}}
int main(){
    scanf("%d",&T); while(T--){
        scanf("%d%d",&n,&s); set(); for(int i=1;i<=n;i++){
            scanf("%d",&a[i]); if(a[i]/2<s){mmax[i]=a[i]-s>=0?s:a[i]; mmin[i]=a[i]-mmax[i];}
            else{mmin[i]=s; mmax[i]=a[i]-mmin[i];}
        } f[1][0]=f[1][1]=0LL; mmin[1]=mmax[1]=1LL*a[1]; for(int i=2;i<n;i++){
            f[i][0]=min(f[i-1][0]+1LL*mmax[i-1]*mmin[i],f[i-1][1]+1LL*mmin[i-1]*mmin[i]);
            f[i][1]=min(f[i-1][0]+1LL*mmax[i-1]*mmax[i],f[i-1][1]+1LL*mmin[i-1]*mmax[i]);
        } printf("%lld\n",min(f[n-1][0]+1LL*mmax[n-1]*a[n],f[n-1][1]+1LL*mmin[n-1]*a[n]));
    } return 0;
}
```


---

## 作者：kingho11 (赞：1)

# CF1787C Remove the Bracket 题解

我们今天老师上课讲了这道题，再加上我的一些理解后，想要分享一下
## 题意：
给你 $n$ 个数，除了第 $1$ 个和第 $n$ 个外，需要将其它数拆成 $x_i+y_i$ 的形式，同时要满足 $(x_i-s) \cdot (y_i-s) \geq 0$ 在此前提下，最小化
$$
F=a_1 \times x_2+y_2 \times x_3+y_3 \times x_4+ ... +y_{n-2} \times x_{n-1}+y_{n-1} \times a_n
$$
的值

## 思路：
我们可以优先观察如何拆 $a_i$ 可以使得 $x_i,y_i$ 对答案的贡献最小

观察可得，当所有的 $x_i,y_i$ 都很接近的时候，$F$的值最大

那么反过来，即可得到当所有的 $x_i,y_i$ 都差的很大的时候，$F$ 的值最小

好的，现在的问题转化为，如何分配 $x_i,y_i$ 使得 它们之间的差值最大

思考一下，我们是不是可以让所有的 $x_i,y_i$ 的其中一个尽量小，另一个尽量大就可以了

当然，题目中还有一个条件 $(x_i-s) \cdot (y_i-s) \geq 0$ 用人话翻译一下就是 $x_i,y_i$ 要不都大于 $s$，要不都小于 $s$。

依据前面提到的内容，我们可以进行分类讨论

①当 $a_i \ge s$ 时，可以把 $a_i$ 拆分为 $s$ 和 $a_i-s$

②当 $a_i \le s$ 时，可以把 $a_i$ 拆分为 $0$ 和 $a_i$

于是，我们便可以设计 $dp$ 状态了

设 $dp_{i,j}$ 表示到前 $i$ 个数，$y_i$ 的取值是前者（即 $s$ 或 $0$）还是后者（即 $a_i-s$ 或 $a_i$）

因为我们可以通过 $y_i$ 的取值排除出 $x_i$ 的取值，所以不需要更多的维度来记录，且用 $j=0$ 来表示 $y_i$ 的取值是前者，用 $j=1$ 来表示 $y_i$ 的取值是后者

状态转移方程在代码里面写的很详细
## 细节
$1$、当 $i=1,2,n$ 的时候需要特殊处理，详见代码

$2$、$dp$ 数组需要先赋一个极大值
## 代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,s,a[N],dp[N][2];
void solve()
{
	cin>>n>>s;//读入 
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	memset(dp,0x7f,sizeof(dp));//赋极大值 
	dp[1][0]=dp[1][1]=0;//初始化，即i=1时 
	if(a[2]>=s)//特殊处理i=2时，因为i=2时的状态转移的方式和别的不一样 
	{
		dp[2][0]=a[1]*(a[2]-s);
		dp[2][1]=a[1]*s;
	}else
	{
		dp[2][0]=a[1]*a[2];
		dp[2][1]=0;
	}
	for(int i=3;i<=n-1;i++)
	{
		if(a[i]>=s)//把a_i拆成s和a_i -s
		{
			dp[i][0]=min((a[i]-s)/*这里是x_i*/*(a[i-1]>=s?s:0)/*三目运算符中是上一轮的y_i*/+dp[i-1][0],(a[i]-s)/*这里是x_i*/*(a[i-1]>=s?a[i-1]-s:a[i-1])/*三目运算符中是上一轮的y_i*/+dp[i-1][1]);
			dp[i][1]=min(s/*这里是x_i*/*(a[i-1]>=s?s:0)/*三目运算符中是上一轮的y_i*/+dp[i-1][0],s/*这里是x_i*/*(a[i-1]>=s?a[i-1]-s:a[i-1])/*三目运算符中是上一轮的y_i*/+dp[i-1][1]);
		}else//把a_i拆成0和s
		{
			dp[i][0]=min(a[i]/*这里是x_i*/*(a[i-1]>=s?s:0)/*三目运算符中是上一轮的y_i*/+dp[i-1][0],a[i]/*这里是x_i*/*(a[i-1]>=s?a[i-1]-s:a[i-1])/*三目运算符中是上一轮的y_i*/+dp[i-1][1]);
			dp[i][1]=min(dp[i-1][0],dp[i-1][1]);//因为此时的x_i=0，所以前面的直接省略了 
		}
	}
	cout<<min((a[n-1]>=s?s:0)*a[n]+dp[n-1][0],(a[n-1]>=s?a[n-1]-s:a[n-1])*a[n]+dp[n-1][1])<<"\n";//此时需要特殊处理，因为上一轮的y_n-1在这里不是乘的这一轮的x_n了，而是a_n 
}
signed main()
{
	ios::sync_with_stdio(false);//关流 
	cin.tie(0),cout.tie(0);
	int _;
	cin>>_;
	while(_--)
	{
		solve();
	}
}
```

---

## 作者：ttq012 (赞：1)

upd $2023/02/04$：格式化了代码。

首先考虑将 $a_i$ 分解成两部分。

容易发现，分解也就是让一个数尽量的大，另外的一个数尽量的小。

证明：设前一个数是 $x$，后一个数是 $y$。分解出来的两个数分别是 $a$ 和 $b$。

设 $x>y$，$a>b$。

那么答案是 $x\times b + y\times a$。容易发现是最小的。

如果 $x\le y$，$a>b$。

那么答案是 $y\times b + x\times a$。容易发现也是最小的。

但是暴力做是 $\mathcal O(2^n)$ 的，会 $\texttt{\color{darkblue}{TLE}}$。

那么考虑 $\mathcal DP$。

设 $mx_i$ 是第 $i$ 个数分解完了之后大的那一个，$mi_i$ 是小的那一个。

设 $f_{i,0/1}$ 是目前执行到了第 $i$ 个数，让小的在前面大的在后面 或者 小的在后面大的在前面，所得到的最小的值。

那么初始条件是 $f_{2,0}=a_1\times mi_2$，$f_{2,1}=a_1\times mx_2$，其他的 $f_{i,0/1} = \infty$。

然后转移的时候 $i\in [3,n)$：

+ $f_{i,0}=\min(f_{i-1,0}+mx_{i-1}\times mi_i,f_{i-1,1}+mi_{i-1}\times mi_i)$。
+ $f_{i,1}=\min(f_{i-1,0}+mx_{i-1}\times mx_i,f_{i-1,1}+mi_{i-1}\times mx_i)$。

到最后求答案的时候特判最后一个即可。

时间复杂度 $\mathcal O(n)$。

$\Huge\color{white}\text{停止颓废，从我做起}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define seele while(T--)
#define orz solve();
#define cf_t signed main() {
	int T;
	cin>>T;
	seele orz return 0;
}
const int N=2e5+10;
int mx[N],mi[N],f[N][2],a[N];
int n,s;
void solve() {
	cin>>n>>s;
	for (int i=1;i<=n;i++)cin>>a[i];
	for (int i=1;i<=n;i++)if(a[i]>=2*s)mi[i]=s,mx[i]=a[i]-s; else if(a[i]>=s)mx[i]=s,mi[i]=a[i]-s; else mx[i]=a[i],mi[i]=0;
	f[2][1]=a[1]*mx[2],f[2][0]=a[1]*mi[2];
	for (int i=3;i<n;i++) {
		f[i][0]=min(f[i-1][0]+mx[i-1]*mi[i],f[i-1][1]+mi[i-1]*mi[i]);
		f[i][1]=min(f[i-1][0]+mx[i-1]*mx[i],f[i-1][1]+mi[i-1]*mx[i]);
	}
	cout<<min(f[n-1][0]+mx[n-1]*a[n],f[n-1][1]+mi[n-1]*a[n])<<'\n';
}
cf_t
```



---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1787C)

# 思路：
因为数组中的数都是正整数，所以 $(x_i-s)*(y_i-s) \ge 0$ 就等价于 $\min(x_i,y_i) \ge s$ 或 $\max(x_i,y_i) \le s$。

要把一个数分成两个数，最优的方案就是一个是合法的最大数，另一个是最小的，因为只要这个数原来两边的数和不一样，如果分成的两个数一个数 $+1$，一个数 $-1$，那么乘积的和就会加或减和的差，所以只有 $x_i,y_i$ 都是极端状态才可能成为最优方案。所以当这个数小于等于 $s$ 时，$x_i,y_i$ 中的最大值小于等于 $s$，所以就是这个数本身，最小值就是 $0$，当这个数大于 $s$ 时，如果这个数小于等于两倍的 $s$，那么最大值就是 $s$，最小值就是 $a_i-s$，如果这个数大于两倍的 $s$，那么最大值是 $a_i-s$，最小值是 $s$，所以综上，这个数大于s时最大值就是 $\max(s,a_i-s)$，最小值等于 $a_i$ 减最大值。那么我们 ```dp``` 枚举即可，$dp[i][0]$ 表示当前数分成最大数在前，最小数在后，$dp[i][1]$ 表示当前数分成最大数在后，最小数在前，每个 $dp[i]$ 都从 $dp[i-1]$ 的两种状态中的最优值转移即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int read(){
    int x=0,f=1;
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
void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9){
        write(x/10);
    }
    putchar(x%10+'0');
    return;
}
int t,n,s,ma[N],mi[N],dp[N][2];
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>s;
		for(int i=1,x;i<=n;i++){
			cin>>x;
			if(i==1){
				ma[i]=mi[i]=x;
				continue;
			}
			if(i==n){
				ma[i]=mi[i]=x;
				continue;
			}
			if(x<=s){
				ma[i]=x;
				mi[i]=0;
			}else{
				int x1=s,x2=x-s;
				ma[i]=max(x1,x2);
				mi[i]=x-ma[i];
			}
		}
		for(int i=2;i<=n-1;i++){
			dp[i][0]=min(dp[i-1][0]+mi[i-1]*ma[i],dp[i-1][1]+ma[i-1]*ma[i]);
			dp[i][1]=min(dp[i-1][0]+mi[i-1]*mi[i],dp[i-1][1]+ma[i-1]*mi[i]);
		}
		cout<<min(dp[n-1][0]+mi[n-1]*ma[n],dp[n-1][1]+ma[n-1]*ma[n])<<endl;
	}
	return 0;
}
```
完结撒花~

---

## 作者：Furina_Saikou (赞：0)

# 思路

观察 $x_i,y_i$ 和 $s$ 的关系，由 $(x_i-s)\cdot (y_i-s)\ge 0$ 可知要么都大于等于 $s$，要么都小于等于 $s$。最优的情况下，$x_i,y_i$ 应该一个尽量大，一个尽量小，于是我们以 $s$ 为界限判断：

- 当 $a_i\ge s$，将 $a_i$ 分为 $(s,a_i-s)$。
- 当 $a_i < s$，将 $a_i$ 分为 $(0,a_i)$。

解决拆分的问题之后，就可以开始 DP 了，设 $dp_{i,0/1}$ 为前 $i$ 位，第 $i$ 位选最小或最大时的最小值，定义 $maxl,minl,maxn,minn$ 分别为上一个最大，上一个最小，当前最大，当前最小。我们有 $dp_{i,0}=\min(dp_{i-1,0}+maxl\cdot minn,dp_{i-1,1}+minl\cdot minn)$，$dp_{i,1}$ 同理。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=415411;
int t,n,s,a[N],dp[N][2],maxl,minl,maxn,minn;
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>s;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		maxl=a[1],minl=a[1];
		for(int i=2;i<n;i++)
		{
			if(a[i]>=s)
			{
				maxn=max(a[i]-s,s),minn=min(a[i]-s,s);
			}else
			{
				maxn=max(0ll,a[i]),minn=min(0ll,a[i]);
			}
			dp[i][0]=min(dp[i-1][0]+maxl*minn,dp[i-1][1]+minl*minn);
			dp[i][1]=min(dp[i-1][0]+maxl*maxn,dp[i-1][1]+minl*maxn);
			maxl=maxn,minl=minn;
		}
		cout<<min(dp[n-1][0]+a[n]*maxl,dp[n-1][1]+a[n]*minl)<<"\n";
	}
	return 0;
}
```

---

## 作者：zsyzsy_2012 (赞：0)

CF思维好题。

首先考虑暴力做法。我们枚举 $\forall i \in [2,n-1]$ 的 $x[i]$，进而推出 $y[i]$，判断 $(x[i]-s)(y[i]-s) \geq 0$ 是否成立。当然，这种方法太慢了。

再考虑两个优化。

第一个：推式子。$(x[i]-s)(y[i]-s) \geq0$ 其实等价于 $x[i]$ 和 $y[i]$ 都大于等于 $s$ 或者 $x[i]$ 和 $y[i]$ 都小于等于 $s$。 具体是那一种呢？我们发现，如果是第一种情况，则有 $x[i] + y[i] = a[i]\geq2s$。如果是第二种情况，则有 $x[i]+y[i]=a[i]\leq2s$。因此我们可以分类讨论：

(i) $a[i]\geq2s$ 此时 $x[i]$ 的最大值是 $a[i]-s$，最小值是 $s$。

(ii) $a[i]<2s$ 此时 $x[i]$ 的最大值是 $\min(a[i],s)$，最小值是 $a[i]-\min(a[i],s)$。

第二个：有了第一个，这个就很容易想到了。对于 $x[i]$，如果 $y[i - 1]>x[i + 1]$，则 $x[i]$ 取上述最小值总是不劣的。反之，$x[i]$ 取最大值也是不劣的。我们得到一个结论：$x[i]$ 取最小值或最大值，得到的相对优的结果总是不劣于任意 $x[i]$ 合法取值中的最优方案。我们可以想到动态规划，用两个数组记录取最大、最小值的情况，每次更新，答案由 $n-1$ 时的状态取最优来决定。

有了思路，代码就很自然了。具体细节见代码注释：

```
#include <bits/stdc++.h>
#define int long long//十年OI一场空，不开long long见祖宗!
#define N 200010
using namespace std ;
int a[N] , maxn[N] , minn[N] , dp[N][2] ;
//dp[i][0]:x[i]取max值
//dp[i][1]:x[i]取min值
signed main() {
	int T , n , s ;
	scanf("%lld" , &T) ;
	while(T--) {
		scanf("%lld%lld" , &n , &s) ;
		for(int i = 1 ; i <= n ; i++) {
			scanf("%lld" , &a[i]) ;
		}
		dp[1][0] = dp[1][1] = 0 ;
		maxn[1] = minn[1] = a[1] ;//初始化
		for(int i = 2 ; i < n ; i++) {
			if(a[i] >= 2 * s) {
				int mx = a[i] - s , mn = s ;
				maxn[i] = mx ;
				minn[i] = mn ;
				dp[i][0] = min(mx * minn[i - 1] + dp[i - 1][0] , mx * maxn[i - 1] + dp[i - 1][1]) ;
				dp[i][1] = min(mn * minn[i - 1] + dp[i - 1][0] , mn * maxn[i - 1] + dp[i - 1][1]) ;//第一种更新
			}
			else {
				int mx = min(a[i] , s) ;
				int mn = a[i] - mx ;
				maxn[i] = mx ;
				minn[i] = mn ;
				dp[i][0] = min(mx * minn[i - 1] + dp[i - 1][0] , mx * maxn[i - 1] + dp[i - 1][1]) ;
				dp[i][1] = min(mn * minn[i - 1] + dp[i - 1][0] , mn * maxn[i - 1] + dp[i - 1][1]) ;//第二种更新
			}
		}
		int ans = min(dp[n - 1][0] + minn[n - 1] * a[n] , dp[n - 1][1] + maxn[n - 1] * a[n]) ;//求答案，注意这里的更新和上面的不一样
		printf("%lld\n" , ans) ;
	}
	return 0 ;
}
```


---

## 作者：masonpop (赞：0)

有点不等式中调整法的意思了。

直接贪心肯定不行。我们可以控制其它变量，只考虑 $(x_i,y_i)$ 的贡献。和它相关的只有 $y_{i-1}x_i+y_ix_{i+1}$ 这个量。可以发现，我们可以根据 $y_{i-1},x_{i+1}$ 的大小关系将 $x_i,y_i$ 向两边调整，则最小值一定在变量在边界处取到。

而由于 $(x_i-s)(y_i-s)\ge0$，因此根据 $a_i$ 的大小可以确定是 $x_i,y_i\ge s$ 还是 $x_i,y_i\leq s$。那么，马上可以确定取最小值的时候 $x_i,y_i$ 较大者和较小者的取值。接下来只需确定顺序。

显然考虑 $dp$。设 $dp_{i,0/1}$ 表示当前选到第 $i$ 组 $(x_i,y_i)$ 的值，且 $0$ 表示 $x_i$ 取较小值，$1$ 表示 $x_i$ 取较大值。然后，根据根据 $y_{i-1}x_i+y_ix_{i+1}$ 可以由 $i$ 转移到 $i+1$。时间复杂度 $O(n)$。[代码](https://codeforces.com/contest/1787/submission/210611288)。

---

