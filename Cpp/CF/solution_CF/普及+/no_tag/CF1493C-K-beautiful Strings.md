# K-beautiful Strings

## 题目描述

You are given a string $ s $ consisting of lowercase English letters and a number $ k $ . Let's call a string consisting of lowercase English letters beautiful if the number of occurrences of each letter in that string is divisible by $ k $ . You are asked to find the lexicographically smallest beautiful string of length $ n $ , which is lexicographically greater or equal to string $ s $ . If such a string does not exist, output $ -1 $ .

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

In the first test case "acac" is greater than or equal to $ s $ , and each letter appears $ 2 $ or $ 0 $ times in it, so it is beautiful.

In the second test case each letter appears $ 0 $ or $ 1 $ times in $ s $ , so $ s $ itself is the answer.

We can show that there is no suitable string in the third test case.

In the fourth test case each letter appears $ 0 $ , $ 3 $ , or $ 6 $ times in "abaabaaab". All these integers are divisible by $ 3 $ .

## 样例 #1

### 输入

```
4
4 2
abcd
3 1
abc
4 3
aaaa
9 3
abaabaaaa```

### 输出

```
acac
abc
-1
abaabaaab```

# 题解

## 作者：little_sun (赞：3)

### 题目大意

给定两个整数 $n$ 和 $k$，和一个字符串 $s$，你需要求出字典序最小且大于 $s$ 的满足任意字符都出现了 $k$ 的倍数次的字符串 $t$。

多组数据， $n,k \leq 10^5$ 。

### 题目分析

首先我们可以特判掉 $ n \not\equiv 0 \pmod k $ 的情况，那接下来所有情况都是有解的。

因为要求字典序最小，故我们尝试从后往前枚举 $t$ 第一次大于 $s$ 的位置 $p$，并求出 $p$ 位置上取什么字符能够满足条件，这可以在 $ O(26n)$ 的时间内求出。

在求出了 $p$ 之后，由于$p$ 之后的位置可以任意放置，于是我们结合 $p$ 之前字符的出现情况，计算$[p+1,n]$的答案即可。

### 代码

``` cpp
#include <bits/stdc++.h>
 
#define R register
#define ll long long
#define sum(a, b, mod) (((a) + (b)) % mod)
#define meow(cat...) fprintf(stderr, cat)
 
const int MaxN = 1e5 + 10;
 
int n, k, cnt[27];
char s[MaxN], t[MaxN];
 
signed main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int ans = 0, spos = 0;
        scanf("%d%d%s", &n, &k, s + 1);
        if (n % k)
        {
            printf("-1\n");
            continue;
        }
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++)
            cnt[s[i] - 'a']++, t[i] = 0;
        memset(t, 0, n + 10);
        for (int i = 0; i < 26; i++)
            if (cnt[i] % k) ans = -1;
        if (~ans)
        {
            printf("%s\n", s + 1);
            continue;
        }
        ans = 1, spos = s[1] + 1;
        for (int i = n; i; i--)
        {
            int num = 0;
            cnt[s[i] - 'a']--;            
            if (s[i] == 'z') continue;
            for (int l = s[i] - 'a' + 1; l < 26; l++)
            {
                cnt[l]++, num = 0;
                for (int j = 0; j < 26; j++)
                   num += k * ((cnt[j] / k) + ((cnt[j] % k) != 0)) - cnt[j];
                if (num <= n - i)
                {
                    ans = i, spos = l;
                    break;
                }
                cnt[l]--;
            }
            if (ans == i) break;
        }
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i < ans; i++)
            t[i] = s[i], cnt[t[i] - 'a']++;
        t[ans] = spos + 'a', cnt[t[ans] - 'a']++;
        int pos = ans + 1, sum = 0;
        for (int i = 0; i < 26; i++)
            cnt[i] = k * ((cnt[i] / k) + ((cnt[i] % k) != 0)) - cnt[i], sum += cnt[i];
        while (sum + ans < n)
            sum += k, cnt[0] += k;
        for (int i = 0; i < 26; i++)
            for (int j = 0; j < cnt[i]; j++)
                t[pos] = i + 'a', ++pos;
        printf("%s\n", t + 1);
    }
    return 0;
} 
```

---

## 作者：ax_by_c (赞：1)

