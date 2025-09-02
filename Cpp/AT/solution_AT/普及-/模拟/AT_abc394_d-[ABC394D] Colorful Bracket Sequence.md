# [ABC394D] Colorful Bracket Sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc394/tasks/abc394_d

给定一个由 6 种字符 `(`, `)`, `[`, `]`, `<`, `>` 组成的字符串 $S$。

当字符串 $T$ 满足以下条件时，称其为卡芙乐括号列：

> 通过执行以下操作若干次（包括零次）可以将 $T$ 变为空字符串：
> 
> - 若 $T$ 中存在连续的 `()`, `[]`, `<>` 子字符串，选择其中任意一个删除。
> - 若删除的子字符串位于 $T$ 的开头或结尾，则将剩余部分作为新的 $T$。
> - 否则，将删除位置前后的字符串连接为新的 $T$。

请判断 $S$ 是否为卡芙乐括号列。

## 说明/提示

### 约束条件

- $S$ 是长度介于 $1$ 到 $2 \times 10^5$ 之间的字符串
- $S$ 仅由 `(`, `)`, `[`, `]`, `<`, `>` 组成

### 样例解释 1

对于 $S=$ `([])<>()`，可通过以下操作变为空字符串：
- 删除第 2-3 字符 `[]`，得到新字符串 `()<>()`。
- 删除第 1-2 字符 `()`，得到新字符串 `<>()`。
- 删除第 1-2 字符 `<>`，得到新字符串 `()`。
- 删除 `()` 后字符串变为空。  
因此输出 `Yes`。

### 样例解释 2

$S=$ `([<)]>` 不包含任何 `()`, `[]`, `<>` 子字符串，无法执行任何操作，因此输出 `No`。

### 样例解释 3

无法通过操作将 $S=$ `><><` 变为空字符串，因此输出 `No`。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
([])<>()```

### 输出

```
Yes```

## 样例 #2

### 输入

```
([<)]>```

### 输出

```
No```

## 样例 #3

### 输入

```
())```

### 输出

```
No```

# 题解

## 作者：boluo2014 (赞：3)

又来发 AT 的题解了。

### 思路

关键就是：其实，这道题目就是让你判断这个括号序列是否合法。（也就是加上数字能否变为算式）

为了后续叙述的方便，我们把 `(`, `)`, `[`, `]`, `<`, `>` 分别称为左小、右小、左中、右中、左尖、又尖。

所以，我们可以找出一些情况：

#### 第一种情况

左小个数不等于右小个数，或左中个数不等于右中个数，或左尖个数不等于右尖个数，那就肯定会出现错误啊。

#### 第二种情况

在某一个时刻，右小个数大于左小个数，或右中大于左中个数，或右尖个数大于左尖个数，那相当于右边和左边反了，也肯定不行。

#### 第三种情况

如果你想到这里就以为结束了，那你会发现第三组样例错了。然后看了一眼它的错误。

这个错误的判断相比前面稍微复杂了一点。其实是一对的中间还插了一对。那没有办法了我们只好引入一个新的方法：栈。

至于栈，你可以把它想象成一个垃圾桶。你先放进去的东西就会晚出来，而后放进去的东西就会先出来。

所以，你可以把左小、左中、左尖当作放进去的东西，而如果是右小、右中、右尖则是把东西拿出来。可是，如果想拿的东西和实际的对不上，那就取不出来，也就出现了“错乱”的现象了。故这个括号序列不正确，结束程序。如果刚好对应，那把它取出就好了。

### 代码实现

先将一些栈的基本操作（只是举例子）。

定义：
```
stack<int>st;
```
存入：
```
int x;
cin>>x;
st.push(x);
```
访问顶端：
```
int d=st.top();//d 是 st 中最上面的元素
```
弹出最上面的（删除）：
```
st.pop();
```
是否为空：
```
if(st.empty()){
	cout<<"Empty"<<endl;
}
else{
	cout<<"Not empty"<<endl;
}
```
基本的操作就这些了。

然后，你可以先考虑第一种情况和第二种情况，载考虑第三种情况。就是我赛时写的（有点烦）：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
stack<int>st;
signed main(){
	string s;
	cin>>s;
	int a,i,x1=0,y1=0,x2=0,y2=0,x3=0,y3=0;
	a=s.size(); 
	for(i=0;i<a;i++){//第一种情况 
		if(s[i]=='(')x1++;
		if(s[i]==')')y1++;
		if(s[i]=='[')x2++;
		if(s[i]==']')y2++;
		if(s[i]=='<')x3++;
		if(s[i]=='>')y3++;
		if(y1>x1){cout<<"No"<<endl;return 0;}
		if(y2>x2){cout<<"No"<<endl;return 0;}
		if(y3>x3){cout<<"No"<<endl;return 0;}
	}
	if(x1!=y1||x2!=y2||x3!=y3){cout<<"No"<<endl;return 0;}//第二种情况 
	for(i=0;i<a;i++){//第三种情况 
		if(s[i]=='(')st.push(1);
		if(s[i]=='[')st.push(2);
		if(s[i]=='<')st.push(3);
		if(s[i]==')'){
			if(st.top()!=1){
				cout<<"No"<<endl;
				return 0;
			}
			else{
				st.pop();
			}
		}
		if(s[i]==']'){
			if(st.top()!=2){
				cout<<"No"<<endl;
				return 0;
			}
			else{
				st.pop();//记得弹出 
			}
		}
		if(s[i]=='>'){
			if(st.top()!=3){
				cout<<"No"<<endl;
				return 0;
			}
			else{
				st.pop();
			}
		}
	}
	cout<<"Yes"<<endl;//啥问题都没有 
	return 0;
}

```

