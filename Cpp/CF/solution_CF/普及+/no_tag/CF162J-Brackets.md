# Brackets

## 题目描述

一个由括号组成的序列被称作**平衡的**，当且仅当这个序列可以通过在字符串中加入“+”号或数字 $1$。例如，序列"(())()", "()" 和 "(()(()))"是**平衡的**，但是")(", "(()" 和 "(()))(" 不是平衡的。  

给定一个由左右圆括号组成的字符串，请你判断它是否是**平衡的**。

## 样例 #1

### 输入

```
(()(()))()
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
())()
```

### 输出

```
NO
```

# 题解

## 作者：皓月星辉 (赞：4)

## 题目大意

说白了就是括号匹配（红题）。
## 分析

都做过括号匹配吧，提供两种方法：

- 栈做法
- 非栈做法

### 栈做法

遇到左括号压入栈。

遇到右括号时，如果站内有左括号，则将栈顶弹出，如果栈是空的，则直接输出错。

遍历完整个序列，如果栈是空的，输出对，反之，输出错。

代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
stack<int> st;
int main()
{
  cin>>s;
  int n=s.size();
  for(int i=0;i<n;i++)
  {
    if(s[i]=='(')st.push(1);
    if(s[i]==')')
    {
      if(st.empty())
      {
        cout<<"NO";
        return 0;
      }
      else st.pop();
    }
  }
  if(st.empty())cout<<"YES";
  else cout<<"NO";
  return 0;
}
```
### 非栈做法（一个变量搞定）
我们用一个变量来记录。

遇到左括号就就将变量加一。

遇到右括号，如果变量为零，输出错，反之，就将变量减一。

遍历完整个序列，如果变量为零，输出对，反之，输出错。

代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    cin>>s;
    int a=0,n=s.size();
    for(int i=0;i<n;i++)
    {
        if(s[i]=='(')a++;
        if(s[i]==')')
        {
	    if(a!=0)a--;
	    else
	    {
                cout<<"NO";
                return 0;
            }
        }
    }
    if(a==0)cout<<"YES";
    else cout<<"NO";
    return 0;
}
```
### end
求过。

---

## 作者：lichenzhen (赞：3)

## 题目大意
给出一个由 `(` 或者 `)` 组成的字符串，看一下这个字符串括号是否匹配。

## 题目解法
这道题最好用栈来解决，有点像 P1739。但是这题比 P1739 简单。我们可以不用栈来模拟。

首先定义两个变量为 $ans,cnt$，$ans$ 用来记录左括号出现的次数，$cnt$ 用来记录右括号出现的次数。

之后循环判断，存储 $ans,cnt$。若 $ans<cnt$ 说明有右括号没有匹配就直接输出 `NO` 并 `return 0` 即可。

之后循环结束后，若 $ans \ne cnt$，此时肯定有括号没匹配就输出 `NO`，否则就输出 `YES`。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s; 
int ans,cnt;
int main()
{
	cin>>s;
	int l=s.size();
	for(int i=0;i<l;i++){
		if(s[i]=='(') ans++;
		if(s[i]==')') cnt++;
		if(cnt>ans){
			puts("NO");
			return 0;
		}
	}
	puts(ans!=cnt?"NO":"YES");
}

