# ABBB

## 题目描述

Zookeeper is playing a game. In this game, Zookeeper must use bombs to bomb a string that consists of letters 'A' and 'B'. He can use bombs to bomb a substring which is either "AB" or "BB". When he bombs such a substring, the substring gets deleted from the string and the remaining parts of the string get concatenated.

For example, Zookeeper can use two such operations: AABABBA $ \to $ AABBA $ \to $ AAA.

Zookeeper wonders what the shortest string he can make is. Can you help him find the length of the shortest string?

## 说明/提示

For the first test case, you can't make any moves, so the answer is $ 3 $ .

For the second test case, one optimal sequence of moves is BABA $ \to $ BA. So, the answer is $ 2 $ .

For the third test case, one optimal sequence of moves is AABBBABBBB $ \to $ AABBBABB $ \to $ AABBBB $ \to $ ABBB $ \to $ AB $ \to $ (empty string). So, the answer is $ 0 $ .

## 样例 #1

### 输入

```
3
AAA
BABA
AABBBABBBB```

### 输出

```
3
2
0```

# 题解

## 作者：_Scaley (赞：2)

考试难得第一道题 A 了，写个题解庆祝一下

# 题目简要：

有一个只由 A 和 B 组成的字符串，每次可以消去 “AB” 或者 “BB” 的组合（消除后剩余字符还是连在一块的），问经过若干次消除后最少能剩下几个字符。

# 题目分析：

这道题算是一个贪心题，我们可以想象一下：

如果遇到一个 “AB” 或者 “BB” 的话就删，那么最后可能会出现原本可以与其他字符组合时可以被消除的字符被留了下来，一些用其他方式消除的字符也被留了下来，显然这不是最优的。

这时候可以**从被消除的字符序列的角度**考虑：

“AB” 和 “BB” 可以被消除，可以看出：

* “B” 字符无论在前面是与 “A” 字符组合还是与 “B” 字符组合都可以被消除。

* “A” 字符只能在后面有 “B” 的情况下才能被消除。

我们的目的是使最后的字符达到最少，显然 “A” 字符能被消除就去消除，而 “B” 字符能和 “A” 字符组合就与 “A” 字符组合，最后呈现的字符串一定是两种情况：

“BAAA…A” 或者 “AAAA…A”。

### 那么正解也就出来了：

1. 先从头到尾扫一遍字符串，如果在 “A” 字符后面发现有 “B” 字符就消除。（可以用栈来维护）

2. 最后将经过操作 1 的字符串再从头到尾扫一遍，如果出现 “BB” 序列就消除。

3. 输出经过操作 1 和操作 2 的字符串的长度。

# 代码实现：

```
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define MAXN 3000010
using namespace std;

int T, l, top = 0, ans;
char sta[MAXN], s[MAXN]; // sta 是栈，s 为原字符串

int read() { // 快读
  int s = 0, f = 0; char ch = getchar();
  while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
  while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
  return f ? -s : s;
}

int main() {
	//freopen("a.in", "r", stdin);
	//freopen("a.out", "w", stdout);
	
	T = read();
	for (int t = 1; t <= T; ++t) {
		scanf("%s", s);
		l = strlen(s); top = 0; // 记得要清空栈
		sta[++top] = s[0]; // 将第一个字符放进栈里
		for (int i = 1; i < l; ++i) {
			if (s[i] == 'A') sta[++top] = s[i]; // 如果字符为 “A” 放进栈里
			else if (sta[top] == 'A') top--; // 否则当字符为 “B” 时查看栈顶是否为 “A”，如果是，则让 “A” 出栈
			else sta[++top] = s[i]; // 如果不是，将 “B” 压入栈里
		}
		ans = top;
		for (int i = 2; i <= top; ++i)
			if (sta[i] == 'B' && sta[i - 1] == 'B') {
				i++; // 如果有 “BB” 字符序列，将 i 指到下一位字符
				ans -= 2; // ans 减去 2
			}
		printf("%d\n", ans); // 输出答案
	}
	
	//fclose(stdin); fclose(stdout);
	return 0;
}
```

---

## 作者：Zxsoul (赞：2)

## 题面
- 一个由 $A$ 和 $B$ 组成的序列， $AA$ 和 $AB$ 的组合删除，求剩余数

## 思路
- 显而易见需要一个栈进行维护

- 当前字符和栈顶满足条件就直接让栈顶出站，否则入栈 

- 还需考虑当栈为空时，应该直接入栈

- 手写栈或手写队列要考虑时间，以防卡常

## Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;

