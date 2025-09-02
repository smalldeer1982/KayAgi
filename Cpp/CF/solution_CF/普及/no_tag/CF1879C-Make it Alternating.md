# Make it Alternating

## 题目描述

You are given a binary string $ s $ . A binary string is a string consisting of characters 0 and/or 1.

You can perform the following operation on $ s $ any number of times (even zero):

- choose an integer $ i $ such that $ 1 \le i \le |s| $ , then erase the character $ s_i $ .

You have to make $ s $ alternating, i. e. after you perform the operations, every two adjacent characters in $ s $ should be different.

Your goal is to calculate two values:

- the minimum number of operations required to make $ s $ alternating;
- the number of different shortest sequences of operations that make $ s $ alternating. Two sequences of operations are different if in at least one operation, the chosen integer $ i $ is different in these two sequences.

## 说明/提示

In the first test case of the example, the shortest sequences of operations are:

- $ [2] $ (delete the $ 2 $ -nd character);
- $ [3] $ (delete the $ 3 $ -rd character).

In the second test case of the example, the shortest sequences of operations are:

- $ [2, 1] $ (delete the $ 2 $ -nd character, then delete the $ 1 $ -st character);
- $ [2, 2] $ ;
- $ [1, 1] $ ;
- $ [1, 2] $ ;
- $ [3, 1] $ ;
- $ [3, 2] $ .

In the third test case of the example, the only shortest sequence of operations is $ [] $ (empty sequence).

## 样例 #1

### 输入

```
3
10010
111
0101```

### 输出

```
1 2
2 6
0 1```

# 题解

## 作者：Κarrу5307 (赞：11)

题目要求相邻的两个字符不同，则考虑把连续的一段 $1$ 或 $0$ 删成 $1$ 个。

设 $d_1, d_2, \cdots, d_k$ 表示连续的极长 $1$ 或 $0$ 子串的长度，显然至少要删 $\sum\limits_{i = 1}^k (d_i - 1)$ 次。

接着考虑计算方案数。对于第 $i$ 段，我们可以考虑留下哪一个元素，有 $d_i$ 种方案。对于要删的元素，有 $\left(\sum\limits_{i = 1}^k (d_i - 1)\right)!$ 种方案。所以答案为 $\left(\sum\limits_{i = 1}^k (d_i - 1)\right)!\prod\limits_{i = 1}^k d_i$。

---

## 作者：tang_mx (赞：7)

非常不错的一道排列组合题啊。

### 题目大意

输入一串只有 $0/1$ 的字符串 $s$，要删除若干个数，使得 $s$ 成为类似 $010101$ 的字符串（即 $0$ 只和 $1$ 相邻，$1$ 只和 $0$ 相邻）。

问要达到目的需要删除的数的总数，以及删数的方案数，最终答案对 $998244353$ 取模。

### Analysis

需要删的数还是很好求的，遍历一遍字符串 $s$，找出长度大于 $1$ 的由连续的 $0$ 或 $1$ 构成的子串 $s_i$，其长度 $len_i-1$ 即这一子串要删除的数的个数，累加起来的总数 $sum$ 就是需要删除的数的总数。

下面分析方案数的求法。因为我们求出了 $s_i$ 的长度 $len_i$，需要从 $len_i$ 个数中选 $len_i-1$ 删掉，即求 $C_{len_i}^{len_i-1}$，由数学知识我们知道 $C_{len_i}^{len_i-1}=len_i$，因此将 $len_i$ 累乘起来的结果 $ans$ 即部分方案数。由于删数的顺序不定，还需要求出 $sum$ 个数的全排列 $sum!$，将 $ans$ 乘上 $sum!$ 即最终方案总数。

CODE

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long

using namespace std;

inline int read(){
	int x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') y=-y;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*y;
}

const int N=2e5+10;

const ll mod=998244353;

int t,n;

inline ll js(ll x){
	ll ans=1;
	while(x){
		ans=ans*x%mod;
		x--;
	}
	return ans%mod;
}