```


---

## 作者：ChrisWangZi (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF162J)

看到大家都用栈，但这道题可以不用栈。

------------
## 思路
我们用一个 $cnt$ 变量，记录当前位置前还未配对的左括号数量。

输出``No``只有两种情况：

- 出现了一个没有可以配对的左括号的右括号；

- 左括号太多，右括号有的配对不上。

对应的状况也有两种：

- 遍历时 $cnt$ 为小于零的数；

- 循环后，$cnt \ge 1$。

## 代码：
```cpp
#include<iostream>
using namespace std;
int main(){
	string a;
	cin>>a;
	int cnt=0;
	for(int i=0;i<a.length();i++){
		if(a[i]=='('){
			cnt++;
		}
		else{
			if(cnt==0){
				cout<<"NO";
				return 0;
			}
			cnt--;
		}
	}
	if(cnt>0){
		cout<<"NO";
	}
	else{
		cout<<"YES";
	}
	return 0;
}
```

---

## 作者：NaOHqwq (赞：1)

## 题意

有一个由括号组成的字符串，在其中添加 `+` 和 数字 $1$，问其是否为合法表达式。

转换一下问题就是判断一下这个括号串的括号是否匹配，如果匹配就输出 `YES`，否则输出 `NO`。

## 思路

关于括号匹配的问题相似的题目还有 [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)，但是两题的输入还是有差别的。

我们在做括号匹配的时候最先想到的做法应该就是栈，左括号直接入栈，如果是右括号先判断栈是否为空，为空则输出 `NO`，否则弹出对应的左括号。循环结束后再看栈是否为空即可。

这里笔者想到的是最基础的方法，遍历一遍字符串，统计左括号与右括号的出现次数（因为要保证括号匹配需要让两种括号数量相同），如果左括号数量小于右括号，则说明有右括号没有匹配，直接输出 `NO` 即可。

循环结束后，再次比较两种括号出现的次数，如果两个次数不相等就输出 `NO`，相等就输出 `YES`。

思路没有什么特别难的地方，这里就只贴第二种方法的代码了 qwq。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int l, r; //统计括号出现次数
int main(){
	cin >> s;
	int len = s.length();
	for(int i = 0;i < len;i++){ //遍历
		if(s[i] == '('){
			l++; //左括号
		}
		if(s[i] == ')'){
			r++; //右括号
		}
		if(r > l){ //比较
			puts("NO");
			return 0;
		}
	}
	if(l != r){ //最后比较
		puts("NO");
	}else{
		puts("YES");
	}
	return 0;
}
```

---

## 作者：szh_AK_all (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF162J)
这道题就是让我们判断一个字符串的括号是否匹配，那么我们需要循环枚举字符串的每一位，分为两种情况：一、这一位是左括号，可以直接让左括号的计时器加 $1$；二、这一位是右括号，先让右括号的计时器加 $1$，再判断计时器是否比在它之前的左括号的计时器大—如果比它大，那么肯定不匹配，直接输出`NO`，因为顺序是从左往右的。如果不比它大，那么继续循环。全部枚举完后，再判断左括号与右括号的数量是否相等。
## 代码如下
```c
#include<iostream>
#include<string>
using namespace std;
int main()
{
    string s;
    cin>>s;
    int ans=0,tmp=0;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]==')')
        {
            tmp++;
            if(tmp>ans)
            {
                cout<<"NO";
                return 0;
            }
        }
        else
        ans++;
    }
    if(ans==tmp)
    cout<<"YES";
    else
    cout<<"NO";
    return 0;
}
```


---

## 作者：Flying_Eagle (赞：1)

### 题目思路

用一个栈来维护括号序列，如果是左括号就入栈，如果是右括号，先判断一下栈是否为空，如果为空，那么输出 `NO`，否则就删除对应的左括号。

循环结束后看看栈是否为空，如果为空，输出 `YES`，否则输出 `NO`。

### 题目代码

```cpp
#include <bits/stdc++.h>
using namespace std;
stack<char> a;
char s[505];

int main() {
	scanf("%s", s);
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == '(')
			a.push(s[i]);
		else if (s[i] == ')') {
			if (a.empty()) {
				cout << "NO";
				return 0;
			} else
				a.pop();
		}
	}
	if (a.empty())
		cout << "YES";
	else
		cout << "NO";
	return 0;
}
```


---

## 作者：w9095 (赞：1)

