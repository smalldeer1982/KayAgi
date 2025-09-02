# Paint the Numbers

## 题目描述

给出一个长度为$n$的序列$a_1,a_2,a_3,...\ ,a_n$，要求你使用最少的颜色对每个染色。对于任何颜色，满足：染成该颜色的数都能被染成该颜色的最小数整除。

比如$[40,60,10]$可以被染成同一种颜色，因为它们都可以被$10$整除。

每种颜色可以使用一次或多次。染成同一个颜色的所有元素不需要是连续的。请求出最少需要的颜色数量。

## 说明/提示

$1 \leq n \leq 100$, $1 \leq a_i \leq 100$

### 样例解释

样例1：$[ {\color{red}{10}}, {\color{blue}{2}}, {\color{orange}{3}},{\color{red}{5}}, {\color{blue}{4}}, {\color{blue}{2}} ]$

样例2：$[ {\color{red}{100}}, {\color{red}{100}}, {\color{red}{100}},{\color{red}{100}} ]$

样例3：$[ {\color{gray}{7}}, {\color{blue}{6}}, {\color{orange}{5}},{\color{red}{4}}, {\color{blue}{3}}, {\color{red}{2}}, {\color{red}{2}}, {\color{blue}{3}} ]$

## 样例 #1

### 输入

```
6
10 2 3 5 4 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
100 100 100 100
```

### 输出

```
1
```

## 样例 #3

### 输入

```
8
7 6 5 4 3 2 2 3
```

### 输出

```
4
```

# 题解

## 作者：dz_ice (赞：4)

我先来大致讲一下题意

就是说你把每个元素涂上颜色，并且这个颜色的所有元素必须要被涂了这个颜色的最小元素整除，要使用的颜色尽量少，并输出使用的颜色数量

cf的a题还是比较容易想的，我们可以用贪心的思想，先从小到大排一遍序，每次取最小的数字来涂色ans++，就可以得到答案

上代码

```
#include<bits/stdc++.h>
using namespace std;
int n,a[103],b[103],ans;
int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		scanf("%d",&a[i]); 
	sort(a+1,a+n+1); //从小到大排序
	for(int i=1; i<=n; i++) 
		if(b[i]==0) //没有被涂过才能作为颜色
		{
			ans++; 
			for(int j=i+1; j<=n; j++) //对后面的数涂色
				if(a[j]%a[i]==0)
					b[j]=1;
		}
	cout<<ans;
	return 0;
}
```


---

## 作者：__shadow__ (赞：3)



【问题分析】 

方法一：排序后从小到大排查，因为同色的数必须要是此色中最小数的倍数，又因为小的数不可能是大的数的倍数，所以从小开始算，把后面它的倍数都标记掉。记颜色的数量。

方法二：因为数的最大小于等于 $100$ ，所以可以用桶排来写，把所有数分别装入相应的桶中后，从桶 $1$ 开始到桶 $100$ 。如果桶内有数，把它的倍数的桶中的数全部清空。记颜色的数量。

【设计程序】

方法一：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<stdio.h>
#include<cstdio>
#include<queue>
using namespace std;
const int N = 100 + 5;
int a[N];
int n, sum;
int main()
{
	scanf ("%d", &n);
	for (int i = 0;i < n; i++)//输入n个数
		scanf ("%d", a + i);
	sort(a, a + n);//排序
	for (int i = 0;i < n; i++)
	{
		if (a[i] == 0)//如果已经有颜色，则开始下一个
			continue;
		sum++;//如果没颜色，加一种颜色
		for (int j = i + 1;j < n; j++)//把它的倍数标掉
			if (a[j] % a[i] == 0)
				a[j] = 0;
		a[i] = 0;
	}
	printf ("%d", sum);//输出
	return 0;
}
```


方法二：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<stdio.h>
#include<cstdio>
#include<queue>
using namespace std;
const int N = 10000 + 5;
int a[N];
int n, t, sum;
int main()
{
	scanf ("%d", &n);
	for (int i = 0;i < n; i++)
	{
		scanf ("%d", &t);//输入数
		a[t]++;//装入桶
	}
	for (int i = 1;i <= 100; i++)//每一只桶遍历过去
	{
		if (a[i] == 0)//如果为空
			continue;//下一只
		sum++;//否则加一种颜色
		a[i] = 0;//清空这只桶
		for (int j = 1;j <= 100 / i; j++)//找是它的倍数的桶
			a[i * j] = 0;//清空
	}
	printf ("%d", sum);//输出
	return 0;
}
```


