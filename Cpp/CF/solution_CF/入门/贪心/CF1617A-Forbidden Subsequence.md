# Forbidden Subsequence

## 题目描述

You are given strings $ S $ and $ T $ , consisting of lowercase English letters. It is guaranteed that $ T $ is a permutation of the string abc.

Find string $ S' $ , the lexicographically smallest permutation of $ S $ such that $ T $ is not a subsequence of $ S' $ .

String $ a $ is a permutation of string $ b $ if the number of occurrences of each distinct character is the same in both strings.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) elements.

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

In the first test case, both aaaabbc and aaaabcb are lexicographically smaller than aaaacbb, but they contain abc as a subsequence.

In the second test case, abccc is the smallest permutation of cccba and does not contain acb as a subsequence.

In the third test case, bcdis is the smallest permutation of dbsic and does not contain bac as a subsequence.

## 样例 #1

### 输入

```
7
abacaba
abc
cccba
acb
dbsic
bac
abracadabra
abc
dddddddddddd
cba
bbc
abc
ac
abc```

### 输出

```
aaaacbb
abccc
bcdis
aaaaacbbdrr
dddddddddddd
bbc
ac```

# 题解

## 作者：ForeverCC (赞：2)

因为要输出字典序最小的那一个，所以先想到把 $S$ 排成字典序中最小的那种，形式为 `a...b...c...`。

