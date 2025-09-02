# Maximum Xor Secondary

## 题目描述

Bike loves looking for the second maximum element in the sequence. The second maximum element in the sequence of distinct numbers $ x_{1},x_{2},...,x_{k} $ $ (k&gt;1) $ is such maximum element $ x_{j} $ , that the following inequality holds: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF280B/cbffb592db1e3f6cc63c23bba8878833c080a3b3.png).

The lucky number of the sequence of distinct positive integers $ x_{1},x_{2},...,x_{k} $ $ (k&gt;1) $ is the number that is equal to the bitwise excluding OR of the maximum element of the sequence and the second maximum element of the sequence.

You've got a sequence of distinct positive integers $ s_{1},s_{2},...,s_{n} $ $ (n&gt;1) $ . Let's denote sequence $ s_{l},s_{l+1},...,s_{r} $ as $ s[l..r] $ $ (1<=l&lt;r<=n) $ . Your task is to find the maximum number among all lucky numbers of sequences $ s[l..r] $ .

Note that as all numbers in sequence $ s $ are distinct, all the given definitions make sence.

## 说明/提示

For the first sample you can choose $ s[4..5]={4,3} $ and its lucky number is $ (4 xor 3)=7 $ . You can also choose $ s[1..2] $ .

For the second sample you must choose $ s[2..5]={8,3,5,7} $ .

## 样例 #1

### 输入

```
5
5 2 1 4 3
```

### 输出

```
7
```

## 样例 #2

### 输入

```
5
9 8 3 5 7
```

### 输出

```
15
```

# 题解

## 作者：ykzzldz (赞：10)

今天上课讲到这题，就写个题解吧。

考虑枚举次大值，这时，我们可以容易的使用单调栈求出次大值左右两边更大的数，这时，这两个数可以成为最大值。复杂度是 $O(n)$ 的，代码比较简单，就不给了。

---

## 作者：Egg_eating_master (赞：8)

其他题解貌似不是很清楚，蒟蒻来写一篇吧

这题要求的东西似乎很诡异

我们不妨换个思路，对于每个数，固定其为选出的序列中的次大值，在它左边去找最大值，也就是它左边离它最近的比它大的数

这样的话，我们就要对于每个$a_i$，找到一个最大的$j$，使得$j<i$且$a_j>a_i$

看到这个式子就想到单调栈了

不懂单调栈的话，左转[P5788](https://www.luogu.com.cn/problem/P5788)

当然我们的最大值也可以在次大值的右边，于是正着跑一遍单调栈，再反着跑一遍，在所有的答案中取一个$\max$，就是最终结果

时间复杂度为$O(n)$
```
#include<bits/stdc++.h>
using namespace std;
int n;
int a[100005];
stack<int>s;
int ans=-1e9;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	    cin>>a[i];
	for(int i=1;i<=n;i++){
		while(!s.empty()&&s.top()<a[i])s.pop();//维护单调栈，找到距离a[i]最近的大于a[i]的数
		if(!s.empty())ans=max(ans,s.top()^a[i]);//答案打擂台取最大值
		s.push(a[i]);
	}
	while(!s.empty())s.pop();
	for(int i=n;i>=1;i--){//同上
		while(!s.empty()&&s.top()<a[i])s.pop();
		if(!s.empty())ans=max(ans,s.top()^a[i]);
		s.push(a[i]);
	}
	cout<<ans<<endl;
	return 0;
} 
```

---

## 作者：WiseStar (赞：5)

嗨嗨嗨，本蒟蒻第一次写题解（好久没上洛谷，前段时间进来发现~~蓝名了~~）。

好了，废话不多说。

## 思路
新建一个递增/递减序列，每次有元素入队时就与队中的元素异或一下，用一个变量来存储答案（最大值）。

可问题就在这儿，**到底使用递增序列还是递减序列呢**。

嗯……是个很好的问题。

于是……本蒟蒻拿样例分析了一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/od7b7e2p.png)

然后会发现一个严重的问题：

虽然答案是对的，**但有一些区间内的“最大”和“次大”没有进行异或运算。**

