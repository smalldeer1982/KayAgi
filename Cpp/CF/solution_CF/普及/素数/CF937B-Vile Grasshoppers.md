# Vile Grasshoppers

## 题目描述

The weather is fine today and hence it's high time to climb the nearby pine and enjoy the landscape.

The pine's trunk includes several branches, located one above another and numbered from $ 2 $ to $ y $ . Some of them (more precise, from $ 2 $ to $ p $ ) are occupied by tiny vile grasshoppers which you're at war with. These grasshoppers are known for their awesome jumping skills: the grasshopper at branch $ x $ can jump to branches ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF937B/e256171e16de0ce2bc4667496d6c5befd611ffc8.png).

Keeping this in mind, you wisely decided to choose such a branch that none of the grasshoppers could interrupt you. At the same time you wanna settle as high as possible since the view from up there is simply breathtaking.

In other words, your goal is to find the highest branch that cannot be reached by any of the grasshoppers or report that it's impossible.

## 说明/提示

In the first sample case grasshopper from branch $ 2 $ reaches branches $ 2 $ , $ 4 $ and $ 6 $ while branch $ 3 $ is initially settled by another grasshopper. Therefore the answer is $ 5 $ .

It immediately follows that there are no valid branches in second sample case.

## 样例 #1

### 输入

```
3 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 4
```

### 输出

```
-1
```

# 题解

## 作者：hu1029282594 (赞：9)

这题难想的不是算法，因为算法就是暴力。困难的是
# 时间复杂度的计算

真坑啊！先贴代码

```cpp
#include<bits/stdc++.h>
#define MAXN 50000050 
using namespace std;
int p,y;
int main()
{
	scanf("%d%d",&p,&y);
	for(;y>=2;y--)
	{
		if(y<=p){
			printf("%d\n",-1);
			break;
		}
		bool ok=1;
		for(register int i=2;i*i<=y&&i<=p;i++)//仅用<=sqrt(y）的数就可证明它是质数肯定不能被后面的<=p的数整除
		if(y%i==0){ok=false;break;
		}
		if(ok){
			printf("%d\n",y);break;
		}
	}
	return 0;	
} 
```

~~要不是看到讨论，我永远想不到这样能过~~

这题坑的地方就在于 
# 小于等于10^9的两个质数之间的差最大不超过300

两个质数之间就是这样了，那加上没筛掉的合数就更近了

最坏情况下复杂度
## O(300*sqrt(y))
所以能过

---

## 作者：User757711 (赞：1)

# [CF937B Vile Grasshoppers](https://www.luogu.com.cn/problem/CF937B) 题解
### 题目大意
筛出 $y$ 到 $p$ 中最大不是 $2$ 到 $p$ 任何一个数的倍数的数。
### 思路分析
直接从 $y$ 开始筛，如果这个数不是 $2$ 到 $p$ 中任何一个数的倍数，直接输出这个数，结束程序。

如果循环结束还没输出，输出 $-1$。
### 最后，附上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int p,y;
	cin>>p>>y;
	for(int i=y;i>p;i--) //从y到p筛
	{
		bool flag=0;
		for(int j=2;j<=sqrt(i);j++)
		{
			if(j>p)
			{
				break;
			}
			if(i%j==0)
			{
				flag=1;
			}
		}
		if(!flag) //如果是质数
		{
			cout<<i; 
			return 0; //输出，结束程序
		}
	}
	cout<<-1;
	return 0;
}
```
### The End！

---

## 作者：kimidonatsu (赞：1)

# CF937B Vile Grasshoppers 题解

## 思路分析

其实这道题的范围只到了 $2 \leq p \leq y \leq 10^9$，完全可以直接筛过去。

这里给大家提供一点思路：

我们可以从 $y$ 开始，倒着搜到 $p + 1$，在搜索的过程中每次都筛，找到了就把 $flag$ 打上标记然后输出，不然就输出 $-1$ 。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll p, y;

int main() {
    scanf("%lld %lld", &p, &y);
    for (ll i = y; i > p; i--) {
        bool f = true;
        for (ll j = 2; j * j <= i; j++) {
            if (j > p) break;
            if (i % j == 0) {
                f = false;
                break;
            }
        }
        if (f == true) {
            printf("%lld\n", i);
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}

```

这个程序的瓶颈在素数筛的过程，但是仍足以通过本题。


---

## 作者：wangshi (赞：1)

[CF937B](https://www.luogu.com.cn/problem/CF937B)

给你两个数 $p,y$ ，求去掉 $2 \sim{1}$ 中所有 $2 ~ \sim{p}$ 的数的倍数后剩下的最大值 ! 没有则输出 $- 1$ ；
那就可以从 $y \sim{2}$ 的每一个数把 $2 \sim{p}\ mod$ 一遍

因为时间复杂度的要求，所以循环到 $\sqrt{y}  $ 或者到 $i \times i <= y$
最后再加一个 $y < = p$ 的特判。

AC代码
```c
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
    int p,y;
    bool f=true;//记录循环中有没有答案 
    cin>>p>>y;//平平无奇的输入 
    while(y>=2)//因为是最大值,所以从y~2 
    {
        if(y<=p)//特判一下 
        {
            break;
        }
        bool f1=true;//记录这个数有没有mod成功的 
        for(int i=2;i<=p&&i<=sqrt(y);i++)//i*i<=y 
        {
            if(y%i==0)
            {
                f1=false;
                break;  
            }   
        }
        if(f1)//有直接输出结束循环 
        {
            f=false;
            cout<<y;
            break;
        }
        y--;
    } 
    if(f)//没找到输出-1 
    {
        cout<<"-1";
    }
    return 0;//完美结束 
}
```

---

## 作者：fish_shit (赞：0)

## 题目大意
找出从 $2$ 到 $y$ 中不是从 $2$ 到 $p$ 中的任意一个数的倍数的数的最大值。

## 解题思路
从 $y$ 遍历到 $p$ ，因为不大于 $p$ 且大于等于 $2$ 的整数一定不满足要求。再在每一次遍历中都从 $2$ 遍历到 $\sqrt{n}$ 和 $p$ 中的较小的那一个。虽然题面上要求是要遍历到 $p$，但是遍历到 $\sqrt{n}$ 就可以保证第一层循环遍历的那个数为质数，自然是满足要求的。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int p,y;
	cin>>p>>y;
	for(int i=y;i>p;i--){
		bool flag=0;//标记是否满足要求
		for(int j=2;j<=min(int(sqrt(i)),p);j++){
			if(i%j==0){
				flag=1;
				break;
			}
		}
		if(!flag){
			cout<<i;
			return 0;
		}
	}
	cout<<"-1";
	return 0;
}