~~可以复制了~~

但是这个太长了，我们可以尝试优化代码。也就是把第一种可能、第二种可能、第三种可能一起用栈来实现。新的代码如下：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
stack<char>st;
signed main(){
	string s;
	cin>>s;
	int a,i;
	a=s.size(); 
	for(i=0;i<a;i++){
		if(s[i]=='('||s[i]=='['||s[i]=='<')st.push(s[i]);
		if(s[i]==')'){
			if(st.empty()){//我啥也没有你干嘛把我弹出（第二种可能） 
				cout<<"No"<<endl;return 0;
			}
			if(st.top()!='('){//第三种情况 
				cout<<"No"<<endl;return 0;
			}
			else{
				st.pop();
			}
		}
		if(s[i]==']'){
			if(st.empty()){
				cout<<"No"<<endl;return 0;
			}
			if(st.top()!='['){
				cout<<"No"<<endl;
				return 0;
			}
			else{
				st.pop(); 
			}
		}
		if(s[i]=='>'){
			if(st.empty()){
				cout<<"No"<<endl;return 0;
			}
			if(st.top()!='<'){
				cout<<"No"<<endl;
				return 0;
			}
			else{
				st.pop();
			}
		}
	}
	if(!st.empty()){//第一种情况 
		cout<<"No"<<endl;
		return 0;
	}
	cout<<"Yes"<<endl;//啥问题都没有 
	return 0;
}
```
这应该可以看懂吧。

觉得好就点个赞，看不懂就在评论区说，或者直接私信我也行。

---

## 作者：ryf2011 (赞：2)

# 题目思路
我们用一个栈来存储所有的括号。

遍历字符串，让左括号和右括号都入栈，如果出现两个括号匹配的情况，那么将这对括号移出栈，不断重复这个过程，直到所有元素都遍历完成。

注意：本题的括号共有三种，注意判断两个括号是否为同一种类型的一对括号。

# 代码
注：本代码仅供参考。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int max_n=2e5+5;
char s[max_n];
char st[max_n]; //手写栈 
int top; //栈顶位置 
int main(){
	scanf("%s",s+1); //输入 
	for(int i=1;i<=strlen(s+1);i++){
		if(s[i]=='('||s[i]=='['||s[i]=='<'){ //如果是左括号，将其加入栈 
			top++;
			st[top]=s[i];
		}
		else{ //右括号同样加入栈 
			top++;
			st[top]=s[i];
			//如果两个括号匹配，那么将他们移出栈，也就是栈顶位置变量 -2 
			if(st[top-1]=='('&&st[top]==')'||st[top-1]=='['&&st[top]==']'||st[top-1]=='<'&&st[top]=='>'){
				top-=2;
			}
		}
	}
	if(top==0){ //如果栈为空，说明括号全部匹配，输出 Yes 
		printf("Yes\n");
	}
	else{ //如果栈不为空，说明有括号未成功匹配，输出 No 
		printf("No\n");
	}
	return 0;
}
```

