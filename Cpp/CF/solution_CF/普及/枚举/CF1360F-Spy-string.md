# Spy-string

## 题目描述

You are given $ n $ strings $ a_1, a_2, \ldots, a_n $ : all of them have the same length $ m $ . The strings consist of lowercase English letters.

Find any string $ s $ of length $ m $ such that each of the given $ n $ strings differs from $ s $ in at most one position. Formally, for each given string $ a_i $ , there is no more than one position $ j $ such that $ a_i[j] \ne s[j] $ .

Note that the desired string $ s $ may be equal to one of the given strings $ a_i $ , or it may differ from all the given strings.

For example, if you have the strings abac and zbab, then the answer to the problem might be the string abab, which differs from the first only by the last character, and from the second only by the first.

## 说明/提示

The first test case was explained in the statement.

In the second test case, the answer does not exist.

## 样例 #1

### 输入

```
5
2 4
abac
zbab
2 4
aaaa
bbbb
3 3
baa
aaa
aab
2 2
ab
bb
3 1
a
b
c```

### 输出

```
abab
-1
aaa
ab
z```

# 题解

## 作者：Warriors_Cat (赞：3)

## CF1360F

### $Description:$

有 $n$ 个长度为 $m$ 的字符串 $a_{1...n}$，请找到一个长度为 $m$ 的字符串 $S$，满足 $\forall k \in [1, n]$， $\sum_{i=1}^m[a_{k, i} \neq S_i] \le 1$。如果没有就输出 $-1$。

### $Preface:$

一开始以为这是一道神仙题，不过看到 $t \le 100$，$n \le 10$，$m \le 10$ 这样小的数据范围，就想到了暴力......

### $Solution:$

考虑直接暴力。每次把 $a_1$ 的所有可能是答案的字符串给枚举一遍，然后判断这个字符串和 $a_2, a_3, ... a_n$ 是不是可匹配的。最后如果什么都找不到就直接输出 $-1$ 了。

时间复杂度为 $O(tnm^2)$，加上一个 $26$ 的常数。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
int t, n, m;
string s[20];
inline bool check(string ans){
	for(int i = 2; i <= n; ++i){
		int cnt = 0;
		for(int j = 1; j <= m; ++j){
			if(ans[j] != s[i][j]) cnt++;
		}
		if(cnt > 1) return 0;
	}
	return 1;
}
int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) cin >> s[i], s[i] = '$' + s[i];
		string ans = s[1];
		bool flag = 0;
		for(int i = 1; i <= m; ++i){
			for(char j = 'a'; j <= 'z'; ++j){
				char ch = ans[i];
				ans[i] = j;
				if(check(ans)){
					flag = 1;
					break;
				}
				ans[i] = ch;
			}
			if(flag) break;
		}
		if(flag){
			for(int i = 1; i <= m; ++i) printf("%c", ans[i]);
			printf("\n");
		}
		else printf("-1\n");
	}
	return 0;
}
```


---

## 作者：_•́へ•́╬_ (赞：2)

### 题意简述

給你 $n$ 个长度为 $m$ 的字符串。

请你找到一个字符串：它和每个给定的字符串之间的差不超过 $1$。

給一下“差”的定义：两个长度相等的字符串中不同的字符的个数。（是逐位比较，不是LCS）

### 思路

很简单。

- 一种情况：你找到的字符串就在给定的字符串当中。这个你枚举每个字符串就行了。

- 还有一种情况：你把**第一个**字符串改动一个字符。你要枚举改动哪个字符和改成什么字符。

  解释一下为什么只要改第一个字符串：如果你改第一个字符串都找不到解，那你改别的字符串得到的结果与第一个字符串之间的差肯定超过 $1$。希望大家能自己弄明白。

### $code$

```cpp
#include<stdio.h>
inline void read(int&x)
{
	register char c=getchar();for(;c<'0'||'9'<c;c=getchar());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=getchar());
}
int t,n,m;char a[10][11],s[11];bool ok;
bool jg(char*a,char*b)//judge:a==b?
{
	register int cnt=0;
	for(register int i=0;i<m;++i)if(a[i]!=b[i])++cnt;
	return cnt<=1;
}
main()
{
	for(read(t);t--;)
	{
		read(n);read(m);for(register int i=0;i<n;++i)scanf("%s",a[i]);
		/*            don't change
		 *try:a[i]--------------------->s
		 */
		for(register int i=0;i<n;++i)//try:s==a[i]
		{
			sprintf(s,"%s",a[i]);//copy a[i]->s
			ok=1;
			for(register int j=0;j<n;++j)if(!jg(a[j],s)){ok=0;break;}
			if(ok){puts(s);goto end;}
		}
		/*          change one letter
		 *try:a[0]---------------------->s
		 */
		for(register int i=0;i<m;++i)//try:change a[0][i]
			for(register int j='a';j<='z';++j)if(a[0][i]!=j)//try:change a[0][i] to j
			{
				sprintf(s,"%s",a[0]);s[i]=j;
				ok=1;
				for(register int j=0;j<n;++j)if(!jg(a[j],s)){ok=0;break;}
				if(ok){puts(s);goto end;}
			}
		puts("-1");//no solution
		end:;
	}
}
```



---

## 作者：sxshm (赞：1)

# Spy-string
[题目链接](https://www.luogu.com.cn/problem/CF1360F)

[codeforces 原站网址](https://codeforces.com/problemset/problem/1360/F)

## 分析
这道题乍一看像是最长公共子序列，可仔细一看：同一下标。这道题瞬间简单了不少（~~不就是暴力吗~~），开始做题。
### 一.怎么暴力
因为是两个任意字符串的距离，所以可以直接用第一个字符串来暴力枚举所有可能的答案，然后的事情交给 $\operatorname{check}$ 函数。
### 二.$\operatorname{check}$ 函数
扫一遍所有的字符串（除了第一个），将修改过的 $s_{1}$ 与 $s_{i}$ 比较，如果“距离”大于 $1$，直接返回 $\operatorname{false}$，全部扫完后返回 $\operatorname{true}$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,m;
string s[50];
bool check(string x){
	for(int i=2;i<=n;i++){//扫一遍除了第一个的所有字符串
		int cont=0;
		for(int j=0;j<m;j++){
			if(x[j]!=s[i][j]) cont++;//记录不一样的个数
		}
		if(cont>1) return false;//如果“距离”大于，直接返回false
	}
	return true;//扫完返回true
}
int main(){
	scanf("%d",&t);
	while(t--){
		bool flag=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++) cin>>s[i];
		for(int i=0;i<m;i++){//暴力枚举第i位被修改
			for(char j='a';j<='z';j++){//枚举第i位修改后的
				swap(s[1][i],j);//修改
				if(check(s[1])){//判断是否符合要求
					flag=1;	//标记为符合
					break;//直接跳出，不用复原
				}
				swap(s[1][i],j);//复原
			}
			if(flag) break;
		}
		if(flag){
			cout<<s[1]<<"\n";//输出未复原的ans
		}else{
			printf("-1\n");//没找到输出-1
		}
	}
	return 0;
}

```
**完结撒花~~~**

