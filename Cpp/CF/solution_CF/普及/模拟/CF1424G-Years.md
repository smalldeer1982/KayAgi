# Years

## 题目描述

During one of the space missions, humans have found an evidence of previous life at one of the planets. They were lucky enough to find a book with birth and death years of each individual that had been living at this planet. What's interesting is that these years are in the range $ (1, 10^9) $ ! Therefore, the planet was named Longlifer.

In order to learn more about Longlifer's previous population, scientists need to determine the year with maximum number of individuals that were alive, as well as the number of alive individuals in that year. Your task is to help scientists solve this problem!

## 说明/提示

You can assume that an individual living from $ b $ to $ d $ has been born at the beginning of $ b $ and died at the beginning of $ d $ , and therefore living for $ d $ - $ b $ years.

## 样例 #1

### 输入

```
3
1 5
2 4
5 6```

### 输出

```
2 2```

## 样例 #2

### 输入

```
4
3 4
4 5
4 6
8 10```

### 输出

```
4 2```

# 题解

## 作者：lngqb (赞：2)

看完题目，想到差分，但是一看数据范围，发现1e9，直接差分肯定不行的，会MLE，于是STL大法好，用了个map就行了
[AC记录](https://www.luogu.com.cn/record/41849979)
```c
#include<bits/stdc++.h>
using namespace std;
map<int,int> c;
int main()
{
	int n;
	int a,b;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b;
		c[a]++;
		c[b]--;
	}
	int ans=0,pos,max=-1;
	for(map<int,int>::iterator it=c.begin();it!=c.end();it++)
	{
		ans+=it->second;
		if(ans>max)
		{
			max=ans;
			pos=it->first;
		}
	}
	cout<<pos<<" "<<max;
}
```


---

## 作者：是个汉子 (赞：2)

### 题意

有 $n$ 个区间，找到一个点使得所包含的区间最多

### Solution

这种题的解法多式多样，比如区间右端点排序，差分数组，线段树区间加+单点查询

我们这里用到的是差分数组，在从左到右扫一遍的过程中维护最大值和 $pos$ 。

但是需要注意的是，区间最大会到 $10^9$ ，直接差分是不行的，我们需要先对所有 $b$ 和 $d$ 进行离散化，然后再去差分。

### 代码

```c++
#include<bits/stdc++.h>

using namespace std;
const int N=5e5+10,INF=1e9;
int n,ans,sum,pos,cnt,tot,a[N],l[N],r[N],b[N],c[N];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

int main(){
    n=read();
    for(int i=1;i<=n;i++){
        l[i]=read();
        r[i]=read();
        a[++cnt]=l[i];
        a[++cnt]=r[i];
    }
    sort(a+1,a+cnt+1);
    for(int i=1;i<=cnt;i++)
        if(i==1||a[i]!=a[i-1]) a[++tot]=a[i];
    int t1,t2;
    for(int i=1;i<=n;i++){
        t1=lower_bound(a+1,a+tot+1,l[i])-a;
        t2=lower_bound(a+1,a+tot+1,r[i])-a;
        c[t1]=l[i],c[t2]=r[i];//记录本来的位置
        b[t1]++,b[t2]--;
    }
    for(int i=1;i<=tot;i++){
        sum+=b[i];
        if(sum>ans) ans=sum,pos=c[i];
    }
    printf("%d %d\n",pos,ans);
    return 0;
}
```



---

## 作者：RioFutaba (赞：1)

# 题意
有 $N$ 个人，第 $i$ 个人的在世的年份是 $b_i$ 到 $d_i-1$ 年，问哪一年在世的人最多。

数据范围：$1 \le N \le 10^5$，$1 \le b_i \le d_i \le 10^9$

# 思路
这题很容易想到使用差分，开一个 cnt 数组进行统计。

但是 $d_i \le 10^9$，所以单纯的使用数组空间会爆炸。

那么使用 map 就可以避免这个问题。

最后按照差分思路统计答案即可。

代码：
```cpp
#include <cstdio>
#include <map>
using namespace std;

map<int,int> cnt;//核心差分数组
int n,sum,ans,ac;//ans为答案年份，ac为答案人数
int main(){
	scanf("%d",&n);
	while(n--){
		int b,d;scanf("%d %d",&b,&d);//输入
		cnt[b]++;
		cnt[d]--;//注意不是cnt[d+1]
	}
	map<int,int>::iterator i;
	for(i=cnt.begin();i!=cnt.end();i++){
		sum+=i->second;//经典差分
		if(sum>ac){
			ans=i->first;
			ac=sum;
			//更新答案
		}
	}
	printf("%d %d",ans,ac);//输出答案
	return 0;
}
```

---

## 作者：Aoharu_shiroko (赞：1)

# 0x00 题目概述
 给你 $n$ 个数 $(1\le N \le 10^5)$ ，表示为 $n$ 个人。 在输入每个人生死时期即 $b$ 和 $d$ $(1 \le b,d \le 10^9)$，求哪一年的**在世人数最多，且输出在世人数。**

# 0x01 思路

~~不可能用暴力等类做法，否则会......~~


## 首先我们可以尝试用map来做一个映射关系，如下：
 设今年为第 $i$ 年，在世人数为 $bnum$ 人，离世人数为 $dnum$ 人，则 **映射关系为 $mp_i=bnum-dnum$** 即第 $i$ 年，增长了 $bnum-dnum$ 人 (Ps：如果 $bnum-dnum$ 为负时则表示没有在世的人，反而有离世的人)。

   那么根据以上条件就可以写代码了。

# 0x02 AC code
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int b,d;
map< int,int > mp;


int main()
{
	scanf("%d",&n);
	while (n--)
	{
		scanf("%d%d",&b,&d);
		mp[b]++;//在b年出生，当年增长一人
		mp[d]--;//在d年死亡，当年减少一人
	}
	int anst=0;
	int ans=0;
	int t=1;
	int max=-1;
	for (auto it:mp)
	{
		ans+=it.second;//加上当年净增长人数
		if (ans>max)
		{
			max=ans;
			anst=it.first;//修改为当前符合要求的答案
		}
	}
	cout << anst << " " << max << endl;
	return 0;
}

```

---

## 作者：Clyfort (赞：1)

# Solution

看到题目，首先想到的就是模拟（可能是我模拟做多了），再看到数据范围 $1 \le b_i \le d_i \le 10^9$，立马想到用 `map`。

具体怎么实现呢，我们用一个 `map` $p$ 来存储每年活着的人，也就是说，对于第 $i$ 个人，我们需要将 $p_{b_i} + 1$，然后将 $p_{d_i} - 1$，这样 $p_i$ 就是第 $i$ 年的净人数，即第 $i$ 年出生的人数 $-$ 第 $i$ 年死亡的人数。

最后对 $p$ 中的每个元素进行枚举，如果枚举到第 $i$ 个元素，则若对于 $x \in \{k \in N_+ | \  k < i\}$ 的所有 $p_x$ 之和大于当前最大解，则记录答案（位置和人数）。

# Code
```c++
#include <bits/stdc++.h>
using namespace std;

int n, ans, pos, maxans;
map <int, int> live;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i ++)
    {
        int x, y;
        cin >> x >> y;
        live[x] ++;
        live[y] --;
    }

    for (auto x : live)
    {
        ans += x.second;
        if (ans > maxans)
        {
            pos = x.first;
            maxans = ans;
        }
    }
    cout << pos << " " << maxans;
    return 0;
}
```

---

## 作者：NRDI (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1424G)

## 题意
给出各种人的生卒年，求人口最多是啥时候。

## 思路
一看到这题就知道要用差分，但是数据量达到 $ 10^9 $，用数组会爆内存，想到了 STL 的 map。

map 有一个 key 和一个 value，把原本方法数组的下标设为 int 类型即可。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

map <int, int> ma; // 由于数据范围到了1e9,用map,前面用int,不然会爆
int n, x, y, ans, maxx, sum; //n为人数，x,y分别为出生年和卒年

int main() {
    //先输入哈
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //上面是输入优化,也可以用scanf
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x >> y; //出生年和卒年
        //下面两步是差分
        ma[x]++;
        ma[y]--;
    }
    for (auto i : ma) { //auto默认识别数据类型,好像要用c++11
        sum += i.second; //second是map自带的，就是所谓的value
        if (sum > maxx) {
            ans = i.first; //first是key
            maxx = sum;
        }
    }
    cout << ans << " " << maxx;
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/154791198)

---

## 作者：ny_Dacong (赞：0)

这是一道差分模板题。不过考虑到数据范围较大，所以可以使用 map 维护。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
map<int,int> Map;
int n,b,d,ans,sum,year;
int main() {
	scanf("%d",&n);
	for(int i = 1; i <= n; i++){
		scanf("%d%d",&b,&d);
		Map[b]++;
		Map[d]--;
	}
	auto i = Map.begin();
	for(; i != Map.end(); i++){
		sum += i->second;
		if(sum > year){
			ans = i->first;
			year = sum;
		}
	}
	printf("%d %d",ans,year);
	return 0;
}
```

