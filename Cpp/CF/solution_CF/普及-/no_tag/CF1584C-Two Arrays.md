# Two Arrays

## 题目描述

You are given two arrays of integers $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ .

Let's define a transformation of the array $ a $ :

1. Choose any non-negative integer $ k $ such that $ 0 \le k \le n $ .
2. Choose $ k $ distinct array indices $ 1 \le i_1 < i_2 < \ldots < i_k \le n $ .
3. Add $ 1 $ to each of $ a_{i_1}, a_{i_2}, \ldots, a_{i_k} $ , all other elements of array $ a $ remain unchanged.
4. Permute the elements of array $ a $ in any order.

Is it possible to perform some transformation of the array $ a $ exactly once, so that the resulting array is equal to $ b $ ?

## 说明/提示

In the first test case, we can make the following transformation:

- Choose $ k = 2 $ .
- Choose $ i_1 = 1 $ , $ i_2 = 2 $ .
- Add $ 1 $ to $ a_1 $ and $ a_2 $ . The resulting array is $ [0, 2, 0] $ .
- Swap the elements on the second and third positions.

In the second test case there is no suitable transformation.

In the third test case we choose $ k = 0 $ and do not change the order of elements.

## 样例 #1

### 输入

```
3
3
-1 1 0
0 0 2
1
0
2
5
1 2 3 4 5
1 2 3 4 5```

### 输出

```
YES
NO
YES```

# 题解

## 作者：Morgen_Kornblume (赞：2)

# CF1584C Two Arrays 解题报告

先吐槽一句：本题赛时 pretest :

**太弱啦！**

赛时没有锁题，但是被 Hack 了嘤嘤嘤，好奇怪！

进入正题，关于题意就不多废话，赛后重做的时候收到了 @DYF_dyf 的上帝神启：这不是网络流模板题吗？

注：以下所有边容量均为 $1$ 。

我们这样做，建一对源点汇点，建两倍的中间点，表示平移后的所有数值，先把所有数加一个大数平移到正整数区间，然后对于每个在 $a$ 中出现的数值 $a_i$ ，从源点向点 $a_i$ 连一条边，从 $a_i$ 向点 $2*a_i$ 和点 $2*(a_i+1)$ 分别连一条边，表示对其使用操作 $+1$ 与否 ；对于每个在 $b$ 中出现的数值，从点  $2 * b_i$ 向汇点连一条边。

然后就可以愉快地跑 Dinic 了，只要检验最后的流量是不是 $n$ 就可以判断 `YES` 或 `NO` 了。

因为数据范围很小，所以没有太大问题，随便跑。

什么叫做牛刀杀鸡啊？

参考代码：

```
const int maxn=533,maxm=1010;

struct edge{
	int u,v,cap;
};

struct dinic{
	int tp,s,t,dis[maxn],cur[maxn],que[maxn];
	vector<edge>e;vector<int>v[maxn];
	
	void AddEdge(int x,int y,int flw){
		e.push_back(edge{x,y,flw});
		e.push_back(edge{y,x,0});
		v[x].push_back(e.size()-2);
		v[y].push_back(e.size()-1);
	}
	
	int bfs(){
		memset(dis,0x3f,sizeof(dis));
		int l=1,r=1;que[1]=s;dis[s]=0;
		while(l<=r){
			int p=que[l++],to;
			for(int i:v[p]){
				if(e[i].cap&&dis[to=e[i].v]>1e9){
					dis[to]=dis[p]+1;que[++r]=to;
				}
			}
		}
		return dis[t]<1e9;
	}
	
	int dfs(int p,int a){
		if(p==t||!a)return a;
		int sf=0,flw;
		for(int &i=cur[p],to;i<(int)v[p].size();++i){
			edge &E=e[v[p][i]];
			if(dis[to=E.v]==dis[p]+1&&(flw=dfs(to,min(a,E.cap)))){
				E.cap-=flw;e[v[p][i]^1].cap+=flw;
				a-=flw;
				sf+=flw;
				if(!a)break;
			}
		}
		return sf;
	}
	
	int Dinic(int s,int t,int tp=1){
		
		this->s=s;this->t=t;this->tp=tp;
		int flw=0;
		while(bfs()){
			memset(cur,0,sizeof(cur));
			flw+=dfs(s,INT_MAX);
		}
		return flw;
	}
	
};

int main(){
	ios::sync_with_stdio(false);
	
	int T;
	
	cin>>T;
	
	while(T--){
		int n;
		cin>>n;
		
		int BASE=105;
		int a[110],b[110];
		
		for(int i=1;i<=n;i++){
			cin>>a[i];
			a[i]+=BASE;
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
			b[i]+=BASE;
		}
		
		int s=510,t=511;
		dinic sol;
		for(int i=1;i<=n;i++){
			sol.AddEdge(s,a[i],1);
			sol.AddEdge(a[i],a[i]*2,1);
			sol.AddEdge(a[i],(a[i]+1)*2,1);
			sol.AddEdge(b[i]*2,t,1);
			
		}
		
		int flow=sol.Dinic(s,t,1);
		
		if(flow==n)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	
	return 0;
}
```


