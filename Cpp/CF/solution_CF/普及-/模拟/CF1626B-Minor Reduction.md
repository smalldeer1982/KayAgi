# Minor Reduction

## 题目描述

You are given a decimal representation of an integer $ x $ without leading zeros.

You have to perform the following reduction on it exactly once: take two neighboring digits in $ x $ and replace them with their sum without leading zeros (if the sum is $ 0 $ , it's represented as a single $ 0 $ ).

For example, if $ x = 10057 $ , the possible reductions are:

- choose the first and the second digits $ 1 $ and $ 0 $ , replace them with $ 1+0=1 $ ; the result is $ 1057 $ ;
- choose the second and the third digits $ 0 $ and $ 0 $ , replace them with $ 0+0=0 $ ; the result is also $ 1057 $ ;
- choose the third and the fourth digits $ 0 $ and $ 5 $ , replace them with $ 0+5=5 $ ; the result is still $ 1057 $ ;
- choose the fourth and the fifth digits $ 5 $ and $ 7 $ , replace them with $ 5+7=12 $ ; the result is $ 10012 $ .

What's the largest number that can be obtained?

## 说明/提示

The first testcase of the example is already explained in the statement.

In the second testcase, there is only one possible reduction: the first and the second digits.

## 样例 #1

### 输入

```
2
10057
90```

### 输出

```
10012
9```

# 题解

## 作者：gzlinzy (赞：5)

首先，我们可以证明，操作后的数一定小于原来的数。

设操作的两个数分别为 $x$ 和 $y$。

1、当 $x+y\le9$ 时，$x+y$ 只有一位数字，比原来的两位少了一位，因此操作后的数也比原来少一位，自然比原来要小。

2、当 $x+y>9$ 时，此时 $x$，$y$ 均为正整数，操作后的数和原来位数相同，但结果从原来的 $10x+y$ 变为 $x+y$ ，依然减小了。

第一种情况，$x$ 和 $y$ 越靠近个位减小得越小，得数就越大。

第二种情况，操作前两位时最高位上的 $x+y$ 明显不小于原来的 $x$，自然是最优解。

因此，为了最大化答案，当存在满足第一种情况的 $x$，$y$ 时操作最靠近个位的 $x$ 和 $y$，否则操作前两位。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,f,lena;
string a;
int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>a;
		lena=a.length();
		for(int i=0;i<lena-1;i++)
			if(a[i]+a[i+1]-2*'0'>9)f=i;
		for(int i=0;i<f;i++)cout<<a[i];
		cout<<a[f]+a[f+1]-2*'0';
		for(int i=f+2;i<lena;i++)cout<<a[i];
		cout<<endl;
		f=0;
	}
}
```


---

## 作者：哈士奇憨憨 (赞：4)

[传送门](https://www.luogu.com.cn/problem/CF1626B)
## 题目大意
有一个整数 $x$，请取一次 $x$ 中的两个相邻数字，并将其替换为它们的和,求能得到的最大数字是多少。
## 思路
设取的两个数是 $m ,\ n$ 

则它们原本的数是 $10m +n$ 

现在的数为 $m + n$ 

所以进行操作后答案不会变得更优。 

但如果 $m + n < 10$，说明这个数少了一位，比 $m + n \ge 10$ 时数位不变会更劣，所以应该从数的权重较小的地方开始判断到数的权重较大的地方。
## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int main(){
	cin >> t;
	while(t--){
		cin >> s;
		int j = 0;
		for(int i = 0; i < s.size() - 1; i++){
			if(s[i] - '0' + s[i + 1] - '0' >= 10){//判断是否进位
				j = i;//记录相加位置
			}
		}
		for(int i = 0; i < j; i++){
			cout << s[i];
		}
		cout << s[j] - '0' + s[j + 1] - '0';//相加的两个数做特殊处理
		for(int i = j + 2; i < s.size(); i++){
			cout << s[i];
		}
		cout << endl;	
	}
 } 
 ```

---

## 作者：Argon_Cube (赞：2)

* **【题目链接】**

