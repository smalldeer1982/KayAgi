# Ultra-Fast Mathematician

## 题目描述

Shapur was an extremely gifted student. He was great at everything including Combinatorics, Algebra, Number Theory, Geometry, Calculus, etc. He was not only smart but extraordinarily fast! He could manage to sum $ 10^{18} $ numbers in a single second.

One day in 230 AD Shapur was trying to find out if any one can possibly do calculations faster than him. As a result he made a very great contest and asked every one to come and take part.

In his contest he gave the contestants many different pairs of numbers. Each number is made from digits $ 0 $ or $ 1 $ . The contestants should write a new number corresponding to the given pair of numbers. The rule is simple: The $ i $ -th digit of the answer is $ 1 $ if and only if the $ i $ -th digit of the two given numbers differ. In the other case the $ i $ -th digit of the answer is $ 0 $ .

Shapur made many numbers and first tried his own speed. He saw that he can perform these operations on numbers of length $ ∞ $ (length of a number is number of digits in it) in a glance! He always gives correct answers so he expects the contestants to give correct answers, too. He is a good fellow so he won't give anyone very big numbers and he always gives one person numbers of same length.

Now you are going to take part in Shapur's contest. See if you are faster and more accurate.

## 样例 #1

### 输入

```
1010100
0100101
```

### 输出

```
1110001
```

## 样例 #2

### 输入

```
000
111
```

### 输出

```
111
```

## 样例 #3

### 输入

```
1110
1010
```

### 输出

```
0100
```

## 样例 #4

### 输入

```
01110
01100
```

### 输出

```
00010
```

# 题解

## 作者：da32s1da (赞：7)

这个题不难嘛，就几行可以了
```
#include<cstdio>
char a[200];int b;
int main(){
    while(scanf("%c",&a[b++])!=EOF);
    for(int i=0;i<=b/2-2;i++)
    printf("%d",a[i]^a[i+b/2]);
}
```
'0'=48=110000
'1'=49=110001
所以不用处理字符，直接异或起来就可以了

---

## 作者：Taurus_Lzc (赞：3)

异或指的是两个数的同为如果相同则为0，否则为1  
这题因为两个数都小于100位，所以最好用字符串  
逐位判断输出0或1  
下见代码：
```cpp
#include<bits/stdc++.h>  //万能头文件
using namespace std;
char a[110],b[110];  //定义字符数组
int main(){
	gets(a);  //输入第一个数
	gets(b);  //输入第二个数
	for (int i=0;i<strlen (a);i++){  //其实也可以写i<strlen (b)，因为两个数长度相同
		if (a[i]==b[i]) cout<<"0";  //异或判断并输出，相同为0
		else cout<<"1";  //不同为1
	}
}
```

---

## 作者：SKTelecomT1_Faker (赞：2)

这题很简单，适合初学者，说下思路

先输入两个字符串$a$,$b$,之后逐位比较$a$与$b$，相同则输出$0$，不同则输出$1$就行了。

记得输出时千万别加换行！（WA的教训）

$Code↓$

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
string a,b;//定义字符串
signed main(void)//主程序
{
    cin>>a;
    cin>>b;//输入
    for(register int i=0;i<a.size();i++)//模拟循环
    {
        if(a[i]==b[i]) cout<<"0";//相同
        else cout<<"1";//不同
    }
    cout<<endl;//换行（个人码风）
    exit(0);//好习惯
}
```

---

## 作者：PC_DOS (赞：1)

模拟也是可以的，只要知道异或的算法就可以了。

方法：同时遍历两个字符串，如果对应位置字符不同，输出0，否则输出1。

代码:
```
#include <iostream>
#include <string>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	string sInput1, sInput2; //两个输入串
	register int i; //循环计数器
	int iLength; //字符串长度
	getline(cin, sInput1);
	getline(cin, sInput2); //读入两个串
	iLength = sInput1.length(); //保存长度
	for (i = 0; i < iLength; ++i){ //遍历字符串
		if (sInput1[i] == sInput2[i]) //如果对应位置字符不同
			cout << 0; //输出0
		else //否则
			cout << 1; //输出1
	}
	return 0; //结束
}
```

---

## 作者：SUNCHAOYI (赞：0)

**在int型中的异或 ：**
```
int a,b;
cout<<a ^ b<<endl;//a xor b
```
**在字符串中（因为长度length max = 100 - 1，只能使用字符串）：**

**输入两个字符串后逐一判断，当两字符不同时输出1，否则输出0**
```
#include <iostream>
#include <string>
using namespace std;
int main()
{
	//a ^ b
	string a,b;
	cin>>a>>b;
	for(int i = 0;i < a.size();i++)
		cout<<(a[i] != b[i]) ? 1 : 0;
	cout<<endl;
	return 0;
 } 
```


---

