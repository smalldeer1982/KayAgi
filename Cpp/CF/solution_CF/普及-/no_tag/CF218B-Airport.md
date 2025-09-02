# Airport

## 题目描述

Lolek and Bolek are about to travel abroad by plane. The local airport has a special "Choose Your Plane" offer. The offer's conditions are as follows:

- it is up to a passenger to choose a plane to fly on;
- if the chosen plane has $ x $ $ (x&gt;0) $ empty seats at the given moment, then the ticket for such a plane costs $ x $ zlotys (units of Polish currency).

The only ticket office of the airport already has a queue of $ n $ passengers in front of it. Lolek and Bolek have not stood in the queue yet, but they are already wondering what is the maximum and the minimum number of zlotys the airport administration can earn if all $ n $ passengers buy tickets according to the conditions of this offer?

The passengers buy tickets in turn, the first person in the queue goes first, then goes the second one, and so on up to $ n $ -th person.

## 说明/提示

In the first test sample the number of passengers is equal to the number of empty seats, so regardless of the way the planes are chosen, the administration will earn the same sum.

In the second sample the sum is maximized if the 1-st person in the queue buys a ticket to the 1-st plane, the 2-nd person — to the 2-nd plane, the 3-rd person — to the 3-rd plane, the 4-th person — to the 1-st plane. The sum is minimized if the 1-st person in the queue buys a ticket to the 1-st plane, the 2-nd person — to the 1-st plane, the 3-rd person — to the 2-nd plane, the 4-th person — to the 2-nd plane.

## 样例 #1

### 输入

```
4 3
2 1 1
```

### 输出

```
5 5
```

## 样例 #2

### 输入

```
4 3
2 2 2
```

### 输出

```
7 6
```

# 题解

## 作者：L_zaa_L (赞：5)

# 分析
首先最大最小值看得出来要贪心，而它的值就要能大就大，能小就小。
### 最大
从后往前，每次找空位多的坐，可以先从座位的数量入手找到最大的数，将所有等于这个数的减少，并记录答案，然后将最大值减少，直到每个人都有座位就停止。
### 最小
从前往后，每次将座位最少飞机坐满，就会得到最小的答案，也是到每个人都有座位时停止。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[10001],mn,mx;//rt
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	} 
	sort(a+1,a+n+1);//排序，至关重要的一步
	int s=0;//记录有位置的人的数量
	bool flag=0;
	for(int i=1;i<=n;i++){
		int p=a[i];
		while(s!=m&&p){//将每个飞机坐满，并要防止每个人都有位置了
			mn+=p;//记录答案
			p--;//减少座位数
			s++;//有一个人有位置了
		}
		if(s==m) break;//如果每个人都有位置了，就不要算了
	}
	int p=a[n];//记录最大值
	s=0;//记录有位置的人的数量
	for(int i=p;i>=1;i--){
		for(int j=n;j>=1;j--){//从前往后找
			while(a[j]>=i&&s!=m){//不能多于最大值
				s++;
				mx+=a[j];
				a[j]--;//同上
			}
			if(s==m) break;//同上
		}
		if(s==m) break;//同上
	}
	cout<<mx<<" "<<mn; 
	return 0;
} 
```

---

## 作者：_byta (赞：3)

考虑贪心，我们当前只考虑票价最大的情况，最小同理可得。

要使票价最大，每个人肯定选择空位最多的那个位子，于是我们可以用大根堆

维护当前空位最多的位子。当一个人选了之后，把此位置空位减一再加入大根堆。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1002;
int n,m,k,p,ans,sum,tot,cnt,a[N],b[N],c[N];
priority_queue<int> q;
priority_queue<int,vector<int>,greater<int> > q2;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i];
		q.push(a[i]);
		q2.push(a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		int maxn=q.top();
		q.pop();
		ans+=maxn;
		if(maxn-1!=0)q.push(maxn-1);
		int minn=q2.top();
		q2.pop();
		sum+=minn;
		if(minn-1!=0)q2.push(minn-1);
	}
	cout<<ans<<" "<<sum;
    return 0;
}
```




---

## 作者：miraculously (赞：2)

