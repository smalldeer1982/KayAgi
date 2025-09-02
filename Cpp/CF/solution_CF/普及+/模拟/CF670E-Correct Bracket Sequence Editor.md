# Correct Bracket Sequence Editor

## 题目描述

`Polycarp`有一个长度为 $n$ 的括号串。

我们设 $pre_i$ 为字符串中第 $1$ 位到第 $i$ 位的左括号数量减去右括号数量，那么当每个 $1\leqslant i\leqslant n$ ， $pre_i\geqslant0$ 。同时 $pre_n=0$ 时，我们认为这个括号串合法。

现在`Polycarp`为合法括号串设计了一种编辑器，这个编辑器支持如下操作:

1. `L`，将光标左移一格
2. `R`，将光标右移一格
3. `D`，删除这个括号到与它对应的括号之间的所有字符，在删除之后，光标会跳到它右边的没有被删除的最左边的括号处，如果没有这样的括号了，那么光标会跳到它左边的没有被删除的最右边的括号处。

举个例子:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF670E/08b0f9032003921a97680a954e716fd13a3de759.png)

上图中，在第一排左边的串使用`D`，使得 $[2,3]$ 全部被删掉了。

第二排中，使用`D`，删除了 $[4,7]$ ，因为第 $7$ 个括号的配对括号在 $4$ 处。

第三排也是一样。

`Polycarp`的编辑器不支持错误的操作，例如删掉整个字符串。

`Polycarp`对他的设计感到自豪，但是他不会实现这个编辑器，所以他想请你来帮他实现，你能帮他实现编辑器的功能吗？

## 说明/提示

$1\leqslant p\leqslant n\leqslant 5\times 10^5,1\leqslant m\leqslant 5\times 10^5$

## 样例 #1

### 输入

```
8 4 5
(())()()
RDLD
```

### 输出

```
()
```

## 样例 #2

### 输入

```
12 5 3
((()())(()))
RRDLD
```

### 输出

```
(()(()))
```

## 样例 #3

### 输入

```
8 8 8
(())()()
LLLLLLDD
```

### 输出

```
()()
```

# 题解

## 作者：尹昱钦 (赞：3)

## 解题思路
首先可以用一个**栈**求出每个括号配对的括号的位置————
遇到左括号进栈，遇到右括号一定与当前的栈顶配对。

用**双向链表**储存一下某一个括号左面第一个没删的和右面第一个没删的括号的位置，这样可以 $O(1)$ 执行左移和右移操作，删除也用双向链表的基本操作 $O(1)$ 进行即可。

