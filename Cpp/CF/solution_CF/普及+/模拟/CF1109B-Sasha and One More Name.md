# Sasha and One More Name

## 题目描述

Reading books is one of Sasha's passions. Once while he was reading one book, he became acquainted with an unusual character. The character told about himself like that: "Many are my names in many countries. Mithrandir among the Elves, Tharkûn to the Dwarves, Olórin I was in my youth in the West that is forgotten, in the South Incánus, in the North Gandalf; to the East I go not."

And at that moment Sasha thought, how would that character be called in the East? In the East all names are palindromes. A string is a palindrome if it reads the same backward as forward. For example, such strings as "kazak", "oo" and "r" are palindromes, but strings "abb" and "ij" are not.

Sasha believed that the hero would be named after one of the gods of the East. As long as there couldn't be two equal names, so in the East people did the following: they wrote the original name as a string on a piece of paper, then cut the paper minimum number of times $ k $ , so they got $ k+1 $ pieces of paper with substrings of the initial string, and then unite those pieces together to get a new string. Pieces couldn't be turned over, they could be shuffled.

In this way, it's possible to achive a string abcdefg from the string f|de|abc|g using $ 3 $ cuts (by swapping papers with substrings f and abc). The string cbadefg can't be received using the same cuts.

More formally, Sasha wants for the given palindrome $ s $ find such minimum $ k $ , that you can cut this string into $ k + 1 $ parts, and then unite them in such a way that the final string will be a palindrome and it won't be equal to the initial string $ s $ . It there is no answer, then print "Impossible" (without quotes).

## 说明/提示

In the first example, you can cut the string in those positions: no|l|on, and then unite them as follows on|l|no. It can be shown that there is no solution with one cut.

In the second example, you can cut the string right in the middle, and swap peaces, so you get toot.

In the third example, you can't make a string, that won't be equal to the initial one.

In the fourth example, you can cut the suffix nik and add it to the beginning, so you get nikkinnikkin.

## 样例 #1

### 输入

```
nolon
```

### 输出

```
2
```

## 样例 #2

### 输入

```
otto
```

### 输出

```
1
```

## 样例 #3

### 输入

```
qqqq
```

### 输出

```
Impossible
```

## 样例 #4

### 输入

```
kinnikkinnik
```

### 输出

```
1
```

# 题解

## 作者：Celtic (赞：6)

先考虑`Impossible`的情况。

显然如果所有字符全一样那肯定无解。

还有一种情况就是 $n$ 为奇数且除了中间的一个字符其余全部相等，也无解。

理由很简单，剩下的字符全相等，由于新串是回文的，所以和原来的串一定是同一个串。

下面我们分奇偶性来讨论。

-  $n$ 为奇数

这种情况下，答案不大于 $2$ ，因为除了中间的旁边的字符不全相等，所以一定有中间的一段，他的两边不是回文串，直接切两下就行了。

同时，答案也不可能小于 $2$ ，因为如果一刀就行的话，由于新串回文，且长度为奇数，所以手动模拟一下就能看出，这样一定所有字符都相等才能让新串和原串全都回文，而这时答案为`Impossible`，不符合题意。

所以当 $n$ 为奇数时，答案为 $2$ 。

-  $n$ 为偶数

这时稍微麻烦一点，分两种情况。

我们取串的前一半，由于是回文长度为偶数的串，所以后一半一样的不用管就可以了。
1. 取出的这个串不是回文串，这时直接一刀把原串从中间分成两段即可，答案为 $1$ 。
1. 取出的串是回文串，这样我们可以把整个原串分成两半，因为这一半回文，所以求出当串长为 $\frac{n}{2}$ 时的答案。如果是 $2$ 就对称的切一刀，原串答案仍为 $2$ 。如果是 $1$ 就还在那个位置切，原串答案仍为 $1$ 。所以新串的答案即为原串的答案，递归处理即可。

时间复杂度 $O(n\log n)$ 。

代码

