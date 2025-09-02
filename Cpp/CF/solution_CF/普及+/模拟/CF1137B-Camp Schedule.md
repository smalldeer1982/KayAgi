# Camp Schedule

## 题目描述

The new camp by widely-known over the country Spring Programming Camp is going to start soon. Hence, all the team of friendly curators and teachers started composing the camp's schedule. After some continuous discussion, they came up with a schedule $ s $ , which can be represented as a binary string, in which the $ i $ -th symbol is '1' if students will write the contest in the $ i $ -th day and '0' if they will have a day off.

At the last moment Gleb said that the camp will be the most productive if it runs with the schedule $ t $ (which can be described in the same format as schedule $ s $ ). Since the number of days in the current may be different from number of days in schedule $ t $ , Gleb required that the camp's schedule must be altered so that the number of occurrences of $ t $ in it as a substring is maximum possible. At the same time, the number of contest days and days off shouldn't change, only their order may change.

Could you rearrange the schedule in the best possible way?

## 说明/提示

In the first example there are two occurrences, one starting from first position and one starting from fourth position.

In the second example there is only one occurrence, which starts from third position. Note, that the answer is not unique. For example, if we move the first day (which is a day off) to the last position, the number of occurrences of $ t $ wouldn't change.

In the third example it's impossible to make even a single occurrence.

## 样例 #1

### 输入

```
101101
110
```

### 输出

```
110110```

## 样例 #2

### 输入

```
10010110
100011
```

### 输出

```
01100011
```

## 样例 #3

### 输入

```
10
11100
```

### 输出

```
01```

# 题解

## 作者：Hughpig (赞：12)

很显然的想法是不断地拿 $t$ 拼凑起来，直到拼凑不了了再把剩下的字符也输出去。

但是这并不对。原因是 $t$ 的后缀可以被重复利用，可以包含更多的字串 $t$。

所以我们要找到 $t$ 最长的公共前后缀并重复利用，最大化可以包含的 $t$ 的个数。

哎？这不是我们的 border 吗？

用 KMP 的方法预处理出 $t$ 的最长 border，然后每次输出完下次就不用输出前 $next_m$ 个字符了。最后输出剩余字符即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

string s,t;
int n,m,cnt0,cnt1,cnt,nxt[500007];

int main()
{
	cin>>s>>t;
	n=s.size(),m=t.size();
	for(auto c:s){
		if(c=='0')++cnt0;
		else ++cnt1;
	}
	s=" "+s,t=" "+t;
	for(int i=2,j=0;i<=m;++i){
		while(j&&t[i]!=t[j+1])j=nxt[j];
		if(t[i]==t[j+1])++j;
		nxt[i]=j;
	}
	while(1){
		int precnt0=cnt0,precnt1=cnt1;
		if(cnt){
			for(int i=1+nxt[m];i<=m;++i){
				if(t[i]=='0')--cnt0;
				else --cnt1;
			}
		}
		else{
			for(int i=1;i<=m;++i){
				if(t[i]=='0')--cnt0;
				else --cnt1;
			}
		}
		if(cnt0<0||cnt1<0){
			cnt0=precnt0,cnt1=precnt1;
			break;
		}
		if(cnt)cout<<t.substr(nxt[m]+1);
		else cout<<t.substr(1);
		++cnt;
	}
	while(cnt0>0)cout<<0,--cnt0;
	while(cnt1>0)cout<<1,--cnt1;
	return 0;
}
```

---

## 作者：StudyingFather (赞：5)

欢迎各位dalao来踩我的博客QAQ：[Studying Father's Blog](studyingfather.com)

------------

### 前置知识：KMP

不会KMP算法的请先右转[这道模板题](https://www.luogu.org/problemnew/show/P3375)。

------------

接下来进入正题。

本题的任务是让我们重排文本串 $ s $ ，使得模式串 $ t $ 在 $ s $ 中出现的次数尽可能多。

我们自然而然想到了用KMP算法的思想来解决这道题目。

首先，对模式串 $ t $ 计算 $ next $ 数组的值，然后贪心填充文本串 $ s $ （即在0和1的个数充足的情况下，尽可能多的匹配 $ t $ 串）。

每完成一次匹配时，我们不能简单地将模式串的指针重新指向字符串开头，因为字符串的前缀和后缀可能重叠，这样就可能丢失最优解。因此，我们应该利用前缀和后缀的公共部分。

那么完成一次匹配后，模式串的指针应该移到哪个位置开始匹配呢？根据KMP的思想，应该移到到字符串 $ t $ 最后一位对应的 $ next $ 值的后一位进行匹配。（别忘了 $ next $ 数组的意义：字符串前 $ i $ 位的最长公共前后缀长度）

这样，我们就可以在线性时间复杂度内解决本题了。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[500005],t[500005],res[500005];
int nxt[500005];
void getnext()
{
 nxt[1]=0;
 int len=strlen(t+1);
 for(int i=2,j=0;i<=len;i++)
 {
  while(j&&t[i]!=t[j+1])
   j=nxt[j];
  if(t[i]==t[j+1])j++;
  nxt[i]=j;
 }
}
int main()
{
 scanf("%s",s+1);
 scanf("%s",t+1);
 getnext();//先计算next数组
 int cnt1=0,cnt0=0,lens=strlen(s+1),lent=strlen(t+1);
 for(int i=1;i<=lens;i++)
  if(s[i]=='0')cnt0++;
  else cnt1++;
 for(int i=1,j=1;i<=lens;i++,j++)
 {
  if(t[j]=='0'&&(!cnt0))res[i]='1',cnt1--;
  else if(t[j]=='1'&&(!cnt1))res[i]='0',cnt0--;
  else//假如0或1的数量充足，就直接填充
  {
   res[i]=t[j];
   if(t[j]=='0')cnt0--;
   else cnt1--;
  }
  if(j==lent)j=nxt[j];//将模式串的指针移到到最优位置，减少重复匹配
 }
 printf("%s\n",res+1);
 return 0;
}
```


