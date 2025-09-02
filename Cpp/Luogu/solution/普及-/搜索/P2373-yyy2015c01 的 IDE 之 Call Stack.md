# yyy2015c01 的 IDE 之 Call Stack

## 题目背景

在 2020 年的某一天，我们的 yyy2015c01 同学想要开发一套 IDE。


## 题目描述

作为他开发团队中的一员，你不幸地 yyy2015c01 被选入了 Debugger 的开发组。

yyy2015c01 设想的 Debugger 由几部分组成，其中的一个小组件就是 Call Stack——中文称之为 “调用栈”。

由于 IDE 目前还是内测版，开发组需要先编一个能识别参数表的 Call Stack 来看看效果如何。这个任务交由你来完成。

开发组假想的 Call Stack 能实现识别 `int` 和 `char` 参数表，以辨别出不同的函数，规则是：

```
int fac1(int n);
```

和

```
int fac1(char n);
```

是两个不同的函数；但

```
int Fac1(int n,int m);
```

和

```
int FAC1(int x,int y);
```

被认为是相同的函数。也就是说，这个 Call Stack 认的不是参数名，而是其类型和忽略大小写的函数名。

注意：`int main()` 可能会出现，也可能不出现；无论它有没有出现，都不能将其算入函数中。

请你编写一个 Call Stack，并在所有函数调用完后输出这个程序一共有多少个不完全相同的函数（保证程序中的每个函数至少调用一次）。


## 说明/提示

每个函数的参数最多有 $10$ 个，每行的输入数据长度均不超过 $255$。

向本题主人公 yyy2015c01 同学致敬！


## 样例 #1

### 输入

```
2
FAC1 (N=233, M=65 'A', A=0)
main ()
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
fac1 (N=250)
FAC1 (a=987)
```

### 输出

```
1
```

# 题解

## 作者：Alex_Wei (赞：18)

这是一道模拟题，有些细节需要注意。

---

主要思路：

声明一个结构体 $\mathrm{'fact'}$：里面装一个字符串（函数名）和一个 $\mathrm{int}$ 类型的 $\mathrm{vector}$。

再用一个 $\mathrm{'fact'}$ 类型的 $\mathrm{vector}$ 存储答案，最后输出它的大小即可。

- 判断是否重复：如果参数个数一样，函数名字相同，且每个参数类型相同，那么这两个函数就相同。

- 可以单独写函数来输入并处理参数，这样程序可读性更高。

---

