# Minimize the Permutation

## 题目描述

给你一个长度为 $n$ 排列，你需要经过至多 $n-1$ 次的交换，使得排列的字典序尽量小。

这里要注意：交换仅能交换相邻的两数，且每个位置只能交换一次。

位置的定义如下：

交换 $a_1,a_2$ 两数称为在位置 $1$ 上的交换，交换 $a_2,a_3$ 两数称为在位置 $2$ 上的交换，......，交换 $a_{n-1},a_{n}$ 两数称为在位置 $n-1$ 上的交换。

## 样例 #1

### 输入

```
4
5
5 4 1 3 2
4
1 2 4 3
1
1
4
4 3 2 1
```

### 输出

```
1 5 2 4 3 
1 2 3 4 
1 
1 4 3 2 
```

# 题解

## 作者：Inkyo (赞：8)

>这里是墨攸，平生没有什么爱好，就喜欢做div.3题。

这题是CF某场div.3的第二题...

- ## 思路

贪心。

我们需要交换处理后的排列字典序最小，那么自然就可以想到：先把最小的数移到尽量前的位置最优。

那么，我们可以在每次交换的时候，暴力查找整个排列中 $1$ 的位置。然后不断把 $1$ 和在它前面位置的数交换，直到交换到第一位为止。因为每个位置只能交换一次，所以我们还要创建一个 $bool$ 数组，记录哪些位置被交换过了。

然后就处理 $2$，同样暴力查找 $2$ 的位置，然后与在它之前的那个数交换。由于$1$交换时，可能某些位置已经被交换过了，所以一旦发现无法交换（当前位置被用过）就要立即停止。

然后就处理$3,4.....n$，直到字典序最小。

注意：不一定必须要经过$n-1$次交换，只需要字典序最小即可。

复杂度：$O(qn^2)$，复杂度看起来很高，但是足以$A$了这题了。

- ## 优化

那么问题来了：加强数据了怎么办。

我们考虑优化。上面方法复杂度高的原因主要在于暴力查找。我们每次查找最坏情况下都要花费$O(n)$的复杂度，所以总复杂度高。

实际上，我们并不需要暴力查询，我们可以记录每个数的$rank$值（即记录每个数排在哪个位置），查找那个数的时候直接去找那个数的$rank$值即可。交换时顺便处理一下$rank$即可。

这样做，直接把查找的复杂度降值$O(1)$，总复杂度$O(qn)$，可以承受$n=1e5$的数据

## $Code$

```cpp
#include<bits/stdc++.h>
#define orz 0
#define inf 0x3f3f3f3f
#define maxn 105
 
using namespace std;
 
int q, n, a[maxn], rk[maxn], now;
bool used[maxn]; //判断该位置有没有被交换过
 
int main()
{
	scanf("%d", &q);
	while(q --)
	{
		memset(used, 0, sizeof(used));
		now = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++)
		{
			scanf("%d", a + i);
			rk[a[i]] = i;
		}
		while(now != n + 1) //now代表当前查询的数
		{
			int rank = rk[now]; //查询该数的rank值
			if(a[rank] < a[rank - 1] && !used[rank - 1])
			{
				rk[a[rank]] --; rk[a[rank - 1]] ++;
				swap(a[rank], a[rank - 1]);
				used[rank - 1] = true;
			}
			else now ++; //如果最后交换不了了，查询下一个数
		}
		for(int i = 1; i <= n; i ++)
			printf("%d ", a[i]);
		printf("\n");
	}
	
	return orz;
}
```

---

## 作者：andyli (赞：3)

循环操作，每次寻找当前区间中最小的数，若最小数在区间最左侧，则将当前区间的左端点+1变为新的区间，否则将最小数移动至最左侧并将当前区间的左端点改为最小数移动前位置的编号。区间大小为0时循环结束。时间复杂度$O(n^2)$。  