```cpp
#include<bits/stdc++.h>
#define re register
#define N 1001001
#define MAX 2001
#define inf 1e18
using namespace std;
typedef long long ll;
typedef double db;
inline void read(re ll &ret)
{
    ret=0;re ll pd=0;re char c=getchar();
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
    ret=pd?-ret:ret;
    return;
}
ll t,n;
char s[N];
signed main()
{
    t=1;
    while(t--)
    {
        scanf("%s",s+1);
        n=strlen(s+1);
        re bool flag=true;
        for(re int i=2;i<=(n>>1);i++)
            flag&=(s[i]==s[i-1]);
        if(flag)
        {
            puts("Impossible");
            continue;
        }
start:
        flag=true;
        for(re int i=1;(i<<1)<=n;i++)
        {
            if(s[(n>>1)-i+1]!=s[i])
                flag=false;
        }
        if(!flag&&(n&1))
        {
            puts("2");
            continue;
        }
        else if(!flag&&!(n&1))
        {
            puts("1");
            continue;
        }
        else if(flag&&(n&1))
        {
            puts("2");
            continue;
        }
        else if(flag&&!(n&1))
        {
            n>>=1;
            goto start;//即为前文所说的递归，goto简化代码
        }
 
    }
	exit(0);
}
```


---

## 作者：CaiXY06 (赞：4)

看到大家都是采用分奇偶分类讨论的方法，那我就来一篇不一样的题解吧。

答案只有三种情况，Impossible，$1$ 或者 $2$。

先考虑 Impossible 的情况：如果该回文串内全是同一个字母（如果字符串长度为奇数不包括最中间的字符），那么必定无解。因为你所有字符相同（若长度为奇数，中心的字符显然不能移动）无论如何都找不出与原串不同的方案。

由于给定的是回文串，除去 Impossible 的情况，那么左右两端肯定会存在两种不同的字母，我们一定可以由外向内的前缀（或后缀）中找到一个由两段不同字母组成的串，交换位置之后产生的串必然与原串不同。所以答案不会超过 $2$。

我们最后考虑只分成两段的情况。我们可以暴力枚举断点，将两段字符串颠倒位置后重新拼接。然后再继续判断该新串是否回文，我们可以将该串倒置，与原新串进行比较，如果相同那么回文，反之则不然。以上这些部分都可以用 **Hash** 解决，时间复杂度为 $O(n)$。

但是如果我们因转来转去麻烦而不想写 **Hash** 该怎么办？

可以观察到字符串的长度不超过 $5000$，显然 $O(n^2)$ 的算法是可以接受的。那么我们就可以使用 **STL** 中的 **string** 以及它的库函数 **substr** 来解决问题（懒人专属且 **string** 的内部重定义运算常数大，都需产生新串来运算，运算复杂度为 $O(|s|)$ 的，数据量一大就 **GG** 了，所以不推荐，所以还是建议写 **Hash**）。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,res;
string s,S,T;
int main(){
	std::ios::sync_with_stdio(0);cin.tie(0);
	cin>>s;n=s.size();
	for(int i=0;i<n>>1;i++)res+=(s[i]!=s[0]);
	if(!res)return puts("Impossible"),0;//判断无解
	for(int i=1;i<=n>>1;i++){
		T=s.substr(i,n)+s.substr(0,i);//获得新串
		S=T;reverse(S.begin(),S.end());//翻转新串
		if(S==T&&S!=s)return puts("1"),0;//判断是否回文，且是否与原串一致
	}
	puts("2");
	return 0;
}
```






---

## 作者：Imitators (赞：2)

先说无解情况
1. 奇回文串时，左右两端的串的字符都相等
2. 偶回文串时，整个串的字符都相等

除了无解情况，对于这个题，我们可以考虑有三种情况。

我们设这个回文串叫做`s`,其长度为`l`。

---

第一种：奇回文串

有结论，这时必须要切分`2`次。

证明如下：

那么如果我们要选择切掉串`A`。

![](https://cdn.luogu.com.cn/upload/image_hosting/cod553ox.png)

那么由于一共有两个对称中心，那么左右对称的操作会一直持续下去。

又因为这个奇回文串是有对称中心的，所以这样下去一定会使得整个串都是`A`串，有由于`A`串会有重叠，导致整个串都是一个字符，此时归于无解情况。

而我们可以从左右找出第一个不是回文的地方，然后切断，再交换就是一种合法情况。

当然由于左右并不是全部相同，所以一定存在可以切分的地方。

---
第二种 偶回文串，且两边的子串不是回文

有结论此时只需要切分`1`次。

直接从对称轴那里切开，再交换，由于左右字串不是回文串所以一定是相异的串。

---
第二种 偶回文串，且两边的子串都是回文

有结论，此时的答案等于该串从中点切开两端串的答案。

我们可以发现，我们最后一定是一堆"全等"的子串。

![](https://cdn.luogu.com.cn/upload/image_hosting/9ge1viwo.png)

如图，我们发现只要我们子串只要能够被切开，那么整个回文串也可以被切出来。

而对称中心的位置也恰好移动到了那个子串的切割处，由于每个子串都是回文串。

我们不难发现，现在的的串就是新的回文串。

$\text{code}$
``` cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300000;
char s[N];
int t;
inline int cmp(char *s,int l)
{
    bool f=1;
    int mid=l/2;
    for(int i=1,j=mid;i<=mid;i++,j--)
    {
        if(s[i]!=s[j])
        {
            f=0;
            break;
        }
    }
    if(f==1&&l%2==1) return 2;
    if(f==1) return  cmp(s,mid);
    if(!f&&(l%2==1))
        return 2;
    return 1;
}
int main()
{
    t=1;
    while(t--)
    {
        scanf("%s",s+1);
        int n=strlen(s+1);
        int l=n;
        if(l%2==1)
        {
            int mid=l/2;
            bool f=1;
            for(int i=1,j=mid;i<=mid;i++)
            {
                if(s[i]!=s[1])
                {
                    f=0;
                    break;
                }
            }
            if(f) puts("Impossible");
            else puts("2");
            continue;
        }
        bool f=1;
        int mid=l/2;
        for(int i=1,j=mid;i<=mid;i++,j--)
        {
            if(s[i]!=s[1])
            {
                f=0;
                break;
            }
        }
        if(f==1) {puts("Impossible");continue;}
        int k=cmp(s,n);
        if(k==0) puts("Impossible");
        else cout<<k<<endl;
    }
}

