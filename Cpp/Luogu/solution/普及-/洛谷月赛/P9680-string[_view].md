# string[_view]

## 题目背景

C++ 的 string 类是一个功能强大的字符串类，然而由于其字符串算法和内存管理绑定的机制，所以在处理 C 风格字符串时效率低下。

为了解决这个问题，C++17 标准引入了 string\_view 类型，将内存管理和字符串算法分离，从而更好地适配了 C 风格字符串的处理。

## 题目描述

你需要模拟一个简单的 C++ 程序，该程序的每一行必然为如下两种形式之一：

- `string <variable-name>(<initializer>);`
- `string_view <variable-name>(<initializer>);`

其中 `variable-name` 为声明的变量名（保证之前未出现过，且长度不超过 $10$），`initializer` 为初始化该变量的内容，可以是：

- 字符串字面量，即用双引号引起的字符串（形如 `"abc"`）；
- 之前出现过的变量名 `source`，此时应将 `source` 对应的字符串赋给 `variable-name`。

具体而言，将任意一个字符串 $s$ 赋给 string 类型会进行 $|s|$ 次字符拷贝，而赋给 string\_view 类型不会拷贝字符。其中 $|s|$ 为字符串 $s$ 的长度。

你需要计算出该程序中字符拷贝的总次数。

## 说明/提示

  对于每组数据，保证代码长度均不超过 $10^4$（不包括换行符）。

保证字符串字面量（除去两侧引号）和变量名中只有拉丁字母，且给定的代码严格满足题目要求。

### 子任务

|  #   |            特殊性质            | 分值 |
| :--: | :----------------------------: | :--: |
|  0   |              样例              | 0  |
|  1   | 所有变量均为 string\_view 类型 | 10 |
|  2   |    只使用字符串字面量初始化    | 20 |
|  3   |               -                | 70 |

---

好消息：GCC 9.3.0 支持 string_view。

坏消息：NOI 不开 C++17。

## 样例 #1

### 输入

```
6
string a("cxyakioi");
string_view b("cxyakapio");
string c(b);
string_view d(a);
string_view cxyakioi(c);
string cxyakapio(d);```

### 输出

```
25```

# 题解

## 作者：a1a2a3a4a5 (赞：13)

# P9680 string[_view] 
## 题意
1. 两个字符类型，一个字符类型花费次数，一个不花费，花费次数是字符串长度。
2. 在“**赋给** `string_view` 类型不会拷贝字符。”中，赋给的意思就是等号右边的字符串类型是 `string_view` 的不会拷贝字符。

