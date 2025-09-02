# Chat Order

## 题目描述

有一个队列，初始时为空。现在依次插入 $n$ 个单词，如果这个单词已经在队列中，那就把这个单词从原来位置移到队首，否则直接把这个单词放到队首。问你最后这个队列长啥样。

## 样例 #1

### 输入

```
4
alex
ivan
roman
ivan
```

### 输出

```
ivan
roman
alex
```

## 样例 #2

### 输入

```
8
alina
maria
ekaterina
darya
darya
ekaterina
maria
alina
```

### 输出

```
alina
maria
ekaterina
darya
```

# 题解

## 作者：Michael123456 (赞：9)

本蒟蒻献上翻译，此为我的教练翻译，不要给我加贡献。

Problem

有一个队列，初始时为空。现在依次插入nn个单词，如果这个单词已经在队列中，那就把这个单词从原来位置移到队首，否则直接把这个单词放到队首。
问你最后这个队列长啥样。

Input Data

第一行，一个整数n(1 \le n \le 200000)n(1≤n≤200000)，表示单词的数量；
接下来nn行，每行一个单词，每个单词都由小写字母构成，非空且长度均不超过1010。

Output Data

若干行，每行一个单词，依次表示从队首到队尾的每个单词。

Input Sample 1

4

alex

ivan

roman

ivan

Output Sample 1

ivan

roman

alex



反向思考：一个名字最多在队列中出现一次，输出也最多一次，所以从红往前扫最后一次出现的位置就好啦。

可以用map记录一个名字是否被输出。

```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<string>
#include<map>
#include<iostream>
using namespace std;

map<string,bool>mp;
int n;
string s[200000+10];

int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=n;i>=1;i--)
	{
		if(mp[s[i]])continue;
		cout<<s[i]<<'\n';
		mp[s[i]]=true;
	}
	return 0;
} 

```

---

## 作者：反手一只MJJ (赞：2)

# 我觉得“栈+bool”会比“队”更方便↓


### 题目描述

有一个队列，初始时为空。现在依次插入n个单词，如果这个单词已经在队列中，那就把这个单词从原来位置移到队首，否则直接把这个单词放到队首。问你最后这个队列长啥样。

### 输入输出格式

#### 输入格式：

第一行，一个整数 n ( 1 ≤ n ≤ 200000 )，表示单词的数量。接下来 n 行，每行一个单词，每个单词都由小写字母构成，非空且长度均不超过 10 。

#### 输出格式：

若干行，每行一个单词，依次表示从队首到队尾的每个单词

~~——————————完美的分界线———————————~~

### 若按照题目机械式思维：
###  先queue，然后每次输入一个人名"a"，在队里扫一遍，if队列中没出现过"a"则在队首插入"a"(注意不是队尾)；if"a"已经在队伍里，则删除"a"，再在队首插入“a”。最后一次性从队首输出到队尾。【中间的判重会影响时间复杂度】

#### 1.由上可以看到，可以把过程分为：①输入，②判重&删除，③插入"a"，④输出；且是按照①②③,①②③,①②③....④,④,④..的顺序执行；

#### 2.然而①的最坏情况是从头扫到尾(O(n))。因为所有的人是从**队首**插入队伍的，而输出也是从头到尾，所以先出来的人后面不可能再出来(被判重删除了)。
#### 3.所以，这个“判重队列”可以用栈(先进先出)来实现，执行顺序为①③,①③,①③...(②:仅查看一项而非从头扫到尾)④，(②)④，(②)④...
#### 下面是代码↓

```cpp
#include<bits/stdc++.h>//万能库
using namespace std;
map<string,bool>ma;//创立一个map容器,用于string"a"的判重。
string a;
stack<string>Tony;//不用队列okk。
int n;
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a;//-->①
		Tony.push(a);//-->③
		ma[a]=1;
	}//先不判重，全部进栈进栈。
	for(int i=0;i<n;i++)//边输出边判重
	{
		if(ma[Tony.top()]==0);//-->(②)
		else {cout<<Tony.top()<<endl;ma[Tony.top()]=0;}//-->④
		Tony.pop();
	}
	return 0;
}
```
### 实际上可连栈都不用，只不过是本蒟蒻用惯了栈而非队。
#### 还有——》学习一下容器map，判重很有用！


---

## 作者：UperFicial (赞：1)

# 不同于其它题解的做法

### 前言

逗比题，但显然我 $WA$ 了一次/kk

网址：[$\text{Link}$](https://www.luogu.com.cn/problem/CF637B)

这里讲一个不同于其它题解的做法。

### 题意

有 $n$ 个单词，你需要顺序将它们插入到队首，若这个单词已经在队列中，那么就把原来的那个单词移至队首，问你最后这个队列长啥样。

### 题解

这完全就是个模拟题，但如果要暴力模拟显然 $T$ 飞。

不过我们发现，题目中涉及了很多的删除和插入操作，**链表**这一简单的数据结构便可 $O(1)$ 解决。

我们定义一个双向链表 $lst$，其中额外有一个 $string$ 类型的变量的 $x$，代表这个位置存的 $string$。

但是链表如果在队首放元素貌似不太好办，我们可以先把每个单词放到队尾，到时候反着输出就 $OK$ 了。

在队尾插入一个元素是很好解决的，只要把尾指针 $+1$ 后赋值就好了：

```cpp
void push_end(string x)
{
	tail++;
	lst[tail].x=x;
	return;
}
```
将全部数据插入后，再用一次 $O(n)$ 的时间去重，我们定义 $pos[s]$ 为字符串 $s$ 在 $lst$ 中的位置。为什么要设立这个 $pos$，是因为我们对于每个 $s'$ 可以知道它有没有出现过，没有出现过显然它就不动，并将 $pos[s']$ 赋值，否则就说明已经出现过，我们需将上一个位置直接删除，但别忘了再更新 $pos[s']$ 的位置，因为上一个元素已经删除了，真正的位置已经变了。

时空复杂度：$O(n)$。

[$code$](https://paste.ubuntu.com/p/qdHCCtdPWS/)

$$\texttt{The End.by UF}$$




---

## 作者：Eason_AC (赞：1)

## Content
有 $n$ 个字符串，每次出现这个单词就把这个单词放到队列的队首（若已经出现就把原队列里面的那个单词提到队首），求最后的队列由队首到队尾的元素依次是多少。

**数据范围：$1\leqslant n\leqslant 2\times 10^5$。**
## Solution
直接用结构体存储一下每个字符串最后出现的位置（可以用 $\texttt{map}$ 直接映射），然后我们按出现的位置从大到小排序即可。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

struct node {
	string name;
	int last;
	bool operator < (const node& cjy) const {return last > cjy.last;}
}a[200007];
map<string, int> vis;
int n, cnt;

int main() {
	//This program is written in Ubuntu 16.04 by Eason_AC
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		string s;
		cin >> s;
		if(!vis[s]) {
			a[++cnt].name = s;
			vis[s] = cnt;
		}
		a[vis[s]].last = i;
	}
	sort(a + 1, a + cnt + 1);
	for(int i = 1; i <= cnt; ++i)
		cout << a[i].name << endl;
	return 0;
}

```

---

## 作者：happybob (赞：0)

本题不难，用 `map` 模拟即可。注意要倒序模拟，代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
map<string, bool> mp;
string s[N];

int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> s[i];
	for (int i = n; i >= 1; i--)
	{
		if (mp[s[i]]) continue;
		cout << s[i] << endl;
		mp[s[i]] = true;
	}
	return 0;
}
```


---