---

## 作者：zac2010 (赞：4)

考虑利用 $\text{KMP}$ 辅助进行贪心。

先预处理出 $t$ 所有前缀的 $\text{border}$，也就是熟知的 $next$ 数组。然后在 $s$ 上做一个贪心的匹配——假若 $s$ 剩余的字符中还存在能和 $t$ 中匹配的字符，那必定优先选它；否则之后只有一种可能，就是一直取同样的一个字符。

至于贪心的正确性，可以凭借直觉/归纳反证。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 5e5 + 10;
int n, m, j = 1, nxt[N], cnt[N];
char a[N], b[N], ans[N];
void get_nxt(){
    int j = 0;
    FL(i, 2, m){
        while(j && b[j + 1] != b[i]) j = nxt[j];
        if(b[j + 1] == b[i]) j++; nxt[i] = j;
    }
}
int main(){
    scanf("%s%s", a + 1, b + 1);
    n = strlen(a + 1), m = strlen(b + 1);
    FL(i, 1, n) cnt[a[i]]++; get_nxt();
	FL(i, 1, n){
		if(cnt[b[j]]) cnt[ans[i] = b[j]]--;
		else cnt[ans[i] = (b[j] ^ 1)]--;
		if(j == m) j = nxt[j]; j++;
	}
	printf("%s", ans + 1);
	return 0;
}
```


---

## 作者：qwqszxc45rtnhy678ikj (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1137B)

读完题面后，我们可以发现，$s$ 串中怎么排列根本就不重要，重要的是 $s$ 中有多少个 $0$ 和 $1$，用来我们构造新的串，所以我们要先统计出来 $s$ 中 $0$ 和 $1$ 的个数。

在仔细思考过后，能够发现，我们要构造的新串有个明显的性质：我们让所有的 $t$ 重复得越多，就可以节省越多的 $0$ 和 $1$ 用来构造更多的 $t$。那么这道题就是很明显的有贪心性质了。

但是我们怎样在能够保证效率的同时保证重复得最多呢？所以接下来我们就要用到 KMP 了。我们求出 $t$ 的 $nxt$ 数组，取 $t$ 的最后一位就可以求出重复的长度了。

由于我们要构造新串，所以要看 $t$ 所占的 $0$ 和 $1$ 的个数（第一个 $t$），和除重复部分以外的剩余部分所占的 $0$ 和 $1$ 的个数（后面的 $t$），才可以保证构造新串用的 $0$、$1$ 的个数不多于原串的个数。

当然肯定会剩余几个 $0$ 和 $1$ 不能构造 $t$ 了，这个时候我们直接把这些“废品”扔串后面即可。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
char s[1000010],t[1000010];
int n,m,i=0,j=-1,p,k0,k1,h0,h1,u0,u1,len,nxt[1000010]={-1};
int main(){
	cin>>s>>t;
	n=strlen(s),m=strlen(t); //n代表原串长度，m代表t的长度
	for(int i=0;i<n;i++){ //原串0和1的个数
		if(s[i]=='0')h0++;
		else h1++;
	}
	for(int i=0;i<m;i++){ //t中0和1的个数
		if(t[i]=='0')k0++;
		else k1++;
	}
	while(i<m){ 
		if(j==-1||t[i]==t[j]){
			i++,j++;
			nxt[i]=j;
		}else j=nxt[j];
	} //求kmp（因为我习惯的写法中，kmp数组是直接顺位向后移了一位的，所以后面原本最后一位是m-1，需要写成m。
	for(int i=nxt[m];i<m;i++){ //除重复部分以外0和1的个数
		if(t[i]=='0')u0++;
		else u1++;
	}
	if(h0>=k0&&h1>=k1){ //判断第一个能不能构造
		h0-=k0,h1-=k1;
		for(int i=0;i<m;i++)s[++len]=t[i];
		while(h0>=u0&&h1>=u1){ //贪心构造后面的
			h0-=u0,h1-=u1;
			for(int i=nxt[m];i<m;i++)s[++len]=t[i];
		}
	}
	for(int i=1;i<=len;i++)cout<<s[i];
	while(h0--)cout<<0; //剩余的废品输出
	while(h1--)cout<<1; //同上
	return 0;
}
```


