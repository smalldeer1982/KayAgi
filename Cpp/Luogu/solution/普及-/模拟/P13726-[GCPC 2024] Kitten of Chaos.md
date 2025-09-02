# [GCPC 2024] Kitten of Chaos

## 题目描述

Karen 在她客厅的架子上放着一个漂亮而珍贵的玻璃物品。不幸的是，她的猫 Klaus 并不喜欢在他最喜欢的架子上有东西。凡是没有被固定或粘住的东西，他都会一边盯着 Karen 的眼睛，一边慢慢地把它推到架子的边缘。

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/oh6p314l.png)

Klaus，在一场幸运地被 Karen 的保险覆盖的事件发生前的 10 秒。

:::

现在，Klaus 的爪子正在慢慢地实施他的恶作剧。他那可爱的毛茸茸的脸上流露出无意的无辜。Karen 知道任何干预都只能延缓不可避免的结果，她开始好奇她妹妹 Kim 写在珍贵玻璃物品上的字符串会变成什么样子。毕竟，Kim 花了一整周才收集齐所有组成该字符串的 $\texttt{bdpq}$ 字母。

你能告诉 Karen，当玻璃物品在掉落过程中，从她的视角看，这个字符串会变成什么样吗？

在掉落过程中，Karen 的珍贵玻璃物品会经历以下变换（从正面观察物品时）：

- $\texttt{h}$：水平翻转，例如 $\texttt{bbq}$ 变为 $\texttt{pdd}$
- $\texttt{v}$：垂直翻转，例如 $\texttt{bbq}$ 变为 $\texttt{ppd}$
- $\texttt{r}$：旋转 $180$ 度，例如 $\texttt{bbq}$ 变为 $\texttt{bqq}$

不会发生其他轴向的翻转或旋转。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
bbq
h```

### 输出

```
pdd```

## 样例 #2

### 输入

```
bbq
v```

### 输出

```
ppd```

## 样例 #3

### 输入

```
bbq
r```

### 输出

```
bqq```

## 样例 #4

### 输入

```
ppbddbq
hvrhv```

### 输出

```
bqppqdd```

# 题解

## 作者：uou203 (赞：3)

### 题意简述
给定一个由字符 $\texttt{bdpq}$ 组成的字符串 $s$，以及一个由操作 $\texttt{hvr}$ 组成的字符串 $t$。

然后模拟翻转或旋转操作后的结果。每个操作都会改变字符串：

$\texttt{h}$ 水平翻转：反转字符串顺序，并将每个字符映射为其水平镜像。

$\texttt{v}$ 垂直翻转：不反转字符串顺序，但将每个字符映射为其垂直镜像。

$\texttt{r}$ $180$ 度旋转：反转字符串顺序，并将每个字符映射为其 $180$ 度旋转后的镜像。

---
### 暴力做法
直接模拟。

时间复杂度：$O(|s| \times |t|)$，显然超时。

---
### 正确解法
我们注意到，每个操作实际上做了两件事：

1. 反转或不反转字符串。
2. 把每个字符映射到另一个字符。

所以我们可以将整个操作序列拆解为：

- 字符映射函数（从原始字符直接到最终字符）。
- 是否需要反转整个字符串。

因此，我们维护两个状态：

- $rev$：一个布尔值，表示最终是否需要反转字符串。
- $cur$：一个长度为 $4$ 的数组，表示当前字符映射。索引 $0$ 至 $3$ 分别对应 $\texttt{bdpq}$。

对于每个操作，我们更新 $rev$ 和 $cur$：

- 对于操作 $\texttt{h}$：$rev$ 取反，然后更新`cur_map`。
- 对于操作 $\texttt{v}$：`rev`不变，更新`cur_map`。
- 对于操作 $\texttt{r}$：`rev`取反，更新`cur_map`。

#### 什么这样做是正确的？
因为每个操作都可以看作是一个函数，这些函数可以组合。

而且，改变顺序的操作都会反转字符串的顺序，所以我们可以用异或操作来判断最终是否需要反转。

我们始终维护一个映射，表示从原始字符到当前状态的字符的映射。

当我们应用一个新操作时，我们将其映射应用到当前映射上。

例如，假设当前映射是 $u$，然后我们应用映射 $v$，那么新映射是 $v(u(x))$，即先应用 $u$，再应用 $v$。

---
### AC Code：
```cpp
#include <bits/stdc++.h>
using namespace std;