#### 后记
更多内容，请移步至 [$\color{red}\texttt{ryf2011}$](https://www.luogu.com.cn/user/1151973 "点我进入ryf2011")。

---

## 作者：Iron_Spade (赞：2)

现在 abc 的前面几道题开始拼手速了。

## Solution

括号匹配问题。

我们知道朴素的左右小括号序列判断合法是用个**栈**，具体的操作就是遇到左括号就进栈，遇到右括号就判断**当前栈顶是否有左括号**，如果有就将这个左括号弹出栈，代表**这两个括号组成了一个括号对。**

那么考虑拓展这个问题，它是三种不同的括号，其实本质相同，和上面的问题一样，只是当我们遇到一个右括号的时候的判断改为**当前栈顶是否为其对应的一个左括号**，其余操作一样，具体可以见代码。

```cpp
void sol() {
	cin >> s, n = s.size(), s = ' ' + s;
	if(n & 1) cout << "No", exit(0);
	rep(i, 1, n) {
		if(s[i] == '<' || s[i] == '(' || s[i] == '[') st.push(s[i]);
		else {
			if(s[i] == '>') {
				if(st.empty() || st.top() != '<') cout << "No", exit(0);
				else st.pop();
			}
			if(s[i] == ']') {
				if(st.empty() || st.top() != '[') cout << "No", exit(0);
				else st.pop();
			}
			if(s[i] == ')') {
				if(st.empty() || st.top() != '(') cout << "No", exit(0);
				else st.pop();
			}
		} 
	}
	cout << "Yes";
}
```

不知道这个题是否有 $n\equiv 1\pmod 2$ 的情况，建议判一下，因为这样肯定不是一个合法的括号序列。

---

## 作者：H_dream (赞：2)

# 题目大意
其实就是括号匹配，经典问题了。不过需要注意，这里只有连续的两个括号才能配对，例如 `(<>)` 是合法的，但 `<(>)` 不合法。
# 思路
和原括号匹配一样，我们使用一个栈，如果当前括号为左括号，则直接入栈，否则将其与栈顶字符进行匹配。最好记得查看栈是否为空。
# 代码参考
```
// Problem: D - Colorful Bracket Sequence
// Contest: AtCoder - KAJIMA CORPORATION CONTEST 2025 (AtCoder Beginner Contest 394)
// URL: https://atcoder.jp/contests/abc394/tasks/abc394_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms

#include<bits/stdc++.h>
#define ll long long
using namespace std;
string s;
stack<char> st;
bool flag=1;
int main(){
	cin>>s;
	for(int i=0;s[i];++i){
		if(s[i]=='('||s[i]=='<'||s[i]=='[') st.push(s[i]);
		else {
			if(st.empty()){
				flag=0;
				break;
			}
			char a=st.top();
			if(a=='('&&s[i]!=')' || a=='['&&s[i]!=']' || a=='<'&&s[i]!='>'){
				flag=0;
				break;
			}
			st.pop();
		}
	}
	if(!st.empty()) flag=0;
	if(flag) printf("Yes");
	else printf("No");
	
	return 0;
}
```

---

## 作者：zlqwq (赞：2)

巨水的一道题。

括号匹配的改编版，如果遇到左边括号，直接加入栈中，否则判断能否配对，如果配对，直接弹出。

最后判断栈是否为空即可。

---

## 作者：MaiJingYao666 (赞：2)

# AT_abc394_d [ABC394D] Colorful Bracket Sequence  题解  
### 解题思路  
很明显的一道类括号匹配板子题，详见 [我也不知道在哪](https://www.luogu.com.cn/article/8a91sa5m)。  
好的不说废话，这题可以用一个栈来实现匹配，当该字符是前括号时入栈，否则将它与栈顶元素判定，就是这样了。  
注意要处理好细节，比如空栈的情况。  
### AC 代码  

```cpp
#include<iostream>
#include<stack>
#include<cstring>
using namespace std;
char c[200005];
stack<char> stk;
int main(){
	cin>>c;
	int len=strlen(c);
	for(int i=0;i<len;i++){
		if(c[i]=='(' || c[i]=='[' || c[i]=='<'){
			stk.push(c[i]);
		}
		else if(stk.empty()){
			cout<<"No";
			return 0;
		}
		else if(c[i]==')'){
			if(stk.top()=='('){
				stk.pop();
			}
			else{
				cout<<"No";
				return 0;
			}
		}
		else if(c[i]==']'){
			if(stk.top()=='['){
				stk.pop();
			}
			else{
				cout<<"No";
				return 0;
			}
		}
		else if(c[i]=='>'){
			if(stk.top()=='<'){
				stk.pop();
			}
			else{
				cout<<"No";
				return 0;
			}
		}
	}
	if(stk.size())cout<<"No";
	else cout<<"Yes";
}
```

---

## 作者：Tomwsc (赞：2)

# AT_abc394_d [ABC394D] Colorful Bracket Sequence 题解

## 题意

一句话：括号合法性匹配。

## 思路

用栈模拟即可。

- 如果下一个字符是左括号，就直接入栈。
- 如果栈顶是右括号，下一个字符直接入栈。
- 如果栈顶是左括号，下一个字符是同种右括号就出栈。
- 如果栈顶是左括号，下一个字符是不同种右括号就直接判非法。
- 如果栈已经为空，下一个字符是右括号就直接判非法。
- 如果字符都处理完毕，但栈不为空就判非法。
- 否则输出合法。

知道了这些，代码就很好实现了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf (1ll << 62)
using namespace std;
string s;
stack<char>st;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	for(register int i = 0;i < s.length();i ++) {
		if(s[i] == '(' || s[i] == '[' || s[i] == '<')
			st.push(s[i]);
		else if(s[i] == ')') {
			if(st.empty()) {
				cout << "No";
				exit(0);
			}
			if(st.top() == '(')
				st.pop();
			else if(st.top() == '<' || st.top() == '[') {
				cout << "No";
				exit(0);
			} else
				st.push(s[i]);
		} else if(s[i] == ']') {
			if(st.empty()) {
				cout << "No";
				exit(0);
			}
			if(st.top() == '[')
				st.pop();
			else if(st.top() == '<' || st.top() == '(') {
				cout << "No";
				exit(0);
			} else
				st.push(s[i]);
		} else if(s[i] == '>') {
			if(st.empty()) {
				cout << "No";
				exit(0);
			}
			if(st.top() == '<')
				st.pop();
			else if(st.top() == '(' || st.top() == '[') {
				cout << "No";
				exit(0);
			} else
				st.push(s[i]);
		}
	}
	if(st.empty())
		cout << "Yes";
	else
		cout << "No";
	return 0;
}
```

---

## 作者：dg114514 (赞：1)

#### 闲话

这不就是 [P1739](https://www.luogu.com.cn/problem/P1739) 的加强版吗（

### 题意

给你一个只包含 `(`、`)`、`[`、`]`、`<`、`>` 的字符串 $S$，求能否执行无数次以下操作使 $S$ 变空：

- 找到 $S$ 的子串 `()`、`[]` 或 `<>`，并删除它。

### 思路

可以发现，只要 $S$ 的括号（`<>` 也算作）能够匹配，$S$ **一定**可以满足题目要求。所以跑个栈匹配即可。

### 代码（STL 栈）

```cpp
#include<bits/stdc++.h>
using namespace std;
stack<char>stk;
signed main(){
	string s;
	cin>>s;
	for(auto &i:s){
		if(i=='('||i=='['||i=='<')
			stk.push(i);
		if(i==')'){
			if(stk.empty()||stk.top()!='(') puts("No");//特判：如果栈空还取 top/pop 会 RE 
			else stk.pop();
		}
		if(i==']'){
			if(stk.empty()||stk.top()!='[') puts("No");
			else stk.pop();
		}
		if(i=='>'){
			if(stk.empty()||stk.top()!='<') puts("No");
			else stk.pop();
		}
	}
	puts(stk.empty()?"Yes":"No");//栈不空则还有剩余左括号 
	return 0;
}
```

---

## 作者：nr0728 (赞：1)

用栈，如果当前的字符是反括号（`)`、`]` 或 `>`），并且刚好是栈顶反过来，就匹配了一对括号，弹出栈顶，否则把当前的字符压入栈。最后栈空就是匹配。

---

## 作者：cjx_AK (赞：1)

#### 题目描述
给你一个字符串，让你求括号是否匹配。

只需定义一个栈，然后如果是左半边的括号，那么入栈。

如果是右半边的括号那么如果和栈顶的括号匹配，那么栈顶元素，表示这个括号被消掉了，否则则括号序列不满足要求。

code：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,T,i,x,tp;

string s;
map<int,char>q;
int main(){

	T=1;
	while(T--){
		cin>>s;
	}
	for(int i=0;i<s.size();i++){
		if(s[i]=='['||s[i]=='('||s[i]=='<'){q[++x]=s[i];}
else{
	char t=q[x];
	if((t=='['&&s[i]==']')||(t=='('&&s[i]==')')||(t=='<'&&s[i]=='>')){x--;}
else q[++x]=t;
}		
	}
	if(x==0){
		cout<<"Yes";
	}else{
		cout<<"No";
	}
	return 0;
}

```