举个栗子：

$2\sim4$ 区间内，最大的 4 和次大的 2 就没有进行异或运算。

递增不行，那……试试递减？

![](https://cdn.luogu.com.cn/upload/image_hosting/prlsievv.png)

可以看到，用递减做就非常完美，每个区间的“最大”和“次大”都进行了异或运算。

## 代码落实
定义一个队列，也可以是栈（stack），本人觉得后者比较好用，所以我用的栈。

```c
while(!s.empty()&&s.top()<a[i]){//a[i]就是输入的值
	ans=max(ans,s.top()^a[i]),s.pop();//如果非空且遍历道德这个数比对前面的数大（严格递减，不能取等），就把前面的数删掉（出队）。
}
```

后面加上：

```c
if(!s.empty())
	ans=max(ans,a[i]^s.top()),s.push(a[i]);
```
这样就能保证**每一个被遍历到数对都能取一次异或，不会在某个区间内被遗漏。**

## 完整 AC 代码~~我知道你们只看这儿~~

```c
#include<iostream>
#include<stack>
using namespace std;
int n,a[100001],ans;
stack<int> s;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	s.push(a[1]);
	for(int i=2;i<=n;i++){
		while(!s.empty()&&s.top()<a[i]){
			ans=max(ans,s.top()^a[i]);
			s.pop();
		}
		if(!s.empty())
			ans=max(ans,a[i]^s.top());
		s.push(a[i]);
	}
	printf("%d",ans);
	return 0;
}
```
### THE END

~~点个赞吧~~

---

## 作者：king_xbz (赞：2)

# 前言：
好像题解区还没有手写栈的题解，~~一味的依赖STL会误了大事的~~，所以我来发一篇QAQ。这是一道相当不错的单调栈练习题，建议大家独立完成。
# 题意分析
先吐槽一下翻译有误，这题要求的并不是所有子序列，而是最大值和次大值的异或值。希望管理大大看到能修改。
# 前置知识
**按位异或运算**：即^或xor运算，对于每个二进制位，不同则为1，相同则为0.

$1\ xor\ 1=0,0\ xor\ 0=0,1\ xor\ 0=1,0\ xor\ 1=1$

**单调栈**是一种满足在栈内单调递增或单调递减的数据结构。我有一篇博客专门对此详述，[单调栈教学](https://www.luogu.com.cn/blog/kingxbz/solution-p5788)，这里不再赘述
# 做法分析
对于这道题，我们维护一个单调递减的栈，即栈顶元素是最大值，然后将栈顶元素与当前元素异或更新最值，然后将当前元素入栈，注意如果单调性被破坏，就要清空元素保证严格单调。最后输出答案即可。
# 代码详解
代码很简单
```cpp
int main()
{
	int n;
	cin>>n;
	for(fint i=1;i<=n;i++)
	cin>>a[i];
	int ans=0;
	for(fint i=1;i<=n;i++)
	{
		while(tops)
		{
			ans=max(ans,st[tops]^a[i]);
			if(a[i]<=st[tops])
			break;//加入新元素后仍，满足单调性，就不用弹出元素
			tops--;//保证单调性
		}
		st[++tops]=a[i];//进栈
	}
	cout<<ans;
	return 0;
}
```
最后，强力建议大家平常多使用手写栈，如果遇到毒瘤题目（如[P5788](https://www.luogu.com.cn/problem/P5788)）STL栈不吸氧是过不了的！

---

## 作者：Dream__Sky (赞：1)

算法考虑单调栈。

对于每一个区间，只有最大值和次大值是有贡献的，其它的数没有任何用。那我们只要知道所有的最大值和对应的次大值，就能求出答案。

考虑如何求这个东西。如果先固定枚举最大值，那么次大值很难求，需要考虑整个当前枚举的区间内，各个数与各个数之间的关系，时间复杂度为 $O(n^2)$，显然不可行。那我们考虑枚举次大值。对于最大值，我们只要找出向两边拓展时，第一次比这个数大的数就行了，可以用单调栈维护。

注意要向左右两边各做一次单调栈，因为最大值与次大值的左右关系是不定的。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[100010],ans;
stack<int> s;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		while(!s.empty()&&s.top()<a[i]) s.pop();
		if(!s.empty()) ans=max(ans,a[i]^s.top());
		s.push(a[i]);
	}
	for(int i=n;i>=1;i--)
	{
		while(!s.empty()&&s.top()<a[i]) s.pop();
		if(!s.empty()) ans=max(ans,a[i]^s.top());
		s.push(a[i]);
	}
	cout<<ans;
	return 0;
}


```


---

## 作者：liuyifan (赞：1)

## 单调栈
好久没写题解了，今天再写一波吧

从左到右弄一个单调递减栈，从右往左弄一个单调递减栈

然后求出左右第一个违反单调性的点

这样每个点就确定了两个区间，然后遍历找到最大异或点就可以了

**注意左右端点的特判**

code:
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register
#define ll long long
#define inf 0x3f3f3f3f
#define iinf 0x3f3f3f3f3f3f3f3fll//注意后缀ll,不加可能会死得惨烈
using namespace std;
ll n,a[1000005],l[1000005],r[1000005],maxx=-iinf;
stack<ll>s1,s2;//使用STL栈维护
int main()
{
	scanf("%lld",&n);
	for(reg int i=1;i<=n;i++)scanf("%lld",&a[i]);
 	for(reg int i=n;i>=1;i--)
	{
		while(s1.empty()==0&&a[s1.top()]<a[i])s1.pop();//弹出违背单调性的点
		l[i]=s1.empty()?n+1ll:s1.top();//如果栈空了的特殊处理
		s1.push(i);//加入栈
	}//维护单调递减栈
	for(reg int i=1;i<=n;i++)//注意循环顺序的区别
	{
		while(s2.empty()==0&&a[s2.top()]<a[i])s2.pop();
		r[i]=s2.empty()?0ll:s2.top();
		s2.push(i);//操作流程大体同上
	}//维护单调递增栈
	for(reg int i=1;i<=n;i++)
	{
		if(l[i]!=n+1)maxx=max(maxx,a[i]^a[l[i]]);
		if(r[i])maxx=max(maxx,a[i]^a[r[i]]);
	}//求最大异或值
	//C++ ^运算符为按位异或,直接用就行了
	printf("%lld",maxx);//输出答案
	return 0;
}
```


---

## 作者：A_Bit_Cold (赞：0)

给定一个序列，求其子串中最大值与次大值的异或值最大为多少。保证 $s_i$ 互不相等，无歧义。

枚举次大值，然后向前向后两遍求第一个大于次大值的数的位置，即最大值。

很容易想到这是个单调栈的板子。

异或其实是诈骗的，并不需要 trie 树。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
stack <int> s;
int a[N],ans[N],maxn;
int main() {
	int n; cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=n;i>=1;i--) {
		while(!s.empty()&&a[i]>=a[s.top()]) s.pop();
	    if(s.empty()) ans[i]=-1;
	    else ans[i]=s.top();
		s.push(i);
	}
	for(int i=1;i<=n;i++) {
		if(ans[i]!=-1) maxn=max(maxn,a[ans[i]]^a[i]);
	}
	while(!s.empty()) s.pop();
	for(int i=1;i<=n;i++) {
		while(!s.empty()&&a[i]>=a[s.top()]) s.pop();
	    if(s.empty()) ans[i]=-1;
	    else ans[i]=s.top();
		s.push(i);
	}
	for(int i=1;i<=n;i++) {
		if(ans[i]!=-1) maxn=max(maxn,a[ans[i]]^a[i]);
	}
	cout<<maxn;
	return 0;
}
```

---

## 作者：wsx10 (赞：0)

首先，我们可以考虑确定最大值和次大值的其中一个，通过枚举的方式确定另一个值。

但是，如果确定最大值，枚举次大值，对于 `4 3 2 5` 这组数据，`4 3 2 5` `3 2 5` `2 5` 三种情况的次大值并不确定，所以我们应该确定次大值，枚举最大值。

那接下来就很简单了。从左到右，从右到左跑 $2$ 次单调栈，确定每一个值左侧和右侧的更大的收即可。

代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100004;
int st[maxn],top=0;
int l[maxn],n,ans;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>l[i];
	for(int i=1;i<=n;i++)
	{
		while(top>0&&l[st[top]]<l[i]) top--;//因为题里保证各数互不相同，所以 l[st[top]]<=l[i] 也可 
		st[++top]=i;
		if(top>1) ans=max(ans,l[st[top-1]]^l[i]);
	}
	top=0;//清空栈
	for(int i=n;i>=1;i--)
	{
		while(top>0&&l[st[top]]<l[i]) top--;
		st[++top]=i; 
		if(top>1) ans=max(ans,l[st[top-1]]^l[i]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：LZYAC (赞：0)

## 思路

通过题意发现，我们可以尝试通过固定最大值或者次大值再来确定另外一个值，很明显，确定最大值比次大值简单得多。

于是我们固定次大值（也就是将当前的值设定为区间的次大值）再正反跑两次**单调栈**确定每个次大值对应的最大值即可。

有不懂单调栈的左转[这里](https://www.luogu.com.cn/problem/P5788)。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
stack<long long> s;
long long a[100010],f1[100010],f2[100010],ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=n;i++){
        while(!s.empty()&&a[s.top()]<a[i]) s.pop();
        if(!s.empty()) ans=max(ans,a[i]^a[s.top()]);
        s.push(i);
    }   
    while(s.size()) s.pop();
    for(int i=n;i>=1;i--){
        while(!s.empty()&&a[s.top()]<a[i]) s.pop();
        if(!s.empty()) ans=max(ans,a[i]^a[s.top()]);
        s.push(i);
    }  
    printf("%lld",ans);
}
```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
就是给定一个长度为 $n$ 的数组，要求在这数组里面所有的子串中最大值和次大值异或的最大值。
## 大体思路
我们如果暴力的话，$O(n^2)$ 一定是会超时的，单调栈也很难处理，怎么办呢？

