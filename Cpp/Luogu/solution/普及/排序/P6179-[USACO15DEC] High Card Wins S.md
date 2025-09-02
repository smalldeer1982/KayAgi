# [USACO15DEC] High Card Wins S

## 题目描述

Bessie 是纸牌游戏的忠实粉丝。对她而言，其他奶牛都算不上对手。更糟糕的是，其他奶牛在打牌时的行为都是完全能预测的。尽管如此，Bessie 知道取胜仍然是个挑战。

Bessie 和她的朋友 Elsie 正在玩一种纸牌游戏。这个游戏里要用到一副 $2N$ 张牌的套牌，编号从 $1$ 到 $2N$。Bessie 和 Elsie 每个人各分得 $N$ 张卡片。接下来进行 $N$ 轮比赛，Bessie 和 Elsie 每轮各出一张牌。每一轮谁的牌编号更大，谁就赢得了本轮的胜利。

Bessie 已经预测了 Elsie 的出牌顺序，请帮助 Bessie 算出她最多能赢多少轮。

## 说明/提示

Bessie 手中拿着 $2,3,5$ 三张牌。

它第一轮出 $2$，第二轮出 $3$，第三轮出 $5$，从而赢得一，三两轮。可以证明不存在更优的方案。

## 样例 #1

### 输入

```
3
1
6
4```

### 输出

```
2```

# 题解

## 作者：杨誉yy (赞：5)

Solution1: 36pts  

第一眼过去，一看就是带有简单决策的模拟。

那么，手动模拟怎么做呢？对于样例给出的输入，先将其排序，得到E和B的手牌：  
E 1  4  6  
B 2  3  5  

从B的最小手牌2开始，对E的手牌由大到小进行遍历，若遇到比该牌小的牌，$ans++$，同时对这张E的手牌进行标记，不再进行比较。  

那么，在循环到手牌2时，发现E的第一张手牌1比2小，于是$v[e[1]]=true$且$ans++$。  

接着我们发现，B的第二张手牌已经是全场最小的牌。于是与当前E手中最大的牌极限一换一，$v[e[3]]=true$。

显然，经过$n$次循环，问题就能全部解决。可这种算法的时间在$O(n^2)$左右徘徊，很显然是过不了的。

暴力打下去，拿了36分，代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int ans,i,j,n,m,tmp,tail,cnt;
int a[100010],b[100010];
bool v[100010];
int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
		v[b[i]]=true;
	}
	sort(b+1,b+n+1);
	for(i=1;i<=2*n;i++)
	{
		if(!v[i])
		{
			cnt++;
			a[cnt]=i;
		}
		if(cnt==n)
		{
			break;
		}
	}
	tail=n+1;
	for(i=1;i<=n;i++)
	{
		for(j=n;j>=1;j--)
		{
			if(b[j]!=-1&&a[i]>b[j])
			{
				ans++;
				b[j]=-1;
				break;
			}
		}
		if(tmp==ans)
		{
			do
			{
				tail--;
			}
			while(b[tail]==-1);
			b[tail]=-1;
			
		}
		tmp=ans;
	}
	printf("%d",ans);
}
```

Solution2: 100pts

暴力只拿了36分，在模拟方式上也没有太大的改进空间。这时我们发现在实现模拟的过程中有很多无用的操作：对最小数的“极限一换一”处理并没有在决策上起到任何帮助；对E手中的牌的标记没有记录下来的必要。即对于B的一张牌，只要知道它有赢面即可，不用精确到每一张牌的决策。

经过简化，我们可以将操作流程理解为：对B手中的所有牌进行遍历，找出所有在E手中比他小且未曾被使用过的牌，$cnt++$。若当前$cnt>0$，则$cnt--$并将$ans++$。

显然，若仍继续使用原先的储存结构，实现过程将会很难办。我们可以很容易地想到用桶来储存。

输入时用bool型的$v[]$来记录E的手牌。接着进行$2n$次循环：对于每一次循环，若$v[i]==true$，则$cnt++$，表示对于当前的牌，E手中共有$cnt$张手牌没被使用且比当前的牌小。

若$!v[i]$，表示i为B的手牌，则对$cnt$进行判断；若$cnt>0$，则表示该牌有赢面，于是$ans++$,E手中可取用的手牌少了一张，$cnt--$。

因为使用桶的方式进行储存，所以在进行遍历时数列本身是有序的，在记录$cnt$的值时非常便捷。可以看出，该算法的时间接近于$O(n)$，完全可以通过本题。

AC代码如下：
```cpp
#include<cstdio>
int ans,i,j,n,m,tmp,tail,cnt,b;
bool v[100010];
int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&b);
		v[b]=true;
	}
	for(i=1;i<=2*n;i++)
	{
		if(!v[i])
		{
			if(cnt>0)
			{
				cnt--;
				ans++;
			}
		}
		else
		{
			cnt++;
		}
	}
	printf("%d",ans);
}
```

---

## 作者：study_nerd (赞：4)

这道题可以用二分来解。

每次二分贝西赢的场数，然后另一头牛的牌从第mid大开始，往下减，每次与贝西当前最大的牌比较，如果牌用完了就可以赢这么多场，否则如果出现贝西的牌更小就不行，最后输出。

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[50005],b[50005],tot=0;
bool s[100005];
bool cheak(int x)
{
	int tt=n;
	for(int i=x;i>0;--i)
	{
		if(b[tt]<a[i])return 0;
		tt--;
	}
	return 1;
}
int main(){
	//freopen("highcard.in","r",stdin);
	//freopen("highcard.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		s[a[i]]=true;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=2*n;++i)if(!s[i])b[++tot]=i;
	int l=0,r=n+1;
	while(l+1<r)
	{
		int mid=l+r>>1;
		if(cheak(mid))l=mid;
		else r=mid;
	}
	cout<<l;
	return 0;
}
```