---

## 作者：getchar_unlocked (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc394_d)

### 思路

在最基础的括号匹配问题上，变成了 $3$ 种字符。同样可以用栈进行模拟，将所有左括号压入栈内。若当前右括号与栈顶左括号不匹配或栈为空，输出 `No`。最后再判断最后的栈是否为空（是否有多余的左括号）即可。

时间复杂度 $\mathcal{O}(N)$。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
char to[128];
signed main(){
	string s;cin>>s;
	to[')']='(',to[']']='[',to['>']='<';
	stack<char>st;
	for(auto ch:s){
		if(ch=='('||ch=='['||ch=='<')
			st.push(ch);
		else if(ch==')'||ch==']'||ch=='>'){
			if(st.empty()||st.top()!=to[ch])
				return cout<<"No\n",0;
			st.pop();
		}
		else return cout<<"No\n",0;
	}
	if(st.empty())
		cout<<"Yes\n";
	else cout<<"No\n";
	return 0;
}
```

---

## 作者：__FL__ (赞：1)

栈运用典题，好像还有原题。
## 题意
我们将 ```() [] <>``` 统称为括号。

给定一个括号序列，问它是否合法。我们定义一个括号序列是合法的当且仅当能通过若干次 删除相邻的成一对的括号 这样的操作，使得这个括号序列最终为空。
## 思路
考虑栈。

过程是这样的：遍历整个括号序列，如果为左括号则入栈，否则检查栈顶是否和这个右括号匹配，如果是则出栈，如果否则直接输出 ```No```。最后还要检查栈是否为空。

为什么这样是正确的呢？考虑每一对应当匹配的括号，如果它们中间也是一个合法的括号序列，则显然能通过递归思想消除；否则就不能，整个序列当然也是不合法的。

## 时间复杂度

遍历，$O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
stack<int>t;
int main()
{
	ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin >> s;
	for (char i: s)
	{
		if (i == ')' && (t.empty() || t.top() != 1) ||
			i == ']' && (t.empty() || t.top() != 2) ||
			i == '>' && (t.empty() || t.top() != 3))
		{
			cout << "No";
			return 0;
		}
		if (i == ')' || i == ']' || i == '>') t.pop();
		else if (i == '(') t.push(1);
		else if (i == '[') t.push(2);
		else t.push(3);
	}
	if (!t.empty()) cout << "No";
	else cout << "Yes";
	return 0;
}
```

---

## 作者：qhr2023 (赞：1)

## solution

括号匹配问题，栈的入门题。

