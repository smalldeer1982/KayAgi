# [COCI 2007/2008 #6] CESTARINE

## 题目描述

Luka 的 $n$ 辆卡车行驶在一辆高速路上。高速路上有许多出入口。我们认为相同编号的出入口在同一位置。

开进高速路后，司机会收到一张写着他入口号的单子。驶出时，驾驶员支付的通行费等于出入口号的绝对差。

Luka 是一个爱贪小便宜的人。他发现，即使他们的路线不重叠，司机们可以在高速路上交换他们的单子。

但是，不能再同一位置的出入口进行上高速与下高速。

请你编程求出最少的通行费。

## 说明/提示

#### 样例 #1 解释

最少的通行费为 $ |65−60| + |10−3| + |25−45| = 32$。

#### 数据规模及约定

对于 $100\%$ 的数据，$1 \le n \le 10^5$，$1 \le x, y \le 10^6$，$x \not= y$。 

#### 提示
请使用 $64$ 位整数类型（在 C / C++ 语言中为 `long long`，在 Pascal 语言中为 `int64`），否则可能会导致答案错误（即 Wrong Answer）。 

#### 说明
- 本题满分 $80$ 分。
- 本题默认开启 O2 优化开关。
- 题目译自 [COCI2007-2008](https://hsin.hr/coci/archive/2007_2008/) [CONTEST #6](https://hsin.hr/coci/archive/2007_2008/contest6_tasks.pdf) T6 CESTARINE，译者 @[tearing](https://www.luogu.com.cn/user/219791)。

## 样例 #1

### 输入

```
3
3 65
45 10
60 25 
```

### 输出

```
32```

## 样例 #2

### 输入

```
3
5 5
6 7
8 8 
```

### 输出

```
5```

# 题解

## 作者：yx666 (赞：1)

# P7194 CESTARINE 题解
[原题面传送门](https://www.luogu.com.cn/problem/P7194)
## Part 1：题意
### Part 1.1：题目内容
给定两个长度为 $n$ 的数列 $a$ 和 $b$，满足同一数列中元素互不相同（$a$ 对应题目中所有的入口，$b$ 对应所有的出口）。

求将数列 $a$ 随机打乱后，并满足 $\forall i\in[1,n]$，$a_i\ne b_i$ 时，$\sum_{i=1}^n \left|a_i-b_i\right|$ 的最小值。

### Part 1.2：限制
- $n\in[1,10^5]$。

- $\forall i\in[1,n],a_i,b_i\in[1,10^6]$。

- 时间：$1$ s，空间 $32$ MB，所有输入均为整数。

## Part 2：思路
考虑 dp。

### Part 2.1：定义问题状态
对 $a$、$b$ 进行排序，接着设 $f_k$ 表示将前 $k$ 个出入口配对后的花费最小值，即：

$$f_k=\begin{cases}\sum_{i=1}^k \left|a_i-b_i\right|\qquad&\forall i\in[1,k]，a_i\ne b_i
\\\inf &\text{otherwise} \end{cases}$$

### Part 2.2：状态转移方程
定义函数 $ckabs$：

$$ckabs(x)=\begin{cases}\left|x\right|& x\ne0\\\inf &x=0
\end{cases}$$

#### Part 2.2.1：$a_i$ 与 $b_i$ 配对：
$$f_i=f_{i-1}+ckabs(a_i-b_i)$$ 

#### Part 2.2.2：$a_i,a_{i-1}$ 与 $b_i,b_{i-1}$ 相互配对：
此时只用考虑 $(a_i,b_{i-1})$ 与 $(a_{i-1},b_i)$：

$$f_i=\min(f_i,f_{i-2}+ckabs(a_i-b_{i-1})+ckabs(a_{i-1}-b_i))$$

#### Part 2.2.3：三对数配对：
借助贪心的思想，发现：对于 $a_i\footnotesize(i\in[2,n-1])$ 最优的搭配，是将它与 $b_{i-1}$、$b_i$ 或 $b_{i+1}$ 搭配时（即让 $a_{i-1},a_i,a_{i+1}$ 与 $b_{i-1},b_i,b_{i+1}$ 互相搭配，花费最小时就是最优搭配）。

改一下下标，有以下三种搭配：

1. $(a_i,b_{i-1}),(a_{i-1},b_{i-2}),(a_{i-2},b_i)$。
2. $(a_i,b_{i-2}),(a_{i-1},b_{i-1}),(a_{i-2},b_i)$。
3. $(a_i,b_{i-2}),(a_{i-1},b_i),(a_{i-2},b_{i-1})$。

得到状态转移方程：

$$f_i=\begin{cases}\min(f_i,f_{i-3}+ckabs(a_i-b_{i-1})+ckabs(a_{i-1},b_{i-2})+ckabs(a_{i-2},b_i))\\
\min(f_i,f_{i-3}+ckabs(a_i-b_{i-2})+ckabs(a_{i-1},b_{i-1})+ckabs(a_{i-2},b_i))\\
\min(f_i,f_{i-3}+ckabs(a_i-b_{i-2})+ckabs(a_{i-1},b_{i})+ckabs(a_{i-2},b_{i-1}))\end{cases}$$

#### Part 2.2.4：四对数配对
重复了，因为四对数可以被拆成两个两对数。

### Part 2.3：初始化与边界状态
- 初始化：注意下标，对 $f_1$，$f_2$ 特殊关照：

$$f_1\gets ckabs(a_1-b_1)\\f_2\gets\min(f_1+ckabs(a_2-b_2),ckabs(a_1-b_2)+ckabs(a_2-b_1))$$

- 边界状态：$i=n$。

### Part 2.4：计算顺序与答案
- 计算顺序：$1\to n$。

- 答案：$f_n$。

## Part 3：代码实现
注意开 `long long`。

``` cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

#define T int
inline T read(){T x=0;char ch=getchar();while(ch<'0'||'9'<ch) ch=getchar();while('0'<=ch&&ch<='9') {x=(x<<3)+(x<<1)+(ch-'0');ch=getchar();}return x;}
void write(T x){if(x>9) write(x/10);putchar(x%10+'0');return ;}
#undef T

constexpr int inf=0x3f3f3f3f;

inline int min(int x,int y){return x<y?x:y;}

#define N 100005
#define pii pair<int,int>

int n;
int a[N],b[N],f[N];
signed main(){
	n=read();
	for(int i=1;i<=n;++i){
		a[i]=read(),b[i]=read();
	}
	
	sort(a+1,a+1+n),sort(b+1,b+1+n);
	
	auto ckabs=[](int x){return x==0?inf:x<0?-x:x;};
	
	f[1]=ckabs(a[1]-b[1]);
	f[2]=min(f[1]+ckabs(a[2]-b[2]),ckabs(a[1]-b[2])+ckabs(a[2]-b[1]));
	for(int i=3;i<=n;++i){
		f[i]=f[i-1]+ckabs(a[i]-b[i]);
		f[i]=min(f[i],f[i-2]+ckabs(a[i]-b[i-1])+ckabs(a[i-1]-b[i]));
		f[i]=min(f[i],f[i-3]+ckabs(a[i]-b[i-1])+ckabs(a[i-1]-b[i-2])+ckabs(a[i-2]-b[i]));
		f[i]=min(f[i],f[i-3]+ckabs(a[i]-b[i-2])+ckabs(a[i-1]-b[i-1])+ckabs(a[i-2]-b[i]));
		f[i]=min(f[i],f[i-3]+ckabs(a[i]-b[i-2])+ckabs(a[i-1]-b[i])+ckabs(a[i-2]-b[i-1]));
	}
	write(f[n]);
	return 0;
}
```

[AC 记录（目前最优解）](https://www.luogu.com.cn/record/158765760)。

---

## 作者：_Fontainebleau_ (赞：1)

## CESTARINE

### 题意
给定长度为 $n$ 的序列 $a$ 和 $b$，$\forall i,j \in[1,m],i\not =j$ 有 $a_i\not =a_j,b_i \not =b_j$。求将 $a$ 的元素随意打乱后，满足$\forall i\in {[1,n]},a_i \not = b_i$时， $\sum\limits_{i=1}^n|a_i-b_i|$ 的最小值。

### 做法

考虑 dp。

首先对 $a,b$ 排序。然后从后往前逆推。考虑每次决策的窗口大小最大为多少。

显然，当窗口大小为 $2$ 时，该窗口内不会存在 $a_i=b_i,a_{i+1}=b_{i+1}$ 的不合法情况。

但是很良心的样例 2 给了我们提示。

| $a_i$ | $b_i$ |
| ----- | ----- |
| 5     | 5     |
| 6     | 7     |
| 8     | 8     |

如果每次至多考虑两个窗口，则 $3=1+2=2+1$，不是 $a_1=b_1$ 就是 $a_3=b_3$。

于是我们想到，窗口大小为 $3$ 可以吗？

其实是可以的。具体而言，对于一个数 $n$，若 $n \bmod 3=0$，则显然可以；若 $n\bmod 3=1$，则少选一个 $3$，搞成两个 $2$，即可；若 $n\bmod 3=2$，显然可以。

所以，窗口大小最大为 $3$，每次只需要暴力枚举 $3!$ 种匹配情况即可。

于是这道题就被我们解决了。

注：代码中的 $f_i$ 表示从后往前匹配，当前匹配到第 $i$ 位的最小值。

```c++
#include<bits/stdc++.h>
using namespace std;
int n,m,p[5];
int a[100005],b[100005];
long long f[100005];
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
long long calc(int x,int y)
{
	if(x==y)	return 1ll*1<<60;
	return abs(x-y);
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)	a[i]=read(),b[i]=read();
	sort(a+1,a+1+n),sort(b+1,b+1+n);
	memset(f,63,sizeof(f));
	f[n+1]=0;
	for(int i=n;i>=1;i--)
		for(int k=1;k<=3&&i+k<=n+1;k++)
		{
			for(int j=0;j<k;j++)	p[j]=j;
			do{
				long long cost=0;
				for(int j=0;j<k;j++)	cost+=calc(a[i+j],b[i+p[j]]);
				f[i]=min(f[i],cost+f[i+k]);
			}while(next_permutation(p,p+k));
		}
	printf("%lld\n",f[1]);
	return 0;
}
```



---

## 作者：ShwStone (赞：1)

## Luka ~~（开车）~~ 开卡车

### 题面描述

Luka 有 $n$ 辆卡车行驶在一条高速路上。高速路上有许多出入口。我们认为相同编号的出入口在同一位置。开进高速路后，司机会收到一张写着他入口号的单子。驶出时，驾驶员支付的通行费等于出入口号的差的绝对值。例如，如果单子上的入口 $30$ ，然后在出口 $12$ 退出，那么会花费 $|30 - 12| = 18$ 元。

Luka 是一个爱贪小便宜的人。他发现即使卡车的路线并不重叠，司机们仍然可以在高速路上交换他们的单子。但是，同一辆卡车不能在同一位置的出入口进行上高速与下高速。

请你编程求出最少的通行费。

### 思路分析

这个题和卡车没什么关系，不要用结构体把入口和出口存在一起。这个题就是让我们把入口与出口配对，让差的绝对值的和最小。

对于入口和出口分别排序后，定义状态 $f(i)$ 表示后 $i$ 个入口和出口的最小的差的绝对值和。那怎么转移 $f(i)$ 呢？我们只需要枚举后三个即可，也就是 $f(i)$ 与 $f(i+1),f(i+2)$ 有关。为什么呢？

四个出入口可以拆分成 $1 + 3$, $2 + 2$, $3 + 1$ ，也就是说，再次计算四个入口是没有意义的。

将 $f(i)$ 初始化为 $inf$ ，然后计算 $i,i - 1,i - 2$ 的全排列中的最小代价 $cost$ ，最后 $f(i) = cost + f(i)$ 。

这个题建议评普及+。

### AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define uns unsigned
#define ll long long
#define use_cin_cout do {ios::sync_with_stdio(false); /*cin.tie();*/} while(false)
#define endl '\n'

const ll inf_ll = 0x3f3f3f3f3f3f3f3f;
const int inf = 0x3f3f3f3f, mod = 1e9 + 7;
const int maxn = 1e5 + 5;

int n;
int in[maxn], out[maxn], num[10];
ll dp[maxn];

ll cal(int a, int b) {
    return (a == b) ? 1ll << 60 : abs(a - b); // 
}

int main() {
    use_cin_cout;
    // freopen("cestarine.in", "r", stdin);
    // freopen("cestarine.out", "w", stdout);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> in[i] >> out[i];
    }

    sort(in + 1, in + n + 1);
    sort(out + 1, out + n + 1);

    memset(dp, 63, sizeof(dp));
    dp[n + 1] = 0;
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= 3 && i + j - 1 <= n; j++) {
            for (int k = 0; k < j; k++) num[k] = k;
            do {
                ll cost = 0;
                for (int k = 0; k < j; k++) cost += cal(in[i + k], out[i + num[k]]);
                dp[i] = min(dp[i], cost + dp[i + j]);
            } while (next_permutation(num, num + j));
        }
    }

    cout << dp[1] << endl;

    return 0;
}
```

---

## 作者：Wander_E (赞：0)

首先忽略出入口不同的限制，这时，一个显然的贪心思路是将 $x,y$ 分别排序，对应位置相减即可。

再考虑如果 $x_i = y_i$ 怎么办。容易发现，将 $i,i-1,i+1$ 这三个位置进行交换，一定能够构造出一组合法解。

于是考虑 dp。注意到在上述过程中，我们要考虑 $i + 1$ 这个位置，不利于转移（因为 $i+1$ 尚未填好）所以把 dp 式子改成考虑 $i-2,i-1,i$ 这三个位置的形式。排列组合后得到以下式子（注意：当两数相等时建议让绝对值函数返回 $\infty$ 这样就不用判断了）。

$$\begin{aligned}
& f_i=f_{i-1}+\lvert a_i -b_i\rvert\\ 
& f_i=\min\{f_i,f_{i-2}+\lvert a_i-b_{i-1}\rvert+\lvert a_{i-1} - b_i\rvert\}\\
& f_i=\min\{f_i,f_{i-3}+\lvert a_i-b_{i-2}\rvert+\lvert a_{i-1}-b_{i-1}\rvert+\lvert a_{i-2} - b_i\rvert\}\\ 
& f_i=\min\{f_i,f_{i-3}+\lvert a_{i}-b_{i-2}\rvert+\lvert a_{i-1} - b_{i}\rvert+\lvert a_{i-2}-b_{i-1}\rvert\}\\
& f_i=\min\{f_i,f_{i-3}+\lvert a_i-b_{i-1}\rvert+\lvert a_{i-1} - b_{i-2}\rvert+\lvert a_{i-2}-b_{i}\rvert\}\\

\end{aligned}$$


```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using std::cin, std::cout, std::max, std::min, std::sort;
const int N = 1e5 + 5;
int n, a[N], b[N];
int f[N];
int abss(int x)
{
    if (x)
        return (x > 0 ? x : -x);
    return 0x3f3f3f3f3f3f3f3f;
}
signed main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i] >> b[i];
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);
    f[1] = abss(a[1] - b[1]);
    f[2] = min(f[1] + abss(a[2] - b[2]), abss(a[1] - b[2]) + abss(a[2] - b[1]));
    for (int i = 3; i <= n; i++)
    {
        f[i] = f[i - 1] + abss(a[i] - b[i]);
        f[i] = min(f[i], f[i - 2] + abss(a[i] - b[i - 1]) + abss(a[i - 1] - b[i]));
        f[i] = min(f[i], f[i - 3] + abss(a[i] - b[i - 2]) + abss(a[i - 1] - b[i - 1])) + abss(a[i - 2] - b[i]);
        f[i] = min(f[i], f[i - 3] + abss(a[i] - b[i - 2]) + abss(a[i - 1] - b[i])      + abss(a[i - 2] - b[i - 1]));
        f[i] = min(f[i], f[i - 3] + abss(a[i] - b[i - 1]) + abss(a[i - 1] - b[i - 2])  + abss(a[i - 2] - b[i]));
    }
    cout << f[n] << endl;
    return 0;
}
```

---

## 作者：liuyidu (赞：0)

### 题意简述：
有 $n$ 个整数 $x_i$ 和 $n$ 个整数 $y_i$。使每个 $A_i$ 恰好对应一个 $B_{p[i]}$。要求所有配对的整数差的绝对值之和尽量小，且不允许两个相同的数配对。

### 做法：
这题第一眼看就大概有一个贪心的思路了，首先排序，然后每位依次匹配就好了，但是题目有个限制条件 $a_i \ne b_i$，这就有些难搞了，接下来讨论一下如果遇到相等的情况该如何匹配。

首先，肯定能想到进一步的贪心做法，如果某一位对应相等，那我们就在前面找一位或者后面找一位换一下，但是这样的话需要处理的就比较多了。

那么我们考虑 dp ，这里的 dp 定义较为简单，就不展开了，重点讲一下怎么转移，按上面的方法转移肯定是没法写的，因为你无法保证你前后前后交换之后没有相同的，既然不能前后来回换，为什么不能直接在最后面处理呢，要知道我们写的是 dp 啊。

这里又有另外一个贪心，一个数肯定是和离得越近的数配越好，同时相邻三个数必然存在一种配对方式，那么就知道了，每个数只可能和它前面的一个配或者和后面一个配。

到这里就解决了，我们在计算的时候给相等的数定义一个极大值，那么就可以选择性避开不合法的配对了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,inf=1e9+7;
int n,a[N],b[N],dp[N];
inline int cal(int x,int y){
	return x==y?inf:abs(x-y);
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i]>>b[i];
	}
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	if(n==1&&a[1]==b[1]){cout<<-1;return 0;}
	dp[1]=cal(a[1],b[1]);
	dp[2]=min(dp[1]+cal(a[2],b[2]),cal(a[1],b[2])+cal(a[2],b[1]));
	for(int i=3;i<=n;++i){
		dp[i]=dp[i-1]+cal(a[i],b[i]);
		dp[i]=min(dp[i],dp[i-2]+cal(a[i-1],b[i])+cal(a[i],b[i-1]));
		dp[i]=min(dp[i],dp[i-3]+cal(a[i-2],b[i-1])+cal(a[i-1],b[i])+cal(a[i],b[i-2]));
		dp[i]=min(dp[i],dp[i-3]+cal(a[i-2],b[i])+cal(a[i-1],b[i-2])+cal(a[i],b[i-1]));
	}
	cout<<dp[n];
	return 0;
}
```

---

