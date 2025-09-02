# [ARC059D] アンバランス

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc059/tasks/arc059_b

文字列 $ t $ について、$ t $ の長さが $ 2 $ 以上であり、かつ $ t $ の中の文字のうち過半数が同じ文字であるとき、$ t $ を*アンバランス*であると呼ぶことにします。例えば、`voodoo` や `melee` はアンバランスであり、`noon` や `a` はアンバランスではありません。

小文字のアルファベットからなる文字列 $ s $ が与えられます。$ s $ にアンバランスな (連続する) 部分文字列が存在するか判定してください。存在する場合は、$ s $ の中でそのような部分文字列が存在する位置を一つ示してください。

## 说明/提示

### 制約

- $ 2\ ≦\ |s|\ ≦\ 10^5 $
- $ s $ は小文字のアルファベットのみからなる。

### 部分点

- $ 2\ ≦\ |s|\ ≦\ 100 $ を満たすデータセットに正解した場合は、$ 200 $ 点が与えられる。

### Sample Explanation 1

文字列 $ s_2\ s_3\ s_4\ s_5 $ $ = $ `eede` はアンバランスな文字列です。他にもアンバランスな部分文字列は存在し、例えば `2 6` と出力しても正解となります。

### Sample Explanation 2

文字列 `atcoder` はアンバランスな部分文字列を持ちません。

## 样例 #1

### 输入

```
needed```

### 输出

```
2 5```

## 样例 #2

### 输入

```
atcoder```

### 输出

```
-1 -1```

# 题解

## 作者：cq_loves_Capoo (赞：7)

我发现我好像跟题解写的不一样，但思路还是差不多的。   
    
思路大致如下，与其它题解的差不多：    
    
>从字符串的开头搜索到结尾，如果该字符串与后面一个或者后面第二个是相同的，那么该字符与跟它相同的就是一个符合题目要求的子序列。
   
>例如：$IIIAM$ ，虽然 $IIIAM$ 是一个符合要求的子序列，但是 $II$ 也符合，所以直接输出 $0$ $1$就可以了。
   
>再举一个例子：$IOIII$ ，它本身就是一个符合要求的子序列，但是，最前面的是 $IOI$ ，所以可以得出结论，答案不是两个长度的子序列就是三个长度的子序列。
    
贴 $AC$ 代码（改了码风）：
   
```
#include<bits/stdc++.h>
using namespace std;
string s;//字符串
int main()
{
	cin>>s;//输入字符串s
	for(int i=0; i<s.length(); i++)//循环
	{
		if(s[i]==s[i+1]) //如果跟下一个相等
		{
			cout<<i+1<<" "<<i+2<<endl;//就输出i+1和i+2。
			return 0;//直接退出程序
		}
		if(s[i]==s[i+2])//如果跟第三个字符相等
		{
			cout<<i+1<<" "<<i+3<<endl;//就输出i+1和i+3。
			return 0;
		}
	}
	cout<<"-1 -1\n";//如果还没退出程序，输出-1 -1
}

```
**程序记得加换行！**


---

## 作者：tZEROちゃん (赞：4)

### Language

