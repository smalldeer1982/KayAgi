# Pokémon Army (easy version)

## 题目描述

This is the easy version of the problem. The difference between the versions is that the easy version has no swap operations. You can make hacks only if all versions of the problem are solved.

Pikachu is a cute and friendly pokémon living in the wild pikachu herd.

But it has become known recently that infamous team R wanted to steal all these pokémon! Pokémon trainer Andrew decided to help Pikachu to build a pokémon army to resist.

First, Andrew counted all the pokémon — there were exactly $ n $ pikachu. The strength of the $ i $ -th pokémon is equal to $ a_i $ , and all these numbers are distinct.

As an army, Andrew can choose any non-empty subsequence of pokemons. In other words, Andrew chooses some array $ b $ from $ k $ indices such that $ 1 \le b_1 < b_2 < \dots < b_k \le n $ , and his army will consist of pokémons with forces $ a_{b_1}, a_{b_2}, \dots, a_{b_k} $ .

The strength of the army is equal to the alternating sum of elements of the subsequence; that is, $ a_{b_1} - a_{b_2} + a_{b_3} - a_{b_4} + \dots $ .

Andrew is experimenting with pokémon order. He performs $ q $ operations. In $ i $ -th operation Andrew swaps $ l_i $ -th and $ r_i $ -th pokémon.

Note: $ q=0 $ in this version of the task.

Andrew wants to know the maximal stregth of the army he can achieve with the initial pokémon placement. He also needs to know the maximal strength after each operation.

Help Andrew and the pokémon, or team R will realize their tricky plan!

## 说明/提示

In third test case we can build an army in such way: \[1 2 5 4 3 6 7\], its strength will be $ 5−3+7=9 $ .

## 样例 #1

### 输入

```
3
3 0
1 3 2
2 0
1 2
7 0
1 2 5 4 3 6 7```

### 输出

```
3
2
9```

# 题解

## 作者：Need_No_Name (赞：5)

2021.3.29

本蒟蒻第一篇题解 有一些小鸡冻。

废话不多说，我们开冲！

### STEP1：分析题目



当然，翻译中已经给了分析，但我还是写一下吧。

题意为：给定一个数组a，求如何排列数组中的数，使得$a[1]-a[2]+a[3]-...$最大，求这个最大值。

~~（就是把翻译复制了一遍）~~

### STEP2：选择方法

这道题我们可以选择下一个元素是加上还是不加。emm...再来康康数据范围，如果不大，还可以考虑考虑记忆化搜索... 

。。。

什么！$1≤n≤3·10^5$看来只能选择dp了。。。

~~（瞎扯。。。）~~

### STEP3：既然选择了dp，那就搞一下状态

这道题定义$dp[N][3]$ 其中，$dp[i][0]$表示第$i$个减，反之$dp[i][1]$表示从第$i$个是加。

则状态转移方程为



```cpp
dp[i][0]=max(dp[i-1][0],dp[i-1][1]-num[i]);
dp[i][1]=max(dp[i-1][1],dp[i-1]
```

   
   
有了转移方程，一切也就好说了。

### STEP4：快乐码代码(bushi

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300010;
long long T,n,q,num[N],dp[N][3]; //不开long long见祖宗 

