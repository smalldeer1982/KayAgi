# Judg.

## 题目描述

小 M 正在兴致勃勃地敲打着代码，他突然发现提交代码的评测机无响应了。

你查看了后台数据，请你根据这些已有数据判断他没有通过的测试点有哪些。

已知评测结果与测试点是否通过有如下关系：

|评测结果|测试点是否通过|
| :-----------: | :-----------: |
| $\texttt{AC}$ | 是 |
| $\texttt{WA}$ | 否 |
| $\texttt{TLE}$ | 否 |
| $\texttt{MLE}$ | 否 |


## 说明/提示

#### 【数据范围】

对于所有测试数据，满足 $1 \le n \le 10^5$，输入的字符串一定在 $\{\texttt{AC},\texttt{WA},\texttt{TLE},\texttt{MLE}\}$ 之中。

**本题开启捆绑测试，所有数据范围均相同的测试点捆绑为一个 $\text{Subtask}$。**

各测试点的附加限制如下表所示。

|测试点 |$n \le$  |
| :-----------: | :-----------: |
| $1 \sim 5$ | $10$ |
| $6 \sim 12$ | $2 \times 10^3$ |
| $13 \sim 20$ | $10^5$ |


## 样例 #1

### 输入

```
5
AC
WA
AC
TLE
MLE```

### 输出

```
2 4 5```

## 样例 #2

### 输入

```
5
AC
AC
AC
MLE
TLE```

### 输出

```
4 5```

# 题解

## 作者：nightwatch.ryan (赞：7)

## 思路
本题我们只需要判断读入的字符串是否是 `AC`，如果不是，那么我们就在存储未通过测试点数量的 $cnt$ 变量加 $1$，在存储答案的 $r$ 数组里存入该测试点编号，最后输出答案数组。
## 代码
```cpp
#include<iostream>
using namespace std;
int n,r[200000];
string s;
int cnt;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)   {cin>>s;
    if(s!="AC"){
      cnt++;
      r[cnt]=i;
    }
   }

   for(int i=1;i<=cnt;i++)
   {cout<<r[i]<<" ";}

}
```

---

## 作者：__Octhyccc__ (赞：3)

只需要输出没有通过的测试点。

没有通过的测试点就是非 AC 的测试点。设 $s$ 为评测结果，只要 `s!="AC"` 就需要输出。

尽量不要使用 `getline` 或者 `getchar`，有可能出问题。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int N;
int main(){
	scanf("%d",&N);
	for(int i=0;i<N;i++){
		string a;
		cin>>a;//尽量用 cin 或者 scanf。
		if(a!="AC")printf("%d ",i+1);//是输出 i+1，赛时我差点看成了评测结果。
	}
	return 0;
}
```

---

## 作者：what_could_I_do (赞：3)

[传送门](https://www.luogu.com.cn/problem/P9686)

模拟题。

这题只需要依次将字符串读入并判断是否为 `AC` 就行。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		if(s!="AC") printf("%d ",i);
	}
	return 0;
}
```

---

## 作者：ccxswl (赞：2)

# P9686 Judg. 

每次只用判断首字母就行了，这是一个很常用的减小码量的方法（当然，在本题不明显）。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;

string s;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        if (s[0] != 'A')
        	cout << i << ' ';
    }
}
```

---

## 作者：York佑佑 (赞：2)

## 题意
输入 $n$ 行字符串。若第 $i$ 个字符串不为 ```AC``` 的话，则输出 $i$，并且要求输出的数字递增。
## 分析&代码
按照题意模拟即可。遍历到第 $i$ 个串不为 ```AC``` 的话直接输出 $i$ 和空格即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)//遍历1到n
	{
		string str;
		cin >> str;//输入字符串
		if (str != "AC")//不为“AC”则输出i和空格
			cout << i << " ";
	}
	return 0;
}
```




---

## 作者：Eason_cyx (赞：2)

很简单的一道题，考察字符串入门知识。