```

---

## 作者：decoqwq (赞：2)

这题真正证明我不会啊QAQ找规律做的

还是说说qwq

首先答案要么是$1$要么是$2$要么$Impossible$

感性理解下就好

长度为奇数的时候很方便，但是偶数就很麻烦了

一开始的思路是和奇数一样，判断前一半的字符串是不是回文的就可以了，但是会发现过不了样例

考虑到偶数个可以拆分成很多个小的回文串，对于一个长度为$k\times 2^m(1\leq m)$的回文串，可以拆成$k$个子串来组合

所以只要每次将判断长度除以二来看是否是回文串，直到其为奇数长度

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[5010],p[5010];
int main()
{
    cin>>s;
    int k=strlen(s);
    if(k&1)
    {
        int flag=0;
        for(int i=1;i<(k>>1);i++)
        {
            if(s[i]!=s[i-1])
            {
                flag=1;
                break;
            }
        }
        if(!flag)
        {
            cout<<"Impossible";
            return 0;
        }
        cout<<2;
        return 0;
    }
    else
    {
        int flag=0;
        for(int i=1;i<=(k>>1);i++)
        {
            if(s[i]!=s[i-1])
            {
                flag=1;
                break;
            }
        }
        if(!flag)
        {
            cout<<"Impossible";
            return 0;
        }
        for(int i=0;i<k;i++)
        {
            p[i]=s[i];
        }
        int flags=0;
        for(int m=k;(m%2==0)&&m>0;m>>=1)
        {
            reverse(s,s+(m>>1));
            if(strcmp(s,p)!=0)
            {
                flags=1;
                break;
            }
            reverse(s,s+(m>>1));
        }
        if(flags)
        {
            cout<<1;
        }
        else
        {
            cout<<2;
        }
    }
}
```

---

## 作者：CarrotMeow (赞：1)

分讨。设 $n \gets |s|$ 且 $\operatorname{rev}(s)$ 为 $s$ 的逆序串。

- 首先，当 $n \leq 3$ 或 $s_i$ 全部相同时显然无解。

- 当 $2 \mid n$：

	- 若能找到一个下标 $i$ 满足 $s_{1 \ldots i} = \operatorname{rev}(s_{i + 1 \ldots 2i})$，即可将切割一次，将 $s$ 分割成 $s_{1 \ldots i}, s_{i + 1 \ldots n}$ 两部分。显然 $s_{i + 1 \ldots n} + s_{1 \ldots i}$ 为回文串。
    
		特别地，若 $s_{1 \ldots i}$ 本身为回文串，重新拼接后的新串不变，则无法从此处切割。

