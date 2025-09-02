# Playing with Dice

## 题目描述

两个人正在玩游戏。每人写一个 1~6 之间的数，然后掷骰子。写下的数字和骰子上的数最接近的那个人获胜。如果两个人写的数和骰子上的数差距都是一样的，那么是平局。

第一个人写的数是 a，第二个人写的数是 b。
请分别输出第一个人赢、平局、第二个人赢有多少种可能（方法数）。

## 说明/提示

骰子是一个正方体。每个面上有 1~6 的数字。

当 $| a-x | < | b-x |$ 时，可以说 a 比 b 更接近 x。

## 样例 #1

### 输入

```
2 5
```

### 输出

```
3 0 3
```

## 样例 #2

### 输入

```
2 4
```

### 输出

```
2 1 3
```

# 题解

## 作者：封禁用户 (赞：3)

题目传送>>[CF378A](https://www.luogu.com.cn/problem/CF378A)  
### 题意简述：  
两人分别写下一个 1~6 的数，记作 a,b，接着掷骰子，求其接近 a 的可能，等距的可能，以及接近 b 的可能。  
### 题目分析：  
此题据题意模拟即可。比较其更接近谁，直接比较其与骰子数的差的绝对值即可。  
### 问题解决:  
求绝对值可直接使用数学库中的函数。  
头文件:  
```cpp
#include<cmath>
```
函数：  
```cpp
abs();
```
### Code:  
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	int a,b;   //定义两人分别写下的数字a,b
	int x=0,y=0,z=0;   //定义计数三种情况，初始化为1
	cin>>a>>b;
	for(int i=1;i<=6;i++)
	{
		if(abs(a-i)<abs(b-i)) x++;   //更接近a，计数
		if(abs(a-i)==abs(b-i)) y++;   //差距相等，计数
		if(abs(a-i)>abs(b-i)) z++;    //更接近b，计数
	}
	cout<<x<<" "<<y<<" "<<z;   //输出，注意空格
	return 0;    //结束整个程序
}
```
### 结果（未吸氧）:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/ekyzsqb0.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：zplqwq (赞：1)

~~为了不掉社贡才来水题解~~

### 题目分析：

这道题的题意可以简化成如下样子：

- 有两个人在玩一种游戏，每人写一个数后从 $1$ 至 $6$ 这六个数分别减去每个人写的这个数的绝对值，求出哪个数更接近这个数。

读到这里，不难发现，这是一个很简单的模拟题。

我们每次选择记录每次和骰子点数的差，存入两个变量 $a$ 和 $b$ 。

定义三个变量 $x$ ，$y$ 和 $z$ 存的分别是第一个人赢的情况，平局的情况，以及第二个人赢的情况。

比较 $a$ 和 $b$ 的大小，若离第一个人近，则 `x++`，若距离相同，则 `y++` ，否则，则 `z++` 。

最后输出  $x$ ，$y$ 和 $z$ 即可。




---

## 作者：k3v1n070828 (赞：1)

### 这是一道枚举题，其实也不算因为时间复杂度是O(1)

思路：“枚举”骰子$1$~$6$点时所有的情况.

分别用3个计数器：$ansa$，$ansb$，$ansc$记录答案。

其中$ansa$代表第一个人赢的情况总数，$ansb$是平局情况（不是$0$就是$1$），$ansc$是第二个人赢的情况总数。

好了，话不多说，把蒟蒻的AC Code搁在这里，供大家参考（剩下的解释都在注释中）：

```cpp
#include<cstdio>
#include<cmath>
using namespace std;
int a,b;//输入变量
int ansa,ansb,ansc;//答案变量
int main(){
	scanf("%d%d",&a,&b);//输入
	for(int i=1;i<=6;i++)//循环O(1)枚举
	{
		int disa=abs(a-i),disb=abs(b-i);//记录每次和骰子点数的差
		if(disa<disb) ansa++;//如果离a人近，则a赢的情况++
		if(disa==disb) ansb++;//如果距离相同，则平局情况++
		if(disa>disb) ansc++;//如果离b人近，则b赢的情况++
	}
	printf("%d %d %d\n",ansa,ansb,ansc);//最后输出答案
    return 0;//别忘了结束程序
}
```

---

## 作者：CobaltChloride (赞：1)

```
Pas的题解;
枚举,求出每种情况下的个数即可
var i,a,b,p1,p2,draw:longint;//p1表示玩家1赢,p2表示玩家2赢,draw表示平局
begin
read(a,b);
for i:=1 to 6 do begin
if abs(a-i)>abs(b-i) then inc(p2);//玩家2赢
if abs(a-i)<abs(b-i) then inc(p1);//玩家1赢
if abs(a-i)=abs(b-i) then inc(draw);//平局
end;
writeln(p1,' ',draw,' ',p2);//注意顺序
end.
```

---

## 作者：szkzyc (赞：0)

这道题是一道模拟题，思路很好理解。

题意：有两个人在玩一种游戏，每人写一个数后从 $1-6$ 这六个数分别减去每个人写的这个数的绝对值，求出哪个数更接近这个数。

最后输出第一名玩家胜利、平局、第二名玩家胜利的方法数。

此题的思路就是利用 $abs$ 函数来求出绝对值后比较那个数距离 $x$ 最近，再根据题意模拟即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int A, B, point;
int awin, bwin, allwin;
int mian(){
    cin >> a >> b;
    for(points = 1; points <= 6; points++){ //枚举从 1 到 6 
    	if(abs(a - points) < abs(b - points)) awin++; //判断如果第一名玩家赢 
    	else if(abs(a - points) > abs(b - points)) bwin++; //判断如果第一名玩家输 
    	else allwin++; //否则就平局 
	}
	cout << awin << " " << allwin << " " << bwin << endl;  
	return 0;
}

```


