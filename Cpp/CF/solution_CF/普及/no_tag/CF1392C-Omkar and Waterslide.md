# Omkar and Waterslide

## 题目描述

Omkar is building a waterslide in his water park, and he needs your help to ensure that he does it as efficiently as possible.

Omkar currently has $ n $ supports arranged in a line, the $ i $ -th of which has height $ a_i $ . Omkar wants to build his waterslide from the right to the left, so his supports must be nondecreasing in height in order to support the waterslide. In $ 1 $ operation, Omkar can do the following: take any contiguous subsegment of supports which is nondecreasing by heights and add $ 1 $ to each of their heights.

Help Omkar find the minimum number of operations he needs to perform to make his supports able to support his waterslide!

An array $ b $ is a subsegment of an array $ c $ if $ b $ can be obtained from $ c $ by deletion of several (possibly zero or all) elements from the beginning and several (possibly zero or all) elements from the end.

An array $ b_1, b_2, \dots, b_n $ is called nondecreasing if $ b_i\le b_{i+1} $ for every $ i $ from $ 1 $ to $ n-1 $ .

## 说明/提示

The subarray with which Omkar performs the operation is bolded.

In the first test case:

- First operation:
  
   $ [5, 3, \textbf{2}, 5] \to [5, 3, \textbf{3}, 5] $
- Second operation:
  
   $ [5, \textbf{3}, \textbf{3}, 5] \to [5, \textbf{4},           \textbf{4}, 5] $
- Third operation:
  
   $ [5, \textbf{4}, \textbf{4}, 5] \to [5, \textbf{5},           \textbf{5}, 5] $

In the third test case, the array is already nondecreasing, so Omkar does $ 0 $ operations.

## 样例 #1

### 输入

```
3
4
5 3 2 5
5
1 2 3 5 3
3
1 1 1```

### 输出

```
3
2
0```

# 题解

## 作者：Lynkcat (赞：3)

我们随便画一组数据出来，一切都非常明了了：

| 1 |  |  |  |  |  |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 1 |  |  | 1 |  |  1|
| 1 | 1 |  | 1 |  | 1 |
| 1 | 1 |1  | 1 |1  |  1|
|1  | 1 | 1 | 1 |1  | 1 |

我们发现第三行有两个空缺部分，第二行也有两个空缺部分，第一行有一个空缺部分，所以答案就是5。

也就是说，答案就是每行的空缺区间个数之和。

那么我们可以发现，如果 $a_i<a_{i-1}$ ，那么在 $i$ 与 $i-1$ 时间会多出 $a_{i-1}-a_i$ 个空缺部分。

那么这题就这么解决了。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,T,ans,a[300000];
signed main()
{
	cin>>T;
	while (T--)
	{
		cin>>n;ans=0;
		for (int i=1;i<=n;i++) cin>>a[i];
		for (int i=1;i<=n;i++) if (a[i]<a[i-1]) ans+=a[i-1]-a[i];
		cout<<ans<<endl;
	}
}
```



---

## 作者：封禁用户 (赞：1)

## 题目描述

[Omkar and Waterslide](https://www.luogu.com.cn/problem/CF1392C)

## 算法思路

看到范围 $1 \le n \le 2 \times 10^5$ 就可以想到不能用模拟。

所以用**贪心**：

我们从后往前看。假设第 $i+1$ 到 $n$ 已经非严格单调递增了。如果第 $i$ 个数比第 $i+1$ 个数小，那么它已经有序了，跳过。不然，我们就需要将第 $i+1$ 到 $n$ 一起不断增加直到使第 $i$  到 $n$ 有序。

### 样例解释

样例如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/29k5b4eg.png)

红色方格有 $3$ 个，所以答案输出 $3$。 

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long 
const ll N=200010;
ll t,n,a[N],ans;//ans表示答案 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//输入输出优化 
	cin>>t;//t组数据 
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		ans=0;
		for(int i=2;i<=n;i++)
		{
			if(a[i-1]>a[i])//如果有空缺部分 
			{
				ans+=a[i-1]-a[i];//答案加上 
			}
		}
		cout<<ans<<"\n";//输出答案 
	}
	return 0;
}
```

---

## 作者：Chinese_zjc_ (赞：1)

贪心题.

对于每个 $a_i$ ( $1<i\leq n$ ),肯定要提高得尽量少,而又要满足 $a_{i-1}\leq a_i$ ,因此如果 $a_{i-1}>a_i$ ,肯定要让 $a_i$ 提高 $a_{i-1}-a_i$ 的高度,否则就不用提高.

继续贪心,如果说 $a_{i-1}$ ( $2<i\leq n$ )要提高 $a_{i-2}-a_{i-1}$ 格, $a_{i}$ 要提高 $a_{i-2}-a_i$ 格,那么在提高 $a_{i-1}$ 的时候肯定也可以顺带着提高 $a_i$ ,那这样剩下只要提高 $a_{i-1}-a_i$ 即可了.

以此类推,我们就能得到最终答案:
$$
\sum_{i=2}^n\max\{0,a_{i-1}-a_i\}
$$
直接 $O(n)$ 扫一遍即可 $AC$ .

