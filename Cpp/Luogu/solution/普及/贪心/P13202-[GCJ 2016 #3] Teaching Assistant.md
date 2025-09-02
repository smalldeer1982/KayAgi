# [GCJ 2016 #3] Teaching Assistant

## 题目描述

你正在上一门以题集为评分方式的编程课程。课程持续天数为正偶数天。你开始时没有任何题集。在课程的每一天，你必须执行以下三种操作之一：

* 申请一个“编程（Coding）”题集；
* 申请一个“Jamming”题集；
* 提交一个题集进行评分。你必须至少拥有一个题集才能选择此操作。如果你有多个题集，必须提交**最近申请的那一个**，无论其类型如何。

所有题集都是不同的。对提交题集的类型和数量没有要求。一旦你提交了某个题集，你就不再拥有该题集。任何在课程结束前未提交的题集都不会获得分数。

题集的申请和提交都通过一个人工智能助教完成。奇怪的是，助教每天都有不同的心情——每一天只会喜欢“Coding”或“Jamming”中的一种。

* 当你申请题集时：
   * 如果申请的题集类型与助教当天的心情一致，则该题集最高可得 10 分。
   * 如果申请的题集类型与助教当天的心情不一致，则该题集最高可得 5 分。
* 当你提交题集时：
   * 如果提交的题集类型与助教当天的心情一致，则你能获得该题集的最高分。
   * 如果提交的题集类型与助教当天的心情不一致，则你获得的分数比最高分少 5 分。

例如：

* 如果你在助教心情为“Coding”的那天申请了一个“Coding”题集，并在助教心情为“Jamming”的那天提交，则你能获得 5 分：该题集最高分为 10 分，但助教会少给 5 分。
* 如果你在助教心情为“Coding”的那天申请了一个“Jamming”题集，并在助教心情为“Jamming”的那天提交，则你能获得 5 分：该题集最高分为 5 分，助教会给你最高分。

幸运的是，你有一位非常了解助教的师兄，他告诉了你课程每一天助教的心情。请问你最多能获得多少分？

## 说明/提示

**样例解释**

对于样例第 1 组，最优策略如下：
- 第 1 天：申请“Coding”题集（记为 C1）。
- 第 2 天：提交 C1。
- 第 3 天：申请“Jamming”题集（记为 J1）。
- 第 4 天：提交 J1。

对于样例第 2、3、4 组，最优策略为：先申请 C1，再申请 J1，然后提交 J1，最后提交 C1。

以第 2 组为例，注意你不能先申请 C1，再申请 J1，然后提交 C1。因为每次只能提交最近申请的题集。

对于第 5 组，你可以每隔一天申请一个“Coding”题集，下一天就提交它。

**限制条件**

- $1 \leqslant \mathbf{T} \leqslant 100$。
- $\mathbf{S}$ 的长度为偶数。

**小数据集（5 分，测试集 1 - 可见）**

- $2 \leqslant \mathbf{S}$ 的长度 $\leqslant 50$。

**大数据集（10 分，测试集 2 - 隐藏）**

- $2 \leqslant \mathbf{S}$ 的长度 $\leqslant 20000$。
- 所有测试用例的 $\mathbf{S}$ 总长度不超过 150000。

翻译由 GPT4.1 完成。

## 样例 #1

### 输入

```
5
CCJJ
CJCJ
CJJC
CJJJ
CCCCCC```

### 输出

```
Case #1: 20
Case #2: 10
Case #3: 20
Case #4: 15
Case #5: 30```

# 题解

## 作者：DeekSeep_V3 (赞：14)

蒟蒻一枚，大佬勿喷。

题意分析
---
给定字符串 $S$，当前后两个字符相同时可以得 $10$ 分，否则只能得 $5$ 分，问最多能得多少分。

思路概括
---
~~手滑点了算法标签，~~ 定睛一看，贪心！这题的贪心其实非常简单，顺着助教的心情就能拿到最高分，当前后两个字符相同时可以得 $10$ 分，否则只能得 $5$ 分，模拟时求和即可。怎么模拟呢？可以考虑栈的做法。  
首先枚举判断，如果相同（C 与 C 和 J 与 J）时压碎，即出栈，否则留在栈中。  
在枚举后肯定是互不相同的留在栈里，进行另一种匹配，不同的（C 与 J）互相匹配。

举个栗子：`CCJJ`是不是有两组相同的？所以得分是 $20$ 分。

再举个栗子：`CJCJ`没有相同的，考虑第二种情况，只能得 $10$ 分。


快乐的代码时间
---
```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
string s;
stack<char> stk;//注意是char类型，不是int类型
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>T;
    for(int i=1;i<=T;i++){
        cin>>s;
        int ans=0;
        for(int i=0;i<s.length();i++){
            if(i==0) stk.push(s[i]);
            else if(!stk.empty()&&stk.top()==s[i]) ans+=10,stk.pop();
            else stk.push(s[i]);
        }
        while(!stk.empty()) ans+=5,stk.pop(),stk.pop();
        cout<<"Case #"<<i<<": "<<ans<<endl;
    }
    return 0;
}
```
完结撒花✿✿ヽ(°▽°)ノ✿。

---

## 作者：Chenyuze24 (赞：2)

## Part1 分析
注意到题目中的 ```因为每次只能提交最近申请的题集```。因而考虑到具有先进后出性质的[栈](https://oi-wiki.org//ds/stack/)，只需要在申请题集时将这个字符弹入栈中，而在提交题集是弹出即可。其中用 $ans$ 来记录答案总数。那么就遍历整个字符串，如果栈顶与现在遍历到的字符相等，那么将他弹出，意思就是提交了这个申请过的题集，而且与助教的心情一致，故 ```ans+=10```。否则就将他弹入栈中，即申请题集。那么遍历完一遍后，显然栈中有可能还有元素且其个数为偶数个，就是与助教的心情不相符的字符，故每两个元素能让 ```ans+=5```。最后输出 $ans$ 即可。
## Part2 细节
- 注意栈的类型。
- 每次都要把栈内元素清空。
- 在弹出前先要保证栈内有元素。
- 输出的格式要注意，特别是分号，我就自己敲的时候敲错 $2$ 次，建议把题目中的抄下来。
- 最后的弹出是每次弹 $2$ 个。
## Part3 代码
具体见代码吧。
```cpp
#include<bits/stdc++.h>//万能头。
using namespace std;
#define popp for(int i=1;i<=2;++i)stk.pop()//每次弹两个。
#define li cout<<'\n';//换行。
int read(){//快读。
	int x=0,f=1;char c;
	c=getchar_unlocked();
	while(c<'0'||c>'9'){if(c=='-'){f=-1;}c=getchar_unlocked();}
	while('0'<=c&&c<='9'){x=(x<<3)+(x<<1)+c-'0';c=getchar_unlocked();}
	return x*f;
}
stack<char> stk;//定义栈。注意是char。
int n;
string str;
int idx=1;
void print(int n,int x)//输出。
{
	cout<<"Case #"<<n<<": "<<x;
	++idx;
	li;
}
void rea()
{
	n=read();
}
void solve()
{
	while(n--)
	{
		while(!stk.empty())stk.pop();//初始化。
		int ans=0;
		cin>>str;
		stk.push(str[0]);//先把第一个弹入。
		for(int i=1;i<str.size();++i)//遍历。
		{
			if(!stk.empty()&&stk.top()==str[i])//判断。
			{
				ans+=10;
				stk.pop();//弹出。
			}
			else
			{
				stk.push(str[i]);//否则弹入。
			}
		}
		while(!stk.empty())//必须要有元素的时候才弹。
		{
			popp;
			ans+=5;
		}
		print(idx,ans);//输出。
	}
}
int main()
{
	rea();
	solve();
	return 0;
}
```

---

## 作者：4041nofoundGeoge (赞：2)

这题没黄吧。

## 思路

考虑贪心，策略很好想，把 $S$ 中所有的连续两个相同字符消除，剩下的求和即可。

举例子：

```
CCCJJJCJCJ
```

首先消除两个相同连续字符，得到分数 $20$ 分（这里我们消除了两次）。

```
CJCJCJ
```

这里每一个字符都与旁边的字符相匹配，分数是 $5\times6\div2=15$。最后得分 $15+20=25$ 分。

证明：

设最优解的总得分为 $A$，考虑倒数第二次操作：

1. 如果是申请操作：剩余天数的最优解为 $A -$ 当前得分。

2. 如果是提交操作：剩余天数的最优解为 $A -$ 提交得分。

因此，问题可以分解为子问题，且子问题的最优解构成原问题的最优解。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
stack<char>stk;
int main(){
    int t;
    cin>>t;
    int q=t;
    while(t--){
        string s;
        cin>>s;
        while(!stk.empty())stk.pop();
        int sum=0,sum2=0;
        for(int i=0;i<s.size();i++){
            if(i==0)stk.push(s[i]);
            else if(!stk.empty()&&stk.top()==s[i]){
                sum+=10;
                stk.pop();
            }
            else stk.push(s[i]);
        }
        while(!stk.empty()){
            stk.pop();
            sum2+=5;
        }
        cout<<"Case #"<<q-t<<": "<<sum+(sum2/2)<<"\n";
    }
    return 0;
}
```

---

## 作者：chinazhanghaoxun (赞：1)

# P13202 Teaching Assistant - Solution

## Problem Statement

给定 $T$ 个由 `C` 和 `J` 构成的字符串，按照题意的方式求出一种使得题集得分最多的方式。

## Analysis

看到要求最大值，考虑贪心。

由不同情况，简单分析可得：

- 若 $s[i]=s[i+1]$，我只要令申请的题集编号也等于 $s[i]$ 就可以得到 $10$ 分
- 若找不到 $s[i]=s[i+1]$，那么令题集编号为 `C` 和 `J` 中的任意一个都可以得到最优分数 $5$ 分

## Approach

使用栈存储此前未配对成功的字符，若当前找到相等字符，弹出，$ans\gets ans+10$。否则继续压入栈中，等待下一轮匹配。

相等字符匹配完后一定会剩下，设为 $rest$ 个字符，且它们相邻一定是不同的。则这一部分产生的贡献为 $\frac{rest}2 \times 5$。

因此，总答案就是 $ans+\frac{rest}2 \times 5$，完成一次询问。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,cases=1;
	cin>>t;
	while(t--){
		string s;
		int n,ans=0;
		stack<char> st;
		cin>>s;
		n=s.size();
		for(int i=0;i<n;i++){
			if(!st.empty() && s[i]==st.top()){
				st.pop();
				ans+=10;
			}else{
				st.push(s[i]);
			}
		}
		cout<<"Case #"<<cases<<": "<<ans+st.size()/2*5<<endl;
		cases++;
	} 
	return 0;
}
```

---

## 作者：matrixPower (赞：1)

[传送门](https://www.luogu.com.cn/problem/P13202)

简单贪心题。

根据题面可以发现：

1. 一天必须做事情，申请或者提交。

2. 最优情况为心情一样的两天申请并提交。

3. 如果你要提交，就只能提交最近的题集。

所以我们可以总结出最优情况：第一天申请，第二天提交，且这两天心情相同。

那剩余的日子呢？剩余的日子心情肯定左右不同（即相邻的不同）那么你要么交不上，要么只能得到 $5$ 分。显然选择后者。

可以使用栈来记录两天心情相同。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define lowbit(x) (x)&(-x)
using namespace std;

typedef double db;
typedef long long ll;
typedef __int128 III;
const db eps=1e-6;
const int inf=1e9;
void ll_cmax(ll &a,ll b){a=a>b?a:b;}
void ll_cmin(ll &a,ll b){a=a<b?a:b;}
void int_cmax(int &a,int b){a=a>b?a:b;}
void int_cmin(int &a,int b){a=a<b?a:b;}
bool db_eq(db a,db b){return fabs(a-b)<eps;}
bool number(char ch){return ch>='0' && ch<='9';}
bool lower(char ch){return ch>='a' && ch<='z';}
int sqlong(int n){int sq=sqrt(n)+1;return min(sq,n);}

const int MAXN=20000+5; 
string s;
stack<char>st;
int T;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	int cur=0;
	while(T--)
	{
		++cur;
		cin>>s;
		int len=s.size(),ans=0;
		while(st.size()) st.pop();
		for(int i=0;i<len;i++)
		{
			if(st.empty() || st.top()!=s[i]) st.push(s[i]);
			else ans+=10,st.pop();
		}
		cout<<"Case #"<<cur<<": "<<ans+st.size()/2*5<<endl;
	}
	return 0;
}
//by Matrix_Power
```

---

## 作者：hlb44 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13202)

题目给定课程天数，要我们最大化最终得分，一说到“最”，你应该想到贪心或者 dp。

你可以从题目的某些语句中感受到：提交必须遵循“后进先出”原则（因为只能提交最近申请的题集），你应该立刻想到栈结构。

栈的前置知识：

栈是一个类似楼层一样的东西，你可以往它最上面丢东西，取出的时候也只能拿最上面的。

具体知识请[移步](https://blog.csdn.net/qq_40728285/article/details/81112907)。

综上所述，我们考虑贪心算法结合栈来解决，贪心地优先获取高分，再处理剩余情况：

* 匹配相同心情的提交，可获得 $10$ 分。

* 不匹配的题集我们考虑将当天心情入栈，继续申请新题集。

* 遍历结束后，栈中剩余的题集必为偶数个，每一对题集得 $5$ 分。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define fo(i,begin,end) for(int i=begin;i<=end;++i)
#define of(i,begin,end) for(int i=begin;i>=end;--i)
#define fos(i,begin,end,ADD) for(int i=min(begin,end);i<=max(begin,end);i+=ADD)
#define ofs(i,begin,end,ADD) for(int i=max(begin,end);i>=min(begin,end);i-=ADD)
#define debug(val) cout<<#val<<':'<<(val)<<'\n'
#define debug_1(name,i,x) cout<<#name<<"["<<i<<"]:"<<x<<'\n';
#define debug_2(name,i,j,x) cout<<#name<<"["<<i<<"]["<<j<<"]:"<<x<<"\n";
#define ll long long
#define ull unsigned long long
ll t,ans;
string in;
int main(){
    cin>>t;
    fo(i,1,t){
    	ans=0;
        cin>>in;
        stack<char>st;
        fo(j,0,in.size()-1){
        	if(!st.empty()&&st.top()==in[j]){
        		ans+=10;
				st.pop();
			}
            else{
            	st.push(in[j]);
			}
		}
        while(!st.empty()){
        	ans+=5;
			st.pop();
			st.pop();
		}
        printf("Case #%d: %d\n",i,ans);
    }
    return 0;
}
```

---

## 作者：L_T_L (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13202) 

只需找到一种贪心策略，使得在给定的助教心情序列下，能够获得最高的分数即可。

这道题类似于经典栈问题——括号匹配问题，相邻的相同字符可以配对得 $10$ 分，不同的配对得 $5$ 分。因此，可以使用栈来模拟这个过程：
1. 遍历每一天的心情。
2. 如果栈不为空且栈顶元素与当前天心情相同，则弹出栈顶并加 $10$ 分。
3. 否则，如果栈不为空但栈顶元素不同，则弹出栈顶并加 $5$ 分。
4. 如果栈为空，则将当前天心情入栈。
5. 由于题目保证天数为偶数，剩下的栈中元素必须两两配对，此时它们的类型不同，每对贡献 $5$ 分。

手动栈 CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>s;
        int ans=0,top=0;
        char st[20001]={};
        for(char day:s)
            if(top>0&&st[top-1]==day)
                ans+=10,top--;
            else
                st[top++]=day; 
        while(top>0)
            ans+=5,top-=2; 
        cout<<"Case #"<<i<<": "<<ans<<endl;
    }
    return 0;
}
```
自动栈 CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>s;
        int ans=0;
        stack<char>st;
        for(char day:s)
            if(!st.empty()&&st.top()==day)
                ans+=10,st.pop();
            else
                st.push(day);
        while(!st.empty())
            ans+=5,st.pop(),st.pop();
        cout<<"Case #"<<i<<": "<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：Nostopathy (赞：1)

# Solution

[更好的阅读体验](https://www.luogu.com.cn/article/wlw7ywce)

## 解答

考虑到若相邻两天心情相同，则前一天申请后一天提交即可得 $10$ 分，余下的必然是 $\texttt C$ 和 $\texttt J$ 交错的字符串，则前一天申请与心情相同的题集，后一天提交该题集即可，得 $5$ 分。因此考虑先消除所有心情相同并且相邻的两天，然后统计余下对数并计分。

特殊情况：定义两个相同心情的日期中间为心情相同的相邻两天，如 `CJJC`，则称为一个嵌套，若一个子串满足它是一个嵌套或它由两个相同心情的日期与中间的嵌套组成，如 `CJCCJC`，则该子串可被消除得分。

看一组样例：


```
CCJJCJCJJCCJ
```

（以下字符串从 $S_1$ 开始编号）

相同心情有 $S_1$ 与 $S_2$，$S_3$ 与 $S_4$ 和 $S_7$ 与 $S_{10}$ 嵌套 $S_8$ 与 $S_9$，得 $10 \times 4 = 40$ 分，消除后如下：


```
CJCJ
```

每两个 `CJ` 组成一对，得 $5 \times 2 = 10$ 分。

综上，原字符串总共积 $40 + 10 = 50$ 分。

## 实现

相信你已经有了写代码的思路。以下是我的实现：

考虑维护一个栈，存储目前申请的题集，当遍历到有元素与栈顶元素相同，则构成消除，此时取出栈顶元素并加分。余下的栈的大小就是可积 $5$ 分的对数。设总共消除 $m$ 次，原字符串长 $l$，则总分为 $10m + \frac{5}{2}(l - 2m)$。

你可以用 STL 的栈，但这里我就用 vector 了。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
#define pb push_back
#define rep(a, b, c, d) for(int a=b; a<=c; a+=d)
const int N = 2e4 + 5;
vector<char> arr;
signed main () {
	int t;
	scanf("%lld", &t);
	rep(c, 1, t, 1) {
		arr.clear();
		string s;
		cin >> s;
		arr.pb(s[0]);
		int sum = 0;
		for(int i = 1; i < s.size(); ++ i) {
			if(!arr.empty() && s[i] == arr.back())
				arr.pop_back(), sum += 10;
			else
				arr.pb(s[i]);
		}
		printf("Case #%lld: %lld\n", c, sum + (int)arr.size() / 2 * 5);
	}
	return 0;
}
```

