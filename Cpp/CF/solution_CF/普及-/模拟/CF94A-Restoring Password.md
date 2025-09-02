# Restoring Password

## 题目描述

Igor K. always used to trust his favorite Kashpirovsky Antivirus. That is why he didn't hesitate to download the link one of his groupmates sent him via QIP Infinium. The link was said to contain "some real funny stuff about swine influenza". The antivirus had no objections and Igor K. run the flash application he had downloaded. Immediately his QIP Infinium said: "invalid login/password".

Igor K. entered the ISQ from his additional account and looked at the info of his main one. His name and surname changed to "H1N1" and "Infected" correspondingly, and the "Additional Information" field contained a strange-looking binary code $ 80 $ characters in length, consisting of zeroes and ones. "I've been hacked" — thought Igor K. and run the Internet Exploiter browser to quickly type his favourite search engine's address.

Soon he learned that it really was a virus that changed ISQ users' passwords. Fortunately, he soon found out that the binary code was actually the encrypted password where each group of $ 10 $ characters stood for one decimal digit. Accordingly, the original password consisted of $ 8 $ decimal digits.

Help Igor K. restore his ISQ account by the encrypted password and encryption specification.

## 样例 #1

### 输入

```
01001100100101100000010110001001011001000101100110010110100001011010100101101100
0100110000
0100110010
0101100000
0101100010
0101100100
0101100110
0101101000
0101101010
0101101100
0101101110
```

### 输出

```
12345678
```

## 样例 #2

### 输入

```
10101101111001000010100100011010101101110010110111011000100011011110010110001000
1001000010
1101111001
1001000110
1010110111
0010110111
1101001101
1011000001
1110010101
1011011000
0110001000
```

### 输出

```
30234919
```

# 题解

## 作者：Mysterious_Mini (赞：4)

这是本蒟蒻的第 $2$ 篇题解。
### 思路：
非常朴素的纯暴力（不用 $STL$）：用 $getline$ 进行整行读入，将代表 $0$～$9$ 的十个字符串分别存在 $S_0$，$S_1$，…… ，$S_9$ 中。利用三重循环把整个长字符串切成 $8$ 段，从 $S_0$ 枚举至 $S_9$，从前往后按位判断是否完全相同。一旦完全匹配，就跳出循环。
### 代码：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
string str, s[15];
int qwq, ans[15];
bool flag;
int main()
{
    //输入
    getline(cin, str);
    getline(cin, s[0]);
    getline(cin, s[1]);
    getline(cin, s[2]);
    getline(cin, s[3]);
    getline(cin, s[4]);
    getline(cin, s[5]);
    getline(cin, s[6]);
    getline(cin, s[7]);
    getline(cin, s[8]);
    getline(cin, s[9]);
  
    //循环
    for(int i = 0; i < 8; i++) //正在寻找第i个数字
    {
        for(int j = 0; j < 10; j++) //当前选定s[j]作为目标
        {
            for(int k = 0; k < 10; k++) //判断s[j]的第k位
            {
                if(s[j][k] != str[10 * i + k]) break;
                if(k == 9)
                {
                    flag = true;
                    qwq = j;
                }
            }
            if(flag == true)
            {
                ans[i] = qwq;
                break;
            }
        }
        flag = false;
    }
                                  
    //输出
    for(int i = 0; i < 8; i++)
        cout<<ans[i];
    cout<<endl;
    
    return 0;
}
```
[AC](https://www.luogu.com.cn/record/46693612)：放心，不会超时。这回是最优解的第六名！

求过+求赞QwQ

---

## 作者：CSP_Sept (赞：3)

看见又没有人用 `map` ，~~我又来水一波~~

## map 的基本用法
##### map 相当于一个下标可以是任何类型的数组。

1. `#include <map>` map 头文件。

1. `map <A,B> ds` 建立一个叫 `ds` 的，下标类型为 `A` ，元素类型为 `B` 的映射表。

1. `ds[t1]=t2` 把下标为 `t1` 对应的值改为 `t2` 。

1. `ds[A]` 访问下标为 `A` 的元素。
## 那么，如何做本题呢？
用 `map` 存储 $1-9$ 每个数字对应的密码，例如题中**样例#2**：

| 数字 | 对应的密码 |
| :-----------: | :-----------: |
| $0$ | `1001000010` |
| $1$ | `1101111001` |
| $2$ | `1001000110` |
| $3$ | `1010110111` |
| $4$ | `0010110111` |
| $5$ | `1101001101` |
| $6$ | `1011000001` |
| $7$ | `1110010101` |
| $8$ | `1011011000` |
| $9$ | `0110001000` |

