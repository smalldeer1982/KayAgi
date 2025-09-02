# Palindrome Pairs

## 题目描述

After learning a lot about space exploration, a little girl named Ana wants to change the subject.

Ana is a girl who loves palindromes (string that can be read the same backwards as forward). She has learned how to check for a given string whether it's a palindrome or not, but soon she grew tired of this problem, so she came up with a more interesting one and she needs your help to solve it:

You are given an array of strings which consist of only small letters of the alphabet. Your task is to find how many palindrome pairs are there in the array. A palindrome pair is a pair of strings such that the following condition holds: at least one permutation of the concatenation of the two strings is a palindrome. In other words, if you have two strings, let's say "aab" and "abcac", and you concatenate them into "aababcac", we have to check if there exists a permutation of this new string such that it is a palindrome (in this case there exists the permutation "aabccbaa").

Two pairs are considered different if the strings are located on different indices. The pair of strings with indices $ (i,j) $ is considered the same as the pair $ (j,i) $ .

## 说明/提示

The first example:

1. aa $ + $ bb $ \to $ abba.

The second example:

1. aab $ + $ abcac $ = $ aababcac $ \to $ aabccbaa
2. aab $ + $ aa $ = $ aabaa
3. abcac $ + $ aa $ = $ abcacaa $ \to $ aacbcaa
4. dffe $ + $ ed $ = $ dffeed $ \to $ fdeedf
5. dffe $ + $ aade $ = $ dffeaade $ \to $ adfaafde
6. ed $ + $ aade $ = $ edaade $ \to $ aeddea

## 样例 #1

### 输入

```
3
aa
bb
cd
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6
aab
abcac
dffe
ed
aa
aade
```

### 输出

```
6
```

# 题解

## 作者：yijan (赞：5)

 至少截止现在（2018.9.23）这题竟然是个黑题。。
 
 但这个大概就是黄+/绿-的水平吧。。
 
 进入正题。
 
####  题目给了你$n$个字符串，求取出两个后这两个可以组成一个回文串的个数。（可以任意打乱顺序）

对于暴力很好想，n^2大概就是枚举两个字符串看每种小写字母的出现次数如果最多只有一个字符出现了奇数个就可以。但是ACM赛制+1e5数据显然是不行的。

考虑对于一个字符串 aabccd 其实等价于 bd 因为aa和bb在与其他串组合后有与没有无区别。所以对于每个串，对于a,b,c,d,..z这26个字符只有两种情况   
1. 出现了  
2. 没有出现

所以说对于每个串可以看成一个26位二进制串。然后考虑从1到n每个串进行枚举，对于当前串我们只需要判断当前第i个串和i前面的所有串有哪些可以构成回文。对于两个串可以构成回文又两种情况：

两个串用二进制表示下相等。也就是说每一个字符集都是要么两边各有一个，要么两边都没有。

第i个串去掉一个字符（把一个位上1变成0后）两个串相等，相当于中间有个字符的回文串。


这时候我们只需要把前面所有的二进制存入一个hash表（打cf实现时为了方便直接用unordered_map）然后判断。由于需要对所有位的1进行去掉的尝试，复杂度O(nlogn)

代码实现还有些细节需要注意！ 

Accode
```cpp
#pragma GCC optimize ("O3")
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "unordered_map"
using namespace std;
typedef long long ll;
unordered_map<ll,ll> S;
#define MAXN 1000007
ll num[MAXN];
ll n;ll A[26],res;
int main(){
    cin >> n;getchar();
    for(ll i=0;i<n;++i){
        static char ch;
        memset(A,0,sizeof A);
        while(ch = getchar())
            if(ch!='\n')++A[ch-'a'];
            else break;
        for(ll j=0;j<26;++j)
            num[i] |= ((A[j]%2)<<j);
    }
    sort(num,num+n);
    for(ll i=0;i<n;++i){
        res += S[num[i]];
        for(ll j=0;j<26;++j)
            if((num[i]>>j)&1) res += S[num[i]^(1<<j)];
        ++S[num[i]];
    }
    cout << res;
}
```

---

## 作者：mrsrz (赞：3)

回文串的话，最多存在1个字母的出现次数为奇数。

所以对于每个给定的串，只要求出有哪些串出现了奇数次即可。偶数次的显然可以对消掉。而奇数次的也只用保留1个。

我们可以把小写字母映射成26位二进制中的每一位，则对于每个串，枚举它的字母，然后异或。最后得到的二进制数就恰好为出现奇数次的字母组成的。

然后，一遍扫过来，用一个桶记录每个状态的出现次数。

满足条件的回文串的状态中最多有1个1，对每个回文状态，查询桶内和当前状态$a_i$异或后能变成回文状态的数的个数即可。

$2^{26}$的int数组恰好占了256MB，所以可以用map代替，时间复杂度多个$\log$。也可以用unordered_map。

代码奇短。