string s,t;
// b:0 d:1 p:2 q:3
// 水平翻转映射
// b-d d-b p-q q-p
int hor[5]={1,0,3,2};
// 垂直翻转映射
// b-p d-q p-b q-d
int ver[5]={2,3,0,1};
// 旋转 180 度映射
// b-q d-p p-d q-b
int rot[5]={3,2,1,0};
// 当前字符映射
int cur[5]={0,1,2,3};

// 将字符转换为索引
int char_id(char c){
	switch(c){
		case 'b':
			return 0;
			break;
		case 'd':
			return 1;
			break;
		case 'p':
			return 2;
			break;
		case 'q':
			return 3;
			break;
	}
	return -1;
}

// 将索引转换为字符
int id_char(int i){
	switch(i){
		case 0:
			return 'b';
			break;
		case 1:
			return 'd';
			break;
		case 2:
			return 'p';
			break;
		case 3:
			return 'q';
			break;
	}
	return -1;
}

int main(){
	cin >> s >> t;
	
	bool rev=false; // 是否需要反转
	for(char op:t){
		switch(op){
			case 'h':
				rev^=1; // 水平翻转需要反转
				for(int i=0;i<4;i++) cur[i]=hor[cur[i]];
				break;
			case 'v':
				for(int i=0;i<4;i++) cur[i]=ver[cur[i]];
				break;
			case 'r':
				rev^=1; // 180 度旋转需要反转
				for(int i=0;i<4;i++) cur[i]=rot[cur[i]];
				break;
		}
	}
	
	string res;
	int len=s.size();
	for(int i=0;i<len;i++){
		int id=char_id(s[i]);
		res+=id_char(cur[id]);
	}
	// 如果需要反转字符串
	if(rev) reverse(res.begin(),res.end());
	
	cout << res << "\n";
	return 0;
}
```
---
管理大大求通过~

---

## 作者：__coderyc__ (赞：2)

## 思路
一道字符串处理的好模拟题。

对每种情况的每种字符串的变化，自己进行一遍模拟，其中最后一种操作就相当于将前两种操作全部都执行一遍。

又注意到任意执行两遍相同的操作相当于没有执行，因此我们每一种操作是否执行设为未执行，等到发现操作序列里有这种操作时取反即可，最后再一起处理，不用遇到一次操作就做一次，节省大量时间。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
string s, t;
char hchar(char c) {
    switch(c) {
        case 'b': return 'd';
        case 'd': return 'b';
        case 'p': return 'q';
        case 'q': return 'p';
        default: return c; //凑数
    }
}
char vchar(char c) {
    switch(c) {
        case 'b': return 'p';
        case 'p': return 'b';
        case 'd': return 'q';
        case 'q': return 'd';
        default: return c; //还是凑数
    }
}
int main() {
    cin >> s >> t;
    bool reversed = false; 
    bool h = false;        
    bool v = false; 
    for (char op : t) {
        if (op == 'h') {
            reversed = !reversed;
            h = !h;
        } else if (op == 'v') {
            v = !v;
        } else if (op == 'r') {
            reversed = !reversed;
            h = !h;
            v = !v;
        }
    }
    string result = s;
    for (char &c : result) {
        if (h) c = hchar(c);
        if (v) c = vchar(c);
    }
    if (reversed) {
        reverse(result.begin(), result.end());
    }
    cout << result << endl;
    return 0;
}
```
时间复杂度为 $O (|s| + |t|)$，可以通过此题。
## 彩蛋
喵呜好可爱。

---

## 作者：hcx2012 (赞：1)

比较简单的一道题，这里抢一个题解。

:::info[题意]{open}
给定一个只含有 `bdpq` 的字符串和若干个操作，进行：

