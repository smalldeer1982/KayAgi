# Cram Time

## 题目描述

现在你有两天的时间备考，两天各有$a$小时,$b$小时。

每天可以看若干份笔记。编号为$k$的笔记需要看$k$小时(请不要忽略，最后输出有用)。为了考得更好，你需要最大化看的笔记份数。请你求出最多能看多少份笔记。

注意，看过的笔记需要都不相同。即使是不在同一天看的。

## 样例 #1

### 输入

```
3 3
```

### 输出

```
1
3 
2
2 1 ```

## 样例 #2

### 输入

```
9 12
```

### 输出

```
2
3 6
4
1 2 4 5
```

# 题解

## 作者：如履薄冰 (赞：4)

# 思路
不难发现，我们要想在最短的时间内读完尽可能多的资料，就尽可能读花费时长更小的。我们假设我们读的花费时长最长的资料需要读 $lim$ 小时，则 $ \sum_{i=1}^{lim} i \le a + b$。经过思考，我们可以发现只有将花费时长最长的几篇资料都在第一天看完，你才能看更多的资料。我们可以通过枚举找出这个 $lim$，然后再从大到小把第 $1$ 天能看的最多资料枚举出来，用一个队列维护第 $1$ 天应该看的资料。剩余的就是第 $2$ 天要看的资料。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,i,sum,lim;
bool lock[1100000];
queue<int> data;
int main(){
	ios::sync_with_stdio(false);
	cin>>a>>b; 
	while(1){
		i++;
		sum+=i;
		if(sum>a+b){
			lim=i-1;
			break;
		}
	}
	for(i=lim;i>=1;i--){
		if(a>=i){
			a-=i;
			data.push(i);
			lock[i]=true;
		}
	}
	cout<<data.size()<<endl;
	while(!data.empty()){
		cout<<data.front()<<" ";
		data.pop();
	}
	cout<<endl;
	for(int i=1;i<=lim;i++){
		if(!lock[i]){
			cout<<i<<" ";
		}
	}
	return 0;
}
```

---

## 作者：Piwry (赞：3)

## 解析

不难想到看编号尽量小的笔记会更优

设 $k$ 为最大的满足 $\sum\limits_{i=1}^{limit} i\leq a+b$ 的 $limit$；显然我们最多也只能看 $1$ ~ $k$ 的笔记

接着我们有一个结论：对于任意正整数 $m$，如果有整数 $1\leq x\leq \sum\limits_{i=1}^m i$，我们一定能用若干个不重复的 $1\leq y\leq m$ 相加得到 $x$

证明可以考虑归纳

首先 $m=1$ 时显然成立。设 $m=t$ 时该结论成立，我们需要证明 $m=t+1$ 时该结论仍成立。对于 $x\leq \sum\limits_{i=1}^t i$，显然成立（用 $1\leq y\leq t$ 的数字就行了，即因为 $m=t$ 时该结论成立）；对于 $\sum\limits_{i=1}^t i < x\leq \sum\limits_{i=1}^{t+1} i$，我们只需将 $x$ 减掉 $t+1$，接下来就是刚才的情况了

于是我们只需先找到 $k$，再模拟拼出其中一个，这里就拼 $a$；又由于 $\sum\limits_{i=1}^k i\leq a+b$，于是剩下的数字的和一定小于 $b$，全部放到第二天读即可

注意考虑证明的过程，模拟枚举数字时需要**从大到小**（具体可见代码）

## CODE

```cpp
#include <cstdio>

const int MAXN =1e5;

int arr[MAXN], tot;
bool used[MAXN];

int main(){
	int a, b;
	scanf("%d%d", &a, &b);
	int sum =0;
	if(a+b >= 1)
		for(int i =1; ; ++i){
			arr[tot++] =i;
			sum +=i;
			if(sum+i+1 > a+b)
				break;
		}
	int sum2 =0, cnt_2 =0;
	for(int i =tot-1; i >= 0; --i){/*一定能正好凑出一个数*/
		if(sum2+arr[i] <= a)
			sum2 +=arr[i], used[i] =1, ++cnt_2;
	}
	printf("%d\n", cnt_2);
	for(int i =0; i < tot; ++i)
		if(used[i])
			printf("%d ", arr[i]);
	printf("\n%d\n", tot-cnt_2);
	for(int i =0; i < tot; ++i)
		if(!used[i])
			printf("%d ", arr[i]);
}
```

---

## 作者：guoxinda (赞：2)

## 思路
我们假设一个 $c$ 数组，长度为 $n$。且 $n$ 为 $\sum_{i = 1}^{n}i \le a + b $ 的最大值。则：\
$c_n=a+b-\sum_{i=1}^{n}i+n$。其余为：$c_x=x$。\
则 $a$ 一定能由数组中若干个不同的数相加而成。\
$b$ 则由剩下的若干个不同的数相加而成。\
$n$ 最大为 $\sum_{i=1}^{n}i+n\ge a+b$ 的最小值，即 $\frac{n(n+1)}{2}+n\ge a+b$ 的最小值，$n<10^5$。
## 要注意的点
- $a$ 时间最好要倒着减，（从大减到小）而且还要判断现在的时间够不够 $c_x$。~不然时间会用不完，不是最好结果~
- $a$ 用过的要标记一下，第二轮没标记过的直接输出（$c$ 数组和为 $a+b$）。
## code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b,ans,num,s,c[100001];//c数组最大为[n(n+1)]/2<1^5 
bool v[100001];//标记第一轮 
vector<int>a1;
int main(){
	cin>>a>>b;
	s=a+b;
	for(int i=1;i<=s;i++){
		if(2*i+1>s){
			c[++num]=s;
			break;
		}
		c[++num]=i;
		s-=i;
	}
	for(int i=num;i>=1;i--){//一定要倒过来才能保证刚好用完a时间 
		if(c[i]<=a){
			a-=c[i];
			a1.push_back(c[i]);
			v[i]=1;
		}
		if(!a)break;
	}
	cout<<a1.size()<<endl;
	for(int i=0;i<a1.size();i++){
		cout<<a1[i]<<" ";
	}
	cout<<endl<<num-a1.size()<<endl;//剩下的
	for(int i=1;i<=num;i++){
		if(!v[i]){
			cout<<c[i]<<" ";
		}
	}
	return 0;
} 
```

