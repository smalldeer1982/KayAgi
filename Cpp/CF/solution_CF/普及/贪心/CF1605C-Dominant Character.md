# Dominant Character

## 题目描述

Ashish has a string $ s $ of length $ n $ containing only characters 'a', 'b' and 'c'.

He wants to find the length of the smallest substring, which satisfies the following conditions:

- Length of the substring is at least $ 2 $
- 'a' occurs strictly more times in this substring than 'b'
- 'a' occurs strictly more times in this substring than 'c'

Ashish is busy planning his next Codeforces round. Help him solve the problem.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

## 说明/提示

Consider the first test case. In the substring "aa", 'a' occurs twice, while 'b' and 'c' occur zero times. Since 'a' occurs strictly more times than 'b' and 'c', the substring "aa" satisfies the condition and the answer is $ 2 $ . The substring "a" also satisfies this condition, however its length is not at least $ 2 $ .

In the second test case, it can be shown that in none of the substrings of "cbabb" does 'a' occur strictly more times than 'b' and 'c' each.

In the third test case, "cacabccc", the length of the smallest substring that satisfies the conditions is $ 3 $ .

## 样例 #1

### 输入

```
3
2
aa
5
cbabb
8
cacabccc```

### 输出

```
2
-1
3```

# 题解

## 作者：zhaoyp (赞：9)

# Solution

不难发现选出的字符串中至少含有两个 `a` （如果只有 $1$ 个 `a`，由于选出长度要大于等于 $2$，那么必然还有至少一个 `b` 或 `c`）。

为方便说明，记两个字母 `a` 之间其它字母的数量为这两个字母 `a` 之间的距离。最小距离为字符串中字母 `a` 之间的距离的最小值。

例如：字符串 `cacabccc` 的最小距离为 $1$。

然后进行分类讨论：

1. 若最小距离为 $0$，则原字符串中一定含有字串 `aa` ，易知它满足条件，答案即为 $2$。

2. 若最小距离为 $1$，则原字符串中一定含有字串 `aba` 或 `aca` ，易知它满足条件，答案即为 $3$。

3. 若最小距离为 $2$，设最后选出的字符串为 `str`，那么 `str` 中的距离均为 $2$ 且 `str` 中字母 `b` 和字母 `c` 的数量相等 （证明 $1$ 附后）。

	- 若 `str` 中含有字串 `abca` 或 `acba` ，易知它满足条件，答案即为 $4$。
	- 否则所有距离为 $2$ 的 `a` 之间都是 `aa` 或 `bb`，那么只有字串 `abbacca` 或 `accabba` 才会满足条件，答案即为 $7$（其它更长的满足条件的字符串一定含有该字串）。
   - 如果无法找到字串  `abca` 或 `acba` 或 `abbacca` 或 `accabba`，答案即为 $-1$。

4. 若最小距离大于 $2$，无法找到满足条件的字串（上已证），答案即为 $-1$。

证明 $1$：设 `str` 中有 $x$ 个 `a`，那么 `str` 的长度至少为 $x + 2 * (x - 1) = 3 * x - 2$。由于 `a` 的数量要均大于 `b` 和 `c` 的数量，则所含 `b` 和 `c` 数量的最大值均为 $x - 1$，此时 `str` 长度为 $3 * x - 2$。若 `str` 中还有多余的 `b` 和 `c`，那么长度必然超过 $3 * x - 2$ ，不成立。

---

## 作者：Jerrlee✅ (赞：6)

## 题意
在含有 $a,b,c$ 的字符串中找一个子串，使得：

- 长度至少为 $2$ 且最短；

- $a$ 的数量大于 $b,c$ 的数量。

## 思路
1. 能满足 $aa$ 输出 $2$。

2. 能满足 $aba$ 或 $aca$ 输出 $3$。

3. 能满足 $abca$ 或 $acba$ 输出 $4$。

