# [AGC040A] ><

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc040/tasks/agc040_a

長さ $ N-1 $ の文字列 $ S $ が与えられます． $ S $ の各文字は `<` または `>` です．

長さ $ N $ の非負整数列 $ a_1,a_2,\cdots,a_N $ は， すべての $ i $ ($ 1\ \leq\ i\ \leq\ N-1 $) について次の条件をみたす時，**良い非負整数列**と呼ばれます．

- $ S_i= $ `<` のとき： $ a_i\ <\ a_{i+1} $
- $ S_i= $ `>` のとき： $ a_i\ >\ a_{i+1} $

良い非負整数列の要素の総和としてありうる最小の値を求めてください．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ S $ は `<` と `>` のみから成る長さ $ N-1 $ の文字列．

### Sample Explanation 1

$ a=(0,2,1,0) $ は良い非負整数列であり， この場合の要素の総和は $ 3 $ になります． 要素の総和が $ 3 $ より小さい良い非負整数列は存在しません．

## 样例 #1

### 输入

```
<>>```

### 输出

```
3```

## 样例 #2

### 输入

```
<>>><<><<<<<>>><```

### 输出

```
28```

# 题解

## 作者：rui_er (赞：6)

~~看一下这道题的题面，决定放弃这道题，~~突然想起在 $\text{Atcoder}$ 上可能会有英文翻译，便到原题看了一眼，真的有。题意大概是：

- 输入一个仅由 $\lt$ 和 $\gt$ 组成的字符串 $s$ ，假设共 $l$ 位；
- 请你构造一个共 $l+1$ 位数列 $a$ ，满足 $\sum a_i$ 最小，同时 $a_i$ 与 $a_{i+1}$ 的关系是 $s_i$ 中的字符（即：大于或小于）。
- 输出 $\sum a_i$

看了一眼数据规模，想到一个 $O(n)$ 的暴力解法：

- 从前往后扫一遍字符串，构造 $s_i='\lt'$ 对应的值，具体方法： $a_{i+1}=a_i+1$ ，可以证明这是最优方案；
- 从后往前扫一遍字符串，构造 $s_i='\gt'$ 对应的值，具体方法： $a_i=\max(a_i, a_{i+1}+1)$ ，可以证明这是最优方案。

最后再扫一遍记好的数组，记录 $ans=\sum a_i$ ，输出即可，**注意 $ans$ 可能需要使用 $\text{long long}$**。

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string s;
ll l, a[500001];
ll ans; 

