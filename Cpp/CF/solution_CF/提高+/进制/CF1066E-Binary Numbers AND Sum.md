# Binary Numbers AND Sum

## 题目描述

## 题目大意

现在，给你两个位数为 $n$ 和 $m$ 的两个二进制数$a$,$b$，现在，我们要进行如下操作：

* 计算$a$&$b$
* 答案累加上一个操作的值
* $b$右移一位，最后一位直接舍弃

现在,请你算出最终的答案，并输出，答案对998244353取模

## 样例 #1

### 输入

```
4 4
1010
1101
```

### 输出

```
12
```

## 样例 #2

### 输入

```
4 5
1001
10101
```

### 输出

```
11
```

# 题解

## 作者：离散小波变换° (赞：2)

## 题解

注意到 $A$ 不动，始终是 $B$ 在向右移动。我们考虑 $A$ 的每一个位上的 $1$ 对答案的贡献次数。显然从右往左数第 $i$ 位上的 $1$ 贡献的次数，就是 $B$ 里面从右往左数，第 $i$ 位以及往左的所有 $1$ 的个数。

可以拿如下这个例子来理解：

$$
\begin{array}{rl}
10110\textcolor{red} 10101 & :A \cr\hline
111010\textcolor{red}11111 & : B_0 \cr
11101\textcolor{red}01111 & : B_1 \cr
1110\textcolor{red}10111 & : B_2 \cr
111\textcolor{red}01011 & : B_3 \cr
11\textcolor{red}10101 & : B_4 \cr
1\textcolor{red}11010 & : B_5 \cr
\textcolor{red}11101 & : B_6 \cr
1110 & : B_6 \cr
\cdots
\end{array}
$$

我们观察与 $A$ 当中标红的那个 $1$，与它进行二进制与操作后，产生贡献的次数就是 $B$ 中标红的部分为 $1$ 的位的个数。

