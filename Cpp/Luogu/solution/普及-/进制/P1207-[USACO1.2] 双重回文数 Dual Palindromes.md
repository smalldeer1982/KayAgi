# [USACO1.2] 双重回文数 Dual Palindromes

## 题目背景

如果一个数从左往右读和从右往左读都是一样，那么这个数就叫做“回文数”。例如，$12321$ 就是一个回文数，而 $77778$ 就不是。当然，回文数的首和尾都应是非零的，因此 $0220$ 就不是回文数。

事实上，有一些数（如 $21$ ），在十进制时不是回文数，但在其它进制（如二进制时为 $10101$ ）时就是回文数。

## 题目描述

给定两个十进制数 $n,s$，然后找出前 $n$ 个满足大于 $s$ 且在不少于两种进制（二进制至十进制）上是回文数的十进制数，输出到文件上。

本问题的解决方案不需要使用大于 $32$ 位的整型数



## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 15$，$1\le s \le 9999$

题目翻译来自NOCOW。

USACO Training Section 1.2


## 样例 #1

### 输入

```
3 25
```

### 输出

```
26
27
28
```

# 题解

## 作者：stone_juice石汁 (赞：118)

### 咱不谈什么高级算法，什么高深模拟，甚至转化进制都不需要。

### 并且，算法复杂度最高仅为$O(n+300)$

### 更加NB的是，main里的代码仅仅4行！

那么你可能要问我是什么代码这么NB。

**答案就是：打表无敌！！！！**

```
#include<bits/stdc++.h>
using namespace std;
int num[300]={0,1,2,3,4,5,6,7,8,9,10,15,16,
17,18,20,21,24,26,27,28,31,
33,36,40,45,46,50,51,52,55,
57,63,65,67,73,78,80,82,85,
88,91,92,93,98,99,100,104,105,107,
109,111,114,119,121,127,129,130,135,141,
142,150,151,154,160,164,170,171,173,178,
182,185,186,191,195,200,203,209,212,215,
219,227,235,242,246,252,255,257,264,273,
282,292,300,313,316,325,328,333,341,342,
343,357,364,365,373,381,393,400,414,427,
434,438,446,455,464,471,484,495,511,513,
546,555,560,564,585,624,626,644,646,651,
656,666,676,692,693,701,717,728,730,757,
771,777,787,819,820,856,868,910,939,975,
1023,1025,1066,1105,1221,1285,1312,1365,1432,1441,
1460,1539,1550,1640,1667,1755,1885,2000,2188,2268,
2293,2550,2565,2709,2730,2910,2920,2925,2997,3069,
3074,3075,3280,3315,3550,3591,3640,3663,3735,3740,
3855,3951,3999,4095,4097,4161,4225,4257,4289,4369,
4433,4593,4617,4681,5001,5049,5125,5189,5397,5461,
5740,5840,5854,6148,6200,6560,6562,6643,6697,6724,
6761,6825,6886,6889,6953,7300,7373,7381,7409,7447,
7462,7517,7667,7703,7777,7801,7997,8038,8119,8194,
8200,8258,8281,8322,8386,8578,8778,8802,9009,9103,
9201,9222,9490,9958,10252,10308,10658,10794,10858,10922,
10986,11253,11314,11757,11898,11950,12291,12355,12419,12483, 
12547,12654,12691,13107,13124,13131,13205,13286,13299,13331};
int n,s,g;
int main()
{
	cin>>n>>s;
	for(g=1;num[g]<=s;g++);
	for(int i=0;i<n;i++)cout<<num[g+i]<<endl;
	return 0;
}
```

**你要是看这个代码还不会，算我输。**

## 当然，你可能会问，这个表是从哪里来的？

**~~答：我会手算！~~**

**答：我会写代码！**

那么怎么写这个代码呢？

## **注意：下面要开始介绍打表的技巧，这些技巧可能会在比赛中用到**

### **这些技巧仅适用于较难题~~以及懒得写代码~~。实乃骗分好法。**

- ### 第一步

看题目，**我们要求的是满足至少两个进制的回文数对吧。**

那么我们先新开一个源码求每个进制下的回文数。

**稍微思考一下，我们可以把回文数看做一个数正着输一遍，在倒着输一遍。（如果是奇数位中间的数只输1次）** 那么我们的**第一份源码**就出来了。

我们可以用for套for套for....这个代码求每个进制下的回文数，听起来不难是吧？>.<

**由于是不同进制，所以我们要加上限制条件。即每一位枚举不能大于$k$，$k$为进制数。**然后我们就可以愉快的输出。（记得用$freopen$！）