主要代码如下：  
```cpp
const int maxn = 105;

int A[maxn] = {-1u / 2}; // -1u/2=INT_MAX
int move(int l, int r)
{
    int minp = 0;
    for (int i = l; i <= r; i++)
        if (A[i] < A[minp])
            minp = i;
    if (minp == l)
        return l + 1;
    for (int i = minp - 1; i >= l; i--)
        swap(A[i], A[i + 1]);
    return minp;
}
int main()
{
    int q;
    io.read(q);
    while (q--) {
        int n;
        io.read(n);
        for (int i = 1; i <= n; i++)
            io.read(A[i]);
        int pos = 1;
        while (pos <= n)
            pos = move(pos, n);
        for (int i = 1; i <= n; i++)
            io.write(A[i], " \n"[i == n]);
    }
    return 0;
}
```

---

## 作者：Konnyaku_ljc (赞：3)

### 题目大意
> 给你一个区间，第x个和x+1个数可以交换且仅能交换1次，问如何才能通过交换才能使字典序最小？

由题意知——   
我们首先把最小的数交换到最前面，然后，用一个bool数组记录一下有没有被交换过，如果不能交换，那就换下一个大的数。  

因为题目给几个数都小于等于n并且不相同，所以难度下降一大截。

### 代码——
```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
int Q,n,a[105],b[105];//a记录原数组，b记录数的位置
bool bo[105];//记录交没交换过
int main()
{
	cin >> Q;//Q组数据
	while (Q--)
	{
		
		memset(bo,0,sizeof(bo));//数组清零
		cin >> n;
		for ( int i = 1; i <= n; i++ )
		{
			cin >> a[i];
			b[a[i]] = i;//记录出现位置
		}
		for ( int i = 1; i <= n; i++ )
			for ( int j = b[i]-1; j >= 1; j-- )
			{
				if (!bo[j] && a[j] > a[j+1] ) bo[j] = 1 , swap(a[j+1],a[j]);
                //如果可以交换并且比较优，就换
				else break;//否则，换下一个
			}
		for ( int i = 1; i <= n; i++ ) cout << a[i] << " ";
        //输出
		cout << endl;
	}
}
```

---

## 作者：littlejuruo (赞：3)

### 题目大意：

给你$n$个数，范围是$1-n$，但是乱序的，你可以选择交换相邻的两个位置的数，每个位置只能交换一次，顺序任意，也可以不交换，令最后结果字典序最小

### 思路：

贪心就好了，每次暴力选取当前没移动的最小的数，将它移动到能移动的最前面

### code:

```cpp
    #include<bits/stdc++.h>
    using namespace std;
     
    void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
    int read()
    {
    	int f=1,a=0;char ch=getchar();
    	while(ch<'0'||ch>'9'){
    		if(ch=='-'){
    			f=-f;
    		}
    		ch=getchar();
    	}
    	while(ch>='0'&&ch<='9'){
    		a=a*10+ch-'0';
    		ch=getchar();
    	}
    	return a*f;
    }
     
    int Q,ma,n;
    int num[150];
    int Find(int x)
    {
    	for(int i=1;i<=n;++i){
    		if(num[i]==x){
    			return i;
    		}
    	}
    }
     
    int main()
    {
    //  file("");
    	Q=read();
    	while(Q--){
    		memset(num,0,sizeof(num)),ma=1;//多测不清空，爆零两行泪
    		n=read();
    		for(int i=1;i<=n;++i){
    			num[i]=read();
    		}
    		for(int i=1;i<n;++i){
    			int nn=Find(i);

    			for(int j=nn;j>ma;--j){
    				if(num[j-1]<num[j])break;//这个判断很重要
    				swap(num[j],num[j-1]);
    			}
    			ma=max(ma,nn);
    		}
    		for(int i=1;i<=n;++i){
    			cout<<num[i]<<' ';
    		}
    		cout<<endl;
    	}
    	return 0;
    }
```


---

## 作者：Vector_ (赞：2)

思路:尽量把小的数往前排，如果这个操作已经进行过直接到下一个数(因为这个数不能再动了)