实现细节见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
struct fact{
	string na;//函数名 
	vector <int> para;//由于不知道参数个数，所以最好用vector存参数类型
};
int n;
vector <fact> ans;//答案
int strcmp(string a,string b)//判断两个字符串是否相同（因为不会用现成函数，所以只好手写strcmp） 
{
	if(a.size()!=b.size())return 0;
	for(int x=0;x<a.size();x++)if(a[x]!=b[x])return 0;
	return 1;
}
vector <int> getpara()//获取参数类型的函数
{
	string p;
	int pc=0;//0：数字，1：字符
	vector <int> para;//各个所输入参数的类型
	getline(cin,p);//由于有空格，所以需要用getline 
	for(int x=0;x<p.size();x++){
		if(p[x]==','||p[x]==')')para.pb(pc),pc=0;//一个参数结束，将它的类型压入vector
		if(p[x]==39)pc=1;//如果有单引号，那么这个参数就是字符类型
	}
	return para;//返回所有参数类型 
}
int main()
{
	cin>>n;
	for(int x=1;x<=n;x++){
		string na;//函数名 
		cin>>na;
		for(int y=0;y<na.size();y++)if(na[y]<'a')na[y]+=32;//都转为小写
		if(strcmp(na,"main"))continue;//判断是否是 "main" 函数
		int same=1;//same：是否重复
		vector <int> para=getpara();//获取参数类型
		for(int y=0;y<ans.size();y++){//和已有答案去重
			fact cmp=ans[y];
			if(cmp.para.size()!=para.size()||!strcmp(cmp.na,na))same=0;//参数个数不同或函数名不同
			else for(int z=0;z<cmp.para.size();z++)
					if(cmp.para[z]!=para[z])same=0;//参数类型不同
		}
		if(!same||x==1)ans.pb((fact){na,para});//如果不重复或者才调用第一个函数，那就把这个函数压入答案
	}
	cout<<ans.size();
	return 0;
}
```

$\mathrm{Upd:2019.12.11:}$ 添加 $\mathrm{Latex}$，美化文章。

---

## 作者：liuxy1234 (赞：4)

这是不大不小的模拟，以下提供本人思路：

1. 输入每一个字符串。

2. 先找到函数中的等号,也就是参数个数。

3. 将 int 类型的参数设为 $1$ ,将 char 类型的参数设为 $0$。

4. 将变小写的函数名和表示参数类型的 $01$ 串放进一个结构体，用来判重 （ main 函数要去掉 ） 。

5. 输出不重复的函数数就行了。

---

## 作者：OoXiao_QioO (赞：3)

# 前言

此题解仅适用于 ```C++11``` 版本，代码中用到了 ```gets()``` 来读入，但是 ```C++14``` 并不支持 ```gets()```，可以自己来写一个读入函数，但这里~~我偷懒了~~，大家请见谅。

# 题目描述简化

给出 $n$ 个函数，将他们的函数名、参数进行比较，输出有几个不同的函数，定义不同的函数即忽略大小写后，函数名字，各个参数的类型有一项或多项与前面的函数不符，输出不同函数的个数。

# 思路

看了别的大佬的题解，小蒟蒻真心觉得这道题不至于让数据结构大家族```vector```、```map```、```pair``` 一起上阵，反而可以用一些巧妙而又简单的想法轻松解决这道题。

我们可以定义一个 ```string``` 类型的字符串 $x$，$x$ 的组成是函数名 $+$ 参数的类型（这里可以用 $1$ 表示 ```int```，用 $0$ 表示 ```char```。），例如样例中的 ```FAC1 (N=233, M=65 'A', A=0)``` 可以简写为 $\verb!fac1101!$，把简写完的字符串扔到桶里面，最后输出一下桶内元素的数量即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//这里桶我用的是 map 存储，很方便。 
map<string,int> M;

string x;
char s[100001],s1[100001];//s 和 s1 没定义成 string 是因为后面的读入方式不同。 

int main()
{
	//定义变量 
	
	int n,i,l,cnt=0,f;//f 表示当前参数的类型，1 为 int，0 为 char。 
	
	//输入
	 
	cin>>n;
	
	//处理
	 
	while(n--)
	{
		scanf("%s",s);
		l = strlen(s);
		if(strcmp(s,"main")==0)//题目说明了不能统计 main 函数，只要出现了 main 就立即返回，执行下一次操作。 
			continue;
		//把字符串转化为小写统计比较方便（题目说了，要忽略大小写）。 
		for(i=0;i<l;i++)
			if(isupper(s[i])) 
				s[i] += 32;
		//根据 x 的定义，函数名 + 各个参数的类型，所以我们需要把 x 初始化为字符串 s。 
		x = s;
		getchar();//注意看输入的时候，函数名与括号隔了一个空格，所以我们需要把空格吞掉，防止误操作。 
		gets(s1);
		l = strlen(s1);
		for(i=0;i<l;i++)
		{
			f = 1;//f 初始化为 1，表示为 int 类型。 
			if(s1[i]=='=')//开始判断是否为字符类型 
			{
				while(s1[i]!=','&&i<l)//根据样例的研究，是否为字符类型的关键是在于有没有出现单引号，而单引号肯定在等号的后面，逗号的前面，我们只需要根据这个区间进行判断就可以了。 
				{
					i++;
					if(s1[i]=='\'')//如果这个符号是单引号，我们就知道这个参数的类型不是 int，那么将 f 变成 0,并及时 break。注意判断的时候要加上转义字符。 
					{
						f = 0;
						break;
					}
				}
			}
			if(f)//根据 f 的值来进行决定。 
				x += '1';//在这里就体现出 string 的妙用了，我们直接在后面加上字符 '1' 即可。 
			else
				x += '0';//否则就是 int 类型，在 x 后面接上 '0'。 
		}
		if(M[x]==0)//来看看桶里面有没有这个简写后的字符串 x。 
			cnt++;//没有，计数器 cnt++。 
		M[x] = 1;// 把当前字符串的位置标上 1。 
	}
	cout<<cnt<<endl;//输出 
	return 0;//结束 
}
```


---

## 作者：zimingsun23 (赞：3)

# 这是一道模拟题

题意大概是：判断变量名是否相同和，含参是否相同

------

因为每个函数的参数最多有 10 个，每行的输入数据长度均不超过 255。

~~所以这道题可以随便暴力~~

主要思路：

用一个包含函数名称和参数的

``
map<pair<vector<bool>,string>,bool>
``


来判重

判断是字符还是数字可以用引号，因为每个字符后面都有引号，可以通过打标记来判断是数字还是字符。

------

代码细节:

·大小写转换

``
for(char &cs:a) cs=tolower(cs);
``

·注意 main 函数

