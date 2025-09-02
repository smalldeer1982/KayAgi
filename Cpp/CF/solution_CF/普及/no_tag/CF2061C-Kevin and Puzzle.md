# Kevin and Puzzle

## 题目描述

有 $n$ 个人排成一行，第 $i$ 个人说他的左边有 $a_i$ 个说谎的人。

每个人要么诚实，要么说谎，诚实的人总是说真话，说谎的人说的话可真可假，没有两个说谎的人站在一起。

两个方案被认为是不同的，应当使至少一个人在一个方案诚实，在另外一个方案说谎。请输出不同的方案数对 $998244353$ 取模的结果。

## 样例 #1

### 输入

```
8
3
0 1 2
5
0 0 0 0 0
5
0 0 1 1 2
5
0 1 2 3 4
5
0 0 1 1 1
5
5 1 5 2 5
1
0
4
2 3 1 1```

### 输出

```
1
2
3
0
4
1
2
0```

# 题解

## 作者：ARIS2_0 (赞：6)

### 思路

下文认为第 $0$ 个人是好人，钦定 $a_0=0$。

考虑两个非常好的性质：

- 如果第 $i$ 个人和第 $i-1$ 个人都是好人，则有 $a_i=a_{i-1}$；

- 如果第 $i-1$ 个人是骗子，第 $i$ 个人是好人，由于第 $i-2$ 个人一定也是好人，则有 $a_i=a_{i-2}+1$。

我们可以根据上述性质进行 $O(n)$ 的 DP。 

设 $f_{i,0/1}$ 为已经钦定前 $i$ 个人的身份，且第 $i$ 个人为骗子/好人的方案数。

初始状态：$f_{1,0}=1,f_{1,1}=\begin{cases}1,a_1=0\\0,a_1\not=0\end{cases}$

第 $i$ 个人是骗子，只要上一个人不是骗子即可。

第 $i$ 个人是好人，分两种情况：

- 第 $i-1$ 个人是好人，此时要求 $a_i=a_{i-1}$；

- 第 $i-1$ 个人是骗子，此时要求 $a_i=a_{i-2}+1$。

则转移方程为（其中 $[B]$ 为艾佛森括号，$B$ 为真时返回值为 $1$，否则为 $0$）：

$$\begin{cases}f_{i,0}=f_{i-1,1}\\f_{i,1}=f_{i-1,1}\times [a_i=a_{i-1}]+f_{i-1,0}\times [a_i=a_{i-2}+1]\end{cases}$$

答案为 $f_{n,0}+f_{n,1}$，记得随时取模。

### Code

```cpp
#include<algorithm>
#include<bitset>
#include<deque>
#include<iomanip>
#include<iostream>
#include<iterator>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<utility>
#include<vector> 
#include<chrono>
#include<random>
#include<tuple>
#include<unordered_map>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define debug1(x) cerr<<#x<<"="<<x<<" "
#define debug2(x) cerr<<#x<<"="<<x<<"\n"
const int inf=1e16,mod=998244353;
int n,m,a[1000010],b[1000010],k,dp[1000010][2];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		//for(int i=1;i<=m;i++)cin>>b[i];
		if(a[1]==0)dp[1][1]=1;
		else dp[1][1]=0;
		dp[1][0]=1;
		for(int i=2;i<=n;i++){
			dp[i][0]=dp[i-1][1];
			dp[i][1]=0;
			if(a[i]==a[i-1])(dp[i][1]+=dp[i-1][1])%=mod;
			if(a[i]==a[i-2]+1)(dp[i][1]+=dp[i-1][0])%=mod;
		}
		cout<<(dp[n][0]+dp[n][1])%mod<<"\n";
	}
	return 0;
}
/*
clang++ -std=c++14 -Wall -Wextra -Wshadow -Wconversion -Wl,-stack_size -Wl,512000000 pos.cpp -o pos
*/
```

---

## 作者：CraaazyShep (赞：4)

### 分析

考虑 dp 求解。

方便起见我们不妨假设 $f_{1,i}$ 表示以 $i$ 为结尾，且假设 $i$ 号人是好人的方案数，$f_{2,i}$ 同理但是假设 $i$ 号是骗子。

首先先看 $f_{2,i}$：由于我们已经假设 $i$ 号可能在胡说八道，那 $a_i$ 的值就不重要了，同时又由于两个骗子不可能相邻，因此我们可以直接继承 $i-1$ 是好人的情况。即 $f_{2,i} \gets f_{1,i-1}$。

