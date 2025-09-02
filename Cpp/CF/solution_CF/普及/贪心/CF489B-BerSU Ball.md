# BerSU Ball

## 题目描述

The Berland State University is hosting a ballroom dance in celebration of its 100500-th anniversary! $ n $ boys and $ m $ girls are already busy rehearsing waltz, minuet, polonaise and quadrille moves.

We know that several boy&girl pairs are going to be invited to the ball. However, the partners' dancing skill in each pair must differ by at most one.

For each boy, we know his dancing skills. Similarly, for each girl we know her dancing skills. Write a code that can determine the largest possible number of pairs that can be formed from $ n $ boys and $ m $ girls.

## 样例 #1

### 输入

```
4
1 4 6 2
5
5 1 5 7 9
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1 2 3 4
4
10 11 12 13
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5
1 1 1 1 1
3
1 2 3
```

### 输出

```
2
```

# 题解

## 作者：_xbn (赞：5)

考虑贪心，首先对男孩和女孩的舞技排序，之后扫描一遍男孩和女孩，

如果能匹配，答案加一。这样做正确是对的，下面给出证明：

对于一个男孩，我们从有序的女孩序列中找能与他匹配的女孩，因为女孩从大到小排好了序，

所以越靠后的女孩肯定不会被选，所以正确性正确。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k,p,q,ans,sum,tot,cnt,a[100002],b[100002];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>b[i];
	}
	sort(b+1,b+m+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(abs(a[i]-b[j])<=1&&a[i]!=-1&&b[j]!=-1)
			{
				ans++;
				a[i]=-1;
				b[j]=-1;
			}
		}
	}
	cout<<ans;
  	return 0;
}
```





---

## 作者：MrFish (赞：2)

## 整体思路： 
#### 使用两个priority_queue来存储男生和女生的能力值（因为要排序）。如果两个队首可以匹配，答案加一，否则两个队首能力值低的被弹出。因为能力值小的那个人既然不能和不能和比他大一些的人配对，就更不能更比他大更大一些的人配对，所以两个队首能力值低的被弹出。直到一个队列空了。
我们来模拟一下样例一。
```latex
样例1：
4
1 4 6 2
5
5 1 5 7 9

Queue 1: 1 2 4 6 
Queue 2: 1 5 5 7 9

第一步:两个队首匹配，全部弹出，答案加一。
       Queue 1: 2 4 6
       Queue 2: 5 5 7 9
第二步:两个队首不匹配，弹出小的。
       Queue 1: 4 6
       Queue 2: 5 5 7 9		
第三步:两个队首匹配，全部弹出，答案加一。
       Queue 1: 6
       Queue 2: 5 7 9  
第四步:两个队首匹配，全部弹出，答案加一。
       Queue 1:
       Queue 2: 7 9 
Queue 1 为空，停止。
答案为三，正确。
```

------------

## AC代码
```cpp
#include<iostream>
#include<queue>
#include<cmath>
#include<vector>

using namespace std;

