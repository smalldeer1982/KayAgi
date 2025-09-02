# Balanced Ternary String

## 题目描述

You are given a string $ s $ consisting of exactly $ n $ characters, and each character is either '0', '1' or '2'. Such strings are called ternary strings.

Your task is to replace minimum number of characters in this string with other characters to obtain a balanced ternary string (balanced ternary string is a ternary string such that the number of characters '0' in this string is equal to the number of characters '1', and the number of characters '1' (and '0' obviously) is equal to the number of characters '2').

Among all possible balanced ternary strings you have to obtain the lexicographically (alphabetically) smallest.

Note that you can neither remove characters from the string nor add characters to the string. Also note that you can replace the given characters only with characters '0', '1' and '2'.

It is guaranteed that the answer exists.

## 样例 #1

### 输入

```
3
121
```

### 输出

```
021
```

## 样例 #2

### 输入

```
6
000000
```

### 输出

```
001122
```

## 样例 #3

### 输入

```
6
211200
```

### 输出

```
211200
```

## 样例 #4

### 输入

```
6
120110
```

### 输出

```
120120
```

# 题解

## 作者：花里心爱 (赞：5)

这是一道贪心题qwq

首先发现最终结果的`'0', '1', '2'`数量一定都是$n/3$。

其次因为要求改动次数最小，所以最初个数就小于等于$n/3$的都要保留。

然后分别考虑这3个数的个数大于$n/3$的情况：

1. 当`'2'`的个数大于$n/3$时，我们发现后面的`'2'`需要保留，于是从前往后换，优先换`'0'`，其次换`'1'`。
2. 当`'0'`的个数大于$n/3$时，我们发现前面的`'0'`需要保留，于是从后往前换，优先换`'2'`，其次换`'1'`。
3. 当`'1'`的个数大于$n/3$时，我们维护两个指针$l, r$， 分别从前往后/从后往前扫一遍，左指针$l$扫到的`'1'`优先换`'0'`，右指针$r$扫到的`'1'`优先换`'2'`。

这样就可以保证字典序最小。

下面放代码：
```
#include <cstdio>

int n, qui;
char s[300005];
int cnt[105];
// 注意每次修改元素后要及时修改 cnt 数组

int main() {
	scanf("%d", &n);
	qui = n/3;
	scanf("%s", s+1);
	for(int i = 1; i <= n; ++i)
		++cnt[(int)s[i]];
	for(int i = 1; cnt['2'] > qui && i <= n; ++i) {
		if(s[i] == '2') {
			if(cnt['0'] < qui) s[i] = '0', ++cnt['0'], --cnt['2'];
			else if(cnt['1'] < qui) s[i] = '1', ++cnt['1'], --cnt['2'];
		}
	}
	for(int i = n; cnt['0'] > qui && i; --i) {
		if(s[i] == '0') {
			if(cnt['2'] < qui) s[i] = '2', ++cnt['2'], --cnt['0'];
			else if(cnt['1'] < qui) s[i] = '1', ++cnt['1'], --cnt['0'];
		}
	}
	for(int l = 1, r = n; cnt['1'] > qui && r; ++l, --r) {
		if(s[l] == '1' && cnt['0'] < qui) s[l] = '0', ++cnt['0'], --cnt['1'];
		if(s[r] == '1' && cnt['2'] < qui) s[r] = '2', ++cnt['2'], --cnt['1'];
	}
	puts(s+1);
	return 0;
}
```

---

## 作者：floatery (赞：1)

仍然恶意评分

这不是一道贪心吗？

贪心方法：找到出现次数最多的数字，假如这个数字是0，那么就从后往前，能用2换就不用1换；假如这个数字是1，那么两波循环；假如这个数字是2，和0类似，不予叙述。

读者可配合代码自己思考。

