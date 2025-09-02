# ソーシャルゲーム

## 题目描述

[problemUrl]: https://atcoder.jp/contests/donuts-live2014/tasks/donuts_live2014_3

ソーシャルゲームを運営するためには、日々のユーザ数の増減を観察することが欠かせません。

ゲーム会社を運営しているパンチくんは、最もユーザが増加した期間に、何人ユーザが増加したかを調べようとしています。

日々のユーザの増減数 $ a_1,\ a_2,\ …,\ a_N $ が与えられるので、ユーザ数の増減数が最大となる期間のユーザの増減数を求めて下さい。

## 说明/提示

### 部分点

$ 1\ ≦\ N\ ≦\ 3000 $ を満たすテストケースに正解した場合、部分点として $ 40 $ 点が与えられる。

### Sample Explanation 1

$ 3 $ 日目から $ 6 $ 日目までの、 $ (2,\ 3,\ -1,\ 2) $ の増加数 $ 6 $ が最大です。

### Sample Explanation 2

全期間が、ユーザの増減数が最大となる期間となります。

### Sample Explanation 3

出力はマイナスとなることがあります。 出力対象となる期間は $ 1 $ 日以上であることに注意して下さい。

## 样例 #1

### 输入

```
7
3 -4 2 3 -1 2 -1```

### 输出

```
6```

## 样例 #2

### 输入

```
3
10 20 30```

### 输出

```
60```

## 样例 #3

### 输入

```
3
-4 -2 -5```

### 输出

```
-2```

# 题解

## 作者：David_yang (赞：4)

**[题目传送门](https://www.luogu.com.cn/problem/AT_donuts_live2014_3)**

第一篇题解，如有不妥请~~忽视~~指出。

这道题用了一个小小的 dp。

dp 的思想就是选这个数还是不选这个数。

而这道题的思想就是选这个区间还是不选这个区间。

先把状态转移方程摆出来：$f=\max(f+a,a)$。

其中 $f+a$ 就是接着用原来的区间，$a$ 就是另一个新的区间。

这方程是我遇到的最简单的转移方程了……

这道题不能说和 P1115 很相似，是一模一样（这就意味着两题的代码一样，尽管我 UKE 了……）。

### code 来了：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,f,ans=-10005;//要初始化为最小值哟！
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&a);
		f=max(f+a,a);//选还是不选，这是一个值得思考的问题......
		ans=max(f,ans);//汇总
	}
	printf("%d",ans);
	return 0;
}
```
注：13:50:45，我 AC 了，所以此代码可放心食用。

---

## 作者：Hughpig (赞：2)

双倍经验：[P1115](https://www.luogu.com.cn/problem/P1115)。

我们记 $f_i$ 为以 $a$ 前 $i$ 个数的非空最大子段和。

显然，$f_1=a_1$（只有 $1$ 个数，只能选它）。

对于第 $i$ 个数，$f_i$ 有两种选择：

1. 在前 $i-1$ 个数的最大子段和的基础上加上 $a_i$，设为 $f_{i-1}+a_i$。

2. 不管前 $i-1$ 个数的最大子段和，新开一段设为 $a_i$。

两者之间取最大值即可，即 $f_i=\max(f_{i-1}+a_i,a_i)$。

然后由于答案要取最大值，所以找出 $f$ 中的最大值即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],f[100005],mx,n;//mx 记录最大值
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	f[1]=mx=a[1];//初始 f1 和最大值都设为 a1
	for(int i=2;i<=n;i++)
	{
		f[i]=max(f[i-1]+a[i],a[i]);//计算以 i 结尾的最大子段和
		mx=max(mx,f[i]);//答案要取最大值
	}
	cout<<mx<<'\n';
	return 0;
}
```

---

## 作者：qi__ (赞：1)

## AT_donuts_live2014_3
一眼看出来是 dp。

直接列出转移方程：
$$
dp_{i}=\max(a_{i},dp_{i-1}+a_{i})
$$

其中：

1. $dp_{i}$ 表示 $a_{1}$ 到 $a_{i}$ 非空最大子段和。
2. $a_{i}$ 不解释。

最后

$$
ans=\max(dp_{i})
$$

代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000005;
int n,a[MAXN],dp[MAXN],sum=-114514;//可能是负数，不能设-1
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		dp[i]=max(a[i],dp[i-1]+a[i]);
		sum=max(dp[i],sum);
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：mayike (赞：1)

