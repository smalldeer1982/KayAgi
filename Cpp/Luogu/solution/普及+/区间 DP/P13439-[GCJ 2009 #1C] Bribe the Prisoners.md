# [GCJ 2009 #1C] Bribe the Prisoners

## 题目描述

在一个王国里，有一些牢房（编号为 $1$ 到 $P$），这些牢房排成一条直线。编号为 $i$ 和 $i+1$ 的牢房是相邻的，相邻牢房中的囚犯被称为“邻居”。相邻牢房之间有一堵带窗户的墙，邻居们可以通过窗户进行交流。

所有囚犯本来相安无事，直到有囚犯被释放。当某个囚犯被释放时，他的邻居会得知这个消息，并且每个邻居会把这个消息传递给他的另一个邻居。如此传递下去，直到消息传到没有其他邻居的囚犯（即处在第 $1$ 号牢房、第 $P$ 号牢房，或其相邻牢房已空的囚犯）。每当某个囚犯得知有其他囚犯被释放时，除非他被贿赂一枚金币，否则他会愤怒地砸坏自己牢房里的所有东西。因此，当释放编号为 $A$ 的囚犯时，$A$ 号牢房两侧的所有囚犯——从 $A$ 向左直到第 $1$ 号牢房、向右直到第 $P$ 号牢房或遇到空牢房为止——都需要被贿赂。

假设每个牢房最初都正好关押着一名囚犯，并且每天只能释放一个囚犯。给定 $Q$ 个将要被释放的囚犯（共需 $Q$ 天），请你计算，如果可以任意选择释放顺序，最少需要多少金币用于贿赂。

注意，每一次贿赂只对当天有效。如果某个囚犯昨天被贿赂了，今天又听说有囚犯被释放，他还需要再次被贿赂。


## 说明/提示

**样例说明**

在第二个样例中，假如你先释放 14 号牢房的囚犯，再释放 6 号，最后释放 3 号，所需金币数为 $19 + 12 + 4 = 35$。如果你先释放 6 号，再释放 3 号，最后释放 14 号，所需金币数为 $19 + 4 + 13 = 36$。

**限制条件**

- $1 \leq N \leq 100$
- $Q \leq P$
- 每个牢房编号均为 $1$ 到 $P$ 之间的整数

**小数据集**

- 时间限制：2 秒
- $1 \leq P \leq 100$
- $1 \leq Q \leq 5$

**大数据集**

- 时间限制：3 秒
- $1 \leq P \leq 10000$
- $1 \leq Q \leq 100$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
2
8 1
3
20 3
3 6 14```

### 输出

```
Case #1: 7
Case #2: 35```

# 题解

## 作者：Mindulle (赞：7)

非常基础的区间 DP 题。除此之外，还有两道几乎或完全相同的题目：P1622 和 SP14846。

令 $dp_{l,r}$ 为区间 $[l,r]$ 里所需贿赂的最小值，明显可以得到状态转移方程：

$$
dp_{l,r}=\min^{r}_{k=l}\{dp_{l,k-1}+dp_{k+1,r}+a_{r+1}-a_{l-1}-2\}
$$

之所以新的贿赂是 $a_{r+1}-a_{l-1}-2$，是因为释放 $a_k$ 时，需要贿赂的囚犯数量是从 $a_{l-1} + 1$ 到 $a_k - 1$ 和从 $a_k + 1$ 到 $a_{r+1} - 1$ 的所有囚犯。因此，总贿赂数为：

$$
(a_k-a_{l-1}-1)+(a_{r+1}-a_k-1)=a_{r+1}-a_{l-1}-2
$$

最后输出 $dp_{1,q}$ 即可。

注意多测清空！

```cpp
for(int i=1;i<=n;i++){
  memset(dp,0,sizeof dp);
  cout<<"Case #"<<i<<": ";
  cin>>p>>q;
  for(int i=1;i<=q;i++) cin>>a[i];
  a[0]=0,a[q+1]=p+1; //这里是为了方便处理第一次的dp
  for(int len=1;len<=q;len++){ //先枚举区间长度
    for(int l=1;l+len-1<=q;l++){ //左端点
      int r=l+len-1; //右端点
      dp[l][r]=INT_MAX; //初始化为极大值
      for(int k=l;k<=r;k++)
        dp[l][r]=min(dp[l][r],dp[l][k-1]+dp[k+1][r]+a[r+1]-a[l-1]-2);
    }
  }
  cout<<dp[1][q]<<'\n';
}
```

---

## 作者：4041nofoundGeoge (赞：2)

水题
:::align{center}
## 思路
:::
很**~~不~~**明显，这是一道区间 DP。

设 $f_{i,j}$ 为 $[i,j]$ 之间的所需贿赂的最小值。我们有：

$$
f_{i,j}=\min\limits^{j-1}_{k=i+1}\{f_{i,k}+f_{k,j}+\text{money}([l,k],[k,r])\}
$$

其中函数 $\text{money}([l,k],[k,r])=a_r-a_l-2$。

非常好理解，我们每一次计划一个区间中走的是 $k$ 号，自然给的钱就是 $\text{money}([l,k],[k,r])$，我们虚拟一个左右边界 $a_0\leftarrow 0,a_{Q+1}\leftarrow P+1$，这样可以方便计算函数 $\text{money}$。
:::align{center}
## 代码

```cpp 
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
int f[1005][1005],a[1005];
int main(){
    int t;
    cin>>t;
    int q=t;
    while(t--){
        int n,m;
        cin>>n>>m;
        memset(f,0,sizeof f);
        memset(a,0,sizeof a);
        for(int i=1;i<=m;i++)cin>>a[i];
        a[0]=0,a[m+1]=n+1;
        sort(a+1,a+m+1);
        for(int len=2;len<=m+1;len++){
            for(int l=0;l<=m+1;l++){
                int r=l+len;
                f[l][r]=INF;
                for(int k=l+1;k<=r-1;k++){
                    f[l][r]=min(f[l][r],f[l][k]+f[k][r]+(a[r]-a[l]-2));
                }
            }
        }
        cout<<"Case #"<<q-t<<": ";
        cout<<f[0][m+1]<<endl;
    }
    return 0;
}
```

---

## 作者：signed_long_long (赞：1)

~~头一次听说狱警贿赂囚犯的……~~

# 题目解法

令 $f_{i,j}$ 为释放区间 $[sf_i,sf_j]$ 里所有需要释放的囚犯最少需要贿赂的金币（$sf_i$ 就是第 $i$ 个需要释放的囚犯编号），那么就有转移方程：
$$f_{i,j}=\min_{i\le k\le j}\{f_{i,k-1}+f_{k+1,j}+sf_{j+1}-sf_{i-1}-2\}$$

解释：$f_{i,k-1}+f_{k+1,j}$ 为释放囚犯 $sf_k$ 前所需要的最少的贿赂的金币，$sf_{j+1}-sf_{i-1}-2$ 为释放囚犯 $sf_k$ 所需要的金币。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e2+5;
int T;
int p,q;
int sf[105];
int f[N][N];
void work(int qwert){
    cin>>p>>q;
    for(int i=1;i<=q;i++) cin>>sf[i];
    sf[0]=0;
    sf[q+1]=p+1;//方便处理第一次
    memset(f,0,sizeof f);
    for(int len=1;len<=q;len++){
        for(int i=1;i<=q-len+1;i++){
            int j=i+len-1;
            f[i][j]=INT_MAX;
            for(int k=i;k<=j;k++){
                f[i][j]=min(f[i][j],f[i][k-1]+f[k+1][j]+sf[j+1]-sf[i-1]-2);
            }
        }
    }
    printf("Case #%d: %d\n",qwert,f[1][q]);
}
int main(){
    cin>>T;
    for(int i=1;i<=T;i++) work(i);
    return 0;
}
```

---

## 作者：Aron_2023 (赞：1)

## 前言

希望能更进一步的学习、练习与巩固动态规划算法。

## 分析
### 算法

区间 dp。

该题不能贪心。对于以下的贪心策略：每次释放影响范围最小的囚犯（即左右未被释放的囚犯数量最少的），有反例证明贪心错误，根据样例也能自己推出来贪心错误。另外，可以通过数据规模来推断解法。贪心题目的数据规模一般为 $n\le10^5$，本题可以根据数据规模推断出正解为动态规划。

设 $dp_{i,j}$ 代表释放区间 $[i,j]$ 的囚犯所需的最少金币。

对于区间 $[i,j]$，枚举其中每一个囚犯 $k$ 作为当前释放的囚犯，释放 $k$ 时贿赂范围为从 $A_{i-1}+1$ 到$A_{j+1}-1$，共 $A_{j+1}-A_{i-1}-1$ 个囚犯，减去已经被释放的 $k$，则所需金币为 $A_{j+1}-A_{i-1}-2$。这样就分解为了两个子问题，继续求解。

状态转移方程：
$$
dp_{i,j}=\min_{i \leq k \leq j} \big\{dp_{i,k-1}+dp_{k+1,j}+(A_{j+1}-A_{i-1}-2) \big\}
$$

边界：当 $i>j$ 时，$dp_{i,j}=0$，表示没有囚犯需要释放。当 $i\le j$ 时，$dp_{i,j}=\inf$。

为了方便处理边界，可以在 $A$ 数组的首尾分别添加 $0$ 和 $P+1$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9+7;
int a[107],dp[107][107];
int main()
{
	int T,p,q,xt=1;
	cin>>T;
	while(T--)
	{
		cin>>p>>q;
		for(int i=1;i<=q;i++)
			cin>>a[i];
		sort(a+1,a+q+1);
		a[0]=0,a[q+1]=p+1;
		memset(dp,0,sizeof(dp)); 
		for(int len=1;len<=q;len++)
			for(int i=1;i<=q-len+1;i++)
			{
				int j=i+len-1;
				dp[i][j]=inf;
				for(int k=i;k<=j;k++)
					dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k+1][j]+(a[j+1]-a[i-1]-2));
			} 
		cout<<"Case #"<<xt<<": "<<dp[1][q]<<'\n';
		xt++;
	}
	return 0;
}
```

---

## 作者：_Weslie_ (赞：1)

双倍经验：[SP14846](https://www.luogu.com.cn/problem/SP14846)。

这个区间 dp 挺有意思的。

## Solution SP14846/P13439

### Idea

正着做，你会发现会出现一堆情况需要考虑。

不妨反着做。

这样问题转化成：你有一排牢房，原先有 $q$ 个空着，其他都有囚犯住在里面。现在你领来了 $q$ 个新囚犯，要把他们都扔进牢房里。每次你可以选择把一个囚犯扔进一个牢房里，但是在这次操作之后，这个牢房旁边的囚犯会传递信息，被传递到信息的囚犯需要一个金币。问最少用多少金币。

我们设 $dp_{l,r}$ 为把 $[l,r]$ 区间里的囚犯全都扔进牢房里，所需要的最少金币数。

那么有

$$dp_{l,r}=\min\limits_{k=l}^r(dp_{l,k-1}+dp_{k+1,r})+a_{r+1}-a_{l-1}-2$$

意思就是：取中间一个断点 $k$，考虑这一次扔进去 $k$。由于此时 $(a_{l-1},a_{r+1})$ 范围内的囚犯除了 $a_k$ 位置都已经在牢房里了，所以你需要给他们一人一个金币。一共有 $a_{r+1}-a_{l-1}-1-1$ 个（第一个 $-1$ 是为了求区间长度，第二个 $-1$ 是去掉 $a_k$ 位置）。

注意一下边界及初值。

### Code

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=105;
ll dp[N][N];
int n,l,a[N];
void solve(int cas){
	scanf("%d%d",&l,&n);
	a[0]=0;a[n+1]=l+1;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		dp[i][i-1]=0;
	}
	dp[n+1][n]=0;
	for(int len=1;len<=n;len++){
		for(int l=1,r=len;r<=n;l++,r++){
			dp[l][r]=0x3f3f3f3f3f3f3f3f;
			for(int k=l;k<=r;k++){
				dp[l][r]=min(dp[l][r],dp[l][k-1]+dp[k+1][r]);
			} 
			dp[l][r]+=a[r+1]-a[l-1]-2;
		}
	}
	printf("Case #%d: %lld\n",cas,dp[1][n]);
} 
int main(){
	int T;scanf("%d",&T);
	for(int i=1;i<=T;i++){
		solve(i);
	}
}
```

---

## 作者：chen_zhe (赞：1)

本题解来自于[《挑战程序设计竞赛》](https://www.luogu.com.cn/training/813583)。

---

这道题的关键是，释放了某个囚犯之后，就把连续的牢房分成了两段，此后这两段就相互独立了。

![](https://cdn.luogu.com.cn/upload/image_hosting/yptlqxmi.png)

释放上图中 ☆ 里的囚犯时

- 此时所需的金币数量
- 释放左侧部分（①）所需的金币总数
- 释放右侧部分（②）所需的金币总数

这三者的总和就是所需的金币总数。只要不断递归地枚举最初释放的囚犯并计算对应的金币总数，就能求出答案了。

这里，递归计算过程中作为计算对象的连续部分，其两端是空牢房或监狱两端。因此，作为计算对象的连续部分一共有 $O(Q^{2})$ 个。所以，利用动态规划按顺序计算，就能够在 $O(Q^{3})$ 时间内求解。

① $dp[i][j]$ 表示的是，将从 $A[i]$ 号囚犯到 $A[j]$ 号囚犯（不含两端的囚犯）的连续部分里的所有囚犯都释放时，所需的最少金币总数。

② 为了更方便地处理两端的情况，我们把左端当成 0 号囚犯，右端当成 $Q+1$ 号囚犯。这样，$dp[0][Q+1]$ 就是答案。

```cpp
// 输入
int P, Q, A[MAX_Q + 2];  // A中保存输入数据，下标从1开始
// dp[i][j] := 释放(i, j)所需的金币
int dp[MAX_Q + 1][MAX_Q + 2];

void solve() {
    // 为了处理方便，将两端加入A中
    A[0] = 0;
    A[Q + 1] = P + 1;

    // 初始化
    for (int q = 0; q <= Q; q++) {
        dp[q][q + 1] = 0;
    }

    // 从短的区间开始填充dp
    for (int w = 2; w <= Q + 1; w++) {
        for (int i = 0; i + w <= Q + 1; i++) {
            // 计算dp[i][j]
            int j = i + w, t = INT_MAX;
           // 枚举最初释放的囚犯，计算最小的费用
            for (int k = i + 1; k < j; k++) {
                t = min(t, dp[i][k] + dp[k][j]);
            }

            // 最初的释放还需要与所释放囚犯无关的A[j] - A[i] - 2枚金币
            dp[i][j] = t + A[j] - A[i] - 2;
        }

    printf("%d\n", dp[0][Q + 1]);
}
```

---

## 作者：Black_Myth_Wukong (赞：0)

# P13439 [GCJ 2009 #1C] Bribe the Prisoners
老师讲了区间动态规划，所以找了道题复习：[传送门。](https://www.luogu.com.cn/problem/P13439)
## 思路 
这题用的是**区间动态规划**，令 $f_{i,j}$ 为释放第 $i \sim j$ 囚犯的最小花费，可得状态转移方程：
$$f_{i,j}=\min(f_{i,j},f_{i,k-1}+f_{k+1,j}+need_{j+1}-need_{i-1}-1-1)$$
其中 $i,j$ 均为需被释放的囚犯编号，并非牢房编号，需释放囚犯编号储存在 $need$ 数组中；$need_{j+1}-need_{i-1}-1$ 就表示第 $j+1\sim i-1$ 名囚犯所需的金币数。第二个 $-1$ 表示第 $k$ 人不能拿到金币。
## 下面是通过记录和代码。
[记录。](https://www.luogu.com.cn/record/227809202)
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+1;
int n,m,s;
int need[N];//需释放的囚犯数 
int f[N][N];//区间dp数组 
int main(){
	ios::sync_with_stdio(0);//加快读入 
	cin.tie(0);cout.tie(0);
	cin>>s;
	for(int a11=0;a11<s;a11++){ 
		cin>>n>>m;//输入牢房数n和需释放的囚犯数m 
    	for(int i=1;i<=m;i++){
    		cin>>need[i];//输入需释放的囚犯编号 
    	}
    	sort(need+1,need+m+1);//排序，后期更方便状态转移 
		need[0]=0,need[m+1]=n+1;//假设0号牢房与m+1号牢房均有人，方便状态转移
    	for(int len=1;len<=m;len++){
    		for(int l=1;l+len-1<=m;l++){
    			int r=l+len-1;
    			f[l][r]=INT_MAX;
    			for(int k=l;k<=r;k++){
    				f[l][r]=min(f[l][r],f[l][k-1]+f[k+1][r]+need[r+1]-need[l-1]-1-1);
					//状态转移方程 
    			}
    		}
    	}
    	cout<<"Case #"<<a11+1<<": "<<f[1][m]<<endl;//输出 
	}
    return 0;//好习惯 
}
```

---

## 作者：yihang2011 (赞：0)

### [P13439 [GCJ 2009 #1C] Bribe the Prisoners](https://www.luogu.com.cn/problem/P13439)

区间 DP 题。

本题解记 $a_i$ 为第 $i$ 个需要释放的犯人所在牢房。

可以记 $f_{i, j}$ 为释放 $a_i$ 与 $a_j$ 之间的犯人（即不包括 $a_i$ 和 $a_j$）所需要的最少金币数。

枚举 $i$，$j$，以及区间内最先释放的 $k$，$a_i$ 与 $a_j$ 之间有 $a_j - a_i - 1$ 间牢房，而释放了 $k$ 又少了一间，所以释放 $k$ 的成本为 $a_j - a_i - 2$。

释放 $k$ 后，$f_{i, j}$ 划分为 $f_{i, k}$ 与 $f_{k, j}$ 两个子问题。

所以状态转移方程为：

$$
f_{i, j} = \min_{i < k < j}\{f_{i, k} + f_{k, j} + a_j - a_i - 2\}
$$

初始状态为 $f = +\infty$，$f_{i, i + 1(0 \le i \le q)} = 0$。

为方便处理边界，我们可以令 $a_0 = 0, a_{q + 1} = p + 1$，则最终答案为 $f_{0, q + 1}$。

时间复杂度 $\mathcal{O}(q^3)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define seta(f, x) memset(f, x, sizeof f)
using ll = long long;
#define gc getchar()
ll read() { ll x = 0, f = 1; char ch = gc; while (ch < '0' || ch > '9') { if (ch == '-') { f = -1; } ch = gc; } while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0', ch = gc; } return x * f; }
#define rd read()
void write(const string& s) { for (char c : s) { putchar(c); } }
void write(ll x) { if (x < 0) { putchar('-'), x = -x; } if (x > 9) { write(x / 10); } putchar(x % 10 + '0'); }
void write(double x, int len) { ll i = x, s = round(1.0 * (x - i) * (pow(10, len))); write(i); putchar('.'); write(s); } 
template<typename... Args> void wrt(ll x, Args... rest) { write(x); if constexpr (sizeof...(rest) > 0) { putchar(' '); wrt(rest...); } }
template<typename... Args> void wrln(ll x, Args... rest) { write(x); if constexpr (sizeof...(rest) > 0) { putchar(' '); wrln(rest...); } else { putchar('\n'); } }
#define wln(x) write(x); putchar('\n')
#define wt(x) write(x); putchar(' ')

const int P = 1e3 + 10, Q = 1e2 + 10;
int f[Q][Q];
int a[Q];
int p, q;

int solve() {
    seta(f, 0x3f), seta(a, 0);
    p = rd, q = rd;
    for (int i = 1; i <= q; i++) {
        a[i] = rd;
        f[i - 1][i] = 0;
    }
    f[q][q + 1] = 0;
    a[0] = 0, a[q + 1] = p + 1;
    for (int len = 2; len <= q + 1; len++) {
        for (int i = 0, j = len; j <= q + 1; i++, j++) {
            for (int k = i + 1; k < j; k++) {
                f[i][j] = min(f[i][j], f[i][k] + f[k][j] + a[j] - a[i] - 2);
            }
        }
    }
    return f[0][q + 1];
}

int main() {
    int T = rd;
    for (int i = 1; i <= T; i++) {
        write("Case #"), write(i), wt(":"), wln(solve());
    }
    return 0;
}
```

[AC Record](https://www.luogu.com.cn/record/230577979)

---

