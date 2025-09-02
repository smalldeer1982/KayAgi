# yyy2015c01 的 IDE 之 Watches

## 题目背景

在 2020 年的某一天，我们的 yyy2015c01 同学想要开发一套 IDE。

## 题目描述

作为他开发团队中的一员，你不幸地被选入了 Debugger 的开发组。

yyy2015c01 设想的 Debugger 由几部分组成，其中的一个小组件就是 Watches——中文称之为“变量观察器”。

由于 IDE 目前还是内测版，开发组需要先编一个能观察 int 类型变量值的 Watches 来看看效果如何。这个任务交由你来完成。

开发组假想的 Watches 能实现如下 3 种语句运行后监测相应变量值的功能：
- `n=1;` 将常量赋给变量，保证这个常量的位数不大于 $9$。
- `a=b;` 变量之间赋值：若原变量（在本例中是 $b$）未被赋值则认为其初始值为 $0$。
- `m=1+2;` $A+B$ 表达式赋值，只有 `+` 且只有两个数或者变量，$A$ 和 $B$ 都介于 $1$ 至 $10^6$ 之间。

请你编写一个 Watches，并在所有语句运行完后对所有被赋值过的变量按标识符的字典序输出它们的值（保证不会有变量的值大于 int 的最大值）。


## 说明/提示

数据很弱，直接模拟过哟~

（别想着变量标识符只有一位哟！）

另：向本题主人公 yyy2015c01 同学致敬！

## 样例 #1

### 输入

```
3
a=233;
b=a;
c=a+b;```

### 输出

```
a 233
b 233
c 466```

## 样例 #2

### 输入

```
3
a=233;
b=1+1;
a=b;```

### 输出

```
a 2
b 2```

# 题解

## 作者：Okimoto (赞：5)

# P2366

### 这道题的算法十分明显：字符串+模拟

这道题难度不高，坑点几乎没有，~~居然是黄题~~。


------------

## Before AC

这道题可以拆分成三个部分，
### 1、输入
这道题最好的输入库其实是$<stdio.h>$, 因为其中的$scanf()$函数自带的$Negated$ $Scanset$（黑名单字符集）功能是真的香。

输入迎刃而解。
```cpp
char cx[32];
char cy[32];
scanf("%[^=]=%[^;];\n", cx, cy);
string a = cx;
string b = cy;
```

### 2、字符串处理和变量赋值
$<string>$ 自带的大小比较适用于本体的字典序输出，故此使用此字符串库
大致的字符串处理过程就是
  1. 判断B表达式是一个数字类型还是变量名类型
  2. 若B表达式是和的形式，拆分取值求和。若B表达式是变量名类型，还需取值
  3. 将A存入数据结构
  
PS：$<map>$是存储【变量标识符 - 变量值】键值对的理想数据结构
### 3、按照变量标识符的字典序输出
存一个$string$ 类型的数组，用来记录已有的变量名。
$<algorithm>$ 自带sort函数，自写cmp。
```cpp
bool cmp(string a, string b){
	return a < b;
}
```
$For$循环输出不解释。


------------
代码：
                 
```cpp
// By Sublime Text 3
// P2366, by Okimoto
// No copy, pls.
#include <stdio.h> // 标准输入输出
#include <map> // STL大法好b（￣▽￣）d　
#include <string> // 用string是因为string自带定义大小排序
#include <algorithm> // Sort
using namespace std;
int n;
map <string, int> mp; // 存输入的信息和数
string ans[128]; // 存储已输入的变量标识符 + 字典序排序
int ptr = 0; // ans的末尾下标记录变量，同时也是ans的长度
bool cmp(string a, string b){
	return a < b; // 字典序
}
int main(int argc, char const *argv[]){
	mp.insert(mp.begin(), pair<string, int>("__NULL__", 0)); // 对于a = b + c的代码处理a = b的情况时，将c假定成0
	scanf("%d\n", &n); // 输入n
	for(int i = 0; i < n; ++ i){
		char aa[32];
		char bb[32];
		scanf("%[^=]=", aa); // 输入直到遇见‘=’为止，顺便刷掉‘=’字符
		string a = aa;
		scanf("%[^;];\n", bb); // 刷掉‘；’ + 刷掉换行符
		string b = bb;
		if('0' <= b[0] && b[0] <= '9'){ // 若b变量是个数字类型的
			int sum = 0; // ‘+’字符之前的数
			int tmp = 0; // ‘+’字符之后的数
			int j;
			// 取sum
			for(j = 0; j < (int)b.size() && b[j] != '+'; j ++){
				sum *= 10;
				sum += b[j] - '0';
			}
			// 取tmp
			for(j = j + 1; j < (int)b.size(); j ++){
				tmp *= 10;
				tmp += b[j] - '0';
			}
			sum += tmp;
			if(mp.end() == mp.find(a)){ // 若a变量还未在mp中
				ans[ptr ++] = a; // ans记录a
				mp.insert(mp.begin(), pair<string, int>(a, sum)); // 将a推入mp
			}
			else
				mp[a] = sum; // 否则，将a的值改变
		}
		else{ // b变量是个变量类型的
			string x; // ‘+’字符之前的变量名
			string y; // ‘+’字符之后的变量名
			bool yFlg = true; // 判断是否没有‘+’以后的变量
			int j;
			// 取x
			for(j = 0; j < (int)b.size() && b[j] != '+'; j ++)
				x += b[j];
			// 取y
			for(j = j + 1; j < (int)b.size(); j ++){
				yFlg = false;
				y += b[j];
			}
			if(yFlg)
				y = "__NULL__";
			// 取数
			int sum = mp[x] + mp[y];
			//同理
			if(mp.end() == mp.find(a)){
				ans[ptr ++] = a;
				mp.insert(mp.end(), pair<string, int>(a, sum));
			}
			else
				mp[a] = sum;
		}
	}
	// 字典序排序
	sort(ans, ans + ptr, cmp);
	// 输出
	for(int i = 0; i < ptr; i ++)
		printf("%s %d\n", ans[i].c_str(), mp[ans[i]]);
	return 0;
}
// 谢谢大家阅读这篇题解，（づ￣3￣）づ╭❤～
```