那么我们对 $B$ 求一个后缀和即可。时间复杂度 $\mathcal O(n+m)$。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
const int MAXN = 2e5 + 3;
const int MOD  = 998244353;
char A[MAXN], B[MAXN];
int S[MAXN], ans = 0, t = 1;
int main(){
    int n = qread(), m = qread();
    scanf("%s", A + 1);
    scanf("%s", B + 1);
    dn(m, 1, i) S[i] = S[i + 1] + (B[i] == '1');
    dn(n, 1, i){
        if(m - (n - i) + 1 >= 1 && A[i] == '1')
            ans = (ans + 1ll * (S[1] - S[m - (n - i) + 1]) * t) % MOD;
        t = 2ll * t % MOD;
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：ztz11 (赞：1)

因为第一个二进制数不动，第二个在动，所以我们可以通过预处理第一个数来获得答案

因为是与，所以只有两个都是1时才会有答案的贡献

那么，比如说这个例子：

1001  
11010

他就会有如下几种情况

01001  
11010

1001  
1101

1001  
0110

1001  
0011

1001  
0001

我们会发现，第一位的1分别和上面的第一个1和最后一个1异或起来对答案有贡献

所以这个1对答案的贡献是$8+1=9$

我们把这个规律推广开来

对y中每一个1进行如上操作

即可得出答案

但是，我们会发现答案复杂度是O（$n \times m$）的，过不了

所以我们要预处理

用前缀和跑一遍x即可

复杂度优化到O($m+n$)

## code:
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rii register int i
#define rij register int j
#define p 998244353
#define int long long
using namespace std;
int a,b;
int x[200005],y[200005],bs[200005],qzh[200005];
void ycl()
{
	bs[0]=1;
	for(rii=1;i<=200002;i++)
	{
		bs[i]=bs[i-1]*2;
		bs[i]%=p;
	}
}
signed main()
{
	scanf("%lld%lld\n",&a,&b);
	for(rii=1;i<=a;i++)
	{
		x[i]=getchar()-'0';
	}
	getchar();
	for(rii=1;i<=b;i++)
	{
		y[i]=getchar()-'0';
	}
	ycl();
	for(rii=a;i>=1;i--)
	{
		qzh[a-i+1]=qzh[a-i];
		qzh[a-i+1]+=x[i]*bs[a-i];
		qzh[a-i+1]%=p;
	}
	if(b>a)
	{
		for(rii=a+1;i<=b;i++)
		{
			qzh[i]=qzh[i-1];
		}
	}
//	for(rii=1;i<=b;i++)
//	{
//		printf("%d ",qzh[i]);
//	}
	int ans=0;
	for(rii=1;i<=b;i++)
	{
		ans+=y[i]*qzh[b-i+1];
		ans%=p;
	}
	cout<<ans%p;
}
```

---

## 作者：Zhao_daodao (赞：0)

# solution

又是一道恶意评分题。

先将两个字符串拍成两个数组。

考虑 $a$ 的每一位怎么对答案作出贡献：

只有在 $a_i=b_j=1$ 时能作出贡献。

其中 $j$ 是 $a_i$ 可能匹配到的 $b$ 字符串中的第 $j$ 位。

对于 $b$ 数组做一个前缀和 $sum$。

每一个 $a_i$ 都有一个 $2^{n-i}$ 的权值。

答案即为 $\sum_{i=1}^{n}2^{n-i}\times sum_{i+m-n}$。

注意：不能直接用位移计算二的次幂，会越界。

# code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+5;
const int mod=998244353;
int n,m;
string s_1,s_2;
int s1[MAXN],s2[MAXN];
int cnt=1,ans,anss;
int cntt[MAXN];
int s[MAXN];
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n>>m;
    cin>>s_1>>s_2;
    for(int i=0;i<n;i++)
        s1[i+1]=s_1[i]=='1'?1:0;
    for(int i=0;i<m;i++)
        s2[i+1]=s_2[i]=='1'?1:0;
    for(int i=1;i<=m;i++)
        cntt[i]=cntt[i-1]+(s2[i]==1);
    for(int i=n;i>=1&&i+(m-n)>=0;i--){
        if(s1[i]){
            anss=cntt[i+(m-n)]*cnt%mod; 
            ans=(ans+anss)%mod;
        }
        cnt=(cnt*2)%mod;
    }
    cout<<ans;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

考虑对于每一个 $a$ 上数位进行分析。令 $a_i$ 表示 $a$ 在二进制表示中**从左往右**数的第 $i$ 位上的数字，$b_i$ 同理。

分类讨论一下 $a_i$ 的取值对于答案的贡献：

1. 如果 $a_i = 0$，对于这一位无论如何都不会拥有贡献。

2. 如果 $a_i = 1$，因为 $b$ 会向右移，所以能产生贡献的一定是 $b_{j} = 1$ 的位置，其中 $j \in [1,i]$。那么可以用前缀和维护这个东西，令 $s_i$ 表示 $b_{1 \sim i} = 1$ 的数量。所以贡献就是 $s_i \times 2^{n - i}$。

当然你需要使 $a,b$ 位数相同，才好处理，所以在较短的数前面加前导零即可。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 2e5 + 10,mod = 998244353;
int n,m,ans;
int s[N];
string a,b;

inline int Add(int a,int b){
	return (a + b) % mod;
}

inline int Mul(int a,int b){
	return a * b % mod;
}

inline int qmi(int a,int b){
	int res = 1;
	while (b){
		if (b & 1) res = Mul(res,a);
		a = Mul(a,a);
		b >>= 1;
	}
	return res;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string za,zb;
	cin >> n >> m >> a >> b;
	for (re int i = n;i < m;i++) za += '0';
	for (re int i = m;i < n;i++) zb += '0';
	if (za.size()) a = ' ' + za + a;
	else a = ' ' + a;
	if (zb.size()) b = ' ' + zb + b;
	else b = ' ' + b;
	n = m = max(n,m);
	for (re int i = 1;i <= m;i++) s[i] = s[i - 1] + (b[i] == '1');
	for (re int i = 1;i <= n;i++){
		if (a[i] == '1') ans = Add(ans,Mul(s[i],qmi(2,n - i)));
	}
	cout << ans;
	return 0;
}
```

---

## 作者：henhen_ (赞：0)

这是一道~~非常水~~的蓝题。

### 题目大意

现在，给你两个位数为 $n$ 和 $m$ 的两个二进制数 $a$，$b$，我们要进行如下操作：

$\bullet$ 计算 $a\&b$。

$\bullet$ 答案累加上一个操作的值。

$\bullet$ $b$ 右移一位，最后一位直接舍弃。

### 思路

通过题意，我们可以非常容易的知道：

对于 $a_i$，如果 $a_i$ 等于 1，那么对答案的贡献就是 $b_i$ 以后所有为 1 的个数乘以 $2^i$，即可得到答案。

### 附上代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int a[200200],b[200200],sum[200200],cnt[200200];
int n,m;
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=n;i>=1;i--){//倒序读入 
		scanf("%1lld",&a[i]);//这样读入可以每次只读入一个数字 
	}
	for(int i=m;i>=1;i--){//倒序读入
		scanf("%1lld",&b[i]);
	}
	for(int i=1;i<=m;i++){
		if(b[i]){
			sum[i]=sum[i-1]+1;//前缀和优化 
		}else{
			sum[i]=sum[i-1];
		}
	}
	int ans=0;
	for(int i=1,p=1;i<=m;i++,p*=2,p%=mod){
		if(a[i]&&sum[m]-sum[i-1]){
			ans=(ans+(sum[m]-sum[i-1])*p%mod)%mod;
		}
	}
	printf("%lld",ans);
}
```


---

## 作者：guanyf (赞：0)

### 题意
- 给定长度分别为 $n,m$ 的二进制串 $a,b$，当 $a > 0$ 时，将 $ans$ 加上 $a\operatorname{and}b$ 的值，再将 $b$ 右移一位。

- 答案对 $998244353$ 取模，$1 \le n,m \le 2 \times 10^5$。

### 思路
由于这道题只能用线性的做法，因此直接模拟肯定是不行的，只能每一位都分别考虑。如果按位来考虑的话，为了方便操作，可以把 $a,b$ 翻转，并将长度小的串补上 $0$，直到长度相同。

```cpp
  reverse(s1.begin(), s1.end()), reverse(s2.begin(), s2.end());
  s1 = ' ' + s1, s2 = ' ' + s2;
  for (int i = (n < m ? n : m); i < (n < m ? m : n); i++) {
    (n < m ? s1 : s2) += '0';
  }
  (n < m ? n : m) = max(n, m);