- `h`，水平翻转。
- `v`，垂直翻转。
- `r`，旋转 180°。
:::

我们发现 `r` 操作可以由一个 `h` 操作和一个 `v` 操作替换。

注意到这里任意一个操作进行两次都没有对字符串进行改变。

使用一个桶，记录 `hv` 两种操作的次数，若为奇数次则模拟操作即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
int a[220];
void h(string &s){
    char replace[222];
    replace['b']='d';
    replace['d']='b';
    replace['p']='q';
    replace['q']='p';
    reverse(s.begin(),s.end());
    for(auto &i:s){
        i=replace[i];
    }
}
void v(string &s){
    char replace[222];
    replace['b']='p';
    replace['d']='q';
    replace['p']='b';
    replace['q']='d';
    for(auto &i:s){
        i=replace[i];
    }
}
int main(){
    ios::sync_with_stdio(0);
    string s;
    cin>>s;
    string op;
    cin>>op;
    string real_op;
    for(auto i:op){
        if(i=='r'){
            real_op+="hv";
        }else real_op+=i;
    }
    for(auto i:real_op){
        (a[i]+=1)%=2;
    }
    if(a['h'])h(s);
    if(a['v'])v(s);
    cout<<s;
    return 0;
}
```

---

## 作者：Loyal_Soldier (赞：1)

### 思路

我们发现，进行两次 $\tt{h}$ 操作后，字符串不变。同理，进行两次 $\tt{v}$ 操作或 $\tt{r}$ 操作，字符串不变，即进行偶数次同样的操作，此操作不会改变字符串，进行奇数次才会改变字符串。于是，可以用三个变量 $h, v, r$ 分别记录三种操作是否要进行，最后直接模拟一遍就行了，具体实现见代码。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int N = 5;
char b[N] = {'d', 'p', 'q'};//b[0] 表示 b 进行 h 操作会变成什么，b[1] 表示 b 进行 v 操作会变成什么，b[2] 表示 b 进行 r 操作会变成什么。以下同理
char q[N] = {'p', 'd', 'b'};
char d[N] = {'b', 'q', 'p'};
char p[N] = {'q', 'b', 'd'};
bool h, v, r;//h,v,r 分别代表 h,v,r 操作是否要进行
signed main()
{
	string s, t;
	cin >> s >> t;
	for(int i = 0;i < t.size();i ++)
	{
		if(t[i] == 'h') h = !h;//改变 h
		else if(t[i] == 'v') v = !v;//改变 v
		else r = !r;//改变 r
	}
	if(h)//进行 h 操作
	{
		reverse(s.begin(), s.end());//h 操作需要翻转字符串
		for(int i = 0;i < s.size();i ++)
		{
			if(s[i] == 'b') s[i] = b[0];
			else if(s[i] == 'q') s[i] = q[0];
			else if(s[i] == 'd') s[i] = d[0];
			else s[i] = p[0];
		}//改变字符
	}
	if(v)//进行 v 操作
	{//v 操作不需要翻转字符串
		for(int i = 0;i < s.size();i ++)
		{
			if(s[i] == 'b') s[i] = b[1];
			else if(s[i] == 'q') s[i] = q[1];
			else if(s[i] == 'd') s[i] = d[1];
			else s[i] = p[1];
		}//改变字符
	}
	if(r)//进行 r 操作
	{
		reverse(s.begin(), s.end());//r 操作需要翻转字符串
		for(int i = 0;i < s.size();i ++)
		{
			if(s[i] == 'b') s[i] = b[2];
			else if(s[i] == 'q') s[i] = q[2];
			else if(s[i] == 'd') s[i] = d[2];
			else s[i] = p[2];
		}//改变字符
	}
	cout << s;
	return 0;
}
```

---

## 作者：Peruere_Arlecchino (赞：0)