下面展示了一个求4进制7，8位回文数的过程。**当然这个代码可以运行9次。只需要把限制条件4改为2-10中的另一个数再运行就可以了。要求其他位数的回文数只需要增减for循环个数以及cout个数就可以了。**

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	for(int a=1;a<4;a++)
		for(int b=1;b<4;b++)
			for(int c=1;c<4;c++)
				for(int d=1;d<4;d++)//你要是够莽，可以开更多for
				{
					cout<<a<<b<<c<<d<<c<<b<<a;
					cout<<a<<b<<c<<d<<d<<c<<b<<a;
				}	
}
```
当然听起来好像是很麻烦，但是做起来的效率其实蛮高了。**如果你还是嫌麻烦，你可以写个递归，用改变量的方式替代改for于cout。**

好了，我们得到了各个进制下的回文数。

（什么！你把数据丢了？我叫过你用$freopen$吧？）

- ### 第二步：

我们现在需要把你得到各个进制下的回文数全部转化为10进制。

这个实现很简单吧。那就直接上代码了！

记住要加$freopen$！别看我没加！~~我懒~~

```
#include<bits/stdc++.h>
using namespace std;
int n,k,ans;//其中,k代表进制。可以自行修改
int main()
{
	while(cin>>n)
	{
		for(int i=0;n;i++)//其中i为进制位数，为累乘服务
		{
			int tmp=n%10;//取最后一位
			else for(int j=1;j<=i;j++)tmp*=k;
			ans+=tmp;
			n/=10;//丢最后一位
		}
		cout<<ans<<" ";
	}
}
```

- ### 第三步

现在你得到的回文数全是10进制了。但是题目要求必须同时满足两种进制的回文数才算。

我们怎么做呢？

非常简单！你刚刚得到了9个文件对吧？他们记录了各个进制的回文数，并且全部转化为了10进制。

**那么就上黑科技：Ctrl+C and Ctrl+V**

简而言之，就是把所有的数据贴在一个文件里。

**然后你就可以很快乐的用一个判重代码来输出那些出现次数多余2的数字。**

记住要$freopen$！！（话说这是第几回提醒了...）

### 到此为止！你就得到了一个表!

~~是不是被我的骗分方法感动了~~

# 总结
**虽说打表暴力无情，但是其实打表也有他独特的方法。如果你能在适当时间进行打表，那么你总能占到一些便宜。上面那个题不是很难，可能还没到打一个表的地步。但是我这里着重展示了打表的方法。希望对各位OIer有帮助！**

---

## 作者：wxy_god (赞：47)

普通的暴力枚举做法不说了，某位巨佬已经讲完了

我们会发现，整个程序中最复杂的部分就是转换进制的部分，这位巨佬是手写的。但在这里我要给大家介绍一个函数：$itoa$！

### $itoa$函数是用来干啥的

$itoa$是$integer$ $to$ $ascii$的缩写。此函数能够将一个$int$类型的数存到一个数组里。不过这可不是简单的复制，它还能够转换进制！

让我们看看库形参：```itoa(int _Val, char *_DstBuf, int _Radix)```。第一个```_Val```是你要转换的数，第二个```*_DstBuf```传进去的是一个```char *```类型的（意思是传进去一个数组），代表你要赋值的数组。第三个```_Radix```就是你要转换的进制了。

### $itoa$的问题

- $Linux$下并没有$itoa$函数！所以千万不要再$NOIp$或洛谷上使用$itoa$函数，否则会$CE$！

- $itoa$函数再转换成大于$10$进制的时候是小写字母。所以如果题目要输出大写字母的话还要单处理。

注：虽然$itoa$并不能在$NOIp$上用，但可以在非$Linux$的环境下的比赛使用并且此函数非常有用。

综上所述，$itoa$最主要的作用是转换进制。

**核心代码：**

```
    for(int i = n + 1; ; i ++ ) {//暴力枚举
    	int Counter = 0;//i是不是双重回文数
    	for(int j = 2; j <= 10; j ++ ) {/2到10进制枚举
    		if(i % j == 0) continue;//如果末尾是0，直接枚举下一种
    		itoa(i, str, j);//转换进制
    		if(check(str) == true) {//check函数是用来判断str是不是回文串的，代码就不放了
    			Counter ++ ;
            }
            if(Counter == 2) break;
        }
        
        if(Counter == 2) {
            printf("%d\n", i);
            counter ++ ;//这是大的计数器
        } 
        
        if(counter == s) exit(0);
    } 

```

### 如果您觉得还行的话请到顶部点个赞吧

---

## 作者：Sino_E (赞：31)

跟USACO的上一题简直就是配套水题大礼包【滑稽】

上一题没改几个字就到了这一题。

思路：枚举，按照题目思路判断答案是否合法。重点在于k进制转换和判断回文，这是比较基础也比较常见的内容。

下面提供比较简洁的代码实现。

```cpp
#include<bits/stdc++.h>
using namespace std;

bool ispal(int n,int k){
    short res[100]={0},p=0;//res里装的是转换后的k进制数
    while(n){
        res[p++]=n%k;
        n/=k;
    }//10转2进制怎么转，10转k进制就怎么转——模拟短除法。当然这么搞到的k进制数在数组里是个反的。 
    //即使数字反了，因为只用判断是不是回文，所以可以不用管。
    //再者，如果是回文，那反不反转好像没啥区别.... 
    int i=0,j=p-1;
    while(i<j)
        if(res[i++]!=res[j--])return 0;        //判断是不是回文
    return 1;
}

