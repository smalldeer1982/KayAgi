# Dog Show

## 题目描述

下星期将会有一个由狗参加的综艺节目，你的狗有幸被选中了。自然的，你想使得你的狗获胜。

在这个节目中，狗的任务是吃掉尽可能多的狗粮。狗们的比赛是分开进行的，规则如下：

一开始，有$n$只盛放着狗粮的碗排列在一条直线上，狗一开始在起点$x=0$处，这些碗依次坐落在$x=1,x=2,...,x=n$处，标号依次为$1$至$n$。当节目开始后，狗将会立即向右跑向第一只碗。

碗里的狗粮并不是一开始就可以吃的，因为它们太烫了。在比赛开始后的第$t_i$秒，狗才能去吃第$i$只碗里的狗粮。

狗需要用$1$秒的时间来向右从$x$坐标移动到$x+1$坐标，狗不可以向左走。当狗遇到一碗狗粮时，有两种不同情况：

狗粮已经冷却：此时狗不需要花费任何时间来吃掉这碗狗粮。

狗粮还未冷却：此时狗可以在原地等候直到狗粮冷却，或者直接放弃这碗狗粮继续向右行动。

$T$秒后节目将结束，此时狗不能再移动或者吃狗粮。如果狗在$T$秒前早已达到第$n$只碗的右边，那么节目可以提前结束。

你的任务是最大化狗在$T$秒内吃掉的狗粮数量。

## 样例 #1

### 输入

```
3 5
1 5 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 2
1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
1 1
1
```

### 输出

```
0
```

# 题解

## 作者：Space_Gold_Trash (赞：5)

莫得人发题解啊，那我发一篇~~凑数~~吧

## 思路

我们对于每一个 $ti$（后面用$t$代替）进行处理,下面是处理过程:

很显然，如果在比赛结束还不能吃掉的话，直接放弃了

否则不吃白不吃

这是有人会问了，如果等待冷却的话，那么后面就可能吃不到

那么我们枚举$i$($1->n$)，表示狗最多走到第i个（必须）的话，不就解决了吗

代码

```
#include<bits/stdc++.h>
using namespace std;
int main( ){
	std::ios::sync_with_stdio(false);
	int n,T,i,t,ans=0;
	cin>>n>>T;
	priority_queue<int>q;
	for(i=1;i<=n;i++){
		while(!q.empty( )&&q.top( )>=T-i)q.pop( );
        //到不到的弹出
		cin>>t;
		if(max(t,i)<T)q.push(t-i);
        //到得了储存
		if(q.size( )>ans)
		ans=q.size( );
        //更新答案
	}
	cout<<ans<<endl;
}
```


---

## 作者：RandomLife (赞：4)

震惊，代码只有 $16$ 行！

### 正文

首先，对于一个狗粮，如果要等待，显然不管在哪里等待都一样（当然不能是在该狗粮后面），于是我们只在意等待时间。

对于第 $i$ 个狗粮，如果吃它，则需要等待的时间是 $\max(t_i-i,0)$，最多能等待的时间是 $T-i-1$。（$-1$ 是因为比赛结束时是不能吃狗粮的，所以要提前 $1$ 秒到达）

于是，我们枚举每个 $i\in[1,n]$，求出只能吃 $1\sim i$，并且必须吃 $i$ 的答案。显然，这个值就是：

$$
\sum_{j=1}^i1[\max(t_j-j,0)\leq T-i-1]
$$

由于 $T-i-1$ 是单调递减的，我们可以使用~~树状数组~~大根堆来维护。

具体的，对于每次枚举，先判断 $\max(t_i-i,0)\leq T-i-1$ 是否成立（因为要满足必须吃 $i$），然后将大根堆中所有大于 $T-i-1$ 的值弹出，再将 $\max(t_i-i,0)$ 压进大根堆。此时大根堆的大小就是当前的答案。对于所有答案取最大值即可。

