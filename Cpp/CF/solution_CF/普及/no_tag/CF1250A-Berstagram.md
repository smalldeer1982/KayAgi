# Berstagram

## 题目描述

**题意简述**

给定两个序列 $a=[a_1,a_2,\dots,a_m]$ 和 $b=[b_1,b_2,\dots,b_n]$，其中 $b_i$ 的初始值为 $i$，$a_i$ 的初始值将由键盘读入。对于每个 $a_i$，若 $b_j=a_i$，则将 $b_j$ 与 $b_{j-1}$ 的值调换（若 $j=1$，则序列不变）。

## 样例 #1

### 输入

```
3 5
3 2 1 3 3
```

### 输出

```
1 2
2 3
1 3
```

## 样例 #2

### 输入

```
10 6
7 3 5 7 3 6
```

### 输出

```
1 2
2 3
1 3
4 7
4 5
6 7
5 7
8 8
9 9
10 10
```

# 题解

## 作者：Withershine (赞：6)

题意描述的很清楚，这里就不多赘述。

### 思路
看题，对于每个 $a_i$，若 $b_j=a_i$，则将 $b_j$ 与 $b_{j-1}$ 的值调换（若 $j=1$，则序列不变）。一开始想的是最直接的暴力，复杂度为 $O(nm)$，虽然开了三秒的时限，但 $4\times10^{10}$ 的数据明显不是三秒钟就能解决的，含恨倒在第 $28$ 个数据点。

**那就换个思路吧。**

再回头看一下题目，不妨换个想法来理解题目中的数组 $a$，将读入的数组 $a$ 看作读入 $m$ 次数字 $a$，将数字 $a$ 它当前所在的位置与它前一个位置的数进行交换。这样复杂度就降了一个数量级。

#### 以样例 $1$ 为例

数组 $b$ 初始：${1,2,3}$。

这时读入 $3$，理解为将数字 $3$ 所在位置与它前一个位置的数，也就是数字 $2$ 交换位置。

第一次操作后变为：${1,3,2}$。

读入第二个数字 $2$，理解为将数字 $2$ 所在位置与它前一个位置的数，也就是数字 $3$ 交换位置。因为此时数字 $2$ 的位置在三号位，二号位置是数字 $3$，故交换它们的位置。

第二次操作后变为：${1,2,3}$。 

这时读入 $1$，理解为将数字 $1$ 所在位置与它前一个位置的数交换位置。但此时数字 $1$ 在一号位置，由于题目限制，所以不做交换。

第三次操作后变为：${1,2,3}$。

剩下两次操作思路一致。

第四次操作后：${1,3,2}$。

第五次操作后：${3,1,2}$。

### 代码实现
在代码中，我开了一个结构体，用来储存数字 $i$，它的最小值和最大值。又开了一个数组 $tag$，用来记录数字 $i$ 所在的位置。

#### 初始化
对于每个 $b_i$，它的初始值是 $i$，它最靠前的位置和最靠后的位置是它自己。

#### 交换及更新位置
```cpp
		a = read();
        ll now = tag[a];//数字a现在的位置
        ll last = now - 1;//now的上一个位置
        if(last == 0)
        {
            continue;
        }
        swap(b[now] , b[last]);
        tag[a] = last;
        tag[b[now].num] = now;
        b[last].minn = min(b[last].minn , last);
        b[now].maxn = max(b[now].maxn , now);
```

结合代码来看，对于每一个交换后的 $a$，它的位置变为 $last$，也就是 $now-1$，明显，此时 $a$ 的最大值并不会更新，因为交换后 $a$ 的位置一定比记录的 $maxn$ 的值小，所以只需要更新最小值。同理，向后移了一个位置的**原先的** $last$ 的位置所对应的数，它的 $minn$ 值也不会改变，只需要更新 $maxn$ 的值。

注意，这里交换位置后，原先的 $now$ 与 $last$ 所对应的数发生了改变，此时的 $last$ 这个位置所在值才是 $a$。