---

## 作者：tribool4_in (赞：2)

这题类似于 田忌赛马 吧。

这题是贪心，但有多种贪心法（然而我懒得写太多了）。

首先把两人（牛）的牌存两个数组（a 和 b）并排序（显然），再从小到大扫一遍。维护三个指针 ```i=1 j=1 head=n```，每一次将 ```a[i]``` 和 ```b[j]``` 比较一下，如果能胜，则直接打出去，即 ```i++, j++```，否则就用这张牌耗掉对方最大的牌，即 ```head--, j++```。最后输出赢的次数即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n;
int a[N], b[N];
bool t[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		t[a[i]] = 1;
	}
	int tmp = 0;
	for (int i = 1; i <= 2 * n; i++) {
		if (!t[i]) {
			b[++tmp] = i;
		}
	}
	sort(a + 1, a + n + 1);
	int i = 1, j = 1, head = n, ans = 0;
	while ((j <= n) || (i <= head)) {
		if (a[i] < b[j]) {
			ans++;
			i++;
			j++;
		} else {
			j++;
			head--;
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：45dino (赞：2)

一个比较简单的题目。

容易想到贪心，当 Elsie 出一张点数为 $a$ 的牌时，Bessie 应该出一张离 $a$ 尽可能接近但大于 $a$ 的。

可以用二分或 lowerbound 对于每一张牌分别求解，复杂度 $O(logn)$ 。

或者不用二分，先将 $a_i$ 排序，显然对于 $(i<j)$ ，$a_i$ 时 Bessie 出的牌的点数小于 $a_j$ 。复杂度还是 $O(logn)$ 。

注意每一张牌只能用一次。

喜闻乐见的代码：
```
#include<bits/stdc++.h>
using namespace std;
int ans,cnt,n,b[50001],e[50001],e_a[100001];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&e[i]);
		e_a[e[i]]=1;
	}
	sort(e+1,e+1+n);	
	for(int i=1;i<=n*2;i++)
		if(!e_a[i])
			b[++cnt]=i;
	cnt=0;
	for(int i=1;i<=n;i++)
	{
		while(b[cnt]<e[i]&&cnt<n)
			cnt++;
		if(b[cnt]<e[i])
			break;
		ans++;
		cnt++;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：james1BadCreeper (赞：2)

数据范围给出的意思是要求 $\mathcal{O}(n\log n)$ 算法，但实际上可以 $\mathcal{O}(n)$ 	求解。

很容易想到贪心，可是怎么贪呢？

因为 Bessie 已经预测了 Elsie 的出牌顺序，就是说已经预测到了 Elsie 要出的牌。又因为数字越大牌的威力越大，所以可以考虑从大往小开始扫（否则就大材小用了）。

用 $A$ 来存哪些牌是 Bessie 的，哪些牌是 Elsie 的，从右（大）往左（小）开始扫 $A$，如果这是 Bessie 的牌，那么说明 Bessie 就多了一次杀 Elsie 的机会（因为是从右往左扫所以必定这张牌战无不胜），如果是 Elsie 的牌，就看有没有杀的机会，否则就完蛋。

可模拟出：

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

int n,cnt=0,ans=0;
int a[5005];

inline int read(void)
{
    register int x=0,c=getchar();
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x;
}

int main(void)
{
    n=read();
    for(register int i=1;i<=n;i++)  
        a[read()]=1;
    for(register int i=(n<<1);i>=1;i--)
    {
        if(!a[i]) cnt++;
        else if(cnt>0) cnt--,ans++;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Pkixzx (赞：1)

题目意思还是比较简单的，看到这道题目的第一个思路肯定是用**贪心**来解决的。

我们先求出Bessie的牌，再对两人的牌进行排序，接着，循环Elsie的牌，从最小的开始，然后用Bessie的牌和Elsie的牌作比较，如果Elsie的牌大于Bessie的牌，则Bessie的牌加一，如果Elsie的牌小于Bessie的牌，则两人的牌都加1，并且最后输出的数加1。

贴一下代码：
```
#include <bits/stdc++.h>
using namespace std; 
int hyf[100010],wtf[100010],wjt[100010];
int main() 
{
    long long n,n1=1,m1=1,m,j,k,i,t=1,x,y,t1=0;
    long long sum=0,num=0;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>hyf[i];
        wtf[hyf[i]]++;//设置一个桶，如果是Elsie的牌就加1
    }
    for(i=1;i<=2*n;i++)
    {
        if(wtf[i]==0)//因为如果是1就说明是Elsie的牌，反过来如果是0就是Bessie的牌
        {
            wjt[t]=i;
            t++;
        }
    }
    sort(hyf+1,hyf+1+n);//对Elsie的牌进行排序
    sort(wjt+1,wjt+1+n);//对Bessie的牌进行排序
    for(i=1;i<=n;i++)
    {
        if(hyf[m1]<wjt[n1])//如果这次牌Bessie能取胜
        {
            t1++;//能赢的次数加1
            m1++;//Elsie的牌加1
        }
        n1++;不管能还是不能，最后Bessie的牌都要加1
    }
    cout<<t1;//输出
    return 0;
}
```


---

## 作者：祖国的花梗 (赞：0)

[题目](https://www.luogu.com.cn/problem/P6179)

题目大意：一共有 **2N** 张牌，编号是 **1~2N** ，已给出 Elsie 手中的牌以及出牌顺序，双方出的牌编号大的获胜，问你 Bessie 怎样出牌才能使自己赢的次数最多，最多是多少？

思路：这其实是一道非常简单的贪心 ~~斗地主带师~~ 
显然，要想自己能够赢更多局，那么肯定是用当前你手牌中第一个比对方出牌编号大的牌来顶，这样才是最优的。
而且如果对面有牌比你所有的牌都大，那么你就没有必要用你最大的牌去顶，而是用一张小的去顶，虽然横竖都是死，但是你可以用大的牌去顶对方其他小的牌，这样可以赢更多。

**详细请看代码：**


```c
#include<bits/stdc++.h>
using namespace std;
int n,m,tnt=0,ans=0;
int a[50005],b[50005];
bool f[100005];

int main()
{
	scanf("%d",&n); m=n*2;
   for(register int i=1;i<=n;i++)
    scanf("%d",&a[i]),f[a[i]]=true;//标记对方的牌，剩下的牌就是自己的
   for(register int i=1;i<=m;i++)
    if(f[i]==false) tnt++,b[tnt]=i;//统计出自己的牌；
   sort(a+1,a+n+1); sort(b+1,b+n+1);//从小到大排序，该输的总得输，还不如多赢点
   int i=1,j=1;
   while(i<=n&&j<=n)
    if(a[j]<b[i])//可以顶就顶
    {
    	i++; j++;//
	ans++;
    }
    else i++;//打不过就往后找比当前大的牌去顶对面
    printf("%d\n",ans);//输出答案
    return 0;
}
```

这还是道[双倍经验](https://www.luogu.com.cn/problem/P1650)的题
 ┏(＾0＾)┛

---

## 作者：E_D_ZYZE (赞：0)

题解区大多是二分什么的做法，我来发一篇贪心+堆优化的题解。

大体思路就是从大到小枚举 Bessie 的牌，选择 Elsie 的牌中小于这张牌且最大的一张牌作比较（Bessie 胜），这样时间复杂度为 $O(N^2)$ 。容易想到，在查找 Elsie 的符合要求的牌时可以使用大根堆优化到 $O(N\log N)$（具体做法看代码）。

---

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 5;

int n;
bool el[ N << 1 ]; //标记 Elsie 的卡牌

priority_queue< int > Q; //STL大根堆

int main()
{
	scanf( "%d" , & n );
	for( int i = 1 , x ; i <= n ; i ++ )
	{
		scanf( "%d" , & x );
		Q.push( x ) , el[ x ] = true;
	}
	
	int cnt = 0; //储存答案
	for( int i = n << 1 ; i >= 1 ; i -- )
		if( ! el[ i ] )
		{
			while( ! Q.empty() && Q.top() > i ) //查找
				Q.pop();
			if( ! Q.empty() )
				Q.pop() , cnt ++;
		}
	
	printf( "%d" , cnt );
	return 0;
}
```


---

## 作者：MC_Launcher (赞：0)

## 此题算法为排序+贪心（尽管我没有排序）

------

首先读懂题意

>有$2n$个数，互不重复，一半是$B$的，一半是$E$的，每次$B$与$E$都出一个数，数大者胜，$B$后手出牌（可以这么理解），那么$B$最多赢几盘？

### 大家应该第一次想到的是暴力吧

先比较，将$B$的每个数二分查找在$E$中刚好比某一个数大的一个，用这两个抵消，剩下小的就是不能取胜的。

那么二分查找为$O(logn)$，一共$n$个数，总复杂度$O(nlogn)$，虽然对于本题数据过得去，但是代码实现有些复杂。

还有什么办法呢？

### 排序+比较

我们可以将$B$与$E$的牌都排序，然后从第一张开始，逐个比较，如果$B_i>E_j$，那么就可以将$ans$加一，否则一直将$B$数组向后查找元素直到出现$B_i>E_j$。

那么为什么正确呢？

假设有两个有序上升数列$B$，$E$，且这两个数列没有交集，数列中也不存在两个相同的数字。

假设有情况刚好$B_i>E_j$，设此时不是最优，那么设$B_{i-n}$或$B_{i+n}$与$E_j$配对可以更优，如果用$B_{i-n}$，那么根据条件，比$E_j$小，比原有可获得分数少$1$分，与原有假设不符；若选用$B_{i+n}$，那么$E_{j+n}$中可能存在比$B_i$大而比$B_{i+n}$小的数，此时也会使可获得分数减少，与假设不符。

所以刚刚的算法即可求最优解

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
bool b[100010],e[100010];//记录B，E所有的数字
int main()
{
	int n,a;
	cin>>n;
	memset(b,1,sizeof(b));//一开始B有全部数字
	for(int i=0;i<n;i++)
	{
		cin>>a;
		e[a]=true;//E有了这个数字
		b[a]=false;//E有的数字B就没有了
	}
	int b_[100010],e_[100010];//用来存数字的数组
	int now=1,now2=1;
	for(int i=1;i<=n*2;i++)//转化数字+排序一起
	{
		if(b[i])b_[now++]=i;
		if(e[i])e_[now2++]=i;//是true就代表有这个数
	}
	int ans=0,bnow=1,enow=1;
	for(int i=1;i<=n;i++)
	{
		if(b_[bnow]>e_[enow])//如刚刚算法所描述
		{
			ans++;
			bnow++;
			enow++;
		}
		else
		{
			bnow++;
		}
	}
	cout<<ans;//输出
	return 0;
}
```

#### 题解仅提供思路，代码请自己编写。

---

## 作者：羚羊WANG (赞：0)

显然，这就是一个田忌赛马

根据输入，我们可以把$Bessie$和$Elsie$的牌都求出来

显然，出牌的顺序根本没有作用，我们可以把牌排序

如果当前张比对手的当前张要大，可以直接用当前张去跟对方最大的抵消，然后到最后一张就行了

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n,m;
int ans;
int sum;
int b[2*50010];
int g[2*50010];
int h[2*50010];
signed main(){
	n=read();
	for(register int i=1;i<=n;++i)
		{
			g[i]=read();
			h[g[i]]=1;
		}
	sort(g+1,g+n+1);
	for(register int i=1;i<=n*2;++i)
		if(!h[i])
			{
				sum++;
				b[sum]=i;
			}
	sum=0;
	for(register int i=1;i<=n;++i)
		{
			while(b[sum]<g[i] && sum<n)
				sum++;
			if(b[sum]<g[i])
				break;
			sum++;
			ans++;
		}
	write(ans);
	return 0;
}

```


---

## 作者：Zenith_Yeh (赞：0)

~~这其实就是一个田忌赛马。。。~~

看到这道题，我们可以想到一个很明显的贪心思路。

将两人的牌都排序后，比较每一张牌，如果大于它就直接出，否则就将这张牌与对方最大的牌相抵掉即可。

**上菜:**
```cpp
#include<bits/stdc++.h>
inline int read()
{	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c))f|=(c=='-'),c=getchar();
	while(isdigit(c))x=x*10+(c&15),c=getchar();
	return f?-x:x;
}
using namespace std;
int n,b[50005],e[50005],head_b=1,head_e=1,tail_b,tail_e,ans;
bool bj[50005*2];
int main()
{	n=read();
	for(register int i=1;i<=n;++i)
	{	int x=read();
		bj[x]=1;
		e[++tail_e]=x;
	}
	for(register int i=1;i<=2*n;++i)
		if(!bj[i])b[++tail_b]=i;
	sort(e+head_e,e+tail_e+1);
	sort(b+head_b,b+tail_b+1);
	for(register int i=1;i<=n;++i)
	{	if(b[head_b]>=e[head_e])
		{	ans++;
			head_b++,head_e++;
		}
		else
		{	head_b++;
			tail_e--;
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：MuYC (赞：0)

#### 前言

看到没有人用 $set$ ，就来发 ~~水~~ 一发 题解。

$set$ + 贪心就可以过掉本题。

#### 思路

首先考虑如何贪心。

~~类似于田忌赛马~~

无论怎么样，我们总是希望能够用**恰好**大于当前的敌方的牌。

倘若无法满足有一张大于敌方当前牌的牌，那么就直接用最小的牌去“抵消”掉敌方的这一张牌即可（下等马对上等马？）。

然后我们发现找**恰好**大于当前牌的牌的话就可以在一个有序数组中二分,upper_bound()它很香啊！然后发现要支持删除一些元素，想到用 $set$ 维护一下就可以了。

**注意：** $set$ 的 begin() 以及 upperbound() 出来的东西都是迭代器，记得加 "*" 号哦，不然编译报错一大堆！

贴上代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
int A[50005],n,book[100005],tail = 0,Ans = 0;
set <int> s;

int main()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i ++)cin >> A[i],book[A[i]] = 1;
    for(int i = 1 ; i <= 2 * n ; i ++)
        if(book[i] == 0) s.insert(i);
    for(int i = 1 ; i <= n ; i ++)
    {
        set<int>::iterator it;
        it = s.upper_bound(A[i]);
        if(*it > A[i])s.erase(*it),Ans ++;
        else s.erase(*s.begin());
    }
    cout << Ans;
    return 0;
}
```

---

## 作者：Masna_Kimoyo (赞：0)

# （居然没人写二分吗）

这是我们今天的考试题

看到楼下没人写二分，来一发（~~其实是贪心+二分~~）

# 贴

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e4+5;
int tot=0,n,l,r,mid;
int a[N],b[N];
bool flag[N*2];
inline int read()
{
	int x=0;
	bool w=0;
	char c=getchar();
	while(!isdigit(c))
		w|=c=='-',c=getchar();
	while(isdigit(c))
		x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return w?-x:x;
}
inline bool check(int x)
{
	int k=n;
	for(register int i=x;i>0;--i)
		if(b[k--]<a[i])
			return 0;
	return 1;
}
int main()
{
	n=read();
	for(register int i=1;i<=n;++i)
		a[i]=read(),flag[a[i]]=1;
	sort(a+1,a+n+1);
	for(register int i=1;i<=2*n;++i)
		if(!flag[i])
			b[++tot]=i;
	l=1,r=n;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid))
			l=mid+1;
		else	r=mid-1;
	}
	cout<<l-1;
	return 0;
}
```
### 望管理通过

---

## 作者：Zirnc (赞：0)

[ChungZH's blog](https://chungzh.cn) · [ChungZH's portfolio](https://chungzh.cc)

------

~~比楼上大佬的方法麻烦一点~~

首先输入出牌顺序，然后排序一遍。（数组 $a$）

用一个 `flag` 数组记录一下哪些牌**不**在 Elsie 手中（$a$ 中的数是 Elsie 的），也就是属于 Bessie 的牌。

把属于 Bessie 的牌计入另一个数组 $b$ 中（有序）。

然后循环一遍，如果 $b_i > a_{cur}$，那么 $cur++$。

由于 $cur$ 最开始就是 $1$（因为数组的下标都从 $1$ 开始），最后输出 $cur-1$ ，也就是 $b$ 数组中 大于 $a$ 数组其中一个数 的数 的数量即可。（~~有点绕口~~


```cpp
#include <algorithm>
#include <iostream>
using namespace std;
bool flag[100004];
int main() {
  int n;
  cin >> n;

  int a[n + 3];
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    flag[a[i]] = 1;
  }

  int b[n + 3], bidx = 1;
  for (int i = 1; i <= 2 * n; i++)
    if (!flag[i]) b[bidx++] = i;

  sort(a + 1, a + n + 1);

  int cur = 1;
  for (int i = 1; i <= n; i++) {
    if (b[i] > a[cur]) {
      cur++;
    }
  }

  cout << cur - 1 << endl;
  return 0;
}

```

---

