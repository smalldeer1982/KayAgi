# Diverse Substring

## 题目描述

You are given a string $ s $ , consisting of $ n $ lowercase Latin letters.

A substring of string $ s $ is a continuous segment of letters from $ s $ . For example, "defor" is a substring of "codeforces" and "fors" is not.

The length of the substring is the number of letters in it.

Let's call some string of length $ n $ diverse if and only if there is no letter to appear strictly more than $ \frac n 2 $ times. For example, strings "abc" and "iltlml" are diverse and strings "aab" and "zz" are not.

Your task is to find any diverse substring of string $ s $ or report that there is none. Note that it is not required to maximize or minimize the length of the resulting substring.

## 说明/提示

The first example has lots of correct answers.

Please, restrain yourself from asking if some specific answer is correct for some specific test or not, these questions always lead to "No comments" answer.

## 样例 #1

### 输入

```
10
codeforces
```

### 输出

```
YES
code
```

## 样例 #2

### 输入

```
5
aaaaa
```

### 输出

```
NO
```

# 题解

## 作者：Annihilation_y (赞：3)

## 思路
- 只需找到相邻且不相同的两个字符，就能满足题目的要求，判断为是 ,并输出这两个满足要求的字符。
- 当整个字符串都查找完后，如果还没有发现符合要求的情况，则判断为否 。

## CODE
~~~c++
#include <bits/stdc++.h>//推荐使用万能头，比较方便且简洁。
using namespace std;
string s;
int len;
int main()
{
	scanf("%d",&len);
	cin>>s;
	s=" "+s;
	for (int i=2;i<=len;i++)
	{
		if(s[i]!=s[i-1])//判断相邻的两个字符是否相同。
		{
			printf("YES\n");
			cout<<s[i-1]<<s[i];
			return 0;//直接结束程序，不使用flag。
		}
	}
	printf("NO");
	return 0;
} 
~~~

---

## 作者：liuyz11 (赞：2)

A. Diverse Substring

