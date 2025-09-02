# Two Subsequences

## 题目描述

#### 题意翻译
给你一个字符串 $s$。你需要两个非空字符串 $a$ 和 $b$ 并且满足下面的条件：
1. 字符串 $a$ 和 $b$ 都是 $s$ 的子串。
2. 对于原字符串的每一个字符，必须属于 $a$ 和 $b$ 之一。
3. $a$ 是所有满足条件的字符串中字典序最小的。
给你 $s$，输出 $a$ 和 $b$。

注意：

如果可以通过删除几个(可能为零)元素从 $s$ 获得 a(b)，那么字符串 a(b) 是字符串s的子序列。例如，“Dores”、“cf”和“for”是“codeforces”的子序列，而“Decor”和“fork”则不是。

字符串 $x$ 比字符串 $y$ 字典序小当且仅当 
- $x$ 是 $y$ 的前缀，但 $x\ne y$ 
- 在 $x$ 和 $y$ 不同的第一个位置，$x$ 中的相应字母在字母表中出现的位置早于 $y$ 中的相应字母。

## 说明/提示

$1\le t\le 1000, 2\le |s| \le 100$
$|s|$ 表示 $s$ 的长度。

译者：@smyslenny

## 样例 #1

### 输入

```
3
fc
aaaa
thebrightboiler```

### 输出

```
c f
a aaa
b therightboiler```

# 题解

## 作者：Yike_linen (赞：4)

### 题目大意
给定字符串 $S$ ，你需要将其拆解成两个**子串** $a,b$，满足对于 $S$ 中的任意一位上字符，只出现在 $a,b$ 中的**恰好**一个。

对于字符串 $a$，要求其字典序在**所有可能**的 $a$ 中最小；对 $b$ 无任何额外要求。输出任意的可行解。

保证 $1 \leqslant t \leqslant 1000 $，$ 2 \leqslant |S| \leqslant 100 $， $S$ 仅由小写字母组成。

---
### 解析
题目要求 $a$ 的字典序最小，那么什么是字典序呢？

---
先按照第一个字母、以 $\texttt{a,b,c...z}$ 的顺序排列；如果第一个字母一样，那么比较第二个、第三个乃至后面的字母。如果比到最后两个单词不一样长（比如，sigh 和 sight，那么把短者排在前。

---
引自百度百科。

**言归正传**，显然对于一个字符串，若要让它的字典序最小，需要从**顺序**和**长度**两方面考虑。

- 对于顺序，先不考虑长度，显然当 $a_0 = \texttt{a}$ 时，a的字典序在顺序上时最小的，如果 $S$ 中不存在字符 $\texttt{a}$，显然 $a$ 字典序最小的情况是 $a_0 = c$，$c$ 为 $S$ 中字典序最小的字符时 。

- 考虑长度，当 $a$ 的组成字符确定时，因为字典序的规则：”**短者在前**“， $a$ 的长度越短，$a$ 的字典序就越小。所以显然 $a$ 的长度应当为 $1$。

结合起来来看，我们应当使 $a$ 的长度为 $1$，同时那个唯一的字符应当是 $S$ 中字典序最小的字符。

这样，我们的思路就明确了，对于字符串 $S$，我们先找到它字典序最小的字符，将其作为 $a$ 本身，然后把剩下的所有字符当作 $b$，输出。

---
#### 代码：
```cpp
#include <iostream>
#include <string>
using namespace std;
int n, t;
string s;
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> s;
        n = s.size();       //s的长度，注意string的下标从0开始，所以要从0循环到n-1
        char c = 'z' + 1;   //先设置字符c为极大值，注意字符可以直接按字典序比较
        int num = 0;        //c的下标
        for (int i = 0; i < n; i++)
        {
            if(s[i] < c)    //如果当前字符比c更小，则将c更新为新的最小值
                c = s[i], num = i;  //同时更新c的下标
        }
        putchar(c);     //输出字符串a
        putchar(' ');
        for (int i = 0; i < n;i++)
        {
            if(num == i)    //跳过字符c
                continue;
            putchar(s[i]);  //一个一个输出字符串b
        }
        putchar('\n');  //换行
    }
    return 0;
}
```