在拆分密码串即可，拆分密码串使用 string 的 `.substr(pos,len)` 函数实现。用法：`s.substr(pos,len)`：截取字符串 $s$ 从第 $pos$ 个位置 $($位置从 $0$ 开始$)$开始的 $len$ 个字符，并返回为 string 类型。

有了这些知识，轻松得出代码：
## $Code:$
```cpp
#include <iostream>
#include <map>
#include <string>
using namespace std;
map <string,int> ds;
int main(){
    string s,a;
    cin>>s;
    for(int i=0;i<10;i++){
        cin>>a;
        ds[a]=i;//存储密码
    }
    for(int i=0;i<80;i+=10){
        string tmp=s.substr(i,10);//挨个截取字符串
        cout<<ds[tmp];
    }
    return 0;
}
```
## 结语
使用 map 可以轻松解决多种问题，对于其他题目，也要从多个角度思考。

希望本文可以让你掌握 map ！

---

## 作者：Jerrycyx (赞：1)

### 简要思路：
使用 ```cin.getline``` 函数读入第一行的原文，用 80 次循环来把它分割成 8 段，存储起来。

接下来再用 ```scanf``` 来输入每个数字所对应的字符串。

最后就可以两层循环来检查每一段字符串是否和某个数字所对应的字符串相等啦！

### 提示:
检查字符串相等可以用 ```cstring``` 头文件里的 ```strcmp``` 函数来检查,如果返回值为 0 就代表两个字符串相等。

## 完整AC代码：
```cpp
#include<cstdio>
#include<cstring>	// strcmp 需要调用 cstring 库 
#include<iostream>	// cin 需要调用 iostream 库
using namespace std;

struct sd{
	char s[20];		//使用结构体存储字符串，更加方便。
}num[20],st[20];	// num 代表每一个数字所代表的字符串， st 储存分段后得到的小字符串 
char str[100];		//第一行所输入的字符串 

int main()
{
	cin.getline(str,100);	//使用 cin.getline 函数读入一整行 
	for(int i=0;i<80;i++)
		st[i/10].s[i%10]=str[i];	//将字符串分段存储 
	for(int i=0;i<=9;i++)
		scanf("%s",num[i].s);		//输入每个数所对应的字符串 
	for(int i=0;i<8;i++)
		for(int j=0;j<=9;j++)				//两层循环检查字符串相等 
			if(strcmp(st[i].s,num[j].s)==0)	//用 strcmp 函数检查相等，返回0代表两个字符串完全相等 
				printf("%d",j);				//如果相等，则输出所对应的数 
	return 0;
}
```

---

## 作者：hensier (赞：1)

很多大佬都使用$STL$，包括$substr,map$等。本蒟蒻虽然浅显地知道一些用法，但是对于这种题目，我们不妨用最朴素的算法来做。（$C/C++$均可用）

```cpp
#include<cstdio>
char s[81],c[10][11],t[11];//定义字符数组
bool check(char a[],char b[])//check函数可以判断两个字符数组是否完全相同，当然可以直接调用string.h/cstring头文件的strcmp函数直接比较
{
    for(int i=0;a[i];i++)if(a[i]-b[i])return 0;
    return 1;
}
int main()
{
    gets(s);//gets函数可以读入整行
    for(int i=0;i<10;i++)gets(c[i]);//读入整行
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<10;j++)t[j]=s[i*10+j];//把t字符数组给赋值为s字符数组的第i段
        for(int j=0;j<10;j++)
        {
            if(check(t,c[j]))//从0到9逐一判断是否相等
            {
                printf("%d",j);//找到之后打印j并跳出当前循环
                break;
            }
        }
    }
}
```

---

## 作者：灵光一闪 (赞：1)

### 壮哉我大C++！

这题对C++来说就是一个``s.substr(i,10)``搞定的事~

就是截取一下，然后模拟嘛（代码是半年前的，懒得改了，凑合看吧）
```
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
int main()
{
	string S;
	cin>>S;
	string s[10],a[10];
	for(int i=0,j=0;i<80;i+=10,j++)
	{
		a[j]=S.substr(i,10);//十个十个截
// 		cout<<a[j]<<" ";
	}
	//return 0;
	for(int i=0;i<10;i++)
	{
		cin>>s[i];//然后输入
	}
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(s[j]==a[i])
			{
				cout<<j;//找到就输出
				continue;
			}
		}
	}
	return 0;
}
```
The End.

---

## 作者：xgwpp6710 (赞：0)

这题很水，就是把输入的匹配字符串放到 $s$ 里挨个匹配就行了。