int main()
{
	cin>>T;
	while(T--)
	{
		memset(num,0,sizeof(num));
		memset(dp,0,sizeof(dp));
		cin>>n>>q;
		for(long long i=1;i<=n;i++)
		{
			cin>>num[i];
		}
		dp[0][0]=dp[0][1]=0;
		dp[1][0]=num[1];
		dp[1][1]=num[1];
		for(long long i=1;i<=n;i++)
		{
			dp[i][0]=max(dp[i-1][0],dp[i-1][1]-num[i]);
			dp[i][1]=max(dp[i-1][1],dp[i-1][0]+num[i]);
		}
		cout<<max(dp[n][0],dp[n][1])<<endl;//在两种情况之中取最大值
	}
	return 0;
} 
//禁止抄袭
```

说点趣事：最近本蒟蒻刚刚学了树形dp，看到这道题dp需要用两种情况，于是直接下意识D!F!S!写的特别得意，噼里啪啦敲着键盘，旁边童鞋康了一眼然后默默地说：你干嘛不用循环。。。

qwq能给本蒟蒻一个赞吗qwq


---

## 作者：忘怀星 (赞：3)


题目提供一个序列，要求你求出一个序列 $b_1\ ,\ b_2\ ,\ b_3\dots$ 使得 $a_{b_1}\ -\ a_{b_2}\ +\ a_{b_3}\ \dots$ 的值最大

我们定义 $f_i$ 为选择奇数个元素并选择 $a_i$ 所能得到的最大值， $g_i$ 为选择偶数个元素并选择 $a_i$ 所能得到的最大值

我们有转移：

$f_i = \max(a_i,a_i+\max\limits_{j=1}^{j<i}g_j)$

$g_i = -a_i+\max\limits_{j=1}^{j<i}f_j$

我们发现在求取 $\max\limits_{j=1}^{j<i}g_j$ 和 $\max\limits_{j=1}^{j<i}f_j$ 复杂度不够优秀，我们换一种定义，将 $f_i$ 定义为 小于等于 $i$ 的情况下选取偶数个元素所能求得的最大值。 $g_i$ 同理。

我们可以得到新的转移式

$f_i = \max(a_i,f_{i-1},a_i+g_{i-1})$

$g_i = \max(g_{i-1},-a_i+f_{i-1})$

我们再使用类似于滚动数组的方式进行空间的优化，可以得到最终的转移式：

$f = \max(a_i,f,a_i+g)$

$g = \max(g,f-a_i)$


---

## 作者：_Winham_ (赞：2)

题目意思：

有一个数组 $a$，让你创造个数组 $b$，问你怎么样让 $a_{b_{1}} - a_{b_{2}} + a_{b_{3}} +\dots$ 结果最大。

----

思路：

这是一道问你怎么最大的问题，所以可以用贪心来做。此时就有两个判断：

- $a_{i} < a_{i-1}$ 且当前为减时，我们就 $b$ 数组就加上此数。
- $a_{i} > a_{i-1}$ 且当前步数为加时，我们也把这个数加到 $b$ 数组中。

---

好了，讲完了，上代码。

```cpp
#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
using namespace std;
#define int long long
const int N = 1e6+10;
const int INF = 0x3f3f3f3f;
int T;
int n,q,a[N];
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	cin>>T;
	while(T--){
		cin>>n>>q;
		a[0]=a[n+1]=0;
		bool in=0;//1为加，0为减
		int sum=0;
		for(int i=1;i<=n+1;i++){
			if(i<=n)cin>>a[i];
			if(a[i]>a[i-1]&&!in)sum-=a[i-1],in=1;
			if(a[i]<a[i-1]&&in)sum+=a[i-1],in=0;
		}
		cout<<sum<<endl;
	}
	return 0;
}

