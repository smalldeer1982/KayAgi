# [ABC158D] String Formation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc158/tasks/abc158_d

高橋君は、英小文字から成る文字列 $ S $ を持っています。

この $ S $ から始めて、ある与えられた手順に従って文字列を作ることにしました。

手順は $ Q $ 回の操作から成ります。操作 $ i(1\ \leq\ i\ \leq\ Q) $ では、まず整数 $ T_i $ が与えられます。

- $ T_i\ =\ 1 $ のとき : 文字列 $ S $ の前後を反転する。
- $ T_i\ =\ 2 $ のとき : 追加で整数 $ F_i $ と英小文字 $ C_i $ が与えられる。
  
  
  - $ F_i\ =\ 1 $ のとき : 文字列 $ S $ の先頭に $ C_i $ を追加する。
  - $ F_i\ =\ 2 $ のとき : 文字列 $ S $ の末尾に $ C_i $ を追加する。

高橋君のために、手順の後に最終的にできる文字列を求めてあげてください。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 10^5 $
- $ S $ は英小文字から成る
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ T_i\ =\ 1 $ または $ 2 $
- $ F_i\ =\ 1 $ または $ 2 $
- $ C_i $ は英小文字である

### Sample Explanation 1

$ Q\ =\ 4 $ 回の操作を行います。初め $ S $ は `a` です。 - 操作 $ 1 $ : $ S $ の先頭に `p` を追加する。$ S $ は `pa` となる。 - 操作 $ 2 $ : $ S $ の前後を反転する。$ S $ は `ap` となる。 - 操作 $ 3 $ : $ S $ の末尾に `c` を追加する。$ S $ は `apc` となる。 - 操作 $ 4 $ : $ S $ の前後を反転する。$ S $ は `cpa` となる。 よって最終的にできる文字列は `cpa` となります。

### Sample Explanation 2

$ Q\ =\ 6 $ 回の操作を行います。初め $ S $ は `a` です。 - 操作 $ 1 $ : $ S $ は `aa` となる。 - 操作 $ 2 $ : $ S $ は `baa` となる。 - 操作 $ 3 $ : $ S $ は `aab` となる。 - 操作 $ 4 $ : $ S $ は `aabc` となる。 - 操作 $ 5 $ : $ S $ は `cbaa` となる。 - 操作 $ 6 $ : $ S $ は `aabc` となる。 よって最終的にできる文字列は `aabc` となります。

## 样例 #1

### 输入

```
a
4
2 1 p
1
2 2 c
1```

### 输出

```
cpa```

## 样例 #2

### 输入

```
a
6
2 2 a
2 1 b
1
2 2 c
1
1```

### 输出

```
aabc```

## 样例 #3

### 输入

```
y
1
2 1 x```

### 输出

```
xy```

# 题解

## 作者：Buried_Dream (赞：2)

## 题意：

给你一个字符串 $s$。

有三种操作，字符串反转，字符串的头部插入字符，字符串的尾部插入字符。

输出最后操作过后的字符串。

## Solution

如果按照题目模拟，显然会超时。

当你反转过后，这两个操作就相当于换一下，于是我们只需要用一个变量来记录这个字符串是否被反转了，被反转偶数次相当于没反转。

我们的字符串是始终不反转的，我们是把操作反转了。

用 string 来模拟就行了。

