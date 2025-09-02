# Technical Support

## 题目描述

### 题面翻译

给定一个只包含大写字母 $\texttt{Q}$ 和 $\texttt{A}$ 的字符串，如果字符串里的每一个 $\texttt{Q}$ 都能与**在其之后**的 $\texttt{A}$ 一一对应地匹配，则输出字符串 $\texttt{Yes}$，否则输出字符串 $\texttt{No}$。注意，可以有 $\texttt{A}$ 没有被匹配，但每个 $\texttt{Q}$ 必须成功地匹配。

## 样例 #1

### 输入

```
5
4
QQAA
4
QQAQ
3
QAA
1
Q
14
QAQQAQAAQQQAAA```

### 输出

```
Yes
No
Yes
No
Yes```

# 题解

## 作者：_H17_ (赞：16)

## 思路分析

这道题让 $Q,A$ 配对肯定要在 $Q$ 后找 $A$，所以可以用栈和队列来实现，首先遇见 $Q$ 则压栈或入队，遇见 $A$ 则若栈或队列非空则弹出，否则跳过。

## 队列基本操作

在此只讲 `STL` 的队列。

- 定义 `queue<类型名>队列名`，举例：`queue<int>q;`

- 判空 `q.empty();` 返回值是 `bool`。（以下认为队列名是 $q$）

- 入队 `q.push(x);` $x$是指要入队的值

- 出队 `q.pop();` 弹出队首元素

- 队首 `q.front();` 取队首

- 队尾 `q.back();` 取队尾

## 栈基本操作

在此只讲 `STL` 的栈。

- 定义 `stack<类型名>队列名`，举例：`stack<int>s;`

- 判空 `s.empty();` 返回值是 `bool`。（以下认为栈名是 $s$）

- 入栈 `s.push(x);` $x$是指要压栈的值

- 出栈 `s.pop();` 弹出栈顶元素

- 栈顶 `s.top();` 取栈顶

## 代码实现-队列

```cpp
#include<bits/stdc++.h>
//#include<管理员最帅>
using namespace std;
int t,n;
char c;
queue<int>q;
int main(){
    scanf("%d",&t);
    for(;t;t--){//据说比while(t--)快
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            cin>>c;//涉及char或string的最好用cin
            if(c=='Q')
                q.push(0);//入队，入什么值都行
            if(c=='A')
                if(!q.empty())
                    q.pop();
        }
        if(q.empty())
            puts("YES");
        else
            puts("NO");
        while(!q.empty())
            q.pop();//清空
    }
    return 0;
}

```

## 代码实现-栈

```cpp
#include<bits/stdc++.h>
//#include<管理员最帅>
using namespace std;
int t,n;
char c;
stack<int>s;
int main(){
    scanf("%d",&t);
    for(;t;t--){//据说比while(t--)快
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            cin>>c;//涉及char或string的最好用cin
            if(c=='Q')
                s.push(0);//压栈，压什么值都行
            if(c=='A')
                if(!s.empty())
                    s.pop();
        }
        if(s.empty())
            puts("YES");
        else
            puts("NO");
        while(!s.empty())
            s.pop();//清空
    }
    return 0;
}

```

---

## 作者：GalwayGirl (赞：6)

题目非常简单。

就是让字符串中每一个 $Q$ 与后面的一个 $A$ 匹配，$A$ 可以不被匹配。记一个 $cnt$ 为未匹配的 $Q$ 的个数，按照题意模拟即可。

```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int t,n,cnt;
    string a;
    int main(){
        scanf("%d",&t);
        while(t--){
            cnt=0;
            scanf("%d",&n);
            cin>>a;
            for(int i=0;i<n;i++){
                if(a[i]=='Q')cnt++;
                else cnt--;
                if(cnt<0)cnt=0;
            }
            if(cnt)printf("NO\n");
            else printf("YES\n");
        }
        return 0;
    }
```


---

## 作者：Day0 (赞：2)

### 题意解释：
给定一个字符串 $s$ , 串中 $Q$ 表示提问 , $A$ 表示回答，一个问题 $Q$ 可能对应多个后面的答案 $A$ , 求是否每个问题都可能获得回答。

### 思路：

不难发现，在一个串的后 $i$ 个字符中，如果出现了 $Q$ 出现的数量 $<$ $A$ 出现的数量，就会有问题得不到解答（比如你有三个问题，但是只有两个回答，肯定是有一个问题是没有获得答复的）。

