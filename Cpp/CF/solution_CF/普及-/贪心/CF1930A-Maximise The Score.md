# Maximise The Score

## 题目描述

There are $ 2n $ positive integers written on a whiteboard. Being bored, you decided to play a one-player game with the numbers on the whiteboard.

You start with a score of $ 0 $ . You will increase your score by performing the following move exactly $ n $ times:

- Choose two integers $ x $ and $ y $ that are written on the whiteboard.
- Add $ \min(x,y) $ to your score.
- Erase $ x $ and $ y $ from the whiteboard.

Note that after performing the move $ n $ times, there will be no more integers written on the whiteboard.

Find the maximum final score you can achieve if you optimally perform the $ n $ moves.

## 说明/提示

In the first test case, you can only make one move. You select $ x=2 $ and $ y=3 $ , and your score will be $ \min(x,y)=2 $ .

In the second test case, the following is a sequence of moves that achieves a final score of $ 2 $ :

- In the first move, select $ x=1 $ and $ y=1 $ . Then, add $ \min(x,y)=1 $ to the score. After erasing $ x $ and $ y $ , the integers left on the whiteboard are $ 1 $ and $ 2 $ .
- In the second move, select $ x=1 $ and $ y=2 $ . Then, add $ \min(x,y)=1 $ to the score. After removing $ x $ and $ y $ , no more integers will be left on the whiteboard.

 It can be proved that it is not possible to get a score greater than $ 2 $ .In the third test case, you will perform the move thrice, adding $ 1 $ to the score each time.

## 样例 #1

### 输入

```
3
1
2 3
2
1 1 2 1
3
1 1 1 1 1 1```

### 输出

```
2
2
3```

# 题解

## 作者：Little_x_starTYJ (赞：5)

### 解题思路
本蒟蒻用贪心做的。

题目要求最大得分，因此我们肯定不能把较大数与较小数同时操作，因为这样会浪费很多分数，所以我们考虑将最小的两个数同时进行操作。

现在，题目就变成了给你一个序列，请将整个序列重新排列得到 $a_1,a_2,\cdots,a_k$，其中，序列 $a$ 满足 $a_1\leq a_2 \leq \cdots \leq a_k$，求 $\min(a_1,a_2)+ \min(a_3,a_4)+\cdots+\min(a_{k-1},a_k)$。又因为重新排列后满足递增，所以我们只需要求出 $a_1+a_3+a_5+\cdots+a_{k-1}$ 即可。

因此，对于这道题目，我们排一个序，使得序列满足递增，再统计处于奇数位的数的和即可。

CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[110];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n, ans = 0;
		cin >> n;
		n *= 2;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; i += 2)
			ans += a[i];
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：zhouchuer (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF1930A)
### 思路
这是一个很简单的贪心题，建议看完思路尝试自己写。

注意此题有 $t$ 组数据，每组输入 $n$ 以及 $2n$ 个 $a_i$，将这些数从小到大排序后，选择 $i$ 为奇数的 $a_i$，加到 $ans$ 里，最后输出，别忘了初始化。

### 代码
```c
#include<bits/stdc++.h>
using namespace std;

int n,a[105],ans;
int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		n*=2;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i+=2){
			ans+=a[i];
		}
		cout<<ans<<endl;
		ans=0;
	}
	return 0;
}
```

---

## 作者：Cold_Eyes_bystander (赞：2)

贪心题。

题目让我们每次都选出两个数，选择小的那个数加入分数，最终让分数最大。

这题看起来很简单，实际上他一点都不难。

思路如下。

- 最小的数一定会加入分数。
- 既然最小的数一定会选，那就让他变得有价值，和第二小的同归于尽。
- 前两个数被选走了，第三小的数变成了最小的，重复以上操作。

代码。

```c++
#include <bits/stdc++.h>
using namespace std;
int a[1919810];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=1;i<=2*n;i++)
        {
            cin>>a[i];
        }
        sort(a+1,a+n+1+n);
        int sum=0;
        for(int i=1;i<=n;i++)
        {
            sum+=a[i*2-1];
        }
        cout<<sum<<endl;
    }
    
    return 0;
}
```

---

## 作者：Malkin_Moonlight (赞：2)

## 题解：CF1930A Maximise The Score
## 思路
**本题为多测，注意清空**