```cpp
string s;

signed main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> s;
	int f = 0;
	int T; cin >> T;
	while(T--) {
		int opt; cin >> opt;
		if(opt == 1) f ^= 1;
		else if(opt == 2) {
			int x;
			cin >> x;
			string t; cin >> t;
			if(x == 1) { 
				if(!f)  t += s, s = t;
				else s += t;
			}
			else if(x == 2) {
				if(!f) s += t; 
				else t += s, s = t;
			}
		}
	}
	if(!f) cout << s;
	else {
		int len = s.length();
		for(register int i = len - 1; i >= 0; i--) cout << s[i];	
	}
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：2)

显然，这是一道数据结构题。不考虑操作 $1$ 的话，我们可以用双端队列 ```deque``` 维护。

然后再看操作 $1$ ，这显然不影响插入！我们只需要打一个标记，将操作反转即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
string st;
deque<char> s;
int q, f, opt, x;
char y;
int main() {
	cin >> st >> q;
	for (char ch : st)
		s.push_back(ch);
	for (int i = 1; i <= q; i ++) {
		cin >> opt;
		if (opt == 1) f ^= 3; // 打标记
		else {
			cin >> x >> y;
			if ((x ^ f) == 1) s.push_front(y); // 反转操作
			else s.push_back(y);
		}
	}
	if (f) reverse(s.begin(), s.end());
	for (char ch : s)
		cout << ch;
	return 0;
}

```


---

## 作者：lizhous (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT5370)  
~~大水黄~~
## 分析
由于涉及到翻转，不用数据结构必须 $O(n^2)$ ，所以我们考虑不翻转。  
我们发现翻转会影响插入操作，而在一个反转字符串前插入一个字符，等同于在原序列后插入。同理，在一个反转字符串后插入一个字符，等同于在原序列前插入。  
所以最终我们只需要维护当前字符串的翻转状态，按要求模拟，最后输出时特殊处理即可。此时我们开两个字符数组记录前后插入的字符以减小常数。
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
int n, t, opt, len1/*前插入个数*/, len2/*后插入个数*/, zp/*翻转状态*/;
string a;
char ch, front[200001]/*前插入*/, back[200001]/*后插入*/;
int main() {
	cin >> a;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &opt);
		if (opt == 1) {
			zp ^= 1; //翻转
		} else {
			scanf("%d %c", &opt, &ch);
			if ((opt + zp) & 1) { //现在应该在前面插入
				front[++len1] = ch;
			} else { //在后面插入
				back[++len2] = ch;
			}
		}
	}
	if (zp) { //输出时是反的
		for (int i = len2; i >= 1; i--) { //先输出尾
			printf("%c", back[i]);
		}
		for (int i = a.size() - 1; i >= 0; i--) cout << a[i]; //原序列翻转
		for (int i = 1; i <= len1; i++) { //再输出头
			printf("%c", front[i]);
		}
	} else { //正常输出
		for (int i = len1; i >= 1; i--) {
			printf("%c", front[i]);
		}
		cout << a;
		for (int i = 1; i <= len2; i++) {
			printf("%c", back[i]);
		}
	}
}
```


---

## 作者：BMTXLRC (赞：2)

一道有翻转操作的题怎么能没有文艺平衡树。

这个文艺平衡树需要支持的操作不多，可能甚至不需要分裂函数（我用的是 FHQ
_Treap）。而且其实就是个文艺平衡树的板子题。

输出答案序列的时候由于文艺平衡树符合二叉搜索树性质，且按照下标为权值，是可以直接进行**中序遍历**得到答案的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
struct FHQ_treap{
	int l,r,pri;
	int x,size,tag;
}a[N];
int n,m,cnt,root;
int new_node(int x){
	int now=++cnt;
	a[now].size=1,a[now].pri=rand();
    a[now].x=x;
	return now;
}
void reverse(int now){
	swap(a[now].l,a[now].r);
	a[now].tag^=1;
}
void pushdown(int now){
	if(!now) return;
	if(a[now].tag==1){
		if(a[now].l) reverse(a[now].l);
		if(a[now].r) reverse(a[now].r);
		a[now].tag=0;
        //标记下传，跟我们平常见到的线段树下传标记是一模一样的
	}
}
void pushup(int now){
	if(!now) return;
	a[now].size=a[a[now].l].size+a[a[now].r].size+1;
    //这个是维护每个节点相关的值，在线段树中跟 a[x].sum=a[x<<1].sum+a[x<<1|1].sum 是一样的
}
int merge(int x,int y){//跟左偏树一模一样
	if(!x||!y) return x+y;
	if(a[x].pri<a[y].pri){
		pushdown(x);
		a[x].r=merge(a[x].r,y);
        //根据随机的权值，维护 Treap 的性质，小权值在上，且要满足二叉搜索树性质
		pushup(x);
		return x;
	}else{
		pushdown(y);
		a[y].l=merge(x,a[y].l);
		pushup(y);
		return y;
	}
}
void split(int now,int k,int &x,int &y){
	if(!now){//分到叶子了
		x=y=0;
		return;
	}
	pushdown(now);
	if(a[a[now].l].size<k){//意思是说，把所有在序列中下标小于 k 的，都分出一棵树来
		x=now;
		split(a[now].r,k-a[a[now].l].size-1,a[now].r,y);
        //打过权值线段树的也知道，这玩意很像权值线段树的查找，权值线段树可以进行离线的普通平衡树操作查询！！原理也不复杂自己在纸上画一下就知道了
	}else{
		y=now;
		split(a[now].l,k,x,a[now].l);
	}
	pushup(now);
}
void dfs(int now){
    if(a[now].tag) pushdown(now);//跟线段树查询差不多，你查一个点的时候总要下传标记的
    if(a[now].l) dfs(a[now].l);
    printf("%c",a[now].x);
    if(a[now].r) dfs(a[now].r);
    return;//由于维护的是下标，且满足二叉搜索树性质，理解一下就是中序遍历得到答案序列
}
char ch[N];
int main(){
    scanf("%s",ch+1);
    for(register int i=1;i<=strlen(ch+1);i++) root=merge(root,new_node(ch[i]));
	scanf("%d",&m);
	for(register int i=1;i<=m;i++){
        int pos,x,y,z,k,op;
        char ch;
		scanf("%d",&op);
		if(op==2){
			scanf("%d %c",&pos,&ch);
            if(pos==1) pos=0;
            else pos=a[root].size;
			split(root,pos,x,y);
			root=merge(merge(x,new_node(ch)),y);
            //插入的流程是先按照下标分成两棵树，再将这三棵树按照原来的秩序合并，非常重要的细节，一点都不能打错
            //事实上由于这道题的特殊性质，我们甚至可以不需要进行分裂操作，思考一下
		}
		if(op==1) reverse(root);
	}
    dfs(root);
}
```

