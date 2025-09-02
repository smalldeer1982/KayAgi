# Vlad and a Sum of Sum of Digits

## 题目描述

Please note that the time limit for this problem is only 0.5 seconds per test.

Vladislav wrote the integers from $ 1 $ to $ n $ , inclusive, on the board. Then he replaced each integer with the sum of its digits.

What is the sum of the numbers on the board now?

For example, if $ n=12 $ then initially the numbers on the board are: $ $$$1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12. $ $  Then after the replacement, the numbers become:  $ $ 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3. $ $  The sum of these numbers is  $ 1+2+3+4+5+6+7+8+9+1+2+3=51 $ . Thus, for  $ n=12 $  the answer is  $ 51$$$.

## 样例 #1

### 输入

```
7
12
1
2
3
1434
2024
200000```

### 输出

```
51
1
3
6
18465
28170
4600002```

# 题解

## 作者：无名之雾 (赞：4)

# Vlad and a Sum of Sum of Digits 题解

~~赛时没有想到前缀和于是写了数位 dp。~~

## 题意

给定一个 $n$ 求 $1$ 到 $n$ 的所有数字的各个数位之和。

看到限制时就知道这题显然不可以用暴力去做。于是我便有了以下思考。

## The first method

而后我就想到了之前学的数位 dp。

$f_i$ 表示在有 $i$ 位数字的情况下，每种数字的个数。对于每一种数，它的数量都是相等的，所以便有了以下递推公式 $f_i=f_{i-1}\times 10+ 10^{i-1}$

而接下来，在处理中，我们可以把一个数字一位一位的分拆开求和即可（~~因为此题仅要求求数字和所以前导零去不去都可以呢。~~）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a,b,hyf[20],f[20],cnta[20],cntb[20];
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
void solve(int x,int *cnt){
    int num[20]={0};
    int len=0;
    while(x){
        num[++len]=x%10;
        x=x/10;
    } 
    for(int i=len;i>=1;i--){
        for(int j=0;j<=9;j++)cnt[j]+=f[i-1]*num[i];
        for(int j=0;j<num[i];j++)cnt[j]+=hyf[i-1];
        int num2=0;
        for(int j=i-1;j>=1;j--)num2=num2*10+num[j];
        cnt[num[i]]+=num2+1;
        cnt[0]-=hyf[i-1];
    } 
}
int main(){
	int t;
	cin>>t;
	while(t--){
		memset(f,0,sizeof(f));
		memset(hyf,0,sizeof(hyf));
		memset(cnta,0,sizeof(cnta));
		memset(cntb,0,sizeof(cntb));
		a=1,cin>>b;
    	hyf[0]=1;
    	for(int i=1;i<=15;i++){
        	f[i]=f[i-1]*10+hyf[i-1];
        	hyf[i]=10*hyf[i-1];
    	}
    	solve(a-1,cnta);
    	solve(b,cntb);
    	int hyfakioi=0;
    	for(int i=0;i<=9;i++)hyfakioi+=(cntb[i]-cnta[i])*i;
    	cout<<hyfakioi<<"\n";
	}
	return 0;
}
```
## The second method

赛后我仔细地思考了一下（~~这是 div.4 不至于这么离谱吧~~）。于是我就想到了前缀和的办法。

我们从 $1$ 到 $n$ 的最大值统计数位和的前缀和，再每次 $O(1)$ 查询即可。 

```cpp
#include <bits/stdc++.h> 
using namespace std;
const int N = 2e5+5;
int f[200005]; 
int dig(int x){
	int cnt = 0;
	while(x/10>0){
		cnt+=x%10;
		x/=10;
	}
	if(x)cnt+=x;
	return cnt;
}
int main(){
	for(int i=1;i<N;i++)f[i]=f[i-1]+dig(i);
	int t;
	cin>>t
	while(t--){
		int n;
		cin>>n;
		cout<<f[n]<<"\n";
	}
	return 0;
}
```

---

## 作者：__Dist__ (赞：2)

吃了 $1$ 发罚时/oh

暴力复杂度 $O(tn)$ 还有一个不小的常数，500ms 跑不动。

超时之后打算打个表，结果代码长度超了。突然发现打表的范围很小，可以预处理。

因为 $n\le 2\times 10^5$，所以我们可以预处理出 $1\sim 2\times 10 ^ 5$ 的所有数的数位和，然后用一个前缀和记录前 $i$ 个数的数位和的和，每次输出 $qzh_n$ 即可。

代码：

```cpp
#include <bits/stdc++.h>
#define gt getchar
#define pt putchar
#define ll long long