原比赛题解：[https://www.cnblogs.com/nblyz2003/p/9909038.html](https://www.cnblogs.com/nblyz2003/p/9909038.html)

题意：给你个字符串，让你找一个子串满足任意一个字符的个数不超过其他字符的总和，输出yes或no表示否存在，如果存在输出任意一个。

这题只要找两个不同的相邻字符，因为两个字符各一个都不超过其他字符的总和，如果字符串只由一个字符组成或长度等于一才会不存在。

 代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define rep(x, l, r) for(int x = (int)l; x <= (int)r; x++)
#define repd(x, r, l) for(int x = (int)r; x >= (int)l; x--)
#define clr(x,y) memset(x, y, sizeof(x))
#define mp(x, y) make_pair(x, y)
#define all(x) begin(x), end(x)
#define MAXN 1005
#define fi first
#define se second;
#define Size(x) ((int)size(x))
using namespace std;
typedef long long LL;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 10000007;
//head by DYH

char st[MAXN];

int main(){
    int n;
    scanf("%d", &n);
    scanf("%s", st);
    int len = strlen(st);
    char ch = st[0];
    rep(i, 1, len - 1){
        if(st[i] != ch){
            puts("YES");
            printf("%c%c\n", ch, st[i]);
            return 0;
        }
    }
    puts("NO");
    return 0;
}
```

---

## 作者：decoqwq (赞：2)

昨晚$cf$只切了四道题的蒟蒻来写个题解

这道题让你求一个字符串里的一个子串，使得子串中出现的任意一种字母都不超过子串长度除以二

然后思考一下，发现如果所有字母都一样肯定是不行的

再想一下，如果相邻的两个不一样，直接输出这两个相邻的字母不就行了吗？

然后就做出来了qwq

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[1010];
int n;
int main()
{
    cin>>n>>s;
    for(int i=1;i<n;i++)
    {
        if(s[i]!=s[i-1])
        {
            printf("YES\n%c%c",s[i-1],s[i]);
            return 0;
        }
    }
    cout<<"NO";
}
```

---

## 作者：zsc2003 (赞：1)

# codeforces1037A 2018.10.25

## 题目大意:

读入一个长度为 $n$ 的字符串，你需要从中找出一个子串，并且该字串需要满足一下条件：
- 子串的长度为该字串的字母个数

- 子串中出现次数最多的字母，出现次数应**小于等于**子串长度/2

> 提示：字串长度/2不是下取整的

如果存在满足条件的子串，则输出任意一个的```YES```之后输出任意一个符合条件的子串即可

否则输出```NO```

(另:题解里面的翻译不是抄袭的题目的翻译，而是题目的翻译就是本人写的...)


思路：

一看数据范围 $n \leq 10^3$

所以就只需  $\Theta(N^2)$ 的枚举子串的两个端点即可，在枚举的过程中记录一下每个数字出现的次数

设子串的左端点为 $l$ , 右端点为 $r$ 则子串的长度显然为 $ r-l+1 $

有因为子串的长度不能$/2$后下取整，所以只需乘到左边即可

下面附上我的代码
```
#include<bits/stdc++.h>
#define ll long long
#define ri register int
using namespace std;
inline int read()//读入优化
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}
int l,maxn,le,r;
char s[1100];
bool flag;
map<char,int> mp;//用于统计每个字母出现的次数
int main()
{
	l=read();
	scanf("%s",s+1);
	for(int i=1;i<=l;i++)
	{
		mp.clear();//将记录次数的数组清空
		maxn=0;
		if(flag)
			break;
		for(int j=i;j<=l;j++)
		{
			mp[s[j]]++;
			maxn=max(maxn,mp[s[j]]);
			if(maxn*2<=(j-i+1))//字符串的长度既然/2之后不能下取整，就乘到左边即可
			{
				flag=1;
				le=i,r=j;
				break;
			}
		}
	}
	if(flag)
	{
		puts("YES");
		for(int i=le;i<=r;i++)
			printf("%c",s[i]);
	}
		
	else
		puts("NO");
	return 0;
}
```

---

## 作者：BlanketRice (赞：0)

### 题目描述
给定一个长度为 $ n $ 的字符串，求是否有满足以下要求的字串：

1.字串中每个字符的出现次数严格小于字串长度的一半。

2.字串必须是字符串中连续的一部分。

### 思路
我们从最简单的部分开始想：

#### 长度为一
显然是不可能的，因为长度为一只有一个字符，无论如何不可能小于字符串的一半。于是我们可以在 $ n $ 等于 `1` 时直接输出 `NO`。

#### 长度为二
当我们发现，长度为 `2` 的时候，如果两个字符不同，就符合要求。那我们就找有没有不一样的就行了！！！

#### 实现
`for` 循环枚举每个字符，以此判断是否等于前一个字符即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string s;
signed main () {
    ios :: sync_with_stdio (0);
    cin.tie (0), cout.tie (0);
    cin >> n;
    cin >> s;
    for (register int i = 1; i <= n; ++ i)
        if (s[i] != s[i - 1]) {
            cout << "YES" << endl;
            return 0;
        }
    cout << "NO" << endl;
    return 0;
}
```

---

## 作者：OoXiao_QioO (赞：0)

# 前言

看了其他大佬的代码，只能用复杂来形容了，小蒟蒻却有一个还算清晰简单的思路，代码也比较易懂，下面就来给大佬们献丑。

# 题目概括

一个长度为 $n$ 的字符串，找出任意一段连续的序列，需满足以下条件：

- 子序列中的任何字母出现次数严格小于子序列长度的一半。

- 子序列是原字符串中连续的一部分。

如果能找到，输出两行，第一行为 $\verb!YES!$，第二行为这个子串。 

否则输出 $\verb!NO!$。

# 思路

首先不要被样例迷惑了！！！

我们不用样例的想法看，题目既然说任意一段，那我们可以找的越短越好，因为子串越短，就越容易判断是否满足条件，那么长度定在几比较容易判断呢？我们可以挨个试一试。

## 长度为1

例如字符串为 $\verb!abcdef!$，我们只能选择单个字符，例如 $a$、$b$等。

### 如果子串为 $a$

长度为 $1$ ，字母出现次数也为 $1$，显然不符合第一个要求，所以长度为1的子串，我们可以舍去。

## 长度为2

例如字符串为 $\verb!aabbccddee!$，这次可以选择 $\verb!aa!$、$\verb!ab!$、$\verb!bb!$ 等子串，选择的数量大大增加，我们可以挨个判断一下是否满足条件。

### 如果子串为 $\verb!aa!$

长度为 $2$，字母 $a$ 出现的次数也为 $2$，显然不符合第一个条件。

### 如果子串为 $\verb!ab!$

长度为 $2$，字母 $a$ 和字母 $b$ 出现次数都为 $1$，两个条件都满足，所以我们可以得出以下结论：

- 子串长度为 $2$。

- 两个字符互不相同

找出满足上述规则的两个连续字符，即可完成输出。

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	//定义变量
	 
	int n,i;
	char s[1001];
	
	//输入 
	scanf("%d %s",&n,s);
	
	//处理
	 
	for (i=1;i<n;i++)//循环变量 i 从 1 开始遍历，因为如果从 0 开始，第17行的代码 s[i-1] 就会超出边界，从而 WA
	{				//于是可以从 1 开始遍历，不用担心会超出边界。
		if (s[i] != s[i-1])//判断两个字符是否不同且相邻 
		{
			printf("YES\n");//满足条件，输出 YES 
			printf("%c%c\n",s[i-1], s[i]);//以及这两个字符，注意顺序 
			return 0;//找到满足条件的子串，程序就可以结束 
		}
	}
	printf("NO\n");//否则输出 NO 
	return 0;
}
```


---

## 作者：j1ANGFeng (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1073A)

### 分析
寻找字符串中连续且不相同的字符，存在输出 `YES` 并输出这两个字符，否则输出 `NO`。

其余细节看代码吧。
### AC CODE
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<cmath>
#define int long long
#define N 10000001
#define inf 2147483647
#define in inline
#define re register
using namespace std;
inline long long rd(){char a=getchar();long long f=1,x=0;while(a<'0'||a>'9'){if(a=='-')f=-1;a=getchar();}while(a>='0'&&a<='9'){x=(x<<3)+(x<<1)+(long(a^48));a=getchar();}return f*x;}in void qwqqwq(long long x){if(x!=0){qwqqwq(x/10);putchar(x%10^48);}return;}inline void wt(long long x){if(x==0){putchar('0');return;}if(x<0){x=-x;putchar('-');}qwqqwq(x);return;}
signed main(){
    int n=rd();
    char last=getchar();   //记录前一个字符
    while(--n){
        char k=getchar();
        if(k!=last){     //判断是否连续不相同
            puts("YES");
            putchar(last);
            putchar(k);
            return 0;
        }
        last=k;
    }
    puts("NO");
    return 0;
}
```

---

## 作者：happybob (赞：0)

STL大法好！！！

这道题目其实 `map` + 一个 $\large \text{O}(n^2)$ 的暴力就好了。

我们用 `map` 是为了统计每个字符出现数量，然后枚举找最大值，与 $\LARGE \frac{length}{2}$ 作比较，注意**小于等于**是可以的，一开始就错在这里。
  
然后除法除以2用右移就可以了。


代码：

```cpp
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cstdio>
#include <string>
using namespace std;

inline bool judge(const string& s, unordered_map<char, int>& mp)
{
	int half = s.length() >> 1, maxn = 0;
	unordered_map<char, int>::iterator it_end = mp.end();
	for (register unordered_map<char, int>::iterator it = mp.begin(); it != it_end; ++it)
	{
		maxn = max(it -> second, maxn);
	}
	return maxn <= half;
}

int main()
{
	scanf("%*d");
	string s;
	cin >> s;
	int len = s.length();
	len--;
	for (register int i = 0; i <= len; i++)
	{
		unordered_map<char, int> mp;
		string now = "";
		for (register int j = i; j <= len; j++)
		{
			now += s[j];
			mp[s[j]]++;
			if (judge(now, mp))
			{
				cout << "YES\n";
				cout << now << endl;
				//system("pause");
				return 0;
			}
		}
	}
	cout << "NO\n";
	//system("pause");
	return 0;
}
```


---

