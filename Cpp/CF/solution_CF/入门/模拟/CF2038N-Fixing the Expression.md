# Fixing the Expression

## 题目描述

一个表达式是由三个字符组成的字符串，其中第一个和最后一个字符是数字（从 $0$ 到 $9$ ），中间的字符是一个比较符号（$<$ 、$=$ 或 $>$ ）。

如果比较符号与数字相匹配，那么这个表达式就是成立的（例如，如果第一个数字严格小于最后一个数字，那么比较符号就应该是 $<$ ）。

例如，表达式 $1<3$ 、$4>2$ 、$0=0$ 是成立的，而 $5>5$ 、$7<3$ 则不成立。

给定一个字符串，它是一个表达式。尽可能少地改变字符，使变成一个成立的表达式。注意，如果已经是成立的，就应该保持原样。

## 样例 #1

### 输入

```
5
3&lt;7
3&gt;7
8=9
0=0
5&lt;3```

### 输出

```
3&lt;7
8&gt;7
8&lt;9
0=0
0&lt;3```

# 题解

## 作者：Vct14 (赞：2)

考虑只将符号改对。这样如果符号本来就正确相当于没改，如果符号错误相当于只改一个字符，一定最优。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;cin>>n;
	while(n--){
		string c;cin>>c;
		if(c[0]<c[2]) c[1]='<';
		if(c[0]>c[2]) c[1]='>';
		if(c[0]==c[2]) c[1]='=';
		cout<<c<<"\n";
	}
	return 0;
}
```

---

## 作者：adsd45666 (赞：2)

最后一题这么水的比赛不多见了。

## 题意概述：

给予 $T$ 组数据，每组数据为一个不等式，输出使用最少次数将其修改为正确后的不等式。



## 解题思路：

由于不用判断不等式的对错，那么我们其实只需改变不等号的方向便是最少的修改次数。对于已经正确的来说，输出正确的不等号方向不会消耗修改次数，对于不正确的，都是一次即可，于是很简单便得出了代码。

## code

```cpp
#include <bits/stdc++.h>
#define seq(q, w, e) for (int q = w; q <= e; q++)
#define ll long long
using namespace std;
const int maxn = 1e5+10,inf=0x7fffffff;
char x,op,y;
int t;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>t;
    seq(i,1,t){
        cin>>x>>op>>y;
        if(x<y)
            cout<<x<<"<"<<y;
        else
            if(x==y)
                cout<<x<<"="<<y;
            else
                if(x>y)
                    cout<<x<<">"<<y;
        cout<<"\n";
    }
    return 0;
}
```

---

## 作者：JoeZYQ (赞：1)

### 思路分析
由于必须改最少的字符，所以我们直接考虑改符号，那么最小字符数量一定 $\le 1$。

既然是改符号，那么原式正不正确都不重要了，直接按照 $a$ 和 $b$ 的大小关系输出正确的算式，这样一定是对的，同时又能保证改的字符数是最小的。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
main(){
	int T;
	cin>>T;
	while(T--){
		int a,b;
		char c;
		cin>>a>>c>>b;
		if(a>b)cout<<a<<">"<<b<<"\n";
		if(a==b)cout<<a<<"="<<b<<"\n";
		if(a<b)cout<<a<<"<"<<b<<"\n";
	}
}

```

---

## 作者：woshishabi1145144444 (赞：1)

这道题目是简单题，题意是：对原式进行最少次数的更改，使得改动后的式子成立。

思路也很简单，如果原式成立，那么直接输出原式。否则**更改符号**即为最少次数的改动。

代码：

```cpp
    #include<bits/stdc++.h>
    #define int long long
    using namespace std;
    int t,a,b;
    char ch;
    signed main(){
    	cin>>t;
    	while(t--){
    		cin>>a>>ch>>b;
    		if(a<b){
    			cout<<a<<'<'<<b<<"\n";
    		}
    		if(a==b){
    			cout<<a<<'='<<b<<"\n";
    		}
    		if(a>b){
    			cout<<a<<'>'<<b<<"\n";
    		}
    	}
    	return 0;
    }
```

---

## 作者：Qerucy (赞：1)

题意：给定一个二元等式或不等式，每次操作可以修改这个式子的一个字符，求把这个二元式子变成立所需的最小操作次数。

签到题，我们可以发现操作次数最多为 $1$ 次，如果式子成立则为 $0$，不成立则为 $1$，因为我们可以改变中间的符号把不成立的式子变成立。

代码：


```cpp
#include<bits/stdc++.h>

using namespace std;

int t;
int a,b;
char c;

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%c%d",&a,&c,&b);
		if(a>b){
			printf("%d>%d\n",a,b);
		}
		if(a<b){
			printf("%d<%d\n",a,b);
		}
		if(a==b){
			printf("%d=%d\n",a,b);
		}
	}
	return 0;
}
```

---

## 作者：jgysb (赞：1)

这是一道字符串的水题

## 思路
对于每次询问，我们可以直接拿出两个数字进行比较。会有以下两种情况：

- 原式成立，直接输出

- 原式不成立，就改符号使原式成立。

这样每次最多只会改一个符号，符合题意。

## code

```cpp
#include<iostream>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)//多测 
	{
		string a;
		cin>>a;
		int x=a[0],y=a[2];
		//注意这里，虽然得到的是数字的ASCLL码,但是因为我们只需要比较两个数的大小，所以不需要转化成对应数字 
		char z=a[1];
		if((z=='>'&&x>y)||(z=='<'&&x<y)||(z=='='&&x==y))cout<<a<<"\n";//原式成立就直接输出 
		else//原式不成立就改符号使原式成立 
		{
			if(x<y)a[1]='<';
			else if(x>y)a[1]='>';
			else a[1]='=';
			cout<<a<<"\n";//输出答案 
		}
	}
	return 0;
}
```