---

## 作者：KellyFrog (赞：1)

先%楼上dalao。

事实上直接进行搜索即可AC，因为中间有字符串之间差值的限定，所以常数会很小，硬说的话大概是$nm^2$的样子（口胡的）

所以我们直接Dfs就好啦！

code:
```cpp
#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 15;

string str[MAXN];
int diff[MAXN], n, m;
bool solve = false;

void Dfs(string cur, int pos) {
	if(solve) {
		return;
	}
	bool vis[27] = {0}, flag = false;
	for(int i = 1; i <= n; i++) {
		flag = false;
		char ch = str[i][pos];
		if(!vis[ch - 'a']) {
			vis[ch - 'a'] = true;
			for(int j = 1; j <= n; j++) {
				if(str[j][pos] != ch) {
					diff[j]++;
					if(diff[j] == 2) { //有一个字符串超过两个不一样了 
						flag = true;
					}
				}
			}
			if(!flag) {
				if(pos == m - 1) {
					cout<< cur << ch << endl;
					solve = true;
					return;
				}
				Dfs(cur + ch, pos + 1);
			}
			//后面别忘了把diff减回去 
			for(int j = 1; j <= n; j++) {
				if(str[j][pos] != ch) {
					diff[j]--;
				}
			}
		}
	}
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		solve = false;
		cin >> n >> m;
		for(int i = 1; i <= n; i++) {
			cin >> str[i];
			diff[i] = 0; 
		}
		Dfs("", 0);
		if(!solve) {
			cout << -1 << endl;
		}
	}
	return 0;
}
```

---

## 作者：PikachuQAQ (赞：1)

