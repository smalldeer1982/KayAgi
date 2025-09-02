# 「SWTR-4」Calculating Machine

## 题目背景

小 E 在用自己的 Calculating Machine 计算 $n$ 个**十进制**数 $a_1,a_2,\cdots,a_n$ 的和。



## 题目描述

小 E 计算几个数的和的方式为：

- 如果参与运算的数不止 $2$ 个，那么**从左往右**依次计算。

- 若两个数的位数不同，则位数少的数自动在前面补前导零，直到两数位数相同。

- 从两个数的最低位开始，计算当前位两个数码的和加上前一位的进位，写上这个和除以 $10$ 的余数。

- 进位规则：如果当前位两个数码的和加上前一位的进位小于 $7$，不进位；如果和大于等于 $7$ 且小于等于 $13$，则进一位；否则进两位。

例如：$2+4=6$，$7+8=25$，$61+6=177$，$38+169=217$，$3+900=1903$。

由于小 E 的计算机器被 360 安全病毒当成病毒杀死了，所以他想请你帮忙求出 $a_1+a_2+\dots+a_n$。

## 说明/提示

【样例 $3$ 说明】

$345+379+573=1734+573=2317$。

【样例 $4$ 说明】

$1234+567+89+10=2801+89+10=3990+10=4000$。

【数据范围与约定】

对于 $10\%$ 的数据，$n=1$。

对于 $30\%$ 的数据，$n \leq 2$。

对于 $60\%$ 的数据，$n \leq 10$，$a_i \leq 10^5$。

对于 $100\%$ 的数据，$1 \leq n \leq 2020$，$0 \leq a_i \leq 10^9$。

【Source】

