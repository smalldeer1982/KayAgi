# Substring and Subsequence

## 题目描述

给定两个字符串 $a$ 和 $b$，均由小写拉丁字母组成。

一个字符串的子序列是指可以通过从原字符串中删除若干（可能为零）个字符后得到的字符串。一个字符串的子串是该字符串的一个连续子序列。

例如，考虑字符串 abac：

- a、b、c、ab、aa、ac、ba、bc、aba、abc、aac、bac 和 abac 是它的子序列；
- a、b、c、ab、ba、ac、aba、bac 和 abac 是它的子串。

你的任务是计算一个字符串的最小可能长度，使得该字符串包含 $a$ 作为子串，并且包含 $b$ 作为子序列。

## 说明/提示

在下面的示例中，与 $b$ 相等的子序列对应的字符用加粗表示。

在第一个示例中，其中一个可能的答案是 caba。

在第二个示例中，其中一个可能的答案是 ercf。

在第三个示例中，其中一个可能的答案是 mmm。

在第四个示例中，其中一个可能的答案是 contest。

在第五个示例中，其中一个可能的答案是 abcdefg。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
aba
cb
er
cf
mmm
mmm
contest
test
cde
abcefg```

### 输出

```
4
4
3
7
7```

# 题解

## 作者：junee (赞：5)

# CF1989B 题解

## 前置知识

双指针。

## 题目分析

子串和子序列的差别就在于子序列是可以断开的，本质上就是要求 $a,b$ 的最长公共子序列，用双指针求，答案即为两个字符串长度之和减去最长公共子序列的长度。

时间复杂度为 $O(nm)$，$n,m$ 为字符串长度。

## Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
string s1,s2;
int n,T,m;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--){
        cin>>s1>>s2;
        n=s1.size();m=s2.size();
        s1=' '+s1,s2=' '+s2;
        int ans=0;
        for(int i=1;i<=m;i++){
            int l=1,r=i;
            while(l<=n&&r<=m){
                if(s1[l]==s2[r])r++;
                l++;
            }
            ans=max(ans,r-i);
        }
        cout<<m+n-ans<<"\n";
    }
    return 0;
}
```

---

## 作者：liyifan202201 (赞：3)

## 题意
给你两个只有小写拉丁字母的字符串 $a，b$ 你需要找出以 $a$ 为子串且以 $b$ 为子序列的一个字符串的最小值。
## 思路
题目上说要使符合要求的字符串的长度尽量小，本质上就是要求 $a，b$ 的最长公共子序列，可以用双指针求，答案就是两个字符串长度和减去最长公共子序列的长度。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){
		string s1,s2;
		cin>>s1>>s2;
		int n=s1.size(),m=s2.size();
		s1=' '+s1,s2=' '+s2;
		int ans=0;
		for(int i=1;i<=m;i++){
			//双指针
			int l=1,r=i;
			while(l<=n and r<=m){
				if(s1[l]==s2[r])r++;
				l++;
			}
			ans=max(ans,r-i);
		}
		cout<<m+n-ans<<endl;
	}
	return 0;
}
```

---

## 作者：xihegudiiakioi (赞：2)

## 题目描述：
给定两个字符串 $a$ 和 $b$，假定有一字符串 $c$，该字符串需要包含 $a$ 作为其子串，并且包含 $b$ 作为其子序列，且长度最小。求 $c$ 的长度。

## 解题思路：
- 子序列：从一个序列中删除一些（或不删除）元素而不改变剩余元素的顺序形成的一个新序列。（不一定连续）

- 子串：从一个字符串中连续取出的一部分字符所组成的新字符串。（一定连续）

由于题目的数据范围较小，可以通过暴力枚举来求解。

为了使 $c$ 的长度最短，我们需要让 $b$ 与 $a$ 的最长公共子序列尽可能长。为此，我们可以枚举 $b$ 的每个位置作为 $a$ 的开头，然后依次往后匹配，记录 $a$ 与 $b$ 在这个区间内的最长公共子序列长度。最终，$c$ 的最小长度就是 $|a|+|b|$ 减去这个最长公共子序列的长度。

时间复杂度：$O(|a| |b|)$
## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int main() {
	cin >> t;
	while(t--) {
		string a,b;
		cin >> a >> b;
		int n = a.length();
		int m = b.length();
		int maxl = 0;
		for(int i = 0; i < m; i++) {
			int k = 0;
			for(int j = 0; i + k < m && j < n; j++) {
				if(a[j] == b[i + k]) {
					k++;
				}
			}
			maxl = max(k,maxl);
		}
		cout << n + m - maxl << endl;
	}
}
```

