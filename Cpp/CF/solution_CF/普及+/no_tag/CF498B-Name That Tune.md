# Name That Tune

## 题目描述

It turns out that you are a great fan of rock band AC/PE. Peter learned that and started the following game: he plays the first song of the list of $ n $ songs of the group, and you have to find out the name of the song. After you tell the song name, Peter immediately plays the following song in order, and so on.

The $ i $ -th song of AC/PE has its recognizability $ p_{i} $ . This means that if the song has not yet been recognized by you, you listen to it for exactly one more second and with probability of $ p_{i} $ percent you recognize it and tell it's name. Otherwise you continue listening it. Note that you can only try to guess it only when it is integer number of seconds after the moment the song starts playing.

In all AC/PE songs the first words of chorus are the same as the title, so when you've heard the first $ t_{i} $ seconds of $ i $ -th song and its chorus starts, you immediately guess its name for sure.

For example, in the song Highway To Red the chorus sounds pretty late, but the song has high recognizability. In the song Back In Blue, on the other hand, the words from the title sound close to the beginning of the song, but it's hard to name it before hearing those words. You can name both of these songs during a few more first seconds.

Determine the expected number songs of you will recognize if the game lasts for exactly $ T $ seconds (i. e. you can make the last guess on the second $ T $ , after that the game stops).

If all songs are recognized faster than in $ T $ seconds, the game stops after the last song is recognized.

## 样例 #1

### 输入

```
2 2
50 2
10 1
```

### 输出

```
1.500000000
```

## 样例 #2

### 输入

```
2 2
0 2
100 2
```

### 输出

```
1.000000000
```

## 样例 #3

### 输入

```
3 3
50 3
50 2
25 2
```

### 输出

```
1.687500000
```

## 样例 #4

### 输入

```
2 2
0 2
0 2
```

### 输出

```
1.000000000
```

# 题解

## 作者：Exschawasion (赞：4)

按套路先设状态：设 $f[i][j]$ 在第 $j$ 秒认出第 $i$ 首歌的概率。

然后就可以列状态转移。枚举这首歌已经放了的秒数 $k$：

$$f[i][j]=f[i-1][j-t_i]\times(1-p_i)^{t_i}+\sum^{t_i}_{k=1}(p_i\times (1-p_i)^{k-1}\times f[i-1][j-k]\color{black})$$

第一项的意义是显然的：一直都没有听出来。

第二项，在 $f[i-1][j-k]$ 前面的那个系数表示**在第 $k$ 秒认出来**的概率，这等价于前 $k-1$ 秒没认出来、第 $k$ 秒认出来。所以要乘上 $k-1$ 次幂而非 $k$ 次幂。

请思考 $f[i][j]$ 的意义。它是在**特定时间**听出**特定歌曲**的概率，类似于一个特定事件的概率。期望应当是**所有事件**的概率乘上所有事件的贡献。听出一首特定歌曲的贡献是 $1$，所以最终答案应当是所有概率乘上 $1$ 的总和，即：

$$\sum_{i=1}^{n}\sum_{j=i}^{T}f[i][j]\times 1$$


直接转移是 $O(nT^2)$ 的。考虑优化，根据“分离无关项”的优化原则，把与 $k$ 无关的项提出去（省略转移的其他部分）：

$$p_i\times\sum^{t_i}_{k=1}( (1-p_i)^{k-1}\times f[i-1][j-k]\color{black})$$


一个很显然的思路是前缀和优化掉那个求和符号：开个 $g$ 数组保存前缀和，然后乘上对应的系数（可预处理）。先把代码难度放一边，数组空间就吃紧（滚动数组能帮你优化 $g$，但是系数还是比较难滚动处理的？试过但是失败了）。

实际上你会发现只要单独开一个变量保存 $f[i-1][j-k]$ 的前缀和就行了。当 $j>t_i$ 时，$j-t_i$ 之前的部分都不会累加进来，因此需要在 $j>t_i$ 时减去 $f[i][j-t_i-1] \times (1-p_i)^{t_i}$。稍微抽象一点，可以类比成单调队列优化的时候从队头踢掉那些过时决策。