---

## 作者：D2T1 (赞：3)

**蒟蒻发题解了！！！！**


------------

## 一道~~大~~模拟

思路：

1、读入一个字符串，将它分为**变量**和**赋值**两部分

```
变量=赋值;
```

2、再去检测赋值语句，有以下六种情况

```
变量
数字
变量+变量
变量+数字
数字+变量
数字+数字
```

3、判断赋值语句中有没有 '+'

```
如果有，把字符串中+的左右两边分开，分别判断是变量还是数字
如果没有，直接判断是变量还是数字。
```

4、将变量与变量的值使用map存储


### 所以程序有2个重点

1、分割字符串

```
由于本人太弱，不会用STL，所以可以这样解（伪代码）：

将字符串a沿‘=’分成2部分

循环（a的大小）次（i=0;i++）：
	定义 变量，赋值
   	如果 读入了等号 赋值+（a的第i位）
	如果 没有读入等号且该字符非等号 变量+（a的第i位）
```

2、检测是变量还是数字

```
由于变量的首位不能为数字
所以只用判断变量的第一位
```

## 代码：

```cpp
//P2366
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
using namespace std;
map<string,int> a;//存储变量+值
string bl_out[1005];//存储变量名，输出用
int bl_out_zz=0;//将变量名存储在bl_out里的位置

int stoi(string a){//string to int
	int ans=0;
	for(int i=0; i<a.size(); i++){
		ans*=10;
		ans+=a[i]-'0';
	}
	return ans;
}

bool find_plus(string a){//找+，判断语句类型
	for(int i=0; i<a.size(); i++){
		if(a[i]=='+') return true;
	}
	return false;
} 

bool if_num(string a){//判断语句开头是否是数字
	if(a[0]>='0' && a[0]<='9') return true;
	return false;
}

int main(){
	int n;
	cin >> n;
	for(int i=0; i<n; i++){
		string ain,bl="",fz="";//输入，变量，赋值qwq
		bool flag=true;
		cin >> ain;
		for(int i=0; i<ain.size(); i++){
			if(ain[i]==';')      break;//检测到分号退出
			else if(ain[i]=='=')   flag=false;//变量与赋值语句用=间隔
			else if(flag)        bl+=ain[i];
			else if(!flag)       fz+=ain[i];
		}
		bl_out[bl_out_zz]=bl;//将变量名存储起来
		bl_out_zz++;
		if(if_num(fz) && !find_plus(fz)){//变量=数字；形式语句
        //本人坑点1，赋值语句第0个字符是数字并不代表整个赋值语句是数字，还有可能是数字+数字或数字+变量的形式
			int int_fz=stoi(fz);//将赋值语句转换为数字
			a[bl]=int_fz;//用map存储变量
		} else if(find_plus(fz)){//变量=A+B；形式语句
			bool flag2=true;
			string left="",right="";//加号左边，加号右边
			for(int i=0; i<fz.size(); i++){//与47-52行同理
				if(fz[i]=='+')  flag2=false;
				else if(flag2)  left+=fz[i];
				else if(!flag2) right+=fz[i];
			}
			if(if_num(left) && if_num(right)){//有加号的语句的四种组成情况
				a[bl]=stoi(left)+stoi(right);
			} else if(if_num(left)){
				a[bl]=stoi(left)+a[right];
			} else if(if_num(right)){
				a[bl]=a[left]+stoi(right);
			} else {
				a[bl]=a[left]+a[right];
			}
		} else {//变量=变量；形式语句
			a[bl]=a[fz];
		}
	}
	sort(bl_out,bl_out+bl_out_zz);//将变量名排序
	for(int i=0; i<bl_out_zz; i++){
		if(bl_out[i]!=bl_out[i+1]){//记得检测是否有重复
			cout << bl_out[i] << ' ' << a[bl_out[i]] << endl;
		}
	}
	return 0;
}
```
### ~~编程要有模块化思想~~

---

## 作者：Ag2WO4 (赞：3)

~~Python大法好啊~~

## 解题思路

1. **第一步：运行输入语句**

Python 中有一个神奇的函数 ```exec()```，它的作用是把一个字符串当成代码来执行。本题直接循环使用该函数就可以得到相应的结果。

2. **第二步：调取变量**

Python 中还有一个神奇的函数 ```globals()```，它会以字典的形式输出所有全局变量名和变量各自的值。

**但是这个函数没有那么简单！**
- Python 3 中不能直接读取这个字典（在 Python 2 里可以），必须另做字典，不然会 RE（因为另生成两个变量去读取字典会导致字典的变化，这在 Python 3 中是不合法的）。
- 只是读取字典的话只能返回变量名，不能返回变量的值。
- Python 运行有底层变量（即程序一开始就存在的变量），当然不能输出它们。

这时，我们要叠加其他的函数，把它变成这个：
```python
globals().copy().items()
```
~~顾（英文）名思义，~~这是复制（即 ```copy()```，用它防止上述 RE 情况）后的全局变量字典里的每个项（即 ```items()```，它返回的不只是变量名，而是每个字典项的名称-内容有序对象对）。洛谷测评环境有 $9$ 个底层变量，加上计数变量和循环变量，我们应该从字典第 $12$ 项开始输出。这个计数由计数变量负责。

注意两个细节：
- 计数变量和循环变量，为了不和测评变量重复导致 WA，最好长一点，不要太简单（比如单出一个 $a$ 就会出错）。
- 全局变量字典的顺序是变量的定义顺序，所以计数变量要在程序的最开头先被定义！