### 注意事项：
若第一个点的 left 设置为$-1$，则删点过程中一定要加 if 判断，防止越界。
## AC代码
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<stack>
using namespace std;
const int maxn=500005;
int n,m,p;
string s,s2; 
stack<int> st;
struct node{
	int left,right,to;
}e[maxn];
int main()
{
    cin>>n>>m>>p>>s>>s2;
    p--;
    for(int i=0;i<n;i++){
    	e[i].left=i-1;
    	e[i].right=i+1;
    	if(s[i]=='(') st.push(i);
    	else{
    		e[i].to=st.top();
    		e[st.top()].to=i;
    		st.pop();
		}
	}
	for(int i=0;i<m;i++){
		if(s2[i]=='L') p=e[p].left;
		else{
			if(s2[i]=='R') p=e[p].right;
			else{
				if(p>e[p].to) p=e[p].to;
				if(e[p].left!=-1) e[e[p].left].right=e[e[p].to].right;
				e[e[e[p].to].right].left=e[p].left;
				if(e[e[p].left].right==n) p=e[p].left;
				else p=e[e[p].to].right;
			}
		}
	}
	while(p>0&&e[p].left!=-1) p=e[p].left;
	while(p!=n){
		cout<<s[p];
		p=e[p].right;
	}
    return 0;
}
```

---

## 作者：卷王 (赞：1)

这一题要实现删除操作，所以可以使用双向链表。

但是在进行操作之前，我们需要先预处理一个括号的对应括号在哪个位置。设 $match_i$ 表示第 $i$ 个位置上的括号的对应括号的位置。然后用栈来维护每一个左括号的下标，碰到右括号就取栈头的匹配。

然后剩下的就是模拟了。

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, p, Q, T, _, ans = 0;
int match[500007];
char s[500007];
char a[500007];
stack<int> st;
int l[500007], r[500007];

signed main() {
	n = read(), m = read(), p = read();
	scanf("%s", s + 1); scanf("%s", a + 1);
	for(int i = 1; i <= n; i++) {
		if(st.empty()) st.push(i);
		else if(s[i] == '(') st.push(i);
		else if(s[st.top()] == '(') {
			match[i] = st.top();
			match[st.top()] = i;
			st.pop();
		}
	}
//	for(int i = 1; i <= n; i++)
//		cout << match[i] << " ";
//	cout << "\n";
	for(int i = 1; i <= n; i++)
		l[i] = i - 1, r[i] = i + 1;
	r[n] = n + 1, l[n + 1] = n;
	r[0] = 1, l[1] = 0;
	
	for(int i = 1; i <= m; i++) {
		if(a[i] == 'R') p = r[p];
		if(a[i] == 'L') p = l[p];
		if(a[i] == 'D') {
			int j = match[p];
			if(p > j) swap(p, j);
			r[l[p]] = r[j], l[r[j]] = l[p];
			
			if(r[j] != n + 1) p = r[j];
			else p = l[p];
		}
	}
	
	int t = r[0];
	while(t != n + 1) {
		printf("%c", s[t]);
		t = r[t];
	}
	return 0;
}
```

---

## 作者：One_JuRuo (赞：1)

## 思路

发现此题除了模拟没有好的方法，所以考虑如何模拟。

先考虑删除操作，如果在删除的时候再去找要删除那些的话，就会使时间复杂度变高，所以考虑先预处理出每个括号对应的位置。如果按照操作删除括号，那么时间复杂度也是非常吓人的。所以我们考虑标记被删除的括号。

再考虑移动操作，如果移动的下一个位置是被删除的操作，则跳转至下一个位置对应的括号的下一个位置，直到得到的位置没有被删除。

最后再关注一下删除后光标的移动方式，模拟就写完了

## TLE code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,p,tz[500005],z[500005],top;
bool vis[500005];
char s[500005],t[500005];
int main()
{
	scanf("%d%d%d%s%s",&n,&m,&p,s,t),--p;
	for(int i=0;i<n;++i)
		if(s[i]=='(') z[++top]=i;
		else tz[i]=z[top],tz[z[top--]]=i;
	for(int i=0;i<m;++i)
	{
		if(t[i]=='L')
		{
			--p;
			while(vis[p]) p=tz[p-1]-1;
		}
		if(t[i]=='R')
		{
			++p;
			while(vis[p]) p=tz[p+1]+1;
		}
		if(t[i]=='D')
		{
			vis[p]=vis[tz[p]]=1,p=max(p,tz[p]);
			int tp=p;
			if(p==n-1) while(vis[p]) p=tz[p]-1;
			else{++p;while(vis[p])p=tz[p]+1;}
			if(p==n){p=tp;while(vis[p]) p=tz[p]-1;}//如果左边没括号了，就跳转到左边第一个没删除的括号
		}
	}
	for(int i=0;i<n;++i)
	{
		if(vis[i]) i=tz[i];
		else printf("%c",s[i]);
	}
	return 0;
}
```

但是 TLE 了，怎么办？

先分析一下 TLE 的原因，如果在括号都是 ```()``` 且删除了一些括号的情况下，频繁地在被删除的括号左右移动，就非常容易超时。

所以考虑减少跳转的次数，想到了记录每个括号左右第一个没删除的位置，移动操作的时间复杂度就变成了 $O(1)$。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,p,tp,z[500005],top;
char s[500005],t[500005];
struct node{int l,r,tz;}a[500005];
int main()
{
    scanf("%d%d%d%s%s",&n,&m,&p,s,t),--p;
    for(int i=0;i<n;i++)
	{
    	a[i].l=i-1,a[i].r=i+1;
    	if(s[i]=='(') z[++top]=i;
    	else a[i].tz=z[top],a[z[top--]].tz=i;
	}
	for(int i=0;i<m;i++)
	{
		if(t[i]=='L') p=a[p].l;
		if(t[i]=='R') p=a[p].r;
		if(t[i]=='D')
		{
			p=min(p,a[p].tz),tp=a[p].tz;
			if(a[p].l!=-1) a[a[p].l].r=a[tp].r;//注意边界
			a[a[tp].r].l=a[p].l;
			if(a[a[p].l].r==n) p=a[p].l;
			else p=a[tp].r;
		}
	}
	while(p>0&&a[p].l!=-1) p=a[p].l;
	while(p<n) printf("%c",s[p]),p=a[p].r;
    return 0;
}
```