4. 能满足 $abbacca$ 或 $accabba$ 输出 $7$。

否则无法满足。
## 代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){ 
        int n;
        string s;
        cin>>n>>s; //n 用不到
        if(s.find("aa")!=string::npos) cout<<2<<endl;
        else if(s.find("aba")!=string::npos||s.find("aca")!=string::npos) cout<<3<<endl;
        else if(s.find("abca")!=string::npos||s.find("acba")!=string::npos) cout<<4<<endl;
        else if(s.find("abbacca")!=string::npos||s.find("accabba")!=string::npos) cout<<7<<endl;
        else cout<<-1<<endl;
   }
}
```
[AC记录（洛谷）](https://www.luogu.com.cn/record/62609609)

[AC记录（CF）](https://codeforces.com/contest/1605/submission/135172171)

---

## 作者：King_duck (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1605C)

这道题比较简单，我就来水一波题解。

首先来分析一下题意，其实它就是给出一个字符串，让你找出一个字串，并让它满足要求（满足 $a$ 的数量大于 $b$ 的数量和 $c$ 的数量）

接下来直接讲解一下我的思路。这道题可以用 
```
substr()
```
它用于截取子串。

```cpp
string a;
a.substr(int i,int n)
```
其中 $i$ 表示字符串中准备截取的开始位置，$n$ 表示截取长度，如果 $n$ 不写就代表从 $a_i$ 一直截取到字符串结尾。

这道题成立的情况不多，直接枚举。

1. "aa"
2. "aba"、"aca"
3. "abca"、"acba"
4. "abbacca"、"accabba"

枚举出情况后，直接用刚刚说的函数判断
```
substr（）
```
上代码。
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
long long n,m;
string str;
int main()
{
    cin>>n;
    while(n--)
	{
        cin>>m;
        cin>>str;
        long long x,minn=1e18;//定义在里面，每次循环后会回复原值 
        for(long long i=0;i<=m;i++)//正片开始 
		{
            if(str.substr(i,2)=="aa")
			{
				x=2;
				minn=min(minn,x);
			}
            if(str.substr(i,3)=="aba"||str.substr(i,3)=="aca") 
			{
				x=3;
				minn=min(minn,x);
			}
            if(str.substr(i,4)=="acba"||str.substr(i,4)=="abca") 
			{
				x=4;
				minn=min(minn,x); 
			}
            if(str.substr(i,7)=="abbacca"||str.substr(i,7)=="accabba") 
			{
				x=7;
				minn=min(minn,x); 
			}
        }
        if(minn==1e18)//minn=1e18时，说明它没变 
		{
			cout<<-1; 
		}
        else 
		{
			cout<<minn;
		}
        cout<<'\n';//换行 
    }
    return 0;//完美收尾 
}
```

---

## 作者：BLX32M_10 (赞：0)

手模可以发现发现最短的且 `a` 的数量比 `b` 或 `c` 的数量多的最短子串情况并不多：

+ `"aa"`
+ `"aba"`、`"aca"`
+ `"abca"`、`"acba"`
+ `"abbacca"`、`"accabba"`

于是我们可以以每一个字符为左端点，向后枚举右端点，看是否符合上述几种情况，记录所有情况长度的最小值即可。

