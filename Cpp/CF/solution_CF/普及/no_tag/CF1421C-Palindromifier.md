# Palindromifier

## 题目描述

Ringo found a string $ s $ of length $ n $ in his [yellow submarine](https://www.youtube.com/watch?v=m2uTFF_3MaA). The string contains only lowercase letters from the English alphabet. As Ringo and his friends love palindromes, he would like to turn the string $ s $ into a palindrome by applying two types of operations to the string.

The first operation allows him to choose $ i $ ( $ 2 \le i \le n-1 $ ) and to append the substring $ s_2s_3 \ldots s_i $ ( $ i - 1 $ characters) reversed to the front of $ s $ .

The second operation allows him to choose $ i $ ( $ 2 \le i \le n-1 $ ) and to append the substring $ s_i s_{i + 1}\ldots s_{n - 1} $ ( $ n - i $ characters) reversed to the end of $ s $ .

Note that characters in the string in this problem are indexed from $ 1 $ .

For example suppose $ s= $ abcdef. If he performs the first operation with $ i=3 $ then he appends cb to the front of $ s $ and the result will be cbabcdef. Performing the second operation on the resulted string with $ i=5 $ will yield cbabcdefedc.

Your task is to help Ringo make the entire string a palindrome by applying any of the two operations (in total) at most $ 30 $ times. The length of the resulting palindrome must not exceed $ 10^6 $

It is guaranteed that under these constraints there always is a solution. Also note you do not have to minimize neither the number of operations applied, nor the length of the resulting string, but they have to fit into the constraints.

## 说明/提示

For the first example the following operations are performed:

abac $ \to $ abacab $ \to $ abacaba

The second sample performs the following operations: acccc $ \to $ cccacccc $ \to $ ccccacccc

The third example is already a palindrome so no operations are required.

## 样例 #1

### 输入

```
abac```

### 输出

```
2
R 2
R 5```

## 样例 #2

### 输入

```
acccc```

### 输出

```
2
L 4
L 2```

## 样例 #3

### 输入

```
hannah```

### 输出

```
0```

# 题解

## 作者：SSerxhs (赞：9)

设原串为 $Tcd$ （$cd$ 是最后两位）

$Tcd\rightarrow Tcdc\rightarrow dcT'Tcdc\rightarrow cdcT'Tcdc$

```
#include <stdio.h>
#include <string.h>
char c[100002];int n;int main(){scanf("%s",c);n=strlen(c);printf("3\nR %d\nL %d\nL 2",n-1,n);}
```

---

## 作者：瞬间。。 (赞：4)

还是一道构造题，我直接给出构造方法吧，显然这是有一个通解的，那我现在给你们说一下规律，~~别问我怎么推的~~\
如果是一个abcdef
我现在把 b 提前变成 **b**abcdef\
然后我在把 abcde 滞后 **b**abcdef**dcba**\
然后我发现现在只缺一个 b 就可以回文\
我就可以再从后面拿出一个 b 
变成 babcdefedcbab

我发现只要进行\
L 2\
R 2\
R len-1\
就结束了

```cpp
#include<bits/stdc++.h>
using namespace std;

string s;

int main()
{
	cin>>s;
	int len=s.size();
	cout<<3<<endl;
	cout<<"L "<<2<<endl;
	cout<<"R "<<2<<endl;
	cout<<"R "<<2*len-1<<endl;
	
}
```
完结撒花


---

## 作者：vectorwyx (赞：2)

最理想的情况是所给字符串的第一个字符与第三个字符相同，这样我们先执行 $R,2$，再执行 $R,len-1$ 就能使得它成为回文串。

也就是说，我们先使它的后 $len-1$ 个字符组成的子串是回文串（这里的 $len$ 均指经过一次操作后得到的字符串的长度），再利用它第一个字符与第三个字符相同的性质把第一个字符“补”到最后面。（这其实就是样例1的做法）

但是，如果所给字符串不满足第一个字符与第三个字符相同的性质呢？正所谓“没有条件就要创造条件”，我们可以执行一次 $L,2$ 操作，把第二个字符放到最前面，这样我们得到的字符串的第一个字符与第三个字符就相同了。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

int main(){
	string s;
	cin>>s;
	int n=s.size();
	puts("3");
	puts("L 2");
	n++;
	puts("R 2");
	n+=n-2;
	printf("R %d",n-1);
	return 0;
}
```


---

## 作者：vеctorwyx (赞：1)

### 题目大意:

给你一个~~绳子~~(谷歌生草机翻译的)字符串，你需要对它进行一定操作使它变成回文串（字符串下标从1到n）。

一共有两种操作：

- ``L i``选择把子串$s_2,s_3,...s_i$翻转（变成一个形如$s_i,s_{i-1},...s_2$，$2≤i≤n-1$）并反向追加（放到）到字符串最前面（原字符串保持不变）。

- ``R i``选择把子串$s_i,s_{i+1},...s_{n-1}$翻转（翻转方法同上，$2≤i≤n-1$）并追加到字符串最后面（原字符串保持不变）。

输出**任意一种**方案的操作次数和具体方法，采用SPJ。

### 解法：

看样例我们可以~~很轻易地~~得到一个通用方法：

把第二个字符进行第一种操作，得到字符串$s_2,s_1,s_2,...s_n$，长度为$n+1$；

然后把$s_1$到$s_n$进行第二种操作，得到字符串$s_2,s_1,s_2,...s_n,s_{n-1},..s_2,s_1$，长度为$n+(n-2)+1=n*2-1$；

最后把倒数第二个字符进行第二种操作，得到字符串$s_2,s_1,s_2,...s_n,s_{n-1},..s_2,s_1,s_2$，长度为$n*2-1+1=n*2$；

总结一下就是一下3步：

```L 2```

```R 2```

```R n*2-1```

因为是SPJ，~~可以为所欲为~~，只要输出一种可行方法就行，不必最优

所以代码可以很短：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
char a[20001000];
signed main()
{ 
	cin>>a;
	int n=strlen(a);
	cout<<3<<endl<<"L "<<2<<endl<<"R "<<2<<endl<<"R "<<2*n-1;
}
```

---

## 作者：shengyeqi (赞：0)

## 题面

[传送门](https://www.luogu.com.cn/problem/CF1421C)

## 思路

我们可以设一个字符串为 $\text{XYZ}$。

推测一下，可以发现三次操作后就可以达到题目的要求。

1. 通过 $L$ $2$ 操作后可得 $\text{XYZY}$。

2. 通过 $R$ $2$ 操作后可得 $\text{ZYX'XYZY}$。

3. 通过 $R$  $2 \times len - 1$   操作后可得 $\text{YZYX'XYZY}$（$s$ 为输入的字符串，$len$ 为 $s$ 的长度）。
 
完整操作：$\text{XYZ}$ $\to$  $\text{XYZY}$  $\to$ $\text{ZYX'XYZY}$ $\to$ $\text{YZYX'XYZY}$。

由此，就可以推断出，$3$ 次操作即可满足题意。

后续只需把 $3$ 种操作输出即可。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	cin>>s;
	int len=s.size();//方便后续操作
	cout<<3<<endl;//三种操作。
	cout<<"L "<<2<<endl;//分别输出。
	cout<<"R "<<2<<endl;
	cout<<"R "<<2*len-1<<endl;//len为s的长度。
	return 0;
}
```


---

## 作者：Create_Random (赞：0)

[C. Palindromifier](https://codeforces.ml/problemset/problem/1421/C)

看到构造思路与其他dalao不一样就来发一篇题解。

解法：

因为要将一个字符串变为回文串，

所以我们可以找到一组通解使得所有情况都符合题意。

这里给出构造方法，并以字符串 $abc$ 作为示例：

```4```

```L 2 abc -> babc```

```R n babc -> babcb```

```L n+1 babcb -> cbababcb```

```L 2 cbababcb -> bcbababcb```

具体原理就是题目要求不能进行整体翻转，

那我们就尽力创造机会，

将左右两边都向外翻转 $1$ 个，

然后整体翻转后最右边的就来到了最左边，

最后因为最右端还向外翻转了一次就再把第 $2$ 个翻转到左边即可。

（解释可能有些繁琐，故请多读几遍助于理解）

$Code$:
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	cin>>s;
	int n=s.length();
	cout<<4<<endl;
	cout<<"L"<<" "<<2<<endl;
	cout<<"R"<<" "<<n<<endl;
	cout<<"L"<<" "<<n+1<<endl;
	cout<<"L"<<" "<<2<<endl;
    return 0;
}
```


---

## 作者：felixshu (赞：0)

**[我是传送门](https://www.luogu.com.cn/problem/CF1421C)** 

此题中，不难发现一个规律，$3$ 次就可以完成了。

设一个字符串 $\text{ABC}$。

把第二个字符 $\text{B}$ 移动到前部，就变成了 $\text{BABC}$。再把 $\text{AB}$ 滞后就可以得到 $\text{BABCBA}$。

可以发现，这时只要把 $\text{B}$ 放到最后就可以完成。$\text{B}$ 在倒数第二个，只用做 $R$  $len \times 2 -1$。

可以得出规律：不管字符串为任何，都只用 $3$ 步就可以完成。

#### 下面是AC代码
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    cin>>s;
    int len=s.size();
    cout<<3<<endl;
    cout<<"L "<<2<<endl;
    cout<<"R "<<2<<endl;
    cout<<"R "<<2*len-1<<endl;
    return 0;
}
```

---

