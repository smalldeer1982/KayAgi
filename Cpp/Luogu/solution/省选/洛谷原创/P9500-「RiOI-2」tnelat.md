# 「RiOI-2」tnelat

## 题目背景

小 E 是一名一年级的小学生。她正在学习如何阅读。

如果在纸上写上 $998,\!244,\!353$，那么她就会读「三——五三四四——二八九九。」是的，她是从右往左读的。然后，她会把这个数理解为 $353,\!442,\!899$。

不过这并不影响她交流——她只是不会读纸上的文字罢了。唯一的问题是，她现在要学习带余除法了，而老师说不定会在纸上画一些红色的叉叉。不过，那又如何？

## 题目描述

对于一个长度为 $n$ 的**由数字组成的**字符串 $s=s_1s_2s_3\cdots s_n$，定义它的权值为 $f(s)=\sum\limits_{i=1}^n 10^{n-i}s_i$。（也就是它代表的十进制数）定义它的反串为 $\overline s=s_ns_{n-1}s_{n-2}\cdots s_1$。例如，$s=\texttt{0321}$ 的权值为 $f(s)=321$，反串为 $\overline s=\texttt{1230}$。  

试构造一个字符串 $s$，使得 $|s|\le 114514$，且 $f(s)\equiv a\pmod {998,\!244,\!353}$ 且 $f(\overline s)\equiv b\pmod{998,\!244,\!353}$。如果 $c=0$，你还要保证 $s_1\neq \texttt0$ 且 $s_n\neq \texttt 0$。
如果无解，仅输出整数 $-1$ 即可。

## 说明/提示

### 样例解释

对于第一组样例的第一组数据，$s=\overline{s}=\texttt{1000000001}$，$f(s)=f(\overline s)=1{,}000{,}000{,}001\equiv 1{,}755{,}648\pmod{998,\!244,\!353}$，所以它是一个可行解。

### 数据规模与约定

**本题开启捆绑测试。**

| $\text{Subtask}$ | 分值 | $a,b$ | 特殊性质 | 
| :--------------: | :--: | :---: | :------: |
| $0$ | $5$ | $ \in [1, 9]$ | $a = b$ |
| $1$ | $10$ | $ \in [0, 9]$ | / |
| $2$ | $15$ | $ \in [0, 99]$ | / | 
| $3$ | $25$ | / | $a = 0$ |
| $4$ | $25$ | / | $c = 1$ |
| $5$ | $20$ | / | / |

上表中的斜杠表示无特殊限制。

对于 $100\%$ 的数据，$1\leq T\leq 30$，$c\in\{0,1\}$，$0 \leq a, b \lt 998{,}244{,}353$。

## 样例 #1

### 输入

```
4
0
1755648 1755648
0 353442899
35281 18253
99728538 70320626```

### 输出

```
1000000001
998244353
35281
66330831785160880538172878128228067748679057340064161580956433229228884846388176250309226257600174873157935217529307119972759542770571505108922703815887608877795159689067116959276902444827654683066165```

## 样例 #2

### 输入

```
1
1
30 30```

### 输出

```
030```

## 样例 #3

### 输入

```
5
0
114514191 214748364
414414414 515515515
302813344 124821394
123456789 987654321
307210721 127012703```

### 输出

```
4509169566936302030543528193
6765800751328156020889260421
6754420765703935546785979321
4408846009459835952892074437
3108033793065515131695113495```

# 题解

## 作者：MatrixGroup (赞：9)

### 前言

非常 Educational 的一道题。

### 题意

构造一个数字串，正写 $\equiv a\pmod {998,\!244,\!353}$，反写 $\equiv b\pmod {998,\!244,\!353}$。


### 做法 1（Subtask 0）

显然一位数正读倒读都是它自己，输出 $a$ 即可。

### 做法 2（Subtask 1,2）

考虑手玩或打表。

### 做法 3（$a=0,c=1$）

定义 $\operatorname{rev}(x)$ 为数 $x$ 反转之后的结果。

考虑构造 $\operatorname{rev}(998,\!244,\!353k)\equiv b\pmod{998,\!244,\!353}$，但是这样枚举量太大了了。不考虑前导后缀 $0$ 的话，考虑构造 $\operatorname{rev}(998,\!244,\!353k)\times10^u\equiv b\pmod{998,\!244,\!353}$。我们猜测，在 $k$ 和 $u$ 在一定的范围内必定有解。迭代其中一个，预处理另一个即可。

期望得分：$0$。


### 做法 4（Subtask 5）

考虑两个问题，

- 如何去掉 $a=0$ 这个特殊限制。
- 如何去掉前后缀的 $0$。

对于 $a\neq0$，我们考虑一个性质：$0\cdot 10^k+a=a$。

由此，我们可以想到如下构造：