[Link:CF1626B](https://www.luogu.com.cn/problem/CF1626B)

* **【解题思路】**

按照题目的要求操作一次，得到结果的位数可能少 $1$ 也可能不变。那么假如能让位数不变显然最好。那么，我们该选哪两个数位加起来呢？显然这两个数位之和得大于 $9$。并且，假如我们进行了一次操作，这个数一定会变小。
（以下我们定义最后面的数为个位）那么，我们让前面权重大的数位变小，不如让后面权重小的数位变小。也就是说，此时能选的数位越靠后越好。

否则，如果找不到两个数位相加大于 $9$，位数一定会少 $1$，我们直接选数字头两位相加。为什么？假如头一位后面不为 $0$，那么我们让后面的数相加变大，不如直接最大化最高位。否则，假如最高位后跟着 $0$，那么显然能少一个 $0$ 是最好的。具体为什么可以自己举例（如 $10123$）。

* **【代码实现】**

```cpp
#include <iostream>
#include <string>
#include <array>

using namespace std;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		string tmp;
		bool flag=false;
		cin>>tmp;
		int len=tmp.size()-1;
		for(int i=len;~i;i--)
			if(tmp[i]+tmp[i+1]-2*'0'>9)
			{
				int temp=tmp[i]+tmp[i+1]-2*'0';
				tmp[i]=temp/10+'0',tmp[i+1]=temp%10+'0',flag=true;
				break;
			}
		if(flag)
		{
			cout<<tmp<<'\n';
			continue;
		}
		cout<<(char)(tmp[0]+tmp[1]-'0');
		for(int i=2;i<=len;i++)
			cout<<tmp[i];
		cout<<'\n';
	}
	return 0;
}


```

---

## 作者：hh20080501hh (赞：1)

想获得更好的阅读体验？~~没有哦~~，你什么也不能戳。
# 题面


[完整题面戳这儿~](https://www.luogu.com.cn/problem/CF1626B)

------------
# 分析
**通过题目的描述，我们很容易可以发现每次替换有两种可能。第一种可能为两位数替换两位数，第二种可能为一位数替换两位数。我们分情况来讨论**

1. **两位数替换两位数**，我们将对原数字进行操作的两位分别记为 $i$，$j$。即第 $i$ 位加上第 $j$ 位大于 $10$。很显然，进行一次这样的操作后，从被操作的数字开始，操作后的数字一定比原数字小，所以我们希望操作的位置在越后面越好，这样对数字减小的影响最小。
1. **一位数替换两位数**，我们将对原数字进行操作的两位分别记为 $i$，$j$。即第 $i$ 位加上第 $j$ 位小于 $10$。很显然，进行了一次这样的操作后，整个数字会少一位，比原数字小。**但是**如果我们看第 $i$ 位和第 $j$ 位，可以发现对他们操作后产生的数字一定一定大于等于 $i$ 和 $j$。既然一定会少一位，那么我们需要在少一位的基础上最大，所以，我们希望操作的地方越前面越好，这样越前面的位越大，整个数也越大。

**注意**用两位数替换两位数结果一定是比一位数替换两位数的结果大的！因为前者会多一位，所以我们可以先判断能否进行两位数替换两位数，不行再去考虑一位数替换两位数。
# 代码
分析结束，上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> n;
	while(n--)
	{
		string s;
		cin >> s;
		int flag = -1;
		for (int i=0 ; i<s.size()-1 ; i++)
		{
			if ((s[i]-'0'+s[i+1]-'0')>=10)
			{
				flag = i; //记录可以进行两位数替换两位数操作的位置，
                	//由于是从前往后扫的，且我们希望
                  //越后越好，所以只要有新的
                  //可以满足的就可以替换前面的
			}
		}
		if (flag!=-1) // 如果可以进行两位数替换两位数操作就进行
		{
			int sum = s[flag]-'0'+s[flag+1]-'0';
			for (int i=0 ; i<flag ; i++)
			{
				cout << s[i];
			}
			cout << sum;
			for (int i=flag+2 ; i<s.size() ; i++)
			{
				cout << s[i];
			}
			cout << endl;
			continue;
		}
		else //进行一位数替换两位数的操作，因为越前越好，
         //所以一定是对最前面两位进行操作
		{
			int sum = s[0]-'0'+s[1]-'0';
			cout << sum;
			for (int i=2 ; i<s.size() ; i++)
			{
				cout << s[i];
			}
			cout << endl;
		}
	}
	return 0;
}

```
代码表达的意思在注释里写的都比较清楚了，应该没有理解难度。
# 感谢大家的阅读。

---

## 作者：cst_123 (赞：1)

#### - [传送门](https://www.luogu.com.cn/problem/CF1626B)

------------

### 大意
一个整数 $n$ ，取一次 $n$ 中的相邻两个数，将其替换为它们之和，问能得到的最大数字是多少。

------------

设取的是 $x$ 和 $y$ ，原来是 $10x+y$ ,现在是 $x+y$ 。

如果 $x + y < 10$ ，说明这个数少了一位，比 $x + y \ge 10$ 时数位不变会更少，所以应从数的权重较小的地方开始判断到数的权重较大的地方。

------------
### 代码

```cpp
long long read(){
   long long x=0,sg=1;char cha=getchar();
   while(cha<'0'||cha>'9'){if(cha=='-')sg=-1;cha=getchar();}
   while(cha>='0'&&cha<='9'){x=x*10+cha-'0';cha=getchar();}
   return x*sg;
}
int main(){
	t=read();//输入 
	while(t--){
		cin>>st;
		len=st.size();
		tot=0;//清零 
		for(int i=0;i<len-1;i++){
			if(st[i]-'0'+st[i+1]-'0'>=10)//判断是否进位
				tot=i;//是就加1 
		}
		for(int i=0;i<tot;i++) cout<<st[i];//输出 
        
		cout<<st[tot]-'0'+st[tot+1]-'0';//相加的数做特殊处理
      		//上面的很重要
		for(int i=tot+2;i<len;i++)
			cout<<st[i];
		cout<<endl; 
	}
	return 0;//完成了 
}
```

---

## 作者：封禁用户 (赞：1)

### [传送门](https://www.luogu.com.cn/problem/CF1626B)

### 思路 ：

我们可以证明，合并后数一定变小了。

若 $a[i]$ $+$ $a[i-1]$ $<10$ ，数字少了一位，变小了。

若 $a[i]$ $+$ $a[i-1]$ $\ge$ $10$ ， $a[i-1]$ 变为 $1$ ，也变小了。

如果在这个数中有进位，那进位一定越后面越好。

如果没有，那一定合并前两个。

具体细节见代码。

###   AC code

```cpp

#include<bits/stdc++.h>
//#define int long long
using namespace std;
int T,len,flag,i,s;
char a[200100];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>a+1;
		len=strlen(a+1);
		flag=1;
		for(i=len;i>=2;i--)   //贪心 
			if(a[i]+a[i-1]-'0'-'0'>=10){  //如果有进位 
				s=a[i]+a[i-1]-'0'-'0';
				a[i-1]=s/10+'0';
				a[i]=s%10+'0';          //改变这个数 
				flag=0;
				break;      //退出 
			}
		if(flag){           //无进位 
			a[2]+=a[1]-'0';
			a[1]=' ';
		}	
		for(i=1;i<=len;i++)if(a[i]!=' ')cout<<a[i];
		cout<<"\n";//输出 
	}
	return 0;//！！！完结撒花！！！
}


