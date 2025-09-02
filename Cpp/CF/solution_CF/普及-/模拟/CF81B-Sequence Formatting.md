# Sequence Formatting

## 题目描述

Polycarp 是个非常严谨的人，不像他的同班同学那样，他甚至仔细地键入数字序列。
如果他看到一个序列在逗号后面没有空格，或是一行有多个空格，或者当其他东西看起来不严谨时，他会立刻纠正它。
例如，如“1,2，3，…，10”所写的数字序列将被修正为“1, 2, 3，…，10”。
在这个任务中，你得到一个字符串 s ，
s 由术语的连词构成，每一个词可以是：

	1.任意长度的正整数（不允许前导零），
	2. 逗号符号（“，”），
	3. 空格符号（“ ”），
	4. “三点”（“…”），即一个接一个地写三个点，也称为“暂停点”。
Polycarp想添加并且删除字符串s中多余的空格来满足以下要求：

	1.每个逗号后面只有一个空格（若逗号是字符串中的最后一个字符，则此规则不适用于它）；
	2.每个“三点”前正好有一个空格（若三点在字符串的开头，则此规则不适用于它）；
	3.如果两个连续的数字仅由空格分隔，那么就应该只剩下一个空格，不应该有多余的空格。
现在请你编写一个程序帮助Polycarp完成对字符串s的操作。

## 样例 #1

### 输入

```
1,2 ,3,...,     10
```

### 输出

```
1, 2, 3, ..., 10
```

## 样例 #2

### 输入

```
1,,,4...5......6
```

### 输出

```
1, , , 4 ...5 ... ...6
```

## 样例 #3

### 输入

```
...,1,2,3,...
```

### 输出

```
..., 1, 2, 3, ...
```

# 题解

## 作者：Henry_ji (赞：3)

# CF81B Sequence Formatting 题解
本文中的代码均为 Python 语言书写，但并不难理解，可供大家参考。
## 一、题目分析
~~乍一看这道题是个模拟题，~~ 实际上它就是个模拟题。

当然，在模拟之前我们首先要来理清我们编程的思路。

既然题目中提到了 **“词”** 这个概念，我们就以 **词** 为单位进行模拟。

P.S. 为了表述方便，后文中以 **单词** 来代替

本题，我采用的是先将字符串拆成单词，再逐个分析并输出单词的方法。

