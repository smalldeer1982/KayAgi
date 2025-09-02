# Bicycle Chain

## 题目描述

Vasya's bicycle chain drive consists of two parts: $ n $ stars are attached to the pedal axle, $ m $ stars are attached to the rear wheel axle. The chain helps to rotate the rear wheel by transmitting the pedal rotation.

We know that the $ i $ -th star on the pedal axle has $ a_{i} $ $ (0&lt;a_{1}&lt;a_{2}&lt;...&lt;a_{n}) $ teeth, and the $ j $ -th star on the rear wheel axle has $ b_{j} $ $ (0&lt;b_{1}&lt;b_{2}&lt;...&lt;b_{m}) $ teeth. Any pair $ (i,j) $ $ (1<=i<=n $ ; $ 1<=j<=m) $ is called a gear and sets the indexes of stars to which the chain is currently attached. Gear $ (i,j) $ has a gear ratio, equal to the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF215A/552855b6cae5503b6d59fc360af0683e021f4625.png).

Since Vasya likes integers, he wants to find such gears $ (i,j) $ , that their ratios are integers. On the other hand, Vasya likes fast driving, so among all "integer" gears $ (i,j) $ he wants to choose a gear with the maximum ratio. Help him to find the number of such gears.

In the problem, fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF215A/552855b6cae5503b6d59fc360af0683e021f4625.png) denotes division in real numbers, that is, no rounding is performed.

## 说明/提示

In the first sample the maximum "integer" gear ratio equals 3. There are two gears that have such gear ratio. For one of them $ a_{1}=4,b_{1}=12 $ , and for the other $ a_{2}=5,b_{3}=15 $ .

## 样例 #1

### 输入

```
2
4 5
3
12 13 15
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
1 2 3 4
5
10 11 12 13 14
```

### 输出

```
1
```

# 题解

## 作者：LKY928261 (赞：1)

## 翻译更正

求当 $b_j\mod a_i=0$ 时，$\frac{b_j}{a_i}$ 的最大值的个数。

## 题目分析

由于 $1\le n,m\le50$，数据范围极小，直接暴力枚举即可。

设 $t$ 是当前的最大值，$ans$ 是当前的答案数。枚举 $i$ 和 $j$，当 $b_j\mod a_i=0$ 时，分情况讨论：
- 若 $\frac{b_j}{a_i}>t$，则将 $t$ 更新为 $\frac{b_j}{a_i}$，并将 $ans$ 赋值为1；
- 若 $\frac{b_j}{a_i}=t$，则将 $ans$ 增加1；
- 若 $\frac{b_j}{a_i}<t$，则不做修改。

## 参考代码

本人的代码非常精简，欢迎借(chao)鉴(xi)。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,a[55],b[55],i,j;
int main(){
	cin>>n;
	for(i=0;i<n;i++)cin>>a[i];
	cin>>m;
	for(i=0;i<m;i++)cin>>b[i];
	for(i=0;i<n;i++)for(j=0;j<m;j++)if(b[j]%a[i]==0)
		if(b[j]/a[i]>x)x=b[j]/a[i],y=1;
		else if(b[j]/a[i]==x)y++;
	cout<<y<<"\n";
}
```

---

## 作者：Albedo (赞：1)

## Description

有多少对 $ (i,j) $，满足 $ b(j) \bmod a(i)=0 $ 并且 $ \frac{b(j)}{a(i)} $ 最大。

## Solution


考虑枚举 $ a_i $ 是多少，然后运用埃氏筛筛质数的方法，枚举他的倍数，如果他的倍数在 $ b_i $ 中存在，那么就记录下这个倍数，同时求出这个倍数的最大值，这样子，我们就满足了题目的限制。

但是接下来，我们还要处理的是有多少对 $ (i,j) $ 满足限制，这个其实也很简单，运用乘法原理，假设 $ a_i $ 的出现次数为 $ x $，$ b_i $ 的出现次数为 $ y $，那么如果 $ a_i $ 和 $ b_i $ 满足限制，他们的贡献就是 $ x\times y $。

## Code

```c++
n=read();
for (i=1;i<=n;i++) x=read(),exist[x]++;
m=read();
for (i=1;i<=m;i++) x=read(),fre[x]++;
	//b[j]/a[i]
for (i=1;i<=10000;i++)
	 if (exist[i])
	   for (j=1;j<=10000/i;j++)
	      if (fre[i*j])
	          ans=max(ans,j);
for (i=1;i<=10000/ans;i++)
	 if (exist[i])
	    sum+=fre[i*ans]*exist[i];
 printf("%d\n",sum);
```



---

## 作者：123456zmy (赞：1)

题意：  
给你两个序列 $a,b$，你要选出一个数对 $(i,j)$，使得 $b_j\bmod a_i=0$ 且 $b_j/a_i$ 最大，输出这样的$(i,j)$ 对的个数。
___
因为 $n$ 和 $m$ 都很小，所以枚举所有的 $(i,j)$ 同时记录最大值和最大值出现的次数即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ansn,a[51],b,ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&b);
		for(int j=1;j<=n;j++)if(b%a[j]==0)
		{
			if(b/a[j]>ans)ans=b/a[j],ansn=1;
			else if(b/a[j]==ans)++ansn;
		}
	}
	printf("%d",ansn);
	return 0;
}
```

