# Down with Brackets

## 题目描述

在 2077 年，机器人决定一劳永逸地摆脱平衡括号序列！

一个括号序列被称为**平衡的**，如果它可以通过以下形式文法构造：

1. 空序列 $\varnothing$ 是平衡的。
2. 如果括号序列 $A$ 是平衡的，那么 $\mathtt{(}A\mathtt{)}$ 也是平衡的。
3. 如果括号序列 $A$ 和 $B$ 是平衡的，那么拼接序列 $A B$ 也是平衡的。

你是对抗平衡括号序列部门的负责人，你的主要任务是确定哪些括号可以被销毁，哪些不能。

给定一个由字符串 $s$ 表示的平衡括号序列，仅包含字符 `(` 和 `)`。由于机器人的能力有限，它们只能从字符串中**恰好删除一个左括号和一个右括号**。

你的任务是判断机器人是否能删除这样两个括号，使得字符串 $s$ **不再**是一个平衡括号序列。

## 说明/提示

在第一个测试用例中，可以证明机器人无法破坏正确的括号序列。

在第二个测试用例中，一种可行的括号删除方式如下：  
$\texttt{(())}{\color{red}\texttt{(}}\texttt{)(}{\color{red}\texttt{)}} \rightarrow \texttt{(()))(}$，结果不是一个正确的括号序列。

