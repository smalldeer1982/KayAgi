# Regular Bracket Sequence

## 题目描述

A string is called bracket sequence if it does not contain any characters other than "(" and ")". A bracket sequence is called regular if it it is possible to obtain correct arithmetic expression by inserting characters "+" and "1" into this sequence. For example, "", "(())" and "()()" are regular bracket sequences; "))" and ")((" are bracket sequences (but not regular ones), and "(a)" and "(1)+(1)" are not bracket sequences at all.

You have a number of strings; each string is a bracket sequence of length $ 2 $ . So, overall you have $ cnt_1 $ strings "((", $ cnt_2 $ strings "()", $ cnt_3 $ strings ")(" and $ cnt_4 $ strings "))". You want to write all these strings in some order, one after another; after that, you will get a long bracket sequence of length $ 2(cnt_1 + cnt_2 + cnt_3 + cnt_4) $ . You wonder: is it possible to choose some order of the strings you have such that you will get a regular bracket sequence? Note that you may not remove any characters or strings, and you may not add anything either.

## 说明/提示

In the first example it is possible to construct a string "(())()(()((()()()())))", which is a regular bracket sequence.

In the second example it is possible to construct a string "", which is a regular bracket sequence.

## 样例 #1

### 输入

```
3
1
4
3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
0
0
0
0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
1
2
3
4
```

### 输出

```
0
```

# 题解

## 作者：kon_tori (赞：6)

### 题意
有 ``4`` 种字符串：
``((`` ， ``()`` ， ``)(`` ， ``))`` 它们的数量分别为 ``a`` ， ``b`` ， ``c`` ， ``d`` ，判断它们能否组成一个左右匹配的字符串(即每个 ``(`` 的右边都能找到一个对应的 ``)`` ，同时每个 ``)`` 左边都能找到一个对应的 ``(`` )。

### 思路
对题意进行简化后发现， ``()`` 本身就匹配，所以不考虑。

