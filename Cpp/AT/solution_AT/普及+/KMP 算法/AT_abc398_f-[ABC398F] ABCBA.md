# [ABC398F] ABCBA

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc398/tasks/abc398_f

请找出一个以字符串 $S$ 为前缀的最短回文串。

## 说明/提示

### 约束条件

- $S$ 是由大写字母构成的字符串，长度为 $1$ 以上 $500000$ 以下

### 样例解释 1

`ABCBA` 是以 $S=$ `ABC` 为前缀的最短回文。

### 样例解释 2

`Z` 是以 $S=$ `Z` 为前缀的最短回文（此时 $S$ 本身就是回文）。

### 样例解释 3

`TREERT` 是以 $S=$ `TREE` 为前缀的最短回文。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
ABC```

### 输出

```
ABCBA```

## 样例 #2

### 输入

```
Z```

### 输出

```
Z```

## 样例 #3

### 输入

```
TREE```

### 输出

```
TREERT```

# 题解

## 作者：Laisira (赞：6)

求包含字符串 $S$ 的最小回文串。

显然就是 $S$ 翻转后的后缀和 $S$ 的前缀最长相同串补在 $S$ 后面就行了，求一下 `S+' '+S'` 的 KMP 就行了。

```cpp
struct KMP{vector<int>nxt;int n;KMP(){n=0;}KMP(string s){int j=0;n=s.size();nxt.resize(n+1);rep(2,n-1,i){while(j&&s[j+1]!=s[i])j=nxt[j];if(s[j+1]==s[i])j++;nxt[i]=j;}}};
///////////////////////////////////////////////////////////
#define Maxn 1000005 
int main()
{
    string s;
    cin>>s;
    int n = s.size();
    string t = s;
    reverse(t.begin(),t.end());
    string S = ' '+t+" "+s;
    KMP kmp(S);
    int k = kmp.nxt[n*2+1];
    // cout<<k<<" ";
    string ans;
    rep(0,n-k-1,i)ans += s[i];
    reverse(ans.begin(),ans.end());
    cout<<s+ans<<"\n";
    return 0;
}

```

---

## 作者：xxgirlxx (赞：4)

## 题外话

这场 rating 结算的时候显示我正好 rk800，难绷。

这场打完差五分上青，难绷。

## 题目大意

给出字符串 $S$。

找到最短回文串，使其前缀为 $S$。

## 题目思路

