# Special Task

## 题目描述

Special Agent Smart Beaver works in a secret research department of ABBYY. He's been working there for a long time and is satisfied with his job, as it allows him to eat out in the best restaurants and order the most expensive and exotic wood types there.

The content special agent has got an important task: to get the latest research by British scientists on the English Language. These developments are encoded and stored in a large safe. The Beaver's teeth are strong enough, so the authorities assured that upon arriving at the place the beaver won't have any problems with opening the safe.

And he finishes his aspen sprig and leaves for this important task. Of course, the Beaver arrived at the location without any problems, but alas. He can't open the safe with his strong and big teeth. At this point, the Smart Beaver get a call from the headquarters and learns that opening the safe with the teeth is not necessary, as a reliable source has sent the following information: the safe code consists of digits and has no leading zeroes. There also is a special hint, which can be used to open the safe. The hint is string $ s $ with the following structure:

- if $ s_{i} $ = "?", then the digit that goes $ i $ -th in the safe code can be anything (between $ 0 $ to $ 9 $ , inclusively);
- if $ s_{i} $ is a digit (between $ 0 $ to $ 9 $ , inclusively), then it means that there is digit $ s_{i} $ on position $ i $ in code;
- if the string contains letters from "A" to "J", then all positions with the same letters must contain the same digits and the positions with distinct letters must contain distinct digits.
- The length of the safe code coincides with the length of the hint.

For example, hint "?JGJ9" has such matching safe code variants: "51919", "55959", "12329", "93539" and so on, and has wrong variants such as: "56669", "00111", "03539" and "13666".

After receiving such information, the authorities change the plan and ask the special agents to work quietly and gently and not to try to open the safe by mechanical means, and try to find the password using the given hint.

At a special agent school the Smart Beaver was the fastest in his platoon finding codes for such safes, but now he is not in that shape: the years take their toll ... Help him to determine the number of possible variants of the code to the safe, matching the given hint. After receiving this information, and knowing his own speed of entering codes, the Smart Beaver will be able to determine whether he will have time for tonight's show "Beavers are on the trail" on his favorite TV channel, or he should work for a sleepless night...

## 样例 #1

### 输入

```
AJ
```

### 输出

```
81
```

## 样例 #2

### 输入

```
1?AA
```

### 输出

```
100
```

# 题解

## 作者：辛丑九月 (赞：2)

## Analysis

建议评红。

对于这题的简单版本 $n \le 5$，答案的数量级为 $10^5$ 次，不会很大，所以可以用爆搜解决问题。

首先是枚举出每一种可能的序列，再与原序列进行比较。

比较的有以下几点：

- 开头不能是 $0$；
- 原文中为数字的位置必须和该数字相同；
- 原文中为同一个字母的对应数字必须相同；
- 原文中不为同一个字母的对应数字必须不同；
- 原文中为 `?` 可以不用考虑。

以上 $3,4$ 条可以用 $n^2$ 的做法暴力判断，总复杂度 $O(n^210^n)$，能过。