题目要求构造的串大于 $s$，仔细阅读题目发现长度其实是一样的，所以只能是前若干位等于并在某一位大于 $s$。

假设我们已经确定了一个前缀，那么我们如何快速判断它是否合法呢？记前缀中第 $i$ 个字符出现次数为 $cnt_i$，则我们至少需要改动 $L=\sum_{i=1}^{26}[cnt_i\bmod k\neq 0]k-cnt_i\bmod k$ 次。如果前缀长度为 $len$，则只要 $n-len\ge L$ 且 $(n-len-L)\bmod k=0$ 就能构造出合法解，否则不行。容易发现这个判断是 $O(\lvert S \rvert)$ 的。

于是从后往前枚举大于的那一位并动态更新 $cnt$，若找到合法解则对后面每一位都枚举一遍，即可找到最优解。若无法找到则无解。

时间复杂度 $O(n\lvert S \rvert^2)$。

---

## 作者：xuezhe (赞：1)

有解当且仅当 $k$ 是 $n$ 的因数。

首先判断 $s$ 本身是否可行。 

否则为了最小化答案 $t$ 字典序，倒序枚举 $i \in [1,n]$ 表示前 $i-1$ 位均相同，$t$ 在第 $i$ 位比 $s$ 大，从小到大枚举这一位填的字符，看一下后面的空位是否足以补足所有字母的需求。

单组时间复杂度 $O(n |\Sigma|)$，这里 $|\Sigma|=26$，表示字符集大小。 

```cpp
int T,n,k,c[26];
char s[100005];

void fakemain(){
    Read(T);
    while(T--){
        Read(n),Read(k),Read(s+1);
        if(n%k){
            puts("-1");
            continue;
        }
        memset(c,0,26<<2);
        for(int i=1;i<=n;++i)
            if((++c[s[i]-'a'])>=k)
                c[s[i]-'a']-=k;
        int o=0;
        for(int i=0;i<26;++i)
            if(c[i])
                o+=k-c[i];
        if(!o){
            puts(s+1);
            continue;
        }
        int flg=0;
        for(int i=n;i;--i){
            if(c[s[i]-'a'])
                o-=k-c[s[i]-'a'];
            if((--c[s[i]-'a'])<0)
                c[s[i]-'a']+=k;
            if(c[s[i]-'a'])
                o+=k-c[s[i]-'a'];
            for(int w=s[i]-'a'+1;w<26;++w){
                if(c[w])
                    o-=k-c[w];
                if((++c[w])>=k)
                    c[w]-=k;
                if(c[w])
                    o+=k-c[w];
                if(o<=n-i){
                    flg=1;
                    for(int j=1;j<i;++j)
                        putchar(s[j]);
                    putchar(w+'a');
                    vector<char> v;
                    for(int t=0;t<26;++t)
                        if(c[t])
                            for(int j=c[t];j<k;++j)
                                v.push_back('a'+t);
                    for(int j=v.size();j<n-i;++j)
                        putchar('a');
                    for(char j:v)
                        putchar(j);
                    break;
                }
                if(c[w])
                    o-=k-c[w];
                if((--c[w])<0)
                    c[w]+=k;
                if(c[w])
                    o+=k-c[w];
            }
            if(flg)
                break;
        }
        putchar(10);
    }
}
```

---

## 作者：7KByte (赞：1)

如果$k|n$，则一定有解，否则一定无解。前者，我们可以构造一个全 $\texttt{z}$ 的串；后者，所有字母出现次数为 $k$ 的倍数则 $n$ 也一定为 $k$ 的倍数。

首先我们判断原串是否满足条件，如果是则直接输出原串。

如果不是，则答案一定与原串不同，我们可以枚举第一个与原串不同位置。显然这个位置越后答案越优，所以我们倒叙枚举。

对于枚举当前位 $i$ ，我们再枚举第 $i$ 位上修改后的字符，注意不能与原串相同。那么第 $i$ 位之后可以任意填，我们只用 $\texttt{check}$ 一下后面的位数是否足够将前 $i$ 位出现次数不是 $k$ 的倍数的字母补齐。

如果能够补齐，则按$a\to z$ 的顺序顺次填充，如果还有多余位数，则在第$i$位之后用$\texttt{a}$补齐。

