# [NEERC 2016] Abbreviation

## 题目描述

定义 word 为一个首字母大写、长度大于 $1$、 其他位为小写字母的单词，如 `Ab`、 `Abc`、 `Abcd` 和 `Abcde`，但 `ab`、`A`、 `AB`、 `ABc` 和 `AbC` 不是。

定义一个 word 串为一个有大于 $1$ 个 word 、每两个 word 中有且只有一个空格的串，如 `International Business Machines`。

现给你若干行，如遇到 word 串则让他变为缩写，缩写方式为：先提取首字母（大写），再加空格和 `(` ，再把全称写出来，最后加上 `)` ，如: `International Business Machines` 可缩写为 `IBM (International Business Machines)` 。

## 样例 #1

### 输入

```
This is ACM North Eastern European Regional Contest,
sponsored by International Business Machines.
The. Best. Contest. Ever.
A Great Opportunity for all contestants.
```

### 输出

```
This is ACM NEERC (North Eastern European Regional Contest),
sponsored by IBM (International Business Machines).
The. Best. Contest. Ever.
A GO (Great Opportunity) for all contestants.
```

## 样例 #2

### 输入

```
ab Ab A Abc AB Abcd ABc Abcde AbC
```

### 输出

```
ab Ab A Abc AB Abcd ABc Abcde AbC
```

## 样例 #3

### 输入

```
Oh  No  Extra Spaces.And,Punctuation Ruin Everything
```

### 输出

```
Oh  No  ES (Extra Spaces).And,PRE (Punctuation Ruin Everything)
```

# 题解

## 作者：heshuxi (赞：9)

#### 这是一个有些繁琐的字符串模拟题。

------------

## 思路简述

1. 首先用一个 ```vector<string>``` 的数组来存储每个单词，**注意要把空格和特殊字符看做一个单独的单词。** 因为可缩写的几个单词之间 **只能** 有 **一个** 空格。

2. 然后开始一个单词一个单词进行模拟。若当前字符是一个无法缩写的串就直接输出；若是一个可缩写的就继续往后判断（ **核心代码** ）：首先看那个串后方是否有一个空格和另一个符合条件的串（即看当前部分是否可以缩写，因为只有一个符合题意的串是无法缩写的），若可以缩写就循环往后并判断，直到无法缩写，这同时也输出它们的缩写（每个的首字母），这部做完后再重新循环一遍把全称也输出（注意还有全称前后的括号、空格）。于是我们就完成了一次缩写。

代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool big(char x){if(x>='A'&&x<='Z')return 1;return 0;}
bool sma(char x){if(x>='a'&&x<='z')return 1;return 0;}
int pd(string a){
    int l=a.length();
    if(!big(a[0])) return 0;
    if(l<=1) return 0;
    for(int i=1;i<l;i++) if(!sma(a[i])) return 0;
    return 1;
}//看该单词是否可以缩写
signed main(){
    string s,no;
    while(getline(cin,s)){
        vector<string>se;int l=s.length();no="";
        for(int i=0;i<l;i++){
            if(big(s[i])||sma(s[i])) no+=s[i];
            else{
                se.push_back(no);no="";no+=s[i];
                se.push_back(no);no="";
            }
        }
        se.push_back(no);no="";
        int n=se.size(),i,j;
        for(i=0;i<n;i++){
            int ii=i;
            if(pd(se[i])){//核心代码如下
                if(i==n-1) {cout<<se[i];continue;}
                if(se[i+1]==" "&&pd(se[i+2])){//后面有空格和另一个符合条件的串
                    for(j=i;j<=n;j++){//往后判断
                        if((j-i)%2==0){
                            if(!pd(se[j])){
                                j--;
                                break;
                            }
                            else cout<<se[j][0];//输出缩写
                        }
                        else if(se[j]!=" ") break;
                    }
                    cout<<" (";
                    for(int k=i;k<j-1;k++) cout<<se[k];cout<<se[j-1]<<")";//输出全称
                    ii=j-1;
                }
                else cout<<se[i];
            }
            else cout<<se[i];
            i=ii;
        }
        cout<<endl;
    }
	return 0;
}
```

个人认为这个题其实没有什么太难的算法，但细节比较繁琐，比较耗时间，比较需要耐心。可以将这种题目用来练习自己的代码能力、耐心以及细心程度。

近年的 ```CSP``` 、 ```NOIP``` 其实也有不少这样的题，如 [时间复杂度](https://www.luogu.com.cn/problem/P3952) ，同样是字符串的模拟； [种花](https://www.luogu.com.cn/problem/P8865) ，一个带点前缀和的模拟等。

如果还有问题可以私信我。

希望管理员大大通过。

---

## 作者：luojingjie (赞：2)

# P6964 [NEERC2016] Abbreviation
[题目传送门](https://www.luogu.com.cn/problem/P6964)
## 题目大意
我们需要替换文本中可缩写单词序列，可缩写单词序列是由一个或多个首字母大写，其余字母小写的单词组成，单词之间有一个空格分隔。替换后由每个单词的首字母组成，后面跟一个空格，一个左括号、原始可缩写单词序列和一个右括号。
## 关键点
### 单词识别
1. 一个单词由一个或多个字母组成的序列。
2. 由一个首字母大写，后面紧跟着一个或多个小写字母。
### 可缩写序列
1. 可缩写序列由两个或多个首字母大写的单词组成，单词之间有一个空格。
2. 序列中不能包含其他特殊符号。
## 代码

```python
import re  
 