一眼看就是贪心。

题目要求选两个数将答案加上这两个数的最小值。所以，要让答案尽可能大，可以把原数组排序，再遍历一遍，取奇数位的数的和。
## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
#define pb emplace_back
const ll MAXN = 2e5 + 5;
const ll MOD = 1e9 + 7;

ll T, n, i, j;
ll a[105];

int main()
{
	//freopen("xxx.in", "r", stdin);
	//freopen("xxx.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> T;
	while (T--)
	{
		ll ans = 0;
		cin >> n;
		for (i = 1; i <= 2 * n; i++)
		{
			cin >> a[i];
		}
		sort(a + 1, a + 2 * n + 1);
		for (i = 1; i <= 2 * n; i+=2)
		{
			ans += a[i];
		}
		cout << ans << endl;
	}
	return 0;
}

```

---

## 作者：xzz_0611 (赞：2)

[题目传送门](/problem/CF1930A)
## 思路
很明显，对于每次操作的两个数 $x$ 和 $y$，只要 $x$ 的值始终大于等于 $y$，那么不管 $x$ 怎么变化，得分都只会累加 $y$，所以想要得分尽可能大，$x$ 的取值就要尽可能地接近 $y$ 且大于等于 $y$，而对于任意一个长度为 $2\times n$ 的**升序序列** $A$，大于等于 $A_i$ 且最接近 $A_i$ 的值就为 $A_{i+1}$，所以这 $n$ 次操作得分最大为：
$$\sum_{i=1}^{n}\min(A_{i\times2-1},A_{i\times2})$$
而由于 $A$ 是一个升序序列，所以 $A_{i\times2-1}$ 肯定小于等于 $A_{i\times2}$，所以可以将式子化简成：
$$\sum_{i=1}^{n}A_{i\times2-1}$$
故只需要将 $a$ 进行升序排序，再按照如上计算方式进行计算即可。
## Code
核心代码：
```cpp
while(t--) {
	cin>>n,ans=0;
	for(int i=1;i<=2*n;++i) cin>>arr[i];
	sort(arr+1,arr+1+n*2);//排序
	for(int i=1;i<=n;++i) ans+=arr[i*2-1];//套入公式
}
```
时间复杂度 $\mathcal O(\sum n)$。

---

## 作者：BJqxszx_zhuyukun (赞：1)

# 写在前面
---
这是本蒟蒻第 $3$ 次发题解，如果写的很差或者码风很烂请谅解。

# 思路
---
既然是加上最小值，那么很显然，让最大数和最小数相加是最亏的。而让两个差不多的比较小的数相加是比较值的，因为这样做损失会更小一些。\
所以，我们可以考虑贪心，每次都用最小的两个数执行操作。\
想到了这里，这题就迎刃而解了。
# 代码
---
本题唯一的坑点似乎就是有 $2n$ 个数，所以数组要开 $2$ 倍才能过（别问我怎么知道的）。\
AC code:
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int t,n,ans;
int a[105];//注意：有 2n 个数，所以要开到 100
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		n<<=1;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+1+n);//贪心求解
		for(int i=1;i<=n;i+=2) ans+=a[i];
		cout<<ans<<'\n';
		ans=0;
	}
	return 0;
}
```

---

## 作者：_Deer_Peach_ (赞：1)

又可以写题解了，~~赶紧来水一波~~。

思路：明显而又简单的贪心题，贪心只要贪小的数就好了，将数组从小到大排序，再用循环两个两个的遍历，每次遍历第一个数就是每次操作的得分，建一个记录答案的变量累加即可。思路和代码都很简单。

