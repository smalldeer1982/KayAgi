# Run For Your Prize

## 题目描述

You and your friend are participating in a TV show "Run For Your Prize".

At the start of the show $ n $ prizes are located on a straight line. $ i $ -th prize is located at position $ a_{i} $ . Positions of all prizes are distinct. You start at position $ 1 $ , your friend — at position $ 10^{6} $ (and there is no prize in any of these two positions). You have to work as a team and collect all prizes in minimum possible time, in any order.

You know that it takes exactly $ 1 $ second to move from position $ x $ to position $ x+1 $ or $ x-1 $ , both for you and your friend. You also have trained enough to instantly pick up any prize, if its position is equal to your current position (and the same is true for your friend). Carrying prizes does not affect your speed (or your friend's speed) at all.

Now you may discuss your strategy with your friend and decide who will pick up each prize. Remember that every prize must be picked up, either by you or by your friend.

What is the minimum number of seconds it will take to pick up all the prizes?

## 说明/提示

In the first example you take all the prizes: take the first at $ 1 $ , the second at $ 2 $ and the third at $ 8 $ .

In the second example you take the first prize in $ 1 $ second and your friend takes the other in $ 5 $ seconds, you do this simultaneously, so the total time is $ 5 $ .

## 样例 #1

### 输入

```
3
2 3 9
```

### 输出

```
8
```

## 样例 #2

### 输入

```
2
2 999995
```

### 输出

```
5
```

# 题解

## 作者：Yaixy (赞：6)

## 题意及注意点

- 可以把题目理解为一个~~不正常的~~数轴上的相遇问题，你在 $1$ 处，朋友在 $10^6$ 处，同时出发。输入 $n$ 相遇点，（你们两人到达相遇点较快那一方的时间为相遇时间），问在这 $n$ 个点中，最长的相遇时间是多少秒。

- 你和朋友的速度均为 $1$ 秒 $1$ 个单位长度。

- ~~经过验证，是暴力也不会 $T$ 的题。（~~

## 思路

我这里的思路有两个qwq

#### 1. 暴力

输入 $n$ 次相遇点，每次循环求出你和朋友分别要用的时间取最小值为 $ans$，最终输出最大的 $ans$。

具体操作详见代码qwq

#### 2. 更方便的暴力（

![](https://cdn.luogu.com.cn/upload/image_hosting/881xm11k.png)

画两张图不难发现，当输入的相遇点 $a_i$ 小于中点 $mid$ 时，你到 $a_i$ 的距离小于朋友到 $a_i$ 的距离。又因为两个人的速度相等，所以此时的相遇时间一定是你到相遇点所花费的时间。由此可得
```cpp 
if(a[i]<=mid) sum=a[i]-1;
```
反之，得

```cpp
if(a[i]>mid) sum=1000000-a[i];
```
那么如果 $a_i$ 等于 $mid$ 呢？

计算一下可以得到，因为 $1$ 与 $10^6$ 的和为奇数，所以你和朋友到 $mid$ 的距离是相等，取哪一方的时间都可以。

最后，取 $sum$ 的最大值输出就可以了qwq


## 代码

#### 1. 

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[500005],n,x,y,mid,sum,ans;
void qwq(int q)
{
    int sum2;
	sum=sum2=0;
	for(int i=x;i<q;++i) sum++;//你的时间
	for(int i=y;i>q;--i) sum2++;//朋友的时间
	sum=min(sum,sum2);
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	x=1;//你的位置
	y=1000000;//朋友的位置
	mid=(x+y)/2;//中点
	for(int i=1;i<=n;++i)
	 {
	 	cin>>a[i];
	 	qwq(a[i]);//暴力枚举
	 	ans=max(sum,ans);//取max值
	 }
	cout<<ans<<"\n";
	return 0;
}
```

#### 2. 

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[500005],n,x,y,mid,sum,ans;
int main()
{

	ios::sync_with_stdio(false);
	cin>>n;
	x=1;
	y=1000000;
	mid=(x+y)/2;
	for(int i=1;i<=n;++i)
     {
	 	cin>>a[i];
	 	if(a[i]<=mid) sum=a[i]-x;//取你的时间
	 	if(a[i]>mid) sum=y-a[i];//取朋友的时间
	 	ans=max(sum,ans);
	 }
	cout<<ans<<"\n";
	return 0;
}
```


------------

撒花完结awa

---

## 作者：Anguei (赞：4)

本题数据范围很小（$10^6$），跑 $O(n)$ 的暴力模拟完全没有问题。
开一个 $10^6$ 的数组分别记录每个坐标是否有奖品，然后从两头遍历数组即可。这么小的数据，不需要考虑离散化，不会 MLE 的。
```cpp
//【CF938B】Run For Your Prize - 洛谷 - Ac
#include <iostream>

int a[1000000];

int main() {
	int n;
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		int t;
		std::cin >> t;
		a[t] = 1;
	}
    // l、r 分别表示你和你朋友的位置，already 表示已经拾了多少奖品，time 表示已消耗时间
	for (int l = 1, r = 1000000, time = 0, already = 0; ; ++l, --r, ++time) {
		if (a[l])
			++already;
		if (a[r])
			++already;
		if (already == n) { // 如果都拾完了
			std::cout << time << std::endl;
			return 0;
		}
	}
}
```

---

## 作者：Moon_Lighter (赞：3)

## 题目大意：

 在一条线上，你在 $1$ 处，朋友在 $10^6$ 处，你们两中间有 $n$ 个礼物。第 $i$ 个礼物的坐标为 $a_i$。你们两个的速度为 $1$，被经过的礼物就被认为是捡起的。你们想把所有礼物捡起，请问最少要多少秒。

## 大致思路:

求礼物距你和朋友的距离，取 $\min$ ，然后对所有的 $\min$ 进行排序，取最大的 $\min$ 。相信很容易理解，具体见源代码，有注释。

---
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],n;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    //代表n个礼物
    {
        cin>>a[i];
        //输入坐标
        a[i]=min(a[i]-1,1000000-a[i]);
        //取最小值
    }
    sort(a+1,a+1+n);
    //排序后取最大值
    cout<<a[n];
    return 0;
}
```

---

## 作者：syanoeclipse (赞：1)

[个人博客体验更佳](https://www.luogu.com.cn/blog/andrew-zhong/solution-cf938b)

今天我发一下题解，不是为别的。。。只是前几篇题解没什么说明，我来给大家补充一下

首先，肯定有很多人不知道他输入的是什么。所以我翻译一下

输入格式

>第一行：有一个整数$n$($1 \leqslant n \leqslant 10^6$)，表示礼品个数
>
>第二行：$n$个整数，这些礼品所在位置

输出格式

>一行，拿起的礼品所用时间

好了，我们来分析一下这个算法，

+ 一个礼品在$5 \times 10^5$前，那么这个礼品就是我的啦。此时返回$1000000-i$。

+ 一个礼品在$5 \times 10^5+1$后，这个礼品，就得给朋友了。此时返回$i-1$。

所以我们来分析一下每个礼品什么时候能捡到，代码登场：

```cpp
int ttc(int i)
{
	const int N=500000;
	const int S=1000000;
	if(i>N)
	{
		// 朋友捡
		return (S-i);
	}
	if(i<=N)
	{
		// 自己捡
		return (i-1);
	}
}
```

`ttc`表示`time to collect`，捡到的时间的意思，然后每一个礼物什么时候捡到

然后简化一下：

```cpp
int ttc(int i)
{
	return (i>500000)?(1000000-i):(i-1);
}
```

这个叫做`(bool)?(int):(int)`句型，它的用法相当于

`(判别式)的话?(就怎么样)否则:(就怎么样)`

好了，判断每个礼物什么时候捡到的程序有了，

现在看看捡完所有礼物的所需时间吧。

这个，只需看看每一个$\operatorname{ttc}(i)$，并求出他们的最大值就可以了。

上代码：（`ttca`是`time to collect all`）

```cpp
int a;
// 这里使用全局变量
void ttca(int k)
{
	int s=0;
	// s存储最后的ttca()
	// a存储输入
	// k是礼品个数
	for(int i=0;i<k;i++)
	{
		cin>>a;
		if(ttc(a)>s)
		{
			s=ttc(a);
		}
	}
	cout<<s;
}
```

好了，这个代码没什么可化简的了，用到的算法也是之前说过的了，直接上代码：

```cpp
#include<iostream>
using namespace std;
int ttc(int i)
{
	return (i>500000)?(1000000-i):(i-1);
}
int a;
void ttca(int k)
{
	int s=0;
	for(int i=0;i<k;i++)
	{
		cin>>a;
		if(ttc(a)>s)
		{
			s=ttc(a);
		}
	}
	cout<<s;
}
int main()
{
	int a[100000],k;
	cin>>k;
	ttca(k);
	return 0;
}
```

亲测48个点全都AC，但我本人另有一份更简单的代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    int s,k;
    int tim;
    int _tim=0;
    cin>>s;
    for(int i=0;i<s;i++)
    {
        cin>>k;
        tim=(k>500000)?(1000000-k):(k-1);
        if(tim>_tim){_tim=tim;}
    }
    cout<<(_tim);
    return 0;
}
```

