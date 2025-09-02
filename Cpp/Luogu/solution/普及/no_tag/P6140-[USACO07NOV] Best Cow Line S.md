# [USACO07NOV] Best Cow Line S

## 题目背景

*本题和 [2007 年 12 月月赛金组同名题目](/problem/P2870) 在题意上一致，唯一的差别是数据范围。*

## 题目描述

Farmer John 打算带领 $N$（$1 \leq N \leq 2\,000$）头奶牛参加一年一度的”全美农场主大奖赛“。在这场比赛中，每个参赛者必须让他的奶牛排成一列，然后带领这些奶牛从裁判面前依此走过。

今年，竞赛委员会在接受报名时，采用了一种新的登记规则：取每头奶牛名字的首字母，按照它们在队伍中的次序排成一列。将所有队伍的名字按字典序升序排序，从而得到出场顺序。

FJ 由于事务繁忙，他希望能够尽早出场。因此他决定重排队列。

他的调整方式是这样的：每次，他从原队列的首端或尾端牵出一头奶牛，将她安排到新队列尾部。重复这一操作直到所有奶牛都插入新队列为止。

现在请你帮 FJ 算出按照上面这种方法能排出的字典序最小的队列。

## 样例 #1

### 输入

```
6
A
C
D
B
C
B```

### 输出

```
ABCBCD```

# 题解

## 作者：做梦想Peach (赞：12)

好久没发过题解了，正好这题是晚上模拟赛的一题，就来写一写咯。

----------
这一题看上去显然是贪心，我们设两个指针，$a$ 表示头指针，也就是队列首端， $b$ 表示为指针，也就是队列末端。

下面是最好容易想到的策略：

1. 当 $\text{s[a]>s[b]}$  ，我们肯定是会选 $\text {s[b]}$ ，随之 $
b- -$ 。
1. 当 $\text{s[a]<s[b]}$  ，我们肯定是会选 $\text {s[a]}$ ，随之 $
a++$ 。

但是，通过样例我们发现，会出现 $\text {s[a]==s[b]}$ 情况，这种情况该怎么处理呢？

其实也很简单，我们找距离 $\text {s[a]}$ 和 $\text {s[b]}$ **最近**的且**不等于** $\text {s[a或b]}$ 的字符，再比较它们大小即可。

$\text {Code}:$
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
char s[3010];
int n,i,a,b,j,p,q;
int main () {
	scanf ("%d",&n);
	for (i=1;i<=n;i++)
		cin>>s[i];
	a=1;
	b=n;
	for (i=1;i<=n;i++) {//从i开始枚举。
		for (j=i;j<=i+79&&j<=n;j++) {//每80个字符就换行。
			if (s[a]==s[b]) {
				p=a;
				q=b;
				while (s[p]==s[q]) {
					p++;
					q--;
				}//策略3。
				if (s[p]<=s[q]) {
					printf ("%c",s[a]);
					a++;
				} //这里又可以想到上面最简单的两种策略。
				else {
					printf ("%c",s[b]);
					b--;
				}
			}
			else {
				if (s[a]>s[b]) {
					printf ("%c",s[b]);
					b--;//策略1。
				} 
				else {
					printf ("%c",s[a]);
					a++;//策略2。
				}
			}
		}
		i+=79;//继续搜索下面的80个字符。
		puts ("");
	}
	return 0;
}
```

---

## 作者：wylt (赞：5)

### 题意简述

给你 $N$ 个按顺序排列的字符，你每次可以从输入序列的头和尾取一个数放到最终数列的末尾，求字典序最小的解。

其中 $N\le2000$ 。

### 题目分析

我们很容易想出一个贪心思路，就是头和尾取最小的。

因为这道题目不存在可以让序列的字典序暂时比较大，通过后面取最优解超过原来比他字典序小的序列的情况。

即只要这一步字典序大了，后面整个串的字典序就永远不会在能翻盘。

但问题来了，如何处理头尾箱等的情况呢？

同样，我们可以走一步，看一步，不断往里找，直到找到两个不相同的，比较这两个数，取小的那一边的头或尾就行了。

### 代码

```cpp
#include<iostream>
#include<stdio.h>
#include<cstring>
#include<string>
using namespace std;
char a[2005];
int n;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	string s;
	int l=1,r=n,t=0;
	while(l<=r){
		if(a[l]<a[r]){
			cout<<a[l];
			l++;
		} else {
			if(a[l]>a[r]){
				cout<<a[r];
				r--;
			} else {
				int ll=l,rr=r;
				while(ll<=rr&&a[ll]==a[rr]){
					ll++;
					rr--;
				}
				if(a[ll]<=a[rr]){
					cout<<a[l];
					l++;
				} else {
					cout<<a[r];
					r--;
				}
			}
		}
		t++;
		if(t%80==0){
			cout<<endl;
		}
	}
	return 0;
}