- 当 $2 \nmid n$：

	- 若除了 $i = \lfloor n \div 2 \rfloor$（即正中间）以外的 $a_i$ 全部相同，则无解。由于正中间的字符与其他字符不同，则其位置不可以移动，而其他位置的字符无论怎样移动，构造出的新串都与原串相同。

- 否则，可以切两刀解决。选择一个不为回文串的前缀 $s_{1 \ldots i}$，分割成 $s_{1 \ldots i}, s_{i + 1 \ldots n - i}, s_{n - i + 1 \ldots n}$ 三个部分。显然 $s_{n - i + 1 \ldots n} + s_{i + 1 \ldots n - i} + s_{1 \ldots i}$ 为回文串。

---

## 作者：zac2010 (赞：1)

我们对数据进行观察/分析归纳，易得出要么 $k\leq 2$，要么无解。

采用构造法证明：

先排除无解的情况：若 $s$ 为偶回文，那么所有字符相等必定无解；若为奇回文，则除去中心字符以外的所有字符相等时无解。

对于剩下的情况，从前往后找到第一个与 $s_1$ 不同的字符（下标从 $1$ 开始），设它处于位置 $i$。接下来考虑把花两次把字符串分成 $3$ 个部分：$[1,i],[i+1,n-i],[n-i+1,n]$。交换第一个和第三个部分，便是一种合法的方案。这种方案 $k=2$。

但在有些情况下答案是否可能为 $1$？答案是肯定的。当 $k=1$ 时我们不妨枚举唯一的一刀切在哪里，然后判断是否为回文以及和原串是否相等即可。

判断是否相等可以使用字符串哈希。

