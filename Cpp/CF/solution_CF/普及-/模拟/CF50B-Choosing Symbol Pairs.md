# Choosing Symbol Pairs

## 题目描述

There is a given string $ S $ consisting of $ N $ symbols. Your task is to find the number of ordered pairs of integers $ i $ and $ j $ such that

1\. $ 1<=i,j<=N $

2\. $ S[i]=S[j] $ , that is the $ i $ -th symbol of string $ S $ is equal to the $ j $ -th.

## 样例 #1

### 输入

```
great10
```

### 输出

```
7
```

## 样例 #2

### 输入

```
aaaaaaaaaa
```

### 输出

```
100
```

# 题解

## 作者：Eason_AC (赞：6)

## Content
给定一个字符串 $s$，求有多少对是相同的（**包括自己和自己这一对，$(x,y)$ 和 $(y,x)$ 是不相同的一对**）。

**数据范围：$1\leqslant |s|\leqslant 10^5$。**
## Solution
这道题目需要证明一个东西：**如果有 $n$ 个相同的字母，那么它们之间相同的对数就是 $n^2$。**

证明：因为自己和自己算做一对，所以先有 $n$ 对。

同时，又因为两两之间配对可以算作两对，$n$ 个字符两两配对就一共会有 $\dfrac{n(n-1)}{2}\times2=n(n-1)$ 对。

所以，加起来一共会有 $n+n(n-1)=n+n^2-n=n^2$ 对。

证毕。

因此，我们需要统计一个字符出现的次数 $n$，那么它对于这个对数的贡献就是 $n^2$，对于每个字符的贡献，我们累加起来，这样得出的结果就是我们题目的答案了。

建议开两个 $\texttt{map}$，一个 $\texttt{map}$ 用来存储每个字符出现的次数，另一个 $\texttt{map}$ 则用来判断是否有重复（这样就不会重复计算）。

## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

string s;
map<char, long long> a, vis;
long long sum;

int main() {
	cin >> s;
	for(int i = 0; i < s.size(); ++i)	a[s[i]]++;
	for(int i = 0; i < s.size(); ++i) {
		if(!vis[s[i]]) {
			sum += a[s[i]] * a[s[i]];
			vis[s[i]] = 1;
		}
	}
	printf("%lld\n", sum);
	return 0;
}
```

---

## 作者：陈晋衍 (赞：3)

模拟大法好啊

基本思路：统计有几个字符，平方相加后输出。

![a](https://cdn.luogu.com.cn/upload/pic/56257.png)

从这张图可以看出来，配对的个数=字符的个数的平方

接下来就好办了
```cpp
#include<iostream>
using namespace std;
long long a[300],s;//开long long
int main()
{
	char c;
	while(cin>>c)a[c]++;//统计字符数
	for(int i=1;i<=299;i++){
		s+=a[i]*a[i];//平方+相加
	}
	cout<<s<<endl;//输出，完美
	return 0;
}
//超短代码
```

---

## 作者：Daniel_yao (赞：1)

## 题目大意

输入一个字符串，判断有多少对是相同的。包括自己和自己这一对。注意 $(x,y)$ 和 $(y,x)$ 是不相同的一对。

### 具体思路

先用一个桶数组把所有出现过的字符存起来，再把所有出现过的字符次数累加起来，就是我们要的答案。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

map<char, long long> cnt;//开map卡常
string s;
long long sum;

int main(){
	cin >> s;
	for(int i = 0;i < s.size();i++){
		cnt[s[i]]++;//统计出现过的字符；
	}
	for(int i = 0;i < s.size();i++){
		sum += cnt[s[i]]; //累加
	}
	cout << sum;
	return 0;
} 
```
时间复杂度为 $O(N)$ ，直接切掉。 

---

## 作者：DPseud (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF50B)

# 题目意思

在一个字符串里找相同的字符有多少个。

# 题目思路

数组计数，即记录每一个字符出现的次数，但是要注意：当我们统计到一个字符出现 x 次时，并不是给累加器加上 x 次，请看下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/zekig4ho.png)

从图中我们能得出：

```
配对次数=出现次数*出现次数=出现次数的平方。
```

有了思路，代码就不难打了，就是要注意数据类型↓

# 正确代码