```


---

## 作者：Flanksy (赞：3)

### 广度优先搜索

------------

最小化字典序就要每次选择能够选择的最小字符，考虑逐位确定答案。

使用 $S$ 表示输入的字符串，$S_1 < S_n$ 时应当删除 $S_1$，$S_1 > S_n$ 时应当删除 $S_n$。**而当 $S_1=S_n$ 时，无论选择删除 $S_1$ 还是 $S_n$，答案的第一个字符都已经确定，可以同时维护两种操作扩展后的结果。**

广度优先搜索，使用数对 $(l,r)$ 表示字符串还剩下子串 $\overline{S_lS_{l+1}\cdots S_r}$。进行操作可以取走 $S_l$ 或 $S_r$，遍历所有**取出答案第 $i$ 位的操作**，答案的第 $i$ 位就为这些操作中取出的字典序最小的字符。记答案为字符串 $ans$，答案的第 $i$ 位为 $ans_i$。再次遍历所有取出答案第 $i$ 位的操作，**当且仅当该操作取出的字符是 $ans_i$ 时扩展这个操作**。举个例子，当 $S_l = ans_i$ 时，取走 $S_l$ 能够最小化字典序，所以从 $(l,r)$ 扩展到 $(l+1,r)$ 是合法的；若 $S_r \neq ans_i$ 就不能从 $(l,r)$ 扩展到 $(l,r-1)$。

**非最优的操作序列会在某轮扩展时终止，终止之前该操作序列确定的答案和最优操作序列确定的答案完全相同**，第 $n$ 轮扩展后即可得到答案。由于满足 $l \leq r$ 的数对 $(l,r)$ 数量与 $O(n^2)$ 同阶，时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Chose{int l,r;Chose(int _l,int _r):l(_l),r(_r){}};
bool on[2005][2005];//on[l][r]记录操作是否被扩展 防止重复入队
queue<Chose> q;
char s[2005];
int n,cnt;
char extend(int x){//扩展所有r-l+1=x的操作
	char ret='Z';//确定一位答案
	vector<Chose> v;
	while(!q.empty()&&q.front().r-q.front().l+1==x) v.push_back(q.front()),q.pop();
	for(auto [l,r]:v) ret=min({ret,s[l],s[r]});//找到最小字符
	for(auto [l,r]:v){
		if(s[l]==ret&&!on[l+1][r]) q.push(Chose(l+1,r)),on[l+1][r]=1;
		if(s[r]==ret&&!on[l][r-1]) q.push(Chose(l,r-1)),on[l][r-1]=1;
	}
	return ret;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) while(!isalpha(s[i])) s[i]=getchar();
	q.push(Chose(1,n));
	for(int i=1;i<=n;i++){
		putchar(extend(n-i+1));
		if((++cnt)%80==0) putchar('\n');
	}
	return 0;
}
```


---

## 作者：Durancer (赞：2)

#### 前言

后缀数组的应用，也是第一道自己做出来的 $SA$ 题。

#### 思路

这题数据很水，贪心暴力可以过，但我想说一说数据加强版的正解。

首先一个很明确的贪心思路，分别从两端来找，不同的字母优先选取字典序更小的那一个。

那么再思考一下相同的情况，那么肯定是比较以左边端点为起点的后缀，和以右边端点为终点的前缀，看看哪一个更小。