## solution idea：
我的思路是通过记录字符映射关系和字符串是否需要反转的状态，来高效的处理一系列翻转和旋转操作。在面对每个变换（水平翻转、垂直翻转、$180$ 度旋转），只需更新字符映射规则以及反转标记，不需要实时的修改整个字符串。当所有操作处理完毕后，就一次性将原始字符串按映射规则转换，并且根据反转标记来决定是否反转字符串，最终得到结果即可。
## code：
```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
char h(char c) {
    switch(c) {
        case 'b': return 'd';
        case 'd': return 'b';
        case 'p': return 'q';
        case 'q': return 'p';
        default: return c;
    }
}
char v(char c) {
    switch(c) {
        case 'b': return 'p';
        case 'p': return 'b';
        case 'd': return 'q';
        case 'q': return 'd';
        default: return c;
    }
}
char r(char c) {
    return v(h(c));
}
int main() {
    string s, t;
    cin >> s >> t;
    bool f = false;
    char m[4] = {'b', 'd', 'p', 'q'};
    for (char o : t) {
        if (o == 'h') {
            f = !f;
            for (int i = 0; i < 4; i++)
                m[i] = h(m[i]);
        } else if (o == 'v') {
            for (int i = 0; i < 4; i++)
                m[i] = v(m[i]);
        } else if (o == 'r') {
            f = !f;
            for (int i = 0; i < 4; i++)
                m[i] = r(m[i]);
        }
    }
    string r = s;
    for (char &c : r) {
        switch(c) {
            case 'b': c = m[0]; break;
            case 'd': c = m[1]; break;
            case 'p': c = m[2]; break;
            case 'q': c = m[3]; break;
        }
    }
    if (f) reverse(r.begin(), r.end());
    cout << r << endl;
    return 0;
}
```
求赞求过。

---

## 作者：imnotcfz (赞：0)

一道简单的模拟题，但细节还是挺多的。

# 0x01 分析

首先我们需要知道这三条铁律：

1. 翻转满足交换律。
1. 翻转两次等于没翻转。
1. 旋转 $180^{\circ}$ 等于水平翻转+垂直翻转。

根据第一条，我们并不需要按顺序执行 $t$ 中的每个操作，只需记录操作次数即可。

根据第二条，我们并不需要执行所有的操作，仅当操作次数为奇数时执行。

根据第三条，我们并不需要专门写旋转 $180^{\circ}$ 的代码，而可以将其转化为翻转。

# 0x02 实现

一些小细节（和血与泪的教训）：

- 翻转字符串时**使用头插（`tmp = s[i] + tmp`）的复杂度为 $O(n^2)$**。
- 字符替换时**绝对不要使用连续`if`**。

Talk is cheap, show me the code!

```cpp line-numbers
#include <algorithm>
#include <iostream>
using namespace std;

string s, op;
bool h, v;  // 我们只关心操作次数的奇偶性

int main() {
  // 无需开 I/O 优化即可通过本题
  // 但开了可以砍掉一半的时间
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> s;
  cin >> op;
  for (auto i : op) {
    if (i == 'r') h ^= 1, v ^= 1;
    else if (i == 'h') h ^= 1;
    else if (i == 'v') v ^= 1;
  }
  if (h) {
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == 'b') s[i] = 'd';
      else if (s[i] == 'd') s[i] = 'b';
      else if (s[i] == 'p') s[i] = 'q';
      else if (s[i] == 'q') s[i] = 'p';
    }
    reverse(s.begin(), s.end());  // STL 大法好
  }
  if (v) {
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == 'b') s[i] = 'p';
      else if (s[i] == 'd') s[i] = 'q';
      else if (s[i] == 'p') s[i] = 'b';
      else if (s[i] == 'q') s[i] = 'd';
    }
  }
  cout << s;
  return 0;
}
```

---

## 作者：Doraeman (赞：0)

## 简化题意
给定一个字符串 $s$，输出对它进行若干次**水平翻转、垂直翻转、$180\degree$ 旋转**后的结果。

## 旋转
现在，我们需要分别写 $3$ 种旋转方式的代码。

### 水平翻转
观察自测样例：```bbp``` $\rightarrow$ ```pdd```。  
可以发现：**水平翻转就是整个字符串从右往左看，每个字母也都要从右往左看**。

#### 字母从右往左看
分类讨论 $4$ 种字母：

