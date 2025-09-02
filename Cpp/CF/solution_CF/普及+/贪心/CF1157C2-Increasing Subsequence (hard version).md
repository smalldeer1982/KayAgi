# Increasing Subsequence (hard version)

## 题目描述

给你一个长度为 n 的序列，每次取出当前序列中最左或最右的数字，每次取出的数都要严格大于上一次取出的数，求最多取出多少数字。

## 样例 #1

### 输入

```
5
1 2 4 3 2
```

### 输出

```
4
LRRR
```

## 样例 #2

### 输入

```
7
1 3 5 6 5 4 2
```

### 输出

```
6
LRLRRR
```

## 样例 #3

### 输入

```
3
2 2 2
```

### 输出

```
1
R
```

## 样例 #4

### 输入

```
4
1 2 4 3
```

### 输出

```
4
LLRR
```

# 题解

## 作者：L______ (赞：9)

这个题其实手动模拟一下就会发现，这道题真的就是一道贪心模拟题……

很显然，对于当前的一个数列，左指针指向最左侧，右指针指向最右侧，如果一边小一边大，那么一定可以贪心的选择较小的那个数，因为这样之后一定还可以选择较大的那个数。如果两边的数字相同的话，那么就直接从两边分别向内看最多选择的连续递增的序列中的个数，最后比较两边选择数的个数，选择个数多的那边就可以了。

所以最终的结论就是：

1.如果两边元素左小右大，选左边，左指针++；

2.如果两边元素左大右小，选右边，右指针--；

3.如果两边元素相同，分别从两边开始看最多选择多少个数，然后选择最多的那一边就可以了。

Code
```
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define N 200010
using namespace std;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int n,a[N],cnt=0,tmp=0;
char ans[N];

int main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	int l=1,r=n;
	while(1){
		if((a[l]<=tmp && a[r]<=tmp) || r<l) break;
		if(a[l]<a[r]){
			if(a[l]>tmp){
				tmp=a[l];
				ans[++cnt]='L';
				l++;
			}
			else{
				tmp=a[r];
				ans[++cnt]='R';
				r--;
			}
		}
		else if(a[l]>a[r]){
			if(a[r]>tmp){
				tmp=a[r];
				ans[++cnt]='R';
				r--;
			}
			else{
				tmp=a[l];
				ans[++cnt]='L';
				l++;
			}
		}
		else{
			int tot1=0;
			for(int i=l+1;i<=r;i++){
				if(a[i]>a[i-1]) tot1++;
				else break;
			}
			int tot2=0;
			for(int i=r-1;i>=l;i--){
				if(a[i]>a[i+1]) tot2++;
				else break;
			}
			if(tot1>tot2){
				for(int i=l;i<=l+tot1;i++){
					ans[++cnt]='L';
				}
			}
			else{
				for(int i=r;i>=r-tot2;i--){
					ans[++cnt]='R';
				}
			}
			break;
		}
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++) printf("%c",ans[i]);
	return 0;
}
```


---

## 作者：Luo_gu_ykc (赞：1)

## 题目大意

给定包含 $n$ 个整数的序列 $a$。

你可以做若干次操作，每次操作你可以拿走序列中最左边或者最右边的元素，把他写下来，并从序列中移除。你想要写下一个**严格上升**的序列，并且你想得到所有合法序列中最长的那一个。

### 注：

CF1157C1 与 CF1157C2 的不同在于 C1 中的所有 $a_i$ 均是不同的，而在 C2 中是不一定的。

## 思路

双指针实现，贪心思想；

看两端指针的数哪一个离上一次选的数更接近，然后再更新上次选的数；

* 先判断两端指针谁大谁小，就知道优先判断左还是右；

* 然后再判断是否大于上次选的数即可。

但此处有特殊情况，有可能两端指针相等，所以需要特判；

题目大意中给定，序列必须是严格上升的，所以遇到两段相等的情况就相当于选一段走到底；

有了这个推断，接下来就简单多了；

先从左右指针各走一遍，看哪端能走更多就知道了答案，最后输出；

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int a[N], n, op, len;
char s[N];

