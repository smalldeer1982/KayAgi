# The Monster

## 题目描述

As Will is stuck in the Upside Down, he can still communicate with his mom, Joyce, through the Christmas lights (he can turn them on and off with his mind). He can't directly tell his mom where he is, because the monster that took him to the Upside Down will know and relocate him.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF917A/4c119b489e29bab2fd3dc778221019b04c8209ba.png)Thus, he came up with a puzzle to tell his mom his coordinates. His coordinates are the answer to the following problem.

A string consisting only of parentheses ('(' and ')') is called a bracket sequence. Some bracket sequence are called correct bracket sequences. More formally:

- Empty string is a correct bracket sequence.
- if $ s $ is a correct bracket sequence, then $ (s) $ is also a correct bracket sequence.
- if $ s $ and $ t $ are correct bracket sequences, then $ st $ (concatenation of $ s $ and $ t $ ) is also a correct bracket sequence.

A string consisting of parentheses and question marks ('?') is called pretty if and only if there's a way to replace each question mark with either '(' or ')' such that the resulting string is a non-empty correct bracket sequence.

Will gave his mom a string $ s $ consisting of parentheses and question marks (using Morse code through the lights) and his coordinates are the number of pairs of integers $ (l,r) $ such that $ 1<=l<=r<=|s| $ and the string $ s_{l}s_{l+1}...\ s_{r} $ is pretty, where $ s_{i} $ is $ i $ -th character of $ s $ .

Joyce doesn't know anything about bracket sequences, so she asked for your help.

## 说明/提示

For the first sample testcase, the pretty substrings of $ s $ are:

1. "(?" which can be transformed to "()".
2. "?)" which can be transformed to "()".
3. "((?)" which can be transformed to "(())".
4. "(?))" which can be transformed to "(())".

For the second sample testcase, the pretty substrings of $ s $ are:

1. "??" which can be transformed to "()".
2. "()".
3. "??()" which can be transformed to "()()".
4. "?()?" which can be transformed to "(())".
5. "??" which can be transformed to "()".
6. "()??" which can be transformed to "()()".
7. "??()??" which can be transformed to "()()()".

## 样例 #1

### 输入

```
((?))
```

### 输出

```
4
```

## 样例 #2

### 输入

```
??()??
```

### 输出

```
7
```

# 题解

## 作者：SpXace (赞：5)

枚举起点，用tot记录，'(' 为+1，')' 为-1，若 tot == 0，说明找到一组解，则Ans++

若是'?'判断tot是否大于0，表示需要右括号匹配，若大于0，此时使'?'为右括号，由于右括号一定可以改为左括号，因此num++（num为可以修改为右括号的'?'个数）

而若小于此时tot < 0，说明'?'只能为左括号，因此不计入num

如果某一个时刻，tot<0且num>0，说明可以将之前的右括号改为左括号，则tot += 2,并num--

若tot<0 但num为0，说明此序列当前及以后都不会合法，break即可
```
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
char s[5050];
int tot = 0,Ans = 0,num = 0; 
int main()
{
    cin >> s;
    int len = strlen(s);
    for(int i = 0; i < len; ++i)	
    {
        tot = 0; num = 0; 
        for(int j = i; j < len; ++j)
        {
            if(s[j] == '(')  tot++;
            if(s[j] == ')')  tot--;
            if(s[j] == '?')
            {
                if(tot > 0)
                    tot--,num++;
                else
                    tot++;
            } 
            if(tot < 0 && num) tot += 2,num--;
            if(tot < 0 && !num) break; 
            if(tot == 0) Ans++;	
        }	 
    }	 
    cout << Ans;
    return 0;
}
```


---

## 作者：laeva (赞：3)

## 先放结论

一个长度为n的序列s是正确的当且仅当：
```
abs( s\[i](0<=i<=n) 中 ‘)’ 的数量 - s\[i]中 ‘(’ 的数量 ) < s\[i]中 ‘?’ 的数量   并且 n%2 == 0

```
#### 为什么呢？

