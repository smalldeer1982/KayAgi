# Chat Ban

## 题目描述

You are a usual chat user on the most famous streaming platform. Of course, there are some moments when you just want to chill and spam something.

More precisely, you want to spam the emote triangle of size $ k $ . It consists of $ 2k-1 $ messages. The first message consists of one emote, the second one — of two emotes, ..., the $ k $ -th one — of $ k $ emotes, the $ k+1 $ -th one — of $ k-1 $ emotes, ..., and the last one — of one emote.

For example, the emote triangle for $ k=3 $ consists of $ 5 $ messages:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1612C/2949e1c874315434d0b3c1f5e20dee7c9097dc7a.png)Of course, most of the channels have auto moderation. Auto moderator of the current chat will ban you right after you spam at least $ x $ emotes in succession (you can assume you are the only user in the chat). Now you are interested — how many messages will you write before getting banned? Or maybe you will not get banned at all (i.e. will write all $ 2k-1 $ messages and complete your emote triangle successfully)? Note that if you get banned as a result of writing a message, this message is also counted.

You have to answer $ t $ independent test cases.

## 说明/提示

Let's analyze the test cases of the example.

1. In the first test case, you write three messages containing $ 1 $ , $ 2 $ and $ 3 $ emotes respectively, and since $ 1 + 2 + 3 \ge 6 $ , you get banned after that.
2. In the second test case, you write four messages containing $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ emotes respectively, and since $ 1 + 2 + 3 + 4 \ge 7 $ , you get banned after that.
3. In the third test case, you write one message containing exactly $ 1 $ emote. It doesn't get you banned, since $ 1 < 2 $ , but you have already finished posting your emote triangle. So you wrote one message successfully.
4. In the fourth test case, you write four messages containing $ 1 $ , $ 2 $ , $ 3 $ and $ 2 $ emotes respectively, and since $ 1 + 2 + 3 + 2 \ge 7 $ , you get banned after that.
5. In the fifth test case, you write three messages containing $ 1 $ , $ 2 $ and $ 1 $ emote respectively. It doesn't get you banned, since $ 1 + 2 + 1 < 5 $ , but you have already finished posting your emote triangle. So you wrote three messages successfully.
6. In the sixth test case, since $ x = 1 $ , you get banned as soon as you send your first message.
7. The seventh test case is too large to analyze, so we'll skip it.

## 样例 #1

### 输入

```
7
4 6
4 7
1 2
3 7
2 5
100 1
1000000000 923456789987654321```

### 输出

```
3
4
1
4
3
1
1608737403```

# 题解

## 作者：Terraria (赞：4)

目前题解都是二分的做法，来水一篇数学解法 qaq。

首先肯定要分类讨论。

- $k \ge n^2$

由于这样的一个图形，一共有 $1+2+\cdots+n-1+n+n-1+ \cdots +2+1=n^2$ 个图案，所以我们可以把每一行都填满。

所以直接输出 $2 \times n-1$ 即可。

- $k \leq \dfrac{n(n+1)}{2}$

这意味着我们最多可以把前 $n$ 层填满。也就是说，我们每一行需要填入的数的个数一定是递增的。

我们不妨假设 $x$ 为能够填入的最多行数，就是我们的答案。

所以我们可以得到一个不等式：

$$\dfrac{x(x-1)}{2} < k \leq \dfrac{x(x+1)}{2}$$

这个不等式的意思是说，我们可以填入的个数，要填满前 $x-1$ 行且能继续填到第 $x$ 行，但是不能填到第 $x+1$ 行。

这里解一个不等式为例，其他的不等式可以类似求解：

解

$$\dfrac{x(x-1)}{2} < k$$

两边同时乘以 $2$ 得

$$x^2-x<2k$$

将左式配方并移项，得

$$(x-\dfrac{1}{2})^2<2k+\dfrac{1}{4}$$

考虑到我们的 $x-\dfrac{1}{2}$ 一定取得正数，所以这个不等式的一部分解集

$$x-\dfrac{1}{2}>-\sqrt{2k+\dfrac{1}{4}}$$

舍去，得到

$$x-\dfrac{1}{2}<\sqrt{2k+\dfrac{1}{4}}$$