不要开 `long double`，或者请把 $f$ 数组滚动化，不然会 MLE。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5000+10;
typedef double db;
int n,T;
int t[maxn];
db p[maxn],f[maxn][maxn];
db qpow(db a,int b){
	db ans=1;
	for(;b;b>>=1,a=a*a)if(b&1)ans*=a;
	return ans;
}
int main(){
	cin>>n>>T;
	for(int i=1;i<=n;i++)cin>>p[i]>>t[i],p[i]/=100.0;
	f[0][0]=1.0;
	for(int i=1;i<=n;i++){
		db sum=0;
		int id=i,rid=i-1;
		for(int j=i;j<=T;j++){
			sum=sum*(1.0-p[i])+f[rid][j-1];//累加前缀和
			if(j>t[i])sum-=f[rid][j-t[i]-1]*qpow(1.0-p[i],t[i]);//去除多余项
			if(j>=t[i])f[id][j]+=f[rid][j-t[i]]*qpow(1.0-p[i],t[i]);//注意边界
			f[id][j]+=sum*p[i];//转移
		}
	}
	db ans=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=T;j++)ans+=f[i][j];
	cout<<fixed<<setprecision(6)<<ans;
}
```



---

## 作者：sxyugao (赞：3)

[推销博客QAQ](https://sxyugao.top/p/d7051add.html)

看见题目就想到期望DP。

第一眼想到的方程是设 $f_{i,j}$ 表示第 $i$ 秒识别到第 $j$ 首歌的期望，不难想出一个 $O(n^3)$ 的算法。

枚举一个 $k$ 表示第 $j$ 首歌已经放了几秒，注意一下边界即可。

转移如下：

```cpp
  double ans = 0;
  f[0][0] = 1; // 初始化
  for (int i = 1; i <= T; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= i && k < t[j]; k++)
        f[i][j] += f[i - k][j - 1] * pow(1 - p[j], k - 1) * p[j];
      if (i >= t[j]) f[i][j] += f[i - t[j]][j - 1] * pow(1 - p[j], t[j] - 1);
      // 单独考虑默认被识别的状况
      ans += f[i][j];
      // 第 i 秒听到了第 j 首的概率，相当于多了 1 首，直接加到 ans 里
    }
  }
}
```

但是发现这题 $N \leq 5000$，$O(n^3)$ 的复杂度显然过不了，但是这个DP方程感觉优化不下去了（可能只是我菜）。。

考虑换一个思路 $f_{i,j}$ 表示第 $i$ 首歌放完是第 $j$ 秒，可以写出这样的方程（~~其实只是把上面方程的 i, j 反了一下~~）：

```cpp
	double ans = 0;
	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= T; j++) {
			for (int k = 1; k <= j && k < t[i]; k++)
				f[i][j] += f[i - 1][j - k] * pow(1 - p[i], k - 1) * p[i];
			if (j >= t[i]) f[i][j] += f[i - 1][j - t[i]] * pow(1 - p[i], t[i] - 1);
			ans += f[i][j];
		}