【代码调试】

1.	测试样例

2.	自测数据（边界值，特殊值， 本题中有特殊值了）

完结撒花

---

## 作者：KEBrantily (赞：1)

所谓染色，并使同颜色数都能被**当前颜色中最小的数**整除

#### 也就是说，把能被某个数整除的所有数放在一起为一组，问共有几组

开始我想写个并查集~~但是很懒~~，看数据范围小的可怜，那我们写个暴力看看

因为每组的共因数都是本组最小，那就先从小到大排序

枚举每个没被标记过的数，从这个数开始往后找，碰到能被他整除的就打标记

然后计数器加一

最后输出就好了

```cpp
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define maxn 100010

using namespace std;

int n,a[maxn],vis[maxn],sum;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(!vis[i]){
//		    vis[i]=1;
		    sum++;	
		}
		for(int j=i+1;j<=n;j++){
			if(a[j]%a[i]==0)
			vis[j]=1;
		}
	}
	cout<<sum;
	return 0;
}
```
请各位批评指正

~~这道题不会真有人来看题解吧~~

---

## 作者：dead_X (赞：1)

# 突然发现这道题挺水的，于是来写一篇题解
## 0 前面的话
显然，dX很菜，这次CF炸了，A愣是写不出QWQ

结果只做出了BCD D还WA了好多次 遗憾掉分。

比完之后又回来看了一眼题面，突然就发现这是一个傻逼贪心题/kk
## 1 题目分析
这道题看起来解法很多，事实上一直在想O(nlogn)的dX一直没看数据范围

**其实就是O(n^2)乱搞就行啦**
## 2 贪心策略
显然，如果一个数能整除另一个数，那么这两个数就可以是同一个颜色了。

那么，我们就认为其中较大者可以不使用新的颜色。

对所有的数全部跑一边，然后统计即可。

(小声bb:这个应该不用证明了吧)
## 3 Code
```
#include<bits/stdc++.h>
using namespace std;
int a[103];
bool f[103];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=n; i>1; i--) for(int j=i-1; j>0; j--) if(a[i]%a[j]==0)
   	{
		f[i]=1;
		break;
	}
	f[1]=0;
	int ans=n;
	for(int i=1; i<=n; i++) ans-=f[i];
	printf("%d",ans);
	return 0;
}
```
## 4 后记
标准橙题，放在div2A还是难度比较正常的

显然是dX太菜了qwq

---

## 作者：一梦南柯 (赞：1)

这道题考的时候被好几个人1min切掉，自闭了qwq

### [题面戳这](https://www.luogu.org/problem/CF1209A)

  题目大意

- 给你一串序列$a_1,a_2....a_n$，要求你在其中选出最少的数(不需连续)，使得这个序列里面的所有数能够被其中至少一个数整除

------------
 根据题目描述，我们知道一个数要么是被选，要么是被其他数整除，而最小的数是不可能被其他数整除的
 
 可以贪心

故我们先排序一下，选出最小的那个数，再把剩下的数扫一遍，标记出已被整除的数，继续这个思路，扫出一个又一个的最小的数，因为这个数既然不被整除，就只能被选了

时间复杂度最坏$O(n^2)$

~~殆马~~如下
```
#include<bits/stdc++.h>
#define rint register int
//据说红题题解不许用define
//上面那个东西(用的好)可以使程序变快
using namespace std;
int n,ans;
int a[105];
bool bj[105];//标记一个数是否已被整除
int main()
{
	cin>>n;
	ans=n;
	for(int i=1;i<=n;++i) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i)
	{
		if(bj[i])
		{	
			ans--;
			continue;
		}
		for(int j=i+1;j<=n;++j)
			if(!(a[j]%a[i])) bj[j]=1;
	}
	cout<<ans<<endl;
	return 0;
}
```

