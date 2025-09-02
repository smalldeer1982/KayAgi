# Last Year's Substring

## 题目描述

本题给你一个字符串，问删去其中一个可以为空的字串后，能否使其变为"$2020$"。

## 样例 #1

### 输入

```
6
8
20192020
8
22019020
4
2020
5
20002
6
729040
6
200200```

### 输出

```
YES
YES
YES
NO
NO
NO```

# 题解

## 作者：立风yu (赞：10)

~~本蒟蒻来水题解了~~

题意：输入一个字符串，判断在这个字符串中是否能一次删去一部分字符之后构成 $"2020"$

其实我刚开始一直没能理解到底要怎么做……因为我看到之后想到了很多种情况

1. $2020……$
1. $202……0$
1. $20……20$
1. $2……020$
1. $……2020$
1. $…2020…$

我一直没做出来是因为我在纠结第六种情况，然后我看了一眼题，是只删一次……好的是我考虑过多，所以只有上面的前五种情况

那问题不大，每种情况都特判就行了（特判大法好啊！）

上代码：

```cpp
#include <iostream>
#include <cstring>
using namespace std;
string a;
int n,m;
int main(){
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>m;
        cin>>a;
        if (a[0]=='2'&&a[1]=='0'&&a[2]=='2'&&a[3]=='0'){
            cout<<"YES"<<endl;
            continue;
        }
        else if (a[0]=='2'&&a[1]=='0'&&a[2]=='2'&&a[m-1]=='0'){
            cout<<"YES"<<endl;
            continue;
        }
        else if (a[0]=='2'&&a[1]=='0'&&a[m-2]=='2'&&a[m-1]=='0'){
            cout<<"YES"<<endl;
            continue;
        }
        else if (a[0]=='2'&&a[m-3]=='0'&&a[m-2]=='2'&&a[m-1]=='0'){
            cout<<"YES"<<endl;
            continue;
        }
        else if (a[m-4]=='2'&&a[m-3]=='0'&&a[m-2]=='2'&&a[m-1]=='0'){
            cout<<"YES"<<endl;
            continue;
        }
        else
        cout<<"NO"<<endl;
    }
    return 0;
}
```


---

## 作者：きりと (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1462B)

## 题目大意：

给定一个字符串，现可以删除此字符串的一段连续的字串，问一次删除后能否将原字符串变成$2020$。

## 解题思路：

因为只能删一次，所以有三种情况：

- 最左边有字串$2020$
- 最右边有字串$2020$
- 删去中间的一部分字串以后，两边剩余的字符正好组成$2020$

## 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		string s;
		cin>>s;
		if(s[0]=='2'&&s[1]=='0'&&s[2]=='2'&&s[3]=='0')
		{
			cout<<"YES"<<endl;
			continue;
		}
		if(s[0]=='2'&&s[1]=='0'&&s[2]=='2'&&s[n-1]=='0')
		{
			cout<<"YES"<<endl;
			continue;
		}
		if(s[0]=='2'&&s[1]=='0'&&s[n-2]=='2'&&s[n-1]=='0')
		{
			cout<<"YES"<<endl;
			continue;
		}
		if(s[0]=='2'&&s[n-3]=='0'&&s[n-2]=='2'&&s[n-1]=='0')
		{
			cout<<"YES"<<endl;
			continue;
		}
		if(s[n-4]=='2'&&s[n-3]=='0'&&s[n-2]=='2'&&s[n-1]=='0')
		{
			cout<<"YES"<<endl;
			continue;
		}
		cout<<"NO"<<endl;
	}
	return 0;
}
```

---

## 作者：XiaU (赞：3)

# 题解

这题说实话不难，重点是能不能想到这个点。

首先，我们想一想，要想直接把一个字符串去掉一段连续的字符串后只剩2020，那么，应该只有以下几种情况：

1. $2020……$

2. $202……0$

3. $20……20$

4. $2……020$

5. $……2020$

所以我们就直接进行特判，然后输出就可以了

# Code

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

char s[207];
int t, n;

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        cin >> s;
        if(s[0] == '2' && s[1] == '0' && s[2] == '2' && s[3] == '0')
        {
            printf("YES\n");
            continue;
        }
        if(s[n - 4] == '2' && s[n - 3] == '0' && s[n - 2] == '2' && s[n - 1] == '0')
        {
            printf("YES\n");
            continue;
        }
        if(s[0] == '2' && s[n - 3] == '0' && s[n - 2] == '2' && s[n - 1] == '0')
        {
            printf("YES\n");
            continue;
        }
        if(s[0] == '2' && s[1] == '0' && s[n - 2] == '2' && s[n - 1] == '0')
        {
            printf("YES\n");
            continue;
        }
        if(s[0] == '2' && s[1] == '0' && s[2] == '2' && s[n - 1] == '0')
        {
            printf("YES\n");
            continue;
        }
        printf("NO\n");
    }
    return 0;
}
```

