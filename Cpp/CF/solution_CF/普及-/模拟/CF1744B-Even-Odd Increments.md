# Even-Odd Increments

## 题目描述

You are given $ n $ of integers $ a_1, a_2, \ldots, a_n $ . Process $ q $ queries of two types:

- query of the form "0 $ x_j $ ": add the value $ x_j $ to all even elements of the array $ a $ ,
- query of the form "1 $ x_j $ ": add the value $ x_j $ to all odd elements of the array $ a $ .

Note that when processing the query, we look specifically at the odd/even value of $ a_i $ , not its index.

After processing each query, print the sum of the elements of the array $ a $ .

Please note that the answer for some test cases won't fit into 32-bit integer type, so you should use at least 64-bit integer type in your programming language (like long long for C++).

## 说明/提示

In the first test case, the array $ a = [2] $ after the first query.

In the third test case, the array $ a $ is modified as follows: $ [1, 3, 2, 4, 10, 48] $ $ \rightarrow $ $ [7, 9, 2, 4, 10, 48] $ $ \rightarrow $ $ [7, 9, 7, 9, 15, 53] $ $ \rightarrow $ $ [7, 9, 7, 9, 15, 53] $ $ \rightarrow $ $ [10, 12, 10, 12, 18, 56] $ $ \rightarrow $ $ [22, 24, 22, 24, 30, 68] $ $ \rightarrow $ $ [23, 25, 23, 25, 31, 69] $ .

## 样例 #1

### 输入

```
4
1 1
1
1 1
3 3
1 2 4
0 2
1 3
0 5
6 7
1 3 2 4 10 48
1 6
0 5
0 4
0 5
1 3
0 12
0 1
6 7
1000000000 1000000000 1000000000 11 15 17
0 17
1 10000
1 51
0 92
0 53
1 16
0 1```

### 输出

```
2
11
14
29
80
100
100
100
118
190
196
3000000094
3000060094
3000060400
3000060952
3000061270
3000061366
3000061366```

# 题解

## 作者：深度产业观察 (赞：4)

这个题打眼一看是一道多点加的题目，但我们仔细观察一下题面，就会得出这么一个结论：**一次操作操作的数不全是奇数就全是偶数，加的数相同**。

那么我们就可以简化成这样：

1：开局读入时分别计算**奇数个数**和**偶数个数**，并求出**初始串的总和**。

2：若读入的是“操作0”那么就将总数加上偶数个数×加数

若读入的是“操作1”那么就将总数加上奇数个数×加数。

3：如果操作0的加数是奇数意味着**所有的偶数都变成了奇数**，偶数个数清零，奇数个数=串长度。


同理如果操作1的加数是奇数意味着**所有的奇数都变成了偶数**，奇数个数清零，偶数个数=串长度。

