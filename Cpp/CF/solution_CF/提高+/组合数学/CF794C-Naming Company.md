# Naming Company

## 题目描述

Oleg the client and Igor the analyst are good friends. However, sometimes they argue over little things. Recently, they started a new company, but they are having trouble finding a name for the company.

To settle this problem, they've decided to play a game. The company name will consist of $ n $ letters. Oleg and Igor each have a set of $ n $ letters (which might contain multiple copies of the same letter, the sets can be different). Initially, the company name is denoted by $ n $ question marks. Oleg and Igor takes turns to play the game, Oleg moves first. In each turn, a player can choose one of the letters $ c $ in his set and replace any of the question marks with $ c $ . Then, a copy of the letter $ c $ is removed from his set. The game ends when all the question marks has been replaced by some letter.

For example, suppose Oleg has the set of letters $ {i,o,i} $ and Igor has the set of letters $ {i,m,o} $ . One possible game is as follows :

Initially, the company name is ???.

Oleg replaces the second question mark with 'i'. The company name becomes ?i?. The set of letters Oleg have now is $ {i,o} $ .

Igor replaces the third question mark with 'o'. The company name becomes ?io. The set of letters Igor have now is $ {i,m} $ .

Finally, Oleg replaces the first question mark with 'o'. The company name becomes oio. The set of letters Oleg have now is $ {i} $ .

In the end, the company name is oio.

Oleg wants the company name to be as lexicographically small as possible while Igor wants the company name to be as lexicographically large as possible. What will be the company name if Oleg and Igor always play optimally?

A string $ s=s_{1}s_{2}...s_{m} $ is called lexicographically smaller than a string $ t=t_{1}t_{2}...t_{m} $ (where $ s≠t $ ) if $ s_{i} <  t_{i} $ where $ i $ is the smallest index such that $ s_{i}≠t_{i} $ . (so $ s_{j}=t_{j} $ for all $ j <  i $ )

## 说明/提示

One way to play optimally in the first sample is as follows :

- Initially, the company name is ???????.
- Oleg replaces the first question mark with 'f'. The company name becomes f??????.
- Igor replaces the second question mark with 'z'. The company name becomes fz?????.
- Oleg replaces the third question mark with 'f'. The company name becomes fzf????.
- Igor replaces the fourth question mark with 's'. The company name becomes fzfs???.
- Oleg replaces the fifth question mark with 'i'. The company name becomes fzfsi??.
- Igor replaces the sixth question mark with 'r'. The company name becomes fzfsir?.
- Oleg replaces the seventh question mark with 'k'. The company name becomes fzfsirk.

For the second sample, no matter how they play, the company name will always be xxxxxx.

## 样例 #1

### 输入

```
tinkoff
zscoder
```

### 输出

```
fzfsirk
```

## 样例 #2

### 输入

```
xxxxxx
xxxxxx
```

### 输出

```
xxxxxx
```

## 样例 #3

### 输入

```
ioi
imo
```

### 输出

```
ioi
```

# 题解

## 作者：Priori_Incantatem (赞：4)

