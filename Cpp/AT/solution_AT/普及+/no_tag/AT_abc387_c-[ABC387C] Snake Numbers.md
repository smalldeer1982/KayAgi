# [ABC387C] Snake Numbers

## 题目描述

在 $10$ 以上（含）的正整数中，我们称一个数字为**蛇数**当且仅当其开头的位（首位）数字严格大于其他位数。例如， $31$ 和 $201$ 是蛇数，而 $35$ 和 $202$ 不是。

求 $L$ 以上 $R$ 以下的蛇数的个数。

## 说明/提示

### 约定

- $10\leq L \leq R \leq 10^{18}$
- 输入均为整数

### 样例解释 1

$97$ 以上 $210$ 以下的蛇数有 $97,98,100,200,201,210$ 这 $6$ 个。

## 样例 #1

### 输入

```
97 210```

### 输出

```
6```

## 样例 #2

### 输入

```
1000 9999```

### 输出

```
2025```

## 样例 #3

### 输入

```
252509054433933519 760713016476190692```

### 输出

```
221852052834757```

# 题解

## 作者：_anll_ (赞：7)

你或许不信，但我真的被这道题卡到结束。
## 思路
来个数位 dp 做法，虽然官方题解不是这个。

首先，因为我们可能会顶着上界跑，所以我们需要 $top$ 来记录是否顶着上界。

其次，这道题需要讨论前导 $0$。但由于我们需要记录首位的大小，所以实际操作中没必要多此一举，直接记录最高位为多少即可。

于是状态就能表示出来了：$dp[len][top][maxn]$ 表示当前在做第 $len$ 位选择，最高位大小为 $maxn$，当 $top$ 为 $1$ 时表示顶着上界，反之。其他的正常做就行了，需要注意的是当走到最末位时，如果依旧顶着上界且上界到不了 $maxn$ 就要返回上界最大取值，否则正常返回 $maxn$。

## 代码
```CPP
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
int n,num[25],dp[25][2][10];
int dfs(int len,int top,int maxn){
	if(len==1) return top?min(maxn,num[1]+1):maxn;
	if(dp[len][top][maxn]) return dp[len][top][maxn];
	if(!maxn){
		int an=0;int mm=(top?num[len]:9);
		for(int i=0;i<=mm;i++){
			maxn=i;
			an+=dfs(len-1,(i==num[len])&&top,maxn); 
		}
		dp[len][top][0]=an;
		return an;
	}
	int an=0,mm=(top?num[len]:9);
	for(int i=0;i<=min(maxn-1,mm);i++){
		an+=dfs(len-1,(i==num[len])&&top,maxn);
	}
	dp[len][top][maxn]=an;return an;
}
int work(int x){
	memset(dp,0,sizeof(dp));n=0;
	while(x) num[++n]=x%10,x/=10;
	int an=dfs(n,1,0);
	return an;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int L,R;
	cin>>L>>R;
	cout<<work(R)-work(L-1); 
	return 0;
}
```

---

## 作者：player_1_Z (赞：5)

### 先来了解题目

这一题就是问你 $L$ 到 $R$ 内有多少个首位大于其他位的数。（题目中把首位大于其他位的数定义为“蛇数”）

