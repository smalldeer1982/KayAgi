# Reverse and Rotate

## 题目描述

给定一个字符串 $S$ 和 $n$ 次操作，每次操作为以下 $3$ 种形式之一：

1. `< x` 表示将 $S$ 向左循环移动 $x$ 位。例如：$\mathtt{abcde}$ 执行 `< 2` 后变成 $\mathtt{cdeab}$。

2. `> x` 表示将 $S$ 向右循环移动 $x$ 位。例如：$\mathtt{abcde}$ 执行 `> 2` 后变成 $\mathtt{deabc}$。

3. `rev` 表示将 $S$ 翻转。例如：$\mathtt{abcde}$ 执行 `rev` 后变成 $\mathtt{edcba}$。

求 $S$ 在**依次**执行这 $n$ 次操作后得到的字符串 $S'$。

注：对于 $S=s_0s_1\cdots s_{k-1}$，将其向左循环移动 $x$ 位，会变成 $s_{-x}S_{-x+1}\cdots S_{-x+k-1}$；向右循环移动 $x$ 位，会变成 $s_{x}S_{x+1}\cdots S_{x+k-1}$。对于 $x\equiv y\pmod k$，有 $s_x=s_y$。

## 说明/提示

**【样例 1 解释】**

- 原字符串为 $\mathtt{abcde}$；
- 第一次操作后，字符串变为 $\mathtt{deabc}$；
- 第二次操作后，字符串变为 $\mathtt{cbaed}$；
- 第三次操作后，字符串变为 $\mathtt{aedcb}$。

**【数据规模与约定】**

记 $|S|$ 表示字符串 $S$ 的长度。

| 测试点编号 | 特殊性质 |
| :----------: | :----------: |
| $1\sim3$ | $\vert S\vert,n,x \le 1000$ |
| $4$ | 没有 `rev` 操作 |
| $5$ | $S=\mathtt{aa...abb...b}$ |
| $6\sim10$ | 无 |

对于 $100\%$ 的数据，$1 \le |S|,n \le 10^6$，$0 \le x \le 10^9$，$S$ 仅由小写字母组成。

## 样例 #1

### 输入

```
abcde
3
> 2
rev
< 2```

### 输出

```
aedcb```

# 题解

## 作者：cff_0102 (赞：11)

如果直接模拟，因为这些字符串操作实际上都是 $O(n)$ 的，所以明显会超时。

因为只需要输出最后一次，再逐步在原字符串上模拟一下这一步结束后的字符串的样子，不难想到可以记录最后输出的字符串的第一位在哪里，还有输出的方向。

需要注意的是，反向之后的位移操作也需要反过来。

下面是赛时代码。刚开始用了 Py，因为这道题每一行末尾有恶心的 `\r`，导致 WA，调了很久，最后改成了 C++ 才通过。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string S;
    int n;
    cin >> S >> n;
    int pos=0;
    int d=1; // 1 -> -1 <-
    while (n) {
        n--;
        string op1;
        cin >> op1;
        if (op1 == "<") {int op2;cin>>op2;
            int x = op2 % S.length();
            pos += x*d;
            pos += S.length();
            pos %= S.length();
        } else if (op1 == ">") {int op2;cin>>op2;
            int x = op2 % S.length();
            pos -= x*d;
            pos += S.length();
            pos %= S.length();
        } else {
            d=0-d;
        }
        //cout << S << " " << pos << " " << d << endl;
    }
    //cout << S << " " << pos << " " << d << endl;
    if (d==1) {
        cout << S.substr(pos) << S.substr(0, pos) << endl;
    } else {
        string S1 = S.substr(0, pos);
        string S2 = S.substr(pos);//cout<<S1<<" "<<S2<<endl;
        reverse(S1.begin(), S1.end());
        reverse(S2.begin(), S2.end());
        cout << S1 << S2 << endl;
    }
    return 0;
}
```

---

## 作者：panxz2009 (赞：10)

## 题意简述 

- 给定一个字符串 $S$ 和 $n$ 次操作，每次操作为以下 $3$ 种形式之一：

1. `< x` 表示将 $S$ 向左循环移动 $x$ 位。

2. `> x` 表示将 $S$ 向右循环移动 $x$ 位。

3. `rev` 表示将 $S$ 翻转。

- 求 $S$ 在**依次**执行这 $n$ 次操作后得到的字符串 $S'$。

## 解题思路

假设只有前两种操作，如果每输入一次操作就执行一次，显然太过耗时；考虑记录下每一个操作的移动位数，输入结束后再统一操作即可。

但本题难点就在于处理第三种操作：`rev`。其实，手摸一下样例不难发现，一样也可以记录下字符串被反转的次数。对于被反转过奇数次的字符串，接下来的左移 $x$ 位操作就转化为右移 $x$ 位操作，同理，右移 $x$ 位操作就转化为左移 $x$ 位操作。若字符串被反转了偶数次，则左移、右移操作照常。

## 代码实现
赛时代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s,op;
int n,x,sum;
signed main(){
	cin>>s>>n;
	int f=1;
	int len=s.size();
	while(n--)
	{
		cin>>op;
		if(op=="<"){
			cin>>x;
			if(f==1) sum-=x;
			else sum+=x;
		} 
		if(op==">"){
			cin>>x;
			if(f==1) sum+=x;
			else sum-=x;
		}
		if(op=="rev"){
			f=1-f;
		}
	}
	sum%=len;
	if(sum<0) sum=abs(sum),rotate(s.begin(),s.begin()+sum,s.end());
	else rotate(s.rbegin(),s.rbegin()+sum,s.rend());
	if(f==0) reverse(s.begin(),s.end());
	cout<<s;
	return 0;
}
```


---

## 作者：very_easy (赞：9)

这种翻转的题明显已经做烂了好吧……

首先显而易见，翻转偶数次对结果没有影响，只需要考虑奇数次翻转的情况。

由于是整体移动的操作，可以抓住一个点来移动，然后还原出原来的序列。

例如先将选择的点设为 $x$，进行 `> 2` 的操作就将 $x+2$，`< 3` 的操作就将 $x-3$，但是减法会 $< 0$，由于是环形的，直接 $+\left| S \right|$就行，其中 $\left| S \right|$ 表示字符串 $S$ 的长度。

需要注意的是字符串是环形移动，因此如果当前点的位置大于字符串长度，要对字符串的长度进行取余操作。

写的时候注意细节。

## 代码
```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
	string a;
	cin>>a;
	int len=a.size();
	int n,f=0,x=1;
	cin>>n;
	while(n--){
		string op;
		cin>>op;
		if(op=="rev") f++,x=len-x+1;//累加rev的次数 
		if(op==">"){
			int s;
			cin>>s;
			s%=len;//取余 
			x+=s;
			x%=len;//取余 
		}
		if(op=="<"){
			int s;
			cin>>s;
			s%=len;//取余 
			x+=len,x-=s;
			x%=len;//取余 
		}
	}
	//还原字符串 
	if(f%2==1){
		string p1=a.substr(x,len-x+1);//使用substr 
		string p2=a.substr(0,x);
		reverse(p1.begin(),p1.end());//奇数次要翻转 
		reverse(p2.begin(),p2.end());
		a=p2+p1;
		cout<<a;
	}
	else{//偶数次没有翻转操作 
		string p1=a.substr(0,len-x+1);
		string p2=a.substr(len-x+1,x);
		a=p2+p1;
		cout<<a;
	}
	return 0;
}
```

