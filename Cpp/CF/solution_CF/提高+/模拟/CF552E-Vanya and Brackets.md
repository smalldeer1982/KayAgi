# Vanya and Brackets

## 题目描述

Vanya正在认真地做他的数学作业，他碰到了一个长度为N的序列，构成序列的元素都在1~9之间，并且各个元素由加号和等号构成了一个式子。


Vanya现在需要通过增加一组小括号来改变运算顺序（运算优先级，括号>乘法>加法）。

## 说明/提示

其中式子元素个数小于等于5001。

## 样例 #1

### 输入

```
3+5*7+8*4
```

### 输出

```
303
```

## 样例 #2

### 输入

```
2+3*5
```

### 输出

```
25
```

## 样例 #3

### 输入

```
3*4*5
```

### 输出

```
60
```

# 题解

## 作者：穼柗° (赞：5)

#### 温馨提示：在[专栏](https://www.luogu.com/article/9vs2rkpe)食用效果更佳。

一定是在乘号两端或者开头增加括号，才可能使得答案变得更大。题目保证了乘号个数不超 $15$，所以可以枚举左右括号的位置。
### Code
```cpp
#include <iostream>
#include <stack>
#define ll long long
using namespace std;
short pri[128]; // 优先级数组
string s;
stack<ll> nums;
stack<char> ops;
inline void init(void) { // 初始化优先级数组
	pri['+']=pri['-']=1,
	pri['*']=pri['/']=pri['%']=2;
}
inline void eval(void) {
	register ll a=nums.top(); nums.pop();
	register ll b=nums.top(); nums.pop();
	register const char op=ops.top(); ops.pop();
	if(op=='+') nums.push(b+a);
	else if(op=='*') nums.push(b*a);
	else if(op=='-') nums.push(b-a);
	else if(op=='/') nums.push(b/a);
	else if(op=='%') nums.push(b%a);
}
ll calc(string &s) { // 计算表达式值
	while(!nums.empty()) nums.pop();
	while(!ops.empty()) ops.pop();
	ll val=0;
	ops.push('('),s+=')';
	for(int i=0;i<s.size();i++)
		if(s[i]>='0'&&s[i]<='9') {
			val=s[i]-'0';
			while(i+1<s.size()&&s[i+1]>='0'&&s[i+1]<='9')
				val=(val<<1)+(val<<3)+s[++i]-48;
			nums.push(val);
		} else if(s[i]=='(')
			ops.push(s[i]);
		else if(s[i]==')') {
			while(ops.top()!='(')
				eval();
			ops.pop();
		} else {
			while(!ops.empty()&&pri[ops.top()]>=pri[s[i]])
				eval();
			ops.push(s[i]);
		}
	s.erase(s.size()-1,1);
	return nums.top();
}
ll ans,flg;
string tmp;
int main() {
	ios::sync_with_stdio(false),
	cin.tie(nullptr),
	cout.tie(nullptr),
	init();
	cin>>s;
	const string fuben=s;
	for(int i=0;i<s.size();s=fuben,i++) // 枚举
		if(s[i]=='*'||!i) {
			if(i) s.insert(i+1,"(");
			else s.insert(i,"(");
			tmp=s;
			for(int j=i+1;j<s.size();s=tmp,j++)
				if(s[j]=='*'||j==s.size()-1) {
					flg=0;
					if(j!=s.size()-1) s.insert(j,")");
					else s.insert(j+1,")");
					ans=max(ans,calc(s));
				}
		}
	cout<<ans;
	return 0;
}
```

#### 注：禁止抄代码！

---

## 作者：如履薄冰 (赞：4)

# 思路
这道题涉及到了表达式求值，建议学完栈再来看本题解。我们发现将括号插在一个数乘另一个数的式子上，比如将 $a \times b$ 改成 $(a \times b)$，并不会改变这个式子的值，因为乘号在没有括号的情况下是最优先的。因此我们只考虑把括号插在其他地方。经过推断，我们发现将括号插在**两个乘号**之间才是最优的。由于乘号最多也就 $15$ 个，我们暴搜括号放置的位置，将每次枚举出来的表达式算出来，拿一个变量维护我们枚举出来的最大值，最后再输出这个变量即可。

