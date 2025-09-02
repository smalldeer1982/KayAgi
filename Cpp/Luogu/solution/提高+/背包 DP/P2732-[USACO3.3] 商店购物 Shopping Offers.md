# [USACO3.3] 商店购物 Shopping Offers

## 题目背景

在商店中，每一种商品都有一个价格（用整数表示）。例如,一朵花的价格是 $2$ ，而一个花瓶的价格是 $5$ 。为了吸引更多的顾客，商店举行了促销活动。

## 题目描述

促销活动把一个或多个商品组合起来降价销售，例如：

三朵花的价格是 $5$ 而不是 $6$ ，$2$ 个花瓶和一朵花的价格是 $10$ 而不是 $12$ 。 请编写一个程序，计算顾客购买一定商品的花费，尽量地利用优惠使花费最少。尽管有时候添加其他商品可以获得更少的花费，但是你不能这么做。

对于上面的商品信息，购买三朵花和两个花瓶的最少花费的方案是：以优惠价购买两个花瓶和一朵花（$10$），以原价购买两朵花（$4$）。

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 3.3


## 样例 #1

### 输入

```
2
1 7 3 5
2 7 1 8 2 10
2
7 3 2
8 2 5```

### 输出

```
14```

# 题解

## 作者：Michael_Li (赞：18)

感觉楼下的题解有些欠缺来补充一下。

首先先讲几个坑点

1.所有优惠方案里不会出现别的物品，所以不要想多，大力搞就行了

2.优惠方案可以多次使用，所以for不用倒过来，这点希望大家注意，我就是没注意第一次按01背包只有41分。

个人感觉我的做法比较好理解，可以给大家提供一点思路。

首先你先观察，发现要你买的物品只有五种，而且所有的优惠方案里没有别的物品，你就只要把编号对应到1.2.3.4.5里就行了，看代码注释

```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
#define N (20010)
using namespace std;
int s, n;
int d[N], need[N], pri[N], f[10][10][10][10][10];//f为dp数组，pri为价格，need表示需要几个
int read(){
    int t = 0;
    char p = getchar();
    while(!isdigit(p)) p = getchar();
    do{
        t = t * 10 + p - 48; 
        p = getchar();  
    }while (isdigit(p));
    return t;
} //快读，打习惯了
struct item{
    int id[100], num[100], v, tot, fin[100];
}q[N];//表示每一个优惠政策
int main(){
    s = read();
    for (int i = 1; i <= s; i++){
        int tot = read();
        q[i].tot = tot;
        for (int j = 1; j <= tot; j++){
            q[i].id[j] = read();
            q[i].num[j] = read();
        }
        q[i].v  = read();
    } 
    n = read();
    for (int i = 1; i <= n; i++){
        int num = read();
        d[num] = i;//d表示我对应的几号物品是1.2.3.4.5中的哪一个
        need[i] = read(), pri[i] = read();
    } 
    for (int i1 = 0; i1 <= need[1]; i1++)    
    for (int i2 = 0; i2 <= need[2]; i2++)
    for (int i3 = 0; i3 <= need[3]; i3++)
    for (int i4 = 0; i4 <= need[4]; i4++)
    for (int i5 = 0; i5 <= need[5]; i5++){
        f[i1][i2][i3][i4][i5] = i1 * pri[1] + i2 * pri[2] + i3 * pri[3] + i4 * pri[4] + i5 * pri[5]; 
```
}//其实我觉得其他题解把单独选的也当dp做，有点杀鸡用牛刀，其实只要预处理一下就行了
```cpp
    for (int i = 1; i <= s; i++){
        for (int j = 1; j <= q[i].tot; j++) q[i].fin[d[q[i].id[j]]] = q[i].num[j];
    }
    for (int i = 1; i <= s; i++){
        for (int i1 = q[i].fin[1]; i1 <= need[1]; i1++)
        for (int i2 = q[i].fin[2]; i2 <= need[2]; i2++)
        for (int i3 = q[i].fin[3]; i3 <= need[3]; i3++)
        for (int i4 = q[i].fin[4]; i4 <= need[4]; i4++)
        for (int i5 = q[i].fin[5]; i5 <= need[5]; i5++)
            f[i1][i2][i3][i4][i5] = min(f[i1][i2][i3][i4][i5], f[i1-q[i].fin[1]][i2-q[i].fin[2]][i3-q[i].fin[3]][i4-q[i].fin[4]][i5-q[i].fin[5]] + q[i].v);
    }//dp转移，其实很水，就是一个模拟离散化的过程有点难想
    printf("%d", f[need[1]][need[2]][need[3]][need[4]][need[5]]);
    return 0;
}
希望大家注意坑点，a题越来越顺利！
```

---

## 作者：installb (赞：12)

做题的时候 看数据范围也是比较重要一件事  
比如这道题  
需要购买 b 种不同的商品 $ 0<=b<=5 $  
可以想到五维完全背包 如果$ b<5 $就假设有$ 5-b $个需要购买0个的物品就可以了  
这时候我们在看k的范围: $ 1<=k<=5 $ , $ (5+1)^5=7776 $绝对不会爆啊  
所以我们可以开始完全背包了  
**这里背包中物品的价值的是每种组合优惠的钱数 用单买所有需要物品的价格减去这个最大的优惠**


细节见注释  
## code:
```cpp
#include <map>
#include <list>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LL long long
#define ULL unsigned long long
using namespace std;
const LL INF = 0x3f3f3f3f3f3f3f3f;

LL dp[6][6][6][6][6] = {0}; // 多重背包
LL s[105][6] = {0},ns[6] = {0},pr_s[105] = {0},pr[6] = {0},val[105] = {0};
LL S,b,n,c,k,p,cnt = 0,sum = 0;
LL to[10005] = {0};
// to是离散化(其实不做也行 999不会爆)把五个物品编号对应到1~5

// s[i][j]代表第i项促销组合含j号物品的数量
// ns[j]代表需要j号物品的数量
// pr_s[i]代表i项组合单价
// pr[j]代表第j号物品单买单价
// val[i]代表买i项组合 比 以单价买里面所有物品 便宜 多少钱

int main(){
	ios::sync_with_stdio(false);
	cin >> S;
	for(register int i = 1;i <= S;i ++){
		cin >> n;
		for(register int j = 1;j <= n;j ++){
			cin >> c >> k;
			if(!to[c]){
				to[c] = ++ cnt; // 离散化
			}
			s[i][to[c]] = k; 
		}
		cin >> pr_s[i];
	}
	cin >> b;
	for(register int i = 1;i <= b;i ++){
		cin >> c >> k >> p;
		ns[to[c]] = k;
		pr[to[c]] = p;
		sum += k * p; // sum代表单买全部需要物品的价格
	}
	for(register int i = 1;i <= S;i ++){
		for(register int j = 1;j <= cnt;j ++){
			val[i] = val[i] + s[i][j] * pr[j];
		}
		val[i] -= pr_s[i]; // 计算每种组合省多少钱
	}
	for(register int i = 1;i <= S;i ++){
		for(register int i1 = s[i][1];i1 <= ns[1];i1 ++){
			for(register int i2 = s[i][2];i2 <= ns[2];i2 ++){
				for(register int i3 = s[i][3];i3 <= ns[3];i3 ++){
					for(register int i4 = s[i][4];i4 <= ns[4];i4 ++){
						for(register int i5 = s[i][5];i5 <= ns[5];i5 ++){
							dp[i1][i2][i3][i4][i5] = max(dp[i1][i2][i3][i4][i5],dp[i1 - s[i][1]][i2 - s[i][2]][i3 - s[i][3]][i4 - s[i][4]][i5 - s[i][5]] + val[i]);
						}
					}
				}
			}
		}
	}
    // 这里完全背包就不多说了 顺序枚举
	cout << sum - dp[ns[1]][ns[2]][ns[3]][ns[4]][ns[5]] << endl;
	return 0;
}
```
话说五维dp确实很少见 但是一定要相信自己的做法

