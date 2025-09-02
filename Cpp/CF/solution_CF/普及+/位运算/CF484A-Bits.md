# Bits

## 题目描述

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 说明/提示

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 样例 #1

### 输入

```
3
1 2
2 4
1 10
```

### 输出

```
1
3
7
```

# 题解

## 作者：XiXi (赞：27)

## [题目链接](https://www.luogu.org/problemnew/show/CF484A)



## 题目大意
给**T**组询问，每次给你两个数**l**和**r**，求出**l**到**r**之间的在二进制下“**1**”个数最多的数（如果有一样的输出最小的即可）

如**1**到**10**之间，在二进制“**1**”最多的数是**7**

## 思路
像这种求极值的很容易想到贪心，因为“**1**”的个数要尽量多并且该数不能超过**r**，所以低位要尽可能多的放“**1**”

因为要大于**l**，所以可以从低往高位直接判断**l**的每一位是否为“**1**”，如果不是，就把这一位变成“**1**”，在代码实现中可用“|”来解决，但要小心可能会大于**r**

~~我才不会说我第一次还想着根据判断**l**和**r**的一些玄学关系来做这题呢~~

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,l,r,i;
int main()
{
    scanf("%lld",&T);  //读入T
    while (T--)
    {
    	scanf("%lld%lld",&l,&r);  //读入l和r
    	for (i=1;(l|i)<=r;i<<=1) l|=i;  //l或上2^x
    	printf("%lld\n",l);
	}
}
```

~~厚颜无耻地求个赞~~

---

## 作者：EuphoricStar (赞：3)

由于题目求 $1$ 的个数**最多** 且 **最小** 的那个数，不难想到这样的贪心策略：

从最低位开始（二进制），每次尝试将 $l$ 的当前位变为 $1$。如果变为 $1$ 后会大于右边界 $r$，则终止循环，输出当前的 $l$。

###### ~~双倍经验：[P2431 正妹吃月饼](https://www.luogu.com.cn/problem/P2431)~~

核心代码仅两行：

```cpp
        ull t = 1;
        while ((l | t) <= r) l |= t, t <<= 1;
```

注：`|` 为按位或运算符，对于参与运算的两个数，只要对应的二进制位都为 $1$，结果的该位就为 $1$；`<<` 是左移运算符，其功能相当于 `*2`。

---

## 作者：_cmh (赞：3)

真是一道好题。

这题的思路非常的妙，因为要让你求区间内二进制表示中 $1$ 的个数最多的数，并且要最小，我们可以考虑 $l$ 二进制表示中，将是 $0$ 的数位改写成 $1$ ，并且需要在每次改写前判断改写后是否大于 $r$ ，大于即终止。

改写的过程可以用位运算中的 `|`（按位或运算，$\bm {or}$，只要两位中有 $1$ ，最后结果就是 $1$ ，否则为 $0$ 。）

**注意开 $long\ long$（我用 $unsigned\ long\ long$），而且用 $cin$ 会 $TLE$ 。**

上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
unsigned long long T,l,r;
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&l,&r);
		for(unsigned long long i=1;(l|i)<=r;i<<=1) l|=i;
		printf("%lld\n",l);
	}
    return 0;
}
```

是的你没看错，实现代码就这么短~

求赞！

---

## 作者：SIXIANG32 (赞：2)

其实这道题还真不难吧（雾都  
闲话少说，切入正题——

---
首先我们看到转换成二进制最多个 $1$，又联想到 CF 的出题风格，可以想到这道题不是找，而是构造一个（确信  
~~CF 不就是构造专区吗（~~  
所以我们来考虑一下怎么构造。我们要找一个最小的还大于等于 $l$ 小于等于 $r$ 的数，就从 $l$ 开始，在二进制的情况下从最低位疯狂变 $1$ 变到某个位置大于 $r$ 了才停下。  

怎么按位变 $1$ 呢？毕竟 $l$ 已经有一些 $1$ 了，不能重复加。这个时候我们就可以用 $l|(1 << p)$ 来完成，$|$ 是位运算或，两个为 $1$ 的位或为 $1$，一个 $0$ 一个 $1$ 或仍然是 $1$，$(1 << p)$ 是将 $1$ 左移 $p$ 位。当要或的数字仅第 $p$ 位为 $1$，那被或的数字那一位肯定也会变为 $1$。  

