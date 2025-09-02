# [AHOI2002] Kitty猫基因编码

## 题目描述

小可可选修了基础生物基因学。教授告诉大家 Super Samuel 星球上 Kitty猫的基因的长度都是 2 的正整数次幂 )， 全是由两种不同的基因单元组成的。 这两种不同的基因单元分别记成 0 和 1，于是 Kitty 猫基因可以写成一个 01 串表达式 。

为了便于分析和降低数据存储量，教授发明了 ABC 编码规则。该编码规则是不断地按照

 ![](https://cdn.luogu.com.cn/upload/pic/1679.png) 

对 Kitty 猫基因 01 串表达式 进行改写， 直至最终被改写成只含有字符 “ A”、“ B”、“ C”的符号串。

 ![](https://cdn.luogu.com.cn/upload/pic/1680.png) 

请你编写程序帮助小可可求出 Kitty 猫基因的 ABC 编码以协助教授开展科研工作。


## 说明/提示

给出的01字符串长度$Len\leq 256$

## 样例 #1

### 输入

```
00```

### 输出

```
A```

## 样例 #2

### 输入

```
01001011```

### 输出

```
CCCABACCBAB```

# 题解

## 作者：狸狸养的敏敏 (赞：34)

看到楼下一堆大佬都是用的什么前缀和，线段树，我感觉很惭愧啊。

其实这道题只需要按照题意来模拟就好了，可以证明到，最坏的时间复杂度就是$O(NlogN)$,就是101010....交替出现的情况

那么这个复杂度对这道题来说是很优秀的，我们知道c++为我们提供了string类，所以利用string类可以使用"+"运算符的特性，我们写出以下代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string T(string str)
{
	int sum=0;
	for(int i=0;i<str.length();i++)
	sum+=str[i]-'0';//统计字符串中1的个数
	if(!sum)return "A";//按照题意，全0串返回"A"
	if(sum==str.length())return "B";//全1串返回"B"
	int mid=(str.length()+1)>>1;//计算字符串的一半的长度
	string str1,str2;
	str1=str2="";
	for(int i=0;i<mid;i++)
	str1+=str[i];//暴力截取前半部分
	for(int i=mid;i<str.length();i++)
	str2+=str[i];//暴力截取后半部分
	return "C"+T(str1)+T(str2);//按题意
}
string str;
int main()
{
	cin>>str;
	cout<<T(str)<<endl;//主程序很简单
	return 0;
}
```

---

## 作者：Saliеri (赞：29)

# 本蒟蒻第二篇题解，如有漏洞，请多指教
这道题既然是输入了一行只有0,1的字符，那我们可以自然地想到——
```cpp
#include <cstring>
```
这个神奇的头文件下有许多极其方便的字符串处理函数，我作为一位被字符串整得死去活来的蒟蒻，在此普及一下如何用这些函数
##### 简洁地
水过这道水题——


---------------------------------------------------------华丽丽的分割线----------------------------------------------------------
## 1
首先我们看到题目要求：

若s串全为0——————A

若s串全为1——————B

否则 C+将s串分成二等分分别处理

### 赤裸裸的递归呀

思路√

## 2
首先，如何判断目前s串全为1或全为0呢？
#### s.find大法好啊！
首先，了解一下find函数的性质——1.如果找到参数字符串，返回找到的第一个字母的位置；2.否则返回-1；

如果要判断全为0，检查find("1")是否==-1；
反之，检查find("0")是否==-1；
```cpp
if(s.find('1')==-1) {printf("A");return ;}
if(s.find('0')==-1) {printf("B");return ;}
```


如果以上皆不成立，分成同样的两部分递归处理：
```cpp
int t=s.size();
printf("C");
dg(s.substr(0,t/2));
dg(&s[t/2]);
```
注：s.substr：指定起点与终点，取s从起点到终点之前的子串；

&s[t/2]：&，取址符；字符串一种极其诡异的性质：取某一个字符的地址，便会自动遍历至字符串末尾……这正好帮了我们，直接&s[t/2]就可以取后半部分了……
## 3 完整代码
```cpp
#include <iostream>
#include <cstring>
using namespace std;
string ss;
void dg(string s) {
	if(s.find('1')==-1) {printf("A");return ;}
	if(s.find('0')==-1) {printf("B");return ;}
	int t=s.size();
	printf("C");
	dg(s.substr(0,t/2));
	dg(&s[t/2]);
}
int main() {
	cin >> ss;
	dg(ss);
	return 0;//编码完成祭
}
```
17行，还不错……

---

## 作者：dream_maker (赞：13)

题目大意是裸裸的递归求解，但其过程可以进行优化，本弱采用前缀数组进行优化，楼下貌似有相似代码，本弱思路仅供借鉴。

s[i]数组记录从第一位到第i位的和,所以

l~r为1等价为s[r]-s[l-1]==r-l+1

l~r为0    等价为s[r]-s[l-1]==0

然后递归求解就好了


代码君奉上

```cpp
#include<bits/stdc++.h>
using namespace std;
int s[2000010]={0};
void Find(int l,int r){
    if(s[r]-s[l-1]==0){putchar('A');return;}
    if(s[r]-s[l-1]==r-l+1){putchar('B');return;}
    putchar('C');
    int mid=(l+r)>>1;
    Find(l,mid);
    Find(mid+1,r);
}
int main() {
    int num=0;
    while(1){
        char t=getchar();
        if(t!='0'&&t!='1')break;
        s[++num]=s[num-1]+t-'0';
    }
    Find(1,num);
    return 0;
}
```

---

## 作者：TianZ (赞：12)

嗯，看到这是道推题就想进来水一手，结果看完题目码代码的时候，我好想把一道递推的题硬生生用二分想出来了！！！好吧其实我自己也木有理解自己代码的意思~~，完全是瞎蒙（果然还是太蒟蒻了)~~

**话不多说，上代码**
```cpp
#include<bits/stdc++.h>//万能头不解释
using namespace std;
char num[2000005];
void search(int left,int right){
	int mid=(left+right)/2,ans=0;//mid指向中间
	for(int i=left+1;i<=right;i++)
		if(num[i]!=num[i-1]){//查找是否存在不相同的数
			ans++;//找到了就记录
			cout<<"C";//并输出C
			search(left,mid);//二分操作
			search(mid+1,right);
			break;//找到了还能咋滴，退出呗
		}
	if((!ans) && num[left]=='0')cout<<"A";//如果之前没有找到，就输出A或B
	if((!ans) && num[left]=='1')cout<<"B";
}
int main(){//主函数
	ios::sync_with_stdio(false);//输入输出流加速
	cin>>num;
	search(0,strlen(num)-1);//递推
	return 0;//华丽结束
}
//如果看不懂那段递推代码可以手模一下，我就是这么做的T^T
```

---

## 作者：迷残云 (赞：6)

一开始没看见基因长度都是2的整数次幂，我去，调了半天崩溃了

作为AH人，必须写啊

提示：
先用字符串读入，然后用递归，按照题目的要求进行转化，最后输出转化的结果即可。

1．  当S为空子串时退出返回

2．  当S串全是0时，退出返回‘A’

3．  当S串全是1时，退出返回‘B’

4．将S串分成两部分，继续递归，并加C。


```cpp
#include<bits/stdc++.h>
using namespace std;
char str[256];
void dna(int s,int e)
{
	int i;
	for(i=s+1;i<e;i++)
	 if(str[i]!=str[i-1])//不相等就二分
	 {
	 	cout<<"C";
	 	dna(s,(s+e)/2);//左区间
	 	dna((s+e)/2,e);//右区间 （~~大佬有没有想起建树？~~）   
         return; //不能省★
	 }
	 if(str[s]=='0')cout<<"A";else cout<<"B";
}
int main()
{
	int n;
	cin>>str;n=strlen(str);
	dna(0,n);//起点和终点
	cout<<endl;
	return 0;
}
```

---

## 作者：览遍千秋 (赞：4)

楼上大神的线段树等各种优化看晕了蒟蒻，蒟蒻决定来一发对其他蒟蒻友好的C++题解。

---
题目要求很明确，我们只需要按题意模拟即可。每次扫描一遍当前串，如果全是0就输出A，如果全是1就输出B，否则递归分成两份求解。

---
代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
string k;
int lo;

inline void f(int l,int r)
{
    if(l==r)//递归终止条件
    {
        if(k[l]=='0')
            printf("A");
        else
            printf("B");
        return;
    }
    bool z=0,o=0;
    for(register int i=l;i<=r;i++)//扫描该串
        if(k[i]=='0')
            z=1;
        else
            o=1;
    if(z&&!o)//如果全是0
    {
        printf("A");
        return;
    }
    if(!z&&o)//如果全是1
    {
        printf("B");
        return;
    }
    printf("C");//开始分
    f(l,(l+r)>>1);//左边
    f((l+r)/2+1,r);//右边，这里位运算会出错
}
inline void Init()
{
    cin>>k;//输入基因
}
inline void Work()
{
    lo=k.size();//求长度
    f(0,lo-1);//开始递归
}
int main()//华丽的主函数
{
    Init();
    Work();
    return 0;
}
```

---

## 作者：redegg (赞：3)

我一看，这不是线段树吗（没错，我就是为线段树发题解），其实不用线段树，递归一下就完事。

但是作为发题解最喜欢发线段树的我，肯定要来一发线段树啊。

线段数可以和这题完美融合（天生一对），线段树本来就是一半一半地分的嘛！

最令我向往的是：

线段树建树的时候就可以返回半段区间的总和，总和为0直接输出B，总和等于长度则输出A，否则继续输出C然后分下去，是不是比递归快很多呀╮(╯▽╰)╭！

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

struct ha
{
    int x,v;
}a[8000005];
char s[1000005];
int n;

void build(int l,int r,int id)
{
    if(l==r)
    {
        a[id].x=s[l]-'0';
        a[id].v=1;
        return ;
    }
    else
    {
        int mid=(l+r)/2;
        build(l,mid,id*2);
        build(mid+1,r,id*2+1);
        a[id].x=a[id*2].x+a[id*2+1].x;
        a[id].v=a[id*2].v+a[id*2+1].v;
    }
}

void ck(int l,int r,int id)
{
    if(a[id].x==a[id].v)
    {
        printf("B");
        return ;
    }
    if(a[id].x==0)
    {
        printf("A");
        return ;
    }
    int mid=(l+r)/2;
    printf("C");
    ck(l,mid,id*2);
    ck(mid+1,r,id*2+1);
}

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);

    build(1,n,1);
    ck(1,n,1);
    printf("\n");
    return 0;
}
```cpp

---

## 作者：一扶苏一 (赞：3)

## Solution

### 这不是线段树裸题嘛=  =

我们考虑对这个字符串建立线段树，每个节点维护这个区间内部有没有 $0$ 和有没有 $1$，由于保证字符串长度为 $2$ 的次幂，我们这样建出的线段树刚好是符合题目要求的，于是按照题意从根节点递归输出答案即可。时间复杂度 $O(n \log n)$

## Code

```cpp
#include <cstdio>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 1000010;
const int maxt = 2000010;

