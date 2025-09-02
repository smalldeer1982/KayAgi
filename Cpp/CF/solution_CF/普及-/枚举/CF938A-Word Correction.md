# Word Correction

## 题目背景

给一个长为n的字符串，当有两个元音字母相邻时，删除后一个元音，输出修改后的字符串。（注：a,e,i,o,u,y为元音字母）

## 题目描述

Victor tries to write his own text editor, with word correction included. However, the rules of word correction are really strange.

Victor thinks that if a word contains two consecutive vowels, then it's kinda weird and it needs to be replaced. So the word corrector works in such a way: as long as there are two consecutive vowels in the word, it deletes the first vowel in a word such that there is another vowel right before it. If there are no two consecutive vowels in the word, it is considered to be correct.

You are given a word $ s $ . Can you predict what will it become after correction?

In this problem letters a, e, i, o, u and y are considered to be vowels.

## 说明/提示

Explanations of the examples:

1. There is only one replace: weird ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png) werd;
2. No replace needed since there are no two consecutive vowels;
3. aaeaa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png)aeaa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png)aaa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png)aa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png) a.

## 样例 #1

### 输入

```
5
weird
```

### 输出

```
werd
```

## 样例 #2

### 输入

```
4
word
```

### 输出

```
word
```

## 样例 #3

### 输入

```
5
aaeaa
```

### 输出

```
a
```

# 题解

## 作者：yizimi远欣 (赞：3)

## 思想

首先判断是否为元音，如果是，就去看后面有多少连续的元音，一并标记（删除）然后去找下一个元音；

## 代码实现及注释

```c
#include<bits/stdc++.h>
using namespace std;
#define go(i,j,n,k) for(int i=j;i<=n;i+=k)//循环偷懒
#define fo(i,j,n,k) for(int i=j;i>=n;i-=k)
#define mn 105
char a[mn];
int n;
bool b[mn];//记录是否被删除
int main(){
	cin>>n;
	go(i,1,n,1){
		cin>>a[i];
		b[i]=true;
	}
	go(i,1,n,1){
		if(b[i]){//是否被删除
			if(a[i]=='a'||a[i]=='e'||a[i]=='o'||a[i]=='i'||a[i]=='u'||a[i]=='y'){//判断是不是元音
				go(j,i+1,n,1){
					if(a[j]=='a'||a[j]=='e'||a[j]=='o'||a[j]=='i'||a[j]=='u'||a[j]=='y'){//循环看有没有连续的元音
						b[j]=false;
					}else{//只要有不是的，直接退出小循环，寻找下一组元音
						break;
					}
				}
			}
		}
	}
	go(i,1,n,1){
		if(b[i]){
			cout<<a[i];
		}
	}
	return 0;
}
```

---

## 作者：Eason_AC (赞：1)

## Content
有一个长度为 $n$ 的，只包含小写字母的字符串，只要有两个元音字母相邻，就得删除后一个元音字母（$\texttt{a,e,i,o,u,y}$ 中的一个），请求出最后得到的字符串。

**数据范围：$1\leqslant n\leqslant 100$。**
## Solution
我们遍历字符串，判断当前扫到的字符是否是元音字母，这样好在遍历到下一个字母时判断是否需要删除，不需要的话直接输出当前字符就好。
## Code
```cpp
string s;
int vowel = 0, n;

int main() {
	getint(n);
	cin >> s;
	_for(i, 0, n - 1) {
		if((s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'y') && vowel) continue;
		printf("%c", s[i]);
		vowel = (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'y');
	}
	return 0;
}
```

---

## 作者：lwz2002 (赞：1)

说实话，这道题比较水
要做题的话还是建议大家刷C级以上的哈
下面进入正题
------------
大致思路就是先输入，之后判断，是辅音就输出，是原因就删去后面的原音
详解看代码
```

#include<bits/stdc++.h>//万能库最好用

using namespace std;
int main()
{
int n;
cin>>n;
string a;
cin>>a;
for(int i=0;i<n;i++)//注意字符串的首项是**零**
{
	if(a[i]!='a'&&a[i]!='e'&&a[i]!='i'&&a[i]!='o'&&a[i]!='u'&&a[i]!='y')//这里要用并且，因为是判断辅音嘛
	cout<<a[i];
	else{
		cout<<a[i];
		int x=i;
		while(x<n){
			if(a[i]=='a'||a[i]=='e'||a[i]=='i'||a[i]=='o'||a[i]=='u'||a[i]=='y')//判断元音当然是或者啦 
            i++;
			else break;
		}
	i--;//这一步是因为是从i开始的，而i位置是元音，第一个肯定加一，所以到最后再减去        虽然直接定义x=i+1就行了。。。。。
	}
}
return 0;完美结束
}
```


