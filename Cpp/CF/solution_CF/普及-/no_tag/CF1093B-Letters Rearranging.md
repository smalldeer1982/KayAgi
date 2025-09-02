# Letters Rearranging

## 题目描述

You are given a string $ s $ consisting only of lowercase Latin letters.

You can rearrange all letters of this string as you wish. Your task is to obtain a good string by rearranging the letters of the given string or report that it is impossible to do it.

Let's call a string good if it is not a palindrome. Palindrome is a string which is read from left to right the same as from right to left. For example, strings "abacaba", "aa" and "z" are palindromes and strings "bba", "xd" are not.

You have to answer $ t $ independent queries.

## 说明/提示

In the first query we cannot rearrange letters to obtain a good string.

Other examples (not all) of correct answers to the second query: "ababaca", "abcabaa", "baacaba".

In the third query we can do nothing to obtain a good string.

## 样例 #1

### 输入

```
3
aa
abacaba
xdd
```

### 输出

```
-1
abaacba
xdd```

# 题解

## 作者：Reywmp (赞：4)

人生第一场CF，还是div2。

写篇题解纪念下。

------------

比赛时没有想到排序，采用了通俗易懂的算法。

我估计复杂度比sort要低（O(len)左右）。

------------

>这一题要求你将回文字符串改为非回文。如果无法修改输出-1；

那么我们可以得出:

1. 当1个字符串所有的字符均相同时，怎么改变都无法得到非字符串。这个时候我们输出-1（也只有这种情况输出-1）；

2. 将回文字符串改为非回文我们只需要将2个**不相同**的字符串对调，字符串就会变成非回文，而且这题没有其他要求且有spj，所以不需要特判；

3. 我们通过便利一遍字符串就可以完成2个任务，即： **_判断是否为全部相同的字符_** 以及 **_如果不是可是是回文字符串那么找到2个不相同的字符的位置_** ；

4. 不论如何，我们先要判断是否为回文字符串：判断回文很简单，只需要从字符串首位和末尾一直向中间位置遍历，如果当前2个字符**不相同**，则不是回文字符串。

------------

那么思路就很清晰了：

>先判断是否为回文，再看是否所有字符相同，

>如果找到了第一对不相同的字符，**记录下他们的位置**并且将全部相同置为false。

>然后按上面的思路输出（全部相同则输出-1，不是回文则输出原字符串，如果是回文却不全相同就交换2个不一样的字符再输出）。

------------

代码如下，内有注释：

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
#define ll long long
//IG NB!<====never mind
using namespace std;
void read(int &x)
{
	 x=0;int w=1;
	 char ch=getchar();
	 while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	 if(ch=='-')w=-1,ch=getchar();
	 while(ch>='0'&&ch<='9')
	 {x=(x<<1)+(x<<3)+ch-48,ch=getchar();}
	 x*=w;
}
int mx(int a,int b){return a>b?a:b;}
int mn(int a,int b){return a<b?a:b;}
char a[1005];
int t,len;
bool bkstr()//判断回文
{
	int r=len-1;
	int l=0;
	while(l<=r)
	{
		if(a[l]!=a[r])return 0;
		l++;r--;
	}
	return 1;
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(t);
	while(t--)
	{
		scanf("%s",a);
		len=strlen(a);
		bool ISBK=bkstr();//看是否为回文
		bool ALLsame=1;//假设一开始是相同的
		int diff1=0,diff2=0;
		for(int i=1;i<len;i++)
		{
			if(a[i]!=a[i-1]){diff1=i;diff2=i-1;ALLsame=0;break;}//找到了不相同的
		}
		if(ISBK==0)
		{
			printf("%s\n",a);//不是回文原样输出
		}
		else
		{
			if(ALLsame==1)puts("-1");//全相同输出-1
			else 
			{
				char x=a[diff1];
				a[diff1]=a[diff2];
				a[diff2]=x;//交换
				printf("%s\n",a);
			}
		}
	}
	return 0;
}
```


---

## 作者：一扶苏一 (赞：3)

## Solution

考虑如果一个字符串如果是回文串，那么首尾一定一样。为了尽可能不一样，我们直接把相同的位置放在一起。如果这样首尾还相同的话，说明原串只有一个字母，这样的串显然无法排好。剩下的情况只要把相同的放在一起，那么最后一位一定不等于第一位。于是就构造出一个不是回文串的串了。

## Code
(话说你谷什么时候资瓷py的高亮啊)

```python
t = int(input())
for T in range(t):
	s = input()
	ss = list(s)
	ss.sort()
	l = len(ss)
	if ss[0] == ss[l - 1]:
		print(-1)
	else:
		for i in range(l):
			print(ss[i], end = "")
		print("")
