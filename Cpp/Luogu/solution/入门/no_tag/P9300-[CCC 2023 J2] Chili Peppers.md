# [CCC 2023 J2] Chili Peppers

## 题目描述

Ron 正在用各种辣椒烹饪辣椒酱。

辣椒的辣度以斯科维尔辣度单位（SHU）来衡量。Ron 的辣椒酱目前一点都不辣，但每次 Ron 加入一个辣椒时，辣椒酱的总辣度就会增加该辣椒的 SHU 值。Ron 可用的辣椒的 SHU 值如下表所示：

| 辣椒名称 | 斯科维尔辣度单位 |
| :----------: | :----------: |
| Poblano | $1500$ |
| Mirasol | $6000$ |
| Serrano | $15500$ |
| Cayenne | $40000$ |
| Thai | $75000$ |
| Habanero | $125000$ |

你的任务是确定 Ron 加完辣椒后，他的辣椒酱的总辣度。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
Poblano
Cayenne
Thai
Poblano```

### 输出

```
118000```

# 题解

## 作者：fkcufk (赞：5)


[题目传送门](https://www.luogu.com.cn/problem/P9300)

题目解析：

本题考查点：`if` 的使用。

我们只需判断第一个字母即可。

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	int ans=0;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		if(s[0]=='P') ans+=1500;
		else if(s[0]=='M') ans+=6000;
		else if(s[0]=='S') ans+=15500;
		else if(s[0]=='C') ans+=40000;
		else if(s[0]=='T') ans+=75000;
		else ans+=125000;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Lovely_Elaina (赞：2)

逐个输入，用 `if` 判断辣度，然后累加到变量 $cnt$ 里面。

注意大小写。

```cpp
#include <iostream>
// #include <bits/stdc++.h>
// #define abs(a) (a<0?-a:a)
// #define max(a,b) (a>b?a:b)
// #define min(a,b) (a<b?a:b)
// #define int __int128
// #define int long long
// #define int unsigned int
#define endl '\n'
using namespace std;

int n,cnt;
string s;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    
    cin >> n;
    while(n--){
        cin >> s;
        if(s == "Poblano"){
            cnt += 1500;
        }else if(s == "Mirasol"){
            cnt += 6000;
        }else if(s == "Serrano"){
            cnt += 15500;
        }else if(s == "Cayenne"){
            cnt += 40000;
        }else if(s == "Thai"){
            cnt += 75000;
        }else if(s == "Habanero"){
            cnt += 125000;
        }
    }
    
    cout << cnt << endl;
    return 0;
}
```

---

## 作者：Hughpig (赞：2)

提供一个不一样的做法，个人觉得更加简单。

此题我使用了 `std::map`，通过字符串与元素的映射通过此题。`std::map` 的具体用法可以参考[此处](https://zhuanlan.zhihu.com/p/127860466)，这里不再赘述。

思路：提前处理每种辣椒的辣度，每次输入字符串，直接累加答案即可。

代码：

```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
map<string,int> mp;//定义一个把 string 映射到 int 的 map

