# C - Security 2

## 题目描述

AtCoder 公司的入口处有一个特殊的密码输入设备。该设备由一个显示一个字符串的屏幕和两个按钮组成。

屏幕上显示的字符串为 $t$ 。最初， $t$ 是空字符串。按下按钮后， $t$ 将发生如下变化：

- 按下**按钮 A**，在 $t$ 的末尾添加 "0"。
- 按下**按钮 B**， $t$ 中的每一位数字都会被替换为下一位数字：对于从 `0` 到 `8` 的数字，下一位数字是数值大于 $1$ 的数字；在 `9` 之后的下一位数字是 `0`。

例如，如果 $t$ 是 `1984` 并按下 A 按钮， $t$ 就变成了 `19840`；如果再按下 B 按钮， $t$ 就变成了 `20951`。

给你一个字符串 $S$ 。从空字符串开始，按下 0 次或更多次按钮，直到 $t$ 与 $S$ 重合。求最少需要按多少次按钮。

## 说明/提示

- $S$ 是由 `0`、`1`、`2`、`3`、`4`、`5`、`6`、`7`、`8` 和 `9` 组成的字符串。
- $1 \le |S| \le 5 \times 10^{5}$ ，其中 $|S|$ 是 $S$ 的长度。

## 样例 #1

### 输入

```
21```

### 输出

```
4```

## 样例 #2

### 输入

```
407```

### 输出

```
17```

## 样例 #3

### 输入

```
2025524202552420255242025524```

### 输出

```
150```

# 题解

## 作者：Clover_Lin (赞：5)

博客：https://blog.csdn.net/ArmeriaLeap/article/details/148196461 ，欢迎阅读。
## 题目大意
有一个空串 $t$ 和一个目标串 $S$，每次执行下面两个操作中的任意一个：
- 在 $t$ 的末位添一个 $0$，如 $407$ 变成 $4070$。
- 将 $t$ 中的所有数字变成它的“下一个”，其中“$a$ 的下一个（$a$ 是数字）”指的是 $(a+1)\bmod 10$ 的值。例：$1029$ 变成 $2130$。

问最少多少次操作可以达到目标串。
## 思路
为了方便，我们令 $N$ 表示 $S$ 的长度。

观察数据范围，$N\le5\times10^5$ 很大，需要一个 $O(N)$ 的做法。然后我们发现了一个突破点：每添加一个数字之后，必须立刻调整整个数组的大小，然后再添加下一个。那么现在问题就转化为了求每一次需要调整多少次。