---

## 作者：xgwpp6710 (赞：0)

最近退谷了，国庆回来发一篇题解。

这道题还是非常简单的，枚举一下骰子 $1$ 到 $6$ 的情况就行了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x1,x2,c1,c2,cd;
int main()
{
	cin>>x1>>x2;
	for(int i=1;i<=6;i++)
	{
		int d1=abs(x1-i),d2=abs(x2-i);//计算距离
		if(d1<d2) c1++;
		else if(d1==d2) cd++;
		else c2++;//统计
	}
	cout<<c1<<" "<<cd<<" "<<c2;
	return 0;
}
```

---

## 作者：LucasXu80 (赞：0)

这道题不难，遍历$1-6$可以轻松AC。但是我的梦想是~~AK IOI~~普及一等，想借着这道题锻炼一下我的思维。

~~（我不会告诉你我想了半个小时）~~

本题解思路与 @森岛帆高 大佬思路基本相同，但是TA的代码不易理解，也用到了许多我看不懂的符号。这里以我的思路为线索，给大家详细讲解。

我们能否通过$a,b$的具体数值，来计算出答案呢？请看。

首先，如果$a=b$，不管怎么样一定是平局。答案是$0$ $6$ $0$，很简单。

接下来就是重中之重了。由于较为不好理解，篇幅较长，请理解。由于$a=b$的情况已经被排除，这里只写$a<b$的情况。

我注意到了样例中的这么一组数据：

输入 2 5  输出 3 0 3

这一组很特别呀，两人胜负的场数是相同的。难道$2,5$有什么特殊的性质？

确实：$2+5=7$。不难知道，只要两个数的和是$7$，结果一定是对半分，没有平局。因为，只要骰子上的数$≤3$，一定是$a$赢；反之$b$赢。

想到这里，仍然没有头绪。继续往下看样例。

输入 2 4  输出 2 1 3

咦，这胜利的天平怎么就向Bob倾斜了？想到刚刚的$7$的规律，我也算了一下：

$2+4=6$。出于好奇，我又算了一组和为$6$的数：$1,5$。

**发现答案也是2 1 3**。

这个时候我恍然大悟：答案与两数之和有关。那具体关系是什么呢？我们来一一列举$2$ $4$这一组数据的情况。

| 骰子 | A胜 | 平局 | B胜 |
| -----------: | -----------: | -----------: | -----------: |
| 1 | √ |  |  |
| 2 | √ |  |  |
| 3 |  | √ |  |
| 4 |  |  | √ |
| 5 |  |  | √ |
| 6 |  |  | √ |

可以看出，$3$是一个分界线，上面A赢，下面B赢。试问为什么？

$3=(2+4)/2$。

想想也能理解，这里就不再赘述了。那么这个分界线$3$就是两数之和$/2$。

这里再想到刚刚发现的规律——答案与两数之和有关，就更能理解为什么了。

总结一下，对于$a<b$的情况，只要骰子上的数比$(a+b)/2$小，Alice胜；若$=$，平局；若$>$，Bob胜。

写到这里，代码实现就不难了，做做减法就可以了。当然我的代码中将$(a+b)/2$是否为整数分开了，这样更清晰一些。

好了，上代码咯~

```cpp

