# Young Explorers

## 题目描述

Young wilderness explorers set off to their first expedition led by senior explorer Russell. Explorers went into a forest, set up a camp and decided to split into groups to explore as much interesting locations as possible. Russell was trying to form groups, but ran into some difficulties...

Most of the young explorers are inexperienced, and sending them alone would be a mistake. Even Russell himself became senior explorer not long ago. Each of young explorers has a positive integer parameter $ e_i $ — his inexperience. Russell decided that an explorer with inexperience $ e $ can only join the group of $ e $ or more people.

Now Russell needs to figure out how many groups he can organize. It's not necessary to include every explorer in one of the groups: some can stay in the camp. Russell is worried about this expedition, so he asked you to help him.

## 说明/提示

In the first example we can organize three groups. There will be only one explorer in each group. It's correct because inexperience of each explorer equals to $ 1 $ , so it's not less than the size of his group.

In the second example we can organize two groups. Explorers with inexperience $ 1 $ , $ 2 $ and $ 3 $ will form the first group, and the other two explorers with inexperience equal to $ 2 $ will form the second group.

This solution is not unique. For example, we can form the first group using the three explorers with inexperience equal to $ 2 $ , and the second group using only one explorer with inexperience equal to $ 1 $ . In this case the young explorer with inexperience equal to $ 3 $ will not be included in any group.

## 样例 #1

### 输入

```
2
3
1 1 1
5
2 3 1 2 2```

### 输出

```
3
2```

# 题解

## 作者：b6e0_ (赞：8)

打完CF又来写题解啦~求兹磁qwq（第一次AC div2的D题）

