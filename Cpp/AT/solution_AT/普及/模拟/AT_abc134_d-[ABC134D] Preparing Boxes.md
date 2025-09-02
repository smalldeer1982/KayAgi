# [ABC134D] Preparing Boxes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc134/tasks/abc134_d

$ N $ 個の空の箱が横一列に並んでいます。 左から $ i $ $ \ (1\ \leq\ i\ \leq\ N) $ 番目の箱には整数 $ i $ が書かれています。

すぬけさんは、それぞれの箱に対してボールを $ 1 $ 個入れるか何も入れないかを選ぶことができます。

ここで、以下の条件を満たすようなボールの入れ方を、いいボールの入れ方と定めます。

- $ 1 $ 以上 $ N $ 以下の任意の整数 $ i $ について、$ i $ の倍数が書かれた箱に入っているボールの個数の和を $ 2 $ で割った余りが $ a_i $ である。

いいボールの入れ方は存在するでしょうか。存在するならば $ 1 $ つ求めてください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ a_i $ は $ 0 $ または $ 1 $ である。

### Sample Explanation 1

$ 1 $ が書かれた箱だけにボールを入れることを考えます。 - $ 1 $ の倍数が書かれた箱は、$ 1 $ が書かれた箱、$ 2 $ が書かれた箱、$ 3 $ が書かれた箱の $ 3 $ 個です。これらの箱に入っているボールの個数の和は $ 1 $ です。 - $ 2 $ の倍数が書かれた箱は、$ 2 $ が書かれた箱の $ 1 $ 個だけです。これらの箱に入っているボールの個数の和は $ 0 $ です。 - $ 3 $ の倍数が書かれた箱は、$ 3 $ が書かれた箱の $ 1 $ 個だけです。これらの箱に入っているボールの個数の和は $ 0 $ です。 以上より、$ 1 $ が書かれた箱だけにボールを入れるのは、与えられた条件を満たすいいボールの入れ方です。

### Sample Explanation 2

ボールを $ 1 $ つも入れない入れ方が、いい入れ方になる場合もあります。

## 样例 #1

### 输入

```
3
1 0 0```

### 输出

```
1
1```

## 样例 #2

### 输入

```
5
0 0 0 0 0```

### 输出

```
0```

# 题解

## 作者：Super_Builder (赞：4)

## 简述题意

这什么破翻译，看了 AtCoder 的英文才看懂。

给定一个长度为 $n$ 序列 $a$，要求构造一个数列 $b$，使得对于任意 $i$，满足：
1. $1 \le i \le n$。

2. 将 $b$ 序列下标为 $i$ 的倍数的值相加使得这个总和模 2 等于 $a_i$。

求序列 $b$ 中值为 1 的个数与值为 1 的个数的位置。

## 解题思路