## 总结

这道题标签为“贪心”，需要一定的策略，确保得出的是最优解。解这种题需要多搓样例，多读题调试，才不会错过任何的情况。

感谢您能看到这里，如有问题欢迎评论区留言。

~~没有求关的题解不是好题解。~~

---

## 作者：Xiaonao_Dali (赞：0)

根据题意，我们必须提交前必须有题库存在，也就是说只能先申请再提交，但提交也只能最近申请的进行提交，我首先想到的是栈（~~我觉得可能是单调栈~~），那么我们可以进行出入栈的模拟。\
其模拟策略如下：

1. 如果该栈为空，压入一个元素。
2. 如果该栈不为空，判断其顶端的与自己遍历到的元素是否相同，若是，将自己的分数加 $10$，若不是，压入元素。
3. 重复以上两个操作，直到遍历完整个字符串。

那么遍历完后有可能会出现还有赘余的元素没出栈，那么这些元素就是找不到匹配的了，那么将分数加 $5$，并连续出两次栈就好了。\
那么接下来是模拟出栈核心的代码。
```cpp
if(!t.empty()&&t.top()==s[i]) pts+=10,t.pop();
else t.push(s[i]);
```
那么没出栈的怎么办呢？那么可以每加 $5$ 分连续出栈两次，直到栈为空，结束，也就是如下核心代码。
```cpp
while(!t.empty()) pts+=5,t.pop(),t.pop();
```
好啦，核心代码给出来了，那么其他部分那就很简单了，我就不贴完整代码啦。