一个右括号一定和它左边最近的同类左括号匹配，这可以用先进先出的数据结构解决。

遇到左括号将其入栈，遇到右括号，判断栈顶能否与之匹配，若栈为空或不匹配则说明这不是合法的序列，若能匹配就将栈首出栈。

遍历完序列后，还要判断栈是否为空，若不为空说明还有字符没有匹配，即不合法，若为空则合法。

## code

[code](https://atcoder.jp/contests/abc394/submissions/63046601)。

---

## 作者：__Accepted_ZYF__ (赞：0)

不是哥们这是怎么上 D 题的，史上最简单。

直接括号匹配即可。

具体维护如下：

1. 对于所有左括号（`(`，`[` 和 `<`）直接加入符号栈。
2. 要是出现右括号：
   - 出现 `)` 则检查当前栈顶是否为 `(`，否则无法匹配，匹配成功则弹出栈顶。
   - 同理，`]` 需要检查栈顶为 `[`，`>` 需要检查栈顶为 `<`。
3. 匹配完成，要是栈中还有待匹配的括号，也是无法匹配的。


```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ivan422{
	#define ll long long
	#define ld long double 
	#define il __int128
	#define fl __float128
	#define x0 x_0
	#define x1 x_1
	#define y0 y_0
	#define y1 y_1
	#define yn y_n
	#define j0 j_0
	#define j1 j_1
	#define k0 k_0
	#define k1 k_1
	#define d0 d_0
	#define d1 d_1
	#define pb push_back
	#define pf push_front
	#define mp make_pair
	#define ar array<int,3>
	#define us unsigned
	#define io ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
};
using namespace ivan422;
const int N=2e5+10,M=1e3+10;
const int P1=1e9+7,P9=998244353;
const double pi=3.1415926535,eps=1e-7;
string s;
stack<char>ch;
signed main(){
	io;
	cin>>s;
	for(auto v:s){
		if(v==']'){
			if(ch.size()&&ch.top()=='[')ch.pop();
			else return cout<<"No",0;
		}else if(v==')'){
			if(ch.size()&&ch.top()=='(')ch.pop();
			else return cout<<"No",0;
		}else if(v=='>'){
			if(ch.size()&&ch.top()=='<')ch.pop();
			else return cout<<"No",0;
		}else ch.push(v);
	}
	if(ch.size())cout<<"No";
	else cout<<"Yes";
	return 0;
}
```

---

## 作者：Furina_Saikou (赞：0)

# 题目大意

给定一个字符串 $s$，问 $s$ 中的括号是否正确匹配，即每个每个括号是否有另一个对应的括号，且不出现如 `([)]` 的错误嵌套关系。

# 思路

遍历字符串，并将左括号压入栈，遇到右括号时判断栈顶是否是对应的左括号，遍历完后要判断是否还有没匹配的左括号。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+1;
string s;
map<char,char>m;
int st[N],top;
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>s;
	m[')']='(',m[']']='[',m['>']='<';//确定对应匹配关系
	for(int i=0;i<s.size();++i)
	{
		if(s[i]=='('||s[i]=='['||s[i]=='<')st[++top]=s[i];
		else if(!top||st[top]!=m[s[i]])//判栈空或不是对应的左括号
		{
			cout<<"No";
			return 0;
		}else --top;//能匹配就出栈
	}
	cout<<(top?"No":"Yes");//top=0就代表全部匹配完毕
}
```

---

## 作者：Miracle_1024 (赞：0)

## 解题思路

~~这不就是括号匹配吗~~

首先要确定括号的数量是成双出现，然后可能会出现右括号在左括号前面的情况。这时，我们创建一个记录变量，如果是左括号就 $+1$，如果是右括号就判断其是否为正数，如果是正数就 $-1$ 最后如果是 $0$ 就说明是匹配的。三种不同的括号都可以用这种方法实现。
## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
const int INF=0x3f3f3f3f;
inline int read(){ll x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
string s;
ll st[N],top=-1;
int main(){
    cin>>s;
    for(int i=0;i<s.size();i++){
        if(s[i]=='(')top++,st[top]=1;
        else if(s[i]==')'){
            if(top==-1)top++,st[top]=2;
            else if(st[top]==1)top--;
            else top++,st[top]=2;
        }
        else if(s[i]=='[')top++,st[top]=3;
        else if(s[i]==']'){
            if(top==-1)top++,st[top]=4;
            else if(st[top]==3)top--;
            else top++,st[top]=4;
        }
        if(s[i]=='<')top++,st[top]=5;
        else if(s[i]=='>'){
            if(top==-1)top++,st[top]=6;
            else if(st[top]==5)top--;
            else top++,st[top]=6;
        }
    }
    if(top==-1)cout<<"Yes";
    else cout<<"No";
}
```

---

## 作者：_shine_ (赞：0)

一个括号匹配的升级版。

维护一个栈，同时扫一遍字符串，如果当前扫到的位置为左括号就加入栈中，如果是右括号且与栈顶匹配就弹出栈顶，反之显然不成立（因为一个可以被删干净的序列必定是层层匹配的，即存在位置满足匹配的括号中间没有遮挡，在删去该匹配后仍然如此），最后输出即可。