```cpp
#include <stdio.h>
char str[300001];
int num[3];
int main()
{
	int n;
	scanf("%d",&n);
	scanf("%s",str);
	for(int i=0;i<n;i++)
	{
		num[str[i]-'0']++;
	}
	int tmp=n/3;
	while(num[0]>tmp)
	{
		for(int j=n-1;j>=0;j--)
		{
			if(num[0]<=tmp) break;
			if(str[j]!='0') continue;
			if(num[2]<tmp)
			{
				str[j]='2';
				num[0]--;
				num[2]++;	
			}
			else if(num[1]<tmp)
			{
				str[j]='1';
				num[0]--;
				num[1]++;
			}
		}
	}
	while(num[1]>tmp)
	{
		for(int j=0;j<n;j++)
		{
			if(num[1]<=tmp) break;
			if(str[j]!='1') continue;
			if(num[0]<tmp)
			{
				str[j]='0';
				num[0]++;
				num[1]--;
			}
		}
		for(int j=n-1;j>=0;j--)
		{
		    if(num[1]<=tmp) break;
			if(str[j]!='1') continue;
			if(num[2]<tmp)
			{
				str[j]='2';
				num[2]++;
				num[1]--;
			}
		}
	}
	while(num[2]>tmp)
	{
		for(int j=0;j<n;j++)
		{
			if(num[2]<=tmp) break;
			if(str[j]!='2') continue;
			if(num[0]<tmp)
			{
				str[j]='0';
				num[0]++;
				num[2]--;
			}
			else if(num[1]<tmp)
			{
				str[j]='1';
				num[1]++;
				num[2]--;
			}
		}
	}
	printf("%s\n",str);
	return 0;
}
```

---

## 作者：Loser_Syx (赞：0)

考虑贪心。  
发现一个数如果要替换为 `0`，则一定是越前面的多出来的数字给它替换（`0` 字典序小于 `1` 和 `2`）；反之，如果一个数要替换为 `2`，则一定是越后面的多出来的给他换。  
然后再看缺 `1` 的情况，优先从前往后换掉多的 `2`，不够再从后往前换掉多的 `0` 即可。

```cpp
int n; string s;
signed main() {
	cin >> n >> s;
	int cnt[3] = {0, 0, 0};
	for (auto i : s) cnt[i - '0'] ++;
	for (auto &i : s) {
		if (cnt[0] < n / 3 && cnt[i - '0'] > n / 3) {
			cnt[0] ++;
			cnt[i - '0'] --;
			i = '0';
		} else if (cnt[1] < n / 3 && i == '2' && cnt[2] > n / 3) {
			i = '1';
			cnt[1] ++; cnt[2] --;
		}
	}
	for (int i = n-1; ~i; --i) {
		if (cnt[2] < n / 3 && cnt[s[i] - '0'] > n / 3) {
			cnt[2] ++;
			cnt[s[i] - '0'] --;
			s[i] = '2';
		} else if (cnt[1] < n / 3 && s[i] == '0' && cnt[0] > n / 3) {
			cnt[1] ++;
			cnt[0] --;
			s[i] = '1';
		}
	} cout << s;
	return 0;
}
```

---

## 作者：Maysoul (赞：0)

## 简述思路：

题意给定这个字符串一定能平衡，所以每种字符所占的个数一定是 $\frac{n}{3}$ 个。

直接平衡很容易，难点在于使字典序最小的贪心，我们可以把这道题分为 6 种状况来考虑：

1. `2`多了，把其中一些变为`0`。
2. `2`多了，把其中一些变为`1`。
3. `1`多了，把其中一些变为`0`。
4. `1`多了，把其中一些变为`2`。
5. `0`多了，把其中一些变为`1`。
6. `0`多了，把其中一些变为`2`。

我们不难发现，在上述情况中，前三条的修改能使字典序变小，后三条的修改能使字典序变大。那么使字典序变小的修改，应该越靠前越好，使字典序变大的修改，应该越靠后越好。

而其中`2`修改为`0`比修改为`1`更优秀，`1`修改为`0`比修改为`2`更优秀，`2`修改为`0`比修改为`1`更优秀。

所以我们的贪心思路就很明确了，先正向扫一遍，再反向扫一遍，按上述思路进行贪心即可。

