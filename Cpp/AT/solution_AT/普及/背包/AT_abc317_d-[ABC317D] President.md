# [ABC317D] President

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc317/tasks/abc317_d

高橋君と青木君が選挙で戦っています。  
 選挙区は $ N $ 個あります。$ i $ 番目の選挙区には $ X_i\ +\ Y_i $ 人の有権者がいて、そのうち $ X_i $ 人が高橋派、$ Y_i $ 人が青木派です。($ X_i\ +\ Y_i $ はすべて奇数です)  
 それぞれの区では、多数派がその区の $ Z_i $ 議席を全て獲得します。そして、$ N $ 個の選挙区全体として過半数の議席を獲得した方が選挙に勝利します。($ \displaystyle\ \sum_{i=1}^N\ Z_i $ は奇数です)  
 高橋君が選挙で勝利するには最低で何人を青木派から高橋派に鞍替えさせる必要がありますか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 0\ \leq\ X_i,\ Y_i\ \leq\ 10^9 $
- $ X_i\ +\ Y_i $ は奇数
- $ 1\ \leq\ Z_i $
- $ \displaystyle\ \sum_{i=1}^N\ Z_i\ \leq\ 10^5 $
- $ \displaystyle\ \sum_{i=1}^N\ Z_i $ は奇数
 
### Sample Explanation 1

選挙区が $ 1 $ 個しかないので、$ 1 $ 番目の選挙区で議席を獲得した人が選挙に勝利します。 $ 1 $ 番目の選挙区の青木派 $ 3 $ 人を高橋派に鞍替えさせると、$ 1 $ 番目の選挙区にいる有権者のうち高橋派は $ 6 $ 人、青木派は $ 5 $ 人になり、高橋君は議席を獲得できます。

### Sample Explanation 2

$ 1 $ 番目の選挙区の議席数よりも $ 2 $ 番目の選挙区の議席数の方が多いため、高橋君が選挙に勝つには $ 2 $ 番目の選挙区で高橋派を多数派にする必要があります。 $ 2 $ 番目の選挙区の青木派の $ 4 $ 人を鞍替えさせると高橋君は $ 5 $ 議席を獲得できます。このとき青木君の獲得する議席は $ 2 $ 議席なので、高橋君は選挙に勝利できます。

### Sample Explanation 3

青木派から高橋派に鞍替えする人が $ 0 $ 人でも高橋君が選挙で勝つ場合は $ 0 $ 人が答えになります。

## 样例 #1

### 输入

```
1
3 8 1```

### 输出

```
3```

## 样例 #2

### 输入

```
2
3 6 2
1 8 5```

### 输出

```
4```

## 样例 #3

### 输入

```
3
3 4 2
1 2 3
7 2 6```

### 输出

```
0```

## 样例 #4

### 输入

```
10
1878 2089 16
1982 1769 13
2148 1601 14
2189 2362 15
2268 2279 16
2394 2841 18
2926 2971 20
3091 2146 20
3878 4685 38
4504 4617 29```

### 输出

```
86```

# 题解

## 作者：ran_qwq (赞：14)

