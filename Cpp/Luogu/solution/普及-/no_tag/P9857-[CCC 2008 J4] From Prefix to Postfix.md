# [CCC 2008 J4] From Prefix to Postfix

## 题目描述

前缀表示法是一种非传统的算术表达式书写方式。标准的算术表达式书写方式，也被称为中缀表示法，将二元运算符置于操作数之间，例如 $3 + 4$，而在前缀表示法中，运算符置于操作数之前，例如 $+$ $3$ $4$。类似地，$5 - 2$ 的前缀表示法是 $-$ $5$ $2$。具有二元运算符的前缀表达式的一个优点是无需括号，因为运算顺序没有歧义。例如，$5 - (4 - 2)$ 的前缀表示为 $-5$ $-$ $4$ $2$，而 $(5 - 4) - 2$ 的前缀表示为 $-$ $-$ $5$ $4$ $2$。前缀表示法也被称为波兰表示法，以纪念波兰逻辑学家 Jan Łukasiewicz，他在 1920 年左右发明了这种表示法。

类似地，在后缀表示法或逆波兰表示法中，运算符置于操作数之后。

例如，中缀表达式 $(5 - 4) - 2$ 的后缀表示为 $5$ $4$ $-$ $2$ $-$。你的任务是编写一个程序，将前缀算术表达式转换为后缀算术表达式。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
1
+ 1 2
- 2 2
+ 2 - 2 1
- - 3 + 2 1 9
0```

### 输出

```
1
1 2 +
2 2 -
2 2 1 - +
3 2 1 + - 9 -```

# 题解

## 作者：cyb6666 (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/P9857)

------------
### 分析

这道题其实只是一道前缀转后缀的题，难度并不高。

前缀表达式和后缀表达式的区别在于符号的位置。

打个生动的比喻，假设数字和符号都是人。

在前缀表达式时，参与运算的数字就是参与运算的符号的小跟班，参与运算的符号永远在参与运算的数字的前面。

在后缀表达式时，情况就不一样了，这下参与运算的符号成了参与运算的数字的小跟班。

此时我们就能想到一种递归的解法：

每次递归，我们先输入当前的操作值。

	 如果是数字，直接输出。
 	 否则，我们先调用递归函数两次（找两个老大），再输出本身。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
void dfs() {
	string s;	//一定要用局部变量
	cin >> s;
	if (s[0] == '0')
		exit(0);	//直接结束程序
	if (s[0] >= '0' && s[0] <= '9')
		cout << s << " ";
	else {
		dfs();	//找第一个老大
		dfs();	//找第二个老大
		printf("%c ", s[0]);	//输出自己
	}
}
int main() {
	while (1) {
		dfs();
		puts("");
	}
	return 0;
}

```

### 完结撒花，留下一个赞吧~

---

## 作者：zyn_ (赞：1)

# P9857 [CCC 2008 J4] From Prefix to Postfix

## 题目大意

给定前缀表达式，求后缀表达式。

## 题目分析

设前缀表达式为 $c_1,c_2,\dots,c_n$。

考虑遍历表达式树。对于一个表达式树的子树，其在前缀表达式中为连续的一段。

因此，设计以下 `dfs()` 函数：

维护全局变量 $pos$，代表现在遍历的子树的根。

首先，令 $p=pos$ 为 $pos$ 的一个副本。

如果 $c_p$ 为运算符，那么没有到达表达式树的叶结点。令 $pos$ 加一，调用 `dfs()` 遍历左子树；再令 $pos$ 加一，调用 `dfs()` 遍历右子树。

然后输出 $c_p$ 即可。