## AC CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+10;
int num,ans;
char a[MAXN];
int num0,num1,num2;
int main()
{
	int n,tol;
	cin>>n;
	tol=n/3;
	for (int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]=='0') num0++;
		if(a[i]=='1') num1++;
		if(a[i]=='2') num2++; 
	}
	for (int i=1;i<=n;i++){
		if(a[i]=='2'&&num2>tol){
			num2--;
			if(num0<tol){
				a[i]='0';
				num0++;
			}
			else if(num1<tol){
				a[i]='1';
				num1++;
			}
		}
		if(a[i]=='1'&&num1>tol){
			if(num0<tol){
				a[i]='0';
				num0++;
				num1--;
			}
		}
	}
	for (int i=n;i>=1;i--){
		if(a[i]=='1'&&num1>tol){
			if(num2<tol){
				a[i]='2';
				num2++;
				num1--;
			}
		}
		if(a[i]=='0'&&num0>tol){
			num0--;
			if(num2<tol){
				a[i]='2';
				num2++;
			}
			else if(num1<tol){
				a[i]='1';
				num1++;
			}
		}
	}
	for (int i=1;i<=n;i++) cout<<a[i];
	return 0;
}

```


---

## 作者：tZEROちゃん (赞：0)

没高中上了所以就来写个题解玩玩。

因为长度是 $n$，所以每个数字一定是 $\dfrac{n}{3}$ 次。

我们进行一个分类讨论：

1. 0 少了。
	1. 0 少了，1 多了，2 正好。    
    从后往前把 1 替换成 0。
    2. 0 少了，1 正好，2 多了。    
    从后往前把 1 替换成 0。       
    3. 0 少了，1 多了，2 少了。    
    我们肯定尽可能把 2 往后放，0 往前放。因此从前往后改 0，从后往前改 2。
    4. 0 少了，1 少了，2 多了。     
    从前往后把 2 改成 1，1 正好以后再改 2，这样字典序肯定是最小的。
    5. 0 少了，1 多了，2 多了。           
    直接从前往后改就行。
2. 1 少了。
    1. 1 少了，2 正好，0 多了。     
    从后往前把 0 替换成 1 即可。
    2. 1 少了，2 多了，0 正好。          
    从前往后把 2 替换成 1 即可。    
    2. 1 少了，2 多了，0 少了。  
    直接从前往后改。            
    2. 1 少了，2 少了，0 多了。        
    从后往前，先改 2 后改 1。
    2. 1 少了，2 多了，0 多了。   
    从前往后把 2 变成 1，然后从后往前把 0 变成 1。
3. 2 少了。     
    1. 2 少了，1 多了，0 正好。       
    从后往前将 1 替换成 2。
    2. 2 少了，1 正好，0 多了。    
    从后往前把 0 替换成 1。
    3. 2 少了，1 多了，0 少了。        
    从前往后把 1 改成 0，从后往前把 1 改成 2。
    3. 2 少了，1 少了，0 多了。        
    从后往前，先改 1 后改 0。
    5. 2 少了，1 多了，0 多了。
    从后往前直接改就行。
    
做完了。代码非常长，写完感觉我是 sb，事实也的确如此。

代码的分讨顺序就是上面的顺序，要看正常的贪心建议去其他题解，再见。

[Code](https://codeforces.com/contest/1102/submission/211337584)。
    

---

## 作者：SakurajiamaMai (赞：0)

## 思路:
要求字典序最小，那就是尽可能的让 $0$ 在前面，让 $1$ 在 $0$ 后面，让 $2$ 在 $1$ 后面，首先算出 $0$，$1$，$2$ 的数量，然后分三种情况讨论，如果 $1$ 多并且 $0$ 或者 $2$ 不够，如果是 $0$ 不够，就从左向右推，因为要字典序最小嘛，如果 $2$ 不够，就从后向前推，尽可能让 $2$ 在后面。如果 $0$ 多，由于 $0$ 的特殊，无论是 $1$ 或者 $2$ 都是要从后向前推，尽可能的让 $0$ 在前面。$2$ 多的情况与 $0$ 和 $1$ 类似，具体实现过程看代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
string s,ss;
int res,n,x,num1,num0,num2;
int main()
{
    cin>>n>>s;
    ss=s;
    x=n/3;
    for(int i=0;i<n;i++){//统计数量。
        if(s[i]=='0') num0++;
        else if(s[i]=='1') num1++;
        else if(s[i]=='2') num2++;
    }
   //分情况讨论。
    if(num2>x){
        if(num0<x&&num2>x)//2 多0少，从前向后。
            for(int i=0;i<n;i++){
                if(num2>x&&num0<x&&s[i]=='2') s[i]='0',num2--,num0++;
                if(num0==x||num2==x) break;
            }        
        if(num1<x&&num2>x)//1 少,，也是从前向后。
            for(int i=0;i<n;i++){
                if(num2>x&&num1<x&&s[i]=='2') s[i]='1',num2--,num1++;
                if(num1==x||num2==x) break;
            }        
    }    
    if(num1>x){
        if(num0<x&&num1>x)
            for(int i=0;i<n;i++){
                if(num1>x&&num0<x&&s[i]=='1') s[i]='0',num1--,num0++;
                if(num0==x||num1==x) break;
            }
        if(num2<x&&num1>x)
            for(int i=n-1;i>=0;i--){
                if(num1>x&&num2<x&&s[i]=='1') s[i]='2',num1--,num2++;
                if(num2==x||num1==x) break;
            }
    }    
    if(num0>x){
        for(int i=n-1;i>=0;i--){
            if(num0>x&&s[i]=='0'){
                if(num2<x) s[i]='2',num2++,num0--;
                else if(num1<x) s[i]='1',num1++,num0--;
            }
        }
    }
    cout<<s;
    return 0;
}
```