## 参考代码
```python
_count_=0
for _loop_ in range(int(input())):
    exec(input().strip())
for _name_,_value_ in globals().copy().items():
	'''字典另做好后就固定下来了，这时定义 _name_ 和 _value_ 是安全的；
	由于 items() 返回的是对象对，所以分别用两个变量，各自抓取名称和值。'''
    _count_+=1
    if _count_>11:
        print(_name_,_value_)
```

---

## 作者：critnos (赞：2)

~~显然，STL库不是个好东西~~

如果把本题分为两部分，那就很简单了：**变量储存器**和**脚本解析器**

### 变量储存器：

一般想到的肯定是用一个map或者数组，然后#！@*&%……（此处省略10万字）

这里提供另一种思路：

首先，**变量的值只看最后一次赋值**

那么，如果每次都把每个操作存起来，事情就简单得多啦

定义一个结构体var(string name,int num)，然后开一个结构体数组，每次把输入的变量插入数组，具体是var(string 变量名,int 表达式的值)，注意：**前面的操作不管有没有定义这个变量都要重新插入**

### 脚本解析器

先分析一下脚本内容

```
变量1=变量（数）2（+变量（数）3）；
```
有一个清奇的思路：如果把所有的变量都变成数，那就容易得多了

函数不难写：

```cpp
int hvar(string b)
{
	for(int i=var_list.size()-1;i>=0;i--)
		if(var_list[i].name==b)
			return var_list[i].num;
}
```
注意一定要倒搜，因为**变量的值只看最后一次赋值**

貌似……貌似就没了？？？

```cpp
#include<bits/stdc++.h>
using namespace std; 
struct var
{
	string name;
	int num;
};
vector<var> var_list;//用了万恶的STL，因为不知道n有多大（据估50即可）
int hvar(string b)//变量转数字函数
{
	for(int i=var_list.size()-1;i>=0;i--)
		if(var_list[i].name==b)
			return var_list[i].num;
}
int main() 
{
    int n,i,f,h1n,h2n;
    char p;
    string b,h1,h2;
    cin>>n;
    for(i=0;i<n;i++)
    {
    	h1=h2=b="",h1n=h2n=0;
    	for(;;)//读入变量1
    	{
    		cin>>p;
    		if(p=='=') break;//注意：变量1的结束标识符是“=”
    		b+=p;
		}
		for(f=1;;)//读入变量（数）2
    	{
    		cin>>p;
    		if(p==';'||p=='+') break;
    		h1+=p,h1n=h1n*10+p-'0';//神奇的东西：同时把变量（数）2当作字符串和数来读入，这样省去了字符串转数的过程
    		if(p>'9'||p<'0') f=0;//f:标识变量（数）2是否为数
		}
		if(f==0) h1n=hvar(h1);//如果不为数则将它变成变量的值
		if(p==';') var_list.push_back(var({b,h1n}));//脚本以“；”结束，如果是分号则终止输入
		else
		{
			for(f=1;;)//同上
	    	{
	    		cin>>p;
	    		if(p==';') break;
	    		h2+=p,h2n=h2n*10+p-'0';
	    		if(p>'9'||p<'0') f=0;
			}
			if(f==0) h2n=hvar(h2);
			var_list.push_back(var({b,h1n+h2n}));
		}
	}
}
```
一切都很顺利……

然鹅……然鹅貌似少了什么……

### 输出

输出比较麻烦

先按关键字name排序，然后呢？