即

$$x < \sqrt{2k+\dfrac{1}{4}}+\dfrac{1}{2}$$

而对于不等式

$$k \leq \dfrac{x(x+1)}{2}$$

我们可以用类似得方法得到

$$x \ge \sqrt{2k+\dfrac{1}{4}}-\dfrac{1}{2}$$

所以对于这一部分的解集为 

$$\sqrt{2k+\dfrac{1}{4}}-\dfrac{1}{2} \leq x <\sqrt{2k+\dfrac{1}{4}}+\dfrac{1}{2}$$

显然这个不等式有且只有一个正整数解，这个解可以通过对 $\sqrt{2k+\dfrac{1}{4}}-\dfrac{1}{2}$ 的值上取整得到。

所以我们就得到了答案。

- $\dfrac{n(n+1)}{2}<k <n^2$

不难发现，这时候我们会填写到下半部分。似乎有点难搞？

我们不妨转化一下——

记 $l=n^2-k$，现在我们只需要求用 $l$ 个消息能够填**满**的总行数 $x$，最终答案用 $2 \times n-1-x$ 即可。

由于是填满 $x$ 行，但是填不满第 $x+1$ 行，于是我们可以得到不等式

$$\dfrac{x(x+1)}{2}\leq l <\dfrac{(x+1)(x+2)}{2}$$

按照上面的步骤可以解得

$$\sqrt{2l+\dfrac{1}{4}}-\dfrac{3}{2}<x \leq \sqrt{2l+\dfrac{1}{4}}-\dfrac{1}{2}$$

所以我们需要的 $x$ 只用对 $\sqrt{2l+\dfrac{1}{4}}-\dfrac{1}{2}$ 下取整即可。

## 几个代码实现小细节

在解完不等式后，要注意判断上下取整得到答案的问题。例如第 $3$ 个分析中，如果我们对 $\sqrt{2l+\dfrac{1}{4}}-\dfrac{3}{2}$ 上取整，有可能 $\sqrt{2l+\dfrac{1}{4}}-\dfrac{3}{2}$ 自身就是整数，导致取得的 $x=\sqrt{2l+\dfrac{1}{4}}-\dfrac{3}{2}$，与不等式相矛盾。

还有，由于这个是数学方法，对于精度的要求可能会比较大，需要用 `long double` 记录 $\sqrt{2k+\dfrac{1}{4}}$ 的值，再算出 $x$ 的值，这样精度误差会小一点（反正我是这样才过去的）。

