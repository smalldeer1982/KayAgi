# [NERC 2022] Football

## 题目描述

科学家们正在研究足球比赛结果对球迷情绪的影响。他们有一个假设，即平局的数量与球迷未来观看足球比赛的意愿之间存在关联。

在足球比赛中，两支球队进行一场比赛。球队在整场比赛中进球得分。比分“$x$ $\tt{:}$ $y$”表示我们观察的球队打进了 $x$ 个球，并丢了 $y$ 个球。如果 $x = y$，则比赛以平局结束。如果 $x > y$，则被观察的球队获胜，如果 $x < y$，则该队告负。

为了找出是否存在这种关联，科学家们收集了关于低级别联赛中球队赛果的信息。他们找到的信息是该队参加的比赛场数 ($n$)、在这些比赛中的总进球数 ($a$) 以及总失球数 ($b$)。

现在给你一支球队的这些信息。你需要计算该队比赛中可能发生的最小平局次数，并提供一个在该最小平局次数下所有比赛的比分列表。


## 说明/提示

翻译由 gemini2.5pro 完成

## 样例 #1

### 输入

```
3
2
4```

### 输出

```
0
1:0
1:2
0:2```

## 样例 #2

### 输入

```
1
2
2```

### 输出

```
1
2:2```

## 样例 #3

### 输入

```
4
0
7```

### 输出

```
0
0:1
0:2
0:1
0:3```

## 样例 #4

### 输入

```
6
3
1```

### 输出

```
2
0:0
1:0
0:0
0:1
1:0
1:0```

# 题解

## 作者：alice_c (赞：2)

## 题意

球队参加了 $n$ 场比赛，已知总进球数 $a$，总失球数 $b$，求最少平局次数和具体方案。

## 思路

一道构造题，分类讨论：

1. $n=1$，只有一场比赛。我们决定不了能平局几次。直接输出比赛结果即可，如果 $a=b$ 则平局次数为 $1$，否则为 $0$。

2. $a+b<n$，进球数加上失球数少于比赛次数。这说明肯定有几场比赛是 $0:0$ 平局。为了让平局次数尽可能少，我们让其他那些比赛为 $1:0$ 或 $0:1$。最多只能有 $a$ 场 $1:0$，$b$ 场 $0:1$，剩下 $n-a-b$ 场都是 $0:0$ 平局。

3. $a+b≥n$。肯定可以构造出一种没有平局的方案。这种情况还可以分成两种：
   1. $a=0$ 或 $b=0$。所有比赛都是 $0:x$（当 $b=0$ 时是 $x:0$)，其中 $x>0$。
   2. 否则，我们先把最后两场比赛预留成 $1:0$ 和 $0:1$。我们让前 $n-2$ 场比赛全都变成 $1:0$ 或 $0:1$，然后把剩余的进球和失球分配给最后两场比赛。

## 代码

