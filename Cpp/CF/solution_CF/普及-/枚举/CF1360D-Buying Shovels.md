# Buying Shovels

## 题目描述

Polycarp wants to buy exactly $ n $ shovels. The shop sells packages with shovels. The store has $ k $ types of packages: the package of the $ i $ -th type consists of exactly $ i $ shovels ( $ 1 \le i \le k $ ). The store has an infinite number of packages of each type.

Polycarp wants to choose one type of packages and then buy several (one or more) packages of this type. What is the smallest number of packages Polycarp will have to buy to get exactly $ n $ shovels?

For example, if $ n=8 $ and $ k=7 $ , then Polycarp will buy $ 2 $ packages of $ 4 $ shovels.

Help Polycarp find the minimum number of packages that he needs to buy, given that he:

- will buy exactly $ n $ shovels in total;
- the sizes of all packages he will buy are all the same and the number of shovels in each package is an integer from $ 1 $ to $ k $ , inclusive.

## 说明/提示

The answer to the first test case was explained in the statement.

In the second test case, there is only one way to buy $ 8 $ shovels — $ 8 $ packages of one shovel.

In the third test case, you need to buy a $ 1 $ package of $ 6 $ shovels.

## 样例 #1

### 输入

```
5
8 7
8 1
6 10
999999733 999999732
999999733 999999733```

### 输出

```
2
8
1
999999733
1```

# 题解

## 作者：丧黑福造 (赞：8)

题目大意：求$[1,k]$之间最大的$n$的因数，输出$n$除以这个数

分析:因为要求的是最大的$n$的因数，因此顺序循环最后输出的一定是**最小值**

代码：

```cpp
#include <stdio.h>
inline int min (int x, int y) {
	return x < y ? x : y;
}
main() {
	int t;
	scanf ("%d", &t);
	while (t --) {
		int ans = 0x7fffffff;//先给ans赋一个很大的数
		int n, k;
		scanf ("%d %d", &n, &k);
		for (register int i = 1; i * i <= n; i ++) {//n的最大因数为sqrt(n)
			if (n % i == 0){//两种情况
				if (i <= k)
					ans = min (ans, n/i);
				if (n/i <= k)
					ans = min (ans, i);
			}
		}
		printf ("%d\n", ans);
	}
	return 0;
}

```

**~~点个赞呗~~**

---

## 作者：andyli (赞：4)

可先将 $n$ 的所有因数中不超过 $k$ 的求出，取最大值，也可把所有因数求出后，使用 `std::upper_bound` 找出不超过 $k$ 的最大因数。  

时间复杂度 $\mathcal O(\sqrt {n})$ 或 $\mathcal O(\sqrt{n}+\log{\text{d}(n)})$。  

两份代码如下：  

```cpp

int main() {
    int q;
    io.read(q);
    while (q--) {
        int n, k;
        io.read(n, k);
        int ans = 0;
        for (int i = 1; i * i <= n; i++)
            if (n % i == 0)
                chkmax(ans, i <= k ? i : 0, n / i <= k ? n / i : 0);
        writeln(n / ans);
    }
    return 0;
}
```


------------

```cpp
#include <vector>

int main() {
    int q;
    io.read(q);
    while (q--) {
        int n, k;
        io.read(n, k);
        std::vector<int> v;
        for (int i = 1; i * i < n; i++)
            if (n % i == 0)
                v.push_back(i);
        for (int i = sqrt(n); i >= 1; i--)
            if (n % i == 0)
                v.push_back(n / i);
        writeln(n / *--std::upper_bound(v.begin(), v.end(), k));
    }
    return 0;
}
```


---

## 作者：_GW_ (赞：2)

## 思路
数量是恰好是 $n$！！！

观察到 $n$ 和 $k$ 都很大，且还是多组测试数据，要么根号要么 $\log$。

看到要求恰好是 $n$，并且只能选一种包裹，那么选择的包裹中物品的个数不就是 $n$ 的因数吗？