- 中文
- [日文 & 英文](https://www.cnblogs.com/tearing/p/15209951.html)

### Solution

为了方便表述，在下文中，$k = |s|$。 

#### Solution（200 点）

$s$ 中至少有 $\frac{k \cdot (k - 1)}{2}$ 个长度为 $2$ 以上的子字符串，我们发现题目中提到：
 
> $2\le |s| \le 100$ を満たすデータセットに正解した場合は、$200$ 点が与えられる。

所以我们可以枚举出 $s$ 的所有子串。通过计算每个字母在每个子串中出现的次数来确定它是否是符合规定的。


#### Solution（400 点）

但是你发现这样显然会 TLE，所以我们尝试其他方法。

那么我们观察多个字符串，发现了，我们只需要判断它是否有一个 $\tt XYX$ 或 $\tt XX$ 形式的字符串，即，两个字母之间最多只有一个其他的字母。

下面说一下原因（因为别的题解好像都没说.jpg）：

- 如果这些形式都不存在，那么在同一字母的两个字母之间总会有 $\ge 2$ 的其他字母，原因是没有一种字母在子串中占严格多于长度一半的字符。

时间复杂度：$O(k)$。

### Code

#### C++ (GCC 9.2.1)

```cpp
string s;
iocin >> s;
FOR (i, 0, int(s.size())) {
  if (s[i] == s[i + 1]) {
    cout << i + 1 << ' ' << i + 2 << endl;
    return 0;
  }
}
FOR (i, 0, int(s.size())) {
  if (s[i] == s[i + 2]) {
    cout << i + 1 << ' ' << i + 3 << endl;
    return 0;
  }
}
cout << -1 << ' ' << -1 << endl;
```

#### Pascal (FPC 3.0.4)

```pascal
var i: longint;
    s: String;
    
begin
  readln(s);
  for i := 2 to length(s) do begin
    if s[i] = s[i - 1] then begin
      writeln(i - 1, ' ', i);
      exit;
    end;
    if s[i] = s[i - 2] then begin
      writeln(i - 2, ' ', i);
      exit;
    end;
  end;
  writeln('-1 -1');
end.
```

#### Python (3.8.2)

```python
s = input()
n = len(s)
for i in range(n - 1) :
  if s[i] == s[i + 1] :
    print(i + 1, i + 2)
    exit()
for i in range(n - 2) :
  if s[i] == s[i + 2] :
    print(i + 1, i + 3)
    exit()
print(-1, -1)
```

---

## 作者：kaceqwq (赞：1)

## 题目大意：
给出字符串 $s$ ,求区间 $[l,r]$ ,使得该子串中有一种字母出现的次数严格大于该子串长度的一半.
如果没有符合条件的子串,输出两个 $-1$ .

## 分析：

首先看题，发现只需要我们截取的长度大于区间长度的一半即可，并没有规定区间长度的多少。

接着，我们可以想到，如果区间长度为 2 （就是相邻的两个字符），那么只要这两个字符一样，就满足条件；如果区间长度为 3 ，那么只要其中两个字符一样，也满足条件（由于相邻的情况我们已经判断过了，所以我们只需要判断区间中除了中间两个字符相不相等即可）。

然后如果上面都不满足，输出两个 "-1" 即可。

最后是代码实现，如下：

# Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{	
	string a;
	getline(cin,a);
	int len = a.size();   //获取字符串的长度
	for (int i = 0;i < len;++ i)
	{
		if(a[i] == a[i + 1]) //判断区间长度为 2 的情况
		{
			cout << i + 1 << ' ' << i + 2 << '\n';
			return 0;
		}
		if(a[i] == a[i + 2]) //判断区间长度为 3 的情况
		{
			cout <<i + 1 << ' ' << i + 3 << '\n';
			return 0;
		}
	}
	cout << "-1 -1" << '\n';  //如果都不满足,即输出两个-1.
	return 0;
}
```



---

## 作者：智子·起源 (赞：1)

这道题真的好奇葩。。。

让我来解释一下为什么楼下的为什么说只有两种情况。

### 题目意思说，只要任意一个符合要求的区间的左端点右端点都是正确的，所以我们可以从简单的入手。

### 例如：

### eelsdieeeee是符合要求的，但里面的ee也是符合要求的，这时我们只要输出ee的区间范围就可以了，所以题目变得简单很多。

刚开始我就只考虑到了连续两个相同字母的子串，然后wrong了六个点。TAT

         。 。
         。 。
         
         
难道还有什么情况吗？

### 对，还有一种隔着一个字母的。如：qwq、QAQ、TAT等等，这些子串虽然不是相同字母黏在一起，但也符合要求，所以这种情况也要考虑。

接下来。。。


就没有了○（~▽~）○

### 因为再有所谓的其它情况也必须是由以上两种情况组合而成的。

举个例子：

这个子串：qwoq

很显然是不符合要求的。

想让它符合要求，那就必须在任意一个空位上加多一个“q”。

那接下来有能会变成：

qqwoq     qwqoq     qwoqq

这时候，这个子串就是符合要求的了。但请看一下，是不是每一个子串里都包含了上面两种情况的任意一种？

所以，这道题动动脑筋想一想还是很简单的。

以上加粗的字可供读者再看一遍理清思路。

结合一下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int len;
int main()
{
  cin>>s;
  len=s.size();
  for(int i=0;i<len-1;i++)
  {
    if(s[i]==s[i+1]){printf("%d %d\n",i+1,i+2);return 0;}
  }
  for(int i=0;i<len-2;i++)
  {
    if(s[i]==s[i+2]){printf("%d %d\n",i+1,i+3);return 0;}
  }
  printf("-1 -1\n");
  return 0;
}

```

