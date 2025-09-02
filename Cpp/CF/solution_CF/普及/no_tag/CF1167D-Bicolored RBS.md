# Bicolored RBS

## 题目描述

A string is called bracket sequence if it does not contain any characters other than "(" and ")". A bracket sequence is called regular (shortly, RBS) if it is possible to obtain correct arithmetic expression by inserting characters "+" and "1" into this sequence. For example, "", "(())" and "()()" are RBS and ")(" and "(()" are not.

We can see that each opening bracket in RBS is paired with some closing bracket, and, using this fact, we can define nesting depth of the RBS as maximum number of bracket pairs, such that the $ 2 $ -nd pair lies inside the $ 1 $ -st one, the $ 3 $ -rd one — inside the $ 2 $ -nd one and so on. For example, nesting depth of "" is $ 0 $ , "()()()" is $ 1 $ and "()((())())" is $ 3 $ .

Now, you are given RBS $ s $ of even length $ n $ . You should color each bracket of $ s $ into one of two colors: red or blue. Bracket sequence $ r $ , consisting only of red brackets, should be RBS, and bracket sequence, consisting only of blue brackets $ b $ , should be RBS. Any of them can be empty. You are not allowed to reorder characters in $ s $ , $ r $ or $ b $ . No brackets can be left uncolored.

Among all possible variants you should choose one that minimizes maximum of $ r $ 's and $ b $ 's nesting depth. If there are multiple solutions you can print any of them.

## 说明/提示

In the first example one of optimal solutions is $ s =  $ " $ \color{blue}{()} $ ". $ r $ is empty and $ b =  $ " $ () $ ". The answer is $ \max(0, 1) = 1 $ .

In the second example it's optimal to make $ s =  $ " $ \color{red}{(}\color{blue}{(}\color{red}{)}\color{blue}{)} $ ". $ r = b =  $ " $ () $ " and the answer is $ 1 $ .

In the third example we can make $ s =  $ " $ \color{red}{(}\color{blue}{((}\color{red}{)()}\color{blue}{)())} $ ". $ r =  $ " $ ()() $ " and $ b =  $ " $ (()()) $ " and the answer is $ 2 $ .

## 样例 #1

### 输入

```
2
()
```

### 输出

```
11
```

## 样例 #2

### 输入

```
4
(())
```

### 输出

```
0101
```

## 样例 #3

### 输入

```
10
((()())())
```

### 输出

```
0110001111```

# 题解

## 作者：lukelin (赞：4)

模拟两个颜色的扩号层数，贪心，如果是左括号，哪边的层数浅就放那边；如果是右括号，哪边的层数深就放那边。  
至于层数的维护，~~两个int就做掉了~~  

放个代码：
```cpp
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

inline int read(){
    int x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

int rd = 0;
int bl = 0;
int ans[200005];

int main(){
	int n = read();
	string s; cin >> s;
	for (int i = 0; i < n; ++i){
		if (s[i] == ')')
			(rd > bl) ? (--rd, ans[i] = 0) : (--bl, ans[i] = 1);
		else if (s[i] == '(')
			(rd < bl) ? (++rd, ans[i] = 0) : (++bl, ans[i] = 1);
	}
	for (int i = 0; i < n; ++i)
		printf("%d", ans[i]);
	return 0;
}
```

---

## 作者：saixingzhe (赞：3)

# 分析

题意其实就是让两边的扩号层数最接近，输出每个括号是分给 `1`，还是 `0`。

我们可以设左括号为 $+1$，右括号为 $-1$，我们要使最后和等于 $0$，且两边操作中的最大值最接近，不难得出一个结论，如果是左括号，放在数值小的那边；如果是右括号，放在数值大的那边。

为什么这个是对的呢？第一，因为给的序列一开始值就是 $0$，这种方法可以平衡两边的数值，最后能使其都等于 $0$；第二，这个方法可以随时平衡两边的数值，使其同速增长，同速下降，所以是最优的。

**代码就不放了。**

---

## 作者：UnknownPeople (赞：1)

## 题意简述  
定义合法括号序列的深度为其嵌套的最大层数。  
现在要给一个长为 $ n $ 的合法括号序列上红蓝两色中的一种，使每种颜色提取出来都是合法括号序列，且深度较大的序列深度最小。  
## 分析
一道比较简单的贪心题。  
一个长为 $ n $ 的合法括号序列中，一定有 $ n/2 $ 个括号。要使每个序列合法，那么每个序列都包含整数个括号。要使深度较大的序列深度最小，就是要使两个序列长度尽可能相近。  
所以可以得到思路，用两个整数储存所遇到的`(`和`)`，交替涂色。由于序列合法，所以任意一个`(`必定与所对应的`)`颜色一样