---

## 作者：DPseud (赞：1)

### [返回题目](https://www.luogu.com.cn/problem/CF1584C)

## 思路

题目中所说的“正好以此操作”指的是随意打乱 $A$ 数组后选择 $k$ 个数加 1，我们可以这样想：想要让 $A$ 数组与 $B$ 数组每个数相等，就必须在打乱时先做到接近，如何做到接近呢？很显然需要用排序。

那么大体思路就是排序后逐一检查 $A$ 数组与 $B$ 数组每个数的差是否为 1 或 0 了，代码如下（貌似是最简短代码）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	register int t,i=0;
	cin>>t;
	forr:int n,a[111],b[111];//用goto比for循环更简便
	memset(a,0,sizeof(a)),memset(b,0,sizeof(b));//将两个数组清空
	cin>>n;
	for(int i=0;i<n;i++)scanf("%d",&a[i]);//读入
	for(int i=0;i<n;i++)scanf("%d",&b[i]);
	sort(a,a+n),sort(b,b+n);//排序
	bool bj=0;
	for(int i=0;i<n;i++)if(b[i]-a[i]<0||b[i]-a[i]>1)bj=1;//如果差不等于1或0将bj设为true
	if(bj==0)puts("YES");//puts自带换行
	else puts("NO");
	i++;
	if(i<t)goto forr;
	return 0;
}
```


---

## 作者：mzyc_jx (赞：1)

[CF1584C Two Arrays](https://www.luogu.com.cn/problem/CF1584C)

### 思路：
1. 先把 $a,b$ 数组都排一个序（因为操作中可以打乱数组，所以可以排序)。

2. 比较下标相同的两个数 $a_i,b_i$ ：如果是 $a_i+1=b_i$ ，在操作中让 $A_i$ 变为 $B_i$ ；如果是 $A_i=B_i$，那么就不操作 $A_i$ 。

3. 若是其他情况就无法对应。也就是如果不是 2. 的两种情况，就直接输出 ```NO``` 并结束本次循环。最后，如果没有输出 ```NO``` ，就输出 ```YES``` 。

### CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105],b[105]; 
int main()
{
	int t,n;
	cin>>t;
	while(cin>>n)//习惯这样循环读入了
	{
		for(int i=1;i<=n;i++)
		cin>>a[i];
		for(int i=1;i<=n;i++)
		cin>>b[i];
		sort(a+1,a+n+1);//排序
		sort(b+1,b+n+1);
		for(int i=1;i<=n;i++)
		if(b[i]-a[i]!=1&&b[i]!=a[i])//比较
		{
			cout<<"NO"<<"\n";
			goto end;//用 goto 比较方便
		}
		cout<<"YES"<<"\n";//符合情况就输出 YES
		end:;
	}
	return 0;
}
```

---

## 作者：OoXiao_QioO (赞：0)

# 题目描述

有 $2$ 个大小为 $n$ 数组 $A,B$。

定义一次操作如下：

- 在 $A$ 数组里选择 $k$ 个数，并把它们加 $1$。

- 随意打乱 $A$ 数组。

问：能否在做完 正好一次 操作后，把 $A$ 数组变为 $B$。

其中要输入 $n$、数组 $A$ 和数组 $B$，而并不需要输入 $k$，我就是这样被坑了一次！！！