这里就是可以上后缀数组应用时两个字符串连接的套路了，既然要找前缀，那么就是找原数组翻过来之后的后缀了，那么就可以考虑把翻转过来的数组连在后面。

那么连接是要有一个注意的细节，连接的中间必须添上一个不属于输入数据范围内的字符作为一个分割点，防止会有一些奇奇怪怪的事情发生。

那么最后比较的时候遇见相同的只需要比较 。

$$\text{rk[l]} \ \ ?\ \ \text{rk[2(n+1)-r]}$$

就能得出答案，排名越小，字典序越小，可能做的贡献就会越大

#### 代码实现

```cpp
/*
	同2870 数据范围变小 
*/
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#include<stack>
#include<map>
using namespace std;
const int N=2000;
int rk[N<<2],rkid[N<<2],oncerk[N<<2];
int cnt[N<<2],sa[N<<2],id[N<<2];
int n,m;
char s[N<<2];
char ans[N<<1];
int top; 
bool cmp(int x,int y,int len)
{
	return (oncerk[x]==oncerk[y])&&(oncerk[x+len]==oncerk[y+len]);
}
void SA()
{
	for(int i=1;i<=n;i++) cnt[rk[i]=s[i]]++;
	for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
	for(int i=n;i>=1;i--) sa[cnt[rk[i]]--]=i;
	
	for(int len=1,p;len<n;len<<=1)
	{
		p=0;
		for(int i=n;i>n-len;i--) id[++p]=i;
		for(int i=1;i<=n;i++)
			if(sa[i]>len)
				id[++p]=sa[i]-len;
		
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;i++) cnt[rkid[i]=rk[id[i]]]++;
		for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--) sa[cnt[rkid[i]]--]=id[i]; 
	
		memcpy(oncerk,rk,sizeof(rk));
		m=0;
		for(int i=1;i<=n;i++)
			rk[sa[i]]=(m+=(cmp(sa[i],sa[i-1],len)^1));
		
	}
}
int main()
{
	//ios::sync_with_stdio(false);//cin加速 
	scanf("%d",&n);
	for(int i=1;i<=n;i++) cin>>s[i];
	s[n+1]='1';
	for(int i=1;i<=n;i++) s[2*n+2-i]=s[i];//构造正向数组+1+反向数组的形式，用于判断 
	int cun=n;//存一下，后面处理完后缀数组会用到 
	n=2*n+1;
	m=max(n,300);
	SA();
	n=cun;
	int l=1,r=n;//左右以此进行 
	while(l<=r)
	{
		if(l==r)
		{
			ans[++top]=s[l];
			break; 
		}
		if(s[l]>s[r])
		{
			ans[++top]=s[r];
			r--;
			continue;
		}
		else if(s[l]<s[r])
		{
			ans[++top]=s[l];
			l++;
			continue;
		}
		else if(s[l]==s[r])
		{
			if(rk[l]<rk[2*(n+1)-r])//l更优 
			{
				ans[++top]=s[l];
				l++;
				continue;
			}
			else 
			{
				ans[++top]=s[r];
				r--;
				continue;
			}
		}
	}
	for(int i=1;i<=top;i++)
	{
		if(i%80==1&&i!=1) cout<<endl;
		printf("%c",ans[i]);
	}
		
	return 0;
}
```


---

## 作者：cccyyylll888 (赞：1)

其实这道题就是一个贪心。

因为要字典序最小，因此，每次插入最后的字符一定是输入字符的现有字符头与尾中较小的一个。

具体过程在代码中标注：