### 题意：


------------

求给定序列的非空最大子段和。


------------

### 思路：
------------
我们可以记 $p$ 为进行到 $a_i$ 的最大子段和，$m$ 是总体的最大子段和，用 $p$ 不断地去更新 $m$ 即可。

因此有 $p=\max(a_i+p,a_i)$，$m=\max(m,p)$。

为什么呢？因为若 $a_i+p<a_i$，那不如不选前面，换一个序列，
反之序列末新加了 $a_i$，$p$ 变大了。

最后循环结束，输出 $m$ 就可以啦。

上代码：
```
#include<bits/stdc++.h>
using namespace std;
int a[200005],p,n,m=-1e9;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        p=max(p+a[i],a[i]);
        m=max(m,p);
    }cout<<m<<'\n';
	return 0;
}
```

---

## 作者：Vocaloid_Paranoia (赞：1)

# 题意

求 $N$ 个数 $a_1a_2\dots a_N$ 中的非空最大子段和。

# 思路

是一道很经典的题，可以用 dp 解决。

设 $dp_i$ 为前 $a_i$ 个数的最大子段和。

**加入 $a_i$ 时，$dp_i$ 有两种选择：**

- 累加到之前的最大子段和上，也就是 $dp_i=dp_{i-1}+a_i$；

- 或是直接记 $a_i$ 为最大子段和，也就是 $dp_i=a_i$。

状态转移方程： 
$dp_i=\max(dp_{i-1}+a_i,a_i)$。

最后找出 $dp$ 数组中最大的即可。

# 注意
 
- 对于 $N=1$ 的情况，直接输出唯一的 $a$ 即可，否则要把 $dp_0$ 赋值为 $a_0$，道理同

  >记 $a_i$ 为最大子段和，也就是 $dp_i=a_i$。

