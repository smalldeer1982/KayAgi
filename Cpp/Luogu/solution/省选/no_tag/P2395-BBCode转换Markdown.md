# BBCode转换Markdown

## 题目背景

BBCode 和 Markdown 是两种常用的格式语言。所谓格式语言指，例如在某些网站评论区发表评论时，可以使用其对你的评论进行修饰，使文字可以有颜色、粗体等各种样式。


## 题目描述

#### ~~PDF版题目: http://pan.baidu.com/s/1i3mxk4t 提取密码 hayc~~

### 2025-7-17：链接炸了

BBCode的语法如下所示：

```plain
[h1]Hello World![/h1]
[h2][i]This is a BBCode[/i][/h2]
[b][i]I love[/i] Olympic [i]Informatics[/i][/b]
```

例如，在标签 `[h1]` 中，在 `[h1]` 和 `[/h1]` 之间包裹的内容属于一级标题，对于这之间的文字要按照一级标题的样式渲染。

请注意 BBCode 要求标签的开闭必须**完整且且嵌套无误**，也就是说，如下列的例子都是不合法的 BBCode：

```plain
[h1]Hello World! //标签未闭合
[h1]Hello World![/h2] //两个标签不匹配
[h1][i]Hello World![/h1][/i] //嵌套次序错误
```

另外，极其重要的一点是，BBCode有一个特殊的标签[quote][/quote]，在其中的任意文字都不应被解析为BBCode代码，而应该对其进行Markdown化处理后被原样输出。

现在介绍Markdown。其语法如下所示：

```cpp
# Hello World! #
## *This is a Markdown* ##
__*I love* Olympic *Informatics*__
```

你的任务就是将给定的一串 BBCode 转换成 Markdown，并对不合法的输入报错。

