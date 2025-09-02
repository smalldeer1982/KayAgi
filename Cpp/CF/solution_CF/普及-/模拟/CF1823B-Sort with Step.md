# Sort with Step

## 题目描述

给定一个 $1$ 到 $n$ 的排列 $p$ 和一个正整数 $k$。

你可以对 $p$ 进行若干次操作，每次操作交换 $p_i$ 和 $p_j$，其中 $|i-j|=k$。你的目标是使得 $p$ 变为升序。

除此之外，在开始你的操作之前，你还可以**预先交换**任意两个 $p_i$ 和 $p_j$ 一次。

你的任务是判断：

1. 能否在不用预先交换的情况下，使得 $p$ 变为升序；
2. 如果不能，能否在预先交换一次的情况下，使得 $p$ 变为升序。

## 说明/提示

$1\le t\le10^4$，$2\le n\le2\times10^5$，$1\le k\le n-1$，$1\le p_i\le n$。

每组数据的 $n$ 的总和 $\sum n\le2\times10^5$。

## 样例 #1

### 输入

```
6
4 1
3 1 2 4
4 2
3 4 1 2
4 2
3 1 4 2
10 3
4 5 9 1 8 6 10 2 3 7
10 3
4 6 9 1 8 5 10 2 3 7
10 3
4 6 9 1 8 5 10 3 2 7```

### 输出

```
0
0
1
0
1
-1```

# 题解

## 作者：__yrq__ (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF1823B)

思路：输入的每个 $ a_{i} $ 都应该在第 $i$ 个位置上，如果 $ a_{i} $ 不在第 $ i$ 个位置上，并且不满足 $|a_{i}-i| \bmod  k = 0$，需要预先交换，$s$ 就要加一。

如果 $s=0$，输出 $0$。

如果 $s=2$，输出 $1$。

如果 $s>2$，输出 $-1$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a[200005],s=0;//s代表需要预先交换的次数 
int main()
{
    cin>>t;
    while(t--)
    {
    	s=0;//初始化 
    	cin>>n>>k;
    	for(int i=1;i<=n;i++)
    	{
    		cin>>a[i];
    		if(a[i]!=i&&abs(a[i]-i)%k!=0) s++;//判断是否需要预先交换 
		}
		//判断三种情况，输出 
		if(s==0) cout<<"0\n";
		else if(s==2) cout<<"1\n";
		else if(s>2) cout<<"-1\n";
	}
    return 0;
}
```

---

## 作者：CheZiHe929 (赞：3)

#  CF1823B  Sort with Step题解
## 原题链接
[**洛谷CF1823B**](https://www.luogu.com.cn/problem/CF1823B)

## 题目大意
给你 $T$ 组测试样例，每组样例都会给你一个长度为 $n$ 的数列和一个模数 $k$，为了将这个数列相邻的两数的差为 $1$ 且为升序数列，你可以进行如下两个操作：
1. 任意交换一组 $a_i$ 和 $a_j$。
2. 在满足 $ | i - j | \bmod k = 0$ 的情况下交换 $a_i$ 和 $a_j$。

输出分三种情况：

- 当不需要执行第一种操作时输出 $0$。
- 当需要执行一次第一种操作时输出 $1$。
- 当需要执行一次以上第一种操作时输出 $-1$。

## 思路分析
既然是一个差为 $1$ 的等差数列，那我们每次循环输入的 $a$ 就应该排在第 $a$ 位上，所以我们只要比较 $a$ 输入时所在的位置以及应该排到的位置（即比较循环输入时枚举的 $i$ 和输入的数 $a$)。如果不满足 $|i-j| \bmod k=0$（此处 $j$ 即为 $a$)，那就要进行第一种操作，用来计数的 $cnt$ 就要加一。

- 如果 $cnt=0$，输出 $0$。
- 如果 $cnt=2$，输出 $1$（注意 $cnt$ 是不会等于 $1$ 的，因为既然要交换，那么就至少有两个数互相交换，也就是进行了一次交换操作）。
- 如果 $cnt>2$，输出 $-1$。

## CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){//测试组数T 
		int n,k;
		cin>>n>>k;
		int cnt=0;//每次需清空计数的cnt 
		for(int i=1;i<=n;i++){
			int a;
			cin>>a;//输入数列中第i个数 
			if(abs(i-a)%k!=0)//如果不满足方案二，则需执行方案一 
				cnt++; 
		}
		if(cnt==0)cout<<0<<endl;
		else if(cnt==2)cout<<1<<endl;
		else cout<<-1<<endl;//则为cnt>2 
	}
	return 0;
}
```