注意在最后要查看是否栈为空。

```cpp
#include<bits/stdc++.h>
using namespace std;
stack<char>st;
string s;
int check(char ch){
	if(ch=='<' || ch=='>')return 1;
	if(ch=='(' || ch==')')return 2;
	if(ch=='[' || ch==']')return 3;
}
signed main(){
	cin >> s;
	for(int i=0;i<s.size();++i){
//		cout << i;
		if(s[i]=='<' || s[i]=='(' || s[i]=='[')st.push(s[i]);
		else if(s[i]=='>' || s[i]==')' || s[i]==']'){
			if(st.size()==0 || check(s[i])!=check(st.top())){puts("No");return 0;}
			st.pop();
		}else {puts("No");return 0;}
	}
//	cout << st.siz
	if(st.size()!=0)puts("No");
	else puts("Yes");
	return 0;
}

```

---

## 作者：lilong (赞：0)

一个非常经典的套路是把所有括号从左到右压入栈中，如果栈顶能与当前的配对则消去。这样做符合题目中只能消除相邻括号的要求，并保证能消除的立刻消除，从而是正确的。最后判断栈是否为空即可。

时间复杂度 $O(n)$。


```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int a[2000001],tp;

int main()
{
    string s;
    int n;
    cin >> s;
    n = s.size();
    for( int i = 0 ; i < n ; i ++ )
    {
        if( tp == 0 )
        {
            a[++ tp] = i;
            continue;
        }
        if( s[a[tp]] == '(' && s[i] == ')' ) tp --;
        else if( s[a[tp]] == '[' && s[i] == ']' ) tp --;
        else if( s[a[tp]] == '<' && s[i] == '>' ) tp --;
        else a[++ tp] = i;
    }
    if( tp == 0 ) cout << "Yes";
    else cout << "No";
    return 0;
}
```

---

## 作者：bananamilktea (赞：0)

首先可以发现，一个满足条件的括号序列必定会满足以下条件：

- 每个括号都可以与另一个括号配对
- 不存在两对括号交叉的情况

第一个条件很好判断，只需要从左往右扫一遍序列，开三个栈分别记录三种不同种类的括号，如果当前的括号是左括号就将其编号加入与之对应的栈，如果是右括号，当前这个右括号必定与栈顶的左括号匹配，将栈顶元素弹出并记录下这一对括号。如果当前的元素是右括号并且与之对应的栈为空，就说明没有与之配对的左括号，不满足第一个条件，括号序列不合法。

扫完以后，三个栈必定都为空，不然就存在多余的不能匹配上的左括号，同样不满足第一个条件。

前面已经记录了每对括号的编号，现在要开始判断第二个条件是否满足，最直观的方法自然是枚举任意两对括号并判断是否交叉，但显然，时间复杂度是 $O(n^2)$ 的，会超时。尝试枚举一对括号，并二分得到所有左端点在这对括号之间的括号，而这些括号之中右端点的最大值如果超过了枚举出来的括号的右端点，就说明存在交叉的情况，不满足第二个条件。

举个例子，如下图：

```
(<[]<>)>
^!! ! ^
```

以下括号的下标均从 $1$ 开始。

下面两个箭头所标注的是当前枚举出来的一对小括号，而在这对括号之间的左括号用 `!` 表示，可以发现，这三个左括号之中，右端点的位置分别为 $6, 4, 8$，而其中的最大值就是位置为 $8$ 的右尖括号，而这个括号比位置为 $7$ 的右小括号要大，因此出现了交叉的情况。

那么还会存在一个问题，怎么计算这个区间中每对括号的左端点与之对应的右端点的最大值？显然，用 st 表维护区间最大值是一个并不怎么明智的选择，~~但是我想不到更好的了~~。

直接上代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 1, L = 19;

string s;
stack<int> sta[3];  //三个栈，分别存储三种括号的左端点下标
vector<pair<int, int>> br[3];   //存储一对括号的左端点及右端点
int cp[3][2][MAXN], len[3];    //cp是用数组进行存储括号端点，方便二分，len相当于是vector的size
int st[3][L][MAXN];           //st表