因为**变量的值只看最后一次赋值**，所以只输出最后一次出现的

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std; 
struct var
{
	string name;
	int num;
};
vector<var> var_list;
int hvar(string b)
{
	for(int i=var_list.size()-1;i>=0;i--)
		if(var_list[i].name==b)
			return var_list[i].num;
}
bool cmp(var a,var b)
{
	return a.name<b.name;
}
int main() 
{
    int n,i,f,h1n,h2n;
    char p;
    string b,h1,h2;
    cin>>n;
    for(i=0;i<n;i++)
    {
    	h1=h2=b="",h1n=h2n=0;
    	for(;;)
    	{
    		cin>>p;
    		if(p=='=') break;
    		b+=p;
		}
		for(f=1;;)
    	{
    		cin>>p;
    		if(p==';'||p=='+') break;
    		h1+=p,h1n=h1n*10+p-'0';
    		if(p>'9'||p<'0') f=0;
		}
		if(f==0) h1n=hvar(h1);
		if(p==';') var_list.push_back(var({b,h1n}));
		else
		{
			for(f=1;;)
	    	{
	    		cin>>p;
	    		if(p==';') break;
	    		h2+=p,h2n=h2n*10+p-'0';
	    		if(p>'9'||p<'0') f=0;
			}
			if(f==0) h2n=hvar(h2);
			var_list.push_back(var({b,h1n+h2n}));
		}
	}
	sort(var_list.begin(),var_list.end(),cmp);
	for(i=0;i<n-1;i++)
		if(var_list[i].name!=var_list[i+1].name)
			cout<<var_list[i].name<<' '<<var_list[i].num<<endl;
	cout<<var_list[n-1].name<<' '<<var_list[n-1].num;
}
```


---

## 作者：a___ (赞：2)

%楼上各位dalao，写这么长的代码。。。  
**STL**大法好  
代码:
```
#include<iostream>
#include<map>//map
#include<cstring>//string
using namespace std;
map<string,int>ma;//map映射变量值（全局变量初值为0，所以未赋值变量为0）
string s;int n;
int tonum(string s)//字符串转数字
{
	int i,lens=s.size(),a=0;
	for(i=0;i<lens;i++)a=a*10+s[i]-'0';
	return a;
}
int main()
{
	cin>>n;
    int a;string sa;
	map<string,int>::iterator iter;//map迭代器
	while(n--)
	{
		cin>>s;
		s.erase(s.size()-1,1);//erase(pos,len)删除从pos起的len个字符。这里删除分号
		a=s.find('=');//找'='的下标
		sa=s.substr(0,a);//substr(pos,len)返回pos起的len个字符。这里返回将要赋值的变量名
		s.erase(0,a+1);//删除变量名和等号
		a=s.find('+');//找'+'的下标
		if(a>=0&&a<s.size())//如果找到，返回可行下标
		{
			//'+'前
            if(s[0]>='a'&&s[0]<='z')ma[sa]=ma[s.substr(0,a)];//如果是变量，先附该变量值
			else ma[sa]=tonum(s.substr(0,a));//是数字，转换为数值，附给该变量
			s.erase(0,a+1);//删除'+'前部分和'+'
            //'+'后
			if(s[a+1]>='a'&&s[a+1]<='z')ma[sa]+=ma[s];//加上变量值
			else ma[sa]+=tonum(s);//加上数值
		}
		else//没有'+'
		if(s[0]>='a'&&s[0]<='z')ma[sa]=ma[s];//附变量值
		else ma[sa]=tonum(s);//附数值
	}
	for(iter=ma.begin();iter!=ma.end();iter++)//begin()返回开始指针,end()返回结尾指针（map是自带排序的）
	cout<<iter->first<<' '<<iter->second<<endl;//输出“变量名 数值”
	return 0;//40行左右结束
}
```
这是一道简单的模拟

---

## 作者：fjy666 (赞：1)

### 0x01 思路
考虑直接模拟。  
我们可以用 `scanf` 函数的字符集来完成“分裂”字符串。  
具体来说，`scanf` 的字符集长这样：  
`scanf("%[<^>[charset]]",str);`   
若前面有 ^ ，表示读到 `charset` 中的字符为止（不包含）。  
否则，代表读到非 `charset` 中的字符为止（不包含）。  
举个例子：  
`scanf("%[abc]",str);`  
`Input:abccdef`  
`str="abcc"`

------------
`scanf("%[^abc]",str);`  
`Input:defsafafas`  
`str="defs"`

然后，我们就可以~~大~~模拟啦！  
模拟时，考虑分类讨论。
- 无 `+` 号  
若是数字，`sscanf`它！  
否则，现在变量列表中找它。
	- **若不存在，初始化为 0，不保存在变量列表中。**
   -  否则，使用它的值。
   
- 有加号  
	分成两部分，对于每一部分，执行“无 `+` 号的操作。”
    
最后，输出整个变量列表即可。  

------------
$\Large{Tips}$  
- 变量列表可以用 `map` ,虽然复杂度 $\log n$，但是自带排序，还可以用 `iterator` 输出。
- 若程序有误，用 **输出中间变量** 的调试方法，调试地更方便哦~
- 局部变量最好附初值。

### 0x02 代码
```cpp
#include <cstdio>
#include <string>
#include <cstring> 
#include <map>
#define It(type_) type_::iterator
#define rtn return

typedef long long ll;
using namespace std;
const int kMaxn = 10001;

map<string,int> variables;
char cmd[kMaxn];
char left[kMaxn],right[kMaxn];
char r_1[kMaxn],r_2[kMaxn];

int main()
{
	int n;
	scanf("%d",&n);
	while (n--)
	{
		scanf("%s",cmd);
//		printf("cmd = %s.\n",cmd);
		sscanf(cmd,"%[^=]%*c%[^;]%*c",left,right);
//		printf("left = %s,right = %s.\n",left,right);
		if (strchr(right,'+') == NULL)
		{
			if (right[0] >= '0' && right[0] <= '9')
			{
				int tmp = 0;
				sscanf(right,"%d",&tmp); 
				variables[string(left)] = tmp; 
			} else {
				int tmp = 0;
				if (variables.count(string(right)))
					tmp = variables[string(right)];
				variables[string(left)] = tmp;
			}
		} else {
			sscanf(right,"%[^+]%*c%s",r_1,r_2);
			int p_1 = 0,p_2 = 0;
			if(r_1[0] >= '0' && r_1[0] <= '9')
				sscanf(r_1,"%d",&p_1);
			else 
				if (variables.count(string(r_1)))
					p_1 = variables[string(r_1)];
			if(r_2[0] >= '0' && r_2[0] <= '9')
				sscanf(r_2,"%d",&p_2);
			else 
				if (variables.count(string(r_2)))
					p_2 = variables[string(r_2)];
			variables[string(left)] = p_1 + p_2;
		}
	}
	for(map<string,int>::iterator it = variables.begin(); it != variables.end(); ++it)
		printf("%s %d\n",it->first.c_str(),it->second);
	rtn 0;
}
```

---

## 作者：AveMarina (赞：1)

## 字符串模拟
__首先考虑怎么存变量__:我考虑的是用map存，变量名就是key，后面的算式就是val，使用map存可以很方便的维护整个表达式

__其次我们考虑下有多少种情况__:\
1. 有一个数字，对应的解决方案就是直接将其转换为数字
2. 有一个已经存在的变量，对应的解决方案就是在map里把val取出来
3. 有两个数字，同1
4. 有两个已经存在的变量，同2
5. 数字和变量各有一个，这里就要判断下那个是变量那个是数字了，然后继续重复1和2

__接下来就可以愉快的模拟了__

__在此之前考虑几个细节__:
1. 如何将字符串转换为数字，可以手写一个函数，也可以用<sstream>头文件中的字符流函数这里我们使用手写函数的方式还原数字
2. 如何区分变量名，算式，以'='为分隔，'='左边就是变量名，右边就是算式
3. ~~Dev C++标准太低~~没有unorder_map怎么按顺序输出答案，用一个vector存放所有变量名即可
```cpp
#include <iostream>
#include <cstdio>
#include <map> 
#include <vector>
using namespace std;
typedef long long LL;
vector<string > vec;
map<string, LL > mp;
// 字符串转数字，可以用字符串流，但是没必要 
LL strToNum(string str) {
	LL res = 0;
	int sLen = str.size();
	for (int i = 0; i < sLen; i++) res = res * 10 + (int)(str[i] - '0');
	return res;
}
int main() {
	int n;
	scanf("%d", &n);
	string str;
	while (n--) {
		cin >> str;
		int sLen = str.size();
		bool flag = true, rflag = true;
		string varname;
		string left = "", right = "";
		for (int i = 0; i < sLen - 1; i++) {
			// 处理=左边的变量名 
			if (str[i] != '=' && flag) {
				varname += str[i];
			} else {
				flag = false;
				if (str[i] == '=') continue;
				// 处理=右边的算式，分两种情况讨论 
				if (str[i] != '+' && rflag) {
					left += str[i];
				} else {
					rflag = false;
					if (str[i] == '+') continue;
					right += str[i];
				}
				
			}
		} 
		// cout << varname << ' ' << left << ' ' << right << endl;
		if (!mp.count(varname)) vec.push_back(varname);
		// 几种情况，只有一个算式，且该算式是一个数字
		// 只有一个算式，或该算式是一个已经存在的变量
		// 有两个算式，一个是数字，一个已经存在的变量
		// 有两个算式，两个都是数字/已经存在的变量 
		// 处理只有一个算式的情况
		if (rflag) {
			// 如果是一个已存在的变量，那么把它的值赋值给当前变量 
			if (mp.count(left)) {
				mp[varname] = mp[left];
			} else {
				// 相反就是一个数字，直接赋值
				mp[varname] = strToNum(left); 
			}
		} else {
			bool mflag = mp.count(left) && mp.count(right);
			 // 如果都是变量，直接相加 
			 if (mflag) mp[varname] = mp[left] + mp[right];
			 // 如果都不是变量，也是直接相加 
			 else if (!mflag) mp[varname] = strToNum(left) + strToNum(right);
			 // 如果有一个不是变量，分情况处理
			 else if (!mp.count(left)) mp[varname] = strToNum(left) + mp[right];
			 else mp[varname] = mp[left] + strToNum(right);
		}
		// cout << varname << ' ' << mp[varname] << endl;
	}
	int vLen = vec.size();
	for (int i = 0; i < vLen; i++) {
		cout << vec[i] << ' ' << mp[vec[i]];
		if (i != vLen - 1) cout << endl;
	}
	return 0;
}
```
 代码很长，但是有注释啊QAQ


---

## 作者：牟一帆mou__yifan (赞：1)

```cpp
//典型的字符串处理~~~
var
  n,i,j,k,t,v,p,q,s,pd4,c,c1,c2:longint;
  st,pd1,pd2,pd3:string;
  r,ans:array[1..100000] of longint;
  tr:array[1..100000] of string;