呼~累死了！

---

## 作者：zqwzqwzqw (赞：1)

### 前言

$\because$ 数据比较小。

$\therefore$ 这道题用模拟就可以过！

---

### 算法

把你和朋友看做两个端点，一起相中前进（左端点$++$,右端点$--$,时间$++$），每遇到一个礼物就捡起来（完成数$++$），直至 完成数**等于**礼物数。

### 提醒

在捡礼物时一定不能像下面的代码一样，只要你**或**朋友有礼物可捡，就将完成数$++$。

```
if(pd[wo]!=0 || pd[pengyou]!=0)	
	done++;
```

这样，当你和朋友同时有礼物可捡时，完成数会**少**加一。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,x,t,done;//n为礼物数，x为礼物的位置，t(time)为时间，done为完成数。
bool pd[1000005];//统计各个位置上有无礼物。
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>x;
		pd[x]=true;//true代表有礼物，false反之。
	}
	int wo=1,pengyou=1000000/*1e6也没问题啦。*/;
	while(done!=n) {//直至完成数等于礼物数，退出循环。
		wo++,pengyou--,t++;
		if(pd[wo]!=0)
			done++;//你捡礼物。
		if(pd[pengyou]!=0)
			done++;//朋友捡礼物。
		//捡礼物。
	}
	cout<<t;//输出。
	return 0;
}
```


---

## 作者：Chthology (赞：1)

### 题目大意：

在一条线上，你1处，朋友在$10^6$处，你们两中间有n个礼物第i个礼物坐标为$a_i$(1<$a_i$<$10^6$)你们两个的速度为1，,被经过的礼物就被认为是捡起的，你们想把所有礼物捡起，问最少要多少秒。

###### ~~仅供参考~~

---

### 思路：

你们跑到一下位置的最大时间取min就行了

| 你 | 朋友 |
| : | |
| 1 | $a_1$ |
| $a_1$ | $a_2$ |
| …… ||
| $a_{n-1}$  |  $a_n$ |
| $a_n$ | $10^6$ | |

---

### 代码：

```cpp
#pragma GCC optimize("O3")  //开O3

