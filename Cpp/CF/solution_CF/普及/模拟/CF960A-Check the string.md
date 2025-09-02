# Check the string

## 题目描述

A has a string consisting of some number of lowercase English letters 'a'. He gives it to his friend B who appends some number of letters 'b' to the end of this string. Since both A and B like the characters 'a' and 'b', they have made sure that at this point, at least one 'a' and one 'b' exist in the string.

B now gives this string to C and he appends some number of letters 'c' to the end of the string. However, since C is a good friend of A and B, the number of letters 'c' he appends is equal to the number of 'a' or to the number of 'b' in the string. It is also possible that the number of letters 'c' equals both to the number of letters 'a' and to the number of letters 'b' at the same time.

You have a string in your hands, and you want to check if it is possible to obtain the string in this way or not. If it is possible to obtain the string, print "YES", otherwise print "NO" (without the quotes).

## 说明/提示

Consider first example: the number of 'c' is equal to the number of 'a'.

Consider second example: although the number of 'c' is equal to the number of the 'b', the order is not correct.

Consider third example: the number of 'c' is equal to the number of 'b'.

## 样例 #1

### 输入

```
aaabccc
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
bbacc
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
aabc
```

### 输出

```
YES
```

# 题解

## 作者：_tommysun_ (赞：1)

这题就是道超水的模拟题。。。逐个判断条件就行了。

**思路：**
- 分为三部分，逐一判断三个条件。
- 第一部分：判断字母的顺序

这部分是很简单的，根本不用大费周折写那么多代码。如果顺序正确的话，那么就是升序排列。所以说只要先把这个字符串排序一下，看看它与原来的字符串是否一样。如果一样，则满足条件。
- 第二部分：判断是否至少有一个$a$和一个$b$

先用循环把字符串扫一遍，再设两个计数器，扫到这个字母相对应的计数器就+$1$，最后再判断一下就行了。
- 第三部分：判断$c$的数量是否与$a$的数量或是与$b$的数量相等。

和第二部分同理，最后判断一下就行了。

**代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int cnta,cntb,cntc;
	cnta=cntb=cntc=0;
	string s;
	cin>>s;
	string t=s;
	sort(t.begin(),t.end()); //字符串的排序方法。 
	if(t!=s){ //如果不是升序的，就不符合第一个条件。 
		cout<<"NO"; return 0;  
	} 
	for(int i=0;i<s.size();i++){ //扫一遍。 
		if(s[i]=='a') cnta++;
		else if(s[i]=='b') cntb++;
		else if(s[i]=='c') cntc++;
	}
	if(cnta==0||cntb==0){ //判断是否有至少一个a,b。 
		cout<<"NO"; return 0;
	}
	if(cntc!=cnta&&cntc!=cntb){ //判断c的数量是否与a的数量或b的数量相等。 
		cout<<"NO"; return 0;
	}
	cout<<"YES";
	return 0;
}
```


---

## 作者：时律 (赞：1)

### 题意翻译

~~(我被禁言了所以没有发翻译)~~

$A$有一个由若干小写英文字母“$a$”组成的字符串。他把它给了他的朋友B，他的朋友B在这个字符串的末尾附加了一些字母“$b$”。因为$A$和$B$都喜欢字母“$a$”和“$b$”，他们已经确保在这一点上，字符串中至少有一个a和一个b。

现在$B$把这个字符串给了$C$，并在字符串的末尾添加了一些字母“$c$”。但是，因为$C$是$A$和$B$的好朋友，所以他添加的字母$c$的数量等于$a$的数量或者字符串中的$b$的数量。也有可能字母$c$的数量同时等于字母$a$的数量和字母$b$的数量。

您手中有一个字符串，您想检查这个字符串是否符合上述要求。如果符合，请输出“$YES$”，否则输出“$NO$”(不带引号)。

---

这一题还算是有些难的。

首先，要确保这个字符串的顺序是先$a$再$b$再$c$，样例2就是说明了这个。

然后，还要保证字符串里不能有多段的$a$，$b$，$c$。

接着就能快乐统计了：

```
#include<bits/stdc++.h>
using namespace std;
string s;
#define A s.find('a')
#define B s.find('b')
#define C s.find('c')
//用宏定义的原因是不用的话代码太长了……
int main()
{
	int a=0,b=0,c=0;
	cin>>s;
	if(A>B or A>C or B>C or A==-1 or B==-1 or C==-1)//判断顺序是先a再b再c，同时无聊地判了一下是不是都存在
	{
		cout<<"NO";
		return 0;
	}
	if(s.rfind('a')+1!=B or s.rfind('b')+1!=C)//确保不存在多的abc段
	{
		cout<<"NO";
		return 0;
	}
	for(int i=0;i<s.size();i++)//快乐统计
		if(s[i]=='a') a++;
		else if(s[i]=='b') b++;
		else c++;
	if(a==c or b==c)//判断
		cout<<"YES";
	else
		cout<<"NO";
}

