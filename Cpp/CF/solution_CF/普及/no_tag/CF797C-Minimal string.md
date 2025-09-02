# Minimal string

## 题目描述

Petya recieved a gift of a string $ s $ with length up to $ 10^{5} $ characters for his birthday. He took two more empty strings $ t $ and $ u $ and decided to play a game. This game has two possible moves:

- Extract the first character of $ s $ and append $ t $ with this character.
- Extract the last character of $ t $ and append $ u $ with this character.

Petya wants to get strings $ s $ and $ t $ empty and string $ u $ lexicographically minimal.

You should write a program that will help Petya win the game.

## 样例 #1

### 输入

```
cab
```

### 输出

```
abc
```

## 样例 #2

### 输入

```
acdb
```

### 输出

```
abdc
```

# 题解

## 作者：Dws_t7760 (赞：4)

我们首先建立一个栈，将字符串的每个元素从前往后压入栈，如果栈顶比未入栈的所有字符的最小值要小，就将其输出并弹出栈，并继续查看栈顶是否能输出并弹出。

AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string t;
int n;
char minn[114514];
stack <char> st;
int main() {
	cin>>t;
	n=t.length(),minn[n]=127;
	for(int i=n-1;i+1;i--) {
		if(t[i]<minn[i+1]) minn[i]=t[i];
		else minn[i]=minn[i+1];
	}
	for(int i=0;i<n;i++) {
		st.push(t[i]);
		while(st.size()&&st.top()<=minn[i+1]) cout<<st.top(),st.pop();
	}
	return 0;
}
```


---

## 作者：Xdl_rp (赞：4)

solution
------------
- 可以用**栈**做。

- 判断栈顶的字符是否应该出栈的规则：当栈顶字符小于等于**未压栈的最小字符**时，则应该将栈顶字符出栈，否则就将接下来的字符入栈以等待最小的字符。

- 求**未压栈的最小字符**时可以用 $p_i$ 表示从第 $i$ 个字符到最后一个字符中的最小字符，这称为后缀最小值，求 $p_i$ 可以从后往前扫描输入字符串，$p_i$ 取 $p_{i+1}$ 和第 $i$ 个字符的最小值。$p$ 数组一开始预处理求出。复杂度 $O(N)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
char p[100005];
stack<char> stk;
int main() {
	string s;
	cin >> s;
	int n = s.size();
	p[n - 1] = s[n - 1];
	for (int i = n - 2; i >= 0; i--) {
		if (s[i] < p[i + 1]) p[i] = s[i];
		else p[i] = p[i + 1];
	}
	for (int i = 0; i < n - 1; i++) {
		stk.push(s[i]);
		while (!stk.empty() && stk.top() <= p[i + 1]) {
			cout << stk.top();
			stk.pop();
		}
	}
	stk.push(s[n - 1]);
	while (!stk.empty()) {
		cout << stk.top();
		stk.pop();
	}
	return 0;
}
```


---

## 作者：Pyrf_uqcat (赞：3)

### 题意
给出一个字符串，按照从前到后的顺序**进栈**，输出字典序最小的**出栈**序列。
### 思路
题目已经告诉我们了，定义一个**栈**。已知字典序最小，也就是优先输出字典序小的字符。所以我们可以将每一个字符依次遍历过去，如果当前字符比后面遍历的字符字典序都要小，那就输出并将这个字符出栈。否则就将后一个字符入栈，依次类推。

代码就不放了，锻炼大家的代码能力。

---

## 作者：lgydkkyd (赞：2)

