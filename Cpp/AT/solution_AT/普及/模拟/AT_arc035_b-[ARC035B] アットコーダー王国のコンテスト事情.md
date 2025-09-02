# [ARC035B] アットコーダー王国のコンテスト事情

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc035/tasks/arc035_b

高橋くん様は、アットコーダー王国の王様です。

プログラミングコンテスト好きな彼が統治するアットコーダー王国では、年に一度コンテストが開催されます。

このコンテストでは $ N $ 問の問題が出題されます。また、順位を付ける際の $ 1 $ つの要素としてペナルティというものが存在します。 ある問題を正解したとき、コンテスト開始から経過した時間分だけのペナルティが、各問題ごとに発生します。そして、その発生したペナルティの総和がコンテストペナルティとなります。ARCのペナルティとは異なるルールであることに注意してください。

非常に優秀な国民である貴方には、全ての問題を解く力があります。 しかも、全ての問題について、その問題を正解するためにどれだけ時間をかければよいのかを知っており、ちょうどその時間取り組むと必ず正解することができます。

貴方は、自由な順番で問題を解くことができるので、コンテストペナルティが最小となるように解こうと思いました。

全ての問題を解くときのコンテストペナルティの最小値と、そのような解き方が何通りあるかを $ 1,000,000,007(10^9+7) $ で割った余りを答えて下さい。

## 说明/提示

### 部分点

この問題には部分点が存在する。

- $ 100 $ 点中 $ 50 $ 点分のテストケースにおいて、コンテストペナルティが最小となるような解き方の数は $ 1 $ 通りである。

### Sample Explanation 1

$ 2 $ 番目の問題を解いてから $ 1 $ 番目の問題を解くのがよい。 - コンテストが開始する(時刻：$ 0 $ 分)。 - $ 10 $ 分後、$ 2 $ 番目の問題に正解する(時刻：$ 10 $ 分)。この時点で発生するペナルティは $ 10 $ 分である。 - その $ 20 $ 分後、$ 1 $ 番目の問題に正解する(時刻： $ 30 $ 分)。この時点で発生するペナルティは $ 30 $ 分である。 コンテストペナルティは $ 40(=10+30) $ 分となる。

### Sample Explanation 3

どのような順番で解いても良い。余りを取るのを忘れないこと。

## 样例 #1

### 输入

```
2
20
10```

### 输出

```
40
1```

## 样例 #2

### 输入

```
5
2
1
2
1
2```

### 输出

```
21
12```

## 样例 #3

### 输入

```
13
1
1
1
1
1
1
1
1
1
1
1
1
1```

### 输出

```
91
227020758```

# 题解

## 作者：Ja50nY0un9_as_AgNO3 (赞：3)

