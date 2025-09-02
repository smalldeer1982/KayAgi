# [ABC301D] Bitmask

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc301/tasks/abc301_d

`0`, `1`, `?` からなる文字列 $ S $ および整数 $ N $ が与えられます。 $ S $ に含まれる `?` をそれぞれ `0` または `1` に置き換えて $ 2 $ 進整数とみなしたときに得られる値の集合を $ T $ とします。 たとえば、$ S= $ `?0?` のとき、 $ T=\lbrace\ 000_{(2)},001_{(2)},100_{(2)},101_{(2)}\rbrace=\lbrace\ 0,1,4,5\rbrace $ です。

$ T $ に含まれる $ N $ 以下の値のうち最大のものを ($ 10 $ 進整数として) 出力してください。 $ N $ 以下の値が $ T $ に含まれない場合は、代わりに `-1` を出力してください。

## 说明/提示

### 制約

- $ S $ は `0`, `1`, `?` からなる文字列
- $ S $ の長さは $ 1 $ 以上 $ 60 $ 以下
- $ 1\leq\ N\ \leq\ 10^{18} $
- $ N $ は整数

### Sample Explanation 1

問題文中で例示したとおり、$ T=\lbrace\ 0,1,4,5\rbrace $ です。 $ T $ に含まれる $ N $ 以下の値は $ 0 $ と $ 1 $ なので、そのうちの最大である $ 1 $ を出力します。

### Sample Explanation 2

$ T=\lbrace\ 5\rbrace $ であるため、$ N $ 以下の値は $ T $ に含まれません。

## 样例 #1

### 输入

```
?0?
2```

### 输出

```
1```

## 样例 #2

### 输入

```
101
4```

### 输出

```
-1```

## 样例 #3

### 输入

```
?0?
1000000000000000000```

### 输出

```
5```

# 题解

## 作者：Coffee_zzz (赞：5)

### 分析

首先可以预处理出每一个二进制位转化成十进制后对应的值。

考虑什么情况下无解。当我们将所有 `?` 都看成 `0` 后，$S$ 还大于 $N$ 时显然无解，因为此时的 $S$ 已经是最小的了。

接着考虑怎么找最大值。我们把将所有 `?` 都看成 `0` 后的 $S$ 设为 $num$，然后从高位到低位依次枚举为 `?` 的位，检查将这位看成 `1` 后，变化后的 $num$ 是否小于等于 $N$，若变化后的 $num\le N$ 则将这位看成 `1` 并更新 $num$。

在枚举完毕所有为 `?` 的位后，$num$ 就是满足条件的最大数了，输出 $num$ 即可。

