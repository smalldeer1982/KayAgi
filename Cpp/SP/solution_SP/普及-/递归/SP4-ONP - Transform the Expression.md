# ONP - Transform the Expression

## 题目描述

请你将 $n$ 个中缀表达式转换为后缀表达式。

## 说明/提示

对于 $100\%$ 的数据，$n \le 100$ , 表达式长度 $\le 400$ 。

Translated by @[稀神探女](/user/85216)

## 样例 #1

### 输入

```
3
(a+(b*c))
((a+b)*(z+x))
((a+t)*((b+(a+c))^(c+d)))```

### 输出

```
abc*+
ab+zx+*
at+bac++cd+^*```

# 题解

## 作者：Loner_Knowledge (赞：25)

这是一道模拟题
---

题意是中缀表达式转后缀表达式，只需要维护一个存储运算符的栈即可。由于题意保证没有形似`a*b*c`的多参数，所以不需要将`(`入栈作为边界标记，出栈时不需要出栈多个运算符并特判`(`。

```cpp
#include<cstdio>
char s[402],sta[402];
int main() {
	int t;
	for(scanf("%d",&t);t;putchar('\n'),--t) {
		scanf("%s",s);
		for(char *i=s,*head=sta;*i;++i) {	//这里使用了指针
			if(*i>='a'&&*i<='z')	//如果是参数则输出
				putchar(*i);
			else if(*i==')')		//如果是右括号)则输出栈顶元素并将其弹出栈
				putchar(*--head);
			else if(*i!='(')		//如果是运算符（左括号(不是）则入栈
				*head++=*i;
		}
	}
	return 0;
}
```

---


---

## 作者：Diamiko (赞：17)

## 模拟

-----------

我看了看现有的题解，大多是“因为题目……，所以我们可以……”。

固然这种面向题目的编程方式是很适合 OIer 的，但掌握知识就掌握透彻，为什么我们不把完整的转换学会呢？况且不知道什么时候就会遇上没有这些限制的题目呢？

------------------

我们来讲一下完整的中缀表达式转换后缀表达式的过程。

中缀表达式转换后缀表达式最常用的方法就是用栈模拟。

### 具体转换方式:
1.从左到右进行遍历

2.运算数，直接输出

3.左括号，直接压入堆栈，(括号是最高优先级，无需比较)(入栈后优先级降到最低，确保其他符号正常入栈)

4.右括号，(意味着括号已结束)不断弹出栈顶运算符并输出直到遇到左括号(弹出但不输出)

5.运算符，将该运算符与栈顶运算符进行比较 

如果优先级高于栈顶运算符则压入堆栈(该部分运算还不能进行)，

如果优先级低于等于栈顶运算符则将栈顶运算符弹出并输出，然后比较新的栈顶运算符.

(低于弹出意味着前面部分可以运算，先输出的一定是高优先级运算符，等于弹出是因为同等优先级，从左到右运算)

直到优先级大于栈顶运算符或者栈空，再将该运算符入栈.

6.如果对象处理完毕，则按顺序弹出并输出栈中所有运算符.

--------------------------

### 举个栗子