````
#include<iostream>
using namespace std;
int n;
char s[2005];//初始队列 
char q[2005];//用数组模拟队列，及输出的排序 
int main()
{
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		cin >> s[i];
	}
	int l = 1,r = n;//指针，代表当前S数组还剩下数的头和尾 
	int cnt = 1;
	while(l <= r)//如果为空，就停止 
	{
		bool flag = false;
		for(int i = 0;l+i <= r;i++)
		{
			if(s[l+i] < s[r-i])//头小于尾 
			{
				flag = true;
				break;
			}
			else
			if(s[l+i] > s[r-i])//头大于尾 
			{
				flag = false;
				break;
			}
			//如果相同就会比较下一位 
		}
		if(flag)//头进队 
		{
			q[cnt] = s[l];
			cnt++;
			l++;
		} 
		else//尾进队 
		{
			q[cnt] = s[r];
			cnt++;
			r--;
		}
	}
	for(int i = 1;i <= cnt - 1;i++)//输出 
	{
		char p = q[i];
		cout << p;
		if(i % 80 == 0)//warning！！！！！！ 
		cout << endl;
	}
	return 0;
}
````

---

## 作者：Monkey_Hunter (赞：1)

### 题目大意
+ 你有两个序列 $a$（初始为空）和 $b$（有 $N$ 个元素），每次操作可以从 $b$ 的首或尾删去一个元素，并将此元素加入 $a$ 的末尾。  
+ 求 $N$ 次操作后字典序最小的 $a$。  
+ 输出时每 $80$ 个字符换一行。
### 题目解法
可以发现，选择 $a_i$ 时，一定选择 $b$ 的首尾中最小的字符。因为如果选择的字符比最小的字符大，就一定可以选择更小的字符，使得字典序更小。

那么，如果 $b$ 的首尾相等，怎么选呢？由于我们在选择这一次后，剩下的字符字典序要尽量小，所以我们要找到哪一边离首尾最近的字符字典序更小，选择那一边。

e.g. 字符串 $\texttt{IAKIOI}$ 中，首尾（$\texttt I$）相等，所以看哪一边离首尾最近的字符字典序更小。  
由于 $\texttt A < \texttt O$，所以应该选择前面的 $\texttt I$。最终结果便是 $\texttt{IAIKIO}$。
### AC 代码（附注释）
```cpp
#include <bits/stdc++.h>
using namespace std;
int head, tail, n, cnt;
char names[2080], ans[2080];
// head 表示首指针，tail 表示尾指针。
// names 表示输入序列，ans 表示答案序列。
int main() {
	cin >> n;
	tail = n - 1;
	for(int i = 0; i < n; i++)
		cin >> names[i];
	while(head <= tail) {
		if(names[head] < names[tail]) {
			cnt++;
			ans[cnt] = names[head];
			head++;
			continue;
		} // 第一种情况，首<尾，取首。
		if(names[tail] < names[head]) {
			cnt++;
			ans[cnt] = names[tail];
			tail--;
			continue;
		} // 第二种情况，首>尾，取尾。
		if(names[head] == names[tail]) {
			if(head == tail) ans[++cnt] = names[head++]; // 特判：首指针=尾指针，任意取一个，结束。
			int h1 = head, t1 = tail;
            // 枚举中间，临时首尾指针。
			while(h1 <= t1) {
				if(names[h1] < names[t1] || (names[h1] == names[t1] && t1 - h1 <= 1)) {
					cnt++;
					ans[cnt] = names[head];
					head++;
					break;
				} // 中间的首<尾，取首。
				if(names[t1] < names[h1]) {
					cnt++;
					ans[cnt] = names[tail];
					tail--;
					break;
				} // 中间的尾<首，取尾。
				h1++, t1--;
                // 更新首尾指针。
			}
		} // 第三种情况，首=尾，往中间枚举，比较大小后决定取首或取尾。
	}
	for(int i = 1; i <= n; i++) {
		cout << ans[i];
		if(i % 80 == 0) cout << endl;
        // 80 个字符换行。
	}
	return 0;
}
```
### 注意事项
+ 不要用 STL 队列，STL 队列只能查询首尾，不方便比较中间部分（需要一系列弹出和重新插入相同数据）。
+ 一定要特判各种指针情况，不要漏掉形如 $\texttt{AAAAAA}$ 的情况。
+ 不要忘记每 $80$ 个字符换一次行。

---

## 作者：asasas (赞：1)

题意：给你$n$个按顺序排列的字符，你每次可以从输入序列(设为$s$)的头和尾取一个字母放到最终序列列的末尾，求字典序最小的解。

