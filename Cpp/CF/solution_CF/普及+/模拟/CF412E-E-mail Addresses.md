# E-mail Addresses

## 题目描述

One of the most important products of the R1 company is a popular @r1.com mail service. The R1 mailboxes receive and send millions of emails every day.

Today, the online news thundered with terrible information. The R1 database crashed and almost no data could be saved except for one big string. The developers assume that the string contains the letters of some users of the R1 mail. Recovering letters is a tedious mostly manual work. So before you start this process, it was decided to estimate the difficulty of recovering. Namely, we need to calculate the number of different substrings of the saved string that form correct e-mail addresses.

We assume that valid addresses are only the e-mail addresses which meet the following criteria:

- the address should begin with a non-empty sequence of letters, numbers, characters '\_', starting with a letter;
- then must go character '@';
- then must go a non-empty sequence of letters or numbers;
- then must go character '.';
- the address must end with a non-empty sequence of letters.

You got lucky again and the job was entrusted to you! Please note that the substring is several consecutive characters in a string. Two substrings, one consisting of the characters of the string with numbers $ l_{1},l_{1}+1,l_{1}+2,...,r_{1} $ and the other one consisting of the characters of the string with numbers $ l_{2},l_{2}+1,l_{2}+2,...,r_{2} $ , are considered distinct if $ l_{1}≠l_{2} $ or $ r_{1}≠r_{2} $ .

## 说明/提示

In the first test case all the substrings that are correct e-mail addresses begin from one of the letters of the word agapov and end in one of the letters of the word com.

In the second test case note that the e-mail x@x.x is considered twice in the answer. Note that in this example the e-mail entries overlap inside the string.

## 样例 #1

### 输入

```
gerald.agapov1991@gmail.com
```

### 输出

```
18
```

## 样例 #2

### 输入

```
x@x.x@x.x_e_@r1.com
```

### 输出

```
8
```

## 样例 #3

### 输入

```
a___@1.r
```

### 输出

```
1
```

## 样例 #4

### 输入

```
.asd123__..@
```

### 输出

```
0
```

# 题解

## 作者：wxzzzz (赞：4)

### 题意

给定一个字符串 $s$，求有多少 $s$ 的子串满足要求。

### 思路

每个合法字符串显然至少要有一个 `@` 符号，因此，可以遍历字符串，每当遇到一个 `@`，就先扩展其前缀，然后找到当前 `@` 后面第一个 `.`，扩展 `.` 后面的后缀，最后当前 `@` 能扩展出的合法子串数量就是前缀长度乘上后缀长度。

扩展时还需特判如果当前 `@` 下一个字符就是 `.`、`@` 或 `_`，则当前 `@` 能扩展出的合法子串数量为 $0$。

记得开 long long！

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, ans, now, cntl, cntr;
char s[1000005];
int main() {
    scanf("%s", s + 1), n = strlen(s + 1);

    for (long long i = 1; i <= n; i++) {
        if (s[i] != '@')
            continue;

        now = i, cntl = cntr = 0;

        while (s[now - 1] != '.' && s[now - 1] != '@' && now > 1)
            now--, cntl++;

        for (long long j = now; j < i; j++)
            if (s[j] < 'a' || s[j] > 'z')
                cntl--;

        now = i;

        if (s[now + 1] == '.')
            continue;

        while (s[now] != '.' && s[now + 1] != '@' && s[now + 1] != '_' && now < n)
            now++;

        if (s[now + 1] == '@' || s[now + 1] == '_')
            continue;

        while ((s[now + 1] >= 'a' && s[now + 1] <= 'z') && now < n)
            now++, cntr++;

        ans += cntl * cntr;
    }

    cout << ans;
    return 0;
}
```

---

## 作者：AKPC (赞：2)

### 思路
暴力模拟题，不愧是 $\texttt {CodeForces}$ 评定 $1900$ 难度的 $\texttt E$ 题啊。

我们可以先找一个标识符，比如 `@`，当然 `.` 也一样。然后暴力扩展前缀后缀，如果不合法就退出即可，然后如果后缀计数器 $y$ 搜到 `.` 就需要用一个新计数器 $z$，当然如果在搜到 `.` 之前就有不合法，那么显然这一段的答案为 $0$ 直接退出。。注意前缀需要额外统计开头为小写字母的个数，计数器设为 $x$，因为 $A$ 字符串**开头必须由小写字母引导**。

统计最后答案，如果没有在搜后缀时搜到 `.`，答案为 $0$ 反之每段的答案就是 $x\times z\times\min\{1,y\}$。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,ans;
string a;
signed main(){
	cin>>a,n=a.length();
	for (int i=0;i<n;i++)
		if (a[i]=='@'){
			int x=0,y=0;
			for (int j=i-1;j>=0&&a[j]!='.'&&a[j]!='@';j--) if (a[j]<='z'&&a[j]>='a') x++;
			for (int j=i+1;j<n&&a[j]!='.'&&a[j]!='@'&&a[j]!='_';j++) y++;
			if (y==0) continue;
			if (a[i+y+1]!='.') continue;
			int z=0;
			for (int j=i+y+2;j<n&&a[j]<='z'&&a[j]>='a';j++) z++;
			ans+=x*z;
		}
	cout<<ans;
	return 0;
}
```


