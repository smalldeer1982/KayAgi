# [USACO08MAR] Pearl Pairing G

## 题目描述

At Bessie's recent birthday party, she received $N(2 \le N \le 10^5,N\equiv0\pmod{2})$ pearls, each painted one of C different colors ($1\le C \le N$).

Upon observing that the number of pearls $N$ is always even, her creative juices flowed and she decided to pair the pearls so that each pair of pearls has two different colors.

Knowing that such a set of pairings is always possible for the supplied testcases, help Bessie perform such a pairing. If there are multiple ways of creating a pairing, any solution suffices.

在 Bessie 最近的生日聚会上，她收到 $N(2\le N \le 10^5,N\equiv0\pmod{2})$ 颗珍珠。一共有 $C$ 种颜色的珍珠（$1\le C \le N$），第 $i$ 种颜色的珍珠有 $C_i$ 颗。


观察到珍珠的数量 $N$ 总是偶数，她的创意来了，决定配对珍珠，使每对珍珠有两种不同的颜色。数据保证存在答案。请帮助 Bessie 执行这样的配对，如果有多种配对的方法，输出任意一种即可。

## 说明/提示

There are $8$ pearls and $3$ different colors. Two pearls have color $\mathrm{I}$; two have color $\mathrm{II}$; four have color $\mathrm{III}$.


Bessie pairs each pearl of color $\mathrm{III}$ with one of color $\mathrm{I}$ and $\mathrm{Ii}$.

说明：有 $8$ 颗珍珠和 $3$ 种不同的颜色。两颗珍珠颜色为 $1$，两颗珍珠颜色为 $2$，四颗珍珠颜色为 $3$。

Bessie 将每颗颜色为 $3$ 的珍珠与颜色为 $1$ 和 $2$ 的珍珠配对。

