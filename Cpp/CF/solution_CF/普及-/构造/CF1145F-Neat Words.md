# Neat Words

## 样例 #1

### 输入

```
NEAT
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
WORD
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
CODER
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
APRILFOOL
```

### 输出

```
NO
```

## 样例 #5

### 输入

```
AI
```

### 输出

```
YES
```

## 样例 #6

### 输入

```
JUROR
```

### 输出

```
YES
```

## 样例 #7

### 输入

```
YES
```

### 输出

```
NO
```

# 题解

## 作者：WKAHPM (赞：6)

这题其实是一道很水的字符串模拟，不要被难度骗了

~~CF恶意评分又不是一两天了（雾）~~

注意题目中说到的

>由直线或都是由曲线构成的

是指该字母的笔画（我理解题目理解了半天$qwq$）

具体思路：

- 1 应用$map$将由直线（或者曲线）构成的字母的映射值设为1


- 2 计算该字符串的所有对应的映射值之和，因为题目要求全为直线或全为曲线，所以当总和为$len$($len$为字符串长度)或$0$时，输出$YES$，否则输出$NO$

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
map<char,bool> p;
int main()
{
	ios::sync_with_stdio(false);
	p['A']=1;//打表
	p['E']=1;
	p['F']=1;
	p['H']=1;
	p['I']=1;
	p['K']=1;
	p['L']=1;
	p['M']=1;
	p['N']=1;
	p['T']=1;
	p['V']=1;
	p['W']=1;
	p['X']=1;
	p['Y']=1;
	p['Z']=1;
	cin>>s;
	int sum=0; 
	for(int i=0;i<s.size();i++) sum+=p[s[i]];//统计映射值之和
	if(sum==s.size() or sum==0) cout<<"YES";//判断
	else cout<<"NO";
	return 0;
}

```


---

## 作者：t162 (赞：2)

其实这题并没有那么难，打表就可以了。

考虑到用Pascal的set做这道题比较简单，~~所以我又去复习了一遍Pascal~~

集合的声明:
```pascal
VAR S:SET OF 基类型;		{注意基类型可存的范围不可超过256个}
```

高清代码：

```pascal
VAR S1,S2:SET OF CHAR;S:STRING[255];I:INTEGER;F,R:BOOLEAN;
BEGIN
    S1:=['A','E','F','H','I','K','L','M','N','T','V','W','X','Y','Z'];			{集合初始化}
    S2:=['B','C','D','G','J','O','P','Q','R','S','U'];								{同上}
    READLN(S);		{注意Pascal的string是从下标1开始存的}
    IF (S[1] IN S1) THEN F:=TRUE ELSE F:=FALSE;						{判断字符串有可能属于哪一种类型}{in运算符表示某个元素是否被集合所包含}
    R:=TRUE;
    FOR I:=2 TO LENGTH(S) DO IF F THEN R:=R AND (S[I] IN S1) ELSE R:=R AND (S[I] IN S2);															{遍历字符串，得到结果}
    IF R THEN WRITE('YES') ELSE WRITE('NO');		{输出答案}
END.
```



---

## 作者：Eason_AC (赞：1)

## Content
本题为 CF 愚人节比赛题目。

给定一个长度为 $n$ 的，仅包含大写字母的字符串，问这个字符串里面的字母是否全部都是由仅有直线的字母组成，或者全部都是由有曲线的字母构成。

**数据范围：$1\leqslant n\leqslant 10$。**
## Solution
我们先来列出 $26$ 个大写字母中仅由直线构成的字母：$\texttt{A,E,F,H,I,K,L,M,N,T,V,W,X,Y,Z}$，那么，由于这道题目的数据范围很小，我们只需要一个一个地去暴力判断就好了。
## Code
```cpp
const string ans = "BCDGJOPQRSU";