---

## 作者：AutumnQ (赞：1)

这是一道大模拟。

# 题意简述
给定一个字符串 $s$，求满足形如“电子邮箱”的子串数量。

# 题目做法
首先，先找一个特殊字符```@```，稍后作为扩展的字符。

由```@```先向左扩展子串。查找仅含有字母、数字以及下划线的子串。但是**注意：只有首位为字母的才能对答案贡献。**

```cpp
int l=i-1,r=i+1;
int times1=0,times2=0;
while((isalpha(s[l]) || isdigit(s[l]) || s[l]=='_') && l>=0){
	if(isalpha(s[l]))times1++;
	l--;
}
```
接下来向右查找字符```.```，如果中途```@```到```.```的子串有除小写字母和数字以外的字符，贡献为 $0$，直接退出。

```cpp
while((isalpha(s[r]) || isdigit(s[r]) || s[r]=='.') && r<=SIZE){
	if(s[r]=='.'){
		flg=true;
		r++;
		break;
	}
	r++;
}
if(!flg)continue;
```

接下来判断```.```后面是否合法。查找到除小写字符就退出。

```cpp
while(isalpha(s[r]) && r<=SIZE+1){
	r++;
	times2++;
}
```

最后对答案能产生 $times_1 \times times_2$ 的贡献。

# 特判
如果你 WA on #26，那么你可以看看下面这句话。

```helloworld@.```中```@```和```.```相连是不合法的。

# 代码
下面放出全部代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
 
string s;
int SIZE;
int ans;

