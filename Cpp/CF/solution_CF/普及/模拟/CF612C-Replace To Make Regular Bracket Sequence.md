# Replace To Make Regular Bracket Sequence

## 题目描述

给定一个只含 `>`，`(`，`)`，`{`，`}`，`[`，`]`的字符串。记`<`，`(`，`{`，`[`为左括号，`>`，`)`，`}`，`]`为右括号。每次可以将任意一个左括号换为任意一个不同的左括号，或将任意一个右括号换为任意一个不同的右括号，记为一次操作。求使括号序合法的最小操作次数，若无解，输出 `impossible`。

## 样例 #1

### 输入

```
[&lt;}){}
```

### 输出

```
2```

## 样例 #2

### 输入

```
{()}[]
```

### 输出

```
0```

## 样例 #3

### 输入

```
]]
```

### 输出

```
Impossible```

# 题解

## 作者：Zachary_Cloud (赞：2)

## $\text{Problem}$

- 题目传送门 $\Rightarrow$ [CF612C Replace To Make Regular Bracket Sequence](https://www.luogu.com.cn/problem/CF612C)

- 题目大意

  给你一个只包含 `<`，`>`，`(`，`)`，`{`，`}`，`[`，`]`的字符串 $s$，左括号之间可以互换，右括号之间也可以互换，求最少进行多少次操作才能使 $s$ 合法。若无解，输出 `Impossible`。


## $\text{Solution}$

遍历每个括号，用栈保存在此之前未被匹配到的括号，每次遍历到一个新的括号时：

- 若栈顶为左括号，当前为右括号时：

  - 若两者匹配，则不用操作，可以直接弹出栈顶；
  
  - 若两者不匹配，则可用一次代价使当前二者直接匹配，弹出栈顶。

- 若栈顶为右括号，当前为左括号时，无论怎样操作都无法匹配，直接说明无解，输出 `Impossible`。

- 其余情况压入栈中。

结束时若栈不为空，说明无解，输出 `Impossible`。

考察了对栈的应用。

## $\text{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
stack <char> a;
int ans;
inline bool is_left(char c) {
	if (c=='<'||c=='('||c=='['||c=='{') return 1;
	else return 0;
}
inline bool match(char a,char b){
	if (a=='<'&&b=='>') return 1;
	if (a=='{'&&b=='}') return 1;
	if (a=='['&&b==']') return 1;
	if (a=='('&&b==')') return 1;
	return 0;
}
signed main() {
	cin>>s;
	for (int i=0;i<s.size();++i) {
		if (is_left(s[i])) a.push(s[i]);
		else {
			if (a.empty()||!is_left(a.top())) {
				cout<<"Impossible"<<endl;
				return 0;
			} else {
				if (!match(a.top(),s[i])) ans++;
				a.pop();
			}
		}
	}
	if (!a.empty()) cout<<"Impossible"<<endl;
	else cout<<ans;
	return 0;
}
```

---

## 作者：IOI_AK_LHY (赞：1)

## 前言

[题目传送门](https://www.luogu.com.cn/problem/CF612C)。

[在博客内食用效果更佳](https://www.luogu.com.cn/blog/lihangyu-749988/solution-cf612c)！

## 题目分析

这题利用了栈的先进后出，我们可以用一个栈来储存左括号，一旦有右括号与之匹配，就把它从栈移出去，然后最后再看没有匹配到的，这些就是需要换成其他括号的。

如果匹配完后栈里还剩有括号不能被搭配的话，那就要输出 `Impossible` 了。

时间复杂度为 $O(n)$。

## 代码实现

```cpp
#include<iostream>
#include<stack>
using namespace std;
int n,ans;
string s;
stack<char> stk;
bool flag1(char a){ //是否是左括号
	if(a=='<'||a=='('||a=='['||a=='{')
		return true;
	return false;
}
bool flag2(char a,char b){ //是否是右括号
	if(a=='<'&&b=='>'||a=='('&&b==')'||a=='['&&b==']'||a=='{'&&b=='}')
		return true;
	return false;
}
int main(){
    cin>>s;
    n=s.size();
    for(int i=0;i<n;i++){
        if(stk.empty()||flag1(s[i])){ //左括号，或者没法匹配，直接进栈
            stk.push(s[i]);
            continue;
        }
        else{ //尝试匹配
            char c=stk.top();
            if(flag1(c)){
                if(!flag2(c,s[i]))
                	ans++;
                stk.pop();
            }
            else stk.push(s[i]);   
        }
    }
    if(!stk.empty()){ //堆不是空的，匹配不完
        cout<<"Impossible";
        return 0;
    }
    cout<<ans;
    return 0;
}
```

希望能帮助到大家！

---

## 作者：linyihdfj (赞：0)

## C.Replace To Make Regular Bracket Sequence ##
[博客食用效果更佳](https://www.cnblogs.com/linyihdfj/p/16419311.html)
### 题目描述： ###
[原题面](https://codeforces.com/contest/612/problem/C)
### 题目分析： ###
最小的操作次数当然就是将不合法的匹配变为合法的匹配所需要花费的次数，也就是不合法的匹配的数量。

那么我们就做一遍括号匹配然后出现不合法的就答案加一并让这对合法就好了。
### 代码详解： ###

```
#include<bits/stdc++.h>
using namespace std;
bool zuo(char a){
	return a == '<' || a == '{' || a == '(' || a == '[';
}
bool you(char a){
	return a == '>' || a == '}' || a == ')' || a == ']';
}
bool check(char a,char b){
	return (a == '<' && b == '>') || (a == '{' && b == '}') || (a == '(' && b == ')') || (a == '[' && b == ']'); 
}
int main(){
	int ans = 0;
	string s;
	cin>>s; 
	stack<char> st;
	for(int i=0; i<s.size(); i++){
		if(!st.empty() && zuo(st.top()) && you(s[i])){
			if(!check(st.top(),s[i])){
				ans++;
			}
			st.pop();
		}
		else{
			st.push(s[i]);
		}
	}
	if(!st.empty()){
		printf("Impossible\n");
	}
	else{
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：hxhhxh (赞：0)

## 大意

给你一个长度为 $ n $ 的字符串 $ S $ 只包含`<`、`>`、`(`、`)`、`[`、`]`、`{`、`}`，左括号之间可以互换，右括号之间也可以互换，求最少进行多少次操作才能使 $ S $ 合法。

左括号指`<`、`(`、`[`、`{`；

右括号指`}`、`>`、`)`、`]`。

## 思路

用`stack`。每一次遇到左括号就直接压入，遇到右括号时需要进行一些判断：

+ 栈为空，不可能合法，`Impossible`；
+ 栈顶元素与当前括号匹配，弹出栈顶元素（与当前括号直接匹配）；
+ 栈顶元素与当前括号不匹配，将当前括号变成与之前括号匹配的括号，答案`++`。

如果结束之后栈不为空，`Impossible`。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch[1000006];
int n,m,T,ans;
stack<char>st;
int fl(char ch){
	if(ch=='('||ch=='<'||ch=='['||ch=='{') return 1;
	return 2;
} 
int main(){
	scanf("%s",ch+1);
	n=strlen(ch+1);
	for(register int i=1;i<=n;++i){
		int nw=fl(ch[i]);
		if(nw==1||st.empty()) st.push(ch[i]);
		else{
			char lc=st.top();
			int lst=fl(lc);
			if(lst==2) st.push(ch[i]);
			else{
				if(!((ch[i]==')'&&lc=='(')||(ch[i]=='>'&&lc=='<')||(ch[i]==']'&&lc=='[')||(ch[i]=='}'&&lc=='{'))) ans++;
				st.pop();
			}
		}
	}
	if(st.size()) cout<<"Impossible";
	else cout<<ans;
	return 0;
}
```

---

## 作者：djh233 (赞：0)

**题意：**

当一个只包含字符 ```<>, {}, [], ()``` 的字符串满足以下条件**之一**时，则该字符串被称为 RBS 。

- 该字符串是空串。
- 形如 ```<s1>s2```，且 ```s1,s2``` 是RBS。
- 形如 ```(s1)s2```，且 ```s1,s2``` 是RBS。
- 形如 ```{s1}s2```，且 ```s1,s2``` 是RBS。
- 形如 ```[s1]s2```，且 ```s1,s2``` 是RBS。

现在给定一个只包含字符 ```<>, {}, [], ()``` 的字符串 $s$ ，其中 ```<,(,[,{``` 可以互相替换（即左括号可以互相替换），```>,),],}``` 也可以互相替换（即右括号可以互相替换），问至少替换多少次可以使得 $s$ 成为 RBS 。

如果不可能通过替换使得 $s$ 成为 RBS ，则输出 ```Impossible``` 。

**数据范围：** $1\le|s|\le 10^6$ 。

**做法：**

我们先定义括号 ```<>,(),[],{}``` 是匹配的。维护一个括号栈，每次看**当前括号**是否为**右括号**，若是，则检查与**栈顶括号**是否为**左括号**，若是，则检查是否匹配，若匹配，则**弹出栈顶括号**，若不匹配，则计数器加 $1$ 。

其他情况直接把当前括号 $\operatorname{push}$ 到栈顶即可。

若最后栈非空，则输出 ```Impossible``` ,否则直接输出计数器的值即可。

**时间复杂度：** $O(|s|)$ 。

$Code:$

```cpp
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    string s;
    cin>>s;
    int n=s.length();
    s=' '+s;

    stack<char> st;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(st.empty() || s[i]=='{' || s[i]=='(' || s[i]=='[' || s[i]=='<')
        {
            st.push(s[i]);
            continue;
        }
        else
        {
            char ch=st.top();
            if(ch=='{' || ch=='(' || ch=='[' || ch=='<')
            {
                if((ch=='{' && s[i]=='}') || (ch=='(' && s[i]==')') || (ch=='[' && s[i]==']') || (ch=='<' && s[i]=='>')) ;
                else ans++;
                st.pop();
            }
            else st.push(s[i]);   
        }
    }
    if(!st.empty())
    {
        puts("Impossible");
        return ;
    }
    printf("%d",ans);
}

int main()
{
    solve();
    return 0;
}

---