```

---

## 作者：Zechariah (赞：2)

对于输入的字符串，如果输入全都是相同的字符，那么无论怎么排都是回文，否则我们用一个桶统计所有字符出现的次数，然后顺着一个个输出就行了，比如输入ababa我们输出aaabb,这样只要输入不全是相同字符总是可以保证输出不是回文

---

## 作者：Sooke (赞：1)

### 题意

重排一个字符串使其不回文，无解输出 $-1$。

### 解题思路

想要让一个字符串排成回文，限制会比较多，但要排成不回文，显然只需让第一个字符和最后一个字符不一样即可。换句话说，如果字符串所有字符相等，即无解，否则，就可以把不一样的字符分别放在首尾，来保证其不回文。

### 代码实现

```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>

int tn;

int main() {
    for (std::cin >> tn; tn; tn--) {
        std::string s; std::cin >> s;
        std::sort(s.begin(), s.end());
        if (s[0] == s[s.size() - 1]) { std::cout << -1 << std::endl; } else { std::cout << s << std::endl; }
    }
    return 0;
}
```

---

## 作者：little_sun (赞：1)

# 题解 CF1093B 【Letters Rearranging】

可以发现，如果将字符串排序后，头字母和尾字母相等，则这个字符串全部由这个字符组成（输出-1）

否则将其排序后输出的绝对不是回文串

代码：
```cpp
# include <bits/stdc++.h>

std::string s;

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        std::cin >> s;
        int len = s.length();
        std::sort(s.begin(), s.end());
        if(s[0] == s[len - 1])
            printf("-1\n");
        else 
            std::cout << s << "\n";
    }
    return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
有 $t$ 次询问，每次询问给定一个字符串 $s$。定义一个“好的字符串”为不是回文串的字符串。对于每一次询问，求出任意一个重新排列能够得到的“好的字符串”，或者这不可能实现。

**数据范围：$1\leqslant t\leqslant 100,1\leqslant|s|\leqslant 1000$。**
## Solution
首先我们来判断一下，什么样的情况下一个回文串无法变成一个非回文串？显然是这个回文串里面只有一种字符的情况下。那么其他的情况下，如何讲一个回文串变成一个非回文串？我们可以先找到中间的一个字符串（如果长度是偶数，随便取左边还是右边都行），然后开始往左扫、往右扫，一旦发现有了和当前字符不一样的字符，就将这两个字符交换，不然换了之后还是回文串。

接下来讲一下，如何判断一个字符串是否是回文串？

我们定一个左边界 $l$ 和右边界 $r$，规定 $l\leqslant r$（尤其是在字符串的长度是奇数的情况下）。那么我们可以直接往中间**一起**扫，一旦有两个字符串不相同，那么这个字符串就不是回文串了。如果到了中间还没有不符合条件的情况出现的话，那么这个字符串就是回文串了。

至于判断一个字符串是否只有一种字符和上面的情况类似，只要发现有两个不同的字符就不可能会是的，扫完之后如果还没有出现有不同字符的情况，那么这个字符串就只有一种字符了。
## Code
```cpp
int t;

int main() {
	getint(t);
	while(t--) {
		string s;
		cin >> s;
		int len = s.size(), flagno = 1, flagpa = 1, i, j;
		_for(i, 1, len - 1) if(s[i] != s[i - 1])	flagno = 0;
		for(i = 0, j = len - 1; i <= j; ++i, --j)
			if(s[i] != s[j])	flagpa = 0;
		if(flagno) {puts("-1"); continue;}
		if(flagpa) {
			int k = i;
			while(s[k] == s[i] && k < len - 1)	k++;
			if(s[k] == s[i]) {
				int k0 = i;
				while(s[k0] == s[i] && k0 > 0)	k0--;
				swap(s[k0], s[i]);
			}
			else swap(s[k], s[i]);
		}
		cout << s << endl;
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

我这个写法可能跟大家有些不同

我是这样想的

每次读入的这个字符串先判断是否是回文，如果是，那么直接输出，所以我构造了一个回文函数：

```cpp
bool huiwen(string x)
{
	string y = x;
	reverse(y.begin(), y.end());//翻转
	return y == x;
}
```

但如果不是呢，想想看，可以往后找对吧？但如果往后找找不到呢？对，要往前找，但这样一会往后一会往前的，很麻烦对吧？

STL大法！先把字符串从小到大排一遍：

```cpp
sort(s.begin(), s.end());
```

那么然后呢？怎么往后找，在STL的algorithm中有个叫：

# next_permutation()

的函数！


这个函数可以做全序列的题目，详见P1706，想做的可以去做做。每调用一次该函数，数组或STL容器会变成下一字典序，可以把全部序列枚举一遍，当该序列为最后一个序列，返回false，否则返回true。

因此，代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

bool huiwen(string x)
{
	string y = x;
	reverse(y.begin(), y.end());
	return  y == x;
}

string s;

int main()
{
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> s;
		if(!huiwen(s))
		{
			cout << s << endl;
		}
		else
		{
			sort(s.begin(), s.end());
			if(!huiwen(s))//要先判断一次！while循环一开始就变成下一字典序了。
			{
				cout << s << endl;
				continue;
			}
			else
			{
				while(next_permutation(s.begin(), s.end()))
				{
					if(!huiwen(s))//如果现在不是回文序列，就输出并且退出循环
					{
						cout << s << endl;
						break;
					}
				}
			}
			cout << "-1\n";//找不到-1
		}
	}
	return 0;
}
```