# 思路

题目说明了可以随意打乱 $A$ 数组，那我们只要让 $A$ 数组有序即可，因为这样能让我们更好的判断是否要 $+1$。而 $B$ 数组我们也可以给它排个序，这样 $A$、$B$ 数组的元素就可以一一对应起来，方便我们比较，然后做出判断。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	//定义变量
	 
	int t,n,i,j,a[10001],b[10001],f;
	// t 表示组数、n 表示 a、b 数组大小， f 表示是否可以让 A 数组变成 B 数组，也是输出的关键 
	
	//输入
	 
	cin>>t;
	
	//处理 
	
	while(t--)
	{
		f = 1;//我们假设一开始 a 数组可以变成 b 数组 
		cin>>n;
		
		for(i=1;i<=n;i++)
			cin>>a[i];
		for(i=1;i<=n;i++)
			cin>>b[i];
			
		sort(a+1,a+1+n);//把 a 数组排序 
		sort(b+1,b+1+n);//把 b 数组排序 
		
		for(i=1;i<=n;i++)
		{
			if(a[i]<b[i])//如果 a[i] < b[i] 
				a[i]++;  //就让 a[i] +1
		}
		
		for(i=1;i<=n;i++)
		{
			if(a[i]==b[i])//判断两个数组的元素是否全部相同 
				continue; //相同的话，继续比较下一个元素 
			else
			{
				f = 0;//发现不相同的元素， f 变成 0 
				break;//我们就不用浪费时间继续找下去了，直接 break 
			}
		}
		
		printf("%s\n",f?"YES":"NO");//巧妙地运用三目运算符，不会使用的同学可以看下面，记得输出换行 
		/*
		if(f)
			printf("YES");
		else
			printf("NO");
		printf("\n");
		*/ 
	}
	return 0;
}
```



---

## 作者：cxy000 (赞：0)

题目描述：


其实这道题是这个意思：


给你 $n$ （首先假设数据组数为 $1$），然后输入 $a_1$，$a_2$，$a_3$... $a_n$ 和 $B$ 数组（这里不赘述），然后将它们进行**排序**，最后枚举 $a_i$ 和 $b_i$ 之间有没有 $a_i+1=b_i$ 或 $a_i=b_i$ 的关系。


那么这道题就很简单了吧。

1.先输入 $A$ 和 $B$ 数组。

2.然后再对 $A$ 和 $B$ 数组进行排序。

3.再从 $i=1,2,...,n$ 对 $A$，$B$ 数组进行枚举推论即可

故我们可以得到代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
bool vis[10010],vis2[10010];
int main(){
	int t;
	cin>>t;
	int a[100100],b[100100];
	while(t--){//t组数据不要忘记
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) cin>>b[i];
		sort(a+1,a+1+n);
		sort(b+1,b+1+n);//用STL-sort进行排序
		bool oo=0;
		for(int i=1;i<=n;i++){
			if(a[i]!=b[i] && a[i]+1!=b[i]) {//进行判断
				oo=1;//出来之后的判断用（当然也可以直接输）
				break;
			} 
		}
		if(oo==1) cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
	return 0;//完结撒花！
}
```


---

## 作者：5k_sync_closer (赞：0)

# 题意
给两个长度为 $n$ 的数组 $A,B$。

现在可以从 $A$ 中选 $k$ 个数，把 $a_i$ 改为 $a_i+1$。

然后可以把 $A$ 任意打乱，问操作后 $A$ 是否可以变成 $B$。
# 思路
显然，如果可以把 $A$ 变为 $B$，

那么在选取 $k$ 个数加一后，$A$ 与 $B$ 可以**一一对应**。

所以，只需要把两个数组排序，使应该对应的数相互对应。

然后判断两个数组中，两个数是否对应即可。

考虑两个数对应的条件，

因为这 $k$ 个数可以任意选，所以 $a_i=b_i$ 或 $a_i+1=b_i$ 都是对应的。

