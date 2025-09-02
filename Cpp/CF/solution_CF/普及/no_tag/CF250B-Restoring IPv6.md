# Restoring IPv6

## 题目描述

An IPv6-address is a 128-bit number. For convenience, this number is recorded in blocks of 16 bits in hexadecimal record, the blocks are separated by colons — 8 blocks in total, each block has four hexadecimal digits. Here is an example of the correct record of a IPv6 address: "0124:5678:90ab:cdef:0124:5678:90ab:cdef". We'll call such format of recording an IPv6-address full.

Besides the full record of an IPv6 address there is a short record format. The record of an IPv6 address can be shortened by removing one or more leading zeroes at the beginning of each block. However, each block should contain at least one digit in the short format. For example, the leading zeroes can be removed like that: "a56f:00d3:0000:0124:0001:f19a:1000:0000" $ → $ "a56f:d3:0:0124:01:f19a:1000:00". There are more ways to shorten zeroes in this IPv6 address.

Some IPv6 addresses contain long sequences of zeroes. Continuous sequences of 16-bit zero blocks can be shortened to "::". A sequence can consist of one or several consecutive blocks, with all 16 bits equal to 0.

You can see examples of zero block shortenings below:

- "a56f:00d3:0000:0124:0001:0000:0000:0000" $ → $ "a56f:00d3:0000:0124:0001::";
- "a56f:0000:0000:0124:0001:0000:1234:0ff0" $ → $ "a56f::0124:0001:0000:1234:0ff0";
- "a56f:0000:0000:0000:0001:0000:1234:0ff0" $ → $ "a56f:0000::0000:0001:0000:1234:0ff0";
- "a56f:00d3:0000:0124:0001:0000:0000:0000" $ → $ "a56f:00d3:0000:0124:0001::0000";
- "0000:0000:0000:0000:0000:0000:0000:0000" $ → $ "::".

It is not allowed to shorten zero blocks in the address more than once. This means that the short record can't contain the sequence of characters "::" more than once. Otherwise, it will sometimes be impossible to determine the number of zero blocks, each represented by a double colon.

The format of the record of the IPv6 address after removing the leading zeroes and shortening the zero blocks is called short.

You've got several short records of IPv6 addresses. Restore their full record.

## 样例 #1

### 输入

```
6
a56f:d3:0:0124:01:f19a:1000:00
a56f:00d3:0000:0124:0001::
a56f::0124:0001:0000:1234:0ff0
a56f:0000::0000:0001:0000:1234:0ff0
::
0ea::4d:f4:6:0
```

### 输出

```
a56f:00d3:0000:0124:0001:f19a:1000:0000
a56f:00d3:0000:0124:0001:0000:0000:0000
a56f:0000:0000:0124:0001:0000:1234:0ff0
a56f:0000:0000:0000:0001:0000:1234:0ff0
0000:0000:0000:0000:0000:0000:0000:0000
00ea:0000:0000:0000:004d:00f4:0006:0000
```

# 题解

## 作者：封禁用户 (赞：4)

