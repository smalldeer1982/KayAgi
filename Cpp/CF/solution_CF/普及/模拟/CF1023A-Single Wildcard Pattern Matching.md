# Single Wildcard Pattern Matching

## 题目描述

给定两个小写英文单词 $s,t$，其中 $s$ 包含还不多于一个的 `*`。$s$ 的长度为 $n$，而 $t$ 的长度为 $m$。

$s$ 中的 `*` 可以被替换为任意小写字母串（可以是空串），但其他字母不能被更改或者调换顺序。如果将 `*` 替换为一个任意小写字母串之后，$s=t$，那么我们称 $s,t$ 是匹配的。

例如，字符串 $s=$ `lu*gu` 与 `luogu` `lugu` `luooooogu`都是匹配的，但与字符串 `lougu` `log` `lu^_^gu` `lu114514gu` 都是不匹配的。

如果给定的 $s,t$ 是匹配的，输出 `YES`，否则输出 `NO`。

## 说明/提示

对于 $100\%$ 的数据，$1\le n,m\le2\times10^5$。

$\mathrm{by\ @}$[$\mathrm{Fish\_Know\_Forever}$](/user/663215)

## 样例 #1

### 输入

```
6 10
code*s
codeforces
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
6 5
vk*cup
vkcup
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
1 1
v
k
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
9 6
gfgf*gfgf
gfgfgf
```

### 输出

```
NO
```

# 题解

## 作者：StudyingFather (赞：4)

这是一道经典的带通配符的字符串匹配问题。

问号的匹配比较容易，因为问号只能代替一个字符，遇到问号直接匹配即可。但星号却能代替0个或多个字符。

我们可以先判断\*前的字符串，如果失配，显然可以输出-1.

如果遇到\*号的话，我们可以将星号的位置记录下来，然后从后往前扫描。

当s的长度n与t的长度m满足n>m+1时，说明匹配失败（因为即使\*代替的内容为空，n的最大长度也只是m+1，当 * 代替的字符串不为空时，显然会满足n>=m）。

接下来从后往前扫描时，只要s与t对应的字母相等，当字符串s匹配到\*时，说明匹配成功。

```cpp
#include <stdio.h>
char s1[200005],s2[200005];
int main()
{
 int n,m;
 scanf("%d%d",&n,&m);
 scanf("%s",s1);
 scanf("%s",s2);
 int flag=1;
 for(int i=0;i<=n;i++)
  if(s1[i]=='*')
  {
   flag=-1;
   break;
  }
  else if(s1[i]=='?')continue;
  else if(s1[i]!=s2[i])
  {
   flag=0;
   break;
  }
 if(flag==1)puts("YES");
 else if(flag==0)puts("NO");
 else
 {
  for(int i=n-1,j=m-1;;i--,j--)
   if(s1[i]=='*')
   {
   	if(i-1>j)flag=0;
   	else flag=1;
   	break;
   }
   else if(s1[i]=='?')continue;
   else if(s1[i]!=s2[j])
   {
    flag=0;
    break;
   }
  if(flag)puts("YES");
  else puts("NO");
 }
 return 0;
}
```

---

## 作者：vanueber (赞：2)