#include<bits/stdc++.h>
#define fri 1000000
using namespace std;

int n,ans,a[100005];

int main(){
	std::ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	ans=fri-a[1];
	for(int i=1;i<n;++i) ans=min(ans,max(a[i]-1,fri-a[i+1]));
	ans=min(ans,a[n]-1);
	cout<<ans;
	return 0;
}
```

---

## 作者：xgwpp6710 (赞：0)

这题可以用贪心的算法做。

怎么个贪心呢，就是看一个奖品离谁近就让谁去捡。

（这个应该很容易证明

那么我们只需要找到那位朋友需要捡的最靠左的那个奖品即可。

然后我们就可以知道你和你朋友分别需要多少时间。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100009],friendMin;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
		if(a[i]>500000)
		{
			friendMin=i;//朋友需要捡起的第一个，这是离他比较近的最靠左的奖品
			break;//不这样就会一直更新friendMin，我因为这个WA了两次
		}
	if(a[n]<=500000) cout<<a[n]-1<<endl;//全部需要你来捡
	else cout<<max(a[friendMin-1]-1,1000000-a[friendMin])<<endl;//否则看谁需要的时间多
	return 0;
}
}
```

---

## 作者：BMTXLRC (赞：0)

首先思考如何解，既然数据很小，就考虑一下暴力啥的。

