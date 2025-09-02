# Compare T-Shirt Sizes

## 题目描述

Two T-shirt sizes are given: $ a $ and $ b $ . The T-shirt size is either a string M or a string consisting of several (possibly zero) characters X and one of the characters S or L.

For example, strings M, XXL, S, XXXXXXXS could be the size of some T-shirts. And the strings XM, LL, SX are not sizes.

The letter M stands for medium, S for small, L for large. The letter X refers to the degree of size (from eXtra). For example, XXL is extra-extra-large (bigger than XL, and smaller than XXXL).

You need to compare two given sizes of T-shirts $ a $ and $ b $ .

The T-shirts are compared as follows:

- any small size (no matter how many letters X) is smaller than the medium size and any large size;
- any large size (regardless of the number of letters X) is larger than the medium size and any small size;
- the more letters X before S, the smaller the size;
- the more letters X in front of L, the larger the size.

For example:

- XXXS &lt; XS
- XXXL &gt; XL
- XL &gt; M
- XXL = XXL
- XXXXXS &lt; M
- XL &gt; XXXS

## 样例 #1

### 输入

```
6
XXXS XS
XXXL XL
XL M
XXL XXL
XXXXXS M
L M```

### 输出

```
<
>
>
=
<
>
```

# 题解

## 作者：flying_man (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF1741A)

题意：给你两个衣服的型号，比较两者大小。

------------

**题解部分：**

注意到型号的最后一个字符只能是 $\text{S}$、$\text{M}$、$\text{L}$ 中的其中一个。

所以我们用一个数字对应每一个型号，通过最后一个字符来决定正负。

**特别的，$\text{M}$ 型号对应的值为 $0$。**

而字符串的长度决定了数字的绝对值。

就比如说，$\text{XXXXS}$ 对应的值为 $-5$，$\text{L}$ 对应的值为 $1$。

然后比较两者大小即可。

