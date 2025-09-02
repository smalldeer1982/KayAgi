# Bug in Code

## 题目描述

公司的代码出问题了！！越学越掂十分生气，为了有个说法，他决定选出两个背黑锅的人。

现在有$n$个人，每个人都会选出两个背黑锅的人，老板想要让决定背黑锅的两个人的支持数（就是有几个人想让这个人背黑锅）之和大于等于$P$。请问有多少种选择方案（顺序无关）

## 样例 #1

### 输入

```
4 2
2 3
1 4
1 4
2 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
8 6
5 6
5 7
5 8
6 2
2 1
7 3
1 3
1 4
```

### 输出

```
1
```

# 题解

## 作者：开始新的记忆 (赞：3)

这道题是我在VJ上比赛时做到的，原题链接：http://codeforces.com/problemset/problem/421/D

这道题我看第一眼就想到把每个人都有多少人选进行记录。（这很容易想）然后WA了……

我百思不得其解，于是乎在疯狂造数据的时候，终于发现本题一大坑点：去重 。因为如果有两个人都选的是同样的两个人，那么当枚举到这两个人时，会多算（可以举个例子看看）。

e.g: 

5 3

1 2

1 2

3 4

3 5

4 5

用一开始的思想来看，计数的数组应该是这样的：2 2 2 2 2，无论怎么选，都可以满足老板的要求，可是如果选1和2的话，同意的人只有两个，不满足大于等于3的条件。

去重过程  x和y分别表示每个人的预测，（x<y），同样的一组预测x和y出现了c次，假如cnt[x]+cnt[y]>=y&&cnt[x]+cnt[y]-c<p，则ans--。

代码如下:

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define FFF 300005
int cnt[FFF],to[FFF];
struct node {
    int x,y;
}f[FFF];
bool cmp(node a,node b){
    if(a.x==b.x)
        return a.y<b.y;
    else
        return a.x<b.x;
}
int main()
{
    int n,p;
    scanf("%d%d",&n,&p);
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&f[i].x,&f[i].y);
        if(f[i].x>f[i].y)
        {
            int t=f[i].x;
            f[i].x=f[i].y;
            f[i].y=t;
        }
        cnt[f[i].x]++;
        cnt[f[i].y]++;
    }
    for(int i=1;i<=n;i++)to[i]=cnt[i];
    long long ans=0,now=n;
    sort(cnt+1,cnt+n+1);
    for(int i=1;i<=n;i++) {
        if(cnt[i]>=p)
            ans+=n-1;
        else{
            while(cnt[now]>=p-cnt[i])
                now--;
            if(cnt[now+1]+cnt[i]>=p){
                if(cnt[now+1]>cnt[i])
                    ans+=n-now;
                else
                    ans+=n-now-1;
            }
        }
    }
    ans/=2;
    sort(f,f+n,cmp);
    node tmp;
    tmp.x=tmp.y=0;
    memset(cnt,0,sizeof(cnt));
    int c=0;
    for(int i=0;i<n;i++)
    {
        if(tmp.x==f[i].x&&tmp.y==f[i].y)
            c++;
        else
        {
            if(tmp.x&&to[tmp.x]+to[tmp.y]>=p&&to[tmp.x]&&to[tmp.x]+to[tmp.y]-c<p)
                ans--;
            tmp.x=f[i].x;
            tmp.y=f[i].y;
            c=1;
        }
    }
    if(to[tmp.x]+to[tmp.y]>=p&&to[tmp.x]&&to[tmp.x]+to[tmp.y]-c<p)
        ans--;
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：GlenBzc (赞：1)

首先大致看了看题面，一眼二分，可以开个桶数组 $a$ 存每个人被怀疑的次数，排个序，因为需要 $x$ ，$y$ 两个人被怀疑的次数之和大于等于 $p$ ，所以我们可以遍历桶数组，每次用  lower_bound()  或者手动二分找到第一个符合  $ a[i] + a[j] \ge p$ 的索引 $j$ ，答案 $ans$ 就可以直接加上 $(n - j + 1 )$ 。 

