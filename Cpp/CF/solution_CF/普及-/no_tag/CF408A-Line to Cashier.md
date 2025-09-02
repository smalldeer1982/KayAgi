# Line to Cashier

## 题目描述

Little Vasya went to the supermarket to get some groceries. He walked about the supermarket for a long time and got a basket full of products. Now he needs to choose the cashier to pay for the products.

There are $ n $ cashiers at the exit from the supermarket. At the moment the queue for the $ i $ -th cashier already has $ k_{i} $ people. The $ j $ -th person standing in the queue to the $ i $ -th cashier has $ m_{i,j} $ items in the basket. Vasya knows that:

- the cashier needs 5 seconds to scan one item;
- after the cashier scans each item of some customer, he needs 15 seconds to take the customer's money and give him the change.

Of course, Vasya wants to select a queue so that he can leave the supermarket as soon as possible. Help him write a program that displays the minimum number of seconds after which Vasya can get to one of the cashiers.

## 说明/提示

In the second test sample, if Vasya goes to the first queue, he gets to the cashier in $ 100·5+15=515 $ seconds. But if he chooses the second queue, he will need $ 1·5+2·5+2·5+3·5+4·15=100 $ seconds. He will need $ 1·5+9·5+1·5+3·15=100 $ seconds for the third one and $ 7·5+8·5+2·15=105 $ seconds for the fourth one. Thus, Vasya gets to the cashier quicker if he chooses the second or the third queue.

## 样例 #1

### 输入

```
1
1
1
```

### 输出

```
20
```

## 样例 #2

### 输入

```
4
1 4 3 2
100
1 2 2 3
1 9 1
7 8
```

### 输出

```
100
```

# 题解

## 作者：RainFestival (赞：2)

$\tt{Difficulty:900}$

对于每一列队伍，我们都要算出他们的时间。

时间分为扫描和付款，对于每一个顾客都要求。

最后我们选择一个时间最短的就行了。

代码如下：

```cpp
#include<cstdio>
int n,f[105],ans=1000000000;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&f[i]);
	for (int i=1;i<=n;i++)
	{
		int s=0;
		while (f[i]--){int x;scanf("%d",&x);s=s+x*5+15;}
		if (s<ans) ans=s;
	}
	printf("%d\n",ans); 
}
```

---

## 作者：小小蒟弱 (赞：1)

模拟题。

算出每队时间求出最小值。

代码：
```cpp
#include <bits/stdc++.h>

using namespace std;

int read() {  // 快读 
    int x = 0, k = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') k = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * k;
}

int a[105];

int main() {
    int n = read(), minn = 1 << 30;
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= n; i++) {
		int s = a[i] * 15;
		// 每个人都要 15 秒 
		for (int j = 1; j <= a[i]; j++) {
			int x = read();
			s += x * 5;  // 每个物品 5 秒 
		}
		if (s < minn) minn = s;  // 最小值 
	}
	printf("%d", minn);  // 完结 
}
```

---

## 作者：hanyuchen2019 (赞：1)


补一下输入格式（纯手打）：

第一行一个整数 $n (1 \le n \le 100)$，表示收银员的队列数量；

第二行有 $n$ 个整数：$k_1,k_2,\dots,k_n(1 \le k_i \le100)$，$k_i$ 表示第 $i$ 个队列的顾客数量；

第 $3$ 至第 $n+2$ 行：对于第 $i$ 行，每行有 $k_i$ 个整数：$m_{i,1},m_{i,2},\dots,m_{i,k_i}$。$m_{i,j}$表示第 $i$ 个队列的第 $j$ 位顾客的商品数量。

### 题解部分

对于第 $i$ 个队列的第 $j$ 位顾客，会用时 $m_{i,j}\times 5+15$ 秒。

算出每个队列的用时总和，再取最小值即可得到答案。

```cpp
#include<iostream>
#include<algortihm>
using namespace std;
int k[105];
int main()
{
	ios::snyc_with_stdio(false);
	int n,ans=2147483647;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>k[i]； 
	for(int i=1;i<=n;i++)
	{
		int ti=0,m;
		for(int j=1;j<=k[i];j++)//求当前队列的用时总和
		{
			cin>>m;
			ti+=m*5+15;
		}
		ans=min(ti,ans);//取最小值
	}
	cout<<ans;
 	return 0;
}

```

---

## 作者：Aya_tt (赞：0)

这题就是一道简单的模拟啊，依次枚举个个队列，看看那个队列花得时间最少。

