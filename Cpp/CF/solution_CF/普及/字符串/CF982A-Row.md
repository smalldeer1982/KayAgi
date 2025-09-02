# Row

## 题目描述

### 读入一个字符串，只含有$01$两种字符，合法则输出"$Yes$",否则输出"$No$"。
### 不合法情况  
$1$.一个为$0$的字符两旁没有$1$。   
$2$.一个为$1$的字符两旁还有$1$。

## 样例 #1

### 输入

```
3
101
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
4
1011
```

### 输出

```
No
```

## 样例 #3

### 输入

```
5
10001
```

### 输出

```
No
```

# 题解

## 作者：Anguei (赞：10)

据题意，易知：
+ 不合法的情况只有两种：
 + 字符串包含了 `000`
 + 字符串包含了 `11`
+ **字符串两头相当于有一个 `0`（突破点！）**

由此，可以非常简单地写出以下三种做法代码：

### 两行 Python2：
```python
s = (raw_input(), '0' + raw_input() + '0')[1]
print 'No' if ('11' in s or '000' in s) else 'Yes'
```
### 使用 C++ 的 `std::string::find`：
```cpp
#include <string> 
#include <iostream>

int main()
{
	std::string s;
	std::cin >> s >> s;
	s = "0" + s + "0";
	std::cout << (s.find("000") != std::string::npos || s.find("11") != std::string::npos ? "No" : "Yes");
}
```
### C++ 朴素做法
```cpp
#include <string>
#include <iostream>

int main()
{
	int n;
	std::cin >> n;
	std::string s;
	std::cin >> s;
	for (char &c : s)
		c -= 48;
	for (int i = 0; i ^ n; ++i)
	{
		if (s[i] == 1)
			if (s[i - 1] == 1 || s[i + 1] == 1)
			{
				std::cout << "No" << std::endl;
				return 0;
			}
			else
				; 
		else
			if (s[i - 1] == 0 && s[i + 1] == 0)
			{
				std::cout << "No" << std::endl;
				return 0;
			}
	}
	std::cout << "Yes" << std::endl;
}
```

---

## 作者：black_trees (赞：2)

## 发现一道字符串的好题

---