然后考虑 $f_{1,i}$：先假设 $i-1$ 号也是好人，假如 $i-1,i$ 都说真话，由于两人左侧的骗子数量一样多，所以只有当 $a_{i-1} = a_i$ 时，才可以把 $f_{1,i-1}$ 添加到 $f_{1,i}$。

假设 $i-1$ 号是骗子的思路也很相似。如果 $i-1$ 是骗子，那么 $i-2,i$ 一定都说真话，就需要有 $a_{i-2} + 1 = a_i$。如果成立就可以把 $f_{2,i-1}$ 添加到 $f_{1,i}$。

初始条件是 $f_{2,1}=1$。如果 $a_i = 0$ 则 $f_{1,1}=1$，否则 $f_{1,1}=0$。按上述思路 dp 即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mo=998244353;
long long t,n;
void solve(){
	cin>>n;
	vector<long long>a(n+1),f1(n+1),f2(n+1);
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	if(a[1]==0){
		f1[1]=1;
		f2[1]=1;
	}
	else{
		f1[1]=0;
		f2[1]=1;
	}
	for(int i=2;i<=n;i++){
		f2[i]=f1[i-1];
		if(a[i]==a[i-1]){
			f1[i]=(f1[i]+f1[i-1])%mo;
		}
		if(a[i]==a[i-2]+1){
			f1[i]=(f1[i]+f2[i-1])%mo;
		}
	}
	cout<<(f1[n]+f2[n])%mo<<"\n";
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：zazic (赞：3)

动规题。

**动态规划分为 $4$ 步：**

* 一、定义数组元素含义。

* 二、找到数组元素之间的关系式。

* 三、找出初始值。

* 四、检查初始化与边界。

首先我们根据测试样例，可以发现判别一个人是否说谎的方法。

我们设当前是第 $i$ 个人。

* 性质一：如果第 $i$ 个人说谎，那么根据题目所给“没有两个说谎的人站在一起”这一性质得到第 $i-1$ 个和第 $i+1$ 个位置的数字相差为 $1$。
  
* 性质二：如果第 $i$ 个和第 $i-1$ 个人说的都是真话，那么他们位置上的数字相等。

性质找完了，我们开始考虑使用 $dp$ 求解。

**第一步**

设 $f_{i,0/1}$ 为当前递推到了第 $i$ 个人，且第 $i$ 个人说的是真话/谎话的方案数。

**第二步**

可以发现，若第 $i$ 个人说谎，那么说明他的前面的人和后面的人说的都是真话，$f_{i,1}$ 的方案数即为 $f_{i,0}$。

若第 $i$ 个人说真话，那么他的前面的人说的可能是真话也可能是谎话，我们需要分类讨论。

* 若前面的人说的是谎话，需要满足**性质一**，即要求第 $i$ 和第 $i-2$ 的位置上的数相差为 $1$，若满足条件加上 $f_{i-1,1}$。 

* 若前面的人说的是谎话，需要满足**性质二**，即要求第 $i$ 和第 $i-1$ 的位置上的数相等，若满足条件加上 $f_{i-1,0}$。

**第三步**

$f_{1,0}=0/1,f_{1,1}=1$。

从第一个位置入手，可以发现第一个位置不管是什么数字一定存在可以说谎的方案，且不一定存在说真话的方案：若第一个位置的数字不为 $0$ 则说谎，反之可能说真话，如此初始化即可。

**第四步**

自己检查一下吧，别忘了取模。

**AC代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=2e5+10,p=998244353;
int t,n,a[N],f[N][2];

signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			f[i][0]=0;f[i][1]=0;
		}
		f[1][1]=1;
		if(a[1]==0) f[1][0]=1;
		else f[1][0]=0;
		for(int i=2;i<=n;i++){
			f[i][1]=f[i-1][0];
			if(a[i]==a[i-1]){
				f[i][0]+=f[i-1][0];
				f[i][0]%=p;
			}
			if(a[i]==a[i-2]+1){
				f[i][0]+=f[i-1][1];
				f[i][0]%=p;
			}
		}
		int ans=(f[n][0]+f[n][1])%p;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Eous (赞：1)