```

然后我们发现了有趣的事情：$f_{i,j}$ 和 $f_{i,j-1}$ 咋这么像呢？！很显然 $k$ 那一维可以用类似前缀和一样的东西优化掉，因为 $f_{i,j}$ 和 $f_{i,j-1}$ 差的基本上只有 $(1-p_i)$ 的概率。

但是直接前缀和是有问题的，当 $j > t_i$ 时明显会把 $t_i \leq j$ 的情况给算重了，所以要减去。

以下为完整代码：

```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
char buf[1 << 14], *p1 = buf, *p2 = buf;
inline char gc() {
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 14, stdin), p1 == p2) ? EOF : *p1++;
}
inline int read() {
  int x = 0, f = 1;
  char c = gc();
  for (; !isdigit(c); c = gc())
    if (c == '-') f = -1;
  for (; isdigit(c); c = gc()) x = x * 10 + c - '0';
  return x * f;
}
const int N = 5005;
double p[N], f[N][N];
int t[N];
int main() {
  int n = read(), T = read();
  for (int i = 1; i <= n; i++) {
    p[i] = 1.0 * read() / 100;
    t[i] = read();
  }
  double ans = 0;
  f[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    double sum = 0;
    double lst = pow(1 - p[i], t[i] - 1);
    for (int j = 1; j <= T; j++) {
      sum *= 1 - p[i];
      sum += f[i - 1][j - 1] * p[i];
      if (j >= t[i]) {
        sum -= f[i - 1][j - t[i]] * lst * p[i];
        f[i][j] += f[i - 1][j - t[i]] * lst;
      }
      f[i][j] += sum;
      ans += f[i][j];
    }
  }
  printf("%.9lf", ans);
}
```


---

## 作者：Lgx_Q (赞：2)

## 题意

用 $1...n$ 这些数字填充一个长度为 $T$ 的数组，按顺序从左到右填充，数字 $i$ 每填充一个位置都有 $p_i$ 的概率换到下一个数字 $i+1$，当填充到 $t_i$ 个数字后强制结束。当填充完数字 $n$ 后直接结束。

问填充的数字种数的期望。

## 分析

考虑数字 $n$ 填充多少位置。

假设填充了 $i$ 个位置，那么剩下 $n-1$ 个数需要填 $T-i$ 个格子，构成子问题。

明显动态规划。

设 $f[i][j]$ 表示填了 $j$ 个格子后，最后填入了数字 $i$ 的概率。

计算总答案时应考虑每一个数字填入的概率来计算期望，即

$$\sum_{i=1}^{n}\sum_{j=1}^{T}f[i][j]×1$$

接下来分析如何转移。

枚举 $i$ 填了 $k$ 个格子后换到下一个数字，那么容易想到方程：

$$f[i][j]=f[i-1][j-t_i]×(1-p_i)^{t_i}+\sum_{k=1}^{t_i}f[i-1][j-k]×(1-p_i)^{t_i-1}×p_i$$

## 优化

上述的 DP 时间复杂度为 $O(nT^2)$，考虑在转移时优化。

拆式子得

$$f[i][j]=f[i-1][j-t_i]×(1-p_i)^{t_i}+p_i(\sum_{k=1}^{t_i}f[i-1][j-k]×(1-p_i)^{t_i-1})$$

于是思考如何快速计算后半部分。

对于 $f[i][j]$ 和 $f[i][j+1]$ 而言，关于 $k$ 的转一部分大部分是相同的。

$f[i][j]$ 的转移部分变换到 $f[i][j+1]$ 的转移部分：

$$\sum_{k=1}^{t_i}f[i-1][j-k]×(1-p_i)^{t_i-1}→(1-p_i)(\sum_{k=1}^{t_i-1}f[i-1][j-k]×(1-p_i)^{t_i-1})+f[i-1][j]$$

更形象地说：

![](https://cdn.luogu.com.cn/upload/image_hosting/ejuvcahh.png?x-oss-process=image/resize,m_lfit,h_500,w_500)

因此，从 $j$ 变到 $j+1$ 时，应删去之前的无用决策（如图中的```j-5```），然后把目前决策的答案乘上 $(1-p_i)$.

时间复杂度 $O(nT)$。

至于空间优化，可以用滚动数组。

## 注意事项

本题十分卡常，本人被 #67 卡了 N 次代码。（计算 $(i-p_i)^{t_i}$ 时要用 ```pow```，别枚举！！）

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
using namespace std;
const int maxn=5010;
int n,T,t[maxn];
double f[2][maxn],sum,p[maxn],pw,ans;
int read()
{
	int n=0;
	char c;
	while(!isdigit(c=cin.get()));
	n=c-'0';
	while(isdigit(c=cin.get())) n=n*10+c-'0';
	return n;
}
int main()
{
	n=read(); T=read();
	for(int i=1;i<=n;i++)
	{
		int _p;
		_p=read();
		t[i]=read();
		p[i]=_p/100.00;
	}
	f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		sum=0;
		pw=pow(1-p[i],t[i]);
		int _i=i&1,_i2=_i^1;
		int _t=t[i];
		double t1=p[i],t2=1-t1;
		for(int j=0;j<=T;j++)
		{
			if(j<i)
			{
				f[_i][j]=0;
				continue;
			}
			sum=sum*t2+f[_i2][j-1];
			if(j>=_t+1) sum-=f[_i2][j-_t-1]*pw;
			if(j>=_t) f[_i][j]=f[_i2][j-_t]*pw;
			else f[_i][j]=0;
			f[_i][j]+=sum*t1;
			ans+=f[_i][j];
		}
	}
	printf("%.9lf",ans);
    return 0;
}
```