- b $\rightarrow$ d；
- d $\rightarrow$ b；
- p $\rightarrow$ q；
- q $\rightarrow$ p。

循环对每个字母都进行更改即可。

```cpp
for(int i=0; i<s.size(); i++)
    if(s[i] == 'b') s[i] = 'd';
    else if(s[i] == 'd') s[i] = 'b';
    else if(s[i] == 'p') s[i] = 'q';
    else s[i] = 'p';
```

#### 字符串从右往左看
设 $s$ 下标从 $0$ 开始。  
那么，对于所有的整数 $i$ 满足 $0\le i<\lfloor\frac{|s|}{2}\rfloor$，只要交换 $s_i$ 与 $s_{|s|-i-1}$ 的值，就可以实现。

```cpp
for(int i=0; i<s.size()/2; i++)
    swap(s[i], s[s.size()-i-1]);
```

### 垂直翻转
垂直翻转更加简单：**所有字母从下往上看**。

仍然分类讨论：

- b $\rightarrow$ p；
- d $\rightarrow$ q；
- p $\rightarrow$ b；
- q $\rightarrow$ d。

```cpp
for(int i=0; i<s.size(); i++)
    if(s[i] == 'b') s[i] = 'p';
    else if(s[i] == 'd') s[i] = 'q';
    else if(s[i] == 'p') s[i] = 'b';
    else s[i] = 'd';
```

### 旋转 $180\degree$
观察可以发现规律：**旋转 $180\degree$ 的操作就是水平翻转 $+$ 垂直翻转**。  
直接调用那两个函数就可以了。

## 细节
最后还有一件非常重要的事情：**每个实现函数的时间复杂度都是 $\operatorname{O}{(N)}$**。（$N$ 是字符串长度）。  
也就是说，如果我们遍历字符串 $t$ 并根据每个字符进行旋转操作，时间复杂度最高可达 $\operatorname{O}{(N^2)}$。~~快乐地超时了。~~

再次观察规律：这 $3$ 种操作中无论什么操作，翻转 $2$ 次与不翻转效果相同。  
所以可以记录每种操作出现的次数，最后再对 $2$ 取模。  
也可以使用 bool 值记录，在循环中每次遇到对应字符就取反。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

string s, opt;
int h, v, r;

void H(){
    for(int i=0; i<s.size(); i++)
        if(s[i] == 'b') s[i] = 'd';
        else if(s[i] == 'd') s[i] = 'b';
        else if(s[i] == 'p') s[i] = 'q';
        else s[i] = 'p';
    for(int i=0; i<s.size()/2; i++)
        swap(s[i], s[s.size()-i-1]);
}
void V(){
    for(int i=0; i<s.size(); i++)
        if(s[i] == 'b') s[i] = 'p';
        else if(s[i] == 'd') s[i] = 'q';
        else if(s[i] == 'p') s[i] = 'b';
        else s[i] = 'd';
}
void R(){
    H(); V();
}

int main(){
    cin >> s >> opt;
    for(int i=0; i<opt.size(); i++)
        h ^= (opt[i] == 'h'),
        v ^= (opt[i] == 'v'),
        r ^= (opt[i] == 'r');

    if(h) H();
    if(v) V();
    if(r) R();

    cout << s;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

前两个操作都是转 $180\degree$ 的，所以两次操作会抵消，即我们只需要维护进行前两个操作的次数的奇偶性即可。注意到 `r` 操作其实相当于一个 `h` 和一个 `v` 操作，所以我们把 `r` 拆掉然后也用于计算前两个操作的奇偶性。

最后直接对 `h` 和 `v` 操作模拟就行。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	string t;
	cin>>s>>t;
	int a=0,b=0;
	for(int i=0;i<t.size();i++)
	{
		if(t[i]=='h') a=!a;
		if(t[i]=='v') b=!b;
		if(t[i]=='r') a=!a,b=!b;
	}
	if(a)
	{
		for(int i=0;i<s.size();i++)
		{
			if(s[i]=='b') s[i]='p';
			else if(s[i]=='d') s[i]='q';
			else if(s[i]=='p') s[i]='b';
			else if(s[i]=='q') s[i]='d';
		}
	}
	if(b)
	{
		reverse(s.begin(),s.end());
		for(int i=0;i<s.size();i++)
		{
			if(s[i]=='b') s[i]='d';
			else if(s[i]=='d') s[i]='b';
			else if(s[i]=='p') s[i]='q';
			else if(s[i]=='q') s[i]='p';
		}
	}
	cout<<s;
}