```
设 $l$ 为补位之后串的长度，我们可以先按照题目模拟一遍：

第一次操作：$1010\operatorname{and}1101$

第二次操作：$0101\operatorname{and}1101$

第三次操作：$0010\operatorname{and}1101$

第四次操作：$0001\operatorname{and}1101$

可以发现：$a$ 中的第一个元素和 $b$ 中的 $1 \rightarrow l$ 个元素进行了 $\operatorname{and}$ 运算，$a$ 中的第二个元素和 $b$ 中的 $1 \rightarrow l-1$ 个元素进行了 $\operatorname{and}$ 运算……以此类推，$a$ 中的第 $i$ 个元素和 $b$ 中的 $1 \rightarrow l-i+1$ 个元素进行了 $\operatorname{and}$ 运算。

可是如何 $O(n)$ 计算出上述操作呢？对于 $a$ 每一个元素，我们可以先预处理出它所对应的 $b$ 中的元素的值 $v$。由于是位与运算，因此需要当 $a_i$ 为 $1$ 时，$ans$ 才能加上 $v$。

在计算 $v$ 的过程中，我们可以算出当前的位权 $tmp_j$，再将 $v$ 加上 $tmp_j \times b_j$。即使这样，我们依然在对于每个的 $i$ 时，都需要重新计算 $v$。但是，由于每次 $i$ 时平滑的变化的，因此 $v$ 等于 $v-tmp_i \times b_i$，不需要每次都重新计算一遍。

### 代码
```cpp
#include <algorithm>
#include <iostream>
#define M % 998244353
using namespace std;
using LL = long long;
const int MAXN = 2e5 + 5, mod = 998244353;
LL n, m, ans, tmp[MAXN], sum;
string s1, s2;
int main() {
  ios::sync_with_stdio(0);
  cin >> n >> m >> s1 >> s2;
  reverse(s1.begin(), s1.end()), reverse(s2.begin(), s2.end());
  s1 = ' ' + s1, s2 = ' ' + s2;
  for (int i = (n < m ? n : m); i < (n < m ? m : n); i++) {
    (n < m ? s1 : s2) += '0';
  }
  (n < m ? n : m) = max(n, m);  // 补位
  for (int i = 1; i <= n; i++) {
    tmp[i] = (i == 1 ? 1 : tmp[i - 1] * 2 M);  // 计算位权
  }
  for (int i = 1; i <= n; i++) {
    sum = (sum + tmp[i] * (s1[i] - '0')) M;  // 计算 v
  }
  for (int i = n; i >= 1; i--) {
    ans = (ans + sum * (s2[i] - '0')) M;           // 累加答案
    sum = (sum - tmp[i] * (s1[i] - '0') + mod) M;  // 更新 v
  }
  cout << ans;
  return 0;
}
```


---

## 作者：AlicX (赞：0)

## Solution 

首先不难想到计算 $a$ 的每一位对答案产生的贡献，然后题目告诉我们 $b$ 每次会往右移一位，然后结合样例可以发现：对于 $a$ 的第 $i$ 位，能与其产生贡献的条件是：$a_i=1$ 且 $b_j=1(i \leq j)$，对答案的贡献不难想出即为 $2^{i-1} \times \sum\limits_{j=i}^{m}b_j$，用前缀和维护即可，时间复杂度为 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second 
#define il inline 
#define db double
#define low(x) x&-x 
#define pb(x) push_back(x) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=2e5+10,Mod=998244353,INF=1e9+7;  
int n,m; 

int a[N],s[N];  
struct Mind{ 
	il bool operator<(Mind &Cyan)const{ } 
}; 
il int read(){ 
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); }
	return x*f;
} 
il int qmi(int x,int k){ 
	int res=1; 
	while(k){ 
		if(k&1) res=res*x%Mod; 
		x=x*x%Mod; k>>=1; 
	} return res; 
} 
signed main(){ char c; 
	n=read(),m=read(); int ans=0;  
	for(int i=1;i<=n;i++) cin>>c,a[i]=c-'0'; 
	for(int i=1;i<=m;i++) cin>>c,s[i]=s[i-1]+(c-'0'); 
	for(int i=n,j=m,p=0;i>=1&&j>=1;i--,j--,p++) if(a[i]) ans=(ans+s[j]*qmi(2ll,p)%Mod)%Mod;
	printf("%lld\n",ans); 
	return 0; 
} /*
10 1
1 2 3 7 2 6 8 10 10 7
*/ 
```


