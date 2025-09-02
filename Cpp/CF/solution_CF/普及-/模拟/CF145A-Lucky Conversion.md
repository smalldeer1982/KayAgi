# Lucky Conversion

## 题目描述

Petya loves lucky numbers very much. Everybody knows that lucky numbers are positive integers whose decimal record contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Petya has two strings $ a $ and $ b $ of the same length $ n $ . The strings consist only of lucky digits. Petya can perform operations of two types:

- replace any one digit from string $ a $ by its opposite (i.e., replace $ 4 $ by $ 7 $ and $ 7 $ by $ 4 $ );
- swap any pair of digits in string $ a $ .

Petya is interested in the minimum number of operations that are needed to make string $ a $ equal to string $ b $ . Help him with the task.

## 说明/提示

In the first sample it is enough simply to swap the first and the second digit.

In the second sample we should replace the second digit with its opposite.

In the third number we should replace all three digits with their opposites.

## 样例 #1

### 输入

```
47
74
```

### 输出

```
1
```

## 样例 #2

### 输入

```
774
744
```

### 输出

```
1
```

## 样例 #3

### 输入

```
777
444
```

### 输出

```
3
```

# 题解

## 作者：cz666 (赞：2)

## 这题恶意评分...其实实质是道红题！！！

### 题面翻译：

给你两个由 $ 4 $ 和 $ 7 $ 构成的字符串 $ a,b $ ，并给你两种变换方式：

1. 把字符串 $ a $ 中的任意一个字符从 $ 4 $ 变成 $ 7 $ 或者从 $ 7 $ 变成 $ 4 $ 。

2. 把字符串 $ a $ 中的某两个元素（这两个元素一定是一个 $ 4 $ 一个 $ 7 $ ）交换位置。

然后，让你求出把字符串 $ a $ 变为字符串 $ b $ 所需的最少步骤数。

### 思路：

两种变换方式其实实质上都是按要求把 $ 4 $ 变成 $ 7 $ 或者把 $ 7 $ 变成 $ 4 $ ，只不过使用一次第二种方法可以比第一种方法节省一步。

所以，根据上面那个~~废话~~，我的思路就初步形成了：

1. 先找到字符串 $ a $ 中到底有多少个 $ 4 $ 和多少个 $ 7 $ 与字符串 $ b $ 不同，分别放到变量 $ p4 $ 和 $ p7 $ （变量名你随便定义，我选了 $ p4 $ 和 $ p7 $ ）中去。

2. 然后我们知道，如果都是按照第一种方案来做，那么答案是 $ p4+p7 $ （这个就是要消耗的最多的步数（全部都只做方法一，一次只改变一个字符））。

   但是我们还有方案二（交换两个位置上的字符），每使用一次方案二就可以节约 $ 1 $ 步，只不过它有要求必须每次交换是一个 $ 4 $ 和一个 $ 7 $ 。
   
   而两个字符串中不一样的字符我们在上一步中已经分别求出，所以最多可以匹配 $ min(p4,p7) $ 个 $ 4 $ 和 $ 7 $ ，也就是说最多可以节省的步数是 $ min(p4,p7) $ 步。

3. 所以，所需的最少步数就是最多的步数减去最多可以减掉的步数，即 $ p4+p7-min(p4,p7) $ 上述式子显然可以化简（因为 $ min(p4,p7) $ 必定是 $ p4 $ 和 $ p7 $ 中较小的那一个，所以减去之后剩下的应该是 $ p4 $ 和 $ p7 $ 中较大的那一个），化简结果就只剩下 $ max(p4,p7) $ 。所以， $ max(p4,p7) $ 就是这道题的最小解。

### 下面贴上我的AC代码：

```cpp
#include<bits/stdc++.h>
#define int long long
//其实这个好像完全没必要，我属于手残党，每次都会写这个...
using namespace std;
string a,b;
signed main(){
	cin>>a>>b;
	int len=a.length(),p4=0,p7=0;//记录字符串长度以及p4,p7的初始化
	for (register int i=0;i<len;i++){
		if (a[i]!=b[i] && a[i]=='4') p4++;//统计a中有几个4和b中的不一样
		if (a[i]!=b[i] && a[i]=='7') p7++;//统计a中有几个4和b中的不一样
	}
	printf("%lld\n",max(p4,p7));//手推完公式后的答案
	return 0;//完美结束程序
}
```

