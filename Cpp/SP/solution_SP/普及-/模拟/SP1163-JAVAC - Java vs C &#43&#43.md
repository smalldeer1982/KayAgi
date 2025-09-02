# JAVAC - Java vs C &#43&#43

## 题目描述

Apologists of Java and C++ can argue for hours proving each other that their programming language is the best one. Java people will tell that their programs are clearer and less prone to errors, while C++ people will laugh at their inability to instantiate an array of generics or tell them that their programs are slow and have long source code.

  
 Another issue that Java and C++ people could never agree on is identifier naming. In Java a multiword identifier is constructed in the following manner: the first word is written starting from the small letter, and the following ones are written starting from the capital letter, no separators are used. All other letters are small. Examples of a Java identifier are javaIdentifier, longAndMnemonicIdentifier, name, nEERC.

  
 Unlike them, C++ people use only small letters in their identifiers. To separate words they use underscore character ‘\_’. Examples of C++ identifiers are c\_identifier, long\_and\_mnemonic\_identifier, name (you see that when there is just one word Java and C++ people agree), n\_e\_e\_r\_c.

  
 You are writing a translator that is intended to translate C++ programs to Java and vice versa. Of course, identifiers in the translated program must be formatted due to its language rules — otherwise people will never like your translator.

  
 The first thing you would like to write is an identifier translation routine. Given an identifier, it would detect whether it is Java identifier or C++ identifier and translate it to another dialect. If it is neither, then your routine should report an error. Translation must preserve the order of words and must only change the case of letters and/or add/remove underscores.

## 样例 #1

### 输入

```
long_and_mnemonic_identifier
anotherExample
i
bad_Style```

### 输出

```
longAndMnemonicIdentifier
another_example
i
Error!```

# 题解

## 作者：一只书虫仔 (赞：4)