------------
code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,z1,z2;
char s1[105],s2[105];
int main(){
	cin >> t;
	while(t--){
		cin >> s1 >> s2;
		int len1 = strlen(s1),len2 = strlen(s2);
		if(s1[len1-1] == 'M') z1 = 0;
		if(s1[len1-1] == 'S') z1 = -len1;
		if(s1[len1-1] == 'L') z1 = len1;
		if(s2[len2-1] == 'M') z2 = 0;
		if(s2[len2-1] == 'S') z2 = -len2;
		if(s2[len2-1] == 'L') z2 = len2;
		if(z1 < z2) printf("<\n");
		if(z1 == z2) printf("=\n");
		if(z1 > z2) printf(">\n");
	}
	return 0;
}
```

---

## 作者：Dry_ice (赞：3)

[更好的阅读体验](https://www.cnblogs.com/dry-ice/p/cf1741a.html)

题链：[cf](https://codeforces.com/contest/1741/problem/A) [lugou](https://www.luogu.com.cn/problem/CF1741A)

> 赛时吃了一波罚时（？ 代码挺长（？

## Description
给你两个衣服尺码，比较他们的大小。

## Analysis
细节题。

首先我们将所有尺码分为 $\text{S}$、$\text{M}$、$\text{L}$ 三类，其中仅 $\text{M}$ 码前不会有 $\text{X}$。

下面分为两类：

1. 异类：直接比较末字符所指向的类别，直接输出比较结果。

1. 同类：向前查询 $\text{X}$ 的个数，再根据 $\text{S}$ 和 $\text{L}$ 的加 $\text{X}$ 比大小规则输出结果。

## Code
> 仅供参考。

```cpp
#include <iostream>
#include <stdio.h>
using namespace std;
string a, b;
int ch[250];
int main(void) {
	ch['S'] = 0, ch['M'] = 1, ch['L'] = 2;
	int t; for (cin >> t; t--; ) {
		cin >> a >> b; int n = a.length(), m = b.length(); --n, --m;
		if (a[n] == 'M') {
			if (b[m] == 'M') puts("=");
			if (b[m] == 'S') puts(">");
			if (b[m] == 'L') puts("<");
			continue;
		}
		if (a[n] == 'L' && b[m] != 'L') {
			puts(">"); continue;
		}
		if (a[n] == 'S' && b[m] != 'S') {
			puts("<"); continue;
		}
		//以上为异类
		//以下为同类
		if (a[n] == 'S') {
			if (n > m) puts("<");
			if (n == m) puts("=");
			if (n < m) puts(">");
			continue;
		}
		if (a[n] == 'L') {
			if (n > m) puts(">");
			if (n == m) puts("=");
			if (n < m) puts("<");
		}
	}
	return 0;
}
```

## The end. Thanks.

~~(路过一顶~~

---

## 作者：ShanCreeperPro (赞：2)

## CF1741A Compare T-Shirt Sizes 題解

### 题意

给定两个字符串 $a$ 和 $b$ 表示两件衣服的尺码，我们规定：字符串只能由字符 M（中等尺寸）组成或由几个字符 X（可以是 0 个）加上一个字符 S（小尺寸） 或 L（大尺寸） 组成。

你需要比较两件衣服尺码大小，比较方法如下：

- 无论前面有多少个字符 X 的小尺寸，都小于中等尺寸和大尺寸；
- 无论前面有多少个字符 X 的大尺寸，都大于中等尺寸和小尺寸；
- 字符 S 前的字符 X 越多，尺寸越小；
- 字符 L 前的字符 X 越多，尺寸越大。



给定 $t$ 组尺寸（$1 \le t \le 10^4$），若第一件衣服尺寸大，输出 `&gt`，若第二件衣服尺寸大，输出 `&lt`，否则输出 `=`。每组数据换行隔开。

## 分析

根据题目给定的比较方法比较，推荐设定专门函数比较，方便使用和阅读。

#### 无论前面有多少个字符 X 的小尺寸，都小于中等尺寸和大尺寸：

特判两件衣服尺码的最后一个字符是否是 S，若是，比较另一件衣服：

- 若仅为一个字符 M 或最后一个字符是 L，这件衣服大；
- 否则，进入第三个函数。

#### 无论前面有多少个字符 X 的大尺寸，都大于中等尺寸和小尺寸：

特判两件衣服尺码的最后一个字符是否是 L，若是，比较另一件衣服：

- 若仅为一个字符 M 或最后一个字符是 S，这件衣服小；
- 否则，进入第四个函数。

#### 字符 S 前的字符 X 越多，尺寸越小：

从字符串开头开始遍历字符串，若字符为 X，则将计数器加上 $1$，随后比较两个字符的计数器：计数器大的衣服小。

#### 字符 L 前的字符 X 越多，尺寸越大：

从字符串开头开始遍历字符串，若字符为 X，则将计数器加上 $1$，随后比较两个字符的计数器：计数器大的衣服大。

### 代码

这里给出函数 1 的代码，其他代码大同小异：

```cpp
class Clothes
{
private:
	std::string c1;
	std::string c2;
public:
	Clothes();
	bool CheckS(std::string s1,std::string s2);
	bool CheckL(std::string s1,std::string s2);
	bool CheckXS(std::string s1,std::string s2);
	bool CheckXL(std::string s1,std::string s2);
}

inline Clothes::Clothes(){ 
	...;
}

//true:2 big
//false:1 big