ps:题面样例爆了，附正确的样例
### 样例输入

```
5
3<7
3>7
8=9
0=0
5<3

```

### 样例输出

```
3<7
8>7
8<9
0=0
0<3

```

---

## 作者：wuyouawa (赞：0)

### 题目大意

表达式是由三个字符组成的字符串，其中第一个和最后一个字符是数字（从 $0$ 至 $9$），中间字符是比较符号（$<$、$=$ 或 $>$）。

如果比较符号与数字匹配，则表达式为真（例如，如果第一个数字严格小于最后一个数字，则比较符号应为 $<$）。

例如，表达式 $1<3$，$4>2$，$0=0$ 为真，而 $5>5$，$7<3$ 则是假。

给一个字符串 $S$，求修改最少的字符使表达式为真，输出修改后的字符串，如果本来就为真，保持原样。

如果有多解输出任意解。
### 思路

这道题很明显改符号是最优的，因为最多只需改一次。

那么直接输出原来的数字，再判断这两个数的正确大小关系即可。

### CODE


```cpp
#include<bits/stdc++.h>
using namespace std;
char a,b,c;//定义三个字符作为表达式
int t; 
int main(){
	cin>>t;
    while(t--)
    {
    	cin>>a>>b>>c;
    	cout<<a;//先输出数字 
    	if(a<c)  cout<<"<";
		if(a==c)  cout<<"="; 
		if(a>c)  cout<<">";
		//判断输出正确的比较字符
		cout<<c<<endl;//多测，换行 
    }
  return 0;
}
```

---

## 作者：ivyjiao (赞：0)

显然我们只需要修改比较符号就能让原等式成立，这样修改只需要修改 $1$ 个位置，是最少的。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,c;
char b;
int main(){
    cin>>t;
    while(t--){
        cin>>a>>b>>c;
        cout<<a;
        if(a==c) cout<<"=";
        if(a<c) cout<<"<";
        if(a>c) cout<<">";
        cout<<c<<endl;
    }
}
```

---

## 作者：Eason_cyx (赞：0)

笑晕了，这题吃了两发才过 /xk

如此实力，如何 NOIP？

----

题意：给定两个数和它们可能错误的大小关系，你需要把这个大小关系改成正确的。

例如：`3<7`，大小关系正确，那么直接输出 `3<7`；`3>8` 大小关系错误，你需要改成 `3<8` 输出。

----

签到题。因为保证两个数都是一位数，所以直接将它们从字符串中提取出来再判断大小关系即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while(t--) {
        string s; cin >> s;
        int a = s[0] - '0',b = s[2] - '0';
        if(a == b) cout << a << "=" << b << endl;
        else if(a < b) cout << a << "<" << b << endl;
        else cout << a << ">" << b << endl;
    }
    return 0;
}
```

---

## 作者：JOKER_chu (赞：0)

## 闲话

初一第一次打 ICPC，我开到了签子，@DASADI 秒了 C 和 J，我是菜鸡。

## 题意

给你 $t$ 个形如 $a < b \lor a > b \lor a = b$ 的式子，满足 $0 \leq a, b \leq 9$，让你修改表达式最少的字符使得式子成立。

## 解法

模拟，显然最多修改一个字符，因为 $a, b$ 都是一位数，所以修改符号还是 $a \lor b$ 的代价都一样，都是 $1$。

## 代码

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 2e5 + 5;
 
 
 
void solve() {
  string a; cin >> a;
  if (a[1] == '>') {
    if (a[0] > a[2]) {
      cout << a << '\n';
    } else if (a[0] < a[2]) {
      cout << a[0] << "<" << a[2] << '\n';
    } else {
      cout << a[0] << "=" << a[2] << '\n';
    }
  } else if (a[1] == '<') {
    if (a[0] < a[2]) {
      cout << a << '\n';
    } else if (a[0] > a[2]) {
      cout << a[0] << ">" << a[2] << "\n";
    } else {
      cout << a[0] << "=" << a[2] << '\n';
    }
  } else {
    if (a[0] < a[2]) {
      cout << a[0] << '<' << a[2] << '\n';
    } else if (a[0] > a[2]) {
      cout << a[0] << ">" << a[2] << "\n";
    } else {
      cout << a[0] << "=" << a[2] << '\n';
    }
  }
}
 
int main() {
  ios :: sync_with_stdio(0), cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) solve();
  return 0;
}
```

---

## 作者：GCSG01 (赞：0)

### 思路
一道入门题，不需要想太复杂，最简便的方法便是修改关系符，这样最多只用一次，我们设正确的关系符为 $op1$，当前的关系符为 $op$，则当 $op=op1$ 时，不用修改，自然是最优的。而 $op$ 与 $op1$ 不同时，只用修改一次，也肯定是最优的。因为当前关系式不对时必须要修改，而且最少修改一次。  
综上所述，只需要通过两个数确定正确的运算符并输出即可。
### Code
赛时代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("1.in","r",stdin);
    #endif
    int t;
    cin>>t;
    while(t--)
    {
        int a,b;
        char c;
        char s;
        cin>>a>>c>>b;
        if(a<b)s='<';
        else if(a==b)s='=';
        else s='>';
        cout<<a<<s<<b<<"\n";
    }
    return 0;
}
```

---

