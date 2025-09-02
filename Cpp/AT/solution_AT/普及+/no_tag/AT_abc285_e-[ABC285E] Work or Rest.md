# [ABC285E] Work or Rest

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc285/tasks/abc285_e

高橋君が住む世界の一週間は $ N $ 日からなります。  
 一週間は曜日 $ 1,2,\dots,N $ と進んでいき、曜日 $ N $ が終わると次の週の曜日 $ 1 $ が始まります。

ABC 国の国王である高橋君は、各曜日に「平日」「休日」のどちらかを割り当てます。この割り当ては毎週同じでなければなりません。また、少なくとも $ 1 $ つの曜日を「休日」に割り当てなければなりません。

この条件の下で、曜日 $ i $ の生産量は長さ $ N $ の数列 $ A $ を用いて以下のように定義されます。

- 曜日 $ i $ が「休日」である場合は $ 0 $
- 曜日 $ i $ が「平日」のとき、直前の休日が $ x $ 日前、直後の休日が $ y $ 日後である場合は $ A_{\min(x,y)} $
  - 割り当ては毎週繰り返されるため、 直前 / 直後 の「休日」が当日とは別の週に属する可能性があることに注意してください。詳しくはサンプルを参照してください。
 
上手く割り当てを決めたときの一週間当たりの生産量の最大値を答えてください。  
 但し、一週間当たりの生産量とは曜日 $ 1,2,\dots,N $ の生産量の総和を指します。

## 说明/提示

### 制約

- 入力はすべて整数
- $ 1\ \le\ N\ \le\ 5000 $
- $ 1\ \le\ A_i\ \le\ 10^9 $
 
### Sample Explanation 1

例えば曜日 $ 2,4 $ を「休日」、残りを「平日」に割り当てることで、以下のように一週間当たりの生産量 $ 50 $ を達成できます。 - 曜日 $ 1 $ ... $ x=4,y=1 $ なので、この曜日の生産量は $ A_1\ =\ 10 $ である。 - 曜日 $ 2 $ ... 「休日」であるので、この曜日の生産量は $ 0 $ である。 - 曜日 $ 3 $ ... $ x=1,y=1 $ なので、この曜日の生産量は $ A_1\ =\ 10 $ である。 - 曜日 $ 4 $ ... 「休日」であるので、この曜日の生産量は $ 0 $ である。 - 曜日 $ 5 $ ... $ x=1,y=4 $ なので、この曜日の生産量は $ A_1\ =\ 10 $ である。 - 曜日 $ 6 $ ... $ x=2,y=3 $ なので、この曜日の生産量は $ A_2\ =\ 10 $ である。 - 曜日 $ 7 $ ... $ x=3,y=2 $ なので、この曜日の生産量は $ A_2\ =\ 10 $ である。 一週間当たりの生産量を $ 51 $ 以上にすることはできません。

## 样例 #1

### 输入

```
7
10 10 1 1 1 1 1```

### 输出

```
50```

## 样例 #2

### 输入

```
10
200000000 500000000 1000000000 800000000 100000000 80000000 600000 900000000 1 20```

### 输出

```
5100000000```

## 样例 #3

### 输入

```
20
38 7719 21238 2437 8855 11797 8365 32285 10450 30612 5853 28100 1142 281 20537 15921 8945 26285 2997 14680```

### 输出

```
236980```

# 题解

## 作者：FFTotoro (赞：18)

## 解法

解题之前，我们先定义一个数列 $S$，其中 $S_i$ 代表若一周有 $i+1$ 天且只有 $1$ 个休息日（即 $i$ 个工作日）时的工作效率。

由题目定义有：

若 $i$ 为奇数，$S_i=\left(2\sum\limits_{j=1}^{\left\lfloor i/2\right\rfloor}A_j\right)+A_{\left\lceil i/2\right\rceil}$；

否则 $S_i=2\sum\limits_{j=1}^{i/2}A_j$。

令 $F_i$ 为一周有 $i$ 天时的最大工作效率，这个 $F_i$ 的来源有两种情况：

- 一周有且仅有 $1$ 个休息日：$F_i=S_{i-1}$；

- 一周不止 $1$ 个休息日：令第一个休息日为周一，枚举第二个休息日，将整周划为两部分。然后我们就可以发现，若两个部分分别是 $x$ 天和 $y$ 天，根据 $F$ 的定义，工作效率的最大值就为 $F_{x+1}+F_{y+1}$。更加形式化地说，如果一周不止一个休息日，那么有 $F_i=\max\limits_{j=1}^{i-3} F_{j+1}+F_{i-1-j}$。

