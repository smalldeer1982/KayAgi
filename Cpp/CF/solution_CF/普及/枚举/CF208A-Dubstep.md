# Dubstep

## 题目描述

## 题目翻译
Vasya有一句歌词(可能含有空格)，他在第一个单词之前和最后一个单词之后加上若干(可以为0)个"WUB",再每个单词之间加上若干(至少为1)个"WUB"，转变成一个新的字符串(无空格)
如"I AM X" 可以变成 "WUBWUBIWUBAMWUBWUBX" 而不能变成 "WUBWUBIAMWUBX"
现在给出转变后的字符串，求出原来的字符串

## 样例 #1

### 输入

```
WUBWUBABCWUB
```

### 输出

```
ABC ```

## 样例 #2

### 输入

```
WUBWEWUBAREWUBWUBTHEWUBCHAMPIONSWUBMYWUBFRIENDWUB
```

### 输出

```
WE ARE THE CHAMPIONS MY FRIEND ```

# 题解

## 作者：封禁用户 (赞：5)

我又来水CF了……

这只是个字符串模拟。。

### 题意

规定 $S$ 为一些单词加上一堆 `WUB` 后的字符串。

规定一个单词前有 $1$ 个或多个 `WUB` 。

求 $S$ 的原串。

### $\sf{Solution}$

模拟，小问题。

读入后把 $S$ 中所有的 `WUB` 去掉。

边输出边标记，让单词与单词间仅有一个空格。

### $\sf{Code}$

```cpp
#include<iostream>
#include<cstring>
using namespace std;
string s;
bool flag=true;//第一个单词前的空格不能输出
int main()
{
	cin>>s;
	for(int i=2;i<s.length();++i)
		if(s[i]=='B'&&s[i-1]=='U'&&s[i-2]=='W')
			s[i]=s[i-1]=s[i-2]=' ';//去"BUW"
	for(int i=0;i<s.length();++i)
    {
		if(s[i]!=' ')
			flag=false;//不是空格就可以输出
		if(!flag)
			cout<<s[i];//因为是输出后标记，所以可以保证输出第一个空格
		if(s[i]==' ')
			flag=true;//遇到空格就要标记啦
    }
	return 0;
}
```

---

## 作者：happybob (赞：3)

模拟即可，只需要把输入的字符串中WUB删掉，但重点是要处理空格！

首先通过样例2可以发现，如果两个字符串中有WUB，那么会产生一个空格。

那如何处理呢？很简单，遍历一遍，发现前面那个是WUB就输出一下"."，代码如下，1.63ms，有注释：

```cpp
#include <iostream>
#include <cstring>
using namespace std;

char x[205];

int main()
{
    cin >> x;
    int len = strlen(x) - 1;
    for(int i = 0; i <= len; i++)
    {
        if(x[i] == 'W' && x[i + 1] == 'U' && x[i + 2] == 'B')//判断是否是WUB，如果是，那么久不用输出了，并且i直接加3
        {
            i += 2;//这里加2
            continue;//continue会加1
        }
        else//不然就输出并且判断下一个是否是WUB
        {
            cout << x[i];
            if(x[i + 1] == 'W' && x[i + 2] == 'U' && x[i + 3] == 'B')//如果是就输出.，这里不用i加多少了，因为下一次循环会进入第一分支的
            {
                cout << " ";
            }
        }
    }
    cout << endl;
    return 0;
}
```
求赞

---

## 作者：Hu_Tao (赞：2)

# ~~啦啦啦~我的第二篇题解~~~

先说题目意思.

给了你一个字符串s.
s里有一些~~乱七八糟的~~字符(全是大写)

现在要把字符串里的WUB换成空格,输出换完了的字符串.

举个栗子:(SAMPLE2)

s=WUBWEWUBAREWUBWUBTHEWUBCHAMPIONSWUBMYWUBFRIENDWUB

把WUB换成空格之后就是WE ARE THE CHAMPIONS MY FRIEND 

下面考虑代码.

很显然这是一道模拟题.

那么怎么模拟呢?

很显然我们可以从左往右扫描,看到了WUB就变成空格,输出就完了.

口胡完毕,那么接下来就是要解决的几个问题:

1.找WUB的过程.很显然只需要判断si=='W'&&si+1=='U'&&si+2=='B'就可以了.

### 2.找完之后直接跳过,不要管空格

为什么不加空格?

举个栗子,比如第二个样例中的一部分吧.

假设s="AWUBWUBB",如果直接加空格,答案会变成：

s'='A'+空格+空格+'B'

两个空格肯定不行,所以不加.

那么怎么跳过呢?很简单,就这样↓

```cpp
		if(i+2<s.size()&&s.substr(i,3)=="WUB")
		{
			i+=3;
			continue;
		}
```


3.如果s.substr(i,3)不是WUB,那么就把答案装到ans里(ans为记录答案的字符串).

4.如果后面还有WUB,就加空格

