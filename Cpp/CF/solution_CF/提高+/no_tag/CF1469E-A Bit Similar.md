# A Bit Similar

## 题目描述

Let's call two strings $ a $ and $ b $ (both of length $ k $ ) a bit similar if they have the same character in some position, i. e. there exists at least one $ i \in [1, k] $ such that $ a_i = b_i $ .

You are given a binary string $ s $ of length $ n $ (a string of $ n $ characters 0 and/or 1) and an integer $ k $ . Let's denote the string $ s[i..j] $ as the substring of $ s $ starting from the $ i $ -th character and ending with the $ j $ -th character (that is, $ s[i..j] = s_i s_{i + 1} s_{i + 2} \dots s_{j - 1} s_j $ ).

Let's call a binary string $ t $ of length $ k $ beautiful if it is a bit similar to all substrings of $ s $ having length exactly $ k $ ; that is, it is a bit similar to $ s[1..k], s[2..k+1], \dots, s[n-k+1..n] $ .

Your goal is to find the lexicographically smallest string $ t $ that is beautiful, or report that no such string exists. String $ x $ is lexicographically less than string $ y $ if either $ x $ is a prefix of $ y $ (and $ x \ne y $ ), or there exists such $ i $ ( $ 1 \le i \le \min(|x|, |y|) $ ), that $ x_i < y_i $ , and for any $ j $ ( $ 1 \le j < i $ ) $ x_j = y_j $ .

## 样例 #1

### 输入

```
7
4 2
0110
4 2
1001
9 3
010001110
9 3
101110001
10 3
0101110001
10 10
1111111111
11 10
11111111110```

### 输出

```
YES
11
YES
00
YES
010
YES
101
NO
YES
0000000001
YES
0000000010```

# 题解

## 作者：灵茶山艾府 (赞：8)

提供一个 $O(n)$ 的做法。

### 提示 1

设答案为 $t$。定义 $\sim t$ 为 $t$ 取反后的结果。

如果 $\sim t$ 在 $s$ 中，那么这个 $t$ 是不合法的。
由于 $s$ 有 $n-k+1$ 个长为 $k$ 的子串，如果 $2^k > n-k+1$，那么肯定存在 $t$，使得 $\sim t$ 不在这 $n-k+1$ 个子串中。

注：根据 de Bruijn sequence，当 $2^k = n-k+1$ 时，可以构造出这样的字符串 $s$，使得这 $n-k+1$ 个子串都互不相同。

### 提示 2

分类讨论：

- 如果 $k$ 比较小（$2^k \le n-k+1$），那么 $t$ 可能不存在。此时可以暴力枚举（滑窗）所有长为 $k$ 的子串（转换成整数），存到一个集合中，然后从小到大枚举 $t$，如果 $\sim t$ 不在集合中，那么这个 $t$ 就是答案。也可以从大到小枚举 $\sim t$，如果 $\sim t$ 不在集合中那么 $t$ 就是答案。
- 如果 $k$ 比较大，那么只需要关心 $t$ 的长为 $\log_2 n$ 的后缀填什么，而 $t$ 的长为 $k-\log_2 n$ 的前缀全填 $0$ 就行。做法是在 $s$ 中找 $\sim t$，即先出现 $k-\log_2 n$ 个 $1$，然后把这之后 $\log_2 n$ 个字符的整数值记到集合中。最后再和上面一样枚举 $t$ 或者 $\sim t$。

统计 $1$ 的个数可以用滑窗。

字符串转成二进制整数也可以可以用滑窗。

通过双滑窗，就可以做到 $O(n)$ 的时间复杂度。

### AC 代码（Go）

