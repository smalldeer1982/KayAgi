# Chat Server's Outgoing Traffic

## 题目描述

Polycarp正在开发一个名为“Polychat”的新项目。按照IT的现代倾向，他决定，这个项目也应该包含聊天。为了实现这一目标，Polycarp在笔记本电脑前花费了几个小时，实现了一个可以处理三种命令的聊天服务器：

将一个人加入聊天（“添加”命令）。

从聊天中删除一个人（“删除”命令）。

向所有正在聊天的人发送消息，包括发送消息的人（“发送”命令）。

现在，Polycarp希望了解处理特定命令集时服务器将产生的传出流量。

Polycarp知道聊天服务器不会为“添加”和“删除”命令发送流量。当处理“发送”命令时，服务器向聊天的每个参与者(当前在线的人)发送l个字节，其中l是消息的长度。

由于Polycarp没有时间，他在寻求帮助来解决这个问题。

## 样例 #1

### 输入

```
+Mike
Mike:hello
+Kate
+Dmitry
-Dmitry
Kate:hi
-Kate
```

### 输出

```
9
```

## 样例 #2

### 输入

```
+Mike
-Mike
+Mike
Mike:Hi   I am here
-Mike
+Kate
-Kate
```

### 输出

```
14
```

# 题解

## 作者：Apro1066 (赞：12)

纯模拟。

（刚刚的图片没上传成功现已重新上传）