const int manx=1e6+10;
const int mamx = 1e6 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar(); int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}
int n;
char a[manx];
int st[manx],top;
int main(){
	n = read();
	while(n--){
		top = 0;
		cin >> a;
		int ans = 0;
		int s = strlen(a);
		st[++top] = a[0]-'A';
		for(int i =  1; i<= s - 1; i++){
			if(top == 0){st[++top] = a[i] - 'A';continue;} 
			int k = st[top];
			if(k == 0 && a[i]-'A' == 1){ top--;continue;}
				else if(k == 1 && a[i]-'A' == 1){top--;continue;}
						else{
					 		st[++top] = a[i]-'A';
						}
		}
		cout<<top<<endl;
	}
	return 0;
}


```
---


---

## 作者：pigstd (赞：2)

貌似用的都是栈的方法，其实本题也可以用链表做。

很容易想到一个显然的贪心：先从后往前删去 $\text{AB}$ ，然后再从后往前删去 $\text{BB}$。

但是删去了之后怎么维护呢？用双向链表维护就可以了。

用 $l_i$ 表示 $i$ 下一个的字母的下标，$r_i$ 表示 $i$ 上一个字母的下标，那么显然删去 $i$ 和 $i+1$ 时，令 $l_{r_i}=l_{l_i},r_{l_i}=r_{r_i}$ 就可以了。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int M=2e5+10;
int T,l[M],r[M],vis[M];
char s[M];

inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>s+1;int n=strlen(s+1);int ans=0;
		for (int i=1;i<=n;i++)vis[i]=0,l[i]=i+1,r[i]=i-1;
		for (int i=n-1;i>=1;i--)
			if (!vis[i]&&!vis[l[i]]&&s[i]=='A'&&s[l[i]]=='B')
			{
				ans+=2;
				l[r[i]]=l[l[i]];
				r[l[i]]=r[r[i]];
				vis[i]=vis[l[i]]=1;
			}
		for (int i=n-1;i>=1;i--)
			if (!vis[i]&&!vis[l[i]]&&s[i]=='B'&&s[l[i]]=='B')
			{
				ans+=2;
				l[r[i]]=l[l[i]];
				r[l[i]]=r[r[i]];
				vis[i]=vis[l[i]]=1;
			}
		cout<<n-ans<<endl;
	}
	return 0;
}
```

---

## 作者：KEBrantily (赞：1)

## Description

>
>有一个只包含'A'与'B'的字符串，每次可以消掉一个 “AB” 或一个   “BB”，并把剩下的拼在一起，求字符串最短的长度。
>



------------

题意已经够简洁了；

这是今天校内魔泥赛唯一一道水题。

------------
## Solution

### 1.

可以用栈维护元素。

这里推荐用 STL 里的 stack，可能有点慢，但是好用也不会超时；

手写栈清空时直接把头指针归零就好了，memset 遇到大数据会被卡。

### 2.

如果用贪心做此题，要注意修改的优先性。

一定是先消除所有的 “AB”，再消除剩下的 “BB”。

#### 正确性证明：

如果优先消除 “BB”，可能会出现剩余的 “A” 无法被消除的情况。

比如 “AAAABBBB”，正确的做法是每一个 “A” 与“B”组队消除，剩下的依次拼接消除，答案是 0；

如果优先消除了 “BB” 或者遇到哪一对消除哪一对，可能会有  “A” 剩余，剩下 “AAAA” 或者 “AA” 的情况，而这并不是最短的。



------------
我用的 STL 维护栈~~毕竟好写~~

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>

using namespace std;

int t;
string a;
stack<int> st;

int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0' ||ch>'9'){
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') s=(s<<1)+(s<<3)+ch-'0',ch=getchar();
	return s*w;
}

int main(){
	t=read();
	for(int i=0;i<t;i++){
		cin>>a;
		int tot=a.length();
	    st.push(a[0]);
	    for(int j=1;j<tot;j++){
            if(st.size()){
	    	    if(a[j]=='B' &&((char)st.top()=='A'||(char)st.top()=='B')){
	    		    st.pop();
	    	    	continue;
			    }
			}
			st.push(a[j]);
		}
		printf("%d\n",st.size());
		while(st.size()) st.pop();
	}
	return 0;
}
```


------------


---

## 作者：jun头吉吉 (赞：1)

# CF1428C 【ABBB】
[$\text{更の阅读体验}$](https://chen-jia-liang.gitee.io/blog/2020/10/18/%E9%A2%98%E8%A7%A3-CF1428C-%E3%80%90ABBB%E3%80%91/)
## 题意

有一个只包含`'A'`与`'B'`的字符串，每次可以消掉一个`"AB"`或一个`"BB"`，并把剩下的拼在一起，求字符串最短的长度。

## 题解
打CF的时没什么思路，于是就用贪心乱搞了一下。

操作类似于栈，如果当前输入`'B'`且栈非空，那么就把栈顶弹出，即原文中的删除操作，否则就把当前字母加入。

可以证明，这样的方案必定是最优的。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;char c[200000+100];
signed main(){
	scanf("%d",&t);
	while(t--) {
		scanf("%s",c+1);n=strlen(c+1);
		stack<char>s;
		for(int i=1;i<=n;i++)
			if(s.size()&&c[i]=='B')s.pop();
			else s.push(c[i]);
		printf("%d\n",s.size());
	}
	return 0;
}
```