int main() {
	string s;
	cin >> s;
	int res = 0, len = s.size(), lena = ans.size();
	_for(i, 0, len - 1) {
		int flag = 1;
		_for(j, 0, lena - 1)
			if(s[i] == ans[j]) {
				flag = 0;
				break;
			}
		res += flag;
	}
	return printf((!res || res == len) ? "YES" : "NO"), 0;
	return 0;
}
```

---

## 作者：tzl_Dedicatus545 (赞：1)

## 思路：
- 先定义一个表,代表每个字母是由曲线还是直线构成的，曲线为 $0$ ,直线为 $1$ 。
- 把字符串放到 $string$ 数组 $a$ 里存起来，如果 $hash_{a_i-'A'} \neq hash_{a_{i-1}-'A'}$ 输出 $NO$，结束程序。
- 在循环结束后，输出 $YES$。

## 代码：

```cpp
//By: Luogu@wangdemao(308854)
#include <iostream>

using namespace std;

bool biao[26]={1,0,0,0,1,1,0,1,1,0,1,1,1,1,0,0,0,0,0,1,0,1,1,1,1,1};

int main()
{
	string a;
	
	cin>>a;
	
	for(int i=1;i<a.size();i++)
	{
		if(biao[a[i]-'A']!=biao[a[i-1]-'A'])	
		{
			cout<<"NO";	
			return 0;		
		}
	}
	
	cout<<"YES";
	
	return 0;
}

```

---

## 作者：Trimsteanima (赞：1)

### Description
给出一个字符串，若所有的字母都是由直线或都是由曲线构成的输出 `YES`，否则输出 `NO`。
### Solution
暴力枚举

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[100];
int f[100], sum;
int main() {
	cin >> s;
	f[1] = 1, f[5] = 1, f[6] = 1, f[8] = 1, f[9] = 1, f[11] = 1, f[12] = 1, f[13] = 1, f[14] = 1, f[20] = 1, f[22] = 1, f[23] = 1, f[24] = 1, f[25] = 1, f[26] = 1;
	for (int i = 0; i < strlen(s); i ++ )	
		sum += f[s[i] - 'A' + 1];
	if (sum == 0 || sum == strlen(s))
		printf("YES\n");
	else 
		printf("NO\n");
	return 0;
}
```

---

## 作者：CZQ_King (赞：0)

见题解都没有用$find$的，蒟蒻在这里发一波。

$find$函数：用于查找字符串里第一次出现目标字符串的位置。

用法：``s.find(v)``或``s.find(v,a)``。其中``s``是原字符串，``v``是目标字符串，``a``是起始位置。例如``s.find(v,5)``就是从``s``的第$5$个字符开始查找``v``。

如果没有找到目标字符串，函数返回$-1$。

------------
做法：

直的字母：
```
A,E,F,H,I,K,L,M,N,T,V,W,X,Y,Z
```
弯的字母：
```
B,C,D,G,J,O,P,Q,R,S,U
```

因为字母不是直的就是弯的，我们可以利用$find$函数，找直的字母如果都没有找到那么说明字母都是弯的，此时输出``YES``。然后找弯的字母如果都没有找到说明字母都是直的，此时输出``YES``，其余情况输出``NO``。

------------
代码：
```cpp
#include<bits/stdc++.h>
#define F(a) s.find(a)==-1//宏定义简化
using namespace std;
string s;
int main(){
	cin>>s;
	puts(F('B')&&F('C')&&F('D')&&F('G')&&F('J')&&F('O')&&F('P')&&F('Q')&&F('R')&&F('S')&&F('U')?"YES":F('A')&&F('E')&&F('F')&&F('H')&&F('I')&&F('K')&&F('L')&&F('M')&&F('N')&&F('T')&&F('V')&&F('W')&&F('X')&&F('Y')&&F('Z')?"YES":"NO");
}
```

---

## 作者：zoobidubi (赞：0)

在这里提交一个很好理解的题解

我不会用map，也不会用各种神奇的判断方法

那我怎么过这道题呢

当然是按照题意用if语句模拟一波就好了

Code