[我的AC记录](https://www.luogu.org/recordnew/show/18113090)

---

## 作者：米奇奇米 (赞：2)

## 这是一题很水的贪心题 ：
### 首先我先对题目意思进行解释：就是有两种操作：
### $A.$ 改变这个数位上的值
### $B.$ 交换自选两个位上的数字，两种操作方法的代价都是$1$
### 首先我们先看一题类似的题目，但不是重题：
#### [CF1037C Equalize](https://www.luogu.org/problemnew/show/CF1037C)
#### 对于这道题目：交换两个位置一定只能在两个数位$abs(i-j)<=2$,要不然这种操作的代价换不如直接改变当前数位上的值，这里就不放代码啦！~~（逃~~

### 对于这道题目，有一个奇怪的思想，因为不论交换多远的两个数位上的值，代价都为$1$。于是我们只要$O(n)$扫一遍字符窜，如果不同，统计$7$,$4$的个数，最后取个$ans=max(sum_4,sum_7)$即可，$ans$就是这道题目的答案。

### 贴一个代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
int ans1,ans2;
int main(){
	cin >> s1 >> s2 ;
	for ( register int i = 0 ; i < s1.length() ; i++ ) 
	    if ( s1[i] != s2[i] ) {
	    	if ( s2[i] == '4' ) ans1++ ;
	    	if ( s2[i] == '7' ) ans2++ ;
	    }
	cout << max ( ans1 , ans2 ) << endl ;
	return 0;
}
```


---

## 作者：LCGUO (赞：1)

这题的结论还是比较好推的。

---

读入两个串 $a,b$。

设 $num4$ 表示 $a$ 串和 $b$ 串不同，且 $a$ 串为 $4$ 的数量；  
设 $num7$ 表示 $a$ 串和 $b$ 串不同，且 $a$ 串为 $7$ 的数量。

---

提出一个结论：最小的转换次数是 $\max(num4,num7)$。

证明如下：

当 $a$ 串和 $b$ 串第 $i$ 位相同时，这个位上字符不需要更改或交换，所以这个位对答案是没有影响的。

如果不考虑交换操作的话，操作次数应该就是 $num4+num7$。

又因为交换是没有限制的，所以 $a$ 串中，一个不对应的 $4$ 必定可以和一个不对应的 $7$ 交换，使得这两个相互对应。

也就是说，现在一个不对应的 $4$ 和一个不对应的 $7$ 可以配对，只相当于一次操作次数，所以操作次数也就是  
$num4+num7-\min(num4,num7)=\max(num4,num7)$

---

经过一波~~伪证~~证明后，我们就可以愉快地使用结论了，代码也就呼之欲出了，如下：

```cpp
#include<bits/stdc++.h>
#define rint register int
using namespace std;
char a[100010],b[100010];
int num7,num4;
int main(){
    scanf("%s%s",a+1,b+1);
    int len=strlen(a+1);
    for(rint i=1;i<=len;++i){
        if(a[i]!=b[i]&&a[i]=='4') num4++;
        if(a[i]!=b[i]&&a[i]=='7') num7++;
    }
    printf("%d",max(num4,num7));
    return 0;
}
```
完了awa

---

## 作者：Valk_R (赞：0)

这里是蒟蒻的第一篇题解，请多多关照指正。


------------
个人感觉这是一道水题，虽然我不会评难度，但这题肯定是没有绿题的水平的。我这个蒟蒻也是提交了一次就过了。

看了一下和其他题解的代码还是有不一样的地方，那么就和大家分享一下我的思路


------------
## 题目分析
我们实际上要将两个数中的每一位一一对应，大概有以下两个步骤。

设第一串数为 $ s1 $,第二串数为 $ s2$。

1. 将 $ s1 $ 和 $ s2$ 中 $4$ 的个数和 $7$ 的个数变为一致，因为如果 $ s1 $ 和 $ s2$ 中 $4$ 和 $4$（或者 $7$ 和 $7$）的个数不相同，两串数是不可能相同的。这就要用到操作1；
1. 变换 $4$ 和 $7$ 的位置使 $ s1 $ 和 $ s2$ 每一位一一对应。这就要用到操作2。

要求步骤1的操作次数我们只要将 $ s1 $ 中的 $4$ 的个数减去 $ s2$ 中的 $4$ 的个数再对其取绝对值就行了（$7$ 也可以）,记这个数为 $a$。

要求步骤2的操作次数我们要先数出 $ s1 $ 和 $ s2$ 中不对应的位数 $n$,操作次数就等于 $(n-a)/2$.因为我们一共要改变 $n$ 对数才能使 $ s1 $ 和 $ s2$ 相同，步骤1中我们已经完成了 $a$ 对，到步骤2时我们还需完成 $n-a$ 对，而操作2每次可以改变 $2$ 对数的状态，所以只需要进行 $(n-a)/2$ 次操作。

那么我们要求的操作次数就是步骤1的次数加步骤2的次数 $a+(n-a)/2$ 即为 $(n+a)/2$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a;
string s1,s2;
int main()
{
	cin>>s1;
	cin>>s2;
	a=abs(count(s1.begin(),s1.end(),'4')-count(s2.begin(),s2.end(),'4'));
        //计算步骤1，count()函数可以数出某段字符串中某字符的个数
	for(int i=0;i<s1.length();i++)
	if(s1[i]!=s2[i])n++;
        //计算步骤2
	cout<<(n+a)/2;
	return 0;
}
```


---

## 作者：cq_loves_Capoo (赞：0)

严重怀疑恶评，咋可能是绿色wq   
  
_______    
  
首先，这道题本身并不难qwq  
  
先来看看题目：   

```
定义幸运数字为只含有“幸运字符”（4和7）的正整数。如4，7，744是，而5,17,467不是。

现有两个等长的字符串a，b，只含“幸运字符”，对a进行下面两个操作中的任意一种：
  
1. 将任意一个a中的字符从4变7，或者从7变4。

2. 将a中任意两个字符位置互换。

求能使a变成b的最小操作次数。
```   
  
先看操作一，既然是等长且只有两个字母，那么就很好办了：不是 4 就是 7 吖。   
  
接着看看操作二能对操作一有什么优化：可以将任意两个字符交换。   
  
因为只有两种交换可能，相同与不相同的交换，很明显相同的交换并没什么用，故只可能将不同的两个字符交换，这一步操作可以代替两步操作一。   
  
那么答案已经出来了：尽量地用第二种操作，直到不能用了，再进行第一步操作。    
  
那么什么时候才不能用第二种操作呢？根据操作二的条件，可以得知是没有两个不符合字符串 $b$ 的字符相同，于是我们可以得出答案为 **若 $a_i = '4'$ 且 $b_i = '7'$ 的情况大于 $a_i = '7'$ 且 $b_i ='4'$ 的情况，那么答案就是前者，否则为后者。**    
  
code:  
   
```
#include <bits/stdc++.h>

using namespace std;

signed main() {
	
	string a, b;
	int di4 = 0, di7 = 0;
	
	cin >> a >> b; //因为没有空格所以采用 cin
	
	for (int i = 0; i < a.size(); i ++) {
		
		if (a[i] != b[i]) //两个字符必须要不同才能进行下面的判断
			if (a[i] == '4' && b[i] == '7')
				++ di4;/*两种不同要区分开来*/ else ++ di7;
	}
	
	printf ("%d", max (di4, di7));
	return 0;
}
```  
  
码风较差，求大佬们少点吐槽（

---

## 作者：きりと (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/CF145A)**

### 题目大意

见中文翻译

### 解题思路

语文题。

显然，交换原有字符的效率肯定是要高于直接变换字符的，而原先就两两相同的字符我们不应该进行处理。

那么就可以贪心了，因为 $a$ 中的 $4$ 和 $7$ 可以随意交换，也就是说，如果 $a$ 中有 $x$ 个 $4$ ， $y$ 个 $7$ ，那么我们可以用 $min(x,y)$ 次交换来让其中 $min(x,y)$ 个字符与 $b$ 中字符相同

此时，剩下的字符数是： $abs(x-y)$ ，这些数字只能进行直接变换，来使其与 $b$ 相同

所以答案就是 $abs(x-y)+min(x,y)$

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
signed main()
{
	cin>>a>>b;
	int x=0,y=0,s=0;
	for(int i=0;i<a.size();i++)
	{
		if(a[i]!=b[i])
		{
			s++;
			if(a[i]=='4')
			{
				x++;
			}
			else
			{
				y++;
			}
		}
	}
	cout<<min(s,abs(x-y)+min(x,y))<<endl;
	return 0;
}
```



---

## 作者：xxzjbd (赞：0)

看到最小次数问题以为是动态转移，但仔细看看，这题又恶评了。

题中只有两个数字与两种操作，且两个数字相互对应，于是为了最少操作次数，更改一个数字前不如先考虑能不能找到另一个数字与它交换位置，一次交换可以满足两个位置的数字，显然优化了操作次数。

所以只要将需要修改次数小的数字先找位置交换，每次交换必定减少了另一个数字的修改次数，最后还多余的数字无法交换，就只能单次修改了。计两个数字需要修改次数为 $a$ 与 $b$ ，则答案为 $max$ $($ $a$ $,$ $b$ $)$
## 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b;
int main(){
	string s1,s2;
	cin>>s1>>s2;
	for(int i=0;i<s1.size();i++)
		if(s1[i]!=s2[i]){
			if(s2[i]=='4')a++;
			else b++;
		}
	cout<<max(a,b);
} 
```
## 谢谢观赏

---

## 作者：_Scaley (赞：0)

这道题算是一个思考题吧

## 题目概要：

有两个相同长度的字符只有 4 和 7 的字符串，要把这两个字符串变得相同，

可以有两种操作：

* 在第一个字符串中单独改变一个数

* 在第一个字符串中交换任意两个数

问最少的操作次数是多少？

## 题目分析：

如果要把两个**只有两种字符**的字符串变得相同，可以想到：

1. 如果两个字符串的相同位置的字符一样，那么这个位置的字符不用改变 。

2. 如果两个字符串的相同位置的字符不一样：

> * 如果有另一个相同位置的字符不一样且那个字符恰好与这个字符不一样，交换两个数。

> * 如果没有上述那种情况，就单独改变这个数。

原因很明显，交换一次两个不相同的数字就相当于改变两次数字，

在达到同样目的的情况下，前者操作次数比后者少，

所以尽量用交换的操作总是没错的。

## 大概流程：

1. 读入两个字符串

2. 同时扫描两个字符串：

> * 如果字符相同，不做操作。

> * 如果字符不同，对第一个字符串的数字进行统计，如果是 4 对 4 进行计数；如果是 7 对 7 进行计数。

我们可以想象，4 和 7 相互抵消，操作数为 4（7） 的数量，

同时剩下需要改变的数字只有 4 或者只有 7，

剩下的只能单独改变，所以要加上剩下的操作数。

所以最后输出 ``max（对 4 的计数， 对 7 的计数）``。

## 代码实现：

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#define F1(i, a, b) for (int i = a; i <= b; ++i)

std :: string a, b;

int main() {
	int l4 = 0, l7 = 0, l; // l4 为对 4 的计数， l7 为对 7 的计数
	std :: cin >> a >> b;
	l = a.length();
	F1(i, 0, l - 1) {
		if (a[i] != b[i]) { // 如果相同位置的字符不一样
			if (a[i] == '4') ++l4; // 对 4 计数
			else ++l7; // 对 7 计数
		}
	}
	printf("%d", std :: max(l4, l7)); // 输出
	return 0;
}
```

---

## 作者：Ba_creeper (赞：0)

#### 题目分析：

这道题主要是贪心。

我们可以先把两个数字串 $a,b$ 读进来，然后，我们可以设 上4下7 出现的次数有 $aa$ 次，上7下4 出现的次数有 $bb$ 次。

结论：需要操作的最小次数是 $max(aa,bb)$ 。

探究思路：根据题意，我们可以明确，一个 $aa$ 和一个 $bb$ 可以相互抵消。我们只需要贪心，算出相互抵消的个数，即 $min(aa,bb)$ 。这样，需要操作的最小数就是 $aa+bb-min(aa,bb)$ ，也就是 $max(aa,bb)$ 了。

#### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
string a,b;
int main()
{
	cin>>a>>b;
	int aa=0,bb=0,lena=a.size();//求出读入字符串的长度
	for(int i=0;i<lena;++i)
	{
		if(a[i]!=b[i] and a[i]=='4') aa++; //统计上4下7的情况
		if(a[i]!=b[i] and a[i]=='7') bb++; //统计上7下4的情况
	}
	cout<<max(aa,bb);
	return 0;
}
```



---

## 作者：Pkixzx (赞：0)

这道题有一定思维难度，代码难度简单。

先证明一下。

如果s[i]和s1[i]相同时，那么就可以不动。如果不相同时，我们可以统计7和4分别的个数t1和t2，每一个4和7互相交换，这是一次操作，这时，操作次数为：**t1+t2-min（t1，t2）**。

这时，我们可以化简这个式子（直接用也可以）得到了max（t1，t2）这个式子。

 　 　
那么代码就非常好写了。
  　　
    
那么可得代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int a[100010];
int main()
{
	string s,s1;
	long long n,m,t=0,t1=0;
	cin>>s>>s1;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]!=s1[i]&&s[i]=='4')//统计不一样且是4的个数
		t++;
		if(s[i]!=s1[i]&&s[i]=='7')//统计不一样且是7的个数
		t1++;
	}
	cout<<max(t,t1);
}
```


---

## 作者：chenpengda (赞：0)

对于串$a$ `4777474774774`和串$b$ `7444747477474`我们的最好方法如下：

首先串$a$和$b$相同的部分不用管，去掉

此时串$a$ 和串$b$ 变成：`4777474747`和`7444747474`

之后（为了观看方便）按照$a$串为$4$，$b$串为$7$ ，这样的位置个数为$x_1$；$a$串为$7$，$b$串为$4$，这样的位置个数为$x_2$。排序后，变成`4444777777`和`7777444444`（不影响答案）

这个时候你会发现，比起使用①操作每次剪掉一个数，不如使用操作②尽量多次，而这个次数就是$\min(x_1,x_2)$，在使用②操作$\min(x_1,x_2)$（例子中是$4$）次后，只剩下一种对应关系，不能使用②了，此时使用①$6$次即可（本例）。

于是最少使用次数就是$\max(x_1,x_2)$，输出即可。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	char a[100005],b[100005];//注意输入的数的位数
	scanf("%s%s",&a,&b);
	int x1=0,x2=0;//
	for(int i=0;i<strlen(a);i++)//strlen(a)是a的长度
	{
		if(a[i]=='4'&&a[i]!=b[i])x1++;
		if(a[i]=='7'&&a[i]!=b[i])x2++;
	}
	cout<<max(x1,x2);
}
```


