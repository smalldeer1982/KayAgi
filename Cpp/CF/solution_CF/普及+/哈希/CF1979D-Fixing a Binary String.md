# Fixing a Binary String

## 题目描述

You are given a binary string $ s $ of length $ n $ , consisting of zeros and ones. You can perform the following operation exactly once:

1. Choose an integer $ p $ ( $ 1 \le p \le n $ ).
2. Reverse the substring $ s_1 s_2 \ldots s_p $ . After this step, the string $ s_1 s_2 \ldots s_n $ will become $ s_p s_{p-1} \ldots s_1 s_{p+1} s_{p+2} \ldots s_n $ .
3. Then, perform a cyclic shift of the string $ s $ to the left $ p $ times. After this step, the initial string $ s_1s_2 \ldots s_n $ will become $ s_{p+1}s_{p+2} \ldots s_n s_p s_{p-1} \ldots s_1 $ .

For example, if you apply the operation to the string 110001100110 with $ p=3 $ , after the second step, the string will become 011001100110, and after the third step, it will become 001100110011.

A string $ s $ is called  $ k $ -proper if two conditions are met:

- $ s_1=s_2=\ldots=s_k $ ;
- $ s_{i+k} \neq s_i $ for any $ i $ ( $ 1 \le i \le n - k $ ).

For example, with $ k=3 $ , the strings 000, 111000111, and 111000 are $ k $ -proper, while the strings 000000, 001100, and 1110000 are not.

You are given an integer $ k $ , which is a divisor of $ n $ . Find an integer $ p $ ( $ 1 \le p \le n $ ) such that after performing the operation, the string $ s $ becomes $ k $ -proper, or determine that it is impossible. Note that if the string is initially $ k $ -proper, you still need to apply exactly one operation to it.

## 说明/提示

In the first test case, if you apply the operation with $ p=3 $ , after the second step of the operation, the string becomes 11100001, and after the third step, it becomes 00001111. This string is $ 4 $ -proper.

In the second test case, it can be shown that there is no operation after which the string becomes $ 2 $ -proper.

In the third test case, if you apply the operation with $ p=7 $ , after the second step of the operation, the string becomes 100011100011, and after the third step, it becomes 000111000111. This string is $ 3 $ -proper.

In the fourth test case, after the operation with any $ p $ , the string becomes $ 5 $ -proper.

## 样例 #1

### 输入

```
7
8 4
11100001
4 2
1110
12 3
111000100011
5 5
00000
6 1
101001
8 4
01110001
12 2
110001100110```

### 输出

```
3
-1
7
5
4
-1
3```

# 题解

## 作者：Engulf (赞：11)

因为 $k \mid n$，所以最终的字符串一定是这两种形式中的一种。

- $\underbrace{11\cdots1}_{k \ 个 \ 1} \underbrace{00\cdots0}_{k \ 个 \ 0} \cdots$

- $\underbrace{00\cdots0}_{k \ 个 \ 0} \underbrace{11\cdots1}_{k \ 个 \ 1} \cdots$

题目已经告诉我们，若选择的位置为 $p$，则操作后的字符串是 $s_{p + 1}s_{p + 2}\dots s_{n}s_ps_{p-1}\dots s_1$，如果合法，则它一定等于上面两个字符串中的一个。

判断字符串相等可以哈希维护。

维护原序列的哈希和反转后的序列的哈希，以 $s_n$ 和 $s_p$ 为界分开字符串，设 $s_{p + 1}s_{p + 2}\dots s_{n}$ 的哈希值为 $h_1$，$s_ps_{p-1}\dots s_1$ 的哈希值为 $h_2$，则它们拼接起来的字符串的哈希值为 $h_1 \cdot B^{p} + h_2$，其中 $B$ 是你字符串哈希使用的底数（base）。