[戳这里感受更加糟心的阅读体验！](https://www.luogu.com.cn/blog/363302/solution-at-arc035-b)
### 题意简述

一场 ARC 比赛中有 $n$ 道题，对于第 $i$ 道题你所需要的时间是 $t_i$ 分钟。

每道题的罚时是从比赛开始到做完这道题所用的时间，同一时刻只能做一道题。

输出最小罚时以及达成最小罚时的开题顺序种数。第二问对 $10^9+7$ 取模。

### 题解

考虑贪心。由于每道题所用时间都会累加到后面每一道题的罚时中，所以第 $n-x+1$ 道题产生的罚时是 $t_i \times x$ 分钟。所以，越靠前的题，罚时倍率就越大，于是我们就应该把耗时越短的题放到越靠前的位置。

我们对数组排序，然后将每道题的罚时累加起来，并记录做完每一道题时的时间。注意，这个数可能很大，而且不要求取模，所以需要开 `long long`。这一段代码如下：
```cpp
sort(a + 1, a + n + 1);
ll ans = 0, t = 0;
for (int i = 1; i <= n; i++){
    ans = ans + t + a[i];
    t += a[i];
}
cout << ans << endl;
```
接着我们考虑第二问。因为消耗时间的顺序是确定且唯一的，只有耗时相同的题目才能交换顺序。假设原数列有 $k$ 个耗时相同的「块」，每块中题目数是 $cnt_i$，我们就要计算下式：

$$(\prod\limits^{k}_{i=1}cnt_i!)\bmod
10^9+7$$

由于每个数只会在一个「块」中，即 $\sum\limits^{k}_{i=1}cnt_i=n$，所以我们可以以 $\Theta(cnt_i)$ 的时间复杂度计算阶乘而无需预处理，总时间复杂度是 $\Theta(n)$ 的。

计算阶乘如下：
```cpp
const ll mod = 1e9 + 7;

ll cal(ll cnt){
    if (!cnt)
        return 0;
    if (cnt == 1)
        return 1;
    return cnt * cal(cnt - 1) % mod;
}
```
计算答案如下：
```cpp
ans = 1;
ll cnt = 1;
for (int i = 1; i <= n; i++){
    if (a[i] != a[i + 1]){
        ans *= cal(cnt);
        ans %= mod;
        cnt = 1;
    }
    else
        cnt++;
}
cout << ans << endl;
```
至此，我们就解决了这道~~水~~题。

---

## 作者：Fire_Kylin (赞：1)

~~又是晴朗的一天~~

# 思路

## 对于第一问
明显一道贪心。**让每道题的罚时最小则总罚时最小。**

那怎样实现呢？

类似排队打水。让耗时更小的题目先做，这样以后的题目等待时间也最小。让每道题对后面的题影响最小，这就是贪心策略。

代码（仅供参考，不保证正确性）:

```cpp
sort(a+1,a+n+1);//贪心，耗时小的先解决。
	
for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];//前缀和求总时间
	
for(int i=1;i<=n;i++) sum+=s[i];//累加前缀和，得出答案
```
这样第一问就解决了。

## 对于第二问
由于第一问的贪心，则解决的顺序已定。但耗时相同题不存在绝对的先后关系，那产生多种解只可能是相同耗时题目中产生的，因为两个都需要 1 分钟的题谁前谁后结果都一样。

可是到底会产生几个解呢？

自己在草稿纸上算算，发现：**有 $m$ 个相同时间的解，则会诞生 $m!$ 个解**。

于是：

```cpp
int cnt=1;//计数器，累加重复出现的数。为了不出现输出0而初始为1
	int out=1;//存储结果
	
	for(int i=2;i<=n;i++){//由于排过序
		if(a[i]==a[i-1]) cnt++;//查找重复从第二个开始，i=2
		
		else{//如果连续相同的数断开了（类似P1420 最长连号)
			out=(out*up(cnt))%mod;//更新答案
			cnt=1;//长度归位
		}
	}
	
	out=(out*up(cnt))%mod;//再算一次
```
第二问也解决了。

# 完整代码
## 带注释

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
int n,a[N],s[N],sum=0;
long long up(int x){//求阶乘函数，保险起见开 long long
	long long ans=1;
	for(int i=1;i<=x;i++) ans=(ans*i)%mod;//每计算一次模一次，防止爆炸
	return ans;
}
signed main(){
	//输入
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	//问题1（超简单）
	sort(a+1,a+n+1);//贪心，类似排队打水，耗时小的先解决。
	
	for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];//前缀和求总时间
	
	for(int i=1;i<=n;i++) sum+=s[i];//累加前缀和，得出答案
	
	
	//问题2
	int cnt=1;//计数器，累加重复出现的数。为了不出现输出0而初始为1
	int out=1;//存储结果
	
	for(int i=2;i<=n;i++){//由于排过序
		if(a[i]==a[i-1]) cnt++;//查找重复从第二个开始，i=2
		
		else{//如果连续相同的数断开了（类似P1420 最长连号)
			out=(out*up(cnt))%mod;//更新答案
			cnt=1;//长度归位
		}
	}
	
	out=(out*up(cnt))%mod;//再算一次
	
	//输出
	cout<<sum<<'\n'<<out;
return 0;//over
}
```
## 无注释

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
int n,a[N],s[N],sum=0;
long long up(int x){
	long long ans=1;
	for(int i=1;i<=x;i++) ans=(ans*i)%mod;
	return ans;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
	for(int i=1;i<=n;i++) sum+=s[i];
	int cnt=1;
	int out=1;
	for(int i=2;i<=n;i++){
		if(a[i]==a[i-1]) cnt++;
		else{
			out=(out*up(cnt))%mod;
			cnt=1;
		}
	}
	out=(out*up(cnt))%mod;
	cout<<sum<<'\n'<<out;
return 0;
}
```