---

## 作者：jianhe (赞：3)

可以发现，括号插在两个乘号之间时最优。

根据英文题面，我们发现乘号个数不会超过 $15$ 个，因此我们枚举两个乘号的位置，暴力插入括号并计算。

写时有些细节要注意，为避免分类讨论，可以在整个式子前加左括号。注意右括号在整个式子后的情况。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=5010;
ll ct,x[N],ans;
string s,t1,t2;
stack<ll> num;
stack<char> op;
bool Dig(char c){return '0'<=c&&c<='9';}
void J(){
	ll a=num.top();num.pop();
	ll b=num.top();num.pop();
	ll c=0;
	char p=op.top();op.pop();
	if(p=='+') c=a+b;
	if(p=='*') c=a*b;
	num.push(c);
}
ll calc(){//计算表达式的值
	while(!num.empty()) num.pop();
	while(!op.empty()) op.pop();
	op.push('('),s+=')';
	for(int i=0;i<s.size();i++){
		if(Dig(s[i])) num.push(s[i]-'0');
		else if(s[i]=='(') op.push(s[i]);
		else if(s[i]==')'){
			while(op.top()!='(') J();
			op.pop();
		}else{
			while(!op.empty()&&op.top()!='('&&(s[i]=='+'||op.top()=='*')) J();
			op.push(s[i]);
		}
	}
	return num.top();
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>s;t1=s;x[0]=-1;//在整个式子前加乘号
	for(int i=0;i<s.size();i++)
		if(s[i]=='*') x[++ct]=i;//预处理乘号位置
	for(int i=0;i<=ct;i++,s=t1){
		s.insert((x[i]+1),"(");t2=s;
		for(int j=i+1;j<=ct+1;j++,s=t2)
			s.insert((j<=ct?x[j]+1:s.size()),")"),ans=max(ans,calc());
            //注意右括号在整个式子后的情况
    }
	cout<<ans;
	return 0;
}
```

---

## 作者：__DICS (赞：2)

## 题意

给你一个只含有+和\*和数字的表达式，你可以在里面放置一对括号，位置随意。

要求放置括号之后，表达式所得的结果最大。

求出这个最大值。

## 解

在一段连续的加号中增加一对括号显然不会对答案产生任何影响。

所以一定是在乘号两端增加括号，才可能使得答案变得更大。

注意到至多只有15个乘号，所以可以枚举左右括号的位置。

剩下的就是在加入括号后求值的问题了，如果用c++的话可以手写一个表达式求值的函数，相比之下python会方便一些，调用`eval()`即可对表达式求值。

**注意考虑括号在最左端或最右端的情况。**

## AC代码(python 3)

```python
# coding: utf-8
expr = list(input())
mul_pos = [-1]
add_cnt = [0] * len(expr)
for i, _ in enumerate(expr):
    add_cnt[i] = add_cnt[i - 1]  # don't worry about add_cnt[-1] ;)
    if _ == '*':
        mul_pos.append(i)
    elif _ == '+':
        add_cnt[i] += 1
mul_pos.append(len(expr))
add_cnt.append(add_cnt[-1])
add_cnt.append(0)
ans = 0
for i in range(len(mul_pos)):
    for j in range(i + 1, len(mul_pos)):
        if add_cnt[mul_pos[i]] - add_cnt[mul_pos[j]]:
            expr.insert(mul_pos[i] + 1, '(')
            expr.insert(mul_pos[j] + 1, ')')
            # print(''.join(expr))
            ans = max(ans, eval(''.join(expr)))
            expr.pop(mul_pos[j] + 1)
            expr.pop(mul_pos[i] + 1)