int main(){
	cin >> n;
	for(int i = 1; i <= n; ++i){
		cin >> a[i];
	}
	int l = 1, r = n;
	while(l <= r){
		if(a[l] > a[r]){ // 判断谁更小
			if(a[r] > op){ // 检查是否大于上次选的数
				op = a[r]; // 更新上次选的数
				r--;
				s[len++] = 'R';
			} else if(a[l] > op){
				op = a[l];
				l++;
				s[len++] = 'L';
			} else { // 如果两端指针都小于
				break; // 提前退出循环
			}
		} else if(a[l] < a[r]){
			if(a[l] > op){  // 同理
				op = a[l];
				l++;
				s[len++] = 'L';
			} else if(a[r] > op){
				op = a[r];
				r--;
				s[len++] = 'R';
			} else {
				break;
			}
		} else {
		  	int len1 = 0, len2 = 0;
		  	for(int i = l; i <= r && a[i - 1] < a[i]; i++){ // 先从左指针走一遍 
        		len1++; // 看能走多久 
			}
		  	for(int i = r; i >= l && a[i] > a[i + 1]; i--){ // 再从右指针走 
        		len2++;
		  	}
		  	if(len1 < len2){ // 看谁走得更远 
        		for(int i = r; i >= l && a[i] > a[i + 1]; i--){
          			s[len++] = 'R'; 
        		}
		  	} else {
		    	for(int i = l; i <= r && a[i - 1] < a[i]; i++){
          			s[len++] = 'L';
		    	}
		  	}
		  	break; // 记住一段走到底 
		}
	}
	cout << len << "\n";
	for(int i = 0; i < len; i++){
		cout << s[i];
	}
  	return 0;
}
```

---

## 作者：Mosher (赞：1)

### 水题呀，建议绿或黄题

~~水题解啦！长经验！~~

**正文：**

1. 题意：不用我说了吧，注意到：每次取出的数都要**大于**上一次取出的数，**相等时就成了取舍重点**，先两个都选，然后直接取完到自身选择的**最大答案**，比较即可。

2. 算法：使用手工队列来分类讨论模拟过程即可

3. 另外：觉得想要双倍经验的，去做下[简单版](https://www.luogu.org/problem/CF1157C1)吧。

**Code（写得丑，求轻喷）:**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,a[maxn],ans;
char s[maxn];

int main(){
	scanf("%d",&n);
	int tail=n,head=1,last=0;//队尾，队头，上个选的数
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	while(1){//都是要严格大于的
		if((a[tail]-last<=0&&a[head]-last<=0)||tail<head||ans==n) break;
		else if(a[tail]-last<=0&&a[head]-last>0){
			last=a[head];
			head++;
			s[ans++]='L';
		}
		else if(a[head]-last<=0&&a[tail]-last>0){
			last=a[tail];
			tail--;
			s[ans++]='R';
		}
		else if(a[tail]<a[head]&&a[tail]>last){
			last=a[tail];
			tail--;
			s[ans++]='R';
		}
		else if(a[head]<a[tail]&&a[head]>last){
			last=a[head];
			head++;
			s[ans++]='L';
		}
		else if(a[head]==a[tail]&&a[head]>last){//相等时
			int ans1=0,ans2=0,last1=last,last2=last;
			for(int i=head;i<=tail;++i){
				if(a[i]>last1) last1=a[i],ans1++;
				else break;
			}
			for(int i=tail;i>=head;--i){
				if(a[i]>last2) last2=a[i],ans2++;
				else break;
			}
			if(ans1>ans2){
				last=a[head];
				head++;
				s[ans++]='L';
			}
			else{
				last=a[tail];
				tail--;
				s[ans++]='R';
			}
		}
	}
	printf("%d\n%s",ans,s);
	return 0;
}
```

rp--

---

## 作者：Shanganze (赞：1)

又是一道贪心水题。

### 分析：
题目要求每次只能从最左侧或最右侧取数，我们只需要判断当前是选左侧更优还是右侧更优即可。优先选择更小的，显然后面有更大几率能够取更多数，若两数相同时，判断两端选哪一端后能选更多数，就先选哪一端。

### 贪心证明：
先取了一端较小的，后可以再取另一端；而取了较大的一端后无法取较小的一端。所以先取较小一端更优。

一直如上取数，直到左右两端都无法取数或数都已去完时截止，。

