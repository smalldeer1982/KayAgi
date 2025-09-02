# Increasing Subsequence (easy version)

## 题目描述

The only difference between problems C1 and C2 is that all values in input of problem C1 are distinct (this condition may be false for problem C2).

You are given a sequence $ a $ consisting of $ n $ integers. All these integers are distinct, each value from $ 1 $ to $ n $ appears in the sequence exactly once.

You are making a sequence of moves. During each move you must take either the leftmost element of the sequence or the rightmost element of the sequence, write it down and remove it from the sequence. Your task is to write down a strictly increasing sequence, and among all such sequences you should take the longest (the length of the sequence is the number of elements in it).

For example, for the sequence $ [2, 1, 5, 4, 3] $ the answer is $ 4 $ (you take $ 2 $ and the sequence becomes $ [1, 5, 4, 3] $ , then you take the rightmost element $ 3 $ and the sequence becomes $ [1, 5, 4] $ , then you take $ 4 $ and the sequence becomes $ [1, 5] $ and then you take $ 5 $ and the sequence becomes $ [1] $ , the obtained increasing sequence is $ [2, 3, 4, 5] $ ).

## 说明/提示

The first example is described in the problem statement.

## 样例 #1

### 输入

```
5
2 1 5 4 3
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
1 3 5 6 7 4 2
```

### 输出

```
7
LRLRLLL
```

## 样例 #3

### 输入

```
3
1 2 3
```

### 输出

```
3
LLL
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
LLRL
```

# 题解

## 作者：L______ (赞：7)

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

## 作者：Mosher (赞：3)

### 水题呀，建议黄或橙题

~~水题解啦！长经验！~~

**正文：**

1. 题意：不用我说了吧，注意到：每次取出的数都要**大于等于**上一次取出的数，那算法就很显然了。

2. 算法：使用双端队列或手工队列来模拟过程即可

