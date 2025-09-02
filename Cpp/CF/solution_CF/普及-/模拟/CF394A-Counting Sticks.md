# Counting Sticks

## 题目描述

When new students come to the Specialized Educational and Scientific Centre (SESC) they need to start many things from the beginning. Sometimes the teachers say (not always unfairly) that we cannot even count. So our teachers decided to teach us arithmetics from the start. And what is the best way to teach students add and subtract? — That's right, using counting sticks! An here's our new task:

An expression of counting sticks is an expression of type:

\[ $ A $ sticks\]\[sign +\]\[ $ B $ sticks\]\[sign =\]\[ $ C $ sticks\] $ (1<=A,B,C) $ . Sign + consists of two crossed sticks: one vertical and one horizontal. Sign = consists of two horizontal sticks. The expression is arithmetically correct if $ A+B=C $ .

We've got an expression that looks like $ A+B=C $ given by counting sticks. Our task is to shift at most one stick (or we can shift nothing) so that the expression became arithmetically correct. Note that we cannot remove the sticks from the expression, also we cannot shift the sticks from the signs + and =.

We really aren't fabulous at arithmetics. Can you help us?

## 说明/提示

In the first sample we can shift stick from the third group of sticks to the first one.

In the second sample we cannot shift vertical stick from + sign to the second group of sticks. So we cannot make a - sign.

There is no answer in the third sample because we cannot remove sticks from the expression.

In the forth sample the initial expression is already arithmetically correct and that is why we don't have to shift sticks.

## 样例 #1

### 输入

```
||+|=|||||
```

### 输出

```
|||+|=||||
```

## 样例 #2

### 输入

```
|||||+||=||
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
|+|=||||||
```

### 输出

```
Impossible
```

## 样例 #4

### 输入

```
||||+||=||||||
```

### 输出

```
||||+||=||||||
```

# 题解

## 作者：清小秋ovo (赞：6)

# CF394A

