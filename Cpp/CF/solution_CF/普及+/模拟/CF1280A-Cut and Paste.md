# Cut and Paste

## 题目描述

We start with a string $ s $ consisting only of the digits $ 1 $ , $ 2 $ , or $ 3 $ . The length of $ s $ is denoted by $ |s| $ . For each $ i $ from $ 1 $ to $ |s| $ , the $ i $ -th character of $ s $ is denoted by $ s_i $ .

There is one cursor. The cursor's location $ \ell $ is denoted by an integer in $ \{0, \ldots, |s|\} $ , with the following meaning:

- If $ \ell = 0 $ , then the cursor is located before the first character of $ s $ .
- If $ \ell = |s| $ , then the cursor is located right after the last character of $ s $ .
- If $ 0 < \ell < |s| $ , then the cursor is located between $ s_\ell $ and $ s_{\ell+1} $ .

We denote by $ s_\text{left} $ the string to the left of the cursor and $ s_\text{right} $ the string to the right of the cursor.

We also have a string $ c $ , which we call our clipboard, which starts out as empty. There are three types of actions:

- The Move action. Move the cursor one step to the right. This increments $ \ell $ once.
- The Cut action. Set $ c \leftarrow s_\text{right} $ , then set $ s \leftarrow s_\text{left} $ .
- The Paste action. Append the value of $ c $ to the end of the string $ s $ . Note that this doesn't modify $ c $ .

The cursor initially starts at $ \ell = 0 $ . Then, we perform the following procedure:

1. Perform the Move action once.
2. Perform the Cut action once.
3. Perform the Paste action $ s_\ell $ times.
4. If $ \ell = x $ , stop. Otherwise, return to step 1.

You're given the initial string $ s $ and the integer $ x $ . What is the length of $ s $ when the procedure stops? Since this value may be very large, only find it modulo $ 10^9 + 7 $ .

It is guaranteed that $ \ell \le |s| $ at any time.

## 说明/提示

Let's illustrate what happens with the first test case. Initially, we have $ s =  $ 231. Initially, $ \ell = 0 $ and $ c = \varepsilon $ (the empty string). The following things happen if we follow the procedure above:

- Step 1, Move once: we get $ \ell = 1 $ .
- Step 2, Cut once: we get $ s =  $ 2 and $ c =  $ 31.
- Step 3, Paste $ s_\ell =  $ 2 times: we get $ s =  $ 23131.
- Step 4: $ \ell = 1 \not= x = 5 $ , so we return to step 1.
- Step 1, Move once: we get $ \ell = 2 $ .
- Step 2, Cut once: we get $ s =  $ 23 and $ c =  $ 131.
- Step 3, Paste $ s_\ell =  $ 3 times: we get $ s =  $ 23131131131.
- Step 4: $ \ell = 2 \not= x = 5 $ , so we return to step 1.
- Step 1, Move once: we get $ \ell = 3 $ .
- Step 2, Cut once: we get $ s =  $ 231 and $ c =  $ 31131131.
- Step 3, Paste $ s_\ell =  $ 1 time: we get $ s =  $ 23131131131.
- Step 4: $ \ell = 3 \not= x = 5 $ , so we return to step 1.
- Step 1, Move once: we get $ \ell = 4 $ .
- Step 2, Cut once: we get $ s =  $ 2313 and $ c =  $ 1131131.
- Step 3, Paste $ s_\ell =  $ 3 times: we get $ s =  $ 2313113113111311311131131.
- Step 4: $ \ell = 4 \not= x = 5 $ , so we return to step 1.
- Step 1, Move once: we get $ \ell = 5 $ .
- Step 2, Cut once: we get $ s =  $ 23131 and $ c =  $ 13113111311311131131.
- Step 3, Paste $ s_\ell =  $ 1 times: we get $ s =  $ 2313113113111311311131131.
- Step 4: $ \ell = 5 = x $ , so we stop.

