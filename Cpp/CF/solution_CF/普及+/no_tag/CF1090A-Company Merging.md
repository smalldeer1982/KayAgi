# Company Merging

## 题目描述

一个由n(1≤n≤2·10^5)个公司组成的企业，每个公司中有mi(1≤m≤2·10^5)个员工，每个公司员工都有工资(≤10^9)。现在，公司老板想要将这n个公司合并，合并的规则为：保证每个公司的最高工资相等，并且工资只能增不能减，一个公司中的员工的工资必须同时增加相同的钱数。

现在老板想要知道最少增加多少钱的工资可以将这些公司合并。

## 说明/提示

第一家公司工资不变，第二家公司所有人工资加2，变为{4,3}，第三家工资都加3，变为{4,4,4}，共需2+2+3+3+3=13块钱。

## 样例 #1

### 输入

```
3
2 4 3
2 2 1
3 1 1 1
```

### 输出

```
13
```

# 题解

## 作者：BZHZS (赞：2)

[题面传送门](https://www.luogu.com.cn/problem/CF1090A)

~~这道题又是一道水绿题~~

因为 “每个公司的最高工资相等”， 所以为了节省钱，我们应该先找出原来的所有公司中的所有员工的最高工资， 设这个值为 $x$。又因为“工资只能增不能减”， 所以我们应该要让每一个公司的最高工资都达到 $x$， 同时为了省钱， 我们只需要让该公司原本的最高工资刚好达到 $x$ 就可以了。而因为“员工的工资必须同时增加相同的钱数”， 所以在这一个数值的基础上再乘以该公司的人数就是该公司需要花费的最小钱数了。 最后把每个公司花费的最小值都加起来， 就是答案了。 

注意： 本题需要开```long long```。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2*1e5+10;
ll n, ans, maxx, can;//maxx用来统计所有公司在一起的最高工资
ll a[N], sum[N];//a数组用来存储每一个公司原来的最高工资， sum数组来存储人数 

int main() {
	cin >> n;	
	for (ll i=1; i<=n; i++) {
		cin >> sum[i];
		for (int j=1; j<=sum[i]; j++) {
			cin >> can;
			a[i] = max (a[i], can);//计算该公司的最高工资 
		}
		maxx = max (maxx, a[i]);//计算所有公司在一起的最高工资 
	}
	for (ll i=1; i<=n; i++)
		ans = ans + sum[i]*(maxx-a[i]);//按照分析进行累积 
	cout << ans << endl;
    return 0;
}


```



---

## 作者：Graphcity (赞：0)

## 思路

首先可以发现，每家公司合并后增加的工资数只和这两家公司工资 **最多** 的人相关，因为题目里面 “保证每个公司的最高工资相等” 就点出了这个性质。

然后，由于所有公司最终都要合并成一个，那么也就是说，每家公司的工资都应该向工资值最大的公司 “看齐”。不管按照什么顺序合并，最终，每一家公司工资的最高值就是原来的最高值，**增加的工资总量不变**。

依照这两个性质，我们只需要先找到每家公司的人数和工资最高值，再按照工资最高值排序。接着，我们设第 $i$ 家公司的人数为 $a_i$ ，工资最高值为 $b_i$ ，第 $k$ 家公司的工资是所有工资里面最高的，那么第 $i$ 家公司总共需要增加

$$
a_i\times(b_k-b_i)
$$

这么多的工资就行了。

---

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=int(2e5);

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n;
long long ans;
struct Node{int a,b;} k[Maxn+5]; // 存储每家公司的人数和工资最高值
bool operator<(Node x,Node y) {return x.b<y.b;}

int main()
{
    n=read();
    for(register int i=1;i<=n;++i)
    {
        k[i].a=read();
        for(register int j=1;j<=k[i].a;++j)
            k[i].b=max(k[i].b,read());
    }
    sort(k+1,k+n+1); // 排序
    for(register int i=1;i<=n;++i) // 累加答案
        ans=ans+1ll*k[i].a*(k[n].b-k[i].b);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Creator_157 (赞：0)

## 题意
有 $n$ 组数据，每组数据有 $m$ 个数，

可以将  每组数据 的 每一个数 同时 **加上相同的数**     

以使**每组数据的最大值相同**，

求这 $m$ 组数据的总和增加了多少。



------------
## 思路
**暴力出奇迹！**

求每组数据的最大值

进而求出 $m$ 组数据的最大值，

用每组数据的  ~~变化量~~（$m$ 组数据的最大值 $减$ 这组数据的最大值） $*$ 每组数据的个数 可得  每组数据变化的总和，

再将其累加起来即可求解。


------------
## code
（**long long**）

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
long long m,n,ans,k,maxn;
struct node{
    long long ma,num;//ma->这组数据的最大值，num->这组数据的个数
}a[200005];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>m;
        for(int j=1;j<=m;j++)
        {
            cin>>k;
            a[i].ma=max(a[i].ma,k);
        }
        a[i].num=m;
        maxn=max(maxn,a[i].ma);
    }
    for(int i=1;i<=n;i++)
    {
        int h=maxn-a[i].ma;
        ans+=h*a[i].num;
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：周子衡 (赞：0)

思路：模拟

找出全局最大值，分析每个公司，模拟即可

代码：

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

int m[200001]={};
long long maxn[200001]={};
vector<long long> a[200001];

int main()
{
	int n=0;scanf("%d",&n);
	long long all=0;
	for(int i=1;i<=n;i++)
	{
		long long k=0;
		scanf("%d",&m[i]);
		for(int j=1;j<=m[i];j++)
		{
			scanf("%d",&k);
			a[i].push_back((long long)k);
			maxn[i]=max(maxn[i],k);
		}
		all=max(all,maxn[i]);
	}
	long long ans=0;
	for(int i=1;i<=n;i++)ans+=m[i]*(all-maxn[i]);
	printf("%lld",ans);return 0;
}
```

---

## 作者：BCZSX (赞：0)

这题就是一道水题，根据我的方法做，我也不知道为什么没有TLE，我的思路是：因为每个公司的员工的工资是一起上涨的，且每个人上涨的钱数都是一样的，所以每个公司总上涨钱数就是$m_{i}$*(maxsum-$maxn_{i}$)，maxsum代表所有公司的最高工资，$maxn_{i}$代表每个公司的最高工资，最后把每个公司的上涨钱数加起来就是答案了。部分讲解就看代码吧qwq!
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
#define ll long long
struct node
{
    ll maxn,len;//maxn存储最高工资，len存储公司人数
    #define len(x) k[x].len
    #define maxn(x) k[x].maxn
}k[200100];
ll n,m,ans,x,maxsum;//n,m如题所述,maxsum上面说了
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&m);//读入人数
        len(i)=m;
        for(int j=1;j<=m;++j)
        {
            scanf("%lld",&x);
            maxn(i)=max(maxn(i),x);//更新本公司最大工资
        }
        maxsum=max(maxsum,maxn(i));//更新所有公司最大工资
    }
    for(int i=1;i<=n;++i)
    {
        ans+=len(i)*(maxsum-maxn(i));
    }
    printf("%lld",ans);//输出答案
    return 0;
}
```

---

