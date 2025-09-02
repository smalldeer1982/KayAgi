# [AGC044A] Pay to Win

## 题目描述

# [AGC044A] Pay to Win


你有一个数字$0$ ，你希望得到数字$N$。

你可以通过以下操作更改数字，需要支付一定数量的硬币：

- 将当前数乘$2$，需要$A$硬币。
- 将当前数乘$3$，需要$B$硬币。
- 将当前数乘$5$，需要$C$硬币。
- 将当前数加$1$或减$1$，需要$D$硬币。

你可以按任意顺序和任意次数执行这些操作。

最少需要多少硬币才能得到$N$？

你需要解决$T$组测试用例。

## 说明/提示

### 约束

- $ 1\ \le\ T\ \le\ 10 $
- $ 1\ \le\ N\ \le\ 10^{18} $
- $ 1\ \le\ A,\ B,\ C,\ D\ \le\ 10^9 $
- $ N,\ A,\ B,\ C,\ D $ 都是整数。

### Sample Explanation 1

对于第一个测试用例，达到最低成本$20$的一系列操作是：

- 初始 $x = 0$.
- 用$8$个硬币使其加$1(x = 1)$
- 用$1$个硬币使其乘$2(x = 2)$
- 用$1$个硬币使其乘$2(x = 4)$
- 用$2$个硬币使其乘$3(x = 12)$
- 用$8$个硬币使其减$1(x = 11)$

对于第二个测试用例，达到最低成本$19$的一系列操作是：

- 初始 $x = 0$.
- 用$8$个硬币使其加$1(x = 1)$
- 用$1$个硬币使其乘$2(x = 2)$
- 用$2$个硬币使其乘$5(x = 10)$
- 用$8$个硬币使其减$1(x = 11)$

## 样例 #1

### 输入

```
5
11 1 2 4 8
11 1 2 2 8
32 10 8 5 4
29384293847243 454353412 332423423 934923490 1
900000000000000000 332423423 454353412 934923490 987654321```

### 输出

```
20
19
26
3821859835
23441258666```

# 题解

## 作者：suzhikz (赞：5)

正着做和反着做本质相同，但是反着做范围更小。

还有比较重要的就是发现先加后除一定比先除后加劣。

这样就可以节省很多不必要的点。

然后就是乘 $d$ 的时候会爆 long long ，注意点即可。

还有经典的 map 记忆化。


```cpp
if(m[x])return m[x];
	if(x==0)return 0;
	if(x==1)return d;
	ll ans=min((__int128)1e18,(__int128)x*d);
	ll l,r;
	{
		l=x/2*2;
		ans=min(ans,(x-l)*d+a+dfs(l/2));
		r=(x+1)/2*2;
		ans=min(ans,(r-x)*d+a+dfs(r/2));
	}
//	cout<<x<<' '<<ans<<endl;
	{
		l=x/3*3;
		ans=min(ans,(x-l)*d+b+dfs(l/3));
		r=(x+2)/3*3;
		ans=min(ans,(r-x)*d+b+dfs(r/3));
	}
//	cout<<x<<' '<<ans<<endl;
	{
		l=x/5*5;
		ans=min(ans,(x-l)*d+c+dfs(l/5));
		r=(x+4)/5*5;
		ans=min(ans,(r-x)*d+c+dfs(r/5));
	}
```

---

## 作者：IkunTeddy (赞：2)

# 题目分析
这个题乍一看好像没什么思路，那就分析一下直接最暴力的 `dfs` 能不能行，对于每一次选择，都可以选择 $4$ 种。

第四种情况的加减 $1$ 比较简单，所用花费就是 $d\times N$。

第一种情况除以一次 $2$，此时 $N \bmod 2 =0$ 所以就需要用加减 $1$ 来达到最近的 $2$ 的倍数。此时的花费就是 $(N \bmod2)\times d+ \lfloor  N\div2\rfloor\times a$ 或 $(N\bmod 2)\times d+(N+N\bmod2)\div2\times a$。

第二种和第三种的情况和第一种情况类似，只要满足 $N \bmod3=0$ 或 $N \bmod5=0$ 就行。

再来分析时间复杂度是否能够接受，是否需要进一步优化。时间复杂度封顶 $O(\log_{2}{N}\times \log_{3}{N}\times \log_{5}{N})<O(60000)$ 很明显是可以接受的。但是每层中可以有多层递归，所以加一个记忆化就直接跑到飞起。

# Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define min(a,b) (a<b)?a:b
using namespace std;
map<int,int>mp;
int a,b,c,d;
int dfs(int n){
	if(mp.count(n))return mp[n];
	int l1=(n/2)*2,r1=((n+1)/2)*2;
	int l2=(n/3)*3,r2=((n+2)/3)*3;
	int l3=(n/5)*5,r3=((n+4)/5)*5;
	int ans=(n<(int)1e18/d)?n*d:(int)1e18;
	ans=min(ans,(n-l1)*d+dfs(l1/2)+a);
	ans=min(ans,(r1-n)*d+dfs(r1/2)+a);
	ans=min(ans,(n-l2)*d+dfs(l2/3)+b);
	ans=min(ans,(r2-n)*d+dfs(r2/3)+b);
	ans=min(ans,(n-l3)*d+dfs(l3/5)+c);
	ans=min(ans,(r3-n)*d+dfs(r3/5)+c);
	return mp[n]=ans;
}
signed main(){
	int T;
	scanf("%lld",&T);
	while(T--){
		int n;
		scanf("%lld%lld%lld%lld%lld",&n,&a,&b,&c,&d);
		mp.clear();
		mp[0]=0;
		mp[1]=d;
		printf("%lld\n",dfs(n));
	}

	return 0;
}


```


---

## 作者：Rainbow_SYX (赞：0)

## 题意
太水了，不用讲了吧。

## 思路
考虑使用 DFS 来做，容易从题目中得出，对于每一次选择，都可以选择 $4$ 种方法。

先说最简单的第四种，直接从 $0$ 一直加到 $N$，需花费 $d \times N$，这个花费基本是最大的，$ans$ 的初始值设为它。

接着是第一种，如果 $n$ 是 $2$ 的倍数，那么花费为 $ans = \min(ans,\operatorname{dfs}(n \div 2)+a)$，如果不是，我们需要用加减一操作把 $n$ 变成距离它上下的两个 $2$ 的倍数，花费为 $ans=\min(ans,\min(\operatorname{dfs}((n-n \bmod 2) \div 2),\operatorname{dfs}((n+2-n \bmod 2) \div 2)+a+d)$。

第二三种比较像，以第三种为例，如果 $n$ 是 $5$ 的倍数，那么花费为 $ans=\min(ans,\operatorname{dfs}(n \div 5)+c)$，如果不是，花费为 $ans=\min(ans,\min(\operatorname{dfs}((n-n \bmod 5) \div 5)+(n \bmod 5) \times d),\operatorname{dfs}(((n+5-n \bmod 5) \div 5)+(5-n \bmod 5) \times d)+c)$。

还有，注意开成 ```unsigned long long```,并使用 ```map``` 记忆化搜索。
## 代码

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
#define ans2z ans=min(ans,dfs(n/2)+a)
#define ans3z ans=min(ans,dfs(n/3)+b)
#define ans5z ans=min(ans,dfs(n/5)+c)
//getchar_unlocked() 更快一点 
using namespace std;
map<int,int> mp;
int n,a,b,c,d;
inline int in()
{
    int k=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
    return k*f;
}
inline void out(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x<10) putchar(x+'0');
    else out(x/10),putchar(x%10+'0');
}
int dfs(int n)
{
	if(mp.count(n)) return mp[n];
	int n2x,n2s,n3x,n3s,n5x,n5s;int ans=n*d;
	n2x=(n-n%2)/2;
	n2s=(n+2-n%2)/2;
	n3x=(n-n%3)/3;
	n3s=(n+3-n%3)/3;
	n5x=(n-n%5)/5;
	n5s=(n+5-n%5)/5;
	if(n%2==0) ans2z;
	else ans=min(ans,min(dfs(n2x),dfs(n2s))+a+d);
	if(n%3==0) ans3z;
	else ans=min(ans,min(dfs(n3x)+(n%3)*d,dfs(n3s)+(3-n%3)*d)+b);
	if(n%5==0) ans5z;
	else ans=min(ans,min(dfs(n5x)+(n%5)*d,dfs(n5s)+(5-n%5)*d)+c);
	mp[n]=ans;
	return ans;
}
signed main()
{
	int T=in();
	while(T--)
	{
		n=in(),a=in(),b=in(),c=in(),d=in();
		mp.clear();
		mp[0]=0;
		mp[1]=d;
		out(dfs(n));
		printf("\n");
	}
	return 0;
}
```

