# Two Pizzas

## 题目描述

现在到了午饭时间，你要为$n$个朋友定披萨。

众所周知，披萨的原料分为9种。每位朋友都有自己喜好的原料（一种或多种），第$i$个朋友喜欢的原料有$f_i$种，分别是$b_{i1},b{i2},...,b{if_i}$。

披萨店出售$m$种不同的披萨。第$j$种披萨里面有$r_j$种原料，分别是$a_{j1},a_{j2},...,a_{jr_j}$。第$j$种披萨售价为$c_j$。

现在你们决定购买恰好两个披萨。我们称一个人是“满意的”，当且仅当他/她想要的**每种原料**都在**至少一个**买下来的披萨出现。你希望最多人是“满意的”，并在这个前提下，支出越少越好。请输出任意一种方案。

## 说明/提示

保证：

- $1\leq n\leq 10^5,2\leq m\leq 10^5$
- $1\leq c_j\leq 10^9$
- $1\leq f_i,b_{it},r_j,a_{jt}\leq 9$

## 样例 #1

### 输入

```
3 4
2 6 7
4 2 3 9 5
3 2 3 9
100 1 7
400 3 3 2 5
100 2 9 2
500 3 2 9 5
```

### 输出

```
2 3
```

## 样例 #2

### 输入

```
4 3
1 1
1 2
1 3
1 4
10 4 1 2 3 4
20 4 1 2 3 4
30 4 1 2 3 4
```

### 输出

```
1 2
```

## 样例 #3

### 输入

```
1 5
9 9 8 7 6 5 4 3 2 1
3 4 1 2 3 4
1 4 5 6 7 8
4 4 1 3 5 7
1 4 2 4 6 8
5 4 1 9 2 8
```

### 输出

```
2 4
```

# 题解

## 作者：CaiXY06 (赞：3)

因为材料只有 $9$ 种，所以我们可以把每一种类型状态压缩成一个数，所以总共的种类数只有 $2^9=512$ 种。对于每一种类的披萨，即状压后编号为 $0-511$ 的披萨，我们统计买它会使多少人满意。

然后我们对于 $m$ 个披萨，我们枚举买两个的编号或的值，判断是否可行并且是否最优（这样就可以排除某些枚举方式下需要去重的问题）。这样显然是 $O(m^2)$ 的，过 $10^5$ 显然不现实，所以我们考虑优化。