[Sweet Round 04](https://www.luogu.com.cn/contest/26414)$\ \ $A

idea：[ET2006](https://www.luogu.com.cn/user/115194)，std：[Alex_Wei](https://www.luogu.com.cn/user/123294)，验题：[Isaunoya](https://www.luogu.com.cn/user/96580) & [FrenkiedeJong21](https://www.luogu.com.cn/user/203968) & [chenxia25](https://www.luogu.com.cn/user/138400)

## 样例 #1

### 输入

```
1
1
```

### 输出

```
1```

## 样例 #2

### 输入

```
2
233 23333
```

### 输出

```
23566```

## 样例 #3

### 输入

```
3
345 379 573
```

### 输出

```
2317```

## 样例 #4

### 输入

```
4
1234 567 89 10
```

### 输出

```
4000```

## 样例 #5

### 输入

```
5
19111010 19260817 19371213 19491001 20200110
```

### 输出

```
239635161```

# 题解

## 作者：SUNCHAOYI (赞：6)

这道题其实跟高精度的模拟类似，但是唯一不同的是逢七进一，且每位上的数字是$0-9$。那么如何进行模拟呢？首先需要知道这道题的进位特点。  
$\color{white}-\color{black}12\color{white}-------\color{black}75$   
$\color{black}+13\color{white}------\color{black}+73$   
$---\color{white}-----\color{black}---$     
$\color{white}-\color{black}25\color{white}-------\color{black}258$     

$\color{black}\textbf{不进位}\color{white}-----\color{black}\textbf{进位}$  
知道这一点后，我们就可以开始模拟。为了方便，我们把个位放在前面。又因为数据比较大，所以我们采用字符串式处理。
```
for(int j = 0;j < now;j++) num[now - 1 - j] = a[i][j] - '0';//加数 
for(int j = 0;j <= max(wei,now);j++)
{
	if(i == 1) k = 0;//第一个加数自己不用进位处理 
	ans[j] += k + num[j];//加法 
	k = ans[j] / 7;//进位 
	ans[j] %= 10;//每一位在0-9之间 
}
```
我们可以发现，在两数相加之后，还有可能不停进位，产生新的一个数位，所以我们要判断$k$是否还存在进位数字。
```
while(k != 0)//还需进位 
{
			//继续模拟加法 
	ans[++now] += k + num[now];
	k = ans[now] / 7;
	ans[now] %= 10;
}
wei = max(wei,now);//保存最大长度 
```
最后就是输出了，把前导的$0$去掉是关键！直接我们做加法的时候是个位在前面，所以输出的时候要记得在调转回来。
```
while(ans[wei] == 0) wei--;//去除前导零 
if(wei < 0) cout<<0<<endl;//等于0的情况特判 
else
{
	for(int i = wei;i >= 0;i--) cout<<ans[i];//正常输出 
	cout<<endl;
}
```


------------

贴一下完整代码:
```
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
string a[2025];
int ans[2025],num[2025];
int main()
{
	int n,k = 0,wei = 0;
	cin>>n;
	for(int i = 1;i <= n;i++) cin>>a[i]; 
	for(int i = 1;i <= n;i++)
	{
		k = 0;
		memset(num,0,sizeof(num));//初始化
		int now = a[i].size();//当前加数的长度
		for(int j = 0;j < now;j++) num[now - 1 - j] = a[i][j] - '0';//加数 
		for(int j = 0;j <= max(wei,now);j++)
		{
			if(i == 1) k = 0;//第一个加数自己不用进位处理 
			ans[j] += k + num[j];//加法 
			k = ans[j] / 7;//进位 
			ans[j] %= 10;//每一位在0-9之间 
		}
		now = max(wei,now);
		while(k != 0)//还需进位 
		{
			//继续模拟加法 
			ans[++now] += k + num[now];
			k = ans[now] / 7;
			ans[now] %= 10;
		}
		wei = max(wei,now);//保存最大长度 
	}
	while(ans[wei] == 0) wei--;//去除前导零 
	if(wei < 0) cout<<0<<endl;//等于0的情况特判 
	else
	{
		for(int i = wei;i >= 0;i--) cout<<ans[i];//正常输出 
		cout<<endl;
	}
	return 0;
}
```



---

## 作者：Remake_ (赞：3)

$rank17$选手来写题解了。

说实话，这道题非常签到，是一道非常水的模拟，处理好进位，基本上这道题就能$AC$了。

为了万无一失，我用了字符串高精。

下面上代码（细节在注释中）：

```cpp
#include<bits/stdc++.h>
using namespace std;
string add(string str1,string str2){//加法
    string str;
    int len1=str1.length();//第一个串的长度
    int len2=str2.length();//第二个串的长度
    if(len1<len2){//通过比较大小来增加前导0
        for(int i=1;i<=len2-len1;i++)
           str1="0"+str1;
    }
    else{
        for(int i=1;i<=len1-len2;i++)
           str2="0"+str2;
    }
    len1=str1.length();
    int cf=0;//进位
    int temp;//该位的最终值
    for(int i=len1-1;i>=0;i--){
        temp=str1[i]-'0'+str2[i]-'0'+cf;
        cf=temp/7;//处理进位
        temp%=10;//按要求%10
        str=char(temp+'0')+str;//将其转化为字符
    }
    if(cf!=0)  str=char(cf+'0')+str;
    return str;
}
int main(){
	int a;
	string b,c;
	cin>>a>>b;
	for(int i=1;i<a;i++){
		cin>>c;
		b=add(b,c);//b为最终答案，一直将c加到b中
	}
	cout<<b;输出答案
}
```


---

## 作者：do_while_false (赞：3)

【大概思路】

首先这题最后算出的答案非常大，我们需要用字符串存储。

其它的按题意模拟即可。

【具体代码】

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string now,add;
int main() {
	scanf("%d",&n);
	cin>>now;//读入 
	for(int i=2;i<=n;i++) {
		cin>>add;
		if(add.size()!=now.size())
			if(now.size()>add.size())
				while(now.size()>add.size())
					add.insert(0,"0");
			else
				while(now.size()<add.size())
					now.insert(0,"0");//根据题目的要求模拟 
		now.insert(0,"0");
		add.insert(0,"0");
		for(int j=now.size()-1;j>0;j--) {
			if(now[j]+add[j]>='7'+'0') now[j-1]++;
			if(now[j]+add[j]>('0'+13+'0')) now[j-1]++;
			now[j]=int(now[j]-'0'+add[j]-'0')%10+'0';//按照题目的要求运算 
		}
		while(now[0]=='0') now.erase(0,1);//删掉前导零 
	}
	cout<<now;
	return 0;
}
```

---

## 作者：荷叶下 (赞：1)

## 题意
##### 与高精度加法思想类似
##### 给定几个数,计算加起来的值
---
## 实现
##### 1.先比较两个数字的位数
##### 哪个数字小在哪个数字前加前导0
```cpp
while(len1 < len2)
{
    x = "0" + x ;
    ++len1 ;
}
while(len1 > len2)
{
    y = "0" + y ;
    ++len2 ; 
}
```
##### 2.从后向前一位一位计算
```cpp
for(int i = len1 - 1 ; i >= 0 ; --i)
{
    sum = x[i] - '0' + y[i] - '0' + t ;
    t = sum / 7 ; sum %= 10 ;
    z = char(sum + '0') + z ;
}
if(t != 0)
    z = char(t + '0') + z ;
```
##### AC代码
```cpp
#include <bits/stdc++.h> //万能头文件
using namespace std ;
int n ;
string a , ans ;

string add(string x , string y)
{
    string z ;
    int len1 = x.size() , len2 = y.size() , t = 0 , sum ;
    while(len1 < len2)
    {
        x = "0" + x ;
        ++len1 ;
    }
    while(len1 > len2)
    {
        y = "0" + y ;
        ++len2 ; 
    }
    for(int i = len1 - 1 ; i >= 0 ; --i)
    {
        sum = x[i] - '0' + y[i] - '0' + t ;
        t = sum / 7 ; sum %= 10 ;
        z = char(sum + '0') + z ;
    }
    if(t != 0)
        z = char(t + '0') + z ;
    return z ;
}

int main()
{
    cin >> n ;
    cin >> ans ;
    for(int i = 2 ; i <= n ; ++i)
    {
        cin >> a ;
        ans = add(ans , a) ;
    }
    cout << ans ;
    return 0 ;
}
```
###### 感谢观看

---

## 作者：lingfunny (赞：1)

前言：看到各位用string还有结构体的dalao，蒟蒻深感无力。我这边只使用了类似高精度想法的代码，处理方式较简单。

# 分析
首先，题意就是给出$n$个数，从左到右进行加法计算，不过这个计算需要按照特殊规则。这样，我们第一个条件就分析完了。

接下来是第二个条件，“若两个数的位数不同，**则位数少的数自动在前面补前导零**，直到两数位数相同。”本蒟蒻嗅到一丝平常高精的气息，便突发奇想。

然后第三和第四个条件则可以理解为高精的进位规则，只要会压位的童鞋这个转化起来都没什么问题。

第三个条件：**从两个数的最低位开始，计算当前位两个数码的和加上前一位的进位，写上这个和除以 $10$ 的余数。** 显然这就是正常的十进制运算的规则。

第四个条件：**进位规则：如果当前位两个数码的和加上前一位的进位小于 $7$，不进位；如果和大于等于 $7$ 且小于等于 $13$，则进一位；否则进两位。** 所以只需要根据这个进位条件写一个条件语句即可。

# 示例代码：
```cpp
#include <iostream>
#include <cstring>		//判断字符串长度需要用到
using namespace std;
int n;
int sum[100005];		//该数组储存当前答案
int tmp[100005];		//该数组则储存最新要被操作的数
long long a;			//中间变量，用来输入数字并将其转换为高精度数
long long sumlen;		//可以用int，是用来储存sum这个数的长度，高精度必备
long long tmplen;		//同上
int main(){
	cin>>n;
	cin>>a;
	while(a!=0){
		sum[++sumlen]=a%10;
		a/=10;
	}
	//sum倒序存储 
	for(long long i=2;i<=n;i++){
		tmplen=0;
		for(int i=1;i<=10;i++)tmp[i]=0;			//要先将tmp置空，否则会出错
		cin>>a;
		while(a!=0){
			tmp[++tmplen]=a%10;
			a/=10;
		}										//将新读入的数转化到tmp里面
		int x;									//x代表进位
		for(long long j=1;j<=tmplen || j<=sumlen;j++){
			x=0;
			sum[j]+=tmp[j];
			if(sum[j]<7)continue;				//如果第j位相加后还小于7，则不用进位，进入下层循环
			else if(sum[j]>=7 && sum[j]<=13)x=1,sum[j]%=10;	//条件4
			else x=2,sum[j]%=10;							//条件4
			sum[j+1]+=x;									//下一位进位
		}
		sumlen=max(tmplen,sumlen)+1;				//先假设最高位进位了
		while(sumlen!=0 && sum[sumlen]==0)sumlen--;	//如果没进位，则到退回来
	}
	for(long long i=sumlen;i>=1;i--)
	cout<<sum[i];
   //输出答案，完美结束
	return 0;
} 
```
**如有错误还望指出，蟹蟹**

---

## 作者：Hexarhy (赞：1)

签到题，细心模拟。心烦的时候可以来做这题。

--------

### 解题思路

题目说的很清楚了，考虑怎么实现。

显然为了模拟**竖式加法**，我们需要采用高精度。至于怎么存，`string`和`int[]`都可以。

这里采用了前者，因为方便插入前导 $0$。

按照题面所述一步步来：

- 反转字符串或倒序遍历数组，使得从右到左进行竖式加法。

- 比较两个数长度，补足前导 $0$。

- 为了方便进位，我们开一个 res 来保存答案。遍历 $[1,n)$， 第 $i$ 位相加，第 $i+1$ 位进位。**注意：由于进位可能导致 res 的长度大于这两个数的长度，因此 res 要开大点长度，用 $0$ 填充即可。**

- 删除 res 的前导 0，再次反转。此时即为两个数相加的答案。

上述过程可以编写为一个函数，每次相加调用这个函数即可。

### 实现细节

一个小坑点，出现在第一次相加的时候。

我们的累加的答案 ans 必须作为第一个数进行输入，而非作为 $0$ 来加上第一个数更新答案。

为什么呢？因为进位机制。

如果第一个数是 $7$。那么 $0+7=17$，可是作为第一个数，它是没有进行任何运算的， ans 应该等于 $7$。


### 参考代码

本代码需要 C++11。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
using namespace std;

int n;
string ans;

string calc(string a,string b)
{
	string res;
	const int len=(int)max(a.size(),b.size());
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	for(int i=0;i<len+4;i++)
	 res.push_back('0');
	while(a.size()<b.size()) 
	 a.push_back('0');
	while(b.size()<a.size())
	 b.push_back('0');
	auto ctoi=[=](const char c){return int(c-'0');};
	auto itoc=[=](const int i){return char(i+'0');};
	for(int i=0;i<len;i++)
	{
		const int num=ctoi(a[i])+ctoi(b[i])+ctoi(res[i]);
		if(num>=7 && num<=13)
		 res[i+1]='1';
		if(num>13)
		 res[i+1]='2';
		res[i]=itoc(num%10);
	}
	for(auto it=res.end()-1;*it=='0';it--)
	 res.pop_back();
	reverse(res.begin(),res.end());
	return res;
}

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>ans;
	for(int i=2;i<=n;i++)
	{
		string s;cin>>s;
		ans=calc(ans,s);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Dovuq (赞：0)

这是本蒟蒻的第 $001$ 篇题解，求过

很显然，最终答案肯定会超过 long long 的范围。所以必须使用高精度计算。

~~看下面的大佬们都用的 string，也许用 string 简单，但是因为我太弱，不懂这个道理。~~

下面是 $\colorbox{green}{\color{white}AC}$ 代码，细节见注释。

```cpp
#include <bits/stdc++.h> //万能头文件真好用
using namespace std;
struct bigint
{
	int size,num[5005];
	bigint() //每次定义 bigint 时都要清零，这里坑了我好几次
	{
		size=0;
		memset (num,0,sizeof(num));
	}
};
int n;
bigint ans,a[2025];
bigint cal (bigint x,bigint y) //计算两个数字的“和”
{
	if (x.size<y.size) swap(x,y); //让 x 的位数大于等于 y，这样便于后面的判断
	bigint c;
	c.size=x.size;
	int d=0; //进位
	for (int i=0;i<x.size;i++)
	{
		c.num[i]+=x.num[i]+y.num[i]+d;
		d=(c.num[i]<7?0:(c.num[i]<14?1:2)); //不知道 ?: 表达式的自行百度
		c.num[i]%=10;
	}
	if (d) //如果最高位还有进位
		c.num[c.size++]=d;
	return c;
}
istream& operator>> (istream &is,bigint &x) //便于使用 cin 输入
{
	int n,i=0;
	is>>n; //数据范围只有 10^9，所以可以直接用 int 输入
	for (;n;i++)
	{
		x.num[i]=n%10;
		n/=10;
	}
	x.size=i;
	return is;
}
ostream& operator<< (ostream &os,bigint x) //便于使用 cout 输出
{
	for (int i=x.size-1;i>=0;i--)
		os<<x.num[i];
	return os;
}
```

下面是美丽的主程序

```cpp
int main ()
{
	scanf ("%d",&n);
	for (int i=0;i<n;i++)
		cin>>a[i];
	ans=a[0];
	for (int i=1;i<n;i++)
		ans=cal(ans,a[i]);
	cout<<ans;
	return 0;
}
```

The end.

---

## 作者：Vector_ (赞：0)

$Update$:更正错别字,添加注释

这题思维难度不大，按照题意模拟即可。

但是有几个坑点要注意一下

1. 不能从0累加。

原因：一个数+0可能因为题意进位规则不等于原数。如

```cpp
0+7=17
```

2. 要开好足够的数组位数。

原因：看似答案不会超过n*max($a_i$),但每次运算都有可能进一位。

```cpp
7+0=17
17+0=27
...
67+0=177
```
~~自己写的时候这里不知道卡了我多久~~

主义之后按题意直接模拟即可。

AC代码:
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
//这里使用了结构体来实现题目中的“十进制数”及其加法。
struct num
{
	int a[5001];//存储每一位的
	num(){for(int i=1;i<=5000;i++) a[i]=0;}//构造函数，初始化
	num(int x){int p=0;while(x){int now=x%10;x/=10;a[++p]=now;}for(int i=p+1;i<=5000;i++) a[i]=0;}//构造函数，分解每一位后存储，并初始化剩余数位
	void print()
	{
		bool ok=false;
		for(int i=5000;i>=1;i-数字-)
		{
			if(a[i]!=0) ok=true;
			if(ok) printf("%d",a[i]);
		}
	}//输出函数
	num operator + (const num &b) const{
		int add=0;
		num ans;
		for(int i=1;i<=5000;i++)
		{
			int tmp=a[i]+b.a[i]+add;
			ans.a[i]=tmp%10;
//			cout<<i<<" ";ans.print();cout<<endl;
			if(tmp<7) add=0;
			else if(tmp<=13) add=1;
			else add=2;
		}
		return ans;
	}//加法
};
int main()
{
	int n;
//  freopen("sj.txt","r",stdin);
	scanf("%d",&n);
	int s;
	scanf("%d",&s);
	num ans=s;
	for(int i=2;i<=n;i++)//不能从0累加
	{
		int x;
		scanf("%d",&x);
		num tmp=x;
//      ans.print();
		ans=ans+tmp;
	}
	ans.print();
	return 0;
}
```

---