```

---

## 作者：STDquantum (赞：2)

提供两种 AC 做法。

---

看到这样的一个求值方式，不难想到用 DP 解决。

设 $f_{i,0/1}$ 为 $i$ 可选可不选，前 $i$ 个能达到的最大值。

其中 $i$ 若选，则 $0$ 代表答案中 $a_i$ 系数为负，$1$ 代表答案中 $a_i$ 系数为正。

若 $i$ 不选，则 $0$ 代表距离 $i$ 最近的一个已选的元素 $a_j$ 在答案中系数为负，$1$ 代表距离 $i$ 最近的一个已选的元素 $a_j$ 在答案中系数为正。

那么就有转移 $f_{i,0}=\max\{f_{i-1,1}-a_i,f_{i-1,0}\}$ 和 $f_{i,1}=\max\{f_{i-1,0}+a_i,f_{i-1,1}\}$。

由于 $a_i$ 一定为正，所以系数为正的数字个数一定比系数为负的数字个数多 $1$，那么答案就是 $f_{n,1}$。

转移只用到了 $i-1$ 的状态，所以可以把第一维去掉。

记得开`long long`。

代码：

```cpp
int n, q, t;
long long f[2];
inline void main() {
  for (read(t); t--; f[0] = f[1] = 0) { // 记得清空数组
    read(n), read(q); // 记得题里还有一个q要读，虽然没用
    for (int i = 1, x; i <= n; ++i) {
      read(x);
      f[0] = max(f[1] - x, f[0]);
      f[1] = max(f[0] + x, f[1]);
    }
    write(f[1]), putchar('\n');
  }
}
```

---

第二种就和 C2 的 hard 版本联系密切了，不过也不用担心，思路是通用的。

小 trick：如果实在不会做可以多看看样例找规律，尤其是这种 easy version，可以去看看 hard version 的样例，好好利用会有大用。（其实这次 C2 给的样例最适合发现这题的规律了）

先给结论：定义 $a_0=a_{n+1}=0$，对于波峰 $i$ 有 $a_i\gt a_{i-1}$ 且 $a_i\gt a_{i+1}$，对于波谷 $i$ 有 $a_i\lt a_{i-1}$ 且 $a_i\gt a_{i+1}$。所有波峰、波谷都要选，波峰系数为正，波谷系数为负。

感性证明：可以考虑一加一减的一个二元组 $(a_i,a_j)$，其中 $i\lt j$。若是选一个波峰和一个波谷一定是局部最优的。若 $a_i$ 不是波峰，对答案贡献会减小，若 $a_j$ 不是波谷，对答案贡献也会减小。所以把所有二元组都统计上一定是最优的。

所以沿途判断是波峰就加、是波谷就减就好。

```cpp
int n, q, t, a[N];
ll ans;
inline void add(int x) {
  if (a[x] > a[x - 1] && a[x] > a[x + 1]) { // 为波峰
    ans += a[x];
  } else if (a[x] < a[x - 1] && a[x] < a[x + 1]) { // 为波谷
    ans -= a[x];
  }
}
inline void main() {
  for (read(t); t--;) {
    read(n), read(q);
    for (int i = 1; i <= n; ++i) { read(a[i]); }
    a[n + 1] = ans = 0; // a[n+1]=0是为了保证答案正确性，因为a[n]也可能被选上
    for (int i = 1; i <= n; ++i) { add(i); }
    write(ans), putchar('\n');
  }
}
```

# 

---

## 作者：Cappuccino_mjj (赞：1)

一道模拟题~

---

## [题目传送门](https://www.luogu.com.cn/problem/CF1420C1)

题目意思：

给出一个序列 $a$，然后我们要从 $a$ 里面求出一个单调递增的序列 $b$，使得按照题目中一减一加的方法求出来的答案最大。

---

思路：
1. 我们可以先用贪心的思路去想。因为要一减一加，所以我们尽量加大的数，减小的数。
2. 按照上面的说法，我们就遍历整个序列 $a$，每次判断当时是要加还是减，然后进行相应的操作就行了。

**注意：因为 $a_i$ 最大能达到 $3\times 10^5$，所以用来计算的变量要开 long long。**

---

代码：
```cpp
#include<iostream>
using namespace std;
const int N=1e6+10;
int a[N];
int t,n;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=0;i<=n;i++)
			cin>>a[i];
		a[n+1]=0;
		int up=0,down=0;//记录应该加还是减
		long long sum=0;
		for(int i=1;i<=n+1;i++)
		{
			if(a[i]>a[i-1])//如果当前的数大于上一个数，证明上一个阶段的最小数就是上一个数
			{
				if(down)sum-=a[i-1];
				down=0;
				up=1;
			}
			if(a[i]<a[i-1])//如果当前的数小于上一个数，证明上一个阶段的最大数就是上一个数
			{
				if(up)sum+=a[i-1];
				down=1;
				up=0;
			}
		}
		cout<<sum<<endl;
	}
	return 0;
}
```

---

完美撒花~

---

## 作者：Fa1thful (赞：1)

### 题目大意：
给一个序列，求它的连续的数$a[b[1]]-a[b[2]]+a[b[3]]-a[b[4]]$的最大值.

### 思路：
正如题目说的一样，$b$序列必须是连续的。一开始我就是没有看到连续的，所以贪心写了半个小时，发现样例没过。如果必须是连续的那么就只能$dp$了。


#### dp状态：
因为题目中有连接加和连接减两种情况，所以$dp$应该要有第二维表示是接着加还是减。所以说$dp[i][0]$表示第$i$个减，反之$dp[i][1]$表示从第$i$个是加。

#### dp转移：
根据我们之前推出的状态，可以轻松地想到转移方程。
```cpp
dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + a[i]);
dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - a[i]);
```
因为如果要减接着的肯定是上一个加，要加肯定要接上面的减。

### 代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
long long a[500000], dp[500000][2];
int main()
{
	int n, q;
	int T;
	cin >> T;
	while (T--)
	{
		memset(dp, 0, sizeof(dp));     //多组数据别忘了dp初始值哦 
		cin >> n >> q;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
		}
		for (int i = 1; i <= n; i++)
		{
			dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + a[i]);
			dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - a[i]);        //dp转移 
		}
		cout << max(dp[n][0], dp[n][1]) << endl;           //两种情况中取最大 
	}
 } 
```


---

## 作者：Heavy_Data_Struct (赞：0)

### 题目大意
给定整数 $N$ 和一个序列 $A$，求出一个非连续子序列 $B$，使 $B_1-B_2+B_3-B_4+\dots$ 最大。