```


---

## 作者：E1_de5truct0r (赞：0)

因为 $y \leq 10^9$，所以质数的间隔并不会很大，大约为 $\log n$的间距。因此，我们从 $y$ 往前找，一直到 $p$，每次都进行一个判断即可。

注意这里判断的不是质数，应该是 $1$ 到 $\min(\sqrt{x},p)$ 的范围内枚举因数。但是由于我们找到了质数就一定可以获得答案，所以这个查询的次数一定 $\leq \log n$。

总的时间复杂度为：

$$\mathcal{O}\left(\sum\limits_{i=y-\log y}^{y}\sqrt{i}\right)=\mathcal{O}\left(\log{y}\sqrt{y}\right)$$

（其实跑不满的qwq），极限复杂度约为 $30 \times (3 \times 10^4) = 9 \times 10^5$ ，显然可以通过本题。

```cpp
#include <bits/stdc++.h>
using namespace std;
int p,y;
bool pd(int x)
{
	for(int i=2;i<=min(p,(int)sqrt(x));i++) // 要对 p 取 min！！
		if(x%i==0) return false;
	if(x<=p) return false;
	return true;
}
int main()
{
	cin>>p>>y;
	for(int i=y;i>p;i--) //显然小于等于 p 的一定不符合
		if(pd(i)) // 如果符合条件
		{
			cout<<i;
			return 0;
		}
	cout<<-1; // 没找到（这个时候其实 y-p 应该小于理论间隙 log，所以其实还是 log 的复杂度）
	return 0;
}
```

---

## 作者：Jasper08 (赞：0)

### 【基本思路】

题目要求的是区间 $[2,y]$ 中去掉 $[2,p]$ 之间的数的倍数后的最大值，实际上就是求区间 $[2,y]$ 去掉 $[2,p]$ 之间的**质数**的倍数后的最大值。这个并不难理解，因为任意 $[2,p]$ 之间的整数都能被分解为 $[2,p]$ 之间的质数的乘积。

所以我们可以用线性筛筛出区间 $[2,\min(p,\sqrt{y})]$ 之间的质数，然后从 $y$ 开始倒着判断，遇到第一个不是 $[2,p]$ 之间质数的倍数的数时就输出。如果循环到 $p+1$ 时还没有结果就输出 `-1`。

### 【完整代码】

$15\text{ms}$，是本题（在洛谷上的）最优解。

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <bitset>

using namespace std;

const int N = 5e4+10; //sqrt(1e9)约等于5e4,开1e5会爆炸

int primes[N], cnt;
bitset<N> st; //开bitset使空间变为bool数组的1/32

void get_primes(int n) { //线性筛
	st[0] = st[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!st[i])
			primes[cnt ++] = i;
		for (int j = 0; primes[j] <= n/i && j < cnt; ++j) {
			st[i*primes[j]] = 1;
			if (i % primes[j] == 0)
				break;
		}
	}
}

int main() {
	int p, y;
	scanf("%d%d", &p, &y);
	int t = (int)sqrt(y) > p ? p : (int)sqrt(y); //判断质数要筛到哪里
	get_primes(t);
	for (int i = y; i > p; --i) { //从y开始倒着循环,直到p+1
		bool check = 1;
		for (int j = 0; j < cnt; ++j) { //判断i能否被[2,t]之间的质数整除
			if (i % primes[j] == 0) {
				check = 0;
				break;
			}
		}
		if (check) {
			printf("%d\n", i); 
			return 0; //如果找到最大值就直接退出
		}
	}
	puts("-1"); //没找到,输出-1
	return 0;
}
```

---

## 作者：BYWYR (赞：0)

## 思路

这肯定是 **暴力+素数筛法** 啦。

- 倒着搜；

- 从 $y$ 一直搜到 $p+1$；

- 只要搜到了，就输出（因为倒着搜，所以保证最大）；

- 找不到就输出 ```-1``` 。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll p,y;
int main(){
	cin>>p>>y;
	for(int i=y;i>p;i--){//倒着搜
		bool flag=true;
		for(int j=2;j*j<=i;j++){//素数筛法
			if(j>p) break;//筛 2~p 范围内的
			if(i%j==0){//整除
				flag=false;
				break;
			}
		}
		if(flag==true){
			cout<<i<<endl;//直接输出
			return 0;
		}
	}
	cout<<"-1";//不存在
    return 0;//完美结束
}

```


---

