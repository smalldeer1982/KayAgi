# 「MSTOI-R1」MST Find

## 题目描述

给你一个字符串，查询字符串中 `M`，`S` 和 `T` 的个数。

不区分大小写。

保证输入的字符串长度 $n$ 不超过 $10^5$。

## 说明/提示

假设输入的字符串的长度为 $n$，则 $1\le n\le 10^5$，保证只包含大小写字母和空格。

## 样例 #1

### 输入

```
MinimumSpanningTree MSTqwq```

### 输出

```
4 2 2```

## 样例 #2

### 输入

```
You must DO your hOMeWork```

### 输出

```
2 1 1```

# 题解

## 作者：MinimumSpanningTree (赞：6)

[题目链接](https://www.luogu.com.cn/problem/P12517)

用三个变量分别表示三个字母的个数，遍历字符串并统计个数。

因为输入的字符串包含空格，所以需要使用 `getline` 输入。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
string s;
int n,c1,c2,c3;
int main()
{
	getline(cin,s);
	n=s.size();
	for(int i=0;i<n;i++) 
	{
		if(s[i]=='m'||s[i]=='M') c1++;
		if(s[i]=='s'||s[i]=='S') c2++;
		if(s[i]=='t'||s[i]=='T') c3++;
	}
	printf("%d %d %d",c1,c2,c3);
	return 0;
} 
```

---

## 作者：ZCJ888888 (赞：2)

# 思路

题目让我们在一个字符串中计算并输出字符串中 `M`，`S`，`T` 的个数，其实我们很简单就可以发现，只要做一个判断就可以了。

# 具体解题步骤

1. 定义，输入字符串与三个计数器。
2. 在循环里不断判断并让对应的计数器加加。
3. 输出答案。

具体代码如下：
```cpp
#include<bits/stdc++.h>//万能头大法
using namespace std;

int main(){
	string s;
	getline(cin,s);//字符串中含有空格
	int summ=0,sums=0,sumt=0;//对应的三个计数器
	for(int i=0;i<s.size();i++){//循环
		if(s[i]=='M' || s[i]=='m'){
			summ++;
		}
		if(s[i]=='S' || s[i]=='s'){
			sums++;
		}
		if(s[i]=='T' || s[i]=='t'){
			sumt++;
		}//如果是对应的字母就让计数器加加
	}
	cout<<summ<<" "<<sums<<" "<<sumt;//最后输出即可
	return 0;//养成好习惯
}
```

---

## 作者：Xiaonao_Dali (赞：2)

### 一，题目大意
给定一个字符串，且保证字符串长度 $\le10^5$，需要你进行在该字符串中查询 `M`，`S` 和 `T` 的字符数量，并以**空格隔开**。
### 二，易错提醒
1. 在本题中查询的 `M`，`S` 和 `T` 是**不区分大小写**的，所以他的小写形式也要判断出来。
2. 在本题中，字符串含有空格，在输入过程中，一般情况检测到空格就会停止读入，这时我们需要**假装读入空格**，使其能**继续读入**。
3. 读入字符串时后，遍历的时候要注意自己是从什么下标开始读入的，**避免出现遗漏**。
### 三，核心代码
我们根据题意得，不区分大小写，也就是 `M` 和 `m` 均视为同一种字符，与之对应的 `S` 和 `s` 以及 `T` 和 `t` 都要将他视为同一种字符。也就是说大小写**都要记录**。当然，我们只能因为不区分大小写假设他们是同一种字符，而在现实生活中是不成立的。下列是一段核心代码。
```cpp
	for(int i=0;i<n;i++){
		if(s[i]=='M'||s[i]=='m')
		ans++;
		if(s[i]=='S'||s[i]=='s')
		ans1++;
		if(s[i]=='T'||s[i]=='t')
		ans2++;
	}
```
### 四，正解
根据以上分析，我们即可得出一个正解代码，具体代码请参考如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	char s[100005];
	cin.getline(s,100005);
	int n=strlen(s);
	int ans=0,ans1=0,ans2=0;
	for(int i=0;i<n;i++){
		if(s[i]=='M'||s[i]=='m')
		ans++;
		if(s[i]=='S'||s[i]=='s')
		ans1++;
		if(s[i]=='T'||s[i]=='t')
		ans2++;
	}
	printf("%d %d %d",ans,ans1,ans2);
	return 0;
}
```

---

## 作者：Evan2000 (赞：1)

## 题意
给你一个字符串，让你分别求出这个字符串中字符 ```M```、```S``` 和 ```T``` 的数量，不区分大小写。
## 思路
因字符串中包含空格，所以需要使用 ```getline``` 函数读入整个字符串，然后遍历每一个字符，遇到给定字符后，将其相应的计数器加一，然后输出即可。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	getline(cin,s);
	int len=s.size();
	int ret=0;
	int sum=0;
	int ans=0;
	for(int i=0;i<len;i++)
	{
		if(s[i]=='M' || s[i]=='m')
		{
			ret++;
		}
		if(s[i]=='S' || s[i]=='s')
		{
			sum++;
		}
		if(s[i]=='T' || s[i]=='t')
		{
			ans++;
		}
	}
	printf("%d %d %d",ret,sum,ans);
	return 0;
}
```

---

## 作者：SXY83296647 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P12517)
首先来看题目，题目要求是分别输出输入的字符串中 `M`，`S` 和 `T` 的个数。我们就可以通过枚举字符串中的各个字符来计算求和，在此给出以下代码。
## AC Code
``` cpp
#include <iostream>
#include <cctype>
using namespace std;
int main()
{
    string a;
    getline(cin,a);//注意空格也是字符串的内容，需整行读入
    int m = 0, s = 0, t = 0;
    for (int i = 0;i < a.length();i++) {
        char lower = tolower(a[i]);//使用cctype的tolower()函数，将字符转换为小写形态，方便判断
        if (lower == 'm') m++;
        else if (lower == 's') s++;
        else if (lower == 't') t++;
    }
    cout << m << " " << s << " " << t << endl;
    return 0;
}
```

---

## 作者：PvbeLLN (赞：0)

## 题目大意

给定一行有空格的字符串，统计其中字符 `m`，`s` 和 `t` 的个数，不区分大小写。

## 解题思路

直接按照题意逐个字符判断统计即可。

读入一整行有空格的字符串可以用 `getline` 实现。

## 代码
```cpp
// Problem: P12517 「MSTOI-R1」MST Find
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12517
// Create Time: 2025-05-17 20:02:27

#include<iostream>
#include<cstring>
#include<cstdio>
#include<stack>
#include<queue>
#include<algorithm>
#include<cmath>
#include<vector>
//#include<unordered_map>
//#define map unordered_map
#ifdef ONLINE_JUDGE
#define getchar getchar_unlocked
#endif
using namespace std;
/*================*/

inline int read() {
	char c=getchar();int x=0,f=1;
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-48;
	return x*f;
}

#define r(a) (a)=read()

string ss;
int m,s,t;

signed main() {
	getline(cin,ss);
	for (auto c:ss) {
		if (c=='M'||c=='m') m++;
		if (c=='S'||c=='s') s++;
		if (c=='T'||c=='t') t++;  //朴实无华的判断
	}
	cout<<m<<" "<<s<<" "<<t<<"\n";
	return 0;
}
```

---