struct Tree {
	Tree *ls, *rs;
	int l, r;
	bool a, b;
	
	inline void pushup() {
		this->a = this->ls->a | this->rs->a;
		this->b = this->ls->b | this->rs->b;
	}
	
	inline bool Alla() {return this->a && !this->b;}
	inline bool Allb() {return this->b && !this->a;}
};
Tree *pool[maxt], qwq[maxt], *rot;
int top;

int len;
int MU[maxn];

void buildpool();
void print(Tree*);
void build(Tree*, ci, ci);

int main() {
	freopen("1.in", "r", stdin);
	do MU[++len] = IPT::GetChar(); while ((MU[len] == '0') || (MU[len] == '1'));
	--len;
	buildpool();
	build(rot, 1, len);
	print(rot);
}

void buildpool() {
	for (rg int i = 0; i < maxt; ++i) pool[i] = qwq + i;
	rot = pool[maxt - 1]; top = maxt - 2;
}

void build(Tree* u, ci l, ci r) {
	u->l = l; u->r = r;
	if (l == r) {if (MU[l] == '0') u->a = true; else u->b = true; return;}
	int mid = (l + r) >> 1;
	if (l <= mid) build(u->ls = pool[top--], l, mid);
	if (mid < r) build(u->rs = pool[top--], mid + 1, r);
	u->pushup();
}

