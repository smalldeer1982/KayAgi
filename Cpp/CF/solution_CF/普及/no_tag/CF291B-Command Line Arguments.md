# Command Line Arguments

## 题目描述

The problem describes the properties of a command line. The description somehow resembles the one you usually see in real operating systems. However, there are differences in the behavior. Please make sure you've read the statement attentively and use it as a formal document.

In the Pindows operating system a strings are the lexemes of the command line — the first of them is understood as the name of the program to run and the following lexemes are its arguments. For example, as we execute the command " run.exe one, two . ", we give four lexemes to the Pindows command line: "run.exe", "one,", "two", ".". More formally, if we run a command that can be represented as string $ s $ (that has no quotes), then the command line lexemes are maximal by inclusion substrings of string $ s $ that contain no spaces.

To send a string with spaces or an empty string as a command line lexeme, we can use double quotes. The block of characters that should be considered as one lexeme goes inside the quotes. Embedded quotes are prohibited — that is, for each occurrence of character """ we should be able to say clearly that the quotes are opening or closing. For example, as we run the command ""run.exe o" "" " ne, " two . " " ", we give six lexemes to the Pindows command line: "run.exe o", "" (an empty string), " ne, ", "two", ".", " " (a single space).

It is guaranteed that each lexeme of the command line is either surrounded by spaces on both sides or touches the corresponding command border. One of its consequences is: the opening brackets are either the first character of the string or there is a space to the left of them.

You have a string that consists of uppercase and lowercase English letters, digits, characters ".,?!"" and spaces. It is guaranteed that this string is a correct OS Pindows command line string. Print all lexemes of this command line string. Consider the character """ to be used only in order to denote a single block of characters into one command line lexeme. In particular, the consequence is that the given string has got an even number of such characters.

## 样例 #1

### 输入

```
&quot;RUn.exe O&quot; &quot;&quot; &quot;   2ne, &quot; two! . &quot; &quot;
```

### 输出

```
&lt;RUn.exe O&gt;
&lt;&gt;
&lt;   2ne, &gt;
&lt;two!&gt;
&lt;.&gt;
&lt; &gt;
```

## 样例 #2

### 输入

```
   firstarg   second   &quot;&quot;    
```

### 输出

```
&lt;firstarg&gt;
&lt;second&gt;
&lt;&gt;
```

# 题解

## 作者：pfrig729 (赞：2)

### 题意
给定一个包含大写和小写英文字母、数字、字符 , . ? ! " 和空格的字符串，**两个引号** 中间的子字符串为一个词素，引号外的 **非空格** 子字符串也为一个词素。请你每个词素一行地输出所有的词素，并在输出时将每个词素包裹在 "<>" 中间。
### 分析
1. 输入字符串 $s$ ，因为有字符串中有空格所以使用 `getline(cin,s)` 。

2. 将整个字符串扫一遍，我们可以用一个字符串 $z$ 来记录当前词素，定义一个`bool`变量 $q$ （初始化为 $0$ ），其作用是记录当前字符是否在两个引号内。

>- 若当前字符是引号，那么将 $q$ 取反，如果此时 $q$ 为 $1$ ，即当前字符在两个引号中间，那么将当前字符存入 $z$ 中；如果此时 $q$ 为 $0$ ，则此时 $z$ 中存的就是引号中的字符，将 $z$ 输出并清空。

>- 若当前字符是空格，先判断它是否在空格中（也就是 $q$ 是否为 $1$ ），如果不在且 $z$ 不为空，那么像前面处理引号一样处理（输出并清空）。

>- 若为其它字符，即是 , . ? ! " 时，将此字符存入 $z$ 中。