---

## 作者：封禁用户 (赞：0)

介绍一种$O(\text{玄学})$的方法。

重新排列一个字符串使它变的不回文看起来挺难的。。。

我们可以用`random_shuffle()`函数，不停打乱字符串直到字符串变得不回文为止。

~~最坏情况可能要shuffle$n!$次。。。~~
```cpp
#include <cstdio>
#include <iostream>
#include <stack>
#include <utility>
#include <algorithm>
#include <ctime>
#include <set>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#define rep(i,a,b) for(int i=(a);i<=(b);++i) 
#define dec(i,a,b) for(int i=(a);i>=(b);--i)
#define gc() getchar()
#define endll putchar('\n')
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double ld;
inline ll read(){
    char ch=gc();
    ll x=0,f=1;
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=gc();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=gc();
    }
    return x*f;
}
inline void print(ll k){
    if(k<0) k=-k,putchar('-');
    if(k>9) print(k/10);
    putchar(k%10+48);
}
inline void println(ll k){
    print(k);
    endll;
}
inline void printsp(ll k){
    print(k);
    putchar(' ');
}
bool is_pal(string a){
	if(a.size()==1) return true;
	rep(i,0,((a.size()/2)-1))  if(a[i]!=a[a.size()-i-1]) return false;
	return true;
}
bool is_samee(string a){
	rep(i,1,(a.size()-1)) if(a[i]!=a[i-1]) return false;
	return true;
}
int main(){
	int t=read();
	while(t--){
		string a;
		cin>>a;
		if(is_samee(a)) println(-1);
		else{
			while(is_pal(a)) random_shuffle(a.begin(),a.end());
			cout<<a<<endl;
		}
	}
}
```

---

## 作者：StudyingFather (赞：0)

将字符串排序一遍就可以使得绝大多数字符串不再满足回文串性质了。（因为较大的字符会全部排到后面）

但是，如果该字符串是由同一个字符构成的，那么就要输出-1了。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[1005];
int main()
{
 int t;
 scanf("%d",&t);
 while(t--)
 {
  bool flag=true;
  scanf("%s",s);
  int len=strlen(s);
  sort(s,s+len);
  for(int i=0;i<len/2;i++)
   if(s[i]!=s[len-i-1])//判断排序后的串是否是回文串
   {
   	flag=false;
   	break;
   }
  if(flag)puts("-1");
  else puts(s);
 }
 return 0;
}
```

---

## 作者：zsc2003 (赞：0)

### codeforces 2018.12.15 B

题目大意:
读入一个字符串，若这个字符串无论怎么交换其中的字符都是回文的，则输出```-1```

否则输出任意一种交换过字符后不是回文的字符串

(交换字符只能是改串内不同位置互相交换)

思路:

不是回文的直接输出即可

通过交换第一个字符和后面任意一个不与它相同的字符，构造出的字符串一定不是回文的


如果这个字符串所有的字符都是相同的，那么无论怎么变换都一定是回文的

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
    int r,s=0,c;
    for(;!isdigit(c=getchar());s=c);
    for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
    return s^45?r:-r;
}
int l,t,ans;
bool flag;
char s[1100];
int main()
{
    t=read();
    while(t--)
    {
        scanf("%s",s+1);
        flag=0;
        l=strlen(s+1);
        for(int i=1;i<=l/2;i++)
            if(s[i]!=s[l-i+1])
            {
                flag=1;
                break;
            }
        if(!flag)
        {
            int num=0;
            for(int i=2;i<=l;i++)
                if(s[i]==s[i-1])
                    num++;
            if(num==l-1)//如果这个字符串所有的字符都是相同的，那么无论怎么变换都一定是回文的
                puts("-1");
            else
            {
                for(int i=2;i<=l;i++)//通过交换第一个字符和后面任意一个不与它相同的字符，构造出的字符串一定不是回文的
                    if(s[i]!=s[1])
                    {
                        swap(s[i],s[1]);
                        break;
                    }
                printf("%s\n",s+1);
            }
        }	
        else//不是回文的直接输出即可
            printf("%s\n",s+1);
    }
    return 0;
}
```

---

## 作者：LJC00118 (赞：0)

如果一个字符串重排后一定是回文串，说明这个字符串只有 $ 1 $ 种字符

如果有两种不同字符，就可以把一个放在开头，一个放在结尾，这样形成的一定不是回文串

一个简单一点的写法是 $ sort $ 一下这个字符串，判断回文

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie();
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int N = 1005;

char c[N];
int T, n;

bool check() {
    int l = 1, r = n;
    while(l < r) {
        if(c[l] != c[r]) return 1;
        l++; r--;
    }
    return 0;
}

int main() {
    read(T);
    while(T--) {
        scanf("%s", c + 1); n = strlen(c + 1);
        if(check()) { printf("%s\n", c + 1); continue; }
        sort(c + 1, c + n + 1);
        if(check()) { printf("%s\n", c + 1); continue; }
        printf("-1\n"); 
    }
    return 0;
}
```

---

