# [JRKSJ R8] 三七二十一

## 题目描述

给你一个由 $1\sim 9$ 的数字组成的数字串 $s$。定义一个数字串 $s$ 表示的数为将其看作十进制数得到的数。形式化地说，长为 $n$ 的数字串 $s$ 表示的数是 $\sum_{i=1}^n  10^{n-i}s_i$。

你可以对这个数字串执行若干次操作，每次操作中你可以选定一个位置 $1\le p\le n$ 并将 $s_p$ 修改为任意 $1\sim 9$ 中的数字。你需要使该数字串**不存在**任何一个非空子串满足这个子串表示的数字是 $2^k(k\in \N)$ 即 $2$ 的任意**非负整数**次幂，请你求出最少的操作次数。

## 说明/提示

### 样例解释

对于样例 $1$，满足表示的数是 $2$ 的非负整数次幂的 $s$ 的非空子串有 $2,4,8$，将 $s$ 修改为 $5963$ 是最优解之一。

对于样例 $2$，满足表示的数是 $2$ 的非负整数次幂的 $s$ 的非空子串有 $1,4,16,64$，将 $s$ 修改为 $666$ 是最优解之一。


### 数据规模与约定
**本题采用捆绑测试。**

令 $n=|s|$。

| $\text{Subtask}$ | $n\le $ | 分值 |
| :----------: | :----------: | :----------: |
| $1$ | $4$ | $10$ |
| $2$ | $8$ | $10$ |
| $3$ | $17$ | $20$ |
| $4$ | $10^3$ | $20$ |
| $5$ | $10^6$ | $40$ |

对于 $100\%$ 的数据，$1\le n\le 10^6$，$s$ 由 $1\sim 9$ 的数字组成。

## 样例 #1

### 输入

```
2468```

### 输出

```
3```

## 样例 #2

### 输入

```
164```

### 输出

```
2```

## 样例 #3

### 输入

```
65535```

### 输出

```
0```

# 题解

## 作者：Little_x_starTYJ (赞：11)

### 解题思路
为了不让数字串中出现 $2$ 的非负整数次幂，那么 $1,2,4,8$ 必须得删去，于是写出了以下代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int ans;
signed main() {
	ios::sync_with_stdio(false);
	string a;
	cin >> a;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == '1' || a[i] == '2' || a[i]== '4' || a[i] == '8')
			ans++;
	}
	cout << ans;
	return 0;
}
```
交上去发现只有 $10$ 分。为什么只有 $10$ 分？会不会有特殊情况？于是打了一个表，发现 $2^k(k\in \N)$ 只有 $65536$ 不包含 $1,2,4,8$，所以我们还需要单独处理 $65536$。需要注意的是，对于两个重叠的 $65536$，我们只需要删掉 $1$ 个数，例如 $655365536$，我们只需要删除最中间的 $6$。

AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int ans;
signed main() {
	ios::sync_with_stdio(false);
	string a;
	cin >> a;
	for (int i = 0; i < a.size(); i++) {
        if (a[i] == '6' && a[i + 1] == '5' && a[i + 2] == '5' && a[i + 3] == '3' && a[i + 4] == '6')
            ans++, i += 4;
    }
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == '1' || a[i] == '2' || a[i]== '4' || a[i] == '8')
			ans++;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：tyccyt (赞：3)

# P10571 [JRKSJ R8] 三七二十一 题解

## 骗分

个人认为这一部分极具正解引导性。

首先有一个比较好的暴力，即**只**消除单个字符组成的 $2$ 的任意非负数次幂，因为这些都是必须替换的数。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int main()
{
	cin>>s;
	int len=s.size(),cnt=0;
	for(int i=0;i<len;i++)
	{
		int t=log2(s[i]-'0');
		if((1<<t)==s[i]-'0')
		{
			cnt++;
		}
	}
	cout<<cnt;
	return 0;
}
```

