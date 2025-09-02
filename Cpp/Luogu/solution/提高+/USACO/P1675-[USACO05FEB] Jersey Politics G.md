# [USACO05FEB] Jersey Politics G

## 题目描述

在 Wisconsin（地名），有 $3 \times k$ 个城市，依次标号为 $1, 2, \cdots, 3 \times k$，每个城市共有 $1000$ 头奶牛。Jersey（人名）在这些城市中各占有 $w _ 1, w _ 2, \cdots, w _ {3 \times k}$（$0 \leq w _ i \leq 1000$）头奶牛。

你需要将这些城市平分为 $3$ 组。显然，此时每组城市中总共有 $1000 \times k$ 头奶牛。

你需要保证，在至少两组城市中，Jersey 占有的奶牛总数**严格大于** $1000 \times k$ 的一半。

求一种可行的分配方案。



## 说明/提示

可能会有多组解，输出任意一组即可。

$1\le k\le 60$。

## 样例 #1

### 输入

```
2
510
500
500
670
400
310```

### 输出

```
1
2
3
6
5
4```

# 题解

## 作者：Jason0211 (赞：4)

~~看到标签里有随机化，乱写了一下直接过了。~~

这里提供一种随机化~~乱搞~~的做法：

首先，将数列从小到大将原序列排序，由于我们只需要使两组数的和尽可能大，根据贪心，我们可以将最小的 $k$ 个分为一组，才能保证其他两组尽可能大（这里想一想就能明白了，无需证明）。

然后，对后面 $2k$ 个数进行随机化排列，然后直接判断是否符合要求，不符合则继续，符合则直接输出。这里，我们可以选择使用 $\operatorname{shuffle}$
函数对原序列进行随机化打乱，实测出解率很高，每个测试点均可跑到 $4$ 毫秒以内。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node
{
	int sum,id;
}a[185];
bool cmp(Node a,Node b)
{
	return a.sum<b.sum;
}
inline int read()
{
	int x = 0, f = 1;
	char ch = 0;
	while (!isdigit(ch)) {ch = getchar(); if (ch == '-') f =-1;}
	while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}

int main()
{
	int k;
	k=read();
	int len=3*k;
	for(int i=1;i<=len;i++)
	{
		a[i].sum=read();
		a[i].id=i;
	}
	sort(a+1,a+len+1,cmp);
	for(int i=1;i<=k;i++)
	{
		printf("%d\n",a[i].id);
	}
	while(true)
	{
		random_shuffle(a+k+2,a+len+1);
		int ans=0,cnt=0,re=500*k;
		for(int i=k+1;i<=2*k;i++)
		{
			ans+=a[i].sum;
			if(ans>re)
			{
				cnt++;
				break;
			}
		}
		ans=0;
		for(int i=2*k+1;i<=len;i++)
		{
			ans+=a[i].sum;
			if(ans>re)
			{
				cnt++;
				break;
			}
		}
		if(cnt==2)
		{
			for(int i=k+1;i<=len;i++)
			{
				printf("%d\n",a[i].id);
			}
			break;
		}
	}
	return 0;
}
```

---

## 作者：1qaz234567pzy (赞：3)

一道随机化好~~水~~题。

### 前置知识：需要会用 `random_shuffle` 函数。



`random_shuffle` 是一个用来随机打乱数组中任意一段的函数，用法如下

```cpp
int a[10000]={1,2,3,4,5,6,7,9,0,10,11,12};
random_shuffle(a+3,a+11);//用法跟sort类似
for(int qwq=0;qwq<=11;qwq++)
{
    cout<<a[qwq]<<" ";
}