---

## 作者：净霖 (赞：10)

看到满篇的五维dp  我觉得我该放上我的状压

用六进制来存各个状态 然后再用完全背包来搞用不用优惠

详见代码

```c
#include<bits/stdc++.h>
using namespace std;
const int S=100+5,N=10,P=10000+5,C=1000+5;
int sale[S],sp[S],sta=0,f[50000],pri[N],cnt=0,s,b,c,k,p;
//优惠的状态 各优惠花的钱 目标状态 各个状态的最小花费 各个商品的单价 总有多少种商品
int base[N],cd[50000];
//六进制的转化 离散化
template<class t>void rd(t &x)
{//快读
    x=0;int w=0;char ch=0;
    while(!isdigit(ch)) w|=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=w?-x:x;
}

bool jud(int st,int x[N])
{
    int cur=0;
    while(st)
    {
        if((st%6)>x[++cur]) return 0;
        st/=6;
    }
    return 1;
}

int main()
{
    memset(cd,0,sizeof(cd));
    memset(sale,0,sizeof(sale));
    base[1]=1;
    for(int i=2;i<=6;++i) base[i]=base[i-1]*6;//初始化
    rd(s);
    for(int i=1;i<=s;++i)
    {
        int n;rd(n);
        for(int j=1;j<=n;++j)
        {
            rd(c),rd(k);
            if(!cd[c]) cd[c]=++cnt;
            sale[i]+=base[cd[c]]*k;//各个优惠的对应状态
        }
        rd(sp[i]);
    }
    rd(b);
    for(int i=1;i<=b;++i)
    {
        rd(c),rd(k),rd(p);
        if(!cd[c]) cd[c]=++cnt;
        sta+=base[cd[c]]*k,pri[cd[c]]=p;
    }
    for(int ss=1;ss<=sta;++ss)
    {//枚举各种状态
        int pro[N],nw=ss,cur=0;//处理出当前状态所包含的产品及其数量
        while(nw) pro[++cur]=nw%6,nw/=6;
        for(int i=1;i<=cur;++i) f[ss]+=pro[i]*pri[i];
        //算不用优惠直接单买的价格
        for(int i=1;i<=s;++i)//枚举各个优惠
        if(ss>=sale[i]&&jud(sale[i],pro))//判断其是否可用即不能添加商品
        f[ss]=min(f[ss],f[ss-sale[i]]+sp[i]);
    }
    printf("%d",f[sta]);
    return 0;
}
```
悄咪咪放一波蒟蒻的[博客](https://www.cnblogs.com/lxyyyy/)

---

## 作者：Sarah (赞：8)

写一个不是很好想的方法：最短路

每个节点的标号可以映射成一个篮子的物品个数情况，每一个优惠方式（包括以物品原价购买）表示一条边，权值就是花费，所以就是求一个从空篮子到目标篮子的最短路径。代码来自usaco此题题解
```cpp
#include <stdio.h>
#include <string.h>

/* maximum number of offers */
/* 100 offers + 5 degenerate offers */
#define MAXO 105

typedef struct OFFER_T
 {
  int nitem; /* number of items in the offer */
  int itemid[5]; /* item's id */
  int itemamt[5]; /* item's amount */
  int cost; /* the cost of this offer */
 } offer_t;

offer_t offers[MAXO];
int noffer;

/* the cost of each basket type */
int cost[7776];

/* the item statistics */
int itemid[5]; /* the id */
int itemcst[5]; /* the cost of buying just 1 */
int nitem;

/* heap used by Dijkstra's algorithm */
int heap[7776];
int hsize;
int hloc[7776]; /* location of baskets within the heap */

/* debugging routine */
void check_heap(void)
 { /* ensure heap order is maintained */
  int lv;
  return;

  for (lv = 1; lv < hsize; lv++)
   {
    if (cost[heap[lv]] < cost[heap[(lv-1)/2]])
     {
      fprintf (stderr, "HEAP ERROR!\n");
      return;
     }
   }
 }

/* delete the minimum element in the heap */
void delete_min(void)
 {
  int loc, val;
  int p, t;

  /* take last item from the heap */
  loc = heap[--hsize];
  val = cost[loc];

  /* p is the current position of item (loc,val) in the heap */
  /* the item isn't actually there, but that's where we're
     considering putting it */
  p = 0; 

  while (2*p+1 < hsize)
   { /* while one child is less than the last item,
        move the lesser child up */
    t = 2*p+1;
    /* pick lesser child */
    if (t+1 < hsize && cost[heap[t+1]] < cost[heap[t]]) t++;

    if (cost[heap[t]] < val)
     { /* if child is less than last item, move it up */
      heap[p] = heap[t];
      hloc[heap[p]] = p;
      p = t;
     } else break;
   }

  /* put the last item back into the heap */
  heap[p] = loc;
  hloc[loc] = p;
  check_heap();
 }

/* we decreased the value corresponding to basket loc */
/* alter heap to maintain heap order */
void update(int loc)
 {
  int val;
  int p, t;

  val = cost[loc];
  p = hloc[loc];

  while (p > 0) /* while it's not at the root */
   {
    t = (p-1)/2; /* t = parent of node */
    if (cost[heap[t]] > val)
     { /* parent is higher cost than us, swap */
      heap[p] = heap[t];
      hloc[heap[p]] = p;
      p = t;
     } else break;
   }

  /* put basket back into heap */
  heap[p] = loc;
  hloc[loc] = p;
  check_heap();
 }

/* add this element into the heap */
void add_heap(int loc)
 {
  if (hloc[loc] == -1)
   { /* if it's not in the heap */

    /* add it to the end (same as provisionally setting it's value
       to infinity) */
    heap[hsize++] = loc;
    hloc[loc] = hsize-1;
   }

  /* set to correct value */
  update(loc);
 }

/* given an id, calculate the index of it */
int find_item(int id)
 {
  if (itemid[0] == id) return 0;
  if (itemid[1] == id) return 1;
  if (itemid[2] == id) return 2;
  if (itemid[3] == id) return 3;
  if (itemid[4] == id) return 4;
  return -1;
 }

/* encoding constants 6^0, 6^1, 6^2, ..., 6^5 */
const int mask[5] = {1, 6, 36, 216, 1296};

void find_cost(void)
 {
  int p;
  int cst;
  int lv, lv2;
  int amt;
  offer_t *o;
  int i;
  int t;

  /* initialize costs to be infinity */
  for (lv = 0; lv < 7776; lv++) cost[lv] = 999*25+1;

  /* offer not in heap yet */
  for (lv = 0; lv < 7776; lv++) hloc[lv] = -1;
  
  /* add empty baset */
  cost[0] = 0;
  add_heap(0);

  while (hsize)
   {
    /* take minimum basket not checked yet */
    p = heap[0];
    cst = cost[p];

    /* delete it from the heap */
    delete_min();

    /* try adding each offer to it */
    for (lv = 0; lv < noffer; lv++)
     {
      o = &offers[lv];
      t = p; /* the index of the new heap */
      for (lv2 = 0; lv2 < o->nitem; lv2++)
       {
        i = o->itemid[lv2];
	/* amt = amt of item lv2 already in basket */
	amt = (t / mask[i]) % 6;

	if (amt + o->itemamt[lv2] <= 5)
	  t += mask[i] * o->itemamt[lv2];
	else
	 { /* if we get more than 5 items in the basket,
	      this is an illegal move */
	  t = 0; /* ensures we will ignore it, since cost[0] = 0 */
	  break;
	 }
       }
      if (cost[t] > cst + o->cost)
       { /* we found a better way to get this basket */

        /* update the cost */
        cost[t] = cst + o->cost;
	add_heap(t); /* add, if necessary, and reheap */
       }
     }
   }
 }

int main(int argc, char **argv)
 {
  FILE *fout, *fin;
  int lv, lv2; /* loop variable */
  int amt[5]; /* goal amounts of each type */
  int a; /* temporary variable */

  if ((fin = fopen("shopping.in", "r")) == NULL)
   {
    perror ("fopen fin");
    exit(1);
   }
  if ((fout = fopen("shopping.out", "w")) == NULL)
   {
    perror ("fopen fout");
    exit(1);
   }

  fscanf (fin, "%d", &noffer);

  /* read offers */
  for (lv = 0; lv < noffer; lv++)
   {
    fscanf (fin, "%d", &offers[lv].nitem);
    for (lv2 = 0; lv2 < offers[lv].nitem; lv2++)
      fscanf (fin, "%d %d", &offers[lv].itemid[lv2], &offers[lv].itemamt[lv2]);
    fscanf (fin, "%d", &offers[lv].cost);
   }

  /* read item's information */
  fscanf (fin, "%d", &nitem);
  for (lv = 0; lv < nitem; lv++)
    fscanf (fin, "%d %d %d", &itemid[lv], &amt[lv], &cost[lv]);

  /* fill in rest of items will illegal data, if necessary */
  for (lv = nitem; lv < 5; lv++) 
   {
    itemid[lv] = -1;
    amt[lv] = 0;
    cost[lv] = 0;
   }

  /* go through offers */
  /* make sure itemid's are of item's in goal basket */
  /* translate itemid's into indexes */
  for (lv = 0; lv < noffer; lv++)
   {
    for (lv2 = 0; lv2 < offers[lv].nitem; lv2++)
     {
      a = find_item(offers[lv].itemid[lv2]);
      if (a == -1)
       { /* offer contains an item which isn't in goal basket */
        
	/* delete offer */

	/* copy last offer over this one */
        memcpy (&offers[lv], &offers[noffer-1], sizeof(offer_t));
	noffer--;

	/* make sure we check this one again */
	lv--;
	break;
       }
      else
        offers[lv].itemid[lv2] = a; /* translate id to index */
     }
   }

  /* add in the degenerate offers of buying single items 8/
  for (lv = 0; lv < nitem; lv++)
   {
    offers[noffer].nitem = 1;
    offers[noffer].cost = cost[lv];
    offers[noffer].itemamt[0] = 1;
    offers[noffer].itemid[0] = lv;
    noffer++;
   }

  /* find the cost for all baskets */
  find_cost();

  /* calculate index of goal basket */
  a = 0;
  for (lv = 0; lv < 5; lv++)
    a += amt[lv] * mask[lv];

  /* output answer */
  fprintf (fout, "%i\n", cost[a]);
  return 0;
 }
 ```

---

## 作者：「QQ红包」 (赞：7)

嗯。竟然是完全背包的题。


我们为了方便处理，于是将单独购买也当做一种组合。


然后就可以放代码了。


```cpp
/*
ID: ylx14274
PROG: shopping
LANG: C++     
*/
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long
int n;//优惠方案总数
int i,j,k,l,m,z;
struct haha
{
    int n;//n 种商品组成
    int k[6];//数量
    int p;//优惠价 
}a[200];//我们把单独购买的商品也当做一种组合 
int nn;//需要购买的商品数
int d[1000];//存商品标号的，反正最多5种商品
int t;
int ai,bi,ci;
int f[6][6][6][6][6];//dp用的数组
int x[6];//存每种商品需要的数量 
using namespace std;
int main() 
{
    freopen("shopping.in","r",stdin);
    freopen("shopping.out","w",stdout); 
    scanf("%d",&n);
    for (i=1;i<=n;i++)
    {
        scanf("%d",&a[i].n);//读入商品数量
        for (j=1;j<=a[i].n;j++)
        {
            scanf("%d%d",&ai,&bi);//ai：编号
            if (d[ai]==0)//此商品没出现过
            {
                t++;
                d[ai]=t;//存编号 
            }
            a[i].k[d[ai]]=bi;//存组合i所需的第ai种物品的数量 
        }
        scanf("%d",&a[i].p);//读入优惠价 
    }//才读完优惠方案
    scanf("%d",&nn);//读入需要购买的商品数 
    for (i=1;i<=nn;i++)
    {
        scanf("%d%d%d",&ai,&bi,&ci);//ai：编号,bi:需要数量
        if (d[ai]==0)//此商品没出现过
        {
            t++;
            d[ai]=t;//存编号 
        }
        x[d[ai]]=bi;//需求量。
        n++;//组合数+1
        a[n].n=1;//把零售也当成一种组合存进去
        a[n].k[d[ai]]=1;//数量 
        a[n].p=ci;//价格 
    }
    for (i=0;i<=5;i++)
        for (j=0;j<=5;j++)
            for (k=0;k<=5;k++)
                for (l=0;l<=5;l++) 
                    for (m=0;m<=5;m++)
                    f[i][j][k][l][m]=233333;//只能人工赋初值。 
    f[0][0][0][0][0]=0;//初始化 
    for (z=1;z<=n;z++)//n种方案，嗯，完全背包 
        for (i=a[z].k[1];i<=x[1];i++) 
            for (j=a[z].k[2];j<=x[2];j++) 
                for (k=a[z].k[3];k<=x[3];k++) 
                    for (l=a[z].k[4];l<=x[4];l++) 
                        for (m=a[z].k[5];m<=x[5];m++) 
                        f[i][j][k][l][m]=min(f[i][j][k][l][m],
                        f[i-a[z].k[1]]
                        [j-a[z].k[2]]
                        [k-a[z].k[3]]
                        [l-a[z].k[4]]
                        [m-a[z].k[5]]
                        +a[z].p);//动态转移方程 
    printf("%d\n",f[x[1]][x[2]][x[3]][x[4]][x[5]]);//输出
    return 0;
}
```

---

## 作者：Jsxts_ (赞：4)

# 题解 P2732 商店购物 Shopping Offers
[传送门](https://www.luogu.com.cn/problem/P2732)

这道题因为物品个数 $\le 5$，所以可以想到五维 DP。

我们令 $f[i][j][k][l][o]$ 代表当第一种物品有 $i$ 个，第二种物品有 $j$ 个。。。时的最小花费。

DP 时就枚举每一位，然后先让最小花费为不用任何优惠的钱数，即 $i\times w_1+j\times w_2+k\times w_3+l\times w_4+o\times w_5$，其中 $w_i$ 代表第 $i$ 个物品的原价。

之后就枚举每一种优惠方案，如果可行就转移一次（即当前这类物品数 $\ge$ 优惠套餐中的此类物品个数）。

但是因为题目给的是一个编号，所以要用一个 $id$ 数组记录是第几个物品。

最后输出 $f[v_1][v_2][v_3][v_4][v_5]$ 即可，其中 $v_i$ 代表第 $i$ 个物品的个数。

剩下的一些存变量的细节在注释中体现。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int f[10][10][10][10][10];//状态 
int n,m,cnt;
vector<pair<int,int> > vc[10010];//存优惠方案 
int id[100010],w[10],v[10],t[10],s[10010];//各种值 
int main() {
	scanf("%d",&n);
	for (int i = 1;i <= n;i ++ ) {
		int k;
		scanf("%d",&k);
		for (int j = 1;j <= k;j ++ ) {
			int x,y;
			scanf("%d%d",&x,&y);
			if (!id[x]) id[x] = ++cnt;//存是第几个数，可以是任何顺序 
			vc[i].push_back(make_pair(id[x],y));//存方案 
		}
		scanf("%d",&s[i]);//价格 
	}
	scanf("%d",&m);
	for (int i = 1,x,k,p;i <= m;i ++ ) {
		scanf("%d%d%d",&x,&k,&p);
		if (!id[x]) id[x] = ++cnt;//这里也要再存一遍 
		v[id[x]] = k, w[id[x]] = p;//个数、价钱 
	}
	for (int i = 0;i <= v[1];i ++ ) {
		for (int j = 0;j <= v[2];j ++ ) {
			for (int k = 0;k <= v[3];k ++ ) {
				for (int l = 0;l <= v[4];l ++ ) {
					for (int o = 0;o <= v[5];o ++ ) {//五层枚举 
						f[i][j][k][l][o] = i*w[1]+j*w[2]+k*w[3]+l*w[4]+o*w[5];//没有优惠时 
						for (int I = 1;I <= n;I ++ ) {
							int t[6]={0};
							for (int J = 0;J < vc[I].size();J ++ ) {
								t[vc[I][J].first] = vc[I][J].second;//每种的个数 
							}
							if (i<t[1]||j<t[2]||k<t[3]||l<t[4]||o<t[5]) continue;//是否可行 
							f[i][j][k][l][o] =
							min(f[i][j][k][l][o],f[i-t[1]][j-t[2]][k-t[3]][l-t[4]][o-t[5]]+s[I]);//状态转移 
						}
					}
				}
			}
		}
	}
	printf("%d",f[v[1]][v[2]][v[3]][v[4]][v[5]]);//输出答案 
	return 0;
}
```

Time：58ms（-O2）

---

## 作者：Rocket_raccoon_ (赞：4)

由于动态规划要满足无后效性和最优化原理，所以我们来分析此题是否满足以上两点。首先确定状态，商品不超过5种，而每种采购的数量又不超过5，那么可以用一个5维数组来表示第i种商品买Ai的最小费用:   
```
	F[A1][A2][A3][A4][A5]
```  
考虑这个状态的由来，当然，我们不用优惠商品也可以买，显然这样不是最优。于是如果我们能够使用第i条商品组合Si的话，状态就变为了
```
	F[A1-Si1][A2-Si2][A3-Si3][A4-Si4][A5-Si5]（但是要注意边界）
```  
这样的话，状态1的费用为状态2的费用加上Si的费用，而状态2的费用必须最低（很显然，用反证法可证明），同时我们也不管状态2是如何来的（因为每一个优惠商品的组合的使用是没有限制的），所以本题既满足无后效性，又符合最优化原理，同时还有大量重叠子问题产生，动态规划解决此题再好不过了。   
由于0<=b<=5,1<=k<=5,故可用5x5x5x5x5的DP，又因为每种买0到5个，故可以用6进制表示，5维DP即可    
设 F[b1][b2][b3][b4][b5] 为买b1件物品1......b5件物品5时，需要的最少价格。    
则状态转移方程为
```
	f[b1][b2][b3][b4][b5]=min(f[b1][b2][b3][b4][b5],f[b1-p[i][1]][b2-p[i][2]][b3-p[i][3]][b4-p[i][4]][b5-p[i][5]]+P[i][0]),其中i=1,...,(s+b)且ak-p[i][k]>=0
```
边界条件f[0][0][0][0][0]=0;
代码如下
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
struct lol{
	int c,m;
}s[11];
long long f[11][11][11][11][11];//防止溢出
int sum[110][1010];
int ans,t;

int main(){
	int i,j,k,n,a1,a2,a3,a4,a5,b1,b2,b3,b4,b5;
	cin>>ans;
	for (i=1; i<=ans; i++){
		cin>>n;
		for (j=1; j<=n; j++){
			cin>>k;
			cin>>sum[i][k];
		}
		cin>>sum[i][1001];
	}
	cin>>t;
	for (i=1; i<=t; i++){
		cin>>s[i].c>>s[i].m>>sum[++ans][1001];
		sum[ans][s[i].c]=1;
	}
	memset(f,1,sizeof(f));
	f[0][0][0][0][0]=0;
	for (i=1; i<=ans; i++){
		a1=sum[i][s[1].c];
		a2=sum[i][s[2].c];
		a3=sum[i][s[3].c];
		a4=sum[i][s[4].c];
		a5=sum[i][s[5].c];//赋初值
		for (b1=a1; b1<=s[1].m; b1++){
			for (b2=a2; b2<=s[2].m; b2++){
				for (b3=a3; b3<=s[3].m; b3++){
					for (b4=a4; b4<=s[4].m; b4++){
						for (b5=a5; b5<=s[5].m; b5++){
							f[b1][b2][b3][b4][b5]=min(f[b1][b2][b3][b4][b5],f[b1-a1][b2-a2][b3-a3][b4-a4][b5-a5]+sum[i][1001]);
						}
					}
				}
			}
		}
	}
	
	cout<<f[s[1].m][s[2].m][s[3].m][s[4].m][s[5].m];
	
	return 0;
}
```
码字不易，求过......


---

## 作者：封禁用户 (赞：3)


这道题目，果然不愧是提高+/省选-的题目啊$QWQ$，做了那么多道$USACO$的题目，这是唯一一道让我写出了$3KB$代码的题目。。。

代码很简单，只要模拟一下题目所说的就可以了，时间效率也还行，每个点也就$9ms$吧。

$ps$:千万不要调试这个程序，因为我使用的$6$维数组，一调试$CPU$的温度居然会上升$10$度！

好了，废话不多说，直接上代码吧（这个代码我可用了$1$个多小时才搞定的$QWQ$）
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>//头文件
int s,b,x,y,z,sum[100],a[100][10][2],v[100],small[10],cnt;
int need[5][2],sale[5],f[6][6][6][6][6];
bool bo[6][6][6][6][6];
using namespace std;
int main()
{
	memset(f,0x3f3f3f3f,sizeof(f));//初始化
	scanf("%d",&s);
	for (int i=1;i<=s;i++)
	{
		scanf("%d",&sum[i]);
		for (int j=1;j<=sum[i];j++) 
		{
			scanf("%d",&x);
			bool flag=1;
			int number;
			for (int k=1;k<=cnt;k++)
			  if (small[k]==x)//记录当前这个物品的编号是多少（由于物品个数最多只有5个，我们将其编号为1~5）
			  {
			  	number=k;
			  	flag=0;
			  	break;
			  }
			if (!flag) a[i][j][0]=number; else
			{
				small[++cnt]=x;
				a[i][j][0]=cnt;
			}
			scanf("%d",&a[i][j][1]);
		}
		scanf("%d",&v[i]);
	}
	scanf("%d",&b);
	for (int i=1;i<=b;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		int number=0;
		for (int j=1;j<=cnt;j++)
		  if (small[j]==x)
		  {
		  	number=j;
		  	break;
		  }
		if (number)//因为这里我第一次提交WA了两个点QWQ
		{
			need[i][0]=number;
			need[i][1]=y;
			sale[number]=z;
		} else
		{
			number=++cnt;//注意，即使前面的套餐未出现这个物品，我们也要将其记录至small数组
			small[cnt]=x;
			need[i][0]=number;
			need[i][1]=y;
			sale[number]=z;
		}
	}
	f[0][0][0][0][0]=0;
	bo[0][0][0][0][0]=1;//简单的DP初始化
    //以下的5重循环是计算如果没有套餐的情况下，一个一个买需要多少钱
	for (int i1=0;i1<=5;i1++)
	  for (int i2=0;i2<=5;i2++)
	    for (int i3=0;i3<=5;i3++)
	      for (int i4=0;i4<=5;i4++)
	        for (int i5=0;i5<=5;i5++)
	        {
	        	if (i1==0&&i2==0&&i3==0&&i4==0&&i5==0) continue;
	        	if (i1&&bo[i1-1][i2][i3][i4][i5]&&sale[1]) 
				{
					f[i1][i2][i3][i4][i5]=min(f[i1][i2][i3][i4][i5],f[i1-1][i2][i3][i4][i5]+sale[1]);
					bo[i1][i2][i3][i4][i5]=1;
				}
	        	if (i2&&bo[i1][i2-1][i3][i4][i5]&&sale[2]) 
				{
					f[i1][i2][i3][i4][i5]=min(f[i1][i2][i3][i4][i5],f[i1][i2-1][i3][i4][i5]+sale[2]);
					bo[i1][i2][i3][i4][i5]=1;
				}
	        	if (i3&&bo[i1][i2][i3-1][i4][i5]&&sale[3]) 
				{
					f[i1][i2][i3][i4][i5]=min(f[i1][i2][i3][i4][i5],f[i1][i2][i3-1][i4][i5]+sale[3]);
					bo[i1][i2][i3][i4][i5]=1;
				}
	        	if (i4&&bo[i1][i2][i3][i4-1][i5]&&sale[4]) 
				{
					f[i1][i2][i3][i4][i5]=min(f[i1][i2][i3][i4][i5],f[i1][i2][i3][i4-1][i5]+sale[4]);
					bo[i1][i2][i3][i4][i5]=1;
				}
	        	if (i5&&bo[i1][i2][i3][i4][i5-1]&&sale[5]) 
				{
					f[i1][i2][i3][i4][i5]=min(f[i1][i2][i3][i4][i5],f[i1][i2][i3][i4][i5-1]+sale[5]);
					bo[i1][i2][i3][i4][i5]=1;
				}
	        }
	for (int i=1;i<=s;i++)//这个循环是用来计算如果出现了套餐，应付多少元
	{
		int i1=0,i2=0,i3=0,i4=0,i5=0;
		for (int j=1;j<=sum[i];j++)//判断当前这个套餐各个物品至少需要多少个才能开始DP
		{
			if (a[i][j][0]==1) i1=a[i][j][1];
			if (a[i][j][0]==2) i2=a[i][j][1];
			if (a[i][j][0]==3) i3=a[i][j][1];
			if (a[i][j][0]==4) i4=a[i][j][1];
			if (a[i][j][0]==5) i5=a[i][j][1];
		}
		for (int ii1=i1;ii1<=5;ii1++)
		  for (int ii2=i2;ii2<=5;ii2++)
		    for (int ii3=i3;ii3<=5;ii3++)
		      for (int ii4=i4;ii4<=5;ii4++)
		        for (int ii5=i5;ii5<=5;ii5++)//下面的DP十分的基础，不解释啦
		          f[ii1][ii2][ii3][ii4][ii5]=min(f[ii1][ii2][ii3][ii4][ii5],f[ii1-i1][ii2-i2][ii3-i3][ii4-i4][ii5-i5]+v[i]);
	}
	int i1=0,i2=0,i3=0,i4=0,i5=0;
	for (int j=1;j<=b;j++)
	{
		if (need[j][0]==1) i1=need[j][1];
		if (need[j][0]==2) i2=need[j][1];
		if (need[j][0]==3) i3=need[j][1];
		if (need[j][0]==4) i4=need[j][1];
		if (need[j][0]==5) i5=need[j][1];
	}
	printf("%d\n",f[i1][i2][i3][i4][i5]);
	return 0;```
}

---

## 作者：key_rA9 (赞：3)

## 1851: [USACO3.3]Shopping Offers【商店购物】
这题需要把各种各样的编号变成1~5，然后就可以DP找到需要购买商品的最低价格。因为数据范围小所以不怕爆乱七八糟的东西。
详见代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node//优惠方案 
{//觉得其实好像大概似乎应该貌似可以用 short 吧↓
    int s,t[6],p;//s是方案中含商品个数，t[i]是第i种的数量，p是方案总价 
}a[110];int f[10][10][10][10][10];//每种商品买一定数量的价格 
int m,b,n[6],bk[1100],z;//方案总数,商品总数，每种需要的个数，bk用来改编号，bk已变的个数 
int main()
{
    int x,y,Z;//输入用 
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&a[i].s);
        for(int j=1;j<=a[i].s;j++)
        {
            scanf("%d%d",&x,&y);
            if(!bk[x])bk[x]=++z;//把编号变成1~5 
            a[i].t[bk[x]]=y;//需要的数量 
        }scanf("%d",&a[i].p);//方案价格 
    }
    scanf("%d",&b);
    while(b--)
    {
        scanf("%d%d%d",&x,&y,&Z);//商品信息 
        if(!bk[x])bk[x]=++z;//同上 
        n[bk[x]]=y;
        a[++m].s=1;a[m].t[bk[x]]=1;//数量都为1 
		a[m].p=Z;//把单独买商品记为一种方案↑
    }
    memset(f,127,sizeof(f));
    f[0][0][0][0][0]=0;//初始化 
    for(int k=1;k<=m;k++)//枚举方案 
    for(int i1=a[k].t[1];i1<=n[1];i1++)//枚举 
    for(int i2=a[k].t[2];i2<=n[2];i2++)//商 
    for(int i3=a[k].t[3];i3<=n[3];i3++)//品 
    for(int i4=a[k].t[4];i4<=n[4];i4++)//数 
    for(int i5=a[k].t[5];i5<=n[5];i5++)//量 
    {
    	f[i1][i2][i3][i4][i5]=min(f[i1][i2][i3][i4][i5],
		f[i1-a[k].t[1]] [i2-a[k].t[2]] [i3-a[k].t[3]] [i4-a[k].t[4]] [i5-a[k].t[5]]+a[k].p
		);//直接完全背包 
	}
	printf("%d\n",f[n[1]] [n[2]] [n[3]] [n[4]] [n[5]]);//要求的最终状态 
	return 0;
}
```

---

## 作者：Celebrate (赞：3)

这一道题有着一下几个难点：

（1）物品的编号变化多样：

解法：定义一个bk数组来记录出现过的编号

（2）应该怎么样背包：

解法：我用了完全背包，在前面把原价也看成是一种优惠，其实完全没有必要把它们分

开，然后枚举所有的优惠价，还有每一种商品的所需量，这样五维数组（最多只有五个

物品）暴力竟然过了，很神奇

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node//记录每一种优惠的情况 
{
    int s,k[11],p;
}a[210];int n,len;//优惠的数量 
int bk[1100],cnt;//记录编号的出现状况 
int t1,t2,t3;
int f[11][11][11][11][11];//五维背包 
int v[6];
int main()
{
    int i,j,k,l,r,ki;
    scanf("%d",&len); 
    for(i=1;i<=len;i++)
    {
        scanf("%d",&a[i].s);
        for(j=1;j<=a[i].s;j++)
        {
            scanf("%d%d",&t1,&t2);
            if(bk[t1]==0) bk[t1]=++cnt;//如果没有出现过 
            a[i].k[bk[t1]]=t2;
        }
        scanf("%d",&a[i].p);
    }
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d%d%d",&t1,&t2,&t3);
        if(bk[t1]==0) bk[t1]=++cnt;
        v[bk[t1]]=t2;
        len++;//把原价也设置为优惠 
        a[len].s=1;a[len].k[bk[t1]]=1;a[len].p=t3;
    }
    memset(f,127,sizeof(f));//初始化无限大 
    f[0][0][0][0][0]=0;//表示买第i种物品j个需要的最小价钱 
    for(ki=1;ki<=len;ki++)//枚举优惠的个数 
        for(i=a[ki].k[1];i<=v[1];i++)//完全背包 
            for(j=a[ki].k[2];j<=v[2];j++)//从这一个优惠里这个商品的数量一直到所需量 
                for(k=a[ki].k[3];k<=v[3];k++)
                    for(l=a[ki].k[4];l<=v[4];l++)
                        for(r=a[ki].k[5];r<=v[5];r++)
                            f[i][j][k][l][r]=min(//更新最优值，无需判断一堆的东西，这就是完全背包在这一题的优势 
                            f[i][j][k][l][r],
                            f[i-a[ki].k[1]][j-a[ki].k[2]][k-a[ki].k[3]][l-a[ki].k[4]][r-a[ki].k[5]]+a[ki].p);
    printf("%d\n",f[v[1]][v[2]][v[3]][v[4]][v[5]]);//输出 
    return 0;
}
```

---

## 作者：梦景 (赞：2)

用了个dfs+hash记忆化，没想到一遍过，数据太弱了。。。

```cpp
type    node    = record c , k : longint ; end ;
        arr     = array[1..5] of longint ;
var     f       : array[0..5,0..5,0..5,0..5,0..5] of longint ;
        hash    : array[0..1000] of longint ;
        rebate  : array[0..100,1..5] of node ;
        hold    : array[0..100] of longint ;
        prefer  : array[0..100] of longint ;
        price   : array[0..100] of longint ;
        buy     : array[0..100] of node ;
        cnt , sellnum , buynum : longint ;
procedure       dp (a : arr) ;
var     i , j , tmp , ret
                : longint ;
        b       : arr ;
        flag    : boolean ;
begin
        if (f[a[1]][a[2]][a[3]][a[4]][a[5]] <> -1) then
         exit ;
        ret := 1000000000 ;
        for i := 1 to 5 do
         if (a[i] > 0) then begin
          move (a , b , 20) ;
          dec (b[i]) ;
          dp (b) ;
          tmp := f[b[1]][b[2]][b[3]][b[4]][b[5]] + price[i] ;
          if (tmp < ret) then
           ret := tmp ;
         end ;
        for i := 1 to sellnum do begin
         move (a , b , 20) ;
         flag := true ;
         for j := 1 to hold[i] do begin
          dec (b[rebate[i][j].c] , rebate[i][j].k) ;
          if (b[rebate[i][j].c] < 0) then begin
           flag := false ;
           break ;
          end ;
         end ;
         if (not flag) then
          continue ;
         dp (b) ;
         tmp := f[b[1]][b[2]][b[3]][b[4]][b[5]] + prefer[i] ;
         if (tmp < ret) then
          ret := tmp ;
        end ;
        f[a[1]][a[2]][a[3]][a[4]][a[5]] := ret ;
end ;
procedure       solve ;
var     i , j , n , c , k , p : longint ;
        a       : array[1..5] of longint ;
begin
        cnt := 0 ;
        readln (sellnum) ;
        for i := 1 to sellnum do begin
         read (n) ;
         hold[i] := n ;
         for j := 1 to n do begin
          read (c , k) ;
          if (hash[c] = 0) then begin
           inc (cnt) ;
           hash[c] := cnt ;
          end ;
          c := hash[c] ;
          rebate[i][j].c := c ;
          rebate[i][j].k := k ;
         end ;
         readln (prefer[i]) ;
        end ;
        readln (buynum) ;
        for i := 1 to buynum do begin
         readln (c , k , p) ;
         if (hash[c] = 0) then begin
          inc (cnt) ;
          hash[c] := cnt ;
         end ;
         c := hash[c] ;
         buy[i].c := c ; buy[i].k := k ;
         price[c] := p ;
        end ;
        fillchar (a , sizeof (a) , 0) ;
        for i := 1 to buynum do
         inc (a[buy[i].c] , buy[i].k) ;
        fillchar (f , sizeof (f) , $ff) ;
        f[0][0][0][0][0] := 0 ;
        dp (a) ;
        writeln (f[a[1]][a[2]][a[3]][a[4]][a[5]]) ;
end ;
begin
        solve ;
end .
```
后来看网上题解，发现竟然是dp背包。。。
状态设置：F[a1][a2][a3][a4][a5]为买a1件物品1,a2件物品2,a3件物品3,a4件物品4,a5件物品5时，所需的最少价格

边界条件：F[0][0][0][0][0]=0;

状态转移方程：

F[a1][a2][a3][a4][a5]=min{F[ a1-P[i][1] ][ a2-P[i][2] ][ a3-P[i][3] ][ a4-P[i][4] ][ a5-P[i][5] ]+P[i][0]}

其中i=1..s+b; 且 ak-p[i][k]>=0

(来自nocow)

代码(来自nocow)

 
 
 
 
```cpp
var name:array[1..999] of integer;
    a:array[1..5] of integer;
    sale:array[1..104,0..5] of integer;
    s,b:integer;
procedure init;
  var n,c,k,p,i,j,t:integer;
  begin
    fillchar(name,sizeof(name),0);
    fillchar(sale,sizeof(sale),0);
    t:=0;
    readln(s);
    for i:=1 to s do
      begin
        read(n);
        for j:=1 to n do
          begin
            read(c,k);
            if name[c]=0 then begin t:=t+1; name[c]:=t; end;
            sale[i,name[c]]:=k;
          end;
        readln(sale[i,0]);
      end;
    readln(b);
    for i:=1 to b do
      begin
        readln(c,a[i],p);
        if name[c]=0 then begin t:=t+1; name[c]:=t; end;
        sale[s+i,name[c]]:=1;
        sale[s+i,0]:=p;
      end;
  end;
function min(a,b:integer):integer;
  begin
    if a<b then min:=a else min:=b;
  end;
procedure work;
  var f:array[0..5,0..5,0..5,0..5,0..5] of integer;
      i,j,k,l,m,n:integer;
  begin
    f[0,0,0,0,0]:=0;
    for i:=0 to a[1] do
      for j:=0 to a[2] do
        for k:=0 to a[3] do
          for l:=0 to a[4] do
            for m:=0 to a[5] do
              if i+j+k+l+m<>0 then
                begin
                  f[i,j,k,l,m]:=maxint;
                  for n:=1 to s+b do
                    if (i>=sale[n,1]) and (j>=sale[n,2]) and (k>=sale[n,3]) and (l>=sale[n,4]) and (m>=sale[n,5]) then
                      f[i,j,k,l,m]:=min(f[i,j,k,l,m],f[i-sale[n,1],j-sale[n,2],k-sale[n,3],l-sale[n,4],m-sale[n,5]]+sale[n,0]);
                end;
    writeln(f[a[1],a[2],a[3],a[4],a[5]]);
  end;
begin
  init;
  work;
end.
```

---

## 作者：cszhpdx (赞：1)

题目传送门：[P2732 \[USACO3.3\]商店购物 Shopping Offers](https://www.luogu.com.cn/problem/P2732)

这道题乍一看，压根看不懂，再看，看懂题了，第三眼，发现是动规，冥思苦想了半天想出来一个特别暴力的办法

首先我瞄准了小数据，最多只会有 5 种，所以我决定直接五维 dp 

$f[i][j][k][l][m]$ 表示在第一个物品有 $i$ 个，表示在第二个物品有 $j$ 个，表示在第三个物品有 $k$ 个，表示在第四个物品有 $l$ 个，表示在第五个物品有 $m$ 个，的情况下的最少费用，于是剩下的就是有手就行的完全背包

但是呢我们发现它还有一个烦人的编号，怎么处理呢？

我的处理方法类似离散化，把每一个编号对应一个较小的数，$lsh[i]==0$ 表示当前 $i$ 这个编号第一次出现，那么我们开辟一个新的编号，否则 $lsh[i]$ 就是这个编号对应的更小的数，初始 $lsh$ 里全是 0 ，比如有四个编号：

112 293 112 737

首先看第一个数时新的，于是我们让 $lsh[112]=1$ ，293 是新的，于是 $lsh[293]=2$ ，然后是 112 ，我们发现 $lsh[112] \not= 0$，112 对应的就是 $lsh[112]=1$，解决了，这个数据的问题

剩下的就是代码实现了：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int NR=7, SR=1005;
int s, n[SR], c[SR][NR], k[SR][NR], p[SR];
int b, t[NR], r[NR], a[SR], f[NR][NR][NR][NR][NR];
int lsh[SR], ccnt, tx, ty, tz;
int main()
{
	scanf("%d", &s);
	for(int i=1;i<=s;i++)
	{
		scanf("%d", n+i);
		for(int j=1;j<=n[i];j++)
		{
			scanf("%d%d", &tx, &ty);
			if(!lsh[tx])lsh[tx]=(++ccnt);
			k[i][lsh[tx]]=ty;
		}
		scanf("%d", p+i);
	}
	scanf("%d", &b);
	for(int i=1;i<=b;i++)
	{
		scanf("%d%d%d", &tx, &ty, &tz);
		if(!lsh[tx])lsh[tx]=(++ccnt);
		t[lsh[tx]]=ty;
		r[lsh[tx]]=tz;
	}
	for(int i1=0;i1<=t[1];i1++)
	for(int i2=0;i2<=t[2];i2++)
	for(int i3=0;i3<=t[3];i3++)
	for(int i4=0;i4<=t[4];i4++)
	for(int i5=0;i5<=t[5];i5++)
	{
		f[i1][i2][i3][i4][i5]=r[1]*i1+r[2]*i2+r[3]*i3+r[4]*i4+r[5]*i5;
		for(int i=1;i<=s;i++)
			if(i1>=k[i][1] && i2>=k[i][2] && i3>=k[i][3] && i4>=k[i][4] && i5>=k[i][5])
				f[i1][i2][i3][i4][i5]=min(f[i1][i2][i3][i4][i5], f[i1-k[i][1]]
					[i2-k[i][2]][i3-k[i][3]][i4-k[i][4]][i5-k[i][5]]+p[i]);
	}
	printf("%d", f[t[1]][t[2]][t[3]][t[4]][t[5]]);
    return 0;
}
```

---

## 作者：_l_l_ (赞：1)

[**题目页面**](https://www.luogu.com.cn/problem/P2732)

[**更好的阅读体验**](https://www.luogu.com.cn/blog/yinjun2024/solution-p2732)

这个是一道~~基础的~~高维 DP，我们需要开五维的数组去存储商品的数量

可以单独买，也可以使用完全背包来优惠买。

（有时候你想到了五维的 DP 那就对了）

代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXK = 10;
const int MAXS = 105;
const int MAXB = 10;
const int MAXN = 10;
int dp[MAXK][MAXK][MAXK][MAXK][MAXK];
struct free {
	int num;
	int id;
	bool operator < (const free& sec) const {
		return this->id < sec.id;
	}
} frees[MAXS][MAXN];
int free_price[MAXS];
struct list {
	int num;
	int id;
	int price;
	bool operator < (const list& sec) const {
		return this->id < sec.id;
	}
} item[MAXB];
int main() {
	int s;
	scanf("%d", &s);
	for (int i = 1; i <= s; i++) {
		int n;
		scanf("%d", &n);
		for (int j = 1; j <= n; j++) {
			int c, k;
			scanf("%d %d", &c, &k);
			frees[i][j].num = k;
			frees[i][j].id = c;
		}
		int p;
		scanf("%d", &p);
		free_price[i] = p;
		stable_sort(frees[i] + 1, frees[i] + n + 1);
	}
	int b;
	scanf("%d", &b);
	for (int i = 1; i <= b; i++) {
		int c, k, p;
		scanf("%d %d %d", &c, &k, &p);
		item[i].num = k;
		item[i].id = c;
		item[i].price = p;
	}
	stable_sort(item + 1, item + b + 1);
	memset(dp, 0x7f, sizeof dp);
	dp[0][0][0][0][0] = 0;
	for (int i = 0; i <= item[1].num; i++) {
		for (int j = 0; j <= item[2].num; j++) {
			for (int k = 0; k <= item[3].num; k++) {
				for (int l = 0; l <= item[4].num; l++) {
					for (int m = 0; m <= item[5].num; m++) {
						// printf("\n%d %d %d %d %d", i, j, k, l, m);
						if (i != 0 || j != 0 || k != 0 || l != 0 || m != 0) {
							if (i != 0) {
								dp[i][j][k][l][m] = min(dp[i][j][k][l][m], dp[i - 1][j][k][l][m] + item[1].price);
							}
							if (j != 0) {
								dp[i][j][k][l][m] = min(dp[i][j][k][l][m], dp[i][j - 1][k][l][m] + item[2].price);
							}
							if (k != 0) {
								dp[i][j][k][l][m] = min(dp[i][j][k][l][m], dp[i][j][k - 1][l][m] + item[3].price);
							}
							if (l != 0) {
								dp[i][j][k][l][m] = min(dp[i][j][k][l][m], dp[i][j][k][l - 1][m] + item[4].price);
							}
							if (m != 0) {
								dp[i][j][k][l][m] = min(dp[i][j][k][l][m], dp[i][j][k][l][m - 1] + item[5].price);
							}
							// printf("@");
							for (int n = 1; n <= s; n++) {
								bool flag = true;
								int index = 1;
								int map[MAXB];
								memset(map, 0, sizeof map);
								for (int o = 1; frees[n][o].id; o++) {
									// printf("%d", o);
									while (index <= b && frees[n][o].id != item[index].id) {
										index++;
									}
									if (index > b) {
										flag = false;
										break;
									} else {
										map[index] = o;
										if (frees[n][o].num > (index == 1 ? i : index == 2 ? j : index == 3 ? k : index == 4 ? l : m)) {
											flag = false;
											// printf("@");
											break;
										}
									}
								}
								if (flag) {
									// printf(" ohhh ");
									// printf("%d %d %d %d %d", i - frees[n][map[1]].num, j - frees[n][map[2]].num, k - frees[n][map[3]].num, l - frees[n][map[4]].num, m - frees[n][map[5]].num);
									dp[i][j][k][l][m] = min(dp[i][j][k][l][m], dp[i - frees[n][map[1]].num][j - frees[n][map[2]].num][k - frees[n][map[3]].num][l - frees[n][map[4]].num][m - frees[n][map[5]].num] + free_price[n]);
								}
							}
						}
						// printf("-> %d", dp[i][j][k][l][m]);
					}
				}
			}
		}
	}
	printf("%d", dp[item[1].num][item[2].num][item[3].num][item[4].num][item[5].num]);
	return 0;
}
```

**Update: 代码忘记改了QwQ**

---

## 作者：Durancer (赞：0)

### 前言

一眼看不出来的大水题，正常背包思维去想就行了

### 思路

首先，因为有五个种类，所以要设五维来进行转移。

唯一的一个较难的点就是需要去离散化，因为数据中说了，物品的种类最多就是五种，所以把那些编号较大的都离散化为小的即可。

注意离散化的时候不要和以前的数组弄混了，建议新开一个数组尽心储存离散后的新值。

其余的就是背包板子了，写循环的时候因为是 $5$ 层循环，建议换行，防止写错参数。

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
using namespace std;
const int N=10;
struct node{
	int tot;//总共有多少！ 
	int id[109];//编号 
	int val;//价值
	int num[109];//个数  
	int cnt[109];//离散后的个数 
}a[109]; 
int s,n;//优惠方案数,需要购买的货物种类 
int f[N][N][N][N][N];//美丽的五层DP,表示放...个东西需要的最小价值 
map<int,int> lis;//离散化
int price[N];
int need[N]; 
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar(); }
	return f*x;
}
void Bag_read()
{
	for(int i=1;i<=s;i++)
	{
		a[i].tot=read();
		for(int j=1;j<=a[i].tot;j++)
		{
			a[i].id[j]=read();
			a[i].num[j]=read();
		}
		a[i].val=read();
	}
}
void shop_read()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		int x=read();
		lis[x]=i;//进行离散化
		need[i]=read();
		price[i]=read();	
	} 
}
void prepare()
{
	for(int i=1;i<=s;i++)
		for(int j=1;j<=a[i].tot;j++)
			a[i].cnt[lis[a[i].id[j]]]=a[i].num[j];
			//因为编号过多，但是最终有贡献的只有五个，所以直接离散化了
	for(int s1=0;s1<=need[1];s1++)
		for(int s2=0;s2<=need[2];s2++)
			for(int s3=0;s3<=need[3];s3++)
				for(int s4=0;s4<=need[4];s4++)
					for(int s5=0;s5<=need[5];s5++)
						f[s1][s2][s3][s4][s5]=price[1]*s1+
											  price[2]*s2+
											  price[3]*s3+
											  price[4]*s4+
											  price[5]*s5; 
}
void DP()
{
	for(int i=1;i<=s;i++)
		for(int s1=a[i].cnt[1];s1<=need[1];s1++)
			for(int s2=a[i].cnt[2];s2<=need[2];s2++)
				for(int s3=a[i].cnt[3];s3<=need[3];s3++)
					for(int s4=a[i].cnt[4];s4<=need[4];s4++)
						for(int s5=a[i].cnt[5];s5<=need[5];s5++)
							f[s1][s2][s3][s4][s5]=min(f[s1][s2][s3][s4][s5],
							f[s1-a[i].cnt[1]]
			 				 [s2-a[i].cnt[2]]
			 				 [s3-a[i].cnt[3]]
			 				 [s4-a[i].cnt[4]]
			 				 [s5-a[i].cnt[5]]+a[i].val);	
} 
int main()
{
	s=read();
	Bag_read();
	shop_read();
	prepare();
	DP();
	printf("%d\n",f[need[1]][need[2]][need[3]][need[4]][need[5]]);
	return 0;
}
```

---