def abbreviate_text(text):  
    # 匹配多个首字母大写的单词序列  
    pattern = re.compile(r'\b[A-Z][a-z]+(?:\s[A-Z][a-z]+)+\b')  
      
    def abbreviate_match(match):  
        words = match.group(0).split()  
        abbreviation = ''.join(word[0] for word in words)  
        full_sequence = match.group(0)  
        return f"{abbreviation} ({full_sequence})"  
      
    # 使用正则表达式替换  
    result = pattern.sub(abbreviate_match, text)  
    return result  
   
input_lines = []  
try:  
    while True:  
        line = input()  
        input_lines.append(line)  
except EOFError:  
    pass  
  
for line in input_lines:  
    print(abbreviate_text(line))
```

---

## 作者：ZPB2011 (赞：2)

# Abbreviation

[题目传送门](https://www.luogu.com.cn/problem/P6964)

题意：给出若干行字符串，简写开头为大写字母，其他为小写字母的字符串，且必须大于两个，中间有空格。

思路：这是一道~~烦人的~~大模拟，思路很简单，就是每输入一行就用一个`vector<int>`记录下来然后进行输出，按题目模拟即可。

易错点：要在每次输出完一行后清空`vector`。

AC code：

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector <string> word;

bool checkword(string s) {//判断是否为word
	if(s[0] < 'A' || s[0] > 'Z') return false;
	if(s.size() <= 1) return false;
	for(int i = 1; i < s.size(); i++) {
		if(s[i] < 'a' || s[i] > 'z') return false;
	}
	return true;
}

void solve() {//输出
	for(int i = 0; i < word.size(); i++) {
		int i2 = i;
		if(checkword(word[i])) {
			if(i != word.size() - 1) {
				if(word[i + 1] == " " && checkword(word[i + 2])) {//可以缩写
					int j;
					for(j = i; j < word.size(); j++) {
						if((j - i) % 2 == 0) {
							if(!checkword(word[j])) {
								j--; 
								break;
							}
							else cout << word[j][0];
						}
						else if(word[j] != " ") break;
					}
					cout << " (";
					for(int k = i; k < j - 1; k += 2) cout << word[k] << ' ';
					cout << word[j - 1] << ')';
					i2 = j - 1;
				}
				else cout << word[i];//无法缩写
			}
			else cout << word[i];//无法缩写
		}
		else cout << word[i];
		i = i2;
	}
} 

int main() {
	string s;
	while(getline(cin, s)) {
		string str = "";
		for(int i = 0; i < s.size(); i++) {//输入
			if((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z')) str += s[i];
			if((s[i] < 'A' || s[i] > 'Z') && (s[i] < 'a' || s[i] > 'z')) {
				word.push_back(str);
				str = "";
				str += s[i];
				word.push_back(str);
				str = "";
			}
		}
		word.push_back(str);
		solve();
		word.clear();//记得清空！
		cout << endl;
	}
	return 0;
}
```

---

## 作者：Daniel_xu (赞：0)

# 题意简述
定义 word 为一个长度大于 $1$、首字母大写、其他为小写字母的单词。如果有连续出现大于 $1$ 个 word，且 word 之间有且仅有一个空格，则将这些 word 缩写，即提取首字母并用括号括起来实际的 word。
# 思路
本题为模拟，考验字符串处理能力。\
整体思路：逐行处理。\
对于每一行：
1. 处理字符串：将带空格的字符串拆分为单词部分与非单词部分，并且记录这个单词是否为 word，便于之后处理。
2. 对于每一个单词，向后依次寻找能与他构成缩写的单词，并记录其首字母，便于之后输出。
3. 输出结果。
# 注意事项
- 由于输入中含有空格建议使用 getline 进行输入。
- 不要忘记处理标点。
- 不要忘记处理最后一个单词后面的非单词部分。
# AC 代码