时间复杂度$\rm O(26N) $ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 100005
using namespace std;
int n,k,c[30];char s[N];
void calc(int x,int y){
	memset(c,0,sizeof(c));
	s[x]=y+'a';
	rep(i,1,x)c[s[i]-'a']++;
	int sum=n-x;
	rep(i,0,25)sum-=(k-c[i]%k)%k;
	rep(i,1,x)putchar(s[i]);
	rep(i,1,sum)putchar('a');
	rep(i,0,25)rep(j,1,(k-c[i]%k)%k)putchar('a'+i);
	putchar('\n');
}
void solve(){
	memset(c,0,sizeof(c));
	scanf("%d%d",&n,&k);
	scanf("%s",s+1);if(n%k){puts("-1");return ;}
	rep(i,1,n)c[s[i]-'a']++;
	int sum=0;
	rep(i,0,25)sum+=(k-c[i]%k)%k;
	if(!sum){
		puts(s+1);return ;
	}
	pre(i,n,1){
		sum-=(k-c[s[i]-'a']%k)%k;
		c[s[i]-'a']--;
		sum+=(k-c[s[i]-'a']%k)%k;
		rep(j,s[i]-'a'+1,25){
			int cur=sum;
			cur-=(k-c[j]%k)%k;
			c[j]++;
			cur+=(k-c[j]%k)%k;
			c[j]--;
			//cout<<i<<" "<<j<<" "<<cur<<endl;
			if(cur<=n-i){calc(i,j);return ;}
		}
	}
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[K-beautiful Strings CF1493C](https://www.luogu.com.cn/problem/CF1493C)

# 解题思路

首先，如果原字符串是合法的直接输出原字符串即可。

然后我们考虑一个最简单的暴力，你枚举第一个你构造的字符串比原串大的字符的位置，再枚举这个字符，然后后面的肯定是从后往前贪心放即可，在此不再赘述。

这样的复杂度是 $O(|S|^2 \times V^2)$ 的，其中 $V = 26$，$|S|$ 代表给定的字符串长度，这样的时间复杂度并不优秀，不能通过本题。

考虑你从后缀往前扫，维护一个桶，每次向前一个字符只需要使用 $O(1)$ 的时间复杂度修改，而从后缀往前扫，不难发现，这样构造出来的第一个字符串是一定最优的。

时间复杂度 $O(|S| \times C^2)$，可以通过此题。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
ll _t_;
void _clear(){}
ll n,m;
string s;
ll a[30];
ll pd;
string ans;
ll f(char x){
	return x-'a'+1;
}
void check(ll x,char y)
{
	a[f(y)]++;
	ll need=0;
//	forl(i,1,10)
//		cout<<a[i]<<' ';
//	cout<<endl;
	forl(i,1,26)
		need+=(m-a[i]%m)%m;
//	cout<<need<<' '<<n<<' '<<x<<endl;
	if(n-x<need)
	{
		a[f(y)]--;
		return ;
	}
	pd=1;
	ans="";
	forl(i,0,n)
		ans+=' ';
	forl(i,1,x-1)
		ans[i]=s[i];
	ans[x]=y;
	ll id=0;
	forr(i,n,x+1)
	{
		ll pd2=0;
		forr(j,26,1)
			if(a[j]%m)
			{
				a[j]++,ans[i]=j+'a'-1;
				pd2=1;
				break;
			}
		if(!pd2)
		{
			id=i;
			break;
		}
	}
	forl(i,x+1,id)
		ans[i]='a';
}
void solve()
{
	ans="",pd=0; 
	_clear();
	cin>>n>>m>>s;
	if(n%m)
	{
		cout<<-1<<endl;
		return ;
	}
	s=' '+s;
	forl(i,1,26)
		a[i]=0;
	forl(i,1,n)
		a[f(s[i])]++;
	forl(i,1,26)
	{
		if(a[i]%m)
			break;
		if(i==26)
		{
			for(auto j:s)
				if(j!=' ')
					cout<<j;
			cout<<endl;
			return ;
		}
	}
/**	a[f(s[4])]--;
	a[f(s[3])]--;
	a[f(s[2])]--;
	check(2,'c');*/
	forr(i,n,1)
	{
		a[f(s[i])]--;
		forl(j,s[i]+1,'z')
		{
			check(i,j);
			if(pd)
			{
				for(auto j:ans)
					if(j!=' ')
						cout<<j;
				cout<<endl;
				return ;
			}
		}
	}
}
int main()
{
	IOS;
	_t_=1;
 	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1493C 题解



## 思路分析

字符串下标从 $0$ 开始，记 $S[l\cdots r]$ 表示字符 $S_l\sim S_r$ 构成的子串。

观察到 $k\nmid n$ 时满足条件的字符串一定不存在，而对于 $k\mid n$ 的情况字符串 $\texttt{zzzzz}\cdots$ 一定满足条件。

若 $S$ 已经满足条件，直接输出 $S$ 即可。

为了让字典序尽量小，我们可以从大到小枚举 $\operatorname{lcp}(S,T)$ 的长度（$\operatorname{lcp}(S,T)$ 表示 $S,T$ 的最长公共前缀）。

对于每个前缀 $S[0\cdots i-1]$，我们可以维护每个字符出现的次数，由于每次只减少一个字符，因此单次更新是 $\Theta(1)$ 的。

接下来我们枚举 $T_i$ 的值，显然 $T_i>S_i$ 因此从 $S_i+1$ 枚举到 $\texttt z$，这个时候我们就确定了 $T[0\cdots i]$ 的值，而 $T[i+1\cdots n-1]$ 中的每个位置就都可以随便填了。

根据题意能够计算出 $T[i+1\cdots n-1]$ 中每个字符出现次数 $\bmod k$ 的余数，因此我们能得到最少需要多少个字符才能让每种字符的出现次数都是 $k$ 的倍数，而剩下的位置全填 $\texttt{a}$，然后从小到大排列字符，如果爆长度了返回无解。

记 $\alpha(S)$ 表示 $S$ 的字符集大小，我们判断 $T[i+1\cdots n-1]$ 是否有解是 $\Theta(\alpha (S))$ 的，而对于每个前缀，有 $\alpha(S)$ 个可能的 $T[0\cdots i]$ 需要判断 $T[i+1\cdots n-1]$ 是否有解，因此判断解的总复杂度为 $\Theta(n\alpha^2(S))$。

虽然构造一个 $T[i+1\cdots n-1]$ 的复杂度是 $\Theta(n)$ 的，但是只有有解的时候会进行构造，因此得到合法的 $T[i+1\cdots n-1]$ 只会进行一次。

综上所述，总时间复杂度为 $\Theta(n\alpha^2(S))$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
inline bool check(vector<int> cnt) {
	for(int i=0;i<26;++i) if(cnt[i]!=0) return false;
	return true;
}
inline string construct(vector<int> cnt,int n) {
	int sum=0;
	for(int i=0;i<26;++i) sum+=cnt[i];
	if(sum>n) return "! Construction Failed";
	assert((n-sum)%k==0);
	cnt[0]+=n-sum;
	string ret;
	for(char ch='a';ch<='z';++ch) {
		for(int i=1;i<=cnt[ch-'a'];++i) ret.push_back(ch);
	}
	return ret;
}
inline void solve() {
	string S;
	cin>>n>>k>>S;
	if(n%k!=0) {
		puts("-1");
		return ;
	}
	vector <int> cnt(26);
	for(int i=0;i<n;++i) cnt[S[i]-'a']=(cnt[S[i]-'a']+1)%k;
	if(check(cnt)) {
		cout<<S<<"\n";
		return ;
	}
	for(int i=n-1;i>=0;--i) {
		cnt[S[i]-'a']=(cnt[S[i]-'a']+k-1)%k;
		vector <int> tmp(26);
		for(int i=0;i<26;++i) tmp[i]=(k-cnt[i])%k;
		for(char ch=S[i]+1;ch<='z';++ch) {
			tmp[ch-'a']=(tmp[ch-'a']+k-1)%k;
			string ret=construct(tmp,n-i-1);
			if(ret=="! Construction Failed") {
				tmp[ch-'a']=(tmp[ch-'a']+1)%k;
				continue;
			}
			string T;
			T=S.substr(0,i)+ch+ret;
			cout<<T<<"\n";
			return ;
		}
	}
	puts("-1");
}
signed main() {
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```



---

## 作者：snnu_lgw (赞：0)

### Description

- 给定两个正整数 $n$ 和 $k$，和一个字符串 $s$，其中 $n$ 为字符串 $s$ 的长度。
- 给定 K-beautiful 的含义：字符串 $s$ 中每个小写字母出现的次数都能被 $k$ 整除。
- 求满足 K-beautiful 的字典序最小的字符串 $t$，且 $t$ 的字典序要大于等于 $s$ 的字典序。
- 多组输入，$1 \le k \le n  \le 10^5$。

### Solution

如果 $k$ 无法整除 $n$，显然解是不存在的，输出 $-1$。

设 $cnt[i]$ 表示每个小写字母在 $s$ 中出现的次数，其中 $0 \le i <26$。如果当前每个 $cnt[i]$ 为 $0$ 或者可以被 $k$ 整除，即 $s$ 符合条件，故直接输出 $s$ 即可。

如果上述条件均不符合，那么就开始逐字符修改 $s$，直到其可以满足条件且一定可以修改到满足条件的状态。因为要求字典序在大于等于 $s$ 的前提下最小，所以就需要倒序枚举 $s$ 的每个字符。

设当前枚举的字符的位置为 $pos$（$0 \le pos \le n-1$），要逐渐增大 $pos$ 位置的字符，前面的字符不能变，后面的字符已经暂时被删除了，即可以任意放置字符。现在要计算 $pos$ 及以前的字符要达到 K-beautiful 还需要后面提供多少个位置（设为 $sum$），如果 $sum \le n-pos-1$，则可以满足条件，把还需要的字符输出即可。

注意如果 $pos$ 及其前面的字符出现的次数已经是 $k$ 的倍数，则需要把 $pos$ 后面的位置按需求输出字符 $a$ 即可。

### Code

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int cnt[30];

int main()
{
	int t; cin>>t;
	while(t--)
	{
		int n, k; cin>>n>>k;
		string s;
		cin>>s;
		if(n%k){
			cout<<-1<<endl;
			continue;
		}	
		memset(cnt,0,sizeof(cnt));
		for(int i=0;i<n;i++)
			cnt[s[i]-'a']++;
		
		bool p = 1;
		for(int i=0;i<26;i++)
			if(cnt[i]%k!=0){
				p = 0;
				break;
			}
		if(p){
			cout<<s<<endl;
			continue;
		}	
		
// 前面的字符不能修改, pos位置之后的可以任意变动，因为已经把它们都删除掉了 
		int pos = 0, ch = -1;
		for(int i=n-1;i>=0;i--)
		{
			cnt[s[i]-'a']--;
			if(s[i]=='z') continue; //如果是'z',显然无法继续变大了 
			int now = s[i]-'a';
			for(int j=now+1;j<=26;j++)
			{
				cnt[j]++; 
				int num = 0;
				for(int t=0;t<26;t++)
				{
					if(cnt[t]%k==0)
						continue;
					num = num + (cnt[t]/k+1)*k-cnt[t];
				}
				if(num<=n-i-1)
				{
					pos = i;
					ch = j;
					break;
				}
				cnt[j]--;
			}
			if(pos==i)
				break;
		}
		
		for(int i=0;i<pos;i++)
			cout<<s[i];
		cout<<char(ch+'a');
		int sum = 0;
		for(int i=0;i<26;i++)
		{
			if(cnt[i]%k==0)
				cnt[i] = 0;
			else 
				cnt[i] = (cnt[i]/k+1)*k-cnt[i];
				
			sum+=cnt[i];
		}
		while(sum<n-pos-1)
		{ 
			sum += k;
			cnt[0]+=k;
		}
		for(int i=0;i<26;i++)
			for(int j=0;j<cnt[i];j++)
				cout<<char(i+'a');
		cout<<endl;
	} 
	return 0;
}
```



---

## 作者：OranJun (赞：0)

## $Solution$

看到字典序，我们考虑让这个字符串前缀匹配最多之后，再在下一位比原字符串大。

那么问题转化为如何在某一个前缀的位置判断剩下来的空是否合法。

考虑记一个字符的前缀和，设在 $i\in[1,pos]$ 中 $j$ 出现了 $b[pos[[j]$ 次，那么在 $[pos+1,n]$ 处，就要出现 $k-b[pos][j]\bmod k $ 次 。

注意可能会出现空位，这时我们要用 $'a'$ 来填充

接下来大力分类讨论

### 1.不够填完这些数
 
此时无解 $return$

### 2.够填完这些数，并且 $s[pos+1]+1$ 是要填的

那么比原串字典序大并且字典序最小的，一定在 $pos+1$ 位填了 $s[pos+1]+1$。

### 3.够填完这些数，$s[pos+1]+1$不需要填，并且有空余的位置

那么如果空余的位置 $ky\  \bmod k >0$时，无解。 

否则我们可以考虑下一位用空余的位置把 $s[pos+1]+1$ 填进去，同时在桶中记录下这个字符的变化情况。

注意如果 $ ky>k $ ，那么我们只需要填 $k$ 个 $s[pos+1]+1$， 剩下的留给$'a'$ 。

### 4.只够填完这些数

那么我们找到第一个大于 $s[pos]$ 并且需要填的数，填进去，剩下的按照字典序来填就好了


```cpp
#include<bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i=a;i<=b;++i)
#define rf(i,a,b) for(int i=a;i>=b;--i)
template<typename T>
inline void read(T &x){
	char c=getchar();x=0;bool f=0;
	while(!isdigit(c))f|=(c=='-'),c=getchar();
	while(isdigit(c))x=x*10+(c^48),c=getchar();
	x=f?-x:x;
}
typedef long long ll;
const int N=1e5+5;
char s[N];
int b[N][26];
int n,k;
bool check(int pos){
	ll sum=0;
	fr(i,0,25)if(b[pos][i]%k)sum+=k-b[pos][i]%k;//前面要补上的 
	
	if(sum>n-pos)return 0;//如果凑不齐 
	
	if(pos==n){//原串满足条件就直接输出
		if(sum)return 0;
		fr(i,1,n)printf("%c",s[i]);
		puts("");
		return 1;
	}
	
	int pd=0;
	fr(i,s[pos+1]-'a'+1,25)if(b[pos][i]>0&&b[pos][i]%k){pd=i;break;}//看下一位有没有比他大的 
	
	int ky=n-pos-sum;
	if(ky%k||s[pos+1]=='z')return 0;//如果下一位找不到比它大的或者空余的位置不合法
	if(b[pos][s[pos+1]+1-'a']%k){//可用加一就加一 
			++b[pos][s[pos+1]+1-'a'];
			fr(i,1,pos)printf("%c",s[i]);
			printf("%c",s[pos+1]+1);
			fr(i,1,ky)putchar('a');
			fr(i,0,25)if(b[pos][i]%k){
				fr(j,1,k-b[pos][i]%k)printf("%c",'a'+i);
			}
			puts("");
			return 1;
	}
	if(ky){//用多余的位置来加一的 
			b[pos][s[pos+1]+1-'a']++,ky-=k;
			fr(i,1,pos)printf("%c",s[i]);
			printf("%c",s[pos+1]+1);
			fr(i,1,ky)putchar('a');
			fr(i,0,25)if(b[pos][i]%k){
				fr(j,1,k-b[pos][i]%k)printf("%c",'a'+i);
			}
			puts("");
			return 1;
	}
	if(pd){//只能用比较大的 
		++b[pos][pd];
		fr(i,1,pos)printf("%c",s[i]);
		printf("%c",'a'+pd);
		fr(i,0,25)if(b[pos][i]%k){
			fr(j,1,k-b[pos][i]%k)printf("%c",'a'+i);
		}
		puts("");
		return 1;
	}
	return 0;
}
void solve(){
	read(n),read(k);
	fr(i,0,n)fr(j,0,25)b[i][j]=0; 
	cin>>s+1;
	if(n%k){
		puts("-1");
		return;
	}
	fr(i,1,n){
		fr(j,0,25)b[i][j]=b[i-1][j];
		++b[i][s[i]-'a']; 
	}
	rf(i,n,1){//倒序判断满足条件就可以退出
		if(check(i))
			return;
	}
    
	if(s[1]=='z'){//这种情况是前缀长度为0
             //那么我们用k个s[1]+1再加上n-k个a就可以了
		puts("-1");
		return;
	}
	++b[0][s[1]+1-'a'];
	printf("%c",s[1]+1);
	fr(i,1,n-k)putchar('a');
	fr(i,1,k-1)printf("%c",s[1]+1);
	puts(""); 
}
int main(){
	int T;
	read(T);
	while(T--){
		solve(); 
	}
}

---