---

## 作者：LiSA_OLiVE (赞：0)

跟其它题解一样，对于这种进行一系列操作最终得到某个值的题目，很多一部分都是用的记忆化搜索 DFS。不过我尽量详细说下具体操作，以便可能有初学者看到的话能看得更明白。

首先，由题意，从 $0$ 开始，只要想有效进行乘除操作，必须先加到 $1$。所以递归出口就被我们赋值为 $f(0)=0$ 和 $f(1)=d$。随后，我们可以从 $n$ 开始从大到小记忆化 DFS。**这里注意，由于 $10^{18}$ 的数据量太大，记忆化数组需要使用 map 离散化**。在 DFS 中，可以有以下思路：

1. 递归出口和记忆化：当前 $x$ 如果已经记录过答案，那么直接返回这个答案。
2. 如果没有记录过答案，那么就尝试使用四种操作计算最优答案。最坏的情况就是从 $0$ 每次加一到 $x$，所以 $ans$ 最大值也不会超过这种方法的价值 $x \times d$。$ans$ 初值设置为它。
3. 依次尝试三种乘法操作。以乘 $3$ 为例，**如果 $x$ 是 $3$ 的倍数**，那么直接 $ans=\min(ans,\operatorname{dfs}(x \div 3)+b)$。**如果不是**，那么我们用加减一操作把 $x$ 变成距离它上下的两个 $3$ 的倍数即 $x-x \bmod 3$ 和 $x+3-x \bmod 3$，然后再当成倍数来 DFS。别忘了给 DFS 的答案加上加减一带来的价值。即：$ans=\min(ans,\min(\operatorname{dfs}((x-x \bmod 3) \div 3)+(x \bmod 3) \times d,\operatorname{dfs}((x+3-x \bmod 3) \div 3)+(3-x \bmod 3) \times d)+b)$。
4. 其它乘操作以此类推。最后取得 $ans$ 最小值，并且赋值给记忆化数组。

输出答案，于是这道题就结束了。以下是正确代码：
```cpp
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int N=1e18;
map <int,int> mp;
int n,a,b,c,d;
int dfs(int x){
	if(mp.count(x)) return mp[x];
	int ans=x*d;
	
	if(x%2) ans=min(ans,min(dfs((x-x%2)/2),dfs((x+2-x%2)/2))+a+d);
	else ans=min(ans,dfs(x/2)+a);
	
	if(x%3) ans=min(ans,min(dfs((x-x%3)/3)+(x%3)*d,dfs((x+3-x%3)/3)+(3-x%3)*d)+b);
	else ans=min(ans,dfs(x/3)+b);
	
	if(x%5) ans=min(ans,min(dfs((x-x%5)/5)+(x%5)*d,dfs((x+5-x%5)/5)+(5-x%5)*d)+c);
	else ans=min(ans,dfs(x/5)+c);
	
	mp[x]=ans;
	return ans;
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>a>>b>>c>>d;
		mp.clear();
		mp[0]=0;
		mp[1]=d;
		cout<<dfs(n)<<"\n";
	}
	return 0;
}
```

---

## 作者：xukehg (赞：0)

看这庞大的数据规模和神秘的要求，只有 $1$ 种可能：搜索！

很明显，如果按题意模拟从下往上乘，会有极其多的情况，情况也会极大，所以我们考虑从上往下搜，把乘运算改为除运算，并加上记忆化搜索。但直接搜时间复杂度依旧感人。

我们思考加减 $1$ 的意义，实际上，在绝大部分情况中除操作比加减操作更优，所以实际上加减是为了进行除操作。因此我们只要考虑加或减使得被某个数整除的情况，而不是漫无目的的乱加减。另外，直接通过减 $1$ 的操作变成 $0$ 的情况也要考虑，视为最大值。

理清楚方法后就很好做了：在 $7$ 种情况中取最小值，情况不会很多，不过要开 `int128` 。