要求购买次数最小，即可转换成求 $n$ 的最大的且小于 $k$ 的因数。

$AC$~

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=10010;
int a[N],num,ans,data,T,n,m;
bool vis[N];
int x,y,xa,ya;
void check()
{
    vector<int> v;
    for(int i=1;i<=sqrt(n);i++)
    {
        if(n%i==0)
        {
            v.push_back(i);
            if(i*i!=n) v.push_back(n/i);//埃氏筛
        }
    }
    sort(v.begin(),v.end());
    for(int i=v.size()-1;i>=0;i--)
    {
        if(v[i]<=m)
        {
            cout<<n/v[i]<<endl;//求n的最大符合要求因数。
            return;
        }
    }
}
int main()
{
    cin>>T;
    while(T--)//多组测试数据。
    {
        cin>>n>>m;
        check();
    }
    return 0;
}
```


---

## 作者：Warriors_Cat (赞：2)

## CF1360D

将这道题的题意简化一下：

在 $1$ 到 $k$ 中选出 $n$ 的最大因数，答案为 $n$ 除以这个数。

首先我们将 $n$ 分解质因数，时间复杂度为 $O(\sqrt n)$。

接着把所有因数排个序，用一下 `algorithm` 里面的 `upper_bound` 找一下最小的大于 $k$ 的因数，那么前一个就是最大的小于等于 $k$ 的因数了。

代码实现不难，注意多测清空数组即可。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
#define F(i, a, b) for(int i = a; i <= b; ++i)
#define R(i, a, b) for(int i = a; i >= b; --i)
int t, n, k, a[100010], len;
int main(){
	t = read();
	while(t--){
		n = read(); k = read();
		memset(a, 0, sizeof(a)); len = 0;
		for(int i = 1; i * i <= n; ++i){
			if(i * i == n) a[++len] = i;
			else if(n % i == 0){
				a[++len] = i;
				a[++len] = n / i;
			}
		}
		sort(a + 1, a + len + 1);
		a[len + 1] = 0x7fffffff;
		int idx = upper_bound(a + 1, a + len + 1, k) - a - 1;
		printf("%d\n", n / a[idx]);
	}
	return 0;
}

```


---

## 作者：Tarsal (赞：2)

这题确实没什么好讲的= =

如果 $k >= n$ 那么肯定是取 $i == n$ 此时答案为 $1$

如果 $k < n$ 就找出 $n$ 小于 $k$ 的最大因子
```
Rep(i, 1, sqrt(n)) {
	if(n % i == 0 && i <= k) now = n / i;//如果i是因子，那么n/i也是因子，先把i存下来，防止k < sqrt(n)
	if(n % i == 0 && n / i <= k) { flag = 1; printf("%d\n", i); break;}//因为是从头枚举的，所以i == n / i 时最大
```


```
#include <bits/stdc++.h>
#define inc(i) (++ (i))
#define dec(i) (-- (i))
#define Next(i, u) for(register int i = head[u]; i ; i = e[i].nxt)
#define Rep(i, a, b) for(register int i = (a) , i##Limit = (b) ; i <= i##Limit ; inc(i))
#define Dep(i, a, b) for(register int i = (a) , i##Limit = (b) ; i >= i##Limit ; dec(i))
using namespace std;
inline int read() {
    register int x = 0, f = 1; register char c = getchar();
    while(c < '0' || c > '9') {if(c == '-') f = -1;c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar(); 
    return x * f;
}
signed main() { int T = read();
	while(T --) { int n = read(), k = read(), now = -1, flag = 0;
		if(k >= n) { puts("1"); continue;}
		else {
			Rep(i, 1, sqrt(n)) {
				if(n % i == 0 && i <= k) now = n / i;
				if(n % i == 0 && n / i <= k) { flag = 1; printf("%d\n", i); break;}
			}
		}
		if(flag == 0) printf("%d\n", now != -1 ? now : n);
	} 
	return 0;
}

```

