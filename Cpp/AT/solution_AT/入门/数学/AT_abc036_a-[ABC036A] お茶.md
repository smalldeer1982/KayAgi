# [ABC036A] お茶

## 题目描述

**题意：**

高桥买了一种可以装A个瓶子的箱子，他现在有B个瓶子，请你帮助他得出他至少要买多少个箱子才可以装所有瓶子。

## 说明/提示

$0\le A,B\le1000$

岛国的题最后输出答案要换行！

# 题解

## 作者：CZQ_King (赞：5)

# 一楼我占了！！
~~翻了好久的AT题，终于找到一题那么水的~~


------------

### 题意：输入两个数a,b。若b能整除a，输出b/a，否则输出b/a+1

感谢[@da32s1da](https://www.luogu.org/space/show?uid=50092)的隐藏


------------

```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int a,b;//我还以为要用double
int main(){
    cin>>a>>b;
    if(b%a==0)//如果b能整除a
        cout<<b/a<<endl;//输出b除以a
    else//否则
    	cout<<b/a+1<<endl;//输出b除以a再加1
    return 0;//完美结束
}
```

---

## 作者：Messi李 (赞：1)

题意：输入两个数a,b。若b能整除a，输出b/a，否则输出b/a+1   谢谢[da32s1da](https://www.luogu.org/space/show?uid=50092)
的提供。

所以 上代码

```cpp
#include <bits/stdc++.h>//万能头文件
using namespace std;
int main(){
    int a,b;
    cin>>a>>b;//输入a和b
    if(b%a == 0) cout<<b/a<<endl;
    //如果b可以整除a，就输出b除a的值
    else cout<<b/a+1<<endl;//如果不行就输出b除a+1的值
    return 0;
}
```
很简单的一道题  emmmmmm  ~~水ti~~

---

## 作者：Cambridge (赞：1)


小学生又来发题解了！

岛国的题真心简单，看到那么多大佬直接用公式，本蒟蒻深表佩服，那好吧，应俗话“暴力出奇迹，枚举过样例”，我们就来暴力一波！首先，读入a和b，while循环到b<=0为止，c这个累加器就是求一共需要多少箱子，和(b+a-1)/2这个公式是等价的，最后输出c即可。

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    int a,b,c;//定义变量
    int main()
    {
    cin>>a>>b;//读入
    while(b>0)b-=a,c++;//求出要用多少个箱子
    cout<<c<<endl;//输出结果并换行
    return 0;
    }
    
好了，本蒟蒻就讲到这里，希望对读者有所帮助。


---

## 作者：林家三少 (赞：1)

这题我觉得不用if,直接输出就行了.

我看到有2位大佬都用了printf,我觉得不用也行.

_AC_ 代码：

	#include<iostream>
	#include<cstdio>
	
	using namespace std;
	int a,b;  //定义a,b
	int main()
	{
		cin>>a>>b;  //输入a,b
		cout<<(b+a-1)/a<<"\n";  //直接输出,要加换行
		return 0;
	}
### 注意:岛国题要换行！

---

## 作者：Aw顿顿 (赞：0)

## 暴力方法 $or$ 数学方法
1. 暴力搜索：

~~~
核心思想：
while循环一遍一遍减，就可以看出他所需要个数，如果没有减至0，那么输出时要输出cnt+1；
~~~

由于已经有人上过代码，这里就不提供代码了。

2. 数学方法

~~~
核心思想：
看b能否被a整除，如果可以直接输出，如果不行那就输出+1
~~~

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b;
int main()
{
	cin>>a>>b;
	if(b%a==0)cout<<b/a<<endl;
	else cout<<b/a+1<<endl;
	return 0;
}
```

3. ceil大法好

~~~
核心思想：
将他们除出一个浮点数，然后上去整，如果不是整数就起到了+1的作用
~~~

4. floor同上

~~~
将除出来的商+1再用floor下去整，更上面的方法类似。
~~~

---

## 作者：有限光阴 (赞：0)

# 一看就知道这是一道难(shui)题
我们先输入
```
cin>>a>>b;
```
再判断,输出
```
if(b%a==0) cout<<b/a<<endl;
else cout<<b/a+1<<endl;
```
下面就是AC代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b;
	cin>>a>>b;
	if(b%a==0) cout<<b/a<<endl;
	else cout<<b/a+1<<endl;
	return 0;
}
```
谢谢观看,管理员大大求过

---

## 作者：bym666 (赞：0)

# AT1863 【お茶】
这道题我想出来的有两个方法，下面我就来给大家好好的说一说。
## 方法一 
方法一用的是if语句，如果能整除，直接输出，否则就加一再输出。
代码如下：
```
#include <bits/stdc++.h>//万能头文件 
using namespace std;
int main()
{
	int a,b;
	cin>>a>>b;//输入 
	if(b%a==0) cout<<b/a<<endl;//如果能整除则直接输出 
	else cout<<b/a+1<<endl;//否则加一再输出 
	return 0;//结束程序 
} 
```
## 方法二
方法二用的是ceil函数（不知道ceil的自己看→[ceil函数](https://baike.sogou.com/v159539.htm?fromTitle=ceil)）。这个方法比方法一简单一点，只要掌握了ceil函数就可以了。
```
#include <bits/stdc++.h>//万能头文件 
using namespace std;
int main()
{
	double a,b;//注意定义的类型 
	cin>>a>>b;//输入 
	cout<<ceil(b/a)<<endl;//输出 
	return 0;//结束程序 
}
```


---

## 作者：唐一文 (赞：0)

这道题很简单，直接输出就行了，连判断都不需要 。  

### 只需用到一个函数：$ceil$ 。

$ceil$的作用是将一个不为整数的数向上取整 。  
当然，用$ceil$的时候要强制转换成$float$或$double$类型的数  ，或者定义时就为$float$或$double$类型的数，不然就会返回整数部分 。


Code出现！（~~挑战极简代码~~）
```cpp
#include<bits/stdc++.h>  //万能头文件
using namespace std;
int main(){
    double a,b;  //注意类型
    cin>>a>>b;  //输入
    cout<<ceil(b/a);  //直接输出向上取整的数
    return 0;  //好习惯
}
```

---

## 作者：wjmqwq (赞：0)

## **~~小学数学题~~可以用if来判断**
### 思路：如果瓶子不能被整除就把箱子+1不然输出箱子数
### 代码如下：

```c
#include<iostream>
using namespace std;
int a,b,c;  //定义 
int main()
{
	cin>>a>>b;  //输入 
	c=b/a;      //c表示箱子数 
	if(b%a!=0)  //如果b不能整除a 
	cout<<c+1<<endl;   //箱子数+1 
	else
	cout<<c<<endl;    //如果能被整除输出箱子数 
	return 0;    //结束 
}

```
**qwq**


---

## 作者：boshi1 (赞：0)

## 你们不觉得python更好用吗？

#### 思路各位大佬都发了，本蒟蒻不再多说

#### py代码：

```python
s=input().split();a=int(s[0]);b=int(s[1])	#初始a,b
if (b/a)%1!=0:							   #判断b/a是否是小数
    print(b//a+1)							#是小数输出b/a+1
else:
    print(b//a)							  #不是小数输出b/a
```

#### 注意：岛国题要换行，但用python写不用特意加\n，请放心

---

## 作者：封禁用户 (赞：0)

这题非常的水，一个判断就搞定了！   
**AC**代码：   
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int a,b;
int main()
{
	scanf("%d%d",&a,&b);//格式化输入输出更快！更爽！更好用！但很复杂。。
	if(b%a==0)//判断b是否整除a
	printf("%d",b/a);//如果是就输出b除a
	else
	printf("%d/n",b/a+1);//否则输出b除a+1
 return 0;
}

```
记住！！岛国题要换行！！

---

