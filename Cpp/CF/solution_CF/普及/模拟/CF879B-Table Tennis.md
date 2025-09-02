# Table Tennis

## 题目描述

 $ n $ people are standing in a line to play table tennis. At first, the first two players in the line play a game. Then the loser goes to the end of the line, and the winner plays with the next person from the line, and so on. They play until someone wins $ k $ games in a row. This player becomes the winner.

For each of the participants, you know the power to play table tennis, and for all players these values are different. In a game the player with greater power always wins. Determine who will be the winner.

## 说明/提示

Games in the second sample:

 $ 3 $ plays with $ 1 $ . $ 3 $ wins. $ 1 $ goes to the end of the line.

 $ 3 $ plays with $ 2 $ . $ 3 $ wins. He wins twice in a row. He becomes the winner.

## 样例 #1

### 输入

```
2 2
1 2
```

### 输出

```
2 ```

## 样例 #2

### 输入

```
4 2
3 1 2 4
```

### 输出

```
3 ```

## 样例 #3

### 输入

```
6 2
6 5 3 1 2 4
```

### 输出

```
6 ```

## 样例 #4

### 输入

```
2 10000000000
2 1
```

### 输出

```
2
```

# 题解

## 作者：Xiaonanu (赞：2)

## Table Tennis

### 思路分析

这道题如果纯模拟的话，明显会超时，所以我们可以通过优化通过此题。

#### 1. 如何优化
因为题目分两种最后结果：**如果能力值比较小的还没轮到能力值最大的选手的话就完成连击，他才能赢，否则会由能力最大的人赢。**

所以，我们可以先模拟一轮比赛，如果轮完了 $1$ 轮还没分出胜负，即代表能力最大的人获胜。

#### 2. 数据范围判断

因为 $n \leq 500$ ，所以循环 $500$ 次不会超时，而 $k$ 的范围不用管，因为我们把 $k$ 优化了。还有一点，$k$ 要开成长整形变量，因为我们在连击达成判断中用到。

#### 3. AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k;			
int maxn=-1;
queue<int>q,qf;					
void qmax()						
{
	for(int i=1;i<=n+3;i++)
	{
		maxn=max(maxn,q.front());
		q.push(q.front());		
		q.pop();
	}
}
void f()
{
	int sum=0,a=qf.front();
	qf.push(qf.front());		
	qf.pop();
	for(int i=1;i<=2*n;i++)
	{
		if(qf.front()>a)		
		{
			sum=0;
			qf.push(a);
			a=qf.front();
			qf.pop();
		}
		else					
		{
			qf.push(qf.front());
			qf.pop();
		}
		sum++;
		if(sum>=k)				 
		{
			cout<<a;
			return;
		}
	}
	cout<<maxn;					
	return;
}
int main()
{
	cin>>n>>k; 
	for(int i=1;i<=n;i++)	
	{
		int a;
		cin>>a;
		q.push(a);
		qf.push(a);
	}
	qmax();					
	f();
	return 0;
}
```


---

## 作者：To_Carpe_Diem (赞：1)

## 题目简述

给你两个数 $n$ 和 $k$，$n$ 代表排队人数，$k$ 代表需要连续赢的次数，模拟过程如下：

- 队首的两个人进行打擂。

- 能力值大的人获胜，继续打擂。

- 另一个人回到队尾，继续参加打擂。

## 思路

首先，看见这道题，我的思路是这样的：

- 当 $n \le k$ 时直接输出 $\max_{i=1}^{n} a_i$

- 当 $n > k$ 时直接输出 $\max_{i=1}^{k+1} a_i$

写出来代码如下：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define MAXN 505

long long n, k, a[MAXN], maxn = -1e9;

int main() {
	cin >> n >> k;
	for(int i = 1; i <= n; i ++) {
		cin >> a[i];
		maxn = max(maxn, a[i]);
	}
	if(k >= n) { cout << maxn << endl; return 0; }
	sort(a + 1, a + k + 2);
	cout << a[k + 1] << endl;
	return 0;
}
```