#include <iostream>
using namespace std;
int main()
{
    int a,b;
    cin>>a>>b;//定义两个数并输入
    if (a==b) cout<<"0 6 0";//如果相等，输出0 6 0
    else if (a<b)//a<b（也就是题解中说的情况）
    {
        double x=(a+b)/2.0;//保留小数
        int y=(a+b)/2;
        //如果x=y说明x是整数，有平局
        if (x==y) cout<<y-1<<" 1 "<<6-y;
        //y-1实质上是(y-1)-1+1，从1到y-1都是A胜;6-y实质上是6-(y+1)+1，同理
        else cout<<y<<" 0 "<<6-y;//不是整数，没有平局
        //y=y-1+1,6-y同上
    }
    else//a>b的情况，只不过输出反一下罢了，不再加注释了
    {
        double x=(a+b)/2.0;
        int y=(a+b)/2;
        if (x==y) cout<<6-y<<" 1 "<<y-1;
        else cout<<6-y<<" 0 "<<y;
    }
    return 0;
}
```
### 后记

其实我花了半个小时解决一道这么简单的题，可能有人觉得没有必要，其实这是锻炼自己的思维能力。设想如果不是一个骰子，而是$int$范围内的整数，就不能枚举了。真正AC的那一刻，还是非常快乐的！

希望大家喜欢！

---

## 作者：灵小沙 (赞：0)

	#include<bits/stdc++.h>//别问我，为什么打那么多头文件 
	#include<string>
	#include<iostream>
	#include<cmath>
	#include<set>
	#include<stack>
	#include<queue>
	using namespace std;
	
	int main()
	{
		int a,b,a1=0,b1=0,lie=0;//前面计数变量为零 
		cin>>a>>b;
		int i;
		for(i=1;i<=6;i++)//纯模拟，打个很简单的表 
		{
			if(abs(i-a)>abs(i-b))//abs绝对值，差值大于b，就选b。 
			{
				b1++;
			}
			if(abs(i-a)<abs(i-b))
			{
				a1++;
			}
			if(abs(i-a)==abs(i-b))//lie表示平局 
			{
				lie++;
			}
		}
		cout<<a1<<" "<<lie<<" "<<b1;
		return 0;
}


---

## 作者：tryrtj (赞：0)

这题要是再不会就该放弃OI了，除了一个abs函数几乎没啥有难度的，直接上代码

```
#include<iostream>
#include<cmath>//abs函数用的
using namespace std;
int main(){
	int a,b;
	cin>>a>>b;
	int ping=0,win1=0,win2=0;//初始为0
	for(int i=1;i<=6;i++){//枚举6个点数
		if(abs(a-i)>abs(b-i))win2++;//差的绝对值小的赢
		if(abs(a-i)<abs(b-i))win1++;
		if(abs(a-i)==abs(b-i))ping++;
	}
	cout<<win1<<' '<<ping<<' '<<win2<<endl;//输出
	return 0;//一道水题能给注释已经不错了QAQ
}
```

---

## 作者：_lzh_ (赞：0)

## 思路

因为骰子的点数只有 1-6 ，所以直接枚举骰子的点数即可。

对于每一个点数，计算出它与 $a,b$ 的差的绝对值，再进行比较即可。

注意一定要计算绝对值。

具体讲解见代码。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans1/*记录第一个人赢的次数*/,ans2/*记录第二个人赢的次数*/;
int ans3/*记录平局的次数*/,a,b;
signed main()
{
	cin>>a>>b;
	ans1=ans2=ans3=0;//初始化 
	for(int i=1;i<=n;i++)
	{
		int x=abs(i-a);
		int y=abs(i-b);
		//计算出当前点数与 a,b 的差的绝对值 
		if(x<y)/*如果第一个人获胜*/
			ans1++;
		else if(x>y)/*如果第二个人获胜*/
			ans2++;
		else/*否则是平局*/
			ans3++;
	}
	cout<<ans1<<" "<<ans2<<" "<<ans3;
	return 0;
}
```

---

