# Divan and a Store

## 题目描述

给定一个长为 $n$ 的数组 $a$，从中选出若干个在 $[l,r]$ 区间的数，使得总和不大于 $k$。求最多个数。

## 样例 #1

### 输入

```
8
3 1 100 100
50 100 50
6 3 5 10
1 2 3 4 5 6
6 3 5 21
1 2 3 4 5 6
10 50 69 100
20 30 40 77 1 1 12 4 70 10000
3 50 80 30
20 60 70
10 2 7 100
2 2 2 2 2 7 7 7 7 7
4 1000000000 1000000000 1000000000
1000000000 1000000000 1000000000 1000000000
1 1 1 1
1```

### 输出

```
2
2
3
0
0
10
1
1```

# 题解

## 作者：MeowScore (赞：2)

题意很清晰，不再描述了。

采取贪心的思路。

把这些数从小到大排序，用一个变量记录当前选取的数字的总和。然后从左到右考虑这些数，如果当前数在区间 $[l,r]$ 内，且当前数字加上目前已经累计的总和不超过 $k$，就选这个数。

为什么这样是对的呢？选取每个数字对最终答案的贡献都是 $1$，但是选一个更小的数，会使得剩下的数字可选的余地更大了，而不选这个数，去选择一个更大的数，贡献不变，但是总和却更加接近 $k$ 的限制，一定不优。


下面是代码：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1000];
int cmp(int aa,int bb){
	return aa<bb;
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,l,r,k;
		cin>>n>>l>>r>>k;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		sort(a+1,a+n+1,cmp);
		int ans=0,nw=0;
		for(int i=1;i<=n;i++){
			if(a[i]>=l&&a[i]<=r&&nw+a[i]<=k){
				nw+=a[i];
				ans++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}








```

---

## 作者：qwcdim (赞：2)

## CF1614A Divan and a Store题解

[题目传送门](https://www.luogu.com.cn/problem/CF1614A)

[顺便安利一下博客](https://www.luogu.com.cn/blog/I-like-10/)

### 题目大致意思

有人想买巧克力，他有 $k$ 的预算。商店有 $n$ 条不同的巧克力，每条的价格分别是 $a_1 , a_2 , a_3 ,..., a_n $ 如果巧克力的价格**严格低于** $l$ 元或**严格高于** $r$ 元，那么就不会买。让你求出不超过 $k$ 的预算最多能买几条巧克力。

### 关于严格大于和严格小于（会的大佬可以跳过

什么是严格大于呢？

严格大于是指一定要大于某数，比如说严格大于 $5$ 的第一个数是 $6$ ,不可以出现等于的情况。

严格小于也是一样的。

### 题目思路

看完题目你一定可以想到贪心，只需要 $\texttt{sort}$ 一下，再从头到尾遍历一下，把满足条件的数加入 $ans$ ，同时 $cnt$ 加等于 $1$。如果 $ans$ 大于预算时就可以输出 $cnt-1$ ，具体看代码。

### 高清可直接食用代码

```cpp
#include<iostream>
#include<cstdio>
#include<stdio.h>
#include<algorithm>
using namespace std;
int t,a[1010];
int n,l,r,k,ans,cnt;
bool flag;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d",&n,&l,&r,&k);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);//输入 
		}
		sort(a+1,a+n+1);//排序 
		for(int i=1;i<=n;i++){
			if(a[i]>=l&&a[i]<=r){//如果满足条件 
				ans+=a[i];//ans 加上 a[i] 
				cnt++;//条数++ 
			}
			if(ans>k){//如果大于预算 
				printf("%d\n",cnt-1);//因为在此之前cnt++了，而这时的a[i]加上就超了，所以要减1 
				flag=true;//如果输出了就做个记号 
				break;//没有继续的必要，退出 
			}
		}
		if(flag==false) printf("%d\n",cnt),printf("\n");//如果没有输出，那么就是在满足条件的同时，加起来还比预算小 
		else flag=false;
		cnt=ans=0;//“末 始化 
	}
	return 0;
}
```


---

## 作者：small_turtle (赞：1)

一道简单的模拟题。
***
### 大致思路：
首先对 $a$ 数组从小到大排序，再依次判断，若价格大于 $l$ 且小于 $r$，则购买此巧克力棒，否则则钱数不够，直接退出。
***
### CODE：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int t,n,l,r,k,ans,a[111];
int main()
{
    cin >> t;
    while(t--)
    {
        ans=0;
        cin >> n >> l >> r >> k;
        for(int i=1;i<=n;i++)
        {
            cin >> a[i];
        }
        sort(a,a+n+1);
        for(int i=1;i<=n;i++)
        {
            if(a[i]>=l&&a[i]<=r)
            {
                if(a[i]<=k)
                {
                    k-=a[i];
                    //cout << k << ' ';
                    ans++;
                }
                else
                {
                    break;
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}

```

