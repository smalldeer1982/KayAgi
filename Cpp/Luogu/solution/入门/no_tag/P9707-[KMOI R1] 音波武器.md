# [KMOI R1] 音波武器

## 题目背景

在 [对 $Y$ 星的军事行动](/problem/P9709) 中，舰队在攻占城市 $p$ 时遇到了一些困难。

## 题目描述

小袁的舰队采用使用音波武器攻击的方式，但是对方的城墙使用了一种特殊材料——普林，导致音波攻击效果不是很好。

我们定义**削弱系数 $m$** 为：收到强度为 $n$ 的音波时，音波在穿透普林后会被削弱为 $n\bmod m$ 强度的音波。

现在小袁发射了强度为 $l!,(l+1)!,(l+2)!\dots (r-1)!,r!$ 的 $r-l+1$ 个音波，对方使用了削弱系数为 $k$ 的普林。现在小袁想知道，经过削弱后强度最大的音波的强度是多少。

符号 $!$ 在这里表示阶乘，$x!=1\times 2\times\dots\times x$。例如 $4!=1\times2\times3\times4$。特别地， $0!=1$。

## 说明/提示

## 样例 $1$ 解释

最终强度分别是 $1,2,2$，故输出 $2$。

## 样例 $2$ 解释

最终强度分别是 $6,4,0,0$，故输出 $6$。

## 数据范围

对于 $20\%$ 的数据：$1\le l\le r\le 20$，$1\le k\le 10^2$。

对于 $50\%$ 的数据：$1\le l\le r\le 2000$，$1\le k\le 10^5$。

对于 $100\%$ 的数据：$1\le l\le r\le 2\times 10^6$，$1\le k\le 10^{12}$。

## 样例 #1

### 输入

```
1 3 4```

### 输出

```
2```

## 样例 #2

### 输入

```
3 6 10```

### 输出

```
6```

## 样例 #3

### 输入

```
100 1000 911451407```

### 输出

```
911273936```

# 题解

## 作者：zhang_Jimmy (赞：11)

看到这题，我们想到的最直接的思路就是从 $l$ 遍历到 $r$，算出阶乘然后取最大值。但是这样显然会超时。

于是我们可以用一个辅助数组 $a$，用空间来换时间。

# 正确思路：

首先计算出 $l!  \bmod k$ 的值，将其存在 $a_l$ 里。

接下来，我们按照这样的规律来计算：

$$a_i = a_{i - 1} \times i \bmod k$$

为什么呢？

这样想一下：

我们已经计算出了 $3! = 6$，现在要计算 $4!$。

$3! = 1 \times 2 \times 3$，$4! = 1 \times 2 \times 3 \times 4$。

可以发现后者比前者刚好多乘了一个 $4$。

那么这个性质可以得到推广：

对于任意一个 $i!$，都有 $i! = (i - 1)! \times i$。

总结出来这个公式后，结合题目，就可以得到 $a_i = a_{i - 1} \times i \bmod k$ 这个公式了。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

long long l, r, k, ans = INT_MIN, a[2000010]; 

long long jc(long long n){
	long long sum = 1;
	for(int i = 1; i <= n; i ++){
		sum = sum * i % k;
	}
	return sum;
}

int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	cin >> l >> r >> k;
	ans = max(ans, jc(l));
	a[l] = jc(l);
	for(int i = l + 1; i <= r; i ++){
		a[i] = a[i - 1] * i % k;
		ans = max(ans, a[i]);
	}
	cout << ans;
	return 0;
}