用一个 $cnt$ 统计时间，$cnt$ 每次更新都要加上时间，因为他问的所用时间的最少值，每次统计的是时间，时间就是 $k$ 乘五再加十五，$k$ 就是输入的数，$cnt$ 把每个时间加起来。最后就是要求求出 $ans$ 最小值，及 $ans=\min(ans,cnt)$，注意，$ans$ 初始值要大。

模拟的关键就是要跟着题意来，题目要你干什么你就要顺着他的做，这道题的确没啥可说的，算出队列所用的总时间，他们的最小值就答案，实现过程也非常简单。

最终代码：

```c
#include<bits/stdc++.h>
using namespace std;
int n,a[110],k,cnt,ans = 1000000000;
int main(){
    cin>>n;
    for(int i = 1;i <= n;i++) cin>>a[i];
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= k[i];j++){
            cin>>k;
            cnt += (k * 5 + 15);
        }
        cnt = min(cnt,ans);
        cnt = 0;
    }
    cout<<ans;
}
```


---

## 作者：HarryKane (赞：0)

这道题是一道简单的模拟题。

根据题意进行模拟即可，找到最小的值更新，最后输出最小的值。

下面是代码：

```cpp
#include<stdio.h>
#include<algorithm> 
const int N=1e2;
int k[N+5],m[N+5][N+5];//如题所示。

void in(int &x){//快读。
	char c=getchar(),f=1;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-'){
	   f=-1,
	   c=getchar();
	}
	for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	x*=f;
}

void out(int x){//快输。
	if(x){
		out(x/10);
		putchar('0'+x%10);
	}
}

int main(){
	int n;
	in(n);
	for(int i=1;i<=n;i++) in(k[i]);
	for(int i=1;i<=n;i++) for(int j=1;j<=k[i];j++) in(m[i][j]);
	int mn=1<<30;//先把最小值放到最大。
	for(int i=1;i<=n;i++){
		int sum=0;
		for(int j=1;j<=k[i];j++){
			sum+=15;//每一次都要加15。
			sum+=m[i][j]*5;//每一个顾客要用的时间。
		}
		mn=std::min(mn,sum);//更新最小值。
	}
	printf("%d\n",mn);
	return 0;
}
```


---

## 作者：Firstly (赞：0)

看到题解区有些单调，所以这里给出一种用优先队列来完成的解题思路。

## **题目思路：**
------------
我们可以发现，每位顾客所用时间是其商品数量的 5 倍加 15 秒。即若某位顾客买了 $n$ 件商品，那么其所用时间为 $5n+15$ 秒。我们将每个队列中所有顾客所用时间的总和算出来，并且将其加入小根堆当中。这样，当所有队列都计算完毕时，最短时间就是优先队列的第一个元素。

## **Code：**
------------
```cpp
#include<iostream>
#include<queue>
using namespace std;
int n,k[105],m,sum;
priority_queue<int,vector<int>,greater<int> >q;//小根堆
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>k[i];
	for(int i=1;i<=n;i++){
		sum=0;
		for(int j=1;j<=k[i];j++){
			cin>>m;
			sum+=m*5+15;
		}q.push(sum);//将该队列用的时间添加到优先队列中
	}printf("%d",q.top());//直接输出堆顶元素即可
	return 0;
}
```


---

## 作者：fox_nice (赞：0)

最新修改：改了一点小瑕疵

~~又来水题解喽~~

大致题意是这样的：

超市收银台有 $n$ 个收银员，每位收银员都有 $k_i$ 个人，每个人结账时，需要花费的时间是手里的物品数的 $5$ 倍加上 $15$ 秒钟。求哪一条用时最短。

这道题乍一看数据范围，$( 1\le n\le 100 )$,$( 1\le k_{i}\le 100)$,$( 1\le m_{i,j}\le 100 )$ 直接暴力搜一遍就能过，很明显，这道题~~太水了~~是一道比较简单的数学题。

接下来上代码：

```cpp
#include <iostream>
using namespace std;
int main(){
    int n;
    cin >>n;
    int a[105];
    for(int i=0;i<n;i++){
        cin >>a[i];
    }
    int mi=0x7f7f7f7f;//用来存答案
    for(int i=0;i<n;i++){
        int sum=0;
        for(int j=0;j<a[i];j++){
            int s;
            cin >>s;
            sum+=s*5;
            sum+=15;//计算每位顾客所用时间
        }
        mi=min(mi,sum);//与最短时间进行比较
    }
    cout<<mi<<endl;//输出
}
```

~~又水完了一篇题解~~

---