[题目传送门](https://atcoder.jp/contests/abc317/tasks/abc317_d)

有两个人 A 和 B 在选举，有 $n$ 个选区。第 $i$ 个选区有 $x_i$ 个人支持 A，$y_i$ 个人支持 B。

你可以让一些支持 B 的人支持 A。如果第 $i$ 个选区，支持 A 的人比支持 B 的多，A 可以获得 $z_i$ 票。

求使 A 票数比 B 多，支持 B 的人转为支持 A 的最小人数。

$n\le100,X_i,Y_i\le10^9,\sum Z_i\le10^5$。

---
首先可以预处理出第 $i$ 个选区获得 $Z_i$ 票的最小代价 $W_i$。

不难看出是个 01 背包。

设 $dp_{i,j}$ 为前 $i$ 个选区，A 有 $j$ 票的方案数。

状态转移方程：$dp_{i,j}=\min(dp_{i-1,j},dp_{i-1,j-Z_i}+W_i)$。

初始值：$dp_{0,0}=0$，其它为正无穷。

答案：$\min\limits_{i=\lceil\frac{\sum Z_i}{2}\rceil}^{\sum Z_i}dp_{n,i}$。

可以滚动数组，也可以不滚。

必须开 `long long`，我没开吃了一发罚时。

[AT 提交记录](https://atcoder.jp/contests/abc317/submissions/44953932)

---

## 作者：zhangjiting (赞：4)

## 题意

高桥和青木正在竞选。  


有 $N$ 个选区。第 $i$ 个选区有 $X_i + Y_i$ 个选民，其中 $X_i$ 个是高桥的，$Y_i$ 个是青木的。$X_i + Y_i$ 总是奇数）。


在每个选区，多数党赢得该选区的所有 $Z_i$ 个席位。然后，谁赢得了整个 $N$ 个选区的多数席位，谁就赢得了选举（$\displaystyle \sum_{i=1}^N Z_i$ 是奇数）。


至少要有多少选民从青木转向高桥，高桥才能赢得选举？

## 思路

如果我们想让青木的选民的数量在选区 $i$ 小于高桥的选民的数量，需要 $\max(0,(Y_i-X_i+1)/2)$ 个选民从青木转向高桥。

那么第 $i$ 个选区就可以看成一个大小为 $\max(0,(Y_i-X_i+1)/2)$，价值为 $Z_i$ 的物品。

这样就变成了一道简单的背包 dp。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int dp[100005],ans,bag;
signed main(){
	int n;
	cin>>n;
	memset(dp,0x3f,sizeof(dp));
	ans=dp[0];
	dp[0]=0;
	for(int i=1;i<=n;i++){
		int a,b,c,w=0;
		cin>>a>>b>>c;
		bag+=c;
		w=(b-a+1)/2;
		if(w<0) w=0;
		for(int j=bag;j>=c;j--) dp[j]=min(dp[j],dp[j-c]+w);
	}
	for(int i=bag/2+1;i<=bag;i++)
		ans=min(ans,dp[i]);
	cout<<ans;
	return 0; 
}

```


---

## 作者：Fire_flame (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc317_d)

所以，ABC316 去哪里了？

## $\mathtt{Solution}$

一眼丁真，以为是个贪心，其实不然，$n$ 和 $Z_i$ 的范围提示了我们是个 $01$ 背包。

首先，枚举 $1\le i\le n$，如果 $X_i>Y_i$，那么这个区域的人不用策反，直接加上 $Z_i$ 的选票。

统计完之后，如果高桥的选票大于青木的选票，直接输出 $0$。

否则，考虑转化成一个 $01$ 背包模型，令高桥、青木的选票分别为 $num1,num2$。

对于 $\forall i$ 满足 $X_i<Y_i$，高桥需要至少策反 $\dfrac{X_i+Y_i+1}{2}-X_i$ 人，才能够为自己带来 $Z_i$ 的选票。

又因为高桥增加了 $Z_i$ 选票之后，青木会减少 $Z_i$ 的选票，相当于重量为 $2\times Z_i$，价值为 $\dfrac{X_i+Y_i+1}{2}-X_i$ 的一个物品。

所以，定义状态 $f_{i,j}$ 表示前 $i$ 个物品，获得 $j$ 选票的最小价值，可得：

$f_{i,j}=\min\{f_{i-1,j-2\times Z_i}+\frac{X_i+Y_i+1}{2}-X_i,f_{i-1,j}\}$

初始化就是 $f_{0,0}=0$，其他的设成无穷大。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 105, MR = 2e5 + 5;//空间要开两倍，因为2*Z[i]可能达到2e5
int n, ans = 1e16, cnt, num1, num2, f[MAXN][MR], v[MAXN], w[MAXN];
signed main(){
	n = read();
	for(int i = 1;i <= n;i ++){
		int x = read(), y = read(), z = read();
		if(x > y)num1 += z;//高桥赢得了这个区域的选票
		else w[++ cnt] = z * 2, v[cnt] = (x + y + 1) / 2 - x, num2 += z;
        //青木赢得了这个区域的选票，添加一个物品
	}
	if(num1 > num2){//高桥票数比青木多
		puts("0");
		return 0;
	}
//	printf("%d\n", cnt);
//	for(int i = 1;i <= cnt;i ++)printf("%d %d\n", v[i], w[i]);
	memset(f, 0x7f, sizeof(f));
	f[0][0] = 0;
	for(int i = 1;i <= cnt;i ++){
		for(int j = 0;j < MR;j ++){
			f[i][j] = f[i - 1][j];
			if(j >= w[i])f[i][j] = min(f[i][j], f[i - 1][j - w[i]] + v[i]);
//			printf("%d %d %d\n", i, j, f[i][j]);
		}
	}
	for(int i = num2 - num1 + 1;i < MR;i ++)ans = min(ans, f[cnt][i]);//求解答案
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：tbdsh (赞：2)

# 题意简述
[更好的阅读体验](https://www.luogu.com.cn/blog/tianbiandeshenghuo11/solution-at-abc317-d)

[洛谷题目传送门](https://www.luogu.com.cn/problem/at_abc317_d)

[AtCoder 题目传送门](https://atcoder.jp/contests/abc317/tasks/abc317_d)

Takahashi 和 Aoki 正在竞选。

一共有 $n(1\le n\le 100)$ 个选区，每个选区有 $x_i(1\le x_i\le 10^9)$ 个选民支持 Takahashi，$y_i(1\le y_i\le 10^9)$ 个选民支持 Aoki。如果其中一人在这个选区的支持者比另一个人多，那么他将获得 $z_i(\sum^n_{i=1}z_i\le10^5)$ 点威望。

最终威望值更大的人将竞选成功。

现在，因为 Takahashi 的支持者不够多。所以他想知道：至少还要多少个选民放弃支持 Aoki 而支持 Takahashi 他才能竞选成功。

# 分析
本题是一道背包 DP 题。

下记 $p=\sum^n_{i=1}z_i$。

我们记 $dp_{i,j}$ 表示 Takahashi 在前 $i$ 个选取获得 $j$ 点威望值需要的最小增加选民数量。

那么就有 $dp_{i + 1,j+z_i}=\min\{dp_{i,j}+\max(0, \left\lfloor\dfrac{(y_i-x_i+1)}{2}\right\rfloor)\}$。

因为数据范围保证 $n\le 100$，$p\le 10^5$，所以做法可以通过。

但同时，也可以进行一些小优化。

不难发现当前能进行转移的有效状态只有 $\sum^i_{j=1}z_j$ 个。所以我们转移只需要枚举 $1\sim\sum^i_{j=1}z_j$ 即可。

最后答案就是 $\min\limits_{\left\lfloor\frac{p+1}{2}\right\rfloor\le j\le p}\{dp_{n+1,j}\}$。

时间复杂度：$O(n\times \sum^n_{i=1} z_i)$。

空间复杂度：$O(n\times \sum^n_{i=1} z_i)$。
# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 1e2 + 5, MAXV = 1e5 + 5;
int n, m;
long long dp[105][MAXV];
struct Node{
  int x, y, z;
} a[MAXN];
int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  int sum = 0;
  long long cnt = 2e18;
  for (int i = 1; i <= n; i++){
    cin >> a[i].x >> a[i].y >> a[i].z;
    sum += a[i].z;
    for (int j = 0; j <= sum; j++){
      dp[i][j] = 2e18;
    }
  }
  for (int j = 0; j <= sum; j++){
    dp[n + 1][j] = 2e18;
  }
  sum = 0;
  dp[1][0] = 0;
  for (int i = 1; i <= n; i++){
    sum += a[i].z;
    long long tmp = max(0, (a[i].y - a[i].x + 1) / 2);
    for (int j = 0; j <= sum; j++){
      dp[i + 1][j + a[i].z] = min(dp[i + 1][j + a[i].z], dp[i][j] + tmp);
      dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
    }
  }
  int p = sum;
  sum = (sum + 1) / 2;
  for (int i = sum; i <= p; i++){
    cnt = min(cnt, dp[n + 1][i]);
  }
  cout << cnt;
  return 0;
}
```

---

## 作者：xxr___ (赞：2)

### 思路：
从第一行开始枚举，需要多少才能让高桥胜利，因为高桥胜利会获得加成，将这个状态持续到下一行，判断一下是选还是不选即可。如果选，则第二行高桥的人数加一。
### 代码：
```cpp
#include <bits/stdc++.h>
#define inf 1e18
using namespace std;
signed main(){
    int n;
    cin>>n;
    vector<long long>  dp{0};
    int sum=0;
    for (int i=0;i<n;i++) {
        int x,y,z;
        cin>>x>>y>>z;
        int ans1=max(0,(x+y+1)/2-x);
        sum+=z;
        dp.resize(sum+1,inf);
        for(int i=sum;i>=z;i--)dp[i]=min(dp[i],dp[i-z]+ans1);
    }
    long long ans2=*min_element(dp.begin()+(sum+1)/2,dp.end());
    cout<<ans2<<"\n";   
    return 0;
}
```

---

## 作者：Jorisy (赞：1)

第一次自己写出一道 dp，但是是板子 /ll。

相当于 01 背包，$f_{i,j}$ 表示前 $i$ 个选区高桥得到 $j$ 票时最少改变选票的人数。

然后我们就可以推出转移方程 $f_{i,j}=\begin{cases}f_{i-1,j}&(j<Z_i)\\
\min\{f_{i-1,j},f_{i-Z_i}+p\}&(j\ge Z_i)\end{cases}$。

这里 $p$ 分类讨论一下。

- 如果 $X_i>Y_i$，那么这个时候已经赢了，因此没必要增加改变选票人数，$p=0$；
- 否则，就要增加 $\left\lceil\dfrac{X_i+Y_i}{2}\right\rceil-X_i$ 的人改变选票，因为 $\left\lceil\dfrac{X_i+Y_i}{2}\right\rceil$ 是当前选区可以获胜的最小票数。

我们令 $v=\sum\limits_{i=1}^nZ_i$，那么最后 $ans=\min\limits_{\lceil\frac v2\rceil\le i\le v}\{f_{n,i}\}$（即所有可能获胜的情况中改变选票人数中最少的）。

代码就不放了。

---

## 作者：incra (赞：0)

### 题解
考虑 DP。

设 $f_{i,j}$ 表示前 $i$ 组人一共有 $j$ 的代价时最少改变人的投票策略的代价。

若第 $i$ 组人本身已经有大于一半给第一个人投票了，那么代价为 $0$，即 $f_{i,j}=f_{i-1,j-z_i}$。

反之，把投票给第一个人投票的人数增加到一半以上，即 $\left\lceil\frac{sum_i}{2}\right\rceil$，其中 $sum_i$ 表示第 $i$ 组一共有几人，所以不难得到此时 $f_{i,j}=f_{i-1,j-z_i}+\left\lceil\frac{sum_i}{2}\right\rceil-x_i$。

不难得到答案就是 $\displaystyle\min_{i=\left\lceil\frac{s}{2}\right\rceil}^s\{f_{n,i}\}$，其中 $s$ 表示总人数。

代码顺带加了类似 `01` 背包优化的思想，这里就不再赘述。

最后吐槽一下 `C++20` 禁止读入字符数组这件事，随便写一下就复原出这个功能了。
### 代码
```cpp
#include <bits/stdc++.h>
#define rep(i,l,r) for (int i = (l),SIZE = (r);i <= SIZE;i++)
#define per(i,l,r) for (int i = (l),SIZE = (r);i >= SIZE;i--)
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef pair <int,int> PII;
istream& operator >> (istream& in,char* s) {
	char ch = getchar ();
	while (isspace (ch) && ch != EOF) ch = getchar ();
	int n = 0;
	while (!isspace (ch) && ch != EOF) s[n++] = ch,ch = getchar ();
	if (ch == EOF) exit (0);
	s[n] = '\0';
	return in;
}
const int N = 110,M = 100010;
int n;
int x[N],y[N],z[N];
LL f[M];
int main () {
	cin >> n;
	int ansa = 0,ansb = 0;
	vector <int> v;
	rep (i,1,n) {
		cin >> x[i] >> y[i] >> z[i];
		if (x[i] > y[i]) ansa += z[i];
		else ansb += z[i];
	}
	if (ansa > ansb) puts ("0");
	else {
		memset (f,0x3f,sizeof (f));
		f[0] = 0;
		int sum = 0;
		rep (i,1,n) {
			sum += z[i];
			per (j,M - 1,z[i]) f[j] = min (f[j],f[j - z[i]] + max (y[i] - (x[i] + y[i]) / 2,0));
		}
		LL ans = 1e18;
		rep (i,(sum + 1) / 2,M - 1) ans = min (ans,f[i]);
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：WilliamFranklin (赞：0)

### 主要思路

一眼 dp。

我们可以将题目转化为如下问题：

有 $n$ 个物品，每一个物品都只有 $1$ 个。当 $x_i < y_i$ 时（$x_i + y_i$ 保证是奇数），第 $i$ 个物品的价格 $c_i$ 为 $\lfloor\frac{y_i - x_i}{2}\rfloor$，否则，第 $i$ 个物品的价格 $c_i$ 为 $0$。然后，第 $i$ 个物品的价值为 $z_i$。所有物品的价值和为 $sum$，保证 $sum$ 是奇数。求出所买物品价值大于 $\lfloor \frac{sum}{2} \rfloor$ 的最少花费。

我们设 $f_{i,j}$ 表示买前 $i$ 件的物品的总价值为 $j$ 的最少花费。

由此转移方程如下：

$$
f_{i, j} = \min\{f_{i - 1, k(z_i \le k \le sum) - z_i}\} + c_i 
$$

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 105;
long long x[N], y[N], z[N];
long long f[100005];
int n;
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	long long sum = 0;
	For(i, 1, n) cin >> x[i] >> y[i] >> z[i];
	For(i, 1, n) x[i] = max((long long)0, (y[i] - x[i] + 1) / 2), sum += z[i];
	For(i, 1, sum) f[i] = 1e18;
	f[0] = 0;
	For(i, 1, n) Dec(j, sum, z[i]) f[j] = min(f[j - z[i]] + x[i], f[j]);
	long long ans = 1e18;
	For(i, (sum + 1) / 2, sum) ans = min(ans, f[i]);
	cout << ans;
	return 0;
} 
```

---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc317_d)

#### 思路

容易想到此题是一个背包，如果高桥能赢就用 $ans$ 加起来，否则添加一个容量为 $(y_i - x_i + 1) / 2$，价值为 $c_i$ 的物品，用 $ans1$ 加起来，最后背包容量就是 $(ans1 - ans + 1) / 2$，$01$ 背包就可以了，    由于只要价值大于容量就可以，所以其实背包部分和[这道题](https://www.luogu.com.cn/problem/AT_abc145_e)几乎一样。

code

```c
#include<bits/stdc++.h>
using namespace std;
long long n,a,b,cc,sum,ans,ans1,o,dp[1145014],m,ma = LONG_LONG_MAX;
struct w
{
	long long x,y;
}c[400000];
bool cmp(w a,w b)
{
	return a.x < b.x;
}
int main()
{
	cin >> n;
	for(int i = 1;i <= 110000;i++) dp[i] = 1e11;
	for(int i = 1;i <= n;i++) 
	{
		cin >> a >> b >> cc;
		if(a > b) ans += cc;
		else c[++o].y = (b - a + 1) / 2,c[o].x = cc,ans1 += cc;
	}
	m = (ans1 - ans + 1) / 2;//容量 
	sort(c + 1,c + 1 + o,cmp);
	for(int i = 1;i <= o;i++)
	{
		for(int j = m + c[i].x - 1;j >= c[i].x;j--)
		{
	    	dp[j] = min(dp[j],dp[j - c[i].x] + c[i].y);
			if(j >= m) ma = min(ma,dp[j]);//取最小值 
	    }
	}
	if(ma == LONG_LONG_MAX) ma = 0;//无解 
	cout << ma;
    return 0;
}

```



---

## 作者：sunkuangzheng (赞：0)

**【题目分析】**

很板子的背包。

如果 $x_i > y_i$，那我们直接让已经获得的选民数量 $c \gets c+z_i$。

否则，我们把这个地区的费用视为 $\dfrac{x_i+y_i+1}{2}-x_i$，价值视为 $z_i$。

然后直接背包。注意到费用很大而价值很小，所以我们将两维反过来跑 01 背包，即设 $f_i$ 表示要获得 $i$ 个选民至少需要的价格。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
#define int long long
int n,a[105],b[105],c[105],ans,sum,w[105],d[105],tot,f[maxn],mn = 1e15;
signed main(){
    cin >> n;
    for(int i = 1;i <= n;i ++){
        cin >> a[i] >> b[i] >> c[i],sum += c[i];
        if(a[i] > b[i]) ans += c[i];
        else w[++tot] = c[i],d[tot] = (a[i] + b[i] + 1) / 2 - a[i]; 
    }f[0] = 0;if(ans > (sum + 1) / 2) return cout << 0,0;
    for(int i = 1;i <= 200000;i ++) f[i] = 1e15;
    for(int i = 1;i <= tot;i ++){
        for(int j = 200000;j >= w[i];j --)
            f[j] = min(f[j],f[j-w[i]]+d[i]);
    }for(int i = (sum+1)/2-ans;i <= 200000;i ++) mn = min(mn,f[i]);
    cout << mn;
}
```

---

## 作者：happybob (赞：0)

考虑每一个 $x_i < y_i$ 的组，拿回 $z_i$ 的票需要 $\lceil \dfrac{y_i-x_i}{2}\rceil$ 个人从 $y_i$ 变成 $x_i$。

直接算出两个人的得分 $a,b$，则至少需要 $\lceil \dfrac{b-a}{2}\rceil$ 的票。

直接背包就好了。

```cpp
#pragma GCC optimize("-Ofast,fast-math,-inline")
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e5 + 5, MOD = 1e9 + 7; // Remember to change

int n;

struct Node
{
	long long x, y, z;
	Node(long long _x, long long _y, long long _z): x(_x), y(_y), z(_z){}
	Node(){}
}a[N];

namespace FastIo
{
	#define QUICKCIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
	int read()
	{
		char ch = getchar();
		int x = 0, f = 1;
		while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
		while (ch == '-')
		{
			f = -f;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9')
		{
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template<class T>
	void write(T x)
	{
		if (x < 0)
		{
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	template<class T>
	void writeln(T x)
	{
		write(x);
		putchar('\n');
	}
}

int dp[N];
vector<pair<int, int> > v;

signed main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin>>n;
	int s1=0,s2=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y>>a[i].z;
		if(a[i].x<a[i].y)
		{
			v.emplace_back(make_pair((a[i].y-a[i].x+1)/2, a[i].z));
			s2+=a[i].z;
		}
		else s1+=a[i].z;
	}
	if(s1>s2) cout<<"0\n";
	else
	{
		int p=(s2-s1+1)/2;
		//cout<<p<<"\n";
		memset(dp,0x3f,sizeof dp);
		dp[0]=0;
		for(auto&i:v)
		{
			//cout<<i.first<<" " << i.second << "\n";
			for(int j=100000;j>=i.second;j--)
			{
				dp[j]=min(dp[j],dp[j-i.second]+i.first);
			}
		}
		int ans=1e18;
		for(int i=p;i<=100000;i++) ans=min(ans, dp[i]);
		cout<<ans<<"\n";
	}
	return 0;
}


```


---

## 作者：Failure_Terminator (赞：0)

## Solution

赛时写过贪心，但是假掉了。

再看一眼数据范围，发现 $z$ 的总和与 $n$ 都很小，因此考虑 dp。

$dp_i$ 表示要获得 $i$ 个选票至少需要的支持选民数。

接下来是经典的 $01$ 背包问题。

最后的符合条件的 $dp_i$ 取最小值即可。

## Code

[Link](https://atcoder.jp/contests/abc317/submissions/44965778)

---

## 作者：wenlebo (赞：0)

一道不错的背包问题。

如果我们想要得到更多的票（以下的票为选举人票）就要把对方占优势的选区赢到自己手里，就假设赢得第 $i$ 选取需要劝说 $c_i$ 位选民，并积累 $m_i$ 票优势。

在 $X_i < Y_i$ 时，我方劣势，需要劝说 $\lfloor (Y_i - X_i) \div 2 \rfloor +1$ 位选民，并获得 $Z_i + Z_i$ 张票的优势(因为这一选区原先属于对方，在赢得以后对方票数消耗了 $Z_i$ 票，但我方赢得了 $Z_i$ 票)。

在 $X_i > Y_i$ 时，我方优势，无需劝说任何选民，也不能得到额外票。

注意：这题强调了 $ X_i + Y_i $ 是奇数，且 $ \displaystyle\ \sum_{i=1}^N\ Z_i $ 是奇数，这意味着无论是单个选区还是整体结果都**不会出现平票**。

此时我们可以把它当作一个背包问题，将 $c_i$ 作为体积，将 $w_i$ 作为价值即可。

因为 $\displaystyle\ \sum_{i=1}^N\ Z_i \leq 10^5$ 但 $X_i$ 和 $Y_i$ 都很大，所以应该设 $dp_i$ 为在获取 $i$ 张选举人票时最少劝说的人数。

下面进行基本的背包问题求解即可，最后遍历数组 $dp$ 寻找最优解。

实现细节：

```
dp[j]=min(dp[j-m[i]]+c[i],dp[j]);
```


因为我的代码过于混乱，暂时不放。

---

## 作者：God_Max_Me (赞：0)

## 题意

给定 $n$ 个区，每个区的价值为 $z_i$ ，现在有两个人竞争，我们想让第一个人赢，现在每个人每个区的支持人数分别为 $u,v$ ，哪方支持人数多，那么他就能获得这个区的价值，最后如果要使的第一个人获得的价值大于的二个人获得的价值，需要至少让多少人更改支持方。

## 思路

相当于就是说要选一些区的人改票，这能让我们想到背包DP，第一个人需要改票的人数为 $w_i$，显然 $w_i=\frac{u+v+1}{2}-u$，这相当于是背包容量，$z_i$ 即是背包物品价值。

转移方程如下：
$$
dp[j]=min(dp[j-z[i]]+w[i],dp[j])
$$

## 代码
~~~cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
template<typename P>
inline void read(P &x){
   	P res=0,f=1;
   	char ch=getchar();
   	while(ch<'0' || ch>'9'){
   		if(ch=='-') f=-1;
   		ch=getchar();
   	}
   	while(ch>='0' && ch<='9'){
   		res=res*10+ch-'0';
   		ch=getchar();
	}
	x=res*f;
}
int T=1;
int n,m;
int w[120],z[120];
long long dp[100010];
signed main(){
	read(n);
	int u,v,c=0;
	long long res=0x3f3f3f3f3f3f3f3f;
	memset(dp,0x3f,sizeof(dp));
	for(int i=0;i<n;++i){
		read(u),read(v),read(z[i]);
		if(u<v) w[i]=(u+v+1)/2-u;
		c+=z[i];
	}
	dp[0]=0;
	for(int i=0;i<n;++i){
		for(int j=c;j>=z[i];--j){
			dp[j]=min(dp[j-z[i]]+w[i],dp[j]);
		}
	}
	for(int i=(c+1)/2;i<=c;++i) res=min(res,dp[i]);
	cout<<res<<endl;
	return 0;
}


~~~

---

## 作者：WhisperingWillow (赞：0)

# 简化题意

有 $N$ 个三元组 $(X,Y,Z)$。

保证 $\sum_{i=1}^N Z_i \equiv 1 \pmod 2$。

$\forall i\in[1,N]$，如果 $X_i<Y_i$，则 $Z_i=-Z_i$。

保证 $X_i+Y_i \equiv 1 \pmod 2$。

现在你可以做若干次操作，每次操作可将选择 $i,p$，使 $X_i$ 加上 $p$，$Y_i$ 减去 $p$，操作的花费为 $p$。

请问使 $\sum_{i=1}^N Z_i >0$ 的最小花费是多少？

# 题目解析

以下设 $k=\sum_{i=1}^n|Z_i|$。

当 $X_i>Y_i$ 时，显然不用做任何调整。

当 $X_i<Y_i$ 时，显然可以找到最小的 $p_i$，最优情况下 $p_i+X_i=Y_i-p_i+1$，得 $p_i=\dfrac{Y_i-X_i+1}{2}$。

考虑转移，设 $dp_x$ 为剩下的为非负整数的 $Z_i$ 的和恰好为 $x$ 的最小代价，如果不可以达到，则 $dp_x=\infty $。

则可以列出方程 $dp_j=dp_{j-Z_i}+p_i$。

倒着转移即可。

如果 $\sum^n_{i=1}Z_i>0$，那么非负整数的 $Z_i$ 的和要 $>\dfrac{k+1}{2}$，得答案为 $\min_{i=\frac{k+1}{2}}^kdp_i$ 

## 代码

```
int w[N],z[N];
int dp[M];
co int INF=1e18;
il void solve(){
    n=read();
    f(i,1,n){
    	int x=read(),y=read();
		z[i]=read();
    	k+=z[i];
    	w[i]=(x+y+1)/2-x;
    	if(w[i]<0)w[i]=0;
	}
	f(i,1,k) dp[i]=INF;
	f(i,1,n) {
		fd(j,z[i],k){
			dp[j]=min(dp[j],dp[j-z[i]]+w[i]);			
		}
	}
	m=INF;
	f(i,k/2+1,k){
		m=min(m,dp[i]);
	}
	cout<<m<<endl;
    return;
}
```

---

## 作者：Loser_Syx (赞：0)

由于本题要求改变最少数量的人，使得当 $X_i > Y_i$ 的 $Z_i$ 总和大于 $X_i < Y_i$ 的 $Z_i$ 总和，那么对于当前 $i$，如果需要移动 $Y_i$ 至 $X_i$ 的话，那么其的代价为 $(X_i + Y_i) - (X_i + Y_i) \div 2 - X_i$，所得到的价值为 $Z_i$。

然后又求所得的代价最小，便可以考虑背包，定义状态 $dp_i$ 为到达价值 $i$ 的最小花费，进行 01 背包，然后最后查找最小符合条件的元素便可。

[代码](https://atcoder.jp/contests/abc317/submissions/44978676)。

---