signed main(){
	getline(cin,s);
	SIZE=s.size();
	s=" "+s;
	for(int i=1;i<=SIZE;i++){
		if(s[i]!='@')continue;
		int l=i-1,r=i+1;
		int times1=0,times2=0;
		while((isalpha(s[l]) || isdigit(s[l]) || s[l]=='_') && l>=0){
			if(isalpha(s[l]))times1++;
			l--;
		}
		bool flg=false;
		if(s[r]=='.')continue;
		while((isalpha(s[r]) || isdigit(s[r]) || s[r]=='.') && r<=SIZE){
			if(s[r]=='.'){
				flg=true;
				r++;
				break;
			}
			r++;
		}
		if(!flg)continue;
		while(isalpha(s[r]) && r<=SIZE+1){
			r++;
			times2++;
		}
		ans+=times1*times2;
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：RE_Prince (赞：1)

# CF412E E-mail Addresses

[link](https://www.luogu.com.cn/problem/CF412E)

## 思路

因为 $|S|\leq 10^6$，因此只能是 $O(|S|)$ 或 $O(|S|\log |S|)$ 的复杂度。显然 $\log$ 不可行，因为此题中并不需要排序或二分。所以考虑线性复杂度。

注意到，邮箱地址必须包含一个 `@` 和一个 `.`，且按这两个字符把一个邮箱地址分成三段，每段都有自己的字符要求。因此我们可以按照这两个字符把整个字符串分成若干段并记录这些段的结尾。这样只需线性扫一遍相邻的三个段 $i,i+1,i+2$ 并判断这三段是否分别满足题目中的要求。当然，要处理第一段的结尾和第二段的结尾是否为 `@` 和 `.`。为了保证复杂度，我们预处理每段是否有数字和下划线，并记录每段有多少个字母。

但是这会出现一个问题。在处理最后一段 $i+2$ 时，字母的数量不一定是最后一段能选的线段数量。如果在一堆字母后出现一个数字或一个下划线，那结尾在这个字符之后的线段就都废了。因此我们再记录每个段开始有多少个连续的字母。最后答案就是：第一段字母的数量乘最后一段开始连续字母的数量。第二段对答案没有贡献，因为不管第一段和最后一段怎么选开头和结尾，中间这段一定是都选的。但这也说明，第二段不满足条件的话，第一段和第三段怎么选也不会满足条件。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,i,j,k,ans,pos1,pos2,c1,c2,cnt;
string s;
int a[1000009],b[1000009],c[1000009];//at and dot
bool y[1000009],z[1000009];//number underline
int r[1000009],t[1000009];
int seg=1;
signed main()
{
	cin>>s;
	int ll=s.size();
	for(i=0;i<ll;i++) 
	{
		if(isdigit(s[i])) y[seg]=1;
		if(s[i]=='_') z[seg]=1;
		if(isalpha(s[i])) c[seg]++;
		if(isalpha(s[i])&&!z[seg]&&!y[seg]) t[seg]++;
		if(s[i]=='@'||s[i]=='.'||i==ll-1) 
		{
			if(i==ll-1) r[seg]=i;
			else r[seg]=i-1;
			if(i!=ll-1) seg++;
		}
	}
//	for(i=1;i<=seg;i++) cout<<r[i]<<" ";
	for(i=1;i<=seg-2;i++)
	{
		if(z[i+1]||s[r[i]+1]!='@'||s[r[i+1]+1]!='.'||abs(r[i]-r[i+1])==1||abs(r[i+1]-r[i+2])==1) continue;
		ans=ans+(c[i]*t[i+2]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
首先找出每个相邻的 `@` 和 `.` 的位置，然后判断 `@` 和 `.` 之间是否合法，若合法，枚举 `@` 前的连续的仅由小写字母、数字和下划线构成的最长子串，并数出其中的小写字母的个数 $s1$ 作为开头，再枚举 `.` 后面的仅由小写字母构成的最长子串，并数出其中的小写字母个数 $s2$ 作为结尾，然后根据乘法原理，这一对 `@` 和 `.` 能构成的“电子邮箱”就是 $s1\times s2$。此外，`@` 和 `.` 之间没有任何字符的情况需要特判。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
string a;
int n, at = -1, l, r;
vector <pii> v;
ll sum;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> a;
	n = a.size ();
	for (int i = 0; i < n; ++ i)
		if (a[i] == '@')
			at = i;
		else if (a[i] == '.' && ~ at)
			v.push_back ({at, i}), at = -1;
	for (pii &i : v) {
		if (i.first + 1 >= i.second)
			continue ;
		for (int j = i.first + 1; j < i.second; ++ j)
			if (a[j] == '_')
				goto end;
		l = r = 0;
		for (int j = i.first - 1; ~j; -- j)
			if (a[j] == '.' || a[j] == '@')
				break ;
			else if (a[j] >= 'a' && a[j] <= 'z')
				++ l;
		for (int j = i.second + 1; j < n; ++ j)
			if (a[j] < 'a' || a[j] > 'z')
				break ;
			else
				++ r;
		sum += (ll) l * r;
end:
		;
	}
	cout << sum;
	return 0;
}
```

---

## 作者：5ab_juruo (赞：0)

首先找 `@`，`.` 字符（令其为特殊字符），找到一个 `.` 且上一个特殊字符是 `@`，然后找 `@` 之前的合法后缀数，`.` 之后的合法前缀数，乘起来即可。

显然一个区间最多只会被遍历两次（`.xxxxx@`），所以复杂度线性。

注意 `@` 和 `.` 中间的部分也要判非空和字符集合法性。

```cpp
/* name: CF412E
 * author: 5ab
 * created at: 22-02-08 16:36
 */
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

typedef long long ll;
const int max_n = 1000000;

char s[max_n+1];

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> s;
	int n = strlen(s), lstp = -1, adp = -1, ttmp;
	ll tmp, ans = 0;
	
	for (int i = 0; i < n; i++)
	{
		if (s[i] == '@')
		{
			if (adp != -1)
				lstp = adp;
			adp = i;
		}
		else if (s[i] == '.')
		{
			if (adp != -1)
			{
				tmp = 1;
				for (int j = adp + 1; j < i; j++)
					if (!isdigit(s[j]) && !islower(s[j]))
					{
						tmp = 0;
						break;
					}
				if (tmp && i - adp > 1)
				{
					ttmp = 0;
					for (int j = adp - 1; j > lstp; j--)
					{
						if (islower(s[j]))
							ttmp++;
						else if (!isdigit(s[j]) && s[j] != '_')
							break;
					}
					tmp *= ttmp, ttmp = 0;
					for (int j = i + 1; j < n; j++)
					{
						if (islower(s[j]))
							ttmp++;
						else
							break;
					}
					tmp *= ttmp;
					ans += tmp;
				}
			}
			lstp = i, adp = -1;
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
```

---

## 作者：Graph_Theory (赞：0)

### 思路

对于每一个电子邮件中，一定且只包含一个 `@` 和 `.` 并且有顺序。

统计每一个邮件时，先找到一个 `@` 和 `.` 此时对于每一个 `@` 和 `.` 中，答案为左边合法字符和右边合法字符的乘积。

对于由 `@` 和 `.` 分段的 $3$ 个字符串中，要判断每一串是否合法。

对于左边的串，要保证地址的开头为小写字母，所以左边合法字符的数量为左边小写字母的数量。其中，小写字母到 `@` 中只存在下划线和数字。

对于中间的串，要保证中间只存在下划线和数字。

对于右边的串，要保证仅由小写字母构成。所以右边合法字符的数量为右边字符串的长度。

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
char s[1000010];
int len,ans=0,lef=0,rig=0;
signed main()
{
	cin>>(s+1);
	len=strlen(s+1);
	for(int i=1;i<=len;i++)
	{
		if(s[i]!='@' ) continue;
		int now=i,lef=0,rig=0;
		//左串
		while(s[now-1]!='@' && s[now-1]!='.' && now >1)
		{
			now--,lef++;
			if(s[now]<'a' ||s[now]>'z' ) lef--;
		}
		//中间串
		now=i;
		if(s[now+1]=='.') continue;
		while(s[now+1]!='@' && s[now]!='.' && s[now+1]!='_' && now <len) now++;
		if(s[now+1]=='@'||s[now+1]=='_') continue;
		//右串
		while( (s[now+1]>='a' &&s[now+1]<='z' )&& now <len) now++,rig++;
		ans+=lef*rig;
	}
	
	cout<<ans;
	return 0;
}
```

---