到这里跳不跳过都无所谓,反正下一边循环碰到这个WUB就直接过去了.

所以这四部操作加起来就长这样:

```cpp
for(int i=0;i<s.size();)
{
	if(i+2<s.size()&&s.substr(i,3)=="WUB")
	{
		i+=3;
		continue;
	}
	
	ans+=s[i];
	i++;
	
	if(i+2<s.size()&&s.substr(i,3)=="WUB")ans+=' ';
}
```
最后附上完整代码:

```cpp
#include<bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define pb push_back
#define mp make_pair
#define Unique(x) x.erase(unique(all(x)),x.end());

using namespace std;

const int dx[]={-1,0,1,0};
const int dy[]={0,-1,0,1};

const int Days[]={-1,31,28,31,30,31,30,31,31,30,31,30,31};

inline int read()
{
	#define gc getchar
	int ans=0;
	bool f=1;
	char ch=gc();
	
	while(!isdigit(ch))f^=ch=='-',ch=gc();
	
	while(isdigit(ch))ans=((ans<<2)+ans<<1)+(ch^48),ch=gc();
	
	return f?ans:-ans;
	
	#undef gc
}

typedef long long ll;

string s;
string ans;

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	
	cin>>s;
	
	for(int i=0;i<s.size();)
	{
		if(i+2<s.size()&&s.substr(i,3)=="WUB")
		{
			i+=3;
			continue;
		}
		
		ans+=s[i];
		i++;
		if(i+2<s.size()&&s.substr(i,3)=="WUB")ans+=' ';
	}
	
	cout<<ans;
	
	//printf("Time used = %.12f",(double)(clock())/CLOCKS_PER_SEC);
	return 0;
}

/*  GOD BLESS  */

```

求过!求点赞!谢谢!

---

## 作者：liuyifan (赞：1)

题意:输入一个字符串,将所有连续的WUB替换为空格,输出替换后的字符串

解法:按题意暴力模拟即可,时间复杂度O(n)

code:
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register
using namespace std
string s,tmp;
int main()
{
    getline(cin,s);//与cin>>s相比可以直接读入一整行,将空格一并读入,遇到回车停止(虽然这道题好像并没有)
    for(reg int i=0;i<s.length();)
    {
        string t=s.substr(i,3);//s.substr(a,b)指s从a开始b位的一个字串
        if(t=="WUB")i+=3;//直接跳过
        else
        {
            tmp+=s[i++];//tmp为答案字符串
            //i++和++i的区别:前者是先用(取值)再加，后者是先加再用
            string t=s.substr(i,3);//取字串,同上
            if(t=="WUB")tmp+=' ';//跳过
        }
    }
    cout<<tmpendl;//输出
    return 0
}
```

拒绝抄袭,共建和谐洛谷



---

## 作者：Argon_Cube (赞：0)

- **【题目链接】**

[Link:CF208A](https://www.luogu.com.cn/problem/CF208A)

- **【解题思路】**

#### **1. 总结题意：**

给定一个字符串，删去里面所有的 *WUB* ,并把原来被 *WUB* 分割的相邻单词间加上一个空格。

---
#### **2.看到字符串，自然想起了$string$类。**
---

#### **3. 想想如何实现。**

* 如何删去*WUB*？

要删去所有的*WUB*，必须一个一个找到它们。

然后就想起$string$类有一个$find$方法。

_（find，最常用的原型为string::find(char*),接受一个字符串，返回该字符串在调用者中的下标。如果没有找到，返回string::npos。)_

又想起：$find$相当于遍历一遍字符串啊，反复调用会超时吗？

数据范围：$|SSS|≤200$。

所以再怎么折腾都不会超时的 :)

* 删去 *WUB* 后如何确定是相邻的两个单词还是一个？

那就替换，找到一个 *WUB* 就把它替换成空格！

* 多出的空格怎么办？

当遇到空格时查看上一个字符是否为空格，如果是就不输出。

可以用一个字符变量`last`存储上一个字符。

* `last`的初始值是什么？

我们暂时还不知道。

* 如何跳过开头的空格？

简单，不用特判，直接假装开头已经输出了一个空格（然而并没有）。

`last`的初始值也出来了：空格（$ASCII\ 32$）。

把`last`设为空格代表上一个字符是个空格，后面的不用再输出了。

* 如何跳过结尾的空格？

不用处理，评测机会忽视每行末尾的空格。

- **【代码】**

```cpp
#include <iostream>

using namespace std;

int main(int argc,char *argv[],char *env[])
{
	string org;
	unsigned long long pos;
	cin>>org;
	while((pos=org.find("WUB"))!=string::npos)
		org[pos]=org[pos+1]=org[pos+2]=' ';//找到WUB就把它替换成空格
	char last=' ';
	for(char tmp:org)
	{
		if(tmp==' ')
		{
			if(last!=' ')
				cout<<' ';
		}
		else
			cout<<tmp;
		last=tmp;
	}
	return 0;
}

