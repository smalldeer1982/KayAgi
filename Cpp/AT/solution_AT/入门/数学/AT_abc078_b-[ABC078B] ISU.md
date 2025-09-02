# [ABC078B] ISU

## 题目描述

有一把宽度为 $X$ 厘米的椅子。现在有很多人想坐在这把椅子上，每个人坐下时会占据 $Y$ 厘米的宽度。

希望让尽可能多的人坐在椅子上，但由于每个人都很害羞，因此每两个人之间，以及椅子边缘与人之间，至少需要留出 $Z$ 厘米的间隔。

最多可以有多少人坐在椅子上？

## 说明/提示

## 限制条件

- 所有输入均为整数。
- $1 \leq X, Y, Z \leq 10^5$
- $Y + 2Z \leq X$

## 样例解释 1

如下图所示，可以正好坐下 $3$ 个人。  
![](https://img.atcoder.jp/abc078/4a35302937c3cbc2f625156e7834d27f.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
13 3 1```

### 输出

```
3```

## 样例 #2

### 输入

```
12 3 1```

### 输出

```
2```

## 样例 #3

### 输入

```
100000 1 1```

### 输出

```
49999```

## 样例 #4

### 输入

```
64146 123 456```

### 输出

```
110```

## 样例 #5

### 输入

```
64145 123 456```

### 输出

```
109```

# 题解

## 作者：t162 (赞：7)

我们可以用O(1)的方法来解决。

先来模拟一张凳子：

`空人空人空人空`

我们先减去开头空的部分，得到：

`人空人空人空`

发现这时人的数目和空隙的数目是相等的。那么得出：
$$\text{人数}=\dfrac{\text{椅子长度}-\text{空隙长度}}{\text{人占长度}+\text{空隙长度}}$$

考虑到结果不一定是整数，而世界上又不可能存在几分之几个人，所以要对结果向下取整，得到式子：
$$\text{人数}=\lfloor\dfrac{\text{椅子长度}-\text{空隙长度}}{\text{人占长度}+\text{空隙长度}}\rfloor$$

根据式子编写程序即可。

---

## 作者：蒟蒻取不来名 (赞：5)

$$QwQ$$

我好蒻啊

AT普及-不存在模拟做不出的题

```
#include<iostream>
using namespace std;
int x, y, z, qaq, ans;
int main()
{
	cin >> x >> y >> z;
	qaq = z;//将qaq初始值定为z（座位末端的人与椅子边缘的间隔为Z厘米长）
	while(qaq + y + z <= x){
		qaq += y + z;//每做一个人要多占要y+z的位置（坐在座位上的人总是占据长度为Y厘米的间隔，两个人之间必须有至少Z厘米的长度差距）
		ans ++;
	}
	cout << ans;
	return 0;
}
```
温馨提示：AT不换行会听取WA声一片的QwQ

---

## 作者：Eason6 (赞：4)



------------
祖国的花朵，最蒟的是我。大家好，我就是大蒟蒻。

------------
没错，我大蒟蒻刷了红水题，现在又向黄水题进军了。我大蒟蒻又来刷水题了。

------------
鉲鉲，进入正题，首先看到题：小学五（或者六）上（或下）数学广角的植树问题，只不过树已有了长度，因此只需将总长减去一个间隙距离再除以树长与间隔之和即可，代码虽短，五脏俱全。好了，话不多说，上代码：（注释在代码里）
```
#include<bits/stdc++.h>//万能头文件 
using namespace std;//命名空间 
int main(){//主函数 
	long long int a,b,c;//定义 
	cin>>a>>b>>c;//输入 
	cout<<(a-c)/(b+c)<<endl;//公式 
	return 0;//结束程序 
}//perfect 
```


---

## 作者：I_will (赞：2)

不知道为什么，大家都想坐椅子，而在part里只有一张长x米的长凳，每个人要坐长y米的地方（屁股好大），park规定：每个人都要相隔z米，最后一个人和边缘也要相隔z米。

-----


献上程序：
```
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
	int x,y,z,h,g;
int main()
{
	cin>>x>>y>>z;
	h=x-z;
	while(h-z>0)
	{
		if(h-y-z<0)break;
		else h=h-y-z;
		g++;
	}
	cout<<g<<endl;
	return 0;
}
```

---

## 作者：hzx1 (赞：2)

把这道题转化为数学题思路就很清晰咯…

有点类似于数学中的植树问题…（两个端点都种）

设m为最终坐下的人数

可得：

        zm+ym+z=x

解：(z+y)m+z=x

              m=(x-z)/(z+y)

最后就是代码啦
```cpp
#include<iostream>
using namespace std;
int main(){
	int x,y,z;
	cin>>x>>y>>z;
	cout<<(x-z)/(z+y)<<endl;
	return 0;
}
```

---

## 作者：丁丁の丁丁 (赞：1)

emm我决定用do while来做
~~~~
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,m,k,l,i=0;
	cin>>n>>m>>k;
	l=k;//把离椅子边缘赋值给l;
	do
	{
		l+=m+k;//i个人用过的椅子；
		i++;//人数+1；
	}
	while(l<n);//到没有距离的时候结束；
	if(l>n) i--;//判断有没有超出椅子距离，超出就减去！
	cout<<i<<endl;
	return 0;
}
~~~~

---

## 作者：wushuang0828 (赞：1)

翻译讨论帖里有，我用的是while循环……

作为P党，没有Pascal题解就来发一个……

具体看代码吧:
```pascal
var
 x,y,z,i,s:longint;
begin
 readln(x,y,z);
 s:=z;//因为第一个离椅子的边缘有z厘米
 while s<x do//如果还有距离，就继续循环
  begin
   s:=s+y+z;//i个人已用的椅子距离
   inc(i);//又多了一个人
  end;
 if s>x then dec(i);//判断是否有超出，超出就减去一个人
 writeln(i);//输出有多少个人
end.
```

---

## 作者：CZQ_King (赞：1)

### 做法：这道题由于凳子与人之间要有空隙，所以可以先减去一个空隙，然后再用总长除以一个人和空隙的长度。最后就是人的个数。
就算多出来一些空隙，用除法的话C++会自动除去小数部分。
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int a,b,c;
int main(){
    cin>>a>>b>>c;
    a-=c;//减去空隙
    cout<<a/(b+c)<<endl;//除以人和空隙
    return 0;//结束
}
```

---

## 作者：勘探员·引魂人 (赞：1)

**前言：岛国人民真 ~~伟大~~ ，AT普及像童话。今天，我又找到了一道AT普及题（又跟AT入门题没什么区别），我 ~~绞尽脑汁~~ 轻轻松松就过了这道题**

**思路：先写一个check函数，由于椅子之间有空隙，所以x(总长)先减掉z(一个空隙的长度)，接着答案=公式“x/(y+z)”（详细请见下），最后调用函数输出**

**公式意义：用总长除以一个人要坐的长度+空隙长度**

```
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<string>//文件头不多讲
using namespace std;
int a,b,c;//定义总长，一个人要坐的长度，空隙长度
int check(int x,int y,int z)//定义check函数
{
	int ans;//定义答案
	x-=z;//总长先减掉一个空隙的长度
	ans=x/(y+z);//答案=总长除以一个人要坐的长度+空隙长度
	return ans;//return 答案
}
int main()
{
    cin>>a>>b>>c;//输入总长，一个人要坐的长度，空隙长度
    cout<<check(a,b,c)<<endl;//直接调用函数输出

    return 0;//结束“题解 AT3669 【ISU】”
}
```


---

## 作者：黄昏烟雨乱WA声 (赞：0)

## ~~好水的题~~
先来看，原本是010101010……

最前面的那个位置（z）对计算无用，删掉它。

就变成了101010101010

可以看成每个人都占自己的位置和边上那个他的空位

就是每个人等效为（10）

可以等效为一条长为X-Z的凳子，每个人都占Y+Z的长度，紧挨着，问最多能坐下多少人

## ~~这是小学计算题~~

上代码
```cpp
#include <iostream>
#include <bits/stdc++.h>
using namespace std; 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int x,y,z;
	cin>>x>>y>>z;
	x=x-z;
	y=y+z;
	z=x/y;
	cout<<z;
	return 0;
}
  
```


---