void print(Tree *u) {
	if (u->Alla()) putchar('A');
	else if (u->Allb()) putchar('B');
	else {
		putchar('C');
		print(u->ls);
		print(u->rs);
	}
}
```



---

## 作者：qzgx_41 (赞：2)

首先，这道题一看就是大水题，递归+模拟，我们只需要string里面的两个函数就行了，下面让本大（jû）佬（ruò）来给你们说一下。。。

①a.find（char x或string x）：返回a里面第一个是x的字符（字符串）的首字母下标，如果没有就返回-1

②a.substr（int a，int b）：返回从a开始，长度为b的字符串

知道了这些，就很好写代码了。

```cpp
#include <iostream>
#include <string>
using namespace std;
string t(string a,int n)//n是长度
{
    if(a.find('1')==-1)return "A";//如果没有1（全0）
    if(a.find('0')==-1)return "B";//如果没有0（全1）
    return "C"+t(a.substr(0,n/2),n/2)+t(a.substr(n/2,n/2),n/2);//前一半从0开始，长度为n/2；后一半从n/2开始，长度也是n/2。字符串能做加法，如“A”+“BC”=“ABC”，但不能做减法
}
int main()
{
    string a;
    cin >> a;
    cout << t(a,a.size());
    return 0;
}
```


---

## 作者：谬悠 (赞：2)

因为这题涉及到一个查询的问题，而每次分割都需要从头检查是否为全0或全1，很麻烦，当然这题数据很小，不然是容易超时的

而有一个叫做前缀和的东西，可以在O（1）的时间内判断，这篇题解就用来讲解一下前缀和吧~~~~~~~

Qwq
另外讲解一下题意，注意，是从前往后处理的，

前缀和就是把前面的信息不断累加，详情见代码吧Qwq

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
string shu;
long long num[500];
void fen(int x,int y) {
	if(x>y)return;
	if(x==y) {
		if(shu[x]=='0')cout<<'A';
		else cout<<'B';
	}//分开处理，希望能跑的快一点
	else if(num[y]-num[x]+(shu[x]-'0')==0)//这里就是查询操作了，如果这一段没有出现1则输出A
		cout<<'A';
	else if(num[y]-num[x]+(shu[x]-'0')==y-x+1)//之所以要这么写是因为第一个值处理的有问题、、、、
		cout<<'B';
	else {
		cout<<'C';
		fen(x,x+(y-x)/2);//写的很丑
		fen(x+(y-x)/2+1,y);//我是蒟蒻
	}//分成两段递归求解
	return;
}
int main() {
	cin>>shu;
	int str=shu.size();
	num[0]=shu[0]-'0';//其实不应该这么写的，但由于我前面没有选择垫空格，就这么处理第一个了
	for(int i=1; i<str; i++) {
		num[i]=num[i-1]+(shu[i]-'0');//每个num【i】的值代表前面出现了几个1
	}
	fen(0,str-1);//开始递归
	return 0;
}
```

