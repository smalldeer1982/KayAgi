# [ABC307D] Mismatched Parentheses

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc307/tasks/abc307_d

英小文字および `(`, `)` からなる長さ $ N $ の文字列 $ S $ が与えられます。  
 以下の操作を可能な限り繰り返したあとの $ S $ を出力してください。

- $ S $ の連続部分文字列であって、最初の文字が `(` かつ 最後の文字が `)` かつ 最初と最後以外に `(` も `)` も含まないものを自由に $ 1 $ つ選び削除する
 
なお、操作を可能な限り繰り返したあとの $ S $ は操作の手順によらず一意に定まることが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N $ は整数である
- $ S $ は英小文字および `(`, `)` からなる長さ $ N $ の文字列である
 
### Sample Explanation 1

例えば、以下の手順により操作後の $ S $ が `ac` となります。 - $ S $ の $ 4 $ 文字目から $ 6 $ 文字目までからなる部分文字列 `(d)` を削除する。$ S $ は `a(b)c` となる。 - $ S $ の $ 2 $ 文字目から $ 4 $ 文字目までからなる部分文字列 `(b)` を削除する。$ S $ は `ac` となる。 - これ以上操作を行うことはできない。

### Sample Explanation 3

操作後の $ S $ は空文字列になる可能性があります。

## 样例 #1

### 输入

```
8
a(b(d))c```

### 输出

```
ac```

## 样例 #2

### 输入

```
5
a(b)(```

### 输出

```
a(```

## 样例 #3

### 输入

```
2
()```

### 输出

```
```

## 样例 #4

### 输入

```
6
)))(((```

### 输出

```
)))(((```

# 题解

## 作者：lottle1212 (赞：10)

# [原题传送门](https://www.luogu.com.cn/problem/AT_abc307_d)
## Part 0
**题目大意**

- 给定一个长度为 $N (1 \leq N \leq 2 \times 10 ^ 5)$ 的由小写字母与括号组成的字符串。
- 将所有成对的左右括号以及括号内的小写字母删除，输出处理后的字符串。

举个典型的例子，请大家看样例二。

在字符串 $\texttt{"a(b)("}$ 中，$\texttt{"(b)"}$ 有完整的左右括号，因此可以删除，而 $\texttt{"(b)"}$ 之后的一个 $\texttt{"("}$ 由于没有 $\texttt{")"}$ 与其配对，因此不能删除。

## Part 1

**解题思路**

看到关于括号匹配，我们就会想到使用栈来解决问题。

对于入栈与出栈的情形，我们可以分类讨论：

1. 该字符为小写字母。此时我们直接入栈。
1. 该字符为 $\texttt{"("}$。此时我们先入栈，并统计 $\texttt{"("}$ 数量。
1. 该字符为 $\texttt{")"}$。此时我们先查询栈中是否有没删去的 $\texttt{"("}$。若有，我们便不断删字符到 $\texttt{"("}$ 为止，并更新 $\texttt{"("}$ 数量；否则，将 $\texttt{")"}$ 入栈。