AC 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
set <string> v;
int main()
{
    int t, n;
    string s;
    scanf("%d", &t);
    v.insert("aa");
    v.insert("aba");
    v.insert("aca");
    v.insert("abca");
    v.insert("acba");
    v.insert("abbacca");
    v.insert("accabba");
    while (t--)
    {
        scanf("%d", &n);
        cin >> s;
        int cnt = 0x3f3f3f3f;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == 'a')
                for (int j = 2; j <= 7; j++)
                    if (v.find(s.substr(i, j)) != v.end())
                        cnt = min(cnt, j);
        }
        if (cnt == 0x3f3f3f3f)
            printf("-1\n");
        else
            printf("%d\n", cnt);
    }
    return 0;
}
```

---

## 作者：_cpp (赞：0)

这题考察分类讨论。

### 思路：

逛了一圈题解区，发现大部分题解只是提到了 $\texttt {aa}$ 之间是什么情况，却没有详细介绍为什么只要讨论 $\texttt {aa}$ 之间的情况。首先，我们容易得到，长度为 $2$ 满足题目要求的字符串只有 $\texttt {aa}$ 一种可能，而且题目要求最短的子串。如果当前子串的长度大于 $2$，那么有 $\texttt{aba}$，$\texttt{aca}$，$\texttt{aab}$，$\texttt{aac}$，$\texttt{baa}$，$\texttt{caa}$ 这六种字符串满足要求。但我们发现最后四种都包含更小的字串 $\texttt{aa}$，以此类推，更长的字串也只要考虑首尾都是 $\texttt{a}$ 的情况即可。

分类讨论：

1. 长度为 $2$ 的：$\texttt{aa}$。
2. 长度为 $3$ 的：$\texttt{aba}$，$\texttt{aca}$。
3. 长度为 $4$ 的：$\texttt{abca}$，$\texttt{acba}$。
4. 长度为 $7$ 的：$\texttt{abbacca}$，$\texttt{accabba}$。
5. 都不满足，输出 $-1$。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int t,n;
int main()
{
    cin >> t;
    while(t--){
        cin >> n >> a;
        if(a.find("aa") != -1) cout << "2\n";
        else if(a.find("aba") != -1 || a.find("aca") != -1) cout << "3\n"; 
        else if(a.find("abca") != -1 || a.find("acba") != -1) cout << "4\n";
        else if(a.find("abbacca") != -1 || a.find("accabba") != -1) cout << "7\n";
        else cout <<"-1\n";
    }
    return 0;
}
```


---

## 作者：PigJokerYellow (赞：0)

## ~~看题解区没有用  substr  的，便用  substr  水波题解。~~


# 前言

- $ str.substr(begin,length) $；

- 表示切割字符串 $ str $，从下标 $ begin $ 处开始，长度为 $ length $ 来切片。


------------

# 题意

~~题目已经翻译得很详细了。~~

- 给定字符串，找出一子串，求子串大小的最小值。

- 在子串中，规定 $ a $ 的个数大于 $ b $ 和 $ c $ 的个数。

# 思路

- 若有 $ aa $ 输出 $ 2 $;
- 若有 $ aba $ 或 $ aca $ 输出 $ 2 $;
- 若有 $ abca $ 或 $ acba $ 输出 $ 4 $;
- 若有 $ abbacca $ 或 $ accabba $ 输出 $ 7 $;

# $ Code $

```cpp
#include <bits/stdc++.h>
using namespace std;

long long n,m;
//n为操作总次数，m为输入str的长度 
string str;

int main(){
	cin>>n;
	while(n--){
		cin>>m;
		cin>>str;
		long long minn=1e18;
		//设置一个极大值，循环枚举str 
		long long x;
		for(long long i=0;i<=m;i++){
			if(str.substr(i,2)=="aa") x=2,minn=min(minn,x);
			if(str.substr(i,3)=="aba"||str.substr(i,3)=="aca") x=3,minn=min(minn,x);
			if(str.substr(i,4)=="acba"||str.substr(i,4)=="abca") x=4,minn=min(minn,x); 
			if(str.substr(i,7)=="abbacca"||str.substr(i,7)=="accabba") x=7,minn=min(minn,x); 
		}
		//判断 
		if(minn==1e18) cout<<-1;
		//如果minn没变，输出-1 
		else cout<<minn;
		//否则输出minn的值 
		cout<<'\n';
	}
	return 0;
}
```


---

## 作者：skyskyCCC (赞：0)

## 前言。
一道分类讨论题目。
## 分析。
分类讨论每两个 $a$ 之间有**其他字符**的数量。

