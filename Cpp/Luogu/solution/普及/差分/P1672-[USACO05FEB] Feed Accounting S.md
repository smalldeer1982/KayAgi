# [USACO05FEB] Feed Accounting S

## 题目描述

约翰想知道上一船饲料是什么时候运到的。在饲料运到之前，他的牛正好把仓库里原来的饲料全吃光了。他收到运来的 $F1(1\le F1\le 10^6)$ 千克饲料。遗憾的是，他已经不记得这是哪一天的事情了。到第 $D(1\le D\le 2\times 10^3)$ 天为止，仓库里还剩下 $F2(1\le F2\le F1)$ 千克饲料。

约翰养了 $C(1\le C\le 100)$ 头牛，每头牛每天都吃掉恰好 $1$ 千克饲料。由于不同的原因，牛们从某一天开始在仓库吃饲料，又在某一天离开仓库，所以不同的两天可能会有差距很大的饲料消耗量。每头牛在来的那天和离开的那天都在仓库吃饲料。给出今天的日期 $D$，写一个程序，判断饲料**最近**一次运到是在什么时候。今天牛们已经吃过饲料了，并且饲料运到的那天牛们还没有吃过饲料。

**如果最终的答案有多个可能，请输出最大的（即，最近的）那一个。**

## 说明/提示

### 样例解释

上一次运来了 $14$ 千克饲料，现在饲料还剩下 $4$ 千克。最近 $10$ 天里，有 $3$ 头牛来吃过饲料。

约翰在第 $6$ 天收到 $14$ 千克饲料，当天吃掉 $2$ 千克，第 $7$ 天吃掉 $2$ 千克，第 $8$ 天吃掉 $3$ 千克，第 $9$ 天吃掉 $2$ 千克，第 $10$ 天吃掉 $1$ 千克，正好还剩 $4$ 千克。

### 数据规模

$1\le F2\le F1\le 10^6$，$1\le D\le 2\times 10^3$，$1\le C\le 100$。

## 样例 #1

### 输入

```
3 14 4 10
1 9
5 8
8 12```

### 输出

```
6```

# 题解

## 作者：2024sdhkdj (赞：15)

# [USACO05FEB] Feed Accounting S题解