```
运行结果为

![](https://cdn.luogu.com.cn/upload/image_hosting/qnzxcqs6.png)

可见 `random_shuffle` 函数随机打乱了 $a$ 数组的后 $9$ 位。



所以我们可以用它来做一些随机化的操作。



------------

知道了这个，那我们怎么用这个做这道题呢？

我们看一下题目，题目要求在至少两组城市中 Jersey 占有的奶牛总数**严格大于** $500 \times k$。

也就是说我们要把最小的一些数放在第一组城市，把大的都留给后两组城市，来让满足题目要求的可能性越大（自己可以想一下为什么）。至于后两组城市之中城市的分配，我们就可以使用 `random_shuffle` 函数了。

我们第一组，第二组，第三组的数都放在同一个数组里，先把最小的数都放进第一组，然后随机打乱第二组和第三组的数（细节见代码），验证是否满足题目要求，满足就输出就行了。

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
    int val;
    int id;
}a[1000];
bool cmp(node a,node b)
{
    return a.val<b.val;
}
int k;
int main()
{	
    cin>>k;
    int tot=3*k;//城市总数
    for(int i=1;i<=tot;i++)
    {
        cin>>a[i].val;
        a[i].id=i;
    }
    //第一组 1到k 第二组k+1到2*k 第三组 2*k+1到3*k
    sort(a+1,a+1+tot,cmp);//预先排序
    int ans=0;
    int cnt=0;
    while(1)
    {
        ans=0;
        cnt=0;
	     for(int qwe=2*k+1;qwe<=3*k;qwe++)//验证第三组城市是否满足题目要求
	     {
	     	ans+=a[qwe].val;
	     	if(ans>500*k)
             {
          cnt++;
          break;
           }
       }
      ans=0;
      for(int qwe=k+1;qwe<=2*k;qwe++)//验证第二组城市是否满足题目要求
      {
            ans+=a[qwe].val;
            if(ans>500*k)
            { 
            cnt++;
            break;
            }
      }
      if(cnt==2)//满足题目要求就不用再随机化了
      {
          break;
      }         
      random_shuffle(a+2+k,a+1+tot);//代码的核心-随机打乱第二组与第三组
    }
    for(int qwe=1;qwe<=3*k;qwe++)//输出
    {
    	cout<<a[qwe].id<<endl;
    }
    return 0;
}
```

没想到速度还蛮快啊（每个点都能跑到 $10$ 毫秒以内）。


---

## 作者：ncwzdlsd (赞：2)