---

## 作者：DHT666 (赞：0)

## 题意
区间修改 + 查询最大值及其下标。

## 思路
区间修改？直接差分。

注意到区间范围是 $10^9$，故考虑 map。

在差分完成后，需要遍历 map，就涉及到迭代器的使用，用 `map<int,int>::iterator i` 申请一个迭代器叫 `i`，可以在 map 中使用。

一些常见的~~我用到的~~操作：

- `begin()`，获取一个 map 的首地址。
- `end()`，获取一个 map 的尾地址。
- `->`，其实就是一般用 map 中的 `.`，用于指针访问值。
 
怎么到下一个地址？直接 `++` 就行了。

## 代码
~~~cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, sum, p, ans;

map<int,int> m;

signed main(){
    cin >> n;
    for(int i = 1;i <= n;i++) {
    	int x, y;
    	cin >> x >> y;
    	m[x]++, m[y]--; // 注意区间是 l ~ r - 1
	}
	
	for(map<int,int>::iterator i = m.begin();i != m.end();i++) {
		sum += i -> second; // 前缀和
		if(sum > p) { // 找最大
			p = sum;
			ans = i -> first;
		}
	}
	
	cout << ans << " " << p;
    
    
    return 0;
}
~~~

---

## 作者：nyC20 (赞：0)