两者取较大值即可。

最终答案即为 $F_N$。

如果你把上面的公式拿起来再细细回味，你就会发现它其实就是个**完全背包**。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long // 记得 long long
using namespace std;
int a[5001],s[5001],f[5001];
main(){
  ios::sync_with_stdio(false);
  int n; cin>>n;
  for(int i=1;i<=n;i++)cin>>a[i];
  for(int i=1;i<=n;i++)
    if(i&1)s[i]=s[i-1]+a[(i>>1)+1];
    else for(int j=1;j<=i>>1;j++)s[i]+=a[j]<<1; // 推导 S 数组
  for(int i=2;i<=n;i++){
    f[i]=s[i-1]; // 第一种情况
    for(int j=1;j<i-2;j++) // 第二种情况，枚举
      f[i]=max(f[i],f[j+1]+f[i-j-1]); // 转移，取较大值
  }
  cout<<f[n]<<endl; // 答案输出
  return 0;
}
```

## 后记

还记得去年的时候，我身边的同学都被简单的背包类动态规划搞得晕头转向，大家做背包基本都是运用“背模板”的方法。我那时常常对同学们说：“背什么模板啊，我一般都考场上手推的！”他们总是惊叹不已。

这次 ABC 中，E 题是个很不明显的背包。然而我的手推能力就在这里体现出来了，我花了 $20$ 分钟，在草稿纸上写写画画。等到同学们发现了题目是个背包 DP 再提交时，发现我早已 AC——谁说“手推”就一定输“背模板”？

一时对模板的熟悉固然好，但是对算法“不透彻”的了解，在长远上看，是十分致命的。

---

## 作者：Hell0_W0rld (赞：13)

# [ABC285E](https://atcoder.jp/contests/abc285/tasks/abc285_e) 题解
*1466。

赛场 AC 人数居然只有 786 人，我做的时候感觉不难啊。~~（我才不会说我 D 做的时间比 E 长）~~

## 题目大意
`AtCoder` 王国一个礼拜有 $N$ 天。国王高桥准备把每一天安排为 节假日或者工作日。如果 $i$ 号是工作日，那么动力是 $A_{\min (x,y)}$，其中 $x$ 和 $y$ 是它离前一个或后一个节假日的天数。
## 解题思路
我们发现，如果 ${d_1,d_2,\cdots,d_k}$ 是节假日，那么 ${d_1+x,d_2+x,\cdots,d_k+x}$ 是节假日答案不变。所以我们令第 $N$ 天是节假日。

如果 $l,r$ 为节假日，那么 $[l+1,r-1]$ 的工作量怎么求呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/638k3xvf.png)

我们发现，这个形成一个山峰的样子！

所以，我们用前缀和 $O(1)$ 可以求解。注意边界特判（预防）。

### Code：
```cpp
ll cost(ll l,ll r){
	if(l==r)return 0;
	l++,r--;
	ll len=(r-l+1)/2;
	ll res=sum[len]*2;
	if(l%2==r%2){
		res+=a[len+1];
	}
	return res;
}
```
### Continue$\to$
我们发现，是一个序列切割的问题。于是我们可以用 $\mathrm{dp}$：

$f_{i,j}$ 表示上一个节假日为 $j$，$i$ 也为节假日，前 $i$ 天的最大动力。

显然有转移方程：$f_{i,j}=\operatorname{cost}(i,j)+\max\limits_{k<j}\{f_{k,j}\}$。

这样转移是 $O(n^3)$ 的，无法通过。

注意到 $\max$ 是一个定值，我们可以令 $\mathrm{mx}_j=\max\limits_{k<j}\{f_{k,j}\}$。这样转移是 $O(n^2)$ 的。

最后答案显然输出 $\mathrm{mx}_n$。

## 完整代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ull unsigned long long
#define rep(i,l,r) for(register ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(register ll i=(r);i>=(l);--i)
#define repD(i,u,E) for(register ll i=hd[u];i;i=E[i].nxt)
#define all(x) x.begin(),x.end()
using namespace std;
void upd_s(ll&x,ll v){x=min(x,v);}
void upd_b(ll&x,ll v){x=max(x,v);}
const ll N=5009;
ll n,a[N],sum[N];
ll cost(ll l,ll r){//l号是节假日，r也是，求[l+1,r-1]的动力 
	if(l==r)return 0;
	l++,r--;
	ll len=(r-l+1)/2;
	ll res=sum[len]*2;
	if(l%2==r%2){
		res+=a[len+1];
	}
	return res;
}
ll f[N][N],mx[N];
int main(){
	cin>>n;
	rep(i,1,n)cin>>a[i];
	rep(i,1,n)sum[i]=sum[i-1]+a[i];
	rep(i,1,n)rep(j,0,i-1){//前i天，上一个节假日j，i为节假日，前i天的最大动力（j=0即i为第一个节假日） 
		f[i][j]=mx[j]+cost(j,i);
		mx[i]=max(mx[i],f[i][j]);
	}
	cout<<mx[n]<<endl;
	return 0;
}
```