---

## 作者：joker_opof_qaq (赞：0)

算是贪心模板了，和接水问题很相似。

## 题意翻译

每个人做题需要时间，求最小时间总数和时间方案。

## 思路 && 解法

先做快的题目明显最优，这样后面题目就能等的更短。

而数量只要考虑重复数的先后顺序即可。

9.15 Update 发现了一个错别字，管理大大没审核出来，重新申请。

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc035_b)

### 温馨提示
岛国题要换行！

### 题目大意
一场 ARC 比赛中有 $n$ 道题，对于第 $i$ 道题你所需要的时间是 $t_i$ 分钟。

每道题的罚时是从比赛开始到做完这道题所用的时间，同一时刻只能做一道题。

输出最小罚时以及达成最小罚时的开题顺序种数。第二问对 $10^9+7$ 取模。

### 解题思路
第一问很简单，直接贪心。贪心策略如下：将所有用时从小到大进行排序，然后将每道题的罚时累加起来，并记录做完每一道题的时间即可。

代码如下：
```cpp
sort(a+1,a+n+1);
for(int i=1;i<=n;i++){
    s[i]=s[i-1]+a[i];
    sum+=s[i];
}
```

下面考虑第二问。由于数组已经排好序，所以只有耗时相同的题目才能交换顺序。如果有 $x$ 道题的时间相同，那么一共就会有 $x!$ 种可能性。

代码如下：
```cpp
for(int i=2;i<=n;i++){
    if(a[i]==a[i-1]) t++;
    else{
        ans=ans*fac(t)%mod;
        t=1;
    }
}
```

### 完整代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+1,mod=1e9+7;
int n,a[N],s[N],sum,t=1,ans=1;
int fac(int x){
	int ans=1;
	for(int i=1;i<=x;i++) ans=ans*i%mod;
	return ans;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		s[i]=s[i-1]+a[i];
		sum+=s[i];
	}
	cout<<sum<<endl;
	for(int i=2;i<=n;i++){
		if(a[i]==a[i-1]) t++;
		else{
			ans=ans*fac(t)%mod;
			t=1;
		}
	}
	cout<<ans*fac(t)%mod<<endl;
}
```

---

## 作者：__hjwucj__ (赞：0)

# 题解：[AT_arc035_b アットコーダー王国のコンテスト事情](https://www.luogu.com.cn/problem/AT_arc035_b)

## 思路
### 第一问
考虑贪心。由于每道题所用时间都会累加到后面每一道题的罚时中，所以第 $n-x+1$ 道题产生的罚时是 $x\times t_i$ 分钟。所以，越靠前的题，罚时倍率就越大，于是我们就应该把耗时越短的题放到越靠前的位置。

我们对数组排序，然后将每道题的罚时累加起来，并记录做完每一道题时的时间。注意，这个数可能很大，而且不要求取模，所以需要开 `long long`。

这一段的代码如下：

```cpp
int ans=0,t=0;
for (int i=1;i<=n;i++) ans+=t+a[i],t+=a[i];
cout<<ans<<endl;
```
### 第二问
接着我们考虑第二问。因为消耗时间的顺序是确定且唯一的，只有耗时相同的题目才能交换顺序。假设原数列有 $k$ 个耗时相同的块，每块中题目数是 $cnt_i$，我们就要计算下式：

$$(\sum_{i=1}^k cnt_i!) \bmod (10^9+7)$$

由于每个数只会在一个块中，即 $\sum_{i=1}^kcnt_i\neq n$，所以我们可以预处理阶乘，总时间复杂度是 $O (n)$ 的。

代码如下：
```cpp
ans=1;
int cnt=1;
for (int i=1;i<=n;i++)
    if (a[i]!=a[i+1])
	{
        ans*=f[cnt];
        ans%=(int)1e9+7;
        cnt=1;
    } else cnt++;
