# Cartons of milk

## 题目描述

Olya likes milk very much. She drinks $ k $ cartons of milk each day if she has at least $ k $ and drinks all of them if she doesn't. But there's an issue — expiration dates. Each carton has a date after which you can't drink it (you still can drink it exactly at the date written on the carton). Due to this, if Olya's fridge contains a carton past its expiry date, she throws it away.

Olya hates throwing out cartons, so when she drinks a carton, she chooses the one which expires the fastest. It's easy to understand that this strategy minimizes the amount of cartons thrown out and lets her avoid it if it's even possible.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767D/609b94e7f0b8a5d407df0e97345c78713f56ad66.png)Milk. Best before: 20.02.2017.The main issue Olya has is the one of buying new cartons. Currently, there are $ n $ cartons of milk in Olya's fridge, for each one an expiration date is known (how soon does it expire, measured in days). In the shop that Olya visited there are $ m $ cartons, and the expiration date is known for each of those cartons as well.

Find the maximum number of cartons Olya can buy so that she wouldn't have to throw away any cartons. Assume that Olya drank no cartons today.

## 说明/提示

In the first example $ k=2 $ and Olya has three cartons with expiry dates $ 0 $ , $ 1 $ and $ 1 $ (they expire today, tomorrow and tomorrow), and the shop has $ 3 $ cartons with expiry date $ 0 $ and $ 3 $ cartons with expiry date $ 2 $ . Olya can buy three cartons, for example, one with the expiry date $ 0 $ and two with expiry date $ 2 $ .

In the second example all three cartons Olya owns expire today and it means she would have to throw packets away regardless of whether she buys an extra one or not.

In the third example Olya would drink $ k=2 $ cartons today (one she alreay has in her fridge and one from the shop) and the remaining one tomorrow.

## 样例 #1

### 输入

```
3 6 2
1 0 1
2 0 2 0 0 2
```

### 输出

```
3
1 2 3```

## 样例 #2

### 输入

```
3 1 2
0 0 0
1
```

### 输出

```
-1```

## 样例 #3

### 输入

```
2 1 2
0 1
0
```

### 输出

```
1
1 ```

# 题解

## 作者：Serve (赞：5)

