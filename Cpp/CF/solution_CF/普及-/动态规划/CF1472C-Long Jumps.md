# Long Jumps

## 题目描述

Polycarp found under the Christmas tree an array $ a $ of $ n $ elements and instructions for playing with it:

- At first, choose index $ i $ ( $ 1 \leq i \leq n $ ) — starting position in the array. Put the chip at the index $ i $ (on the value $ a_i $ ).
- While $ i \leq n $ , add $ a_i $ to your score and move the chip $ a_i $ positions to the right (i.e. replace $ i $ with $ i + a_i $ ).
- If $ i > n $ , then Polycarp ends the game.

For example, if $ n = 5 $ and $ a = [7, 3, 1, 2, 3] $ , then the following game options are possible:

- Polycarp chooses $ i = 1 $ . Game process: $ i = 1 \overset{+7}{\longrightarrow} 8 $ . The score of the game is: $ a_1 = 7 $ .
- Polycarp chooses $ i = 2 $ . Game process: $ i = 2 \overset{+3}{\longrightarrow} 5 \overset{+3}{\longrightarrow} 8 $ . The score of the game is: $ a_2 + a_5 = 6 $ .
- Polycarp chooses $ i = 3 $ . Game process: $ i = 3 \overset{+1}{\longrightarrow} 4 \overset{+2}{\longrightarrow} 6 $ . The score of the game is: $ a_3 + a_4 = 3 $ .
- Polycarp chooses $ i = 4 $ . Game process: $ i = 4 \overset{+2}{\longrightarrow} 6 $ . The score of the game is: $ a_4 = 2 $ .
- Polycarp chooses $ i = 5 $ . Game process: $ i = 5 \overset{+3}{\longrightarrow} 8 $ . The score of the game is: $ a_5 = 3 $ .

Help Polycarp to find out the maximum score he can get if he chooses the starting index in an optimal way.

## 说明/提示

The first test case is explained in the statement.

In the second test case, the maximum score can be achieved by choosing $ i = 1 $ .

In the third test case, the maximum score can be achieved by choosing $ i = 2 $ .

In the fourth test case, the maximum score can be achieved by choosing $ i = 1 $ .

## 样例 #1

### 输入

```
4
5
7 3 1 2 3
3
2 1 4
6
2 1000 2 3 995 1
5
1 1 1 1 1```

### 输出

```
7
6
1000
5```

# 题解

## 作者：Melon_Musk (赞：14)

