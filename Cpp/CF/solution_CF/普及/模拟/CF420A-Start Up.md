# Start Up

## 题目描述

Recently, a start up by two students of a state university of city F gained incredible popularity. Now it's time to start a new company. But what do we call it?

The market analysts came up with a very smart plan: the name of the company should be identical to its reflection in a mirror! In other words, if we write out the name of the company on a piece of paper in a line (horizontally, from left to right) with large English letters, then put this piece of paper in front of the mirror, then the reflection of the name in the mirror should perfectly match the line written on the piece of paper.

There are many suggestions for the company name, so coming up to the mirror with a piece of paper for each name wouldn't be sensible. The founders of the company decided to automatize this process. They asked you to write a program that can, given a word, determine whether the word is a 'mirror' word or not.

## 样例 #1

### 输入

```
AHA
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
Z
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
XO
```

### 输出

```
NO
```

# 题解

## 作者：我和鱼过不去 (赞：7)

### 注意  
符合题意的字符串，除了要是一个回文字符串，还必须由全部由 **轴对称字母** 组成。
  
### 思路
+ 判断是否含有非轴对称字母  
+ 判断是否为回文字符串  

以下是所有的轴对称字母：
```
AHIMOTUVWXY
```  

这里介绍一个string类型操作，可以快速反转字符串。
```cpp
string str;
reverse(str.begin(),str.end());
```
这样操作后的 $str$ 就是一个水平翻转后的字符串了。
然后就可以愉快的与原来的字符串比较啦~
  
~~其实我就是为了做回文串的题而学会的操作。~~ 


------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
string str;
int main()
{
    cin>>a;     //使用string处理字符串题目更方便
    for(int i=0;i<a.length();i++) //循环判断字符串中的每个字母是否为非轴对称字母
    {
        if(a[i]!='A'&&a[i]!='H'&&a[i]!='I'&&a[i]!='M'&&a[i]!='O'&&a[i]!='T'&&a[i]!='U'&&a[i]!='V'&&a[i]!='W'&&a[i]!='X'&&a[i]!='Y')
        {
            cout<<"NO"<<endl;
            return 0;
        }
    }
    str = a ;   //用另一个string存一下翻转的字符串
    reverse(str.begin(),str.end());
    if(a!=str)
    {
        cout<<"NO"<<endl;
        return 0;
    }
    cout<<"YES"<<endl;   //如果能跑到这里，就一定是符合要求的字符串
    return 0;
}

```


---

## 作者：Aw顿顿 (赞：5)

首先，如果有非轴对称的字符，直接输出 `NO`。

但是这还不够，要求一个字符串反过来一模一样，他一定要是一个回文串。

这里给出所有的轴对称字符：

~~~
AHIMOTUVWXY
~~~

其判断语句如下：

```cpp
for(int i=0;i<l;i++){
       if(a[i]!='A'&&a[i]!='H'&&a[i]!='I'&&a[i]!='M'&&a[i]!='O'&&a[i]!='T'&&a[i]!='U'&&a[i]!='V'&&a[i]!='W'&&a[i]!='X'&&a[i]!='Y')
            {puts("NO");return 0;}
    }
```
判断回文的代码如下：
```cpp
cin>>a;
l=a.size();
j=l-1;
while(i<j&&a[i]==a[j]){
	i++;j--;
}
if(i>=j)puts("YES");
else puts("NO");

```

这样就解决了两个问题，整体代码就不给出了。

AC 记录：https://www.luogu.com.cn/record/32997229

---

## 作者：andyli (赞：2)

只需判断每个字符是否为 `AHIMOTUVWXY` 中的一个，以及原字符串是否为回文串即可。前者可用二分。  

代码如下（[模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
#include <cstring>
#include <string>
constexpr int maxn = 100005;

const std::string c = "AHIMOTUVWXY";
char A[maxn];
int main() {
    io.read(A + 1);
    int n = strlen(A + 1);
    bool flag = true;
    for (int i = 1; i <= n && flag; i++)
        flag &= std::binary_search(c.begin(), c.end(), A[i]);
    for (int i = 1, j = n; i < j && flag; i++, j--)
        flag &= (A[i] == A[j]);
    writeln(flag ? "YES" : "NO");
    return 0;
}
```

其中 `binary_search` 函数定义在 `algorithm` 中，意为在有序区间内能否找到对应的字符。  