代码
```cpp
#include<iostream>
using namespace std;
bool str[200005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	int cnt1=0,cnt2=0;
	for(int i=0;i<n;i++){
		char c;
		cin>>c;
		if(c=='('){
			str[i]=cnt1%2;
			cnt1++;
		}
		else{
			str[i]=cnt2%2;
			cnt2++;
		}
	}
	for(int i=0;i<n;i++)
		cout<<str[i];
	return 0;
} 
```
[~~目前是最优解~~](https://www.luogu.com.cn/record/148796142)

---

## 作者：installb (赞：1)

先看题 看到**minimizes maximum**应该可以想到是二分答案  
在最大深度已知的情况下 可以判断是否可行  



**solution:** 二分最大深度  
对于一个括号序列 它的最大深度就是**每一个位置**的**左括号前缀和减去右括号前缀和**的最大值  

为了方便我们直接用两个变量就可以分别记录两种颜色当前位置**左括号数量减去右括号数量**的值  

把一开始遇到的左括号$($先全部标记为颜色0 如果把这个括号标记完之后左括号比右括号多超过二分的答案 就标记为1  
颜色1还超过就代表不可行了
遇到右括号就如果颜色1的左右括号数量差值大于0 标记颜色1 颜色1的值减1  
否则一样的方法处理颜色0  

记得把答案记录下来

虽然这道题目要求的是方案 看似和最大深度没有关系 但是根据深度是可以在判断是否可行的同时直接求出方案  

主要的都在上面讲了 代码就不贴注释了。

## code:
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

LL n,m,k;
LL col[500005] = {0};
LL ans[500005] = {0};
LL L,R,M;
string s;

char ck(LL x){ // char可以代替bool...
  	memset(col,0,sizeof(col));
	LL r = 0,b = 0;
	for(LL i = 0;i < n;i ++){
		if(s[i] == '('){
			if(r < x){ r ++; col[i] = 0; }
			else{ b ++; col[i] = 1; }
			if(b > x) return 0; // 遇到左括号的处理 如果两个都超过x就无法满足返回false
		}
		if(s[i] == ')'){
			if(b > r){ b --; col[i] = 1; }
			else{ r --; col[i] = 0; } // 右括号的处理
		}
    }
	for(LL i = 0;i < n;i ++) ans[i] = col[i]; // 记录答案返回true
	return 1;
}

int main(){
	ios::sync_with_stdio(false);
	cin >> n;
	cin >> s;
	L = 1; R = n;
	while(L <= R){ // 二分答案
		M = (L + R) >> 1;
		if(!ck(M)) L = M + 1;
		else R = M - 1;
	}
	for(LL i = 0;i < n;i ++) cout << ans[i]; // 输出答案
	cout << endl;
	return 0;
}
//
```

**此题完结**

---

## 作者：TPJX (赞：0)

[文章传送门](https://www.luogu.com.cn/article/jag5azhk)

从左到右遍历括号序列，对于每个左括号，优先选择当前两边深度较小的那边放置，右括号放到当前深度较大的那边。能尽量平衡两边的深度，避免某一边的深度过大。

代码：
```cpp
#include <iostream>
using namespace std;
int n, r, b;
int main() {
    string s;
    cin >> n >> s;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') {
            if (r <= b) {
                cout << "0";
                ++r;
            } else {
                cout << "1";
                ++b;
            }
        } else {
            if (r >= b) {
                cout << "0";
                --r;
            } else {
                cout << "1";
                --b;
            }
        }
    }
    cout << endl;
    return 0;
}
```

---

## 作者：King_duck (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1167D)

这道题主要就是模拟和贪心，如果是左括号，哪边的层数浅就放哪边；如果是右括号，哪边的层数深就放哪边。

上代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,a,b,ans[N];
string s;
signed main()
{
	cin>>n>>s;
	for(int i=0;i<n;i++)
	{
		if(s[i]==')')
		{
			if(a>b)
			{
				a--;
				ans[i]=0;
			}
			else
			{
				b--;
				ans[i]=1;
			}
		}
		else if(s[i]=='(')
		{
			if(a>b)
			{
				a++;
				ans[i]=0;
			}
			else
			{
				b++;
				ans[i]=1;
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		cout<<ans[i];	
	}
	return 0;
}
```

---