考虑可以逆序构造序列 $b$，因为判断条件只可能用到后面的值。  
如果不满足条件 2，则让 $b_i$ 等于 1，即可满足，并且计入答案，否则为 0。

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<int>ans;
int n,a[200005],cnt=0,b[200005];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",a+i);
	for(int i=n;i>=1;i--){
		int tmp=0;
		for(int j=i;j<=n;j+=i){
			tmp+=b[j];
		}
		if(tmp%2!=a[i]){
			b[i]=1;
			ans.push_back(i);
		}
	}
	printf("%lld\n",ans.size());
	for(auto x:ans){
		printf("%lld ",x);
	}
	return 0;
}
```


---

## 作者：零殇 (赞：3)

#### 题意

给到一个序列$A$，求一个序列$B$，满足对于任意一个下标$i$， 将所有是$i$的倍数的下标中储存的值相加，其和$mod2$的结果为$ai$，输出$B$序列中所有值为$1$的下标。

#### 思路

因为后面的数会将前面求得的答案影响，所以我们从后往前遍历。

对于$B[i]$的值，首先我们把除了$i$本身之外，所有下标是$i$的倍数储存的值相加并$mod2$。如果和$a[i]$相等，$B[i]$则等于$0$，否则等于$1$。

接下来我们证明这个算法。

当相等时，因为已经满足了这个题目要求，那么为了不影响，我们就将$B[i]$变成$0$。

即$B[i]=0$。

当不相等时，因为$A[i]$和我们的结果只有$0$和$1$两种情况，相当于，对于$mod$后的结果，我们要把$0$变成$1$，把$1$变成$0$。

那么，我们只要多加一个$1$，就能把$0$变成$1$；而$1$加$1$后等于$2$，由于我们的答案是$mod2$的。所以就会变成$0$。

即$B[i]=1$。

上代码：
```
#include<bits/stdc++.h>
using namespace std;
int a[200001],b[200001],flag[200001],num,n,sum; 
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=n;i>=1;i--)
	{
		sum=0;
		for(int j=i*2;j<=n;j+=i)
			sum+=b[j];
		sum%=2;
		if(sum!=a[i])
		{
			num++;
			b[i]=1;
			flag[num]=i;
		}
	}
	printf("%d\n",num);
	for(int i=1;i<=num;i++)
		printf("%d ",flag[i]);
	printf("\n");
	return 0;
}
```

完结撒花~

---

## 作者：STARSczy (赞：2)

# 思路：
我们令 $i$ 从 $n$ 开始枚举至 $1$，设输出序列为 $ans$，每次累计亦或 $ans$ 下标为 $i$ 的倍数的值（不含 $ans_i$），最开始亦或值为 $0$，判断是否与 $a_i$ 值相同，不相同只需将 $ans_i$ 更改为 $1$ 即可。这样可以保证每次只用修改 $ans_i$ 的值就可以满足条件，再加上每次枚举 $i$ 的倍数，均摊时间复杂度就是调和级数 $\Theta(n \log{n})$

# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+10;
int read(){
	int n=0,c,x=0;
	while((c=getchar())<'0'||c>'9') x=(c=='-');
	do n=n*10+c-'0';while((c=getchar())>='0'&&c<='9');
	return x?-n:n;
}
int write(int n){
	if(n<0) putchar('-'),n=-n;
	if(n>9) write(n/10);
	putchar(n%10+'0');
	return n;
}

int n=read(),a[maxn],len,ans[maxn];

signed main(){
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=n;i;--i){
		int cnt=0;
		for(int k=i<<1;k<=n;k+=i) cnt^=ans[k];//累计亦或
		if(cnt^a[i]) ans[i]^=1;
		if(ans[i]) len++;//统计数量
	}
	write(len),puts("");
	for(int i=1;i<=n;++i) if(ans[i]) write(i),putchar(' ');
	return 0;
}
```

---

## 作者：Kawaii_qiuw (赞：1)

### 题意：

给你一个序列 $a$，让你构造一个序列 $b$，序列里面只有数字 $0$ 和 $1$，满足以下条件：对于位置 $i$，将所有是 $i$ 的倍数的下标里的值相加，取余 $2$ 必须等于 $a_{i}$。

### 思路：

直接从后往前模拟一遍就可以了，因为后面的数会影响前面的数，所以必须先确定后面的数。

那么怎么确定 $i$ 位置的值是什么呢，只有将它的倍数的值全部加起来（除了一倍），如果取余和 $a_{i}$ 相等那么 $b_{i}$ 就是 $0$，否则的话改为 $1$。

### 代码


```cpp
#include<bits/stdc++.h>

#define ULL unsigned long long
#define LL long long
#define Max 100005
#define mem(a,b) memset(a,b,sizeof(a));
#define pb push_back
#define mp make_pair
const LL mod=1e9+7;
const ULL base=131;
const LL LL_MAX=9223372036854775807;
using namespace std;
int a[2*Max], b[2*Max];
vector<int> ans;
int main() {
    int n;
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = n; i >= 1; i--) {
        int sum = 0;
        for (int j = i + i; j <= n; j += i)
            sum += b[j];
        if (sum % 2 != a[i])
            b[i] = 1, ans.push_back(i);
    }
    printf("%d\n",ans.size());
    for (int i = 0; i < ans.size(); i++)
        printf("%d ", ans[i]);
    printf("\n");
    return 0;
}
```