### Code

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,t,a,ans=0;
priority_queue<int>q;
int main(){
	scanf("%d%d",&n,&t);
	for(int i=1;i<=n;++i){
		while(!q.empty()&&q.top()>t-i-1)q.pop();
		scanf("%d",&a);
		if(max(a,i)-i<=t-i-1)q.push(max(a,i)-i);
		ans=max(ans,(int)q.size());
	}
	printf("%d",ans);
	return 0;
}
```

**感谢观看！**

---

## 作者：__Cby___ (赞：2)

## 解题思路
枚举狗最终结束的碗的编号，模拟即可。  
同时采用贪心思路，能吃就吃。   
我们用优先队列维护到达每个碗分别要等几秒，每到达一个碗，就把在规定时间内等几秒都不能吃到的碗出队，然后统计狗最终能吃到的狗粮数的最大值就好了。  
## 代码
```cpp
#include <iostream>
#include <queue>
using namespace std;
int a[200025];
int main() {
	int n, T;
	cin >> n >> T;
	priority_queue<int> pq;
	for (int i = 1; i <= n; i++)cin >> a[i];
	int ma = 0;
	for (int i = 1; i <= n; i++) {
		while (!pq.empty() && pq.top() >= T - i)pq.pop();
		if (max(a[i], i) < T)pq.push(a[i] - i);
		ma = max((int)pq.size(), ma);
	}
	cout << ma << endl;
	return 0;
}
```

---

## 作者：xu222ux (赞：2)

~~我知道我的机会来了。~~

翻译题面上有了，我就不多说了。

## 大致思路

我们用优先队列存储目前哪些狗粮能吃：

在时间加一是，我就加看一盆狗粮。如果狗粮能吃，就放入队列，最后统计一下队列中狗盆个数，最后比个最大值。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t;
int a[200005];
signed main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++)cin>>a[i];
	priority_queue<int>pq;
	int ans=0;
	for(int i=1;i<=n;i++){
		while(!pq.empty()&&pq.top()>=t-i)pq.pop();
       	if(a[i]<t&&i<t)pq.push(a[i]-i);
		ans=max(ans,(long long)pq.size());
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：DHeasy (赞：2)

### 我的解法

对于第 $i$ 种狗粮，到这里的时间为 $i$。

所以，如果 $t_i\le i$，则刚到这盆狗粮时就可以吃了，反之，要等待 $t_i-i$ 的时间。  
每次选择狗粮前，要先把一定到不了的狗粮去掉，为了方便，我使用优先队列（$\text{priority\_queue}$）来计入吃每一盆狗粮的时间（不包含过去的时间）。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<int>dog;
int n,T,ans;
int main(){
	scanf("%d%d",&n,&T);
	for(int i=1;i<=n;i++){
		while(!dog.empty()&&dog.top()>=T-i)
			dog.pop();
		int a;
		scanf("%d",&a);
		if(max(a,i)<T)
			dog.push(max(a-i,0));
		ans=max(ans,int(dog.size()));
	}
	return !printf("%d",ans);
}
```
建议自己写写，不要复制粘贴呀~

---

## 作者：zhangjyoi (赞：1)