观察题目可以发现，只要评测结果不是 `AC`，就视为不通过。因此判断一下即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    for(int i = 1;i <= n;i++) {
        string s; cin >> s;
        if(s != "AC") cout << i << ' ';
    }
    cout << endl;
    return 0;
}
```

---

## 作者：Focalors (赞：2)

读入 $n$ 个字符串，若其不为 $\texttt{AC}$，则输出该字符串编号即可。

AC 代码如下：
```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read() {
	ll x = 0, y = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') y = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c & 15), c = getchar();
	return x * y;
}
int n;
string s; 
int main(){
	n = read();
	for (int i = 1; i <= n; i++) {
		cin >> s;
		if (s != "AC") printf("%d ", i);
	}
	return 0;
}
```

---

## 作者：CNS_5t0_0r2 (赞：2)

模拟题。$i$ 从 $1$ 开始，当输入状态不为 ``AC`` 时输出 $i$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	string stat;
	cin >> n;
	for(int i = 1;i <= n;i++){
		cin >> stat;
		if(stat != "AC")
			printf("%d ",i);
	}
}
```


---

## 作者：cirrationaler (赞：2)

一道简单模拟。

这道题最简单的方法就是直接在 `for` 循环中判断题目给出状态是否为 AC，如果不是则输出当前 $i$ 的值，否则就不输出。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n;

string a[MAXN];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++)
	{
		if (a[i] != "AC")
		{
			printf("%d ", i);
		}
	}
	return 0;
}
```

---

## 作者：Big_Dinosaur (赞：1)

依次输入 $n$ 个字符串，如果第 $i$ 个不是 `AC`，输出 $i$ 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
int n;cin>>n;string s;
for(int i=1;i<=n;++i){cin>>s;if(s!="AC")cout<<i<<' ';}
}
```

---

## 作者：WBH_xh_WSD (赞：1)

一.原题链接：[原题链接](https://www.luogu.com.cn/problem/P9686)  
二.思路：  
本题就是输入 $n$ 此测评结果，输出第几次没有通过那个测试点。我们就是模拟。枚举 $i$ 从 $1$ 到 $n$，输入，每次判断它是不是 `AC`，如果不是就输出 $i$。每次都要加空格。  
三.代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
int n;
string s; 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		if(s!="AC")
			cout<<i<<" ";
	}
	return 0;
}
```

---

## 作者：wangweichen666 (赞：1)

## 题目大意
给定 $n$ 组字符串，求所有字符串中内容不为 “AC” 的字符串的**下标**，并按从小到大的顺序输出。
## 题目分析
我们可以用 `string` 开数组，然后用条件语句 `if` 判断。
## 题目解法
在读取完 $n$ 个字符串后用循环语句从 $1$ 到 $n$ 枚举并判断即可。

AC 代码如下：
```c++
#include<bits/stdc++.h>
using namespace std;
string a[100005];
int main(){
	ios::sync_with_stdio(0);//输入输出加速
	cin.tie(0),cout.tie(0);//输入输出加速
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];//读入所有字符串
	for(int i=1;i<=n;i++) 
    		if(a[i]!="AC") cout<<i<<" ";//判断并输出当前字符串的下标
	return 0;
}
```

---

## 作者：Lovely_Elaina (赞：1)

一边读一边比较，如果输入的字符串不是 `AC`，就输出当前序号。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
string s;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    // freopen("app.in","r",stdin);
    // freopen("app.out","w",stdout);
    
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> s;
        if(s != "AC")
            cout << i << " ";
    }
    
    return 0;
}
```

---

## 作者：Yzmddsw (赞：1)

# P9686

## 解法

只要输入不为 $\texttt{AC}$ ，就输出测试点编号。那么先读入数量 $n$ ，循环读入字符串，判断是否为 $\texttt{AC}$ ，按条件输出。

## 代码
```cpp
#include <iostream>
#include <string>
using namespace std;
int main(){
    int n;
    cin>>n;
    string s;
    for(int i=1;i<=n;i++){
        cin>>s;
        if(s!="AC"){//判断输入是否为 "AC" 
            cout<<i<<" ";
        }
    }
    return 0;
}
```