### 题意：
给出 $n$ 个压缩后的IPv6地址,给出一些压缩的方法,恢复IPv6地址的完整形式    
压缩方法有以下2条:        
1.删除前导 $0$ :       
（例如```a56f:00d3:0000:0124:0001:f19a:1000:0000``` $→$ ```a56f:d3:0:0124:01:f19a:1000:00```)        
2.用 $::$ 缩写连续 $0$ 序列          
（例如```a56f:00d3:0000:0124:0001:0000:0000:0000``` $→$ ```a56f:00d3:0000:0124:0001::```)        
注意IPv6地址只能用一次 $::$ 
### 分析：
不用什么算法，是较简单的字符串处理。但是码力很大，细节比较难处理。         
做法读完题目后已经很明确了，主要是以下三种情况：       
1.如果在两个 $:$ 之间有四个字符，直接输出，不用进行改变          
2.如果在两个 $:$ 之间少于四个字符，计算有几个字符，输出 $4-s$ 个 $0$ 后输出剩下的字符即可，其中 $s$ 代表两个 $:$ 之间的字符长度       
3.特殊的 $::$ 情况：我们要进行特殊处理，实现记录在 $::$ 之前有多少段，再寻找 $::$ 之后有多少段，这样就可以求出有多少段 $0000$ ,最后再输出就行了
### tips:
1.当记录到输出为最后一段时，要注意不要输出多余的空格或 $:$          
2.当不好观察输出时，可以使用文件输出。           
文件输出示例: ```freopen("test.txt","w",stdout);```      
打开程序所在位置的 ```test.txt``` 文件即可观察输出        
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,d,e,lsss;
string s;
int ts(int lss){//::的情况 
	e=0;
	for(int i=lss+1;s[i]!='\0';i++){
		if(s[i]==':'){
			e++;
		}
	}
	b+=e;
	b--;
	for(int i=1;i<=(7-b);i++){
		if((b-e+i)==8){
			cout<<"0000";
			break;
		}
		else{
			cout<<"0000:";
		}
	}
}
int findd(int ls){
	if(s[ls-1]==':'&&s[ls]==':'){//::的情况 
		ts(ls);
	}
	else{//一般的情况 
		for(int i=1;i<=(4-c);i++){
			cout<<0;
		}
		for(int i=ls-c;i<=ls;i++){
			if(s[i]-'0'>=0&&s[i]-'0'<=9)
				cout<<s[i];
			if(s[i]=='a'||s[i]=='b'||s[i]=='c'||s[i]=='d'||s[i]=='e'||s[i]=='f'||s[i]==':'){
				cout<<s[i];
			}
		}
	}
}
int main(){
	cin>>a;
	for(int i=1;i<=a;i++){
		b=0;
		cin>>s;
		c=0;
		d=0;
		lsss=0;
		for(int j=0;s[j]!='\0';j++){
			d++;
			if(s[j]==':'){
				lsss=j;
				b++;
				findd(j);
				c=0;
			}
			else{
				c++;
			}
		}
		findd(d);
		cout<<endl;
	}
} 
```

---

## 作者：0AND1STORY (赞：2)

这道题和

>[P2815 IPv6地址压缩](https://www.luogu.org/problemnew/show/P2815)

这道题一样，都是简单的字符串处理

只不过P2815是将完整的ipv6地址压缩，而这道题是将压缩后的ipv6地址展开，原理都差不多

P2815可以用

```cpp
scanf("%x:%x:%x:%x:%x:%x:%x:%x",&s[1],&s[2],&s[3],&s[4],&s[5],&s[6],&s[7],&s[8]);
```

的方法读入，而这一道题因为要处理双冒号，而且读入数的个数也无法确定，所以这道题只能用读入整个字符串的方法来做

根据题目很容易就想到做法，

### 步骤如下：

0. 宏定义。。。

```cpp
//不用在意这些宏定义，方便而已
#define main int main()
#define Void inline void
#define Int register int
#define for(i, l, r) for(Int i = l; i < r; i ++)
#define endmain return 0
```

1. 读入地址存入字符串s

```cpp
cin >> s;
```

2. 将字符串s中的数据转存到a数组中，用0xfffff代替双冒号

```cpp
Int x = 0;
for (i, 0, s.size() - 1)
{
    //如果发现双冒号，则将双冒号解释为0xfffff
    if (s[i] == ':' && s[i + 1] == ':')
    {
        a.push_back(x);    //因为发现双冒号相当于发现了冒号，将读入的数加入a中
        x = 0;
        a.push_back(0xfffff);   //将双冒号的标志加入a
        i ++;   //跳过下一个冒号
        continue;
    }
    //如果不是16进制数，即为冒号，则将已读入的数加入a
    if (!isdigit(s[i]) && (s[i] < 'a' || s[i] > 'f'))
    {
        a.push_back(x);
        x = 0;
        continue;
    }
    else    //如果是16进制的数，则用x记录读入到的数
    {
        //因为是16进制数，所以要乘16，x << 4就相当于乘16
        x = (x << 4) + (isdigit(s[i]) ? s[i] - '0' : s[i] - 'a' + 10);
    }
}
a.push_back(x); //以为地址最后不会有冒号，所以将最后一个数加入a
//如果地址最后为`:`，即双冒号在末尾，
//上一步多加了一个数，这一步将这个数删去
if (s[s.size() - 1] == ':')
    a.pop_back();