$Code$:

```cpp
//This Code was made by Chinese_zjc_.
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<bitset>
#include<cmath>
#include<queue>
#include<stack>
#include<string>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<map>
#include<set>
#include<time.h>
// #include<windows.h>
#define int long long
#define PI 3.14159265358979323
#define INF 0x3fffffffffffffff
using namespace std;
int n,t,a[200005],ans;
signed main()
{
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--)
    {
        cin>>n;
        ans=0;
        for(int i=1;i<=n;++i)
        {
            cin>>a[i];
            ans+=max(0ll,a[i-1]-a[i]);
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

最后,这题是三倍经验…

另外两题的链接:

[P1969 积木大赛](https://www.luogu.com.cn/problem/P1969)

[P5019 铺设道路](https://www.luogu.com.cn/problem/P5019)

(代码需要略微改动)

---

## 作者：_rxfalty_ (赞：0)

## [题意](https://www.luogu.com.cn/problem/CF1392C)
[题目来源](https://codeforces.com/problemset/problem/1392/C)

给定一个分成 $n$ 段的滑道中每一段的高度，你可以选择一段不下降的区间，将区间内的滑道高度 $+1$，求出至少要多少次操作才能使滑道的高度形成一个不下降的数列。（有多组数据）
### 数据范围
$1 \le t \le 100$，$1 \le n \le 2 \times 10^5$，$0 \le a_i \le 10^9$。

## 算法思路
看到范围 $1 \le n \le 2 \times 10^5$ 
就可以想到不能用模拟。

所以用贪心：

题目要求对这个序列进行操作，使这个序列变成非递减数列。

对于每个 $a_i$，如果 $a_i < a_{i-1}$，那么 $ans$ 加上 $a_{i-1}-a_i$，否则啥也不干。

时间复杂度：$O(n \cdot t)$

## 代码
```c++
#include<iostream>
using namespace std;
long long t,n,ans,a[200005];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		ans=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			ans=ans+max(0ll,a[i-1]-a[i]);//ll后缀：把这个数转换成long long类型 
		}
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：naroto2022 (赞：0)

# CF1392C题解
### 分析
根据题意可得：设任意一个一个正整数 $i$（$n\geq i$）要是 $a[i]<a[i-1]$ 则这两个数至少需要操作 $a[i-1]-a[i]$ 次。

换一句话说，每组数据的答案为所有前一个数大于后一个数的前一个数减后一个数。（就是上面的字母表示）

### 话不多说，上代码！！！

```cpp
#include<bits/stdc++.h>
#define ll long long//懒人必备
using namespace std;
ll n,T,ans,a[300005];
int main(){
	cin>>T;//T组数据
	while(T--){//循环输入T组数据
		cin>>n;
		ans=0;//每组数据的答案清零
		for(ll i=1; i<=n; i++) cin>>a[i];
		for(ll i=1; i<=n; i++) if(a[i]<a[i-1]) ans+=a[i-1]-a[i];//如果后一个小于前一个，则要多做（前一个减后一个的差）次
		cout<<ans<<endl;
	}
	return 0;//养成好习惯
}
//完结撒花✿✿ヽ(°▽°)ノ✿
```

---

## 作者：xyta (赞：0)

这道题其实代码并不难，只要想清楚就可以。

而我们采用的是贪心的思想，在成功的情况下使方法最优。

我们拿第样例的第一组来说：

我们根据不存在下降子序列的规则来看，目前有两个区间不符合要求（可以理解为两个连续的数据之间的差为下降），分别是 $ a_1$ 和 $a_2$ 以及 $a_2$ 和 $a_3$ 。

所以我们需要把不符合的数据 +1 ,并且可以发现，不符合的两个区间是相邻的，而相邻的就可以一起 +1 ,这样就是最优策略。

然后第二个和第三个一块加了 2 。接着第三个又加了 1 。所以答案就是 3 。

思路就是这样，接下来讲代码如何书写。

我们只需要一个循环来从前往后循环，每循环到一个点就只需要求他单独 +1 数量，也就是他前一个数比他多了几。他不需要考虑前面的情况，因为如果前面不符合，他前面的数就会带着她一起上升，这就是最优方案。

注意：算完了他需要加几后不能改变原数组，否则就不是最优策略了。