int main(){
    int n,s;
    cin>>n>>s;
    int ans=0;
    for(int i=s+1;ans!=n;i++){
        int cnt=0;
        for(int j=2;j<=10&&cnt<2;j++){
            if(ispal(i,j))cnt++;//在j进制下i为回文数，计数cnt++ 
        }
        if(cnt>=2)printf("%d\n",i),ans++;//若计数不小于2，则输出，答案计数ans++ 
    }
    return 0;
}
```

---

## 作者：开挂老司机 (赞：10)

看了好几个题解，好像其他大佬都是累加数，再从二到十一个一个转进制的啊-_-

这里给一种更省时间的方法：
## 进制加
把每个进制的数各存进一个数组里，二进制逢二进一，三进制逢三进一，以此类推

代码奉上：
```
#include<iostream>
#include<cstdio>
using namespace std;
inline int read()//快速读入
{
    int neg=1,x=0;
    char c;
    while((c=getchar())<'0'||c>'9')
      if(c=='-')
        neg=-1;
    x=c-'0';
    while((c=getchar())>='0'&&c<='9')
      x=x*10+(c-'0');
    return neg*x;
}
int a[11][101];//保存2~10进制的数值
bool check(int x)//回文判断
{
	int head=1,tail=a[x][0];//头尾指针
	while(head<tail)
	{
		if(a[x][head]!=a[x][tail])//如果头尾指针对应的数不相等，直接返回0
		  return 0;
		head++,tail--;//头指针加，尾指针减
	}
	return 1;//返回1
}
int main()
{
	int n=read(),k=read(),t;//读入n、k(s)
	for(int i=2;i<=10;i++)
	{
		t=k;
		while(t>0)
		{
			a[i][++a[i][0]]=t%i;
			t/=i;
		}
	}//这个for循环是吧k转化成2~10进制
	int ans=0,step,sum,num=k;//定义各数并初始化回文个数
	while(ans<n)
	{
		sum=0;
		num++;//数字加一
		for(int i=2;i<=10;i++)
		{
			a[i][1]++;//最低位加一
			step=1;//将数位改为1
			while(a[i][step]==i)//逢i进一
			{
				a[i][step]=0;
				a[i][++step]++;
				if(step>a[i][0])
				  a[i][0]++;
			}//进制加
			if(check(i))
			  sum++;
		}
		if(sum>=2)//如果这个数在两个以上进制为回文数
		  cout<<num<<endl,ans++;//输出这个数并将个数加一
	}
	return 0;//结束喽(￣▽￣)~*
}
```
给个好评呗O(∩_∩)O谢谢

![](http://p0.so.qhimgs1.com/bdr/_240_/t0136de3c3a4c871b30.jpg)

---

## 作者：sycqwq (赞：6)

__思路__：这一题，可以 __完全枚举__ ，先从s+1开始循环，一直到找到n个双重回文数之后退出循环。

__核心代码__ :

```cpp
int pd(int n,int k)//判k进制下的n是不是回文数
{
	int p[1005];
	int t=0;
	while(n!=0)//进制转换法，辗转相除法的模拟，如果实在不会，可以尝试背下来
	{
		p[++t]=n%k;
		n/=k;
	}
	for(int i=1,j=t;i<=t/2;i++,j--)//判断是否回文，i指向最前，j指向最后，一个一个比较看是否相同，不相同直接返回0
		if(p[i]!=p[j])
			return 0;
	return 1;//因为如果不是回文的话就已经退出函数来，能执行到循环结束就代表是回文数
}

```

__完整代码__（加入少量注释）：


```cpp
#include<bits/stdc++.h>
using namespace std;
int pd(int n,int k)//解释过了，不多说。
{
	int p[1005];
	int t=0;
	while(n!=0)
	{
		p[++t]=n%k;
		n/=k;
	}
	for(int i=1,j=t;i<=t/2;i++,j--)
		if(p[i]!=p[j])
			return 0;
	return 1;
}

int main(){
	int n,s,ans=0;//ans为已经找到的个数
	cin>>n>>s;
	for(int i=s+1;ans<n;i++)
	{
		int count=0;//count代表i在几个进制下是回文的
		for(int j=2;j<=10;j++)//2~10进制枚举
			if(pd(i,j)==1)//判断，若j进制下是回文就count++
				++count;
		if(count>=2)//如果多于两个就代表是双重回文数
		{
			++ans;
			cout<<i<<endl;
			
		}
	}
    return 0;
}

```

---

## 作者：Chaos1018 (赞：4)

/\*

请勿复制,创建美好题解


\*/
###乍一看,这道题不就跟上道题回文平方数一毛一样吗?

##然而的确是一毛一样

###让我强行找一个~~不算重点的~~重点吧--要从M+1开始枚举.

我直接贴代码吧

```cpp
/*
ID: czj20052
LANG: C++
TASK: dualpal
*///不要在意这些细节~~USACO上要的
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
using namespace std;
int a[10000];
int l1,l2;
int hw()//判断回文的函数拉
{
    for (int i=1;i<=l1/2;i++)
        if (a[i]!=a[l1-i+1])
            return 0;
    return 1;
}
int pd(int k,int n)//转化进制的小函数
{
    l1=0;
    do
    {
        a[++l1]=k%n;
        k/=n;
    } while (k!=0);
    return 0;
}
int main()
{
    freopen("dualpal.in","r",stdin);
    freopen("dualpal.out","w",stdout);//温馨提示,抄代码的记得删掉
    int n,m;
    cin>>n>>m;
    int i=m+1;//这里要注意!!!
    int k=0;
    while(k<n)//K是记输出了几个数的计数器
    {
        int ans=0;
        for(int j=2;j<=10;j++)//从二进制到十进制一一枚举
        {
            memset(a,0,sizeof(0));//每次记得把这个数组清零
            pd(i,j);
            if(hw()==1)
             {
                 ans++;
             }
        }
        if(ans>=2)//如果有两种以上的进制是回文的,那么输出,K++
        {
            cout<<i<<endl;
            k++;
        }
        i++;
    }
    return 0;
}```
其实就是一道枚举入门题,相信你们都能做出来的拉


---

## 作者：封禁用户 (赞：3)

请注意：此方法当且仅当编译器支持C++11及以上标准时即可食用，NOIP/NOI等竞赛编译器默认不打开C++11支持。

模拟，辅助函数：

①转进制：用stl的栈和string实现（其实只用string实现就可以了。。。。）

②判断回文：读入一个string，再创建这个string的副本，然后将副本反转（stl的reverse()函数），最后判断是否相等即可

主函数：用k来记录进制数，用x来记录个数，模拟即可

详细C++11的函数的调用处请看代码（话说C++11真好用2333）

```cpp
#include<cstdio>
#include<string>
#include<iostream>
#include<stack>
#include<algorithm>