```

---

## 作者：Annihilation_y (赞：1)

## 思路 
首先，我们可以证明，每操作一次，都会使这个数减小。所以，为了使答案最大，只操作一次。

其次，分两种情况考虑：

- 两数相加大于十：这两个数减少，数位不变。

- 两数相加小于十：这两个数减少，数位减一。

所以，尽量满足第一种情况，否则，操作前两位，让首位尽量大。

## CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	while(n--)
	{
		string a;
		cin>>a;
		int len=a.length();
		a=" "+a;
		int ans=1;//存储操作的两个数的数位
		for (int i=1;i<len;i++)
		{
			if(a[i]+a[i+1]-2*'0'>9)
			{
				ans=i;//找到两数相加大于等于十的数位
				//这里不能退出，要找到最后一个
        }
		}
		for(int i=1;i<ans;i++)
			cout<<a[i];
		cout<<a[ans]+a[ans+1]-2*'0';
		for (int i=ans+2;i<=len;i++)
			cout<<a[i];
		cout<<endl;
	}
	return 0;
} 

```
#### _The end_

---

## 作者：Node_Edge (赞：0)

题意化简：

给定 $n$ 个数，选出 $a_i$ 中的两个相邻数字，将其替换为它们的和,使得到的最大数字。

-----

思路：