---

## 作者：Mr_WA的大号 (赞：0)

在题海中遨游，在代码中绽放。小学生又来发题解了！

题号：CF145A

难度：★★

算法：数论、暴力、字符串

## 开课了！

这一题也是一道数学题，考我们的数学思维。接下来我就讲一下这题的解题思路。

根据题目的条件，我们可以很容易发现，第一步比第二步少去一步，如：47变成74，第一步只要一次就行了，而第二步要两次。这就得出了我们要多用第一步。

接着我们就要思考怎么求出步数。设定原串为a，目标串为b，则如果a[i]不等于b[i]，就至少要一步。统计的时候我们还要多用两个变量：four和seven，代表要换多少个4和多少个7。

输出要特殊处理一下：输出four与seven中较大的数。为什么呢？相信很多人都知道。假设four大于seven，就用four中前seven个做步骤1，其他做步骤二。seven大于four同理。four等于seven时，全部都做步骤一。

好了，上代码：
```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<string>
#include<cstring>
#include<string.h>
#include<algorithm>
#include<iomanip>
using namespace std;
string a,b;//定义字符串
int four,seven;//定义four和seven
int main()
{
	cin>>a>>b;//输入
	for(int i=0; i<a.size(); i++)//从第0位到最后一位查找
		if(a[i]=='4')//如果a[i]是4
		{
			if(a[i]!=b[i])//如果不相同
				four++;//four++
		}	
		else//如果a[i]不是4，则为7
			if(a[i]!=b[i])//如果不相同
				seven++;//seven++
	cout<<max(four,seven)<<endl;//输出两个数较大的一个
	return 0;
}
```
祝大家能AC!

---