[AC 记录。](https://www.luogu.com.cn/record/197236705)

完结撒花。

---

## 作者：__little__Cabbage__ (赞：1)

## Description

给定一个长度为 $n$ 的序列 $a$，求一个长度为 $n$ 的序列 $b$，使得对于 $i$，所有 $i$ 的倍数为下标，$b$ 中这些数的和 $\bmod~2=a_i$。

## Solution

由于 $i$ 的倍数一定 $\ge i$，所以考虑逆序构造序列 $b$。对于 $i$，每次统计一下除了 $b_i$ 之外以 $i$ 的倍数为下标的数之和，然后根据其 $\bmod~2$ 的结果判断 $b_i$ 的取值即可。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
//#define int long long
#define pb emplace_back
using namespace std;
const int MAXN=2e5+5;
int n,a[MAXN],b[MAXN];
vector <int> v;
signed main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	int sum;
	for(int i=n;i;--i)
	{
		sum=0;
		for(int j=i;j<=n;j+=i)
			sum+=b[j];
		if(sum%2!=a[i])
			b[i]=1,v.pb(i);
	}
	cout<<v.size()<<'\n';
	for(auto i:v)
		cout<<i<<' ';
	return 0;
}
```

---

## 作者：zcr0202 (赞：1)

## 题目大意

给你一个数组 $a$，让你求出数组 $b$，并且找出 $b$ 数组中 1 的数量且它们的坐标。

当 $1 \le i \le n$ 的时候，如果 $b$ 数组中是 $i$ 的倍数的坐标的值之和等于 $a_i$，那么 $b_i$ 就等于 1。

## 解题思路

按照题意模拟即可，不会超时。时间复杂度为 $\Theta(n \log{n})$。注意：求 $b$ 数组时要从 $n$ 开始枚举，因为即使没有求前面的数，也不会影响 $b_i$ 的结果。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int a[N], b[N], ans[N], d;
signed main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for(int i = n; i >= 1; i--) {	//从n开始枚举
		int s = 0;
		for(int j = i; j <= n; j += i) {
			s += b[j];
		}	//求出s
		if(s % 2 != a[i]) b[i] = 1, ans[++d] = i;	//加入答案数组
	}
	cout << d << '\n';
	for(int i = d; i >= 1; i--) {
		cout << ans[i] << " ";
	}
	return 0;
}
```

---

## 作者：zhouzihang1 (赞：1)

## 题意

给出长度为 $n$ 的序列 $a$，找一个长度为 $n$ 的序列 $b$。

对于序列 $b$，满足任意 $i$ $(1\le i \le n)$，所有下标为 $i$ 的倍数的值相加。

最后的结果等于 $a_i$。

求满足 $b_i$ 为 $1$ 的所有 $i$。

## 思路

题意已经清楚了，就可以直接模拟了。

### 注意

要从后往前遍历，因为计算时是计算 $i$ 后面的值相加，保证结果不受影响。

另外，记录答案有多种方式，我推荐使用 vector 记录答案，~~就是方便。~~

# AC Code

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=2e5+10;
int n,a[N],b[N];
vector<int> ans;
int main()
{
	scanf("%d",&n);//cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);//cin>>a[i];
	int cnt;
	for(int i=n;i>=1;i--)
	{
		cnt=0;
		for(int j=i;j<=n;j+=i) cnt+=b[j];
		cnt%=2;
		if(cnt!=a[i])
		{
			b[i]=1;
			ans.push_back(i);
		}
	}
	printf("%d\n",ans.size());//cout<<ans.size()<<endl;
	for(auto it:ans) printf("%d ",it);
	/*
	for(auto it:ans) printf("%d ",it);
	等同于：
	for(int i=0;i<ans.size();i++) cout<<ans[i]<<' '; 
	*/
    return 0;
}
```

---

## 作者：_GJM_ (赞：1)

###### [更好的阅读体验？](https://www.luogu.com.cn/blog/GeJiamu/solution-ABC134D)
## 题意
给一个序列 $A$，求一个序列 $B$。
   
满足对于任意一个下标 $i$，将所有是 $i$ 的**倍数**的下标中储存的值**相加**，其和 $\bmod\ 2$ 的结果为 $a_i$。
   
输出 $B$ 序列中所有值为 $1$ 的**下标**。
   
## 思路
题意很清楚了，可以直接模拟：
    
```cpp
int cnt=0;//记录所有是i的倍数的下标中储存的值。
	for(int j=i;j<=n;j+=i)//枚举i的倍数。
		cnt+=b[j];
	cnt%=2;
	if(cnt!=a[i]){//if((cnt+1)%2==a[i])
		b[i]=1;
		ans[k++]=i;//记录下标。
	}