begin
  readln(n);
    for i:=1 to n do begin
    readln(st);j:=pos('=',st);//读入并记录等号在字符串中的位置，这样便于记录等号前面的变量
    for k:=1 to j-1 do pd3:=pd3+st[k];//变量记录。注：由于变量可能不止一位，所以不能写成pd3:=st[1]!!!
    for v:=1 to n do//判断此变量在前面有没有出现过
      if tr[v]=pd3 then begin//如果出现
      p:=v;//则要改变的变量在v位置，赋值到p中
      pd4:=1;pd4变成1
      break;//退出循环，避免超时
    end;
      if pd4<1 then begin
      tr[i]:=pd3;//如果没有出现，就将其加到这个数组里去
      r[i]:=1;//表明这个变量被赋值过
      p:=i;//要改变的变量在i位置
    end;
    t:=pos('+',st);//寻找加号的位置
      if t<>0 then begin//若有加号
      pd1:=copy(st,j+1,t-j-1);
      pd2:=copy(st,t+1,length(st)-t-1);//将加号两端复制下来
        if ord(pd1[1])<64 then begin//如果两端都是数
        val(pd1,c1);val(pd2,c2);
        ans[p]:=c1+c2;//转型相加即可
      end
        else begin//若不是数
          for q:=1 to n do if tr[q]=pd1 then begin
          c1:=ans[q];break;
        end;
          for q:=1 to n do if tr[q]=pd2 then begin
          c1:=c1+ans[q];break;
        end;
        ans[p]:=c1;//这个理解下吧
      end;
    end
      else begin//如果t=0（没有加号）
      pd1:=copy(st,j+1,length(st)-j-1);就将等号右边的复制下来
        if ord(pd1[1])>64 then begin//若不是数
          for q:=1 to n do if tr[q]=pd1 then begin
          ans[p]:=ans[q];break;
        end;//跟上面基本相同
      end
      else begin val(pd1,c);ans[p]:=c;end;不是数就直接赋值进去
    end;
    delete(pd3,1,length(pd3));pd4:=0;//还原旧状态，不然就WA得很漂亮
  end;
  for s:=1 to n do if r[s]=1 then writeln(tr[s],' ',ans[s]);//如果它被赋值过，就输出它和它最终的值
