# Elections

## 题目描述

三名候选人参加竞选 。第一名候选人得到了 $a$ 票，第二名候选人得到了 $b$ 票，第三名候选人得到了 $c$ 票 。对于每一个候选人，解决以下问题 ：

至少给该候选人增加多少票，使得该候选人的票数严格大于其它候选人？

注意，每个问题是独立存在的 。

## 样例 #1

### 输入

```
5
0 0 0
10 75 15
13 13 17
1000 0 0
0 1000000000 0```

### 输出

```
1 1 1
66 0 61
5 5 0
0 1001 1001
1000000001 0 1000000001```

# 题解

## 作者：智子 (赞：2)

## 题意

三个人参加投票选举，分别得到了 $a$ 票、 $b$ 票和 $c$ 票。求每个人至少还要得到多少票才能比另外两个人得到的票都多。(每个人需要多得到的票数独立计算，不会互相影响。)

## 思路

对于第一个人，检查 $a$ 是否大于 $\max\{b, c\}$，如果大于就不需要多得到投票，否则需要多得到 $\max\{b, c\} - a + 1$ 票。（之所以要 `+1` 是因为必须比别人得票多而不是和别人得票相等。）

第二个人、第三个人同理。

## 代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    int a, b, c, T;

    cin >> T;
    while(T--) {
        cin >> a >> b >> c;

        if(a > max(b, c)) {
            cout << 0 << " ";
        } else {
            cout << max(b, c) - a + 1 << " ";
        }
        if(b > max(a, c)) {
            cout << 0 << " ";
        } else {
            cout << max(a, c) - b + 1 << " ";
        }
        if(c > max(b, a)) {
            cout << 0 << " ";
        } else {
            cout << max(b, a) - c + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
```

---

## 作者：little_cindy (赞：1)

第一次在线打CF，一遍就AC了。感觉是个签到题。
## 思路
对于每个人，如果他的票数已经大于另外两个人的票数，则输出 $0$，否则输出另外两个人票数的最大值加 $1$ 的和，再减去他的票数便是他的答案。

如果我们用 $x$ 表示当前的这个人，$y,z$ 分别表示另外的两个人，$ans$ 表示答案，那么：

$$
ans=\begin{cases}\max\begin{cases}y\\z\end{cases}+1-x(x\le\max\begin{cases}y\\z\end{cases})\\0(x>\max\begin{cases}y\\z\end{cases})\end{cases}
$$

写成一个函数是：
```cpp
int get_ans(int x,int y,int z){
	int maxn=(y>z)?y:z;
	if(x>maxn){
		return 0;
	}
	else{
		return maxn+1-x;
	}
}
```
## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
#define inl inline
#define Ofast ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
int t;
void make(int x,int y,int z){
	int maxn=(y>z)?y:z;
	if(x>maxn){
		cout<<0;
	}
	else{
		cout<<maxn+1-x;
	}
	cout<<' ';
}
int main() {
	cin>>t;
	while(t--){
		int a,b,c;
		cin>>a>>b>>c;
		make(a,b,c);
		make(b,a,c);
		make(c,a,b);
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：feicheng (赞：1)

## A. Elections



### Task

给定 $a,b,c$，对每一个数求出至少要加多少才能使这个数**大于**剩下两个数。

多测。

**限制**：$0\leq a,b,c\leq 10^9,1\leq t\leq 10^4$

### Solution

设最大值为 $\text{mx}$，如果这个数是最大值且唯一，则答案为 $0$，若不唯一，则答案为 $1$，如果不是最大值，设其为 $p$，则需要加上 $\text{mx} - p+1$。

时间复杂度：$\mathcal O(t)$

---

## 作者：Forever1507 (赞：0)

题意：

$t$ 组测试数据，每组给你 $a,b,c$ 三个数，求对于每一个数，若想严格大于其他两个，最少需要增加多少。

显然的结论题，红题差不多了。对于数 $i$，如果 $i$ 是最大值且没有与之相同的数，答案为 $0$。如果有相同就是 $1$，如果不是最大值就是与最大值的差再加上一完事。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int a1,a2,a3,t;
int main(){
	cin>>t;
	while(t--){
		cin>>a1>>a2>>a3;
		if(a1>a2&&a1>a3)cout<<0<<' ';
		else cout<<max(a2,a3)-a1+1<<' ';
		if(a2>a1&&a2>a3)cout<<0<<' ';
		else cout<<max(a1,a3)-a2+1<<' ';
		if(a3>a2&&a1<a3)cout<<0<<' ';
		else cout<<max(a2,a1)-a3+1<<' ';
		puts("");
	}
	return 0;
}
```


---

## 作者：sycqwq (赞：0)

__题意：__

给你 $3$ 个数 $a$，$b$，$c$ 让你求出 $a$，$b$，$c$ 分别加上多少使它成为这 $3$ 个数中的严格最大值。

__思路：__

如果是最大值，而不是严格最大值的话，很好解决。

只需分别输出 $\max(a,b,c)-a$、$\max(a,b,c)-a$、$\max(a,b,c)-a$ 就可以了。

严格最大值的话，考虑两种情况

1.  当 $\max(a,b,c)$ 是严格最大值时，即若 $a=\max(a,b,c)$ 时，$b,c\neq \max(a,b,c)$

    此时，如果一个数等于 $\max(a,b,c)$，则输出 ```0```。

    否则输出 $\max(a,b,c)$ 与该数的差加一。

2. 当 $\max(a,b,c)$ 不是严格最大值时，即若 $a=\max(a,b,c)$ 时，$b=\max(a,b,c)$ 或者 $c=\max(a,b,c) $

   此时，因为如果这个数它等于 $\max(a,b,c)$ 时，它也不是严格最大值，所以 对于任意数，需要输出 $\max(a,b,c)$ 与该数的差加一。

__代码：__

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main()
{
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        int n=max(a,max(b,c));
        if(a==n&&b==n||a==n&&c==n||c==n&&b==n||a==n&&b==n&&c==n)//第二种情况
        {
            cout<<n-a+1<<' '<<n-b+1<<' '<<n-c+1<<endl;
        }
        else//第一种情况
        {
            cout<<(a==n?0:n-a+1)<<' '<<(b==n?0:n-b+1)<<' '<<(c==n?0:n-c+1)<<endl;
        }
    }
    return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15408845.html)

$\rm upd~on~2021/10/17:$ 改良了 $\LaTeX$ 和 【滥用粗体】 的情况。

# 题目大意

给定 $T$，表示输入数据的个数。

对于每组数据：

给定三个整数 $a,b,c$，分别求出要想让每个数比另外两个数大的最少操作次数。

**注意，每次操作是独立的。**

定义一次操作为让指定数加一。

例如样例 `1 2 2`

依次考虑：

对于 $1$，要想让 $1>max(2,2)$，输出 $2$。

对于 $2$，要想让 $2>max(1,2)$，输出 $1$。

对于 $2$，同上。

翻译 $\rm By~$[$\rm\color{black} Coros~Trusds.$](https://www.luogu.com.cn/user/430409)

# 题目分析

签到题。

翻译很良心（

对于每组数据，我们只需要输出除当前讨论数之外的两个数的最大值 $+1$ 与当前讨论数的差即可。

有点绕，形象化一点：

有三个数 $a,b,c$，讨论 $a$ 时，答案即为 $\max(b,c)+1-a$。

于是就没有了。

# 代码

```cpp
inline int solve(int a,int b,int c)
{
	if(a>b && a>c)
	{
		return 0;
	}
	
	return max(b,c)+1-a;
}

int main(void)
{
	int T=read();
	
	while(T--)
	{
		int a=read(),b=read(),c=read();
		
		printf("%d %d %d\n",solve(a,b,c),solve(b,a,c),solve(c,a,b));
	}
	
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

这道题就是个模拟。

假设我们要考虑的候选人手里有 $a$ 票，别人手里分别有 $b$ 票和 $c$ 票。

设 $s$ 为 $\operatorname{max}(a,b,c)$

如果 $s=a$，如果 $s=b\operatorname{or}s=c$，则还需要 $1$ 票；否则不需要票。

否则，需要 $s-a+1$ 票。

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
int t;
int a,b,c;
int s;
int ma(int a,int b){
	return a>b?a:b;
}
int mi(int a,int b){
	return a<b?a:b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1593A_1.in","r",stdin);
	freopen("CF1593A_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&a,&b,&c);
		int s=ma(a,ma(b,c));
		if(s==a){
			if(s==b||s==c)printf("1 ");
			else printf("0 ");
		}
		else printf("%d ",s-a+1);
		if(s==b){
			if(s==a||s==c)printf("1 ");
			else printf("0 ");
		}
		else printf("%d ",s-b+1);
		if(s==c){
			if(s==a||s==b)printf("1 ");
			else printf("0 ");
		}
		else printf("%d ",s-c+1);
		printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/59838954)

By **dengziyue**

---

## 作者：ttq012 (赞：0)

这道题是一个简单的模拟题

很容易发现：对于一个数 $a$，让它严格大于另外的两个数 $b$ 和 $c$，那么它就一定严格大于 $\max(b, c)$

所以，让数 $a$ 严格大于另外的两个数 $b$ 和 $c$ 的公式就是：$\max(0, \max(b, c) - a + 1)$

然后，数 $b$ 和数 $c$ 的公式也是一样的，所以使用这一个公式也能求解出来答案。

**上代码**

```cpp
#include <iostream>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t --)
    {
        int a, b, c;
        cin >> a >> b >> c;
        cout << max(0, max(b, c) - a + 1) << ' ' << max(0, max(a, c) - b + 1) << ' ' << max(0, max(a, b) - c + 1) << endl;
    }
    return 0;
}

```


---

## 作者：PHarr (赞：0)

若三个数相同，答案都是一

若两个数相等大于第三个，相等两数答案为一，第三数答案是大数减小数加一

若一个数严格大于另外两数，最大数为零两个小数为大数减小数加一

```cpp
#include <bits/stdc++.h>
using namespace std;

int n , a , b , c ;


int main()
{
    cin >> n;
    for( register int i = 1 ; i <= n ; i ++ )
    {
        cin >> a >> b >> c;
        if( a == b && b == c ) printf("1 1 1\n");
        else if( a == b && a > c ) printf("1 1 %d\n" , a - c + 1 );
        else if( a == c && a > b ) printf("1 %d 1\n" , a - b + 1 );
        else if( b == c && b > a ) printf("%d 1 1\n" , b - a + 1 );
        else if( a > b && a > c ) printf("0 %d %d\n" , a - b + 1 , a - c + 1 );
        else if( b > a && b > c ) printf("%d 0 %d\n" , b - a + 1 , b - c + 1 );
        else printf("%d %d 0\n" , c - a + 1 , c - b + 1 );
    }
    return 0;
}
```


---