[CF题面传送门](https://codeforces.com/contest/1355/problem/B) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1355B) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1355B)

这题是个贪心？为什么有人dp？

对于$1$，他自成一组肯定是最优的。即使他要和$2$或者更大的数字组成一组，那么构成的还是一组，并且浪费了几个更大的数字。

对于$2$，肯定是两两一组。证明方法类似。但是，有可能会剩下来一个$2$。这时剩下来的和其他$2$自己组成一个$3$个人的组肯定不值，所以它应该与$3$组，满足更多的$3$。

对于$3$，它们带上上一组剩下来的$2$（如果有），每$3$个一组。如果有剩余，与$4$一起组。

按照这个思路，我们就可以写出如下的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010],tot[200010];//tot是桶
int main()
{
	int t,n,i,le,ans;
	cin>>t;
	while(t--)
	{
		memset(tot,0,sizeof tot);//清零不能忘
		ans=le=0;//ans为答案，le为上一轮剩下来的
		cin>>n;
		for(i=0;i<n;i++)
		{
			cin>>a[i];//a[i]其实没用
			tot[a[i]]++;
		}
		for(i=1;i<=n;i++)
		{
			ans+=(tot[i]+le)/i;//组队
			le=(tot[i]+le)%i;//计算剩余
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
这份代码赛时是pretest passed的。但是赛后测完，这个代码是TLE的！（~~没人抄吧~~）原因就在memset。
## memset的复杂度其实是$O(n)$，只是常数小一点！
以前一直把他当$O(1)$看的qwq

这里$t$最大可到$2\times10^5$，加上这里每组数据$2\times10^5$的清零，肯定炸。

所以，我们必须把数组开在循环内。其他部分与上面代码基本相同。

AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010];
int main()
{
	int t,n,i,le,ans;
	cin>>t;
	while(t--)
	{
		ans=le=0;
		cin>>n;
		int tot[n+10]={};//要按照n的大小开，并清零！
		for(i=0;i<n;i++)
		{
			cin>>a[i];
			tot[a[i]]++;
		}
		for(i=1;i<=n;i++)
		{
			ans+=(tot[i]+le)/i;
			le=(tot[i]+le)%i;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
时间复杂度为$O(n)$。

---

## 作者：zhangzirui66 (赞：2)

# 题解：CF1355B Young Explorers
## 1.思路
最优化问题，考虑 dp。
## 2.状态转移
设 $f_i$ 为序列前 i 项能分多少组。
如果不单独为一组，那么 $f_i=f_{i-1}$。

- 如果不单独一组，那么 $a_i$ 就成了该子序列的最大值，为了保证能更多地分，那么该子序列长度至少为 $a_i$。

- 如果要分，分完以后，剩下 $i-a_i$ 个数，组数加 1。

当 $i<a_i$ 时也就是不够分时，考虑第一种情况，直接不管。

当 $i \ge a_i$ 时，可以单独分一组，那么考虑第二种情况，能多分就多分。

得到状态转移方程：

$f_i = \begin{cases}
  f_{i-1} \hspace{3cm}\ i<a_i\\
  \max(f_{i-1}, f_{i-a_i}+1) \hspace{0.6cm}\ i\ge a_i \\
\end{cases}$

**code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a[200005], f[200005];
int main(){
    scanf("%d", &t);
    while(t --){
        scanf("%d", &n);
        for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
        sort(a + 1, a + n + 1);//排序使得a[i]为子序列最大值
        for(int i = 1; i <= n; i ++){
            f[i] = f[i - 1];//先赋为上一个值
            if(i >= a[i]) f[i] = max(f[i - 1], f[i - a[i]] + 1);//如果可以添加进子序列，取最大值
        }
        printf("%d\n", f[n]);
        for(int i = 1; i <= n; i ++) f[i] = 0;//手动清空用memset会超时
    }
}
```

---

## 作者：钓鱼王子 (赞：2)

这里用的是 DP。

先将所有人排序，然后设 $dp_i$ 表示前 $i$ 个人最多能分几组，转移也很简单，$dp_i=\max(dp_{i-1},dp_{i-a_i}+1)$，分别表示不选和选这个人，取 $\max$ 即可。

数组清空不能 memset，有 $2\times 10^5$ 组数据。会 T。可以用 fill 或手动清空。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,t,ans,a[1000002],dp[1000002];
int main(){
	t=read();
	while(t--){
		n=read();
		for(re int i=1;i<=n;++i)a[i]=read();
		sort(a+1,a+n+1);ans=0;
		for(re int i=1;i<=n;++i){
		dp[i]=dp[i-1];		if(i>=a[i])dp[i]=max(dp[i],dp[i-a[i]]+1);ans=max(ans,dp[i]);}
		printf("%d\n",ans);
		for(re int i=1;i<=n;++i)dp[i]=0;
	}
}
```


---

## 作者：hhztl (赞：1)

## 题意简述
给定一个长为 $n$ 的序列，求在保证每个子序列里的最大值不超过子序列长度的条件下最多能划分出几个子序列。
## 算法分析
考虑使用动态规划。首先，题目其实只要求**每个子序列里的最大值不超过子序列长度**，没有重复元素是一个误导~~有被坑到~~。所以，选到第 $i$ 个数时的状态可以由之前的状态推导得到。设选到第 $i$ 个数时的最多划分数为 $dp_i$，容易得出，在 $i \ge a_i$ 的情况下，$dp_i$ 可以由 $dp_{i-a_i}+1$ 得到。

那具体该怎么实现呢？

为保证最优解，我们需要先将数组排序。接着从 $1$ 到 $n$ 循环，将 $dp_i$ 赋值为 $dp_{i-1}$（去掉第 $i$ 个数的情况），如果 $i \ge a_i$，将 $dp_i$ 与 $dp_{i-a_i}$ 取 max。看到其他 dalao 大多是取 $dp_i$ 的最大值，但其实可以直接输出 $dp_n$ ，因为 $dp_n$ 的情况**一定是之前的最大值**。  
还有最后的最后，本题的**最大**坑点：$dp$ 数组需要清零，**但是用 memset 时间会炸掉**。这点其他 dalao 也讲过了，本蒟蒻也不过多赘述，直接手动清零即可。
## 上代码！~~我知道你们只看这个~~
```
#include<bits/stdc++.h>//万能头
#define ma(x,y) ((x>y)?x:y)//手打max，时间更优
using namespace std;
long long t,n,a[200010],dp[200010];
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>n;
        for(int j=1;j<=n;j++)cin>>a[j];
        sort(a+1,a+n+1);//快排
        for(int j=1;j<=n;j++){
            dp[j]=dp[j-1];
            if(j>=a[j])dp[j]=ma(dp[j],dp[j-a[j]]+1);
        }cout<<dp[n]<<'\n';//直接输出dp[n]
        for(int j=1;j<=n;j++)dp[j]=0;//清零，千万不要用memset!
    }return 0;//完结撒花!!!
}
```

---

## 作者：oimaster (赞：1)

# Codeforces 1355 B 题解

## Part1 前言

这一道题我觉得第一眼看上去时比 A 题简单一些，所以在比赛的时候我就先做了这道题。印象还是不错的。

## Part2 题面

有 $N\left(1 \leq N \leq 2 \cdot 10^{5}\right)$ 个小探险家，第 $i$ 个小探险家的经验值为 $e_i$，满足 $1 \leq e_{i} \leq N$ 。

然后老师们规定，如果一个小探险家的值为 $e$，那么他的队伍人数必须大于或等于 $e$。

求最多这些小探险家能组成多少队伍。

你需要回答 $T\left(1 \leq T \leq 2 \cdot 10^{5}\right)$ 组数据，所有的 $N$ 不会超过 $3 \cdot 10^{5}$。

## Part3 思路

这一道题其实是一道贪心题。我们可以分析一下 Codeforces 这道题给的样例。

```
2
3
1 1 1
5
2 3 1 2 2
```

看第二组数据。我们可以想到解法：

1. 首先将 $1$ 分成单独的一组；
2. 然后看 $2$，发现有 $3$ 个 $2$。那么我们就把其中 $2$ 个 $2$ 结成一组，另一个 $2$ 跟 $3$ 来配对。
3. 接下来看见有 $3$ 来了。我们用 $3$ 和上一轮剩下来的 $2$ 来结对，可最后还是不够 $3$ 个，只好留下来，与 $4$ 看看。
4. 可是发现没有 $4$，那么直接打印输出 $2$。剩下的两个 $2$ 和 $3$ 只需要跟着前面两组混混即可，一定可以混到自己的队伍。

所以，这道题就很简单了，只需要按照步骤模拟即可。

## Part4 代码

请不要抄袭！

```c++
#include<iostream>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int e[n+1];
		for(int i=1;i<=n;++i)
			cin>>e[i];
		int sum[n+1];
		for(int i=0;i<=n;++i)
			sum[i]=0;
		for(int i=1;i<=n;++i)
			++sum[e[i]];
		int ans=0;
		int left=0;
		for(int i=1;i<=n;++i){
			ans+=(sum[i]+left)/i;
			left=(sum[i]+left)%i;
		}
		cout<<ans<<endl;
	}
}
```

## Part5 结语

我给大家看看另一位同学的 TLE 代码，大家来看看是什么问题。

![另一位同学的代码](https://tianyublog.github.io/%E5%8F%A6%E4%B8%80%E4%BD%8D%E5%90%8C%E5%AD%A6%E7%9A%84%E4%BB%A3%E7%A0%81.PNG)

没错，问题就出在 `memset` 上面。`memset` 的复杂度并不是大家以为的 $\operatorname{O}\left(1\right)$ 啊！是 $\operatorname{O}\left(N\right)$ 的复杂度。大家用的原因可能是它的常数较小。但在这道题中，`System Test` 就把 `memset` 卡掉了。这是件好事，提醒更多的人。~~不过我没有被卡掉，我是现场定义的哈哈！~~

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1355B)

------------
# 题意
给你 $n$个人，你需要给这些人组队。每个人有个对应的 $a_i$ 值，表示这个人如果组队了，队伍应当人数大于等于 $a_i$。求最多能组出多少个队伍，但有人可以没有队伍。

# 思路
我们把所有的人按照 $a_i$ 的值从小到大排序，然后从前向后遍历排序后的数组，并记录一个 $sum$ 值，表示当前已经遍历过且没有队伍的人数。如果 $sum = a_i$，则表示我们可以让这 $sum$ 个人组成队伍。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int T,n,a[N];
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+1+n);
		int ans=0,s=0;
		for(int i=1;i<=n;i++){
			s++;
			if(s==a[i]){
				s-=a[i];
				ans++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
完结撒花~

---

## 作者：chenyihang2012 (赞：0)

# 第一篇题解：
先说思路：因为子序列必须要长于这里面最大的数，即开一个桶数组，统计每个数出现了几次，再用次数除以这个数的大小，把多的数的次数存到下一个数出现的次数的地方。

注意：一定要把数组定到外面。
##### 一遍的流程：
```c
int n,h=0,m=0;
		cin>>n;
		for(int j=1;j<=n;j++)
			a[j]=0;
		for(int j=1;j<=n;j++){
			int x;
			cin>>x;
			a[x]++;
		}
		for(int j=1;j<=n;j++){
			h+=(a[j]+m)/j;
			m=(a[j]+m)%j;
		}
		cout<<h<<endl;
```



### 完整代码：
```
#include <bits/stdc++.h>
using namespace std;
int a[200005]={0}; \\ 定义加归零
int main() {
	int t;
	cin>>t;\\输入次数
	for(int i=1;i<=t;i++){
		int n,h=0,m=0;\\在循环里定义，省的归零
		cin>>n;\\输入单次的母序列长度
		for(int j=1;j<=n;j++)
			a[j]=0;\\循环清零在数据较多的时候快于其他方法
		for(int j=1;j<=n;j++){
			int x;
			cin>>x;\\输入数据
			a[x]++;\\计入次数
		}
		for(int j=1;j<=n;j++){
			h+=(a[j]+m)/j;\\运算单个数构成的子序列数
			m=(a[j]+m)%j;\\将剩余的数归入下一位
		}
		cout<<h<<endl;\\输出
	}
   return 0;\\华丽收场
}

---

## 作者：__hjwucj__ (赞：0)

# 题解：CF1355B Young Explorers

[题目传送门](https://www.luogu.com.cn/problem/CF1355B)

## 思路

考虑 $\texttt {dp}$。

设 $f_i$ 为划分第 $i$ 个数的最小序列数，那就可以得出状态转移方程：

$$f_i \gets \max (f_{i-1},f_{i-a_i}+1)$$

具体可见[这里](https://www.luogu.com.cn/article/9rieistn)（解法差不多）。

## 代码

由于 $\texttt {memset}$ 的时空复杂度是 $O(n)$ 的，所以我们可以使用动态数组（要定义在 $\texttt {while}$ 循环里面）或手动清空。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n;
int main ()
{
	cin>>T;
	for (int qp=1;qp<=T;qp++)
	{
		cin>>n;
		vector<int> a(1);
		a[0]=0;
		for (int i=1;i<=n;i++) {int x;cin>>x;a.push_back (x);}
		sort (a.begin ()+1,a.end ());
		vector<int> f (1);
		f[0]=0;
		int maxn=0;
		for (int i=1;i<=n;i++)
		{
			int x;
			if (i>=a[i])
				x=max (f[i-1],f[i-a[i]]+1),maxn=max (maxn,x);
					else x=f[i-1];
			f.push_back (x);
		}
		cout<<maxn<<endl;
	}
	return 0;
}
```

---

## 作者：jess1ca1o0g3 (赞：0)

[Portal(CF)](http://codeforces.com/problemset/problem/1355/B)

[Portal(Luogu)](https://www.luogu.com.cn/problem/CF1355B)

## 题意

给定序列 $a$，将其分割为许多子序列，有些数可以不分，每个子序列的长度要大于等于子序列最大值，最多能分多少？

## 思路

动态规划。

我们设 $dp_i$ 为序列前 $i$ 个数最多能分多少组。

对于当前这个数，考虑两种情况：

- 如果不单独为一组，也就是不管它，那么 $dp_i=dp_{i-1}$，这是显而易见的。

- 如果单独一组，那么 $a_i$ 就成了该子序列的最大值，为了保证能更多地分，那么该子序列长度至少为 $a_i$。分完以后，剩下 $i-a_i$ 个数，不过分的子序列个数多了 $1$ 个。

当 $i<a_i$ 时，也就是不够分时，考虑第一种情况，直接不管。

当 $i\geq a_i$ 时，可以单独分一组，那么考虑第二种情况，能多分就多分。

得到状态转移方程：

$$dp_i=\begin{cases} dp_{i-1} &i<a_i\\ \max(dp_{i-1},dp_{i-a_i}+1) &i\geq a_i \end{cases}$$

代码就好写了。

## 注意

- 由于多测，数组不要用 `memset` 函数，需要手动置为 $0$。

- 序列 $a$ 需要排序，这样 $a_i$ 才能成为子序列最大值。

## $\mathtt{Code}$

```cpp
#include<cstdio>
#include<algorithm>
const int SIZE=2e5;
int t,n,s[SIZE+5],dp[SIZE+5];
signed main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",s+i);
        std::sort(s+1,s+n+1);
        for(int i=1;i<=n;i++){
            dp[i]=dp[i-1];
            if(i>=s[i]){
                dp[i]=std::max(dp[i-1],dp[i-s[i]]+1);
            }
        }
        printf("%d\n",dp[n]);
        for(int i=1;i<=n;i++) dp[i]=0;
    }
}
```

---

## 作者：Weekoder (赞：0)

# CF1355B Young Explorers 题解

## 题目大意

有一个长度为 $N$ 的数组 $e_1,e_2,e_3,\dots,e_{N-1},e_N$，现在要把这个数组 $e$ 划分为若干个子序列 $S_1,S_2,\dots,S_n$，使得每个子序列 $S_i$ 满足 $\max(S_i)\le\lvert S_i\rvert$，并且可以选择若干个数**不加入划分的子序列中**，求最多能划分几个子序列。

讲的通俗一点，就是要从 $e$ 中选几个子序列出来，有些数可以不选，并且每个子序列的长度都要大于等于这个子序列中的最大值。

## 解题思路

考虑 DP 求解。

设 $dp_i$ 表示前 $i$ 个人的最大分组数目。我们可以发现，当前的决策就是考虑第 $i$ 个人要不要单独分组。分以下两种情况讨论：

- 不单独分组。这时候，我们便不考虑第 $i$ 个人，于是这里 $dp_i$ 的结果就和 $dp_{i-1}$ 是相同的。

- 单独分组。如果要单独分组，我们就要让 $e_i$ 成为这一组的最大值，也就是说，这个序列的长度就得大于等于 $e_i$，但我们想分的尽量多，所以剩下的空间也得尽量多，所以这个序列的长度就是最小的 $e_i$。那么，当我们在分完这个组后，剩下能给我们用的就只有 $i-e_i$ 个人了，但是分的组数就会多 1。这时候，我们不难发现第 $i$ 个人单独分组的条件：$i\ge e_i$，因为只有这样才有空间给我们去单独分一个组。如果 $i<e_i$，也不用担心剩下的数，因为题目中说可以不让一些数划分进子序列中。

于是我们可以列出**状态转移方程：**
$$
dp_i=\begin{cases}
i\ge e_i, & \max(dp_{i-1},dp_{i-e_i}+1) \\
i<e_i, & \max(dp_i, dp_{i-1})
\end{cases}
$$

按照状态转移方程逐步求解就行了。

## 代码细节

1. 因为有 $T$ 组数据，每次 $dp$ 数组都需要重置为 $0$。但是不要用 memset 函数，因为这样会导致超时。建议手动重置。

1. $e$ 数组是需要排序的，因为这样才能保证 $e_i$ 前面的数都比 $e_i$ 小，这样，$e_i$ 才是划分的数组中的最大值。

## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
int t, n, e[N], dp[N];
int main() {
    ios::sync_with_stdio(0);
    cin >> t;
    while (t --) {	// T组数据
        cin >> n;
        for (int i = 1; i <= n; i++)
            dp[i] = 0;	// 重置dp数组，不要写memset
        for (int i = 1; i <= n; i++)
            cin >> e[i];  // 输入数组
        sort(e + 1, e + 1 + n);  // 排序是必要的，这样才能保证正确性
        for (int i = 1; i <= n; i++) {	// 循环求解，套上状态转移方程就行
            if (i >= e[i])
                dp[i] = max(dp[i - 1], dp[i - e[i]] + 1);
            else
            	dp[i] = max(dp[i], dp[i - 1]);
    	}
        cout << dp[n] << "\n";	// 输出
    }
    return 0;
}
```

---

## 作者：Into_qwq (赞：0)

没时间打$cf$，就过来写题解吧

题目大意(简化版)：

有几个数字，把它们划分成尽可能的多的子序列，子序列的长度要大于等于这个子序列中最大的数

所以，贪心策略：尽量把相同的数分在一起

如果剩余了几个数，那么就把它和大的分在一起

代码如下
```c++
#include<bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for(register int i=l;i<=r;++i)//我懒
map <int,int> p;//用map存储
inline void solve(int n){
    p.clear();//直接清空很方便
    int ans=0,people_left=0;
    rep(i,1,n){
        int x;
        cin>>x;
        ++p[x];//记录
    }
    rep(i,1,n){
        ans+=(p[i]+people_left)/i;//分组
        people_left=(p[i]+people_left)%i;//记录剩余的
    }
    cout<<ans<<endl;//输出
}
int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        solve(n);
    }
    return 0;
}
```
完结啦qwq

---

## 作者：do_while_true (赞：0)

让 $e$ 小的尽量和小的在一块。也就是说，假如有一个 $e=x$ 的，我们让他和 $x$ 个人走即可，不需要让他再和其他人组队，这样一定更优。所以我们拍完序，一个一个组队，如果当前队伍可以走就让这个队伍走，再重新集结队伍。

只需要维护当前队伍大小和当前队伍的需求即可，如果大小满足需求就计数器+1，重新计算队伍。

[$\mathcal{Code}$](https://codeforces.com/contest/1355/submission/80311169)

---