```cpp

#include<bits/stdc++.h>
using namespace std;
string s;
bool f;
int main()
{
    cin >> s;
    for (int i = 0; i < s.size(); i ++) 
	{
	     if (s[i] == 'A' || s[i] == 'E' || s[i] == 'F' || s[i] == 'H' || s[i] == 'I' || s[i] == 'K' || s[i] == 'L' || s[i] == 'M' || s[i] == 'N' || s[i] == 'T' || s[i] == 'V' || s[i] == 'W' || s[i] == 'X' ||s[i] == 'Y' || s[i] == 'Z')
	     {
	     	f = 1;//如果是直线构成的就是1
		 }
		 else {
		 	f = 0;//只要有一个不是就别循环了
		 	break;
		 }
	}
	if (f == 1) //如果全都是的话就输出yes
	{
	    cout << "YES"; 
	    return 0;
	} 
    for (int i = 0; i < s.size(); i ++) 
	{
	     if (!(s[i] == 'A' || s[i] == 'E' || s[i] == 'F' || s[i] == 'H' || s[i] == 'I' || s[i] == 'K' || s[i] == 'L' || s[i] == 'M' || s[i] == 'N' || s[i] == 'T' || s[i] == 'V' || s[i] == 'W' || s[i] == 'X' ||s[i] == 'Y' || s[i] == 'Z'))//再次寻找如果都是用曲线（非直线）
	     {
	     	f = 1;
		 }
		 else {
		 	f = 0;
		 	break;
		 }
	}
	if (f) cout << "YES";//同理
	else cout << "NO";//都不是的话就输出NO吧
    return 0;
}


```


---

## 作者：毛梁智洲666 (赞：0)

C++ CF1145F

题目中所说的由曲线构成和由直线构成是指字母有没有“圆弧”。（B，就有2个；A都是直线，所以没有）

这题可以打表，只要是由直线构成就为1，否则为0。

```
int a[26] = {1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1};
```

这就是最主要的了。

然后再开一个数组存放字符串，输入要用gets，strlen函数可以判断字符串的长度。

```
char b[10001];
gets(b);
int n = strlen(b),
```
基本思路：判断第i个字符是否和前面的一个的数字（1或0）相等，不相等就输出NO，否则一直判断到最后，输出YES。

接着，上代码：

```
#include <bits/stdc++.h> //万能头文件
using namespace std; //声明姓名空间

int main() { //主程序开始
    int a[26] = {1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1}; //打表
    char b[10001]; //字符串
    gets(b); //输入
    int n = strlen(b), s = a[b[0] - 'A']; //判断长度，设定最初的数字（b[0]是一个字母，减去A就是第几个字母，然后看他的数字）
    for (int i = 1; i < n; i++) { //原本应该是从0循环到n - 1，可现在0已经变成了s，就从1开始。
        if (a[b[i] - 'A'] != s) { //判断是否和第0个字符的数字相同。
            cout << "NO" << endl; //如果不一样，输出0。
            return 0; //不用继续循环了。
        }
    }
    cout << "YES" << endl; //一直到最后都是一样的，就代表他们的数字都相同
    return 0;
}
```

---

## 作者：Kuriyama_Mirai (赞：0)

给你一个由大写字母构成的字符串，若字符串中所有字符的笔画都是直的或都是弯的就是输出YES，否则输出NO。

```cpp
#include <cstdio>

bool bow[26] = {1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1};
char str[11];
int res[2];

int main() {
	scanf("%s", str);
	
	int i = -1;
	while (str[++ i])
		res[bow[str[i] - 'A']] |= 1;
	
	printf("%s", res[0] + res[1] == 1  ?  "YES"  :  "NO");
	return 0;
}
```

---

## 作者：AC_Dolphin (赞：0)

愚人节的地方在翻译里已经告诉你了。。。

所以只要~~打表~~一下直的字符和弯的字符，最后再处理一下就行了

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=100010;
int a[MAXN],n,cnt;
char str[MAXN]={'A','E','F','H','I','K','L','M','N','T','V','W','X','Y','Z'};//直的字符
bool flag=false;//表示是否是同一种字符
string s;
inline int read(){
    int f=1,x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
int main(){
    cin>>s;
    for(int i=0;i<s.length();i++){
        bool sb=false;
        for(int j=0;j<15;j++){
            if(s[i]==str[j]){//如果当前字符是直的字符
                sb=true;
                if(i==0) flag=true;//设为true
                else{
                    if(flag==false){//如果前面有弯的字符
                        cout<<"NO";//输出no
                        return 0;
                    }
                }
            }
        }
        if(sb==false){
            if(i==0) flag=false;//同上
                else{
                    if(flag==true){
                        cout<<"NO";
                        return 0;
                    }
                }
        }
    }
    cout<<"YES";//最后只能输出yes了
    return 0;
}
```
蒟蒻第一次写题解，求通过了吧。。。

---

