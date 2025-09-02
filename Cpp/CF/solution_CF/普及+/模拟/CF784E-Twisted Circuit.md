# Twisted Circuit

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF784E/03bc9ecd826bed4c1045a0a976af29d4edaea871.png)

## 样例 #1

### 输入

```
0
1
1
0
```

### 输出

```
0
```

# 题解

## 作者：PC_DOS (赞：12)

本题为逻辑电路图解析题(而且符号还和国内高中物理教科书采用的[IEC 标准](https://zh.wikipedia.org/zh-hans/%E9%82%8F%E8%BC%AF%E9%96%98)规定的图示不一样(至少人教版如此))，本题的图示采用的是[ANSI/IEEE Std 91-1984 标准](https://zh.wikipedia.org/zh-hans/%E9%82%8F%E8%BC%AF%E9%96%98)之中规定的逻辑电路图示。

下面是本题出现的图示:

![](https://cdn.luogu.com.cn/upload/pic/13796.png )

"与"门，相当于AND(&)。

![](https://cdn.luogu.com.cn/upload/pic/13798.png )

"或"门，相当于OR(|)。

![](https://cdn.luogu.com.cn/upload/pic/13797.png )

"异或"门，相当于XOR(^)。

这样，沿着题目所给的电路图走一遍就可以得到输出了...

代码:
```
#include <iostream>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	bool iIn1, iIn2, iIn3, iIn4,iAns; //四个输入(模拟输入端的高低电平)以及一个输出(模拟输出端的高低电平)，因为只可能是0和1，用bool就够了
	cin >> iIn1 >> iIn2 >> iIn3 >> iIn4; //读入四个输入
	iAns = ((iIn1^iIn2) & (iIn3 | iIn4)) ^ ((iIn2&iIn3) | (iIn1^iIn4)); //计算输出
	cout << int(iAns); //输出
	return 0;
}
```

---

## 作者：weak_ddb (赞：10)

表示，我们按题目说的做就行了。

```
#include<bits/stdc++.h>
using namespace std;
int iIn1,iIn2,iIn3,iIn4;
int main()
{
	cin>>iIn1>>iIn2>>iIn3>>iIn4;
	cout<<(((iIn1^iIn2)&(iIn3|iIn4))^((iIn2&iIn3)|(iIn1^iIn4)));
	return 0;
}
```
### 完结撒花

---

## 作者：肆零肆 (赞：3)

### daolao勿喷，蟹蟹QwQ

------------
### 主要思路：

###### 其实这道题就是一些dalao们说的 “逻辑门” （然后就传到了我这个蒟蒻的耳朵里辣）

P.S.不知道的小伙伴们戳这里：[“逻辑门”](baike.baidu.com/item/逻辑门/5141155?fr=aladdin)

###### 然后根据题目所给出的关系，输入 bool 类型 iIn1, iIn2, iIn3, iIn4 四个变量，判断输出结果 true 或 false，用 1, 0 表示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF784E/03bc9ecd826bed4c1045a0a976af29d4edaea871.png)

###### 而且善意的PC_DOS（翻译者）已经帮我们直接表示出了他们之间的关系式：

###### ((iIn1^iIn2) & (iIn3 | iIn4)) ^ ((iIn2&iIn3) | (iIn1^iIn4))

###### （"^"表示异或 "|"表示或 "&"表示与）

###### 所以我们只需要输入和按关系式输出就行了


------------


### 最后附上本蒟蒻的AC代码：

```cpp
#include <iostream>
using namespace std;
int iIn1,iIn2,iIn3,iIn4;
int main() {
	ios::sync_with_stdio(false);
	cin >> iIn1 >> iIn2 >> iIn3 >> iIn4;
	cout << (((iIn1^iIn2)&(iIn3|iIn4))^((iIn2&iIn3)|(iIn1^iIn4)));
	return 0;//管理员大大求通过
｝
```

---

## 作者：CZQ_King (赞：2)

居然没有打表？

蒟蒻表示打表大法好！

------------
> 题意：

> 如入四个数，都是$0$或$1$ $iIn1$, $iIn2$, $iIn3$, $iIn4$ 输出((iIn1^iIn2) & (iIn3 | iIn4)) ^ ((iIn2&iIn3) | (iIn1^iIn4))

> "^"表示异或 "|"表示或 "&"表示与

做法：
把全部情况打出来，存进一个四维数组里，然后输出相应的就好了。
因为输入的数字只有$0$和$1$两种，所以表只有$2^4=16$种方案。

生成表的代码：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("1.txt","w",stdout);//输出路径
	cout<<"int a[5][5][5][5];\n";//定义数组
	for(int iIn1=0;iIn1<2;iIn1++)
	for(int iIn2=0;iIn2<2;iIn2++)
	for(int iIn3=0;iIn3<2;iIn3++)
	for(int iIn4=0;iIn4<2;iIn4++)//每个数都从0到1枚举
	cout<<"a["<<iIn1<<"]["<<iIn2<<"]["<<iIn3<<"]["<<iIn4<<"]="<<(((iIn1^iIn2)&(iIn3|iIn4))^((iIn2&iIn3)|(iIn1^iIn4)))<<";\n";//输出相应数组下表标以及答案
}
```
最后把``1.txt``里的东西复制出来

真正的代码：
```
/*打表*/
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a[5][5][5][5],b,c,d,e;
	a[0][0][0][0]=0;
	a[0][0][0][1]=1;
	a[0][0][1][0]=0;
	a[0][0][1][1]=1;
	a[0][1][0][0]=0;
	a[0][1][0][1]=0;
	a[0][1][1][0]=0;
	a[0][1][1][1]=0;
	a[1][0][0][0]=1;
	a[1][0][0][1]=1;
	a[1][0][1][0]=0;
	a[1][0][1][1]=1;
	a[1][1][0][0]=1;
	a[1][1][0][1]=0;
	a[1][1][1][0]=1;
	a[1][1][1][1]=1;//初始化数组
	cin>>b>>c>>d>>e;
	cout<<a[b][c][d][e];//输出相应的答案
}
```

---

## 作者：Erusel (赞：2)

这题本身不要翻译啊。。。

**我们来解释一下翻译**

#### 通过观察得到，样例读入的四个数代表着开始的四根线的电流状态（有电流为1，无电流为0）
#### 第一盏灯由1，2控制
#### 第二盏灯由3，4控制
#### 第三盏灯由2，3控制
#### 第四盏灯由1，4控制
#### ~~剩下的就按翻译做行了~~

代码：

```
#include<bits/stdc++.h>

using namespace std;

int a,b,c,d;

int main()
{
    cin>>a>>b>>c>>d;
    cout<<(((a^b)&(c|d))^((b&c)|(a^d)));
    return 0;
}
```

---

## 作者：wzm2007 (赞：2)

	只需按题目的要求跑一遍即可
    ((iIn1^iIn2)&(iIn3|iIn4))^((iIn2&iIn3)|(iIn1^iIn4))

------------

    #include <iostream>
    using namespace std;
    int main()
    {
        bool a,b,c,d,ans;
        cin>>a>>b>>c>>d;
        ans=((a^b)&(c|d))^((b&c)|(a^d));
        cout<<int(ans);
        return 0;
    }

---

## 作者：Mystery_Sky (赞：2)

	(本题本来可能也就普及难度但是硬
    生生给评成了一道NOI难度的紫题，有点无语。。。)
    这道题目是一道愚人节题目，本来只有下面的电路图，结果翻
    译完之后难度就直接没了。
    
    

------------
	言归正传， 说说这个题目吧。
    #### 
    抛开题目不谈，我们来复习下这个题目的原理。（与，或， 异或的概念）
    
![或](https://cdn.luogu.com.cn/upload/pic/40969.png)

或（|）：若二者均为0则返回0，否则返回1。

![与](https://cdn.luogu.com.cn/upload/pic/40967.png)
    
与（&）：若二者均为1则返回1，否则返回0。

![异或](https://cdn.luogu.com.cn/upload/pic/40970.png)

异或（^）：若二者相等则返回0，不等则返回1。



------------

（~~其实可以直接复制解说的那段公式~~）

贴码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main() {
	int a, b, c, d;
	scanf("%d%d%d%d", &a, &b, &c, &d);
	int s1, s2, s3, s4, s5, s6, s7;// s1, s2, s3, s4, s5, s6, s7分别为每一步的结果。 
	if(a == b)
		s1 = 0;
	else
		s1 = 1;
	if(c == 0 && d == 0)
		s2 = 0;
	else 
		s2 = 1;
	if(s1 == 1 && s2 == 1)
		s3 = 1;
	else
		s3 = 0;
		
	if(b == 1 && c == 1)
		s4 = 1;
	else
		s4 = 0;
	if(a == d)
		s5 = 0;
	else
		s5 = 1;
	if(s4 == 0 && s5 == 0)
		s6 = 0;
	else
		s6 = 1;
		
	if(s3 == s6)
		s7 = 0;
	else
		s7 = 1;
	/*直接s7 = ((a ^ b) & (c | d) ) ^ ((b & c）| (a ^ d))应该也行吧*/  
	printf("%d\n", s7);//输出最后的结果

	return 0;
}
```


---

## 作者：LCuter (赞：1)

~~虽然这道题可以直接输出他的表达式……~~

咳咳，切入正题：

讲解一下这些位运算符号吧~~我是蒟蒻啊~~

# &与 and

运算两数同为1，返回1

否则返回0

# |或 or

运算两数同为0，返回0

否则返回1

# ^异或 xor

运算两数相同，返回0

否则返回1

~~以上是经过简化的，其实是一个恒等变形~~

那么虽然可以用C++自带符号或保留字，但我就是要自己写

```cpp
#include<iostream>
using namespace std;
bool XOR(bool a,bool b){
    if(a==b){
        return false;
    }
    else{
        return true;
    }
}
bool OR(bool a,bool b){
    if(a==0&&b==0){
        return false;
    }
    else{
        return true;
    }
}
bool AND(bool a,bool b){
    if(a==1&&b==1){
        return true;
    }
    else{
        return false;
    }
}
int main(){
    bool a,b,c,d;
    cin>>a>>b>>c>>d;
    cout<<XOR(AND(XOR(a,b),OR(c,d)),OR(AND(b,c),XOR(a,d)))<<endl;
    return 0;
}
```

---

## 作者：向日葵小班 (赞：0)

### 翻译已经把公式列出来了，所以我们直接输出就好啦

## 放代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d;
int main()
{
	cin>>a>>b>>c>>d;
	cout<<(((a^b)&(c|d))^((b&c)|(a^d)));//公式
    return 0;//完美结束
}
```

**~~管理给过吧QwQ~~**


---

## 作者：陈绎睿 (赞：0)

很简单，题目怎么说，就怎么打

```
#include<bits/stdc++.h>
using namespace std;
int iIn1,iIn2,iIn3,iIn4;
int main()
{
    cin>>iIn1>>iIn2>>iIn3>>iIn4;
    cout<<(((iIn1^iIn2)&(iIn3|iIn4))^((iIn2&iIn3)|(iIn1^iIn4)));
    return 0;
}
```
在这里，向大家介绍一下"^符号。

异或运算（^）
 

参加运算的两个数据，按二进制位进行“异或”运算。

 

运算规则：0^0=0；   0^1=1；   1^0=1；   1^1=0；

　　即：参加运算的两个对象，如果两个相应位为“异”（值不同），则该位结果为1，否则为0。

 

例如：9^5可写成算式如下： 00001001^00000101=00001100 (十进制为12)可见9^5=12  




完（bei）美（can）结束！

---

## 作者：GIFBMP (赞：0)

这题就是裸的模拟题，只需模拟情况就好了。
（与，或，非，异或这些不要解释了吧）

```cpp
#include<cstdio>
#include<string>
#include<iostream>
using namespace std;
int a[10];
bool yu(int a,int b)
{
    return a&&b;
}
bool huo(int a,int b)
{
    return a||b;
}
bool yihuo(int a,int b)
{
    return a!=b;
}
bool fei(int a)
{
    return !a;
}
int main()
{
    for(int i=1;i<5;i++)scanf("%d",&a[i]);
    int k=yihuo(yu(yihuo(a[1],a[2]),huo(a[3],a[4])),huo(yu(a[2],a[3]),yihuo(a[1],a[4])));
    printf("%d\n",k);
    return 0;
}
```

---

## 作者：MX_plasma (赞：0)

emm一道CF的紫水题……

模拟逻辑电路 直接输入In然后套用题目内公式然后输出Out就好了

不多说直接上代码

```cpp
#include<stdio.h>
using namespace std;
int main(){
	bool In1,In2,In3,In4,Out;
	scanf("%d %d %d %d",&In1,&In2,&In3,&In4);
	Out=((In1^In2)&(In3|In4))^((In2&In3)|(In1^In4));
	printf("%d",Out);
	return 0;
}
```

---

## 作者：Retrospective (赞：0)

 ------------------------我是分割线------------------------
 
**灌水区**
 
 _看了 PC_DOS（这位**dalao**）的翻译就会发现~~其实这题是十分水的~~_ 
 
 只需动动手指添个括号
 
 就可以$\color{green}\text{AC}$

------------------------我是分割线------------------------

**$\color{green}\text{AC}$代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,d;//定义4个变量
int main()
{
    cin>>a>>b>>c>>d;//输入4个变量
    cout<<(((a^b) & (c | d)) ^ ((b&c) | (a^d)));//输出答案
    //只需在((iIn1^iIn2) & (iIn3 | iIn4)) ^ ((iIn2&iIn3) | (iIn1^iIn4))外面再加个括号就能直接求出大案
    return 0;
}
```
------------------------我是分割线------------------------

**祈祷区**

$\color{red}\text{一定要过啊！！！}$

$\color{red}\text{上帝保佑！！！}$

$\color{red}\text{上帝保佑！！！}$

---

## 作者：Cx330ㅤ (赞：0)

发篇P党的:
```pascal
var a1,a2,a3,a4:longint;
    a,b,c,d:boolean;
begin
 readln(a1);
 if a1=1 then a:=true else a:=false;
 readln(a2);
 if a2=1 then b:=true else b:=false;
 readln(a3);
 if a3=1 then c:=true else c:=false;  
 readln(a4);  
 if a4=1 then d:=true else d:=false;
 if ((a xor b)and(c or d))xor((b and c)or(a xor d))=true then write(1)else write(0);//暴力枚举
end.
```

---

