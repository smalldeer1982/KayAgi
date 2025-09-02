# Memory and Trident

## 题目描述

Memory is performing a walk on the two-dimensional plane, starting at the origin. He is given a string $ s $ with his directions for motion:

- An 'L' indicates he should move one unit left.
- An 'R' indicates he should move one unit right.
- A 'U' indicates he should move one unit up.
- A 'D' indicates he should move one unit down.

But now Memory wants to end at the origin. To do this, he has a special trident. This trident can replace any character in $ s $ with any of 'L', 'R', 'U', or 'D'. However, because he doesn't want to wear out the trident, he wants to make the minimum number of edits possible. Please tell Memory what is the minimum number of changes he needs to make to produce a string that, when walked, will end at the origin, or if there is no such string.

## 说明/提示

In the first sample test, Memory is told to walk right, then right, then up. It is easy to see that it is impossible to edit these instructions to form a valid walk.

In the second sample test, Memory is told to walk up, then down, then up, then right. One possible solution is to change $ s $ to "LDUR". This string uses 1 edit, which is the minimum possible. It also ends at the origin.

## 样例 #1

### 输入

```
RRU
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
UDUR
```

### 输出

```
1
```

## 样例 #3

### 输入

```
RUUR
```

### 输出

```
2
```

# 题解

## 作者：Keep_RAD (赞：1)

~~水题解啦~~

一天，你在CF题库里闲逛，挑一些不一样的题~~水题解~~，发现了这一道题。



------------
其实这一题很简单，这样经过思考，就可以写出来。

我们知道，一左一右，一上一下，都可以抵消。那么要想在原地，有一左必有一右，有一上必有一下，所以只有偶数个字符的串，才可以经过操作后仍在原地。

特判代码：

```cpp
int s=a.size();
	if(s%2==1)
	{
		cout<<-1;
		return 0; 
	}
```

经过刚刚的分析，我们可以提出这样一个思路：读进一个字符，就进行判断，在其对应的变量中储存，所对应的变量可以相互抵消，就加入绝对值的计算。

理解都在代码里了哦。


代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int u=0,r=0,l=0,d=0; //字符对应的变量
string a;
int main()
{
	cin>>a;
	int s=a.size();//计算长度
	if(s%2==1)//特判
	{
		cout<<-1;
		return 0; 
	}
	for(int i=0;i<s;++i)//枚举每个字符
	{ 
		if(a[i]=='U') u++;//进行对应变量的操作，上则上变量自增，以下同理
		if(a[i]=='D') d++;//注意要用单引号
		if(a[i]=='R') r++;
		if(a[i]=='L') l++;
	}
	cout<<(abs(l-r)+abs(u-d))/2;//左右上下抵消，输出
	return 0;
}
```

懂了咩？

bug在评论区里发出来哟？点赞（逃）


---

## 作者：WsW_ (赞：0)

### 更新
这是一篇已通过的题解。  
- $2024.12.30$ 更新旧题解。

---

### 思路
先考虑能不能回到原点，也就是最终 `U` 的个数要与 `D` 的个数一样，这样才能抵消，`L` 和 `R` 同理。  
即最终要 $cnt_L=cnt_R,cnt_U=cnt_D$ 。  
上式能成立的必要条件为 $(cnt_L+cnt_U+cnt_R+cnt_U) \bmod 2 = |s| \bmod 2 = 0$，由于我们可以修改，所以这个必要条件同时是充分条件。  
如果 $|s| \bmod 2 \neq 0$ 时就一定不行，直接输出 `-1`。  
如果可行的话就求出一共要换几个，即和目标差多少，但要除以 $2$。  
为什么除以 $2$ 呢？每次修改会造成 $2$ 的改变。例如本来往左走一步，改成往右走一步，修改前对比修改后就有 $2$ 的改变。  

时间复杂度为 $O(|s|)$。

---

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int l,fx[5];
char ch[100004];
int main(){
	cin>>ch;
	l=strlen(ch);
	if(l&1){ //不成立，输出-1。
		printf("-1");
		return 0;
	}
	for(int i=0;i<l;i++){//统计个数
		if(ch[i]=='U')fx[1]++;
		if(ch[i]=='D')fx[2]++;
		if(ch[i]=='L')fx[3]++;
		if(ch[i]=='R')fx[4]++;
	}
	printf("%d",(abs(fx[1]-fx[2])+abs(fx[3]-fx[4]))/2);//差距除以二
	return 0;
}
```

---

## 作者：Galaxy_Q (赞：0)

# CF712B Memory and Trident 题解




## 题目概述：
输入字符串，分别有：上（U） 、 下（D） 、 左（L） 、 右（R） 共计四种指令.求出是否能够经过更改指令回到原点，若能回到原点，最少需要更改几个指令.