## Code：
```cpp
#include<map>
#include<cstdio>
#include<iostream>
std::map<int,int>b;
int a[100005],n;
char s[1000005];
long long ans=0;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%s",s);
		int&f=a[i];
		for(int t=0;s[t];++t)f^=1<<(s[t]-'a');
	}
	b[a[1]]=1;
	for(int i=2;i<=n;++i){
		ans+=b[a[i]];
		for(int j=0;j<26;++j)ans+=b[a[i]^(1<<j)];
		++b[a[i]];
	}
	std::cout<<ans;
	return 0;
}
```

---

## 作者：lzyqwq (赞：2)

**[洛谷](https://www.luogu.com.cn/problem/CF1045I) [CF](https://codeforces.com/contest/1045/problem/I)**

> - 给出 $n$ 个由小写字母组成的字符串 $s_1\sim s_n$，求有多少个无序对 $(i,j)\,(i<j)$，满足将 $s_i$ 和 $s_j$ 拼接后，所得字符串重排后是回文串。
>
> - $n\le 10^5$，$\sum\limits_{i=1}^n s_i\le 10^6$。

首先考虑怎样的字符串重排后能得到回文串，其必满足出现奇数次的字符至多有一种。

$|\Sigma|=26$ 很小，考虑使用 $26$ 位的二进制数 $msk_i$ 描述 $s_i$ 每一种字符出现个数的奇偶性。不难发现这样描述的状态可以**结合**。

考虑枚举 $j$，枚举可以和 $s_j$ 构成回文串的状态 $S$，开一个桶 $mp$ 维护当前每个状态有多少种，则 $S$ 与 $j$ 的贡献为 $mp_S$。

时间复杂度为 $\mathcal{O}(|\Sigma|\cdot n+\sum_{i=1}^n |s_i|)$，空间复杂度为 $\mathcal{O}(n+\sum_{i=1}^n |s_i|)$。

**[提交记录（含代码）](https://codeforces.com/contest/1045/submission/230782539)**

---

## 作者：Adchory (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1045I)。

## 思路

当两个串的组合中存在一种排列使得该排列所形成的字符串为回文串，仅当两个串组合字符串中至多只有一个字符出现次数为奇数次，由于运算只涉及奇偶性，不妨考虑状态压缩，记 $S_i$ 表示 $i$ 状态下字符串的个数（$1$ 表示这个位置上的字符出现次数为奇数，$0$ 则反之），那么两个状态 $i,j$ 组成的串为合法串当且仅当 $\operatorname{popcount}(i\oplus j)\le 1$，其贡献为 $S_{i}\times S_{j}$。

然后我们枚举 $i$，根据 $\operatorname{popcount}(i\oplus j)\le 1$ 我们可以很轻松的得到 $j$，然后加上它们两个的贡献即可。

注意，本题卡空间，因此我们需要使用 `map`，当然这会使时间复杂度多一只 $\log$，不过没有关系。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=1e5+7;
int n,f[Maxn],b[27];
ll ans;
map<int,int>S;
string s;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>s;
		for(int j=0;j<26;j++) b[j]=0;
		for(int j=0;j<s.size();j++) b[s[j]-'a']++;
		for(int j=0;j<26;j++) if(b[j]&1) f[i]^=(1<<j);
		S[f[i]]++;
	}
	for(auto i:S){
		int x=i.second;
		int k=i.first; 
		ans+=1ll*x*(x-1)/2;
		for(int j=0;j<26;j++) 
			if(k>>j&1){
				ans+=1ll*S[k]*S[k^(1<<j)];
			}
	}
	printf("%lld",ans);
	return 0;
}