---

## 作者：qwq___qaq (赞：1)

### 题意
某人想买巧克力，但他只会要价格在 $[l,r]$ 这个区间的巧克力，现在已知第 $i$ 个巧克力的价格为 $a_i$，求最多巧克力的数量。
### 思路
首先，为了使价格最多，我们可以看出这是一个“最优选择问题”。所以，我们可以先选价格低的，再选价格高的，这样就保证了数量最多。然后我们只需要选择 $[l,r]$ 范围内即可。如果当前价格 $>r$ 或者加上它之后就 $>k$，那么可以直接 `break` 优化循环，因为后面比它更贵，瓶颈在排序，时间复杂度 $O(n\log n)$。
### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,l,r,k,a[105];
int main(){
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		int ans=0,sum=0;
		scanf("%d%d%d%d",&n,&l,&r,&k);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)
			if(a[i]<=r&&a[i]>=l&&sum+a[i]<=k){
				sum+=a[i];
    				ans++;
    		} else if(a[i]>r||sum+a[i]>k)
    			break;
    	printf("%d\n",ans);
    }
    return 0;
} 
```

---

## 作者：orz_z (赞：0)

## 题目大意

有 $n$ 个物品，第 $i$ 个商品的价格为 $a_i$。

给你 $l$ 和 $r$，表示商人只会选择价格在 $[l,r]$ 内的物品。

商人有 $k$ 元钱，问你商人最多可以买多少个商品。

共 $T$ 组数据。

对于 $100\%$ 的数据，保证 $1\leq T \leq 100,1 \leq n \leq 100,1 \leq l \leq r \leq 10^9,1 \ leq k \leq  10^9,1 \leq a_i \leq 10^9$。

## 解题思路

贪心，每次买剩下的价格最小的商品。

首先选出满足条件的物品，放到优先队列里（最小值优先）。

然后一件一件弹出来，计算钱数，若钱数 $> k$ 或队列为空，结束程序。

时间复杂度 $\mathcal O(Tn \log n)$。

## CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

int t;

int n, l, r, k;

signed main()
{
    scanf("%lld", &t);
    while (t--)
    {
        scanf("%lld%lld%lld%lld", &n, &l, &r, &k);
        priority_queue<int, vector<int>, greater<int>> q;
        for (int i = 1, a; i <= n; ++i)
        {
            scanf("%lld", &a);
            if (a < l || a > r)
                continue;
            q.push(a);
        }
        int ans = 0, sum = 0;
        while (!q.empty())
        {
            int now = q.top();
            q.pop();
            sum += now;
            // cout << now << "\n";
            if (sum <= k)
                ans++;
            else
                break;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：Violet___Evergarden (赞：0)

# CF1614A题解
[希望更好地阅读？](https://www.luogu.com.cn/blog/chairmanZhangjvruo/solution-cf1614a)

由于 $n \leq 100$，可以直接暴力将数组排序，开一个 $sum$ 记录已经选的数字的和，$ans$ 记录答案。**对于能选的数从小到大贪心去选**，如果 $sum + a_i \leq k$就代表能选，此时 $sum \gets sum+a_i$，$ans \gets ans+1$。
```cpp
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
int t,n,l,r,k,a[101];
signed main()
{
cin>>t;
while(t--)
{
  cin>>n>>l>>r>>k;
  for(int i=1;i<=n;i++)cin>>a[i];
  sort(a+1,a+n+1);
  int sum=0,ans=0;
  for(int i=1;i<=n;i++)
  {
    if(a[i]<l)continue;
    if(a[i]>r)break;
    sum+=a[i];
    if(sum<=k)ans++;
    else break;
  }
  cout<<ans<<"\n";
}
return 0;
}
```

---

## 作者：IYSY2009I (赞：0)

#### [CF1614A Divan and a Store](https://www.luogu.com.cn/problem/CF1614A)

先说一下本人对这道题的看法。

这道题应该是一道红题的水平，标签大概是“排序”“贪心”。

下面贴一下我提交的翻译，在洛谷翻译没出来之前大家可以凑合着看：

题目描述

商人 Divan 十分喜欢巧克力! 今天他来到了商店想要买一些巧克力。如同所有商人一样, Divan 知道钱的重要性， 所以他不会买太贵的巧克力。同时，太便宜的巧克力口感不好， 所以他也不会买。

他来到的这个商店有 $n$ 个不同种类的巧克力，第 $i$ 种巧克力的价格为 $a_i$ 美元。 Divan 认为，如果一块巧克力的费用严格超过了 $r$ 美元，那么这块巧克力就太贵了。同样的，如果一块巧克力的费用严格低于了 $l$ 美元，那么这块巧克力就太便宜了。Divan 不会买太贵或者太便宜的巧克力。

Divan 不准备把所有的钱都花费在买巧克力上，所以他做多会花 $k$ 美元在购买巧克力上。

请算出 Divan 最多能买多少块巧克力。

输入格式

每个测试点包含多个测试数据。第一行包含测试数据的数量 $t ( 1 \le t \le 1001≤t≤100 )$。下面是每个测试数据的内容。

每个测试数据都会被描述两行。第一行有整数$n,l,r,k, ( 1 \le n \le 100, 1 \le l \le r \le 10^9, 1 \le k \le 10^9) $ ——分别为巧克力的最低可以接受价格，最高可以接受价格 和 Divan 的总预算.

第二行一个整数序列 $a_1, a_2, \ldots, a_n ( 1 \le a_i \le 10^9)$ ——这些巧克力在商店里的价格。

输出格式

对于每一个测试数据，输出一个整数 ——Divan 最多能买多少块巧克力。

说明/提示

在第一个例子中 Divan 可以花费 $100$ 美元 购买 $1$ 号和 $3$ 号巧克力 。

在第二个例子中 Divan 可以花费 $7$ 美元 购买 $3$ 号和 $4$ 号巧克力 。

在第二个例子中 Divan 可以花费 $12$ 美元 购买 $3$ 号、$4$ 号和 $5$ 号巧克力 。

在第四个例子中，这些巧克力要么太贵了，要么太便宜了， Divan 不能买任何巧克力。

在第五个例子中， Divan 不能买任何巧克力 因为他认为一号巧克力太贵了, 同时他的预算也不够买二号和三号巧克力。

在第六个例子中， Divan 可以买下商店里所有的巧克力。

##### 思路

首先我们可以看到， Divan 只会买价格为 $\left[l,r\right]$ 的巧克力，所以我们要先将这个数组 $a$ 排序。

紧接着，我们思考一下，为了买到更多的巧克力， Divan 买的巧克力价格一定要尽可能的低，所以我们要从低往高枚举，凡是可以买的我们就买下了，知道不能再买任何巧克力位置（也就是说当前无法再购买任何  $\left[l,r\right]$ 的巧克力或者已经买完）。

那么我们就可以愉快地给出我们的代码了：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm> 
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
bool cmp(int x,int y){
	return x<y;
}
void cf(){
	int a[105];
	int n=read(),l=read(),r=read(),k=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	sort(a+1,a+n+1,cmp);
	int ans=0; //最终答案 
	int jia_ge=0; //当前已经购买的巧克力价格 
	for(int i=1;i<=n;i++){
		if(a[i]<l) continue; //这里也可以直接二分寻找比不小于 l 且价格最低的巧克力 
		if(a[i]>r) break;
		if(jia_ge+a[i]>k) break;
		ans++;
		jia_ge+=a[i];
	}
	printf("%d\n",ans);
	return;
}
int main(){
	int t=read();
	for(int i=1;i<=t;i++)
		cf();
	return 0;
}
```

