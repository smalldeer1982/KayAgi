# [RC-06] Operation Sequence

## 题目描述

给出 $n$，以及一个长度为 $n+1$ 的数组 $[a_1,a_2,\dots,a_{n+1}]$，初始时 $a_i=i\ (1\le i\le n)$，$a_{n+1}=0$。

你只能进行以下一种操作，通过输出特定字符串完成操作：

- 输出 `i j` ：其中 $i,j$ 为正整数，要求 $1\le i,j\le n+1$，表示把 $a_i$ 赋值为 $a_j$。

请把 $a$ 数组**的前 $n$ 位**向**右**循环移位 $K$ 位；即，在执行完毕你输出的所有操作后，要求 $a$ 数组第 $i\ (1\le i\le K)$ 位等于 $n-K+i$；第 $i\ (K+1\le i\le n)$ 位等于 $i-K$，第 $n+1$ 位任意。你只能进行至多 $T=\lfloor1.5n\rfloor$ 次赋值操作。

如果你进行的操作数多于 $T$ 也可以获得部分分，具体地，设你的操作次数为 $S$：

- 如果 $S\le T$，得 $100$ 分。
- 如果 $T<S\le 4T$，得 $50$ 分。
- 如果 $S>4T$，得 $0$ 分。

你在本题的得分是所有测试点中所有数据里得分的最小值。

## 说明/提示

所有数据均满足：$1\le T\le 10^4$，$1\le n\le 10^5$，$0\le K\le n-1$。保证同一个测试点中所有 $n$ 的和不超过 $5\times 10^5$。

## 样例 #1

### 输入

```
2
3 0
2 1```

### 输出

```
0
3
3 1
1 2
2 3```

# 题解

## 作者：JuRuoOIer (赞：7)

## 题解 P8910 [RC-06] Operation Sequence

~~这是蒟蒻在赛时唯一 AC 的题了……~~

### Part 1 题意

给定一个长度为 $n+1$ 的数组 ${1,2,3,...,n,0}$，你可以将其中任意一项赋上其它项的值，要求用不超过 $\lfloor 1.5n \rfloor$ 次操作将数组的**前 $n$ 项向右**循环移动 $k$ 位。

### Part 2 直击满分

