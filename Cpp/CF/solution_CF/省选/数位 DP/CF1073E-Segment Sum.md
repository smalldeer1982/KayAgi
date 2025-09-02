# Segment Sum

## 题目描述

You are given two integers $ l $ and $ r $ ( $ l \le r $ ). Your task is to calculate the sum of numbers from $ l $ to $ r $ (including $ l $ and $ r $ ) such that each number contains at most $ k $ different digits, and print this sum modulo $ 998244353 $ .

For example, if $ k = 1 $ then you have to calculate all numbers from $ l $ to $ r $ such that each number is formed using only one digit. For $ l = 10, r = 50 $ the answer is $ 11 + 22 + 33 + 44 = 110 $ .

## 说明/提示

For the first example the answer is just the sum of numbers from $ l $ to $ r $ which equals to $ \frac{50 \cdot 51}{2} - \frac{9 \cdot 10}{2} = 1230 $ . This example also explained in the problem statement but for $ k = 1 $ .

For the second example the answer is just the sum of numbers from $ l $ to $ r $ which equals to $ \frac{2345 \cdot 2346}{2} = 2750685 $ .

For the third example the answer is $ 101 + 110 + 111 + 112 + 113 + 114 + 115 + 116 + 117 + 118 + 119 + 121 + 122 + 131 + 133 + 141 + 144 + 151 = 2189 $ .

## 样例 #1

### 输入

```
10 50 2
```

### 输出

```
1230
```

## 样例 #2

### 输入

```
1 2345 10
```

### 输出

```
2750685
```

## 样例 #3

### 输入

```
101 154 2
```

### 输出

```
2189
```

# 题解

## 作者：Mihari (赞：9)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF1073E)

# 题解

一道 ~~记忆化搜索~~ 用状压配合数位 $DP$ 的题。

首先将”求区间 $[l,r]$ 的和“转化为”求区间 $[1,i]$ 的和“，记 $[1,i]$ 的合法数字和为 $f(i)$，那么答案就是 $f(r)-f(l-1)$，这是数位 $DP$ 的经典操作，不作过多解释。

考虑 `dfs(pos,s,pz,rl)` 为填数到第 $pos$ 位（最低位保证 $pos=1$），数字出现情况为 $s$（二进制串），是否前导零，是否触及上界的状态，考虑 $f[pos][s][pz][rl]$ 为这个状态的合法后续数字的和，考虑怎么从 $f[pos-1]$ 处算出 $f[pos]$ 的值。

假设第 $pos$ 位填的是 $x$，那么其对答案的贡献应该为 $x\times 10^{pos-1}\times cnt$，其中 $cnt$ 是之后状态的合法数字的个数，但是如果我们只有 $f$ 似乎是无法同时记录这个 $cnt$ 的。