[题目链接](https://www.luogu.com.cn/problem/CF794C)  
[在我的Blog查看](https://blog.csdn.net/Brian_Pan_/article/details/114869898)

### 题目大意

A,B 两人各有一个长度为 $n$ 的，由小写字母构成的字符串 $s,t$，还有一个长度为 $n$，初始时由 `?` 组成的目标串 $f$。

现在，A和B轮流进行如下操作：  
1. 在自己的字符串中选出一个字符 $x$。
2. 将 $f$ 中的一个 `?` 替换为 $x$。
3. 将 $x$ 从自己的字符串中删去。
当 $f$ 中没有 `?` 时游戏结束。

A 的目标是让 $f$ 的字典序尽量小，而 B 的目标是让字典序尽量大。  
现在设 A 为先手，你需要求出游戏结束后的 $f$。

注意：$s,t$ 中可能有多个重复的字符，**每次只删除一个**。

### 解题思路

一个显而易见的贪心思路，分别让 $s,t$ 升序和降序排序。  
然后，每个人尽可能把自己字符串中前面的字符放在 $f$ 的前面，从而最大/最小化 $f$ 的字典序。

如果你是这么写的话，恭喜你 `WA on test 6`。

这里来举一个反例：

```
s="pqrs"
t="dcba"
```

如果在这种情况下，还是按照上面的方法，那你会发现 A,B 在互相帮助QwQ。也就是说，两方的操作会对对方的目标产生好处。  
那么，我们的最优方案就变成了**止损**。由于在字符串越前面的字符，对字典序的影响就越大，所以，我们就尽可能地把对对方有利的字符往后放。  
比如对于这组数据，A 就需要尽可能地把字典序大的字母往 $f$ 的后面放，B 同理。

最后，我们将两个思路结合：  
当 $s_i<t_i$ 时，按第一种方法贪心。  
否则，就按第二种方法贪心。

有一些实现上的小细节，这里就不写了，直接上代码。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int Maxn=3e5+10;
char s[Maxn];
int a[Maxn],b[Maxn];
int f[Maxn];
int n;
inline bool cmp(int x,int y)
{
	return x>y;
}
int main()
{
	// freopen("in.txt","r",stdin);
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;++i)
	a[i]=s[i]-'a';
	scanf("%s",s+1);
	for(int i=1;i<=n;++i)
	b[i]=s[i]-'a';
	sort(a+1,a+1+n);
	sort(b+1,b+1+n,cmp);
	int x=0,y=0,pos=n;
	for(int i=1;i<=n;++i)
	{
		if(a[x+1]>=b[y+1]){pos=i-1;break;}
		if(i & 1)f[i]=a[++x];
		else f[i]=b[++y];
	}
	x=y=(n>>1)+1;
	if((n & 1))++x;
	for(int i=n;i>pos;--i)
	{
		if((pos+(n-i+1)) & 1)f[i]=a[--x];
		else f[i]=b[--y];
	}
	for(int i=1;i<=n;++i)
	putchar(f[i]+'a');
	putchar('\n');
	return 0;
}
```

---

## 作者：白简 (赞：3)

**[更好的阅读体验](https://www.cnblogs.com/baijian0212/p/CF794C.html)**
### 题目大意

奥列格和伊戈尔打算开一个公司，他们对于公司的取名有不同的意见。

他们两个各有一个长度相等的字符串，公司的名字最初是全由 $\texttt{?}$ 构成的一个字符串，两人轮流操作，在自己的字符串中选出一个字符取代公司名字中的某一个 $\texttt{?}$，使用后该字符就在当前操作者的字符串中消失了。

游戏结束当且仅当每一个 $\texttt{?}$ 都被两人的字符取代。

奥列格想要使得公司名字的字符串字典序最小，伊戈尔想要让公司名字的字符串字典序最大。

假设两人都进行最优操作，请求出操作结束后的公司名字。

### 思路

首先有一个比较显然的贪心思路。

为使得最终字符串的字典序最小，奥列格每次选取自己字典序最小的字符，放在能够放置的最前面位置，伊戈尔每次选取自己字典序最大的字符，也放在能够放置的最前面位置。

但这样的贪心是有问题的，会错在第 $6$ 个测试点。

考虑这样一种状况，奥列格剩下的字符中最小的都已经大于伊戈尔手中最大的，那么如果奥列格再往最前面放显然就是错的了。

这种状况下奥列格怎么最优操作呢？他可以把自己的字符往后放，这样伊戈尔就不得不把他小于奥列格的字符往前放。

那么在这种条件下，二者的最优策略就是把自己的字符从后往前放。

所以当奥列格仍然有小于伊戈尔的字符时，采取第一种策略，否则采取第二种策略。

具体代码可以用 `deque` 维护，支持取头尾元素，十分的方便。

时间复杂度 $\operatorname{O}(n)$。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;

string s,t;

deque<char> q1,q2;

int main() {
    cin >> s >> t;

    n = s.size();
    sort(s.begin(),s.end());

    sort(t.begin(),t.end());
    reverse(t.begin(),t.end());

    for(int i = 0;i < (n + 1) / 2; i++) 
        q1.push_back(s[i]);
    
    for(int i = 0;i < n / 2; i++)
        q2.push_back(t[i]);

    string ansl = "",ansr = "";
    
    bool flag = 0;
    for(int i = 1;i <= n; i++) {
        if(i % 2) {
            if(!q2.empty() && q1.front() >= q2.front())
                flag = 1;
            
            if(flag) {
                ansr += q1.back();
                q1.pop_back();
            }
            else {
                ansl += q1.front();
                q1.pop_front();
            }
        }
        else {
            if(!q1.empty() && q1.front() >= q2.front())
                flag = 1;
            
            if(flag) {
                ansr += q2.back();
                q2.pop_back();
            }
            else {
                ansl += q2.front();
                q2.pop_front();
            }
        }
    }
    
    reverse(ansr.begin(),ansr.end());

    string ans = ansl + ansr;

    cout << ans;
    return 0;    
}

```

---

## 作者：DPair (赞：1)

题解连更计划第5篇

## 【题意】
好题，但是翻译错了，然后讨论里的翻译不够全面，下面简述一下题意。

就是有三个长度为$n$的字符串$A$，$B$，$C$，其中$C$是一个仅由$'?'$构成的字符串。

现在$Oleg$和$Igor$每个人分别有一个字符串（可能会有重复元素），然后从$Oleg$开始轮流进行下列操作：

1. 选一个自己字符串中的字符
2. 把$C$中**任何一个位置**上的$'?'$字符替换为所选字符
3. 删去自己字符串中的所选字符

然后$Oleg$要尽可能使$C$字典序小，$Igor$反之，且两人都使用最优策略，求$C$。

## 【注意】
我上面已经标黑了——**任意一个位置**。不然这道题就太水了

## 【思路】
首先，我们很容易想到：

若$n \equiv 1(mod~2)$，则$Oleg$需要选出$\lfloor \frac n2 \rfloor + 1$个字母，而$Igor$需要选出$\lfloor \frac n2 \rfloor$个。

若$n \equiv 0(mod~2)$，则$Oleg$需要选出$\lfloor \frac n2 \rfloor$个字母，而$Igor$需要选出$\lfloor \frac n2 \rfloor$个。

而由于$Oleg$要尽可能让字典序小，他一定只会选出$A$**字符串中所有字母里字典序最小的那几个字母**，同理，$Igor$会选出$B$中最大的几个。

于是想到排序，然后分别储存两个人**一定会用到**的字母。

接下来思考对于这一些字母，两个人会怎么处理，即最优策略，得出后模拟即可。

## 【策略】
分两种情况讨论。

当$Oleg$所选字母中最小的已经比$Igor$所选的字母中最大的还要大了，例如
$${A}={b, c}~~{B}={a, a}$$
为了使字典序尽可能小，$Oleg$应该怎么做？

答案显而易见，**如果这一步不能使自己最优，那就防止自己最劣**。

因此，他应该把$'c'$放到$C$的最后一位，显然这是当前最优的（因为如果他对前面进行操作，后手一定可以使你更劣，比如你把$'b'$放到第二位，后手就可以把$'a'$放到最后一位，此时你一定更劣）。

所以，当$Oleg$所选字母中最小的已经比$Igor$所选的字母中最大的还要大了，就把$A$**必选的字母中**最大的放到$C$的最后。

而如果上述情况不发生，就按照一般思维，把自己最小的放在$C$最前面，防止对手抢占这个位置。

而$Igor$显然同理，这里不再赘述，留给读者思考。

等等，同理？

那么这两个人的程序显然可以合并起来写啊。

## 【写法】
这里提供一种很简便的代码写法。

先排序，这个不用说，也没什么技术含量。

由于要同时求最大值与最小值，想到单调队列，进一步想到$deque$来维护。

然后用类似于**滚动数组**的写法分别模拟两个玩家的所有操作策略，由于两人策略显然相同，应此程序相同，不用多次判断。

最后输出$C$即可。

下面给出程序。

```cpp
#include <bits/stdc++.h>
using namespace std;

char s[2][300010], ans[300010];//滚数写法
inline bool cmp(char x, char y)
{
	return x > y;
}

int ed, bg, len;

deque <char> a[2];

int main()
{
	scanf("%s%s", s[0], s[1]);
	len = strlen(s[0]);//要卡卡常，我在这里锅过
	sort(s[0], s[0] + len);
	sort(s[1], s[1] + len, cmp); 
	for (register int i = 0;i < len;i ++)
	{
		a[i & 1].push_back(s[i & 1][cur[i & 1] ++]);//存deque
	}
	bg = 0;
	ed = len - 1;
	for (register int i = 0;i < len;i ++)
	{
		if(a[0].front() >= a[1].front())//重头戏，这里面的转移可以思考一下
		{
			ans[ed --] = a[i & 1].back();
			a[i & 1].pop_back();
		}
		else
		{
			ans[bg ++] = a[i & 1].front();
			a[i & 1].pop_front();
		}
	}
	printf("%s", ans);
}
```

---