1. 因为在我们匹配（暂不考虑‘)’在‘(’的情况）的时候，先用‘(’与‘)’匹配，如果有一方剩下，我们使用 ‘?’ 抵消掉他，这样的话s\[i]中 ‘?’ 的数量就要多于s\[i]中 ‘)’、‘(’ 的数量差。

2. 另外，两个符号才能完成匹配，所以 n%2 == 0

#### 那么如何处理‘)’在‘(’前的情况呢？ 
- 我们选择通过正反两次枚举：从前向后枚举‘)’，从后向前枚举‘(’,当当前这个点不满足要求后，就让他后面的所有结果全制为false；

~~解决了，有没有感觉很简单？~~

## code
```cpp
#include<cstdio>
#include<cmath>
#include<cstring>

#define MAXN 5010
#define fom(i, a, b) for(int i = a; i <= b; i++)
#define foi(i, a, b) for(int i = a; i >= b; i--)

using namespace std;

char s[MAXN];
bool f[MAXN][MAXN],g[MAXN][MAXN];

int main(int argc, char const *argv[]) {
	scanf("%s", s);
	int l = strlen(s), ans = 0;   
	fom(i, 0, l - 1) {   
		bool flag = true;
		int cnt = 0, snt = 0;   
		fom(j, i, l - 1) {
			if (s[j] == ')') cnt--;   
			else cnt++;　　
			if (cnt < 0) flag = false;   
			f[i][j] = flag;
		}    
	            　　
	}　　　　　　
	fom(i, 0, l - 1) {
		bool flag = true;
		int cnt = 0, snt = 0; 　　　 
		foi(j, i, 0) {
			if (s[j] == '(') snt--;
			else snt++;
 		    if (snt < 0) flag = false;   
			g[j][i] = flag;  
		}
	}  　　　
	fom(i, 0, l - 1) fom(j, i + 1, l - 1)   
		if (f[i][j] && g[i][j] && (j - i + 1) % 2 == 0) ans++;  
	printf("%d", ans);
	return 0;       　　
}
```
~~（ps:请不要抄题解，除非你觉得中文全角空格很和蔼）~~

---

## 作者：BYWYR (赞：2)

## 题目大意

给定一个由 '(', '?', ')' 三种字符组成的字符串 $s$，长度为 $n$（$2≤n≤5000$），问有多少个合法的子串。一个字符串合法是说，把其中的 '?' 替换成 '(' 或 ')'，能够使得每一个左括号都找到唯一与之对应的右括号。

## 思路

第一反应是可以动态规划判断一个子串 $[l, r]$ 是否合法，合法的字符串满足以下两个条件之一：

-  $s_l,s_r$组成一对括号，并且子串 $[l + 1, r - 1]$ 合法；

-  存在某个 $l < k < r$，使得子串 $[l, k]$ 合法，子串 $[k + 1, r]$ 也合法。

但第二个条件的判断是 $O(n^3)$ 的，输入串长度 $5000$ 的话并不能过。



------------

事实上，一个字符串 $s$（长度为 $n$）合法等价于如下三个条件：

- $2 | n$ ;

- 对于所有 $1 ≤ i ≤ n$：字串 $[1, i]$ 中所有 '(' 的数量 + 所有 '?' 的数量 >= 所有 ')' 的数量 ;

- 对于所有 $1 ≤ i ≤ n$：字串 $[1, i]$ 中所有 ')' 的数量 + 所有 '?' 的数量 >= 所有 '(' 的数量 。

必要性显然，充分性的话如果没有 '?' 的话等于说只要把一个串任意分成左右两半，左边的'('数量不少于 ')' 数量，右边的 ')' 数量不少于 '(' 数量，整个串里他们数量相等。那么这个串就是合法的（可以想象一个栈，左括号就把一个物品压栈，右括号就出栈，这样的条件保证任何时候不会让空栈做出栈操作，并且所有操作完毕后栈为空）。



------------

## Code

~~讲得很清楚了，就不给代码了。~~



---

## 作者：linan04195 (赞：1)

## 思路

把字符串从头到尾遍历一遍，用 $cnt$ 记录左右括号的个数，用 $num$ 记录问号，用 $ans$ 记录解的数量。

- 当遇到左括号时 $cnt+1$ 。
- 遇到右括号时 $cnt-1$ 。

如果遇到了 **问号**：

- 如果 $cnt<0$ 说明需要把问号变成 **左括号** 来匹配，不计入 $num$ 。
- 如果 $cnt>0$ 说明需要把问号变成 **右括号** 来匹配，计入 $num$ 。

在某一时：

- 若 $cnt=0$ 说明是解，让 $ans+1$ 。
- 若 $cnt<0$ 并且 $num>0$ 说明可以把右括号改为左括号，让 $cnt+2$ 且 $num-1$ 。
- 若 $cnt<0$ 并且 $num=0$ 说明不合法，跳出循环。

## Code
```

#include<bits/stdc++.h>
using namespace std;

string s;
int cnt=0,num=0,ans=0;
 
int main(){
	
    cin>>s;
    int len=s.size();
    
    for(int i=0;i<len;i++){ //从头到尾 
    	
        cnt=0,num=0; //初始化 
        for(int j=i;j<len;j++){
        	
            if(s[j]==')') cnt--; //右括号 
            if(s[j]=='(') cnt++; //左括号 
            
            if(s[j]=='?'){
                if(cnt>0) cnt--,num++;
                else cnt++;
            } 
            
            if(cnt==0) ans++; //是解 
            if(cnt<0&&num>0) cnt+=2,num--; //可以替换为左括号 
            if(cnt<0&&num==0) break; //不合法 
        }	 
    }	
	
    cout<<ans; //答案 
    return 0;
}
```

---

## 作者：Zheng_iii (赞：1)

## 思路
分别枚举连续子序列所有起点的可能。

用变量来记录左括号和右括号的数量，左括号 $+1$，右括号 $-1$。

对于问号，则通过当前左括号和右括号的数量来判断应该变为右括号还是变为左括号。

当右括号数量大于左括号数量时，就可以停止枚举以当前起点为起点的连续子序列了，因为无论怎么枚举都是不合法的。

如果当前子序列内的左括号与右括号数量相等，则让答案加一。

## AC 代码

```cpp
#include<bits/stdc++.h>
using ll = long long;
using namespace std;
string s;
int cnt,ans,flag;

int main(){
	// freopen("text.in","r",stdin);
	// freopen("text.out","w",stdout);
	ios::sync_with_stdio(0),cout.tie(0),cin.tie(0);
    cin >> s;
    int n = s.size();
    for(int i = 0; i < n;i++){
        cnt = 0;
        flag = 0; 
        for(int j = i; j < n;j++){
            if(s[j] == '(')cnt++;
            if(s[j] == ')')cnt--;
            if(s[j] == '?'){
                if(cnt > 0)cnt--,flag++;
                else cnt++;
            } 
            if(cnt == 0)ans++;
            else if(cnt < 0){
            	if(flag){
            		cnt += 2;
            		flag--;
            	}else{
            		break; 
            	}
            }
        }	 
    }	 
    cout<<ans;
    return 0;
}
```

---

## 作者：OJ_killer (赞：1)

明显的**括号序列**

根据数据范围长度不大于 $5000$ 的字符串。容易得出用 $O(n^2)$ 的算法计算，即枚举区间。

合法括号序列需要满足每个前缀和大于等于 $0$，且最后前缀和等于 $0$。

当遍历的时候遇到问号，先假设问号是右括号，最后在判断是否需要转变为左括号，详见代码。

$code$
```cpp
#include<bits/stdc++.h>
using namespace std;

string s;//用string字符串

signed main() {
	getline(cin,s);
	int ans = 0;//记得初始化
	for (int i = 0; i < s.size(); i++) {
		int l = 0, x = 0;
		for (int j = i; j < s.size(); j++) {
			if (s[j] == '(')
				l++;
			else if (s[j] == ')')
				l--;
			else
				l--, x++;
			if (l == 0)
				ans++;
			else if (l < 0) {
				if (!x)
					break;//不合法
				else
					l += 2, x--;
			}
		}
	}
	cout << ans;
	return 0;//愉快结束
}

---

## 作者：naroto2022 (赞：1)

# CF917A 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF917A)

### 思路

看了下题目，很简单，直接从开头开始爆搜即可，枚举出一种可能，答案就加一。

问题来了，爆搜的过程呢？

容易想到，可以用一个变量 $sum$ 动态统计当前序列未配对的左括号的数量，对于一个 $s[i](i\in[1,strlen(s)])$ 有如下两种情况：

1. 若 $s[i]$ 为 `(`，则 $sum$ 加一，表示未配对的左括号数加一。
2. 若 $s[i]$ 为 `)`，则 $sum$ 减一，表示未配对的左括号数减一。

如上是正常情况，接下来要考虑特殊情况：如果 $s[i]$ 是 `?` 呢？容易想到，再用一个 $num$ 来统计 `?` 修改成 `)` 的个数，接下来同样的，分成两种情况，讨论 `?` 是换成 `(` 还是 `)`：

1. 若未配对的左括号的数量大于 $0$，即 $sum>0$ 时，则把 `?` 变成 `)` 去和左括号配对。所以是 $sum-1,num+1$。
2. 否则，`?` 变成 `(`，即 $sum+1$。

于是，一个子区间就处理好了，接下来要对这个子区间进行判断，有如下三种情况：

1. $sum<0,num>0$，说明可以把之前的右括号改为左括号，则 $sum+2$，并且 $num-1$。
2. $sum<0,num=0$，则序列违法，无法每对括号都匹配成功。
3. $sum=0$，则这个序列满足条件，$ans+1$。

于是，代码基本就可以出来了。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
char s[5005];
int sum,ans,num,len;
//sum是用来记录未配对的左括号的数量。
//ans为答案。
//num统计‘？’可以修改成‘）’的个数。
//len来统计输入序列的长度。
int main(){
    cin>>s;
    len=strlen(s);//求输入的字符串的长度。
    for(int i=0; i<len; i++){//暴力枚举。
        sum=0,num=0;//初始化。
        for(int j=i; j<len; ++j){
            if(s[j]=='(') sum++;//正常情况：为前括号，未配对的左括号数+1。
            if(s[j]==')') sum--;//正常情况：未配对的左括号数-1。
            if(s[j]=='?'){//特殊情况‘？’，可以为任意符号。
                if(sum>0) sum--,num++;
                else sum++;
            } 
            if(sum<0&&num) sum+=2,num--;//sum<0且num>0，说明可以把之前的右括号改为左括号，则sum+=2,并num--;。
            if(sum<0&&!num) break;//序列违法，无法每对括号配对成功。
            if(sum==0) ans++;//sum等于0则答案就多一种，ans++;。
        }	 
    }	 
    cout<<ans;
    return 0;
}
```

---

## 作者：李至擎 (赞：1)

[点我看题](https://www.luogu.com.cn/problem/CF917A)


看到各位dalao都讲过了写法，那我这个蒟蒻就来补充一下做法的细节与思路。

思路：枚举起点与终点，判断左右括号是否能匹配上（考虑问号存在）。若合法，则统计答案。

方法（以一次枚举为例）：

- $1.$ 从 $1$ 到 $n$ 枚举起点，从起点到 $n$ 枚举终点；

- $2.$ 统计左右括号之差与问号个数；

- $3.$ 根据上一步结果判断是否可行；

- $4.$ 如果可以，就统计答案。

细节：

- $1.$ 若在枚举到一个终点时，此序列已经不合法，说明此序列当前及以后都不会合法，要及时退出；

- $2.$ 注意是“从起点到 $n$ 枚举终点”，而不是“从起点 $+1$ 到 $n$ 枚举终点”。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char w[10005];//w字符串就是题目中的字符串 
int l,ans;//l是字符串长度，ans就是答案个数 
int main()
{
	scanf("%s",w+1);//输入 
	l=strlen(w+1);//计算长度 
	for(int i=1;i<=l;i++)//枚举起点（i即为起点） 
	{	
		int a=0,b=0;//a和b分别是左右括号之差与问号个数 
		for(int j=i;j<=l;j++)//枚举终点（i即为起点） 
		{
			if(w[j]=='(')a++;//如果它是左括号，差值+1 
			else if(w[j]==')')a--;//如果它是右括号，差值-1  
			else b++;//如果它是问号，问号数+1  
			while(b&&b>a)a++,b--;//用问号尽量补齐差值
			//如果对此处判断条件感到疑问的，具体理由详见巨佬laeva的解释，这里不过多展开	
			if(a<0)break;//如果在此区间内，右括号数大于左括号数，当前和以后就都不行了，直接退出 
			if((j-i+1)%2==0&&a==b)ans++;//如果区间长度是偶数，且左右括号数相等，答案+1	
			//这里之所以是(j-i+1)%2==0，是因为两个符号才能完成匹配，所以区间长度要为偶数	
		}
	}
	cout<<ans;//输出结果 
    return 0;//结束程序 
}
```

---

## 作者：ZSYZSYZSYZSY (赞：0)

# CF917A The Monster

## Description

首先，我们要理解题目所描述的括号序列的性质以及如何判断一个字符串是否能够转换成正确的括号序列。根据题目描述，一个正确的括号序列满足以下条件：

1. 空字符串是一个正确的括号序列。

1. 如果 $s$ 是一个正确的括号序列，那么 $(s)$ 也是一个正确的括号序列。

1. 如果 $s$ 和 $t$ 是正确的括号序列，那么将它们连接起来得到的字符串 $st$ 也是一个正确的括号序列。

## Solution

我们需要设计一个算法来解决这个问题。我们可以使用动态规划的方法来解决这个问题。具体步骤如下：
接下来，我们可以使用动态规划的方法来解决这个问题。具体步骤如下：
1. 定义一个二维数组 $dp$，其中 $dp_{i,j}$ 表示从第 $i$ 个字符到第 $j$ 个字符组成的子串能否转换成正确的括号序列。

1. 初始化动态规划数组，对于长度为 $1$ 的子串，如果是左括号或者右括号，则 $dp_{i,i} = 0$，否则 $dp_{i,i} = 1$。

1. 接下来，我们从长度为 $2$ 的子串开始，逐步增加长度，更新动态规划数组。对于长度为 $len$ 的子串，我们枚举起始位置 $i$，然后枚举分割位置 $k$，如果 $dp_{i,k}$ 和 $dp_{k+1,i+len-1}]$ 都为真，或者 $dp_{i,k}$ 为真且 $dp_{k+1,i+len-1}$ 为左括号，那么 $ dp_{i,i+len-1} $ 为真。

1. 最后，我们统计所有满足条件的子串数量，即为所求答案。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll read()
{
    register ll x = 0, f = 1; 
    register char ans = getchar(); 
    while (ans < '0' || ans > '9')
    {
        if (ans == '-')
            f = -1;
        ans = getchar();
    }
    while (ans >= '0' && ans <= '9')
    {
        x = x * 10 + ans - 48;
        ans = getchar();
    }
    return x * f;
}

ll tot = 0, ans = 0, num = 0; // 定义三个全局变量，分别表示括号总数、结果、问号数

int main()
{
    string s; // 定义一个字符串变量
    getline(cin, s); // 从标准输入读取一行输入，存入字符串变量 s 中
    ll n = s.length(); // 获取字符串的长度
    for (ll i = 0; i < n; i++) // 遍历字符串的每一个字符
    {
        ll tot = 0, num = 0; // 初始化括号总数和问号数为 0
        for (ll j = i; j < n; j++) // 从当前位置开始遍历字符串的每一个字符
        {
            if (s[j] == '(') // 如果当前字符是左括号
            {
                tot++; // 括号总数加一
            }
            if (s[j] == ')') // 如果当前字符是右括号
            {
                tot--; // 括号总数减一
            }
            if (s[j] == '?') // 如果当前字符是问号
            {
                if (tot > 0) // 如果当前已有左括号
                {
                    tot--, num++; // 左括号数减一，问号数加一
                }
                else // 如果当前没有左括号
                {
                    tot++; // 括号总数加一
                }
            }
            if (tot < 0 && num) // 如果当前括号总数为负且存在问号
            {
                tot += 2; // 将括号总数加上 2，表示将一个问号转换为左右括号
                num--; // 问号数减一
            }
            if (tot < 0 && num == 0) // 如果括号总数为负且问号数为 0
            {
                break;
            }
            if (tot == 0) // 如果括号总数为 0
            {
                ans++; // 结果加一
            }
        }
    }
    cout << ans;
    return 0;
}

```

---