那么就可以从后往前遍历，如果出现 $Q$ 的数量 $>$ $A$ 的数量，则为错误，否则则为正确。

### code:

```cpp
/*
    Author : TLE_Automaton && hhdxgd && JRXGD && hwd-gd
    Right Output ! & Accepted !
*/

#include <bits/stdc++.h>
//#define int long long
using namespace std;

int T;
const int L = 2e5 + 5;
int t, n;
string s;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch))
		f = (ch == '-' ? -1 : f), ch = getchar();
	while (isdigit(ch))
		x = (x << 3) + (x << 1) + (ch - '0'), ch = getchar();
	return x * f;
}


signed main() {
	T = read();
	while (T--) {
		n = read();
		cin >> s;
		int anum = 0, qnum = 0;
		for (int i = n - 1; i >= 0; i--) {
			if (s[i] == 'A') {
				anum++;
			} else {
				qnum++;
				if (anum < qnum) {
					puts("NO");
					break;
				}

			}
			if (!i) {
				puts("YES");
			}
		}
	}
	return 0;
}
```

---

## 作者：Strelitzia_ (赞：2)

## 题目大意

给出一个只包含 $\texttt{Q}$ 和 $\texttt{A}$ 的字符串 $S$，定义 $S$ 是合法的当且仅当任意一个 $\texttt{Q}$ 后面都能有一个 $\texttt{A}$ 与之对应。也就是说，任意一个位置后面 $\texttt{A}$ 的数量不能少于 $\texttt{Q}$ 的数量。

------------
## 思路

对于 $S$，我们生成一个序列 $\{a_n\}$，当 $S_i$ 为 $\texttt{Q}$ 时 $a_i=-1$，否则 $a_i=1$。

然后我们从后向前做一遍反方向的前缀和。然后再扫一遍：如果当前的和小于 $0$，则说明当前位置后面的 $\texttt{Q}$ 的数量大于 $\texttt{A}$ 的数量，不合法；否则合法。

代码如下：

```cpp
char ch[N];int len,s[N],t,a[N];
signed main(){
	t=read();for(int nowt=1;nowt<=t;nowt++){
		len=read();scanf("%s",ch+1);len=strlen(ch+1);
		for(int i=1;i<=len;i++) a[i]=(ch[i]=='Q'?-1:1);
		if(ch[len]=='Q'){puts("No");continue;}bool flg=1;
		for(int i=len-1;i;i--) a[i]+=a[i+1];
		for(int i=1;i<=len;i++) if(a[i]<0){puts("No");flg=0;break;}
		if(a[len]<0){puts("No");continue;}
		if(flg) puts("Yes");
	}
}
```

---

## 作者：CSPJ10pts (赞：0)

这道题的思路是每出现一个问题时，问题总数加一，遇见一个回答时，问题总数减一。最后如果问题总数小于等于 $0$ 即问题全被回答了时，输出 Yes，不然输出 No。

于是有了代码：
```
#include <iostream>
using namespace std;
int t, n, cnt;
char x;
int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> x;
            if (x == 'Q') cnt++;
            if (x == 'A') cnt--;
        }
        if (cnt <= 0) cout << "Yes" << endl;
        else cout << "No" << endl;
        cnt = 0;
    }
    return 0;
}
```

不过这样做我们会发现一个问题：

**输入**

```
8
QAAAAAAQ
```

如果按我们的思路，输出将会是：

```
Yes
```
但答案其实是 No 。为什么呢？因为我们回答太多了，但全浪费在第一个 $Q$ 上了，最后一个 $Q$ 没匹配成功。

怎么去改呢？

其实很简单，当问题总数被回答消成负数的时候出现了一个问题，那么将问题总数归 $0$ 在加一就好了。

最后，多测记得清空。