---

## 作者：songxiao (赞：2)

## 三个板块，应该是很 _详细_ 的。

### 主要思路：
- 遍历判断是否回文
- 用if判断字母
- 中途不符合要求，直接输出`NO`，然后退出程序
- 活到最后的就是符合要求的，输出`YES`


### 重点知识：
- 用s.length()计算字符串s的长度，**注意length后面有`()`**
- 循环次数：长度**除以二再加一**，不能漏掉最中间的字母
- 判断字母if中的**逻辑符号要用`&&`**，不是`||`
- 不要忘了**结束程序**：`return 0`


### AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;	//用string类型保存输入的字符串
    cin>>s;	//输入
    int l=s.length()-1;	//s.length()用来计算字符串的长度，注意后面有()，减一是因为要从0开始
    for(int i=0;i<l/2+1;i++)	//循环遍历，注意要+1，不能漏掉最中间的数
    {
    //注意，我分成了多个if，一是看着清楚，二是如果前面的不符后面就不要判断了
        if(s[i]!=s[l-i])	//是否回文
        {
            cout<<"NO";
            return 0;	//直接结束
        }
        if(s[i]!='A'&&s[i]!='H'&&s[i]!='I'&&s[i]!='M'&&s[i]!='O'&&s[i]!='T'&&s[i]!='U'&&s[i]!='V'&&s[i]!='W'&&s[i]!='X'&&s[i]!='Y')	
        {//判断字母是否符合要求
            cout<<"NO";
            return 0;//同上
        }
        if(s[l-i]!='A'&&s[l-i]!='H'&&s[l-i]!='I'&&s[l-i]!='M'&&s[l-i]!='O'&&s[l-i]!='T'&&s[l-i]!='U'&&s[l-i]!='V'&&s[l-i]!='W'&&s[l-i]!='X'&&s[l-i]!='Y')	
        {//判断与它回文的那个数
            cout<<"NO";
            return 0;//同上
        }
    } 
    //如果都符合才能到这儿
    cout<<"YES";
    return 0;	//结束程序
}
```


太简单不过瘾？再来些其他解法，解释少一点，因为内容是一样的：

```cpp
//压行版：
#include<iostream>
int main(){
    string s;cin>>s;int l=s.length()-1;	//定义、输入、计算长度
    for(int i=0;i<l/2+1;i++){//遍历
        if((s[i]!=s[l-i])||(s[i]!='A'&&s[i]!='H'&&s[i]!='I'&&s[i]!='M'&&s[i]!='O'&&s[i]!='T'&&s[i]!='U'&&s[i]!='V'&&s[i]!='W'&&s[i]!='X'&&s[i]!='Y')||(s[l-i]!='A'&&s[l-i]!='H'&&s[l-i]!='I'&&s[l-i]!='M'&&s[l-i]!='O'&&s[l-i]!='T'&&s[l-i]!='U'&&s[l-i]!='V'&&s[l-i]!='W'&&s[l-i]!='X'&&s[l-i]!='Y')){//判断
            std::cout<<"NO";return 0;//输出并结束程序
    	}
    }
    std::cout<<"YES";return 0;//输出并结束程序
}
```




---

## 作者：Arghariza (赞：1)

题目要求的字符串**必须**满足以下两个性质：

- 该字符串的所有字母都为“回文字母”（翻转过来和原字母一样的字母），例如$\mathtt{U,X,Y,A,H,I,T,O,W,V,M}$ 。
- 此字符串除了满足上述条件，还必须为回文串。

对于性质 $1$ ，我们只用把字符串从头到尾遍历一遍即可。而对于性质 $2$ ，我们需要判断回文串。

其实判断回文串有很多方法，但我个人觉得 $stack$ 蛮好用的（ $\mathtt\color{gold}STL$ 万岁！），对于前半段字符串，我们把每个字符**依次压入栈顶**；对于后半段字符（当然如果长度是奇数可以直接省略中间的字符），我们**遍历时将当前字符与栈顶元素一一配对，如果相同，则 $pop$ 掉栈顶元素，否则直接判断输出 $NO$** 。

如果到了最后，直接输出 $YES$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
string s;
stack<char> st;

int main() {
	getline(cin, s);
	n = s.length();
	for (int i = 0; i < n; i++) {
		if (s[i] != 'U' && s[i] != 'X' && s[i] != 'Y' && s[i] != 'A' && s[i] != 'H' && s[i] != 'I' && s[i] != 'T' && s[i] != 'O' && s[i] != 'W' && s[i] != 'V' && s[i] != 'M') {// 判断性质1
			cout << "NO";
			return 0;
		}
	}
   	// 判断性质2
	for (int i = 0; i < n / 2; i++) {// 将前半段压入栈
		st.push(s[i]);
	}
	for (int i = (n % 2) ? (n / 2 + 1) : (n / 2); i < n; i++) {// 从后半段开始匹配
		if (st.top() != s[i]) {// 如果栈顶元素与当前字符不等，直接判断NO
			cout << "NO";
			return 0;
		}
		st.pop();// pop掉栈顶元素
	}
	cout << "YES";// 留到最后的都是符合条件的题目
	return 0;
}
```