### 代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
int x[300001];
int main(){
	int n,m;
	cin>>n;
	for(int q=1;q<=n;q++)cin>>x[q];
	int l=1,r=n,last=-1e9,ans=0;
	string a;
	while(l<=r){
		if(x[l]<=last&&x[r]<=last)break;
		ans++;
		if(x[r]<=last&&x[l]>last){//只能取左，而不能取右时，直接取左
			a+='L';
			l++;
			last=x[l-1];
		}
		else if(x[l]<=last&&x[r]>last){//同理
			a+='R';
			r--;
			last=x[r+1];
		}
		else if(x[l]<x[r]){//两端都可取，优先取小的一端
			l++;
			a+='L';
			last=x[l-1];
		}
		else if(x[l]>x[r]){
			r--;
			a+='R';
			last=x[r+1];
		}
		else if(x[l]==x[r]){//相等时
			int p=0,pp=0,o=x[l],oo=x[r];
			for(int q=l+1;q<=r;q++){
				if(x[q]>o)p++,o=x[q];
				else break;
			}
			for(int q=r-1;r>=l;q--){
				if(x[q]>oo)pp++,oo=x[q];
				else break;
			}
			if(p>pp){
				l++;
				a+='L';
				last=x[l-1];
			}
			else{
				r--;
				a+='R';
				last=x[r+1];
			}
		}
	}
	cout<<ans<<"\n"<<a;
	return 0;
}

```


---

## 作者：DovFrcm (赞：0)



[原题链接 $\verb!here!$](https://www.luogu.com.cn/problem/CF1157C2)

[博客链接 $\verb!here!$](https://www.luogu.com.cn/blog/XYJ-ABM/solution-cf1157c2)

## 题目大意
一个数列，只能取两边，且取出的数**严格大于**上一次取出的数（$\verb!easy!$ 版的要求**大于等于**上一次取的数），求最多能取多少数，且给出方案。

## 分析

### 对于 $\verb!easy!$ 版的分析

我们可以先分析 $\verb!easy!$ 版怎么做，首先两边的数一共有三种情况。（如果已经分析过 $\verb!easy!$ 版的朋友可以直接跳到 $\verb!hard!$ 版的分析）

1. 左边的数大于右边的数。

1. 左边的数等于右边的数。
1. 左边的数小于右边的数。

对于第一种情况：不难发现，取的数越大，之后可以取的数的个数越少，取的数越小，之后可以取的数的个数越多。所以我们应该尽可能取更小的数，应该先判断右边的数是否大于上一次取的数，如果大于上一次取的数则取，如果小于上一次取的数则继续判断左边的数是否大于上一次取的数，如果大于上一次取的数则取，如果小于上一次取的数则取不了了，输出答案。

对于第二种情况：既然要求取出的数可以**等于**上一次取的数，那么直接将两头的数取出来。

对于第三种情况：与第一种情况一样，不过需要先判断左边在判断右边。

### 对于 $\verb!hard!$ 版的分析

$\verb!easy!$ 版的分析完了，那 $\verb!hard!$ 版的怎么做呢？

我们可以发现 $\verb!hard!$ 版与 $\verb!easy!$ 版相比，只限制了取的数不能等于上一次取的数，那我们先模拟几个左右两头的数相等的数据。

$$2,\ 3,\ 4,\ 5,\ 6,\ 9,\ 8,\ 7,\ 2$$

在 $\verb!easy!$ 版中，我们可以先将两边的 $2$ 全取了，然后再按照数字大小依次取完数字。

但在 $\verb!hard!$ 版中，我们只能选择取一边的 $2$，因为取了左边的 $2$ 之后右边的 $2$ 会因为与上一次取的数相等而取不了，而右边的 $2$ 的左边两个数会因为有 $9$ 与 $2$ 的阻挡取不了。同理，如果我们取了右边的 $2$，我们同样会放弃 $3,\ 4,\ 5,\ 6$ 这几个数。

我们发现，我们会在左边一段**连续**的**严格上升**的数字与右边一段**连续**的**严格下降**的数字中做出选择，而做出选择后，我们将无数可取。

所以如果左右两边的数字相等，我们可以求出左边一段**连续**的**严格上升**的数字与右边一段**连续**的**严格下降**的数字的长度，取两段数字中数字较多的一段，然后输出答案


## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	
	int n;
	cin >> n;
	
	deque<int> q;
	for(int i = 1; i <= n; i++){
		int x;
		cin >> x;
		q.push_back(x);
	}
	
	vector<bool> ans_;
	int lst = 0;
	while(!q.empty()){
//		cout << lst << '\n';
		bool f = 1;
		if(q.front() > q.back()){//对应第一种情况
			if(lst < q.back()){
				lst = q.back();
				f = 0;
				q.pop_back();
				ans_.push_back(0);
			}else if(lst < q.front()){
				lst = q.front();
				f = 0;
				q.pop_front();
				ans_.push_back(1);
			}
		}else if(q.front() < q.back()){//对应第三种情况
			if(lst < q.front()){
				lst = q.front();
				f = 0;
				q.pop_front();
				ans_.push_back(1);
			}else if(lst < q.back()){
				lst = q.back();
				f = 0;
				q.pop_back();
				ans_.push_back(0);
			}
		}else{//对应第二种情况
			int lst1 = lst, lst2 = lst;
			int k1 = 0, k2 = 0;
			
			stack<int> fg;
			while(!q.empty() && lst1 < q.front()){//一直取左边
				lst1 = q.front();
				k1++;
				fg.push(q.front());
				q.pop_front();
			}
			
			while(!fg.empty()){
				q.push_front(fg.top());
				fg.pop();
			}
			
			while(!q.empty() && lst2 < q.back()){//一直取右边
				lst2 = q.back();
				k2++;
				q.pop_back();
			}
			
			if(k1 > k2){
				for(int i = 1; i <= k1; i++){
					ans_.push_back(1);
				}
			}else{
				for(int i = 1; i <= k2; i++){
					ans_.push_back(0);
				}
			}
			break;
		}
		if(f)break;
	}
	
	cout << ans_.size() << '\n';
	
	for(int i = 0; i < ans_.size(); i++){
		cout << (ans_[i] ? 'L' : 'R');
	}
	
	return 0;
}
/*
6
1 2 6 5 4 3

1 10 11 12 13 1 10 9 1
*/
```


