# Ebony and Ivory

## 题目描述

Dante is engaged in a fight with "The Savior". Before he can fight it with his sword, he needs to break its shields. He has two guns, Ebony and Ivory, each of them is able to perform any non-negative number of shots.

For every bullet that hits the shield, Ebony deals $ a $ units of damage while Ivory deals $ b $ units of damage. In order to break the shield Dante has to deal exactly $ c $ units of damage. Find out if this is possible.

## 说明/提示

In the second sample, Dante can fire $ 1 $ bullet from Ebony and $ 2 $ from Ivory to deal exactly $ 1·3+2·2=7 $ damage. In the third sample, Dante can fire $ 1 $ bullet from ebony and no bullets from ivory to do $ 1·6+0·11=6 $ damage.

## 样例 #1

### 输入

```
4 6 15
```

### 输出

```
No
```

## 样例 #2

### 输入

```
3 2 7
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
6 11 6
```

### 输出

```
Yes
```

# 题解

## 作者：封禁用户 (赞：3)

最弱鸡的思路：

枚举$x$，判断在符合$a*x+b*y=c$的条件下，$y$是否有正整数解。

$for$循环跑一遍就好惹~

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c;
int main() {
	scanf("%d%d%d",&a,&b,&c);
	for(int i=0; i*a<=c; ++i) {
		int t(c-i*a);
		if(t%b==0) {
			printf("Yes\n");
			return 0;
		}
	}
	printf("No\n");
	return 0;
}
```

- 为什么$i$最小要是$0$？

$CF633A.in$
```cpp
6 11 6
```

$CF633A.out$

```cpp
Yes
```

这组样例$x=1$，$y=0$，说明$x$和$y$可以为$0$。

>PS：注意输出字母的大小写。

---

## 作者：_0x46EDC (赞：1)

[获得更好的阅读体验](https://www.luogu.com.cn/jasonying/cf633a-ebony-and-ivory) [题目传送门](https://www.luogu.com.cn/problem/CF633A)

---
### 题目分析
求二元一次方程是否有整数解，将 $x$ 或 $y$ 遍历一遍判断另一个变量是否是整数即可。

### 知识点
1. 判断 $\dfrac{b}{a}$ 是否为整数

**方法一：**```b/a*a==b```

如果上式为真，则是整数，反之，不是整数。

举例：

$a=3, b=29$

$b/a=6 \implies b/a\times a=28 \neq 29$

所以 $\dfrac{b}{a}$ 不是整数。

好处：在比自己还要蒟的同学面前秀一波

**方法二：**```b%a==0```

最简单粗暴也最为常用的一种，即判断是否整除，如果上式为真，则是整数，反之不是。

好处：比较短小精悍

2. 输出字符串的简洁方法——puts

代码 ```puts("xxx");``` 即可输出字符串 ```xxx``` ，注意只能输出字符串。

### 推导
$ax+by=c$

$\implies ax=c-by$

$\because a \neq 0$ 
	
$\therefore x=\dfrac{c-by}{a}$

$\because x\ge0$

$\therefore c-by\ge0$

$\therefore 0\le y\le\dfrac{c}{b}$

### 代码
```cpp
#include<iostream>
using namespace std;
int a,b,c;
int main(){
    cin>>a>>b>>c;
    for(int i=0;i<=c/b;i++){//在范围内遍历
        if((c-b*i)%a==0){//判断是否为整数解，也可写为(c-b*i)/a*a==c-b*i
            puts("Yes");//有整数解
            return 0;//结束程序
        }
    }
    puts("No");//没有整数解
    return 0;
}
```
### 结语
挑战本题最短代码Orz

---

---

## 作者：Fuko_Ibuki (赞：1)

这是一个枚举题,然而我用这题练了练$exgcd$,还把我宝贵的第$1000$次提交献给它了.  
首先判断$c$是否能够被$gcd(a,b)$整除,否则输出$"No".$  
接下来判是否存在非负整数解.  
用$exgcd$先求出一组解,看看哪一个是负数,然后先把它转化成最小非负整数,再反过来去算另一个,如果另一个也是非负的,就输出$"Yes"$,否则输出$"No"$.然后就A了.
```cpp
#include<bits/stdc++.h> //Ithea Myse Valgulious
namespace chtholly{
typedef long long ll;
#define re0 register int
#define rec register char
#define rel register ll
#define gc getchar
#define pc putchar
#define p32 pc(' ')
#define pl puts("")
/*By Citrus*/
inline int read(){
  int x=0,f=1;char c=gc();
  for (;!isdigit(c);c=gc()) f^=c=='-';
  for (;isdigit(c);c=gc()) x=(x<<3)+(x<<1)+(c^'0');
  return f?x:-x;
  }
template <typename mitsuha>
inline bool read(mitsuha &x){
  x=0;int f=1;char c=gc();
  for (;!isdigit(c)&&~c;c=gc()) f^=c=='-';
  if (!~c) return 0;
  for (;isdigit(c);c=gc()) x=(x<<3)+(x<<1)+(c^'0');
  return x=f?x:-x,1;
  }
template <typename mitsuha>
inline int write(mitsuha x){
  if (!x) return 0&pc(48);
  if (x<0) x=-x,pc('-');
  int bit[20],i,p=0;
  for (;x;x/=10) bit[++p]=x%10;
  for (i=p;i;--i) pc(bit[i]+48);
  return 0;
  }
inline char fuhao(){
  char c=gc();
  for (;isspace(c);c=gc());
  return c;
  }
}using namespace chtholly;
using namespace std;
ll a,b,c,x,y;