---

## 作者：Zechariah (赞：1)

考虑贪心  
我们肯定是要按照$t$串来构造的，关键是$t$串的某个后缀可能会与前缀相同，那么如果我们利用这个相同部分肯定是最优的  
于是直接按$kmp$求出$next$数组，记录下串中$0$和$1$的个数，直接顺着摆就行了，每次摆完一个串就跳$next$，最后剩余的随便摆，这个策略绝对是最优的
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x&-x)
#define jh(x, y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 5e5 + 5, mod = 998244353, INF = 0x3f3f3f3f;
using namespace std;
namespace fast_IO {
    inl ll read() {
        rg char c;
        rg ll x = 0;
        rg bool flag = false;
        while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
        if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
        while ((c = getchar()) != ' ' && c != '\n' && c != '\r'&&~c)
            x = (x << 1) + (x << 3) + (c ^ 48);
        if (flag)return -x; return x;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
char s[N], t[N];
int nt[N];
int cnt[2];

int main(void)
{
    scanf("%s%s", s, t);
    rg int lens = strlen(s), lent = strlen(t), i = 0, j = -1; *nt = -1;
    while (i != lent)
        if (j == -1 || t[i] == t[j])nt[++i] = ++j;
        else j = nt[j];
    for (rg int i = 0; i != lens; ++i)++cnt[s[i] ^ 48];
    for (rg int i = 0, now = 0; i != lens; ++i)
    {
        if (cnt[t[now] ^ 48])--cnt[t[now] ^ 48], putchar(t[now]);
        else if (cnt[0])putchar('0');
        else putchar('1');
        if (++now == lent)now = nt[now];
    }
    return 0;
}

```


---

## 作者：Priestess_SLG (赞：0)

笑点解析：不会 KMP

考虑一个简单的贪心：新建的串中能多放一个串 $t$ 就是一个串 $t$。于是可以得到 $O(n)$ 的解法，然后很高兴的获得 wa。

考虑做法为什么错了。发现每一次往新建串中放 $t$ 时，都可以去利用前面放过的 $t$。发现可以利用的长度就是 $t$ 中最大的 $l$ 满足 $l<|t|$ 且 $t_{[1:l]}=t_{[|t|-l+1:|t|]}$。发现这就是 kmp 算法中 border 的定义，直接跑 kmp 或者用哈希二分均可。这里采用了 kmp 的做法（更好写）。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 500010;
char s[N], t[N];
int border[N];
signed main() {
    cout << fixed << setprecision(15);
    // cin.tie(0)->sync_with_stdio(false);
    scanf("%s%s", s + 1, t + 1);
    int n = strlen(s + 1), m = strlen(t + 1);
    for (int i = 2, j = 0; i <= m; ++i) {
        while (j && t[i] != t[j + 1]) j = border[j];
        if (t[i] == t[j + 1]) ++j;
        border[i] = j;
    }
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
    for (int i = 1; i <= n; ++i)
        if (s[i] == '1') ++c1;
        else ++c2;
    for (int i = 1; i <= m; ++i)
        if (t[i] == '1') ++c3;
        else ++c4;
    if (c1 < c3 || c2 < c4) {
        puts(s + 1);
    } else {
        int c5 = 0, c6 = 0;
        int len = border[m];
        for (int i = len + 1; i <= m; ++i)
            if (t[i] == '1') ++c5;
            else ++c6;
        c1 -= c3, c2 -= c4;
        int cnt = 0;
        while (c1 >= c5 && c2 >= c6) {
            c1 -= c5, c2 -= c6;
            ++cnt;
        }
        for (int i = 1; i <= m; ++i) cout << t[i];
        for (int j = 1; j <= cnt; ++j)
            for (int i = len + 1; i <= m; ++i)
                cout << t[i];
        for (int i = 0; i < c1; ++i) cout << 1;
        for (int i = 0; i < c2; ++i) cout << 0;
        cout << '\n';
    }
    return 0;
}
```

---

## 作者：GeXiaoWei (赞：0)

# CF1137B Camp Schedule
## 前置知识
KMP 算法求字符串的 $\text{border}$，学会再看。
## 解析
首先，用 KMP 算法求出题目中字符串 $t$ 的 $\text{border}$ 并求出字符串 $s$ 和 $t$ 的 $01$ 字符个数，然后用字符串 $s$ 的 $01$ 去拼多个字符串 $t$ 凑最优解，剩下的单独输出。你就会发现不对。

为什么呢？设除去字符串 $t$ 的后面一段 $\text{border}$ 的结尾部分后的字符串为 $k$，则多个 $k$ 与字符串 $t$ 的 $\text{border}$ 拼再一起再拼上剩下的 $01$ 就会更优，这就是这题的正确解法。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m,s0,s1,t0,t1,a,b,Next[N];
char s[N],t[N];
string qi="",ho="";
void getNext(char p[]){
	int i,j;
	for(Next[1]=j=0,i=2;p[i];i++){
		while(j&&p[i]!=p[j+1]) j=Next[j];
		if(p[i]==p[j+1]) j++;
		Next[i]=j;
	}
}
int main(){
    scanf("%s%s",s+1,t+1);
    n=strlen(s+1),m=strlen(t+1);
    for(int i=1;i<=n;i++){
        if(s[i]=='0') s0++;
        else s1++;
    }getNext(t);
    for(int i=1;i<=Next[m];i++){
        qi+=t[i];
        if(t[i]=='0') t0++;
        else t1++;
    }for(int i=Next[m]+1;i<=m;i++){
        ho+=t[i];
        if(t[i]=='0') a++;
        else b++;
    }if(t0<=s0&&t1<=s1){
        s0-=t0,s1-=t1,cout<<qi;
        while(s0>=a&&s1>=b){
            cout<<ho;
            s0-=a,s1-=b;
        }
    }while(s0--) printf("0");
    while(s1--) printf("1");
    return 0;
}
```

---

## 作者：zym20249_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1137B)

## 题意
给定两个字符串 $s$ 和 $t$，要求由 $0$ 和 $1$ 构成。要求重新构造 $s$，且重构后的 $0$ 和 $1$ 的个数不能改变。你希望尽可能让重构的 $s$ 里面出现多次 $t$，输出重构后的 $s$。

## 思路
这道题需要用到 KMP，需要用到 $nxt$ 数组，这个数组是当前字符的前缀和后缀相同且最大的长度。使用 KMP 算法才不会超市，时间复杂度为 $\Theta(n+m)$，暴力枚举时间复杂度为 $\Theta(n·m)$。

---

## 作者：Aurora_Borealis_ (赞：0)

我们可以用贪心解决这个问题。

首先，先放置一个 $t$ 串。

然后我们需要考虑怎么能把这第一个串最大利用，也就是让第二个 $t$ 串的前缀尽可能地与第一个的后缀重合，达到节约字符的效果（显然剩下的字符越多，答案就可能越大，但绝对不会变小），我们需要知道这个后缀（或者说前缀也行）的长度。

此时我们可以发现，这个长度的定义与 KMP 算法中的 nxt 数组的定义相吻合，所以可以利用 nxt 数组求解。

所以整体思路如下：

1. 先放置一个 $t$ 串。

1. 在字符数量够用的情况下，前一个串的基础上接上模式串的 $[nxt_m+1,m]$ 部分

1. 输出剩余的边角料。

code:

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define vi vector<int>
#define imp map<int,int>
using namespace std;
const int N=500005;
char a[N],b[N];
int n,m,nxt[N],s1=0,s2=0,z1=0,z2=0;
int q1=0,q2=0;

int main(){
	cin>>a+1>>b+1;
	n=strlen(a+1);
	m=strlen(b+1);
	nxt[1]=0;
	int j=0;
	for(int i=1;i<=n;i++){
		if(a[i]=='0'){
			s1++;
		}else{
			s2++;
		}
	}
	for(int i=1;i<=m;i++){
		if(b[i]=='0'){
			z1++;
		}else{
			z2++;
		}
	}
	for(int i=2;i<=m;i++){
		while(j>0&&b[i]!=b[j+1]) j=nxt[j];
		if(b[i]==b[j+1]) j++;
		nxt[i]=j;
	}
	for(int i=nxt[m]+1;i<=m;i++){
		if(b[i]=='0'){
			q1++;
		}else{
			q2++;
		}
	}
	if(s1>=z1&&s2>=z2){
		s1-=z1,s2-=z2;
		for(int i=1;i<=m;i++){
			cout<<b[i];
		}
		while(s1>=q1&&s2>=q2){
			s1-=q1;
			s2-=q2;
			for(int i=nxt[m]+1;i<=m;i++){
				cout<<b[i];
			}
		}
	}
	while(s1>0){
		s1--;
		cout<<0;
	}
	while(s2>0){
		s2--;
		cout<<1;
	}
	return 0;
}

```


---

## 作者：star_magic_young (赞：0)

$\color{red}FST$
选手来水一发题解

首先可以先不管三七二十一放下一个$t$串,然后我们发现,如果$t$串的长度为$i$的前缀等于长度为$i$的后缀,那么直接在后面加上$t$的长度为$|t|-i$的后缀即可构造出另一个$t$,贪心的想,这个$i$越长越好,只要找出最大的$i$,然后贪心能放就放

这个可以$kmp$实现,当然也可以哈希,直接$O(1)$比较长度为$i$的前缀和后缀.不过这题是卡了$\mathrm{unsigned\ long\ long}$自然溢出的~~别问我为什么~~,所以建议用两个不同的模数进行双哈希,细节详见代码


```cpp
#include<bits/stdc++.h>
#define LL long long
#define uLL unsigned long long
#define il inline
#define re register

using namespace std;
const int N=5e5+10;
il int rd()
{
    int x=0,w=1;char ch=0;
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*w;
}
char cc[N],ss[N];
int n,m,cn[2],cs[2],cx[2],ma;
LL ha[N],hb[N],b1[N],b2[N],s1=233,s2=677,m1=19491001,m2=993244853;
uLL gha(int l,int r)
{
    return (ha[r]-ha[l-1]*b1[r-l+1]%m1+m1)%m1;
}
uLL ghb(int l,int r)
{
    return (hb[r]-hb[l-1]*b2[r-l+1]%m2+m2)%m2;
}

int main()
{
    scanf("%s%s",cc+1,ss+1);
    n=strlen(cc+1),m=strlen(ss+1);
    for(int i=1;i<=n;++i) ++cn[cc[i]-'0'];
    for(int i=1;i<=m;++i) ++cs[ss[i]-'0'];
    b1[0]=b2[0]=1;
    for(int i=1;i<=m;++i)
    {
        b1[i]=b1[i-1]*s1%m1;
        b2[i]=b2[i-1]*s2%m2;
        ha[i]=(ha[i-1]*s1%m1+ss[i])%m1;
        hb[i]=(hb[i-1]*s2%m2+ss[i])%m2;
    }
    for(int i=m-1;i;--i)
        if(gha(1,i)==gha(m-i+1,m)&&ghb(1,i)==ghb(m-i+1,m)) {ma=i;break;}
    for(int i=ma+1;i<=m;++i) ++cx[ss[i]-'0'];
    if(cn[0]>=cs[0]&&cn[1]>=cs[1])
    {
        for(int i=1;i<=m;++i) printf("%c",ss[i]);
        cn[0]-=cs[0],cn[1]-=cs[1];
        while(cn[0]>=cx[0]&&cn[1]>=cx[1])
        {
            for(int i=ma+1;i<=m;++i) printf("%c",ss[i]);
            cn[0]-=cx[0],cn[1]-=cx[1];
        }
        while(cn[0]>0) putchar('0'),--cn[0];
        while(cn[1]>0) putchar('1'),--cn[1];
    }
    else for(int i=1;i<=n;++i) printf("%c",cc[i]);
    return 0;
}
```

---

## 作者：mountain_k (赞：0)

[我的博客](https://www.cnblogs.com/mountaink/p/10507584.html)

题意：给出$s$和$t$两个串，让你构造出一个答案串，使得答案串中的01数量和$s$一样，并且使$t$在答案串中作为子串出现次数最多。

思路：
要想出现的次数尽可能多，那么就要重复的利用，哪一部分是可以重复利用的呢？就是前缀和后缀相同的部分，然后我们就想到了kmp算法中$fail$函数就是求这个东西的，那么我们先对t串$fail$一遍得到next数组，然后先使前缀出现一次，然后就使除了前缀以外的后缀按顺序出现，并且尽可能出现的多，这样得到的答案串必定是最多的，最后把剩余的01输出就可以了。

　　记住扫描字符串的for循环千万不要用(i<strlen(s))当条件，否则就是个$n2$的算法了（你会tle15）。
  ```cpp
#include<bits/stdc++.h>
#define clr(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn=500010;
int n,f[maxn],a,b;
char s[maxn],p[maxn];
void fail(){
	f[0]=-1;
	for(int j=1;j<n;j++)
	{
		for(int i=f[j-1];;i=f[i])
		{
			if(p[j]==p[i+1]){
				f[j]=i+1;
				break;
			}else if(i==-1)
			{
				f[j]=-1;
				break;
			}
		}
	}
	for(int i=0;i<n;i++)f[i]++;
}
int main(){
	while(scanf("%s",s)!=EOF)
	{
		scanf("%s",p);
		n=strlen(p);
		fail();
		a=b=0;
		int si=strlen(s);
		for(int i=0;i<si;i++)
		{
			if(s[i]=='0')a++;
			else b++;
		}
		int xx=0,yy=0;
		for(int i=0;i<f[n-1];i++)
		{
			if(p[i]=='0')xx++;
			else yy++;
		
		}
		if(a>=xx&&b>=yy)
		{
			for(int i=0;i<f[n-1];i++)printf("%c",p[i]);
			a-=xx,b-=yy;
			int xxx=0,yyy=0;
			for(int i=f[n-1];i<n;i++)
			{
				if(p[i]=='0')xxx++;
				else yyy++;
			}
			int flag=0;
			while(a>0&&b>0)
			{
				if(a<xxx||b<yyy)break;
				for(int i=f[n-1];i<n;i++)
				{
					printf("%c",p[i]);
				}
				a-=xxx,b-=yyy;
			}
			while(a>0){
				printf("0");
				a--;
			}
			while(b>0){
				printf("1");
				b--;
			}
			puts("");
		}else{
			printf("%s\n",s);
		}
	}
}
```


---