---

## 作者：tanzexiaodezhonghao (赞：1)

## 思路
大概是让你构造一个以 $a$ 为子字符串且以 $b$ 为子序列的字符串，这里很容易想到，因为要包含 $b$ 中的所有字母和字符串 $a$，所以结果是 $a$ 和 $b$ 的长度减去两者的最长公共子序列长度。可以直接暴力。评个橙或者红。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int main(){
	int T;cin>>T;int maxans=0,now;
	while(T--){
		cin>>a>>b;maxans=0;
		int lena=a.size(),lenb=b.size();
		for(int i=0;i<lenb;i++){
            int l=0,r=i;
            while(l<lena&&r<lenb){
                if(a[l]==b[r]) r++;
                l++;
            }
            maxans=max(maxans,r-i);
        }
		cout<<lena+lenb-maxans<<endl;
	}
    return 0;
}
```

---

## 作者：qhr2023 (赞：1)

## 题意

求一个包含 $a$ 作为子串和 $b$ 作为子序列的字符串的最小长度。

## 思路

贪心，因为答案一定包含这两个字符串并加上一些字符，为使答案最短，我们要让添加的字符最少，即让 $a$ 和 $b$ 的公共子序列尽可能长，所以答案即为两个字符串长度之和减去最长公共子序列的长度。

## 实现

数据小，直接暴力找最长公共子序列，每次从 $b$ 的的一个字符开始向后与 $a$ 匹配，$sum$ 记录当前区间的最长公共子序列，$s$ 记录 $a$ 和 $b$ 的最长公共子序列。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin >> T;
	while (T--) {
		string a, b;
		cin >> a >> b;
		int n=a.size(), m=b.size(), s=0;
		for (int i=0, sum=0; i<m; i++, s=max(s, sum), sum=0) 
			for (int j=0, t=i; j<n; j++) 
				if(a[j]==b[t])
					t++, sum++;
		cout << n+m-s << '\n';
	}
	return 0;
}
```

---

## 作者：Eason_cyx (赞：1)

考虑将 $t$ 分成 $3$ 部分：第一部分插在 $s$ 字符串前面，第二部分包含在 $s$ 字符串里，第三部分插在 $s$ 后面，那么我们只需要判断第二部分是否能包含在 $s$ 字符串内即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
 
void Main() {
	string s,t; cin >> s >> t;
	swap(s,t);
	int ans = 0x7fffffff;
	for(int i = 0;i < s.size();i++) {
		for(int j = i;j < s.size();j++) {
			//i+1 ~ j
			string q = s.substr(i,j-i+1);
			// cout << q << endl;
			bool flag = true;
			int pos = 0;
			for(int k = 0;k < q.size();k++) {
				int ppos = pos;
				while(ppos < t.size() && t[ppos] != q[k]) ppos++;
				if(ppos == t.size()) {
					flag = false;
					break;
				}
				pos = ppos+1;
			}
			if(flag) {
				// cout << "YES" << endl;
				ans = min(ans,(int)t.size()+i+(int)s.size()-j-1);
			}
		}
	}
	if(ans == 0x7fffffff) cout << (int)t.size()+(int)s.size() << endl;
	else cout << ans << endl;
}
int main() {
	int t; cin >> t;
	while(t--) Main();
	
	return 0;
}
```

---

## 作者：tzzl3035 (赞：0)

# CF1989B 题解
### 题目大意
有 $t$ 组数据，每组给定两个由小写字母组成的字符串 $a$ 和 $b$，求以 $a$ 为子串且以 $b$ 为子序列的字符串的最小长度。
### 思路
很明显，我们应该用 $a$ 和 $b$ 的长度和减去两者的的最长公共子序列。但是目标字符串要以 $a$ 为子串，不难想出，这个公共子序列一定要是 $b$ 的子串，所以要使用类似于双指针的处理方法。
### 代码（去头文件）
``` c++
using namespace std;
void solve() {
	string a, b;
	cin >> a >> b; // 读入
	int len1 = a.size(), len2 = b.size(), res = 0;
 	// 取最长公共子序列
	for(int i = 0; i < len2; i++) { // 枚举开头
		int tmp = 0, ind = i;
		for(int j = 0; j < len1; j++) {
			if(b[ind] == a[j]) // 处理当前元素相同的情况
				++tmp, ++ind;
		}
		res = max(res, tmp); // 更新答案
	}
	cout << len1 + len2 - res << '\n';
}
int main()
{
 	// 挨组处理
	int t; cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}