---
最后，由于 $1\le l \le r \le 10^{18}$，所以我们要开 ```long long```。  
这个程序的复杂度可以说接近 $\log_2 len$ 了。~~具体多少我懒得算~~

---
上代码：  
```cpp
#include <iostream> 
#define MAXN 1e5
#define qwq printf("qwq\n");
#define int long long
using namespace std;
int solve(int l, int r) {
	int ans = l;
	for(int p = 1; (ans | p) <= r; p <<= 1)
		ans |= p;
	return ans;
}
signed main() {
	int n;
	cin >> n;
	while(n--) {
		int l, r;
		cin >> l >> r;
		cout << solve(l, r) << endl;
	}
}
```

---

## 作者：agicy (赞：1)

# 题意

-  $n$ 组询问，每次给出一个区间 $l, r$ ，你需要输出在这个区间内二进制表示中$1$的个数最多的数

- 如有多个答案，输出最小的那个

-  $(n \leq10^4, 0\leq l, r \leq10^{18})$ 

来自@龙_之_谷 。

## 题面源代码

```
-  $n$ 组询问，每次给出一个区间 $l, r$ ，你需要输出在这个区间内二进制表示中$1$的个数最多的数

- 如有多个答案，输出最小的那个

-  $(n \leq10^4, 0\leq l, r \leq10^{18})$ 
```

# 思路

很明显，要求在区间\[$l,r$\]中，二进制表示中$1$的个数最多的数，我们只需要将数$l$最低的为$0$位改为$1$即可。

## 关于求最低的为$0$位

如果我们将一个数按位取反，则它最低的为$1$位，就是原数最低的为$0$位。

而求一个数$j$最低的为$1$位，我们可以这样：

```cpp
j&-j;
```

所以，我们可以这样表示将一个数$j$的最低为$0$位改为￥$1$。

```cpp
j+=(~j&(-~j);
```

# 代码

代码如下。