## 思路
1. 首先是一堆麻烦的边角料，咱给他按模拟的思路去了。
2. 可以发现如果是普通字符串类型，我们字符串内容没什么用，所以定两个 `map` 一个存字符串长度，一个存字符串是不是 `string_view` 类型，如果赋字符串变量就赋字符串变量的长度。
3. 然后如果要花费直接加长度。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int l,da;
string fw,xiaochou,ming,neirong;
map<string,int> len;
map<string,bool> lihai;
int main()
{
	cin>>l;
	for(int i=1;i<=l;i++)
	{
		cin>>fw>>xiaochou;//俩小丑，咱们用完就把他俩甩了！
		bool f=0,mao=0;ming="";neirong="";
		//mao冒号？ming名字，neirong内容。
		for(int i=0;i<xiaochou.size();i++)
		{
			char x=xiaochou[i];//把小丑的钱给我家哥哥。
			if(x=='('||x==')'||x==';') f=1;//f判断是不是到赋值部分了。
			else if(x=='"') mao=1;//独立自主的。
			else if(f==0) ming=ming+x;//变量名字。
			else neirong=neirong+x;
		}
		if(mao)//有冒号？
		{
			len[ming]=neirong.size();
			lihai[ming]=fw.size()>8?1:0;//你什么血统？
			if(!lihai[ming]) da+=len[ming];//投胎不好直接制裁！
		}
		else//借助前辈的力量。
		{
			len[ming]=len[neirong];//直接啃老。
			lihai[ming]=fw.size()>8?1:0;//记录血统！
			if(!lihai[ming]) da+=len[neirong];//投胎不好继续制裁！
		}
	}
	cout<<da;
	return 0;
}
```

---

## 作者：Light_az (赞：8)

简化题意后，本题是求所有 `string` 操作复制的字符串总长度之合。

这道题目难点显然在于处理输入的字符串，主要是判断该行程序是 `string` 还是 `string_view`，同时处理复制的两个字符串的名字。

首先我们直接输入操作类型，因为操作类型和复制字符串之间存在空格，然后处理 `variable-name` 和 `initializer` 复制字符串，发现字符串之间会有左括号隔开，所以当我们提取到左括号后，可以停止读取，跳过左括号后提取后面的字符串直到遇见右括号时，停止读取，代码如下：

```cpp
void f(){
	ll i;
	for(i=0;i<=len-1;i++){
		if(s[i]=='(') break;//读取了左括号
		s2+=s[i];
	}
	i++;//跳过左括号
	for(;i<=len-1;i++){
		if((s[i]<='z'&&s[i]>='a')||(s[i]<='Z'&&s[i]>='A')) s3+=s[i];//不是字符就可以停止读取
		if(s[i]=='"') k=1;//读入的是新字符串而不是名称
	} 
	return ;
}
```

观察样例发现，`initializer` 有可能不是字符串的名称，而是新的字符串，因此上面代码使用 $k$ 特判该字符串，方便后面的操作，完整代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(ll i=j;i<=n;i++)
#define D double
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10;
ll n,m,k,x,y,u,v,w,cnt,ans,t,l,r,len,T,id;
ll mn=INT_MAX,mx=0,p,opt;
string s1,s2,s3,s;
map<string,string> mp;
void f(){//上面代码已解释
	ll i;
	for(i=0;i<=len-1;i++){
		if(s[i]=='(') break;
		s2+=s[i];
	}
	i++;
	for(;i<=len-1;i++){
		if((s[i]<='z'&&s[i]>='a')||(s[i]<='Z'&&s[i]>='A')) s3+=s[i];
		if(s[i]=='"') k=1;
	} 
	return ;
}
int main(){
	cin>>n;
	F(id,1,n){
  		//mp[s]对于字符串s的内容
		cin>>s1>>s;
		len=s.size(),s2="",s3="",k=0;//清空
		f();
		if(k) mp[s2]=s3;//新字符串，直接读取
		else mp[s2]=mp[s3];//是字符串名字
		if(s1=="string"){//如果是string，需要添加长度
			if(k) ans+=s3.size();//加上字符串长度
			else ans+=mp[s3].size(); //加上对应字符串长度
		} 
	} 
	cout<<ans;
	return 0;
}


```


---

## 作者：zhang_Jimmy (赞：6)

部分思路来自[这里](https://www.luogu.com.cn/paste/n64n1ruf)，万分感谢 @xiaoyang111。

# 思路：

首先可以想到，用 `std::map<string, int>` 存储每一个 `string` 变量对应的字符串的长度。

再对输入的字符串进行拆解，将其分成类似于 `s st(s2)` 这样子，也就是数据类型 $s$，将 $s2$ 这个字符串常量或字符串变量赋值给 $st$。

然后分几种情况判断：

1. 如果 $s2$ 是字符串常量，那么 $mp_{st} = \left\vert s2 \right\vert$，接下来进行判断：
	
	- 如果 $s = \texttt{string}$，那么将 $\left\vert s2 \right\vert - 2$ 累加到答案中（因为 $s$ 的第一位和最后一位都多了一个冒号）。
   
   - 否则，直接忽略这次操作。

1. 如果 $s2$ 是字符串变量：
   
	- 如果 $s = \texttt{string}$，那么将 $mp_{s2}$ 累加到答案中。
   
   - 否则，直接忽略这次操作。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, ans;
string s, s2;
map<string, int> mp; 

int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	cin >> t;
	while(t --){
		cin >> s >> s2; 
		string st;
		while(s2[0] != '('){//提取变量名 
			st += s2[0];
			s2.erase(0, 1);
		}
		//while 循环结束后，其实就已经将左括号及左括号之后的东西放在 s2 里面了
		s2.erase(0, 1);//删除( 
		s2.pop_back();//删除; 
		s2.pop_back();//删除) 
		int len;
		if(s2[0] == '\"')
			len = s2.size() - 2; //为什么要减 2 上面说过 
		else
			len = mp[s2]; //如果是变量名那么直接将字符串变量对应的长度提取出来 
		mp[st] = len; //将新的字符串变量以及长度添加到 map 中 
		if(s == "string")
			ans += len;
	} 
	cout << ans;
	return 0;
}