显然，当数组长度为 $i$ 的时候，一定与第 $i$ 个数和第 $i+1$ 个数有关。发现是求差的关系（因为具体的值在最后一次添加后可以调整，但是差必须马上确定）。然后，我们来考虑一下最后一次添加后应该怎么调整。现在，我们得到了前 $N-1$ 个数的“相对数列”——所有的差都是固定的了，但是值随着最后的一组调整而改变。实际上，第 $N-1$ 个数和第 $N$ 个数的差也已经固定了，所以不用重复计算。那么需要的添加次数就是目标串中第 $N$ 个数字的值。
## 代码
AC 记录：[Submission #66099456](https://atcoder.jp/contests/abc407/submissions/66099456)。
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int n; string s;
int f[500010];

int main()
{
	cin >> s;
	n = s.size();
	s = " " + s + "0";
	for (int i = 1; i <= n; i++)
		f[i] = f[i - 1] + (s[i] - s[i + 1] + 10) % 10;
	cout << f[n] + n << endl;
	return 0;
}
```
## 总结
难度大约 $\color{orange} 普及-$。

---

## 作者：syx_2014 (赞：2)

~~结论题为啥还卡半个小时。~~

我们发现，如果一个数字 $s$ 中的数单调不增的话，那密码锁从一个空串变为 $s$ 的最少的次数就是 $s$ 的最高位加上 $s$ 的位数。

过程如下：

以 $6321$ 为例。

过程如下：
$$0\Rightarrow1\Rightarrow2\Rightarrow3\Rightarrow30\Rightarrow41\Rightarrow410\Rightarrow521\Rightarrow5210\Rightarrow6321$$

共 $6+4=10$ 步。

多构造几组就可证明。

如果不是单调不增的呢？

那就把它变成单调不增的！

显然，如果按下 $10$ 次 B 按钮，那屏幕上的数就会与原来一样。

所以如果有一个数小于它后面的数，那就把它不断加 $10$，直到大于等于它后面的数为止。最后再输出 $s$ 的最高位加上 $s$ 的位数的和。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int a[500100];
signed main(){
	cin>>s;
	int n=s.size();
	for(int i=0;i<n;i++) a[i+1]=s[i]-'0'; //这里要把字符串中的每一个数都换成数组中的一个元素，这样才能做后续操作。
	for(int i=n;i>=1;i--){
		a[i]+=a[i+1]/10*10;
		if(a[i]>=a[i+1]);
		else a[i]+=10;
	}
	cout<<a[1]+n<<'\n';
	return 0;
}

```

---

## 作者：Gilbert1206 (赞：2)

## 题解：AT_abc407_c [ABC407C] Security 2

[题目传送门](https://www.luogu.com.cn/problem/AT_abc407_c)

## 题意

现有一个空的字符串，每次我们可以给当前字符串做出两种操作。

1. 给当前字符串末尾加上一个 $0$。
2. 给当前每个字符串的每一个数字加上 $1$，如果当前数字为 $9$，加上 $1$ 后应为 $0$。

现在让你用最少的次数让最开始的字符串变为所给的字符串 $S$。

## 思路

通过 $S$ 的长度可以看出这道题明显是不可以暴力的，所以做法应该为贪心，先观察第二个样例 $407$。

1. 因为他是从末尾构造出一个 $0$。所以先造出第一个 $0$，此时字符串为 $0$，次数为 $1$。
2. 我们可以从中发现如果当前数字 $a_i$ 比数字 $a_{i+1}$ 大或者相等，说明了在当前数字肯定是在 $a_i$ 做完一部分后加进去继续同加同减。那么此时先做四次操作 $2$，再做一次操作 $1$，得到的字符串为 $40$，花了 $6$ 次。
3. 但此时我们发现样例二中的 $0$ 是小于 $7$ 的，此时前面的数都需要加 $10$ 次才能回到原数，当然因为每一个数字都小于 $10$，所以我们可以在此之中把构造出一个 $0$，再与字符串一起每次增加 $1$。从而我们可以算出每次花费的次数应为 $$10+1=11$$ 次，因为样例二中的 $0$ 是小于 $7$ 的，所以 $$6+11=17$$ 次。

所以最终的答案应为 $17$。相信大家应该从样例中知道如何计算了吧。

- 当 $a_i>a_{i-1}$ 时，答案加 $11$ 次。
- 当 $a_i \le a_{i-1}$ 时，答案加 $1$ 次。
- 当 $i=0$ 时，答案加 $a_i+1$ 次。

## code


```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
	string a;
	cin>>a;
	int now=a[0]-'0',ans=now+1;//最开始我们需要的次数
	for(int i=1;i<a.size();i++){//从第二个开始
		if(a[i]-'0'<=now){//如果小于等于前面一个
			ans++;
		}
		else{//如果大于前面一个
			ans+=11;
			
		}
		now=a[i]-'0';
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Jerry20231029 (赞：1)

## 题意

一开始有一个空字符串 $S$，有两种操作：

- 在 $S$ 末尾添加一个字符 `0`
- 将 $S$ 中的所有字符替换为下一个字符（`0` 替换为 `1`，`1` 替换为 `2`，……，`8` 替换为 `9`，`8` 替换为 `0`）

给定一个字符串 $t$，求至少需要几次操作才能将 $S$ 变为 $t$。

## 思路

可以发现，每个单调不上升子串 $s$ 都是可以在 $|s|+9$（$|s|$ 表示 $s$ 的长度）次操作之内得到，所以我们就把 $S$ 分割为若干个单调不上升子串，其中第一个子串 $s_1$ 只需要 $|s_1|+\max\{s_1\}$ 次操作，因为需要插入 $|s_1|$ 个 `0`，并增加 $\max\{s_1\}$ 次；其他的则需要 $|s_i|+10$ 次操作，因为还需要还原前面的所有数字。

## 代码

[AC 记录](https://atcoder.jp/contests/abc407/submissions/66146642)

```cpp
#include<iostream>
#include<string>
using namespace std;

int main(){
	string s,s1;
	int c=0,c1=1;
	cin>>s;
	int i;
	for(i = 1; i < s.size(); i++){
		if(s[i] <= s[i-1]){
			c1++;
		}else{
			break;
		}
	}
	c += c1+s.front()-'0';
	c1 = 1;
	s = s.substr(i);
	if(s.empty()){
		cout<<c;
		return 0;
	}
	for(char ch : s){
		if(s1.empty() || s1.back()>=ch){
			s1.push_back(ch);
		}else{
			c += s1.size()+10;
			s1 = ch;
		}
	}
	c += s1.size()+10;
	cout<<c;
	return 0;
}
```

---

## 作者：shigengxin (赞：1)

### 题意
有一个空字符串，每次可以执行以下操作之一：

* 在字符串后添加一个数字 $0$。
* 把当前字符串上的每一位数字加 $1$（$9$ 变为 $0$）。

问至少经过多少次操作才能得到给定的字符串 $S$。
### 思路
逆向思维，每次可以把每位数字减 $1$（$0$ 变为 $9$）（操作一），或者删除最后一位（为 $0$ 时）（操作二）。

倒序枚举字符串，并使用 $sum$ 记录当前执行过的操作一的次数。

对于每一位数字，由 $sum$ 计算出变化之后的数字，再将 $sum$ 加上把当前数字变为 $0$ 并删除所需的操作次数。额外的操作次数就是这个数字当前的数值。

一直做到字符串为空即可。

答案需加上原来的 $|S|$ 表示操作二的次数。

### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
void solve(){
    int sum = 0;
    for(int i = s.size() - 1; i >= 0; i--){
        int noww = s[i] - '0';
        noww = ((noww - sum) % 10 + 10) % 10;
        sum += noww;
    }
    cout << sum + s.size() << "\n";
}
signed main( ){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> s;
    solve();
    return 0;
}
```

---

## 作者：hjyowl (赞：0)

### 思路

首先直接用搜索做是会超时的。

首先你至少要按 $s$ 的长度次按钮保证长度达到。

那么我们考虑用一个变量 $t$，反过来遍历 $s$ 来求出集体加的最少次数。

令 $c = t \bmod 10$，如果 $c$ 小于当前的 $s_i$，那么 $t$ 就加上 $t-c$，否则就加上 $t-c+10$。

最后答案就是 $t$ 加上 $s$ 的长度。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin >> s;
	long long tt = 0;
	for (long long i = s.size() - 1; i >= 0; i -- ){
		long long t = s[i] - '0';
		long long c = tt % 10;
		long long cc;
		if (c <= t){
			cc = tt - c + t;
		}
		else{
			cc = tt - c + 10 + t;
		}
		tt = cc;
	}
	cout << tt + s.size();
	return 0;
}
```

---

## 作者：zhangbo1000 (赞：0)

显然：

> 能使相邻两个数不同的唯一方法是，在生成前一个数后摁下若干次按钮 B，按了 $x$ 次将会导致前一个数比后一个大 $x$（$9$ 后面跟着 $0$ 意味着这里需要模 $10$）。

所以答案为 $\sum_{i=1}^{n-1}(S_i-S_{i+1}\bmod 10)+S_n+n$，其中 $n$ 为 $S$ 的长度，$S_i$ 为 $S$ 的第 $i$ 个数字。

[代码和评测记录。](https://atcoder.jp/contests/abc407/submissions/66177438)

---

## 作者：_xdd_ (赞：0)

### 题目大意：
给定一个空串，进行以下两种操作使其变为只有数字的字符串 $S$：

- 在末尾添加一个 `0`。
- 将每个位置的数字循环加一（$9$ 加一变为 $0$）。

求最小操作次数。

### 解题思路
倒着操作，即操作 $S$ 使其变为空串。

在倒着操作的前提下，操作变为：

- 把末尾的一个 $0$ 删除。
- 将每个位置的数字循环减一。

我们只需要一直执行操作二，使得 $S$ 的末尾变为 $0$ 然后执行操作一将其删掉，模拟一下就好了。


```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define r0 return 0
#define inf (0x7fffffff)
#define maxn ( 500005 +5)
#define int long long
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
char a[maxn];
int sz,sum,num;
signed main(){
    cin >> a;
    sz=strlen(a);
    while(sz>0){
        int x=a[sz-1]-'0';
        if(x-num<0){
            x+=10-num;
        }else{
            x-=num;
        }
        sum+=x+1;
        num+=x;
        num%=10;
        sz--;
    }
    cout << sum;
    return 0;
}
```

---