最后附上源码
```
#include<bits/stdc++.h>
#define r register
using namespace std;

map<pair<vector<bool>,string>,bool> pd;
#define mp make_pair

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	r int n,ans=0;
	r bool pds=0;
	r string a,b,c;
	cin>>n;
	for(r int i=1;i<=n;++i)
	{
		cin>>a>>b;
		c="";
		vector<bool> dq;
		for(char &cs:a) cs=tolower(cs);
		if(a=="main") continue;
		while(b[b.length()-1]!=')')
		{
			cin>>b;
			for(r int j=b.length()-1;j>=0;--j)
			{
				if(b[j]=='=') break;
				else if(b[j]=='\'') 
				{
					pds=1;
					dq.push_back(0);
					break;
				}	
			}
			if(!pds) dq.push_back(1);
			pds=0;
		}
		if(pd[mp(dq,a)]==0) 
		{
			pd[mp(dq,a)]=1;
			++ans;
		}
	}
	cout<<ans;
	exit(0);
}
```

---

## 作者：ZXXS (赞：2)

### 思路
这道题属于一个模拟题，使用 set<pair<string,string> > 维护函数是否重复。第一项判断函数名，第二项判断参数类型。

#### 判断函数名
1. 函数名与后面的参数中间有一个空格，所以可以用 cin 先来输入变量名。
1. 因为函数名不区分大小写，所以可以把函数名每一个小写字母转化成大写字母，方便之后判断参数。
1. main 函数需要去除，发现是 main 函数后要把后面的括号部分读入，方便判断下一个函数。

#### 判断参数
1. 使用 getline 函数读入一整行参数。

1. 如果是空参数直接加入 set。

