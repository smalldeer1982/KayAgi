# Fishingprince Plays With Array

## 题目描述

Fishingprince is playing with an array $ [a_1,a_2,\dots,a_n] $ . He also has a magic number $ m $ .

He can do the following two operations on it:

- Select $ 1\le i\le n $ such that $ a_i $ is divisible by $ m $ (that is, there exists an integer $ t $ such that $ m \cdot t = a_i $ ). Replace $ a_i $ with  $ m $ copies of $ \frac{a_i}{m} $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[2,3] $ and $ i=1 $ , $ a $ changes into $ [1,1,3] $ .
- Select $ 1\le i\le n-m+1 $ such that $ a_i=a_{i+1}=\dots=a_{i+m-1} $ . Replace these $ m $ elements with a single $ m \cdot a_i $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[3,2,2,3] $ and $ i=2 $ , $ a $ changes into $ [3,4,3] $ .

Note that the array length might change during the process. The value of $ n $ above is defined as the current length of the array (might differ from the $ n $ in the input).

Fishingprince has another array $ [b_1,b_2,\dots,b_k] $ . Please determine if he can turn $ a $ into $ b $ using any number (possibly zero) of operations.

## 说明/提示

In the first test case of the sample, we can do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},4,2]\to [1,\color{red}{4},4,2] $ .

In the second testcase of the sample, we can:

- do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},8,2,2]\to [1,\color{red}{4},8,2,2] $ .
- do the second operation with $ i=4 $ : $ [1,4,8,\color{red}{2,2}]\to [1,4,8,\color{red}{4}] $ .
- do the first operation with $ i=3 $ : $ [1,4,\color{red}{8},4]\to [1,4,\color{red}{4,4},4] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{4,4},4,4]\to [1,\color{red}{8},4,4] $ .
- do the second operation with $ i=3 $ : $ [1,8,\color{red}{4,4}]\to [1,8,\color{red}{8}] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{8,8}]\to [1,\color{red}{16}] $ .

## 样例 #1

### 输入

```
5
5 2
1 2 2 4 2
4
1 4 4 2
6 2
1 2 2 8 2 2
2
1 16
8 3
3 3 3 3 3 3 3 3
4
6 6 6 6
8 3
3 9 6 3 12 12 36 12
16
9 3 2 2 2 3 4 12 4 12 4 12 4 12 4 4
8 3
3 9 6 3 12 12 36 12
7
12 2 4 3 4 12 56```

### 输出

```
Yes
Yes
No
Yes
No```

# 题解

## 作者：lenlen (赞：10)

一道比较妙的构造题。

### Problem

题目大意：给定两个序列和一个数 $m$，你可以将一个 $m$ 的倍数 $a$ 拆成 $m$ 个 $a/m$，或者将 $m$ 个相同的数 $a$ 合成一个 $am$，问序列 $a$ 能否经过操作后变成 $b$ 序列。

数据范围： $\sum n \leq 2 \times 10^5,t \leq 10^4,a_i,b_i,m \leq 10^9$。

### Solution

首先我们可以发现，这两个操作本质是互逆的相反的操作，而且并不改变序列本身每个数的和，所以第一个判断就显而易见了：若两个序列和不相同，那么一定无法构造。

第二点，我们研究一下可以发现，两个序列要能构造也就等价于两个序列全部尽可能执行第一个操作之后的数组相等。证明显然，$b$ 数组经过第一个操作显然也就等价于 $a$ 数组经过第一个操作之后再进行第二个操作。