```cpp
#include<bits/stdc++.h>//万能的头文件
using namespace std; 
int main(){
    
    //麻雀虽小，五脏俱全
	string s;
	unsigned long long sum=0;
	getline(cin,s);//虽说字符串里应该没空格，但为了保险还是用getline 
	static unsigned long long a[256];//main函数外定数组不好看，用static静态类型直接数组初始化，这里注意要用long long 
	for(unsigned long long i=0;i<s.length();i++)a[s[i]]++;//数组计数
	for(int i=0;i<128;i++)//ASCII码最大是128，遍历128即可 
	{
		unsigned long long dou=pow(a[i],2);//pow(a[i],2)可以写成a[i]*a[i] 
		sum+=dou;//遍历计数的数组，将平方相加
	}
	cout<<sum; 
    return 0;
}
```

---

## 作者：Lucifer_Bartholomew (赞：1)

# 模拟
既然是相同的字符，就算出每个字符出现了多少个。对于每个字符，可以和相同字符组合，所以每个字符的组合数量就是字符数 * 字符数。

且
>包括自己和自己这一对

-->自己也要算
```cpp
#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rr register int
using namespace std;
char s[70]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
map<char,int> ma;
int main()
{
	char c[100001];
	scanf("%s",c);//读入
	int n=strlen(c);
	for(rr i=0;i<n;++i)
		ma[c[i]]++;//计算每个字符出现了多少次
	long long ans=0;
	for(rr i=0;i<62;++i)
		ans+=(long long)ma[s[i]]*ma[s[i]];//1e5的数据范围所以是long long
	printf("%lld\n",ans);
	return 0;
}
```
~~我是蒟蒻~~

---

## 作者：dingshengyang (赞：0)

这题有几个坑点：

$1$.$n \le 10^5$，$O(n^2)$ 枚举会 TLE。

$2$.$n^2$ 最大可以有 $10^{10}$，切记开 `long long`！

好，现在正式讲解。

对于每个字符 $s_i$，有 $n$ 个字符 $s_j$ 可以和它结对。但是，如果 $s_i = s_j(i\not = j)$，我们不能让 $(s_j,s_i)$ 再次算一遍！

每一次对答案的贡献都是 $cnt(s_i)^2$。（这表示形如 $s_i$ 的字符出现的次数）