---

## 作者：_lbh_ (赞：0)

## 题目传送门[点这](https://www.luogu.com.cn/problem/CF1102D)

## 思路：
这是一道贪心题。

最终每个数的个数都要改成 $n\div3$。

我们可以循环两遍，先正序，再倒序。

### 先考虑正序循环：

正序是要将靠前的大数改小。

1. 若 $a[i]=2$，那么先考虑改成 $0$ 在考虑改成 $1$。

2. 若 $a[i]=1$，那么只用考虑改成 $0$。
 
3. 若 $a[i]=0$，改不了了，$0$ 是最小了。

### 接下来考虑倒序循环：

正序是要将靠后的小数改大。

1. 若 $a[i]=0$，那么先考虑改成 $2$ 在考虑改成 $1$。

2. 若 $a[i]=1$，那么只用考虑改成 $2$。

3. 若 $a[i]=2$，改不了了，$2$ 是最大了。

代码：

 ```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n, cnt[3], a[N];
char b[N];
int main()
{
  cin>>n;
  for(int i=1; i<=n; i++)
  {
    cin>>b[i]; 
    a[i]=((int)b[i]-'0');//转成int
    cnt[a[i]]++;//记录有几个a[i]
  }
  int tmp=n/3;//求出最终要改成多少个
  for(int i=1; i<=n; i++)//正序修改
  {
    if(a[i]==2&&cnt[2]>tmp&&cnt[0]<tmp)
    {
      a[i]=0;
      cnt[2]--;
      cnt[0]++;
    }
    if(a[i]==2&&cnt[2]>tmp&&cnt[1]<tmp)
    {
      a[i]=1;
      cnt[2]--;
      cnt[1]++;
    }
    if(a[i]==1&&cnt[1]>tmp&&cnt[0]<tmp)
    {
      a[i]=0;
      cnt[1]--;
      cnt[0]++;
    }
  }
  for(int i=n; i>=1; i--)//倒序修改
  {
    if(a[i]==0&&cnt[0]>tmp&&cnt[2]<tmp)
    {
      a[i]=2;
      cnt[2]++;
      cnt[0]--;
    }
    if(a[i]==1&&cnt[1]>tmp&&cnt[2]<tmp)
    {
      a[i]=2;
      cnt[2]++;
      cnt[1]--;
    }
    if(a[i]==0&&cnt[0]>tmp&&cnt[1]<tmp)
    {
      a[i]=1;
      cnt[1]++;
      cnt[0]--;
    }
  }
  for(int i=1; i<=n; i++)
  {
    cout<<a[i];
  }
  return 0;
}

 ```

---

## 作者：yimuhua (赞：0)

## 题意：

给一个由 '0'，'1'，'2' 组成的字符串（长度是3的倍数），可以修改任意位置上的字符，要求修改最少使得 '0'，'1'，'2' 个数相等，在此条件下输出字典序最小的串。