[CF1472C Long Jumps题面](https://www.luogu.com.cn/problem/CF1472C)

[安利我的博客](https://www.melonmusk.cn/index.php/2021/02/01/cf1472c-long-jumps-%e9%a2%98%e8%a7%a3/)

## 题面描述

一个长为$ n $的序列$ a $，如果当前在下标$ i $，则下一步会跳到$ i + a[i] $，直到跳出序列。 要求答案即为路径上经过的$ a[i] $之和。现在你可以任意选择起点，求答案的最大值。 

## 分析

**一道比较显然的dp题**

对于我们当前所在的位置 $ i $ ，显然它可以转移到 $ i+a[i] $。

令$f[i]$表示到走到当前所在的位置$i$的路径中答案的最大值。

故由题意得转移方程式为：

$f[i+a[i]]=max(f[i+a[i]],f[i]+a[i])$

初始所有$f[i]$均为0。总答案即为所有$f[i]$中的最大值

于是我飞速将此代码码了出来，然后发现它 [RE](https://www.luogu.com.cn/record/45892057) 了。

原因是这题的$a[i]$范围在 $10^9$，我们的$f[i]$直接开数组显然会爆炸！

所以我们可以将$f$数组改为map类型！因为我们的$n$只有$2⋅10^5$，所以可以通过这道题。

[AC记录](https://www.luogu.com.cn/record/45892115)

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e7+7;
ll read() 
{
	ll res=0,f=1;
	char c=getchar();
	while(!isdigit(c) && c!='-') c=getchar();
	if(c=='-') f=-1,c=getchar();
	while(isdigit(c)) res=(res<<1)+(res<<3)+c-48,c=getchar();
	return res*f;
}
ll a[maxn];
map<ll,ll> f;
int main()
{
	int T=read();
	while(T--)
	{
		int n=read();
		ll maxx=0;
		f.clear();
		for(int i=1;i<=n;i++) 
			a[i]=read();
		for(int i=1;i<=n;i++)
		{
			f[i+a[i]]=max(f[i+a[i]],f[i]+a[i]);
			maxx=max(maxx,f[i+a[i]]);
		}
		printf("%lld\n",maxx);
	} 
	return 0;
}
```

求点赞awa！


---

## 作者：__shadow__ (赞：9)

【题目分析】

本题有两个方法，

方法一：每一个位置可得的分分别求出，打擂找出最大（可得部分分）

方法二：从后往前求可得的分数，以避免一些不必要的重复。

【设计程序】

方法一：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<stdio.h>
#include<cstdio>
#include<queue>
using namespace std;
const int N = 2 * 1e5 + 5;
int a[N];
int n;
long long score(int x)//求这个位置出发可得的分
{
	long long ans = 0;
	while(x <= n)//当x还在n的范围中时
	{
		ans += a[x];//加这个位置的值
		x += a[x];//把x标到下一个位置
	}
	return ans;//返回得分
}
int main()
{
	int p;
	scanf ("%d", &p);//输入组数
	while (p--)
	{
		long long maxn = 0;
		scanf ("%d", &n);//输入数据个数
		for (int i = 1;i <= n; i++)//输入数据
			scanf ("%d", a + i);
		for (int i = 1;i <= n; i++)//从每一个位置开始
			maxn = max(maxn, score(i));//求最大值
		printf ("%d\n", maxn);//输出最大值
	}
	return 0;
}
```

方法二：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<stdio.h>
#include<cstdio>
#include<queue>
using namespace std;
const int N = 2 * 1e5 + 5;
int a[N];
long long b[N];//b[i]表示从i出发可得的分数
int n;
int main()
{
	int p;
	scanf ("%d", &p); //输入组数
	while (p--)
	{
		scanf ("%d", &n); //输入数据个数
		for (int i = 1;i <= n; i++)//输入数据
			scanf ("%d", a + i);
		for (int i = n;i >= 1; i--)
		{
			if (i + a[i] > n)
			//如果后一个位置在n的范围外
				b[i] = a[i];//此位置的得分为本位置的值
			else//如果在n中
				b[i] = a[i] + b[i + a[i]];
				//本位置的值加上下个位置的得分
		}
		long long maxn = b[1];
		for (int i = 2;i <= n; i++)//打擂找最大
			maxn = max(maxn, b[i]);
		printf ("%d\n", maxn);//输出最大值
	}
	return 0;
}
```

【调试代码】
1.	测试样例
2.	自测数据（特殊值，边界值）

数据：

4

5

0 0 0 0 0

3

3 2 1

1

1000

5

1 1 1 1 1



---

## 作者：BYWYR (赞：7)

好像所有题解都用了dp？可是有些人（比如我）就是想不到dp，其实这道题可以直接**模拟**，题目怎么说我们就怎么做（也可以看作是**记忆化搜索**）

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[205000],vis[205000];
int main(){
	scanf("%d",&t);
	while(t--){
		int maxn=0;
		memset(vis,0,sizeof(vis));
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%d",&a[i]);
		for(int i=1;i<=n;++i){
			if(vis[i])continue;
			int pts=0,pos=i;
			while(pos<=n){
				vis[pos]=1;//记忆化
				pts+=a[pos];
				pos=a[pos]+pos;//题目怎么说我们就怎么做，直接模拟
			}
			maxn=max(maxn,pts);
		}
		printf("%d\n",maxn);
	}
	return 0;
}
```


---

## 作者：胖头鱼学员 (赞：5)

# CF1472
## [CF传送门](http://codeforces.com/problemset/problem/1472/C)
## [洛谷传送门](https://www.luogu.com.cn/problem/CF1472C)

## $Question Meaning$

$Polycarp$在玩一个游戏，给定有$n$个元素的数组$a$，设定一个起始点$i$。当 $i\leq n$时， $i=i+a_i$，得分$score = score + a_i$，试求出对于数组$a$可以得出的最大得分。

## $Solution$

考虑$dp$转移：

每一个点只能转移到下标为$i+a_i$的点，那么对于每一个$i$，那么用$Q_i$来存满足下式的所有$j$：
$$
j + a_j = i
$$

那么现在只要按顺序计算，随后取最大值即可，设$Q_i$为满足柿子（式子）的所有$j$的集合，则状态转移方程为：
$$
dp_i = \sum_{j\in Q_i}dp_j
$$

## $Code$
```
# include <algorithm>
# include <iostream>
# include <vector>

using namespace std;

const int kMaxN = 2e5 + 2;

int t, n;
int a[kMaxN], dp[kMaxN];
vector<int> ve[kMaxN];

void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    ve[i].clear();
  }
  for (int i = 1; i <= n; i++) {
    int mx = 0;
    for (auto j : ve[i]) {
      mx = max(mx, dp[j]);
    }
    dp[i] = a[i] + mx;
    ve[min(i + a[i], n + 1)].push_back(i);
  }
  cout << *max_element(dp + 1, dp + 1 + n) << endl;
}

int main() {
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
```

---

## 作者：Parat_rooper (赞：4)

# 题面翻译：
有一个长为n的序列a，如果当前在下标i，则下一步会跳到i + a[i]，直到跳出序列。
现在可以任意选择起点，求路径上的数的和的最大值。
# 解题思路：
本题是一个典型递推，相当于一个每次走$a_i$的楼梯问题，我们考虑收集型递推（扩散型也一样，不过本人是收集型），用递推算出所有路径之后，取最大值
首先，能直接走出去的起点的值一定是$a_i$自己，所以从后往前更新能直接走出去的起点路径值。否则这条路径一定是$a_i$与以（i+$a_i$）为起点的路径的和，此时是由之前已经得出的状态的附加属性（路径）得出这个状态的附加属性，故为收集型递推。

## 附上代码：
```cpp
#include <iostream>
#include <cstring>
 
using namespace std;
 
const int kMaxN = 2e5 + 1;
 
int t, n, a[kMaxN], d[kMaxN], maxx;
 
int main() {
  cin >> t;
  while (t--) {
    maxx = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    d[n] = a[n];
    for (int i = n - 1; i >= 1; i--) {
      d[i] = a[i];
      if (a[i] <= (n - i)) {
        d[i] += d[i + a[i]];
      }
    }
    for (int i = 1; i <= n; i++) {
      maxx = max(maxx, d[i]);
    }
    cout << maxx << endl;
  }
  return 0;
}
```


---

## 作者：Need_No_Name (赞：1)

# Solution for CF1472C

2021.4.6

本蒟蒻第二篇题解

### STEP1：分析题目

给定数组 $a$ ，定义 $score=0$ 。从数组第 $i$ 项开始，将 $score+=a_i$ ，下一次操作则跳跃到 $a$ 的第 $i+a_i$ 项 ，使得 $score$ 最大。

### STEP2：选择方法

数据范围为 $0≤n≤2·10^5$ ，看来只能用 $O(n)$ 算法。

这道题可以考虑考虑 $dp$ ，但只限于一维 $dp$ 。这里我们就用 $dp$ 来一发。

### STEP3：既然选择了dp，那就搞一下状态

这道题最容易想到的$dp$状态就是 $dp[i]$ 从 $a_i$ 起跳时 $score$ 的最大值。则 $dp[i]$ 为 $dp[a[i]]+a[i]$ ，也就是由 $dp[a[i]]$ 往回推，也可以自然而然地想到 $dp$ 要从后往前循环。

#### 需要特别注意的两点：
1.需要特判循环有没有越界，即 $i+a[i]$ 需要小于等于 $n$ ，否则将 $dp[i+a[i]]$ 赋值为 $a[i]$ 。

2.需要特别注意，数组中可以为负数，也就是说每次都得将   $dp[i+a[i]]+a[i]$ 与 $0$ 取最大。

有了思路，那么转移方程就简单了。如下：


```cpp
if(i+a[i]<=n)//特判是否越界 
{
	dp[i]=max(0,dp[i+a[i]]+a[i]);
}
else
{
	dp[i]=a[i];
}
```


### Step4：快乐码代码(bushi
上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const signed N=200005;
inline read()
{
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);ch=getchar();
	}
	return x*f;
}
inline Never_TLE()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}
int T;
int dp[N],a[N],n,maxans=0;
int main()
{
	
	Never_TLE();
	T=read();
	while(T--)
	{
		memset(dp,0,sizeof(dp));
		memset(a,0,sizeof(a));
		maxans=0;
		n=read();
		for(register int i=1;i<=n;i++)
		{
			a[i]=read();
		}
		for(register int i=n;i>=1;i--)
		{
			if(i+a[i]<=n)//特判是否越界 
			{
				dp[i]=max(0,dp[i+a[i]]+a[i]);
			}
			else
			{
				dp[i]=a[i];
			}
			maxans=max(maxans,dp[i]);//不断取最大 
			
		}
		cout<<maxans<<endl; 
	}
	return 0;
}
//请勿抄袭 
```

当然，我为了优化时间复杂度，将循环前加上register，同时加入了快读快写。看卡常代码看的不舒服的见下面的代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int T;
int dp[N],a[N],n,maxans=0;
int main()
{
	cin>>T;
	while(T--)
	{
		memset(dp,0,sizeof(dp));
		memset(a,0,sizeof(a));
		maxans=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		for(int i=n;i>=1;i--)
		{
			if(i+a[i]<=n)//特判是否越界 
			{
				dp[i]=max(0,dp[i+a[i]]+a[i]);
			}
			else
			{
				dp[i]=a[i];
			}
			maxans=max(maxans,dp[i]);//不断取最大 
			
		}
		cout<<maxans<<endl; 
	}
	return 0;
}
//请勿抄袭 
```
完结撒花，好文要顶qwq

---

## 作者：UperFicial (赞：1)

# 递推

### 前言

个人感觉更像是模拟，只要把题目理解了直接上就完事。

~~小学阅读训练五合一~~

题目链接：[$\text{Link}$](https://www.luogu.com.cn/problem/CF1472C)

### 题意简述

- 给定长度为 $n$ 的数列 $a$。

- 选任意一个初始位置 $i$，对于一次转移：$i=i+a_i,score=score+a_i$。（$1\le i\le n$）

- 求最大的 $score$。

### 题目分析

不难发现跟 $dp$ 的状态转移方程很类似。

设 $dp_i$ 为以 $i$ 为初始位置时的最大得分。

根据题意直接上：$dp_i=\begin{cases}a_i&i+a_i>n\\dp_{i+a_i}+a_i&i+a_i\le n\end{cases}$

最后在 $dp_i$ 之中取个最大值，因为初始位置是任意的。

时空复杂度：$O(n)$。

[$code$](https://paste.ubuntu.com/p/sfvjCvXvtG/)

~~最优解 $\sout{top2}$~~

$$\texttt{The End.by UF}$$




---

## 作者：juun07 (赞：1)

## 简单dp

思路也跟楼上差不多

也是从后往前

能加就加，不能加就沿用前面的结果

状态转移方程为$dp[i]=a[i]+dp[i+a[i]]$

## Code

```cpp
#include<iostream>
using namespace std;
int a[200001], b[200001], t, n;
int main()
{
	cin>>t;
	for(int j=0; j<t; j++)
    { //题目有多组数据，故需输入t次
		cin>>n;
		for(int i=1; i<=n; i++)//输入不多说
        {
            cin>>a[i]; 
        }
		int ans=0;
		for(int i=n; i>=1; i--) //代码核心部分，从后往前推
        {
			if((i+a[i])>n) //能否放入背包
                b[i]=a[i]; 
			else 
                b[i]=a[i]+b[i+a[i]]; 
            //比较分数，择优
			ans=b[i]>ans?b[i]:ans;
		}
		cout<<ans<<"\n";
	}
	return 0;
} 
```

感谢阅读

---

## 作者：Phartial (赞：1)

## [传送门](https://www.luogu.com.cn/problem/CF1472C)
## 思路
其实是道很简单的动态规划题（~~却想了一个小时~~）

应该一~~亿~~眼就能看出转移方程：
$$ dp[i]=a[i]+(i+a[i]>n?0:a[i+a[i]]) $$
（~~完结撒花~~）
## 一点改进
- 我们看一眼就会发现$i+a[i]$这个式子出现了两次，所以可以用一个临时变量x来存储这个值
- 实际上这里dp数组完全是多余的，所以我们可以直接在a数组上进行计算

上代码！
## 代码
```cpp
#include <iostream>
using namespace std;
const int kMaxN = 2e5 + 1;
int t, n, a[kMaxN], m;
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
    }
    for (int i = n; i >= 1; --i) {
      int x = i + a[i];
      a[i] += (x > n ? 0 : a[x]);
      m = max(m, a[i]);
    }
    cout << m << endl;
  }
  return 0;
}
```


---

## 作者：Fa1thful (赞：0)

### 题意：
给定一个数组，现在可以从任何一个地方开始，每取当前的一个数就要往前跳取得那个数的长度。求最多能取的数值是多少。
### 分析：
这题一看就是 $dp$ ，因为它是可以从任意一个点起跳的。如果从一个特别大的起跳，那么很可能会在后面错过更大的数，所以只能 $dp$。

#### dp状态
我们最容易想到的一个状态就是 $dp[i]$ 表示从 $i$ 起跳，能取到的的最大值。
#### dp方程
我们可以通过状态知道转移一共分为两种情况：1.跳了之后没有越界，可以往下跳。2.越界了，跳不了。所以说转移方程如下：
```cpp
if (i + a[i] <= n) dp[i] = max(0, dp[i + a[i]] + a[i]); //如果没越界
else dp[i] = a[i]; //越界了
```
还有一个问题，一定要从后往前枚举，因为前面的转态是由后面推出来的。
### 代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
int a[600000];
int dp[600000];
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		memset(dp, 0, sizeof(dp));     //多组数据别忘了初始值 
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
		}
		for (int i = n; i >= 1; i--)
		{
			if (i + a[i] <= n) dp[i] = max(0, dp[i + a[i]] + a[i]);
			else dp[i] = a[i];     //转移 
		}
		int maxx = -99999;
		for (int i = 1; i <= n; i++)
		{
			maxx = max(maxx, dp[i]);	  //打擂台找到从一个位置的起跳的最大值 
		}
		cout << maxx << endl;
	}
}
```


---

## 作者：qhy_ (赞：0)

### [原题地址](https://codeforces.com/contest/1472/problem/C)
### [洛谷题目地址](https://www.luogu.com.cn/problem/CF1472C)

------------
### 思路：
一道递推题，很容易可以得出

$$ sum_i=\left\{
\begin{aligned}
a_i&&&& (i+a_i>n) \\
sum_{i+a_i} &&&& (i+a_i<=n) \\
\end{aligned}
\right.
$$
当然，可以用记忆化，算过的就不用算了

------------
### $code$

```cpp
#include <cstring>
#include <iostream>