设两个 $a$ 中的其它字符的数量为 $x$ 个。
- 如果 $x$ 等于 $0$ 的时候，显然这个都是 $a$ 的子串一定符合题意，此时 $2$ 为最短的子串长度。
- 如果 $x$ 等于 $1$ 的时候，显然因为两边是 $a$ 而使得 $a$ 的数量大于中间的字符的数量，符合题意，此时 $3$ 为最短的子串长度。
- 如果 $x$ 等于 $2$ 的时候，如果中间的字符都是同一个字符，因为 $a$ 与其他字符个数相等，所以不符合题意。当中间不是同一个字符时，符合题意，此时 $4$ 为最短的子串长度。
- 如果 $x$ 大于等于 $3$ 的时候，无论中间的是相同字符还是不同字符，都不符合题意，这点可以用抽屉原理得证。

但是在第二条中，注意到不符合题意的 $\texttt{abba}$ 或 $\texttt{acca}$ 中，如果输入的字符串为 $\texttt{abbacca}$ 或 $\texttt{accabba}$ 时，明显可以符合题意，此时 $7$ 为最短的子串长度。

代码如下，仅供参考：
```
#include<iostream>
#include<cstring>
using namespace std;
int t,n;
string str;
int main(){
    cin>>t;
    while(t--){ 
        cin>>n>>str;
        if(str.find("aa")!=string::npos){
		    cout<<"2\n";
		}
        else if(str.find("aba")!=string::npos||str.find("aca")!=string::npos){
		    cout<<"3\n";
		}
        else if(str.find("abca")!=string::npos||str.find("acba")!=string::npos){
		    cout<<"4\n";
		}
        else if(str.find("abbacca")!=string::npos||str.find("accabba")!=string::npos){
		    cout<<"7\n";
		}
        else cout<<"-1\n";
   }
   return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：yangzd (赞：0)

题意：在含有 $a,b,c$ 的字符串中找一个长度最短的子串，使得：

+ 长度至少为 $2$
+ $a$ 的数量严格大于 $b$ 的数量，也严格大于 $c$ 的数量。

# 分析：

zd的第一想法是，如果有连在一起的 $aa$，就直接输出 $2$

现在考虑两个 $a$ 中间夹了一个字符，可以直接输出 $3$ 。

考虑两个 $a$ 之间夹了至少两个字符。如果是 $abca,acba$ ，直接输出 $4$ ，如果是 $abba,acca$ ，不符合要求，但是两个组合起来，即 $abbacca,accabba$ 符合要求。

考虑每两个 $a$ 之间夹了三个或以上的字符，不可能找到相应的答案。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

signed main()
{
	ios::sync_with_stdio(0);
	
    long long n,t;
    bool flag=true;
    
    cin >> t;
    
    while (t--)
    {
		cin >> n;
		
		string s;
		
		cin >> s;
		
		string dict[]={"aa","aba","aca","abca","acba","abbacca","accabba"};
		
		for(auto it:dict)
		{
		    if(s.find(it)!=string::npos) 
		    {
		        cout << it.size() << endl;
		        
		        flag=false;
		        break;
		    }
		}
		
		if (flag==true)
			cout << "-1" << endl;
			
		flag=true;
	}
	
	return 0;
}

```

---

## 作者：Jur_Cai (赞：0)

### 题意
给定一个由 abc 组成的字符串，找出一个最短的子串，满足 a 的数量严格大于 b 的数量和 c 的数量。
### 分析
由于要长度最短，可以发现串两端必然为 a。

然后分类讨论即可。

- aa
- aba 或 aca
- abca 或 abca
- abbacca

可以发现两个 a 中如果有大于等于 3 个其他字符，这必然不能形成一组解（理解不了的可以手玩一下），那就只要记录一下前两个 a 的位置判断即可。

