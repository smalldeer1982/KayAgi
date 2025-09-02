# 3-palindrome

## 题目描述

题意
给定n，求长度为n的以'a','b'或'c'构成的字符串，使得其中不存在长为3的回文子串（如"abc","abca"均符合，但"aba"不符），并使'c'的个数尽可能少

## 样例 #1

### 输入

```
2
```

### 输出

```
aa
```

## 样例 #2

### 输入

```
3
```

### 输出

```
bba
```

# 题解

## 作者：DovFrcm (赞：3)

## 题目大意
输出一个长度为 $n$ 并只包含字符 $a\ b\ c$ 的字符串,满足该字符串其中不存在长为 $3$ 的回文子串,且 $c$ 字符个数最少
## 题目分析

首先,我们可以看到,题目要求**使**$\mathbf{c}$**的个数尽可能少**

那么怎样才能使$c$的个数最少呢？

我们先手写一遍 $n=2\ n=3\ n=4$ 的输出：

$n=2\ $:

	bb
$n=3\ $:

	bba

$n=4\ $:

	bbaa

我们可以看出,只需要循环输出 $bbaa$ 就满足 ```使其中不存在长为3的回文子串且c的个数最少``` 了

## 题目代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		if(i%4==0||i%4==1){
			cout<<'b';
		}else{
			cout<<'a';
		}
	}
	return 0;
}
```

题目链接: [$\color{red}here$](https://www.luogu.com.cn/problem/solution/CF805B)


---

## 作者：张语诚ZYC (赞：2)

# 这道题应该是思维题
## 思路分析
### 题目描述
构造以```a```,```b```或```c```构成的字符串，使得其中不存在长为3的回文子串（如```abc```,```abca```均符合，但```aba```不符），并使```c```的个数尽可能少。
### 注意：
**使```c```的个数尽可能少，言外之意是我们可以不使用```c```，** ~~因为个数是零~~ **。**
### 主体分析
若要不出现回文字符串，就轮回输出```aa```和```bb```， ~~然后看自己的心情~~  （**实际上是看情况**） 在开头或结尾输出```a```和```b```。
## $\texttt{AC Code}$：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read_int(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			w=-1;
		} 
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';ch=getchar();
	}
	return s*w;
}
int main(){
	int n=read_int();
	int flag=0,time=-1;
	for(;n>0;n-=1){
		if(flag==0){
			printf("a");
			time++;
			if(time%4==1||time%4==0){
				flag=1;
			}
		}else{
			printf("b");
			time++;
			if(time%4==3||time%4==2){
				flag=0;
			}
		}
	}
}
```


---

## 作者：chenpengda (赞：2)

本题做法很多，这边循环输出“aabb”。

先贴代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	while(n>=4)
	{
		cout<<"aabb";
		n-=4;
	}
	if(n==3)cout<<"aab";
	else if(n==2)cout<<"aa";
	else if(n==1)cout<<"a";
   return 0;
}
```

那么，为什么这个代码可以过呢？

比如，输入$15$，会输出$aabbaabbaabbaab$。

其中任意三个字符要么是$aab$要么是$abb$，要么是$bba$要么是$baa$，**其中没有回文子串。**

这道题有一个坑：$c$的个数尽可能少（显然不能有$c$）。

另外的做法包括循环输入除了$c$之外的所有字母，循环输出$ddee$等，不再赘述。

---

## 作者：Cult_style (赞：2)

这道题其实还是很水的，~~我提交了五次就过了~~（~~溜~~

首先题目叫我们要尽量少出现“c”，（~~有三次提交都是因为没看到这句话~~）如果要让“c”最少出现的话，那当然是让“c”不出现，然而我们可以让“c”不出现，轮流输出“aa”，“bb”就行了，但是奇偶性还是得判断，长度是偶数的话直接“aa”“bb”输出就行了，是奇数的话就要看看最后输出“a”还是“b”了，那就在代码里详细说明。

献上代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,cnt=1;
string abc[3]={"aa","bb"};
//像上面说的“aa”，“bb”轮流来
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n/2;i++)
	cout<<abc[(++cnt)%2];
    //这样就是先取cnt的余数来当abc数组的下标
    if(n%2==0) return 0;
    //如果是偶数就已经结束了
    if(n/2%2==1) printf("b");
    //打个比方，如果n是7的话应该输出aabbaab,那最后一个就是b
    else printf("a");
    //同理，如果n=5，应该输出aabba,那最后一个就是a
	
    return 0;
}
```