解法一：

贪心思想，直接暴力做，要票价最贵，能取最大就取最大，最小同理。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,b[1001],a[1001],maxn,minn,cnt=1;//cnt指不为0的最小下标为取最小值服务
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	b[i]=a[i];//b可以看作中转站，因为a的值要用两次，所以用b来代替
	for(int i=1;i<=n;i++)
	{
		sort(b+1,b+m+1);
		maxn+=b[m];
		b[m]--;
	}
	for(int i=1;i<=m;i++)
	b[i]=a[i];
	for(int i=1;i<=n;i++)
	{
		sort(b+1,b+m+1);
		minn+=b[cnt];
		b[cnt]--;
		while(b[cnt]==0)
		cnt++;
	}
	printf("%d %d",maxn,minn);
}
```

解法二（不贴代码）：

最大值仍用原做法，将 $a$ 从小到大排，一个个累加，直到大于等于人数，设这时有 $cnt$ 个数，将前 $cnt-1$ 的数的等差数列和累加，然后再加上多出来的人数需要的费用就是最小值。

---

## 作者：LeiZeProMax (赞：1)

题意：给定乘客数量 $n$，飞机数量 $m$ 和每架飞机的空座，求最大价钱和最小价钱。

我们可以用两个优先队列 $a$ 和 $b$ 来分别维护最大价和最小价。
求最大价的方法：每次弹出队列 $a$ 中的最大值，让价钱加上空座位数量，并让空座位 $-1$。

求最小价的方法：每次弹出队列 $b$ 中的最小值，让价钱加上空座位数量，并让空座位 $-1$，判断队列 $b$ 中的最小值是否等于 $0$，如果等于就弹出。

# Code：
```cpp
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
priority_queue<int>a;
priority_queue<int,vector<int>,greater<int> >b;
int n,m,ans1,ans2;
inline int read()//快读 
{
	int s=0;bool x=true;char ch=getchar();
	while(ch<'0'||ch>'9'){x=(ch=='-'?false:true);ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<3)+(s<<1)+(ch^48);ch=getchar();}
	return x==true?s:(~s+1);
}
int main()
{
	n=read();m=read();
	while(m--)
	{
		int x=read();
		a.push(x);b.push(x);//将座位压入队列
	}
	for(register int i=1;i<=n;i++)
	{
		int c;
		ans1+=a.top();//更新最大值
		c=a.top()-1;a.pop();a.push(c);//求最大值
		ans2+=b.top();//更新最小值
		c=b.top()-1;b.pop();b.push(c);//求最小值
		if(b.top()==0)b.pop();//如果等于0，弹出
	}
	printf("%d %d\n",ans1,ans2);
	return 0;
}
```


---

## 作者：_szs9601 (赞：0)

#### 题意
有 $n$ 个乘客，$m$ 架飞机，求出可以赚取的最大价钱和最小价钱。
#### 思路
一道很水的贪心题。求最大的价钱，我们用数组进行模拟，每次都进行排序，然后加入当前最大的票价，答案就是可以赚取的最大价钱。求最小的价钱也是用相同的方法。
### 注意
在求最小价钱时不能加入票价为 0 的票。
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool cmp(int x,int y){return x>y;}
int n,m,i,ma,mi,cnt,a[1010],b[1010];
int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) scanf("%d",&a[i]),b[i]=a[i];
	cnt=1;
	for(i=1;i<=n;i++){
		sort(a+1,a+m+1,cmp);
		ma+=a[1];a[1]--;//最大 
		sort(b+1,b+m+1);
		mi+=b[cnt];b[cnt]--;
		if(b[cnt]==0) cnt++;//最小 判断票价为0的票
	}
	printf("%d %d\n",ma,mi);
	return 0;
}
```

---

## 作者：zwy__ (赞：0)

