# (∀x∀)

## 题目描述

给定一个长度为 $N$ 的只包含大写字母的字符串 $S$，你需要计算出所有长度仍为 $N$ 的字符串 $X$ 的个数，要求其必须满足：
* $X$ 也只包含大写字母 $S$。
* $X$ 是一个回文字符串。
* $X$ 按字典序小于等于 $S$。

答案对 $998244353$ 取模。你需要回答 $T$ 组询问。

## 说明/提示

### 数据规模与约定
* $1\le T\le 250000$
* $1\le N\le 10^6$
* **每个测试点的所有 $N$ 之和不超过 $10^6$。**
* $S$ 是一个只包含大写字母的长度为 $N$ 的字符串。
### 样例解释 1
这个测试点包含 $5$ 组测试数据。

第 $1$ 组：满足条件的 $24$ 个字符串 $X$ 分别为：`AAA`,`ABA`,……,`AXA`。

第 $2$ 组：注意 $S$ 不一定是一个回文串。

第 $3$ 组：注意确保答案对 $998244353$ 取模。

Translate by @[Ascnbeta](https://www.luogu.com.cn/user/767561).

## 样例 #1

### 输入

```
5
3
AXA
6
ABCZAZ
30
QWERTYUIOPASDFGHJKLZXCVBNMQWER
28
JVIISNEOXHSNEAAENSHXOENSIIVJ
31
KVOHEEMSOZZASHENDIGOJRTJVMVSDWW```

### 输出

```
24
29
212370247
36523399
231364016```

# 题解

## 作者：XYQ_102 (赞：2)

这道题直接枚举判断回文串不太好做而且会超时。

我们可以从回文串入手，在 $S$ 的基础上将前一般的子串翻转构造出一个回文串，这个回文串可能比 $S$ 大，也可能比 $S$ 小。

比如：$S=$`ABCZAZ`，那么我们第一步得到的回文串 `ABCCBA` 是比 $S$ 字典序小的，那么这个回文串 `ABCCBA` 就是答案之一而且是字典序最大的。

由于回文串是由前一半的字符串确定的，所以前一半字符串字典序小于 `ABC` 的字符串的数量就是答案（等于的情况后面再说）。

那么如何求字典序小于 `ABC` 的的字符串的数量呢？

我们可以将只由大小字母构成的字符串看作一个 $26$ 进制的数值， 那么这个 $26$ 进制的数就是答案。

还有一些特殊情况：
- 如果 $S$ 的长度是奇数，那么当取前一半字符串的时候将中间的一并带上，拼接另一半时将第一个字符再删掉就可以了
- 如果在 $S$ 的基础上获得的回文串小于等于 $S$，那么答案还要加 $1$。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a;i < b;i++)
#define per(i,a,b) for(int i = b - 1;i >= a;i--)
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int mod = 998244353;
int q;