[atcoder 原题](https://atcoder.jp/contests/abc387/tasks/abc387_c)
### 思路

我们发现数据较大，直接枚举 $L$ 到 $R$ 会超时，于是又想到**枚举位数**，在 $L$ 和 $R$ 特判。但是当 $R$ 和 $L$ 的位数相等时不好做。于是又又想到可以把 $1 \sim R$ 内的蛇数个数减去 $1 \sim (L - 1)$ 内的蛇数个数作为答案并输出。同时在计算 $1 \sim (L - 1)$ 内的蛇数个数和 $1 \sim R$ 内的蛇数个数时可以用枚举位数的方式。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=2005;
long long C[N][N],s[N],tot,l,r;
long long ksm(long long x,long long y){//快速幂 
	long long res=1;
	while(y){
		if(y&1) res=res*x;
		x=x*x;
		y>>=1;
	}
	return res;
}
long long sx(long long x){//1 ~ x 的蛇数个数 
	if(x<10) return 0;
	tot=0;
	while(x) s[++tot]=x%10,x/=10;//预处理 
	reverse(s+1,s+1+tot);
	long long ans=0;
	for(long long i=2;i<=tot;i++){
		for(long long j=1;j<=9;j++){
			if(i==tot&&j==s[1]) break;
			ans+=ksm(j,i-1);
		}
	}
	for(long long i=2;i<=tot;i++){//枚举位数 
		for(long long j=0;j<min(s[1],s[i]);j++) ans+=ksm(s[1],tot-i);
		if(s[i]<s[1]&&i==tot) ans+=ksm(s[1],tot-i);
		if(s[i]>=s[1]) break;
	}
	return ans;
}
int main(){
	cin>>l>>r;
	printf("%lld\n",sx(r)-sx(l-1));
	return 0;
}
```

---

## 作者：Ivan422 (赞：4)

竟然出了数位动态规划？在第三题？蒟蒻疑惑。

建议查看[模版](https://www.luogu.com.cn/problem/P2657)以学习。

我们先来看代码：[链接](https://atcoder.jp/contests/abc387/submissions/61380890)。

看到这道题，显然看出是一道非常典型的数位动态规划。

怎么整？

注意到这题的限制条件变成了枚举每一位的大小不能超过首位，那么我们考虑修改记忆化搜索中的 $r$ 定义。

在模版中，$r$ 是记录上一位的数，那么，我们将这个改成记录开头的数，$0$ 代表没有开头。

修改完这一个定义，我们再看搜素代码。


```cpp
int dfs(int p,int r,bool z,bool lmt){
	if(p==0)return 1;
	if(!lmt&&f[p][r]>-1)return f[p][r];
	int ans=0,mx=(lmt?c[p]:9);
	for(int i=0;i<=mx;i++){
		if(!z&&i>=r&&r!=0)continue;
		if(z&&i==0)ans+=dfs(p-1,0,1,lmt&&(i==mx));
		else ans+=dfs(p-1,(r==0?i:r),0,lmt&&(i==mx));
	}
	if(!lmt&&!z)f[p][r]=ans;
	return ans;
}
int func(int x){
	memset(f,-1,sizeof(f));
	s=to_string(x);
	n=s.size();
	for(int i=1;i<=n;i++)c[n-i+1]=s[i-1]-'0';
	return dfs(n,0,1,1);
}
```

首先，我们记搜的精髓就是记忆，这里用 $f_{p,r}$ 代表首位是 $r$，搜到第 $p$ 位（高往低）的答案。

当然，答案可能为 $0$，所以要初始化成 $-1$。

考虑一直用的边界需要限制，加入 $lmt$ 限制。

接着我们转移。

要是某一次数还是 $0$，$z$ 限制就会是 $1$，而当已经有数，枚举的 $i$ 超过了首位 $r$，状态不合法。

要是我们将 $0$ 给他转移到 $0$ 上，即 $z=1$ 且 $i=0$ 时，我们的 $r$ 将保留 $0$，$z$ 保留 $1$，$lmt$ 按照模版正常维护。

否则我们要判断第一次让数从 $0$ 变成 $i$ 的情况，如果是，那么 $r=i$，否则不变。

感觉转移还是浅显易懂。

然后是剩下的。

我们的求解函数应该把开头 $r$ 改成 $0$，其他跟板子一模一样。

最后放板子和此题来对比下。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=205;
int a,b,c[N],cur,n,f[N][N];
string s;
int dfs(int p,int r,bool z,bool lmt){
	if(p==0)return 1;
	if(!lmt&&f[p][r]>-1)return f[p][r];
	int ans=0,mx=(lmt?c[p]:9);
	for(int i=0;i<=mx;i++){
		if(!z&&abs(i-r)<2)continue;
		if(z&&i==0)ans+=dfs(p-1,i,1,lmt&&(i==mx));
		else ans+=dfs(p-1,i,0,lmt&&(i==mx));
	}
	if(!lmt&&!z)f[p][r]=ans;
	return ans;
}
int func(int x){
	memset(f,-1,sizeof(f));
	s=to_string(x);
	n=s.size();
	for(int i=1;i<=n;i++)c[n-i+1]=s[i-1]-'0';
	return dfs(n,-2,1,1);
}
signed main(){
	cin>>a>>b;
	cout<<func(b)-func(a-1);
	return 0;
}
```

这题：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=205;
int a,b,c[N],cur,n,f[N][N];
string s;
int dfs(int p,int r,bool z,bool lmt){
	if(p==0)return 1;
	if(!lmt&&f[p][r]>-1)return f[p][r];
	int ans=0,mx=(lmt?c[p]:9);
	for(int i=0;i<=mx;i++){
		if(!z&&i>=r&&r!=0)continue;
		if(z&&i==0)ans+=dfs(p-1,0,1,lmt&&(i==mx));
		else ans+=dfs(p-1,(r==0?i:r),0,lmt&&(i==mx));
	}
	if(!lmt&&!z)f[p][r]=ans;
	return ans;
}
int func(int x){
	memset(f,-1,sizeof(f));
	s=to_string(x);
	n=s.size();
	for(int i=1;i<=n;i++)c[n-i+1]=s[i-1]-'0';
	return dfs(n,0,1,1);
}
signed main(){
	cin>>a>>b;
	cout<<func(b)-func(a-1);
	return 0;
}
```

是不是很像？

---

## 作者：sjh0626 (赞：3)

## 题意概括
一个不小于 $10$ 的正整数，其十进制表示法的首位（最重要的一位）严格大于该数的其他各位，叫做蛇形数。例如， $31$ 和 $201$ 是蛇形数，但 $35$ 和 $202$ 不是。

求在 $L$ 和 $R$ 之间（包括首尾两个数）有多少个蛇形数。
## 思路分析
一开始以为数论，结果发现是数位动规，现场学了一下，过了。

别看是动态规划就被吓着了，其实数位动规就是记忆化搜索，我们会搜索一下三个内容：

- 当前还剩多少个数
- 首位数字
- 是否满了（就是当前数字到达上限了）

接下来套板子就过了，要注意一个坑点，开头不能为 $0$。

总结：这篇题解建议看着代码理解。
## 代码解析
```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
#define ll long long
#define int long long
using namespace std;
class FastIO{
	public:
	inline ll read(){
		ll x=0,f=1;char ch=getchar();
		while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
		while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
		return x*f;
	}
	FastIO &operator>>(ll &x){
		x=read();
		return *this;
	}
};
FastIO qin;
int l,r,dp[30][30];
vector<int>num;
int dfs(int pos,int pre,bool limit){ //板子 
	if(pos==0)return 1; 
	if(!limit&&dp[pos][pre]!=-1)return dp[pos][pre];
	int mx=(limit?num[pos-1]:9); //最大可以达到的数字
	int res=0;
	for(int i=0;i<=mx&&i<pre;i++){
		res+=dfs(pos-1,(pre==10&&i!=0?i:pre),limit&&i==mx);
	}
	if(!limit)dp[pos][pre]=res;
	return res;
}
int query(ll x){
	num.clear();
	while(x){
		num.push_back(x%10);
		x/=10;
	}
	return dfs(num.size(),10,1);
}
signed main(){
	qin>>l>>r;
	memset(dp,-1,sizeof(dp));
	cout<<query(r)-query(l-1);
	sjh0626s code;
}
```

---

## 作者：Ambrose0321 (赞：3)

C 题比 D 题还难。

题意简述：
---

我们把首位严格大于后面每一位的数字称作蛇皮数字，问 $l$ 到 $r$ 之间有多少个蛇皮数字。

思路：
---

求从 $l$ 到 $r$ 的蛇皮数字，也就是从 $1$ 到 $r$ 的蛇皮数字减从 $1$ 到 $l-1$ 的蛇皮数字。

有了这一步转化，我们只要用一个函数挨个计算就可以了，接下来我举一个例子来说怎么求蛇皮数，下面的首位都简称为 $k$。

例如，从 $1$ 到 $525$ 的蛇皮数字，我们只要求从 $1$ 到 $500$ 的开头数字就行，在乘法原理算出对应该开头的蛇皮数字就行。

接下来，还剩 $500$ 到 $525$ 这一段，我们可以先把 $525$ 转化为小于等于它最大的蛇皮数字，具体方法就是从第一位看到最后一位，一旦这一位 $\ge 5$ 就把后面的位全改成 $k-1$ 就行。

最后，把这个小于等于 $525$ 的最大蛇皮数字转化为 $k$ 进制就解决这道题啦！


AC code:
---

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef __int128 i128;
typedef set<int> si;
typedef map<int, int> mii;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int N = 500001, P = 998244353, INF = 2139062143;
int gcd(int A, int B) {return B ? gcd(B, A % B) : A;}
int lcm(int A, int B) {return A * B / gcd(A, B);}
// 上面的都可以不看
int c[19];
ll l, r, f[19];
ll Pow(int a, int b) {
	ll ans = 1;
	for (; b--; )
		ans *= a;
	return ans;
}
ll calc(ll x) {
	int n = 0;
	ll ans = 1, B = 1;
	bool b = 0;
	while (x)
		c[++n] = x % 10, x /= 10;
	reverse(c + 1, c + n + 1);
	for (int i = 1; i < c[1]; i++)
		ans += Pow(i, n - 1);
	for (int i = 2; i <= n; i++) {
		if (c[i] >= c[1])
			b = 1;
		if (b)
			c[i] = c[1] - 1;
	}
	for (int i = n; i > 1; --i)
		ans += c[i] * B, B *= c[1];
	return ans + f[n - 1];
}
int main() {
	for (int i = 1; i < 19; i++) {
		ll cnt = 0;
		for (int j = 1; j <= 9; j++)
			cnt += Pow(j, i - 1);
		f[i] = f[i - 1] + cnt;
	}
	scanf("%lld%lld", &l, &r);
	printf("%lld\n", calc(r) - calc(l - 1));
}
```
本蒟蒻的第三篇题解，不喜勿喷。希望过审 qwq。

---

## 作者：lhz2022 (赞：2)

考虑数位 dp 算法。

如果你不会数位 dp，那就把它当成一种记忆化搜索。

记在函数 $query(i)$ 表示区间 $[1,i]$ 中满足条件的数。

我们要求的答案即为 $query(r)-query(l-1)$。

那么可以使用记忆化。

设 $dp_{i,j}$ 表示现在是第 $i$ 位，当前的最高位是 $j$。

转移是显然的，细节就放注释里面了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int __int128
#define debug() puts("I WILL AK")
#define N 100007
int num[N],sz;
int dp[200][200];
inline int rd(){
	int ans=0,w=0;
	char ch=getchar();
	while (ch<'0'||ch>'9'){
		w|=ch=='-',ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	}
	return w?-ans:ans;
}
inline void wr(int x){
	if(x<0)
		putchar('-'),x=-x;
	if(x<=9){
		putchar(x+'0');
		return;
	}
	wr(x/10);
	putchar(x%10+'0');
}
void f(int x){
	sz=0;
	while(x){
		num[++sz]=x%10;
		x/=10;
	//	wr(num[sz]);
	}
	memset(dp,-1,sizeof(dp));//将数字转化为字符数组，以便考虑上界问题。
}
int dfs(int u,int pre,bool fl,bool start,int first){//当前位，上一位，是否之前所有位都取到了最大值，是否是第一个，数字的第一个字符是什么
	//printf("u:%d pre:%d fl:%d start:%d first:%d\n",u,pre,fl,start,first);
	if(!first&&start) first=pre;//如果这是第一个字符
	if(u>sz){//边界条件
		return 1;
	}
	if(!fl&&dp[u][first]!=-1) return dp[u][first];//记忆化
	int r;
	if(fl){
		r=num[sz-u+1];//如果前面都取到了最大值，那么这一位只能取到num[sz-u+1],无法取到9
	}
	else{
		r=9;
	}
	int kk=min(r,first==0?9ll:first-1);//这里是加上题面中的限制
	int ans=0;
	for(int i=0;i<=kk;++i){//这一位取的数
		ans+=dfs(u+1,i,(i==r)&&fl,start||(i>0),first);
	}
	if(!fl&&start) dp[u][first]=ans;//记忆化
	return ans;
}

int query(int x){
	f(x);
	return dfs(1,0,1,0,0);
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int a,b;
	a=rd(),b=rd();
	wr(query(b)-query(a-1));
	return 0;
}
```

---

## 作者：Yuexingfei_qwq (赞：1)

我见过最逆天的 C 题。出题人认真的吗。  
**声明**：此题解思路参照官方题解。
## 思路  
通过观察数据范围可以发现 $R - L$ 最大可以达到 $10^{18}$，暴力肯定不行。

设 $f(x)$ 表示从 $1$ 到 $x$ 里的蛇数个数，参考前缀和思想可以得出答案等价于 $f(R) - f(L - 1)$。  

接下来介绍 $f(x)$ 函数。

首先，将参数 $x$ 数位分解，存在 $v$ 里面，将 $v$ 翻转，使其高位在前。  
然后用 $i$ 遍历 $v$ 的第二位到最后一位的后一位，如果 $v_i \ge v_0$，说明 $x$ 不是蛇数，那么退出循环，否则答案加上这一位的贡献值。如果此时是 $v$ 最后一位的后一位还没有退出循环，说明 $x$ 本身也是个蛇数，答案就要加一。  
接着再遍历 $v$ 数组，对于每个位置，从 $1$ 开始循环，到 $s$ 结束，答案加上每个数字的贡献值。  
**上文中 $s$ 的定义**：如果现在遍历到的数位是第一个位置（即 $i = 0$），$s = v_i - 1$，否则 $s = 9$。

最后输出 $f(R) - f(L - 1)$ 即可。
## AC CODE

```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf ("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a * b / __gcd(a, b)
#define setp(x) fixed << setprecision(x)

using namespace std;

typedef long long ll;
typedef string str;
using ull = unsigned ll;

int l, r;
std::vector<int> v;

inline int p(int a, int n) {
	int v = 1;
	while (n--) {
		v *= a;
	}
	return v;
}

inline int f(int x) {
	v.clear();
	while (x) {
		v.push_back(x % 10);
		x /= 10;
	}
	reverse(v.begin(), v.end());
	int n = v.size(), ans = 0;
	F(i, 1, n, 1) {
		if (i == n) {
			ans++;
			break;
		}
		ans += p(v[0], n - i - 1) * std::min(v[0], v[i]);
		if (v[i] >= v[0]) {
			break;
		}
	}
	F(i, 0, n - 1, 1) {
		F(j, 1, (i ? 9 : v[0] - 1), 1) {
			ans += p(j, n - i - 1);
		}
	}
	return ans;
}

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	cin >> l >> r;
	cout << f(r) - f(l - 1) << el;
	r0;
}
```

[AC记录](https://atcoder.jp/contests/abc387/submissions/61401981)

---
完结~~不~~散花。

---

## 作者：HasNoName (赞：1)

### 思路
一道很板的数位动态规划。

考虑对于首位和非首位分类讨论。

对于非首位，记录下首位的数字 $k$，这一位 $i$ 的数字为 $a$，在分 $a\le k$ 和 $a>k$ 讨论，当 $a\le k$ 时，小于当前数的方案总数为 $a\times k^i$。如果 $a>k$ 则计算答案后直接返回。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
ll pw[11][20],f[20];
ll get(ll x)
{
	ll ans=0,t=1e9;
	for(int i=18;i>=0;i--)
	{
		ll g=x/pw[10][i]%10;
		if(pw[10][i+1]>x&&g)
		{
			t=g;
			for(int j=1;j<t;j++)
				ans+=pw[j][i];
			ans+=f[i];
			continue;
		}
		if(g)
		{
			if(g>=t)
			{
				ans+=pw[t][i+1];
				return ans;
			}
			else ans+=pw[t][i]*g;
		}
	}
	return ans+1;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	for(int i=1;i<=10;i++)pw[i][0]=1;
	for(int i=1;i<=19;i++)
		for(int j=1;j<=10;j++)
			pw[j][i]=pw[j][i-1]*j;//预处理 i^j
	for(int i=1;i<=19;i++)
	{
		f[i]=f[i-1];
		for(int j=1;j<=9;j++)
			f[i]+=pw[j][i-1];
	}
	ll l,r;
	cin>>l>>r;
	cout<<get(r)-get(l-1)<<'\n';
	return 0;
}
```

---

## 作者：Double_Light (赞：1)

首先可以把原问题拆解成 $[1,r]$ 中的 Snack Number 减去 $[1,l]$ 中的 Snack Number。

接下来考虑如何算出 $[1,x]$ 范围内 Snack Number 的数量。

考虑枚举在范围内的 Snack Number 的最高位。如果这个最高位 $k$ 小于 $x$ 的最高位，那么后面每一位都有 $k$ 种填法（$0\sim k-1$），乘法原理可以求得答案。

考虑 $k$ 等于 $x$ 的最高位时的情况，想到数位 DP。从高位往低位填数，从左数第二位开始填，设 $f_{i,0/1}$ 表示填完左数第 $i$ 位，前面的数字是否与 $x$ 的前 $i$ 位完全相同。然后记忆化搜索。

```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#define int long long
using namespace std;
int l,r;
int mi[25];
int a[25];
int dp[25][15][2];//这里第二维状态可以去掉
int n;
int ksm(int x,int y){//快速幂
	int ans=1;
	while(y){
		if(y%2==1)ans*=x;
		y>>=1;
		x*=x;
	}
	return ans;
}
int dfs(int x,int y/*can't >= */,int f){//填到第x位，f表示前面是否均与上界相同
	if(x==n)return dp[x][y][f]=1;//所有位都填完且合法，只有1种可行情况
	if(dp[x][y][f])return dp[x][y][f];//已经求出过答案
	int ans=0;
	for(int i=0;i<y;i++){
		if(f&&i>a[x])break;//前面都与上界相同，这一位更大了，即整体比上界更大
		if(f&&i==a[x]){
			ans+=dfs(x+1,y,f);
			continue;
		}
		ans+=dfs(x+1,y,0);
	}
	return dp[x][y][f]=ans;//记忆化
}
int solve(int x){
	int ans=0;
	if(x<10)return 0;
	n=0;
	int m=x;
	while(m){
		m/=10;n++;
	}
	m=x;
	for(int i=1;i<n;i++){//分离后n-1位数位（n为l或r的数位个数）
		a[n-i]=m%10;
		m/=10;
	}
	for(int i=2;i<=n;i++){
		for(int j=1;j<=9;j++){
			if(i==n&&j>=x/mi[i-1])continue;
			ans+=ksm(j,i-1);
		}
	}
	memset(dp,0,sizeof(dp));
	ans+=dfs(1,x/mi[n-1],1);
	return ans;
}
signed main(){
	mi[0]=1;
	for(int i=1;i<=20;i++)mi[i]=mi[i-1]*10;//预处理10的整数幂（快速幂也可以）
	cin>>l>>r;
	cout<<solve(r)-solve(l-1)<<endl;
	return 0;
}
```

---

## 作者：lucasincyber (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc387_c)
## 思路
数位统计题。我们可以先用前缀和思想，把问题转化为：求 $1$ 至 $r$ 的 Snake Number，再求 $1$ 至 $l - 1$ 的 Snake Number，最后再相减。

那我们可以分三种情况讨论，先假设当前这个区间为 $1$ 至 $x$，位数为 $|x|$：

1. 一个数位数 $size < |x|$ 时，此时当第一位 $= t$，剩下的位每一个都有 $t$ 种取法，所以方案数为 $t^{size-1}$。
2. 一个数位数 $= |x|$，但第一位 $t < x$ 的第一位时，剩下的位都有 $t$ 种取法，此时方案数为 $t^{|x| - 1}$。
3. 否则，我们就可以暴力 dfs，枚举每一位选什么，如果这样选后面的位数就没有影响了，那就同上求出方案数，否则继续递归。

最后将所有的方案数加起来，求解即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll l, r;

ll dfs(int u, int last, int sz, string s)
{
	if (u >= sz) return 0;
	if (u == sz - 1)
		return min(s[u] - '0' + 1, last);
	ll res = 0;
	for (int i = 0; i <= min(last - 1, s[u] - '0'); i++)
	{
		if (i == s[u] - '0') res += dfs(u + 1, last, sz, s);
		else
		{
			ll mul = 1;
			for (int j = u + 1; j < sz; j++)
				mul *= last;
			res += mul;
		}
	}
	return res;
}

ll solve(ll x)
{
	if (x < 10) return 0;
	string t = to_string(x);
	int sz = t.size();
	ll res = 0;
	for (int i = 2; i < sz; i++) // 长度 
	{
		for (int j = 1; j <= 9; j++) // 第一位是 i 
		{
			ll mul = 1;
			for (int k = 1; k < i; k++)
				mul *= j;
			res += mul;
		}
	}
	for (int i = 1; i < t[0] - '0'; i++) // 长度为 n 时，第一位是 i 
	{
		ll mul = 1;
		for (int j = 2; j <= sz; j++) // 剩下的位数
			mul *= i;
		res += mul;
	}
	res += dfs(1, t[0] - '0', sz, t);
	return res;
}

int main()
{
	scanf("%lld%lld", &l, &r);
	printf("%lld\n", solve(r) - solve(l - 1));
	return 0;
}
```

---

## 作者：zsq9 (赞：0)

[AC 记录](https://www.luogu.com.cn/record/197827651)

## 题目大意

不小于 $10$ 的正整数，其十进制表示中的最高位（最高有效位）严格大于该数中的每隔一位，称为 **蛇数**。例如，$31$ 和 $201$ 是蛇号，但 $35$ 和 $202$ 不是蛇号。

找出在 $L$ 和 $R$ 之间（含）存在多少个蛇号。

## 思路

看到很多人用数位动态规划，这题可以分开做，不用数位动态规划，我们首先可以把求 $l\sim r$ 的数变成求 $1 \sim r \Rightarrow 1 \sim l$ 的数。再分成三个部分，第一个部分就是 $1 \sim$ 离 $l$ 最近的整千 $-1$ 的数，然后第二个部分是，离 $l$ 最近的整千的数 $\sim$ 离 $r$ 最近的整千 $-1$ 的数，最后就是，离 $r$ 最近的整千的数 $\sim r$，这样就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
int l,r;
int opzc(int x){
	if(x<10)return 0;
	int fg=9,y,d=1,sum=0,ans=0,e=0;
	while(fg*10+9<x){
		fg=fg*10+9,d++;
		for(int i=1;i<=9;i++){
			sum=1;
			for(int j=1;j<d;j++)sum*=i;
			ans+=sum; 
		}
	}
	y=x/(++fg);
	for(int i=1;i<y;i++){
		sum=1;
		for(int j=1;j<=d;j++)sum*=i;
		ans+=sum;
	}
	sum=1,e=0;
	while(x>=10){
		if(x%10>y-1)sum=0;
		int opzc35=min(x%10,y);
		for(int i=1;i<=e;i++)opzc35*=y;
		x/=10,e++,sum+=opzc35;
	}
	return ans+sum;
}
signed main(){
ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>l>>r;
	cout<<opzc(r)-opzc(l-1);

return 0;
}
```

---

## 作者：cyq32ent (赞：0)

数位 DP。

状态设计 $f_{pos,mx,is_t,limited}$ 表示当前从前往后第 $pos$ 位，首位数字为 $mx$，$is_t$ 为之前位是否达到最大值，$limited$ 为当前是否有限制。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int mem[200][11][2][2],f[200][11][2][2];
string s;char g[100];
int dfs(int pos,int mx,int is_t,int limited){
	if(pos==s.length())return 1;
	if(mem[pos][mx][is_t][limited])return f[pos][mx][is_t][limited];
	int lim=is_t?(s[pos]-'0'):9,cnt=0;
	if(!limited){
		for(int i=1;i<=min(lim,mx);i++)cnt+=dfs(pos+1,i-1,is_t&&i==lim,1);
		cnt+=dfs(pos+1,9,0,0);
	}else{
		for(int i=0;i<=min(lim,mx);i++)
			cnt+=dfs(pos+1,mx,is_t&&i==lim,1);
	}
	
	mem[pos][mx][is_t][limited]=1;
	//cout<<pos<<" "<<mx<<' '<<is_t<<' '<<limited<<' '<<cnt<<endl;
	return f[pos][mx][is_t][limited]=cnt;
}
signed main(){
	int L,R,c;
	cin>>L>>R;
	L--;
	snprintf(g,sizeof g,"%lld",L);s=g;c=-dfs(0,9,1,0);
	memset(mem,0,sizeof mem);memset(f,0,sizeof f);memset(g,0,sizeof g);
	snprintf(g,sizeof g,"%lld",R);s=g;c+=dfs(0,9,1,0);
	cout<<c<<endl;
	return 0;
}
```

---

