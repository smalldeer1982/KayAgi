# Three Strings

## 题目描述

You are given three strings $ a $ , $ b $ and $ c $ of the same length $ n $ . The strings consist of lowercase English letters only. The $ i $ -th letter of $ a $ is $ a_i $ , the $ i $ -th letter of $ b $ is $ b_i $ , the $ i $ -th letter of $ c $ is $ c_i $ .

For every $ i $ ( $ 1 \leq i \leq n $ ) you must swap (i.e. exchange) $ c_i $ with either $ a_i $ or $ b_i $ . So in total you'll perform exactly $ n $ swap operations, each of them either $ c_i \leftrightarrow a_i $ or $ c_i \leftrightarrow b_i $ ( $ i $ iterates over all integers between $ 1 $ and $ n $ , inclusive).

For example, if $ a $ is "code", $ b $ is "true", and $ c $ is "help", you can make $ c $ equal to "crue" taking the $ 1 $ -st and the $ 4 $ -th letters from $ a $ and the others from $ b $ . In this way $ a $ becomes "hodp" and $ b $ becomes "tele".

Is it possible that after these swaps the string $ a $ becomes exactly the same as the string $ b $ ?

## 说明/提示

In the first test case, it is impossible to do the swaps so that string $ a $ becomes exactly the same as string $ b $ .

In the second test case, you should swap $ c_i $ with $ a_i $ for all possible $ i $ . After the swaps $ a $ becomes "bca", $ b $ becomes "bca" and $ c $ becomes "abc". Here the strings $ a $ and $ b $ are equal.

In the third test case, you should swap $ c_1 $ with $ a_1 $ , $ c_2 $ with $ b_2 $ , $ c_3 $ with $ b_3 $ and $ c_4 $ with $ a_4 $ . Then string $ a $ becomes "baba", string $ b $ becomes "baba" and string $ c $ becomes "abab". Here the strings $ a $ and $ b $ are equal.

In the fourth test case, it is impossible to do the swaps so that string $ a $ becomes exactly the same as string $ b $ .

## 样例 #1

### 输入

```
4
aaa
bbb
ccc
abc
bca
bca
aabb
bbaa
baba
imi
mii
iim```

### 输出

```
NO
YES
YES
NO```

# 题解

## 作者：HsKr (赞：3)

考虑分类讨论：

$1.\quad b_i\ne c_i \&a_i\ne c_i$ 不可以通过交换达成

$2. \quad b_i=c_i\;or\;a_i=c_i$

$\qquad I. \quad a_i=b_i$ 随意交换一个即可

$\qquad II. \quad a_i\ne b_i$ 

$\qquad \qquad \text{(一)、} \quad a_i=c_i$ 交换$b_i \text{与}c_i$

$\qquad \qquad \text{(二)、} \quad b_i=c_i$ 交换$a_i \text{与}c_i$

分析了这么多，应该也会写了，程序看看就好了：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int T;
string a,b,c;
int len;
int main(){
	cin>>T;
	while(T--){
		cin>>a>>b>>c;
		len=a.size();
		for(int i=0;;i++){
			if(a[i]!=c[i] && b[i]!=c[i]){
				cout<<"NO"<<endl;
				break;
			}
			if(i==len-1){
				cout<<"YES"<<endl;
				break;
			}
		}
	}
	return 0;
}
```

$\color{white}\text{当然代码有点奇怪}$

---

## 作者：zplqwq (赞：0)

~~写题解涨rp~~



------------


这题分类讨论一下。

首先考虑什么情况不可以达成:$b_i \neq c_i$且$a_i \neq c_i$ 。

原因很显然，互不相等的话怎样都不可能通过交换得到彼此，比如`aa`，`bb`就不可能通过交换得到`cc` 。

然后就做完了，因为题目要求判断无解的即可。

这里给一个其他情况的构造。

$a_i = b_i$的话随意交换，否则判断$a_i$和$b_i$谁等于$c_i$然后交换剩下两个即可。





---

## 作者：借我昔日热忱 (赞：0)



------------
本题题解分为两个部分:

一个是讲解思路和实现方式.

更有价值的是纠正部分人的坏习惯导致的“样例全过，提交全WA”

------------
一，思路与实现方式

题目要求：t组数据，每组3个字符串，a与b可以跟c相同位置可调换，最后判段调换后a,b是否完全相同。

手动模拟的话可以模拟而得，其实就是从c里面找有没有与a或者b相同的字符。
**如果C同一位置与b相同,就调换当前位置的a；如果C同一位置与a相同,就调换当前位置的b**（ _~~看不明白可以看下面的伪代码~~_ ），即：

```cpp
if(a[i]==c[i]) b[i]=c[i];