相信在座的各位都理解了，上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,q,a,b,s[1000000],js,os,cnt;
int main(){
	cin>>t;
	for(int g=1;g<=t;g++){
		cin>>n>>q;
		for(int i=1;i<=n;i++){
			cin>>s[i];
			if(s[i]%2==0)
				os++;
			else
				js++;
			cnt+=s[i];
		}
		for(int i=1;i<=q;i++){
			cin>>a>>b;
			if(a==0){
				cnt+=os*b;
				if(b%2!=0){
					js+=os;
					os=0;
				}
			}
			else{
				cnt+=js*b;
				if(b%2!=0){
					os+=js;
					js=0;
				}
			}
			cout<<cnt<<endl;
		}
		cnt=0;
		js=os=0;
		for(int i=1;i<=n;i++)
			s[i]=0;
	}
	return 0;
} 
```
结束。

---

## 作者：_Haoomff_ (赞：3)

挺简单的一道题，但是要注意一下细节。

### 前置“芝士”：

- 奇数+奇数=偶数
- 奇数+偶数=奇数
- 偶数+偶数=偶数

### 思路：
在输入 $n$ 个数的时候，我们可以把奇、偶数的个数求出来并把这 $n$ 个数的和求出来，因为对于 $q$ 次操作，每次均只需输出数列的和。

在执行 $q$ 次操作时，设每次操作输入的是 $x$ 和 $y$，那么就按照 $x$ 是 $0$ 的情况和 $x$ 是 $1$ 的情况分别执行：若为 $0$，则数列和加上偶数 $\times y$；若为 $1$，则数列和加上奇数 $\times y$。

按照上面这个思路，看似可以过了，开始时我也是这么打的，但是测试样例只对了几组。

为什么呢？因为奇数加偶数仍然等于奇数，而奇数加奇数则等于偶数，因此在 $x=0$ 或 $x=1$ 的情况下都要特判 $y$ 是否为奇数：若 $x=0$ 且 $y$ 为奇数，根据奇数加偶数等于奇数，要将奇数个数加上偶数个数，并将偶数个数清 $0$；若 $x=1$ 且 $y$ 为奇数，根据奇数加奇数等于偶数，要将偶数个数加上奇数个数，并将奇数个数清 $0$。

另外，这题必须使用 $\texttt{long long}$，因为数列和可能会超出 $\texttt{int}$ 范围。

### 代码：
```cpp
#include<iostream>
#include<cstring>
#define ll long long
using namespace std;
ll t,n,q,a[100005];
ll js;//奇数个数 
ll os;//偶数个数 
ll ans;//数组和 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	for(;t--;){
		js=os=ans=0;//初始化 
		cin>>n>>q;
		for(int i=1;i<=n;++i){
			cin>>a[i];
			if(a[i]%2==0)++os;
			else ++js;
			ans+=a[i];//求出整个数组的和 
		}
		for(int i=1;i<=q;++i){
			int x,y;
			cin>>x>>y;
			if(x==0){
				ans+=os*y;
				if(y%2==1){//奇数+偶数=奇数，所以偶数全部变为奇数
					js+=os;
					os=0;
				}
			}
			else if(x==1){
				ans+=js*y;
				if(y%2==1){//奇数+奇数=偶数，所以奇数全部变为偶数 
					os+=js;
					js=0;
				} 
			}
			cout<<ans<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：ice_fish01 (赞：1)

## **$\text{CF1744B Even-Odd Increments}$ 题解**

### $\texttt{A.}$ 前言

本蒟蒻的第二篇题解。

话说这道题 ~~真的不坑~~ **坑点很多**。

### $\texttt{B.}$ 思路分析

### $\texttt{Part1. 40 pts}$ 的遍历修改

一开始，某些童鞋的第一反应可能是：**遍历过水题**，结果 $5$ 分钟写完代码，交上去很自然的没了。

思路非常的简单，按照题目说的做就行。（这一部分的代码，**没有就是没有**）。

### $\texttt{Part2.}$ 醒悟

一看数据范围：$1 \leq t \leq 10^4$，$1 \leq n,q \leq 10^5$！没想到 $ t \times n \times q$ 最大竟然可以到 $10^{14}$ 的级别，看来遍历就算再怎么卡常也不可能过这道题了。

那么，我们该怎么办？

### $\texttt{Part3. AC}$ 思路

思路：

对于每一组数据，我们先读入 $n$ 和 $q$。

接着，我们读入这个数列。在读入时，我们可以顺便算一下数列每一项的**奇偶性**和**数列的总和**，目的是本题的操作主要以**奇偶性**和**数列总和**为主。需要注意的是，$1 \leq a_i \leq 10^9,1 \leq n \leq 10^5$，所以该数列的总和最大可达到 $10^{14}$，必须用 `long long` 类型的变量来存储。

然后就是激动人心的 $q$ 次操作了。唠叨两句，其实对于信息学中的很多题目，我们**并不用**完全按照题目说的去完成代码，而是针对题目**需要求的值、可能性等**去完成代码。所以，我们可以这样应对这 $q$ 次操作：

$(1)$ 读入两个整型数，含义如题所述；
 
$(2)$ 将总和加上 奇/偶数个数 $\times x$；

$(3)$ 如果 $x$ 为偶数，那么将数列中的某些数加上 $x$ 并不改变它们的奇偶性 **（余数的性质）**；如果 $x$ 为奇数，那么这次操作中每一个加上了 $x$ 的数的奇偶性将改变，即，操作后数列中**只有**奇数或偶数。

$(4)$ 输出当前的总和。

这就是我们的 $q$ 次操作。每一组数据处理完成后，记得**清空所有非读入的变量**。

### $\texttt{C.}$ $\text\color{green}AC$ $\text\color{green}Coding$

```cpp
//CF1744B Even-Odd Increments
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,q,a,opt,x,sum,ou,ji;

signed main()
{
	cin >> t; //数据组数 
	while(t--)
	{
		//正式开始 
		cin >> n >> q;
		for(int i = 1;i <= n;i++) //输入这个数列。因为我们没有需要在后面继续使用这些数据，所以我们可以只用一个变量  
		{
			cin >> a;
			sum += a; //记录总和  
			if(a % 2 == 0) //记录奇偶数个数 
				ou++;
			else
				ji++;
		}
		while(q--) //开始进行操作  
		{
			cin >> opt >> x; //输入 
			if(opt == 0) //对偶数进行操作 
			{
				sum += x * ou; //总和加上 偶数个数 * x 
				if(x % 2 == 1) //x是奇数，影响奇偶性 
				{
					ji = n;
					ou = 0;
				}
			}
			else
			{
				sum += x * ji;
				if(x % 2 == 1)
				{
					ou = n;
					ji = 0;
				}
			}
			cout << sum << '\n'; //最后输出莫忘记 
		}
		//清空变量好习惯 
		ou = 0;
		ji = 0;
		sum = 0;
	}
	return 0; //好习惯 
}

```

### $\texttt{D.}$ 鸣谢
[~~ice_fish01~~](https://www.luogu.com.cn/user/770910)

**至高无上的管理员**



------------


### **完结撒花！**

---

## 作者：_JF_ (赞：1)

## Even-Odd Increments 

[题目传送门](https://www.luogu.com.cn/problem/CF1744B)

题目大意：给定一个长度为 $n$ 的数列，有 $q$ 次操作，每次对数列中的奇偶数进行操作，问每次执行完操作后数列的总和。

如果一一遍历去修改的话，时间是 $O(nq)$ 会超时。

但是，他只对数列中的奇数或偶数进行加和，我们只要统计出奇数和偶数的个数，加和就是他们的个数乘上这个加上的数就是现阶段的贡献。

但是，把一个数加上某个数，这个数的奇偶性就会发生变化。

如果当前的数是偶数，加上的数是奇数的话，这个数就变成奇数，那么所有的偶数变成奇数，奇数的个数就是 $n$，偶数就是 $0$。

奇数的如上所示，是一样的。

最后记得要统计初始的贡献。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int t;
	cin>>t;
	while(t--)
	{
		int n,q,sum=0,ans=0,ans1=0;
		cin>>n>>q;
		for(int i=1,x;i<=n;i++)
		{
			cin>>x,sum+=x;
			if(x%2==0)
				ans++;
			else
				ans1++;
		}
		while(q--)
		{
			int opt,s;
			cin>>opt>>s;
			if(opt==0)
			{
				sum+=ans*s,cout<<sum<<endl;
				if(s%2!=0)
					ans1=n,ans=0;
			}
			else
			{
				sum+=ans1*s,cout<<sum<<endl;
				if(s%2!=0)
					ans1=0,ans=n;
			}
		 } 
	}
	return 0;
}

```


---

## 作者：Marshall001 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1744B)

## 题目大意

给定一个长度为 $n$ 的数列，有 $q$ 次操作，问每次执行完操作后数列的总和。

共有两种操作：

- $\texttt{0\space x}$，给所有偶数加上 $x$。

- $\texttt{1\space x}$，给所有奇数加上 $x$。

## 思路

偶数 $+$ 偶数 $=$ 偶数，偶数 $+$ 奇数 $=$ 奇数，奇数 $+$ 偶数 $=$ 奇数，奇数 $+$ 奇数 $=$ 偶数。上面这些式子想必大家都知道，如果这些式子弄清楚了，这道题也就很简单了。首先记录每组数据的偶数个数和奇数个数还有这组数据的和 （用 $ans$ 记录）。如果是 $0$ 指令，那么 $ans= $ 偶数个数 $\times x$。如果是 $1$ 指令，那么 $ans= $ 奇数个数 $\times x$。每次操作要记得根据上面的四个式子更新偶数个数和奇数个数。

## 代码

```cpp
#include <iostream>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		long long n,q,ans=0,s1=0,s2=0;//s1是偶数个数，s2是奇数个数。
		cin>>n>>q;
		for(int i=1;i<=n;i++){
			long long a;
			cin>>a;
			ans+=a;
			if(a%2==0){
				s1++;
			}
			else{
				s2++;
			}
		}
		for(int i=1;i<=q;i++){
			int id,x;
			cin>>id>>x;
			if(id==0){
				ans+=s1*x;
				if(x%2==1){//更新
					s2+=s1;
					s1=0;
				}
			}
			else{
				ans+=s2*x;
				if(x%2==1){//更新
					s1+=s2;
					s2=0;
				}
			}
			cout<<ans<<endl;//每次操作后都要输出！
		}
	}
	return 0;
}
```


---

## 作者：Larryyu (赞：1)

## _Description_
给定一个长度为 $n$ 的数列，有 $q$ 次操作，问每次执行完操作后数列的总和。

共有两种操作：
- $\texttt{0\space x}$，给所有偶数加上 $x$；
- $\texttt{1\space x}$，给所有奇数加上 $x$；
## _Solution_
如果每次操作暴力遍历一次，时间复杂度为 $\Theta(t\times n\times q)$，明显会爆。

所以我们只记录下每次 $x$ 加了多少次即可，而这个次数取决于奇偶数的数量，这个在输入时记录一下就可以了。

记得加上最初始的 $n$ 个数。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t;
int n,q;
int cnt1,cnt2;
ll ans;
ll read(){
    ll x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main(){
    t=read();
    while(t--){
    	ans=0,cnt1=0,cnt2=0;
    	n=read();
    	q=read();
    	for(int i=1;i<=n;i++){
            int x;
            x=read();
            ans+=x;
            if(x%2==1) cnt1++;
            else cnt2++;
        }
        for(int i=1;i<=q;i++){
            int opt,x;
            opt=read();
            x=read();
            if(opt==0){
                ans+=cnt2*x;
                if(x%2==1){
                cnt1+=cnt2;
                cnt2=0;
                }
            }
            else {
                ans+=cnt1*x;
                if(x%2==1){
                    cnt2+=cnt1;
                    cnt1=0;
	            }
            }
            cout<<ans<<endl;
        }
    }
	return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

[也许有更好的阅读体验](https://www.cnblogs.com/zheyuanxie/p/cf1744b.html)

## 简要题意

$T$ 组数据，每组数据给定一个长度为 $n$ 的数列，有 $q$ 次操作，共有两种操作：

- $\texttt{0 x}$，给数列中所有偶数加上 $x$；
- $\texttt{1 x}$，给数列中所有奇数加上 $x$;

每一次操作结束后，输出数列的和。

$1 \leq T \leq 10^{4},1 \leq n,q \leq 10^{5}$

## 思路

相当巧妙的一道思维题。

首先，如果直接暴力搞貌似不太行，线段树太难写，而且也没有区间操作。

其实这道题有一个更简单的做法，首先，如果 $x$ 时奇数，那么在 $0$ 操作中所有数都会变成偶数，在 $1$ 操作中所有数都会变成奇数。（因为奇数加奇数为偶数，奇数加偶数为奇数，偶数加偶数为偶数）。再维护一个全局和，你发现就可以 $O(1)$ 操作了。

整体时间复杂度 $O(T(n+q))$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int odd,even,sum,n,q,a[100005];

void solve(){
	odd=0;even=0;sum=0;
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum += a[i];
		if(a[i]&1)odd++;
		else even++;
	}
	while(q--){
		int op,x;
		cin>>op>>x;
		if(op==0){
			sum += even*x;
			if(x&1){
				odd=n;
				even=0;
			}
		}
		else{
			sum += odd*x;
			if(x&1){
				even=n;
				odd=0;
			}
		}
		cout<<sum<<'\n';
	}
}

signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：隐仞Mrsu (赞：0)

~~当时写的时候，把操作对象错看成奇数序号的元素和偶数序号的元素了。~~

对于给定的 $n$ 长数组，进行 $q$ 次操作。

操作包括：
- 对所有当前数值为奇数的元素加上 $x_j$；
- 对所有当前数值为偶数的元素加上 $x_j$。

每次操作过后输出当前数组中所有元素的和。

为了避免写暴力而超时的尴尬情况，不妨用变量 $od$ 和 $ev$ 分别储存当前奇数元素之和、偶数元素之和。

每次操作时，将 $od$ 或 $ev$ 乘上 $x_j$。同时，如果 $x_j$ 是奇数，则原本数组中的奇数都会变成偶数，原本数组中的偶数都会变成奇数，因此应进行代换。然后输出答案即可。

详见代码

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 1e5+6;
LL _,n,q,a[N],ev,od,res;
void work(){
	ev=od=res=0;
	cin>>n>>q;
	for(LL i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]%2)od++;
		else ev++;
		res+=a[i];
	}
	for(LL i=1;i<=q;i++){
		LL t,x;
		cin>>t>>x;
		if(!t){
			res+=x*ev;
			if(x%2){
				od+=ev;
				ev=0;
			}
		}
		else{
			res+=x*od;
			if(x%2){
				ev+=od;
				od=0;
			}
		}
		cout<<res<<'\n';
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>_;
	while(_--){
		work();
	}
}
```