[CF162J Brackets](https://www.luogu.com.cn/problem/CF162J)

看到两位用栈匹配括号的大佬，这里提供另一个思路。

对于括号的问题，我们考虑**区间DP**。

设状态 $dp[i][j]$ 表示使区间 $[i,j]$ 内的括号匹配需要添加的括号数量，则转移方程如下：

$1$ ：区间两边括号匹配时，因为最外层不需要匹配，需要添加的括号数量取决于最外层括号内的需要添加的括号数量，也就是 $dp[i+1][j-1]$ 的值。

$$dp[i][j]=\min\{dp[i][j],dp[i+1][j-1]\}$$ 

$2$ ：枚举分割点 $k$ ，把原区间分 $[i,k]$ 和 $[k+1,j]$ 两个区间，然后求和，把使两个子区间需要添加的括号数量合起来，就是总区间需要添加的括号数量。

$$dp[i][j]=\min\{dp[i][j],dp[i][k]+dp[k+1][j])\}$$

最后，如果使整个区间的括号匹配不需要任何括号，也就是说 $dp[0][n-1]=0$ ，那么说明这个序列本来就是匹配的，输出 `YES` ，否则输出 `NO` 。

虽然复杂度是 $O(n^3)$ ，但是由于序列长度最长只有 $100$ ，还是可以做的。

C++版本代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int f[600][600];
char s[600];
int main()
{
    scanf("%s",s);
    int n=strlen(s);
    for(int i=0;i<n;i++)f[i][i]=1;
    for(int l=2;l<=n;l++)
        for(int i=0;i+l-1<n;i++)
            {
                int j=i+l-1;
                f[i][j]=l;
                if((s[i]=='('&&s[j]==')')||(s[i]=='['&&s[j]==']'))f[i][j]=min(f[i][j],f[i+1][j-1]);
                for(int k=i;k<j;k++)
                    f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]); 
            }
    if(!f[0][n-1])printf("YES"); 
    else printf("NO");
    return 0;
}
```


---

## 作者：jijidawang (赞：1)

## 题意简述

> 有一个括号串，在其中添加`+`和 $1$，判断是否能使其成为合法表达式。

## 算法分析

问题转换：

> 判断一个括号串中的括号是否匹配

这个就是~~臭名昭著的~~**括号匹配问题**，是用**栈**来解答的。

我们比如要判断`((()())`是否匹配：

首先我们建立一个括号栈：

![图片.png](https://i.loli.net/2020/03/28/l7myJMXp4bU1ru9.png)

先插入`(`，然后再插入两次，也就是插入三个`(`：

![图片.png](https://i.loli.net/2020/03/28/mdZFKzWq9Y2Sirc.png)

然后发现`)`，然后弹出堆顶：

![图片.png](https://i.loli.net/2020/03/28/XgTUqrBDjhKvJ1G.png)

又遇到`(`，插入：

![图片.png](https://i.loli.net/2020/03/28/mdZFKzWq9Y2Sirc.png)

又遇到两个`(`，弹出两次：

![图片.png](https://i.loli.net/2020/03/28/MlpvkraFZ5bGC4Y.png)

序列遍历完毕，发现栈非空，得出不是合法序列。

而且如果发现`(`且栈顶不是`)`时，可以直接判定不是合法序列。

流程图如下：

![流程图.png](https://i.loli.net/2020/03/28/VGmE7XtDQ21Cy6w.png)

按照这个模拟即可。

设括号序列为 $a$，主要代码如下：

```cpp
bool check(string a)         //传入括号序列
{
	stack<char> s;           //括号栈
    int len=a.length();
    for (int i=0;i<len;i++)  //遍历
    {
    	if (a[i]=='(') s.push('('); //如果发现左括号，入栈
        else if (a[i]=='(')         //如果发现右括号
        {
        	if (s.top()!='(') return false; //如果栈顶不是左括号，直接判定不合法
            s.pop();                        //弹出栈顶
        }
    }
    if (s.empty()) return true;  //栈空了，合法
    return false;                //栈非空，不合法
}
```

Bye~~

---

## 作者：_Winham_ (赞：0)

这一题目，可以多种方法实现，我将会分两个思路去讲解。

----

思路一：

当遇到左括号，我们可以把左括号存进一个容器，当遇到右括号时，我们则可以把容器的一个左括号拿出来。用这种方法实现可以用数组、栈、队列、等等。

因为作者比较喜欢用栈，所以我会用栈去实现。

```cpp
#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
#include<queue>
using namespace std;
#define LL long long
const int N = 1e6+10;
const int INF = 0x3f3f3f3f;
stack<char>q; 
int main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++){
		char x=s[i];
		if(x=='(')q.push(x);
		else{
			if(q.empty()){
				cout<<"NO\n";
				return 0;
			}
			q.pop();
		}
	}
	if(!q.empty())cout<<"NO\n";
	else cout<<"YES\n";
	return 0;
}


```

----

思路二：

由于想让括号拥有对称性，所以左括号与右括号数量必须相等，但我们还得考虑一种情况就是 `(()))(`，不难看出这种情况是不成立的，所以在统计数量中，要加个判断，看看右括号有没有大于左括号的数量。

```cpp
#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
#include<queue>
using namespace std;
#define LL long long
const int N = 1e6+10;
const int INF = 0x3f3f3f3f;
stack<char>q; 
int main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++){
		char x=s[i];
		if(x=='(')q.push(x);
		else{
			if(q.empty()){
				cout<<"NO\n";
				return 0;
			}
			q.pop();
		}
	}
	if(!q.empty())cout<<"NO\n";
	else cout<<"YES\n";
	return 0;
}


