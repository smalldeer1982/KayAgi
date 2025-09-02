# The Fibonacci Segment

## 题目描述

你得到了一个数组 $a_1,a_2,\dots,a_n$。区间 $[l,r]$被称为**好的**，仅当对于每一个 $i$ $(l + 2 \leq i\leq r)$，都满足 $a_i = a_{i-1} + a_{i - 2}$。

定义区间 $[l,r]$ 的长度 $len([l,r])$ 为 $r - l + 1$，区间 $[l_1,r_1]$ 比 区间 $[l_2,r_2]$ 更长，仅当 $len([l_1,r_1]) \gt len([l_2,r_2])$。

你要求出在数组 $a$ 中最长的好的区间。

注意，一个长度为 $1$ 或 $2$ 的区间总是好的。

## 样例 #1

### 输入

```
10
1 2 3 5 8 13 21 34 55 89
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5
1 1 1 1 1
```

### 输出

```
2
```

# 题解

## 作者：bigclever (赞：3)

## 思路：
因为一个好的区间 $[l,r]$ 满足 $a_i=a_{i-1}+a_{i-2}(l+2 \le i \le r)$。所以对于每一个 $a_i$，如果它满足该条件，那么长度 $+1$，否则重置为 $2$。最后在所有长度里取 $\max$ 即为数组 $a$ 中最长的好的区间。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(n<3){cout<<n;return 0;}//特判
	int len=2,ans=2;//因为长度为2的区间总是好的，所以初始值赋为2
	for(int i=3;i<=n;i++){
		if(a[i-1]+a[i-2]==a[i])len++;
		else len=2;
		ans=max(ans,len);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Spir1t (赞：3)

## [传送门](https://www.luogu.com.cn/problem/CF365B)

对于这道题，我们首先可以定义一个 $len$ 代表这个好的区间的长度，并将 $len$ 初始值设为 $2$，然后只需判断 $a_i$ 是否等于 $a_{i-1}+a_{i-2}$ 的值，如果是那么就把 $len$ 加一，否则重置为 $2$ 即可。

但要注意的是，在判断 $a_i$ 是否等于 $a_{i-1}+a_{i-2}$ 的时候，必须再判断一下这项 $i$ 是不是大于等于 $3$。

代码很简单，就不放了

---

## 作者：foryou_ (赞：2)

定义 $cnt$ 为当前好序列的长度，**初始值为 $2$**。

**核心思路**：对于每一个满足 $3 \le i \le n$ 的 $a_i$，若满足 $a_i=a_{i-1}+a_{i-2}$，则将 $cnt$ 累加，否则变回初始值 $2$；同时将最长好序列的长度 $ans$ 变为 $\max(cnt,ans)$。

需要注意当 $n=1$ 时，仅需直接输出 $1$ 即可。

代码很好写，因此不再展示了。感觉只有入门难度。

---

## 作者：Chis725 (赞：2)

### 题目简介

给一个长度为 $n$ 的数列，求一个区间满足从第三个数起每一个数都是前两个数的和，求区间的最大长度。

### 思路

这道题明显是一道模拟题，我们从第三个数开始枚举，如果这个数是前两个数的和，它可以接上上一个区间，将 $sum$ 加一，否则将 $sum$ 的值重新变成 $2$，最后将每个可能的区间的长度取最大就是我们的答案。

### 细节

当 $n$ 小于 $2$ 时，他的答案是 $n$。$sum$ 的初始值为 $2$。

### 代码献上：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,ans=2,sum,a[100001];
signed main(){
    cin>>n;
    if(n<=2){cout<<n;return 0;}//特判
    sum=2;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(i>=3){//从三开始
            if(a[i]==a[i-1]+a[i-2])sum++;
            else sum=2;
            ans=max(ans,sum);//取最大的区间
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Zq_water (赞：2)

思路很简单，若这上两项之和等于该项，累加，否则重置成 $2$，每次记录最大值。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int n,s=2,ans,a[100005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	if(n<=2){//要特判
		printf("2");
		return 0;
	} 
	for(int i=3;i<=n;i++){
		if(a[i]==a[i-1]+a[i-2]) s++; //累加
		else s=2; //重置
		ans=max(ans,s);//记录最大值
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Bpds1110 (赞：1)

[**原题传送门**](https://www.luogu.com.cn/problem/CF365B)
## 题面:
给出一个含有 $n$ 个正整数的序列 $a$，求这个序列中最长的好的区间。其中，好的区间定义为从第三项起，当前这项等于前两项之和。
## Solution:
一道纯模拟水题，最长不降子序列。特判：如果 $n$ 小于或等于 $2$，那么这个序列中最长的好区间的长度就是它的长度。我们设 $s$ 为当前保持的好的区间的长度，从 $3$ 开始把这个序列扫一遍，如果当前这项等于前两项之和，则长度加 $1$，否则重新开始一个新的区间。最后，每个区间求最大即可。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,s,ans,a[100001];
int main()
{
	cin>>n;
	for(i=1;i<=n;i++) cin>>a[i];
	if(n<=2) return cout<<n,0;//特判，如果长度<=2则直接输出 
	s=2;//默认初始长度为2 
	for(i=3;i<=n;i++)//从3开始扫一遍 
	{
		if(a[i-1]+a[i-2]==a[i]) s++;//如果满足条件，长度+1 
		else s=2;//否则重新开始计数 
		ans=max(ans,s);//求最大 
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：封禁用户 (赞：1)

这道题目。。。水得很啊。。。

不知道我为什么能成为咕咕第一个交的$\rm QwQ$

思路蛮简单，就是暴力+线扫，先读入两个数，然后不断地读入数，判断是否是前两个数之和，如果是，则$s++$，如果不是，就记录一下最大值。

$\rm My$ $\rm Code$
```cpp
#include<cstdio>
#include<algorithm>
int n,x,y,z,maxx=2,s=2;
using namespace std;
int main()
{
	scanf("%d",&n);
	if (n<3)
	{
		printf("%d\n",n);
		return 0;
	} 
	scanf("%d%d",&x,&y);
	for (int i=1;i<=n-2;i++)
	{
		scanf("%d",&z);
		if (z==x+y) s++,x=y,y=z; else
		{
			x=y,y=z;
			maxx=max(maxx,s);
			s=2;
		}
	}
	maxx=max(maxx,s);
	printf("%d\n",maxx);
	return 0;
}
```

---

## 作者：lmndiscyhyzdxss (赞：0)

### 题目大意
一个数组 $ a $ 的一个好区间，要求每一个数都是前两个数之和，求最长的好区间的长度。           

注意：长度为 $ 1 $ 或 $ 2 $ 的区间总是好的。
### 题目分析
直接暴力，不断判断这个数是否是前两个数之和，如果是，则长度加，如果不是，就记录一下最大值，记得初始化为 $ 2 $。  

注意:前头加上一个特判，如果长度 $ <3 $，直接输出 $ n $。

还要记得最后在记录一下。
### AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100010],ma=-1,h=2;
int main(){
	cin>>n;
	if(n<3){cout<<n;return 0;}//特判
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=3;i<=n;i++)
	{
		if(a[i]==a[i-1]+a[i-2])h++; //累加
		else ma=max(ma,h),h=2; //判断和重置
	}
	ma=max(ma,h);//最后记录
	cout<<ma;
	return 0;
}
```


---

## 作者：LaDeX (赞：0)

## 题意

给定一个数组 $a$，区间 $[l,r]$ 被称为 **好的**，仅当对于每一个 $i$ $(l + 2 \leq i \leq r)$，都满足 $a_i = a_{i-1} + a_{i-2}$。

求最长的好区间的长度。

注意，长度为 $1$ 或 $2$ 的区间总是好的。

## 解法

感觉很水，从前往后扫一遍数组，如果 $a_i = a_{i-1} + a_{i-2}$，那么 当前好字符串长度 加一，答案取最大值，否则当前长度赋值为 $2$。

注意要特判 $n = 1$ 或 $n = 2$ 的情况，且 答案初始化为 $2$。

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
#define Fcin\
	ios :: sync_with_stdio(0);\
	cin.tie(0); cout.tie(0)
using namespace std;
const LL N = 1e5 + 10;
LL n, A[N];

int main(){
	Fcin;
	cin >> n;
	for (LL i = 1; i <= n; i ++){
		cin >> A[i];
	}
	// 特判
	if (n <= 2){
		cout << n;
		return 0;
	}
	
	LL ans = 2, res = 2;
	for (LL i = 3; i <= n; i ++){
		if (A[i] == A[i - 1] + A[i - 2])
			ans = max(ans, ++ res);
		else
			res = 2;
	}
	cout << ans;
	return 0;
}
```


---

## 作者：Luo_gu_ykc (赞：0)

~~发现代码部分写错了，于是重新写了一遍~~

## 题目大意

给定一个长度为 $n$ 的序列 $a$，求满足条件的最长序列的长度。

满足的条件为：这个数列中任意一个数要为数列中前两个数之和。

## 思路

因为这种数列必须是要连续的，所以可以直接枚举一遍序列，如果当前数满足条件就计数器累加，不满足条件就取 $ \max $,然后计数器就重置为 $2$ 即可。

- ### 注:

1.仔细观察，可以发现，$n \geq 3$ 时，答案至少为 $2$。

2.$n \leq 2$ 时，不满足至少答案为 $2$ 的条件，所以直接输出 $n$。 

## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, a[N], maxi = 2, sum = 2;

int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for(int i = 3; i <= n; i++){
		if(a[i] == a[i - 1] + a[i - 2]){ // 满足条件
			sum++; 
		} else { // 不满足，计数器重置
			sum = 2;
		}
		maxi = max(maxi, sum); // 不断更新答案
	}
	cout << (n < 3 ? n : maxi);
	return 0;
}
```

---

## 作者：Colead (赞：0)

# CF365B
首先我们来确定这一题的做法。

看到题目，在一个数组中找出一个最长的满足某要求的连续段。

想到了什么？

### 动态规划（dynamic programming）

有人说：这一题我们明显可以设$f[i]$表示前i个数中最长的$rongzutong$数列的长度，但这样会有后效性，不能确定和后面有没有关联。

于是我们放弃这个想法。

### 回到题目的本质。

$rongzutong$数列一定是连续的，而且每一个数只依赖于其之前的两个数。

所以……

我们可以直接线性处理，从前往后扫一遍，不符合$a[i]=a[i-1]+a[i-2]$的数时，就把最大值更新，计数器清零。否则一路记下去，即可。

于是我们有了：
```
#include<bits/stdc++.h>
using namespace std;
int a[100005]={};
int main()
{
	int n;
	cin>>n;
	cin>>a[1]>>a[2];
	int fad=2;
	int maxn=0;
	for(int i=3;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==a[i-1]+a[i-2])
		{
			fad++;
		}
		else
		{
			maxn=max(maxn,fad);
			fad=2;
		}
	}
	cout<<maxn<<endl;
	return 0;
}
```

不符合就更新，这看起来没有问题。

然而第一个样例就挂了。

输出是0？

原来是它从头加到尾，根本没有更新$maxn$的机会！

于是我们在最后更新一下：

```
#include<bits/stdc++.h>
using namespace std;
int a[100005]={};
int main()
{
	int n;
	cin>>n;
	cin>>a[1]>>a[2];
	int fad=2;
	int maxn=0;
	for(int i=3;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==a[i-1]+a[i-2])
		{
			fad++;
		}
		else
		{
			maxn=max(maxn,fad);
			fad=2;
		}
	}
	maxn=max(maxn,fad);
	cout<<maxn<<endl;
	return 0;
}
```

样例貌似没有了问题，（又是一个）然而……

## WA

原来n还不到3的时候要特判，不然会算多！

于是我们有了：

## AC代码：
```
#include<bits/stdc++.h>
using namespace std;
int a[100005]={};
int main()
{
	int n;
	cin>>n;
	if(n<3)
	{
		cout<<n<<endl;
		return 0;
	}
	cin>>a[1]>>a[2];
	int fad=2;
	int maxn=0;
	for(int i=3;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==a[i-1]+a[i-2])
		{
			fad++;
		}
		else
		{
			maxn=max(maxn,fad);
			fad=2;
		}
	}
	maxn=max(maxn,fad);
	cout<<maxn<<endl;
	return 0;
}
```

下次再见啦，拜拜！

---

## 作者：ZHANGyutao123 (赞：0)

# 题目大意

给定一个长度为 $n$ 的数组 $a$，找出其中最长的好的区间。所谓好的区间是指区间 $[l,r]$ 满足对于每一个 $i$ $(l+2 \leq i\leq r)$，都满足 $a_i = a_{i-1} + a_{i - 2}$。

# 思路
我们用 $f_i$ 表示以位置 $i$ 结尾的最长 Fibonacci 子序列长度。

那么当我们枚举到位置 $i$ 时，如果 $a_i$ 能够接在 $a_{j-1}$ 和 $a_j$ 上，使得 $a_{j-1}$、$a_{j}$、$a_i$ 构成一个 Fibonacci 子序列，则 $f_i$ 就可以从 $f_{j-1}$ 转移而来。

那么状态转移方程为：

$$
\begin{cases}
f_i=2, &i \leq 2 \\
f_i=f_{i-1}+1, &a_i=a_{i-1}+a_{i-2} \\
f_i=2, &a_i \neq a_{i-1}+a_{i-2}
\end{cases}
$$

初始状态为 $f_1=2, f_2=2$。因为一个长度为 $1$ 或 $2$ 的区间总是好的，所以初始状态也是合理的。

最终的答案即为 $f_i$ 中的最大值。时间复杂度为 $O(n)$，空间复杂度也是 $O(n)$。

# 参考代码
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int a[100002], f[100002],n, ans = 2;; 
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);//输入
    }
    f[1] = f[2] = 2; // 初始化长度为 1 和 2 的区间的答案均为 2
    for (int i = 3; i <= n; i++) {
        if (a[i] == a[i-1] + a[i-2]) { // 判断是否为好区间
            f[i] = f[i-1] + 1; // 在前一个好区间的基础上累计长度
        } else {
            f[i] = 2; // 不是好区间，则重新开始计算
        }
        ans = max(ans, f[i]); // 更新最大值
    }
    printf("%d",ans);
    return 0;
}

```


---

## 作者：ImNot6Dora (赞：0)

一道很好的斐波那契变形题。

由于题目中说了，长度为 $2$ 的序列是好的，所以我们把答案初始值设为 $2$。

之后开始输入，当输入到第三个数时，开始计算，如果满足 $a_i=a_{i-1}+a_{i-2}$，就累计，否则将累计的变量恢复为 $2$，每次操作后比较大小即可。

注意别忘了特判 $n$ 是 $1$ 的情况。

# AC C++ CODE：
~~（高清无注释）~~

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int a[100010];
int main(){
	int n;
	cin>>n;
	int ans=2,cnt=2;
	if(n==1){
		cout<<1;
		return 0; 
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(i>=3){
			if(a[i]==a[i-1]+a[i-2])cnt++;
			else cnt=2;
			ans=max(ans,cnt);
		}
	}
	cout<<ans;
	return 0;
}

```
By ImNot6Dora

---

## 作者：ssSSSss_sunhaojia (赞：0)

[**原题传送门**](https://www.luogu.com.cn/problem/CF365B)
# 思路：
我们将给定的 $a$ 将数组从第三个数开始扫一遍。然后对于每一个 $a_i$，如果这个数是前两个数之和，则增加当前好的区间的长度；否则，先更新答案，再将前好的区间的长度变为 $2$。
# 细节：
* 如果 $n \leq 2$，则应该输出 $n$，因为一个长度为 $1$ 或 $2$ 的区间总是好的。
* 区间长度的初始值应是 $2$，因为是从第三个数开始扫的。
* 循环结束后，还要更新一下最大值，因为有可能最终的区间长度没被更新过。
# Code:
```
#include <bits/stdc++.h>
using namespace std;
#define in inline
#define re register
typedef long long LL;
LL n, a[100010], sum = 2, ans = 2; 
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n; 
	for(re int i = 1; i <= n; i ++) cin >> a[i]; 
	if(n <= 2) {cout << n; return 0; }//特判
	for(re int i = 3; i <= n; i ++) 
		if(a[i] == a[i - 1] + a[i - 2]) sum ++; //增加区间的长度
		else ans = max(ans, sum), sum = 2; //更新答案并将区间的长度变为2
	ans = max(ans, sum); //最后再更新一次
	cout << ans; 
	return 0;
}
```

---

## 作者：lkjzyd20 (赞：0)

### 思路
思路蛮简单，因为“好的”必须是要连续的，所以可以直接暴力枚举一遍序列。如果当前数满足条件就计数器累加，不满足条件就取 $\max$，然后计数器就重置为 $2$ 即可，注意，长度为 $\leq 2$ 的数列肯定是“好的”，直接输出 $n$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,tot=2,ans,a[100001];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);    
    for(int i=3;i<=n;i++)
    {
        if(a[i]==a[i-1]+a[i-2]) tot++;
        else tot=2;
        ans=max(ans,s);
    }
    if(n<=2)
        printf("%d",n);
    else
        printf("%d",ans);
    return 0;
}
```

---