if(b[i]==c[i]) a[i]=c[i];
```
~~此段伪代码仅供理解题意~~

实际写代码的时候题目没有要求输出最后调换完的字符串，所以只需要判断当每一个位置都满足以上关系就输出“YES”，只要有一个不满足就输出“NO”。

------------

 
 _看到这，你就可以去自己写写尝试一下了_ 

------------
二，纠正习惯性错误

 _**如果你样例全过，但全一提交全WA了，然后又回来了，那么这篇题解的真正价值可能就实现了（~~虽然也可能不是我这里指出的错误~~）**_ 

当写循环判断的时候可能有些人习惯写从1开始循环到字符串长度末尾，即这种：	**for(int j=1;j<a.size();j++)** ~~这可能是很多人的习惯~~

但是是否有人还记得： _**字符串读入的时候是从0开始读入的**_ ，所以循环时应该从0开始，即：**for(int j=0;j<a.size();j++)**

（比较坑的是这个毒瘤样例没法打掉这个错误，你造的数据也可能默认第一位相同）

------------
然后给出简短的全代码：

```cpp
#include<iostream>
using namespace std;
string a,b,c;int k,t;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>a>>b>>c;
		for(int j=0;j<a.size();j++){
			if(a[j]==c[j]||b[j]==c[j]) continue;//满足条件直接跳过 
			k=1; //一个小标记 ，确认他是没满足条件 
			printf("NO\n");break;
		}
		if(k==0)printf("YES\n");k=0;//确认是否满足所有条件 +重置标记 
	}
}
```
谢谢观看（~~写题解不易，不喜勿喷~~）


---

## 作者：Phoenix_chaser (赞：0)

# 本题核心：判断
本题的题意为必须让ai或bi与ci进行交换，问a是否能等于b

如果我们分析一下再仔细分析一下题目

会发现交换其实 _**只有两种情况**_ 

### 将ai和ci进行交换，其实就是 _看是否ci与bi相等_ 

### 将bi和ci进行交换，其实就是 _看ai与ci是否相等_

如果交换了之后a还是无法等于b的话，那肯定就不能相等了

#### 那如何处理？

在输入的过程中每次输入都进行判断

####  _**看ci和bi是否相等或ai和ci是否相等**_ 

只要满足其中的一个条件，那么就可以往下进行

如果不满足的话那就停止并输出一个“NO”

举例说明：

imi

mii

iim

a1=c1,所以继续进行

b2=c2继续进行

a3!=c3且b3!=c3

输出"NO"

本题的思路就到这里了

代码如下
```cpp
#include<iostream> 
using namespace std;
int n,changdu;
string s1,s2,s3;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	{cin>>s1>>s2>>s3;
	changdu=s1.size();
	for(int j=0;j<changdu;j++)
	{if(s1[j]!=s3[j]&&s2[j]!=s3[j])
	//判断满足条件 
		{cout<<"NO"<<'\n';
		//不满足就输出NO 
		break; 
		}
	if(j==changdu-1) cout<<"YES"<<'\n';}
	//如果都满足就输出YES}
	}

}
```
## 谢谢观看
### THE END

---

## 作者：Strelitzia (赞：0)

#### [题目传送门](https://www.luogu.com.cn/problem/CF1301A)
-----------------

$\ \ \ \ \ $题目我们可以翻译为，从a，b中对应位选出与c相同的一项。

$\ \ \ \ \ $但a，b中任意一个与c的对应位相同就可以了。

$\ \ \ \ \ $从a，b中匹配一个c。

$\ \ \ \ \ $代码如下：

```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
template<typename T>void read(T &x) {
	x = 0;T f = 1;char s = getchar();
	while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
	while(s >= '0' && s <= '9') {x = x * 10 + s - 48;s = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if(x < 0)putchar('-'),x = -x;
	if(x > 9)print(x / 10);
	putchar(x % 10 + '0');
}
int times;
char a[105],b[105],c[105];
int main() {
	read(times);
	while (times --) {
		scanf("%s%s%s",a,b,c);
		bool flag = 1;			//flag是能否匹配
		for (int i = 0 ; a[i] != '\0' ; ++ i) {
			if (a[i] != c[i] && b[i] != c[i]) {			//匹配中...
				flag = 0;
				break;
			}
		}
		puts(flag ? "YES" : "NO");		//输出答案
	}
	return 0;
}
```
$\ \ \ \ \ $Thanks♪(･ω･)ﾉ

---

## 作者：HohleFeuerwerke (赞：0)

#### 前言

第一场 CF，死状极惨。[题目戳这里](https://www.luogu.com.cn/problem/CF1301A)。

#### 正文

给你三个字符串，$a$，$b$，$c$。

问你：能否通过交换 $a$，$b$ 的第 $i$ 位，使得 $a$ 和 $b$ 中有一个和 $c$ 完全一样。

解释样例：

```
abc
bca
bca
```
这个不用换，直接 $b$ 和 $c$ 就是一样的。

```
aabb
bbaa
baba
```
我们考虑使得 $b=c$。由于第一位完全一样，不用换。第二位不一样，考虑交换，与 $a$ 交换后变为 `ba`，前两位一样。看第三位，与 $c$ 不一样，考虑交换。交换后变为 `bab`，前三位一样。第四位一样，不需要交换。

那么我们直接得出显然结论：如果某一位 $a≠c$ 且 $b≠c$ 那么直接判`false`，否则就能够成功。

如果某一位 $a≠c$ 且 $b≠c$ 那么自然，即使交换了也不能和 $c$ 一样，自然`false`。

如果某一位 $a=c$ 或 $b=c$ 那么我们显然能够通过交换使得这一位与 $c$ 相同。但是这是不能冲动的直接输出，因为我们还需要考虑其他位置是否满足这个条件。

贴代码：

```cpp
#include<bits/stdc++.h>
#define HohleFeuerwerke using namespace std
HohleFeuerwerke;
int n;
bool check(string a,string b,string c){
	for(int i=0;i<a.size();i++)
		if(a[i]!=c[i]&&b[i]!=c[i]) return false;
	return true;
}
//判断每一组数据是否能够满足条件。
int main()
{
	ios::sync_with_stdio(false);
	cout.tie(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		string a,b,c;
		cin>>a>>b>>c;
		if(check(a,b,c)) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
}
```

---

## 作者：123456zmy (赞：0)

题意：  
给你三个长度相同的字符串 $a$ $b$ $c$ 对于第 $i$ 位，必须将 $c_i$ 与 $a_i$ 或 $b_i$ 交换。问是否能交换后使 $a$ 与 $b$ 完全相同。
___
只要 $c_i$ 与 $a_i$ 或 $b_i$ 中的至少一个相同，就可以将 $c_i$ 另一个交换。如果有任意一位不符合上述条件就不合法，否则合法。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b,c;
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		cin>>a>>b>>c;
		bool ok=1;
		for(int i=0;i<a.size();i++)if(c[i]!=a[i]&&c[i]!=b[i])
		{
			puts("NO");
			ok=0;
			break;
		}
		if(ok)puts("YES");
	}
	return 0;
}
```

---

## 作者：违规用户名gAGt8$%z (赞：0)

## 思路
若 $a_{i}=b_{i}$ 就可随意交换，否则判断 $a_{i}$ 和 $b_{i}$ 谁等于 $c_{i}$ 然后交换剩下两个即可。
## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
string a,b,c;
int main()
{
    scanf("%d",&T);
    while(T--) {//T组数据
        cin>>a>>b>>c;
        bool flag=false;
        for(int i=0; i<a.size(); i++){
            if(a[i]==c[i] || b[i]==c[i]) continue;
            else{//如果不符合，直接退出
                flag=true;
                break;
            }
        }
        if(flag) printf("NO\n");//提前退出循环一定不符合，输出no
        else printf("YES\n");
    }
    return 0;
}
```


---