![](https://cdn.luogu.com.cn/upload/pic/26314.png)

由图可知，把当前一个人说的话的长度*当前在线人数就是本题的解。

```cpp
#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <algorithm>
#include <string>
#include <string.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);//另外提醒大家，加上这个就不要用scanf和printf了
	char s1[101*101*101]={};
	int i=1,j,k,s=0,t=0;//s计算流量，t计算人数
	while(gets(s1))//不断读入数据，直到读入回车+Ctrl+Z+回车
	{
		if(s1[0]=='+')//如果前缀为+
		{
			t++;
		}
		else if(s1[0]=='-')//如果前缀为-
		{
			t--;
		}
		else//如果是消息
		{
			j=0;
			while(s1[j]-':')//向右扫描直到冒号
			{
				j++;//指向
			}
			s=s+(strlen(s1+1)-j)*t;//累计流量
		}
	}
	cout<<s<<endl;//输出流量
	return 0;
}
```

---

## 作者：云浅知处 (赞：10)

[更好的阅读体验？](https://www.luogu.com.cn/blog/wwwluogucn/solution-cf5a)
***
依照题意模拟即可。

举个例子：

$\begin{matrix}+\text{kkcs1}&\text{人数}:1&\text{总流量：0}\\\text{kkcs1:I AK IOI}&\text{人数：1}&\text{总流量：0+8
}\!\!\times\text{1=8}\\+\text{Chi\_prce}&\text{人数：2}&\text{总流量：8}\\\text{Chi\_prce:DNCYBXS}&\text{人数：2}&\text{总流量：8+7}\times2=22\\-\text{Chi\_prce}&\text{人数：1}&\text{总流量：22}\\-\text{kkcs1}&\text{人数：0}&\text{总流量：22}\end{matrix}$

从上表中，我们不难看出：**只要有用户发消息了，那么流量就会增加当前用户数量与消息长度的乘积。**

比如，第二行中$\text{kksc1}$发了一条`I AK IOI`，这条消息长度为$8$，发消息时当前用户数量为$1$，故流量数增加$8\times1=8$。
***
需要注意的几个点：

- 要用`getline`进行整行的输入，否则输入时一旦遇到空格就会停下，然后把接下来的内容放进下一个字符串。
- 题中没给消息总数量，我们可以用`while(getline(cin,s))`来不断读入字符串。

***
接下来，开始写代码啦！
```cpp
#include<bits/stdc++.h>//万能头棒棒哒
using namespace std;

int main(){
	int flow=0,now=0;//flow是流量，now是现有人数
	string s;

	while(getline(cin,s)){//整行整行的输入
		if(s[0]=='+') now++;//如果有人加入了
		else if(s[0]=='-') now--;//如果有人退出了
		else{//如果有人说话了
			for(int i=0;i<s.size();i++){//遍历字符串找到':'的位置
				if(s[i]==':'){//找到啦！
					flow+=(s.size()-i-1)*now;//将流量数加上消息的字节数×目前聊天中的人数
					break;//并退出循环
				}
			}
		}
	}
	
	cout<<flow;//输出流量数
	return 0;//完结撒花
}
```

---

## 作者：Purslane (赞：10)

# 字符串模拟水题
## 可以考验C++选手对字符串处理函数的掌握
## 所以不怎么难
## 只要求出圈内一共有多少个人，再乘上消息的长度
## 上代码
```
#include<bits/stdc++.h>
using namespace std
int ans,people //当前用的流量和在交流的人数 
int main() {
	string k; //输入用指令 
	while(getline(k,cin)) { //整行读入 
		if(k[0]=='+') people+1; //有人加入了 
		else if(k[0]=='-') people-1; //有人退出了 
		else {
			int z=k.find(':'); //找到“：”的位置 
			ans+=people*(k.size()-1-z); //计算它后面有几个字符 ，并乘上当前对话的人数 
		}
	}
	cout<<ans; //答案输出 
	return 233;


```
# 祝大家AC快乐！

---

## 作者：离散小波变换° (赞：2)

## 题目大意

要求统计一个聊天系统的流量总数，共有三个操作：

- $1.$`+<name>`：添加名称叫 `<name>` 的人。
- $2.$`-<name>`：去除名称叫 `<name>` 的人。
- $3.$`<name>:<message>`：名称叫 `<name>` 的人向聊天系统内存在的每个人（包括自己）发送信息 `<message>`。产生的流量是信息长度与聊天系统内人数的乘积。

**保证数据合法**

## 题解

既然没有人用 $\rm Pascal$ 写，那么这里就放一个 $\rm Pascal$ 的题解吧。

$\rm Pascal$ 可以直接用 $\tt readln()$ 读入整行。只需要判断是否到达文件末尾就可以读入多行字符串了。接着就是对读入的字符串进行操作。

题目中有一个很重要的条件，就是添加的人目前必定不在聊天室中，删除的人必定在聊天室中。因此我们不需要考虑加减操作对应的人是否合法，只要遇到 `+` 就让总人数 $+1$，遇到`-`就让总人数 $-1$。

比较关键的是信息长度的统计。我们只需要定位到信息中 `:` 的位置，然后用字符串末尾字符的位置减去它，就可以得到信息的长度。

## 参考代码

```pascal
var s:string; var t,p,l,ans:longint;
begin
t:=0; ans:=0;
while not eof do begin
    readln(s); p:=1; l:=length(s);
    if s[1]='+' then inc(t) else
    if s[1]='-' then dec(t) else begin
        while s[p]<>':' do inc(p);
        ans:=ans+(l-p)*t;
    end;
end;
writeln(ans);
end.
```


---

## 作者：PC_DOS (赞：2)

这是一道字符串模拟题，只需要维护一个表示当前在线人数的变量就可以了。

大致思路:

每行读入一个字符串，讨论该串首字符的情况:

为加号: 在线人数加一。

为减号: 在线人数减一。

其他字符: 这是一条消息，只需要依照题意提取从第一个冒号之后的字符串，并计算本条消息产生的流量即可。

代码:
```
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
using namespace std; //头文件和命名空间
string strMid(string strOrigin, long long iStart, long long iLength){ //从strOrigin[iStart]截取长度为iLength的字符串的函数
	string ans("");
	if (iStart > strOrigin.length() - 1) return ans;
	long long i;
	for (i = iStart;; ++i){
		ans += strOrigin[i];
		if (i >= strOrigin.length() - 1) break;
		if (ans.length() == iLength) break;
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	string sInput; //存放输入的记录
	long long nOnline = 0, iTraffic = 0,i; //nOnline-当前在线人数，iTraffic-记录服务器总流量
	while (getline(cin, sInput)){ //循环读入，调试的时候使用一行CTRL+Z(^Z)终止
		switch (sInput[0]){ //讨论该串首字符的情况
		case '+': //为加号
			++nOnline; //在线人数加一
			break;
		case '-': //为减号
			--nOnline; //在线人数减一
			break;
		default: //其他字符
			for (i = 0; i <= sInput.length() - 1; ++i){ //查找第一个冒号
				if (sInput[i] == ':'){
					break;
				}
			}
			iTraffic += nOnline*strMid(sInput, i+1, sInput.length()).length(); //截取第一个冒号之后的字符串，并计算本条消息产生的流量，由于i>=0，因此将截取长度指定为原字符串的长度可以保证整个消息被截出(strMid函数已经对可能的溢出进行了处理)
		}
	}
	cout << iTraffic; //输出总流量
	return 0; //结束
}
```

---

## 作者：林家三少 (赞：1)

$\color{orange}\text{网课学习后写的第一篇题解.}$

一个寒假没上你谷，咕值掉到了101(有一分是比赛情况的)qaq.

好了废话部分到此结束，下面我们进入正题

题目的输入一共有三种格式：

	第一种是'+'+一串英文，就是加入一个人
    第二种是'-'+一串英文，就是减少一个人
    第三种是一串英文+':'后面跟一大串英文(内容不重要，看长度)
    
然后最后输出的东西就是流量，流量就是发送信息的人发出信息的长度×当前聊天的人数(包括他自己)，要注意的是':'是英文标点

所以上代码吧

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>
using namespace std;
int rs,ans;
string st;
int main(){
	while(getline(cin,st)){ //整行输入，因为不知道有几行，所以用while
		if(st[0]=='+'){
			rs++; //如果是加一个人，那当前人数就+1，名字不重要
		}
		else{
			if(st[0]=='-'){
				rs--; //相反，人数就-1
			}
			else{ //两种情况都不是，那就只剩发送信息了
				for(int i=0;i<=st.size()-1;i++){ //找问号
					if(st[i]==':'){
						ans+=(st.size()-1-i)*rs; 
                        //这个就是求流量的公式
						break; //然后退出继续
					}
				}
			}
		}
	}
	cout<<ans;//最后输出，完结撒花
	return 0;
}

```


---

## 作者：SIXIANG32 (赞：1)

# 蒟蒻又来写题解啦
我是蒟蒻，文笔不好，不要喷我啦。  
——————————————————————————  
题目当中保证输入的数据都是正确的体现了这道题的简单，像毒瘤题目肯定不会给你这个福利滴。添加人第一个字符永远是+，删除人第一个字符永远是-，只要不是这两个操作，就是聊天发送消息。而且我们可以知道，每一次的聊天的流量等于聊天人数×说话的长度，因此这道题的主要思路就理出来了。  
1. 输入若干行数据  
2. 判断第一个字符是+还是-  
	2.1. 是+，人数+1
    2.2. 是-，人数-1  
    2.3  都不是，就把答案更新  
    
———————————————————————————  
那么怎么才能知道这个聊天的字符串聊天的内容的长度呢？  
其实也很简单，string库里有专门的find函数！！！，只要拿总长减“：”的位置即可。注意find函数后还有-1才能得到“：”的位置哦。  
——————————————————————————  
代码献上:
```cpp
#include<iostream>
#include<string>//string一定要加这个头文件
using namespace std;
int sum=0,ans=0;//sum是人数，ans是流量
int main() 
{
	string str;//每行指令
	while(getline(cin,str))//一定要写getline！！！！我就是被这个卡了很长时间，足以看出我的蒻了
		if(str[0]=='+')sum++;/*添加人，人数+1*/else if(str[0]=='-')sum--;/*删除人，人数-1*/ else ans=ans+(str.size()-1-str.find(':'))*sum;/*都不是，就更新答案*/
	cout<<ans<<endl;//完美的输出答案
	return 0;//结束程序咯
}
```

---

## 作者：qzhwyce (赞：0)

~~我又来刷水题题解了~~

------------
### 这题是纯模拟的字符串题
照着题意写就行了。  
题目要求根据输入的命令来计算出流量大小（即消息长度 * 人数）  
那么我们先判断命令的三种种类：  

	1.判断命令开头是否有'+';  
	2.判断命令开头是否有'-';  
	3.循环查找命令中是否有‘:'  
于是就可以得出各个消息长度了。  
当前总人数可以再定义一个变量sum来表示 

------------

## AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
char a[10001];
int ans = 0,sum = 0;
int main(){
	while(gets(a)){//用gets函数输入字符串 ，当没有东西可输入时，gets会返回0，跳出循环 
		if(a[0] == '+'){//判断命令开头是否有'+'
			sum++;//总人数 + 1 
		}else if(a[0] == '-'){//判断命令开头是否有'-'
			sum--;//总人数 - 1 
		}else{
			for(int i = 0;i < strlen(a);i++){
				if(a[i] == ':'){
					ans += (strlen(a) - i - 1) * sum;//计算答案 
				}
			}
		}
	}
	cout<<ans;
	return 0;
}

```


------------
顺便问一下，为什么以while(gets(a))输入数据时，在本地测试啥都不输出，而OJ上却能AC？

---

## 作者：旋风猪皮 (赞：0)

字符串模拟题，不谈了。

题目描述有点诡异，但其实很简单。就是把每次人说的话的长度乘上当时的人数全部加起来，就是最后的结果。整个题中人的名字没有什么用，我们只需要关注人数就好了。

我们可以一行一行读入数据，然后看这一行的第一个字符，是+的话那么就把人数+1，是-就把人数-1，如果都不是，那么说明这行是有一个人在说话，然后我们就从字符串左端向右一直扫描知道找到冒号，然后再用字符串长度和冒号的位置一算就知道说的话的长度了。

代码如下
```
#include<bits/stdc++.h>
using namespace std;
char c[1000001];//开大点，以防万一
int s=0,total=0;//s表示人数，total表示总流量
int main()
{
	while(gets(c+1))//读数据
	{
		if(c[1]=='+') s++;//如果第一个字符是+号，人数+1
		if(c[1]=='-') s--;//同上，反之亦然
		if(c[1]-'+'&&c[1]-'-')//第一个字符不是+或-，说明这一行是描述一个人说话
		{
			int t=1;//字符串起始位置（我习惯从1开始）
			while(c[t]-':') t++;//向右扫描直到冒号
			total+=((strlen(c+1)-t)*s);//算出话的长度，乘上人数，加到总流量里。
		}
	}
	cout<<total;//输出
	return 0;
}
```

---

