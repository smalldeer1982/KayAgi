# [ABC328D] Take ABC

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc328/tasks/abc328_d

`A` , `B` , `C` の $ 3 $ 種類の文字のみからなる文字列 $ S $ が与えられます。

$ S $ が連続な部分文字列として文字列 `ABC` を含む限り、下記の操作を繰り返します。

> $ S $ に連続な部分文字列として含まれる文字列 `ABC` のうち、$ S $ の中で最も左にあるものを、$ S $ から削除する。

上記の手順を行った後の、最終的な $ S $ を出力してください。

## 说明/提示

### 制約

- $ S $ は `A` , `B` , `C` のみからなる長さ $ 1 $ 以上 $ 2\times\ 10^5 $ 以下の文字列
 
### Sample Explanation 1

与えられた文字列 $ S\ = $ `BAABCBCCABCAC` に対して、下記の通りに操作が行われます。 - $ 1 $ 回目の操作で、$ S\ = $ `BAABCBCCABCAC` の $ 3 $ 文字目から $ 5 $ 文字目の `ABC` が削除され、その結果 $ S\ = $ `BABCCABCAC` となります。 - $ 2 $ 回目の操作で、$ S\ = $ `BABCCABCAC` の $ 2 $ 文字目から $ 4 $ 文字目の `ABC` が削除され、その結果 $ S\ = $ `BCABCAC` となります。 - $ 3 $ 回目の操作で、$ S\ = $ `BCABCAC` の $ 3 $ 文字目から $ 5 $ 文字目の `ABC` が削除され、その結果 $ S\ = $ `BCAC` となります。 よって、最終的な $ S $ は `BCAC` です。

### Sample Explanation 2

この入力例では、最終的な $ S $ は空文字列です。

## 样例 #1

### 输入

```
BAABCBCCABCAC```

### 输出

```
BCAC```

## 样例 #2

### 输入

```
ABCABC```

### 输出

```
```

## 样例 #3

### 输入

```
AAABCABCABCAABCABCBBBAABCBCCCAAABCBCBCC```

### 输出

```
AAABBBCCC```

# 题解

## 作者：cjh20090318 (赞：3)