代码：
```cpp
#include <bits/stdc++.h>
#define int __int128
using namespace std;

inline int read() {
	__int128 x=0,f=1;
	char ch=getchar();
	while (ch<'0' || ch>'9') {
		if (ch=='-')f=-1;
		ch=getchar();
	}
	while ('0'<=ch && ch<='9') {
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
inline void write(__int128 x) {
	static __int128 sta[35];
	int top = 0;
	do {
		sta[top++] = x % 10,x /= 10;
	} while (x);
	while (top) putchar(sta[--top] + 48);
}
int a,b,c,d,n;
map<int,int> dp;
int mymin(int a,int b){
	if (a < b) return a;
	return b;
}
void writen(int k){
	write(k);
	printf(" ");
}
#define min mymin
int dfs(int num){
	if (dp.count(num) != 0) return dp[num];
	int ans = num * d,ans1 = dp[num],ans2 = dp[num],ans3 = dp[num],ans4 = dp[num],ans5 = dp[num],ans6 = dp[num];
	int aa = num % 2,bb = num % 3,cc = num % 5,aaa = 2 - num % 2,bbb = 3 - num % 3,ccc = 5 - num % 5;
	ans1 = min((num - aa) / 2 * d + aa * d + a,dfs((num - aa) / 2) + d * aa + a);
	ans = min(ans,ans1);
	ans2 = min((num + aaa) / 2 * d + aaa * d + a,dfs((num + aaa) / 2) + d * aaa + a);
	ans = min(ans,ans2);
	ans3 = min((num - bb) / 3 * d + bb * d + b,dfs((num - bb) / 3) + d * bb + b);
	ans = min(ans,ans3);
	ans4 = min((num + bbb) / 3 * d + bbb * d + b,dfs((num + bbb) / 3) + d * bbb + b);
	ans = min(ans,ans4);
	ans5 = min((num - cc) / 5 * d + cc * d + c,dfs((num - cc) / 5) + d * cc + c);
	ans = min(ans,ans5);
	ans6 = min((num + ccc) / 5 * d + ccc * d + c,dfs((num + ccc) / 5) + d * ccc + c);
	ans = min(ans,ans6);
	//writen(num),writen(ans1),writen(ans2),writen(ans3),writen(ans4),writen(ans5),writen(ans6),printf("\n");
	return dp[num] = ans;
}
signed main(){
	int t;
	t = read();
	while (t--){
		n = read(),a = read(),b = read(),c = read(),d = read();
		dp.clear();
		dp[0] = 0;
		dp[1] = d;
		write(dfs(n));
		printf("\n");
	}
}
/*
3
11 1 2 4 8
11 1 2 2 8
32 10 8 5 4
*/
```

---

## 作者：墨笙_Mooos (赞：0)

注：本人的思路与官方题解思路相同，可以当作是官方题解的翻译与详细解释。

----

发现从零开始计算容易超过 $N$，考虑反过来计算，也就是初始为 $N$，要将其变成 $0$，操作变为：

* $2 \mid x$ 时，可以花费 $A$ 将 $x$ 除以 $2$
* $3 \mid x$ 时，可以花费 $B$ 将 $x$ 除以 $3$
* $5 \mid x$ 时，可以花费 $C$ 将 $x$ 除以 $5$
* 可以花费 $D$ 将 $x$ 变为 $x + 1$ 或者 $x - 1$

先考虑最朴素的一组解，进行 $N$ 次 $-1$ 的操作。答案为 $N \times D$。

然后再考虑应用一次除以 $k$ 的操作（$k \in \{ 2, 3, 5\}$），将 $N$ 先变为另一个较小数 $t$ 再变为 $0$ 的操作过程，可以得到：

$$\left\{ N, N-1, \cdots, tk, t, \cdots\right\}$$

可以看到，我们省略了从 $tk$ 到 $t$ 的 $-1$ 操作，用一个除以 $k$ 的操作代替之。

因为除以 $k$ 的操作固定（无该操作的答案已经计算），于是我们思考，如何才能省略更多的 $-1$ 操作呢？

无疑，我们需要将除以 $k$ 的操作尽量提早，即令 $t = \left\lfloor\dfrac{N}{k}\right\rfloor$。具体的，我们的操作过程应该是这样的：

$$\left\{N, N-1, \cdots, k\left\lfloor\dfrac{N}{k}\right\rfloor, \left\lfloor\dfrac{N}{k}\right\rfloor, \cdots\right\}$$

这时候，我们把 $\left\lfloor\dfrac{N}{k}\right\rfloor$ 视为新的 $N$，以同样的方式再次解决这个问题。

