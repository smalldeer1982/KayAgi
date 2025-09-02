# BA-String

## 题目描述

You are given an integer $ k $ and a string $ s $ that consists only of characters 'a' (a lowercase Latin letter) and '\*' (an asterisk).

Each asterisk should be replaced with several (from $ 0 $ to $ k $ inclusive) lowercase Latin letters 'b'. Different asterisk can be replaced with different counts of letter 'b'.

The result of the replacement is called a BA-string.

Two strings $ a $ and $ b $ are different if they either have different lengths or there exists such a position $ i $ that $ a_i \neq b_i $ .

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

Now consider all different BA-strings and find the $ x $ -th lexicographically smallest of them.

## 说明/提示

In the first testcase of the example, BA-strings ordered lexicographically are:

1. a
2. ab
3. abb
4. abbb
5. abbbb

In the second testcase of the example, BA-strings ordered lexicographically are:

1. aa
2. aba
3. abba

Note that string "aba" is only counted once, even though there are two ways to replace asterisks with characters 'b' to get it.

## 样例 #1

### 输入

```
3
2 4 3
a*
4 1 3
a**a
6 3 20
**a***```

### 输出

```
abb
abba
babbbbbbbbb```

# 题解

## 作者：wanggiaoxing (赞：5)

### 发现一些性质
当 $k=2$ 时 $a ** a$,你可以将第一个 $* $ 替换为两个 $b$ 然后第二个不替换。也可以将第二个 $* $ 替换为两个 $b$ 然后第一个不替换。但它们的结果都是一样的，也就是说一串连续的 $* $ 可以替换的个数是一定的不管方式如何。而个数就是连续 $* $ 个数乘 $k$ 再加一（因为有零）于是我们合并这些 $* $.
### 考虑字典序
令 ${a}_i$ 表示当前合并后第 $i$ 个 $* $ 的替换个数。当前这个位置每多出一个 $ * $ 排名就会多出后面所有 $\prod_{i+1}^{n}{a}_i$ 。然后一位一位去推就行了。
```cpp
#include<bits/stdc++.h>
#define int __int128
//#define pa pair<int,int>
//#define int unsigned long long
//const int mod=1e9+7;
//const int mod=998244353;
using namespace std;
inline int read(){
	int s=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch<='9'&&ch>='0')
		s=s*10+ch-'0',ch=getchar();
	return s*w;
}
int t,n,k,x,ans[2005]; 
string s;
vector<int>v;
signed main(){
	t=read();
	while(t--){
		n=read(),k=read(),x=read()-1;//因为当前x到1才是答案所以要留个1所以要减
		memset(ans,0,sizeof(ans));
		int now=0;
		v.clear();
		cin>>s;
		for(int i=0;i<s.size();i++){
			if(s[i]=='a'){
				if(now)v.push_back(now*k+1);
				now=0;
			}else now++;
		}
		if(now)v.push_back(now*k+1);//合并
		int ji=1;
		for(int i=0;i<v.size();i++){
			ji=1;
			for(int j=i+1;j<v.size();j++){//这里牺牲一个n保证它不会溢出
				ji*=v[j];
				if(ji>x)break;
			}
			if(ji>x)continue;
			if(x==0)continue;
			ans[i]=x/ji;
			x%=ji;
			//cout<<x<<" "<<ji<<" "<<ans[i]<<endl;
		}
		now=0;
		int tot=-1;
		for(int i=0;i<s.size();i++){
			if(s[i]=='a'){
				if(now)tot++;
				if(now)for(int i=1;i<=ans[tot];i++)printf("b");					
				printf("a");
				now=0;
			}else now++;
		}
		if(now)tot++;
		if(now)for(int i=1;i<=ans[tot];i++)printf("b");
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Presentation_Emitter (赞：4)

题意：给定一个仅包含 `a` 和 `*` 的串，将每个 `*` 替换成 $cnt \in [0,k]$ 个 `b`，求字典序第 $x$ 小的字符串。

首先把所有连续 `*` 串（长度为 $len$）视为一个能替换成 $cnt \in [0,k \cdot len]$ 个 `b` 的 `*`。不难发现靠前的 `*` 贡献大于靠后的 `*`。

设总共有 $t$ 个 `b`，对于第 $i$ 个 `*`，每增加一个 `b`，就相当于字典序增加了 $\prod\limits_{j=i+1}^{t}(k \cdot len_j+1)$，因为其后面每一个 `*` 都有 $k \cdot len+1$ 种可能。

于是做一遍类似进制转换的过程即可。细节较多。时间复杂度 $\Theta(n)$。

极其丑陋的赛时代码：

```cpp
ll T,n,k,x,d[2005],val[2005];char s[2005];vector<ll>v;
int main()
{
	T=rd();
	while(T --> 0)
	{
		n=rd();k=rd();x=rd();scanf("%s",s+1);
		s[n+1]='a';v.clear();clr(val);
		for(int i=1,cnt=0;i<=n+1;++i)
			if(s[i]=='*')++cnt;else if(cnt)v.pb(cnt),cnt=0;
		ll t=v.size(),cur=x-1,r=0;
		d[t+1]=1;
		for(int i=t-1;i>=0;--i)
		{
			db tmp=d[i+2]*(v[i]*k+1.L);
			if(tmp>1e18)d[i+1]=3.1415e18;
			else d[i+1]=d[i+2]*(v[i]*k+1);
		}
		for(int i=1;i<=t;++i)
			if(d[i+1]<=cur)val[i]=cur/d[i+1],cur%=d[i+1];
		for(int i=1;i<=n;++i)
		{
			if(s[i]=='a')pc('a');
			else
			{
				++r;for(int t=1;t<=val[r];++t)pc('b');
				while(i<n&&s[i+1]=='*')++i;
			}
		}
		puts("");
	}
	ret 0;
}
```

~~这个题我赛时调了 40 min。。。还是太菜了~~

---

## 作者：GGBoodsqy (赞：2)

# 题意：
给你一个由字符 $a$ 和 $*$ 组成的字符串，你可以把每个 $*$ 换成 $0$ 到 $k$ 个 $b$ ，让你求出转化后第 $x$ 小的字符串。

# 思路：
不难发现对于每组连续的 $*$ ，能形成的方案数为 $cnt⋅k+1$ ，$cnt$ 是 $*$ 的个数。假设有 $n$ 组连续的 $*$ ， $vt_i$ 表示第 $i$ 组 $*$ 的个数。那么在当前位置插入一个 $b$ ，排名就会增加 $g=\prod\limits_{t=i+1}^{n} (a_i⋅k+1)$ ，那么每次判断一下 $g$ 与 $x$ 的大小关系即可，若大于，就不能放，因为只要放一个排名就大于 $x$ 了。反之，则放 $x$ 除 $g$ 个。

# 代码如下：

```cpp
#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;
ll read(){
	ll f=1,k=0;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-f;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=k*10+(c-'0');
		c=getchar();
	}
	return f*k;
}
void print(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else print(x/10),putchar(x%10+'0');
}
vector<ll>vt;
ll ans[2010];
int main(){
	ll t;
	t=read();
	while(t--){
		vt.clear();
		for(ll i=0;i<=2000;i++)ans[i]=0;
		ll n,k,x;
	    n=read();k=read();x=read()-1;
		string s;
		cin>>s;
		s+='a';
		ll cnt=0;
		for(ll i=0;i<=n;i++){
			if(s[i]=='a'){
				if(cnt)vt.push_back(cnt*k+1);
				cnt=0;
			}
			else cnt++;
		}
		for(ll i=0;i<vt.size();i++){
			if(!x)break;
			ll g=1;
			for(ll j=i+1;j<vt.size();j++){
				g*=vt[j];
				if(g>x)break;
			}
			if(g<=x)ans[i]=x/g,x%=g;
		}
		cnt=-1;
		bool f=false;
		for(ll i=0;i<=n;i++){
			if(s[i]=='a'){
				if(f)cnt++;
				if(f)for(ll j=1;j<=ans[cnt];j++)printf("b");
				f=false;
				if(i!=n)printf("a");
			}
			else f=true;
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 1800}$

---
### 解题思路：

进制转化的简单变体。

出现的 $b$ 在越前面能代表越大的权值，具体的权值为后面所有的可能星号组合，和一般的数值进制很相似。

连续的若干个星号需要看作一个可以替换成星号数量乘以 $k$ 的大星号，因为若干个星号连载一起只关心这一大段里一共有多少个 $b$。

那么题目也就是求一个第 $i$ 最大值为 $cnt_i\times k$ 的特殊进制，求出每一位代表的数，从大到小依次填入即可，和一般的进制转化一样做就行了。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
#define int long long
int T,n,k,x,num[20005],cnt,sum[20005],now;
char c[20005];
char get(){
	char c1=getchar();
	while(c1=='\n'||c1==' '||c1=='\r')c1=getchar();
	return c1;
}
signed main(){
	scanf("%I64d",&T);
	while(T--){
		scanf("%I64d%I64d%I64d",&n,&k,&x);x--;
		cnt=0;
		for(int i=1;i<=n;i++)
		num[i]=c[i]=0,sum[i]=1;
		c[0]='a';
		for(int i=1;i<=n;i++){
			c[i]=get();
			if(c[i]=='*'){
				if(c[i-1]=='a')num[++cnt]=k;
				else num[cnt]+=k;
			}
		}
		if(k==0){
			for(int i=1;i<=n;i++)
			if(c[i]=='a')printf("a");
			printf("\n");
			continue;
		}
		sum[cnt+1]=1;
		for(int i=cnt;i>=1;i--){
			sum[i]=sum[i+1]*(num[i]+1);
			if(sum[i]>x||sum[i]<0)sum[i]=x+1;
		}
		now=0;
		for(int i=1;i<=n;i++){
			if(c[i]=='a')printf("a");
			if(c[i]=='*'&&c[i-1]!='*'){
				now++;
				for(int j=1;j<=x/sum[now+1];j++)
				printf("b");
				x%=sum[now+1];
			}
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Xiphi (赞：0)

很恶心的一道细节题。挺考验耐心和思维的清晰与否。反正脑子不清晰的话就会跟我一样暴调 $40$ 分钟。

找出字符串中所有极大通配符段，设其中某段的长度为 $L$。我们可以用一个通配符来表示，然后这个通配符就可以表示 $0$ 到 $L \times b$ 个 $b$。

然后我们发现，`a` 对序列是完全没有影响的，我们就考虑忽视掉它，发现此时变成了这样一个问题：每一位是一个不同的进制，求这个“混合进制数”的从 $0$ 开始的第 $k$ 个数是多少。

笔者采用了从前向后遍历，然后通过计算算出某一位最后应是多少，这样就更便于输出了。我看题解区一般都是分开输出的。我的方法会简单一些。

在递归之前，还要从后往前遍历对每个下标预处理出可以生成的字符串个数。然后这题就做完了。

这里笔者提供一组小 hack 数据方便调试：

input：
```
1
4 1 3
*aa*
```

output：
```
baa
```


```cpp
//代码中把 read() 函数删去了。
#include<bits/stdc++.h>
#define _for(i,x,y) for(int i=x;i<=y;++i)
#define _forp(i,x,y,z) for(int i=x;i<=y;i+=z)
#define _rep(i,x,y) for(int i=x;i<y;++i)
using namespace std;
#define int __int128
int T,n,k,x;string s,t;
int a[2005];
int mul[2005];
void solve(int pos,int X){
    if(pos==n) return ;
    if(s[pos]!='*'){
        cout<<'a';
        solve(pos+1,X);
        return ;
    }
    if(mul[pos]/(1+(a[pos])*k)>X){
        if(s[pos]!='*') cout<<s[pos];
        solve(pos+1,X);
        return;
    }
    int xx=(X)/((mul[pos]/(1+(a[pos])*k)));
    if(X%((mul[pos]/(1+(a[pos])*k)))!=0) xx++;
	_for(i,2,xx){
       	cout<<'b';
   	}
   	solve(pos+1,X-(mul[pos]/(1+(a[pos])*k))*(xx-1));
}
signed main(){
	read(T);
    int cnt=0;
    while(T--){
        s.clear();
        read(n),read(k),read(x);
		cin>>t;
        cnt++;
        t=" "+t;
        int r=1,cnt=0,cnl=0;
        _for(i,1,n){
            if(t[i]!='*'&&cnt) s+='*',a[s.size()-1]=cnt,cnt=0;
            else cnt+=(t[i]=='*');
            if(t[i]=='a') s+='a';
        }
        if(cnt) s+='*',a[s.size()-1]=cnt;
        n=s.size();
        //0 n-1
        mul[n]=1;
        for(int i=n-1;i>=0;--i){
            if(a[i]){
                mul[i]=mul[i+1]*(1+(a[i])*k);
            }else{
                mul[i]=mul[i+1];
            }
            if(mul[i]>=1e18||mul[i]<0){
                if(mul[i]<0) mul[i]=0;
                break;
            }
        }
        _for(i,0,n-1){
            if(s[i]=='*'&&mul[i]){solve(i,x);break;}
            else {
                if(s[i]=='a')cout<<s[i];
            }
        }
        memset(a,0,sizeof a);
        memset(mul,0,sizeof mul);
        cout<<'\n';
    }
	return 0;
}
```

---

## 作者：_RainCappuccino_ (赞：0)

> $\mathtt{TAG}$：枚举

# First. 缩点

对于一段长度为 $len$ 连续的 `*`，它的生成方案数**不是** $(k + 1)^{len}$。为什么？对于该段，长度至多为 $k \times len$，至少为 $0$，所以长度一共有 $len\times k + 1$ 种方案，而所有字符都是相同的，所以方案数仅与长度有关。

于是，不妨将所有连续的 `*` 所为一个可以生成 $0 \sim len \times k$ 的特殊 `*`，后面成为 $cnt$。

# Second. 定位

考虑字典序最小，肯定是优先展开靠后的 `*`。  

对于后 $i$ 个 `*`，他们可以生成的字符串的种类数为 $fac_i = \prod_{j = i}^{n} cnt_j$。

找到第一个 $< x$ 的 $fac_i$，记为 $pos$。

而对于 $pos - 1$，它每增加一个 `b`，就会增加 $fac_{pos}$ 种字符串，所以 $pos - 1$ 需要展开的个数，即为 $\frac{x}{fac_{pos}}$。

对于剩下 $pos$ 个数，它们应该是后 $pos$ 个 `*` 所形成的字符串种第 $x \bmod fac_{pos}$ 个，按照这种方法接着扫下去，就可以得到每个 `*` 需要展开的次数。随后，输出即可。

# Tips

1. $fac_i$ 可能爆 long long 所以求到第一个 $> x$ 的 $fac_i$ 就可以停下了，而前面的 `*` 肯定不能展开。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int , int> pi;
#define endl '\n'
#define int long long
const int N = 2000 + 10;
int n , k , x , tot , tmp;
string s;
int len[N] , cnt[N] , p[N] , fac[N] , to[N];
bool type[N];
int ans[N];

signed main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
    int _;
    cin >> _;
    while (_--) {
        cin >> n >> k >> x >> s;
        x--;
        s = '.' + s;
        tot = tmp = 0;
        memset(type, 0, sizeof type), memset(len, 0, sizeof len), memset(fac, 0, sizeof fac);
        memset(cnt, 0, sizeof cnt), memset(ans, 0, sizeof ans);
        for (int i = 1; i <= n; i++) {
            if (s[i] != s[i - 1]) len[++tot] = 1 , type[tot] = (s[i] == '*');
            else len[tot]++;
        }
        for (int i = 1; i <= tot; i++) {
            if (type[i]) to[i] = ++tmp , cnt[tmp] = len[i] * k + 1;
        }
        fac[tmp + 1] = 1;
        for (int i = tmp; i >= 1; i--) {
            if(fac[i + 1] * 1.0 > (x * 1.0 / (cnt[i] * 1.0))) break; // 防止爆 Long long
            fac[i] = fac[i + 1] * cnt[i];
        }
        for (int i = 2; i <= tmp + 1; i++) {
            if(fac[i] == 0) continue;
            ans[i - 1] = x / fac[i];
            x %= fac[i];
        }
        for (int i = 1; i <= tot; i++) {
            if (!type[i]) {
                for (int j = 1; j <= len[i]; j++) cout << 'a'; // 对于连续段 a
            } else {
                for (int j = 1; j <= ans[to[i]]; j++) cout << 'b'; // 对于连续段 b
            }
        }
        cout << endl;
    }
    return 0;
}
```

---

## 作者：蒟蒻丁 (赞：0)

[更好体验](https://www.cnblogs.com/caijiLYC/p/15729909.html)

先考虑如何构造一个比序列 A ,字典序大一的序列。  
首先考虑在末尾添加一个 b ，如果超过了添加上限，那么就进一位。把末尾的 b ，全部拿掉，然后在前面一个可以放置 b 的地方放一个，比如下面情况。  
>3 2 3  
a * a *  
a a  
a a b  
a b a  

于是我们可以理解为找一个字典序为 k ，的序列就是找到 k 在不定进制下的表达，考虑倒序枚举，首先找到第一个开始放置 b 的位置在哪里，然后从这里开始找。每次用 k' 取模后面的总方案数，就能知道当前的位置要放置多少个 b ，以此类推即可构造出答案。  
```c++17
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
ll n,m,k,a[1000010],f[1000101],ans[1000011],T,p;
char c[10001];

int main(){
	cin>>T;
	while(T--){
		memset(a,0,sizeof(a));
		memset(f,0,sizeof(f));
		memset(ans,0,sizeof(ans));
		scanf("%lld%lld%lld",&n,&m,&k);
		p=0,n++;
		scanf("%s",c+2);
		c[1]='a';
		for(ll i=1;i<=n;i++)
			if(c[i]=='a')p++;
		ll r=p,num=0,pos=-1;
		for(ll i=n;i>=1;i--){
			if(c[i]=='a')
				a[r--]=num,num=0;
			else num++;
		}
		for(ll i=1;i<=p;i++)a[i]*=m;
		for(ll i=1;i<=p;i++)a[i]++;
		f[p]=a[p];
		for(ll i=p;i>=1;i--){
			if(!f[i])f[i]=f[i+1]*a[i];
			if(f[i]<0)f[i]=1e18;
			if(f[i]>=k){
				pos=i;
				break;
			}
		}
		f[p+1]=1;
		for(ll i=pos;i<=p&&k;i++){
			if(k%f[i+1]==0)ans[i]=k/f[i+1]-1;
			else ans[i]=k/f[i+1];
			k-=f[i+1]*ans[i];
		}
		for(ll i=1;i<=p;i++){
			if(i!=1)printf("a");
			for(ll j=1;j<=ans[i];j++)printf("b");
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：dzh_goes_to_thu (赞：0)

# 0.写在最前面
本题有一定思维含量。
# 1.小小的转化
首先考虑把 `a` 当作 `1` ，把 `b` 当作 `0` 然后填充二进制数。  
显然 如果啥都不填的情况 就是 `0000...0` ，这个是最小的。  

如果这是一段连续的、长度为 $len$ 的 `*` 的话，那么就有可能这里能填 $len\times k$ 的 `1` 。

# 2.寻找相似处

我们不妨从这段长度在于 $[0,len\times k] $ 的 `1` 区间来看。

因为 **区间互相独立** ，所以 **前面取什么不影响后面取什么**。

因为 **字典序的性质** ，所以 **相邻的两个这样的二进制数，必然是最后一位多（少）取了一个 `1` 。**

如果没有理解，建议结合样例 `3` 食用。 

然后，我们可以把 **取多少个数 写出来** ，然后整个序列就写成了这样（样例3）：

```
00
01
02
...
09
10
11
...
19
20
...

```

找到什么规律了吗？**是的，我们规定每一位取的上限，然后不断进位。**

更形象地说，**就是把这个 $k$ 转化成一个整数，但是每一位都有不同的进位上限。**

# 3.具体处理

来讲详细的操作了。

首先，确保答案的每一位都开足 `long long` ，进位需要；然后给最后一位赋上值 $x-1$ ；不断模拟 **像是高精度的进位** 即可。

但是求出的只是 **对于每一位输出多少个 `b`** 。于是记录每一位前面有多少个 `a` 即可。

# 4.代码

```cpp
#include<bits/stdc++.h>
using namespace std;typedef int I;typedef long long LL;const int inf=1073741823;int FL;char CH;template<typename T>void in(T&a){for(CH=getchar(),FL=1,a=0;CH<'0'||CH>'9';CH=getchar())FL=(CH=='-')?-1:1;for(;CH>='0'&&CH<='9';CH=getchar())a=a*10+CH-'0';a*=FL;}template<typename T,typename...Args>void in(T&a,Args&...args){in(a);in(args...);}
I n,k,m;LL x;
const I maxn=2010;
LL lim[maxn],ans[maxn];
I frm[maxn];
char b[maxn];
void sol(){
	in(n,k,x);
	m=1;
	I i,j;
	memset(b,0,sizeof(b));
	for(i=1;i<=n;++i){
		while(CH!='a'&&CH!='*')CH=getchar();
		b[i]=CH;CH=getchar();
		lim[i]=frm[i]=0;
		ans[i]=0; 
	}
	i=1;
	while(i<=n&&b[i]=='a')++frm[1],++i;
//	printf("%d\n",i);
	for(j=i;j<=n;){
		while(j<=n&&b[j]=='*')++j,++lim[m];
		++m;
		while(j<=n&&b[j]=='a')++j,++frm[m];
		i=j;
	}
//	for(I i=1;i<=m;++i)printf("%lld %d\n",lim[i],frm[i]);
	for(I i=1;i<m;++i)lim[i]*=k,++lim[i];
//	printf("%lld ",lim[i]);
//	putchar(10);
	ans[m-1]=x-1;
	for(I i=m-1;i;--i){
		ans[i-1]+=ans[i]/lim[i];
		ans[i]%=lim[i];
	}
//	for(I i=1;i<m;++i)printf("%d ",ans[i]);
//	putchar(10);
	for(I i=1;i<=m;++i){
		while(frm[i])--frm[i],putchar('a');
		while(ans[i])--ans[i],putchar('b');
	}putchar(10);
}
I main(){
	I T;
	in(T);
	while(T--){
		sol();
	}
	return 0;
}

```

---