int main()
{
    int n,m;
    int ans=0;
    priority_queue<int, vector<int>, greater<int> > a; //男生能力值
    priority_queue<int, vector<int>, greater<int> > b; //女生能力值
    //定义从小到大排序的priority_queue
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int tmp;
        cin>>tmp;
        a.push(tmp);
    } //读入男生能力值
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        int tmp;
        cin>>tmp;
        b.push(tmp);
    } //读入女生能力值
    while(!a.empty()&&!b.empty())//如果有一个队列为空，停止。
    {
        if(abs(a.top()-b.top())<=1) //如果匹配（能力值差一），答案加一
        {
            a.pop();
            b.pop();
            ans++;
        }  
        else
        {
            if(a.top()<=b.top())
            {
                a.pop();
            }
            else           
            {
                b.pop();
            } //不匹配，弹出小的队首
        }
    }
    cout<<ans<<endl; //输出
    return 0;
}
```
最后安利一下博客：[blog](https://www.luogu.com.cn/blog/ArthurYu/)

拜拜！

---

## 作者：UperFicial (赞：1)

# 贪心题

### 前言

逗比题，不过这道题对于新手来讲还是很友好的。

题目链接：[$\text{Link}$](https://www.luogu.com.cn/problem/CF489B)

看到楼下的复杂度都是 $O(nlogn)$ 的，这里给个 $O(n)$ 的做法。

目前来看是最优解啊/xyx。

### 题目简述

有两个长度分别为 $n,m$ 的数列 $a,b$，当 $a$ 数列中的第 $x$ 个数和 $b$ 数列中的第 $y$ 个数的差 $\le1$，那么就说明它俩可配对且每个数至多只能被匹配一次，求最多匹配数。

~~还不如回去看题目描述~~

### 题目解析

不难想到是贪心，**与楼下唯一不同的是这里给出贪心证明**。

先说一下怎么贪心：

- 分别将 $a$ 数列和 $b$ 数列从小到大排序

- 设两个指针 $tot1,tot2$，若当前 $\mid a_{tot1}-b_{tot2}\mid\le1$，就说明又有了一组匹配，那么将 $tot1$ 和 $tot2$ 同时往后挪，否则若 $a_{tot1}<b_{tot2}$，那么将 $tot1$ 往后挪，否则 $tot2$ 往后挪。

可为啥这样，以下是证明：

如果对于一个 $a$ 数列中的一个最小的数 $a_x$，它可能和多个在 $b$ 数列的数相匹配，显然，我需要先试试 $b$ 数列中最小的一个 $b_y$，如果可行，那么赶紧配对，再试试 $a$ 数列中第 $2$ 小和 $b$ 数量中第 $2$ 小的；否则，如果 $a_x>b_y$ 说明既然 $b$ 数列最小的已经不行了，那么我们就要再次将最小的和 $a$ 匹配，反之亦然，最后以此类推，发现只是一个不断找最小值的过程，所以就要先排序。

但为什么我的算法是 $O(n)$ 呢？因为这道题中 $a_i,b_i$ 的值都非常小，故可用 $O(n)$ 的桶排/xyx。

_[$code$](https://paste.ubuntu.com/p/zmWHjZHdyD/)_

时空复杂度：$O(n)$。

$$\texttt{The End.by UF}$$

---

## 作者：infinities (赞：1)

此题模拟+贪心即可，思路：

- 先排序一遍（贪心开始）

- 用一个$A$和一个$B$来分别表示目前选到的男孩和目前选到的女孩

- 如果第$A$个男孩比第$B$个女孩矮一个单位以上，将$A+1$反之亦然

- 然后统计一下身高在范围内的个数即可

- 时间复杂度大概$O(n log n+m log m)$（即$O(n log n)$），不会超时

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+10;//此处必须用const(好像是常识)
int a[MAXN],b[MAXN],n,m,A=1,B=1,ans;//定义
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    cin>>m;
    for(int i=1;i<=m;i++)cin>>b[i];
    sort(a+1,a+1+n);
    sort(b+1,b+1+m);//排序，贪心开始
    while(A<=n&&B<=m){//枚举目前选到的男孩和女孩
        if(a[A]>=b[B]-1&&a[A]<=b[B]+1)ans++,A++,B++;//如果可以配对，次数加一，A和B均加1
        if(a[A]<b[B]-1)A++;
        if(a[A]>b[B]+1)B++;//不然就枚举下一个，为了省一点时间，这里没有加else，想加的话也可以，只是可能会慢一点
    }
    cout<<ans<<"\n";//输出个数
}
```

就这么简单。

本题数据很小，如果暴力枚举而不是枚举序号，也能轻松跑过

---

## 作者：hs_wfz_orz (赞：0)

### 题解 CF489B 【BerSU Ball】

### 来看这道题，他要求一位男和一位女成为舞伴，并且要求相差<=1，神仙

### n方判断是否能成为舞伴，能的话用一个vis数组来标记他们已成为舞伴，好的，您WA了；

### 我们设一个男的叫猥琐，一个女的叫纯洁，那么由于男的过于猥琐，所以他有可能和多个纯洁的小女生匹配，可是后面的男的更猥琐，所以我就要猥琐和他相差最小的纯洁匹配，把其他纯洁给后面更猥琐的男的；

### 对于怎么匹配相差最小的，直接sort一遍就行了吖吖啊

# 上代码

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<queue>
using namespace std;
int n,m,b[105],g[105],ans,vis[105];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){//经典for循环
		cin>>b[i];
	}
	cin>>m;
	sort(b+1,b+n+1);//把他们进行排序
	for(int i=1;i<=m;i++){
		cin>>g[i];
	}
	sort(g+1,g+m+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(abs(g[j]-b[i])<=1&&vis[j]==0){
				ans++;
				vis[j]=1;
				break;
			}
		}
	} 
	cout<<ans;
}
```


---

## 作者：xsI666 (赞：0)

本题是排序基础题。
-------------

我们可以将a[i]、b[i]分别从小到大排序后，依次枚举比较两两组合是否符合要求，最后输出答案ans即可。

AC代码：
```cpp
#include <bits/stdc++.h>//万能头文件

using namespace std;//使用标准名字空间

inline int read()//快速读入
{
	int f=1,x=0;
	char c=getchar();

	while(c<'0' || c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}

	while(c>='0' && c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}

	return f*x;
}

int m,n,a[110],b[110],ans;//定义变量，含义如分析

int main()
{
	n=read();
	
	for(register int i=1;i<=n;i++)a[i]=read();
	
	m=read();
	
	for(register int j=1;j<=m;j++)b[j]=read();
    
    //以上为输入
	
	sort(a+1,a+1+n);//对男生进行从小到大排序
	sort(b+1,b+1+m);//对女生进行从小到大排序
	
	for(register int i=1;i<=n;i++)//枚举男生
	{
		for(register int j=1;j<=m;j++)//枚举女生
		{
			if(abs(a[i]-b[j])<=1)//如果满足题目中的条件
			{
				++ans;//更新答案
				
				b[j]=1000;//因为该女生已经有了舞伴，所以将女生设为不可能再匹配
				
				break;//由于该男生已经有了舞伴，就枚举下一个男生
			}
		}
	}
	
	printf("%d",ans);//输出答案
	
	return 0;//结束
}
```


---