枚举相邻的两个数字 $x$ 和 $y$，分为两种情况：

1. $x+y \leq 9$，$x+y$ 是一位数

2. $x+y > 9$，$x+y$ 是两位数，即从 $10x+y$ 变为 $x+y$，比第一种更优

用字符串实现此题，从数的影响力较小的地方开始判断到数的影响力较大的地方。

----

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>s;
		int j=0;//标记影响力最大的位置 
		for(int i=0;i<s.size()-1;i++){
			if(s[i]-'0'+s[i+1]-'0'>= 10){//判断是否进位 
				//减字符0，转数字  
				j=i;
				//标记影响力 
			}
		}
		//输出相加前的数字  
		for(int i=0;i<j;i++){
			cout << s[i];
		}
		//输出相加的数字 
		cout<<s[j]-'0'+s[j + 1]-'0';
		//输出相加后的数字 
		for(int i = j + 2; i < s.size(); i++){
			cout << s[i];
		}	
	}
	return 0; 
 } 
```


---

## 作者：sgl654321 (赞：0)

### 题目大意
给定一个很大的数 $x$，选定相邻两位上的数字 $x_i$ 和 $x_{i+1}$，将它们相加，其余部分不变，会得到一个新的数 $x'$。求出 $x'$ 的最大值。具体请看[题目](https://www.luogu.com.cn/problem/CF1626B)。
### 解题思路
$x$ 非常大，又~~懒得写高精度~~，所以我们考虑一下能否用别的方法求出最大值。

显然，若 $x_i+x_{i+1}$ 可以进位，则一定比不能进位要好（如果不能进位，那就会失去一位）。

所以我们可以分两种情况来讨论：

- 如果所有的 $x_i+x_{i+1}$ 都无法进位，那么就让**前两位** $x_1$ 与 $x_2$ 相加，这样能够保证**最高位最大**，一定是最优解。
- 如果所有的 $x_i+x_{i+1}$ 中有一些可以进位，那么就让**最后面的两位**相加。具体请看下面证明：

$\because 10x_i+x_{i+1}\geq x_i+x_{i+1}$，即 $\overline {x_ix_{i+1}}\geq x_i+x_{i+1}$

$\therefore$ 每一次相加，都一定会小于等于原来的数。

为了使得到的数最大，我们要尽量操作后面的，而不要动前面的，这样可以保证**高位最大**。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,len,a[200010],k;
string st;
int main(){
	cin>>t;
	while(t--){
		cin>>st;
		len=st.size();
	 	k=0;//寻找进位的位置。 
		for(int i=1;i<=len;i++)
			a[i]=st[i-1]-'0';
		//考虑是否进位。
		//如果有进位，那么选用最低位的进位。
		//如果没有进位。那么合并前两个数。 
		for(int i=1;i<len;i++)
			if(a[i]+a[i+1]>=10)
				 k=i;
		if(k==0){
			cout<<a[1]+a[2];
			for(int i=3;i<=len;i++)
				cout<<a[i];
			cout<<endl;
			continue; 
		} 
		for(int i=1;i<k;i++)
			cout<<a[i];
		cout<<a[k]+a[k+1];
		for(int i=k+2;i<=len;i++)
			cout<<a[i];
		cout<<endl;
			
	}
	return 0;
}

```

写在最后：管理大大求过。


---

## 作者：zbk233 (赞：0)

## 解题思路

考虑分类讨论。

设要相加的两个数为 $x$ 与 $y$。

当 $x+y\ge 10$ 时，这个数的位数不变，但是数字会变小。

根据小学数学，放在更接近个位的位置会让数变小的影响最小。

当 $x+y<10$ 时，这个数位数变小，但是数字会变大。

根据小学数学，放在最高位会让数变得最大。

## 代码实现