---

## 作者：Anaxagoras (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT5370)

### 0x00 所需知识

STL 双端队列 deque

### 0x01 思路

首先我要说在前面，暴力模拟的人歇一歇吧，看看范围，$1\le Q\le2\times10^5$，翻转次数过多不超时才怪！这里我要介绍一种~~高级~~优化策略。

首先则让输入的进入双端队列。我们可以用一个布尔变量来储存是否翻转，而插入的时候则看这个布尔变量是否改变，如果改变，则与题意唱反调，反之则依题意处理。

最后输出时也看变量是否改变，改变则反着输出，否则顺序输出。

### 0x02 AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
deque<char>q;
int n,lx,cr,len;
char c;
bool fz;
string st; 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>st>>n;
	for(int i=0;i<st.size();i++)
	{
		q.push_back(st[i]);//首先把输入的字符串入队
	}
	for(int i=1;i<=n;i++)
	{
		cin>>lx;
		if(lx==1)
		{
			fz=!fz;//翻转标记
		}
		else
		{
			cin>>cr>>c;//如果使用 cin 则不用过滤空格
			if(fz)//要翻转，唱反调
			{
				if(cr==1)
				{
					q.push_back(c);
				}
				else
				{
					q.push_front(c);
				}
			}
			else//不用翻转，按题意插入
			{
				if(cr==1)
				{
					q.push_front(c);
				}
				else
				{
					q.push_back(c);
				}
			}
		}
	}
	len=q.size();
	for(int i=1;i<=len;i++)
	{
		if(fz)//要翻转，反着输出
		{
			cout<<q.back();
			q.pop_back();
		}
		else//不用翻转，顺序输出
		{
			cout<<q.front();
			q.pop_front();
		}
	}
	return 0;
}
```

跪求点赞，球球了，蟹蟹！

---

## 作者：allqpsi (赞：0)

这是一道模拟题，解法如下：
## 问题：

这道题用暴力很显然是会爆的的，呢么，问题是，我们怎么优化呢？

## 思路：

其实，我们不必每次都把字符串反过来，只要记录有没有反过来就可以了。

然后，再根据情况把输入放到前面或后面。

注意！

如果最后字符串是反的，我们还要把它反过来。


------------

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int a,b,n,l,s1,s2,k=0;
char c;
int main(){
	cin>>s>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(a==1){//记录反了几次
			k++;
		}
		else{
			cin>>b>>c;
			if(b==1){//查看string是否是反的
				if(k%2==0){
					s=c+s;
				}
				else{
					s+=c;
				}
			}
			else{
				if(k%2==1){
					s=c+s;
				}
				else{
					s+=c;
				}
			}
		}
	}
	if(k%2==1){//如果最后是反的，反着输出
		for(int i=s.size()-1;i>=0;i--){
			cout<<s[i];
		}
	}
	else{
		for(int i=0;i<s.size();i++){
			cout<<s[i];
		}
	}
}
```