---

## 作者：动态WA (赞：1)

刚看到这题，想都没想就打了个判断回文串的代码，一看样例，原来还有条件：字母必须是轴对称的。

那么我们可以根据这个思路，一个一个读入字符，一发现不是轴对称的字母，直接输出“NO”，结束程序。这个判断的代码可以直接用if~~暴力~~实现。

在每个字符读取结束后，加入到字符串s中。等到所有字符读取完毕（即读取到换行符），就开始回文判断。创建两个变量，i指头，j指尾，每次循环判断s[i]是否等于s[j]，之后i++，j--，直到i>j

代码实现如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
int main(){
	char x;
	string s="";
	x=getchar();
	while (x!='\n'){
		if (x!='A'&&x!='H'&&x!='I'&&x!='M'&&x!='O'&&x!='T'&&x!='U'&&x!='V'&&x!='W'&&x!='X'&&x!='Y')
		{
			cout<<"NO";
			return 0;
		}
		s+=x;
		x=getchar();
	}
	for (int i=0,j=s.size()-1;i<=j;i++,j--)
		if (s[i]!=s[j]){
			cout<<"NO";
			return 0;
		}
	cout<<"YES";
	return 0;
}
```


---

## 作者：CobaltChloride (赞：1)

```
//简单判断即可,注意不仅要是回文串
#include<bits/stdc++.h>
using namespace std;
int i,ans=1;//初始化
string s;
int main(){
    cin>>s;
    for(i=0;i<=s.length()/2;i++){
        if(s[i]!=s[s.length()-i-1]||/*对称位置字符不同*/(s[i]!='W'&&s[i]!='T'&&s[i]!='Y'&&s[i]!='U'&&s[i]!='I'&&s[i]!='O'&&s[i]!='A'&&s[i]!='H'&&s[i]!='X'&&s[i]!='V'&&s[i]!='M'))/*不是对称字符*/ ans=0;
    }
    if(ans) cout<<"YES";
    else cout<<"NO";
    return 0;
}

```

---

## 作者：Eason_AC (赞：0)

## Content
给定一个长度为 $n$ 的字符串，求这个字符串整个反转过来后是否和原字符串一样。

**数据范围：$1\leqslant n\leqslant 10^5$。**
## Solution
众所周知，反转过来后一模一样的大写字母仅有以下这些：

$\texttt{AHIMOTUVWXY}$

所以这就相当于在判断回文串的基础上再判断是否是以上这些字符，直接开个左节点和右节点，往中间边遍历边判断即可。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

string a;

int main() {
	cin >> a;
	int len = a.size();
	for(int i = 0, j = len - 1; i <= j; ++i, --j)
		if(!(a[i] == a[j] && (a[i] == 'A' || a[i] == 'H' || a[i] == 'I' || a[i] == 'M' || a[i] == 'O' || a[i] == 'T' || a[i] == 'U' || a[i] == 'V' || a[i] == 'W' || a[i] == 'X' || a[i] == 'Y')))
			return printf("NO"), 0;
	return printf("YES"), 0;
}

```

---

## 作者：jijidawang (赞：0)

**注意！这题不仅仅是判回文串！而是把它翻转过来，也就是要求字母轴对称且对称轴垂直于底平面！**

## 题面简述

> 判断字符串翻过来后是不是等于原样。

## 算法分析

判回文串和轴对称字母即可。