### 代码

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read(){
		reg char ch=gh();
		reg long long x=0;
		reg char t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
}
using IO::read;
string s;
int n,con[65];
signed main(){
	int num=0,cnt=1;
	cin>>s>>n;
	for(int i=s.size()-1;i>=0;i--) con[i]=cnt,cnt*=2;
	for(int i=0;i<s.size();i++)if(s[i]=='1') num=num+con[i];
	if(num>n) puts("-1"),exit(0);
	for(int i=0;i<s.size();i++) if(s[i]=='?') if(num+con[i]<=n) num=num+con[i];
	cout<<num<<endl;
	return 0;
}
```

---

## 作者：没见过AC (赞：2)

贪心简单题。

在小于等于 $N$ 的情况下使变出来的数最大。


先把非 "?" 位的值算出来，然后从高位到低位依次在不超过 $N$ 的情况下贪心取 $1$ 。 

判 $-1$ 只需要在算非"?"位的值时就超过 $N$ 直接输出 $-1$ 就好了。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10000;
typedef long long ll;
int read()
{
    int n=0,x=1;char ch=getchar();
    if(ch=='-') x=-1;
    while(ch<'0'||'9'<ch)ch=getchar();
    while(ch>='0'&&ch<='9'){n=n*10+ch-'0';ch=getchar();}
    return n*x;
}
ll m,n,x,e[N],ans=0;
string s;
int main()
{
    cin>>s;
    cin>>n;
    x=n;
	for(int i=s.size()-1;i>=0;i--)
	{
		if(s[s.size()-i-1]!='?')
			ans+=(long long)(s[s.size()-i-1]-'0')*(long long)pow(2,i);
	}
	if(ans>n)
	{
		cout<<-1;
		return 0;
	}
	for(int i=s.size()-1;i>=0;i--)
	{
		if(s[s.size()-i-1]=='?')
		{
			if(ans+(long long)pow(2,i)<=n)
			{
				ans+=(long long)pow(2,i);
			}
		}
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：_Ad_Astra_ (赞：2)

考虑贪心，在高位上的一个 `1` 一定优于后面的任何情况，因此从高位往低位选择一定是最优的。对于每一个问号，如果这一位为 `1`，后面所有的问号都为 `0`（即后面尽可能最小化）时，这个数小于 $n$，那么这一位就可以为 `1`，否则只能为 `0`。

时间复杂度 $O(\log^2n)$。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
string s;
int n;
signed main()
{
	cin>>s>>n;
	reverse(s.begin(),s.end());
	int x=0;
	for(int i=0;i<s.size();i++)
		if(s[i]=='1')
			x|=(1LL<<i);
	if(x>n)
	{
		cout<<-1;
		return 0;
	}
	x=0;
	for(int i=s.size()-1;i>=0;i--)
	{
		if(s[i]!='?')
		{
			x|=(s[i]-'0')*(1LL<<i);
			continue;
		}
		int t=x|(1LL<<i);
		for(int j=i-1;j>=0;j--)
			if(s[j]=='1')
				t|=(1LL<<j);
		if(t<=n)x|=(1LL<<i);
	}
	cout<<x;
	return 0;
}
```

---

## 作者：tbdsh (赞：1)

# 题意简述
[题目传送门](/problem/at_abc301_d)

[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-at-abc301-d)

给定整数 $N$ 和只包含字符 `0`、`1`、`?` 的字符串 $S(1\le |S|\le 60)$。

将 $S$ 视为一个二进制数，令 $T$ 为将 $S$ 中的 `?` 替换为 `0` 或 `1` 后所能得到的数字集合。请求出 $T$ 中小于等于 $N$ 的最大数字，并以十进制方式输出。

如果 $T$ 中不包含小于等于 $N$ 的数字，输出 `-1`。

# 分析
## 初步完成代码
考虑到 $1\le |S|\le 60$，所以我们考虑使用搜索。

我们可以对这个二进制数从高位到到低位进行搜索。在搜索时顺便转十进制。

如果 $S_i=\text{1}$ 或 $S_i=\text{0}$，那么直接转十进制然后进行下一位的搜索。如果 $S_i=\text{?}$，那么把搜索两种情况：$S_i=\text{1}$ 和 $S_i=\text{0}$。