---

## 作者：Fr0sTy (赞：0)

### 题意简述
------------

给定一个长为 $n$ 的数列 $a$ 和一个长为 $m$ 的数列 $b$。

令 $f(i,j) = \dfrac{b_j}{a_i}$。令 $t=f(i,j)_ {max}$。问所有有序数对 $(i,j)$ 为 $t$ 的个数。

### 解题思路
------------

注意到本题数据范围：$1 \leqslant n \leqslant 50 , 1 \leqslant m \leqslant 50$。

因为 $n \cdot m \leqslant 2500$，所以 $\Theta (nm)$ 完全能过这道题。选择**枚举**。

注意 $f(i,j) \in \mathbb{Z^+}$。所以要判读能否被整除。

### 代码实现
------------

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000005],b[1000005];
int maxx,ans;
int main() {
	scanf("%d",&n); for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	scanf("%d",&m); for(int i=1;i<=m;i++) scanf("%d",&b[i]);
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(b[j]%a[i]==0&&b[j]/a[i]>maxx) maxx=b[j]/a[i],ans=1;
			else if(b[j]%a[i]==0&&b[j]/a[i]==maxx) ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
//code by TheCedar
```

---

## 作者：Firstly (赞：0)

本题翻译有些问题，有条件没有翻译进去，题目应为求 $b_j \bmod a_i = 0$ 时，$f(i,j)$ 的最大值。

## **题目思路**：

由于数据范围仅为 $n\leq 50$，$m\leq 50$，所以直接暴力枚举即可。

我们可以进行两重循环，第一重循环求每一个 $f(i,j)$ 的值，并记录下其中的最大值。注意，该环节还需要判断 $b_j \bmod a_i$ 是否等于 $0$。由于因为题目保证 $b$ 数组中的任意值都不小于 $1$，所以任意合法的 $f(i,j)$ 都必定大于 $0$，那么我们就可以仅在 $b_j \bmod a_i=0$ 时对 $f(i,j)$ 进行赋值，否则默认为 $0$。

然后再将数组枚举一遍，如果当前 $f(i,j)$ 与最大值相等时，将答案加 $1$，最后输出答案即可。

## **Code：**

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,a[55],b[55],ans;
double f[55][55],t;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;i++)cin>>b[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(b[j]%a[i]==0)f[i][j]=1.0*b[j]/a[i],t=max(t,f[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(f[i][j]==t)ans++;
	cout<<ans;
	return 0;
}
```


---

## 作者：Need_No_Name (赞：0)

# Solution For CF215A

~~锻炼一下暴力能力，万一哪天联赛爆零了呢~~

## 题意

给你一个长度为 $n$ 序列 $a$ 和长度为 $m$ 的序列 $b$ ，你要选出一个数对 $(i,j)$，$(1≤i≤n, 1≤j≤m)$，使得 $b_j \bmod $ $a_i = 0$ 且 $\frac{b_j}{a_i}$ 最大，输出这样的 $(i,j)$ 对的个数。

（翻译误人子弟。。。害我白白浪费了半小时。。。）

## 思路

直接在 $a$ 和 $b$ 中枚举 $i$，$j$ ，先去枚举最大值，再去找数量即可

还是很水的，建议评红。

## 代码

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
const int N = 55;
int n, m;
int a[N], b[N];
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	cin >> m;
	for(int i = 1; i <= m; i++) cin >> b[i];
	int maxa = -INT_MAX;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++){ if((b[j] % a[i]) == 0) maxa = max(maxa, b[j] / a[i]);}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if((b[j] % a[i]) == 0 && b[j] / a[i] == maxa) ans++;
		}
	}
	cout << ans << endl;
	return 0;
 } 
```


---

## 作者：多喝岩浆 (赞：0)

这题让你求所有 $b_j\div a_i$ 中的最大值的个数，那么只需要枚举一遍 $n$ 和 $m$ 如果$a_i \mid b_j$ 那么开一个桶，把位置为 $b_j\div a_i$ 的那个桶数量加 $1$ 最后从 $10000$ 开始从打到小扫一遍，如果找到了，那么他就是最大值，输出答案退出循环。代码如下：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define PP pair <int, int>
using namespace std;
const int N = 1e4 + 10;
const int M = 55;
int f[N], a[M], b[M], n, m;
int main () {
	//freopen (".in", "r", stdin);
	//freopen (".out", "w", stdout);
	ios::sync_with_stdio (false);
	cin.tie (0), cout.tie (0);
	cin >> n;
	for (int i = 1; i <= n; i ++ ) cin >> a[i];
	cin >> m;
	for (int i = 1; i <= m; i ++ ) cin >> b[i];
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= m; j ++ )
			if (b[j] % a[i] == 0) f[b[j] / a[i]] ++ ;
	for (int i = 10000; i; i -- )	
		if (f[i]) {
			cout << f[i] << endl;
			return 0;
		}
	return 0;
}
```


---