---

## 作者：Prean (赞：2)

咋黑色啊，这不是看到数据范围就去想 $ O(nT) $ 的做法吗？

然后仔细想想最靠谱的就是 DP。

设 $ dp[n][T] $ 表示听完第 $ n $ 首歌，总共听了 $ T $ 秒。

很明显有 $ dp[n][T]=dp[n-1][T-t_n] \times (1-p)^{t_n}+\sum_{i=1}^{t_n}dp[n-1][T-i] \times (1-p)^{i-1} \times p $。

很明显这个是 $ O(nT^2) $ 的，接下来开始优化。

我们先先写成 $ dp[n][T]=\sum_{i=1}^{t_n}dp[n-1][T-i] \times (1-p)^{i-1} $，最后令每一项乘上 $ p $。

发现这个有点儿像把一个长度为 $ t_n $ 的区间当做一个多项式，翻转过来后带入 $ 1-p $，我们考虑每次平移一下这个多项式，再去掉多余的项。

然后你发现这个多项式带入后的值其实就是 $ dp[n][T-1] $，所以并不需要新开一个变量。

预处理一下幂就可以做到 $ O(nT) $ 了。

答案为 $ \sum_{i=1}^n\sum_{j=1}^T dp[i][j] $。
```cpp
#include<cstdio>
#include<cmath>
typedef long double db;
const int M=5005;
int n,m,t;double p,pw,ans,S[M],dp[2][M];
signed main(){
	int i,x;scanf("%d%d",&n,&m);dp[0][0]=1;
	for(int T=1;T<=n;++T){
		scanf("%d%d",&x,&t);p=.01*x;pw=pow(1-p,t);dp[T&1][0]=0;
		for(i=1;i<=m;++i)dp[T&1][i]=dp[T&1][i-1]*(1-p)+dp[T&1^1][i-1],i>t&&(dp[T&1][i]-=dp[T&1^1][i-t-1]*pw);
		for(i=1;i<=m;++i)dp[T&1][i]*=p,i>=t&&(dp[T&1][i]+=dp[T&1^1][i-t]*pw),ans+=dp[T&1][i];
	}
	printf("%.9lf",ans);
}
```

---

## 作者：yuzhechuan (赞：2)

动态规划。

---
f[i][j]表示前i秒时间听了j首歌的概率，则有：

$f[i][j]=∑f[i-k][j-1]*(1-p_j)^{k-1}*p_j$

k枚举i秒前的每一秒，要求前i-1秒都不跳歌，且在第i秒跳歌

这个方程直接转移的时间复杂度为$O(NT^2)$。

---
尝试进行优化。

观察可以发现，f[i][j]与f[i-1][j]的方程基本不变，考虑直接从f[i-1][j]转移到f[i][j]。

时间复杂度降到$O(NT)$。