using namespace std;
using ll = long long;

ll n, a[200008], T, sum[200009];
ll ans;

ll F(ll x) {
  return x > n ? 0 : sum[x] ? sum[x] : sum[x] = a[x] + F(x + a[x]);
}

int main() {
  cin >> T;
  for (int p = 1; p <= T; p++) {
    memset(sum, 0, sizeof(sum));
    ans = 0;

    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
      if (!sum[i]) {
        sum[i] = F(i);
      }
      ans = max(ans, sum[i]);
    }
    cout << ans << endl;
  }
  return 0;
}
```


---

## 作者：YueYang1235 (赞：0)

好像所有题解都用了dp？可是有些人（比如我）就是想不到dp，其实这道题可以直接模拟，题目怎么说我们就怎么做（也可以看作是记忆化搜索）

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[205000],vis[205000];
int main(){
	scanf("%d",&t);
	while(t--){
		int maxn=0;
		memset(vis,0,sizeof(vis));
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%d",&a[i]);
		for(int i=1;i<=n;++i){
			if(vis[i])continue;
			int pts=0,pos=i;
			while(pos<=n){
				vis[pos]=1;//记忆化
				pts+=a[pos];
				pos=a[pos]+pos;//题目怎么说我们就怎么做，直接模拟
			}
			maxn=max(maxn,pts);
		}
		printf("%d\n",maxn);
	}
	return 0;
}
```