---

## 作者：jasonshen_ (赞：1)

## 解题思路

首先观察数据范围，$1 \le k , n \le 10^9$，暴力枚举已经不现实了，需要想出更优秀的算法。

从数据规模入手：

 $$\begin{aligned} &n \leq 10^9\\ &k \leq 10^9 \end{aligned}$$

可以推测：对于一个数 $n$，买 $k$ 支铲子包肯定太多（针对特定的 $n$ 和 $k$ 能否证明一下呢？欢迎评论区讨论一下），因此所购买的包装物品数量最大值 $\geq1$，最小值 $\leq\sqrt{n}$。

考虑如下方法：

对于每个数  $i (1 \le i \le \sqrt{n})$，计算 $n / i$。显然如果 $i$ 是 $n$ 的因数之一，那么  $t \times i$（ $t$  为任意数）也是 $n$ 的因子之一。记  $x=n/i$，则共需要购买 $(x - n/x) \times i$ 个包装物品。

选出这些包装物品总量中最小的即可。

该算法时间复杂度为 $\sqrt{n}$，可以通过本题。

## C++ 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int t, n, k;

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> k;
        int ans = n;
        for (int i = 1; i <= sqrt(n); ++i)
            if (n % i == 0) {
                if (i <= k)
                    ans = min(ans, n / i);
                if (n / i <= k)
                    ans = min(ans, i);
            }
        cout << ans << endl;
    }
    return 0;
}
```

时间复杂度 $O(t\sqrt{n})$，可以通过本题。

---

## 作者：__HHX__ (赞：1)

# 大意
给定 $k$ 和 $n$ 求出最大的 $i (i$ 为 $n$ 的因数,并且 $i\le k)$。
# 思路
## 思路推导
看到因数我们不免想到质数筛，

因为质数都是看除它与 $1$ 以外的数字有没有其他的因数。

在看到此题，就感到与质数筛没有太大的区别，都是**枚举因数**。

但是**不能用** $O(n)$ 的时间复杂度筛。

因为 $n(1\le n\le 10^9)$，再加上 $t$ 组数据那更不敢想。

所以我们要找到一个**非线性**的算法。

接下来有请一个十分重要的公式：

积数 $=$ 因数 $\times$ 因数。

这样我们就知道一个因数就可以**求出另一个因数**。

就减少了枚举另一数的时间了，道理我都懂，但要**怎么枚举**呢？

只要**枚举到** $\sqrt n$ 就可以了。

**为什么呢？**

我们可以尝试手写出一些数（不建议使用质数）的因数，然后从 $1$ 开始向后~~划~~并且~~划掉~~这个数对应的因数。

你会发现**最中间**的 $1$ 或 $2$ 个数是最后~~划掉~~的，你跟会发现这些数**近似**或**等于** $\sqrt n$。

这是又是**为什么**呢？

我现在令 $\sqrt n$ 为 $n$ 的因数，那 $n=\sqrt n\times\sqrt n$。

那 $n$ 此时就**不用向后枚举了**。

## 限定条件

因为我们是**枚举因数**，所以我们只需**枚举到** $\sqrt n$。

但**必须满足** $i\le k$ 这个限定条件。

## 答案判断

因为要令 $i$ **最大**，所以我们要取这两个**因数**中**最大**且**符合条件**的就可以了。

到此思路就结束了。

# 代码实现

```cpp
#include<iostream>
using namespace std;