int main() {
    scanf("%d", &q);
    rep(_,0,q) {
        int n;
        string s;
        cin >> n >> s;
        string ss = s.substr(0,(n+1)/2);
        string ss2 = ss;
        reverse(all(ss2));
        if(n % 2) ss2.erase(ss2.begin());
        ll c = 0;
        rep(i,0,(int)ss.size()) {
            c = (c * 26 + (ss[i] - 'A')) % mod;
        }
        if((ss + ss2) <= s) c = (c + 1) % mod;
        printf("%lld\n", c);
    }
    return 0;
}
```

---

## 作者：Down_syndrome (赞：1)

## 思路
由于规定是统计回文串的个数，那么假设 $k=\lfloor\dfrac{n+1}{2}\rfloor$，如果前 $1$ 到 $k$ 个字母已经确认了，那么这个长度为 $n$ 的回文串也就确认了，所以我们只用关心前 $k$ 个字母的取值就行了。令 $f_i$ 为前 $i-1$ 位都与 $X$ 相同，第 $i$ 位比 $X_i$ 小的回文串个数。容易发现 $f_i=(x_i-65)\times 26^{k-i}$，其中 $x_i$ 为 $X_i$ 的 ASCII 值，因为比 $X_i$ 小的字母共有 $x_i-65$ 个，而后面 $k-i$ 个字母的取值没有限制，因此共有 $26^{k-i}$ 种情况。答案显然为 $\sum\limits_{i=1}^k f_i$。

真的吗？

如果你写出来代码，会发现样例某些答案会刚好少 $1$，这是因为我们漏了一种特判，我们没有统计长度为 $n$ 的前 $k$ 位都和 $X$ 相等的字符串。特判后，如果这个串小于等于 $X$，令 $ans\gets ans+1$。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
const int mod=998244353;
int t,n,k,ans,P[N];
char a[N],b[N];
bool check(){
	for(int i=1;i<=n;i++){
		if(b[i]<a[i]) return true;
		if(b[i]>a[i]) return false;
	}
	return true;
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%s",&n,a+1);
		P[0]=1;
		for(int i=1;i<=n;i++) P[i]=P[i-1]*26%mod;
		k=(n+1)/2;
		ans=0;
		for(int i=1;i<=k;i++) b[i]=b[n-i+1]=a[i];
		if(check()) ans++;
		for(int i=1;i<=k;i++) ans=(ans+(a[i]-'A')*P[k-i]%mod)%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Takato_ (赞：0)

## 题意理解与思路

我觉得题意翻译似乎已经说得很清楚了。

给定正整数 $N$ 和长度为 $N$ 的字符串 $S$，你的任务是计算有多少个长度为 $N$ 的回文字符串 $X$，使得 $X\le S$。计算结果对 $998244353$ 取模。$S$ 和 $X$ 均只包含大写英文字母。

总共有 $T$ 组数据。$T \le 250000$，$N \le 10^6$，所有 $S$ 的字母总数不超过 $10^6$。

## 做法分析

先来看看第一个样例 ```AXA```，很明显可以看出，这个字符本身就是一个回文串，再加上 ```X``` 前一共有 $23$ 个字母，选用任意一个都可以构成回文串。所以答案是 $24$ 个。

再来看第二个样例 ```ABCZAZ```。首先 ```A``` 是最小的字符，无法变化，所以当前位答案为 $0$。而第二个字符在取 ```B``` 以前的字符时，永远比初始字符串小，后面在取回文串时永远合法。而第二个字符后只有第三个字符。所以当第二个字符每取一个比本身小的字符时，此时的回文字符串的个数为 $1 \times 26^1$，而第三个字符前有 $2$ 个字符，若后面还有字符，则取这两个字符后，剩下的字符无论取何都能满足条件，所以加上 $2 \times 26^0$。再加上本身将前三个字符反转后小于原字符，答案再加上 $1$，为 $29$。

由此我们大概可以知道，首先需要将原来的字符串的前一半部分进行翻转组成一个回文串，并判断它是否小于等于 $S$。同时从第一个字符开始遍历到第 $\frac{n+1}{2}$ 个字符，对于第 $i$ 个字符，用它前面的字符个数乘上 $26^{\frac{n+1}{2}-1-i}$，同时取余累加答案。

为了简便，我将代码写成了这样。
```cpp
for (int i = (n + 1) / 2 - 1; i >= 0; -- i){
    int t = (s[i] - 'A') * last;
    t %= P;
    ans += t;
    last *= 26; last %= P;
}
```

倒序遍历，并用 $last$ 统计 $26$ 的次方。

代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int P = 998244353;
int T;
signed main(){
    cin >> T;
    while(T--) {
        int n, ans = 0;
        string s, ss = "";
        cin >> n >> s;
        for (int i = 0; i < (n + 1) / 2; i++) ss += s[i];
	    for (int i = n - (n + 1) / 2 - 1; i >= 0; i--) ss += s[i];
        // cout << ss << endl;
        int last = 1;
        for (int i = (n + 1) / 2 - 1; i >= 0; -- i){
            int t = (s[i] - 'A') * last;
            t %= P;
            ans += t;
            last *= 26; last %= P;
        }
        if(ss <= s) ans ++;
        cout << ans % P << endl;
    }
}
```
感觉讲的不是很清楚，但写这篇题解只是为了加深理解而已。

---

## 作者：zyc418 (赞：0)