```

~~这道CF的题竟然卡了我20分钟~~

---

## 作者：Suuon_Kanderu (赞：0)

这个题虽然简单，但我们也可以用栈来解决他。

栈的方法 
```
stack<L>name//L是某种数据类型，name就是名字

name.empty()//栈是否为空，访问栈顶和取出栈顶元素是必须访问，不然容易RE

name.pop();//取出栈顶元素

name.push(s);//向栈里放入一个元素

//我们基本就用这几个
```

回到正题，此题有几个``` NO```的情况

- b或c 在a前面

- c在b前面

- push b或c 栈时为空

- c的数量 $\not =$ b的数量 并且 c的数量 $\not =$ a的数量

没了，放代码

```
#include<bits/stdc++.h>
using namespace std;
stack<char>a;
int main() {	
	char s;
	int a_cnt = 0,b_cnt = 0,c_cnt = 0;//abc的出现几次
	while(cin >> s) {//在线
		if(s == 'a'){
			if(!a.empty()){//判断栈是否为空
				if(a.top() != 'a'){
					cout << "NO";return 0;
				}
			}
			a.push(s),a_cnt++;	
		}
		if(s == 'b'){
			if(a.empty() || (a.top() == 'c') ){//c在b前面
				cout << "NO";return 0;
			}
			else a.push(s),b_cnt++;			
		}
		if(s == 'c') {
			if(a.empty() || (a.top() == 'a' ) {//b夹空了
				cout <<"NO";return 0;
			}
			else a.push(s),c_cnt++;
		}
	}
	if(c_cnt != a_cnt && c_cnt != b_cnt || a== 0|| b==0)//没有a或b
			cout << "NO";return 0;
	}
	cout << "YES"; return 0;
}

}

```


---

## 作者：Dark_Sky (赞：0)

这题还是算~~比较水~~的，因为本蒟蒻不会find，所以就用了暴力方法做这题。

要求:

1.c的数量要等于b的数量或a的数量。如：aaabbcc(b=c)

2.保证a后面是a或b或c,b后面是b或c,c后面只能是c。如：aaaabc,不能是bbaacc

3.保证有a和b。

上代码：

```cpp
#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 5001;
char s[MAXN];
int a,b,c;//a,b,c的计数器

int main(){
	cin>>s;
	int len = strlen(s);//字符串的长度
	for(int i = 0;i < len;i++){
		if(s[i] == 'a')a++;
		else if(s[i] == 'b')b++;
		else c++;
	}
	for(int i = 0;i < len;i++){//判断a后面是不是b,b后面是不是c
		if(s[i] == 'b'){//判断b后面有没有a
			for(int j = i;j < len;j++){
				if(s[j] == 'a'){//有,输出NO,程序结束
					cout<<"NO"<<endl;
					return 0;
				}
			}
		}
		if(s[i] == 'c'){//判断c后面有没有b和a
			for(int j = i;j < len;j++){
				if(s[j] == 'a' || s[j] == 'b'){//有,输出NO,程序结束
					cout<<"NO"<<endl;
					return 0;
				}
			}
		}
	}
	
	if(a != c && b != c || a == 0 || b == 0){//判断一下字母c的数量是否等于a的数量或者字符串中的b的数量a和b有没有.
		cout<<"NO"<<endl;
		return 0;
	}
	cout<<"YES"<<endl;//如果你走到这里了,恭喜,输出YES
	return 0;//完美结束
}
```


---

