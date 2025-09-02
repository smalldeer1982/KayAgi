# [ICPC 2015 WF] Evolution in Parallel

## 题目描述

### 题目背景

公元2178年，人类在一颗遥远的行星上发现了外星生命。但是似乎这颗行星上只有单一物种而且它们并不像地球上的动物一样繁殖。更神奇的是，每个生物的基因构成是完全相同的！

每个生物的基因构成是单一核苷酸序列。在它们基因中有三种核苷酸，表示为‘A’  (腺嘌呤，Adenine), ‘C’ (胞嘧啶，Cytosine), and ‘M’ (膜嘌呤，Muamine)。根据某种假说，在这颗星球上只有某个新的核苷酸插入现存的生物基因序列某处时才会出现进化。如果这个改变是对进化有利的，这个带有新基因序列的生物会迅速取代没有变异的旧生物。

我们起初认为这种生物是从基因序列只含有单一核苷酸的生物经过多次上述的变异进化而来。然而化石证据表明可能并不是一直是这种情况。目前，与你协作的科研团队正在尝试证实“平行进化”的概念。“平行进化”指可能事实上有两条如同上述的进化路径，最终他们都进化成了这颗行星如今的物种。你的任务是证实平行进化假说是否与你的团队在化石中发现的遗传物质样本一致。 