望管理员大大通过


---

## 作者：抽了风的你 (赞：2)

# 不会string的往这看
本蒟蒻第二次发题解
~~第一次还被删了，呜呜呜~~~~~

纯粹靠char数组

本题是一道明显的递归

### 不多说，上代码


------------


```cpp
#include<bits/stdc++.h>
using namespace std;
void cat(char *s,int n);//*是指针，就是一个char数组，n字符串是长度 
int main()//主函数 
{
	char S[260];//原始数组 
	int N;//符串是长度 
	cin>>S;//输入 
	N=strlen(S);//strlen是获取字符串长度 
	cat(S,N);
}
void cat(char *s,int n)
{
	int s1=0,s0=0;//s1是1的个数，s0是0的个数 
	for(int i=0;i<n;i++)//统计 
	{
		if(s[i]=='1')
		{
			s1++;
		}
		if(s[i]=='0')
		{
			s0++;
		}
	}
	if(s1==n)//如果全是1，输出B，返回 
	{
		cout<<"B";
		return;
	}
	else if(s0==n)//如果全是0，输出A，返回 
	{
		cout<<"A";
		return;
	}
	cout<<"C";//既然可以执行到这一步，证明这个字符串有1和0 
	char a[260];
	strncpy(a,s,n/2);//定义一个新的字符串，表示原字符串的左半段 
	cat(a,n/2);//左半段 
	cat(&s[n/2],n/2);//右半段 
}
```
###### 求过（小声BB）

---

## 作者：beng (赞：2)

# 很直白的递归题……

三种情况在题目描述内已解释得很清楚了，直接编代码就行了……（思维要求较少，初学者必备）

话说这里**判断子串是否只有0或1不用循环一个一个去判断，只需用pos判断是否存在另一个数**就行了……

不多说，直接上代码。

——————分割不完全的分割线——————

pascal代码如下：

```pascal
var s:ansistring;//数据长度超过string范围，故用ansistring
function go(s:ansistring):ansistring;//同上
begin
  if pos('1',s)=0 then//子串全部是0，即子串内不含1
  go:='A'//编码为A
  else
  if pos('0',s)=0 then//子串全部是1，即子串内不含0
  go:='B'//编码为B
  else
  go:='C'+go(copy(s,1,length(s) div 2))+go(copy(s,length(s) div 2+1,length(s) div 2));//子串有0有1，编码为C和前后两段字串递归下去（copy那一段较难理解，请认真思考）
end;
begin
  readln(s);
  writeln(go(s));//开始递归
end.
```

---

## 作者：yyyyyyy (赞：1)

【问题转述】