```
   
### 注意
从后往前遍历，因为后面的数会影响前面的数。
## [AC Code](https://www.luogu.com.cn/paste/xf3vzqy4)


---

## 作者：YueYang1235 (赞：1)

[题目传送门（atcoder）](https://atcoder.jp/contests/abc134/tasks/abc134_d)

题目大意：

给你一个数列 a ,构造一个数列 b ,（两个数列中的数均为0或1）满足以下条件：

对于位置 $ i $, 将所有是 $ i $ 的倍数的下标的值相加，其和 $ mod $ $ 2 $ 的结果为 $ ai $

让你输出数列 b 中所有数字为 $ 1 $ 的下标


------------

由于后面的数会影响前面的数，所以必须先确定后面的数，所以要从后往前枚举。

那么怎么确定i位置的值是什么呢，只有将它的倍数的值全部加起来（除了一倍），如果取余和 $ a_i $ 相等那么bi就是0，否则的话改为1。

$ code $ :

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[205000],b[205000];
int ans[205000],len;
int main(){
  scanf("%d",&n);
  for(int i=1;i<=n;i++)scanf("%d",&a[i]);
  for(int i=n;i>=1;i--){
    int sum=0;
    for(int j=i*2;j<=n;j+=i)sum+=b[j];
    if(sum%2!=a[i]){
    	b[i]=1;
			ans[++len]=i;
    }
  }
  cout<<len<<endl;
  for(int i=1;i<=len;++i)cout<<ans[i]<<" ";
  return 0;
}
```

另外，第二个样例错了，应该输出0而不是什么也不输出，可见题目原网址。


---

## 作者：Yashajin_Ai (赞：1)

### 思路
这道题有一个很明显的拓扑序，因为后面的数会影响前面的数，所以从后找了，按照题目意思我们每次找他的倍数，根据 $b_i$ 修改，当前位置是否为一个合法的好位置，用 $ans_i$ 记录答案。

输出 $ans$ 序列中为 $1$ 的编号，反向输出。

时间复杂度：$O(n \log n)$，可以根据非收敛调和级数算出。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k=1;
bool a[200005];
bool b[200005];
int ans[200005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	} 
	for(int i=n;i>=1;i--){
		bool x=0;
		for(int j=i*2;j<=n;j+=i){
			if(b[j]){
				x=!x;
			}
		}
		if(x^a[i]){
			b[i]=1;
			ans[k++]=i;
		}
	}
	cout<<k-1<<endl;
	for(int i=k-1;i>=1;i--){
		cout<<ans[i]<<" ";
	}	
}
```

---

## 作者：Like_Amao (赞：0)

**前言**

[题目传送门](https://www.luogu.com.cn/problem/AT_abc134_d)

**题目大意**

逆天翻译，看了半天才懂。

输入一个长度为 $n$ 的数组 $a$，请你根据下面的条件来构造一个数组 $b$。

* 当 $1 \le i \le n$ 时，请构造一个 $b$ 数组满足每个下标为 $i$ 的倍数的 $b _ j$ 的和与 $a _ i$ 模二同余。

**思路**

首先我们可以用一个循环，在循环中建立一个变量 $sum$ 来记录 $b$ 数组中下标为 $i$ 的倍数的和，然后判断它模二的余数是否不等于 $a _ i$，如果不等于，就将 $b _ i$ 的值赋值为 1，然后用答案数组记录，最后输出 1 的个数和答案数组即可。

**代码**


```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200001],b[200001],ans[200001];
int main()
{
	long long n,cnt=0;
	cin>>n;
	for(long long i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(long long i=n;i>=1;i--)
	{
		long long sum=0;
		for(long long j=i;j<=n;j+=i)
		{
			sum+=b[j];
		}
		if(sum%2!=a[i])
		{
			b[i]=1;
			ans[++cnt]=i;
		}
	}
	cout<<cnt<<endl;
	for(long long i=cnt;i>=1;i--)
	{
		cout<<ans[i]<<" ";
	}
	return 0;
}
```

---

## 作者：Swirl (赞：0)

社贡要掉了，来写几篇。

> 涉及芝士点：构造。

构造入门练手好题。

### 思路简述

如果从 $b_1$ 开始构造，需要考虑的 $a$ 的值太多，不妨从 $b_n$ 开始逆序构造。

我们知道：

$$
a_i = \sum_{1 \le j \times i \le n} b_{j \times i} \bmod 2
$$

当我们处理到 $b_i$ 时，$b_i$ 以后的所有数已经确定，所以 $b_i$ 以后所有索引是 $i$ 的倍数的位置（不含 $b_i$）和 $a_i$ 已经确定，此时即可确定 $b_i$。

$$ 
b_i = (a_i - \sum_{1 \lt j \le n} b_{j \times i} \bmod 2 + 2) \bmod 2
$$

思路部分完毕。

### 代码

```cpp
namespace zqh {
int n, a[200005], b[200005];

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
}

void solve() {
    b[n] = a[n];
    for (int i = n - 1; i >= 1; i--) {
        int sum = 0;
        for (int j = i + i; j <= n; j += i) {
            sum += b[j];
        }
        sum &= 1;
        b[i] = (sum != a[i]);// 此处有简写，若 sum 等于 a[i] 则无需再加，否则需要用 1 调和。
    }
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (b[i])
            ans.push_back(i);
    }
    cout << ans.size() << endl;
    for (int x : ans) cout << x << " ";
}