---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1157C2)

记录一个弱智错误。

感觉这题面有点 CSP-S 2021 T3 那味了（

显然是贪心模拟题。

考虑最后选出的序列必然是单调递增的，因此每次必须选当前可选的最小数。如果左右两端的数相等，分别从左右两端向下枚举，看看分别能扩展多少，扩展多的那一端就是答案。

但是如果你用数组模拟一个双端队列，那么注意判断的时候要判断两次左右端点值相等的情况，否则会 WA on #17。

时间复杂度 $O(n)$。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define back return
#define ri register int
#define ull unsigned ll
using namespace std;
ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	back x*f;
}
char c[200005];
int n,sum,sum1,sum2,a[200005],a1[200005];
int main()
{
	n=read();
	for(ri i=1;i<=n;i++)
		a[i]=read();
	int l=1,r=n,last=0;
	while(l<=r)
	{
		if(a[l]<=last&&a[r]<=last)
			break;
		if(a[l]==a[r])
		{
			int lsbl=last;
			for(ri i=l;i<=r;i++)
				if(a[i]>last)
					sum1++,last=a[i];
				else
					break;
			last=lsbl;
			for(ri i=r;i>=l;i--)
				if(a[i]>last)
					sum2++,last=a[i];
				else
					break;
			if(sum1>=sum2)
			{
				for(ri i=sum+1;i<=sum+sum1;i++)
					c[i]='L';
				sum+=sum1;
				break;
			}
			else
			{
				for(ri i=sum+1;i<=sum+sum2;i++)
					c[i]='R';
				sum+=sum2;
				break;
			}
		}
		if((a[r]<=a[l]&&a[r]>last)||(a[l]<=last&&a[r]>last))
			c[++sum]='R',last=a[r--];	
		if(l>r)
			break;
		if(a[l]==a[r])//这部分需要判断两次，因为上次处理过之后可能出现左右端点相等情况
		{
			int lsbl=last;
			for(ri i=l;i<=r;i++)
				if(a[i]>last)
					sum1++,last=a[i];
				else
					break;
			last=lsbl;
			for(ri i=r;i>=l;i--)
				if(a[i]>last)
					sum2++,last=a[i];
				else
					break;
			if(sum1>=sum2)
			{
				for(ri i=sum+1;i<=sum+sum1;i++)
					c[i]='L';
				sum+=sum1;
				break;
			}
			else
			{
				for(ri i=sum+1;i<=sum+sum2;i++)
					c[i]='R';
				sum+=sum2;
				break;
			}
		}
		if((a[l]<=a[r]&&a[l]>last)||(a[r]<=last&&a[l]>last))
			c[++sum]='L',last=a[l++];	
	}
	cout<<sum<<"\n";
	for(ri i=1;i<=sum;i++)
		cout<<c[i];
	back 0;
}
```

---

## 作者：小元勋 (赞：0)

## 题意

- 给定一个长度为$n$的序列，每一次可以从序列最左边或者最右边拿出一个数。必须使拿出来的数列单调递增，最大化拿出来数的数量，并求方案。$n<=2*10^{5}$

## 分析：

- 如果左右两边数不相等，那么拿较小的且满足单调递增的数更优

- 如果两个数相等，那么从一端拿了之后另一端就无法再拿了。直接看从左端还是右端拿哪边更优就行了。

- 时间复杂度$O(n)$

## $Code$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 200050

int n,a[maxn],lst,l,r,cnt = 0;
char ans[maxn];

inline int read_() {
	int x_=0,f_=1;char c_=getchar();
	while(c_<'0'||c_>'9') {if(c_=='-') f_=-1;c_=getchar();}
	while(c_>='0'&&c_<='9') {x_=(x_<<1)+(x_<<3)+c_-'0';c_=getchar();}
	return x_*f_;
}

void readda_() {
	n = read_();
	for(int i=1;i<=n;++i) a[i] = read_();
	lst = 0;l = 1;r = n;
	while(l<=r){
		if(a[l]!=a[r]) {
			if(lst<a[l]&&lst<a[r]) {
				if(a[l]<a[r]) {
					lst = a[l];
					++l;
					ans[++cnt] = 'L';
				}
				else {
					lst = a[r];
					--r;
					ans[++cnt] = 'R';
				}
			}
			else if(lst<a[l]) {
				lst = a[l];
				++l;
				ans[++cnt] = 'L';
			}
			else if(lst<a[r]) {
				lst = a[r];
				--r;
				ans[++cnt] = 'R';
			}
			else break;
		}
		else {
			if(lst>=a[l]) break;
			int len_1 = 1,len_2 = 1;
			for(int i=(l+1);i<=r;++i) {
				if(a[i]>a[i-1]) ++len_1;
				else break;
			}
			for(int i=(r-1);i>=l;--i) {
				if(a[i]>a[i+1]) ++len_2;
				else break;
			}
			if(len_1>len_2) while(len_1--) ans[++cnt] = 'L';
			else while(len_2--) ans[++cnt] = 'R';
			break;
		}
 	}
 	printf("%d\n",cnt);
 	for(int i=1;i<=cnt;++i) printf("%c",ans[i]);
}

int main() {
//	freopen("a.txt","r",stdin);
	readda_();
	return 0;
}
```



