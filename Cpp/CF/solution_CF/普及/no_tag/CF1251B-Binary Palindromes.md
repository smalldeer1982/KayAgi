# Binary Palindromes

## 题目描述

A palindrome is a string $ t $ which reads the same backward as forward (formally, $ t[i] = t[|t| + 1 - i] $ for all $ i \in [1, |t|] $ ). Here $ |t| $ denotes the length of a string $ t $ . For example, the strings 010, 1001 and 0 are palindromes.

You have $ n $ binary strings $ s_1, s_2, \dots, s_n $ (each $ s_i $ consists of zeroes and/or ones). You can swap any pair of characters any number of times (possibly, zero). Characters can be either from the same string or from different strings — there are no restrictions.

Formally, in one move you:

- choose four integer numbers $ x, a, y, b $ such that $ 1 \le x, y \le n $ and $ 1 \le a \le |s_x| $ and $ 1 \le b \le |s_y| $ (where $ x $ and $ y $ are string indices and $ a $ and $ b $ are positions in strings $ s_x $ and $ s_y $ respectively),
- swap (exchange) the characters $ s_x[a] $ and $ s_y[b] $ .

What is the maximum number of strings you can make palindromic simultaneously?

## 说明/提示

In the first test case, $ s_1 $ is palindrome, so the answer is $ 1 $ .

In the second test case you can't make all three strings palindromic at the same time, but you can make any pair of strings palindromic. For example, let's make $ s_1 = \text{0110} $ , $ s_2 = \text{111111} $ and $ s_3 = \text{010000} $ .

In the third test case we can make both strings palindromic. For example, $ s_1 = \text{11011} $ and $ s_2 = \text{100001} $ .

In the last test case $ s_2 $ is palindrome and you can make $ s_1 $ palindrome, for example, by swapping $ s_1[2] $ and $ s_1[3] $ .

## 样例 #1

### 输入

```
4
1
0
3
1110
100110
010101
2
11111
000001
2
001
11100111
```

### 输出

```
1
2
2
2
```

# 题解

## 作者：zhanghapi (赞：4)

看到前面先发题解的大佬写的有些简单，这里写一下我自己对这个题的理解。

首先分类找规律发现：假设有长度为n的串。

当n为奇数时：只要放置小于n的任意多的1都可以满足回文。

当n为偶数时：必须放置偶数个1才可以满足回文。

因此我们统计1的个数和奇数长度串的个数，因为不论什么样的串都可以放偶数个的1，因此我们计算tot%2，假如tot%2==1，那么必须有至少一个奇数串，否则必定有一个串拼不成回文即输出n-1.

最后附上AC代码：
```cpp
#include<cstdio>
#include<cstring> 
#include<iostream>
using namespace std;
const int maxn=60;
int q,n;
char c[maxn];
int main()
{
	scanf("%d",&q);
	while(q--)
	{
		scanf("%d",&n);
		int tot=0,sum=0;
		for(int i=1;i<=n;i++){
			cin>>c;
			int l=strlen(c);
			if(l%2) sum++;
			for(int j=0;j<l;j++)
				if(c[j]=='1') tot++;
		}
		if(tot%2==1){
			if(sum>=1) printf("%d\n",n);
			else printf("%d\n",n-1); 
		}
		else printf("%d\n",n);
	}
	return 0;
}
```


---

## 作者：_GW_ (赞：1)

## 思路

能交换任意两个字符串中的任意位置，那不就是只要每一个字符串的长度不变，想怎么换怎么换吗？

找规律：如果当前字符串为 $s$，那么，如果 $s$ 的长度为偶数，想要他成为回文串，必须是由偶数个 $0$ 与 偶数个 $1$ 拼接的。

如果 $s$ 的长度为奇数，那么不论的奇数个 $1$，还是偶数个 $1$，都能凑成回文串。

那么，就统计 $1$ 的个数和长度为偶数的字符串的个数，最后判断即可。

判断：如果全是长度为偶数的字符串，且 $1$ 的个数为奇数，那么必定要舍弃一个字符串，答案为 $n-1$。

否则，答案都为 $n$。

## code

```cpp
#include  <bits/stdc++.h>
using namespace std;
const int N=55;
int val,n,m,T,res,num;
string a[N],s;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		res=num=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(a[i].size()%2==0)
			{
				res++;
			}
			for(int j=0;j<a[i].size();j++)
			{
				if(a[i][j]=='1')
				{
					num++;
				}
			}
		}
		if(num%2==1)
		{
			if(res==n) cout<<n-1<<endl;
			else cout<<n<<endl;
		}
		else
		{
			cout<<n<<endl;
		}
	}
	return 0;
}
```


---

## 作者：盧鋅 (赞：0)

又是一道水题。

找规律，很明显的可以发现奇数长的字串，可以放置小于等于其长度的1；

偶数长的字串只可以放置偶数长度的1；

over！！！！

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
signed main(){
	int ans=0,one=0;
	string s;
	int t,n;
	cin>>t;
	while(t--){
		cin>>n;
		int k=n;
		ans=0;
		one=0;
		while(k--)
		{
			cin>>s;
			ans+=s.length()%2;
			for(int i=0;i<s.length();++i)if(s[i]=='1')one++;
		}
		if(ans>=one%2)cout<<n<<endl;
		else cout<<n-1<<endl;
	}
	return 0; 
}
```


---