print(eval(''.join(expr)) if ans == 0 else ans)
```

代码中的add_cnt是前缀和数组，用来记录加法符号个数的前缀和。

增加这个是为了剪枝。如果一段括号区间内没有加法符号的话，显然增加这个括号并不会对答案产生任何影响。

mul_pos记录了所有乘法符号的下标，在枚举括号位置时使用。

第一次写题解，如果有写的不清楚的地方还请见谅。

---

## 作者：lovely_AKCode (赞：1)

## 题目大意

> Vanya 可以增加一组小括号来改变运算顺序，求改变后的最大值，只能加一组小括号。

## 题目思路：

>如果输入的字符串 $a$ 是只有数字和乘号，可以直接输出求中缀表达式的值。

>由于左括号没必要出现加号的右边，所以左括号只能出现在乘号右边或整个表达式最左边。如果满足 $i$ 是 $0$，或 $a_i$ 是乘号，才能计算。同样，由于右括号没必要出现加在加号左边，所以右括号只能出现在乘号右边或表达式最右边。暴力枚举左右括号的位置，在计算表达式的值，求最大值就好了。

## 代码参考

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string a;
int n,m; 
int cur,ans;
int expr();
int factor(){
	int res=0;
	if (a[cur]=='(') {
		cur++;
		res=expr();
		cur++;
	}
	else{
		while(true){
			if(a[cur]>='0'&&a[cur]<='9') {
				res=res*10+a[cur]-'0';
				cur++;
			}
			else break;
		}
	}
	return res;
}
int term(){
	int res=factor();
	while(true){
		if(a[cur]=='*'){
			cur++;
			res=res*factor();
		}
		else if(a[cur]=='/'){
			cur++;
			res=res/factor();
		}
		else break;
	}
	return res;
}
int expr(){
	int res=term();
	while(true){
		if(a[cur]=='+'){
			cur++;
			res=res+term();
		}
		else if(a[cur]=='-'){
			cur++;
			res=res-term();
		}
		else break;
	}
	return res;
}
signed main(){
	cin>>a;
	string b=a;
	if(a.find('+')==a.npos) cout<<expr(),exit(0);
	for(int i=0;i<a.size();i++){
		if(i==0||a[i]=='*'){
			if(i!=0)a.insert(i+1,"(");
			if(i==0) a.insert(i,"(");
			string c=a;
			for(int j=i+1;j<a.size();j++){
				if(a[j]=='*'||j==a.size()-1) {
					if(j==a.size()-1)a.insert(j+1,")");
					else a.insert(j,")");
					cur=0;
					int sum=expr();
					ans=max(ans,sum);
					a=c;
				}
			}
		}
		a=b;
	}
	cout<<ans;
}
```



---

## 作者：xvl_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF552E)

一道枚举题。

枚举左括号和右括号的位置括号，为了答案最优，左括号只能在开头或者 `*` 的右边。右括号只能在末尾或者 `*` 的左边。每一次枚举都计算一下这个加了括号后表达式的值，最后取最大值即可。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
string s, backup1;
ll ans, cur;
ll facrot();
ll term();
ll expr();
ll factor() {
    ll res = 0;
    if (s[cur] == '(') {
        cur++;
        res = expr();
        cur++;
    }
    else {
        while (1) {
            if (s[cur] >= '0' and s[cur] <= '9') {
                res = (res * 10 + s[cur] - '0');
                cur++;
            }
            else break;
        }
    }
    return res;
}
ll term() {
    ll res = factor();
    while (1) {
        if (s[cur] == '*') {
            cur++;
            res = res * factor();
        }
        else if (s[cur] == '/') {
            cur++;
            res = res / factor();
        }
        else break;
    }
    return res;
}
ll expr() { // 表达式求值
    ll res = term();
    while (1) {
        if (s[cur] == '+') {
            cur++;
            res += term();
        }
        else if (s[cur] == '-') {
            cur++;
            res -= term();
        }
        else break;
    }
    return res;
} 
signed main() {
    ios :: sync_with_stdio(0);
    cin >> s;
    backup1 = s;
    for (ll i = 0; i < s.size(); i++) {
        if (s[i] == '*' or i == 0) {
            if (i != 0) s.insert(i + 1, "(", 0, 1);
            else s.insert(i, "(", 0, 1);
            string backup2 = s;
            for (ll j = i + 1; j < s.size(); j++) {
                if (s[j] == '*' or j == s.size() - 1) {
                    cur = 0;
                    if (j != s.size() - 1) s.insert(j, ")", 0, 1);
                    else s.insert(j + 1, ")", 0, 1);
                    ans = max(ans, expr());
                }
                s = backup2;
            }
        }
        s = backup1;
    }  
    cout << ans;
    return 0;
}