//否则最后是一个数字，因为扫描数字时没有扫描到最后一个，
//所以这一步将最后一位加上
else
    a[a.size() - 1] = (a[a.size() - 1] << 4) + (isdigit(s[s.size() - 1]) ? s[s.size() - 1] - '0' : s[s.size() - 1] - 'a' + 10);

```

3. 将a数组按照完整格式输出，计算"::"所代表的0的个数，并输出即可

```cpp
for (i, 0, a.size() - 1)
    //如果不是双冒号，即为16进制数，进行输出
    if (a[i] != 0xfffff)
        //%04x即为以列宽为4输出，空格用0填充
        printf("%04x:", a[i]);
    else
    {
        //如果为双冒号，计算双冒号代替的0的个数并输出
        //（此时双冒号不在最后）
        for (j, 0, 8 - a.size() + 1)
            printf("0000:");
    }
//如果双冒号不在最后，输出最后一个数
if (a[a.size() - 1] != 0xfffff)
    printf("%04x", a[a.size() - 1]);
else    //否则输出双冒号所代替的0
{
    //这里三目运算符用来判断是否需要在末尾加上冒号
    for (i, 0, 8 - a.size() + 1)
        printf("0000%s", i == 8 - a.size() ? "" : ":");
}
printf("\n");   //注意最后必须要换行，因为是多组数据

```

### AC代码如下：

```cpp
#include <cstdio>
#include <cctype>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//不用在意这些宏定义，方便而已
#define main int main()
#define Void inline void
#define Int register int
#define for(i, l, r) for(Int i = l; i < r; i ++)
#define endmain return 0

//定义一个a数组用来存从原地址中的数
vector<int> a;
//用来存读入的原地址
string s;

//从原地址中读入数存入a数组，这一段类似于快读
Void input()
{
    Int x = 0;
    for (i, 0, s.size() - 1)
    {
        //如果发现双冒号，则将双冒号解释为0xfffff
        if (s[i] == ':' && s[i + 1] == ':')
        {
            a.push_back(x);    //因为发现双冒号相当于发现了冒号，将读入的数加入a中
            x = 0;
            a.push_back(0xfffff);   //将双冒号的标志加入a
            i ++;   //跳过下一个冒号
            continue;
        }
        //如果不是16进制数，即为冒号，则将已读入的数加入a
        if (!isdigit(s[i]) && (s[i] < 'a' || s[i] > 'f'))
        {
            a.push_back(x);
            x = 0;
            continue;
        }
        else    //如果是16进制的数，则用x记录读入到的数
        {
            //因为是16进制数，所以要乘16，x << 4就相当于乘16
            x = (x << 4) + (isdigit(s[i]) ? s[i] - '0' : s[i] - 'a' + 10);
        }
    }
    a.push_back(x); //以为地址最后不会有冒号，所以将最后一个数加入a
    //如果地址最后为`:`，即双冒号在末尾，
    //上一步多加了一个数，这一步将这个数删去
    if (s[s.size() - 1] == ':')
        a.pop_back();
    //否则最后是一个数字，因为扫描数字时没有扫描到最后一个，
    //所以这一步将最后一位加上
    else
        a[a.size() - 1] = (a[a.size() - 1] << 4) + (isdigit(s[s.size() - 1]) ? s[s.size() - 1] - '0' : s[s.size() - 1] - 'a' + 10);
}

Void work()
{
    //记得将a数组清空
    a.clear();
    s = "";
    cin >> s;
    input();    //将a数组中的数据读入a数组
    for (i, 0, a.size() - 1)
        //如果不是双冒号，即为16进制数，进行输出
        if (a[i] != 0xfffff)
            //%04x即为以列宽为4输出，空格用0填充
            printf("%04x:", a[i]);
        else
        {
            //如果为双冒号，计算双冒号代替的0的个数并输出
            //（此时双冒号不在最后）
            for (j, 0, 8 - a.size() + 1)
                printf("0000:");
        }
    //如果双冒号不在最后，输出最后一个数
    if (a[a.size() - 1] != 0xfffff)
        printf("%04x", a[a.size() - 1]);
    else    //否则输出双冒号所代替的0
    {
        //这里三目运算符用来判断是否需要在末尾加上冒号
        for (i, 0, 8 - a.size() + 1)
            printf("0000%s", i == 8 - a.size() ? "" : ":");
    }
    printf("\n");   //注意最后必须要换行，因为是多组数据
}