当然，还有一种情况，就是 $N$ 先进行 $+1$ 操作，再除以 $k$。这时候我们取到的 $t = \left\lceil\dfrac{N}{k}\right\rceil$，操作过程应该是：

$$\left\{N, N + 1, \cdots, k\left\lceil\dfrac{N}{k}\right\rceil, \left\lceil\dfrac{N}{k}\right\rceil, \cdots\right\}$$

这时我们将 $\left\lceil\dfrac{N}{k}\right\rceil$ 视为新的 $N$，以同样的方式解决。

---

综上，令 $f(N)$ 表示将 $N$ 变为 $0$ 的最小代价，$Cost_k$ 表示除以 $k$ 的代价，那么 $f(N)$ 的值即为如下几种情况的最小值：

* 只有 $-1$ 操作，代价为 $N \times D$。

* 进行 $-1$ 的操作，直到 $k\left\lfloor\dfrac{N}{k}\right\rfloor$，再进行除以 $k$ 的操作，$N$ 变为 $\left\lfloor\dfrac{N}{k}\right\rfloor$，代价为 $D \times (N \bmod k) + Cost_k + f(\left\lfloor\dfrac{N}{k}\right\rfloor)$。

* 进行 $+1$ 的操作，直到 $k\left\lceil\dfrac{N}{k}\right\rceil$，再进行除以 $k$ 的操作，$N$ 变为 $\left\lceil\dfrac{N}{k}\right\rceil$，代价为 $D \times (k - N \bmod k) + Cost_k + f(\left\lceil\dfrac{N}{k}\right\rceil)$。

易知边界为 $f(0) = 0, f(1) = D$。

---

考虑时间复杂度。我们考虑计算被调用到的 $f(N)$。由于每次调用到的下一级为 $\left\lfloor\dfrac{N}{k}\right\rfloor$ 和  $\left\lceil\dfrac{N}{k}\right\rceil$，所以所有被调用的状态都可以表示为 $\left\lfloor\dfrac{N}{2^a3^b5^c}\right\rfloor$ 和 $\left\lceil\dfrac{N}{2^a3^b5^c}\right\rceil$。

易知 $0 \leq a \leq \left\lfloor\log_2{N}\right\rfloor = 59$，$0 \leq b \leq \left\lfloor\log_3{N}\right\rfloor = 37$，$0 \leq c \leq \left\lfloor\log_5{N}\right\rfloor = 25$。

因此，被调用到的 $f(N)$ 的数量上限为 $60 \times 38 \times 26 = 59280$，考虑到离散化，$59280 \times \log_2{59280} \approx 939899 < 1\ 000\ 000$，没有问题。

---

在代码实现上，要注意：
* 值域较大，可以使用 ```map``` 或者 ```__gnu_pbds::tree``` 进行离散化。
* $10^{18} \times 10^9$ 是超过 ```unsigned long long``` 的存储范围的，所以可以使用 ```__int128_t```，最后答案会很小（极限情况下，最大答案应该是 $10^9 \times \log{10^{18}}$ 左右的），所以可以转 ```unsigned long long``` 输出。（也可以通过其他方法规避）

> Talk is cheap, show me the code.

```cpp
typedef long long ll;
typedef __int128_t lll;
typedef unsigned long long ull;
using __gnu_pbds::tree;
ll T, n, D, Cost[10];
tree<ll, lll> Res;

template<typename T> inline void CkMin (T & x, const T & y) { x = min (x, y); }

inline lll DFS (ll Now)
{
	if (Now == 0) return 0;
	if (Now == 1) return D;
	auto Node = Res.find (Now);
	if (Node != Res.end ()) return Node->second;
	lll Ans = (lll) Now * D;
	for (ll T : { 2, 3, 5 } ) if (Now % T != 0)
		CkMin (Ans, Cost[T] + D * (T - Now % T) + DFS (Now / T + 1)),
		CkMin (Ans, Cost[T] + D * (Now % T) + DFS (Now / T));
	else CkMin (Ans, Cost[T] + DFS (Now / T));
	return Res[Now] = Ans;
}

int main ()
{
	std::cin.tie (nullptr), std::ios::sync_with_stdio (false);
	cin >> T; while (T--)
	{
		cin >> n >> Cost[2] >> Cost[3] >> Cost[5] >> D, Res.clear ();
		cout << (ull) DFS (n) << endl;
	}
	return 0;
}
```

---