---

## 作者：happybob (赞：0)

STL大法好，602ms，速度第4

代码来了，用的是STL库的string和布尔类型flag的搭配

代码有注释

```cpp
#include <iostream>
#include <cstring>//string头文件
using namespace std;

int main()
{
    int n;
    bool flag = false;//初始值为false
    string str;
    cin >> n >> str;
    while(!flag)//不会死循环的
    {
        flag = true;
        for(string::iterator it = str.begin(); it != str.end(); it++)//string迭代器
        {
            if(*it == 'a' || *it == 'e' || *it == 'i' || *it == 'o' || *it == 'u' || *it == 'y')//判断是否元音，用*访问迭代器指向的那个数据
            {
                if(*(it + 1) == 'a' || *(it + 1) == 'e' || *(it + 1) == 'i' || *(it + 1) == 'o' || *(it + 1) == 'u' || *(it + 1) == 'y')
                {
                    str.erase(it + 1);//删除it + 1位置的数据
                }
            }
        }
        for(int i = 0; i <= str.length() - 1; i++)//这里不用迭代器了，length读取string长度
        {
            if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' || str[i] == 'y')
            {
                if(str[i + 1] == 'a' || str[i + 1] == 'e' || str[i + 1] == 'i' || str[i + 1] == 'o' || str[i + 1] == 'u' || str[i + 1] == 'y')
                {
                    flag = false;//如果还有两个相邻元音，flag等于false
                    break;//break不能少
                }
                else
                {
                    flag = true;//否则flag变为true
                }
            }
            else
            {
                flag = true;//否则flag变为true
            }
            //如果flag为true的话会停止循环
        }
    }
    cout << str << endl;
    return 0;
}
```


---

## 作者：monstersqwq (赞：0)

#### 题意：

给一个长为 $n$ 的字符串，当有两个元音字母相邻时，删除后一个元音，输出修改后的字符串。

做法1；

对于字符串中每个字符（除了第一个），如果这个和前一个不都是元音，就输出当前字符，否则不输出。

实际上这种做法可以一边输入一边处理，但是还需要加一个判断上一个是否为元音的变量，我懒得搞了，就套个数组吧，毕竟 $1 \le n \le 100$。

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
using namespace std;
bool check(char a)
{
    if(a=='a'||a=='e'||a=='i'||a=='o'||a=='u'||a=='y') return true;
    else return false;
}//定义判断元音函数，简化代码
int main()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    for(int i=0;i<n;i++)
    {
        if(i==0)
        {
            cout<<s[i];
            continue;
        }//第一位必须输出，特判
        if(check(s[i])&&check(s[i-1])) ;
        else cout<<s[i];
    }
    return 0;
}
```

做法2：

建一个栈，如果当前字符和栈顶都是元音，就不输出也不压栈，否则输出，再把当前字符压到栈里。

这个可以一边输入一边处理，可以干掉一个数组。

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;
bool check(char a)
{
    if(a=='a'||a=='e'||a=='i'||a=='o'||a=='u'||a=='y') return true;
    else return false;
}
stack<char> q;
int main()
{
    int n;
    cin>>n;
    char s;
    for(int i=1;i<=n;i++)
    {
    	cin>>s;
    	if(q.empty())
    	{
    		q.push(s);
    		cout<<s;
		}
		else
		{
			if(check(s)&&check(q.top())) ;
			else
			{
				cout<<s;
				q.push(s);
			}
		}
	}
    return 0;
}
```


---

## 作者：Zirnc (赞：0)