---

## 作者：银杉水杉秃杉 (赞：2)

先看看翻译：

将仅由小写字母组成的字符串 $s$ 拆成两个子串（可以不连续）$a$ 和 $b$，使得 $a$ 的字典序最小，输出 $a$ 和 $b$（中间用空格隔开）。答案可能有多种，任意输出一种即可。

很简单的字符串练习，$a$ 为 $s$ 中出现的最小字母时，$a$ 的字典序最小。在 $s$ 中找到最小字母 $a$，将其删除即可得到 $b$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,c[30];
string s,b;
char a;
int main()
{
    cin>>T;
    while (T--)
    {
        cin>>s;
        memset(c,0,sizeof(c));
        for (int i=0;i<s.size();i++)
            c[s[i]-'a']++;
        for (int i=0;i<26;i++)//利用桶排的思想
            if (c[i])
            {
                a=i+'a';
                break;
            }
        b=s.erase(s.find(a),1);
        cout<<a<<' '<<b<<endl;
    }
    return 0;
}
```


---

## 作者：HerikoDeltana (赞：1)

## 「题目简述」

给出一个字符串 $S$，要求找到一个字典序最小的非空字串，然后输出这个字串和原字符串删掉这个字串后形成的串。

## 「思路简述」

还是一如既往的手速题（

因为是找出一个字典序最小的非空字串，所以找到一个字典序最小的字母即可。

## 「Code」

```cpp
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <cstring>

#define Heriko return
#define Deltana 0
#define Romanno 1
#define S signed
#define LL long long
#define R register
#define I inline
#define CI const int
#define mst(a, b) memset(a, b, sizeof(a))
#define ON std::ios::sync_with_stdio(false);cin.tie(0)
#define Files() freopen("RNMTQ.in","r",stdin);freopen("RNMTQ.out","w",stdout)

using namespace std;

template<typename J>
I void fr(J &x)
{
    short f(1);x=0;char c=getchar();

    while(c<'0' or c>'9')
    {
        if(c=='-') f=-1;
        
        c=getchar();
    }

    while (c>='0' and c<='9') 
    {
        x=(x<<3)+(x<<1)+(c^=48);
        c=getchar();
    }
   
    x*=f;
}

template<typename J>
I void fw(J x,bool k)
{
    if(x<0) x=-x,putchar('-');

    static short stak[35];short top(0);

    do
    {
        stak[top++]=x%10;
        x/=10;
    }
    while(x);

    while(top) putchar(stak[--top]+'0');

    k?puts(""):putchar(' ');
}

CI MXX(1005);

char s[MXX];

S main()
{
    Files();

    int T;fr(T);

    while(T--)
    {
        scanf("%s",s+1);
        int a(1),n(strlen(s+1));

        for(int i(2);i<=n;++i)
            if(s[i]<s[a])
                a=i;

        putchar(s[a]);putchar(' ');

        for(int i(1);i<=n;++i)
            if(i!=a)
                putchar(s[i]);

        puts("");
    }

    Heriko Deltana;
}
```



---

## 作者：GuoWil (赞：1)

题意简述：

有一个字符串 $s$ ，构造两个 $s$ 的子串 $a$ 和 $b$ ，使得 $s$ 的每一个字符都在 $a$ 或 $b$ 中出现，还要使得 $a$ 的**字典序**最小。

思路：先满足 $a$ 。使得 $a$ 的字典序最小的情况为 $s$ 中 ASCII 码最小的字符，把它提取出来后，剩下的字符串正好也是 $s$ 的子串，而且 $s$ 中剩下的字符都在这个字符串 $b$ 里，满足题目条件。

做法：

1. 先定义一个字符串 $ss$ 等于 $s$ ，$s$ 用来排序， $ss$ 当成原字符串进行遍历。

1. 把整个字符串 $s$ 排序，（用法：``` sort(s.begin(),s.end())```）。取出第一个也就是最小的字符当成字符串 $a$ 。
1. 遍历 $ss$ 中的每一个字符，如果等于 $a$ ，计数变量加 $1$。
1. 再次遍历，如果和 $a$ 不相同 **或 $ss$ 中 $a$ 的数量大于 $1$**，就输出。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	string s;
	cin >> n;
	while(n--){
		cin >> s;
		string ss=s;
		sort(s.begin(),s.end());// 排序。
		cout << s[0] << ' ';
		for(int i=0,ct=0;i<ss.size();++i){
		    if(ss[i]==s[0]) ++ct;//查找字符串中最小字符的个数。
		    if(ss[i]!=s[0]||(ss[i]==s[0]&&ct>1)) putchar(ss[i]);
		}
		puts(" ");
	}
}
```