------------

### 解法：

让你跟朋友每人分 $5\times10^5$ 的距离，这很显然是最优解，路上如果遇到礼物就让计数器自增，什么时候增到了总的礼物数量就停止并输出。

设一个 $\texttt{l}$ 代表你的位置，$\texttt{r}$ 代表你朋友的位置，然后两人向中间靠近就行。

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int a[N],n,x,t=0,cnt=0;
int main(){
	cin>>n;
	for(register int i=1;i<=n;i++) cin>>x,a[x]=1;
	for(register int l=1,r=N-5;;l++,r--,t++){
		if(a[l]) cnt++;
		if(a[r]) cnt++;
		if(cnt==n){cout<<t;return 0;}
	}
}
```


---

## 作者：Eason_AC (赞：0)

## Content
有两个人，一个在 $1$ 处，一个在 $10^6$ 处，在他们之间有 $n$ 个奖品，第 $i$ 个奖品在 $a_i$ 处。一开始在 $1$ 处的人每秒可向右移动 $1$ 个单位，一开始在 $10^6$ 处的人每秒可向左移动 $1$ 个单位，我们认为他们经过了礼物就算得到礼物，并且不需要耗费时间，求他们得到所有礼物的最短时间。

**数据范围：$1\leqslant n\leqslant 10^5,1<a_i<10^6$。**
## Solution
我们可以将满足 $1< a_i\leqslant 5\times10^5$ 的奖品都划给在 $1$ 处的人去取，将满足 $5\times 10^5< a_i<10^6$ 的奖品都划给在 $10^6$ 处的人去取，很容易发现这是最优的方案，然后我们看在 $1$ 处的人取到他要取的最右边的奖品需要耗费的时间和在 $10^6$ 处的人取到他要取的最左边的奖品需要耗费的时间的较大值，这其实就等同于求距离了。
## Code
```cpp
int n, x, a[100007], b[100007];

int main() {
	getint(n);
	_for(i, 1, n) {getint(x); if(x >= 1 && x <= 500000) a[++a[0]] = x; else b[++b[0]] = x;}
	sort(a + 1, a + a[0] + 1), sort(b + 1, b + b[0] + 1);
	int ans = max((a[0] ? a[a[0]] - 1 : 0), (b[0] ? 1000000 - b[1] : 0));
	writeint(ans);
	return 0;
}
```

---

## 作者：houpingze (赞：0)

思路：

直接暴力枚举，因为$a_i≤10^6$，不会超时

用桶标记来解决:
 

$a_i=x$表示这个位置有$x$个礼物

每次输入一个值$t$，$a_t++$即可

注意：
有可能一个位置里有两个礼物 ，并且是从1出发的，捡起1号位置不需要花费时间

```cpp
#include<iostream> 
using namespace std;
int n,cnt,m,tmp,a[1000001];//根据ai的大小来定义
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>tmp;//输入 
		a[tmp]++;//桶标记 
	} 
	int l=1,r=1000000; //l是我的位置，r是朋友的位置
	while(1){
		cnt=cnt+a[l]+a[r];//把路过的礼物捡起来，有可能一个位置里有两个以上的礼物 
		if(cnt==n) {
			cout<<l-1;//因为是从1开始行走的，1走到1不需要花费时间，所以输出l-1 
			return 0;
		}
		l++,r--;//继续走
	}
}

