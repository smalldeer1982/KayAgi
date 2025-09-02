# Punctuation

## 题目描述

有一个文本，包含小写字母、空格和标点（点、逗号、感叹号和问号），连续的字母组成的序列称为单词。

你的任务是修改这个文本，使它满足一下规则：

1. 相邻两个单词间最多只能有一个空格

2. 标点的前面没有空格，后面有一个空格

（保证两个标点间至少有一个单词，文本的开头、结尾都是字母）

## 样例 #1

### 输入

```
galileo galilei was an   italian physicist  ,mathematician,astronomer
```

### 输出

```
galileo galilei was an italian physicist, mathematician, astronomer
```

## 样例 #2

### 输入

```
galileo  was  born  in  pisa
```

### 输出

```
galileo was born in pisa
```

# 题解

## 作者：清小秋ovo (赞：6)

# CF147A
[原题传送门](https://codeforces.com/problemset/problem/147/A)

[洛谷传送门](https://www.luogu.com.cn/problem/CF147A)

这是一道不错的模拟题。

给出一段文本（包含空格），输出整理后的文本。

其中每个单词要以空格隔开，标点和前一个单词之间没有空格，跟后一个单词之间有空格。

## 解题思路

首先，全行读入字符串。

扫描字符串，如果该字符为字母，直接输出。

如果该字符为空格，则进入第二个循环开始往后面扫，并记录连续空格数量。

注意：这里需要特判在空格区间内是否出现了标点符号，因为需要不同的处理方法：（* 号代表空格）
```
处理前：A****BC
处理后：A*BC
```
```
处理前: A****,BC
处理后: A,*BC
```
其区别在于，如果是一个纯空格组成的区间，需要输出一个空格隔开两个单词，但是如果空格区间中出现了标点符号，按照规则标点符号应该是紧贴上一个单词的，所以不应该输出空格。所以这里需要统计空格区间是否为一个纯空格区间还是一个存在标点符号的区间。

随后只需要将指针挪到空格结束的地方，继续进行判定即可。

如果扫描到标点符号，则需要判定标点符号的下一个是否为字符。因为标点符号后面不应该有存在字符，所以应当提前输出一个空格。否则直接输出标点。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

bool is_punc(char a){ //判断是否为标点符号
    bool flag=false;
    if(a==',')flag=true;
    if(a=='!')flag=true;
    if(a=='.')flag=true;
    if(a=='?')flag=true;
    return flag;
}

int main()
{
   string a;
   getline(cin,a); //getline可以全行读入
   int cnt=1; //计数器
   bool flag=true; //判断区间是否为纯空格区间还是空格+标点区间
   bool space=false; //是否出现了空格区间
   for(int i=0;i<a.length();i++){
       flag=true;
       cnt=1;
       space=false; //变量归零
       if(isalpha(a[i]))cout<<a[i]; //如果为字符直接输出
       if(a[i]==' '){
           space=true;
           for(int j=i+1;j<a.length();j++){ //如果出现空格，则开始循环扫描
               if(a[j]!=' '&&!is_punc(a[j])) break;//判定为纯空格区间
               else if(is_punc(a[j])){ //判定为空格+标点区间 
                   flag=false;
                   break;
               }
               else cnt++;
           }
       }
       if(space){
           if(flag){//对应的挪动指针
               cout<<' ';
               i+=cnt-1;
           }else{
               i+=cnt;
           }
       }
       if(is_punc(a[i])&&isalpha(a[i+1])){//对于出现标点的两种情况的判断
           cout<<a[i];
           cout<<' ';
       }else if(is_punc(a[i])&&!isalpha(a[i+1])){
           cout<<a[i];
       }
   }
}

```
完结撒花！

---

## 作者：TheSky233 (赞：1)

## Description
给定一个字符串，给出字符串经过题意修改之后的结果。

## Solution
### 前置知识
C++ 的 ```<ctype.h>``` 头文件中包含了许多字符检测函数，如 ```isalpha```、```isdigit``` 等。

具体的，（引用自大佬的[这篇博客](https://www.cnblogs.com/ruofengzhishang/p/3881377.html)）
```cpp
isalpha(c)    /*判断是否为英文字符*/
iscntrl(c)     /*判断是否为控制字符*/	
isdigit(c)     /*判断是否为阿拉伯数字0到9*/
isgraph(c)   /*判断是否为可打印字符，若所对应的ASCII码可打印，且非空格字符则返回TRUE*/
islower(c)    /*判断是否为小写英文字母*/
ispunct(c)   /*判断是否为标点符号或特殊符号。返回TRUE也就是代表为非空格、非数字和非英文字母*/
isspace(c)   /*判断是否为空格字符，也就是判断是否为空格(' ')、水平定位字符('\t')、归位键('\r')、换行('\n')、垂直定位字符('\v')或翻页('\f')的情况*/
isupper(c)   /*判断是否为大写英文字母*/
isalnum(c)   /*判断是否为字母或数字*/
isxdigit(c)   /*判断是否为16进制数字*/
```

以 ```isalpha``` 为例，如果字符 $\texttt{c}$ 是个字母，那么 ```isalpha(c)``` 的返回值就为 $1$，否则为 $0$。
### 思路
用 ```getchar()``` 来做。每读进一个字符，就判断它的类型。

1. 如果是字母，按原样输出即可。
2. 如果是空格，就用 ```while``` 把后面所有的空格都过滤了，过滤完如果是字母，输出一个空格，再把这个字母原样输出，如果是字符，到第 $3$ 步。
3. 如果是符号，先输出符号，再输出一个空格，然后重复第 $2$ 步。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

char ch;
bool is;

int main(){
	ch=getchar();
	while(ch!='\n'){
		if(isalpha(ch)) putchar(ch);
		while(isspace(ch))
			ch=getchar(),is=1;
		if(is && isalpha(ch))
			putchar(' '),putchar(ch);
		if(ispunct(ch)){
			putchar(ch); putchar(' ');
			ch=getchar();
			while(isspace(ch)) ch=getchar();
			putchar(ch);
		}
		is=0;
		ch=getchar();
	}
	return 0;
}

```
## Conclusion
目前以 $300ms$ 坐在最优解第一，祝大家 $\color{green}\texttt{AC}$ 愉快！

---

## 作者：封禁用户 (赞：1)

## CF147A Punctuation
[原题链接](https://www.luogu.com.cn/problem/CF147A)
码量最少。时间空间最优解。
## 分析
模拟。

让字符串最终满足三个条件：

1. 两个单词间只有一个空格。

2. 标点的前面没有空格，后面有一个空格。

3. 字符串末无空格。

整行读入，从头扫一遍字符串，边判断边输出。

如果该位为空格，第一种情况：下一位是标点，标点前面不需要输出空格，跳过。第二种情况：下一位是空格或字母，两个单词间只需要一个空格，当下一位不为空格时，输出一个空格。

如果该位为字母，且上一位是标点，标点后面需要一个空格，输出一个空格和该位字母。

否则该位为上一位不为标点的字母或标点，直接输出即可。

## Code
```cpp
#include<iostream>
#define F(n) (s[n]=='.'||s[n]==','||s[n]=='!'||s[n]=='?')
//判断标点
using namespace std;
int main(){
	string s;getline(cin,s); //整行读入
	for(int i=0;i<s.length();i++){
		if(s[i]==' '){
			if(F(i+1)) continue; //空格下一位是标点
			if(s[i+1]!=' ') cout<<" "; //空格下一位是字母
		}
		else if(F(i-1)&&s[i]!=' ') cout<<" "<<s[i]; //上一位是标点 该位为字母 
		else cout<<s[i]; //字母、标点直接输出 
	}
	return 0;
}
```
没有刻意压行，不需要任何多余变量和操作，可能是最简单的解法了。

---

## 作者：infinities (赞：1)

一如既往打广告：[更佳的阅读体验](https://www.luogu.org/blog/209547/solution-cf147a)

本题算是一道字符串的模拟水题，但是坑点不少（各位$dalao$不要像我一样不好好看题导致心态几乎爆炸），现在盘点一下本题坑点：

- 注意题面里的标点指点、逗号、感叹号和问号，如果像我一样一开始没看到的话，可能会崩溃..

- 在处理标点时，要注意标点前面的空格几乎全部要删了

- $string$类型只支持在后面加上字符，如$a+=b$，而并不支持类似于$a-=b$一类的操作，所以，我们就不能直接把标点前面的空格直接删掉了事

- 如果标点前面还是一个标点以及其空格，千万不要删掉那个空格

- 还有...欸？！好像没了...

$code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,flag,num,mi;//flag用来判断字符前面是否含多个空格 
string a,b[10101];//多定义几个字符串，用来“删除”空格 
int main(){
    getline(cin,a);//getline输入一整行 
    for(;ans<a.size();ans++){ 
        if(a[ans]!=' '&&a[ans]!=','&&a[ans]!='.'&&a[ans]!='!'&&a[ans]!='?')flag=0,b[mi]+=a[ans];//如果是字母，接下来的空格可以开始处理了，flag归零 
        else if(a[ans]==' '&&flag==0)flag+=1,b[mi]+=a[ans];//如果是空格并且前面一个字符是字母，打上标记，将空格扔到第mi队尾 
        else if(a[ans]==','||a[ans]=='.'||a[ans]=='!'||a[ans]=='?'){
            flag=1;//打上标记 
            if(b[mi][b[mi].size()-1]==' '&&b[mi][b[mi].size()-2]!=','&&b[mi][b[mi].size()-2]!='!'&&b[mi][b[mi].size()-2]!='.'&&b[mi][b[mi].size()-2]!='?'){//如果前面一个字符是空格并且空格不是标点所带着的，处理一下 
                for(int i=0;i<b[mi].size()-1;i++){//由于空格不能直接删除，只好采用这种方式 
                    b[mi+1]+=b[mi][i];//扔到下一队的队尾 
                }
                mi++;//现在已经开始处理第二队了 
                b[mi]+=a[ans],b[mi]+=' ';//加上标点和空格 
            }else
            b[mi]+=a[ans],b[mi]+=' ';//同上 
        }
    }
    cout<<b[mi];//输出最后的一队
	//return 0; 
}
```
没太多值得总结的，但还是总结一下吧：

模拟题是个好东西，可以提升自己调试代码的能力，不要认为模拟题不值得一做，如果您这么想，可以去看看猪国杀（当然，如果您秒切了猪国杀并且AK了很多比赛，那我没话说，只能$orz$）


---

## 作者：wenlebo (赞：0)

本蒟蒻的第一篇题解。


------------


查看问题，可以看出以下结论：

**空格后不能是空格，标点前不是空格。**

只需设置一个变量记录前面的字符类型是否为空格再按规则看是否输出就行了。

**注意：发现字母后的空格不要马上输出，因为后面可能是标点！！！**

### AC代码：



```
#include <bits/stdc++.h>
using namespace std;
int main(){
	bool last=1;//1为非空格
	string a;
	getline(cin,a);//整行输入，用while读char会略过空格
	for(int i=0;i<a.size();i++){
		switch(a[i]){
			case ' ':
					last=0;//字符为空格
				break;
			case '!':case '?':case ',':case '.':
				cout<<a[i];
				last=0;//不直接输出空格（读到后头的字母会输出）
				break;
			default:
				if(last==0){
					cout<<" ";//空格后为字母，可以输出
				}
				cout<<a[i];
				last=1;//字符非空格
		}
	}
	return 0;
}
```


---

## 作者：haraki (赞：0)

做法分析
---
来一个 getchar 的做法。

用 getchar 有一个坑点需要注意：

**在标点输出空格后，后面字母前面不能再输出空格！**

然后主要的模拟流程就是：

- 读入

	+ 如果是换行符：break 掉。
    
   + 如果是空格：如果没有标点标记，打一个空格标记 space。
   
   + 如果是标点符号：去掉空格标记，输出符号后面再输出一个空格，打一个 **标点标记** dots。
   
   + 如果是字母：如果有空格标记，输出一个空格、去掉空格标记、标点标记，再输出这个字母。
   
空格标记的作用：只输出一个空格。

标点标记的作用：在例如 `haraki_,____a juruo` 时避免输出两个空格。（下划线代表空格）

**Code**
---
```cpp
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
int main(){
	int space=0,dots=0;
	while(1){
		char c=getchar();
		if(c=='\n')break;//换行
		else if(c==' '){
			if(space==0&&dots==0){//标记空格flag
				space=1;
			}
		}else if(c=='.'||c==','||c=='!'||c=='?'){//标点
			space=0;
			dots=1;
			cout<<c<<" ";
		}else{
			if(space==1){//输出一个空格
				cout<<" ";
				space=0;
			}
			cout<<c;
			dots=0;
		}
	return 0;
}
```
P.S. 本代码已开启反抄袭，但不影响阅读。

---

## 作者：　　　吾皇 (赞：0)

### 大水题不知道为什么没人做，代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
#define F(i,a,b) for(int i=a;i<b;i++)
#define B(x) x!='.'&&x!=','&&x!='!'&&x!='?'
string s1,s2;
int main(){
	getline(cin,s1);//完整读入一个中间有空格的字符串 
	F(i,0,s1.size()){
		if(B(s1[i])){
			if(s1[i]!=' ') s2=s2+s1[i];//如果不为标点不为空格直接导入 
			else {
				while(s1[i+1]==' ') i++;//如果是空格找到后面第一个不是空格的 
				if(B(s1[i+1]))s2=s2+' ';//如果不是标点再加空格 
			}
		}
		else {
			s2=s2+s1[i];//是标点直接加 
            while(s1[i+1]==' ') i++;//同理找到第一个不是空格的 
			s2=s2+' ';//再添上一个空格 
		}
	}
	cout<<s2;//输出 
	return 0;
}
```


---