main
{
    Int t;
    scanf("%d", &t);
    while (t --)
        work();
    endmain;
}
```

#### 最后附上一张AC截图：

![AC截图](https://s2.ax1x.com/2019/01/27/kubUQP.png)


---

## 作者：TLEWA (赞：1)

## 题意

给出 $n$ 个可能经过压缩的 IPv6 地址，让我们输出 $n$ 个地址解压缩后的字符串。Ipv6 地址格式和压缩规则如下：

### 地址格式

IPv6 地址被分为八个块，每一块是四个十六进制数字，相邻块以 `:` 分割

如：`2001:4860:4860:0000:0000:0000:0000:8888`。

## 压缩规则

对于每一个块，我们可以将其的前导零删除，如：`a56f:00d3:0000:0124:0001:f19a:1000:0000` 可以变为 `a56f:d3:0:0124:01:f19a:1000:00`（注意变换方式不一定是唯一的，给出的字符串可能没有经过完全压缩）

特别地，对于一个或多个多个连续的 `0000` 块，我们可以使用 `::` 替换它们，注意 `::` 替换在整个 IPv6 串中只会使用最多一次。如：`0001:0000:0000:0000:0000:0000:0000:0001` 可以变为 `1::1`。

## 解题思路

这是一道明显的大模拟，`:` 字符在解压缩字符串的过程中很烦人，所以我们考虑先将十六进制字符串先分组存储，将每块分别解压缩后再拼接。对于 `::` 这个压缩方法，我们使用这个分离的方法也很好处理，由于 IPv6 串固定有八个块，我们计算出被 `::` 压缩的块以外的块数，`::` 压缩的 `0000` 块数即为 $8 - 非 :: 压缩串数量$，在分离块或输出的时候直接添加即可。

以下是我的 AC 代码，如果对流程有不理解可以结合代码和注释理解：

```cpp
#include<bits/stdc++.h>

using namespace std;

int n,p,plusp;
string s,arr[10];

void split(string s) { //将串拆解成块
	if(s[s.size()-1]!=':')s+=':';
	s+=' ';
	int las=0;
	p=0,plusp=-1;
	for(int i=0;i<s.size()-1;++i) {
		if(s[i]==':') {
			++p;
			arr[p]="";
			for(int j=las;j<i;++j) arr[p]+=s[j];
			las=i+1;
			if(s[i+1]==':'){
				las=i=i+2;
				plusp=p;
			}
		}
	}
}

string get(string s) {
	split(s);
	string news="";
	for(int i=1;i<=p;++i) {
		for(int j=1;j<=(4-arr[i].size());++j)  news+='0'; //处理前导零被压缩
		for(auto c:arr[i]) news+=c;
		if(plusp==i) {
			for(int j=1;j<=(8-p);++j) news+="0000"; //处理 :: 压缩
		}
	}
	string lasts="";
	for(int i=1;i<=news.length();++i) {
		lasts+=news[i-1];
		if(i<32&&i%4==0) lasts+=':'; //添加 :，将块重新拼接成 IPv6 串
	}
	return lasts;
}