```go
package main

import (
	"bufio"
	. "fmt"
	"math/bits"
	"os"
	"strconv"
	"strings"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var T, n, k int
	var s string
next:
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &n, &k, &s)
		if n == 1 {
			Fprintln(out, "YES")
			Fprintln(out, s[0]&1)
			continue
		}
		k2 := bits.Len(uint(n)) - 1
		left := k - k2
		if left <= 0 {
			has := make([]bool, 1<<k)
			mask := 1<<(k-1) - 1
			v, _ := strconv.ParseUint(s[:k-1], 2, 64)
			x := int(v)
			for _, c := range s[k-1:] {
				x = x<<1 | int(c&1)
				has[x] = true
				x &= mask
			}
			for i := 1<<k - 1; i >= 0; i-- {
				if !has[i] {
					Fprintf(out, "YES\n%0*b\n", k, 1<<k-1^i)
					continue next
				}
			}
			Fprintln(out, "NO")
		} else {
			has := make([]bool, 1<<k2)
			mask := 1<<(k2-1) - 1
			c1 := strings.Count(s[:left-1], "1")
			v, _ := strconv.ParseUint(s[left:left+k2-1], 2, 64)
			x := int(v)
			for i := left - 1; i+k2 < n; i++ {
				c1 += int(s[i] & 1)
				x = x<<1 | int(s[i+k2]&1)
				if c1 == left {
					has[x] = true
				}
				x &= mask
				c1 -= int(s[i-left+1] & 1)
			}
			for i := 1<<k2 - 1; ; i-- {
				if !has[i] {
					Fprintf(out, "YES\n%s%0*b\n", strings.Repeat("0", left), k2, 1<<k2-1^i)
					break
				}
			}
		}
	}
}
```


---

## 作者：quest_2 (赞：7)