---

## 作者：CQ_Bob (赞：0)

## 分析

因为 $a$ 是一直没有改变的，移动的只有 $b$，所以从 $a$ 的每一位的贡献入手。

对于 $a$ 中的从低到高第 $i$ 位，其对应的十进制值是 $a_{n-i+1}\times 2^{i-1}$。注意到 $b$ 是每次右移一位的，所以在 $b$ 中能与 $a_{n-i+1}$ 匹配的都是在下标区间 $[1,m-i+1]$。根据 $1\&1=1,1\&0=0,0\&0=0$ 的性质，能够得到从低到高第 $i$ 位的贡献是：$a_{n-i+1}\times 2^{i-1}\times cnt_{m-i+1}$。其中 $cnt_i$ 表示 $b$ 中前 $i$ 位 $1$ 的数量。

注：$b$ 与 $a$ 的长度可能不一样，注意下标问题。

~~这题比 CF1881A 简单。~~

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int p=998244353;
string a,b;int n,m;
int cnt,ans,nw=1;

il void solve(){
	cin>>n>>m>>a>>b;
	for(re int i=0;i<m;++i) cnt+=(b[i]-'0');
	for(re int i=n-1,j=m-1;i>=0&&j>=0;--i,--j) 
		ans=(ans+(a[i]-'0')*nw*cnt)%p,
		nw=nw*2%p,cnt-=(b[j]-'0');
	cout<<ans;return ;
}

signed main(){
	solve();
	return 0;
}
```


---

