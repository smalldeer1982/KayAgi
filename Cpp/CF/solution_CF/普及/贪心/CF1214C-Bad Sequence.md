# Bad Sequence

## 题目描述

给出一个长度为 $n$ 的括号序列 $s$ , 求出 $s$ 能否通过移动不超过 $1$ 个括号的位置, 使得这个括号序列变成一个正确的括号序列.

我们定义满足下面任意一个条件的括号序列 $S$ 为一个正确的括号序列:

- $S$ 是一个空串
- $S = (t)$ , 其中 $t$ 是一个正确的括号序列
- $S = t_1 + t_2$ , 其中 $t_1$ , $t_2$ 都是正确的括号序列, '$+$' 运算定义为字符串的拼接.

## 说明/提示

$1 \leq n \leq 200000$

## 样例 #1

### 输入

```
2
)(
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
3
(()
```

### 输出

```
No
```

## 样例 #3

### 输入

```
2
()
```

### 输出

```
Yes
```

## 样例 #4

### 输入

```
10
)))))(((((
```

### 输出

```
No
```

# 题解

## 作者：L______ (赞：8)

好像看到其他大佬说什么把最左边的右括号移到最右边然后开始模拟，觉得有点小麻烦。

说下我看到这道贪心（~~栈模拟~~）好题（~~水题~~）的思路吧。

我们知道对于一个什么操作都没有的括号序列，我们栈模拟，左括号入栈，右括号把左括号弹出栈，那么这道题有一个奇怪的移动操作，我们应该怎么办呢？很简单，这道题只有一个移动操作，那么我们直接模拟完看最后栈内的结果就好了。

最终可以分为3种情况：

1.如果栈为空，那么括号序列本来就是合法的，我们不需要移动。

2.如果栈内有元素，且仅剩下了相应的一个右括号和一个左括号，那么通过一次移动可以使得括号序列合法。

3.对于其他栈中剩下元素的情况都不合法。

Code
```
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define N 200010
using namespace std;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int n,s[N],top=0;
char ch[N];

int main(){
	n=read();
	scanf("%s",ch+1);
	for(int i=1;i<=n;i++){
		if(ch[i]=='(') s[++top]=1;
		else{
			if(top!=0 && s[top]==1) top--;
			else s[++top]=0;
		}
	}
	if(top==0 || (top==2 && s[1]==0 && s[2]==1)) printf("Yes\n");
	else printf("No\n");
}
```


---

## 作者：Meatherm (赞：2)

一看到括号序列，就想到了栈。


遇到一个 `(` ，将它压入栈。

遇到一个 `)` 将它弹出栈。如果此时没有可弹的括号，不匹配的右括号数量 $+1$。

如果序列处理完毕时仍然有左括号在栈中，不匹配的左括号数量就是栈中的元素数量。

如果没有不匹配的括号 —— 序列合法，输出 `Yes`。

如果恰好有一对不匹配的括号 —— 我们可以将某一个移到另外一个旁边使得其匹配，从而使序列合法，输出 `Yes`。

其他情况均不能匹配，输出 `No`。

```cpp
# include <bits/stdc++.h>
# define rr register
const int N=200010;
char c[N];
int n;
int Leftsum,Rightsum;
int stacksum;
int main(void){
	scanf("%d",&n);
	scanf("%s",c+1);
	for(rr int i=1;i<=n;++i){
		if(c[i]=='('){
			++stacksum;
		}else{
			if(stacksum==0){
				++Rightsum;
			}else{
				--stacksum;
			}
		}
	}
	Leftsum=stacksum;
	if(Leftsum==Rightsum&&(Leftsum==1||Leftsum==0)){
		printf("Yes");
	}else{
		printf("No");
	}
	return 0;
}
```

---

## 作者：AFOier (赞：2)

一道水题。

题意：给定一个长度为n的由$'('$和$')'$组成的括号序列，求能否移动一个括号使这个序列为合法扩号序列。

显然当左括号与右括号数量不相等时，肯定无法匹配。

我们用栈统计括号序列中最大合法子序列长度s。

若$s=n-2$，则只有两个括号不匹配。又因为前面判断过肯定是1个左括号和1个右括号，显然移动一个括号能使其为合法括号序列

若$s=n$，则不移动括号即可。

$Code:$
```
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n,m,lkh,rkh,num,ans;
string b;
int main(){
	scanf("%d",&n);
    cin>>b;
    for(int i=0;i<b.size();i++){
        if(b[i]=='(')num++,lkh++;
        else {
			rkh++;
			if(num>0)num--,ans+=2;//用栈统计最长合法子序列
		}
    }
    if(lkh!=rkh){
    	cout<<"No"<<endl;
    	return 0;
    }//做括号数与右括号数不相等
    if(ans==n-2||ans==n)cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    return 0;
}
```

---

## 作者：断清秋 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1214C)

这题一脸 CF-style……比较小清新。