[CF 原题传送门](https://codeforces.com/problemset/problem/1023/A)

# 题目大意

给定两个字符串，其中可能有一个字符 $\texttt * $ ，可以替换为任意字串，问两个字串能不能相等。

# 题目分析

分成以下情况讨论。

1. 如果 $\texttt * $ 字符代表空，第一个串的长度应该大于第二个长度加一，不符合则输出 $\texttt No $。
2. 枚举每一位，如果在遇到 $\texttt * $ 前就不匹配，输出 $\mathtt{No}$。
3. 找到 $\texttt * $，则从字符串的后面开始比较。
4. 最后特判一下，当 $\texttt * $ 在最后一个字符的情况。

具体实现见代码。

# 代码

```cpp
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int l1,l2;
string s1,s2;

int main()
{
	cin>>l1>>l2>>s1>>s2;
	if(l1>l2+1)
	{
		cout<<"No"<<endl;
		return 0;
	} 
	if(s1==s2)
	{
		cout<<"Yes";
		return 0;
	}
	for(int i=0;i<min(s1.size(),s2.size());i++)
	{
		if(s1[i]=='*')
		{
			if(s1.size()-1>s2.size())
			{
				printf("No\n");
				return 0;
			}
			else
			{
				int p1=s1.size(),p2=s2.size();
				while(true)
				{
					if(s1[p1]!=s2[p2])
					{
						printf("No\n");
						return 0;
					}
					--p1,--p2;
					if(s1[p1]=='*')
					{
						printf("Yes\n");
						return 0;
					}
				}
			}
		}
		if(s1[i]!=s2[i])
		{
			printf("No\n");
			return 0;
		}
	}
	bool flag=true;
	for(int i=0;i<s1.size()-1;i++)
	{
		if(s1[i]!=s2[i])
		{
			flag=false;
			break;
		}
	}
	if(flag&&s1[s1.size()-1]=='*')
	{
		printf("Yes");
		return 0;
	}
	printf("No\n");
	return 0;
}
```
[AC记录](https://codeforces.com/problemset/submission/1023/218747536)

---

## 作者：小闸蟹 (赞：2)

```cpp
// 字符串模拟题
// 首先先特判掉"n > m + 1"的情况，因为第一个字符串都比第二个字符串长，那肯定不行
// 然后特判掉没有'*'的情况，直接两个字符串匹配即可
// 接着找到'*'的位置，以此分割第一个字符串，从前往后和从后往前去匹配第二个字符串
// 一旦出现任何失配，则输出"NO"，否则输出"YES"
#include <iostream>
#include <string>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    if (n > m + 1)  // 特判长度
    {
        std::cout << "NO" << std::endl;

        return 0;
    }

    std::string Str1, Str2;
    std::cin >> Str1 >> Str2;

    auto Pos = Str1.find('*');
    if (Pos == std::string::npos)   // 没有'*'的情况
    {
        if (Str1 == Str2)
        {
            std::cout << "YES" << std::endl;
        }
        else
        {
            std::cout << "NO" << std::endl;
        }
    }
    else
    {
        auto p = static_cast<int>(Pos);
        for (int i = 0; i < p; ++i) // 从前往后扫
        {
            if (Str1[i] != Str2[i])
            {
                std::cout << "NO" << std::endl;

                return 0;
            }
        }
        for (int i = n - 1, j = m - 1; i > p; --i, --j) // 从后往前扫
        {
            if (Str1[i] != Str2[j])
            {
                std::cout << "NO" << std::endl;

                return 0;
            }
        }

        std::cout << "YES" << std::endl;
    }

    return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：1)

## CF1023A Single Wildcard Pattern Matching 题解
### 思路

很简单的一道字符串题。

问号的匹配比较容易，因为问号只能代替一个字符，遇到问号直接匹配即可。但星号会对匹配产生影响，我们可以这么做：

- 若没有 `*` 号，则将两个字符串逐位比较。

- 若有 `*` 号，则将 `*` 号前 $a$ 字符串和 $b$ 对应的字符串比较，`*` 后则相反。

### 代码

```cpp
#include<assert.h> 
#include<ctype.h> 
#include<errno.h> 
#include<float.h> 
#include<math.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 
#include<wchar.h> 
#include<wctype.h>
#include<algorithm> 
#include<bitset> 
#include<cctype> 
#include<cerrno> 
#include<clocale> 
#include<cmath> 
#include<complex> 
#include<cstdio> 
#include<cstdlib> 
#include<cstring> 
#include<ctime> 
#include<deque> 
#include<exception> 
#include<fstream> 
#include<functional> 
#include<limits> 
#include<list> 
#include<map> 
#include<iomanip> 
#include<ios> 
#include<iosfwd>
#include<iostream> 
#include<istream> 
#include<ostream> 
#include<queue> 
#include<set> 
#include<sstream> 
#include<stack> 
#include<stdexcept> 
#include<streambuf> 
#include<string> 
#include<utility> 
#include<vector> 
#include<cwchar> 
#include<cwctype>
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int maxn=2e5+10;
int n,m,op;
char a[maxn],b[maxn];
bool vis[maxn];
int main()
{
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]=='*')
		{
		    op=i;
		}
	}	
	for(int i=1;i<=m;i++)
	{
	    cin>>b[i];
	}
	if(op==0)
	{
		bool flag=true;
		if(n==m)
		{
			for(int i=1;i<=n;i++)
			{
				if(a[i]!=b[i])
				{
					flag=false;
					break;
				}
			}
		} 
		else flag=false;
		if(flag)
	    {
	        cout<<"YES"<<endl;
	    }
	    else
	    {
	        cout<<"NO"<<endl;
	    }
		return 0;
	}
	bool flag=true;
	if(n-1>m)
	{
	    flag=false;
	}
	else 
	{
		for(int i=1;i<op;i++)
		{
			if(a[i]!=b[i])
			{
				flag=false;
				break;
			}
		}
		for(int i=n;i>op;i--)
		{
			if(a[i]!=b[m-n+i])
			{
				flag=false;
				break;
			}
		}
	}
	if(flag)
	{
	    cout<<"YES"<<endl;
	}
	else
	{
	    cout<<"NO"<<endl;
	}
	exit(0);
} 