---

## 作者：Eason_AC (赞：1)

## Content
给定一个整数 $n$，请构造出长度为 $n$ 的仅含 `a`、`b`、`c` 三个字母的字符串，使得其中没有长度为 $3$ 的回文子串，并且 `c` 出现的次数尽可能少。

**数据范围：$1\leqslant n\leqslant 2\times 10^5$。**
## Solution
分析不难发现，我们可以构造出满足题意的字符串，使得 `c` 不会出现在这个字符串中。下面给出我的一种构造方案。

直接循环输出 `abba`，比如说 $n=8$ 时输出 `abbaabba`，$n=9$ 时输出 `abbaabbaa`，这样可以保证不会出现长度为 $3$ 的回文子串并且不会出现 `c`。

下面给出极为简洁的代码。 
## Code
```cpp
const string ans = "abba";

int main() {
	int n = Rint;
	F(int, i, 0, n - 1) putchar(ans[i % 4]);
    return 0;
}
``` 

---

## 作者：zqwzqwzqw (赞：1)

- ### 审题
$\qquad\ $在**没有**长度为$3$回文子串的情况下，把$c$输出得**最少**。

- ### 算法
$\qquad\ \because 1\le n\le 2\times 10^5\quad \therefore\ int\ \  n\ $就可以了。

$\qquad$要使$c$的个数最少，干脆把个数弄成$0$即可。

$\qquad$没有长度为$3$得回文子串，那就一直输出$aabb$即可。

$\qquad\qquad\qquad\qquad \texttt{输入}\qquad\texttt{输出}$

$\qquad\qquad\qquad\qquad n=1\qquad a$

$\qquad\qquad\qquad\qquad n=2\qquad aa$

$\qquad\qquad\qquad\qquad n=3\qquad aab$

$\qquad\qquad\qquad\qquad n=4\qquad aabb$

- ### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main() {
	scanf("%d",&n);
	for(int i=0; i<n; i++)
		if(i%4==0 || i%4==1)
			printf("a");
		else
			printf("b");

	return 0;
}
```

---

## 作者：一只大龙猫 (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF805B)

这是一篇 **Python** 题解，文末也会给出 C 和 C++ 的代码。

这是一道经典的构造题，我们可以尝试先构造一下。

当 $n=1$ 时，我们可以直接输出`a`；

当 $n=2$ 时，输出`ab`就可以了；

当 $n=3$ 时，要注意不能输出`aba`（因为会出现长度为 $3$ 的回文串），所以要输出`abb`；

当 $n=4$ 时，不能输出`abbb`，只能输出`abba`；

当 $n=5$ 时，不能输出`abbab`，只能输出`abbaa`……

不难发现，只要循环输出`abba`，就可以得到正确答案。

以下是代码。

```python
n=int(input())
for i in range(n):
    if i%4==0 or i%4==3:
        print('a',end='')
    else:
        print('b',end='')
```

由于篇幅原因，C 和 C++ 的代码被我放到了[这里](https://www.luogu.com.cn/paste/9nb2q3pl)，有需要的可以点击查看。

注：

由于 $i$ 的初始值为 $0$，所以当 $i \bmod 4=0$ 或 $i \bmod 4=3$ 时输出`a`，其他的时候输出`b`。如果 $i$ 的初始值为 $1$，读者可以自己推算情况。

Python 中的`print()`函数默认输出后换行，可以通过在要输出的东西后面加上`,end=''`来取消换行。

---

## 作者：UperFicial (赞：0)

# 构造入门

### 前言

构造题，逗比题，直接切了。

题目链接：[$\text{Link}$](https://www.luogu.com.cn/problem/CF805B)。

### 题目大意

要求构造一个长度为 $n$ 的并以 `a`，`b`，`c` 三个字符构成字符串 $s$，使得其中不存在任何长度为 $3$ 的回文子串的前提下 `c` 的数量尽量小。

### 题目解析

先从题目的限制入手：

> 不存在任何长度为 $3$ 的回文子串。

也就是说，对于在串 $s$ 中的一个位置 $i(i\ge3)$ 使得 $s_i$ 不等于 $s_{i-2}$。

这就很好办了，我们可以先自己构造一些。

- $n=1$，输出 `a`。

- $n=2$，输出 `aa`。

- $n=3$，我们发现已经不能再输出 `a` 了，而又要使 `c` 的数量尽量少，应输出 `aab`。

- $n=4$，还是不能输出 `a`，还是得输出 `b`，所以应输出 `aabb`。

- $n=5$，又可以输出 `a` 了。

- $\cdots$

我们发现，根本用不着输出 `c`，轮着输出 `aa` 和 `bb` 就好了。

$AC$ 记录：[$\text{Link}$](https://www.luogu.com.cn/record/43109586)

[$code$](https://paste.ubuntu.com/p/xFhqdrFK39/)

时间复杂度：$O(n)$。

空间复杂度：$O(1)$。

$$\texttt{The End.by UF}$$



---

## 作者：happybob (赞：0)

说要‘c’少，c可以一个都没有，水

首先只要顺序输出bbaa就永远不可能有3位的回文，比如：
输入：
```cpp
15
```
输出：
```cpp