```


---

## 作者：Pink_Cut_Tree (赞：4)

# P9680 string[_view] 题解

模拟题，很简单。

## 解析

### $10$ 分

看到“所有变量均为 string_view 类型”，直接输出 `0`。

### $100$ 分

使用一个 `map` 统计每一个 `string` 型变量所代表的内容。

模拟题，没啥说的，掌握 `substr` 函数即可。

## 代码

```cpp
#include<iostream>
#include<cstring>
#include<map>
using namespace std;
#define str string //简写string，其实没啥必要 
int n;
map<str,str>ds; //变量名到变量代表什么的映射 
str ans1,ans2,s;
int pl,cnt,cnt2;
bool flag;
long long ans;
int main(){
	cin.tie(0)->sync_with_stdio(0); //读入优化 
	cin>>n;
	getline(cin,s); //把换行符读掉 
	while(n--){
		getline(cin,s); 
		if(s[6]=='_'){ //string_view
			for(int i=12;i<s.size();i++){
				if(s[i]=='('){
					cnt=i; break;
				}
			}
			ans1=s.substr(12,cnt-12); //截取变量名 
			if(s[cnt+1]=='"'){ //字面赋值 
				for(int i=cnt+2;i<s.size();i++){
					if(s[i]=='"'){
						cnt2=i; break;
					}
				}
				ans2=s.substr(cnt+2,cnt2-cnt-2);
			}
			else{ //变量赋值 
				for(int i=cnt+1;i<s.size();i++){
					if(s[i]==')'){
						cnt2=i; break;
					}
				}
				ans2=s.substr(cnt+1,cnt2-cnt-1);
				ans2=ds[ans2];
			}
			ds[ans1]=ans2;
		}
		else{ //string
			for(int i=7;i<s.size();i++){
				if(s[i]=='('){
					cnt=i; break;
				}
			}
			ans1=s.substr(7,cnt-7); //截取变量名 
			if(s[cnt+1]=='"'){ //字面赋值 
				for(int i=cnt+2;i<s.size();i++){
					if(s[i]=='"'){
						cnt2=i; break;
					}
				}
				ans2=s.substr(cnt+2,cnt2-cnt-2);
			}
			else{ //代码赋值 
				for(int i=cnt+1;i<s.size();i++){
					if(s[i]==')'){
						cnt2=i; break;
					}
				}
				ans2=s.substr(cnt+1,cnt2-cnt-1);
				ans2=ds[ans2];
			}
			ds[ans1]=ans2;
			ans+=ans2.size(); //加上拷贝次数 
		}
	}
	cout<<ans;
return 0;
}
```


---

## 作者：Bc2_ChickenDreamer (赞：3)

# P9680 string[\_view] 题解

## Sol

模拟题。

我们先定义一个结构体，来存储定义的字符串的名字，内容和长度。每一次输入分两个字符串，一个是类型，一个是名字和赋值内容。当遇到 `string` 时，如果是用字面量赋值，那么就计算引号里字符串的长度 $l$。然后把答案加上 $l$，并把名字，内容，长度存储起来。如果是出现过的变量名赋值，那么在已经存储的字符串里查找，如果查找到了，那么把查找到的字符串的内容和长度赋值给新字符串并存储名字。再把答案加上长度。遇到 `string_view` 类型时只需去掉"把答案加上长度"这一步即可。

## code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

using ll = long long;

const int kMaxN = 1e4 + 10, kInf = (((1 << 30) - 1) << 1) + 1;

int l, ans = 0;
string a, b, tmp;

struct node { // 结构体
  string name, t; // 名字和内容
  int len; // 长度
} s[kMaxN];

int main() {
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);
  cin >> l; // 输入 l
  for (int i = 1; i <= l; ++ i) {
    cin >> a >> b; // a 时类型，b 是名字和赋值内容
    if (a == "string") { // 如果是 string 类型
      if (b.find("\"") != b.npos) { // 如果是字面量
        int fst = b.find("\""); // 查找第一个 "
        char tmp = b[fst];
        b[fst] = '!';
        int scd = b.find("\""); // 查找第二个 "
        b[fst] = tmp;
        s[i].name = b.substr(0, fst - 1);
        // 存储名字（第一个 " 之前的字符串）
        s[i].t = b.substr(fst + 1, scd - fst - 1);
        // 存储内容（第一个 " 和第二个 " 之间的字符串）
        s[i].len = s[i].t.size();
        // 存储长度
        ans += s[i].len;
        // 答案加上长度
      } else {
        int fst = b.find("("); // 查找 (
        char tmp1 = b[fst];
        b[fst] = '!';
        int scd = b.find(")"); // 查找 )
        b[fst] = tmp1;
        tmp = b.substr(fst + 1, scd - fst - 1); // 已经存储的字符串的名字
        for (int j = 1; j < i; ++ j) { // 查找
          if (s[j].name == tmp) { // 如果是配对的
            s[i].name = b.substr(0, fst); // 存储名字（"(" 之前的字符串）
            s[i].t = s[j].t;
            // 把内容赋给新字符串
            s[i].len = s[j].len;
            // 把长度赋给新字符串
            break;
          }
        }
        ans += s[i].len;
      }
    } else {
       /*只少了"把答案加上长度"这一步，不做注释*/
      if (b.find("\"") != b.npos) {
        int fst = b.find("\"");
        char tmp = b[fst];
        b[fst] = '!';
        int scd = b.find("\"");
        b[fst] = tmp;
        s[i].name = b.substr(0, fst - 1);
        s[i].t = b.substr(fst + 1, scd - fst - 1);
        s[i].len = s[i].t.size();
      } else {
        int fst = b.find("(");
        char tmp1 = b[fst];
        b[fst] = '!';
        int scd = b.find(")");
        b[fst] = tmp1;
        tmp = b.substr(fst + 1, scd - fst - 1);
        for (int j = 1; j < i; ++ j) {
          if (s[j].name == tmp) {
            s[i].name = b.substr(0, fst);
            s[i].t = s[j].t;
            s[i].len = s[j].len;
            break;
          }
        }
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
```