另外，这个做法不知道为什么，一份 AC 过的代码有时候能过，有时候过不了（可以参见我的提交记录[一](https://www.luogu.com.cn/record/65962109)、[二](https://www.luogu.com.cn/record/65963049)），不知道是不是哪里又有精度问题还是怎么的，欢迎大佬在讨论区里指出！

如果不想避免这种情况，考虑到精度误差不会很大，可以特判一下 $ans-1,ans,ans+1$ 中哪一个是正确答案（

时间复杂度 $\text{O}(T)$。

代码不放了，感觉讲的还挺详细的（

---

## 作者：Jur_Cai (赞：3)

### 题意
第 $1$ 行有 $1$ 个表情，第 $2$ 行有 $2$ 个表情 $\dots$ 第 $k$ 行有 $k$ 个表情。

第 $k+1$ 行有 $k-1$ 个表情，第 $k+2$ 行 $k-2$ 个表情 $\dots$ 第 $k+k-1$ 行有 $1$ 个表情。

可以连续发 $x$ 个表情，问能发出几行消息 ( 不足一行也算 )。
### 分析
[等差数列求和公式](https://baike.baidu.com/item/%E7%AD%89%E5%B7%AE%E6%95%B0%E5%88%97%E6%B1%82%E5%92%8C%E5%85%AC%E5%BC%8F/7527418?fr=aladdin)相信大家都会吧，前 $n$ 行表情的总和显然是单调递增的，就可以二分总和大于等于 $x$ 最早位置即为答案。

赛时分了答案在前 $k$ 行和在后 $k-1$ 分别二分，写的好像反而有点恶心了 QwQ。

``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) {
		long long k,x;
		scanf("%lld%lld",&k,&x);
		if(x>=(k+1)*k/2+k*(k-1)/2) cout<<k*2-1<<'\n';
		else {
			if(x==k*(k+1)/2) cout<<k<<'\n';
			else if(x<k*(k+1)/2) {
				//正常的二分
				int l=1,r=k,ans=1;
				while(l<=r) {
					int mid=(l+r)>>1;
					if((1+mid)*mid/2==x) {
						ans=mid;
						break;
					} else if((1+mid)*mid/2>x) {
						ans=mid;
						r=mid-1;
					} else l=mid+1;
				}
				cout<<ans<<'\n';
			} else {
				//答案在后半段的二分可能有些奇怪，因为l指向反而是消息中靠下的一个
				int l=1,r=k-1,ans=1;
				x-=k*(k+1)/2;
				while(l<=r) {
					int mid=(l+r)>>1;
					if((k-1+mid)*(k-mid)/2==x) {
						ans=mid;
						break;
					} else if((k-1+mid)*(k-mid)/2>x) {
						ans=mid;
						l=mid+1;
					} else r=mid-1;
				}
				cout<<k+k-ans<<'\n';
			}
		}
	}
	return 0;
}
```

---

## 作者：Lijunzhuo (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/CF1612C)  
这道题暴力是过不了的。我们可以用二分答案来解决，因为输出总数具有单调性。  
如何求出当输出 $l$ 行时的表情包总数？我们分类讨论。  
若 $l\le n$ 则表情包总数为
~~~cpp
t=dengcha(1,l);
~~~
若 $l>n$ 则表情包总数为
```cpp
dengcha(n-l,n-1)+dengcha(1,n);
```
其中，$\texttt{dengcha}(l,r)$ 表示 $\sum\limits_{i=l}^ri$。  
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,k,sum,ans,w,l,r,mid;
long long dengcha(long long l,long long r){return (l+r)*(r-l+1)/2;}
long long da(long long l)
{
    long long t=dengcha(1,l);
    if(l>n)
    {
    	l-=n;
		w=dengcha(n-l,n-1);
        t=dengcha(1,n)+w;
    }
	return t;
}
bool cmp(long long l)
{
	return da(l)<=k;
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&k);
		if(n*n<=k)
		{
			printf("%lld\n",2*n-1);
			continue;
		}
		l=0;
		r=2*n;
		while(l+1<r)
		{
			mid=(l+r)>>1;
			//printf("%lld,%lld %lld %lld\n",mid,da(mid),l,r);
			if(cmp(mid))
			{
				ans=mid;
				l=mid;
			}else r=mid;
		}
		printf("%lld\n",da(ans)<k?ans+1:ans);
	}
	return 0;
}

```
[通过记录](https://www.luogu.com.cn/record/133396905)

---

## 作者：jiangjiangQwQ (赞：1)

### 引入
根据数据范围的提示得知需要二分答案。
### 分析
题目要求输出最多发送信息的个数，所以答案区间为 $1 \leq ans \leq2 \times n-1 $，考虑二分答案。

在 **check** 函数里需要分类讨论，一种是 $l \leq n$ ，另一种是 $l > n$ 的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/t6xzmzyv.png)

如图所示，$l = 3$ 时字符总数为 6，$l = 4$ 时字符总数为 8。
很容易发现，当 $l \leq n$ 时直接等差数列求和，而 $l > n$ 则要分成两部分相加，最后判断字符总数符合要求即可。

注释版代码 :
```cpp
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
#define int long long
int T,n,k;
int C(int w){return (1+w)*w/2;}
bool check(int l){
    int t;
    if(l<=n) t=C(l);//l<=n的情况等差数列求和
    else{
        int cnt=(n-1)-(l-n),w=n*(n-1)/2-(1+cnt)*cnt/2;
        //w为下半部分的字符总数
        t=C(n)+w;//两部分相加
    }return t<k;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie();cout.tie();
    cin>>T;
    while(T--){
        cin>>n>>k;
        int l=1,r=2*n-1,f=0;
        //f变量用作判断如果所有信息都能发送的情况
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid)){
                l=mid+1;
                if(l>2*n-1){//所有信息都能发送
                    cout<<2*n-1<<'\n';
                    f=1;
                    break;
                }
            }
            else r=mid-1;
        }
        if(!f)
        cout<<l<<'\n';
    }
    return 0;
}
```