代码:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[110];
bool vis[110];
int main()
{
	int q;
	cin>>q;
	while(q--)
	{
		memset(vis,false,sizeof(vis));
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++)
		{
			int p;
			for(int j=1;j<=n;j++)
				if(a[j]==i)
				{
					p=j;
					break;
				}
			for(int j=p-1;j>=1;j--)
				if((!vis[j])&&a[j]>a[j+1])
				{
					vis[j]=true;
					swap(a[j],a[j+1]);
				}
		}
		for(int i=1;i<=n;i++) printf("%d ",a[i]);
		printf("\n");
	}
}
```

---

## 作者：FLAMEs_ (赞：1)

本题主要运用贪心求解。

题中要求使序列的字典序**最小**，而且每个位置只能**交换一次**。

由此，我们可以用一个 $pos$ 数组记录每个数据在数列中的位置，在交换时顺便处理一下 $pos$ 即可，期望复杂度 $\Theta(1)$ 。

总的时间复杂度在 $\Theta(qn)$ 左右,可以承受 $n = 10^5$ 的数据。

更详细解释在代码中。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 105
int T,n,a[N],pos[N],now;
bool used[N];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		memset(used,0,sizeof(used));
		now=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]),pos[a[i]]=i;//记录每个数的坐标。 
		while(now!=n+1)//贪心思想，从零开始扫，这样可以使字典序更小。 
		{
			int rk=pos[now];
			if(a[rk]<a[rk-1]&&!used[rk-1])pos[a[rk]]--,pos[a[rk-1]]++,swap(a[rk],a[rk-1]),used[rk-1]=1;//合法，并未标记过。此时可以进行交换并标记使用过。 
			else now++;//不合法，找下一个 
		}
		for(int i=1;i<=n;i++)printf("%d ",a[i]);//输出。 
		printf("\n");//别忘记换行 
	}
	return 0;
}
```


---

## 作者：lsr1409111459 (赞：1)

#### 1 题目描述（[传送门](https://www.luogu.com.cn/problem/CF1256B)）

##### 1.1 题目大意

给你一个长度为 $n$ 的整数序列，你可以进行至多 $n-1$ 次操作，使该序列字典序最小。

操作 $i\ (1 \leq i \leq n-1)$ 是交换序列中 $i$ 和 $i+1$ 的元素，操作 $i$ 最多执行一次。

共有 $q$ 组提问。

##### 1.2 输入格式

第一行一个整数 $q\ (1\leq q \leq 100)$ 。

接下来 $q$ 组输入，每组输入两行。

每组的第一行为一个整数 $n\ (1 \leq n \leq 100)$ 。

每组的第二行为 $n$ 个整数，表示给的长度为 $n$ 的整数序列。

##### 1.3 输出格式

共 $q$ 行。输出每组的答案。

对于每组，输出 $n$ 个整数，为最多 $n-1$ 次交换后得到的字典序最小的序列。

#### 2 解题思路

交换相邻元素使字典序最小，这使我们想到了冒泡排序。但这道题每个位置只能交换一次，所以在冒泡排序的基础上记录每个位置是否进行过操作即可。

冒泡排序有向前（向小）和向后（向大）两种方法。对于本题，如果向后冒的话，无法达到字典序最小，因为我们要尽可能让最小的数字在最前面，而每个位置只能操作一次。所以我们应该从后向前遍历（注意是从 $n-1$ 开始），每次遍历都判断当前元素和后面紧邻它的元素的大小关系即是否可以进行操作。经过若干次遍历后，整个序列不会再改动，即得出最优解。

#### 3 解题代码

```cpp
#include <iostream>
using namespace std;
int q,n;
int a[110];
bool f[110];//当前位置是否进行过操作
int main()
{
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            f[i]=0;
        }
        bool flag=true;//本轮遍历是否有改动
        while(flag)
        {
            flag=false;
            for(int i=n-1;i>=1;i--)
            {
                if(!f[i]&&a[i]>a[i+1])
                {
                    f[i]=true;
                    swap(a[i],a[i+1]);
                    flag=true;
                }
            }
        }
        for(int i=1;i<=n;i++)printf("%d ",a[i]);
        printf("\n");
    }
    return 0;
}
```