3. 最后要进行特判，如果此时 $z$ 中还有字符，那么将 $z$ 中所有剩余的字符输出。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
string s,z="";
bool q;
int main()
{
    getline(cin,s);
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='"')
        {
            q=!q;
            if(!q)
            {
                printf("<%s>\n",z.c_str());
                z="";
            }
        }
        else if(s[i]==' '&&!q)
        {
            if(z!="")
            {
                printf("<%s>\n",z.c_str());
                z="";
            }
        }
        else
        {
            z+=s[i];
        }
    }
    if(z!="")
    {
        printf("<%s>\n",z.c_str());
    }
    return 0;
}
```

---

## 作者：tangxinyan (赞：1)

### 题目分析

本题要求解析一个模拟的命令行输入字符串，这个字符串遵循虚构的 Pindows 操作系统的规则。我们需要识别命令行中的各个词素（lexemes），这些词素可能被空格分隔，也可能被双引号包围（包括空词素和包含空格的词素）。任务是按顺序输出这些词素，并在每个词素的前后加上尖括号。

### 解题思路

解题的核心在于准确地识别词素的边界。我们按照以下规则解析输入字符串：

1. **双引号**：当遇到一个双引号时，就知道已经进入了一个词素。双引号内的所有内容都应该视为同一个词素，直到遇到下一个双引号。如果双引号内为空，仍然输出一个空的词素。

2. **空格**：在双引号外，空格表示词素的边界。每次遇到空格时，将之前收集的字符作为一个词素输出，并开始收集下一个词素。

3. **词素收集**：通过一个循环来逐字符读取输入字符串，根据上述规则来确定词素的开始和结束。

### 代码实现

```
#include<bits/stdc++.h>
using namespace std;
vector<string> split_command_line(const string &s)
{
    vector<string> lexemes;
    string lexeme;
    bool in_quotes=0;
    for(char ch : s)
	{
        if(ch=='"')
		{
            in_quotes=!in_quotes;
            if(!in_quotes)
			{
                lexemes.push_back(lexeme);
                lexeme.clear();
            }
        }
		else if(ch==' '&&!in_quotes)
		{
            if(!lexeme.empty())
			{
                lexemes.push_back(lexeme);
                lexeme.clear();
            }
        }
		else
		{
            lexeme+=ch;
        }
    }

    if(!in_quotes&&!lexeme.empty())
	{
        lexemes.push_back(lexeme);
    }
    return lexemes;
}

int main()
{
    string command_line;
    getline(cin,command_line);
    vector<string> lexemes=split_command_line(command_line);
    for(const string &lex : lexemes)
	{
        cout<<'<'<<lex<<'>'<<endl;
    }
    return 0;
}
```

---

## 作者：floodfill (赞：0)

# CF291B Command Line Arguments 题解
### 题目大意
给定一个字符串 $s$，**两个引号**中间的字符串为一个词素，引号外的**非空格**子串也为一个词素。输出所有词素。
### 大致思路
定义字符串 $c$ 以存储词素，```bool``` 型变量 $is$ 以记录在遍历时是否出现还未被输出的子串。

遍历字符串 $s$。若 $s_i$ 不是双引号或空格，即将 $s_i$ 加入 $c$。当 $s_i$ 是双引号或空格，我们先查询 $is$ 的值是否为 $0$。若 $is=1$，我们直接输出 $c$ 即可。

注意：
- 输出 $c$ 之前要先判断是否为空。
- 输出之后记得要清空 $c$。
- 当有子串为**双引号**，$is$ 取反。

---

## 作者：lpx666666 (赞：0)

## 题面
给定一个字符串，两个引号中间的字符串为一个词素，在引号外的字符串每一个词素都被空格隔开，输出每一个词素。

## 思路
可以对整个字符串的每个字符分类，分为引号、空格和其他，用一个统计字符串去记录每个词素。

我一开始想引号前要么是引号内的字符串，要么是引号外的最后一个字符串，都一定会输出，但样例中引号前可能是空格，引号外空格做为分隔符，不能输出，所以要对统计的字符串进行是否为空的特判。

### 注意：英文字符中左右引号是一模一样的，要用一个计数变量记录从而判断引号的左右。

空格就比较简单了，可利用引号的计数变量判断这个空格在引号外还是引号内，引号内的空格属于词素中的一个字符，所以只需直接统计，引号外的空格做为分隔符应该直接输出统计的词素，但和左引号一样，需要判断统计的字符串是否为空。

其他的只需直接统计就可以。

## 代码
洛谷最近交不上这道题，只能到主站上交，附[提交记录](https://codeforces.com/contest/291/submission/276029805)。

上代码。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
string s,ss="";
int cnt=0;
int main(){
	getline(cin,s);//输入 
	for(int i=0;i<s.size();i++){
		if(s[i]=='"'){
			cnt++;
			if(cnt%2==0){//判断内外 
				cout<<'<'<<ss<<'>'<<endl;//输出 
				ss="";
			}
			else{
				if(ss.size()){//判断是否为空 
					cout<<'<'<<ss<<'>'<<endl;//输出 
					ss="";
				}
			}
		}
		if(s[i]!='"' && s[i]!=' '){//其他 
			ss+=s[i];//统计 
		}
		if(s[i]==' '){//空格 
			if(cnt%2==0){//判断内外 
				if(ss.size()){//输出 
					cout<<'<'<<ss<<'>'<<endl;
					ss="";
				}
			}
			else{
				ss+=s[i];//统计 
			}
		}
	}
	if(ss.size()){//输出最后剩下的 
		cout<<'<'<<ss<<'>'<<endl;
		ss="";
	}
	return 0;//华丽收场 
}
```

这道题说着复杂，但思路和代码都挺简单，只需注意一些细节就能通过。

---

## 作者：GreenMelon (赞：0)

### 提示

`getline(cin, s)` 可以读入空格，在这道题可以应用到。
### 解析