代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
signed main(){
	cin>>t;
	while(t--){//注意多组数据哦
		int n,ans=0;
		cin>>n;
		n=n*2;//数组长度是2n，并不是n
		int a[n];
		for(int i=0;i<n;i++)cin>>a[i];//输入
		sort(a,a+n);
		for(int i=0;i<n;i+=2){
			ans+=a[i];//循环遍历
		}cout<<ans<<endl;//注意换行
	}
	return 0;
}
```

---

## 作者：_zqh_ (赞：1)

### Solution

贪心。

显然，在数列最大值唯一的情况下最大值一定不会被累加到答案里，其一定会被比它小的数冲掉。

不妨用次大（不严格）与最大取最小值，这样的损失最小。

剩下 $2 \times n - 2$ 个数用类似的思路取完即可。

故，对于给定的数组 $A$，答案为：
$$
\sum_{i=1}^{n}B_{2\times i-1}
$$

其中 $B$ 数组代表排序后的 $A$ 数组；

### Code

你在期待什么？

[code](https://codeforces.com/contest/1930/submission/265165711)。

码风奇丑，请见谅。

---

## 作者：ACtheQ (赞：1)

本题能一眼看出是个贪心。

题目要求选出两个数将答案增加两数的最小值。

易发现，假如想让答案最大，就让选的两数越接近越好。这样呢不会让大的数浪费掉。

所以对原数组排序。

每次让最小的两个数操作。可以发现每次操作的数为排序后下标为奇数位的数的和。

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=55;
int a[N]; 
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		n<<=1;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+n+1);
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(i&1) ans+=a[i]; 
		}
		cout<<ans<<endl; 
	}
	return 0;
}
```

---

## 作者：xcms (赞：1)

# CF1930A Maximise The Score
先把这个数组排序。为了让 $a_i$ 不影响后面更大的数，我们需要让 $a_{2i-1}$ 与 $a_{2i}$ 求最小值。

拿样例分析：$1$ $1$ $2$ $1$ 排完序后变成 $1$ $1$ $1$ $2$。然后 $1$ 与 $1$ 求最小值得到 $1$，$1$ 与 $2$ 求最小值得到 $1$，$1 + 1=2$。可以发现，这道题就是求 $i$ 为奇数的 $a_i$ 的和。

## std
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1000005];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,ans=0;
		cin>>n;
		for(int i=1;i<=n*2;i++)cin>>a[i];
		sort(a+1,a+1+n*2);//排序（非常重要）
		for(int i=1;i<n*2;i+=2)ans+=a[i];//求所有下标是奇数的a[i]的和
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：qusia_MC (赞：0)

很水的题。

## 分析
对 $2n$ 个数进行 $n$ 次操作，每次选出两个数 $i,j$，满足 $\forall i,j$ 均不相等。

对于每次操作，得分为 $\min(a_i,a_j)$，记为 $k$ 数组，求 $\sum^n_{i=1}k_i$。

## 思路
很容易想到，每次得分只与最小值有关。所以想到尽量让 $\left|a_i-a_j\right|$ 尽可能小。也就是让 $a_i,a_j$ 尽量接近。

为什么呢，因为：若 $a_i$ 很小，那么即便 $a_j$ 再大也没用。所以就消耗掉尽量小的 $a_j$，让大的留到后面再用。

不难想到，我们可以给 $a_1\sim a_{2n}$ 排个序，这样只要求出 $\sum^{n}_{i=1} a_{2\times i-1}$。