好，$O(n)$ 过。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long st[256],vis[256];
long long ans = 0;
int main(){
	string s;
	cin >> s;
	for(int i = s.size()-1;i >= 0;i --)st[s[i]] ++;
	for(int i = s.size()-1;i >= 0;i --){
		if(vis[s[i]]==0){
			ans += st[s[i]]*st[s[i]];vis[s[i]] = 1;
		}
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：szkzyc (赞：0)

题意清楚，就不多做解释了。

首先注意到 $|s|<=10^5$，就是说 $s$ 的长度最长能到 $1e5$，用 $O(slen^2)$ 暴力肯定会超时。

因为只有完全相同的字符才会被算上，所以可以记录每个字符出现了多少次。容易发现， $x$ 个字母中能两两组合出 $x^2$ 对相同的组合。

考虑使用映射 $map$ 来解决，存字符出现的个数。

### 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF INT_MAX
#define debug puts("qwq")
using namespace std;
map <char, int> m; //用来存字符x出现了几次的映射 ，记得开long long 
map <char, bool> m2;//用来判断这个字符是否被统计过的映射 
long long cnt;//记得开long long 
int main(){
	string str;
	cin >> str;
	for(int i = 0; i < str.size(); i++) m[str[i]]++;//这个字符对应的值加一 
	for(int i = 0; i < str.size(); i++){
		if(!m2[str[i]]){//如果这个字符没有被统计过 
			cnt += m[str[i]] * m[str[i]];//答案加上这个字符出现次数的平方 
			m2[str[i]] = true;//标记统计过 
		}
	}
	cout << cnt << endl;//输出答案 
	return 0;
}

```


---

## 作者：Allanljx (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/CF50B)

[CF传送门](http://codeforces.com/problemset/problem/50/B)
## 题意
输入一个字符串，判断有多少对是相同的。包括自己和自己这一对。注意 $(x,y)(x,y)$ 和 $(y,x)(y,x)$ 是不相同的一对。
## 思路
找规律，发现平方和就是结果。设有 $n$ 个相同的字母，因为自己和自己算做一对，所以有 $n$ 对， $n$ 个字符配对就会有 $n(n-1)$ 对，再加上 $n$ 就一共有 $n*n$ 对。统计每种相同的字符有几个，将平方和输出。

## 代码
```cpp
#include<iostream>
using namespace std;
long long a[301],sum;
int main()
{
	char ch;
	while(cin>>ch)
	{
		a[ch]++;
	}
	for(int i=1;i<=300;i++)
	{
		sum+=a[i]*a[i];
	}
	cout<<sum<<endl;
	return 0;
}
```


---

## 作者：phil071128 (赞：0)

显然这是一道模拟题

题意：
输入一个字符串，判断有多少对是相同的。**包括自己和自己这一对**。注意 $(x,y)$ 和 $(y,x)$ 是不相同的一对


首先我们很容易就能得出暴力代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
string a1;
ll sum;
int main(){
	cin>>a1;
	int str=a1.length();
	for(int i=0;i<str;i++){
		for(int j=0;j<str;j++){
			if(a1[i]==a1[j]){
				sum++;
			}
		}
	}
	cout<<sum;
	return 0;
}
```
过了前20个点，后面的应该都TLE了，还是比较满意的（

[$\color{white}\colorbox{black}{TLE}$**评测代码** ](https://www.luogu.com.cn/record/43238777)

然后我们尝试换一种思想

|  |AAA  | ABB | ACC |
| -----------: | -----------: | -----------: | -----------: |
| 图 | ![](https://cdn.luogu.com.cn/upload/image_hosting/2qy2rrb7.png) |![](https://cdn.luogu.com.cn/upload/image_hosting/vg9o57sd.png)  | ![](https://cdn.luogu.com.cn/upload/image_hosting/rgnrm3i5.png)
 A的个数| 3 | 1 |1|
| B的个数 | 0 |  2| 1 |
|  C的个数| 0 | 0 | 1 |
| 输出 | 9 | 5 | 3 |



由此，推出公式：

 **配对的个数=每个字符个数的平方和**
 
### 代码：
 ```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
string s;
ll num[300];
ll sum;
int main(){
	cin>>s;
	for(int i=0;i<s.length();i++){
		num[s[i]]++;  //用一个桶来统计每个字符的数量
	}
	for(int i=0;i<300;i++){
		sum+=pow(num[i],2);
	}
	cout<<sum;
	return 0;
}
```
[$\color{white}\colorbox{green}{AC}$**评测代码** ](https://www.luogu.com.cn/record/43242449)
 

求管理通过


---

## 作者：chenkaiwen (赞：0)

了解一下题意，题目是要求一个字符串中，把每个出现过的字符的数量的平方相加后输出，那么这一题的难点就是储存每一个字符的数量，因为前面已经有人用 $ map $ （红黑树）来做，所以这里就用另一种不同的方法来做，对于题目输入的字符串中的字符我们可以把它们分成三种，分别是：数字，小写字母，大写字母，然后我们开三个大小发表为：10,26,26的数组来存三种字符中每一个字符的数量，在求答案时有一点要注意，因为是求平方所以最好要加上 $ long$ $ long $ 其他细节上的问题我会在代码注释中写出，这里就不在说了，代码如下：

### [![](https://cdn.luogu.com.cn/upload/image_hosting/f732gahs.png)证明](https://www.luogu.com.cn/record/32081912)

```cpp
#include<bits/stdc++.h>
#include <iostream>
using namespace std;
int a[10],b[26],c[26];//三个数组对应三种字符：数字，小写字母，大写字母
int main() {
	ios::sync_with_stdio(0);
	char w=getchar();//getchar 比cin快
	while(w!='\n') {//如果换行代表输入结束了
		if(w>='0'&&w<='9') {//数字 
			a[w-'0']++;
		}
		if(w>='a'&&w<='z') {//小写字母 
			b[w-'a']++;
		}
		if(w>='A'&&w<='Z') {//大写字母 
			c[w-'A']++;
		}
		w=getchar();
	}
	long long ans=0;//因为是平方所以最好要加long long
	for(int i=0; i<10; i++) {
		ans+=(long long)a[i]*a[i];//用括号括着变量类型可以强转变量 
	}
	for(int i=0; i<26; i++) {
		ans+=(long long)b[i]*b[i];
	}
	for(int i=0; i<26; i++) {
		ans+=(long long)c[i]*c[i];
	}
	cout<<ans<<endl;
	return 0;
}




```


---

## 作者：Suuon_Kanderu (赞：0)

这个题如果用暴力的话会TLE掉的！（废话）
```
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	string s;
	int ans=0;
	cin>>s;
	for(int i=0;i<=s.size()-1;i++)
	for(int j=0;j<=s.size()-1;j++)
	if(s[i]==s[j])ans++;
	cout<<ans<<endl;
	return 0;
}
```
很容易想到统计字符的方法，其他大佬已经说了，窝就不在说了。

```
#include<iostream>
using namespace std;
long long a[300]={0},ans;//10^5;
int main()
{
    char c;
    while(cin>>c)a[int(c)]++;
    for(int i=1;i<=299;i++)if(a[i])ans+=a[i]*a[i];//微微优化 
    cout<<ans<<endl;
    return 0;
}
```


---