推一下蒟蒻 [$\color{limegreen}\texttt{博客}$](https://www.luogu.com.cn/blog/quest233/#) ～

-----

~~**倒垃圾（bushi）：**~~

阴间题，赛时PP了以为稳极，谁知道第二天一早醒来就收到了被叉的噩耗/fn

-----

**会被叉的思路**：

我一看，$n$ 不超 $1e6$ ，那么我们大可直接枚举子串（ $1e6$ 级别），从而刷出一些“危险”的串，即与某个长度为 $k$ 的子串 **没有任何一位相同** 的串。

因为这是一个可爱的01串，所以直接取反串即可（这个反串说的是每位 **取反** 后的串）。

把这些危险串存起来，显然这些串一共也不超过 $1e6$ 个。也就是说，必然存在一个 $20$ 位的 $01$ 串，和这些危险串互异。（ $2^{20}>1e6$ ）

很舒适，那么直接枚举这个 $01$ 串即可。确保了最后 $20$ 位的 “A bit similar” 之后，其它的位上我们就可以 **自由发挥** 了。

它让我们取最小字典序，那么我们只需在其他位上都填 $0$ 即可。

这太简单了叭，我也能有一天 $1h$ 不到切E题，蛤蛤蛤蛤蛤……

真的如此吗？

----

**我为什么又又又又被叉了：**

考虑我们“自由发挥”的时候，我们把一些位置填上了 $0$ 。

但是当我们把这些位置填上 $0$ 的时候，是否想过，如果在这里填 $0$ 就可以 **防出去一些危险串** 的话，那这些被防出去的串是不是就 **不危险** 了？

如果这样一个被防出去的串的字典序更小，是不是就可以替换答案了？

得在原来的瑇码上缝缝补补以应对这种情况。

以下是代码，实现方法在注释里：

```cpp
#include <bits/stdc++.h>

using namespace std;
const int MAX = 4e6 + 7;
int N, M;
string s;
int dan[MAX];
int ok[MAX];
void solve(int T)
{
	cin >> N >> M >> s;
	int st = max(0, M - 20); //有多长的长度可以自由发挥
	string ans = "";
	for (int i = 0; i < st; i++) //先全0
	{
		ans += "0";
	}
	if (st > 0) //如果可以自由发挥
	{
		int j = 0;
		for (int i = 0; i < N; i++)
		{
			if (s[i] == '0')
			{
				j = max(i - st + 1, j);
				while (j <= i) //这说明从j到i这块地儿可以直接防出去
				{
					ok[j] = T; //用询问编号作为 ok 的标记是为了珍爱生命远离memset
					j++;
				}
			}
		}
	}
	for (int i = 0; i + M <= N; i++)
	{
		if (ok[i] == T) //防出去那就不管了
			continue;
		int cur = 0;
		for (int j = st; j < M; j++) //否则这个串就是危险子串
		{
			cur = cur * 2 + s[i + j] - '0'; //取出这个串
		}
		dan[cur] = T;
	}
	for (int mask = 0; mask < (1 << (M - st)); mask++) //枚举到2^{M-st}
	{
		if (dan[mask ^ ((1 << (M - st)) - 1)] == T) //这是危险的，不能用
										    //异或上 ((1 << (M - st)) - 1) 即取出 (M - st) 位以下的部分
			continue;
		cout << "YES\n";
		cout << ans;				    //一些0
		for (int i = M - 1; i >= st; i--) //输出和危险串都互异的那个01串
		{
			if (mask & (1 << (i - st)))
			{
				cout << 1;
			}
			else
			{
				cout << 0;
			}
		}
		cout << "\n";
		return;
	}
	cout << "NO\n";
}
int main()
{
	int T = 1;
	cin >> T;
	for (int i = 1; i <= T; i++)
	{
		solve(i);
	}
	return 0;
}

```

这样你就通过了这道题～

-----

~~**花絮：**~~

![](https://cdn.luogu.com.cn/upload/image_hosting/pcdcqv1j.png)

---

## 作者：zjjws (赞：2)

觉得这道题挺妙的，考场上因为过于 Naive 而被 Hacked，导致排名 $200\to 600$。

首先把题意转化一下，就是所有长度为 $k$ 的这 $n-k+1$ 个 01 串，它们 **取反的结果不能作为答案**。因为只要满足答案不等于这个子串的取反（所有 $0$ 变 $1$，$1$ 变 $0$），那么必然包含一位与这个字串相等。

于是你就得到了 $n-k+1$ 个长度为 $k$ 的 **限制串**（为原子串取反的结果），规定了答案不能等于这些串。

这里有一个 **非常显然** ~~但我也没有发现~~ 的结论。

就是对于答案串，只要保证它的后 $x$ 位和那些限制串的后 $x$ 位不相等，那便是合法的。

因为限制串的个数有限，我们只要保证 $2^x>(n-k+1)$，那么后 $x$ 位就一定可以使得答案串合法。由于需要字典序最小，所以 $[1:n-x]$ 都可以直接取 $0$。

于是乎因为只剩下了 $20$ 位，只要从小到大枚举每个串是否可行即可。

但是啊。

```
 while checking the last 20 characters of the substring people forgot to check whether the remaining all characters of that substring are zero or not.
```

不要忘记答案串前面那些全 $0$ 的已经可以把一些限制串的影响消掉了。

代码（写得可能比较奇怪）

```cpp
#include <stdio.h>
#include <string>
#include <iostream>
#define LL long long
using namespace std;
const int N=2e6+3;
inline int rin()
{
    int s=0;
    bool bj=false;
    char c=getchar();
    for(;(c>'9'||c<'0')&&c!='-';c=getchar());
    if(c=='-')bj=true,c=getchar();
    for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
    if(bj)s=-s;
    return s;
}
inline int max(int x,int y){return x>y?x:y;}

string a;
string ans;

int d[N];
int tail;

bool vit[N];

inline void work()
{
    int n=rin(),k=rin();
    cin>>a;a=" "+a;
    int ed=max(n-k+1,1);
    int s=0;
    int p=0;
    int cutt=0;
    int lens=min(k,20);
    p=(1<<lens)-1;
    tail=0;
    for(int i=k-lens+1;i<k;i++)s=(s<<1)+('1'-a[i]);
    for(int i=k-lens,j=1;j<i;j++)if(a[j]=='0')cutt++;
    for(int i=1;i<=ed;i++)
    {
        s=(s<<1)+('1'-a[i+k-1]);
        s=s&p;
        if(a[i+k-1-lens]=='0')cutt++;
        if(a[i-1]=='0')cutt--;
        if(!cutt)vit[s]=true,d[++tail]=s;
    }
    for(int i=0;i<=ed;i++)
    {
        if(!vit[i])
        {
            ans="";
            for(;i;i>>=1)ans=(char)((i&1)+'0')+ans;
            if(ans.size()>k)puts("NO");
            else 
            {
                puts("YES");
                for(i=ans.size()+1;i<=k;i++)putchar(48);
                cout<<ans;
                putchar('\n');
            }
            break;
        }
    }
    for(;tail;tail--)vit[d[tail]]=false;
}
int main()
{
    int i,j;
    for(int T=rin();T;T--)work();
    return 0;
}
```

---

## 作者：naroanah (赞：1)

很妙。发现直接找符合条件的不好做，反过来考虑，不满足条件的序列是怎样的。

很容易发现，对于 $s$ 的每个长度为 $k$ 的子串，按位取反后就是一个不合法的串，一共有 $n - k + 1$ 长度为 $k$ 的子串，最坏情况下（互不相同），就会有 $n - k + 1$ 个不能选，设 $z = n - k + 1$ ，显然当 $2 ^ k > z$ 时一定有解。

考虑如何构造解，设 $lg = \lceil \log_2 {(z+1)} \rceil$，那么前面的 $k - lg$ 位用不到，可以全部填 $0$，后面的位共有 $2 ^ {lg}$ 种情况，$O(n)$ 划窗去掉所有不合法的 ，找到剩下最小的转成二进制输出就是答案，可以开桶，也可以用 set 维护。

坑点不少：

- 由于存在重复的情况， $2 ^ k \le z$ 时也可能有合法的解，不能直接特判掉。
- 前面全部填 $0$ 的部分也可能产生匹配，注意前面能匹配时这个串就合法了，不能删掉。

```cpp
int n, k;
string str;
set<int> s;
void solve() {
    cin >> n >> k >> str; str = " " + str;
    int z = n - k + 1; 
    int lg = 0; while((1 << lg) <= z) lg++;
    lg = min(lg, k);
    rep(i, 0, (1 << lg) - 1) s.insert(i);
    int now = 0, cnt = 0;
    rep(i, 1, k - lg) if(str[i] == '0') cnt++;
    req(i, k, k - lg + 1) if(str[i] == '0') now += (1 << k - i); 
    if(!cnt and s.find(now) != s.end()) s.erase(now);
    rep(i, k + 1, n) {
        if((now >> lg - 1) & 1) now -= 1 << lg - 1;
        if(str[i - k] == '0') cnt--; if(str[i - lg] == '0') cnt++;
        now <<= 1;
        if(str[i] == '0') now++;
        if(!cnt and s.find(now) != s.end()) s.erase(now);
    }
    if(s.empty()) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    int t, v = *s.begin();
    vector<int> ans; while(v) ans.push_back(v & 1), v >>= 1;
    reverse(all(ans));
    t = k - ans.size();
    rep(i, 1, t) cout << "0"; for(auto i : ans) cout << i;
    cout << "\n";
    s.clear();
}
```

~~写的丑，常数大。~~

---

## 作者：tommy0221 (赞：1)

[CF1469E A Bit Similar](https://www.luogu.com.cn/problem/CF1469E)

[更好的阅读体验](https://www.cnblogs.com/zzctommy/p/14231884.html)

~~我只是，纯粹的，来水点社贡~~

因为这道题上了一百多分呢，刷新了div.2最高记录。~~如果我A题不挂两发直接上Master了/kk~~

这是一种没有细节，只用敲863B的无脑方法，非常适合在打CF的时候使用。

这题解法好多啊，而且怎么有2400啊，感觉偏高>_<

---------------

看完题第一反应，一个串不可行，当且仅当它是原串某个长度为 $k$ 的子串的反串。

再看几眼灵光一闪直接就会了。把原串字符串哈希了，把每一个长度为 $k$ 的串的反串丢进哈希表。然后维护一个二进制 $k$ 位的大整数，初始为 $0$，每次加 $1$ ，模拟进位，动态维护这个新串的哈希值（这样显然字典序最小），直到这个串的哈希值不在原串出现，或者这个串已经是 $1111\cdots111$ 并且哈希值还是出现了，那就无解。

进位直接均摊 $O(\text{次数}) $ ，显然最多修改 $n-k+1$ 次。哈希为了不被卡用了 `map` ，虽然由于模数是自己设的不太能卡。所以复杂度大常数 $O(n\log n)$ ，CF跑跑还是很轻松的，只用了 $800ms$ 。

真的非常无脑。只不过第一次写这个动态维护哈希，而且还是自己yy出来的，有点心虚。或许很多人也是第一次见到这玩意，还是详细讲一下吧：

设当前串的哈希值为 $h$ 。

+ 末尾加 $1$ ，那么 $h+=1$ 

+ 如果第 $i$ 位要进位，那么这一位减少 $2$ ，下一位加 $1$ ，$h+=base^{i+1}-2base^i$

其实挺easy的。

~~什么？可以只考虑最后 $20$ 位？然后一群人因为没考虑前面的 $0$ fst了？这种方法完全没事/cy，毫无细节，好写多了（~~

你可能会问为啥这种东西你只写了863B。

因为，我 有 板 子 /cy。字符串哈希什么的直接拉下来就能用。~~实际3.6k~~

你可能会问CF用哈希不怕被卡吗？

+ Div.2 的rank1用的是1e7模数单哈希，我和同学一起叉了 $2h$ 叉不掉。应该有很多人尝试叉他了，但是他活的好好的。
+ 你有本事把我这个hash叉掉，我请你吃饭。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
struct Rand{
	unsigned long long sa,sb,sc;
	static const int basic=(1<<30)-1;
	Rand(){
		srand(time(0));
		sa=1ull*::rand()*::rand();
		for(int i=1,up=::rand()%100;i<=up;++i)::rand();
		srand(::rand()^clock());
		sb=1ull*::rand()*::rand();
		for(int i=1,up=::rand()%100;i<=up;++i)::rand();
		srand(::rand()^clock());
		sc=1ull*::rand()*::rand();
	}
	void init(){
		srand(time(0));
		sa=1ull*::rand()*::rand();
		for(int i=1,up=::rand()%100;i<=up;++i)::rand();
		srand(::rand()^clock());
		sb=1ull*::rand()*::rand();
		for(int i=1,up=::rand()%100;i<=up;++i)::rand();
		srand(::rand()^clock());
		sc=1ull*::rand()*::rand();
	}
	inline int rand(){
		sa^=sa<<32,sa^=sa>>13,sa^=sa<<1;
		unsigned long long t=sa;
		sa=sb,sb=sc,sc^=t^sa;
		return static_cast<int>(sc&basic)+1;
	}
	int rad(int l,int r){return rand()%(r-l+1)+l;}
};

template<int N>
struct String_Hash{

static const int O=N+5;
LL H1[O],H2[O],pw1[O],pw2[O],mod1,mod2;
int base1,base2;

String_Hash(){
	static const int base[8]={31,37,41,43,47,53,59,61};
	static const LL mod[8]={100000000000031ll,100000000000367ll,100000000000169ll,100000000000261ll,
	10000000000000069ll,10000000000000639ll,10000000000000753ll,10000000000000669ll};
	static Rand maker;
	base1=base[maker.rand()&7];
	while((base2=base[maker.rand()&7])==base1);
	mod1=mod[maker.rand()&7];
	while((mod2=mod[maker.rand()&7])==mod1);
	pw1[0]=1;for(int i=1;i<=N;++i)pw1[i]=pw1[i-1]*base1%mod1;
	pw2[0]=1;for(int i=1;i<=N;++i)pw2[i]=pw2[i-1]*base2%mod2;
}
void insert(char*str,int n){
	H1[0]=H2[0]=0;
	for(int i=1;i<=n;++i)H1[i]=(H1[i-1]*base1+str[i]-'0'+1)%mod1;
	for(int i=1;i<=n;++i)H2[i]=(H2[i-1]*base2+str[i]-'0'+1)%mod2;
}
LL mul(LL x,LL y,LL mod){
	LL res=x*y-(LL)((long double)x/mod*y+0.5)*mod;
	return res<0?res+mod:res;
}
pair<LL,LL>Hash_val(int l,int r){
	LL v1=(H1[r]-mul(H1[l-1],pw1[r-l+1],mod1)+mod1)%mod1;
	LL v2=(H2[r]-mul(H2[l-1],pw2[r-l+1],mod2)+mod2)%mod2;
	return mkp(v1,v2);
}

};
const int N=1000005;
String_Hash<N>hs;
int n,k,ans[N];
char S[N],T[N];
void Main(){
	scanf("%d%d%s",&n,&k,S+1);
	for(int i=1;i<=n;++i)T[i]='1'-S[i]+'0';
	map<pair<LL,LL>,bool>mp;
	hs.insert(T,n);
	for(int i=1;i<=n-k+1;++i)mp[hs.Hash_val(i,i+k-1)]=1;
	LL h1=0,h2=0;
	for(int i=1;i<=k;++i)h1=(h1*hs.base1+1)%hs.mod1;
	for(int i=1;i<=k;++i)h2=(h2*hs.base2+1)%hs.mod2;
	for(int i=0;i<=k;++i)ans[i]=0;
	for(int i=0;i<=n-k+1;++i){
		if(!mp[mkp(h1,h2)]){
			puts("YES");
			for(int j=1;j<=k;++j)putchar(ans[j]+'0');
			puts("");
			return;
		}
		++ans[k],h1=(h1+1)%hs.mod1,h2=(h2+1)%hs.mod2;
		int j=k;
		while(ans[j]>1){
			ans[j]=0,++ans[j-1];
			h1=(h1+hs.pw1[k-j+1]-2ll*hs.pw1[k-j]%hs.mod1+hs.mod1)%hs.mod1;
			h2=(h2+hs.pw2[k-j+1]-2ll*hs.pw2[k-j]%hs.mod2+hs.mod2)%hs.mod2;
			--j;
		}
		if(j<=0)break;
	}
	puts("NO");
}
signed main(){for(int T=read();T;--T)Main();}
```

---

## 作者：dead_X (赞：1)

## 前言
有一种自信叫我觉得我没 FST。
## 思路
A bit similar 其实就是**不是完全取反**。

也就是说只有 $10$ 和 $01$ 不是 a bit similar 的，其余都是 a bit similar 的。

于是问题变成了给 $n-k+1$ 个长度为 $k$ 的字符串，求没出现过的字典序最小的字符串。

注意到 $n-k+1\leq10^6$，因此**在最后 $20$ 位**中，必然会有一个位置空缺。因此，对于 $k\leq 20$ 的部分，我们暴力上 $\text{01-trie}$，对于 $k>20$ 的部分，我们暴力把前 $k-20$ 位都输出 $0$，然后对于最后 $20$ 位建 $\text{01-trie}$ 即可。

时间复杂度 $O(n\log n)$。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
char s[2000003];
int l[30000003],r[30000003],sz[30000003],cnt;
int n,m;
void ins(int now,int pos,int len)
{
	//printf("%d\n",now);
	if(len==0)
	{
		sz[now]=1;
		//printf("%d=1\n",now);
		return ;
	}
	int qwq=now;
	if(s[pos]=='0') 
	{
		if(!l[now]) l[now]=++cnt,l[cnt]=r[cnt]=0;
		now=l[now],ins(now,pos+1,len-1);
	 } 
	else
	{
		if(!r[now]) r[now]=++cnt,l[cnt]=r[cnt]=0;
		now=r[now],ins(now,pos+1,len-1);		
	}
	now=qwq;
	 sz[now]=sz[l[now]]+sz[r[now]];
	 //printf("%d %d %d %d\n",l[now],sz[l[now]],r[now],sz[r[now]]);
	 return ;
}
void query(int pre,int len)
{
	if(sz[1]==(1<<len))
	{
		puts("NO");
		return ;
	}
	puts("YES");
	for(int i=1; i<=pre; i++) printf("0");
	for(int i=1,j=1; j<=len; ++j) 
	{
		if(sz[l[i]]==(1<<(len-j))) printf("1"),i=r[i]; else printf("0"),i=l[i];
	}
	puts("");
}
signed main()
{
	int T=read();
	while(T--)
	{
		n=read(),m=read();
		scanf("%s",s+1);
		for(int i=1; i<=n; ++i)
		{
			if(s[i]=='0') s[i]='1';
			else s[i]='0';
		}
		int len=min(21,m);
		int cur=0;
		cnt=1,l[1]=r[1]=0;
		for(int i=1; i<m-len; i++) if(s[i]=='0') ++cur; else cur=0;
		if(len==m) for(int i=0; i<=n-len; i++) ins(1,i+1,len);
		else for(int i=m-len; i<=n-len; i++) 
		{
			if(s[i]=='0') ++cur; else cur=0;
			if(cur>=m-len) ins(1,i+1,len);
		}
		//printf("%d\n",sz[1]);
		query(m-len,len);
	}
	return 0;
}
```

---

## 作者：AsunderSquall (赞：1)

# 题意  
你有一个长度为 $n$ 的 $\text{01}$ 字符串 $s$，和给定的一个数 $k$。  
如果一个长度为 $k$ 的 $\text{01}$ 字符串 $t$ 使得，任意 $s$ 的长度为 $k$ 的子串，和 $t$ 至少有一个字符相同，那么称 $t$ 为“好的”。  
你需要求出字典序最小的“好的”的字符串。  
# 题解  
假设 $s$ 的一个长度为 $k$ 的子串为 $S$。  
我们知道 $t$ 和 $S$ 至少有一位相同。  
其实就是将 $S$ 每一位取反之后与 $t$ 不能相同。  
然后我们发现了一个很神奇的事情，就是 $s$ 至多只有 $1e6$ 个子串。   
也就是说，我们将 $s$ 的子串每一位取反之后，也至多只有 $1e6$ 个子串。  
而 $2^{20}>1e6$！  
这个性质能干什么？  
这个性质告诉我们，只枚举后 $20$ 位，就一定存在这么一个字符串 $t$，使得 $t$ 的后 $20$ 位和 每个 $s$ 的子串取反后的结果都不一样！  
那么我们开一个`bool`数组存一下每个 $s$ 的子串的后 $20$ 位的结果（hash值）。  
然后从 $0$ 枚举到 $n-k$，第一个没有出现过的数就是答案的后 $20$ 位。  
前面的全部补 0 就行了。  
注意特判以及清空。
```cpp
#include<bits/stdc++.h>
#define int long long
#define rd(x) x=read()
using namespace std;
const int N=(1<<20)+5;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int n,m,k;
string s;
string ans;
bool can[N];
vector<int> del;
signed main()
{
	int T;
	cin>>T;
	while (T--)
	{
		del.clear();
		cin>>n>>k;cin>>s;s=" "+s;
		for (int i=1;i<=n-k+1;i++)
		{
			int tmp=0;
			for (int j=max(i,i+k-20);j<=i+k-1;j++) tmp=tmp*2+('1'-s[j]);
			can[tmp]=1;
			del.push_back(tmp);
		}
		for (int i=0;i<=n-k+1;i++)
		{
			if (can[i]==0) 
			{
				ans="";int x=i;
				while (x){tmp='0'+(x&1);ans=tmp+ans;x>>=1;	} 
				if (ans.size()>k) puts("NO");
				else {puts("YES");for (int i=ans.size()+1;i<=k;i++) putchar('0');cout<<ans<<"\n";}
				break;
			}
		}
		for (int i=0;i<del.size();i++) can[del[i]]=0;
	}
}
```
好的它被`Hacked`了，我们来看看为什么。  
虽然前面的串都是 $0$，但是也会有一定的贡献。具体地说，就是我们有一些 $20$ 位的串是不用把它设为 “不能用” 的。  
那么我们计算一下每个子串的前面有几个 $0$，然后递推就行了。  
```cpp
#include<bits/stdc++.h>
#define int long long
#define ls (rt<<1)
#define rs (rt<<1|1)
#define rd(x) x=read()
using namespace std;
const int N=(1<<20)+5;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int n,m,k;
string s;
string ans;
bool can[N];
vector<int> del;
int cnt,B,E;
signed main()
{
	int T;
	cin>>T;
	while (T--)
	{
		del.clear();
		cin>>n>>k;cin>>s;s=" "+s;cnt=0;
        for (int i=1;i<max(1LL,1+k-20);i++) if (s[i]=='0') cnt++;
        B=1,E=max(1LL,1+k-20)-1;
		for (int i=1;i<=n-k+1;i++)
		{
			int tmp=0;
			for (int j=max(i,i+k-20);j<=i+k-1;j++) tmp=tmp*2+('1'-s[j]);
			//cout<<tmp<<endl;
			if (cnt==0) can[tmp]=1;
			del.push_back(tmp);
            if (s[B]=='0') cnt--;B++;
            E++;if (s[E]=='0') cnt++;
		}
		for (int i=0;i<=n-k+1;i++)
		{
			if (can[i]==0) 
			{
				ans="";int x=i;
				while (x){char tmp='0'+(x&1);ans=tmp+ans;x>>=1;	} 
				if (ans.size()>k) puts("NO");
				else {puts("YES");for (int i=ans.size()+1;i<=k;i++) putchar('0');cout<<ans<<"\n";}
				break;
			}
		}
		for (int i=0;i<del.size();i++) can[del[i]]=0;
	}
}
```

---

## 作者：AK_heaven (赞：0)

### [CF1469E](https://www.luogu.com.cn/problem/CF1469E)

首先存在性命题转化为其逆否命题，通俗的讲就是转化为它的否定命题，然后再否认这个否定命题，就和原命题等价了。

这时候问题转化为了对于每个长度为 $k$ 的反串，都不会与最终的答案串 **完全相同**。

这时候我们只需要贪心的求出答案串并保证其 Hash 值与这个反串集合不相同即可。

继续观察性质，发现如果 $n \le 10^6$ 的话，所有反串最后 $20$ 位必定存在一种情况都没有出现，因为 $10^6 < 2^{20}$，于是我们只需要贪心的枚举后 $20$ 位即可。注意，如果使用 Hash 的话建议使用多模数 Hash，不然可能会被卡掉。

---

## 作者：subcrip (赞：0)

简单哈希题。

首先观察到任何一个长度为 $k$ 的子串取反之后的数值一定是和它没有公共位的，所以肯定不行。而这样的数值至多有 $n-k+1$ 个，并不是很多，所以考虑排掉它们，剩下的就是答案。

我们用滑动窗口把每个长度为 $k$ 的子串取反之后的数值模上一个大数存到一个 `unordered_set` 中，然后枚举 $1$ 到 $n+1$ 中的每一个值，只要这个值不在 `unordered_set` 中就说明可以。

找到满足条件的值之后，把它再还原成 $01$ 串就行了。

时间复杂度 $O(n)$，前提是认为 `__builtin_ctz` 这类函数可以 $O(1)$ 计算。

Code:（为了防止 hack 这里模了两个大数）

```cpp
using mll1 = MLL<MDL1>;  // 自动取模 1
using mll2 = MLL<MDL2>;  // 自动取模 2
constexpr int N = 1e6 + 10;
mll1 pw1[N];
mll2 pw2[N];

void prep() {  // 预处理 2 的幂，滑窗时用来删除窗口最左边的数字
    pw1[0] = 1, pw2[0] = 1;
    for (int i = 1; i < N; ++i) {
        pw1[i] = pw1[i - 1] * 2;
        pw2[i] = pw2[i - 1] * 2;
    }
}

void solve() {
    read(int, n, k);
    vector<int> a;
    for (int i = 0; i < n; ++i) {
        read(char, c);
        a.emplace_back(c == '1');
    }

    unordered_set<pll, pair_hash> oc;  // 确定不行的值就放在这里

    mll1 h1 = 0;
    mll2 h2 = 0;
    for (int i = 0; i < n; ++i) {
        h1 = h1 * 2 + (a[i] ^ 1);
        h2 = h2 * 2 + (a[i] ^ 1);
        if (i >= k) {
            h1 -= pw1[k] * (a[i - k] ^ 1);
            h2 -= pw2[k] * (a[i - k] ^ 1);
        }
        if (i + 1 >= k) {
            oc.emplace(h1.val, h2.val);
        }
    }

    int res = -1;
    for (int i = 0; i < n + 2; ++i) {
        if (i and __builtin_ctz(i) >= k) {  // 如果最低位在第 k 位说明当前的数值长度超过了 k
            break;
        }
        if (not oc.count({ i, i })) {
            res = i;
            break;
        }
    }

    if (res == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        string out;
        for (int i = 0; i < k; ++i) {
            out.push_back('0' + (res & 1));
            res >>= 1;
        }
        reverse(out.begin(), out.end());
        cout << out << '\n';
    }
}
```

---

## 作者：蒟蒻君HJT (赞：0)

### 一道带有 string suffix structures 标签的题目居然没有后缀数组的题解，令人震惊。

题意：给定一个长为 $n$ 的 $01$ 串 $s$ ，求一个字典序最小的长为 $k$ 的 $01$ 串 $t$ ，使得它与 $s$ 中所有长为 $k$ 的子串至少有一位对应相同。

 考虑将 $s$ 按位取反得到串 $r$ 。那么 $t$ 合法的充要条件是它与 $r$ 中所有长为 $k$ 的子串不同。暴力怎么做呢？首先先将无解的情况判掉，即若 $r$ 中长为 $k$ 的本质不同的子串数量恰好等于 $2^k$ ，就是无解的情况。

否则，从高位往低位贪心填 $0/1$ ，假设我们当前在填第 $i$ 位（$1\leq i \leq k$），前 $i - 1$ 位已经确定了。如果 $r$ 中所有长为 $k$ 的且长为 $i-1$ 的前缀与 $t$ 相同的且第 $i$ 位为 $0$ 的子串数量是 $2^{(k-i)}$ ，说明这一位填 $0$ 的话后面填什么都没救了，只能填 $1$ ；否则填 $0$ 。同时为了完成这一操作，我们每次确定第 $i$ 位的取值的时候，要把第 $i$ 位不符合的 $r$ 的长为 $k$ 的子串去掉（举个例子，前三位填了 $001$ ，如果 $k=4$ 就得把串 $0001$ 去掉）。

这个复杂度是 $O(n^2)$ 的，可以用后缀数组优化。建出 SA 后按照后缀排名从小到大遍历每一个本质不同的长为 $k$ 的串并把它们扔到一个数组里，这样的话字典序自然保证了递增；维护一个左指针和右指针表示当前需要考虑的串的范围，每次填数用二分找出第 $i$ 位为 $0$ 的串的数量就可以 check 合法性了，然后你会发现用后缀数组的好处就是每次更新需要考虑的串的范围的具体操作就是去掉一个前缀或后缀，所以用之前二分得到的信息更新左右指针就很 trivial。几乎没有细节，时间复杂度 $O(n\log n)$ 。

有一个坑点是多组询问的情况下**要对 rk （后缀排名）数组的两倍进行清空**，否则 WA on test 86。

提交记录：[link](https://codeforces.com/contest/1469/submission/165796570)

---

