# [WFOI - 01] 猜数（guess）

## 题目背景

**这是一道交互题。交互库自适应。请注意特殊的时间限制。**

**每次输出后请记得清空缓存**

简化题意：[$\texttt{Link}$](https://www.luogu.com.cn/paste/xx7sa8go)。

## 题目描述

你需要猜一个正整数 $q$，保证 $q\in [1,n]$；

你每次可以用诸如 `? x y` 的询问，交互库会在 $[x,y]$ 中指定选择一个数 $z$；

然后交互库会输出形如 `u v` 的回答，表示指定的数是 $u$，其与 $q$ 的关系为 $v$；

具体地，
- 当交互库返回的 $v=0$ 时，表示 $u<q$；
- 当交互库返回的 $v=1$ 时，表示 $u=q$；
- 当交互库返回的 $v=2$ 时，表示 $u>q$。

而一次询问的代价是 $\dfrac{1}{y-x+1}$；

你可以通过 `! x` 输出你认为正确的答案。

现在你要求出 $q$。

------------

设你的代价为 $x$，你每个测试点获得的分数和你的总代价有如下关系（每个测试点满分 $10$ 分）：


- 若 $x\le 1.9813035$，则你可以得到 $\text{10 pts}$；
- 若 $1.9813035 < x \le 12$，则你可以得到 $\lfloor(12-x)\times0.7 \div 1.00186965\rfloor  \text{ pts}$。
- 若 $x\ge12$，则你可以得到 $\text{0 pts}$。


需要注意的是，在每一次操作后，需要调用以下函数刷新缓存：

- 对于 C/C++：`fflush(stdout)`；
- 对于 C++：`std::cout << std::flush`；
- 对于 Java：`System.out.flush()`；
- 对于 Python：`stdout.flush()`；
- 对于 Pascal：`flush(output)`；
- 对于其他语言，请自行查阅对应语言的帮助文档。

### 交互格式

一开始交互库会给你 $n$，

然后你可以按题目描述中的方式进行询问或回答答案；

在回答后请立即退出程序。

## 说明/提示

- **样例 $1$ 解释：**
	
    询问后发现 $1<x\le2$，所以 $x=2$；
    
- **样例 $2$ 解释：** 

    第一次询问后发现 $1<x\le3$；
    
    第二次询问后发现 $1<x<3$，所以 $x=2$；

**【数据规模与约定】**

| 测试点编号 | $n \le$ | 测试点编号 | $n\le$ |
| :-: | :-: | :-: | :-: |
| $\texttt{1}$ | $1$ | $\texttt{6}$ | $2\times 10^3$ |
| $\texttt{2}$ | $7$ | $\texttt{7}$ | $10^4$ |
| $\texttt{3}$ | $20$ | $\texttt{8}$ | $5\times 10^4$ |
| $\texttt{4}$ | $80$ | $\texttt{9}$ | $10^5$ |
| $\texttt{5}$ | $300$ | $\texttt{10}$ | $10^5$ |

对于 $100\%$ 的数据，$1\le n\le10^5$，$1\le q,\forall u\le n$，$\forall v\in\{0,1,2\}$。

保证每询问一次交互库时间是 $\mathcal O(1)$ 的。

## 样例 #1

### 输入

```
2

1 0
 ```

### 输出

```

? 1 2

! 2```

## 样例 #2

### 输入

```
3

1 0

3 2
 ```

### 输出

```

? 1 3

? 3 3

! 2```

# 题解

## 作者：yzy1 (赞：5)

## 题目大意

有一个数 $x \in [1,n]$，并非一开始就确定，每次你可以选择一个区间 $[a,b]$（花费 $\dfrac{1}{b-a+1}$ 的代价），交互库会选择一个数 $c \in [a,b]$ 并告诉你 $c$ 与 $x$ 的大小关系，现在你需要在 $1.9813035$ 总代价内求出 $x$。

## 做法

考虑 DP，设 $dp(i)$ 表示当前要猜的是大小为 $i$ 的区间时，要猜到数字最差情况所耗费的代价。则有：
$$
dp(i)=\begin{cases}
0 & i\le 1\\
\min_{j=1}^i \frac 1 j + dp(\max(L-1,i-L,L+j-2,i-L-j+1)) & i>1
\end{cases}
$$
其中 $L$ 代表 $\lfloor \dfrac{1+i}2 \rfloor - \lfloor \dfrac{j-1} 2 \rfloor$。可以发现，$dp(10^5)\simeq 1.98130349020495$，可见这个做法正确性没有问题。DP 的同时记录一下每个状态是从哪个状态转移来的，就得到了最优决策点。每次询问时用预处理出来的最优决策点作答。但是发现这个 DP 是 $O(n^2)$ 的，时间复杂度过高，无法通过此题，考虑另一种做法——打表。

---

先将每个状态 $dp(i)$ 所对应的最优转移来源 $dp1(i)$ 进行打表。代码：

```cpp
int n,dp1[N]; lf dp2[N];

signed main() {
  dp2[0] = 0;
  dp2[1] = 0;
  printf("1\n");
  rep(i, 2, 1e5) {
    dp2[i] = INFINITY;
    int mid = (1 + i) / 2;
    re(j, i) {
      int l = mid - (j - 1) / 2, r = l + j - 1,
          res = max({l - 1, i - l, r - 1, i - r});
      if (dp2[res] + 1.l / j < dp2[i])
        dp2[i] = dp2[res] + 1.l / j, dp1[i] = j;
    }
    printf("%d\n",dp1[i]);
  }
  return 0;
}
```



你会发现这个表太大了导致提交不到 OJ 上。我们可以先把数据扔进 Excel 里可视化：

![](https://cdn.luogu.com.cn/upload/image_hosting/rlkwd8xj.png)

可以发现，数据中形成了几条直线，所以可以只将前 $10^4$ 个数据打成表，将后面的数据拟合成一个分段函数：
$$
F(i)=\begin{cases}
\text{biao}_i & i\le 1000\\
4938 & i\le 13383\\
7000 & i\le 19690\\
9900 & i \le 27902\\
14030 & i \le 39555\\
19853 & i \le 55906\\
28114 & i \le 79133\\
39600 & i \le 10^5
\end{cases}
$$
利用这个函数作为二分的决策点，可写出以下代码：

```cpp
const int biao[11234]={/*省略数据表*/};
int F(int x) {
  if (x <= 10000)
    return biao[x];
  if (x <= 13383)
    return 4938;
  if (x <= 19690)
    return 7000;
  if (x <= 27902)
    return 9900;
  if (x <= 39555)
    return 14030;
  if (x <= 55906)
    return 19853;
  if (x <= 79133)
    return 28114;
  return 39600;
}
void Ans(int x) {
  cout << "! " << x << '\n' << flush;
  exit(0);
}
pair<int, int> Ask(int l, int r) {
  cout << "? " << l << ' ' << r << '\n' << flush;
  int x, y;
  cin >> x >> y;
  return {x, y};
}
void ErFen(int l, int r) {
  if (l == r)
    Ans(l);
  int len = r - l + 1, mid = (l + r) / 2, res = F(len),
      L = mid - (res - 1) / 2, R = L + res - 1;
  auto [u, v] = Ask(L, R);
  if (v == 1)
    Ans(u);
  else if (v == 2)
    ErFen(l, u - 1);
  else
    ErFen(u + 1, r);
}
```

代码量就降到了 48k，这就可以交到 OJ 上了。这个代码得到了 99pt，最后一个点超出标准次数 $2\times 10^{-7}$ 次。

---

既然函数拟合的不够好，可以再用 DP 把函数上下扰动调整一下。DP 的第二维改成从 $F(i)-\Delta$ 枚举到 $F(i)+\Delta$。采用 $\Delta=5$ 时，可以通过此题。

```cpp
signed main() {
  dp2[0] = 0;
  dp2[1] = 0;
  rep(i, 2, 1e5) {
    dp2[i] = INFINITY;
    int mid = (1 + i) / 2;
    rep(j, max(1, F(i) - 5), min(i, F(i) + 5)) {
      int l = mid - (j - 1) / 2, r = l + j - 1,
          res = max({l - 1, i - l, r - 1, i - r});
      if (dp2[res] + 1.l / j < dp2[i])
        dp2[i] = dp2[res] + 1.l / j, dp1[i] = j;
    }
  }
  cin >> n;
  ErFen(1, n);
  return 0;
}
```

---

## 作者：€€£ (赞：5)

### 题解（guess）

#### 算法1：我会二分！

每次暴力二分，总代价为 $1 \times \log n$

#### 算法2：我会暴力！

记录当前你能确定的范围，每次询问这个范围，总代价 $\ln n$​

#### 算法3：我会DP！

考虑设 $f(n)$​ 表示确定一个区间长度为 $n$​ 的期望最小次数

设 $g(n)$ 表示区间长度为 $n$ 的第一次转移是多少

我们枚举其第一次选择的两个端点，然后暴力计算贡献

时间复杂度 $O(n^3)$​

##### 优化1：我会观察性质！

显然，第一次选取的端点越靠中间越好

于是我们优化成了 $O(n^2)$​

##### 优化4：我会剪枝！

我们发现，一个 $g(n)$ 最小是 $g(n-1)-1$，最大是 $\dfrac{n}{2}+2$

于是我们发现跑得飞快​​

还有一个优化是发现 $g(n)$ 与 $n$ 同奇偶

常数很小的话可能可以通过此题

##### 优化5：我会打表！

我们发现，$g(n)$ 与 $g(n-1)$ 差值很大的 $n$ 数量很少，于是我们手动打表即可得到一个复杂度极为优秀的算法

于是我们优化成了 $O(n)$​

可以通过此题

另：好像std在最坏情况下代价是1.98……但应该不卡

---

## 作者：Purslane (赞：2)

# Solution

首先我们要理解这一类交互模型，也就是**交互库自适应**。也就是说，你要的答案会**根据你的询问而改变**，从而卡掉一些复杂度不能保证的做法。说白了，交互库是一个丧心病狂的 Hacker。它会**引导你的交互代码进行最多次的操作**。

对于本题，很容易发现，如果 $n$ 越大，我们的代价和就会越大。

假设当前你已经确定了 $q$ 所在的范围是 $[1,n]$，你询问了 $(l,r)$。交互库会想办法让你的询问区间缩短最小。如何实现？很显然，交互库可以返回“这个数比 $l$ 大”或者“这个数比 $r$ 小”。这样可以让你的下一个区间的长度为 $\max\{r-1,n-l\}$。

因此，我们可以得到一个 DP，记录 $dp_n$ 为长度为 $n$ 的区间，保证能确定唯一值的代价的最小值。得到：

$$dp_n = \min_{1 \le l \le r \le n}\{\frac{1}{r-l+1} + dp_{\max\{r-1,n-l\}}\}$$

这个是不好处理的。考虑如果 $\max\{r-1,n-l \} \le m$，得到 $r \le m+1$，$l \ge n-m$。因此 $r-l+1 \le 2m-n+2$，而且必须有 $r=m+1$，$l=n-m$。因此，得到：

$$dp_n = \min_{\lceil \frac{n-1}{2} \rceil \le m \le n-1} \{ \frac{1}{2m-n+2} + dp_m\}$$

其中 $dp_1=0$。

很容易发现，由于 $f(x) = \dfrac{1}{2x-n+2}$ 在 $x>0$ 时二阶导大于零，所以该 DP 具有决策单调性。可以使用二分栈在 $O(n \log n)$ 复杂度内完成，顺带记录一下最优转移。

然后根据最优转移模拟即可。跑~的~飞~快~。

打表？不可能的！

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int n,ori[MAXN];
long double dp[MAXN];
struct Node {int l,r,ori;};
int tot; Node st[MAXN];
long double f(int x,int v) {return dp[x]+1.0/(2*x+2-v);}
int bfind(int l,int r,int x,int y) {
	int ans=r+1;
	while(l<=r) {
		int mid=l+r>>1;
		if(f(x,mid)>f(y,mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
int find_bl(int l,int r,int v) {
	int ans=-1;
	while(l<=r) {
		int mid=l+r>>1;
		if(st[mid].l<=v) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
int solve(int l,int r) {
	if(l==r) return l;
	int R=l+ori[r-l+1],L=r-ori[r-l+1];
	cout<<"? "<<L<<' '<<R<<endl; cout.flush();
	int u,v; cin>>u>>v;
	if(v==0) return solve(u+1,r);
	if(v==1) return u;
	if(v==2) return solve(l,u-1);
}
int main() {
	cin>>n;
	st[++tot]={min(n,2),min(n,3),1};
	ffor(i,2,n) {
		int pos=find_bl(1,tot,i);
		dp[i]=f(st[pos].ori,i),ori[i]=st[pos].ori;
		int R=min(n,2*i+1);
		while(tot) {
			int r=st[tot].r,l=max(i+1,st[tot].l);
			int lst=bfind(l,r,st[tot].ori,i);
			if(lst>st[tot].r) {
				if(lst<=R) st[++tot]={lst,R,i};	
				break ;
			}
			else if(lst!=st[tot].l) {
				st[tot].r=lst-1;
				st[++tot].l=lst,st[tot].r=R,st[tot].ori=i;
			}
			else tot--;
		}
	}
	int ans=solve(1,n);
	cout<<"! "<<ans<<endl; cout.flush();
	return 0;
}
```

---

## 作者：int08 (赞：1)

## 前言
那一天，小 F 终于感受到了根据答案倒推过程的爽感。

# Solution
对于自适应交互的一个固定思考方向是思考交互库会如何来卡你。

很显然任意时候可能成为答案的位置是一段区间，交互库就会尽可能地让剩下的区间长，它必然会选择你询问的区间中位置最偏的那个，并告诉你答案在这个点到较远的端点之间。

这告诉我们：询问的区间应该是对称的，如果不对称，补齐短段不会让最坏情况更劣。

进一步发现，在剩下的区间长度为定值的时候询问的区间长度也是固定的，我们可以用 DP 求出来：

设 $dp_i$ 表示答案所在区间长度为 $i$ 时候问出来所需最小代价，边界有 $dp_1=0,dp_2=0.5$，转移时候枚举询问区间的长度即可。

算出来发现 $dp_{10^5}$ 确实就是题目中要求的那个数，看来我们的做法是正确的。

但是此时复杂度为 $O(n^2)$，不能通过。

优化 DP？不需要的！

因为这题的 DP 过程固定，考虑打表。

但是直接打完又会超过码长限制。

观察数据，我们发现最优转移点形如一段一段的，但是每一段之间具体又是乱的。

没有关系！考虑原来我们枚举了所有可能的询问区间长度，现在我们可以只在打的表的结果**附近**枚举，能够让程序 $0.3$ 秒出结果就行了。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 114514
double dp[N];
int n,i,j,tr[N],l[N],r[N],u,v;
#define set(a,b,x,y) for(i=a;i<=b;i++) l[i]=x,r[i]=y
void solve(int l,int r)
{
	if(l==r)
	{
		cout<<"! "<<l<<endl;
		exit(0);
	}
	int len=r-l+1;
	int L=(l+r+1)/2-tr[len]/2,R=(l+r)/2+tr[len]/2;
	cout<<"? "<<L<<" "<<R<<endl;
	cin>>u>>v;
	if(v==0) solve(u+1,r);
	if(v==2) solve(l,u-1);
	cout<<"! "<<u<<endl;
	exit(0);
}
int main()
{
	cin>>n;
	for(i=1;i<=n;i++) dp[i]=1e9;
	dp[1]=0,dp[2]=0.5,dp[3]=5.0/6.0;
	tr[2]=2,tr[3]=3;
	set(1,19773,2,7500);set(19774,27984,9500,10000);set(27985,39595,13700,14200);set(39596,56027,19500,20000);set(56028,79206,27500,28500);set(79207,100000,39000,40000);
	for(i=4;i<=n;i++)
		for(j=l[i]+(i&1);j<=min(r[i],i);j+=2) if(dp[i]>dp[i/2-1+(j+1)/2]+1.0/double(j)) dp[i]=dp[i/2-1+(j+1)/2]+1.0/double(j),tr[i]=j;
//	for(i=1;i<=n;i++) printf("%d : %.10f %d\n",i,dp[i],tr[i]);
	solve(1,n);
}
```
# The End.

---