```cpp
#include<iostream>
#include<cstring>
using namespace std;
string str;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T,n;
	cin>>T;
	while(T--){
		cin>>str;
		int len=str.size(),flag=1;
		for(int i=len-1;i>=0;i--){
			int tmp=str[i]-'0'+str[i+1]-'0';
			if(tmp>=10){
				flag=0;
				str[i]=tmp/10+'0';
				str[i+1]=tmp%10+'0';
				break;
			}
		}
		if(flag){
			str[1]=str[0]-'0'+str[1];
			for(int i=1;i<len;i++) cout<<str[i];
			cout<<'\n';
		}else{
			cout<<str<<'\n';
		}
	}
	return 0;
}
```



---

## 作者：IvanZhang2009 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1626B)

## 题意
将一个十进制数进行**一次**操作：

选择相邻的两位数字，取其和放回原数字。

求一次操作后的最大数字

举例：

10057

1、选择 10，则转换为 1057(10->1)

2、选择 00，则转换为 1057(00->0)

3、选择 05，则转换为 1057(05->5)

4、选择 57，则转换成 10012(57->12)

所以最后的答案就是 10012

## 解法
将两个数字变成它们的和，那么可以是有进位或没有进位。如果原数中没有相邻两位之和大于九的，则只考虑不进位；反之，则进位的解明显由于不进位的解。考虑分类讨论：

1、原数中没有相邻两位之和大于九的

如果选择前两位进行操作  ($ 10 \le x < 10^{200000}$ ，一定取得到)，则新数首位必定大于等于原数首位，即选择其他位进行操作得到的数的首位。又因为所有可能的操作后得到的数位数相等，则选择前两位操作是最优解。

2、原数中有相邻两位之和大于九的

为了让答案更大，我们优先选择相加有进位的两位进行操作。但这时与第一种情况不同。

若选择可以进位的地方进行操作，则相加之后第一位一定是 1，则结果必然减小。

如果结果必然会减小，那么肯定选择最后一处可以进位的一处进行操作，则减少的量是最少的，即得到此时的最优解。

## 代码
主要部分如下：

```cpp
string pplus(char a,char b,string s=""){ //将两个相邻数相加
	int c=a+b-'0';
	if(c>'9')
		s+="1",c-=10;
	return s+(char)(c);
}
void Main() {
	string s;
	cin>>s;
	bool v=0;
	REP(i,0,s.size()-1)
	if(s[i]+s[i+1]-'0'>'9')v=1; //判断是否有相邻两位之和大于 9 的
	if(v){               //分类讨论
		for(int i=s.size()-1;i>0;i--) //从后往前找
		if(s[i]+s[i-1]-'0'>'9'){  //从后往前第一处进位的
			string x=pplus(s[i-1],s[i]);
			s[i-1]=x[0],s[i]=x[1];    //调整原数
			cout<<s<<endl;
			return;
		}
		
	}else{
		s[1]+=s[0]-'0';       //直接对前两位进行操作
		s=s.substr(1,s.size()-1);
		cout<<s<<endl;
	}
}
```

---

## 作者：Land_ER (赞：0)

## 题意简述
- 给出一个数 $x(10 \leqslant 10^{200000})$。
- 在其中挑选相邻的两位，用这两个数的和代替这两位数。

## 解题思路
设选取的两位分别为 $a$ 和 $b$ 考虑这两种情况：

1. $a+b \geqslant 10$，即操作完原数位数不变。
2. $a+b < 10$，即操作完数位减少 $1$。

首先，如果出现了第一种情况，那么一定选择第一种，因为
>比较两个正整数，位数多的更大。——《小学数学》

其次，如果有多处符合第一种情况，那么应该选取哪一处呢？

容易证明，如果符合第一种情况，在操作后产生的两位数一定比原数小。这会导致原数变小。

而越靠近个位，位权越小，减小的数也越小。

因此，如果出现第一种情况，应该取最靠近个位的一处。

而第二种情况呢？

>两个正整数相加，和大于任意一个加数。——《小学数学》

操作后的数字一定会大于原来两位数中远离个位的一个。比较所有可能的操作，可以发现，操作在最远离个位的位置时结果最大。

得到结论：