在考虑 $t$ 为 `abc` 的情况 `abc` 是 `a...b...c...` 的子序列，这时只要把 `b` 和 `c` 的数量和顺序交换即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt[26];
char s[105],t[105];
int main(){
    scanf("%d",&n);
    while(n--){
    	memset(cnt,0,sizeof(cnt));
    	scanf("%s%s",s,t);
    	for(int i=0;s[i];i++)
    		cnt[s[i]-'a']++;//统计数量 
    	if(t[0]=='a'&&t[1]=='b'&&t[2]=='c'&&cnt[0]&&cnt[1]&&cnt[2]){//判断特殊情况 
    		swap(cnt[1],cnt[2]);
    		for(int i=0;i<26;i++)
				for(int j=1;j<=cnt[i];j++)
					if(i==1)printf("c");
					else if(i==2)printf("b");
					else printf("%c",'a'+i);
		}else
			for(int i=0;i<26;i++)
				for(int j=1;j<=cnt[i];j++)
					printf("%c",'a'+i);
		puts("");
	}
    return 0;
}
```


---

## 作者：Eason_AC (赞：2)

## Content
给定两个仅包含小写字母的字符串 $S$ 和 $T$，保证 $T$ 仅包含 `a`、`b`、`c` 且这三个小写字母都出现且仅出现一次。现重新排列字符串 $S$，记重新排列之后的字符串为 $S'$，我们希望 $T$ 不是 $S'$ 的子序列。请你求出重新排列之后满足该要求的字符串 $S'$，如果满足要求的 $S'$ 有多个，输出字典序最小的那一个。

**数据范围：$t$ 组数据，$1\leqslant t\leqslant 1000$，$1\leqslant |S|\leqslant 100$，$|T|=3$。**
## Solution
我们不难发现，重新排列 $S$ 时，先放所有的 `a`，再放所有的 `b`，再放所有的 `c`，……，最后得到的字符串 $S'$，在大多数情况下都满足要求且是在所有满足要求的当中字典序最小的。那么在什么情况下不是的呢？仅在 $T=\texttt{abc}$，且 `a`、`b`、`c` 都出现在 $S$ 中的时候，这时该怎么办呢？只需要改变一个地方，就是在放的时候把 `b`、`c` 放的顺序调换一下就可以了。
## Code
```cpp
namespace Solution {
	iv Main() {
		MT {
			string a, b; cin >> a >> b;
			sort(a.begin(), a.end());
			if(b != "abc" || (b == "abc" && (a.find("a") != string :: npos) + (a.find("b") != string :: npos) + (a.find("c") != string :: npos) != 3)) cout << a << endl;
			else {
				string ans = "";
				F(int, i, 0, (int)a.size() - 1) if(a[i] == 'a') ans += a[i];
				F(int, i, 0, (int)a.size() - 1) if(a[i] == 'c') ans += a[i];
				F(int, i, 0, (int)a.size() - 1) if(a[i] == 'b') ans += a[i];
				F(int, i, 0, (int)a.size() - 1) if(a[i] != 'a' && a[i] != 'b' && a[i] != 'c') ans += a[i];
				cout << ans << endl;
			}
		}
		return;
	}
}
```

---

## 作者：rainygame (赞：1)

**STL 大法好！**

将 $s$ 排序即可解决一部分问题（也就是把 $s$ 改成 $\texttt{a\dots b\dots c\dots}$ 的形式），但是当 $t=\texttt{abc}$ 的时候，就不能解决了。

所以，我们需要把 $\texttt{b}$ 和 $\texttt{c}$ 的位置对调。

我们可以先排序，再对调。

而排序就可以用到 `std::sort` 对 `std::string` 简便的进行排序。

当然，有一个问题，就是当 $s$ 中没有 $\texttt{a}$ 的时候，就不需要对调了。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define for1(i, s, t) for (int i(s); i<=t; ++i)
#define for2(i, t, s) for (int i(t); i>=s; --i)
#define for3(i, vec) for (auto i: vec)
#define INF 0x3f3f3f3f
#define opb pop_back
#define pb push_back
#define pf push_front
#define opf pop_front
#define fi first
#define se second
#define space putchar(' ')
#define eoln putchar('\n')
#define pc(x) putchar(x)
#define err assert(0);
//const int MAXN(1e5);
//const ll MOD(1e9+7);

ll read(){
	ll x(0), f(1);
	char ch;
	while ((ch = getchar()) < 48) f = ch == '-' ? -1 : 1;
	do{
		x = (x << 1) + (x << 3) + (ch ^ 48);
	}while ((ch = getchar()) > 47);
	return x * f;
}

void uwrite(ll x){
	ll tmp(x/10);
	if (tmp) uwrite(tmp);
	putchar(x-(tmp<<1)-(tmp<<3)^48);
}

void write(ll x){
	if (x < 0){
		putchar('-');
		x = -x;
	}
	uwrite(x);
}

int cnt[2];
string t, s;

void solve(){
	cin >> s >> t;
	sort(s.begin(), s.end());
	if (t == "abc" && s[0] == 'a'){  // 判断是否需要对调
		for3(i, s){
			if (i == 'a') pc('a');  // 先输出 a
			else if (i <= 'c') ++cnt[i-'b'];  // 记录数量
			else break;  // 否则就退出
		}
		
		while (cnt[1]){  // 输出 c
			pc('c');
			--cnt[1];
		}
		while (cnt[0]){  // 再输出 b
			pc('b');
			--cnt[0];
		}
		for3(i, s){  // 最后输出其它字符
			if (i > 'c') pc(i);
		}
	}else cout << s;
}

int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);

	int t(1);
	t = read();
	while (t--){
		solve();
		putchar('\n');
	}

	return 0;
}

```


---

## 作者：cyz_czy (赞：0)

## 题目大意
给定两个仅包含小写字母的字符串 $S$ 和 $T$，保证 $T$ 仅包含 `a`、`b`、`c` 且这三个小写字母都出现且仅出现一次。现重新排列字符串 $S$，记重新排列之后的字符串为 $S'$，我们希望 $T$ 不是 $S'$ 的子序列。请你求出重新排列之后满足该要求的字符串 $S'$，如果满足要求的 $S'$ 有多个，输出字典序最小的那一个。

## 具体思路
看到字典序最小，我们就先将 $S$ 排成最小的一种，分成三段，第一段全是 $a$，第二段全是 $b$，第三段全是 $c$。