## Description
[Link](https://www.luogu.com.cn/problem/CF1360F)

## Solution

$1 \leq n \leq 10$，考虑暴力。

将每一组第一个字符串的每一位都更换一次从 $a$ 到 $z$ 的字母，再检查带入整组检查合法性（差不为 $1$）即可。

## Code

```cpp
#include <iostream>

using namespace std;

const int kMaxN = 17;

string s[kMaxN], k;
int t, n, m;
bool f;

bool check(string p) {
    int k;
	for (int i = 2; i <= n; i++, k = 0) {
		for (int j = 0; j < m; j++) {
            (s[i][j] != p[j]) && (k++);
        }
		if (k > 1) return 0;
	}
	return 1;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for (cin >> t; t; t--, f = 0, k = "") {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
            cin >> s[i];
        }
		for (int i = 0; i < m && !f; i++) {
			for (int j = 0; j < 26 && !f; j++) {
				k = s[1], k[i] = 'a' + j, (check(k)) && (f = 1);
			}
	    }
        cout << (f ? k : "-1") << '\n';
	}

	return 0;
}
```


---

## 作者：xujunlang2011 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1360F)

## 思路

看到数据范围 $n, m\leq10$，所以可以直接暴搜枚举改动的字符。

先枚举更换的位置，再枚举更换的字符 `a` 到 `z`，然后检查新字符串的正确性。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int n, m, a[15];
string s[15];
bool F = 0;
void dfs(int k, string st)
{
    if (F)
    {
	    return;
    }
    bool f = 0;
    for (int i = 1;i <= n;i++)
    {
	    if (a[i] >= 2)
	    {
	        f = 1;
	    }
	}
	if (f)
	{
	    return;
	}
	if (k == m)
	{
	    cout << st << "\n";
	    F = 1;
	}
	bool t[260];
	for (int i = 1;i <= 256;i++)
	{
	    t[i] = 0;
	}
	for (int i = 1;i <= n;i++)
	{
	    if (!t[s[i][k + 1]])
	    {
            t[s[i][k + 1]] = 1;
            for (int j = 1;j <= n;j++)
            {
                if (s[j][k + 1] != s[i][k + 1])
                {
                    a[j]++;
                }
            }
            dfs(k + 1, st + s[i][k + 1]);
            for (int j = 1;j <= n;j++)
            {
                if (s[j][k + 1] != s[i][k + 1])
                {
                    a[j]--;
                }
            }
        }
	}
}
int main()
{
    int t;
    cin >> t;
    for (int ti = 1;ti <= t;ti++)
    {
    	cin >> n >> m;
    	F = 0;
    	for (int i = 1;i <= 10;i++)
    	{
    	    a[i] = 0;
    	}
    	for (int i = 1;i <= n;i++)
        {
            cin >> s[i];
            s[i] = " " + s[i];
        }
        dfs(0, "");
        if (!F)
        {
            cout << -1 << "\n";
        }
    }
    return 0;
}
```


---

## 作者：U_star (赞：0)

[CF原题](https://codeforces.com/contest/1360/problem/F)

[洛谷](https://www.luogu.com.cn/problem/CF1360F)

Virtual participation 秒切，很水的一道题。

此题大意：给你 $n$ 个长度 $m$ 的字符串 $A_1,A_2......A_n$，你需要构造一个长度 $m$ 的字符串，使这个构造的字符串与题目给出的所有字符串之差不超过 $1$。

思路 $1$：枚举所有长度为 $m$ 的字符串。

时间复杂度 $O(26^m)$，超时。

思路 $2$：尝试对字符串 $A_1$ 的每个字符依次进行修改，并与其他串比较。

具体来说，假如我们现在在修改字符串 $A_1$ 的第 $i$ 位，我们可以依次尝试将这一位改为 $A_2,A_3......A_n$ 的第 $i$ 位，并在修改后依次与 $A_2,A_3......A_n$ 进行比较。

时间复杂度为 $O(m^2 n^2)$，可以通过此题。

注意：我们也可以不对 $A_1$ 进行修改，一定要考虑到这种特殊情况，不然会 WA。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
string a[15],s;
bool spy(string a,string b)
{
	int sum=0;
	for(int i=0;i<m;i++)
		if(a[i]!=b[i])
		sum++;
	if(sum<=1)
	return 1;
	return 0;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		cin>>a[i];
		s=a[1];
		for(int i=0;i<m;i++)//i为当前尝试修改的下标
		{
			for(int j=1;j<=n;j++)//尝试将这一位修改为a[j]的第i位，注意j要从1开始枚举
			{
				s[i]=a[j][i];
				for(int k=1;k<=n;k++)//依次与其他所有串进行比较
				{
					if(spy(a[k],s)==0)
					break;
					else if(k==n)
					{
						cout<<s<<"\n";
						goto s1;
					}
				}
			}
			s[i]=a[1][i];//最后别忘了改回来
		}
		cout<<"-1\n";
		s1:1;
	}
	return 0;
}
```


---

## 作者：Infinite_Loop (赞：0)

# CF1360F
## 题意
给定 $n$ 个长度为 $m$ 的字符串，找到一个长度为 $m$，且与这 $n$ 个字符串不同字符的数量小于等于 $1$。
## 思路
因为 $t \le 100$ ，$n \le 10$，$m \le 10$，可以使用暴力。

枚举所有与 $a _ {1}$ 相等或仅相差一个字符的字符串，与剩下 $n-1$ 个字符串进行比较是否符合。如果一个也找不到就输出 $-1$。

时间复杂度为 $O(tnm^2)$，再加上一个 $26$ 的常数。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,flag;
string s[15],ans;
void solve(int step,string str){
	if(step==n+1){
		flag=1;
		ans=str;
		return;
	}else if(step==1){
		string temp=s[1];
		solve(step+1,temp);
		for(int i=0;i<m;i++){
			for(char ch='a';ch<='z';ch++){
				temp[i]=ch;
				str=temp;
				solve(step+1,str);
				if(flag)return;
				temp=s[1];
			}
		}
	}else{
		int cnt=0;
		for(int i=0;i<m;i++){
			if(s[step][i]!=str[i])cnt++;
			if(cnt>=2)return;
		}
		if(cnt>=2)return;
		else solve(step+1,str);
		if(flag)return;
	}
}
int main(){
	cin>>t;
	while(t--){
		flag=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++)cin>>s[i];
		string ss="";
		solve(1,ss);
		if(flag)cout<<ans<<'\n';
		else cout<<-1<<'\n';
	}
	return 0;
}
```


---