代码如下:
```cpp
#include <bits/stdc++.h>
using namespace std;
signed main()
{
    int n,p;cin>>n>>p;
    int a[n+1];
    memset(a,0,sizeof(a));
    for(int i=1;i<=n;i++)
    {
          int x,y;cin>>x>>y;
          a[x]++;a[y]++;
    }
    long long ans=0;   
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++)
    {
        int j=lower_bound(a+1+i,a+1+n,(p-a[i]))-a;
        ans+=(n-j+1);
    }
    cout<<ans<<endl;
    return 0;
}
```
  
然而 Wrong answer on test 6 ...  
仔细一想发现不对，因为可能有重复的情况也就是多个人怀疑的一样，所以我们可以在排序前预处理一下。  

代码如下:
```cpp
#include <bits/stdc++.h>
using namespace std;
map<pair<int,int>,int> mp;
signed main()
{
   int n,p;cin>>n>>p;
    int a[n+1];
    memset(a,0,sizeof(a));
    mp.clear();
    for(int i=1;i<=n;i++)
    {
        int x,y;cin>>x>>y;
        if(x>y)swap(x,y);//别忘了swap，因为1，2和2，1是一样的
        a[x]++;a[y]++;
        mp[{x,y}]++;
    }
    long long ans=0;   
    for(auto i=mp.begin();i!=mp.end();i++)
    {
        if(a[i->first.first]+a[i->first.second]>=p&&a[i->first.first]+a[i->first.second]-i->second<p)
        {
            ans--;
        }
    }
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++)
    {
        int j=lower_bound(a+1+i,a+1+n,(p-a[i]))-a;
        ans+=(n-j+1);
    }
        cout<<ans<<endl;
	return 0;
}
```
~~时间卡的有点紧，可以开个读入优化。~~

---

## 作者：Graph_Theory (赞：0)

### 思路
枚举一个人，记录下这个人的票数，计算出另一个人所需的最小票数 $p-a_i$ 对每个人的票数排序并使用二分搜索查找一个 $a_j>p-a_i$ 此时所有 $a_{n\to j}+a_i>p$ 所以 $ans+(n-j+1)$ 即为当前满足的人数。

注意，样例存在有两个人或更多人的投票一样。例如：有两个人投票给了 $x$ 和 $y$ 实际上数组会认为有 $4$ 个人投票给了 $x$ 和 $y$，导致答案错误，这也是难点所在。 

所以我们计算相同对的数量，遍历 `map` 中的元素。当两个元素和达到 $p$ 时，且当前元素和减去投票人数小于 $p$ 时，此时 $ans-1$ 原因是投重复的那些人多投了一票，实际上只投了一票。

```cpp
for(auto i=mp.begin();i!=mp.end();i++)
{
	int nx  =  i->first.first;
	int ny  =  i->first.second;
	int tot =  i->second;
	//注意这里索引的返回值是 pair<Key, T> 
  	if(a[nx]+a[ny]>=p&&a[nx]+a[ny]-tot<p)
		ans--;
}
```

---

## 作者：RainFestival (赞：0)

枚举第一个被删除的人 $x$ 。

这样我们可以删除所有 $(x,y)$ 以及 $(y,x)$。

求出删除另外一个 $y$ 的方案数目。

代码：

```cpp
#include<cstdio>
#include<vector>
std::vector<int> a[300005];
int n,p,cnt[300005],f[300005];
long long ans=0;
int main()
{
	scanf("%d%d",&n,&p);
	for (int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		++cnt[x],++cnt[y];
		a[x].push_back(y),a[y].push_back(x);
	}
	for (int i=1;i<=n;i++) f[cnt[i]]++;
	for (int i=n;i>=1;i--) f[i]=f[i]+f[i+1];
	for (int i=1;i<=n;i++)
	{
		int k=p-cnt[i];
		if (k<=0) ans=ans+n-1;
		else
		{
			int del=0;
			if (cnt[i]>=k) ++del;
			for (int j=0;j<a[i].size();j++)
			{
				int x=a[i][j];
				if (cnt[x]--==k) ++del;
			}
			ans=ans+f[k]-del;
			for (int j=0;j<a[i].size();j++)
			{
				int x=a[i][j];
				++cnt[x];
			}
		}
	}
	printf("%lld\n",ans/2);
	return 0; 
}
```

---