我们在做的时候，顺便维护一下满足编号 $i$ 的披萨的花费的最小值以及它的编号，这样就可以做到在判断时枚举一个披萨，$O(1)$ 找到另一个披萨。总时间复杂度为 $O(512(n+m))$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,res=-1,ans,A,B,vis[600],cnt[600],v[600];
//注意最大人数的初始值要赋负值，可能会出现没有一个满足的情况
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1,k,s;i<=n;i++){
		scanf("%lld",&k);
		s=0;
		for(int j=1,x;j<=k;j++)
		scanf("%lld",&x),s|=1<<(x-1);
		for(int j=0;j<512;j++)
		if((s|j)==j)cnt[j]++;//统计人数
	}
	for(int i=1,k,s,c;i<=m;i++){
		scanf("%lld",&c);
		scanf("%lld",&k);
		s=0;
		for(int j=1,x;j<=k;j++)
		scanf("%lld",&x),s|=1<<(x-1);
		for(int j=0;j<512;j++){//枚举编号或和
			if((s|j)!=j)continue;
			if(cnt[j]<res)continue;
			int o=j^s;//另外一个披萨的编号
			if(!vis[o])continue;
			if(cnt[j]>res||(cnt[j]==res&&v[o]+c<ans)){
				res=cnt[j],ans=v[o]+c;
				A=i,B=vis[o];
			}
		}
		for(int j=0;j<512;j++)if((s|j)==s)if(!vis[j]||c<v[j])vis[j]=i,v[j]=c;//维护
		if(!vis[0]||c<v[0])vis[0]=i,v[0]=c;
	}
	printf("%lld %lld",A,B);
	return 0;
}
```


---

## 作者：wucstdio (赞：3)

题面翻译好评。

首先我们发现食材只有$9$种，所以每一个集合都可以用二进制来表示。

我们记录$min[s]$表示用了$s$这个集合的所有的披萨中最小的花费，$num[s]$表示需求为$s$的管理员人数。

我们可以枚举两个集合$s_1,s_2$表示你选出来的披萨，这样能够满足的人数就是$\sum_{s'\in(s_1\cup s_2)num[s']}$，直接枚举子集即可。

然而这两个集合是可以相等的，所以我们还需要对每一个集合记录一下第二小的花费。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,a[100005],c[100005],s[100005],minc[1<<9],minc2[1<<9],ans[1<<9],num[1<<9];
int kind[1<<9],k2[1<<9],x[1<<9],y[1<<9];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int k;
        scanf("%d",&k);
        while(k--)
        {
            int x;
            scanf("%d",&x);
            a[i]|=1<<(x-1);
        }
        num[a[i]]++;
    }
    memset(minc,0x3f,sizeof(minc));
    memset(minc2,0x3f,sizeof(minc2));
    memset(ans,0x7f,sizeof(ans));
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&c[i]);
        int k;
        scanf("%d",&k);
        while(k--)
        {
            int x;
            scanf("%d",&x);
            s[i]|=1<<(x-1);
        }
        if(c[i]<minc[s[i]])
        {
            minc2[s[i]]=minc[s[i]];
            minc[s[i]]=c[i];
            k2[s[i]]=kind[s[i]];
            kind[s[i]]=i;
        }
        else if(c[i]<minc2[s[i]])
        {
            minc2[s[i]]=c[i];
            k2[s[i]]=i;
        }
    }
    for(int i=0;i<(1<<9);i++)
    {
        if(kind[i]&&k2[i])
        {
            ans[i]=minc[i]+minc2[i];
            x[i]=k2[i],y[i]=kind[i];
        }
    }
    for(int i=0;i<(1<<9);i++)
    for(int j=i+1;j<(1<<9);j++)
    {
        if(minc[i]>1000000000||minc[j]>1000000000)continue;
        ans[i|j]=min(ans[i|j],minc[i]+minc[j]);
        if(ans[i|j]==minc[i]+minc[j])
        {
            x[i|j]=kind[i];
            y[i|j]=kind[j];
        }
    }
    int res=0,maxx=-1,val=2147483647;
    for(int i=0;i<(1<<9);i++)
    {
        if(ans[i]>2000000000)continue;
        int now=0;
        for(int j=0;j<(1<<9);j++)
        {
            if((j&i)==j)
              now+=num[j];
        }
        if(now>maxx)res=i,maxx=now,val=ans[i];
        else if(now==maxx&&ans[i]<val)res=i,val=ans[i];
    }
    printf("%d %d\n",x[res],y[res]);
    return 0;
}
```

---

## 作者：傅思维666 (赞：0)


## 题解：