[差不多的阅读体验](https://www.cnblogs.com/Eous/articles/18683138)

### 题意

有 $n$ 个人，从左开始的第 $i$ 个人说他左边有 $a_{i}$ 个说谎者。但是有些人会说谎，所以他们的 $a_{i}$ 不可信。说谎者不能相邻。求有多少种不同的情况。两种情况不同当且仅当有一个人在一种情况中说谎了而在另一种里没有。

### 题解

我们可以套路的设 $dp_{i,0/1}$ 表示处理到了第 $i$ 个人，这个人说谎或没说谎。第二维是 $0$ 表示他说谎了，为 $1$ 表示没有说谎。那么初始化就是 $dp_{1,0} = 1,dp_{1,1} = [a_{1} = 0]$。现在来考虑转移，分两种情况：

- 第 $i$ 个人说谎了，那么上一个人必定不可能说谎，有 $dp_{i,0} \leftarrow dp_{i - 1,1}$。
- 第 $i$ 个人没说谎，那么又得分两种情况。
- - 第 $i - 1$ 个人说谎了。那么第 $i - 2$ 个人肯定没有说慌，且 $a_{i} - a_{i - 2}$ 一定为要为 $1$，因为中间夹了一个说谎的。有 $dp_{i,1} \leftarrow dp_{i - 1,0}$
  - 第 $i - 1$ 个没说谎，那么一定要满足 $a_{i} = a_{i - 1}$，因为他俩说的都是真话且他俩中间不会有说谎者。有 $dp_{i,1} \leftarrow dp_{i - 1,1}$。

最终的答案就是 $dp_{n,0} + dp_{n,1}$。

[submission](https://codeforces.com/contest/2061/submission/302162000)

upd：更新错别字

---

## 作者：K_yuxiang_rose (赞：0)

考虑用动态规划解决问题，设 $dp_{i,0}$ 代表前 $i$ 个人，第 $i$ 个人为骗子的方案数，$dp_{i,1}$ 代表前 $i$ 个人，第 $i$ 个人为好人的方案数。

如果第一个人为骗子，那方案数为一，即 $dp_{1,0}=1$。

如果第一个人为好人，如果 $a_1=0$，那说明他没说谎，方案数为一，即 $dp_{1,1}=[a_1=0]$。

题目给我们标出了一个性质：

>**不能有两个骗子站在一起。**

所以，当第 $i$ 个人为骗子时，第 $i-1$ 个人必定是好人，得 $dp_{i,0}=dp_{i-1,1}$。

当第 $i$ 个人为好人时：
>当第 $i-1$ 个人为好人时，当且仅当 $a_i=a_{i-1}$，第 $i$ 个人才为好人。
>
>当第 $i-1$ 个人为骗子时，第 $i-2$ 个人为好人，当且仅当 $a_i=a_{i-2}+1$，第 $i$ 个人才为好人。

得：$dp_{i,1}=dp_{i-1,1}\times[a_i=a_{i-1}]+dp_{i-1,0}\times[a_i=a_{i-2}+1]$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int a[200005],b[200005],dp[200005][2];
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i],dp[i][0]=dp[i][1]=0;
		dp[1][0]=1;
		if(a[1]==0) dp[1][1]=1;
		for(int i=2;i<=n;i++)
		{
			dp[i][0]=dp[i-1][1];
			if(a[i]==a[i-1])
			dp[i][1]+=dp[i-1][1];
			if(a[i]==a[i-2]+1)
			dp[i][1]+=dp[i-1][0];
			dp[i][1]%=mod;
		}
		cout<<(dp[n][0]+dp[n][1])%mod<<"\n";
	}
	return 0;
}
```

https://codeforces.com/problemset/submission/2061/305443375

---

## 作者：Wide_Master (赞：0)

## 题意

$t$ 组数据。

$n$ 个人站成一排，第 $i$ 个人会告诉你他的左边有 $a_i$ 个说谎者。

每个人有两种身份，诚实者和说谎者，诚实者一定会说真话，说谎者可能会说真话，也可能会说假话。

说谎者之间不能相邻。

现在问你游戏一共有多少种**不同的**情况。答案对 $998244353$ 取余。

## 思路

考虑动态规划，我们可以用一个数组 $dp$ 来统计答案。其中 $dp_{i,0/1}$ 用来统计第 $i$ 个人是诚实者/说谎者产生的贡献。

继续考虑初始化，我们可以初始化第 $1$ 个人的，因为他只有是诚实者或说谎者两种可能。如果他是诚实者，那么就是 $1$ 种情况，也就是说真话，即 $dp_{i,0}=1$，如果他是说谎者，那么就要判断他说的是不是真话，我们可以判断 $a_i$ 是否为 $0$，因为他左边已经没有人了。所以初始化为 $dp_{i,1}=[a_1=0]$。

接下来考虑转移方程，如果第 $i$ 个人是说谎者，那么第 $i-1$ 个人绝对不可能是说谎者，即 $dp_{i,0}\gets dp_{i-1,1}$。

如果第 $i$ 个人不是说谎者，那么就需要继续考虑。

- 第 $i-1$ 个人是说谎者。那么第 $i-2$ 个就一定不是说谎者。这需要满足 $a_i-1=a_{i-2}$，因为他们之间夹了一个说谎者。即 $dp_{i,1}=dp_{i-1,0}$。
- 第 $i-1$ 个人是诚实者。那么就需要满足 $a_i=a_{i-1}$，因为他们都是诚实者，所以不可能有差别。即 $dp_{i,1}\gets dp_{i-1,1}$。

最终的答案为 $dp_{n,0}+dp_{n,1}$。注意多测清空。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353,N=2e5+7;
int n,a[N],dp[N][2],t;
int main()
{
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        dp[1][0]=1;
        if(a[1]==0)dp[1][1]=1;
        else dp[1][1]=0;
        for(int i=2;i<=n;i++){
            dp[i][0]=dp[i-1][1];
            dp[i][1]=0;
            if(a[i]==a[i-1])dp[i][1]=(dp[i][1]+dp[i-1][1])%mod;
			if(a[i]-1==a[i-2])dp[i][1]=(dp[i][1]+dp[i-1][0])%mod;
        }
        cout<<(dp[n][0]+dp[n][1])%mod<<endl;
    }
    return 0;
}
``````

---

## 作者：yvbf (赞：0)

![](bilibili:BV1MuwverEdQ?t=547)

---

## 作者：Kendieer (赞：0)

原题：[**\[CodeForces\]**](https://codeforces.com/contest/2061/problem/C)、[**\[洛谷\]**](/problem/CF2061C)。

---

赛时差点以为是线段树优化 dp 了，还是自己太蒻了。

## 思路构筑

由于每个人都有两种状态：说真话、说假话，并且所有人说的话只对左边的人进行判断（无后效性），所以考虑动态规划。

设 $dp_{i,j}$ 为第 $i$ 个人说的是真/假话情况下前 $i$ 个人存在的方案数。（不妨设 `j=0` 为真话，`j=1` 为假话）

关于初值：

+ 无论如何，我们都可以假设第一位说了假话，所以 $dp_{1,1} = 1$。
+ 当第一位说 $0$ 时，才会有可能说真话，所以当且仅当 $a_1=0$ 时 $dp_{1,0}=1$，否则为 $0$。

于是我们就可以分析递推式：

+ 当此时说的是假话时，由于不能存在 $2$ 名相邻的说谎者，所以方案数就是上一位说真话的方案数 $dp_{i-1,0}$。
+ 当此时说的是真话时就要分类讨论了：
  + 当上一位说的是真话时，则必须满足 $a_i=a_{i-1}$，否则与前者说真话的人相冲突。
  + 当上一位说的是假话时，则倒数第二位必然说的是真话，此时断言说谎者数量必然要满足 $a_i=a_{i-2}+1$，否则不能转移相应方案。

记得处理 $dp_{0,0} = 0$，不然转移 $dp_{2,0}$ 时会出问题。

## Code

``` cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define rep(i,a,b) for(ll i = (a);i < (b);i++)
#define repr(i,a,b) for(ll i = (b) - 1;i>= (a);i--)
#define elif else if
#define Code_by_Kendieer return 0
typedef long long ll;
typedef unsigned long long ull;
const ll inf = 0x3f7f7f7f7f7f7f7f;