看几位大佬都是用优先队列的，我来发一篇普通数组的。
### [题目传送门](https://www.luogu.com.cn/problem/CF218B)
### 题意
$n$ 个乘客， $m$ 架飞机，每个乘客按顺序挑选一架飞机并买票，票价为他挑选的飞机的空位数，求航空公司可以赚取的最大价钱和最小价钱。
### 思路
这题我们按题目意思模拟，用一个数组当临时存放数的，每次排序，再按题目处理，最后输出答案。
### 细节
注意在从小到大排序时，要注意最小会出现 $0$ 的情况，要记得处理。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,mi,ma,wz;
int a[1005],b[1005];
int main()
{
    cin>>n>>m;
    for(int i=1; i<=m; i++)
    {
    	cin>>a[i];
    	b[i]=a[i];
    }
    for(int i=1; i<=n; i++)
    {
    	sort(b+1,b+1+m);
    	ma+=b[m];
    	b[m]--;
    }
    wz=1;
    for(int i=1; i<=m; i++)b[i]=a[i];
    for(int i=1; i<=n; i++)
    {
    	sort(b+1,b+1+m);
    	mi+=b[wz];
    	b[wz]--;
    	while(b[wz]==0)wz++;//可能会有0的情况
    }
    cout<<ma<<" "<<mi;
    return 0;
}
```
[记录](https://www.luogu.com.cn/record/74275127)

---

## 作者：xiaomuyun (赞：0)

# CF218B Airport 题解
[题目传送门](https://www.luogu.com.cn/problem/CF218B)
## 题意简述
~~感觉翻译有点不清晰~~

有 $n$ 个人在买票。有 $m$ 架飞机，一开始第 $i$ 架飞机有 $a_i$ 个空位，而且当某个人买了这架飞机的票时，他需要花费的钱就是这架飞机**当前**的空位数。**注意，当某个人买了第 $i$ 架飞机的票时，这架飞机的空位数量就会 $-1$。**
## 前置知识
这题需要用一个叫做 `priority_queue` 的 `STL` 容器，即**优先队列**。这个容器和队列一样，但是每次取 $\operatorname{top()}$ 时，返回的是最大值或最小值。具体怎么做，请大家看下面：
```cpp
priority_queue<int,vector<int>,less<int> > q;
//这行代码会定义一个每次返回最大值的优先队列
priority_queue<int,vector<int>,greater<int> > q2;
//这行代码会定义一个每次返回最小值的优先队列
```
不过，一般第一行代码会简化成这样：
```cpp
priority_queue<int> q;
```
有一个地方要注意，就是在最后两个 `>` 之间要有一个空格，否则编译器会把这个东西看成右移运算符（`>>`）。
## 算法分析
我们要定义两个优先队列，一个是返回最小值的，另一个是返回最大值的。我们需要将这两个优先队列配合**贪心**。
### 求最大价钱
为了让每次买票的人花的钱最多，所以我们可以让他们都买当前**空位最多**（即价格最高）的飞机票。

每次在返回最大值的优先队列中得到当前最大空位数的飞机，然后将它推出队列，再将这个数 $-1$ 并入队（注意，如果当前飞机已经没有空位了，就不用再入队了）。为了统计答案，需要在将这个数 $-1$ 之前将答案增加当前飞机所花的价钱。
### 求最小价钱
和上面几乎一样，只不过是用返回最小值的优先队列罢了。
## 代码实现
```cpp
#include<cstdio>
#include<queue>
using namespace std;
int n,m,seat[1001],res1=0,res2=0;
//res1是最大价钱
//res2是最小价钱
priority_queue<int,vector<int>,less<int> > q1;//返回最大值的优先队列
priority_queue<int,vector<int>,greater<int> > q2;//返回最小值的优先队列
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i) scanf("%d",&seat[i]);
	for(int i=1;i<=m;++i){//首先，都入队
		q1.push(seat[i]);
		q2.push(seat[i]);
	}
	for(int i=1;i<=n;++i){//求最大价钱
		int val=q1.top();
		q1.pop();
		res1+=val--;//相当于首先将res1增加val，然后--val
		if(val>0) q1.push(val);//注意要判断当前飞机是否还有空位
	}
	for(int i=1;i<=n;++i){
		int val=q2.top();
		q2.pop();
		res2+=val--;
		if(val>0) q2.push(val);
	}
	printf("%d %d\n",res1,res2);
	return 0;
}
```

---

