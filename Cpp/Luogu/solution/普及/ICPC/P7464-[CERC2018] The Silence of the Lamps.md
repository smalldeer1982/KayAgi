# [CERC2018] The Silence of the Lamps

## 题目描述

**译自[ [CERC2018]](https://contest.felk.cvut.cz/18cerc/) [The Silence of the Lamps](https://contest.felk.cvut.cz/18cerc/solved/lamps.pdf)**

在开始之前，如果之前没有见过台灯，那么现在我们把它看做一个用玻璃做的长方体（一个矩形表面的箱子），里面都是煤气。灯的所有边长度都是整数。

曾经，我们的一位讲师曾因破坏路灯而被判刑。他肯定疯了，因为他认为一些路灯向他高声尖叫。

在他的想法里，他遵从一个奇怪的行为模式。他只会认出并且破坏表面不是正方形，并且体积不超过一个给定数值的路灯。后来，在与医生 Clarice 的一次会谈中，他说他非常害怕大型物体和形状过于规则的物体。

你的任务是数出所有满足讲师条件的可能长方体。

## 说明/提示

$1≤T≤10^5$，$1≤N≤10^6$。

## 样例 #1

### 输入

```
5
5
6
10
30
666```

### 输出

```
0
1
3
26
2406```

# 题解

## 作者：阿丑 (赞：3)

[传送门](https://www.luogu.com.cn/problem/P7464)

#### 前置知识：

前缀和，dfs。

#### 题意：

+ $T$ 组数据，每组数据给出一个正整数 $n$，求所有满足 $i<j<k$ 且 $i\times j\times k\le n$ 的正整数三元组 $(i,j,k)$ 的个数。

+ $T\le 10^5$，$n\le 10^6$。

下文中，若未做特殊说明，则默认 $i<j<k$。

#### 分析：

考虑只有单个询问的情况。注意到 $i$ 是 $\sqrt[3]n$ 级别的，可以尝试暴力枚举。

注意到在枚举的过程中，我们可以把求 $i\times j\times k\le n$ 的三元组个数，看做求所有 $i\times j\times k=m,m\le n$ 的三元组个数。因此当 $n$ 取 $10^6$ 时，对于所有 $m\le 10^6$，我们在 dfs 时就已经求出了 $i\times j\times k=m$ 的三元组 $(i,j,k)$ 的个数。

考虑多个询问的情况。对于询问 $n'$，由于 $n'\le 10^6$，所以我们已经求出了对于所有 $m\le n'$ 的 $i\times j\times k=m$ 的三元组个数。可以使用前缀和将其相加，从而 $O(1)$ 求出答案。

#### 思路：

1. 对于所有 $m\le 10^6$，通过 dfs 求出 $i\times j\times k=m$ 的三元组个数。dfs 只需要一次。

2. 将求出的答案前缀和处理，对于每一个询问 $O(1)$ 解决。

---

#### dfs 部分

下面分析 dfs 的复杂度。~~因为太水了只好开始瞎扯~~

令 $i$ 从 $1$ 枚举到 $n$，考虑 $i=i_0$ 时需要枚举多少 $j$ 和 $k$。

$j$ 从 $1$ 枚举到 $\dfrac n {i_0}$，而对于 $j=j_0$ 的情况，$k$ 从 $1$ 枚举到 $\dfrac n {i_0\times j_0}$。因此，枚举的时间复杂度是 $\sum\limits_{j_0=1}^{\frac n{i_0}}\dfrac n{i_0\times j_0}=\dfrac n{i_0}\sum\limits_{j_0=1}^{\frac n{i_0}}\dfrac 1{j_0}$，是 $\dfrac n{i_0}\log\dfrac n{i_0}$ 级别的。

所以总时间复杂度为 $O(\sum\limits_{i=1}^n\dfrac ni\log\dfrac ni)$。

可以写一个程序计算这个时间复杂度。我算出来的结果是 $1.5\times 10^8$，可以接受。

当然，实际上枚举的时候可以不从 $1$ 开始，也不必枚举到 $n$ 等上界，因此复杂度会更小。

代码实现应该不用多说吧（

---

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mN=1e6+100;
int mp[mN];

void dfs(int st, int v, long long now) {	//now 存的是目前所有数的乘积 
	if(st==3) ++mp[now];
	else for(int i=v+1; now*i<mN; ++i) dfs(st+1, i, now*i);	//从 v+1 枚举到 1e6/now
}
int main() {
	dfs(0, 0, 1);
	for(int i=1; i<mN; ++i) mp[i]+=mp[i-1];	//前缀和处理 
	int T, n;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		printf("%d\n", mp[n]);
	}	
	return 0;
}
```

---

## 作者：A_grasser (赞：3)

## 题意简化

求体积小于等于特定值的长方体方案数。

## 需要注意的地方

1. 多测，注意考虑更优算法。

## 解法分析

如何求长方体的种数呢？

可以申请一个 `ans` 数组，其中 $ans_i$ 表示体积为 $i$ 时的长方体数量。

于是我们就可以得到两种预处理写法：一种是 dfs 的写法，一种是枚举的算法。废话不说了，上代码！

dfs 的写法：一条边一条边枚举，剪枝就是每一条边都比上一条边大就可以。时间复杂度能过此题。代码：

```cpp
//num:第几条边 last:上一条边 sum:总体积 
void dfs(int num,int last,long long sum){
	if(num==3) ans[sum]++;//构成了长方形 
	else {
		for(int i=last+1;sum*i<1000005;i++){//枚举可能的边 
			dfs(num+1,i,sum*i);//搜索下一条边 
		}
	}
}
```
枚举的写法：枚举长宽高，三层循环，暴力美学。时间复杂度为 $O(\sqrt[3]{n})$。代码：

```cpp
for(int i=1;i<1000005;i++){//长 
	for(int j=i+1;i*j<1000005;j++){//宽 
		for(int k=j+1;i*j*k<1000005;k++){//高 
			ans[i*j*k]++;//符合一个长方形 
		}
	}
}
```

统计部分就写完了。

接下来的多测很烦，每问一次就要从前往后统计一遍，时间复杂度爆表，那就前缀和！

```cpp
for(int i=1;i<1000100;i++) ans[i]+=ans[i-1];//前缀和 
```

剩下的就简单多了，输入输出即可。

```cpp
cin>>t;
while(t--){//多测 
	scanf("%d",&n);
	printf("%d\n",ans[n]);
}
```


最后说一句，我比较推荐万能头文件，这样可以省去很多不必要的麻烦。

## 完整代码

dfs 版本：

```cpp
//已通过
#include<bits/stdc++.h>
//万能头文件
using namespace std;
int t,n;
int ans[1000005];
//num:第几条边 last:上一条边 sum:总体积 
void dfs(int num,int last,long long sum){
	if(num==3) ans[sum]++;//构成了长方形 
	else {
		for(int i=last+1;sum*i<1000005;i++){//枚举可能的边 
			dfs(num+1,i,sum*i);//搜索下一条边 
		}
	}
}
int main(){
	dfs(0,0,1);//预处理 
	for(int i=1;i<1000100;i++) ans[i]+=ans[i-1];//前缀和 
	cin>>t;
	while(t--){//多测 
		scanf("%d",&n);
		printf("%d\n",ans[n]);
	}	
	return 0;
}
```

枚举版本：

```cpp
//已通过
#include<bits/stdc++.h>
//万能头文件
using namespace std;
int t,n;
int ans[1000005];
int main(){
	for(int i=1;i<1000005;i++){//长 
		for(int j=i+1;i*j<1000005;j++){//宽 
			for(int k=j+1;i*j*k<1000005;k++){//高 
				ans[i*j*k]++;//符合一个长方形 
			}
		}
	}
	for(int i=1;i<1000100;i++) ans[i]+=ans[i-1];//前缀和 
	cin>>t;
	while(t--){//多测 
		scanf("%d",&n);
		printf("%d\n",ans[n]);
	}	
	return 0;
}
```

---

## 作者：Tjaweiof (赞：2)

# P7464 题解
[题目传送门](https://www.luogu.com.cn/problem/P7464)

这题实际上非常的简单，只需要预处理，用一个三层循环，求出每一个 $n$ 的答案，然后算一遍前缀和，存在一个答案数组里。最后每次询问只需要输出 $ans[n]$ 即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1000000;
long long t, n, ans[N + 1];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	for (long long i = 1; i <= N; i++){
		for (long long j = i + 1; i * j <= N; j++){
			for (long long k = j + 1; i * j * k <= N; k++){
				ans[i * j * k]++;
			}
		}
	}
	for (long long i = 1; i <= 1000000; i++){
	    ans[i] += ans[i - 1];
	}
	while (t--){
		cin >> n;
		cout << ans[n] << endl;
	}
	return 0;
}
```
#### 此代码时间复杂度 $O(n\log^2 n)$，空间复杂度 $O(n)$，完美过关！

---

## 作者：IAWNA (赞：1)

~~先说两句有的没的，真有路灯体积是 $10^6$ 吗……~~

搜索大法好啊！

显然这题直接搜长方体三条边 $i,j,k$，它的体积是 $i \times j \times k$。

```dfs(gs,lt,nw)``` 表示当前搜了 $gs$ 条边，上一条边长 $lt$，搜过的边乘积是 $nw$。

然后我们可以写出：

```cpp
inline void dfs(int gs,int lt,long long nw)
{
	if(gs==3)
	{
		++ans;
		return ;
	}
	for(int i=lt;nw*i<=n;++i)//n是路灯最大体积 
	dfs(gs+1,i+1,nw*i);
	return ;
}
```

每组询问做一下就行了。

~~骗你的，不行。~~

因为 $t \leq 10^5$，所以我们需要一种 $O(1)$ 输出答案的方法，而不是每输入一个做一次 （TLE on #test 15）。

我们可以预处理出每个体积的满足条件长方体的个数，然后做前缀和。

然后对于每组询问直接输出 $ans$ 就行了。

# 代码

```cpp
#include<cstdio>
int ans[1000005];
inline void dfs(int gs,int lt,long long nw)
{
	if(gs==3)
	{
		++ans[nw];
		return ;
	}
	for(int i=lt;nw*i<1000005;++i)
	dfs(gs+1,i+1,nw*i);
	return ;
}
int main()
{
	dfs(0,1,1);
	int t;
	scanf("%d",&t);
	for(int i=1;i<1000005;++i)
	ans[i]+=ans[i-1];
	while(t--)
	{
		int n;
		scanf("%d",&n);
		printf("%d\n",ans[n]);
	}
	return 0;
}
```


---

## 作者：ztntonny (赞：1)

## 题意

本题重在理解题意。

$\mathcal{Part1}$：一个没有面是正方形的长方体意味着什么？每一个长方体都有 $12$ 条棱，而其中分成 $3$ 组每组 $4$ 条分别相等，也就是说总共有 $3$ 种棱长，而其中 $6$ 个面两两相等，有 $3$ 种不同形状，也就是说 $3$ 种形状是由 $3$ 种棱长排列组合而成，又正方形是邻边相等的长方形，所以 **$3$ 种棱长两两不等**。

$\mathcal{Part2}$：长方体体积小于一个定值意味着什么？长方体的体积等于 $3$ 种棱长的乘积，也就是说**要保证 $3$ 种棱长乘积 $\leq N$**。

#### 于是总结得到，我们要做的实际上就是枚举 $3$ 个不同的数，保证它们乘积 $\leq N$。

## 思路

楼上大佬用的 dfs，我本来用的也是，但是介绍一下~~对萌新更友好的~~纯暴力方法。其实就是 dfs 的摊开，因为选数数量确定，考虑**三重循环预处理**：

```cpp
for ( ll i = 1; i < 1000005; i++ )
	for ( ll j = i + 1; i * j < 1000005; j++ )
		for ( ll k = j + 1; i * j * k < 1000005; k++ )
			p[i * j * k]++;
```

枚举每一组边长，注意每一次从上一条边**加一**开始枚举可以保证**不重不漏**。当枚举完 $3$ 个数时放进**桶数组中计数**。

然后进行[前缀和](https://www.luogu.com.cn/blog/ztntonny/qian-zhui-hu-jian-shu)，计算小于等于下标的符合数对数量：

```cpp
for ( int i = 0; i < 1000005; i++ )	p[i] += p[i - 1];
```

然后就可以简单的输入，输出对应前缀和，代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n , p[1000005] , ans , cmp , m , jug , k , num[1000005];
int main()
{
	cin >> n;
	for ( ll i = 1; i < 1000005; i++ )
		for ( ll j = i + 1; i * j < 1000005; j++ )
			for ( ll k = j + 1; i * j * k < 1000005; k++ )
				p[i * j * k]++;
	for ( int i = 0; i < 1000005; i++ )	p[i] += p[i - 1];
	for ( int i = 1; i <= n; i++ )
	{
		cin >> k;
		cout << p[k] << endl;
	}
	return 0;
}
```

---

## 作者：August44 (赞：0)

## 题意
求边长为整数且体积不大于 $N$ 的**长方体**的数量。

## 分析
因为是多测，所以需要进行预处理。用 $a_i$ 表示体积为 $i$ 的**长方体**数量，对于 $a_i$ 可以依次枚举长，宽，高进行计数。

题目要求不大于 $N$ 的长方体个数，所以要求出 $a_i$ 的前缀和进行优化。

预处理时间复杂度为 $O(\sqrt[3]{n})$，前缀和时间复杂度为 $O(n)$，查询时间复杂度为 $O(1)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000005
using namespace std;
int a[N],sum[N],T;
signed main()
{
	for(int i=1;i<=N;i++)
	  for(int j=i+1;i*j<=N;j++)
	    for(int k=j+1;i*j*k<=N;k++)
	      a[i*j*k]++;
	for(int i=1;i<=N;i++)
	  sum[i]=sum[i-1]+a[i];
	cin>>T;
	while(T--)
	{
		int x;
		cin>>x;
		cout<<sum[x]<<endl;
	}
	return 0;
}
```

---

## 作者：Flaw_Owl (赞：0)

# P7464 [CERC2018] The Silence of the Lamps 题解

原题链接：[P7464 [CERC2018] The Silence of the Lamps 题解](https://www.luogu.com.cn/problem/solution/P7464)

## 题目分析

抽象题意，实际上就是求满足 $i < j < k$ 且 $ijk \leq N$ 的三元组 $(i,j,k)$ 的数量。用朴素的暴力思想，这实际上可以用一个简单的三重循环来解决。但是由于这道题有多测，每次都暴力显然不现实，那么我们预先处理好每一个满足 $ijk = N$ 的三元组的数量，再用前缀和存储，就可以找到所有满足 $ijk \leq N$ 的三元组的数量了。

## 注意事项

值得注意的是，在我们的三重循环中，第一层的结束条件应该是 `i <= N`，第二层的条件应该是 `i * j <= N`，第三层的条件应该是 `i * j * k <= N`。又因为 $1 \leq N \leq 10^6$，在处理 `i * j` 和 `i * j * k` 的时候可能会有爆 `int` 的情况，因此要将这三个变量都设置为 `long long` 类型。

## 复杂度分析

下面尝试对该解法进行（可能较为严谨的）复杂度分析。

在三层循环中，第一层循环共执行 $N$ 次，第二层循环共执行 $\dfrac{N}{i} - i$ 次，第三层循环共执行 $\dfrac{N}{ij} - j$ 次。我们对其进行求和，即：

$$ \sum_{i=1}^n \sum_{j = i+1}^{\lfloor \frac{n}{i} \rfloor} \sum_{k = j+1}^{\lfloor \frac{n}{ij} \rfloor} $$

对内层循环，

$$ \sum_{k = j+1}^{\lfloor \frac{n}{ij} \rfloor} \approx \dfrac{N}{ij} - j $$

计算复杂度的时候省略常数。

对中层循环,利用调和级数进行计算：

$$ \sum_{j = i+1}^{\lfloor \frac{n}{i} \rfloor} \dfrac{N}{ij} = \dfrac{N}{i} \sum_{j = i+1}^{\lfloor \frac{n}{i} \rfloor} \dfrac{1}{j} \approx \dfrac{N}{i} \cdot \left[ \ln \left( \dfrac{N}{i} \right) - \ln (i) \right] = \dfrac{N}{i} \ln \left( \dfrac{N}{i^2} \right) $$

对外层循环，

$$ \sum_{i=1}^N \dfrac{N}{i} \ln \left( \dfrac{N}{i^2} \right) = N \sum_{i=1}^N \dfrac{\ln \left( \frac{N}{i^2} \right)}{i} = N \sum_{i=1}^N \dfrac{\ln N - 2 \ln i}{i} = N \ln N \sum_{i=1}^N \dfrac{1}{i} - 2N \sum_{i=1}^N \dfrac{\ln i}{i}$$

利用调和级数，可以得到：

$$ \sum_{i=1}^N \dfrac{1}{i} = \ln N $$

利用积分近似

$$ \sum_{i=1}^n f(i) = \int_1^n f(x) \, dx $$

可以得到：

$$ \sum_{i=1}^N \dfrac{\ln i}{i} = \int_1^N \dfrac{\ln x}{x} \,dx = \dfrac{(\ln N)^2}{2} $$

也就是说，原式变为：

$$ N (\ln N)^2 - N (\ln N)^2$$

也就是得到了最终的时间复杂度为：

$$ O(N \log^2 N) $$

题目中 $1 \leq N \leq 10^6$ 且时间限制为 1 秒，可以通过。

## 参考代码

```cpp
#include <iostream>
#include <cctype>
#define ll long long

using namespace std;

int read()
{
    int x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int maxN = 1e6 + 5;

int T;
int n;

ll a[maxN];
ll s[maxN];

int main()
{
    T = read();
    for (ll i = 1; i <= maxN; i++)
        for (ll j = i + 1; i * j <= maxN; j++)
            for (ll k = j + 1; i * j * k <= maxN; k++)
                a[i * j * k]++;
    for (int i = 1; i <= maxN; i++)
        s[i] = s[i - 1] + a[i];
    while (T--)
    {
        n = read();
        printf("%lld\n", s[n]);
    }
    return 0;
}
```

---

## 作者：keepwatcher_kensap (赞：0)

## Part 1 题意

有一个讲师会破坏形状为长方体，体积不超过 $n$ 的路灯。即假设路灯的长宽高为 $x,y,z$，则若 $x \times y \times z \leq n$，该路灯就会被破坏。给定 $n$，求出可能被破坏的路灯有多少种不同的形状。

## Part 2 思路

当你看到 $1 \leq n \leq 10^6$ 时就认为不能枚举 $x,y,z$ 了，实则不然。

首先，我们先确保 $x < y < z$，此时就不是确保 $x,y,z$ 是路灯的长宽高了，而是确保 $x,y,z$ 为路灯最短，次长，最长的边。同时要注意令 $x \neq y \neq z$，因为题目遵循破坏表面不为正方形。

由于路灯的总体积是 $x \times y \times z$，因此我们在枚举的时候要注意令 $x \times y \times z \leq n$。如下进行枚举：

```
for (long long i=1;i<=maxn;i++)
{
	for (long long j=i+1;i*j<=maxn;j++)
	{
		for (long long k=j+1;i*j*k<=maxn;k++) f[i*j*k]++;
	}
}
```

代码中 $f_i$ 表示路灯总体积恰好是 $i$ 的情况下符合要求的路灯数量。而路灯被破坏只要满足体积小于等于 $n$ 即可，因此我们还要进行一次前缀和处理：

```
for (long long i=1;i<=maxn;i++) f[i]+=f[i-1];
```

## Part 3 优化

虽然正常的输入输出可以，但是使用快读和快写会更加迅速。

```
inline long long read() // 快读
{
	long long x=0,y=1;
	char ch=getchar();
	while (ch<'0' || ch>'9')
	{
		if (ch=='-') y=-1;ch=getchar();
	}
	while (ch>='0' && ch<='9')
	{
		x=x*10+(long long)(ch-'0');ch=getchar();
	}
	return x*y;
}
inline void write(long long x) // 快写
{
	if (x<0) putchar('-'),x=-x;
	if (x>9) write(x/10);
	putchar(x%10+'0');
	return ;
}
```

## Part 4 代码

```
#include <bits/stdc++.h>
using namespace std;
const long long maxn=1e6;
long long f[maxn+5];
inline long long read()
{
	long long x=0,y=1;
	char ch=getchar();
	while (ch<'0' || ch>'9')
	{
		if (ch=='-') y=-1;ch=getchar();
	}
	while (ch>='0' && ch<='9')
	{
		x=x*10+(long long)(ch-'0');ch=getchar();
	}
	return x*y;
}
inline void write(long long x)
{
	if (x<0) putchar('-'),x=-x;
	if (x>9) write(x/10);
	putchar(x%10+'0');
	return ;
}
inline void found()
{
	for (long long i=1;i<=maxn;i++)
	{
		for (long long j=i+1;i*j<=maxn;j++)
		{
			for (long long k=j+1;i*j*k<=maxn;k++) f[i*j*k]++;
		}
	}
	for (long long i=1;i<=maxn;i++) f[i]+=f[i-1];
	return ;
}
int main()
{
	found();
	long long t=read();while(t--)
	{
		long long n=read();write(f[n]);putchar('\n');
	}
	return 0;
}
```

---

## 作者：niuzh (赞：0)

### 思路

由于这题 $T \le 10^5$，所以在每个小点之内枚举肯定会超时，所以我们可以考虑在开始预处理出 $a_i$ 等于面积为 $i$ 的长方体总数，再进行前缀和并存在 $ans$ 里，输入为 $n$ 的答案即为 $ans_n$。

### 代码

![](https://cdn.luogu.com.cn/upload/image_hosting/z9mk8wo4.png)

---

## 作者：WaterSky (赞：0)

# [P7464 [CERC2018] The Silence of the Lamps](https://www.luogu.com.cn/problem/P7464)

## 题意：
有 $T$ 组数据，每组数据有一个 $N$，求不同的三元组 $(i,j,k)$ 的个数，满足以下条件：
- $i < j < k$。
- $i \times j \times k \le N$。

## 数据范围：
$1 \le T\le 10^5$，$1 \le N\le 10^6$。

## 思路：
由于有多组数据，而且组数多。所以可以先不考虑组数的问题，先考虑只有一组的情况。 

只有一组，那就好想多了。

可以三重暴力枚举，先枚举 $i$，然后枚举 $j$，最后枚举 $k$。

从 $1$ 开始枚举 $i$，循环的结束条件是当 $i \times j$ 不再小于 $n$ 时就结束，因为如果已经超过了，那么 $j$ 怎么增加都是超过 $n$ 的。

枚举 $k$ 时同理，直到 $i \times j \times k$ 不再小于 $N$ 时就结束。

那多组数据又要怎么解决呢？

将小于 $N$ 的数表示为 $M$。

我们在上面枚举小于等于 $N$ 的数时，就已经把 $i \times j \times k = M$ 的三元组的个数算了出来。

我们就可以在开始时就把小于 $10^6$ 的情况枚举，然后再用前缀和数组来记录小于等于 $M$ 的数量，就可以做到每一组数据 $O(1)$，也就可以正确了。

## 代码：
```
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[1000005];
int main(){
	cin>>t;
	for(long long i=1;i<=1000000;i++) //一定要开 long long。
		for(long long j=i+1;j*i<=1000000;j++)
			for(long long k=j+1;i*j*k<=1000000;k++)
				a[i*j*k]++;//记录。
	for(int i=1;i<=1000000;i++) a[i]+=a[i-1];/前缀和。
	while(t--)
		cin>>n,cout<<a[n]<<endl;
	return 0;
}
```

感谢管理员审核!

---

## 作者：Erica_N_Contina (赞：0)

# [CERC2018] The Silence of the Lamps


## 简明

$T$ 组数据。每组数据中给定体积 $V$，求体积 $≤V$ 的不同的长方体的个数，且要求长 $≠$ 宽 $≠$ 高。

## 思路

我们考虑到，对于一个体积 $V$ 的长方体，其最长的边一定 $≥\sqrt[3]{V}$，并且不可能有多于 $2$ 条边 $>\sqrt{n}$。我们求出 $\sqrt[3]{n}=100,\sqrt{n}=1000$，所以我们可以枚举其中两条边。但这样的时间复杂度为 $O(NT)$，过不去。

所以我们换一个方向思考：既然我们不能对于每个询问独立求出答案，那么既然询问的值域较小（$1≤N≤10^6$），我们是不是可以用一个桶来计数，一次性求出对于 $1\sim 10^6$ 中的每一个 $V$ 的答案。

我们只需要枚举长方体的三条边 $i,j,k$，枚举时保证 $i,j,k$ 有序（比如 $i>j>k$），复杂度较小。

## 优化&剪枝

事实上，最大的那条边（即 $i$）我们只需要枚举到 $N\div 2$ 即可，因为 $j,k$ 不能相等，那么 $j\times k$ 必定 $≥2$。

我们在三层循环时注意剪枝，即当 $i\times j\times k>N$ 时我们要及时 `break`（break 掉 $k$ 循环），还有当 $i\times j(\times 1)>N$ 时我们也要 `break`（break 掉 $j$ 循环）。

对于 $i,j,k$ 的开始枚举的初始值，我们设定为 $i=3,j=2,k=1$，很容易知道这样最好，因为要求 $i≠j≠k$。



## 代码

因为要求输出答案为 $≤V$ 的情况，所以求出桶后要前缀和一遍。

```C++
/*////////ACACACACACACAC///////////
       . Code by Ntsc .
       . Fancy Chargcy .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define ll int
#define db double
#define rtn return
using namespace std;

const int N=1e6;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

ll n,m,ans;
ll qzh[N],ton[N];

void init(){
	for(int i=3;i<=N/2;i++){
		for(int j=2;j<i;j++){
			if(i*j>N)break;
			for(int k=1;k<j;k++){
//				if(i==j||j==k||k==i)continue;
				if(i*j*k>N)break;
				ton[i*j*k]++;
			}
		}
	}
	
	for(int i=1;i<=N;i++){
		qzh[i]=ton[i]+qzh[i-1];
	}
	
//	for(int i=1;i<=20;i++){
//		cout<<ton[i]<<' ';
//	}
}

signed main(){
	cin>>n;
	init();
	while(n--){
		int v;
		cin>>v;
		cout<<qzh[v]<<endl;
	}
	return 0;
}

```








---

## 作者：封禁用户 (赞：0)

## 题意描述

共 $T$  组询问，每次给定一个整数 $n$，求有多少个 $i,j,k$，满足 $i < j <k$ 且 $i × j × k \le n$。

## 做法分析

类似于调和级数。我们枚举 $i,j,k$，在保证 $i × j × k \le 10^6$ 的情况下，这个积一定是一个满足条件的体积的值。我们可以将这个操作看成：求 $1$ 到 $10^6$ 之间，每个数能够分解成 $n=i×j×k$ 的方案数。

在求出来之后，这只是等于 $n$ 的方案数，而题目是求小于等于 $n$ 的方案数。所以我们还需要跑一边前缀和来求体积从 $1$ 到 $n$ 的方案数之和。

注意，在存方案数的时候，不能用 `map<int,int>`，这样会超时。

## 正解代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
vector<int> V(N);
int q,n;
int check(int a,int b,int c){return a*b*c;}//求i*j*k 
signed main()
{
	for(int i=1;;i++)
	{
		if(check(i,i,i)>N) break;//越界判断 
		for(int j=i+1;;j++)
		{
			if(check(i,j,j)>N) break;
			for(int k=j+1;;k++)
			{
				if(check(i,j,k)>N) break;
				V[check(i,j,k)]++;
			}
		}
	}
	for(int i=1;i<=N;i++) V[i]=V[i-1]+V[i];//前缀和
	cin>>q;
	while(q--)
	{
		cin>>n;
		cout<<V[n]<<endl;
	}
	return 0;
}
```


---

