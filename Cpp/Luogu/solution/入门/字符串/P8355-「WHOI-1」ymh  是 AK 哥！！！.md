# 「WHOI-1」ymh  是 AK 哥！！！

## 题目背景

$2077$ 年春。$15$ 岁的 miku 正在对着你谷发呆，突然看到一个奇怪的问题，你能帮帮他么？？

----

你要先学会一些定义。


我们约定一个字符串下标从 $1$ 开始，$s[l,r]$ 表示 $s_ls_{l+1}\dots s_r$ 拼接成的一个字符串。

---

定义括号匹配串如下：

- 空串是括号匹配串。
- 如果 $A$ 是括号匹配串，则 $(A)$ 是括号匹配串。
- 如果 $A,B$ 是括号匹配串，则 $AB$ 是括号匹配串。

---

括号匹配前缀长度是指最大的 $k$ 使得 $s[1,k]$ 是一个括号匹配串。

比如：
- $s=\text{(())(()}$ 时括号匹配前缀长度是 $4$。
- $s=\text{()()()(()))(}$ 时括号匹配前缀长度是 $10$。

## 题目描述

给你一个括号串 $s$。定义一次操作是交换他们当中相邻的两个字符。

你的任务是找出若干次操作后 $s$ 的括号匹配前缀长度最大值。


## 说明/提示



**本题采用 $\texttt{Subtask}$ 计分方式，只有通过该 $\texttt{Subtask}$ 的所有测试点才能得到该点的分数。**

| $\texttt{Subtask}$ 编号 | 特殊限制 | 分值 |
| :----------: | :----------: | :----------: |
| 1 | 只含左括号或只含右括号 | 2 |
| 2 | $n \leq 2$ | 3 |
| 3 | $n \leq 10$ | 10 |
| 4 | $n \leq 1000$ | 20 |
| 5 | 无| 65 |

对于 $100\%$ 的数据，保证 $ 1\leq n\leq10^6$。

## 样例 #1

### 输入

```
3
(()```

### 输出

```
2```

## 样例 #2

### 输入

```
2
()```

### 输出

```
2```

# 题解

## 作者：BYWYR (赞：12)

打开洛谷比赛仅剩 $10min$，切掉了 $A$ 题。

## Solution 

定义括号匹配串说白了就是 一个左括号和一个右括号匹配起来，构成了一个匹配串。

因为题目并没有限制可以交换括号多少次，所以容易看出 此题只用寻找有几对左括号和右括号可以匹配起来，就可以得出答案。

注意：题目要求的是**匹配串的长度**，而不是有几个匹配串。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
string s;
int len,l,r;
int main(){
	cin>>len;
	cin>>s;
	for(int i=0;i<len;i++){
		if(s[i]=='(') l++;//左括号
		else if(s[i]==')') r++;	//右括号
	}
	cout<<min(l,r)*2;//左括号个数和右括号个数中较小的个数就是匹配串的个数，一个串有2个括号
	return 0;
}
```


---

## 作者：喵仔牛奶 (赞：4)

由于可以调整任意次数，序列的前后是无关紧要的。我们只需要关注左括号与右括号最多能匹配多少就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;
char ch;
int n, lans, rans;
inline int read() {
	char ch = getchar();
	int x = 0, f = 1;
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while ('0' <= ch && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
inline void write(int x) {
	if (x < 0) {
		x = ~(x - 1);
		putchar('-');
	}
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
int main() {
	n = read();
	while (~(ch = getchar())) {
		if (ch == '(') ++ lans;
		if (ch == ')') ++ rans;
	}
	write(lans < rans ? lans << 1 : rans << 1);
	return 0;
}
```


---

## 作者：快斗游鹿 (赞：3)

## 思路

因为可以任意交换相邻的两个字符，所以这道题的关键在于左括号与右括号的数量。

如下图所示，这是当原始括号序列为 $\texttt{)()}$ 时的两种操作。这充分证明了上述结论。所以我们只需要统计左括号和右括号的数量，再取其中最小的乘上 $2$，就得到了问题的答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/hqqn2pw0.png)

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,ans;
string s; 
int main(){
	scanf("%d",&n);
	cin>>s;
	for(int i=0;i<s.length();i++){
		if(s[i]=='(')ans++;//只需统计左括号数量就可得出右括号数量
	}
	int len=s.length(); 
	printf("%d",min(ans,len-ans)*2);//判断 & 输出
	return 0;
}

```


---

## 作者：KAqwq (赞：3)

# P8355
拿到题一看，这不就是到括号匹配吗，然后立马写完交上去，2pts...

# 正解	
想了想，发现这其实就是一道交换括号的题，正解应该是栈。当存在 $s_i$ 为左括号，$s_{i-1}$ 为右括号或 $s_i$ 为右括号，$s_{i-1}$ 为左括号时，将匹配数量 $+2$ 并出栈；否则，将当前的字符入栈。

# 注意
由于```#include<stack>```并不存在遍历栈的操作，所以我选择了好久不用的手打栈。