using namespace std;

const int MAXN = 2e5 + 5;

ll read() {
	ll x = 0, f = 1;char ch = gt();
	while (ch < '0' || ch > '9') {if (ch == '-') f = -1;ch = gt();}
	while (ch >= '0' && ch <= '9') {x *= 10;x += ch - '0';ch = gt();}
	return x * f;
}

ll T;
ll n;
ll qzh[MAXN];
ll ans[MAXN];

ll get_sum(ll x) {
	ll res = 0;
	while(x) {
		res += x % 10;
		x /= 10;
	}
	return res;
}

void solve() {
	n = read();
	cout << qzh[n] << '\n';
}

int main() {
//	ios::sync_with_stdio(false);
//	cout.tie(nullptr);
//	freopen("1.out", "w", stdout);
	for (int i = 1; i <= MAXN - 5; i++) {
		ans[i] = get_sum(i);
		qzh[i] = qzh[i - 1] + ans[i];
	}
	T = read();
	while(T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：dthythxth_Huge_Brain (赞：1)

## 前言

赛时用的预处理，赛后突然想到了思路 2。

## 思路 1

首先可以发现题目要求的就是 $1\sim n$ 的数字的前缀和。

我们可以直接预处理 $1\sim2\times10^5$ 的前缀和，每次 $O(1)$ 查询即可。

## 参考代码 1

```
#include<bits/stdc++.h>
int t,n,s[200004];
void init(){
	for(int i=1,j;i<=200000;i++){
		j=i;
		while(j)s[i]+=j%10,j/=10;
		s[i]+=s[i-1];
	}
}
signed main(){
	scanf("%d",&t),init();
	while(t--){
		scanf("%d",&n),printf("%d\n",s[n]);
	}
	return 0;
}
```

## 思路 2

数位 dp，$f_i$ 表示在 $i$ 位数下各个数的数量，即可列出转移方程。

$$f_i=f_{i-1}\times10+10^{i-1}$$

然后数位 dp 板子，最后统计总和，输出即可。

## 参考代码 2

```
//暂时的最优解
#include<bits/stdc++.h>
#define int long long
namespace FAST_IO{
	using std::sort;
	const int LEN=1<<18;
	char BUF[LEN],PUF[LEN];
	int Pin=LEN,Pout;
	inline void flushin(){memcpy(BUF,BUF+Pin,LEN-Pin),fread(BUF+LEN-Pin,1,Pin,stdin),Pin=0;return;}
	inline void flushout(){fwrite(PUF,1,Pout,stdout),Pout=0;return;}
	inline char Getc(){return (Pin==LEN?(fread(BUF,1,LEN,stdin),Pin=0):0),BUF[Pin++];}
	inline char Get(){return BUF[Pin++];}
	inline void Putc(char x){if(Pout==LEN)flushout(),Pout=0;PUF[Pout++]=x;}
	inline void Put(char x){PUF[Pout++]=x;}
	template<typename tp=int>inline void swap(tp x,tp y){if(x!=y)x^=y^=x^=y;}
	template<typename tp=int>inline tp max(tp a,tp b){return a>b?a:b;}
	template<typename tp=int>inline tp abs(tp a){return a>0?a:-a;}
	template<typename tp=int>inline tp qpow(tp a,tp b,tp mod){if(b==0)return 1;int tmp=qpow(a,b>>1,mod);if(b&1)return tmp*a%mod*tmp%mod;return tmp*tmp%mod;}
	template<typename tp=int>inline tp min(tp a,tp b){return a>b?b:a;}
	template<typename tp=int>inline tp gcd(tp a,tp b){while(b^=a^=b^=a%=b);return a;}
	template<typename tp=int>inline tp read(){(Pin+32>=LEN)?flushin():void();tp res=0;char f=1,ch=' ';for(;ch<'0'||ch>'9';ch=Get())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=Get())res=(res<<3)+(res<<1)+ch-48;return res*f;}
	template<typename tp>inline void wt(tp a){if(a>9)wt(a/10);Put(a%10+'0');return;}
	template<typename tp>inline void write(tp a,char b=' '){static int stk[20],top;(Pout+32>=LEN)?flushout():void();if(a<0)Put('-'),a=-a;else if(a==0)Put('0');for(top=0;a;a/=10)stk[++top]=a%10;for(;top;--top)Put(stk[top]^48);Put(b);return;}
}
using namespace FAST_IO;
int t=1,n,b,pos[10],f[10],sum[10],ans;
void Solve(int x,int*Ans){
	int a[20]={0},siz=0;
	while(x)a[++siz]=x%10,x=x/10;
	for(int i=siz;i;i--){
		for(int j=0;j<=9;j++)Ans[j]+=f[i-1]*a[i];
		for(int j=0;j<a[i];j++)Ans[j]+=pos[i-1];
		b=0;
		for(int j=i-1;j;j--)b=b*10+a[j];
		Ans[a[i]]+=b+1,Ans[0]-=pos[i-1];
	}
}
void solve(){
	//多测不清空，爆零两行泪！
	n=read(),memset(pos,0,sizeof pos),memset(f,0,sizeof f),memset(sum,0,sizeof sum),pos[0]=1,ans=0;
	for(int i=1;i<=6;i++)f[i]=f[i-1]*10+pos[i-1],pos[i]=10*pos[i-1];
	Solve(n,sum);
	for(int i=0;i<=9;i++)ans+=sum[i]*i;
	write(ans,'\n');
}
signed main(){
	t=read();
	for(;t--;)solve();
	flushout();
	return 0;
}
```

---

## 作者：HashHacker_Peas (赞：1)

## 解题思路
注意到 $1\leq n\leq2\times10^5$ 与 $0.5\text{s}$ 的时间限制，显然 $O(tn\log n)$ 的时间复杂度无法胜任此题。我们不妨令 $s_x=\sum_{i=1}^{x}\text{Digit}(i)$（此处 $\text{Digit}(i)$ 表示 $i$ 在十进制下的数位和），则 $\sum_{i=l}^{r}\text{Digit}(i)=s_r-s_{l-1}$，注意到这一部分就是前缀和，因此可以 $O(n\log n)$ 进行预处理，$O(t)$ 查询即可。
## 代码部分
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int t,n,s[maxn];
int digit(int n){
   int res=0;
   while(n){
       res+=n%10;
       n/=10;
   }
   return res; 
}
void init(){
    for(int i=1;i<maxn;i++)
        s[i]=s[i-1]+digit(i);
}
int main(){
    init();
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        printf("%d\n",s[n]);
    }
    return 0;
}
```

---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1926C)

## 思路

考虑到这题 $500\mathrm{ms}$ 的时间限制，如果暴力做时间复杂度为 $\mathcal{O}(tn)$ 且带有一个巨大的常数，肯定过不了，所以我们考虑预处理出前缀和，然后 $\mathcal{O}(1)$ 查询，肯定能通过此题。

从 $1$ 到 $n$ 最大值 $2\times 10^5$ 循环统计每个数每位数字之和，并用前缀和存储。问前 $n$ 个数每位之和的时候直接输出下标为 $n$ 的前缀数组即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
int n;
ll a[N],p[N];
inline void solve(){
    cin>>n;
    cout<<p[n]<<"\n";
    return ;
}
int main(){
    int T;
    cin>>T;
    for(int i=1;i<=(int)2e5;++i){
        int t=i;
        while(t){
            a[i]+=t%10;
            t/=10;
        }
        p[i]=p[i-1]+a[i];
    }
    while(T--)solve();
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/147966583)

---

## 作者：_smart_stupid_ (赞：0)

## [题目](https://www.luogu.com.cn/problem/CF1926C)

我想用正经一点的做法通过，但是它太难了。

我们注意到 $n$ 并不大，而且 $n+1$ 个数字的和可以用 $n$ 个数字的和变换得到。我们可以预处理出这些数字的和，然后要用的时候直接输出即可。

对于 $n$ 个数字的和，我们可以在 $n-1$ 个数字的和的基础上加上第 $n$ 个数字的位数和，就得到了第 $n$ 个答案。

时间复杂度：$O(n\log_{10}(n))$

一共有 $2\cdot10^5$ 种答案，可以通过。

## AC Code：

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int t, n, n1;
long long ans;
int list[200100];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	for (int i = 1; i <= 200000; i ++) {
		list[i] = list[i - 1];
		int k = i;
		while (k) {
			list[i] += k % 10;
			k -= k % 10;
			k /= 10;
		}
	}
	while (t--) {
		int k;
		cin >> k;
		cout << list[k] << '\n';
	}
	return 0;
}
```

---

## 作者：Code_Select_You (赞：0)

## 思路
这道题的 $n \le 2⋅10^5$，所以可以在程序开始前暴力枚举 $1$ 到 $2⋅10^5$ 范围内所有的数的数位和，然后前缀和求出答案即可。

## AC code
```cpp

#include<bits/stdc++.h>
using namespace std;
long long s[200001];
int T,n;
void init(){
	int l=2e5;
	for(int i=1;i<=l;i++){
		int q=i;
		long long p=0;
		while(q){
			p+=q%10,q/=10;
		}
		s[i]=p+s[i-1];
	}
}
int main(){
	scanf("%d",&T);
	init();
	while(T--){
		scanf("%d",&n);
		printf("%lld\n",s[n]);
	}
	return 0;
} 
```


---

## 作者：RyanLi (赞：0)

传送门：洛谷 [Vlad and a Sum of Sum of Digits](https://www.luogu.com.cn/problem/CF1926C) | Codeforces [C. Vlad and a Sum of Sum of Digits](https://codeforces.com/contest/1926/problem/C)

更佳的阅读体验：[CF1926C 题解](https://blog.ryanli.top/index.php/archives/37/)

---

**简要题意**：给定多个 $n$，询问 $1$ 到 $n$ 的所有数字的**数位之和**。

如果我们对于每次询问都暴力地求解，那么时间消耗将非常巨大。不难想到，对于每个 $n$，它的答案都是唯一的。

注意到，$1$ 到 $n$ 的所有数字的数位和，一定是 $1$ 到 $n - 1$ 的所有数字的数位和，加上 $n$ 的数位和，答案具有显然的递推关系。

考虑递推预处理。由于 $n$ 的范围只有 $2 \times 10^5$，在程序开始时暴力地计算 $n$ 的值为 $1$ 到 $2 \times 10^5$ 的答案进行预处理即可。

```cpp
#include <iostream>
using namespace std;
using ll = long long;

const int N = 2e5 + 10;
int t, n, a[N], sum, tmp;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for (int i = 1; i < N; ++i) {
        tmp = i, sum = 0;
        while (tmp) sum += tmp % 10, tmp /= 10;
        a[i] += a[i - 1] + sum;
    } for (cin >> t; t; --t) {
        cin >> n;
        cout << a[n] << '\n';
    } return 0;
}
```



---

## 作者：jess1ca1o0g3 (赞：0)

[Portal(Luogu)](https://www.luogu.com.cn/problem/CF1926C)

[Portal(CF)](https://codeforces.com/contest/1926/problem/C)

## 思路

题本身很简单，将每个数字拆开相加。

由于时限仅有 $0.5s$，可以使用前缀和，预处理所有答案，然后 $\mathcal{O(1)}$ 查表。

设 $a$ 为前缀和数组，则 $a_i=\sum_{j=1}^{i}{d(j)}$，$d(i)$ 是 $i$ 的数位和。

然后边读边查 $a_n$。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define YES cout<<"Yes"<<endl;
#define NO cout<<"No"<<endl;
using namespace std;
const int SIZE=2e5;
ll t,a[SIZE+5];
void init(){
	for(int i=1;i<=SIZE;i++){
		int k=0,tmp=i;
		while(tmp){
			k+=tmp%10;
			tmp/=10;
		}
		a[i]=a[i-1]+k;
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>t;
	init();
	while(t--){
		int n;
		cin>>n;
		cout<<a[n]<<endl;
	}
	return 0;
}
```

---

## 作者：Programming_Konjac (赞：0)

# 思路
先预处理出 $1\rightarrow200000$ 的数位之和，然后用前缀和进行求和。

求数位之和的方法：

1. 用累加器加上这个数个位。

2. 然后把这个数的个位去掉，那么十位变成个位，百位变成十位等等。

直到这个数为 $0$，然后停止循环。

把最后得到的 $200005$ 个数求个前缀和，前缀和公式：$sum_i=sum_{i-1}+a_i$。

预处理完之后，对于每次的 $n$，直接输出前缀和数组的第 $n$ 项就可以了。

# 代码
~~codeforces 打不开了，只能重写了 QwQ~~。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,sum[200005];
int sumc(int n){
    int ans=0;
    while(n){
        ans+=n%10;
        n/=10;
    }
    return ans; 
}
int main(){
    for(int i=1;i<=200000;i++) sum[i]=sum[i-1]+sumc(i);
    cin>>t;
    while(t--){
    	cin>>n;
    	cout<<sum[n]<<"\n";
    }
    return 0;
}

```

---

## 作者：minVan (赞：0)

**题目大意**

求 $1$ 到 $n$ 每个数的数字和的和。

**解题思路**

$100$ 位一节，每节的十位数字和加上个位数字和为 $900$，再算上百位及以上数字和乘 $100$ 即可。

最后多出的个数一定小于 $100$，每个都暴力求解数字和即可。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 15;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    int n, i, ans = 0;
    cin >> n;
    for(i = 0; i + 100 <= n; i += 100) {
      int tmp = i, c = 0;
      while(tmp) {
        c += tmp % 10;
        tmp /= 10;
      }
      ans += c * 100 + 900;
    }
    for(; i <= n; i++) {
      int tmp = i, c = 0;
      while(tmp) {
        c += tmp % 10;
        tmp /= 10;
      }
      ans += c;
    }
    cout << ans << '\n';
  }
  return 0;
}

```

---

## 作者：tder (赞：0)

考虑记忆化。

用 $a_i$ 表示前 $i$ 个数的答案，每次询问若已经计算则输出 $a_n$ 即可，反之暴力计算。

另外需要维护 $m$ 表示当前计算完的最大值。

时间复杂度 $O(n_{\max}\log n_{\max})$。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int t, n, m, a[N];
signed main() {
    cin>>t;
    while(t--) {
        cin>>n;
        if(a[n]) {
            cout<<a[n]<<endl;
            continue;
        }
        int s = a[m];
        for(int i = m + 1; i <= n; i++) {
            int cnt = 0, k = i;
            while(k) {
                cnt += k % 10;
                k /= 10;
            }
            s += cnt;
            a[i] = s;
        }
        cout<<a[n]<<endl;
        m = max(m, n);
    }
}
```

---

## 作者：lovely_hyzhuo (赞：0)

一个不预处理的题解。

对于本题，考虑直接暴力去做，时间复杂度是 $O(TN\lfloor\log_{10}^{(N)}\rfloor)$ 的。

显然不可过（CF 又不是 CCF）。

考虑记忆化，你会发现你过了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[2000010];
int maxn=0;
void solve()
{
	int n;
	cin>>n;
	if(a[n]!=0)
	{
		cout<<a[n]<<endl;
		return;
	}
	int sum=a[maxn];
	for(int i=maxn+1;i<=n;i++)
	{
		int cnt=0;
		int ttt=i;
		while(ttt)
		{
			int tttt=ttt%10;
			cnt+=tttt;
			ttt/=10;
		}
		sum+=cnt;
		a[i]=sum;
	}
	a[n]=sum;
	maxn=max(maxn,n);
	cout<<sum<<endl;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
		solve();
	return 0;
}
```


---

## 作者：__O__o__ (赞：0)

## 大致思路
由于数据范围过大，并且题目时限较小。我们只能预处理一下每一个数的数位之和，然后再做一个前缀和，然后对于每一次查询进行 $O(1)$ 的操作即可。
## 代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[200006];
inline void init()
{
    int sum1=0;
    for(int i=1;i<=200000;i++)
    {
        int t=i,sum=0;
        while(t)
        {
            sum+=t%10;
            t/=10;
        }
        sum1+=sum;
        a[i]=sum1;
    }
}
int main()
{
    init();
    int T;
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;
        cout<<a[n]<<'\n';
    }
    return 0;
}
```

---

## 作者：Eason_cyx (赞：0)

以 $12$ 为例，直接观察可能没啥思路，我们可以在小一些的数前面补 $0$ 来观察：

$00,01,02,03,04,05,06,07,08,09,10,11,12$。

根据题目，我们只需把这所有的**数字**加起来即可。那么，我们就可以把每一位拆开来计算。

如何算呢？我们先算个位数：

个位数是 $0\sim9$ 为一个周期，这样的**完整**周期有几组？$1$ 组。

$1$ 组的完整周期的和是多少？$\frac{(0+9)\times10}{2}\times1=45$。

剩下的数，是从 $0$ 到几？$0$ 到 $2$。和为多少？$\frac{(0+2)\times3}{2}=3$。

总和为：$45+3=48$。

所以个位数的贡献一共为 $48$。

再算十位：

十位数以 $0,\dots0,1\dots1,2\dots2,\dots9\dots9$ 为一组，其中每个数字都有相同的 $10$ 个。这样的完整周期有几组？$0$ 组（严谨起见，我们还是算一算 $0$ 组）。

$0$ 组的完整周期的和是多少？$(\frac{(0+9)\times10}{2}\times10)\times0=0$。

剩下的数，是从 $0$ 到几？$0$ 到 $1$。

先算 $0$，和为 $0\times10=0$。

$1$ 有几个？$3$ 个。

再算 $1$，和为 $1\times3=3$。

所以十位数的和为 $0+0+3=3$。

所以所有数的和为 $48+3=51$。

找到这个计算方法后，代码就好写了：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        int bas = 10;
        int k = n;
        long long sum = 0;
        while(k) {
            int num = k % 10;
            int cur = n / bas;
            int Num = cur * 45 * (bas/10);
            for(int i = 1;i < num;i++) {
            	Num += i * (bas/10);
            }
            Num += num * (n % (bas/10) + 1);
            sum += Num;
            bas *= 10;
            k /= 10;
        }
        cout << sum << endl;
    }
    return 0;
}
```

上位橙吧。

---

## 作者：_little_Cabbage_ (赞：0)

# CF1926C Vlad and a Sum of Sum of Digits 题解
~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-cf1926c)~~

这是一道思维题。

我们可以预处理出所有 $n$ 范围内的答案，每次询问输出即可。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010],b[200010];
void init()
{
	for(int i=1;i<=200000;i++)
	{
		int j=i;
		while(j>0)
		{
			a[i]+=j%10;
			j/=10;
		}
		b[i]=b[i-1]+a[i];
	}
}
signed main()
{
	init();
	long long t;
	scanf("%lld",&t);
	while(t--)
	{
		long long n;
		scanf("%lld",&n);
		printf("%lld\n",b[n]);
	}
}
```
[AC 记录](https://codeforces.com/contest/1926/submission/247291305)

[little_Cabbage 的 CF1926题解集](https://www.luogu.com.cn/blog/958804/cf1926-ti-xie-ji)

---