---

## 作者：Rainy7 (赞：1)

- **分析**

  可以想到用栈来处理。
  
  每读入一个 `B` 。只要此时栈内有一个 `A` 或 `B` ，就可以弹出栈顶。
  
  所以直接跑一遍就可以了。
  
  复杂度 $O(n)$ 。
  

------------

  
- **代码**

```cpp
    #include<iostream>
    #include<cstdio>
    #include<cmath>
    #include<cstring> 
    using namespace std;
    const int Maxn=200000+5;
    int T,n,top,cnt;
    char s[Maxn],s2[Maxn],st[Maxn];
    int main()
    {	scanf("%d",&T);
    	while(T--)
    	{	top=0;cnt=0;
    		scanf("%s",s+1);
    		n=strlen(s+1);
    		for(int i=1;i<=n;i++)
    		{	if(s[i]=='B'&&top>0)top--;
    			else st[++top]=s[i];
    		}
    		printf("%d\n",top);
    	}
    	return 0;
    }
```


---

## 作者：Binaries (赞：0)

# 前言

- 给过吧QWQ，至今没过过题解

# 思路

- 由于 B 的作用似乎更大一些，所以我们可以考虑节约用 B 。

- 我们注意到，若 B 与 A 匹配，则一个 B 便可以对答案作出 -2 的贡献，而 B 与 B 匹配则需要两个 B 。

- 这就意味着，我们要尽可能多地将 B 与 A 匹配。

- 那么怎么匹配呢？

- 显然， B 只能与其前面的 A 匹配，所以便有了以下几点：

  - 当某一位是 B 时，如果还有 A 未被匹配，则将 B 与该 A 匹配，如果没有，则在后面的位置也不可能再有 A 与 B 匹配（因为顺序一定），可以将其扔入“废品堆”（即无法继续与 A 匹配的 B）。
  
  - 当某一位是 A 时，将 A 的数量加一，方便后面的 B 匹配。

- 注意到我们只是简单粗暴地统计 A 的个数，那么，怎么保证 B 一定能匹配到前面的 A 呢？  

- 这并不难，由于原序列只有 A 和 B 两种字符，那么在原序列中，当前的 B 与想与其匹配的 A 中间只会有 A 与 B 两种字符。

- 而它们中间能够匹配的 A 与 B 都已经两两匹配，如果中间剩余了一个 B ，那么该 A 一定会优先与剩余的 B 匹配而不是当前的 B，反之，如果中间剩余了若干个 A，那么当前的 B 一定会优先与最靠后的 A 匹配。

- 综上所述，当找到一个 B 并且还有 A 没有匹配时，该 B 一定能够成功匹配。

- 统计完了以后，对于没有匹配 A 需要直接计入答案，而剩余的 B 则可以两两匹配，剩余的 B 与其奇偶性一致。

- 根据以上思路，我们可以写出以下代码。

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;
int AA,BB,T;string s;
int main(){
	scanf("%d",&T);
	while(T--){
		AA=0,BB=0;
		cin>>s;int le=s.length();
		for(register int i=0;i<le;++i)
			BB+=((AA==0)&&(s[i]=='B')),
			AA+=((s[i]=='B')?((AA==0)?0:-1):1);
		printf("%d\n",AA+(BB&1));
	} 
	return 0;
}
```

# 后语

- 这是一道不错的贪心题，值得研究。

- 另外，给蒟蒻过了吧QWQ

---

## 作者：Durancer (赞：0)

#### 题目思路

1、组成的一定是？B,所以遇到B的时候要处理


2、用栈做，如果是A就放进去，如果是B,判断一下栈里有没有元素，如果有就弹出，没有就放进栈里面，当操作进行完的时候，找一找栈里还有多少元素输出就行了;

#### 代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
using namespace std;
int T;
char s[2000009];
int main()
{
	cin>>T;
	stack<char> st;
	for(int i=1;i<=T;i++)
	{
		cin>>(s+1);
		int len=strlen(s+1);//将第一个标号弄为1
		for(int j=1;j<=len;j++)
		{
			if(s[j]=='A')
			{
				st.push('A');
			}
			else if(!st.empty())
			{
				st.pop();//如果当前不是A并且栈里面不为空，就弹出来就行了 
			}
			else st.push('B'); 
		}
		int ans=0;
		while(!st.empty())
		{
			ans++;
			st.pop();
		}
		cout<<ans<<endl;
	}
	return 0;
} 
```