# Code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int s=0,w=1;
    char ch=getchar();
    while(ch<='0'||ch>'9'){
        if (ch=='-') w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
int n,m;
int ans,top,i;
const int MAXN=1e7+15;
char s[MAXN],a[MAXN];
signed main(){
	n=read();
	scanf("%s",&s);
	for(int i=0;i<n;i++){
		if(!top) a[++top]=s[i];
		else{
			if(s[i]=='('){
				if(a[top]==')') ans+=2,top--;
				else a[++top]=s[i];
			}
			else if(s[i]==')'){
				if(a[top]=='(') ans+=2,top--;
				else a[++top]=s[i];
			}
		}
	}
	printf("%lld",ans);
	return 0;
}


```
### ——The End

---

## 作者：封禁用户 (赞：2)

因为本题说每次交换相邻两个括号，所以每个括号都可以到 6872 想让它到的位置，所以可以直接统计两种括号的个数然后输出最小的即可。

推荐大家去做下 AT4627，这两者是差不多的，因为他们的字符串操作是完全独立的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    string t;
    cin>>n>>t;
    
    int l=0,r=0;
    for(int i=0;i<t.size();i++){
        if(t[i]=='(')l++; // 左
        else r++; // 右
    }
    cout<<min(l,r)*2<<endl; // 记得×2，括号是匹配的！
    return 0;
}
```

---

## 作者：Sternenlicht (赞：1)

思路：

设字符串 $s$ 中左括号出现 $x$ 次，右括号出现 $y$ 次。经过若干次操作后，肯定能把左括号和右括号两两配对，$\min(x,y)$ 即为能配对的括号的个数。题目要求计算长度，就将 $\min(x,y) \times 2$ 即为答案。

```cpp
#include <bits/stdc++.h>
using namespace std;

string s;int n;
int main(){
	cin>>n>>s;
	int lft=0,rgt=0;//lft为左括号个数，rgt为右括号个数
	for (int i=0;i<s.size();i++)
		if (s[i]=='(')
			lft++;
		else
			rgt++;
	cout<<min(lft,rgt)*2<<endl;
	return 0;
}

---

## 作者：Kaenbyou_Rin (赞：0)

这道题读懂题目就好了。



------------

题目中的原序列不要紧（题目说了可以变换，而且不限次数），所以我们只需要统计左括号和右括号的个数，取最小值并乘上 $2$ 即可。

因为调换后，假设一个括号有与之相匹配的另一个括号，那他们总能对 $ans$ 贡献两个长度。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int a,b,n;
int main(){
	cin>>n;
	cin>>s;
	for(register int i=0;i<n;i++){
		if(s[i]=='(') a++;
		else b++;
	}
	printf("%d\n",min(a,b)*2);
}
```


---

## 作者：songhx (赞：0)

不难看出，若干次操作后可以将括号串随意排序。

那么就可以形成诸如 $()()()()……$ 的括号匹配前缀，只要让后面只含有一类括号（或没有括号）即可。

设有 $l$ 个左括号， $r$ 个右括号，最后该串的长度为 $\text{min}(l,r)*2$ 。

代码：

```cpp
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char *argv[]) {
	int n,l = 0,r = 0;
	string str;
	cin >> n >> str;
	for(int i = 0; i < n; i++){
		if(str[i] == '(') l++;
		else r++;
	}
	cout << min(l,r) * 2;
	return 0;
}
```


---

## 作者：lelml (赞：0)

## 解法

这道题中，由于不限制交换次数，我们只需要判断字符串的组成。只要前后括号各有一个，我们就可以将其凑成一对。因此，把所有可以组成的括号对放在前面即可，个数即为 $\min(a,b)$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int x;
    cin>>x;
    int m=0,n=0;
    char a;
    for(int i=0;i<x;i++){
        cin>>a;
        if(a=='(') m++;
        else if(a==')') n++;
    }
    cout<<min(m,n)*2<<endl;
}
```


---

## 作者：Awhale_tauntingcat (赞：0)

#### 题意分析

~~本题只是看起来很吓人~~

通过读题，我们可以发现：只要将所有括号一一匹配，然后将多余的括号移动到后面，可匹配的括号数量即为答案。

例如： ```(()()((``` 可以通过匹配括号变成 ```()()(((``` 此时 $k$ 值即为4

#### 源代码

如下：

```cpp
#include<iostream>
#include<cmath>
/*#define c cin
#define itn int
#define mian main*/ //这里是本人防止手滑的东西
using namespace std;
char a[1000005];
int main(){
    int n,sum1=0,sum2=0;
    cin>>n>>a;
    for(int i=0;i<n;i++){
	if(a[i]==')') 
	sum1++; 
	else sum2++;
	}
    cout<<min(sum1,sum2)*2<<endl;
    return 0;
}
```

---

## 作者：iiiiiiiiiiiiiiiiiii (赞：0)

## 15pts

枚举 $s$ 的所有排列，计算它们的匹配前缀长度，取最大值，时间复杂度 $O(n!)$。

## 100pts

因为可以交换无限次，所以可以将括号成对匹配，匹配数乘 $2$ 就是答案。匹配数就是左括号数量和右括号数量的最小值。时间复杂度 $O(n)$。

## 代码

```cpp
int n,len,a,b;
string s;
signed main()
{
	n=read(),cin>>s,len=s.size();
	for(int i=0;i<len;i++)
	{
		if(s[i]=='(')
			a++;
		else
			b++;
	}
	printf("%d",min(a,b)*2);
	return 0;
}

```


---