1、题意描述
------------
依照[题面](https://www.luogu.com.cn/problem/P1672)：已知今日日期 $D$ 和最近一次饲料运到至今所消耗的饲料 $F2\sim F1$。有 $C$ 头牛，每头牛每天都吃掉恰好 $1$ 千克饲料，对于每头牛，有一个开始日期 $ate$ 和一个结束日期 $Left$，求上一船饲料运到的时间。


2、思路
----
此题正解是差分，但我却阴差阳错想到了**二分答案**。此题的二分答案的思路是：初始化左端点 $l=0$，右端点 $r=d$ （今天日期），然后开始二分答案 $mid$。对于每次二分到的 $mid$，记录以它为**上一船饲料运到的时间**所消耗的饲料，然后判断其是否与 $F1-F2$ 相等，最后记录答案并输出即可。此算法复杂度为 $O(n \log n)$。

**如有解释不当之处，请辅以代码理解！**

3、贴代码：
----
``` cpp
#include<bits/stdc++.h>
using namespace std;
int c,f1,f2,d,ate[110],Left[110],ans;
bool check(int x){//检查此答案是否合法
	int jl=0;
	for(int i=1;i<=c;i++){
		if(ate[i]<=x){
			if(Left[i]>=x&&Left[i]<=d)
				jl+=Left[i]-x+1;
			else if(Left[i]>d)
				jl+=d-x+1;	
		}
		else{
			if(ate[i]<=d){
				if(Left[i]>=d)
					jl+=d-ate[i]+1;
				else
					jl+=Left[i]-ate[i]+1;	
			}
		}			
	}
	return jl>=f1-f2;
}
int main()
{
    ios::sync_with_stdio(NULL);//快读
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>c>>f1>>f2>>d;
    for(int i=1;i<=c;i++)
    	cin>>ate[i]>>Left[i];//ate表示此牛来的日期，Left表示离开日期
    int l=1,r=d,mid;
    while(l<=r){//二分答案
    	mid=(l+r)/2;
    	if(check(mid)){//如果此答案满足，则记录下来
    		ans=mid;
    		l=mid+1;
	}
	else
		r=mid-1;
	} 
	cout<<ans;
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/114834648)

---

## 作者：Your_Majesty (赞：10)

（蒟蒻的第一篇题解，求过）

发现很多大佬用的是差分，看数据范围的话可以发现这道题其实可以暴力解决。

##思路

这道题其实可以用数组 $grass$ 来记录每天消耗的草的数量，变量 $f$ 
来记录最近的一批草消耗的数量（即 $f1-f2$ 的值），最后再从当前天开始一天一天的往前推，每一天都减去当天消耗的草的数量。当草的数量变为零的那一天，就是最近一批草运来的时间。

**如果有解释不清楚的地方，可以配合代码来理解。**

##下面是代码

```cpp
#include<iostream>
using namespace std;
int c,d,f1,f2;        //按照题目要求的输入
int f;            //用来记录消耗草的数量
int n,m;              //每头牛吃草的时间
int grass[2005];      //记录每天消耗的草的数量

int main(){
    cin>>c>>f1>>f2>>d;

    for(int i=1;i<=c;i++){
        cin>>n>>m;

        for(int j=n;j<=m;j++){
            grass[j]++;  //每头牛每天的消耗数量加一
        }
    }

    f=f1-f2;      //记录消耗草的数量，用于下面的计算
    for(int i=d;i>=1;i--){
        f=f-grass[i];
        //每次减去当天消耗的草的数量（因为最近一批草料运来当天所有草料已经吃完，且当天所有牛吃的是新草料，所以一定会有一天正好减到0）

        if(f==0){  //吃完当天就是草料运来的那一天，输出就行啦
            cout<<i;
            break;
        }
    }

    return 0;
}
```

第一次发题解，如有不足，请指出，我会加以改进。

---

## 作者：Chengjintian (赞：8)

# P1672 [USACO05FEB] Feed Accounting S 详细题解

[题目传送门](https://www.luogu.com.cn/problem/P1672)

[前置知识——差分](https://oi-wiki.org/basic/prefix-sum/)

1、思路
------------
首先，我们想要知道上一船饲料运到的时间，我们应该先知道：

>第 $i$ 天吃掉的饲料 $a_i$，原来有多少饲料，现在还剩多少饲料，以及现在是第几天。

我们发现，题目中已经给出了：原来的饲料—— $F1$，现在还剩的饲料—— $F2$，现在是第—— $D$ 天，以及再算算就可以出来的 $a_i$，~~这题目不是把所有未知数都给你了吗？~~ 

那么，我们设上一船饲料运到的时间是第 $x$ 天，易得以下方程：

$F1+\sum_{i=x}^Da_i=F2$

~~给看不懂的人的解释：~~ 上式的 $\sum_{i=x}^Da_i$ 表示从第 $D$ 天到第 $x$ 天的 $a_i$ 之和。

那我们只需要枚举一下 $x$ 即可，还有一个需要注意的：$a_i$ 还需要计算出来，而题目中只给出了第 $i$ 头牛吃饲料的区间 $l\sim r$，正常做法应该是用一个循环循环 $l\sim r$，然后让 $a_i$ 加 $1$。

那这样也太废时间了吧，光是计算 $a_i$ 的值我们就要足足浪费 $C(r-l)$ 次循环的时间！

鉴于循环是区间修改 $sum$，这里我们引入一个高级的东西——差分。它使得区间修改只需要 $O(n)$。

这里随便讲一下，有意者[自学](https://oi-wiki.org/basic/prefix-sum/)。

例如，我们想要下面的数列的第 $2$ 位到第 $5$ 位全部加 $1$，我们就可以定一个差分数组 $c_i$ 表示 $a_i$ 和 $a_{i-1}$ 的差值。

| $a_i$| $1$|$2$|$1$|$3$|$1$ |$1$ |$4$| 
| :----------: | :----------: |:----------: |:----------: |:----------: |:----------: |:----------: |:----------: |
| $c_i$ | $1$ |$1$|$-1$|$2$|$-2$|$0$|$3$|

我们要修改区间 $2 \sim  5$，就是让差分数组的第 $2$ 位和第 $5+1$ 位进行修改，即：

修改后的数组：

| $a_i$| $1$|$3$|$2$|$4$|$2$ |$1$ |$4$| 
| :----------: | :----------: |:----------: |:----------: |:----------: |:----------: |:----------: |:----------: |
| $c_i$ | $1$ |$1+1 $ |$-1$|$2$|$-2$|$0-1$|$3$|

我们发现，这个差分数组仅仅只是修改了两个地方，但却引导着 $a_i$ 的变化！
	
易得公式：

$a_l+y,a_{l+1}+y\dots a_r+y \Rightarrow c_l+y,c_{r+1}-y$

即：修改 $a_{l\sim r}$，可以导致 $c_l$ 和 $c_{r+1}$ 的变化，反之一致。

~~你们可以自己证明一下。~~

现在，我们已经求出了上方程所有的参数，现在我们只要枚举 $x$ 即可！详细见代码：

方程放这里方便你们和代码一起食用：

$F1+\sum_{i=x}^Da_i=F2$

2、代码
------------

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll C,f1,f2,d,l,r,c[(ll)2e3+25],a[(ll)2e3+25];
//解释：C、F1、F2、D，意思与题面一致。l,r表示每头牛吃饲料的左右区间；
//c[]表示差分数组，a[]表示每天的消耗 。 
ll minn=INT_MAX,maxx=INT_MIN;
int main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);//加快输出入输出，注意，加了这句话，就不能用 scanf 和 printf 了 
	cin>>C>>f1>>f2>>d;
	for(int i=1;i<=C;i++){
		cin>>l>>r;
		c[l]++;//修改差分数组 
		c[r+1]--;
		minn=min(minn,l);//确定牛吃饲料的时间区间 
		maxx=max(maxx,r);
	}
	for(int i=minn;i<=maxx;i++){
		a[i]=a[i-1]+c[i];//通过差分数组计算出a[i] 
	}
	ll x=d+1;
	while(f2!=f1){//枚举到方程成立 
		f2+=a[--x];//开始枚举x 
	}
	cout<<x;
	return 0;
}

```

---

## 作者：fangyicheng1216 (赞：4)

~~本蒟蒻第十次发题解。~~

[题目传送门](https://www.luogu.com.cn/problem/P1672)

# 思路：

~~大水题！~~

首先，题目标签里挂了差分，所以，这道题肯定要用**差分**。

**什么是差分：**

- 差分其实就是数组内每一个元素的差。

比如：

- 一个数组 $a$，$a$ 内元素分别为 $1,3,4,6,8,9$，那么差分数组内元素就是 $1,2,1,2,2,1$。（差分数组第一个就是数组的第一个）

**差分的性质：**

  - 差分的优势就在于在修改一整个区间内的数组时，差分数组仅需修改两个数。即 $a_l+1$ 和 $a_{r+1}-1$。（$a$ 是差分数组，$l$ 是修改区间左侧，$r$ 是修改区间右侧）

具体原理就是数学中等式的性质：$a-b=(a+c)-(b+c)$。

- 在 $a_l$ 这里，$b$ 并没有加 $c$。所以 $a_l$ 的值会加上 $c$。

- 在 $a_{r+1}$ 这里，$a$ 并没有加 $c$。所以 $a_{r+1}$ 的值会减去 $c$。

那么了解了差分之后，就可以顺利讲思路了！

这道题可以先开一个差分数组，然后用差分数组求出每天少的饲料，接着从 $D$ 向 $1$ 枚举即可求出答案！

~~所以说是大水题！~~

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std; 
int c,f1,f2,d;
int a[2005];//差分数组 
int main(){
	cin>>c>>f1>>f2>>d;
	for(int i=1;i<=c;i++){
		int l,r;
		cin>>l>>r;
		//根据差分性质更改差分数组 
		a[l]+=-1;
		a[r+1]-=-1;
	}
	for(int i=1;i<=d;i++) a[i]=a[i-1]+a[i];//算出前D天每天少的饲料 
	for(int i=d;i>=1;i--){//暴力查找 
		f2-=a[i];
		if(f2==f1){
			cout<<i;
			return 0;
		}
	}
    return 0;
}
```


---

## 作者：Silence_World (赞：3)

# 思路
很明显的差分，类似于板子的变式，建议没学过的先了解一下差分，学过的可以直接跳过。

## 什么是差分

在一个数轴上，每两个点会给一段区间提供一部分的贡献，要实现这个效果正常来说是要从第一个数到第二个数一个一个枚举去加，复杂度和时间都太高了，很有可能会超时，所以我们可以这样来做：

在一个数轴上先标记第一个数的点，很明显的，在他往后直到第二个数的点都会加这个贡献，所以我们开一个数组，先称第一个点为 $x$，第二个点为 $y$，从 $x$ 加这个贡献，到 $y+1$ 减去，也就是说这就代表着从 $x$ 到 $y$ 的值加完了，代码也很好实现。
 
# 本题

并不是很难，几乎裸板子题，每个区间用差分处理，从今天往后推，只要数到了题中所规定的 $f-f1$（也就是吃到的数到了消耗掉的粮食，就是粮食所运到的时候），这样本题轻松完成。

# 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[100005];
int b[100005];
signed  main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int n;
	int f,f1;
	int td;
	cin>>n>>f>>f1>>td;
	int r=0;
	while(n--){
		int x,y;
		cin>>x>>y; 
		a[x]++;
		a[y+1]--;
	}
	for(int i=1;i<=td;i++){
		b[i]=b[i-1]+a[i];
	}
	int sum=0;
	int t=0;
	for(int j=td;j>=1;j--){
		sum+=b[j];
		if(sum==f-f1){
			cout<<j;
			break;
		}
	}
	return 0;
} 
```


---

## 作者：technopolis_2085 (赞：1)

分析：

由于 $D$ 不大，所以考虑求出每天吃掉多少饲料。

对于每一头牛，设它来到仓库的时间是 $l$，离开仓库的时间是 $r$。

这头牛的贡献相当于区间 $[l,r]$ 内的每个元素都加 $1$。

这个问题可以用差分实现，即 $sum_l$ 加 $1$，$sum_{r+1}$ 减 $1$。

这样我们就求出了每天吃掉了多少饲料。

然后我们从 $D$ 开始往下枚举，每次减去当天吃掉的饲料数。当减去的所有数的和等于 $F1 - F2$ 时，说明这天的饲料有 $F1$ 千克。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
int sum[maxn];

int main(){
	int n,f1,f2,d;
	scanf("%d%d%d%d",&n,&f1,&f2,&d);
	
	for (int i=1;i<=n;i++){
		int l,r;
		scanf("%d%d",&l,&r);
		
		sum[l]++; sum[r+1]--;
	}
	
	for (int i=1;i<=d;i++) sum[i]+=sum[i-1];
	
	int num=f1-f2;
	for (int i=d;i>=1;i--){
		num-=sum[i];
		if (num==0){
			printf("%d",i);
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：WhxStar2024 (赞：0)

## 本题思路：
这道题从数据范围上看上去暴力会报时间复杂度，所以这里就需要用到差分这种算法了。

我们可以先从每一只奶牛过来吃草的时间开始看起，把高于 $d$ 天的先排除掉，随后用一个数组来把这只奶牛进来的时间加个一，再把它出去的后一天减去一，这样用前缀和就可以求出每一天有多少只奶牛在棚里吃草了。

随后我们就可以从第 $d$ 天开始暴力枚举，把进的粮食减去剩的粮食的差每次去减去当天的奶牛只数，当无粮草时输出上一天即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2001];
int main()
{
	int c,f1,f2,d;
	cin>>c>>f1>>f2>>d;
	for(int i=1;i<=c;i++)//差分 
	{
		int x,y;
		cin>>x>>y;
		if(x<=d) a[x]++;//判定，减少a数组开的空间 
		if(y<=d) a[y+1]--;
		else if(x<=d) a[d+1]--; 
	}
	for(int i=1;i<=d;i++) a[i]+=a[i-1];//前缀和 
	f1-=f2;
	for(int i=d;i>=1;i--)
	{
		if(f1<=0)//若无粮草时就是上一天进的 
		{
			cout<<i+1;
			return 0;
		}
		f1-=a[i];
	}
	return 0;
}
```


---

## 作者：lizulong (赞：0)

## 题意
有一群牛，每头牛每天吃 $1$ 千克的饲料。有天运过来 $F1$ 千克饲料，到 $D$ 天为止，还剩 $F2$ 千克饲料。

问饲料哪天运来的。
## 思路
因为要快速的改变一段区间，所以用差分优化，再暴力求解。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[5000005],ans=0,b[5000005];
int c,f1,f2,d,lai,zou;
int main() {
	cin>>c>>f1>>f2>>d;int food=f1-f2;
	for(int i=1;i<=c;i++){cin>>lai>>zou;a[lai]++,a[zou+1]--;}
	for(int i=1;i<=100001;i++) b[i]=b[i-1]+a[i];
	for(int i=d;i>0;i--){
		food-=b[i];
		if(food<=0) cout<<i<<endl;return 0;}
	}
	return 0;
}
```

---

## 作者：guozhetao (赞：0)

一题~~很简单的~~差分。
## 思路
显而易见，我们可以先算出每一天消耗的饲料数，再看从第 $i$ 天到第 $d$ 消耗的饲料数是否等于 $f1 - f2$。如果是，输出 $i$。

因为需要区间修改，可以使用差分，差分可以在极短的时间内完成区间修改。具体方法是记录每个数与前一个数的差值，对于在 $l$ 到 $r$ 的区间内加上 $1$，显然第 $l$ 个数与第 $l - 1$ 个数的差值会增加 $1$,第 $r$ 个数与第 $r + 1$ 个数的差值会减 $1$，最后还原数组即可。
## 代码
[AC 记录](https://www.luogu.com.cn/record/115606876)

```cpp
#include<bits/stdc++.h>
using namespace std;
int c,f1,f2,d,from[2005],t[2005],siliao[2005];
signed main() {
	scanf("%d %d %d %d",&c,&f1,&f2,&d);
	for(int i = 1;i <= c;i++) {
		scanf("%d %d",&from[i],&t[i]);
		//if(t[i] > d) t[i] = d;
		siliao[from[i]]++,siliao[t[i] + 1]--;
	}
	for(int i = 1;i <= d;i++) siliao[i] += siliao[i - 1];
	siliao[d] += f2;
	int ans = 0;
	//for(int i = 1;i <= d;i++) printf("%d ",siliao[i]);
	//printf("\n");
	for(int i = d;i >= 1;i--) {
		ans += siliao[i];
		if(f1 == ans){
			printf("%d\n",i);
			return 0;
		}
	}
	printf("-1\n");
}
```


---

## 作者：Code_Fish_GoodBye (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P1672)

## 思路

一道特别简单的**差分模板题**，其实也有点推理的感觉。

对于每头牛，我们通过两次循环使用差分倒推出在这几天内它对我们饲料消耗的贡献，进而推出每一天的饲料消耗量，从 $D$ 天到现在一共吃掉的饲料数为 $F1-F2$ 的那一天即是我们所求的。

输入的时候依照题意模拟一次差分，扫一遍差分，算出每一天的饲料消耗量，再扫一遍每天饲料消耗量，用一个变量储存在算出从 $D$ 天到现在一共吃掉的饲料数，推出上一船饲料运到的时间。时间复杂度为 $O(c+2d)$。 

参考代码（请勿抄袭）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int c,f1,f2,d,begi,en,b[20005],sum[20005],s;//b为差分数组，sum为每天的消耗量数组，s为这一天的饲料总和

int main(){
    scanf("%d%d%d%d",&c,&f1,&f2,&d);//输入牛的数量，运来的饲料量，剩下的饲料量
    for(int i=1;i<=c;i++){
        scanf("%d%d",&begi,&en);//输入每头牛来和走的时间
        b[begi]++;
        b[en+1]--;//差分
    }
    for(int i=1;i<=d;i++) sum[i]=sum[i-1]+b[i];//算出每天饲料消耗量
    for(int i=d;i>=1;i--){//从现在往以前倒推
        s+=sum[i];//算出从D天到现在一共吃掉了多少饲料
        if(s==f1-f2){//找到了满足条件的那一天
            printf("%d",i);//输出结果
            exit(0);//结束程序
        }
    }
    return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/P1672)

### 简单分析

将时间理解成轴，牛来的和去的时间理解成线段，在这个线段内的时间消耗的草量增加一。很容易想到用 **差分** 解决类似问题。不会的自行百度。

差分处理完后，问题来到了时间上。看似饲料送来的时间很棘手，但是其实很好解决：

- 一开始送来 $F1$ 千克，现在还剩 $F2$ 千克，所以这段时间内消耗了 $F1-F2$ 千克。
- 由题可知饲料一直到今天（也就是 $D$）都没有断过，考虑从今天开始往前推，每次处理出当前还剩下的饲料，直到推回和 $F1$ 相等即为答案。

没看懂？给代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e3+10;

int Q,f1,f2,d,a,b,diff[N];

signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>Q>>f1>>f2>>d;
	while(Q--){
		cin>>a>>b; 
		if(a>d)continue;
		if(b>d)b=d;//这里两个是担心题目会有超过 D 的数据（而且样例里面确实有）
		diff[a]++;
		diff[b+1]--;
	}
	for(int i=1;i<=d;i++)diff[i]+=diff[i-1];//简单差分，归回
	for(int i=d;i>=1;i--){//从后往前推日期
		f1-=diff[i];//这里也可以是 f2+=diff[i]，自行选择
		if(f1==f2){//推到相等时
			cout<<i;
			break;
		}
	}
    cout<<0;
	return 0;
} 
```

---

## 作者：Light_Star_RPmax_AFO (赞：0)

### 前言

[传送门](https://www.luogu.com.cn/problem/P1672)

[blog](https://www.luogu.com.cn/blog/JJL0610666/solution-p1672)

## 差分

差分可以理解为前缀和的逆运算，可以快速的改变一段区间。

[差分](https://blog.csdn.net/qq12323qweeqwe/article/details/122118514)

# 思路

差分模板题，可以用其算出每天所吃的饲料，然后我们就可以从 $D$ 开始倒推，如果有一天刚好吃的是 $F1-F2$，也就是说在那天肯定是进了货的，详解看代码。

$sum_i$ 用来记录改变之后的差分数组，$b_i$ 用来记录每一天吃了多少包。

```cpp

#include <bits/stdc++.h>
using namespace std;

int c,f1,f2,d; 
int sum[2010],b[2010];
int main(){
	scanf("%d%d%d%d",&c,&f1,&f2,&d);
	for(int i = 1;i <= c;i++){
		int begin,end;
		scanf("%d%d",&begin,&end);
		sum[begin]++,sum[end + 1]--;//差分
	} 
	for(int i = 1;i <= d;i++){
		b[i] = sum[i] + b[i - 1];//运用前缀和算出牛来了之后的数组，也就是每天牛总共的饲料重量。
	}
	int ans = 0;
	for(int i = d;i >= 1;i--){
		ans += b[i];//如果有一天刚好吃的是 f1-f2 那么肯定在这天进货。
		if(ans == f1 - f2){
			cout<<i;
			return 0;
		} 
	}
	return 0;
}

```

---

## 作者：hubin1 (赞：0)

# [USACO05FEB] Feed Accounting S

## 题意
- 约翰养了一群牛，每头牛每天吃 $1$ 千克的饲料。
- 某天运来 $F1(1\le F1\le 10^6)$ 千克的饲料，到第 $D(1\le D\le 2\times 10^3)$ 天为止，仓库里还剩下 $F2(1\le F2\le F1)$ 千克饲料。
- 让我们求哪天运来的饲料。

## 思路
- 可以先差分求出前 $D$ 天一共消耗了多少饲料。
- 我们从后向前用 $F1$ 和 $F2$ 的差减去之前求出的数据，当这两个数的差为 $0$ 时，就意味着这天送来了饲料。

## Code
``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAX=1e4;
int a[MAX];
signed main()
{
    int C,F1,F2,D;
    cin>>C>>F1>>F2>>D;
    for(int i=1;i<=C;i++)
    {
        int l,r;
        cin>>l>>r;
        a[l]++;
        a[r+1]--;
        //前缀和
    }
    for(int i=1;i<=D;i++)
        a[i]=a[i-1]+a[i];
    int temp=F1-F2;//求差
    for(int i=D;i>=1;i--)
    {
        if(temp-a[i]==0)//判断今天是不是送来了饲料
        {
            cout<<i<<endl;
            return 0;
        }
        else
            temp=temp-a[i];
    }
    return 0;
}
```

---

## 作者：FreedomKing (赞：0)

差分板子题，适合练手。

### 思路

直接使用差分维护每天牛牛们一共吃了多少，还原序列，然后从第 $n$ 天开始也就是今天往前遍历，只要遍历过的那 $x$ 天被吃掉的饲料总数刚好等于送来的饲料减去还剩的饲料数，即 $\sum\limits_{i=x}^D a_i=F1-F2$，$x$ 即为答案。

------------

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int a[N],n,m,t,k;
signed main(){
	cin>>n>>m>>t>>k;
	for(int i=1;i<=n;i++){
		int l,r;
		cin>>l>>r;
		a[l]++;
		a[r+1]--;
	}
	for(int i=1;i<=k;i++) a[i]+=a[i-1];
	while(!(m==t)){
		m-=a[k];
		k--;
	}
	cout<<k+1;
	return 0;
}
```

---