void main() {
    init();
    solve();
}
}  // namespace zqh
```

---

## 作者：complete_binary_tree (赞：0)

题目大意：构造一个 $01$ 序列 $b$ 使得对于任意 $i$ 有 $\displaystyle \bigoplus_{i \mid j} b_j = a_i$。

---

我们发现每一个位置的改变只会影响它的因数。所以我们从后往前枚举，枚举到 $b_i$ 如果不等于 $a_i$ 的时候就把它和它的因数全都异或 $1$。这样就做完了。

时间复杂度 $O(n \sqrt n)$。

---

机房大佬 @[快斗游鹿](https://www.luogu.com.cn/user/356925) 的 $O(n \log n)$ 做法：每次检查它的倍数的异或和，如果相同该位不改变，如果不同该位改变。这样复杂度是调和级数的。

---

代码：

我的做法：(91ms)

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int a[N], b[N], n, ans, an[N];

int main(){
	scanf( "%d", &n );
	for( int i = 1; i <= n; ++i ) scanf( "%d", &a[i] );
	for( int i = n; i >= 1; --i ){
		if( a[i] ^ b[i] ){
			for( int j = 1; j * j <= i; ++j ){
				if( i % j == 0 ){
					b[j] ^= 1;
					if( j != i / j ) b[i / j] ^= 1;
				}
			}
			an[i] = 1, ans++;
		}
	}
	printf( "%d\n", ans );
	for( int i = 1; i <= n; ++i ) if( an[i] ) printf( "%d%c", i, " \n"[i == n] );
	return 0;
}
```

机房大佬的做法：(21ms)

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int a[N], b[N], n, ans;

int main(){
	scanf( "%d", &n );
	for( int i = 1; i <= n; ++i ) scanf( "%d", &a[i] );
	for( int i = n; i >= 1; --i ){
	    bool tmp = 0;
		for( int j = 1; 1ll * i * j <= n; ++j ) tmp ^= b[i * j];
		if( tmp != a[i] ) b[i] ^= 1, ans++;
	}
	printf( "%d\n", ans );
	for( int i = 1; i <= n; ++i ) if( b[i] ) printf( "%d%c", i, " \n"[i == n] );
	return 0;
}
```

---

## 作者：CuteForces (赞：0)

## 前言

本题翻译有误！！！翻译为“构造 $b$”，实为“$b$ 中为 $1$ 的下标”。

## 解法

根据题意模拟即可......

首先，创建一个 $b$，将 $b_i$ 全部设置为 $0$。然后，枚举 $i$，根据题意，将 $b_{i\times k}(1\le k\le \lfloor\frac{n}{i}\rfloor)$ 求和，判断其 $\bmod 2$ 是否等于 $a_i$。如果不等，则说明 $b_i$ 需要修改。然后修改 $b_i$，并将 $i$ 计入答案。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, a[200010], b[200010], ans[200010], k; 
signed main(){
	cin >> n;
	for (int i = 1; i <= n; i ++ ) cin >> a[i];
	for (int i = n; i; i -- ) {
		int x = 0;
		for (int j = i; j <= n; j += i ) x ^= b[j];
		if (x != a[i]) {
			b[i] = 1;
			ans[++ k] = i;
		}
	}
	cout << k << endl;
	for (int i = k; i; i -- ) cout << ans[i] << " ";
	return 0;
}
```

---