---

## 作者：starNameHXH (赞：6)

[我的博客](https://www.luogu.com.cn/blog/754095/)

初次见面，我是明星兔！

# 前言

首先，我们来看一下这道题。

这道题……想必它怎么模拟都知道吧？但是！友情提醒，纯模拟只能拿 30 分！（[血的教训](https://www.luogu.com.cn/record/142811032)）

这里，我将会告诉各位我优化的看法。我和第一篇题解的思路基本一样，不过我个人认为我的更好理解。

# 常量/变量解释

以下是本题思路推导常量/变量的一些解释：

- $S$ 的意义题目有提到，就是题目给的字符串， $S'$ 则是求得的字符串。
- $start$ 的意义是当字符串输出时，第一个输出的字符串的下标，初始为 $0$。
- $rev$ 的意义是当字符串输出时，是否需要反向输出，初始为 $false$。
- $op$ 是题目给的操作指令。
- $len$ 是题目给的字符串的长度。

# 主体思路

## 你的下一次字符串操作，何必真的在字符串上操作？

大家知道，传统的字符串操作（尤其真的在字符串上翻转字符串）是一个极其耗时间的操作，且一般的题目还必须这样。

**但是**，这道题目只有三个操作：

1. `< x` 表示将 $S$ 向左循环移动 $x$ 位。例如：$\mathtt{abcde}$ 执行 `< 2` 后变成 $\mathtt{cdeab}$。

2. `> x` 表示将 $S$ 向右循环移动 $x$ 位。例如：$\mathtt{abcde}$ 执行 `> 2` 后变成 $\mathtt{deabc}$。

3. `rev` 表示将 $S$ 翻转。例如：$\mathtt{abcde}$ 执行 `rev` 后变成 $\mathtt{edcba}$。

欸？**没有一个操作**是真的将字符串的某部分改成别的东西，只有整体偏移，以及翻转！那么，让我们花点小心思……

![思路](https://oj.ipachong.com/upload/oj.ipachong.com/image/20240115/20240115210633_63267.png)

看懂了吗？我们只需要存储起点的下标以及输出方向就可以了！而且……我们甚至不用改变起点（与最早的题解的不同）！

### 主函数部分代码
```cpp
while(T--){
	string op;
	cin>>op;
	if(op=="rev"){
		rev=!rev;
	}else if(op=="<"){
		int t;
		cin>>t;
		if(!rev) goLeft(t);
		else goRight(t); // 如果是倒过来输出则按相反方向改起点
	}else{
		int t;
		cin>>t;
		if(rev) goLeft(t);
		else goRight(t);
	}
}
```

### 功能函数代码
```cpp
void goLeft(int dis){
	dis%=len; // 优化
	start=(start+dis)%len;
}
void goRight(int dis){
	dis%=len;
	start-=dis;
	if(start<0) start=len+start;
}
```

## 输出

可是，输出呢？输出怎么解决？这个很简单，直接给代码吧，应该能看懂的。

### 主函数部分代码

```cpp
if(!rev){
	for(int i=start;i<len;i++){
		cout<<s[i]<<endl;
	}
	for(int i=0;i<start;i++){
		cout<<s[i]<<endl;
	}
}else{
	for(int i=start-1;i>=0;i--){
		cout<<s[i]<<endl;
	}
	for(int i=len-1;i>=start;i--){
		cout<<s[i]<<endl;
	}
}
```

# 代码汇总

一百次空谈，不如一次实际的行动，现在，让我们有请总代码登场！

```cpp
//Author: RabbitStar(starNameHXH)
//Copyright (c) 2023 RabbitStar(starNameHXH)
//All rights reserved.

#include <bits/stdc++.h>
using namespace std;
int start=0,len;
bool rev=0;
void goLeft(int dis){
	dis%=len;
	start=(start+dis)%len;
}
void goRight(int dis){
	dis%=len;
	start-=dis;
	if(start<0) start=len+start;
}
int main(){
	string s;
	cin>>s;
	len=s.size();
	int T;
	cin>>T;
	while(T--){
		string op;
		cin>>op;
		if(op=="rev"){
			rev=!rev;
		}else if(op=="<"){
			int t;
			cin>>t;
			if(rev) goRight(t);
			else goLeft(t);
		}else{
			int t;
			cin>>t;
			if(rev) goLeft(t);
			else goRight(t);
		}
	}
	if(!rev){
		for(int i=start;i<len;i++){
			cout<<s[i]<<endl;
		}
		for(int i=0;i<start;i++){
			cout<<s[i]<<endl;
		}
	}else{
		for(int i=start-1;i>=0;i--){
			cout<<s[i]<<endl;
		}
		for(int i=len-1;i>=start;i--){
			cout<<s[i]<<endl;
		}
	}
	return 0;
}
```


---

## 作者：FurippuWRY (赞：6)

可以将 $S$ 抽象成一个环，可以发现：无论怎么左移右移反转，最终的字符串都可以从环上按照一定顺序读出。那么可以先对三种操作进行统计，把修改字符串放到最后，而非直接暴力。

定义变量 $cnt=0,p=0$，如果右移 $x$ 位，$cnt\leftarrow cnt + x$，如果左移 $x$ 位，$cnt\leftarrow cnt - x$，如果反转 $cnt\leftarrow -cnt,p\leftarrow p+1$。

若最终的 $p$ 为奇数，则翻转，然后判定 $cnt$ 的正负，若为正，向右移动 $(cnt \bmod |S|)$ 位（你要是不取模就 T 飞了），若为负，向左移动 $(-cnt\bmod |S|)$ 位。

至于为什么 $cnt$ 要取模，假设 $|S| = 114,cnt=228$，这时移动 $228$ 位，很明显，字符串没变，如果 $|S| = 114,cnt=229$，这时字符串只移动了 $1$ 位，即 $229\bmod 114=1$，也就是说，字符串的移动位数只和 $|cnt|\bmod |S|$ 有关。

可以用双端队列模拟，感觉会比纯数组方便的多。

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

deque<char> n;
int t, x, len, cnt = 0, p = 0;
string opt, s;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> s;
    len = s.size();
    for (int i = 0; i < len; ++i) n.push_back(s[i]);
    cin >> t;
    while (t--) {
        cin >> opt;
        if (opt[0] == '<') {
            cin >> x;
            cnt -= x;
        }
        else if (opt[0] == '>') {
            cin >> x;
            cnt += x;
        }
        else {
            p++;
            cnt = -cnt;
        }
    }
    if (p & 1) reverse(n.begin(), n.end());
    if (cnt > 0) {
        for (int i = 1; i <= cnt % len; ++i) {
            n.push_front(n.back());
            n.pop_back();
        }
    }
    else if (cnt < 0) {
        for (int i = 1; i <= -cnt % len; ++i) {
            n.push_back(n.front());
            n.pop_front();
        }
    }
    for (auto i : n) cout << i;
    return 0;
}
```

---

## 作者：Saint_ying_xtf (赞：5)

这道题，很容易看出来其实这个字符串反转几次其实无所谓，因为两两抵消，只需要看是不是奇数次反转即可。

然后会发现，其实不管怎样，这个字符串相对是原来的顺序。也就是说原来的 $s_1$ 到了答案最终的位置，一定是 $s_2$ 在他的左边或右边。通过自己手玩样例就可以知道了。

换句话说，关系到最后的情况只有一开始的 $s_1$ 在结束的什么地方，然后反转的奇偶性。

如何计算第一个字符的位置？每一次向右移动 $x$ 位就是 $+x$，左移就是 $-x$。注意如果大于 $n$ 还要减去 $n$。

这样，我们固定了第一个字符最后的位置，然后知道了是否要反转。

最后直接模拟即可。

最后，我感觉这一题在黄左右吧。

```cpp
//Author: gsczl71
//Copyright (c) 2023 gsczl71 All rights reserved.

#include<bits/stdc++.h>
#define ll long long
#define i128 __int128
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<long long, long long>
#define fir first
#define se second
#define endl '\n'
#define debug puts("AK IOI")
#define re register
#define pb push_back
using namespace std;
#define int long long
const int mod = 1e9 + 7;
//const int mod = 998244353;
const int inf = 0x3f3f3f3f, N = 1e6 + 5, M = 2e5 + 5;
const ll linf = 0x3f3f3f3f3f3f3f3f;
string s;
int n;
int x = 1;
int flag=0;
char ans[N];
void solve() {
	cin >> s >> n;
	while (n--) {
		string op;
		cin >> op;
		int t = 0;
		if (op == ">") {
			int t;
			cin >> t;t%=s.size();
			x += t;
			if (x > s.size()) x -= s.size();
		} else if (op == "<") {
			int t;
			cin >> t;t%=s.size();//进行取模，因为会有转了很多圈回来了。
			x += s.size(), x -= t;
			if (x > s.size())x -= s.size();
		} else {
			x = s.size()-x+1;
			flag=!flag;
		}
	}
	if(!flag){
		int it=0;
		for(int i = x;i <= s.size();i++){
			ans[i] = s[it];it++;
		}for(int i = 1;i <= x-1;i++){
			ans[i] = s[it];it++;
		}
	}else{
		int it=0;
		for(int i = x;i >= 1;i--){
			ans[i] = s[it];it++;
		}for(int i = s.size();i >= x+1;i--){
			ans[i] = s[it];it++;
		}
	}
	
	for(int i = 1;i <= s.size();i++){
		cout<<ans[i];
	}
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1;
//	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：Shadows_of_Twilight (赞：4)

怎么前三题都是思维题啊。
## 思路
总共有三个操作，先不看翻转操作。

如果你右移 $x$ 位之后，左移 $x$ 位，那么就**相当于没有操作**。这个应该是很好理解的。

我们根据上面的结论，能得出以下代码。
```cpp
    if(op==">"){
        cin>>x;
        f+=x;
    }
    else if(op=="<"){
        cin>>x;
        f-=x;
    }
```

变量 $f$ 是最终应该右移多少位，$op$ 是操作，$x$ 是位数。

统计出最终右移多少位，最后进行操作。

接着看翻转。

首先，翻转两次是可以**抵消**的。

思考，翻转前需要右移 $x$ 位，那么翻转后需要右移多少位呢？

不妨举个例子。

如果字符串 `abcde` 需要右移 1 位。按正常顺序，先右移，变成 `eabcd`，再翻转，变成 `dcbae`。如果先翻转，变成 `edcba`，发现只需要在左移 1 位，即右移 -1 位，就正好可以变为 `dcbae`。

因此我们的**规律**是，翻转前需右移 $x$ 位，翻转后需右移 $-x$ 位。

仔细在脑子里想一想，画一画，发现这个规律很显然成立，主要是需要想到这一步。

然后这个问题就可以**解决**了。

如果是左移或右移，就按前面的操作办。如果是翻转，就看记录次数，并且变量 $f$ 应该乘上 -1，最后如果总共翻转奇数次，则需要给字符串翻转，然后右移即可。

还有一下几点需要注意：

- 如果一个字符串右移自己的长度位，就**相当于没有操作**，所以最终需要将 $f$ 对字符串长度取模。

- 最后取模的话，一定要开 `long long`。

## AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    int T,f=0,x,n,fg=0;
    string s;
    cin>>s;
    n=s.size();
    cin>>T;
    while(T--){
        string op;
        cin>>op;
        if(op==">"){
            cin>>x;
            f+=x;
        }
        else if(op=="<"){
            cin>>x;
            f-=x;
        }
        else{
            f=-1*f;
            fg=(fg==0?1:0);
        }
    }
    f=f%n;
    if(fg)reverse(s.begin(),s.end());
    if(f==0)return cout<<s,0;//这里应该不要这么麻烦
    if(f>0){
        cout<<s.substr(n-f)<<s.substr(0,n-f);
    }
    else{
        f=abs(f);
        cout<<s.substr(f)<<s.substr(0,f);
    }
	return 0;
}
```

---

## 作者：xiayz2010 (赞：2)

把 $S$ 首尾连接成一个环更好理解，发现题目中这三种操作都不会改变 $S$ 中每个字符之间的相对顺序，即原先任意一个字符两侧的字符在进行完所有操作之后仍在这个字符的两侧。

如果没有 `rev` 操作，可以记录共旋转了多少位，并在操作输入完了之后统一进行操作。

发现如果有 `rev` 操作，当 $S$ 翻转后时再进行向左循环移动 $x$ 位的操作，与进行向右循环移动 $x$ 位再将 $S$ 翻转效果是一样的（向右转同理）。

所以可以将所有翻转操作最后进行，前面只需要像没有 `rev` 操作一样记录旋转位数最后统一进行操作就可以了。
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

string s;
int n, m; // n 为操作数，m 为 S 的长度
int rev = 0, turn = 0; // rev为当前相对于最初是否翻转，turn为当前左旋了多少位

int main(){
    cin >> s >> n;
    m = s.size();
    while(n--){
        string op;
        cin >> op;
        if(op == "<"){
            int x;
            cin >> x;
            if(rev == 0) turn = ((turn + x) % m + m) % m;
            else turn = ((turn - x) % m + m) % m;
            // 取模是因为左旋 m 下相当于不动
        }
        if(op == ">"){
            int x;
            cin >> x;
            if(rev == 0) turn = ((turn - x) % m + m) % m;
            else turn = ((turn + x) % m + m) % m;
        }
        if(op == "rev") rev = 1 - rev;
    }
    if(rev == 0){
        string ans;
        for(int i = turn; i < m; i++) ans += s[i];
        for(int i = 0; i < turn; i++) ans += s[i];
        cout << ans;
    }else{
        string ans;
        for(int i = turn; i < m; i++) ans += s[i];
        for(int i = 0; i < turn; i++) ans += s[i];
        reverse(ans.begin(), ans.end());
        cout << ans;
    }
    return 0;
}
```

---

## 作者：oceanfish (赞：2)

## 题目
[题目传送门](https://www.luogu.com.cn/problem/P10058)

主要围绕有关字符串的操作。

字符串可左移，右移，以及翻转。

问最终字符串。

## 思路

模拟肯定不行，会超时。

这启发我们使用一些特殊的方法，我们为什么不最后再处理字符串呢？

我们假设左移就加，右移就减，那么我们就可以将操作归结起来，最后一次性处理。

翻转怎么办呢？翻转后，原来的左右移操作会颠倒，我们只要多加判断即可。

最后，由于左右移许多次后，字符串会和原来一样，所以我们要注意处理该问题，在每一次累加后模字符串长度即可。

最后处理，并输出。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
string s, t1;
int n, sum, t2, l;
bool rev = 0;

signed main() {
	cin >> s;
	l = s.size();
	cin >> n;
	while (n--) {
		cin >> t1;
		if (t1 == "<") {
			cin >> t2;
			if (rev == 0)
				sum = (sum + t2) % l;
			else
				sum = (sum - t2) % l;
		}
		if (t1 == ">") {
			cin >> t2;
			if (rev == 0)
				sum = (sum - t2) % l;
			else
				sum = (sum + t2) % l;
		}
		if (t1 == "rev")
			rev = !rev;
	}
	if (sum < 0)
		sum += l;
	string s1 = s.substr(sum);
	string s2 = s.substr(0, sum);
	s = s1 + s2;
	if (rev)
		reverse(s.begin(), s.end());
	cout << s;
	return 0;
}
```


---

## 作者：Hexiuqi (赞：2)

## 思路

显然暴力是不可取的，时间复杂度 $O(n^2)$。（而且搞不好就会 RE）

观察这三个操作，发现操作是可以叠加的，具体来说，所有操作执行完之后的结果都是可以用一次翻转加一次左循环来达成的。

那该怎么将这一堆操作转化为两个操作呢？

定义两个变量 $rev,bac$，分别表示最后我们要不要翻转和我们要左循环多少位。左循环可以直接叠加，右循环可以当成左循环的相反数，翻转可以将翻转标记取反，再将左循环变成右循环就可以了。

## 代码

赛时代码，写的比较丑陋。

```cpp

#include <bits/stdc++.h>
using namespace std;
int n,m,rev,bac;
string s;
int main(){
    cin>>s>>m;
    n=s.length();
    while(m--){
        string op; int x;
        cin>>op;
        if(op=="rev") rev^=1,bac=n-bac; //翻转操作
        else cin>>x;
        if(op=="<") bac=(bac+x)%n; //左循环
        else if(op==">") bac=bac-x; //右循环
        if(bac<0) bac=n-(-bac)%n; //防止bac为负
    }
    if(rev) for(int i=0;i<n/2;i++) swap(s[i],s[n-i-1]); //最后翻转
    for(int i=0;i<bac;i++) s[i+n]=s[i]; //最后循环
    for(int i=bac;i<bac+n;i++) cout<<s[i]; //注意输出方式（不然会RE的很惨！）
    return 0;
}

``````

---

## 作者：_anll_ (赞：2)

## 题目大意
给你一个字符串 $s$ 和 $n$ 次操作，每次操作为以下 $3$ 种形式之一：

1. `< x` 表示将 $s$ 向左循环移动 $x$ 位。
2. `> x` 表示将 $s$ 向右循环移动 $x$ 位。
3. `rev` 表示将 $s$ 翻转。

求 $s$ 在**依次**执行这 $n$ 次操作后得到的字符串 $s'$。
## 大体思路
考场上看到这道题的第一反应是使用双端队列维护。理由是该字符串的前后都需要维护。于是很快可以有思路：

1. 对于操作 `<`，从队首取出字符丢到队尾。
1. 对于操作 `>`，从队尾取出字符丢到队首。
1. 对于操作 `rev`，把整个队列颠倒过来。

于是提交上去，美美 TLE 了。

所以考虑优化。于是很轻松地得到了三个优化：
1. 对于字符串，你把它左循环移动 $a$ 次，再把它右循环移动 $a$ 次后得到的字符串和原先的字符串是一样的。

1. 如果要对于颠倒过来的序列进行操作，相当于把操作颠倒过来，最后输出的时候再判断一下方向就好。

1. 对于一个长度为 $m$ 的字符串，如果你左移或右移它 $m$ 次，它就会回到原点。所以我们操作时只需要把操作次数对 $m$ 取模即可。

知道怎么优化后，代码的实现也十分显然易见了：我们令右循环为正操作，左循环为负操作。先考虑翻转，我们拿一个变量判断是否反转，如果反转则对应的操作都需要反转。处理完这一点后，再拿变量 $need$ 储存正操作的次数。每次右循环就把 $need$ 加上 $x$，反之在每次左循环时把 $need$ 减去 $x$。操作完毕后把通过正负数对双端队列进行上文提到的操作。最后输出时判断需要正向还是逆向输出即可。

## 代码展示
上文有讲的不清楚的地方，还请结合代码理解。
```cpp
#include<iostream>
#include<deque>
#define int long long
using namespace std;
deque<char> dq;
int n,what;
string s;
string check(string ss){
    if(what==1){
        if(ss==">") ss="<";
        else if(ss=="<") ss=">";
    }
    return ss;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>s;
    for(int i=0;i<s.size();i++) dq.push_back(s[i]);
    cin>>n;
    string op;int a,need=0;
    for(int i=1;i<=n;i++){
        cin>>op;
        op=check(op);
        if(op==">"){
            cin>>a;
            need+=a;
        }
        else if(op=="<"){
            cin>>a;
            need-=a;
        }
        else what^=1;
    }
    if(need>0){
        need%=s.size();
        for(int i=1;i<=need;i++){
            char awa=dq.back();dq.pop_back();
            dq.push_front(awa);
        }
    }
    else{
        need=-need;
        need%=s.size();
        for(int i=1;i<=need;i++){
            char awa=dq.front();dq.pop_front();
            dq.push_back(awa);
        }
    }
    if(!what)
    while(!dq.empty()){
        cout<<dq.front();dq.pop_front();
    }
    else
    while(!dq.empty()){
        cout<<dq.back();dq.pop_back();
    }
    return 0;
}
```


---

## 作者：yzm0325 (赞：1)

真有黄吗。

以下记 $l=|s|$。

首先考虑前两个操作。因为字符串本身没变，所以我们可以维护一个字符串的起始位置 $beg$（初始为 $0$，这里字符串下标是 $1 \sim l-1$），每次操作只需要对变量进行加减即可。简单模拟一下，可以发现左循环移动 $x$ 位相当于 $beg$ 加上 $x$ 再对字符串长度取模，右循环移动相反。注意 C++ 对负数取模会得到负数或 $0$，这时直接取模的话，后面可能会访问负下标导致 RE，所以 $beg$ 为负数时只能不断增加 $l$ 直到 $beg \geq 0$。这里我偷了个懒，因为 $l$ 和 $x$ 之间最多相差 $l$ 的 $10^9$ 倍，所以直接让 $beg < 0$ 时加上 $l \times 10^9$，此时 $beg$ 一定为正整数（因为 $beg$ 最小为 $-x$），对 $l$ 取模即可。

在输出时，先输出 $s_{beg}s_{beg+1}\cdots s_l$ 这一段，再输出 $s_1s_2\cdots s_{beg-1}$ 这一段，注意 $beg$ 的位置不要重复输出。

之后考虑翻转操作。用一个布尔型变量 $isre$ 记录字符串是否被翻转，每次遇到翻转操作直接让 `isre = !isre`，在输出时如果 $isre$ 是真则反着输出，即输出字符串 $s_{beg-1}s_{beg-2}\cdots s_1s_ls_{l-1}\cdots s_{beg}$。注意此时前两个操作也要反过来。

更多细节请见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int n;
int main() {
    cin >> s >> n;
    long long beg = 0; // 注意 long long！下面的 + 1ll * s.size() * 100000000 会爆 int
    bool isre = 0;
    while(n--) {
        string r;
        int a; // 即题目中的 x
        cin >> r; // 直接以字符串形式输入可以避免读到 rev 时需要额外把字符串读完
        if(r == "<") {
            cin >> a;
            if(isre) beg = (beg - a + 1ll * s.size() * 100000000) % s.size(); // 这里要在前面乘一个 1ll，不然也会爆 int
            else beg = (beg + a) % s.size(); // 无论哪个操作都要取模，防止数组越界
        } else if(r == ">") {
            cin >> a;
            if(!isre) beg = (beg - a + 1ll * s.size() * 100000000) % s.size();
            else beg = (beg + a) % s.size();
        } else {
            isre = !isre;
        }
//        if(isre) {
//        	for(int i = beg - 1; i >= 0; i--) cout << s[i];
//        	for(int i = s.size() - 1; i >= beg; i--) cout << s[i];
//    	} else {
//        	for(int i = beg; i < s.size(); i++) cout << s[i];
//        	for(int i = 0; i < beg; i++) cout << s[i];
//    	}
//    	puts(""); 这一块是调试所加
    }
    if(isre) {
        for(int i = beg - 1; i >= 0; i--) cout << s[i];
        for(int i = s.size() - 1; i >= beg; i--) cout << s[i];
    } else {
        for(int i = beg; i < s.size(); i++) cout << s[i];
        for(int i = 0; i < beg; i++) cout << s[i];
    }
    return 0; // 完结撒花！！
}
```

---

## 作者：jomy (赞：1)

### 前言
~~咕咕咕，怎么又是题解区第二篇题解。~~
# 回归正题
~~我是一眼瞪出来的。~~

### 30pts

第一种方法：

模拟每一次操作，暴力出奇（~~寄~~）迹，代码略。

第二种方法：

食用满分代码时没有开【数据删除】导致在极限数据为 $10^6 \times 10^9 =10^{15} >2^{31}-1$ 时见祖宗。

### 100pts

先说明一个条件，后面会用到。

即：
```
if(c==">"){
    cin>>a;
    right+=a*re;//right：右移，re：是否反转（true -1，false 1）
}
else if(c=="<"){
    cin>>a;
    right-=a*re;
}
else{
    re*=-1;
}
```
怎么说明其正确性呢，我可能说的不好，见谅，请自行理解。

~~说人话~~就是我俩面对面，我的左边就是你的右边，我的右边就是你的左边。这个理解到了就行。

所以只需在反转时左右移调转，最后反转答案（只是反转奇数次时），即答案。

关键代码如下：
```
while(m--){
    string c;
    long long a;
    cin>>c;
    if(c==">"){
        cin>>a;
        right+=a*re;
    }
    else if(c=="<"){
        cin>>a;
        right-=a*re;
    }
    else{
        re*=-1;
    }
}
right%=n;
for(int i=0;i<n;i++){
    c[i]=s[(i+n-right)%n];//一腚加n再-right。
}
if(re<0){
    for(int i=0;i<n;i++){
        cout<<c[n-i-1];
    }
}
else{
    for(int i=0;i<n;i++){
        cout<<c[i];
    }
}
```
**完结撒花**

---

## 作者：羊羊君的幻想 (赞：1)

小清新题。


------------

### 题意

对一个字符串维护循环操作、翻转操作。



------------
### 题解

看似这几项操作很复杂，实际并不复杂。

我们先定义字符串长度 $|s|=len$。

这些操作放到字符串上不好处理，可以转化一下，先不考虑翻转操作，我们维护两个指针 $L$ 和 $R$，分别表示答案字符串的起始位置和终止位置。

加上翻转操作也不难，我们再去维护一个状态 $g$，代表 $L$ 到 $R$ 的方向，这样就可以完美进行三项操作了。

#### 操作 1 & 2

操作 $1$ 和操作 $2$ 是类似的，我们可以一起说。

首先 $x$ 完全可以简化，$x \bmod len$ 和 $x$ 的操作效果是一样的。

所以操作之前我们先把 $x$ 对 $len$ 取模。

思考怎么维护指针。

我们拿操作 $2$ 举例，假设这是指针的初始状态：

![](https://cdn.luogu.com.cn/upload/image_hosting/uv6ipm5k.png)

我们进行操作 $2$,向右循环的本质其实是平移 $L$ 和 $R$ 指针 $x$ 个单位长度，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/p2se99xi.png)

发现 $R$ 越界了，怎么办？让它的位置减去 $len$，就回来了。

![](https://cdn.luogu.com.cn/upload/image_hosting/tmsy1o30.png)

操作 $1$ 和方向相反的情况请自行思考，原理是一样的。

#### 操作 3 

这个更好维护了，直接改变一下方向状态 $g$ 即可。

------------

### 代码

```cpp

#include<bits/stdc++.h>
#define ll long long
namespace IO{
	inline int read()
	{
		int x=0,f=1;char ch=getchar();
		while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
		while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
		return x*f;
	}
}
using namespace IO;
using namespace std;
string s;
int x,l,r,len;
void w1(){
	l+=x;r+=x;
	if(l>len) l-=len;
	if(r>len) r-=len;
}
void w2(){
	l-=x;
	r-=x;
	if(l<1) l+=len;
	if(r<1) r+=len;
}
signed main(){
	cin>>s;
	len=s.size();
	l=1,r=len;
	int g=1;
	int n=read();
	for(int i=1;i<=n;i++){
		string op;
		cin>>op;
		if(op==">"){
			x=read();
			x%=len;
 			if(g==1){
 				w2();
			 }else w1();
		}else if(op=="<"){
			x=read();
			x%=len;
			if(g==1){
				w1();
			}else w2();
		}else{
			g=3-g;
		}
	}
	
	if(g==1){
		int i=l;
		while(i!=r){
			cout<<s[i-1];
			++i;
			if(i>len) i=1;
		}
		cout<<s[i-1];
	}else{
		int i=r;
		while(i!=l){
			cout<<s[i-1];
			--i;
			if(i<1) i=len;
		}
		cout<<s[i-1];
	}
return 0;
}
```

---

## 作者：Crazyouth (赞：1)

## 分析

2024 第一场 AK 的比赛，祭。

不难发现一点，不管如何操作，最终得到的串一定可以表示为原串翻转或不翻转后向右移动若干位。考虑维护是否翻转，与最后移动多少位。

是否翻转直接用 `rev` 的数量统计。移动的位数也好分析，我们提出以下几个结论：

- 向右移动 $m$ 位相当于向右移动 $m \bmod |S|$ 位。
- 向左移动 $m$ 位（$0\le m\le |S|$）相当于向右移动 $m-|S|$ 位。
- 翻转后向右移动 $m$ 位相当于向左移动 $m$ 位再翻转。

前两个非常好证，至于最后一个，我们考虑把 $S$ 扩展为一个无限长的串，以 `abcde` 为例，那么把它看成串 `...abcdeabcdeabcde...` 中间的 $5$ 个字母，如果你翻转后再向右移动 $m$ 位，其实你从背面（感性理解一下）看就是向左移动了 $m$ 位，从背面看本质上是翻转操作，因此结论 $3$ 是成立的。

那么这就非常好办了，引入变量 $p$ 表示向右移动多少位，遇到 `rev` 就 $p\leftarrow |S|-p$，否则按照结论 $1,2$ 的来做。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	int n,flag=0,p=0;
	cin>>s>>n;
	while(n--)
	{
		string opt;
		cin>>opt;
		if(opt=="rev") flag^=1,p=s.size()-p;
		else if(opt=="<")
		{
			int m;
			cin>>m;
			m%=s.size();
			p+=s.size()-m;
			p%=s.size();
		}
		else
		{
			int m;
			cin>>m;
			m%=s.size();
			p+=m;
			p%=s.size();
		}
	}
	if(flag) for(int i=0;i<s.size()/2;i++) swap(s[i],s[s.size()-1-i]);
	if(!p) cout<<s;
	else
	cout<<s.substr(s.size()-p,p)+s.substr(0,s.size()-p);
	return 0;
} 

---

## 作者：cosf (赞：1)

我们记录两个量，$rev, dif$，表示翻转因子（$1$ 为未翻转，$-1$ 为翻转）和偏移位数。

若当前是翻转操作，则 $rev \gets -rev$。

若当前操作为 `<`，则 $dif \gets dif + rev \times x$。

若当前操作为 `>`，则 $dif \gets dif - rev \times x$。

最后再根据 $rev$ 的值来判断应该顺序输出还是逆序输出即可。

```cpp
#include <iostream>
using namespace std;

int main()
{
	string s;
	int n;
	cin >> s >> n;
	int dif = 0;
	int rev = 1;
	int m = s.length();
	while (n--)
	{
		string op;
		cin >> op;
		if (op == "rev")
		{
			dif = (dif + m) % m;
			rev = -rev;
		}
		else
		{
			int x;
			cin >> x;
			if (op == "<")
			{
				dif += x * rev;
			}
			else
			{
				dif -= x * rev;
			}
			dif = (dif % m + m) % m;
		}
	}
	if (rev == 1)
	{
		for (int i = 0; i < m; i++)
		{
			cout << s[(i + dif) % m];
		}
		cout << endl;
	}
	else
	{
		for (int i = m - 1; ~i; i--)
		{
			cout << s[(i + dif) % m];
		}
		cout << endl;
	}
	return 0;
}

```


---

## 作者：zhlzt (赞：0)

### 题解

这道题算简单的，我们只需要推出一个性质就好了。

在翻转后，原来是向左移动几位，现在就是向右移动几位，反之同理。

在代码中，$tag$ 记录是否要翻转，$cnt$ 表示向右移动几位，如果为负，就表示向左移 $|cnt|$ 位。并且，$cnt$ 是可以对 $n$ 取模的，具体原理可以自己分析，不难。 

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
char str[maxn],srt[maxn];
int main(){
	int m;scanf("%s%d",str,&m);
	int cnt=0,tag=0,n=strlen(str);
	while(m--){
		char opt[10];int d;scanf("%s",opt);
		if(opt[0]=='r') tag^=1,cnt=-cnt;
		else if(opt[0]=='>') scanf("%d",&d),cnt=(cnt+d)%n;
		else if(opt[0]=='<') scanf("%d",&d),cnt=(cnt-d)%n;
	} cnt=(cnt%n+n)%n;
	for(int i=0,j=n-1;i<n;i++,j--) 
	if(tag) srt[i]=str[j]; else srt[i]=str[i];
	for(int i=n-cnt;i<n;i++) printf("%c",srt[i]);
	for(int i=0;i<n-cnt;i++) printf("%c",srt[i]);
	return 0;
}
```

---

## 作者：_little_Cabbage_ (赞：0)

# P10058 Reverse and Rotate 题解
~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-p10058)~~

这是一道字符串的思维题。

我们设字符串长度为 $len$。

我们可以发现，如果有奇数次翻转，才翻转。

然后对于左移和右移，移的位数为 $a\bmod len$，不然 $10^9$ 没法做。

然后用两个变量 $x$ 和 $y$，一个加左移的位数，一个加右移的位数，最后两个变量都要 $\bmod len$，然后在进行左移和右移就行了。

这里要注意，一定要先翻转，不然会有问题。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	cin>>s;
	int len=s.size();
	int n;
	scanf("%d",&n);
	int cnt=0;
	int ans1=0;
	int ans2=0;
	int ans3=0;
	while(n--)
	{
		string op;
		cin>>op;
		if(op=="rev")
		{
			cnt++;
			ans3=ans1;
			ans1=ans2;
			ans2=ans3;
		}
		else
		{
			int x;
			cin>>x;
			x%=len;
			if(op=="<")
			{
				ans1+=x;
			}
			else
			{
				ans2+=x;
			}
		}
	}
	
	if(cnt%2==1)
	{
		reverse(s.begin(),s.end());
	}
	string t=s;
	ans1%=len;
	for(int i=0;i<len;i++)
	{
		t[(i-ans1+len)%len]=s[i];
	}
	ans2%=len;
	string l=t;
	for(int i=0;i<len;i++)
	{
		l[(i+ans2+len)%len]=t[i];
	}
	
	cout<<l;
}
```
[AC 记录](https://www.luogu.com.cn/record/142868519)

---

## 作者：fish_love_cat (赞：0)

为啥总觉得这题似曾相识~~难道是原~~？

---

观察题面后，可以发现：

**直接模拟题意会炸。**

反转后，左移变右移，右移变左移。

反转后再反转等于没变。

左右移相互抵消。

移 $|S|$ 次等于没移。

移动的先后与结果答案无关。

---

那么，我们就可以：

直接统计左移右移数量，没用的删去，最后再计算答案。还要实时记录反转状态，方便左右移转化。

注意最后要反转的话记得反转。

~~有人因此错一发，我不说是谁。~~

---

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool zt=false;
int lef,righ;
signed main(){
    string s;
    cin>>s;
    int t;
    cin>>t;
    int mod=s.size();
    while(t--){
        string op;
        cin>>op;
        if(op=="rev")zt=!zt;
        else{int x;cin>>x;
            if(op==">"&&zt||!zt&&op=="<")lef=(lef+x)%mod;
            else righ=(righ+x)%mod;
        }
    }
    int sum=max(righ,lef)-min(righ,lef);
    string ans="";
    if(righ>lef){
        for(int i=mod-sum+1;i<=mod;i++)ans+=s[i-1];
        for(int i=1;i<=mod-sum;i++)ans+=s[i-1];
    }else{
        for(int i=sum+1;i<=mod;i++)ans+=s[i-1];
        for(int i=1;i<=sum;i++)ans+=s[i-1];
    }
    if(zt)reverse(ans.begin(),ans.end());
    cout<<ans;
    return 0;
}//我恨人类
```

---

## 作者：封禁用户 (赞：0)

首先观察数据范围，$1\le|S|,n\le10^6$，直接暴力的复杂度是 $\mathcal O(n\cdot|S|)$，显然无法通过。

考虑存储左移位数和是否要翻转。
#### 左移操作
若当前已需要左移 $k$ 位，要左移 $x$ 位，共左移 $(k+x)$ 位。
#### 右移操作
若当前已需要左移 $k$ 位，要右移 $x$ 位，共左移 $(k-x)$ 位。
#### 翻转操作
显然，每一次翻转会使左移变为右移，左移位数变为右移位数，若当前已需要左移 $k$ 位，是否翻转的标记变量改变，转换为左移即左移 $|S|-k$ 位。
- - -
#### 关于负数的取模
C++ 一个负数取模正数有点问题，若是 $a$ 取模 $b$，应该使用 `(a%b+b)%b`。
- - -
直接上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,ss;int n,x,l,rev;
int main(){
    cin>>s>>n;
    int len=s.size();
    while(n--){
        cin>>ss;
        if(ss=="<")cin>>x,x%=len,l=(l+x)%len;//左移
        if(ss==">")cin>>x,x%=len,l=(l-x+len)%len;//右移
        if(ss=="rev")rev^=1,l=len-l;//翻转
    }if(rev)reverse(s.begin(), s.end());//进行最后的翻转
    for(int i=l;i<len;i++)putchar(s[i]);//左移
    for(int i=0;i<l;i++)putchar(s[i]);//左移
    return 0;
}
```

---

## 作者：jqQt0220 (赞：0)

~~电脑被我妈收了，我硬生生用手机切了这道题写了这篇题解，厉不厉害~~

看到题第一眼想到双端队列暴力模拟，向左就是头出入到尾，向右就是尾出入到头，rev 操作就全从头出再全从头入。但是 $x\le10^{9}$，显然会寄。因为是循环，所以实际上只有 $x\bmod|S|$ 次。这样可以减轻许多 TLE 的危机，但还是会 T 飞，实测 30pts，时间复杂度 $O(n^{2})$。删去了缺省源的代码如下：
```cpp
deque<char> q;
int main()
{
    ___();
    string s;
    cin>>s;
    for(char p:s)
        q.push_back(p);
    int l=q.size();
    int _;
    cin>>_;
    while(_--)
    {
        string op;
        cin>>op;
        if(op=="<")
        {
            int x;
            cin>>x;
            x%=l;
            while(x--)
                q.push_back(q.front()),q.pop_front();
        }
        if(op==">")
        {
            int x;
            cin>>x;
            x%=l;
            while(x--)
                q.push_front(q.back()),q.pop_back();
        }
        if(op=="rev")
        {
            string t;
            while(!q.empty())
            {
                t+=q.front();
                q.pop_front();
            }
            for(char p:t)
                q.push_front(p);
        }
    }
    while(!q.empty())
    {
        cout<<q.front();
        q.pop_front();
    }
    return 0;
}
```

考虑优化。可以把每次 rev 操作前的左右移相加，每次 rev 时再统一位移然后反转。不过优化完后并没有快多少，只多过了一个没有 rev 操作的点，拿到了 40pts，复杂度也没差多少。代码如下：
```cpp
deque<char> q;
int main()
{
    ___();
    string s;
    cin>>s;
    for(char p:s)
        q.push_back(p);
    int l=q.size();
    int _;
    cin>>_;
    int k=0;
    while(_--)
    {
        string op;
        cin>>op;
        if(op=="<")
        {
            int x;
            cin>>x;
            k=((k+x)%l+l)%l;//全转成正数次左移
        }
        if(op==">")
        {
            int x;
            cin>>x;
            k=((k-x)%l+l)%l;
        }
        if(op=="rev")
        {
            while(k--)//一次移完
                q.push_back(q.front()),q.pop_front();
            k=0;//移完后 k 会等于 -1，要变回 0
            string t;
            while(!q.empty())
            {
                t+=q.front();
                q.pop_front();
            }
            for(char p:t)
                q.push_front(p);
        }
    }
    while(k--)//最后还要再移一次
        q.push_back(q.front()),q.pop_front();
    while(!q.empty())
    {
        cout<<q.front();
        q.pop_front();
    }
    return 0;
}
```

继续优化。很明显，rev 后位移操作对于原串相对位置的方向会反，而两次 rev 会回到原串。这样就可以直接累加位移量，最后一次移完，再反转。这样一次累加时间复杂度 $O(1)$，最后位移和反转时间复杂度 $O(n+|S|)$，整体时间复杂度 $O(n+|S|)$。AC 代码：
```cpp
deque<char> q;
int main()
{
    ___();
    string s;
    cin>>s;
    for(char p:s)
        q.push_back(p);
    int l=q.size();
    int _;
    cin>>_;
    int k=0,f=1;//k 是位移量，f 是判反转，正为未反转，负为反转
    while(_--)
    {
        string op;
        cin>>op;
        if(op=="<")
        {
            int x;
            cin>>x;
            k=((k+x*f)%l+l)%l;
        }
        if(op==">")
        {
            int x;
            cin>>x;
            k=((k-x*f)%l+l)%l;
        }
        if(op=="rev")
            f=-f;
    }
    while(k--）  
        q.push_back(q.front()),q.pop_front();
    s.clear();//直接利用前面输入的 s
    while(!q.empty())//存进字符串
    {
        s+=q.front();
        q.pop_front();
    }
    if(f<0)//标记了就反转
        reverse(s.begin(),s.end());
    cout<<s;
    return 0;//完美结束 QwQ
}
```

---

## 作者：Lovely_Elaina (赞：0)

一道非常若至的题，随便模拟一下就能得到结论。

我们用一个变量表示是否翻转，翻转偶数次则没有翻转。

定义一个变量为移几位。

若右移 $x$ 位，则等同于右移 $x\bmod|S|$ 位，等同于左移 $|S|-(x\bmod|S|)$ 位。

被翻转时的移动方向可以视为未翻转的相反移动方向。

解决了。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

int n,in;
string s;
string op;

bool rev;
int cnt;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(NULL); 
    
    cin >> s >> n;

    int sz = s.size();
    while(n--){
        cin >> op;
        if(op == "rev"){
            rev = !rev;
        }else{
            cin >> in;

            in %= sz;
            
            if(op == ">") cnt += (!rev ? 1 : -1) * in;
            else cnt += (!rev ? -1 : 1) * in;
        }
    }

    if(rev){
        string s1 = s;
        reverse(s1.begin(),s1.end());
        s = s1;
    }

    cnt %= sz;

    if(cnt < 0){
        cnt = sz + cnt;
    }

    // cout << s << " " <<  cnt << endl;
    if(cnt == 0){
        cout << s;
    }else{
        if(rev) cnt = sz-cnt;

        int i = sz-cnt;

        int t = sz;
        while(t--){
            cout << s[i++];
            i %= sz;
        }
    }
    return 0;
}
```

---

## 作者：heaksicn (赞：0)

记 $S$ 的长度为 $len$。

首先可以注意到循环移位 $len$ 次相当于没移，所以所有数值都可以模 $len$。

在这个前提下，左移 $x$ 位相当于右移 $len-x$ 位，所以可以统一当成右移处理。

同样的，翻转两次相当于没有翻转，所以只用考虑翻转一次后的操作如何处理。

手摸一下可以发现，翻转后右移是移动的后缀相当于翻转前的前缀。所以翻转后右移 $x$ 位相当于翻转前左移 $x$ 位。

累加起来即可。

### code
```
//Man always remember love because of romance only!
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
char c[1000010];
signed main(){
	cin>>c+1;
	int n=strlen(c+1),sum=0,fl=0;
	int T=read();
	while(T--){
		string opt;
		cin>>opt;
		if(opt=="rev") fl^=1;
		else if(opt==">"){
			int x=read()%n;
			if(fl) sum+=(n-x);
			else sum+=x;
		}else{
			int x=read()%n;
			if(fl) sum+=x;
			else sum+=(n-x);
		}
		sum=sum%n;
	}
	if(fl==0){
		for(int i=n-sum+1;i<=n;i++) cout<<c[i];
		for(int i=1;i<=n-sum;i++) cout<<c[i];
	}else{
		for(int i=n-sum;i;i--) cout<<c[i];
		for(int i=n;i>=n-sum+1;i--) cout<<c[i];
	}
		
	return 0;
}

```


---

## 作者：_qhbd_ (赞：0)

# 题意
给定一个字符串 $S$ 并且有 $n$ 次操作，问经过 $n$ 次操作后的字符串。

有以下 $3$ 种操作：

1. `< x` 表示将 $S$ 向左循环移动 $x$ 位。例如：$\mathtt{abcde}$ 执行 `< 2` 后变成 $\mathtt{cdeab}$。
2. `> x` 表示将 $S$ 向右循环移动 $x$ 位。例如：$\mathtt{abcde}$ 执行 `> 2` 后变成 $\mathtt{deabc}$。
3. `rev` 表示将 $S$ 翻转。例如：$\mathtt{abcde}$ 执行 `rev` 后变成 $\mathtt{edcba}$。
# 思路
这个题比较有意思的是前两种操作，初看感觉有点云里雾里，但是很好理解。这里简单举例。

令 $S$ 为 `abcde`，那么左右移动的操作可以看成是将一个长度为 $|S|$ 的滑窗在一个由 $S$ 不断拼接组成的类似 `abcdeabcdeabcde` 的字符串上滑动， `<` 即滑窗向左边滑动，`>` 则刚好相反往右滑动。

而 `rev` 则是把这个类 `abcdeabcdeabcde` 的字符串给反转了而已。

所以，我们只需要维护操作时滑窗滑动的距离，最后在这个由 $S$ 组成的字符串上找到滑窗的位置将对应区域的字符串取出来即可。

需要注意的是，反转前后，对于滑窗移动距离的维护是不一样的，以及注意开 long long。
```cpp
#include<iostream>
using namespace std;
string s,op;
long long opn,x,k,id;
int main(){
    cin>>s;
    scanf("%lld",&opn);
    for(int i=1;i<=opn;i++){
        cin>>op;
        if(op=="rev"){
            k^=1;
            id=-id;
        }
        else if(op[0]=='>'){
            scanf("%lld",&x);
            id-=x;
        }
        else{
            scanf("%lld",&x);
            id+=x;
        }
    }
    long long len=s.size();
    id=(id%len+len)%len;
    if(k)
        for(int i=0;i<len/2;i++)
            swap(s[i],s[len-i-1]);
    s=s+s;
    cout<<s.substr(id,len);
    return 0;
}
```

---

## 作者：LYJ_B_O_Creation (赞：0)

性质：
-
1. ``<`` 与 ``>`` 为逆运算。
2. ``rev`` 偶数次相当于一次没动，奇数次相当于一次。
3. 设字符串长度为 $len$，``<x`` 或 ``>x`` 相当于 ``<(x mod len)`` 或 ``>(x mod len)``。
4. ``<x`` 再 ``rev`` 相当于 ``rev`` 再 ``>x``。

思路：
-

用性质 $1$、$3$ 把多次 ``<x`` 与 ``>x`` 转为 $1$ 次 ``<x`` 或 ``>x``（记 ``<`` 为正，``>`` 为负，累加即可。），用性质 $4$ 把 ``rev`` 都移到前面，让后用性质 $2$ 转为 $1$ 次或 $0$ 次 ``rev``，最后模拟即可，为 $O(n)$。

代码：
-

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10;
int n , sum , num;
char a[N] , b[N] , ans[N];
signed main()
{
    int x;
    cin >> a + 1;
    n = strlen(a + 1);
    int q;
    cin >> q;
    while(q--)
    {
    	char s[10];
    	cin >> s;
    	if(s[0] == '>')
    	{
    		cin >> x;
    		sum += x;
    	}
    	if(s[0] == '<')
    	{
    		cin >> x;
    		sum -= x;
    	}
    	if(s[0] == 'r')
    	{
    		sum *= -1;
    		num ^= 1;
    	}
    }
	if(num == 1) for(int i = 1;i <= n;i++) b[i] = a[n - i + 1];
	else
	{
		for(int i = 1;i <= n;i++) b[i] = a[i];
	}
	if(sum > 0)
	{
		sum %= n;
		for(int i = 1;i <= n;i++) 
		{
			int j = i - sum;
			if(j <= 0) j += n;
			ans[i] = b[j]; 
		}
	}
	else
	{
		sum *= -1;
		sum %= n;
		for(int i = 1;i <= n;i++)
		{
			int j = i + sum;
			if(j > n) j -= n;
			ans[i] = b[j];
		}
		
	}
    for(int i = 1;i <= n;i++) cout << ans[i];
    return 0;
}
```

---

## 作者：ivyjiao (赞：0)

`rev` 老套路了，直接打个反转标记即可，`rev` 两遍就取消标记。

`<` 在有反转标记的时候相当于往右移，否则往左移。

`>` 在有反转标记的时候相当于往左移，否则往右移。

最后输出的时候按有无反转标记分类输出即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,now;
string s,op;
bool p,q;
signed main(){
    cin>>s>>n;
    int len=s.size();
    for(int i=1;i<=n;i++){
        cin>>op;
        if(op=="rev") p=!p;
        if(op=="<"){
            cin>>x;
            if(p) now-=x;
            else now+=x;
        }
        if(op==">"){
            cin>>x;
            if(p) now+=x;
            else now-=x;
        }
    }
    if(now<0) now=-now,q=1;
    now%=s.size();
    if(q) now=s.size()-now;
    if(p) for(int i=now-1;i>=now-1-len+1;i--) cout<<s[(i+2*s.size())%s.size()];
    else for(int i=now;i<=now+s.size()-1;i++) cout<<s[i%s.size()];
}
```

---