这个只能得 $10$ 分。

## 正解

考虑题目是如何卡 $10$ 分骗分做法的？

于是打个判断，找出所有 $2$ 的非负整数次幂每一位都**不含** $2$ 的非负整数次幂的数。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t=1;
int book[11]; 
int main()
{
	for(int i=1;t<10000000;i++)
	{
		int flag=0;
		long long x=t;
		while(x)
		{
			int e=log2(x%10);
			if((1<<e)==x%10)
			{
				flag=1;
			}
			x/=10;
		}
		if(flag==0)cout<<t<<' ';
		t*=2;
	}
	return 0;
}
```

结果是令人惊讶的！！！

```c
65536 
```

只有这一个数**不包含** $2$ 的非负整数次幂同时是2的非负整数次幂！！！

那么就在 $10$ 分骗分代码之上再特判一下 $65536$，将它删去，即它换成 $65537$ 或 $75536$ 等更改一个数其不是 $2$ 的非负整数次幂的数。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int main()
{
	cin>>s;
	int len=s.size(),cnt=0;
	for(int i=0;i<len;i++)
	{
		int t=log2(s[i]-'0');
		if((1<<t)==s[i]-'0')
		{
			cnt++;
			s[i]='9';
		}
	}
	for(int i=0;i+4<len;i++)
	{
		if(s[i]=='6'&&s[i+1]=='5'&&s[i+2]=='5'&&s[i+3]=='3'&&s[i+4]=='6')
		{
			cnt++;
			s[i+4]='7';
		}
	}
	cout<<cnt;
	return 0;
}
```

一道好题~~

有问题请指出----

---

## 作者：dlzlj_2010 (赞：2)

注意到 $2^k(k\in\N)$ 除 $65536$ 外均含有 $1,2,4,8$，所以删掉 $1,2,4,8$ 后再特判一下 $65536$ 即可。
## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