AC代码：
```
#include <iostream>
using namespace std;
int t, n, cnt;
char x;
int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> x;
            if (x == 'Q') {
                if (cnt < 0) cnt = 0; // 答案太多了但匹配不上问题时又出现一个问题需要将计数器归0
                cnt++; // 问题总数加一
            }
            if (x == 'A') cnt--;
        }
        if (cnt <= 0) cout << "Yes" << endl;
        else cout << "No" << endl;
        cnt = 0; // 多测记得清空
    }
    return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/91299203)

---

## 作者：YH_Eternally (赞：0)

## 题外话
虽然看起来十分简单，但赛时吃了一波罚时 qwq。

## 思路
一道字符串模拟题，但是坑点十分多，要注意以下几点。

- 如果字符 $\tt Q$ 的数量大于字符 $\tt A$ 的数量，就一定不合法。

- 如果字符串的最后一个字符为 $\tt Q$，就说明它没有一个字符 $\tt A$ 与其对应，也不合法。

- 每个 $\tt Q$ 之后最少一定要对应一个 $\tt A$，如字符串 $\tt QAAAQQQAA$，虽然 $\tt A$ 的数量比 $\tt Q$ 要多，最后一位字符也不为 $\tt Q$。可是在最后三个 $\tt Q$ 后的 $\tt A$ 只有两个，这就说明这 $3$ 个 $\tt Q$ 中一定有一个对应不上 $\tt A$ ，所以这种情况已是不合法的。

## 代码
``` cpp
#include<bits/stdc++.h>
 
using namespace std;
 
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar();}
	return x * f;
}
 
string s;
 
int main() {
	int t = read();
	while(t --) {
		int n = read(), s3 = 0, s4 = 0, s1 = 0, s2 = 0;
		cin >> s;
		int len = s.size(), flag = 0;
		for(int i = 0; i < len; i ++) {
			if(s[i] == 'Q') {
				s3 ++;
				s1 = s2 = 0;
				for(int j = i + 1; j < len; j ++) {
					if(s[j] == 'Q') s1 ++;
					else s2 ++;
				}
				if(s1 >= s2) { // 不满足的情况三
					puts("No");
					flag = 1;
					break;
				}
			} else {
				s4 ++;
			}
		}
		if(flag) continue;
		if(s3 > s4 || s[len - 1] == 'Q') puts("No"); // 不满足的情况一与情况二
		else puts("Yes");
	}
	return 0;
}
```

---

## 作者：Aeilot (赞：0)

# ~~水题~~

## 读题

1. 输入字符串
2. 字符串由 `Q` 开始
3. 一个 Q 匹配 **一个或多个** A （实际上只需要判断一个，多余的可以忽略）

## 思路

实际上 一个 Q 对应 一个 A，多余的 A 忽略，用栈的思想就可以解决此问题。（类似括号匹配）

1. **读入Q:** 入栈
2. **读入A:** 如果栈非空，出栈
3. 最后判断栈是否为空，输出结果

## 代码

```cpp
#include <cstdio>
#include <iostream>
#include <stack>
 
using namespace std;
 
int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        stack<char> st;
        for (int j = 0; j < n; j++) {
            char x;
            cin >> x;
            if (x == 'Q') {
                st.push('Q');
            }
            if (x == 'A') {
                if (!st.empty()) st.pop();
            }
        }
        if (st.empty())
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
```

---

## 作者：ZZQF5677 (赞：0)

### 前言：
CSP2022JS 赛前一发题解，在这里祝大家 CSP2022-JS RP++！！！
### 解题思路：
我试着用队列来实现这个过程（实际上，数据结构貌似都可以），当遇上一个问题时，我就把这个问题放入队列。当遇上一个答案时，我就让它尽量只解决一个问题，这样才能解决的问题更多，但前提是，只解决当前累计的问题，这个答案过了这一次就作废，不管有没有解决到问题（解决不到问题的可能只有一种：没有问题要解决了）。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n;
queue<bool> q;
int main() {
	cin >> t;
	while (t--) {
		while (!q.empty()) {
			q.pop();
		}
		cin >> n;
		for (int i = 1; i <= n; i++) {
			char ch;
			cin >> ch;
			if (ch == 'Q') {
				q.push(1);
			}	else {
				if (!q.empty()) {
					q.pop();
				}
			}
		}
		if (q.empty()) {
			puts("Yes");
		}else {
			puts("No");
		}
	}
	return 0;
}
```

### CSP2022 RP++！！！

---

## 作者：Dry_ice (赞：0)

