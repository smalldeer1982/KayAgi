# Johnny and His Hobbies

## 题目描述

Among Johnny's numerous hobbies, there are two seemingly harmless ones: applying bitwise operations and sneaking into his dad's office. As it is usually the case with small children, Johnny is unaware that combining these two activities can get him in a lot of trouble.

There is a set $ S $ containing very important numbers on his dad's desk. The minute Johnny heard about it, he decided that it's a good idea to choose a positive integer $ k $ and replace each element $ s $ of the set $ S $ with $ s \oplus k $ ( $ \oplus $ denotes the [exclusive or](https://en.wikipedia.org/wiki/Exclusive_or#Computer_science) operation).

Help him choose such $ k $ that Johnny's dad will not see any difference after his son is done playing (i.e. Johnny will get the same set as before playing). It is possible that no such number exists. It is also possible that there are many of them. In such a case, output the smallest one. Note that the order of elements in a set doesn't matter, i.e. set $ \{1, 2, 3\} $ equals to set $ \{2, 1, 3\} $ .

Formally, find the smallest positive integer $ k $ such that $ \{s \oplus k | s \in S\} = S $ or report that there is no such number.

For example, if $ S = \{1, 3, 4\} $ and $ k = 2 $ , new set will be equal to $ \{3, 1, 6\} $ . If $ S = \{0, 1, 2, 3\} $ and $ k = 1 $ , after playing set will stay the same.

## 说明/提示

In the first test case, the answer is $ 1 $ because it is a minimum positive integer and it satisfies all the conditions.

## 样例 #1

### 输入

```
6
4
1 0 2 3
6
10 7 14 8 3 12
2
0 2
3
1 2 3
6
1 4 6 10 11 12
2
0 1023```

### 输出

```
1
4
2
-1
-1
1023```

# 题解

## 作者：ecxjs (赞：1)

题意看上去很复杂，其实并不难。

首先，集合内的元素不考虑顺序问题，所以题目中的相等也是不考虑顺序的。

并且通过观察 $k$，发现枚举每一个 $k$ 完全不会超时，所以将异或后的数存入另一个数组。要看它们是否一样只需要排序后一个个比对即可。

代码实现比较简单，这里不提供了。

---

## 作者：Jsxts_ (赞：1)

# 题解 CF1326B
[传送门](https://www.luogu.com.cn/problem/CF1362B)
## 题意
见原题（原题讲得很清楚了）。
## 题解

首先因为数据范围很小，可以暴力枚举 $k$ ,每次暴力改变数组再判断，得到满足条件的 $i$ 就结束循环。

如何方便地判断呢？

我们用 $c$ 数组记录初始集合每个数的个数，改成新的集合后把里面每个数 $c$ 的值都减一，最后判断每个 $c$ 是否都为 0，是就代表满足要求。

而因为一个数异或它本身等于 0，所以变回原来的数组只用再异或一次，并不用多用一个数组。

剩下的细节就看代码理解。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[10010],c[10010];
int main() {
	int t;
	scanf("%d",&t);//多组数据 
	while (t -- ) {
		int n,mx = 0;
		scanf("%d",&n);
		memset(c,0,sizeof c);//初始化 
		for (int i = 1;i <= n;i ++ )
			scanf("%d",&a[i]), mx = max(mx,a[i]), c[a[i]] ++;//记录初始数组每个数的个数 
		for (int i = 1;i <= 1024;i ++ ) {//枚举 k 
			for (int j = 1;j <= n;j ++ ) a[j] ^= i, c[a[j]] --;//按题意修改数组，顺便更新c 
			for (int j = 0;j <= mx;j ++ ) {
				if (c[j]) goto bre;//判断是否满足要求 
			}
			printf("%d\n",i);
			goto bre2;
			bre:;
			for (int j = 1;j <= n;j ++ ) c[a[j]] ++, a[j] ^= i;//把数组修改回去 
		}
		puts("-1");//没有满足的k 
		bre2:;
	}
	return 0;
}
```
Time：336ms，一遍拿到最优解。

---

## 作者：ShineEternal (赞：1)

[更佳的阅读效果。](https://vipblog.github.io/_caeP72oh/)

## description：

给出 $n$ 个数字，让找出最小的正整数 $k$，使得这 $n$ 个数字异或 $k$ 之后，还是这 $n$ 个数字。（顺序不一定要相同

## solution：

观察到数据范围并不大，故直接枚举 $k$ 从 $1\sim 1024$，可以在输入的时候就预处理出来每一种异或结果然后分别排序。

## code：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int b[1030][1030],a[1030];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			for(int j=1;j<=1024;j++)
			{
				b[j][i]=a[i]^j;
			}
		}
		for(int i=1;i<=1024;i++)
		{
			sort(b[i]+1,b[i]+n+1);
		}
		sort(a+1,a+n+1);
		int tag=0;
		for(int i=1;i<=1024;i++)
		{
			int flag=0;
			for(int j=1;j<=n;j++)
			{
				if(b[i][j]!=a[j])
				{
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				printf("%d\n",i);
				tag=1;
				break;
			}
		}
		if(tag==0)printf("-1\n");
	}
	return 0;
} 
```

---

## 作者：OIerZhang (赞：0)

# [CF1362B Johnny and His Hobbies](https://www.luogu.com.cn/problem/CF1362B) 题解

一道位运算入门题，建议萌新拿这道题练练位运算用法，犇犇就把这题当水题切了吧。

## 思路

这道题真的很仁慈，$n$ 最大只有 $1024$，用暴力就可以秒掉这道题。

过程就摆在这里了，我不信有人看不懂。
1. 输入数据并排序，至于为什么，下面我会讲。
1. 枚举 $k$，范围 $[1, 1024]$。$k$ 一定会小于等于 $1024$，因为一个数异或另一个比它大的数一定与原来不相等。
1. 计算异或值，将它们存储在临时数组中。
1. 将数组排序，和原数据比对。

为什么要排序？因为数据是无序的，有可能调换一下异或值就能符合要求，通过排序可以尽可能将两组数据一一对应。

## 代码

时间复杂度 $O(n^3 \log n)$，但因为有些循环不会执行完，所以是能通过的。

```cpp
#include <iostream>
#include <algorithm>
#define ios ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a[1050], x[1050];

int main()
{
    ios;
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        bool flag = true;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        sort(a + 1, a + 1 + n); // 这里排序很重要，不加就会满屏 -1，连样例都过不去
        for (int k = 1; k <= 1024; k++)
        {
            bool f = true;
            for (int i = 1; i <= n; i++)
                x[i] = a[i] ^ k; // 计算异或值
            sort(x + 1, x + 1 + n); // 排序
            for (int i = 1; i <= n; i++)
            {
                if (a[i] != x[i])
                {
                    f = false;
                    break;
                }
            }
            if (f)
            {
                cout << k << endl;
                flag = false;
                break;
            }
        }
        if (flag)
            cout << "-1\n";
    }
    return 0;
}
```

---

## 作者：ChenYanlin_20 (赞：0)

### 思路：
由于 $t \le 1024$ , $n \le 1024$ , 所以 $k$ 也应该 $ \le 1024 $ , 暴力枚举复杂度为 $ O ( 1024^3 ) $ 。但是可以发现，枚举 $k$ 的一层循环并不会执行满，而且一个不满足的 $k$ 也会在判定中提前跳出，所以时间复杂度会小很多，暴力~~蹭题解~~。
### CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+50;
int s[N],a[N],t;
int main(){
	int t;
	cin>>t;
	while(t--){
		bool flag=0;
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>s[i];
		}
		sort(s+1,s+n+1);
		for(int k=1;k<=1024;k++){
			bool cnt=1;
			for(int i=1;i<=n;i++)
				a[i]=s[i]^k;
			sort(a+1,a+1+n);
			for(int i=1;i<=n;i++){
				if(a[i]!=s[i]){
					cnt=0;
					break;
				}
			}
			if(cnt){
				flag=1;
				cout<<k<<'\n';
				break;
			}
		}
		if(flag==0) cout<<"-1\n";
	}
	
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

首先观察数据范围：$t\le1024,n\le1024$。数据不是很大，可以考虑暴力枚举 $k$，将算出的集合存入临时数组。

最后注意一下**集合的相等不会考虑顺序**，只需要将每次的 $s$ 数组和临时数组排序即可，最后进行比对。

- - -

AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,s[1025],s2[1025];
int main(){
    cin>>t;
    while(t--){
        bool flag=0;
        cin>>n;
        for(int i=1;i<=n;i++)cin>>s[i];
        sort(s+1,s+n+1);//排序
        for(int i=1;i<=2000;i++){//枚举 k
            for(int j=1;j<=n;j++)s2[j]=s[j]^i;//结果存入临时数组
            sort(s2+1,s2+n+1);//排序
            for(int j=1;j<=n;j++)if(s[j]!=s2[j])goto A;//若不一样则不在比对
            cout<<i<<'\n',flag=1;break;//找到答案
A:          ;
        }if(!flag)puts("-1");//不存在
    }return 0;
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1362B)

题意：给出一个自然数集合 $S$，求最小的正整数 $k$，使得 $S$ 里的每个数异或 $k$ 后新的集合仍然等于 $S$。

因为这题数据范围非常小，所以可以直接暴力枚举 $k$ 从 $1$ 到 $1024$。

先把 $S$ 装进数组里排个序。

然后枚举的时候每次都把 $S$ 异或上 $k$ 然后排序，看新的数组和原来是否一样。如果一样，则输出 $k$ 并结束程序。

最后记住无解输出 $-1$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[2001], b[2001], flag, f; 
int main(){
	cin >> t;
	while (t--){
		cin >> n; f = 0;
		for (int i = 1; i <= n; i++) cin >> a[i];
		sort(a + 1, a + n + 1);
		for (int i = 1; i <= 1024; i++){
			flag = 0;
			for (int j = 1; j <= n; j++) b[j] = a[j] ^ i;
			sort(b + 1, b + n + 1);
			for (int j = 1; j <= n; j++)
				if (b[j] != a[j]){flag = 1; break;}
			if (!flag){cout << i << endl; f = 1; break;}
		}
		if (!f) cout << -1 << endl;
	}
    return 0;
}
```

---

## 作者：Ericby666 (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/CF1362B)
本题数据范围非常小，因此可以暴力枚举 $k$（$1$ 到 $1024$）。先给 $S$ 排序，每次异或完 $k$ 之后再排一次序。最后再比较 $S$ 和之前是否相同即可。

谨记无解输出 $-1$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[1029],b[1029];
int main(){
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		int n;
		bool f,ff=0;
		scanf("%d",&n);
		for(int j=1;j<=n;j++)scanf("%d",&a[j]);
		sort(a+1,a+n+1);//先排序
		for(int j=1;j<=1024;j++){//枚举k
			f=0;
			for(int k=1;k<=n;k++)b[k]=a[k]^j;//异或
			sort(b+1,b+n+1);//再排序
			for(int k=1;k<=n;k++)
				if(a[k]!=b[k]){//比较
					f=1;
					break;
				}
			if(!f){
				printf("%d\n",j);//有解就输出
				ff=1;
				break;
			}
		}
		if(!ff)printf("-1\n");//无解输出-1
	}
	return 0;
}
```

---

## 作者：RioFutaba (赞：0)

# 题意
有一个集合 $S$，要求一个最小的正整数 $k$，让 $S$ 的每一个数异或上 $k$ 后与原来的 $s$ 相等。

数据范围：$1 \le n \le 1024$，$\sum n \le 1024$，$1 \le s_i<1024$。
# 思路
因为数据范围很小，所以可以暴力枚举 $k$，排序之后判断是否相等就行了。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=1024+5;
int t;
int n,s[maxn],f[maxn];//f为临时记录结果的数组
bool check(int k){
	for(int i=1;i<=n;i++) f[i]=s[i]^k;
	sort(f+1,f+n+1);//排序
	for(int i=1;i<=n;i++) if(f[i]!=s[i]) return 0;//判断是否相等
	return 1;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&s[i]);
			f[i]=s[i];
		}
		sort(s+1,s+n+1);
		bool flag=0;
		for(int i=1;i<=1024;i++){//枚举k
			if(check(i)){
				printf("%d\n",i);
				flag=1;
				break;
			}
		}
		if(!flag) printf("-1\n");//无解
	}
	return 0;
}
```

---