At the end of the procedure, $ s $ has length $ 25 $ .

## 样例 #1

### 输入

```
4
5
231
7
2323
6
333
24
133321333
```

### 输出

```
25
1438
1101
686531475
```

# 题解

## 作者：ZLCT (赞：3)

# CF1280A Cut and Paste
## 题意简述
给定一个由 $1,2,3$ 组成的字符串 $s$ 和操作次数 $x$。初始有一个 $l$ 指向第一个字符，每次操作都把字符串 $(l,|s|]$ 区间在字符串末尾复制 $s_i-1$ 遍。求最终字符串长度。
## 困难数学题 $\times$ 简单暴力题 $\checkmark$
刚看到题会觉得这题需要类似于等比数列之类的思想，结果一看数据范围发现 $x\le10^6$。\
那这不就简单了吗？\
我们只需要把 $x$ 次操作都暴力跑出来不就好了吗？\
但是我们发现如果 $s_i$ 全都是 $3$，那么字符串长度是指数级别的。\
发现我们最终其实只需要求出字符串长度，而有关我们字符串操作的其实只有前 $x$ 个字符。所以我们完全可以只记录前 $x$ 个字符，其余只记录其所贡献的长度即可。\
需要注意的一点是我们不能判断 $ans$ 是否小于 $x$，因为在取模以后可能数值变小。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int x,a[1123456];
string s;
int ans,len;
void solve(){
    cin>>x>>s;
    len=s.size();ans=len;
    for(int i=0;i<len;++i){
        a[i]=s[i]-'0';
    }
    for(int i=0;i<x;++i){
        ans+=(a[i]-1)*(ans-i-1)%mod;
        ans%=mod;
        int slen=len;
        for(int j=1;j<a[i]&&len<x;++j){
            for(int k=i+1;k<slen&&len<x;++k){
                a[len++]=a[k];
            }
        }
    }
    cout<<(ans+mod)%mod<<'\n';
    return;
}
signed main(){
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：万弘 (赞：1)

[本场比赛完整题解](https://www.luogu.com.cn/blog/c2522943959/cf1281round-607-div-2-ti-xie)

### C - Cut and Paste
给一个串$s$(下标从1到$n)$,和一个变量$it$,初始为$0$.要你执行$x$次操作,求最后的串长度对$10^9+7$取模的结果.  
操作如下:  
1. 将$it+1$  
2. 将剪贴板的内容替换为$[it,n]$($n$是当前的串的长度),并在原串中删除$[it,n]$
3. 在串的末尾把剪贴板内容粘贴$s_{it}$次

$x\le 10^6$,原串长度$\le 500$  

这题的做法是非常显然的:  
因为$it$不会移动到$x$之后,也就是对于$x$之后的部分,我们只需要关心长度,而不需要关心具体的$s_i$

长度如何算?设当前的串长是$ans$,则
$$ans=(ans+((ans-it-1+mod)\%mod)*(s[i]-'1'))\%mod$$

~~好像有点丑~~写成代码就是`ans=(ans+((ans-i-1+mod)%mod)*(s[i]-'1'))%mod;`
就是把后面的部分复制`s[i]-'1'`次.

如果在$x$之前,直接暴力,因为$x\le 10^6$所以这样做时间复杂度$O(x)$是不会TLE的.
```cpp
/**********/
str s;
const ll mod=ll(1e9+7);
int main()
{
	ll task=read();
	while(task--)
	{
		ll x=read(),ans=0;
		std::cin>>s;
		ans=s.size();
		for(ll i=0;i<x;++i)
		{
			if(s.size()>=x)//这里不能写ans,因为ans取模之后可能变小了
			{
				ans=(ans+((ans-i-1+mod)%mod)*(s[i]-'1'))%mod;
			}
			else
			{
				if(s[i]=='2')s+=s.substr(i+1);
				if(s[i]=='3')s+=s.substr(i+1)+s.substr(i+1);//暴力
				ans=s.size();
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

## 思路

一看到这道题，又以为是个~~暴力~~困难的要加奇怪的优化的题。

然后看到了数据范围：$x \leq 10^6$！

那这不是大水题吗！做法也就了然了：每次看一下复制的操作，因为要用到前 $x$ 个字符，所以每次判断，如果复制之后 $|s| \leq x$，就复制；否则记录它将来也不会更新，是没用的。

这样的话时间复杂度大概是 $O(nk)$，其中 $k$ 为玄学常数，因为 string 太慢了，所以会在极限数据 T 上天。因此，我们要优化一下。发现当 $s_i = 1$ 的时候，相当于做无用功，只要跳过即可。然后就愉快的 AC 了此题。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=1e9+7;
string s;
int main()
{
	int T,x; scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&x); cin>>s;
		s=' '+s;
		int it=1;
		ll nowlen=s.size();
		for(register int i=1;i<=x;i++)
		{
			it++;
			int t=s[it-1]-48;
			if(t==1) continue;
			if(s.size()<=x+1)
			{
				string s1="";
				for(register int j=it;j<s.size();j++) s1+=s[j];
				for(register int i=1;i<t;i++)
				{
					s+=s1;
					if(s.size()>x+1) break;
				}
			}
			ll tmp=nowlen-(ll)it;
			nowlen=(nowlen+tmp*(ll)(t-1)%mod)%mod;
		}
		printf("%lld\n",(nowlen-1ll+mod)%mod);
	}
	
	return 0;
}
```

---

## 作者：YLWang (赞：0)

我们不妨考虑转化思路。

显然，如果完全暴力枚举，串的长度成指数级增长。

但因为我们只要对前 $x$ 个数操作，于是我们就只暴力出前 $x$ 个数，复杂度$O(x)$。对于剩下的直接扩展长度，而不用维护出扩展了多少。

注意一下空间问题，最好使用$vector$或者$string$，省得RE

再注意一下负数取模问题就可以AC了

```cpp
#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define ll long long
#define int long long
#define reaD() read()
#define pb push_back
#define mkp make_pair
#define mst(a,b) memset(a,b,sizeof(a))
#define foR(i, k, j) for(register int i = (k); i >= (j); i--)
#define For(i, k, j) for(register int i = (k); i <= (j); i++)
#define DEBUG fprintf(stderr, "***IAKIOI***\n")
#define CDEBUG cerr << "***IAKIOI***" << endl;
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
const int MOD = 1000000007; //
using namespace std;
inline void ckmax(int &a, int b) {a = max(a, b);}
inline void ckmin(int &a, int b) {a = min(a, b);}
inline void addmod(int &a, int b) {int t = a + b; a = (t >= MOD ? t - MOD : t); }
inline int read() {
    int num=0,flag=1;char c=' ';
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag=-1;
    for(;c>='0'&&c<='9';num=num*10+c-48,c=getchar());
    return num*flag;
}
int x;
string s;
signed main()
{
	IOS;
	int T; cin >> T; 
	while(T--) {
		cin >> x >> s; s = ' ' + s;
		int n = s.size()-1, i = 1;
		for(; i <= x; i++) {
			if(n > x) break;
			if(s[i] - '0' == 2) {
				string t = s.substr(i+1);
				s += t;
			} else if(s[i] - '0' == 3) {
				string t = s.substr(i+1);
				s += t; s += t;
			}
			n = s.size()-1;
		}
		for(; i <= x; i++) {
			if(s[i] - '0' == 2) {
				n += (n - i);
			} else if(s[i] - '0' == 3) {
				n += (n - i) * 2;
			}
			n %= MOD;
			n = (n + MOD) % MOD; 
		}
		cout << (n % MOD + MOD) % MOD << endl;
	} 
    return 0;
}
```

---