因为信仰写了一个 `string` 的朴素算法上去，然后多了一发罚时，~~[甚至过了很多个点](https://atcoder.jp/contests/abc328/submissions/47473315)~~。

## 题意

给定一个仅含 `A`、`B`、`C` 三个字母的字符串，你需要对其进行操作：

- 每次从最左边找到第一个 $\texttt{ABC}$ 连续子串，然后删掉这个连续子串。

你需要对字符串不断执行操作直到无法找到这样一个连续子串，并输出操作后的字符串。

## 分析

这样一个操作很类似于括号序列，如果当前字符为右括号且栈顶为左括号就弹出，否则压入。

这道题也一样，如果当前字符为 `C` 且栈顶为 `B`，其次为 `A`，就将两个字符弹出，否则压入 `C`。


## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<vector>
using namespace std;
vector<char> v;
int main(){
	for(char c=getchar();'A'<=c&&c<='C';c=getchar()){
		if(c=='C' && v.size()>=2 && v.back()=='B' && v[v.size()-2]=='A') v.pop_back(),v.pop_back();//在元素数量足够的情况下判断。
		else v.push_back(c);//压入该字符。
	}
	for(const char c:v) putchar(c);//输出当前字符串。
	return 0;
}

```

---

## 作者：OAer (赞：3)

### 题目描述

给你一个字符串 $S$，一直执行以下操作，直到找不到为 `ABC` 的子串：

找到 $S$ 中最靠左边的子串 `ABC`，然后把它删掉。例如 $S=\texttt{ABA}\texttt{\color{ff0000}{ABC}}\texttt{BCC}$ 时，要删掉的部分为标红部分。

输出执行完后的 $S$。



例如这个：

- 未开始操作时，$S=\texttt{BAABCBCC}$。

- 第一次，找到的子串为标红部分：$\texttt{BA}\texttt{\color{ff0000}{ABC}}\texttt{BCC}$，删掉后为 $\texttt{BABCC}$。

- 第二次，找到的是：$\texttt{B}\texttt{\color{FF0000}{ABC}}\texttt{C}$，删掉后为 $\texttt{BC}$。

- 第三次，无法找到，故输出 $\texttt{BC}$。

### 解题思路

此处要注意：不能光扫一遍，因为把中间的删了，前面的和后面的又有可能结合在一起。（见样例）



那么有什么方法可以保留前面的字符，又可以检查后面的是否可以和前面的结合呢？没错，就是栈。



从左到右依次扫描字符串 $S$，把 $S$ 中的字符依次放入栈中。若栈顶的三个元素为 $\texttt{A}$、$\texttt{B}$、$\texttt{C}$，可以直接将这几个元素出栈。最后的结果就是栈中剩下的元素（从栈底到栈顶）。



不管了，先上代码：



### AC 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char a[200005];	//字符串 S 
char S[200005];	//栈 
int top;	//栈顶指针 
int main(){
	scanf("%s",a);
	int n=strlen(a);
	for(int i=0;i<n;i++){
		S[++top]=a[i];	//入栈 
		if(top>=3){	//防溢出 
			if(S[top-2]=='A'&&S[top-1]=='B'&&S[top]=='C')	//检查栈顶的元素 
				top-=3;	//出栈 
		}
	}
	for(int i=1;i<=top;i++) printf("%c",S[i]);	//输出 
	return 0;
}
```

[ATCODER 中我的提交记录](https://atcoder.jp/contests/abc328/submissions/47493182)



### 答疑

##### Q1：你怎么能保证它是最左边的元素？

因为它是从左到右扫的，出现满足条件的时候一定是最先出现的，后面结合并删除的时候也是立马就删的，然后后面的元素才进栈，故它删除的一定是最靠左的。

##### Q2：那么前面的怎么办呢？

要是前面的能被删早删了，结合的时候也是尽早删的。



### 彩蛋

你肯定不知道，我之前一不小心把 $top$（栈顶指针）开成字符类型的，导致 RE 了 $18$ 个点，不信你看！[Link](https://atcoder.jp/contests/abc328/submissions/47488178)








---

## 作者：HDS_Acenaphthylene (赞：2)

看到题解区没有链表的，来写一发。

我们把字符串转化为一个链表，判断**之后**三个字符是否构成 `ABC`，如果构成，消除。此时之前的字符和之后的字符可能构成 `ABC`，所以要回退两个字符（`ABABCC`在消除 $S_{3\dots5}$ 后要从 `B` 回退到头结点）。

```
#include<bits/stdc++.h>
using namespace std;
string s;
struct node{char c;int next, pre;}lst[200005];
char nxt(int idx, int t) {
	if(idx == 11451419)return 'F';
	if(t == 0)
		return lst[idx].c;
	return nxt(lst[idx].next, t - 1);
}
int main() {
	cin >> s;
	s = " " + s;
	for(int i = 0;i <= s.size() - 1;i ++){
		lst[i].c = s[i];
		lst[i].next = i + 1;
		lst[i].pre = i - 1;
		if(i == s.size() - 1)lst[i].next = 11451419;
		if(i == 0)lst[i].pre = 0;
	}
	for(int i = 0;i != 11451419;) {
		if(nxt(i, 1) == 'A' && nxt(i, 2) == 'B' && nxt(i, 3) == 'C' && nxt(i, 3) != 'F') {
			lst[i].next = lst[lst[lst[lst[i].next].next].next].next;
			if(lst[i].next != 11451419)
				lst[lst[i].next].pre = i;
			i = lst[i].pre;
			i = lst[i].pre;
		}
		else i = lst[i].next;
	}
	for(int i = lst[0].next;i != 11451419;i = lst[i].next)cout << lst[i].c;
	return 0;
}
```

---

## 作者：BugGod (赞：1)

首先看到消去连续的 $\texttt{ABC}$ 可以联想到括号匹配，那么我们直接开个栈模拟，最后从栈底到栈顶，依次输出即可。当然，也可以写链表模拟。

做法：我们每遇到一个字符，就塞进栈中，如果发现栈顶部有 $\texttt{ABC}$ 的存在，就删除这三个字母，这样的话，每遇见一个 $\texttt{ABC}$ 都能消掉。

CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
char st[200010],cnt;
int main()
{
	cin>>s;
	for(int i=0;i<s.size();i++)
	{
		st[++cnt]=s[i];
		if(cnt>2&&st[cnt-2]=='A'&&st[cnt-1]=='B'&&st[cnt]=='C')cnt-=3;
	}
	for(int i=1;i<=cnt;i++)cout<<st[i];
	return 0;
}
```

---

## 作者：Mortidesperatslav (赞：1)

注意到数据范围是 $2 \times 10^5$ 我们不能直接暴力枚举，因为可能被卡成 $n^2$。

我们细看一下，会发现本题要删除的子串 `ABC` 非常短。

那么我们用一个栈模拟。

每当读入一个字符时，弹出栈顶两个元素，判断一下这两个元素和当前字符能否构成 `ABC`，是就弹掉，不是就放入当前元素。

最后把栈里的东西倒过来就行了。

值得注意的是，`stack` 为空时，采用 `top()` 和 `pop()` 会 RE。所以要特判一下。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
stack<char>s;
stack<char>tmps;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	char ch='a';//先给一个不等于 EOF 的初值，防止 UB
	while(ch!=EOF){
		ch=getchar();//读入字符
		char s1,s2;
		if(s.size()<2){//注意到栈里面元素不够时弹出来会运行错误，直接特判
			s.push(ch);
			continue;
		}
		s1=s.top();
		s.pop();
		s2=s.top();
		if(s2=='A'&&s1=='B'&&ch=='C')s.pop();//如果是 ABC，就弹掉
		else{
			s.push(s1);
			s.push(ch);//放进去，s1 是刚才弹出来的，要放回去
		}
	}
	while(!s.empty()){
		tmps.push(s.top());
		s.pop();
	}//另开一个栈，实现把字符串倒过来
	while(!tmps.empty()){
		if(tmps.top()=='A'||tmps.top()=='B'||tmps.top()=='C')cout<<tmps.top();
		tmps.pop();//输出
	}
}
```

---

## 作者：EityDawn (赞：1)

## 题面描述
在一个只含 $A$，$B$，$C$ 的字符串中删去所有 $ABC$ 串。
## 解题思路
KMP 算法模板题，令 $ABC$ 为模式串，在主串中匹配就行了，时间复杂度 $O(L)$，$L$ 为主串长度。
### code
```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=1000010;
int la,lb,res;
char a[N],b[N];
int p[N],pre[N];
int zh[N],top=0;
int i,j;
void init()
{
	for(i=2,j=0;i<=lb;i++)
	{
		while(j&&b[i]!=b[j+1])
			j=p[j];
		if(b[i]==b[j+1])
			j++;
		p[i]=j;
	}
	return;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>a+1;
	for(int i=0;i<=2;i++) b[i+1]='A'+i;
	la=strlen(a+1);
	lb=strlen(b+1);
	init();
	for(i=1,j=0;i<=la;i++)
	{
		while(j&&a[i]!=b[j+1])
			j=p[j];
		if(a[i]==b[j+1])
			j++;
		pre[i]=j;
		zh[++top]=i;
		if(j==lb)
			top-=lb,j=pre[zh[top]]; 
	}
	for(i=1;i<=top;i++) cout<<a[zh[i]];
	return 0;
}
```


---

## 作者：UncleSam_Died (赞：0)

### 题目大意
告诉你一个由 A、B、C 三种字符组成的字符串 $s$，每次消除最左边的一个字符串 `ABC`，问最后剩下的字符串是什么。
### 解题思路
很简单的一道题，我们考虑用栈来维护。对于每个字符，如果是 A 或 B，那么直接进栈，否则的话，考虑当前栈顶的两个元素能否和当前的 C 共同构成一个字符串 `ABC` 如果能的话，弹出两个栈顶元素，不能的话，就把当前的 C 也加入栈中。
### AC 代码
```cpp
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<math.h>
#include<time.h>
#define N 200005
char sta[N],s[N];
int tail;
inline void work(){
	scanf("%s",s+1);
	int len=strlen(s+1);
	for(int i=1;i<=len;++i){
		if(s[i]=='A') sta[++tail]='A';
		else if(s[i]=='B') sta[++tail]='B';
		else{
			if(sta[tail]=='B'&&sta[tail-1]=='A'){
				tail-=2;
			}else sta[++tail]='C';
		}
	}for(int i=1;i<=tail;++i)
		putchar(sta[i]);
}signed main(){
	work();
}
```


---

## 作者：whx2009 (赞：0)

## 本题思路：
这道题其实很简单，我们只需要用链表存储一下每一个数字在删除一些字母后的左边是哪一个即可，这样我们就可以直接连边，遇到 ```ABC``` 就删掉了。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int net[200006];
int main()
{
	cin>>s;
	int n=s.size()-1;
	for(int i=0;i<=n;i++) net[i]=i-1; 
	for(int i=0;i<=n;i++)
	{
		if(i>=2)
		{
			if(s[i]=='C' && s[net[i]]=='B' && s[net[net[i]]]=='A')
            		s[i]=s[net[i]]=s[net[net[i]]]=0,net[i+1]=net[net[net[i]]];
		}
	}
	for(int i=0;i<=n;i++) 
	{
		if(s[i]!=0) cout<<s[i];
	}
	return 0;
}

```

---

## 作者：WilliamFranklin (赞：0)

### 主要思路

因为题目中要求了，是从前往后查找，所以说方便了许多。

这道题我用的是链表，$l_i$ 就表示 $i$ 它的上一位，$r_i$ 就表示 $i$ 的下一位。因为我们会发现，如果出现了一次 `ABC`，那么就相当于在链表中删除这一段。为了方便，我们可以从前往后枚举 `C` 出现的位置，在看一看 $l_i$ 是不是 `B`，$l_{l_i}$ 是不是 `A` 即可。删除的时候就是让 $r_{l_{l_i}}$ 为 $r_i$，$l_{r_i}$ 为 $l_{l_i}$。

最后的答案我们可以从 $0$ 开始，也可以从 $n + 1$ 开始查找（注：这里的 $n$ 指 $s$ 的长度）。

好了，看代码吧。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); TI--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 2e5 + 5;
string s;
int l[N];
int r[N];
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> s;
	for (int i = 0; i <= s.size(); i++) l[i] = i - 1, r[i] = i + 1;
	for (int i = 2; i < s.size(); i++) {
		if (s[i] != 'C') continue;
		int x = l[i];
		if (x == -1) continue;
		int y = l[x];
		if (y == -1) continue;
		if (s[x] == 'B' && s[y] == 'A') {
			l[r[i]] = l[y];
			r[l[y]] = r[i];
		}
	}
	string ans = "";
	int now = l[s.size()];
	while (now != -1) {
		ans += s[now];
		now = l[now];
	}
	reverse(ans.begin(), ans.end());
	cout << ans;
	return 0;
} 
```

### 谢谢观看

---

## 作者：heyx0201 (赞：0)

# Take ABC 题解
## Description
> 给定一个只包含 `A`,`B`,`C` 的字符串 $S$，只要 $S$ 包含字串 `ABC`，就删除最左边的子串 `ABC`，输出最后的字符串。

## Solution
这题类似于括号匹配，我们可以实现一个栈，然后遍历 $S$ 的每个字符，依次入栈，如果发现栈顶的 $3$ 个元素是 `ABC`，那么把 $3$ 个元素都弹出。

注意：RE 问题，弹出的时候要判断是否可以弹出。

## Accept Code
因为我太蒻了，写法有些恶心，请见谅。
```cpp
#include <bits/stdc++.h>

using namespace std;

string s;
stack<char> stk, stk2;

int main() {
  cin >> s;
  for (int i = 0; i < s.size(); i++) {
    stk.push(s[i]);
    stk2 = stk;
    if (stk2.top() == 'C') {
      if (stk2.empty()) {
        continue;
      }
      stk2.pop();
      if (stk2.top() == 'B') {
        if (stk2.empty()) {
          continue;
        }
        stk2.pop();
        if (stk2.top() == 'A') {
          if (stk2.empty()) {
            continue;
          }
          stk.pop(), stk.pop(), stk.pop();
        }
      }
    }
  }
  string ans = "";
  while (!stk.empty()) {
    ans += stk.top();
    stk.pop();
  }
  reverse(ans.begin(), ans.end());
  cout << ans;
  return 0;
}
```
[Accept Record（只能放 AtCoder 上的提交记录了，洛谷还在 UKE）](https://atcoder.jp/contests/abc328/submissions/47502031)

---

## 作者：kk1501201 (赞：0)

[题目传送门（洛谷）](https://www.luogu.com.cn/problem/AT_abc328_d)

# 题目描述
给定字符串 $S$ ,每次最左侧的 $\texttt {ABC}$ 删去,输出最后的字符串。

# 思路
有一个很~~清新脱俗~~怪的思路，把 $S$ 看做一个字符数组输入，一边输入一边倒着找（也就是找 $\texttt {CBA}$ ）每找到一次就删掉这三个，也就可以看做数组下标 $i$ 往前移了三位，复杂度 $O(n)$

# 赛时代码：（头文件、快读等已省略）
```cpp
const int N=3e5+1;
char c[N];
int main()
{
	int i=1;
	char ch;
	while(cin>>ch)
	{
		c[i]=ch;
		if(i>=3) 
		{
			if(c[i]=='C'&&c[i-1]=='B'&&c[i-2]=='A')
			{
				i-=3;
			}
		}
		i++;
	}
	for(int j=1;j<i;++j) putchar(c[j]);//因为最后多加了一次i，所以j要小于i
    return 0;
}

```


---

## 作者：_AyachiNene (赞：0)

# 思路：
链表做法。这道题很好想到用链表做，找到一个可以删的位置连着往后面删两个就行了。还要注意一个细节，删完后向前跳要跳两次，因为可能有这种情况：
```
AABCBC
```
先前跳一次就只能删掉中间的 ABC，两次才能找到后面的 ABC。
# Code:
```
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int f=1,res=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<1)+(res<<3)+(c^48);c=getchar();}
	return res*f;
}
void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
struct node
{
	int nxt,pre;
	char val;
}e[114514*2];
void del(int x)
{
	e[e[x].pre].nxt=e[x].nxt;
	e[e[x].nxt].pre=e[x].pre;
}
string s;
int main()
{
	cin>>s;
	int n=s.size();
	s=' '+s;
	for(int i=1;i<=n;i++)
		e[i].pre=i-1,e[i].nxt=i+1,e[i].val=s[i];
	e[n].nxt=0;
	int head=n+1;
	e[head].nxt=1;
	e[1].pre=head;
	int i=head;
	while(i)
	{
//		cout<<i<<endl;
		if(e[i].val=='A'&&e[e[i].nxt].val=='B'&&e[e[e[i].nxt].nxt].val=='C')
		{
			for(int j=1;j<=3;j++)
			{
				del(i);
				i=e[i].nxt;
			}
			for(int j=1;j<=2&&i!=head;j++)
				i=e[i].pre;
		}
		else
			i=e[i].nxt;
	}
	for(int i=head;i;i=e[i].nxt)
		if(i!=head)
			cout<<e[i].val;
}
```


---

## 作者：uid_647775 (赞：0)

可以用栈来模拟题目要求。  
从左到右依次将字符加入栈内，每次加入之后，判断栈顶是否是 ABC，若是，则将其弹出。  

---

```cpp
#include<cstdio>
int n,top;
char A[200005],St[200005];
//输入的字符串、栈 
int main() {
	scanf("%s",A+1);
	while(A[n+1]) n++;
	//n 为输入长度 
	for(int i=1;i<=n;i++) {
		St[++top]=A[i]; 
		if(top>=3&&St[top-2]=='A'&&St[top-1]=='B'&&St[top]=='C') 
			top-=3;
	}
	for(int i=1;i<=top;i++)
		putchar(St[i]);
	return 0;
}
```

---

## 作者：Expert_Dream (赞：0)

## 题目大意：

给你一个字符串 $s$。你要在其中找到多少个 `ABC` 的子串，例如 `AABCBC` 算两个，删掉中间的 `ABC` 后，前面的和后面的加起来也是一个 `ABC`，所以就算两个。

## 思路分析：

首先很容易写出暴力，把一个 `ABC` 提取出来后把后面的元素往前移，然后再重复操作，但是我们发现时间复杂度会卡成 **$O(n^2)$**。$n$ 指 $s$ 的长度。

于是我们想到用栈来维护，遍历这个字符串，把每一个字符串扔进栈里，设栈顶为 $bk$，如果栈中 $bk-2$ 的位置为 `A`，$bk-1$ 的位置为 `B`，$bk$ 的位置为 `C`，那么就是可以组成一个 `ABC`。这样遍历的时候每一次做一下判断，如果发现存在 `ABC`，那么就把这对应的栈中位置给删除了即可。

[link](https://atcoder.jp/contests/abc328/submissions/47476189)。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define fir first
#define se second
#define endl '\n'
#define debug puts("AK IOI")
using namespace std;
const int N = 2E5+5;
char st[N];int bk,n;
string s;
int main(){
	cin >> s;
	n=s.size();
	s=' '+s;
	for(int i = 1;i <= n;i++){
		st[++bk]=s[i];
		if(bk >= 3 && st[bk-2]=='A' && st[bk-1]=='B' && st[bk]=='C'){
			bk-=3;
		}
	}
	for(int i = 1;i <= bk;i++) cout<<st[i];
	
	return 0;
}
```

---

## 作者：Natori (赞：0)

>[ABC328D Take ABC](https://www.luogu.com.cn/problem/AT_abc328_d)

考场上看到这题马上联想到括号序列：

$\texttt{(()(()(())()))(}$

一对匹配的括号其实和一组 $\texttt{ABC}$ 本质上是相同的，都是匹配上之后要把它们从序列中删掉。

因此像括号序列一样维护一个栈，栈中存储当前还没有匹配上的字符。遇到 $\texttt{A}$ 和 $\texttt{B}$ 时直接入栈，遇到 $\texttt{C}$ 时判断能否弹出。最后按入栈序输出仍没有弹出栈的所有元素。

容易发现最后输出的字符串中一定不含子串 $\texttt{ABC}$，否则与栈的维护方法是矛盾的。每个元素最多进栈一次、出栈一次，时间复杂度 $\mathcal{O}(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool Mbegin;
void File_Work(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
}
const int N=2e5+8;
int n;
string str;
int stc[N],top;
bool Mend;
int main(){
//	File_Work();
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cerr<<fixed<<setprecision(3)<<(&Mbegin-&Mend)/1048576.0<<" MB\n\n\n";
	cin>>str;
	n=str.length();
	str=" "+str;
	for(int i=1;i<=n;i++){
		char ch=str[i];
		if(ch=='A')
			stc[++top]=1;
		else if(ch=='B')
			stc[++top]=2;
		else if(ch=='C'){
			if(top<=1)
				stc[++top]=3;
			else if(stc[top-1]==1&&stc[top]==2)
				top--,top--;
			else
				stc[++top]=3;
		}
//		cerr<<ch<<'\n';
//		for(int j=1;j<=top;j++)
//			cerr<<stc[j]<<' ';
//		cerr<<'\n';
	}
	for(int i=1;i<=top;i++){
		int va=stc[i];
		if(va==1)
			cout<<'A';
		else if(va==2)
			cout<<'B';
		else if(va==3)
			cout<<'C';
	}
	cerr<<"\n\n\n"<<fixed<<setprecision(0)<<1e3*clock()/CLOCKS_PER_SEC<<" ms";
	return 0;
}
```

---

## 作者：qqqaaazzz_qwq (赞：0)

~~花了我35分钟才做出来。~~

考虑用链表来维护未删去的字符，指针从左往右扫，如果扫到一个完整的 $\text{ABC}$，就把这个 $\text{ABC}$ 删掉，然后 $i$ 往后跳两步。故使用链表维护。

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[200010];
int nxt[200010];
int lst[200010];
bool del[200010];
int n;

signed main()
{
	cin >> s;
	n = strlen(s);
	for (int i=n;i>=1;i--) s[i] = s[i-1];
	s[0] = 0;
	for (int i=1;i<=n;i++)
	{
		lst[i] = i-1;
		nxt[i] = i+1;
	}
	nxt[0] = 1;
	int x = 1;
	while(x!=n+1)
	{
		if(s[x]=='A'&&s[nxt[x]]=='B'&&s[nxt[nxt[x]]]=='C')
		{
			int u = lst[x];
			int v = nxt[nxt[nxt[x]]];
			lst[v] = u;
			nxt[u] = v;
			del[x] = del[nxt[x]] = del[nxt[nxt[x]]] = true;
			x = lst[lst[x]];
		}
		else x = nxt[x];
	}
	for (int i=1;i<=n;i++)
	{
		if(!del[i]) cout << s[i];
	}
	return 0;
}
```

---

## 作者：jess1ca1o0g3 (赞：0)

## 前置芝士

栈的运用

## 思路

这道题给定一个字符串，要求删除符合标准的子串。

数据达到了 $2 \times 10^5$，不能用朴素的 $\Theta(n^2)$ 算法。

这不由得想到栈。

我们只需要不断将字符入栈，一旦满足条件就将其出栈，最后剩下的就是答案了。

## $Code$

C++

```cpp
#include<cstdio>
#include<cstring>
int top=0;
const int MAX=2e5+5;
char st[MAX],s[MAX];
signed main(){
	scanf("%s",s);
	for(int i=0;i<strlen(s);i++){
		st[++top]=s[i];
		if(top>=3&&st[top]=='C'&&st[top-1]=='B'&&st[top-2]=='A') top-=3;
	}
	for(int i=1;i<=top;i++) printf("%c",st[i]);
	return 0;
}
```

Python

```python
s=input()
st=list()
for i in s:
    st.append(i)
    if len(st)>=3 and st[len(st)-1]=="C" and st[len(st)-2]=="B" and st[len(st)-3]=="A":
       st.pop()
       st.pop()
       st.pop()
for i in st:
    print(i,end="")
```

---

## 作者：xxr___ (赞：0)

### 思路：
从前往后扫，遇到不是 `C` 的就直接如栈然后跳过，否则判读栈首前两个元素是否为 `A` 和 `B` 是就把这三个全删了，否则就把 `C` 入队。
### 赛时代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

char ch[200005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	string s;
	cin>>s;
	int len=s.size();
	int cnt=0;
	for(int i=0;i<len;i++){
		if(s[i]=='A'||s[i]=='B'||cnt<2){
			ch[++cnt]=s[i];
			continue;
		}
		char x=ch[cnt];
		--cnt;
		if(x=='B'&&ch[cnt]=='A'){
			--cnt;
		}else{
			ch[++cnt]=x;ch[++cnt]=s[i];
		}
	}
	for(int i=1;i<=cnt;++i)cout<<ch[i];
	return 0;
}

```

---

## 作者：MMXIandCCXXII (赞：0)

## 题目大意
给定字符串 $S$，当发现字符串中有子串 `ABC` 时，删除它，剩余部分为新的字符串，继续重复此操作知道无法找到这个子串。

## 思路
打比赛时没分析时间复杂度，打了个暴力。实际上，我们可以用类似栈的方法解决此题。遍历字符串，把当前字符存入栈中，如果栈顶的的三个字符是 `ABC`，将这几个字符删去，存入下一个字符。最后存在栈里的就是答案，时间复杂度 $O(n)$。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;
    string v;
    for (int i = 0; i < s.size(); i++)
    {
    	v.push_back (s[i]);
    	int len = v.size ();
    	if (len >= 3 && v.substr (len - 3, 3) == "ABC")
    	{
    
    		v.pop_back ();
    		v.pop_back ();
    		v.pop_back ();
	}
    }
    for (int i = 0; i < v.size (); i++)
    {
	cout << v[i];
    }
    return 0;
}
```

---