所以我们可以将两个数组能拆就拆，然后判断拆出来的数的数量和大小是否相等。但是如果两个数组都拆并且存下来比较的话，会发现数组不够大，因为 $a_i,b_i \leq 10^9$，所以我们可以将 $a$ 先拆开扔进双端队列里面，在一步一步的拆 $b$ 看满不满足要求，比较即可。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7232;
int t,n,m;
int nn,a[N],b[N];
long long s1,s2;
struct hl{
    int d,sum;
}tmp;
int main()
{
	scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);s1=0;s2=0;
        deque <hl> q;
        for(int i=1;i<=n;i++) 
        {
            scanf("%d",&a[i]);s1+=a[i];
            int k=1;
            while(a[i]%m==0) a[i]/=m,k*=m;
            q.push_back((hl){a[i],k});//先将a  按顺序  扔进双端队列
        }
        scanf("%d",&nn);
        for(int i=1;i<=nn;i++) scanf("%d",&b[i]),s2+=b[i];
        int flag=0;
        if(s1!=s2) //直接不合法
        {
            printf("No\n");
            continue;
        }
        for(int i=1;i<=nn&&!flag;i++)
        {
            int k=1;
            while(b[i]%m==0) b[i]/=m,k*=m;//一个一个判断b
            while(k)
            {
                if(q.empty())
                {
                    flag=1;
                    break;
                }
                tmp=q.front();q.pop_front();
                if(tmp.d!=b[i]) //分解出的类型不同
                {
                    flag=1;
                    break;
                }
                if(tmp.sum<=k) k-=tmp.sum;//数量不够，继续拿数出来
                else
                {
                    q.push_front((hl){tmp.d,tmp.sum-k});//注意，剩下的因为要按原来顺序插入，所以是插入队头
                    k=0;
                }
            }
        }
        if(flag) printf("No\n");
        else printf("Yes\n");
    }
}
```


---

## 作者：Avocadooo (赞：5)

### 1.题目思路

题目提及**特殊限定的拆分与合并**，且要我们判断**可行性**。

为了说明方便，我们称拆分操作为 $ split $，合并操作为 $ merge $。

首先我们得到一个很显然的发现：

> $ split $ 和 $ merge $ 操作是**恰好相反的**。

我们举个例子来进行说明：

对于 $ m=7 $，原序列如下：

$$ 7\;7\;7\;7\;7\;7\;7 $$

$$ split(1):1\;1\;1\;1\;1\;1\;1\;7\;7\;7\;7\;7\;7 $$

$$ merge(1,7):7\;7\;7\;7\;7\;7\;7 $$

可以发现，经过一次 $ split $ 和对被拆开的数进行一次 $ merge $ 之后，序列相较原序列未发生变化。同样先 $ merge $ 再 $ split $ 也可以达到相同的效果。

那么若有一个序列 $ A $ 和一个序列 $ B $，判断 $ A $ 能不能变为 $ B $ 也就相当于判断 $ B $ 能不能变为 $ A $，这比较容易理解。

那么既然如此，我们建立两个新的序列 $ A',B' $，且 $ A',B' $ 分别是由 $ A,B $ 不停 $ split $ 直到不可以继续 $ split $ 为止。显然对于 $ A' $ 序列有如下性质，可以感性理解：

> 由于 $ split $ **只对单点操作且不对其他位置造成影响的确定性**，故一个序列 $ A $ 有其**唯一对应的** $ A' $。（$ A' $ 之所以不定义为反复 $ merge $ 得到的序列也就是因为其不存在和 $ split $ 一样的确定性，通俗一点，就是我不清楚到底 $ merge $ 哪一个区间）

根据之前的发现，$ A',B' $ 分别可以通过**一定方式的** $ merge $ 得到 $ A,B $。

那么在 $ A' \not= B' $ 的情况下，由于唯一对应的性质，$ A' $ 不能通过某种方式 $ merge $ 得到 $ B $。此时 $ B' $ 同理。

反之 $ A'=B' $，$ A $ 能 $ split $ 得到 $ A' $，$ A' $ 能合并得到 $ B $,那么就满足了 $ A $ 可以变化为 $ B $。

问题转化为判断 $ A'=B' $。

那么直接暴力拆分后按位对比？仔细考虑一下，空间和时间显然都不能承受。

但由于拆分出来的数大多都是相同的，我们可以利用结构体去重进行比对即可。

### 2.细节内容

拆分？怎么拆？去重？怎么去？

对于序列：

$$ A=\{a_1,a_2,a_3,\dots,a_n\} $$

我们可以把其写作如下形式:

$$ A=\{f_1\cdot m^{t_1},f_2\cdot m^{t_2},f_3\cdot m^{t_3},\dots,f_n\cdot m^{t_n}\} (\forall 1 \le i \le n,f_i \in N^+,m \nmid f_i) $$

显然发现在 $ A' $ 序列中，$ i $ 从 $ 1 $ 至  $ n $，会依次有 $ m^{t_i} $ 个 $ f_i $ 出现。用结构体来存储，就相当于对原序列进行了去重。

接着发现对于相邻的 $ f_i $ 与 $ f_{i+1} $，若 $ f_i=f_{i+1} $，则等价于在 $ A' $ 序列中存在着 $ m^{t_i}+m^{t_{i+1}} $ 个 $ f_i $ 。可以将其中一些结构体合并便于我们判断。

**另外注意，$ \sum m^{t_i} $ 可能十分巨大，需要开** ```long long```。

细节大概就是这些，不再赘述。如果还有疑问可以参考代码加以理解。

### 3.代码

```cpp
#include<map>
#include<cmath>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=300005;
typedef long long ll;
using namespace std;
struct NUM
{
	int rt;
	ll cnt;
}a[N],b[N];
int n,m,f,cnt,a2;
signed main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		cnt=0,f=0,a2=0;
		scanf("%d %d",&n,&m);
		ll sum=0;
		for(int i=1,x,y;i<=n;i++)
		{
			scanf("%d",&x);
			sum+=x,y=1;
			while(x%m==0) x/=m,y*=m;
			if(!cnt || x!=a[cnt].rt) a[++cnt].rt=x,a[cnt].cnt=y;
			else if(x==a[cnt].rt) a[cnt].cnt+=y;
		}
		int k;
		scanf("%d",&k);
		for(int i=1,x,y;i<=k;i++)
		{
			scanf("%d",&x);
			sum-=x,y=1;
			while(x%m==0) x/=m,y*=m;
			if(!a2 || x!=b[a2].rt) b[++a2].rt=x,b[a2].cnt=y;
			else if(x==b[a2].rt) b[a2].cnt+=y;
		}
		if(sum || cnt!=a2)
		{
			puts("NO");
			continue;
		}
		for(int i=1;i<=a2;i++)
		{
			if(a[i].rt!=b[i].rt || a[i].cnt!=b[i].cnt)
			{
				f=1;
				break;
			}
		}
		if(f) puts("NO");
		else puts("YES");
	}
	return 0;
}
```

---

## 作者：SoyTony (赞：2)

# 题意
给定两个数列 $a$ 和 $b$，对数列 $a$ 进行两种操作。

操作一：将数列中一个 $m$ 的倍数拆成 $m$ 份，不改变相对位置放入数列。

操作二：将数列中连续 $m$ 个相同的数合并成一个数。

问经过若干次操作后能否使 $a$ 变成 $b$。
# 题解
发现两个操作一拆一合，其实是相反的，于是将 $a$ 合上向 $b$ 靠拢，不如看成拆 $b$。

只需要把 $a$ 和 $b$ 分别完全拆开，判断是否相同即可。

当然，因为拆开后数据个数可能很大，需要用 vector 压缩一下相邻的相同元素。

---

## 作者：jiangtaizhe001 (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16420062.html)  

[题目传送门](http://codeforces.com/problemset/problem/1696/C)  
### 题目大意
给定一个长度为 $n$ 的数组 $a$ 、一个长度为 $k$ 的数组 $b$ 和一个数字 $m$，现在对数组 $a$ 进行以下操作：
- 选择数组 $a$ 中一个 $m$ 的倍数 $a_i$ 替换成 $m$ 个 $\dfrac{a_i}{m}$
- 选择数组 $a$ 中 $m$ 个相同的数字 $a_i,a_{i+1},\dots,a_{i+m-1}$ 替换成 $m\cdot a_i$  

请问能否把数组 $a$ 变成数组 $b$。  
数据范围：$1\le n,k\le 5\times 10^4$，$2\le m\le 10^9$，$1\le a_i,b_i\le 10^9$，$\sum n+k\le 2\times 10^5$。  
### 题目解析
发现两个操作是互逆的，所以我们判断是否可以把数组 $a$ 和数组 $b$ 通过这两个操作来转化成同一个数组。  
所以我们只需要把两个数组中所有 $m$ 的倍数都拆开，然后判断两个数组是否相同即可。  
显然可能会拆出很多项，所以需要开一个结构体来表示数组，里面的两个变量分别代表这个数字和它的重复次数。

```cpp
int n,m,k,a[maxn],b[maxn],len1,len2; ll sum1,sum2;
struct JTZ{ int s; ll num; }tmpa[maxn],tmpb[maxn];
int solve(int arr[],JTZ res[],int len){
	int nlen=0,tmp,i; ll cnt;
	for(i=1;i<=len;i++){
		cnt=1; tmp=arr[i];
		while(tmp%m==0) tmp/=m,cnt*=m;
		if(nlen==0||res[nlen].s!=tmp) nlen++,res[nlen].num=cnt,res[nlen].s=tmp;
		else res[nlen].num+=cnt;
	} return nlen;
}
void work(){
	n=read(); m=read(); int i;
	for(i=1;i<=n;i++) a[i]=read(); k=read(); for(i=1;i<=k;i++) b[i]=read();
	len1=solve(a,tmpa,n); len2=solve(b,tmpb,k);
	if(len1!=len2){ puts("No"); return; }
	for(i=1;i<=len1;i++) if(tmpa[i].num!=tmpb[i].num||tmpa[i].s!=tmpb[i].s){ puts("No"); return; }
	puts("Yes"); return;
}
```

---

## 作者：JS_TZ_ZHR (赞：1)

## 题解：

容易发现两个操作本质上是互逆的，因此只要将 $a$ 和 $b$ 中的所有元素拆开再比较是否相同即可。

注意最后的数字总数可能过大，记录每个数字拆开来后的大小和数量即可。

## 代码：

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define int long long
using namespace std;
int T,n,m,k,a[N],b[N],p1,p2,sum1,sum2;
struct node{
	int num,sum;
};
stack<node>s;
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>m;
		bool flag=1; 
		sum1=sum2=0;
		while(!s.empty())s.pop();
		for(int i=1;i<=n;i++){
			cin>>a[i],sum1+=a[i];
			int tmp=1;
			while(a[i]%m==0)a[i]/=m,tmp*=m;
			s.push((node){
				a[i],tmp
			});
		}
		cin>>k;
		for(int i=1;i<=k;i++)cin>>b[i],sum2+=b[i];
		if(sum1!=sum2){
			puts("No");
			continue;
		}
		for(int i=k;i>=1;i--){
			int tmp=1;
			while(b[i]%m==0)b[i]/=m,tmp*=m;
			while(tmp){
				if(s.empty()||b[i]!=s.top().num){
					flag=0;
					break;
				}
				if(tmp>=s.top().sum)tmp-=s.top().sum,s.pop();
				else {
					s.top().sum-=tmp;
					tmp=0;
				}
			}
			if(!flag)break;
		}
		puts(flag?"Yes":"No");
	}
} 
```


---

