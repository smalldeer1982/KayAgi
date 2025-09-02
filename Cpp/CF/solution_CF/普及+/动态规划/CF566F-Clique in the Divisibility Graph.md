# Clique in the Divisibility Graph

## 题目描述

As you must know, the maximum clique problem in an arbitrary graph is $ NP $ -hard. Nevertheless, for some graphs of specific kinds it can be solved effectively.

Just in case, let us remind you that a clique in a non-directed graph is a subset of the vertices of a graph, such that any two vertices of this subset are connected by an edge. In particular, an empty set of vertexes and a set consisting of a single vertex, are cliques.

Let's define a divisibility graph for a set of positive integers $ A={a_{1},a_{2},...,a_{n}} $ as follows. The vertices of the given graph are numbers from set $ A $ , and two numbers $ a_{i} $ and $ a_{j} $ ( $ i≠j $ ) are connected by an edge if and only if either $ a_{i} $ is divisible by $ a_{j} $ , or $ a_{j} $ is divisible by $ a_{i} $ .

You are given a set of non-negative integers $ A $ . Determine the size of a maximum clique in a divisibility graph for set $ A $ .

## 说明/提示

In the first sample test a clique of size 3 is, for example, a subset of vertexes $ {3,6,18} $ . A clique of a larger size doesn't exist in this graph.

## 样例 #1

### 输入

```
8
3 4 6 8 10 18 21 24
```

### 输出

```
3
```

# 题解

## 作者：cenxinyang12 (赞：7)

## 题意
给定 $n$ 个点的点权，点权有倍数关系的两个点相连，求出最多有几个点两两相连。
## 思路
利用 DP，定义 $f_i$ 是以数字 $i$ 为结尾的最长合法结果，$f_i$ 一定会被它的因数赋值。如： $ f_6 \gets f_2$ , $f_6 \gets f_3$。$f_6$ 既能被 $f_2$ 赋值，又能被 $f_3$ 赋值，便应该从中取最大值，转移方程即为:
### $ f_i=\max(\max{f_{j(j\mid i)}},f_i)$
------------
这样理解后，代码便不难打了，详细内容参见代码
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,i,ma,f[1000010];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //加速cin、cout，很不错的东西，能防止TLE，有能力的话还是用快读吧
    cin>>n;
    while(n--){
        //因为这种算法的每个点与前面一个点无关，所以可以直接使用while循环
        cin>>x;f[x]++;//读入并累加答案
        for(i=2;i*x<=1000000;i++)
            f[i*x]=max(f[i*x],f[x]);
        //对自己的倍数（即联通的点）更新结果
        ma=max(ma,f[x]);//求出最大值
    }
    cout<<ma;
    return 0;
}
```


---

## 作者：slzx2021zjx (赞：5)

简单题意：能约分的一对数间有路，问最大完全子图。

用最长公共子序列做法 dp 求出最长路，由于一个数约数的约数也是这个数的约数，所以只要能连起来就是个完全子图。

## CODE
```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 1000000
using namespace std;
int n,dp[maxn+5],Max=-2e9;
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
    	int x;
        scanf("%lld",&x);
        dp[x]++;
        Max=max(Max,dp[x]);
        for(int j=2;j*x<=maxn;j++){
            dp[j*x]=max(dp[j*x],dp[x]);
        }
    }
    printf("%lld\n",Max);
    return 0;
}

```


---

## 作者：Up_Xu (赞：4)

# **思路**

本题可用筛选法加 DP 做。
 
 
 定义 $dp_i$ 表示：以 $i$ 这个权值结尾的最大合法结果，那么 $dp_i$ 就等于 $i$ 的所有因数在 $dp$ 数组中的最大值。这样一想，本题就简单了，用筛选法求出每个权值 $j$ 的倍数 $i$，可得转移方程： 
 
$$dp_i=\max(dp_i,dp_j)$$



# **代码**
```
#include <bits/stdc++.h>
using namespace std;
const int M=1000010;
int  n,sum,Max;
int b[M],dp[M],f[M];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);//加速代码 
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>b[i];
		Max=max(Max,b[i]);//求最大 
		f[b[i]]=1;//计数 
	}
	
	for(int i=1;i<=n;i++){
		int x=b[i]; 
		int j=x;
		dp[x]++;//自己算一个点 
		while(j+x<=Max){ //筛选 
			j+=x;
			if(f[j]==1)//判断此点是否出现 
				dp[j]=max(dp[j],dp[x]);//转移方程 
		}
		sum=max(dp[x],sum);//边做边求最大 
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：Y2y7m (赞：3)

upd：更改了之前的一些笔误。

翻译也有些笔误（

~~这道题CF评分1500我居然顿了一会才切掉。~~

十分明显，这道题的题意就是给你一个数列，找到其中的一个最大的子序列使得其中任意两数之间有倍数关系。

很容易发现是 $\text{dp}$。先将数组排序，然后再 $\text{dp}$。

定义 $f_i$ 为以数字 $i$ 为结尾的最长合法子序列，转移方程即为:

$$f_i=\max(\max{f_{j(j\mid i)}+1},1)$$

发现这么做是 $n^2$ 的，不太可行。

于是考虑计算贡献，即从当前状态计算对其他状态的贡献。用 $f_i$ 去更新 $i$ 的倍数的状态。

众所周知调和级数为 $\log{n}$，所以本题复杂度为 $O(n\log_2{n})$。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
const int maxn=1e6+10;
int n;
int a[maxn];
int f[maxn],cnt[maxn];
int mx=0;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],mx=max(mx,a[i]),cnt[a[i]]++;
	sort(a+1,a+1+n);
	int c=unique(a+1,a+1+n)-a-1;
	for(register int i=1;i<=c;i++)
	{
		int t=a[i];
		f[t]=max(f[t],cnt[t]);
		for(int j=2;j*t<=mx;j++)
			f[j*t]=max(f[j*t],f[t]+cnt[j*t]);
	}
	int ans=0;
	for(int i=1;i<=c;i++)
		ans=max(ans,f[a[i]]);
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：lizhengdong (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/CF566F)