对于这题数量级大的做法可以[看这里](https://www.luogu.com.cn/blog/2021February/solution-cf316a2)。

## Code

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;

int n, res;
char s[7];
int a[7];

void dfs (int id) {
	if (id > n) {
		if (a[1] == 0) return ; // 开头不能是 0
		for (int i = 1; i <= n; i++) {
			if (isdigit (s[i]) && s[i] - '0' != a[i]) return ; // 是数字且不相符
			if (isupper (s[i])) // 是字母
				for (int j = i + 1; j <= n; j++) if (isupper (s[j])) {
					if (s[i] == s[j] && a[i] != a[j]) return ; // 相同字母对应不同数字
					if (s[i] != s[j] && a[i] == a[j]) return ; // 不同字母对应相同数字
				}
		}
		res++;
		return ;
	}
	for (int i = 0; i <= 9; i++) a[id] = i, dfs (id + 1);
	return ;
}

signed main () {
	cin >> (s + 1); n = strlen (s + 1);
	dfs (1); printf ("%lld\n", res);
	return 0;
}
```

---

## 作者：初雪_matt (赞：1)

## 思路

简单如[你](https://www.luogu.com.cn/problem/CF316A2)。

分两种情况讨论，显然数字我们是不需要讨论的。

情况分别为字母，问号与首字符。

- 当这是首字符时，如果其是字母与问号，对答案的贡献均为 $9$。

- 当该字符为字母时，对答案的贡献应为 $T\times(10-K)$，其中 $T$ 为该字符是否出现过，$K$ 为当前统计过了多少个不同的字符。

- 当该字符为问号时，必定对答案的贡献为 $10$。

注意在首字符情况下依然要统计 $T$ 与 $K$ 的值，这里我用映射处理 $T$ 的值。

## 代码

```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
int n,m;
string s;
map<char,int> mp;
int ans=1,k,l;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>s;
	for(int i=0;i<s.length();i++){
		if(s[i]=='?'){
			l++;//统计每个问号数量
			continue;
		}
		if(s[i]>='A'&&s[i]<='J') mp[s[i]]++;//处理字符数量
	}
	if(s[0]=='?') ans*=9,l--;
	if(s[0]>='A'&&s[0]<='J') ans*=9,mp[s[0]]=1e9,k++;
	if(l) ans*=pow(10,l);
	for(int i=1;i<s.length();i++){
		if(mp[s[i]]&&mp[s[i]]!=1e9){
			ans*=10-k++;//算答案
			mp[s[i]]=1e9;//赋值为极大值代表已经处理过
		}
	}
	cout<<ans<<endl;
} 
```

---

## 作者：Lemon_zqp (赞：0)

### 思路
对于这道题目这个有三种情况：

数字不需要管，对答案的贡献为 $1$，不用做处理。

字母需要分两种情况来讨论：

1. 在开头，对答案的贡献为 $9$。

2. 不在开头，对答案的贡献可以用一个变量来存可能，一开始为 $10$，每出现一个新字母就减一。

问号和字母一样，也需要分两种情况：

1. 在开头，对答案的贡献为 $9$。

2. 不在开头，对答案的贡献始终为 $10$。

### 代码

```
#include<bits/stdc++.h>
using namespace std;

bool if_h[50];//A:1 B:2 C:3 D:4 ...... 
int g = 10;//选了10 - g个数。
long long ans = 1;//最高位有9种选择。

int main()
{
	string s;
	cin >> s;
	if(s[0] == '?')
	{
		ans *= 9; 
	}
	if(s[0] >= 'A' && s[0] <= 'J' && s[0] != '?')
	{
		ans *= 9;
		if_h[s[0] - 'A' + 1] = true;//标记为出现。
		g--; 
	}
	for(int i = 1; i <= s.size() - 1; i++)
	{
		if(s[i] == '?')
		{
			ans *= 10;
		}
		else if(if_h[s[i] - 'A' + 1] == false && !(s[i] >= '0' && s[i] <= '9'))//没有出现过。
		{
			if_h[s[i] - 'A' + 1] = true;//标记为出现。
			ans *= g;
			g--;//减去一种可能。
		}
	}
	cout << ans;
	return 0;
}

```


---

## 作者：Mx_sky (赞：0)

[题目传送门。](https://www.luogu.com.cn/problem/CF316A1)

### 思路阐述
题意题目已经说的很清楚了，在此不多叙述。

这是一道小学方案数问题，此题分以下几步解决：

- 数字不需要管，对答案的贡献为 $1$，乘了等于没乘。
- 字母需要分两种情况来讨论：

  1. 在开头，对答案的贡献为 $9$。
  
  2. 不在开头，对答案的贡献为 $10-$ 字母数 $+1$，此处可能会说得不太清楚，详细见代码。
- 问号同字母，也需要分两种情况：

  1. 在开头，对答案的贡献为 $9$。
  
  2. 不在开头，对答案的贡献始终为 $10$。

处理好以上几步，此题基本上就解决了。

此处可以自己想一个样例从而帮助理解：
```
ABC?AJ
```
开头的 $A$ 只能是 $1\sim9$，接下来的 $B$ 去掉 $A$ 的一种情况只能有 $9$（注意 $0$）种情况，$C$ 去掉 $A$ 和 $B$ 两种情况只能有 $8$（注意 $0$）种情况，问号不在开头，所以有 $10$ 种情况，接下来的 $A$ 不需要重复算跳过，$J$ 去掉 $A$，$B$，$C$ 三种情况有 $7$ 种情况，则答案为：$9\times9\times8\times10\times7=45360$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Max=500003;
#define ll long long
string s;
ll x,ans=1,sum,m=0;
map<char,int>a;
int main(){ 
    cin>>s;
    if(s[0]=='?') ans*=9;
    else if(s[0]>='A'&&s[0]<='Z') ans*=9,sum++,a[s[0]]++,m=1;
    //以上是处理开头
    int l=s.size();
    for(int i=1;i<l;i++) 
    {
    	if(s[i]=='?') ans*=10;
      //问号的贡献是10
    	else if(s[i]>='A'&&s[i]<='Z'&&a[s[i]]==0) sum++,a[s[i]]=1;
      //统计字母个数
    }
    for(;sum>m;sum--) ans*=(10-sum+1);
    //加上字母的方案数
    cout<<ans<<endl;
    return 0;
}
//蒟蒻的第7篇题解，求过
```


