# [ABC308E] MEX

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc308/tasks/abc308_e

$ 0,1,2 $ からなる長さ $ N $ の数列 $ A=(A_1,A_2,\dots,A_N) $ と、 `M`, `E`, `X` からなる長さ $ N $ の文字列 $ S=S_1S_2\dots\ S_N $ が与えられます。

$ 1\ \leq\ i\ <\ j\ <\ k\ \leq\ N $ かつ $ S_iS_jS_k= $ `MEX` を満たす全ての整数の組 $ (i,j,k) $ に対する $ \text{mex}(A_i,A_j,A_k) $ の総和を求めてください。 ここで、$ \text{mex}(A_i,A_j,A_k) $ は $ A_i,A_j,A_k $ のいずれとも一致しない最小の非負整数を意味します。

## 说明/提示

### 制約

- $ 3\leq\ N\ \leq\ 2\times\ 10^5 $
- $ N $ は整数
- $ A_i\ \in\ \lbrace\ 0,1,2\rbrace $
- $ S $ は `M`, `E`, `X` からなる長さ $ N $ の文字列
 
### Sample Explanation 1

$ S_iS_jS_k $ = `MEX` となる $ i,j,k\ (1\ \leq\ i\ <\ j\ <\ k\ \leq\ N) $ の組は $ (i,j,k)=(1,2,4),(1,3,4) $ の $ 2 $ つです。 $ \text{mex}(A_1,A_2,A_4)=\text{mex}(1,1,2)=0,\text{mex}(A_1,A_3,A_4)=\text{mex}(1,0,2)=3 $ より答えは $ 0+3=3 $ です。

## 样例 #1

### 输入

```
4
1 1 0 2
MEEX```

### 输出

```
3```

## 样例 #2

### 输入

```
3
0 0 0
XXX```

### 输出

```
0```

## 样例 #3

### 输入

```
15
1 1 2 0 0 2 0 2 0 0 0 0 0 2 2
EXMMXXXEMEXEXMM```

### 输出

```
13```

# 题解

## 作者：zac2010 (赞：6)

简单的计数题。

从左到右一遍扫过去，分三种情况：
1. $S_i=M$

	维护 $0,1,2$ 三种权值分别出现的次数。第 $i$ 种值的出现次数记为 $c_i$。
2. $S_i=E$

	利用第 $1$ 种情况维护的东西去维护两个数组合的所有情况。
   
   记 $t_{a,b}$ 为 `M` 和 `E` 位置上分别是 $a,b$ 的方案数。有 $t_{a,b}=c_a \times c_b$。
3. $S_i=X$

	利用第 $2$ 种情况统计答案——对于所有的两个数组合都把 $A_i$ 代进去求 $\text{MEX}$，然后别忘乘上两个数组合的方案数。
    
实现起来不难。