```


---

## 作者：Wei_Han (赞：0)

排列是回文的，说明排列后的字符串最多只有一种字母出现的次数是奇数，这样对我们有用的只有串内每一种字母的奇偶性，我们只需要记录那些出现奇数次的字母即可，然后扔进 ```map``` 里，把删掉偶数之后是空串的数量记录下来，然后考虑一个字符串删除一位和别的拼，或者和自己拼起来的种类数，再加和即可。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define pr putchar('\n')
#define pp putchar(' ')
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(ll i = a ; i >= b ; -- i )
//#pragma GCC optimize(2)
using namespace std;
typedef long long ll;
typedef __uint128_t ui128;
typedef __int128 i128;
typedef unsigned long long ull;
const int N=2e6+10;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}

ll n,sum1,sum2,sum3;
map<string,ll> mp,vis;
queue<string> q;
signed main(){
	read(n);
	fo(1,i,n){
		string s,t="";cin>>s;
		ll viss[27]={0},flag=0;
		fo(0,j,s.size()-1) viss[s[j]-'a']^=1;
		fo(0,j,25) if(viss[j]) flag=1,t=t+char(j+'a');
		sort(t.begin(),t.end());
		if(!flag) sum1++;else mp[t]++,q.push(t);
	}
	while(!q.empty()){
		string s=q.front();
		q.pop();
		if(vis[s]) continue;
		vis[s]=1;sum3+=(mp[s]*(mp[s]-1))/2;
		if(s.size()==1){sum3+=sum1*mp[s];continue;}
		fo(0,i,s.size()-1){
			string ss=s;
			s.erase(i,1);
			sum2+=mp[ss]*mp[s];
			s=ss;
		}
	}
	wr(sum1*(sum1-1)/2+sum2+sum3);
	return 0;
}	
``````

---

## 作者：codwarm (赞：0)

[题目传送门~](https://www.luogu.com.cn/problem/CF1045I)

## 题目分析
首先得出两个串加在一起构成回文的要求：**最多只有 $1$ 个字母总共有奇数个**。

想也很好想，同个字母两两对应，对应不了的那个放中间就行。

然后我们发现每个字符串只需要存储每个字母的数量的奇偶性 $0,1$ 两个量，很容易想到用一个 $26$ 位二进制来存字符串。

满足要求的对数可以分成两种情况考虑：

1. 每个字母总共都是偶数个。

观察下列式子：$0+0=0,1+1 = 2$

可以发现只有二进制数相等的两个字符串可以构成这种情况，开一个数组记录每个二进制数的个数。然后这其中任选两个都能构成回文，即贡献为 $C_{n}^{2}$。


2. 有且仅有一个字母为奇数个。

也很容易得出两个字符串的二进制仅有一个位不同。那么也只需要开一个哈希记录每一个二进制数可以被“匹配”的数量（“匹配”即为仅有一个位不同）。然后贡献为每个字符串对应的二进制数被“匹配”的个数。

最后答案为上述两种情况的和。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
unordered_map<long long,long long> mp,ct;
vector<long long> v;
long long n,x,res;
int main()
{
	scanf("%lld",&n);
	for (int e = 1;e <= n;e++)
	{
		x = 0;//将字符串存为一个二进制数
		string s;cin >> s;
		for (int i = 0;i < s.size();i++) x ^= (1 << (s[i]-'a'));//存第s[i]位
		v.push_back(x);
		for (int i = 0;i < 26;i++) 
			if (((x >> i) & 1) == 0) 
				ct[(x+(1 << i))]++; //第i位不同的匹配
		mp[x]++; 
	}
	for (auto e:mp) res += e.second*(e.second-1)/2; //偶数的情况贡献为cn2
	for (auto t:v) res += ct[t]; // 可以被匹配
	cout << res <<endl;
	return 0;
}
```



---

## 作者：HomuraCat (赞：0)

一道乱搞题

根据字符出现的奇偶性，我们可以将一个字符串化成一个$26$元组，并且每个字符用$0/1$表示这个元素出现偶数$/$奇数次，可以直接表示成一个$26$位的二进制数

然后所谓匹配就是两个数的海明距离$<=1$，直接将这些数暴力排序，海明距离$=0$就是找有多少个相等的数，$=1$每次枚举改变一位然后去所有数字里找就行，可以一个$upper\_bound$和$lower\_bound$一气呵成，详见代码

时间复杂度$O(26nlogn)$

```cpp
#include<bits/stdc++.h> 
#define fo(i, a, b) for (int i = (a); i <= (b); ++i)
#define fd(i, a, b) for (int i = (a); i >= (b); --i)
#define edge(i, u) for (int i = head[u], v = e[i].v; i; i = e[i].nxt, v = e[i].v)
#define pb push_back
#define F first
#define S second
#define ll long long
#define inf 1000000007
#define mp std::make_pair
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mod 998244353
#define eps 1e-4
#define lowbit(x) (x & -x)
#define N 100005
int n;
int head[N], tot, a[N], u[N];
struct node{
    int nxt, v, cnt;
}e[N << 1];
int tmp[26];
char ch;
ll ans;
inline void read (int &x)
{
    memset(tmp, 0, sizeof tmp);
    ch = getchar();
    while (!isalpha(ch)) ch = getchar();
    while (isalpha(ch)) ++tmp[ch - 'a'], ch = getchar();
    fo (i, 0, 25) x = (x << 1) | (tmp[i] & 1);
}
int now, x;
int main ()
{
    scanf("%d", &n);
    fo (i, 1, n) { read(a[i]); u[i] = a[i]; }
    std::sort(u + 1, u + n + 1);
    fo (i, 1, n)
    {
        ans += std::upper_bound(u + 1, u + n + 1, a[i]) - std::lower_bound(u + 1, u + n + 1, a[i]) - 1;
        fo (j, 0, 25)
        {
            now = a[i] ^ (1 << j);
            x = std::upper_bound(u + 1, u + n + 1, now) - std::lower_bound(u + 1, u + n + 1, now);
            ans += x;
        }
    }
    printf("%lld", ans >> 1);
}
```

---