3. 另外：觉得太水的，去做下[加强版](https://www.luogu.org/problem/CF1157C2)吧，虽然也水

**Code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,a[maxn],ans;
char s[maxn];

int main(){
	scanf("%d",&n);
	int tail=n,head=1,last=0;//last记录上一个选的,tail,head维护队尾，队头
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	while(1){
		if((a[tail]-last<0&&a[head]-last<0)||tail<head||ans==n) break;//宣布出来，或 选完，那就break
		else if(a[tail]-last<0&&a[head]-last>=0){//注意last先填写，以下模拟即可
			last=a[head];
			head++;
			s[ans++]='L';
		}
		else if(a[head]-last<0&&a[tail]-last>=0){
			last=a[tail];
			tail--;
			s[ans++]='R';
		}
		else if(a[tail]<a[head]){
			last=a[tail];
			tail--;
			s[ans++]='R';
		}
		else{
			last=a[head];
			head++;
			s[ans++]='L';
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
题目要求每次只能从最左侧或最右侧取数，我们只需要判断当前是选左侧更优还是右侧更优即可。优先选择更小的，显然后面有更大几率能够取更多数。

### 贪心证明：
先取了一端较小的，后可以再取另一端；而取了较大的一端后无法取较小的一端。所以先取较小一端更优。

一直如上取数，直到左右两端都无法取数或数都已去完时截止

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
		if(x[l]<last&&x[r]<last)break;
		ans++;
		if(x[r]<last&&x[l]>=last){//只能取左，而不能取右时，直接取左
			a+='L';
			l++;
			last=x[l-1];
		}
		else if(x[l]<last&&x[r]>=last){//同理
			a+='R';
			r--;
			last=x[r+1];
		}
		else if(x[l]<=x[r]){//两端都可去，优先取小的一端
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
	cout<<ans<<"\n"<<a;
	return 0;
}
```


---

## 作者：Luo_gu_ykc (赞：1)

## 题目大意

给定包含 $n$ 个整数的序列 $a$。

你可以做若干次操作，每次操作你可以拿走序列中最左边或者最右边的元素，把他写下来，并从序列中移除。你想要写下一个的序列，并且你想得到所有合法序列中最长的那一个。

## 思路

双指针实现，贪心思想；

看两端指针的数哪一个离上一次选的数更接近，然后再更新上次选的数；

如何看两端指针的数离上一次选的数更接近呢？

* 先判断两端指针谁大谁小，就知道优先判断左还是右；

* 然后再判断是否大于上次选的数即可。

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
			if(a[r] >= op){ // 检查是否大于上次选的数
				op = a[r]; // 更新上次选的数
				r--; // 移动指针
				s[len++] = 'R';
			} else if(a[l] >= op){
				op = a[l];
				l++;
				s[len++] = 'L';
			} else { // 如果两端指针都小于
				break; // 提前退出循环
			}
		} else {
			if(a[l] >= op){ // 同理
				op = a[l];
				l++;
				s[len++] = 'L';
			} else if(a[r] >= op){
				op = a[r];
				r--;
				s[len++] = 'R';
			} else {
				break;
			}
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

## 作者：StephenYoung (赞：1)

#### 最初想法

其实这道题有很多思考方式，不一定都和贪心有关。

不过我还是来贪心吧。

#### 实现

如果有一边比另外一边小，那就选这边，当然要比上一次大。

麻烦的是如果两边一样怎么办？

我们注意到在这种情况下，一定会有一端以后都不可能再被拿走了，所以直接看从左边开始拿和从右边开始拿哪一个拿的多就行了。（这个时候不需要比上次大，相等即可）

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=200007;
int n,a[maxn],l,r,last,cnt;
char c[maxn];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	l=1,r=n;
	for(int l=1,r=n;l<=r;)
	{
		if(a[l]<a[r]&&a[l]>last)
		{
			last=a[l];
			c[++cnt]='L';
			l++;
			continue;
		}
		if(a[l]>a[r]&&a[r]>last)
		{
			last=a[r];
			c[++cnt]='R';
			r--;
			continue;
		}
		if(a[l]>last)
		{
			last=a[l];
			c[++cnt]='L';
			l++;
			continue;
		}
		if(a[r]>last)
		{
			last=a[r];
			c[++cnt]='R';
			r--;
			continue;
		}
		break;
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
	printf("%c",c[i]);
	return 0;
}
```


---

## 作者：小元勋 (赞：0)

## 题意

- 给出一个长度为$n$的序列，每次可以在序列的最左边或者最右边选择一个数出来，要求选出来的数不递减。使选出来的数最多，并输出选择方案。$n<=2*10^{5}$

## 分析

- 我们要尽可能的选多，当左边或者右边只有一个数大于等于前一个选的数时，直接选那一个数。

- 当左边和右边的数都大于等于前一个选择的数时，选择较小的一个，这样对全局更优。

- 每次的选择，删除使用双端队列实现。

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
		if(lst<=a[l]&&lst<=a[r]) {
			if(a[l]<=a[r]) {
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
		else if(lst<=a[l]) {
			lst = a[l];
			++l;
			ans[++cnt] = 'L';
		}
		else if(lst<=a[r]) {
			lst = a[r];
			--r;
			ans[++cnt] = 'R';
		}
		else break;
 	}
 	printf("%d\n",cnt);
 	for(int i=1;i<=cnt;++i) printf("%c",ans[i]);
}

int main() {
	//freopen("a.txt","r",stdin);
	readda_();
	return 0;
}
```


---

## 作者：qian_shang (赞：0)

 这就是一道~~比较简单~~的贪心题

大致思路如下：

因为是严格不下降序列，所以每次可以在能选的时候贪心选择最小的

比如：3 5 2 2 1 那么第一次就会选择1，而不是3

有一种情况要特判一下就是两头的数相等的情况

这个时候就分别扫一遍两头，取max

代码（窝码风真的太丑了）
```#include<iostream>
#include<cstdio>
#include<algorithm>
#define N 200005
#define LL long long
using namespace std;
LL n,m,a[N],l,r,ans,cnt,suml,sumr,k,t;
char c[N]; bool flag;
bool cmp(LL a,LL b){return a<b;}
LL maxx(LL a,LL b){return a>b?a:b;}
int main()
{
	scanf("%lld",&n);
	for (LL i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	l=1; r=n; cnt=0;
	while (l<=r)
	{
		if (a[l]==a[r]) break;
		if (a[l]<=cnt&&a[r]<=cnt) {flag=1;break;}//不能选就退出
		if (a[l]<=cnt) {c[ans++]='R';cnt=a[r--];}
		else if (a[r]<=cnt) {c[ans++]='L';cnt=a[l++];}
		else if (a[l]<=a[r]) {c[ans++]='L';cnt=a[l++];}
		else {c[ans++]='R';cnt=a[r--];}//选择较小值记录
	}
	if (l<=r&&(!flag)) {//判断相等的情况
		k=l; t=cnt;
		while (k<=r)
		{
			if (a[k]<=t) break;
			suml++; t=a[k++];
		}
		k=r; t=cnt;
		while (k>=l) 
		{
			if (a[k]<=t) break;
			sumr++; t=a[k--];
		}
	}
	printf("%lld\n%s",ans+maxx(suml,sumr),c);
	if (suml>sumr) {
		while (suml--) printf("L");
	}else {
		while (sumr--) printf("R");
	}//输出
	return 0;
}//完结撒花
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

好吧开玩笑的。。。假如你直接这样做的话你会发现当遇到两个数相同的时候你就会左右为难，迷茫而无所适从，这时候怎么办呢？我们可以发现如果你选择了左边那个数，右边那个数就不可能被取到了，只能从左边一直拿到底，右边也是同理，所以遇到左右为难的情况的时候直接从左数一遍在从右数一遍取较大者就好了，时间复杂度O(n）。[附上双倍经验题](https://www.luogu.org/problem/CF1157C2)（方法优秀一点直接交就是了）

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