数据很小，暴力就很舒服，不用优化。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,test[11];
int lxtsb[11];
bool match(string s0,int x)
{
    for(int i=0;i<10;i++)
    {
        if(s0[i]!=s[x*10-10+i]) return 0;//s[x*10-10+i]代表s的第x段的第i位
    }
    return 1;
}
int main()
{
    cin>>s;
    for(int i=0;i<=9;i++)
    {
        cin>>test[i];
        for(int j=1;j<=8;j++)
            if(match(test[i],j))
            {
                lxtsb[j]=i;//匹配，这里是存一下s的每一段是几号密码
            }
    }
    for(int i=1;i<=8;i++) cout<<lxtsb[i];
    return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
有一个 $80$ 位的 $01$ 字符串，由 $8$ 个长度为 $10$ 的 $01$ 字符串组成，每个小字符串分别对应一个数字。现在，给出这个字符串和 $0$ ~ $9$ 分别对应的 $01$ 字符串，请你破解出这个字符串对应的数字。
## Solution
这么好的题目为什么不用 $\texttt{map}$ 呢……

分别将 $0$ ~ $9$ 的字符串分别映射到对应的数字，然后看每 $10$ 位字符串分别对应那些数字，就可以直接用 $\texttt{map}$ 映射出来了。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#include <map>
using namespace std;

string s[17];
map<string, int> num;

int main() {
	for(int i = 0; i <= 10; ++i) {
		cin >> s[i];
		if(i)	num[s[i]] = i - 1;
	}
	int len = s[0].size(); 
	for(int i = 0; i < len; i += 10) {
		string tmp = "";
		for(int j = 0; j < 10; ++j)
			tmp += s[0][i + j];
		printf("%d", num[tmp]);
	}
	return 0;
}
```

---

## 作者：K2sen (赞：0)

### CF94A Restoring Password
[传送门](https://www.luogu.com.cn/problem/CF94A)

### 思路
先把串读进去

用map存一下当前这个串的编号

然后我们用string来把每一段从大串里边取出来就行了

string有一个好处就是用string加一个字符串就是在string后边添上

而且string可以比较大小，也很方便，但是时间有点慢

### code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define N 100010
#define M 100

using namespace std;
string ss;
string a;
map<string, int> ma;

int read() {
	int s = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

int main() {
	cin >> ss;
	for (int i = 0; i < 10; i++) {
		cin >> a;
		ma[a] = i;
	}
	for (int i = 0; i < 8; i++) {
		string sy;
		for (int j = 0; j < 10; j++)
			sy += ss[i * 10 + j];
		cout << ma[sy] ;
	}
}
```

---

## 作者：chenkaiwen (赞：0)

先了解一下题意，这一题是考点有两个：

1. 把一个长度为80的字符串分为8个长度为10的字符串
2. 把长度为10的字符串对应成数字

这一题中可以暴力分段（及用 $O(N)$ 的时间复杂度分段），所以分段不是很难，而把字符串对应成数字，建议大家可以用 $map$ ， $map$ 本质上是一棵红黑树在这里就不详细的讲解它的构造方法和技术原理，只简单说一下用法。 $map$ 的用法是
```cpp
map <下标的变量类型,需要储存的变量类型> 数组名;
```
那么我们只要把下标定义为 $string$ 型，需要储存的变量定义为 $int$ 型，就可以实现字符串和数字的对应。

其他细节上的内容我会在代码的注释中写出，这里就不详细的解释，代码如下：

[![](https://cdn.luogu.com.cn/upload/image_hosting/bhfc7ota.png)证明](https://www.luogu.com.cn/record/32193325)

```cpp
#include<bits/stdc++.h>
using namespace std;
string read() {//快读，加快输入且用起来方便 
	string w="";
	char c=getchar();
	while(c>'9'||c<'0') {
		c=getchar();
	}
	while(c<='9'&&c>='0') {
		w+=c;
		c=getchar();
	}
	return w;
}
map <string,int> a;//用map存起来方便一点 
string s;//用来存第一个输入（及长度为80）的那个字符串 
string Ans(string q) {
	string w="",ans="";
	for(int i=0; i<80; i++) {
		w+=s[i];
		if((i+1)%10==0&&i!=0) {//把s分成8段 
			ans+=(char)(a[w]+'0');//把数字转成字符并储存 
			w="";
		}
	}
	return ans;//返回答案 
}
int main() {
	ios::sync_with_stdio(0);
	s=read();
	for(int i=0; i<=9; i++) {
		a[read()]=i;//输入+存储 
	}
	cout<<Ans(s)<<endl;//输出答案 
	return 0;
}




```
### 感谢观看，请勿抄袭

---