void solve(){
	string s;
	cin>>s;
	int len=s.length();
	int cnt=1;
	vector<int>a(len);
	int top=1;
	for(int i=1;i<len;i++){
		if(s[i]==s[i-1]){
			a[top]=1;
			while(s[i]==s[i-1]){
				a[top]++;
				i++;
			}
			top++;
		}
	}
	int i=1;
	int ans=0;
	ll ans2=1;
	for(int i=1;i<top;i++){
		ans+=a[i]-1;
		ans2=ans2*a[i]%mod;
	}
	ans2=ans2*js(ans);
	printf("%d %lld\n",ans,ans2%mod);
}

int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
```


---

## 作者：llxsmy_forever (赞：4)

## 题目描述
给定一个 $01$ 串 $s$，要删除最少的数字使得此串不存在连续的 $1$ 和 $0$，并且在删除的数字最少的前提下求出方案数。

## Solution
先看第一个询问，结论很显然，先把原串分成 $m$ 块，每一块是连续的 $0/1$，设第 $i$ 块的字符数是 $a_i$，我们只要删除其中任意 $a_i-1$ 个就好了。答案就是 $\sum_{i=1}^m a_i-1$。又因为 $\sum_{i=1}^m a_i = |s|$，所以答案就是 $|s|-m$。

重点看第二个询问，先说一个细节，当时比赛的时候卡了半小时，就是删字符时不一定等第 $i$ 块搞定之后再搞下一块，可以这一块删几个字符，再跳到另一块去删几个字符。对此，设询问一答案为 $k$，我们先求出删的 $k$ 个数的方案数，也就是 
$\prod_{i=1}^m C_{a_i}^{a_i-1}$。然后再对每一种方案求全排列，所以询问二的答案就是 $(\prod_{i=1}^m C_{a_i}^{a_i-1} )\times A_{k}^{k}$。

## Code
```cpp
#include<bits/stdc++.h>
//记得开long long
#define ll long long
using namespace std;
const ll N=3e5+100,P=998244353;
char s[N];ll fac[N];
int main(){
	ll t;scanf("%lld",&t);fac[0]=1;
	for(ll i=1;i<=200000;i++)fac[i]=fac[i-1]*i%P;
	while(t--){
		scanf("%s",s+1);
		ll n=strlen(s+1);
		ll ans1=0,ans2=1,last=0;
		for(ll i=1;i<=n;i++){
			if(i==n||s[i]!=s[i+1]){
				ll x=i-last;
				ans1+=x-1;
				ans2=ans2*x%P;
				last=i;
			}
		}
        //第一个询问答案为1时记得特判
		printf("%lld %lld\n",ans1,ans1==0?1:ans2*fac[ans1]%P);
	}
	return 0;
}
```


---

## 作者：__Star_Sky (赞：2)

## Description

给定一个由 `0` 或 `1` 构成的字符串，每次操作可以删除任意一个字符，记这次操作为删除的字符的下标。问至少需要多少次才能把原字符串变成 `01` 交替的， 以及有多少种不同的操作序列。

## Solution

对于第一问，显然每段连续的 `0` 或 `1` 都要删除到只剩一个。假设由 $k$ 段连续的 `0` 或 `1`，每段长度为 $len$，那么 $ans=\sum\limits_{i=1}^{k} len_i$。

对于第二问，对于每一段连续的 `0` 或 `1`，要选择 $len-1$ 个字符删除，有 $C_{len}^{len-1}=len$ 种选法。构成的操作序列长度为 $ans$，每个操作序列都可以将其任意排列，总共有 $ans!$ 种方案。最终答案就是 $ans!\times \prod\limits_{i=1}^{k}len_i$。

## Code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int N=3e5+10;
char s[N];
int f[N];
signed main()
{
	f[0]=1;for(int i=1;i<=200000;i++) f[i]=f[i-1]*i%mod;
	int T;
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%s",s+1);
		int ans1=0,ans2=1;
		int n=strlen(s+1),cnt=1;
		for(int i=2;i<=n+1;i++)
		{
			if(s[i]==s[i-1]) cnt++;
			else
			{
				ans1+=cnt-1;
				if(cnt>1) ans2=ans2*cnt%mod;
				cnt=1;
			}
		}
		printf("%lld %lld\n",ans1%mod,ans2*f[ans1]%mod);
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

**分析**

对于第一个问题显然不难解决。首先找到一段全是 $1$ 或全是 $0$ 的，设其长度为 $k$，那么就要从 $k$ 个中选取 $k-1$ 个删掉。所以答案是 $(\displaystyle\sum k-1)\bmod998244353$。

第二个问题的话，一共要删 $(\displaystyle\sum k-1)$ 个数，所以每次 $ans2$ 要乘上连续段的长度，最后乘 $(\sum k-1)!$。

**AC Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int jc[200010];
signed main()
{
	int t;
	string s;
	jc[1]=1;
	for(int i=2;i<=2e5;i++) jc[i]=(jc[i-1]*i)%mod;
	cin>>t;
	while(t--)
	{
		long long ans1=0,ans2=1;
		cin>>s;
		for(int i=1;i<s.size();i++) if(s[i]==s[i-1]) ans1++;
		cout<<ans1<<' ';
		if(ans1==0)
		{
			cout<<1<<endl;
			continue;
		}
		long long tp=1;
		for(int i=1;i<s.size();i++)
		{
			if(s[i]==s[i-1]) tp++;
			else
			{
				ans2*=tp%mod;
				ans2%=mod;
				tp=1;
			}
		}
		ans2*=tp%mod;
		ans2%=mod;
		ans2*=jc[ans1];
		cout<<ans2%mod<<endl;
	}
}

---

## 作者：DerrickLo (赞：0)

我们把原串抽象成一段 $0,1$ 交替的字符串：

$$1\ldots10\ldots01\ldots1\ldots$$

那我们容易发现对于每个全是 $0$ 或 全是 $1$ 的子串，设这个子串的长度为 $len$，则需要操作的次数是 $len-1$，而且这个子串有 $\dbinom{cnt}{cnt-1}=cnt$ 种选择方法，这样就能求出最小需要删除的次数和选择方法总数了，注意最后还有阶乘种操作的排序方式，乘上即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int t,fac[200005];
string s;
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int C(int n,int m){
	if(n<m)return 0;
	return fac[n]*ksm(fac[m],mod-2)%mod*ksm(fac[n-m],mod-2)%mod;
}
signed main(){
	cin>>t;
	fac[0]=1;
	for(int i=1;i<=200000;i++)fac[i]=fac[i-1]*i%mod;
	while(t--){
		cin>>s;
		int cnt=0,ans=1,anss=0;
		s+='2'; 
		for(int i=0;i<s.size();i++){
			if(i!=0&&s[i]!=s[i-1]){
				if(cnt==1){
					continue;
				}
				ans*=cnt,ans%=mod;
				anss+=cnt-1;
				cnt=0;
			}
			cnt++;
		}
		ans*=fac[anss],ans%=mod;
		cout<<anss<<' '<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：phigy (赞：0)

我们会发现，由于每一步不同的位置在选择序列中的数值也就是不同的，所以答案就是删除最少的数形成 `01` 交替的方案数。

那么对于 `01` 交替有两种结果一种是开头为 `1` 一种是开头为 `0`，我们分别计数。

我们最终剩余的串的长度是由原始串连续的 `1` 段和 `0` 段的个数决定的，再此之后对于每个段我们又只需要保留一个，因此乘上 $\dbinom{len_i}{len_i-1}$。

然后在我们选择要删哪些后，我们就要选择删的顺序那就是乘上 $(\sum len_i)!$。

然后如果两种情况删的一样多加起来即可，否则答案就是删的少的那个的方案数。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>

#define int long long
#define MOD 998244353

using namespace std;

int T;
int n;
char c[1000005];

int qpow(int x,int k)
{
    if(k==0)return 1;
    if(k==1)return x;
    int qp=qpow(x,k/2);
    qp*=qp;
    qp%=MOD;
    if(k&1)
    {
        qp*=x;
        qp%=MOD;
    }
    return qp;
}
int fac[1000005],inv[1000005];
int C(int n,int m)
{
    return (fac[n]*inv[m]%MOD)*inv[n-m]%MOD;
}
signed main()
{
    int i,j,k;
    inv[0]=fac[0]=1;
    for(i=1;i<=1000000;i++)
    {
        fac[i]=fac[i-1]*i%MOD;
        inv[i]=qpow(fac[i],MOD-2);
    }
    cin>>T;
    while(T--)
    {
        cin>>c+1;
        n=strlen(c+1);
        int res0=0,res1=0,f0=0,f1=1;
        for(i=1;i<=n;i++)
        {
            if(f0==c[i]-'0')res0++,f0=1-f0;
            if(f1==c[i]-'0')res1++,f1=1-f1;
        }
        int ans=1;
        if(res0>=res1)
        {
            int sum=1;
            int now=0;
            f0=0;
            for(i=1;i<=n;i++)
            {
                if(f0==c[i]-'0')f0=1-f0,sum*=C(now+1,now),sum%=MOD,now=0;
                else now++;
            }
            sum*=C(now+1,now),sum%=MOD;
            ans*=sum*fac[n-res0]%MOD;
            ans%=MOD;
        }
        if(res0<=res1)
        {
            int sum=1;
            int now=0;
            f1=1;
            for(i=1;i<=n;i++)
            {
                if(f1==c[i]-'0')f1=1-f1,sum*=C(now+1,now),sum%=MOD,now=0;
                else now++;
            }
            sum*=C(now+1,now),sum%=MOD;
            ans*=sum*fac[n-res1]%MOD;
            ans%=MOD;
        }
        cout<<n-max(res0,res1)<<' '<<ans<<endl;
    }
    return 0;
}

```