## CF847D Dog Show 题解
### 题目大意
你的狗要演出，有 $N$ 碗狗粮，$T$ 的时间，每碗狗粮 $t_i$ 秒后冷却。狗只能向右移动。求你的狗最多吃到几碗狗粮。
## 思路
我们枚举每碗狗粮，若无法吃掉，将耗时最多的狗粮一个一个淘汰，直到这碗狗粮可以吃。这可以用一个优先队列实现（~~小蒟蒻用的是 priority_queue 代替~~），不懂优先队列的可以参考[这](https://blog.csdn.net/weixin_52192405/article/details/124593027)。每次队列里都只有可以吃的狗粮，用队列的元素数量更新答案就可以了。
## ACode
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,T,ans;
long long a;
int main(){
	scanf("%lld%lld",&n,&T);
	priority_queue<long long>q;
	for(long long i=1;i<=n;i++){
		scanf("%lld",&a);
		while(!q.empty()&&q.top()>=T-i)q.pop();
		if(max(a,i)<T)q.push(a-i);
		if(q.size()>ans)ans=q.size();
	}
	printf("%lld",ans);
	return 0;
}
```
### 注意事项
此题不开 long long 见祖宗！！！

---

## 作者：Ag2WO4 (赞：0)

看着没人写 $O(n)$ 的写法，我自己来一发吧。

思路：考虑到达第一个狗粮后等待然后直接冲过去（在任意等长等待序列里一定最优），如果 $T$ 很富裕不妨多等一会，枚举等待时间算能吃到的狗粮数，前缀和优化。
#### 代码
```python
n,t=map(int,input().split());t-=1;a=list(map(int,input().split()));from collections import*
for i in range(n):a[i]=max(a[i]+~i,0)
if t>n:
    for i in range(n):a[i]=max(a[i]-t+n,0)
    t=n
b=Counter(a[:t]);c=d=i=0
while t:
    c+=b[i];d=max(d,c)
    if a[t-1]>n:b[a[t-1]]-=1
    else:c-=1
    i+=1;t-=1
print(d)
```

---

## 作者：Expert_Dreamer (赞：0)

~~因为咕值才写的题解~~

## 解题思路
枚举每一个“狗粮”的编号，那么在规定时间内不能吃的就没用，可以直接扔掉，不然就可以放进优先队列（这实际上是一种贪心思想），然后每次更新最大值。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,x,ans;
priority_queue<int>q;
int main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		while(!q.empty()&&q.top()>=t-i) q.pop();//扔掉的。
		cin>>x;
		if(max(x,i)<t) q.push(x-i);//放入的。
		if(q.size()>ans) ans=q.size();//手写max。
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：wei2013 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF847D)

## 思路：
因为狗每次走一步只能走一个单位，而每秒只能走一步，所以走到第 $i$ 个位置上的狗粮，需要消耗 $i$ 点体力。

所以如果 $t_i \le i$ 的话，狗在走到第 $i$ 个狗粮时，狗粮一定会是冷却的，可以直接吃，如果 $t_i > i$，狗就要等待 $t_i-i$ 秒，当然无意义的等待会使后面的狗粮有可能吃不到，导致非最优解，有一些一定到不了的狗粮肯定是要排除的，要排除无法到达的狗粮很简单，只用判断剩余时间是否足够即可，所以可以用优先队列来存储每袋狗粮所需的时间（仅那一个），从头到尾扫一遍，用 $ans$ 作最终答案，取每次序列的元素最大值即可。
## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue <int> que;
int t[200005];
int main( ){
	int n,T,ans=0;
	cin>>n>>T;
	for(int i=1;i<=n;i++){
		cin>>t[i]; 
	}
	for(int i=1;i<=n;i++){
		while(!que.empty() && que.top()>=T-i){
			que.pop();
		}
		if(max(t[i],i)<T){
			que.push(t[i]-i);
		}
		ans=max(ans,int(que.size()));
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lndjy (赞：0)

~~为了咕值~~，来补一篇题解。

### 解法

用一个优先队列来表示每个狗粮是否被吃，选择任意时刻能吃的数量的最大值即可。

那么具体怎么操作呢？

1. 对于每个位置，把不能吃掉的狗粮踢出去。
1. 如果这袋狗粮能吃，就放进去。
1. 任意时刻，优先队列里的狗粮都是能吃的，对于每种情况取最大size即可。

代码含注释：
```cpp
#include<iostream>
#include<queue>
using namespace std;
int a[200005];
int main()
{
	int n,t;
	cin>>n>>t;
	for(int i=1;i<=n;i++)
	cin>>a[i];
	priority_queue<int> q;//优先队列
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		while(!q.empty()&&q.top()>=t-i) q.pop();//对于每个位置，把不能吃掉的狗粮踢出去。
       		if(a[i]<t&&i<t)
		q.push(a[i]-i);//如果这袋狗粮能吃，就放进去。
		ans=max(ans,int(q.size()));//对于每种情况取最大size
	}
	cout<<ans;
	return 0;
}
```


---