int main()
{
    mp["Poblano"]=1500;//预处理辣度值
    mp["Mirasol"]=6000;
    mp["Serrano"]=15500;
    mp["Cayenne"]=40000;
    mp["Thai"]=75000;
    mp["Habanero"]=125000;
    int n,ans=0;//定义变量，注意 ans 要赋值为 0
    cin>>n;
    while(n--)
    {
    	string s;
    	cin>>s;
    	ans+=mp[s];//计算
	}
	cout<<ans;//输出
	return 0;
}
```

---

## 作者：Leaves_xw (赞：1)

**思路：**

每一次读入时判断是哪种辣椒，之后在 $ans$ 中增加它对应的辣度，最后输出 $ans$ 即可。

由于辣椒名称的首字母不同，所以只需要判断首字母即可。

**主要代码：**

```
scanf("%d",&n);
while(n)
{
    n-=1;
    scanf("%s",s);
    if(s[0]=='P')ans+=1500;
    else if(s[0]=='M')ans+=6000;
    else if(s[0]=='S')ans+=15500;
    else if(s[0]=='C')ans+=40000;
    else if(s[0]=='T')ans+=75000;
    else if(s[0]=='H')ans+=125000;
}
printf("%d\n",ans);
```

---

## 作者：maomao233 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9300)

### 分析

逐个输入 $n$ 个字符串，用分支语句判断输入的是哪个辣椒，再把其对应的辣度累加到计数变量 $ans$ 里即可。

注意到每个辣椒名的首字母各不相同，直接判断首字母更方便。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int ans=0;
	while(n--)
	{
		string s;
		cin>>s;
		if(s[0]=='P')
		{
			ans+=1500;
		}
		else if(s[0]=='M')
		{
			ans+=6000;
		}
		else if(s[0]=='S')
		{
			ans+=15500;
		}
		else if(s[0]=='C')
		{
			ans+=40000;
		}
		else if(s[0]=='T')
		{
			ans+=75000;
		}
		else
		{
			ans+=125000;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Loser_Syx (赞：1)

## 思路

一道 `if` 的练习题。

只需根据输入来判断其对应的值，最后相加总和即可，注意输入时首字母是大写的。

## 代码

```cpp
//Author: Saint_ying_xtf
//help me,qwq
//Timelimit: 1000ms
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
#define int long long
#define f(W, X, Y, Z) for(int W = X; W <= Y; W += Z)
#define F(W, X, Y, Z) for(int W = X; W >= Y; W -= Z)
#define debug puts("QAQ")
namespace fastIO{
	inline int read(){
		int x = 0, s = 1;
		char c = getchar();
		while(c < '0' || c > '9'){
			if(c == '-') s = -1;
			c = getchar();
		}
		while(c >= '0' && c <= '9'){
			x = (x << 3) + (x << 1) + (c ^ '0');
			c = getchar();
		}
		return x * s;
	}
	inline void Write(int x){
		if(x < 0){
			putchar('-');
			x = -x;
		}
		if(x > 9) Write(x / 10);
		putchar(x % 10 + '0');
	}
	inline void write(int x, char c){
		Write(x);
		putchar(c);
	}
}
using namespace fastIO;
namespace SyxQwQ{
	inline int qwq(){
		return 0;
	}
	inline int main(){
		//todo
		int n = read(), ans = 0;
		while(n--){
			string s;
			cin >> s;
			if(s == "Thai") ans += 75000;
			else if(s == "Habanero") ans += 125000;
			else if(s == "Poblano") ans += 1500;
			else if(s == "Mirasol") ans += 6000;
			else if(s == "Serrano") ans += 15500;
			else ans += 40000;
		}
		write(ans, '\n');
		return qwq();
	}
}
signed main(){
	SyxQwQ::main();
	return 0;
}
```

---

## 作者：Jasoncwx (赞：1)

## 题目思路
按照题意模拟，定义变量 $ans$ 表示答案。

对于每次输入的字符串 $t$：
- $t=$ `Poblano`，$ans+1500$。
- $t=$ `Mirasol`，$ans+6000$。
- $t=$ `Serrano`，$ans+15500$。
- $t=$ `Cayenne`，$ans+40000$。
- $t=$ `Thai`，$ans+75000$。
- $t=$ `Habanero`，$ans+125000$。

最后输出 $ans$ 即可。

## 代码
```cpp
//By Jasoncwx
#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,sum=0;
	cin>>n;
	while(n--){
		string t;cin>>t;
		if(t=="Poblano")sum+=1500;
		if(t=="Mirasol")sum+=6000;
		if(t=="Serrano")sum+=15500;
		if(t=="Cayenne")sum+=40000;
		if(t=="Thai")sum+=75000;
		if(t=="Habanero")sum+=125000;
	}
	cout<<sum;
    return 0;
}
```

---

## 作者：prt_xcdh (赞：1)

# 思路

这道题就是一个输入 `n` 次的字符串，如果满足要求的就存储到 `sum` 里 主要考察的是 `if` 语句的应用，需要注意的是每个字符串的大小写。

# # CODE

```c++
#include<bits/stdc++.h>
using namespace std;
string s;
int main() {
	int n,sum=0;
	cin >> n;
	while(n--){
		cin >> s;
		if(s == "Poblano")sum+=1500;
		else if(s=="Mirasol")sum+=6000;
		else if(s=="Serrano")sum+=15500;
		else if(s=="Cayenne")sum+=40000;
		else if(s=="Thai")sum+=75000;
		else if(s=="Habanero")sum+=125000;
	}
	cout << sum;
    return 0;
}

```



---

## 作者：qwertim (赞：0)

一道入门题。

逐个输入每个辣椒的名字，用 ```if``` 判断是什么辣椒，最后用一个变量加上所有辣椒的辣度即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
string s;
int main(){
	cin>>n;
	while(n--){
		cin>>s;
		if(s=="Poblano")ans+=1500;
		else if(s=="Mirasol")ans+=6000;
		else if(s=="Serrano")ans+=15500;
		else if(s=="Cayenne")ans+=40000;
		else if(s=="Thai")ans+=75000;
		else ans+=125000;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Sun_Email (赞：0)

虽然是一道简单题，不过也有要注意的地方。

首先是要注意大小写，其次，为了省~~一点点~~码量，注意到各个辣椒的首字母不同，可以只比较首字母来确定各个辣椒辣度。

最后将每个辣椒辣度累加即可。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=0;
char s[8];
int main(){
	scanf("%d",&n);
	while(n--){
		scanf("%s",s);
		if(s[0]=='P'){
			ans+=1500;
		}
		else if(s[0]=='M'){
			ans+=6000;
		}
		else if(s[0]=='S'){
			ans+=15500;
		}
		else if(s[0]=='C'){
			ans+=40000;
		}
		else if(s[0]=='T'){
			ans+=75000;
		}
		else if(s[0]=='H'){
			ans+=125000;
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