读入 $s$ 后，我们一个一个遍历。

如果 $s_i$ 不是空格或双引号，将 $s_i$ 加进 $k$ 中。

- 关于空格

如果空格前是空格或双引号，直接跳过，无需进行操作（如 `"123" "456"`）

如果此空格在双引号中（如 `"123 456"`）将此空格加进 $k$ 中。

如果空格前为其他字符，则将 $k$ 输出，并清空 $k$。

- 关于双引号

可以用 $isyin$ 变量判断字符是否在双引号中，如果是则为 $\texttt{true}$ 否则为 $\texttt{false}$。

如果 $isyin$ 为 $\texttt{true}$ 且该字符为双引号，将 $k$ 输出，并清空 $k$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool isyin;//默认为false
void print(string s){
	cout<<"<"<<s<<">"<<endl;
}
int main(){
	string s, k="";
	getline(cin, s);
	s+=' ';
	for(int i=0;i<s.size();i++){
		if(s[i]==' ' && s[i-1]!=' ' && s[i-1]!='\"' && i!=0 && !isyin){ //记得判断前面是不是空格或双引号
			print(k);
			k="";
			continue;
		}
		if(s[i]==' ' && !isyin) continue;
		if(s[i]=='\"'){
			if(!isyin) isyin=1;
			else{
				print(k);
				k="";
				isyin=0;
			}
			continue;
		}
		k+=s[i];
	}
	return 0;
}
```

---

## 作者：DennyQi (赞：0)

这是一道模拟题。

用`gets`读入字符串。

从前往后扫描，记录两个布尔变量$inq$和$ins$分别表示当前位置是否处于一个括号内命令，与当前位置是否处于一个括号外命令。当$inq$或$ins$的值为1时，判断是否进行到`"`或` `，如果进行到则输出答案。

注意结尾要特判。

表达不清晰，具体看代码。

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int N = 100010;
const int P = 998244353;
const int INF = 0x3f3f3f3f;
inline int mul(const int& a, const int& b){ return 1ll*a*b%P; }
inline int add(const int& a, const int& b){ return (a+b>=P)?a+b-P:a+b; }
inline int sub(const int& a, const int& b){ return (a-b<0)?a-b+P:a-b; }
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0' || c>'9')) c = getchar();
    if(c=='-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
    return x*w;
}
char s[N];
vector <int> ans;
int n,inq,ins,sz;
int main(){
	// freopen("file.in","r",stdin);
	gets(s+1);
	n = strlen(s+1);
	for(int i = 1; i <= n; ++i){
		if(!inq){
			if(s[i] == '\"'){
				inq = 1;
				printf("<");
				continue;
			}
			if(!ins){
				if(s[i] != ' '){
					ans.push_back(s[i]);
					ins = 1;
					printf("<");
				}
			}
			else{
				if(s[i] == ' '){
					ins = 0;
					sz = ans.size();
					for(int j = 0; j < sz; ++j){
						printf("%c",ans[j]);
					}
					printf(">\n");
					ans.clear();
				}else{
					ans.push_back(s[i]);
				}
			}
		}else{
			if(s[i] == '\"'){
				inq = 0;
				sz = ans.size();
				for(int j = 0 ;j < sz; ++j){
					printf("%c",ans[j]);
				}
				printf(">\n");
				ans.clear();
			}else{
				ans.push_back(s[i]);
			}
		}
	}
	if(ans.size()){
		sz = ans.size();
		for(int j = 0; j < sz; ++j){
			printf("%c",ans[j]);
		}
		printf(">\n");
	}
	return 0;
}
```

---

## 作者：liyp (赞：0)

## 思路
很简单的模拟题，我们只需要扫一遍即可。

我们可以开一个变量 $flag$，用于记录在我们扫的时候有没有出现还没有被输出的子字符串。当扫到符合的字符串时，将 $flag$ 标记为 $1$。

当我们扫到一个字符 `` ``（空格）或 `"` 时，我们只需要看一下 $flag$ 的值是否为 $1$，如果是，直接输出记录的子字符串即可。

警告： 

1. 输出子字符串之前要先判断子字符串是否为空，否时才能输出。

2. 在扫完之后也要按照警告一的要求输出一次，防止有子字符串被遗漏。
## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
bool isyin;//默认为false
void out(string z) {printf("<%s>\n", z.c_str());}
int main() {
	string s, k = "";
	getline(cin, s);
	bool flag = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '"') {
			flag = !flag;
			if (flag == 0) {
				out(k);
				k = "";
			}
		}
		else if (s[i] == ' '&&!flag) {
			if (!k.empty()) {
				out(k); k = "";
			}
		}
		else k += s[i];
	}
	if (!k.empty()) out(k);
	return 0;
}
```

---