inline Clothes::CheckS(std::string __s1,std::string __s2){
	int len1=__s1.size();
	int len2=__s2.size();
	return (__s1[len1-1]=='S')?((__s2[0]=='M'||__s2[len1-1]=='L')?true:false):((__s1[0]=='M'||__s1[len2-1]=='L')?false:true);
}
```

---

## 作者：BlackPanda (赞：1)

**[problem](https://www.luogu.com.cn/problem/CF1741A)**


------------
### 题意：

有 $n$ 次询问，每次给出 $2$ 个衣服的尺码，比较它们的大小。

比较规则如下：

- 无论前面有多少个字符 X 的小尺寸，都小于中等尺寸和大尺寸；

- 无论前面有多少个字符 X 的大尺寸，都大于中等尺寸和小尺寸；

- 字符 S 前的字符 X 越多，尺寸越小；

- 字符 L 前的字符 X 越多，尺寸越大。

------------
### 思路：

简单的模拟题。

先特判两个尺码是否相等，是的话输出 $\verb!=!$。

然后取出每个尺码的最后一个字符，即为尺寸。

然后枚举找出每个尺码前 $\verb!X!$ 的个数，最后根据比较规则分类讨论即可。

------------
### code：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
string s1, s2;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i ++ )
    {
        cin >> s1 >> s2;
        if (s1 == s2)
        {
            cout << "=\n";
        }
        else
        {
            char c1 = s1[s1.length()-1];
            char c2 = s2[s2.length()-1];
            //cout << c1 << " " << c2 << endl;
            int r1=0, r2=0;
            for (int i = 0; i < s1.length(); i ++ )
                if (s1[i] == 'X')   r1 ++ ;
            for (int i = 0; i < s2.length(); i ++ )
                if (s2[i] == 'X')   r2 ++ ;
            if (c1 == c2)
            {
                if (c1 == 'S')
                {
                    if (r1 > r2)    cout << "<\n";
                    else cout << ">\n";
                }
                else
                {
                    if (r1 < r2)    cout << "<\n";
                    else cout << ">\n";
                }
            }
            else
            {
                if ((c1=='M'&&c2=='S')||(c1=='L'&&c2=='M')||(c1=='L'&&c2=='S'))
                    cout << ">\n";
                else   
                    cout << "<\n";
            }
        }
    }
    return 0;
}

```

---

## 作者：LeNotFound (赞：1)

### 题意简述  
输入两个字符串 $a$ 和 $b$，表示两件衣服的尺码，要求比较两件衣服的大小，并输出对应的表示关系的符号。  

衣服的有 L，M 和 S 三种尺码，M 表示中等，S 表示小，L 表示大，字母 X 表示额外的大小，X 的数量越多，程度也就越深。  

比较大小的规则：  

* 任意的 S 尺码都**小于**任意的 M 尺码和任意的 L 尺码，无论带有多少个 X  
* 任意的 L 尺码都**大于**任意的 M 尺码和任意的 S 尺码，无论带有多少个 X  
* S 前边的 X 数量越多，尺码越**小**  
* L 前边的 X 数量越多，尺码越**大**  

不知道是不是你谷爬虫的原因，~~把人家 LaTex 的源码给爬过来了~~，实际上输出应该只包含 $<$ $>$ 和 $=$ 这三种情况。  

### 题目分析  
主要考察模拟能力和对分支语句的掌控，只要列举好情况然后分类讨论即可。  

* 我们先考虑相等的情况，显然，直接判断 string 是否相等即可。  
* 然后再考虑不同的情况，这种情况我们只需要比较最后一个字符即可。  
	* 对于末尾字符相同的情况，要比较字符串 $a$ 和 $b$ 的长度。
   * 对于末尾字符不同的情况，根据排列组合一共有 $2 \cdot C_3^2 = 6$ 种情况，需要分别判断字符串 $a$ 和 $b$ 的末尾字符比较大小。  

具体实现看代码吧  

### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

void solution()
{
    string a, b;
    cin >> a >> b;

    if (a == b)
    {
        cout << "=" << endl;
        return;
    }

    if (a.back() == b.back())
    {
        if (a.back() == 'L')
        {
            if (a.length() > b.length())
            {
                cout << ">" << endl;
                return;
            }
            else
            {
                cout << "<" << endl;
                return;
            }
        }
        if (a.back() == 'S')
        {
            if (a.length() < b.length())
            {
                cout << ">" << endl;
                return;
            }
            else
            {
                cout << "<" << endl;
                return;
            }
        }
    }
    else if (a.back() == 'L' && b.back() == 'S')
    {
        cout << ">" << endl;
        return;
    }
    else if (a.back() == 'S' && b.back() == 'L')
    {
        cout << "<" << endl;
        return;
    }
    else if (a.back() == 'L' && b == "M")
    {
        cout << ">" << endl;
        return;
    }
    else if (a.back() == 'S' && b == "M")
    {
        cout << "<" << endl;
        return;
    }
    else if (a == "M" && b.back() == 'L')
    {
        cout << "<" << endl;
        return;
    }
    else if (a == "M" && b.back() == 'S')
    {
        cout << ">" << endl;
        return;
    }
}