我们可以从左往右遍历一遍数组，每一个数默认是当前的次大值，只需要从左往右找第一个比他大的，这是个子串，处理一下 max 就行。

注意到有可能次大值在最大值右边，我们再扫一遍即可。

正确性也很好证明，因为再接着往右走，默认的次大值就不是次大值了，就算无影响，我们要求的是最大值，也不会产生影响。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
stack<int> s;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int ans=0;
	for(int i=1;i<=n;i++){//维护单调栈，正着扫 
		while(!s.empty()&&s.top()<a[i]){
			s.pop();
		}
		if(!s.empty()){
			ans=max(ans,s.top()^a[i]);
		}//处理最大值 
		s.push(a[i]);
	} 
	while(!s.empty()){
		s.pop();
	}//别忘了清空一下 
	for(int i=n;i>=1;i--){//维护单调栈，反着扫。 
		while(!s.empty()&&s.top()<a[i]){
			s.pop();
		}
		if(!s.empty()){
			ans=max(ans,s.top()^a[i]);
		}//处理最大值 
		s.push(a[i]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_QWQ__QWQ_ (赞：0)

由于正求次大值比较困难，不如逆向思考。

由次大值来找最大值，即对于每个 $ i $，找到一个 $ j $，满足 $ j<i $ 并且 $ a_i<a_j $。

这项工作当然要交给[单调栈](https://oi-wiki.org/ds/monotonous-stack/)来解决啦。

特别的，如果最大值在次大值的右边，你就会很[开心](https://www.luogu.com.cn/record/152194196)的得到一个大大的 WA。

所以还需要反跑一遍。

AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
stack<int>st,st1;//st正，st1反
int ans=-1e9;
int n,a[maxn];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		while(!st.empty()&&a[st.top()]<a[i]){
			st.pop();//正常单调栈
		}
		if(!st.empty())ans=max(ans,a[st.top()]^a[i]);//找到最大值，更新答案
		st.push(i);
	}
	for(int i=n;i>=1;i--){//反跑
		while(!st1.empty()&&a[st1.top()]<a[i]){
			st1.pop();//反着的单调栈
		}
		if(!st1.empty())ans=max(ans,a[st1.top()]^a[i]);//同上
		st1.push(i);
	}
	cout<<ans;//撒花！！！
	return 0;
}
```

---

## 作者：COsm0s (赞：0)

发现题解区没有这种半玄学做法，目前跑到了全谷最优解。

采用**链表**思想。

首先我们看到“最大值和次大值”这样的表述，就能联想到枚举次大值。

这是因为当确定次大值之后，我们所要做的就是在它左右两边去找最大值，也就是它两边离它最近的比它大的数。


------------

这一步有很多解法。我们可以使用二分和 `RMQ` 的方式，也可以采取单调栈来选取。

但是有一种很难被卡的链表做法，而且常数比单调栈更小。

我们令 $lst_i$ 为 $i$ 位置左边第一个大于 $a_i$ 的位置。

那么在解决 $lst_i$ 的取值时，我们可以借用 $lst_{j}(1\leq j<i)$ 的值。

当 $a_j<a_i$ 时，显然只有当 $a_k>a_j$ 才有可能使 $a_k>a_i$。那么 $a_j$ 之前第一个比它大的值正是 $a_{lst_j}$。

所以我们只要不断通过 $lst_i$ 往回“跳”即可。

对于 $i$ 之后的最大值，同样处理即可。

```
	int j = i - 1;
	while (a[j] <= a[i]) j = pre[j];
	pre[i] = j;
```

代码如上。

在不断的试验下，作者发现这种方法事实上复杂度是近似等于 $O(1)$ 的，当然作者不会证明。

并且在通常情况下，常数是比单调栈、单调队列等线性结构优秀的。

所以复杂度 $\Theta(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Jelly {
	const int N = 1e5 + 5, inf = 1e9;
	int n, a[N], pre[N], ans;
	int main() {
		cin >> n;
		a[0] = a[n + 1] = inf;
		for (int i = 1; i <= n; i ++) cin >> a[i];
		pre[1] = 0;
		for (int i = 2; i <= n; i ++) {
			int j = i - 1;
			while (a[j] <= a[i]) j = pre[j];
			pre[i] = j;
			if(pre[i]) ans = max(ans, a[pre[i]] ^ a[i]);
		}
		pre[n] = n + 1;
		for (int i = n - 1; i; i --) {
			int j = i + 1;
			while (a[j] <= a[i]) j = pre[j];
			pre[i] = j;
			if(pre[i] != n + 1) ans = max(ans, a[pre[i]] ^ a[i]);
		}
		cout << ans << '\n';
		return 0;
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T = 1;
//	cin >> T;
	while (T --) Jelly::main();
	return 0;
}
```

附上最优解证明（$2023.12.1$）。

![](https://cdn.luogu.com.cn/upload/image_hosting/kial20rm.png))

---

## 作者：first_fan (赞：0)

题面翻译：

>题目大意：
>给出一个长为n的正整数序列。定义一个序列的所有数异或的结果为该式子的价值。求在此序列的所有子串（即要求连续一段区间）中价值最大是多少。

那么就很简单了，我们可以使用一个`单调递减栈`来维护信息，每读一个数就更新一次栈，以维持其递减性，插入和弹出的时候都更新一下答案就行了。

```cpp
#include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;

int read()
{
	int num=0;
	int flg=1;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
		{
			flg=-1;
		}
		c=getchar();
	}
	while(isdigit(c))
	{
		num=(num<<1)+(num<<3)+(c^48);
		c=getchar();
	}
	return num*flg;
}

int ans=0;
stack<int>s;//STL栈

int main()
{
	int n=read();
	while (n--)//边读边做
	{
		int x=read();
		while (s.size())//维护一个单调递减栈
		{
			ans=max(ans,s.top()^x);
			if(s.top()>x)
			{
				break;
			}
			//如果新数比栈头小，则直接压栈
			//否则清空栈内比新数小的所有数
			s.pop();
		}
		s.push(x);//压栈
	}
	return 0&printf("%d",ans);
}
```

---