点开题面，输出字典序最小的出栈序列这几个大字很显眼，不用想就知道这提示一道有一点点进阶的贪心，因为这题融合了栈，但是只要用栈写便不成问题了。而根据传统的贪心题的做法，要想写代码必须找到贪心策略，而这题由于让我们找尽量小的字典序无非就是**让小的字母尽量排在前面**,如果说当前的字符比还没有进栈的所有字母全都要要小，那么这样一来输出当前字符就是字典序最小的方案也就是该样例的最优解。然后就是代码实现的环节，但是乍一看数据绝对值有 $10^5$ ，很容易会出现超时的情况。这里就需要接触到另外一个概念，预处理。需要提前建一个类型为字符串的 $q$ 数组，用来记录第 $i$ 个元素后面的元素最大哪一个字母。经过这样的优化时间复杂度也就由原来的 $O(|s|^2)$ 成功缩短到了 $O(|s|)$，自然也就可以通过此题了。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
char q[114514],r[114514];//记录第i个元素后面的元素最大是什么的数组和输入的字符串 
stack<char>p;
int main(){
	cin>>r;//输入字符串 
	int rlen=strlen(r);//记录长度 
	q[rlen]='z'+1;//初始化，因为字符一定是小写字母，z+1就避免了重复 
	for(int i=rlen-1;i>=0;i--){//倒序遍历 
		q[i]=min(q[i+1],r[i]);//初始化一下q数组 
	}
	for(int i=0;i<rlen;i++){
		p.push(r[i]);//入栈元素 
		while(!p.empty()){
		    if(p.top()>q[i+1])break;//不满足条件可以跳出循环 
			putchar(p.top());//满足则输出，且使栈顶出栈
			p.pop();
		}
	}
	while(!p.empty()){
		putchar(p.top());//输出当前栈顶 
		p.pop();//栈顶出队 
	}
    return 0;//华丽结束``` 
}
```

---

## 作者：sto__Liyhzh__orz (赞：2)

[传送门：](https://www.luogu.com.cn/problem/CF797C)

------------

我用是用栈做的。

由于这个题非常的~~水~~，所以我来讲一下栈是个什么东西。

栈，`stack`，与队列（先进先出）相反，是后进先出，只能访问栈顶元素，就像手枪的弹夹一样。

常用操作有：

```cpp
#include<stack>       //头文件，也可以万能头
stack<int>sc;         //定义
sc.push(a);           //将a入栈
sc.top();             //访问栈顶元素
sc.pop();             //删除栈顶元素
sc.size();            //获取栈的长度
sc.empty();           //判断栈是否为空，空返回1，否则返回0
```

回到题目上来，来分析一下：

1. 当栈顶小于等于未入栈中最小字符，应该将栈顶出栈，并输出。

2. 写预处理用后缀算出每个字符后最小的字符。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long

const int MAXN=100000+5;
char minn[MAXN];
stack<char>ch;
string s;

int main()
{
    cin>>s;
    int len=s.size();
    minn[len-1]=s[len-1];
    for(int i=len-2;i>=0;i--)
    {
        minn[i]=min(minn[i+1],s[i]);
    }
    for(int i=0;i<len-1;i++)
    {
        ch.push(s[i]);
        while(!ch.empty() && ch.top()<=minn[i+1])
        {
            cout<<ch.top();
            ch.pop();
        }
    }
    ch.push(s[len-1]);
    while(!ch.empty())
    {
        cout<<ch.top();
        ch.pop();
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：2)

栈的模板题。

题意：

给出一个字符串，按照从前到后的顺序进栈，输出字典序最小的出栈序列。

思路：

因为要使字典序最小，于是优先输出最小的便是。

所以当栈中末尾的字符是最小时，其出栈；否则，将下一个字符入栈等下一个最小的字符。

这样一定是最优的。

代码：

```
	 ios::sync_with_stdio(false);
    char a[N], mx[N], s[N];
    cin>>a+1;//细节
    int n = strlen(a+1);
    mx[n + 1] = 127;
    for (int i = n; i >= 1; --i)
        mx[i] = min(a[i], mx[i + 1]);
    Stack stk;//定义一个栈。
 for (int i = 1; i <= n; i++) {
    stk.push(a[i]); // 将当前位置的字符入栈
    while (!stk.isEmpty() && stk.peek() <= mx[i + 1]) {
        cout << stk.pop(); 
    }
}
    return 0;
}
```


---

## 作者：highkj (赞：1)

# 前言
确实社供掉了，所以来发一篇题解。
# 思路
其实题目中都提醒了要用栈了，所以我们就可以发现因为每一个位置都要输出最小的又由于我们一定会遍历到最后一个所以我们就可以预处理从 $i\sim n$ 的最小值。

然后我们遍历整个数组如果现在的栈顶小于等于从 $i+1\sim n$ 中的最小值那么我们现在弹出栈顶一定最优，然后我们就可以一直这样执行，最后将还在栈中的元素全部弹出即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y) 
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
string s;
char Min[100100];
stack<char>st;
fire main() {
	cin>>s;
	s=" "+s;
	int l=s.size()-1;
	Min[l]=s[l];
	rep1(i,l-1,1) Min[i]=min(Min[i+1],s[i]);
	rep(i,1,l) {
		st.push(s[i]);
		while(st.size()&&st.top()<=Min[i+1]) {
			cout<<st.top();
			st.pop();
		}
	}
	while(st.size()) cout<<st.top(),st.pop();
	return false;
}
```

---

## 作者：Fa_Nanf1204 (赞：1)

## 栈加贪心的模板题
### 题意简述
输入一个字符串，按照给定字符串的字符顺序进栈，输出字典序最小的出栈方案。
- - -
### 分析
题目要求输出字典序最小的出栈方案，所以这题有一定贪心的想法。