## 思路：

贪心。

最终结果的 '0', '1', '2' 数量一定都是 $n/3$。

其次因为要求改动次数最小，所以最初个数就小于等于 $n/3$ 的都要保留。

然后分别考虑这 3 个数的个数大于 $n/3$ 的情况：

1.当 '2' 的个数大于 $n/3$ 时：

$\ \ \ $从前往后换，**优先换 '0' ，其次换 '1'**。

2.当 '0' 的个数大于 $n/3$ 时：

$\ \ \ $从后往前换，**优先换 '2' ，其次换 '1'**。

3.当 '1' 的个数大于 $n/3$ 时：

$\ \ \ $维护两个指针 $l, r$， 分别从前往后 / 从后往前扫一遍，左指针 $l$ 扫到的 '1' **优$\ \ \ $先换 '0'**，右指针 $r$ 扫到的 '1' **优先换 '2'**。

根据此思路，即可使字典序最小。

## AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int n, avg, cnt[105];
int main() {
    cin >> n >> s;
    avg = n / 3;
    for(int i = 0; i < n; i++)
        cnt[s[i] - '0']++;
    for(int i = 0; cnt[2] > avg && i < n; i++)
        if(s[i] == '2') {
            if(cnt[0] < avg)
                s[i] = '0', cnt[0]++, cnt[2]--;
            else if(cnt[1] < avg)
                s[i] = '1', cnt[1]++, cnt[2]--;
        }
    for(int i = n - 1; cnt[0] > avg && i >= 0; i--)
        if(s[i] == '0') {
            if(cnt[2] < avg)
                s[i] = '2', cnt[2]++, cnt[0]--;
            else if(cnt[1] < avg)
                s[i] = '1', cnt[1]++, cnt[0]--;
        }
    for(int l = 0, r = n - 1; cnt[1] > avg && r >= 0; l++, r--) {
        if(s[l] == '1' && cnt[0] < avg)
            s[l] = '0', cnt[0]++, cnt[1]--;
        if(s[r] == '1' && cnt[2] < avg)
            s[r] = '2', cnt[2]++, cnt[1]--;
    }
    cout << s;
    return 0;
}
```


---

## 作者：xyf007 (赞：0)

### 如果$0$的个数多于$n/3$，从后往前把$0$换成$2$，再换成$1$
### 如果$1$的个数多于$n/3$，从前往后把$1$换成$0$，再从后往前把$1$换成$2$
### 如果$2$的个数多于$n/3$，从前往后把$2$换成$0$，再换成$1$
```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
string s;
int n,zero,one,two;
int main()
{
	scanf("%d",&n);
	cin>>s;
	zero=one=two=-n/3;
	for(int i=0;i<n;i++)
	{
		if(s[i]=='0')
		{
			zero++;
		}
		if(s[i]=='1')
		{
			one++;
		}
		if(s[i]=='2')
		{
			two++;
		}
	}
	if(zero>0)
	{
		for(int i=n-1;(i>=0)&&(zero>0);i--)
		{
			if(s[i]=='0')
			{
				zero--;
				if(two<0)
				{
					s[i]='2';
					two++;
				}
				else
				{
					s[i]='1';
					one++;
				}
			}
		}
	}
	if(one>0)
	{
		for(int i=0;(i<n)&&(zero<0)&&(one>0);i++)
		{
			if(s[i]=='1')
			{
				one--;
				zero++;
				s[i]='0';
			}
		}
		for(int i=n-1;(i>=0)&&(two<0)&&(one>0);i--)
		{
			if(s[i]=='1')
			{
				one--;
				two++;
				s[i]='2';
			}
		}
	}
	if(two>0)
	{
		for(int i=0;(i<n)&&(two>0);i++)
		{
			if(s[i]=='2')
			{
				two--;
				if(zero<0)
				{
					s[i]='0';
					zero++;
				}
				else
				{
					s[i]='1';
					one++;
				}
			}
		}
	}
	cout<<s;
	return 0;
}
```

---

## 作者：Zechariah (赞：0)

这题没啥别的技巧...大力贪心就行了  
考虑0的个数不够，优先用2来补，其次是1  
考虑1的个数不够，优先用2来补，其次是0  
考虑2的个数不够，优先用1来补，其次是0  
输出的时候，尽量把小的放前面，保证字典序最小
```cpp
#include <bits/stdc++.h>
#define rg register
#define inl inline
typedef long long ll;
const double PI = 3.1415926535898, eps = 0;
const int N = 3e5 + 10, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
	long long read()
	{
		rg long long num = 0;
		rg char ch;
		rg bool flag = false;
		while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
		if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
		while ((ch = getchar()) >= '0'&&ch <= '9')
			num = (num << 1) + (num << 3) + (ch ^ 48);
		if (flag)return -num; return num;
	}
	int chread(rg char s[])
	{
		rg char ch;
		rg int len = 0;
		while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
		s[len++] = ch;
		while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
			s[len++] = ch;
		s[len] = 0;
		return len;
	}
	ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