---

## 作者：gaozitao1 (赞：0)

**题目大意**：给一个字符串 $s$，将这个字符串分成两个非空子串，使第一个子串字典序最小。如果有多个答案，输出任意一个。

字典序最小，首先要使第一个数尽可能小，其次是要短，所以，只需要找出字符串 $s$ 中字典序最小的字母作为第一个子串，剩下的作为第二个子串就可以了。

代码：
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
char c[100];
int main()
{
	char s;
	int a,i,n,t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s",&c);
		n=strlen(c);
		a=0;//记录最小的字母出现的位置
		s=c[0];
		for(i=1; i<n; ++i)
			if(c[i]<s)
			{
				a=i;
				s=c[i];
			}
		putchar(s);
		putchar(' ');
		for(i=0; i<a; ++i)
			putchar(c[i]);
		for(i=a+1; i<n; ++i)
			putchar(c[i]);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：bigju (赞：0)

# 题意

给定一个字符串 $s$，让你求两个字符串 $a$ 和 $b$ 使得它们满足：

- $a$ 和 $b$ 都为 $s$ 的子串。
- $s$ 的每个字符都在 $a$ 或 $b$ 中出现过。
- $a$ 的字典序要尽量的小，$b$ 则不作要求。

# 做法

我们考虑找出 $s$ 中字典序最小的一个字符作为 $a$，剩下的作为 $b$，显然这样 $a$ 的字典序是最小的，也可以满足上述要求。

[Code](https://www.luogu.com.cn/paste/4azdrzwo)

---

## 作者：奥斯卡小冰人 (赞：0)

[$\color{black}CF1602A$](https://www.luogu.com.cn/problem/CF1602A)

这道题比较简单。题意大概就是给出一个字符串s，求出字符串a和字符串b。a和b有以下要求：
- a和b为s的一个子序列；
- 对于任何一个$i$，$s_i$，必须恰好属于a或者b中的一个字符串； 
- a的字典序尽可能的小，而b可以是任何一个可能的字符串。

(翻译可能不严谨，可在评论中指出。~~主要是英语太菜了~~)

看完题意可能没什么想法，但是当你看完样例，就会发现，事实上如果要a的字典序小，a就最好是一个字符，而且是字符串s中最小的字符。而b就是s中除去a剩下的字符串。

上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string s,b;
char a;
int main()
{
	cin >> n;
	while(n--)
	{
		cin >> s;a = s[0];b = "";
		for(int i = 1;i < s.length();i++) a = min(s[i],a);
		cout << a << ' ';
		for(int i = 0;i < s.length();i++)
		{
			if(s[i] == a) a = ' ';
			else b += s[i];//这里其实可以直接输出的，不知道在想什么
		}
		cout << b << endl;
	}
	return 0;
}
 ```

---

## 作者：Jerrlee✅ (赞：0)

## 题意
给你一个字符串 $s$。你需要找到两个非空字符串 $a$ 和 $b$，以满足以下条件： 
1. 字符串 $a$ 和 $b$ 都是 $s$ 的子序列。

2. 对于每个索引 $i$，字符串 $s$ 的 $s_i$ 必须正好属于字符串 $a$ 或 $b$ 中的一个。

3. 字符串 $a$ 是字典上可能的最小值，字符串 $b$ 可能是任何可能的字符串。

## 思路
在 $s$ 中将 $a$ 作为最小字符始终是最佳的（$a$ 以最小可能字符开始，并且是任何其他较长字符串的前缀）。在这种情况下，$b$ 只是 $s$ 中除 $a$ 的所有字符。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        string s,c;
        cin>>s;
        c=s;
        sort(c.begin(),c.end());
        int a=s.find(c[0]);
        s.erase(s.begin()+a);
        cout<<c[0]<<" "<<s<<endl;
    }
}
```
[AC记录（洛谷）](https://www.luogu.com.cn/record/61096530)

[AC记录（CF）](http://codeforces.com/contest/1602/submission/133251853)

---

## 作者：A_Đark_Horcrux (赞：0)

对于原字符串 $s$，它字典序最小的子序列就是它所包含的序号最小的那一个字母，很明显如果不是它或者它后面跟上其他字符字典序会变大。

因此一次遍历找出最小的那个字母，由于题目要求每一位必须只属于一个子序列，因此两个子序列没有相同元素，只要把原字符串去掉最小的那一位，剩下的就是满足题意的另一个子序列qwq

```cpp
#include<iostream>
using namespace std;
int main()
{
	int T; string s;
	cin>>T;
	while(T--)
	{
		cin>>s; char minn='z'+1; int p=0;//最小和位置
		for(int i=0;i<s.length();i++) if(s[i]<minn) minn=s[i],p=i;//找最小，标记位置
		cout<<minn<<" "; for(int i=0;i<s.length();i++) if(i!=p) cout<<s[i];//先输出单个字母，然后输出剩下的
		cout<<"\n";//awa
	}
	return 0;
}

```


---

## 作者：smyslenny (赞：0)

# CF1602A

## Solution

看到限制，要保证 $a$ 和 $b$ 是 $s$ 的子串并且要包含 $s$ 中的所有字母，我们不妨将 $s$ 分成两部分。分别作为 $a$ 和 $b$。

那怎么保证 $a$ 的字典序最小呢，我们考虑将 $s$ 中所有字母最小的一个拿出来，不难发现，此时 $a$ 一定是所有可能的 $a$ 中最小的。

### Code

```cpp
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
const int M=105;
int T;
int read()
{
	int x=0,y=1;
	char c=getchar();
	while(!isdigit(c)) {if(c=='-') y=0;c=getchar();}
	while(isdigit(c)) { x=x*10+(c^48);c=getchar();}
	return y?x:-x;
}
char s[M];
int main()
{
	T=read();
	while(T--)
	{
		scanf("%s",s+1);
		int len=strlen(s+1),pos=0,Min=INF;
		for(int i=1;i<=len;i++)
			if(s[i]-'a'<Min)
				Min=s[i]-'a',pos=i;
		printf("%c ",Min+'a');
		for(int i=1;i<=len;i++)
			if(i!=pos)
				printf("%c",s[i]);
		printf("\n");
	}
	return 0;
}

```


---

## 作者：智子 (赞：0)

## 题意

输入一个字符串 $s$，将其分成两个字序列 $a$ 和 $b$，使 $a$ 的字典序尽量小。

## 思路

容易想到字典许最小的字序列就是 $s$ 中最小的单个字符，所以 $a = \min s_i$，而 $b$ 就是 $s$ 去掉 $a$ 后剩余的部分。

## 代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN = 100 + 5;

char s[MAXN];

int main() {
    int T;

    scanf("%d", &T);
    while(T--) {
        scanf("%s", s);
        int n = strlen(s), p = 0;
        for(int i = 1; i < n; i++) {
            if(s[i] < s[p]) {
                p = i;
            }
        }
        printf("%c ", s[p]);
        for(int i = 0; i < n; i++) {
            if(p == i) {
                continue;
            }
            printf("%c", s[i]);
        }
        printf("\n");
    }

    return 0;
}

```

---