注意处理输入格式。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
char c[30],a;
int pos,n;
void dfs(){
	int p=pos;
	if(c[p]<48||c[p]>57)++pos,dfs(),++pos,dfs();
	putchar(c[p]),putchar(32);
}
int main(){
	while(a=getchar(),a-48){
		n=1;
		c[1]=a;
		while(1){
			a=getchar();if(a=='\n')break;
			a=getchar();if(a=='\n')break;
			c[++n]=a;
		}
		pos=1;dfs();puts("");
	}
	return 0;
}
```

---

## 作者：zbzbzzb (赞：1)

我们可以看看前缀表达式和后缀表达式的区别。

可以发现，前缀就是把符号提到这个表达式前面，后缀就是把符号拖到这个表达式后面。

因此，我们可以递归到每一个表达式，然后把后面两个表达式先继续递归输出，再输出符号。

AC CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt,cntnow;
char t[1000010];
string s;
void out(){
	cntnow++;
	int now=cntnow;
    if(t[now]<='0'||t[now]>'9'){
        out(),out();
    }printf("%c ",t[now]);
}int main(){
	while(1){
    	getline(cin,s);
        if(s[0]=='0'){
    		return 0;
		}int len=s.size();
		cnt=0,cntnow=0;
		for(int i=0;i<len;i+=2){
			t[++cnt]=s[i];
		}out();
		printf("\n");
    }return 0;
} 
```

---

## 作者：Hulless_barley (赞：1)