signed main(){
	string s;
	cin>>s;
	int cnt=0;
	for(int i=0;i<s.size();i++){
		switch (s[i]) {//1,2,4,8。
			case '1':case'2':case'4':case'8':cnt++;
		}
		if(i>=4&&s[i-4]=='6'&&s[i-3]=='5'&&s[i-2]=='5'&&s[i-1]=='3'&&s[i]=='6')//特判 65536。
		{
			cnt++;
			if(i+5<=s.size()&&s[i]=='6'&&s[i+1]=='5'&&s[i+2]=='5'&&s[i+3]=='3'&&s[i+4]=='6')//出现 655365536，只需删中间的 6 ，所以跳过去即可。
            			i=i+4;
		}
	}
	cout<<cnt;
    return 0;
}
```

---

## 作者：dulinfan2023 (赞：2)

## 题意：

有一个字符串，仅由 $1 \sim 9$ 的数字组成。

要进行 $n$ 次操作以后，是每个**非空字串**都不是 $2^x(x \in \N)$ 并使 $n$ 最小。

## 思路：

仅仅一位数的二次幂有 $1,2,4,8$，所以如果遇到 $1,2,4,8$，给答案加上 $1$。

找到不含 $1,2,4,8$ 的二次幂，发现只有为 $65536$，如果遇到 $65536$，那么也给答案加 $1$，而且记得给个位覆盖掉哦。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
#define debug() cout<<"come on"<<'\n'
signed main(){
	string s;
	cin>>s;
	int cnt=0;//统计变量
	for(int i=0;i<s.size();i++){
		if(s[i]=='1'||s[i]=='2'||s[i]=='4'||s[i]=='8'){
			cnt++;
		}
		if(s[i]=='6'&&s[i+1]=='5'&&s[i+2]=='5'&&s[i+3]=='3'&&s[i+4]=='6'){
			cnt++;
			s[i+4]='5';//覆盖
		}
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：LostKeyToReach (赞：1)

更新：修复了一处重大错误。

注意到除了删 $1,2,4,8$ 以外，还要特判 $65536$。

可以证明，在 $2^{31000}$ 内，任意 $2$ 的非负整数次幂只有 $2^{16}$ 不包含 $1,2,4,8$。

具体证明可以看 irris 在讲课时推送的[链接](https://math.stackexchange.com/questions/957447/why-is-216-65536-the-only-power-of-2-less-than-231000-that-doesnt-c)。

那么程序就好实现了，遇到 $65536$ 将答案加 $1$，$i$ 加上 $4$ 即可。

代码如下：

```cpp
int main() {
	string s;
	cin >> s;
	int ans = 0;
	FORL(i, 0, (int)s.size() - 1, 1) {
		if (s[i] == '1' || s[i] == '2' || s[i] == '4' || s[i] == '8') {
			ans++;
		}
		if (i + 4 < (int)s.size()) {
			if (s[i] == '6' && s[i + 1] == '5' && s[i + 2] == '5' && s[i + 3] == '3' && s[i + 4] == '6') {
				ans++;
				i += 4;
			}
		}
	}
	write(ans);
}
```

---

## 作者：ggylz49 (赞：0)

## Update
- 2024-07-16：修改了错别字和一个逻辑错误：“只需要将百位的 $6$ 修改即可”应为“只需要将万位的 $6$ 修改即可”。
## 代码和分析
为了不让 $s$ 的子串中出现 $2$ 的非负整数次幂，我们可以修改掉与 $2$ 的非负整数次幂有关的数字。

容易发现，$2^0=1,2^1=2,2^2=3,2^3=8$。所以对于 $1,2,4,8$ 需要将答案加一，然后把这一位上的数字覆盖为与 $2$ 的非负整数次幂无关的数，例如 $3$。

于是生成了如下代码：
```cpp
#include <iostream>
#include <string>
using namespace std;
int main()
{
    int ans=0;
    string s;
    cin>>s;
    for (int i=0;i<s.size();i++)
    {
        if (s[i]=='1'||s[i]=='2'||s[i]=='4'||s[i]=='8')ans++,s[i]='3';
    }
    cout<<ans;
    return 0;
}
```
然而这种做法只能得到 $10$ 分。可以发现，对于在题目范围内的 $2$ 的非负整数次幂值，有特殊数字 $65536$。若发现字串 $65536$ 应该将其覆盖，答案加一。

于是又写出如下代码：
```cpp
#include <iostream>
#include <string>
using namespace std;
int main()
{
    int ans=0;
    string s;
    cin>>s;
    for (int i=0;i<s.size();i++)
    {
        if (s[i]=='1'||s[i]=='2'||s[i]=='4'||s[i]=='8')ans++,s[i]='3';
        if (s[i]=='6'&&s[i+1]=='5'&&s[i+2]=='5'&&s[i+3]=='3'&&s[i+4]=='6')ans++,s[i]='3';//特判65536
    }
    cout<<ans;
    return 0;
}
```
可以发现，虽然对 $65536$ 进行了特判，但依旧只拿到了 $20$ 分。我们可以生成奇怪的 hack 数据：$655365536$。按照最优解，只需要将万位的 $6$ 修改即可，答案为 $1$。

然而，输出了 $2$！

很容易发现，我们将 $s_1$ 修改成 $3$ 后，$s=355365536$，仍然有字串 $65536$。为了避免无效的覆盖，我们应该将 $65536$ 的最后一位覆盖成 $3$。这时 $s=655335536$，就可以得到最优解 $1$。

代码修改为：
```cpp
#include <iostream>
#include <string>
using namespace std;
int main()
{
    int ans=0;
    string s;
    cin>>s;
    for (int i=0;i<s.size();i++)
    {
        if (s[i]=='1'||s[i]=='2'||s[i]=='4'||s[i]=='8')ans++,s[i]='3';
        if (s[i]=='6'&&s[i+1]=='5'&&s[i+2]=='5'&&s[i+3]=='3'&&s[i+4]=='6')ans++,s[i+4]='3';//修改最后一位
    }
    cout<<ans;
    return 0;
}
```
通过。

---

## 作者：封禁用户 (赞：0)

说实话前两道数学题坑有点多……

不严谨的说一个结论：除 $65536$ 以外所有 $2^k$（$k$ 为非负整数）都包含 $1,2,4,8$ 这 $4$ 个数字。暴力判断到 $10^{18}$ 也是同样的结果（虽然不太严谨）。

特例就是 $2^{16} = 65536$，是我用暴力跑出来的唯一特例。

那么，遍历一遍字符串，当发现 $1,2,4,8,65536$ 的时候将个数增加即可。$0$ 不是 $2$ 的非负整数幂，就不用判了。

代码：

```cpp
#include <iostream>
using namespace std;

