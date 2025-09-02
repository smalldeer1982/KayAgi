# Array K-Coloring

## 题目描述

You are given an array $ a $ consisting of $ n $ integer numbers.

You have to color this array in $ k $ colors in such a way that:

- Each element of the array should be colored in some color;
- For each $ i $ from $ 1 $ to $ k $ there should be at least one element colored in the $ i $ -th color in the array;
- For each $ i $ from $ 1 $ to $ k $ all elements colored in the $ i $ -th color should be distinct.

Obviously, such coloring might be impossible. In this case, print "NO". Otherwise print "YES" and any coloring (i.e. numbers $ c_1, c_2, \dots c_n $ , where $ 1 \le c_i \le k $ and $ c_i $ is the color of the $ i $ -th element of the given array) satisfying the conditions above. If there are multiple answers, you can print any.

## 说明/提示

In the first example the answer $ 2~ 1~ 2~ 1 $ is also acceptable.

In the second example the answer $ 1~ 1~ 1~ 2~ 2 $ is also acceptable.

There exist other acceptable answers for both examples.

## 样例 #1

### 输入

```
4 2
1 2 2 3
```

### 输出

```
YES
1 1 2 2
```

## 样例 #2

### 输入

```
5 2
3 2 1 2 3
```

### 输出

```
YES
2 1 1 2 1
```

## 样例 #3

### 输入

```
5 2
2 1 1 2 1
```

### 输出

```
NO
```

# 题解

## 作者：yuzhechuan (赞：4)

首先不要被标签吓到了，这是一道水题，绝对没有绿题难度

~~自认为代码是三篇c++题解中最简最快的~~

---

### 思路：

这道题有这么几个任务：

1. 用上所有颜色

1. 每种相同数字的颜色不同

1. 输出

对于第一个，简单地，只需设置一个变量color，一直++，超过了颜色数就再次从1开始

对于第二个，为了让相同数字排在一起我们需要一次sort，之后就只要保证该种数字的数量小于颜色数就好了

对于输出，按照读入顺序再次sort即可

---

之后就是模拟了！

```cpp
#include <bits/stdc++.h>
using namespace std;
int k,n;
struct node
{
	int x,id,ans; //x为数字,id为输入顺序,ans为颜色
}a[5005];
bool cmp1(node x,node y) //第一次按数字排序
{
	return x.x<y.x;
}
bool cmp2(node x,node y) //第二次按输入顺序排序
{
	return x.id<y.id;
}
int main()
{
	scanf("%d%d",&n,&k);
	if(n<k) //颜色比格子多，不可能全部用上
	{
		puts("NO");
		return 0;
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i].x),a[i].id=i;
	sort(a+1,a+1+n,cmp1);
	int start=0,color=0; //start为某种数字首次出现的位置,color为当前要填的颜色
	for(int i=1;i<=n;i++)
	{
		if(++color>k) color-=k; //换一种颜色,太大了就回到第一种颜色
		a[i].ans=color; //填色
		if(a[i].x==a[i-1].x)
		{
			if(i-start+1>k) //减一减得到已经填了几个该种相同数字，是否大于颜色数
			{
				puts("NO");
				return 0;
			}	
		}
		else start=i; //新数字,新起点
	}
	puts("YES");
	sort(a+1,a+1+n,cmp2); //按输入顺序重排一次
	for(int i=1;i<=n;i++)
		printf("%d ",a[i].ans); //输出
}
```

---

~~数据不大，不IO优化也行。。。~~

---

## 作者：floatery (赞：3)

本题存在恶意评分嫌疑

思路：桶排序，统计各个数字出现次数，如果一个数字出现次数多于颜色总数，则输出NO，否则输出YES；同时可以对排好序的序列用一定的顺序（我的代码是从1~k）进行染色。
```cpp
#include <stdio.h>
int a[5001],cnt[5001],color[5001];
int main()
{
	int n,k,t=0;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		cnt[a[i]]++;
	}
	for(int i=1;i<=5000;i++)
	{
		if(cnt[i]>k)
		{
			printf("NO\n");
			return 0;
		}
		else
		{
			for(int j=1;j<=n;j++)
			{
				if(a[j]==i)
				{
					color[j]=++t;
					t%=k;
				}
			}
		}
	}
	printf("YES\n");
	for(int i=1;i<=n;i++)
	{
		if(i!=1) printf(" ");
		printf("%d",color[i]);
	}
	return 0;
}
```

---

## 作者：oimaster (赞：1)

我又来写题解了，呵呵呵，最近沉迷于刷题、写题解，无法自拔……
好了，不说别的了，现在快点进入正题。