1. 逗号分割两个参数。遍历字符串，判断每一个字符是否为逗号(,)，如果是，就要看他前面是否有单引号(')，后面是否有单引号，分三种情况：
- 前面有单引号:逗号前的参数类型为 char，用1表示;
- 前面没有单引号:逗号前的参数类型为 int，用0表示;
- 前后都有单引号:逗号为一个字符，不应计入总数;

4. 最后一个参数后没有逗号，所以要手动加上。
#### 去重
最后存在 set 中去重。

### 代码
```cpp
#include<iostream>
#include<set>
using namespace std;
set<pair<string,string> > se;
int m; 
string s,a;
int main()
{
	scanf("%d",&m);
	for(int i=1;i<=m;++i)
	{
		cin>>s;
		if(s=="main")//去除main函数
		{
			getline(cin,s);//读入后面的“()”
            continue;
		}
		for(int i=0;i<s.size();++i)
		{
			if(s[i]>='a'&&a[i]<='z')//小写字母转大写字母
			{
				s[i]+='A'-'a';
			}
		}
		a=s;
		getline(cin,s);
		s[s.size()-2]=',';//手动加逗号
        if(s=="()")//空串
        {
            se.insert(make_pair("",a));//去重
        }
        string p="";//储存参数类型，0为int，1为char
		for(int i=0;i<s.size();++i)
		{
			if(s[i]==',')
			{
				p+=(s[i-1]==39&&s[i+1]!=39?'1':'0');//判断前后是否有单引号，'的ASCLL码=39
			}
		}
		se.insert(make_pair(p,a));//去重
	}
	printf("%d\n",se.size());
    return 0;
}

```

---

## 作者：UnyieldingTrilobite (赞：2)

~~感觉最近比较颓缩以按照习惯来刷模拟~~

首先，相当于求函数名不同或参数类型（int/char）不同的函数个数

由于只有两种状态缩以珂以变一下：

用0记录int,1记录char.

用函数名（string）+函数参数类型列表记录一个函数。

把这些函数全扔到一个set里。（感受一下：set<pair<string,vector\<bool> > >）

然后就是大模拟了~

由于空格的福音缩以珂以直接cin>>函数名，少了一些判断（真好）。

上主要代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool operator < (const vector<bool>&a,const vector<bool>&b){
	if(a.size()!=b.size())return a.size()<b.size();
	for(register int i=0;i<a.size();++i){
		if(a[i]^b[i])return b[i];
	}
	return 0;
}//扔set写个比较器（当然其实吧数据范围这么小vector也没问题）
set<pair<string,vector<bool> > >st;
string input;
int n;
vector<bool>p;
bool readnxt();//见下
int main(){
	cin>>n;
	while(n--){
		cin>>input;
		for(int i=0;i<input.size();++i)if(isupper(input[i]))input[i]=input[i]-'A'+'a';//统一转小写
		if(input=="main"){
			getline(cin,input);
			continue;
		}//特判main()包
		for(p.clear();readnxt(););//读入参数类型列表
		st.insert(make_pair(input,p));//插入新函数
	}
	cout<<st.size()<<endl;
    return 0;
}
```
现在就考虑怎么实现readnxt(读取下一个参数类型并返回是否到头）

首先，如果直接“撞墙”了（无参数），那么肯定返回0；

缩以需要一个布尔值tag表示是否只有();

然后想想字符和数字的最大区别，主要就在于单引号；

于是每读入一个字符就判断，如果是单引号，那么这个参数就是字符。

其他就没什么坑点了：
```cpp
bool readnxt(){
	bool f=0,tag=0;//f:是否为字符;tag:是否没“撞墙”
	char c=getchar();//一个个读取（类似快读？）
	while(c!=','&&c!=')'){//当这个参数还没读完
		if(c!='(')tag=1;//并没有撞墙（撞墙就是()，第一次c=='('不更新tag,第二次直接跳出循环）
		if(c==39)f=1;//单引号
		c=getchar();
	}
	if(tag)p.push_back(f);//新参数读取完成
	return c!=')';//是否到尾
}
```
至于完整代码······

~~嗯，要抄袭的话直接先Ctrl+C+V第一段然后Ctrl+C+V第二段就行了，函数声明是一种合法的写法。~~

最后推销[blog](https://www.luogu.com.cn/blog/2007100723874wxz/)。

---

## 作者：伏地魔老杨 (赞：1)

## 思路

[本题](https://www.luogu.com.cn/problem/P2373)是一道模拟题，题目要求我们找出有多少个不同的函数，每个函数分为函数名和一些参数。函数名是不区分大小写的，参数类型有 int 和 char 两种。

所以我们可以开个结构体，记录函数名和每个参数类型，然后依次去跟其他函数比对。需要注意的是，参数不区分参数名，只区分类型。对于参数类型，我们不难发现，如果这个参数是 int 类型的话，它的格式应该是 `参数名 + 等号 + 整数`。如果是 char 类型则是 `参数名 + 等号 + 字符ASCII码 + 空格 + '字符'`。 所以我们只要识别到当前位置为数字且如果下一位置是逗号或者是反括号的话，那么该参数就记录为 int 类型，如果下一位置是空格的话，则该参数为 char 类型。具体实现过程请看代码。

## 代码实现

```c
#include <iostream>
#include <string>
#include <map>
using namespace std;
int ans;
struct fun
{
	string name;//函数名称
	char par[15];//参数类型数组, i代表int, c代表char。
	int qua = 0;//计算参数数量
	void work(string a, string b)//将读入的字符串存储
	{
		name = a;
		int len = b.size(), cur = 0;//cur记录当前是第几个参数
		for (int i = 0; i < len; ++i)
		{
			if (b[i] >= '0' && b[i] <= '9' && (b[i + 1] == ',' || b[i + 1] == ' ' || b[i + 1] == ')'))
			{
				if (b[i + 1] == ',' || b[i + 1] == ')')//如果数字后面直接是逗号或是反括号，证明这个参数是int类型的。
				{
					++cur;
					par[cur] = 'i';
				}
				else//否则是char类型
				{
					++cur;
					par[cur] = 'c';
				}
			}
		}
		qua = cur;
	}
};
void change(string &s)//将所有大写字母转化成小写字母。
{
	int len = s.size();
	for (int i = 0; i < len; ++i) if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a';
}
int main()
{
	int n;
	cin >> n;
	fun f[n + 5];
	string a, b;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a;//读入函数名称
		change(a);//全变成小写
		getline(cin, b);//读入参数，注意参数中有空格，所以需要使用getline读入。
		if (a == "main") continue;//如果是main函数跳过。
		f[i].work(a, b);
		bool check = true;
        for (int j = i - 1; j >= 1; --j)
        {
        	if (a != f[j].name) continue;
        	if (f[i].qua != f[j].qua) continue;
        	bool flag = true;
			for (int k = 1; k <= f[i].qua; ++k)
			{
				if (f[i].par[k] != f[j].par[k])
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				check = false;
				break;//如果找到相同的，就打上标记结束寻找
			}
		}
		if (check) ans++; //如果没有相同的，ans++;
	}
	cout << ans;//输出答案
	return 0;//END~
}
````

[AC记录](https://www.luogu.com.cn/record/100818405)

**温馨提示：请勿抄袭题解！**



---

## 作者：TsReaper (赞：1)

一道比较容易的模拟题，以下提示一些简化程序的方法：

1、如何判断参数的个数呢？参数的个数等于“=”符号的个数。

2、如何判断参数的类型呢？如果某个参数“=”符号的后面有一个单引号，说明这个参数是char型的，否则就是int型的。

3、如何判断两个函数是否相同呢？先判断参数个数是否相同，然后判断函数名，再然后判断各个参数的类型。


---