```

---

## 作者：czrjx (赞：0)

## 题意

输入一个只包含括号的序列，判断是否能完全匹配。

这题跟 [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739) 是很相似的，只不过这题的输入更加简洁，没有多出来的符号。

## 思路

对于一个**平衡的**括号序列，从左往右搜索的过程中左括号的数量一定是大于右括号的数量的，所以可以用 $m$ 来存储左括号的数量，遇到左括号就 $+1$，$n$ 来存储右括号的数量，遇到右括号就 $+1$，如果在搜索过程中 $m \le n$ 则说明右括号比左括号多，即不平衡。

最后再判断一下左右括号数量，如果不一样，则说明不平衡。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1000];
int main()
{
	int i,l,m=0,n=0;
	scanf("%s",a);
	l=strlen(a);
	for(i=0;i<l;i++)
	{
		if(a[i]=='(')
			m++;
		if(a[i]==')')
			n++;
		if(n>m)
		{
			cout<<"NO";
			return 0;
		}
	}
	if(m!=n)
		cout<<"NO";
	else
		cout<<"YES";
}
```

---

## 作者：Milthm (赞：0)

## CF162J 题解

### 题目大意

给定一个括号序列，求出它是否匹配。

### 题目解法

这题很简单，其实栈都不需要，只需要一个计数器，如果是左括号就加一，如果是右括号就减一，其中中间如果出现负数的情况，或者是到最后计数器不是零，那么就说明不匹配，否则就是匹配的。

### AC代码

（如果代码有问题可以提出）

```cpp
#include<iostream>
using namespace std;
string s;
int cnt;
int main(){
    cin>>s;
    int l=s.size();
    for(int i=0;i<l;i++){
        if(s[i]=='(')cnt++;//左括号
        else{
            cnt--;
            if(cnt<0)return cout<<"NO",0;//如果是负数就跳出
        }
    }
    if(cnt!=0)cout<<"NO";//判断计数器是否为零
    else cout<<"YES";
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

题目传送门：[CF162J Brackets](https://www.luogu.com.cn/problem/CF162J)

**题目意思：** 给你一堆括号，判断里面的括号是否匹配。

**题解：** 用栈来实现，遇到左括号入栈，遇到右括号判断是否合法即可。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
stack <char> s;
char c[256];
int i;
int main(){
    scanf("%s",&c);
    int len=strlen(c);
    while(i<len){
        if(c[i]=='(')s.push(c[i]);
        if(c[i]==')'){
            if(s.empty()){
                printf("NO");
                return 0;
            }
            s.pop();
        }
        i++;
    }
    if(s.empty()==1)printf("YES");
    else printf("NO");
    return 0;
}
```


---