```


---

## 作者：Nozebry (赞：1)

## $Problems$
给定一个不带括号的表达式，现在要你增加一组小括号，使得这个表达式的值最大。
## $Answer$
$1.$ 其实我们不难发现，将括号加在两 $+$ 中间，最终结果没有改变；将括号加在 $+$ 和 $*$ 之间，可使结果变大，但不一定最优；只有当括号加在两 $*$ 之间时，结果是最大。

$2.$ 题目规定了 $*$ 不会超过 $15$ 个，所以可直接枚举两个称号的位置来确定左右括号的位置，然后将左右括号带入算式，求出算式的值，比较一下是不是最大值即可。

---

## 作者：FISH酱 (赞：0)

## 前置知识铺垫

因为这题有表达式求值，所以学会了之后做本题会更轻松，可参考 [P1981 表达式求值](https://www.luogu.com.cn/problem/P1981)。

## 大体思路讲解

题目意思很简单，希望增加一对括号，并改变式子的运算顺序，假设我们把一个乘法算式 $x \times y$ 改为 $(x \times y)$ ，显而易见，运算顺序还是一样的，没有达到预期效果，尝试后我们可以发现规律，括号插在两个乘号之间时最优，举个例子， $x \times y + q \times w$ 修改为 $x \times (y + q) \times w$ 后，运算结果是最大，符合题意。已知乘号数量小于等于 $15$ 个，那么我们何必去想那么多，直接对表达式的字符串暴搜，每搜索到一次加号就加一对括号，加完以后表达式求值，得到值后与当前最大值比较，更新即可，最后输出最大值就能成功通过本题。

---

## 作者：lovely_AKCode (赞：0)


## 题目思路：

>如果输入的字符串 $a$ 是只有数字和乘号，可以直接输出求中缀表达式的值。

>左括号只能出现在乘号右边或整个表达式最左边，右括号只能出现在乘号右边或表达式最右边。暴力枚举左右括号的位置，在计算表达式的值，求最大值就好了。

## 代码参考

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string a;
int n,m; 
int cur,ans;
int expr();
int factor(){
	int res=0;
	if (a[cur]=='(') {
		cur++;
		res=expr();
		cur++;
	}
	else{
		while(true){
			if(a[cur]>='0'&&a[cur]<='9') {
				res=res*10+a[cur]-'0';
				cur++;
			}
			else break;
		}
	}
	return res;
}
int term(){
	int res=factor();
	while(true){
		if(a[cur]=='*'){
			cur++;
			res=res*factor();
		}
		else if(a[cur]=='/'){
			cur++;
			res=res/factor();
		}
		else break;
	}
	return res;
}
int expr(){
	int res=term();
	while(true){
		if(a[cur]=='+'){
			cur++;
			res=res+term();
		}
		else if(a[cur]=='-'){
			cur++;
			res=res-term();
		}
		else break;
	}
	return res;
}
signed main(){
	cin>>a;
	string b=a;
	if(a.find('+')==a.npos) cout<<expr(),exit(0);
	for(int i=0;i<a.size();i++){
		if(i==0||a[i]=='*'){
			if(i!=0)a.insert(i+1,"(");
			if(i==0) a.insert(i,"(");
			string c=a;
			for(int j=i+1;j<a.size();j++){
				if(a[j]=='*'||j==a.size()-1) {
					if(j==a.size()-1)a.insert(j+1,")");
					else a.insert(j,")");
					cur=0;
					int sum=expr();
					ans=max(ans,sum);
					a=c;
				}
			}
		}
		a=b;
	}
	cout<<ans;
}
```



---