---

## 作者：Accteped (赞：2)

我刚看到此题时，看到样例，当时就慌了，想了很久但~~一想红题不会是这样的难度~~再仔细地又看了几遍题目，发现了这个规律:


只有这几种情况
我就以长度为8来举例，并且不管长度为什么，都符合这个规律

### 1.2020……

### 2.202……0

### 3.20……20

### 4.2……020

### 5.……2020

### 6.…2020…

所以，我们只需用几个if对字符串进行判断即可

## AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int t,n;//几组数据和字符串长度 
int main(){
	cin>>t;//t组数据
	while(t--){
		cin>>n>>s;//输入长度和字符串
		if(s[0]=='2'&&s[1]=='0'&&s[2]=='2'&&s[3]=='0'){
			cout<<"YES"<<endl;continue;
		}
		if(s[0]=='2'&&s[1]=='0'&&s[2]=='2'&&s[n-1]=='0'){
			cout<<"YES"<<endl;continue;
		}
		if(s[0]=='2'&&s[1]=='0'&&s[n-2]=='2'&&s[n-1]=='0'){
			cout<<"YES"<<endl;continue;
		}
		if(s[0]=='2'&&s[n-3]=='0'&&s[n-2]=='2'&&s[n-1]=='0'){
			cout<<"YES"<<endl;continue;
		}
		if(s[n-4]=='2'&&s[n-3]=='0'&&s[n-2]=='2'&&s[n-1]=='0'){
			cout<<"YES"<<endl;continue;
		}//具体思路请看上方 
		cout<<"NO"<<endl;//如果都不满足就输出NO 
	} 
	return 0;//完结撒花 
}
```

~~求赞~~

## 禁止抄袭!

---

## 作者：_caiji_ (赞：2)

### 题目大意

给定一个字符串，问删除其中一段连续字符后，能否把它变成字符串"$2020$"？

### 题目思路

暴力判断就可以了。我们假设 $n=7$，列出输出"$\text{YES}$"的情况：

- "$2020\text{xxx}$"
- "$202\text{xxx}0$"
- "$20\text{xxx}20$"
- "$2\text{xxx}020$"
- "$\text{xxx}2020$"

显然，除了这些情况外，直接输出"$\text{NO}$"。

### 代码实现
```cpp
#include<cstdio>
#define YES printf("YES\n")
#define NO printf("NO\n")//合理的宏定义能使代码更好看
using namespace std;
char a[210];//4<=n<=200
int T,n;
int main(){
    scanf("%d",&T);
    while(T--){//这种写法比for(int i=0;i<T;i++)更简洁
        scanf("%d\n%s",&n,a+1);//写a+1可以让输入的字符串下标从1开始
        if(a[1]=='2'&&a[2]=='0'&&a[3]=='2'&&a[4]=='0') YES;
        else if(a[1]=='2'&&a[2]=='0'&&a[3]=='2'&&a[n]=='0') YES;
        else if(a[1]=='2'&&a[2]=='0'&&a[n-1]=='2'&&a[n]=='0') YES;
        else if(a[1]=='2'&&a[n-2]=='0'&&a[n-1]=='2'&&a[n]=='0') YES;
        else if(a[n-3]=='2'&&a[n-2]=='0'&&a[n-1]=='2'&&a[n]=='0') YES;
        else NO;//暴力判断
    }
    return 0;
}
```

---

## 作者：几时明月 (赞：1)

题目其实就是问剩下的字符里有没有2020.
### 注意题目，因为只能删一次所以有三种情况
1.左边有2020；

2.右边有2020；

3.中间凑成了一个2020。

好了，知道这几种情况，也就简单多了。

#### 照样定义一个
```cpp
string m;
```
#### 再来判断是否能凑成2020
```cpp
	if(m[0]=='2'&&m[1]=='0'&&m[2]=='2'&&m[3]=='0')//n为字符串的长度
	{
		cout<<"YES"<<endl;
		continue;
	}
	if(m[0]=='2'&&m[1]=='0'&&m[2]=='2'&&m[n-1]=='0')
	{
		cout<<"YES"<<endl;
		continue;
	}
	if(m[0]=='2'&&m[1]=='0'&&m[n-2]=='2'&&m[n-1]=='0')
	{
		cout<<"YES"<<endl;
		continue;
	}
	if(m[0]=='2'&&m[n-3]=='0'&&m[n-2]=='2'&&m[n-1]=='0')
	{
		cout<<"YES"<<endl;
		continue;
	}
	if(m[n-4]=='2'&&m[n-3]=='0'&&m[n-2]=='2'&&m[n-1]=='0')
	{
		cout<<"YES"<<endl;
		continue;
	}
		cout<<"NO"<<endl;//这里如果全都不是，那就会直接输出NO。
	}
