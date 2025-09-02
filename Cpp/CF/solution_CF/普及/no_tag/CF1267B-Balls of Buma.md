# Balls of Buma

## 题目描述

巴尔夫在玩一个游戏。在这个游戏中，他将得到一串彩色的球。他需要选择一个颜色的球并在这串球中选择任意一个位置插入这个球。

当一个球被插入后，以下情况会重复发生：如果连续一串相同颜色的球**由于先前的操作而变长**，并且其长度大于或等于$3$，则这一串相同颜色的球都将被消除。

例如，一串球“AAABBBWWBB”。假如巴尔夫选择了一个颜色为‘W’的球，并将其插入到第$6$个位置（即‘B’和‘W’之间），此时颜色为‘W’的球将被消除，因为该操作使得此段变长且长度为$3$。现在，这串球为“AAABBBBB”。颜色为‘B’的球现在被消除了，因为颜色为‘B’的球段变长了，并且长度为$5$。剩下的球为“AAA”，由于没有任何操作使得颜色为‘A’的球段变长，所以无法再次进行消除。

巴尔夫想知道，如果给你任意一串球，有多少种插入的方式能使得所有的球都能被消除？

## 样例 #1

### 输入

```
BBWWBB
```

### 输出

```
3
```

## 样例 #2

### 输入

```
BWWB
```

### 输出

```
0
```

## 样例 #3

### 输入

```
BBWBB
```

### 输出

```
0
```

## 样例 #4

### 输入

```
OOOWWW
```

### 输出

```
0
```

## 样例 #5

### 输入

```
WWWOOOOOOWWW
```

### 输出

```
7
```

# 题解

## 作者：_Spectator_ (赞：3)