[SP1163 JAVAC - Java vs C &#43&#43](https://www.luogu.com.cn/problem/SP1163)

### Translate

- **本题有多组数据。**
- 给定一个字符串 $s$，分两种情况处理
	- 如果有一个地方为 `_`
    	- 如果后面是小写字母，则把 `_` 去掉换成小写字母的大写形态。
        - 如果后面是大写字母，输出 `Error!` 然后结束程序。
   - 如果有一个地方是大写字母，就把他转化为 `_` 和大写字母的小写形态。
- 如果这个字符串中 `_` 的情况和大写字母的情况共存，也只输出 `Error!` 然后结束程序。

### Solution

这题算水字符串模拟吧（    
首先输入一个字符串 $s$，然后进行判断。   

- 如果这个字符为 `_`，判断后面的字符，如果是大写，就输出 `Error!` 结束，如果不是，就把答案字符串更新，变成大写，记得特判超出字符串范围的情况。
- 如果这个字符为大写字符，就把答案字符串更新，加上 `_` 和小写。
- 为了方便，可以定义一个 $len$ 存放答案字符串长度

但我刚开始觉得这样子有点麻烦吧，然后就写了一个自认为更省事的

- 输入一个字符，然后按照上面的直接输出
- 如果是小写字母，就原样输出。
- 如果是大写字母，就输出 `_` 和小写字母。
- 如果是 `_`

这块就出问题了啊 ……   
所以，还是乖乖的用字符串模拟吧！

---

## 作者：BearBig (赞：2)

### 题目描述
这道题，输入一个字符串，按规定输出，挺简单的。
### 思路分析
首先输入字符串，注意输入可能有空格。
```cpp
getline(cin,tmp);
```
接下来对字符串进行遍历：
* 如果字符串的某一项为 `_` 那么对下一项进行搜查：
	* 如果下一项为小写字母，输出大写字母；
   * 如果下一项为大写字母，输出 `Error!`；
* 如果字符串的某一项为大写字母，就转换成 `_` 和小写字母。
* 如果前一项为大写字母，同样输出 `Error`。    

```cpp
for(int i=0;i<tmp.length();++i)
{
		if(tmp[i]=='_')
		{
			if(islower(tmp[i+1]))tmp[i+1]-=32;
			if(isupper(tmp[i+1]))
			{
				cout<<"Error!"<<endl;
				break;
			}
      		}
		if(isupper(tmp[i]))
		{
			if(tmp[i-1]=='_')
			{
				cout<<"Error!\n";
				break;
			}
			cout<<'_';tmp[i]+=32;
		}
cout<<tmp[i];
}
cout<<endl;
```
### 代码分享
根据以上步骤，无注释代码如下。
```cpp
#include<iostream>
#include<ctype.h>
using namespace std;
main()
{
string s;while(getline(cin,s))
{
		for(int i=0;i<tmp.length();++i)
		{
			if(tmp[i]=='_')
			{
				if(islower(tmp[i+1]))tmp[i+1]-=32;
				if(isupper(tmp[i+1]))
				{
					cout<<"Error!"<<endl;
					break;
				}
      			}
			if(isupper(tmp[i]))
			{
				if(tmp[i-1]=='_')
				{
					cout<<"Error!\n";
					break;
				}
				cout<<'_';tmp[i]+=32;
		}
		cout<<tmp[i];
	}
cout<<endl;
}
```
**珍爱生命，远离抄袭！**

---

## 作者：cyrxdzj (赞：2)

### 一、题目翻译题意不明确的修正

本题题目翻译题意不明确，漏了一些要点。

- `C++` 语言的变量命名习惯：每个单词全部小写，且单词之间用下划线 `_` 分隔。

- `Java` 语言的变量命名习惯：每个单词直接连接，中间没有任何字符分隔。每个单词的第一个字母使用大写，但第一个单词是个例外，全部小写。

- 你的任务就是，输入一个变量名（不会告诉你这是什么语言的），输出这个变量名的另一种语言的命名习惯。如果出现了错误，输出 `Error!`

### 二、基本思路

参考题意，我们可以得出几条要点：

- 变量名不能以下划线开头或结尾。

- 变量名不能以大写字母结尾，但可以以大写字母结束。

- 变量名不能出现连续 $2$ 个或以上的下划线。

- 变量名不能同时出现大写字母与下划线。

本题可以采用模拟法，一个个地扫描。

### 三、具体思路

- 前期特判，如果变量名不符合第 $1-2$ 条要点，直接报 `Error!`。如果符合，则继续。

- 如果遇到了下划线：
  
  - 如果后一个字母是小写字母：
  
    转换为大写字母，并继续遍历。
  
  - 否则：
  
    报 `Error!`。

- 如果遇到了大写字母：
  
  将其转换为下划线加小写字母的形式。

- 如果遇到了小写字母：
  
  没啥好说的，直接加入答案字符串序列。

- 如果不符合第 $4$ 条要点（使用两个布尔型变量表示）：
  
  报 `Error!`。

由此我们得出了完整代码。

### 四、完整代码

```cpp
#include<iostream>
#include<string>
using namespace std;
string input;
int main()
{
	while(cin>>input)
	{
		if(input[0]=='_'||
			(input[0]>='A'&&input[0]<='Z')||
			input[input.length()-1]=='_')//前期特判。
		{
			cout<<"Error!"<<endl;
			continue;
		}
		bool java_flag=false,cpp_flag=false;//两个flag。
		string ans;
		for(int i=0;i<input.length();i++)
		{
			if(java_flag&&cpp_flag)//同时出现了两种模式。
			{
				ans="Error!";
				break;
			}
			if(input[i]=='_')//下划线。
			{
				if(input[i+1]>='a'&&input[i+1]<='z')//小写字母。
				{
					ans+=input[i+1]-'a'+'A';
					cpp_flag=true;
					i++;
				}
				else//其它字符。
				{
					ans="Error!";
					break;
				}
			}
			else if(input[i]>='A'&&input[i]<='Z')//大写字母。
			{
				ans+='_';
				ans+=input[i]-'A'+'a';
				java_flag=true;
			}
			else//小写字母。
			{
				ans+=input[i];
			}
		}
		cout<<ans<<endl;//输出。
	}
	return 0;//完结撒花！
}

```

### 五、后记

记录：<https://www.luogu.com.cn/record/51893585>。

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：六子轩 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/SP1163)
# 理解题意
- 由于这道题~~好多~~一些地方没讲清楚（加粗的），导致一些问题。

- 如果有一个地方为 '_' 

	- 如果后面是小写字母，则把 '_'  去掉换成小写字母的大写形态。
    
	- 如果后面是大写字母，输出 $\texttt{ 'Error!'}$ 然后结束程序。
    
