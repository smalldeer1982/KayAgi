# Kolya and Tandem Repeat

## 题目描述

### 题目大意

有一个字符串 $s$ ，在字符串 $s$ 的后面添加 $k$ 个字符，使得新的字符串 $ss$ 有两个重复的字串，**重复子串必须是相邻的**，求两个重复子串的长度和。

## 样例 #1

### 输入

```
aaba
2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
aaabbbb
2
```

### 输出

```
6
```

## 样例 #3

### 输入

```
abracadabra
10
```

### 输出

```
20
```

# 题解

## 作者：zhouchuer (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF443B)
### 题意
有一个字符串 $s$，在字符串 $s$ 的后面添加 $k$ 个字符，使得新的字符串 $t$ 有两个重复的字串，**重复子串必须是相邻的**，求两个重复子串的长度和。

### 思路
注意题目问的是**最长**的情况。这道题不需要复杂的思路或代码，可用**暴力**实现。可以先在原字符串 $s$ 后面添加 $k$ 个特殊字符 `?`，然后枚举。可以直接开三层循环。第一层用于枚举起点，变量就用 $i$，第二层用于枚举长度，变量就用 $j$，第三层用于判断能否得到两个相同的子串，变量就用 $c$，如果 $s_c \ne s_{c+\frac{j}{2}}$ 且 $s_{c+\frac{j}{2}}$ 不为 `?` 时就是不合法的。每一轮通过比较长度更新答案，最后输出即可。[代码](https://www.luogu.com.cn/paste/rhtg8bms)。

---

## 作者：Never_care (赞：1)

$200$ 的数据量一眼暴力。
### 思路
在字符串 $s$ 后加上 $k$ 个字符，使新字符串有两个相同的**子串**。  

直接暴力枚举长度，起点，长度，判断，三重循环。判断时只需判断前和后是否完全相同。具体操作为判断 $s_i=s_{i+len}$ 的值是否为 $true$，符合条件则让 $maxx$ 变量存储最长长度。
### code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;
string s;
int k;
int main(){
	cin>>s>>k;
	for(int i=0;i<k;i++){
	    s+='%';
	}
	int maxx=-2e9;
	for(int i=0;i<=s.size()-2;i++){
		for(int j=2;j<=s.size();j+=2){
			bool flag=0;
			for(int k=i;k<=(k+j/2)-1;k++){
				if(s[k]!=s[k+j/2]&&s[j/2+k]!='0'){
				    flag=1;
				    break;
				}
			}
			if(flag){
				maxx=max(maxx,j);
			} 
		}
	}
	cout<<maxx;
	return 0;
}
```

---

## 作者：ATION001 (赞：1)

## 题目描述
给定一个字符串 $s$，现要求在字符串的后面添加 $k$ 个字符，使得字符串有两个完全相同的字串（不是子序列），请求出两个重复子串的长度之和。
## 思路
这一题首先看着很麻烦，但是看看数据范围：$1\le |s| \le 200$（$|s|$ 表示字符串 $s$ 的长度）。

那么，~~直接暴力啊。~~

首先我们在字符串 $s$ 的后面拼接上长度为 $k$ 的乱码（只要不是字母就行了）。然后遍历整个字符串，开始添加字符。如果当前修改后的字串（记作 $s1$）满足题目要求，那么 $ans=\max(ans,|x|)$，否则结果保持不变（$ans$ 记录的是答案）。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int k,ans=INT_MIN;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>s>>k;
	for(int i=1;i<=k;i++){ // 拼接上乱码（这里我拼接的是"?"）
		s+='?';
	}
	for(int i=0;i<s.size();i++){ // 遍历整个字符串
		for(int j=2;j+i-1<s.size();j+=2){ // 枚举长度
			bool flag=false;
			for(int k=i;k<=i+j/2-1&&!flag;k++){ // 这个循环判断当前长度是否合法
				if(s[k]!=s[k+j/2]&&s[k+j/2]!='?'){ // 如果与当前字符对应的字符不一样并且不能修改，说明不合法
					flag=true;
				}
			}
			ans=(!flag?max(ans,j):ans); // 合法的话比较结果，不合法保持不变，这里用了三目运算符
		}
	}
	cout<<ans;
}
```

---

## 作者：Yuexingfei_qwq (赞：0)

暴力，启动~
## 思路  
看到数据范围后面带两个 $0$，考虑 $O(N^3)$ 的暴力。  

首先，把后面需要储存新添加的字符串的位置预留在 $s$ 后面，长度为 $k$。做法就是往 $s$ 的末尾扔 $k$ 个非小写英文字母的字符就行。 

然后，写上字符串暴力三件套（枚举起点、枚举长度和判断是否满足条件），在满足题目要求的条件时更新答案即可。代码就不过多叙述了。

## AC CODE
```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf ("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a * b / __gcd(a, b)
#define setp(x) fixed << setprecision(x)

using namespace std;

typedef long long ll;
typedef string str;
using ull = unsigned ll;

str s;
int k;
int n;
int ans = -inf;

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	cin >> s >> k;
	F(i, 1, k, 1) {
		s.push_back('#');
	}
	n = s.size();
	base(s);
	F(i, 1, n, 1) {
		F(j, 2, n - i + 1, 2) {
			bool f = 0;
			F(k, i, i + (j / 2) - 1, 1) {
				if (s[k] != s[k + j / 2] && s[k + j / 2] != '#') {
					f = 1;
					break;
				}
			}
			if (!f) {
				ans = std::max(ans, j);
			}
		}
	}
	cout << ans << el;
	r0;
}
```

[AC 记录](https://codeforces.com/contest/443/submission/303225303)

--- 
完结~~不~~散花。

---

## 作者：goIdie (赞：0)

题意比较清楚，不再赘述。

## 思路

由于数据范围很小，考虑直接暴力。

在 $s$ 后添加 $k$ 个特殊字符，然后三层循环暴力枚举，分别枚举起点，长度，判同。判同时只需判断前一半和后一半是否相同。形式化的，设枚举的长度为 $l$，则判断 $s_i=s_{i+l}$ 的结果是否为 $1$。建一个变量 $ans$ 表示最大长度，在合法时和 $l$ 取最大值即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int k,ans,flag;
int main(){
	cin>>s>>k;
	for(int i=0;i<k;i++){
	    s+='э';
	}
	for(int i=0;i<=s.size()-2;i++){
		for(int l=2;l<=s.size();l+=2){
			flag=0;
			for(int j=i;j<=(i+l/2)-1;j++){
				if(s[j]!=s[j+l/2]&&s[j+l/2]!='0'){
				    flag=1;
				    break;
				}
			}
			ans=flag?max(ans,l):ans; 
		}
	}
	cout<<ans;
}
```

---

## 作者：wwxxbb (赞：0)

### 思路

首先，这题让我们求的是**最长**的长度，如果不是最长的话取最后 $k$ 位就行了。

此题没有用什么高深的算法，直接暴力枚举长度，判断合法的时候只需看前一半和后一半是否相同。形式化地，如果 

$$s_i\neq s_{i+\frac{len}{2}}$$

则不合法。

如何判断在原串后面的字符呢？只需在后 $k$ 位加特殊字符即可。

### Code

```c++
#include <bits/stdc++.h>
using namespace std;

string s;
int k, ans;

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> s >> k;
	s += string(k, '$');
	for (int i = 0; i < s.size(); i ++) {
		for (int len = 2; len <= s.size(); len += 2) {
			if (i + len / 2 >= s.size()) break;
			bool flag = 0;
			for (int j = i; j < i + len / 2; j ++)
				if (s[j] != s[j + len / 2] && s[j + len / 2] != '$') {
					flag = 1;
					break;
				}
			if (!flag) ans = max(ans, len);
		}
	}
	return cout << ans, 0;
}
```

---

## 作者：_Kimi_ (赞：0)

# CF443B题解

### 题意

有一个字符串 $s$ ，在字符串 $s$ 的后面添加 $k$ 个字符，使得新的字符串 $ss$ 有两个一样的字串，求两个重复子串的长度和。

### 思路

在字符串后面添加 $k$ 个 $0$，枚举起点和长度即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int k, ans;
int main() {
	ios::sync_with_stdio(false);
	cin >> s >> k;
	for (int i = 0; i < k; i++) s += "0";
	for (int i = 0; i <= s.size() - 2; i++) {
		for (int j = 2; j <= s.size(); j += 2) {
			bool f = 0;
			for (int v = i; v <= (i + j / 2) - 1; v++) {
				if(s[v] != s[v + j / 2] && s[v + j / 2] != '0') {
					f = 1;
					break;
				}
			}
			if(!f) ans = max(ans, j);
		}
	}
	cout << ans << endl;
	return 0;
}
```


---