---

## 作者：gyh20 (赞：0)

又一个贪心。

将所有字母从前往后加入队列，若果当前加入的是 $B$ 且队列不为空就弹掉队首，表示删去这个字符。

为什么这样没有后效性？

因为我们能删的只有 $AB$ 和 $BB$，所以只要这一位是 $B$，前面无论是什么都无关，所以删掉一定是最优的。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,t,a[1002],b,c,d,p[1002];
char s[300002];
queue<char>q;
int main(){
	t=read();
	while(t--){
		scanf("%s",s+1);
		n=strlen(s+1);
		re int ans=0;
		while(!q.empty())q.pop();
		for(re int i=1;i<=n;++i){
			if(q.empty())q.push(s[i]);
			else if(s[i]=='A')q.push(s[i]);
			else q.pop(),ans+=2; 
		}
		printf("%d\n",n-ans);
	}
}
```


---

## 作者：江户川·萝卜 (赞：0)

### 题意：
将一个`AB`串通过若干次删减操作（删`AB`或`BB`）使该字符串变得最短。求最短的字符串长度。

---
### 解法：
~~ABC题怎么都是简单思维题啊~~

消掉`AB`，相当于前面一个`A`后面一个`B`相抵消。

注意不能前面的`B`抵消后面的`A`。

于是得出策略：
1. 遇到`A`时，统计A的个数。
2. 遇到`B`时，优先抵消前面的`A`，并统计剩余B的个数。

最后可以消掉`BB`来减少B的个数。

---
### 代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int T,len,bcnt,acnt;
string s;
int main(){
	scanf("%d",&T);
	while(T--){
		cin>>s;
		len=s.length();
		bcnt=acnt=0;
		for(int i=0;i<len;i++){
			if(s[i]=='B'){
				bcnt++;
				if(acnt) bcnt--,acnt--;
			}
			if(s[i]=='A') acnt++;
		}
		printf("%d\n",bcnt%2+acnt);
	}
	return 0;
}
```

---

## 作者：smallfang (赞：0)

我们发现 只有 $AB$ $BB$ 我们发现第二位都是 $B$ ，那么我们只需要从左到右发现一个 $B$，就将一个前面的连带删除。需要注意，每次删除时，如果 $length > 1$ 才可以算数。最后输出长度即可。

Code:

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>

using namespace std;

const int N = 1e5 + 5;

int a[N];

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t -- )
	{
		string str;
		cin >> str;
		int len = str.size();
		int cnt = 1;
		for (int i = 1; i < len; i ++ )
		{
			cnt ++;
			if (str[i] == 'B')
			{
				if (cnt > 1)
				{
					cnt -= 2;
				}
			}
		}
		cout << cnt << endl;
	}
	return 0;
}
```

---

## 作者：Ryo_Yamada (赞：0)

> 给定一个由 $A,B$ 组成的字符串，每次可以取连续的两个字符 $AB$ 或 $BB$ 消除，问最后最少剩下几个字符。

考虑贪心。由于 $A$ 只能从字符串 $AB$ 被消除，而 $B$ 可以从 $AB$ 和 $BB$ 被消除。所以优先使用 $AB$ 消除 $A$，用剩下的 $BB$ 消除 $B$。

使用栈维护，遇到 $B$，若栈为空或栈顶为 $B$ 则入栈。否则将栈顶的 $A$ 出栈，将 $\operatorname{ans}+\,2$。若遇到 $A$ 直接入栈。

循环结束，栈内形式必为 $BBBAAA$，若 $B$ 之前有 $A$ 那么早就已经出栈，剩下的 $A$ 都是没有 $B$ 配对的，所以直接弹出即可。剩下的 $B$ 都是可以消除的，若剩下 $B$ 的个数为奇数则有一个是不能消除的。

$\text{Code}$：

```cpp

int main() {
	ios::sync_with_stdio(0);
 	int T;
 	cin >> T;
 	w(T) {
 		int ans = 0;
 		string s;
 		cin >> s;
 		stack<char> st;
 		while(!st.empty()) st.pop();
 		for(int i = 0; i < s.size(); i++) {
 			if(s[i] == 'B') {
 				if(st.empty() || st.top() != 'A') st.push(s[i]);
				else st.pop(), ans += 2;
			}
			else st.push(s[i]);
		}
		while(!st.empty() && st.top() == 'A') st.pop();
		ans += st.size();
		ans -= (st.size() & 1);
		printf("%d\n", s.size() - ans);
 	}
	return 0;
}
```


---