[ChungZH's blog](https://chungzh.cn) · [ChungZH's OI blog](https://oi.chungzh.cn) · [ChungZH's portfolio](https://chungzh.cc)

（看了看题解，好像我的还算比较简洁易懂吧...

简单解释一下代码：

- `isaeiouy` 判断是否元音
- 循环
	
    - 如果这个字母和下一个字母都是元音，先输出这个字母，然后 一直 `i++` 直到下一个字母不是元音

## Code

```cpp
#include <iostream>
using namespace std;

inline bool isaeiouy(const char c)
{
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y')
        return true;
    return false;
}

int main()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    for (int i = 0; i < n; i++)
    {
        cout << s[i];
        if (isaeiouy(s[i]) && isaeiouy(s[i+1]))
            while (isaeiouy(s[i+1]) && i < n-1)
                i++;
    }

    return 0;
}
```

---

## 作者：judgejudge (赞：0)

# 通俗易懂！！！
因为可以把所有的字母分成**元音和辅音**两大类：所以储存一个数组，**令元音为1，辅音为0.**

然后就可以把一个字符串转换成01序列的形式。以样例1为例：
| w | e | i | r | d |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| 0 | 1 | 1 | 0 | 0 |
**这样转换成01序列可以让我们感觉更直观**，因此更好判断。

然后我们就可以查找是否出现两个相邻的1，如果出现就只输出前一个即可！！！

奉上代码：
```cpp
#include <iostream>
#include <string>
using namespace std;
char c[6]={'a','e','i','o','u','y'};
int a[100001];
int main(){
    int i,j,k,n;
    string st;
    cin>>n;
    cin>>st;
    for(i=0;i<st.length();i++){
        for(j=0;j<6;j++)
        if(st[i]==c[j]){
            a[i]=1;
            j=6;
        }
    }
    int time=0;
    for(i=0;i<st.length();i++){
        if(a[i]==0)cout<<st[i];
        else if(time==0){
            cout<<st[i];
            time++;
        }
    }
    cout<<endl;
    return 0;
}
```
如果把这个代码提交，很尴尬的是，第4个点就会出错。

因为有可能会出现这样的情况：

| a | e | p | a | e |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| 1 | 1 | 0 | 1 | 1 |

**如果根据这个代码，判断第2个元音的时候，之后的元音就都不会输出，即使它们不相邻！！！**

**所以这个代码的缺陷就是无法判断两个及以上相邻元音！！！**

那么我们改进一下：
```cpp
#include <iostream>
#include <string>
using namespace std;
char c[6]={'a','e','i','o','u','y'};//储存元音数组
int a[100001];//定义01序列
int main(){
	int i,j,k,n;
	string st;
	cin>>n;
	cin>>st;
	for(i=0;i<n;i++){
		for(j=0;j<6;j++)
		if(st[i]==c[j]){//一旦发现元音，变为1
			a[i]=1;
			j=6;
		}
	}
	int time=0;
	for(i=0;i<n;i++){
		if(a[i]==0){//如果是辅音的话，说明此时不会出现相邻的元音，它的起点需要重新设置
		    cout<<st[i];
		    time=0;//此时让起点为0，因为辅音必定阻碍两个元音相邻
		}
		else if(time==0){//如果是元音，并且是第一个
		    cout<<st[i];
		    time++;//保证不会输出后一个元音
		}
	}
	cout<<endl;
	return 0;//程序结束
}
```



---

## 作者：·靈·柒· (赞：0)

    var i,j,k,n:longint;s:string;
    begin
      readln(n);//n其实没什么用
      readln(s);//读入
      i:=1;s:=s+' ';//以防万一
      while i+1<length(s) do
        begin
          while (s[i] in ['a','e','i','o','u','y'])
          and(s[i+1] in ['a','e','i','o','u','y'])
            do delete(s,i+1,1);//一定要用while
          inc(i);//下一个
        end;
      writeln(s);
    end.



---

## 作者：珅肐 (赞：0)

### 思想：如果当前字母与前一个都是元音字母，就什么也不做，否则输出当前字母

代码：
```c
#include<iostream>
using namespace std;
char s;//连数组也不用开，在线做
int main()
{
    int n,m=0;//m要赋初值为0，表示未标记
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        if(s!='a' && s!='e'&& s!='i' && s!='o' && s!='u' && s!='y')//这个地方很坑啊！y是半元音也算！我第一遍就错了
            cout<<s,m=0;//输出并且取消标记
        else if(m) continue;//如果是元音字母并且前一个也是元音字母，直接continue进行下一遍循环
        else cout<<s,m=1;//如果前一个不是元音字母，标记一下，并输出
    }
    return 0;
}
```

---

## 作者：Chthology (赞：0)

### 题目大意：

给一个长为n的字符串，当有两个元音字母相邻时，删除后一个元音，输出修改后的字符串。（注：a,e,i,o,u,y为元音字母）

###### ~~仅供参考~~

---

### 思路：

线性扫一遍字符串，遇到元音字母标记一下，如果有标记时遇到元音字母，不输出，否则输出。遇到辅音字母，抹掉标记并输出。

---

### 代码：
```cpp
#pragma GCC diagnostic error "-std=c++14" //暴力开C++14
#pragma GCC optimize ("O3")               //开O3

#include<bits/stdc++.h>
using namespace std;

int n;

int main(){
	std::ios::sync_with_stdio(false);
	cin>>n;
	cin.get();
	bool tag=true;
	for(int i=1;i<=n;++i){
		char c=cin.get();
		if(c!='a'&&c!='e'&&c!='i'&&c!='o'&&c!='u'&&c!='y'){cout<<c;tag=true;}
		else if(tag){cout<<c;tag=false;}
	}
	return 0;
}
```

---