[如果你不明白为什么拼起来哈希值是它](https://www.luogu.com.cn/paste/8l62wd62)。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

using ull = unsigned long long;

const int N = 1e5 + 5;

ull base = 233;

int n, k;
char s[N], revs[N];
char v1[N], v2[N];

inline char rev(char x) {return x == '0' ? '1' : '0';}

ull pre[N], suf[N];
ull pw[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    pw[0] = 1;
    for (int i = 1; i < N; i++) pw[i] = pw[i - 1] * base;
    int tt;
    cin >> tt;
    while (tt--) {
        cin >> n >> k >> s + 1;

        for (int i = 1; i <= k; i++) v1[i] = '1', v2[i] = '0';
        for (int i = k + 1; i <= n; i++) v1[i] = rev(v1[i - k]), v2[i] = rev(v2[i - k]);

        int cnt = count(s + 1, s + 1 + n, '1');
        ull h1 = 0, h2 = 0;
        int t1 = 0, t2 = 0;

        for (int i = 1; i <= n; i++) {
            h1 = h1 * base + v1[i], t1 += v1[i] == '1';
            h2 = h2 * base + v2[i], t2 += v2[i] == '1';
        }

        if (t1 != cnt) h1 = -1;
        if (t2 != cnt) h2 = -1;

        strcpy(revs + 1, s + 1);
        reverse(revs + 1, revs + 1 + n);

        pre[0] = suf[0] = 0;

        for (int i = 1; i <= n; i++) {
            pre[i] = pre[i - 1] * base + s[i];
            suf[i] = suf[i - 1] * base + revs[i];
        }

        int ans = -1;
        for (int i = 1; i <= n; i++) {
            ull h = (pre[n] - pre[i] * pw[n - i]) * pw[i] + (suf[n] - suf[n - i] * pw[i]);
            if (h == h1 || h == h2) {
                ans = i;
                break;
            }
        }

        cout << ans << "\n";

    }
    return 0;
}
```

样例第四个小点答案 $1$ 或 $5$，我这个跑出来就是 $1$。

---

## 作者：BeJoker (赞：4)

# 模拟 + 贪心  
时间复杂度O(n)  

[AC记录](https://codeforces.com/contest/1979/submission/264528916)  
## 思路  
题目大意是一刀两段，翻转左边那段后衔接到右边使其满足要求  

**首先**，无可置疑的是，如果不用翻转就能满足要求，那么直接输出字符串的长度即可。  
对应题目中给出的样例4  
```
5 5
00000
```
**然后**我们思考，我们**为什么要进行翻转**？只可能的原因是最后不是连续的k个(k是题目中的） 
对应题目中给出的样例3
```
12 3
111000100011
```
最后面跟着的是两个1，但是我们需要3个，因此我们一定要将前面进行翻转。  

**接着**我们思考，**怎么进行翻转**？  
还是看这个样例  
```
12 3
111000100011
``` 
最后两个1是要去跟翻转后的左边去匹配的，因此他们一定是留在右边的  
然后这两个1前面有3个0。这3个0我们也是一定要留在右边的。  
**为什么？** 首先这是0，是不能去跟那两个1去匹配的，所以我们肯定要全放右边。其次，就算出现了000111这种情况，我们还是会将0留在右边，翻转了成为了111000和000111并无区别。  

这就告诉了我们，除了最右边留着匹配的部分，其余的连续k个都放可以放在右边。
题目样例1
```
8 4
11100001
```
按我的意思来，切的位置应该在这111 | 00001
翻转过去成为了00001111符合题意，进行输出

以上由贪心讨论了切的位置  
再进行详细说明  
```
k = 3
100011
切在这
1 | 00011

k = 3
111000111
切在这
| 111000111
这种切法是直接输出长度的，因为本身就满足，需要判断

k = 3
110000111
切在这
110 | 000111
```

由此题目得到了解答。  
注：这只是看了切的位置，需要再进行整个判断  
接下来就是**细节处理**和码力了。

## code部分

```cpp
inline void solve() {
     int n, k; cin >> n >> k;
     string s; cin >> s;    
     s = " " + s;
     char last = s[n];
     int j = n, len = 0;
     while (len < k && s[j] == last) j -= 1, len += 1;
     int ok = j, ji = len;
     if (j == 0) return cout << n << endl, void();
     if (s[j] != last) {
     	while (true) {
     		char cur = s[j];
     		len = 0;
     		while (s[j] == cur) j -= 1, len += 1;
     		if (len == k) ok = j;
     		else if (len > k) {
     			ok = j + len - k;
     			break;
     		}else break;
     		if (j == 0) break;
    	}
     }
     if (ok == 0) {
     	if (ji == k) cout << n << endl;
     	else cout << -1 << endl;
     	return;
     }
     reverse(s.begin() + 1, s.begin() + 1 + ok);
     s = " " + s.substr(1 + ok) + s.substr(1, ok);
     len = 0;
     int cur = s[1] - '0';
     bool flag = true;
     for (int i = 1; i <= n - k; i ++ ) {
     	if (s[i] - '0' != cur) flag = false;
     	len += 1;
     	if (len == k) len = 0, cur ^= 1;
     	if (s[i + k] == s[i]) flag = false;
     }
     if (k == n) {
     	char tt = s[1];
     	for (int i = 1; i <= n; i ++ ) if (s[i] != tt) flag = false;
     }
     if (flag) cout << ok << endl;
     else cout << -1 << endl;
	 return;
}
```

---

## 作者：Lu_xZ (赞：4)

**D		\*1831**

只有一段连续区间的末尾可以作为分割点（红蓝交界），符合要求的位置少于 $\dfrac{n}{k}$ 个。

预处理 $pre_i$ 表示 $s_1\sim s_i$ 的翻转是否合法，$suf_i$ 表示 $s_i\sim s_n$ 是否合法。

如果 $pre_p = 0$ 或 $suf_{p + 1} = 0$，则一定不合法。

否则，检查每个 $i \in [\max(p + 1, n - k + 1), n]$，是否满足 $s_{i} \ne s_{p - (i + k - n) + 1}$，即后缀与翻转后的前缀之间是否合法。

每个位置最多检查 $k$ 次，时间复杂度 $O(n)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/9tz43eyr.png)

```cpp
constexpr int N = 2e5 + 5;

int n, k, pre[N], suf[N];
string s;

void solve() {
	cin >> n >> k >> s;
	if(k == n) {
		int cnt = count(s.begin(), s.end(), s.front());
		cout << (cnt == n ? 1 : -1) << '\n';
		return;
	}
	s = ' ' + s + ' ';
	pre[0] = 1;
	for(int i = 1; i <= n; ++ i) {
		pre[i] = pre[i - 1] && (i <= k || s[i] != s[i - k]);
	}
	suf[n + 1] = 1;
	for(int i = n; i >= 0; -- i) {
		suf[i] = suf[i + 1] && (i + k > n || s[i] != s[i + k]);
	}
	for(int i = 1, cnt = 0; i <= n; ++ i) {
		if(s[i] != s[i - 1]) cnt = 1;
		else ++ cnt;
		if(cnt >= k && s[i] != s[i + 1]) {
			int p = i - k;
			if(!p || !pre[p] || !suf[p + 1]) continue;
			int ok = 1;
			for(int j = max(p + 1, n - k + 1); j <= n; ++ j) {
				int x = p - (j + k - n) + 1;
				if(x < 1) break;
				if(s[x] == s[j]) {
					ok = 0;
					break;
				}
			}
			if(ok) {
				cout << p << '\n';
				return;
			}
		}
	}
	cout << -1 << '\n';
	return;
}
```

---

## 作者：cjh20090318 (赞：3)

观察不出来性质，我选择了最朴素的方法。

## 题意

定义一个字符串是 $k\text{-proper}$，需要满足下列两个条件。

- $s_1 = s_2 = \ldots = s_k$；
- $\forall 1 \le i \le n-k,s_{i+k} = s_i$。

定义一次操作为选择一个 $p \in [1,n] \cap \mathbb{N^*}$，将字符串 $s_1s_2\ldots s_n$ 变为 $s_{p+1}s_{p+2}\ldots s_ns_ps_{p-1}\ldots s_1$。

你需要找到一个整数 $p$ 使得将字符串 $s$ 恰好一次操作后是 $k \text{-proper}$。

## 分析

根据定义可以得到 $k\text{-proper}$ 字符串一定是 $k$ 个 $0$ 和 $k$ 个 $1$ 交替出现的，所以即存在两种：$0$ 开头的和 $1$ 开头的。

于是对应两种字符串，直接枚举 $p$ 判断进行操作后两字符串是否相等即可。

枚举 $p$ 的时间复杂度 $O(n)$，使用哈希判断两字符串相等的时间复杂度为 $O(1)$，总体时间复杂度为 $O(n)$。

## 注意事项

本题是 CodeForces 上的一道题，由于 Hack 机制的存在，强烈不建议大家写固定模数哈希（双哈希也不建议），所以我选择了随机双底数自然溢出前后缀哈希。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstdlib>
#include<random>
#define MAXN 100005
using namespace std;
typedef unsigned int UI;
typedef unsigned long long ULL;
int n,k;
mt19937 mtrd(random_device{}());
const UI P[]={61,3881,6907,19260817,29050993,998244353};//底数列表。
UI p1,p2;
ULL pn1[MAXN],pn2[MAXN],hsl[2][MAXN],hsr[2][MAXN],htl[2][MAXN],htr[2][MAXN];
char s[MAXN],t[MAXN];
void init(ULL hsl[][MAXN],ULL hsr[][MAXN],char *s,const int n){//初始化前后缀哈希。
	hsl[0][0]=hsl[1][0]=0;
	for(int i=1;i<=n;i++)
		hsl[0][i]=hsl[0][i-1]*p1+s[i]-'0'+1,hsl[1][i]=hsl[1][i-1]*p2+s[i]-'0'+1;//前缀哈希。
	hsr[0][n+1]=hsr[1][n+1]=0;
	for(int i=n;i>0;--i)
		hsr[0][i]=hsr[0][i+1]*p1+s[i]-'0'+1,hsr[1][i]=hsr[1][i+1]*p2+s[i]-'0'+1;//后缀哈希。
}
ULL qryl(ULL *hs,ULL *pn,const int l,const int r){//查询前缀。
	return hs[r]-hs[l-1]*pn[r-l+1];
}
ULL qryr(ULL *hs,ULL *pn,const int l,const int r){//查询后缀。
	return hs[l]-hs[r+1]*pn[r-l+1];
}
void solve(){
	scanf("%d %d %s",&n,&k,s+1);
	init(hsl,hsr,s,n);//初始化 s 的哈希值。
	bool f=0;
	for(int i=1;i<=n;f^=!(i++%k)) t[i]=f|'0';//0 开头的 k-proper 序列。
	init(htl,htr,t,n);
	for(int p=1;p<=n;p++)
		if(qryl(hsl[0],pn1,p+1,n)==qryl(htl[0],pn1,1,n-p)&&qryl(hsl[1],pn2,p+1,n)==qryl(htl[1],pn2,1,n-p)
		&&qryr(hsr[0],pn1,1,p)==qryl(htl[0],pn1,n-p+1,n)&&qryr(hsr[1],pn2,1,p)==qryl(htl[1],pn2,n-p+1,n)){
			printf("%d\n",p);return;
		}//判断 s[p+1:n]=t[1:n-p] 和 s[p:1]=t[n-p+1:n]。
	f=1;
	for(int i=1;i<=n;f^=!(i++%k)) t[i]=f|'0';//1 开头的 k-proper 序列。
	init(htl,htr,t,n);
	for(int p=1;p<=n;p++)
		if(qryl(hsl[0],pn1,p+1,n)==qryl(htl[0],pn1,1,n-p)&&qryl(hsl[1],pn2,p+1,n)==qryl(htl[1],pn2,1,n-p)
		&&qryr(hsr[0],pn1,1,p)==qryl(htl[0],pn1,n-p+1,n)&&qryr(hsr[1],pn2,1,p)==qryl(htl[1],pn2,n-p+1,n)){
			printf("%d\n",p);return;
		}//判断条件同上。
	puts("-1");
}
int main(){
	p1=P[mtrd()%6];
	do p2=P[mtrd()%6];while(p1==p2);//随机选择双底数。
	*pn1=*pn2=1;
	for(int i=1;i<MAXN;i++) pn1[i]=pn1[i-1]*p1,pn2[i]=pn2[i-1]*p2;//预处理幂次。
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：Exp10re (赞：2)

前后缀哈希是什么，没听过。

## 解题思路

按照原题中的方案按顺序判断前缀是否是合法 $k$-proper 串的前缀，直到当前前缀不合法或者判断到 $n+1$ 停止。

- 如果判断到 $n+1$，那么说明原串是 $k$-proper 串。选择 $p=n$ 将一整个串翻转即可。

- 否则，找到一个删掉该前缀后满足后面的串存在至少有 $k$ 个连续值的最长合法前缀进行操作，然后判断操作后的串是否为 $k$-proper 串即可。
	- 因为如果操作后的串不为 $k$-proper 串，那么换一个位置操作就一定会使得该不合法前缀存在或者操作后的串前 $k$ 个值不合法，所以这种情况下操作是唯一的。
    
时间复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=1010100;
char s[MAXN];
long long n,a[MAXN],b[MAXN],k;
bool finalcheck(long long x)
{
	long long i,j=0;
	for(i=x+1;i<=n;i++)
	{
		j++;
		b[j]=a[i];
	}
	for(i=x;i>=1;i--)
	{
		j++;
		b[j]=a[i];
	}
	for(i=2;i<=k;i++)
	{
		if(b[i]!=b[i-1])
		{
			return false;
		}
	}
	for(i=k+1;i<=n;i++)
	{
		if(b[i]==b[i-k])
		{
			return false;
		}
	}
	return true;
}
void work()
{
	long long i,j,p,sta,lst=1,t,pos;
	scanf("\n%lld %lld\n%s",&n,&k,s+1);
	for(i=1;i<=n;i++)
	{
		a[i]=s[i]-'0';
	}
	a[0]=-1;
	for(i=n;i>=1;i--)
	{
		if(a[i]!=a[i-1])
		{
			p=i;
			break;
		}
	}
	for(i=2;i<=n;i++)
	{
		if(a[i]!=a[i-1])
		{
			t=i-lst;
			pos=i-1;
			lst=i;
			if(t!=k)
			{
				if(t<k)
				{
					if(finalcheck(pos))
					{
						printf("%lld\n",pos);
						return;
					}
					else
					{
						printf("-1\n");
						return;
					}
				}
				else if(t<=k*2)
				{
					if(finalcheck(pos-k))
					{
						printf("%lld\n",pos-k);
						return;
					}
					else
					{
						printf("-1\n");
						return;
					}
				}
				else
				{
					printf("-1\n");
					return;
				}
			}
		}
	}
	if(finalcheck(n))
	{
		printf("%lld\n",n);
		return;
	}
	else
	{
		printf("-1\n");
		return;
	}
	return;
}
int main()
{
	long long T;
	scanf("%lld",&T);
	while(T--)
	{
		work();
	}
	return 0;
}
```

---

## 作者：lhc0707 (赞：1)

字符串哈希题目。

注意到一个满足 k-proper 性质的 01 串必然是以下两种中的一种：

- 前 $k$ 个是 $1$，再 $k$ 个是 $0$，依次类推。
- 前 $k$ 个是 $0$，再 $k$ 个是 $1$，依次类推。

我们用字符串哈希维护以上两种状态设我们选取的模数是 $m$，求出前缀哈希 pre 与后缀哈希 suf，则 $p = p_0$ 时，经过变换后的 01 串的哈希值为：$(pre_n- pre_{p_0} \times m^{n-p_0})\times m^{p_0}+suf_1-suf_{p_0+1}\times m^{p_0}$，将这个值和两种目标状态的哈希值比较就可以得出结果。$m$ 的值推荐使用 $131$ 或 $13331$。

代码：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define N 100005
#define ull unsigned long long
using namespace std;
const ull mod=131;
int n,k,a[N],v1[N],v0[N];
ull pre[N],suf[N],pw[N];
string s;
int mian()
{
	cin>>n>>k>>s; pw[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*mod;
	for(int i=1;i<=n;i++)a[i]=s[i-1]-'0';
	for(int i=1;i<=n;i++)pre[i]=pre[i-1]*mod+a[i];
	for(int i=n;i>=1;i--)suf[i]=suf[i+1]*mod+a[i];
	ull k1=0ull,k0=0ull;
	for(int i=1;i<=k;i++)v1[i]=1,v0[i]=0;
	for(int i=k+1;i<=n;i++)v1[i]=v1[i-k]^1,v0[i]=v0[i-k]^1;
	for(int i=1;i<=n;i++)k1=k1*mod+v1[i],k0=k0*mod+v0[i];
	int ans=-1;
	for(int p=1;p<=n;p++)
	{
		ull hash=(pre[n]-pre[p]*pw[n-p])*pw[p]+suf[1]-suf[p+1]*pw[p];
		if(hash==k1||hash==k0){ans=p;break;}
	}
	cout<<ans<<'\n';
	return 0;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T;cin>>T;while(T--)mian();
	return 0;
}
```

---

## 作者：ttq012 (赞：1)

首先考虑暴力求解。枚举每一个 $i$，然后暴力 check 一下是否符合条件。

考虑优化上面的暴力。首先观察得到上面的这个操作其实就是让字符串 $s$ 变为 $s_{p+1}s_{p+2}s_{p+3}\ldots s_ns_ps_{p-1}s_{p-2}\ldots s_2s_1$。

容易发现这个字符串其实可以被分割为 $s_{p+1}s_{p+2}s_{p+3}\ldots s_n$ 和 $s_ps_{p-1}s_{p-2}\ldots s_2s_1$ 两个部分。

然后再观察 $k$ -proper 的性质。

容易发现一个 $k$ -proper 其实只有两种不同的情况：

+ $s_1=s_2=s_3=\ldots=s_k=1,s_{k+1}=s_{k+2}=s_{k+3}=\ldots=s_{2k}=0,s_{2k+1}=s_{2k+2}=s_{2k+3}=\ldots=s_{3k}=1,s_{3k+1}=s_{3k+2}=s_{3k+3}=\ldots=s_{4k}=0$，以此类推。令生成的这个字符串为 $S_1$。
+ $s_1=s_2=s_3=\ldots=s_k=0,s_{k+1}=s_{k+2}=s_{k+3}=\ldots=s_{2k}=1,s_{2k+1}=s_{2k+2}=s_{2k+3}=\ldots=s_{3k}=0,s_{3k+1}=s_{3k+2}=s_{3k+3}=\ldots=s_{4k}=1$，以此类推。令生成的这个字符串为 $S_2$。

然后就可以去做这个题目啦。首先考虑字符串的前半部分 $s_{p+1}s_{p+2}s_{p+3}\ldots s_n$。容易发现这个部分必须和 $S_1$ 或者 $S_2$ 的长度为 $n-p$ 的前缀**完全相同**。后半部分 $s_ps_{p-1}s_{p-2}\ldots s_2s_1$ 的最长的长度为 $k$ 的倍数的后缀必须和 $S_1$ 或者 $S_2$ 等长的前缀**完全相同**。

此时还（可能）在第二个字符串前缀中剩下 $s_{p}s_{p-1}s_{p-2}\ldots s_q$ 这样的一个字符串，容易发现这样的一个字符串的长度为 $p-q+1$。那么此时将这个字符串直接接到第一个字符串上去，判断这个字符串是否仍然和 $S_1$ 或者 $S_2$ 等长的前缀字符串**完全相同**。

容易发现 $S_1$ 和 $S_2$ 的长度取到 $n$ 就够了。但是问题是判断两个字符串匹配的时间复杂度仍然为 $O(n)$。因此考虑哈希判定（是显然的）。总的时间复杂度为 $O(n)$，注意要使用**四哈希**防止被卡。代码细节很多。

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define em emplace_back
#define F(i,x,y) for(int i=x;i<=y;i++)
#define G(i,x,y) for(int i=x;i>=y;i--)
#define W(G,i,x) for(auto&i:G[x])
#define W_(G,i,j,x) for(auto&[i,j]:G[x])
#define add(x,y) z[x].em(y)
#define add_(x,y) add(x,y),add(y,x)
#define Add(x,y,d) z[x].em(y,d)
#define Add_(x,y,z) Add(x,y,z),Add(y,x,z);
#ifdef int
#define inf (7611257611378358090ll/2)
#else
#define inf 0x3f3f3f3f
#endif
using namespace std;
int ll(int a, int b) {
    return a / __gcd(a, b) * b;
}
const int N = 400100;
int s1[N], s2[N];
struct Hash {
    int h1, h2, h3, h4;
    bool operator==(const Hash &r) const {
        return h1 == r.h1 && h2 == r.h2 && h3 == r.h3 && h4 == r.h4;
    }
} ;
const int m1 = 1e9 + 9, m2 = 998244353, m3 = 998244853, m4 = 19260817;
Hash hh1[N], hh2[N], hh3[N], hh4[N];
int bit1[N], bit2[N], bit3[N], bit4[N];
char ss[N], st[N];
Hash get(Hash *h, int l, int r) {
    int v1, v2, v3, v4;
    v1 = h[r].h1 - h[l - 1].h1 * bit1[r - l + 1] % m1, v1 %= m1; v1 += m1; v1 %= m1;
    v2 = h[r].h2 - h[l - 1].h2 * bit2[r - l + 1] % m2, v2 %= m2; v2 += m2; v2 %= m2;
    v3 = h[r].h3 - h[l - 1].h3 * bit3[r - l + 1] % m3, v3 %= m3; v3 += m3; v3 %= m3;
    v4 = h[r].h4 - h[l - 1].h4 * bit4[r - l + 1] % m4, v4 %= m4; v4 += m4; v4 %= m4;
    return {v1, v2, v3, v4};
}
signed main() {
    int T;
    cin >> T;
    bit1[0] = bit2[0] = bit3[0] = bit4[0] = 1;
    F(i, 1, N - 1) {
        bit1[i] = bit1[i - 1] * 131 % m1;
        bit2[i] = bit2[i - 1] * 1331 % m2;
        bit3[i] = bit3[i - 1] * 13331 % m3;
        bit4[i] = bit4[i - 1] * 133331 % m4;
    }
    while (T--) {
        int n, m;
        cin >> n >> m;
        string s;
        cin >> s;
        s = ' ' + s;
        for (int i = 0; i <= n + 5; i++) {
            hh1[i].h1 = hh1[i].h2 = hh1[i].h3 = hh1[i].h4 = hh2[i].h1 = hh2[i].h2 = hh2[i].h3 = hh2[i].h4 = hh3[i].h1 = hh3[i].h2 = hh3[i].h3 = hh3[i].h4 = hh4[i].h1 = hh4[i].h2 = hh4[i].h3 = hh4[i].h4 = s1[i] = s2[i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            if ((i - 1) % (2 * m) < m) {
                ss[i] = '1';
                st[i] = '0';
            } else {
                ss[i] = '0';
                st[i] = '1';
            }
        }
        for (int i = 1; i <= n; i++) {
            s1[i] = s1[i - 1];
            if (s[i] == '1') {
                s1[i]++;
            }
            hh1[i].h1 = hh1[i - 1].h1 * 131 + s[i]; hh1[i].h1 %= m1;
            hh1[i].h2 = hh1[i - 1].h2 * 1331 + s[i]; hh1[i].h2 %= m2;
            hh1[i].h3 = hh1[i - 1].h3 * 13331 + s[i]; hh1[i].h3 %= m3;
            hh1[i].h4 = hh1[i - 1].h4 * 133331 + s[i]; hh1[i].h4 %= m4;
        }
        for (int i = n; i; i--) {
            s2[i] = s2[i + 1];
            if (s[i] == '1') {
                s2[i]++;
            }
            hh2[n - i + 1].h1 = hh2[n - i + 1 - 1].h1 * 131 + s[i]; hh2[n - i + 1].h1 %= m1;
            hh2[n - i + 1].h2 = hh2[n - i + 1 - 1].h2 * 1331 + s[i]; hh2[n - i + 1].h2 %= m2;
            hh2[n - i + 1].h3 = hh2[n - i + 1 - 1].h3 * 13331 + s[i]; hh2[n - i + 1].h3 %= m3;
            hh2[n - i + 1].h4 = hh2[n - i + 1 - 1].h4 * 133331 + s[i]; hh2[n - i + 1].h4 %= m4;
        }
        for (int i = 1; i <= n; i++) {
            hh3[i].h1 = hh3[i - 1].h1 * 131 + ss[i]; hh3[i].h1 %= m1;
            hh3[i].h2 = hh3[i - 1].h2 * 1331 + ss[i]; hh3[i].h2 %= m2;
            hh3[i].h3 = hh3[i - 1].h3 * 13331 + ss[i]; hh3[i].h3 %= m3;
            hh3[i].h4 = hh3[i - 1].h4 * 133331 + ss[i]; hh3[i].h4 %= m4;
            hh4[i].h1 = hh4[i - 1].h1 * 131 + st[i]; hh4[i].h1 %= m1;
            hh4[i].h2 = hh4[i - 1].h2 * 1331 + st[i]; hh4[i].h2 %= m2;
            hh4[i].h3 = hh4[i - 1].h3 * 13331 + st[i]; hh4[i].h3 %= m3;
            hh4[i].h4 = hh4[i - 1].h4 * 133331 + st[i]; hh4[i].h4 %= m4;
        }
        int id = -1;
        for (int i = 1; i <= n; i++) {
            if (i == n || s[i + 1] == '1') {
                int len = n - i;
                if (get(hh1, i + 1, n) == get(hh3, 1, len)) {
                    int remainlen = (m - len % m) % m;
                    if (remainlen && ss[len + 1] == '1' || !remainlen && ss[len + 1] == '0') {
                        if (s1[i] - s1[i - remainlen] == remainlen) {
                            if (get(hh2, n - (i - remainlen) + 1, n) == get(hh4, 1, i - remainlen)) {
                                id = i;
                                break;
                            }
                        }
                    } else {
                        if (s1[i] - s1[i - remainlen] == 0) {
                            if (get(hh2, n - (i - remainlen) + 1, n) == get(hh3, 1, i - remainlen)) {
                                id = i;
                                break;
                            }
                        }
                    }
                }
            } else {
                int len = n - i;
                if (get(hh1, i + 1, n) == get(hh4, 1, len)) {
                    int remainlen = (m - len % m) % m;
                    if (st[len] == '1') {
                        if (s1[i] - s1[i - remainlen] == remainlen) {
                            if (get(hh2, n - (i - remainlen) + 1, n) == get(hh4, 1, i - remainlen)) {
                                id = i;
                                break;
                            }
                        }
                    } else {
                        if (s1[i] - s1[i - remainlen] == 0) {
                            if (get(hh2, n - (i - remainlen) + 1, n) == get(hh3, 1, i - remainlen)) {
                                id = i;
                                break;
                            }
                        }
                    }
                }
            }
        }
        cout << id << '\n';
    }
}

---

## 作者：DDF_ (赞：0)

## 题面

给一个 $01$ 串 $s$ 和一个正整数 $k$，求 $p$，使得将前 $p$ 位反转拼到 $s$ 末尾后，$s$ 满足：$s$ 中 $[1,k]$ 的子串所有元素相同，且 $\forall i \in [1,n-k], s_{i} \neq s_{i+k}$。

## 题解

注意力惊人，注意到操作的字符串一定是 `111000111000...` 或 `000111000111...` 的形式（$k=3$）。 

然后就枚举所有断点，将在这个断点操作后的字符串与上述两种串匹配，如果行就直接输出即可。

但是这样太暴力了，一看是绿题，掐指一算时间复杂度 $O(n^{2})$，过不了，喜提 TLE。

所以，有没有时间复杂度低，可维护的匹配两个字符串的方法呢？

有的兄弟有的，这个算法叫字符串哈希。

将前后两个串的哈希算出来，然后算操作后的串的哈希。我这里用的是多项式哈希，由多项式哈希的定义，得整串哈希值为将右串哈希值 $hr$ 乘上 $B^{p}$ 再加上左串哈希值 $hl$。

提前预处理上面两个串的哈希，判断每个断点上操作的哈希值是否相等即可。

我用的是自然溢出。

## 代码

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const ull base=41;
const int N=1e5+2;
int t;
int n,p,ans;
char s[N],s1[N],s2[N];
ull hl,hr[N],h1,h2;
ull power(ull a,ull b) {
	ull res=1;
	while(b) {
		if(b&1) res*=a;
		a*=a,b>>=1;
	}
	return res;
}
void work() {
	scanf("%d%d",&n,&p);
	cin>>(s+1);
	for(int i=1;i<=n/p;i++) for(int j=1;j<=p;j++) s1[(i-1)*p+j]=(i%2==0)?'0':'1',s2[(i-1)*p+j]=(i%2==0)?'1':'0';
	hl=h1=h2=0llu,ans=-1;
	memset(hr,0,sizeof hr);
	ull k=1llu,k1=1llu;
	for(int i=n;i;i--) h1=h1+(s1[i]=='1')*k,h2=h2+(s2[i]=='1')*k,hr[i]=hr[i+1]+(s[i]=='1')*k,k*=base;
	for(int i=1;i<=n;i++) {
		hl=hl+(s[i]=='1')*k1,k1*=base;
		ull h=hl+hr[i+1]*k1;
		if(h==h1||h==h2) {ans=i;break;}
	}
	printf("%d\n",ans);
	return;
}
int main() {
	scanf("%d",&t);
	while(t--) work();
	return 0;
}
```

---

## 作者：Rt__ (赞：0)

[CF1979D Fixing a Binary String](https://www.luogu.com.cn/problem/CF1979D)
## 题意简述
给定一个字符串，对它进行下面的三个操作一次：

1. 选定一个长度 $p$；
2. 将字符串 $1\sim p$ 翻转；
3. 将翻转后的 $1\sim p$，接到末尾。

给定 $k$，问选择一个 $p$，是否能构造出一个字符串形如
```
000111000111...（以k为周期）
```
## 思路
只操作一次，说明只可以将一个断开的周期拼成一块，所以我们就想着找到这个断开的周期。再仔细观察，我们发现由于它是拼到末尾，所以如果有断的，末尾肯定有一部分断开的。所以我们可以从末尾第二段开始找，找到第一个长度不为 $k$ 的区间，把它加上他前面的翻转一下，然后直接拼到最后去，判断合不合法就行。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 200010;

int fr[N], ba[N];

signed main(){
	int t;
	cin >> t;
	while(t --){
		string s;
		int n, k;
		cin >> n >> k >> s;
		
		s = ' ' + s;
		int cnt = 0;
		for(int i = 1; i <= n; i ++){
			if(s[i] == s[i - 1]){
				cnt ++;
				fr[i] = cnt;
			}
			else{
				cnt = 1;
				fr[i] = cnt;
			}
		}
		cnt = 1;
		ba[n] = 1;
		for(int i = n - 1; i >= 1; i --){
			if(s[i] == s[i + 1]){
				cnt ++;
				ba[i] = cnt;
			}
			else{
				cnt = 1;
				ba[i] = cnt;
			}
		}
		int now = fr[n] - 1;
		bool flag = 1, flagg = 0;
		string ss, c1, c0;
		// if(n % k){
		// 	cout << -1;
		// 	goto loop;
		// }
		if(n == k){
			if(ba[1] != n){
				cout << -1;
				goto loop;
			}
		}
		now = n - fr[n];
		while(fr[now] == k){
			now -= fr[now];
		}
		if(fr[now] > k)now -= k;
		reverse(s. begin() + 1, s. begin() + 1 + now);
		ss = s. substr(now + 1) + s. substr(1, now); 
		c1 = "", c0 = "";
		for(int i = 1; i <= k; i ++)c1 = c1 + '1', c0 = c0 + '0';
		
		for(int i = 0; i < n - k; i += k){
			if((ss. substr(i, k) == c1 && ss. substr(i + k, k) == c0) || (ss. substr(i, k) == c0 && ss. substr(i + k, k) == c1)){
				flagg = 1;
			}
			else flag = 0;
		}
		if(flag && flagg || fr[n] == k && fr[n] == n){
			if(now == 0)now = n;
			cout << now;
		}
		else {
			cout << -1;
		}
loop:
		cout << endl;
	}
    return 0;
}
```

---

## 作者：I_will_AKIOI (赞：0)

观察一个字符串 $s$ 是 $k\operatorname{-proper}$ 需要满足的两个条件，我们手玩一下会发现只有可能是 $k$ 个 $0$ 和 $k$ 个 $1$ 交替构成的。

接着我们看操作的过程，一个字符串 $s$ 选择了整数 $p$ 进行操作，会发现是将 $s$ 选择 $p-1$ 进行操作后，将 $s_1$ 放到
 $s_{n-i}$ 之后。我们可以维护两个整数 $x,y$ 表示当前的哈希值，开始 $x$ 为 $s$ 的哈希值，然后每次操作就是将 $x$ 的最高位扔掉，放到 $y$ 的最高位。最后将 $x$ 和 $y$ 拼接起来就是 $s$ 的哈希值。举个例子，开始 $s=\text{110001100110},k=2$，则操作如下。
 
第一次：$x=110001100110,y=0$。

第二次：$x=10001100110,y=1$。

第三次：$x=001100110,y=011$。（这里补 $0$ 是为了方便看）

发现第三次 $x$ 和 $y$ 拼起来为 $001100110011$，构成了 $k\operatorname{-proper}$ 的形式，所以我们把两种 $k\operatorname{-proper}$ 的形式也给哈希一下，然后判断 $x$ 和 $y$ 拼起来是否和其中一个哈希值相等即可。

```cpp#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define BASE 13331
#define N 100005
#pragma GCC optimize("O3")
using namespace std;
int n,k,h1,h2,u,v,p[N*2];
string s;
void solve()
{
  cin>>n>>k>>s;
  p[0]=1;
  u=v=h1=h2=0;
  for(int i=1;i<=n;i++) p[i]=p[i-1]*BASE%mod,u=(u*BASE+s[i-1]-48)%mod;//计算开始的哈希值
  for(int i=0;i<n;i++)//k-proper的形式哈希值
  {
    h1=h1*BASE%mod;
    h2=h2*BASE%mod;
    if(i/k%2==0) h1++;
    else h2++;
  }
  for(int i=0;i<n;i++)
  {
    if(i>0&&((u*p[i]+v)%mod==h1||(u*p[i]+v)%mod==h2))//x和y拼起来是否和哈希值相等，注意开始是k-proper也需要操作
    {
      cout<<i<<"\n";
      return;
    }
    u=((u-p[n-i-1]*(s[i]-48)%mod)+mod)%mod;
    v=(v+p[i]*(s[i]-48))%mod;
    //将u的最高位放到v的最位
  }
  cout<<-1<<"\n";
  return;
}
signed main()
{
  ios::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--) solve();
  return 0;
}
```

---

## 作者：Mashu77 (赞：0)

给定一个字符串，定义字符串 $s$ 是 $p$ 好的当且仅当 $s_1=s_2=\cdots =s_p$ 且任意 $i \leq n-p$ 都有 $s_i \neq s_{i+p}$，现在你必须对字符串做一次操作：反转一个前缀然后接到后面，问怎么操作能让字符串变成 $p$ 好的，$p$ 给定。

这个题的关键可能就是你不能一直想分讨一些情况简化条件，而是你要想我们先就硬做，不满足会怎么样。

一个不难发现的点是这其实等价于我把一个后缀 reverse 然后判断是不是 $p$ 好，然后你先尝试从第一个字符往前走，看看不操作到哪里会变得不好。

接着你会发现这个点如果不是某个连续相同块的开头，那么你只可能把它所标志的前缀做上述操作，否则你还得看一下后面少了多少个类似的字符，然后相匹配地进行操作，只要这两个分讨论就可以结束。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {

int tt;cin>>tt;
while(tt--){
   int n,k;cin>>n>>k;
   string p="",q="",a,b;string s;cin>>s;
   for(int i=0;i<k;i++)p+='0',q+='1';
   while(a.size()<n){
       a+=p;
       b+=q;
       if(a.size()>=n)break;
       a+=q;
       b+=p;
   }
   
   string x;
   int ans=-1;
   for(int i=0;i<n;i++){
      x=s[0]+x;
      s.erase(s.begin());
      string p=s+x;
      if(p==a||p==b){
          ans=i+1;
          break;
      }
   }
   
   cout<<ans<<endl;
   
}
}

---

## 作者：zengziqvan (赞：0)

考虑枚举 $p$，对每个 $p$ 判断是否合法。

由于 $k\mid n$，故容易发现最终的合法串一定是如下两种，这里设 $k=4$：

$11110000111100001111\dots$

$00001111000011110000\dots$

所以我们直接构造上述两种串，并且算出它们的 Hash 值。

```c++
int op=0;
for(int i=1;i<=n;i+=k) {
	op^=1;
	FOR(j,i,i+k-1) {
		a0[j]=(op+48);
		a1[j]=((op^1)+48);
	}
} 
FOR(i,1,n) {
	h1=h1*P+a0[i];//第一种串
	h2=h2*P+a1[i];//第二种串
}
```
考虑生成 $S$ 倒着读的串 $S'$，同时求出两串的前缀 Hash 值，这样方便后续判定。

不难发现，对于一个 $p$，其两次操作后形成的串一定是**由 $S$ 的后 $n-p$ 个字符与 $S'$ 的后 $p$ 个字符拼起来的**（可以自己手玩样例推一下）。

这个新串的 Hash 值是可以 $\operatorname{O}(1)$ 求的。

所以就做完了，时间复杂度 $\operatorname{O}(n)$。

```c++
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define FOR(i,l,r) for(int i=l;i<=r;++i)
#define ROF(i,r,l) for(int i=r;i>=l;--i)
#define mkp make_pair
#define fr first
#define se second
using namespace std;
const int N=1e5+10,P=131;
int t,n,k;
char a[N],b[N],a0[N],a1[N];
ull H[N],Hr[N],p[N],h1,h2;
ull Get2(int l,int r) {
	return Hr[r]-Hr[l-1]*p[r-l+1];
}
ull Get1(int l,int r) {
	return H[r]-H[l-1]*p[r-l+1];
}
void solve() {
	cin>>n>>k;int op=0;
	for(int i=1;i<=n;i+=k) {
		op^=1;
		FOR(j,i,i+k-1) {
			a0[j]=(op+48);
			a1[j]=((op^1)+48);
		}
	} 
	scanf("%s",a+1);
	h1=h2=0;
	FOR(i,1,n) {
		b[i]=a[i];
		H[i]=H[i-1]*P+a[i];
		h1=h1*P+a0[i];
		h2=h2*P+a1[i];
	}
	reverse(b+1,b+n+1);
	FOR(i,1,n) Hr[i]=Hr[i-1]*P+b[i];
   int ok=1;
	FOR(i,1,n) {
		ull nw=Get1(i+1,n)*p[i]+Get2(n-i+1,n);//求 p=i 时操作后的串的 Hash 值
		if((nw==h1||nw==h2)&&ok) {
			cout<<i<<"\n";
			ok=0;
		}
	}
	if(ok) puts("-1");//无解
	return ;
}
int main() {
	cin>>t;p[0]=1;
	FOR(i,1,100000) p[i]=p[i-1]*P;//处理 p 的整次幂
	while(t--) solve();
	return 0;
}
```

---

## 作者：ZhongYuLin (赞：0)

不难注意到，成立的情况为 $k$ 个 $0$ 和 $k$ 个 $1$ 交错出现。显然这种情况只有两种。考虑去枚举 $p$，操作后进行比较。要比较字符串大概率用哈希。但是怎么去维护呢？实际上，我们维护前后缀哈希，就可以维护翻转；再利用拼接字符串的公式，就可以维护循环移位。而本人没有脑子，不想写前后缀哈希，于是使用线段树。

```cpp
#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
using namespace std;
using ll=long long;
const int N=2e5+3,M=13331,P=998244353;
int n,cnt,k;
bool a[N],b[N];
ll h1,h2;
string s;
ll t1[N<<2],t2[N<<2],h[N];
void push_up(int l,int r,int p){
    int mid=l+r>>1;
    t1[p]=(t1[ls]*h[r-mid]%P+t1[rs])%P;
    t2[p]=(t2[rs]*h[mid-l+1]%P+t2[ls])%P;
}
void build(int l=1,int r=n,int p=1){
    if(l==r){t1[p]=t2[p]=a[l];return;}
    int mid=l+r>>1;
    build(l,mid,ls);build(mid+1,r,rs);
    push_up(l,r,p);
}
ll q1(int x,int y,int l=1,int r=n,int p=1){
    if(y<x)return 0;
    if(x<=l&&r<=y)return t1[p];
    int mid=l+r>>1;
    if(y<=mid)return q1(x,y,l,mid,ls);
    if(x>mid)return q1(x,y,mid+1,r,rs);
    return (q1(x,y,l,mid,ls)*h[r-mid]%P+q1(x,y,mid+1,r,rs))%P;
}
ll q2(int x,int y,int l=1,int r=n,int p=1){
    if(y<x)return 0;
    if(x<=l&&r<=y)return t2[p];
    int mid=l+r>>1;
    if(y<=mid)return q2(x,y,l,mid,ls);
    if(x>mid)return q2(x,y,mid+1,r,rs);
    return (q2(x,y,l,mid,ls)+q2(x,y,mid+1,r,rs)*h[mid-l+1]%P)%P;
}
void solve(){
    cin>>n>>k>>s;cnt=0;h1=h2=0;int tot=0;
    for(int i=1;i<=n;++i)a[i]=s[i-1]-'0',cnt+=a[i];
    build();
    for(int i=1;i<=k;++i)a[i]=1;
    for(int i=k+1;i<=n;++i)a[i]=!a[i-k];
    for(int i=1;i<=n;++i)h1=h1*M%P+a[i],tot+=a[i];
    if(tot!=cnt)h1=-1;
    tot=0;
    for(int i=1;i<=k;++i)a[i]=0;
    for(int i=k+1;i<=n;++i)a[i]=!a[i-k];
    for(int i=1;i<=n;++i)h2=h2*M%P+a[i],tot+=a[i];
    if(tot!=cnt)h2=-1;
    for(int p=1;p<=n;++p){
        ll k=(q1(p+1,n)*h[p]%P+q2(1,p))%P;
        if(k==h1||k==h2){printf("%d\n",p);return;}
    }puts("-1");
}
int main(){
    ios::sync_with_stdio(cin.tie(cout.tie(0)));
    for(int i=h[0]=1;i<N;++i)h[i]=h[i-1]*M%P;
    int T;for(cin>>T;T--;)solve();
    return 0;
}
```

---