---

## 作者：Creative_sad_yosgic (赞：0)

## CF316A1の题解
### 思路
作为 CF361A 的弱化版，实现方式还是比较简单的，比如，我们手搓一组样例
```cpp
IAGED
```
首先，开头的 $I$ 只能表示 $1$ 到 $9$ 中的数（因为**首位不能为 $0$**），而因**为不同字母不能表示相同数字**，所以 $A$ 能表示的数只有 $9$ 种，$G$ 就只有 $8$ 种，$E$ 只有 $7$ 种.... 以此类推，根据小学数学，能组成的不同数字就有 $9\times 9 \times 8\times 7\times 6=27216$ 种。

易发现，只要出现 $?$ ，种数就会 $\times 10$，特别的，位于开头的 $?$，只会使总数 $\times 9$。

同时，出现已经出现过的字母，总数不会变化。

按此模拟即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
map<char,int> mp;//用 map 记录字母是否出现
int main(){
	cin>>s;
	int wen=1,zm=0;//记录 ？和字母 
	for(int i=0;i<s.size();i++){
		if(s[i]=='?'&&i==0) wen*=9;//开头的 ？使总数*9
		else if(s[i]=='?') wen*=10;//中间的？*10
		else if(mp[s[i]]==0&&s[i]>='A'&&s[i]<='Z') zm++,mp[s[i]]=1;//记录不同字母
	}
	int ans=1;
	while(zm){
		int p=10-zm+1;//为总数遇到该字母乘数
		if(p==10){//如果这是第一个字母
			if(s[0]>='A'&&s[0]<='Z') ans*=9;//如果在开头 *9
			else ans*=10;//否则*10
		}  
		else ans*=p;
		zm--;
	}
	cout<<ans*wen;
	return 0;
} 
```


---

## 作者：Jerry_heng (赞：0)

（一）

一道排列组合水题。

对每一位分三种情况讨论。

-  数字，即 $0-9$。

既然无法改变，也就不做讨论了。

- 字母，即 $A-J$。

假如确定一个字母对应的数字，那么与这个字母相同的字母也就确定了。

所以，只需要统计出现了多少不同的字母，设有 $\verb!s!$ 种。

那么就是将 $0-9$ 这些数字分配给 $\verb!s!$ 个字母，要用到排列：  $P$。

$\operatorname{P}\begin{matrix}
  s  \\
   10 
\end{matrix}=\prod \limits_{i=0}^{s-1}(10-i)$。

原理很简单。

第一个字母能从十个数字里挑，第二个字母只能从九个数字里挑，因为有一个已经挑过了，等等。

- 如果是问号，那么对应的数可以是 $0-9$，每个问号有十种可能。


注意：特殊考虑首位为 $0$ 成立。

即如果首位不确定，那么 $ans= ans \times \frac{9}{10}$。

（二） 

AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
int s,ans=1;
int p(int x){
	int a=1;
	for(int i=10;i>=10-x+1;i--)a*=i;
	return a;
}
bool b[10];
int main(){
	cin>>st;
	for(int i=0;i<st.length();i++){
		if(st[i]>='0'&&st[i]<='9')continue;
		if(st[i]=='?')ans*=10;
		else{
			if(!b[st[i]-'A']){
				s++;
				b[st[i]-'A']=1;
			}
		}
	}
	ans*=p(s);
	if(st[0]<'0'||st[0]>'9')ans=ans*9/10;
	cout<<ans;
	return 0;
} 
```


---