```
还是很简洁易懂的QWQ

---

## 作者：TianLuen (赞：0)

# CF938B C++ 题解
### 题意简述
- 两人分别从 $1$ 和 $10^6$ 出发，相向而行
- 速度均为 $1$
- 有 $n$ 个礼物，第 $i$ 个的位置是 $a_i$
- 求的是两人收集所有礼物的时间
### 题目分析
读题后，可以发现，可以将整条路径折叠起来，即两人在同一出发点，于是就可以变成一个人行走了。折叠后，可以计算出，各个礼物就是所在 $a_i$ 或 $10^6-a_i$，而取得所有礼物的最短时间，就是最大的 $a_i-1$ 了。

于是就可以直接模拟了。这题不一定要数组。
### 代码
```cpp
#include<iostream>
using namespace std;
int main()
{
    int n,temp,max=0;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>temp;
        //核心部分↓
        int temp2=temp<=500000?temp:1000001-temp;//计算折叠后距离
        if(temp2>max)
            max=temp2;//比较出最远的礼物
    }
    cout<<max-1;
    return 0;
}
```


---

## 作者：XMK_萌新 (赞：0)

~~第一次发CF题解，好激动嘤~~

```cpp
//大水题啊 
//发一波思路 
//其实礼物在你和朋友位置连线中点（500000.5）上捡的时间最长  （然而并没有小数这一说？因此是500000 or 500001） 
//那么最终答案就是到离中点距离最短的那一个礼物的时间（或者说距离）辣 
//tips:普及知识  AB距离 = |A - B|

#include <iostream>
#include <cmath>
using namespace std;
int n,p,ans,dao_zhong_dian_ju_li=1e6+233;	//变量名…… 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>p;
		int dis=abs(500000.5-p);
		if(dis<dao_zhong_dian_ju_li)
		{
			dao_zhong_dian_ju_li=dis;
			int tmp=min(abs(1-p),abs(1000000-p));	//你和朋友的最小值 
			ans=tmp;	//更新 
		}
	} 
	cout<<ans;
	return 0;
}
```

---

## 作者：EAT_NH4HCO3 (赞：0)

### 思路
- 通过一个multiset将数据进行存储，鉴于此题的特殊性我们可以直接使用set的自动排序而不考虑bug的问题
- 我们对输入的n直接处理：如果i（我的位置）和j（朋友的位置）的数据能在set中找到那么将n--，每一次移动（i++,j--）时ans++
- 当n==0时得出答案，直接退出循环，输出

~~虽然不如楼上大佬但我还是挺欣赏我自己的方法的（滑稽）（^_^）~~
### 代码
```cpp
//Codeforces
//938B Run For Your Prize
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
multiset<int> gift;//gift用来存储礼品位置
int main()
{
	ios::sync_with_stdio(false);//哲学需要快
	int n,ans=0;//ans是最短时间即输出结果
	cin>>n;
	for(int i=0;i<n;++i)
	{
        int t;
        cin>>t;
        gift.insert(t);//输入
	}
	for(int i=1,j=1000000;;++i,--j)//i是我的位置，j是朋友的位置，两个人一起走，即i++，j--
	{
		if(gift.find(i)!=gift.end())--n;
		if(gift.find(j)!=gift.end())--n;//如果碰到礼物，则n--，此处n代表剩余的礼品个数
		if(n==0)break;
		else ans++;//重点！因为每一次循环代表前进一步，如果此处已经收集玩礼物要先退出，不然答案是错误的
	}
	cout<<ans;//结束
	return 0;
}
```
### 恳请各位指正！

---