---

## 作者：Lemon_zqp (赞：3)

### 思路
这道题目就是模拟，首先输入字符串，然后开两个数组，一个存变量名，一个存数据，然后每次输入把内容取下来存到数组里即可，如果第一个字符串是 string 的话就要把长度加到答案里，否则忽略这一步就可以了。
### 代码+注释
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

string b[100005], ne[100005];//b数组用来存变量，ne数组用来存内容 

signed main()
{
	int n, ans = 0, ni = 1;//n表示多组数据，ans表示答案，ni表示当前存了几个变量 
	cin >> n;
	for(int i = 1; i <= n; i++){
		string s, ss;//输入两个字符串 
		cin >> s >> ss;
		if(s == "string"){//如果是string要把长度加到ans里 
			int i = 0;
			string kao = "";//把变量名取下来 
			while(ss[i] != '('){
				kao += ss[i];
				i++;
			}
			i++;
			string nei = "", bian = "";
			if(ss[i] == '"'){//如果括号里是字符串，直接赋值
				i++;
				while(ss[i] != '"'){
					nei += ss[i];
					ans++;//增加ans 
					i++;
				}
				b[ni] = kao;//存到数组里 
				ne[ni] = nei;
				ni++;//个数加一 
			}
			else{
				while(ss[i] != ')'){//如果是变量，在b数组里找到对应的值，再赋值 
					bian += ss[i];
					i++;
				}
				for(int i = 1; i <= ni; i++){
					if(b[i] == bian){
						ans += ne[i].size();//增加ans 
						b[ni] = kao;
						ne[ni] = ne[i];
						break;
					}
				}
				ni++;
			}
		}
		else{//下面一样，只不过不把长度加到ans里 
			int i = 0;
			string kao = "";
			while(ss[i] != '('){
				kao += ss[i];
				i++;
			}
			i++;
			string nei = "", bian = "";
			if(ss[i] == '"'){
				i++;
				while(ss[i] != '"'){
					nei += ss[i];
					i++;
				}
				b[ni] = kao;
				ne[ni] = nei;
				ni++;
			}
			else{
				while(ss[i] != ')'){
					bian += ss[i];
					i++;
				}
				for(int i = 1; i <= ni; i++){
					if(b[i] == bian){
						b[ni] = kao;
						ne[ni] = ne[i];
						break;
					}
				}
				ni++;
			}
		}
	}
	cout << ans;
	return 0;
}