---

## 作者：DaiRuiChen007 (赞：1)

# $CF1612C\;Chat\,Ban$ 题解

## 题目描述

现在小A想发送一个 $2n-1$ 的符号三角形，具体如下：

第 $1$ 行，输出 $1$ 个符号；

第 $2$ ~ $n$ 行，每行比前一行多输出一个符号；

第 $n+1$ ~ $2n-1$ 行，每一行比前一行少输出一个符号。

可是，小A猖狂的行为引来了管理员的注意，如果小A再发完某条信息后，所发送的符号总数大于等于 $k$ ，小A将会被禁言。

现在请你求出在小A被禁言前最多能发送多少条信息。

## 数据范围

$1\leq n\leq 10^9$ ， $1\leq k\leq 10^{18}$

## 思路分析

由于数据范围过大，暴力显然会 TLE，

那么我们可以将小A发送的信息条数分为三种情况：

1. 小A能够发送的信息条数 $\leq n$ 条

2. 小A能够发送的信息条数 $<n$ 条且小于 $\leq2n-1$ 条

3. 小A能够成功发送整个符号三角形

依据上面的分类 ~~不难~~ 得出：

令 $f(x)\,=\,\Sigma^{x}_{i=1} i\,=\dfrac{x\times(x+1)}{2}$

- 对于第一种情况，直接查找小A能够发送的信息条数 $x$ ，此时 $x$ 满足 $f(n-1)<x\leq f(n)$ 。

- 对于第二种情况，反面考虑，查找管理员在他还差 $y$ 条信息没发送时将他禁言，此时 $y$ 满足 $f(n-1)-1\leq y<f(n)-1$ 。

- 对于第三种情况，直接输出 $2n-1$ 即可。

第三种情况可以直接输出。

对于第一或第二种情况，发现 $f$ 函数在区间 $\left[1,+\infty\right)$ 上是单调递增的，所以查询时可以采用二分法直接查找。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long //十年OI一场空，不开long long见祖宗 
using namespace std;
//查询满足n(n-1)/2<x<=n(n+1)/2的x 
inline bool judge1(int x,int l) {
	return x*(x-1)/2<l;
}
inline int query1(int x) {
    //普通二分模板
	int r=1e9+10,l=1;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(judge1(mid,x)) {
			l=mid+1;
		} else {
			r=mid-1;
		}
	}
	return r;
}

//查询满足n(n-1)/2<=x+1<n(n+!)/2
inline bool judge2(int x,int l) {
	return x*(x-1)/2<=l;
}
inline int query2(int x) {
    //普通二分模板
	int r=1e9+1,l=1;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(judge2(mid,x)) {
			l=mid+1;
		} else {
			r=mid-1;
		}
	}
	return r-1;
}