int main(){
	int t;
	cin>>t;
	while(t--)
	{
		int n,k,maxx;
		cin>>n>>k;
		maxx=-1;//一定要赋值(局部变量) 0与-1一下都可以 
		for(int i=1;i*i<=n&&i<=k;i++)//i*i=n->i^2=n->i=sqrt(n)因为sqrt要开cmath所以就用i*i喽 
		{
			if(n%i==0)//如果i是因数 
			{
				maxx=(n/i<=k?max(maxx,n/i):max(maxx,i));
				/*
				三目运算符?:
				与if,else类似
				如果另一个因数(n/i)满足小于k条件
				就选另一个因数(n/i)
				否则选本来的因数(i)(i是已经小于k的故不判)
				*/
			}
		}
		cout<<n/maxx<<endl;//用此数除以最大且符合条件的因数
	}
} 
```

---

## 作者：2021changqing52 (赞：1)

#### 大意：在 $1$ 到 $k$ 之间求一个 $n$ 的因数，输出 $n$ 除以这个数。

注意不能从 $1$ 到 $k$ 进行枚举，要枚举 $n$ 的因数，小于等于 $k$ 的就更新最小值。

### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		int ans=INT_MAX;
		for(int i=1;i<=sqrt(n);i++){//枚举到sqrt(n)就行了
			if(n%i==0){//两种情况
				if(i<=k)ans=min(ans,n/i);
				if(n/i<=k)ans=min(ans,i);
			}
		}
		cout<<ans<<endl;
	}
    return 0;
}

```

---

## 作者：togeth1 (赞：1)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF1360D)

### [题意解析]
有 $t$ 个问题，每个问题中第 $i$ 种包裹有 $i$ 个物品，有 $k$ 个包裹，现在需要恰好买 $n$ 个物品且只能购买一种包裹，但可以购买无数次，求最少的购买次数。

### [思路分析]
简化一下题目意思，这道题就变成了：求 $1∼k$ 之间最小因数。但我们想题目要求的这个因数是必须要 $\leq k$ 的，**所以我们与其去 $1∼k$ 里找因数，不如去 $1∼n$ 里找那个合法因数**。而在 $1∼n$ 之间找最小的合法因数就不需要我多说了，**但小心因数是成对出现的**。

### [贴上代码]
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k,mn;
void work(){
	/* i*i<=n 会比 i<=sqrt(n) 节省一些时间*/
	for(int i=1; i*i<=n; i++){
		/*我们只用枚举到n的开方就好了*/
		if(n%i==0){
			if(n/i<=k)mn=min(mn,i);
			if(i<=k)mn=min(mn,n/i);
			/*因数是成对出现的，除了 i 这个因数，还有 n/i 这个因数*/
		}
	}
}
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		mn=2147483647;
		/*设一个初始值*/
		work();
		/*找因数*/
		cout<<mn<<"\n";
	}
	return 0;
}
```


---

## 作者：Aehnuwx (赞：1)

### 题目大意
- 有 $k$ 种包裹
- 第 $i$ 种包裹中有 $i$ 个物品（$1\le i\le k$）
- 需要购买 **恰好** $n$ 个物品
- 只能购买一种包裹，但是可以购买无数次该包裹
- 问最少的购买次数

### 解法

设 $m=\min\{\lfloor \sqrt{n}\rfloor,k\}$，其意义是买若干次包裹后 $\ $ **可能** 得到 **恰好** $n$ 个物品 $\ $ 的最小购买次数 的最大值（因为若有一个数 $a$ 是 $n$ 的因子，必然有 $a\le \lfloor\sqrt{n}\rfloor$）。

故从 $1\sim m$ 枚举，统计答案即可。复杂度 $t\sqrt{n}$。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
const int INF=0x3f3f3f3f;
//const ll INF=0x3f3f3f3f3f3f3f3fll;
using namespace std;
void rdt(int&),solve();
int check(int);
int n,k;
int main() {
    int t; rdt(t);
    for (;t;t--) solve();
    return 0;
}
void rdt(int& t) {
    //t=1;
    scanf("%d",&t);
}
void solve() {
    scanf("%d%d",&n,&k);
    if (k>=n) {puts("1"); return;}
    int m=min((int) sqrt(n),k);
    printf("%d\n",check(m));
}
int check(int nn) {
    int ret=INF;
    for (int i=nn;i;i--) {
        if (n%i) continue;
        int x=i,y=n/i;
        ret=min(ret,n/x);
        if (y<=k) ret=min(ret,n/y);
    }
    return ret;
}
```