```


---

## 作者：HFanGDoDM (赞：1)

## 前置知识

[C++ string 用法](https://oi.wiki/lang/csl/string/)、[C++ STL map 用法](https://oi.wiki/lang/csl/associative-container/#map)

# 题意简述

给定一段 C++ 程序的代码，每一行可能是 `string <variable-name>(<initializer>);` 或 `string_view <variable-name>(<initializer>);`。

`variable-name` 是声明的变量名，`initializer` 是初始化该变量的内容。其中 `initializer` 可以是：

- 用双引号引起的字符串，表示将该字符串内容赋给 `variable-name`。

- 之前出现过的变量名，表示将该变量名对应的字符串赋给 `variable-name`。

已知将字符串 $s$ 赋值给 `string` 类型会 **进行 $|s|$ 次字符拷贝**，赋值给 `string-view` 类型 **不会进行字符拷贝**。求该程序中字符拷贝的总次数。

### 数据范围

每个变量名长度 $1\leqslant l\leqslant 10$，代码长度 $1\leqslant len\leqslant 10^4$。字符串字面量（不含引号）和变量名中只含拉丁字母，且给定代码严格符合题目要求。保证每一行声明的变量名在之前未出现过。

# 解题思路

## 子任务 0

### 做法

答案为 $25$。

### 正确性证明

答案在 **样例输出 #1** 中给出，为 $25$。

### 具体实现

输出 $25$。

### 时间复杂度分析

执行一次输出语句，复杂度为 $O(1)$，可以通过 **子任务 0**。

### 参考核心代码

```cpp
printf("25");
```

### 期望得分

$0$ 分。

## 子任务 1

### 做法

答案为 $0$。

### 正确性证明

将字符串赋给 `string_view` 类型 **不会拷贝字符** $\implies$ 拷贝字符的 **次数为 $0$**。

所有变量均为 `string_view` 类型 $\implies$ **所有赋值操作** 的字符拷贝次数都为 $0$ $\implies$ 该程序字符拷贝 **总次数** 为 $0$。

### 具体实现

输出 $0$。

### 时间复杂度分析

$O(1)$，可以通过 **子任务 1**。

### 参考核心代码

```cpp
printf("0");
```

### 期望得分

$10$ 分。结合 **子任务 0** 的解法可以得到 $10$ 分。

## 子任务 2

### 做法

对于每一行代码，我们找到这一行代码中出现的 **用双引号引起的字符串**。

若这一行代码中，变量的类型是 `string` 类型，则答案增加量为这一字符串（**不含双引号**）的长度；否则，答案不变。

处理完所有代码后，答案即为该程序中字符拷贝的总次数。

### 正确性证明

只使用字符串字面量初始化 $\implies$ 对于每一行代码，总能找到其初始化的字符串字面量。

将字符串 $s$ 赋值给 `string` 类型会 **进行 $|s|$ 次字符拷贝** $\implies$ 若变量类型为 `string`，则 **字符拷贝总次数增加 $|s|$**。

因此做法正确。

### 具体实现

这里本人使用了 `string` 读入字符串。每行代码，首先读入字符串类型，然后读入初始化语句（**`string` 读入时遇到空格会停止读入**）。

设读入的表示字符串类型的字符串为 `type`，则使用 **`type=="string"
`** 语句判断本句程序初始化的变量是否为 `string` 类型。

若不是 `string` 类型，跳过本句程序。否则：

在初始化语句中，**使用 `find` 函数**，找到 `(` 和 `)` 两个字符的位置。由于双引号在括号内部紧挨括号，所以应当 **对左括号位置加 $2$，对右括号位置减 $2$**，以定位到初始化的字符串的始末位置 $l$ 和 $r$。此时对答案增加 $r-l+1$。

最后输出答案。

### 时间复杂度分析

设每行代码对应的字符串为 $str$。

读入所有代码，复杂度为 $O(len)$。每行代码调用 `find` 函数，对于上述实现，复杂度是 $O(|str|)$ 的。

总时间复杂度 $O(len)$，可以通过 **子任务 2**。

### 参考核心代码

```cpp
    string type;
    cin>>type>>str[i];
    if(type=="string"){//若类型为string，答案增加字符串长度
        int lef=str[i].find("(")+2,rig=str[i].find(")")-2;
        ans+=rig-lef+1;
    }