时间复杂度线性。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
const ll base = 27, p = 2654404609;
int n; ll s[2][N], pw[N];
char str[N];
ll ch(int l, int r, int t){
	if(!t) return (s[0][r] - s[0][l - 1] * pw[r - l + 1] % p + p) % p;
	return (s[1][l] - s[1][r + 1] * pw[r - l + 1] % p + p) % p;
}
int main(){
	scanf("%s", str + 1), n = strlen(str + 1), pw[0] = 1; 
	FL(i, 1, n) pw[i] = pw[i - 1] * base % p;
	FL(i, 1, n) s[0][i] = s[0][i - 1] * base % p + (str[i] - 'a');
	FR(i, n, 1) s[1][i] = s[1][i + 1] * base % p + (str[i] - 'a');
	FL(i, 2, n){
		ll z = (ch(i, n, 0) * pw[i - 1] + ch(1, i - 1, 0)) % p;
		ll f = (ch(1, i - 1, 1) * pw[n - i + 1] + ch(i, n, 1)) % p;
		if(z == ch(1, n, 0) || z != f) continue;
		printf("1\n"); return 0;
	}
	FL(i, 2, n / 2) if(str[i] != str[1]){
		printf("2\n"); return 0;
	}
	printf("Impossible\n");
	return 0;
} 
```


---

## 作者：fish_love_cat (赞：0)

非常巧妙的题。

---

首先可以发现，当整个字符串完全相同时，无论怎么移动都不会改变。这样是无解的。

还可以发现，如果 $|s|$ 是奇数，那么除了中间的一个字符其余全部相等时，因为要移动后仍然回文，所以中间的那一个字符必定不能动，那么无论怎么移动都不会改变。这样也是无解的。

除去无解的情况，我们可以分奇偶性进行讨论。

当 $|s|$ 是奇数时，我们可以用两刀把 $s$ 分为 $s_{1 \sim \left \lfloor \frac{|s|}{2} \right \rfloor },s_{\left \lceil \frac{|s|}{2} \right \rceil},s_{(\left \lceil \frac{|s|}{2} \right \rceil +1)\sim |s|}$ 三段，然后交换第一段和第三段，根据回文的性质，可以知道交换后的串一定也是回文串。而且由于第一段和第三段不相等（相等无解），可以知道交换后的串一定不是原来的串。此时答案为 $2$。

当 $|s|$ 是偶数时，我们把 $s$ 分为两半，取其中前面的一半 $s'$ 进行分类讨论。

当 $s'$ 不是回文串时，我们可以切一刀把 $s'$ 放到后面，这样的构造是正确的。此时答案为 $1$。

当 $|s'|$ 是奇数时，因为原串 $s$ 是回文串，所以 $s_{i \sim (|s'|-i+1)}$ 也是回文串，那么我们就可以在首尾各砍一刀，取两段长度相等但不相同的串交换，这样的构造是正确的。此时答案为 $2$（首尾各一刀）。

可以发现新串的答案即为原串的答案，原串的其他部分保证了有解，但不影响答案。

剩下的情况 $s'$ 是回文串且长度为偶数，我们可以考虑使用递归求解。

然后你就过了一道 *1800 的题。

---

[代码](https://www.luogu.com.cn/paste/6hht2ucb)。

[CF AC 记录](https://codeforces.com/contest/1109/submission/276075985)。

为什么是 CF？

我想 RMJ 大抵是[似了](https://www.luogu.com.cn/discuss/598533)，所以洛谷这里目前没有 AC 记录，先这样。

---

## 作者：cosf (赞：0)

## [CF1109B](https://codeforces.com/problemset/problem/1109/B)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1109B)

---

看到大家都用哈希，那我就提供一个和哈希无关的算法：`Manacher + KMP`。

## 思路

和大家一样，容易发现答案只能是 `Impossible` 或 $1$ 或 $2$，其中 `Impossible` 是当这个字符串形如 `aa...aba...aa` 的时候。

那么重点就是判断是 $1$ 还是 $2$。我们来讨论答案是 $1$ 的情况。

假设原来的字符串为 $s_0s_1s_2\dots s_{len - 1}$，其中分界点（可行的当中最小的那个）为 $i$，即转换后的字符串为 $s_{i+1}s_{i+2}\dots s_{len - 1}s_0s_1\dots s_i$。

首先可以证明，$2i + 1 \lt len$。事实上，如果 $2i+1 = len$ 的话，$i$ 就是 $s$ 的正中间的那个字符，根据定义，可以发现这种情况是属于 `Impossible` 的。而当 $2i+1 \gt len$ 时，取 $i' = len - i - 1$，可以发现 $i'$ 同样满足，与 $i$ 最小矛盾。

我们令 $R(p)$ 表示字符串 $p$ 翻转过后的字符串。~~显然有 $\sout{R(s)=s}$。~~

那么，交换过后的 $s$，即 $s_{i+1}s_{i+2}\dots s_{len - 1}s_0s_1\dots s_i$，可以划分为三个段落：

$$
s_{i+1}\dots s_{2i + 1} | s_{2i + 2}\dots s_{len - 1} | s_0\dots s_i
$$

根据回文串定义，有 $R(s_{i+1}\dots s_{2i + 1}) = s_0\dots s_i$，而且有 $R(s_{2i + 2}\dots s_{len - 1})=s_{2i + 2}\dots s_{len - 1}$。放回原来的 $s$ 中可以发现，$s_0\dots s_{2i+1}$ 是一个长度为偶数的回文串，$s_{2i+2}\dots s_{len - 1}$ 是一个回文串。

那么，答案为 $1$ 的情况即 $s$ 可以被划为一个长度为偶数的回文串在前，和一个回文串在后。这一块用 `Manacher`。

不过，需要判断是否有 $s_{i+1}\dots s_{len - 1} = s_{0}\dots s_{len - i - 2}$，因为这个时候交换后的字符串就和原来的 $s$ 一样了，需要特判。当然，还需要判断 $s_0\dots s_i$ 是否和 $s_{len - i - 1}\dots s_{len - 1}$ 相等。这一块可以用 `KMP`。

理论复杂度 $O(n^2)$，不过常数极小，近似于 $O(n)$。

## 代码

```cpp
#include <iostream>
using namespace std;

#define MAXL 20026 // 这个开大了，只要是 10005 应该就可以了

int rar[MAXL];
int rad[MAXL];
int kmp[MAXL];
char str[MAXL];
string s;

inline bool chkpre(int l, int p) // 判断是否为前缀
{
    while (l > p)
    {
        l = kmp[l] - 1;
    }
    return l == p;
}