```
### [RESULT](https://codeforces.com/problemset/submission/1989/270176344)

---

## 作者：IOI_official (赞：0)

## 题意：

构造一个字符串 $c$，使 $a$ 为 $c$ 的字串且 $b$ 为 $c$ 的子序列，求 $c$ 的最小长度。

## 思路：

设 $a$ 的长度为 $lena$，$b$ 的长度为 $lenb$，$a$ 与 $b$ 的最大公共子序列长度为 $s$，因为 $c$ 中一定包含 $a$ 跟 $b$ 中的所有字符，所以我们可以知道 $c$ 的最小长度为 $lena+lenb-s$。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,maxn=-1;
string s,ss;
int main(){
	cin>>t;
	while(t--){
		cin>>s>>ss;
		int lena,lenb;
		lena=s.size();
		lenb=ss.size();
		maxn=-1;
		for(int i=0;i<lenb;i++){
			int n=i,len=0;
			for(int j=0;j<lena;j++){
				if(s[j]==ss[n]){
					n++;
					len++;
				}
			}
			maxn=max(maxn,len);
		}
		cout<<lena+lenb-maxn<<endl;
	}
	return 0;
}
```

---

## 作者：xingshuyan000 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1989B)

# 题目大意

给你两个只有小写拉丁字母的字符串 $a,b$，你需要找出以 $a$ 为子串且以 $b$ 为子序列的一个字符串的最小值。

# 题目分析

### 关联知识点

