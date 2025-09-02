# [USACO10MAR] Test Taking S

## 题目描述

Farmer John has to take his annual farming license test. The test comprises N (1 <= N <= 1,000,000) true/false questions. After FJ's dismal performance on last year's test Bessie wishes to help him.

Bessie has inside information that the number of questions whose answer is true will be one of t\_1, t\_2, t\_3,..., or t\_K (0 <= t\_i <= N; 0 <= K <= 10,000) -- even though Bessie has no information about any answer to any specific question. Bessie wants to know the best score that FJ is guaranteed achieve by exploiting this information carefully, even if he doesn't know the actual answers to any test questions.

To demonstrate Bessie's idea, consider a license test with N=6 questions where Bessie knows that the number of questions with the answer 'true' is either 0 or 3. FJ can always get at least 3 answers correct using logic like this: If FJ answers 'false' on every

question and there are 0 questions with the answer 'true' then he will get all 6 correct. If there are 3 questions with the answer 'true' then he will get 3 answers correct. So as long as he marks every answer as 'false' he is guaranteed to get at least 3 correct without knowing any answer to the test questions.

On the other hand, consider what happens if FJ chooses an inferior strategy: he guesses that some 3 answers are 'true' and the other 3 are 'false'. If it turns out that NO answers are 'true' then FJ will get 3 answers correct, the ones he guessed were false. If 3 answers are 'true' then FJ could get as few as 0 answers correct. If he answered incorrectly on all 3 of that answers for which he guessed 'true', and the other 3 (for which he guessed 'false') are true, then he gets 0 correct answers. Even though FJ could get 3 correct in this case by guessing 'false' every time, he can not always guarantee even 1 correct by guessing some 3 answers as 'true', so this strategy can not guarantee getting any answer correct. FJ should use the previous paragraph's strategy.

Given Bessie's inside information, determine the number of answers FJ can always get correct using this information assuming he uses it optimally.


Farmer John要参加一年一度的农民资格考试。考试很简单，只有N个 （1≤N≤1，000，000)true/false的判断题。然而FJ去年考试却“杯具”了，Bessie：希望今年能帮帮他。


Bessie得到可靠的内部消息，有可能有T\_1，T\_2，T\_3，...，或T\_K(0≤T\_i≤N；0≤K≤10，000)


道题的答案为ture：，但具体哪道题的答案是什么却不知道。Bessie希望知道在认真研究了这些内部消息后(虽然不能确定任何一道题的具体答案)，一定保证FJ考试时能获得的最高分数是多少?


为了说明Bessie的想法，考虑N=6的一次考试，Bessie知道答案为true的题的数量是0或者3。FJ可以按这样的做题策略来答对至少3题：如果FJ全部答'false'，那么当有0道题的正确答案是'true'，则FJ答对6题；而当有3道题的正确答案是'true'，则FJ答对3题。因此，只要FJ部答'false'，那么至少一定能答对3题，尽管FJ并不知道每道题的确切答案。


另一方面，考虑如果FJ选择了另一种非最优的做题策略：他猜测某3道题为'true'而另3道题为'false'。当所有题目的正确答案是'false'时，那么FJ能答对3道题。而当有3道题的正确答案是'true'时，那么FJ有可能一道题都答不对。这是因为FJ有可能把3道正确答案为'true'的题全猜成'false'!这说明这种做题策略不如前一种优秀。

给出Bessie获得的内部消息，计算出FJ采用最优做题策略保证能得到的最高分数是多少?

第1行：2个整数N，K

第2…K+1行：第i+1行包含一个整数t_i

第1行：一个整数，表示FJ一定能获得的最高分数

## 说明/提示

翻译提供： @fan404


## 样例 #1

### 输入

```
6 2 
0 
3 
```

### 输出

```
3 
```

# 题解

## 作者：sxyugao (赞：6)