---

## 作者：To_Carpe_Diem (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1023A)

# 题目主要内容
题目要求判断给定两个字符串 $s$ 和 $t$ 是否匹配。字符串 $s$ 可以包含一个通配符，它可以表示**任意长度**的字符序列。如果可以通过**替换** $s$ 中的**通配符**来得到字符串 $t$，则表示匹配。

# 主要知识:
字符串处理：包括字符串的**比较**，**截取**，**查找**等操作。

字符串匹配：根据题目要求进行**字符串匹配**，判断**两个字符串**是否相等或**部分匹配**。

这道题目主要涉及到了字符串的**匹配和处理**，以及一些相关的字符串操作函数。通过观察字符串中的**通配符和使用字符串匹配的方式**，可以判断给定的字符串**是否匹配**。

# AC Code:

```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    if (s == t) {
        cout << "YES" << endl;
    } else if (s.find('*') != string::npos) {
        int wildcard_pos = s.find('*');
        string s_prefix = s.substr(0, wildcard_pos);
        string s_suffix = s.substr(wildcard_pos+1);
        if (t.length() >= s.length()-1 && t.substr(0, s_prefix.length()) == s_prefix && t.substr(t.length()-s_suffix.length()) == s_suffix) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    } else {
        cout << "NO" << endl;
    }
    return 0;
}

```

---

## 作者：happybob (赞：1)