---

## 作者：Pink_Cut_Tree (赞：1)

# CF1360D Buying Shovels 题解

### 题目大意

题中的翻译已经给得很清楚了，无需过多解释。算法也很容易想出来。即依次枚举 $1 \sim n$ 判断是否是 $n$ 的因数即可。但是——很不幸，这个算法 TLE 了。

### 坑点

注意到题中 $1 \leq n \leq 10^9$ 和 $1 \leq k \leq 10^9$，暴力枚举 $1 \sim n$ 的情况肯定不行。那怎么办呢？

想到要求的是 $n$ 的因数中的最大值，那么只需枚举到 $\sqrt n$ 即可（想想质数筛的过程），这题就迎刃而解了，时间复杂度 $O( t \sqrt n )$，可以通过本题。

### 代码

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int t,n,k;
int main(){
	ios::sync_with_stdio(0); //关闭读写同步
	cin>>t;
	while(t--){
		cin>>n>>k;
		int ans=n;
		for(int i=1;i<=sqrt(n);++i){
			if(n%i==0){ //是因数 
				if(i<=k){
					ans=min(ans,n/i);
				}
				if(n/i<=k){ //这里不能用else 
					ans=min(ans,i);
				}
			} 
		}
		cout<<ans<<"\n"; //输出
	}
return 0;
}
```


---

## 作者：01Dragon (赞：0)

### 题意
给定 $n$ 和 $k$，求 $n$ 除以 $n$ 的 $k$ 以内的最大因数的商。
### 思路
一个数的因数都是成对出现的。所以只需要从 $1$ 循环到 $\sqrt n$，找到 $n$ 的因数，再将这个因数和其对应的因数得到的结果取最小值记录下来即可。别忘了有 $t$ 组数据。
### 代码
```cpp
#include<iostream> 
#include<cstdio> 
#include<algorithm> 
#include<cmath> 
#include<deque> 
#include<vector> 
#include<queue> 
#include<string> 
#include<cstring> 
#include<map> 
#include<stack> 
#include<set> 
using namespace std;
int t,n,k,ans;
int main()
{
	cin>>t;
	for(int i=0;i<t;i++)
	{
		cin>>n>>k;
		ans=n;//ans一定小于等于n
		for(int j=1;j*j<=n;j++)
		{
			if(n%j==0)//如果是n的因数
			{
				if(j<=k)
				{
					ans=min(ans,n/j);
				}
				if(n/j<=k)
				{
					ans=min(ans,j);
				}
			} 
		}
		cout<<ans<<endl;
	}
	return 0;
} 
```


---

## 作者：19x31 (赞：0)

## 题意
本题给出 $n$ 和 $k$，求 $1$ 到 $n$ 之间 $k$ 的最小因数。因为题目要求只能买一种包裹，还要求购买次数最小，所以答案固然是 $1$ 到 $n$ 之间 $k$ 的最小因数。

## 思路
先看数据大小，$1 \le k \le 10^9$，枚举 $O(k)$ 会超时，那么不妨换个思路，枚举 $1$ 到 $\sqrt n$，看看 $i$ 和 $n \div i$ 是否为 $k$ 的因数并储存最小值即可。时间复杂度 $O(\sqrt n)$，不超时。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,k,s;
int main(){
	cin>>s;
	while(s--){
		cin>>n>>k;
		int mina=INT_MAX;//记得初始化 
		for(int i=1;i<=sqrt(n);i++){
			if(i<=k&&n%i==0){
  				mina=min(mina,n/i);
  			}
			if((n/i)<=k&&n%i==0){
                mina=min(mina,i);
			}//判断i和n/i是否为n的因数且小于k 
		cout<<minn<<endl;
	}
    return 0;
}
```