int main()
{
    ll T = 0;
    T = read();
    for (ll i = 0; i < T; i++)
    {
        solution();
    }
    return 0;
}
```
tips：函数中每当这个分支完成且不必再往下进行的时候，直接 return 掉是个好习惯，可以避免很多错误。

---

## 作者：_FJX_ (赞：0)

题意：  
给定两个尺码，让你比较它们的大小

细节：  
尺码有 $S$、$M$、$L$ 三类，其中只有 $M$ 码前不会有 $X$。

思路：  
分两类讨论：  
    1.异类：比较末尾字符所指向的类别，然后输出比较结果。  
    2.同类：查找 $X$ 的个数，再根据加 $X$ 后的比大小规则输出结果。

---

## 作者：ImposterAnYu (赞：0)

# 解析
根据题意，我们很容易就可以得知：

1. 无论 `S` 前面加多少个 `X`，都比 `M` 小。
2. 无论 `L` 前面加多少个 `X`，都比 `M` 大。
3. `S` 前面的 `X` 越多，尺码越小。
4. `L` 前面的 `X` 越多，尺码越大。

于是，我们在读入两个尺码 $a$ 和 $b$ 之后，可以先看 $a$ 和 $b$ 的最后一位，如果相同且不为 `M` 的话（如果是 `M` 的话肯定相等，因为 `M` 的前面不会有 `X`），就根据 $a$ 和 $b$ 前面的 `X` 的个数来比较大小（依据是后两条规则）。如果不相同的话，就直接根据前两条规则来判断就好了。

# AC code
```c++
#include<bits/stdc++.h>
#define int1 long long
#define p 11
using namespace std;
int1 t,la,lb;
char a[55],b[55],aa,bb;
int1 read(){
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void print(int1 x){
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar(x % 10 + 48);
  	return ;
}
int main(){
	t = read();
	while(t--){
		cin >> a >> b;//其实这里用 scanf 会更快，但是因为是赛时写的，就没想那么多了（bushi）
		la = strlen(a),lb = strlen(b),aa = a[la - 1],bb = b[lb - 1];//找出两个尺码的最后一个字母
		if(aa == bb){//如果相同则按 X 的个数来比较
			if((la < lb && aa == 'S') || (la > lb && aa == 'L')){
				printf(">\n");
			}else if((la > lb && aa == 'S') || (la < lb && aa == 'L')){
				printf("<\n");
			}else{
				printf("=\n");
			}
		}else{//不同则直接按最后一位来比较
			if((aa == 'L' && (bb == 'M' || bb == 'S')) || (aa == 'M' && bb == 'S')){
				printf(">\n");
			}else if((aa == 'S' && (bb == 'M' || bb == 'L')) || (aa == 'M' && bb == 'L')){
				printf("<\n");
			}else{
				printf("=\n");
			}
		}
	}
	return 0;
}
```

---

## 作者：Tomato_Ya (赞：0)

## 题意
有 $t$ 组数据，每组数据给你两个字符串，代表两件衣服的尺码，让你比较这两件衣服的大小。
## 思路
首先我们要知道不同的尺码的比较：

$$\cdots >\tt XXL>XL>L>M>S>XS>XXS>\cdots$$

其中，如果最后一个字符是 $\tt L$，那么前面的 $\tt X$ 越多，这件衣服的尺码就越大。反之，如果最后的字符是 $\tt S$，前面的 $\tt X$ 越多，这件衣服就越小。

我们输入字符串后，先比较每个字符串最后一个字符，就会有两种情况出现：

1. 如果相等，再判断两个字符串的长度是否相等，如果相等，就说明这两件衣服的尺码相等。如果不相等，由于我们之前判断过两个字符串最后一个字符都是相等的，所以不同之处就是字符串前面的 $\tt X$ 数不同，比较字符串的长度。当最后的字符是 $\tt S$ 时，第一个字符串长就是小于，反之大于。当最后的字符是 $\tt L$ 时，第一个字符串长就是大于，反之小于。

2. 如果不同,判断所有情况，如果第一个字符串最后一个字符小于第二个字符串的最后一个字符，就是小于，反之大于。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string a, b;
int main(){
    scanf("%d", &t);
    while(t --){
        cin >> a >> b;
        int la = a.size() - 1, lb = b.size() - 1;
        if(a[la] == b[lb]){
            if(la == lb) cout << "=\n";
            else if(a[la] == 'S' && la > lb) cout << "<\n";
            else if(a[la] == 'S' && la < lb) cout << ">\n";
            else if(a[la] == 'L' && la > lb) cout << ">\n";
            else if(a[la] == 'L' && la < lb) cout << "<\n";
        }
        else{
            if(a[la] == 'S' && b[lb] == 'M') cout << "<\n";
            else if(a[la] == 'M' && b[lb] == 'L') cout << "<\n";
            else if(a[la] == 'S' && b[lb] == 'L') cout << "<\n";
            else if(a[la] == 'L' && b[lb] == 'M') cout << ">\n";
            else if(a[la] == 'L' && b[lb] == 'S') cout << ">\n";
            else if(a[la] == 'M' && b[lb] == 'S') cout << ">\n";
        }
    }
    return 0;
}
```


---

## 作者：little_cindy (赞：0)

## 1 题意简述

给定两个衣服尺码，请比较它们的大小。

## 2 思路

### 2.1 比较最后一位

设第一个尺码为 $s_1$，第二个为 $s_2$。

首先看是尺码最后一位：

| ${s_1\atop \downarrow}{s_2\atop\rightarrow}$ |   $\text{S}$    | $\text{M}$ |   $\text{L}$    |
| :------------------------------------------: | :-------------: | :--------: | :-------------: |
|                  $\text{S}$                  | 见 $\text{2.2}$ |    $<$     |       $<$       |
|                  $\text{M}$                  |       $>$       |    $=$     |       $<$       |
|                  $\text{L}$                  |       $>$       |    $>$     | 见 $\text{2.3}$ |

### 2.2 对于末尾都是 $\text{S}$ 的

显然，我们可以发现，$\text{X}$ 越多，尺码越小。

考虑到 $\text{X}$ 的个数为 $s$ 的长度减去 $1$，显然只需比较 $s_1$ 和 $s_2$ 的长度即可（对于末尾都是 $\text{S}$ 的，长度越大，尺码越小）。

### 2.3 对于末尾都是 $\text{L}$ 的

类似 $\text{2.2}$，我们可以得到对于末尾都是 $\text{L}$ 的，长度越大，尺码越大。

## 3 code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
template <typename T>
inline void read(T &x)
{
    x = 0;
    T f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    x = x * f;
    return;
}
template <typename T, typename... Arg>
void read(T &x, Arg &...arg)
{
    read(x);
    read(arg...);
}
template <typename T>
inline void write(T x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x < 10)
        putchar(x + '0');
    else
        write(x / 10), putchar(x % 10 + '0');
}
template <typename T, typename... Arg>
void write(T &x, Arg &...arg)
{
    write(x);
    putchar(' ');
    write(arg...);
}
int num(char c)
{
    switch (c)
    {
    case 'S':
    {
        return -1;
    }
    case 'M':
    {
        return 0;
    }
    case 'L':
    {
        return 1;
    }
    }
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        string a, b;
        cin >> a >> b;
        if (num(a[a.size() - 1]) > num(b[b.size() - 1]))
        {
            \\以下的代码只是将思路的部分简化
                puts(">");
            continue;
        }
        else if (num(a[a.size() - 1]) == num(b[b.size() - 1]))
        {
            if (num(a[a.size() - 1]) * a.size() < num(b[b.size() - 1]) * b.size())
            {
                puts("<");
                continue;
            }
            else if (a.size() == b.size())
            {
                puts("=");
                continue;
            }
            else
            {
                puts(">");
                continue;
            }
        }
        else
        {
            puts("<");
        }
    }
    return 0;
}
```

---

## 作者：cyhtxdy (赞：0)

很简单的分支结构模拟。

可以分成两大类进行操作：大小类型相同和不相同的（大，中，小）。

大小类型相同的直接按照比较规则比较 `s` 的数量即可。

大小类型不相同的需要分类讨论，也是按照比较规则比较大小类型。

思路很简洁，给出代码：

```
#include <bits/stdc++.h>