int main() {
	cin >> s;
	for(int i = 0; i < s.size(); i++) {  //对不同种类的括号进行分类讨论
		if(s[i] == '(') {   //如果是左括号
			sta[0].push(i);   //对应的栈中加入当前括号的下标
		}
		else if(s[i] == ')') {  //如果是右括号
			if(!sta[0].size()) {  //如果找不到匹配的
				cout << "No";       //不满足第一个条件
				return 0;
			}
			br[0].push_back({sta[0].top(), i});  //找到配对的括号并记录
			sta[0].pop();
		}
		else if(s[i] == '[') {  //同理
			sta[1].push(i);
		}
		else if(s[i] == ']') {
			if(!sta[1].size()) {
				cout << "No";
				return 0;
			}
			br[1].push_back({sta[1].top(), i});
			sta[1].pop();
		}
		if(s[i] == '<') {
			sta[2].push(i);
		}
		else if(s[i] == '>') {
			if(!sta[2].size()) {
				cout << "No";
				return 0;
			}
			br[2].push_back({sta[2].top(), i});
			sta[2].pop();
		}
	}
	if(!sta[0].empty() || !sta[2].empty() || !sta[1].empty()) {   //如果栈不为空，说明栈中仍有未配对的左括号
		cout << "No";
		return 0;
	}
	sort(br[0].begin(), br[0].end());
	sort(br[1].begin(), br[1].end());
	sort(br[2].begin(), br[2].end());
	for(int i = 0; i < 3; i++) {  //将括号存储进数组里，方便二分
		len[i] = br[i].size();
		for(int j = 0; j < br[i].size(); j++) {
			cp[i][0][j + 1] = br[i][j].first, cp[i][1][j + 1] = br[i][j].second;
		}
	}
	for(int i = 0; i < 3; i++) {  //给st表赋初始值
		for(int j = 1; j <= len[i]; j++) {
			st[i][0][j] = cp[i][1][j];
		}
	}
	for(int i = 0; i < 3; i++) {
		for(int j = 1; j < L; j++) {
			for(int k = 1; k <= len[i] - (1 << j) + 1; k++) {
				st[i][j][k] = max(st[i][j - 1][k + (1 << (j - 1))], st[i][j - 1][k]);
			}
		}
	}
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(i == j) {
				continue;
			}
			for(int k = 1; k <= len[i]; k++) {
				int l = lower_bound(cp[j][0] + 1, cp[j][0] + len[j] + 1, cp[i][0][k]) - cp[j][0];
				int r = upper_bound(cp[j][0] + 1, cp[j][0] + len[j] + 1, cp[i][1][k]) - cp[j][0] - 1;  //两次二分算出有哪些括号在枚举出来的括号之间
				if(cp[j][0][l] > cp[i][1][k]) {  //如果没有找到，直接退出
					continue;
				}
				int res = 0;  //用来计算区间内右端点最大值
				int x = l;
				for(int nowl = L; nowl >= 0; nowl--) {
					if((1 << nowl) + l - 1 <= r) {
						res = max(res, st[j][nowl][l]);
						l += (1 << nowl) - 1;
					}
				}
				if(res > cp[i][1][k]) {  //不满足第二个条件直接退出
					cout << "No";
					return 0;
				}
			}
		}
	}
	cout << "Yes";
	return 0;
}
```

---

## 作者：cqbzcjh (赞：0)

彩色括号序列就是所有括号都能配对的序列。

我们用一个栈来维护配对情况：
- 遇到一个左括号或者栈是空的就进栈。
- 遇到一个右括号就判断栈顶能不能和它配对，如果能就弹出。

如果最后栈为空就说明配对成功。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n;
stack<char> st;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>s;n=s.size();s=" "+s;
	for(int i=1;i<=n;i++){
		if(st.empty()||s[i]=='('||s[i]=='['||s[i]=='<')st.push(s[i]);
		else if(st.top()=='('&&s[i]==')')st.pop();
		else if(st.top()=='['&&s[i]==']')st.pop();
		else if(st.top()=='<'&&s[i]=='>')st.pop();
		else st.push(s[i]);
	}
	if(!st.empty())cout<<"No";
	else cout<<"Yes";
	return 0;
}
```

---

## 作者：yr409892525 (赞：0)

## 题解：AT_abc394_d [ABC394D] Colorful Bracket Sequence
使用栈来维护。                 
每次把当前字符加入栈，如果栈顶可以匹配，就弹出栈顶，重复该操作。               
最后判断栈是否为空。                 

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,inf=1e9;
string s;
char a[N];
int t;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>s;
    int n=s.size();
    s=" "+s;
    for(int i=1;i<=n;i++){
        a[++t]=s[i];
        while(t>=2){
            if(a[t]==')' && a[t-1]=='(') t-=2;
            else if(a[t]==']' && a[t-1]=='[') t-=2;
            else if(a[t]=='>' && a[t-1]=='<') t-=2;
            else break;
        }
    }
    if(t) cout<<"No\n";
    else cout<<"Yes";
	return 0;
}
```

---

## 作者：Magus (赞：0)

我们可以用一个栈来维护括号序列。

当要插入栈的字符与栈顶字符相匹配时，不插入字符，同时删除栈顶，操作完后判断这个栈是否为空，如果是那么满足题意输出 `Yes`，否则输出 `No`。时间复杂度 $O(|S|)$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define I using
#define AK namespace
#define NOIP2024 std
I AK NOIP2024;
const int maxn=1e6+10,maxm=1e3+10,mod=998244353;
int n,m,x,y,arr[maxn];
string s;
stack<char>st;
signed main()
{
	cin>>s;
	n=(int)(s.size());
	for(int i=0;i<n;i++)
	{
		if(!st.empty())
		{
			if((s[i]==')' and st.top()=='(') or (s[i]=='>' and st.top()=='<') or (s[i]==']' and st.top()=='['))
			{
				st.pop();
				continue;				
			}
		}
		st.push(s[i]);
	}
	if(st.empty())
	{
		cout<<"Yes";
	}
	else
	{
		cout<<"No";
	}
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

典题。

将每种类型的左括号压入栈中，如果右括号能匹配就出栈，否则肯定不合法，如 `[(])`。

最后如果栈空了就合法，否则不合法。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e5 + 10;
const int M = 4e2 + 10;
const int inf = 1e16;
int T,n;
string s;
stack <char> sta;
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
signed main(){
	close();
	cin >> s;
	n = s.size();
	for (int i = 0 ; i < n ; i++){
		if (s[i] == '<' || s[i] == '(' || s[i] == '['){
			sta.push(s[i]);
		}else{
			if (sta.empty()){ // 栈空也是不合法的
				cout << "No\n";
				return 0;
			}
			int c = sta.top();
			sta.pop();
			if (c == '<' && s[i] == '>') continue;
			if (c == '(' && s[i] == ')') continue;
			if (c == '[' && s[i] == ']') continue;
			cout << "No\n"; // 无法匹配
			return 0;
		}
	}
	if (sta.empty()) cout << "Yes\n"; // 检查栈
	else cout << "No\n";
	return 0;
}
```