```cpp
#include <cstdio>
int n,a,b;
int main()
{
    scanf("%d%d%d",&n,&a,&b);
    if(n==1){//情况一
        if(a==b) printf("1\n");
        else printf("0\n");
        printf("%d:%d",a,b);
    }
    else if(a+b<n){//情况二
        printf("%d\n",n-a-b);
        for(int i=1;i<=a;i++) printf("1:0\n");
        for(int i=1;i<=b;i++) printf("0:1\n");
        for(int i=1;i<=n-a-b;i++) printf("0:0\n");
    }
    else{//情况三
        printf("0\n");
        if(!a){
            for(int i=1;i<n;i++)
                printf("0:1\n");
            printf("0:%d",b-(n-1));
        }
        else if(!b){
            for(int i=1;i<n;i++)
                printf("1:0\n");
            printf("%d:0",a-(n-1));
        }
        else{
            a--,b--;//先预留 1:0 和 0:1 最后两场比赛
            for(int i=1;i<=n-2;i++){
                if(a>0){
                    printf("1:0\n");
                    a--;
                }
                else{
                    printf("0:1\n");
                    b--;
                }
            }
            printf("%d:0\n0:%d",a+1,b+1);//注意需要+1
        }
    }
}
``````

---

求过qwq！

---

## 作者：wenhaoran11 (赞：2)

## 题目简介：

一支足球比赛在 $n$ 场比赛中，进了 $a$ 个球，丢了 $b$ 个球，问最少的平局数量。

## 分类讨论

1. $n=1$ 等情况下，如果 $a=b$ 说明有一场平局，`cout<<1`，否则 `cout<<0`。

2. 第二种必有平局的情况：$a+b<n$，可以构造出 $a$  个 $1:0$，$b$ 个 $0:1$，$n−a−b$ 个 $0:0$ 三种情况，也就是有 $n−a−b$ 个平局。

3. 没有任何的平局情况，有三种构造方法。
    1. $b=0$ ,构造 $n−1$ 个 $1:0$ 和一个 $n−a+1:0$。
    2. $a<n−1$,构造 $0:a+b−n+1$ 和一个 $a$ 个 $1:0$，$n−a−1$ 个 $0:1$。
    3. 如果两个都不是，构造 $n−2$ 个 $1:0$，一个 $0:b$ ,和一个 $a−n+2:0$。
---
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b;
int main(){
	cin>>n>>a>>b;
	if(n==1){//第一种情况
		if(a==b) cout<<1<<"\n"<<a<<':'<<b<<"\n";
		else cout<<0<<"\n"<<a<<':'<<b<<"\n";
	}else if(a+b<n){//第二种情况
		printf("%d\n",n-a-b);
		for(int i=1;i<=a;i++){
			puts("1:0");
		}
		for(int i=1;i<=b;i++){
			puts("0:1");
		}
		for (int i=1;i<=n-a-b;i++) {
			puts("0:0");	
		}
	}else{//第三种情况
		cout<<"0\n";
		if(b==0){
		    for(int i=1;i<n;i++){
				puts("1:0");
			}
		    printf("%d:0",a-n+1);
		}else if(a<n-1) {
		    for(int i=1;i<=a;i++){
				puts("1:0");
		    }
			for(int i=1;i<=n-a-1;i++){
				puts("0:1");
			}
		    printf("0:%d",a+b-n+1); 
		}else{
		    for(int i=1;i<n-1;i++){
				puts("1:0");
			}
		    printf("%d:0\n0:%d",a-n+2,b); 
		}
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

# [P12795 [NERC 2022] Football](https://www.luogu.com.cn/problem/P12795)
## 题目介绍：
一支队伍有 $n$ 场比赛，进了 $a$ 个球，丢了 $b$ 个球，求最少平局数量。

## 分析做法：
构造题。

可以分为三种情况：

第一种情况，只比赛了一场，也就是说 $n$ 等于 $1$，此时如果 $$a = b$$，那就是 $1$ 场平局，否则是 $0$ 场平局，最后再输出最后再输出比分即可。

```cpp
if (n == 1) {
		if (a == b) cout << 1 << endl << a << ":" << b << endl;
		else cout << 0 << endl << a << ":" << b << endl;
	}
```

第二种情况，$a + b < n$，此时必有平局。

开始构造：
1. 构造 $a$ 个 $1 : 0$。

2. 构造 $b$ 个 $0 : 1$。

3. 构造 $n - a - b$ 个 $0 : 0$。

也就是说一共有 $n - a - b$ 个平局。

```cpp
else if (a + b < n) {
		cout << n - a - b << endl;
		for (int i = 1; i <= a; i++) {
			cout << 1 << ":" << 0 << endl;
		}
		for (int i = 1; i <= b; i++) {
			cout << 0 << ":" << 1 << endl;
		}
		for (int i = 1; i <= n - a - b; i++) {
			cout << 0 << ":" << 0 << endl;		
		}
	}
```

第三种情况，在除前两种情况下，必定没有平局，但依旧有三种情况。

开始三种情况的构造：
1. 如果 $$b = 0$$，构造 $n − 1$ 个 $1 : 0$ 和一个 $n − a + 1 : 0$。

2. 如果 $a < n − 1$ 时，构造 $a$ 个 $1 : 0$，$n − a − 1$ 个 $0 : 1$ 和一个 $0 : a + b − n + 1$。

3. 否则构造 $n − 2$ 个 $1 : 0$，一个 $a - n + 2 : 0$ 和一个 $0 : b$。

```cpp
else {
		cout << 0 << endl;
		if (b == 0) {
		    for(int i = 1; i < n; i++) {
				cout << 1 << ":" << 0 << endl;
			}
		    cout  << a - n + 1 << ":" << 0 << endl;
		} else if (a < n - 1) {
		    for(int i = 1; i <= a; i++) {
				cout << 1 << ":" << 0 << endl;
		    }
		    for(int i = 1; i <= n - a - 1; i++) {
				cout << 0 << ":" << 1 << endl;
			}
		    cout << 0 << ":" << a + b - n + 1 << endl;
		} else {
		    for(int i = 1; i < n - 1; i++) {
				cout << 1 << ":" << 0 << endl;
			}
		    cout << a - n + 2 << " " << 0 << endl;
		    cout << 0 << ":" << b << endl;
		}
	}