[子串、子序列](https://oi-wiki.org/string/basic/)

[最长公共子序列](https://oi-wiki.org/dp/basic/#%E6%9C%80%E9%95%BF%E5%85%AC%E5%85%B1%E5%AD%90%E5%BA%8F%E5%88%97)

（这题的最长公共子序列求法跟 OI-wiki 上面的求法不一样，我最开始用了 OI-wiki 的方法求最长公共子序列，结果 WA 了，后来又用了后面代码所示的方法）

这道题是一个很明显的贪心题，贪心策略不难想到，这题的答案就是字符串 $a,b$ 的长度之和减去 $a,b$ 的最大公共子序列长度。

鉴于本题测试点范围不大，虽然测试组数达到了 $1000$，但是 $1 \le |a|,|b| \le 100$，测试时间限制又是 $2s$，所以可以直接考虑暴力枚举，找出 $a,b$ 的最大公共子序列长度（记为 $lcs$）。

则答案 $ans=|a|+|b|-lcs$。

本题的时间复杂度 $\mathcal{O}(|a| \times |b|)$。

# Code

代码走起！

```cpp
#include<bits/stdc++.h>
using namespace std;
void solution();//函数的声明，因为solution()函数是在main()函数的后面，必须加上函数的声明，否则会编译错误
int main()
{
	int T;
	cin>>T;
	while(T--)solution();
	return 0;
}
int LCS(string a,string b)//求字符串a,b的最长公共子序列
{
	int p=a.length(),q=b.length();//获取两个字符串的长度
	int lcs=-2e9;
	for(int i=0;i<q;i++)
	{
		int s=0,aa=i;//s记录长度，aa记录字符所在b的位置
		for(int j=0;j<p;j++)
		{
			if(a[j]==b[aa])aa++,s++;
		}
		if(s>=lcs)lcs=s;//打擂台求出来最大公共子序列长度
	}
	return lcs;
}
void solution()
{
	string a,b;
	cin>>a>>b;
	int ans;
	int p=a.length(),q=b.length();//p，q分别存储字符串a，b的长度
	int lcs=LCS(a,b);
	ans=p+q-lcs;//答案等于两个字符串a，b的长度之和减去这两个字符串的最长公共子序列长度
	cout<<ans<<endl;//直接输出即可，记得换行
	return;
}
```

---

## 作者：xcms (赞：0)

这道题比较简单。

首先不难发现，要使 $a$ 和 $b$ 是 $c$ 的子串，最简单的办法就是直接把 $a$ 和 $b$ 拼接，但是这样 $c$ 的长度会比较长，所以我们考虑将 $a$ 和 $b$ 的最长公共子序列从 $c$ 减去。

可以用暴力枚举最长公共子序列。首先枚举字符串 $a$，每次把当前的 $i$ 存下来，然后枚举 $b$，判断 $a_i$ 与当前的 $b_j$ 是否相等，最后把 $i$ 加 $1$ 并记录答案。

这里只给出求最长公共子序列的代码：
```cpp
for(int i=0;i<s2.size();i++){
	int now=0,temp=i;
	for(int j=0;j<s1.size();j++){
		if(s1[j]==s2[temp]){
			now++;
			temp++;
		}
	}
	len=max(len,now);
}
```

---

## 作者：x1489631649 (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/CF1989B)
#### 个人感言
开始我没看数据范围，后面才发现可以暴力枚举。
# 输入 
1. 第一行，数据组数 $t(1 \le t  \le 10^3)$。
1. 每组数据两行，代表子字符串 $a$ 和子序列 $b$，将它们的长度分别记为 $l1(1 \le l1 \le 100)$ 和  $l2(1 \le l2 \le 100)$。
1. [子字符串](https://baike.baidu.com/item/%E5%AD%90%E4%B8%B2/11047664?fr=ge_ala)和[子序列](https://answer.baidu.com/answer/land?params=OFXuIxDyA2vnx7Krw9b48oXIUD2qMZUVpWtbd9Sv%2FB8tedQnPt0q0Zb7sapzZ1k4a7M3%2FnK2lfYWZvHjeDGi4xek8DU1m8qilyUKzEW9twzUsbWp5j%2BnOhhJoKk1kfik%2BAR8CyOp8H4XlQHFssIVwwT5GTKhS6PxCRzCZUNx9T8fFB%2BwbGziR8o6z0ucY68E62Tv%2BUOOZTicEUvYa4WMVA%3D%3D&from=dqa&lid=cc1d6c4e003de283&word=%E5%AD%90%E5%BA%8F%E5%88%97%E6%98%AF%E4%BB%80%E4%B9%88%E6%84%8F%E6%80%9D)
# 输出
输出最短的字符串的长度，使它以 $a$ 为子字符串且以 $b$ 为子序列。
# 分析
因为要使符合要求的字符串的长度尽量小，所以要使 $a$ 和 $b$ 重复的字符尽量多，我们可以暴力的枚举，来寻找字符串 $a$ 和 $b$ 的最长公共子序列，然后就不难求出满足要求的字符串的长度。
 # Code
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		string a,b;
		cin>>a>>b;
		int l1=a.size(),l2=b.size();//两个字符串的长度。 
		int maxx=-1e9;//最长公共子序列。 
		for(int i=0;i<l2;i++)
		{
			int l=0;//当前枚举公共子序列的长度。 
			int place=i;//当前枚举子序列 b 的下标。 
			for(int j=0;j<l1;j++)
			{
				if(a[j]==b[place])
				{
					place++;
					l++;
				}
			}
			maxx=max(maxx,l);
		}		
		cout<<l1+l2-maxx<<endl;
	}
	return 0;
}
```
# 时间复杂度
本代码使用三重循环，且 $t$ 的最大值为 $10^3$，$l1$ 和 $l2$ 的最大值为 $100$ 所以极限只会跑 $10^7$ 次，题目中的时间限制为 2 秒，所以可以通过。

---

## 作者：ANDER_ (赞：0)

考察：贪心、动态规划、最长公共子序列。
## 题意
给定两个字符串 $s_1$ 和 $s_2$，构造字符串 $s_3$，使得 $s_1$ 和 $s_2$ 为 $s_3$ 的子串，求 $|s_3|$ 的最小值。共有 $n$ 组数据。

## 思路
考虑贪心。不难发现，计算出 $s_1$ 与 $s_2$ 的最长子公共子序列 $lcs$，计算 $|s_1| + |s_2| - |lcs|$ 即可得到答案。

时间复杂度：$O(|s_1|\times|s_2|)$
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std; 
int n;
string a, b;
inline int get(const string& s1, const string& s2) {//计算最长公共子序列的长度
	int m = s1.length(), n = s2.length(), tmp = -1;
   	for(int i = 0, s, x ; i < n ; i ++){
		s = 0 ;
		x = i ;
		for(int j = 0 ; j < m ; j ++){
			if(a[j] == b[x]){
				x ++, s ++;
			}
		}
		tmp = max(tmp, s);
	}
	return tmp;
}
signed main() {
	ios::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);
	cin>>n;
	while(n --) {
		cin>>a>>b;
    	cout<<a.size() + b.size() - get(a, b)<<endl;//计算结果
	}
    return 0;
}

```

---

## 作者：Dream_Mr_li (赞：0)

## 题意

有一个包含 $a$ 为子串并且 $b$ 为子序列的字符串。让你求这个字符串的最小长度。

## 思路

可以想到，结果一定是 $a$ 和 $b$ 的长度之和减去最大公共子序列的长度。

又因为最大公共子序列一定包含 $a$ 和 $b$ 并重复一些字符，所以我们为了求出最大公共子序列只需要让 $a$ 和 $b$ 重复的字符尽量多，最后 $a$ 和 $b$ 的长度之和减去最大公共子序列的长度即可。

## 代码

```c++
#include<bits/stdc++.h>
using namespace std;
int la,lb,be,len,mx; 
string a,b;
void solve(){
	cin>>a>>b;
	la=a.size();
	lb=b.size();
	mx=0;
	for(int i=0;i<lb;i++){
		len=0; be=i;
		for(int j=0;j<la;j++){
			if(a[j]==b[be]){//公共子序列
				be++,len++;
			}
		}
		mx=max(mx,len);//最大公共子序列
	}		
	cout<<la+lb-mx<<endl;
}
int t;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：HsNu1ly7_ (赞：0)

## 题意

给你两个字符串 $a$ 和 $b$，求出一个长度尽可能短的字符串,使得 $a$ 是这个字符串的子串，$b$ 是这个字符串的子序列，输出这个字符串最短的长度。

## 思路

考虑到 $a$ 是最终答案的子串，所以最终的答案如下

$$
ans = lena + (lenb - temp)
$$

其中，$ans$ 代表最终答案，$temp$ 表示字符串 $b$ 在 $a$ 中的最长子序，$lena$ 表示字符串 $a$ 的长度，$lenb$ 表示字符串 $b$ 的长度。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
void solve (){
	string a , b ;
	cin >> a >> b ;
	int temp = -200000000 ;
	int al = a.length() , bl = b.length() ;
	for ( int i = 0 ; i < bl ; i++ ){
		int sum = 0 ;
		int idx = i ;
		for ( int j = 0 ; j < al ; j++ ){
			if ( a[j] == b[idx]){
				++idx ;
				++sum ;
			}
		}
		temp = max ( temp , sum ) ;
	}
	int ans = al + ( bl - temp ) ;
	cout << ans << '\n' ;
	return ;
}
signed main (){
	ios::sync_with_stdio(0) ;
	cin.tie(0) ;
	cout.tie(0) ;
	int _ ;
	cin >> _ ;
	while ( _-- ){
		solve () ;
	}
	return 0 ;
}
```

---

## 作者：GeYang (赞：0)

# 题意

给你两个字符串，要求构造出一个完全包含这两个字符串的字符串，求这个字符串的最小长度。

# 思路

结果一定是这两个字符串的长度之和减去最大公共子序列的长度。

因为数据范围较小，所以直接遍历最大公共子序列即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string str1,str2;
void solve()
{
	cin>>str1>>str2;
	int ans=0;
	for(int i=0; i<str2.length(); i++)
	{
		int bm=0;
		for(int j=0; i+ans<str2.length()&&j<str1.length(); j++)
		{
			if(str1[j]==str2[i+bm])
			{
				bm++;
			}
		}
		ans=max(bm,ans);
	}
	cout<<str1.length()+str2.length()-ans<<endl;
} 
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		solve();
	}
}
```

---