> Please don't copy mine.Try youself.

---

## 作者：shiranui (赞：0)

## 题目描述

商人 Divan 去了一家商店购买巧克力。他不会买太贵的巧克力也不会买太便宜的巧克力。

他光临的商店有 $n$ 块不同的巧克力，其中购买第 $i$ 块巧克力需要 $a_i$ 美元。Divan 只会购买符合 $l≤ a_i ≤r$ 的巧克力。

请你告诉他在不超过预算 $k$ 的情况下，最多能买多少巧克力。

## 思路
不符合条件的巧克力不用考虑。

为了能买更多的巧克力，肯定要从最便宜的能买的巧克力下手。

我们开一个小根堆，把所有能买的巧克力丢进去，再一个一个买，买到没钱或者没货就行了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,l,r,k;
priority_queue <int, vector <int> ,greater<int> > q; 
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		while(!q.empty())q.pop();
		scanf("%d %d %d %d",&n,&l,&r,&k);
		int ans=0;
		int a;
		for(int i=1;i<=n;i++)
		{
			cin>>a;
			if(a>=l&&a<=r)q.push(a);
		}
		while(!q.empty())
		{
			k-=q.top();
			if(k<0)break;
			ans++;
			q.pop();
		}
		printf("%d\n",ans);
	}
	return 0;
}

```

## 结语

这题真的简单，很快就能过。

像我这种 T1 都能吃罚时的蒟蒻也没谁了……

祝你过题愉快。

---

## 作者：BootsH (赞：0)

简单贪心题。

## 思路

先将 $a$ 数组从小到大排序。

对于每个 $a_{i}$，若 $a_{i} < l$ 或者 $a_{i} > r$ 则可以直接忽略。

对于满足 $l \leq a_{i} \leq r$ 的最小的 $a_{i}$，我们就买这个物品（显然，要使得买的巧克力最多，我们要尽量买便宜的巧克力）。那么，还剩的钱要减去这个巧克力的价格。即 

```cpp
k -= a[i];
```

即可。

当目前的 $k < a_{i}$ 时，不论是否有 $l \leq a_{i} \leq r$，都不能买到（因为钱不够）。此时直接 

```cpp
break;
```

即可。

最后输出买到巧克力的个数。

## 代码

快读快写操作等略，见 [这里](https://www.luogu.com.cn/paste/57w4pqr0)

注意结果要开 `long long`。

```cpp
#include <algorithm>