ll exgcd(ll a,ll b,ll &x,ll &y){
if (!b) return x=c,y=0,a;
ll gcd=exgcd(b,a%b,y,x);
return y-=a/b*x,gcd;
}

int main(){
read(a),read(b),read(c);
ll gcd=exgcd(a,b,x,y);
if (c%gcd) return puts("No")&0;//判是否存在解.
if (x<0){//判是否存在非负整数解.这是x<0的情况.
  ll nowx=(x%b+b)%b;
  y-=(nowx-x)*a/b;
  puts(y>=0?"Yes":"No");
  }else{//这是其他情况,包括y<0的情况.
  ll nowy=(y%a+a)%a;
  x-=(nowy-y)*b/a;
  puts(x>=0?"Yes":"No");
  }
}
//Thank you for reading!
```

---

## 作者：Soshine_溯闪 (赞：0)

我 **第四次** 传题解。       
这是一道枚举加模拟的题。       
# 整体思路 
1. 枚举 $i$ ，就是题目中的 $x$  。   
2. 枚举 $j$ ，就是题目中的 $y$ 。          
3. 根据给的不定方程开始处理。    

PS:**枚举时注意别忘考虑上0。**           
# 题很水，上程序 
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdio>
#include <queue>
#include <map>
#include <iomanip>
using namespace std;
int a,b,c; 		//定义 
int main(){
	cin>>a>>b>>c;		//输入 
	for(int i=0;i<=c;i++)		//枚举i(相当于题目中的x） 
		for(int j=0;j<=c;j++){		//枚举j（相当于题目中的y） 
			int s1=i*a;		
			int s2=j*b;		//开始计算 
			if(s1+s2==c){		//是否等于 
				cout<<"Yes"<<endl;		//等于 就输出 
				return 0; 		//AC 
			}
		}
	cout<<"No"<<endl;		//没有等于，就输出No
	return 0;		//还是AC 
}

```
题真的很简单，我也没用什么花式解法，编的程序中规中矩，应该很好理解。         
跪求管理员给过。     
也求大家点个赞。    

---

## 作者：KazamiHina (赞：0)

暴力枚举$x$ 算出$y$ 判断$y$ 是不是整数就好啦

$code:$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int a,b,c;

int main(){
	scanf("%d%d%d",&a,&b,&c);
	for(int i=0;i<=10000;i++){//c最大是10000 那就枚举到10000
		int w=c-a*i;
		if(w<0)continue;//判断w是不是负数，如果w是负数，那么w%b就是负数，但是w%b不能是负数，所以就continue
		if(w%b==0){//w%b算出y 如果w能被b整除，那么y就是整数
			printf("Yes");
			return 0;
		}
	}
	printf("No");
	return 0; 
}
```

$qwq$

---

## 作者：Suuon_Kanderu (赞：0)

这个题可以o(n)复杂度的。

思路就是枚举x的值。然后根据x的值求y得值。

∵a * x + b * y = c

∴y=(c - x  * a )/b ;

其实也很简单

```
#include<bits/stdc++.h> 

using namespace std;

int main(){

double y,a,b,c,x;
//这里要注意了，要把他们设为double要不然整数除法会自动
取整；
int z;

cin>>a>>b>>c;

for(int i=0;i<=c;i++)//从零开始循环，因为x>=0;
{    x=i;
	
    y=(c-x*a)/b*1.0;//同解释；
	
    z=int (y);//看一个double和整数的比较可以这样，强
    
    制转换类型；
	
    if( z==y&&a*x+b*y==c&&y>=0 )//y是非负整数>=0;
  
    {cout<<"YES"<<endl;return 0;}
 
}
 cout<<"NO"<<endl;//如果循环结束也不能找到整数解，输出
 NO；
 
return 0;
}  
```

应该很容易理解吧


---

## 作者：laeva (赞：0)

### 这只是道枚举题。。。。。。
我们可以通过枚举每个x与y，如果找到满足 a * x + b * y == c 的解(x,y)输出Yes，如果每个数都不满足，输出No；复杂度$$O(c^{2})$$
#### 会T吗？？？
c的平方最多是1e8，很危险，但也能过，出于保险~~(为了AC率)~~加个小优化（见代码）

## code

```cpp
#include<cstdio>

#define fom(i, a, b) for(int i = a; i <= b; i++)
#define foi(i, a, b) for(int i = a; i >= b; i--)

using namespace std;

int read() {
	int ans = 0;
	char ch = getchar(), last = ' ';
	while (ch<'0' || ch>'9') { last = ch; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { ans = ans * 10 + ch - '0'; ch = getchar(); }
	if (last == '-')ans = -ans;
	return ans;
}

int main()
{
	int a = read(), b = read(), c = read();
	fom(i, 0, c) {
		foi(j, c, 0) {
			if (a * i + b * j < c) break;
            //小优化，因为第二个数是由大到小枚举，如果结果小了，那么后面的一定不满足
			if (a * i + b * j == c) { printf("Yes"); return 0; }
		}
	}
	printf("No");
	return 0;
}
```
~~发篇题解弥补本题零题解的尴尬~~

---