- 如果有一个地方是大写字母，就把他转化为 '_' 和大写字母的小写形态。

- **如果第一个字符是 '_' 或大写字母，输出 $\texttt{ 'Error!'}$ 然后结束程序。**

- **如果最后一个字符是 '_' ，输出 $\texttt{ 'Error!'}$ 然后结束程序。**

- **如果有几个连续的 '_' ，输出 $\texttt{ 'Error!'}$ 然后结束程序。** 

- 如果同时出现大写字母和 '_'，输出 $\texttt{ 'Error!'}$ 然后结束程序。
# 思路
- 一个字符一个字符地枚举。

- 用 $1$ 个变量来解决 '_' 后面是否小写字母判断问题。

- 用 $2$ 个变量来解决 '_' 和大写字母同时出现的问题。

- 最后再特判一下最后一个字符是不是 '_' 。

# 代码

```cpp
#include<bits/stdc++.h>
#define Err {cout<<"Error!"<<endl;break;}//为了方便，用一个Err来代替“输出 'Error!' 然后结束程序。”的代码
using namespace std;
string s,ss; // s 代表输入的字符串, ss 则代表处理后的新的字符串
bool f,sxhx,sdx;// f 实现了思路中的第2条, sxhx && sdx 则实现了思路中的第3条。
int main(){
	while(cin>>s){
    	ss="";sxhx=0;sdx=0;f=0;//初始化
		for(int i=0;i<s.size();i++){
			if(i==0 && (s[i]=='_' || (s[i]>='A' && s[i]<='Z'))) Err//判断第一个字符是不是 '_' 或大写字母
			else if(s[i]=='_'){// '_' 后面是否小写字母
				sxhx++;//下划线的个数加 1 
				if(s[i+1]=='_') Err//如果后一个字符还是 '_' ,输出 'Error!' 然后结束程序。
				else f=1;//否则将是否为 '_' 设为True,并在下一次判断
			}
			else if(f){//如果上一个字符是 '_'
				if(s[i]>='a' && s[i]<='z') ss+=char(s[i]-32);//如果合法，将其变为大写
				else Err//否则输出 'Error!' 然后结束程序。
				f=0;//归位
			}
			else if(s[i]>='A' && s[i]<='Z'){//如果是大写
				sdx++;//大写字母的个数加 1
				ss=ss+'_'+char(s[i]+32);//将其变为 '_'+小写
			}
			else ss+=s[i];//如果不是以上的特殊情况，什么都不干
			if(sxhx && sdx) Err//同时出现大写字母和 '_'，输出 'Error!' 然后结束程序。
			if(i+1==s.size()){//如果已经枚举到了最后一个字符，准备输出
				if(!f) cout<<ss<<endl;//特判：如果最后一个字符不是 '_' 正常输出
				else Err//输出 'Error!' 然后结束程序。
			}
		}
	}
	return 0;
}

```

---

## 作者：CGDGAD (赞：1)

### 题解 SP1163 「Java vs C++」

----

### 题意

有两种不同的变量命名风格：

- C++ 风格：所有字符采用小写，并用一个下划线分隔开单词。如 `hello_world_luogu`。
- Java 风格：第一个单词全小写，后面的单词首字母大写、其余全小写，如 `helloWorldLuogu`（其实就是小驼峰）。

要求你转换这两种命名风格。

如，输入 `helloWorldLuogu`，输出 `hello_world_luogu`；输入 `hello_world_luogu`，输出 `helloWorldLuogu`。如果某一个变量名不属于任何命名风格，如 `hello_worldLuogu`，输出 `Error!`。

----

### 思路

遍历原变量名中每个字符：

- 如果这个字符是下划线：
  - 如果下一个字符是小写字母：
     
     在新字符串中加入这个字符的大写形式，并继续遍历下一个字符。
  - 如果下一个字符是其他符号：

     Error。
     
- 如果这个字符是大写字母：

  在新字符串中加入一个下划线，以及它的小写形式。
  
- 如果这个字符是小写字母：

  在新字符串中加入这个小写字母。
  
- 如果发现了大写字母和下划线同时存在（这个可以用几个 bool 变量来记录）：
  
  Error。
  
----

### 坑点

这题 AC 率这么低就是因为有几个坑：

- 首字母不能是大写字母，也不能是下划线。

- 尾字母不能是下划线。
  
- 不能有连续多个下划线。