int main()
{
    cin >> s;
    int len = s.length();
    int e = 1;
    for (int i = 0; i * 2 < len - 3; i++)
    {
        if (s[i] != s[i + 1])
        {
            e = 0;
            break;
        }
    }
    if (e)
    {
        cout << "Impossible" << endl;
        return 0;
    }
    // KMP
    kmp[0] = 0;
    for (int i = 1; i < len; i++)
    {
        int j = kmp[i - 1];
        while (j > 0 && s[i] != s[j])
        {
            j = kmp[j - 1];
        }
        if (s[i] == s[j])
        {
            j++;
        }
        kmp[i] = j;
    }
    // Manacher
    int c = 0;
    for (int i = 0; i < len - 1; i++)
    {
        str[c++] = s[i];
        str[c++] = '#';
    }
    str[c++] = s[len - 1];
    int l = 0, r = -1;
    for (int i = 0; i < len; i++)
    {
        int k = (i > r) ? 0 : min(rar[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < len && s[i - k - 1] == s[i + k])
        {
            k++;
        }
        rar[i] = k--;
        if (i + k > r)
        {
            l = i + k - 1;
            r = i + k;
        }
    }
    l = 0;
    r = -1;
    for (int i = 0; i < c; i++)
    {
        int k = (i > r) ? 1 : min(rad[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < c && str[i - k] == str[i + k])
        {
            k++;
        }
        rad[i] = k--;
        if (i + k > r)
        {
            l = i - k;
            r = i + k;
        }
    }
    /*
     * 为 1 的情况
     *     l            r
     * |-------|.......|----------|
     *  ->
     * |......./----------|-------|
     *
     * |.......|----------|-------|
     */
    for (int i = 0; 2 * i + 1 < len; i++)
    {
        int t = (c - (4 * i + 3)) / 2;
        if (rar[i + 1] == i + 1 && rad[c - t] == t && !chkpre(len - 1, len - i - 2) && !chkpre(len - 1, i))
        {
            e = 1;
            break;
        }
    }
    if (e)
    {
        cout << 1 << endl;
        return 0;
    }
    cout << 2 << endl;
    return 0;
}

```


---

## 作者：FreedomKing (赞：0)

### 题目大意

给定一个**回文串**，问最少能将它劈 $k$ 刀使得这 $k+1$ 个子串可以通过排序获得一个不同于原串的回文串。

### 思路

不难发现，对于这每个字符串 $s$ 只有 $3$ 种答案，分别是 $1,2$ 和 Impossible，直接考虑分类讨论。

- 当 $s$ 的每个元素都相等或只有中间的元素不同，无解，输出 Impossible。

- 当 $\left|s\right|$ 为奇数且有解时，一定可以在中点两边的一对对称点切开，输出 $2$。

- 当 $\left|s\right|$ 为偶数且有解时，枚举每个 $1$ 次操作的点，判断是否存在，如果存在输出 $1$，否则输出 $2$。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int a[N],n,m,t,k;
bool flag;
char s[N],ss[N];
int main(){
	cin>>s;
	int len=strlen(s);
	n=len>>1;
	for(int i=0;i<n;i++)
		if(s[i]!=s[0])
			flag=true;
	if(!flag){
		cout<<"Impossible";
		return 0;
	}
	if(len&1){
		cout<<'2';
		return 0;
	}
	for(int i=0;i<len;i++) ss[i]=s[i];
	for(int i=len;i>0&&(!(i&1));i>>=1){
		reverse(ss,ss+(i>>1));
		if(strcmp(s,ss)!=0){
			cout<<'1';
			return 0;
		}
		reverse(ss,ss+(i>>1));
	}
	cout<<'2';
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

Update on 8.5：经大佬提醒，修改一处笔误。

**分析**



~~俗话说，“不可以，总司令”，所以~~我们先考虑输出 `Impossible` 的情况，假如一个串从第一位到最中间的前一位都是一个字母，那么不管怎么切，都不可能产生不同的回文串，所以 `Impossible`。

接下来证明一点，没有输出 `Impossible` 的情况一定是可以在 $2$ 刀内解决的。我们找到串中与第一个字符不相等的字符位置，设其为 $i$，则把字符串切成 $[1,i],[i+1,n-i],[n-i+1,n]$（其中 $n$ 为串长），然后按照 $[n-i+1,n]+[i+1,n-i]+[1,i]$ 的方式拼接即可。最后假如 $i+1=n-i$，则只需要 $1$ 刀，枚举 $i$ 即可。

注意到 $O(n^2)$ 复杂度可通过此题，考虑使用 `substr` 函数来切字符串，然后丢到手写判回文函数里面，再与原串对比即可。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int pal(string s)//判回文
{
	for(int i=0;i<s.size();i++) if(s[i]!=s[s.size()-i-1]) return 0;
	return 1;
} 
int main()
{
	int cnt=0;
	string s,t;//s为原串，t为切完重组的串
	cin>>s;
	for(int i=0;i<s.size()/2;i++) 
	if(s[i]!=s[0]) cnt++;
	if(!cnt)
	{
		cout<<"Impossible";
		return 0;
	}
	for(int i=1;i<=s.size()/2;i++)//判断能不能一刀
	{
		t=s.substr(i,s.size())+s.substr(0,i);//重组
		if(pal(t)&&s!=t)//回文且不与原串相等
		{
			cout<<1;
			return 0;
		}
	}
	cout<<2;//不能1刀，最多2刀
	return 0;
}

---

## 作者：柳易辰 (赞：0)

## 结论

简单观察后，直接~~扔~~猜出一个结论：答案只有 `Impossible`，$1$ 或者 $2$。

## 证明

于是我们尝试证明这个结论。设字符串长度为 $l$，并令 $t=\lceil\frac l 2\rceil$。

直接证比较难，但是我们可以发现判定 `Impossible` 是比较简单的，大致有两种情况。

1. 全部都是同一个字母，比较显然。
2. $l$ 为奇数，并且除了 $s_{t}$ 之外，其余字母都相同。这样的话这个字母一定放在中间，所以无论怎么换，一共就一种可能的回文串，即原串。

于是，我们在判断完 `Impossible` 之后，发现剩下的 $s$ 都是有解的，于是我们发现 $s$ 一定满足一个性质：总是存在至少两个 $i\ (1\leqslant i<t)$ 满足 $s_i\neq s_{i+1}$。并且容易发现 $l\geqslant 4$。

为什么满足此性质？因为如果不满足此性质的字符串都是 `Impossible` 的。

现在我们来证明需要的切分次数不多于 $2$：

根据上面的性质，我们可以找到第二个 $j$ 使 $1\leqslant j<t$，我们将 $s$ 划分成 $1\sim j+1,\ j+1\sim l-j-1,\ l-j\sim l$ 三段。

由于 $s$ 为回文串，并且第一段与第三段长度相等的。在第一段中，除了最后一个字符之外，其余均相等；在第三段中，除了第一个字符外，其余均相等。又 $s_1=s_l,s_{j+1}=s_{l-j}$，所以第一段和第三段不相等。因此交换后，新串与原串不相等。

交换第一段和第三段之后，由于原串的回文性质，第二段是回文串，第一段和第三段正好是互相翻转的结果，所以新串也是回文串。

于是，只要按此方法交换，切分次数一定不多于 $2$，证毕。

## 思路

先判断 `Impossible`，很简单，从 $1$ 扫到 $t$ 即可。

其次，已经证明答案是 $1$ 或 $2$。由于需要最小值，不难发现更重要的是判断 $1$ 可不可行。

实际上这是很简单的，我们枚举在哪里切分即可，对于每次切分，直接暴力交换与判断回文，观察到 $l\leqslant 5000$，这样做是 $l^2$ 的，可以通过。

如果枚举完之后没有可行的，说明 $1$ 次切分不能满足，输出 $2$ 即可。

## 代码

```C++
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
string s; bool d;
int main()
{
    cin >> s; const int l(s.size()); s = ' ' + s; // 下标从 1 开始，方便处理
    for (int i(2); i <= l >> 1; ++i) if (s[i] != s[1]) { d = true; break; }
    if (!d) { puts("Impossible"); return 0; } // 不可行
    for (int i(1); i <= l >> 1; ++i) {
        const string t(s.substr(i + 1) + s.substr(1, i));        // 交换
        string r(t); reverse(r.begin(), r.end());                // 翻转
        if (s.substr(1) != t && r == t) { puts("1"); return 0; } // 判断
    } puts("2"); return 0;
}
```

---