```cpp
#include<stdio.h>

long long n,l,r;//记得使用long long

int main(void){
	register int i;
	register long long j,ans;
	scanf("%lld",&n);
	for(i=1;i<=n;i++){
		scanf("%lld%lld",&l,&r);
		for(j=l;j<=r;j+=(~j&(-~j)))//不断增加
			ans=j;//赋值
		printf("%lld\n",ans);//输出，记得换行
	}
	return 0;
}
```

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF484A](https://www.luogu.com.cn/problem/CF484A)

* **【解题思路】**

看到题目，想到的第一种方法是设一个变量$n$把二进制全$1$的数枚举出来，然后一个一个比较，如果$l\leq n \leq r$，那么就更新最大值。

看了看样例，我觉得我的想法是对的。$\color{white}\tiny{\sout{\text{话说CF的样例真的一点强度都没有啊}}}$

打代码打到一半，忽然发现：

如果$l=r$且$l$的二进制表示并非全$1$怎么办？特判就行了！

可是我又发现了另一个反例：

```
1
1048500 1048575
```

$l$和$r$靠的太近怎么办？

显然这种思路行不通。

再想一想：题目是求$\operatorname{popcount(n)}$的最大值，没说一定是全$1$啊。

那么，我们只要用暴力枚举试试最大可以有几个$1$就行了。但是，显然这种方法会超时（复杂度$\Theta(2^{63})$）。

再想想，这不就是一个贪心吗？

因为把$l$加一个$2$的次幂就可以把$l$相应的位变成$1$（前提是原来这位是$0$），那么我们只要把$l$的二进制表示从低到高一位位变成$1$不就能让$l$在二进制表示最多的情况下最小了吗？

所以，我们只要按上面的方法操作直到操作后的$l$会大于$r$为止，然后输出$l$就行了。

* **【代码实现】**

```cpp
#include <iostream>

using namespace std;

int main(int argc,char *argv[],char *env[])
{
	unsigned long long cnt,left,right,tmp;
	cin>>cnt;
	while(cnt--)
	{
		cin>>left>>right;
		tmp=1;
		while((left|tmp)<=right)//是的，核心代码只有这个2行的while
			left|=tmp,tmp<<=1;
		cout<<left<<endl;
	}
 	return 0;
}

```

---

## 作者：xxzjbd (赞：0)

## 题意分析
给定一个区间，求区间内二进制下 $1$ 个数最多的最小值。

这道题可以用贪心求解，从 $l$ 开始向 $r$ 贪心，每次将最低位变成 $1$ ，直到大于 $r$ ，得到的第一个满足要求的数即为答案，且保证最小。

为什么呢？首先要清楚或 $( | )$ 的位运算规则是有 $1$ 则 $1$ ，也就是说当二进制的一位本身就是 $1$ 时，运算不改变数的大小，所以放心的从最低位开始运算就好了。因为从最低位开始运算，所以当两个数 $1$ 同时多时，先得到的数一定最小，且有 $n$ 个 $1$ 的数只会被贪心到一次。
## 代码如下
```cpp
#include<cstdio>
#define int unsigned long long
using namespace std;
signed main(){
	int n;
	scanf("%llu",&n);
	while(n--){
		int l,r,cnt=1;
		scanf("%llu%llu",&l,&r);
		for(int i=1;(l|cnt)<=r;i++){
			l|=cnt;
			cnt<<=1;
		}
		printf("%llu\n",l);
	}
}
```
只开 $int$ 类型会炸掉
## 谢谢观赏

---

## 作者：wzkdh (赞：0)

## 一道贪心题

我们要找出$l$到$r$中最小的包含最多$1$的数字，我们可以换一种思路，就是在l的基础上尽可能的增加$1$的数量，这样可以保证范围在$l$到$r$之间，根据贪心思想，$1$尽可能的向权值小的位上加，这样就可以保证答案最小了。

### 代码:

```#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
unsigned long long n,l,r;
int main()
{
	cin>>n;
	while(n--)
	{
		scanf("%lld%lld",&l,&r);
		for (unsigned long long i=1;(l|i)<=r;i<<=1)
			l|=i;
		printf("%llu\n",l);
	}
	return 0;
}

---

## 作者：MVP_Harry (赞：0)

来一个不同的解法。其他大佬们都是一行就解决了，我这个方法虽然复杂点，但还是很好理解的。令$f(l, r)$为对于$l, r$的解，并规定$d = bits(x)$为最大的整数满足$2^d \le x$。对于$x, y,$ 此时分几种情况讨论：

1. $x = y,$ 则$f(l, r) = l.$
2. 若$y = 2^{bits(y) + 1} - 1,$ 则$y$肯定就是我们要的最优解。
3. 若$bits(x) < bits(y),$ 则 $2 ^ {bits(y)} - 1$ 为最优解。
4. 否则，$bits(x) = bits(y)$，则我们必须取最高位，并可以递归为$2^{bits(x)} + f(l - 2^{bits(x)}, r - 2^{bits(x)}).$

不难写出以下程序：

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long

int find_length(ll x) {
	for (int i = 0; ; i++) 
		if ((ll) ((ll) 1 << i) > x) return i; 
}

ll solve(ll l, ll r) {
	int len1 = find_length(l), len2 = find_length(r); 
	// -> l >= 2 ^ len1 & r >= 2 ^ len2; 
	if (l == r) return l; 
	if (r == (ll) ((ll) 1 << (len2)) - 1) return r; 
	if (len2 > len1) return (ll) ((ll) 1 << (len2 - 1)) - 1;
	return (ll) ((ll) 1 << (len1 - 1)) + solve(l - ((ll) 1 << (len1 - 1)), r - ((ll) 1 << (len1 - 1))); 
} 

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0); 
	int T;
	cin >> T;
	while (T--) {
		ll l, r;
		cin >> l >> r;
		cout << solve(l, r) << "\n"; 
	}    
	return 0; 
}
```


---

## 作者：__Hacheylight__ (赞：0)

题意：

求在l到r中1数量最多的数。

思路：

很明显是贪心。

我们很明显发现在位权小的位置放1能够使得最终结果最少。

做法：

初始的时候是1

于是我们就从位0到iinf放1，如果>r就break

代码：

就这么短，。

```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long 
int n,l,r ;
signed main(){
	scanf("%lld",&n) ;
	while(n--){
		scanf("%lld%lld",&l,&r) ;
		for (int i=0;;i++){
			if ((l|(1ll<<i))>r) break ;
			l|=(1ll<<i) ;
		} 
		printf("%lld\n",l) ;
	} 
    return 0 ;
}
```

---