考虑能够用至多 $1$ 次移动变成合法的括号序列 $a_n$，需要满足以下两个条件：1、序列中左括号和右括号的数量相等；2、这个序列中以 $a_1$ 为开头的任意子序列中，右括号的个数 $-$ 左括号的个数 $\le 2$。

这个结论是显然的，于是考虑维护左右括号数量。

具体维护：初始时 $s=0$，读入左括号时 $s=s-1$，读入右括号时 $s=s+1$，如果 $s=2$ 就证明右括号已经比左括号多了两个，那么无解。

最后判断完之后，如果 $s=0$ 则证明左右括号个数相等，即满足以上两个条件，那么有解；反之则无解。

---

## 作者：YUYGFGG (赞：1)

思路：

1. 如果 $n$ 是奇数肯定不行（一对括号两个，只有偶数个总数可能）。

2. 删除所有匹配的上的括号。

3. 统计左括号和右括号的总数，如果左括号数目不等于右括号数目那肯定不行。

4. 如果栈里剩下的左括号少于 $2$ 个，那可以，否则不行。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
stack<char> sta;
int main(){
	int n;
    cin>>n>>s;
	if(n%2==1) cout<<"No"<<endl;
	else{
		int sumleft=0,sumright=0;
		for(int i=0;i<n;i++) {
			if(s[i]=='(') sta.push(s[i]);
			else if(s[i]==')'&&!sta.empty()) sta.pop();
			if(s[i]=='(') sumleft++;
			else sumright++;
		}
		if(sta.empty()&&sumleft==sumright) cout<<"Yes"<<endl;
		else {
			if(sta.size()>1||sumleft!=sumright) cout<<"No"<<endl;
			else cout<<"Yes"<<endl;
		}
	}
	return 0; 
} 
```


---

## 作者：Taoist_Cheewood (赞：1)

能否最多移动一次（包括不移）括号，使序列合法。

假如我们要移动一个“）”，那么移到序列最后，一定是最优的。

假如我们要移动一个“（”，即寻找移动完后的“（”，匹配的是哪一个“）”。其实这样可以不移这个“（”，而去移动上句话中所述的“）”；

那么就只考虑移动“）”。

先用栈思想匹配括号，记录未匹配的“（”个数，遇到一个“）”就匹配，记录未能匹配的“）”数，在最后进行处理，若剩下的左右括号能匹配（个数相等且为1），则合法，输出YES。
```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
int n;
string s;