那么，我们就有了如下代码：
```cpp
long long ans = -1;
void dfs(int x, long long op, long long cnt){
  if (x == len + 1){
    if (cnt <= n){
      ans = max(ans, cnt);
    }
    return ;
  }
  if (s[x] == '?'){
    dfs(x + 1, op / 2, cnt + op);
    dfs(x + 1, op / 2, cnt);
  }else {
    dfs(x + 1, op / 2, cnt + op * (s[x] - '0'));
  }
}

cout << ans;
```
## 优化
提交后，有很多 [`TLE`](https://atcoder.jp/contests/abc301/submissions/41459761)。所以考虑优化。

我们很容易发现：如果当前得到的数 $cnt$ 已经大于 $n$，我们就可以直接退出搜索。因为之后不可能再得到答案。

而又因为我们是从高位开始搜索，那么搜索到的第一个数就是我们要求的答案，即小于等于 $n$ 的最大值。

在搜到答案后，我们可以直接用 `exit(0)` 结束程序。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
string s;
long long n, len;
void dfs(int x, long long op, long long cnt){
  if (cnt > n){
    return ;
  }
  if (x == len + 1){
    cout << cnt;
    exit(0);
  }
  if (s[x] == '?'){
    dfs(x + 1, op / 2, cnt + op);
    dfs(x + 1, op / 2, cnt);
  }else {
    dfs(x + 1, op / 2, cnt + op * (s[x] - '0'));
  }
}
int main(){
  cin >> s >> n;
  len = s.size();
  s = ' ' + s;
  dfs(1, pow(2, len - 1), 0);
  cout << -1;
  return 0;
}
```


---

## 作者：ReeChee (赞：1)

## Problem
给出一个仅含 `0`、`1` 和 `?` 的字符串 $S$ 和一个正整数 $N$，其中 $S$ 表示一个二进制数，`?` 可由 `0` 或 `1` 替代，求出最大的 $S$ 可表示出的数 $T$ 满足 $T\leq N$，若不存在则输出 $-1$。

$1\leq \mathrm{len}(S)\leq 60$，$1\leq N\leq 10^{18}$

## Solution

预先把所有为 `1` 的位先填充上，`?` 都填充为 `0`，若此时就已经比 $N$ 大则不存在 $T$ 满足题目要求，反之则从最高位枚举 $S$ 的每位，若填充该位依旧满足条件则直接填充 `1`，反之填充 `0`（直接从最高位填充一定比从最低位开始填充的数字要大，比如 $(1000)_2 > (0111)_2$），最后输出答案即可。

时间复杂度 $\mathcal{O}(\mathrm{len}(S))$。

## Code

```cpp
inline int FillOne(){
    int cur=0;
    F(i,0,(signed)s.size()-1){
        if (s[i]=='1')
            cur|=1ll<<i;
    }
    return cur;
}
signed main(){
    cin>>s;
    n=read();
    reverse(s.begin(),s.end());
    ans=FillOne(); // 将所有为 1 的位预先填充为 1，之后在预先填充完的数的基础上枚举每位
    if (ans>n) puts("-1"),exit(0);
    FJ(i,(signed)s.size()-1,0)
        if (s[i]=='?')
            if ((ans|(1ll<<i))<=n) // 若填充为 1 后依旧满足条件
                ans|=(1ll<<i); // 填充该位为 1
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：DengDuck (赞：1)

考虑在保证这个数字小于等于 $N$ 的情况下贪心使其最大化。

正确性显然，因为如果可以，我们总是希望最高位的 `?` 为 $1$，其作用最大。

我们预处理出 $f_i$ 表示 $i$ 往后的几位的最小值，也就是所有 `?` 都填 `0`。

然后我们从高位到低位，如果填 $1$ 后面填最小值仍小于 $N$，则合法，我们填 $1$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
string a;
LL n,len,ans,pw[1005],f[1005],flg;
int main()
{
	pw[0]=1;
	for(int i=1;i<=63;i++)pw[i]=2*pw[i-1];
	cin>>a>>n;
	len=a.size();
	for(int i=len-1;i>=0;i--)
	{
		if(a[i]=='1')f[i]+=pw[len-i-1];
		f[i]+=f[i+1];
	}
	for(int i=0;i<len;i++)
	{
		if(a[i]=='?')
		{
			if(ans+pw[len-i-1]+f[i]<=n)ans+=pw[len-i-1]; 		
		}
		if(a[i]=='1')ans+=pw[len-i-1];
	}
	if(ans>n)
	{
		puts("-1");
		return 0;
	}
	cout<<ans<<endl;
}
	
```

---

## 作者：kkxacj (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc301_d)

#### 题目大意

给定整数 $N(1\le N\le 10^{18})$ 和只包含字符 `0`、`1`、`?` 的字符串 $S(1\le |S|\le 60)$。

将 $S$ 视为一个二进制数，令 $T$ 为将 $S$ 中的 `?` 替换为 `0` 或 `1` 后所能得到的数字集合。请求出 $T$ 中小于等于 $N$ 的最大数字，转化成十进制输出。

如果 $T$ 中不包含小于等于 $N$ 的数字，输出 `-1`。

#### 思路

读题可知，这道题要我们构造出尽可能大但又要小于 $n$ 的数，由于我们只能改变 $S$ 中的 `?`，所以我们应改先扫一遍 $S$ 中原本含有的 `1`，之后在来修改 $S$ 中的 `?`，由于要求出的数尽可能大，所以从最高位往最低位扫。

[不知道如何将二进制转化为十进制由此去](https://so.csdn.net/so/search?spm=1000.2115.3001.4498&q=%E4%BA%8C%E8%BF%9B%E5%88%B6%E8%BD%AC%E5%8D%81%E8%BF%9B%E5%88%B6&t=&u=)

code

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
long long o = 1,n,l,oo;
int main()
{
	cin >> s >> n;
	oo = s.size() - 1;
	while(oo) //求出2的(s.size - 1)次方 
	{
		o *= 2;
		oo--;
	}
	for(int i = 0;i < s.size();i++)//这里的0是第n位，1是第n - 1位... 
	{
		if(s[i] == '1') l += o; //如果第w位为1，那么转化为十进制就是加上2的w次方 
		o /= 2;
	}
	o = 1;
	oo = s.size() - 1;
	while(oo) //求出2的(s.size - 1)次方
	{
		o *= 2;
		oo--;
	}
	for(int i = 0;i < s.size();i++)
	{
		if(s[i] == '?' && l + o <= n) l += o;//如果当前为？且加上还小于等于n 
		o /= 2;
	}
	if(l <= n) cout << l; 
	else cout << -1;
    return 0;
}


```


---

## 作者：Yashajin_Ai (赞：0)

### 思路
开始看见数据不算大，考虑大模拟，一种情况一种情况试一试，可以码到一半，想到贪心，读题可知，这道题要我们构造出尽可能大但又要小于 $n$ 的数，由于我们只能改变 $S$ 中的 ```?```，所以我们应改先扫一遍 $S$ 中原本含有的 $1$，并且同时将 $S$ 中的 ```?``` 如果为 $1$ 时，当前值是多少，由于要求出的数尽可能大，所以从最高位往最低位扫，看最多能加上多少，大于 $n$ 就输出，当然如果最小情况就大于 $n$ 了，就输出 $-1$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string s;
ll n,ans[61],a=1,res;
int main(){
	cin>>s>>n;
	for(ll i=s.size()-1;i>=0;i--,a*=2){
		if(s[i]=='?')ans[i]=a;
		if(s[i]=='1')res+=a;
	}
	for(ll i=0;i<s.size();i++) if(res+ans[i]<=n)res+=ans[i];
	if(res>n)cout<<-1;
	else cout<<res;
}
```

---

## 作者：DHeasy (赞：0)

[本文章同步发表于博客园](https://www.cnblogs.com/fengxiaoyi/p/17407040.html)

### 思路

算法：贪心。

我们可以将 $s$ 想象成一个二进制数，每一位都有它对应的权值。

我们将 $N$ 依次减去已经确定的位的权值，如果减完后 $N\lt0$，则 `?` 即使都填 `0`，值也大于 $N$，输出 `-1` 即可。

接下来，我们就贪心的从第一位（二进制数下的最高位）开始枚举，如果当前位置为 `?`，那么：

- 如果将当前位置改为 `1`，最后的值仍然小于等于 $N$，则贪心的这个位置改为 `1`。

- 否则，改为 `0`。

最后，将 $s$ 转化成 $10$ 进制数，输出即可。

#### 贪心的正确性证明

> 如果将当前位置改为 `1`，最后的值仍然小于等于 $N$，则贪心的这个位置改为 `1`。

反证法，如果当前位置不选 `1`，那么由于在二进制下，第一个为值不同时，值为 $1$ 的一定最大，则后面不管怎么选，都不是最大的答案。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,now,ans;
char s[100];
int si; 
int main(){
	scanf("%s",s+1);
	scanf("%lld",&n);
	si=strlen(s+1);
	now=1ll<<(si-1);
	for(int i=1;i<=si&&n>=0;i++){
		if(s[i]=='1') n-=now;
		now>>=1;
	}
	if(n<0) return !printf("-1");
	now=1ll<<(si-1);
	for(int i=1;i<=si;i++){
		if(s[i]=='?'){
			if(now<=n) s[i]='1',n-=now;
			else s[i]='0';
		}
		now>>=1;
	}
	for(int i=1;i<=si;i++) ans=(ans<<1ll)+1ll*s[i]-'0';
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc301_d)      
一道很优质的贪心 & 位运算题。       
易知无解情况是所有 `?` 都为 `0` 时仍比 $n$ 大。    
我们的贪心策略很简单，尽量替换在高位的 `?` 为 `1`。            
我们**从高位往低位**扫一遍，如果这一位可以替换成 `1`，就替换，否则不替换。       
最后求值即可。        
[CODE](https://www.luogu.com.cn/paste/827gp8pb)

---

## 作者：hellolin (赞：0)

## AtCoder Beginner Contest 301 - D - Bitmask

[洛谷题面](https://www.luogu.com.cn/problem/AT_abc301_d) | [AtCoder 题面](https://atcoder.jp/contests/abc301/tasks/abc301_d) | [AC 记录](https://www.luogu.com.cn/record/110510447) | $\texttt{\color{73f273}*885}$

$\log(10^{18})\approx 60$，纯纯的贪心。

考虑将 $N$ 转换为二进制表示的形式，那么只需要与 $S$ 进行比较，尽可能往大填就行了。

这种方法虽然可行但代码实现太长了。其实还可以继续简化：

先将 $S$ 中的 `?` 当做 `0` 计算，算出 $S$ 的十进制表示 $T'$。

``` cpp
#define int long long
reverse(s.begin(),s.end());
int t=0;
for(int i=0;i<s.length();i++)
    if(s[i]=='1')
        t+=1ll<<i; // 注意 long long
```


若 $T'>N$ 直接 `-1`，否则，在 $T'\le N$ 的情况下，将 $S$ 中 `?` 填成 `1` 即可。由于只让求 $T$ 的值，所以不必更新 $S$ 了。

``` cpp
if(t>n){
    cout<<-1<<endl;
    return;
}
for(int i=s.length()-1;i>=0;i--) // 优先填大的
    if(s[i]=='?')
        if(t+(1ll<<i)<=n)
            t+=1ll<<i;
```

完整代码如下：

``` cpp
// 珍爱账号，请勿贺题
#include <bits/stdc++.h>
using namespace std;
#define int long long

string s;
int n,t;
void solve(){
    cin>>s>>n;

    reverse(s.begin(),s.end());
    for(int i=0;i<s.length();i++)
        if(s[i]=='1')
            t+=1ll<<i;
    
    if(t>n){
        cout<<-1<<endl;
        return;
    }
    for(int i=s.length()-1;i>=0;i--)
        if(s[i]=='?')
            if(t+(1ll<<i)<=n)
                t+=1ll<<i;

    cout<<t<<endl;
}

int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}
```


---

## 作者：Loser_Syx (赞：0)

一道有思维难度的贪心题。

## 思路

首先看到题目，它要求要转二进制，但同时也有 `?`，表示这个里面你可以填 `0` 或 `1`，随你怎么填。

由于这是二进制数，我们可以先把每一位的权值计算出来，方便之后计算。

接下来考虑贪心策略。

先假设每一个 `?` 都是 `0`，计算出权值，这是最小的得数。

如果计算出的 $> n$，那么没戏了，输出 $-1$。

接下来我们依次从高位开始，如果它这一位是 `?` **且**加上之后总和还是 $\leq n$ 的，那么我们一定加上。

最后输出得数即可。

注意 `long long` 问题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long Pow[1010];
long long n;
int main(){
	string s;
	cin >> s >> n;
	int len = s.length();
	long long p = 1;
	for(int i = len-1; i >= 0; --i){
		Pow[i] = p;
		p *= 2;
	}
	long long ans = 0;
	for(int i = 0; i < len; ++i){
		if(s[i] == '1'){
			ans += Pow[i];
		}
	}
	if(ans > n) return puts("-1"), 0;
	for(int i = 0; i < len; ++i){
		if(s[i] == '?' && ans + Pow[i] <= n){
			ans += Pow[i];
		}
	}
	cout << ans;
	return 0;
}
```

---