这道题就是给你一个长度2^k的01序列，然后让你把这个01序列转换成ABC编码。转化方法，如果子串全是0，那么就转换成A，如果子串全是1，那么转换成B，否则，就把这个子串分成长度相等的两个子串，加一个C，然后转换分开的两个子串。

【解决方法】

首先，这道题要用到字符串；而且问题中说，如果子串不是全为0或1，那么就要分成长度相等的两个子串，这就要用到我们学过的算法二分，如果当前子串不为全0或1，我们就要把子串切分，直到这个子串为全0或1为止。并且，不用担心子串不能分成长度相等的子串，因为子串的长度是2的次方，所以一定能被二整除。

【解题程序】

```cpp
var
 s,s1:ansistring;//因为k最大是8，2的8次方是256，正好超出了string的长度，所以要用ansistring。
procedure try(l,r:longint);
 var
  f:boolean;
  i:longint;
 begin
  f:=true;
  for i:=l to r-1 do
   if s[i]<>s[i+1]//判断这个子串是否全部相同。
   then begin
         f:=false;
         break;
        end;
  if f//如果f为true，说明这个子串全部相同。
   then begin
         if s[l]='0'//判断这个子串是全0还是全1。
          then s1:=s1+'A'
          else s1:=s1+'B';
         exit;
        end;
  s1:=s1+'C';//如果这个子串不是全部相同，那么加一个C，把子串分成两份。
  try(l,(l+r) div 2);//调用前一个子串。
  try((l+r) div 2+1,r);//调用后一个字串。
 end;
begin
{assign(input,'kitty.in');
 reset(input);
 assign(output,'kitty.out');
 rewrite(output);}
 readln(s);
 s1:='';//s1用来存储转换后的ABC编码。
 try(1,length(s));//子程序调用，开始转换。
 writeln(s1);
{ close(input);
 close(output);}
end.

```

---

## 作者：ICEMAGE (赞：1)

看了楼上的大佬，突然发现没有暴力套线段树的（数据范围好像真的有点小），在下便贡献一份。



```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[300000];
char s[300000];
int build(int k)    //直接建树，a数组表示这个区间的元素是不是完全相同
{
    if (k>=n) return 0;
    build(2*k);
    build(2*k+1);
    if ((a[2*k]==0)&&(a[2*k+1]==0)) {a[k]=0;return 0;}
    if ((a[2*k]==1)&&(a[2*k+1]==1)) {a[k]=1;return 0;}
    a[k]=2; return 0;
}
int find(int k)  //按照前例遍序直接输出
{
    printf("%c",(char) 'A'+a[k]);
    if ((a[k]==0)||(a[k]==1)) return 0;
    find(2*k);
    find(2*k+1);
    return 0;
}
int main()
{
    scanf("%s",&s);
    n=strlen(s);
    for (int i=n;i<2*n;i++)
      a[i]=s[i-n]-'0';            //直接把值赋给叶子节点
    build(1);
    find(1);
    return 0;
}
```

---

## 作者：AdzearDisjudge (赞：1)

转了一圈没有用string内置函数玩的~~，那我水一发好了~~

**s.find(char c)**:判断s中是否存在字符c，存在返回第一次出现的位置，不存在返回string::npos

**s.substr(int pos,int len)**:返回从s.at(pos)开始，长度为len的子字符串，也就是s.at(pos)~s.at(pos+len-1)（s.at(x)可以理解为等价于s[x]）

然后我们根据题意构造递归函数，用find()判断只有‘0’，‘1’还是都有，只有一种直接返回“A”或“B”，有两种就用substr切成两个，分别递归，返回‘C’+子串1返回值+子串2返回值即可。

~~不要在意我很长的板子，里边有很多没用的东西~~

```cpp
#include<bits/stdc++.h>
#define rep(i,a,n) for(register int i=a;i<=n;++i)
#define per(i,a,n) for(register int i=a;i>=n;--i)
#define mem(a) memset(a,0,sizeof(a))
#define elif else if
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
inline ll read()
{
    ll f=1,x=0;
    char ch;
    do
    {
        ch=getchar();
        if(ch=='-')
        f=-1;
    }
    while(ch<'0'||ch>'9');
    do
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    while(ch>='0'&&ch<='9');
    return f*x;
}
string check(string s)
{
	if(s.find('0')!=string::npos)
	{
		if(s.find('1')!=string::npos)
		{
			int t=s.size();
			return 'C'+check(s.substr(0,t/2))+check(s.substr(t/2,t/2));
		}
		else
		return "A";
	}
	else
	{
		if(s.find('0')!=string::npos)
		{
			int t=s.size();
			return 'C'+check(s.substr(0,t/2))+check(s.substr(t/2,t/2));
		}
		else
		return "B";
	}
}
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	string s;
	cin>>s;
	cout<<check(s);
//	fclose(stdin);
//	fclose(stdout);
    return 0;
}

```