[题解博客传送门](https://www.cnblogs.com/fusiwei/p/11822348.html)

~~2019.11.8模拟赛T2 30分场~~

前一天刚学状压就来一道状压的题，虽然没场上切但还是感谢出题人@ysy20021208，吸一口大佬欧气。

一开始看到数据范围果断选择了状压，一看就是这9种东西选还是没选，然后觉得可以依次枚举这$m$张披萨两两搭配合并之后能满足多少人的欲望。进行更新。一看这复杂度是$O(N*M*M)$的，肯定是废只能拿30分。后来一想：虽然$n$是$10^5$级别的，但是这$9$位的状态无论如何只能搭配出$512(2^9)$种可能，所以$N$就被我们优化到了$512$，然后一顿乱搞，最后还是拿了30分（滑稽）

（暴力考场代码使用了各种$C++STL$...）

```cpp
#include<cstdio>
#include<bitset>
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn=1e5+10;
const int INF=2147483645;
int n,m,maxx,minn=INF,ansx,ansy,tot;
bitset<10> t;
bitset<10> s[1<<9+1];
vector<pair<int,bitset<10> > >vec;
struct node
{
    int v,id;
    bitset<10> x;
}p[maxn];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int a,f;
        bitset<10> tt;
        scanf("%d",&a);
        for(int j=1;j<=a;j++)
        {
            int k;
            scanf("%d",&k);
            tt.set(k);
        }
        for(int j=0;j<vec.size();j++)
            if(vec[j].second==tt)
            {
                vec[j].first++;
                break;
            }
        vec.push_back(make_pair(1,tt));
    }
    for(int i=1;i<=m;i++)
    {
        int a;
        scanf("%d%d",&p[i].v,&a);
        for(int j=1;j<=a;j++)
        {
            int k;
            scanf("%d",&k);
            p[i].x.set(k);
        }
        p[i].id=i;
    }
    maxx=-1;
    for(int i=1;i<=m;i++)
        for(int j=i;j<=m;j++)
        {
            tot=0;
            if(i==j)
                continue;
            t=(p[i].x|p[j].x);
            for(int k=0;k<vec.size();k++)
                if((vec[k].second&t)==vec[k].second)
                    tot+=vec[k].first;   
            if(tot>=maxx)
            {
                if(tot>maxx)
                    minn=INF;
                maxx=tot;
                if((p[i].v+p[j].v)<minn)
                {
                    ansx=i,ansy=j;
                    minn=p[i].v+p[j].v;
                }
            }
        }
    printf("%d %d",ansx,ansy);
    return 0;
}
```

然后我详细介绍一下看完题解之后自己捋顺的满分思路：

其实暴力想的时候已经离正解好近了（真是遗憾）。

我想到了把$n$个人的状态进行包含性质的枚举，但是就是没想到$m$张披萨也可以这么干（简直匪夷所思）。

看一下题：我们发现：对于两张披萨，它们有可能能满足同一个人的需求，这时，这两张披萨之间肯定是子集或真子集的关系。那么我们完全可以把$m$张披萨也“需求化”。什么意思呢？既然枚举所有的$n,m$复杂度过高，那么我们就“要什么拿什么”，设置$minn[st]$数组来存能满足需求为$st$的人的所有披萨中价值最小的那张的花费。并且，存储$num[st]$表示需求为$st$的人的人数。**同时**，因为我们需要选择最优秀的两张披萨，所以还需要记录一下满足需求为$st$的人的所有披萨中价值**第二小**的花费为$minn2[st]$。

那么我们在对披萨们进行预处理的时候，就可以顺道把这两个数组处理出来。并且，因为我们最终要输出披萨的编号，所以我们还需要另开数组$k,k2$来存当前状态最小价值披萨的编号、次小价值披萨的编号。

然后我们就完成了暴力的优化。由原来的$O(m^2)$级别的复杂度成功降低到了$O(512\times 512)$的复杂度。所以，在我们状态压缩的时候，懂得优化复杂度，一定要从状态入手，看枚举的东西能不能按状态进一步压缩而变得更快。

AC代码:

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=1e5+10;
const int maxs=1<<9;
int n,m;
int a[maxn],b[maxn],v[maxn],num[maxs];
int minn[maxs],minn2[maxs],k[maxs],k2[maxs];
int ans[maxs],ansx[maxs],ansy[maxs];
int main()
{
    memset(minn,0x3f,sizeof(minn));
    memset(minn2,0x3f,sizeof(minn2));
    memset(ans,0x7f,sizeof(ans));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int p;
        scanf("%d",&p);
        for(int j=1;j<=p;j++)
        {
            int k;
            scanf("%d",&k);
            a[i]|=1<<(k-1);
        }
        num[a[i]]++;
    }
    for(int i=1;i<=m;i++)
    {
        int p;
        scanf("%d%d",&v[i],&p);
        for(int j=1;j<=p;j++)
        {
            int k;
            scanf("%d",&k);
            b[i]|=1<<(k-1);
        }
        if(v[i]<minn[b[i]])
        {
            minn2[b[i]]=minn[b[i]];
            minn[b[i]]=v[i];
            k2[b[i]]=k[b[i]];
            k[b[i]]=i;
        }
        else if(v[i]<minn2[b[i]])
        {
            minn2[b[i]]=v[i];
            k2[b[i]]=i;
        }
    }
    for(int i=0;i<maxs;i++)
        if(k[i]&&k2[i])
        {
            ans[i]=minn[i]+minn2[i];
            ansx[i]=k2[i],ansy[i]=k[i];
        }
    for(int i=0;i<maxs;i++)
        for(int j=i+1;j<maxs;j++)
        {
            if(minn[i]>1000000000 || minn[j]>1000000000)
                continue;
            ans[i|j]=min(ans[i|j],minn[i]+minn[j]);
            if(ans[i|j]==minn[i]+minn[j])
            {
                ansx[i|j]=k[i];
                ansy[i|j]=k[j];
            }
        }
    for(int i=0;i<maxs;i++)
        printf("%d\n",ans[i]);
    int target=0,maxx=-1,mi=2100000000;
    for(int i=0;i<maxs;i++)
    {
        if(ans[i]>2000000000)
            continue;
        int tmp=0;
        for(int j=0;j<maxs;j++)
            if((j&i)==j)
                tmp+=num[j];
        if(tmp>maxx)
            target=i,maxx=tmp,mi=ans[i];
        else if(tmp==maxx && ans[i]<mi)
            target=i,mi=ans[i];
    }
    printf("%d %d\n",ansx[target],ansy[target]);
    return 0;
}
```



---