**无注释版的在[这里](https://www.luogu.com.cn/paste/pj7uo1oq)。**

## [AC 记录](https://www.luogu.com.cn/record/110473120)

**THE END.**

**THANK YOU.**

---

## 作者：I_am_kunzi (赞：2)

# CF1823B 题解

### 题目大意

给你 $ t $ 组测试数据，其中每组数据都有以下的输入输出：

> 一个 $ n $ 个数的排列和一个 $ p$，其中有 $ 1 $ ~ $ n $ 中的数，问你是否能在最初做最多一次操作 $ I$：

>> 找到最多一组 $ a_i $ 和 $ a_j $ 并交换。

> 的情况下，通过不限次数的操作：

>> 找到满足 $ | i - j | \bmod p = 0 $ 的 $ (i , j)$，交换 $ a_i $ 和 $ a_j $。

> 将这个排列变成 $ 1 $ ~ $ n $ 升序排列的样子呢？

> 如果可以通过 $ 0 $ 次操作 $ I $ 完成任务，输出 $ 0$；通过一次操作完成任务，输出 $ 1$；通过大于一次操作完成任务，输出 $ -1$。

其中，有 $ 1 \le t \le 10 ^ 4 , 1 \le n \le 2 \times 10 ^ 5 , 1 \le p \le n - 1 , \sum n \le 2 \times 10 ^ 5$。

### 题目分析

我们在循环读入排列时，可以判断下这个数 $ a $ 是否满足 $ | a - i | \bmod p = 0$，并用一个 $ cnt $ 统计有几个不满足的数，那么这些数就是需要用操作 $ I $ 换位置的，又注意到每一次操作会交换 $ 2 $ 个数。

所以如果 $ cnt = 0$，输出 $ 0$；如果 $ cnt = 2$，输出 $ 1$；如果 $ cnt > 2$，输出 $ -1$。

### 代码时间

```cpp
#include<iostream>
#include<cmath>
using namespace std;
signed main()
{
	int t; //t 为数据组数 
	cin >> t;
	while(t--) 
	{
		int n , q; //n 为排列长度，q 即为上文的 p 
		cin >> n >> q;
		int cnt = 0; //同上文 cnt 
		int a; //同上文 a 
		for(int i = 1 ; i <= n ; i++)
		{
			cin >> a;
			if((int) fabs(a - i) % q != 0) //判断是否需要操作 I 
			{
				cnt++;
			}
		}
		//上文所说的三种情况 
		if(cnt == 0)
		{
			printf("0\n");
		}
		else if(cnt == 2)
		{
			printf("1\n");
		}
		else
		{
			printf("-1\n");
		}
	}
    return 0;
}
```

---

## 作者：Otue (赞：1)

若一个序列的第 $i$ 个位置值为 $a_i$，那么升序排列后绝对在新序列的第 $a_i$ 个位置。即从第 $i$ 个位置变化到了第 $a_i$ 个位置。

由于他每次交换的数下标差值为 $k$，所以一定满足 $|a_i-i| ≡0 \pmod k$。但是对于所有的 $i$ 不一定都满足这样的条件，对于不满足的来说，就 **预先交换** 一次。最后根据 **预先交换** 次数输出答案即可。

不难注意到，只需要 **预先交换** 一次的，会在答案中统计两次。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int T, n, k, a[N];


int main() {
	cin >> T;
	while (T--) {
		cin >> n >> k;
		for (int i = 1; i <= n; i++) cin >> a[i];
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			if (abs(i - a[i]) % k != 0) cnt++;
		}
		if (cnt == 0) puts("0");
		else if (cnt == 2) puts("1");
		else puts("-1");
	}
}
```

---

## 作者：qwq_hwc (赞：0)

## 翻译
给定一个 $1$ 到 $n$ 的排列 $p$ 和一个正整数 $k$。

你可以对 $p$ 进行若干次操作，每次操作交换 $p_i$ 和 $p_j$，其中 $|i-j|=k$ 。你的目标是使得 $p$ 变为升序。

除此之外，在开始你的操作之前，你还可以**预先交换**任意两个 $p_i$ 和 $p_j$ 一次。

你的任务是判断：

1. 能否在不用预先交换的情况下，使得 $p$ 变为升序；
2. 如果不能，能否在预先交换一次的情况下，使得 $p$ 变为升序。

## 思路
创建一个变量 $cnt$ 来记录 $|i-j|$ $\bmod$ $k$ 是否等于 $0$ ，接着判断是否满足条件 $1$ 或 $2$ 。


# AC Code
```cpp
#include<cstdio>
#include<cmath>//绝对值abs的头文件
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){ //有多组数据
		int n,k;
		scanf("%d%d",&n,&k);
		int cnt=0; 
		for(int i=1;i<=n;i++){
			int a;
			scanf("%d",&a);
			if(abs(i-a)%k!=0) cnt++; 
		}
		if(cnt==0)printf("0\n");//如果等于0，则输出0
		else if(cnt==2)printf("1\n");//如果等于2，则输出1
		else printf("-1\n");//否则，输出-1
	}
	return 0;
}
```

---

## 作者：smydahaoren (赞：0)

CF1823B Sort with Step
------------

[原题 CF1823B 传送门](https://www.luogu.com.cn/problem/CF1823B)

**题目分析**：


------------

题目中给定 $T$ 组数据

在每组数据中：

- 第一行是数列的长度 $n$，以及模数 $k$。

- 第二行是乱序的一个公差为 $1$ 的等差数列。

然后做两个操作：

1. 交换一组数： $p_i$ 和 $p_j$，其中 $\lvert{i-j}\rvert\bmod k =0$。


1. 如果以上步骤不能让 $p$ 数列有序，那么可以交换一次 $p_i$ 和 $p_j$。（以下简称其为第二操作）

输出数据：

1. 如果不需要第二操作就可以让数列 $p$ 有序，则输出 $0$。

1. 需要第二操作后可以让数列 $p$ 有序，则输出 $1$。

1. 需要执行 $2$ 次及以上的第二操作后才让数列有序，输出 $-1$。

**思路分析**：


------------

因为数列公差为 $1$，所以交换的数的差和其编号一样都被 $k$ 整除，所以可得到： $\lvert p_i-p_j \rvert\bmod k=0$。

同时，因为输出的结果只和第二次操作次数有关，因此可以设置变量 $cnt$ 表示操作次数。

1. $cnt=0$ 时，即没有操作过第二操作，输出 $0$。

1. $cnt=2$ 时，因为两个数字交换时， $cnt$ 会计算两次，故这表示操作过第二操作  $1$ 次，输出 $1$。

1. $cnt>2$ 时，可以理解为做过 $1$ 次以上的第二操作，输出 $-1$。

**AC代码**：



------------
```c
#include<bits/stdc++.h>
using namespace std;
const int N=200009;
int p[N];
int n,k,t,cnt;
int main(){
	cin>>t;
	for(int q=0;q<t;q++){
		cnt=0;//不同样例需要清零统计结果
		memset(p,0,sizeof(p));//不同样例需要清零数组
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>p[i];
				if(abs(p[i]-i)%k!=0) //判断需要不需要第二操作
					cnt++;
		}
		switch(cnt){//以下判断输出结果
			case 0:
				cout<<0<<endl;break;
			case 2:
				cout<<1<<endl;break;
			default:
			cout<<-1<<endl;break;
		}
	}
	return 0;
} 
```


---

## 作者：kaceqwq (赞：0)

# 题目大意：
给定一个 $1$ 到 $n$ 的序列 $p$，和一个正整数 $k$。现要求对 $p$ 进行若干次操作，每次操作可以交换 $p_i$ 和 $p_j$，使得 $p$ 变成升序的。除此之外，在开始操作之前，你还可以预先交换任意两个 $p_i$ 和 $p_j$ 一次。

任务是判断：

1. 能否在不用预先交换的情况下，使得 $p$ 变为升序；

2. 如果不能，能否在预先交换一次的情况下，使得 $p$ 变为升序。

### 输出：
如果满足条件 $1$ 输出一行 $0$；

如果不满足条件 $1$ 但满足条件 $2$ 输出一行 $1$；

如果条件 $1$，$2$ 都不满足输出一行 $-1$。

# 思路：
是一道简单的题目，我们只需在输入序列时，判断 $\left\vert p_i - i \right\vert \bmod k$ 是否不等于零，然后用一个计数器累加，最后计数器的值即可判断能否满足条件 $1$，$2$。

# Code：
```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
int t, n, k, p[1000005], sum;
signed main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> t; //注意有多组数据
    while (t--) {
        sum = 0;
        cin >> n >> k;
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
            if (abs(i - p[i]) % k != 0) sum++; // sum累加
        }
        if (sum == 0) cout << 0 << '\n'; //如果为0，输出0
        else if (sum == 2) cout << 1 << '\n'; //如果为2， 输出1
        else cout << -1 << '\n'; //否则，输出-1
    }
    return 0;
}
```


---

## 作者：__Dist__ (赞：0)

### 题目大意

这题其实挺绕的，不过不难理解。给定 $ T $ 组测试数据，每组给定 $ N $ 和 $ k $，共 $ N $ 个数。问能不能通过 $ n $ 次交换第 $ i $ 个数 $ p $ 并且其满足 $ |p - i| \bmod k = 0 $，使数列有序。

如果 $ n = 0 $，输出 $ 0 $；如果 $ n = 1 $，输出 $ 1 $；如果 $ n > 1 $，输出 $ -1 $。

### 思路分析

我们只要循环输入 $ p $ 并判断即可。第 $ i $ 次输入我们要找到不符合 $ |p-i| \bmod k = 0 $ 的数，用 $ cnt $ 计数。最终，因为需要交换的数是成对出现的，所以 $ cnt $ 一定是偶数。所以，如果 $ cnt = 0 $ 就意味着不需要交换，输出 $ 0 $；如果 $ cnt = 2 $ 就需要交换一次，输出 $ 1 $；若 $ cnt > 2 $ 就意味着多于一对，要输出 $ -1 $。

### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int main(){
	cin>>T;
	while(T--){
		int cnt=0;//计数
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			int p;
			cin>>p;
			if(abs(p-i)%k!=0) ++cnt;//找到不符合条件的
		}
        //分情况输出
		if(cnt==0) cout<<0;
		else if(cnt==2) cout<<1;
		else cout<<-1;
		puts("");
	}
	return 0;
}
```

 $ AC $ [链接](https://www.luogu.com.cn/record/109885690)。

---

## 作者：_5t0_0r2_ (赞：0)

upd on 2023.8.6 代码中的花括号没删干净，导致提交会出现 CE 的情况，现已修复。

# 分析；
对于任意数 $i$，排序后它就应该在第 $i$ 位上。假设 $i$ 此时在第 $j$ 位，那么 $j$ 应满足 $|j - i| \bmod k = 0$（$|j - i|$ 表示数 $i$ 现在的位置与应该在的位置的距离，这个距离应该是 $k$ 的倍数）。

我们将不符合上述要求的数的个数统计出来，如果个数为 $0$，就不需要提前交换；如果个数为 $2$（只可能是偶数个），就需要提前交换；如果个数大于 $2$，就不能排序好。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,tmp,cnt;
int main(){
	scanf("%d", &t);
	for(int i = 1;i <= t;i++){
		cnt = 0;//每次处理完一组数据后将计数器清空
		scanf("%d%d", &n, &k);
		for(int j = 1;j <= n;j++){
			scanf("%d", &tmp);
			if(abs(tmp - j) % k != 0)
				cnt++;//统计个数
		}
		if(cnt == 0)
			puts("0");
		else if(cnt == 2)
			puts("1");
		else if(cnt > 2)
			puts("-1");
	}
}
```


---

## 作者：rmzls (赞：0)

### 思路

很显然，只有每个数当前的位置与应在的位置的差被 $k$ 整除的时候才可以不用第二种操作。  
先全部扫一遍数组，看有几个数不符合上面的情况，将其记录下来。要是不符合上述条件的数的个数超过 $2$ 便无解，否则将不符合的两个换位后再检查一遍，看是否符合上述情况，符合的话便输出 $1$。

------------

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t,n,k,a[N],cnt;
struct node{
	int p,num;
}q[N];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++){
        	scanf("%d",&a[i]);
        	if(abs(a[i]-i)%k!=0){
        		node m;m.num=a[i];m.p=i;
        		q[++cnt]=m;
			}
		}
		if(cnt>2){
			printf("-1\n");
		}
		else if(cnt==0){
			printf("0\n");
		}
		else{
			if(abs(q[1].num-q[2].p)%k==0&&abs(q[2].num-q[1].p)%k==0){
				printf("1\n");
			}
			else{
				printf("-1\n");
			}
		}
		cnt=0;
    }
    return 0;
}
```


---