---

## 作者：斯蒂芬·库里30 (赞：0)

看到题目关于第三种转化可以想到通过递归算法实现1/2的传递

关于1.2.两条转换规则

暴力加和时间复杂度爆炸,会T

可以通过前缀和优化

如果当前选择 L ~R区间

sum[R]-sum[L-1]==0 则是A字符代替
2.sum[R]-sum[L-1]==R-L+1 则是A字符代替

Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <cctype>         //头文件
#define maX(a,b) (a>b?a:b)
#define miN(a,b) (a<b?a:b)
#define LL long long      //宏定义
#define N 2000010         //最大数据范围
using namespace std;
inline int read()
{
    register int x=0;
    register bool f=0;
    register char ch=getchar();
    while(!isdigit(ch))
    {
        f^=!(ch^'-');
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=(x+(x<<2)<<1)+(ch^'0');
        ch=getchar();
    }
    return f?-x:x;
}                                  //读入优化
inline void print(int x)
{
    register int sc[30]={0},tot=0;
    do
    {
        sc[++tot]=x%10;
        x/=10;
    }while(x);
    while(tot)
        putchar('0'+sc[tot--]);
}                                                                      //输出优化
int sum[N];              //前缀和优化:当前到了第i位1~i有多少个1
char tmp;                //临时字符输入
int tot;                 //记录字符串长度
inline void find(int l,int r)
{
    if(sum[r]-sum[l-1]==0)   //判断转化条件1
    {
        putchar('A');
        return ;
    }
    if(sum[r]-sum[l-1]==r-l+1) //判断转化条件2
    {
        putchar('B');
        return ;
    }
    putchar('C');             //转化条件3
    int mid=(r+l)>>1;         //递归二分之一边界
    find(l,mid);              //前1/2
    find(mid+1,r);            //后1/2
}
int main()
{
    while(1)
    {   
        tmp=getchar();                    //输入0 1
        if(tmp!='1'&&tmp!='0')            //判断输入结束
            break;                            
        sum[++tot]=sum[tot-1]+tmp-'0';    //前缀和转化
    }
    find(1,tot);                          //递归区间
    puts("");
    return 0;
}
```

---

## 作者：瓜皮少年 (赞：0)

解题思路：

题目里要求已经讲得很明白了，很显然，这道题用递归做最合适。

根据 这3条指示很容易写出判断条件。

1．  当S为空子串时退出返回

2．  当S串全是0时，退出返回‘A’

3．  当S串全是1时，退出返回‘B’

4．将S串分成两部分，继续递归，并加C。



```pascal
var

  s:ansistring;

function asd(s:ansistring):ansistring;

var

  i,len,max0,max1:longint;

  s1,s2:ansistring;

begin

  if s='' then exit;

  len:=length(s);

  max0:=0;s1:='';

  max1:=0;s2:='';

  for i:=1 to len do

  if s[i]='0' then inc(max0)

              else inc(max1);

  if max0=len then exit('A');

  if max1=len then exit('B');

  for i:=1 to len div 2 do

  begin

  s1:=s1+s[i];s2:=s2+s[i+(len div 2)];

  end;

  asd:='C'+asd(s1)+asd(s2);

end;

begin

  readln(s);

  s:=asd(s);

  writeln(s);

end.
```

---

## 作者：pascalfans (赞：0)

![](https://cdn.luogu.com.cn/upload/pic/1679.png)

**否则把s串分成两个等长的字串s1和s2**
这明显是**递归**！

于是乎，我们来看代码：
```cpp
var
 s,b:^ansistring;//指针
 a:ansistring;
procedure select(s:ansistring);//递归
begin
 if pos('1',s)=0then begin//如果该子串中没有1
                      b^:=b^+'A';//把A加入存储单元
                      exit;//返回上一级
                     end
                else if pos('0',s)=0then begin//如果该子串中没有0
                                          b^:=b^+'B';//把B加入存储单元
                                          exit;//返回上一级
                                         end
                else b^:=b^+'C';//都没有，把C加入存储单元
 select(copy(s,1,length(s)div 2));//检查前一半
 select(copy(s,length(s)div 2+1,length(s)div 2));//检查后一半(一定要加+1!否则稻花香里说丰年)
end;
begin
 new(s);
 new(b);
 readln(s^);
 a:=s^;
 select(a);
 writeln(b^);
 dispose(b);
 dispose(s);