```
#### 核心代码已给出，制作不易，感谢。

---

## 作者：happybob (赞：1)

来个正则表达式做法，其实也是每个判断，因为只有  $5$ 种可行方案，不用写那么多 `if`。

更多关于正则表达式的使用请看我的[题解](https://www.luogu.com.cn/blog/332914/ti-xie-at1481-post)。

代码：

```cpp
#include <iostream>
#include <string>
#include <regex>
using namespace std;

static regex reg("\\w*2020"), reg2("202\\w*0"), reg3("20\\w*20"), reg4("2\\w*020"), reg5("2020\\w*");

int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (register int i = 1; i <= n; i++)
	{
		string s;
		cin >> s >> s;
		if (regex_match(s, reg) || regex_match(s, reg2) || regex_match(s, reg3) || regex_match(s, reg4) || regex_match(s, reg5))
		{
			cout << "YES\n";
		}
		else
		{
			cout << "NO\n";
		}
	}
	//system("pause");
	return 0;
}
```


---

## 作者：UperFicial (赞：1)

# 模拟题

### 前言

闲来无事发篇题解，由于 $whk$ 原因没打 CF/kk

字符串基础题，但用了个暴力的做法，$O(tn)$。

题目链接：[$\text{Link}$](https://www.luogu.com.cn/problem/CF1462B)

### 题意简述

给定长度为 $n$ 的字符串 $s$，问能否在删掉一个可空的子串后，剩下的字符串构成 `2020`。

### 题目分析

一开始的思路就是暴力枚举删掉的子串的两个端点 $i,j$，然后判断剩下的字符串是否合法，复杂度 $O(tn^3)$，枚举 $O(n^2)$，判合法 $O(n)$。

在 $n\le 300$ 数据下可以过，但是还可以更优。

要使得剩下的字符串是 `2020`，那么删去的子串的长度必须是 $n-4$，因为要保留 $4$ 个字符，而总的字符数量是 $n$。

并且子串是连续的，所以就可以抽象形成一个长度为 $n-4$ 的窗口，从左到右移动，这个窗口里边的便是要删去的字符串，而没有被盖住的则是需要判断合法的字符串，实现就很简单了。

[$code$](https://paste.ubuntu.com/p/NtcyXXDP34/)

时间复杂度：$O(tn)$，窗口的滑动需要 $O(n)$，剩下的需要判断合法的字符只有 $4$ 个，省略系数，得到 $O(tn)$。

空间复杂度：$O(n)$。

[$AC$ 记录](https://www.luogu.com.cn/record/44189956)

$$\texttt{The End.by UF}$$

---

## 作者：_OJF_ (赞：1)

## 此题大意：
给定一个长度为$n$的字符串$s$，删掉其中第$i$个到第$j$个字符$(1 \le i < j \le n)$，求剩下有没有可能组成“2020“

## 做法
太暴力了，首先，只能留下4个字符，并且这四个字符都是在给定字符串两端的，所以，我们只需要枚举一下以下是否组成“2020”：

$s_1,s_2,s_3,s_4$

$s_1,s_2,s_3,s_n$

$s_1,s_2,s_{n - 1},s_{n}$

$s_1,s_{n - 2},s_{n - 1},s_{n}$

$s_{n - 3},s_{n - 2},s_{n - 1},s_{n}$

现在就可以上代码了
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n;
char c[205];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		if(n < 4){
			cout<<"NO"<<endl;
			continue;
		}
		for(int i = 1;i <= n;i++)
			cin>>c[i];
		if(c[n - 3] == '2' && c[n - 2] == '0' && c[n - 1] == '2' && c[n] == '0'){
			cout<<"YES"<<endl;
			continue;
		}
		if(c[1] == '2' && c[n - 2] == '0' && c[n - 1] == '2' && c[n] == '0'){
			cout<<"YES"<<endl;
			continue;
		}
		if(c[1] == '2' && c[2] == '0' && c[n - 1] == '2' && c[n] == '0'){
			cout<<"YES"<<endl;
			continue;
		}
		if(c[1] == '2' && c[2] == '0' && c[3] == '2' && c[n] == '0'){
			cout<<"YES"<<endl;
			continue;
		}
		if(c[1] == '2' && c[2] == '0' && c[3] == '2' && c[4] == '0'){
			cout<<"YES"<<endl;
			continue;
		}
		cout<<"NO"<<endl;
	}
	return 0;
}
```