# 思路
差分板子，但是注意到数据范围 $ 1 \le b \lt d \le 10^9 $，所以不能开常规数组，马上想到 STL 库的 map，直接用就可以了，输入生卒年就维护离散化的 map，然后遍历一遍找答案即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
map<int,int> Map;
int n, b, d, ans, sum, year;
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&b,&d);
		Map[b]++;
		Map[d]--;//活到d-1年，但是差分右端点要加一，故Map[d]-- 
	}
	map<int,int>::iterator i;
	for(i=Map.begin();i!=Map.end();i++){
		sum+=i->second;
		if(sum>year){
			ans=i->first;
			year=sum;
		}
	}
	printf("%d %d",ans,year);
	return 0;
}
```

---

## 作者：_QWQ__QWQ_ (赞：0)

## 思路

这个题意思很显然，是求 $ n $ 个区间重叠最多的地方和值。

那么我们能想到用差分数组，在扫一遍的过程中维护最大值和 $ pos $。

但是需要注意的是，区间最大会到 $ 10^9 $，直接差分是不行的，我们需要先对所有 $ b $ 和 $ d $ 进行离散化，然后再去差分。

## 源码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
int n,ans,sum,pos,cnt,tot,a[maxn],l[maxn],r[maxn],b[maxn],c[maxn];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>l[i]>>r[i];
        a[++cnt]=l[i];
        a[++cnt]=r[i];
    }
    sort(a+1,a+cnt+1);
    for(int i=1;i<=cnt;i++){
    	if(i==1||a[i]!=a[i-1]){
    		a[++tot]=a[i];
		}
	}  
    int t1,t2;
    for(int i=1;i<=n;i++){
        t1=lower_bound(a+1,a+tot+1,l[i])-a;
        t2=lower_bound(a+1,a+tot+1,r[i])-a;
        c[t1]=l[i];//记录本来的位置
		c[t2]=r[i];//记录本来的位置
        b[t1]++;
		b[t2]--;
    }
    for(int i=1;i<=tot;i++){
        sum+=b[i];
        if(sum>ans){
        	ans=sum,pos=c[i];
		}
    }
    cout<<pos<<' '<<ans;
    return 0;
}
```

---

## 作者：ChenZQ (赞：0)

这道题我们可以使用 `map` 来做。

首先，看到题目，我们就可以想到算法差分。

差分是一种优化区间操作的算法，比如我们想给从 $l$ 和 $r$ 的区间加上 $k$。我们只需要给 $a_l$ 加上 $1$，$a_{r+1}$ 减一就好了，最后再做一遍前缀和。

为什么呢？

比如 $l = 2$，$r = 4$。数组的长度是 $5$。那么我们按照上面的操作，给指定区间加一，那么数组会变成这样：

`0 1 0 0 -1`

那么再做一遍前缀和就是：

`0 1 1 1 0`

那个负一相当于一个挡住加一的点。这就是差分的原理。

但是数据范围太大了，我们无法使用普通的差分来做这道题，所以我们可以使用 `map` 来做。

以下是代码，参考此篇[题解](https://www.luogu.com.cn/blog/lhydcm/solution-cf1424g)。

```
#include<bits/stdc++.h>
using namespace std;
map<int,int> c;
int main()
{
    int n;
    int a,b;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a>>b;
        c[a]++;
        c[b]--;//注意，题目是说第b年死了，所以不能加一。
    }
    int ans=0,pos,max=-1;
    for(map<int,int>::iterator it=c.begin();it!=c.end();it++)//ans其实就是我们差分前缀和的过程。
    {
        ans+=it->second;
        if(ans>max)
        {
            max=ans;//我们只需要每个区间看开头就好了，因为只要没有其他区间的干扰，开头的元素其实就是整个区间的元素。而有区间的干扰，那个区间段其实也是跟那个区间的开头是一样的。只是累加了一下而已。
            pos=it->first;
        }
    }
    cout<<pos<<" "<<max;
}
```

---