---

## 作者：zjr0330 (赞：0)

根据题意得知：
- `AC` 为正确，其他为错误。

我们可以使用数组来解，即：输入 $n$，定义一个长度为 $n$ 的数组 $a$，输入这个数组，输出时判断 $a_i$ 是否为 `AC`，如果不是，输出 $i$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    string a[n];
    for(int i=0;i<n;i++){
       cin>>a[i];    //输入数组
    }
    for(int i=0;i<n;i++){
       if(a[i]!="AC")cout<<i+1<<' ';    //判断输出
    }
                          
    return 0;
}
```

当然，我们也可以不用数组。即只定义 $n$ 和 $a$，在输入时就做出判断，如果输入的字符不等于 `AC`，那么输出 $i$。代码如下：

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
	int n;
	cin >> n;
	string x;
	for (int i = 0; i < n; i++) {
		cin >> x;
		if (x != "AC") {    //在输入时判断
			cout << i + 1 << ' ';
		}
	}

	return 0;
}

```


---

## 作者：_Evergarden_ (赞：0)

#### [传送门](https://www.luogu.com.cn/problem/P9686)


------------

### 字符串签到题

显然，我们只需要判断字符串是否是 `AC`，我们可以定义数组 $ans$ 来储存答案，用 $cnt$ 来控制下标。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N = 1e5 + 10;

int n, ans[N], cnt;

int main() {
    ios::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);//输入优化

    cin >> n;
    for(int i = 1; i <= n; ++ i) {
        string s;
        cin >> s;
        if(s[0] != 'A') ans[++ cnt] = i;//储存答案
    }
    for(int i = 1; i <= cnt; ++ i) cout << ans[i] << " ";
    return 0;//完美结束
}
```


---

## 作者：rzm120412 (赞：0)

简单入门，直接模拟即可。

不是"AC"就输出。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		if(s!="AC"){
			cout<<i<<" ";
		}
	}
	return 0; 
} 
```


---

## 作者：zhangyuanxiao (赞：0)

## 题意
+ 有 $n$ 条评测结果，按顺序输出每个不为 AC 的评测结果对应的测试点编号。
+ $1 \le n \le 10^5$。

## 分析
用 string 类型读入每条评测结果，若不为 AC，就输出编号。时间复杂度 $O(n)$。

## 代码
```cpp
#include<iostream>
using namespace std;

int n;
string judge;

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>judge;
		if(judge!="AC") cout<<i<<" ";
	}
	return 0;
}
```

---

## 作者：jqQt0220 (赞：0)

大大大淼题。

直接用 `string` 读入，如果不是 `AC` 就输出编号。

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        if(s!="AC")
            printf("%d ",i);
    }
    return 0;
}
```

不过可能这个代码会出点问题，比如样例在终端运行长这样：
```
5
AC
WA
2 AC
TLE
4 MLE
5
```
但是评测只会评测输出内容，所以开个文件输入输出就能看到有正常的输出了，这是不影响 AC 的。

就这么简单。

---

## 作者：zhang_Jimmy (赞：0)

# 思路
我们可以将输入的字符串进行判断，设输入的字符串为 $s$，如果 $s \ne \texttt{AC}$，那么就可以输出当前字符串的编号了。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int t;
string s; 

int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	cin >> t;
	for(int i = 1; i <= t; i ++){
		cin >> s;
		if(s != "AC")
			cout << i << " ";
	}
	return 0;
}

```


---

## 作者：luogu10086 (赞：0)