[板](https://www.luogu.com.cn/problem/P3805)

问题转化一下就是求最长回文后缀，看到回文先想到马拉车，但是多了个后缀的要求。问题不大，最后求答案的时候判断一下以这个位置为回文中心的最长回文串有没有包括最后一个位置即可，最后转化输出。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string S,T;
char s[31000010];
int l[31000010],n,mx,p,m;
int main(){
	cin>>S,T=S;
	m=S.size(),n=S.size()*2-1,S=' '+S;
	s[0]='!',s[n+1]='$';
	for(int i=1;i<=n;i+=2)s[i]=S[(i+1)/2],s[i+1]='#';
	mx=1,p=1;
	for(int i=1;i<=n;i++){
		l[i]=min(mx-i,l[2*p-i]);
		while(s[i+l[i]+1]==s[i-l[i]-1]&&i-l[i]-1>=0&&i+l[i]+1<=n+1)l[i]++;
		if(i+l[i]>=mx)mx=i+l[i],p=i;
	}
	mx=0;
	for(int i=1;i<=n;i+=2){
		if((i+1)/2+l[i]/2>=m)mx=max(mx,l[i]/2*2+1);
	}
	for(int i=2;i<=n;i+=2){
		if(i/2+(l[i]+1)/2>=m)mx=max(mx,(l[i]+1)/2*2);
	}
	cout<<T;
	for(int i=T.size()-mx-1;i>=0;i--)cout<<T[i];
	return 0;
}
```

---

## 作者：Dream_poetry (赞：3)

### 思路：

我们把原字符串 $s$ 翻转得到新字符串 $ss$，比较 $s$ 的后缀哈希值与 $ss$ 前缀哈希值，若相同则说明此段为一段回文串，找到后再截取 $s$ 的前段，翻转，补充到 $s$ 的后面，输出即可。

另：好像还有马拉车和 KMP 的做法，但我不会。

### 代码：


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int base=1e9+7;
const int mod=1e9+9;

int Hash1[1000005];
int p[1000005];

int Hash2[1000005];

int n;
string ans;

signed main() {
    string s;
    cin>>s;
	n=s.size();
    p[0]=1;
	string ss=s;
    for (int i=0;i<n/2;i++){
        swap(ss[i],ss[n-i-1]);
    }
    for (int i=0;i<n;i++){
        Hash1[i+1]=(Hash1[i]*base+s[i])%mod;
        Hash2[i+1]=(Hash2[i]*base+ss[i])%mod;
        p[i+1]=(p[i]*base)%mod;
    }

    int max_x=0;
    for (int x=0;x<n;x++){
        int len=n-x;
		int hash1=(Hash1[x+len]-Hash1[x]*p[len]%mod+mod)%mod;
		int hash2=(Hash2[len]-Hash2[0]*p[len]%mod+mod)%mod;
        if (hash1==hash2){
            max_x=len;
            break;
        }
    }

    ans=s;
    string c=s.substr(0, n-max_x);
    int LEN=c.size();
    for (int i=0;i<LEN/2;i++){
        swap(c[i],c[LEN-i-1]);
    }
    ans+=c;
    cout<<ans;    
    return 0;
}
```

---

## 作者：Clover_Lin (赞：3)

## 题目大意
请点击[这里](https://atcoder.jp/contests/abc398/tasks/abc398_f)查看原题面。给定一个字符串 $S$，找出以 $S$ 为前缀的最短回文字符串。
## 思路
观察样例三，容易发现只要寻找到一个合适的“对称轴”即可。可以考虑枚举对称轴位置，判断然后得到长度并计算答案串。但是这样显然会超时。我们可以考虑使用哈希算法来优化，注意需要维护正序哈希和逆序哈希，建议把 $base$ 设为 $13331$。
## 代码
[赛时已 AC，如有问题请联系作者。](https://atcoder.jp/contests/abc398/submissions/64072413)

---

## 作者：leo120306 (赞：2)

要让整串最短，就要让添加的后缀最短，相应的就要让其对应的前缀最短，也就是让原串的后缀回文串最长。因此原问题转化为了求最长回文后缀的长度。

使用字符串哈希实现即可，时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
#define Mod 1000000007
#define INF 0x3f3f3f3f3f3f3f3f
#define N 500005
#define next nxt
//#define int ll
#define i128 __int128 
#define ld long double

string s;
struct SH{
	ull P;
	ull Po[N],ha[N];
	
	void init(int p){
		P=p;
		Po[0]=1;
		for(int i=1;i<s.length();i++){
			Po[i]=Po[i-1]*P;
			ha[i]=ha[i-1]*P+s[i];
		}
	}
	
	ull get(int a,int b){
		return ha[b]-ha[a-1]*Po[b-a+1];
	}
}sh1,sh2;

signed main(){
	cin>>s;int n=s.length();
	s='1'+s;
	sh1.init(13331);
	reverse(s.begin()+1,s.end());
	sh2.init(13331);
	reverse(s.begin()+1,s.end());
	
	int len;
	for(len=n;len>=1;len--){
		ull h1=sh1.get(n-len+1,n),h2=sh2.get(1,len);
		if(h1==h2)break;
	}
	for(int i=1;i<=n;i++)cout<<s[i];
	for(int i=n-len;i>=1;i--)cout<<s[i];
	
	return 0;
}
```

---

## 作者：Merge_all (赞：2)

赛事做完 C 以后看来一眼排行榜，发现大片的人都过了 F，于是就直接做 F，没想到怎么水。

# Solution
显然要让最终的字符串长度最小，肯定要找到原字符串的后缀最长回文串，这样所添加的字符一定是最少的。

问题就是怎么去**快速**判断一个字符串是否是回文串，考虑字符串哈希（正反双哈希），这样只用判断一个字符串正着的哈希值和反着的哈希值是否相同即可。

~~其实就是一个字符串哈希的板子~~

# Code
```
#include<bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
constexpr int N = 5e5 + 5;
constexpr ull P = 13331;
int n;
string str;
ull h1[N], h2[N], pw[N];
ull check1 (int l, int r) {return h1[r] - h1[l - 1] * pw[r - l + 1];}
ull check2 (int l, int r) {return h2[l] - h2[r + 1] * pw[r - l + 1];}
int main () {
	*cin.tie(nullptr) << fixed << setprecision (20), cout.tie(nullptr) -> ios_base :: sync_with_stdio (false);
	
	cin >> str, n = str.size (), str = "@" + str;
	pw[0] = 1;
	for (int i = 1; i <= n; i ++) pw[i] = (ull) pw[i - 1] * P, h1[i] = (ull) h1[i - 1] * P + str[i];
	for (int i = n; i; i --) h2[i] = (ull) h2[i + 1] * P + str[i];
//	for (int i = 1; i <= n; i ++) cout << h1[i] << ' '; cout << '\n';
//	for (int i = 1; i <= n; i ++) cout << h2[i] << ' '; cout << '\n';
	if (check1(1, n) == check2(1, n)) {
		for (int i = 1; i <= n; i ++) cout << str[i];
		return 0;
	}
	for (int i = n - 1; i; i --)
		if (check1 (n - i + 1, n) == check2 (n - i + 1, n)) {
			for (int j = 1; j < n - i + 1; j ++) cout << str[j];
			for (int j = n - i + 1; j <= n; j ++) cout << str[j];
			for (int j = n - i; j; j --) cout << str[j];
			return 0;
		}
	return 0;
}
```

---

## 作者：endswitch (赞：1)

难度严格小于 D 和 E。

题目本质上是将反串拼到原串后，有多少重合的部分。

做法有很多，这里讲一下 kmp 求 `border` 的做法。

将反串接在原串的前面，那么题目转化为求最长公共前后缀。

最后按题目格式输出即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 5;
int nxt[N << 1];
string s, t;

signed main() {
	ios_base :: sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin >> s;
	
	t = s;
	
	reverse(t.begin(), t.end());
	
	int n = s.size(), m = t.size();
	
	string S = t + "?" + s;
	
	for(int i = 1, j = 0 ; i < (int)(S.size()) ; ++ i) {
		while(j && S[i] != S[j]) j = nxt[j - 1];
		
		if(S[i] == S[j]) {
			nxt[i] = ++ j;
			
			if(nxt[i] == m) j = nxt[j - 1]; 
		}
	}
	
	for(int i) 
	
	for(int i = 0 ; i < n ; ++ i)
		cout << s[i];
	for(int i = nxt[n + m] ; i < m ; ++ i)
		cout << t[i];
	
	return 0;
}
```

---

## 作者：SunburstFan (赞：1)

## F - ABCBA

### 题目大意

KMP 板子。

给定一个只包含大写英文字母的字符串 $S$，要求构造一个以 $S$ 为前缀的最短回文字符串。

### 解题思路

- 将字符串 $S$ 反转得到 $R$。
- 构造字符串 `C = R + # + S`。
- 在 $C$ 上计算 $KMP$ 失配函数，得到末尾位置可匹配的最长前后缀长度 $l$。

$l$ 表示 $S$ 的开头与 $R$ 的结尾重合的最大部分，因此只需将 $R$ 剩下未匹配的前缀部分拼接到 $S$ 后，即为最短回文。

**代码**：

```cpp
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    string s;
    cin>>s;

    string r=s;
    reverse(r.begin(),r.end());

    string c=r+"#"+s;
    int n=c.size();
    vector<int> p(n,0);

    for(int i=1;i<n;i++){
        int j=p[i-1];
        while(j>0&&c[i]!=c[j]){
            j=p[j-1];
        }
        if(c[i]==c[j]){
            j++;            
        }
        p[i]=j;
    }

    int l=p.back();
    string a=r.substr(l);
    
    cout<<s+a;

    return 0;
}
```

---

## 作者：Dtw_ (赞：1)

## 题意
给你长为 $n$ 的字符串 $s$，你需要构造出一个字符串，使得 $s$ 为它的前缀，且这个字符串回文。
## Solution
我们把 $s$ 反转过来的串称为 $s'$。因为 $s'$ 就相当于倒过来看 $s$，所以下文中 $s'$ 的下标从 $n$ 开始一直到 $1$。

容易想到的是答案串应该是把 $s$ 和 $s'$ 拼在一块。

那么我们只需要看他们可以重合多少即可。

考虑枚举在 $s$ 上从 $i$ 这里开始重合。

那么也就是说 $s$ 上的 $[i, n]$ 这一段后缀和 $s'$ 上的 $[n, i]$ 的前缀一样。还剩下 $s$ 的一段前缀和 $s'$ 的一段后缀，他们必然一样。

所以我们字符串哈希判断上述要求，直接输出即可。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll unsigned long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 5e5 + 10, base = 131;

string s;
ll p[N], a[N], b[N];

ll get1(int l, int r) { return a[r] - a[l - 1] * p[r - l + 1]; }

ll get2(int l, int r) { return b[l] - b[r + 1] * p[r - l + 1]; }

int main()
{
    fst
    cin >> s;
    int n = s.size();
    s = " " + s;
    p[0] = 1;
    for (int i = 1; i <= n; i++) p[i] = p[i - 1] * base, a[i] = a[i - 1] * base + s[i];
    for (int i = n; i >= 1; i--) b[i] = b[i + 1] * base + s[i];
    int ans = n;
    for (int i = 1; i <= n; i++) if (get1(i, n) == get2(i, n)) { ans = i; break; }
    for (int i = 1; i < ans; i++) cout << s[i];
    for (int i = n; i >= 1; i--) cout << s[i];
    return 0;
}
```

---

## 作者：StarsIntoSea_SY (赞：1)

写了 manacher 的大炮轰蚊子做法。

很显然你得先找到这个串的**最长回文后缀**，然后剩下的再倒着输出一遍就行了。

赛时写的 manacher，因为一时没想到怎么快速求最长回文后缀。跑完 manacher 就看以每个位置为中心的最长回文能不能取到最后一个字符，如果能取到就是一个回文后缀，其中长度最大的一个就是最长回文后缀，后面就简单了。

时间复杂度 $O(|S|)$。

[赛时代码](https://atcoder.jp/contests/abc398/submissions/64076362)。

---

## 作者：wmrqwq (赞：1)

这是一篇视频题解。

![](bilibili:BV1E5XWYKE3n?t=410)

[参考代码](https://atcoder.jp/contests/abc398/submissions/64048777)

---

## 作者：_sin_ (赞：1)

评价：ABC 这回正没活整了，F 放这道题。

首先，考虑要补成最短的回文串，先枚举回文中心，尽量让回文中心靠前。枚举完回文中心用哈希判一下正着看和反着看是否相等即可。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll read(){
    ll x=0,f=1;char ch=getchar_unlocked();
    while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar_unlocked();}
    while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar_unlocked();}
    return f*x;
}

const int N = 500005;
const ll mod = 998244353,P=131;
int n;ll p[N],hs1[N],hs2[N];
char s[N],ans[N];

ll ask1(int l,int r){if(l>r)return -1;
    ll hs=hs1[r]-hs1[l-1]*p[r-l+1]%mod;
    hs=(hs%mod+mod)%mod;return hs;
}
ll ask2(int l,int r){if(l>r)return -1;
    ll hs=hs2[l]-hs2[r+1]*p[r-l+1]%mod;
    hs=(hs%mod+mod)%mod;return hs;
}

int main(){scanf("%s",s+1);n=strlen(s+1);hs2[n+1]=0;
    p[0]=1;for(int i=1;i<=n+1;i++)p[i]=p[i-1]*P%mod;
    for(int i=1;i<=n;i++)hs1[i]=(hs1[i-1]*P+s[i])%mod;
    for(int i=n;i>=1;i--)hs2[i]=(hs2[i+1]*P+s[i])%mod;
    for(int i=1;i<n;i++)if(i*2>=n){
        if(ask2(i+1,n)==ask1(i-(n-i),i-1)){
            for(int j=1;j<=i;j++)putchar(s[j]);
            for(int j=i-1;j>=1;j--)putchar(s[j]);
            exit(0);
        }if(ask2(i+1,n)==ask1(i-(n-i)+1,i)){
            for(int j=1;j<=i;j++)putchar(s[j]);
            for(int j=i;j>=1;j--)putchar(s[j]);
            exit(0);
        }
    }for(int i=1;i<=n;i++)putchar(s[i]);
    for(int i=n-1;i>=1;i--)putchar(s[i]);
    return 0;
}
```

---

## 作者：Tomwsc (赞：1)

# AT_abc398_f [ABC398F] ABCBA 题解

## 题意

给定一个字符串，求以这个字符串为前缀的最短回文串。

## 思路

水题。

容易发现这个字符串只可能是两种状态：

- 末尾已经出现了长度大于一的回文子串。
- 没有出现长度大于一的回文子串。

对于第一种情况，只需要找到是从第几位出现的回文子串即可。对于第二种情况，则给定的字符串一定是最短回文串的前半部分。

为了验证第一种情况，可以使用字符串哈希来实现。即正序求一边哈希值，逆序求一边哈希值，然后匹配即可。若求出在第 $i$ 位到最后一位出现了回文，则最终答案即为：原字符串加上第 $i-1$ 位到第 $1$ 位。

## 代码

直接预处理出哈希值即可。不过在匹配时要注意一下匹配的回文串的长度是奇数还是偶数。

时间复杂度：$O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf (1ll << 62)
#define regint register int 
using namespace std;
const int MAXN = 5e5 + 10 , b = 35;
string s;
int len;
unsigned long long ha[MAXN] , num[MAXN];
unsigned long long ha1[MAXN];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	len = s.length();
	s = ' ' + s;
	num[0] = 1;
	for(regint i = 1;i <= len;i ++) {
		ha[i] = ha[i - 1] * b + (unsigned long long)(s[i] - '0' + 1);
		num[i] = num[i - 1] * b;
	}
	for(regint i = len;i >= 1;i --)
		ha1[i] = ha1[i + 1] * b + (unsigned long long)(s[i] - '0' + 1);
	for(regint i = 1;i <= len;i ++) {
		int k = (len - i + 1) / 2;
		if(ha[i + k - 1] - ha[i - 1] * num[k] == ha1[(len - i + 1) % 2 ? i + k + 1 : i + k]) {
			for(regint j = 1;j <= len;j ++)
				cout << s[j];
			for(regint j = i - 1;j >= 1;j --)
				cout << s[j];
			return 0;	
		}
	}
	return 0;
}
```

---

## 作者：KobeBeanBryantCox (赞：1)

# AT_abc398_f [ABC398F] ABCBA 题解

---------------

[题目传送门](https://www.luogu.com.cn/problem/AT_abc398_f)。

真的有 F 的难度吗？连我这种蒟蒻都做得出来。

---------------

## 题意

求以 $S$ 为前缀的最短回文。

---------------

## 思路

感性理解一下（理性也很好证明，考虑回文串的充要条件即可，具体的可以看[官解](https://atcoder.jp/contests/abc398/editorial/12501)），好像是不是只能在 $S$ 中找最长的回文后缀，然后把这个后缀的前面反过来加入 $S$ 后面，这样才能保证 $S$ 是最短回文啊？

所以枚举 $S$ 最长回文后缀，正着一遍哈希反着一遍哈希，然后就做完了？

上面那一步官解居然用的是 manacher？太麻烦了吧。

----------------

## AC 代码

复杂度 $O(n)$。

~~我不会告诉你我赛时数组开小了挂了一发的。~~

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
#define int long long
int in()
{
    int k=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
    return k*f;
}
void out(int x)
{
    if(x<0)putchar('-'),x=-x;
    if(x<10)putchar(x+'0');
    else out(x/10),putchar(x%10+'0');
}
const int N=5e5+10,B=131,mod[2]={998244353,(int)1e9+7};
int power[N][2];
void init(int n)
{
	for(int $=0;$<2;$++)
	{
		power[0][$]=1;
		for(int i=1;i<=n;i++)power[i][$]=power[i-1][$]*B%mod[$];
	}
}
struct hash1
{
	string s;int a[N][2];
	void init()
	{
		for(int $=0;$<2;$++)
			for(int i=1;i<=s.size();i++)a[i][$]=(a[i-1][$]*B+s[i-1])%mod[$];
	}
	pair<int,int>get(int l,int r)
	{
		int b[2];
		for(int $=0;$<2;$++)b[$]=(a[r][$]-a[l-1][$]*power[r-l+1][$]%mod[$]+mod[$])%mod[$];
		return make_pair(b[0],b[1]);
	}
};
signed main()
{
    hash1 s;cin>>s.s,s.init();
    int ans=s.s.size();
    init(ans);
    hash1 t;t.s=s.s;
    reverse(t.s.begin(),t.s.end()),t.init();
    for(;ans>=1;ans--)
        if(s.get(s.s.size()-ans+1,s.s.size())==t.get(1,ans))break;
    cout<<s.s;for(int i=s.s.size()-ans-1;i>=0;i--)putchar(s.s[i]);
    return 0;
}
```

---------------

若有误或不清，欢迎私信或者评论。

---

## 作者：Lyw_and_Segment_Tree (赞：0)

## 开始解题！

前言：本来没想着过的，随便写了个哈希，结果不仅过了还跑的巨快。。。

考虑对 $s$ 正反各做一遍哈希，记为 $hl_i, hr_i$，这里我取了 $B = 1331$，反正一般取什么值都没什么问题的，因为可以自然溢出，哈希的 `query` 函数也很好写，一般形式如下：

```cpp
int query(int l, int r) {
    return hash[r] - hash[l - 1] * powb[r - l + 1];
} 
```

为了方便，接下来记 $ql(l, r)$ 表示 $s_l \sim s_r$ 的哈希值，$qr(l, r)$ 表示 $s$ 翻转字符串之后 $s_l \sim s_r$ 的哈希值。

然后我们从小到大枚举 $i$，如果 $ql(i, n) = qr(1, n - i + 1)$ 说明位置 $i$ 就是答案，又因为我们是从小到大枚举的，所以答案就直接是最优的。

这样直接做确实是 $O(n ^ 2)$ 的，但是实际测试下来在 AT 上最大点不超过 20ms，特别优秀。

代码是简单的。

code ：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define vec vector
#define pll pair<ll, ll>
#define mkp make_pair
#define endl "\n"

using namespace std;

const ll mod = 998244353;

namespace fastio {
    char buf[1 << 21], *p1 = buf, *p2 = buf;
	
    const ll getc() {
        return p1 == p2 && ( p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++;
    }
	
    const ll read() {
        ll x = 0, f = 1;
		
        char ch = getc();
		
        while (ch < '0' || ch > '9') {
            if (ch == '-') f = -1; ch = getc();
        }
		
        while (ch >= '0' && ch <= '9') {
            x = (x << 1) + (x << 3) + (ch ^ 48), ch = getc();
        }
		
        return x * f;
    }
	
    const void write(ll x) {
        if (x < 0) {
            putchar('-'), x = -x;
        }
		
        ll sta[35], top = 0;
	    
        do {
            sta[top++] = x % 10, x /= 10;
        } while (x);
	    
        while (top) putchar(sta[--top] + 48);
    }
}

#define rd fastio::read
#define wt fastio::write
#define gc fastio::getc

ll n, m, q, pb[500005], hl[500005], hr[500005]; string s;

ll opt, l, r, ans = 0;

const ll B = 131;

ll ql(ll l, ll r) {
    return hl[r] - hl[l - 1] * pb[r - l + 1];
}

ll qr(ll l, ll r) {
    return hr[r] - hr[l - 1] * pb[r - l + 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    ll i, j, k, x, y, z, res = 0, now;

    cin >> s, n = s.size(), s = ' ' + s;

    pb[0] = 1;

    for (i = 1; i < 500005; i++) pb[i] = pb[i - 1] * B;

    for (i = 1; i <= n; i++) hl[i] = hl[i - 1] * B + (s[i] - 'A');

    for (i = 1; i <= n; i++) hr[i] = hr[i - 1] * B + (s[n - i + 1] - 'A');

    for (i = 1; i <= n; i++) {
        if (ql(i, n) == qr(1, n - i + 1)) {
            for (j = 1; j <= n; j++) cout << s[j];

            for (j = i - 1; j; j--) cout << s[j];

            break;
        }
    }

    return 0;
}
```

[AC record](https://atcoder.jp/contests/abc398/submissions/64119176)

---

## 作者：cyq32ent (赞：0)

字符串哈希板子题。

枚举每一个可能的回文串对称轴位置，用字符串哈希判断位置后面的部分翻折后能否与前面重合即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+2009,base=26;
char s[505050];int N;
int hsh[505050],hs1[505050];
int pw(int a,int b){
	int r=1;
	for(;b;a=a*a%mod,b>>=1)if(b&1)r=r*a%mod;
	return r;
}
int gt(int i,int j){
	return (hsh[j]+mod-hsh[i]*pw(base,j-i)%mod)%mod;
}int gt1(int i,int j){
	return (hs1[i]+mod-hs1[j]*pw(base,j-i)%mod)%mod;
}
signed main(){
	cin>>s+1;N=strlen(s+1);
	for(int i=1;i<=N;i++){
		hsh[i]=(hsh[i-1]*base%mod+s[i]-'A')%mod;
	}for(int i=N;i;i--){
		hs1[i]=(hs1[i+1]*base%mod+s[i]-'A')%mod;
	}for(int i=N;i<=2*N;i++){
		if(i&1){
			int mid=(i+1)>>1;
			if(gt(2*mid-N-1,mid-1)==gt1(mid+1,N+1)){
				for(int i=1;i<mid;i++)cout<<s[i];
				cout<<s[mid];
				for(int i=mid-1;i;i--)cout<<s[i];
				return 0;
			}
		}else{
			int mid=i>>1;
			if(gt(2*mid-N,mid)==gt1(mid+1,N+1)){
				for(int i=1;i<=mid;i++)cout<<s[i];
				for(int i=mid;i;i--)cout<<s[i];
				return 0;
			}
		}
	}
	return 0;
}
```

---

