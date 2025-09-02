# Rounding

## 题目描述

Vasya has a non-negative integer $ n $ . He wants to round it to nearest integer, which ends up with $ 0 $ . If $ n $ already ends up with $ 0 $ , Vasya considers it already rounded.

For example, if $ n=4722 $ answer is $ 4720 $ . If $ n=5 $ Vasya can round it to $ 0 $ or to $ 10 $ . Both ways are correct.

For given $ n $ find out to which integer will Vasya round it.

## 说明/提示

In the first example $ n=5 $ . Nearest integers, that ends up with zero are $ 0 $ and $ 10 $ . Any of these answers is correct, so you can print $ 0 $ or $ 10 $ .

## 样例 #1

### 输入

```
5
```

### 输出

```
0
```

## 样例 #2

### 输入

```
113
```

### 输出

```
110
```

## 样例 #3

### 输入

```
1000000000
```

### 输出

```
1000000000
```

## 样例 #4

### 输入

```
5432359
```

### 输出

```
5432360
```

# 题解

## 作者：Reywmp (赞：6)

 _**下面哪位用c++的仁兄方法有些繁琐。其实很好理解的！**_ 
 
------------
因为5舍去和进位都可以而且是 _**“四舍六入”**_那我们可以理解为：
-  1,2,3,4要舍去
-  6,7,8,9要进位
-  5可以进位可以舍去

这么一想，如果我们每次都将5进位岂不还是变成了 **_“四舍五入”_** 吗？

------------
c++代码如下：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
    int a;
    scanf("%d",&a);
    a=(a+5)/10*10;//这是信息学中四舍五入的手写方法
    printf("%d",a);
    return 0;
}
```

------------ 
科普一下：

三种小数处理函数：

|**Floor()**  |**下取整（不大于本身的最大 _整数_ ）**  |
| :----------: | :----------: |
|**Ceil()** |**上取整（不小于本身的最大 _整数_ ）**|
|**Round()**  |  **四舍五入到最邻近的 _整数_  ** |





---

## 作者：ACE_ZY (赞：2)

既然没有pascal的字符串解 我来发一个

题意很好理解输入 _**一个整数**_ 将它的最后一位四舍**六**入

自创样例1

输入一个数 1234 将最后一位的4进行四舍六入 它小于5 舍去4 成0 则输出 1230

自创样例2

输入一个数 4567 将最后一位7进行四舍六入 它大于等于6 进1位 输出是4570

自创样例3

输入一个数 8765 将最后一位的5进行四舍六入 可是题目说5可以舍去 也可以进位 所以有两个正确输出 1:8760 2:8770 都是正确的

附上字符串代码

```pascal
var
  x1,x,i:longint;
  s,s1:string;
begin
  readln(s);//读入一个字符串
  for i:=1 to length(s)-1 do s1:=s1+s[i];//将除了最后一位其它都保存起来
  if s[length(s)] in ['5'..'9'] then x:=x+1;//用集合类型 判断最后一位是否大于等于5 (这里将5认定进位,也可以是 in ['6'..'9']) 因为是字符串 必须加双引号 x统计是是否大于5
  val(s1,x1);//将除了最后一位全转成数字
  write((x1+x)*10);//进行四舍六入输出
end.//结束
```

求通过 谢谢

---

## 作者：empty (赞：2)

我看大家啊，都是一些巧方法来解的，模拟也是很直接         
 个位数>5+（10-个位），<5直接变0        
 我就不会那么聪明的方法,还是暴力最可靠        
 ```cpp