[传送门](https://www.luogu.com.cn/problem/P9686)

### PART 1

题目大意：

判断测评结果，输出**错误**的测试点编号，并且编号都是递增的。



------------

### PART 2

整体思路：

可以一边输入一边判断输出。

-----

### PART 3

代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[114514];
int main(){
    int n;
    cin>>n;
    int i = 1;
    while(i<=n){
        string s;
        cin>>s;
        if(s!="AC")cout<<i<<" ";//判断
        i++;
    }
}//非常简单的一题
```


---

## 作者：ICU152_lowa_IS8 (赞：0)

一道很简单的题。

如果输入为 $\texttt{AC}$ ，则跳过。

否则输出当前测试点编号即可。

代码：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		if(s=="AC")continue;
		cout<<i<<" ";
	} 
	return 0;
}

```


---

## 作者：ccg12345 (赞：0)

签到题。

## 思路

字符串一个一个的读入，如果不是 `AC` 就输出当前序号，反之略过。

附代码：

```
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	cin >> n;
    for(int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        if(s != "AC")
            cout << i << " ";
    } 
    return 0;
}
```


---

## 作者：Lavande (赞：0)

# 题目

有 $t$ 组数据，每一行有一个字符串 $s$，问没有通过的有哪些测试点。

# 思路

对于输入的每一个字符串 $s$，判断它是否为正确，不是正确就输出下标。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		string s;
		cin>>s;
		if(s!="AC"){
			cout<<i<<" ";
		}
	}
	return 0;
}

```


---

## 作者：CRTL_xzh2009 (赞：0)

简单字符串。

对于输入的字符串 $s$，直接判断第一个字符是不是 `A` 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
string s;
int n;
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        if(s[0]!='A') /不是就输出
            cout<<i<<" ";
    }
    return 0;
}
```


---

## 作者：Crasole (赞：0)

## 思路

因为只有 `AC` 是有通过的，所以在输入时判断，如果当前不为 `AC` 就输出当前的 $i$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string s;
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> s;
		if(s != "AC") cout << i << ' ';
	}
	return 0;
} 
```

---

## 作者：xiaoyang111 (赞：0)

# P9686 Judg. 题解

## 前言

[题面传送门。](https://www.luogu.com.cn/problem/P9686)

[可能更好的阅读体验。](https://www.luogu.com.cn/blog/xiaoyang111/p9686-judg-ti-xie)

求过。

## 讲解

### 思路

这一题主要考察循环结构和分支结构。

读题，可以把题面简化成：

> 有 $n$ 个字符串，为 $\{\texttt{AC},\texttt{WA},\texttt{TLE},\texttt{MLE}\}$ 中的一个，如果第 $i$ 个字符串不等于 $\texttt{AC}$，输出 $i$。

我们按照简化过后的题面做题，先读入 $n$ 个字符串，然后判断这个字符串是不是 $\texttt{AC}$，如果不是就输出这是第几个字符串。因为是第一题，所以比较简单。

### 代码

思路出来了，代码很简单。代码风格可能有些古怪，敬请谅解。

```cpp
#include <iostream>//头文件。
using namespace std;
int main(){
	int n;
	cin >> n;//输入。
	for (int i=1;i<=n;++i){//要从 1 开始循环。
		string str;
		cin >> str;//输入。
		if (str!="AC"){
			cout<<i<<" ";//因为是从 1 开始循环的所以可以直接输出。
		}
	}
	return 0;
}
```

---

## 作者：littleqwq (赞：0)

# P9686 Judg.题解

[博客里看更好！！！](https://www.luogu.com.cn/blog/wangzihandeboke1026/ti-xie)

### 题目意思：

就是看哪几行上的字符串是 ```AC```，如果是不用管他，如果不是那么就输出他的序号 $i$。

### 大致思路：

首先输入，输入的字符串变量类型用 ```string```，当然 ```char``` 也可以，这道题用字符串更好，接着每次判断是否不等于 ```AC```，成立就输出它的编号 $i$，即可！

代码实现：

```
#include<bits/stdc++.h>
using namespace std;
long long n;
string s;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		if(s!="AC"){
			cout<<i<<' ';
		}
	}
	cout<<endl<<endl;
	return 0;
} 
```
这样就可以 AC 了，仅供参考哦！！！

---