---

## 作者：Allanljx (赞：0)

## 思路
记录奇数的数量、偶数的数量以及初始的和，此时操作完的值可以直接算出。考虑修改，当偶数加上奇数时所有数都会变成奇数，当奇数加上奇数时所有数都会变成偶数，因此每次询问都可以 $\Theta(1)$ 算所有数的和以及修改后奇数和偶数的数量。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,q;
int a[200005],d1,d2;
signed main()
{
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--)
	{
		d1=d2=0;
		int sum=0;
		cin>>n>>q;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			sum+=a[i];//初始的和
			if(a[i]%2) d1++;//奇数的数量
			else d2++;//偶数的数量
		}
		while(q--)
		{
			int op,x;
			cin>>op>>x;
			if(!op) sum+=x*d2;
			else sum+=x*d1;//算和
			if(!op)
			{
				if(x%2) d1+=d2,d2=0; 
			}
			else
			{
				if(x%2) d2+=d1,d1=0;
			}
			cout<<sum<<"\n";
		}
	}
}
```

---

## 作者：XiaoQuQu (赞：0)

由于题目要求只需要求和，而非具体的每一个数，于是我们考虑将 $a$ 数组的和预处理出来，记为 $s$。

设 $a_i$ 中有 $e$ 偶数， $o$ 个奇数，那么对于一次操作，如果是对偶数加 $x$，那么会对最终的结果加上 $x\times e$。对奇数操作同理。

考虑到奇数加奇数为偶数，于是对奇数进行操作的时候，若加上的是奇数，则在统计完贡献后将 $o$ 设为 $0$，$e$ 设为 $1$。对偶数加上奇数同理。

```cpp
// Problem: B. Even-Odd Increments
// Contest: Codeforces - Codeforces Round  #828 (Div. 3)
// URL: https://codeforces.com/contest/1744/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

const int MAXN = 1e5 + 5;
int a[MAXN], os, es, n, q, s;

void work() {
    cin >> n >> q;
    es = os = s = 0;
    for (int i = 1; i <= n; ++i) {
    	cin >> a[i];
    	if (a[i] % 2 == 1) os++;
    	else es++;
    	s += a[i];
    }
    for (int i = 1; i <= q; ++i) {
    	int t, x;
    	cin >> t >> x;
    	if (t == 0) {
    		s += es * x;
    		if (x % 2) es = 0, os = n;
    	}
    	else {
    		s += os * x;
    		if (x % 2) os = 0, es = n; 
    	}
    	cout << s << endl;
    }
    // cout << s << endl;
}

signed main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        work();
    }
    return 0;
}
```



---