```
#include<bits/stdc++.h>
using namespace std;
char s[1000005];
int main() {
	int T,n;
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		scanf("%s",s+1);
		int lastlasta=-1,lasta=-1,ans=114514;
		for(int i=1; i<=n; i++) {
			if(s[i]=='a') {
				if(lasta==-1) lasta=i;
				else {
					if(i-lasta==1) ans=min(ans,2);
					else if(i-lasta==2) ans=min(ans,3);
					else if(i-lasta==3) {
						if(s[i-1]!=s[i-2]) ans=min(ans,4);
						else if(lastlasta!=-1) {
							if(lasta-lastlasta==3&&s[i-4]==s[i-5]&&s[i-4]!=s[i-1]) ans=min(ans,7); 
						}
					}
					lastlasta=lasta,lasta=i;
				}
			}
		}
		cout<<(ans==114514?-1:ans)<<'\n';
	}
	return 0;
}
```

---

## 作者：feicheng (赞：0)

## C. Dominant Character

### Description

给定字符串 $s(\Sigma=\{a,b,c\})$，要求找到 $s$ 的一个子串 $t$，使得 $t$ 中 $a$ 的数量**严格大于** $b,c$ 的数量，求 $t$ 长度的最小值，无解输出 $-1$。

多测。

**数据范围**

$1\le T\le 10^5$,$1\le n,\sum n\le 10^6$

### Solution

还是结论题。

满足条件的答案仅有 `aa`,`axa`,`axya`,`axxayya`（x,y 表示 b 或 c）。

枚举情况找子串即可。

由于懒就直接抄了个 KMP 的板子。

### Code

```cpp
constexpr int N = 1'000'010;
 
int n, T;
int nxt[10];
char s[N], t[10];
 
inline bool Find() {
	const int ls = strlen(s + 1), lt = strlen(t + 1);
	for (int i = 1;  i <= 9; ++i) {
		nxt[i] = 0;
	}
	for (int i = 2, j = 0; i <= lt; ++i) {
		while (j > 0 && t[i] != t[j + 1]) {
			j = nxt[j];
		}
		if (t[i] == t[j + 1]) {
			++j;
		}
		nxt[i] = j;
	}
	for (int i = 1, j = 0; i <= ls; ++i) {
		while (j > 0 && s[i] != t[j + 1]) {
			j = nxt[j];
		}
		if (s[i] == t[j + 1]) {
			++j;
		}
		if (j == lt) {
			return true;
		}
	}
	return false;
}
 
inline void solve() {
	cin >> n >> (s + 1);
	for (int i = 1; i <= 9; ++i) {
		t[i] = '\0';
	}
	t[1] = 'a', t[2] = 'a', t[3] = '\0';
	if (Find()) {
		cout << 2 << '\n';
		return;
	}
	t[1] = 'a', t[2] = 'b', t[3] = 'a';
	if (Find()) {
		cout << 3 << '\n';
		return;
	}
	t[1] = 'a', t[2] = 'c', t[3] = 'a';
	if (Find()) {
		cout << 3 << '\n';
		return;
	}
	t[1] = 'a', t[2] = 'b', t[3] = 'c', t[4] = 'a';
	if (Find()) {
		cout << 4 << '\n';
		return;
	}
	t[1] = 'a', t[2] = 'c', t[3] = 'b', t[4] = 'a';
	if (Find()) {
		cout << 4 << '\n';
		return;
	}
	t[1] = 'a', t[2] = 'b', t[3] = 'b', t[4] = 'a', t[5] = 'c', t[6] = 'c', t[7] = 'a';
	if (Find()) {
		cout << 7 << '\n';
		return;
	}
	t[1] = 'a', t[2] = 'c', t[3] = 'c', t[4] = 'a', t[5] = 'b', t[6] = 'b', t[7] = 'a';
	if (Find()) {
		cout << 7 << '\n';
		return;
	}
	cout << -1 << '\n';
}
 
```

---