---

## 作者：Derpy (赞：0)

### 闲来没事来水篇题解

~~其实这题本身也还是比较水~~

# 另外要注意在左右操作对答案的贡献一样时优先从右边操作！！！

如：1 1 这样的数就得输出 1 R

### 好了进入正题

## 先说思路吧

首先看到题我们就比较容易想到是贪心，每次从两端中选出较小那个。至于证明嘛。。。你想啊，如果你先取走了小的那个在取走右边大的那个完全不会亏啊。所以这道题就这样A掉了。

好吧开玩笑的。。。假如你直接这样做的话你会发现当遇到两个数相同的时候你就会左右为难，迷茫而无所适从，这时候怎么办呢？我们可以发现如果你选择了左边那个数，右边那个数就不可能被取到了，只能从左边一直拿到底，右边也是同理，所以遇到左右为难的情况的时候直接从左数一遍在从右数一遍取较大者就好了，时间复杂度O(n）。附上双倍经验题（[甚至是easy版本的](https://www.luogu.org/problem/CF1157C1)）

## 思路就到这了，下面是具体实现

由于一直在比较最前面那个数和最后面那个数，可以想到双向队列，但是最后那个扫描操作光是双向队列好像比较难实现，再加上C++自带的双向队列常数好像很大，我就自己手写了一个（马生第一次手写这种东西），感觉实现起来比较方便，看起来的话也比较好理解，最后写出来按时间排名的话也还是比较靠前（~~其实是因为快读的原因~~）。

## 再具体一点的话还是看代码吧

```c
#include<bits/stdc++.h>
#define mx 200005 
using namespace std;
queue<char>q;//由于先出结果再输出具体操作，所以我用了个队列来储存每一次操作 
inline int r()//标准的快读，不再赘述。。。 
{
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')
		{
			f=-1;
		}
		ch=getchar();
	}
	while(isdigit(ch))
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
struct QAQ//自写双向队列 (PS:里面的函数名我自己随便起的，不是具体对应的双向队列里的函数名 
{
	int a[mx],head=1,tail=0;
	bool empty()//判空 
	{
		if(tail-head==-1) return 1;
		else return 0;
	}
	void psb(int x)//从队尾插入(push_back) 
	{
		a[++tail]=x;
	}
	int ff()//查看队首(find front) 
	{
		return a[head];
	}
	int fb()//查看队尾(find back)
	{
		return a[tail];
	}
	void ppf()//弹出队首(pop_front) 
	{
		head++;
	}
	void ppb()//弹出队尾(pop_back) 
	{
		tail--;
	}
	int SPJ()//最后的特判(special judge)，返回的值是最后能取走的最长长度 
	{
		int ansl=0,ansr=0;
		for(int i=head+1;i<=tail;i++)//从左边开始取的话。。。 
		{
			if(a[i]>a[i-1]) ansl++;
			else break;
		}
		for(int i=tail-1;i>=head;i--)//从右边开始取的话。。。
		{
			if(a[i]>a[i+1]) ansr++;
			else break;
		}
		if(ansl>ansr)//择优录取 
		{//之前有提到过这种情况所进行的操作要么全是左边要么全是右边，所以直接把对应数量的操作装进队列里就好了 
			for(int i=0;i<=ansl;i++)//为什么从0开始记?因为我们是先取了一个再开始进行ansl和ansr的长度判断的所以得多记一次 
			{
				q.push('L');
			}
			return ansl+1;
		}
		else//这个else实现了优先右边 
		{ 
			for(int i=0;i<=ansr;i++)
			{
				q.push('R');
			}
			return ansr+1;
		}
	}
};
QAQ A;//定义一个可爱的双向队列 
int main()
{
	int n;
	n=r();
	for(int i=1,c;i<=n;i++)
	{
		A.psb(r());//入队列 
	}
	int last=-0x3f3f3f3f;//用于保存上一个取的数，由于第一个可以随便取，所以赋了一个很小的初值 
	int ans=0;//记录操作次数 
	while(!A.empty())
	{
		if(A.fb()<=last&&A.ff()<=last)//都不能取时 
		{
			break;
		}
		else
		{
			if(A.ff()>last&&A.fb()<=last)//只有左边能取时 
			{
				ans++;
				last=A.ff();
				q.push('L');
				A.ppf();
			}
			else
			{
				if(A.fb()>last&&A.ff()<=last)//只有右边能取时 
				{
					ans++;
					last=A.fb();
					q.push('R');
					A.ppb();
				}
				else//两边都能取时 
				{
					if(A.ff()>A.fb())//要先取走小的 
					{
						ans++;
						last=A.fb();
						q.push('R');
						A.ppb();
					}
					else
					{
						if(A.ff()<A.fb())
						{
							ans++;
							last=A.ff();
							q.push('L');
							A.ppf();
						}
						else//两边一样大左右为难时 
						{
							ans+=A.SPJ();//用上我们的特判 
							break;
						}
					}
				}
			}
		}
	}
	printf("%d\n",ans);//先输出答案 
	while(!q.empty())
	{
		putchar(q.front());//再输出过程 
		q.pop();
	}
	return 0;//收刀 
}
```

~~大佬轻喷~~

---