### 代码
补充一句话：最后的数组 $t$ 是为了按顺序输出，与核心思路无关。

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#define ll long long
#define inf 0x3f3f3f3f
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
#pragma comment(linker , "/stack : 200000000")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
inline char gchar()
{
    static char buf[1000000] , *p1 = buf , *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1000000 , stdin) , p1 == p2) ? EOF : *p1++;
}
inline ll read()
{
    ll x = 0 , f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	  {
        if(ch == '-')
        {
        	f = -1;
		}
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
	  {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
ll n , m;
ll a;
struct node
{
    ll num , maxn , minn;
}b[1100000] , t[1100000];
ll tag[1100000];//记录数字i所在的位置
signed main()
{
    n = read();
    m = read();
    fr(i , 1 , n)
    {
        b[i].num = b[i].maxn = b[i].minn = tag[i] = i;
    }
    fr(i , 1 , m)
    {
        a = read();
        ll now = tag[a];//数字a现在的位置
        ll last = now - 1;
        if(last == 0)
        {
            continue;
        }
        swap(b[now] , b[last]);
        tag[a] = last;
        tag[b[now].num] = now;
        b[last].minn = min(b[last].minn , last);
        b[now].maxn = max(b[now].maxn , now);
    }
    fr(i , 1 , n)
    {
       t[b[i].num] = (node)b[i];
    }
    fr(i , 1 , n)
    {
        printf("%lld %lld\n" , t[i].minn , t[i].maxn);
    }
    system("pause");
    return 0;
}
```


---

## 作者：Goodrage (赞：1)

~~标题就是 Instagram 的改编~~
#### 思路分析
暴力维护序列顺序，修改并同时记录最大位置与最小位置。

$\textit{ori}$ 是原始数列，数列中元素会改变。$pos_i$ 是数 $i$ 在序列 $\textit{ori}$ 中的位置（从左数）。

$\textit{mx}$ 记录位置最大值，$\textit{mn}$ 记录位置最小值。

$\textit{other}$ 是和这个数字调换的另一个数字，即它上面的一个。

```cpp
#include<bits/stdc++.h>
using namespace std;
int ori[100100],pos[100100];
int mx[100100],mn[100100];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		mx[i]=i;//初始每个数字都在自己对应位置上，最大值和最小值都是它自己。
		mn[i]=i;
		ori[i]=i;
		pos[i]=i;
	}
	while(m--)
	{
		int tmp;
		scanf("%d",&tmp);//需要移动的数字
		int tmppos=pos[tmp];//这个数字的对应位置
		if(tmppos!=1)//如果是第一个，不用调换
                {
                    int other=ori[tmppos-1];//它前面的数，不过过会就不是前面了，所以要记录一下
                    swap(ori[tmppos-1],ori[tmppos]);//改变原本的数列里的位置
                    pos[tmp]=tmppos-1;
                    pos[other]=tmppos;//改变记录位置的数列
                    mx[tmp]=max(mx[tmp],pos[tmp]);
                    mn[tmp]=min(mn[tmp],pos[tmp]);
                    mx[other]=max(mx[other],pos[other]);
                    mn[other]=min(mn[other],pos[other]);//更新最大位置与最小位置
                }
	}
	for(int i=1;i<=n;i++)//挨个输出
		printf("%d %d\n",mn[i],mx[i]);
	return 0;
}

```
#### 结果

发这篇题解时，题目的 Remotejudge 似乎是崩的，但是 CF 上是[这样](https://codeforces.com/contest/1250/submission/143497357)。


---

## 作者：ChenZQ (赞：0)

这道题乍一看数据范围很难，但是我们发现每个数最多最少都是出现一次。

所以我们可以开一个数组表示这个数目前的位置，再开两个数组分别表示这个数存在的最大和最小位置，每次交换时就以数值为下标更新数组就好了。

具体详见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
int mx[N],mi[N],id[N];

int a[N],b[N];

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) b[i]=i,mx[i]=mi[i]=id[i]=i;
	for(int i=1;i<=m;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	{
		int k=id[a[i]];//现获取下标。
		if(k==1) continue;//如果下标为一就不操作。
		swap(b[k],b[k-1]);//交换原数组中的数。
		mi[a[i]]=min(mi[a[i]],k-1);//往前移了一格，更新最小值。
		mx[b[k]]=max(mx[b[k]],k);//前面的往后挪了一格，更新最大值。
		swap(id[a[i]],id[b[k]]);//交换下标。
	}
	for(int i=1;i<=n;i++) printf("%d %d\n",mi[i],mx[i]);
}
```

---