在第四个测试用例中，一种可行的删除方式如下：  
$\texttt{(}{\color{red}\texttt{(}}\texttt{))((}{\color{red}\texttt{)}}\texttt{)}\rightarrow \texttt{())(()}$，结果不是一个正确的括号序列。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
(())
(())()()
()
(())(())```

### 输出

```
NO
YES
NO
YES```

# 题解

## 作者：TB__QGSS__423 (赞：2)

# 思路
首先，我们分出两种情况：

1. 形如 `()()`，由多个平衡括号序列并排在一起。
2. 形如 `(())`，只有一个大的平衡括号序列。

那么我们观察，第一种情况显然可以成功，只需要删成 `)(` 即可（就是删掉最左边和最右边）。但是第二种就不行，无论删掉哪两个，都会重新组成一个新的。

实现就很简单了，用一个栈储存，如果是 `(` 就入队，是 `)` 就删去栈顶（可以证明这样操作栈顶一定是 `(` 的）。最后看整个字符串扫完之前栈是否能为空，是的话就输出 `YES`，否则输出 `NO`。

# Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
int t;
int main()
{
	cin>>t;
	while(t--){
		string a;
		cin>>a;
		stack<char> s;
		bool fl=1;
		for(int j=0; j<a.size(); j++){
			if(a[j]=='('){
				s.push(a[j]);
			}else{
				s.pop();
				if(s.empty() && j!=a.size()-1){
					cout<<"YES"<<endl;
					fl=0;
					break;
				}
			}
		}
		if(fl) cout<<"NO"<<endl;
	}
    return 0;
}
```

---

## 作者：Zskioaert1106 (赞：2)

题目传送门：[CF2110B Down with Brackets](https://www.luogu.com.cn/problem/CF2110B)

对于一个右括号，如果以它为右端点的前缀括号串是一个合法的括号序列，那么删除其中的一个左括号一定使得括号序列不合法。

只要此时它的右边还有东西，则一定是另一个合法括号串。那我们把最右边的 `)` 也删掉就行了。

否则呢，就是形如 `((()))` 的，一定无法删除一左一右使得其不平衡。

### 代码实现

```cpp
#include<iostream>
using namespace std;
bool solve(string s){
	int sum=0,ans=0;
	for(int i=0;i<s.size();i++){
		if(s[i]=='(')sum++;
		else{
			if(!--sum&&i<s.size()-1)return 1;
		}
	}
	return 0;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		string s;
		cin>>s;
		cout<<(solve(s)?"YES":"NO")<<'\n';
	}
	return 0;
}
```

[AC on CF](https://codeforces.com/contest/2110/submission/321643527)。

---

## 作者：yulinOvO (赞：1)

### 题意
给定一个合法的括号序列，能否删除一个左括号和一个右括号，使得剩下的序列不合法？能输出 `YES`，否则输出 `NO`。
### 思路
- 如果原括号序列是全左括号在前 + 全右括号在后，删除任意一对匹配的括号后仍平衡，输出 `NO`。
- 否则总能找到一对括号，删除后破坏平衡，输出 `YES`。
- 特别的是，长度为 $2$ 的括号序列，删除后为空（视为平衡），直接输出 `NO`。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
void solve()
{
    string s;
    cin >> s;
    int n=s.size();
    if(n==2)
    {
        cout << "NO\n";
        return ;
    }
    bool flag=1;
    for(int i=0;i<n/2;i++)
    {
        if(s[i]!='(')
        {
            flag=0;
            break;
        }
    }
    if(flag) cout << "NO\n";
    else cout << "YES\n";
}
int main()
{
    int T;
    cin >> T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：Bobi2014 (赞：0)

这道题非常~~可爱~~。

### 前置知识

- [栈](https://oi.wiki/ds/stack/)

### 思路

考虑把这个序列删头删尾，因为除了整个序列是由一对括号包起来的情况，都能使一个左括号和一个右括号失去配对的括号，所以在除了整个序列是由一对括号包起来的情况下是最优的，删头删尾后再判断是否是不平衡的。

在考虑整个序列是由一对括号包起来的情况，这种情况其实无法删成不平衡的括号序列，因为如果使得中间的括号不平衡，那么两边的括号就会来补救，比如 `(()())`，删掉中间的括号后变成 `(())`，如果删两边的，中间的括号序列依旧是平衡的。

时间复杂度 $O(t \times |s|)$。

---

## 作者：MattL (赞：0)

## 题意
$T$ 次询问，每次询问合法括号序列 $S$ 删除首尾括号后是否仍合法。合法输出 `NO`，不合法输出 `YES`。
## 分析
结论：对于任意的括号序列 $|S|$，其合法的充要条件为 $\forall 1\leq i\leq |S|,L_i\geq R_i$，其中 $L_i,R_i$ 分别表示前 $i$ 个字符中 `(`、`)` 的数量。

证明：我们试图使用数学归纳法来证明。

- 对于空序列，显然是一个合法的序列。
- 对于嵌套前缀括号序列 $S$，形如 `((()))`，显然 $L_i=R_i$ 且 $\forall 1\leq i\leq |S|,L_i\geq R_i$。
- 当合法括号序列并列时，形如 `(())(())()`，显然有 $L_i\geq R_i$， 因为可以将一个个前缀嵌套括号序列拆出来，$L_j=R_j$，故不影响。
- 当合法括号序列 $S$ 外面套一个括号时，在 $S'=(S)$ 中 $\forall 1\leq i \leq |S'|-1,L'_i=L_{i-1}+1,R'_i=R_{i-1}$，因为有 $L_i\geq R_i$，故 $L'_i=L_{i-1}+1\geq R'_i=R_{i-1}$。$i=|S'|$ 时，因为 $S'$ 是个合法括号序列，故显然 $L_{|S'|}=R_{|S'|}$。
- 合法括号序列只能由并列于嵌套两种方法构造，故证毕。

以上证明是根据合法括号序列的构造方式来的，故必要性与充分性都得证：

---
有了这个结论后，我们只需要判断 $S_{2\sim |S|-1}$ 是否合法即可，即判断是否 $\exist 2\leq i\leq |S|-1,L_i<R_i$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ls (now<<1)
#define rs (now<<1|1)
#define LL long long
#define f(i,n) for(int i=1;i<=n;i++)
#define f_(i,n) for(int i=n;i>=1;i--)
#define ff(i,a,b) for(int i=a;i<=b;i++)
#define ff_(i,a,b) for(int i=a;i>=b;i--)
#define pi pair<int,int>
#define pb push_back
#define vi vector<int>
#define yes cout<<"Yes"<<endl
#define no cout<<"No"<<endl
#define fs(i,s) for(int i=0;i<s.size();i++)
#define re return
#define con continue
#define bre break
#define mkp make_pair
#define umap unordered_map
#define ld long double
const int N=2e6+10;
int n,a[N];
string s;
int cnt;
void solve(){
	cnt=0;
	cin>>s;
	for(int i=1;i<s.size()-1;i++){
		if(s[i]==')'&&!cnt){
			yes;re;
		}
		if(s[i]=='(')cnt++;
		else cnt--;
	}no;
}
int main(){
//    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
	while(T--)
        solve();
    return 0;
}
```

---

## 作者：yangduan_ (赞：0)

## 思路
因为一个平衡括号序列中每一个左括号都有一个对应的右括号，所以我们只需要想办法让至少一个左括号没有对应的右括号。又因为保证所给的括号是平衡括号序列，所以括号最左边一定是左括号，最右边一定是右括号。由于我们要让对应的括号减少，所以我们需要删去能对应括号最多的左括号和右括号，因此删去最左边和最右边是最优解，最后判断一下剩下的序列即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 200020
int t;
char a[N];
stack<char> st;
signed main(){
	int i,j;
	cin>>t;
	while(t--){
		cin>>(a+1);
		int l=strlen(a+1);
		if(l==2){
			cout<<"NO"<<endl;
			continue ;
		}
		while(!st.empty()) st.pop();
		for(i=2;i<l;i++){
			if(!st.empty()&&a[i]==')'&&st.top()=='('){
				st.pop();
			}else{
				st.push(a[i]);
			}
		}
		if(st.empty()){
			cout<<"NO"<<endl;
		}else{
			cout<<"YES"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Aeyone (赞：0)

## B. Down with Brackets
贪心、构造
#### 题意
给出一个括号序列，问你能不能通过删除一个左括号和一个右括号，使得该括号序列中的括号存在一对括号不匹配，比方说 `(())()()→(()))(`。
#### 做法
我们可以把一个匹配的括号序列视为一个栈，当栈空的时候代表这个匹配的括号序列结束。如果删除栈内的任意一对括号，那么对整个栈来说没有任何影响，相当于少插入了一次和少弹出了一次，如果我们删除的括号一个在前一个栈中，一个在后一个栈中，那么一定会对这两个栈造成影响（被删掉左括号的栈会多出一个右括号，被删掉右括号的相反），那么答案就很显然了，就是看答案给的括号序列是不是一整个栈，而不是多个相连的栈。\
tips：做括号匹配题的固定套路：将左括号视为 1，右括号视为 -1，求前缀和数组 $s$，那么 $s_i=0$ 时为栈已经清空。
#### Code
```C++
#include <bits/stdc++.h>
using namespace std;

void solve() {
	string ss;
	cin >> ss;
	int n = ss.size();
	ss = " " + ss;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		if (ss[i] == '(')
			a[i] = 1;
		else
			a[i] = -1;
	}
	vector<int> s(n + 1);
	bool ok = false;
    //这里跳过了最后一个位置，因为题目给的括号序列一定匹配，所以最后一个位置一定是0
	for (int i = 1; i < n; i ++)
		s[i] = s[i - 1] + a[i], ok |= (s[i] == 0);
    

	if (ok)
		cout << "YES" << '\n';
	else
		cout << "NO" << '\n';

}

signed main() {
//	freopen("data.in", "r", stdin), freopen("data.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr);
	int _;
	cin >> _;
	while (_ --)
		solve();
}
```

---

## 作者：linch (赞：0)

## Problem
给出一个合法的括号序列，必须删除一个左括号和一个右括号，问删除后能否使其变为不合法括号序列。

## Solution
回顾括号匹配算法，记录剩余未被匹配的左括号数，如果遇到一个右括号时，左括号数量为 $0$，即没有左括号与它匹配，那么就不是合法括号序列。

考虑在每个位置时未匹配的左括号数。如果存在一个中间位置，匹配后剩余待匹配左括号数恰好为 $0$，那么我们可以删除开头的左括号，就让它变成 $-1$ 了，是不合法的序列。有括号就删最后一个，对前面没有影响。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+10;
int t, n;
string s;
bool check() {
	int top = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == '(') {
			top++;
		}
		if (s[i] == ')') {
			top--;
		}
		if (i < n - 1 && top == 0) return true;
	}
	return false;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--) {
		cin >> s;
		n = s.length();
		if (check()) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}
```
[AC record](https://codeforces.com/contest/2110/submission/321244967)

---

## 作者：ghx0052 (赞：0)

### 思路

对于平衡括号序列 $S$ 的任意前缀，左括号的数量总是 **大于等于** 右括号的数量。

所以我们只要使其存在某一前缀使其左括号的数量 **小于** 右括号的数量即可；

由此可知，删除 **第一个左括号** 为最优，因为其可以影响 **更多** 的前缀（减少前缀中左括号的数量）；

同理可得，删除 **最后一个右括号** 也为最优，因为其可以影响 **更少** 的前缀（减少前缀中右括号的数量）；

又因为 $S$ 一定可以表示为 $(A)$ 的形式（$A$ 为一个括号序列）

所以，我们只需判断 $S$ 删去头尾后（即 $A$）是否为平衡括号序列即可。

### 代码
```c++
#include <bits/stdc++.h>
using namespace std;
stack<bool> st;
string s;
void solve() {
    cin >> s;
    for (int i = 1; i < s.size() - 1; i ++) {
        if (s[i] == '(') st.push(1);
        else if (s[i] == ')') {
            if (st.empty() || st.top() != 1) {
                cout << "YES" << endl;
                return;
            } else st.pop();
        }
    }
    if (st.empty()) cout << "NO" << endl;
    else cout << "YES" << endl;
    while (!st.empty()) st.pop();
}
int main() {
	int t;
	cin >> t;
	while (t --) solve();
}
```

---

## 作者：AnOIer (赞：0)

### Solution

删掉一个左括号和一个右括号能否使得一个括号序列不合法。

回顾一下如何判断一个括号序列是否合法，需要设统计变量 $cnt$。遍历字符串，当字符为左括号时 $cnt$ 加 $1$，否则 $cnt$ 减 $1$，且此过程中 $cnt$ 不能为负数，最后 $cnt$ 应该等于 $0$。

因为删掉一个左括号和一个右括号不会改变左括号和右括号数量之差，因此为了使序列不合法，我们需要使遍历过程中 $cnt$ 为负数。

不难想到删掉第一个左括号和最后一个右括号是最优的操作，因此我们只需要判断字符串中第 $2$ 个字符到 $len-1$ 个字符的这一子串是否合法即可，其中 $len$ 为字符串长度。

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve() {
	string s;
	cin >> s;
	int n = s.size();
	if (n == 2) {
		cout << "NO" << endl;
		return;
	}
	string t = s.substr(1, n - 2);
	int cnt = 0;
	bool ok = true;
	for (int i = 0; i < t.size(); i++) {
		char c = t[i];
		if (c == '(') cnt++;
		else cnt--;
		if (cnt < 0) {
			ok = false;
			break;
		}
	}
	if (ok && cnt == 0) {
		cout << "NO" << endl;
	} else {
		cout << "YES" << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
```

---

## 作者：lw393 (赞：0)

好题，~~直接猜！~~

题目大意：在一个合法括号序列 $S$ 中，我们只能删除一个左括号和一个右括号，能否将它变得不合法？

我们发现，无论怎么样，都不能将它变合法的的括号序列是形如：$(A)$，其中 $A$ 是一个合法的括号序列。因为无论如何，它的任意前缀，左括号的数量总是**大于**右括号的数量。所以删去任意一个左括号与右括号，都不会导致任意前缀中左括号数量小于右括号数量。

所以由上，我们只需判断 $S(2,len_S - 1)$ 这一段串是否不为合法括号序列即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
  string s;
  cin >> s;
  string res = s.substr(1, s.length() - 2);
  stack<char>st;
  for(int i = 0; i < res.length(); i++) { if(res[i] == '(') st.push('('); else if(st.empty()) { cout << "Yes\n"; return; } else st.pop(); }
  cout << "No\n";
}

int main(){
  int t = 1;
  cin >> t;
  while(t--){
    solve();
  }
  return 0;
}
```

---

