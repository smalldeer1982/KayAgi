# Chewbaсca and Number

## 题目描述

Luke Skywalker gave Chewbacca an integer number $ x $ . Chewbacca isn't good at numbers but he loves inverting digits in them. Inverting digit $ t $ means replacing it with digit $ 9-t $ .

Help Chewbacca to transform the initial number $ x $ to the minimum possible positive number by inverting some (possibly, zero) digits. The decimal representation of the final number shouldn't start with a zero.

## 样例 #1

### 输入

```
27
```

### 输出

```
22
```

## 样例 #2

### 输入

```
4545
```

### 输出

```
4444
```

# 题解

## 作者：珂爱甲贺忍蛙 (赞：5)

# 模拟！模拟！模拟！
这道题，我们来模拟一下：
如果不考虑首位为9的情况下，什么情况可以改变数呢？

当然是5、6、7、8、9这五个数啦！

所以我们每次判断这个位数上的数是不是5、6、7、8、9即可。

最后，在首位一定要特判一下，因为首位不能为0。

最后的最后，贴上代码：
```
#include <bits/stdc++.h>
using namespace std; 
int main() 
{
	string s;
    long long i,x,j,m,l,n,k,t=0,y,ans=1,mm=0,num=1;
    cin>>s;
    for(i=0;i<=s.size()-1;i++)
    {
    	if(s[i]=='5')
        s[i]='4';
        else if(s[i]=='6')
        s[i]='3';
	    else if(s[i]=='7')
	    s[i]='2';
	    else if(s[i]=='8')
	    s[i]='1'; 
	    else if(s[i]=='9')
	    s[i]='0';
	}
	if(s[0]=='0')
	s[0]='9';
	cout<<s;
}
```
完美结束。

---

## 作者：引领天下 (赞：2)

先发翻译：
给你一个数x（$ x<={10}^18$），可以对它的每一位数y进行翻转（将其替换为9-y），也可以不替换。求最小 
# **正数**

这个请管理员放到题面上。

------------
题解

------------
这题其实不难，只需按题意模拟即可。

### 但是

## 有坑点！

那就是需要特判的情况：

首位为0（包括整个数为0的情况）

很明显，这种情况是不符合**正数**这一条件的

所以我在题面中标记了这个坑

注意了这点，代码就很好写了

上巨短代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
char a[20];
int main(void){
    scanf ("%s",a);
    for (int i=0;a[i];i++)a[i]=min(a[i],char(9+'0'-a[i]+'0'));
    if (a[0]=='0')a[0]='9';
    printf ("%s",a);
}
```

---

## 作者：Frank_R_Z (赞：1)

###
我这篇题解是把其他三个dl的方法笼络了一下，代码的实现就会比较简洁且更容易理解
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string a;//此类改数字的题目string最为funny
	cin>>a;
	for(int i=0;i<a.size();i++)
	{
		a[i]=min(a[i],char(9+48-a[i]+48));//48是‘0’的ASCLL码
	} 
	if(a[0]=='0')a[0]='9';
	cout<<a<<endl;//快乐输出
	return 0;
}

```
##
~~你们可以尝试用long long~~(光速逃


---

## 作者：yuzhechuan (赞：1)

```cpp
#include <bits/stdc++.h>//方便的万能库，开放的洛谷
using namespace std;

char c;
 
int main()
{
    ios::sync_with_stdio(false);//输入输出加速，经本人实测，能快30ms
    cin>>c;//读入首位数字(字符)
    if(c=='9')cout<<'9';//特判首位数字
    else cout<<min(9-(c-'0'),c-'0');//条件不能为0=>字符减九前不能为9
    while(cin>>c) cout<<min(9-(c-'0'),c-'0');/*边读边处理
      cin作为函数是有返回值的，能读到就是真
      c-'0'将字符转数字，然后用取小函数min进行选择*/
    return 0；//嘿嘿
}
```

---

## 作者：PC_DOS (赞：1)

为了得到"最小"的数字，我们可以用字符串读入题目所给的数字，将其从头到尾遍历一遍，并做如下处理：

1. 除最高位外，若某位数字大于等于5，则将其反转。

2. 若最高位大于等于5小于等于8，同样将其反转。

由于本题要求得到最小的正数，因此对于长度为1的字符串不需要特殊处理。

代码:
```
#include <iostream>
#include <string>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	string sNum; //字符串形式的数字
	int iLength; //长度
	register int i; //循环计数器
	cin >> sNum; //读入数字
	iLength = sNum.length(); //保存长度
	if (sNum[0] >= '5' && sNum[0] <= '8'){ //最高位特殊处理: 若最高位大于等于5小于等于8，将其反转
		sNum[0] = '9' - sNum[0] + '0';
	}
	for (i = 1; i < iLength; ++i){ //遍历字符串，跳过最高位
		if (sNum[i] >= '5' && sNum[i] <= '9'){ //若某位数字大于等于5，则将其反转
			sNum[i] = '9' - sNum[i] + '0';
		}
	}
	cout << sNum; //输出
	return 0; //结束
}
```

---

## 作者：Star_Wind (赞：0)

可怜我一名蒟蒻居然不知道10的18次方在longlong范围内

不过这题还是用字符串简单

首先，坑已经在题目里说了，那我们把循环从一开始，st[0]做个特判

st[i]是一个字符，把它化成数字要减去字符‘0’，接着我们把st[i]对应的数字和9-st[i]对应的数字作min比较。这里要特别注意，min之后的值是一个整数，再把它化成字符需要强制转换：char(...+'0')（~~蒟蒻我为了这个调了半天~~）

最后输出st就行了

附上AC代码：
```cpp
#include<bits/stdc++.h>
#define xh(i,l,r) for(int i=l;i<=r;i++)         
using namespace std;
string st;
int main()
{
	getline(cin,st);
	if(st[0]!='9') st[0]=char(min(st[0]-'0',9-(st[0]-'0'))+'0');
	xh(i,1,st.size())
	  st[i]=char(min(st[i]-'0',9-(st[i]-'0'))+'0');
	cout<<st;
	return 0;
	while(1) cout<<"NO chaoxi!!!!"<<endl;//hh
}
```

ps如果你们不信我对了的话，可以看我的[记录](https://www.luogu.org/record/25765594)

~~当然这么帅气的代码你们怎么可能不信呢~~（逃


---