然后我们再判断当字符串 $T$ 是 $abc$ 的时候，我们将 $b$ 与 $c$ 的子串长度与顺序交换即可；若字符串 $T$ 不是 $abc$ 的时候，那么 $T$ 就不会是 $S'$ 的字串。

## Code:

```cpp
#include <iostream>

#include <algorithm>
#include <cstring>
#include <cmath>

#include <set>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <deque>

/*
#define int long long
*/

#define reint register int

inline int read();//快读

const int N=3e2;

int l[N];
std::string a,b;

int T;

bool pd(){
	return b[0]=='a'&&b[1]=='b'&&b[2]=='c'&&l[0]&&l[1]&&l[2];//思路中所说的 abc情况
    //同时要保证S中a，b，c三个字符都有
}

signed main(){
	T=read();
	
	while(T--){
		memset(l,0,sizeof(l));
		
		std::cin>>a>>b;
		
		for(reint i=0;a[i];i++)
			l[a[i]-'a']++;//将a的个数储存在l[0]中，把b的个数储存在l[1]中，把c的个数储存在l[2]中，将S排成了字典序最小的情况
		
		if(pd()){//若T是abc
			std::swap(l[1],l[2]);
			for(reint i=0;i<26;i++)
				for(reint j=1;j<=l[i];j++){
					
					if(i==1)
						printf("c");
					if(i==2)
						printf("b");
              //调换顺序          
					if(i>2||i==0)
						printf("%c",'a'+i);//其余照常
				}
		}
		
		else//若不是直接输出
			for(reint i=0;i<26;i++)
				for(reint j=1;j<=l[i];j++)
					printf("%c",'a'+i);
		
	//	printf("\n");
		putchar('\n');//别忘了换行
	}
	
	return 0;
}

inline int read(){
    int x=0,f=1;
    char ch=getchar();

    while(ch<'0'||ch>'9'){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}

    while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}

    return x*f;
}

```

[AC 记录](https://www.luogu.com.cn/record/112741357)

---

## 作者：奥斯卡小冰人 (赞：0)

[$\color{blue}\textsf{CF1617A}$](https://www.luogu.com.cn/problem/CF1617A)

## 题意简述

给出两个字符串 $s$ 和 $t$，求出字典序最小的 $s$ 的排列且满足 $t$ 不是这个排列的子序列。

保证 $t$ 是 abc 的一个排列。

## 思路

先将 $s$ 进行排序。首先因为 $t$ 是 abc 的一个排列，那么如果 $s$ 中根本没有出现 a、b、c 其中一个字母，$t$ 就肯定不是 $s$ 的一个子序列了，直接输出排序后的 $s$ 即可。


之后，我们发现如果 $t$ 是 $s$ 的子序列，那么改变 b 和 c 这两个字母的字典序是最小的。举个例子 :

$s$ 为 ```abc```，

$t$ 为 ```abc```。

显然 ```acb``` 的字典序要比 ```bac``` 更小。

所以，在 $t$ 为$s$ 的情况下，修改 b 和 c的字典序最小。


AC code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        string s,t;
        cin >> s >> t;
        sort(s.begin(),s.end());
        int k1 = t.find('a');// 查找t中相应的字符
        int k2 = t.find('b');
        int k3 = t.find('c');
        int p1,p2,p3;
        p1 = s.find('a');// 查找s中相应的字符
        p2 = s.find('b');
        p3 = s.find('c');
        if(p1 == -1||p2 == -1||p3 == -1) {cout << s << '\n';continue;}//如果没有出现a、b、c其中一个的话，就直接输出
        if(k2 < k3&&k1 < k2)//如果t为s的子序列
            while(s[p3] == 'c') 
                s.insert(p2,"c"),
                s.erase(p3 + 1,1),
                p3++;//修改b和c的顺序
        cout << s << '\n';
    }
    return 0;
}
```

---

