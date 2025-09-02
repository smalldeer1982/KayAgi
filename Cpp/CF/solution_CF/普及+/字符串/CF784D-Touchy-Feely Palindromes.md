# Touchy-Feely Palindromes

## 样例 #1

### 输入

```
373
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
121
```

### 输出

```
No
```

## 样例 #3

### 输入

```
436
```

### 输出

```
Yes
```

# 题解

## 作者：Na2_CuCl4 (赞：5)

首先我先想到了一些失败的思路：
- 制作二维数组（可行是可行，但是各种坑还是层出不穷，不建议）。
- $bool$ 数组记录盲文（同上，难执行）。
- 类似普通回文数，用 $while$( )拆（不可行）。

最后，我总结出了一种方法：



**直接用 `for( )` 拆啊！！！**
 
做法：先定义 $fz$（反转）数组，再 $for$ 循环让第 $i$ 个与第 $l$( $l$ 为数的长度）$ -i-1$ 个数对比。

代码：

`char fz[13]={'8','x','x','3','6','9','4','7','0','5'};`

| $0$ | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ | $8$ | $9$ |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| $8$ | $x$ | $x$ | $3$ | $6$ | $9$ | $4$ | $7$ | $0$ | $5$|


```cpp
int main(){
	string n;//string优于char[]，故用string
	cin>>n;
	int l=n.length();
	for(int i=0;i<l/2+1;i++){
		if(n[l-i-1]!=fz[n[i]-'0']){
			cout<<"No";
			return 0;//如果发现不符合立即结束
		}
	}
	cout<<"YES";//若没有不符合部分输出yes
	return 0;
}

```

附：完整代码 **禁止抄袭！！！**
```cpp
#include<iostream>
#include<cstring>
using namespace std;
char fz[13]={'8','x','x','3','6','9','4','7','0','5'};
int main(){
	string n;
	cin>>n;
	int l=n.length();
	for(int i=0;i<l/2+1;i++){
		if(n[l-i-1]!=fz[n[i]-'0']){
			cout<<"No";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}

```

管理大大求过·w·

---

## 作者：政凯 (赞：3)

  这道题，有求出一个数，在盲文中是否回文数。
  
  在阿拉伯数字里，左右对称的数是回文数：左1对右1，左2对右2，左3对右3……

在盲文中，左3对右3，左4对右6，左5对右9，左7对右7，左8对右0，左6对右4，左9对右5，左0对右8。因此，我们可以打个二维表， 将能成回文数的赋值1，如：f[3][3]=1……

打完二维数组后，就可以判断，这个数左右是否对称，是否是回文数。
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int l,a[10000+5],f[100+5][100+5];
string st;
int main()
{
	cin>>st;l=st.size();
	for (int i=0;i<st.size();i++)
	  a[i+1]=st[i]-48;
	f[3][3]=1;f[4][6]=1;f[5][9]=1;f[7][7]=1;f[8][0]=1;
	f[3][3]=1;f[6][4]=1;f[9][5]=1;f[7][7]=1;f[0][8]=1;
	for (int i=1;i<=l/2+1;i++)
	  if (f[a[i]][a[l-i+1]]==0) {cout<<"No";return 0;}
	cout<<"Yes";
	return 0;
}
```


---

## 作者：qss_ (赞：2)

本人不才，有一种好理解的方法。

Q：对于正常的字符串我们怎么判断回文呢？

A：当然是先倒着把字符串抄一遍再比较啦。

举个例子：

```
abcba倒着看还是abcba，所以是回文；
但是xyz倒着看是zyx，所以不是回文。
```

那我们也把盲文字符串翻转就行了。

Q：但是盲文翻转和普通字符串翻转不一样啊？

A：没事，对应一下就行了。

看对照表：

![](https://cdn.luogu.org/upload/pic/13921.png)

1和2翻转后啥也不是（对应不上），所以只要有1和2都不是回文字符串。

3还是3；7还是7；

4和6相互对应；5和9相互对应；8和0相互对应。

只要按照这个先把字符串翻转后对应的字符串写出来再比较就行了。

再举个例子：

```
我们看436
436对应634，4->6, 3->3, 6->4
然后第一个正着与第二个倒着比较：
4 == 4
3 == 3
6 == 6
所以是回文

再看574
574对应976，5->9, 7->7, 4->6
然后第一个正着与第二个倒着比较：
5 != 6
7 == 7
4 != 9
所以不是回文
```

上代码：

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

char s[15], rev_s[15];// 原字符串和翻转后的字符串

int main()
{
	scanf("%s", s);
	for (int i = 0; i < strlen(s); i++)// 先对应一下
	{
		if (s[i] == '1' || s[i] == '2')
		{
			printf("No");// 1和2没戏
			return 0;
		}
		if (s[i] == '3') rev_s[i] = '3';// 按照上面对应
		if (s[i] == '4') rev_s[i] = '6';
		if (s[i] == '5') rev_s[i] = '9';
		if (s[i] == '6') rev_s[i] = '4';
		if (s[i] == '7') rev_s[i] = '7';
		if (s[i] == '8') rev_s[i] = '0';
		if (s[i] == '9') rev_s[i] = '5';
		if (s[i] == '0') rev_s[i] = '8';
	}
	for (int i = 0; i < strlen(s); i++)
	{
		if (s[i] != rev_s[strlen(s)-i-1])// 逆序比较
		{
			printf("No");
			return 0;
		}
	}
	printf("Yes");// 最后才是yes
	return 0;
}
```

~~人生中第1篇题解 求通过qwq~~

---

## 作者：B_lhx (赞：1)

[CF784D Touchy-Feely Palindromes](https://www.luogu.com.cn/problem/CF784D)
========
思路：模拟
------
```
#include <bits/stdc++.h>
using namespace std;
int main(){
string s;//定义字符串
cin>>s;//输入
int n=s.size();//取长度
for(int i = 0;i<n;i++){//模拟
	if(s[i]=='1'||s[i]=='2'){//1和2没有对称的
		cout<<"No";//不行
		return 0;
	}
	if(s[i]=='3'&&s[n-i-1]!='3'){//如果对面不对称
		cout<<"No";//不行
		return 0;
	}
	if(s[i]=='4'&&s[n-i-1]!='6'){//如果对面不对称
		cout<<"No";//不行
		return 0;
	}
	if(s[i]=='6'&&s[n-i-1]!='4'){//如果对面不对称
		cout<<"No";//不行
		return 0;
	}
	if(s[i]=='5'&&s[n-i-1]!='9'){//如果对面不对称
		cout<<"No";//不行
		return 0;
	}
	if(s[i]=='0'&&s[n-i-1]!='8'){//如果对面不对称
		cout<<"No";//不行
		return 0;
	}
	if(s[i]=='9'&&s[n-i-1]!='5'){//如果对面不对称
		cout<<"No";//不行
		return 0;
	}
	if(s[i]=='8'&&s[n-i-1]!='0'){//如果对面不对称
		cout<<"No";//不行
		return 0;
	}
}
cout<<"Yes";//如果还能运行下来就是
    return 0;
}
```


---

## 作者：MeowScore (赞：0)

## 题目大意：

给出一个数字串以及数字转化成盲文的规则，判断这个数字串转化成盲文后是否回文。


------------
## 解决方法

采用非常暴力的手段即可。要判断回文，我们想象把这个字符串首尾对折一下，重合的两个字符我们称它们处于“对应位置”。我们来对照表格看一下对应位置的字符要满足什么条件？

![](https://cdn.luogu.com.cn/upload/image_hosting/tsdnknrv.png)

很显然，若该串回文，对于任意一个字符，其对应位置的字符分以下几种情况：

$1.$ 当前字符为 $4$，则它对应位置的字符为 $6$。

$2.$ 当前字符为 $6$，则它对应位置的字符为 $4$。

$3.$ 当前字符为 $5$，则它对应位置的字符为 $9$。

$4.$ 当前字符为 $9$，则它对应位置的字符为 $5$。

$5.$ 当前字符为 $8$，则它对应位置的字符为 $0$。

$6.$ 当前字符为 $0$，则它对应位置的字符为 $8$。

$7.$ 当前字符为 $3$，则它对应位置的字符为 $3$。

$8.$ 当前字符为 $7$，则它对应位置的字符为 $7$。

其余情况皆不满足。我们只用跑一下该字符串的 $0$ 到 $len/2$ 位置，判断每个字符和它对应位置的字符是不是满足上述条件的一种即可。

特别地，若该字符串长度为奇数，则它的中间位置字符只能是$3$ 或 $7$。


------------


## 上代码

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	char a[500];
	gets(a);
	int len=strlen(a);
	if(len%2&&a[len/2]!='3'&&a[len/2]!='7'){//当长度为奇数，判断中间位置的字符 
		cout<<"No";
		return 0;
	}
	for(int i=0;i<=len/2;i++){
		int p=len-1-i;//这样a[p]是a[i]对应位置的字符  
		if((a[i]=='3'&&a[p]=='3')||(a[i]=='7'&&a[p]=='7')||
			(a[i]=='4'&&a[p]=='6')||(a[i]=='6'&&a[p]=='4')||
			(a[i]=='5'&&a[p]=='9')||(a[i]=='9'&&a[p]=='5')||
			(a[i]=='8'&&a[p]=='0')||(a[i]=='0'&&a[p]=='8'))//满足任意一种条件，该位置判定成立 
			continue;
		cout<<"No";//否则立刻判定为错误 
		return 0;
	}
	cout<<"Yes";
	return 0;
}
```


---

## 作者：joy2010WonderMaker (赞：0)

本题是一道字符串模拟题，具体如下。

一个字符串，如果这一位为 $x$，则有下面的表格。

| **数字** | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |:----------: | 
| **对称后对应数字** | ？ | ？ | 3 | 6 | 9 | 4 | 7 | 0 | 5 | 8 |

这样，问题就被简化了，我们只要判断这一位和将这个数翻转后同样位置上的数字是否对应即可。

**给一组样例：6644**

6对应4，4对应6，所以输出 `Yes`。

**AC** **Code**

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    string n;
    cin>>n;
    for(int i=0;i<n.size()/2+1;i++){//只用循环到n的长度除以2加1的原因是因为把数组反过来对应的位置就是n的长度减1减i
        if(n[i]=='1'||n[i]=='2'){//有1和2肯定不行
            cout<<"No"<<endl;
            return 0;
        }
        if(n[i]=='3'||n[i]=='7'){//开始判断对应数字
            if(n[n.size()-1-i]!=n[i]){
                cout<<"No"<<endl;
                return 0;
            }
        }
        if(n[i]=='4'){
            if(n[n.size()-1-i]!='6'){
                cout<<"No"<<endl;
                return 0;
            }
        }
        if(n[i]=='5'){
            if(n[n.size()-1-i]!='9'){
                cout<<"No"<<endl;
                return 0;
            }
        }
        if(n[i]=='6'){
            if(n[n.size()-1-i]!='4'){
                cout<<"No"<<endl;
                return 0;
            }
        }
        if(n[i]=='8'){
            if(n[n.size()-1-i]!='0'){
                cout<<"No"<<endl;
                return 0;
            }
        }
        if(n[i]=='9'){
            if(n[n.size()-1-i]!='5'){
                cout<<"No"<<endl;
                return 0;
            }
        }
        if(n[i]=='0'){
            if(n[n.size()-1-i]!='8'){
                cout<<"No"<<endl;
                return 0;
            }
        }
    }
    cout<<"Yes"<<endl;//如果前面没有结束，那就输出Yes
    return 0;
}
```


---

## 作者：ZBAA_MKC (赞：0)

### 思路分析

首先这题肯定不能用二维字符数组来存储盲文，因为这样太麻烦，而且容易出错。

正解：根据盲文对照表分别找出每一个盲文数字对应的回文盲文数字，然后其余部分按照常规的回文判定就可以啦。


[AC链接](https://www.luogu.com.cn/record/48328556)

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int chart[10] = {8, -1, -1, 3, 6, 9, 4, 7, 0, 5}; //记录与哪个数是回文的,-1代表没有对应的数 
char c[15]; //个人习惯，不用string 
int main()
{
    scanf("%s", c);	//输入 
    int len = strlen(c); //预先计算长度
    int ter = len / 2 + 1; 
	for (int i = 0; i < ter; i++) //枚举到len/2+1 
	{
		if (len % 2 == 0 && (c[i] == '1' || c[i] == '2')) //特判 
		{ //长度为偶数且扫到了1或2 
			cout << "No"; //那直接输出No 
			return 0;
		}
		if (int(chart[c[i] - '0']) != c[len - i - 1] - '0') //如果哪一位不回文 
		{
			cout << "No"; //输出No
			return 0;
		}
	} 
	cout << "Yes"; //输出Yes 
	return 0;
}
```



---

## 作者：小坦克 (赞：0)

#### [CF784D Touchy-Feely Palindromes](https://www.luogu.com.cn/problem/CF784D)

------------
### 一、理解题意：

原图对照：

![](https://cdn.luogu.org/upload/pic/13921.png)

- **分析**：

数字对应的**回文数**：
- 0 & 8
- 5 & 9
- 4 & 6
- 7 & 7
- 1 & 2 **先放一边**

-------------
### 二、探究做法：
- 首先我想到的就是模拟！！！

$Q:$既然思路已经出来了，怎么实现呢？

$A:$

1. 定义一个数组。

```cpp
char m[13]={'8','a','a','3','6','9','4','7','0','5'};
```
2. 用 `for` 作对比。

- 详细见代码
------------
### 三、部分代码：

```cpp
for(int i=1;i<=l/2+1;i++){ //
		if(n[l-i]!=m[n[i-1]-'0']){
			cout<<"No"; //如果发现不符合立即结束
			return 0;
		}
	}
cout<<"YES"; //若没有不符合部分输出yes
```

-----------
完结撒花！

---

## 作者：FuriousC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF784D)

# 前置芝士：
回文串的定义：“回文串”是一个正读和反读都一样的字符串

看不懂？没事，举个栗子：

$123$翻转后是$321$，所以它不是回文串

$121$翻转后是$121$，所以它是回文串

# 思路：
对照盲文数字对照表，可以得出：

1、3翻转后仍是3，7反转后也仍是7

2、4翻转后是6

3、5翻转后是9

4、8翻转后是0

5、1和2翻转后不表示任何数字

（详细见代码注释）

# 废话不多说，上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[15],s1[15];//s表示原来的字符串，s1表示翻转后的字符串
int main(){
    cin>>s;//可以直接输入或输出一个只含小写字母或数字的字符串 
    for(int i=0;i<strlen(s);i++){//strlen(s)表示s这个字符串的长度 
        if(s[i]=='3'){
            s1[i]='3';
        }//3变3 
        if(s[i]=='7'){
            s1[i]='7';
        }//7变7 
        if(s[i]=='4'){
            s1[i]='6';
        }//4变6 
        if(s[i]=='6'){
            s1[i]='4';
        }//6变4 
        if(s[i]=='5'){
            s1[i]='9';
        }//5变9 
        if(s[i]=='9'){
            s1[i]='5';
        }//9变5 
        if(s[i]=='8'){
            s1[i]='0';
        }//8变0 
        if(s[i]=='0'){
            s1[i]='8';
        }//0变8 
    }
    for(int i=0;i<strlen(s);i++){
        if(s[i]=='1'||s[i]=='2'||s[i]!=s1[strlen(s)-i-1]){//判断是不是1或2或符不符合回文串的性质 
            cout<<"No"<<endl;//只要有一个不符合就输出No 
            return 0;
        }
    }
    cout<<"Yes"<<endl;//否则输出Yes 
    return 0;//好习惯 
}
```
代码看完了，你学废了吗？

---

## 作者：PC_DOS (赞：0)

愚人节题目，输入一个字符串，把它转换成盲文判断一下是不是回文...

注意，翻转的时候要把盲文字符整体翻转。

盲文数字对照表:

![](https://cdn.luogu.com.cn/upload/pic/13921.png)

所以就有代码了:
```
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
using namespace std; //头文件和命名空间
bool isBraillePalindrome(string sTest){ //判断一个数(字符串)是不是盲文回文
							 //0, 1 , 2 , 3, 4, 5, 6, 7, 8, 9
	int arrBrailleNums[10] = { 8, -1, -1, 3, 6, 9, 4, 7, 0, 5 }; //存放一个数和与它对应的翻转后的盲文数字的数组，-1表示翻转后和它对应的盲文数不存在
    int i; //循环变量
	for (i = 0; i <= sTest.length() - 1; ++i){ //判断是不是回文
		if (arrBrailleNums[sTest[i] - '0'] != sTest[sTest.length() - 1 - i]-'0') //如果发现不能对应
			return false; //返回false
	}
	return true; //否则最终返回true
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	string sInput; //存放输入的字符串
	getline(cin, sInput); //读入
	if (isBraillePalindrome(sInput)) //判断是不是盲文回文
		cout << "YES"; //是
	else
		cout << "NO"; //否
	return 0; //结束
}
```

---