![](https://cdn.luogu.com.cn/upload/image_hosting/o9adpa6o.png)

显然，这样构造出来的数正着读余 $a$，倒着余 $b$。所以它符合条件。

我们考虑如何去掉前后缀的 $0$。我们可以把 $0$ 替换为一些不是 $0$ 的东西，但效果一样。这需要一个东西正读倒读都余 $0$。可以发现$A=649{,}938{,}929{,}839{,}946$ 符合条件。我们把前后缀的 $15$ 个 $0$ 替换成 $A$ 即可。（可以简单地保证至少有 $15$ 个 $0$）

-- -

为何数据不随机的情况下这个算法是正确的呢？

借用机器的算力我们可以证明：考虑这么一个事情，我们假如让每一个数取 $10$ 模 $998,\!244,\!353$ 的离散对数。（$10$ 是模 $998,\!244,\!353$ 的原根）打出 $10^6$ 以内的 $\operatorname{rev}(998,\!244,\!353k)$ 表后，发现对数的 gap 在 $2\times10^4$ 的级别。因此我们可以最多迭代 $2\times10^4$ 级别的 $u$ 就可以得到答案。长度不超过 $4\times10^4$ 级别。

实际上，有很多对撞算法也可以以很高概率得到正解，因为**没法对着卡**，所以本题数据实际上是随机造的。

## Bonus

保证数据随机，请你保证答案在 $2^{127}-1$ 以内。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,n) for(int i=0,_##i##__end=(n);i<_##i##__end;++i)
#define pb push_back
#define mp make_pair
typedef long long ll;
using namespace std;
const ll mod1=998244353;
const ll g=10;
const ll inv_g=299473306;
const string f15="649938929839946";
string s,t;
int rev(ll x)
{
	ll v=0;
	rep(i,18)
	{
		v=v*10+x%10;x/=10;
	}
	return v%mod1;
}
string revv(ll x)
{
	string f="";
	rep(i,18)
	{
		f+=char('0'+x%10);x/=10;
	}
	return f;
}
map<int,int> idx;
string gett(ll a)// mod 0 = a
{
	string v="";
	int c=15;rep(i,c)a=a*inv_g%mod1;
	while(!idx.count(a))
	{
		a=a*inv_g%mod1;
		++c;
	}
	int fst=idx[a];
	v=revv(fst*mod1);
	rep(i,c-15) v+="0";
	v+=f15;
	return v;
}
void init()
{
	rep(i,1000001) idx[rev(i*mod1)]=i;
}
void solve()
{
	int a,b;
	cin>>a>>b;
	s=gett(a);t=gett(b);
	reverse(t.begin(),t.end());cout<<t<<s<<endl;
}
int main()
{
	init();
	ios_base::sync_with_stdio(false);
	int t,c;cin>>t>>c;
	while(t--)
	solve();
	return 0;
}
```

---

## 作者：Grand_Dawn (赞：7)

[题目链接](https://www.luogu.com.cn/problem/P9500)。

很有意思的构造题。

这里提供一种思路：

以下定义 $\operatorname{rev}(x)$ 表示为数 $x$ 反转之后的结果，$\operatorname{len}(x)$ 表示为数 $x$ 的长度（数字的个数）。

考虑将答案认为是 $p=998,244,353x$ 和 $q=a+998,244,353y$ 拼在一起。

首先考虑正写 $\equiv a(\bmod\  998,244,353)$ 的条件，发现显然成立。

接着考虑反写 $\equiv b(\bmod\  998,244,353)$ 的条件，等价于 $\operatorname{rev}(q)\times 10^{\operatorname{len}(p)}+\operatorname{rev}(p) \equiv b(\bmod\ 998,244,353)$。

使用 meet in the middle 的做法，需要使式子其中一边仅和 $p$ 有关，另一边仅和 $q$ 有关。

因此，原式可化为 $\operatorname{rev}(q)\equiv\dfrac{b-\operatorname{rev}(p)}{10^{\operatorname{len}(p)}}(\bmod\ 998,244,353)$。

代码实现：先枚举 $x$ 将所有的 $\dfrac{b-\operatorname{rev}(p)}{10^{\operatorname{len}(p)}}$ 存入哈希表中，再枚举 $y$ 确定合法的 $p$ 和 $q$。

枚举 $x$ 和 $y$ 至 $10^5$ 即可通过本题。

注意点：需要跳过一些 $x$ 和 $y$，使得开头和末尾不会为 $0$。

数字串长度最大为 $28$，应该算比较不错的。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define B 100000
#define a first
#define b second
using namespace std;
int qpow(int mt,int p){
    int ret=1;
	for(;p;p>>=1,mt=mt*mt%mod)if(p&1)ret=ret*mt%mod;
	return ret;
}
pair<int,int>op[B];
unordered_map<int,int>trans;
string inttostring(long long x){
	stringstream ss;string s;
	ss<<x;ss>>s;
	return s;
}
int rev(int x){
	string s=inttostring(x);
	reverse(s.begin(),s.end());
	stringstream ss;
	ss<<s;ss>>x;
	return x;
}
string solve(int a,int b){
	trans.clear();
	for(int i=1;i<B;i++)if(i%10)trans[(b+mod-op[i].b)*qpow(op[i].a,mod-2)%mod]=i;
	for(int i=0;i<B;i++){
		if((a+i*mod)%10==0)continue;
		int val=rev(a+i*mod)%mod;
		if(trans.find(val)!=trans.end())
			return inttostring(trans[val]*mod)+inttostring(a+i*mod); 
	}
	return "";
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	for(int k=1;k<B;k++){
		if(k%10==0)continue;
		string s=inttostring(rev(k*mod));
		op[k].a=1;
		for(auto i:s){
			op[k].a=op[k].a*10%mod;
			op[k].b=(op[k].b*10+(i-'0'))%mod;
		}
	}
	int t,id;cin>>t>>id;
	while(t--){
		int a,b;cin>>a>>b;
		cout<<solve(a,b)<<endl;
	}
	return 0;
}

```



---