```cpp
#include <bits/stdc++.h>
#define int long long
#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 2e5 + 10;
int n, ans, a[N], c[3], t[3][3];
char s[N];
int mex(int a, int b, int c){
	int cnt[4] = {0}; cnt[a] = 1, cnt[b] = 1, cnt[c] = 1;
	L(i, 0, 3) if(!cnt[i]) return i;
}
signed main(){
	scanf("%lld", &n);
	L(i, 1, n) scanf("%lld", &a[i]);
	L(i, 1, n) scanf(" %c", &s[i]);
	L(i, 1, n){
		if(s[i] == 'M'){
			c[a[i]]++;
		}
		else if(s[i] == 'E'){
			L(j, 0, 2) if(c[j]) t[min(j, a[i])][max(j, a[i])] += c[j];
		}
		else{
			L(j, 0, 2) L(k, j, 2){
				if(a[i] < j) ans += t[j][k] * mex(a[i], j, k);
				else if(a[i] >= k) ans += t[j][k] * mex(j, k, a[i]);
				else ans += t[j][k] * mex(j, a[i], k);
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：CQ_Bob (赞：1)

## 分析

题目不难。（看错了三遍）

由于这道题的所有元素值不会大于二，所以我们可以推导出以下结论：

1. 在 $\text{mex} (A_i,A_j,A_k)=0$ 时，$A_i,A_j,A_k$ 中至少有一个的值为 $1$，一个的值为 $2$。（边界限制，取定值）

2. 在 $\text{mex} (A_i,A_j,A_k)=1$ 时，$A_i,A_j,A_k$ 中至少有一个的值为 $0$，一个的值为 $2$。

3. 在 $\text{mex} (A_i,A_j,A_k)=2$ 时，$A_i,A_j,A_k$ 中至少有一个的值为 $1$，一个的值为 $0$。

4. 在 $\text{mex} (A_i,A_j,A_k)=3$ 时，$A_i,A_j,A_k$ 中必有一个为 $0$，一个为 $1$，一个为 $2$。

然后就是模拟了。我们以字符 $\text{E}$ 为中间点（分割点），找到对于每个 $\text{E}$，其左边的字符是 $\text{M}$ 的值分别为 $0,1,2$ 的数量，其右边的字符是 $\text{X}$ 的值为别为 $0,1,2$ 的数量。再按照上面的结论，对于三种不同的值利用组合数进行计算即可。找到左边和右边的那些值，我们可以用前缀（后缀）和。

注：第一个结论怎么都知道是无效的，可以省略。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int n;
int sa0[N],sc0[N];//前缀（后缀）和 
int sa1[N],sc1[N];
int sa2[N],sc2[N];
int s[N];//读入值 
char ch[N];//字符串 
int ans;//答案 
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	for(int i=1;i<=n;i++){
		cin>>ch[i];
		sa0[i]+=sa0[i-1],sa1[i]+=sa1[i-1],sa2[i]+=sa2[i-1];
		if(ch[i]=='M'){
			if(s[i]==0) sa0[i]++;
			else if(s[i]==1) sa1[i]++;
			else sa2[i]++; 
		}
		else if(ch[i]=='X'){
			if(s[i]==0) sc0[i]++;
			else if(s[i]==1) sc1[i]++;
			else sc2[i]++;
		} 
	}
	for(int i=n;i>=1;i--){
		sc0[i]+=sc0[i+1],sc1[i]+=sc1[i+1],sc2[i]+=sc2[i+1];		
	}
	//上面是输入和预处理前缀（后缀）和 
	for(int i=1;i<=n;i++){//枚举每个分割点（E） 
		if(ch[i]=='E'){
			if(s[i]==0){//这里是按照E的影响进行计算的 
				ans+=1*(sa0[i]*sc2[i]+sa2[i]*sc0[i]+sa2[i]*sc2[i]+sa0[i]*sc0[i]);
				ans+=2*(sa0[i]*sc1[i]+sa1[i]*sc0[i]+sa1[i]*sc1[i]);
				ans+=3*(sa1[i]*sc2[i]+sa2[i]*sc1[i]);
			}//组合数求方案 
			else if(s[i]==1){
				ans+=2*(sa0[i]*sc1[i]+sa1[i]*sc0[i]+sa0[i]*sc0[i]);
				ans+=3*(sa0[i]*sc2[i]+sa2[i]*sc0[i]);				
			}
			else if(s[i]==2){
				ans+=1*(sa0[i]*sc2[i]+sa2[i]*sc0[i]+sa0[i]*sc0[i]);
				ans+=3*(sa1[i]*sc0[i]+sa0[i]*sc1[i]);
			}
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：未来姚班zyl (赞：1)

## 题目大意

给你一个长度为 $N$ 的数列 $A$ （只含数值 $0,1,2$）和长度为 $N$ 的字符串 $S$（只含字符 `M`,`E`,`X`），求 $\sum\limits_{1\le i<j<k\le N}[S_iS_jS_k=$ `MEX` $]$ $\operatorname{mex}(a_i,a_j,a_k))$。

## 题目分析

题目还是比较简单的。首先对于 mex，由于数列只包含 $0,1,2$，可以直接预处理所有的情况，代码也很短。其次，我们将三个数压缩成一个三进制的三位数，在十进制下这个数的范围为 $[0,26]$，在三进制下的每一位代表了对应的 $A$ 值。这时候预处理就是这样写了：
```cpp
inline int w(int x){
	int a,b,c;
	a=x%3,x/=3,b=x%3,x/=3,c=x;
	if(a&&b&&c)return 0;
	if((a^1)&&(b^1)&&(c^1))return 1;
	if((a^2)&&(b^2)&&(c^2))return 2;
	return 3;
}
```

这样我们对一个选择可以快速求值，现在就是要计数。

同样的思路，我们分别记录 `M` 对应的取值的数量 $sm_{i}$，表示 `M` 位上取 $i$ 的数量，再记录 $sme_i$，其中 $0\le i\le8$ 设 $i$ 在三进制下的高位为 $x$，低位为 $y$，则表示 `M` 对应的位置取了 $x$，`E` 对应的位置取了 $y$。这样的话，从左往右遍历 $S$，若 $S_i=$ `M`，则 $sm_{a_i}$ 加一；若 $S_i=$ `E`，则对于 $0\le i\le 2$，$sme_{i\times 3+a_i}$ 加上 $sm_i$；若 $S_i=$ `X`，则对于 $0\le i\le8$，将 $i\times 3+a_i$ 的值投进上面的函数中，将得到的值乘上 $sme_i$，累加到答案就可以了。复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1)
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define ull unsigned long long
#define ui unsigned int
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5,M=2e6+5,inf=2147000000,base=19491001;
const ll mod=998244353;
using namespace std;
int n=read(),a[N];
char s[N];
ll sm[3],sme[15];
inline ll w(int x){
	int a,b,c;
	a=x%3,x/=3,b=x%3,x/=3,c=x;
	if(a&&b&&c)return 0;
	if((a^1)&&(b^1)&&(c^1))return 1;
	if((a^2)&&(b^2)&&(c^2))return 2;
	return 3;
}
ll ans;
int main(){
	rep(i,1,n)a[i]=read();
	cin >> s+1;
	rep(i,1,n){
		switch(s[i]){
			case 'M':
				sm[a[i]]++;
				break;
			case 'E':
				rep(j,0,2)sme[j*3+a[i]]+=sm[j];
				break;
			default:
				rep(j,0,8)ans+=sme[j]*w(j*3+a[i]);
				break;
		}
	}
	cout <<ans;
	return 0;
}
```



