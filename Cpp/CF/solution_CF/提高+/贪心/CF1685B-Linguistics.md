# Linguistics

## 题目描述

Alina 发现了一种只由 $\text{A, B, AB, BA}$ 四种单词组成的语言，这种语言不含有空格，书写句子时只需要将单词直接连接起来即可。

她很好奇是否可以用 $a$ 个 $\text{A}$，$b$ 个 $\text{B}$，$c$ 个 $\text{AB}$，$d$ 个 $\text{BA}$ 拼接形成句子 $s$。

换句话说，是否可以用 $a+b+c+d$ 个单词以某种顺序拼接出句子 $s$，这 $a+b+c+d$ 个单词都得被用到，他们的顺序可以由你决定。

## 样例 #1

### 输入

```
8
1 0 0 0
B
0 0 1 0
AB
1 1 0 1
ABAB
1 0 1 1
ABAAB
1 1 2 2
BAABBABBAA
1 1 2 3
ABABABBAABAB
2 3 5 4
AABAABBABAAABABBABBBABB
1 3 3 10
BBABABABABBBABABABABABABAABABA```

### 输出

```
NO
YES
YES
YES
YES
YES
NO
YES```

# 题解

## 作者：Endt (赞：9)

# Linguistics-题解

### 题意

现有 $4$ 种碎片 `A`、`B`、`AB`、`BA`，数量分别为 $a$、$b$、$c$、$d$。你可以以任意顺序拼接这些碎片，问能否拼成字符串 $s$。

### 解法

首先判无解，非常简单，看 `A` 与 `B` 各自的个数是否匹配。

`A` 和 `B` 补位就可以，我们主要找 `AB` 和 `BA`。那么问题就变成了从 $s$ 中找  $c$ 个`AB` 和 $d$ 个 `BA`，不能有重合部分。

显然，我们通过拆分 `ABAB...` 或 `BABA...` 构造，考虑分类：

1. 首尾相同，那么这个串用 `AB` 填或 `BA` 填都最多填 $\frac{length-1}{2}$ 个。

2. 首尾不同，不妨设以 `A` 开头，那么用 `AB` 填最多填 $\frac{length}{2}$ 个，而 `BA` 只能填 $\frac{length-2}{2}$ 个。以 `B` 开头同理。

贪心地，先将第二种串解决，以 `A` 开头的填 `AB`，以 `B` 开头的填 `BA`。剩下第一种情况的串、全 `A` 串、全 `B` 串能填什么就填什么。

### 代码

```cpp
#include<bits/stdc++.h>

#define  Int  long long int
#define  Pub  public

using std::min;using std::max;

int a,b,c,d,n;
char s[200005];
bool check(){
    int numa=0,numb=0;
    for(int i=0;i<n;++i)
        if(s[i]=='A')++numa;
        else ++numb;
    return numa==a+c+d&&numb==b+c+d;
}

void solve(int &A,int x,int &B){
    if(A>=x){
        A-=x;
    }else{
        x-=A+1; 
        A=0;
        B-=min(B,x);
    }
}
int main(){
    int T;
    scanf("%d",&T);
    while(~--T){
        scanf("%d%d%d%d",&a,&b,&c,&d);
        scanf("%s",s);
        n=strlen(s);
        if(!check()){
            printf("No\n");
            continue;
        }
        int cd=0;
        std::vector<int> C,D;
        for(int i=0;i<n;){
            int j=i+1;
            while(j<n&&s[j]!=s[j-1])++j;
            int len=j-i;
            if(len==1){
                i=j;
                continue;
            }
            if(len&1)
                cd+=len/2;
            else{
                len/=2;
                if(s[i]=='A')
                    C.push_back(len);
                else
                    D.push_back(len);
            }
            i=j;
        }
        sort(C.begin(),C.end());
        sort(D.begin(),D.end());
        for(int i:C)
            solve(c,i,d);
        for(int i:D)
            solve(d,i,c);
        printf(cd>=c+d?"Yes\n":"No\n");
    }
}
```


---

## 作者：Hovery (赞：3)