感谢@[线段木](https://www.luogu.com.cn/user/33930) 提供翻译，@[PineappleSummer](https://www.luogu.com.cn/user/880187) 修正翻译以及提供 $\LaTeX$。

## 样例 #1

### 输入

```
8 3 
2 
2 
4 
```

### 输出

```
1 3 
1 3 
2 3 
3 2 
```

# 题解

## 作者：Waddles (赞：21)

这道题没有更优的解法？

那我来发一波

分成N/2组（毋庸置疑）

每一种颜色数量肯定小于N/2（毋庸置疑）

读入时将每一种展开，依次配对

这种算法实现的依据是每种颜色不超过N/2，所以第i种颜色和i+n/2配对，就可以保证不重复，且不遗漏，如果用其他的方法我觉得麻烦一些


题解区居然没有这种解法

$code$:

```
#include<map>
#include<cmath>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;//头文件
template<class AK>void r(AK &x){//快读
    x=0;
    int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        f|=(ch=='-');
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    x=f?-x:x;
    return;
}
int n,m,a[1000005],top;
int main(){
    r(n);r(m);
    for(int i=1;i<=m;i++){
    	int x;
    	r(x);//读入个数
    	while(x--)a[++top]=i;//展开
	}
	for(int i=1;i<=n/2;i++)printf("%d %d\n",a[i],a[i+n/2]);//配对输出，就是那么简单
    return 0;//结束
}
```

---

## 作者：御·Dragon (赞：12)

2020 年 1 月 17 日更新题解报告：

评论区有同学说不用快排。我试了试~~WC还真可以~~，非常感谢评论区前排同志。其实还是要快排的，只是数据太水，具体原因看下面。

然后浮现这题的题解我这种做法越来越多，但是我毕竟是这种思路的第一奠基人~~此乃事实，别喷我~~，为了我的算法保持领先的状态，还是改了码风，详细了思路。

------------

这题有点像脑筋急转弯，想通了就很简单

## 题目大意：

$N$ 个元素（$N$ 为偶数），需要你来染色。现在需要两个元素为一组，且每一组的元素颜色要保证不同，求任意一种解法。

## 题意分析：

其实我们来看看，为了保证有解，即有一种方案使得 __两个元素为一组，且每一组的元素颜色要保证不同__ ，所以 __不可能有某种珍珠会超过总数的一半__ （否则根据小奥，一定会有两个相同颜色的元素在一组）。

且我们知道： __一共有 $N$ / 2 组__

这个就是抽屉问题（鸟巢问题），想明白了就很简单。

## 具体操作：

题目给的是每种颜色的数量，我们不妨将 每种颜色的元素数量 转化为 每个元素的颜色。

根据小奥，我们一般做抽屉问题时都是按照 __将每种颜色的珍珠按照每组一个__ 的方式操作。

然后为了正解，我们可以先按照 __每种颜色的元素数量__ 从大到小排序，那么由于不可能有某种珍珠会超过总数的一半，所以即便元素数量最多的颜色的那些元素，排完序后也不可能有一个元素超过中点。

故我们不妨将 第 $i$ 个元素与 第 $i + (n / 2)$ 个元素合成一组，这样可以方便而快速的避免无解。

数据太水，不排序也能过，博主太懒，也把排序略了。

__AC代码在此镇楼：__

```
#include<bits/stdc++.h>
#include<cctype>
#pragma GCC optimize(2)
#define in(n) n = read()
#define out(a) write(a)
#define outn(a) out(a),putchar('\n')
#define Min(a,b) a < b ? a : b
#define Max(a,b) a > b ? a : b
#define ll long long
#define New ll
#define rg register
using namespace std;

namespace IO_Optimization
{
	inline New read()//快读 
	{
	    New X = 0,w = 0;
		char ch = 0;

		while(!isdigit(ch))
		{
			w |= ch == '-';
			ch=getchar();
		}
	    while(isdigit(ch))
		{
			X = (X << 3) + (X << 1) + (ch ^ 48);
			ch = getchar();
		}
	    return w ? -X : X;
	}

	inline void write(long long x)//快输 
	{
	     if(x < 0) putchar('-'),x = -x;
	     if(x > 9) write(x / 10);
	     putchar(x % 10 + '0');
	}
}
using namespace IO_Optimization;

const int MAXN = 100000 + 2;//定义常量 

int s[MAXN]; //记录每个珍珠的颜色 
int n,c,k;//如题，k为输入时当前有了多少珍珠数量 

int main()
{
	in(n),in(c);//输入 
	for(rg int i = 1;i <= c; ++i)
	{//枚举 
		int x = read();//输入每种颜色的数量 
		for(rg int j = 1;j <= x; ++j)//保存每个珍珠的颜色  
			s[++k] = i;//每次k加1,s[k] = i即可
	}
	n >>= 1;//N /= 2 
	for(rg int i = 1;i <= n; ++i)//截半枚举 
		out(s[i]),cout<<" ",outn(s[i + n]);//截半输出 
	return 0;
}
```

---

## 作者：Exber (赞：5)

## 做法
这道题十分的简单，建议评红……

只要把每一颗珍珠都存起来，最后再前一半珍珠和后一半珍珠配对就行了。

## AC 代码
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int n,c,tot,num[10000005]; // 数组尽量开大点 

int main()
{
	scanf("%d%d",&n,&c);
	for(int i=1;i<=c;i++)
	{
		int x;
		scanf("%d",&x);
		while(x--)
		{
			num[++tot]=i; // 每一颗珍珠存起来 
		}
	}
	for(int i=1;i<=n/2;i++)
	{
		printf("%d %d\n",num[i],num[i+n/2]); // 输出 
	}
	return 0;
}
```


---

## 作者：MloVtry (赞：4)

模拟模拟%

首先我们贪心的操♂作，数量最多的牛（颜色）一定要先铺放

所以我们先把每一对铺上一个颜色

然后呢，再去找每一对的对应颜色

具体的，我们枚举每一对牛

首先，第一遍，铺放（也就是每一对的第一头牛）

维护一个指针，指向某种颜色的牛

然后呢，一直铺下去，直到没有这个颜色 的牛为止；用完之后就换一种颜色（拔吊无情）

随后开始第二遍，操作是一样的，不过这一次我们放了每一对的第二头牛，也就可以输出了

口胡功力好差...看代码吧...

代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#define N 100010
using namespace std;
int col[N],n,c;
struct node
{
    int nu,id;
}a[N];
bool comp(node aa,node bb){return aa.nu>bb.nu;}
int main()
{
//    freopen("ppairing.in","r",stdin);
//    freopen("ppairing.out","w",stdout);
    scanf("%d%d",&n,&c);
    n/=2;
    for(int i=1;i<=c;++i) scanf("%d",&a[i].nu),a[i].id=i;
    sort(a+1,a+c+1,comp);
    int j=1;
    for(int i=1;i<=n;++i)
    {
        a[j].nu--;
        col[i]=a[j].id;
        if(!a[j].nu) j++;
    }
    for(int i=1;i<=n;++i)
    {
        a[j].nu--;
        printf("%d %d\n",col[i],a[j].id);
        if(!a[j].nu) j++;
    }
    return 0;
}
//我永远喜欢U47.jpg
//10月到了，又是一个换老婆的季节~
//柚子好棒啊~~~w~~~~~~
```

---

## 作者：qingfengwuhui (赞：3)

首先，这是一道贪心。
于是我们要想它的贪心策略。

---------
### First

先看题干：
这道题目的目的是让我们求出n / 2 组以两颗颜色不同的珍珠组成的组合。


既然这样，我们可以先sort ，将全部的珍珠按降序排列，接着每次将最高位和次高位的两种珍珠组合并减1，再分别使用两次冒泡，将这两种珍珠下移，使当前的序列仍未降序，再重复操作。

如此，代码的框架就出来了：
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n , c;
struct xi{
	int m;
	int c;
}a[100020];//一个结构体 表示以 c 为颜色的珍珠有 m 颗
bool cmp(xi x , xi y){//将全部的珍珠从大到小排列
	return x.m > y.m;
}
void Swap(int x , int y){//因为冒泡时要将颜色和数量都交换，所以写成函数
	swap(a[x].m , a[y].m);
	swap(a[x].c , a[y].c);
	return ;
}
int main(){
	cin >> n >> c;
	for(int i = 1;i <= c;i ++){//输入
		cin >> a[i].m;
		a[i].c = i;
	}
	sort(a + 1 , a + c + 1 , cmp);//排列
	for(int k = 1;k <= n / 2;k ++){
		cout << a[1].c << " " << a[2].c << endl;
		a[1].m -- , a[2].m --;//将最高和次高的珍珠输出并减小
		int i = 2;//进行两次冒泡操作，使序列恢复降序
		while(a[i].m < a[i + 1].m && i < c){
			Swap(i , i + 1);
			i ++;
		}
		i = 1;
		while(a[i].m < a[i + 1].m && i < c){
			Swap(i , i + 1);
			i ++;
		}
	}
	return 0;
}
```
这个代码是80分（~~其实是因为数据水才这样的~~）
[这是结果](https://www.luogu.com.cn/record/28116511)

还是较为理想的，当时我们还要优化。

--------
### Second

在代码中，能优化的部分只有循环。

原代码中，每次输出后都重新排序有些浪费。于是，我将一次一次减改为一个for循环

即：
```cpp
int j = 1;
	while(1){
		if(a[j].m > a[j + 1].m)
		Swap(j , j + 1);//将最大的珍珠换到次位 并 将次大珍珠换到第一位 可以省略但是下面的都要修改
		for(int i = 1;i <= a[j].m;i ++)//输出
		cout << a[j].c << " " << a[j + 1].c << endl;
		j ++;//这里要注意，由于后面不会再使用到当前次大的珍珠，所以只用减小一个
		a[j].m -= a[j - 1].m;//将次大的珍珠个数减小
		if(a[j].m == 0)
		j ++;
		if(j >= c)
		return 0;
	}
```
[结果在这里](https://www.luogu.com.cn/record/28132964)

虽然不再有TLE，
但是十分不幸，分数反而减少了10分。
冥思苦想的我在调了许久，（~~并下载了数据~~）后，终于发现了错误！！！

---
解释：：

1000 5

119

497

117

132

135


来看这组数据：

当我们使用这个代码来解决时，答案会少3组。

为什么呢？？？

其实，当我们进行到最后时，会有6个相同的珍珠余下。
此时，程序会直接跳出循环，而剩余的6个相同珍珠将不会处理。

---
### Third

那么这就意味着这种贪心的策略行不通吗？

夜间不停地想，终于想出了解决办法。

让我来解释一下。

在生活中，如果让你做同样的事情，但只有很少的堆数。当你发现做完后，有些许重复的珍珠余下，你会怎么办？

如 

10 3

2

4

4

这样的数据。
当我们用上述的办法解决后，会有两颗1号的珍珠余下。

即当前的排列为：

3 2

3 2

3 2

3 2

1 1

这时，我们发现最后有一组两颗珍珠的颜色相同。

此时，我们可以将前面组好的组合中选出几颗进行交换（注意要不能影响到前面的组合），就可以完成任务。

即将最后一组的第一个珍珠与第一组的第一个交换。

这样，答案就是：

1 2

3 2

3 2

3 2

3 1

源代码的问题就解决了

不过如果使用源代码，第一组已经输出，不能交换。所以，我们要用一个数组来存储。因为输出数据不大，所以数组可以存储

这样，既不会影响前面的组合，也能解决当前的贪心策略的漏洞。

AC代码如下：
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n , c;
struct xi{
	int m;
	int c;
}a[100020];
struct si{
	int x , y;
}dep[100000 / 2 + 1];//存储当前的所有答案，包括正确的 和 错误的
int head = 1;//记录当前的正确答案个数 + 1
bool cmp(xi x , xi y){//排序
	return x.m > y.m;
}
void Swap(int x , int y){//交换
	swap(a[x].m , a[y].m);
	swap(a[x].c , a[y].c);
	return ;
}
int main(){
	cin >> n >> c;
	for(int i = 1;i <= c;i ++){//输入
		cin >> a[i].m;
		a[i].c = i;
	}
	sort(a + 1 , a + c + 1 , cmp);//排序
	int j = 1;
	while(1){//由于是直接执行到只剩下有相同颜色的珍珠余下，可以直接在 while 中判断并跳出
		if(a[j].m > a[j + 1].m)
		Swap(j , j + 1);//同上 可以省略，但下面的都要修改
		for(int i = 1;i <= a[j].m;i ++){
			dep[head].x = a[j].c;
			dep[head].y = a[j + 1].c;//将原本的输出改为存入
			head ++;//正确答案个数加一
		}
		a[j + 1].m -= a[j].m;
		a[j].m = 0;
		j ++;//这里要注意，一定要先减小最大的珍珠数量 在清空次大的 否者最大的珍珠个数将不变
		if(a[j].m == 0)//当当前的第一位珍珠个数为零时 j 再++
		j ++;
		if(j >= n){
			head --;//表示当前除去余下珍珠后正确的答案长度
			if(a[j].m){
				for(int k = 1;k <= a[j].m / 2;k ++){//将所有余下的珍珠两两组合
					dep[k + head].x = a[j].c;
					dep[k + head].y = a[j].c;
				}
				for(int k = 1;k <= a[j].m / 2;k ++)//与前面的交换
				swap(dep[k].x , dep[k + head].x);
			}
			break;
		}
	}
	for(int i = 1;i <= head + a[j].m / 2;i ++)//输出
	cout << dep[i].x << " " << dep[i].y << endl;
	return 0;
}
```

[结果](https://www.luogu.com.cn/record/28145310)

这样就可以完美地解决这个问题。

-------
###### ~~写得不好，大佬勿喷~~

# END

---

## 作者：木木！ (赞：3)

这题是道脑筋急转弯题emmmm，但是，智商不够，数据结构来凑。

容易想到，如果每次将最大的和次大的配对，那么一定可行。

证明？找不出反例不就证出来了吗……反正证证更健康qwq。

容易发现，最后必然会到达一个局面：有一个大数x和`C-1`个1。所以，最后只需要说明这个留下来的大数`x`小于`C`。

可以发现，其他颜色肯定都会和最大的颜色匹配，如果在贪心策略中有一个颜色没有和原来最大的颜色匹配的话，那么当前“最大的颜色”必然有两个以上，在这个情况下，`x`最大只能到2。

所以，如果`x`大于2的话，其他颜色都会和原来最大的颜色匹配。而没有一个颜色大于n/2，即不可能所有颜色都与原来最大的颜色匹配后最大的颜色还有剩余。因此，一定能匹配成功。

（有点绕qwq，反正找不出反例就对了）

效率证明，因为每次取出两个数必然要入队列、出队列各两次，所以时间复杂度$\Theta(nlogC)$，不是很优秀qwq。

还有个坑点，注意读入的时候`Ci`就为0的情况。（数量为0还单独挑出来搞个颜色干嘛啊魂淡QwQ）

当然，如果观察到每次入队的珍珠的数量一定不增的话，可以先排序然后开队列达到$\Theta(ClogC+n)$，或者计数排序后开队列达到$\Theta(C+n)$，不过能AC就不优化了qwq。

附AC代码：（全站最慢）

```cpp
#include <queue>
#include <cstdio>
using namespace std;

int main()
{
	int n,c;
	scanf("%d%d",&n,&c);
	priority_queue<pair<int,int> > pq;
	for(int i=1; i<=c; ++i)
	{
		int ci;
		scanf("%d",&ci);
		
		if(ci)
		{
			pq.push(make_pair(ci,i));
		}
	}
	
	while(!pq.empty())
	{
		int an = pq.top().first;
		int ac = pq.top().second;
		pq.pop();
		int bn = pq.top().first;
		int bc = pq.top().second;
		pq.pop();
		
		printf("%d %d\n",ac,bc);
		--an;
		--bn;
		
		if(an)
		{
			pq.push(make_pair(an,ac));
		}
		if(bn)
		{
			pq.push(make_pair(bn,bc));
		}
	}
}
```

---

## 作者：不存在之人 (赞：2)

**Bessie将每种颜色3的珍珠与一种颜色1和2配对。**

**贪心题，将颜色最多的牛先配对。**

**（原以为是DP。。。）**

### 附代码：
```cpp
#include<cstdio>
#include<algorithm>
#define MAXN 100010
using namespace std;
int n,c,l=1,f[MAXN];
struct node1{
	int x,id;
}a[MAXN];
inline int read()
{
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9')
	{
		if(c=='-')w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		date=date*10+c-'0';
		c=getchar();
	}
	return date*w;
}
bool cmp(const node1 &x,const node1 &y)
{
	return x.x>y.x;
}
int main()
{
	n=read();c=read();
	for(int i=1;i<=c;i++)
	{
		a[i].x=read();
		a[i].id=i;
	}
	sort(a+1,a+c+1,cmp);
	for(int i=1;i<=n/2;i++)
	{
		a[l].x--;
		f[i]=a[l].id;
		if(!a[l].x)l++;
	}
	for(int i=1;i<=n/2;i++)
	{
		a[l].x--;
		printf("%d %d\n",f[i],a[l].id);
		if(!a[l].x)l++;
	}
	return 0;
}
```

---

## 作者：Jason12 (赞：1)

## 题目：[传送门](https://www.luogu.com.cn/problem/P2902)

## 思路：
  由于题目保证存在答案，所以对于每颗珍珠一定存在与其相配对的一颗颜色不同的珍珠，所以易得单种颜色的珍珠数量必定小于等于珍珠总数的一半,将珍珠按颜色存入数组中后配对输出即可。（详见代码）

## 代码：

```cpp
#include <bits/stdc++.h>
  using namespace std;
int n,c,a[100005],s[100005],i,j,t;
int main()
{
	scanf("%d%d",&n,&c);//输入珍珠总数 n 和颜色数 c 
	for (i=1;i<=c;i++)
	{
		scanf("%d",&a[i]);//输入每种颜色的珍珠数量 a[i] 
		for (j=1;j<=a[i];j++)
		{
			s[++t]=i;//将 a[i] 颗颜色为 i 的珍珠依次放入数组中 
		}
	}
	for (i=1;i<=n/2;i++)
	{
		printf("%d %d\n",s[i],s[i+n/2]);//对珍珠进行配对并输出 
	}
	return 0;
}
```

这是蒟蒻的第一篇题解~~上一篇被打回了~~，求管理员大大通过!qwq

---

## 作者：Yldar (赞：1)

  题目描述
  给你N个球，c种颜色。以及每个颜色的数量。求一种方案，使得所有的球两两配对且两个球颜色不同。  
  我们考虑怎么配对。首先我们可以想到最大的一堆跟最小的一堆配对，但这种方法有个bug，就是到最后只剩下一种颜色，GG。       
  于是我们考虑另外一种从大到小排序，然后在n/2的位置截一段，因为数据保证有解，所以在n/2前每个数可以跟n/2后的相应数配对。（这一点不详细解释）      
  最后上代码
  ```
#include<bits/stdc++.h>

using namespace std;

inline int read(){
   int w=1,s=0;
   char ch=getchar();
   while(ch<'0'||ch>'9') {if (ch=='-') w=-1;ch=getchar();} 
   while(ch>='0'&&ch<='9')  s=s*10+ch-'0',ch=getchar();
   return s*w;
}

struct node{
    int num,color;
}a[100010];

int cmp(node  a1,node a2){return a1.num>a2.num;}

int ans[100010];

int main(){
    int n=read(),c=read();
    for(int i=1;i<=c;i++) a[i].num=read(),a[i].color=i;
    sort(a+1,a+c+1,cmp);
    int l=0;
    for(int i=1;i<=c;i++)
    for(int j=1;j<=a[i].num;j++) 
    ans[++l]=a[i].color;
   for(int i=1;i<=n/2;i++)
   cout<<ans[i]<<" "<<ans[i+n/2]<<endl;
    return 0;
}
```

---

## 作者：allqpsi (赞：0)

我发现其他人都会用一个数组来记录每个颜色有多少个珍珠，本人认为用优先队列也可以满分……

我们可以在优先队列里面储存每个颜色和每个颜色的珍珠的数量，然后依次找到最多珍珠的两个颜色，两个数量都减一，再放回优先队列里就可以了。
### 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y;
	bool operator<(node l)const{
		return y<l.y;
		//以珍珠的数量排序。
	}
};
long long n,s,m;
node a,b;
priority_queue<node>qi; 
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		qi.push(node{i,s});
	}
	for(int i=1;i<=m/2;i++){
		a=qi.top();
		qi.pop();
		b=qi.top();
		qi.pop();
		//找到最大珍珠数量的颜色。
		cout<<a.x<<' '<<b.x<<endl;
		//把它-1放回优先队列。
		if(a.y>1){
			qi.push(node{a.x,a.y-1}); 
		}
		if(b.y>1){
			qi.push(node{b.x,b.y-1});
		}
	}
}
```


---

## 作者：Sternenlicht (赞：0)

思路：

注意到 $n$ 是偶数，第一反应就是从这里入手。

有 $c$ 种颜色，每种颜色的珍珠有 $x$ 颗，可以将这 $x$ 颗珍珠的颜色编号存入 $color$ 数组中。又每种颜色的珍珠数量都不超过 $\frac{n}{2}$，所以 $color_i$ 和 $color_{i+n/2}$ 一定不相等，让这两种珍珠相匹配即可。

```cpp
#include <bits/stdc++.h>
//封装的快读快写
namespace IO{
	inline LL read(){
	    LL x=0,f=1;char ch=getchar();
	    for (;!isdigit(ch);ch=getchar())if (ch=='-')f=-1;
	    for (;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
	    return x*f;
	}
	inline void write(LL x,char c='\n'){
	    if (x){
	    	if (x<0)x=-x,putchar('-');
	    	char a[30];short l;
	    	for (l=0;x;x/=10)a[l++]=x%10^48;
	    	for (l--;l>=0;l--)putchar(a[l]);
		}
		else putchar('0');putchar(c);
	}
	inline char getc(){
		char ch=getchar();
		while (isspace(ch))ch=getchar();
		return ch;
	}
}
using namespace IO;
using namespace std;

const int N = 1e5+10;
int color[N],n,c,cnt;//如题意，color数组存珍珠编号
int main(){
	n=read(),c=read();
	for (int i=1;i<=c;i++)
		{int x=read();while (x--)color[++cnt]=i;}//存入珍珠编号 
	for (int i=1;i<=n/2;i++)
		write(color[i],' '),write(color[i+n/2]);//输出 
    return 0;
}
```

---

## 作者：_Imaginary_ (赞：0)

这道题毕竟是提高-，并没有那么难。

# 正文

首先，我们来举个例子：（样例）
```cpp
8 3
2
2
4
```

我们有一个比较简单的做法。首先，让我们把这一串珠子进行排序，变成 `33332211`。这样，我们就能进行这样的操作：

Step 0: 建造 $N/2$ 个组合，2行：

|1|2|3|4|
|:-:|:-:|:-:|:-:|
|||||
|| |||

Step 1: 选出个数最多的珠子，堆到第一行：

|1|2|3|4|
|:-:|:-:|:-:|:-:|
|3|3|3|3|
||| | |

Step 2: 仿照前面的操作，把目前最多的珠子放到空间最大的行。第一行空间0，第二行空间4，所以把2号珠子全部放到第二行：

|1|2|3|4|
|:-:|:-:|:-:|:-:|
|3|3|3|3|
|2|2| | |

同理，最后填满：

|1|2|3|4|
|:-:|:-:|:-:|:-:|
|3|3|3|3|
|2|2| 1| 1|

Over。

**但是还有一个小问题。**

看一下这一组：

```
8 3
3
3
2
```

按照前面的操作，我们可以做到这一步：

|1|2|3|4|
|:-:|:-:|:-:|:-:|
|1|1|1||
|2|2|2 | |

接下来把两个 3 放进去就悲剧了。

怎么解决呢？

我们不妨把这两个3先放进去。

|1|2|3|4|
|:-:|:-:|:-:|:-:|
|1|1|1|3|
|2|2|2 | 3|

~~似乎没有想出办法~~

我们发现，把第一行翻转一下，变成 `3 1 1 1` 就不会产生问题了。

如何证明这样永远不会发生问题呢？

可能发生问题的只有最后多出来的k个3。显然 $k\le N/2$，那么最多只有k组里面会出现3。把3均摊放到这几组里面，没有问题。

这样，我们最终构造的数列可能是这种形式：

```
A a a b b c c d d e e e f f f 
g g g g h h h h i i i j j j A
```
简单来说，就是

**第一行从右向左加元素，第二行从左到右加元素，多出来的在两边补空荡**

~~希望能通过~~


---

