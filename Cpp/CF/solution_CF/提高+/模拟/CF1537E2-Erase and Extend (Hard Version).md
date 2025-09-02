# Erase and Extend (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is the constraints on $ n $ and $ k $ . You can make hacks only if all versions of the problem are solved.

You have a string $ s $ , and you can do two types of operations on it:

- Delete the last character of the string.
- Duplicate the string: $ s:=s+s $ , where $ + $ denotes concatenation.

You can use each operation any number of times (possibly none).

Your task is to find the lexicographically smallest string of length exactly $ k $ that can be obtained by doing these operations on string $ s $ .

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a\ne b $ ;
- In the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

In the first test, it is optimal to make one duplication: "dbcadabc" $ \to $ "dbcadabcdbcadabc".

In the second test it is optimal to delete the last $ 3 $ characters, then duplicate the string $ 3 $ times, then delete the last $ 3 $ characters to make the string have length $ k $ .

"abcd" $ \to $ "abc" $ \to $ "ab" $ \to $ "a" $ \to $ "aa" $ \to $ "aaaa" $ \to $ "aaaaaaaa" $ \to $ "aaaaaaa" $ \to $ "aaaaaa" $ \to $ "aaaaa".

## 样例 #1

### 输入

```
8 16
dbcadabc```

### 输出

```
dbcadabcdbcadabc```

## 样例 #2

### 输入

```
4 5
abcd```

### 输出

```
aaaaa```

# 题解

## 作者：岸芷汀兰 (赞：28)

# 一、题目：