---

## 作者：封禁用户 (赞：0)

贪心。

我们需要在课程持续的天数内最大化总得分。每天有三种操作可选，且得分规则与助教当天心情相关。关键在于**如何安排申请和提交的顺序**以获取最高分。

优先在助教心情匹配时申请和提交题集，以获得最高分（$10$ 分）。当无法直接匹配时，考虑**交替**申请和提交的策略。

然后使用**栈**来模拟题集的申请和提交过程。当栈顶题集类型与当天助教心情匹配时，立即提交以获得高分。不匹配时，继续申请新题集，后续再处理。

课程结束时，若栈中仍有未提交的题集，按最低得分规则处理（每次提交两个得 $5$ 分）。

时间复杂度：$O(n)$。

---

AC code：
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        string S;
        cin >> S;
        int n = S.size();
        int score = 0;
        vector<char> stack;
        for (int i = 0; i < n; ++i) {
            if (stack.empty()) {
                stack.push_back(S[i]);
            } else {
                if (stack.back() == S[i]) {
                    score += 10;
                    stack.pop_back();
                } else {
                    stack.push_back(S[i]);
                }
            }
        }
        while (!stack.empty()) {
            char c1 = stack.back(); stack.pop_back();
            char c2 = stack.back(); stack.pop_back();
            score += 5;
        }
        cout << "Case #" << t << ": " << score << endl;
    }
    return 0;
}
```

---