这也是我翻 SPOJ 讨论区才看出来的。

----

### Code

采用 `std::string`，方便操作。

```cpp
#include <string>
#include <iostream>
std::string s;
int main() {
	while (std::cin >> s) {
		const int len = s.length();
		std::string newS;
		bool flag1 = false, flag2 = false;
		if (s[0] == '_' || s[0] >= 'A' && s[0] <= 'Z') { // 判首字母
			puts("Error!");
			continue;
		}
		for (int i = 0; i < len; ++i) {
			if (flag1 && flag2) { // 判多种命名方法混杂的情况
				newS = "Error!";
				break;
			}
			if (s[i] == '_') { // 判下划线
				flag1 = true;
				if (i == len - 1) { // 判尾字母
					newS = "Error!";
					break;
				}
				if (s[i + 1] >= 'a' && s[i + 1] <= 'z') {
					newS += s[i + 1] + 'A' - 'a';
					++i;
					continue;
				} else {
					newS = "Error!";
					break;
				}
			} else if (s[i] >= 'A' && s[i] <= 'Z') { // 判大写字母
				flag2 = true;
				newS += '_';
				newS += s[i] + 'a' - 'A';
			} else { // 其余情况（小写字母）
				newS += s[i];
			}
		}
		std::cout << newS << std::endl;
	}
}
```

---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP1163)

小学生又来写题解啦！

本题显然是**字符串模拟**，认真维护好每个要求即可。

首先先判断是情况一还是情况二，如果同时出现，输出报错信息。

我们可以用一个函数实现上述功能。

若是情况一，**枚举下划线位置**，再加以判断是否报错。

若是情况二，**枚举大写字母位置**。

若什么情况都不是，直接输出原字符串。

其中关于报错的细节在代码中会说明。