using namespace std;

int main () {
	int T;
	cin >> T;
	while (T --) {
		string s1, s2;
		cin >> s1 >> s2;
		char a1 = s1[s1.size () - 1], a2 = s2[s2.size () - 1];
		if (a1 == a2) {//大小类型相同 
			if (s1.size () == s2.size ()) {//s数量相同 
				cout << '=' << endl;
			}
			else if (a1 == 'S') {
				cout << (s1.size () > s2.size () ? '<' : '>') << endl;
			}
			else if (a1 == 'L') {
				cout << (s1.size () < s2.size () ? '<' : '>') << endl;
			}
		}
		else {//大小类型不相同 
			if (a1 == 'L') {
				cout << '>' << endl;
			}
			else if (a1 == 'S') {
				cout << '<' << endl;
			}
			else if (a1 == 'M') {
				cout << (a2 == 'S' ? '>' : '<') << endl;
			}
		}
	}
	return 0;
}
```


---

## 作者：mzyc_yang2021 (赞：0)

题意：判断两个号码的大小。

大小规则：

在末尾不同的情况下，带 S 的更小，带 L 的更大，带 M 的则介于两者之间。

末尾同为 S 的情况下，带 X 越少则越大。

末尾同为 L 的情况下，带 X 越多则越大。

实现：输入字符串，暴力比对即可。

代码（加解释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s1,s2;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s1>>s2;
		int l1=s1.size(),l2=s2.size();
		if(s1[l1-1]=='M'&&s2[l2-1]=='M'){cout<<"="<<"\n";continue;} //同为M一样 
		else if(s1[l1-1]=='S'&&s2[l2-1]=='S') //同为S 
		{
			if(l1>l2) cout<<"<"<<"\n"; //X越多越小，反之更大 
			else if(l1<l2) cout<<">"<<"\n";
			else cout<<"="<<"\n";
			continue;
		}
		else if(s1[l1-1]=='L'&&s2[l2-1]=='L') //同为L
		{
			if(l1>l2) cout<<">"<<"\n";//X越多越大，反之更小 
			else if(l1<l2) cout<<"<"<<"\n";
			else cout<<"="<<"\n";
			continue;
		}
		if(s1[l1-1]=='S'){cout<<"<"<<"\n";continue;} //哪个带S哪个小 
		if(s2[l2-1]=='S'){cout<<">"<<"\n";continue;}
		if(s1[l1-1]=='L'){cout<<">"<<"\n";continue;} //哪个带L哪个大 
		if(s2[l2-1]=='L'){cout<<"<"<<"\n";continue;}
		if(s1[l1-1]=='M') //带M就判断 
		{
			if(s2[l2-1]=='S') cout<<">"<<"\n";
			else cout<<"<"<<"\n";
			continue;
		}
		if(s2[l2-1]=='M')
		{
			if(s1[l1-1]=='S') cout<<"<"<<"\n";
			else cout<<">"<<"\n";
			continue;
		}
	}
	return 0;
}
```


---