![](https://img-blog.csdnimg.cn/20190530133043323.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDI2MDc3OQ==,size_16,color_FFFFFF,t_70)

看懂了吗？看不懂再来一个。

![](https://img-blog.csdnimg.cn/20190530133057843.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDI2MDc3OQ==,size_16,color_FFFFFF,t_70)

（图片来自[CSDN博客](https://blog.csdn.net/weixin_44260779/article/details/90695746)）

---------------------
### 代码实现

(详见注释)

```cpp
#include<iostream>  
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<stack>
using namespace std;
int n;
string s;
bool check(char t,char x)
{
	//check函数返回true代表可入栈，false代表不可入栈
	//t表示栈顶元素，x表示待入栈元素
	if(x=='(')return 1;
	//左括号最高等级
	if(x==')')return 0;
	//右括号不能入栈
	if(t=='(')return 1;
	//左括号入栈后降级到最低，以便其他符号入栈
	if(t=='^')return 0;
	if(x=='^')return 1;
	//除括号外乘方是最高等级
	if(t=='*'||t=='/')
		return 0;
	//除去前面那些只剩加减乘除了，乘除当然最高
	if(t=='+'||t=='-')
		return !(x=='+'||x=='-');
	//如果栈顶是加或减（最低），待入栈元素也是的话，就不能入栈
	//否则一定比栈顶大，就可以入栈
}
int main()
{
	cin>>n;
	while(n--)
	{
		stack<char>sym;
		cin>>s;
		for(char c:s)
		{
			if(isalpha(c))
			{
				//如果是字母，在这题里就是运算数
				cout<<c;
				continue;
				//直接输出就行了
			}
			if(sym.empty())
			{
				sym.push(c);
				continue;
				//如果栈空的话就不用考虑剩下的部分了
				//要不然会RE的，毕竟栈里本来就没东西
			}
			while(!check(sym.top(),c))
			{
				//只要不能入栈，就一直弹出栈顶
				if(sym.top()=='('&&c==')')
				{
					sym.pop();
					break;
					//如果栈顶是左括号，待入栈是右括号
					//就要特殊处理，因为后缀表达式中没有括号
				}
				cout<<sym.top();
				//输出栈顶
				sym.pop();
				//弹出
				if(sym.empty())break;
				//如果已经空了，就结束循环，因为栈顶已没有元素了
			}
			if(c!=')')
				sym.push(c);
			//右括号不能入栈
		}
		for( ;sym.size();sym.pop())
			cout<<sym.top();
		cout<<endl;
		//输出栈里剩余的符号
	}
    return 0;  
}
```

---

## 作者：RagnaLP (赞：4)

就是一道模拟题

~~看到后缀表达式就很头大，这道题正好解了我的头疼~~

关于**后缀表达式**：

也叫逆波兰表达式，指的是不包含括号，运算符放在两个运算对象的后面，所有的计算按运算符出现的顺序，严格从左向右进行。（就是打死不用括号）

主要算法：栈（stack）,大部分操作和queue一样的。

**需要注意的地方**

1.数字或者是表示一个数的字母在后缀表达式中都是直接输出

2.注意前后的括号的匹配

代码：（有点乱）
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<stack>
#include<cmath>
using namespace std;
stack<char> s;//栈用于存放操作符（+、-、*、/和括号）
int n;//n为表达式的个数
void Init() {
	scanf("%d",&n);
	while(n--) {
		char now,c=getchar();//now用于输出括号内的符号，见下面
		while(c!='(')c=getchar();//排除其他字符影响
		s.push(c);//将第一个‘（’入栈；
		while(c!='\n') {
			c=getchar();
			if(c>='a'&&c<='z') {//如果是字母就直接输出，见注意1
				printf("%c",c);
			} else if(c!=')') {
				s.push(c);
			} else {//如果是‘）’，则需要把一直到上一个‘（’中间的所有符号输出
				now=s.top();
				s.pop();
				while(now!='(') {//直到取出上一个‘）’
					printf("%c",now);
					now=s.top();
					s.pop();
				}
			}
		}
		printf("\n");
	}
}
int main() {
	Init();
	return 0;
}
```

[还有什么不懂的话可以看看这里](http://blog.csdn.net/huangchijun11/article/details/60963444)

---

## 作者：BorisDimitri (赞：3)

# 中缀表达式转后缀表达式：

假定有**中缀表达式**:  $1 + (( 2 + 3)* 4 ) – 5$  ，将它转化为后缀表达式。

## 方法一：利用表达式树

首先将**中缀表达式**转换为表达式**树**，然后后序遍历这棵树，所得结果就是后**缀表达式**。

**将中缀表达式转化为表达式树方法：**

>表达式树的叶节点是**操作数**，而其他的节点为**操作符**。
>
>根节点为**优先级最低**且**靠右**的操作符（如上述表达式优先级最低的是$-$ 和$+$，但$ + $更靠右，所以根为$+$），其中不包括括号。

如上述中缀表达式转换后的表达式树如下：

![0uTBMd.jpg](https://s1.ax1x.com/2020/09/30/0uTBMd.jpg)



经过**后序遍历**表达式树后得到的答案为：
$ 12 3 + 4 * + 5 – $

## 方法二：利用辅助栈

>1.从左到右遍历中缀表达式的每个操作数和操作符。
>
>2.当读到**操作数**时，立即把它**输出**，即成为后缀表达式的一部分。
>
>3.若读到**操作符**，~~判断**该符号**与**栈顶符号**的**优先级**~~，若该符号优先级**高于栈顶元素**，则将该操作符**入栈**。
>
>4.**否则**就一次把栈中运算符**弹出**并**加到后缀表达式尾端**，直到遇到**优先级低于该操作符的栈元素**，然后把该操作符**压入栈中**。
>
>5.如果**遇到**”(”，直接压入栈中，如果遇到一个”)”，那么就将栈顶元素**弹出**并加到后缀表达式尾端，但**不输出左右括号**。
>
>6.最后，如果读**到**中缀表达式的**尾端**，将**栈元素依次完全弹出并加到后缀表达式尾端**。

**注释：这里给出的中序遍历一定是符合规则的中序遍历，所以同一个括号内，优先的操作符一定先出现，所以可以不需要判断优先级，直接碰到那个操作符就入栈。**

仍然以上面的表达式为例，其转换过程如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/nk7l9c9m.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/qwc43s1g.png) 


![](https://cdn.luogu.com.cn/upload/image_hosting/6ejt2g88.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/g4yf5ktk.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/8yeixpnv.png) 

![](https://cdn.luogu.com.cn/upload/image_hosting/k5yvspjz.png)


利用辅助栈后缀表达式与用表达式树的结果一样，都为：$1 2 3 + 4 * + 5 –$

---
### AC Code（栈辅助做法）
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;//个数

void change(string mid_order)//中缀表达式 转换为 后缀表达式
{
    stack<char> oper; //操作符栈

    int len=mid_order.length();//中序遍历的长度
    for(int i=0;i<len;i++)
    {
        if(mid_order[i]>='a' && mid_order[i]<='z') putchar(mid_order[i]);//如果是操作数,直接输出
        else if(mid_order[i] == ')') 
        {
            putchar(oper.top());//输出操作符
            oper.pop();//栈顶出栈
        }
        else if(mid_order[i] != '(') oper.push(mid_order[i]);//如果是一个操作符就入栈
    }

    while(!oper.empty())//输出剩下的字符 
    {
        putchar(oper.top());
        oper.pop();
    }

    return ;
}

int main()
{
    scanf("%d",&n);

    while(n--)
    {
        string mid_order;//中序遍历

        cin>>mid_order;//输入中序遍历

        change(mid_order);

        puts("");
    }

    return 0;
}
```

---

## 作者：Terraria (赞：2)

### 题目大意：给出 $n$ 个中缀表达式，求其后缀表达式。

## $Part$ $1$.什么是后缀表达式？

假设一个表达式为 $E$，那么：

- 如果 $E$ 本身是一个常量或变量，那么 $E$ 的后缀表达式是它本身。

- 如果 $E$ 是 $E_1$ $op$ $E_2$ 形式的表达式，这里 $op$ 是任何二元操作符，则 $E$ 的后缀式为 $E_1$ $E_2$ $op$，这里 $E_1$ 和 $E_2$ 分别为 $E_1$ 和 $E_2$ 的后缀式。

例如，$(a+b)$ 的后缀表达式就是 $ab+$；

又例如，$((a+b)\times(x+y))$ 的后缀表达式为 $ab+xy+ \times$。

- 如果 $E$ 是 $(E1)$ 形式的表达式，则 $E1$ 的后缀式就是 $E$ 的后缀式。

~~以上内容源于百度百科。~~

## $Part$ $2$.怎么处理后缀表达式？

一般我们使用栈来操作。

~~栈应该都会吧。~~

几个基本操作：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
stack<int> s;//声明一个名为s的栈
int main(){
    cin>>n;
    for(int i=n;i>=1;i--) s.push(i);//每次插入i到栈顶
    //若n为5，则当前栈内从顶到底的元素分别为1，2，3，4，5
    cout<<s.size()<<endl;//访问栈内的元素个数 
    cout<<s.top()<<" ";//输出栈顶元素，即为1
    s.pop();//弹出栈顶元素 
    while(!s.empty()){//判断s是否为空
        cout<<s.top()<<" ";//不断输出栈顶元素
        s.pop();//弹出栈顶元素
    }
    //以上这个程序在输入为5的情况下输出为：
    /*
    5
    1 2 3 4 5 
    */
}
```
明白了吧~

## $Part$ $3$.怎么搞定这一题？

主要分为以下几步：

- 遇到左括号：直接跳过；

- 遇到了变量 $a,b,c,...,x,y,z$ 直接输出；

- 遇到了右括号：由于一个表达式可能会有优先级之分，这时候就需要我们的栈出场了！当遇到一个右括号时，说明当前这段括号里的表达式的常量与变量已经处理完毕，唯独这段表达式的符号还没有输出。因此直接访问栈顶的符号并输出就好了！同时记住要弹出栈顶！

- 如果以上都不是，那么就说明当前为一个符号，直接入栈。

## $Part$ $4$.$Code$:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin>>n;
	while(n--){
		string s;
		stack<char> sta;
		cin>>s;
		for(int i=0;i<s.size();i++){
			if(s[i]=='(') continue;
			if(s[i]>='a'&&s[i]<='z'){
				cout<<s[i];
				continue;
			}
			if(s[i]==')'){
				cout<<sta.top();
				sta.pop();
			}
			else sta.push(s[i]);
		}
		putchar('\n');
	}
}
```
完结撒花~

---

## 作者：潘捷 (赞：2)

# 禁止抄袭，但思路可以借鉴
## **首先我认为本题的考点为递归而不是单纯的模拟**
然后思路为递归到最小括号，然后依次解决。

详见代码

代码如下：（自认为很详细）
```cpp
#include<bits/stdc++.h>//头文件 
using namespace std;
int p=0,n;//变量，不做解释 
string s;//全局变量，不做解释
string dg()
{ 
	string s1,s2,s3;//s1表示第一个完整的括号例如((a+b)*(z+x))中的a，b，s2 表示该括号之外的数字（z,x）因为题目讲解不可能出现a*b*c情况所以可以这么写，s3为符号。 
	int f=0;//判断是不是第一个括号 
	while(p<s.size())//从字符0~结尾循环 
	{
		if(f==0&&s[p]=='(')//情况1 ，可以根据上述的实际意义理解，不做过多解释 
		{
			p++;f=1;s1=dg();//p指针++，f标记为1，递归直到最小括号 
		}
		else if(f==1&&s[p]=='(')//第二个括号出现 
		{
			p++;s2=dg(); 
		}
		else if(f==0&&s[p]>='a'&&s[p]<='z')//情况3 
		{
			f=1;s1=s[p];//已经出现括号 可以整理数字 
		}
		else if(f==1&&s[p]>='a'&&s[p]<='z')
		{
			s2=s[p];//第二个括号的数字处理 
		}
		else if(s[p]==')') break;//情况4，如果是）就结束 
		else s3=s[p];//依次存入字符 
		p++;
	}
	return (s1+s2+s3);//后缀表达式的输出方式 
}
int main()//主程序过于简单不做过多解释 
{
	cin>>n;
	for(int i=1;i<=n;i++)//循环 
	{
		p=0;
		cin>>s;
		cout<<dg()<<endl;//依次输出 
	}
}
```

---

## 作者：joyoi (赞：1)

## 模拟题...

此题考的是由中缀表达式转换为后缀表达式，且保证括号一定匹配

方法：建立一个 $stack$

举个栗子:  ![](https://ss1.bdstatic.com/70cFuXSh_Q1YnxGkpoWK1HF6hhy/it/u=901333867,1403435926&fm=26&gp=0.jpg)
$(a+(b*c))$

从 $($ 开始

如果碰到的是字母，则直接输出

如果碰到的是运算符，则入$stack$

如果碰到的是 $)$，则输出 $stack$ 顶的运算符，即最近记录下的那个运算符，然后将它删除

如果碰到的是 $($，就不管他

```cpp
1.(   不管
2.输出 a
3.+ 记录
4.(   不管
5.输出 b
6.* 记录
7.输出 c
8.)   输出 *, 删除 stack 顶的 *
9.)   输出 +，删除 stack 顶的 +
```


### 具体代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;

stack<char> a; //建立stack
int n;
string s;

int main()
{
    cin >> n;
	while(n--){
		cin >> s; //输入中缀表达式
		int len = s.length();
		for(int i = 0; i < len; i++){
			if(((s[i] - '0') >= 49) && ((s[i] - '0') <= 74)){
				cout << s[i];
			}
            //判断字母
			else if(s[i] != '(' && s[i] != ')'){
				a.push(s[i]);
			}
            //记录运算符
			else if(s[i] == ')'){
				cout << a.top();
				a.pop();
			}
            //输出运算符
		}
		cout << endl;
	}
	return 0;
}
```

$多短的代码啊~$


---

## 作者：Herkezi (赞：1)

这是一道普及-(~~即使我认为它有普及难度~~)的题目，中缀表达式转为后缀表达式。

做这道题，如果要用模拟做法（因为还有递归实现的方法，~~可惜我不太解释得来~~，所以讲模拟算法），首先我们要知道，什么是前缀、中缀和后缀以及栈（~~废话~~）。

如果你不知道什么叫前缀、中缀和后缀以及栈，请认真阅读分割线以内的文字。
————————————————————————————————

这个“缀”是指运算符在算术表达式中的位置。

比如一个算术表达式：a+b，a和b是运算数，+是运算符

a+b就是它的中缀表达式，也是我们一般习惯的形式。

+ab是它的前缀表达式，即运算符放在运算数之前。

ab+是它的后缀表达式，即运算符放在运算数之后。

前缀、中缀和后缀讲清楚了（~~我认为的~~），接下来就是栈了。

栈其实就是一个坑（至于为什么，看后面）……

首先，栈有两个基本操作：入栈和出栈（也叫压栈和弹栈）。

要明白栈到底是个什么东西，且先听个故事。

一天，a、b、v（别问为什么不是c，~~关于c，他死了~~）三个人按先后顺序走在路上（这就是一个准备入栈的序列）。

突然，a掉坑里了（栈从空转为非空，当然这题与栈空不空没多大关系）……

此时一种神秘的力量指向了a（栈顶指针），~~“少年，你就是被命运选中的人！”~~咳咳，不好意思，莫名犯中二了。

此时a便是栈里唯一的元素，他可以出来继续走路，也可以在坑里当个地头蛇。

我们假设他选择当了地头蛇。

之后，b也掉进来了。那股神秘的力量又指向了他，~~“少年……”~~咳咳。

此时他也可以选择走或留，不过他不能动a，因为a是大哥，比他厉害。

后面的v和b差不多，也是这么个情形。哪怕后面有再多的人，他们如果进了这个坑，依旧只能自己选择，而不能左右别人，包括入栈序列里的人，因为他们没有加入这个栈（~~坑~~）。

因此，栈只可以对栈顶元素进行操作（就是只能处理最后掉坑的人，~~因为他是萌新~~，而下面的人都是他大哥，后面的人都和他没关系，他除了自己谁也动不了）。

————————————————————————————————

好了，(~~假装~~)概念都说清楚了，算法（~~其实也就是模拟~~）就看代码注释吧（~~逃~~）。
```
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
string s; //这是要读入的字符串。 
char x[405];  //这是储存字符的栈。 
int top=0;  //这是栈顶指针。 
int main()
{
	freopen("transfer.in","r",stdin);
	freopen("transfer.out","w",stdout);
	int n;
	cin>>n;  //n个中缀表达式。 
	while (n--)
	{
		cin>>s;  //在这里我们要明确一件事，题目里说明保证有唯一解，也就是说不会出现x+y+z这种东西。 
		//而是把x+y作为一个基本形式。 
		for (int i=0;i<s.size();i++)
		{
			if (s[i]>='a' && s[i]<='z')
				cout<<s[i];  //如果是字母直接输出，因为后缀表达式的运算符要放在运算数之后。 
			if (s[i]=='(' || s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/' || s[i]=='^')
				x[++top]=s[i];  //如果是前括号或是运算符，压入栈。 
			if (s[i]==')')  //碰见后括号了，把到前括号之前的运算符全输出。 
			{
				while (x[top]!='(')
					cout<<x[top--];
				top--;  //注意把压入的前括号给删了（其实也不是删 ，而是把栈顶指针移到前括号下面，再有要压入栈的元素就会把它覆盖掉）。 
			}		
		}
		cout<<endl;  //注意要回车。 
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```

---

## 作者：FutureThx (赞：0)

## 前提知识


$\ $1.$C++$基础语法（[菜鸟教程快速入门](https://www.runoob.com/cplusplus/cpp-tutorial.html)）

$ $
2.会运用 $STL$ 库中的栈（自己手写的大佬当我没说）

$ $
3.中缀及后缀表达式的概念


## 思路 

$ \ $  **A了这道题，总共需三步！**

$ $
**1.** 读入一个中缀表达式，声明一个栈

$ $
**2.** 对于表达式中的每个字符单个处理（也就是遍历表达式）
 
$\ \ \ \ $
  $2.1$ 遍历字符 $C_i$ 如果为**小写字母**：直接输出当前字符

$\ \ \ \ $
  $2.2$ 遍历字符 $C_i$ 如果为**右括号或运算符**：压到栈里面去
  
$\ \ \ \ $
  $2.3$ 遍历字符 $C_i$ 如果为**左括号**: 循环弹出栈顶，直到弹出的栈顶为右括号
  
$ $
**3.** 结束此次处理

## 代码
```cpp
#include <iostream>
#include <cstring>
#include <stack>//STL栈所在的头文件
using namespace std;
int main()
{
    int t;
    cin >> t;
    for(int i = 1;i <= t;i++){
        char a[401];
        stack<char> s;//声明一个栈
        cin >> a;
        for(int j = 0;j < strlen(a);j++){//遍历字符数组
            if(a[j] >= 97 && a[j] <= 122)//若为小写字母
                cout << a[j];//直接输入
            else{
                if(a[j] == ')'){//若当前字符为左括号
                    while(s.top() != '('){//循环，终止条件
                        cout << s.top();
                        s.pop();
                    }//输出栈顶，再弹出栈顶
                    s.pop();
                }
                else//若为其他符号(也就是右括号或运算符)
                    s.push(a[j]);//压栈
            }
        }
        cout << endl;
    }
    return 0;//结束代码
}
```
## 后记
$Updata \ 2020.8.13 \ 13:29: \ \ $ 完成题解，求管理员通过 

---

## 作者：wzm2007 (赞：0)

    #include<bits/stdc++.h>
    using namespace std;
    int main()
    {
        stack<char> s;
        int n;
        cin>>n;
        while(n--)
        {
            char c,t;
            cin>>c;
            while(c!='(')cin>>c;
            s.push(c);
            while(c!='\n')
            {
                c=getchar();
                if(c>='a'&&c<='z')cout<<c;
                else if(c!=')')s.push(c);
                else
                {
                    t=s.top();
                    s.pop();
                    while(t!='(')
                    {
                        cout<<t;
                        t=s.top();
                        s.pop();
                    }
                }
            }
            cout<<endl;
        }
        return 0;
    }

---