## 满分代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
string s;
int len;
int find_op() //寻找属于哪种情况。 
{
	bool a = false, b = false;  
	for (int i = 0; i < len; i++) 
		if (s[i] == '_') //有情况一。 
		{
			a = true;
			break;
		}
	for (int i = 0; i < len; i++) 
		if ('A' <= s[i] && s[i] <= 'Z')  //有情况二。 
		{
			b = true;
			break;
		}
	if (a && b) return -1;  //情况共存，爆掉。 
	if (a) return 1;
	if (b) return 2;
	return 3;  //啥情况都没有。 
}
void calc(int t)
{
	if (t == -1) 
	{
		printf("Error!\n");
		return;
	}
	else if (t == 1)
	{
		if (s[0] == '_' || s[len-1] == '_')     //若首尾是下划线，爆掉。 
		{
			printf("Error!\n");
			return;
		}
		string ans = ""; 
		for (int i = 0; i < len; i++)
		{
			if (s[i] == '_')
			{
				if ('a' <= s[i+1] && s[i+1] <= 'z') //后一个得是小写字母。 
				{
					ans += s[i+1] - 'a' + 'A';
					i++;	//作用为跳过下一个字符。 
				}
				else
				{
					printf("Error!\n");      //不是小写字母，爆掉。 
					return;
				}
			}
			else ans += s[i];
		}
		cout << ans << endl;
	}
	else if (t == 2)
	{
		if ('A' <= s[0] && s[0] <= 'Z')        //首位是大写字母，爆掉。 
		{
			printf("Error!\n");
			return;
		}
		for (int i = 0; i < len; i++)
		{
			if ('A' <= s[i] && s[i] <= 'Z') cout << "_" << (char)(s[i] - 'A' + 'a');  //大写转小写。 
			else cout << s[i];
		}	
		cout << endl;
	}
	else if (t == 3) cout << s << endl; 	//什么情况都没有。 
}
int main()
{
	while (cin >> s)   //处理多组数据。 
	{
		len = s.length();
		int t = find_op();
		calc(t);
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

传送门：[SP1163 JAVAC - Java vs C &#43&#43](https://www.luogu.com.cn/problem/SP1163)

很明显一字符串模拟题，但是要考虑几个问题，这是翻译没有写的，首先如果 `_` 后面还是 `_`，要输出 `Error!`；第二，如果字符串末尾或第一个是 `_`，也要输出 `Error!`；最后，如果字符串第一个是大写，也要输出 `Error!`。

然后就是模拟了：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	string s;
	while (cin >> s)
	{
		if (s[0] == '_' || isupper(s[0]) || s.back() == '_')
		{
			cout << "Error!" << endl;
			continue;
		}
		int len = s.length() - 1;
		string copy = s;
		transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
		int fd = s.find("_");
		string finalans = "";
		if (fd != string::npos && copy != s)
		{
			cout << "Error!\n";
			continue;
		}
		if (fd != string::npos)
		{
			for (int i = 0; i <= len; i++)
			{
				if (s[i] == '_')
				{
					if (isupper(s[i + 1]) || s[i + 1] == '_')
					{
						finalans = "Error!";
						break;
					}
					else
					{
						s[i + 1] = toupper(s[i + 1]);
					}
				}
				else
				{
					finalans += s[i];
				}
			}
		}
		else
		{
			for (int i = 0; i <= len; i++)
			{
				if (isupper(s[i]))
				{
					finalans += "_";
					s[i] = tolower(s[i]);
				}
				finalans += s[i];
			}
		}
		cout << finalans << endl;
	}
	return 0;
}
```


---

## 作者：light_ght (赞：0)

## 模拟与 `Ascii` 码的应用

~~这玩意儿为啥空间给这么大~~ SPOJ特色了属于是

退役之日的一篇题解。

- [题目](https://www.luogu.com.cn/problem/SP1163)传送门

- 题意：

	给定一个字符串 $str$，分两种情况输出每个字符：

    - 如果有一个地方为 `_`：
    
      - 如果后面是小写字母，则把 `_` 去掉，输出该小写字母的大写。
      
      - 如果后面是大写字母，输出 `Error!` 然后直接进入下一组数据（原题面这里错了）。
      
    - 如果有一个地方是大写字母，就输出 `_` 以及该大写字母的小写。
 
     特别地，如果这个字符串中 `_` 和**单独的**大写字母共存，输出 `Error!` 然后进入下一组（又错一次）。

- 卡 AC 的点（还是题面的锅）：
    
    $str$ 的首项不能是 `_` 或者大写字母；尾项不能是 `_`。
	
    不能有多个 `_` 连接。
   
- 那么我们不难发现，只要特判一下上面一点的内容（“不能有多个 `_` 连接”这一点需要在扫描时记得判断），且以 $\Theta(n)$ 的复杂度扫描一遍特判出所有可能导致的 `Error!`，剩下的一定是合法字符串，随后就按照以下方式输出就行了：

	假设目前已经扫描到 $str$ 的第 $i$ 项（记为 $str_i$)。
    
    - 当 $str_i$ 为 `_`，则输出 $str_{i+1}$ 的大写格式（即 `Ascii` 码减少 $32$)；
    
    - 当 $str_i$ 为大写字母，则输出 `_` 和 $str_i$ 的小写格式（即 `Ascii` 码增加 $32$)；
    
    - 否则直接输出 $str_i$。
    
- 代码&注释

```cpp

char str[110]; //比string快,何乐而不为
int len;
bool upper(char s){ //定义函数,判断一个字母是否大写
	return (s>=65&&s<=90);
}
signed main(){
	while(~scanf("%s",str+1)){
		bool lw=0; //判断有无下划线
        bool up=0; //判断有无大写字母
		len=strlen(str+1);
        
		if(str[1]=='_'||upper(str[1])||str[len]=='_'){
        //判断 str 的首项不能是下划线或者大写字母,尾项不能是下划线
			puts("Error!");
			goto endd;
		}	
		for(int i=1;i<=len;i++){
			if(str[i]=='_'){
				lw=1;
				if(upper(str[i+1])||str[i+1]=='_'){
                //判断下划线后不能是大写字母,不能是下划线
					puts("Error!");
					goto endd;
				}	
			}
			if(upper(str[i]))up=1;
		}
		if(up&&lw){ //又有大写又有下划线,舍去
			puts("Error!");
			goto endd;
		}	
		for(int i=1;i<=len;i++){
			if(str[i]=='_')printf("%c",str[++i]-32); //下划线,注意输出的是下一项,下标+1
			else if(upper(str[i]))printf("_%c",str[i]+32); //大写字母
			else printf("%c",str[i]);
		}
		puts("");
		endd:;	
	}
    //system("PAUSE");
}

```

AFO on 29/11/2021。逆旅未定，我亦行人。

---