## Problem

[CF1685B](https://www.luogu.com.cn/problem/CF1685B)

## Sol

首先对于一个字符串，我们设它里面A的数量为 $num_a$，B的数量为 $num_b$，若一个字符串要满足答案，必定会有 $a+c+d=num_a$ 和 $b+c+d=num_b$。

然后考虑若答案成立，必定会有AB和BA都填完，由于上面满足了 $a+c+d=num_a$ 和 $b+c+d=num_b$，所以说将AB和BA填完剩下的字符必定能够满足答案。

那么问题就变成了从 $s$ 中找不相交的AB和BA，使得其满足AB的个数为 $c$，BC的个数为 $d$。

首先，对于AA，BB这种串是对答案没有贡献的。

换句话说，只有ABAB...和BABA...这种AB交替的串对答案会产生贡献。

考虑分类。

$1.$ 首尾相同，也就是ABABA，BABAB这种，那么它们对AB和BA的贡献是一样的，都是 $\dfrac{len - 1}{2}$。

$2.$ 首尾不同，形如ABAB，BABA。对于A开头，它对AB的贡献为 $\dfrac{len}{2}$，对BA的贡献为 $\dfrac{len}{2} - 1$。B开头同理。

那从贪心的角度，最好是将ABAB，拿去给AB，BABA拿去给BA，最后ABABA，BABAB这种去补。

假如AB已经找完了，BA还有很多，ABAB这种串也还有很多，那么就将剩下的ABAB都给BA做贡献。

但还有一点，AB和BA可以共用一个串。

这是什么意思呢？

对于ABABABAB...（首尾相同不同都可）

我们可以让它对AB的贡献为前 $4$ 个，将后 $4$ 个给BA做贡献。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;

const int N = 2e5;

int _1, _2, _3, _4, n, l, cnt, a[N], b[N], c[N], _a, _b, _c;

string s;

void solve()
{
	_a = _b = _c = 0;
	cin >> _1 >> _2 >> _3 >> _4;
	cin >> s;
	n = s.length();
	s = " " + s;
	int sum = 0;
	for (int i = 1;i <= n;i++)
	if (s[i] == 'A')
	{
		sum ++;
	}
	if (_1 + _3 + _4 != sum || _2 + _3 + _4 != n - sum)
	{
		cout << "NO\n";
		return;
	}
	cnt = 0;
	l = 1;
	for (int i = 2;i <= n;i++)
	if (s[i] == s[i - 1])
	{
		if (l != i - 1)
		{
			if (s[l] == s[i - 1])
			{
				a[++_a] = i - l >> 1;
			}
			else {
				int k = i - l >> 1;
				if (s[l] == 'A')
				b[++_b] = k;
				else c[++_c] = k;
			}
		}
		l = i;
	}
	if (l != n)
	{
		if (s[l] == s[n])
		{
			a[++_a] = n - l + 1 >> 1;
		}
		else {
			int k = n - l + 1 >> 1;
			if (s[l] == 'A')
			b[++_b] = k;
			else c[++_c] = k;
		}
	}
	sort(a + 1, a + _a + 1);//首尾相同
	sort(b + 1, b + _b + 1);//首尾不同，第一位为A
	sort(c + 1, c + _c + 1);//首尾不同，第一位为B
	for (int i = 1;i <= _b;i++){
		if (_3 < b[i])
		{
			b[i] -= _3;
			_3 = 0;
			for (int j = i;j <= _b;j++)
			_4 -= (b[j] - 1);
			break;
		}//若AB没了，剩下都给BA
		_3 -= b[i];
	}
	if (_4 < 0)
	{
		cout << "YES\n";
		return;
	}
	for (int i = 1;i <= _c;i++)
	{
		if (_4 < c[i])
		{
			c[i] -= _4;
			_4 = 0;
			for (int j = i;j <= _c;j++)
			_3 -= (c[j] - 1);
			break;
		}//若BA没了，剩下都给AB
		_4 -= c[i];
	}
	if (_3 <= 0 && _4 <= 0)
	{
		cout << "YES\n";
		return;
	}
	sum = 0;
	for (int i = 1;i <= _a;i++)
	sum += a[i];
	if (max(_3, 0ll) + max(_4, 0ll) > sum)
	{
		cout << "NO\n";
		return;
	}//最后拿首尾相同的去补
	else cout << "YES\n";
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
}
```

---

## 作者：WaterSun (赞：2)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18559018)

@hzjoiineg 为什么是神？

# 思路

首先将 $S$ 中 `A` 的数量不等于 $a + c + d$ 的情况判掉。

然后将 $S$ 划分为 `ABAB...` 和 `BABA...` 的若干段，对于长度为奇数的段构造方案只能是如下构成：`A` 开头为例）：`AB` 和 `BA` 共 $\lfloor \frac{len}{2} \rfloor$ 个，再加一个 `A`。将 $a$ 减一，并用记录每一个长度为奇数的段的 $\lfloor \frac{len}{2} \rfloor$ 之和记为 $cnt$，最后判断剩下的 `A,B,AB,BA` 能否凑出 $cnt$ 个 `AB` 或 `BA` 即可。

其次对于长度为偶数的构造，要么用 $\frac{len}{2}$ 个 `AB`；要么用 `AB` 和 `BA` 共 $\frac{len}{2} - 1$ 个，同时使用一个 `A` 和一个 `B`。贪心地，我们显然希望在此情况下尽可能地使用 `AB`，不够的再用 `BA` 补，再不够的用 `A,B` 补。因为使用 `A,B` 的限制明显弱于使用 `AB,BA` 的限制。

需要注意的是对于偶数的构造需要先处理 $len$ 较小的，因为如果先处理了一个 $len$ 较大的将 `AB` 消耗完了，但是对于小的段，每一段都需要一个 `A` 和一个 `B`，但是可能消耗不了 `BA`，因此不优。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define fst first
#define snd second

using namespace std;

typedef pair<int,int> pii;
const int N = 2e5 + 10;
int a,b,c,d,n;
char s[N];
bool vis[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void solve(){
    a = read(),b = read(),c = read(),d = read();
    scanf("%s",s + 1); n = strlen(s + 1);
    int numa = 0;
    for (re int i = 1;i <= n;i++) numa += (s[i] == 'A');
    if (numa != a + c + d) return puts("NO"),void();
    int lst = 0; vector<pii> v;
    for (re int i = 1;i <= n;i++){
        if (i == n) v.push_back({lst + 1,n});
        else{
            if (s[i] == s[i + 1]){
                v.push_back({lst + 1,i}); lst = i;
            }
        }
    }
    int cnt = 0;
    vector<int> va,vb;
    for (pii p:v){
        int len = p.snd - p.fst + 1;
        if (len & 1){
            if (s[p.fst] == 'A'){
                if (a) a--;
                else return puts("NO"),void();
            }
            else{
                if (b) b--;
                else return puts("NO"),void();
            }
            cnt += (len / 2);
        }
        else{
            if (s[p.fst] == 'A') va.push_back(len);
            else vb.push_back(len);
        }
    }
    sort(va.begin(),va.end());
    sort(vb.begin(),vb.end());
    for (int p:va){
        int nd = p / 2;
        if (c >= nd) c -= nd;
        else{
            nd -= c; c = 0;
            if (a && b){
                a--; b--; nd--;
                if (d >= nd) d -= nd;
                else{
                    nd -= d; d = 0;
                    if (a >= nd && b >= nd) a -= nd,b -= nd;
                    else return puts("NO"),void();
                }
            }
            else return puts("NO"),void();
        }
    }
    for (int p:vb){
        int nd = p / 2;
        if (d >= nd) d -= nd;
        else{
            nd -= d; d = 0;
            if (a && b){
                a--; b--; nd--;
                if (c >= nd) c -= nd;
                else{
                    nd -= c; c = 0;
                    if (a >= nd && b >= nd) a -= nd,b -= nd;
                    else return puts("NO"),void();
                }
            }
            else return puts("NO"),void();
        }
    }
    if (a < 0 || b < 0) puts("NO");
    else if (min(a,b) + c + d < cnt) puts("NO");
    else puts("YES");
}

int main(){
    int T; T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：zcxxnqwq (赞：2)

## 分析：
转化题意：给定字符串 $s$，问它能否由 $a$ 个 `A`、$b$ 个 `B`、$c$ 个 `AB`、$d$ 个 `BA` 拼成，那么首先想到统计 $s$ 中的 `A` 和 `B` 的个数与要填的 `A` 和 `B` 个数是否相等，若不等直接判否。

然后发现，`A` 和 `B` 一定可以全部被填入 $s$ 中，那么就只需判断当前字符串能否填入 $c$ 个 `AB` 和 $d$ 个 `BA` 即可。

字符串中能放 `AB` 或 `BA`，当且仅当处在连续的 `A` 和连续的 `B` 交界处，形如：`AB`，`ABA`，`BAB`，`ABAB` 等。考虑他们对答案的贡献，这些能放 `AB` 或 `BA` 的字符串又可以分为两种：长度为奇数与长度为偶数。

长为奇数：对 `AB` 和 `BA` 的贡献相同，均为 $\left\lfloor\dfrac{len}{2}\right\rfloor$；

长为偶数：以 `A` 开头的对 `AB` 的贡献为 $\left\lfloor\dfrac{len}{2}\right\rfloor$，对 `BA` 的贡献为$\left\lfloor\dfrac{len}{2}\right\rfloor-1$，以 `B` 开头同理。

填入 `AB` 和 `BA` 的过程中，要贪心地使能填入的 `AB` 和 `BA` 最多，那么一定优先选没有损耗的，即 `AB` 优先填入以 `A` 开头长为偶数的字符串，而 `BA` 优先填入以 `B` 开头长为偶数的字符串，若填完后 $c$ 和 $d$ 仍大于 $0$，再去考虑填入其它。

考虑这样一种情况：$c$ 很小，填完后形如 `ABAB` 的字符串仍有剩余，而 $d$ 很大，需要去填入长度为奇数的字符串，而填完 $d$ 仍大于 $0$，此时 `BA` 便需要填到形如 `ABAB` 的字符串里，此时怎么最大程度的减少损耗呢？由于每一段填入 `BA` 的 `ABAB` 都只损耗 $1$，故当填入 `BA` 的 `ABAB` 串最少的时候 $1$ 损耗最小。于是将形如 `ABAB` 的字符串长度从小到大排序，使 `AB` 优先填入长度小的字符串，这样就能保证后面填的 `BA` 最多。

代码实现就，不手残万岁啦。
```cpp
#include<bits/stdc++.h>
#define ff(i,s,e) for(int i(s);i<=(e);++i)
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=2e5+5;
int T,a,b,c,d,n;
char s[N];
int aa[N],bb[N],cnt1,cnt2; 
inline void solve(){
	a=read(),b=read(),c=read(),d=read();
	scanf("%s",s+1);
	n=strlen(s+1);
	int sum=0;
	int cnta=0,cntb=0; 
	ff(i,1,n){
		if(s[i]=='A') cnta++;
		else cntb++;
	}
	if(cntb-cnta!=b-a) return printf("NO\n"),void();
	cnt1=cnt2=0;
	s[n+1]=s[n];//防止判断出bug 
	ff(i,1,n){ 
		int cnt=0,st=i;
		while(1){
			if(s[i]!=s[i+1]) ++cnt,++i;
			else break;
			if(i==n) break;
		}
		if(cnt) ++cnt;
		if(!cnt) continue;
		int k=cnt>>1;
		if(cnt&1) sum+=k;
		else{
			if(s[st]=='A') aa[++cnt1]=k;
			else bb[++cnt2]=k;
		}
	}
	sort(aa+1,aa+cnt1+1),sort(bb+1,bb+cnt2+1);
	int pos1=-1,pos2=-1;
	ff(i,1,cnt1){
		if(c>=aa[i]) c-=aa[i];
		else{aa[i]-=c,c=0,pos1=i;break;}
	}
	ff(i,1,cnt2){
		if(d>=bb[i]) d-=bb[i];
		else{bb[i]-=d,d=0,pos2=i;break;}
	}
	if(pos1!=-1&&pos2!=-1) return printf("YES\n"),void();
	if(pos1==-1&&pos2==-1){
		if(c+d<=sum) printf("YES\n");
		else printf("NO\n");
		return;
	}
	else if(pos1==-1){
		ff(i,pos2,cnt2){
			if(c>=bb[i]-1) c-=bb[i]-1;
			else{c=0;break;}
		}
		if(c<=sum) return printf("YES\n"),void();
		else return printf("NO\n"),void();
	}
	else{
		ff(i,pos1,cnt1){
			if(d>=aa[i]-1) d-=aa[i]-1;
			else{d=0;break;}
		}
		if(d<=sum) return printf("YES\n"),void();
		else return printf("NO\n"),void();
	}
}
signed main(){
	T=read();
	while(T--) solve();
	return 0;
} 
```
完结撒花

---

## 作者：Exber (赞：0)

贪心。

题意显然可以转化为**把 $a$ 个 $\texttt{A}$、$b$ 个 $\texttt{B}$、$c$ 个 $\texttt{A}\texttt{B}$ 和 $d$ 个 $\texttt{B}\texttt{A}$ 不重叠地放进字符串 $s$ 中，使得对应位相等**。

首先若放的 $\texttt{\texttt{A}}$、$\texttt{B}$ 的个数和 $s$ 中 $\texttt{A}$、$\texttt{B}$ 的个数不同，那么就是不行的。接下来考虑让所有放单个 $\texttt{A}$ 和 $\texttt{B}$ 的操作都挪到最后进行，那么问题就转化为判断能否把 $c$ 个 $\texttt{A}\texttt{B}$ 和 $d$ 个 $\texttt{B}\texttt{A}$ 都放进 $s$ 里面。

考虑一段形如 $\texttt{A}\texttt{B}\texttt{A}\texttt{B}\texttt{A}\texttt{B}\texttt{A}\texttt{B}$ 这样 **$\texttt{A}\texttt{B}$ 相间的极长子串**，设它的长度为 $cnt$，那么分类讨论：

- 若 $cnt$ 是奇数，那么这一段可以**放 $\lfloor\frac{cnt}{2}\rfloor$ 个 $\texttt{A}\texttt{B}$ 或 $\texttt{B}\texttt{A}$**；
- 若 $cnt$ 是偶数，那么：
  * 若这一段以 $\texttt{B}$ 结尾，即形如 $\texttt{A}\texttt{B}\texttt{A}\texttt{B}$，那么可以**放 $\lfloor\frac{cnt}{2}\rfloor-1$ 个 $\texttt{A}\texttt{B}$ 或 $\texttt{B}\texttt{A}$，或者可以放 $\lfloor\frac{cnt}{2}\rfloor$ 个 $\texttt{A}\texttt{B}$**；
  * 若这一段以 $\texttt{A}$ 结尾，即形如 $\texttt{B}\texttt{A}\texttt{B}\texttt{A}$，那么可以**放 $\lfloor\frac{cnt}{2}\rfloor-1$ 个 $\texttt{A}\texttt{B}$ 或 $\texttt{B}\texttt{A}$，或者可以放 $\lfloor\frac{cnt}{2}\rfloor$ 个 $\texttt{B}\texttt{A}$**；

不难发现，当 $cnt$ 为奇数时这一段**对 $\texttt{A}\texttt{B}$ 和 $\texttt{B}\texttt{A}$ 都是公平的**，即它们放的上限都是 $\lfloor\frac{cnt}{2}\rfloor$，并且对放多少个 $\texttt{A}\texttt{B}$ 和多少个 $\texttt{B}\texttt{A}$ 没有限制，只要它们数量加起来不超过 $\lfloor\frac{cnt}{2}\rfloor$ 就可以了。

所以可以令 $bot=\sum\limits_{cnt\operatorname{mod}2=1}\lfloor\frac{cnt}{2}\rfloor$ 即**奇数段最多可以放的 $\texttt{A}\texttt{B}$ 和 $\texttt{B}\texttt{A}$ 的数量**。

若 $cnt$ 为偶数，那么这一段**对 $\texttt{A}\texttt{B}$ 和 $\texttt{B}\texttt{A}$ 是不公平的**，即它们放的上限一个多，一个少。为了减少位置的浪费，不妨**先钦定这一段都放上限多的那种字符串，再用两个数组 $vala$ 和 $valb$ 存偏心 $\texttt{A}\texttt{B}$ 或者 $\texttt{B}\texttt{A}$ 即能放更多 $\texttt{A}\texttt{B}$ 或 $\texttt{B}\texttt{A}$ 的偶数段中两种字符串放置的上限**。

最后**若每一段偶数段都放上限多的字符串时 $c$ 或 $d$ 还是大于 $0$，那么就让偏心另一种字符串的偶数段分一些位置放这种字符串**即可。不难发现由于没分之前偶数段总共能放 $\lfloor\frac{cnt}{2}\rfloor$ 个字符串，分了之后只能放 $\lfloor\frac{cnt}{2}\rfloor-1$ 个，所以**分的段数肯定是越少越好**。那么按段的长度从大到小分即可。

代码如下：

```cpp
// Problem: D. Linguistics
// Contest: Codeforces Round #794 (Div. 2)
// URL: https://codeforces.com/contest/1686/problem/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <vector>
#include <map>
#include <set>

using namespace std;

const int S=1919810;

struct node
{
	int x,y;
}vala[S],valb[S];

int n,a,b,c,d;
char str[S];

inline bool cmp(node x,node y)
{
	return x.y>y.y;
}

inline void slove()
{
	cin>>a>>b>>c>>d>>(str+1);
	n=strlen(str+1);
	int cnta=0,cntb=0;
	for(int i=1;i<=n;i++)
	{
		cnta+=str[i]=='A';
		cntb+=str[i]=='B';
	}
	if(cnta-c-d!=a||cntb-c-d!=b) // A 或 B 的数量不符合的情况
	{
		cout<<"NO"<<endl;
		return;
	}
	int m1=0,m2=0,bot=0;
	str[n+1]=str[n];
	for(int i=1,cnt=0;i<=n+1;i++)
	{
		if(str[i]!=str[i-1])
		{
			cnt++;
		}
		else
		{
			if(cnt>1)
			{
				if(cnt&1) // 公平的奇数段
				{
					bot+=cnt/2;
				}
				else
				{
					if(str[i-1]=='B')
					{
						vala[++m1]=(node){cnt/2,cnt/2-1}; // 偏心 AB
						c-=cnt/2;
					}
					else
					{
						valb[++m2]=(node){cnt/2,cnt/2-1}; // 偏心 BA
						d-=cnt/2;
					}
				}
			}
			cnt=1;
		}
	}
	if(d>0)
	{
		sort(vala+1,vala+m1+1,cmp);
		for(int i=1;i<=m1;i++)
		{
			if(c+vala[i].x<=0)
			{
				c+=vala[i].x;
				d-=vala[i].y;
			}
			else
			{
				int lft=vala[i].x+c;
				if(lft>vala[i].y)
				{
					continue;
				}
				d-=vala[i].y-lft;
				c=0;
			}
		}
	}
	else
	{
		sort(valb+1,valb+m2+1,cmp);
		for(int i=1;i<=m2;i++)
		{
			if(d+valb[i].x<=0)
			{
				d+=valb[i].x;
				c-=valb[i].y;
			}
			else
			{
				int lft=valb[i].x+d;
				if(lft>valb[i].y)
				{
					continue;
				}
				c-=valb[i].y-lft;
				d=0;
			}
		}
	}
	c=max(c,0);
	d=max(d,0);
	cout<<(c+d<=bot?"YES":"NO")<<endl;
}

int main()
{
	ios::sync_with_stdio(false);
	int _=1;
	cin>>_;
	while(_--)
	{
		slove();
	}
	return 0;
}
```



---

## 作者：hfjh (赞：0)

# B.Linguistics

## 题意

给你一个 `AB` 串 $s$，问你是否可以用 $a$ 个`A`，$b$ 个 `B`，$c$ 个 `AB`，$d$ 个 `BA` 拼接成 $s$。

## 题解

首先我们把连续的 `AB` 交替出现的串分离出来。

例如样例 `BBABABABABBBABABABABABABAABABA`，

我们分离成 `B[BABABABAB]B[BABABABABABABA][ABABA]`。

我们发现分离之后单个的 `A/B` 只能用单个的填，我们就只用考虑连续交替串。

我们把连续交替串按照长度奇偶分为两类：

- 长度为奇数，开头结尾重复了一个一样的，例如 `[ABABA]` 我们填它的方法是用 1 个开头结尾出现的单个字符 `A` 和 $\frac {len-1} 2$ 个 `AB/BA`。

- 长度为偶数，例如 `[BABABABABABABA]`，就有两种情况：
  
  - 1.用 $\frac {len} 2$ 个 `BA` 填充。
  
  - 2.用 $\frac{len}2 - 1$ 个 `AB/BA` 填充，用 1 个 `A` 和 1 个 `B` 填充。

因为 1 个 `A` 和 1 个 `B` 可以拼成一个 `AB/BA`，所以我们尽量要先消耗 `AB/BA`，保留 `A/B`。

长度为奇数的填充方法是唯一的，我们先贪心考虑长度为偶数的。

先按长度从小到大排序，能用方法 1 填的尽量用方法 1，这样消耗的单个 `A/B` 是最少的。

剩下的记录 `AB/BA` 都可以选的然后判断 $ab + ba$ 和它大小相等不相等。

注意 1 个 `A` 和 1 个 `B` 可以拼成一个 `AB/BA`。

## 代码
```cpp
#include<bits/stdc++.h>
#define puba push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
using namespace std;
const int N = 2e5 + 10;
int t, n, a, b, ab, ba;
int l, r, arb;
int vis[N]; 
vector<pair<int, int> >p;
char s[N];
bool cmp (const pair<int, int> a, const pair<int, int> b){
	return a.se - a.fi < b.se - b.fi;
} 
void input(){
	cin >> a >> b >> ab >> ba;
	cin >> (s + 1);
	n = strlen(s + 1);
}
bool op(){
	for(l = 1, r = 1; r < n; ++r){
		if(s[r] == s[r + 1]){
			if(l != r){
				p.puba({l, r});
				
			}
			l = r + 1;
		}	
	}
	if(l != r)p.puba({l, r});
	sort(all(p), cmp);
	for(auto i : p){
		if((i.se - i.fi + 1) % 2 == 1){
			if(s[i.fi] == 'A') --a;
			else --b;
			arb += (i.se - i.fi) / 2;
		}else{
			if(s[i.fi] == 'A' && ab >= (i.se - i.fi + 1) / 2 ) ab -= (i.se - i.fi + 1) / 2;
			else if(s[i.fi] == 'B' && ba >= (i.se - i.fi + 1) / 2) ba -= (i.se - i.fi + 1) / 2;
			else{
				arb += (i.se - i.fi - 1) / 2;
				--a; --b;
			}
		}
		for(int j = i.fi; j <= i.se; ++j) vis[j] = 1;
	}	
	for(int i = 1; i <= n; ++i){
		if(!vis[i]){
			if(s[i] == 'A') --a;
			else --b;
		}
	} 
	int w = min(a, b);
	if(w < 0) return 0;
	a -= w, b -= w;
	arb -= w;
	return (a == 0) && (b == 0) && (ab + ba == arb);
}
void qk(){
	arb = 0;
	p.clear();
	for(int i = 1; i <= n; ++i){
		vis[i] = 0;
	}
}
int main(){
	cin >> t;
	while(t--){
		qk();
		input();
		cout<< (op() ? "YES" : "NO") <<"\n";
	}
	return 0;
}

---