题目数据中会出现的所有 BBCode 的标签与其对应 Markdown 对应关系如下，保证不出现除此之外的对应：

 ![](https://cdn.luogu.com.cn/upload/pic/1493.png) 

对于 `[quote]` 标签的附加说明：

![](https://cdn.luogu.com.cn/upload/pic/1494.png)


## 说明/提示

为保证评测顺利不被误判，请注意下列要求：

尊重原输入输出的换行，不自行添删。

对于第一条的例外是， 遇到 `[quote]` 标签不在新的一行时，Markdown 中请另起一行。另外 `[quote]` 标签中的代码段头尾空行请去除，不会出现空白的 quote。

请注意上表中的空格。

对于不合法的 BBCode 输入，你的程序必须报错：

- 对于匹配错误的标签输出 `Match Error`；
- 对于未闭合的标签输出 `Unclosed Mark`，请参考样例。

两种情况同时出现的时候（即同时有匹配错误和未闭合的标签时），按照匹配错误处理，输出 `Match Error`。

由于 quote 标签的特殊性，为保证不出现歧义，数据保证 quote 标签不会出现错误。

例如：对于出现如 `[i][h1]Text[/i]` 这样的情况，按照 `Match Error` 处理，对于 `[i][h1]Text[/h1]` 这样的情况，按照 `Unclosed Mark` 处理。

由于洛谷限制，请大家在输出 `Unclosed Mark` 的时候在 `close` 中间切开分为两段字符串输出，否则会被吞记录。

保证以下三种字符不出现在除quote标签包裹的段落中的文字中：`[` `]` `/` `*` `_` `#` `>`，但地址中可能会出现/字符。

保证输入不会出现标签不完整的情况，例如 `[h1]Text[/h`。

对于曾经在其他地方使用过 Markdown 与 BBCode 的同学：题中的格式不是严格的 BBCode 与 Markdown 格式，请勿被经验迷惑。


## 样例 #1

### 输入

```
[h1]Hello World![/h1]
[h2]How are [i]you[/i]?[/h2]```

### 输出

```
# Hello World! #
## How are *you*? ##```

## 样例 #2

### 输入

```
[h1]Introducing Swift.[/h1][quote]
import SpriteKit
let object = SKSpriteNode(imageNamed: “[L2/Ascention]”
[/quote]```

### 输出

```
# Introducing Swift. #
> import SpriteKit
> let object = SKSpriteNode(imageNamed: “[L2/Ascention]”```

## 样例 #3

### 输入

```
[h1]I knew you were
trouble when you walked in[/h1]
[url=http://www.example.com]By Taylor Swift[/url]```

### 输出

```
# I knew you were
trouble when you walked in #
[By Taylor Swift](http://www.example.com)```

## 样例 #4

### 输入

```
[h1]Thanks for [i]inviting[/h1] me.[/i]```

### 输出

```
Match Error```

## 样例 #5

### 输入

```
[h2]Your gift is awesome!```

### 输出

```
Unclosed Mark```

## 样例 #6

### 输入

```
[quote][/quote][/quote]```

### 输出

```
Match Error
(对该数据的解释: 匹配到第一个关闭标签后即不认为后面的内容仍是代码段)```

## 样例 #7

### 输入

```
[quote][quote][/quote]```

### 输出

```
> [quote]```

# 题解

## 作者：Macesuted (赞：11)

[在此处阅读体验更佳](https://www.macesuted.cn/article/luogu2395/)

[题面](https://www.luogu.com.cn/problem/P2395)

# 题意
给出一段 BBCode 格式的代码，让你将其转换为 Markdown 格式。

具体语法展示在题面中，其中减少了相当多的语法，并且对输入的代码作出了一些大大减轻码量的限制。
# 分析
如果是让你将一个没有语法问题的 BBCode 代码转换成 Markdown 代码，相信一定不难。对于除 `quote` 以外的指令，你可以使用直接替换的方式转换代码，如 `[h1]` 转换为 `# `, `[/b]` 转换为 `__`。而 `quote` 则相对难处理，因为 `quote` 块内可能出现其他的标识符，从而影响你的解析。事实上你只需要找到 `[quote]` 出现后的第一个 `[/quote]`，然后将他们中间的部分拿出来直接作为 `quote` 块即可。

那么我们考虑可能存在语法错误的情况。

1. **标签匹配错误**：解决标签匹配错误最常规的方法，就是开一个指令栈。每当遇到一个起始标签，就将它压入指令栈；遇到一个结束标签，就检查指令栈的栈顶是否与它对应。如果不对应，则说明出现了 `Match Error` 情况。
2. **标签未闭合**：在上文指令栈的基础上，只需要在处理完整个输入之后判断一个指令栈是否不为空。如果不为空，则说明还有些标签是失配的，出现了 `Unclosed Mark` 情况。

毕竟是大模拟，细节处还需参见代码。

# 代码
```cpp
/**
 * @file P2395.cpp
 * @author Macesuted
 * @date 2020-12-21
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <bits/stdc++.h>
using namespace std;

//需压入指令栈的操作的对应值
#define val_h1  1
#define val_h2  2
#define val_i   3
#define val_b   4
#define val_url 5
#define val_img 6

#define bufferSiz 1 << 16
char B[bufferSiz], *_S = B, *_T = B;
#define getchar() (_S == _T && (_T = (_S = B) + fread(B, 1, bufferSiz, stdin), _S == _T) ? EOF : *_S++)

string output;//输出缓存
stack<int> cmdStack;//指令栈
stack<string> infoStack;//URL信息临时存储栈

void checkStack(int val)
{
    if(cmdStack.empty()||cmdStack.top()!=val) puts("Match Error"),exit(0);//如果栈顶标签与此标签不同
    return cmdStack.pop();
}

int main() {
    char c=getchar();
    while(c!=EOF)
    {
        if(c=='[')
        {//开始读入标签
            string cmd="";
            c=getchar();
            while(c!=']') cmd.push_back(c),c=getchar();
            //此时已经读入完整的标签（在中括号中间的内容）
            bool reverse=false;//false表示起始标签，true表示结束标签
            if(cmd[0]=='/') reverse=true,cmd=cmd.substr(1);
            if(cmd=="h1")
            {//直接转换
                if(!reverse) output.append("# "),cmdStack.push(val_h1);
                else output.append(" #"),checkStack(val_h1);
            }else if(cmd=="h2")
            {//直接转换
                if(!reverse) output.append("## "),cmdStack.push(val_h2);
                else output.append(" ##"),checkStack(val_h2);
            }else if(cmd=="i")
            {//直接转换
                output.push_back('*');
                if(!reverse) cmdStack.push(val_i);
                else checkStack(val_i);
            }else if(cmd=="b")
            {//直接转换
                output.append("__");
                if(!reverse) cmdStack.push(val_b);
                else checkStack(val_b);
            }else if(cmd.substr(0,3)=="url")
            {
                if(!reverse) infoStack.push(cmd.substr(4)),//由于URL信息在Markdown中后置，所以开栈临时存储
                output.push_back('['),cmdStack.push(val_url);
                else output.append("]("+infoStack.top()+")"),infoStack.pop(),checkStack(val_url);
            }else if(cmd.substr(0,3)=="img")
            {//与上面唯一的区别就是'['的左侧多了一个'!'
                if(!reverse) infoStack.push(cmd.substr(4)),output.append("!["),cmdStack.push(val_img);
                else output.append("]("+infoStack.top()+")"),infoStack.pop(),checkStack(val_img);
            }else if(cmd=="quote")
            {//由于quote的特殊性，这里一次性读到quote的结束标签
                char c=getchar();
                while(c=='\n'||c=='\r') c=getchar();//删除quote块的头部空行
                string cache="";//cache临时存储读进来的所有内容
                while(c!=EOF)
                {
                    cache.push_back(c);
                    //如果cache字符串的末尾是"[/quote]"，说明已结束
                    if(cache.size()>7&&cache.substr(cache.size()-8)=="[/quote]") break;
                    c=getchar();
                }
                if(c==EOF) { puts("Match Error"); return 0; }//如果读完了全文还没有读到结束标签
                //比较愚笨的删除方法
                cache.pop_back(),cache.pop_back(),cache.pop_back(),cache.pop_back(),
                cache.pop_back(),cache.pop_back(),cache.pop_back(),cache.pop_back();
                while(cache.back()=='\n'||cache.back()=='\r') cache.pop_back();//删除quote块的尾部空行
                if(output.back()!='\n'&&output.back()!='\r') output.push_back('\n');//quote块前需有空行
                output.append("> ");//以头部符号开始
                for(string::iterator i=cache.begin();i!=cache.end();i++)
                {
                    output.push_back(*i);
                    if(*i=='\n'||*i=='\r') output.append("> ");//每次换行都新增头部符号。
                }
                output.push_back('\n');//最后需要换行
            }
        }
        else output.push_back(c);//如果是常规字符，则应该输出
        c=getchar();
    }
    if(!cmdStack.empty()) { printf("Unclos"),puts("ed Mark"); return 0; }//如果指令栈没空
    printf("%s\n",output.c_str());//输出缓存的输出
    return 0;
}
```

---

## 作者：rzh123 (赞：8)

# P2395 题解  

题目链接：[P2395 BBCode转换Markdown](https://www.luogu.com.cn/problem/P2395)  

不算太大的字符串模拟题，是把 BBCode 转换成 Markdown。  

目前还没有转换 Token 做的题解。  

既然是一种语言转另一种语言，也类似于一个编译器，模拟编译器常见的思路就是转换 Token。  
Token 就是代码中的一个元素，比如这道题中就有两种 Token：  

+ 标签：一对方括号内一个合法的 BBCode 命令  
+ 文本：除标签外的其他内容  

用结构体存储 Token，存类别、文字或标签名、参数。  

## Step 1  

先把 BBCode 转成 Token。  

为了方便转换，这里先忽略 `[quote][/quote]` 中的标签按文本处理的特殊情况，都按标签处理，之后特判。  

`[url]` 和 `[img]` 要特殊处理，另外存储“参数”（`=` 之后 `]` 之前的内容）  

## Step 2  

检查 BBCode 是否合法。  

用栈模拟，遇到开始标签就把标签名压入栈，遇到结束标签就弹出栈顶。如果弹出时发现栈为空，或者弹出的标签与结束标签不匹配，就是 `Match Error`，如果到最后栈不为空，就是 `Unclosed Mark`。  

特判 `[quote]`：遇到 `[quote]` 就压栈后直接扫到 `[/quote]` 为止（数据保证 `[quote]` 标签不会出现错误），然后直接弹出。  

## Step 3  

转换 Markdown。  

遍历 Token，标签基本都可以替换，如 `[h1]` 换成 `# `，`[/h1]` 换成 ` #` 等。  

带参数的标签（`[url` 和 `[img]`），由于 Markdown 的参数是后置的，要让结束标签知道匹配的是哪个，所以还要用一个栈，遇到带参数的开始标签就把参数压入栈，遇到对应的结束标签就弹出参数输出。  

特判 `[quote]`：如果遇到的 `[quote]` **不是整个程序中的第一个 Token，而且它的前一个 Token 结尾不是换行符**，就在前面补一个换行，然后把一对 `[quote]` 之间的所有 Token 转换成纯文本，去掉前导、后缀换行之后，每换一行加 `> `，开头也要加。  

还有一点题目没说清楚，根据常识，`[/quote]` 之后要补一个换行。  

## 代码  

由于没有给定范围，使用了大量 STL。  

```cpp
#include <cstdio>
#include <string>
#include <vector>
#include <stack>
#define fprintf(...)
using std::string;
using std::vector;
using std::stack;
string code;
unsigned cl;
enum TokType{TAG,TEXT};
struct Token{
	TokType t;
	string s;
	string s2;
	Token(){}
	Token(const TokType &_t,const string &_s):
		t(_t),s(_s),s2(""){}
	Token(const TokType &_t,const string &_s,const string &_s2):
		t(_t),s(_s),s2(_s2){}
};
vector<Token> tk;
void readall(){
	char c=getchar();
	while(~c){
		if(c!='\r'){ 
			code+=c;
		} 
		c=getchar();
	}
}
inline void ps(const string &s){
	fputs(s.c_str(),stdout);
}
bool istag(string s){
	string s4;
	if(s.size()>4){ 
		s4=s.substr(0,4);
	}
	else{
		s4="";
	}
	if(
		s=="h1"||s=="/h1"||
		s=="h2"||s=="/h2"||
		s=="i"||s=="/i"||
		s=="b"||s=="/b"||
		s4=="url="||s=="/url"||
		s4=="img="||s=="/img"||
		s=="quote"||s=="/quote"||
	0){
		return 1;
	}
	return 0;
}
void divide(){
	char c;
	string buf;
	cl=code.size();
	for(unsigned i=0;i<cl;){
		c=code[i];
		if(c=='['){
			buf="";
			for(++i;code[i]!=']';++i){
				buf+=code[i];
			}
			if(istag(buf)){
				if(buf[3]=='='){
					tk.push_back(Token(TAG,buf.substr(0,3),buf.substr(4)));
				}
				else{
					tk.push_back(Token(TAG,buf));
				}
			}
			else{
				tk.push_back(Token(TEXT,string()+"["+buf+"]"));
			}
			++i;
		}
		else{
			buf="";
			for(;code[i]!='['&&i<cl;++i){
				buf+=code[i];
			}
			tk.push_back(Token(TEXT,buf));
		}
	}
}
int check(){
	static stack<string> stk;
	for(unsigned i=0;i<tk.size();++i){
		if(tk[i].t==TAG){
			if(tk[i].s[0]=='/'){
				if(stk.empty()){
					puts("Match Error");
					return 1;
				}
				if(tk[i].s.substr(1)!=stk.top()){
					puts("Match Error");
					return 2;
				}
				stk.pop();
			}
			else{
				stk.push(tk[i].s);
				if(tk[i].s=="quote"){
					for(++i;tk[i].s!="/quote";++i);
					stk.pop();
				}
			}
		}
	}
	if(!stk.empty()){
		ps("Unc");
		puts("losed Mark");
		return 3;
	}
	return 0;
}
string plain(const Token &t){
	string r="";
	if(t.t==TEXT){
		r+=t.s;
	}
	else{
		r+='[';
		r+=t.s;
		if(t.s2.size()){
			r+='=';
			r+=t.s2;
		}
		r+=']';
	}
	return r;
}
void quote(const string &t){
	unsigned i=0,s=t.size();
	while(t[i]=='\n'){
		++i;
	}
	while(t[s-1]=='\n'){
		--s;
	}
	ps("> ");
	for(;i<s;++i){
		putchar(t[i]);
		if(t[i]=='\n'){
			ps("> ");
		}
	}
	puts("");
}
void trans(){
	static stack<string> stk;
	for(unsigned i=0;i<tk.size();++i){
		if(tk[i].t==TAG){
			if(tk[i].s=="h1"){
				ps("# ");
			}
			else if(tk[i].s=="/h1"){
				ps(" #");
			}
			else if(tk[i].s=="h2"){
				ps("## ");
			}
			else if(tk[i].s=="/h2"){
				ps(" ##");
			}
			else if(tk[i].s=="i"){
				ps("*");
			}
			else if(tk[i].s=="/i"){
				ps("*");
			}
			else if(tk[i].s=="b"){
				ps("__");
			}
			else if(tk[i].s=="/b"){
				ps("__");
			}
			else if(tk[i].s=="url"){
				ps("[");
				stk.push(tk[i].s2);
			}
			else if(tk[i].s=="/url"){
				ps("](");
				ps(stk.top());
				putchar(')');
				stk.pop();
			}
			else if(tk[i].s=="img"){
				ps("![");
				stk.push(tk[i].s2);
			}
			else if(tk[i].s=="/img"){
				ps("](");
				ps(stk.top());
				putchar(')');
				stk.pop();
			}
			else if(tk[i].s=="quote"){
				string t="";
				int f=666666;
				if(i){
					if(tk[i-1].t==TEXT&&tk[i-1].s[tk[i-1].s.size()-1]=='\n'){
						f=0;
					}
				}
				else{
					f=0;
				}
				if(f){
					puts("");
				}
				for(++i;!(tk[i].t==TAG&&tk[i].s=="/quote");++i){
					t+=plain(tk[i]);
				}
				quote(t);
			}
		}
		else{
			ps(tk[i].s);
		}
	}
}
int main(){
	readall();
	divide();
	if(check()){
		return 0;
	}
	trans();
	return 0;
}
```  



---

## 作者：Eleveslaine (赞：7)

## 前言

码量适中的大模拟，作为我（蒟蒻）的第一道紫题来写个题解。（逃  
思维难度只有普及，代码难度较大~~但是显然没有猪国杀难~~。  

## 分析&代码

从宏观视角来说，本题就是给你一段 BBCode，然后让你转化成 Markdown。

显然有以下思路：一次全部输入完，从头遍历一遍并匹配 `[h1]`，`[h2]`，`[/h1]` 等标签进行处理，处理过程使用一个栈 `st` 来应对可能出现的 Match Error 或 Unclosed Mark 错误。  
设目前遍历到的位置为 `pointer`，初始为 $0$。

- 如果 $s$ 从 `pointer` 开始的一个前缀为 `[h1]`，对应地处理 `[h1]`，`pointer` 向后跳 $4$ 位（即跳到 `[h1]` 后面的第一个字符）；  
- 以此类推，如果 $s$ 从 `pointer` 开始的一个前缀为 $p$，对应地处理 $p$，`pointer` 后移 $|p|$ 位。
- ……
- 如果前面都没有匹配上，说明现在 `pointer` 的位置只是一个普通字符，输出这个字符并 `pointer++` 即可。

给出此部分代码实现（细节放在代码注释中）：

```cpp
// inline bool pd(const string &s,const string &pre)
// 判断 s 从 pointer 开始的前缀是否为 pre
while(pointer<s.length())
    if(pd(s,"[h1]"))
    {
        // st 为自定义 Node 类型的栈
        // Node 有两个属性：int type 和 string info
        // 前者代表标签类型（例如 [h1] 标签 type 为 1），
        // 后者存储其他信息，用于 [url] 和 [img] 标签
        st.push((Node){1,""});
        out("# ");
        pointer+=4;
    }
    else if(pd(s,"[h2]"))
    {
        st.push((Node){2,""});
        out("## ");
        pointer+=4;
    }
    else if(pd(s,"[i]"))
    {
        st.push((Node){3,""});
        out("*");
        pointer+=3;
    }
    else if(pd(s,"[b]"))
    {
        st.push((Node){4,""});
        out("__");
        pointer+=3;
    }
    else if(pd(s,"[/h1]"))
    {
        // MatchError 宏定义，字面意思，触发错误并 break;
        if(st.empty()||st.top()!=1)
            MatchError
        st.pop();
        out(" #");
        pointer+=5;
    }
    else if(pd(s,"[/h2]"))
    {
        if(st.empty()||st.top()!=2)
            MatchError
        st.pop();
        out(" ##");
        pointer+=5;
    }
    else if(pd(s,"[/i]"))
    {
        if(st.empty()||st.top()!=3)
            MatchError
        st.pop();
        out("*");
        pointer+=4;
    }
    else if(pd(s,"[/b]"))
    {
        if(st.empty()||st.top()!=4)
            MatchError
        st.pop();
        out("__");
        pointer+=4;
    }
    ......
```

除了上文直接替换的标签，还存在一些特殊标签需要特殊处理：

1. `[url]` 和 `[img]` 标签。  
以 `url` 为例，它的标准格式为 `[url=A]B[/url]`，识别时的固定前缀为 `[url=`。之后找到第一个 `]` 字符（本题保证 A 中没有 `]`），由此截下 A 部分的内容，随着 `Node` 存入栈中，并先输出一个 `[` 字符；  
中间的 B 可能还含有标签，留给其他部分处理；  
等识别到 `[/url]` 结束标签时，从栈中拿出 A，输出 `](A)`，结束。  
`[img]` 标签同理。  
代码实现：

```cpp
......
else if(pd(s,"[url="))
{
    // [text](url)
    url=s.substr(pointer+5,s.find_first_of(']',pointer)-pointer-5);
    pointer+=6+url.length();
    st.push((Node){6,url});
    out("[");
}
else if(pd(s,"[/url]"))
{
    if(st.empty()||st.top()!=6)
        MatchError
    out("](");
    out(st.top().info.c_str());
    out(")");
    pointer+=6;
    st.pop();
}
else if(pd(s,"[img="))
{
    // ![text](img)
    img=s.substr(pointer+5,s.find_first_of(']',pointer)-pointer-5);
    pointer+=6+img.length();
    st.push((Node){7,img});
    out("![");
}
else if(pd(s,"[/img]"))
{
    if(st.empty()||st.top()!=7)
        MatchError
    out("](");
    out(st.top().info.c_str());
    out(")");
    pointer+=6;
    st.pop();
}
```

2. `[quote]` 标签。  
这个标签可以说是本题中最难处理的了，主要原因是本题对此表述十分不清晰。它的处理过程如下：  
因为它中间的所有标签不用渲染，所以可以一次从 `[quote]` 读到结束标签 `[/quote]`。

- 过滤内容前后的 `\n`，并在最前面插入 "`> ` "。
- 对于中间的每个 `\n`，在其后插入 "`> ` "。
- 其他内容不变。  
（注：不考虑 `\r`，在输入时已经过滤一遍。）  
此外，由于在读 `[quote]` 时已经读完了 `[/quote]`，所以如果还存在落单的 `[/quote]` 那么它前面一定没有 `[quote]`，直接判为 Match Error 即可。  
这里的代码实现见下面剪贴板中 `if(pd(s,"[quote]"))` 部分。

全部处理完后，如果栈不为空，判定 Unclosed Mark。最后如果不存在错误再进行输出。

完整代码见[剪贴板](https://www.luogu.com.cn/paste/cqmoa8tz)。

## 致谢

感谢大模拟之神 @[qwasd](https://www.luogu.com.cn/user/484970) 提供代码优化方面的帮助，%%% Orz！

---

## 作者：囧仙 (赞：6)

## 题目大意

> 将一个 $\text{BBCode}$ 的字符串转换成 $\text{Markdown}$ 格式。具体格式参见下表：  
$$\def\arraystretch{1.5}\begin{array}{|c|c|c|}\hline
\textbf{含义} &\textbf{BBC Code} & \textbf{Markdown} \cr\hline
\text{一级标题} & \verb![h1]文字[/h1]! & \verb!# 文字 #! \cr\hline
\text{二级标题} & \verb![h2]文字[/h2]! & \verb!# 文字 #! \cr\hline
\text{斜体} & \verb![i]文字[i]! & \verb!*文字*! \cr\hline
\text{粗体} & \verb![b]文字[b]! & \verb!__文字__! \cr\hline
\text{链接} & \verb![url=地址]文字[/url]! & \verb![地址](文字)! \cr
\text{图片} & \verb![img=地址]文字[/img]! & \texttt{!}\verb![地址](文字)! \cr\hline
\text{代码块} & \verb![quote]文字[/quote]! & \begin{aligned}&\text{多行，每行前添加}\verb!"> "!\cr&\text{，有空格，不含引号}\end{aligned} \cr\hline
\end{array}$$  
若匹配错误，输出 $\verb!Match Error!$ ；若未闭合，输出 $\verb!Unclosed Mark!$ 。具体细节参见题面。

## 题解

题面描述不清啊……先提及几个可能出现的锅：

- 总输入量比较大，应该是介于 $10^6$ 和 $2\times 10^6$ 之间。如果你用数组存储，建议开到 $2\times 10^6$ 。每个 $\text{url}$ 的最大长度也不清楚……如果用数组，建议开大一些（比如 $50,100$ 之类的）。

- 注意 $\verb!quote!$ 。若 $\verb![quote]!$ 不是另起一行的开头，那么需要换行；在 $\verb![/quote]!$ 后**无论是什么都要加上换行**。

- 题面上说的什么“在输出 $\text{Unclosed Mark}$ 的时候在 $\text{close}$ 中间切开分为两段字符串”意义不明，直接输出 $\verb!Unclosed Mark!$ 就行了。

下面开始正题。

- 对于标记匹配，我们可以用一个栈来维护。具体而言，遇到一个起始标签就入栈，遇到终止标签就弹出栈顶并比较，若不能匹配/栈空了则判定为匹配错误。如果最后还有东西在栈里，那么就判定为未闭合。

- 为了便于比较字符串，我们可以写一两个函数用于辅助我们的判断。比如比较一个字符串是否是另外一个的前缀、向一个字符串末尾增加一个字符串。这两者可在下方的代码中体现。

- 我们可以边读入，边将新的内容加入结果串。注意：我们并不能直接输出，因为在读完这个串前不能保证不会出现标记匹配错误的情况。

- 对于特殊的 $\text{url,img}$ 标记，我们可以另外开一个栈用来存储 $\verb!url=XXX,img=XXX!$ 的内容。在遇到终止标记时，我们可以取出这个特殊栈的栈顶并输出。当然，你也可以存储在输入串中的位置，这样可以节省一些空间。（尽管下面程序并没有这么做）。

其他倒也没什么，只要注意不出锅就行了。顺便附送一个主要是 $\text{quote}$ 的[样例数据](https://www.luogu.com.cn/paste/2l28lsqz)。

不是很难的题，但是 $\verb!quote!$ 卡人的确挺谔谔的……

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int MAXN=5e6+3,MAXM=5e4+3,MAXK=100+3;
char S[MAXN],T[MAXN],Q[MAXN],R[MAXN],M[MAXM][MAXK];
int s,n,t,r,m,o,O[MAXN];
bool cmp(char *A,const char *B){
    for(int p=0;B[p];++p) if(A[p]!=B[p]) return false; return true;
}
void ist(char *A,const char *B,int &l){for(int p=0;B[p];++p) A[l++]=B[p];}
void err(bool t){puts(t?"Match Error":"Unclosed Mark"),exit(0);}
void clc(){
    up(0,s-1,i) if(S[i]=='['){
        for(t=0;t<s&&S[i+t]!=']';++t) T[t]=S[i+t]; T[t++]=S[i+t];  int w=0;
        if(cmp(T,"[h1]")) w=1,ist(R,"# " ,r); else
        if(cmp(T,"[h2]")) w=2,ist(R,"## ",r); else
        if(cmp(T,"[i]" )) w=3,ist(R,"*"  ,r); else
        if(cmp(T,"[b]" )) w=4,ist(R,"__" ,r); else
        if(cmp(T,"[url")) w=5,ist(R,"["  ,r),memcpy(M[m++],T+5,t-6); else 
        if(cmp(T,"[img")) w=6,ist(R,"![" ,r),memcpy(M[m++],T+5,t-6); else 
        if(cmp(T,"[/h1]")) w=-1,ist(R," #" ,r); else
        if(cmp(T,"[/h2]")) w=-2,ist(R," ##",r); else
        if(cmp(T,"[/i]" )) w=-3,ist(R,"*"  ,r); else
        if(cmp(T,"[/b]" )) w=-4,ist(R,"__" ,r); else
        if(cmp(T,"[/url]")) w=-5,ist(R,"]",r); else 
        if(cmp(T,"[/img]")) w=-6,ist(R,"]",r); else 
        if(cmp(T,"[quote]")){
            for(t=0;t<s&&!cmp(S+i+t,"[/quote]");++t) T[t]=S[i+t];
            ist(T,"[/quote]",t); int a=7,b=t-9;
            while(T[a]=='\n') ++a; while(T[b]=='\n') --b;
            if(i>0&&S[i-1]!='\n') R[r++]='\n'; ist(R,"> ",r);
            up(a,b,j){
                if(j>a&&T[j-1]=='\n') ist(R,"> ",r); R[r++]=T[j];
            }
            R[r++]='\n';
        } else if(cmp(T,"[/quote]")) err(1);
        if(w>0) O[o++]=w; if(w<0){if(!o||O[o-1]!=-w) err(1); else --o;}
        if(w==-5||w==-6){
            --m,R[r++]='(',ist(R,M[m],r),R[r++]=')';
            memset(M[m],0,strlen(M[m]));
        }
        i+=t-1,memset(T,0,t);
    } else R[r++]=S[i];
    if(o) err(0);
}
int main(){
    s=fread(S,1,MAXN,stdin),clc(),fwrite(R,1,r,stdout);
    return 0;
}
```

---

## 作者：lusers (赞：5)

[P2395](https://www.luogu.com.cn/problem/P2395)

本篇题解主要展示一些工程化的写法。

## 题意

BBCode -> Markdown

## 分析

字符串大模拟，边读入边处理（流式）。

关于嵌套判断，类括号嵌套可以用栈处理；其余按照题面处理。

Unmatch 和 Unclosed 的区别可以理解为 Unmatch 是栈下溢（Underflow）或栈顶和括号不匹配，Unclosed 是读取完毕后栈喂空。

这题的细节很多，有的时候可能无法理解题面所表达的意思，那么就可以采用“设置”，用 constexpr / 宏控制程序的行为，然后通过调试找到正确的值。

## 代码


*更新*：洛谷升级到了 gcc 13，所以不再需要自定义实现的 `std::ranges::split_view`。代码 643 -> 457 lines。


450+ 行。

<https://www.luogu.com.cn/paste/ro2k5zhk>

简要概述一下：

* BBCodeReader 类，负责流式读取 BBCode 代码并调用回调（就像 SAX 那样）
* MarkdownWriter 类，提供一个回调函数，用于将抽象化的表达式流式转换为 Markdown 代码
* BBCodeIncrementalMarkParser 函数，增量解析 BBCode 方括号标签
* 一些零散的数据结构
* ACTP 命名空间，存储设置（constexpr）


~~其中一小半的代码是一个 `ranges::split_view` 的自定义实现，因为 gcc 11 的 bug 导致 STL 的无法使用。~~


---

## 作者：Milthm (赞：3)

## P2395 题解

### 前置知识

- 模拟

### 题目解法

算是大模拟，又不能完全算。相比鸭棋来说还是保守了。

模拟的话十分简单，按照题意描述即可，判断是否合法只需要一个栈即可。

但是本题真的只有这样吗？

其实本题真正的难点在于如何读懂题目，以及十分多的坑点，本篇题解将会一一叙述。以下是我找到的全部坑点：

#### 一、`url` 与 `img`

关于 `url` 和 `img`，两个的内容里面是会有**嵌套**的，所以不能直接处理，需要一个栈来维护。


#### 二、`quote`

`quote` 的处理方式题目中说的并没有多么清楚，那我们在此说明一下。

为了方便处理换行，这里有个小技巧，读入的时候直接把 `\r` 这种东西不要让它读入进来。

首先，如果 `[quote]` 前不是换行，需要先换一个行。

然后，如果 `[/quote]` 后面没有换行，也需要换一个行。

其次，如果 `[quote]` 后面有换行或者 `[/quote]` 前面有换行，需要消除掉。具体是只消除前后两个还是全部消除，题目中没有明确说明，我是按后者写的，两种写法都能过。

最后，如果检测到了 `[quote]`，那其它的标签都不要判断了，只判断 `[/quote]`。

#### 三、数据范围

输入量大概在 $10^6$ 左右，所以时间复杂度尽量要是 $O(n)$ 的，不然有可能会超时。

剩下的几乎没有坑点了。

### AC 代码

```cpp
#include<iostream>
using namespace std;
char a[4000005],ans[4000005];
int n,zhan[1000005],tot,num,isq,l;
char url[10005][10005];
bool pd(int i,int len,char* c){//判断是否是这个字符串
	for(int j=i;j<i+len;++j){
		if(a[j]!=c[j-i])return 0;
	}
	return 1;
}
void qwq(int x){//不合法判断
	if(zhan[tot]!=x){
		cout<<"Match Error";exit(0);
	}
	else --tot;
}
void add(char c){//往答案里加入字符
	ans[++l]=c;
}
int main(){
	while((a[++n]=getchar())!=EOF){
		if(a[n]=='\r')--n; //别让\r 读入进来！
	}
	a[0]='\n';
	--n;
	for(int i=1;i<=n;){
    //以下是一些简单的判断
		if(isq==0&&pd(i,4,"[h1]")){
			zhan[++tot]=1;
			add('#'),add(' ');
			i+=4;
		}
		else if(isq==0&&pd(i,5,"[/h1]")){
			qwq(1);
		    add(' '),add('#');
		    i+=5;
		}
		else if(isq==0&&pd(i,4,"[h2]")){
			zhan[++tot]=2;
			add('#'),add('#'),add(' ');
			i+=4;
		}
		else if(isq==0&&pd(i,5,"[/h2]")){
			qwq(2);
			add(' '),add('#'),add('#');
			i+=5;
		}
		else if(isq==0&&pd(i,3,"[i]")){
			zhan[++tot]=3;
			add('*');
			i+=3;
		}
		else if(isq==0&&pd(i,4,"[/i]")){
			qwq(3);
			add('*');
			i+=4;
		}
		else if(isq==0&&pd(i,3,"[b]")){
			zhan[++tot]=4;
			add('_');add('_');
			i+=3;
		}
		else if(isq==0&&pd(i,4,"[/b]")){
			qwq(4);
			add('_');add('_');
			i+=4;
		}
		else if(isq==0&&pd(i,5,"[url=")){
			zhan[++tot]=5;
			++num;
			int j=0;
			for(j=i+5;j<=n&&a[j]!=']';++j){
				url[num][j-(i+5)]=a[j];
			}
			url[num][j]='\0';
			add('[');
			i=j+1;
		}
		else if(isq==0&&pd(i,6,"[/url]")){
			qwq(5);
			add(']');
			add('(');
			for(int j=0;url[num][j]!='\0';++j){
				add(url[num][j]);
			}
			--num;
			add(')');
			i+=6;
		}
		else if(isq==0&&pd(i,5,"[img=")){
			zhan[++tot]=6;
			++num;
			add('!');
			int j=0;
			for(j=i+5;j<=n&&a[j]!=']';++j){
				url[num][j-(i+5)]=a[j];
			}
			url[num][j]='\0';
			add('[');
			i=j+1;
		}
		else if(isq==0&&pd(i,6,"[/img]")){
			qwq(6);
			add(']');
			add('(');
			for(int j=0;url[num][j]!='\0';++j){
				add(url[num][j]);
			}
			--num;
			add(')');
			i+=6;
		}
        //重点来啦
		else if(isq==0&&pd(i,7,"[quote]")){
			zhan[++tot]=7;
			isq=1;
			int j=i+7;
			if(a[i-1]!='\n')add('\n');//如果上一个不是换行
			add('>');add(' '); 
			while(a[j]=='\n')++j;//记得往后跳
			i=j;
		}
		else if(pd(i,8,"[/quote]")){
			qwq(7);
			isq=0;
			while(ans[l]=='>'||ans[l]=='\n'||ans[l]==' ')--l;//消除后面换行
			if(a[i+8]!='\n')add('\n');//如果下一个不是换行
			i+=8;
		}
		else{
			add(a[i]);
			if(a[i]=='\n'&&isq)add('>'),add(' ');
			++i;
		}
	}
	if(tot)cout<<"Unclosed Mark";//记得判一下第二种不合法情况
	else for(int i=1;i<=l;++i)putchar(ans[i]);
	return 0;
}

```




---

## 作者：CANTORSORT (赞：2)

## 简要题意

给你一段用格式语言 BBCode 书写的代码，且只含有 **一级标题**、**二级标题**、**斜体文字**、**粗体文字**、**链接**、**图片** 和 **代码段** 这几种格式。要求把这一段代码转换成用 Markdown 语言书写的格式代码。

## 思路

模拟题。但不知道为什么我居然能联想到 [这道题](https://www.luogu.com.cn/problem/P7869)。

为了方便处理，最好把输出存储在一个 `string` 里面。

而且出题人很仁慈地用这样一个样例来提醒我们：

`[h1][i]Hello World![/h1][/i] //嵌套次序错误`

一下子就看出来这些命令的正确嵌套顺序与栈的存储规则 **完全一样**。

于是就可以用栈来存储命令信息（有一点像括号匹配）。

前面四个命令都可以用简短的几行代码来解决；但是后面三个不太好搞。

链接和图片，我们都可以用一个 `string` 类型的 **栈** 来存储网址。

为什么还要用个栈啊？

因为~~毒瘤的~~ Markdown 允许用一张图片作为超链接的文字信息，就像这样：

`[![](https://cdn.luogu.com.cn/upload/image_hosting/925awur2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)](https://www.luogu.com.cn/user/387212)`

可以尝试把上面这段格式代码粘贴到个人主页或云剪贴板，然后你就会发现这个很毒瘤的细节了。

最后就是代码段。

当我们检测到 `[quote]` 时，我们就要直接继续往下输入，用一个 `string` 来存属于代码段的字符，直到检测出 `[/quote]` 为止。

接下来有两个判断：

1. 是否存在形如 `[quote][/quote]` 的情况（就是特判中间是不是空的，样例 6 需要用到）
2. 在开始往输出的字符串中加入代码段时，要先判断前面有没有其他的文字，以此确定要不要换行（具体见样例 7，如果没处理好前面就会多空一行）

所有格式信息都转换完以后，我们还要判断，原先那个我们用来存储命令的栈是不是空的（如果不空，就说明要输出 `Unclosed Mark`）。

## 代码（核心）

代码中的 `io.write()` 是我自己定义的快写函数，改成自己喜欢的输出方式就可以了~

```cpp
string Ans;
stack<int> CmdStack;
stack<string> InfoStack;
map<string,int> CmdMap;
inline void CheckStack(int val)
{
	if(CmdStack.empty()||CmdStack.top()!=val)
	{
		Ans="Match Error";
		io.write(Ans);
		exit(0);
	}
	CmdStack.pop();
}
signed main()
{
	CmdMap["h1"]=1;
	CmdMap["h2"]=2;
	CmdMap["i"]=3;
	CmdMap["b"]=4;
	CmdMap["url"]=5;
	CmdMap["img"]=6;
	char c=getchar();
	while(~c)
	{
		if(c=='[')
		{
			string Cmd;
			c=getchar();
			while(c!=']')
			{
				Cmd+=c;
				c=getchar();
			}
			bool tail=0;
			if(Cmd[0]=='/')
			{
				tail=1;
				Cmd=Cmd.substr(1);
			}
			if(Cmd=="h1")
			{
				if(!tail)
				{
					Ans+="# ",
					CmdStack.push(CmdMap[Cmd]);
				}
				else
				{
					Ans+=" #";
					CheckStack(CmdMap[Cmd]);
				}
			}
			else if(Cmd=="h2")
			{
				if(!tail)
				{
					Ans+="## ";
					CmdStack.push(CmdMap[Cmd]);
				}
				else
				{
					Ans+=" ##";
					CheckStack(CmdMap[Cmd]);
				}
			}
			else if(Cmd=="i")
			{
				Ans+='*';
				if(!tail)
					CmdStack.push(CmdMap[Cmd]);
				else
					CheckStack(CmdMap[Cmd]);
			}
			else if(Cmd=="b")
			{
				Ans+="__";
				if(!tail)
					CmdStack.push(CmdMap[Cmd]);
				else
					CheckStack(CmdMap[Cmd]);
			}
			else if(Cmd.substr(0,3)=="url")
			{
				if(!tail)
				{
					InfoStack.push(Cmd.substr(4));
					Ans+='[';
					CmdStack.push(CmdMap[Cmd.substr(0,3)]);
				}
				else
				{
					Ans+="]("+InfoStack.top()+")";
					InfoStack.pop();
					CheckStack(CmdMap[Cmd.substr(0,3)]);
				}
			}
			else if(Cmd.substr(0,3)=="img")
			{
				if(!tail)
				{
					InfoStack.push(Cmd.substr(4));
					Ans+="![";
					CmdStack.push(CmdMap[Cmd.substr(0,3)]);
				}
				else
				{
					Ans+="]("+InfoStack.top()+")";
					InfoStack.pop();
					CheckStack(CmdMap[Cmd.substr(0,3)]);
				}
			}
			else if(Cmd=="quote")
			{
				if(tail)
				{
					Ans="Match Error";
					io.write(Ans);
					return 0;
				}
				char c=getchar();
				while(c=='\n'||c=='\r')
					c=getchar();
				string Cache;
				while(c!=EOF)
				{
					Cache+=c;
					if(Cache.length()>7&&Cache.substr(Cache.size()-8)=="[/quote]")
						break;
					c=getchar();
				}
				if(Cache.length()>8)
				{
					if(c==EOF)
					{
						Ans="Match Error";
						io.write(Ans);
						return 0;
					}
					rep(i,1,8)
						Cache.pop_back();
					while(Cache.back()=='\n'||Cache.back()=='\r')
						Cache.pop_back();
					if(Ans.length()&&Ans.back()!='\n'&&Ans.back()!='\r')
						Ans+='\n';
					Ans+="> ";
					rep(i,0,Cache.length()-1)
					{
						Ans+=Cache[i];
						if(Cache[i]=='\n'||Cache[i]=='\r')
							Ans+="> ";
					}
					Ans+='\n';
				}
			}
		}
		else
			Ans+=c;
		c=getchar();
	}
	if(CmdStack.size())
	{
		Ans="Unclosed Mark";
		io.write(Ans);
		return 0;
	}
	io.write(Ans);
	return 0;
}
```



---

## 作者：mydcwfy (赞：2)

调了好久，好不容易才过了，给后来人留一些经验，也纪念一下吧。

## 1. 题意

将 BBCode 转化为 Markdown。

1. `[h1]...[/h1]` 转化为 `# ... #`，指一级标题
2. `[h2]...[/h2]` 转化为 `## ... ##`，指二级标题（注意这两个都有空格）
3. `[i]...[/i]` 转化为 `*...*`，指斜体
4. `[b]...[/b]` 转化为 `__...__`，指粗体（注意这两个又没有空格）
5. `[url=A]B[/url]` 转化为 `[B](A)`，指链接
6. `[img=A]B[/img]` 转化为 `![B](A)`，指图片（注意这两个的顺序）
7. `[quote]...[/quote]` 转化为 `> ...`，指代码块（注意换行，这个也是最难处理的）

如果不匹配输出 `Match Error`，如果最后没有都匹配，输出 `Unclosed Mark`。`Match Error` 优先。

`[quote]` 一定不会出现歧义。可能会出现嵌套。

`[,],*,_,#,>,/,` 不会在除 `[quote]` 包裹的代码块外出现，但 `/` 可能在 `[url=A]` 或 `[img=A]` 中出现。但 `[url=A]` 或 `[img=A]` 中的 `A` 不会出现嵌套。

## 2. 各种情况

相信大家看到这个题的时候，直接会想到用栈来维护嵌套，这里就不多讲了。

下面给出每一个转义的一些注意事项（毒瘤的题目，坑点比较多）：

#### 1）一级标题 / 二级标题

这两个注意要输出空格，开始的时候要输出空格，结束的时候也要输出空格。

#### 2）斜体 / 粗体

唯一没有坑点的转义了吧……

#### 3）链接

首先，判断的时候，如果从 `[` 开始的话，匹配到要将指针向后移动 5 位，输出一个 `[`，然后将后面的东西存入一个数组，然后碰到 `]` 结束。碰到 `[/url]` 之后，输出 `](` 后，然后将存的东西输出。 

#### 4）图片

这个除了上面链接的坑点之外，还有一个：在判断他是哪一个转义的时候，注意判断转义后面的字符是不是 `]` 或 `=`，否则的话，`img` 会被识别为斜体。

#### 5）代码块

这个最特殊也最麻烦……

首先，注意判断 `[quote]` 前面有没有 `\n`，如果有的话，就不需要再输出一个换行了。

每一个碰到 `\n` 的时候，自动输出一个 `\n> `，但是最后的时候要判断是不是 `[/quote]`，最后一个如果还是 `\n` 的话不需要输出，因为代码块结束的时候自己会输出一个 `\n`。

结束的时候，如果本身有 `\n`，也应该跳过，不然的话就会 `Too short on line x`。

#### 6）其他

由于最后可能会出现 `Unclosed Mark`，所以我们前面输出的时候应该将答案存下来，最后判断有没有收尾，有的话再将所有输出。

读入可以一直 `getchar()`，直到 `\0`（还是 EOF，不大记得了 qwq）

但这种写法调试的时候，必须使用文件输入输出，请注意。

存栈的时候，可以使用数字来标识是哪个转义。

关于数组大小，没有定论，反正我开了 $5\times10^6$ 的长度，然后栈开了 $1000$，可过。

遇到结束的时候，可以直接跳过 `/`，再进行匹配。

前 4 个可以合并一下，使代码简短（虽然感觉我的代码最长

## 3. Code

毕竟是大模拟，有时带字符串的，很难调，故放上整个代码，供大家参考。

有没有考虑到的地方，欢迎在评论区指出。

码风略丑，请见谅。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const char muban[8][7] = {{"\0"}, {"h1"}, {"h2"}, {"i"}, {"b"}, {"url"}, {"img"}, {"quote"}};
const char trans_to[6][7] = {{"\0"}, {"#"}, {"##"}, "*", "__"};
char ch, a[5000000], ans[5000000], k[10000][1000];
int stk[1000], top, n, tot;
//h1 -> 1 -> # || h2 -> 2 -> ## || i -> 3 -> * || b -> 4 -> __ || url -> 5 -> []() || img -> 6 -> ![]()
//quote -> 7 -> > 

bool cmp(int pos, int id)
{
	int sz = strlen(muban[id]);
	for (int i = 0; i < sz; ++ i)
		if (a[pos + i] != muban[id][i]) return false;
	if (a[pos + sz] != ']' && a[pos + sz] != '=') return false;
	return true;
}

int find_muban(int pos)
{
	for (int i = 1; i <= 7; ++ i)
		if (cmp(pos, i)) return i;
	return -1;
}

void materr()
{
	puts("Match Error");
	exit(0);
}

void uncldmk()
{
	printf("Unclosed ");
	puts("Mark");
	exit(0);
}

void output(string s)
{
	for (int i = 0; i < (int)s.size() && s[i]; ++ i)
		ans[++ tot] = s[i];
}

void Debug_Failed()
{
	puts("Failed");
	exit(0);
}

int main()
{
	// freopen("P2395_ex.in", "r", stdin);
	// freopen("P2395_ex.out", "w", stdout);
	while ((ch = getchar()) != -1 && ch != 0) a[++ n] = ch;

	for (int i = 1; i <= n;)
	{
		if (a[i] == '[')
		{
			bool flag = 0;
			if (a[i + 1] == '/') flag = 1, i ++;
			int t = find_muban(i + 1);
			if (t <= 0) Debug_Failed();
			// cout << "match : " << t << endl;
			if (flag)
			{
				if (t != stk[top]) materr();
				if (t <= 4)
				{
					i += strlen(muban[t]) + 2;
					if (t <= 2) output(" ");
					output(trans_to[t]);
				}
				if (t == 5)
				{
					output("](");
					output(k[top] + 1);
					output(")");
					i += 5;
				}
				if (t == 6)
				{
					output("](");
					output(k[top] + 1);
					output(")");
					i += 5;
				}
				top --;
				continue;
			}
			if (t <= 4)
			{
				output(trans_to[t]);
				if (t <= 2) output(" ");
				stk[++ top] = t;
				i += strlen(muban[t]) + 2;
				continue;
			}
			if (t == 5)
			{
				i += 5;
				int tmp = 0;
				output("[");
				stk[++ top] = 5;
				while (a[i] != ']') k[top][++ tmp] = a[i ++];
				i ++;
			}
			if (t == 6)
			{
				i += 5;
				int tmp = 0;
				output("![");
				stk[++ top] = 6;
				while (a[i] != ']') k[top][++ tmp] = a[i ++];
				i ++;
			}
			if (t == 7)
			{
				i += 7;
				if (a[i] == '\n') i ++;
				if (i != 8 && a[i - 8] != '\n') output("\n");
				output("> ");
				while ((!cmp(i + 2, 7) || a[i + 1] != '/'))
				{
					if (a[i] == '\n' && cmp(i + 3, 7) && a[i + 2] == '/')
					{
						i ++;
						break;
					}
					if (a[i] == '\n') output("\n> ");
					else ans[++ tot] = a[i];
					i ++;
				}
				i += 8;
				output("\n");
				if (a[i] == '\n') i ++;
			}
		}
		else
		{
			string t = " ";
			t[0] = a[i ++];//将字符转化为字符串
			output(t);
		}
	}
	if (top) uncldmk();
	cout << ans + 1;
	return 0;
}
```

---

## 作者：Leaves_xw (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P2395)、[题解传送门](https://www.luogu.com.cn/problem/solution/P2395)。

大模拟好啊！

**大意：**

将所需转换的 BBCode 转化成 Markdown。

**思路：**

所需转换的大约就这几个：

![](https://cdn.luogu.com.cn/upload/pic/1493.png)

可以看到，需要转化的东西并不是很多，也就是说，几个判断就能搞定。

但是真的是这样吗？

题目已经说了：

```
为保证评测顺利不被误判，请注意下列要求：

尊重原输入输出的换行，不自行添删。

对于第一条的例外是， 遇到[quote]标签不在新的一行时，Markdown中请另起一行。另外[quote]标签中的代码段头尾空行请去除，不会出现空白的quote。

请注意上表中的空格。

对于不合法的BBCode输入，你的程序必须报错：对于匹配错误的标签输出Match Error，对于未闭合的标签输出Unclosed Mark，请参考样例。两种情况同时出现的时候（即同时有匹配错误和未闭合的标签时），按照匹配错误处理，输出Match Error。由于quote标签的特殊性，为保证不出现歧义，数据保证quote标签不会出现错误。(对于出现如[i][h1]Text[/i]这样的情况，按照Match Error处理，对于[i][h1]Text[/h1]这样的情况，按照Unclosed Mark处理)

由于洛谷限制，请大家在输出Unclosed Mark的时候在close中间切开分为两段字符串输出，否则会被吞记录。

保证以下三种字符不出现在除quote标签包裹的段落中的文字中：[,],/,*,_,#,>，但地址中可能会出现/字符。

保证输入不会出现标签不完整的情况，例如[h1]Text[/h

对于曾经在其他地方使用过Markdown与BBCode的同学：题中的格式不是严格的BBCode与Markdown格式，请勿被经验迷惑。
```

也就是说，我们需要一个栈来储存，每次形如 [P1499 后缀表达式](https://www.luogu.com.cn/problem/P1449) 一样，如果遇到 BBCode，则将代码压入栈，并将所表示的 $flag$ 标记为 `true`，在下一次遇到第二个所需要转换的表示相同意义的 BBCode 时，将两个 BBCode 转化为Markdown，并且将 $flag$ 标记为 `false`即可。

**但是注意，如果最后的时候 $flag$ 仍为 `true`，则需要输出 `Match Error`，对于 `[i][h1]Text[/h1]` 这样的情况，需要输出 `Unclosed Mark`。**

`url` 和 `img` 需要特殊处理一下。

END。

---

## 作者：CYMario (赞：2)

我看这题一直没有题解，那我来写一个吧...

头一次写题解，可能不是很擅长写的十分清楚，还请谅解...

总的来说，这道题是纯粹的字符串处理的大模拟，而且不适合离线处理（因为所有的代码块随时处理完之后会带来一系列的变化,这也是我第一版提交又WA又TLE，只有60分的原因。）

所以使用getchar()边读入边处理，直到出现了EOF为止。

首先关于是否嵌套有误，很容易可以拿栈来进行判断，如果在整体处理代码块的时候，读到了文件的末尾，或者出现了需要出栈但是栈空了的状态，则非法

然后剩下的就直接根据题目要求进行处理即可，不需要递归什么的

但是这个代码在读入代码块这里忘记判断如果读到结束了应该怎么进行判断，这里可以改进一下
```cpp
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<stack>
#include<vector>
#define endline '\n'
#define debugQuote 0
#define debugGetchar 0
using namespace std;
string output;
string tag;
stack<string>parseStack;
stack<string>lastURL;
string quoteBuf;
bool isclose;
char c;
char lastC;
string processTag(string tag) {
	if (tag == "h1")return "#";
	if (tag == "h2")return "##";
	if (tag == "i")return "*";
	if (tag == "b")return "__";
	if (tag == "url")return "[";
	if (tag == "img")return "![";
	return "";
}
bool quoteBufNotOver() {
	string last = quoteBuf.substr(quoteBuf.size() - 8, 8);
	return last != "[/quote]";
}
string handleQuoteSpace(string str) {
	int pos = str.find_first_not_of(" \n\r\t");
	if (pos == str.npos)return str;
	int pos2 = str.find_last_not_of(" \n\r\t");
	if (pos2 != str.npos)return str.substr(pos, pos2 - pos + 1);
	else return str.substr(pos);
}
//重写:直接跳过对这中间指令的判断,这也是在线处理的好处
void addQuote() {
	if (isclose && parseStack.empty()) { puts("Match Error"); exit(0); }
	if (lastC != endline) output += endline;//quote默认上一行非空就要重启一行
	quoteBuf = "";
	while (quoteBuf.length() < 8 || quoteBufNotOver()) {
		char t = getchar();
		if (t == EOF) { printf("Unclo"), puts("sed Mark"); exit(0); }
		quoteBuf.push_back(t);
	}
	quoteBuf = "> " + handleQuoteSpace(quoteBuf.substr(0, quoteBuf.length() - 8));
	for(int pos = 0; pos < quoteBuf.size(); ++pos)
		if(quoteBuf[pos] == '\n')quoteBuf.insert(pos + 1, "> ");
	output += quoteBuf + endline;
}
void addURLorIMG() {
	//img和url就差一个叹号
	if (isclose) {
		if (parseStack.empty() || tag != parseStack.top()) { puts("Match Error"); exit(0); }
		parseStack.pop();
		output += "](" + lastURL.top() + ")";
		lastURL.pop();
	}
	else {
		lastURL.push(tag.substr(4));
		parseStack.push(tag.substr(0, 3));
		output += processTag(tag.substr(0, 3));
	}
}
void addNormal() {
	if (isclose) {
		if (parseStack.empty() || tag != parseStack.top()) { puts("Match Error"); exit(0); }
		parseStack.pop();
		if (tag[0] == 'h')output += " ";
		output += processTag(tag);
	}
	else {
		parseStack.push(tag);
		output += processTag(tag);
		if (tag[0] == 'h')output += " ";
	}
}
int main() {
	//FILE* in;
	//in = freopen("P2395in.txt", "r", stdin);
	lastC = endline;
	while ((c = getchar()) != EOF) {
		if (c == '[') {
			tag = "";
			int i = 0;
			isclose = false;
			char t;
			while ((t = getchar()) != ']') {
				if (t == '/' && i == 0)isclose = true;
				else tag.push_back(t), ++i;
			}
			if (tag == "quote")addQuote();
			else if (tag[0] == 'u' || (tag[0] == 'i' && tag.length() > 1))addURLorIMG();
			else addNormal();
		}
		else output += c;//这样不仅解决了普通tag的问题,还解决了没有在任何tag中的文字的极端情况
		lastC = c;
	}
	if (!parseStack.empty()) { printf("Unclo"), puts("sed Mark"); exit(0); }
	else puts(output.c_str());
}
```


---

## 作者：gtafics (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P2395)

## 题目大意：

给出一段 BBCode 格式的待转换字符串，要求将其转换为 Markdown 格式。

![BBCode 和 Markdown 转换表](https://cdn.luogu.com.cn/upload/pic/1493.png "BBCode 和 Markdown 转换表")

## 解题思路：

对于输入中的非标签内容**直接输出**即可；对于一二级标题、斜体、粗体的标签，我们可以**直接将其替换** Markdown 格式的；而对于链接和图片，可以将链接**保存**下来，等到结束标签时在将文字描述一起按格式输出；代码段可以通过逐行输入，并**忽略除 `[/quote]` 以外的标签**。

几个需要注意的点：

标签中可能有嵌套，可以**用栈**来维护；链接和图片也有可能嵌套，所以需要另一个栈来维护链接。也可以使用 `stack` 配合 `pair` 来同时维护标签和链接。

遇到 `Unclosed Mark` （可以忽略题目中让我们分两段输出该错误的信息）和 `Match Error` 的错误时，你的程序应当**只输出**两个错误**之一**。可以通过判断栈顶和当前结束标签来判断是否出现 `Match Error`；通过在格式转换部分全部运行结束之后判断栈是否为空来判断是否出现 `Unclosed Mark`。注意可能出现**栈为空时**读入一个结束标签的情况，这种情况属于 `Match Error`。

按照原输入的换行进项输出，**除了 `[quote]` 标签**的首尾空行。这些空行**不应**在你的输出中出现。对于 `[quote]` 标签不在单独一行的情况，你的程序应该让代码段**独立成行**。注意，在 `[/quote]` 标签后应该**加上一个换行**。如：

输入：
```plain
[quote]123[/quote]456
```
输出
```plain
> 123
456
```

最后附上[代码](https://www.luogu.com.cn/paste/jm6mlhtc)。

---

## 作者：AFOatic (赞：1)

## 思路

维护一个存标签的栈，依次读入每行，当读取到`[`时
1. 正常状态
读入完整标签，获取标签名（对`url=xxx`和`img=xxx`特判）
	先考虑语法：

    1. 如果是开始标签，将标签名压入栈
    2. 如果是结束标签，与栈顶标签名不同则匹配失败，`Match Error`

	语法无误后：

    1. 对于`h1`类标签名，直接替换
    2. 对于`url`和`img`，用一个单独的栈存链接，在结束标签出输出链接
    3. 对于`quote`进入`quote`状态
2. `quote`状态
    继续向后读，如果读到`[/quote]`就结束，否则正常输出

如果遍历完输入后，标签栈不是空的，则为`Unclosed Mark`

将输出先存在一个队列中，如果语法没有问题，最后依次输出并忽略空行（即`"> "`和`""`）
## 坑点

1. 文末所说`由于洛谷限制，请大家在输出Unclosed Mark的时候在close中间切开分为两段字符串输出，否则会被吞记录。`是假的，正常输出才能AC
2. `quote`中可能有`[`
3. `url`,`img`中可能有`/`

## 代码
见注释
```cpp
#include<bits/stdc++.h>
using namespace std;
queue<string>about_to_put;//只需要顺序遍历即可
stack<string>tags;//存标签
stack<string>ttemp;//存url/img，标签能嵌套
const string endquote="/quote]";
string tagname(string s){
    if(s[0]=='u')return "url";
    else if(s.length()>1&&s[0]=='i')return "img";
    return s;
}//获取正确的标签
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);//关闭流同步
    string s;
    bool quote=false;//是否正在quote
    while(getline(cin,s)){//依次读入每行
        string put;
        if(quote)put="> ";//quote前的`> `
        int t=s.length();
        for(int i=0;i<t;++i){//遍历字符串
            char c=s[i];
            if(c=='['){
                int j;
                if(quote){
                    //会有各种奇怪的坑：[quote][[[[[[[/quote]
                    string tttemp;
                    bool flag=false;
                    for(int k=1;k<=7;k++){
                        if(i+k==t){
                            i=t;
                            put+=("["+tttemp);
                            about_to_put.push(put);
                            put="";
                            flag=true;
                            break;//跳出大循环
                        }
                        tttemp+=s[i+k];
                    }
                    if(flag)break;
                    if(tttemp==endquote){
                        quote=false;
                        about_to_put.push(put);
                        put="";
                        tags.pop();//栈弹出 quote
                        i+=7;
                    }
                    else{
                        put+="[";
                    }
                    continue;
                }
                string temp;
                bool isclose=false;
                if(s[i+1]=='/')isclose=true;
                else temp+=s[i+1];//需要提前判断，因为url/img= 后面的东西可能会包含 /
                ++i;
                for(j=i+1;j<t;++j){
                    c=s[j];
                    ++i;
                    if(c==']'){
                        break;
                    }
                    //if(c=='/')isclose=true;
                    temp+=c;
                }
                /*
                if(quote&&(!isclose||temp!="quote")){
                    put+=("["+temp+"]");
                    continue;
                    //如果正在quote且不是关闭标签，直接导入
                }
                */
                if(isclose){
                    if(tags.empty()||tags.top()!=tagname(temp)){//匹配错误
                        //注意：||是短路运算符，把empty放前面，否则会RE！！！
                        cout<<"Match Error";
                        return 0;
                    }
                    tags.pop();
                }
                else tags.push(tagname(temp));
                if(temp=="h1"){
                    if(isclose)put+=" #";
                    else put+="# ";
                }
                else if(temp=="h2"){
                    if(isclose)put+=" ##";
                    else put+="## ";
                }
                else if(temp=="i")put+="*";
                else if(temp=="b")put+="__";
                else if(temp[0]=='u'){//url
                    if(isclose){
                        put+=("]("+ttemp.top()+")");
                        ttemp.pop();
                    }
                    else{
                        put+="[";
                        string tttemp=temp.substr(4);//截取 = 后部分
                        ttemp.push(tttemp);
                    }// [] 中的部分可以直接导入 about_to_put
                }
                else if(temp[0]=='i'){//img
                    if(isclose){
                        put+=("]("+ttemp.top()+")");
                        ttemp.pop();
                    }
                    else{
                        put+="![";
                        string tttemp=temp.substr(4);
                        ttemp.push(tttemp);
                    }
                }
                else{//quote
                    about_to_put.push(put);//换行
                    /*if(isclose){
                        quote=false;
                        put="";
                    }
                    else*/{
                        quote=true;
                        put="> ";//[quote]things...[/quote]
                    }
                }
            }
            else put+=c;
        }
        about_to_put.push(put);
    }
    if(!tags.empty())cout<<"Unclosed Mark";//仍有标签未关闭
    else{
        while(!about_to_put.empty()){
            string temp=about_to_put.front();
            about_to_put.pop();
            if(temp=="> "||temp=="")continue;//空行
            cout<<temp<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：Untitled10032 (赞：0)

这是一篇使用 C 语言的题解。

## 简要题意

- 将（题目中给出的）BBCode 风格的标签转换为 Markdown 格式，并实现一定的语法检测功能。

## 思路

~~一道中模拟题。可比 P3695 什么的阳间多了。~~

他要什么你就怎么写就可以了。

### 首先是读入。

- __我使用 `fread` 函数将所有输入一次性读入__。

- 注意读入数据大小。字符数组开到 $6 \times 10^5$ 是够的（小一点我也没试过）。

- 如果你使用了 `fread` 且从控制台输入，则可以换行输入 ctrl + z 作为结束标志。

### 读入字符串的处理：

- 从前往后的顺序遍历输入字符串。

- 由题目可知，所有 BBCode 标签都被中括号包裹，仅当一个字符为 `[` 时，以这个字符为开头的某个子串需要进行转换。所以每次遇到 `[` 时判断标签类型。

- 我使用了函数 `judgeLabel` 判断标签类型。（不要忘记先判断这个标签有没有 `/`。）

```c
//给标签设置枚举类
typedef enum {
    H1, H2, B, I, URL, IMG, QUOTE
} Label;

//... ...

//判断标签。
//static inline 是优化用的
static inline Label judgeLabel() {
    if (*cursor == 'h') {
        cursor++;
        if (*cursor == '1') {
            cursor += 2;    //跳过后括号
            return H1;
        } else {
            cursor += 2;
            return H2;
        }
    } else if (*cursor == 'b') {
        cursor += 2;
        return B;
    } else if (*cursor == 'i') {
        if (*(cursor + 1) == 'm') {
            cursor += 4;
            return IMG;
        } else {
            cursor += 2;
            return I;
        }
    } else if (*cursor == 'u') {
        cursor += 4;
        return URL;
    }
    cursor += 6;
    return QUOTE;
}
```

- 使用一个栈存储暂未闭合的标签，用来检查语法错误。

- 在判断完标签类型后将对应标签压入 / 弹出标签栈中，并检查语法错误。

```c
bool is_end = false;	//存储这个标签是否是结束标志（是否有斜杠）
if (*cursor == '/') {
    cursor++;
    is_end = true;
}
Label now_label = judgeLabel();
if (!is_end) {
    labPush(now_label);	//labPush、labPop 等为栈操作。函数就一行。具体见源代码。
} else {
    if (labEmpty()) {
        puts("Unclosed Mark");
        return 0;
    }
    if (labTop() != now_label) {
        puts("Match Error");
        return 0;
    }
    labPop();
}
```

### 之后处理各个标签。

- __注意转换后的结果不能直接输出，万一后面有个得报错的就寄了。所以我开了一个数组作为输出缓冲区。 `ansAppend` 函数的功能是在输出缓冲区的末尾追加一个字符。__

- 语法错误之前已经判断过了，所以这里不用（也不能）重复判断。

- `h1`、`h2`、`b`、`i` 标签直接换成对应的字符就可以了。__注意空格位置。__

- `url`、`img` 标签只差了一个感叹号，所以可以一起处理。

- `url`、`img` 标签中两段文本 BBCode 和 Markdown 顺序是反的（BBCode：`[url=链接文本]描述文本[/url]`）。因为描述文本中可能还会有其它标签需要转换，不能也一股脑读入，所以读到 `[url=` 时，先将链接文本读入，并放入一个 __字符串栈__ 中。

- 等读到 `[/url]` 时再从字符串栈中取栈顶并弹出，转换为相应 Markdown。（以上两条 `img` 同理）。

- 最后是 `quote`。这个标签比较烦的就是开始和结束的换行问题。`[quote]` 和 `[/quote]` 两个标签的前后四个位置都可能有换行，但是我们只需要开始一个和结束一个的换行，且结束的换行后不应加上 `> `。

- 遇到 `quote` 时，将其包裹的字符全部读入，直到遇见完整的 `[/quote]`。其中如遇换行则加上 `> `，并特殊判断一下开始和结束的换行。

```c
//... ...

else if (now_label == QUOTE) {
    if (*cursor == '\n' && (*(ans_cursor - 1) == '\n' || ans_cursor == ans))
        cursor++;   //防止多换行：
                    //如果输出缓冲区的最后一个字符是换行而且紧接着[quote]光标读到的
                    //也是一个换行，那么就让光标后移，跳过换行。
    if (*(cursor - 1) != '\n') {  //判断 [quote] 前面是否没有换行
        //解决无换行quote第一行没有> 的问题
        if (*(ans_cursor - 1) != '\n')
            ansAppend('\n');    //如果 [quote] 两边都没有换行就加上一个换行。
        ansAppend('>');
        ansAppend(' ');
    }
    do {
        if (*cursor == '\n') {
            ansAppend('\n');    //解决最后一行换行多出> 的问题。
            cursor++;   //如果这个字符是换行，先把换行输出，之后去看看后面紧接着的是不是 [/quote]
                        //如果是就会在后面判断时 break 掉，不会输出 > 
        }
        if (*cursor == '[' && *(cursor + 1) == '/' && *(cursor + 2) == 'q' &&
            *(cursor + 3) == 'u' && *(cursor + 4) == 'o' && *(cursor + 5) == 't' &&
            *(cursor + 6) == 'e' && *(cursor + 7) == ']')
            break;
        if (*(cursor - 1) == '\n') {
            ansAppend('>');
            ansAppend(' ');
        }
        ansAppend(*cursor);
        
    } while (*(cursor++) != '\0');
    if (*cursor == '\0') {
        //整个输入读完了之后都没找到 [/quote]
        puts("Unclosed Mark");
        return 0;
    }
    cursor += 8;    //跳过标签
    if (*cursor == '\n' && *(ans_cursor - 1) == '\n')
        cursor++;   //防止多换行
    labPop();   //弹出栈中的quote
}
```

## 最后一点

~~海内存知己，天涯若比邻。请稍等...~~

- 不要忘了判断标签栈是否空了，如果没空记得报错。

- 将输出缓冲区中的内容全部输出。

- 等待 AC。

~~祝你们成功（滑稽~~

## [点击此处查看源代码](https://www.luogu.com.cn/paste/3q01mvak)


---

