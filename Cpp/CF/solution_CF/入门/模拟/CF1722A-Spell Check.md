# Spell Check

## 题目描述

输入一个字符串，请判断这个字符串是不是字符串 `Timur` 的一种排列。

例如：`Timur` ，`miurT` ，`Trumi` ，`mriTu` 都是正确的排列。

**注意：正确的排列必须包含大写的T和小写的其他字母。**

---

## 说明/提示

$ 1 \le t \le 10^3 $ , $1 \le n \le 10$。

Translate By @Andy_L

## 样例 #1

### 输入

```
10
5
Timur
5
miurT
5
Trumi
5
mriTu
5
timur
4
Timr
6
Timuur
10
codeforces
10
TimurTimur
5
TIMUR```

### 输出

```
YES
YES
YES
YES
NO
NO
NO
NO
NO
NO```

# 题解

## 作者：zhang_kevin (赞：14)

[题目传送门](https://codeforces.com/problemset/problem/1722/A)

# Content

判断字符串是否由 $\verb!T,i,m,u,r!$ 组成。

# Solution

我们可以定义一个标准字符串，然后用 $\verb!sort!$ 进行排序，接着对每一个输入的字符串进行 $\verb!sort!$ 排序，并判断是否等于标准字符串即可。
 
# Code

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main() {
    int n;
    cin >> n;
    string StandardString = "Timur";
    sort(StandardString.begin(), StandardString.end());
    while(n--){
        int m;
        cin >> m;
        string s;
        cin >> s;
        sort(s.begin(), s.end());
        cout << (s==StandardString?"YES":"NO") << endl;
    }
    return 0;
}
```


---

## 作者：zeekliu (赞：2)

【题意简述】：给定一个字符串与它的长度，判断它是否为 ```Timur``` 的排列。

显然，如果如果长度就不是 $ 5 $，那一定不可能，输出 ```NO```。

那么当长度是 $ 5 $，直接循环判断即可，**注意清零！**。

```cpp
//CF1722A 22-09-01
#include <bits/stdc++.h>
using namespace std;

int main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int _; cin>>_;
	while (_--)
	{
		int n; cin>>n;
		string s; cin>>s;
		if (n!=5) cout<<"NO"<<endl;
		else 
		{
			int _t=0,_i=0,_m=0,_u=0,_r=0; //注意清零！
			for (int i=0;i<=4;i++)
			{
				if (s[i]=='T') _t++;
				if (s[i]=='i') _i++;
				if (s[i]=='m') _m++;
				if (s[i]=='u') _u++;
				if (s[i]=='r') _r++;
			}
			if (_t && _i && _m && _u && _r) cout<<"YES"<<endl; // 如果每个字符都有，在长度为 5 的情况下一定正确
			else cout<<"NO"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：__Allen_123__ (赞：1)

## 题目分析

这个题目中，我们要判断字符串 $s$ 是否是 `Timur` 的一种正确排列，那么我们就要判断这五个字符中每个字符出现了多少次。

这题很简单，但是有些人会用这种错误的方法作答：统计这五个字符的出现次数之和，全部加起来，如果和等于 5，那么就输出 `YES`。这种方法遇到 `Timura` 这种的 Hack 数据就会输出错误。

那么，这题我们应该怎么作答呢？

为了应对这种数据，我们应该清楚它应该满足哪些条件：

1. 字符串的长度为 5。这个是最必要的，因为它的合法排列的长度必须为 5。

2. 除了 `T`、`i`、`m`、`u`、`r` 这五种字符，没有其他字符。

3. 这五种字符各出现一次。

那么，我们就可以想到一个方法：

1. 输入字符串后，如果输入的长度 $n$ 不为 5，那么直接输出 `NO`。

2. 遍历整个字符串，用 5 个计数器或者一个长度为 5 的数组存储 `T`、`i`、`m`、`u`、`r` 的出现次数。

3. 如果这五个字符的出现次数均为 1，那么输出 `YES`，否则输出 `NO`。

---

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a1, a2, a3, a4, a5; // 定义题目所需变量和计数器
string s;
int main(){
	scanf("%d", &t);
	for(int i = 0;i < t;i++){
		cin >> n >> s;
		a1 = 0;
		a2 = 0;
		a3 = 0;
		a4 = 0;
		a5 = 0; // 计数器归零
		if(n != 5){ // 判断条件 1
			printf("NO\n");
			continue;
		}
		for(int j = 0;j < n;j++){ // 遍历整个字符串 s，并计算这 5 个字符的出现次数
			if(s[j] == 'T'){
				a1++;
			}
			else if(s[j] == 'i'){
				a2++;
			}
			else if(s[j] == 'm'){
				a3++;
			}
			else if(s[j] == 'u'){
				a4++;
			}
			else if(s[j] == 'r'){
				a5++;
			}
		}
		if(a1 == 1 && a2 == 1 && a3 == 1 && a4 == 1 && a5 == 1){ // 判断条件 2、条件 3
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
	return 0;
}
```

---

## 作者：thh_loser (赞：0)

# CF1722A Spell Check题解

## 题目描述

给你一个字符串的长度和一个字符串，问这个字符串重新排列后能否组成 $\verb|Timur|$。

## 思路

首先考虑字符串的长度，如果长度不为 $5$ 那么肯定不行。如果长度为 $5$ 就逐个比对 $\verb|Timur|$ 的每一个字符在给出的字符串中是否存在。

## code

```cpp

#include<bits/stdc++.h>
using namespace std;
int t,n;
string s;
string ans="Timur";
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		cin>>s;
		if(n!=5){//如果长度不为5就肯定不行 
			printf("NO\n");
		}
		else{
			bool flag=0,sf=0;
			for(int i=0;i<5;i++){//逐个比对五个字符 
				flag=0;
				for(int j=0;j<5;j++){
					if(s[j]==ans[i]){//如果这个字符找到了 
						flag=1;
						break;
					}
				}
				if(!flag){//有一个字符没找到就肯定不行 
					printf("NO\n");
					sf=1;
					break;
				}
			}
			if(!sf){//全部匹配成功 
				printf("YES\n");
			}
		}
	}
	return 0;
} 


```


---

## 作者：Lantrol (赞：0)

两种做法。

注意到当且仅当字符串长度为 $5$ 时，才有可能是 `Timur` 的一种排列。如果输入字符串长度不是 $5$，就直接判掉。然后统计一下字符串中，这 $5$ 个字母是否全部出现。

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
	int n;string s;
	bool t=0,I=0,m=0,u=0,r=0;
	cin>>n>>s;
	if(n!=5){
		cout<<"NO"<<endl;
		return;
	}
	for(int i=0;i<n;i++){
		if(s[i]=='T'){
			t=1;
		}
		if(s[i]=='i'){
			I=1;
		}
		if(s[i]=='m'){
			m=1;
		}
		if(s[i]=='u'){
			u=1;
		}
		if(s[i]=='r'){
			r=1;
		}
	}
	if(t&I&m&u&r){
		cout<<"YES"<<endl;
	}
	else{
		cout<<"NO"<<endl;
	}
}

int main(){
	int t;
	cin>>t;
	while(t--){
	    solve();
	}
}

```

另外一种做法是读入字符串后，先排序，然后与**排序后的** `Timur` 进行比较。

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
	int n;
    string s,t="Timur";
	cin>>n>>s;
	if(n!=5){
		cout<<"NO"<<endl;
		return;
	}
	sort(s.begin(),s.end());
	sort(t.begin(),t.end());
	if(s==t){
		cout<<"YES"<<endl;
	}
	else{
		cout<<"NO"<<endl;
	}
}

int main(){
	int t;
	cin>>t;
	while(t--){
	    solve();
	}
}

```


---

