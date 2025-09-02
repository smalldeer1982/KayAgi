# Tavas and Nafas

## 题目描述

Today Tavas got his test result as an integer score and he wants to share it with his girlfriend, Nafas.

His phone operating system is Tavdroid, and its keyboard doesn't have any digits! He wants to share his score with Nafas via text, so he has no choice but to send this number using words.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF535A/b4f47a55f97fcd02924cac5270349f0616c61519.png)He ate coffee mix without water again, so right now he's really messed up and can't think.

Your task is to help him by telling him what to type.

## 说明/提示

You can find all you need to know about English numerals in [http://en.wikipedia.org/wiki/English\_numerals](http://en.wikipedia.org/wiki/English_numerals) .

## 样例 #1

### 输入

```
6
```

### 输出

```
six
```

## 样例 #2

### 输入

```
99
```

### 输出

```
ninety-nine
```

## 样例 #3

### 输入

```
20
```

### 输出

```
twenty
```

# 题解

## 作者：李至擎 (赞：3)

[点我看题](https://www.luogu.com.cn/problem/CF535A)

题意：输入一个 $0$ （题面上是 $1$ ，但是数据出现了 $0$ ）至 $99$ 的整数，转化成英文的写法。

思路&方法：因为 $0 \le n \le 99$ ，数据范围很小，所以我们根本不需要考虑太多，直接打表就可以通过本题。

细节：

- 当 $n$ 为 $0$ 时，要输出 $zero$ 。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int num;
char a[105][25]={"zero","one","two","three","four","five","six","seven","eight","nine",
"ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen",
"nineteen","twenty","twenty-one","twenty-two","twenty-three","twenty-four","twenty-five",
"twenty-six","twenty-seven","twenty-eight","twenty-nine","thirty","thirty-one","thirty-two",
"thirty-three","thirty-four","thirty-five","thirty-six","thirty-seven","thirty-eight",
"thirty-nine","forty","forty-one","forty-two","forty-three","forty-four","forty-five",
"forty-six","forty-seven","forty-eight","forty-nine","fifty","fifty-one","fifty-two",
"fifty-three","fifty-four","fifty-five","fifty-six","fifty-seven","fifty-eight",
"fifty-nine","sixty","sixty-one","sixty-two","sixty-three","sixty-four","sixty-five",
"sixty-six","sixty-seven","sixty-eight","sixty-nine","seventy","seventy-one","seventy-two",
"seventy-three","seventy-four","seventy-five","seventy-six","seventy-seven","seventy-eight",
"seventy-nine","eighty","eighty-one","eighty-two","eighty-three","eighty-four",
"eighty-five","eighty-six","eighty-seven","eighty-eight","eighty-nine","ninety",
"ninety-one","ninety-two","ninety-three","ninety-four","ninety-five","ninety-six",
"ninety-seven","ninety-eight","ninety-nine"};//一个0~99的表
int main()
{
	cin>>num;
	cout<<a[num];//输出结果 
    return 0;
}
```

---

## 作者：Eason_AC (赞：2)

## Content
请输出整数 $s$ 的英文写法。

**数据范围：$0\leqslant s\leqslant 99$。**
## Solution
直接对应打表即可。

- 当 $0\leqslant s\leqslant 19$，直接特判对应输出即可。
- 当 $20\leqslant s\leqslant 99$，碰到整十数就先输出对应的英文单词，如果后面还有数，先加上一个连字符，再输出个位上的数字。

建议做完这题目之后再去做做 [P1617](https://www.luogu.com.cn/problem/P1617)。

## Code
```cpp
const string num[11] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const string ty[11] = {"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
const string teen[21] = {"", "", "", "", "", "", "", "", "", "", "", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
int a[5], n, cnt;

int main() {
	scanf("%d", &n);
	int tmp = n;
	while(tmp) {
		a[++cnt] = tmp % 10;
		tmp /= 10;
	}
	int teens = a[2] * 10 + a[1];
	if(cnt == 2) {
		if(teens >= 11 && teens <= 19)
			cout << teen[teens];
		else if(!a[1]) {
			if(a[2] == 1)	cout << ty[1];
			else	cout << ty[a[2]];
		}
		else
			cout << ty[a[2]] << '-' << num[a[1]];
	} else
		cout << num[a[1]];
	return 0;
}
```

---

## 作者：cq_loves_Capoo (赞：1)

这一题是一题大水题，只要不粗心大意（不要像这个人一样），那么还是很好过的。   
   
首先给出一种代码量较短的方法：   
   
存好 $0$ 至$ 9$ ，$10$ 到 $20$ ，还有整十数的英文，然后判断，如果小于二十，就直接输出答案，否则就输出整十数，如果该数不是整十数，则输出它的个位。
  
第一种方法的代码：   
   
```
#include<bits/stdc++.h>
#define endl '\n'
#pragma GCC optimize(3)

using namespace std;
int n;
string a[15] = {"zero" , "one" , "two" , "three" , "four" , "five" , "six" , "seven" , "eight" , "nine"};//0到9的
string b[15] = {"ten" , "eleven" , "twelve" , "thirteen" , "fourteen" , "fifteen" , "sixteen" , "seventeen" , "eighteen" , "nineteen"};//10到19的
string c[15] = {"twenty" , "thirty" , "forty" , "fifty" , "sixty" , "seventy" , "eighty" , "ninety"};//整十数的
signed main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	if (n < 10) cout << a[n];//如果小于10，直接输出个位。
	else 
	{
		if (n < 20) cout << b[n-10];小于二十则输出10到19的
		else 
		{
			cout << c[n/10-2];//输出十位
			if (n%10 != 0)/*如果个位不是0*/ cout << '-' << a[n%10];//输出个位
		}
	}
}
```
  
第二种方法是无脑的方法，直接 $1$ 到 $99$ 打表，个人不太建议用这种方法。       

代码是真的长，不贴了，给个一到九十九的表吧/kk    
   
```
one two three four five six seven eight nine ten eleven twelve thirteen fourteen
 fifteen sixteen seventeen eighteen nineteen twentytwenty-one twenty-two twenty-
three twenty-four twenty-five twenty-six twenty-seven twenty-eight twenty-nine t
hirtythirty-one thirty-two thirty-three thirty-four thirty-five thirty-six thirt
y-seven thirty-eight thirty-nine fortyforty-one forty-two forty-three forty-four
 forty-five forty-six forty-seven forty-eight forty-nine fiftyfifty-one fifty-tw
o fifty-three fifty-four fifty-five fifty-six fifty-seven fifty-eight fifty-nine
 sixtysixty-one sixty-two sixty-three sixty-four sixty-five sixty-six sixty-seve
n sixty-eight sixty-nine seventyseventy-one seventy-two seventy-three seventy-fo
ur seventy-five seventy-six seventy-seven seventy-eight seventy-nine eightyeight
y-one eighty-two eighty-three eighty-four eighty-five eighty-six eighty-seven ei
ghty-eight eighty-nine ninetyninety-one ninety-two ninety-three ninety-four nine
ty-five ninety-six ninety-seven ninety-eight ninety-nine
```

---

## 作者：开始新的记忆 (赞：1)

题目大意：给你一个小于一百的自然数，输出它的英文

除了在11-19之间的数的形式不同，其余都可找出规律


```cpp
#include<cstdio>
#include<iostream>
#include<string>
using namespace std;
int main()
{
    string a[20]={"zero","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
    string b[10]={" ","fucxk","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
    int c;
    cin>>c;
    if(c<=19)
    {
        cout<<a[c];
    }
    else if(c%10==0) cout<<b[c/10];
    else
    {
        cout<<b[c/10]<<"-"<<a[c%10];
    }
    return 0;
}
```


---

## 作者：a1ioua (赞：0)

这道题 ~~并不是黄题，而是红题。~~ 只要细心一点，就可以AC的。

也没什么可说的了，给出正解：
```cpp
#include <bits/stdc++.h>
using namespace std;
string g[11] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};零到九
string s[11] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};十到十九
string s1[11] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};整十数
int main() {
    int n;
    cin >> n;
    if (n < 10) cout << g[n];输出〇到九
    else if (n < 20) cout << s[n - 10];输出十到十九
    else {
        cout << s1[n / 10 - 2];输出前半部分
        if (n % 10 != 0) cout << '-' << g[n % 10];如果末尾不是〇，输出后半部分
    }输出二十到九十九
    return 0;
}
```
也可以打表，改一下代码就可以了。

---

## 作者：Arghariza (赞：0)

吐槽一下：题面说的是 $1-99$ ，结果 $\mathtt{codeforces}$ 上第 $9$ 个点是 $0$ ......

然后就顺理成章地 $\mathtt\color{red}WA$ 了。

![](https://i.loli.net/2020/11/24/8GgEeCAk3dncwWs.png)

所以首先我们得特判一下 $n$ 是否等于 $0$ 。

如果不是的话打两个表：

```cpp
string num1[11] = {"qwq", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
string num2[11] = {"qwq", "qwq", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
```

$num1$ 代表个位数字，$num2$ 代表其十位数字（因为十位是 $1$ 的时候还要特判所以没写进去）。

如果 $n$ 是一位数的话直接输出 $num1_n$ 即可，否则需要像上面说的一样特判 $n$ 的十位是否为 $1$ 。如果是的话就只能挨个输出 $ten,\,eleven,\,twelve,\,...$ ；如果不是的话直接输出 $num2_{\left\lfloor\frac{n}{10}\right\rfloor}-num1_{n\mod 10}$ 即可。（当然还需要判断一下个位数是否为 $0$ ，如果是的话就不用输出了）。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
string num1[11] = {"qwq", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
string num2[11] = {"qwq", "qwq", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

int main() {
	cin >> n;
	if (n == 0) cout << "zero";
	else if (n < 10) cout << num1[n];
	else {
		if (n / 10 == 1) {
			switch(n % 10) {
				case 0:
					cout << "ten";
					break;
				case 1:
					cout << "eleven";
					break;
				case 2:
					cout << "twelve";
					break;
				case 3:
					cout << "thirteen";
					break;
				case 4:
					cout << "fourteen";
					break;
				case 5:
					cout << "fifteen";
					break;
				case 6:
					cout << "sixteen";
					break;
				case 7:
					cout << "seventeen";
					break;
				case 8:
					cout << "eighteen";
					break;
				default:
					cout << "nineteen";
			}
		} else {
			cout << num2[n / 10];
			if (n % 10) {
				cout << "-" << num1[n % 10];
			}
		}
	}
	return 0;
}
```

---

## 作者：九月_014 (赞：0)


一道难度偏下的模拟题，码量还算是可以的，

和大家分享一下我的思路：

根据字符串的长度进行判断。

在1--19的时候，我们要进行特判，分别输出。

而在20--99的时候呢，我们就可以采用“xx—xx” 的方式。注意在个位是0的时候要不输出‘-’；

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

char a[5];
int l;
int main()
{
	cin>>a;
	l=strlen(a);
	if(l==1)//只有一位
	{
		if(a[0]=='0') cout<<"zero";//一定要判断，这个地方翻译有点错误
		if(a[0]=='1') cout<<"one";
		if(a[0]=='2') cout<<"two";
		if(a[0]=='3') cout<<"three";
		if(a[0]=='4') cout<<"four";
		if(a[0]=='5') cout<<"five";
		if(a[0]=='6') cout<<"six";
		if(a[0]=='7') cout<<"seven";
		if(a[0]=='8') cout<<"eight";
		if(a[0]=='9') cout<<"nine";
	}
	if(l==2&&a[0]=='1')//两位数且十位为1
	{
		if(a[1]=='0') cout<<"ten";
		if(a[1]=='1') cout<<"eleven";
		if(a[1]=='2') cout<<"twelve";
		if(a[1]=='3') cout<<"thirteen";
		if(a[1]=='4') cout<<"fourteen";
		if(a[1]=='5') cout<<"fifteen";
		if(a[1]=='6') cout<<"sixteen";
		if(a[1]=='7') cout<<"seventeen";
		if(a[1]=='8') cout<<"eighteen";
		if(a[1]=='9') cout<<"nineteen";
	}
	if(l==2&&a[0]!='1')//首位不为1，且是两位数
	{
		if(a[0]=='2') cout<<"twenty";
		if(a[0]=='3') cout<<"thirty";
		if(a[0]=='4') cout<<"forty";
		if(a[0]=='5') cout<<"fifty";
		if(a[0]=='6') cout<<"sixty";
		if(a[0]=='7') cout<<"seventy";
		if(a[0]=='8') cout<<"eighty";
		if(a[0]=='9') cout<<"ninety";
		if(a[1]!='0') //个位有数才输出‘—’没数就算了，不进入判断
		{
			cout<<"-";
			if(a[1]=='1') cout<<"one";
			if(a[1]=='2') cout<<"two";
			if(a[1]=='3') cout<<"three";
			if(a[1]=='4') cout<<"four";
			if(a[1]=='5') cout<<"five";
			if(a[1]=='6') cout<<"six";
			if(a[1]=='7') cout<<"seven";
			if(a[1]=='8') cout<<"eight";
			if(a[1]=='9') cout<<"nine";
		}	
	}
}
```



---

## 作者：ZolaWatle (赞：0)

### CF535A 题解

其实这道题作为一道黄题已经极水无比了。

本题的升级版请戳：[P1617 爱与愁的一千个伤心的理由](https://www.luogu.com.cn/problem/P1617)

思路：打表即可，要注意判断一下几种特殊情况：

- **n==0 cout<<"zero"** 本人第一次提交就是没考虑这个挂的

- **n在11和19之间** 学过英语的都知道，这几个词是独立的

- **n为两位数但是n的个位是0** 这个时候就不需要输出个位了（例如"twenty-zero"就显得很沙雕）

吼了，考虑了这些情况，聪明的你们还会错吗？

### Code:

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define re register int
using namespace std;

int n;
string tp[20]={"","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
string gw[20]={"zero"/*极坑无比*/,"one","two","three","four","five","six","seven","eight","nine","ten"}; 
string sw[20]={"","","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
//前三行打表不解释，成员个数定义那么大是因为懒得数，如果看不懂自己补英语去吧~ 

int main()
{
	std::scanf("%d",&n);
	
	if(n<=10)
	{
		std::cout<<gw[n];
		return 0;
	}//是个1位数 
	if(n>=11&&n<=19)
	{
		std::cout<<tp[n-10];
		return 0;
	}//在11和19之间 
	std::cout<<sw[n/10];//输出十位部分 
	if(n%10!=0) std::cout<<'-'<<gw[n%10];//如果个位不是零，输出个位 
	
	return 0;
}
```


---