---

## 作者：WritingLetter (赞：0)

## 暴力
拿到题目，先可以想个暴力。对于这题，暴力就是普通模拟，依照题目意思，我们按照三种操作依次去做即可。时间复杂度 $O(st)$，看眼数据范围，啧，都是 $5e5$，那还是算了吧。

## 正解
考虑优化，首先，这些操作本质都是 $180°$ 的操作，那么偶数次的操作会回归原串，这里作出通俗点的解释：
- 将一本书封面朝上平放于桌面。
- 水平翻转两次：每次固定书的右沿，向右翻两次。
- 垂直翻转两次：每次固定书的下沿，向下翻两次。
- $180°$ 旋转两次：每次固定书的中心，向右旋转 $180°$ 两次。
- 可以自己拿本书试试，发现没有改变原状。

于是得到第一次优化：**对于连续的同一个操作，只有操作次数为奇数时，才对原串有所改变。**

但是如果所有操作都交替出现，那么时间复杂度依旧高达 $O(st)$。接下来就有一点抽象了。我们将三个操作拆分，会得到**五个操作**：
- 水平翻转：将字符串整体翻转，每个字符变化。
- 垂直翻转：每个字符变化。
- $180°$ 旋转：将字符串整体翻转，每个字符变化。

**这些操作实际上对顺序没有任何要求**，通俗理解：你有一排盒子，整体翻转是盒子之间的移动，每个字符操作则是盒子内的东西被替换，无论先进行什么操作都不影响结果。

得到第二个优化：`hvrhv` 这样的操作，可以**同类的放一起，不影响答案**：`hhvvr`。

哎？这不就可以用上第一个优化了吗！

### 最终思路
对于三种操作，计算操作总和，奇数次的才要操作，偶数次的直接忽略。时间复杂度为 $O(3s)$ 即 $O(s)$。

### 一些注意事项
- 一定要一一对应好每个字符转换后是什么。
- 字符串下标默认从 $0$ 开始。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=5e5+5;//注意范围

string s,t;
int h,v,r;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);

	cin>>s>>t;
	int sl=s.size(),tl=t.size();
	for(int i=0;i<tl;i++){
		if(t[i]=='h') 
			h^=1;//异或1等价于+1再取模，用于计算是否操作奇数次
		if(t[i]=='v') 
			v^=1;
		if(t[i]=='r') 
			r^=1;
	}
	
	if(h){//奇数次
		reverse(s.begin(),s.end());//字符串翻转函数
		for(int i=0;i<sl;i++){//记得一一对应
			if(s[i]=='b')
				s[i]='d';
			else if(s[i]=='d')
				s[i]='b';
			else if(s[i]=='p')
				s[i]='q';
			else 
				s[i]='p';	
		}
	}
	if(v){//这个不用整体翻转
		for(int i=0;i<sl;i++){
			if(s[i]=='b')
				s[i]='p';
			else if(s[i]=='d')
				s[i]='q';
			else if(s[i]=='p')
				s[i]='b';
			else 
				s[i]='d';	
		}
	}
	if(r){
		reverse(s.begin(),s.end());
		for(int i=0;i<sl;i++){
			if(s[i]=='b')
				s[i]='q';
			else if(s[i]=='d')
				s[i]='p';
			else if(s[i]=='p')
				s[i]='d';
			else 
				s[i]='b';	
		}
	}
	
	for(int i=0;i<sl;i++)
		cout<<s[i];
	return 0;
}
```
整体就是这样了，如果有不懂或者错误请随时私信我或在评论区指出，感谢！求赞 qwq。

---