---

## 作者：The_FAKIR (赞：0)

## 大意
求从 $1$ 到 $k$ 之间 $n$ 的最小因数。
## 分析
从 $1$ 到 $n$ 的开方依次查找 $i$ 和 $n/i$ 有没有小于 $k$，再用一个变量储存一下最小值就好了。由于 $n$ 小于 $10^9$，所以不用担心超时。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t,minn,l;
int main(){
	cin>>l;
	for(int i=1;i<=l;i++){
		cin>>n>>k;
		minn=INT_MAX;
		for(int i=1;i<=sqrt(n);i++){
			if(i<=k&&n%i==0) minn=min(minn,n/i);
			if(n/i<=k&&n%i==0) minn=min(minn,i);
		}
		cout<<minn<<endl;
	}
    return 0;
}
```


---

## 作者：liukangyi (赞：0)

# 题目大意
给你 $T$ 组样例，每组样例中有个数 $n$，代表有 $n$ 个物品需购买，还有一个数 $k$，代表有 $k$ 种包裹，每个包裹只有对应种类数件物品。现在你只能购买其中**一种**包裹，请你求出**最少的购买次数**。


------------
# 分析
我们先将题目简化一下：其实就是要使得两个数的**乘积**为 $n$，而且其中一个数要小于等于 $k$，因为它是购买 $k$ 个包裹里面的一种包裹若干次，而第 $i$ 个包裹里只有 $i$ 件物品，最多只有 $k$ 个物品，所以应有一数小于等于 $k$。根据上述分析，我们做这道题就完全可以枚举 $n$ 的因数，并且利用一数从而求出**另一个因数**，然后分别判断两个因数能否作为**包裹里面的物件数**，同时更新最小值即可。


------------
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n,k;
//定义变量 
int main(){
    cin>>T;
    while(T--){
    	scanf("%d%d",&n,&k);
    	int ans=INT_MAX; //初始化最少的购买次数
		//枚举n的约数 
    	for(int i=1;i*i<=n;i++){ 
    		if(n%i!=0)
    			continue;
    		//如果枚举数i不是n的因数，则进行下一个循环 
    		int tmp=n/i;
    		if(tmp<=k) //如果另一个因数可以作为k个物品中的一种 
    			ans=min(ans,i);
    		if(i<=k) //如果当前因数可以作为k个物品中的一种 
    			ans=min(ans,tmp);
    	}
    	cout<<ans<<'\n';
    } 
    return 0;
}
```


---

## 作者：lmndiscyhyzdxss (赞：0)

## 题目大意
题目大意：有 $ k $ 种包裹，第 $ i $ 种包裹有 $ i $ 个物品 $ (1 \leq i \leq k ) $，现在需要恰好买 $ n $ 个物品，只能购买一种包裹，但可以购买无数次，求最少的购买次数。
## 题目分析
因为只能选一种包裹，且恰好要买完 $ n $ 个物品，也就是选第 $ i $ 个包裹的个数是 $ n $ 的因数，还要保证 $ i \leq k $ 且最大。

当然，如果直接枚举从 $ 1 \sim k $ 的数，时间复杂度为 $ O(k) $，相必是不行的。我们不如反其道而行之，枚举 $ 1 \sim n $ 的数,当然也不行，得想办法优化。

如果 $ a\times b=n $，则 $ a $ 和 $ b $ 都是 $ n $ 的因数，枚举时只需要枚举 $ \min(a,b) $ 即可，这个值最小为 $ \sqrt n $，只需要枚举到这个值就可以了，顺便判断一下是否小于 $ k $ 并记录个数最小值即可。

