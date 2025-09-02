# [ABC154D] Dice in Line

## 题目描述

给出 $N$ 个骰子，我们同时投掷 $K$ 个连续骰子。求出可能的最大数学期望值。

## 说明/提示

本题使用**Special Judge**，你的答案和数据误差小于等于$10^{-6}$就会被评判对

## 样例 #1

### 输入

```
5 3
1 2 2 4 5```

### 输出

```
7.000000000000```

## 样例 #2

### 输入

```
4 1
6 6 6 6```

### 输出

```
3.500000000000```

## 样例 #3

### 输入

```
10 4
17 13 13 12 15 20 10 13 17 11```

### 输出

```
32.000000000000```

# 题解

## 作者：Blikewsr (赞：6)

 - [$\color{lightgreen}\text{[AT5300 原题链接]}$](https://www.luogu.com.cn/problem/AT5300)                               

 - 题目描述                 
   给出 `N` 个骰子， 同时投掷 `K` 个连续骰子, 要求出可能的最大数学期望值。 
   
 - 输入格式            
   第一行两个数， `N` 和 `K` .
   第二行 `N` 个数, 代表每一个骰子的面数。
   
 - 输出格式               
   一个 `12` 位的小数， 表示最大数学期望值。
  
 - 思路         
   首先， 我们要先知道， 数学期望值是什么？
   
   数学期望值是试验中每次可能的结果乘以其结果概率的总和。 
   
   也就是说在骰子里的数学期望值就是它的所有面的点数之和除以它的面数。
   我们假设这是一个有 `n` 面的骰子， 那么它的数学期望值就是：
   
   $$\frac{1+2+3+...+(n-2)+(n-1)+n}{n}$$
   
   根据我们的观察， 可以发现， $(1+2+3+...+(n-2)+(n-1)+n)$ 是一个等差数列求和的式子。
   
   我们知道， 等差数列求和公式是 $\frac{(1+n)n}{2}$ .
   
   所以， 把上面的式子化简一下就成了这样：
   
   $$\frac{\frac{(1+n)n}{2}}{n}$$
   
   我们再把 `n`  约分掉， 最终就成了这样：
   
   $$\frac{1+n}{2}$$
   
   知道了这个式子， 那这题就简单了。
   
   因为是连续的骰子， 所以我们只需要用一个前缀和数组把答案存起来就行了， 最后在用 `for` 循环和前缀差求出最大值就行了。

 - 代码实现
 ```cpp
 #include <bits/stdc++.h>
 #define N 200001
 #define int long long
 using namespace std;
 int n, k;
 double prefix[N], p[N], maxn;
 signed main() {
 	cin >> n >> k;
 	for(int i = 1; i <= n; i++) {
 		cin >> p[i];
 		p[i] = (1 + p[i]) / 2;
 		prefix[i] = prefix[i - 1] + p[i];
 	}
 	for(int i = k; i <= n; i++) {
 		maxn = max(maxn, prefix[i] - prefix[i - k]);
 	}
 	printf("%0.12lf\n", maxn);
 	return 0;
 }
 ```
 
 - 此题解仅供参考， 谢谢 ！

---

## 作者：Anaxagoras (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT5300)

$update\ 2022.01.04$ 修改了一些没注意到的错误。

思路：

首先我们要知道什么叫数学期望值。数学期望值就是试验中每次可能的结果乘以其结果概率的总和。所以我们可以先推一下 n 面骰子的公式。

$$\frac{1+2+3+...+n}{n}=\frac{\frac{(n+1)n}{2}}{n}=\frac{\frac{n^2+n}{2}}{n}=\frac{n+1}{2}$$

由于求的是**连续**的骰子，所以我们可以用一个前缀和数组存下来，求最大期望值可以用 01 背包的思想：我要么不存这个区间，要么存下来，于是就有了这个转移方程：

$$maxx=\max(maxx,sum[i]-sum[i-k])$$

这似乎就是 01 背包。那么存储和 dp 都是 $\Theta(n)$，加起来仍然是 $\Theta(n)$，数据范围 $1 \leq K \leq N \leq 200000$，不会超时（但是 1000.00MB 是真的吓人）

AC Code：

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
double a[200005];
double sum[200005];//前缀和数组
inline double maxx(double x,double y)
{
  if(x>y)
    {
      return x;
    }
  return y;
}
signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);//加速
  int n,k;
  cin>>n>>k;
  double max=0;
  for(int i=1;i<=n;i++)
    {
      cin>>a[i];
      a[i]=(a[i]+1)/2;//套期望值公式
      sum[i]=sum[i-1]+a[i];//前缀和存储
    }
    for(int i=k;i<=n;i++)//直接从第 k 个开始
    {
    	max=maxx(max,sum[i]-sum[i-k]);
	}
	printf("%.12lf\n",max);
  return 0;
}

