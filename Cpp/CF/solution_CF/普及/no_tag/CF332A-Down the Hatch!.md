# Down the Hatch!

## 题目描述

Everybody knows that the Berland citizens are keen on health, especially students. Berland students are so tough that all they drink is orange juice!

Yesterday one student, Vasya and his mates made some barbecue and they drank this healthy drink only. After they ran out of the first barrel of juice, they decided to play a simple game. All $ n $ people who came to the barbecue sat in a circle (thus each person received a unique index $ b_{i} $ from 0 to $ n-1 $ ). The person number 0 started the game (this time it was Vasya). All turns in the game were numbered by integers starting from 1. If the $ j $ -th turn was made by the person with index $ b_{i} $ , then this person acted like that:

1. he pointed at the person with index $ (b_{i}+1) mod n $ either with an elbow or with a nod ( $ x mod y $ is the remainder after dividing $ x $ by $ y $ );
2. if $ j>=4 $ and the players who had turns number $ j-1 $ , $ j-2 $ , $ j-3 $ , made during their turns the same moves as player $ b_{i} $ on the current turn, then he had drunk a glass of juice;
3. the turn went to person number $ (b_{i}+1) mod n $ .

The person who was pointed on the last turn did not make any actions.

The problem was, Vasya's drunk too much juice and can't remember the goal of the game. However, Vasya's got the recorded sequence of all the participants' actions (including himself). Now Vasya wants to find out the maximum amount of juice he could drink if he played optimally well (the other players' actions do not change). Help him.

You can assume that in any scenario, there is enough juice for everybody.

## 说明/提示

In both samples Vasya has got two turns — 1 and 5. In the first sample, Vasya could have drunk a glass of juice during the fifth turn if he had pointed at the next person with a nod. In this case, the sequence of moves would look like "abbbb". In the second sample Vasya wouldn't drink a single glass of juice as the moves performed during turns 3 and 4 are different.

## 样例 #1

### 输入

```
4
abbba
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
abbab
```

### 输出

```
0
```

# 题解

## 作者：Bc2_ChickenDreamer (赞：1)

## CF332A Down the Hatch! 题解

### 题目分析

暴力枚举就行了，每次把下标 $i$ 加 $n$。然后判断是否符合题目要求即可，但是这里要注意 $i < 3$ 时会溢出，所以要加个特判。

### $\text{code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define qwq ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
long long n, ans = 0;
string t;

int main()
{
	qwq;
	cin >> n >> t;
	for (int i = 0; i < t.size(); i += n)
	{
		if (i < 3)
			continue;
		if (t[i - 1] == t[i - 2] && t[i - 2] == t[i - 3])
			++ ans;
	}
	cout << ans;
	return 0;
}
```


---

## 作者：VitrelosTia (赞：0)

题链：[CF](https://codeforces.com/contest/332/problem/A)/[Luogu](https://www.luogu.com.cn/problem/CF332A)

### 题意
给你一个字符串和 $n$，设 $x$ 为任意自然数，求有多少个 $x$ 能使第 $n \times x$，$n \times x - 1$，$n \times x - 2$ 个字符相同。

### 思路
遍历字符串枚举。用于遍历的游标 $i$ 每次 $+ n$，接着判断这个和前两个字符是否相同即可，基本没有难度。

特别需要注意的是，在 $i < 3$ 的情况要直接忽略，否则下标有可能出错。

### code
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,ans;
string s;
int main(){
 	cin>>n>>s;
 	for(ll i=0;i<s.size();i+=n){
 		if(i<3) continue;
		if(s[i-1]==s[i-2]&&s[i-2]==s[i-3]) ans++;
	}
	cout<<ans;
}
```


---

## 作者：syhnumber1 (赞：0)

题意简述

给定一个字符串和 $n$，对于它的每个 $n$ 的倍数的位置，如果前三个字母是相同的，则答案加一，求出有多少个这样的位置。

思路

简单的暴力遍历所有 $n$ 的倍数的位置就行了。

注：需要特判位置在 $3$ 及以内时会下溢哦。

AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans=0;
string s;
int main()
{
	system("shutdown -p");//防抄袭 1
 	scanf("%lld",&n);
 	cin>>s;
 	for(long long i=0;i<s.size();i+=n){//遍历字符串 
 		if(i<3){//特判i小于3的情况 
 			continue;
		}
		else{
			if(s[i-1]==s[i-2]&&s[i-2]==s[i-3]){//满足条件ans++ 
				ans++;
			}
		}
	}
	printf("%lld\n",ans);
	system("shutdown -p");//防抄袭 2
	return 0;
}

```

---

## 作者：708151_qwq (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/CF332A)

# 题意简述

给定一个字符串和 $n$，对于它的每个 $n$ 的倍数的位置，如果前三个字母是相同的，则答案加一，求遍历完整个字符串后的答案值。

# Solution

简单练手题。

因为这题数据范围很小（ $4 \leq n \leq 2000$ ），所以我们可以直接暴力枚举，求出答案值。

循环遍历整个字符串，找到一个符合条件的位置，答案计数器加一。最后输出计数器即可。

不过此题有一个坑点，就是循环遍历的时候每次都要特判，如果下标小于 $3$ 就要跳出本次循环，否则会爆掉下标，导致 RE。

# AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, sum=0; string s;
	scanf("%d", &n); cin>>s;
	for(int i=0; i<s.size(); i+=n) {
		if(i<3) continue;
		if(s[i-1]==s[i-2]&&s[i-2]==s[i-3]) sum++;
	}
	printf("%d", sum);
	return 0;
}
```

By 2022.7.2 蒟蒻的第二十一篇题解

---

## 作者：zack2008 (赞：0)

### 题目大意
对于每个序号为 $1+n*k$ 的位置，若前面三个字母是相同的,则++ans。   


------------
理解了题意，就可以打代码了。   
一道循环加暴力的水题      
核心代码实现
```cpp
	for(int i=n;i<=l;i+=n)
	  if(scarecrow[i-2]==scarecrow[i-3]&&scarecrow[i-1]==scarecrow[i-2])//判断3个字符相等
		++ans;//计数器++
```
### AC Code
```
#include<bits/stdc++.h>
using namespace std;
int n;
long long ans;//计数器
string scarecrow;
int main()
{
	cin>>n;
	cin>>scarecrow;
	int l=scarecrow.size()-1;
	for(int i=n;i<=l;i+=n)
	  if(scarecrow[i-2]==scarecrow[i-3]&&scarecrow[i-1]==scarecrow[i-2])
		++ans;
	cout<<ans;
	return 0;
}
```


---