---

## 作者：Iron_Heart (赞：0)

## 思路

由于规定了只能删除**一个子串**，所以只有五种情况是输出 `YES` 的：

1. `2020xxx`
2. `2xxx020`
3. `20xxx20`
4. `202xxx0`
5. `xxx2020`

因此对于每种情况特判一下就行了，如果五种情况都不满足则输出 `YES`。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n;
string s;

int main()
{
    ios::sync_with_stdio(0);
    cin >> t;
    while (t--)
    {
        cin >> n >> s;
        if (s.substr(0, 4) == "2020") cout << "YES\n";
        else if (s[0] == '2' && s[n - 3] == '0' && s[n - 2] == '2' && s[n - 1] == '0') cout << "YES\n";
        else if (s.substr(0, 2) == "20" && s.substr(n - 2, 2) == "20") cout << "YES\n";
        else if (s.substr(0, 3) == "202" && s[n - 1] == '0') cout << "YES\n";
        else if (s.substr(n - 4, 4) == "2020") cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
```


---

## 作者：expnoi (赞：0)

暴力判断每种情况即可，但是思维难度却略难。

每种情况是2020在最前面，2020在最后面，然后是2020中间分隔开来的(也就是删中间的一块)。

Code:
```cpp
#include<bits/stdc++.h>
#define yes cout<<"YES\n";
#define no cout<<"NO\n"; 
#define con continue;
#define _ using 
#define w while
#define __ namespace 
#define ___ std;
_ __ ___
int T,n;
char a[1001];
int main()
{
	cin>>T;
	w(T--)
	{
		cin>>n;
		if(n<4)//不可能有2020 
		{
			no
			con
		}
		cin>>a;
		if((a[0]=='2'&&a[1]=='0'&&a[2]=='2'&&a[3]=='0')||(a[n-4]=='2'&&a[n-3]=='0'&&a[n-2]=='2'&&a[n-1]=='0'))
		{
			yes
			con
		}
		if(a[0]=='2'&&a[1]=='0'&&a[2]=='2'&&a[n-1]=='0')
		{
			yes
			con
		}
		if(a[0]=='2'&&a[1]=='0'&&a[n-2]=='2'&&a[n-1]=='0')
		{
			yes
			con
		}
		if(a[0]=='2'&&a[n-3]=='0'&&a[n-2]=='2'&&a[n-1]=='0')
		{
			yes
			con
		}
		if(a[n-4]=='2'&&a[n-3]=='0'&&a[n-2]=='2'&&a[n-1]=='0')
		{
			yes
			con
		}
		no
	}
}
```

---