[题目传送鸡](https://www.luogu.org/problemnew/show/CF767D)

~~之前的格式太丑了~~
### 题目思路
------------
- 这应该是一篇正解啦。
- 首先，我要开一个home数组记录每一天**家里**有哪些牛奶到期

- 接着我们要从后往前遍历，比较第i天**家里**到期牛奶数量与k，如果数量大于k，那么就要把这home[i]-k放到前一天去喝掉，如果数量小于k 那么这一天就会有k-home[i]个剩余可以用来买超市牛奶，开一个spare数组记录这一天还可以喝多少牛奶
- 如果到了第0天仍有超过k的牛奶要喝完，那么情况就不成立，直接输出-1

- 那么为什么要从后往前遍历呢？从前往后遍历的话，是不知道后面有多少牛奶是要提前喝掉的。而从后往前遍历的话，因为前面牛奶已经到了保质期，所以前面的牛奶不会对后面造成影响。

- 最后我们要处理超市牛奶，首先将**超市**牛奶按从小到大的保质期排序，接着从前往后遍历spare数组，如果第i天有空余，那么筛去**超市**已过期的牛奶，把能喝的牛奶加入answer中最后输出就好啦
### 以下代码
------------
```cpp
#include<cstdio>//码风凑合看吧QAQ
#include<iostream>
#include<algorithm>
#define N 10000050
using namespace std;
struct node
{
	int num;//在输入中是第几个
	int t;//到期日
	}market[N];//超市牛奶
int cmp(struct node a,struct node b)
{
	if(a.t!=b.t)
	return a.t<b.t;
	else
	return a.num<b.num;
	}//比较函数
int home[N],answer[N],spare[N];//见解析
int main()
{
	int i,t,n,m,k,maxt=0,sum=0,now=1,q=0;
	scanf("%d%d%d",&n,&m,&k);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&t);
		maxt=max(maxt,t);//maxt记录保质期最大是多少天
        home[t]++;//家里有多少牛奶这一天到期		
		}
	for(i=1;i<=m;i++)
    {
		scanf("%d",&market[i].t);
		market[i].num=i;
		maxt=max(maxt,market[i].t);
		}
	sort(market+1,market+m+1,cmp);
	for(i=maxt;i>=0;i--)//注意从后往前遍历
	{
		if(home[i]<=k)//如果这一天家里要解决的数量小于k
		spare[i]=k-home[i];//这一天还可以喝多少瓶
		else
		{
	    if(i==0)//到了第0天还有超过k的牛奶要解决
	    {
		printf("-1");
        return 0;
	 	}
	 	home[i-1]+=home[i]-k;//前一天要解决的数量要加上今天没解决完的数量
		}
		}
		for(i=0;i<=maxt;i++)
		{
		if(spare[i]>0)//如果可以买
		{
		while(market[now].t<i&&now<=m)
		now++;//筛去已经到保质期的
		while(spare[i]>0&&now<=m)//将能加的都加上
		{
		answer[++q]=market[now].num;
		spare[i]--;
		now++;
		}
		} 
		}
		sort(answer+1,answer+1+q);//把答案按照输入数据排序
		printf("%d\n",q); 
		for(i=1;i<=q;i++)
		printf("%d ",answer[i]); 
	}
```

---

## 作者：封禁用户 (赞：3)

# 1.前言
- 题目链接：http://codeforces.com/contest/767/problem/D

- 题目大意：

小红很喜欢喝牛奶，每天最多能喝 $k$ 瓶牛奶；
小红有 $n$ 瓶牛奶，每瓶牛奶都有一个有效时间 $f[i]$，表示需要在 $f[i]$ 天内喝完。

同时商店里有 $m$ 瓶牛奶，每瓶牛奶的有效时间是 $g[i]$。

小红很讨厌浪费，所以她希望能全部喝完自己的牛奶；同时小红很喜欢牛奶，她希望尽可能喝更多的牛奶。

问小红最多能买多少瓶牛奶，保证牛奶都在保质期内喝完。
 
# 2.解析：
小红必须是先满足喝完自己的牛奶，再去喝商店里的牛奶。小红应该每天尽可能喝有效时间最短的牛奶，并且每天都喝 $k$ 瓶。

### 做法：
把小红所有的牛奶排序，按照有效时间从小到大遍历每瓶牛奶，可以容易判断小红自己的牛奶是否能全部喝完。
 
再来考虑商店里的牛奶：假如小红能喝完数量为 $i+1$ 瓶的牛奶，那么必然能喝完 $i$ 瓶牛奶，具有单调性。

二分 $mid$，表示小红能喝完 $mid$ 瓶商店里的牛奶；
再用贪心，从商店里选择 $mid$ 瓶有效时间最长的牛奶，混入小红必须喝完的列表，然后排序。
 
总得复杂度 $O(\log MN\log N)$，但因为 $N=10^6$，加上 $\log M$ 和 $\log N$，大概有 $4\times 10^8$的复杂度；
 
于是在二分完 $mid$ 之后，不与小红已有的牛奶混合排序，用 two pointers 的方法进行判断。
 
 
# 3.核心代码
~~你可以选择加上头文件啥的来抄题解~~

```cpp
struct Node {
    int first, second;

    bool operator<(const Node &tmp) const
    {
        if (first != tmp.first) return first > tmp.first;
        else return second < tmp.second;
    };
    Node(int first, int second):first(first), second(second){};
    Node(){};
}f[N], g[N];
int a[N];
int main(){
    lld n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &f[i].first);
        f[i].second = i;
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &g[i].first);
        g[i].second = i;
    }
    sort(f + 1, f + 1 + n);
    sort(g + 1, g + 1 + m);
    
    int left = 0, right = m + 1, ans = -1;
    while (left < right) {
        int mid = (left + right) / 2;
        int ok = 1;
        int sum = 0, x = n, y = mid;
        while (x > 0 || y > 0) {
            ++sum;
            int day = 0;
            if (x == 0) { // left y
                day = g[y].first;
                --y;
            }
            else if (y == 0) {
                day = f[x].first;
                --x;
            }
            else {
                if (f[x].first < g[y].first) {
                    day = f[x].first;
                    --x;
                }
                else {
                    day = g[y].first;
                    --y;
                }
            }
            if (sum > (day + 1) * k) {
                ok = 0;
                break;
            }
        }
        
        if (ok) {
            ans = mid;
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }
    
    cout << ans << endl;
    for (int i = 1; i <= ans; ++i) printf("%d ", g[i].second);
    
    
    return 0;
}
```

参考资料：程序员进阶练习

---

## 作者：chlchl (赞：1)

简单题，一眼秒。

## Solution
首先，显然买的牛奶保质期越长越容易成功喝完，因此答案一定是买保质期最长的那几盒牛奶。

发现正着做不好做。可以知道，若购买 $x$ 瓶牛奶的情况下可以喝完，那么购买 $[1,x-1]$ 瓶牛奶也一定能喝完，答案具有单调性。

考虑二分答案 $x$，检验若购买保质期最长的 $x$ 瓶牛奶，能不能成功喝完。

检验的时候简单粗暴地模拟每天喝哪 $k$ 瓶（挑保质期最短的 $k$ 瓶喝），但是时间不允许我们在每次检查的时候都把家里的和买来的牛奶放在一起重新排序。

解决方法也不难，输入完后分别按保质期升序排序，检查的时候**双指针**，每次取保质期较小的那瓶牛奶即可。具体可以看代码。

双指针复杂度是 $O(n+m)$ 的，总时间复杂度 $O\big((n+m)\log m\big)$。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int n, k, m, lim[N];
struct milk{
	int day, id;
	bool operator < (const milk &p) const {
		return day < p.day;
	}
} a[N];

bool check(int x){
	int day = 0, s = 1, t = m - x + 1;//显然是买保质期最大的 x 盒牛奶 
	while(s <= n || t <= m){
		for(int i=1;i<=k;i++){
			int mn = min(lim[s], a[t].day);
			if(mn < day)
				return 0;
			if(s <= n && lim[s] <= a[t].day)
				++s;
			else
				t = min(t + 1, m + 1);
			if(s > n && t > m)
				return 1;
		}
		++day;
	}
	return 1;
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	for(int i=1;i<=n;i++)
		scanf("%d", &lim[i]);
	for(int i=1;i<=m;i++)
		scanf("%d", &a[i].day), a[i].id = i;
	sort(lim + 1, lim + 1 + n);
	sort(a + 1, a + 1 + m);
	lim[n + 1] = a[m + 1].day = 2e9;
	int l = 0, r = m, ans = -1;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(check(mid))
			ans = mid, l = mid + 1;
		else
			r = mid - 1;
	}
	printf("%d\n", ans);
	for(int i=m-ans+1;i<=m;i++)
		printf("%d ", a[i].id);
	return 0;
}
```

---

## 作者：Fuko_Ibuki (赞：1)

```cpp
/*
先说一句吧.这个算法虽然能A这道题,但是实际上随便找几个数据就可以hack掉它.
首先建一个桶存放保质期到第i天的牛奶的瓶数.然后把`tong[i]=k-tong[i]`,求出每一天还能再喝多少瓶牛奶.这里就可以看到这个算法的问题所在,它没有考虑今天把明天的份喝掉,而在看到负数之后直接输出了-1.但是这么明显的错误居然没有数据能够hack掉它,我也是觉得不可思议.
接下来把超市里的牛奶的保质期和编号放在一个pair里并排序.
然后进行暴力.注意p这个变量在代码当中的运用,如果直接暴力就gg了.
由于我很久以前写的代码实在是太丑了,所以我改了一下,好看多了.
重要的事情要说三遍!!!这个代码虽然A掉了,但不是正解!
*/
#include<bits/stdc++.h>
using namespace std;
const int boss=1e6;
pair<int,int> sm[boss+10];
int n,m,k,tong[boss*10+10],sc[boss+10];
int main()
{
int a,i,j,t=0,p=0;//t是ans,p是目前枚举到的第一个不是0的日子(前面的日子已经全部分给了一些牛奶,即对于任何小于p的自然数x来说,都有tong[x]=0).
scanf("%d%d%d",&n,&m,&k);
for (i=1;i<=n;i++) scanf("%d",&a),tong[a]++;
for (i=0;i<=boss*10;i++) if ((tong[i]=k-tong[i])<0) return puts("-1"),0;//当天喝当天的牛奶,如果不能直接输出-1.
for (i=1;i<=m;i++) scanf("%d",&sm[i].first),sm[i].second=i;//构造pair并排序
sort(sm+1,sm+m+1);
for (i=1;i<=m;i++)//枚举每一瓶超市里的牛奶
  {
  for (j=p;j<=sm[i].first;j++) if (tong[j])//贪心从早开始选择,如果能买的话就买,可以在第j天喝掉它
    {
    if (--tong[j]==0) for (;!tong[p];++p);//如果这一天的k瓶已经预定完了,将p往后扫,直到tong[p]>0,可以保证之前不可能再购买任何一瓶牛奶.
    sc[++t]=sm[i].second;
    break;
    }
  }
printf("%d\n",t);
for (i=1;i<=t;i++) printf("%d ",sc[i]);
}
```

---