[可能更差的食用体验（？）](https://www.luogu.com.cn/blog/523641/CF1267B)

[题目传送门](https://www.luogu.com.cn/problem/CF1267B)

~~作为翻译人来水一篇题解。~~

鄙人不才，参考了[@gyh20大佬](https://www.luogu.com.cn/blog/gyh20/solution-cf1267b)的思路，并加以优化与说明。

------------
### ${\color{RoyalBlue} {样例解释}}$

```txt
WWWOOOOOOWWW
```
这个样例可以在第 $3$ 到第 $9$ 任意一个字符后插入一个“O”，共 $9-3+1=7$ 种方式。

以在第 $5$ 位插入一个“O”为例：第一次中间连续一段的“O”的长度因插入而变长且长度大于等于 $3$ ，满足消除条件。当中间的“O”被消除后，前后两段连续的“B”连成一段（即长度因“O”的消除而变长）且长度大于等于 $3$ ，再次消除。此时所有字符都被消除，即为一种成功的方案。读者可以尝试模拟在其他位置插入其他字符时游戏的过程。


------------

### ${\color{RoyalBlue} {主要思路}}$
从上面的模拟不难看出，前面的字符必定只能与后面对应的字符连成一段并消除，例如：形如“AABBAAA”、“ABBCCBAA”等的字符串都是合法的，而形如“AABBAABB”、“AABBCCAABB”等的字符串都是不合法的。可以通过比较前后字符的方法从外向内进行消除。不难想到可以维护一个双向队列。

以第一个样例“BBWWBB”为例：

`deque<char>st`
|B|B|W|W|B|B|
|-|-|-|-|-|-|

第一次，队列将两头的“B”弹出，并统计出个数为 $4$。个数大于等于 $3$，程序继续进行消除操作。

此时队列为：
|W|W|
|-|-|

第二次，队列将两头的“W”弹出，并统计出个数为 $2$。此时队列为空，个数只要大于等于 $2$ 就为合法。此时可以在这一串“W”之间和前、后任意位置插入一个“W”，故答案为 $2+1=3$。

这一段消除的过程可以用以下代码实现：
```cpp
long long cnt=0; 
while(!st.empty())
{
	ch=st.front(),st.pop_front(),cnt++;
	if(st.front()!=ch)break;
}
while(!st.empty())
{
	ch=st.back(),st.pop_back(),cnt++;
	if(st.back()!=ch)break;
}
if(st.empty()&&cnt>=2)
{
	cout<<cnt+1;
	return 0;
}
if(cnt<3)break;
```
还有一点要注意：如果队列的队首和队尾字符不相同或者队列的长度只有 $1$，都是不合法的字符串。只需在每次操作前判断一下即可。
```cpp
if(st.size()==1||st.front()!=st.back())break;
```
总的时间复杂度为 $O(\ st.size()\ )$，非常优秀。

------------

### ${\color{RoyalBlue} {完整代码}}$

```cpp
#pragma G++ optimize(2)
#include<bits/stdc++.h>
#error\ 
禁止抄题解 
using namespace std;
char ch;
deque<char>st;
long long l,r; 
int main()
{
	ios::sync_with_stdio(false);
	while(cin>>ch)st.push_back(ch);
	while(!st.empty())
	{
		if(st.size()==1||st.front()!=st.back())break;
		long long cnt=0; 
		while(!st.empty())
		{
			ch=st.front(),st.pop_front(),cnt++;
			if(st.front()!=ch)break;
		}
		while(!st.empty())
		{
			ch=st.back(),st.pop_back(),cnt++;
			if(st.back()!=ch)break;
		}
		if(st.empty()&&cnt>=2)
		{
			cout<<cnt+1;
			return 0;
		}
		if(cnt<3)break;
	}
	cout<<0;
	return 0;
}
```

**xt__温馨提示：**

**${\color{brown} {题解千万条，理解第一条。直接粘题解，棕名两行泪。}} $**

---

## 作者：gyh20 (赞：2)

贪心

由题可知，必须要最中间的被消除(数量$>=2$)，之后每一个的数量都$>=3$即可。

方案数即为中间的个数$+1$。

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#define in inline
#define re register
using namespace std;
in int read() {
	re int t=0;
	re char v=getchar();	
	while(v<'0'||v>'9'){
	v=getchar();
	}	
	while(v>='0'&&v<='9'){		
	t=(t<<3)+(t<<1)+(v^48);		
	v=getchar();	}
	return t;
}
char s[300005];
int l,r,cnt;
int main(){
	scanf("%s",s);
	l=0;
	r=strlen(s)-1;
	while(l<=r){
		if(l==r){
			putchar('0');
			return 0;
		}
		cnt=2;
		if(s[l]!=s[r]){
			putchar('0');
			return 0;
		}
		while(s[l+1]==s[l]&&l<r)++l,++cnt;
		while(s[r-1]==s[r]&&r>l)--r,++cnt;
		++l;
		--r;
		if(r<l){
			printf("%d",cnt);
			return 0;
		}
		if(cnt<3){
			putchar('0');
			return 0;
		}
		
	}
}
```


---

## 作者：xh001 (赞：1)

# 题意
每组数据包含一个字符串，求在插入一个任意字符后，如果连续一串相同的字符由于先前的操作而变长，并且其长度大于或等于 $3$，则这一串相同的字符都将被消除，有多少种插入的方式能使得所有的球都能被消除。
# 思路
因为只能插入一个字符，所以它一定只能用来改变中间的字符串（不一定是正中间），我们可以从两端开始向中间遍历，如果发现两端的字符不能在中间的字符串消除后被消除，直接输出 $0$ 即可。若整个字符串被消除了，方案数即为中间的字符串长度加一。

最后记得特判首尾字符不相同或者字符串长度只有 $1$ 的情况就能切了。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//好习惯。 
string s;
char c;
deque<char>q;//双端队列。 
ll l,r,sum; 
inline ll read()
{
	ll k=0,f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) k=(k<<1)+(k<<3)+(c^48);
	return f?-k:k;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>s;
	for(ll i=0;i<s.size();i++) q.push_back(s[i]);//把初始字符串存在队列里。 
	while(!q.empty())
	{
		if(q.size()==1 || q.front()!=q.back()) break;//特判。 
		sum=0; 
		while(!q.empty())//处理队头。 
		{
			c=q.front();
			q.pop_front();
			sum++;
			if(q.front()!=c) break;
		}
		while(!q.empty())//处理队尾。 
		{
			c=q.back();
			q.pop_back();
			sum++;
			if(q.back()!=c) break;
		}
		if(q.empty() && sum>=2)
		{
			cout<<sum+1;
			return 0;
		}
		if(sum<3) break;
	}
	cout<<0;
	return 0;
}
```


---

## 作者：copper_ingot (赞：0)

[洛谷](https://www.luogu.com.cn/problem/CF1267B)

[Codeforces](http://codeforces.com/problemset/problem/1267/B)

对于一个球的串，如果在其中加入一个球，那么必然是先删掉中间的一些球，然后逐步往外层删。

所以我们可以反过来考虑，从外往内删。

把球串塞到一个 `deque` 里，每次从两端分别删除一些一样的球，表示他们可以被删掉。

如果只剩下一个球或首尾的球不一样，说明无法继续删了，答案为 $0$。

如果某次删的球不足三个，说明没法删掉这些球，答案也为 $0$。

否则最后肯定会删到只剩下一些颜色一样的球，可以把一个球塞到两个球中间或所有球的两端，若剩下球的数量为 $x$，则方案数为 $x+1$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s; int n;
deque<char> q;
int main(){
	cin >> s; n = s.length();
	for (int i = 0; i < n; i++) q.push_back(s[i]);
	while (!q.empty()){
		if (q.size() == 1 || q.front() != q.back()){puts("0"); return 0;}
		int num = 0;
		while (!q.empty()){
			char nw = q.front(); q.pop_front();
			num++;
			if (nw != q.front()) break;
		}
		while (!q.empty()){
			char nw = q.back(); q.pop_back();
			num++;
			if (nw != q.back()) break;
		}
		if (q.empty() && num >= 2){printf("%d\n", num + 1); return 0;}
		if (num <= 2){puts("0"); return 0;}
	}
	return 0;
}
```

---

## 作者：__O_v_O__ (赞：0)

读完题可知，一串合法的球应该满足以下特点：

1. 两端球类型相同。

2. 两端相同类型的球个数大于等于 $3$ 个。

所以，我们用一个 ``deque`` 来存放球。每次先判断首字符和尾字符是否相同，再把左右相同的字符全部弹出，同时使用一个计数器来计弹出的个数，最后判断计数器是否小于 $3$ 即可。

但是题目要求的是合法种类数，怎么求呢？很简单，通过样例我们可以知道，一个合法的序列，它的种类数就是中间相同字符个数加 $1$。所以我们在弹出相同字符后，如果队列空了，答案就是现在的计数器加 $1$。

**AC代码：**
```cpp
#include<bits/extc++.h>
using namespace std;
#define BTS 0
#define STB 1
#define afor(i,n,m,dir) for(int i=n;dir?i<=m:i>=m;dir?i++:i--)
deque<char>q;char a;
signed main(){
	ios::sync_with_stdio(0);//cin优化
	while(cin>>a)q.push_back(a);
	while(!q.empty()){//循环直到队列空
		if(q.front()!=q.back()){cout<<0;return 0;}//检查左右两端字母是否相同
		int cn=0;char t=q.front();
		while(!q.empty()&&t==q.front())t=q.front(),q.pop_front(),cn++;//消除左边相同元素
		t=q.back();
		while(!q.empty()&&t==q.back())t=q.back(),q.pop_back(),cn++;//消除右边相同元素
		if(q.empty()&&cn>=2){cout<<cn+1;return 0;}//长度合法且已经枚举完则输出
		if(cn<3){cout<<0;return 0;}//判断左右长度是否合法
	}return 0;
}
```

---