[题目超链接](https://www.luogu.com.cn/problem/P9857)

首先让我们来了解一下三种表达式：
- 中缀表达式 $1+2$；
- 前缀表达式 $+\ 1\ 2$；
- 后缀表达式 $1\ 2\ +$。

这道题是将前缀表达式转化为后缀表达式（逆波兰表达式）。我们通过观察可知，前缀表达式将运算符号提前，而后缀表达式将符号调后。那岂不是数字不变，只需要把符号放到最后输出就行了？那么我们可以分如下两种情况讨论：
1. 如果输入的是数字，直接输出；
2. 如果输入的是符号，先输出后面的两个数字（或表达式），再输出符号。

这样的话，这题就迎刃而解啦！
```cpp
#include<bits/stdc++.h>
using namespace std;
void print(){
    char a[105];
    cin>>a;
    if(a[0]=='0')exit(0);//如果读到0，就直接终止程序 
    if(!(a[0]>'0'&&a[0]<='9')){
        print();//先输出后面的数字（或表达式） 
        print();//同上 
        cout<<a[0]<<' ';//再输出符号 
    }
    else cout<<a<<' ';//直接输出数字 
}
int main(){
    while(true){
        print();
        cout<<endl;//别忘记换行！ 
    }
    return 0;//养成好习惯 
}
```


---

## 作者：ICU152_lowa_IS8 (赞：0)

一道有趣的思维题。

主要思路其他题解都已经讲过了，这里重新讲述一遍：

如果碰到的是数字，输出；

如果碰到的是符号，那么向后继续遍历两个分支。

但没有一篇题解给出证明，这里给出作者的一个思路：

___

众所周知，一个式子可以化为一个二叉树。这里给出一个例子便于说明：

![](https://cdn.luogu.com.cn/upload/image_hosting/tlxcri32.png)

前缀表达式，即该二叉树的前序遍历，写成表达式是 $-2+1\text{ }1$；

中缀表达式，即该二叉树的中序遍历，写成表达式是 $2-(1+1)$（这个对解题没什么用但可以了解一下）；

后缀（逆波兰）表达式，即该二叉树的后序遍历，写成表达式是 $2\text{ }1\text{ }1 + -$。

对仅有两个数字和一个运算符的情况进行讨论：

![](https://cdn.luogu.com.cn/upload/image_hosting/ztmjtu5l.png)

前缀表达式下，为前序遍历，顺序为根左右，所以符号在题目输入中先被读入。

后缀（逆波兰）表达式下，为后序遍历，顺序为左右根；发现什么没？根移到了后面！表面上这显而易见，但是实际上如果推到了这一步，已经足以做对这道题：**题目先读入的是符号，而输出时把符号挪到后面去即为我们需要的答案**。

对该结论进行拓展：

![](https://cdn.luogu.com.cn/upload/image_hosting/9gv1wwxv.png)

**$c$ 为任意运算符，$u$ 和 $v$ 均为表达式树（或数字叶节点），读入时先读入的是 $c$，然后才是 $u$ 和 $v$，我们只要将 $c$ 放在后面输出就可以了。**


这正是其他题解“遇到符号递归左右两个分支”说法的由来。
___

本题只需要延迟符号的输出即可，方法有多种，最常用的就是递归，代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int now=0;
string s;
int len;
void dfs(){
	if(now>len)return;
	now+=2;
	int pr=now-2;
	if(s[pr]>'9'||s[pr]<'0'){
		dfs();
		dfs();
	}
	cout<<s[pr]<<" ";
}
int main(){
	while(1){
		getline(cin,s);
		now=0;
		len=s.length();
		if(s=="0"){
			break;
		}
		dfs();
		cout<<endl;
	}
	return 0;
}

```


---

## 作者：__zfy__ (赞：0)

### 思路

首先考虑递归处理前缀表达式的部分，对于每次读入一个字符，是数字就直接输出，是运算符就接着递归求左右两个分支，最后输出这个运算符。

接着考虑输入，如何把所有的字符读进来呢？其实只要使用 `getline(cin,s);` 就可以了，这个输入函数会把所有字符读入，也就是包括空格的一切字符都会被读入。

最后考虑主函数部分，开始时先判断这个字符串是否只有一个 $0$，如果是，直接 `break`，代表着程序结束。然后观察每行格式，看出每次下标 $i$ 加二即可，可以保证每一个都是字符。每次先将计数器 $s + 1$，然后让 $ts_s = s_i$，因为在搜索时需要看现在到这一位的字符串的字符是否是数字。

### 代码

搜索部分。
```cpp
void dfs()
{
    t++;
    int i=t;
    if(c[i]<'0'||c[i]>'9') dfs(),dfs();
    cout<<c[i]<<" ";
}
```

---

## 作者：wwd_ewen (赞：0)

### 思路
输入前缀表达式，转化成后缀表达式。这是前缀表达式与后缀表达式：

**前缀表达式**：$-\times+\ 3\ 4 \ 5 \ 6$

**后缀表达式**：$3\ 4+ 5\times 6\ -$

通过观察可以发现：前缀表达式运算符号提前，后缀表达式运算符号靠后。那么我们分成两种情况讨论。

1. 是**数字**直接输出；

2. 是**运算符号**先输出后两个数字再输出运算符号。

用递归函数就能解出来了。递归中如果读到 0 直接用 exit 结束程序，不能用 return 因为还会返回到 main 函数。
```cpp
//洛谷P9857 
#include <stdio.h>
#include <stdlib.h> //exit函数需用库 
void hzbds()
{
    char a[105]; scanf("%s",a); //输入前缀表达式 
    if(a[0]=='0') exit(0); //如题意读到0终止，不能用return，直接终止程序 
    if(a[0]>'0'&&a[0]<='9') printf("%s ",a); //数字直接输出 
    else //是运算符号先输出后两位数字再输出运算符号 
    {
    	hzbds(); hzbds(); //后两位数字 
        printf("%c ",a[0]); //运算符号 
    }
}
int main()
{
    while(1) //死循环，结束条件exit(0)在函数中 
    {
        hzbds(); //将前缀表达式转化成后缀表达式 
        puts(""); //换行 
    }
    return 0; //完美结束好习惯 
}
```
注：本题解引用他人的内容，参考[此处](https://www.luogu.com.cn/blog/wn-wsx-zzh-is-clever/solution-p9857)。

---

## 作者：noi2077 (赞：0)

可以递归处理前缀表达式。递归时先读入一个字符，如果是数字就直接输出，否则就递归处理两个表达式，然后输出这个运算符。

`getline(cin,str)` 可以从 `cin` 中读入一行存到字符串 `str` 中。

```cpp
#include<iostream>
#include<sstream>
using namespace std;
char c[1000005];
int cur = 0;
void dfs()
{
    int nw = ++cur;
    if(c[nw] < '0' || c[nw] > '9') dfs(), dfs();
    cout << c[nw] << " ";
}
int main()
{
    string str;
    while(getline(cin, str))
    {
        if(str == "0") break;
        int cnt = 0; cur = 0;
        for(int i = 0; i < str.length(); i+=2)
        {
            c[++cnt] = str[i];
        }
        dfs();
        cout << endl;
    }
    return 0;
}
```

---