[洛谷传送门](https://www.luogu.com.cn/problem/CF394A)

[原题传送门](https://codeforces.com/problemset/problem/394/A)

## 题目说明

一道题意比较简单的模拟题。

~~（莫名其妙打了个最优解）~~

模拟的过程为火柴棍游戏，其中规定的输入格式如下：

```
|||+||=|||||
```
请问如果最多只能移动一个火柴棍（无法移动加，减，等于号上的火柴棍），火柴棍等式是否成立？

如果给出的等式本身就成立，那么直接输出。

## 解题思路

判断条件的本身并不复杂。

将等式左边的两个加数记为 $n$，$m$。等式右边的和记为 $k$。

那么首先判断是否：
$$n+m=k$$
如果满足该条件证明给出的等式本身就是符合要求的，直接输出。

继续判断是否: 
$$n+m+2=k$$
只有在当 $k$ 正好与左边的式子的和的差值为 $2$ 时，将 $k$ 处的火柴棍左移，也可以做到等式合法。同理也可以判断：
$$n+m=k+2$$
只有当左边的和比 $k$ 正好大 $2$ 时，则将 $n,m$ 中任意一处的火柴棍右移。

**但是这里有一个魔鬼细节：因为当出现刚刚描述的情况需要进行右移时, $n$ 或者 $m$ 不能为 $1$, 应当选择那个值大于 $1$ 的加数进行操作。**

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;
//输出函数
void print(int a,int b, int c){
    for(int i=0;i<a;i++)cout<<"|";
    cout<<"+";
    for(int i=0;i<b;i++)cout<<"|";
    cout<<"=";
    for(int i=0;i<c;i++)cout<<"|";
}
int main()
{
   string a;
   cin>>a;
   int n=0,m=0,k=0,plus=0,s=0;//n,m为加数，k为和，plus记录加号出现次数, s记录等号出现次数
   for(int i=0;i<a.length();i++){
       if(a[i]=='+')plus++;
       if(a[i]=='=')s++;
       if(a[i]=='|'&&plus==0&&s==0)n++;//分别读入n,m,k数据
       if(a[i]=='|'&&plus==1&&s==0)m++;
       if(a[i]=='|'&&plus==1&&s==1)k++;
   }
   if(n+m==k) cout<<a<<endl,exit(0);//如果式子本身合法，直接输出
   if(n+m+2==k){//情况1，需要从右往左移，只需要在输出的前面提前打一个'|', 然后k的地方减少一个棍子就好了
           cout<<"|";
           print(n,m,k-1);//三个参数分别代表两个加数棍子的数量，以及和的棍子的数量
           return 0;
   }
   if(n+m==k+2){//情况2，需要从左往右移，默认是挪第一个加数，但是如果第一个加数只有1的时候，就只能挪第二根棍子
       if(n>1){
           print(n-1,m,k+1);
           return 0;
       }if(m>1){
           print(n,m-1,k+1);
           return 0;
       }
   }
   cout<<"Impossible"<<endl; //如果情况都不符合，输出impossible
}

```
完结撒花！


---

## 作者：Ryan_Yu (赞：6)

本题的思路都在代码里，在此，本蒟蒻只讲本题的一个难点，即：怎样判断 $1$ 根火柴棒是第一个加数、第二个加数还是第三个加数。

首先需定义三个 `bool` 型的标志变量:

当$flag1=false$时，第一个加数 $n_1\gets n_1+1$。

当$flag2=false$时，第二个加数 $n_2\gets n_2+1$。

当 $flag3=false$ 时，和 $n_3\gets n_3+1$。

然后再进行判断：

如果读入的字符是 $\texttt{+}$ 号，就将 $flag1$ 置为 $true$ ，同时将 $flag2$ 置为 $false$。

如果读入的字符是 $\texttt{=}$ 号，就将 $flag2$ 置为 $true$ ，同时将 $flag3$ 置为 $false$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n1,n2,n3,i,al;string a;
bool flag1=false,flag2=true,flag3=true;
//注意：flag1开始为true
int main() 
{
    cin>>a;
	al=a.size();
    for(i=0;i<al;i++)
    {
        if(a[i]=='|')
        {
            if(flag1==false)
                n1++;//n1为第一个加数
            if(flag2==false)
                n2++;//n2为第二个加数
            if(flag3==false)
                n3++;//n3为和
        }
        else if(a[i]=='+')
            {
                flag1=true;
                flag2=false;
            }
        else if(a[i]=='=')
            {
                flag2=true;
                flag3=false;
            }
    }
    if(n1+n2==n3)
    {
        
        for(i=1;i<=n1;i++)
            cout<<"|";
        cout<<"+";
        for(i=1;i<=n2;i++)
            cout<<"|";
        cout<<"=";
        for(i=1;i<=n3;i++)
            cout<<"|";
        cout<<endl;
    }
    /*左边的火柴棒总个数与右边的火柴棒个数相等，
    这种情况原样输出即可。
    /*
    else if(n1+n2-1==n3+1)
    {
        if(n1>n2)
            n1--;
        else
            n2--;
        for(i=1;i<=n1;i++)
            cout<<"|";
        cout<<"+";
        for(i=1;i<=n2;i++)
            cout<<"|";
        cout<<"=";
        for(i=1;i<=n3+1;i++)
            cout<<"|";
        cout<<endl;
    }
    /*左边的火柴棒总个数-2等于右边的火柴棒个数。
    这种情况需进行判断，如果第一个加数>第二个加数，第一个加数 $-1$根火柴棒到右边。
    /*
    else if(n1+n2+1==n3-1)
    {
        for(i=1;i<=n1+1;i++)
            cout<<"|";
        cout<<"+";
        for(i=1;i<=n2;i++)
            cout<<"|";
        cout<<"=";
        for(i=1;i<=n3-1;i++)
            cout<<"|";
        cout<<endl;
    }
    /*左边的火柴棒总个数等于右边的火柴棒个数-2。
	  这种情况直接把右边的火柴棒拿一根给第一个加数即可。
    /*
    else
        cout<<"Impossible"<<endl;
    //啥也不是，输出Impossible。
	return 0;
}
```


---

## 作者：追梦之鲸 (赞：1)

[Link](https://www.luogu.com.cn/problem/CF394A)

### 思路

首先读入 $A,B,C$，如果 $A+B=C$，那么直接输出；如果 $A+B+2=C$，那么让 $C-1,A+1$；如果 $A+B=C+2$，那么让 $A$ 和 $B$ 中最大的那个减一。如果都不是，那么就直接输出 ``Impossible``。


### Code
```c
#include<bits/stdc++.h>
using namespace std;
char hc;
template <class O>
inline void read(O &ie){hc=getchar();ie=0;for(;!isdigit(hc);hc=getchar());for(;isdigit(hc);hc=getchar())ie=ie*10+(hc^48);return;}
const int MAX=1e+9;
const int N=3e+3+10;
string s;
char c;
int x,y,z;
signed main(){
	c=getchar();
	for(;c=='|';c=getchar())x++;
	c=getchar();
	for(;c=='|';c=getchar())y++;
	cin>>s;z=s.size();
    //以上部分是读入，我个人觉得比别的题解简便
	if(x+y+2==z){
		while(x--)cout<<'|';
		cout<<'+';
		while(y--)cout<<'|';
		cout<<"|=";z--;
		while(z--)cout<<'|';
	}else if(x+y==z+2){x>y?x--:y--;
		while(x--)cout<<'|';
		cout<<'+';
		while(y--)cout<<'|';
		cout<<"=|";
		while(z--)cout<<'|';
	}else if(x+y==z){
		while(x--)cout<<'|';
		cout<<'+';
		while(y--)cout<<'|';
		cout<<"=";
		while(z--)cout<<'|';
	}else{
    	cout<<"Impossible";
    }return 0;
}
```

---

## 作者：Szr__QAQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF394A)

[提交记录](https://www.luogu.com.cn/record/109902928)


这题题意明确，这里不再赘述。

------------
**思路**：**模拟**

这题根据题意直接模拟即可，代码比较简单但是非常的长。

首先，我们用 $cnt$ 记录第一个加数的火柴棒的个数，用 $cnt2$ 记录第二个加数的火柴棒的个数，再用 $sum$ 记录第三个火柴棒组中火柴棒的个数，最后再依题意判断加输出即可，具体实现过程在代码中。


------------
**坑点**：

**要特别判断第一个火柴棒组中火柴棒的个数是否为1，如果是1，就只能挪第二组火柴棒！！！**。


------------
**完整代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int qwq=3e2+5;
string s;
int cnt=0,cnt2=0,sum=0,cd;
char c[qwq];

int main()
{
	cin>>s;
	cd=s.size(); 
	int o=0;
	for(int i=0;i<cd;i++)
	{
		if(s[i]=='|') 
			o++;
		if(s[i]=='+')//以加号和等于号分段记录 
		{
			cnt=o;
			o=0;
		}
		if(s[i]=='=')
		{
			cnt2=o;
			o=0;
		}
		c[i]=s[i];
	}
	sum=o;//注意：这里sum记得赋值 
	if(cnt+cnt2==sum)//特判，如果两数之和直接等于第三个火柴棒组中火柴棒的个数就直接输出 
	{
		cout<<s;
		return 0;
	}
	if(cnt==1)//第一个火柴棒组中火柴数量为1的情况，只能挪cnt2 
	{
		if(cnt+cnt2-1==sum+1)//从左边挪1个到右边 
		{
			for(int i=0;i<cd;i++)
			{
				if(c[i+1]=='=')
				{
					continue;
				}
				cout<<c[i];
			}
			cout<<"|";
			return 0;
		}
		if(cnt+cnt2+1==sum-1)//从右边挪1个到左边 
		{
			cd--;
			for(int i=0;i<cd;i++)
			{
				if(c[i]=='=')
				{
					cout<<"|=";
					continue;
				}
				cout<<c[i];
			}
			return 0;
		}
		cout<<"Impossible";//不成立的情况 
		return 0;
	}
	//第一个火柴棒组中火柴数量为不为1的情况
	if(cnt-1+cnt2==sum+1) //从左边挪1个到右边
	{
		for(int i=0;i<cd;i++)
		{
			if(c[i+1]=='+')
			{
				continue;
			}
			if(c[i]=='=')
			{
				cout<<"=|";
				continue;
			}
			cout<<c[i];
		}
		return 0;
	}
	if(cnt+1+cnt2==sum-1)//从右边挪1个到左边 
	{
		cd-=1;
		for(int i=0;i<cd;i++)
		{
			if(c[i]=='+')
			{
				cout<<"|+";
				continue;
			}
			cout<<c[i];
		}
		return 0;
	}
	cout<<"Impossible";//不成立的情况
	return 0;
}
```


------------
本人只是一名小蒟蒻，若有错误请指正，谢谢大家。

---

## 作者：__LiChangChao__ (赞：0)

## 思路
考虑**分类讨论**。

先将这个火柴式子转换为数学式子，设为 $a+b=c$。

当然这个等式可能不成立，那先看看有什么情况最多移动一根火柴时是成立的。

显然有三种情况：

$a+b=c$，即本身就成立。

$a+b+1=c-1$，即从 $c$ 处移动一根火柴棒至 $a+b$。

$a+b-1=c+1$，即从 $a+b$ 处移动一根火柴棒至 $c$。

对后两个式子进行移项，即 $a+b+2=c$ 和 $a+b=c+2$。

然后再特判一下 $a$ 或 $b$ 等于 $1$ 的情况就好啦（显然 $a$ 或 $b$ 不能为 $0$）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int sum[10],cnt=1;//sum[1]就是a，sum[2]就是b，sum[3]就是c 
int main() {
	cin>>s;
	for(int i=0; i<s.length(); i++) {//输入 
		if(s[i]=='+'||s[i]=='=') {//这是另一个数 
			cnt++;
			continue;
		}
		sum[cnt]++;
	}
	if(sum[1]+sum[2]==sum[3])return cout<<s,0;//一样的 
	else {
		if(sum[1]+sum[2]==sum[3]+2) {//判断 
			if(sum[1]>1)sum[1]-=1;//不能为0 
			else if(sum[2]>1)sum[2]-=1;
			sum[3]+=1;
		} else if(sum[1]+sum[2]+2==sum[3]) {
			sum[1]+=1;//直接移 
			sum[3]-=1;
		} else {
			printf("Impossible");//无解 
			return 0;
		}
	}
	for(int i=1; i<=sum[1]; i++)printf("|");//输出 
	printf("+");
	for(int i=1; i<=sum[2]; i++)printf("|");
	printf("=");
	for(int i=1; i<=sum[3]; i++)printf("|");
}
```

---

## 作者：cyz_czy (赞：0)

## CF394A 题解

这道题非常简单，我们只需要输入一个字符串，然后读取左边的两个加数和右边的和，再进行简单枚举即可：

若等式本就成立，则直接输出；若右边两个加数之和与左边的和相差 $2$，那么就可以在一步以内符合成立；否则不能在一步以内使等式成立。

话不多说，上代码！

```cpp
#include <iostream>
#include <string>

std::string l; 
int a,b,c; // a 和 b 是两个加数，c 是和 
int d; //读取 a，b，c 的时候需要的下标 

int du(){
	int s=0;//计数 
	while(l[d]!='+' && l[d]!='=' && d<l.length()) // '+'是第一个数a的节点 ，'='是第二个数b的节点，字符串长度上限是第三个数c的节点 
		d++,s++; //下标增加的同时和增加 
	d++; // 下次再用时直接跳过节点 
	return s; //返回和 
}

void input(){  
	std::cin>>l; //输入字符串 
	a=du();
	b=du();
	c=du(); //读取三个数 
}

void print(int x,int y,int z){
	while(x--)
		printf("|"); //第一个数 
	printf("+");
	
	while(y--)
		printf("|"); //第二个数 
	printf("=");
	
	while(z--)
		printf("|"); //第三个数 
	
	exit(0);
}

int main(){
	input();
	
	if(a+b==c)
		print(a,b,c); //如果本来就成立则直接输出 
	
	if(a-1+b==c+1){ //左边移往右边 
		if(a>1) //判断，若出现非正整数则舍去，优先第一个数 
			print(a-1,b,c+1);
		if(b>1)
			print(a,b-1,c+1);
	}
		
	
	if(a+1+b==c-1)
		print(a+1,b,c-1); //右边移往左边 
	
	printf("Impossible"); //无法在一步以内成立输出'Impossible'
	
	return 0;
}
```

### [AC 记录](https://www.luogu.com.cn/record/108891914)

希望对你有帮助,祝你 AC！

---

## 作者：Jerrycyx (赞：0)

题目要求给定一个可能正确的式子 $a+b=c$，要求将其进行转换得到正确的式子。

因为题目要求“把等号左边移**一根**火柴棒到右边”，所以很容易看出有这几种情况是可以做到的：

$$a+b=c$$

直接就满足条件，不用移动。

$$\begin{cases}
(a-1)+b=(c+1)\\
a+(b-1)=(c+1)\\
\end{cases}$$

分别代表在 $a$ 中移动一根到 $c$,以及在 $b$ 中移动一根到 $c$。

$$\begin{cases}
(a+1)+b=(c-1)\\
a+(b+1)=(c-1)\\
\end{cases}$$

分别代表在 $c$ 中移动一根到 $a$，以及在 $c$ 中移动一根到 $b$。

稍加计算即可将其整理成三个式子：

$$\begin{cases}
a+b=c\\
a+b=c+2\\
a+b=c-2\\
\end{cases}$$

这三种情况是可行的，否则是不行的（输出 `Impossible`）。

注意一点：输出不能为 `||+=||` 或 `+||=||` 的形式（即 $a$ 或 $b$ 为 $0$）。

其它细节看代码：

```cpp
#include<cstdio>
using namespace std;

int a,b,c;

inline void Read()	//用于读入 a,b,c 
{
	char ch=getchar();
	while(ch=='|') a++,ch=getchar();
	ch=getchar();
	while(ch=='|') b++,ch=getchar();
	ch=getchar();
	while(ch=='|') c++,ch=getchar();
	return;
}
inline void Print(int x,int y,int z)	//用于输出指定“|”数量的等式 
{
	for(int i=1;i<=x;i++) printf("|");
	printf("+");
	for(int i=1;i<=y;i++) printf("|");
	printf("=");
	for(int i=1;i<=z;i++) printf("|");
	printf("\n");
	return;
}
int main()
{
	Read();		//输入 a,b,c 
	if(a+b==c) Print(a,b,c);	//情况1：满足条件直接输出 
	else if(a+b==c+2)			//情况2：从左往右移动火柴棒 
	{
		if(a!=1) Print(a-1,b,c+1);		//避免“0+b=c”的情况 
		else Print(a,b-1,c+1);
		/*
		不会出现 a+b=c+2 且 a,b 均为 1，输出 Impossinle 的情况
		因为若出现，则该式子必定为 1+1=0
		而题目中“a,b,c>=1”所以 c 不可能为 0
		故这里不用特判 b!=0 也能 AC 
		*/
	}
	else if(a+b==c-2)	//情况3：从右往左移动火柴棒 
		Print(a+1,b,c-1);	//c-2 为正整数，c-1也必定为正整数，这里也不用特判 
	else printf("Impossible\n");	//若以上情况都不满足，表明不可能得到正确的等式 
	return 0;
}
```

$$\frak{The ~ End}$$

---

## 作者：OoXiao_QioO (赞：0)

# 前言

大佬们这题做的太复杂了，小蒟蒻压根看不懂，但有一个巧妙的方法却几乎没人发现，小蒟蒻下面就给大佬们献丑。

# 题目描述

给你一个火柴棒等式（不一定成立），火柴棒表示为 $|$，而不是 $1$。从两个加数之间的任意一个加数挪一根火柴棒放到和的右边，或者从和挪一根火柴棒放到第一个加数上（注意只能放在第一个加数上），或者不动，问你能不能只挪一根或不动，让火柴棒等式成立（即等号左边的火柴棒数目等于等号右边的火柴棒数目）。

# 思路

相比其他大佬的思路，我认为我的思路比较清晰。

我们可以用三个变量 $\verb!s1,s2,s3!$ 分别表示第一个加数火柴棒数目，第二个加数火柴棒数目，以及和的火柴棒数目。

如果 $(s1-1) + s2 = (s3+1)$，即从第一个加数往和移了一根火柴棒，且等式成立，那么输出 $s1-1$ 个 $|$，一个加号， $s2$ 个 $|$，一个等号和 $s3+1$ 个 $|$。

如果 $s1 + (s2-1) = (s3+1)$，即从第二个加数往和移了一根火柴棒，且等式成立，那么输出 $s1$ 个 $|$，一个加号， $s2-1$ 个 $|$，一个等号和 $s3+1$ 个 $|$。

如果 $(s1+1) + s2 = (s3-1)$，即从和往第一个加数移了一根火柴棒，且等式成立，那么输出 $s1+1$ 个 $|$，一个加号， $s2$ 个 $|$，一个等号和 $s3-1$ 个 $|$。

如果以上都不成立，输出 $\verb!Impossible!$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	//定义 
	int s1,s2,s3,l,i,f;// f 表示现在如果找到了一个 '|'，要往哪个变量上 +1。 
	//如果 f == 1，那么 s1++，如果 f == 2，那么s2++，否则 s3++。 
	char s[1001];
	
	//输入
	scanf("%s",s);
	
	//变量赋值
	 
	s1 = s2 = s3 = 0;//清空 
	f = 1;// f 初值为 1，表示现在是第一个加数的统计时间。 
	l = strlen(s);
	
	//循环 
	
	for(i=0;i<l;i++)
	{
		if(f==1&&s[i]=='|')//如果现在该统计第一个加数且是一根火柴棒 
			s1++;//统计第一个加数的变量 ++。 
		else if(f==2&&s[i]=='|')//如果现在该统计第二个加数且是一根火柴棒 
			s2++;//统计第二个加数的变量 ++。
		else if(f==3&&s[i]=='|')//如果现在该统计和且是一根火柴棒 
			s3++;//统计和变量 ++。
		if(s[i]=='+')//如果 s[i] == '+'，说明统计第一个加数结束，该统计第二个加数了。 
			f = 2;// f = 2，表示该统计第二个加数。 
		if(s[i]=='=')//如果 s[i] == '='，说明统计第二个加数结束，该统计第和了。 
			f = 3;// f = 3，表示该统计和。 
	}
	
	//开始判断
	 
	if(s1+s2==s3)//如果左边两个火柴棒数目和等于和，即不需要做出改变且等式成立 
	{
		for(i=1;i<=s1;i++)//输出 s1 个 '|'。 
			printf("|");
		putchar('+');//输出加号。 
		for(i=1;i<=s2;i++)//输出 s2 个 '|'。 
			printf("|");
		putchar('=');//输出等号。
		for(i=1;i<=s3;i++)//输出 s3 个 '|'。 
			printf("|");
		putchar('\n');//输出换行。
	}
	else if((s1-1)+s2==(s3+1)&&s1-1>0)//如果第一个加数往和移了一根火柴棒而且移动后第一个加数还有火柴棒且等式成立 
	{
		s1--;//模拟第一个加数的一根火柴棒移走了 
		s3++;//模拟和增加一根原属于第一个加数的火柴棒 
		for(i=1;i<=s1;i++)//输出 s1 个 '|'。 
			printf("|");
		putchar('+');//输出加号。
		for(i=1;i<=s2;i++)//输出 s2 个 '|'。 
			printf("|");
		putchar('=');//输出等号。 
		for(i=1;i<=s3;i++)//输出 s3 个 '|'。 
			printf("|");
		putchar('\n');//输出换行。
	}
	else if(s1+(s2-1)==(s3+1)&&s2-1>0)//如果第二个加数往和移了一根火柴棒而且移动后第二个加数还有火柴棒且等式成立 
	{
		s2--;//模拟第二个加数的一根火柴棒移走了 
		s3++;//模拟和增加一根原属于第二个加数的火柴棒 
		for(i=1;i<=s1;i++)//输出 s1 个 '|'。 
			printf("|");
		putchar('+');//输出加号。
		for(i=1;i<=s2;i++)//输出 s2 个 '|'。 
			printf("|");
		putchar('=');//输出等号。
		for(i=1;i<=s3;i++)//输出 s3 个 '|'。 
			printf("|");
		putchar('\n');//输出换行。
	}
	else if((s1+1)+s2==(s3-1)&&s3-1>0)//如果和往第一个加数移了一根火柴棒而且移动后和还有火柴棒且等式成立 
	{
		s3--;//模拟和的一根火柴棒移走了 
		s1++;//模拟第一个加数增加一根原属于和的火柴棒 
		for(i=1;i<=s1;i++)//输出 s1 个 '|'。 
			printf("|");
		putchar('+');//输出加号。
		for(i=1;i<=s2;i++)//输出 s2 个 '|'。 
			printf("|");
		putchar('=');//输出等号。
		for(i=1;i<=s3;i++)//输出 s3 个 '|'。 
			printf("|");
		putchar('\n');//输出换行。
	}
	else//否则不满足移动后等式成立 
		printf("Impossible\n");//输出 Impossible。 
	return 0; 
}
```


---

## 作者：Sternenlicht (赞：0)

思路：

设加号左边 '|' 的个数为 $jia1$，加号右边 '|' 的个数为 $jia2$，等于号右边 '|' 的个数为 $he$。

有四种情况，可分类讨论：

1. $jia1+jia2=he$。这种情况直接输出即可。

2. $jia1+jia2+2=he$。这种情况要将 $he$ 中的一个 '|' 挪到 $jia1$ 或 $jia2$ 上。

3. $jia1+jia2-2=he$。这种情况要将 $jia1$ 或 $jia2$ 上的一个 '|' 挪到 $he$ 中。特别的，若 $jia1$ 为 $1$，则只能挪 $jia2$ 上的；若 $jia2$ 为 $1$，则只能挪 $jia1$ 上的；若两者都 $>1$，则任意挪一个即可。

4. 若上面 $3$ 种情况都不满足，输出   Impossible。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define endl '\n'
using namespace std;

string s;int jia1,jia2,he;
int main(){
	cin>>s;int i,len=s.size();
	for (i=0;s[i]!='+';i++)
		jia1++;
	for (i++;s[i]!='=';i++)
		jia2++;
	for (i++;i<len;i++)
		he++;
	if (jia1+jia2==he){
		for (i=1;i<=jia1;i++)cout<<"|";
		cout<<"+";
		for (i=1;i<=jia2;i++)cout<<"|";
		cout<<"=";
		for (i=1;i<=he;i++)cout<<"|";
		return 0;
	}
	if (jia1+jia2+2==he){
		for (i=1;i<=jia1;i++)cout<<"|";
		cout<<"+";
		for (i=1;i<=jia2;i++)cout<<"|";
		cout<<"|=";
		for (i=1;i<he;i++)cout<<"|";
		return 0;
	}
	if (jia1+jia2-2==he){
		if (jia1==1){
			for (i=1;i<=jia1;i++)cout<<"|";
			cout<<"+";
			for (i=1;i<jia2;i++)cout<<"|";
			cout<<"=";
			for (i=1;i<=he+1;i++)cout<<"|";
		}
		else if (jia2==1){
			for (i=1;i<jia1;i++)cout<<"|";
			cout<<"+";
			for (i=1;i<=jia2;i++)cout<<"|";
			cout<<"=";
			for (i=1;i<=he+1;i++)cout<<"|";
		}
		else{
			for (i=1;i<=jia1;i++)cout<<"|";
			cout<<"+";
			for (i=1;i<jia2;i++)cout<<"|";
			cout<<"=";
			for (i=1;i<=he+1;i++)cout<<"|";
		}
		return 0;
	}
	cout<<"Impossible";
	return 0;
}

---

## 作者：happybob (赞：0)

随便搞，设一开始等式 $a+b=c$，显然 $\left| a + b - c \right| = 2$ 时有解，然后判断是 $c-(a+b)=2$ 还是 $(a+b)-c=2$，模拟即可。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
using namespace std;

string s;
int cnt[5], now, nc = 0;

int main()
{
	cin >> s;
	s += '+';
	for (int i(0); i < s.size(); i++)
	{
		if (s[i] != '|')
		{
			cnt[++now] = nc;
			nc = 0;
		}
		else nc++;
	}
	int t = cnt[1] + cnt[2];
	if (cnt[1] + cnt[2] == cnt[3])
	{
		s.erase(--s.end());
		cout << s << endl;
		return 0;
	}
	if (abs(t - cnt[3]) != 2) printf("Impossible");
	else
	{
		if (cnt[3] - t == 2)
		{
			for (int i(1); i <= cnt[1] + 1; i++) printf("|");
			printf("+");
			for (int i(1); i <= cnt[2]; i++) printf("|");
			printf("=");
			for (int i(1); i < cnt[3]; i++) printf("|");
			puts("");
		}
		else
		{
			if (cnt[1] != 1)
			{
				for (int i(1); i < cnt[1]; i++) printf("|");
				printf("+");
				for (int i(1); i <= cnt[2]; i++) printf("|");
				printf("=");
				for (int i(1); i <= cnt[3] + 1; i++) printf("|");
				puts("");
			}
			else
			{
				for (int i(1); i <= cnt[1]; i++) printf("|");
				printf("+");
				for (int i(1); i < cnt[2]; i++) printf("|");
				printf("=");
				for (int i(1); i <= cnt[3] + 1; i++) printf("|");
				puts("");
			}
		}
	}
	return 0;
}
```


---

## 作者：BetaCutS (赞：0)

## 题目大意

给你一个火柴棒算式，要求最多移动一根火柴，如果能使等式成立，输出等式，否则输出 Impossible。

## 算法

模拟加数、另一个加数、和三者选两个进行火柴移动，如果等式成立，输出并结束程序，如果找不到成立的算式，输出 Impossible。

## 代码

```cpp
string s;
int a[4];
int main()
{
	cin>>s;
	a[1]=s.find('+'),a[2]=s.find('=')-a[1]-1,a[3]=s.size()-a[1]-a[2]-2;//得到加数、另一个加数、和的火柴棒根数
	for(int i=1;i<=3;i++)//加数、另一个加数、和之中火柴选两个来移动
		for(int j=1;j<=3;j++)
		{
			a[i]--,a[j]++;//火柴棒的移动
			if(a[1]&&a[2]&&a[3]&&a[1]+a[2]==a[3])//如果等式成立，输出
			{
				for(int k=1;k<=a[1];k++)
					printf("|");
				printf("+");
				for(int k=1;k<=a[2];k++)
					printf("|");
				printf("=");
				for(int k=1;k<=a[3];k++)
					printf("|");
				return 0;
			}
			a[i]++,a[j]--;//恢复原来
		}
	puts("Impossible");//不可行
	return 0;
}

```


---

## 作者：HuZHUNZHUN (赞：0)

**本蒟蒻的第五篇题解QAQ**

本题思路：

先把原来的式子转化为 $a+b=c$ 的形式，那么：

如果根本就不需要移动，即 $a+b=c$ 成立，那么不用动了，直接输出；

如果需要从右边拿一个到左边，即 $a+b+1=c-1$ 成立，那么 $c$ 减一 $a$ 加一就可以输出了；

如果需要从左边拿一个到右边，即 $a+b-1=c+1$ 成立，那么 $c$ 加一 $a$ 减一，这里需要小细节因为 $a=1$ 时是不能再减的，要从 $b$ 那里拿；

如果以上三条都不满足，那么这个式子没救了。

无注释代码奉上：

```cpp
#include<bits/stdc++.h>
using namespace std;
void print(int x,int y,int z)
{
	while(x--) cout<<"|";
	cout<<"+";
	while(y--) cout<<"|";
	cout<<"=";
	while(z--) cout<<"|";
	cout<<endl;
}
int main()
{
	ios::sync_with_stdio(false);
	string s;
	cin>>s;
	int len=s.length(),x,y;
	for(int i=0;i<len;i++)
	{
		if(s[i]=='+') x=i;
		if(s[i]=='=') y=i;
	}
	int a=x,b=y-x-1,c=len-y-1;
	if(a+b==c)
	{
		print(a,b,c);
		return 0;
	}
	if(a+b+2==c)
	{
		a++;
		c--;
		print(a,b,c);
		return 0;
	}
	if(a+b==c+2)
	{
		if(a>1) a--;
		else b--;
		c++;
		print(a,b,c);
		return 0;
	}
	cout<<"Impossible"<<endl;
	return 0;
}
```

---

## 作者：caibet (赞：0)

### 题意：

给你一个火柴棒表达式，求移动一根或不移动火柴棒能否使表达式成立，若能则输出成立的表达式。

### 解法：

>学霸题，使它成立。
>
>分类讨论法，从左往右数。

这种很多 `或` 字的题肯定要分类讨论了。

然而首先我们需要把数据读进来。

```
|||+||=|||||
```

这种数据怎么读呢？正好，有一个函数 `getline()`，其第一个参数是输入的定向，第二个参数为要读入的字符串（`string`），而可选的第三个参数刚好是我们所需要的——读入的终止字符。于是我们只需要：

```cpp
getline(cin,a,'+');getline(cin,b,'=');getline(cin,c);
```

即可。那么读出来的字符串的长度就是火柴棒的数量。我们设这三堆火柴棒数量分别为 $x,y,z$。

接下来就要分类讨论了——

1. 等式原本就成立

直接输出。

2. 等式不成立，需要从左边移动一根到右边。

这时就有一个问题，是移动 $x$ 还是 $y$ 呢？

既然从一堆火柴棒中移出一根会使数量 $-1$，那么选的火柴棒肯定不能只有一根了。因此我们移走火柴棒数量大于 $1$ 的那一根。

那么会不会有两堆都为 $1$ 根的情况呢？由题意可以知道，这种情况下一定有 $x+y-1=z+1$，则 $x=y=1$ 时 $z=0$，不符合题意。因此我们不需要考虑这种情况。

3. 等式不成立，需要从右边移动一根到左边。

和上面一样，我们可以得到 $x+y+1=z-1$。考虑 $z=1$ 的极端情况，此时 $x+y=-1$，可是 $x,y \geq 1$，因此我们也不需要考虑这种相当离谱的情况，直接把 $z-1$，$x$ 或 $y+1$ 就可以了。

4. 等式不成立，左边也不能移到右边，右边也不能移到左边。

无解。

因此代码就出来了。个人建议写一个函数便于输出。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define return while(1)
int x,y,z;
string a,b,c;
void pt(int n){
	for(int i=1;i<=n;i++) cout<<"|";
}
int main(){
	getline(cin,a,'+');
	getline(cin,b,'=');
	getline(cin,c,'\n');
	x=a.size(),y=b.size(),z=c.size();
	if(x+y==z){
		pt(x);
		cout<<"+";
		pt(y);
		cout<<"=";
		pt(z);
		return 0;
	}
	if(x+y+1==z-1){
		pt(x+1);
		cout<<"+";
		pt(y);
		cout<<"=";
		pt(z-1);
		return 0;
	}else if(x+y-1==z+1){
		if(x>1) x--;
		else y--;
		pt(x);
		cout<<"+";
		pt(y);
		cout<<"=";
		pt(z+1);
		return 0;
	}else cout<<"Impossible";
	return 0;
}
```

>结果算出来，你学会了吗？

---

## 作者：zyh888 (赞：0)

# 题意
给定一个火柴棒等式，问你能不能在最多移动一根火柴棒的情况下使这个等式成立
# 思路
先读入左边等号前的火柴棒数，记作 $a$，代表第一个加数，再读加号与等号之间的火柴棒个数，记作 $b$,代表第二个加数，最后读和，记作 $c$。

在这里能成立的条件就只有两种：

  - 1、无需移动小棒：$a+b=c$，左右两边无需变动。

  - 2、需要移动一根小棒：

	- 在这种情况中，两边的差必须为 $2$。很好证明：将小的一边的一根小棒移到右边，这时这个等式小的一边多了 $1$，大的一边少了 $1$，这个等式就恒成立了。
    
	- $a+b+2=c$，也就是 $c$ 比 $a+b$ 大 $2$,这种情况也很好处理，只需将 $c$ 的一根小棒移到 $a$。
    
	- $a+b=c+2$，这种情况是不是直接将 $a$ 的一根小棒移到 $c$ 呢？并不是，这里有一处细节，题目中的数据 $1\leqslant a \leqslant 100$，也就是说 $a$ 是可能等于 $1$ 的，在 $a = 1$，的情况下把 $a$ 减去 $1$，$a$ 的位置就空了。所以对于 $a$ 等于 $1$ 的情况，将 $b$ 的一根小棒移到 $c$ 即可。
# code
```c
#include<bits/stdc++.h>
using namespace std;
int a1,b,c;
int main(){
	char ch; 
	while(ch!='+'){ch=getchar(); a++;} //第一个加数
	while(ch!='='){ch=getchar(); b++;} //第二个加数
	do{ch=getchar(); c++;}while(ch=='|'); //和
	a--;b--;c--; //每次统计都会多读一个字符所以需要-1
	if(a+b!=c){ 
		if(abs(a+b-c)^2){ //在a+b!=c且两边的差不等于2就无解
			puts("Impossible");
			return 0;
		}else{
			if(a+b<c){ //只需移动一根小棒的第一种情况，将和的减去1，第一个加数加上1
				a++;
				c--;
			}else{
				if(a^1){ //第二种情况，需要特判
					a--; //如果a不等于1，就把它的1移到c
					c++;
				}else{
					b--; //如果a等于1，移了它就空了，所以把b的1移到c
					c++;
				}
			}
		}
	}
	while(a--) printf("|");	
	printf("+");
	while(b--) printf("|");
	printf("=");
	while(c--) printf("|"); 
	return 0;
}
```



---

## 作者：BCZSX (赞：0)

发现这一题~~又是恶意评分~~是一道~~紫题~~……
具体的讲解就看代码吧qwq
```cpp
#include<cstdio>
#include<cstring>//这个头文件用或不用都可以
using namespace std;
char s;
int a,b,c,t=1;
int main()
{
	while(scanf("%c",&s)!=EOF)//一个一个输入字符，直到为换行符
	{
		if(s=='|')
		{
			if(t==1) a++;//a存储‘+’号前的棒子个数
			else if(t==2) b++;//b储存‘+’号后面‘=’号的棒子个数
			else c++;//c储存‘=’号后面的棒子个数
		}
		else t++;//t用来划分‘+’号和‘=’号前后
	}
	if(a+b==c)//判断a+b是否等于c，是则直接输出答案
	{
		for(int i=1;i<=a;++i) printf("|");
		printf("+");
		for(int i=1;i<=b;++i) printf("|");
		printf("=");
		for(int i=1;i<=c;++i) printf("|");
		return 0;
	}
	if(a+b==c-2)//判断是否需要从‘=’号左边拿一根火柴到右边，是则直接输出答案
	{
		for(int i=1;i<=a+1;++i) printf("|");
		printf("+");
		for(int i=1;i<=b;++i) printf("|");
		printf("=");
		for(int i=1;i<c;++i) printf("|");
		return 0;
	}
	if(a+b==c+2)//判断是否需要从‘=’号右边拿一根火柴到左边，是则输出
	{
		if(a>b) a--;
		else b--;
		for(int i=1;i<=a;++i) printf("|");
		printf("+");
		for(int i=1;i<=b;++i) printf("|");
		printf("=");
		for(int i=1;i<=c+1;++i) printf("|");
		return 0;
	}
	else//均不满足上面条件，则不能构成等式，输出Impossible
	{
		printf("Impossible");
		return 0;
	}
    //完美结束
}
```

---

## 作者：CobaltChloride (赞：0)

```
#include<bits/stdc++.h>
using namespace std;
string s;
int a,b,c,l,i;
int main(){
	cin>>s;
	l=s.length();
	for(i=0;i<l;i++){
		if(s[i]=='+'){
			a=i;
			break;
		}
	}//求出a
	for(i=i+1;i<l;i++){
		if(s[i]=='='){
			b=i-a-1;//注意减去一个字符'+'
			break;
		}
	}//求出b
	c=l-a-b-2;//注意减去两个字符'+''='
	if(a+b==c) cout<<s;//正好相等
	else if(a+b==c+2){//从加数移到和
		if(a==1){
			cout<<"|+";
			for(i=3;i<l;i++) cout<<s[i];
			cout<<'|';
			//如果a==1则只能移除b的一根,题中说a,b,c>0,所以a==1时b一定不等于1
			//注意该特判一定要加,否则WA#22 
		}
		else{
			for(i=1;i<l;i++) cout<<s[i];
		    cout<<'|';
		}//否则移除a的
	}
	else if(a+b==c-2){//从和移到加数
	    cout<<'|';
		for(i=0;i<l-1;i++) cout<<s[i];
	}
	else cout<<"Impossible";//不可能 
	return 0;
}
```

---

## 作者：哔哩哔哩 (赞：0)

一道比较有意思的题目

翻译

> 给一个火柴棍加法算式，只从加数或和上移动一根火柴，使等式成立。

一个简单的模拟

虽然我做了好多好多次才过

（CF专业掉分）

大致思路就是统计+左右和=后面的火材棒数量

~~然后分类讨论~~

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int a,b,c,cnt;
int main()
{
    cin>>s;
    int len=s.size();
    for(int i=0;i<len;i++)
    {
        if(s[i]=='+')
        {
            a=cnt;
            cnt=0;
        }
        else if(s[i]=='=')
        {
            b=cnt;
            cnt=0;
        }
        if(s[i]=='|') cnt++;
    }
    c=cnt;
    if(a+1+b==c-1)
    {
        for(int i=0;i<a+1;i++) putchar('|');
        putchar('+');
        for(int i=0;i<b;i++) putchar('|');
        putchar('=');
        for(int i=0;i<c-1;i++) putchar('|');
        return 0;
    }
    else if(a+b==c)
    {
        for(int i=0;i<a;i++) putchar('|');
        putchar('+');
        for(int i=0;i<b;i++) putchar('|');
        putchar('=');
        for(int i=0;i<c;i++) putchar('|');
        return 0;
    }
    else if(a+b-1==c+1)
    {
    	if(a>1){
    		for(int i=0;i<a-1;i++) putchar('|');
        	putchar('+');
        	for(int i=0;i<b;i++) putchar('|');
        	putchar('=');
		}
        else{
        	for(int i=0;i<a;i++) putchar('|');
        	putchar('+');
        	for(int i=0;i<b-1;i++) putchar('|');
        	putchar('=');
		}
        for(int i=0;i<c+1;i++) putchar('|');
        return 0;
    }
    else printf("Impossible");
    return 0;
}
```

(可能被hack)

刷刷水题弥补退役的伤心的心ing

---