int main()
{
	int l=0,r=0;
	scanf("%d",&n);
	cin>>s;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='(') l++;//入栈 
		else if(l==0) r++;
		else l--;//出栈 
	}	
	if(l==r&&(l==0||l==1)){ //(l==r) 能否匹配;l,r==0 已经合法;r,l==1 将右括号移到最后进行匹配;
		printf("Yes\n");
	}
	else printf("No\n");
	return 0;
}
```

结束。

---

## 作者：__int127 (赞：0)

## CF1214C Bad Sequence 题解

#### [题目传送门](https://www.luogu.com.cn/problem/CF1214C)

#### [双倍经验](https://www.luogu.com.cn/problem/UVA673)

### 题目大意

给定一个长度为 $n$ 的括号序列 $S$，判断序列 $S$ 是否能通过 $\le1$ 次操作，将其变成一个合法括号序列，如果可以，则输出 `Yes`，否则输出 `No`，定义合法括号序列为：

- 空串合法。

- 若 $t$ 合法，则 ($t$) 也合法。

- 若 $t_1$ 和 $t_2$ 合法，则 $t_1+t_2$ 也合法，定义 `+` 为字符串的拼接。

### 样例解释

#### 样例 \#1 解释

第一个样例，$n=2$，即字符串长度为 $2$，字符串 $S$ 为 `)(`，将 $S_2$ 以至 $S_1$，可以组成一个合法括号序列，输出 `Yes`。


#### 样例 \#2 解释

第一个样例，$n=3$，即字符串长度为 $3$，字符串 $S$ 为 `(()`，无论怎样移动，都无法组成合法括号序列，输出 `No`。


#### 样例 \#3 解释

第一个样例，$n=2$，即字符串长度为 $2$，字符串 $S$ 为 `()`，$S$ 本身就是一个合法括号序列，输出 `Yes`。


#### 样例 \#4 解释

第一个样例，$n=10$，即字符串长度为 $10$，字符串 $S$ 为 `)))))(((((`，无论怎样移动，都无法组成合法括号序列，输出 `No`。

### 思路

本题可以用栈来模拟。

首先读入 $n$ 和字符串 $S$，这里要注意，由于空串合法，本题需要用

```cpp
getline(cin, s);
```

来读入，但是 getline 会读入换行，所以还需要一个临时的字符串类型的变量用 getline 读入换行。

接下来就可以用栈来模拟啦。

如果 $S_i$ 为 `(`，将 $S_i$ 压入栈。

如果 $S_i$ 为 `)` 且栈不为空时，查看当前栈顶是否为 `(`，如果是，将当前栈顶弹出，舍弃 $S_i$（找到了匹配的括号）；如果不是，则将 $S_i$ 压入栈。

如果将 $S$ 遍历完后，栈为空，说明 $S$ 本身就是一个合法括号序列，输出 `Yes`。如果栈为 `)(`，则可以移动一个字符使 $S$ 是一个合法括号序列，输出 `Yes`。若果为其它情况，则不能只移动一个字符使 $S$ 是一个合法括号序列，输出 `No`。

### 代码+注释

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string s, e;
stack <char> a;
int main(){
	cin >> n;
	getline(cin, e);// 假装读入换行
	getline(cin, s);// 读入字符串
	for (int i = 0; i < n; i++){
		if (s[i] == '(' || (s[i] == ')' && a.empty())){// 如果当前字符为 '(' 或者当前字符为 ')' 且栈为空时，将 s[i]
 压入栈			a.push(s[i]);
		} else if (!a.empty()){
			if (a.top() == '('){
				a.pop();// 找到了匹配的括号，弹出栈
			} else {
				a.push(s[i]);// 没有找到匹配的括号，压入栈
			}
		}
	}
	if (a.empty()){// 当栈为空时，输出 "Yes"
		cout << "Yes";
	} else {
		if (a.size() != 2){
			cout << "No";
			return 0;
		}
		char c = a.top();
		a.pop();
		if (!a.empty()){
			if (c == '(' && a.top() == ')'){// 当栈为 ")(" 时，输出 "Yes"
				cout << "Yes";
			} else {
				cout << "No";
			}
		} else {
			cout << "No";
		}
	}
	return 0;
}
```

### 最后
本题题解到此结束，希望大家能看懂、有思路。

---

## 作者：Micnation_AFO (赞：0)

[CF1214C Bad Sequence](https://www.luogu.com.cn/problem/CF1214C)

-------------

前置知识：[UVA673 平衡的括号 Parentheses Balance](https://www.luogu.com.cn/problem/UVA673)

在 UVa673 的基础上，本题多了一个移动操作。显然，当 `(` 与 `)` 的数量不等时，一定无法成功。若两者相等，我们可以像 UVa673 那样先对括号序列进行操作。
- 当最后栈为空时，此时不需要移动，一定可以。
- 若栈内元素的个数为两个，则栈内的元素按顺序一定是：`)(`，此时利用移动的作用，使其变为 `()`，因此也能成功完成操作。
- 若栈内元素的个数超过两个，则仅靠 $1$ 次操作无法完成。

核心代码：
```cpp
bool check(string str) {
    stack<char> s;
    for (int i = 0; i < str.size(); i++) {
        if (s.empty() || !(s.top() == '(' && str[i] == ')')) s.push(str[i]);
        else s.pop();
    }
    int cnt = 0;
    while (!s.empty()) { cnt++; s.pop(); }
    if (cnt <= 2) return true;
    else return false;
}

int num(char ch, string s) {
    int cnt = 0;
    for (int i = 0; i < s.size(); i++) 
        if (s[i] == ch) cnt++;
    return cnt;
}

signed main() {
    cin >> n;
    cin >> s;
    if (num('(', s) == num(')', s) && check(s)) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}
```

---

## 作者：meyi (赞：0)

无需模拟进栈出栈，我们记录一个累加器 $m$，遇到 `(` 则 $m \leftarrow m+1$，遇到 `)` 则 $m \leftarrow m-1$，则当 $m<0$ 时，$|m|$ 即为未匹配到左括号的右括号数量。本题要求移动不超过一个括号，即未匹配到左括号的右括号不超过一个，故 $m$ 最终为 $0$ 且 $m_{min} \geq -1$ 时，该序列合法，输出 `Yes`，否则输出 `No`。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int m,n;
char s[maxn];
int main(){
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;++i){
		m+=(s[i]=='('?1:-1);
		if(m<-1)return puts("No"),0;
	}
	puts(m?"No":"Yes");
	return 0;
}
```


---

## 作者：qian_shang (赞：0)

 一道贪心~~水题~~好题
 
 大体思路如下：

 题目要求改变一个括号位置而使序列合法
 
 可以证出，改变第一个不合法的‘）’会更优
 
 所以只需要记录第一个不合法的‘）’位置并删除
 
 最后判断有没有剩一个‘（’就可以啦
 
 代码如下（窝码风真的太丑了QAQ）

```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<algorithm> 
#define N 200005
#define LL long long
#define inf 0x7f7f7f
using namespace std;
int n,k;//k指目前没配对的‘（’
bool flag;
char c;
int main()
{
	scanf("%d\n",&n);
	printf("\n");
	for (int i=1;i<=n;i++)
	{
		scanf("%c",&c);
		if (c=='(') k++;
		else {
			if (k==0) {
				if (flag==0) flag=1;//记录
					else {printf("No");return 0;}//有两个不合法就NO
			}else k--;
		}
	}
	if (flag) {
		if (k==1) printf("Yes");
			else printf("No");
	}else {
		if (k==0) printf("Yes");
		else printf("No");
	}//输出
	return 0;
}
```

---

