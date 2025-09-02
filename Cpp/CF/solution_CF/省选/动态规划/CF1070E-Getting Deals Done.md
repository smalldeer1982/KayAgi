# Getting Deals Done

## 题目描述

Polycarp有很多工作要做。最近他学会了一条新的时间管理技巧：“如果任务需要五分钟或更短时间，请立即执行”。Polycarp喜欢新技巧，但他不确定五分钟是最佳值。他认为这个值 d（分钟）应根据现有任务列表选择。

Polycarp有一份长度为 n 的要完成的任务清单。第 i 个任务有一个需要的时间Pi，即它确切地需要 Pi 分钟来完成。Polycarp从第一个到第 n 个逐个浏览任务。如果任务所需时间是 d 或更少，Polycarp立即开始执行任务。如果任务需要时间大于 d ，他不会去完成这个任务。列表中的任务的顺序是固定的了，所以，不容许你重新排序。当Polycarp阅读任务或跳过任务时，Polycarp不会花任何时间。

Polycarp有 T 分钟完成任务。但他不想一直工作。他决定在每做 m 个任务后休息一下。每次休息时间应该与完成这 m 个任务的时间相同。

例如，如果 N = 7，p = [3,1,4,1,5,9,2]，d = 3 和 m = 2 ，Polycarp的工作所需时间如下：

Polycarp读取第一个任务，其难度不大于 d ，并使用了 3 分钟（即分钟 1， 2 ，3 ）;

Polycarp读取第二项任务，其难度不大于 d ，并使用 1 分钟（即分钟 4 ）;

Polycarp注意到他已经完成了 m = 2 个任务并休息 3 + 1 = 4 分钟（即分钟 5,6,7,8 ）;

Polycarp读取第三项任务，其难度大于 d ，所以Polycarp不花任何时间跳过它;

Polycarp读取第四项任务，其难度不大于 d ，并适用于 1 1分钟（即分钟 9 ）;

Polycarp读取第五项和第六项任务，跳过他们两个。

Polycarp读取第七项任务，其难度不大于 d ，并使用 2 分钟（即分钟 10，11 ）;、

Polycarp注意到他又完成了 m = 2 个任务并休息 1 + 2 = 3分钟（即分钟 12,13,14 ）。

Polycarp会使用 T 分钟来完成任务。如果Polycarp启动任务但尚未完成任务，则该任务不会被视为已完成。

Polycarp认为在做完最后的任务之后可以接受比本来更短的休息时间，甚至根本没有休息——他的工作日结束了，他还有足够的时间休息。

请帮助Polycarp找到这样的价值 d ，使他能够在 T 分钟完成最多的任务。

## 样例 #1

### 输入

```
4
5 2 16
5 6 1 4 7
5 3 30
5 6 1 4 7
6 4 15
12 5 15 7 20 17
1 1 50
100
```

### 输出

```
3 5
4 7
2 10
0 25
```

## 样例 #2

### 输入

```
3
11 1 29
6 4 3 7 5 3 4 7 3 5 3
7 1 5
1 1 1 1 1 1 1
5 2 18
2 3 3 7 5
```

### 输出

```
4 3
3 1
4 5
```

# 题解

## 作者：SDNetFriend (赞：2)

## CF1070E Getting Deals Done 题解

（看到没有题解于是决定来~~水~~写一篇，这个题做的人好少）

### 题意这里不再赘述

[CF1070E Getting Deals Done](https://www.luogu.com.cn/problem/CF1070E)

### 分析

没有太多可分析的，感性理解一下能发现答案是关于 $d$ 的单峰函数，因为如果 $d$ 比较小那么限制答案的是任务数，即没有足够的任务去充满这些时间，当 $d$ 比较大的时候限制答案的是时间，并且 $d$ 越大就相当于加进来了一些时间更长的任务，会使答案单调不增。

然后我们可能会想求单峰函数极值什么的来三分，但似乎行不通。我们可以从这个答案函数的性质入手。

根据刚才对单峰的理解，我们发现 $d$ 一定可以分为两种，即被任务数限制的 $d$ 和被总时间限制的 $d$。这样看来我们意识到函数的峰一定出现在两种情况的交汇处。

于是我们就可以二分了，二分来查找最后一个被任务数限制的 $d$，每一次都模拟一次判断下是被什么限制了。找到位置之后再把下一个位置跑一下取个最大值就可以了。时间复杂度 $O(n\log n)$。

### 实现细节

因为找的是最后一个被任务数限制的位置，所以如果合法的话边界变化是 ```l=mid;```，那在二分时除二要上取整防止死循环。

因为 $T$ 很大所以记得开 long long。

### 贴代码

```cpp
#include <bits/stdc++.h>
#define lint long long
#define rint register int
using namespace std;
inline lint read(){
	char c;lint f=1,res=0;
	while(c=getchar(),!isdigit(c))if(c=='-')f*=-1;
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
const lint N=2e5+5;
lint T,n,m,t,a[N],b[N];
lint d,ans,_n;
//返回是否是件数不够 
inline bool solve(){
	ans=0;
	lint sum=0,lst=0,cnt=0;
	for(rint i=1;i<=n;++i){
		if(a[i]>d)continue;
		if(sum+a[i]>t)return false;
		++ans;sum+=a[i];
		lst+=a[i];++cnt;
		if(cnt==m)
			sum+=lst,cnt=lst=0;
	}
	return true;
}
int main(){
	T=read();
	while(T--){
		n=read();m=read();t=read();
		for(rint i=1;i<=n;++i)
			a[i]=b[i]=read();
		sort(b+1,b+1+n);
		_n=unique(b+1,b+1+n)-(b+1);
		lint l=1,r=_n,mid;
		while(l!=r){
			mid=(l+r+1)/2;d=b[mid];
			if(solve())l=mid;
			else r=mid-1;
		}
		d=b[l];solve();lint a0=ans,a1=0;
		if(l<_n)d=b[l+1],solve(),a1=ans;
		if(!a0&&!a1)printf("0 1\n");//注意特判这种情况 
		else if(a1<=a0)printf("%lld %lld\n",a0,b[l]);
		else printf("%lld %lld\n",a1,b[l+1]);
	}
	return 0;
}


```


---

## 作者：EternalLabyrinth (赞：0)

咋评的紫？

注意到你的答案趋势大概是先上升后下降的，于是你的答案是一个关于 $d$ 的单峰函数。然后你考虑二分那个临界值。（其实应该三分但我们有二分 check 的方法）。

考虑到你 $d$ 太大其实就是你选的太少，$d$ 太小你的时间不够。于是我们折中。

Key Observation: 考虑二分“时间不够”的临界点。那么他的下一个就是“选太少”。我们对这两种 $d$ 的取值取最大值即可。这不赘述。

二分 check 也非常简单，直接模拟题目在说什么即可，做完了。

---