using namespace std;

stack<int> s;

string changeSys(int num,int sys){
	do{
		s.push(num % sys);
		num /= sys;
	}while(num != 0);
	
	string ans = "";
	while(s.size()){
		ans += to_string(s.top());//to_string()当且仅当C++11下可用，可以将int/double/long long等类型转换为string类型 
		s.pop();
	}
	
	return ans;
}

bool isPal(string s){
	string ss = s;
	reverse(ss.begin(),ss.end());
	
	return ss == s ? true : false;
}

int main(){
	int n,s;
	scanf("%d %d",&n,&s);
	
	int k = 0,x = 0;
	for(int i = s + 1;i <= 666666;i++){
		for(int j = 2;j <= 10;j++){
			if(isPal(changeSys(i,j))){
				k++;
			}
		}
		
		if(k >= 2 && x < n){
			printf("%d\n",i);
			x++;
		}
		
		if(x == n){
			break;
		}
		
		k = 0;
	}
	
	return 0;
}
```

---

## 作者：Sshenyyyu (赞：2)

# 双重回文数
这题，本蒟蒻使用暴力枚举做的，从s+1一直往后找，找到答案就++，知道满足ans==n就跳出。
贴代码。。。
```
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
#include <iostream>
using namespace std;

const int Maxn=10001;

int n,s;
int a[Maxn],cnt;

bool is_ok(int x,int k)//判断是否在k进制下满足回文数
{
	cnt=0;
	while(x>0) {//转成k进制
		a[++cnt]=x%k;
		x/=k;
	}
	for(int i=1; i<=cnt/2; i++)//判断是否回文
		if(a[i]!=a[cnt-i+1])
			return false;//一旦找到一个不回文的数，直接返回假
	return true;
    //转成k进制之后，虽然是k进制下反向的，但如果是回文数，那么反转过后依然是回文数，所以，就不需要再次反转了
}

int main()
{
	cin>>n>>s;
	int ans=0;
	for(int i=s+1; ans!=n; i++) {//枚举从大于s的第一个数开始
		int sum=0;
		for(int j=2; j<=10; j++)//枚举2~10进制
			if(is_ok(i,j)==true)
				sum++;//累计可以的进制
		if(sum>=2) {//如果可行的进制大于等于2，就输出，并累加答案
			cout<<i<<endl;
			ans++;	
		}
	}
	return 0;
}

```

---

## 作者：AFOier (赞：2)

其实就是一大水题

#要注意的有以下几点

1.没有1进制

2.是从s+1开始判断的

3.先输入要判断几个数再输入从几+1开始

这三点过关了，这道题目就简单了

30行秒过，当然还可以更简单

话不多说，附上代码：

```cpp

#include <iostream>
#include <string>
using namespace std;
int jzzh(long long int s,int i)
{
    long long int ss=s; //搞了一个ss来作s的替身 
    string ds="",zs=""; //两个字符串，ds=倒数，zs=正数，差不多就行 
    while(ss!=0)
    {
        ds+=(ss%i)+48; //注意要+48，因为要变成字符 
        ss/=i; //10进制转n进制（n<=10）的公式 
    }
    for(int j=ds.size()-1;j>=0;j--)
    zs+=ds[j]; //把它反过来 
    if(zs==ds)return 1; //判断回文数 
    else return 0;
}
int main()
{
    long long int s,m; //定义参数 
    cin>>m>>s; //输入 
    while(m>=1) //如果m大于等于1就循环，等于m!=0 
    {
        s++; //数字+1 
        int s1=0; //用于判断有几个进制是回文数的参数，赋初值为0 
        for(int i=2;i<=10;i++)
        {if(jzzh(s,i)==1)s1++;} //判断，如果是回文数，s1++ 
        if(s1>=2){cout<<s<<endl;m--;} //如果条件成立，打印，m-- 
    }
}

