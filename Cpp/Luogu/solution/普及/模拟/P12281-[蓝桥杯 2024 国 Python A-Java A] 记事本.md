# [蓝桥杯 2024 国 Python A/Java A] 记事本

## 题目描述

小蓝经常用记事本记录文字，最近他发现记事本功能太少，因此他写了一款插件用来支持记事本更多的文本编辑功能，这些功能如下表所示：

| 命令 | 功能 |
| :---: | :---: |
| $[n]\mathrm{h}$ | 光标向左移动 $[n]$ 个字符（到最左侧则停止）。 |
| $[n]\mathrm{l}$ | 光标向右移动 $[n]$ 个字符（到最右侧则停止）。 |
| $\mathrm{insert}$ "$[text]$" | 在当前光标位置插入文本 $[text]$，同时光标移动到 $[text]$ 右侧。 |
| $\mathrm d [n]\mathrm{h}$ | 删除光标左侧 $[n]$ 个字符（不足 $[n]$ 则全删除）。 |
| $\mathrm d [n]\mathrm{l}$ | 删除光标右侧 $[n]$ 个字符（不足 $[n]$ 则全删除）。 |

小蓝建立了一个新的文本文件，初始是空白的，在经过若干次上述操作之后，请将文本内容输出。

## 说明/提示

### 评测用例规模与约定

对于所有评测用例，$1 \leq T \leq 100$，$1 \leq |text| \leq 100$，$1 \leq n \leq 100$，$text$ 仅包含大小写字母、数字、空格。

## 样例 #1

### 输入

```
9
d1h
insert "hello"
insert " world"
7h
d2h
insert "11"
3l
d1l
insert "0"```

### 输出

```
he11o w0rld```

# 题解

## 作者：volatile (赞：7)

# 思路

## 模拟方式

模拟罢了，但是如何实现光标？考虑使用两个栈 $a$ 和 $b$，$a$ 表示光标左侧的文字，$b$ 表示光标右侧的文字（如下图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/rs1k1ore.png)

## 操作判断

这里反而是最简单的。

### 光标移动的判断

判断读入的字符串第一位是不是数字即可，至于往左和往右看最后一位。

获取 $n$ 的方式很简单，从第一位遍历到倒数第二位（最后一位是方向）用一个初始为 $0$ 的变量 $t$，每次乘以 $10$ 在加上当前字符，就能实现增加位数。


```cpp
int t=0;
for(int i=0;i<s.size()-1;i++) t=t*10+(s[i]-'0');
```

在移动过程中，每移动一位就要将对应方向的栈顶字符插入到另一个栈中（如下图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/v4z511r4.png)


```cpp
if(s[s.size()-1]=='h'){
    while(t--&&!a.empty()){
        b.push(a.top());
        a.pop();
    }
}
else{
    while(t--&&!b.empty()){
        a.push(b.top());
        b.pop();
    }
}
```

### 删除字符的判断

看第一位和最后一位，大同小异，只是获取 $n$ 要从第二位开始。删除字符的方式也很简单，根据方向把对应的栈的栈顶弹出即可。

```cpp
if(s[s.size()-1]=='h') while(t--&&!a.empty()) a.pop();
else while(t--&&!b.empty()) b.pop();
```
### 插入字符串

由于插入字符串是统一在光标左侧，所以只需要插入在 $a$ 栈即可。

```cpp
for(int i=8;i<s.size()-1;i++) a.push(s[i]);
```

## 输出

现将 $a$ 栈的所有字符转移到 $b$ 栈，最后遍历 $b$ 栈即可。

# 代码


```cpp
#include<iostream>
#include<stack>
using namespace std;
stack<char>a,b;
int main()
{
    int T;
    cin>>T;
    string s;
    getline(cin,s);
    while(T--){
        getline(cin,s);
        if(s[0]>='0'&&s[0]<='9'){
            int t=0;
            for(int i=0;i<s.size()-1;i++) t=t*10+(s[i]-'0');
            if(s[s.size()-1]=='h'){
                while(t--&&!a.empty()){
                    b.push(a.top());
                    a.pop();
                }
            }
            else{
                while(t--&&!b.empty()){
                    a.push(b.top());
                    b.pop();
                }
            }
        }
        else if(s[0]=='d'){
            int t=0;
            for(int i=1;i<s.size()-1;i++) t=t*10+(s[i]-'0');
            if(s[s.size()-1]=='h') while(t--&&!a.empty()) a.pop();
            else while(t--&&!b.empty()) b.pop();
        }
        else{
            for(int i=8;i<s.size()-1;i++) a.push(s[i]);
        }
    }
    while(!a.empty()){
        b.push(a.top());
        a.pop();
    }
    while(!b.empty()){
        cout<<b.top();
        b.pop();
    }
    return 0;
}
```