[更好的阅读体验](https://www.cnblogs.com/dry-ice/p/cf1754a.html)

题链：[cf](https://codeforces.com/contest/1754/problem/A) [luogu](https://www.luogu.com.cn/problem/CF1754A)

> 简单的问题。

## Description
给你一串，内含 ```Q``` 与 ```A``` 代表问题与回答。如果一个串是合法的，那么要求一个问题至少要有一个回答，回答位置必须在问题位置之后。问原串是否合法。

## Analysis
显然类似栈的思想。

易知有贪心思路：当有问题 $\text{A}$ 已经出现但还未回答时不会使另一已经回答的问题 $\text{B}$ 增加一条回答，而应该回答当前未回答的问题 $\text{A}$。

直接一个 ```tp``` 统计已经出现并未解决的问题数，按照贪心思路匹配就行了。

## Code
```cpp
#include <stdio.h>
int n; char s[105];
inline bool Solve() {
	scanf("%d %s", &n, s + 1); int tp = 0;
	for (int i = 1; i <= n; ++i)
		if (s[i] == 'Q') ++tp; //统计 Q 个数
		else if (tp > 0) --tp; //没有未回答的问题了，对已回答的问题进行多次回答
	return tp == 0;
}
int main(void) {
	int T; for (scanf("%d", &T); T--; ) puts(Solve() ? "Yes" : "No");
	return 0;
}
```

## The end. Thanks.

~~（点点~~

---

## 作者：abensyl (赞：0)

这题我自己做的时候吃了一个罚时（qwq）。

原题：[Technical Support](https://www.luogu.com.cn/problem/CF1754A)。

## 思路

首先，根据常识和题意，我们可以知道两个事：

1. 回答一个问题一定在提问这个问题之后。

2. 对于一个问题，可以存在多个回答，但是一个回答不能回答多个问题。

所以我们遍历数组，在每个问题后找到其相应的回答即可。

如果某个问题 **在这个问题的的后面** 找不到相应的回答，那么就输出 `No`，否则输出 `Yes`。

## 代码

```cpp
#include <iostream>
using namespace std;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int cnt = 0;
    for (auto c : s)
      if (c == 'Q')
        cnt--;
      else if (cnt < 0)
        cnt++;
    if (cnt < 0)
      cout << "No";
    else
      cout << "Yes";
    cout << "\n";
  }
  return 0;
}
```

我的 [AC记录](https://www.luogu.com.cn/record/91301375)

---

## 作者：LinGxIao_0230 (赞：0)

### [原题链接](https://www.luogu.com.cn/problem/CF1754A)



在读入的过程中，判断
$ x = \begin{cases}
  Q \text{ 将其入栈}\\
  A \text{ 判断栈中是否还有元素，若栈为非空，则弹出栈顶元素}\\
\end{cases} $

读入完毕后判断栈中是否还有元素，若栈为空，则输出$Yes$，反则输出$No$

用栈和队列是直观理解~~正常人都是直接计数的~~
## Code
```cpp
void solve(){
	stack<int>st;
	cin>>n;
	for(int i=1;i<=n;i++){
		char x;cin>>x;
		if(x=='Q') st.push(i);
		else if(st.size()) st.pop();
	}
	puts(st.size()?"No":"Yes");
}
```


---

## 作者：maxyzfj (赞：0)

对于一个 `Q` 后面应该有一个或多个 `A` 与之对应。因此我们可以维护一个栈，当遇到一个 `Q` 就入栈，遇到一个 `A` 如果栈里面非空就弹栈，将目前的这个 `A` 作为对栈顶的 `Q` 的回答，否则什么也不用做（因为允许有 `Q` 对应多个 `A`）。

到最后如果栈非空，那么有 `Q` 没有对应上 `A`，输出 `No`，否则输出 `Yes`。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
	int x=0,f=1;
    char ch=getchar();
	while (ch<'0'||ch>'9'){
    	if (ch=='-') f=-1;ch=getchar();
    }
	while (ch>='0'&&ch<='9'){
    	x=x*10+ch-48;ch=getchar();
    }
	return x*f;
}
void write(int x){
    if(x<0){
		putchar('-'),x=-x;
	}
    if(x>9){
		write(x/10);
	}
    putchar(x%10 +'0');
}
stack<char>s;
int n, t;
signed main(){
	t=read();
	while(t--){
		while(s.size())s.pop();
		char c;
		n=read();
		for(int i=1;i<=n;i++){
			cin>>c;
			if(c=='Q')
				s.push(c);
			else{
				if(s.empty()){
					continue;
				}
				s.pop();
			}
		}
		if(s.empty()){
			puts("Yes");
		}
		else{
			puts("No");
		}
	}
	return 0;
}
```

---