---

## 作者：StudyingFather (赞：2)

显然，最优的方案是看 $ 1 \ldots k $ 这几份笔记。（其中 $ k $ 的值应该是满足 $ k(k-1)/2 \leq a+b $ 的最大整数解）

接下来就是分配时间了，我们的原则是：让第一天的时间利用最多。

我们先计算出 $ k $ ，然后将耗时最多的几份笔记放入第一天的复习计划，并使得第一天的耗时恰好为 $ a $ 。

把剩下的笔记放入第二天的复习计划即可。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int maxt,vis[80005],ans,tot;
int main()
{
 int a,b;
 scanf("%d%d",&a,&b);
 if(a==0&&b==0)
 {
  printf("0\n\n0\n\n");//其实这里是否输出空行并不会产生太大影响
  return 0;
 } 
 for(int i=1;;i++)
 {
  tot+=i;
  if(tot>a+b)
  {
   maxt=i-1; 
   break;
  }
 }
 tot=0;
 for(int i=maxt;i>=1;i--)
 {
  if(i+tot>=a)
  {
   if(a==0)
   {
    printf("0\n");
    ans=maxt;
    break;
   }
   printf("%d\n",min(a-tot,maxt)?maxt-i+1:maxt-i);
   for(int j=i+1;j<=maxt;j++)
    printf("%d ",j),vis[j]=1;
   if(min(a-tot,maxt))printf("%d\n",min(a-tot,maxt));
   else puts("");
   vis[min(a-tot,maxt)]=1;
   ans=min(a-tot,maxt)?i-1:i;
   break;
  }
  tot+=i;
  if(i==1)
  {
   printf("%d\n",maxt);
   for(int i=1;i<=maxt;i++)
    printf("%d ",i);
   puts("");
  }
 }
 printf("%d\n",ans);
 if(ans==0)return 0;
 for(int i=1;i<=maxt;i++)
  if(!vis[i])printf("%d ",i);
 return 0;
}
```

---

## 作者：浮光掠影 (赞：1)

### 思路：

贪心，能用小的不用大的。

满足 $\sum_{i=1}^{n} i \leq a + b$，最大的 $i$，一定可以用完  $1\sim n$。

对于 $a$，直接从大到小枚举是否可以看，剩下的给 $b$。


### Code


```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
LL a, b;
int flag[1000010];

int main(){
	scanf("%lld%lld", &a, &b);
	LL x = 1, s = 0;
	while (s + x <= a + b) s += x++;
	--x;
	LL ans = 0, y = x;
	for (LL i = x; i > 0; i = min(a, i - 1))
		if (a >= i) a -= i, flag[i] = 1, ++ans;
	printf("%d\n", ans);
	if (ans > 0){
		for (int i = 1; i <= y; ++i) if (flag[i]) printf("%d ", i);
		puts("");
	}
	printf("%lld\n", y - ans);
	if (y - ans > 0) for (int i = 1; i <= y; ++i) if (!flag[i]) printf("%d ", i);
	return 0;
}

```

---

## 作者：ballpoint_pen (赞：0)

一个显然的贪心是：最后看的笔记肯定是尽量看编号小的。所以我们求出一个最大的 $m$ 使得 $(\sum_{i=1}^{m}i)\le a+b$。这样的 $m$ 不会太大，直接暴力枚举即可。

接着我们考虑怎么分配。我们倒序扫一遍，如果第一天还能放下就放，否则就放第二天。容易证明这样一定刚好可以凑出 $a$，又因为 $(\sum_{i=1}^{m}i)\le a+b$，所以剩下的和肯定也不超过 $b$，这样就做完了。

---