---
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=5005;
int t[N],n,m;
double p[N],f[N][N];
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lf%d",&p[i],&t[i]);
		p[i]/=100; //变成概率
	}
	/*初始化*/
	f[0][0]=1;
	double sum=0;
	/*DP*/
	for(int i=1;i<=n;i++){
		double ans=0,tp=pow(1-p[i],t[i]);
		for(int j=i;j<=m;j++){
			ans+=f[i-1][j-1];
			if(j-t[i]>=1) ans-=f[i-1][j-t[i]-1]*tp;
			f[i][j]=ans*p[i];
			if(j-t[i]>=0) f[i][j]+=f[i-1][j-t[i]]*tp;
			ans*=1-p[i];
			sum+=f[i][j];
		}
	}
	printf("%.9lf",sum);
}
```

---

## 作者：intel_core (赞：1)

看到 $n,T \le 5000$ 之后就知道这题 `200%` 是 $O(nT)$ 做法。

记 $f_{i,j}$ 表示在 $j$ 时刻听出第 $i$ 首歌的概率是多少。

那么 $f_{i,j}=\sum\limits_{1\le k\le t[i]}f_{i-1,j-k} \times (1-p_i \%)^{k-1}\times p \%+f_{i-1,j-t[i]}\times (1-p_i \%)^k$。

观察到 $\sum\limits_{1\le k\le t[i]}f_{i-1,j-k} \times (1-p_i \%)^{k-1}$ 很明显可以快速维护，所以可以 $O(nT)$ 求出 $f$ 数组。

我们求出 $f$ 数组之后，直接对所有 $f_{i,j}$ 求和就是答案。因为 $\sum f_{k,i}$ 代表能识出 $k$ 首歌的概率，而能识出 $k$ 首的概率已经在 $k-1$ 时统计过了，只需要统计增量就可以，实际上 $k-(k-1)=1$ ，所以增量为 $1$，对所有贡献求和即对所有 $f_{i,j}$ 求和。

综上，复杂度 $O(nT)$。

这题卡空间，开 `long double` 会 `MLE`。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=5e3+10;
#define ld double
int n,T,a[NR],p[NR];
ld f[NR][NR],ans,res,last;

int main(){
	cin>>n>>T;
	for(int i=1;i<=n;i++)scanf("%d%d",&p[i],&a[i]);
	f[0][0]=1.0;
	for(int i=1;i<=n;i++){
		ld now=0,lcy=pow(1-0.01*p[i],a[i]);
		for(int j=i;j<=T;j++){
			now+=f[i-1][j-1];
			if(j-a[i]>=1)now-=f[i-1][j-a[i]-1]*lcy;
			f[i][j]=now*0.01*p[i];
			if(j-a[i]>=0)f[i][j]+=f[i-1][j-a[i]]*lcy;
			now*=(1-0.01*p[i]);ans+=f[i][j];
		}
	}
		
	printf("%.6lf\n",ans);
	return 0;
}
```

---

## 作者：aaaaaaaawsl (赞：0)

看题解区的卡常写法都是一样？我换一种更好理解的写法。

设 $f_{i,j}$ 为第 $i$ 首歌在第 $j$ 秒**被识别**的**概率**，$f_{0, 0} = 1$。

一首歌有两种被识别的方式，第一种是规定时间内没识别出来（目前翻译有错）。第二种是在规定时间内被识别出来的。

因此状态转移为 

 $$f_{i,j} = f_{i - 1,j - t_{i}} \times (1 - p_i)^{t_i} + \sum_{k = 1}^{t_i}f_{i - 1, j - k} \times (1 - p_i)^{k - 1} \times p_i$$
 
因此可以写出一个 $O(n^3)$ 的 DP。