[更坏的阅读体验](https://www.luogu.org/blogAdmin/article/edit/169807)

---

## 作者：QcpyWcpyQ (赞：0)

- ~~老师作业布置了这题，发现挺水就正好水一发题解。~~


------------
数据范围$N\leq 100$,可以随便玩了。考虑贪心：若一个数能被另一个数整除，那么这两个数字会被涂上相同的颜色。因此在较小数在被染色时较大数也会被染，较大数就不用重新染色了。

- 所以得出算法流程：	

1. 将序列从小到大排序。
2. 枚举每个没被标记过的数，从这个数开始往后找，找到能被他整除的就标记。
3. 当整个序列搜索一遍后，计数器加一。若序列中还有未被标记的返回2.，否则跳出循环，输出计数器。


------------
~~马蜂太丑~~，就不贴上了。

---

## 作者：YONIC (赞：0)

# [CF1209A Paint the Numbers](https://www.luogu.com.cn/problem/CF1209A)
本题作为一道关于“整除”的数学题，刚看到的时候，脑子里就出现了以前写线性筛，杜教筛，$\mathcal{Pollard-Rho}$ 挂了许多次的画面。但一看题目难度标了橙：好了，放心了，又看了看数据范围中 $n\leq100$ 那就更没事了。

于是我写完这道题就来水题解了。

思路是什么呢，就是说我们考虑一个尚未染色，已经排好序了的数组。这个数组里面的最小值显然需要染色，然后我们把它染上一种颜色以后往大了找它的倍数，全都染上这种颜色（不染白不染），这样我们就清除了所有的倍数，缩小了数组的大小，此时最小值会更新，于是我们就可以重新走一遍这个程序，以此类推。

分析时间复杂度：每一个更新版本中的最小值都会往这个数组的最大端走一遍，每一次更新至少染色一个最小值，时间复杂度为 $\operatorname{O}(n^2)$，对本题来说绰绰有余。

Code:
```
#include<bits/stdc++.h>
using namespace std;
int n,cnt,a[103],f[103];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",a+i);
    sort(a+1,a+n+1);//记得排序
    for(int i=1;i<=n;++i) if(!f[n]){for(int j=i;j<=n;++j) if(a[j]%a[i]==0) f[j]=1; ++cnt;}
    printf("%d",cnt);
    return 0;
}
```

---

## 作者：Zxsoul (赞：0)

# 贪心+模拟+桶排序
##  题面：
### [题目传送门](https://www.luogu.com.cn/F1209Aproblem/C)
## 想法：
	1. 题中需要分成至少k份（回忆题意），
    2.思路就可以往贪心上想，至于分组，题中说每组数都是最小值的倍数
    3.So,我们可以先排序，将小数及其和他的倍数放在一个桶里（桶排序），
    4.如果当前数不是这个小数的倍数，那就重新以当前数为小数重新开桶（贪心）
### 思路：

 1. 先排序，从小到大取模。
 
2. 用桶排序，开桶储存需要染色的种类（即被mod的数）
   
 3. 记录桶的个数，最后输出ans 
 
# Code
```c
/*
  CF1209A Paint the Numbers
  2020/10/4
  by BZQ
*/ 
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,a[209],vis[209],s,ans,b[209];//vis[]表示该数是否已放入桶中，b[]是记录每个数的桶标号 
int main(){
	cin >> n;
	for (int i = 1;i <= n; i++)cin >> a[i];
	sort(a+1,a+1+n);//排序 
	for(int i = 1;i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(a[i] % a[j] == 0 && vis[i]==0 )
			{
				vis[i] = 1;//标记已经被查询过 
				b[i] = a[j];//标记桶标号。 
			}
		}
	}
	sort(b+1,b+n+1);//将桶排序，便于比较出桶的数量 
	for(int i = 1;i <= n; i++){
		//<<a[i]<<" "<<b[i]<<endl;
		if(b[i] != b[i-1]){
			ans++;
		}//如果桶的标号不一样就证明有新的桶加入 
	}
	cout<<ans;
}
```
# 如果有不明白的可以问我，My Bolg

---

## 作者：yizr_cnyali (赞：0)

因为题目要求每个数和它的最小的约数以及所有倍数的颜色相同,且需要最小化使用的颜色数量,我们可以用一个桶来存储所有出现过的元素。

因为同一元素出现多次不会影响它所涂的颜色,我们不需要记录元素出现的次数

然后,从小到大扫一遍这个桶,把每个还没有被筛掉的元素和它的倍数一起筛掉,每进行一次这个操作,就将使用的颜色数+1。由于是从小到大扫的,所以扫到的没被筛掉的元素不会有约数,因为如果有约数,在扫到最小者时,这个元素就会被筛掉,与扫到时这个元素没有约数矛盾。

最后输出使用的颜色数即可

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

template <typename T> inline int Chkmax (T &a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline int Chkmin (T &a, T b) { return a > b ? a = b, 1 : 0; }

template <typename T> inline T read(){
    T sum = 0;
    int fl = 1,ch = getchar();
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') fl = -1;
    for(; isdigit(ch); ch = getchar()) sum = (sum << 3) + (sum << 1) + ch - '0';
    return sum * fl;
}

const int maxn = 100 + 5;

int n;
bool book[maxn];

inline void Solve (){
	int ans = 0;
	for(int i = 1; i <= maxn; i++){
		if(book[i]){
			for(int j = i; j <= maxn; j += i){
				book[j] = false;
			}
			ans++;
		}
	}
	printf("%d\n",ans);
}

inline void Input (){
	n = read<int>();
	for(int i = 1; i <= n; i++){
		book[read<int>()] = true;
	}
}

int main(){
	Input();
	Solve();
	return 0;
}
```


---

## 作者：Meatherm (赞：0)

暴力枚举大法好。

我们每次枚举每一个没有被填涂颜色的 $a_i$，然后判断由它做“基数”最多能填涂掉多少颜色。选其中一个最大的，将所有 $a_j\mod a_{max} =0$ 的 $a_j$ 填涂颜色。

时间复杂度：$O(n^3)$。

```cpp
# include <bits/stdc++.h>
# define rr register
const int N=110;
bool use[N];
int a[N];
int sum;
int n,gca;
int main(void){
	std::cin>>n;
	for(rr int i=1;i<=n;++i)
		std::cin>>a[i];
	while(gca<n){
		++sum;
		int maxid=-1,maxsum=0;
		for(rr int j=1;j<=n;++j){
			if(use[j])//判断是否使用过，避免重复计算
				continue;
			int tmp=0;	
			for(rr int k=1;k<=n;++k){
				if(a[k]%a[j]==0)
					++tmp;
			}
			if(tmp>maxsum)
				maxsum=tmp,maxid=j;
		}
		for(rr int j=1;j<=n;++j){
			if(!use[j]&&a[j]%a[maxid]==0){
				++gca,use[j]=true;
			}
		}
	}
	printf("%d",sum);
	return 0;
}
```

---

## 作者：fighter (赞：0)

作为一道A题，还是挺简单的

很显然，不管已经涂了多少种颜色，未涂色的数字中的最小值是一定需要单独染色的，那么同时它的倍数可以和它染成相同的颜色（倍数如果不然显然不优）。所以每次我们找到未涂色的最小值，然后把全部倍数染色即可。

```cpp
#include <bits/stdc++.h>
#define MAX 105
using namespace std;

int n, a[MAX], vis[MAX];

int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	sort(a+1, a+n+1);
	int cnt = 0;
	for(int i = 1; i <= n; i++){
		int p = 0;
		for(int j = 1; j <= n; j++){
			if(!vis[j]){
				p = j;
				break;
			}
		}
		if(!p) break;
		for(int j = p; j <= n; j++){
			if(a[j]%a[p] == 0) vis[j] = 1;
		}
		cnt++;
	}
	cout << cnt << endl;
	
	return 0;
}
```

---