---

## 作者：梦应归于何处 (赞：1)

题目大意：

给定长度为 $N$ 的包含 $0,1,2$ 的序列 $A_1,A_2 \dots A_n$,和一个长度为 N 的包含字符 ``MEX`` 的字符串 $S = S_1$,$S_2 \dots S_n$。对于所有符合条件 $1 \le i < j < k \le N$，$S_iS_jS_k$ = ``MEX`` 的三元组 $(i, j, k)$，请你求出 $\operatorname{mex}(A_i, A_j, A_k)$ 之和。$\operatorname{mex}()$ 函数表示未出现在序列中的最小非负整数。

## 思路

我们从左边到右边把 $M$ 的个数都处理出来，可以当成一个前缀和，然后，我们再从右边到左边把 $X$ 的个数都处理出来，可以当成一个后缀和。预处理就完成了。

那我们应该怎么计算呢？

我们在字符串 $S$ 中找到 ``MEX`` 中间的 ``E``，然后把左边的 ``M`` 的个数、右边的 ``E`` 的个数和 $\operatorname{mex}(j,A_i,k)$ 相乘，然后，把所有的都相加起来，就得到了最终的答案。

详情见代码。

代码：
~~~cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll a[300000];
ll cntl[300000][5], cntr[300000][5];
/*cntl[i][j]代表前i个字符中，a数组的值为j的'M'的个数。cntr[i][j]代表后i个字符中，a数组的值为j的'X'的个数。*/
ll mex(ll i, ll j, ll k) {
	for (int s = 0; s <= 2; s++) {
		if (i != s && j != s && k != s) {
			return s;
		}
	}
	return 3;
}
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	string s;
	cin >> s;
	for (int i = 1; i <= n; i++) { //预处理M的个数
		if (s[i - 1] == 'M') {
			cntl[i][a[i]]++;
		}
		for (int j = 0; j <= 2; j++) {
			cntl[i][j] += cntl[i - 1][j];
		}
	}
	for (int i = n; i >= 1; i--) { //预处理X的个数
		if (s[i - 1] == 'X') {
			cntr[i][a[i]]++;
		}
		for (int j = 0; j <= 2; j++) {
			cntr[i][j] += cntr[i + 1][j];
		}
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++) { //算最终的答案
		if (s[i - 1] == 'E') {
			for (int j = 0; j <= 2; j++) {
				for (int k = 0; k <= 2; k++) {
					ans += cntl[i - 1][j] * cntr[i + 1][k] * mex(j, a[i], k); //前面讲的公式
				}
			}
		}
	}
	cout << ans;
	return 0;
}