```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
 
using namespace std;
 
inline int read(){
	register int x = 0, f = 1; register char ch = getchar();
	for(; ch > '9' || ch < '0'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return x * f; 
}
 
const int N = 5e3 + 10;
double f[N][N], ans;
int t[N];
double p[N];
int sum[N];
int n, T; 
 
int main(){
	n = read(); T = read();
	for(register int i = 1; i <= n; ++ i){
		p[i] = 1.0 * read() / 100.0; t[i] = read();
	}
	f[0][0] = 1;
	for(register int i = 1; i <= n; ++ i){	
		for(register int j = 1; j <= T; ++ j){
			if(j >= t[i]) f[i][j] += f[i - 1][j - t[i]] * pow(1 - p[i], t[i] - 1);
			for(register int k = 1; k <= j && k < t[i]; ++ k) f[i][j] += f[i - 1][j - k] * pow(1 - p[i], k - 1) * p[i];
			ans += f[i][j];
		}
	}
	printf("%.9lf", ans);
}
```

考虑 $f_{i, j}$ 与 $f_{i, j + 1}$ 的相似部分：

对于一个一般的 $f_{i, j}$ 有：

```
f[i][j] += f[i - 1][j - t[i]] * pow(1 - p[i], t[i] - 1);
for(register int k = 1; k <= j && k < t[i]; ++ k) f[i][j] += f[i - 1][j - k] * pow(1 - p[i], k - 1) * p[i];
```