注意：枚举时，$ i $ 和 $ n \div i $ 都要判断，且记得最小值初始化。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,mi;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>n>>k,mi=2147483647;//输入和初始化
		for(int j=1;j<=sqrt(n);j++)
		{
			if(n%j==0)//当可以整除
			{
				if(j<=k)mi=min(mi,n/j);//第一种情况
				if(n/j<=k)mi=min(mi,j);//第二种情况
			}
		}
		cout<<mi<<endl;
	}
	return 0;
}
```


---

## 作者：j1ANGFeng (赞：0)

### 题意
求 $n$ 最大且不大于 $k$ 的因子，求 $n$ 除以这个数。
### 分析
枚举 $n$ 的因子，寻找最小的因子且 $n$ 除以这个数不大于 $k$。

### AC CODE
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<cmath>
#define ll long long
#define N 10000001
#define inf 2147483647
#define in inline
#define re register
using namespace std;
inline long long rd(){char a=getchar();long long f=1,x=0;while(a<'0'||a>'9'){if(a=='-')f=-1;a=getchar();}while(a>='0'&&a<='9'){x=(x<<3)+(x<<1)+(long(a^48));a=getchar();}return f*x;}in void qwqqwq(long long x){if(x!=0){qwqqwq(x/10);putchar(x%10^48);}return;}inline void wt(long long x){if(x==0){putchar('0');return;}if(x<0){x=-x;putchar('-');}qwqqwq(x);return;}

signed main(){
	int t=rd()+1;
	while(--t){
		int n=rd(),k=rd(),ans=inf;
		int qwq=sqrt(n);
		for(int i=1;i<=qwq;++i){
			if(n%i==0){
				if(i<=k&&ans>n/i)
				  ans=n/i;
				if(n/i<=k&&ans>i)
				  ans=i;
			}
		}
		wt(ans);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：rui_er (赞：0)

这一题数据不大，想到暴力 $\sqrt{n}$ 求出 $k$ 以内的最大因数，然后输出 $n\div k$ 即可。

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;

int T, n, k;

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &k);
		int ma = 1;
		for(int i=sqrt(n);i>=1;i--) {
//			printf("%d %d %d %d\n", i, n%i, n/i, k);
			if(n % i != 0) continue;
			int a = i, b = n / i;
			if(a <= k) ma = max(ma, a);
			if(b <= k) ma = max(ma, b);
		}
		printf("%d\n", n/ma);
	}
	return 0;
}
```

---

## 作者：zhanghaosong (赞：0)

# CF1360D Buying Shovels 题解

### 分析

观察“只能购买一种包裹，但可以购买无数次”这一句话，这就告诉我们本题是来找 $n$ 的最小因数。

### 小坑点

观察数据范围，$ 1 \leq i$ $ \leq k $，这告诉我们我们没法依次从 $1$ 枚举到 $n$，但是没事，由于因数成对出现，只需枚举到 $ \sqrt n$ 即可。

### 附上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k;
int main(){
	cin>>T;
	for(int i=1;i<=T;i++){ //也可写成 while(T--) 
		cin>>n>>k;
		int ans=n;
		for(int j=1;j<=sqrt(n);j++){
			if(n%j==0){
				if(j<=k){
					ans=min(ans,n/j);
				}
				if(n/j<=k){
					ans=min(ans,j); //除了 i 这个因数，还有 n/i 这个因数
				}
			} 
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：scplzy (赞：0)

# 题目大意
就是让我们用代码求出 $1$ ~ $s$ 中 $n$ 的最小因数。
## 想法
从 $1$ 开始到 $n$ 的开方，考虑 $i$ 或 $n\div i$ 是否小于等于 $k$ ，如果条件达成，那么用个变量存储最小值。 
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,t,zx,l;
int main(){
	cin>>l;
	for(int i=1;i<=l;i++)
	{
		cin>>n>>s;
		zx=INT_MAX;
		for(int i=1;i<=sqrt(n);i++)
		{
			if(i<=s&&n%i==0) 
				zx=min(zx,n/i);
			if(n/i<=s&&n%i==0) 
				zx=min(zx,i);
		}
		cout<<zx<<endl;
	}
    return 0;
}
```


---

