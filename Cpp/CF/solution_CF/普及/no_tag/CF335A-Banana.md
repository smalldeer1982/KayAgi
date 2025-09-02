# Banana

## 题目描述

Piegirl is buying stickers for a project. Stickers come on sheets, and each sheet of stickers contains exactly $ n $ stickers. Each sticker has exactly one character printed on it, so a sheet of stickers can be described by a string of length $ n $ . Piegirl wants to create a string $ s $ using stickers. She may buy as many sheets of stickers as she wants, and may specify any string of length $ n $ for the sheets, but all the sheets must be identical, so the string is the same for all sheets. Once she attains the sheets of stickers, she will take some of the stickers from the sheets and arrange (in any order) them to form $ s $ . Determine the minimum number of sheets she has to buy, and provide a string describing a possible sheet of stickers she should buy.

## 说明/提示

In the second example, Piegirl can order 3 sheets of stickers with the characters "nab". She can take characters "nab" from the first sheet, "na" from the second, and "a" from the third, and arrange them to from "banana".

## 样例 #1

### 输入

```
banana
4
```

### 输出

```
2
baan
```

## 样例 #2

### 输入

```
banana
3
```

### 输出

```
3
nab
```

## 样例 #3

### 输入

```
banana
2
```

### 输出

```
-1
```

# 题解

## 作者：sysong (赞：3)

# 题解CF335A Banana

### 题目描述

Piegirl 正在为一个项目买贴纸。贴纸粘贴在纸张上，每一张纸都包含正好 $n$ 张贴纸。每一张贴纸上恰好只印了一个字符，所以纸张可以用一个长度为 $n$ 的字符串来描述。

Piegirl 想用贴纸创造一个字符串 $s$。她可以购买任意数量的纸张，并且可以把这些纸张指定为长度为 $n$ 的任意字符串，但是所有的纸张必须相同，因此所有纸张的字符串都是相同的。一旦她拿到了纸张，她会从纸张上取下一些贴纸，然后（按任意顺序）排列成 $s$。

确定她必须购买的最小纸张数，并提供一个字符串，描述她应该购买的可能的纸张。

如果没有符合要求的纸张，输出 `-1`。

### $Solution$

首先我们统计字符串中每个字符的出现个数，如果个数 $k > n$，显然无解。

如果有解，我们就要计算最少需要的纸张数。

怎么计算呢？

我们可以把所有字符存入一个优先队列，显然需要最多的字符总数除以当前添加到纸张字符串中的字符数（向上取整）就是答案。

用这个对字符进行比较，每一次对于最需要的字符数加一。

因为每个字符都肯定会出现，所以初始值都为一。

### $C++ \quad Code$

```c++
#include <bits/stdc++.h>
#define R register
using namespace std;

char s[1010],ans[1010];int n,t,l,f[30],p;
struct ch{
	int k,a;										// k 指该字符总数，a 指当前字符数
	char c;
	ch(){}
	ch(int _k,char _c):k(_k),a(1),c(_c){}			// a 的值即为初始化 1
	int st(){return (k-1)/a+1;}						// 按照目前选择计算，总共需要的纸张数目
}h[30];

bool operator <(ch a,ch b){
	return a.st()<b.st();							// 根据需要纸条数进行比较
}
priority_queue<ch> q;
int main(){
	scanf("%s%d",s,&n);
	l=strlen(s);
	for(R int i=0;i<l;i++)++f[s[i]-'a'];
	for(R int i=0;i<26;i++)
        if(f[i])
            q.push(ch(f[i],'a'+i)),					// 如果有该字符，则加入优先队列
    		ans[p++]='a'+i;							// 每一个字符都是必须的，所以开始就应该加入答案序列
	if(n<q.size()){printf("-1\n");return 0;}		// 如果纸张长度连字符数都不够，显然不行
	ch c;
	for(n-=q.size();n;--n){							// 之前已经添加过每个字符了，所以循环次数要减掉字符数
		c=q.top();q.pop();
		ans[p++]=c.c;
		c.a++;										// 如果还可以选择，那么最缺的优先
		q.push(c);
	}
	c=q.top();
	printf("%d\n",c.st());							// 最后队首元素需要的值即为答案
	puts(ans);
	return 0;
}
```





***by jsntsys***

$2020.11.30$

红名祭

upd 2020.12.2:更正了题目描述和一处笔误。

---

## 作者：A_small_WA (赞：1)

题意有点难理解，简单来讲就是需要你创造尽可能少的字符串每个字符串都一样且只包含 $n$ 个字符，希望可以从这些字符串里取出任意字符得到一个字符串 $s$。

首先第一眼小桶计数，先求出每个字符在 $s$ 中出现的个数，如果出现过的字符数量大于 $n$ 那肯定是不行的，因为每张纸都一样。输出 $-1$ 即可。

那么剩下的部分就剩构造了。可以确定，每个出现过的字符都要加入到纸上。此时如果之上的字符数量 $k$ 刚好等于 $n$，那就可以直接输出。但是，如果之上还有空间，该贴上哪个字符呢？

应该是在 $s$ 中出现次数最多的那个字符吧？如果你这么想，那么恭喜你将会 WA On #7。

我们可以用一个优先队列 $pq$ 来存出每个字符出现的个数，每次取出其中数量最多的那个字符，贴到纸上，只是我们需要算的是现在这张纸需要多少张，也就是 $k_1\div k_2$ 的最大值（$k_1$ 是 $s$ 中某个字符出现的个数，$k_2$ 表示纸上的对应字符出现个数），在优先队列里反复将 $k_1\div k_2$ 的最大的那个字符填入纸上，并改为 $k_1\div (k_2+1)$ 即可，记得每次要判断纸上的字符个数是否大于 $n$。最后输出剩下 $k_1\div k_2$ 的最大值即之上的字符就 OK 啦！
可以证明这样的贪心是正确的，因为每次改变最大值都会使最后需要使用的纸的张数减少。

最后是代码，应该很好理解：
```cpp
#include <bits/stdc++.h>
using namespace std;
int cnt[200],cnt1[200];
typedef pair <int,int> P;
//懒得用结构体了，first为k1/k2的值，second为字符对应的ASCII码。
priority_queue <P> pq;
string s,s1;
int n,ans;
int main(){
	cin>>s>>n;
	int m=s.size();
	for(int i=0;i<m;i++){
		cnt[s[i]]++;
	}
	for(int i=20;i<=130;i++){
		if(cnt[i]){
			s1+=char(i);
			cnt1[i]++;
			ans++;
			pq.push(P(cnt[i],i));
		}
	}
	if(ans>n){
		cout<<-1;
		return 0;
	}
	while(ans<n){
		s1+=char(pq.top().second);
		cnt1[pq.top().second]++;
		int a=cnt[pq.top().second]/cnt1[pq.top().second],
		b=pq.top().second;
      //注意余数对答案的影响！！！
		if(cnt[pq.top().second]%cnt1[pq.top().second]) a++;
     //这里比较麻烦的一点是pair的first不能--或++。
		pq.pop();
		pq.push(P(a,b));
		ans++;
	}
	cout<<pq.top().first<<endl<<s1;
	return 0;
}
```
这是蒟蒻的第 $6$ 篇题解，支持一下孩子吧！

---