我们随便举个例子：
![](https://cdn.luogu.com.cn/upload/image_hosting/whvinm0z.png)

从图中可以看到思路：先把 $1$ 放到最后的空位，然后看 $1$ 的位置，要放 $3$，于是填上 $3$，以此类推……一直到全部填完。

**难道这样就可以万事大吉吗？**

我们将 $n$ 改成 $6$，然后……

![](https://cdn.luogu.com.cn/upload/image_hosting/4lq5dw9m.png)

可以发现，走了三步就走完了，$2,3,5,6$ 这四个数根本就没动着。解决的办法也很简单，只需要在**发现之后，往右走一格**，并把这一项的内容塞到最后一项，继续填充即可。可以发现最后一项每赋值一次至少可以影响两项，所以不会超限。找找规律可以发现，赋值的次数应该是 $n\times \gcd(n,k)$ 的，当然像我赛时那样，先跑一遍数次数输出也可以。图解如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/5vv4xld0.png)

### Part 3 代码

注释在代码里啦！

```cpp
#include<iostream>
#define ll long long
using namespace std;
ll t,n,k,a[100010],p,s,bg;
ll gcd(ll x,ll y){//算次数用
	while(x%y){
		ll tmp=x;
		x=y;
		y=tmp%y;
	}
	return y;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		if(k==0){
			cout<<"0\n";
			continue;
		}
		for(int i=1;i<=k;i++){//预处理出最终状态
			a[i]=n-k+i;
		}
		for(int i=k+1;i<=n;i++){
			a[i]=i-k;
		}
		cout<<n+gcd(n,k)<<endl;
		cout<<n+1<<" 1\n";
		p=1;//多测不清空，爆零两行泪
		bg=1;
		s=0;
		while(s<n-1){//我把第 n 项放外边了
			if(a[p]!=bg){//没循环
				cout<<p<<' '<<a[p]<<endl;
				p=a[p];
			}
			else{//循环了
				cout<<p<<' '<<n+1<<endl;
				p=(p+1)%(n+1);//往右移动，模一下保证安全（别移出去了）
				bg=p;
				cout<<n+1<<' '<<p<<endl;
			}
			s++;
		} 
		cout<<p<<' '<<n+1<<endl;//处理第 n 项
	}
	return 0;
}

```

---

## 作者：zengyongxu (赞：1)

### 写在前面

::::warning[warning]
不要抄题解！
::::

认为是一道好题，特地来写写题解以回报自己一小时的战果。

### 思路

做完这道题，看了看楼下两篇题解，感觉我的代码像是两篇题解综合起来。

首先，看到这道题，首先想到的是部分分（是因为我太弱了）。

但是部分分没有啊！那就只好骗分，注意到 $k=0$ 或 $k = n$ 的时候答案一定是 0，于是特判一下。

~~但是我也不知道多少分。因为接下来我想到了正解。~~

接下来来思考正解。

手搓自己造的样例，发现这个 $a_{n+1}$ 非常重要，可以用来当临时使用。

那么，我们让任意一个数赋值到 $n+1$，不妨设为 1，令一个指针 $p$，初始指向 1，代表当前可以赋值为目标的地方。

那我们就可以不断地让当前数赋值为应该目标数，然后让 $p$ 指向目标数所在的下标。

但是，在手搓了自己又造了的几组略大的数据之后，发现好像会有一些问题诶。

可能会出现多个环，而不是理想状态下的 $p$ 指针一直移动最终全部赋值成目标值。

那么每次在发现环的时候就可以让 $p$ 指针随便指向一个地方就可以了，我这里让 $p$ 指针直接指向下一个地方。

### 代码实现 & 细节

首先，判断是否形成环。只需要存一个 $begin$ 指针，表示一个环的开头，一开始 $begin$ 指向 1，以后每次发现 $p = begin$ 的时候就形成了环，这是 $p$ 指针会指向下一个地方，而我们让 $begin$ 指向 $p$ 即可。

其次，形成环时需要实现的步骤：

1. 让当前 $a_p$ 赋值为 $a_{n + 1}$ 因为 $a_{n+1}$ 存储了 $a_{begin}$ 原本的值。
2. 移动 $p$ 指针，更新 $begin$ 指针。
3. 让 $a_{n+1}$ 赋值为 $a_p$ 这样才可以在下次发现形成环的时候正确的赋值。

这一部分的注意点是在第 3 步中，需要判断是不是还有需要修改的地方。可能不用，因为 $a_{n+1}$ 最终赋值什么值都可以。~~但是我懒没有尝试可不可以。~~

其他注意事项和小技巧：
1. 前面所说的骗分同时也是特判记得加上。
2. 可以直接用 `vector` 来存储答案，不需要楼下的 $n + \gcd(n,k)$。（当然我只是偷懒而已） ~~顺便吐槽：楼下怎么还把加法打成了乘法啊……~~

### 代码 & 代码解释

::::success[code]
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int t, n, k, to[N];

int gcd(int a, int b){
    return (!b ? a : gcd(b, a % b));
}

int main(){
    cin >> t;
    while (t -- ){
        cin >> n >> k;
        if (k == 0 || k == n){
            cout << "0\n";
            continue;
        }
        
        for (int i = 1; i <= n; i ++ ) to[i] = (i <= k ? n - k + i : i - k);

        vector <pair<int, int> > res;

        res.push_back({n + 1, 1});
        int now = 1, beg = 1, cnt = 0;
        while (cnt < n){
            if (to[now] != beg){
                res.push_back({now, to[now]});
                now = to[now];
            }
            else{
                res.push_back({now, n + 1});
                beg = now = now % n + 1;
                if (cnt != n - 1) res.push_back({n + 1, now});
            }
            cnt ++;
        }
        
        cout << res.size() << "\n";
        for (auto [i, j] : res) cout << i << " " << j << "\n";
    }
}
```
::::

代码解释：
1. 代码中的 $now$ 为文中的 $p$。
2. 代码中的 $beg$ 为文中的 $begin$。
3. 代码中的 $res$ 为文中小技巧部分所提到的记录答案的 `vector`。
4. 代码中的 $to$ 为存储目标值的数组。

---

## 作者：_Z_F_R_ (赞：0)

~~赛时唯一 AC 的题呢 QwQ。~~
***
### 思路

既然这个题目要我们循环向右移动 $k$ 位，那我们能不能考虑移动 1 位的情况呢？

$n=5,k=1$ 时：

初始状态：

1 2 3 4 5 0

第一步：

$a_6 \gets a_5$

1 2 3 4 5 5

第二到五步：

$a_5 \gets a_4$

$a_4 \gets a_3$

$a_3 \gets a_2$

$a_2 \gets a_1$

1 1 2 3 4 5

最后一步：

$a_1 \gets a_6$

5 1 2 3 4 5

回归向右移动 $k$ 位的情况。

我们不难发现，向右移动 $k$ 位相当于形成了若干个环（环内都是向右移动 1 位）。

例：

$n=5,k=3$ 时：

这一个环就为：

$a_1 \to a_4 \to a_2 \to a_5 \to a_3 \to a_1$

$n=6,k=3$ 时

这三个环就为：

$a_1 \to a_4 \to a_1$

$a_2 \to a_5 \to a_2$

$a_3 \to a_6 \to a_3$
***
### 代码

代码实现较简单，基本上是模拟，只需要注意 $k=0$ 时的特判。

于是，~~你们最喜欢的代码来了~~。

```cpp
#include<bits/stdc++.h>
using namespace std;

int mt[100005],mb[100005];//mt 是移到哪去，mb 是从哪来
bool vis[100005];
struct Ans
{
	int i,j;
}ans[500005];

void init_m(int n,int k)//预处理
{
	int i;
	for(i = 1;i <= n;i++)
		if(i <= k)
			mb[i] = n - k + i;
		else
			mb[i] = i - k;
	for(i = 1;i <= n;i++)
		mt[mb[i]] = i;
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,k,i,st;
		scanf("%d%d",&n,&k);
		init_m(n,k);
		if(k == 0)//特判
		{
			printf("0\n");
			continue;
		}
		memset(vis,0,sizeof(vis));
		int j = 0;
		for(st = 1;st <= n;st++)
		{
			if(vis[st])//在之前的某个环里
				continue;
			vis[st] = true;
			j++;
			ans[j].i = n + 1;
			ans[j].j = st;
			for(i = mb[st];i != st;i = mb[i])
			{
				j++;
				ans[j].i = mt[i];
				ans[j].j = i;
				vis[i] = true;
			}
			j++;
			ans[j].i = mt[i];
			ans[j].j = n + 1;
		}
		printf("%d\n",j);
		for(i = 1;i <= j;i++)
			printf("%d %d\n",ans[i].i,ans[i].j);
	} 
}
```

---