```


---

## 作者：Brain_Huger (赞：4)

## 题目大意
> 在 $\left [ l,r \right ] $ 区间内，求出区间内数的阶乘模 $k$ 的最大值。

## 解题思路

不难发现这题暴力从 $l$ 遍历到 $r$，每次求出阶乘，肯定会 T。所以我们要优化此代码。

不难发现，设一个数为 $i$，那么 $(i+1)!=i! \times (i+1)$，也就是说我们可以只算出 $l$ 的阶乘，每次遍历时再乘上遍历的数，然后取模，复杂度 $O(r)$，可以通过此题。

最后附上代码：
```
#include<bits/stdc++.h>
#define int long long
#define D(x) cout<<#x<<'='<<x;
int l,r,k,ans,ll;
int jc(int x){//阶乘
	if(x==0)return 1;
	return x*jc(x-1)%k;
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%lld%lld%lld",&l,&r,&k);
	ans=ll=jc(l)%k;
	for(int i=l+1;i<=r;i++){
		ll*=i,ll%=k,ans=std::max(ans,ll);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：4)

# P9707 [KMOI R1] 音波武器

场切的大水题。

### 解法

就是计算 $l!,(l+1)!,\cdots,(r-1)!,r!$ 模 $k$ 的最大值。

你不能把每个数都依次算出来，这样时间会爆掉；你可以这么做：先算出 $l!$ 模 $k$ 的值，然后将这个数乘上 $(l+1)$ 并对 $k$ 取模，然后你就算出了 $(l+1)!$ 模 $k$ 的值，并对其取最大值即可。

### 代码

```cpp
#include<iostream>
using namespace std;
long long l,r,k,num,ans;
int jc(int x){ //阶乘 
	return x==1?1:x%k*jc(x-1)%k;
}
int main(){
	cin>>l>>r>>k;
	num=ans=jc(l); //先计算出 l! 模 k 的值 
	for(int i=l+1;i<=r;i++){
		num*=i; num%=k; //依次算出 (l+1)!,(l+2)!,...,(r-1)!,r! 模 k 的值 
		ans=max(ans,num); //取其中最大者 
	}
	cout<<ans;
return 0;
}
```


---

## 作者：AuZeb (赞：4)

### _**思路**_  

------------

从 $1$ 枚举至 $r$，使用 $j$ 存储阶乘之积，边乘边模，当 $l \le i \le r$ 使用 $\max$ 更新答案。

### _**代码**_ 
 
------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long l,r,k,ans=0,j=1;
	cin>>l>>r>>k;
	for(int i=1;i<=r;i++){
		j*=i,j%=k;
		if(i>=l) ans=max(ans,j);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：szh_AK_all (赞：3)

## 题意
给出 $l$ 和 $r$，要我们求出从 $l$ 的阶乘到 $r$ 的阶乘中对 $k$ 取模的最大值。

## 分析
不难发现，对于 $l!,(l+1)!,(l+2)!...(r-1)!,r!$，后一项都是前一项的倍数，所以，不难推出：$(i+1)! \equiv i!\times(i+1) \pmod k$，其中 $i$ 为非负整数。

由此，我们就得到了一个递推式。由于 $l,r,k$ 不可能为 $0$，所以，我们不妨设递推的第 $0$ 项为 $1$，然后依次递推，记录其中大于等于 $l$ 并且小于等于 $r$ 的值的最大值即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[2000005];
int main()
{
	int l,r;
	long long k;
	cin>>l>>r>>k;
	a[0]=1;
	long long ans=0;
	for(int i=1;i<=r;i++)
	{
		a[i]=a[i-1]*(i%k)%k;
		if(i>=l)
		ans=max(ans,a[i]);
	}
	cout<<ans;
} 
```


---

## 作者：二叉苹果树 (赞：3)

本题中 $l, r \leq 2 \times 10^5$，范围很小，考虑直接计算模 $k$ 意义下的 $l! \sim r!$ 然后取其中最大值即为所求。

另外 $k \leq 10 ^ {12}$，所以需要使用 $\text{long long}$。

```cpp
#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    long long l, r, k, ans = 1, max = 0;
    std::cin >> l >> r >> k;
    for (int i = 1; i <= r; i++)
    {
        ans = (ans * i) % k;
        if (i >= l)
            max = std::max(max, ans);
    }
    std::cout << max << std::endl;
    return 0;
}
```


---

## 作者：__Tonycyt__ (赞：2)

### 思路
本题暴力明显过不了，考虑优化。  
暴力算法中每次都要重新计算阶乘，但是其实 $i!=(i-1)!\times i$，所以可以记录上一次阶乘的值，留到下一次用。  
具体看代码。
### 代码
入门题我就不用读写优化了。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int l,r;
	long long k,cnt=1,maxx=0;//注意数据范围，不开long long见祖宗 
	cin>>l>>r>>k;//输入 
	for(int i=2;i<l;i++) cnt=cnt*i%k;//计算(l-1)! 
	for(int i=l;i<r;i++){
		cnt=cnt*i%k;//i!=(i-1)!*i
		maxx=max(maxx,cnt);//更新答案 
	}
	cout<<maxx;//输出答案 
	return 0;
}
```

---

## 作者：2c_s (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P9707)

## 思路

单层循环即可实现。

用数学原理推导出 $(i+1)!=i!\times (i+1)$ （$i$ 为任意非负整数）。于是我们从 $i=1$ 开始循环，一直循环到 $i=r$ 结束。每次循环到一个 $i$ 就将记录结果的变量 $\times i$ 后**对 $k$ 取余**。当 $l\le i\le r$ 时，记录结果变量的最大值。最后输出即可。

- 数据不在 int 范围内，记得开 long long。

## AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll l,r,m,ans;
int main(){
	cin>>l>>r>>m;
	ll k=1;
	for(int i=1;i<=r;++i){
		k=(k*i)%m;
		if(l<=i)ans=max(ans,k);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：DFbd (赞：1)

直接模拟，从一循环到 $l$，算出 $l$ 的阶乘，再从 $l$ 循环到 $r$，边算阶乘边求答案。

可以把算 $l$ 的阶乘的循环和从 $l$ 循环到 $r$ 的循环合起来，统计答案时判断 $i$ 是否在 $l$ 到 $r$ 之间就好了。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long //要开long long
using namespace std;
int l, r, k, a = 1, ans;
signed main() {
  cin >> l >> r >> k;
  for (int i = 1; i <= r; i++) {
    a = (a * i) % k;
    if (i >= l) ans = max(ans, a);
  }
  cout << ans;
  return 0;
}
```

---

## 作者：Fiendish (赞：1)

本题为简单入门题。

根据阶乘定义，我们有 $n!=(n-1)!\times n$，所以可以线性地从 $l!$ 递推到 $r!$，注意每次递推时都要取模，否则会爆掉。

上代码：
```cpp
#include<iostream>
using namespace std;
int l,r,k;
long long ans,ans1;//数据范围
int main(){
	cin>>l>>r>>k;
	ans1=1;
	for(int i=1;i<l;i++) ans1=(ans1*((1ll*i)%k))%k;//递推+取模
	for(int i=l;i<=r;i++){
		ans1=ans1=(ans1*((1ll*i)%k))%k;//递推+取模
		ans=max(ans1,ans);//求最大答案
	}
	cout<<ans;
}
```
若有疏漏、不详之处，恳请各位大佬指点。

---

## 作者：miaoyu2022 (赞：1)

# 洛谷P9707音波武器题解

## 题意简述

很简单，就是求 $l!,(l+1)!,(l+2)!\dots (r-1)!,r!$ 全部 $\bmod k$ 的最大值。

## 思路

一看数据范围：

对于 $100\%$ 的数据：$1\le l\le r\le 2\times 10^6$，$1\le k\le 10^{12}$。

暴力枚举时间复杂度肯定没问题，但是 $\left(2\times 10^6\right)!$ 肯定会溢出，要不要上高精呢？其实不需要，因为完全可以每次都取模，不影响结果。

## 代码

代码写的比较丑，大佬们不要见怪啊。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r,k,ans=INT_MIN,t=1; //一定要开long long!
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0); //读入优化
	cin>>l>>r>>k;
	for(int i=1;i<l;i++)
		t=t*i%k; //先算出(l-1)!
	for(int i=l;i<r;i++){
		t=t*i%k;
		ans=max(ans,t); //取max
		if(t==0) break; //小小的优化，当（i!）是k的倍数时，那么剩下的(i+1)!到（r）肯定也是k的倍数，所以mod k一定为0，可直接返回。
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：littleqwq (赞：1)

# P9707 [KMOI R1] 音波武器题解

题外话：这一道不难的题，被我想复杂，~~提交了长达 33 次~~。

### 题目大致意思：

根据题目给的公式，求出最大强度。其实说的直白一点，就是从 $l$ 到 $r$ 之间所以数的阶乘里，找出 $i$ 的阶乘取余 $k$ 最大的结果是多少。

### 大致思路：

一开始的想法：就是从 $l$ 到 $r$ 之间一个个阶乘算过去，每乘一次，就取模一次，最后比大小，输出最大的。想法特别好，现实太残酷。

```
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    l=read();
    r=read();
    k=read();
    for(int i=r;i>=l;i--){
    	if(i==0){
    		long long l=1;
    		mx=maax(l,mx);
    		continue;
		}
    	long long p = jc(i,k);
		p=p%k;
		mx=maax(mx,p);
	}
	printf("%lld\n",mx);
```

成功收获超时 $50$ 分，当我以为超时不多时，发现我即使拿出了多种加快速度的方法，甚至加上了快读，把自带函数都写了一遍，还是超时。

经过某讨论区大佬帮我看过，我总算发现了个规律。

后来发现的规律：其实阶乘不用 $r - l + 1$ 次，只需先求出 $l$ 的阶乘即可，因为我们会发现 $i$ 的阶乘其实等于 $(i - 1)! × i$，用公式来看就是 $i! = (i - 1)! × i$。得到此规律，做起来就简单了，先求出 $l$ 的阶乘，比大小，接着每次乘上 $i$，比大小，每进行一次乘的操作，就取一次模 $k$，这样我们就理顺了思路，做起来就比较方便了！

代码实现：

```
#include<bits/stdc++.h>
using namespace std;
int l,r;
int x;
long long k,mx=INT_MIN;
long long maax(long long c,long long v){//自写函数找最大
	return c>v?c:v;
}
long long read(){//快读
	int k;
	k=0;
	char l=getchar();
	while(l>'9'||l<'1'){
		l=getchar();
	}
	while(l>='0'&&l<='9'){
		k=l-'0'+k*10;
		l=getchar();
	}
	return k;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    l=read();
    r=read();
    k=read();
	long long d=1;
	for(int i=1;i<=l;i++){//求l的阶乘
		d=d*i%k;//阶乘方法边乘边取模
	}
	d=d%k;
	mx=maax(d,mx);//找最大值，其实它里面原本没有值，可以直接把d放入mx里面
    for(int i=l+1;i<=r;i++){
    	d=d*i%k;//相同操作
    	mx=maax(d,mx);//比大小
	}
	cout<<mx<<endl;//输出
    return 0;
}
```

注：注意数据范围哦！

这样，这道题就完成啦！！！

---

## 作者：CRTL_xzh2009 (赞：1)

模拟。

对于输入的 $l,r,k$，先用 $sum$ 预处理 $1 \sim l$ 的乘积（记得模 $k$！！！），再从 $l \sim r$ 枚举，每次答案 $ans$ 取 $sum$ 和原 $ans$ 的最大值即可。

注意：本题采用 `long long` 存储 $sum$ 与 $ans$。

```cpp
#include<bits/stdc++.h>
#define ll long long //开long long 
using namespace std;
ll l,r,k,ans=0,sum=1;
int main()
{
	scanf("%lld %lld %lld",&l,&r,&k);
	for(int i=1; i<=l-1; i++) //预处理 1~l 
	{
		sum*=i;
		sum%=k; //记得模k
		//printf("%lld ",sum);
	}
	for(int i=l; i<=r; i++) 
	{
		sum*=i;
		sum%=k;
		ans=max(ans,sum); //计算最大值 
	}
	printf("%lld\n",ans); //输出即可 
	return 0;
}
```


---

## 作者：Darkworldmystery (赞：0)

[原题连接](https://www.luogu.com.cn/problem/P9707)

## 题意

给给你 $l, r, k$ 三个数，求 $l!, (l - 1)!, (l - 2)!, \dots, (r - 1)!, r!$ 对 $m$ 取模的最大值。

## 思路

考虑直接求阶乘然后取模，然后在区间 $[l, r]$ 扫一遍，用 $ans$ 记录最大值即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e6 + 5;
int l, r, k, ans, dp[N];
signed main() 
{
    cin >> l >> r >> k;
    dp[1] = 1;
    for(int i = 2; i <= r; i++) 
        {dp[i] = (dp[i - 1] * i) % k;}
    for(int i = l; i <= r; i++) 
        {ans = max(ans, dp[i]);}
    cout << ans;
    return 0;
}
```

---

## 作者：JamesZhan (赞：0)

# P9707 [KMOI R1] 音波武器
## 原题链接
[P9707 KMOI R1 音波武器](https://www.luogu.com.cn/problem/P9707)
## 大致思路
因为阶乘中：
$$ x!=(x-1)!\times x$$
所以每一个声波的能量可以直接从上一个声波的能量获得，而且因为数据范围不大，所以我们可以直接枚举每个声波，再判断取模后的最大值。
```cpp
for(long long i=l;i<=r;i++){
	g=(g*(i%k))%k;
	if(g>maxn)maxn=g;
}
```
但是，我们的起始值必须老老实实算阶乘，只需并入循环即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r,k,g=1,maxn=-1;
int main(){
	scanf("%lld %lld %lld",&l,&r,&k);//记得lld
	for(long long i=1;i<=r;i++){//从1开始算阶乘
		g=(g*(i%k))%k;
		if(g>maxn&&i>=l)maxn=g;//因为阶乘并入，前面算的阶乘不计入结果
	}
	printf("%lld\n",maxn);
	return 0;
}
```
审核辛苦了，感谢观看！

---

## 作者：jqQt0220 (赞：0)

一道比较水的数学但不完全数学的题。

我们可以边乘边模。只要算出 $(l-1)!\bmod k$，然后再分别乘 $l\sim r$，乘到 $i$ 就是 $i!$，一个个找最大值就行了。但是要注意开 long long。

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//不开 long long 见祖宗
ll l,r,m,as=0;
int main()
{
    scanf("%lld%lld%lld",&l,&r,&m);
    ll s=1;
    for(int i=1;i<l;i++)
        s=(s%m)*(i%m)%m;
    for(int k=l;k<=r;k++)
    {
        s=(s%m)*(k%m)%m;
        as=max(as,s);
    }
    printf("%d",as);
    return 0;
}
```

---

## 作者：Miyamizu_Mitsuha (赞：0)

非常签到，直接暴力就行（但是还 WA 了几发）。先把左端点之前的阶乘处理出来，然后再从区间左端点乘到右端点，注意一步一乘，每次乘上一次的结果，不然每次单独拿出来处理会 T 飞。

```
#include <iostream>
#include <algorithm>
using namespace std;
#define int long long
int l, r, x;
int ans = -0x7ffffffffffffff;
int ml = 1;
signed main()
{
	cin >> l >> r >> x;
	for(int i = 1; i < l; i++)ml = (ml * i) % x;
	for(int i = l; i <= r; i++)
	{
		ml = (ml * i) % x;
		ans = max(ans, ml);
	}
	cout << ans;
  return 0;
}
```


---

## 作者：Jasoncwx (赞：0)

## 题目思路
直接按照模拟即可。

为了节省时间，我们不需要重复计算 $i!$ 的阶乘，那么我们可以使用一个变量 $sum$，初始值为 $(l-1)!$，**取一次模**。那么我们枚举 $l\sim r$ 的阶乘时，$sum\leftarrow sum\times i$，**取模后**取最大值。

最后输出最大值即可。
## 代码
```cpp
#include<iostream>
using namespace std;
int main(){
    long long l,r,k,sum=1,ans=0;
    cin>>l>>r>>k;
    for(int i=2;i<l;i++){
        sum*=i;
		sum%=k;//取模
    }
    for(int i=l;i<=r;i++){
        sum*=i;
        ans=max(ans,sum%=k);//取模后取最大值
    }
    cout<<ans;
}
```


---

## 作者：哈哈人生 (赞：0)

## 简要题意
计算 $l$ 至 $r$ 的阶乘中模 $k$ 的最大值。

## 思路
首先看一眼数据范围：$r\le 2\times 10^6$，所以我们直接暴力从 $1$ 开始计算阶乘，每一步都模 $k$ 打擂记录最大值即可。要注意两点：
1. 特判 $l=r=0$ 时，输出 $1$。
2. 从 $1$ 的阶乘开始计算，只有当 $l\le i$ 时，再打表记录。

## 代码
别忘了用长整型哦。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int l,r,k;
signed main(){
	cin>>l>>r>>k;
	if(l==0&&r==0){
		cout<<1;
		return 0;
	}
	int jc=1,maxx=-1;
	for(int i=1;i<=r;i++){
		jc*=i,jc%=k;
		if(i>=l)maxx=max(jc,maxx);
	}
	cout<<maxx;
	return 0;
}
```
站长曾经说过，不抄袭题解代码，只借鉴题解思路，但应该给题解点赞。

---

## 作者：ICU152_lowa_IS8 (赞：0)

题面应该都看过了，不多说。

由于是入门题，所以题解稍微多加了一点东西。

首先最暴力的做法就是从 $l$ 到 $r$ 挨个给阶乘算出来，然后再取模计算，代码：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int l,r,k;
	cin>>l>>r>>k;
	long long ans=0;
	for(int i=l;i<=r;i++){
		long long cnt=1;
		for(int j=1;j<=i;j++){
			cnt*=j;
		}
		ans=max(ans,cnt%k);
	}
	cout<<ans;
	return 0;
}

```

别急，显然拿不到满分（虽然 $40$ 也不错了），原因是啥应该不要我多说了吧，进行第一轮修改：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int l,r,k;
	cin>>l>>r>>k;
	long long ans=0;
	for(int i=l;i<=r;i++){
		long long cnt=1;
		for(int j=1;j<=i;j++){
			cnt*=j;
			cnt%=k;
		}
		ans=max(ans,cnt);
	}
	cout<<ans;
	return 0;
}

```
仍旧只有 $50$ 分，剩下 $5$ 个点全部超时了，这时看向数据范围：

$1\leq l,r\leq2\times10^6$。

显然对于每一个 $l\leq i\leq r$ 的 $i$，$i!$ 可以直接由 $(i-1)!\times i$ 得到，所以我们可以直接从 $(i-1)!$ 的 $cnt$ 中乘一次 $i$ 并取模来计算出 $i!$ 的 $cnt$。

代码如下：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int l,r,k;
	cin>>l>>r>>k;
	long long cnt=1,ans=0;
	for(int i=2;i<l;i++){
		cnt=cnt*i%k;
	}
	for(int i=l;i<=r;i++){
		cnt=cnt*i%k;
		ans=max(ans,cnt);
	}
	cout<<ans;
	return 0;
}
```


---