cout<<ans<<endl;
```
## 代码参考
```cpp
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
int n,a[10001],f[10001];
signed main ()
{
	ios::sync_with_stdio (false);
	cin.tie (0);
	cout.tie (0);
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	sort (a+1,a+n+1);
	f[1]=1;
	for (int i=1;i<=10000;i++) f[i]=f[i-1]*i%(int)(1e9+7);
	int ans=0,t=0;
	for (int i=1;i<=n;i++) ans+=t+a[i],t+=a[i];
	cout<<ans<<endl;
	ans=1;
	int cnt=1;
	for (int i=1;i<=n;i++)
	    if (a[i]!=a[i+1])
		{
	        ans*=f[cnt];
	        ans%=(int)1e9+7;
	        cnt=1;
	    } else cnt++;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：2021zjhs005 (赞：0)

Description
------------

给定 $\texttt{ARC}$ 做出 $n$ 道题目的每题所需的时间 $a_1$，$a_2$，$\cdots$，$a_n$，每次罚时为比赛开始到做出题目，请解决如下问题：

- 最小的比赛罚时。

- 最小的比赛罚时的方案总数，答案对 $10^9 + 7$ 取余。


Solution
------------

- 对于第一问，就是[排队接水问题。](https://www.luogu.com.cn/problem/P1223)为了让后面的做出题目的罚时最小，我们应该让做出时间短的排在前面。

- 对于第二问，明显，只有相同的做题时间交换才可以成为新的方案。如果有 $k$ 个相同的做题时间，那么对答案的贡献时则为乘 $k!$。对于阶乘，我们可以预处理。


Code
------------

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define pr printf

inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

const int N = 10005 , MOD = 1e9 + 7;
int n,cnt,ans;
int a[N],b[N],fact[N];

signed main(){
  n = read();
  rep(i,1,n) a[i] = read();
  sort(a+1,a+1+n);
  rep(i,1,n) ans += a[i] * (n - i + 1);//答案 1。
  pr("%lld\n",ans);
//------------------------
  ans = 1;
  rep(i,1,n)
    if(a[i] != a[i - 1]) b[++cnt] = 1;
    else b[cnt]++;//统计各个相同的时间。
  fact[0] = 1;
  rep(i,1,n) fact[i] = fact[i - 1] * i % MOD;//预处理阶乘。
  rep(i,1,cnt) ans = ans * fact[b[i]] % MOD;//计算答案 2。
  pr("%lld\n",ans);
  return 0;
}
```

---

## 作者：lpx666666 (赞：0)

## 题面
给定一个长度为 $n$ 的数组，求每道题完成时相加的最小值的和与排序方式。
## 思路
这道题很明显用贪心。我们可以想，每个数要做到最小值，那就必须要从小到大做题，因为一道题每次完成的时刻就相当于前面所有的时间加这道题，那前面的时间肯定越小越好，所以直接排序，枚举相加即可。

第二问可以用桶和小学奥数的排列组合解决，用桶记录单个数的数量，相同的数可以调换位置，所以假设一个数的数量为 $k$，那么这些书的排列方法就有 $A^k_k$ 种，将所有数的排列方法相乘即可。
### 注意
记得取余 $10^9 + 7$。

## 代码
提交的时候出现大大小小的错误，这道题还是要很细心的。

这是精简很多的代码了。
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#define int long long 
using namespace std;
const int mod=1e9+7;//取余的数 
int n,a[100005],arr[100005],ans=1,o,p;  
signed main(){//本人比较懒，也可以把所有int手改为longlong 
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		arr[a[i]]++;//用桶计数 
	}
	sort(a+1,a+1+n);//排序 
	for(int i=1;i<=n;i++){//计算最小值 
		p+=a[i];
		o+=p; 
	}
	for(int i=1;i<=100005;i++){//枚举桶 
		if(arr[i]!=0){//数组中包含此数 
			int r=1;
			for(int j=1;j<=arr[i];j++){//计算 
				r=(r%mod*(j%mod))%mod;//取余 
			}
			ans=(ans%mod*(r%mod))%mod;//将每个数的结果相乘 
		}
	}
	cout<<o<<endl<<ans%mod<<endl;//输出 
	return 0;//华丽结尾 
}
```

---

## 作者：Slient_QwQ (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Manipula/p/17740873.html)

## 前置芝士
[排列组合](https://oi-wiki.org/math/combinatorics/combination/)
## 分析

明显的贪心，第一问与[此题](https://www.luogu.com.cn/problem/P1223)思路相似，优先选择做时间少的，可以尽可能让后面的罚时尽量的小。

难点在第二问，第二问问的是有几种可能性，有个显然的结论：相同做题时间的题目，位置调换答案仍然相同。

那么可以用 桶+排列组合 来解决：

用桶储存这个做题时间的出现次数 $b_i$，然后进行遍历，如果这个数出现多次，那么 $ans \leftarrow ans \times b_i!$。

注意输出答案时，结尾要有换行。~~AT 老 bug 了~~。

## Accpeted Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e4 + 5;
const int mod = 1e9 + 7;
int t[N], b[N], now, mx, ans1, ans2 = 1;
int fac(int n)
{
	int res = 1;
	for (int i = 1; i <= n; i++)res = (res * i) % mod;
	return res;
}
signed main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)cin >> t[i];
	sort(t + 1, t + n + 1);
	for (int i = 1; i <= n; i++)
	{
		now += t[i];
		mx = max(mx, t[i]);
		b[t[i]]++;
		ans1 += now;
	}
	for (int i = 1; i <= mx; i++)
		if (b[i])ans2 = (ans2 * fac(b[i])) % mod;
	cout << ans1 << endl << ans2 << endl;
	return 0;
}
```

---

## 作者：SMall_X_ (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT_arc035_b)

---

## 思路分析

### 第一问

考虑贪心，不难想到要先完成所用的时间少的，因为每道题所用的时间都会累加到后面的题目的罚时中，前面的用时会对后面的罚时产生影响。

贪心排完序后按题意模拟即可，注意要开 `long long`。

### 第二问

根据第一问，不难证明最优开题顺序肯定是唯一的，即开题顺序不能改变，因为任意两道题所需要的时间可能相同（这也是为什么会有开题顺序总数），所以我们可以交换所需要的时间相同的两道题的先后顺序。

考虑排列组合，设 $n$ 表示当前相同的题数，求 $n$ 个数调换顺序组成的方案数不就是小学学过的 **全排列** 问题吗，方案数很明显为 $n!$，记得对 $10^9+7$ 取模。

---
注意 Atcoder 题输出最后要换行。

## $\texttt{code}$

```cpp
/*Written by smx*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=1e4+5,inf=1e18,mod=1e9+7; 
int t[MAXN],cnt[MAXN];
int f(int n){
	int ret=1;
	for(int i=2;i<=n;i++){
		ret=(ret*i)%mod;
	}
	return ret;
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,Time=0,maxn=INT_MIN,ans1=0,ans2=1;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>t[i];
		maxn=max(maxn,t[i]);
	}
	sort(t+1,t+n+1);
	for(int i=1;i<=n;i++){
		Time=Time+t[i];
		cnt[t[i]]++;
		ans1=ans1+Time;
	}
	for(int i=1;i<=maxn;i++){
		if(cnt[i]>0){
			ans2=(ans2*f(cnt[i]))%mod;
		}
	}
	cout<<ans1<<"\n"<<ans2<<"\n";
	return 0;
}
```

---

## 作者：smartdevil (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc035_b)、

## 题面：

给出 $n$ 道题目所需的时间，每道题的罚时是做完这道题时的时间。

第一问：求最小罚时。

第二问：最小罚时有多少种法案，答案对 $10^9+7$ 取模。

## 思路：

第一问：明显的贪心，优先做时间少的，让后面的罚时最少。

第二问：虽然所有题目要按做题时间从小到大排序，但是可能有题目时间相同。对于这些用时相同的题目，改变他们的顺序不会影响到答案，所以可以组成新的方案。

假设有 $n$ 道时间相同的题目，就可以组成 $n!$ 种方案。

输出后再换行就行了。

---

## 作者：zyc230721hzx (赞：0)

蒟蒻的第一篇题解。

[题目传送门](https://www.luogu.com.cn/problem/AT_arc035_b)

做本题前，建议先练习 [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)。
### 题意：

已知每题所需时间，求最小等待时间和方案总数。

 
### 第一问
  
- 考点：贪心，排序。

- 思路：

很明显，要使等待时间和（罚时）最小，应先做花费时间长的题目。

1. 先对每题所花时间进行从大到小排序：


```cpp
sort(a+1,a+1+n,greater<int>());
```
greater 函数可将 sort 的排序顺序转为从大到小，当然也可以手写 cmp 排序函数。

2. 循环遍历数组，每题时间应乘以等待次数：


```cpp
for(long long i=1;i<=n;i++){
		anss1+=(i*a[i]);
		js[a[i]]++;//为第二题做准备
}
```


3. 输出结果。
  
### 第二问

- 考点：排列组合。

- 思路：

  
显然只有耗时相同的题目可以进行交换，从而产生不同的方案。

计算耗时相同题目的数量 `js[i]`（可以用计数数组或 map）。

由排列组合公式得

$$P _ {js _ i} ^ {js _ i}= \frac{js _ i!}{(js _ i-js _ i)!}=\frac{js _ i!}{0!}=\frac{js _ i!}{1}=js _ i!$$

（‘！’表示阶乘）

而总方案数为

$$\prod _ {i=1} ^ {\max{a _ i}} js _ i$$

### AC 代码（c++版）：


```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MOD=1000000007;
long long n,a[10005],anss1=0,anss2=1;
long long js[10005];
inline long long jc(long long n){//求阶乘函数
	long long a=1;
	n++;
	while(--n)a*=n,a%=MOD;
	return a;
} 
int main(){
	cin>>n;
	for(long long i=1;i<=n;i++){
		cin>>a[i];
	}sort(a+1,a+1+n,greater<int>());//第一问
	for(long long i=1;i<=n;i++){
		anss1+=(i*a[i]);
		js[a[i]]++;
	}cout<<anss1<<"\n";
	for(long long i=1;i<=10000;i++){//第二问
		if(js[i])anss2*=jc(js[i]);
	}cout<<anss2<<"\n";
	return 0;
}

```

### 注意点：

- 排序要**从大到小**；
- 记得**取模**。
- 记得**开 `long long`**。

**预祝 AC**

---

## 作者：liyp (赞：0)

## 思路
很明显的贪心。

### 第一问
这里重新解释一下罚时，这里的罚时是指你做完这一道题的时间，因此罚时之和就是**每一道题做完的时间之和**。

因此我们经过推导就可以得出一个结论：要想让罚时之和最小，就要让每一道题对做后面的题的罚时影响尽可能小。

这样我们就只需要用自带的 ``sort`` 排个序，把做题时间更小的题目放在前面，然后再从前往后扫一遍就行了。

```cpp
sort(a+1,a+1+n); // 从小到大排序
for(int i=1;i<=n;i++){ //从前往后扫，优先扫时间小的题目
    ans1+=t+a[i];//罚时和加上第 i 道题的罚时
    t+=a[i];//现在已经用的时间加上做这道题的时间
}
cout<<ans1<<endl;//输出答案
```
### 第二问
怎么来算方案数呢？其实很简单。

首先，刚刚我们已经说了所有题目要按做题时间从小到大排序，这个是改不了的。但是可能有很多道题目做题时间相同。对于这些用时相同的题目，改变他们的顺序既不会影响到答案，又可以组成新的方案。

假如有 $m$ 道题目做题时间相同，那么它们可以组成 $m!$ 种不同的方案。

这一问就做出来了：
```cpp
t=1;
for(int i=2;i<=n;i++){
    if(a[i]==a[i-1]){
        t++;
    }
    else{
        ans2*=cal(t);//cal 函数是用来求阶乘的，要自己手搓
        ans2=ans2%mod;
        t=1;
    }
}
// 最后别忘了再算一次
ans2*=cal(t);
ans2=ans2%mod;
cout<<ans2<<endl;
```

## 完整代码
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 1e5 + 10;
int a[MAXN], n, m;
const int mod = 1e9 + 7;
LL ans1 = 0,t=0,ans2=1;
LL cal(LL x){
    if(x<1) return 0;
    if(x==1) return 1;
    return x*cal(x-1)%mod;
    
}
signed main()
{
    int T;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++){
        ans1+=t+a[i];
        t+=a[i];
    } 
    cout<<ans1<<endl;
    t=1;
    for(int i=2;i<=n;i++){
        if(a[i]==a[i-1]){
            t++;
        }
        else{
            ans2*=cal(t);
            ans2=ans2%mod;
            t=1;
        }
    }
    ans2*=cal(t);
    ans2=ans2%mod;
    cout<<ans2<<endl;
    return 0;
}
```

---