```


---

## 作者：Eason_AC (赞：0)

## Content
有一个字符串被变换了。其中在这个字符串的前面加了 $\geqslant 0$ 个 ``WUB``，每个单词（由空格间隔）之间加了 $\geqslant 1$ 个 ``WUB``，在这个字符串的后面加了个 $\geqslant 0$ 个 ``WUB``。现在给出变换之后的字符串（长度为 $n$），求原来的字符串。

**数据范围：$n\leqslant 200$。**
## Solution
我们直接遍历这个字符串，一碰到 ``WUB`` 就不输出，否则输出当前字符一直到一个 ``WUB`` 前面的一个字符（注意，这种情况如果不是在当前字符串中第一次出现的话要加个空格）。
## Code
```cpp
string s;
int len, cur, word;

int main() {
	cin >> s;
	len = s.size(), cur = 0;
	while(cur < len) {
		if(s[cur] == 'W' && s[cur + 1] == 'U' && s[cur + 2] == 'B')	cur += 3;
		else {
			if(word)	printf(" ");
			word++;
			while((s[cur] != 'W' || s[cur + 1] != 'U' || s[cur + 2] != 'B') && cur < len) {
				printf("%c", s[cur]);
				cur++;
			}
		}
	}
	return 0;
}
```

---

## 作者：_Legacy (赞：0)

#### 分析

1. 输入字符串s
2. 判断$s_i$到$s_{i+2}$是否为"WUB"
`if(s[i]=='W'&&s[i+1]=='U'&&s[i+2]=='B')`
3. 如果2.成立，跳过后面的'W'和'B'(`i+=3`)
4. 如果2.成立，判断上一个是不是"WUB",如果不是，输出空格
5. 如果2.不成立，下一项(`i++`),用$t=1$标记这一项不是"WUB"

#### 完整代码

```
#include<bits/stdc++.h> 
using namespace std;
char s[201];
bool t;
int main(){
	cin >> s;
	for(int i=0;i<strlen(s);){
		if(s[i]=='W'&&s[i+1]=='U'&&s[i+2]=='B'){
			i+=3;
			if(t==1){
				cout << " ";
				t=0;
			}
				
		}
		else{
			cout << s[i];
			i++;
			t=1;
		}
	}
}
//CF208A
```

---

## 作者：SIXIANG32 (赞：0)

显而易见这又是一道字符串模拟。  
我们可以分解成如下几个子问题：  

- 子问题1：怎么查找替换？  
- 子问题2：替换成什么？
- 子问题3：怎么构成目标字符串？

让我们一一解决：

- 子问题1：查找我们可以用```string```库中的```find```函数去解决，替换则可以用```string```库中的```replace```函数完成。  
- 子问题2：当然是三个空格啦。  
- 子问题3：用子问题1和子问题2的操作把输入字符串给操作一遍后遍历。如果是遇到了不是空格的字符就直接添加并且打标机说明这是一个单词。如果遇上了空格就判断是否打上了标记。若有，直接添加并解除标记表示这不是单词。  

最后总结一个坑点：  

- 如果构成的目标字符串第一个字符是空格要删除  

上代码：  
```cpp
#include<iostream>
#include<string>
using namespace std;
int main()
{
	bool flag=0;//标记
	string str,ans="";//ans是目标字符串
	cin>>str;
	while(str.find("WUB")!=string::npos)//子问题1和子问题2：查找替换
		str.replace(str.find("WUB"),3,"   ");
	for(int p=0;p<=str.size()-1;p++)//子问题3也是核心：构造目标字符串
		if(str[p]!=' ')ans+=str[p],flag=0;//这是单词打上标记
		else if(!flag)ans+=str[p],flag=1;//这不是单词解除表设计
	if(ans[0]==' ')ans.erase(0,1);//特判
	cout<<ans<<endl;//输出
	return 0;//结束
}
```

---

## 作者：灵光一闪 (赞：0)

~~一看只有两篇题解，本蒟蒻也来发一波~~~

这个题嘛，难点只有一个：

### 前面的空格怎么办？

## 好的，辣么我们开始解答

### 直接把循环变量加到不是空格处为止

**代码**：

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>
#include<string>
using namespace std;

int main()
{
    string s;
    cin>>s;
    bool q=false;
    if(s.size()<=2)//如果长度小于3，直接输出
    {
        cout<<s;
        return 0;
    }
    for(int i=0;i<s.size()-2;i++)
    {
        if(s.substr(i,3)=="WUB")//先全换成空格
        {
            s[i]=s[i+1]=s[i+2]=' ';
            i+=2;
        }
    }
    for(int i=0;i<s.size();i++)
    {
        if(s[i]==' '&&!q)//行首空格，不用管
            continue;
        else//如果不是行首空格，输出（不管ta是字母还是空格）因为无论你中间有多少个空格，都是对的（不知道是不是checker出错了
        {
            cout<<s[i];
            q=true;
        }
    }
    return 0;
}
```


---