end.
```
顺便科普一下指针。

声明一个指针：在var界面像声明普通变量一样，只是要在类型前加^就行了

指针的使用：new声明储存单元，dispose释放掉

读入、输出:同普通变量，只是要在后面加^

---

## 作者：_Qer (赞：0)

看了几位大佬的题解，好像还没有把基因和长度传入函数来解决的吧

~~来钻个空子交题解~~

~~递归啊，要不然怎样~~

递归过程其实不算重点吧

就是用string存基因

每次先判断是否满足A或B的条件

如果可以就直接输出A或B然后直接return

否则输出C并且把基因分成两半继续递归

判断是A或B或C的地方（check函数部分）可以有很多方法

这里选择用累加

因为每个位只有0和1两种

若满足A（返回1）则和应该为0

满足B（返回2）则和应该为该基因序列的长度

否则为C（返回3）
```cpp
#include<string>
#include<cstring>
//以上两个是用string和.length()的必要头文件
#include<iostream>
#include<algorithm>
using namespace std;
string str;//基因序列
int check(string s,int l){
//判断s里面（长度l）的类型
    int sum=0;
    //当前区间所有数的和，等于l就是全1，等于0就是全0，否则都有
    for(int i=0;i<l;++i){
        sum+=s[i]-'0';//加上每个数字
    }
    if(sum==0){
        return 1;
    }else if(sum==l){
        return 2;
    }else{
        return 3;
    }
}
void f(string s,int l){
//主要递归函数，s为当前基因，l为长度
    int t=check(s,l);//用一个数存结果，不用调用很多次
    if(t==1){
        cout<<"A";
    }else if(t==2){
        cout<<"B";
    }else{
        string a(s,0,l/2);//基因的前半段给a
        string b(s,l/2,l);//后半段给b
        cout<<"C";
        f(a,l/2);//递归前半段
        f(b,l/2);//递归后半段
    }
}
int main(){
    cin>>str;
    int l=str.length();
    f(str,l);
    return 0;
}
```

---

## 作者：睡在墙上的猫 (赞：0)

**觉得自己的程序适合新手**

//首先read数组执行第一次的基因分解如果全是0flag=0全是1flag=1不一致flag=2

/如果flag=0说明全是0输出Aflag=1说明全是1输出Bflag=2咋把他分成两段一个s1,s2分别递归在输出一个c

```cpp
//substr取子串的意思s.substr(起始位置,长度)；
#include<bits/stdc++.h>
using namespace std;
void t(string s)
{
    int flag=0;//0表示全是0输出“A”1表示全是1输出“B”2表示不一致为“CT（s1）t(s2)” 
    if (s[0]=='1') flag=1;
    else if (s[0]=='0') flag=0;
    for (int i=1;i<s.size();i++)
    {
        if (s[i]!=s[0]) flag=2;
    }
    if (flag==1) 
    {
        cout<<"B";
    }
    else if (flag==0) cout<<"A";
    else if (flag==2)
    {
        cout<<"C";
        string s1=s.substr(0,s.size()/2);
        string s2=s.substr(s.size()/2,s.size()/2);
        t(s1);
        t(s2);
    } 
}
void read()
{
    string s;
    cin>>s;
    int flag=0;//0表示全是0输出“A”1表示全是1输出“B”2表示不一致为“CT（s1）t(s2)” 
    if (s[0]=='1') flag=1;
    else if (s[0]=='0') flag=0;
    for (int i=1;i<s.size();i++)
    {
        if (s[i]!=s[0]) flag=2;
    }
    if (flag==1) 
    {
        cout<<"B";
    }
    else if (flag==0) cout<<"A";
    else if (flag==2)
    {
        cout<<"C";
        string s1=s.substr(0,s.size()/2);
        string s2=s.substr(s.size()/2,s.size()/2);
        t(s1);
        t(s2);
    } 
}
int main()
{
    read();
    return 0;
}