给个赞再走呗 qwq……

---

## 作者：DE_aemmprty (赞：6)

### E 题

**题目大意：**

一周有 $N$ 天，你可以将每周中的某些天设为休息日，其余天设为工作日。每周都至少要有一天为休息日。

每天都有一个生产值，计算方法如下：

若这天为休息日，生产值为 $0$。

若这天为工作日，生产值为 $A_{\min\{x,y\}}$，其中 $A$ 为给定的序列，$x,y$ 分别指上一个休息日在 $x$ 天前，下一个休息日在 $y$ 天后。

问通过分配休息日，每周 $N$ 天的生产值之和最大可以是多少。

**提示：**

对于 $100\%$ 的数据：

* $1 \leq N \leq 5000$
* $1 \leq A_i \leq 10^9$

**解法分析：**

看到这一道题的第一想法就是 DP。

设 $f_i$ 为前 $i$ 天的最大生产值，则容易得知 $f_0 = 0$。接着对 $f_1$ 的取值做分析，虽然这 $N$ 天是周期进行的，但我们一定能找到一段区间，使得第一天为休息日，这样的好处就是不必考虑周期的问题，所以 $f_1 = 0$。

然后考虑转移。我们可以将每一个连续的工作日区间当作一个个体，所以枚举 $j$ 使得第 $i - j + 1$ 天到第 $i$ 天都是工作日并且第 $i - j$ 天为休息日，此时可以从 $f_{i - j - 1}$ 转移到 $f_i$，即 $f_i = \min{\{f_{i - j - 1} + \text{这段区间的生产值}\}}$。

最后考虑对于每一段工作日区间的生产值计算。假设长度为 $n$, $s_i = a_1 + a_2 + \cdots + a_i$，则当 $n$ 为奇数时，生产值为 $a_1 + a_2 + \cdots + a_{\frac{n+1}{2}} + \cdots + a_2 + a_1 = s_{\frac{n+1}{2} - 1} \times 2 + a_{\frac{n + 1}{2}}$，否则生产值为 $a_1+a_2+\cdots+a_{\frac{n}{2}}+a_{\frac{n}{2}}+\cdots +a_2+a_1=s_{\frac{n}{2}}\times2$。

于是整道题就完成了。

**AC Code**
```cpp
# include <bits/stdc++.h>
using namespace std;

# define ll long long
# define lf double
# define int ll
# define GO(i,a,b) for(ll i = a; i <= b; i ++)
# define RO(i,b,a) for(ll i = b; i >= a; i --)
# define FO(i,u,head,e) for(int i = head[u]; i; i = e[i].next)
# define CI const int
# define pii pair<int,int>
# define MP(a,b) make_pair(a, b)
# define PB push_back
# define mem(a,x) memset(a, x, sizeof a)
# define F first
# define S second

CI maxn = 10007;

int n;
int a[maxn];
int s[maxn];
int f[maxn];

int cal(int len){
	if (len % 2 == 0) return s[len / 2] * 2;
	return s[len / 2] * 2 + a[len / 2 + 1];
}

signed main(){
	cin >> n;
	GO (i, 1, n) scanf("%lld", &a[i]), s[i] = s[i - 1] + a[i];
	GO (i, n + 1, 2 * n) a[i] = a[i - n], s[i] = s[i - 1] + a[i];
	int ans = -2e18;
	GO (i, 2, n){
		f[i] = -2e18;
		GO (j, 0, i - 1){
			f[i] = max(f[i], f[i - j - 1] + cal(j));
		}
	}
	cout << f[n];
	return 0;
}
```
**后文：**