```

谢谢观看，求过求赞。

---

## 作者：yuxinrui0618 (赞：1)

# 题解：P12795 [NERC 2022] Football
## 1. 题目大意
- 给定比赛场数，总进球数和总失球数，输出一种平局场数最少的得分方案。

## 2. 思路
- 分类讨论：
- 如果只有一场比赛（即 $n$ 为 1），那么只需要构造 $a:b$ 即可；
- 如果 $a+b<n$，就一定有平局比赛，而且一定是 $n-a-b$ 场，这是只需要构造 $a$ 个 $1:0$，$b$ 个 $0:1$ 和 $n-a-b$ 个 $1:1$ 即可；
- 剩下的情况一定没有平局，这时候就又要分类讨论了：第一种情况，没有失球（即 $b$ 为 0），那么只需要构造 $n$ 个 $1:0$ 即可；第二种，$a<n-1$，这时只需构造 $a$ 个 $1:0$，$n-a-1$ 个 $0:1$ 和一个 $0:(a+b-n+1)$ 即可；剩下的情况（即 $a=n-1$），只需构造 $n-2$ 个 $1:0$，一个 $(a+b-n+1):0$ 和一个 $0:b$ 即可。

## 3. 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int n,a,b;
    cin>>n>>a>>b;
    if (n==1)
    {
    	if (a==b) cout<<1;
    	else cout<<0;
    	cout<<endl<<a<<":"<<b<<endl;
	}
	else if (a+b<n)
	{
		cout<<n-a-b<<endl;
		for (int i=1;i<=a;i++)
			cout<<"1:0"<<endl;
		for (int i=1;i<=b;i++)
			cout<<"0:1"<<endl;
		for (int i=1;i<=n-a-b;i++)
			cout<<"0:0"<<endl;
	}
	else
	{
		cout<<0<<endl;
		if (b==0) 
		{
			for (int i=1;i<=n-1;i++)
				cout<<"1:0"<<endl;
			cout<<a-n+1<<":0"<<endl;
		}
		else if (a<n-1)
		{
			for (int i=1;i<=a;i++)
				cout<<"1:0"<<endl;
			for (int i=1;i<=n-a-1;i++)
				cout<<"0:1"<<endl;
			cout<<"0:"<<a+b-n+1<<endl;
		}
		else 
		{
			for (int i=1;i<=n-2;i++)
				cout<<"1:0"<<endl;
			cout<<a+b-n+1<<":0"<<endl;
			cout<<"0:"<<b<<endl;
		}
	}
    return 0;
}
```

## 4. 总结
谢谢观赏！  
如有问题和建议还请各位大佬指出！

---

## 作者：大宝和小宝 (赞：0)

### 题解：P12795 [NERC 2022] Football

题意：

在 $n$ 场比赛中，踢进 $a$，个球，踢丢 $b$ 个球。

题目要求求出最小平局数并输出一个比分列表，满足有 $d$ 场平局，其他比赛非平局。

主要思路：
观察可以发现平局场次的进球和失球数必须相等，即每场平局消耗的 $a$ 和 $b$ 相同。所以剩余比赛需分配剩余的 $a' = a - sum(x_i)$ 和 $b' = b - sum(y_i)$，且所有非平局比赛必须满足 $x_i ≠ y_i$。


```cpp

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,a,b;
    cin>>n>>a>>b;
    
    // 单场比赛情况
    if(n==1){
        if(a==b) cout<<"1\n"<<a<<':'<<b<<"\n";
        else cout<<"0\n"<<a<<':'<<b<<"\n";
    }
    // 总进球数不足n场的情况
    else if(a+b<n){
        cout<<n-a-b<<"\n";
        for(int i=1;i<=a;i++) puts("1:0");
        for(int i=1;i<=b;i++) puts("0:1");
        for(int i=1;i<=n-a-b;i++) puts("0:0");
    }
    // 正常情况
    else{
        cout<<"0\n";
        // 无失球情况
        if(b==0){
            for(int i=1;i<n;i++) puts("1:0");
            printf("%d:0",a-n+1);
        }
        // 进球数不足n-1场
        else if(a<n-1){
            for(int i=1;i<=a;i++) puts("1:0");
            for(int i=1;i<=n-a-1;i++) puts("0:1");
            printf("0:%d",b-(n-a-1));
        }
        // 一般情况
        else{
            for(int i=1;i<n-1;i++) puts("1:0");
            printf("%d:0\n0:%d",a-(n-2),b);
        }
    }
    return 0;
}

```