然而，在第九个测试点输出错误。

经过一番思考，可得以下 $\text{hack}$ 数据：

```
4 2
1 2 3 4
```

这个样例本应输出 $4$，但是程序输出的却是 $3$。

从中可以知道当 $n > k$ 的时候程序不一定正确。

需要进行打擂法，可得以下模拟代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define MAXN 1005

long long n, k, a[MAXN], b[MAXN], maxn = -1e9, x = 1;
//a数组用来存储能力值，b数组用来存储赢的次数。

int main() {
	cin >> n >> k;
	for(int i = 1; i <= n; i ++) {
		cin >> a[i];
		maxn = max(maxn, a[i]);
	}
	if(k >= n) {
		cout << maxn << endl;
		return 0;
	}
	for(int i = 2; i <= n; i ++) {
		if(a[x] > a[i] && a[i] != -1) a[i] = -1, b[x] ++;
		else if(a[x] < a[i] && a[i] != -1) x = i, b[x] ++;
		if(b[x] == k) {//当次数等于k时直接输出
			cout << a[x] << endl;
			return 0;
		}
	}
	cout << a[x] << endl;
	return 0;
```

我发现大家都用的 $\text{deque}$，于是来一篇 $\text{list}$ 的。

简单的区分一下 $\text{deque}$ 和 $\text{list}$ 的区别：

- $\text{list}$ 是非连续存储结构，其插入和删除效率高，但是不支持随机访问。

- $\text{deque}$ 是连续存储结构，其支持随机访问。

因此这道题不需要随机访问，所以用 $\text{list}$ 好一点。

```cpp
#include<iostream>
#include<queue>
#include<list>
#include<algorithm>
#define ll long long
using namespace std;

ll n,k,times;
ll x,maxn;
list<ll> q;

int main(){
	cin>>n>>k;
	for(ll i=1;i<=n;i++){
		cin>>x;
		q.push_back(x);
		maxn=max(maxn,x);
	}
	if(n<=k){
		cout<<maxn<<"\n";
	 	return 0;
	}
	while(times<k){
		int a=q.front();
		q.pop_front();
		int b=q.front();
	  	q.pop_front();
		if(a>b){
			times++;
			q.push_front(a);
			q.push_back(b);
		}
		else{
			times=1;
			q.push_front(b);
			q.push_back(a);
		}
	}
	cout<<q.front()<<"\n";
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/127649840)

---

## 作者：TheSky233 (赞：1)

## Description
给定一个正整数序列 $a_{1 \cdots n}$，每次将 $a_1$ 与 $a_2$ 作比较，如果 $a_1 > a_2$，就把连胜数加 $1$，并把 $a_2$ 放到序列最后，否则清空连胜数，并把 $a_1$ 放到序列最后，求能连胜 $k$ 场的序列元素的值。

## Solution

### 前置知识
STL 中的 deque（双端队列）。

### 思路
模拟即可。

由于往序列里插入元素时用数组模拟太麻烦，于是考虑用 STL 中的 deque，不知道 deque 用法的可以[戳这里](http://c.biancheng.net/view/6860.html)。

对于每一次比较，我们从队列中取出队首，然后 pop 掉，再取一次，这样就有了上文描述的 $a_1$ 和 $a_2$，打擂台，如果 $a_1 > a_2$，就把计数器加 $1$，然后把 $a_1$ 放回队首，把 $a_2$ 放到队尾，否则把 $a_2$ 放到队首，把 $a_1$ 放到队尾，并**把计数器的值设为** $1$（可以看作第二个人连胜了一场）。如果计数器的值大于等于 $k$，```break``` 掉，最后输出队首即可。

### 一个必要的优化
我们注意到，$k \leq 10^{12}$，如果纯模拟一定会 TLE，但是 $n \leq 500$，容易想到，如果 $k \geq n$，那么就说明最后的答案一定会和队中每个元素都打一遍擂台，那么就直接输出序列中的最大值即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

template <typename T> inline void read(T& x) {
	x=0;T f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=x*f;
	return;
}
template <typename T,typename ...Arg>void read(T& x,Arg& ...arg){
	read(x);
	read(arg...);
}
template <typename T>void write(T x) {
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else write(x/10),putchar(x%10+'0');
}
template <typename T,typename ...Arg>void write(T& x,Arg& ...arg){
	write(x);
	putchar(' ');
	write(arg...);
}

long long n,k,winstreak;
int num,maxx;
deque<int> q;

int main(){
	read(n,k);
	for(int i=1;i<=n;i++){
		read(num);
		q.push_back(num);
		maxx=max(maxx,num);
	}
	if(n<=k){write(maxx); return 0;}
	while(winstreak<k){
		int fr=q.front(); q.pop_front();
		int se=q.front(); q.pop_front();
		if(fr>se){
			winstreak++;
			q.push_front(fr);
			q.push_back(se);
		}
		else{
			winstreak=1;
			q.push_front(se);
			q.push_back(fr);
		}
	}
	write(q.front());
	return 0;
}
```

---

## 作者：至成天下 (赞：1)

看一眼题目,我立即就想到了队列

这道题由于数据不强直接队列模拟即可

注意如果k>n输出的能力值一定是能力值中最大的,纯模拟过不了10^12

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,maxn;
queue <int> q;//定义队列
long long k,coun;
int main(){
	cin>>n>>k;
	cin>>a;//特殊处理第一个数
	maxn=a;
	for(int i=1;i<n;++i){
		cin>>b,q.push(b);
		maxn=max(maxn,b);
	}
	if(k>n){//特判
		cout<<maxn<<endl;
		return 0;
	}
	while(1){
		if(a<q.front()){//比较队头和擂主
			coun=1;
			int t=a;
			a=q.front();
			q.pop();
			q.push(t);//交换擂主
		}
		else {
			coun++;
			q.push(q.front());//排入队尾
			q.pop();
		}
		if(coun==k){//判断是否连胜k场
			cout<<a<<endl;
			return 0;
		}
	}
	return 0;
}

```


---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF879B) & [CF链接](http://codeforces.com/problemset/problem/879/B)

## 题意简述：

有 $n$ 个人打擂台赛，能力值高的获胜，赢的是擂主，输的下去排队挑战，输出第一个连续当擂主 $k$ 次的能力值。

## 思路分析：

很明显，当 $k\ge n-1$ 时，答案是 $\max a_i$。

当 $k\le n-1$ 时，我们可以枚举一遍。仔细观察题目中的特点：

1. 输出的是能力值而不是编号。

2. 输了要去队尾排队。

是不是符合队列先进先出的性质？所以我们只需要吧每个能力值入队模拟即可。注意 $k$ 的取值范围。

## 代码：

```cpp
#include<iostream>
#include<queue>
#define ll long long
using namespace std;
queue<int>q;
int n,x,maxn,tmp,ans,now;//ans记录当前擂主连续获胜次数，now表示当前挑战者，tmp表示当前擂主，maxn求最大值 
ll k;//十年OI一场空 
int main(){
	scanf("%d%lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		q.push(x);//入队 
		maxn=max(maxn,x);//求最大值 
	}
	if(k>=n-1){//特判 
		cout<<maxn;
		return 0;
	}
	tmp=q.front();//队首暂时擂主 
	q.pop();
	for(int i=2;i<n;i++){
		now=q.front();
		q.pop();
		if(tmp>now){//擂主守擂成功 
			ans+=1;
			q.push(now);//挑战者去队尾 
			if(ans>=k){
				cout<<tmp;
				return 0;
			}
		}else{//新晋擂主 
			if(ans>=k){
				cout<<tmp;
				return 0;
			}
			ans=1;//已经获胜一次 
			q.push(tmp);//原擂主去后面排队 
			tmp=now;//更新擂主
			//注意操作顺序 
		}
	}
	cout<<maxn;
	return 0;
}
```

---

## 作者：_HiKou_ (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF879B)

虽然洛谷的 RMJ 炸了，不过还是去 CF 上面交了这道题目...

题目：一个有 $n$ 个数的数列，将前两个数比较，较小者移动到队尾，求在比较的过程中最先连续 $k$ 次成为最大值的数。

由题可知，$2≤n≤500$，$2≤k≤10^{12}$，所以我们得想办法处理 $k$。

可以证明，如果比较 $n-1$ 次，在队首的一定是整个数列的最大值。因为题目保证所有的 $a_i$ 并不相同，所以在这之后，无论怎么比较，最大值一定会比第二个数大，所以可以一直连胜。

也就是说，只要 $k>n$，那么其他的任何数最多只能连胜 $n-2$ 次，只有数列的最大值能达到任意的 $k$ 值，即答案为数列最大值。（虽然上面说的 $k>n$ 也差不了多少，但是我实际评测快了 1ms）

剩下的情况模拟即可。即把较小的数通过交换移动到数列的最尾端。

CODE：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,k,a[514],maxt[514],maxn=0,i;
int main(){
	scanf("%lld%lld",&n,&k);
	for(i=1;i<=n;i++)scanf("%lld",&a[i]),maxn=max(maxn,a[i]);//在输入时找最大值
	if(k>n-1)//这里是特判
	{
		printf("%lld",maxn);
		return 0;
	}
	ll ls=0;//连胜次数
	while(ls!=k)
	{
		ll winner;
		if(a[1]>a[2])ls++,winner=1;//赢家为前面的
		else ls=1,winner=2;//注意在这里已经赢了一次了，所以初始化为 1
		for(i=1;i<=n-1;i++)
		{
			if(winner==1&&i==1)continue;//如果赢家在前面就把第二位换到后面，自己思考一下
			swap(a[i],a[i+1]);//否则就交换
		}
	}
	printf("%lld",a[1]);//输出队首就可以了
	return 0;
} 
```

---

## 作者：YCE__22 (赞：0)

题意：

有1-n组成的一个排列，每个数代表一个人的power，两个人比赛时power大的人会获胜

比赛从左到右比，输了的人移到末尾，赢的人和下一个人比，当有一个人赢了k盘时输出该人的power

```cpp
#include <iostream>
 
using namespace std;
 
int main()
{
    long long n,k;
    int fg=0,a[505];
    cin>>n>>k;
    for(int i=0;i<n;i++)
    cin>>a[i];
    if(k>=n)   //只有power为n的人才能赢>=n盘 ，所以k>=n时输出n
    cout<<n<<endl;
    else
    {
       for(int i=0;i<n;i++)
       {
          int s=0;
          if(i!=0&&a[i]>a[i-1])
          s=1;
          for(int j=1;j<=k-s;j++)
          {
             int pos=(i+j)%n;  //亮点，细细体会
             if(a[i]<a[pos])
             break;
             if(j==k-s)
             {
                fg=1;
                cout<<a[i]<<endl;
                break;
             }
          }
          if(fg)
          break;
       }
    }
    return 0;
}
```


---

## 作者：YuRuiH_ (赞：0)



------------
**~~感谢CF的又一道水题~~**

~~这道题也就红题水平吧？~~

**思路：记录每个赢得人赢得次数，谁赢了k次就输出**

**注意k很大，当k>n时，输出最大的那个就行**

直接看代码吧


```c
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;
int a[1000];
int b[1000];
int n;
long long k;
int x;
int main()
{
    cin>>n>>k;
    for(int i=0;i<n; i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<n; i++)
    {
        if(a[x]>a[i]&&a[i]!=-1)
        {
            a[i]=-1;
            b[x]++;
 
        }
        else if(a[x]<a[i]&&a[i]!=-1)
        {
            x=i;
            b[x]++;
        }
        if(b[x]==k)
        {
            cout<<a[x]<<endl;
            return 0;
        }
        //cout<<x<<endl;
    }
    cout<<a[x]<<endl;
}
 

```


---

