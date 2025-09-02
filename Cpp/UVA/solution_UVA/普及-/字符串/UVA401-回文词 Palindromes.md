# 回文词 Palindromes

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=342

[PDF](https://uva.onlinejudge.org/external/4/p401.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA401/b6c215fa795465f551b5ca7a97ddc3a7f22e50ab.png)

## 样例 #1

### 输入

```
NOTAPALINDROME
ISAPALINILAPASI
2A3MEAS
ATOYOTA```

### 输出

```
NOTAPALINDROME -- is not a palindrome.

ISAPALINILAPASI -- is a regular palindrome.

2A3MEAS -- is a mirrored string.

ATOYOTA -- is a mirrored palindrome.```

# 题解

## 作者：Andorxor (赞：12)

输入字符串，用字符数组rev预存好镜像字符，遍历字符串看每个字符是否都符合镜像或回文的要求，只要出现一个不符合镜像或回文的字符，该字符串就一定不是镜像或回文字符串（类似于质数判定）。

用两个标记来排列组合判断是四种情况中的哪一种，直接对应输出。

```cpp
#include<bits/stdc++.h>
using namespace std;
char rev[]="A   3  HIL JM O   2TUVWXY51SE Z  8 ";
char s[100];
int hw,jx;
char getrev(char c){
    if(c>='A'&&c<='Z')
        return rev[c-'A'];
    else
        return rev[c-'0'+25];
}
int main(){
    while(cin>>s){
        int len=strlen(s);
        cout<<s;
        hw=0,jx=0;
        for(int i=0;i<(len+1)/2;i++){
            if(s[i]!=s[len-i-1])
                hw=1;
            if(getrev(s[i])!=s[len-i-1])
                jx=1;
        }			
        if(!hw&&!jx)
            cout<<" -- is a mirrored palindrome."<<endl<<endl;
        else if(!hw&&jx)
            cout<<" -- is a regular palindrome."<<endl<<endl;
        else if(hw&&!jx)
            cout<<" -- is a mirrored string."<<endl<<endl;
        else
            cout<<" -- is not a palindrome."<<endl<<endl;
    }
    return 0;
}

```

尤其注意一点：每次输出的最后面都要换两次行才可以（其实洛谷的的输出样例每次输出后面都有一行空行的，只是不明显，这个问题使我连续误交了几次，都没发现哪里有问题）。


---

## 作者：algobase (赞：5)

一道主要考字符串的题目，虽然代码有点长，但是写起来并不难。

------------
主部分伪代码：

```cpp
if(是回文字符串)
{
	if(是镜像字符串)
	{
		printf("%s -- is a mirrored palindrome.\n", str);
	}
	else
	{
		printf("%s -- is a regular palindrome.\n", str);
	}
}
else if(是镜像字符串)
{
	printf("%s -- is a mirrored string.\n", str);
}
else
{
	printf("%s -- is not a palindrome.", str);
}
```
接下来就是判断回文串和镜像串。

- 回文串

这一部分比较简单，不多讲

```cpp
bool is_palidrome()
{
	for(int i = 0; i < len; i++)
	{
		if(str[i] != str[len - i - 1])
		{
			return 0;
		}
	}
	return 1;
}
```
- 镜像串

题目里有一张表，我们要按这张表转换字符，可以使用打表的方法。

打表程序：

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

char a, b;

int main()
{
	freopen("mirror.out", "w", stdout);
	
	while(cin >> a >> b)
	{
    	printf("mir['%c'] = '%c';\n", a, b);
	}
	
	fclose(stdout);
	
	return 0;
}
```
这时，表格就输出在文件里了，真方便（~~蒟蒻第一次打表~~）

------------
我们把上面的几个部分合在一起，便得到了以下完整代码：

```cpp
#include <cstdio>
#include <cstring>

using namespace std;

int mirror[256], len;
char str[1005];

bool is_palidrome()
{
	for(int i = 0; i < len; i++)
	{
		if(str[i] != str[len - i - 1])
		{
			return 0;
		}
	}
	return 1;
}

bool is_mirror_palidrome()
{
	for(int i = 0; i < len; i++)
	{
		if(mirror[str[i]] != str[len - i - 1])
		{
			return 0;
		}
	}
	return 1;
}

int main()
{
	mirror['A'] = 'A';
	mirror['E'] = '3';
	mirror['H'] = 'H';
	mirror['I'] = 'I';
	mirror['J'] = 'L';
	mirror['L'] = 'J';
	mirror['M'] = 'M';
	mirror['O'] = 'O';
	mirror['S'] = '2';
	mirror['T'] = 'T';
	mirror['U'] = 'U';
	mirror['V'] = 'V';
	mirror['W'] = 'W';
	mirror['X'] = 'X';
	mirror['Y'] = 'Y';
	mirror['Z'] = '5';
	mirror['1'] = '1';
	mirror['2'] = 'S';
	mirror['5'] = 'Z';
	mirror['8'] = '8';

	while(scanf("%s", str) == 1)
	{
		len = strlen(str);
		
		if(is_palidrome())
		{
			if(is_mirror_palidrome())
			{
				printf("%s -- is a mirrored palindrome.\n", str);
			}
			else
			{
				printf("%s -- is a regular palindrome.\n", str);
			}
		}
		else if(is_mirror_palidrome())
		{
			printf("%s -- is a mirrored string.\n", str);
		}
		else
		{
			printf("%s -- is not a palindrome.\n", str);
		}
	}
	
	return 0;
}
```
呀？为什么样例的第三个字符串输出的不是回文串？看来是表格的问题。我们仔细检查一下，发现 `mirror['E'] = '3';` ，而没写 `mirror['3'] = 'E';` ，所以我们要把这一句补上：

```cpp
#include <cstdio>
#include <cstring>

using namespace std;

int mirror[256], len;
char str[1005];

bool is_palidrome()
{
	for(int i = 0; i < len; i++)
	{
		if(str[i] != str[len - i - 1])
		{
			return 0;
		}
	}
	return 1;
}

bool is_mirror_palidrome()
{
	for(int i = 0; i < len; i++)
	{
		if(mirror[str[i]] != str[len - i - 1])
		{
			return 0;
		}
	}
	return 1;
}

int main()
{
	mirror['A'] = 'A';
	mirror['E'] = '3';
	mirror['H'] = 'H';
	mirror['I'] = 'I';
	mirror['J'] = 'L';
	mirror['L'] = 'J';
	mirror['M'] = 'M';
	mirror['O'] = 'O';
	mirror['S'] = '2';
	mirror['T'] = 'T';
	mirror['U'] = 'U';
	mirror['V'] = 'V';
	mirror['W'] = 'W';
	mirror['X'] = 'X';
	mirror['Y'] = 'Y';
	mirror['Z'] = '5';
	mirror['1'] = '1';
	mirror['2'] = 'S';
    mirror['3'] = 'E';
	mirror['5'] = 'Z';
	mirror['8'] = '8';

	while(scanf("%s", str) == 1)
	{
		len = strlen(str);
		
		if(is_palidrome())
		{
			if(is_mirror_palidrome())
			{
				printf("%s -- is a mirrored palindrome.\n", str);
			}
			else
			{
				printf("%s -- is a regular palindrome.\n", str);
			}
		}
		else if(is_mirror_palidrome())
		{
			printf("%s -- is a mirrored string.\n", str);
		}
		else
		{
			printf("%s -- is not a palindrome.\n", str);
		}
	}
	
	return 0;
}
```
但是，题目样例有一个地方格式错误，就是每一句话输出完之后要两个换行，否则 `PE`。

```cpp
#include <cstdio>
#include <cstring>

using namespace std;

int mirror[256], len;
char str[1005];

bool is_palidrome()
{
	for(int i = 0; i < len; i++)
	{
		if(str[i] != str[len - i - 1])
		{
			return 0;
		}
	}
	return 1;
}

bool is_mirror_palidrome()
{
	for(int i = 0; i < len; i++)
	{
		if(mirror[str[i]] != str[len - i - 1])
		{
			return 0;
		}
	}
	return 1;
}

int main()
{
	mirror['A'] = 'A';
	mirror['E'] = '3';
	mirror['H'] = 'H';
	mirror['I'] = 'I';
	mirror['J'] = 'L';
	mirror['L'] = 'J';
	mirror['M'] = 'M';
	mirror['O'] = 'O';
	mirror['S'] = '2';
	mirror['T'] = 'T';
	mirror['U'] = 'U';
	mirror['V'] = 'V';
	mirror['W'] = 'W';
	mirror['X'] = 'X';
	mirror['Y'] = 'Y';
	mirror['Z'] = '5';
	mirror['1'] = '1';
	mirror['2'] = 'S';
    mirror['3'] = 'E';
	mirror['5'] = 'Z';
	mirror['8'] = '8';

	while(scanf("%s", str) == 1)
	{
		len = strlen(str);
		
		if(is_palidrome())
		{
			if(is_mirror_palidrome())
			{
				printf("%s -- is a mirrored palindrome.\n\n", str);
			}
			else
			{
				printf("%s -- is a regular palindrome.\n\n", str);
			}
		}
		else if(is_mirror_palidrome())
		{
			printf("%s -- is a mirrored string.\n\n", str);
		}
		else
		{
			printf("%s -- is not a palindrome.\n\n", str);
		}
	}
	
	return 0;
}
```

这下子就能AC了

---

## 作者：JMercury (赞：2)

```cpp
#include<iostream>
using namespace std;

string ss;
string mirl="A   3  HIL JM O   2TUVWXY5"; ///字母镜像
string mirn=" 1SE Z  8 "; ///数字镜像

bool hw(string ss) ///判断回文：直接反转，判等
{
    string tmp="";
    int p=ss.size()-1;
    while(p>=0)
    {
        tmp=tmp+ss[p];
        p--;
    }
    return ss==tmp;
}

bool jx(string ss) ///判断镜像：生成新字串后反转判等
{
    string tmp="";
    string tmp2="";
    int p;
    for(p=0;p<=ss.size()-1;p++)
    {
        if(ss[p]>='A' && ss[p]<='Z')
            tmp+=mirl[ss[p]-'A'];
        else tmp+=mirn[ss[p]-'0'];
    }
    p=ss.size()-1;
    while(p>=0)
    {
        tmp2=tmp2+tmp[p];
        p--;
    }
    return ss==tmp2;
}

void work() 
{
    cout<<ss<<" -- "; ///先输出
    bool b1=hw(ss),b2=jx(ss); ///是否回文，是否镜像
    if(b1==false && b2==false) ///根据两种条件的四种组合按要求输出（常见错误：没有打句号，没有多空一行。。。）
        cout<<"is not a palindrome."<<endl<<endl;
    else if(b1==true && b2==false)
        cout<<"is a regular palindrome."<<endl<<endl;
    else if(b1==false && b2==true)
        cout<<"is a mirrored string."<<endl<<endl;
    else cout<<"is a mirrored palindrome."<<endl<<endl;
}

int main()
{
    while(cin>>ss)
        work();
    return 0;
}

```

---

## 作者：WanderingTrader (赞：1)

这题是道很简单的字符串题，模拟即可。
### 题目分析
算出字符串$s$是否回文，是否镜面，然后分情况输出即可。  
不过这里有个BUG：每次输出完毕后要再输出 **两个** 空行（而不是一个），所以样例输出应该是：
```
NOTAPALINDROME -- is not a palindrome.

ISAPALINILAPASI -- is a regular palindrome.

2A3MEAS -- is a mirrored string.

ATOYOTA -- is a mirrored palindrome.


```
注意文件结尾也有两个空行。
### 代码
框架：
```cpp
#include <bits/stdc++.h>
using namespace std;
bool is_p(const string& s,const int& l)
{
}
bool is_m(const string& s,const int& l)
{
}
int main(){
	string s;
	while(cin >> s)
	{
		int len = s.length();
		bool a = is_p(s,len),b = is_m(s,len);
		cout << s << " -- ";
		if(a)
		{
			if(b) printf("is a mirrored palindrome.");
			else printf("is a regular palindrome.");
		}
		else
		{
			if(b) printf("is a mirrored string.");
			else printf("is not a palindrome.");
		}
		printf("\n\n");
	}
	return 0;
}
```
然后我们完成两个“子任务”，即回文和镜面即可。  
1. 回文  
这个很简单，挨个位置判断即可。  
```cpp
bool is_p(const string& s,const int& l)
{
	for(int i = 0;i <= l / 2;i ++)
		if(s[i] != s[l - i - 1]) return 0;
	return 1;
}
```
注意下标，与$s[i]$相对应的应是$s[l-i-1]($而不是$s[l-i])$。 

2. 镜面  
这里我们又要借用打表的思想了，定义字符数组$mir[]$存放各个字符（下标为对应的ASCII码）镜面后的结果，如果无法镜面则为'\0'，也就是空字符。  
打表生成器很简单，如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	char a,b;
	freopen("mirror.out","w",stdout);
	while(cin >> a >> b)
	{
		printf("	mir['%c'] = '%c';\n",a,b);
	}
	return 0;
}
```
把题面里的这张表输进去：
```
A           A
E           3
H           H
I           I
J           L
L           J
M           M
O           O
S           2
T           T
U           U
V           V
W           W
X           X
Y           Y
Z           5
1           1
2           S
5           Z
8           8
```
打开mirror.out文件得到：
```
	mir['A'] = 'A';
	mir['E'] = '3';
	mir['H'] = 'H';
	mir['I'] = 'I';
	mir['J'] = 'L';
	mir['L'] = 'J';
	mir['M'] = 'M';
	mir['O'] = 'O';
	mir['S'] = '2';
	mir['T'] = 'T';
	mir['U'] = 'U';
	mir['V'] = 'V';
	mir['W'] = 'W';
	mir['X'] = 'X';
	mir['Y'] = 'Y';
	mir['Z'] = '5';
	mir['1'] = '1';
	mir['2'] = 'S';
	mir['5'] = 'Z';
	mir['8'] = '8';
```
程序自己也会写程序了！（可以这么理解）  
把它们复制粘贴到main函数开头（这就是为什么每行前要带一个TAB）：
```cpp
int main(){
	string s;
	mir['A'] = 'A';
	mir['E'] = '3';
	mir['H'] = 'H';
	mir['I'] = 'I';
	mir['J'] = 'L';
	mir['L'] = 'J';
	mir['M'] = 'M';
	mir['O'] = 'O';
	mir['S'] = '2';
	mir['T'] = 'T';
	mir['U'] = 'U';
	mir['V'] = 'V';
	mir['W'] = 'W';
	mir['X'] = 'X';
	mir['Y'] = 'Y';
	mir['Z'] = '5';
	mir['1'] = '1';
	mir['2'] = 'S';
	mir['5'] = 'Z';
	mir['8'] = '8';
	while(cin >> s)
	{
		int len = s.length();
		bool a = is_p(s,len),b = is_m(s,len);
		cout << s << " -- ";
		if(a)
		{
			if(b) printf("is a mirrored palindrome.");
			else printf("is a regular palindrome.");
		}
		else
		{
			if(b) printf("is a mirrored string.");
			else printf("is not a palindrome.");
		}
		printf("\n\n");
	}
	return 0;
}
```
但这里又有一个BUG：题目的表没给完整，少了一行：
```
3          E
```
因此代码中还要加上：
```cpp
mir['3'] = 'E';
```
有了这张表，$is\_m$函数就简单多了，和$is\_p$几乎一模一样：
```cpp
bool is_m(const string& s,const int& l)
{
	for(int i = 0;i <= l / 2;i ++)
		if(mir[s[i]] != s[l - i - 1]) return 0;
	return 1; 
}
```
全部代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200
char mir[N];
bool is_p(const string& s,const int& l)
{
	for(int i = 0;i <= l / 2;i ++)
		if(s[i] != s[l - i - 1]) return 0;
	return 1;
}
bool is_m(const string& s,const int& l)
{
	for(int i = 0;i <= l / 2;i ++)
		if(mir[s[i]] != s[l - i - 1]) return 0;
	return 1; 
}
int main(){
	string s;
	mir['A'] = 'A';
	mir['E'] = '3';
	mir['H'] = 'H';
	mir['I'] = 'I';
	mir['J'] = 'L';
	mir['L'] = 'J';
	mir['M'] = 'M';
	mir['O'] = 'O';
	mir['S'] = '2';
	mir['T'] = 'T';
	mir['U'] = 'U';
	mir['V'] = 'V';
	mir['W'] = 'W';
	mir['X'] = 'X';
	mir['Y'] = 'Y';
	mir['Z'] = '5';
	mir['1'] = '1';
	mir['2'] = 'S';
	mir['3'] = 'E';
	mir['5'] = 'Z';
	mir['8'] = '8';
	while(cin >> s)
	{
		int len = s.length();
		bool a = is_p(s,len),b = is_m(s,len);
		cout << s << " -- ";
		if(a)
		{
			if(b) printf("is a mirrored palindrome.");
			else printf("is a regular palindrome.");
		}
		else
		{
			if(b) printf("is a mirrored string.");
			else printf("is not a palindrome.");
		}
		printf("\n\n");
	}
	return 0;
}
```
其实很简单，不是吗？  

时空复杂度都是$O(\left\vert s \right\vert)$，此处$\left\vert s \right\vert$表示字符串$s$的长度。  

$\mathrm{The\ End.}$  

---

## 作者：AC基德 (赞：1)

# 来一波c++题解

### 分析：
#### 既然不包含空白字符串，可以安全地使用scanf进行输入。
回文串和镜像串地判断都不复杂，并且可以一起完成，详见下面的代码。使用常数数组，只用少量代码即可解决这个有些复杂的题目。

#### 一部分代码：

```c
const char* rev= "A  3 HIL JM O  2TUVWXY51SE Z  8 ";
const char *msg[] = {"not a palindorme", "a regular palindrome", "a mirrored string","a mirrored palindrome"};

char r(char ch){
	if(isalpha(ch)) return rev[ch - 'A'];
	return rev[ch-'0'+25];
}
```



#### 主函数：

```
char s[30];
	while(scanf("%s", s)==1)
	{
		int len=strlen(s);
		int p = 1,m = 1;
		for(int i = 0;i < (len+1)/2;i++)
		{
			if(s[i] != s[len-1-i]) p=0;//不是回文串 
			if(r(s[i]) != s[len-1-i]) m=0;//不是镜像串 
		}
		printf("%s -- is %s.\n\n", s, msg[m*2+p]); 
	}
```
### 本蒟蒻50分钟的一片题解，如有不适，大佬轻喷


---

## 作者：李宗骏 (赞：1)

### 既然不包含空白字符，可以安全地使用scanf进行输入。回文串和镜像串的判断都不复 杂，并且可以一起完成，详见下面的代码。使用常量数组，只用少量代码即可解决这个看上去有些复杂的题目
```cpp
#include <stdio.h>
#include <string.h>
#define maxn 1000
int main()
{
	char a[maxn],b[]="A3HILJHO2TUVWXY51SEZ8",c[]="AEHIJLHOSTUVWXYZ12358";
	int len;
	//freopen("data.txt","rb",stdin);
	while(scanf("%s",a)==1)
	{
		printf("%s",a);
		int count=0,flag=-1,count2=0,count3=0,j; 
		len=strlen(a);
			for(int i=0;i<len/2;i++) 
			{
				if(a[i]==a[len-(i+1)])
				{
					count++;//回文 
					if(strchr(b,a[i]))
						{
							count2++;//回文镜像 
						}
					//printf("***%d*%d",strchr(b,a[i]),strchr(c,a[len-(i+1)]));
				}
				for(j=0;j<21;j++)
				{
					if(a[i]==b[j])
					break;
				}
				if((a[i]==b[j])&&(a[len-(i+1)]==c[j]))
				{
					count3++;//镜像 
				} 
		    }
		    //printf("%d%d%d",count,count2,count3);
		    if(count==(len/2)) 
		    {
		    	if(count==count2)
		    	{
		    	  printf("--is a mirrored palindrome.\n");	//回文镜像
				}
				else
				{
				  	printf("--is a regular palindrome.\n");//回文
				}	
			}
			else
			{
			  if(count3==(len/2))
			  {
				  	printf("--is a mirrored string.\n");//镜像
			  }
			  else
			  {
			  	printf("--is not a palindrome. \n");//不是也不是镜像回文
			  }	
			}
	}
}
//潜在的问题：如果镜像串是奇数串，中间的那个字母是否必须是镜像字符？如果有要求程序仍需添加判断内容。 

```


---

## 作者：PC_DOS (赞：0)

这道题可以通过分别实现将字符串倒转和镜像倒转的函数，对于每一个输入的字符串，分别进行倒转和镜像倒转，比较结果和原字符串是否相等即可。

**务必注意，输出结论之后还要再输出一个空行。**

代码:
```
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
using namespace std; //头文件和命名空间
string strReverse(string strOrigin){ //字符串倒转的函数
	if (strOrigin.length() == 0){ //防止由于字符串为空串导致RE
		return "";
	}
	long long i;
	string ans;
	for (i = strOrigin.length() - 1; i >= 0; --i) //倒着读一遍
    	ans += strOrigin[i];
	return ans;
}
string strReverseMirror(string strOrigin){ //字符串镜像倒转的函数
	if (strOrigin.length() == 0){ //防止由于字符串为空串导致RE
		return "";
	}
	long long i;
	string strAns("");
	for (i = strOrigin.length() - 1; i >= 0; --i){ //倒着读一遍
		switch (strOrigin[i]){ //直接借助替换功能和正则表达式写了个swich语句
		case 'A':
			strAns += 'A';
			break;
		case 'E':
			strAns += '3';
			break;
		case '3':
			strAns += 'E';
			break;
		case 'H':
			strAns += 'H';
			break;
		case 'I':
			strAns += 'I';
			break;
		case 'J':
			strAns += 'L';
			break;
		case 'L':
			strAns += 'J';
			break;
		case 'M':
			strAns += 'M';
			break;
		case 'O':
			strAns += 'O';
			break;
		case 'S':
			strAns += '2';
			break;
		case 'T':
			strAns += 'T';
			break;
		case 'U':
			strAns += 'U';
			break;
		case 'V':
			strAns += 'V';
			break;
		case 'W':
			strAns += 'W';
			break;
		case 'X':
			strAns += 'X';
			break;
		case 'Y':
			strAns += 'Y';
			break;
		case 'Z':
			strAns += '5';
			break;
		case '1':
			strAns += '1';
			break;
		case '2':
			strAns += 'S';
			break;
		case '5':
			strAns += 'Z';
			break;
		case '8':
			strAns += '8';
			break;
		default:
			break;
		}
	}
	return strAns;
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	bool IsPalindrome = false, IsMirrored = false; //IsPalindrome-是不是回文串；IsMirrored-是不是镜像串
	string sInput; //存放输入的字符串
	while (cin >> sInput){ //循环读入字符串，在Visual Studio调试请使用CTRL+Z(^Z)结束输入
		if (sInput == strReverse(sInput)) //判断一下是不是普通的回文串
			IsPalindrome = true; //如果是，IsPalindrome置为真
		else
			IsPalindrome = false; //否则，IsPalindrome置为假
		if (sInput == strReverseMirror(sInput)) //判断一下是不是镜像串
			IsMirrored = true; //如果是，IsMirrored置为真
		else
			IsMirrored = false; //否则，IsMirrored置为假
		cout << sInput << " -- "; //输出结论的开头
		if (IsMirrored && IsPalindrome) //如果既是回文串，又是镜像串
			cout << "is a mirrored palindrome.\n\n"; //输出结论，注意空一行
		else if (IsMirrored && !IsPalindrome) //如果不是回文串，但是是镜像串
			cout << "is a mirrored string.\n\n"; //输出结论，注意空一行
		else if (!IsMirrored && IsPalindrome) //如果是回文串，但不是镜像串
			cout << "is a regular palindrome.\n\n"; //输出结论，注意空一行
		else //如果既不是回文串，又不是镜像串
			cout << "is not a palindrome.\n\n"; //输出结论，注意空一行
	}
	return 0; //结束
}
```
~~什么？您问我写那么长的case累不累？Visual Studio + 正则表达式大法好。~~

---