---

## 作者：ylch (赞：0)

[Luogu - CF670E](https://www.luogu.com.cn/problem/CF670E)

## Tips

1. 题目中的 $p$ 从 $1$ 开始。
2. 不用判断序列合法不合法的问题，原题干：
   > "It is followed by the string of $n$ characters '(' and ')' forming the correct bracket sequence." 

   说明序列一定是合法的。
3. 错误的操作（删掉整个序列、光标移动到串外）也不会发生，原题干：
   > "It is guaranteed that the given operations never move the cursor outside the bracket sequence, as well as the fact that after all operations a bracket sequence will be non-empty."
   
其中 2,3 条私认为是题目翻译漏了。本人第一次看中文题干的时候压根不知道“合法括号串”和“不支持错误的操作”在题目中的作用。

## Analysis

这道题的考点是括号匹配 + 模拟。考验基本功和综合能力。

首先，根据题目要求匹配对应括号可知，要用传统的括号匹配方法，把左括号和与之对应的右括号匹配起来，方便删除。

然后，考虑到题目要进行多次删除，用双向链表来存储括号串，插入删除复杂度 $O(1)$。

接下来直接模拟三种操作即可。注意一些细节和在 Tips 中说的东西，可以省去一些错误的判断。

时间复杂度是 $O(n)$ 的。代码实现看似在删除操作的双层循环使复杂度变成 $O(n^2)$，但因为字符串有 $n$ 个元素，每个元素只能被删一次，也就是说最多删除 $n$ 次。所以复杂度还是线性 $O(n)$ 的。

## Code

这里用了指针链表的形式实现，相当于给自己加了难度。大家可以参考。

```cpp
#include <bits/stdc++.h>
using namespace std;

struct LinkNode{
	char data; // 当前的字符：'(' 或 ')'
	int id; // 在串中的编号，用来确定两个迭代器之间的前后位置大
	LinkNode *matched; // 与之匹配的字符
	LinkNode *pre, *nxt; // 前驱节点、后驱节点
	
	LinkNode() : data('-'), id(0), matched(nullptr), pre(nullptr), nxt(nullptr) {}
};

// 指针一定初始化
LinkNode *head = nullptr, *tail = nullptr; // head是链表头，tail是链表尾

// 在链表后面插入it，tail的出现可以实现O(1)插入
void pushback(LinkNode *it){
	if(head == nullptr){ // 如果表头为空，就特殊初始化
		head = it;
		tail = it;
	}
	else{ // 先给tail和it之间的边连起来，再把it赋值给tail
		it->pre = tail;
		tail->nxt = it;
		tail = it;
	}
}

// 删除it节点
void remove(LinkNode *it){
	if(it == head){ // 特判it是开头的情况，避免头指针丢失
		head = it->nxt;
		it->nxt->pre = nullptr; // 置空，避免访问到已经被删除的内存
		delete it; // 已经没用了，直接删了就行。如果正常删的话，it->pre会访问到空指针从而运行错误
	} 
	else if(it == tail){ // 尾指针同理
		tail = it->pre;
		it->pre->nxt = nullptr;
		delete it;
	}
	else{
		it->pre->nxt = it->nxt;
		it->nxt->pre = it->pre;
		delete it; // 一定记得释放空间
	}
}

void solve()
{
	int n, m, p; cin >> n >> m >> p;
	LinkNode *cur = new LinkNode(); // cur是当前光标的位置
	
	// 输入括号序列
	for(int i = 1; i <= n; i ++){
		LinkNode *it = new LinkNode();
		cin >> it->data;
		it->id = i;
		pushback(it);
		if(i == p) cur = it; // 给光标初始化
	}
	
	// 进行括号匹配
	stack <LinkNode*> S;
	for(LinkNode *it = head; it != nullptr; it = it->nxt){
		if(it->data == '('){ // 左括号入栈
			S.push(it);
		}
		else{ // 右括号就和与其相连的左括号匹配。题目中保证括号序列一定合法
			it->matched = S.top();
			S.top()->matched = it;
			S.pop();
		}
	}
	
	// 处理 L,R,D 操作
	while(m --){
		char c; cin >> c;
		if(c == 'L'){ // 左移指针，题目保证指针不会移出序列
			cur = cur -> pre;
		}
		else if(c == 'R'){ // 右移指针，题目保证指针不会移出序列
			cur = cur->nxt;
		}
		else{ // 'D'操作，删除cur和cur->matched之间的所有字符。
			/*
			在删除之后，光标会跳到它右边的没有被删除的最左边的括号处，
			如果没有这样的括号了，那么光标会跳到它左边的没有被删除的最右边的括号处。
			*/
			// 确定cur和cur->>mathced的前后关系，方便遍历删除（注意这里涉及到指针操作，直接用swap可能出问题）
			LinkNode *begin, *end;
			if(cur->id < cur->matched->id) begin = cur, end = cur->matched;
			else begin = cur->matched, end = cur;
			// 确定删除后的光标位置
			LinkNode *tmp;
			if(end->nxt != nullptr){ // 先看“右边的没有被删除的最左边的括号处”是否为空
				tmp = end->nxt;
			} 
			else if(begin->pre != nullptr){ // 再看“左边的没有被删除的最右边的括号处”是否为空。题目保证不会删除成空串，所以这两个一定有一个不空
				tmp = begin->pre;
			}
			// 删除[cur,cur->matched]
			int end_id = (end->nxt == nullptr? -1 : end->nxt->id); // 如果end的下一个为空，就把end_id设置成一个永远无法达到的值。这样循环会通过 it!=nullptr 这一条件结束
			for(LinkNode *it = begin; it != nullptr && it->id != end_id; ){ //细节，把判断nullptr放在前面，这样不会导致后面的it->id运行错误 
				LinkNode *p = it;
				it = it->nxt;
				remove(p); // 注意一定先把it移到下一个位置再删除，不然会出现it丢失的情况
			}
			// 把正确的cur值赋值回去
			cur = tmp;
		}
	}
	
	// 输出结果，同时释放空间
	for(LinkNode *it = head; it != nullptr; ){
		LinkNode *p = it;
		cout << it->data;
		it = it->nxt;
		delete p; // 注意一定先把it移到下一个位置再删除，不然会出现it丢失的情况
		// 这里直接删就行，因为后面没用了
	}
}

signed main()
{
	ios :: sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	solve();
	return 0;
}
```

## End

错因总结：
1. 不能用 STL 的 list 搭配记录迭代器。因为 list 的迭代器在指向的元素被删除之后就会失效，不能再与其他点产生联系。
2. 指针的链表写法一定要注意各种越界、访问野指针等问题，细节往往最折磨人！身为程序员，一定要尽自己最大的努力让程序不出现一点 BUG！

管理员大大辛苦啦~

谢谢大家！

---