要使字符串能够匹配：
- 1.若不存在 ``)(`` ，则只需满足 ``((`` 的数量等于 ``))`` 的数量(即 ``a=d`` )，字符串就匹配。
- 2.若存在 ``)(`` ，则必须同时存在 ``((`` 和 ``))`` 且 ``((`` 的数量等于 ``))`` 的数量才能匹配(即 ``a=d`` 且 ``a!=0`` 且 ``d!=0`` )。


### 代码实现

$\texttt{code:}$
```cpp
/* light^chaser */
  #include<bits/stdc++.h>
  using namespace std;
  int a,b,c,d;
  int main(){
      cin>>a>>b>>c>>d;
      if( c==0 && a==d ){
          puts("1");
      }//第一种满足的情况
      else if( c!=0 && a!=0 && d!=0 && a==d ){
          puts("1");
      }//第二种满足的情况
      else{
          puts("0");
      }//不满足
      return 0;
  }
```
### 后记
感谢管理员的辛勤付出！

蒟蒻的第$7$篇题解，望通过。



---

## 作者：Fan_Tuan (赞：3)

# 题解CF1132A【Regular Bracket Sequence】



## 思路： 
括号要全部匹配， 那么左括号的数量必须等于右括号的数量，因此cnt1必须等于cnt4才有可能， 而第二种括号"()"的数量是没有影响的， 因为这两个括号已经匹配了， 且第三种括号")("必须要有第一种括号和第四种括号才能做到匹配， 那么这道题就做出来了



------------

## 代码：
```c
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;
int cnt1, cnt2, cnt3, cnt4;
int main() {
	scanf("%d%d%d%d", &cnt1, &cnt2, &cnt3, &cnt4);
	if (cnt1 != cnt4) printf("0\n");
	else {
		if (cnt1 == 0 && cnt3 != 0) printf("0\n");
		else printf("1\n");
	}
	return 0; 
} 
```


---

## 作者：Yizhixiaoyun (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1132A)

## 题目分析

本题我们找到了三种情况：

1. 如果括号要匹配，也就是左括号的数量等于右括号的数量，那么必须是 $a = d$ 。

2. 而对于第二种括号，我们发现本身就是匹配的，所以不用管它。

3. 如果是第三种括号，那么必须有第一个与第四个与其搭配才可以匹配。

## 贴上代码

```cpp
#include<iostream>
using namespace std;
int a,b,c,d;
int main(){
	cin>>a>>b>>c>>d;
	if(a!=d) cout<<"0\n";
	else if(a==0&&c!=0) cout<<"0\n";
	else cout<<"1\n";
}
```

---

## 作者：GusyNight (赞：1)

先读题~~~
```
有4种字符串，

"(("
"()"
")("
"))"

给你每种字符串的数目，求能否组成一个左右括号相匹配的字符串。若能输出1,若不能则输出0。
```
**思路**
```
首先，
"(("和"))"的数量一定要一样!
条件1:n[1]==n[4];
Second,
")("这种不可以出现，不然就为0
条件2:n[3]==0;
但是如果n[1]出现(就是"((")的次数为0那么也不成立
条件3:n[1]>0
```
**代码**
```cpp
#include<bits/stdc++.h>
#define I int
#define L long long
#define C char
#define S string
#define B bool
#define Max 100000009
#define Mid 1000009
#define Sml 10009
#define Lit 109
using namespace std;
inline int read(){
    char c=getchar();
    int x=0;
    bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
int main(){
	int n[Lit];
	for(int i=1;i<=4;i++){
		n[i]=read();
	}
	bool flag=false;
	if(n[1]==n[4]&&n[3]==0&&n[1]>0){
		flag=true;
	}
	if(flag==false){
		puts("0");
	}
	else{
		puts("1");
	}
    return 0;
}
```
**貌似.....**

思路错了
=
```
原来条件3和条件2是只要满足一个就可以了丫~~~
```
**AC代码:**
```cpp
#include<bits/stdc++.h>
#define I int
#define L long long
#define C char
#define S string
#define B bool
#define Max 100000009
#define Mid 1000009
#define Sml 10009
#define Lit 109
using namespace std;
inline int read(){
    char c=getchar();
    int x=0;
    bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
int main(){
	int n[Lit];
	for(int i=1;i<=4;i++){
		n[i]=read();
	}
	bool flag=false;
	if(n[1]==n[4]&&n[3]==0||n[1]>0){
		flag=true;
	}
	if(flag==false){
		puts("0");
	}
	else{
		puts("1");
	}
    return 0;
}
```

---

## 作者：j1ANGFeng (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1132A)

### 题意
有 4 种字符串, `((` , `()` , `)(` 和 `))` ，给你每种字符串的数目，求能否组成一个左右括号相匹配的字符串。若能输出 `1` ,若不能则输出 `0` 。

### 分析
我们规定 $a$ 为 `((` 的数量， $b$ 为 `()` 的数量， $c$ 为 `)(` 的数量， $d$ 为 `))` 的数量

首先 $b$ 可以省略，而 $a$ 和 $d$ 必须相等，而且有 $c$ 必须要有 $a$ 和 $d$ 。

那么符合条件的 $ a , b , c , d $ 有下列两种可能

1 `a==d&&c==0`

2 `c==0&&a==d`

### AC CODE
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<deque>
#define int long long
#define N 10000001
#define inf 2147483647
#define in inline
#define re register
using namespace std;
inline long long rd(){char a=getchar();long long f=1,x=0;while(a<'0'||a>'9'){if(a=='-')f=-1;a=getchar();}while(a>='0'&&a<='9'){x=(x<<3)+(x<<1)+(long(a^48));a=getchar();}return f*x;}in void qwqqwq(long long x){if(x!=0){qwqqwq(x/10);putchar(x%10^48);}return;}inline void wt(long long x){if(x==0){putchar('0');return;}if(x<0){x=-x;putchar('-');}qwqqwq(x);return;}

signed main(){
	int a=rd(),b=rd(),c=rd(),d=rd();
	if(a==d&&a!=0||c==0&&a==d)
	  puts("1");
	else
	  puts("0");
	return 0;
}
```

---

## 作者：wuwenjiong (赞：0)

## 题意：
给出四种字符串的数量，问是否能组成合法的字符串，即左括号和右括号两两相对。

我们来分析一下情况：

1. `()` ，可看出它本身就是左括号和右括号两两相对的，符合题意，可以忽略。
1.，不难发现，只有当它们的数量相等时，才有可能组成合法的字符串。
1. `)(` ， 当此字符串左右两边分别放一个左括号和右括号，例如： `(()())` ，这样就又是合法的了。

所以，我们可以从中得出结论：只有 `)(` 的数量为零，且 `((` 和 `))` 数量相等，或者 `((` 和 `))` 数量相等且不为零的情况是合法的，其它的都是不合法的。

代码实现如下：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int main(){
	int a,b,c,d;
	cin>>a>>b>>c>>d;
	if(c==0&&a==d)
		cout<<1;
	else{
		if(a==d&&a&&d)
			cout<<1;
		else
			cout<<0;
	}
	return 0;
}
```
谢谢！！！

---

## 作者：Chtholly_L (赞：0)

### 题意：

有四种字符串，分别为 `((`、`()`、`)(`、`))`，给出他们的数量，问它们能否组成一个左右括号匹配合法的字符串。

---


### 分析：

`()` 已经是一个合法的字符串了，所以无论它有多少个都没有影响。

由于左括号和右括号必须对应，所以 `((` 和 `))` 的数量必须一样，否则无法组成对应的序列。此时的 `)(` 的数量可以为零。

如果 `)(` 的数量不为零，而 `)(` 无论有多少个都无法自己组成一个合法的序列，因此需要同时有 `((` 和 `))` 来补全左右两边的括号。在这里不用考虑它们的数量问题，因为 `)(` 可以组成只有左右两边有一个单独的括号的序列，因此只要左右两边至少有一个匹配的 `((` 和 `))` 即可。

比如

`)()()()()()(`

只需要在左右两边各加上一个 `((` 和 `))`

`(()()()()()()())` 

就可以组成一个合法的字符串。

---

### 代码：

```cpp
#include<iostream>

using namespace std;

int main(){
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    if(a==d){  //这是大前提，只有满足这一条的才有可能只合法的。
        if(a!=0&&d!=0&&c!=0){  // )( 的数量不为零
            cout<<1;
            return 0;
        }
        else if(c==0){  //若为零，且 (( 和 )) 的数量相等，一定是合法的
            cout<<1;
            return 0;
        }
        else{  //否则不合法
            cout<<0;
            return 0;
        }
    }
    else{  //不满足大前提的不合法
        cout<<0;
        return 0;
    }
}
```


---

## 作者：Zechariah (赞：0)

类型2显然不需要，直接忽略  
如果有类型3，那么一定要有类型1和4  
类型1和4的数量必须相同  
这就是这题的所有条件了...
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x&-x)
#define jh(x, y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7, INF = 0x3f3f3f3f;
using namespace std;
namespace fast_IO {
    inl ll read() {
        rg char c;
        rg ll x = 0;
        rg bool flag = false;
        while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
        if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
        while ((c = getchar()) != ' ' && c != '\n' && c != '\r'&&~c)
            x = (x << 1) + (x << 3) + (c ^ 48);
        if (flag)return -x; return x;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}


int main(void)
{
    rg int a = fast_IO::read(); fast_IO::read();
    rg int b = fast_IO::read(), c = fast_IO::read();
    if (b && (!a || a != c))puts("0");
    else puts(a == c ? "1" : "0");
    return 0;
}

```


---