- 如果出现第一种情况，就选取最靠近个位的一处进行操作。
- 如果没有出现第一种情况，就选取最远离个位的一处进行操作。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t,i,p,l,r;
    string s;
    bool flag;
    char c[3];
    cin >> t;
    while(t --){
    	cin >> s;
    	flag = 0;
    	l = s.size();
    	r = l - 2;
    	for(i = l-2;i >= 0;-- i){
    		if((s[i]-'0')+(s[i+1]-'0') >= 10){
    			r = i;
    			flag = 1;
    			break;
			}
		}
		if(flag){
			p = (s[r]-'0') + (s[r+1]-'0');
			s[r+1] = p % 10 + '0';
			p /= 10;
			s[i] = p + '0';
		}
		else{
			r = 0;
			c[0] = (s[r]-'0') + (s[r+1]-'0') + '0';
			c[1] = '\0';
			s.erase(r,2);
			s.insert(r,c);
		}
		cout << s << '\n';
    }
    return 0;
}
```

---

## 作者：Lantrol (赞：0)

# CF1626B 题解
### 题目描述
给定正整数 $x$（$10≤x≤10^{2\times10^5}$），可对其中任意两个相邻的数字进行合并，即用这两个数字的和代替这两位数。

例如，当 $x=10057$ 时，有以下几种可能的合并：

- 选择第一位 $1$ 和第二位 $0$，将其合并，得到 $1+0=1$，于是 $x$ 变换为 $1057$；
- 选择第二位 $0$ 和第三位 $0$，将其合并，得到 $0+0=0$，于是 $x$ 变换为 $1057$；
- 选择第三位 $0$ 和第四位 $5$，将其合并，得到 $0+5=5$，于是 $x$ 变换为 $1057$；
- 选择第四位 $5$ 和第五位 $7$，将其合并，得到 $5+7=12$，于是 $x$ 变换为 $10012$。

该操作可且仅可进行一次，问经过一次该操作后，可获得的最大数。

显然，在上述示例中，获得的最大数为 $10012$。

### 思路

注意到数据范围，考虑线性复杂度做法。

采用贪心思想。要使变换后的数最大，首先变换后的数的位数一定要最多。所以我们期望找到一对相邻的数字之和不小于 $10$。继续思考，发现可能出现有多对相邻数字之和不小于 $10$ 的情况。那么如何进行操作才能使结果最大呢？不难发现，当两位数字之和大于 $10$ 时，它们的和必然小于由它们所组成的数。例如 $38$，$3+8=11$，显然 $11<38$。多举几个例子也成立。

简单证明，当 $x$，$y$ 均为正整数时，显然有 $x+y<10x+y$。

那么由此我们想到，在保证一对相邻数字和不小于 $10$ 的条件下，尽可能地使被合并的这对数出现在更靠后的位置，这样可以使结果尽可能大。那我们直接倒着枚举，当两个数和大于 $10$ 时，直接输出结果即可。

那么假如找不到一对和大于 $10$ 的相邻数字呢？

简单思考后发现，假如找不到这对数字，直接合并前两位即可。因为在这种情况下，合并后的数字肯定大于合并前。那么把合并操作尽可能靠前地完成，就可以使得结果最大，设法输出即可。

由于 $x$ 很大，直接用 $\text{string}$ 存，然后转存到数组即可。关于输出时所需要注意的，代码里都有，此处不多作解释。

### CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[200005];
void solve(){
	string s;
	cin>>s;
	int len=s.size();
	for(int i=0;i<len;i++){
		a[i+1]=s[i]-'0';
	}
	for(int i=len;i>1;i--){//倒着枚举 
		int ans=a[i]+a[i-1];
		if(a[i]+a[i-1]>=10){//优先判断是否有相邻数之和大于等于10的情况 
			a[i]=ans%10;
			a[i-1]=ans/10;//替换数字，然后输出 
			for(int i=1;i<=len;i++){
				cout<<a[i];
			}
			cout<<endl;
			return;
		}
	}
	a[2]=a[1]+a[2];//直接合并前两位 
	for(int i=2;i<=len;i++){//此时第一位为前导0，所以直接从第二位开始输出 
		cout<<a[i];
	}
	cout<<endl;
}
int main(){
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}

```


---

## 作者：_Diu_ (赞：0)