考虑多一个数组记录 $cnt$，设 $g[pos][s][pz][rl]$ 为状态 `dfs(pos,s,pz,rl)` 的合法后续的数字个数，那么 $g[pos]$ 很好从 $g[pos-1]$ 处转移，有
$$
g[pos][s][pz][rl]=\sum g[pos-1][s'][pz'][rl']
$$
~~似乎什么都没写~~ 其中，$s'$ 指数字出现的状态 $s$ 在 $x$ 填入后变成的新状态，$pz'$ 指 $x$ 在填入后是否仍然存在前导零，$rl'$ 指 $x$ 填入后是否仍然触及上界

而 $f[pos]$ 的转移和这个差不多，有
$$
f[pos][s][pz][rl]=\sum f[pos-1][s'][pz'][rl']+x\times 10^{pos-1}\times g[pos-1][s'][pz'][rl']
$$
对于临界状态 $f[0]$ 和 $g[0]$，显然有 $\forall f[0]=0$，对于 $g[0]$，记 $\text{bitcnt}(x)$ 为 $x$ 二进制下有多少个 $1$，如果 $\text{bitcnt}(s)\le k$，有 $g[0][s][pz][rl]=1$，否则有 $g[0][s][pz][rl]=0$.

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13460461.html
```



---

## 作者：Juanzhang (赞：5)

**思路**：

- 数位$dp$

考虑状压，$dp_{pos,mark}$表示考虑到第$pos$位，并且包含了$mark$的数码的数的总和。

注意考虑前导0的影响，以及每个数个数对答案的贡献。

``` cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int p = 998244353;
int k, a[20], pw[20];
struct pr {
	int tot, sum;
	pr() {}
	pr(int a, int b) : tot(a), sum(b) {}
	void clr() { tot = sum = 0; }
	bool chk() { return ~tot && ~sum; }
} dp[2][2][20][1 << 10];

void add(pr& a, pr b, int num, int pos) {
	a.tot = (a.tot + b.tot) % p;
	a.sum = (a.sum + 1ll * num * pw[pos] % p * b.tot % p + b.sum) % p;
}

pr dfs(bool lim, bool zero, int pos, int mark) {
	if (!pos) return pr(1, 0);
	pr& res = dp[lim][zero][pos][mark];
	if (res.chk()) return res;
	res.clr();
	for (int i = 0; i <= (lim ? a[pos] : 9); i++) {
		if (__builtin_popcount(zero && !i ? 0 : mark | 1 << i) <= k) {
			add(res, dfs(lim && i == a[pos], zero && !i, pos - 1, zero && !i ? 0 : mark | 1 << i), i, pos - 1);
		}
	}
	return res;
}

int calc(ll x) {
	int len = 0;
	memset(dp, -1, sizeof dp);
	while (x) a[++len] = x % 10, x /= 10;
	return dfs(1, 1, len, 0).sum;
}

int main() {
	pw[0] = 1;
	for (int i = 1; i < 19; i++) {
		pw[i] = 10ll * pw[i - 1] % p;
	}
	ll l, r;
	scanf("%lld %lld %d", &l, &r, &k);
	printf("%d", (calc(r) - calc(l - 1) + p) % p);
	return 0;
}
```

---

## 作者：45dinо (赞：4)

一个很棒的题目，看了题解才做出来。

对于这种连续区间问题，一般的套路是设 $solve(x)$ 为 $[1,x]$ 之间符合要求的数的和。

然后问题就转换成了一个比较明显的数位dp，重点是如何设计状态。

由于要小于 $x$，所以需要一个 $0/1$ 变量 $j$ 判断前面 $i$ 为是否已经分出胜负。

考虑到和多少个不同的数出现有关，所以使用状态压缩表示哪些出现过了。

设 $num_{i,j,l,k}$ 表示已经处理了最高 $i$ 位，是否分出胜负，是否有前导0，目前已经有 $k$ 出现过了时的总数。

同时还要设计 $sum_{i,j,l,k}$ 表示次数的和。

然后考虑转移。

枚举第 $i$ 位取哪些，然后根据 $j$ 判断是否可行。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int l,r,K,num[20][2][2][2000],sum[20][2][2][2000];
int solve(string s)
{
	memset(num,0,sizeof(num));
	memset(sum,0,sizeof(sum));
	num[0][0][0][0]=1;
	for(int i=0;i<s.size();i++)
		for(int j=0;j<2;j++)
			for(int l=0;l<2;l++)
				for(int k=0;k<(1<<10);k++)
					if(num[i][j][l][k])
					{
						int nn=num[i][j][l][k];
						int ss=sum[i][j][l][k];
						int lim=(j?9:s[i]-'0');
						for(int t=0;t<=lim;t++)
						{
							int c=k;
							if(l||t)
								c|=(1<<t);
							(num[i+1][j||(t<lim)][l||t][c]+=nn)%=mod;
							(sum[i+1][j||(t<lim)][l||t][c]+=ss*10%mod+t*nn%mod)%=mod;
						}
					}
	int ans=0;
		for(int j=0;j<2;j++)
			for(int l=0;l<2;l++)
				for(int k=0;k<(1<<10);k++)
					if(__builtin_popcount(k)<=K)
						(ans+=sum[s.size()][j][l][k])%=mod;
	return ans;
}
signed main()
{
	scanf("%lld %lld %lld",&l,&r,&K);
	cout<<(solve(to_string(r))+mod-solve(to_string(l-1)))%mod;
	return 0; 
}
```


---

## 作者：tzc_wk (赞：3)

> Codeforces 1073E

> 题意：求 $[l,r]$ 之间包含不超过 $k$ 个不同数码的数的和。

> $1 \leq l,r \lt 10^{18}$，$1 \leq k \leq 10$

首先，看到问题要求 $[l,r]$ 之间满足一种条件的数的和，可以想到数位 $dp$。再看到 $k$ 的数据范围只有 $10$ 可以想到状压 $dp$。

我们设 $calc(i)$ 表示 $[1,i]$ 中满足条件的数的个数。那么原问题的答案就可以变成 $calc(r)-calc(l-1)$

关键是怎么求 $calc(x)$ 的值。我们将 $x$ 一位一位拆开，$a[0]$ 表示最低位，$a[cnt-1]$ 表示最高位。

然后我们从高到低进行数位 $dp$。我们记 $f[i][j]$ 表示枚举到第 $i$ 位，出现的数的集合为 $j$ 的情况下，所有数的**和**，记 $g[i][j]$ 表示在前 $i$ 位里面，出现的数的集合为 $j$ 的情况下，数的**个数**。

考虑转移。我们枚举第 $i$ 为上填的数 $t$，假设填完 $t$ 以后出现的数的集合为 $j'$，那么

- $f[i][j]=\sum\ (10^i \times t \times g[i-1][j']+f[i-1][j'])$

- $g[i][j]=\sum\ g[i-1][j']$

边界条件：

- $f[-1][j]=0$，$g[-1][j]=1$ $\ \ \ (cnt(j) \leq k)$

- $f[-1][j]=0$，$g[-1][j]=0$ $\ \ \ (cnt(j) > k)$

那么 $calc(i)=f[cnt-1][0]$

注意事项：注意前导 $0$ 不能被统计进状态中。

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
const int MOD=998244353;
int l=read(),r=read(),k=read();
int a[20],cnt,P[20];
pii dp[20][1024];
inline pii dfs(int pos,int sta,bool lead,bool limit){
	if(!~pos)	return pii(__builtin_popcount(sta)<=k,0);
	if(!lead&&!limit&&~dp[pos][sta].fi)	return dp[pos][sta];
	int up=(limit)?a[pos]:9;
	pii ans=pii(0,0);
	for(int i=0;i<=up;i++){
		int nsta=(lead&&i==0)?sta:(sta|(1<<i));
		pii nxt=dfs(pos-1,nsta,(lead&&i==0),(limit&&i==up));
		ans=pii((ans.fi+nxt.fi)%MOD,(nxt.fi*P[pos]%MOD*i%MOD+nxt.se+ans.se)%MOD);
	}
//	cout<<pos<<" "<<sta<<" "<<ans.fi<<" "<<ans.se<<endl;
	if(!limit&&!lead)	dp[pos][sta]=ans;
	return ans;
}
inline int solve(int x){
	fill0(a);cnt=0;
	while(x){
		a[cnt++]=x%10;x/=10;
	}
	fz(i,0,18)	fz(j,0,1023)	dp[i][j].fi=dp[i][j].se=-1;
	return dfs(cnt-1,0,1,1).se;
}
signed main(){
	P[0]=1;fz(i,1,18)	P[i]=P[i-1]*10%MOD;
	cout<<(solve(r)-solve(l-1)+MOD)%MOD<<endl;
	return 0;
}
```

---

## 作者：GK0328 (赞：3)

居然没看题解干掉了一道这么难的**数位DP**，好开森啊~~（大佬莫鄙视，毕竟我是蒟蒻）~~。

# 状态：

dp[i][j][k][l][o]表示当前取到第i位，取到的数字集合为j（即状压），有k个不同的数字（其实没用，包含在j里了，但是为了方便，多定义一维），l表示是否有前导0（见注①），o表示当前数字是否可以任意取（数位DP常规操作，这里也定义在状态里了，true表示可以任意取）的数的和。

c[i][j][k][l][o]状态与dp数组相同，只不过表示的是方案数而不是数的和。

注：

①这道题需要判前导0，前导0不算在数字中，我用了一个zero来记录当前数字是否还在前导0部分，如果在前导0部分，zero为false。

# 转移：

两大种情况：

[1]当前还在前导0部分，即zero=false

[2]当前不在前导0部分，即zero=true

## [1]分为两种情况：

### ①当前数字仍为0：

```cpp
dfs(w-1,s,id,false,f or (i<>q[w]));
```

zero仍为false

### ②当前数字不为0

```cpp
dfs(w-1,1 << i,1,true,f or (i<>q[w]));
```

zero变成true，状态变为1 << i，同时出现了一个数

## [2]也是两种情况：

### ①当前加入的数字已经在原数中了：

```cpp
dfs(w-1,s,id,zero,f or (i<>q[w]));
```

s,id都不更新，因为已经存在了。

### ②当前加入的数字不在原数中：

```cpp
dfs(w-1,s or (1 << i),id+1,zero,f or (i<>q[w]));
```

同样，运用状压的思想。

统计答案不是简单的加起来，而且要加上这一位的贡献，即下一种转移有多少种情况当前数位所表达的值，以[1]②为例：

```cpp
res:=(res+ten[w]*i mod p*c[w-1][1 << i][1][true][f or (i<>q[w])] mod p+dp[w-1][1 << i][1][true][f or (i<>q[w])]) mod p;
```

ten[w]*i即当前数位所表达的值。

因为下一种转移有c[w-1][1 << i][1][true][f or (i<>q[w])]种情况，所以要乘以c[w-1][1 << i][1][true][f or (i<>q[w])]次，可以想象，这些值与dp[w-1][1 << i][1][true][f or (i<>q[w])]结合起来便组成了所有数。

c数组不断累计更新。

细节不再多说,~~我数组开小了调了1hQAQ~~。

Pascal Code：

```cpp
const
  p:int64=998244353;
var
  c:array[0..20,0..1024,0..10,false..true,false..true]of int64;
  dp:array[0..20,0..1024,0..10,false..true,false..true]of int64;
  ten:array[0..55]of int64;
  q:array[0..55]of longint;
  top,k,i:longint;
  ans,l,r:int64;
procedure dfs(w,s,id:longint; zero,f:boolean);//记忆化搜索
var
  i,sl:longint;
  res:int64;
begin
  if id>k then//不满足题目要求，退出
  begin
    c[w][s][id][zero][f]:=0;
    dp[w][s][id][zero][f]:=0;
    exit;
  end;
  if w=0 then//到底了
  begin
    c[w][s][id][zero][f]:=1;
    dp[w][s][id][zero][f]:=0;
    exit;
  end;
  if dp[w][s][id][zero][f]<>-1 then//已经处理过了
    exit;
  if f then//不能超过原数
    sl:=9 else
    sl:=q[w];
  c[w][s][id][zero][f]:=0;
  res:=0;
  for i:=0 to sl do//注意不断取模，否则WA飞。。。
  begin
    if not zero then
    begin
      if i=0 then
      begin
        dfs(w-1,s,id,false,f or (i<>q[w]));
        res:=(res+dp[w-1][s][id][false][f or (i<>q[w])]) mod p;
        c[w][s][id][zero][f]:=(c[w][s][id][zero][f]+c[w-1][s][id][false][f or (i<>q[w])]) mod p;
      end else
      begin
        dfs(w-1,1 << i,1,true,f or (i<>q[w]));
        res:=(res+ten[w]*i mod p*c[w-1][1 << i][1][true][f or (i<>q[w])]+dp[w-1][1 << i][1][true][f or (i<>q[w])]) mod p;
        c[w][s][id][zero][f]:=(c[w][s][id][zero][f]+c[w-1][1 << i][1][true][f or (i<>q[w])]) mod p;
      end;
    end else
    begin
      if s and (1 << i)<>0 then
      begin	    
        dfs(w-1,s,id,zero,f or (i<>q[w]));
        res:=(res+ten[w]*i mod p*c[w-1][s][id][zero][f or (i<>q[w])]+dp[w-1][s][id][zero][f or (i<>q[w])]) mod p;
        c[w][s][id][zero][f]:=(c[w][s][id][zero][f]+c[w-1][s][id][zero][f or (i<>q[w])]) mod p;
      end else
      begin
        dfs(w-1,s or (1 << i),id+1,zero,f or (i<>q[w]));
        res:=(res+ten[w]*i mod p*c[w-1][s or (1 << i)][id+1][zero][f or (i<>q[w])]+dp[w-1][s or (1 << i)][id+1][zero][f or (i<>q[w])]) mod p;
        c[w][s][id][zero][f]:=(c[w][s][id][zero][f]+c[w-1][s or (1 << i)][id+1][zero][f or (i<>q[w])]) mod p;
      end;
    end;
  end;
  dp[w][s][id][zero][f]:=res;
end;
function check(x:int64):int64;
var
  i,j,k:longint;
  l,o:boolean;
begin
  if x=0 then
    exit(0);
  top:=0;
  while x<>0 do
  begin
    inc(top);
    q[top]:=x mod 10;
    x:=x div 10;
  end;
  for i:=0 to 20 do//初始化
    for j:=0 to 1024 do
      for k:=0 to 10 do
        for l:=false to true do
          for o:=false to true do
          begin
            dp[i][j][k][l][o]:=-1;
            c[i][j][k][l][o]:=0;
          end;
  dfs(top,0,0,false,false);
  exit(dp[top][0][0][false][false]);
end;
begin
  readln(l,r,k);
  ten[1]:=1;
  for i:=2 to 20 do
    ten[i]:=ten[i-1]*10 mod p;//预处理10的幂次
  ans:=check(r)-check(l-1);
  ans:=(ans mod p+p) mod p;//可能减出来是负的
  writeln(ans);
end.
```

最后再推荐两道CF的数位DP：

[CF628D Magic Numbers](https://www.luogu.org/problemnew/show/CF628D)

[CF55D Beautiful numbers](https://www.luogu.org/problemnew/show/CF55D)

---