[题目](https://www.luogu.com.cn/problem/CF982A)

---
这道题的大意：

给你一排凳子，让你安排座位。不合法输出`No`合法则输出`Yes`

规则如下：

~~~
1、不可以出现：没人的位置两旁都没有人（000）

2、也不可以出现：有人的座位旁边也有至少一个座位是有人的（11）。
~~~

(其实就是只能是`010101`的情况）

那么，直接去查找`000`和`11`这两个字符串是否存在于输入的字符串就行了。

这里可以运用$STL$里的`find()`来查找（子串）

这个函数如果没找到对应子串就会返回`string::npos`

如下：

```cpp
   in.find("000")!=string::npos||in.find("11")!=string::npos//这里就是在判断有没有出现，如果出现了，那方案绝对不合法
```



不过有几种特殊的情况：

`001`（开头没人）

`100`（结尾没人）

这两种情况应该是不合法的。如果我们只查找`000`的话，那么就会$\color{red}WA$

咋办？


很简单，只需要给字符串首尾各加一个`0`就可以了：

```cpp
void init(string in){
	in="0"+in;
    in+="0";
}
```
思路到这里理清晰了，代码自然可以出来：

$RT$：

```cpp
#include<bits/stdc++.h>
using namespace std;
void init(string in){
	in="0"+in;
    in+="0";
}//初始化（给字符加0）
void put(bool f){
	if(f==false){
		puts("No");
	}
	else{
		puts("Yes");
	}
}//输出
string in;
int n;
bool f;//标志变量
int main(){
	ios::sync_with_stdio(false);//cincout加速
	cin.tie(0);//读入加速
	cin>>n>>in;
    init(in);
	if(in.find("000")!=string::npos||in.find("11")!=string::npos){//判断是否合法
		f=false;
	}
	else{
		f=true;
	}
	put(f);//输出
	return 0;
}
```

---
~~我真的菜，连有翻译都没看到~~

---

## 作者：Doqin07 (赞：1)


#### ~~55个测试点，这很CF~~


------------
### 题目意思：
- ##### 给定一个字符串
- ##### 若一个为$0$的字符两边没有$0$或者一个为$1$的字符两边没有$1$,则这个字符串不合法
- ##### 给定$n$为字符串$s$的长度，让你输出合不合法
---
#### 简单题，直接按照题意模拟即可（个人认为字符数组简单）
---
##### 若一个字符为$0$且两边都没有1则返回$false$，若一个字符为$1$且两边有任意一个位置为$1$则返回$false$
---
### 核心Code
```cpp
bool check (char a[]){
	for (int i = 0 ; i < n ; ++ i){
		if (a[i] == '0') if (a[i - 1] != '1' && a[i + 1] != '1' ) return false;  
		if (a[i] == '1') if (a[i - 1] == '1' || a[i + 1] == '1' ) return false;  
	}
	return true;
}

```



---

## 作者：FJ·不觉·莫笑 (赞：1)

### **一道字符串题！**  
### **读题**
违法情况如下：  
$1.一个为0的字符两旁没有1。$    
$2.一个为1的字符两旁还有1。$  
 
### **思路**：  
遍历每一位，判断是否合法（不合法直接输出，程序结束），合法输出$YES$,不合法输出$NO$.
   
### **所以：**   
只要解决此部分代码，问题就简单了   
条件一解决代码：   
```cpp
if(|s[i]=='0'&&(s[i+1]!='1'&&s[i-1]!='1'))//0的旁边没有1
	cout<<"NO";
```
条件二解决代码：  
```cpp
if(s[i]=='1'&&(s[i+1]=='1'||s[i-1]=='1')//为1旁边还有1
	cout<<"NO";
```

代码如下：   
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;//输入字符串长度
	string s;
	cin>>s;//输入字符窜
	for(int i=0;i<n;i++)
		if(s[i]=='1'&&(s[i+1]=='1'||s[i-1]=='1')||s[i]=='0'&&(s[i+1]!='1'&&s[i-1]!='1'))//是否合法判断
		{
			cout<<"NO";
			return 0;//不合法直接输出，程序结束
		}
	cout<<"YES";//若合法，输出YES
	return 0;
}
```
第一篇题解，求通过（QwQ）

---

## 作者：小恐 (赞：1)

本题惊现管理员大佬！！

管理员大佬用的是$string$，那本蒟蒻就只好用$char$数组了。

思路非常简单，也没有像管理员大佬考虑那么多，只是从第一个字符开始枚举，$find$我也不会（我太弱了！）QWQ。

上代码吧（辣么难的题我觉得也不需要太多解释）:
```cpp
/*稍微学过一点c++的人我估计都能看懂，就不加注释了*/
#include<stdio.h>
using namespace std;
char a[1005];
int main()
{
	int n;
	scanf("%d",&n);
	scanf("%s",a);
	for(int i=0;i<n;++i)
	{
		if(a[i]=='0')
		{
			if(i==0)
			{
				if(a[i+1]!='1')
				{
					printf("No");
					return 0;
				}
			}
			else if(i==n-1)
			{
				if(a[i-1]!='1')
				{
					printf("No");
					return 0;
				}
			}
			else
			{
				if(a[i-1]!='1'&&a[i+1]!='1')
				{
					printf("No");
					return 0;
				}
			}
		}
		else
		{
			if(i==0)
			{
				if(a[i+1]=='1')
				{
					printf("No");
					return 0;
				}
			}
			else if(i==n-1)
			{
				if(a[i-1]=='1')
				{
					printf("No");
					return 0;
				}
			}
			else
			{
				if(a[i-1]=='1'||a[i+1]=='1')
				{
					printf("No");
					return 0;
				}
			}
		}
	}
	printf("Yes");
	return 0;
}                         
```
珍爱生命，远离抄袭

---

## 作者：Cocoly1990 (赞：0)

## 前置芝士
$x.find("")$ 函数 。

作用是查找查找字符串$x$中有没有包含一个子串 ， 如果没有返回$x.npos$。

有了这个这题就很简单了。
## 思路简述
这题有个小坑点，就是字符串前后都有一个$0$ ，要加上去。

仔细审题你就会发现，如果这个数列中包含了子串$000$或$11$，就不合法了。

用上面教的函数去搞，有手就行

## code
```cpp
#include<bits/stdc++.h>
using namespace std ;
string a , n ;
int flag ;
int main()
{
    cin >> n ;
    cin >> a ;
    a = "0" + a; 
    a += "0" ;
    if(a.find("000") != a.npos || a.find("11") != a.npos) cout << "No" ;
    else cout << "Yes" ;
    system("pause") ;
    return 0 ;
}
```
sol by Cocoly1990




---

## 作者：RBI_GL (赞：0)

### 题意：
给定一个01字符串，如果：

$i)$  一个为 $0$ 的字符两旁没有 $1$ 

$ii)$ 一个为 $1$ 的字符两旁还有 $1$

**输入的字符串只要满足以上的任意一条或两条，那么它就是不合法的**。

否则它就是合法的。

----

### 思路：
读入字符串后，遍历它的每一位，判断它是否合法，如果合法就输出 $Yes$ ，否则输出 $No$ 

**判断条件：**

```cpp
 if (a[i-1] != '1' && a[i+1] != '1') flag = false;
  
 if (a[i-1] == '1' || a[i+1] == '1') flag = false;
```

----


### Code：

    #include <bits/stdc++.h>
    using namespace std;
    int n;
    char a[1005];
    bool flag = true;
    int main() {
        cin>>n; 
        for (int i=0;i<n;i++) cin>>a[i]; //读入
        for (int i=0;i<n;i++) { //遍历搜索
            if (a[i] == '0') {
                if (a[i-1] != '1' && a[i+1] != '1') flag = false;
            }
            if (a[i] == '1') {
                if (a[i-1] == '1' || a[i+1] == '1') flag = false;
            }  //使用两个判断条件来判断字符串是否合法
        }
        if (flag == true) { //是就输出Yes
            cout<<"Yes";
            return 0;
        }
        cout<<"No"; //否则输出NO
        return 0;
    }

---

## 作者：鸿飞 (赞：0)

一道简单的字符串+逻辑判断题
## PART1：思路
读入字符串后一个一个扫过去。读到0时，判断左右两边是否都不为1（逻辑且）；读到1时，判断左右两边是否有1（逻辑或）即可，然后根据条件进行输出。
## PART2：注意事项
逻辑与的优先级是要高于逻辑或的优先级的。
## PART3：代码
```cpp
#include<iostream>
#include<string>
using namespace std;
int n;
string s;
int main(){
	cin >> n ;//输入
	cin >> s ;//输入+1
	for(int i=0;i<n;i++)
	{
		if(s[i]=='0'&&s[i-1]!='1'&&s[i+1]!='1')//判断
		{
			cout << "NO" ;
			return 0;
		}
		if(s[i]=='1'&&(s[i-1]=='1'||s[i+1]=='1'))//还是判断，不过要记得加括号
		{
			cout << "NO" ;
			return 0;
		}
	}
	cout << "YES" ;
	return 0; 
}

```


---

## 作者：Arghariza (赞：0)

先来介绍黑科技：string。

大家可能都知道string的用法，所以这里直奔主题。

1. ```s.find()```：

这是一个专属于string类的查找函数，如果找到了，则返回找到的字符串的坐标，如果没有找到，会返回```string::npos```，譬如：

```
string s = "123123123";
if (s.find("4") = string::npos) cout << "Not find!";
else cout << "Find!";
```

显然，上述程序输出的是```"Not find!"```

有了这个知识，我们再想一想：本题不符合的字符串有什么特征呢？

- 首先根据题目可以知道0的两旁没有1是不合法的，所以：

```
if (s[i] == 0 && s[i + 1] != 1 && s[i - 1] != 1) cout << "NO";
```

再进一步就变成了：不能有```"000"```的情况，也就是：

```
if (s.find("000") != string::npos) cout << "NO";
```

- 题目又说1的两旁不能有1，也就是不能存在：```011```和```110```。

在进一步就变成了不含有```"11"```：

```
if (s.find("11") != string::npos) cout << "NO";
```

综上所述，本题不符合字符串条件为：```s.find("11") != string::npos || s.find("000") != string::npos```

但是！

不要忘记把字符串两头写作0，也就是：

```
s = "0" + s;
s = s + "0";
```

所以我们的整体代码就出来了：

```
#include <string> 
#include <iostream>
using namespace std;

int n;
string s;

int main() {
    cin >> n >> s;//输入
    s = "0" + s;//头+0
	s = s + "0";//尾+0
    if (s.find("000") != string::npos || s.find("11") != string::npos) cout << "NO";
    else cout << "YES";
}
```

---

## 作者：yf最qhhh (赞：0)

首先分析题目：

从
```
一个为0的字符两旁没有1。
```
可以得出 $000$ 不合法。

从
```
一个为1的字符两旁还有1。
```
可以得出 $11$ 不合法。

所以这道题很简单：判断一个字符串中是否含有 $000$ 或者 $11$，如果含有就不合法。

最后呢这道题有个小坑，字符串最左边和最右边都要添上一个 $0$。

代码如下：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define rll register long long
using namespace std;
string s;
int main(){
	rll i,n;
	cin>>n>>s;//n本身是没有用的，但是需要输入。
	char a=s[0],b;
	s[0]='0';
	for(i=1;i<=s.length();i++){
		b=s[i];
		s[i]=a;
		a=b;
	}
	s[s.length()+1]='0';//给字符串两头加上0
	for(i=0;i<s.length();i++){
		if(s[i]=='0'){
			if(s[i+1]=='0'&&s[i+2]=='0')return cout<<"No",0;
		}else{
			if(s[i+1]=='1')return cout<<"No",0;
		}
	}//枚举两种不合法的情况，因为是从左到右所以枚举时也只需要判断右边的情况。
	cout<<"Yes";//出来了就说明合法，输出yes
	return 0;
}

```


---

## 作者：cq_loves_Capoo (赞：0)

题目只需要我们判断两个条件：    
1.一个为0的字符两旁没有1。   
2.一个为1的字符两旁还有1。   
如果符合这两种情况，输出No，否则输出Yes。   
那么我们就可以这样做：   
1.在程序后面加个0，防止最后出现特殊情况。   
2.特殊情况：先判断第一个数是否等于第二个数，如果符合，输出No，退出程序。   
3.根据题意循环，然后1和0的情况逐个判断，如果符合，输出No，退出程序。    
4.如果程序到最后还没结束，输出Yes。  
代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cmath>//头文件
using namespace std;
int n,s;
string st;
void no()//定个函数（因为输出No的次数较多，这样可以短些）
{
	printf("No");
	exit(0);
}
int main()
{
	scanf("%d",&n);
	cin>>st;  st+='0';//在程序后面加个0
	if(st[0]==st[1]) no();
	for(int i=1;i<n;i++)
	{
		if(st[i]=='1')
			if(st[i-1]=='1'||st[i+1]=='1') no();//如果符合1的情况，输出No，退出。
			else ;
		else 
			if(st[i-1]=='0'&&st[i+1]=='0') no();//判断0的情况，符合输No，并退出
	}
	printf("Yes");//如果程序没结束，输出Yes
	return 0;
}

```


---