码风比较容易接受，可供大家参考（不是抄袭！！！！！）

管理员大大，看在我解释了这么多的份上，就过一篇吧。

---

## 作者：Tarsal (赞：0)

这个题最开始还准备用一种特别复杂的方法去做，大概是：

维护每一个字母在之前出现的最大贡献，大概就是 $总数 - 2 * 该字母出现个数$ 的最小值，然后判断这个是否存在字母出现次数严格大于长度的一半。

后面突然发现，可以贪心的搞。

你发现如果一段区间满足题意，那么考虑最近的 $2$ 个相同的字母的位置。

当区间长度为奇数时，并且某一字母的个数是 $\frac{长度 + 1}{2}$ 这个时候所有字母(选定)之间都最多相距 $1$ 个其他字母。

其他情况都至少会有一对相邻的字母(选定)。

如果存在区间满足题意，那么一定会存在长度为 $2$ 或者 $3$ 的区间更先满足题意。

所以只要判断每一个字母的前一个或者前 $2$ 个和它是不是同一字母即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ls (x << 1)
#define rs (x << 1 | 1)
#define mid ((l + r) >> 1)
#define int long long
#define Rep(x, a, b) for(int x = a; x <= b; ++ x)
#define Dep(x, a, b) for(int x = a; x >= b; -- x)
#define Next(i, x) for(int i = head[x]; i ; i = e[i].nxt)
int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
const int maxn = 1e5 + 10;
const int maxm = 2010;
const int XRZ = 1e9 + 7;
char s[maxn]; int f[30];
signed main() {
    scanf("%s", s + 1); int len = strlen(s + 1);
    Rep(i, 1, len) {
        if(s[i] == s[i - 1]) { printf("%d %d", i - 1, i); return 0;}
        if(s[i] == s[i - 2]) { printf("%d %d", i - 2, i); return 0;}
    } puts("-1 -1");
	return 0;
}
```

---

## 作者：RioBlu (赞：0)

好好想一想：

1.对于**一个相邻的相同的可以选择**比如：bee 或 nextdoor

2.对于**一个中间隔了个字符但相同的字符可以选择**比如：even 或 iakioi

本题只说输出一个方案，所以这样子就可以AC了
```
#include<bits/stdc++.h>
using namespace std;
string a,b;
int main()
{
	cin>>a;
	for(int s=1;s<a.size();s++)
	{
		if(a[s]==a[s-1])
		{
			cout<<s<<" "<<s+1<<endl;
			return 0;
		}
	}
	for(int s=2;s<a.size();s++)
	{
		if(a[s]==a[s-2])
		{
			cout<<s-1<<" "<<s+1<<endl;
			return 0;
		}
	}
	cout<<-1<<" "<<-1<<endl;
	return 0;
}
```

---

## 作者：Lithium_Chestnut (赞：0)

根据题目判断，看起来寻找合法子串非常简单。

来推一推几种情况：

 + `zwzzz`：那么显然，这个串共有 $5$ 个字符，`z` 占了 $4$ 个，从前至后找，最先找到的合法子串是 `zwz`，所以输出 `0 2` 即可。这种类别我们称之为：$\text{ABA}$ 型。
 
 + `qqwqq`：与上一个相同，依然从前至后找，最先找到的合法子串是 `qq`，所以输出 `0 1` 即可。这种类别我们称之为：$\text{AA}$ 型。
 
就这两种。

看到这里，很多小伙伴要来抬杠了：那你说 `kkksc` 这种难道不是一种新情况吗？

那么这里呢，为方便，我们完全可以直接把 `kkk` 看成 `kk`，这样就可以直接归到 $\text{AA}$ 型中了。

那么讲下代码，循环判断：如果字符串第 $i$ 位与其第 $i+1$ 位相同，也就是我们的 $\text{AA}$ 型，就直接输出 $i$ 和 $i+1$ 即可；如果字符串第 $i$ 位与其第 $i+2$ 位相同，也就是我们的 $\text{ABA}$ 型，就直接输出 $i$ 和 $i+2$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	cin>>s;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]==s[i+1])
		{
			cout<<i+1<<" "<<i+2;
			return 0;
		}
	}
	for(int i=0;i<s.length();i++)
	{
		if(s[i]==s[i+2])
		{
			cout<<i+1<<" "<<i+3;
			return 0;
		}
	}
	cout<<"-1 -1";
	return 0;
}
```

---