int main()
{
	cin>>s;
	s = " " + s;
	l = s.length() - 1;
	for(int i=1;i<=l;i++) (s[i] == '<') ? (a[i+1] = a[i] + 1) : (a[i+1]);
	for(int i=l;i>=1;i--) (s[i] == '>') ? (a[i] = max(a[i], a[i+1]+1)) : (a[i]);
	for(int i=1;i<=l+1;i++) ans += a[i];
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：RyanCh (赞：0)

题意：

用一个长度为 $N - 1$ 的字符串 $S$ ， 表示其左右两个数的关系， 表示其左右两个数字的关系式， 使解出来的数字之和最小。

分析：

用 $a_i$ 表示当前求解的数， 我们易得如下几种情况：

1. 如果 $a_i$ , $a_{i - 1}$ , $a_{i + 1}$ 的关系式为 $a_{i - 1} < a_i < a_{i + 1}$ 则 $a_i = 0$ ；

2. 与上一条同理， 若 $a_1 <a_2$ ， 则 $a_i = 0$ ； 若 $a_{n - 1} > a_n$ 则 $a_n = 0$ ;

3. 如果不属于以上两种情况， 若 $a_i < a_{i + 1}$ 且 $a_i$ 已得而不影响其他的情况下， $a_{i + 1} = a_i + 1$ ;

4. 否则， 若 $a_i > a_{i + 1}$ , 可以证明有一个求解的数可以符合第一条规则， 那么答案就是这两个数字下标的差。 同时， 如果 $a_i > a_{i - 1}$ ， 那么答案还可以是与前一个满足第一条规则的数字的下标的差， 取较小值。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std; 
const int N = 5e5 + 10;
int n, a[N], v[N], cnt, now = 1, ans; 
bool pd[N];
string s;
void init() {
	if(s[0] == '<') v[++cnt] = 0, a[0] = 0, pd[0] = 1;
	for(int i = 1; i < s.size(); i++) if(s[i] == '<' && s[i - 1] == '>') a[i] = 0, v[++cnt] = i, pd[i] = 1;
	if(s[s.size() - 1] == '>') v[++cnt] = s.size(), a[s.size()] = 0, pd[s.size()] = 1;
}
void calc() {
	for(int i = 0; i <= s.size(); i++) {
		if(pd[i]) {now++; continue;}
		if(s[i] == '<') if(i == 0) a[i] = 0; else a[i] = a[i - 1] + 1;
		else {
			if(a[i] == 0) continue;
			a[i] = v[now] - i;
			if(i == 0) continue;
			if(s[i - 1] == '>') {a[i] = min(a[i], a[i - 1] - 1); continue;}
			if(now != 1) a[i] = max(a[i], i - v[now - 1]);
		}
	}
}
int main() {
	memset(a, 1, sizeof a);
	cin >> s;
	init();
	calc();
	for(int i = 0; i <= s.size(); i++) {ans += a[i];/*cout << a[i] << " ";*/}
	cout << ans;
	return 0;
}
```


---

## 作者：BlackPanda (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/AT5659)**

------------
### 题意：
给定一个长度为 $n-1$ 的字符串 $s$，$s$ 中的元素仅包含 $\verb!>!$ 和  $\verb!<!$，请你构造一个长度为 $n$ 的非负整数序列，满足以下条件：

- 若 $s_i = \verb!>!$，则 $a_i > a_{i+1}$。

- 若 $s_i = \verb!<!$，则 $a_i < a_{i+1}$。

输出这个序列的最小权值。

------------
### 思路：
这道题是给定一个序列中相邻两个数的大小关系，让你构造这个序列，并输出最小权值。

我们可以用两种不同的遍历方法构造出两个序列，然后对于这两个序列的每个元素取最大值即可。

- 先从前往后遍历字符串，如果 $s_i = \verb!<!$，则 $a_i=a_{i-1}+1$。

- 再从后往前遍历字符串，如果 $s_i = \verb!>!$，则 $b_i=b_{i+1}+1$。

我们定义字符串 $s$ 的长度为 $len$，最后只需要求出 $\sum\limits_{i = 1}^{len}{\operatorname{max}(a_i,b_i)}$ 即可。

**注意：这道题最后用来求和的变量 $ans$ 一定要开成 long long！**

------------
### code：

```cpp

#include <bits/stdc++.h>
using namespace std;

string s;
long long a[500005],b[500005];

int main(){
	cin >> s; 
	int len=s.length();
	for(int i=1;i<=len;i++){
		if(s[i-1] == '<'){
			a[i]=a[i-1]+1;
		}
	}
	for(int i=len-1;i>=0;i--){
		if(s[i] == '>'){
			b[i]=b[i+1]+1;
		}
	}
	long long ans=0;
	for(int i=0;i<=len;i++){
		ans+=max(a[i],b[i]);
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：NOIAKME (赞：0)

**~~没人写栈吗~~**

具体思路：

首先定义字符串（>和<），定义计数器```cnt```，用```for```进行前后对应，用特判：
```cpp
    if(a[i]=='<') s[++top]=a[i];
		else if(a[i]=='>'){
			……
		}
```

识别是否有~~缺斤少两~~的，计数器```cnt```累加，最后输出```cnt```。
```cpp
#include<bits/stdc++.h> //万能头
using namespace std;
int main(){
	string a; 
	int s[100005],top=0，cnt=0; //top为栈点
	cin>>a;
	//重要开始
    for(int i=0;i<a.size();i++){
		if(a[i]=='<') s[++top]=a[i];//“s[++top]=a[i]很重要”！
		else if(a[i]=='>')//特判前后是否相应
			……
            cnt++;
		}
        ……
	}
    cout<<cnt;
	return 0;
}
```
~~别的不用多说了，代码自己补吧~~


---

## 作者：sgl654321 (赞：0)

### 题意描述
构造一个数列 $a$，使得所有的 $1\leq i\leq {N-1}$ 都满足以下条件：

- $a_i$ 为非负整数。
- 若 $S_i$ 为小于号，则 $a_i<a_{i+1}$；
- 若 $S_i$ 为大于号，则 $a_i>a_{i+1}$。

求数列 $a$ 的每一项之和。


### 解题思路
显然每一次加或减的数都要为 $1$。

如果出现大于号，就非常容易减出一个负数来。但是又要求了数列中的每一个数都是非负整数，所以可以想到，这题要顺着倒着都做一遍。

首先顺着做一遍。如果我们遇到了小于号，那么就让 $x_i=x_{i-1}+1$。

然后逆着做一遍。如果我们遇到了大于号，那么就让 $y_i=y_{i+1}+1$。

求出来的 $x$ 和 $y$ 序列都不一定是正确答案。正确答案应该是他们每一项的较大值。即对于所有的 $1\leq i \leq N$，有 $ans_i=\max(x_i,y_i)$。经检验，发现这是正确的。

举个例子，当 $S$ 为 ```>><><``` 时：

- 首先顺着做一遍。每一次遇到小于号，都要将其设定为前一个数加 $1$。序列 $x$ 就为 $[0,0,0,1,0,1]$。
- 然后逆着做一遍。每一次遇到大于号，都要将其设定为右边的数加 $1$。序列 $y$ 就为 $[2,1,0,1,0,0]$。
- 将所有的 $1\leq i \leq N$ 中的 $ans_i$ 设定为 $\max(x_i,y_i)$。 序列 $ans$ 就为 $[2,1,0,1,0,1]$。

所以，就应该输出 $5$。

### 代码
两个注意点：

- 注意字符串的长度与构造出的序列的长度相差 $1$。
- 要使用 long long。
```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
long long len,x[500010],y[500010],ans;
int main(){
		cin>>st;
		len=st.size();
		x[0]=0;//使用x表示顺序遍历。 
		y[len]=0;//使用y表示逆序遍历。 
		for(int i=1;i<=len;i++)
			if(st[i-1]=='<')x[i]=x[i-1]+1;
		for(int i=len-1;i>=0;i--)
			if(st[i]=='>')y[i]=y[i+1]+1;
		for(int i=0;i<=len;i++)
			ans+=max(x[i],y[i]);
		cout<<ans<<endl;
		return 0;
}
```
写在最后：管理大大求过。



---

## 作者：猜一猜我是谁 (赞：0)

# 思路
我们可以考虑建立两个数组 a 和 b，用两种方法构造方案，最后再取其中最大值即可。

- 所以先从前往后扫一遍字符串，如果 $s_i='<'$，那么构造方案 $a_{i+1}=a_{i}+1$。

- 再从后往前扫一遍字符串，如果 $s_i='>'$，那么构造方案 $b_{i}=b_{i+1}-1$。

接着求 $\sum\limits_{i=1}^l\max(a_i,b_i)$，其中 l 为字符串长度。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[500002],b[500002];
int main()
{
    string s;
    long long ans;
    cin>>s;
    s=" "+s;
    int l=s.length();
    for(int i=1;i<=l;i++)//第一种方案
        if(s[i]=='<') a[i+1]=a[i]+1;
    for(int i=l;i>=1;i--)//第二种方案
        if(s[i]=='>') b[i]=b[i+1]+1;
    for(int i=1;i<=l;i++)
        ans+=max(a[i],b[i]);
    cout<<ans;
}
```

---

## 作者：BF_AlphaShoot (赞：0)

**注**：本题解中的 $n$ 指 $a$ 的长度，但代码中的 $n$ 指字符串长度。

- 在 $s_i=$`<` 时保证和最小，则必然有 $a_{i+1}=a_i+1$。那么从前往后遍历一遍构造 a，若 $s_i=$`<`，则 $a_{i+1}=a_i+1$。
- 在 $s_i=$`>` 时保证和最小，则有 $a_i=\max(a_i,a_{i+1}+1)$（因为有可能正向构造时已经符合要求，所以要取 $\max$）。那么从后往前遍历一遍构造 $a$，若 $s_i=$`>`，则 $a_i=\max (a_i,a_{i+1}+1)$。
- 再求得 $\sum\limits_{i=1}^na_i$  即可。

反向构造（即先反后正）也是可以的，式子基本不变，这里不再赘述。

注意：

1. 所给字符串长度为 $n-1$，不要搞混长度。
2. $ans$ 需要开 long long。

先正后反：

```c++
#include<bits/stdc++.h>
using namespace std;
 
#define int long long
#define ri register int
 
const int INF=0x3f3f3f3f,N=5e5+10;
int n,ans;
int a[N]={0};
char s[N];

signed main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    for(ri i=1;i<=n;i++)
        if(s[i]=='<')
            a[i+1]=a[i]+1;
    for(ri i=n;i>=1;i--){
        if(s[i]=='>')
            a[i]=max(a[i],a[i+1]+1);
        ans+=a[i];
    }
    printf("%lld",ans+a[n+1]);
    return 0;
}
```

先反后正：

```c++
#include<bits/stdc++.h>
using namespace std;
 
#define int long long
#define ri register int
 
const int INF=0x3f3f3f3f,N=5e5+10;
int n,ans;
int a[N]={0};
char s[N];

signed main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    for(ri i=n;i>=1;i--)
        if(s[i]=='>')
            a[i]=a[i+1]+1;
    for(ri i=1;i<=n;i++)
        if(s[i]=='<')
            a[i+1]=max(a[i]+1,a[i+1]);
    for(ri i=1;i<=n+1;i++)
        ans+=a[i];
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：BotDand (赞：0)

# $\text{Problems}$
给定一个长度为 $N-1$ 的字符串 $S$，每个元素为 `>` 或 `<`。

我们称一个长度为 $N$ 的非负整数序列 $\{a_n\}$ 为好的，当且仅当对于任意的 $1\le i\le N-1$，都满足以下条件：

- 若 $S_i = $ `>` ，则 $a_i> a_{i+1}$

- 若 $S_i = $ `<` ，则 $a_i> a_{i+1}$

定义一个好的序列的权值为序列中所有元素的和，求所有好的序列中可能的最小权值。
# $\text{Answer}$
先说一下结论： $a_i=\max($ $S_i$ 左边**连续**的 `'<'` 的个数,$S_i$ 右边**连续**的 `'>'` 的个数$)$

~~不知道如何解释（han，搬运官方题解吧（雾。~~

前提：因为要 `>` 或 `<` ，所以构造出的数组的相邻数值差为 $1$ 的情况越多是越好的。

* 如果 $a_{i-x}<a_{i-x+1}<......<a_{i}$，则 $a_i$ 至少为 $x$。

* 如果 $a_{i}>a_{i+1}>......>a_{i+x}$，则 $a_i$ 至少为 $x$。

考虑到$2\le N\le 5\times 10^5$，于是用前缀和维护即可。
# $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
long long ans;
long long a[500002],b[500002];
int main()
{
    cin>>s;
    s=" "+s;
    for(int i=1;i<=s.length();++i) if(s[i]=='<') a[i]=a[i-1]+1;else a[i]=0;
    for(int i=s.length();i>=1;--i) if(s[i]=='>') b[i]=b[i+1]+1;else b[i]=0;
    for(int i=1;i<=s.length();++i) ans+=max(a[i-1],b[i]);
    cout<<ans;
    return 0;
}
```


---