#include<cstdio>
using namespace std;
int main()
{
 int n,n1;
 scanf("%d",&n);
 while(1)
 {
  n1=n%10;
  if(n1==0) break;//不就是最后个位变成0吗
  if(n1<=5) n--;//<=5就把它一直减到0
  if(n1>5)  n++;//>5就把它一直加到0
  }
 printf("%d",n);
 return 0;
}
```

---

## 作者：Tarensev (赞：2)

howdy我又来发cf的pascal题解辣~

看了楼下的题解，我一直很纳闷，为什么要记录位数呢？

我们直接考虑最后一位要不要四舍五入，而最后一位就是n%10(n mod 10)

判断一下余数是否四舍五入，四舍不加，五入就加，不需要凑零

九行代码轻松过
```pascal
var n，x：longint；
begin
 readln(n);
 case n mod 10 of
  0..5:x:=0;{5和4都行，如果是4那么就把6变成5}
  6..9:x:=1;{这些都是考虑进不进位的事情了}
 end;
 writeln((n div 10+x)*10);{div 10是为了去掉末尾的四舍五入，再加x是看有没有进位}
end.
```
P.S:有更好的方法请在评论区尽管指出，我会虚心接受的

---

## 作者：zhengjiabao (赞：0)

### python题解

既然题目中说“末尾为5舍去或进位都可”，那么，我们可以直接让5进位，于是就变成了熟悉的“四舍五入”。

代码极简：

```python
print(round(int(input())/10)*10)
```

------------


顺便介绍python中常用的3个处理小数的函数：

| `math.ceil(num)` | 向上取整 |
| :----------: | :----------: |
| **`math.floor(num)`** | **向下取整** |
| **`round(num)`** | **四舍五入** |

（用前两个函数时要注意写`import math`）


---

## 作者：向日葵小班 (赞：0)

## $\color{red}\text{这是一道大水题}$ 

**$\color{red}\text{只要记住两条公式：}$**

**$\color{red}\text{最后一位小于等于5：}$n-=n%10**

**$\color{red}\text{最后一位大于5：}$n+=(10-n%10)**

## 放代码：

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
long long n;//定义一个数字n
int main()
{
     cin>>n;//输入n
	 if(n%10<=5)n-=n%10;//如果最后一位小于等于5，n-=n%10
	 if(n%10>5)n+=(10-n%10);//如果最后一位大于5，n+=(10-n%10)
	 cout<<n;//输出n
    return 0;//完美结束
}
```



---

## 作者：TCZN (赞：0)

根据蒟蒻多年在洛谷摸爬滚打的经验

我发现（~~一副很拽的样子~~）：

# 这 是 一 道 大 难（shui） 题！

只要判断个位是否满足题目要求就行了

贴代码：
```pascal
var
  n,i,s:longint;
begin
 read(n);
  s:=n mod 10; //取出个位
   if s=5 then writeln(n-s) //先对5进行处理，题目中是进位或舍去都行，蒟蒻就舍去吧
    else if s<5 then writeln(n-s) //如果小于5就舍去
    else if s>=6 then writeln(n+10-s); //大于等于6就进1，注意，加的是十位，且个位清零
end.
```
~~CF的题真水啊（小声bb）~~

---

## 作者：不到前10不改名 (赞：0)

//这题算法乱评的吧！谁告诉你们的字符串模拟暴力！分明是利用除法自动向下取整的特性~QAQ~
```
#include<stdio.h>
int n;
int main()
{
    scanf("%d",&n);
    if(n%10>=5)//5入
    n=(n/10+1)*10;//入就+1
    else//4舍
    n=n/10*10;//末尾值自动舍弃，c的特性
    printf("%d",n);
    return 0;
}
```

---

## 作者：Kai_Fu (赞：0)

### **这题思路很简单 个位小于等于5就舍去，入其实就是加一个数字使得前一位数字+1就行了，也就是十位。