## CODE

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int T,n,a[114514],ans=0;
    cin>>T;
    while(T--)
    {
        cin>>n;
        ans=0;//别忘了清零！！！！！！
        for(int i=1;i<=2*n;i++)
        {
             cin>>a[i];
        }
        sort(a+1,a+2*n+1);//排序
        for(int i=1;i<=2*n;i+=2)
        {
            ans+=a[i];//累加
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：LookatSea (赞：0)

思路：直接贪心即可。

此题较为简单，建议自己写代码。

输入 $T$ 组数据，每组数据输入一个 $n$ 和 $n\times2$ 个 $a_i$ 然后排序，选第一小的与第二小的数去最小值，然后第三小的就会变为第二小的，以此类推得到最大值。

---

## 作者：Ice_rnfmabj (赞：0)

### 题目大意

给定 $2n$ 个正整数，初始得分为 $0$，对其进行 $n$ 次操作。每次操作选择两个数，加上这两个数中较小的数，求：最大的总和是多少。

### 思路

为了不浪费一些较大的数，我们就必须使选出的两个数的差最小。这自然而然会令人想到亲爱的 ```sort```。

使用快排将数列排好序，然后加上奇数位上的值就行了（因为排序好后显然奇数位上的数字更小，不信你随便找组数据试试）。

代码部分：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,ans;
int main(){
	cin>>t;
	while(t--){
		int n,a[101];
		cin>>n;//输入，别忘了要读入 2n 个数据！
		n=n*2;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+1+n);//排序
		for (int i=1;i<=n;i+=2) ans+=a[i];//加上奇数位的数
    	cout<<ans<<"\n";//输出
    	ans=0;//ans 需要归0
	}
    return 0;
}
```

---

## 作者：__bjxx0201__ (赞：0)

## 题面意思

给定 $2 \times n$ 个数，每次策略性选取两个数，总和需要加上这两个数中较小的那个数，请求出最大的总和是多少。

## 思路

[题目传送门](https://www.luogu.com.cn/problem/CF1930A)

考虑到贪心的做法。

我们先用快排 `sort` 升序排序，这样可以找出两个数之间较小的数，也可以使得总和最大。然后，排完序之后，我们只需要将总和加上奇数位上的数字，因为是相邻两个数字做对比，奇数位上的数字小，所以才加奇数位上的数字。

参考代码：

```
#include <bits/stdc++.h>
using namespace std;
int t; 
int main() {
    cin>>t;
    while (t--) {
    	int a[200],ans=0,n;
    	cin>>n;
    	n*=2;//数列长度干脆直接更新，这样可以使下面的操作简单一点。
    	for (int i=1;i<=n;i++) cin>>a[i];
    	sort (a+1,a+1+n);//排序，从小到大排序。
    	for (int i=1;i<=n;i+=2) ans+=a[i];//累加值。
    	cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：天使宝贝 (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/CF1930A)

### 题目简述

给定 $2n$ 个数，每次选取两个数进行操作，每次操作给得分加上这两个数的最小值，求最后答案的最大得分。

### 思路&分析

很明显的贪心。

可以现对这些数进行升序排序，这样即可发现，第 $a_{2i - 1}$ 永远比第 $a_{2i}$ 个数小，这样就将问题转换成了求这些数升序排列后奇数位置的数的总和，于是就能愉快的解决本题啦！

### CODE
```cpp
#include <bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
int T, n, a[105], ans;
int main()
{
    IOS;    // 读入加速
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i = 1; i <= 2 * n; i++)
            cin >> a[i];
        ans = 0;
        sort (a + 1, a + 2 * n + 1);    // 排序
        for (int i = 1; i <= 2 * n; i += 2)
            ans += a[i];    // 对奇数位置求和
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：GoodLuckCat (赞：0)

### CF1930A 题解

这道题要每次选择两个数，将总和加上这两个数中的最小值，求最大的总和。

先来看一个例子：

```
1
3
1 100000 2 2 99999 5
```

如果这时选择了 $1$ 和 $2$，就会发现不会浪费很多。但是如果选择 $1$ 和 $100000$，最小值当然是 $1$，$100000$ 就浪费掉了。所以要先将这个数组排序，然后选取相邻两项进行操作，才可以使得最终的得分最大。加上去的时候，要注意要将 **所有的奇数项** 加上去，才是最终结果。

Code:

```cpp
#include<algorithm>
#include<iostream>
using namespace std;
int a[101];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,s=0;
        cin>>n;
        for(int i=1;i<=2*n;i++)cin>>a[i];
        sort(a+1,a+2*n+1);
        for(int i=1;i<=2*n;i+=2)s+=a[i];
        cout<<s<<endl;
    }
    return 0;
}
```

---

## 作者：xujingyu (赞：0)

本题，怎么说，dfs 勉强还行，dp 也可以，反正 $n\leq50$。

这里提供一个 dp 做法。因为输入有 $2n$ 个数，那就不妨先把 $n\times2$。

把 $a$ 数组从小到大排序，两个为一组。设 $dp_j$ 表示至第 $j$ 组的最大答案（所以 $j\leq\dfrac{n}{2}$）。

转移方程为 $dp_j=\min(a_i,a_{i+1})+dp_{j-1}$，其中 $i\leq n$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n,a[101],dp[101];

signed main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		n *= 2;//先乘二
		for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
		sort(a + 1,a + n + 1);//排序
		for(int i = 1,j = 1;i <= n;i += 2,j++) dp[j] = min(a[i],a[i + 1]) + dp[j - 1];//转移
		printf("%d\n",dp[n / 2]);//注意要除以二
	}
	return 0;
}
```

---