---

## 作者：_WCW_ (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P12281)
 # 解题思路
 本题是字符串模拟题，不熟悉字符串请看[此处](http://oi-wiki.com/lang/csl/string/)。
 ## 读入
 读入循环次数 $T$ 后，循环 $T$ 次，每次操作使用字符串读入，根据题目中每种操作的格式进行判定，之后操作。
 ## 光标移动
 设置一个指针模拟光标，之后将移动操作中的数提取出来，进行左移或右移操作，对于超过最左侧或最右侧的情况进行特判。
 ## 插入
 判断是插入操作后，继续读入后面要插入的字符串，去掉引号和 $\text{insert}$ 之间的空格，根据光标当前位置进行插入。
 ## 删除
 提取输入中的数字，根据光标位置进行向左删除或向右删除，对于不足 $n$ 的情况进行特判。
 # [AC](https://www.luogu.com.cn/record/215888466) 代码
 
```cpp
#include<bits/stdc++.h>
using namespace std;
string ans="",in;//ans为最终结果，in为输入的操作
int p,t,k,num;//p为光标，num为光标移动操作或删除操作中提取出来的数
int main()
{
    cin>>t;//输入循环次数T
    for(int i=1;i<=t;i++)
    {
        num=0,k=0;//初始化
        cin>>in;//输入每轮操作
        if(in[in.size()-1]=='h' && in[0]!='d')//判断是否为向左移动光标的操作
        {
            for(int i=in.size()-2;i>=0;i--)//提取数
            {
                num+=(in[i]-'0')*pow(10,k++);
            }
            /*
              这里和下文的提取数采用按权展开求和
              例如53=5*10^1+3*10^0
            */
            if(ans.empty()) p=0;//字符串为空特判
            else if(num>p) p=0;//超过最左侧特判
            else p-=num;//正常左移操作
        }
        else if(in[in.size()-1]=='l' && in[0]!='d')//判断是否为向右移动光标的操作
        {
            for(int i=in.size()-2;i>=0;i--)//提取数
            {
                num+=(in[i]-'0')*pow(10,k++);
            }
            if(ans.empty()) p=0;//字符串为空的特判
            else if(num>=ans.size()-p) p=ans.size();//超过最右侧特判
            else p+=num;//正常右移操作
        }
        else if(in=="insert")//判断是否为插入操作
        {
            string text;//要插入的字符串
            getline(cin,text);//中间会有空格，用getline读入
            text.erase(0,2);//删除insert后面的空格及引号
            text.erase(text.size()-1,1);//删除最后的引号
            ans.insert(p,text);//根据光标位置插入
            p+=text.size();//移动光标
        }
        else if(in[0]=='d' && in[in.size()-1]=='h')//判断是否是向左删除操作
        {
            for(int i=in.size()-2;i>=1;i--)//提取数
            {
                num+=(in[i]-'0')*pow(10,k++);
            }
            if(p<num)//对不足n的特判
            {
                ans.erase(0,p);//向左删除
                p=0;//更改光标
            }
            else
            {
                ans.erase(p-num,num);//正常向左删除操作
                p-=num;//更改光标
            }
        }
        else if(in[0]=='d' && in[in.size()-1]=='l')//判断是否是向右删除操作
        {
            for(int i=in.size()-2;i>=1;i--)//提取数
            {
                num+=(in[i]-'0')*pow(10,k++);
            }
            if(ans.size()-p<=num)//对不足n的特判
            {
                ans.erase(p,ans.size()-p);//向右删除
            }
            else ans.erase(p,num);//正常向右删除操作
            //向右删除不用更改光标，可以举几个例子验证一下
        }
    }
    cout<<ans;//输出最后结果

    return 0;
}
```
## Python
```python
ans=""
p=0
t=int(input())
for _ in range(t):
    line=input().strip()
    if line.endswith('h') and not line.startswith('d'):
        num_str=line[:-1]
        num=int(num_str) if num_str else 0
        if not ans:
            p=0
        else:
            p=max(p-num,0)
    elif line.endswith('l') and not line.startswith('d'):
        num_str=line[:-1]
        num=int(num_str) if num_str else 0
        if not ans:
            p=0
        else:
            a=len(ans)-p
            if num>=a:
                p=len(ans)
            else:
                p+=num
    elif line.startswith('insert'):
        tmp=line.split('"')
        text=tmp[1] if len(tmp)>=2 else ""
        ans=ans[:p]+text+ans[p:]
        p+=len(text)
    elif line.startswith('d') and line.endswith('h'):
        num_str=line[1:-1]
        num=int(num_str) if num_str else 0
        if p<num:
            ans=ans[p:]
            p=0
        else:
            ans=ans[:p-num]+ans[p:]
            p-=num
    elif line.startswith('d') and line.endswith('l'):
        num_str=line[1:-1]
        num=int(num_str) if num_str else 0
        a=len(ans)-p
        if a<=num:
            ans=ans[:p]
        else:
            ans=ans[:p]+ans[p+num:]
print(ans)
```

---

## 作者：longyitongxue (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P12281)  
[博客使用效果更佳](https://www.luogu.com.cn/article/x1bln8wn)
# 主要思路
本题是一道栈的题目，如果纯用字符串模拟，会炸掉几个点，我们可以用两个栈，想象成一个栈顶朝右，一个栈顶朝左的两个栈，用栈的空隙来模拟光标。详细栈的内容请见 [OI Wiki](https://oi-wiki.org/ds/stack/)。由于本题比较复杂，我们分步骤来做。
## Step $\bf1$：命令的输入
题目中命令的输入是一个难点，它不像往常那样先输入 $op$，然后跟着几个数的操作。我们必须先读入一整行字符串（因为 $\textmd{insert}$ 操作会有空格），然后对字符串进行拆分。由于插入和删除有明显的 $\textmd{insert}$ 和 $\textmd{d}$ 的标志，我们可以写两个判断，看包不包含 $\tt insert$ 子串或是 $\tt d$ 子串，包含 $\tt insert$ 子串的就是插入，包含 $\tt d$ 子串的就是删除，剩下一个没有明显标志的就是移动了。

接下来，我们就可以把移动或删除命令中出现的数提取出来，插入命令的字符串提取出来。Step $1$ 就算完成了。
```cpp
        getline(cin,s);
        if(s.find("insert")!=string::npos){
            string ins;
            for(int i=s.find("\"")+1;s[i]!='\"';i++){
                ins.push_back(s[i]);
            }
//          cout<<ins;
        }else if(s.find("d")!=string::npos){
            int num=0;
            for(int i=s.find("d")+1;s[i]>='0'&&s[i]<='9';i++){
                num=num*10+s[i]-'0';
            }
//          cout<<num;
        }else{
            int num=0;
            for(int i=0;s[i]>='0'&&s[i]<='9';i++){
                num=num*10+s[i]-'0';
            }
//          cout<<num;
        }
```
## Step $\bf2$：插入
为什么先写插入呢？因为插入代码最简单，因为题目描述中插入 $\rm text$ 后把光标移至其右边，所以我们只用往左栈里插入这个字符串的每个字符就行了。Step $2$ 简单明了。
```cpp
            for(int i=0;i<ins.size();i++){
                l.push(ins[i]);
            }
```
## Step $\bf3$：向左向右移动
次简单的操作就是向左向右移动了。如果光标向左移动，我们就让左栈的字符插入右栈，如果是光标向右移动，我们就让右栈的字符向左移动。Step $3$ 也秒了。
```cpp
            if(s.find("h")!=string::npos){
                while(num!=0&&l.size()){
                    r.push(l.top());
                    l.pop();
                    num--;
                }
            }else{
                while(num!=0&&r.size()){
                    l.push(r.top());
                    r.pop();
                    num--;
                }
            }
```
## Step $\bf4$：删除
既然移动都秒了，那么删除也没那么难了。如果要删除光标左边，那就弹出左栈的字符，反之删除右栈的字符。Step $4$ 结束后，操作就做完了。
```cpp
            if(s.find("h")!=string::npos){
                while(num!=0&&l.size()){
                    l.pop();
                    num--;
                }
            }else{
                while(num!=0&&r.size()){
                    r.pop();
                    num--;
                }
            }
```
## Step $\bf5$：输出
操作结束，我们就该输出了。我们需要把左栈的字符全都插入右栈，输出右栈中的每个字符（如果把右栈的字符插入左栈就会成为倒序的答案）。Step $5$ 结束，完结撒花~
```cpp
    while(l.size()){
        r.push(l.top());
        l.pop();
    }
    while(r.size()){
        cout<<r.top();
        r.pop();
    }
```
# [AC](https://www.luogu.com.cn/record/214854375) code
```cpp
#include<iostream>
#include<stack>
#include<bits/stdc++.h>
using namespace std;
stack<char> l,r;
int main(){
    int t;
    cin>>t;
    string s;
    getline(cin,s);
    while(t--){
        getline(cin,s);
        if(s.find("insert")!=string::npos){
            string ins;
            for(int i=s.find("\"")+1;s[i]!='\"';i++){
                ins.push_back(s[i]);
            }
//          cout<<ins;
            for(int i=0;i<ins.size();i++){
                l.push(ins[i]);
            }
        }else if(s.find("d")!=string::npos){
            int num=0;
            for(int i=s.find("d")+1;s[i]>='0'&&s[i]<='9';i++){
                num=num*10+s[i]-'0';
            }
//          cout<<num;
            if(s.find("h")!=string::npos){
                while(num!=0&&l.size()){
                    l.pop();
                    num--;
                }
            }else{
                while(num!=0&&r.size()){
                    r.pop();
                    num--;
                }
            }
        }else{
            int num=0;
            for(int i=0;s[i]>='0'&&s[i]<='9';i++){
                num=num*10+s[i]-'0';
            }
//          cout<<num;
            if(s.find("h")!=string::npos){
                while(num!=0&&l.size()){
                    r.push(l.top());
                    l.pop();
                    num--;
                }
            }else{
                while(num!=0&&r.size()){
                    l.push(r.top());
                    r.pop();
                    num--;
                }
            }
        }
    }
    while(l.size()){
        r.push(l.top());
        l.pop();
    }
    while(r.size()){
        cout<<r.top();
        r.pop();
    }
    return 0;
}
```

---

## 作者：zhangaixi (赞：3)

# **思路**
本题是一道字符串模拟，我们可以用一个字符串 $ans$ 存储答案，一个整数 $now$ 表示光标当前的位置，$now$ 的初始值为 $-1$，每输入一条命令就对 $ans$ 和 $now$ 进行改动。
## **1.输入**
因为我们不知道下一条命令的长度，所以输入时我们可以用字符串 $a$ 输入，然后判断具体是哪一种命令。
## **2.移动光标**
如果命令的第一位是数字，那就是移动光标的命令了。因为输入数据可能会出现光标左侧或右侧不足 $n$ 个字符的情况，所以我们要把光标即将移动到的位置与答案字符串 $ans$ 的边界进行比较。如果是向左移动，光标收到命令后的位置就取光标即将移动到的位置和 $-1$ 取较大值；反之，若是向右移动，就和 $ans$ 的长度 $-1$ 取较小值。

```cpp
if(a[0]>='0' && a[0]<='9'){
	int len=a.size(),l=ans.size(); 
	for(int j=0;j<len-1;j++) num=num*10+a[j]-'0';
	if(a[len-1]=='h') now=max(now-num,-1);
	else if(a[len-1]=='l') now=min(now+num,l-1);
}
```

## **3.插入**
如果命令的第一位是 $i$，那就是插入命令。直接在光标后插入就好，记得要把光标移动到 $[text]$ 的右侧。

```cpp
else if(a[0]=='i'){
	int len=a.size(),l=ans.size();
	ans.insert(now+1,a.substr(8,len-9));
	now+=len-9;
}
```


## **4.删除**
如果命令的第一位是 $d$，那就是删除命令了。 直接删除就好，但要注意边界。值得注意的是删除光标左侧字符时，光标位置要跟着移动；而删除右侧字符时则不用。

```cpp
else if(a[0]=='d'){
	int len=a.size(),l=ans.size();
	for(int j=1;j<len-1;j++) num=num*10+a[j]-'0';
	if(a[len-1]=='h'){
		num=min(num,now+1); 
		ans.erase(now-num+1,num);
		now=now-num;
	}
	else if(a[len-1]=='l'){
		num=min(num,l-1-now);
		ans.erase(now+1,num);
	}
}
```
## **代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,now=-1,num;
string a,ans;
int main(){
	cin>>n;
	getchar();
	for(int i=1;i<=n;i++){
		num=0;
		getline(cin,a);
		int len=a.size(),l=ans.size();
		if(a[0]>='0' && a[0]<='9'){
			for(int j=0;j<len-1;j++) num=num*10+a[j]-'0';
			if(a[len-1]=='h') now=max(now-num,-1);
			else if(a[len-1]=='l') now=min(now+num,l-1);
		}
		else if(a[0]=='i'){
			ans.insert(now+1,a.substr(8,len-9));
			now+=len-9;
		}
		else if(a[0]=='d'){
			for(int j=1;j<len-1;j++) num=num*10+a[j]-'0';
			if(a[len-1]=='h'){
				num=min(num,now+1); 
				ans.erase(now-num+1,num);
				now=now-num;
			}
			else if(a[len-1]=='l'){
				num=min(num,l-1-now);
				ans.erase(now+1,num);
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：awdfkewd (赞：2)

# [蓝桥杯 2024 国] 记事本题解
[题目传送门](https://www.luogu.com.cn/problem/P12281)  
[博客食用](https://www.luogu.com.cn/article/6a9f4bhj)  
~~比较懒，示意图的结点就只画值域了。~~
## 分析
### 核心算法
我们使用双向链表来模拟，可以避免字符串的整体位移。  

理解如何模拟这些命令其实很简单，点开记事本。用两个哨兵结点 $head$ 和 $tail$ 模拟记事本的左右边缘。再定义一个指针 $pointer$ 通过指向光标左侧的字符的结点（如记事本为空则指向 $head$），来模拟光标出现在字符右侧。如图：  
![记事本如图](https://cdn.luogu.com.cn/upload/image_hosting/39ui62t3.png)
#### [n]h
就是按键盘上的 $\larr$ 键让光标右移到屏幕最右边，让 $pointer$ 往左边遍历。
#### [n]l
与上一个类似。**但是请注意**，因为光标不能在 `tail` 的右边（那样就到屏幕外面了，这合理吗？），所以 $pointer$ 到 `tail->left` 就要停下。   
如图：
![光标移动示意](https://cdn.luogu.com.cn/upload/image_hosting/cfzp6wcu.png)
#### insert "[text]"
这个不难理解，就是一个一个插入 text 中的每一个字符，然后 $pointer$ 指向 text 中最后一个字符的结点。
#### d[n]h 以及 d[n]l
回忆一下你平常是如何选取文本的：在一处开始长按（不动的选取开头）并拖到一点（移动的选取末尾）。   
我们便可以模拟这个过程，忽略选取开头和末尾间的删除操作，只处理开头和结尾，并不用一个一个删除结点。  
**但要注意一点**，在删除时光标是否会移动呢？  
又如图：![delete](https://cdn.luogu.com.cn/upload/image_hosting/fy3nsqg1.png)

### 命令读入及结果输出
这里为大家安利一下两个很好用的函数：  
`stoi()` 和 `substr()`。
#### `stoi()`
即 string to int，顾名思义能将读入的 `string` 字符串转为 `int`（读入的字符串如果包含非数字字符，就会报错，平常使用建议搭配 `try-catch`）。
#### `substr()`
读入起始点和裁剪长度（注意！！！**不是**结束点）便可以帮助你裁剪字符串。
## AC CODE（C++）

```cpp
#include<iostream>
#include<cstring>
using namespace std;

// 双向链表节点结构
struct Node {
    char value;       // 存储的字符值
    Node *left;       // 指向前驱节点的指针
    Node *right;      // 指向后继节点的指针
};

// 链表头尾哨兵节点及当前指针
Node *head = new Node;  // 链表头节点，不存储实际数据
Node *tail = new Node;  // 链表尾节点，不存储实际数据
Node *pointer = head;   // 当前光标位置，初始指向头节点

int n;                  // 命令数量
int len, num;           // 临时变量：len存储字符串长度，num存储数字参数
string str;             // 存储输入的命令行

// 光标向左移动n步
void h(int n) {
    while (pointer != head && n > 0) {
        pointer = pointer->left;  // 向左移动光标
        n--;
    }
}

// 光标向右移动n步
void l(int n) {
    while (pointer->right != tail && n > 0) {
        pointer = pointer->right;  // 向右移动光标
        n--;
    }
}

// 删除左边n个字符
void dh(int n) {
    Node *temp = pointer->right;   // 保存当前位置的后继节点
    while (n > 0 && pointer != head) {
        pointer = pointer->left;   // 向左移动n步
        n--;
    }
    pointer->right = temp;         // 跳过被删除的节点
    temp->left = pointer;          // 更新后继节点的前驱指针
}

// 删除右边n个字符
void dl(int n) {
    Node *temp = pointer;          // 保存当前位置
    while (n > 0 && temp->right != tail) {
        temp = temp->right;        // 向右移动n步
        n--;
    }
    if (temp->right == tail) {     // 如果右边没有字符
        pointer->right = tail;     // 直接连接到尾节点
    } else {
        temp->right->left = pointer;  // 更新后继节点的前驱指针
        pointer->right = temp->right;  // 跳过被删除的节点
    }
}

// 在当前位置插入字符串
void insert(string str) {
    int len = str.length();
    for (int i = 0; i < len; i++) {
        Node *node = new Node;     // 创建新节点
        node->value = str[i];      // 设置节点值
        node->left = pointer;      // 新节点的前驱为当前节点
        node->right = pointer->right;  // 新节点的后继为当前节点的后继
        node->right->left = node;  // 更新后继节点的前驱指针
        node->left->right = node;  // 更新前驱节点的后继指针
        pointer = node;            // 移动当前指针到新节点
    }
}

int main() {
    head->right = tail;            // 初始化链表为空
    tail->left = head;
    
    cin >> n;                      // 读取命令数量
    cin.ignore();                  // 读取整数后清空缓冲区，准备读取整行命令
    
    for (int i = 0; i < n; i++) {
        getline(cin, str);         // 读取一行命令
        len = str.length();
        
        if (str[0] == 'd') {       // 删除命令
            if (str[len - 1] == 'h') {  // 删除左边n个字符
                str = str.substr(1, len - 2);  // 提取数字部分
                num = stoi(str);
                dh(num);
            } else {               // 删除右边n个字符
                str = str.substr(1, len - 2);  // 提取数字部分
                num = stoi(str);
                dl(num);
            }
        } else if (str[len - 1] == 'h') {  // 光标左移命令
            str = str.substr(0, len - 1);  // 提取数字部分
            num = stoi(str);
            h(num);
        } else if (str[len - 1] == 'l') {  // 光标右移命令
            str = str.substr(0, len - 1);  // 提取数字部分
            num = stoi(str);
            l(num);
        } else if (str.substr(0, 7) == "insert ") {  // 插入命令
            str = str.substr(8, len - 9);  // 提取要插入的字符串
            insert(str);
        }
    }
    
    // 输出链表中存储的所有字符
    for (Node *i = head->right; i != tail; i = i->right) 
        cout << i->value;
    
    return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/215310260)。

---

## 作者：Zqx_Vector_2014 (赞：0)

这就是一个普通的字符串模拟题，按题意模拟即可，但还是要说几个做法。在这里面，我把 1、2 号要求和 3、4 号要求都放在一个做法里。这几个做法没什么好解释的，就是模拟。所以就用字符串来完成这个任务。由于 1、2 号做法和 4、5 号做法类似，就把它们放在一起处置。在此，我们用 $l$ 当临时变量。

先做一个辅助函数 $\operatorname{num}$ 来把字符串转化成数字：

```cpp
int num(string s){
	int ans=0;
	for(char c:s)ans=ans*10+(c-'0');
	return ans;
}
```

接着用一个字符类变量 $dir$ 提取 $l$ 的最后一位。再做一个字符串类变量 $n\_str$ 为 $l$ 第 $0$ 个下标到最后一位的下标减一的下标再判断一下 $dir$ 为 $h$ 还是 $l$ 分别向左向右移，再用 $\max$ 或 $\min$ 防止越界。

- 第一个和第二个：

```cpp
else{
	char dir=l.back();
	string n_str=l.substr(0,l.size()-1);
	int n=num(n_str);
	if(dir=='h')i=max(0,i-n);
	else i=min((int)str.size(),i+n);
}
```

这个判断 `insert` 的没有技术含量，纯纯模拟，直接跳过。

- 第三个：

```cpp
if(l=="insert"){
	string l;
	getline(cin,l);
	l.erase(0,l.find_first_not_of(" "));
	int first=l.find('\"');
	int last=l.rfind('\"');
	if(first!=string::npos&&last!=string::npos&&first<last){
		string text=l.substr(first+1,last-first-1);
		str.insert(i,text);
		i+=text.size();
	}
}
```

跟第一种方法类似，只是把移动改成了删除防止越界依旧在。

- 第四个和第五个：

```cpp
else if(l[0]=='d'){
	char dir=l.back();
	string n_str=l.substr(1,l.size()-2);
	int n=num(n_str);
	if(dir=='h'){
		int del=min(n,i);
		str.erase(i-del,del);
		i-=del;
	}else{
		int available=str.size()-i;
		int del=min(n,available);
		str.erase(i,del);
	}
}
```

就用这几种做法搭配主函数就可以很容易的做出来了~~非常的简单好吧~~。

# Code：

## C++：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int max(int A,int B){return (A>B)?A:B;}
int min(int A,int B){return (A<B)?A:B;}
int num(string s){
	int ans=0;
	for(char c:s)ans=ans*10+(c-'0');
	return ans;
}signed main(){
	ios::sync_with_stdio(0),
	cin.tie(0),cout.tie(0);
	int T;cin>>T;
	string str;int i=0;
	while(T--){
		string l;cin>>l;
		if(l=="insert"){
			string l;
			getline(cin,l);
			l.erase(0,l.find_first_not_of(" "));
			int first=l.find('\"');
			int last=l.rfind('\"');
			if(first!=string::npos&&last!=string::npos&&first<last){
				string text=l.substr(first+1,last-first-1);
				str.insert(i,text);
				i+=text.size();
			}
		}else if(l[0]=='d'){
			char dir=l.back();
			string n_str=l.substr(1,l.size()-2);
			int n=num(n_str);
			if(dir=='h'){
				int del=min(n,i);
				str.erase(i-del,del);
				i-=del;
			}else{
				int available=str.size()-i;
				int del=min(n,available);
				str.erase(i,del);
			}
		}else{
			char dir=l.back();
			string n_str=l.substr(0,l.size()-1);
			int n=num(n_str);
			if(dir=='h')i=max(0,i-n);
			else i=min((int)str.size(),i+n);
		}
	}
	cout<<str<<endl;
	return 0;
}
```

## Python：

```python
import sys
def num(s):return int(s)
T=int(sys.stdin.readline())
s,i='',0
for _ in range(T):
    l=sys.stdin.readline().strip()
    if l=='insert':
        l=sys.stdin.readline().strip()
        l=l.lstrip()
        first=l.find('\"')
        last=l.rfind('\"')
        if first!=-1 and last!=-1 and first<last:
            text=l[first+1:last]
            s=s[:i]+text+s[i:]
            i+=len(text)
    elif l[0]=='d':
        dir=l[-1]
        n_str=l[1:-1]
        n=num(n_str)
        if dir=='h':
            del_=min(n,i)
            s=s[:i-del_]+s[i:]
            i-=del_
        else:
            avail=len(s)-i
            del_=min(n,avail)
            s=s[:i]+s[i+del_:]
    else:
        dir=l[-1]
        n_str=l[:-1]
        n=num(n_str)
        if dir=='h':i=max(0,i-n)
        else:i=min(len(s),i+n)
print(s)

```

## Java：

```java
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        sc.nextLine();
        StringBuilder sb = new StringBuilder();
        int i = 0;
        while (T-- > 0) {
            String l = sc.nextLine().trim();
            if (l.equals("insert")) {
                String input = sc.nextLine().trim();
                int first = input.indexOf('"');
                int last = input.lastIndexOf('"');
                if (first != -1 && last != -1 && first < last) {
                    String text = input.substring(first + 1, last);
                    sb.insert(i, text);
                    i += text.length();
                }
            } else if (l.startsWith("d")) {
                char dir = l.charAt(l.length() - 1);
                int n = Integer.parseInt(l.substring(1, l.length() - 1));
                if (dir == 'h') {
                    int del = Math.min(n, i);
                    sb.delete(i - del, i);
                    i -= del;
                } else {
                    int available = sb.length() - i;
                    int del = Math.min(n, available);
                    sb.delete(i, i + del);
                }
            } else {
                char dir = l.charAt(l.length() - 1);
                int n = Integer.parseInt(l.substring(0, l.length() - 1));
                if (dir == 'h') {
                    i = Math.max(0, i - n);
                } else {
                    i = Math.min(sb.length(), i + n);
                }
            }
        }
        System.out.println(sb.toString());
    }
}

```

---