------------

## 题目分析：
 **1.** 首先判断是否能够回到原点，因为一旦移动一次，就需要向与它相反的方向移动，从而抵消. 所以能够回到原点的移动次数为一个偶数，**换句话说：移动次数为奇数的移动， 一定不会回到原点.** 
 
 **2.** 因为相反的移动会与其抵消，所以只需要设置两个计数器用来存储移动方向.因为最后判断的是与原点的距离，所以正负是一样意义的，只需要在最后输出时加上绝对值.
 

------------

## 代码实现：


```cpp
//CF712B
#include <bits/stdc++.h>
using namespace std;
string st;
int cnt1, cnt2; // ->存储移动指令
void f(char x){
	if(x == 'L')
		cnt1--;
	if(x == 'R')
		cnt1++;
	if(x == 'U')
		cnt2--;
	if(x == 'D')
		cnt2++;
	return; // ->进行对指令的判断
}
int main(){
	cin>>st;
	if(st.length()%2)
		cout<<"-1"<<endl; // -> 筛出无法回到原点的指令 
	else{
		for(int i=0;i<st.length();i++)
			f(st[i]);
		cout<<(abs(cnt1)+abs(cnt2))/2<<endl; // ->考虑负数情况，加绝对值
	}
	return 0;
} 
```


------------

# [AC记录](https://www.luogu.com.cn/record/65597948)


---

## 作者：Mysterious_Cat (赞：0)

### 思路：
1. 指令个数如果为奇数直接输出$-1$。
2. 向左走和向右走抵消，所以只用记录左右的偏移量，最后除以二。
3. 同理求上下的偏移量
4. AC
### Code：
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
    string s;
    cin >> s;
    if(s.size() % 2)
    {
        cout << -1;
        return 0;
    }
    int x = 0, y = 0;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == 'U') y++;
        if(s[i] == 'D') y--;
        if(s[i] == 'L') x++;
        if(s[i] == 'R') x--;
    }
    printf("%d", (abs(x) + abs(y)) / 2);
    return 0;
}
```


---

## 作者：Creator_157 (赞：0)

~~CF日常水题解~~


------------

### 题意：

有一人从 原点$（0,0）$ 出发，按照字符串的指令移动—— R：向右、L：向左、U：向上、D：向下。

如果一通操作之后 可以通过改变指令中某些字符 回到原点，就输出改变的个数。

如不然就输出$-1$。


------------
### 思路：

① 可以先判断输出$-1$的情况：

如果这个人想回到原点，最简单的方法就是  _沿着来时的路走_  那么可以推断出 TA要接受的指令的个数 **一定是偶数** 个时才能回到原点。

那么如果指令个数是 **奇数** 直接输出$-1$。

② 如果指令个数为偶数，如果想回到原点就必须满足 向**左**走的步数**等于**向**右**走的步数 向**上**走的步数**等于**向**下**走的步数，那么就累加起来向上、下、左、右 走的步数

（（求他们的差）的和）/2 ==ans

### code
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
char a[100005];
int u,r,l,d,k;
int main()
{
    cin>>a;
    int s=strlen(a);
    if(s%2==1)cout<<-1;
    else
    {
        for(int i=0;i<s;i++)
        {
            if(a[i]=='R')r++;
            else if(a[i]=='L')l++;
            else if(a[i]=='U')u++;
            else d++;
        }
        k+=abs(u-d);
        k+=abs(l-r);
        k/=2;
        cout<<k;
    }
    return 0;
}
```


---

## 作者：羽儇 (赞：0)