这是一道很好的**贪心**题目，代码短但需要经过很长的思考。


我们设$l$代表当前指向$s$的首端(队列的头指针)，$r$指向s的末端(队列的尾指针)。

每次判断取头指针指向的字符还是尾指针指向的字符。这时有三种情况：

①:$s_l>s_r$，这时取尾指针较优。

②:$s_l<s_r$，这时取头指针较优。

③:$s_l==s_r$ 这种情况较复杂。可以理解为比较两个数字的大小。从当前位置一个一个的比，直到比较出大小的位置，此时同①②的比较方式。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
char a[3005];
int main(){
	int n;
	cin >> n;
	for (register int i=1;i<=n;i++){
		cin >> a[i];//读入
	}
	int l=1,r=n,ans=0;
	while(l<=r){
		if (a[l]<a[r]){
			cout << a[l];//第一种情况
			l++;
		}
		else{
			if (a[r]<a[l]){
				cout << a[r];//第二种情况
				r--;	
			} 
			else {//第三种
				int tl=l+1,tr=r-1;//记录
				while(tr-tl>1&&a[tl]==a[tr]) tl++,tr--;//从头到尾比较，指导比较出大小或两个指针指向同一位置
				if (a[tl]<a[tr]) cout << a[l],l++;
				else cout << a[r],r--;
			}
		}
		ans++;
		if (ans%80==0) cout << endl;//每80个一换行
	}
}
```


---

## 作者：Exber (赞：1)

## 题意
- #### 给你一个字符串，要你用这个构造一个新的字符串。
- #### 每次可以把原字符串第一个字符或者最后一个字符删掉，并加入新的字符串末尾。
- #### 求所有可以构成的新的字符串中字典序最小的那个字符串，输出时 80 个字符一行。

## 做法
很容易想到贪心。

由于我们要构造一个字典序尽量小的字符串，所以每次把原字符串两端小的那个字符删掉并加入新的字符串末尾就行了，这个操作可以用双端队列非常方便地维护。

碰到两端的字符相等的情况怎么办呢？也许你会想：“随便选一个就行啦”。可是，事情并没有这么简单。例如这样一个字符串：

```DEAD```

如果把第一个字符删掉加入新的字符串末尾，最终会得到 ```DDAE```；可是如果把最后一个字符删掉加入新的字符串末尾，则会得到 ```DADE```，很明显结果是不一样的。

所以，当两端的字符相等时，需要一路往中间比较，遇到不同的字符则选小的那一端的字符来删掉并加入新的字符串末尾。如果一路比较下来都是相等的，那选哪个都没问题了。

例如 ```DEAD``` 这个字符串，先比较 ```D``` 和 ```D```，发现他们相等。那么就继续比较下两个字符，发现 ```E``` 比  ```A``` 大，那么就结束比较，删掉原字符串中处于后端的 ```D```，并把它加入新字符串的末尾。可以发现，这样才是最优的。

这个一路比较的算法依旧可以用双端队列维护，为了省事，我们可以直接使用 ```STL``` 的 ```deque```。

## AC 代码
```cpp
#include <iostream>
#include <deque>

using namespace std;