end.
```

---

## 作者：RedContritio (赞：1)

一次AC，看到题解区的代码都长的令人心烦，因此把自己的发上来。

题目类型很简单，字符串处理 + 模拟 。

首先我们明确，所有的变量都有两个属性：名称 和 值。

因为语句类型只有三种，所以我们可以将它们统一为一种 ： 左操作量 = 右操作量 ;

接着，我们可以将所有数字看成没有名称的临时变量

学PASCAL 的我不太清楚，但是C和CPP都支持指针，而且很方便。

我们需要实现的函数有这么几个：

一、字符串的分析：先解析出 左操作量 和 右操作量 ， 然后对 右操作量 进行解析。

二、已知名称的变量查找：字符串匹配

三、创建新变量

四、变量列表排序。

具体实现见代码及注释：（CPP）（改掉头函数就是C）






    
         
        



```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define VAR_NAME_MAX_LEN 32
typedef struct tagVAR
{
    char name[VAR_NAME_MAX_LEN];
    int value;
} VAR; // 变量结构体
void Analyse(char* statement); // 分析已知语句
VAR *Find(char* name); // 返回已知名称的变量指针，如果name是数字，返回一个临时变量
VAR *CreateNewVar(char* name);// 创建新变量
VAR *list , *temp; // 变量列表 及 临时变量列表
int used , tud ; // 变量数量 及 临时变量数量
int cmp(const void* a,const void* b); // 排序辅助函数
int main()
{
    int N;
    scanf("%d",&N);
    list = (VAR*)calloc( 3*N , sizeof(VAR) ); // 分配空间
    temp = (VAR*)calloc( 2*N , sizeof(VAR) ); // 分配空间
    char Reader[255] = "";
    for(int i=0; i<N; i++)
    {
        scanf("%s",Reader); 
        Reader[strlen(Reader)-1]=0; // 清除掉语句末尾的分号
        Analyse(Reader); // 开始分析语句
    }
    qsort(list,used,sizeof(VAR),cmp); // 快排
    for(int i=0;i<used;i++)
    {
        printf("%s %d\n",list[i].name,list[i].value); // 输出
    }
}
void Analyse(char* statement)
{
    char* tep = strstr(statement,"=");
    char lts[255] = "";
    memcpy(lts,statement,tep-statement); // 至此 ， lts 为 左操作量 的名称
    VAR* ltp = Find(lts); // ltp 为 左操作量的指针
    char* etp = strstr(statement,"+"); // etp 为+号的位置
    if(etp)
    {
        tep++;
        char rt1s[255] = "";
        memcpy(rt1s,tep,etp-tep); // 至此，rt1s为第一个右操作量的名称
        VAR* rt1p = Find(rt1s); //rt1p为第一个右操作量的指针
        VAR* rt2p = Find(etp+1); // rt2p 为第二个右操作量的指针
        ltp->value = rt1p->value + rt2p->value ; // 赋值
        return ;
    }
    else // 如果没有加号（右操作量为单个变量/数字）
    {
        VAR* rtp = Find(tep+1); // 返回右操作量的指针
        ltp->value = rtp->value ; // 赋值
        return ;
    }
}
VAR* Find(char* name)
{
    if(name[0] > 0x2F && name[0] < 0x3A ) // 如果是数字
    {
        temp[tud].value = atoi(name); // 创建临时变量
        return &temp[tud++]; // 返回之
    }
    for(int i=0; i<used; i++)
    {
        if(strcmp(name,list[i].name)==0)return &list[i]; // 如果变量已创建，返回其地址
    }
    return CreateNewVar(name); // 创建新变量并返回地址
}
VAR* CreateNewVar(char* name) // 创建新变量
{
    strcpy( list[used].name , name );
    list[used].value = 0;
    used++;
    return &list[used-1];
}
int cmp(const void* a,const void* b) // 比较函数
{
    return strcmp((char*)a,(char*)b);
}
```

---

## 作者：happybob (赞：0)

这个题目处理不难，但是这个读入真是坑爹啊！

说说我的经历：

代码没问题，scanf提交，MLE。下载数据，什么玩意1.20s，1ms都不用就出结果了，这……

cin提交，WA3个点，\n出的乱子

cin.get以及getchar提交，MLE……

终于，AC喽：

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std;

map <string, int> mp;

char ch;

int value = 0;

string x = "", f = "";

int main()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        x = "";
        value = 0;
        f = "";
        while(cin >> ch && ch != '=')
        {
            x += ch;
        }
        while(cin >> ch)//这里坑人啊！！！
        {
            if(ch != '+' && ch != ';')
            {
                f += ch;
            }
            else
            {
            	//string转int，stoi函数可以，但是嘛……调用函数费时间哦
                if(f[0] >= '0' && f[0] <= '9')
                {
                    int q = 0, len = f.length() - 1;
                    for(int i = 0; i <= len; i++)
                    {
                        q = (q << 1) + (q << 3) + (f[i] ^ 48);
                    }
                    value += q;
                }
                else
                {
                    value += mp[f];
                }
                f = "";
            }
            if(ch == ';')//这里不加会获得开心的25分哦
            {   
                break;
            }
        }
        mp[x] = value;
    }
    for(map <string, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    {
        if(it -> second != 0)
        {
            cout << it -> first << " " << it -> second << endl;
        }
    }
    return 0;
}
```

那说下思路：

先用while读前面的，一直读到=就停止（那什么黑名单字符集貌似有问题），然后继续while读值，如果说不是+或者不是末尾的;就加起来，如果是就判断是变量还是数字！是数字string转int，不然就加这个变量的值

map大法好！

9ms

求过和赞


---

## 作者：3water (赞：0)

# STL是个好东西

map也是个好东西

string也是个好东西