## 题面
### 英文题面
这里从来不会出现英文题面的好吗，需要你去 [这里](http://codeforces.com/problemset/problem/1102/B) 看的。
### 中文题面
写完今早的题解后，我想了想，决定还是把题目的意思放出来，能节约大家的时间。
给出一个长为 $n$ 的序列 $a$ 和 $k$ 种颜色,用这 $k$ 种颜色给 $a$ 中的元素染色，要求：
+ 每个元素都要被染色
+ 每种颜色都要被使用
+ 每种颜色不会被用于相同的元素(即若颜色

如果没有可行的方案，输出 `NO` ,否则输出 `YES` 和任何一种可行的方案。即若颜色 $c_i = c_j(i \neq j)$ ，必须保证 $a_i \neq a_j$
## 思路
首先先膜拜一下大佬 xyf007 ，他写的这篇洛谷题解引发了我的思路（虚拟赛后看见的，大家别以为我作弊），然后我想了想，决定写一下这篇题解。

我们这道题的确完全不用各种各样的高级算法，什么桶排序、什么双指针、什么vis数组，都不要，我们只要结构体，一个变量 `num` ，就可以做了。

如果 $n<k$ 的话，肯定用不完所有的数字，输出 $-1$。

我们首先判断是否有数字出现次数 $>k$ ，如果有，那么一定不行的。

如果没有，那么一定行。我们像这样填色。

+ 先将数组按照大小排序

+ 然后让一个变量 `num` 来从 $1$ 到 $k$ 循环，到了 $k+1$ 就把它赋值为 $1$。

+ 轮流填， `num` 是多少就填多少。
 
想想，为什么这样子可以？

然后就十分简单，我们按照原始数列的编号排个序，输出即可。
## 代码
请到 [这里](https://oi-master.github.io/post/codeforces-contest-1102-b-ti-jie/) 查看代码。

---

## 作者：YuanZhizheng (赞：1)

**先声明，下面文章中提及的指针，均不是C语言中真正真正意义的指针，而是“双指针”操作中的指针**。

本题思维上的难度是很低的，只要你的代码能过一些测试点就说明你大体思路是对的，但是需要注意一些细节。

思路再简单也还是要说一下的吧。

**1.思路**：

从题目入手：

(1).1~n数组中每个元素都要被染色。提取到一个要点——**应该要遍历数组**。再一看数据范围很小，所以遍历数组应该是一个可行的方案。当然，我们也应该注意到，题目**没有说不能用和a[i]相同的颜色来染a[i]**。

(2).输入k代表有1、2...k一共k种元素，都要用来染色。这就提取到第一个要点——**k种元素都要使用到**。

做法x：如果只有(1)和(2)两个点的话，那么这题就简单利用**双指针**，一个指向原数组；另一个指向1，依次向k移动，指到k以后跳回1继续循环，就可以完成了。

(3).如果原数组中的a[i]和a[j]两个元素是同种颜色的话，那么在染色的时候，不能拿相同的颜色去染a[i]和a[j]。这个要点，给我们遍历数组的时候增加了一点点限制，所以我们就不能原封不动的使用前面提到的做法x了。——我们应该想到，**既然原数组中颜色相同的不能染一样的颜色，那么我们就由1~k依次给颜色相同的元素染色**，这样就解决第(3)点了。

所以，我们只需要再添加一个指针，就可以了。

一个指针i指向1~5000的每一个元素，另一个指针j指向数组来遍历数组寻找值为i的数组元素，另外一个指针key指向1~k中每一种颜色。只有指针i和j需要循环，所以这题的做法可以是O(n^2)的复杂度。

**2.坑点**：

有可能原数组中几乎没有相同的元素，会导致key指针从来都不会移动到k，导致无法使用到所有元素。

只要注意到这个细节，那么上面的做法就基本没有问题了，下面直接上AC代码，代码中还会有一些补充助于理解。
```
#include<bits/stdc++.h>
using namespace std;
int a[5005];//接收数组
bool vis[5005];//标记当前位置是否染过色，每个地方只需要染一次色就够了
int coloruse[5005];//记录是否使用这个颜色的数组
int main()
{
    int i,j,n,k;
    cin>>n>>k;
    for(i=1; i<=n; i++)
        cin>>a[i];
    bool flag=1;
    for(i=1; i<=5000; i++)//指向1~5000每个数字，因为原数组中可能出现的数字一定在1~5000中
    {
        if(flag==0)
            break;
        int key=1;//指向1~k
        for(j=1; j<=n; j++)
        {
            if(a[j]==i&&!vis[j]&&key<=k)//如果是本来颜色就是i的话，由1到k依次染色，可以保证不会重复
            {
                coloruse[key]++;//标记当前颜色是否已经用过
                a[j]=key++;//key+1，保证下一次遇到i不会用同种颜色
                vis[j]=1;//标记这点已经被染色
            }
            else if(a[j]==i&&!vis[j]&&key>k)//如果还有等于i的点，但是颜色数量已经不够了，那可以直接退出了
            {
                flag=0;
                break;
            }
        }
    }
    if(flag==1)
    {
        j=1;//指向数组
        for(i=1; i<=k; i++)//检查1~k中是否有颜色没有使用过
        {
            if(!coloruse[i]&&j<=n&&coloruse[a[j]]>1)//保证当前颜色足够多
            {
                coloruse[a[j]]--;
                coloruse[i]++;
                a[j]=i;
                j++;
            }
            else if(!coloruse[i]&&j<=n&&coloruse[a[j]]==1)//如果当前颜色不够多的话，就找到够多的为止
            {
                while(coloruse[a[j]]==1)
                {
                    j++;
                }
                coloruse[a[j]]--;
                coloruse[i]++;
                a[j]=i;
                j++;
            }
            if(j>n&&!coloruse[i])//如果已经遍历了数组，还是没有用完颜色，那就无法完成题目要求了
            {
                flag=0;
            }
        }
    }
    if(flag==1)
    {
        cout<<"YES"<<'\n';
        for(i=1; i<=n; i++)
            printf("%d ",a[i]);
    }
    else
        printf("NO");
    return 0;
}
```

---

## 作者：两年打铁 (赞：1)

蒟蒻终于过了，发篇题解纪念一下（~~这都要纪念果然很弱~~）

我的思路是：我~~们~~先记录每一个数字出现的次数，在输入的时候就可以对cnt数组进行更新，我~~们~~使每个ai为它这个数出现的次数，这样就初步地保证了不重复。

接下来，我~~们~~要考虑如何让每个颜色都涂到，那再开一个数组记录这个颜色被涂的次数，这样就可以完美地解决有些颜色没涂。我~~们~~对于每一个没有没涂过的颜色，在改动后的数组里找到一个被涂次数大于1的颜色，把它给换成未涂过的颜色，这样就可以保证每个颜色被涂，并且每个数都被涂。



------------

```
#include<bits/stdc++.h>
using namespace std;
void read(int &x)
{
	x=0;
	char ch=getchar();
	int pd=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			pd=-pd;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=pd;
}
void write(const int &x)
{
	int tmp=x;
	int s=0;
	char fake[10000];
	if(tmp<0)
	{
		tmp=-tmp;
		putchar('-');
	}
	while(tmp>0)
	{
		fake[s++]=tmp%10+'0';
	}
	while(s>0)
	{
		putchar(fake[--s]);
	}
}
int n,k,a[1000001];
int maxn;
int cnt[10000001];
int s[1000001];
bool colored[1000001];
int gg[1000001];
int main()
{
	read(n);
	read(k);
	if(k>n)
	{
		puts("NO");
		return 0;
	}//两个小判断，k=n的判断非常重要。
	if(k==n)
	{
		puts("YES");
		for(register int i=1;i<=k;++i)
		{
			cout<<i<<" ";
		}
		return 0;
	}
	for(register int i=1;i<=n;++i)
	{
		cin>>a[i];
		++cnt[a[i]];//cnt记录每个数出现的次数。
		s[i]=cnt[a[i]];//显然s数组记录的是改动后的数组，gg数组记录的是每个颜色被涂的次数。
		gg[s[i]]++;
		if(cnt[a[i]]>k)//非常明显的判断，如果出现次数大于K那肯定不能保证不一致。
		{
			puts("NO");
			return 0;       
		}
	}
	for(register int i=1,j=n;i<=k;++i)
	{
		while(gg[s[j]]<=1)j--;//每次找到一个被涂次数>1的颜色
		if(gg[i]==0)gg[s[j]]--,gg[i]++,s[j]=i;//把它换掉
	}
	puts("YES");
	for(register int i=1;i<=n;++i)
	{
		cout<<s[i]<<" ";
	}
}

```

---

## 作者：xyf007 (赞：1)

# 我的想法非常奇特！！！（不使用vis[i][j]表示是否染色）
## 下面是我的思路：
### 既然不能给相同的数染相同颜色，那么就按大小排序后，按序染色，再排序回去。
#### 以下代码
---
```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int n,k,b[5001];
struct node
{
	int sum,id,color;
}a[5001];
bool cmp1(node a,node b)
{
	return a.sum<b.sum;
}
bool cmp2(node a,node b)
{
	return a.id<b.id;
}//两次排序
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		a[i].id=i;
	}
	if(n<k)
	{
		printf("NO");
		return 0;//n<k必然不行
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].sum);
		b[a[i].sum]++;
		if(b[a[i].sum]>k)
		{
			printf("NO");
			return 0;//有出现次数大于k的也不行
		}
	}
	sort(a+1,a+n+1,cmp1);
	int now=1;
	for(int i=1;i<=n;i++)
	{
		a[i].color=now++;//按序染色
		if(now==k+1)
		{
			now=1;
		}
	}
	sort(a+1,a+n+1,cmp2);
	printf("YES\n");
	for(int i=1;i<=n;i++)
	{
		printf("%d ",a[i].color);
	}
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 题目分析：

首先判断是否可行，题目给出的限制有三个：

1. “每个元素都要被染色”，这是一句有用的废话。

2. “每种颜色都要被使用”，结合后面的第三点，发现我们其实是希望眼色更多的，所以只要颜色不是多到大于 $n$ 都是没有问题的。

3. “每种颜色不会被用于相同的元素”，这应该是最重要的一点，这个要求的限制使得不能有任何一个元素的数量多于颜色的数量，否则一定会有颜色重复。

然后考虑如何构造这样一组颜色序列，这里需要注意第二条条件，这里可以考虑先将相同颜色放在一起，然后用递增的颜色一个一个刷过去，这样就能在保证每一种颜色都使用的前提下保证同种元素的颜色不同了。

----------
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct node{
	int id,col,num;
}p[5005];
int n,k,cnt[5005],now;
bool cmp1(node a,node b){
	return a.num<b.num;
}
bool cmp2(node a,node b){
	return a.id<b.id;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&p[i].num);
		p[i].id=i;
		cnt[p[i].num]++;
	}
	for(int i=1;i<=5000;i++)
	if(cnt[i]>k){
		printf("NO\n");
		return 0;
	}
	if(k>n){
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	sort(p+1,p+n+1,cmp1);
	for(int i=1;i<=n;i++){
		now++;
		if(now>k)now=1;
		p[i].col=now;
	}
	sort(p+1,p+n+1,cmp2);
	for(int i=1;i<=n;i++)
	printf("%d ",p[i].col);
	return 0;
}
```


---

## 作者：shenmadongdong (赞：0)

```
var n,i,k,s,j,t,p:longint;
    a,b,c,d:array [1..5000] of longint;
begin
  read(n,k);
  for i:=1 to n do read(c[i]);
  for i:=1 to n do
  begin
    s:=c[i];
    p:=0;
    for j:=1 to n do if (c[j]=s) and(d[j]=0) then begin
    d[j]:=1;
    inc(a[s]);
    if a[s]>k then begin write('NO'); exit; end
    else b[j]:=(a[s]+t) mod k+1;
    p:=1;
    end;
    if (p=1) then t:=t+a[s];
  end;
  writeln('YES');
  for i:=1 to n do write(b[i],' ');
end.
```

---

## 作者：Zechariah (赞：0)

首先如果n<k那么就是NO  
题目要求1到k都输出，我们可以先输出1到k，记录每一组都输出了哪些数，用一个桶记录下每一组的元素个数，然后不断递减保证同一组的数字都不同，注意不要与之前输出的1到k重复  
```cpp
#include <bits/stdc++.h>
#define rg register
#define inl inline
typedef long long ll;
const int N = 5e3 + 10, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
    long long read()
    {
        rg long long num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) >= '0'&&ch <= '9')
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
int tong[N], c[N];
bool have[N][N];

int main()
{
    rg int n = fast_IO::read(), k = fast_IO::read(), which = 0;
    if (n < k) { puts("NO"); return 0; }
    for (rg int i = 1; i <= n; ++i)++tong[c[i] = fast_IO::read()];
    for (rg int i = 1; i <= n; ++i)
        if (tong[c[i]] > k) { puts("NO"); return 0; }
        else if (tong[c[i]] > tong[which])which = c[i];
    puts("YES");
    for (rg int i = 1; i <= k; ++i)
    {
        if (i != 1)putchar(' ');
        fast_IO::write(k - i + 1);
        have[c[i]][k - i + 1] = true;
    }
    for (rg int i = k + 1; i <= n; ++i)
    {
        putchar(' ');
        while (have[c[i]][tong[c[i]]])--tong[c[i]];
        fast_IO::write(tong[c[i]]--);
    }
    return 0;
}

```

---

