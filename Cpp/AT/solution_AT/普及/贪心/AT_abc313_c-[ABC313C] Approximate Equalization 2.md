# [ABC313C] Approximate Equalization 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc313/tasks/abc313_c

整数列 $ A=(A_1,A_2,\dots,A_N) $ があります。 あなたは次の操作を好きな回数（$ 0 $ 回でもよい）行うことができます。

- $ 1\leq\ i,j\ \leq\ N $ を満たす整数 $ i,j $ を選ぶ。$ A_i $ を $ 1 $ 減らし、$ A_j $ を $ 1 $ 増やす。
 
$ A $ の最小値と最大値の差を $ 1 $ 以下にするために必要な最小の操作回数を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ \leq\ 10^9 $
- 入力は全て整数
 
### Sample Explanation 1

以下のように $ 3 $ 回の操作を行うことで、$ A $ の最小値と最大値の差を $ 1 $ 以下にすることができます。 - $ i=2,j=3 $ として操作を行う。$ A=(4,6,4,7) $ になる。 - $ i=4,j=1 $ として操作を行う。$ A=(5,6,4,6) $ になる。 - $ i=4,j=3 $ として操作を行う。$ A=(5,6,5,5) $ になる。 $ 3 $ 回未満の操作で $ A $ の最小値と最大値の差を $ 1 $ 以下にすることはできません。よって答えは $ 3 $ です。

## 样例 #1

### 输入

```
4
4 7 3 7```

### 输出

```
3```

## 样例 #2

### 输入

```
1
313```

### 输出

```
0```

## 样例 #3

### 输入

```
10
999999997 999999999 4 3 2 4 999999990 8 999999991 999999993```

### 输出

```
2499999974```

# 题解

## 作者：Dream_poetry (赞：4)

### 题目翻译：

给你一个长度为 $n$ 的序列 $a$，每次可以将 $a$ 中的任意两个元素一个加一，另一个减一。

输出使 $a$ 中的最大值与最小值相差为 $1$ 的最小次数。

### 思路：

由于每次都是一个元素加一，另一个减一，所以序列中的元素之和 $sum$ 始终不变。

所以，用 $sum$ 除以 $n$，就可以得出处理结束之后，序列内的最小值。

再用 $sum \bmod n$，就是有多少个元素处理完之后是**最大值**。

最后，我们用得到的结果序列 $b$ 的每一项与原序列 $a$ 的每一项作差，并取**绝对值**相加，最后**除以二**输出即可。

### 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
int b[300000];
int a[300000];
int main() {
    int n;
    cin >> n;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        cin>>a[i];
        sum+=a[i];
    }
    sort(a,a+n); 
    for (int i=0;i<n;i++) b[i]=sum/n;
    for (int i=0;i<sum%n;i++)
        b[n-1-i]++;
    ll ans=0;
    for (int i=0;i<n;i++) 
        ans+=abs(a[i]-b[i]);
    cout <<ans/2 << endl;
}
```


---

## 作者：_liuyi_ (赞：4)

# 题意
给定一 个 $n$ 个数的序列，你可以任选两个数，一个加一，一个减一，最少操作几次让序列最大值与最小值差为 $1$。
# 思路
令 $sum$ 为序列的和，容易发现最后变成的数一定是 $\lceil \frac{sum}{n} \rceil$ 和 $\left \lfloor \frac{sum}{n} \right \rfloor $，我们贪心地想，把序列中小于 $\left \lfloor \frac{sum}{n} \right \rfloor $ 变成 $\left \lfloor \frac{sum}{n} \right \rfloor $，大于 $\lceil \frac{sum}{n} \rceil$ 变成 $\lceil \frac{sum}{n} \rceil$，容易证明这样操作一定是最优的，最后两个取个较大值即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define mem(a, x) memset(a, x, sizeof(a)) 
#define pb push_back
#define SZ(x) ((int)(x).size())
#define debug(x) cout<<#x<<":"<<x<<endl;
#define all(a) a.begin(),a.end()
typedef long long ll;
typedef pair<int,int> PII;
typedef unsigned long long ull;
typedef double db;
typedef vector<int> VI;
const int N=2e5+10;
const int mod=1e9+7;
//const int mod=998244353;
ll n,a[N],d[N],sum,s1,s2;
ll ans1,ans2;
int main(){
	scanf("%lld",&n);
	rep(i,1,n) scanf("%lld",&a[i]),sum+=a[i];
	s1=sum/n;
	s2=s1+1;
	rep(i,1,n){
		if(a[i]==s1||a[i]==s2)continue;
		if(a[i]<s1) ans1+=abs(a[i]-s1);
		if(a[i]>s2) ans2+=abs(a[i]-s2);
	}
	printf("%lld",max(ans1,ans2));
	return 0;
}
```