感谢 [$\color{black}\texttt{@\_\_l\_z\_c\_\_}$](https://www.luogu.com.cn/user/675888) 纠正了题解中的一个错误，在此受蒟蒻一拜/bx/bx/bx。

---

## 作者：CarroT1212 (赞：3)

#### 题目大意

一周有 $N$ 天，你可以将每周中的某些天设为休息日，其余天设为工作日。每周都至少要有一天为休息日。

每天都有一个生产值，计算方法如下：

+ 若这天为休息日，生产值为 $0$。
+ 若这天为工作日，生产值为 $A_{\min(x,y)}$，其中 $A$ 为给定的序列，$x,y$ 分别指上一个休息日在 $x$ 天前，下一个休息日在 $y$ 天后。

问通过分配休息日，每周 $N$ 天的生产值之和最大可以是多少。

数据范围：$1 \le N \le 5000$，$1 \le A_i \le 10^9$。

#### 解法分析

这个题目加上数据范围一看就很 DP，但是 DP 初始状态好像不是很好确定。

首先可以发现，由于是周期，将这 $N$ 天的休息日分配进行循环移位后对答案没有影响。又因为题目要求每周必须至少有一个休息日，所以我们可以直接把第 $1$ 天固定为休息日，然后从第 $2$ 天开始 DP，这样就好处理很多了。

设 $dp_i$ 为第 $i$ 天为休息日且第 $(i+1)$ 至 $N$ 天都不为休息日的最大生产值之和，$cal(i)$ 为连续 $i$ 天都为工作日时这 $i$ 天的生产值之和（这个可以通过预处理出 $A$ 的前缀和来计算）。初始化 $dp_1=cal(N-1)$，则我们可以得到转移方程为 $dp_i=\max\limits_{j<i}\{dp_j-cal(N-j)+cal(i-j-1)+cal(N-i)\}$。最后的答案为 $\max\{dp_i\}$。

#### 代码

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
using namespace std;
const int N=5007;
int n;
ll a[N],sum[N],dp[N],ans;
ll cal(ll len) { return sum[len/2]*2+(len&1?a[len/2+1]:0); }
int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&a[i]),sum[i]=sum[i-1]+a[i];
	dp[1]=cal(n-1),ans=dp[1];
	for (int i=2;i<=n;i++) {
		for (int j=1;j<i;j++) dp[i]=max(dp[i],dp[j]-cal(n-j)+cal(i-j-1)+cal(n-i));
		ans=max(ans,dp[i]);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：cancan123456 (赞：2)

考虑 DP，钦定第 $1$ 天休息，设 $f_i$ 为考虑了前 $i$ 天，第 $i$ 天休息的最大生产力，那么有边界条件、转移：

$$f_1=0$$

$$f_i=\max_{j=1}^{i-1}f_j+w(j-i-1)$$

其中 $w(i)$ 表示连续 $i$ 天工作的生产力，显然可以用前缀和 $O(1)$ 求出。

则答案为 $\max_{i=1}^nf_i+w(n-i)$。

---

## 作者：FReQuenter (赞：2)

## 思路

这是一个环形的问题，那我们不妨设一个休息日为起点，把它变成一条链。

我们考虑 DP。

设 $f_{i,j}$ 表示当前已经过去了 $i$ 天（破环成链后）且有 $j$ 个连续的工作日。

转移有两种情况：

- 下一天为工作日，则 $f_{i,j}=f_{i-1,j-1}$。

- 下一天休息，则 $f_{i,0}=\max\{f_{i-1,j}+x_j\}$，这里的 $x_j$ 表示连续 $j$ 天工作所带来的贡献。

那么这个贡献如何求：我们可以预处理，$x_j=\sum^{j}_{i=1}a_{\lfloor\frac{i+1}{2}\rfloor}$。

DP的初值就是除了 $f_{1,0}=0$，其余均为 $-\inf$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,a[5005],sum[5005],f[5005][5005];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[(i+1)>>1];
	memset(f,-0x3f,sizeof(f));
	f[1][0]=0;
	int maxn=f[1][0]+sum[0];
	for(int i=2;i<=n;i++){
		for(int j=0;j<=n;j++){
			if(j) f[i][j]=max(f[i][j],f[i-1][j-1]);
			if(!j) f[i][j]=max(f[i][j],maxn);
		}
		maxn=-0x3f3f3f3f;
		for(int j=0;j<=n;j++) maxn=max(maxn,f[i][j]+sum[j]);
	}
//	for(int i=1;i<=n;i++){
//		for(int j=0;j<=n;j++){
//			cout<<f[i][j]<<' ';
//		}
//		cout<<endl;
//	}
	for(int i=1;i<=n;i++) ans=max(ans,f[n][i]+sum[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：Lyu_echo (赞：2)

# AtCoder Beginner Contest 285 E-Work or Rest Solution

## 题目大意

这是一个异世界。

定义一周有 $N$ 天。每一天存在工作日和休息日两种状态。

给定长度为 $N$ 的序列 $A$。

定义一周中第 $i$ 天的生产力如下：

- 若第 $i$ 天是休息日，则生产力 $=0$；
- 若第 $i$ 天是工作日，则生产力 $=A_{\operatorname{min}(x,y)}$，$x$ 为距离过去最近休息日天数，$y$ 为距离未来最近休息日天数。
  - 注意，周与周之间是连贯的。也就是说，一周的第一天的过去可以是上一周。

每周至少休息一天。求一周的最大生产力。



## 解题思路

不难发现，每两个休息日之间的所有工作日的生产力是固定的。

我们设 $f_i$ 为一周中第 $i$ 天休息的最大生产力值。

讨论最近的过去休息日，设为 $j$。也就是说，在第 $i$ 天至第 $j$ 天全部为工作日。

明显的，如上述，$f_i = \operatorname{max}_{j = 1}^{i} (f_j + P(j,i))$，其中 $p(j,i)$ 表示 $j+1$ 天到 $i-1$ 天的生产力。

总体时间复杂度 $\mathcal{O}(N^3)$，考虑优化。

对于状态转移方程 $f_i = \operatorname{max}_{j = 1}^{i} (f_j + P(j,i))$， 枚举 $i$, $j$ 并不能优化。所以瓶颈在于计算生产力 $p(j,i)$。

展开 $p(j,i)$。

$p(j,i) =\begin{aligned}
\begin{cases}
 A_1 + \dots + A_{\lceil \frac{i}{2} \rceil} + \dots + A_1 \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ i\text{ 为奇数}\\
 A_1 + \dots + A_{\lceil \frac{i}{2} \rceil} + A_{\lceil \frac{i}{2} \rceil} + \dots + A_1 \ \ i\text{ 为偶数}
\end{cases}
\end{aligned}$

使用前缀和预处理优化即可。

考虑到一周的第 $n$ 天贡献可能和下一周的第一天贡献重复，我们固定每一周的休息日为第 1 天，从第 2 天开始递推，答案即为 $f_{n+1}$。

总体时间复杂度 $\mathcal{O}(N^2)$。

## 代码实现

``` cpp
#define int long long
void solve() {
	int n;
    cin >> n;
    int a[n+1] = {0}, f[n+2] = {0}, sum[n+1] = {0};
    memset(f, -0x7f, sizeof f);
    f[1] = 0;
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i-1] + a[i];
    }
    for (int i = 2; i <= n + 1; i++) {
        for (int j = 1; j < i; j++) {
            int p = sum[(i-j)/2] + sum[(i-j-1)/2];
            f[i] = max(f[i], f[j] + p);
        }
    }
    cout << f[n+1] << endl;
    return ;    
}
```



---

## 作者：Otue (赞：1)

# 思路
所有数组均在题目中表明或已说明。

第一次看没什么思路，但仔细观察会发现两个假期之间的贡献是可以直接计算出来的。

假设两个假期之间有 $d$ 个工作日，且贡献为 $B_i$：

* 当 $d=0$ 时，$B_i=0$
* 当 $d=1$ 时，$B_i=A_1$
* 当 $d=2$ 时，$B_i=2\times A_1$
* 当 $d=3$ 时，$B_i=2\times A_1+A_2$
* 当 $d=4$ 时，$B_i=2\times A_1+2\times A_2$
* 当 $d=5$ 时，$B_i=2\times A_1+2\times A_2+A_2$

* $ \ ⋮$

也许你会疑问 $B_i$ 咋算出来的，只需要每一个工作日的贡献加起来就行了。

然后总结一个规律：$B_d=\sum^{d}_{i=1}A_{\frac{i+1}{2}}$，是下取整。$B_d$ 可以直接前缀和计算。

接下来考虑 dp。

令 $dp_{i,j}$ 表示前 $i$ 天，且当前持续了 $j$ 天工作日的最大贡献。

* 第一种情况：若第 $i+1$ 天选择继续工作，$dp_{i,j}$ 转移到 $dp_{i+1,j+1}$。
* 第二种情况：若第 $i+1$ 天选择休息，那么 $dp_{i,j}+B_j$ 转移到 $dp_{i+1,0}$。（如果看不懂方程式说明没理解到 $B$ 数组的含义）

最后考虑求答案，但是不是很方便。当在解决循环中的问题时，通常在头部固定一个属性。这样，就简化了从尾部到头部的连接。对于这道题，只需要把假日定义在一周的第一天就可以了。

# 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 5005;
int n, a[N], dp[N][N], b[N];

signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) b[i] = b[i - 1] + a[(i + 1) / 2];
    memset(dp, -0x3f3f3f3f3f3f, sizeof dp);
    dp[1][0] = 0;   // 把假日定义在一周的第一天
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            if (dp[i][j] < 0) continue;
            dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j]);
            dp[i + 1][0] = max(dp[i + 1][0], dp[i][j] + b[j]);
        }
    }
    int res = -1e18;
    for (int i = 0; i <= n; i++) res = max(res, dp[n][i] + b[i]);  // 往头部连接
    cout << res << endl;
}
```

---

## 作者：hcywoi (赞：1)

[Work or Rest](https://www.luogu.com.cn/problem/AT_abc285_e)。

我们考虑**相邻**两个假期之间的工作效率和。

设 $len$ 为**相邻**两个假期间隔的天数。

举个例子，如果假期为 $\{1, 3, 7\}$，那么 $len$ 为 $\{1, 4\}$。

根据题意可知这相邻两个假期之前的工作效率和为 $\sum\limits_{i=1}^{len}A_{\left\lfloor\frac{i}{2}\right\rfloor}$。

不难看出，这柿子可以用前缀和求出。

根据以上柿子，我们只关心相邻两个假期间隔的天数，由此我们可以发现最优解一定是可以 $\text{Day}\ 1$ 为假期。

-----

设 $f_i$ 为 $\text{Day}\ i$ 为假期的最大效率和。

则 $f_i = \max\limits_{1\le j<i}\left\{f_{i-j}+\sum\limits_{k=1}^{j-1}A_{\left\lfloor\frac{k}{2}\right\rfloor}\right\}$。

答案就为 $\max\limits_{1\le i\le n}\left\{f_i+\sum\limits_{j=1}^{n-i}A_{\left\lfloor\frac{j}{2}\right\rfloor}\right\}$。

时间复杂度：$\mathcal O(n^2)$。

[代码](https://atcoder.jp/contests/abc285/submissions/38095403)。

---

## 作者：DaiRuiChen007 (赞：0)

# ABC285E 题解



## 思路分析

考虑 dp，用 $dp_i$ 表示前 $i$ 天在第 $i$ 天休息时的最大价值，状态转移方程如下：
$$
dp_i=\max_{j=1}^i\{dp_j+\operatorname{cost}(j,i)\}
$$
其中 $\operatorname{cost}(l,r)$ 表示在 $l,r$ 两天休息，中间不休息的情况下 $l+1\sim r-1$ 获得的最大价值，通过前缀和优化可以在 $\Theta(1)$ 的时间内计算。

注意到第 $n$ 天可能和下周的第一天结合产生贡献，为了解决这个问题，我们不妨把有休假的日子设为第 $1$ 天，这样答案就是 $dp_{n+1}$ 了。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=5005;
int a[MAXN],sum[MAXN],dp[MAXN];
inline int cost(int l,int r) {
	int k=r-l-1;
	return sum[(k+1)/2]+sum[k/2];
}
signed main() {
	int n;
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) {
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	memset(dp,-0x3f,sizeof(dp));
	dp[1]=0;
	for(int i=2;i<=n+1;++i) {
		for(int j=1;j<i;++j) {
			dp[i]=max(dp[i],dp[j]+cost(j,i));
		}
	}
	printf("%lld\n",dp[n+1]);
	return 0;
}
```