[随机化](https://blog.csdn.net/ncwzdlsd/article/details/133753719)。

考虑贪心，把最小的 $k$ 个分给第一个序列，这样可以尽可能地最大化后两个序列的值。

然后考虑随机化。用 `random_shuffle` 随机打乱序列，判断两个序列是否都满足条件，如果满足直接输出，不满足就继续打乱。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

struct node{int id,val;}a[200];

bool cmp(node a,node b){return a.val<b.val;}

int main()
{
    int k;cin>>k;
    for(int i=1;i<=k*3;i++) cin>>a[i].val,a[i].id=i;
    sort(a+1,a+k*3+1,cmp);
    for(int i=1;i<=k;i++) cout<<a[i].id<<endl;
    while(1)
    {
        random_shuffle(a+k+2,a+k*3+1);
        int cnt=0,sum1=0,sum2=0;
        for(int i=k+1;i<=2*k;i++)
        {
            sum1+=a[i].val;
            if(sum1>500*k) {cnt++;break;}
        }
        for(int i=k*2+1;i<=k*3;i++)
        {
            sum2+=a[i].val;
            if(sum2>500*k) {cnt++;break;}
        }
        if(cnt==2) break;
    }
    for(int i=k+1;i<=k*3;i++) cout<<a[i].id<<endl;
    return 0;
}
```

---

## 作者：SDLTF_凌亭风 (赞：2)

## 解题思路

均分三组，至少要两组，那我就**只去满足两组**。

又要满足总和尽可能大，那我肯定**先把小的给排除在外**。

如何将小的排除在外？一个显然的想法就是先排序，再把最小的 $k$ 个排除在外。

剩下的两个序列，显然序列元素总和一大一小。

那我难道要每次在总和大的里面拿出一个最大的，和总和小的里面最小的交换吗？那可能就总和大的就变成总和小的，然后你再一次进行这种交换，不断重复下去，好麻烦。

不如直接随机交换，反正他只要求满足条件的一组解。

使用随机化算法，**主要看脸**。

## 代码

给出关键的交换代码：

```cpp
// 随机交换，启动！
while(sum2 <= k * 500 || sum3 <= k * 500) {
	int r1 = rnd() % k + 1, r2 = rnd() % k + 1;
	sum2 -= sec2[r1].first, sum3 -= sec3[r2].first;
	swap(sec2[r1], sec3[r2]);
	sum2 += sec2[r1].first, sum3 += sec3[r2].first;
}
```

---

## 作者：OIer_ACMer (赞：2)

~~唉，我竟然不会随机化！！！！~~

------------
## 大致思路：
这道题，不说多的主要是~~自己快被自己的垃圾实力搞崩溃了~~随机化比较简单，首先，我们要知道一个十分重要的函数 `random_shuffle`。它是**随机化的核**心，就是能够实现**随意打乱顺序**，这是随机化的精髓~~说白了就是不会高级算法~~。

首先，我们开一个结构体 $node$ 和数组 $cities$，来存储各个城市的坐标与那个人在这座城市拥有的牛的数量，接着，我们可以知道：如果将数组排序，那么前 $k$ 个数的 $sum$ **累加和一定是小于要求的**，因为我们可以知道所有城市总共有 $1000$ 头牛，要求是要**严格大于** $1000 \times k$ **的一半**的，但是要**分成** $3$ **组**，且那个人在一座城市拥有的奶牛一定会小于等于 $1000$，再怎么有牛也不能比 $1000$ 大，所以，前一组（就是全是最小数的那一组）肯定小于等于 $1000$。

其次，我们在做随机化的时候，建议**分开算**，这样可以避免许多例如 $i$ 超过了 $k \times 3$ 的范围的问题，并用 $ans$ 数组计算符合要求的组数。

最终，如果 $ans > 2$，则循环输出城市坐标（用结构体的好处就体现在这里了）。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int N = 182;
struct node
{
    int a, dz;
} cities[N];
bool cmp(node a, node b)
{
    return a.a < b.a;
}
int n;
int main()
{
    n = read();
    n *= 3;
    int u = n / 3;
    for (int i = 1; i <= n; i++)
    {
        cities[i].a = read();
        cities[i].dz = i;
    }
    sort(cities + 1, cities + n + 1, cmp);
    int summ = 0;
    int p = 0;
    while (1)
    {
        // int op[4][66];
        random_shuffle(cities + 2 + u, cities + n + 1);
        int sum = 0, ans = 0, l = 1, k = 0;
        for (int i = u + 1; i <= n; i++)
        {
            if (i == u * 2 + 1)
            {
                if (sum > (500 * u))
                {
                    ans++;
                }
                sum = 0;
            }
            sum += cities[i].a;
            if (i == n)
            {
                if (sum > (500 * u))
                {
                    ans++;
                }
            }
        }
        if (ans >= 2)
        {
            for (int i = 1; i <= n; i++)
            {
                cout << cities[i].dz << endl;
            }
            return 0;
        }
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/121094517)

---

## 作者：tmpliyijiang (赞：1)

## 前置知识: `random_shuffle` 函数。
`random_shuffle` ： 用来随机打乱数组指定部分的函数。

格式如下，与 sort 函数相似：
```cpp
int a[11]={0,1,2,3,4,5,6,7,8,9,10};
random_shuffle(a+1,a+10);//打乱a数组2~11位

```
首先观察题目，容易发现：所有城市 Jersey 占有的奶牛总数不变，为了使其中 $2k$ 个城市尽量多，另外 $k$ 个城市应尽量少。

所以我们可以先新建一个数组记录每个城市奶牛数的原值以便输出时查询位置，再把输入数据按降序排序，随机排序前 $2k$ 个城市直到满足要求。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[190],b[190],k;//a数组用来找可行解，b数组记录原值
bool choseN[190];//防止相同数据导致查找的下标相同
inline bool cmp(int a,int b){
	return a>b;
}
inline bool isoK(){//用来检查是否符合要求
	int ans1=0,ans2=0;
	for(register int i=1;i<=k;i++){
		ans1+=a[i];//前k个城市的和
	}
	if(ans1<=500*k)return 0;
	for(register int i=k+1;i<=2*k;i++){
		ans2+=a[i];//第k+1~2k个城市的和
	}
	if(ans2<=500*k)return 0;//不合法
	return 1;
}
inline int FinD(int x){//用来查找
	for(register int i=1;i<=3*k;i++){
		if(b[i]==x&&!choseN[i]){
			choseN[i]=1;//标记
			return i;
		}
	}
}
int main(){
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>k;
	for(register int i=1;i<=3*k;i++){
		cin>>a[i];b[i]=a[i];
	}
	sort(a+1,a+3*k+1,cmp);//排序
	while(!isoK())random_shuffle(a+1,a+1+2*k);//找解
	for(register int i=1;i<=3*k;i++){
		cout<<FinD(a[i])<<' ';
	}//输出
	cout<<endl;
	return 0;
}

```

---

## 作者：一只小兔子 (赞：1)

~~哦不我讨厌随机化~~

题目大意是把给定 $3k$ 个一千以内的自然数平分为三份，使得至少两份的和大于 $500k$。

一个非常容易想的贪心是首先排个序，把最少的 $k$ 个分给第三组，正确性易得。（证明有点繁琐，但非常好想）

剩下的，就是给定 $2k$ 个数平分，使得这两份的和大于 $500k$。

### 随机化

因为要选 $k$ 个数进第一组，不妨先选择最多的 $k$ 个数，剩下中间 $k$ 个数进第二组。每次随机在第一组和第二组中各选择一个数交换，直到这两组的和均满足要求，并输出。

复杂度非常玄学，但看起来应该是非常快，而且代码没有什么太大的难点，强烈建议这种方法。（毕竟标签写着呢）

当然，弊端就是无法判断无解情况，毕竟题目没有说一定存在解。（但测试数据保证有解，啊？）

### 动态规划

动态规划数组 $f_{i,j}$ 记录选择 $i$ 个数的和为 $j$ 的方案。因为只有 $2k$ 个数，状态压成两个长整型即可。

想到这步，那么转移就很好想了。$f_{i,j}$ 用集合表示，加入的数是 $x$。

$$f_{i+1,j+x}=f_{i,j}\cup\{x\}$$

对每个数跑一遍转移，再加上只从存在方案的状态转移这个剪枝，就可以了。答案就是 $f_{k,500k+r}$，遍历一遍找方案然后输出。

因为随机因素变少了，复杂度很好算，是 $O(1000k^3\epsilon)$。$O(1000k^3)$ 是朴素动态规划的复杂度，$\epsilon<1$ 是剪枝的效果，玄学情况下可过。

不仅如此，如果没有找到合法方案，可以直接判定无解。代价就是慢，是最优解里最慢的。

### 参考代码

~~方法是动态规划，随机化的我不想打。~~

```cpp
#include<iostream>//P1675 [USACO05FEB] Jersey Politics G
#include<algorithm>
struct city{int val,pos;}p[180];
bool cmp(city a,city b){return a.val>b.val;}
struct state{
	long long fpart,spart;
	bool valid(){return fpart>0||spart>0;}
	void flip(int bit,bool iss){if(iss)spart^=(1<<bit);else fpart^=(1<<bit);}
	void put(){std::cout<<fpart<<"+"<<spart<<" ";}
	int check_bit(){
		int tot=0;long long tmp=fpart;while(tmp)tot+=(tmp&1),tmp>>=1;
		tmp=spart;while(tmp)tot+=(tmp&1),tmp>>=1;return tot-1;
	}
}dp[61][60001];
int main(){freopen("testdata.in","r",stdin);
	int k,target=0,success=-1;std::cin>>k;dp[0][0].flip(60,0);
	for(int i=0;i<3*k;++i)std::cin>>p[i].val,p[i].pos=i+1;
	std::sort(p,p+3*k,cmp);for(int i=0;i<2*k;++i)target+=p[i].val-500;
	for(int i=0;i<2*k;++i)for(int r=k-1;~r;--r)for(int h=0;h<=r*1000;++h)
		if(dp[r][h].valid())dp[r+1][h+p[i].val]=dp[r][h],dp[r+1][h+p[i].val].flip(i%k,i>=k);
	for(int aim=1;aim<target;++aim)if(dp[k][k*500+aim].valid()){success=k*500+aim;break;}
//	for(int layer=1;layer<=k;++layer){
//		for(int off=layer*500-10;off<=layer*500+10;++off)
//		dp[layer][off].put();std::cout<<std::endl;
//	}
	if(success==-1){std::cout<<"impossible";return 0;}
	for(int i=0;i<k;++i)if(dp[k][success].fpart&(1<<i))
	std::cout<<p[i].pos<<std::endl,p[i].pos*=-1;
	for(int i=0;i<k;++i)if(dp[k][success].spart&(1<<i))
	std::cout<<p[i+k].pos<<std::endl,p[i+k].pos*=-1;
	for(int i=0;i<2*k;++i)if(p[i].pos>0)std::cout<<p[i].pos<<std::endl;
	for(int i=0;i<k;++i)std::cout<<p[i+2*k].pos<<std::endl;
}
```

---

## 作者：1234567890sjx (赞：0)

随机化。

首先考虑将数组排序，然后按照大小顺序把所有的数分成三组。第一组肯定不满足，第三组肯定满足。但是不一定能够保证第二组满足。

所以随机化，每一次随机交换第一组和第二组的一个元素，判断是否合法即可。很[抽象](/user/761125)。

---

## 作者：Eltaos_xingyu (赞：0)

## 题目描述

将所有城市平分为 $3$ 组，使得有两组城市中的特殊奶牛占每组城市总奶牛的多数（**大于**一半）。

## 实现

~~看到标签里有一个随机化的标签于是就真的随机做了。~~

本篇题解用函数 `random_shuffle(a+l,a+r)` 来对 $a$ 数组 $[l,r)$ 区间进行随机打乱。

这道题检查是否合法很简单，直接暴力求和比较一下就行了。

好！直接随机打乱所有的城市顺序再检查是否合法！

......

超时了......

所以有什么优化的地方吗？

考虑稍微贪心一下；先排序一下，把小的都分在前面那一组，只需要随机打乱长度为 $2k$ 的剩余序列即可，这样保证了较大的数一定在我们想要的那两组内。这样就能 AC 了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct test{
	int id;
	int v;
}w[201];
long long sum=0;
bool cmp(test a,test b){
	return a.v<b.v;
}
int k;
bool check(){
	long long u=0;
	for(int i=k+1;i<=2*k;i++){
		u+=w[i].v;
	}
	if(u<=500*k||sum-u<=500*k)return 1;
	return 0;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	cin>>k;
	for(int i=1;i<=k*3;i++)cin>>w[i].v,w[i].id=i;
	sort(w+1,w+k*3+1,cmp);
	for(int i=k+1;i<=3*k;i++)sum+=w[i].v;
	while(check())random_shuffle(w+k+1,w+3*k+1);
	for(int i=1;i<=3*k;i++){
		cout<<w[i].id<<endl;
	}
	return 0;
}
```


---

## 作者：xiazha (赞：0)

### 思路

随机化好题。

首先，考虑贪心。由于只需其中两组加和大于 $500\times k$ 即可满足条件，所以我们只需要对序列 $w$ 进行降序排序，尽可能的使前两组最大。

然后，直接抛弃第三个。由于现在第二组有可能没超过 $500\times k$，所以需要用过交换一二两组的数使得一二两组尽量平均，这样才可以使一二两组都大于 $500\times k$。

最后，你会发现没有什么太好的算法能通过交换使一二两组都大于 $500\times k$。于是，随机化来了。随机选取一二两组中的数各一个，将他们交换。直到两组都大于 $500\times k$ 为止。

可以这样做的依据很简单：

1. 数据保证有解。

2. $k \le60$

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int k,n;
struct node
{
	int sum,id;
}a[202];
bool cmp(node a,node b)
{
	return a.sum>b.sum;
}
signed main()
{
	k=read();n=k*500;
	for(int i=0;i<k*3;i++) a[i].sum=read(),a[i].id=i;
	sort(a,a+k*3,cmp);
	int s1=0,s2=0;
	for(int i=0;i<k;i++) s1+=a[i].sum,s2+=a[i+k].sum;
	srand(time(NULL));
	while(!(s1>n&&s2>n))
	{
		int lao=rand()%k;
		int yuan=rand()%k;
		s1=s1-a[lao].sum+a[k+yuan].sum;
		s2=s2-a[k+yuan].sum+a[lao].sum;
		int t1=a[lao].sum,t2=a[lao].id;
		a[lao].sum=a[k+yuan].sum;
		a[lao].id=a[k+yuan].id;
		a[k+yuan].sum=t1;
		a[k+yuan].id=t2;		
	}
	for(int i=0;i<3*k;i++) printf("%d\n",a[i].id+1);
    return 0;
}
```


---