[luogu 传送门](https://www.luogu.com.cn/problem/CF1626B)

[cf 传送门](https://codeforces.com/contest/1626/problem/B)

## 题目大意

给处一个数 $x(\le 10^{200000})$，

要求把这个数的其中一对相邻两位的书相加，再放回去，得到一个新数。

如 $10057$ 把右数第三、第四位进行操作后就是 $1057$，最左侧两位操作后就是 $10012$。

问这样操作中得到的数中最大的是多少。

多组数据。

## 思路

如果直接每一个得出来的数都暴力判断的话，显然是过不了的。

我们这样想，合并之后的数可以分为三种情况：

- 合成一个两位数，比原来的数字更大

- 合成一个两位数，比原来的数字更小

- 合成一个一位数

显然，位数更多的更优，

而在位数多的情况下，比原来的数大的更优。

在比原来的数大的数中，修改的数字位数越高，就越大。

在比原来的数小的数中，修改的数字位数越低，就越大。

而在合成出一位数的情况下，合成出的新数肯定大于或等于原来的那一位，此时位数越大，就越大。

跟着这个思路，用贪心的思想去判断就好了。

时间复杂度 $O(Tn)$（$n$ 是数字 $x$ 十进制下的位数）。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t,ans;
string s;
string add(char a,char b){
	int x=a+b-'0'-'0';
	string s="";
	if(x>9)s=(char)('0'+x/10),s+=(char)('0'+x%10);
	else s=(char)(x+'0');
//	cout<<a<<' '<<b<<' '<<x<<' '<<s<<'\n';
	return s;
}
bool cmp(string a,string b){
	if(a.size()^b.size())return a.size()>b.size();
	for(int i=0;i<a.size();i++)if(a[i]^b[i])return a[i]>b[i];
	return 1;
}
signed main(){
	scanf("%d",&t);
	for(;t--;){
		cin>>s;
		int n=s.size();
		ans=-1;
		for(int i=0;i<n-1;i++){
			if(s[i]+s[i+1]-'0'-'0'>9){
				int x=s[i]+s[i+1]-'0'-'0',y=(s[i]-'0')*10+s[i+1]-'0';
				if(x>y){ans=i;break;}
			}
		}
		if(ans==-1)for(int i=n-2;i>=0;i--){
			if(s[i]+s[i+1]-'0'-'0'>9){ans=i;break;}
		}
		if(ans==-1)ans=0;
		for(int i=0;i<ans;i++)cout<<s[i];
		cout<<add(s[ans],s[ans+1]);
		for(int i=ans+2;i<n;i++)cout<<s[i];
		cout<<'\n';
	}
}
```

---

## 作者：heaksicn (赞：0)

## 1 题意
给定一个数，将其中两个相邻的数相加，填补到原来选取的数的位置（不含前导 0）。问进行一次操作后这个数最大可以变为多少。

多组数据。
## 2 思路
通过题目描述，我们可以得出一个结论：操作后的数一定比原本的数小。

那么，我们需要分类讨论：

1. 如果每组相邻的数的和都不超过 $9$，那么此时为了使操作后的数尽量大，我们应该选取最前面的一组数进行合并。

2. 如果每组相邻的数的和中存在超过 $9$ 的组合，那么此时为了使操作后对数字的影响最小，我们应该选取最后面的一组和大于 $9$ 的数进行合并。

具体见代码。
## 3 code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int a[200001];
int T;
int sum[200001];
int main(){
	T=read();
	while(T--){
		cin>>s;
		int len=s.size();
		for(int i=0;i<len;i++){//分离数位
			a[i+1]=s[i]-'0';
		}
		bool flag=1;
		for(int i=1;i<len;i++){
			sum[i]=a[i]+a[i+1];//求出和
			if(sum[i]>=10) flag=0;//有没有大于9的组合
		}
		if(flag==0){//有这样的组合
			for(int i=len-1;i>=1;i--){//选取排最后的一对
				if(sum[i]>=10){
					for(int j=1;j<i;j++) cout<<a[j];//输出前缀
					cout<<sum[i];
					for(int j=i+2;j<=len;j++) cout<<a[j];//输出后缀
					cout<<endl;
					break;
				}
			}
		}else{//没有这样的组合
			cout<<sum[1];//合并第一项
			for(int i=3;i<=len;i++) cout<<a[i];//输出后缀
			cout<<endl;
		}
	}
	return 0;
}
```


---