---

## 作者：TCY1234567 (赞：0)

### 题意

有一支球队，共参加了 $n$ 场比赛，已知进球数为 $a$，失球数为 $b$，求最少平局次数并输出一种具体方案。

### 解析

显然是一道构造题，于是考虑分类讨论。

当 $n=1$ 时，比分只能是 $a$ 比 $b$，判断一下就完事了。

然后当 $a+b<n$ 时，一定会有平局。所以想让平局数最少，肯定是要用最少的球数去完成一局，所以说一共有 $n-a-b$ 局是 $0:0$ 平局，其它就是 $a$ 局的 $1:0$ 和 $b$ 局的 $0:1$。

最后就是 $a+ b \ge n$ 时，$a=0$ 或 $b=0$ 显然是好做的，如果 $a$ 和 $b$ 都不等于 $0$，可以在前 $n-2$ 局中分配 $0:1$ 和 $1:0$，最后把剩余的分配给最后两场比赛即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a,b;
void solve1()// a = 0 时
{
	for(int i=1;i<=n-1;i++) puts("0:1");
	printf("0:%d",b-n+1);
}
void solve2()// b = 0 时
{
	for(int i=1;i<=n-1;i++) puts("1:0");
	printf("%d:0",a-n+1);
}
void solve3()
{
	for(int i=1;i<=n-2;i++)
	{
		if(a>1)//这里一定要是大于 1，不然 a 会减成 0，就会错
		{
			puts("1:0");
			a--;
		}
		else
		{
			puts("0:1");
			b--;
		}
	}
	printf("%d:0\n",a);
	printf("0:%d",b);
}
int main()
{
	scanf("%d%d%d",&n,&a,&b);
	if(n==1)
	{
		if(a==b) puts("1");
		else puts("0");
		printf("%d:%d",a,b);
	}
	else if(a+b<n)
	{
		int p = n-a-b;
		printf("%d\n",p);
		for(int i=1;i<=a;i++) puts("1:0");
		for(int i=1;i<=b;i++) puts("0:1");
		for(int i=1;i<=p;i++) puts("0:0");
	}
	else
	{
		puts("0");
		if(a==0||b==0)
		{
			if(a==0)
				solve1();
			else
				solve2();
		}
		else
		{
			solve3();
		}
	}
}
```

---

## 作者：违规用户名1058825 (赞：0)

当 $n=1$ 时，被逼无奈只可能是 $a:b$。

当 $a=b$ 时平局数为 $1$;  
否则平局数为 $0$。

```cpp
if(n==1)printf("%d\n%d:%d",a==b,a,b);
```

- - -

当 $a+b<n$ 此时平局数被逼无奈不能为 $0$。

构造 $a$ 个 $1:0$，$b$ 个 $0:1$，$n-a-b$ 个 $0:0$。

平局数为 $n-a-b$。

可以证明以上做法是最优的。

```cpp
if(a+b<n){
    printf("%d\n",n-a-b);
    for(int i=1;i<=a;i++)puts("1:0");
    for(int i=1;i<=b;i++)puts("0:1");
    for(int i=1;i<=n-a-b;i++)puts("0:0");
}
```

- - -

剩下的最小平局数一定为 $0$。

当 $b=0$ 时，构造 $n-1$ 个 $1:0$ 和一个 $n-a+1:0$。

当 $a<n-1$ 时，构造 $a$ 个 $1:0$，$n-a-1$ 个 $0:1$ 和一个 $0:b-(n-a-1)$（$0:a+b-n+1$）。

否则构造 $n-2$ 个 $1:0$，一个 $a-(n-2):0$（$a-n+2:0$），一个 $0:b$。

**如果直接进行后两步判断会出现 $0:0$。**

```cpp
puts("0");
if(b==0){
    for(int i=1;i<n;i++)puts("1:0");
    printf("%d:0",a-n+1);
}else if(a<n-1){
   for(int i=1;i<=a;i++)puts("1:0");
   for(int i=1;i<=n-a-1;i++)puts("0:1");
   printf("0:%d",a+b-n+1); 
}else{
   for(int i=1;i<n-1;i++)puts("1:0");
   printf("%d:0\n0:%d",a-n+2,b); 
}
```
- - -
时间复杂度 $O(n)$。

---