namespace Solution
{
    std::ifstream cin; 
    std::ofstream cout;
    using namespace AKA;
    using IO::gc; using IO::pc; 
    using IO::iget; using IO::ipr; using IO::iwsp; using IO::iwln;
    using IO::llget; using IO::llpr; using IO::llwsp; using IO::llwln;
    using IO::ullget; using IO::ullwsp; using IO::ullwln;
    using IO::spr; using IO::swsp; using IO::swln;
    using IO::pr; using IO::wsp; 


    constexpr int maxn = 10005;

    ll a[maxn];

    void real_main()
    {
        int n, l, r; 
        ll k;
        iget(n, l, r, k);
        for (int i = 1; i <= n; ++i)
        {
            a[i] = iget();
        }
        std::sort(a + 1, a + n + 1);
        ll sum = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (a[i] > k)
            {
                break;
            }
            if (a[i] < l)
            {
                continue;
            }
            if (a[i] > r)
            {
                continue;
            }
            ++sum;
            k -= a[i];
        }
        llwln(sum);
    }


    void main(void)
    {
        std::ios::sync_with_stdio(false);
        #ifndef ONLINE_JUDGE
            cin.open("A.in"), cout.open("A.out");
            IO::inbuf = cin.rdbuf(); IO::outbuf = cout.rdbuf();
        #else
            using std::cin; using std::cout;
            #if __cplusplus >= 201103L
                cin.tie(nullptr); cout.tie(nullptr);
            #else
                cin.tie(NULL); cout.tie(NULL);
            #endif
            IO::inbuf = cin.rdbuf(); IO::outbuf = cout.rdbuf();
        #endif


        int t = iget();
        while (t--)
        {
            real_main();
        }


        #ifndef ONLINE_JUDGE
            cin.close(); cout.close();
        #endif
    }
} // namespace Solution

```

---

## 作者：heaksicn (赞：0)

## 1 题意
有 $n$ 颗糖果， divan 有 $m$ 元钱。他不会买价格小于 $l$ 或者大于 $r$ 元的糖果。他也不希望总花费大于 $m$ 。  
问最多能买几颗糖。
## 2 思路
考虑贪心。  
先将所有的糖果价格从小到大排序。  
枚举一遍，对于第 $i$ 颗糖，如果 $a_i<l$ 或者 $a_i>r$ ，都直接跳过。  
否则尽量选择价格低的糖果即可。  
时间复杂度 $O(Tn)$ 。
## 3 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,l,r;
int a[101];
int main(){
	cin>>T;
	while(T--){
		cin>>n>>l>>r>>m;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+n+1);//从小到大排序
		int now=0,ans=0;//now为当前总花费，ans为答案
		for(int i=1;i<=n;i++){
			if(a[i]<l||a[i]>r) continue;//不符合要求
			if(now+a[i]<=m){//还可以选
				now+=a[i];
				ans++;
			}
		}
		cout<<ans<<endl;//输出
	}
    return 0;
}
```


---

## 作者：TY_OI_hyn (赞：0)

这道题就是一道模拟，贪心题。是商人能购买到足够多的巧克力棒，然而商人很~~吝啬~~有头脑，只要买 l~r元之间的巧克力棒。所以由题意可得我们可以把能买到的巧克力棒寻找出来，从小到大排序一遍，让商人从小到大买，如果再买的时候没有钱了就输出计数器。如果买完了也还有剩余的钱也不用做多的处理，直接跳出循环。暴力即可 _AC_ 。 

**代码**

```cpp
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
ll n,l,k,r,x,t;//一定要用long long 
int ans;
int a[10001];
int main(){
	cin>>t;
	while(t--){
		ans=0;
		cin>>n>>l>>r>>k;
		for(int i=1;i<=n;i++){
			cin>>x;
			if(x>r||x<l) a[i]=-1;//大于或小于规定钱数则标记为-1 
			else a[i]=x;//存储可以买的巧克力棒的数值 
		}
		sort(a+1,a+n+1);//贪心，从小到大排序 
		for(int i=1;i<=n;i++){
			if(a[i]==-1)continue;//为-1则跳过 
			k-=a[i];//减去钱数 
			if(k>=0) ans++;//钱数大于0是计数器累加 
		}	
		cout<<ans<<endl;
	}
}
```
就这样子咯！！！

---