int cnt[3], change[3][3];
char s[N];

int main()
{
	rg int n = fast_IO::read(); fast_IO::chread(s + 1);
	for (rg int i = 1; i <= n; ++i)++cnt[s[i] ^ 48];
	if (cnt[0] < n / 3)
	{
		if (cnt[2] > n / 3 && cnt[2] - n / 3 <= n / 3 - cnt[0])change[2][0] += cnt[2] - n / 3, cnt[0] += cnt[2] - n / 3, cnt[2] = n / 3;
		else if (cnt[2] > n / 3)change[2][0] += n / 3 - cnt[0], cnt[2] -= n / 3 - cnt[0], cnt[0] = n / 3;
		if (cnt[1] > n / 3 && cnt[1] - n / 3 <= n / 3 - cnt[0])change[1][0] += cnt[1] - n / 3, cnt[0] += cnt[1] - n / 3, cnt[1] = n / 3;
		else if (cnt[1] > n / 3)change[1][0] += n / 3 - cnt[0], cnt[1] -= n / 3 - cnt[0], cnt[0] = n / 3;
	}
	if (cnt[1] < n / 3)
	{
		if (cnt[2] > n / 3 && cnt[2] - n / 3 <= n / 3 - cnt[1])change[2][1] += cnt[2] - n / 3, cnt[1] += cnt[2] - n / 3, cnt[2] = n / 3;
		else if (cnt[2] > n / 3)change[2][1] += n / 3 - cnt[1], cnt[2] -= n / 3 - cnt[1], cnt[1] = n / 3;
		if (cnt[0] > n / 3 && cnt[0] - n / 3 <= n / 3 - cnt[1])change[0][1] += cnt[0] - n / 3, cnt[1] += cnt[0] - n / 3, cnt[0] = n / 3;
		else if (cnt[0] > n / 3)change[0][1] += n / 3 - cnt[1], cnt[0] -= n / 3 - cnt[1], cnt[1] = n / 3;
	}
	if (cnt[2] < n / 3)
	{
		if (cnt[1] > n / 3 && cnt[1] - n / 3 <= n / 3 - cnt[2])change[1][2] += cnt[1] - n / 3, cnt[2] += cnt[1] - n / 3, cnt[1] = n / 3;
		else if (cnt[1] > n / 3)change[1][2] += n / 3 - cnt[2], cnt[1] -= n / 3 - cnt[2], cnt[2] = n / 3;
		if (cnt[0] > n / 3 && cnt[0] - n / 3 <= n / 3 - cnt[2])change[0][2] += cnt[0] - n / 3, cnt[2] += cnt[1] - n / 3, cnt[0] = n / 3;
		else if (cnt[0] > n / 3)change[0][2] += n / 3 - cnt[2], cnt[0] -= n / 3 - cnt[2], cnt[2] = n / 3;
	}
	for (rg int i = 1; i <= n; ++i)
	{
		rg bool flag = false;
		for (rg int j = 0; j <= 2; ++j)
			if (change[s[i] ^ 48][j])
			{
				if ((s[i] ^ 48) < j&&cnt[s[i] ^ 48])break;
				--change[s[i] ^ 48][j];
				putchar(j ^ 48); --cnt[j];
				flag = true;
				break;
			}
		if (!flag)putchar(s[i]), --cnt[s[i] ^ 48];
	}
	return 0;
}
```

---