int n;
deque<char> a,s; // 用双端队列存原字符串和新字符串 

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		char ch;
		cin>>ch;
		a.push_back(ch); //构建好存原字符串的双端队列 
	}
	for(int i=1;i<=n;i++)
	{
		if(a.front()!=a.back()) // 首尾字符不相等 
		{
			if(a.front()<a.back()) 
			{
				s.push_back(a.front()); // 删除首字符 
				a.pop_front();
			}
			else
			{
				s.push_back(a.back()); // 删除尾字符 
				a.pop_back();
			}
		}
		else // 首位字符相等 
		{
			deque<char> temp=a; 
			while(!a.empty()&&a.front()==a.back()) // 一路比较 
			{
				a.pop_front();
				a.pop_back();
			}
			if(a.empty()) // 选哪个删除结果完全一样 
			{
				a=temp;
				s.push_back(a.front()); // 删哪一个都行 
				a.pop_front();
			}
			else
			{
				if(a.front()<a.back()) // 删前面的结果会更好 
				{
					a=temp;
					s.push_back(a.front()); // 删前面的 
					a.pop_front();
				}
				else // 删后面的结果会更好 
				{
					a=temp;
					s.push_back(a.back()); // 删后面的 
					a.pop_back();
				}
			}
		}
	}
	int cnt=0; // 本行已经输出了多少个字符 
	while(!s.empty())
	{
		cout<<s.front();
		s.pop_front();
		cnt++;
		if(cnt==80) // 八十个字符一行 
		{
			cout<<endl;
			cnt=0;
		}
	}
	return 0;
}
```


---

## 作者：Cylete (赞：0)

- 暴力做法就是每次最坏地判断当前应该取首还是尾（即比较取首得到的字符串与取尾得到的反串的大小），只需优化这一判断过程即可。

- 由于需要在原串后缀与反串后缀构成的集合内比较大小，可以将反串拼接在原串后，并在中间加上一个没出现过的字符（如 # ，代码中可以直接使用空字符），求后缀数组，即可完成这一判断。

————oiki

所以就无脑后缀数组上

还能过加强版美滋滋

```cpp
int T, n, m;

char s[N];
int c[N], x[N], y[N], sa[N];

inline void SA() {
	cin >> n;
	R int l = 1, r = n;
	for(R int i = 1; i <= n; i++) cin >> s[i];
	for(R int i = 1; i <= n; i++) s[n + n + 2 - i] = s[i];
	n = n + n + 1; m = 200;
	for(R int i = 1; i <= n; i++) ++c[x[i] = s[i]];
	for(R int i = 1; i <= m; i++) c[i] += c[i - 1];
	for(R int i = n; i >= 1; i--) sa[c[x[i]]--] = i;
	for(R int k = 1, num = 0; k < n; k <<= 1, num = 0) {
		for(R int i = n - k + 1; i <= n; i++) y[++num] = i;
		for(R int i = 1; i <= n; i++) if(sa[i] > k) y[++num] = sa[i] - k;
		for(R int i = 1; i <= m; i++) c[i] = 0;
		for(R int i = 1; i <= n; i++) c[x[i]]++;
		for(R int i = 1; i <= m; i++) c[i] += c[i - 1];
		for(R int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
		swap(x, y);
		x[sa[1]] = num = 1;
		for(R int i = 2; i <= n; i++)
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
		if(num == n) break;
		m = num;
	}
	while(l <= r) {
		putchar(x[l] < x[n - r + 1] ? s[l++] : s[r--]);
		if((++T) % 80 == 0) puts("");
	}
}
```

---

## 作者：windrizzle (赞：0)

### 题意

多组测试数据。

给你一个长度为$N$的字符串$S$,输入格式是依次输入$N$个字符。

$N <= 2000$。

每次你可以从$S$的开头或者结尾取出一个字符,放到一个$T$字符串的尾部。

输出字典序最小的$T$字符串,**每$80$个字符换一行输出。**


### 题解

不难，直接循环即可。但是输出略微毒瘤。

我们可以把情况分为两种：

两边字符不一样——直接把字典序小的拿出。

两边字符一样——继续寻找，找到不一样的，然后把字典序小的一边先拿出。

### 代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int n;
int suml,sumr,sum;
char a[30001],ans[30001];
int main()
{
	cin>>n;
	for(int i=0;i<n;i++) cin>>a[i];
	while(strlen(a)!=strlen(ans))
	{
		int l,r;
		r=strlen(a)-1-sumr;
		l=suml;
		while(l<r&&a[l]==a[r]) l++,r--;
		if(a[l]>a[r]) //第一种情况
        sumr++,ans[strlen(ans)]=a[strlen(a)-sumr];
		else suml++,ans[strlen(ans)]=a[suml-1];//否则，判断
	}
	for(int i=0;i<strlen(ans);i++)
	{
		cout<<ans[i];
		sum++;
		if(sum==80) sum=0,cout<<endl;//输出判断
	}
}
```


---