```

---

## 作者：封禁用户 (赞：1)

一道进制题。

>给定两个十进制数 $n$,$s$，然后找出前 $n$ 个满足大于$s$ 且在不少于两种进制（二进制至十进制）上是回文数的十进制数，输出到文件上。

很显然，用枚举法做。

思路：

定义两个自定义函数。一个用来将$x$变成$2\sim10$进制的数，另一个用来判断当前进制的数是否为回文数。

主程序中，循环枚举答案，调用两个自定义函数，如果这个数的两种进制是回文数，$t+1$，输出这个数。

如果已经找到$n$个数了，那就可以结束了。

进制转换的自定义函数：

```cpp
int pd(int x) {
	int y=0,z;
	memset(b,0,sizeof(b));
	for(int i=2; i<=10; ++i) {
		m=0;
		z=x;
		while(z!=0) {
			b[++m]=z%i;
			z/=i;
		}
		//for(int j=1; j<=m; ++j) printf("%d ",b[i]);
		if(ppdd()) y++;
		if(y>=2) return 1;
	}
	if(y>=2) return 1;
	return 0;
}
```

判断是否为回文数的自定义函数：

```cpp
int ppdd() {
	int l=1,r=m;
	while(l<=r) {
		if(b[l]!=b[r]) return 0;
		l++;
		r--;
	}
	return 1;
}
```

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int s,n,t=0,b[1001],m;
int ppdd() {
	int l=1,r=m;
	while(l<=r) {
		if(b[l]!=b[r]) return 0;
		l++;
		r--;
	}
	return 1;
}
int pd(int x) {
	int y=0,z;
	memset(b,0,sizeof(b));
	for(int i=2; i<=10; ++i) {
		m=0;
		z=x;
		while(z!=0) {
			b[++m]=z%i;
			z/=i;
		}
		//for(int j=1; j<=m; ++j) printf("%d ",b[i]);
		if(ppdd()) y++;
		if(y>=2) return 1;
	}
	if(y>=2) return 1;
	return 0;
}
int main() {
	scanf("%d%d",&n,&s);
	for(int i=s+1; t<n; ++i) {
		if(pd(i)) {
			++t;
			printf("%d\n",i);
		}
	}
	return 0;
}
```

给出一组数据方便大家调试：

$P1207.in$

```cpp
9 10
```

$P1207.out$

```cpp
15
16
17
18
20
21
24
26
27
```

>PS：以上数据仅供调试，请不要用于其他途径。

---

## 作者：Ufowoqqqo (赞：1)

蒟蒻来也[delete]（最近脑子不好使，只能刷些题激活一下沉睡的脑细胞了）[/delete]！

按照题意模拟，枚举大于s的整数，转进制，判回文。

当然，数据大的时候还可以有另一种解法：先把s+1从2到10进制转一次，判回文的时候直接判数组就好；然后每次+1就不用再转进制了，直接写高精进制加→\_→

```delphi

var
 n,s,m,i,j,t:longint;

function judge(s:ansistring):boolean;//判回文
var i:longint;
begin
 if (s[1]='0') or (s[length(s)]='0') then exit(false);//特判
 judge:=true;
 for i:=1 to length(s) div 2 do//判一半长度就够了
  if s[i]<>s[length(s)-i+1] then exit(false)
end;

function work(m,n:longint):ansistring;//转进制
begin
 work:='';
 repeat
  if m mod n>9 then work:=chr(m mod n+55)+work else work:=chr(m mod n+48)+work;
  m:=m div n
 until m=0
end;

begin
 read(n,s);
 i:=s+1;
 m:=0;
 repeat
  t:=0;
  for j:=2 to 10 do if judge(work(i,j)) then inc(t);
  if t>1 then
   begin
    writeln(i);
    inc(m)
   end;
  inc(i)
 until m=n
end.

```

---

## 作者：一碗粥 (赞：1)

发题解了！

首先，大多数渣渣肯定和我一样，看到这题后

repeat
思路全无；

生成法？可以吗？太复杂了；

until（看到“本问题的解决方案不需要使用大于32位的整型 ”）；

随后决定：枚举（虽然贴了标签）。

怎么枚举？多大的范围？题目中没有明确地标出，但从上句可以看出范围一定在maxlongint以内，于是就决定枚举到maxlongint。（原因：首先，不能再大了，其次，我们可以运用剪枝来将时间复杂度降到最短，下面的标程中会标注出）