轻易知：轴对称字母有：$\text{AHIMOTUVWXY}$ 这 $11$ 个，挨个判断是否在这 $11$ 个字母里即可。

判回文串用两个指针从左右往回走即可，一遍判回文一边判轴对称

代码：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
    string a;cin>>a;
    int len=a.length();
    for (int i=0;i+i<=len;i++)  //遍历一半，注意奇数长度用<=
    {
    	int j=len-i-1;          //一定要减一啊啊啊
        if (a[i]!='A'&&a[i]!='H'&&a[i]!='I'&&a[i]!='M'&&a[i]!='O'&&a[i]!='T'&&a[i]!='U'&&a[i]!='V'&&a[i]!='W'&&a[i]!='X'&&a[i]!='Y'){cout<<"NO";return 0;}          //判前半部分的轴对称 
        if (a[j]!='A'&&a[j]!='H'&&a[j]!='I'&&a[j]!='M'&&a[j]!='O'&&a[j]!='T'&&a[j]!='U'&&a[j]!='V'&&a[j]!='W'&&a[j]!='X'&&a[j]!='Y'){cout<<"NO";return 0;}          //判后半部分的轴对称 
		if (a[i]!=a[j]){cout<<"NO";return 0;} //判回文
    }
    cout<<"YES";                //一切满足
    return 0;
}
```

---

## 作者：damage (赞：0)

# 题意

给定一个字符串，判断其的镜像串是否与本身相同。

若相同则输出```YES```

否则输出```NO```

---

# 题解

## 注意是镜像串而不是回文串！

而题目要求字符串的镜像串是否与本身相同，所以构成这个字符串的字符一定是左右对称的字母。

题目给了字母的图片，肉眼辨别可知，以下字母不是左右对称字母：

```
BCDEFGJKLNPQRSZ
```

我用的方法是一个一个字符读入，使用字符数组存储，判断其是否为左右对称字符，如果不是就直接输出```NO```结束程序。

至于如何判断，直接把上面的字符串```BCDEFGJKLNPQRSZ```拷贝至一个```string```类型里，然后用内置的```find()```函数判断即可。

别忘了最后判断一下是否回文！

---

# 代码

```cpp
#include<stdio.h>
#include<ctype.h>
#include<string>
using namespace std;
int len;
char c,str[100010];
string no="BCDEFGJKLNPQRSZ"; //不是左右对称的字母集合
int main()
{
	c=getchar();
	for(;isupper(c);c=getchar()) //一直读入直到结束（即EOF或回车符等）
	{
		if(no.find(c)!=string::npos) //find()函数查找失败是会返回string::npos
		{
			printf("NO\n");
			return 0;
		}
		str[++len]=c; //存储字符串
	}
	for(register int i=0;i<=(len>>1);++i) //判断是否为回文串
	{
		if(str[i]!=str[len-i+1])
		{
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");
	return 0;
}
```

---

## 作者：monstersqwq (赞：0)

#### 题目大意：

给出一个字符串，判断它的镜像串是否和原串相同（每个字母也要左右颠倒过来）。是输出 YES，不是输出 NO（全部大写）。

先改变一下题意：判断一个字符串是否是回文串且所有字母左右颠倒都是原字母，因为英语字母中没有一个字母左右颠倒后变成另一个字母的情况，所以可以这样改变。

~~BFS（百度优先搜索）~~ 可知：左右颠倒为原字母的字母有：$\text{AHIMOTUVWXY}$ 这11个，挨个判断是否在这11个字母里即可。

回文串的判断很简单，只不过如果像我这样用 string 类型的话，记得数组下标从0开始哦。

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

int main()
{
	string a;
    cin>>a;
    int tmp=a.length()-1;//tmp为a的最后一位的下标
    for(int i=0;i<=tmp;i++)
    {
        if(a[i]=='A'||a[i]=='H'||a[i]=='I'||a[i]=='M'||a[i]=='O'||a[i]=='T'||a[i]=='U'||a[i]=='V'||a[i]=='W'||a[i]=='X'||a[i]=='Y') ;
        else
        {
            cout<<"NO"<<endl;
            return 0;
        }//判断左右颠倒相同
        if(a[i]!=a[tmp-i])
        {
            cout<<"NO"<<endl;
            return 0;
        }//判断回文
    }
    cout<<"YES"<<endl;
    return 0;
}
```


---