```

---

## 作者：x_faraway_x (赞：0)

偶然间翻到这题，其实这题和[FBI树](http://www.luogu.org/problem/show?pid=1087)很像（这题更简单一点）

一道很好的入门递归练习题，推荐大家来玩玩~

```cpp
#include <cstdio>
#include <cstring> 
const int N = 1<<10+5; //这题没给数据范围啊貌似，就直接用了FBI树的数据范围，貌似可以过QWQ
char s[N];
void dfs(int b, int e) {
    bool flag = true;
    char c = s[b];
    for(int i = b+1; flag && i <= e; i++) //判断是否为全0或全1
        if(s[i] != s[i-1]) flag = false;
    if(flag) { //如果是全0或全1，按题意输出A或B
        if(s[b] == '0') putchar('A');
        else putchar('B');
    }
    else { //否则输出C
        putchar('C');
        dfs(b, (b+e)/2); //分成等长子串继续递归
        dfs((b+e)/2+1, e); //同上
    }
}
int main() {
    scanf("%s", s+1);
    int n = strlen(s+1);
    dfs(1, n);
}
```

---

## 作者：封禁用户 (赞：0)

解题思路：


题目里要求已经讲得很明白了，很显然，这道题用递归做最合适。


根据 这3条指示很容易写出判断条件。


1．  当S为空子串时退出返回


2．  当S串全是0时，退出返回‘A’


3．  当S串全是1时，退出返回‘B’


4．将S串分成两部分，继续递归，并加C。


 

 

程序：





























```cpp
Program  kitty;
var
  s:ansistring;
function asd(s:ansistring):ansistring;
var
  i,len,max0,max1:longint;
  s1,s2:ansistring;
begin
  if s='' then exit;
  len:=length(s);
  max0:=0;s1:='';
  max1:=0;s2:='';
  for i:=1 to len do
  if s[i]='0' then inc(max0)
              else inc(max1);
  if max0=len then exit('A');
  if max1=len then exit('B');
  for i:=1 to len div 2 do
  begin
  s1:=s1+s[i];s2:=s2+s[i+(len div 2)];
  end;
  asd:='C'+asd(s1)+asd(s2);
end;
begin
  readln(s);
  s:=asd(s);
  writeln(s);
end.
```

---

## 作者：Shiloh (赞：0)


虽然题目没有卡，但不少题解都没有判断输入串是否为空，导致输入为空时会有输出。这里补了一下。
代码本身就很清晰了，每个函数也写了注释。 
也许是题解里最清晰的一篇了。
```cpp
#include <iostream>
#include <string>

void Kitty_gene(std::string ss);       //输出Kitty's Gene
std::string sread(void);               //读入string    
std::string Kitty(std::string s);      //转换Kitty's 01串
std::string Kitty_01(std::string s);   //处理0 & 1都有的情况
bool has_char(std::string s, char ch); //判断string里是否有某个char

int main(void)
{
    Kitty_gene(sread());
    return 0;
}

inline std::string Kitty_01(register std::string s, register int len)
{
    return "C" + Kitty(s.substr(0, len/2)) + Kitty(s.substr(len/2, len/2));
}

inline bool has_char(register std::string s, register char ch)
{
    return s.find(ch) != std::string::npos;
}

inline std::string Kitty(register std::string s)
{
    if(s == "")
    {
        return "";
    }
    else
    {
        if(has_char(s, '0'))
        {
            if(has_char(s, '1'))
            {
                return Kitty_01(s, s.size());
            }
            else
            {
                return "A";
            }
        }
        else
        {
            return "B";
        }
    }    
}

inline std::string sread(void)
{
    register std::string ss;
    std::cin >> ss;
    return ss;
}

inline void Kitty_gene(register std::string ss)
{
    std::cout << Kitty(ss) << std::endl;    
}
```

---

## 作者：Shiloh (赞：0)

代码本身就很清晰了，每个函数也写了注释。
也许是题解里最清晰的一篇了。
```cpp
#include <iostream>
#include <string>

void Kitty_gene(register std::string ss);               //输出Kitty's Gene
std::string sread(void);                                //读入string    
std::string Kitty(register std::string s);              //转换Kitty's 01串
std::string Kitty_01(register std::string s);           //处理0 & 1都有的情况
bool has_char(register std::string s, register char ch);//判断string里是否有某个char

int main(void)
{
    Kitty_gene(sread());
    return 0;
}

inline std::string Kitty_01(register std::string s, register int len)
{
    return "C" + Kitty(s.substr(0, len/2)) + Kitty(s.substr(len/2, len/2));
}

inline bool has_char(register std::string s, register char ch)
{
    return s.find(ch) != std::string::npos;
}

inline std::string Kitty(register std::string s)
{
    if(has_char(s, '0'))
    {
        if(has_char(s, '1'))
        {
           return Kitty_01(s, s.size());
        }
        else
        {
            return "A";
        }
    }
    else
    {
        return "B";
    }
}

inline std::string sread(void)
{
    register std::string ss;
    std::cin >> ss;
    return ss;
}

inline void Kitty_gene(register std::string ss)
{
    std::cout << Kitty(ss) << std::endl;    
}
```

---