首先我们可以用一个数组模拟栈，然后让字符依次进栈。此时贪心的策略就是：**如果当前的字符比未进栈的所有字符都要小**，那么输出当前字符就是字典序最小的方案。


再看一下数据范围：$1\le|s|\le10^{5}$，如果使用 $\mathcal{O}(|s|^2)$ 的算法会超时。所以我们可以用个数组记录当前位置的字符到最后一个字符中的最小字符。这样就可以优化时间复杂度。
- - -
### 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int cnt=0,a[100005],minn[100005];
int main(){
    cin>>s;
    minn[s.size()]=160;
    for (int i=s.size()-1;i>=0;i--){
		if (s[i]-'a'>=minn[i+1])minn[i]=minn[i+1];  //继承上一个位置的最小字符 
		else minn[i]=s[i]-'a';   //更新最小字符 
    }
    int len=s.size();
    for (int i=0;i<len;i++){
		a[++cnt]=s[i]-'a';//入栈 
		while(cnt>0 and a[cnt]<=minn[i+1]){  //判断栈顶是否为小于最小字符 
			cout<<char(a[cnt]+'a');//输出 
			cnt--;//出栈
		}
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

[题目传送门](/problem/CF797C)
- - -
## 思路

一眼贪心。

一个一个字符遍历过去，如果栈顶的元素比后面所有元素的字典序都要小，就可以让它出栈。

因为题目中要求输出的是字典序最小的出栈序列，所以是要让前面的元素尽可能小。

若是当前的这个元素比后面的元素都小就没人比它更适合先输出。
- - -
思路有了，现在可以考虑代码的实现。

首先每次需要看当前这个元素是否比后面的都小。

若每次向后遍历，时间复杂度：$\mathcal{O}(|s|^2)$，对于 $|s|\le10^5$ 的数据无法通过。

所以我们需要提前建一个数组，记录第 $i$ 个元素后面的元素最大是什么。

时间复杂度：$\mathcal{O}(|s|)$。
- - -
AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
char mi[100010];//记录第 i 个元素后面的元素最大是什么的数组
string s;
stack<char>st;
int main(){
	cin>>s;
	int l=s.size();
	mi[l]='z'+1;
	for(int i=l-1;i>=0;i--)mi[i]=min(mi[i+1],s[i]);//初始化
	for(int i=0;i<l;i++){
		st.push(s[i]);//入栈
		while(!st.empty()){
		    if(st.top()>mi[i+1])break;//不满足“当前这个元素是否比后面的都小”的条件
			putchar(st.top()),st.pop();//满足则输出
		}
	}while(!st.empty())putchar(st.top()),st.pop();//栈内的剩余元素按次序输出
    return 0;
}
```

---

## 作者：Ryan_Adam (赞：0)

# CF797C Minimal string 题解
## 算法
栈，贪心。
## 分析
运用**贪心**的思想。

题目要求要输出最小的出栈序列，那么就要让小的先出栈。依次进栈，如果当前栈顶的字符比它之后所有的字符都小，那么它现在出栈一定是最优的。

可以先**预处理**出输入字符串 $s$ 第 $i$ 位之后最小的字符，从前往后依次进栈，如果目前栈顶字符比后面的最小字符还要小，就出栈。最后记得要**清栈**，把栈中剩下的元素全部出栈、输出。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Raiden
{
    const int N = 1e5 + 5;
    string s;
    char f[N];
    stack<char> st;
    signed work()
    {
        cin >> s;
        int lens = s.size();
        f[lens] = s[lens - 1];
        for (int i = lens - 1; i >= 0; i--)
            f[i] = min(f[i + 1], s[i]);
        for (int i = 0; i < lens; i++)
        {
            st.push(s[i]);
            while (!st.empty() && st.top() <= f[i + 1])
            {
                cout << st.top();
                st.pop();
            }
        }
        while (!st.empty())
        {
            cout << st.top();
            st.pop();
        }
        return 0;
    }

}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：sunyizhe (赞：0)

这题还比较简单，本篇题解主要是解释其他题解没讲到的地方。

## 一、思路

本题题意非常清晰，这里不再赘述了。很明显按题目中说的用栈来做，贪心找最小字典序的出栈序列。

### 1.1 错误方法

那么如何贪心呢？首先先讲一下我的错误贪心（不知道有没有人和我一样）：如果栈空或当前的字符小于栈顶，就可以压进去，因为尽量让前面的字符最小。否则弹出栈顶并输出。最后把栈全部弹出。但出了什么问题呢？模拟样例 $2$，可以得出：

| $i$  |   $str_i$    |                      栈 $s$                      |      输出       |
| :--: | :----------: | :----------------------------------------------: | :-------------: |
| $0$  | $\texttt{a}$ |               $\texttt{a}$（栈空）               |                 |
| $1$  | $\texttt{c}$ |  $\texttt{c}$（$\texttt{c}$ 大于 $\texttt{a}$）  |  $\texttt{a}$   |
| $2$  | $\texttt{d}$ |  $\texttt{d}$（$\texttt{d}$ 大于 $\texttt{c}$）  |  $\texttt{ac}$  |
| $3$  | $\texttt{b}$ | $\texttt{d,b}$（$\texttt{b}$ 小于 $\texttt{d}$） |  $\texttt{ac}$  |
|      |              |                                                  | $\texttt{acbd}$ |

这里很显然把后面的 $\texttt{b}$ 忽略了，所以不是答案。如何解决问题呢？

### 1.2 正解 + 简略证明

很简单：当栈顶**小于等于**（必须加上等于！！！）未压进过栈的字符（出过栈的不算）中最小的就可以弹出栈。为什么呢？其他题解没写，我补充一下：

我们是按顺序压栈的，以样例 $2$ 为例，设当前搜到 $i$，所以未压进过栈的字符就是 $i+1 \sim 3$。如果栈顶比它大，那么不如直到将未压进过栈的字符中最小的压进栈中再弹出，肯定不是答案。所以该贪心正确。

## 二、代码

```cpp
//程序算法：模拟
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;

char Min[N];

void init(string s)
{
	int len=s.size();
	Min[len-1]=s[len-1];
	
	for(int i=s.size()-2;i>=0;i--)
		Min[i]=min(Min[i+1],s[i]);
}

void fast_read()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}

int main()
{
	//freopen("input.in","r",stdin);
	//freopen("output.out","w",stdout);
	
	fast_read();
	
	string str;
	cin>>str;
	init(str);
	
	stack<char> s;
	for(int i=0;i<str.size();i++)
	{
		s.push(str[i]);
		while(!s.empty()&&s.top()<=Min[i+1])
		{
			cout<<s.top();
			s.pop();
		}
	}
	
	while(!s.empty())
	{
		cout<<s.top();
		s.pop();
	}
	
	return 0;
}
```

---

## 作者：pragma_GCC (赞：0)

# STL 大法好！
这道题我们可以先预处理出每个位置的后缀最小字符 $k$ 数组，然后建一个栈，开始遍历。对于每一个遍历到的位置，先进栈，然后判断 $k[i]$ 与栈顶元素谁大谁小，如果栈顶元素小，则一直退栈，直到栈空或栈顶元素大于 $k[i]$；否则不做任何操作。  
[AC 记录](https://www.luogu.com.cn/record/134453034)  
### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
stack<char> st;
char min_zf[100002];
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>s;
	st.push(s[0]);
	min_zf[s.size()-1]=s.back();
	for(int i=(int)s.size()-2;i>=0;i--){
		min_zf[i]=min(min_zf[i+1],s[i]);
	}
	for(int i=1;i<s.size();i++){
		if(st.top()>min_zf[i]){
			st.push(s[i]);
		}else{
			while(!st.empty()&&st.top()<=min_zf[i]){
				cout<<st.top();
				st.pop();
			}
			st.push(s[i]);
		}
	}
	while(!st.empty())cout<<st.top(),st.pop();
	return 0;
}
```

---

## 作者：zhfaz123 (赞：0)

[题面](https://www.luogu.com.cn/problem/CF797C)

由于字典序的定义，显然尽可能让下一个位置上的字符最小。设当前决策位置为 $i$，栈为 $s$，$m$ 为当前栈的大小。首先，我们拿剩下字符中最小的（包括栈里的字符），那肯定拿。如果最小字符（位置记为 $a_i$）不是当前字符或在栈顶的话，就将 $s_i$ 入栈，然后比较栈顶和 $s_{a_i}$ 的大小并输出；是的话也一样。

所以，我们可以预处理出后缀最小字符，再贪心。时间复杂度 $\mathcal O(N)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr long long N=1e5;
string s;
int a[N+5],n;
int main()
{
	ios::sync_with_stdio(0);//读入加速
	cin.tie(nullptr);
	cin>>s;
	n=s.size();
	a[n]=n-1;
	for(int i=2;i<=n;i++)
	{
		const int& j=n-i+1;
		if(s[j-1]<s[a[j+1]]) a[j]=j-1;
		else a[j]=a[j+1];
	}//预处理
	stack<char,list<char>> st;
	for(int i=1;i<=n;i++)
	{
		st.push(s[i-1]);//先入栈
		while((!st.empty())&&s[a[i+1]]>=st.top())//如果栈顶大于等于最小字符，且栈不为空，输出。
		{
			cout<<st.top();
			st.pop();
		}
	}
	while(!st.empty())
	{
		cout<<st.top();
		st.pop();
	}//清理栈的剩余字符
	return 0;
}
```

---

## 作者：foryou_ (赞：0)

令输入的字符串为 $s$，$n$ 为字符串 $s$ 的长度。

引理：

- 对于栈顶的字符 $s_i$，若它的字典序 $\le$ 栈外的 $s_{i+1 \sim n}$ 中字典序最小的字符（记为 $p_{i+1}$），则它应该出栈并输出。

根据上述引理，我们先预处理出所有的 $p_i$，然后按照引理生成出栈序列输出即可。

时间复杂度 $O(n)$。

---

## 作者：泠小毒 (赞：0)

# Minimal string
给出一个字符串，按照从前到后的顺序进栈，输出字典序最小的出栈序列
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190509/)
## 解法
因为要字典序最小，所以优先输出最小的比较好，每次设定一个小写字母，从a枚举到z

先找在当前位置之前小于等于它的，要优先于后面的出栈

然后将后面所有的该字母找出来，位置设定为最后的该字母

这样一定是最优的，~~很显然啊（大雾~~
## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[100010],st[100010],ch;
int del[100010],len,cnt,nw,last;
int main()
{
    scanf("%s",s),len=strlen(s);
    for(int i=1;i<=26;i++)
    {
        ch='a'+i-1,nw=last-1;
        while(nw>=0&&(s[nw]<=ch||del[nw]))
            {if(!del[nw])st[++cnt]=s[nw],del[nw]=1;nw--;}
        nw=last;
        while(nw<len)
        {
            if(s[nw]==ch)st[++cnt]=ch,del[nw]=1,last=nw;
            nw++;
        }
    }
    for(int i=len-1;i>=0;i--)if(!del[i])st[++cnt]=s[i];
    for(int i=1;i<=cnt;i++)printf("%c",st[i]);
    return 0;
}
```

---

## 作者：tmpliyijiang (赞：0)

## 思路
对于每个字符 $s_i$ 入栈后，我们可以执行：

1. 将其输出并出栈

2. 跳过

如果 $s_i$ 是后方所有字符（含 $s_i$）中 ASCII 码值最小的字符，操作 $1$ 更优。如果不是，则对其中 ASCII 码值最小的字符执行操作 $1$ 更优。

对于此判断，可以用一个字符数组 $a_i(1\le i\le n)$ 表示 $s_i$ 及以后的 ASCII 码值最小的字符实现。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
stack<char> c;
char a[100005];
int main(){
	cin>>s;
	int n=s.size();
	a[n]='z'+1;//赋初值
	for(int i=n-1;~i;i--)
		a[i]=min(a[i+1],s[i]);//求 a 数组
	for(int i=0;i<n;i++){
		c.push(s[i]);
		while(!c.empty()&&c.top()<=a[i+1]){//操作 1
			putchar(c.top());
			c.pop();
		}
	}
	while(!c.empty()){//别忘了输出
		putchar(c.top());
		c.pop();
	}
	return 0;
}

```

---

## 作者：xiaoyuchenp (赞：0)

栈的模板加简单贪心。

**思路**

题目要求输出字典序最小的出栈序列，显然要让较小的字符先输出。我们可以想到，若栈顶的字符比它后面入栈的每一个字符都小，那么让这个字符出栈就是最优的。用这个思路模拟即可。

我们先预处理出入栈字符串 $s$ 的后缀最小字符数组，从前往后依次进栈。如果栈顶的字符比后面所有字符都要小，就可以出栈。这样就可以得出最优序列。

时间复杂度 $O(n)$，显然可以通过本题。

**code**

```cpp
#include<bits/stdc++.h>
#define INF 127
#define MAXN 100005
using namespace std;
int len;
string s;
stack<char>st;
char minc[MAXN];
void init(){
	minc[len]=INF;
	for(int i=len-1;i>=0;i--)
		minc[i]=min(minc[i+1],s[i]);
}

int main(){
	cin>>s;len=s.size();
	init();
	for(int i=0;i<len;i++){
		st.push(s[i]);
		while(!st.empty()&&st.top()<=minc[i+1]){cout<<st.top();st.pop();}
	}
	return 0;
}
```

---