## 1.题目分析
题目意思很简单，简单概括一下：

当一个数是另一个的因数或倍数，两数之间就连一条边，然后让我们找最大的团（团就是所有点凉两两都有一条边，团的大小就是包含了几个点）。

既然两数之间，一个数是另一个的因数或倍数，才连边，那我们就可以规定一个数向自己的倍数连边，那不难想到用 dp。

## 2.解题思路

接着，建立 dp：

定义 $dp[i]$ 为以 $i$ 这个数结尾最大的合法团大小，那么 $dp[i]$ 就等于所有因数在 $dp$ 数组中的最大值。这样一想，思路就非常清晰了。当当前这个数为 $i$，要推 $i×j$ 倍数，最终可以推出转移方程： $dp[i×j]= \max (dp[i×j],dp[i])$

## 3.AC code
``` cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,ans,i,j,x,ma,a[N],dp[N],f[N];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //加速输入输出
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>a[i];
        ma=max(ma,a[i]);//求最大范围 
        f[a[i]]=1;//计数
    }
    for(i=1;i<=n;i++){
        x=a[i];
        dp[x]++;/算上自己
        for(j=2;j<=ma/x;j++)
            if(f[x*j])//存不存在x*j这个点
                dp[x*j]=max(dp[x*j],dp[x]);//转移
        ans=max(ans,dp[x]);//求最大
    }
    cout<<ans;
}
```

---

## 作者：yty2010 (赞：1)

##### 这篇题解教你从一个蒟蒻的角度看绿题
~~（话说CF的绿题比较水）~~

## 题意简述：
给定 $n$ 个数，将每个数对应编号的点与它的倍数对应编号的点连边，求最大的联通块大小。
## 分析
由于 $n \le 10^6$，所以用 $n^2$ 的时间两两判断能否连边是不行的。

因此考虑对每个 $a_i$ 分别操作：定义 $b_i$ 表示 $i$ 的因数组成的图中最大的连通块大小。那么有枚举每个不为 $i$ 的 $i$ 的因数 $g$，有 $b_i=\max(b_i,g_i)$。

操作方式：对于输入的每一个 $a$，先将 $b_a+1$，再更新 $b$ 数组中下标为 $a$ 的倍数的点（用上述操作），最后更新答案就好了。

具体操作可以自己按样例推一遍，这里不做描述。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int b[1000005];
int maxn;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);  //输入输出优化，不然会TLE
	cin>>n;
	while(n--)
	{
		int a;
		cin>>a;
		b[a]+=1;
		for(int i=2;i*a<=1e6;i++)
			b[a*i]=max(b[a],b[i*a]);  //更新b数组
		maxn=max(maxn,b[a]);     //更新答案
	}
	cout<<maxn<<endl;
} 
```

## 后记
这就是动态规划的简化版，对于动态规划的描述见其他题解。

---

## 作者：COsm0s (赞：1)

## $\mathcal{Solution}$

本题的思路很明确，即向自身的因数连边。

转移方程如下：

$f_i=\max_{j\mid i} f_j + 1$。

显然，此方程是 $\Theta(n\sqrt n)$ 级别的，对于 $10^6$ 的数据难以卡过。

那我们考虑向当前数的倍数连边。

转移方程如下：

$f_{i\times k}=\max(f_i+1, f_{i\times k})$。

因为调和级数是 $\Theta(\log n)$ 的，所以总复杂度 $\Theta(n\log n)$。

## $\mathcal{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5, mod = 998244353;
int a[N], b[N], f[N], n, ans;
void slove() {
	cin >> n;
	for(int i = 1; i <= n; i ++) cin >> a[i], b[a[i]] ++;
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i ++) {
		f[a[i]] = max(f[a[i]], b[a[i]]);
		for(int j = (a[i] << 1); j < N; j += a[i])
		   f[j] = max(f[j], f[a[i]] + b[j]);
		ans = max(ans, f[a[i]]);
	}
	cout << ans << '\n';
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; 
//	cin >> T;
	while(T --) slove();
	return 0;
}
```


---