下面介绍三种string自带的函数——
```cpp
s.size();//取s的长度
s.find(a);//在s中寻找子串（字符）
s.substr(first,length);//从first（下标）开始取长度为length的子串
```
然后32行代码献上
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,len,num;
int toint(string x){//字符串转整型,处理了负数的情况(虽然也不知道有没有负数)
    int i,sym,ans=0;
    x[0]=='-'?i=1,sym=-1:i=0,sym=1;
    for(;i<x.size();i++)ans=ans*10+x[i]-'0';
    return ans*sym;
}
map<string,int>str;//保存变量的数值
map<string,bool>co;//该串是否是变量库中的字符串
map<int,string>st;//保存变量库
string s,rs,ls;//ls为等号左边的变量，rs为等号右边的赋值语句
int ask(string a){//处理赋值语句
	int low=a.find('+'),lena=a.size();//处理加号，保存长度
	if(low<0){//没有加号
		if((a[0]=='-'&&a[1]>='0'&&a[1]<='9')||(a[0]>='0'&&a[0]<='9'))return toint(a);//若为数字则转换
		return str[a];//否则为该变量的值
	}
	string s1=a.substr(0,low),s2=a.substr(low+1,lena-low-1);//处理加号左右的串
	return ask(s1)+ask(s2);//进行处理
}
int main(){
	cin>>n;//输入
	while(n--){
		cin>>s;
		t=s.find('='),len=s.size()-t-2,rs=s.substr(t+1,len),ls=s.substr(0,t);//处理等号两边的字符串，注意右边的';'
		if(!co[ls])co[ls]=1,st[++num]=ls;//把新的变量放在变量库内
		str[ls]=ask(rs);//赋值
	}
	for(int i=1;i<=num;i++)cout<<st[i]<<' '<<str[st[i]]<<endl;//输出变量库中的变量及变量的值
}
```
完结撒花~~~

---

## 作者：远航之曲 (赞：0)

竟然没有c++题解，果断来一发

代码写得又臭又长。。。但是思路非常好理解

（做码农题的好处就是A的时候非常爽，整个人都舒畅了）

详细见注释















```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;
int n,len,lenvar=0;
char s[100];
struct node   //每个变量,有名字和value 
{
    string name;
    int v;
}var[100];
int pos(char s[],char ch)    //确定字符位置 
{
    for (int i=0;i<=strlen(s);i++)
        if (s[i]==ch) return i;
}
int judge(char s[])         //确定是哪种操作 
{
    for (int i=0;i<=len;i++)
        if (s[i]=='+') return 3;    //第三种 "A+B表达式赋值，只有“+”且只有两个数或者变量，A和B都介于1至10^6之间"
    for (int i=pos(s,'=')+1;i<=len;i++) 
        if (s[i]<='z' && s[i]>='a')
            return 2;            //第二种"变量之间赋值：若原变量未被赋值则认为其初始值为0" 
    return 1;  //第一种"将常量赋给变量，保证这个常量的位数不大于9" 
}
int invar(string s)    //判断当前变量名是否在var里 
{
    for (int i=0;i<=lenvar;i++)
        if (var[i].name==s) return i;
    return -1;    
}
void process1(char s[])  //第一种操作 "将常量赋给变量，保证这个常量的位数不大于9"
{
    string s1,s2,s3;
    char ch1[10]={0},ch2[10]={0};
    int value=0;
    int l=0;
    for (int i=0;i<=pos(s,'=')-1;i++)
    {
        ch1[l]=s[i];
        l++;
    }
    s1=ch1;   //找出变量 
    l=0;
    for (int i=pos(s,'=')+1;i<=len;i++)
    {
        ch2[l]=s[i];
        l++;
    }
    s2=ch2;
    value=atoi(ch2);  //找出常量 
                                                //printf("%s %d\n",ch2,value);
                                                //cout<<ch2;
    int whvar=invar(s1);
    if (whvar==-1)   //不在var内创建新的 
    {
        lenvar++;
        var[lenvar].name=s1;
        var[lenvar].v=value;
    }
    else
    {
        var[whvar].v=value;//直接赋值 
    }
}
void process2(char s[])//第二种操作 "变量之间赋值：若原变量未被赋值则认为其初始值为0"
{
    string s1,s2,s3;
    char ch1[10]={0},ch2[10]={0};
    int value=0;
    int l=0;
    for (int i=0;i<=pos(s,'=')-1;i++)
    {
        ch1[l]=s[i];
        l++;
    }
    s1=ch1;              //找出第一个变量名 
    l=0;
    for (int i=pos(s,'=')+1;i<=len;i++)
    {
        ch2[l]=s[i];
        l++;
    }
    s2=ch2;             //找出第二个变量名 
    int whvars1=invar(s1);
    int whvars2=invar(s2);//是否在var里 
    if (whvars1==-1)//创建s1 
    {
        lenvar++;
        var[lenvar].name=s1;
        var[lenvar].v=0;
        whvars1=lenvar;
    }
    if (whvars2==-1)//创建s2 
    {
        lenvar++;
        var[lenvar].name=s2;
        var[lenvar].v=0;
        whvars2=lenvar;
    }
    var[whvars1].v=var[whvars2].v;//赋值 
}
void process3(char s[])//第三种操作 "A+B表达式赋值，只有“+”且只有两个数或者变量，A和B都介于1至10^6之间" 
{
    string s1,s2,s3;
    char ch1[10]={0},ch2[10]={0},ch3[10]={0};
    int value=0;
    int pos1=pos(s,'=');
    int pos2=pos(s,'+');//找到+,= 
    int l=0;
    for (int i=0;i<=pos1-1;i++)
    {
        ch1[l]=s[i];
        l++;
    }
    s1=ch1;//找到第一个 
    l=0;
    for (int i=pos1+1;i<=pos2-1;i++)
    {
        ch2[l]=s[i];
        l++;
    }
    s2=ch2;//第二个 
    l=0;
    for (int i=pos2+1;i<=len;i++)
    {
        ch3[l]=s[i];
        l++;
    }
    s3=ch3;//第三个 
    int whvar=invar(s1);//s1必定为变量名 
    if (whvar==-1)//创建 
    {
        lenvar++;
        var[lenvar].name=s1;
        var[lenvar].v=value;
    }
    if (ch2[0]>='0' && ch2[0]<='9' && ch3[0]>='0' && ch3[0]<='9') //全是数字如 A=1+1 
    {
        int whvars1=invar(s1);
        int v1=atoi(ch2);
        int v2=atoi(ch3);//转换 
        var[whvars1].v=v1+v2;//赋值 
    }
    else
    if (ch2[0]>='0' && ch2[0]<='9') //如A=B+1 
    {
        int v1=atoi(ch2);
        int whvars1=invar(s1);
        int whvars2=invar(s3);
        if (whvars2==-1)
        {
            lenvar++;
            var[lenvar].name=s3;
            var[lenvar].v=0;
            whvars2=lenvar;
        }
        var[whvars1].v=var[whvars2].v+v1;
    }
    else
    if (ch3[0]>='0' && ch3[0]<='9') //如A=1+B 
    {
        int v1=atoi(ch3);
        int whvars1=invar(s1);
        int whvars2=invar(s2);
        if (whvars2==-1)
        {
            lenvar++;
            var[lenvar].name=s2;
            var[lenvar].v=0;
            whvars2=lenvar;
        }
        var[whvars1].v=var[whvars2].v+v1;
    }
    else    //全是变量如 A=B+C 
    {
        int whvars1=invar(s1);
        int whvars2=invar(s2);
        int whvars3=invar(s3);
        if (whvars1==-1)
        {
            lenvar++;
            var[lenvar].name=s1;
            var[lenvar].v=0;
            whvars1=lenvar;
        }
        if (whvars2==-1)
        {
            lenvar++;
            var[lenvar].name=s2;
            var[lenvar].v=0;
            whvars2=lenvar;
        }
        if (whvars3==-1)
        {
            lenvar++;
            var[lenvar].name=s3;
            var[lenvar].v=0;
            whvars3=lenvar;
        }
        var[whvars1].v=var[whvars2].v+var[whvars3].v;
    }
}
void process(int type,char s[])//分操作 
{
    if (type==1) process1(s);
    if (type==2) process2(s);
    if (type==3) process3(s);
}
void out()//输出 
{
    for (int i=1;i<=lenvar;i++)
    {
        printf("%s %d\n",var[i].name.c_str(),var[i].v);
    }
}
bool comp(node a,node b)//为了sort 
{
    return a.name<b.name;
}
//void sortvar(node &a)
//{
//    sort(a+1,a+lenvar+1,comp);
//}
main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%s",&s);
        len=strlen(s)-2;
        process(judge(s),s);
    }
    sort(var+1,var+lenvar+1,comp);//字典序 
    out();
}
```

---

## 作者：Ufowoqqqo (赞：0)

本题是一道解法上并不困难，但**[color=red]操作相对复杂[/color]**的题目。主要思路如下：

\* 每次先在变量表中查询是否有相应的变量存在：如果有，将值赋给该变量；否则新建一个变量。

\* 在进行赋值操作时，如果是常量赋值就可以直接将其转为数字进行赋值；如果是某变量，就在变量表中取它的值出来再赋值；如果是加法，就分别取出值并相加，将和赋给目标变量。

\* 赋值操作模拟完毕后对变量表进行排序（由于出题者Huntfire的原因，本题的n非常小，用**[color=red]O(n^2)[/color]**的选择排序足矣）。

在储存方面：

\* 可以用一个一维数组存放，基类型是自定义的“变量”型，变量型里有两个值：该变量的值及该变量的标识符；

\* 可以用两个一维数组，一个存放变量值，另一个存放变量标识符。

另外，赋值语句末尾的分号可以直接忽略，输入完就删除。

对了，请注意Hint的第2点：**[color=red]变量标识符不止一位[/color]**！如果用char作为作为变量标识符的类型，肯定就233了。

```delphi