( TRANSLATED by  [@MolotovM](https://www.luogu.com.cn/user/99461))

### 题目含义

给定1个字符串，n个字符串，求不多于两个的字符串的子串包含其他所有字符串，且这不多于两个的字符串都是给定字符串的子串。

## 样例 #1

### 输入

```
5
AACCMMAA
ACA
MM
ACMAA
AA
A
```

### 输出

```
1 4
MM
A
AA
ACA
ACMAA
```

## 样例 #2

### 输入

```
3
ACMA
ACM
ACA
AMA
```

### 输出

```
impossible
```

## 样例 #3

### 输入

```
1
AM
MA
```

### 输出

```
impossible
```

## 样例 #4

### 输入

```
4
AAAAAA
AA
AAA
A
AAAAA
```

### 输出

```
0 4
A
AA
AAA
AAAAA
```

# 题解

## 作者：Planetary_system (赞：1)

## 题面解释：
~~老实说看了 20 分钟没看懂题，给个好理解的把。~~

维护 $2$ 个栈，栈底元素为现在的生物的基因，需保证栈中上层元素为下层的子序列（怎么不算一种单调性呢）。

## 思路分析：
首先，若 $A$ 是 $B$ 的子序列，$B$ 是 $C$ 的子序列，那么显然 $A$ 是 $C$ 的子序列，那么保证栈的单调性只需要保证每次入栈元素是栈顶元素的子序列。

继续思考子序列的性质，若 $A$ 是 $B$ 的子序列则 $A$ 一定不比 $B$ 长，若一样长则二者必然相等。那么我们可以先按长度从大到小排序，正确性显然。

在保证前面策略正确的情况下，如果当前字符串不是两个栈顶中任意一个的子序列，无解。

我们发现，在一个字符串同时可以加入两边时，我们不知道如何安置这个字符串。那我们就建立一个缓存队列，队列一样满足单调性，里面存的字符串就是同时可以加入两个栈的，等到后面有更多信息再考虑。

那么这时，如果一个字符串只能加入其中一个栈，那么同时要把缓存压入另一个栈。因为如果缓存能压在这个字符串上当且仅当当前字符串与缓存里的字符串相同，那么必然可以进入缓存。

再进一步思考，我们就能发现，能同时加入两个栈的字符串不一定能加入缓存，这个时候我们随便压入一个栈，缓存压入另一个栈即可。不论这时候压入哪边，都是等价的。

最后输出的时候注意不要把最开始加入的初始元素输出即可。
## AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e3+10;
string S,s[N];
int n,len[N],id[N];
stack<string>s1,s2;
deque<string>_s;
inline bool cmp(int p,int q){
	return len[p]>len[q];
}
inline bool In(string p,string q){
	for(int i=0,j=0;j<q.size();j++){
		if(p[i]==q[j])i++;
		if(i==p.size())return 1;
	}
	return 0;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>S;
	for(int i=1;i<=n;i++)
		cin>>s[i],id[i]=i,
        len[i]=s[i].size();
	sort(id+1,id+n+1,cmp);
	s1.push(S);s2.push(S);
	for(int _i=1;_i<=n;_i++){
		int i=id[_i];
		bool bk1=In(s[i],s1.top());
		bool bk2=In(s[i],s2.top());
		if(bk1&&bk2){
			if(_s.empty()||In(s[i],_s.back()))
				_s.push_back(s[i]);
			else{
				s1.push(s[i]);
				while(!_s.empty())
					s2.push(_s.front()),
					_s.pop_front();
			}
		}
		else if(bk1){
			s1.push(s[i]);
			while(!_s.empty())
				s2.push(_s.front()),
				_s.pop_front();
		}
		else if(bk2){
			s2.push(s[i]);
			while(!_s.empty())
				s1.push(_s.front()),
				_s.pop_front();
		}
		else{cout<<"impossible";return 0;}
	}
	while(!_s.empty())
		s1.push(_s.front()),
		_s.pop_front();
	cout<<s1.size()-1<<' '<<s2.size()-1<<'\n';
	while(s1.size()>1)cout<<s1.top()<<'\n',s1.pop();
	while(s2.size()>1)cout<<s2.top()<<'\n',s2.pop();
	return 0;
}
```
有[双倍经验](https://www.luogu.com.cn/problem/UVA1713)，但是不知道为什么过不了。

完结撒花！！！

---

## 作者：FangZeLi (赞：1)

## Link

[[ICPC2015 WF]Evolution in Parallel](https://www.luogu.com.cn/problem/P6908)

## Solution

为数不多独立做出来的国集作业题/wul，做完后发现题解区里已经有一篇一样的解法了，不过我讲的方法可能不太一样。

首先我们要明白，这是一个可以贪心的问题。

也就是说，我们可以先将字符串长度从大到小排序，这样的话，我们就可以依次将字符串加入序列。如果一个字符串在此时不能加入，那之后也不可能被加入。所以这样肯定是可行的。

然后我们考虑一个字符串一个字符串加的过程。

1. 如果我们当前加入的字符串不能加入两个队列中的任何一个，那么直接输出无解。

2. 如果只能加入其中的一个，就直接加入。

如果两个都能加呢？

我们发现这个比较麻烦，因为两种选择显然是有区别的。而我们显然不可能枚举。

我们可以考虑这样的字符串对后面的影响。

首先，如果有连续的一堆都是两个队列都可以放的话，那么我们肯定集中放到一处。因为分散放会使两个队列能容纳的字符串集合同时缩小。

然后，最大问题无非就是，现在来了一个只能放在一边的字符串，而由于我们**之前的一个错误的选择**，导致**一个放两边都行的字符串序列**放错位置，把当前字符串能接的位置占了。如何避免这个问题？

我们额外再维护一个字符串序列，代表两边都可以加的。那么当我们遇到一个两边都可以加的字符串时，我们就尝试将其加入这个字符串序列中。如果能加入的话，就不在进行其他操作；如果不能加入，我们就将之前的等待序列加入两个序列中的一个，并将当前的字符串加入另外一个。（由上面的论述，这个显然是正确的）

同时，上面讨论的2情况也要发生改变：我们要将等待序列加入另一个序列，因为在其中一个加入了一个字符串后，之前的等待序列已经不可以加入该字符串序列了。

最后，当遍历完后，若等待序列非空，不要忘记随便加入一个序列。

## Code 

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>

#define _N 4010

int n;

char cur[_N];
int len[_N], pos[_N];
char input[_N][_N];

char *s1, *s2, *s3;
std::deque<int> q1, q2, q3;

bool check(char* x, char* y) {
	int xlen = strlen(x + 1), ylen = strlen(y + 1);
	if (xlen <= ylen) {
		return false;
	}
	for (int i = 1, j = 0; i <= xlen; i++) {
		if (x[i] == y[j + 1]) {
			j++;
		}
		if (j == ylen) {
			return true;
		}
	}
	return false;
}

bool inline cmp(int left, int right) {
	return len[left] > len[right];
}

int main() {
	scanf("%d", &n);
	scanf("%s", cur + 1);
	s1 = s2 = cur, s3 = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%s", input[i] + 1);
		len[i] = strlen(input[i] + 1);
		pos[i] = i;
	}
	std::sort(pos + 1, pos + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		char *now = input[pos[i]];
		bool f1 = check(s1, now), f2 = check(s2, now);
		if (!f1 && !f2) {
			puts("impossible");
			return 0;
		} else if (f1 && f2) {
			if (!s3 || check(s3, now)) {
				q3.push_back(pos[i]);
				s3 = now;
			} else {
				s1 = now, s2 = s3, s3 = 0;
				q1.push_back(pos[i]);
				while (!q3.empty()) {
					q2.push_back(q3.front());
					q3.pop_front();
				}
			}
		} else {
			if (!f1) {
				std::swap(s1, s2);
				std::swap(q1, q2);
			}
			s1 = now, s2 = (s3 ? s3 : s2), s3 = 0;
			q1.push_back(pos[i]);
			while (!q3.empty()) {
				q2.push_back(q3.front());
				q3.pop_front();
			}
		}
	}
	if (s3) {
		s1 = s3;
		while (!q3.empty()) {
			q1.push_back(q3.front());
			q3.pop_front();
		}
	}
	printf("%d %d\n", q1.size(), q2.size());
	while (!q1.empty()) {
		printf("%s\n", input[q1.back()] + 1);
		q1.pop_back();
	}
	while (!q2.empty()) {
		printf("%s\n", input[q2.back()] + 1);
		q2.pop_back();
	}
	return 0;
}
```

## Inspiration

我认为这题的解决过程就是要先有一个大体思路（贪心），然后不断地修补细节。中间的转化还是比较巧妙的。

核心结论：

1. 子序列结构有偏序关系，可以贪心。
2. 当一时不能进行决策时不妨进行延后，之后再进行选择。

---

## 作者：xtx1092515503 (赞：1)

（介于暂时没有SPJ，本代码在是CF上通过的）

**[Portal to LG](https://www.luogu.com.cn/problem/P6908)**

**[Portal to CF GYM](https://codeforces.ml/gym/101239)**

我们首先可以写出一个 ```SS(u,v)``` 函数，它判断串 $v$ 是否严格是串 $u$ 的子序列。

```cpp
bool SS(int u,int v){//if v is a non-equal subsequence of u
	if(len[u]<=len[v])return false;
	for(int i=0,j=0;i<len[u];i++){
		if(s[u][i]==s[v][j])j++;
		if(j==len[v])return true;
	}
	return false;
}
```

借助此函数，我们可以实现一种构造方式：

我们将所有串按照长度从大到小排序，并设两个数组 $s1,s2$ 分别维护两个序列。初始时两个序列中都只有现存的那条DNA。

当插入一个串时：

1. 假如它一个都插不进去，直接判无解；

2. 假如它能插，但只能插一个，直接插入序列末尾；

3. 假如它两个都能插：

我们另外开一个数组 $s3$ 维护这些两个都能插的东西。假如当前串能插入 $s3$ 末尾，直接插入 $s3$；否则，将其插入 $s1,s2$ 中任何一个序列，并将 $s3$ 中元素顺次插入另一个序列。

同时，在情况（2）中，我们要将 $s3$ 全都插入另一个序列——因为此时 $s3$ 中元素已经不再是两个都能插了。

在全部串都插入完成后，将 $s3$ 插入任何一个序列。

显然这个方法可以构造出一种合法状态（假如它存在的话）。证明如下：

（1）和（2）的操作显然是唯一且合法的。

在（3）中，对于当前串和 $s3$ 中所有串，$s1$ 和 $s2$ 都是等价的；假如当前串和 $s3$ 是共存的，显然它们可以被一起处理，故插入 $s3$；否则，因为 $s1,s2$ 等价，故可以让其中一个随便插，另一个便可以插入另一个序列。

时间复杂度 $O(nm)$，其中 $n$ 是数量，$m$ 是串长。因为每个串插入时最多比较 $3$ 次，所以复杂度正确。

主函数：

```cpp
void p1(int ip){
	for(int i=1;i<=t3;i++)s2[++t2]=s3[i];
	t3=0;
	s1[++t1]=ip;
}
void p2(int ip){
	for(int i=1;i<=t3;i++)s1[++t1]=s3[i];
	t3=0;
	s2[++t2]=ip;	
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<=n;i++)scanf("%s",s[i]),len[i]=strlen(s[i]),ord[i]=i;
	for(int i=1;i<=n;i++)if(!SS(0,i)){puts("impossible");return 0;}
	sort(ord,ord+n+1,[](int u,int v){return len[u]>len[v];});
	for(int i=1;i<=n;i++){
		bool x=SS(s1[t1],ord[i]),y=SS(s2[t2],ord[i]);
		if(!x&&!y){puts("impossible");return 0;}
		if(x&&!y)p1(ord[i]);
		if(!x&&y)p2(ord[i]);
		if(x&&y){
			if(!t3||SS(s3[t3],ord[i]))s3[++t3]=ord[i];
			else p1(ord[i]);
		}
	}
	for(int i=1;i<=t3;i++)s1[++t1]=s3[i];
	printf("%d %d\n",t1,t2);
	for(int i=t1;i;i--)printf("%s\n",s[s1[i]]);
	for(int i=t2;i;i--)printf("%s\n",s[s2[i]]);
	return 0;
}
```

---

## 作者：Filberte (赞：0)

对所有串按长度排序，按照顺序把每个串放入第一个或第二个序列中。每个序列需要满足，序列中每个串都是上一个串的子序列，若能找到一种方法把 $n$ 个串序列都放入则合法。

考虑如果前 $i - 1$ 个串都已经放好了，现在要决策第 $i$ 个串往哪个序列中放。如果两个序列都无法放入，显然无解；如果只有一个序列可以放入，则放入该序列；难点在于两个序列都可以放入的情况。我们可以增设一个“等待序列”，表示暂时无法决策的串，且满足每个串都是上一个串的子序列。

当目前串两个序列都可放入时，若等待序列为空或当前串是等待序列最后一个串的子序列时，将其放入等待序列中。否则这个串肯定会放到第一个序列后，而把等待序列中的串全部放到第二个序列后（交换等价）；当目前串只能放入一个序列时，则把它放到对应序列后，而把等待序列种所有串放到另一个序列后，此时相当于决策了等待序列中串的放置方法。

复杂度分析：每个串的长度不超过 $N$，因此可以 $O(N)$ 判断某个串是不是另一个串的子串，这样的判断最多执行 $O(N)$ 次，总复杂度 $O(N^2)$。实现时应当使用指针或标准模板库中的交换函数，否则暴力交换会导致复杂度退化至 $O(N^3)$。

总结：在决策的过程中，如果无法立即决策的状态，可以考虑先把当前状态存储下来，等到遇见一个限制更严的状态的时候再对当前状态进行决策。

---