int main()
{
    string s;
    int ans = 0;
    cin >> s;
    for (int i = 0; i < s.size(); i++)
    {
        string num;
	    num += s[i], num += s[i+1], num += s[i+2], num += s[i+3], num += s[i+4];
        if (num == "65536")
            ans++, i += 4; // 跳过搜索之间所有的数字，因为在i+4以后for循环中还要+1，所以只需要+4.
        else if (num[0] == '1' || num[0] == '2' || num[0] == '4' || num[0] == '8')
        	ans++;
    }
    cout << ans << endl;
    return 0;
}
```

再说一下注释的那行：比如说 $655365536$，明显只需要改中间的 $6$ 就可以了，但是如果不跳过搜索，它就会在 $i = 0$ 和 $i = 4$ 的时候都搜索到 $65536$，所以跳过中间的所有数字，直接看后面就可以了。

---

## 作者：nightwatch.ryan (赞：0)

### 思路
$2$ 的幂，并且只有一位数的有：$1,2,4,8$。如果枚举到这些数字，答案 $+1$。

但是，$65536$ 非常特殊，他不含一位数的 $2$ 的幂，所以有 $65536$ 的时候，答案也要增加 $1$，并且还需要给最后一位覆盖成 $7$ 或者 $9$。

在题目给定的范围里，只有 $65536$ 一个数字是非常特殊的，所以只要特判一下 $65536$ 即可。
### 代码
```cpp
#include<iostream>
std::string s;
bool check(char x){
	if(x=='1'||x=='2'||x=='4'||x=='8')
		return true;
	return false;
}
int main(){
	std::cin>>s;
	int ans=0;
	for(int i=0;i<s.size();i++){
		ans+=check(s[i]);
		if(s[i]=='6'&&s[i+1]=='5'&&s[i+2]=='5'&&s[i+3]=='3'&&s[i+4]=='6'){
			ans++;
			s[i+4]='9';
		}
	}
	std::cout<<ans; 
}
```

---

## 作者：chenlongli (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10571)
### 思路
首先，$1=2^0,2=2^1,4=2^2,8=2^3$，所以只要这个序列有 $1,2,4,8$，那么就要对这些数字进行一次更改。

我们考虑有没有这个数字既没有哪一位为 $1,2,4,8$，还是 $2$ 的非负整数次幂，在 $10^6$ 之内，只找到了 $65536$ 这个特殊的数字，如果在序列中找到了 $65536$ 这个数字，那么就进行一次更改。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string n;
	cin>>n;
	int ans=0;
	for (int i=0;i<n.length();i++)
	{
		if (n[i]=='2'||n[i]=='4'||n[i]=='8'||n[i]=='1')
		{
			ans=ans+1;
			n[i]='0';
		}
		if (i>3&&n[i]=='6'&&n[i-1]=='3'&&n[i-2]=='5'&&n[i-3]=='5'&&n[i-4]=='6')
		{
			ans=ans+1;
			n[i]='0';
		}
	}
	cout<<ans<<endl;
}
```

---