bbaabbaabbaabba

```


代码如下：

```cpp
#include <iostream>
#include <cstring>
using namespace std;

string ans = "bbaa";//先把答案打进去

int main()
{
    int n;
    cin >> n;
    for(int i = 0; i <= n - 1; i++)
    {
        cout << ans[i % 4];//注意要%
    }
    cout << endl;//endl好习惯
    return 0;
}
```


---

## 作者：Remake_ (赞：0)

这道题呢，非常之水。

首先，根据题面，不难看出，这是CF中比较经典的spj，一般这种题都不是枚举，而是根据你自定义的一个规则来生成字符串，如果再仔细地看的话，就会发现只使用$a$和$b$就能构成符合条件的串，所以$c$的个数必定为$0$，那么，我们就来看看此题的生成规则。

要清楚，长度为$3$的所有回文串形如（注意是形如，还可以将字母调换）$aba$或者$aaa$，所以呢，我们发现只要其每个连续子串都形为$aab$或$baa$就可以避免回文，所以交替填写$aa$和$bb$即可，此为偶数时的情况，奇数时由于不能与最前面的$aa$连在一起成为$aaa$的回文串，所以填$b$就行了。

附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a;
	cin>>a;
	if(a%2==1) cout<<"b";
	for(int i=1;i<=a/2;i++) i%2==0?cout<<"bb":cout<<"aa";
} 
```


---

## 作者：wangjunze (赞：0)

本~~蒟蒻~~都觉得这题太简单，找到规律，直接构造，子串不回文，只可能是abb，baa，aab或bba（少用c就直接忽略吧，只构造含a,b的字符串）上代码：


------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	string s;
		for(int i=0;i<n;i++)
		{
			if(i%4==1 || i%4==2)//i mod 4，让两个字母连在一起
				s+='a';//这个字母就随你便了
			else
				s+='b';
		}
	cout<<s;
	return 0;
}
``` 
（纯c++）
（本~~蒟蒻~~第一次发题解）






---

## 作者：小闸蟹 (赞：0)

```cpp
// 这一题只要构造一个合适的循环节即可，题中要求'c'的数量尽量小，我们可以尝试完全不使用'c'
// 在草稿纸上多试几遍就能找到属于你的循环节了，不唯一
// 我构造的循环节如下：abba abba abba ...
#include <iostream>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int Length;
    std::cin >> Length;
    for (int i = 0; i < Length; ++i)
    {
        switch (i % 4)
        {
        case 0: case 3:
            std::cout << 'a';
            break;

        case 1: case 2:
            std::cout << 'b';
            break;

        default:
            break;
        }
    }
    std::cout << std::endl;

    return 0;
}
```

---

## 作者：mxy1 (赞：0)

这个没有长为3的回文子串只要字符串中第k位和第k+2位不同，为此只要'a''b'调换即可，这样不会出现'c'，效果就是输出"aabbaabb……"，代码如下

```cpp
#include<iostream>
#include<ctime>
int main()
{
	int count = 0, n;
	char c = 'a';
	std::ios::sync_with_stdio (false);
	std::cin >> n;
	while (n--)
	{
		std::cout << c;
		if (++count == 2)
		{
			c = c == 'a' ? 'b' : 'a';
			count = 0;
		}
	}
	std::cout << '\n'
	          << (double) clock() / CLOCKS_PER_SEC << std::endl;
	return 0;
}
```

---