那么，只要有一对数不对应，$A$ 就不能变为 $B$。
# 代码
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int t, n, a[150], b[150];
int main()
{
	cin >> t;
	while(t--)
	{
		cin >> n;bool f = 0;
		for(int i = 0;i < n;++i)
			cin >> a[i];
		for(int i = 0;i < n;++i)
			cin >> b[i];
		sort(a, a + n);sort(b, b + n);
		for(int i = 0;i < n;++i)
			if(b[i] != a[i] && b[i] != a[i] + 1)
			{
				cout << "NO" << endl;f = 1;break;
			}
		if(!f) cout << "YES" << endl;
	}
	return 0;
}
```


---

## 作者：CSP_Sept (赞：0)

**[Technocup 2022 - Elimination Round 2](http://codeforces.com/contest/1584)** [A](https://www.luogu.com.cn/blog/supervise/solution-cf1584a) / [B](https://www.luogu.com.cn/blog/supervise/solution-cf1584b) / C / [D](https://www.luogu.com.cn/blog/supervise/solution-cf1584d) / [E](https://www.luogu.com.cn/blog/supervise/solution-cf1584e) / [F](https://www.luogu.com.cn/blog/supervise/solution-cf1584f) / [G](https://www.luogu.com.cn/blog/supervise/solution-cf1584g)

如果以上链接所指链接不存在，就是作者咕了 /dk

### Description

给定一个数列 $a$，每次操作你可以：

- 选择 $k(0\le k\le n)$ 个数 $i_1\sim i_k$。
- 把所有 $a_{i_k}$ 加上 $1$。
- 任意重排 $a$。

问能否通过一次操作把 $a$ 变成数列 $b$。

### Soluition

显然需要把 $a,b$ 排序。

扫一遍 $a,b$，每次判断 $a_i$ 能否通过操作变成 $b_i$，即是否有 $0\le b_i-a_i\le1$。

可以证明，若此时 $a_i,b_i$ 不满足条件，则无解，这里给出简略证明。

我们把符合 $0\le B-A\le 1$ 的 $A,B$ 称作是配对的。

- 对于 $a_1,b_1$，若二者不配对，则有以下两种情况：
	1. $a_1>b_1$，则必然不存在 $a_i$ 能与 $b_1$ 配对。
	2. $a_1+1<b_1$，则必然不存在 $b_i$ 能与 $a_1$ 配对。
- 若不配对，直接判定无解。
- 否则删除 $a,b$ 的第 $1$ 项，回到第一步。

以上是建立在 $a,b$ 有序的基础上的。

$\mathcal{Q.\ E.\ D.\ }$

### Code

[$\textit{135366687}$](http://codeforces.com/contest/1589/submission/135366687)

顺带一提，这题 pretest 非常弱，我贡献了 [test #131](http://codeforces.com/contest/1589/hacks/770743/test) /se

---

## 作者：徐晨轩✅ (赞：0)

# 题意简述

> 有 $2$ 个大小为 $n$ 数组 $A,B$。
> 
> 定义一次操作如下：
>
> * 在 $A$ 数组里选择 $k$ 个数，并把它们加 $1$。
> * 随意打乱 $A$ 数组。
> 
> 问：能否在做完 **正好一次** 操作后，把 $A$ 数组变为 $B$。

# 解法

不难想到，先把 $A,B$ 数组都排一个递增序（因为操作中可以打乱数组，所以可以对其进行排序，这样，$A_i$ 必须要通过这次操作变成 $B_i$），并比对下标相同的两个数 $A_i,B_i$：如果 $A_i+1=B_i$ 就在操作中选中 $A_i$，即可变为 $B_i$，或者是 $A_i=B_i$，那么就不选中 $A_i$，若是其他情况无论是否选中，都无法对应起来。也就是说，要是不是以上两种情况，就直接输出 `NO` 并结束。最后，如果没有输出 `NO`，就输出 `YES`。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,a[101],b[101]; 
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n;
		for(int i=1;i<=n;i++)
			cin >> a[i];
		for(int i=1;i<=n;i++)
			cin >> b[i];
		sort(a+1,a+n+1);
		sort(b+1,b+n+1);
		for(int i=1;i<=n;i++)
			if(b[i]-a[i]!=1&&b[i]!=a[i])
			{
				cout << "NO" << endl;
				goto end;
			}
		cout << "YES" << endl;
end:;
	}
	return 0;
}
```

---