#### 下面是AC代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    int n,x;
    cin>>n;
    x=n%10;//取出整数的个位
    if(x<=5)   
    n=n-x;//如果小于等于5就舍去
    else
    n=n+(10-x);//否则进位
    cout<<n;
}
```


---

## 作者：OdtreePrince (赞：0)

# -四舍五入-

其实题目说这么多，四个字——四舍五入。

看到很多DALAO用标准的四舍五入法，让蒟蒻也发一波非正规的题解吧！

如果个位小于5，减去个位数。

否则，减去个位数并加上10.

~~~
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    scanf("%d",&n);
    if(n%10<=4) cout<<n-n%10;
    else cout<<n-n%10+10;
    return 0;
}~~~

---

## 作者：RioBlu (赞：0)

# 直接用四舍五入就可以了

*题目说五可入可舍*

所以把它入了会更加简单

# 代码
```
a=input()
b=a+5
b=b/10
b=b*10
print b
```

### *如果a是1~4*

a+5=6~9

 6~9/10=0

0*10=0

### 5及以上加5大于10

10~14之间是数/10=1

1*10=10


---

## 作者：luv_letters (赞：0)

虽然只是一道四舍五入的~~水题~~

但是我看到没人用 字符串处理+模拟 来写233~~（于是我闲的没事写了些）~~

# 思路（c++）
	1.首先读入字符串
	2.将字符串倒序存入另一个数组
    3.此时最后一位数即新数组的第一位
    4.判断是否大于等于五（ps：我计算的四舍五入）
    5.如果大于五的话...
    	a.先判断是否为一位数（防止“9”这种数据）
		b.将最后一位数字变为'0'；
        c.再进行循环（判断下一位是否为9？是 则变为0再继续  否 则这位加一然后退出循环）；
		d.倒序输出；
    6.如果小于五...就只把末位变为0，然后倒序输出；
    
    
    
    
    
    
    
    
    
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	char s[10000];
	char ss[10000];
	cin>>s;
	int len=strlen(s);
	for(int i=len-1,j=0;i>=0;i--,j++){
		ss[j]=s[i];
	}
		if(ss[0]>='5') {
			ss[0]='0';
			if(len==1) {
				ss[len+1]='1';
				cout<<ss[len+1];
			}
			for(int i=1;i<=len-1;i++){
				if (ss[i]=='9') {
					ss[i]='0';
					continue;
				}
				if(ss[i]!='9') {
					ss[i]+=1;
					break;
				}
			}
			for(int i=len-1;i>=0;i--){
					cout<<ss[i];
			}
			return 0;
		}
		if(ss[0]<='4') {
			ss[0]='0';
			for(int i=len-1;i>=0;i--){
				cout<<ss[i];
			}
			return 0;
		}
	
	return 0;
}
```

---

## 作者：applese (赞：0)

此题非常简单
附上代码和一些重要解释：
```
#include<iostream>
#include<algorithm>
using namespace std;
long long n;
int main()
{
	cin>>n;
	long long ge=n%10;     //取各位
	if(n%1000000000==0) //如果可以整除10^9就可以不用操作了，因为下面出错。
	cout<<n;
	else    //如果不行的方法
	{
		n=(n%1000000000)/10;    //保留个位以上的数字
		if(ge>5)      //如果各位大于5
		{
			n=n+1;     //那么十位+1
		}
		if(n!=0)    //如果各位以上的数字大于5，输出n和一个0
		cout<<n<<"0";
		else    //否则输出0
		cout<<"0";
	}
	
}
```

---

## 作者：frankchenfu (赞：0)

既然大家都写四舍五入，那我发一个五舍六入的题解吧。

类似于四舍五入，我先把个位是否大于5取出来（记为bool变量`m`），然后判断是舍还是入。输出的时候输出$\left \lfloor \frac{n}{10} \right \rfloor + m$，然后输出了除了个位以外的所有位。个位是多少？当然是0.所以最后在加上一个0。注意当$n \le 5$的时候要特判。

```cpp
#include<cstdio>
#include<cstring>

int main()
{
	int n,m;scanf("%d",&n);
	m=(bool)(n%10>5);
	if(n>5)
		printf("%d0\n",n/10+m);
	else
		printf("%d\n",n/10+m);
	return 0;
}
```

---