~~~

[AT上的AC记录](https://atcoder.jp/contests/abc308/submissions/43159978)

---

## 作者：引领天下 (赞：1)

题意：给出一个长度为 $N$ 的仅由 $0,1,2$ 构成的序列 $A=(A_1,A_2,\dots,A_N)$ 以及一个长度为 $N$ 仅由 `M,E,X` 构成的字符串 $S=S_1S_2\dots S_N$。现求对所有 $1\le i<j<k\le N$ 且 $S_iS_jS_k=$ `MEX` 的 $\operatorname{mex}(A_i,A_j,A_k)$，其中 $\operatorname{mex}(A_i,A_j,A_k)$ 表示不等于 $A_i,A_j,A_k$ 的最小非负数。

做法：$N\le2\times10^5$，这肯定是不能 $O(N^3)$ 暴力枚举了。

我们能承受的复杂度是 $O(N)$，这就意味着我们需要在 $i,j,k$ 中挑选一个枚举。依次尝试后我们发现只有枚举 $j$ 是可做的，因为 $j$ 相当于是中间的“断点”，可以拆分前后两个问题。

考虑答案怎么算。我们发现 $\operatorname{mex}(A_i,A_j,A_k)$ 只有 $27$ 种可能，所以考虑对 $A_j$ 分类讨论（为方便起见，记一组 $A_i,A_j,A_k$ 为 $A_iA_jA_k$）：

- $A_j=0$，那么答案可能为 $1,2,3$。

  - 答案为 $1$：对应于 $000,002,202$ 的情况。
  
  - 答案为 $2$：对应于 $001,100,101$ 的情况。
  
  - 答案为 $3$：对应于 $102,201$ 的情况。
  
- $A_j=1$，那么答案可能为 $0,2,3$。答案为 $0$ 时压根对最后的结果没有贡献，所以此处不讨论。

  - 答案为 $2$：对应于 $010,011,110$ 的情况。
  
  - 答案为 $3$：对应于 $210,012$ 的情况。

- $A_j=2$，那么答案可能为 $0,1,3$。同样不讨论答案为 $0$ 的情况。

  - 答案为 $1$：对应于 $020,022,220$ 的情况。
  
  - 答案为 $3$：对应于 $120,021$ 的情况。
  
至此，我们已经弄清了应该如何计算，剩下的便是实现了。

具体实现中，我们分别维护一个前缀和和一个后缀和：$m[j][i]$ 表示 $1\sim i$ 中 $A_t$ 为 $j$ 且 $S_t$ 为 `M` 的 $t$ 的数量，$x[j][i]$ 表示 $i\sim N$ 中 $A_t$ 为 $j$ 且 $S_t$ 为 `X` 的 $t$ 的数量。这样在计算时我们直接就得到了对应情况中 $j$ 前的 `M` 的数量和 $j$ 后的 `X` 的数量，根据乘法原理计算即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[200005],m[3][200005],x[3][200005],ans;
string s;
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    cin>>s;
    for(int i=1;i<=n;i++){
        for(int j=0;j<3;j++)m[j][i]=m[j][i-1];
        if(s[i-1]=='M')m[a[i]][i]++;
    }
    for(int i=n;i>=1;i--){
        for(int j=0;j<3;j++)x[j][i]=x[j][i+1];
        if(s[i-1]=='X')x[a[i]][i]++;
    }
    for(int i=1;i<=n;i++)if(s[i-1]=='E'){
        if(a[i]==2)ans+=m[0][i]*x[2][i]+m[0][i]*x[0][i]+m[2][i]*x[0][i]+3*(m[0][i]*x[1][i]+m[1][i]*x[0][i]);/*0 2 2  0 2 0  2 2 0  0 2 1  1 2 0*/
        else if(a[i]==1)ans+=2*(m[0][i]*x[1][i]+x[0][i]*m[1][i]+m[0][i]*x[0][i])+3*(m[0][i]*x[2][i]+m[2][i]*x[0][i]);/*0 1 0  0 1 1  1 1 0  0 1 2  2 1 0*/
        else ans+=m[0][i]*x[2][i]+m[2][i]*x[0][i]+m[0][i]*x[0][i]+m[2][i]*x[2][i]+3*(m[1][i]*x[2][i]+m[2][i]*x[1][i])+2*(m[1][i]*x[0][i]+m[0][i]*x[1][i]+m[1][i]*x[1][i]);/*0 0 2  0 0 0  2 0 0  2 0 2  1 0 2  2 0 1  1 0 1  1 0 0  0 0 1*/
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：xiaoming007 (赞：1)

~~猫儿小~~

## 思路

模拟，但是有难度。

首先我们看到要凑出 `MEX` 这三个字符，第一时间想到之前凑个数的方法——记录前缀的 `M` 和后缀的 `X`，然后碰到每一个 `E`，个数便加上 `M` 的个数 $\times$ `X` 的个数。  
那如果每个数都有权值，是否可以求呢？  
答案肯定是可以的，我们分别记录 `M` 和 `X` 每种权值出现的次数，对于每个 `E`，直接列举所有可能，算总和便可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[1010101];
//int dp[1010101][4][4];
long long ans = 0;
string s;
int mex(int x, int y, int z){
	for(int i = 0; i < 4; ++i){
		if(i != x && i != y && i != z) return i;
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	cin >> s;
	long long m0 = 0, m1 = 0, m2 = 0, k0 = 0, k1 = 0, k2 = 0;
	int len = s.size();
	for (int i = 0; i < len; ++i) {
		if (s[i] == 'X') {
			if (a[i] == 0) k0++;
			else if (a[i] == 1) k1++;
			else k2++;
		}
	}
	for (int i = 0; i < len; ++i) {
		if (s[i] == 'M') {
			if (a[i] == 0) m0++;
			else if (a[i] == 1) m1++;
			else m2++;
		}
		if (s[i] == 'E') {
			ans += mex(0, a[i], 0) * m0 * k0;
			ans += mex(0, a[i], 1) * m0 * k1;
			ans += mex(0, a[i], 2) * m0 * k2;
			ans += mex(1, a[i], 0) * m1 * k0;
			ans += mex(1, a[i], 1) * m1 * k1;
			ans += mex(1, a[i], 2) * m1 * k2;
			ans += mex(2, a[i], 0) * m2 * k0;
			ans += mex(2, a[i], 1) * m2 * k1;
			ans += mex(2, a[i], 2) * m2 * k2;
		}
		if (s[i] == 'X') {
			if (a[i] == 0) k0--;
			else if (a[i] == 1) k1--;
			else k2--;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc308_e)
### 题解
比较麻烦的题。

将题目中的 `MEX` 分为三部分：`M` 和 `EX`。
首先考虑 `EX`，令 $tmp_{i,j,k}$ 表示从 $i\sim n$ 中，字符分别是 `EX` 时，序列中的权值为 $j,k$ 时的方案数，代码中并没有特判当前位置的字符是否为 `E`，但在求答案时有判断。

$tmp$ 数组可以和 $cnt$ 数组配合求解，其中在这里，$cnt_u$ 表示处理当前 $tmp_{i,j,k}$ 时，权值为 $u$ 且位置在 $i\sim n$ 中的字符为 `X` 的数量。

得到了 $tmp$ 数组后，接下来就是处理答案了。

这时，令 $cnt_u$ 表示当前处理到的 $i$ 之前中字符为 `M` 的数量。若当前字符为 `E`，那么答案就要加上 $\displaystyle\sum_{j=0}^2\sum_{k=0}^2\sum_{u=0}^2(tmp_{i,j,k}\times cnt_u\times mex(j,k,u))$。

注意开 long long。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef pair <int,int> PII;
const int N = 200010;
int n;
int a[N];
char s[N];
int tmp[N][9];
int mex (int a,int b,int c) {
	int x = 0;
	while (a == x || b == x || c == x) x++;
	return x;
}
int main () {
	cin >> n;
	for (int i = 1;i <= n;i++) cin >> a[i];
	cin >> s + 1;
	int cnt[3] = {};
	for (int i = n;i >= 1;i--) {
		for (int j = 0;j < 3;j++) tmp[i][min (j,a[i]) * 3 + max (j,a[i])] = cnt[j];
		if (s[i] == 'X') cnt[a[i]]++;
	}
//	for (int i = 1;i <= n;i++) {
//		for (int j = 0;j < 9;j++) cout << tmp[i][j] << ' ';
//		cout << endl;
//	}
	cnt[0] = cnt[1] = cnt[2] = 0;
	LL ans = 0;
	for (int i = 1;i <= n;i++) {
		if (s[i] == 'M') cnt[a[i]]++;
		else if (s[i] == 'E') {
			for (int t1 = 0;t1 < 3;t1++) {
				for (int t2 = t1;t2 < 3;t2++) {
					for (int j = 0;j < 3;j++) ans += (LL)mex (t1,t2,j) * cnt[j] * tmp[i][t1 * 3 + t2];
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Msents (赞：0)

大水题

~~就是比赛的时候脑子短路了没想出来~~

### 题意

给你一个长度为 $n$ 的数组 $a$ 和一个长度为 $n$ 的字符串 $s$，其中数组由 $0 , 1 , 2$ 这三个数组成，字符串由 `M`, `E`, `X` 这三个字母组成。我们定义 $ \text{mex}(a_i,b_j,c_k) $ 为不等于 $a_i$，$a_j$，$a_k$ 的最小自然数。一个三元组 $( i,j,k)$ 能产生贡献，仅当 $1\leq i<j<k\leq n$ 且 $s_i$ 为 `M`，$s_j$ 为 `E`，$s_k$ 为 `X`，该贡献为 $ \text{mex}(a_i,b_j,c_k) $。求所有贡献之和。

### 思路

预处理 $sum$，设 $sum[i][j][k]$ 为 $a_p$ 为 $i$，$s_p$ 为 $j$ 中 $p$ 的个数 $(1\leq p\leq k)$。

我们依次处理每位为在 $s$ 对应的位置中字符为 `E` 的下标 $j$，再依次处理下标 $i$ 在 $s$ 中为 `M`，在 $a$ 中为不同数字的情况，$k$ 同理。设 $num1$ 为 $j$ 对应的数字，$num3$ 为 $k$ 对应的数字。通过 $sum$，对于每一个 $j$，我们快速可以求出形如这样的 $(i,j,k)$ 的数量为 $sum[M][num1][j-1]\times(sum[X][num3][n]-sum[X][num3][j])$。

因为数字一样，所以我们可以求出这样的三元组的贡献为 $ \text{mex}(num1,a_j,num3) $。

将它们相乘，全部加起来就是最终的答案。

复杂度 $Θ(n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//可能会爆int
const int MaxN=200000;
int n,a[MaxN+1],b[MaxN+1],sum[3][3][MaxN+1];
int Mex(const int a,const int b,const int c){
	if(a==0||b==0||c==0){
		if(a==1||b==1||c==1){
			if(a==2||b==2||c==2){
				return 3;
			}else{
				return 2;
			}
		}
		return 1;
	}
	return 0;
}
void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		char c;
		cin>>c;
		if(c=='M')b[i]=0;
		else if(c=='E')b[i]=1;
		else b[i]=2;
//这里将字符转换，节省空间
	}
	for(int mode=0;mode<3;mode++){
		for(int num=0;num<3;num++){
			for(int i=1;i<=n;i++){
				sum[mode][num][i]=sum[mode][num][i-1]+(num==a[i]&&mode==b[i]);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(b[i]==1){
			for(int num1=0;num1<3;num1++){
				for(int num3=0;num3<3;num3++){
					ans+=
						Mex(num1,a[i],num3)*
						sum[0][num1][i-1]*
						(sum[2][num3][n]-sum[2][num3][i]);
				}
			}
		}
	}
	cout<<ans;
}
#undef int
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
//	int T;
//	cin>>T;
//	while(T--)
		Solve();
	return 0;
}

```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc308_e)     
比较麻烦的题目。      
## 题意
给你一个字符串 $s$ 和序列 $a$，它们长度相等。       
$s$ 仅由 `M`、`E`、`X` 组成，$a$ 仅由 $0,1,2$ 组成。      
我们定义，$\operatorname{mex}(a,b,c)$ 指第一个不等于 $a,b,c$ 的自然数。      
那么，对于每一组三元组 $(i,j,k)(1\le i<j<k\le n)$，如果 $s_i$ 为 `M`，$s_j$ 为 `E`，$s_k$ 为 `X`，它的贡献我们就定义为 $\operatorname{mex}(a_i,a_j,a_k)$。求所有三元组的贡献之和。           
## 解法
首先，我们发现 $a$ 仅由 $0,1,2$ 组成，那么 $\operatorname{mex}$ 实际上要考虑的情况很少，我们可以进行预处理。这里我们可以使 $0$ 产生 $2$ 的贡献，$1$ 产生 $3$ 的贡献，$2$ 产生 $5$ 的贡献。枚举的时候将其乘起来即可（根据唯一分解定理可知不会重复）。      
那么现在的问题转化到求每种三元组的个数。     
我们设 $qe_{i,j}$ 为当前在 $i$ 的位置，在这个字符和这个字符之后的 `X` 且对应 $a$ 的值为 $j$ 的数量（就是一个后缀和）。      
这一部分我们很好进行递推，我们倒着枚举 $i$，那么对于任何一种 $j$：     
$qe_{i,j}=qe_{i+1,j}+[a_i=j\land s_i=\text{X}]$。      
我们还需要预处理出 `E`。      
我们设 $qx_{i,j,k}$ 为当前在 $i$ 的位置，在这个字符和这个字符之后的 `EX` 子序列数量且 `E` 对应数值为 $j$，`X` 对应数值为 $k$ 的数量。      
我们还是倒序枚举 $i$，对于每个 $j$ 和 $k$：     
$qx_{i,j,k}=qx_{i+1,j,k}+[s_i=\text{E}\land a_i=j]qe_{i,k}$。   
这个式子有点复杂，我们慢慢解释。   
前半部分我们是把上一次的值继承过来。后半部分的判断条件是对这一个为 `E` 的条件判断（因为只有这一位为 `E` 才对答案有贡献），后面是对 `X` 的累加。     
那么我们最后再扫一遍字符串，把每个为 `M` 的地方搜一遍所有的状态即可。          
总体时间复杂度 $O(n)$，可以通过。   
[CODE](https://www.luogu.com.cn/paste/l91fv5b4)

---

## 作者：FreedomKing (赞：0)

这是一篇比较友好的题解。

### 题目大意

给定一个 $n$，一段长度为 $n$ 的序列 $A$，一段长度为 $n$ 的仅由 $0,1,2$ 构成的字符串 $S$。

对于每一个三元组 $(i,j,k)(1\le i\le j\le k\le n)$，若 $S_i+S_j+S_k=$ `MEX`，我们将会得到一个由 $A_i,A_j,A_k$ 构成的集合，现在需要你求出每一个符合条件的三元组构成的集合的 mex 值之和。

- 关于 mex，它是指一个集合中最小的没有出现过的自然数。

### 思路

我们可以通过枚举 `E` 的方式来计算总和。对于每一个字母 `E`，能与它产生贡献的只有它前面的 `M` 和后面的 `X`，我们可以直接用前后缀和去维护 `M` 和 `X` 的数量。

但是，`MEX` 这三个字母分别对应的 $A_i$ 有三种可能值，所以一共有 $9$ 种可能，考虑将每个字母对应每种值分开维护和计算。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int a[N],n,m,t,k,ans;
char c[N];
struct node{
	int _0,_1,_2;
}M[N],X[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<=n;i++){//枚举M的前缀和
		if(c[i]=='M'){//分开枚举
			if(a[i]==0) M[i]._0++;
			if(a[i]==1) M[i]._1++;
			if(a[i]==2) M[i]._2++;
		}
		M[i]._0+=M[i-1]._0;
		M[i]._1+=M[i-1]._1;
		M[i]._2+=M[i-1]._2;
	}
	for(int i=n;i>=1;i--){//枚举X的后缀和
		if(c[i]=='X'){//分开枚举
			if(a[i]==0) X[i]._0++;
			if(a[i]==1) X[i]._1++;
			if(a[i]==2) X[i]._2++;
		}
		X[i]._0+=X[i+1]._0;
		X[i]._1+=X[i+1]._1;
		X[i]._2+=X[i+1]._2;
	}
	for(int i=1;i<=n;i++){//枚举E的位置
		if(c[i]=='E'){//分开讨论
			if(a[i]==0){
				ans+=M[i]._0*X[i]._0*1;
				ans+=M[i]._0*X[i]._1*2;
				ans+=M[i]._0*X[i]._2*1;
				
				ans+=M[i]._1*X[i]._0*2;
				ans+=M[i]._1*X[i]._1*2;
				ans+=M[i]._1*X[i]._2*3;
				
				ans+=M[i]._2*X[i]._0*1;
				ans+=M[i]._2*X[i]._1*3;
				ans+=M[i]._2*X[i]._2*1;
			}
			if(a[i]==1){
				ans+=M[i]._0*X[i]._0*2;
				ans+=M[i]._0*X[i]._1*2;
				ans+=M[i]._0*X[i]._2*3;
				
				ans+=M[i]._1*X[i]._0*2;
				ans+=M[i]._1*X[i]._1*0;
				ans+=M[i]._1*X[i]._2*0;
				
				ans+=M[i]._2*X[i]._0*3;
				ans+=M[i]._2*X[i]._1*0;
				ans+=M[i]._2*X[i]._2*0;
			}
			if(a[i]==2){
				ans+=M[i]._0*X[i]._0*1;
				ans+=M[i]._0*X[i]._1*3;
				ans+=M[i]._0*X[i]._2*1;
				
				ans+=M[i]._1*X[i]._0*3;
				ans+=M[i]._1*X[i]._1*0;
				ans+=M[i]._1*X[i]._2*0;
				
				ans+=M[i]._2*X[i]._0*1;
				ans+=M[i]._2*X[i]._1*0;
				ans+=M[i]._2*X[i]._2*0;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