[codeforces原题](https://codeforces.com/problemset/problem/1537/E2)

[洛谷原题](https://www.luogu.com.cn/problem/CF1537E2)

# 二、思路：

这题不知道为什么官方题解写得那么复杂。还需要用到扩展 KMP，即 Z 函数。感谢 [Robert_JYH](https://www.cnblogs.com/Robert-JYH) 巨佬提供的思路，让我明白了一种非常简单的做法。

首先，我们可以证明，最优解一定是通过先执行操作 1，后执行操作 2 来得到的（当然也可以不进行操作 1，直接进行操作 2）。因为如果最优解是执行了一些操作 2 之后，再执行的操作 1，那么我们发现把操作 1 放到操作 2 之前操作一定会使答案变得**不劣**。

所以问题就转化成给定一个字符串 $s$，需要保留 $s$ 的一个前缀 $pre$，同时让 $pre$ 复制若干次，得到一个长度为 $k$ 的字符串（多余的部分删去）。目标是让最终的字符串的字典序最小。

暴力当然很简单了，我们枚举所有前缀 $pre$，模拟这个过程，更新答案即可。你就可以成功地解决这道题的简单版了。

那么现在来考虑线性的做法。

我们设当前最优的前缀为 $s[0\sim p-1]$，现在枚举到的前缀是 $s[0\sim i]$。那么分为三种情况。（字符串的下标从 0 开始。）

1. 若 $s[i]>s[i\bmod p]$，那么非常遗憾，$i$ 及 $i$ 以后的所有前缀均不能作为最优答案。直接跳出循环。
2. 若 $s[i]<s[i\bmod p]$，我们发现用前缀 $s[0\sim i]$ 比前缀 $s[0\sim p-1]$ 更优，于是令 $p\gets i+1$。
3. 若 $s[i]=s[i\bmod p]$，这并不能说明什么，我们只能什么都不做。

然后呢？然后你就会惊奇的发现，你写完了一道 Div2 难度的第六题！

# 三、代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
#define FILEIN(s) freopen(s".in", "r", stdin);
#define FILEOUT(s) freopen(s".out", "w", stdout)
#define mem(s, v) memset(s, v, sizeof s)

inline int read(void) {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return f * x;
}

int n, K;
string s;

int main() {
    n = read(); K = read();
    cin >> s;
    int p = 1, i = 0, n = s.length();
    for (; i < n; ++ i) {
        if (s[i] > s[i % p]) break;
        if (s[i] < s[i % p]) p = i + 1;
    }
    for (i = 0; i < K; ++ i) putchar(s[i % p]);
    puts("");
    return 0;
}
```



---

## 作者：vectorwyx (赞：11)

蒟蒻斗胆来一篇贪心的解法（有详细说明！）qwq

首先选一段前缀再不断复制一定是最优的，这个在 E1 的题解区里有就不赘述了。

那么问题就变成了比较 $n$ 个由 $n$ 段前缀不断自我复制所产生的字符串的字典序大小。我们从 $0$ 循环到 $n-1$（下标从 $0$ 开始），边循环边更新最小字符串是由哪段前缀产生的。记当前的答案为 $ans$，对于第 $i$ 次循环：

* 如果 $s_i>s_0$，终止循环
* 如果 $s_i<s_0$，令 $ans=i$，继续下一次循环
* 如果 $s_i=s_0$，则令 $j=i+1$，从左向右遍历 $s[j,n]$，直到 $s_j \not=s_{j\ mod \ i}$。如果 $s_j>s_{j\ mod \ i}$，终止循环；否则，令 $ans=j$，进入第 $j+1$ 次循环。

核心代码：
```cpp
	int n,k,ans=1;cin>>n>>k>>s;
	fo(i,1,n-1){
		int R=i;
		while(R<n&&s[R]==s[R%ans]) R++;
		if(R==n) break;
		if(s[R]<s[R%ans]) ans=R+1,i=R;
		else break;
	}
```
灵魂拷问：这样为什么是对的？前两条肯定没有疑问，重点在第三条上。

首先，我们这样做保证了每次循环时 $ans=i-1$。如果 $s_i=s_0$，那么 $[0,i]$ 这段前缀一定不优于 $[0,i-1]$ （从全是 $s_0$ 的最长前缀的长度考虑会发现这是显然的）。但我们又无法确定 $[0,j](j>i)$ 与 $[0,i-1]$ 的大小关系，于是继续向后看。

对于 $j=i+1$，由于我们已知 $s_i=s_0$，所以只需要比较 $s_{i+1}$ 与 $s_1$。如果大于，那么在此之后的前缀一定不优于 $[0,i-1]$；如果小于，那么 $[0,i+1]$ 优于 $[0,i-1]$，更新答案并进入 $i+1$ 的下一次循环即可；如果仍然等于，显然 $[0,i+1]$ 也不优于 $[0,i-1]$，继续重复上述过程即可。这有点类似于数学归纳法，可以看出是正确的。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}

const int N=5e5+5;
string s;

int main(){
	int n,k,lst=1;cin>>n>>k>>s;//lst就是ans
	fo(i,1,n-1){
		int R=i;
		while(R<n&&s[R]==s[R%lst]) R++;
		//printf("%d %d %d\n",i,R,lst);
		if(R==n) break;
		if(s[R]<s[R%lst]) lst=R+1,i=R;
		else break;
	}
	//printf("%d\n",lst);
	fo(i,1,k/lst) fo(j,0,lst-1) putchar(s[j]);
	fo(i,0,k%lst-1) putchar(s[i]);
	return 0;
}
```
点个赞再走吧，谢谢您！QAQ

---

## 作者：meyi (赞：10)

以下将字符串 $s$ 的前缀 $s[1..n]$ 称为 $\text{prefix}(n)$，将字符串 $s$ 无限连接自身构成的字符串的前 $k$ 个字符称为 $f_k(s)$，即 $f_k(s)=\left\{
    \begin{array}{l}
            s[1..k]\ \ (|s|\ge k) \\  f_k(s+s)\ \ (|s|<k)
        \end{array}
\right.$。

将题意转化为求 $f_k(prefix(x))$ 最小的 $x$，有一种贪心做法如下：

枚举前缀的结尾位置 $i$ ，设当前找到的最优前缀为 $pos$ ，$f_k(prefix(pos))[i]$ 为 $t$，比较 $s[i]$ 与 $t$ 的大小关系，有如下三种情况：

1. $s[i]>t$，此时由于 $i$ 以后的每个位置的前缀都会包含 $s[i]$，所以 $i$ 以后不会有更优解，因此直接退出循环。

2. $s[i]<t$，此时若有 $s[1..i-1]=f_k(\text{prefix}(pos))[1..i-1]$  ，则此时 $i$ 优于 $pos$，更新答案。反证一下满足条件，按上述方式循环，若 $s[1..i-1]> f_k(\text{prefix}(pos))[1..i-1]$，则在 $i-1$ 或更早的位置就已退出循环；若 $s[1..i-1]<f_k(\text{prefix}(pos))[1..i-1]$，则不符合 $pos$ 是最优解的定义。故 $s[1..i-1]=f_k(\text{prefix}(pos))[1..i-1]$，满足更新答案的条件。

3. $s[i]=t$，此时直接继续枚举 $i+1$。易得 $f_k(prefix(i))[i+1]=s[1]$，$f_k(prefix(pos))[i+1]=s[(i\mod pos)+1]$，此时必有 $s[(i\mod pos)+1]\le s[1]$，因为若 $s[(i\mod pos)+1]>s[1]$，则我们直接在此处填 $s[1]$ 会更优，不符合 $pos$ 是最优解的定义，同理 $f_k(prefix(i))$ 与 $f_k(prefix(pos))$ 的第 $i+2$，$i+3$，$\cdots$，$k$ 个字符也可按上述方式比较大小关系。因此 $i$ 不会比 $pos$ 更优，但继续枚举下去可能会有更优解。

相关代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
#define x (i-1)%pos+1
const int maxn=5e5+10;
int m,n;
char t[maxn];
int main(){
    scanf("%d%d%s",&n,&m,t+1);
    ri k=min(m,n),pos=1;
    for(ri i=2;i<=k;++i)
        if(t[i]<t[x])pos=i;
        else if(t[i]>t[x])break;
    for(ri i=1;i<=m;++i)putchar(t[x]);
    return 0;
}
```

---

## 作者：Morgen_Kornblume (赞：7)

# 【题解】CF1537E2 解题报告

### Part.1 题意简述

给定一个长度为 $n$ 的字符串 $ S $（$ 1 \le n \le 5 \cdot 10^5 $），支持如下操作：

1. 删去 $S$ 结尾的一个字符。

2. 将 $S$ 复制一倍，得到一个新的字符串 $ S' = S + S $（加意为将后一个字符串接在前一个字符串末尾）。

所有操作可以按任意顺序使用任意次。

目标：得到一个长度为 $ k $（$1 \le k \le 5 \cdot 10^5 $）的字符串 $Ans$，并且使 $Ans$ 的字典序最小。

E1 是本题的数据弱化版（$ 1 \le n,k \le 5000 $），通过本题的算法也可通过 E1，故本题解也视同为 E1 的题解。

### Part.2 思路理解

前置知识：KMP算法。

CF的出题人题解给的是一个 Z 函数的解法，但是笔者不会 Z 函数，所以本题解提供一个类 KMP（实际就是基于 KMP）的贪心解法。

首先，看到字典序最小，就考虑从前往后贪心，因为前面的字符越小，答案的字典序就越小。

而在本题中，操作 1 和操作 2 实际就允许我们从原字符串的前缀复制得到答案串，我们需要明白的是怎样复制前缀能使答案串的字典序最小。

对于答案串中的一个字符 $ C'_i $，我们思考一下它可以从哪里得来：

1. 原串同一位置的字符 $ C_i $（当且仅当 $1 \le i \le n$）。

2. 由原串的某一前缀复制得到。

第一种方式很简单，不再赘述，我们主要考虑第二种方式。

考虑答案串中 $C'_i$ 之前的 $i-1$ 个字符，和 KMP 算法一样，我们不断计算前 $i-1$ 个字符构成的字符串中后缀与前缀的最大匹配长度（记为 $j$），并计算一个 $Next$ 数组用于处理失配时的情况（维护 Fail 树）。

当前的 $C'_i$ 以第二种方式可以得来的位置为所有可以与前 $i-1$ 个字符的后缀匹配的前缀的下一个字符（这里要动一下聪明的大脑理解一下这个复制过程）（相当于从这个后缀的前面断开，由其前缀的部分复制得到现在的答案串）。

观察到随着匹配长度 $j$ 的不断增加，所有的可能得到的位置对应的前缀实际构成了 Fail 树上从根到当前节点深度增加的一条链，故我们可以维护从根到当前点的最优决策，从而避免每次都要从当前节点往 Fail 树的根上跳的复杂度开销。

需要极度注意的一些点（笔者当晚的 CF 比赛就因为这两点未能通过 E 题）：

1. 决策点和匹配前缀构成的子串不能与和它匹配的后缀子串有重叠（否则这样就违反了操作 2 的要求，类似于 NOI2014 动物园），这时需要强制回到  Fail 树上的父亲节点。 

2. 如果之前使用过操作 2 来得到某一 $C'_i$ ，那么后面就不能从原串获取字符作为答案串的字符，因为相当于这个字符已经被操作 1 在之前删去了。

### Part.3 代码实现

请注意上文提到的细节！

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
int n,k;
char ori[500010];//原串 
char build[500010];//构造的新串 
int nxt[500010];//Fail 树上的父亲节点 
char mc[500010];//匹配前缀长度为 j 时的最优决策 
 
int main(){
	
	scanf("%d%d",&n,&k);
	
	scanf("%s",ori+1);
	bool flag=true;
	for(int i=1,j=0;i<=k;i++){
		if(i==1){
			build[i]=ori[i];
			putchar(build[i]);
			mc[0]=ori[i];
			continue;
		}
		
		while((j+1)*2>i)j=nxt[j];//转移点与匹配前缀有重叠，强制退Fail 
		
		char jc=mc[j];
		if(i<=n&&flag){//注意：前面用过复制前缀就不能再用原串了 
			jc=min(jc,ori[i]);
		}
		build[i]=jc;//最优决策点 
		
		if(i<=n&&build[i]!=ori[i]&&flag)flag=false;
		
		while(j&&build[i]!=build[j+1])j=nxt[j];//KMP过程，计算后缀与前缀的匹配 
		if(build[j+1]==build[i])j++;
		nxt[i]=j;
		
		mc[i-1]=min(mc[nxt[i-1]],build[i]);//计算最优决策点 
		putchar(build[i]);
	}
	
	return 0;
} 
```


---

## 作者：Aestas16 (赞：3)

考虑贪心。记 $i$ 为最小的满足 $s_i \ge s_1\ (i > 1)$ 且 $[1,n]$ 字典序小于 $[i,n]$ 字典序的 $i$，则答案即为循环输出 $[1,i-1]$ 直到达到 $k$ 位为止。

考虑如何找到这个 $i$，瓶颈在于如何快速判断 $[1,n]$ 与 $[i,n]$ 的字典序大小，可以使用后缀排序解决，时间复杂度 $\Theta(n \log n)$。

然而实现上还有一些小细节，我们应当把原串复制一遍后再进行如上操作，原因是有可能出现如下情况：

`ddcd` 按照上述操作会变为 `ddcdddcd`，但实际上 `ddcddcdd` 更优，因为循环后的字符串会影响到后缀字典序的大小，先复制一遍原串再进行后缀排序就不会有如上问题了。

代码：
```cpp
/*
    I will never forget it.
*/

// 392699

#include <bits/stdc++.h>

using namespace std;

template <class T> void fr(T &a, bool f = 0, char ch = getchar()) {
    for (a = 0; ch < '0' || ch > '9'; ch = getchar()) ch == '-' ? f = 1 : 0;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) a = a * 10 + ch - '0';
    a = f ? -a : a;
}
int fr() {
    int a;
    return fr(a), a;
}

const int N = 1e6 + 5;

char s[N];
int n, m, k, fir[N], sec[N], cnt[N], sa[N], qwq[N];

void SA() {
    for (int i = 1; i <= n; i++) {
        fir[i] = s[i] - '0' + 1;
        cnt[fir[i]]++;
    }
    for (int i = 2; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) sa[cnt[fir[i]]] = i, cnt[fir[i]]--;
    for (int P = 1, ss = 0; P <= n; P <<= 1, ss = 0) {
        for (int i = n - P + 1; i <= n; i++) sec[++ss] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > P) sec[++ss] = sa[i] - P;
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++) cnt[fir[i]]++;
        for (int i = 2; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[fir[sec[i]]]] = sec[i], cnt[fir[sec[i]]]--, sec[i] = 0;
        swap(fir, sec), ss = 1, fir[sa[1]] = 1;
        for (int i = 2; i <= n; i++)
            if (sec[sa[i]] == sec[sa[i - 1]] && sec[sa[i] + P] == sec[sa[i - 1] + P])
                fir[sa[i]] = ss;
            else
                fir[sa[i]] = ++ss;
        if (ss == n) break;
        m = ss;
    }
}

struct OI {
    int RP, score;
} CSPS2021, NOIP2021;

int main() {
    CSPS2021.RP++, CSPS2021.score++, NOIP2021.RP++, NOIP2021.score++, 392699;
    fr(n), fr(k), scanf("%s", s + 1), m = 122 - 48 + 1;
    for (int i = 1; i <= n; i++) s[i + n] = s[i];
    n <<= 1, SA();
    for (int i = 1; i <= n; i++) qwq[sa[i]] = i;
    for (int i = 2; i <= n; i++) 
        if (s[i] >= s[1]) {
            if (qwq[i] > qwq[1]) {
                for (int l = 1, j = 1; j <= k; l++, j++) {
                    if (l == i) l = 1;
                    putchar(s[l]);
                }
                return 0;
            }
        }
    for (int l = 1, j = 1; j <= k; l++, j++) {
        if (l == n + 1) l = 1;
        putchar(s[l]);
    }
    return 0;
}
```


---

## 作者：YuanZihan1225 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1537E2)

[双倍经验（弱化版）](https://www.luogu.com.cn/problem/CF1537E1)

# 思路分析

首先，第一种操作一定会将一个穿变成它的前缀，所以我们只需要考虑用它的几个前缀拼成的长为 $k$ 的串中字典序最小的，所以就能一下子想到暴力代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k;
string s, ans = "~~~~~~~~~~~";
int main()
{
	cin >> n >> k >> s;
	for(int i = 0; i < n; i++)
	{
		string a = s.substr(0, i + 1);
		while(a.size() < k)
			a = a + a;
		ans = min(ans, a.substr(0, k));
	}
	cout << ans;
	return 0;
}
```
暴力可以轻易的 AC 弱化版，但这道会 TLE ，所以我们要考虑优化：

明显，如果我们存一个最优前缀，再比较，就会发现当一个前缀不优时，比它长的前缀也一定不优，我们就可以跳过这一部分，同时在比较前缀时，可以从高位比起，同样能够优化。代码见下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k;
string s;
int main()
{
	cin >> n >> k >> s;
	int p = 1, n = s.size();//p表示当前最优前缀的长度
	for(int i = 0; i < n; i++)//注意要正向枚举前缀长度
	{
		if(s[i] > s[i % p])//如果字典序更大就直接跳出
			break;
		if(s[i] < s[i % p])//如果字典序更小就更新p
			p = i + 1;
	}
	for(int i = 0; i < k; i++)//输出时利用模循环输出k位的最优前缀
		putchar(s[i % p]);
	return 0;//完美地结束QWQ
}
```

---

## 作者：紊莫 (赞：1)

短码题，简单题。

---

首先有一个小结论：我们一定是先删除后反复添加。

考虑删除，添加，再删除的情况，发现如果这样能更优，那一定不如把前面一半也变成这样，也就是在前面就删。

然后转化第二个条件，每次翻倍等价于重复，我们对长度取模即可。

那么我们要保留几位呢？显然是贪心的保留，如果能保留就保留，否则开始不优了，也就是说不管后面怎么样，因为这一位（高位）偏大，都不可能是答案了，就退出循环判断。

假设当前长度为 $len$，那么 $S_i$ 对应的就是 $S_{i\bmod len}$，不断比较这两位即可。

什么意思呢？就是说我们现在是前缀长度为 $len$ 的在重复，我想把前缀改的长一点，考虑这个长度为 $len$ 的前缀反复复制，那么和我枚举到的当前 $S_i$ 对齐的就是 $S_{i\bmod len}$，那我们比较这一位就行。

时间复杂度线性。

代码很短就不放了。

---

## 作者：NightmareAlita (赞：1)

## 简要题意

给你一个字符串，找到该字符串的一个前缀并不断复制，可以删除末尾元素，最终要使得得到的字符串长度为 $k$ 且字典序最小。

## 策略分析

对于此类构造题，我们一般需要运用逆向思维，也就是说我们要从前往后扫而不是从后往前删。为什么这样想呢？我们可以发现，字典序最小当且仅当我们要找的前缀的第 $i$ 位比第 $i \bmod len$ 位的字典序小，这样拼接起来才能够使得字典序最小，这个结论是显然的，证明可以使用反证法。

## 参考代码

```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

namespace SHAWN {
    int n, k, l = 1;
    string s;
    int work()
    {
        cin >> n >> k >> s;
        for (int i = 0; i < n; ++i) {
            if (s[i] < s[i % l]) { l = i + 1; }
            else if (s[i] > s[i % l]) { break; }
        }
        for (int i = 0; i < k; ++i) {
            cout << s[i % l];
        }
        return 0;
    }
}

signed int main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    return SHAWN :: work();
}
```



---

## 作者：Little09 (赞：1)

### 前言

这个菜鸡 Little09 连 Z 函数都不会，但是 Little09 还是想做 CF1537E2。

### 转化后题意

给定长度 $n$ 的字符串 $s$，选择 $s$ 的一个前缀，它的无限循环构成的字符串的字典序最小。输出前 $k$ 位。

### 分析

我们考虑现在考虑第 $i$ 位的前缀，$i$ 位以前的答案是第 $ans$ 位的前缀。

如果这一位比目前的答案要大，那么直接退出，因为再往后也不可能更大了。

如果这一位比目前的答案要小，那么把这一位保存为答案，继续往下找下一位。

如果这一位与目前的答案相同，怎么办？

我们先不考虑相同的情况（就是相同的时候不存做答案，也不退出），写出如下的代码：

```cpp
n=read(),m=read();
cin >> a;
ans=0;
for (int i=1;i<n;i++)
{
	int tot=i%(ans+1);
	if (a[tot]<a[i]) break;
	if (a[tot]>a[i]) ans=i;
	//else do something..
}
for (int i=0;i<m;i++) cout << a[i%(ans+1)];

```

令人意料之外的是它一发就过了。

### 为什么这样是对的

想手玩构造出 Hack 数据，经过我半个小时的尝试后失败。我们用随机程序把它和 E1 做个对拍，我跑了 $40000$ 多组仍然没有差异，所以我们可以认定它是正确的算法。

具体的证明 Little09 认为比较麻烦，感觉有种数学归纳的思想，带上几次分类讨论，~~也不确定有没有假了~~，所以不再赘述，请读者自己尝试证明。如果有简单的证明方法，欢迎在评论区提出或者私信我。也欢迎来 Hack！

---

## 作者：Helloworldwuyuze (赞：0)

# CF1537E2题解

## Des

给定 $n,k$ 和一个字符串 $s$。其中，$s$ 可以：

- 删去末尾的一个字符。
- 将 $s$ 复制一遍接到它的后面。

让 $s$ 最后变成长度为 $k$ 的字典序最小的字符串。

## Sol

### Part 1

首先，我们有结论：我们一定是先删除 $s$ 的尾巴，然后不断复制 $s$ 直到超过 $k$，然后再删去后面的多余部分。

> **证明**
>
> 如下图：
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/2318c1ns.png)
>
> 这里 $T$ 是 $S$ 删除一些末尾后得到的字符串，设 $S$ 长度为 $n$，$T$ 长度为 $m$。
>
> 如果这里 $S+T$ 优于 $S+S$，则必有 $T_m< S_m$。
>
> 那么我们不妨在刚开始就把 $S$ 减成 $T$，这样 $T$ 比上面两个 $S+T$ 与 $S+S$ 都更加优。

### Part 2

现在问题就是我们要删除到哪里是最好的。

我们设当前处理到了前 $i$ 个位置，且最好的是 $1\dots j$。

于是，我们分类讨论：

- 如果 $s_i = s_{i\bmod j}$ 那么我们就可以啥都不用干。
- 如果 $s_i >s_{i\bmod j}$，因为从 $j+1\dots i-1$ 都与前面的对应位置相等，因此这个地方大了就肯定不优，因此退出循环即可。
- 如果 $s_i<s_{i\bmod j}$，那么显然把答案的范围更新到 $1\dots i$ 更好。

于是我们就做完了。

```cpp
const int INF = 0x3f3f3f3f;
typedef pair<int,bool> PII;
typedef pair<int,PII> PIII;
const int N = 5e5 + 10;
const int M = 20 + 10;
const int MOD = 1e9 + 7;

int n, k, p;
char s[N];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n>>k>>s;
	p = 1;
	for(int i=1;i<n;++i)
		if(s[i] < s[i%p])	p = i+1;
		else if(s[i] > s[i%p])	break;
	for(int i=0;i<k;++i)	cout<<s[i%p];
	cout<<endl;
	return 0;
}
```

---

## 作者：WOL_GO (赞：0)

## 首先为什么先用操作 $1$ 再用操作 $2$ 一定不劣：

假如最优解是先用操作 $2$，再用操作 $1$：

我们来看，假如用了操作 $2$ 之后再用操作 $1$，等价于会出现不同的前缀连接在一起的情况，如：$[1\dots i][1\dots j]$。下面证明这种情况一定不是最优的：

我们假设答案是 $[1\dots i][1\dots j]$：

+ 假如 $[1\dots i]<[1\dots j]$ 那么我们可以把答案替换成 $[1\dots i]$ $[1\dots i]$。

+ 假如 $[1\dots i]=[1\dots j]$ 那么我们可以把答案替换成 $[1\dots j][1\dots j]$。

+ 假如 $[1\dots i]<[1\dots j]$ 那么我们可以把答案替换成 $[1\dots j][1\dots j]$。

因此，一定不会出现答案是两个不同前缀拼接的情况，也就是答案一定不可能在用了操作 $2$ 之后再用操作 $1$ 那么问题就变成了找到一个最小的前缀（一直用操作 $1$），然后无线复制下去（一直用操作 $2$）。

## 如何线性的找到一个最小的前缀

假设你已经找到了一个长度为 $p$ 的前缀。对于当前 $i$，你考虑要不要以前 $i$ 个字符为前缀，你可以通过判断 $p$ 复制完之后，对应于 $i$ 的位置 $x$。比较 $i$ 和 $x$ 这两个位置的字符大小。

假如 $s_{i}<s_{x}$ 那么你就可以以 $i$ 为前缀，因为更优。

假如 $s_{i}>s_{x}$ 那么从这里开始已经大于当前最优解了，那么 $i$ 以后的都不可能最为一个最优前缀了，那么直接退出循环。

假如 $s_{i}=s_{x}$ 那么比较不了，忽略。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace read_write{
	typedef long long ll;
	template<typename T> 
	void read(T &x){
		x = 0;char ch = getchar();ll f = 1;
		while(!isdigit(ch)){if(ch == '-')f*=-1;ch=getchar();}
		while(isdigit(ch)){x = x*10+ch-48;ch=getchar();}x*=f;
	}
	template<typename T, typename... Args> void read(T &first, Args& ... args){
		read(first);
		read(args...);
	}
	template<typename T>
	void write(T x){
		if(x<0){
			putchar('-');
			x*=-1;
		}
		if(x>9){
			write(x/10);
		}
		putchar(x%10+'0');
	}
	template<typename T, typename... Args> void write(T &first, Args& ... args){
		write(first);
		write(args...);
	}
	template<typename T>
	void readm(T *a,T l,T r){
		for(int i=l;i<=r;++i)read(a[i]);
	}
	template<typename T>
	void writem(T *a,T l,T r,char c=0){
		for(int i=l;i<=r;++i)write(a[i]),c?putchar(c):c=0;
	}
}
using namespace read_write;
int n,k,p=1;
string s;
int main() {
	read(n,k);
	cin>>s;
	s=" "+s;
	for(int i=1;i<=n&&s[i]<=s[(i-1)%p+1];i++)if(s[i]<s[(i-1)%p+1])p=i;
	for(int i=1;i<=k;i++)putchar(s[(i-1)%p+1]);
	return 0;
}
```



---

## 作者：FjswYuzu (赞：0)

问题是找到最优的一个前缀。因为如果 $\operatorname{pre}(s,a) < \operatorname{pre}(s,b)$，那么显然 $\operatorname{pre}(s,a)^\infty < \operatorname{pre}(s,b)^\infty$，推出 $\operatorname{pre}(s,a)^{\frac{k}{|\operatorname{pre}(s,a)|}} < \operatorname{pre}(s,b)^{\frac{k}{|\operatorname{pre}(s,b)|}}$。

那么先找到第一个索引 $t$ 使得 $s_t>s_1$。显然 $s_t$ 及后面的所有字符都没用了。（显然可以只选择前面的部分）

考虑贪心双指针优化匹配过程。每次找到一个索引 $i$ 使得 $s_i=s_1$ 时，向后匹配从 $i$ 匹配至 $cur$，$1$ 匹配至 $now$。分类讨论：

- 如果 $s_{now}>s_{cur}$，那么当前这个索引对应的某一个前缀更优；   
- 如果 $s_{now}=s_{cur}$ 并且 $cur \neq n$，无法确定哪个更优秀，那就继续找；   
- 否则不存在更优秀的可能性，最优秀的前缀长度应该为 $cur-now$，退出循环。

注意，如果正常退出循环，那么最优秀的循环节为 $n$。

```cpp
#include<cstdio>
int n,k;
char s[500010];
int main()
{
	scanf("%d %d %s",&n,&k,s+1);
//	int tmp=n;
	for(int i=2;i<=n;++i)
	{
		if(s[i]>s[1])
		{
			n=i-1;
			break;
		}
	}
	int now=1,ls=1;
	for(int i=2;i<=n;++i)
	{
		if(s[1]==s[i])
		{
			int cur=i;
			while(s[now]==s[cur] && cur<n)	++now,++cur;
			if(s[now]>s[cur])	ls=i,i=cur;
			else if(s[now]==s[cur] && cur!=n)	continue;
			else
			{
				cur-=now;
				ls=cur;
				goto ff;
			}
			now=1;
		}
	}
	ls=n;
	ff:;
	for(int i=1;i<=k;++i)
	{
		int x=i%ls;
		if(x==0)	x=ls;
		putchar(s[x]);
	}
	return 0;
}
```

---

## 作者：xlpg0713 (赞：0)

通过~~猜结论~~找性质可以得知最后一定是选择 $s$ 的一个前缀经过若干次倍增得到的。证明就是随便模拟一下发现倍增之后再删字符是不优的。

于是考虑快速模拟这个过程，我的想法比较暴力。考虑比较前缀 $p$ 和 $q$ 形成的字符串，直接二分哈希，即求一个长度为 $x$，每 $|p|$ 个一循环的字符串的哈希值，这个东西很容易表示为一个等比数列求和再加上什么东西。预处理 $base^i,base^{-i},(base^i-1)^{-1}$ 即可做到单次 $O(1)$ 查询。

---

## 作者：Ryan_Adam (赞：0)

# CF1537E2 Erase and Extend 题解
## 分析
通过观察题目，可以证明结果一定是由多次前缀复制得来的。

题目要求你进行删和复制的操作，与其交替着操作，不如直接先删到最优的前缀再进行复制。

现在就是要找最优的前缀。从头一位一位往后遍历。用 $l$ 来存储目前最优前缀的长度，第 $i$ 位对应复制后的 $k$ 位最优前缀就是第 $i\bmod l$ 位。在往后遍历时，如果下一位的 ASCII 码比最优前缀第 $i\bmod l$ 位的大，就说明后面没有最优解了，直接 `break`。如果小于的话，说明当前的解更优，更新一下长度即可。

复杂度 $\mathcal O(n)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Raiden
{
    int work()
    {
        string s;
        int n,k;
        int l=1;
        cin>>n>>k>>s;
        for(int i=0;i<n;i++)
        {
            if(s[i]>s[i%l])
                break;
            else if(s[i]<s[i%l])
                l=i+1;
        }
        for(int i=0;i<k;i++)
            cout<<s[i%l];
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return Raiden::work();
}
```

---

