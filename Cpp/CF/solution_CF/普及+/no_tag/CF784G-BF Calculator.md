# BF Calculator

## 题目描述

在这个问题中，你要写一个可以生成[Brainfuck](https://en.wikipedia.org/wiki/Brainfuck)语言的代码以算出数学表达式值的生成器。

给你一个算术表达式，其中包括数字0~255以及加减号，你需要生成一个可以算出并输出算术表达式结果的Brainfuck代码

我们将用一个绝对标准的Brainfuck编译器来判断你的Brainfuck代码的正误。

- 有30000个位置供你使用。

- 一个位置用无字符8比特的位置储存0~255的整数。

- 不支持输入（即不能出现','请求输入），在本题中也并不需要。

## 说明/提示

你可以在网站[http://assets.codeforces.com/rounds/784/bf.cpp](http://assets.codeforces.com/rounds/784/bf.cpp)下载Brainfuck编译器。我们将用此测试你的Brainfuck代码。
```
（温馨提示（若有需要，酌量增加）
设指针为now=0，内存为arr[]={0}
在第一个样例中
分号#1：将arr[0]设为2后将now设为1
分号#2：将arr[1]设为3后将now设为2
分号#3：将now设为1
在arr[now]!=0时循环，运行分号#4、#5前后的内容
分号#4：将now减1
分号#5：将arr[now]加1后将now加一
分号#5后一个字符：将now[arr]减一
循环三次后退出循环，此时储存仅有arr[0]为非0整数5，now为1
分号#6：将now设为0
分号#6后：将arr[now]加上48后输出arr[now]所代表的字符，即'5'
代码遍历完成，程序结束
```
Translated by @tiger2005

## 样例 #1

### 输入

```
2+3
```

### 输出

```
++&gt;
+++&gt;
&lt;[&lt;+&gt;-]&lt;
++++++++++++++++++++++++++++++++++++++++++++++++.
```

## 样例 #2

### 输入

```
9-7
```

### 输出

```
+++++++++&gt;
+++++++&gt;
&lt;[&lt;-&gt;-]&lt;
++++++++++++++++++++++++++++++++++++++++++++++++.
```

# 题解

## 作者：Catcats (赞：3)

[题目传送门](/problem/CF784G)

## 题面简化

给定一个表达式，输出一个 Brainf**k 程序，使其可以输出表达式之结果。

---
### 前置芝士

BF 本体是一个 char 数组，有一个指针 pt。

用 `+` 可以让 `*pt++`，用 `-` 可以让 `*pt--`；

用 `<` 可以让 `pt--`，用 `>` 可以让 `pt++`。

而 `.` 相当于 `putchar(*pt)`。

如果还不知道什么是 BF，[戳这里](https://baike.baidu.com/item/Brainfuck)；

---

### 第一步
计算表达式。

众所周知，`cin` 可以连符号输入整数。

例如 `2+3-5+6+7-8`，在 `cin` 看来就是 `2 +3 -5 +6 +7 +8`。

而我们知道，$a-b=a+(-b)$，那么可以循环读入数，直接累加。

代码如下：
```cpp
int x,ans=0;
while(cin>>x)ans+=x;
```

### 第二步

对结果处理。

结果在 $0$~$225$ 之间，那么把它拆成 $3$ 位，代码如下：

```cpp
int a=ans/100,b=ans/10%10,c=ans%10;
```

### 第三步

输出 BF 程序。

有了第二步铺垫，应该有个思路——**让 $3$ 位分别对应数组的 $3$ 位，分别用 `.` 输出。**

但是要注意，直接让 `*pt++` 那么多次不够，因为数字与对应的 ASCII 差 $48$，所以要再加 $48$。

一位输出完用 `>` 换一位，记得特判前导 $0$。代码如下：
```cpp
string operator*(string s,int a){// 重载 *，使输出多个相同字符串更方便
    string res="";
    while(a--)res+=s;
    return res;
}
string add="+";
if(ans>99)cout<<add*(a+48)<<".>";
if(ans>9)cout<<add*(b+48)<<".>";
cout<<add*(c+48)<<'.';
```

完整代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
string operator*(string s,int a){// 重载 *，使输出多个相同字符串更方便
    string res="";
    while(a--)res+=s;
    return res;
}
int main(){
    int x,ans=0;
    while(cin>>x)ans+=x;
    string add="+";
    int a=ans/100,b=ans/10%10,c=ans%10;// 分解
    if(ans>99)cout<<add*(a+48)<<".>";
    if(ans>9)cout<<add*(b+48)<<".>";
    cout<<add*(c+48)<<'.';
}
```

---

## 作者：EuphoricStar (赞：3)

## 思路

如果你不知道 Brainf**k 是什么，可以看[这里](https://baike.baidu.com/item/Brainfuck/1152785?fr=aladdin)。

我们可以先计算表达式的值，再输出。

Python 有个函数 `eval()` 可以计算表达式的值并返回，于是我用 Python 求解。

## 代码

```python
for i in str(eval(input())): print('+' * ord(i), end='.>')
```

注解：`ord(x)` 返回字符 `x` 的 ASCII 码，例如 `ord('1')` 的值为 $49$。

---

## 作者：ChinaNB (赞：3)

题意：给你一个表达式，要你输出一个`Brainfuck`程序，使得它能输出表达式的值。

我们来撕烤一下。既然只要输出它的值，我们只要
### $\color{red}\text{直接输出计算结果}$
不就好了吗？那么怎么计算这个表达式呢？

`Python` `eval` 大法好...

附上我的代码：
```
expr = input()
result = eval(expr)
# python 的语法高亮有问题啊，下面的是整除，不是注释！
r1 = result // 100
r2 = result % 100 // 10
r3 = result % 10

def bf(x: int):
    for i in range(0, 48 + x):
        print("+", end="")
    print(".>", end="")

if r1 != 0:
    bf(r1)
if r2 != 0:
    bf(r2)
bf(r3)
```


---

## 作者：rzh123 (赞：1)

# CF784G 题解

这道题就是输入一个**只有加减**的表达式，输出一个 BF 程序，让这个程序输出表达式计算结果。  
可以先计算结果，再输出。  
## Part 1 计算结果
`scanf` 真是个好东西！它可以带符号读入整数。这道题也不区分优先级，直接一边读入一边计算：  

```
int x,s=0;
while(~scanf("%d",&x)){
	s+=x;
}
```  

## Part 2 输出
本题的重点！  

输出时，可以先分离数位，再逐位输出。结果为0与225间的整数，所以不需要用循环，只需要用三个变量分别存储三位，同时转化成 ASCII 码：  

```
int a=s/100+48,
    b=s/10%10+48,
    c=s%10+48;
```  

之后就是输出 BF 程序。

首先，必须知道 BF 的语法。这种语言有一个指针和一个数组，有如下几种命令：  

（表格来自[百度百科](https://baike.baidu.com/item/Brainfuck/1152785)）  

| 字符 | 含义 |  
| :-: | :-: |
| > | 指针加一 |
| < | 指针减一 |
| + | 指针指向的字节的值加一 |
| - | 指针指向的字节的值减一 |
| . | 输出指针指向的单元内容（ASCII码） |
| , | 输入内容到指针指向的单元（ASCII码） |
| \[ | 如果指针指向的单元值为零，向后跳转到对应的\]指令的次一指令处 |
| \] | 如果指针指向的单元值不为零，向前跳转到对应的\[指令的次一指令处 |
  
很多人都只是把 BF 语言当成一个玩笑，很少有深入研究它的，其实它也有很多值得研究的地方。  
输出字符时，为了快，可以直接用 `+` 加 ASCII 码，然后用 `.` 输出。  
输出了一位之后，其他题解都是用 `>` 移到下一位，其实可以只用一个字节的空间输出。  
BF 中有一个有用的东西： `[-]` 。这三个字符表示：如果当前的数值不是零，就一直减。这就可以把一个字节的空间清空，再写入新的字符。  
唯一需要注意的是不能输出前导零。
这一部分的代码：  
```
int a=s/100+48,b=s/10%10+48,c=s%10+48;
puts("[-]");
if(a>48){
	while(a--)putchar('+');
	puts(".[-]");
}
if(a>48||b>48){ 
	while(b--)putchar('+');
	puts(".[-]");
} 
while(c--)putchar('+');
puts(".[-]");
```  
这个做法目前是[最优解](https://www.luogu.com.cn/record/55880647)。

---

## 作者：Argon_Cube (赞：1)

* **【题目链接】**

[Link:CF784G](https://www.luogu.com.cn/problem/CF784G)

* **【解题思路】**

打破$\color{red}\textsf{caijianhong}$的最短解与输出最少解。

其他人都说了，可以直接计算表达式的值并输出。

也就是说，直接输出表达式的值即可。

很显然，不可能用一次输出输出一个大于 $1$ 位的数，所以可以把各个数位分离再分别输出。

这题表达式结果最多 $3$ 位，所以我用的是```if```。

这题便解完了，我是目前的本题次优解。

* **【实现细节】**

这里我必须要说，很多人都没想到```cin```可以读入符号（```scanf```也可以）。

所以这里我是直接读入数字，并把他们累加起来。

$2+3-4+5$会被自动拆成$2+(+3)+(-4)+(+5)$，大大减少了代码量。

同时，输出许多加号可以不用循环，直接用```string```的构造函数构造一个临时```string```对象输出。

* **【代码实现】**

```cpp
#include <iostream>
#include <string>

using namespace std;

int main(int argc,char *argv[],char *envp[])
{
	int tmp,sum=0;
	while(cin>>tmp)
		sum+=tmp;
	if(sum/100)
		cout<<string(sum/100+48,'+')<<".>";
	if(sum/10%10||sum/100)
		cout<<string(sum/10%10+48,'+')<<".>";
	cout<<string(sum%10+48,'+')<<".>";
 	return 0;
}

```

---

## 作者：_caiji_ (赞：1)

首先我们可以不用去写中缀表达式求值，可以参考[P2788](https://www.luogu.com.cn/problem/P2788)，直接把读进来的数字全部加起来。
```cpp
int getval(){
	int ans=0,x;
    while(~scanf("%d",&x)) ans+=x;
    return ans;
}
```


然后，我们可以使用 `++++++[>+++++++<-]>` 这个东西，把变量的值调到 $48$，后面直接对变量的值微调就好了。具体这样微调：
```cpp
int now=0;
void opt(int to){//to是一位整数
	while(now<to) now++,putchar('+');
    while(now>to) now--,putchar('-');
    putchar('.');
}
```


输出数字可以参考快输的写法：
```cpp
void work(int tmp){
	if(tmp>9) work(tmp/10);
    opt(tmp%10);
}
```

然后把这些代码整合起来，就过了：
```cpp
#include <cstdio>
using namespace std;
int getval(){
    int ans=0,x;
    while(~scanf("%d",&x)) ans+=x;
    return ans;
}
int now;
void opt(int to){
    while(now<to) now++,putchar('+');
    while(now>to) now--,putchar('-');
    putchar('.');
}
void work(int tmp){
    if(tmp>9) work(tmp/10);
    opt(tmp%10);
}
int main(){
    printf("++++++[>++++++++<-]>");
    work(getval());
    return 0;
}
```

---

## 作者：CJ_LIU_XC (赞：1)

首先我们需要了解`Brainf**k`这种语言的特点，明白以后就可以~~轻松~~直接输出结果，结束程序。\
对于`Brainf**k`这种语言，我们可以大概了解它的一些基本字符标识：


| 字符 | 含义 |
| :----------: | :----------: |
| `>` | 指针加一 |
| `<` | 指针减一 |
| `+` | 指针指向的字节的值加一 |
| `-` | 指针指向的字节的值减一 |
| `.` | 输出指针指向的单元内容（ASCⅡ码） |
| `,` | 输入内容到指针指向的单元（ASCⅡ码） |
| `[` | 如果指针指向的单元值为零，向后跳转到对应的`]`指令的次一指令处 |
| `]` | 如果指针指向的单元值不为零，向前跳转到对应的`[`指令的次一指令处 |

接下来，我们就可以把它翻译成C++语言，直接输出结果了，上代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define MAXN 1232000
using namespace std;

char st[MAXN];
int op[MAXN], num[12313], cnt = 0;

int calc(int l, int r)
{
    int x = 0;
    for (int i = l; i <= r; i++) x = x * 10 + st[i] - '0';
    return x;
}

void work(int& th, int x)
{
    int to = x + 48;
    while (th > to) th--, printf("-");
    while (th < to) th++, printf("+");
    printf(".\n");
}

int main()
{
    scanf("%s", st + 1); 
    int pre = 0;
    for (int i = 1; st[i]; i++)
    {
        if (st[i] == '+' || st[i] == '-')
        {
            op[++cnt] = (st[i] == '+') ? 1 : 2;
            num[cnt] = calc(pre + 1, i - 1);
            pre = i;
        }
    }
    num[++cnt] = calc(pre + 1, strlen(st + 1));
    int x = num[1];
    for (int i = 1; i < cnt; i++)
    {
        if (op[i] == 1)x = x + num[i + 1];
        else x = x - num[i + 1];
    }
    int th = 0; cnt = 0;
    if (!x)
    {
        work(th, 0);
        return 0;
    }
    while (x)
    {
        num[++cnt] = x % 10; x /= 10;
    }
    for (int i = cnt; i; i--) work(th, num[i]);
    return 0;
}
```


---

## 作者：Erica_N_Contina (赞：0)

## 题目描述

给你一个算术表达式，其中包括数字 $0\sim255$ 以及加减号，你需要生成一个可以算出并输出算术表达式结果的 Brainfuck 代码


## 思路（快速 AC 请看最后）

那么这就很简单了。

假设我们都指针一开始指向 $1$，我们把地址 $1$ 就看成变量 $a$。

为了修改 $a$ 的值，我们需要使用 `+`。$a$ 的值要设置为多少，我们就需要多少个 `+`。在修改完 $a$ 后，我们要让指针指向下一个位置作为我们的 $b$。那么我们就需要一个 `>`。

所以赋值部分的 BF 代码就是（以 $a=5,b=7$ 为例）

```Plain Text
+++++>
+++++++
```


那么我们怎么样实现运算呢？很简单，我们先用 c++ 写一个

```C++
int a,b;
while(b){
  a++;b--;
}
```


这样我们的 BF 代码就很简单了。

```Plain Text
[<+>-]
[<->-]
```


最后我们的指针值在 $b$，但是我们是在 $a$ 上修改的答案，所以输出应该是。注意 BF 中输出是默认作为 char 类型输出的，因此我们需要加上 $48$。

```Plain Text
<
++++++++++++++++++++++++++++++++++++++++++++++++.
```


然后我们通过这种方法模拟即可。

## 快速 AC

我们在 c++ 里计算出答案，然后直接输出即可。即如果答案为 $res$，那么我们逐位输出 $res_i+48$ 个 `+` 后面附加一个 `.`，然后我们在来 $res_i+48$ 个 `-` 让其归零。

## 代码

```Plain Text
#include<bits/stdc++.h>
using namespace std;
int res,f,ans[10],l;

int main(){
	int c;
    while(cin>>c)res+=c;
	if(!res)ans[++l]=0;
	while(res){
		ans[++l]=res%10;
		res/=10;
	}
	
	for(int k=l;k;k--){
		for(int i=1;i<=ans[k]+48;i++){
			cout<<'+';
		}
		cout<<'.';
		for(int i=1;i<=ans[k]+48;i++){
			cout<<'-';
		}
	}
}
```


应该是最优解，内存小于 [rzh123](https://www.luogu.com.cn/user/237530)。



---

## 作者：fjy666 (赞：0)

## 0x01 思路
很显然，直接计算表达式的值再输出就 OK 了。  
但有几个坑点：
- BF 是输出 ASCII 码的，所以你只能**逐位输出**。
- 你在输出每一位是必须给它加上 ``0`` 的 ASCII 码。
- 输出十位时注意判断百位存不存在

## 0x02 代码
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <ctime>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
#define _for(i_,a_,b_) for(int i_ = a_;i_ < b_;++i_)
typedef long long ll;
using namespace std;
const int bufSize = 5050000;
char buf[bufSize];
int read(int l, int r){
    int ans = 0;
    _for(i, l, r)
        ans = ans * 10 + buf[i] - '0';
    return ans;
}
int main(){
#ifdef LOCAL
    clock_t c1 = clock();
#endif
    scanf("%s", buf);
    int n = strlen(buf);
    int r = 0;
    while(isdigit(buf[r]))
        ++r;
    int ans = read(0, r);
    cerr << "ans = " << ans << "\n";
    cerr << "r = " << r << "\n";
    while(r < n){
        char op = buf[r];
        ++r;
        int left = r;
        while(r < n && isdigit(buf[r]))
            ++r;
        int add = read(left, r);
        ans += op == '+' ? add : -add;
    }
    if(ans / 100 > 0){
        _rep(i, 1, ans / 100) putchar('+');
        _rep(i, 1, '0') putchar('+');
        putchar('.');
        putchar('>');
    }
    if(ans / 100 > 0 || ans / 10 % 10 > 0){
        _rep(i, 1, ans / 10 % 10) putchar('+');
        _rep(i, 1, '0') putchar('+');
        putchar('.');
        putchar('>');
    }
    _rep(i, 1, ans % 10) putchar('+');
    _rep(i, 1, '0') putchar('+');
    putchar('.');
    putchar('>');
#ifdef LOCAL
    printf("\nTime used = %ldms\n",clock()-c1);
#endif
    return 0;
}
```

---