具体代码及简介注释如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
long long a[200010];//数据数组 
int main()
{
	cin>>t;//输入数据组数量 
	while(t--)//多组数据循环 
	{
		cin>>n;//输入序列长度 
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];//逐个输入每组数据 
		}
		long long ans=0;//定义ans来存储需要多少个“+1” 
		for(int i=2;i<=n;i++)//从第二个开始循环，因为第一个没有前面，及肯定满足要求 
		{
			if(a[i]<a[i-1]) ans+=a[i-1]-a[i];//如果不符合要求 ans 加上a[i-1]-a[i]即可。 
		}
		cout<<ans<<endl;//最后输出答案，别忘了换行（因为是多组数据） 
	}
	return 0;//完毕撒花 
}
```
最后 AC 记录：

[带注释提交记录](https://www.luogu.com.cn/record/73338931)

喊出我们的口号：~~点赞，关注，评论！~~ 珍爱生命，远离抄解！

---

## 作者：leoair (赞：0)

### 题意：
给定一个长度为 $n$ 的序列 $a$，你每次可以进行一次操作，将一个不下降的区间 $[l,r]$ 之间的数都加 $1$。求经过多少次操作后可以将整个序列变为不下降的序列。

### 分析：
首先，由于每次操作只能对不下降的序列进行操作。因此，我们先处理出所有的不下降序列，并存入队列 $q$ 中，记为 $q_1,q_2,q_3,\dots,q_{cnt-1},q_{cnt}$。
显然，将第 $i$ 个不下降序列和第 $i+1$ 个不下降序列合并成一个不下降序列，当且仅当 $q_i$ 的最后一个元素不大于 $q_{i+1}$ 的第一个元素。
因此，我们只需将第 $cnt$ 个序列与第 $cnt-1$个序列合并，然后与第 $cnt-2$ 个序列合并，然后和第 $cnt-3$ 个序列合并，$\dots\dots$，最后与第 $1$ 个序列合并。
易得：答案为前一个序列的最后一个值与后一个序列的第一个值的差。

### Code：
```cpp
/*
user:leoair
time:2022.3.24
*/
#include <bits/stdc++.h>
#define int long long
#define N 200010
using namespace std;

int a[N];

inline int read(){
    int s = 0, w = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; w *= ch == '-' ? -1 : 1, ch = getchar());
    for (; ch >= '0' && ch <= '9'; s = s * 10 + ch - '0', ch = getchar());
    return s * w;
}

signed main(){
    for (int _ = read(), n, cnt, ans; _--; ){
        n = read(), cnt = ans = 0;
        queue < int > q[n];
        a[1] = read(), q[1].push(1);
        for (int i = 2; i <= n; ++i){
            a[i] = read();
            if (a[i] >= a[i - 1]) q[cnt].push(i);
            else q[++cnt].push(i), ans += a[i - 1] - a[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：aakennes (赞：0)

难道没人看出来这是 $noip2018$ 的 $D1T1$ 么，一膜一样，还特意去看了一眼

三倍经验（P5019 P1969）

贪心： 
$$ans=\sum_{i=2}^n max(0,a_{i-1}-a_i)$$

证明：

* $a_{i-1}<=a_i$ 不用管，增加反而会答案增加

* $a_{i-1}>a_i$ 直接拔高 $i$ 及 $i$ 以后的所有数，使此后每次被拔高的代价一定不大于相邻两数之差

```
		cin>>n;ans=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(i>1&&a[i]<a[i-1])ans+=a[i-1]-a[i];
		}
		cout<<ans<<endl;
```

---

## 作者：dead_X (赞：0)

## 题意
给定一个序列，定义一次操作为将一段数全部加 $1$ ，问将序列变为非严格递增的最小次数。
## 思路
Tags：贪心

我们从右往左看。假设第 $(i+1) \to n$ 个数已经非严格递增了。如果第 $i$ 个数比第 $(i+1)$ 个数小，那么它已经有序了，跳过。不然，我们就需要将第 $(i+1) \to n$ 个数一起不断增加直到使第 $i\to n$ 个数有序。

贪心的正确性：我们差分一下数组，每一次区间加最多只能让差分数组中的一个数增大 $1$ ，得证。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1000003]; 
int main()
{
	int T=read();
	while(T--)
	{
		int n=read();
		for(int i=1; i<=n; i++) a[i]=read();
		long long ans=0;
		for(int i=n; i>1; i--) ans+=max(a[i-1]-a[i],0);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：zhzzhzzzz (赞：0)

C题算是偏简单的了，但是考场脑抽不知道在搞什么。。。

### 题目大意：

给定一个长度为 $n$ 的序列，每次操作可以选择一段区间，将区间中的每个数都 $+1$ ，求使序列变为单调不下降序列的最少次数。多组测试数据。


有一个奇怪的思路：从右往左枚举 $i$ ，如果  $a_i<a_{i-1}$，就将 $ans$ 加上两数的差值，这样一来如果枚举 $i$ 到了中间出现了逆序对，由于 $i$ 右边的数我们已经搞定了，所以我们可以把从 $i$ 往后的所有数都 $+1$ ，答案不变，仍然是逆序对差值的和，用式子表示就是：

$$ans=\sum_{i=n}^2 \{a_i<a_{i-1}\}(a_{i-1}-a_i)$$

代码挺简单的，不写注释了= =

开 $long\space long$ ！！！

$Code:$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int       a[N];
signed    main()
{
    int T;
    scanf("%lld", &T);
    while (T--) {
        int n;
        scanf("%lld", &n);
        int ans = 0;
        for (int i = 1; i <= n; i++)
            scanf("%lld", &a[i]);
        for (int i = n; i > 1; i--) {
            if (a[i] < a[i - 1])
                ans += a[i - 1] - a[i];
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