```cpp
#include<iostream>
#include<cstring>
#include<string>
using namespace std;
const int N=125;
string word[N];//每一个单词 
string pre[N];//第i个单词前的非单词部分 
bool isword[N];//第i个单词是否是word 

string mysubstr(string str,int l,int r){//截取str中的[i,j]区间 
	return str.substr(l,r-l+1);
}

bool f(string str,int len){//判断一个单词是否为word 
	if(len<=1)return false;
	if(islower(str[0]))return false;
	for(int i=1;i<len;i++){
		if(isupper(str[i]))return false;
	}
	return true;
}

bool work(){
	string str;
	if(!getline(cin,str))return false;
	int n=str.length();
	str+=" ";n++;//后面加一个空格，便于处理 
	int l=0,r=0;
	int len=0;
	string p="";
	//处理字符串 
	while(r<n){
		if(l==r && !isalpha(str[l])){
			p+=str[l];
			l++,r++;
		}else if(!isalpha(str[r])){
			pre[++len]=p;
			word[len]=mysubstr(str,l,r-1);
			isword[len]=f(word[len],r-l);
			l=r;
			p="";
		}else{
			r++;
		}
	}
	//输出 
	for(int i=1;i<=len;i++){
		int j=i;
		string s;s+=word[i][0];
		while(j<len && isword[j+1] && pre[j+1]==" ")j++,s+=word[j][0];//向后寻找 
		if(i==j || !isword[i]){//无法构成缩写 
			cout<<pre[i]<<word[i]; 
		}else{//可构成缩写 
			cout<<pre[i];
			cout<<s<<" ("<<word[i];
			for(int k=i+1;k<=j;k++){
				cout<<pre[k]<<word[k];
			}
			cout<<")";
			i=j;//别忘了更改下标i 
		}
	}
	cout<<p<<'\n';//别忘了输出最后的非单词部分 
	return true;
}
int main(){
	while(work());
	return 0;
}
```

---

## 作者：ddgtang (赞：0)

# 题解P6964

## 题目翻译：

### 题目描述
定义 $word$ 为一个首字母大写、长度大于 $1$ 、 其他位为小写字母的单词，如 `Ab`、 `Abc`、 `Abcd`、 和 `Abcde`，但 `ab`、`A`、 `AB`、 `ABc` 和 `AbC`。

定义一个 $word$ 串为一个有大于 $1$ 个 $word$ 、每两个 $word$ 中有且只有一个空格的串，如 `International Business Machines`。

现给你若干行，如遇到 $word$ 串则让他变为缩写，缩写方式为：先提取首字母（大写），再加空格和 `(` ，再把全称写出来，最后加上 `)` ，如: `International Business Machines` 可缩写为 `IBM (International Business Machines)` 。

### 输入格式
若干行（不超过 $1000$ 行）由大小写字母、标点和空格组成的的字符串（每行不超过 $120$ 个字符）。

### 输出格式
缩写后的若干行字符串（无法缩写的不用缩写）。


## 思路
先用一个 $vector<string>$ 存单词和符号，再定义一个 $bool$ 函数判断属不属于 $word$，在每一个单词、符号的处理中使用。

## $Code:$
```cpp
//复制到Dev里食用口感更佳
#include<bits/stdc++.h>
using namespace std;
vector <string> word;//存放单词和符号

bool bigletter(char c){//判断是不是大写字母
	if(c>='A'&&c<='Z') return true;
	return false;
}
bool smallletter(char c){//判断是不是小写字母
	if (c>='a'&&c<='z') return true;
	return false;
}

bool bigletterword(string s){//判断是不是word
	if (!bigletter(s[0])) return false;
	if (s.size()<=1) return false;
	for (int i=1;i<s.size();i++){
		if (!smallletter(s[i])) return false;
	}
	return true;
}

void work(){//处理每一个单词或符号
	int n=word.size();
	for (int i=0;i<n;i++){
		int inow=i;
		if (!bigletterword(word[i]))//如果不需要缩写则直接输出
			cout<<word[i];
		if (bigletterword(word[i])) {
			if (i!=n-1){//最后一位要么跟着前面的缩写，要么就是只有一个符合的所以不用缩写
				if (word[i+1]==" "&&bigletterword(word[i+2])){
					int j;
					for (j=i;j<n;j++){
						if ((j-i)%2==0){
							if (!bigletterword(word[j])){
								j--; 
								break;
							}
								
							else cout<<word[j][0];
						}
						else if (word[j]!=" ") break;
						
					}//j停在了最后符合要求的word的最后一位的后面一位
					cout<<" (";
					for (int k=i;k<j-1;k+=2)
						cout<<word[k]<<' ';
					cout<<word[j-1]<<')';
					inow=j-1;//i直接跳过缩写的部分
				}
				else cout<<word[i];
			}
			else cout<<word[i];
		}
		i=inow;
	}
} 

int main(){
	//文件输入（不用理睬）
	//freopen("P6964_cin_1.txt","r",stdin);
	//freopen("P6964_cout_1.txt","w",stdout);
	//freopen("P6964_cin_2.txt","r",stdin);
	//freopen("P6964_cout_2.txt","w",stdout);
	//freopen("P6964_cin_3.txt","r",stdin);
	//freopen("P6964_cout_3.txt","w",stdout);
	
	string s;
	while(getline(cin,s)){
		if (s.size()==0) break;//如果输入为空就停止
		string w="";//存放单词
		for (int i=0;i<s.size();i++){//循环s
			if (bigletter(s[i])||smallletter(s[i])) w+=s[i];//如果是字母则直接压到s里
			if (!bigletter(s[i])&&!smallletter(s[i])){//否则把单词压到word了，并把符号也压进去
				word.push_back(w);
				w="";
				w+=s[i];
				word.push_back(w);
				w="";
			}
		}
		word.push_back(w);//把最后一个单词压进去
		work();
		word.clear();//清空word
		cout<<endl;
	}
	//关闭文件（不用理睬）
	//fclose(stdin);
	//fclose(stdout); 
	
	return 0;//完美结束
}
```


---