**AC Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, cnt, top; //cnt 用于统计 "(" 数量
char st[200010], s[200010]; //st 代表栈，s 代表原字符串
signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> s + 1;
	for (int i = 1; i <= n; ++ i)
		if (s[i] == '(') st[++ top] = '(', ++ cnt; //情形2
		else if (s[i] == ')' && cnt) {
			while (st[top] != '(') -- top;
			-- top, -- cnt;
		} //情形3
		else st[++ top] = s[i]; //情形1
	for (int i = 1; i <= top; ++ i) cout << st[i];
	return 0;
}
```


---

## 作者：lrx___ (赞：4)

# 题意简述
输入一个字符串，把完整的括号里面的内容去掉。
# 思路
可以用一个双向队列，并用一个变量记录左括号。如果遇到了右括号并且里面有左括号，就从后面开始删，直到遇到左括号。最后再从前往后输出。
# 代码
```cpp
#include<cstdio>
#include<deque>
//双向队列 
#include<string>
#include<iostream>
using namespace std;
string a;
deque<char>d;
int main(){
	int n,i,cnt=0;
//	cnt为左括号数量 
	scanf("%d",&n);
	cin>>a;
	for(i=0;i<n;i++){
		if(a[i]=='('){
			d.push_back('(');
			cnt++;
		}else if(a[i]==')'){
			if(cnt==0){
				d.push_back(')');
//				没有左括号直接加入 
			}else{
				cnt--;
				while(d.back()!='('){
					d.pop_back();
				}
//				删掉括号内的内容
				d.pop_back(); 
//				删掉左括号 
			}
		}else{
			d.push_back(a[i]);
		}
	}
	while(d.size()){
		putchar(d.front());
		d.pop_front();
//		输出 
	}
	return 0;
}
```

---

## 作者：xht (赞：3)

贪心地匹配括号。

```cpp
int main() {
    int n;
    string s, ans;
    cin >> n >> s;
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') ++c, ans.pb(s[i]);
        else if (s[i] == ')') {
            if (c) {
                while (ans.back() != '(') ans.pop_back();
                ans.pop_back();
                --c;
            } else ans.pb(s[i]), c = 0;
        } else ans.pb(s[i]);
    }
    cout << ans << endl;
	return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：2)

**【题目分析】**

这题其实就是括号匹配。

由于本题有其他字符，所以还需要记录左括号数量。我们维护一个栈，遇到左括号进栈并让计数器加一，遇到右括号，若左括号个数不为 $0$ 就弹栈直到遇到左括号，并让计数器减一。由于栈内元素总个数为 $n$，所以总时间复杂度为 $\Theta(n)$。

**【完整代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,s1,top;
char st[500005];
string s;
int main(){
    cin >> n >> s;
    for(int i = 0;i < n;i ++){
    	st[++top] = s[i];
    	if(s[i] == '(') s1 ++;
    	if(s[i] == ')'){
    		if(s1){
    			s1 --;
    			while(st[top] != '(') top --;
    			top --;
			}
		}
	}
	for(int i = 1;i <= top;i ++) cout << st[i];
	return 0;
}

```

---

## 作者：Jerry_Luo (赞：1)

## [ABC307_D] Mismatched Parentheses
### 题目分析
- 对于一个给定字符串删出每对括号里的所有元素。

- 可以想到用 set 维护每个左括号的位置，出现右括号就退回与之匹配的左括号前一个位置，如果没有左括号则加入答案。

### 代码：
```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
template <typename _T>

inline void read(_T &x)
{
	x = 0; char c; _T d = 1;
	while(c > 57 || c < 48){
		c = getchar();
		if(c == '-') d = -1;
	}
	while(c >= 48 && c <= 57){
		x = (x << 1) + (x << 3) + (c ^ 48);
		c = getchar();
	}
	x *= d;
}

const int N = 2e5 + 5;
int n;
char a[N], ans[N];
set<int> s;
int cnt;

signed main()
{
	read(n);
	cin >> a;
	
	for(int i = 0; i < n; i++){
		if(a[i] == '('){
			ans[++cnt] = a[i];
			s.insert(cnt); 
		}else if(a[i] == ')'){
			if(!s.empty()){
				cnt = *s.rbegin(); //访问最后插入的左括号的位置 
				cnt--; //删除 
				auto pos = s.end(); 
				s.erase(--pos);
			}else{
				ans[++cnt] = a[i];
			}
		}else {
			ans[++cnt] = a[i];
		}
	}
	
	for(int i = 1; i <= cnt; i++) cout << ans[i];
	
	return 0;
}