```

写题解不容易，所以点个赞吧！

---

## 作者：Binary_Lee (赞：3)

## [题面传送门](https://www.luogu.com.cn/problem/AT5300)

不知为何评绿？

### 解决思路

首先，一颗面数已知的骰子掷出的点数期望值是固定的，假设它有 $k$ 面，则期望为 $\frac {\sum_{i = 1}^{k} i} k$ 。然后看数据范围，最多只有 $10^3$ 面，所以完全可以将每个骰子的期望点数预处理出来，然后原题就变成了求最大定长子段和，用前缀和可以轻松解决。


### AC Code

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
using namespace std;
double f[1005],s[200005],now,ans;
int n,k,a;
signed main(){
	IOS;TIE;
	cin>>n>>k;
	for(int i=1;i<=1000;i++) now+=(double)i,f[i]=now/(double)i;
	for(int i=1;i<=n;i++) cin>>a,s[i]=s[i-1]+f[a];
	for(int i=k;i<=n;i++) ans=max(ans,s[i]-s[i-k]);
	cout<<fixed<<setprecision(16)<<ans<<endl;
	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

注意到每个骰子出现某个数字的概率是独立的，所以期望可以很好的加起来。

对与一个包含 $1$ 到 $m$ 的骰子，它期望出现数字是

$$\frac{1+2+\dots+m}{m}=\frac{\frac{m(m+1)}{2}}{m}=\frac{m(m+1)}{2m}=\frac{m+1}{2}$$

所以，可以把一个 $1$ 到 $m$ 的骰子的权值设为 $m+1$；用一个滚动区间维护区间权值和与所遇到的区间权值和的最大值。

答案是这个最大区间权值和除以二。

注意不能使用`double`输出，应为可能答案特别大的时候不输出整个数字。

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;
 
#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

int aray[200005];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int N, K; cin >> N >> K;
    ll v = 0, bes = 0; int cnt = 0;
    rep(i, N) {
        cin >> aray[i]; aray[i]++;
        v += aray[i];
        bes = max(bes, v);
        cnt++;
        if(cnt == K) {
            v -= aray[i-K+1];
            cnt--;
        }
    }
    cout << bes/2;
    if(bes%2) cout << ".5";
    cout << endl;
}

```

---

## 作者：Ninelife_Cat (赞：1)

本题要求连续 $k$ 个骰子点数的期望值最大。

对于某个骰子，它的点数的期望值就是它所有面的点数之和除以它的面数。

如果它有 $x$ 面，那么它的期望值就是:

$$\frac{1+2+...+ \left( x-1 \right)+x}{x}$$

然后这个式子变形一下就是:

$$\frac{\frac{\left( 1+x \right) \times x}{2}}{x}$$

化简之后就得到：

$$\frac{1+x}{2}$$

所以我们可以在输入的时候处理出每个骰子的点数的期望值，前缀和一下就能快速求区间最大值了。


核心代码：
```cpp
const int N=2e5+10;
int n,k;
double s[N],p[N],ans;//s为前缀和数组
signed main()
{
	n=read();k=read();
	for(ri int i=1;i<=n;++i)
		p[i]=read(),p[i]=(p[i]+1)/2,s[i]=s[i-1]+p[i];
	for(ri int i=k;i<=n;++i)
		ans=fmax(ans,s[i]-s[i-k]);
	cout<<fixed<<setprecision(12)<<ans;
	return 0;
}

---

## 作者：Kizuna_AI (赞：1)

这道题目主要求的是$k$个连续骰子数学期望最大的情况。


------------

如果你不知道数学期望是什么，你可以去看[洛谷日报#211](https://45475.blog.luogu.org/mathematical-expectation)。在这里我只简要讲解一下。


------------

求单个骰子的数学期望：就是将骰子的全部点数加起来再除以骰子的面数。  
这里要求的是$k$个连续骰子的数学期望和最大，只需将$k$个骰子的数学期望加起来就行了。


------------


代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,k,p[200010];
double each[200010],now,ans=0;
int main() {
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i]);
	for(int i=1;i<k;i++) { //先求出前k-1个
		each[i]=(double)(1+p[i])*p[i]/2.0/p[i]; //每个骰子的数学期望
		now+=each[i]; //加上前k-1的数学期望
	}
	for(int i=k;i<=n;i++) {
		each[i]=(double)(1+p[i])*p[i]/2.0/p[i]; //每个骰子的数学期望
		ans=max(ans,now); //获取每前k个数学期望的值
		now+=each[i];   //统计第i个并删除第i-k个
		now-=each[i-k];
	}
	ans=max(ans,now);
	cout<<fixed<<setprecision(9)<<ans;
	return 0;
}

```

---

## 作者：panyanppyy (赞：0)

记得模拟赛的时候瞪了好一会才做出来。
## Solution
对于单个 $x$ 面的骰子，投出的期望数字是:

$$ \dfrac{1+2+\cdots +x}{x}=\dfrac{\dfrac1 2x(1+x)}{x}=\dfrac{1+x} 2$$

然后由于是要 $k$ 个**连续**的骰子的和，所以做一下前缀和，直接求:

$$\overset{\underset{\normalsize\max}{\scriptsize  n}}{\scriptsize {i=k}} \overset{\normalsize s_i-s_{i-k}}{}$$

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) (x).begin(),(x).end()
using namespace std;
template<typename T_>void operator+=(vector<T_>&x,T_ y){x.emplace_back(y);}
int n,k;
double ans;
vector<double>s(1);
vector<int>a(1);
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1,x;i<=n;i++)cin>>x,a+=x;
	for(int i=1;i<=n;i++)s+=s.back()+(a[i]+1)/2.;
	for(int i=k;i<=n;i++)ans=max(ans,s[i]-s[i-k]);
	cout<<fixed<<setprecision(10)<<ans<<'\n';
	return 0;
}

```

---