![](https://cdn.luogu.com.cn/upload/image_hosting/nhtmc473.png)

对于接下来的 $f_{i, j+1}$ 有：

![](https://cdn.luogu.com.cn/upload/image_hosting/rf26sgxm.png)

少了红色区域，多了黄色区域，少了绿色区域最左边一个，多了蓝色区域的最右边一个，同时蓝色和绿色相交部分每个都多乘了一个 $(1-p_i)$。在循环的时候加上多的，减去少的，即可，时间复杂度 $O(TN)$。

对于某个 $i$，循环 $j$ 时所乘幂的部分是一样的，要预处理，不然过不去。

对于答案，由于当前 $f_{i,j}$ 存的是第 $j$ 秒听完 $i$ 的概率，所以 $
\sum_{j}f_{i, j}$ 就是听完 $i$ 的概率，它对答案的贡献是 $\sum_{j}f_{i, j} \times 1$。所以最后答案就是 $\sum_{i}\sum_{j}f_{i,j}$

可能是我写法比较丑，加火车头能过，但是我觉得更好理解。

```
/*
这里省略了火车头
*/
#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;

inline short int read(){
	register short int x = 0, f = 1; register char ch = getchar();
	for(; ch > '9' || ch < '0'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return x * f;
}

const int N = 5e3 + 1;
double f[N][N], ans; // is jth
short int t[N];
double p[N], pw, pw1, pw2;
short int sum[N];
short int n, T; 

int main(){
	n = read(); T = read();
	for(register short int i = 1; i <= n; ++ i){ p[i] = 1.0 * read() / 100.0; t[i] = read();}
	f[0][0] = 1;
	for(register short int i = 1; i <= n; ++ i){
		pw = pow(1 - p[i], t[i] - 1);
		pw1 = pw * p[i];
		pw2 = pw * (1 - p[i]);
		for(register short int j = 1; j <= T; ++ j){
			f[i][j] += f[i][j - 1] * (1 - p[i]) + f[i - 1][j - 1] * p[i];
			if(j - 1 >= (t[i] - 1)) f[i][j] -= f[i - 1][(j - 1) - (t[i] - 1)] * pw1;
			if(j >= t[i]) f[i][j] += f[i - 1][j - t[i]] * pw;
			if(j - 1 >= t[i]) f[i][j] -= f[i - 1][j - 1 - t[i]] * pw2;
			ans += f[i][j];
		}
	}
	printf("%.9lf", ans);
}
```

C++17 不加火车头能过的优化版本（目前最优解 343 ms），但是不建议初见就照着写，因为不好理解。

```
#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;

inline short int read(){
	register short int x = 0, f = 1; register char ch = getchar();
	for(; ch > '9' || ch < '0'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return x * f;
}

const int N = 5e3 + 1;
double f[2][N], ans;
short int t[N], now = 1, lst;
double p[N], pw[N], pw1[N], pw2[N];
short int sum[N];
short int n, T; 

int main(){
	n = read(); T = read();
	for(register short int i = 1; i <= n; ++ i){
		p[i] = 1.0 * read() / 100.0; t[i] = read();
		pw[i] = pow(1.0 - p[i], t[i] - 1);
		pw1[i] = pw[i] * p[i];
		pw2[i] = pw[i] * (1.0 - p[i]);
	}
	f[0][0] = 1;
	for(register short int i = 1; i <= n; ++ i){
		for(register short int j = 1; j <= T; ++ j){
			f[now][j] = f[now][j - 1] * (1.0 - p[i]) + f[lst][j - 1] * p[i];
			if(j >= t[i] + 1) f[now][j] += f[lst][j - t[i]] * pw[i] - f[lst][(j - 1) - (t[i] - 1)] * pw1[i] - f[lst][j - 1 - t[i]] * pw2[i];
			else if(j == t[i]) f[now][j] += f[lst][j - t[i]] * pw[i] - f[lst][(j - 1) - (t[i] - 1)] * pw1[i];
			ans += f[now][j];
		}
		now ^= 1; lst ^= 1; f[now][0] = 0;
		
	}
	printf("%.9lf", ans);
	return 0; 
}
```

---

## 作者：liuyifan (赞：0)

## 无需优化的DP,卡常即可
设认出第i首歌的概率是p[i],合唱开始的时刻是t[i]

则F[i][j]=p[i]*F[i-1][j-1]+(1-p[i])*p[i]*F[i-1][j-2]+(1-p[i])*(1-p[i])*p[i]*F[i-1][j-3]…….

  F[i][j+1]=P[i]*F[i-1][j]+(1-p[i])*p[i]*F[i-1][j-1]+(1-p[i])*(1-p[i])*p[i]*F[i-1][j-2]…….

可见这个转移是很有规律的,我们可以从F[i][j]用O(1)的时间推出F[i][j+1],讨论j和t[i]的大小关系即可.时间复杂度O(n^2)，卡卡常就可以通过

code:(下面注释为一些常见卡常技巧)
```cpp
// luogu-judger-enable-o2//在luogu评测机中开启O2优化 ,Remotejudge中似乎无效 
#include<bits/stdc++.h>
#define reg register//register卡常 
#define ll long long//long long 
#define y1 liuifan_y1//防关键字 
#define inf 0x3f3f3f3f
#define iinf 0x3f3f3f3f3f3f3f3f//最大值 
#define data liuyifan_data//同上 
#define next liuyifan_next//同上 
#define ture true//防止打错词 
#define flase false//同上 
#define lowbit(x) x&(-x)//树状数组lowbit 
using namespace std;
double f[5005][5005],p,g,h,l,tmp,ans;//全局变量默认为0 
int n,m,x,y;
int main()
{
	f[0][0]=1; 
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i)//++i比i++快,i++会将自身复制一遍再++，++i不会 
	{
		f[i][0]=0;
		for(reg int j=1;j<=i-1;++j)f[i][j]=0;//同上 
		scanf("%d%d",&x,&y);//大数据一定不要用cin,尤其是没有优化的cin 
		p=x/100.0;//卡精度 
		g=1-p;
		h=pow(g,y-1);//pow默认为double 
		l=h*g;
		tmp=0;//初始化 
		for(reg int j=i;j<=m;++j)//DP
		{
			if(j<y)tmp=tmp*g+p*f[i-1][j-1];//这几个地方如果不用一个tmp中转会TLE 
			else if(j==y)tmp=tmp*g+p*f[i-1][j-1]+f[i-1][0]*l;//同上
			else tmp=tmp*g-l*f[i-1][j-y-1]+l*f[i-1][j-y]+p*f[i-1][j-1];//同上
			f[i][j]=tmp;//保存至f[i][j] 
			ans+=f[i][j];//求和 
		}
	}
	printf("%.7f\n",ans);//保留7位小数 
	return 0;
}
```

---

