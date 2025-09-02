# Higher Order Functions

## 题目描述

Helen studies functional programming and she is fascinated with a concept of higher order functions — functions that are taking other functions as parameters. She decides to generalize the concept of the function order and to test it on some examples.

For her study, she defines a simple grammar of types. In her grammar, a type non-terminal $ T $ is defined as one of the following grammar productions, together with $ \textrm{order}(T) $ , defining an order of the corresponding type:

- "()" is a unit type, $ \textrm{order}(\textrm{"}\texttt{()}\textrm{"}) = 0 $ .
- "(" $ T $ ")" is a parenthesized type, $ \textrm{order}(\textrm{"}\texttt{(}\textrm{"}\,T\,\textrm{"}\texttt{)}\textrm{"}) = \textrm{order}(T) $ .
- $ T_1 $ "-&gt;" $ T_2 $ is a functional type, $ \textrm{order}(T_1\,\textrm{"}\texttt{->}\textrm{"}\,T_2) = max(\textrm{order}(T_1) + 1, \textrm{order}(T_2)) $ . The function constructor $ T_1 $ "-&gt;" $ T_2 $ is right-to-left associative, so the type "()-&gt;()-&gt;()" is the same as the type "()-&gt;(()-&gt;())" of a function returning a function, and it has an order of $ 1 $ . While "(()-&gt;())-&gt;()" is a function that has an order-1 type "(()-&gt;())" as a parameter, and it has an order of $ 2 $ .

Helen asks for your help in writing a program that computes an order of the given type.

## 样例 #1

### 输入

```
()```

### 输出

```
0```

## 样例 #2

### 输入

```
()->()```

### 输出

```
1```

## 样例 #3

### 输入

```
()->()->()```

### 输出

```
1```

## 样例 #4

### 输入

```
(()->())->()```

### 输出

```
2```

## 样例 #5

### 输入

```
()->(((()->())->()->())->())```

### 输出

```
3```

# 题解

## 作者：jianhe (赞：3)

由于数据范围比较小，我们考虑暴力递归求权值（当然，用表达式计算也可以）。

按照题目所说：

> 1.$ord(“()”)=0$

> 2.$ord(“(”+S+“)")=ord(S)$

> 3.$ord(S+“->"+T)=max(ord(S)+1,ord(T))$

找到括号后递归即可。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
string s;
ll solve(ll l,ll r){
	if(l>r) return 0;
	ll ct=0;
	for(int i=l;i<=r;i++){
		if(s[i]=='(') ct++;
		if(s[i]==')') ct--;
		if(!ct&&s[i]=='-') return max(solve(l,i-1)+1,solve(i+2,r));
	}
	return solve(l+1,r-1);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>s;
	cout<<solve(0,s.size()-1);
	return 0;
}
```

---

## 作者：hyman00 (赞：3)

## 题意

[链接](https://codeforces.ml/problemset/problem/1578/H)

定义字符串 `S` 权值为 `ord(S)` 。

计算方式为:

1. $ord("()")=0$

2. $ord("("+S+")")=ord(S)$

3. $ord(S+"->"+T)=\max(ord(S)+1,ord(T))$

输入一个字符串，求它的权值。

## 解法

```c++
1	int ord(int l,int r){
2		if(l+1==r)re 0;
3		int cur=0;
4		for(int i=l;i<=r;i++){
5			if(s[i]=='(')cur++;
6			if(s[i]==')')cur--;
7			if(cur==0&&s[i]=='-'){
8				return max(ord(l,i-1)+1,ord(i+2,r));
9			}
10		}
11		return ord(l+1,r-1);
12	}
```

递归即可， `ord(l,r)` 表示输入字符串从 `l` 到 `r` 的子串。

第 2 行处理第 1 种；

第 3-10 行处理第 2 种，
`cur` 确保 `->` 左右字符串都有定义，即 `(` 和 `)` 出现次数一样；

第 11 行处理第 3 种。

---

## 作者：OIer_Hhy (赞：0)

一道水题，只需要递归即可 AC。

因为连续括号嵌套贡献为 $0$，所以我们只需要看 `->` 就行了。当 `s[i]=='-'` 时，答案就是 $\max$ (`->`左边的字符串的贡献+1，`->`右边字符串的贡献)。

my code:

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int dg(int l,int r){
	if(l+1==r)return 0;
	int cur=0;
	for(int i=l;i<=r;i++){
		if(s[i]=='(') cur++;
		else if(s[i]==')') cur--;
		if(cur==0&&s[i]=='-')
			return max(dg(l,i-1)+1,dg(i+2,r));
	}
	return dg(l+1,r-1);
}
signed main(){
	cin>>s;
	cout<<dg(0,s.size()-1)<<endl;
	return 0;
}



```

---

## 作者：endlessdream (赞：0)

题目大意

定义字符串 S 权值为 ord(S) 。
计算方式为:

$ord("()")=0$

$ord("("+S+")")=ord(S)$

$ord(S+"−>"+T)=max(ord(S)+1,ord(T))$

输入一个字符串，求它的权值。

思路来源于小羊肖恩


由题目单个括号即()的权值是为0的于是我们可以把表达式做如下转换

$ ()->(((()->())->()->())->())$
等同于

$0+(((0+0)+0+0)+0)$
这里为了便换成加号

就变成了表达式的计算，遇到后括号的时候就弹出前括号之前的所有运算符进行运算。

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
	string s,a;cin>>s;
	int n=s.size();
	s=s+' ';
	stack<int>stk1;
	stack<char>stk2;
	for(int i=0;i<n;i++){
		if(s[i]=='('&&s[i+1]==')')
			a+='0',i++;
		else if(s[i]=='-'&&s[i+1]=='>')
			a+='+',i++;
		else
			a+=s[i];
	}
	a='('+a+')';
	cout<<a<<"\n";
	int m=a.size();
	for(int i=0;i<m;i++){
		if(a[i]=='0')
			stk1.push(0);
		else if(a[i]=='+'||a[i]=='(')
			stk2.push(a[i]);
		else if(a[i]==')'){
			while(stk2.size()&&stk2.top()!='('){
				int x=0,y=0;
				if(stk1.size()){
					x=stk1.top();stk1.pop();
				}
				if(stk1.size()){
					y=stk1.top();stk1.pop();
				}
				stk1.push(max(x,y+1));//y为前面的数
				stk2.pop();
			}
			if(stk2.size())
				stk2.pop();
		}
	}
	cout<<stk1.top();
	
}

signed main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	int tt=1;
	while(tt--)solve();
}






```

---