[CF712B](https://www.luogu.org/problem/CF712B)

---

$Solution$

显然假如有奇数个，无论怎样变化，一定都会有一个指示被孤立，就不会回到原点

U 与 D ， L 与 R 之间可以相互抵消

要注意的是U与D，L与R之间也可以转化

$WA$了 $:$我第一遍写的时候直接判断$abs(U-D)$是否等于$abs(L-R)$

所以应该将多余的没有抵消过的指示相加，再除以$2$

---

$Code$

```
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;
char s;
int R,L,U,D,N;
int main()
{
	while(cin >> s)
	{
		N ++;
		if(s == 'R')R ++;
		if(s == 'L')L ++;
		if(s == 'U')U ++;
		if(s == 'D')D ++;
	}
	if(N&1)
	{
		puts("-1");
		return 0;
	}
	int l = abs(R - L),r = abs(U - D);
	printf("%d",(l + r >> 1));
	return 0;
}
```


---

## 作者：yzx72424 (赞：0)

显然读入时，m个R与m个L可以抵消，m个U与m个D可以抵消

设这个人在的位置为（x,y）

则有
  x=R的个数-L的个数
  y=U的个数-D的个数
现在假设在RRRRUUUU 
那么他就在4,4这个位置
一个D与U抵消可以看作Down 2个单位，
同理。一个L与R抵消可以看作LEFT 2个单位

所以ans=(|x|+|y|)**/2**

```
#include<bits/stdc++.h>
using namespace std;
int n,x,y;
string s;
int main() {
    cin>>n;
    cin >> s; 
    for (char c : s) {
    	if(c=='U')y++;
    	else if(c=='D')y--;
    	else if(c=='L')x--;
    	else if(c=='R')x++; 
    }
    cout << abs(x)+abs(y) <<endl;
}

```

当然但操作个数为奇数时不存在答案，输出-1：
```
   for (char c : s) {
    	t++;
    	if(c=='U')y++;
    	else if(c=='D')y--;
    	else if(c=='L')x--;
    	else if(c=='R')x++; 
    }if(t%2==1)cout<<-1;
    else 
    cout << (abs(x)+abs(y))/2 <<endl;
```


---

## 作者：_Felix (赞：0)

因为要回到原点，所以有多少L就必须要有多少R，同理有多少U就必须要有多少D

所以我们知道**奇数长度的不可能，直接输出-1**

我们一定要统计一下各种字母的数量，

算出了 l,r字母数的差lr 和 u,d字母数的差ud

然后再进行+、-、*、/and绝对值

所以我们就开始找规律

最后通过样例的数据我试出答案应该是(abs(l-r)+abs(u-d))/2

---

update:2020/10/11

2年以后再看这题，真是百感交集。

果然还是小孩子有灵感啊，现在的我完全猜不出结论
~~至少根据这个样例猜不出，我记得当时我也猜了很久才猜出来的。~~

竟然还是没有人证明一下。

显然，已经配好对的不需要配对了。

剩下的都是落单的。

设x=abs(l-r),y=abs(l-r),

显然x+y是偶数。

不妨设有x个L和y个U，

- x奇，y奇：(x-1)/2个L改成R，1个U改成R，(y-1)/2个U改成D,总共(x+y)/2

- x偶，y偶：x/2个L改成R，y/2个U改成D,总共(x+y)/2


---

然后上代码：
```
#include<bits/stdc++.h>//万能库
using namespace std;
int main()
{
	string s;//定义
	cin>>s;
	int len=s.size();
	if(len%2==1)
	{
		printf("-1\n");
		return 0;
	}//长度奇数不可能
	int l=0,r=0,u=0,d=0;
	for(int i=0;i<len;i++)
	{
		if(s[i]=='L')
			l++;//统计向左的
		else if(s[i]=='R')
			r++;//统计向右的
		else if(s[i]=='U')
			u++;//统计向上的
		else if(s[i]=='D')
			d++;//统计向下的
	}
	int lr=abs(l-r);
	int ud=abs(u-d);
	cout<<(abs(lr+ud))/2<<endl;//输出
	return 0;
 } 
```

---

## 作者：lhjy666 (赞：0)

### 这题只要算出x和y轴离原点的距离在/2就好了 
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
char a[1000005];
ll R,L,U,D,t;
int main()
{
	scanf("%s",a);
	ll l=strlen(a);
	if(l%2==1)
	{
		printf("-1");
		return 0;
	}
	else
	{
		for (ll i=0;i<l;i++)
		{
			if(a[i]=='R') R++;
			if(a[i]=='L') L++;
			if(a[i]=='U') U++;
			if(a[i]=='D') D++;//算出向上下左右走的距离 
		}
		t=t+abs(abs(L-R)+abs(U-D))/2; 
		printf("%lld",t);
	}
	return 0;
}
```


---

## 作者：lihanyang (赞：0)

```
1.长度为奇数时-1
2.其实这道题只要统计坐标x,y的值，把他们的绝对值相加再除以2就可以了
```
```cpp
#include<bits/stdc++.h>//万能头文件
#define ll long long//ll定义long long （偷懒）
using namespace std;
int main()
{
	ll x=0,y=0;
	string s;
	cin>>s;//读入和初始化
	
	if(s.length()&1) //如果长度是奇数，-1
	{
		cout<<-1<<endl;
		return 0;
	}
	for(ll i=0;i<s.length();i++)
	{
		if(s[i]=='R') x++;
		else
		if(s[i]=='L') x--;
		else
		if(s[i]=='U') y++;
		else
		if(s[i]=='D') y--;
	}//算出x,y坐标
	cout<<(abs(x)+abs(y))/2<<endl;//输出
}
```

---