inline int solve(int k,int x) {
	int a=k*(k+1)/2;
	if(a==x) return k; //特判如果恰好能输出前n行的情况 
	if(k*k<=x) return k+k-1; //如果能够全部输出 
	if(a>x) {
		//第一种情况，直接查询 
		int q=query1(x);
		return q;
	} else {
		//第二种情况，反面考虑 
		int s=k*k;
		int q=query2(s-x);
		return k+k-1-q;
	}
}
signed main() {
	int t;
	scanf("%lld",&t);
	while(t--) {
		int k,x;
		scanf("%lld%lld",&k,&x);
		printf("%lld\n",solve(k,x));
	}
	return 0;
}
```



---

## 作者：断清秋 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1612C)

题意：给定一个 $2k-1$ 的数字三角形，第 $i$ 行的数代表第 $i$ 次可以发送的消息数，当你发出的消息数 $\ge x$ 时就不能再发了，求最多能发送多少次。

$k \le 10^9,x \le10^{18}$。直接暴力显然是 $O(k)$ 的。

设最多能发送次数为 $ans$，显然这玩意有单调性，然后暴力二分。

但是这个倒三角感觉不太好处理，考虑分类讨论。

如果 $ans \le k$，那么发送的消息总数就是 $\dfrac{mid(mid+1)}{2}$。

如果 $ans>k$，那么上半部分固定的贡献是 $\dfrac{k(k+1)}{2}$，下半部分有 $k-1$ 行，发送了 $mid-k$ 次，所以下半部分贡献为 $\dfrac{k(k-1)}{2}-\dfrac{(2k-mid)(2k-mid-1)}{2}$，再加上上半部分的 $\dfrac{k(k+1)}{2}$ 就 win 了。

剩下的就是大力二分了，没有什么实现难度。

时间复杂度 $O(t \log k)$。

---

## 作者：2012zxt (赞：0)

[CF1612C](https://www.luogu.com.cn/problem/CF1612C)

# 1.思路

我们可以先考虑一个暴力解法，就是每一次枚举最多输出信息的条数，并每一次验证。

这份代码很好写，但过不了，因为 $n\le10^9$，何况还有 $t$ 组数据呢？

然后我们考虑优化，我们可不可以把枚举条数转换为**二分**条数呢？

当然是可以的，并且时间复杂度还降了一个 $\log$，十分友好。

而在 $\operatorname{check}$ 函数中，我们分情况讨论，如果条数 $\le n$，那么就直接计算就可以了。

如果大了，就可以再加上从 $x-n$ 到 $n-1$ 的数的和就好了。

但这里有一个坑，根据题目描述，如果小A发完最后一条消息之后被禁言了，那最后一条消息也可以算作答案之一。

所以我们可以将 $x-1$，最后如果算出来的个数 $< x$，就说明最后还可以插入至少一条消息，也就是能行，不然就不行。

于是我们所有的情况都考虑完了，可以写代码了。

# 2.代码

```cpp
#include<bits/stdc++.h>
#define int long long//十年OI一场空，不开long long见祖宗
using namespace std;
int n,k,sum;
int getans(int x,int y){//使用函数快速调用计算
	return (x+y)*(y-x+1)/2;//标准公式
}
bool check(int x){
	x--;
	int tmp=sum;//tmp为这次发的总个数
	if(x<=n)//分类讨论
		tmp=getans(1,x);
	if(x>n){
		x-=n;
		tmp+=getans(n-x,n-1);//注意这里是n-1,本人错了好几遍
   }
	return tmp<k;
}
void help(){
	cin>>n>>k;
	sum=getans(1,n);
	int lt=0,rt=2*n;
	while(lt+1<rt){//求最大值的二分模板，无需改动
		int mid=(lt+rt)/2;
		if(check(mid))
			lt=mid;
		else rt=mid;
	}
	cout<<lt<<"\n";
	return ;
}
signed main(){
	int t;
	cin>>t;
	while(t--)
		help();
	return 0;
}
```

---

## 作者：jsisonx (赞：0)

# 简化题意
给定一个有 $2\times n-1$ 层由符号组成的金字塔形，求第几层时该层及以前的所有符号的和刚好大于等于 $k$。

# 分析
明显，可以考虑二分答案。对于某一次二分得到的层 $mid$，分类讨论其总符号数：

- 若 $mid<n$，则直接使用等差数列求和公式：$(1+mid)\times mid\div 2$。
- 否则分两部分：第一部分是从 $1$ 到 $n$ 的和，第二部分是从 $n-1$ 到 $n-1-(i-n)+1$ 的和，然后将两部分相加即可。

# 代码

```cpp
#include<iostream>
using namespace std;
long long t,n,k,l1,r1,l2,r2,sum1=0,sum2=0,ans=0;
long long ef(long long l,long long r){
	l1=r1=l2=sum1=sum2=0;
	long long mid;
	while(l<=r){
		mid=(r+l)>>1;
		if(mid>=n){
			sum1=(1+n)*n/2;
			l1=n-1;
			r1=mid-n;
			r2=l1-r1+1;
			sum2=(l1+r2)*r1/2;
			sum1+=sum2;
		}
		else{
			sum1=(1+mid)*mid/2;
		}
		if(sum1>=k){
			r=mid-1;
		}
		else{
			l=mid+1;
		}
	}
	return min(2*n-1,l);
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		cout<<ef(1,(2*n)-1)<<endl;
	}
	return 0;
}
```


---

