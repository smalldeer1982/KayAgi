# 「KDOI-04」XOR Sum

## 题目背景

凯文一眼秒了这题。

![](https://cdn.luogu.com.cn/upload/image_hosting/lh1xvu75.png)

## 题目描述

给定一个正整数 $n$，请构造一个长度为 $n$ 的**非负整数**序列 $a_1,a_2,\dots,a_n$，满足：

+ 对于所有 $1\le i\le n$，都有 $0\le a_i\le m$。
+ $a_1\oplus a_2\oplus\dots\oplus a_n=k$。其中 $\oplus$ 表示[按位异或](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677)运算。

或者判断不存在这样的序列。

## 说明/提示

**【样例解释】**

对于第 $1$ 组测试数据，有且仅有一个序列满足条件。

对于第 $2$ 组测试数据，由于 $4\oplus 7=3$ 且 $4,7\le10$，所以这是一个合法的答案。同样地，序列 $(2,1)$ 也是一个合法的答案。

对于第 $4$ 组测试数据，可以证明不存在满足要求的序列。

**【数据范围】**

记 $\sum n$ 为单个测试点中所有 $n$ 的值之和。

对于所有测试数据，保证 $1\le T\le 1~000$，$1\le n\le 2\cdot10^5$，$0\le m,k\le 10^8$，$\sum n\le 2\cdot10^5$。

**【子任务】**

**本题开启捆绑测试。**

+ Subtask 1 (18 pts)：$k\le m$。
+ Subtask 2 (82 pts)：没有额外的约束条件。

## 样例 #1

### 输入

```
5
1 2 2
2 3 10
2 11 8
20 200000 99999
11 191 9810```

### 输出

```
2 
4 7 
8 3 
-1
191 191 191 191 191 191 191 191 191 191 191 ```

# 题解

## 作者：JuRuoOIer (赞：11)

# 题解 P9033 「KDOI-04」XOR Sum

UPD：介绍异或的部分及数据范围部分均按要求进行了调整。

~~好吧又是赛时唯一 AC 的题目……~~

### Part1 题意

[原题传送门](https://www.luogu.com.cn/problem/P9033)

- 给定 $n,m,k$，要求构造一个非负整数序列，长度为 $n$，所有项均不超过 $m$，且异或和为 $k$。
- $1 \le T \le 1000$，$1 \le \sum n \le 2 \times 10^5$，$0 \le m,k \le 10^8$。

### Part2 思路

#### 2-1 关于异或

首先大家要知道[异或是什么](https://oi-wiki.org/math/bit/)。


异或有一个外号，叫做**不进位加法**，因为 $0\ \text{xor}\ 0 = 0$，$1\ \text{xor}\ 1=0$，$0\ \text{xor}\ 1=1$（$0+0$ 和 $1+1$ 二进制最后一位均为 $0$）。

于是我们得出：**任何数异或 $0$ 等于其本身**。这条性质记好了，后面会用到。

#### 2-2 判无解、凑答案

接着我们看怎么得到 $k$。

既然 $k$ 只能通过不超过 $m$ 的数字异或得到，所以 $k$ 的二进制位数不能超过 $m$ 的二进制位数（显然异或没法变出新的位），即 $\lceil\log_2k\rceil \le \lceil\log_2m\rceil$，否则无解。

接下来分两种情况考虑：
- 当 $k \le m$ 时，只需要第一项赋值为 $k$，其余项均为 $0$ 即可（还记得 2-1 中的性质吗？）。
- 当 $k > m$ 时，又由于 $\lceil\log_2k\rceil \le \lceil\log_2m\rceil$，所以 $k$ 和 $m$ 位数相同。也就是说，$k$ 与 $m$ 二进制下最高位是同一位且都是 $1$。
  - 然后我们把 $k$ 最高位上的 $1$ 去掉，此时 $k$ 一定小于 $m$（因为位数减少了），一项就可以完成。
  - 而刚才去掉的 $1$ 实际上就是 $100...00$（长度同 $k,m$），一定不会超过 $m$，也需要一项完成。
  - 由于是同一个数字拆出来的，所以它们不可能在同一个位置均为 $1$。也就是说，它们两个的异或等于它们的和 $k$。

于是 $k>m$ 的情况就解决了：$n=1$ 无解，否则将 $k$ 像上面那样分成两份，后面填 $0$ 即可。

### Part3 代码

注释在代码里啦！

```cpp
#include<bits/stdc++.h>
//此处省略快读快输，见我的主页
//它将这个程序优化了约 4ms 
#define ll long long
#define ull unsigned long long
#define lf double
#define ld long double
using namespace std;
ll t,n,k,m; //意义如题面 
ll log2(ll x){//用不断除以 2 的方式求二进制长度（仅比转换成二进制少了取余，因此很明显正确） 
	ll ans=0;
	while(x){
		ans++;
		x/=2;
	}
	return ans;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k>>m;
		if(log2(m)<log2(k)){//m 的二进制长度小于 k，无解 
			cout<<"-1\n";
		}
		else if(m<k){//m<k 的情况，见 Part2-2 
			if(n==1)cout<<"-1\n";//一项不够，无解 
			else{
				cout<<(1ll<<log2(k)-1)<<' '<<k-(1ll<<log2(k)-1);//左移，1<<k 结果为 2^k 
				for(int i=0;i<n-2;i++){//补 0 
					cout<<" 0";
				}
				cout<<endl;
			}
		}
		else{
			cout<<k;
			for(int i=0;i<n-1;i++){//补 0 
				cout<<" 0";
			}
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：_determination_ (赞：3)

由于 $a_i$ 可以等于零，所以我们只需使用需要的 $a_i$ 即可，后面的全部赋值为零。

然后开始考虑怎样搞这个东西。显然多用不如少用。值能小则不会更大。

然后就可以暴力跑，对于每个 $a_i$ 我们连续的加上 $k$ 的 `lowbit` 直到再加一次就会出现 $a_i > m$ 或者 $k=0$ 的情况。

跑完后判断 $k$ 是否为零即可。

---

## 作者：佬头 (赞：3)

## Description

给定一个正整数 $n$，请构造一个长度为 $n$ 的**非负整数**序列 $a_1,a_2,\dots,a_n$，满足：
+ 对于所有 $1\le i\le n$，都有 $0\le a_i\le m$。
+ $a_1\oplus a_2\oplus\dots\oplus a_n=k$。其中 $\oplus$ 表示[**按位异或**](https://www.luogu.com.cn/problem/P9033)运算。

或者**判断不存在**这样的序列。

## Solution
感谢管理大大帮忙指出错误：下文中 $\lceil\log_2(A+1)\rceil$ 表示 $A$ 在二进制下的数位个数。

构造一个异或和等于 $k$ 的序列，首先想到构造 $\{0,0,\dots,k\}$，题目要求非负整数，显然满足条件。

但是题目中还有一个限制就是 $a_i\le m$，显然 $m\lt k$ 时以上构造方式不成立，接下来思考是否可以构造两个数 $o,p$ 使得 $o\oplus p=k$。

由于两个数异或后的值**在二进制表示下的数位个数**不会多于这两个数的任意一个，不难想到当 $\lceil\log_2(m+1)\rceil\lt\lceil\log_2 (k+1)\rceil$（即 $m$ 在二进制下的数位个数少于 $k$）时，不存在这样的序列可以构造。

此时只剩下 $\lceil\log_2(m+1)\rceil=\lceil\log_2(k+1)\rceil,m\lt k$ 的情况，那么他们是否可以用两个数来解决呢？

答案是肯定的。因为此时 $2^{\lfloor\log_2m\rfloor+1}\gt k\gt m\ge 2^{\lfloor\log_2m\rfloor}$，则我们可以先构造出一个 $2^{\lfloor\log_2m\rfloor}$，那么很明显另一个数就是 $k\oplus 2^{\lfloor\log_2m\rfloor}=k-2^{\lfloor\log_2m\rfloor}$，并且 $k-2^{\lfloor\log_2m\rfloor}\lt2^{\lfloor\log_2m\rfloor}\le m$。当然最后还要满足 $n>1$ 才行。

这是根据上述思路来判断是否存在可构造序列的 `check()` 函数，同时返回 $2^{\lfloor\log_2m\rfloor}$（$2^{\lfloor\log_2k\rfloor}$）：
```cpp
int check(int &k, int &m){
	int i;
	for(i = 0; (1 << i) <= k; ++ i) if((1 << i) > m) return 0;
	return 1 << (i - 1);
}
```
时间复杂度 $\mathcal O(T\log K+\sum n)$。

对于 `check()` 的方式以及两个数的取法，笔者在写完题解后又想到一种**更简单**的。基于上述思路，我们发现（$k\gt m\ge0$）：
- 当 $m=0$ 或 $\lceil\log_2(m+1)\rceil\lt\lceil\log_2(k+1)\rceil$ 时，$m\oplus k\ge2^{\lfloor\log_2k\rfloor}\gt m$（无法构造）。
- 当 $\lceil\log_2(m+1)\rceil=\lceil\log_2(k+1)\rceil$ 时，$m\oplus k\lt2^{\lfloor\log_2k\rfloor}\le m$；

第二种情况的构造方案就是 $\{0,0,\dots,k,m\oplus k\}$。代码时间复杂度 $\mathcal O(\sum n)$。

##
```cpp
#include <iostream>
using namespace std;
int n, k, m;
int read(){
	int x = 0;
	char a = getchar();
	while(a < '0' || '9' < a) a = getchar();
	while('0' <= a && a <= '9') x = (x << 1) + (x << 3) + (a ^ 48), a = getchar();
	return x;
}
void write(int x){
	if(x > 9) write(x / 10);
	putchar(x % 10 | 48);
}
int main(){
	for(int _ = read(); _ >= 1; _ --){
		n = read(), k = read(), m = read();
		if(k <= m){
			for(int i = 1; i < n; ++ i) fputs("0 ", stdout);
			write(k), putchar('\n');
		}
		else if((m ^ k) <= m && n > 1){
			for(int i = 2; i < n; ++ i) fputs("0 ", stdout);
			write(m), putchar(' ');
			write(m ^ k), putchar('\n');
		}
		else fputs("-1\n", stdout);
	}
	return 0;
}
```


---

## 作者：WsW_ (赞：3)

相当好玩的一个思维题，建议升黄。  

---
### 思路
有一个小性质：$x\oplus0=x$。  
所以如果我们的序列长度小于 $n$，那后面补 $0$ 就行。  

如果两个数二进制某位上都为 $1$，那么异或的结果在这一位上为 $0$。  
我们要序列中所有的 $a_i\le m$，那么我们就要避免某一位上重复出现 $1$ 的情况。  
因为重复出现不会对最终的异或积产生任何贡献，而且这会使某个 $a_i$ 变大。  

到这里就很明显了，我们将 $k$ 二进制拆分，然后再组装起来。  
例如 $11011_2$，我们将其拆分成 $10000_2,1000_2,10_2,1_2$ 四个数字，再组装起来。  
我们要使最大的尽可能小，而显然，无论怎么分最大的至少都为 $100000_2$，而且另外其他数字全组装在一起也没它大。  

所以只要把拆出来的数**从小到大**组装起来，贪心让组装出来的数尽可能大。  

可以用 $\operatorname{lowbit}$ 辅助拆分。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) (x&-x)
int T;
int n,k,m;
int x,cnt;
int ans[200003],al;

void work(){
	cin>>n>>k>>m;
	al=0;
	while(k){
		x=0;
		while(k>0&&x+lowbit(k)<=m){
			x+=lowbit(k);
			k-=lowbit(k);
		}
		ans[++al]=x;
		if(al>n){
			cout<<"-1";
			return;
		}
	}
	for(int i=1;i<=al;i++)cout<<ans[i]<<' ';
	for(int i=al+1;i<=n;i++)cout<<"0 ";
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		work();
		cout<<'\n';
	}
	return 0;
}
```

---
### 评分
好玩且新颖。

---

## 作者：Moon_Traveller (赞：2)

[> 传送门 <](https://www.luogu.com.cn/problem/P9033)

~~很暴力的做法，个人感觉比其他题解更容易理解一些。~~

## 题意简述

构造一个数列 $a_1,a_2,\dots,a_n$，使数列中的每个数都满足 $0 \le a_i \le m$，且所有数的异或和为 $k$。

若存在这样的数列，输出这个数列；否则输出 `-1`。

## 思路

首先我们要知道“异或”是个什么东西，简单来说，就是：

$0 \oplus 0 = 0$，$1 \oplus 1 = 0$，$0 \oplus 1 = 1$，$1 \oplus 0 = 1$。

那么通过上面的式子，我们可以得到两个重要信息：

- $a \oplus 0 = a$
- 如果 $a \oplus b = c$，则 $c \oplus a = b$

首先，先想最简单的一种情况，$k \le m$，那么我们只需要把 $a_1$ 变成 $k$，后面的数都是 $0$。即输出：`k 0 0 … 0`

那么 $k>m$ 怎么办，我们可以把 $a_1$ 变成 $(k \oplus m) \le x \le m$ 的一个 $x$（遍历），那么我们的目标就变成了 $a_2 \oplus a_3 \oplus \dots \oplus a_n = k \oplus x$。

这样就得到了新的 $k = k \oplus x$。

按顺序推下去，如果到达 $a_i$ 时，$k\le m$，那么把 $a_i$ 赋值为 $k$ 即可。后面的数全部补 $0$。

而如果推到 $a_n$，还是不存在 $k\le m$，说明无解，直接输出 `-1`。

## 代码及注意事项

```cpp
#include <iostream>
using namespace std;
#define int long long // 不开龙龙见祖宗

int T;
int n, k, m;
int t;

bool dfs(int k, int i) // k和i的含义如上
{
    if(i > n) // 已经推完了a_n，说明无解
    {
        return false;
    }
    if(k <= m) // 可以在这一步结束力！
    {
        cout << k << ' ';
        t++;
        return true;
    }
    for(int x = m; x >= (k ^ m); x--) // 选一个数
    {
        if(dfs(k ^ x, i + 1)) // 搜索i+1
        {
            cout << x << ' '; // 有解有解！
            t++;
            return true;
        }
    }
    return false; // 此步无解，回到上一步换一个数
}

signed main()
{
    cin >> T;
    while(T--)
    {
        cin >> n >> k >> m;
        t = 0; // 多测不清空，保龄两行泪
        if(!dfs(k, 1)) // 无解，输出-1
        {
            cout << -1 << endl;
        }
        else
        {
            for(int ii = t + 1; ii <= n; ii++) // 补零
            {
                cout << 0 << ' ';
            }
        }
        cout << endl;
    }
    return 0;
}
```

---

## 作者：olegekei (赞：1)

首先一个比较容易构造的情况：当 $k\le m$ 时，直接构造一个形如 $\{0,0,…,k\}$ 的序列（序列中有 $n-1$ 个 $0$）即可。

接下来思考如果 $k>m$，根据异或的性质，如果 $k$ 的二进制最高非零位比 $m$ 的二进制最高非零位还要高，那么无解（因为异或不进位）。

除去这种情况，我们可以取出 $k$ 的二进制最高非零位 $p$，将 $2^{p}$ 加入我们构造的序列，那么就将 $(n,k,m)$ 情况转化成了 $(n-1,k-2^{p},m)$ 情况，此时等价于 $k\le m$ 情况进行处理即可，最后构造出的序列则形如 $\{0,0,…,k-2^{p},2^{p}\}$（有 $n-2$ 个 $0$）。别忘了特判 $n$，如果在该情况下 $n=1$ 时则无法构造出该序列。

```cpp
#include<iostream>
using namespace std;
int main(){
int t;
cin>>t;
while(t--){
	int n,k,m;
	cin>>n>>k>>m;
	if(k<=m){for(int i=1;i<n;i++)cout<<"0 ";cout<<k<<'\n';continue;}
	int cnt=0;
	while(m)cnt++,m>>=1;
	int x=k,p=0;
	while(x)p++,x>>=1;
	if(p>cnt||n==1){cout<<"-1\n";continue;}
	for(int i=2;i<n;i++)cout<<"0 ";
	p--;
	cout<<(k-(1<<p))<<' '<<(1<<p)<<'\n';
}
return 0;
}
```

---

## 作者：ncwzdlsd (赞：0)

考虑异或的性质，任何数异或 $0$ 都为 $0$，于是对于 $k\leq m$ 的情况，直接输出一个 $k$ 和 $n-1$ 个 $0$ 即可。

当 $k>m$ 时，显然需要至少两个数，$n=1$ 时无解。设 $k$ 和 $m$ 的二进制下最高非零位分别为 $p_1,p_2$，若 $p_1>p_2$ 则无解，因为异或操作不能实现“进位”。否则，说明 $k$ 的位数等于 $m$，我们直接把 $k$ 减掉 $2^{p_1}$，此时把问题又转化为了 $k<m$ 的情况。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=2e5+5;
int a[maxn];

int calc(int x)
{
    int cnt=0;
    while(x)
        x>>=1,cnt++; 
    return cnt;
}

void solve()
{
    int n,k,m;cin>>n>>k>>m;
    if(k<=m)
    {
        cout<<k<<' ';
        for(int i=1;i<n;i++) cout<<"0 ";
        cout<<'\n';
    }
    else 
    {
        if(n==1) return cout<<"-1\n",void();
        int p1=calc(k),p2=calc(m);
        if(p1>p2) return cout<<"-1\n",void();
        cout<<(1<<(p1-1))<<' '<<(k-(1<<(p1-1)));
        for(int i=3;i<=n;i++) cout<<" 0";
        cout<<"\n";
    }
}

int main()
{
    int T;cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

挺有意思的 div2A。

首先，可以一眼看出如果 $k\le m$ 可以构造出 $0{,}0{,}0{,}\cdots{,}0{,}k$。

其次，我们可以知道 $a$ 中必有一数 $\ge2^{\log k}$，因此如果 $m<2^{\log k}$（也就是 $\log m<\log k$），一定无解。

否则构造出 $0{,}0{,}0{,}\cdots{,}0{,}2^{\log k}{,}k-2^{\log k}$ 即可，因为 $k-2^{\log k}$ 必 $\le m$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int T;
int n,k,m;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>T;
	while(T--){
		cin>>n>>k>>m;
		int logk=ceil(log2(k));
		if((int)(log2(m))<(int)(log2(k))){
			cout<<-1<<endl;
		}
		else if(m<k){
			if(n==1){
				cout<<-1<<endl;
			}
			else{
				cout<<(1ll<<(logk-1))<<' '<<k-(1ll<<(logk-1))<<' ';
				for(int i=1;i<n-1;i++) cout<<0<<' ';
				cout<<endl;
			}
		}
		else{
			cout<<k<<' ';
			for(int i=1;i<n;i++) cout<<0<<' ';
			cout<<endl;
		}
	}
	return 0;
}
```


---

## 作者：Clarinet (赞：0)

[博客食用观感更佳](https://www.luogu.com.cn/blog/Czel-X/ti-xie-14-post)
# 简要题意
有 $t$ 组数据，每组数据给出 $n$、$k$ 和 $m$，要求构造出有 $n$ 个不大于 $m$ 的数的序列，使它们异或后的结果为 $k$。
# 分析
一眼构造题。

开始之前，先为与我一样不大懂异或的蒟蒻大概讲解一下异或。至于最基础的含义原题中给出了，~~自己看百度百科去~~。

我们举个例子，例如两个二进制数 $1001011$ 和 $1100110$，若将他们异或，那么最终的结果就是 $0101101$。  
可以发现，异或后的数字位数一定不会变大，并且如果异或中的一个数字为 0，那么结果就为另一个数字本身。另外若 $a \oplus b = c$，则 $c \oplus b = a$。本题我的思路只需要运用这三个性质即可。

首先考虑是否有解。根据第一条性质，如果在二进制下 $k$ 的位数比 $m$ 大，则证明是无解的，直接输出 $-1$。

否则对于 $k \le m$ 的情况，我们直接在第一个位置输出 $k$ 即可，后面都用 $0$ 补上。

再考虑 $k > m$ 的情况。既然最大数不超过 $m$，我们可以先输出一个 $m$ 来凑得尽可能大。由于此时二进制下 $m$ 和 $k$ 一定位数相同，则一定有不大于 $m$ 的整数 $x$ 满足 $x \oplus m = k$。然后根据第三点性质，我们可以用 $k \oplus m$ 来求出这个 $x$。

在 C++ 中，我们可以直接用 ^ 这个符号来计算异或，所以输出的第二个数就是 $k \oplus m$。并且由以上证明我们也可得知此时 $n$ 必须大于等于 $2$，否则也无解。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,m;
bool check(int x,int y){
	int xr=0,yr=0;
	while(x){
		xr++;
		x/=2;
	}
	while(y){
		yr++;
		y/=2;
	}
	if(xr<yr)return true;
	return false;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k>>m;
		if(check(m,k)){
			cout<<-1<<endl;
			continue;
		}
		if(m>=k){
			cout<<k;
			for(int i=1;i<=n-1;i++)cout<<" 0";
			cout<<endl;
			continue;
		}
		if(n==1){
			cout<<-1<<endl;
			continue;
		}
		int ans=k^m;
		cout<<m<<" "<<ans;
		for(int i=2;i<=n-1;i++)cout<<" 0";
		cout<<endl;
	}
	return 0;
}
```
感谢阅读！

---

## 作者：许多 (赞：0)

~~凯文一眼秒了这题，本蒟蒻却做了半个小时~~。

我们用 $m2$ 表示 $m$ 二进制下的位数，用 $k2$ 表示 $k$ 二进制下的位数.

无解的情况很好判断，当 $m2$ 小于 $k2$ 时无解。

我们使 $a_1=2^{k2}$，求 $a_2$，使 $a_2\oplus a_1=k$，即 $a_2=a_1\oplus k$。

在二进制下，$a_1$ 的位数和 $k$ 的位数相同，所以 $a_2$ 一定小于 $a_1$。

至于后面的数，我们可以让他们都等于 $0$。

记得特判 $n=0$ 的情况。

# 代码

```cpp
#include<bits/stdc++.h>
#include<cstdio>
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
using namespace std;
int f(int a,int n){//快速幂
    int ans=1;
    while(n){
        if(n&1)ans=ans*a;
        a*=a;
        n/=2;
    }
    return ans;
}
int T,n,m,k,m2,k2;
int main(){
    T=read();
    while(T--){
        n=read();k=read();m=read();
        m2=log2(m);
        k2=log2(k);
        if(m2<k2){printf("-1\n");continue;}
        if(n==1){
            if(k>m)printf("-1\n");
            else printf("%d \n",k);
            continue;
        }
        int a1=f(2,k2),a2=0;
        printf("%d ",a1);
        a2=a1^k;
        printf("%d ",a2);
        for(int i=3;i<=n;i++)printf("0 ");
        printf("\n");
    }
    return 0;
}
```


---