```


---

## 作者：Dream_poetry (赞：1)

### 题意简述：

一个含有括号的小写字母串，删除里面的所有**可匹配括号和其中的元素**，让你输出删除完成后的字符串。

### 思路分析：

本来应该用**栈**的，但赛事我用了一种自我认为比较清奇的方法：

* 如果遇到一个左括号，就让变量 $t$ 自增，将记录括号内信息的字符串 $C$ 计入记录所有括号内信息的 $ST_t$ 中。

* 如果遇到右括号，就让 $t$ 自减，并将 $ST_t$ 清除掉。当 $t$ 小于 $0$ 时，输出右括号并将 $t$ 保持为零即可。

* 如果遇到普通字符，只要 $t$ 不为零，就计入到 $C$ 中，否则直接输出。

这样的模拟其实与栈类似，但并不完全相同。

最后，将剩余存储在 $C$ 中的字符输出即可。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,tep,p;
string s,c[1000005];
int main(){
	cin>>n>>s;
	for (int i=0;i<n;i++){
		if (tep<=0 && s[i]!='(' && s[i]!=')') cout<<s[i];
		if (tep>0 && s[i]!='(' && s[i]!=')') c[p]+=s[i];
		if (s[i]=='(' ){
			tep++;
			c[++p]+=s[i];
		}
		if (s[i]==')' ){
			c[p--]="";
			tep--;
			if (tep<0) {
				cout<<')';
				tep=0;
				p=0;
			}
		}
	}
	for (int i=1;i<=p;i++) cout<<c[i];
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/113315654)

---

## 作者：xiaoming007 (赞：1)

这次的 D 比 C 简单。

## 思路

括号匹配问题。

由于每一个 `)` 都要去匹配 `(`，那么容易想到用栈存储之前 `(` 出现的位置，如果碰到了 `)`，就可以将这两个位置之间的各个字符打上标记。

当遍历时，如果遇上了有标记的，便不输出，没有标记直接输出。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t[1001010];// t 数组用于存放标记
int main(){
	string s;
	int len;
	cin >> len >> s;
	std::vector<int> stk;
	for(int i = 0; i < len; ++i){
		if(s[i] == '('){
			stk.push_back(i);
		}else if(s[i] == ')'){
			if(!stk.empty()){
				t[stk.back()] = -1;//标记
				stk.pop_back();
				t[i] = 1;//标记
			}
		}
	}
	int qwq = 0;
	for(int i = 0; i < len; ++i){
		if(t[i]) qwq += t[i];
		else if(qwq == 0) putchar(s[i]);//只有等于 0 了才输出
	}
	return 0;
}
```

---

## 作者：Imken (赞：1)

[题目传送门](https://atcoder.jp/contests/abc307/tasks/abc307_d) [RMJ 传送门](https://www.luogu.com.cn/problem/AT_abc307_d)

## 题意简述

输入一个字符串，要求删除原字符串中左右匹配的括号及其中的内容。

## 思路分析

本题可以使用「珂朵莉树 + 栈」解决。使用栈进行括号匹配，同时存储上一个左括号出现的位置。若出现右括号，则进行 assign 操作，以标记需要被删除的区间。最后遍历所有区间得到答案。具体参见代码。

## 代码

```cpp
#include <iostream>
#include <set>
#include <stack>
using namespace std;

int n, m, u, v, w;
string s, res;

stack<int> st;

/* --- BEGIN ODT --- */

struct node {
    int l, r;
    mutable int v;
    node(const int& il, const int& ir, const int& iv)
        : l(il)
        , r(ir)
        , v(iv)
    {
    }

    bool operator<(const node& o) const { return l < o.l; }
};

set<node> odt;

auto split(int x)
{
    if (x > n)
        return odt.end();
    auto it = --odt.upper_bound(node { x, 0, 0 });
    if (it->l == x)
        return it;
    int l = it->l, r = it->r, v = it->v;
    odt.erase(it);
    odt.insert(node(l, x - 1, v));
    return odt.insert(node(x, r, v)).first;
}

void assign(int l, int r, int v)
{
    auto itr = split(r + 1), itl = split(l);
    odt.erase(itl, itr);
    odt.insert(node(l, r, v));
}

/* --- END ODT --- */

int main()
{
    cin >> n >> s;
    int ptr = 0;
    odt.insert({ 1, s.length(), 0 });
    while (ptr < s.length()) {
        // 括号匹配
        if (s[ptr] == '(') {
            st.push(ptr);
        } else if (s[ptr] == ')') {
            if (!st.empty()) {
                // 注意这里有 1 的偏移量
                assign(st.top() + 1, ptr + 1, 1);
                st.pop();
            }
        }
        ptr++;
    }
    for (node x : odt) {
        // 遍历区间
        if (x.v == 0) {
            for (int i = x.l; i <= x.r; i++)
                putchar(s[i - 1]);
        }
    }
    return 0;
}
```


---

## 作者：PineappleSummer (赞：0)

[ABC307D in Atcoder](https://atcoder.jp/contests/abc307/tasks/abc307_d)

D 题竟然比 C 题简单。

## 分析
栈入门题（当然也可以不用栈）。

定义一个栈，维护左括号的位置，遇到左括号就把位置存进去。

遇到右括号时，找到最新存入栈的左括号，把它们之间的部分删去，就完成了一次操作。重复此操作，直到不可以再删除。该操作代码如下：
```cpp
if(s[i]==')')//如果时右括号
{
	if(!k.empty())//首先判断是否有前面是否有左括号，没有的话就无法进行删除操作
	{
		s.erase(k.top(),i-k.top()+1),i=k.top()-1;//删除从该左括号到该右括号的部分，并更新当前i为左括号前面的位置
		k.pop();//将栈顶出栈（现在栈顶为前一个左括号的位置）
	}
}
```
## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	string s;
	stack<int>k;
	scanf("%d",&n);
	cin>>s;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='(') k.push(i);
		else if(s[i]==')')
		{
			if(!k.empty())
			{
				s.erase(k.top(),i-k.top()+1),i=k.top()-1;
				k.pop();
			}
		}
	}
	cout<<s;
    return 0;
}
```

---

## 作者：syzxzqy (赞：0)

### 题目意思
题目十分简单：给你一个字母串，删除里面的所有括号对及其元素，	求出删除完成后的串。  
### 题目方法
对于删除括号和括号中的串，我们只要用一个栈，记录元素。  
我们再用一个变量 $k$，表示当前左括号的个数。  
如果当前字符为有括号，且有左括号（$k>0$），那么就从栈尾一直往前删，直到删除 $1$ 个左括号为止。  
### 代码实现
```
#include<bits/stdc++.h>
using namespace std;
const int N=200001;
int n,i,t,k;char a[N],s[N];
signed main(){
	cin>>n>>s+1;
   	t=0;k=0;//手动模拟栈，元素个数为0，左括号个数为0
	for(i=1;i<=n;++i)
		if(s[i]==')'&&k>0){//如果有一对括号
			while(a[t]!='(') t--;//删到左括号
			t--;k--;//删去左括号，左括号个数-1
		}
		else{
			if(s[i]=='(') k++;//遇到左括号，左括号个数+1
			a[++t]=s[i];//把当前元素加入栈
		}
	for(i=1;i<=t;i++)//输出
		cout<<a[i];
}
```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc307_d)      
水题，比 C 简单不少。       
## 题意   
给你一个字符串，要求把里面所有可以进行匹配的括号及其里面所包含的所有字符都删掉。     
如 `1(2(3)(`，经过这些处理应该为 `1(2(`，其中只有一组括号可以进行匹配，里面包含了 `3`。          
## 解法
我们可以用一个栈维护括号序列。       
我们思考删除字符的操作。     
设 $a_i$ 为第 $i$ 个字符的状态：如果为 $0$，就不用删除，否则要删除。      
那么，如果一对括号分别在 $l$ 和 $r$ 的位置，我们需要对 $a_l$ 到 $a_r$ 都加上 $1$。    
但是这么样速度很慢，我们用差分实现即可。      
[CODE](https://www.luogu.com.cn/paste/f4930yc3)

---

## 作者：rickyxrc (赞：0)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

## 题意简述

给你一个含有括号的小写字母串，删除里面的所有括号对和其中的元素，让你输出删除完成后的串。

## 实现思路

既然遇到括号匹配，那我们大胆打一个栈上去。

别急，先别动手，因为有这样一种情况：

```
))a(b((c)d)
```

结果应该是：

```
))a(b
```

我们发现:不是所有括号都会被消除，不匹配的括号要保留。

检测到右括号时，若栈中没有左括号，那么这个右括号就不可能消去，只有这种情况要将右括号入栈，否则就将所有字符出栈直到左括号。

所以我们需要记录左括号的数量，在入栈和出栈时更新。

代码如下：

```cpp
#include<stdio.h>
#include<string.h>
#include<set>
#include<algorithm>

#define maxn 200007

char ch[maxn],st[maxn];

int top,lcnt,lc,rc,t,n;

int main(){
	scanf("%d%s",&n,ch);
	
	for(int i=0;i<n;i++){
		if(ch[i]==')'){
			if(lcnt){
				while(st[top-1]!='(')top--;
				top--;
				lcnt--;
			}
			else
				st[top++]=')';
		}
		else	
			st[top++]=ch[i],
			lcnt += (ch[i]=='(');
	}
	
	for(int i=0;i<top;i++)
		putchar(st[i]);
	
	return 0;
}
```

---

## 作者：2huk (赞：0)

[AtCoder ABC307 D - Mismatched Parentheses](https://atcoder.jp/contests/abc307/tasks/abc307_d)

## 题目描述

有一个长度为 $N$ 的仅由小写字母和**左右圆括号**组成字符串 $S$。接下来尽可能多地执行以下操作：

- 选择一个 $S$ 的字串 $s$，满足 $s$ 的第一项为左括号且最后一项为右括号，在 $S$ 中删除 $s$。

最后输出 $S$。

$N \le 2 \times 10^5$。

## 分析

要尽可能多的执行操作，也就是要找到尽可能多的左右括号匹配。·

定义一个栈存储当前还没有被匹配的左括号的**位置**，每当来一个新的右括号，就把栈顶的左括号和这个括号匹配，并把左括号弹栈。然后统计出所有这样匹配的左右括号的位置，用 `vector` 存储。

代码如下：

```cpp
for (re int i = 1; i <= n; i ++ )
{
	if (S[i] == '(') s.push(i);
	else if (S[i] == ')' && s.size())
	{
		v.push_back({s.top(), i});
		s.pop();
	}
}
```

接下来暴力的想法就是枚举每一对匹配的左右括号，假设它们的位置分别为 $l$ 和 $r$，然后删掉 $S_{l \sim r}$ 这一段区间。

```cpp
for (PII i : v)
{
	re int l = i.fi, r = i.se;
	for (re int i = l; i <= r; i ++ )
		st[i] = true;
}

for (re int i = 1; i <= n; i ++ )
	if (!st[i])
		putchar(S[i]);
```

这份代码里用 `st` 这个 `bool` 型数组记录这个位置是否被删除，本质上是一样的。

这样的做法是 $\Theta(n^2)$ 的，考虑优化。

显然的是，如果某个位置 $i$ 被 $\ge 1$ 个区间覆盖了，那么它就是被删掉了。因此我们可以统计一个 $d$ 数组，$d_i$ 表示 $S_i$ **被删掉的次数**，每次找到 $l$ 和 $r$ 就让 $d_{l \sim r}$ 全部进行 $+1$ 操作，然后找出最后的哪些位置仍为 $0$ 输出即可。

将某一个连续的区间加减，显然是差分。当然~~如果很闲的话~~写个线段树也可以。

代码：

```cpp
for (re int i = 1; i <= n; i ++ )
{
	if (S[i] == '(') s.push(i);
	else if (S[i] == ')' && s.size())
	{
		int t = s.top();
		v.push_back({t, i});
		++ d[t], -- d[i + 1];
		s.pop();
	}
}

for (re int i = 1; i <= n; i ++ )
{
	d[i] += d[i - 1];
	if (!d[i]) putchar(S[i]);
}
```





---