## 二、代码思路
### 1、拆分字符串
为了便于大家理解，我画了一张思维导图，较为直观地展示了我的思路。
![](https://s3.bmp.ovh/imgs/2022/05/01/bc2f0e3b54731d0d.png)

## 2、单词输出
这里我们引入一个布尔型变量 flag 来表示上一个输出是否是逗号，用于判断输出三个点时是否加上前导空格

具体过程同样也是一张思维导图。
![](https://s3.bmp.ovh/imgs/2022/05/01/bc54436fe6ecee40.png)

## 三、完整代码
讲了这么多也是时候放 AC 代码了

```python
class CLS_word(object):
    def __init__(self, type, value):
        self.type = type
        self.value = value

def print_s(wL):
    flag = False
    for i in range(len(wL)):
        word = wL[i]
        if word.type == 'num':
            flag = False
            print(word.value, end='')
        elif word.type == 'space' and wL[i - 1].type == 'num' and wL[i + 1].type == 'num':
            flag = False
            print(' ', end='')
        elif word.type == 'comma':
            flag = True
            if i == len(wL) - 1:
                print(',', end='')
            else:
                print(', ', end='')
        elif word.type == 'dot':
            if flag == True or i == 0:
                flag = False
                print('...', end='')
            else:
                print(' ...', end='')
    return

def print_w(wL):
    for word in wL:
        print(word.type, word.value)


s = input()
s += '&'
wordList = []
p1, p2 = 0, 1
num = ('1','2','3','4','5','6','7','8','9','0')

while True:
    if p2 == len(s):
        break
    if s[p1] in num:
        while s[p2] in num:
            p2 += 1
        wordList.append(CLS_word('num', s[p1:p2]))
        p1 = p2
        p2 = p1 + 1
    elif s[p1] == ' ':
        while s[p2] == ' ':
            p2 += 1
        wordList.append(CLS_word('space', s[p1:p2]))
        p1 = p2
        p2 = p1 + 1
    elif s[p1] == '.':
        wordList.append(CLS_word('dot', '...'))
        p1 += 3
        p2 = p1 + 1
    elif s[p1] == ',':
        wordList.append(CLS_word('comma', ','))
        p1 += 1
        p2 = p1 + 1
print_s(wordList)
```

## 四、避坑指南
没什么可多说的，对于模拟题就是 $\color{Red}\text{细心，细心，再细心}$

---

## 作者：zsh_haha (赞：2)

### 题意描述

意思就是让你格式化一串字符串，格式化要求如下

- 自然数后要加空格，除非自然数后跟着逗号或者自然数在末尾;

- 逗号后要加空格，除非逗号在末尾；

- 三点号前要加空格，除非三点号在开头或者三点号前本来就有空格。


### 思路讲解

有了上面的描述，代码实现就很简单了。

我们可以用一个 `char` 数组来保存结果。

具体见代码。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1001];
char b[1001];
int main(){
	cin.getline(a,1000);
	int l=strlen(a);
	int ll=0;
	for(int i=0;i<l;i++){
		if(a[i]>='0'&&a[i]<='9'){//处理自然数 
			while(a[i]>='0'&&a[i]<='9'){
				b[++ll]=a[i];
				i++;
			}
			i--;
			b[++ll]=' ';//加空格 
		}else if(a[i]==','){//处理逗号 
			if(b[ll-1]>='0'&&b[ll-1]<='9'){//如果前面是自然数则把自然数后的空格去掉 
				b[ll]=',';
				b[++ll]=' ';
			}else{
				b[++ll]=',';
				b[++ll]=' ';
			}
		}else if(a[i]=='.'){//处理三点号 
			if(ll==0||b[ll]==' '){//在开头或前面本来就有空格就不加空格 
				b[++ll]='.';
				b[++ll]='.';
				b[++ll]='.';
			}else{
				b[++ll]=' ';
				b[++ll]='.';
				b[++ll]='.';
				b[++ll]='.';
			}
			i+=2;
		}
	}
	for(int i=1;i<=ll;i++){
		if(i==ll&&b[i]==' '){//处理后缀空格 
			break;
		}
		cout<<b[i];
	}
	return 0;
}
```

---

## 作者：Allanljx (赞：2)

## 思路
这是一道模拟需要细心，具体情况见代码注释
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string str;
char a[256];
int k;
int main()
{
	getline(cin,str);//读入一行
	int n=str.size();//取长度
	for(int i=0;i<n;i++)
	{
		if(i==n-1&&str[i]==',')//如果这是逗号且是最后一个字符
		{
			cout<<',';
			continue;
		}
		if(str[i]==' ') continue;//如果是空格跳过
		if(k==0)//k记录上一位除了空格的字符在哪里
		{
			a[++k]=str[i];
			putchar(str[i]);
			if(str[i]<='9'&&str[i]>='0') continue;
			if(str[i]!='.') putchar(' ');
			continue;
		}
		a[++k]=str[i];
		if(str[i]<='9'&&str[i]>='0')//如果这是数字
		{
			if(a[k-1]<='9'&&a[k-1]>='0'&&str[i-1]==' ') putchar(' ');//将数字之间的空格保留一个
			putchar(str[i]);输出这个数字
			continue;
		}
		if(str[i]=='.'&&k>=4&&a[k-1]=='.'&&a[k-2]=='.'&&a[k-3]=='.')//如果是省略号
		{
			putchar(' ');//输出空格
			k-=3;
		}
		putchar(str[i]);
		if(str[i]!='.') putchar(' ');
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

题目一读就懂，按照题目要求，注意考虑清楚情况，细心点就可以请轻松AC。

直接上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	getline(cin,s);
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='.')
		{
			s[i]='@';
			s.erase(s.begin()+i+1);
			s.erase(s.begin()+i+1);
		}
	}
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='@')
		{
			if(s[i-1]==' '||i==0)
				cout<<"...";
			else
				cout<<" ...";
		}
		else if(s[i]==',')
		{
			if(i==s.size()-1)
				cout<<",";
			else
			{
				cout<<", ";
				s[i]=' ';
			}
		}
		else if(s[i]==' ')
		{
			if(s[i-1]==' ')
				continue;
			if(s[i-1]==','||s[i+1]=='@'||(isdigit(s[i-1])&&isdigit(s[i+1])))
				cout<<' ';
			else
				s[i]=s[i-1];
		}
		else
			cout<<s[i];
	}
	return 0;
}

```

---

## 作者：kimi0705 (赞：1)

# CF81B Sequence Formatting 题解
tag: 细节 & 分类讨论


**tips**: (`-`表示` `)
1. 删除多余空格，把多个空格合并成一个。
1. 遍历字符串
   1. 如果是空格
      - 跳过
   1. 如果是数字
      1. 如果后一个是空格且后两个是数字
         - 因为后面隔了一个空格然后是数字，又空格要跳过，所以要多输出
      1. 其他情况
         - 直接输出数字。
   1. 如果是`,`
      1. 如果是最后面的
         - 输出`,`
      1. 其他情况
         - 输出`,-`
   1. 如果是`.`
      1. 如果在最前面
         - 输出`...`
      1. 如果前一个是`,`,已经输出过`-`了，不用在输出了
         - 输出`...`
      1. 同理，如果前两个是`,`，且前一个是`-`,也已经输出过`-`了，不用在输出了
         - 输出`...`
      1. 其他情况
         - 输出`...`
     
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string s;
void replaceA_to_B ( string& S, string A, string B ) {
	size_t found = S.find ( A );
	while ( string::npos != found ) {
		S.replace ( found, A.length(), B );
		found = S.find ( A, 0 );
	}
}
signed main () {
	getline ( cin, s );
	replaceA_to_B ( s, "  ", " " ); 									// 把所有的"  "换成" "
	n = s.size();
	for ( int i = 0; i < n; i++ ) {										// 遍历字符串
		if ( '0' <= s[i] && s[i] <= '9' ) {
			if ( s[i + 1] == ' ' && '0' <= s[i + 2] && s[i + 2] <= '9' )
				cout << s[i] << ' ';
			else cout << s[i];											// 直接输出数字
		} else if ( s[i] == ',' ) {
			if ( i == n - 1 ) {											// 如果是最后一个字符
				cout << ',';
			} else {
				cout << ", ";
			}
		} else if ( s[i] == '.' ) {										// 省略号
			if ( i == 0 ) {
				cout << "...";
			} else if ( s[i - 1] != ',' && ! ( s[i - 2] == ',' && s[i - 1] == ' ' ) ) {
				cout << " ...";
			} else {
				cout << "...";
			}
			i += 2;
		}
	}
}
```

~~题解是我家，AC靠大家。~~

---

## 作者：灵光一闪 (赞：1)

~~Aya，感觉这个题不是我这种蒟蒻做的……~~

~~原本我想虐水题，却被水题虐……~~

好的，开始讲：

这题就是要细心，细心，再细心！！！！！！！！

不然就是WA~~qaq~~
![](https://cdn.luogu.com.cn/upload/pic/63908.png)
![](https://cdn.luogu.com.cn/upload/pic/63909.png)

神™这题真的难做（可能是我太弱了）

下面贴出代码。
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<string>
#include<map>
using namespace std;
map<int,bool> mp;
string str,ans;
string res;
int main(){
    string s;
    getline(cin,s);
    for(int i=0;i<s.size();i++){
        if(s[i]==','){
            str+=s[i];
            str+=' ';
            continue;
        }
        if(s.substr(i,3)=="..."){
            str+='@';//把它改成单字符，很好算
            i+=2;
            continue;
        }
        str+=s[i];
    }
//cout<<str<<endl;
    bool flag=false;
    for(int i=0;i<str.size();i++){//去掉重复空格
        if(str[i]==' '){
            if(!flag){
                flag=true;
                res+=str[i];
                continue;
            }
        }
        else{
            res+=str[i];
            flag=false;
            continue;
        }
    }
    str=res;
//cout<<str<<endl;
    for(int i=0;i<str.size();i++){//避免 “... 1，2 ,”这种情况
        ans+=str[i];
        if(str[i]==' '&&str[i-1]=='@'&&str[i+1]!='@'){
            ans=ans.substr(0,ans.size()-1);
            continue;
        }
        if(str[i]==' '&&str[i+1]!='@'&&str[i-1]!=','){
            if(str[i+1]!=','&&str[i-1]!='@'){
                continue;
            }
            if(str[i]==' '&&str[i+1]==','){
                ans=ans.substr(0,ans.size()-1);
            }
            continue;
        }
    }
//cout<<ans<<endl;
    for(int i=0;i<ans.size();i++){//输出，好好讲讲：
        if(ans.size()-2==i&&ans[i]==','){//如果这是最后一个……
            putchar(',');//就不要输出空格了
            break;
        }
        if(ans[i]=='@'){//如果第一个就是省略号的话也不要空格
            if(i!=0&&ans[i-1]!=' '){
                cout<<" ";
            }
            cout<<"...";
        }
        else{//不然安静地输出qaq
            cout<<ans[i];
        }
    }
//putchar('-');
    return 0;
}
```

---

## 作者：Jerrycyx (赞：0)

~~一看题目内容，这道题看似是道模拟，实际上确实是道模拟。~~

-----

### 解析

题目中分四种类型：整数、逗号、空格、省略号。我们来分类讨论：

1. **整数**：无需处理，直接塞到 $s$ 里面就行了。

2. **逗号**：往 $s$ 里面加一组 `, `（即一个逗号加一个空格）。

3. **空格**：当两个整数内包含多个空格时，只保留一个。即只有前一个是数字时才加入空格，其它忽略。

4. **省略号**：省略号的处理较为复杂，需要分成每三个一组。我们可以用一个变量表示输入 `.` 的个数，当其为 $0$ 时输出 ` .`（空格加点），否则只输出 `.`；当其达到 $3$ 时意味着一组省略号已完成，需要将其清零以便下一组省略号（如果有的话）输出空格。

这样做可能产生连续空格，输出时需要再判断一下，连续空格只输出 $1$ 个。

还有一种特殊情况，输入 `1   ,  2` 时会输出 `1 , 2`,数字和逗号之间多了一个空格。输出时特判一下就好了。

另外，还有一个注意事项：末尾不能额外输出空格或换行，所以末尾的空格还需要处理一下。

具体实现请看代码注释。

这样，就能正确输出答案了。

-----

### 代码：

```cpp
#include<cstdio>
using namespace std;

char s[10005];	//s 储存最终结果，从 s[1] 开始 
int len=0;		//len 表示 s 的长度 

int main()
{
	int dot=0;		//dot 用来表示 . 的个数 
	while(true)
	{
		char ch=getchar();		//输入单个字符 
		if(ch=='\n') break;		//如果输入完成则退出循环 
		if(ch==' ')				//情况 3 
		{
			if(s[len]>='0'&&s[len]<='9')
				s[++len]=' ';
			else continue;
		}
		if(ch>='0'&&ch<='9') 	//情况 1 
			s[++len]=ch;
		if(ch==',') s[++len]=',',s[++len]=' ';	//情况 2 
		if(ch=='.')			//情况 4 
		{
			if(dot==0&&(s[len]!=' '&&len!=0)) s[++len]=' ';
			s[++len]='.';
			dot++;
			if(dot==3) dot=0;
		}
	}
	while(s[len]==' ') len--;		//循环处理字符串末尾字符 
	for(int i=1;i<=len;i++)
	{
		if(s[i]==' '&&s[i-1]==' ') continue;	//判断连续空格 
		if(s[i-1]>='0'&&s[i-1]<='9' && s[i]==' ' && s[i+1]==',')
			continue;		//“数字+空格+逗号”的特殊情况判断 
		putchar(s[i]);
	}
	return 0;
}
```

$$\large\frak{The\ End}$$

---