---

## 作者：BugGod (赞：0)

这个题共两问，我们先看第一问。

第一问要求使序列 01 相间的最少操作次数。那么我们就可以找出所有连续的仅包含 0 或 1 的串，把它们全部删为 1 个即可。

接下来再看第二问。显然，每个串在不同的操作序列中所要删除的内容都是不变的，所以要求操作序列的种类，只需要考虑操作的顺序。那么我们先考虑每个串中留下的，再考虑需要删除的字符的排列，即可。

**注意取模还有开 `long long`**

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//不开long long见祖宗
const int modd=998244353;
int t,a[200010],len=1,cnt,ans=1;
string s;
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>s;
		memset(a,0,sizeof(a));
		len=1;
		cnt=0;
		ans=1;
		for(int i=1;i<s.size();i++)
		{
			if(s[i-1]!=s[i])
			{
				a[++cnt]=len;//统计连续串
				len=1;
			}
			else len++;
		}
		a[++cnt]=len;
		cout<<s.size()-cnt<<" ";
		for(int i=1;i<=cnt;i++)ans=ans*a[i]%modd;//留下的
		for(int i=1;i<=s.size()-cnt;i++)ans=ans*i%modd;//删去的
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

对于第一个问题，直接搜出字符串中有多少个仅由 $0$ 或 $1$ 组成的串组成的。

对于第二个问题，每个串只有一个能选，然后选择顺序有所不同，具体看代码。

（二）

AC 代码。

```cpp#include<bits/stdc++.h>
#define int long long
#define md  998244353
using namespace std;
int t,s[200010];
char ch[200010];
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%s",ch+1);
		int len=strlen(ch+1);
		int sum=1,cnt=0,ans=1;
		for(int i=2;i<=len;i++){
			if(ch[i]!=ch[i-1]){
				s[++cnt]=sum;
				sum=1;
			}
			else sum++;
		}
		s[++cnt]=sum;
		printf("%lld ",len-cnt);
		for(int i=1;i<=len-cnt;i++)ans=ans*i%md;
		for(int i=1;i<=cnt;i++)ans=ans*s[i]%md;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