总的证明楼下的yyhhenry大佬已经写了，如果想了解更多细节或者看不懂他证明的可以去我[博客](https://sxyugao.top/p/1192747.html#solution)上看。

我主要是证明他的那个引理：

> 对于两个长度为n的01串，A中a个1，B中b个1，任一排列中相同位置元素相同的数量至少为```max(a+b-n,n-a-b)```，通过分别分析0和1就可以得到。

我们仍然使用引理中的变量，进行分类讨论：

1、$a+b>n$，即 $A$ 和 $B$ 匹配1。

我们为了让相同元素尽可能少，考虑把 $A$ 中的1全移到前端，$B$ 中的1全移到后端，变成线段覆盖问题，重合部分为 $a+b-n$。

2、$a+b<n$，即 $A$ 和 $B$ 匹配0.

同理，我们考虑把 $A$ 中的0全移到前端，$B$ 中的0全移到后端，用同样的方法得出该情况下结果为 $n-a-b$。

3、$a+b=n$，显然答案为0。

------------
主要证明和代码请移步：https://sxyugao.top/p/1192747.html#solution

---

## 作者：wf1594937223 (赞：3)

一道完全不考察码代码能力的题目，细节比较少，可以说是数学专项练习题。

但是我太弱了，不会纯数学做法，所以提供一个数形结合的做法……

废话不多说，以下开始算法分析。

---

首先分析一下题面，题目说的是“至少”，那么明摆着是让我们求最坏的情况。

可不可能有空题比不空题答案更优的情况呢？显然是没有的。就像你考试的时候，不会的题蒙一个总比不蒙好吧。

我们设 $(a,n-a)$ 为猜 $a$ 个题对，$n-a$ 个题错的情况，然后将每一个限制也同样化为这种形式 $(T_i,n-T_i)$ ，则：

考虑我们的一个猜测 $(a,n-a)$ 与一个限制 $(b,n-b)$，由于我们是要求最坏的情况，那么我们一定是尽量地将我们所选的正确答案匹配答案中的错误答案，即让 $a$ 去匹配 $n-b$，让 $b$ 去匹配 $n-a$。那有多少题是能保证正确的呢？如果某一项匹配完了还有剩余，那这个剩余的就是能保证正确的。比如 $a$ 将 $n-b$ 都匹配完了，那么剩下来的题目就一定都是正确的。所以，这样一来，我们最多能匹配的数量就是 $| n-a-b |$。

接下来，考虑对 $|n-a-b|$ 变形为 $|(n-a)-b|$，即 $(n-a)$ 这个点到 $b$ 这个点的距离。由于每个 $b$ 在输入之后就是给定的，而 $|n-a|$ 相当于一个动点，所以其实此题就是让我们求一个点到一堆定点的最小值最大。

而要求这个值，我们其实只需要考虑相邻两个点的中点离这两个点的距离是多少就可以了。即 $ans=min({\lfloor \dfrac {a_i-a_{i-1}}{2}} \rfloor)$。

但是不要忘记考虑 $a=0$ 和 $a=n$ 的情况。

代码不到 $30$ 行，本人因为~~太懒了~~码风怪异，在此就不现丑了。

~~自己动手，丰衣足食~~

---

## 作者：ThinkofBlank (赞：2)

逛了下题解区才知道，原来这题有结论啊。。。苦笑。。。

不过，也不需要那么复杂，我们来看一个思想更容易理解（说白了就是更暴力的解法，2333）

首先，我们假设，本次答题我们回答i个false和n-i个true[这样假设的目的是为了让式子看起来更漂亮一点]，那么很明显，本次的“保证收益”是:

**$w=min(abs(i-Tj))(j=1,2...n)$**

**[其实，就相当于是最坏情况能答对的题目数]**

然而， 我们枚举i，要用n次枚举，每次枚举又需要k次计算，那么复杂度就达到了恐怖的$O(nk)$了妥妥的TLE

那么，我们必然需要一个方法来优化它！

我们再观察下式子$w=min(abs(i-Tj))$,这个式子的意义是什么？

**不就是$Tj(j=1,2...n)$中最接近i的数字与i的距离吗！**

**我们可以发现，这个数肯定不是前缀就是后缀！**

于是，我们首先将T数组排序，每次二分出当前枚举的i的前后缀再取min即可！

代码:

```c++
//#pragma GCC optimize(3,"inline","Ofast")//手动O3优化
//#pragma GCC target("sse","sse2","sse3","sse4","avx","avx2","popcnt")
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+1;
int a[N];
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;++i){
		scanf("%d",&a[i]);
	}
	sort(a+1,a+k+1);
	int ans=0;
	for(int i=0;i<=n;++i){//回答i个false,n-i个true
		int l=1,r=k,pre=233333333,suf=233333333;//小皮一下
		while(l<=r){
			int mid=(l+r)>>1;
			if(a[mid]<=i){
				pre=a[mid];l=mid+1;
			}else{
				r=mid-1;
			}
		}
		l=1,r=k;
		while(l<=r){
			int mid=(l+r)>>1;
			if(a[mid]>=i){
				suf=a[mid],r=mid-1;
			}else{
				l=mid+1;
			}
		}
		ans=max(ans,min(abs(i-pre),abs(suf-i)));
	}
	printf("%d",ans);
	return 0;
}
```

然后，就AC了。。。

然而，我们并不满足！

很明显，这份代码的复杂度是$O(nlogn)$的，而且常数有点点大（真的只有一点点qwq）

我们考虑下怎么再优化下复杂度

我们观察到，复杂度的局限在于两个地方:

1.排序

2.二分查找前后缀

我们考虑优化这两个地方

排序非常好优化，因为n很小，直接扔桶里即可（当然，你写个基排我也不能说什么。。。）

主要的便是怎么优化找前后缀了。

**我们发现，我们枚举的i是单调的（废话）**

**所以，我们的前后缀也肯定是单调的！所以我们可以直接开一个单调指针来维护前后缀即可**

整体复杂度优化为$O(n)$!(有些小细节需要注意，代码中已经表明)

代码:

```c++
//#pragma GCC optimize(3,"inline","Ofast")//手动O3优化
//#pragma GCC target("sse","sse2","sse3","sse4","avx","avx2","popcnt")
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+1;
int a[N];bool vis[N];
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;++i){
		int x;
		scanf("%d",&x);
		vis[x]=1;
	}
	k=0;//输入中有重复数字，需要重新调整k的大小 
	for(int i=0;i<=n;++i){
		if(vis[i]){
			a[++k]=i;
		}
	}
	int ans=0,pre=0,suf=1;
	for(int i=0;i<=n;++i){//回答n-i个true,i个false
		while(pre<k&&a[pre+1]<=i){//记得写小于k，防止越界等不可避免的玄学错误 
			++pre;
		}
		while(suf<k&&a[suf]<i){
			++suf;
		}
		ans=max(ans,min(abs(a[pre]-i),abs(a[suf]-i)));
	}
	printf("%d",ans);
	return 0;
}
```



---

## 作者：MadokaKaname (赞：1)

~~只有我用的暴力吗........~~

## solution

发现最差情况为最多的 $0$ 和 $1$ 发生了错位，即为 $ \left |  a_i - x \right | $。

因此题目转化为最大化 $ \left |  a_i - x \right | $ 的最小值。

发现 $n \le 10^6 $，$k \le 10^4$，排序后 $O(n)$ 爆搜即可。

时间复杂度 $O(n+k\log k)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int maxx=0;
int n,i,j,k,m,x;
int a[10005];
int main() {
    cin>>n>>m;
    for(i=1;i<=m;i++)
      scanf("%d",&a[i]);
    sort(a+1,a+m+1);
    a[m+1]=0x7fffffff;
    int now=0;
    for(i=0;i<=n;i++){
    	maxx=max(maxx,min(i-a[now],a[now+1]-i));
    	while(a[now+1]==i) now++;
	}
    printf("%d",maxx);

	return 0;
}

```



---

## 作者：ddmd (赞：1)

这道题的题意也是非常简单的，主要是将算法进行分析化简。   

我们可以将限制表示为 $ (T_{i},n-T_{i})$ ,那么我们可以发现最后的结果就是 $ ans = min(\dfrac{T_{i}-T_{i-1}}{2})$。   

最后在判断一下 $ i = 1 $ 和 $i = n$ 即可。   

Code


------------
```cpp
// Dong_Dong出品 必是精品

#include<bits/stdc++.h>
#define int long long
using namespace std;

inline int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
inline void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
inline void writesp(int x)
{
	write(x);
	putchar(' ');
}
inline void writeln(int x)
{
	write(x);
	putchar('\n');
}
bool cmp(int x,int y)
{
	return x<y;
}
const int Maxn=1e4+5;
int a[Maxn]; 
signed main()
{
	int n=read(),m=read();
	for (int i=1;i<=m;i++) 
		a[i]=read();
	sort(a+1,a+m+1,cmp);
	int ans=max(a[1],n-a[m]);
	for (int i=2;i<=m;i++)
		ans=max(ans,(a[i]-a[i-1])/2);
	writeln(ans); 
	return 0;
}
```



---

## 作者：巨型方块 (赞：1)

太菜了，贪心都不会了

读入
排序
答案来自于3个地方

a[1]
m-a[n]
(a[i]-a[i-1])/2

想来也是很显然的

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5;
int a[N];
int n,ans,m;
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    ans=max(a[1],m-a[n]);
    for(int    i=2;i<=n;i++)ans=max(ans,(a[i]-a[i-1])/2);
    printf("%d",ans);
}

```

---