...
printf("%d",ans);
```

### 期望得分

$20$ 分。结合 **子任务 0** 的解法可以得到 $20$ 分，结合 **子任务 1** 的解法可以得到 $30$ 分，结合 **子任务 0** 和 **子任务 1** 的解法可以得到 $30$ 分。

## 子任务 3

### 做法

对于每一行代码，我们首先找到本行代码初始化的变量名。

然后，判断括号内的内容。若括号内使用字符串字面量初始化，则记录变量名与该 **字符串长度** 的 **对应关系**。若使用之前出现过的变量名初始化，则找到 **括号内变量名** 对应的字符串长度。

接着，判断本行代码的初始化变量类型。若变量类型为 `string`，则答案增加上述求出的字符串长度；否则，答案不变。

处理完所有代码后，答案即为该程序中字符拷贝的总次数。

### 正确性证明

初始化变量名不重复 $\implies$ 每个变量名对应 **唯一一个字符串长度**。

括号内的变量名出现过 $\implies$ 可以找到其对应的字符串长度。

字符拷贝总次数只与初始化变量类型与字符串长度有关，**与字符串本身内容无关** $\implies$ 可以只记录字符串长度，无需记录字符串内容。

答案增加量有关内容已经在 **子任务 2** 中证明。

因此，**该做法正确**。

### 具体实现

首先读入变量类型与初始化语句（不一次性读入的原因见 **子任务 2**）。使用 `find` 函数，找到初始化语句中的 `(` 位置，并 **使用 `substr` 函数** 截取初始化语句中首位置到 `(` 的前一位置的子串。该子串即为初始化的变量名。

找到初始化语句中 `(` 的后一位置与 `)` 的前一位置。判断其中一个位置对应的字符 **是否为大小写字母**。**若不是**，则一定为引号，即使用字符串字面量进行初始化。设这两个位置分别为 $l$ 和 $r$，由于不能包含引号，故该字符串长度为 $r-l-1$。**若是**，则使用变量初始化，使用 `substr` 函数截取两个位置（含）之间的子串。该字符串的长度等于该 **之前出现过的变量** 对应的字符串长度。

使用 `map<string,int>` 存储变量名与字符串长度的 **对应关系**。

判断初始化变量类型的具体实现见 **子任务 2**。根据类型，决定答案的增加量。

最后输出答案。

### 时间复杂度分析

读入代码，复杂度 $O(len)$。每次使用 `find` 函数，由 **子任务 2** 的分析，总复杂度是 $O(len)$ 的。单次调用 `substr` 函数，复杂度为 $O(|str|)$。每次需要使用 `map` 记录对应关系，共有 $L$ 个变量，故单次复杂度为 $O(\log L)$。

总时间复杂度 $O(len+L\log L)$。根据题意，可估算出 $L$ 不超过 $1000$，因此可通过 **本题**。

### 参考核心代码

```cpp
map<string,int>len;
...
    string type;
    cin>>type>>str[i];
    string name=str[i].substr(0,str[i].find("("));//提取变量名
    int lef=str[i].find("(")+1,rig=str[i].find(")")-1;
    if(str[i][lef]<'A'||str[i][lef]>'z'){//字符串字面量
        len[name]=rig-lef-1;//记录新变量名与字符串长度的对应关系
        if(type=="string")
            ans+=len[name];
    }
    else{//使用变量名赋值
        string name1=str[i].substr(lef,rig-lef+1);//提取用于赋值的变量名
        if(type=="string")
            ans+=len[name1];
        len[name]=len[name1];//两个变量字符串长度相等
    }
...
printf("%d",ans);
```

### 期望得分

$100$ 分。

---

## 作者：流光萤影 (赞：1)

## 前言：

**本题解使用语言：C++14 (GCC 9)，开不开 O2 随意**

## 正文：

**思路：使用 ```string``` 和 ```map``` 进行模拟。**

**实现**：对 ```string``` 的一些用法进行一个简略的介绍：

- $\texttt{substr}(pos,length)$ 截取从下标 $pos$ 起长度为 $length$ 的子串。

- $\texttt{find}(val)$ 返回字符串中第一个 $val$ 的下标。

示例：

```cpp
name = s.substr(0,s.find('(')); //将 name 赋值为从 0 起长度为 s.find('(') 的字符串。
```

------------

**AC 代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;int n,ans;string s,name,val;
map<string,string> mp;
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin >> n;
	for(;n;--n)
	{
		cin >> s;
		if(s == "string")
		{
			cin >> s;
			name = s.substr(0,s.find('('));
			if(s[s.find('(')+1] == '"') val = s.substr(s.find('(')+2,s.find(')')-1-name.size()-2);
			else val = mp[s.substr(s.find('(')+1,s.find(')')-name.size()-1)];
			mp[name] = val,ans += val.size();
		}
		else
		{
			cin >> s;
			name = s.substr(0,s.find('('));
			if(s[s.find('(')+1] == '"') val = s.substr(s.find('(')+2,s.find(')')-1-name.size()-2);
			else val = mp[s.substr(s.find('(')+1,s.find(')')-name.size()-1)];
			mp[name] = val;
		}
	}
	cout << ans;
}
```

---

## 作者：LEle0309 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9680)

作为 div2 的 T1，本蒟蒻竟然能一遍过（还是道中模拟）

[码量标准的 1KB](https://www.luogu.com.cn/record/126851776)，59 行。

按照题意模拟即可，用一个 `map` 来存储每一个变量所对应的一个值。

古今多少事，尽在代码中。

```cpp
#include<iostream>
#include<map>
using namespace std;
string type,op,name,val;int t,ans;
/*
type：判断是 string 还是 string_view
op：类型之后的字符串
name：从op中分离出来的变量名
val：变量所要赋的值
*/
map<string,string>code;//存储每一个变量的值
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>type>>op;
		name=val="";//清空
		if(type=="string")//string类型
		{
			int i=0;
			for(;i<op.size();i++)
				if(op[i]!='(')name+=op[i];//分离变量名
				else break;//碰到左括号，代表不是变量名了
			++i;//跳过左括号
			if(op[i]=='\"')//用字符串字面量赋值
				for(++i;i<op.size();i++)
					if(op[i]!='\"')val+=op[i];//分离值
					else break;//碰到引号，不是值了
			else//用定义过的字符串赋值
			{
				string name_="";//代表给name赋值的字符串的变量名，注意赋初始值
				for(;i<op.size();i++)
					if(op[i]!=')')name_+=op[i];//分离name_
					else break;//碰到引号，不是变量名了
				val=code[name_];//取出map中name_的值
			}
			code[name]=val;//把这个变量和值存进map中
			ans+=val.size();//更改答案
		}
		else
		{
			int i=0;
			for(;i<op.size();i++)
				if(op[i]!='(')name+=op[i];
				else break;
			++i;
			if(op[i]=='\"')
				for(++i;i<op.size();i++)
					if(op[i]!='\"')val+=op[i];
					else break;
			else
			{
				string name_="";
				for(;i<op.size();i++)
					if(op[i]!=')')name_+=op[i];
					else break;
				val=code[name_];
			}
			code[name]=val;
			//和上面21~39行一模一样，只是不需要更改ans 
		}	
	}
	cout<<ans;//输出 
	return 0;//完结撒花！
}
```

---

## 作者：jqQt0220 (赞：0)

$\LARGE\text{STL 大法好！}$

这题就是简单的字符串处理 & STL map。直接先用 `cin` 读入一串字符串，这个就是定义变量的类型。`string` 和 `string_view` 的区别就在于前者会进行字符长度次字符拷贝，而后者不会，~~所以直接输出 `0` 就能骗到 Subtask #1 的 10 分~~。处理也不是很复杂，只要先遍历到左括号，这之前就是定义变量的名称；之后遍历括号内的东西，如果两边有引号就把引号内的东西直接在 map 映射给变量名，否则就把变量映射给变量名。赋进去的时候如果是 `string` 就把答案加上字符串长度，否则就不用管。直接看代码罢：
```cpp
#include<bits/stdc++.h>
using namespace std;
int q,as=0;
map<string,string> m;//建立一个 map 映射库，用键值对储存信息
int main()
{
    scanf("%d",&q);
    while(q--)
    {
        string t,v;
        cin>>t>>v;
        if(t=="string")
        {
            int l=v.length(),i;
            string s="",r="";
            for(i=0;v[i]!='(';i++)//找出变量名
                s+=v[i];
            i++;//左括号跳过
            if(v[i]=='"')
            {
                for(i++/*前引号跳过*/;v[i]!='"';i++)//找出给出字符串常量
                    r+=v[i];
                m[s]=r;//直接赋进去
                as+=r.length();//加上拷贝次数
            }
            else
            {
                for(;v[i]!=')';i++)//找里面的变量名
                    r+=v[i];
                m[s]=m[r];//找到变量名对应的值赋进去
                as+=m[r].length();//加上拷贝次数
            }
        }
        else//处理同上，就是没有加拷贝次数
        {
            int l=v.length(),i;
            string s="",r="";
            for(i=0;v[i]!='(';i++)
                s+=v[i];
            i++;
            if(v[i]=='"')
            {
                for(i++;v[i]!='"';i++)
                    r+=v[i];
                m[s]=r;
            }
            else
            {
                for(;v[i]!=')';i++)
                    r+=v[i];
                m[s]=m[r];
            }
        }
    }
    printf("%d",as);//输出
    return 0;//华丽结束
}
```

---