int T;
int main() {
	cin >> n;
	for(int i=1;i<=n;++i) {
		cin >> s;
		cout << get(s) << endl;
	}
	
	return 0;
}
```

## 一些闲话

由于每个输入的块是十六进制的，所以可以使用 `scanf("%x")` 来处理，是一种很聪明的写法。但是碍于笔者对于 C 风格的 IO 实在不甚熟悉，所以这种做法我就不赘述了，感兴趣可以自己实现一下。

---

## 作者：fz20181223 (赞：1)

这题对于每组数据来看先将答案数组清零（变为 `0000`）。

在给出缩写中找出 `::` 子串。此时分为两种情况：

第一种：找到了。此时将这个地址分为 `::` 前和 `::` 后两段，对于前面一段，将每个块从头开始往下填。比如对于 `19:26::8:17`，我们发现前面一段为`1:2:3:4`，则从答案数组的第 $0$ 个元素开始，分别放入 `0019`，`0026`。然后对于后面一段，从后往前枚举，将答案从最后一个元素往前填。比如对于前面列出来的 ip，我们发现后面一段为 `8:17` ，则从答案的第 $7$ 个元素开始，分别放入 `0017`，`0008`。

当然，还有第二种情况：没找到。此时直接对这个字符串进行处理即可。为了减少特判，我们可以将其从最后一块的后面分开，分成前面一段为原 ip，后面一段为空的情况进行处理。

强烈建议全程把出现的 ip 当做字符串做，不要转成任何进制的数字。同时建议在分成的前面一段的最后以及后面一段的最前加上 `:` 以免循环完后还要再次处理。

附：AC 代码
```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define pii pair<int,int>
#define mii map<int,int>
#define mset(a,x) memset(a,x,sizeof(a))
#define msetl(a) memset(a,0x3f,sizeof(a))
#define pb push_back
#define mp make_pair
using namespace std;
const int err=-120712^7869^12174,uerr=0x3f3f3f3f,eps=1e-9;
string st,pre="",lst="",ans[8];
int n;
string change(string st){
	while(st.size()<4) st='0'+st;
	return st;
}
void decode(string st){
	for(int i=0;i<8;++i) ans[i]="0000";
	pre="",lst="";
	int i;
	for(i=0;i<st.size()-1;++i){
		if(st[i]==':'&&st[i+1]==':'){
			pre=st.substr(0,i+1);
			lst=st.substr(i+1);
			break;
		}
	}
	if(i==st.size()-1) pre=st+':';
//	cout<<"pre="<<pre<<" lst="<<lst<<endl;
	string t;int p=0;
	for(int i=0;i<pre.size();++i){
		if(pre[i]==':'){
			ans[p++]=change(t);
			t="";
		}
		else t+=pre[i];
	}
	p=7,t="";
	for(int i=lst.size()-1;i>=0;--i){
		if(lst[i]==':'){
			ans[p--]=change(t);
			t="";
		}
		else t=lst[i]+t;
	}
	for(int i=0;i<8;++i) cout<<ans[i]<<":\n"[i==7];
}
int main(){
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);
	scanf("%d",&n);
	while(n--){
		cin>>st;
		decode(st);
	}
	return 0;}

```

---

## 作者：罗小黑小鱼 (赞：1)


## 一、思路
由于 $ipv6$ 地址有 $8$ “段”，所以我们在复原的时候可以先定义个 $ss[9]$，其中 $ss[i]$ 表示第 $i$ “段”。**以下会分为几个小节进行讲解。**

### 如何分“段”
我们可以先考虑从左到右将字符串扫描一次，如果字符串结束或者遇到冒号，就可以记为一段。
### 如何补充每一段省略的$0$
在扫描的时候，定义一个 $p$，代表扫描到一段中非冒号字符个数，如果遇到冒号，就有两种情况：$p==4$ 和 $p!=4$。情况一：没有省略的$0$；情况二：有省略，那么可以根据 $p$ 的值先在 $ss[pe]$（$pe$ 代表段数，下面的小节会详细说明）中补充 $4-p$ 个$0$。处理完后，$p$ 归零。
### 如何记录段数
定义一个 $pe$，初始值为$1$，代表一开始处理的是第一段。在上述操作结束时，$pe++$。
### 如何判断双冒号省略了多少$0$
举个例子，如此地址：

	::1
    ::rq
补全之后为：

	0000:0000:0000:0000:0000:0000:0000:0001
    0000:0000:0000:0000:0000:0000:0000:00rq
由于在省略$0$后面又有要补充的数字和字母，我们便只补充全$0$。所谓全$0$，是指有若干段，每一段整段都是零。如上述的全$0$为：

	0000:0000:0000:0000:0000:0000:0000
    0000:0000:0000:0000:0000:0000:0000
之后的$0001$和$000rq$可以由第二小节中的操作将缺失$0$的段补充完整。

那么到底如何判断双冒号的全$0$有多少个？我们可以在处理之前先看除了双冒号外有多少完整或不完整的段，假设段数为 $m$，则最后全$0$个数为 $32-4*m$ （为了保持 $C++$ 的特性，乘号作星号），中间有 $8-m$ 段是全$0$段。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,s1,ss[9];
int n,tot,num,p,flag,pe,zero,num_,m;
void output(){
	for(int j=1;j<=7;j++)
		cout<<ss[j]<<":";
	cout<<ss[8]<<"\n";
}//输出函数，方便调试
int main(){
	scanf("%d",&n);
	while(n--){
		tot=0;
		zero=0;
		flag=0;
		num_=0;
		p=0;
		m=0; //一开始完整或不完整的段数
		pe=1;
		s="";
		for(int i=1;i<=8;i++) ss[i]="";//全部初始化
		cin>>s;
		for(int i=0;i<s.size();i++)
			if(s[i]!=':') tot++;
			else{
				if(s[i+1]==':') i++,num_++;
				if(tot) m++,tot=0;
			}
		if(num_>1){
			cout<<"INVALID\n";
			continue;
		}
		if(tot) m++; 
		zero=32-4*m;//判断有多少0待补
		int i;
		for(i=0;i<=s.size();i++){
			
			if(s[i]!=':'&&i!=s.size()) p++;//一段中数或字母的个数++
			if(s[i]==':'||i==s.size()){
				if(p){
					if(p>4){
						cout<<"INVALID\n";
						flag=1;
						break;
					}else{
						for(int j=1;j<=4-p;j++) ss[pe]+='0';//补0
						for(int j=i-p;j<i;j++) ss[pe]+=s[j];
					}//上述操作2，即补不完整段中的0
					pe++;//段数++
				}
				p=0;
				if(i!=s.size()){
					if(s[i+1]==':'){
						num=zero/4;
						for(int j=pe;j<pe+num;j++) ss[j]="0000";
						pe+=num;
						i++;//跳过这个冒号，直接开始下一个数字或字母
					}
				} //补全0，有num段，所以pe+=num
				
			}
		}
		if(flag) continue;//这里是判断输入不合法，输出“Invalid”也是在判断输入不合法，虽然题目中不存在这样的要求，但是还是添加了部分判断，读者可以忽略
		output();//输出
	}
	return 0;
}
```
**如果看代码看不懂，请务必多看思路，代码的编写紧扣思路。**