---

## 作者：Mikefeng (赞：0)

# [ABC285E] Work or Rest

## 题目翻译

一个周有 $n$ 天，你可以任意安排休息日，休息日不产生价值，工作日产生的价值是 $A_{\min(x,y)}$，其中 $x,y$ 表示向前和向后距离第一个休息日分别是多少天。

$n\leq5000$

## 做法

由于 $n$ 很小，我们可以猜到这是一个 $n^2$ 的 dp，但是由于第一个休息日会影响到最后几天的价值，所以 dp 状态并不好设计。

这时候我们发现，可以钦定第一天一定是休息日，这样对最后几天的影响就是确定的。

令 $dp_i$ 为最后一个休息日是第 $i$ 天时，第 $1$ 天到第 $i$ 天的价值，$n^2$ 的转移方程很好设计，在计算答案时，我们只要令 $ans=\max(dp_i+f_i)$ 即可，其中 $f_i$ 表示最后一个休息日是第 $i$ 天时第 $i+1$ 天到第 $n$ 天的价值。

时间复杂度就是 dp 转移的 $n^2$。

## 代码

```cpp
#include<iostream>
#include<unordered_map>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<iomanip>
#include<random>
#include<cstdio>
#include<vector>
#include<bitset>
#include<stack>
#include<queue>
#include<deque>
#include<cmath>
#include<ctime>
#include<map>
#include<set>
#define fi first
#define se second
#define name(x) #x
#define ll long long
#define pii pair<int,int>
#define syt cout<<"sytakioi\n"
#define pb(x) push_back(x)
#define dek(x) debug(x)<<" "
#define deh(x) debug(x)<<endl
#define debug(x) cout<<name(x)<<":"<<x
#define F(i,a,b) for(int i=a;i<=b;i++)
#define UF(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
inline ll read(){
	ll x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const ll N=5005;
ll n,ans;
ll a[N],f[N],sum[N];
inline void get_ans(ll x){
	ll num=n-x;
	ans=max(ans,f[x]+sum[num/2]*2+num%2*a[num/2+1]);
}
int main(){
	n=read();
	F(i,1,n) a[i]=read();
	F(i,1,n) sum[i]=sum[i-1]+a[i];
	f[1]=0;
	F(i,2,n) F(j,1,i-1) f[i]=max(f[i],f[j]+sum[(i-j-1)/2]*2+(i-j-1)%2*a[(i-j-1)/2+1]);
	F(i,1,n) get_ans(i);
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：IYSY2009I (赞：0)

看完题面后，很容易想到 dp。

因为 $N \le 5000$，所以如果 dp 的状态有二维，则转移的时间复杂度需要很低，显然是没有前途的，于是我们考虑一维 dp。

首先一个可以发现的性质是，因为 $A_i \ge 1$，所以至少要设置一天休息日，否则答案是 $0$，显然不优。

其次，与答案有关的天数的编号与答案没有关系，所以我们把哪一天作为这个周的第一天不会对答案产生影响，再结合上一段的结论，我们可以强制第一天为休息日，这样方便 dp。

然后，在我们已经确定了第一个休息日和最后一个休息日的情况下，最后一天休息日之后的几天生产力是一定的。我们已经强制了第一天为休息日，所以如果第一天到第 $i$ 天的生产力更大，那么总生产力也就更大。据此我们定义 $f_i$ 表示当前只考虑前 $i$ 天，第 $i$ 天为最后一个休息日的情况下，前 $i$ 天的最大生产力，可以得到转移：

$$f_i=\max_{j=1}^{i-1}f_j+\operatorname{cost}(j,i)$$

其中 $\operatorname{cost}(i,j)$ 表示第 $i,j$ 天为休息日，中间几天的生产力大小（$i<j$）。

现在我们只需要 $\Theta(1)$ 求 $\operatorname{cost}(j,i)$ 就可以了。

先求出 $A$ 的前缀和 $sum$。

我们容易发现，$\operatorname{cost}(i,j)=A_1+A_2+...+A_2+A_1$，于是我们分类讨论。

- 如果 $i-j-1$ （即区间长度）为偶数，那么 $\operatorname{cost}(j,i)=sum_{\frac{i-j-1}{2}} \times 2$。
- 如果 $i-j-1$ 为奇数，那么 $\operatorname{cost}(j,i)=sum_{\frac{i-j}{2}} \times 2-A_{\frac{i-j}{2}}$。

求出来了 $f_i$ 之后，第 $i$ 天为最后一个休息日的情况下，所有天的最大生产力和上面一样分类讨论做即可。最终答案就是这些东西取 $\max$。

总时间复杂度为 $\Theta(N^2)$。

代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long a[5005];
bool h[5005];
long long dp[5005];
long long sum[5005];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	long long ans=0;
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+a[i];
	if((n-1)%2==0) ans=max(ans,sum[n/2]*2);
	else ans=max(ans,sum[n/2]*2-a[n/2]);
	for(int i=2;i<=n;i++){
		for(int j=i-1;j>=1;j--){
			if((i-j-1)%2==0) dp[i]=max(dp[i],dp[j]+sum[(i-j)/2]*2);
			else dp[i]=max(dp[i],dp[j]+sum[(i-j)/2]*2-a[(i-j)/2]);
		}
		if((n-i)%2==0) ans=max(ans,dp[i]+sum[(n+1-i)/2]*2);
		else ans=max(ans,dp[i]+sum[(n+1-i)/2]*2-a[(n+1-i)/2]);
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：NightStriker (赞：0)

考虑 dp。

当两个假期之间有 $x$ 个工作日（$1 \le x \le n$）：


  $\text{if } x=0:0$
  
  $\text{if } x=1:a_1$
  
  $\text{if } x=2:2\times a_1 $
  
  $\text{if } x=3:2\times a_1+a_2 $
  
  $\text{if } x=4:2\times a_1+2\times a_2 $
  
  $\text{if } x=5:2\times a_1+2\times a_2+a_3$

简化后可得，

 $$\large \sum_{i = 1}^{x}a_{\left \lfloor \frac{i+1}{2} \right \rfloor}$$

我们把上面的那个东西存到一个数组 $b$ 里面。

$f_{i,j}$ 代表固定第 $i$ 天休假，已经工作了 $j$ 天的最大生产值。

在解决一个周期的问题时，通常会在最开始固定一个特征。这一次，将一个假期固定在 一周中的第 $1$ 天就可以了。

那么边界值就是 $f_{1,0}$，就是固定在第 $1$ 天休假，工作了 $0$ 天（还没工作）的最大生产总值。也就是 $0$。

下面是转移方程：

- $f_{i+1,j+1}=\max(f_{i+1,j+1},f_{i,j})$（继续工作一天 和 不工作 打擂台）
- $f_{i+1,0}=\max(f_{i+1,0},f_{i,j}+b_j)$（一直休假 和 连续工作 打擂台）

最后再算一下工作几天生产值最大。

除此以外，这道题还需要开 `long long`。因为 $f$ 数组可能很大。



别忘记给 $f$ 数组赋初值和边界值。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[5001],b[5001],f[5001][5001],ans;
signed main() {
	cin>>n; 
	for(int i = 1; i<=n; i++) {
		cin>>a[i];
		b[i] = b[i-1]+a[(i+1)/2];
	}
	memset(f,-0x7f7f,sizeof f);
	f[1][0] = 0;
	for(int i = 1; i<n; i++) {//注意是小于 n，因为 i+1/j+1 可能会越界。
		for(int j = 0; j<=n; j++) {//因为可以工作 0 天，所以是从 0 开始遍历。
			if(f[i][j]<0) continue;
			f[i+1][j+1] = max(f[i+1][j+1],f[i][j]);
			f[i+1][0] = max(f[i+1][0],f[i][j]+b[j]);
		}
	}
	for(int i = 0; i<n; i++) {//打擂台
		ans = max(ans,f[n][i]+b[i]);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

但是我们发现 $f$ 数组很占空间。大约需要 $100+$ MB。

所以我们使用滚动数组。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[5001],b[5001],f[2][5001],ans;
signed main() {
	cin>>n; 
	for(int i = 1; i<=n; i++) {
		cin>>a[i];
		b[i] = b[i-1]+a[(i+1)/2]; 
	}
	memset(f,-0x7f7f,sizeof f);
	int now = 0,last = 1;//上一行和下一行
	f[now][0] = 0;
	for(int i = 1; i<n; i++) {
		swap(now,last);//不断滚动
		for(int j = 0; j<=n; j++) {
			if(f[last][j]<0) continue;//i+1 是 now,i 是 last
			f[now][j+1] = max(f[now][j+1],f[last][j]);
			f[now][0] = max(f[now][0],f[last][j]+b[j]);
		}
	}
	for(int i = 0; i<n; i++) {
		ans = max(ans,f[now][i]+b[i]);
	}
	cout<<ans<<endl;
	return 0;
}
/*
空间：194MB->3MB
时间：163ms->52ms
*/
```



---