- At 的题记得换行。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int N,a[100005],dp[100005],ans;
int main(){
	cin>>N;
	for(int i=0;i<N;i++)
		cin>>a[i];
	if(N==1){//特判
		cout<<a[0];
		return 0;
	}
	dp[0]=ans=a[0];
	for(int i=1;i<N;i++){
		dp[i]=max(dp[i-1]+a[i],a[i]);//计算dp[i]
		ans=max(dp[i],ans);//答案
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# AT_donuts_live2014_3 ソーシャルゲーム 题解

## 题目大意

[题目传送门](https://www.luogu.com.cn/problem/AT_donuts_live2014_3)

给你一个序列，求给定序列 $a$ 的非空最大子段和。

## 思路

- 定义 $ans$ 表示答案， $sum$ 表示包含 $a_i$ 的最大字段和。

- 可以使用贪心求解 $sum$ ，因为只要 $sum \neq 0$ 那么就可以让后面的字段大小更大，因为当 $a>0$ 时，显然可以推出 $a+b>b$ ，所以可以得出这种方法是可行的。

- 因为要求非空，所以还需要定义 $flag$ 记录 $a_i$ 是否全部为负数， $maxx$ 记录最大的 $a_i$。

## code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define re register
#define endl '\n'

const int maxn=1e5+1;
int n,a[maxn],ans,sum,maxx=-1e18;
bool flag=true;

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",a+i);
		if(a[i]>=0)
		{
			flag=false; //记录 a[i] 是否为负数 
		}
		maxx=max(maxx,a[i]); //记录最大的 a[i] 方便后面为负数时输出 
		sum+=a[i];
		ans=max(ans,sum);
		sum=max((int)0,sum);
	}
	if(flag)
	{
		printf("%lld\n",maxx);
		return 0;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：xigou1834 (赞：0)

本题目可以用动态规划来做。

状态：$dp[i]$ 表示以第 $i$ 个数结尾的最大子段和。

状态转移方程：$dp[i] = \max(dp[i-1]+x,x)$。

正确代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	const int N = 1e6 + 5;
	int x , dp[N] = {0} , maxi = -1e9 , n;
	cin>>n;
	for(int i = 1;i<=n;i++){
		cin >> x;
		dp[i] = max(dp[i-1]+x,x);
		maxi = max(maxi,dp[i]);
	}
	cout<<maxi;
	return 0;
}
```

---

## 作者：Teto_etf (赞：0)

非空最大子段和板子。

考虑如何能够通过动态规划“遍历”每一种可能的情况。容易想到对于一个 $a_i$，如果它不是一个子段的开头，那它就在子段的中间或结尾——换句话说，只能从 $a_i$ 开始新开一个子段，或者把它加到前面的子段后面。

对于每个 $i ∈ \{1,  2,\cdots, n-1, n\}$，将上面两种状态取最大值，并开一个计数器，用擂台法记录每一个状态的最大值，将最大值输出即可。形式化地来说，状态转移方程如下：

$$dp_i=\max(dp_{i-1}+a_i, a_i)$$

而最终结果的值则为：

$$S=\max(dp_1,dp_2,\cdots,dp_{n-1},dp_n)$$

```cpp
#include <bits/stdc++.h>
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
using namespace std;

const int maxn = 2e5 + 10;
int n, maxx = INT_MIN;
int a[maxn], dp[maxn];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        dp[i] = a[i]; // 先赋值
    }
    for (int i = 1; i <= n; i++) dp[i] = max(dp[i], dp[i - 1] + a[i]), maxx = max(maxx, dp[i]);
    cout << maxx << endl;
    return 0;
}
```

---

## 作者：Igallta (赞：0)

这题的题意已经非常清楚了，不再赘述。

求的是 “最大非空子段和”,那么我们一下就可以想到 dp。

$dp_i$ 存在两种选择。

1. 在前面 $i-1$ 个数的最大子段的基础上加上 $a_i$。

2. 前面怎么我都不管，直接新开一个设为 $a_i$。

对这两种情况取最大值即可。

顺带需要找出 $dp_i$ 的最大值才输出。 


献上丑陋的代码：


```cpp
/****************************************
作者:
版权:
日期:
*****************************************/
#include<bits/stdc++.h>
using namespace std;
int n,a[200001],ans[200001],sum=-2147483640; 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		ans[i]=a[i];//初始 
		ans[i]=max(ans[i-1]+a[i],a[i]);//dp
		sum=max(sum,ans[i]);//看最大子段 
	}
	cout<<sum<<'\n';//记得加'\n'！！！（撕心裂肺）
	return 0;//完结撒花
}
```

---

## 作者：smydahaoren (赞：0)

### **题目描述**：

这是一道最大子段和，和 P1115 除了数据范围不一样就没什么了。

### **思路分析**：

输入 $n$ 个数，每次输入 $a_i$。

用动态规划做，用 $dp_i$ 来储存到 $a_i$ 位置的最大子段和，每次对于 $dp_i$ 可以选择从 $dp_{i-1}$ 加上 $a_i$，如果 $dp_{i-1}<0$ 那么 $dp_i$ 就可以直接取 $a_i$ 使得到当前数字的子段和最大。

所以 $dp_i=\max(a_i,dp_{i-1}+a_i)$。

最后在 $dp$ 数组中选取最大值作为答案。（如果是通过设置一个初值然后通过比较取得最大值的方法注意将初值设置的小一点）

### **AC 代码**：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000009;
int n,a[N],dp[N],sum=-99999;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){//注意这里从1开始循环，不然会RE
		cin>>a[i];
		dp[i]=max(a[i],dp[i-1]+a[i]);
		sum=max(dp[i],sum);
	}
	cout<<sum;
	return 0;
}
```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_donuts_live2014_3)     
这么典一道题没人切。    
## 题意
求给定序列 $a$ 的非空最大子段和。    
## 解法
最大子段和显然可以用 dp 解决。    
我们设 $f_i$ 为算入 $a_i$ 且以它结束的最大子段和。    
那么显然 $f_i$ 可以不取前面的，单独算上 $a_i$，也可以累加到之前的最大子段和上，即 $f_{i-1}+a_i$。     
那么 $f_i=\max(a_i,f_{i-1}+a_i)$。     
结果为 $\max\limits_{i=1}^{n}f_i$。   
我们可以优化这个过程：发现 $f$ 都只用到了它前面的状态，所以我们用一个变量来动态维护就可以了。      
空间复杂度降到了 $O(1)$，时间复杂度 $O(n)$，可以通过。    
[CODE](https://atcoder.jp/contests/donuts-live2014/submissions/44687101)

---