---

## 作者：Redshift_Shine (赞：0)

多括号匹配模板题。

在基础括号匹配的基础上利用 map 进行额外的判断即可。

```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#include <chrono>
#else
#define debug(...)
#endif
#include <cstdio>
#include <iostream>
// #include <map>
#include <string>
using namespace std;
const int N = 2e5 + 10;
string s;
int idx;
char stk[N], mp[256];
void run()
{
	cin >> s;
	mp[')'] = '(';
	mp[']'] = '[';
	mp['>'] = '<';
	for (auto &i : s)
	{
		if (!mp[i])
		{
			stk[++idx] = i;
			continue;
		}
		if (stk[idx] != mp[i])
		{
			puts("No");
			return;
		}
		idx--;
	}
	puts(idx ? "No" : "Yes");
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	run();
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

## 作者：_Deer_Peach_ (赞：0)

题意：

给出一个括号序列，每次删除一个括号，删除后把后面的字符串移到前面。

思路：

题目很明显就是让你检验一个括号序列是否是合法的括号序列。称字符串 ```()```，```[]```，```<>``` 为合法括号序列，记为 $A$，则 ```(A)```，```[A]```，```<A>``` 以及 ```AA``` 都为合法序列。

我记得有一道题与这题几乎一模一样，但就是找不到。可以用栈做这道题，如果栈顶与当前字符是合法的括号，则弹出栈顶，否则将当前字符放入栈。

最后判断栈是否为空即可。栈为空则是合法的，否则是不合法的。

```
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
const int N=1e5+5;
string s;
signed main(){
	IOS;cin>>s;
	int len=s.size();
	stack<char>q;
	for(int i=0;i<len;i++){
		if(q.size()>0){
			char x=q.top();
			if((x=='('&&s[i]==')')||(x=='['&&s[i]==']')||(x=='<'&&s[i]=='>'))q.pop();
			else q.push(s[i]);
		}else q.push(s[i]);
	}cout<<(q.empty()?"Yes":"No");
	return 0;
}
```

---

## 作者：Lacuna (赞：0)

简单题。

括号匹配这种题一般用栈来解决，我们只要遇到左括号就入栈，遇到右括号就判断栈顶的左括号是否和这个右括号匹配，若是匹配的话就将左括号出栈。若是不匹配的话就说明不是一个合法的括号序列。最后还要注意判断栈是否为空，防止有多余的左括号。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
char s[N];
stack<char> st; 
string solve(int n){
  for(int i=1;i<=n;i++){
  	if(s[i]=='('||s[i]=='['||s[i]=='<')
  	  st.push(s[i]);
  	else{
  	  if(st.empty()) return "No";
  	  else if(s[i]==')'&&st.top()!='(') return "No";
  	  else if(s[i]==']'&&st.top()!='[') return "No";
  	  else if(s[i]=='>'&&st.top()!='<') return "No";
  	  st.pop();
    }
  }
  if(st.empty()) return "Yes";
  else return "No";
}
int main(){
  scanf("%s",s+1);
  cout<<solve(strlen(s+1))<<endl;
  return 0;
} 
```

---

## 作者：Tjaweiof (赞：0)

# AT_abc394_d 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc394_d)

典题，拿个栈记录。遍历一遍字符串，遇到左括号就加入栈；遇到右括号就看一下栈顶是不是与之对应的，如果是就弹出，否则栈顶与当前字符不对应（或者栈空），直接输出 `No` 并 ~~睡觉~~ 直接结束。到了最后如果栈空，就输出 `Yes`，否则输出 `No`。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
int n;
string s;
stack <int> st;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	n = s.size();
	s = " " + s;
	for (int i = 1; i <= n; i++){
		if (s[i] == '(' || s[i] == '[' || s[i] == '<'){
			st.push(i);
		} else {
			if (!st.empty() && s[st.top()] == s[i] - 2 + (s[i] == ')')){
				st.pop();
			} else {
				cout << "No";
				return 0;
			}
		}
	}
	if (st.empty()){
		cout << "Yes";
	} else {
		cout << "No";
	}
	return 0;
}
```

---