### 分析
动态规划。设 $f_{i,j}$ 为区间 $[i,N]$ 的答案，$j=1$ 表示加上第一个元素，否则减掉第一个元素。由此有转移方程
$$
f_{i,j}=\begin{cases}
a_i & i=n\land j=1\\
0 & i=n\land j=0\\
\max(f_{i+1,j},a_i+f_{i+1,0}) & i\ne n\land j=1\\
\max(f_{i+1,j},f_{i+1,1}-a_i) & i\ne n\land j=0
\end{cases}
$$
### code
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
int f[30005][2], a[30005], n;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		cin >> n >> a[0];
		for(int i = 1;i <= n;i ++)
			cin >> a[i];
		for(int i = n;i >= 1;i --)
			for(int j = 1;~ j;j --) {
				f[i][j] = f[i + 1][j];
				if(i == n)
					if(j)	f[i][j] = max(0ll, a[i]);
					else	f[i][j] = max(-a[i], 0ll);
				else
					if(j)	f[i][j] = max(f[i][j], a[i] + f[i + 1][!j]);
					else	f[i][j] = max(f[i][j], f[i + 1][!j] - a[i]);
			}
		cout << f[1][1] << endl;
	}
	return 0;
}
```

---

## 作者：人间凡人 (赞：0)

### 思路：DP

首先，我们另 $dp[i][j]$ 表示在第 $i$ 个数的状态 $j$ 的答案最大值。$i$ 可以为 $1$ 到 $n,j$只能为$0$或$1$。

若 $j=0,$ 则说明当前这个状态应该减数,则从上一个的加数后的状态上减一个数，所以$dp[i][1]=max(dp[i-1][0]+a[i],dp[i-1][1]);$

若 $j=1,$ 则说明当前这个状态应该加数,则从上一个的减数后的状态上加一个数，所以$dp[i][0]=max(dp[i-1][1]-a[i],dp[i-1][0]);$

答案：因为不知道最后一步是加数还是减数，所以答案为$max(dp[n][0],dp[n][1]);$

初始状态：$dp[1][1]=a[1],dp[1][0]=0;$

$Code:$
```cpp
#include<bits/stdc++.h>
#define N 300005
using namespace std;
long long T,n,q,a[N],dp[N][2];
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&q);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		memset(dp,0,sizeof(dp));
		dp[1][1]=a[1];dp[1][0]=0;
		for(int i=2;i<=n;i++){
			dp[i][1]=max(dp[i-1][0]+a[i],dp[i-1][1]);
			dp[i][0]=max(dp[i-1][1]-a[i],dp[i-1][0]); 
		}
		cout<<max(dp[n][1],dp[n][0])<<endl;
	} 
	return 0;
}
```


---

## 作者：king_xbz (赞：0)

这题可以用DP来做，但是我的DP好像和一楼的不太一样，故发一篇题解。

# 设立状态
$f_i$是这一步做加法的最大值，$g_i$是这一步做减法的最大值，初始f数组与g数组均为-0x3f

# 边界条件
我是从2开始DP的，由于$f_i$在2这一步做加法，且第一步不能做减法，所以直接跳过第一步，又$f_i$是从$\large g_{i-1}$转移过来的，所以$g_1=0$。同理，$g_i$要在第二步做减法，那第一步必是加法。所以$\large f_1=a_1$。

# 状态转移
我们需要维护两个状态：初始化状态和更新状态

初始化状态就是每次我们把$f_i$设为$f_{1}$到$f_{i-1}$的最大值，$g_i$设为$g_{1}$到$g_{i-1}$的最大值。然后再考虑转移：

```cpp
f[i]=max(g[i-1]+a[i],f[i]),g[i]=max(f[i-1]-a[i],g[i]);
```
看能否把从g过来这步做加法和从f过来这步做减法给更新掉。然后更新此时f与g的最大值便于下一步使用。

# 代码实现
最后，上代码：
```cpp
signed main()
{
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	while(T--)
	{
		memset(f,-0x3f,sizeof(f));
		memset(g,-0x3f,sizeof(g));
		int n,q;
		cin>>n>>q;
		for(fint i=1;i<=n;i++)
		cin>>a[i];
		f[1]=a[1],g[1]=0;
		int max_f=a[1],max_g=0;
		for(fint i=2;i<=n;i++)
		{
			f[i]=max(max_f,f[i]),g[i]=max(max_g,g[i]);
			f[i]=max(g[i-1]+a[i],f[i]),g[i]=max(f[i-1]-a[i],g[i]);
			max_f=f[i],max_g=g[i];
		}
		int ans=-inf;
		for(fint i=1;i<=n;i++)
		ans=max(ans,max(f[i],g[i]));
		cout<<ans<<endl;
	}
	return 0;
}
```
祝大家AC愉快哦！

---