---

## 作者：joe_zxq (赞：0)

# 思路

这是一道字符串操作题。

我们可以将每一段用 `:` 隔开的子串存起来，若位数不足 $4$ 位，用 $0$ 补成 $4$ 位。

由于题目保证 `::` 至多出现一次，我们便可以计算有多少个用 `:` 隔开的子串，就能得到 `::` 省略了多少个 `0000`。

最后用存起来的子串依次输出，注意不要输出多余的 `:`。 

若你的代码过了样例，但是提交上去后得到了 WA，建议使用下面的数据进行调试。

输入文件：

```
4
::1ed
::30:44
::eaf:ff:000b
56fe::
```

输出文件：

```
0000:0000:0000:0000:0000:0000:0000:01ed
0000:0000:0000:0000:0000:0000:0030:0044
0000:0000:0000:0000:0000:0eaf:00ff:000b
56fe:0000:0000:0000:0000:0000:0000:0000
```

# 代码

附上 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<string>ans;
vector<string>ss;
void solve(){
	ans.clear();
	ss.clear();
	string s; cin>>s;
	if(s[0]==':'){
		s=s.substr(1);
	}
	s=s+":";
	int cnt=0;
	for(int i=0;i<(int)s.size()-1;i++){
		if(s[i]!=':'&&s[i+1]==':'){
			cnt++;
		}
	}
	if(s[(int)s.size()-1]==':'&&s[(int)s.size()-2]==':')s.pop_back();
	cnt=8-cnt;
	string now="";
	for(int i=0;i<(int)s.size();i++){
		if(s[i]==':')ss.push_back(now),now="";
		else now+=s[i];
	}
	for(int i=0;i<(int)ss.size();i++){
		if(ss[i]==""){
			for(int j=1;j<=cnt;j++){
				cout<<"0000";
				if(j!=cnt)cout<<":";
			}
			cnt=0;
		}else{
			while((int)ss[i].size()<4){
				ss[i]="0"+ss[i];
			}
			cout<<ss[i];
		}
		if(i!=ss.size()-1)cout<<":";
	}
	cout<<endl;
}
int main(){
	int tc; cin>>tc;
	while(tc--){
		solve();
	}
	return 0;
}
```

 

---