Type
  Variable=Record//变量
    Value:Longint;//变量值
    Name:String;//变量标识符
  End;

Var
  VarList:Array [1..1000] Of Variable;//变量表
  n,i,p,VarCount:Longint;
  s,t:String;

Function Find(Target:String):Longint;//在变量表中查询标识符为Target的变量的位置，若不存在则返回0
Var i:Longint;
Begin
  Find:=0;
  For i:=1 To VarCount Do
    If VarList[i].Name=Target Then Exit(i);
End;

Function GetValue(VarName:String):Longint;//在变量表中查询标识符为VarName的变量的值
Var i:Longint;
Begin
  For i:=1 To VarCount Do
    If VarList[i].Name=VarName Then Exit(VarList[i].Value);
End;

Procedure Give(VarNum:Longint;s:String);//给变量表中位置为VarNum的变量赋值，s为式子
Var t,Code,Sum:Longint;
Begin
  If Pos('+',s)=0 Then//题目所述的第一、二种赋值
    Begin
      Val(s,t,Code);
      If Code=0 Then VarList[VarNum].Value:=t Else VarList[VarNum].Value:=GetValue(s);
    End
  Else//题目所述的第三种赋值
    Begin
      Sum:=0;
      Val(Copy(s,1,Pos('+',s)-1),t,Code);
      If Code=0 Then Sum:=t Else Sum:=GetValue(Copy(s,1,Pos('+',s)-1));
      Val(Copy(s,Pos('+',s)+1,Length(s)),t,Code);
      If Code=0 Then Inc(Sum,t) Else Inc(Sum,GetValue(Copy(s,Pos('+',s)+1,Length(s))));
      VarList[VarNum].Value:=Sum;
    End;
End;

Procedure NewVar(VarName:String);//增加新变量
Begin
  Inc(VarCount);
  VarList[VarCount].Name:=VarName;
End;

Begin
  Readln(n);
  For i:=1 To n Do
  Begin
    Readln(s);
    Delete(s,Length(s),1);
    t:=Copy(s,1,Pos('=',s)-1);
    p:=Find(t);
    If p>0 Then Give(p,Copy(s,Pos('=',s)+1,Length(s))) Else
      Begin
        NewVar(t);
        Give(VarCount,Copy(s,Pos('=',s)+1,Length(s)));
      End;
  End;
  For i:=1 to VarCount-1 Do
    For j:=1 to VarCount Do
      If VarList[i].Name>VarList[j].Name Then
        Begin
          s:=VarList[i].Name;
          VarList[i].Name:=VarList[j].Name;
          VarList[j].Name:=s;
          p:=VarList[i].Value;
          VarList[i].Value:=VarList[j].Value;
          VarList[j].Value:=p;
        End;
  For i:=1 To VarCount Do
   Writeln(VarList[i].Name,' ',VarList[i].Value);
End.

```

---