ll qread();
char readChar();
void qwrite(ll x,int t = 10);

const int maxn = 2e5 + 7;
const int mod = 998244353;
struct Node {};
ll dp[maxn][2];// truth,lie
int arr[maxn];
int n;


void solve(){
    n = qread();
    rep(i,0,n+1) dp[i][0] = dp[i][1] = 0; // init
    rep(i,1,n+1) arr[i] = qread();
    dp[1][0] = arr[1] == 0,dp[1][1] = 1;
    rep(i,2,n+1){
        if (arr[i] == arr[i-1]) dp[i][0] += dp[i-1][0],dp[i][0] %= mod;
        dp[i][1] += dp[i-1][0],dp[i][1] %= mod;
        if (arr[i] == arr[i-2]+1) dp[i][0] += dp[i-1][1],dp[i][0] %= mod;
    }
    cout << (dp[n][0] + dp[n][1]) % mod << endl;
}

int main(){
    // cin.tie(0),cout.tie(0);
    // ios::sync_with_stdio(0);
    int t = 1;
    t = qread();
    while(t--) solve();
    Code_by_Kendieer;
}

// =====================================================
ll qread(){
    ll r = 0,s = 1,ch = getchar();
    while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
    if (ch == '-') ch = getchar(),s = -1;
    while (ch >= '0' && ch <= '9') r = r * 10 + ch - '0',ch = getchar();
    return r * s;
}
char readChar(){
    int ch = getchar();
    while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
    return ch;
}
void qwrite(ll x,int t){
    if (x<0) putchar('-'),x=-x;
    if (x>=t) qwrite(x/t,t);
    putchar(x%t<10?'0'+x%t:'A'-10+x%t);
}
// =====================================================
```

---

## 作者：UniGravity (赞：0)

### Solution CF2061C Kevin and Puzzle

大炮打蚊子做法。

首先能写出一个简单的平方 dp：记 $f_{i,j,0/1}$ 表示前 $i$ 个人有 $j$ 个说真话，第 $i$ 个是否说真话的方案数。则有：

$$
\begin{align*}
f_{i,j,0}&=f_{i-1,j,1} \\
f_{i,j,1}&=\begin{cases}
f_{i-1,j-1,0}+f_{i-1,j-1,1} & i-j=a_i\\
0 & otherwise.
\end{cases}
\end{align*}
$$

发现形式为交换两个数组，然后将其中一个全部赋值为 $0$ 再对其中某一个单独操作。

交换数组可以通过滚动代替掉，赋值为 $0$ 直接使用线段树维护数组并且打标记即可。

时间复杂度 $O(n\log n)$。

---

## 作者：zhangxiao666 (赞：0)

钦定 $i$ 为好人。

若 $i-1$ 为好人，则 $a_{i-1}=a_i$。

若 $i-1$ 为坏人，则 $a_{i-2}+1=a_i$。

记 $f_i$ 表示钦定 $i$ 为好人时前 $i$ 的方案，转移枚举 $i-1$ 是好是坏，符合条件就加。


具体的，若 $a_{i-1}=a_i$，则 $f_{i-1}\to f_i$，若 $a_{i-2}+1=a_i$，则 $f_{i-2}\to f_i$。

答案为 $f_n + f_{n-1}$。

[code](https://codeforces.com/contest/2061/submission/302230659)

---

## 作者：_anll_ (赞：0)

## 前言
想不出做法时可以水会儿 qq，水完应该就有思路了。
## 思路
刚开始看了以为是奇怪搜索或者构造，结果水了会儿回来突然看到**方案数**，这很坏了。

方案数的话就和 dp 八九不离十了。状态很好想，$dp[i][0/1]$ 表示第 $i$ 个人没说/说谎的方案数。但何时该转移就需要结合 $num$ 数组了。

首先，对于 $dp[i][1]$ 而言，显然能且仅能拿 $dp[i-1][0]$ 转移，原因是不管其有没有撒谎都可以被称为骗子，所以没有额外的约束。而对于 $dp[i][0]$ 而言，如果要从 $dp[i-1][1]$ 转移，那 $i-2$ 在此时一定不是骗子，两个都是真话，因此 $num_i$ 一定比 $num_{i-2}$ 多 $1$，那个 $1$ 就是 $i-1$ 贡献的；反之，如果要从 $dp[i-1][0]$ 转移，因为两个都是真话，所以 $num_i=num_{i-1}$。

然后就这么结束了。注意取模。

## 代码
赛时代码比较丑提前致歉。
```cpp
#include<queue>
#include<iostream>
#define int long long
#define mod 998244353
using namespace std;
const int N=2e5+5;
int n,m,t,num[N],dp[N][2];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>num[i];
	for(int i=1;i<=n;i++) dp[i][1]=dp[i][0]=0;
	dp[1][1]=1;
	if(!num[1]) dp[1][0]=1;
	for(int i=2;i<=n;i++){
		if(num[i]==num[i-2]+1) dp[i][0]+=dp[i-1][1];
		dp[i][0]%=mod;
		if(num[i]==num[i-1]) dp[i][0]+=dp[i-1][0];
		dp[i][1]=dp[i-1][0];
		dp[i][0]%=mod,dp[i][1]%=mod;
	}
	cout<<(dp[n][0]+dp[n][1])%mod<<endl;
}
signed main(){
	ios::sync_with_stdio(false); 
	cin.tie(0);cout.tie(0);
	cin>>t;while(t--) solve();
	return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[CF2061C](https://www.luogu.com.cn/problem/CF2061C)

## Solution

记 $dp_{i,0/1}$ 表示第 $i$ 个人是诚实 / 说谎人的方案数。

- 第 $i$ 个人是说谎者，$i - 1$ 必定为诚实，所以有 $a_{i - 1} + 1$ 个骗子。

- 第 $i$ 个人是诚实，所以有 $a_i$ 个说谎者。

转移方程：

$$
dp_{i,0} \leftarrow dp_{i,0} + dp_{i - 1,0}[a_i = a_{i-1}]
\\
dp_{i,0} \leftarrow dp_{i,0} + dp_{i - 1,1}[a_i = a_{i - 2} + 1]
\\
dp_{i,1} \leftarrow dp_{i,0} + dp_{i - 1,1}
$$

答案即为 $dp_{n,0} + dp_{n,1}$。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 10, MOD = 998244353;
int T, n, A[MAXN], dp[MAXN][2]; /* 0 : true 1 : false */
vector <int> Vec;

signed main() { 
    scanf ("%lld", &T);
    while (T --) {
        scanf ("%lld", &n);
        for (int i = 1; i <= n; i ++)
            scanf ("%lld", &A[i]);
        memset (dp, 0, sizeof dp);
        dp[0][0] = 1;
        for (int i = 1; i <= n; i ++) {
            if (i == 1 || A[i] == A[i - 2] + 1)
                dp[i][0] = (dp[i][0] + dp[i - 1][1]) % MOD;
            if (A[i] == A[i - 1])
                dp[i][0] = (dp[i][0] + dp[i - 1][0]) % MOD;
            dp[i][1] = (dp[i][1] + dp[i - 1][0]) % MOD;
        }
        Vec.push_back ((dp[n][0] + dp[n][1]) % MOD);
    }
    for (int Ans : Vec)
        printf ("%lld\n", Ans);
    return 0;
}
```

---

## 作者：_xguagua_Firefly_ (赞：0)

赛时想出来的神奇做法。

### 分析

问方案数，不是组合数学就是 DP，而这个组合数学似乎不可做，所以考虑 DP。

我们先大胆的设 $dp _ {i,0/1}$ 表示考虑前 $i$ 个人，第 $i$ 个人诚实或说谎。则转移方程如下：

$$
\begin{cases}
dp _ {i,0} \gets dp _ {i - 1,0} + dp _ {i - 1,1} \\
dp _ {i,1} \gets dp _ {i - 1,0}
\end{cases}
$$

但是这样显然不对，因为我们没考虑现在这个人的 $a _ {i}$ 是否满足要求。

所以，我们还需要记录一个 $sum$，表示现在已经确定的说谎的人个数的前缀和。如果 $a _ {i} \neq sum$，则不能转移。

这个东西不太好记录，所以我们不用递推，用记忆化搜索。如果这个人说谎，就不往下个人说谎的状态转移，同时注意如果枚举到 $n$ 了，就不能转移到 $n + 1$ 说谎的状态，否则答案会多。

发现 $sum$ 最多有 $\frac{n}{2}$，普通数组开不下，所以我们可以开 `gp_hash_table` 来记录。

### Code

```cpp
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

constexpr int MAXN = 2e5 + 5,MOD = 998244353;
int T;
int n,a[MAXN];
gp_hash_table<int,gp_hash_table<int,int> > dp[2];
inline int dfs(int pos,int sum,bool lie)
{
    if(pos > n)
        return 1;
    if((sum != a[pos]) && !lie) // 不满足条件，这个方案无效
        return 0;
    if(dp[lie][sum][pos])
        return dp[lie][sum][pos];
    int res = dfs(pos + 1,sum + lie,0);
    if(!lie && pos != n)
        res = (res + dfs(pos + 1,sum + lie,1)) % MOD;
    return dp[lie][sum][pos] = res;
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> T;
    while(T--)
    {
        dp[0].clear(),dp[1].clear();
        cin >> n;
        for(int i = 1;i <= n;i++)
            cin >> a[i];
        int ans = (dfs(1,0,0) + dfs(1,0,1)) % MOD;
        cout << ans << "\n";
    }
}
```

---