#### 4 解题心得

本题数据范围较小，因此采用最暴力的方法进行操作，时间复杂度为 $O(pn^2)$ 。如果数据范围增大，可能会有更优算法，不过本算法解本题足够。

---

## 作者：wangyixuan_s_father (赞：0)

## 题意
输入一个数列，数值为 $1$ 至 $n$。现在要通过相邻两个数的交换来使它们字典序最小。交换 $a_1$，$a_2$ 两数称为在位置 $1$ 上的交换。每个位置只能交换一次。
## 思路
不难看出，$1$ 一定能通过排序来到第一个。所以，重点就在于如何处理剩下的交换次数。因为每个位置都只有 1 次机会交换，所以可以用 bool 数组来表示交换状态。这样就能得出一个方法：遍历数组，发现 $b_i$ 为 $0$（没交换过）时进入 scan 函数找出该段未交换段中最小值进行交换。剩下的细节看代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool b[101],flag;
int f[101],tmp,tmp1,t,n;
void scan(int x)//搜索最小数
{
	if(flag)
	{
		return;
	}
	if(x>n)//越界
	{
		flag=1;
		return;
	}
	if(f[x]<tmp)//发现最小值
	{
		tmp=f[x];
		tmp1=x;
	}
	if(b[x]==1)//该段结束
	{
		flag=1;
		return;
	}
	scan(x+1);
	return;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&f[i]);
		}
		int x=n-1;
		while(x>0)
		{
			for(int i=1;i<n;i++)
			{
				if(b[i]==0)//找段起点
				{
					tmp=f[i];
					tmp1=i;
					scan(i+1);
					for(int j=tmp1;j>i;j--)//交换
					{
						f[j]=f[j-1];
						b[j-1]=1;
						x--;
					}
					if(!b[i])//若当前数为最小值
					{
						b[i]=1;//弃置交换机会
						x--;
					}
					else
					{
						f[i]=tmp;
						i=tmp1-1;//跳过该段
					}
					flag=0;
				}
			}
		}
		for(int i=1;i<=n;i++)//最终的输出
		{
			cout<<f[i]<<" ";
		}
		cout<<endl;
		for(int i=1;i<=n;i++)//还有初始化别忘了
		{
			b[i]=0;
			f[i]=0;
		}
	} 
	return 0;//完结撒花
   //求管理大大通过
}
```
#### 题外话
肝了两个小时的代码，居然出了一个最优解（时间 $15ms$，内存 $8k$）！

---

## 作者：幽界の冥神 (赞：0)

[水坎·越空之门（题目传送法阵）](https://www.luogu.org/problem/CF1256B)

本题首先要知道每次贪心地将最小的数移到当前的最前方$t$处的方案一定是不劣的
，剩下的就好办了。


可以直接看代码，这里注释一下：

1.$b[i]$表示$i$在$a[i]$中出现的位置

2.$c[i]$表示当前这个点的交换机会用过了没有

3.若当前$i$已在$b[i]$位置，则放弃交换机会

大概就是这样

上代码：

```cpp
#include <bits/stdc++.h>

#define N 105

using namespace std;

int q, n, a[N], b[N], c[N];

int main ()
{
	cin >> q;
	while (q --)
	{
		cin >> n;
		memset (a, 0, sizeof (a));
		memset (b, 0, sizeof (b));
		memset (c, 0, sizeof (c));
		for (int i = 1; i <= n; ++i)
		{
			cin >> a[i];
			b[a[i]] = i;
		}
		for (int i = 1; i <= n; ++i)
		{
			if (i == b[i])
				c[i] = 1;
			for (int j = b[i] - 1; j >= 1; --j)
			{
				if (c[j])
					break;
				c[j] = 1;
				if (a[j] > a[j + 1])
					swap (a[j + 1], a[j]);
			}
		}
		for (int i = 1; i <= n; ++i)
		{
			cout << a[i] << (i == n ? '\n' : ' ');
		}
	}
	return 0;
}
```

觉得还行点个赞再走吧

---