我想到用正则表达式，`c++11` 以上只要加上头文件 `<regex>` 即可使用，正则表达式使用方法参见：[百度百科](https://baike.baidu.com/item/%E6%AD%A3%E5%88%99%E8%A1%A8%E8%BE%BE%E5%BC%8F/1700215)。

`c++` 中正则表达式定义如下：

```
regex reg(...);
```

~~然后我就挂了。~~


不是 `RE` 就是 `TLE`，反正数据太毒瘤，数据量太大，`regex` 受不起。想到一个方法：对比前面和后面字符，都一样就全删了。

因为 `regex` 毕竟是 `STL` 的东西，`STL` 的一个明显问题就是时间复杂度。

顺带提一下的是，本题考的做法不是 `regex`，虽然 `regex` 也可以过，但是正路还是 `string` 模拟。

本题的思路其实很简单：因为我们要用 `regex` 模拟，所以 `regex` 的表达式应该为 `a中*的前面的字符` + `若干个（大于等于0个）小写字母` + `a中*后面的字符`。所以我们只需要找到 `*` 的位置，然后用 `substr` 截取即可。但是不要忘记没有 `*` 等特判。

- 如果字符串 `a` 中没有 `*`，那 `a` 和 `b` 必须相等才是 `YES`。
- 如果 `a` 的长度和 `b` 相等，那只有可能 `a` 中除了 `*` 外都和 `b` 相等，不然就无法匹配。

代码三番五次地改，终于 `AC` 了：

```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <regex>
using namespace std;

string a, b;

int main()
{
	int lena, lenb;
	cin >> lena >> lenb;
	cin >> a >> b;
	if (a.length() - 1 > b.length()) // 一堆特判
	{
		cout << "NO\n";
		return 0;
	}
	if (a == b)
	{
		cout << "YES\n";
		return 0;
	}
	int tims = 0;
	while (a[a.length() - 1] == b[b.length() - 1] && tims <= lena / 10000)
	{
		a.pop_back(); 
		b.pop_back();
		tims++;
	}
	tims = 0;
	while (a[0] == b[0] && tims <= lena / 10000)
	{
		a.erase(a.begin()); 
		b.erase(b.begin());
		tims++;
	}
	if (a[0] == '*' && a.length() == b.length())
	{ 
		a.erase(a.begin());
		b.erase(b.begin());
		cout << (a == b ? "YES\n" : "NO\n");
		return 0;
	}
	if (a[0] == '*')
	{
		b = b.substr(b.length() - (a.length() - 1), a.length() - 1);
		a.erase(a.begin());
		cout << (a == b ? "YES\n" : "NO\n");
		return 0;
	}
	int lens = a.length();
	int lns = b.length();
	int place = a.find("*"); 
	for (register int i = 0; i < place; i++)
	{
		if (a[i] != b[i])
		{
			cout << "NO\n";
			return 0;
		}
	}
	if (a[0] != '*' && a[0] != b[0])
	{
		cout << "NO\n";
		return 0;
	}
	if (lens - 1 > lns)
	{
		cout << "NO\n";
		return 0;
	}
	if (lens - lns == 1)
	{
		if (place == string::npos)
		{
			cout << "NO\n";
			return 0;
		}
		a.erase(place, 1);
		/*cout << "a: " << a << endl;
		cout << "b: " << b << endl;
		*/
		if (a != b)
		{
			cout << "NO\n";
		}
		else cout << "YES\n";
		return 0;
	}
	if (lens == lns)
	{
		if (place == string::npos)
		{
			cout << "NO\n";
			return 0;
		}
		for (register char x = 'a'; x <= 'z'; x++)
		{
			a[place] = x;
			if (a == b)
			{
				cout << "YES\n";
				return 0;
			}
		}
		cout << "NO\n";
		return 0;
	}
	if (place == string::npos && a != b) 
	{
		cout << "NO\n";
		return 0;
	}
	string sub_first = a.substr(0, place);
	string sub_last = a.substr(place + 1, (lens - 1) - place);
	string regs = (sub_first + "[a-z]*" + sub_last);
	regex reg(regs);
	try
	{
		if (regex_match(b, reg))
		{
			cout << "YES\n";
		}
		else cout << "NO\n";
	}
	catch (const std::regex_error& err) // 当时为了避免 RE 不知道错误位置加的
	{
		cout << "There is an error. The error is:" << err.what() << endl;
	}
	return 0;
}
```


---

## 作者：Chinshyo (赞：1)

# 我的思路
我的思路就是将整个输入的 $s1$ 字符串与 $s2$ 进行比对。在此过程中，我们分别从开头到结尾各做一次循环，记录下是从什么时候开始不一样的。我们拿样例举例：

![](https://cdn.luogu.com.cn/upload/image_hosting/e7is09ab.png)

图中的红色框就是我们即将用来代替“ $*$ ”的。所以**只要将红色框内的东西判断一下大小写**就好了。
# 吹毛求疵
这道题有一个坑。首先样例中有过找不到“ $*$ ”号的情况，如果有这种情况我们这种算法是会出问题的。所以我们加一句话来判断这个是否合格：

```cpp
if(s1.find('*') == s1.npos){ //如果找不到*号
	cout << "NO" << endl;
	return 0; //直接再见
}
```
# 贴代码

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n1, n2;//无脑输入
	cin >> n1 >> n2;
	string s1, s2;
	cin >> s1 >> s2;
	if(s1.find('*') == s1.npos){
		cout << "NO" << endl;
		return 0;
	}
	
	int fr;//寻找起点终点
	for(int i = 0; i < s1.size(); i++){
		if(s1[i] != s2[i]){
			fr = i;
			break;
		}
	}
	int bc;
	for(int i = s1.size()-1; i <=0; i--){
		if(s1[i] != s2[i]){
			bc = i;
			break;
		}
	}
	
	for(int i = fr; i <= bc; i++){
		if(!islower(s2[i])){ //判断是否小写
			cout << "NO" << endl;
			return 0; //有不是小写的先再见
		}
	}
	cout << "YES" << endl;
	return 0;
} 
```


---

## 作者：2012zxt (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1023A)

# 1.思路

~~库函数模板题~~

本题确实简单，只要你对字符串库函数掌握的还不错这道题就能做。

先考虑什么时候它俩能相等。

首先，因为那个
`*`
可以配任何字符串，所以不能配的就是其他的部分，所以我们可以把
`*`
前面的和后面的都标记位置并在 $t$ 中截取，拼接成一个字符串，然后看它和 $s$ 串是不是一样的，如果一样就是 
`YES`
，否则是 
`NO`
。

# 2.代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,pos;
string s,t;
bool flag;//flag表示s中有没有星号
int main(){
	cin>>n>>m>>s>>t;
	if(n>m+1){//我的长度比你大两个以上，肯定不行
		cout<<"NO";
		return 0;
	}
	s="#"+s;//让有效下标从1到n
	t="#"+t;
	for(int i=1;i<=n;i++)
		if(s[i]=='*')
			flag=1,pos=i;//出现了！星号！存一下位置
	if(!flag){//没有星号，听天由命
		if(s==t)
			cout<<"YES";
		else cout<<"NO";
		return 0;
	}
	int tmp1=n-pos;//存一下星号后面的字符个数
	string tmp2=t.substr(1,pos-1)+t.substr(m-tmp1+1);//如上拼接。
	s=s.substr(1,pos-1)+s.substr(pos+1);//把星号去掉好比较
	if(s==tmp2)
		cout<<"YES";
	else cout<<"NO";
	return 0;
}

```

---