---

## 作者：梦应归于何处 (赞：2)

## 题目大意

给定整数序列 $A_1,A_2,A_3,\dots ,A_N$。你可以做以下操作任意多次（可以零次）：选择 $1 \leq i,j \leq N$ 的整数对 $(i,j)$，让 $A_i$ 减少 $1$，让 $A_j$ 增加 $1$。请你求出让 $A$ 中的最大值减最小值至多为 $1$ 所需的最少操作次数。

## 暴力思路

刚开始看到这题的时候我首先就想到了模拟：每次找一个最大的减一，找一个最小的加一。然后我们就会发现这样一定会超时。就拿样例三来说吧，每次找最小，找最大，一个 $O(N)$ 的复杂度就出来了，再加上每个数字最多要调 $10^5$ 次方左右。$O(N^2)$ 是会超时的，但是也能过一些点。

## 正确思路

我们想一件事：我们能不能直接算出来最中我们要调整出来的数组呢？

答案是能的。我们可以把所有数字求和，然后除以 $N$ 就能得到了，当然，如果有余数的话就挑余数个数加一就可以了。最后就把两个数组取绝对值相减就可以了。

### 细节

不要忘了最后把两个数组都排一遍序。小的对小的，大的对大的，这样才能使总操作数最小。

最后要把答案除以二，因为一次操作室一个加一，一个减一。

### 代码

~~~cpp

#include <bits/stdc++.h>
#define TNTMAX INT_MAX
#define db double
#define ll long long
#define ex exit(0);
using namespace std;
ll a[200000];
ll b[200000];
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n;
	cin >> n;
	ll tot = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		tot += a[i];
	}
	ll s = tot / n;
	ll t = tot % n;
	for (int i = 1; i <= n; i++) {
		b[i] = s;
		if (i <= t) {
			b[i]++;
		}
	}
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += abs(a[i] - b[i]);
	}
	cout << ans / 2;
	return 0;
}

~~~