# E - (∀x∀)
[题目](https://atcoder.jp/contests/abc242/tasks/abc242_e)

~~这题我居然给自己挖了两个坑，还都跳下去了~~

我们考虑回文字符串是如何构成的，是由前面大约 $n \div 2$ 个字符翻转拼接而成。

如果我们考虑前面这些字符串，字典序已经比原串的字典序小了，那么这个回文串的字典序一定比原串小。

问题转化为，前 $n \div 2$ 个字符构成的字符串，有多少个字符串的字典序比它小。

我们还需考虑前 $n \div 2$ 如果和原字符串字典序相同，还可能构成字符串，所以我们需要把这个字符串构造出来，和原串比较字典序即可。

时间复杂度 $O(Tn)$。
# E - Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define mod 998244353
using namespace std;
const ll N=1e6+5;
ll T,n,ans,f;
string s,str1,str2;
int main() {
    cin>>T;
    while(T--) {
        ans=0,f=1;
        cin>>n>>s;
        ll num=(n+1)/2;
        for(ll i=0;i<num;i++) {
            ll cnt=s[i]-'A';
            ans*=26;
            ans+=cnt;
            ans%=mod;
        }
        str1="";
        str2="";
        for(ll i=num-1;i>=0;i--) {
            str1+=s[i];
        }
        if(n%2==0) num++;
        for(ll i=num-1;i<n;i++) {
            str2+=s[i];
        }
        if(str1>str2) f=0;
        cout<<(ans+f)%mod<<endl;
    }
    return 0;
}
```

---

## 作者：IGpig (赞：0)

## ABC242E
### Problem
给你一个字符串，要求有多少个一样长的回文串小于它。

### Solution
因为回文字符串的两边是一样的，所以我们只需要先看字符串的一半，然后判断一下是左边一半大还是右边。
~~~cpp
    string tmp=s.substr(0,n/2);
    reverse(tmp.begin(),tmp.end());
    if(s>=(s.substr(0,(n+1)/2)+tmp)) ans++;
~~~
对于前面的正常统计 $1\Rightarrow \cfrac{(n+1)}{2}$ 就好了：
$$ans=ans\times26+s_i$$

### Code
应该挺好看的吧。
~~~cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
const LL mod=998244353;
LL n,q;
string s;
int main(){
    cin>>q;
    while(q--){
        LL ans=0;
        cin>>n>>s;
        for(int i=0;i<(n+1)/2;i++){
            ans*=26;
            ans=(ans+LL(s[i]-'A'))%mod;
        }
        string tmp=s.substr(0,(n)/2);
        reverse(tmp.begin(),tmp.end());
        if(s>=(s.substr(0,(n+1)/2)+tmp)) ans++;
        cout<<ans%mod<<endl;
    }
    return 0;
}
~~~

---

## 作者：cwxcplh (赞：0)

一道比较简单的题。

题目简化：给定一个字符串 $S$，求所有的回文字符串 $X$ 的总方案数使得 $X\le S$。

因为是个回文串，所以我们只需要研究一边，另一边其实就是一样的，又因为是字符串比较大小，按字典序排，字典序又是从最高位开始，所以我们就看左半边。

首先随便举个例子：`S=ABCDEF`

那么我们就考虑 `ABC` 这一半，对于 $X$ 来讲，第一位在小于 `A` 时，里面一共有 $26^2$ 种情况（乘法原理），但是 $S$ 的第一位就是 `A`，所以不可能比 `A` 还小，此时的 $ans=0\times26^2$。

接着看第二位，$S$ 的第二位是 `B`，而当 $X$ 的第二位比 `B` 小时，里面一共有 $26^1$ 种情况，而比 `B` 小的字母只有 `A`，所以此时的 $ans=0\times26^2+1\times26^1$。

相信数感好的同学这时已经看出些端倪来了，没看出来的可以再算下去。

由此，我们可以得到答案的公式：

$$ans=\sum^{\frac{n}{2}}_{i=1}(c_i\text{在字母表中的第几位}-1)\times26^{(n-\frac{n}{2}-i)}$$

但我们还少考虑了一件事：当前半段完全一样时，这时我们需要看整个回文串是否满足最初的条件：$X\le S$，所以最后还得加个判断。

$$\therefore ans=\sum^{\frac{n}{2}}_{i=1}(c_i\text{在字母表中的第几位}-1)\times26^{(n-\frac{n}{2}-i)}+\operatorname{check(n-\cfrac{n}{2})}$$

注：式子中的幂运算最好不要用 `pow`，不然的话很容易超出数据范围。

AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int t,n,ans;
char c[1000006];
int qpow(int x,int y)//快速幂
{
    if(y==0)
    {
        return 1ll;
    }
    if(y==1)
    {
        return x%mod;
    }
    if(y&1)
    {
        return qpow(x,y>>1)%mod*qpow(x,y>>1)%mod*x%mod;
    }
    else
    {
        return qpow(x,y>>1)%mod*qpow(x,y>>1)%mod;
    }
}
signed main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            cin>>c[i];
        }
        for(int i=1;i<=n-n/2;i++)
        {
            ans+=(int)(c[i]-'A')*(qpow(26ll,n-n/2-i)%mod)%mod;//公式
            ans%=mod;
        }
        bool f=false;
        for(int i=n-n/2+1;i<=n;i++)//公式中的 check 函数
        {
            if(c[i]>c[n+1-i])
            {
                f=true;
                ans++;
                ans%=mod;
                break;
            }
            if(c[i]<c[n+1-i])
            {
                f=true;
                break;
            }
        }
        if(!f)
        {
            ans++;
            ans%=mod;
        }
        cout<<ans%mod<<endl;
        ans=0;
    }
    return 0;
}
```

---

## 作者：forever516 (赞：0)

# 题意
给定正整数
$N$
和长度为
$M$
的字符串
$S$，你的任务是计算有多少个长度为
$N$
的回文字符串
$X$，使得
$X \leq S$。计算结果对 
$998244353$
取模。$S$
和
$T$
均只包含大写英文字母。

# 解法
尝试暴力，直接枚举判断回文串不太好做而且会超时。

因此我们选择更换做法。

我们可以用哈希的思想，将只由大小字母构成的字符串看作一个
$26$
进制的数值， 那么这个数就是答案。

根据这个性质，定义
$dp_i$
表示到第
$i$
个字符时回文串的方案数，我们可以得到转移方程
$dp_i=dp_{i-1} \times 26+a_i$，其中
$a_i$
表示$s_i$
减去
$A$
的值（即可以取多少个小于
$s_i$
的字符）。

但代码只能处理每一个字符都小于
$s_i$
的情况，而无法判断全部等于
$s$
时的情况，需要一个
$check$
去判断前半段字符都与
$s$
相等时是否合法。
最后答案就是
$dp_n+check$。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6,mod=998244353;
ll t,n,k,ans,HASH[N];
char a[N],b[N];
bool check() {
	for(int i=1; i<=n; i++) {
		if(b[i]<a[i]) return 1;
		if(b[i]>a[i]) return 0;
	}
	return 1;
}
void init() {
	HASH[0]=1;
	cin>>n>>a+1;
	for(int i=1; i<=n; i++) HASH[i]=HASH[i-1]*26%mod;
	k=(n+1)/2;
	ans=0;
	for(int i=1; i<=k; i++) b[i]=b[n-i+1]=a[i];
}
void answer(){
	if(check()) ans++;
	for(int i=1; i<=k; i++) ans=(ans+(a[i]-'A')*HASH[k-i])%mod;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--) {
		init();
		answer();
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Saint_ying_xtf (赞：0)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

对于一个长度位 $n$ 的回文串，我们只需要定位到前一半即可。

所以我们可以用递推来遍历一半的数组来得到答案。

设 $dp_i$ 为前 $i$ 个数的方案数。保证这些方案构造的都是小于 $s$ 串的。

于是我们显然可以得到 $dp_i = 26 \times dp_{i-1} + tmp - 1$。

$tmp$ 为 $s_i$ 是第几个字母。

$26 \times dp_{i-1}$ 显然是之前的方案，然后此时每一种字母都可以填，所以直接乘法原理。

$tmp - 1$ 是之前的部分都是等于 $s$ 的，到这一位有多少种方案是可以使得他保持小于 $s$ 串。

到了最后，考虑你要是 $s$ 的前一半构成的一个回文串比 $s$ 小，这也是一种可行方案，答案增加一个。



[link](https://atcoder.jp/contests/abc242/submissions/49421925)。

---

## 作者：Empty_Dream (赞：0)

## 题意

有 $t$ 组数据，每组一个长度为 $n$ 的字符串 $s$。求有多少个长度为 $n$ 的回文串 $x$，使得 $x \le s$，对 $998244353$ 取模。

## 分析

参考 [C题](https://www.luogu.com.cn/problem/AT_abc242_c) 的思路，还是类似递推的做法。

对于两个字符串 $s$ 和 $t$，只要 $t$ 前面有一个字符小于 $s$ 的对应字符，那么后面的所有字符无论多大肯定是小于 $s$ 的，而后面的字符无论是什么都不影响，可以直接乘上 $26$。

根据这个性质，定义 $dp_i$ 表示到第 $i$ 个字符时回文串的方案数，我们可以得到转移方程 $dp_i=dp_{i-1} \times26+a_i$，其中 $a_i$ 表示 $s_i$ 减去 `A` 的值（即可以取多少个小于 $s_i$ 的字符）。但是有个 bug，这个代码只能处理每一个字符都小于 $s_i$ 的情况，而无法判断全部等于 $s$ 时的情况，需要一个 $check$ 去判断前半段字符都与 $s$ 相等时是否合法。最后答案就是 $dp_n+check$。

最后加上 $check$ 后一定要再模 $998244353$。

在每一次询问时一定不要清空 $dp$ 数组，不然会 TLE！！！警钟敲烂。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int mod = 998244353;
int t, n;
int dp[1000005];
string s;

bool check(){//判断原串是否能是回文
	string t = " ";
	for (int i = 1; i <= (n + 1) / 2; i++) t += s[i];
	for (int i = n - (n + 1) / 2; i >= 1; i--) t += s[i];
	return t <= s;
}

signed main(){
	cin >> t;
	while (t--){
		cin >> n >> s;
		s = ' ' + s;
		for (int i = 1; i <= (n + 1) / 2; i++) dp[i] = (dp[i - 1] * 26 + s[i] - 'A') % mod;//递推
		cout << (dp[(n + 1) / 2] + check()) % mod << endl;
	}
	return 0;
}
```

---

## 作者：G__G (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc242_e)

[AT原题](https://atcoder.jp/contests/abc242/tasks/abc242_e)

先解释一下样例：

$$AXA$$

因为 $S$ 的首字母是 $A$，所以 $X$ 的首字母也只能是 $A$。

因为首字母一样，所以第二个字母一定要小于字母 $X$ 所以有 $24$ 种情况。

最后一个字母和首字母一样（$X$ 是回文串）

------------
其实对于 $X$ 的每一位，都可能比 $S$ 的对应位小的一位（前面都相等）。

此时，$X$ 的个数就能表示出来了，假设 $X$ 的长度为 $l$，第 $i$ 位是第一位比 $S$ 的对应位小的，这一位的ASCII码为 $x$ ，则这样的字符串有 $26^{\frac{l+1}{2}-i} \times (x-65)$ 个。

还有一个，就是 $X$ 的前半段等于 $S$ 的前半段，但需要判断是否小于或等于 $S$ 的后半段。

最后加起来即可（注意 $26$ 的高次幂的取余）。

```
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
long long p[20231004]={1};
void solve(){
	int n;
	long long ans=1;
	cin>>n;
	for(int i=1;i<=n;i++){
		p[i]=p[i-1]*26;
		p[i]%=mod;
	}
	string s;
	cin>>s;
	long long len=(n+1)/2;
	for(int i=n/2+n%2,j=n/2-1;i<n;i++,j--){
		if(s[i]<s[j]){
			ans=0;
			break;
		}
		if(s[i]>s[j]){
			ans=1;
			break;
		}
	}
	for(int i=0;i<n/2+n%2;i++){
		ans=ans+(p[len-i-1]*(s[i]-65))%mod;
		ans%=mod;
	}
	cout<<ans%mod<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```


---

## 作者：Erica_N_Contina (赞：0)

# [ABC242E] (∀x∀)

## 思路

首先考虑字符串 $X_0$（我们规定字符串下标由 $0$ 开始）

- 情况 $1$

如果 $\operatorname{ASCII}(X_0)<\operatorname{ASCII}(S_0)$，那么从 $X_1$ 到 $X_{N-1}$ 的字母都可以随便取。但是我们要保证其为一个回文串。情况数为 $26^{\lceil\frac{N-1}{2}\rceil}$。

- 情况 $2$

如果  $\operatorname{ASCII}(X_0)=\operatorname{ASCII}(S_0)$，即 $X_0=S_0$，那么我们就考虑 $X_1$ 和 $S_1$ 的关系，还是按照这两种情况考虑。

特别的，如果我们考虑到 $X_{\lceil n\div 2\rceil -1}$，即回文串的中间位置，如果此时我们任然取情况 $2$，就意味着 $X$ 和 $S$ 的前半部分一模一样，这样我们就需要比对 $X$ 和 $S$ 的字典序关系是否满足要求。

- 情况 $3$

$ \operatorname{ASCII}(X_0)>\operatorname{ASCII}(S_0)$，这种情况我们自然舍去啦~

所以我们要预处理出 $26$ 的 $1\sim N$ 次方对 $mod$ 取模，然后从前往后逐位判断。

## 总结

那么既然 $S$ 已知，那么我们其实可以写出一个简洁的表达式直接表示 $ans$。

$ans=\sum\limits_{i=0}^{\lceil n\div 2\rceil-1} (S_i-65)\times 26^{\lceil n\div 2\rceil -(i+1)}$

特别的，如果 $X$ 和 $S$ 的前半部分一模一样，我们就需要判断 $X$ 是否满足字典序要求，如果满足，$ans$ 加上 $1$。


## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//头文件
#include<bits/stdc++.h>

//数据类型
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
//命名空间
using namespace std;
//常量
const int N=1e6+5;
const int M=1e3;
const int MOD=998244353;
const int INF=1e9;
//变量
int T,n,a,b,c,x[N],y[N],res,tmp,cnt,dev[N];
//int ia,ib,ic,id,ix,iy,in,im,iid,icnt,itmp,ires,ians,ians1,ians2,imx,imn,imxx,imnn;
//int ra[N],rb[N],rc[N],rcnt[N],rton[N],rant[N];
//int qzh[N],cf[N];
//int rra[M][M];
//char cop,cc,cs1[N],cs2[N],crr[M][M];
string s;

void init(){
	//预处理26的幂
	dev[0]=1;
	for(int i=1;i<=N-5;i++){
		dev[i]=dev[i-1]*26%MOD;
	}
}

int check(int b){//检查前半部分一模一样的情况是否成立
	for(int i=n/2+b,j=n/2-1;i<n;i++,j--){
		if(s[i]<s[j])return 0;
		else if (s[i]>s[j])return 1;
	}
	return 1;
}
signed main(){
	
	init();
	cin>>T;
	
	while(T--){
		int ans=0;
		cin>>n>>s;
		int len=ceil(1.0*n/2);//(n+1)/2
		
		int b=n%2;//n为奇偶

		for(int i=0;i<n/2+b;i++){
			ans+=(s[i]-65)*dev[len-i-1]%MOD;
			ans%=MOD;
		}
		cout<<(ans+check(b))%MOD<<endl;
	}
	return 0;
}
```




---

## 作者：Siteyava_145 (赞：0)

大水题，但有许多坑点。

给你一个长度为 $n$ 的字符串 $S$，求有几个回文串 $x$，其字典序 $\le s$ 的字典序。

要求字符均为 `A` 至 `Z`。

例如 $S$ 为 `XIANBEI`。

设 $len=\dfrac{n+1}{2}$，在这里为 $4$。

这时 $x$ 首位 ASCII 小于 `X` 的话，只要 $x$ 回文，后面跟着的字母什么都行。

此时数量为 $26^{len-1}\times 23$。

若等于，则按同样方法看下一位即可。

易得出总和为 $\sum\limits_{i=1}^{len}26^i\times (S_i-65)+1$（$S_i$ 表示 $S$ 中的第 $i$ 位的 ASCII 码）

最后的那个 $1$ 便为 $x_{len}=S_{len}$ 的情况。

-----

但还没完。有一个坑点。

此时 $x$ 已确定，只需判断是否 $\le S$。

如果大于 $S$ 还要将总数的那个 $1$ 减去。

只要将 $x_{len}$ 后面的字母遍历一遍，保证均小于等于 $S$ 的对应位就行

---

还有：

$26$ 的幂次一定要先预处理出来，不然复杂度爆炸。

---

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll T,n;
ll ans,mod=998244353;
string s;
ll esl[600005];
int main(){
	cin>>T;
	esl[0]=1;
	for(int i=1;i<=600000;i++){
		esl[i]=esl[i-1]*26%mod;
	}
	while(T--){
		ans=0;
		cin>>n;
		cin>>s;
		ll len=(n+1)/2;int fl=0;
		if(n&1){
			for(int i=0;i<=n/2;i++){
				ans+=(s[i]-65)*esl[len-i-1]%mod;
				ans%=mod;
			}
			for(int i=n/2+1,j=n/2-1;i<=n;i++,j--){
				if(s[i]<s[j]){
					fl=1;
					break;
				}
				else if (s[i]>s[j])break;
			}
		}else{
			for(int i=0;i<n/2;i++){
				ans+=(s[i]-65)*esl[len-i-1]%mod;
				ans%=mod; 
			}
			for(int i=n/2,j=n/2-1;i<=n;i++,j--){
				if(s[i]<s[j]){
					fl=1;
					break;
				}
				else if (s[i]>s[j])break;
			}
		}
		cout<<(ans+1-fl)%mod<<endl;
	}
	return 0;
}
```




---

## 作者：yukimianyan (赞：0)

## problem
给定正整数 $N$ 和字符串 $S$，构造字符串 $X$ 满足：
- $X$ 由 $N$ 个大写字母组成；
- $X$ 为回文串，即正着读和反着读一样的字符串；
- $X$ 的字典序不大于 $S$ 的字典序。

求 $X$ 的方案数。多组数据，$1\leq N,\sum N\leq 10^6$，$S$ 由 $N$ 个大写字母组成，答案对 $998244353$ 取模。

## solution
注意到 $X$ 是回文串。回文串有一个性质：只要确定回文串的一半，即可确定它的另一半，因为回文串对称。所以，我们只需要枚举 $X$ 的一半，剩下的一半不用考虑。

考虑枚举 $S,X$ 相同的位数（当然不超过一半，接下来令一半的长度为 $M=\left\lfloor\frac{N+1}{2}\right\rfloor$），即 $X_{1\cdots (i-1)}=S_{1\cdots (i-1)}$，再钦定 $X_i<S_i$，那后面怎么填都可以，方案数为 $26^{M-i}(S_i-1)$。

我们还漏了一种情况，即 $X$ 的一半真的与 $S$ 的一半相等。对于这种情况，可以将 $X$ 完整构造出来，与 $S$ 比较。

## code
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int P=998244353;
int n,m;
LL pow26[1000010],ans=0;
char a[1000010];//用 a 代替 S
bool check(){
	for(int i=m+1;i<=n;i++){
		if(a[n-i+1]>a[i]) return 0;
		if(a[n-i+1]<a[i]) return 1;
	}
	return 1;
}
int mian(){
	m=(n+1)>>1;
	ans=check();
	//边界状态 X[1,m]=S[1,m]
	for(int i=1;i<=m;i++){
		(ans+=(a[i]-'A')*pow26[m-i])%=P;
		//普通状态 X[1,i-1]=S[1,i-1],X[i]<S[i]
		//此处 a[i]-'A' 即为 S[i]-1
	}
	printf("%lld\n",ans);
	return 0;
}
void init(){
	for(int i=pow26[0]=1;i<=1e6;i++) pow26[i]=pow26[i-1]*26%P;
	//预处理 26 的幂，计算时不用重新再算
}
int main(){
	for(init(),scanf("%*d");~scanf("%d%s",&n,a+1);mian());
	return 0;
}
```

---