在这里，我们可以用search(i,j)来表示十进制数i(i<=maxlongint)在j进制下是不是回文数，所以有必要把search变成function：boolean(虽然没有硬性规定），这里我怕错，就多做了几个特判，于是又多了几个剪枝，我估计我这种方法能ac就是

1.剪枝剪得还行；2.luogu神机不解释

标程参上：

```delphi
var i,j,k,l,m,n,s,sum,max,ll:longint;
    s1,s2:string;
function search(x,y:longint):boolean;
var ans,mid,t,w:longint;
    a:array[1..100000]of longint;
begin
  ans:=0;//还是0一下比较好
  repeat
  inc(ans);
  a[ans]:=x mod y;
  x:=x div y;
  until x=0;//转化成j进制
  if ans mod 2=0 then//分两种情况
  begin
    t:=1;
    w:=ans;
    repeat
    if a[t]<>a[w] then exit(false);//这里比较重要，如果不是直接退出
    inc(t);dec(w);
    if a[t]<>a[w] then exit(false);//两重特判，如果是回文数就一定不怕的，真金不怕火炼
    until (t+1=w)or(w+1=t);//手模出来的结果
    if a[1]<>0 then exit(true);
  end
  else
  begin
    if ans=3 then begin if (a[1]=a[3])and(a[1]<>0) then exit(true) else exit(false);end;//三位数的话直接判断就好了
    if ans=1 then exit(true);//一位数一定是回文数
    t:=1;
    w:=ans;
    repeat
    if a[t]<>a[w] then exit(false);
    inc(t);dec(w);
    if a[t]<>a[w] then exit(false);//同上
    until t=w;
    if a[1]<>0 then exit(true);
  end;
end;
begin
  read(n,s);
  max:=maxlongint;//定义到最大值
  for i:=s+1 to max do//开始枚举数字
  begin
  if sum=n then halt;//剪枝1：已达到n的值就halt；大家应该都会
  l:=0;
    for j:=2 to 10 do
    begin
      if search(i,j) then inc(l);//如果是，inc（l），很简单
      if l=2 then begin writeln(i);inc(sum);break;end;//这种直接跳出一重循环就好了
    end;
  end;
end.
```
感谢阅读


---

## 作者：AutumnTripod906 (赞：0)

**这是一道可以巩固进制转换和模拟的好题目。**

**为了方便新手阅读，我就用比较好理解的方法来讲解。**


------------

### 本题的思路：

#### 枚举前n个大于s的数，看它是否满足在两种或两种以上进制（二进制至十进制）上是回文数的十进制数。如果满足，输出。



------------

因为本题涉及**进制转换**，就先讲一下这个。如果您了解此知识，可以直接跳过。

### 1.  什么是进制

**进制也就是进位计数制，是人为定义的带进位的计数方法（有不带进位的计数方法。**

**说简单点，可以用一个例**（栗）**子来说明。 当我们统计选票时，可能会用“正”字记数法。每满5个就写出一个“正”字。这就是一种进制**

### 2. 如何实现进制转换

本题需要用的进制转换方法是**短除法**。框架如下：

```cpp
string s;
while(要转换的数不为0时)
{
	s=char(要转换的数%要转成的进制+'0')+s;
	要转换的数/=要转成的进制；
}
```


------------

### 代码 && 讲解

思路详见本题解开头。

**请勿抄袭！**

```cpp
#include<iostream>
#include<string>
using namespace std;
bool turn(int n)
{
	int a[9]={n,n,n,n,n,n,n,n,n},jz=2,temp=0,x=0;
		// a数组存储了2...10进制转换需要用的n，jz为当前要转换的进制，temp为这个数满足的进制个数，x控制a数字的下标 
	while(temp<=2&&jz<=10)	//当这个数满足的进制个数≤2且 前要转换的进制≤10时 
	{
		string s="";
		while(a[x])		//利用短除法进行转换 
		{
			s=char(a[x]%jz+'0')+s;
			a[x]/=jz;
		}
		x++;
		int len=s.size();
		bool f=1;
		for(int i=0,j=len-1;i<=j;i++,j--)	//判断这个数在当前进制下是不是回文数 
			if(s[i]!=s[j])
			{
				f=0;
				break;
			}
		if(f) temp++;	//如果是回文数， 满足的进制个数+1 
		jz++;
	}
	if(temp>=2) return 1;		//如果满足的进制个数≥2，满足题意 
	else return 0;				//否则不满足 
}
int main()
{
	ios::sync_with_stdio(0);
	int n,s;
	cin>>n>>s;
	for(int i=s+1;n;i++)	//从第一个大于s的数开始判断。如果满足题意，n-1 
		if(turn(i))
		{
			cout<<i<<endl;	//输出满足题意的数
			n--;
		}
	return 0;
}
```

---

## 作者：Gast (赞：0)

# 重点重点！本题方法重点！

本题考验的是进制的转换，和回文数的判断。进制转换应该用短除法最简便。回文数应该用分离的方式或者字符串的方式判断。



-------------------------------------------------------------代码分割线----------------------------------------------------
以下是c++代码
```cpp
#include<cstdio>//头文件
using namespace std;
bool judge(int x)//判断函数
{
    int d[100],len,cnt=0;
    for(int i=2;i<=10;i++)
    {
        int h=x;
        len=0;
        while(h!=0)
        {
            d[++len]=h%i;
            h/=i;
        }
        bool flag=true;
        for(int i=1;i<=len-i+1;i++)
            if(d[i]!=d[len-i+1])
            {
                flag=false;
                break;
            }
        if(flag)
            cnt++;
        if(cnt==2)
            return true;//判断
    }
    return false;
}
int main()
{
    //freopen("dualpal.in","r",stdin);
//	freopen("dualpal.out","w",stdout);
    int n,s;
    scanf("%d %d",&n,&s);
    for(int i=s+1,j=1;j<=n;i++)
        if(judge(i))
        {
            printf("%d\n",i);
            j++;
        }
    return 0;
}
```
以下是Pascal代码
```pascal
var
        n,x,i,l,r,tot,j,t:longint;
        s,s1:string;//定义变量
function h(s:string;n:longint):boolean;//判断回文函数
var
        i:longint;//局部变量
begin
        for i:=1 to n div 2 do
        begin
                if s[i]<>s[n+1-i] then exit(false);//从1到一半不相等直接返回False
        end;
        exit(true);
end;
begin
        {assign(input,'dualpal.in'); reset(input);
        assign(output,'dualpal.out'); rewrite(output);}此处为文操
        readln(l,r);
        while l>0 do//主循环
        begin
                inc(r);
                tot:=0;
                j:=1;
                while (j<10)and(tot<2) do
                begin
                        s:='';
                        inc(j);
                        x:=r;
                        t:=0;
                        while x>0 do
                        begin
                                str(x mod j,s1);
                                s:=s+s1;
                                x:=x div j;
                                inc(t);
                        end;
                        while s[t]='0' do dec(t);
                        if h(s,t) then inc(tot);
                end;
                if tot=2 then
                begin
                        writeln(r);
                        dec(l);
                end;
        end;

        close(input); close(output);
end.
```



---

## 作者：Violette (赞：0)

可以根据回文平方数的程序，把主程序改一下：

输入n和s，用一个变量r存储s+1（前N个满足大于S的符合条件的数），

双重循环，转换好进制以后判断如果是回文数就让负责累加的变量加一。

如果这个变量大于等于2了，说明他是在两种或两种以上进制（二进制至十进制）上是回文数的十进制数，就输出。

每输出完一次，才让第一个循环变量加一。

最后，在每次大循环结束之前，让变量r++。

AC代码

```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
int a,n;
int s[301];
void jz(int a,int b){//进制 
    int r=0;
    while(a){
        s[++r]=a%b;
        a/=b;
    }
    s[0]=r;
}
bool change(){//回文 
    for(int i=1;i<=s[0];i++){
    if(s[i]!=s[s[0]+1-i]) return false;
    }
    return true;
}
void print(){//打印，输出 
    for(int i=s[0];i>=1;i--){
        if(s[i]<=9) cout<<s[i];
        else cout<<(char)(s[i]-10+'A');
    }
} 
int main() {
	cin>>n>>a;
	int r=a+1;
	for(int i=1;i<=n;){
    	int sum=0;
    	for(int j=2;j<=10;j++){
        	jz(r,j);
        	if(change()) sum++;
    	} 
    	if(sum>=2){
	        cout<<r<<endl;
	        i++;
	    }
	    r++;
	}
    return 0;
}

```


---

## 作者：buickboy (赞：0)

基本思路是将每个10进制数转换为2进制、3进制……，发现回文则计次，有2次就输出原10进制数，输出次数达到n次，就结束程序。

因此，外循环i从s+1开始依次增1，内循环j则从2到10进制依次遍历，轮流将i转换为j进制，这样就需要设计一个从10进制数转化为j进制字符串的函数。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool hw(string s)//判断字符串回文 
{
	int i,len=s.size();//假设len=4 
	for(i=0;i<len/2;++i)//奇数长度最中间字符不参加比较
	{//偶数长度只比较1-len/2次，次数从0计起就要减1 
		if(s[i]!=s[len-1-i])//s[1]!=s[4-1-1]
			return false;
	}	
	return true;
}
string ten2b(int n,int b)//10进制整型n转b进制字符串x 
{	
	string x,dic="0123456789";//进制数做成字典
	while(n)
	{
		x=dic[n%b]+x;//取余后查表转化
		n/=b;
	}
	return x;
}
int main()
{
    int i,j,n,s,k,m=0;
    string t;
    cin>>n>>s;//前n个比s大的解 
    for(i=s+1;;++i)//比s大 
    {
    	k=0;
    	for(j=2;j<=10;++j)//2-10进制依次转换 
    	{
    		t=ten2b(i,j);//j进制下的i 
    		if(hw(t)) k++;
    		if(k==2) //2次不同进制下回文
			{
				cout<<i<<endl;
				m++;//解的个数要小于n 
				if(m==n) return 0;//到达n个 
				break;//其他进制不必进行
			}			
		}
	}
}

```

---

## 作者：hongzy (赞：0)

我用的双向队列.

思路就是转换成i=2~10进制，判断回文,用双向队列头尾判断.

```cpp
#include <iostream>
#include <queue>
using namespace std;

int N, K, C; 

bool Judge(int num) {
    int cnt = 0, x;
    for(int i=2; i<=10; i++) {
        x = num;
        deque<int> S;
        while(x) S.push_back(x % i), x /= i; //转换成i进制 
        while(!S.empty()) {
            if(S.front() != S.back()) break; //不回文 
            if(S.size() == 1 || (S.size() == 2 && S.front() == S.back())) { //回文 
                cnt ++;
                break;
            }
            S.pop_back();
            S.pop_front();
        }
        if(cnt == 2) break;
    }
    return cnt == 2;
}

int main() {
    cin >> K >> N;
    for(int i=N+1; C<K; i++) {
        if(Judge(i)) {
            cout << i << endl;
            C ++;
        }
    }
    return 0;
}

```

---

## 作者：樱墨抄 (赞：0)

AC代码如下：

**请勿抄袭**

~~抄袭记得删除freopen~~







```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int n,s,len=0;
int a[105];
int ifhw(){    //判断这个进制转换后的数是不是回文数 
    for(int i=1;i<=len/2;i++){
        if(a[i]!=a[len-i+1]){
            return 0;    //不是回文数返回0 
        }
    }
    return 1;    //是回文数返回1 
}
int turn(int x,int k){    //进制转换，将x转换为k进制的数 ，每一位放在a数组里 
    len=0;
    memset(a,0,sizeof(a));
    while(x>0){
        a[++len]=x%k;
        x/=k;
    }
    return 0;
}
int main(){
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    scanf("%d %d",&n,&s);
    int begin=s+1;//开始从s大一的数开始判断 
    for(int k=1;k<=n;){
        int ans=0;
        for(int i=2;i<=10;i++){
            turn(begin,i);//从2到10进制一一枚举 
            if(ifhw()==1)ans++;
        }
        if(ans>=2){
            printf("%d\n",begin);
            k++;
        }
        begin+=1;
    }
    return 0;
}

```

---

## 作者：babingbaboom (赞：0)

主要思路就是先转换进制，再判断回文。十进制转n进制主要就是短除法，把余数放在一起即可；回文数是第i位与第n-i+1位相同。

代码如下：

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int a[105],n,ans=0;
bool used=false;
void transdefine(int x,int k)//一个函数
{
    int i=1,sum=0;
    if(x<k) 
    {
        ans++;
        return;
    }
    else
    {
        while(x>=k)//判断位数和剩余量（转换进制）
        {
           a[i]=x%k;
           x=x/k;
           i++;
        }
        i--;
        a[i+1]=x;
        if(a[1]==0||a[i+1]==0) return;
        else//回文数的判定
        {
           for(int j=1;j<=(i+1)/2;j++)
           {
              if(a[j]==a[i+2-j]) sum++;
           }
           if(sum>=(i+1)/2)
           {
              ans++;
              return;
           } 
           else return;
        }
    }
}
int main()
{
    int s;
    cin>>n>>s;
    for(int j=s+1;;j++)
    {
        for(int i=2;i<=10;i++)
        {
            transdefine(j,i);
            if(ans==2)
            {
               used=true;
               n--; //cout<<n<<" ";
               break;
            }
        }
        ans=0;
        if(n<0) break;
        if(used==true)
        {
            cout<<j<<endl;
            used=false;
        }
    }
     return 0;
}
```

---

## 作者：ljc20020730 (赞：0)

~~Pascal党福利~~

就是一道水水的模拟题，

思路就是枚举进制、判断进制、判断回文、while控制

首先是判断回文，

假设我们在数组a中存储了一个转进制后的数，请判断其是否为回文数？

很简单，我们给出check函数

```cpp
function check(n:longint):boolean;//传入这个数有几位
var i:longint;
begin
 for i:=1 to n div 2+1 do
  if a[i]<>a[n-i+1] then exit(false);
 exit(true);
end;
```
接下来就是转进制，也不难，
注意我们把整个数组的长度定义在a[0]中

```cpp
procedure ff(x,k:longint);
Var i:longint;
Begin
  Fillchar(a,sizeof(a),0);
  i:=0;
  While x>0 do begin
    i:=i+1;
    a[i]:=x mod k;
    x:=x div k;
  End;
  a[0]:=i;//存数位
End;
```
然后就是枚举了，这就不用多说了吧。
主要讲讲坑点：

- 题目说：有一些数（如21），在十进制时不是回文数，但在其它进制（如二进制时为10101）时就是回文数。但是事实上我们枚举到9进制只能拿到57分，第一次就栽在这里~~

- 题目说：找出前N个满足大于S且在两种或两种以上进制（二进制至十进制）上是回文数的十进制数，输出到文件上。说明我们找到2个进制符合即可，不必继续计算

- 转进制后是倒叙存在数组中，这里不换回来是因为本身就是判断回文，与其正序倒序无关~~

所以这道题就妥妥的AC了

```cpp
var a:array[0..100000]of integer;
    n,s,i,tt,cnt,j:longint;
procedure ff(x,k:longint);
Var i:longint;
Begin
  Fillchar(a,sizeof(a),0);
  i:=0;
  While x>0 do begin
    i:=i+1;
    a[i]:=x mod k;
    x:=x div k;
  End;
  a[0]:=i;
End;
function check(n:longint):boolean;
var i:longint;
begin
 for i:=1 to n div 2+1 do
  if a[i]<>a[n-i+1] then exit(false);
 exit(true);
end;
begin
 readln(n,s);
 while cnt<n do begin
  inc(s);  tt:=0;
  for i:=2 to 10 do begin
  ff(s,i);
  if check(a[0]) then inc(tt);
  if tt=2 then break;
  end;
  if tt=2 then begin writeln(s);inc(cnt); end;
 end;
end.

```

---

## 作者：functionendless (赞：0)

要有区块化的编程思想，judge判回文,turn转进制，search枚举



```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int sum=0,a[20],cnt,n,s;
int turn(int n,int w)
{  
    memset(a,0,sizeof(a)); 
    int i=0;
    while(n>0)
    {
        a[++i]=n%w;
        n/=w;
    }
    return i;    
}
bool judge(int x)
{
    int i=1,j=x;
    while(i<j)
    {
        if(a[i++]!=a[j--]) return false;
    }
    return true;
}
void search()
{
    int i,j;
    for(i=s+1;sum<n;i++)
    {
        cnt=0;
        for(j=2;j<=10;j++)
        {
            int x=turn(i,j);
            if(judge(x))
                cnt++;
            if(cnt>=2)
            {
                sum++;
                printf("%d\n",i);
                break;
            }
        }
    }
}
int main()
{
    scanf("%d %d",&n,&s);
    search();
    return 0;
}
```

---

## 作者：FREEH (赞：0)

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n,s,zs;
string zjz(int a,int jz)
{
    string st="";
    while (a>0)
    {
        int ys=a%jz;
        string ch="";
        if (ys<10) ch+=(ys+48);else ch+=(ys+55);
        st=ch+st;
        a/=jz;
    }
    return st;
}
//用函数转换成相应进制
bool hw(string st)
{
    bool p=true;
    for (int j=0;j<st.size();j++)
        if (st[j]!=st[st.size()-j-1])
        {
            p=false;
            break;
        }
    return p;
}
//判断是不是回文数
int main()
{
    scanf("%d%d",&n,&s);
    for (int i=s+1;zs<n;i++)注意是s+1！！！
    {
        int ans=0;
        for (int j=2;j<=10;j++)
        {
            if (hw(zjz(i,j))) ans++;//如果转换成j进制后是回文数，总数+1
            if (ans==2) break;//找到两个，不用再找，退出！
        }
        if (ans==2) 
        {
            printf("%d\n",i);
            zs++;//找到总数+1
        }
    }
    return 0;
}
```
*********************************************************************************************
#需要重点注意：是从s+1开始找起！！！


---