[AC记录和代码](https://atcoder.jp/contests/abc313/submissions/44278043)

[洛谷AC记录](https://www.luogu.com.cn/record/119422430)

---

## 作者：是青白呀 (赞：1)

## 题目大意

给你一个长度为 $N$ 的序列 $A_i$，你可以进行若干次操作，每次操作任选序列中的两个数，将其中的任意一个加 $1$，另一个减 $1$。问若要使得序列的极差小于等于 $1$，最小的操作次数。

## 分析

容易发现，无论进行多少次操作，该序列内所有元素的和值不变。因而若设该序列的和为 $sum$，操作结束后，序列中只会有 $\left\lfloor \frac{sum}{N} \right\rfloor$ 和 $\left\lceil \frac{sum}{N} \right\rceil$ 这两种值（若序列的平均数为整数，则最终序列的元素一定全为该平均数）。设 $ave_1=\left\lfloor \frac{sum}{N} \right\rfloor$，$ave_2=\left\lceil \frac{sum}{N} \right\rceil$。

因而，若要操作次数最少，最佳方案是把所有小于 $ave_1$ 的元素变为 $ave_1$ ，所有大于 $ave_2$ 的元素变为 $ave_2$ 。因而我们统计所有小于 $ave_1$ 的元素与 $ave_1$ 的差值和、以及所有大于 $ave_2$ 的元素与 $ave_2$ 的差值和，两者取 $\max$ 即可。

## code

```cpp
#include<bits/stdc++.h>
#define int long long 
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) x*2
#define rs(x) x*2+1
#define fir first
#define sec second
#define mp make_pair
#define by Qingbai666
using namespace std;
typedef long long ll;
const int N=2e5+5;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n;
int a[N];
int ave1,ave2;
signed main(){
	read(n);
	int sum=0;
	rep(i,1,n)
	    read(a[i]),sum+=a[i];
	if(sum%n)ave1=sum/n,ave2=ave1+1;
	else ave1=ave2=sum/n;
	sort(a+1,a+n+1);
	int sum1=0,sum2,cnt1=0;
	rep(i,1,n){
		if(a[i]<=ave1)sum1+=a[i],cnt1++;
		else break;
	}
	sum2=sum-sum1;
	int ans=max(ave1*cnt1-sum1,sum2-ave2*(n-cnt1));
	printf("%lld",ans);
	return 0;
}

---

## 作者：Frictional (赞：1)

## 题意
给你 $n$ 个数字。有一种操作可以在这 $n$ 个数字中选出两个数字 $a_i$ 和 $a_j$，并将 $a_i$ 减去 1，$a_j$ 加上 1。问最少操作多少次能使这个序列最大值与最小值的差最大为 1。
## 思路
首先，如果要让这个序列的最大值与最小值的差最大为 1。那么这个操作后的序列的值要么都相等；要么分为大数和小数两种，大数比小数大 1。

这道题可以将这 $n$ 个数求个和，称为 $sum$，然后用 $sum/n$（这是整除）。这个值就是最后经过操作后的小数，或全相等的数。而 $a\bmod{n}$ 就是操作后序列大数的个数。

之后我们将一开始输入的序列排个序。我们从大到小枚举。如果是前 $a\bmod{n}$ 个较大的数，就取与 $sum/n+1$（就是大数）的差。如果不是前 $a\bmod{n}$ 个，就取与 $sum/n$（就是小数）的差。求个和，然后因为保证有解，所以小于等于 $sum/n$ 的数就可以用较大的数减去的数补上，而我们也算了，所以要把和除以 2。
## AC code
```
#include<bits/stdc++.h>
#define fi first
#define se second
#define db double
#define U unsigned
#define P std::pair<int,int>
#define int long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define DEBUG(x) std::cerr<<#x<<'='<<x<<std::endl
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
using namespace std;
int n,s,a[200005],ans;
bool cmp(int a,int b){
	return a>b;
}
signed main(){
	cin>>n;
	FOR(i,0,n-1){
		cin>>a[i];
		s+=a[i];
	}
	sort(a,a+n,cmp);
	FOR(i,0,n-1){
		if(i<s%n) ans+=abs(s/n+1-a[i]); 
		else ans+=abs(s/n-a[i]);
	}
	cout<<ans/2;
	return 0;
}
```


---

## 作者：liangbob (赞：0)

### AT_abc313_c 题解

#### 思路分析

简单推柿子的题。

我们要如何使得这个数列的最大值与最小值的差为 $1$ 呢？显然是要尽可能的去让数列中的数平均分布。

显然，当两个数一个加 $1$，一个减 $1$ 时，两数和不变。又因为每次都是这样的操作，因此操作完毕后数列总和不变。

设数列总和为 $S$，数列中有 $n$ 个数。则尽可能平均时，情况如下：

- 后 $S \bmod n$ 个数为 $\left\lceil\\\dfrac{S}{n}\right\rceil$。
- 余下的前面的数为 $\left\lfloor\\\dfrac{S}{n}\right\rfloor$。

然后，我们求出操作次数。

设两数原为 $a_i$ 与 $b_i$，要变为 $p_i$ 与 $q_i$（$b_i \le a_i$ 且 $p_i \ge q_i$）。由题意，$a_i+b_i = p_i + q_i$，即 $p_i - a_i = b_ i - q_i$。

设 $p_i - a_i = b_ i - q_i = k$。

由于两者要变化的量 $k$ 相同，因此，只需操作 $k$ 次即可。如何计算 $k$ 呢？由 $k$ 的定义，$2k=p_i-a_i+b_i-q_i$，即 $k = \dfrac{b_i-a_i+p_i-q_i}{2}$，$k = \dfrac{\left|a_i-b_i\right|+\left|p_i-q_i\right|}{2}$。

还有，由于我们要满足条件 $b_i \le a_i$，因此要对数列排序。而 $p_i \ge q_i$ 是天然满足的，因此不用排序。

最后，由于该情况是最平均的情况，所以操作至此情况所需的步骤也最小。因此按照上述步骤实现即可。

#### 代码

```cpp
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long
#define IL inline
using namespace std;
const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;

IL int read()
{
    int x = 0,f = 1;
    char c = getchar();
    while(c <'0'|| c >'9'){if(c == '-') f = -1;c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = getchar();
    return x * f;
}

void write(int x)
{
    if(x < 0) putchar('-'),x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

int a[N], b[N];

signed main()
{
	int n;
	cin >> n;
	int s = 0; //和 
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i];
		s += a[i];
	}	
	sort(a + 1, a + n + 1); 
	for(int i = 1;i <= n - s % n;i++) //余下的前面的数为 floor(s/n) 
	{
		b[i] = s / n; 
	}
	for(int i = 1;i <= s % n;i++) //后 s % n 个数为 ceil(s/n)（即floor(s / n) + 1） 
	{
		b[n - i + 1] = s / n + 1;
	}
	//依照公式计算操作次数 
	int ans = 0;
	for(int i = 1;i <= n;i++)
	{
		ans += abs(b[i] - a[i]);
	}
	cout << ans / 2 << endl;
    return 0;
}
```

---

## 作者：I_am_kunzi (赞：0)

# AT_abc313_c 题解

### 题目翻译

$ n $ 个数，第 $ i $ 个数为 $ a_i$，求最小的操作次数使得这些数间最大值与最小值差最大为 $ 1$？

一次操作指将一个任务从 $ a $ 分配到 $ b$，其中 $ 1 \le a , b \le n$，此操作会耗费 $ 1 $ 秒。

### 题目思路

注：我和同学打完 abc313_c 后发现了 CF609C，一样的思路和代码，说明多刷题可能遇到原题。

容易得出，在整个操作的过程中，数的总和不会发生变化，发生变化的只有若干个数的值。在此过程中，我们为了让每个数的操作次数尽量少，可以让最终交换完时，本来数较小的位置最终数也较少；本来数较大的位置最终数也较大，例如原来各个数分别为 ``` 4 7 4 7```，交换完变成 ``` 5 6 5 6```。我们可以对原数组 $ a $ 排序，并计算出对应的交换后的数组 $ b$，又因为每交换一次会改变两个位置的值，所以计算出 $ \displaystyle \frac {\sum_{i = 1} ^ n \left | a_i - b_i \right |} 2 $ 即可。

### 题目代码

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
long long a[200005]; // 原数组
long long b[200005]; // 交换后的数组
signed main()
{
	int n;
	cin >> n;
	long long sum = 0;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> a[i];
		sum += a[i];
	}
	sort(a + 1 , a + n + 1); // 排序，方便后续操作
	for(int i = 1 ; i <= n ; i++)
	{
		b[i] += sum / n; // 前面的位置小，所以都是 sum / n（但是后面的位置已经被修改，所以要用 += 而不是 =）
		if(i - 1 < sum % n) // i - 1 是因为 sum % n 的值下限为 0 而不是 1
		{
			b[n - i + 1]++; // 对应的位置增加 1
		}
	}
	long long cha = 0;
	for(int i = 1 ; i <= n ; i++)
	{
		cha += abs(a[i] - b[i]); // cha 的值就应该是需要变动的值的总和
	}
	cout << cha / 2 << endl; // 因为操作一次会改变两个位置，因此此处输出 cha / 2 即可
    return 0;
}
```


---

## 作者：Crazyouth (赞：0)

**翻译**

有一个 $n$ 个数的数列 $a$，请你进行以下操作若干次：

- 选择 $i,j(i\ne j)$，$a_i\leftarrow a_i+1,a_j\leftarrow a_j-1$。

使 $\max(a_i)-\min(a_i)\le1$，问最少需要多少次操作。

**分析**

注意到 $\sum a_i$ 始终不变，进而得到最终的数一定都为 $\lfloor \frac{\sum a_i}{n} \rfloor$ 或 $\lceil \frac{\sum a_i}{n}\rceil$，所以处理出这两个值，小于 $\lfloor \frac{\sum a_i}{n} \rfloor$ 的变成它，否则变成 $\lceil \frac{\sum a_i}{n}\rceil$，再对二者需要的操作数取 $\max$ 就可以贪心地求出答案。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[int(2e5+10)];
int main()
{
	long long n,sum=0,f1,f2,ans1=0,ans2=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];//计算和
	}
	f1=sum/n;//下去整
	f2=ceil(double((double)sum/(double)n));//上取整
	for(int i=1;i<=n;i++)
	{
		if(a[i]<=f1) ans1+=f1-a[i];//贪心过程
		else ans2+=a[i]-f2;
	}
	cout<<max(ans1,ans2);
	return 0;
} 

---