---

## 作者：45dino (赞：0)

一道模拟题

如果按照题目说的做，会TLE；

优化：记录反转次数，最后反转一次；

代码：
```
#include <bits/stdc++.h>
using namespace std;
deque<char> deq;
int main() 
{
    string s;
    cin >> s;
    for(int i=0;i<s.size();i++)
        deq.push_back(s[i]);
    bool on = false;
    int Q;
    cin >> Q;
    while(Q--) 
	{
        int T;
        cin >> T;
        if(T == 1) 
			on ^= true;
        else 
		{
            int F;
            cin >> F;
            char c;
            cin >> c;
            if(on^(F == 1)) 
				deq.push_front(c);
            else 
				deq.push_back(c);
        }
    }
    string ans;
    while(!deq.empty()) 
    {
    	ans.push_back(deq.front());
    	deq.pop_front();
	}
    if(on) 
		reverse(ans.begin(), ans.end());
    cout<<ans;
    return 0;
}
```


---

## 作者：happybob (赞：0)

本题可以使用双端队列，暴力模拟肯定会TLE

有道题目和这个很像：[https://www.luogu.com.cn/problem/P6823](https://www.luogu.com.cn/problem/P6823)

对于维护队列，考的多的是关于翻转，翻转次数过多导致TLE

其实这道题是这样的，做标记现在是否翻转，如果要翻转，标记反过来

标记有什么用？因为如果已经翻转了，插入到前面就要变成后面，这就是标记的用处

代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <deque>
using namespace std;

string s, ans = "";

deque<char> qe;

int main()
{
    bool f = true;
    int n;
    cin >> s >> n;
    int len = s.length() - 1;
    for(int i = len; i >= 0; i--)
    {
        qe.push_front(s[i]);
    }
    for(int i = 1; i <= n; i++)
    {
        int T;
        cin >> T;
        if(T == 1)
        {
            f = !f;
        }
        else if(T == 2)
        {
            char c;
            int F;
            cin >> F >> c;
            if(F == 1)
            {
                if(f)
                {
                    qe.push_front(c);
                }
                else
                {
                    qe.push_back(c);
                }
            }
            else if(F == 2)
            {
                if(f)
                {
                    qe.push_back(c);
                }
                else
                {
                    qe.push_front(c);
                }
            }
        }
    }
    while(!qe.empty())
    {
        ans.push_back(qe.front());
        qe.pop_front();
    }
    if(!f)
    {
        reverse(ans.begin(), ans.end());
    }
    cout << ans << endl;
    return 0;
}
```


---