---

## 作者：KSToki (赞：0)

看他题目那么长，其实就是个简单的递推（也可以叫 dp，但我感觉不算。。。），直接根据题目可得 $f[i]=f[i+a[i]]+a[i]$，时间复杂度就 $O(n)$，直接上就是了。

代码：
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (0x7fffffff)
#define INF (1e18)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,a[200001],f[200001],ans;
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		for(R int i=1;i<=n;++i)
			a[i]=read(); 
		ans=0;
		for(int i=n;i;--i)
		{
			if(i+a[i]>n)
				f[i]=a[i];
			else
				f[i]=a[i]+f[i+a[i]];
			ans=max(f[i],ans);
		}
		putint(ans);
	}
	return 0;
} 
```


---

## 作者：江户川·萝卜 (赞：0)

算法：递推（动规）

从后往前推，记录每一个点的最高得分，时间复杂度 $ O(nt)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[200005],dp[200005];
int main(){
	int t,n;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]); 
		int ans=0;
		for(int i=n;i>=1;i--){
			if(i+a[i]>n) dp[i]=a[i];//跳飞了
			else dp[i]=a[i]+dp[i+a[i]];//跳完还能跳，加上跳过去的点的dp值
			ans=max(dp[i],ans);
		}
		printf("%d\n",ans);
	}
	return 0;
} 
```

---

