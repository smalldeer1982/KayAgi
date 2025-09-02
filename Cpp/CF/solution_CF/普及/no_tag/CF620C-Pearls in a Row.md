# Pearls in a Row

## 题目描述

There are $ n $ pearls in a row. Let's enumerate them with integers from $ 1 $ to $ n $ from the left to the right. The pearl number $ i $ has the type $ a_{i} $ .

Let's call a sequence of consecutive pearls a segment. Let's call a segment good if it contains two pearls of the same type.

Split the row of the pearls to the maximal number of good segments. Note that each pearl should appear in exactly one segment of the partition.

As input/output can reach huge size it is recommended to use fast input/output methods: for example, prefer to use scanf/printf instead of cin/cout in C++, prefer to use BufferedReader/PrintWriter instead of Scanner/System.out in Java.

## 样例 #1

### 输入

```
5
1 2 3 4 1
```

### 输出

```
1
1 5
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7
1 2 1 3 1 2 1
```

### 输出

```
2
1 3
4 7
```

# 题解

## 作者：jockbutt (赞：2)

~~我也来㵘一波。~~

这道题其实就是来讲set和map的用法的。map有人写过了，我来一个set吧。

浅谈set：set的功能就是排序和去重。然后看看某个元素出现过没有。以下是几个set的常用函数：
```cpp
#include <set>//set头文件，当然也在万能头中
set <int> st//定义set，我喜欢用st命名
set.insert(a)//插入数据
set.count(a)//查找数据是否出现
set.clear()//清空
```
具体的不多说。

解法呢很简单，就是贪心，尽可能地多划分一点区间，每一次重复就记录一下最大值就可以了。

AC代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
set <int> st;
int n;
int sum;
int l[1001000]={1,1},r[1010000];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int a;
		scanf("%d",&a);
		if(st.count(a)==1)
		{
			sum++;
			r[sum]=i;
			l[sum+1]=i+1;
			st.clear();
		}
		else	st.insert(a);
	}
	r[sum]=n;
	if(sum==0)	printf("-1\n");
	else{
		printf("%d\n",sum);
		for(int i=1;i<=sum;i++)
		{
			printf("%d %d\n",l[i],r[i]);
		}
	}
	return 0;
}

```


---

## 作者：HMZHMZHMZ (赞：1)

### 题意

给定 $ n $ 个数，要求切割出来的区间内必须至少含有两个相同的数，问最多能切成多少段。

### 思路

显然的贪心，开一个 `map` 记录该数是否被用过，然后发现重复的就归为一段。

不过要注意，我们取出来区间之后可能还会剩下一段，比如 ` 1 2 1 3 ` 这一组数据，如果不判断会直接输出 ` 1 1 3 `，所以要判断最后一段是否包括了 $ n $。

为了避免 `TLE`，最好少使用 `map` 的 `clear` 操作，我采取的写法是给它打上一个时间戳。

时间复杂度 $ O(n \log n) $。

### 代码

```cpp

#include<bits/stdc++.h>
#define ll long long
#define vi vector<int>
#define pii pair<int,int>
#define pb(x) push_back(x)
using namespace std;
ll ans;
int n,m,T,x;
queue<pii> q;
map<int,int> mp;
inline int read(){
	int s=0,f=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch<='9'&&ch>='0') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return f?-s:s;
}
int main(){
	n=read();
	int t=1,l=1;
	for(register int i=1;i<=n;++i){
		x=read();
		if(mp[x]==t){
			++t;
			q.push((pii){l,i});
			l=i+1;
		}else mp[x]=t;
	}
	if(q.size()){
		printf("%d\n",q.size());
		while(!q.empty()){
			if(q.size()!=1) printf("%d %d\n",q.front().first,q.front().second);
			else printf("%d %d\n",q.front().first,n);
			q.pop();
		}
	}else printf("-1");
	return 0;
}

```

---

## 作者：hxhhxh (赞：1)

## 大意

给定长度为 $ n $ 的数组，你要把它划分成尽可能多的几段，使得每一段中都有至少两个不同的元素。求方案，或说不可能。

## 思路

如果某一段 $ [l,r] $ 是合法的，那一般没有必要取 $ [l,r+k](k \in \{1,2,3,\dots\}) $ ，除非这是最后一段，且 $ r < n $ 。

用一个`map`记录一下当前划分中出现的数并记录左端点。如果这个数出现过，答案线段就要加上这一条线段，清空`map`并更新左端点。

如果答案线段一条都没有，`-1`；

如果最后一条线段右端点 $ < n $ ，将它设为 $ n $ ，因为每一个元素都要覆盖。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[300005];
queue<pair<int,int> >ans;
map<int,bool>mp;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	int ls=1;
	for(int i=1;i<=n;i++){
		if(mp[a[i]]){
			ans.push((pair<int,int>){ls,i});
			mp.clear();
			ls=i+1;
		}
		else mp[a[i]]=true;
	}
	if(ans.empty()) cout<<-1;
	else{
		cout<<ans.size()<<endl;
		while(!ans.empty()){
			int l=ans.front().first,r=ans.front().second;
			ans.pop();
			if(ans.empty()) printf("%d %d\n",l,n);
			else printf("%d %d\n",l,r);
		}
	}
	return 0;
}
```

---

## 作者：傅思维666 (赞：1)


## 题解：

[题解博客传送门](https://www.cnblogs.com/fusiwei/p/11833574.html)

~~2019.11.11光棍节模拟赛T1 100分场可海星~~

这是我自从参加$JDFZ\,\,CSP-S$模拟赛之后第一次秒切T1的场！！炒鸡鸡冻！

我觉得思路真的特别好想：

一边输入一边标记出现的数，如果碰到已经打上标记的数就清空标记数组，$++cnt$并且开一个$last$变量存区间分割点。

但是$bool$数组开$1e9$就会炸...

咋办呢？

我们发现$STL$给我们提供了一个特别好用的容器$set$，专门用来维护元素重复的集合。

里面提供了一个特别好用的函数$find()$，能返回等于元素的迭代器。如果返回的迭代器不等于$s.end()$，说明有这个元素，就可以加进答案里。

在$CF$交的时候还出现了一种始料未及的情况，就是这种做法可能会出现不覆盖满的情况，所以退出来的时候要暴力地把$ans[cnt].r$变成$n$。

完整代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
const int maxn=3*1e5+10;
int n,last,cnt;
int a[maxn];
struct node
{
    int l,r;
}ans[maxn];
set<int> s;
set<int>::iterator it;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    last=1;
    for(int i=1;i<=n;i++)
    {
        if((it=s.find(a[i]))!=s.end())
        {
            ans[++cnt].l=last,ans[cnt].r=i;
            s.clear();
            last=i+1;
        }
        else
            s.insert(a[i]);
    }
    if(!cnt)
    {
        printf("-1");
        return 0;
    }
    ans[cnt].r=n;
    printf("%d\n",cnt);
    for(int i=1;i<=cnt;i++)
        printf("%d %d\n",ans[i].l,ans[i].r);
    return 0;
}
```



---

## 作者：MIN__2500 (赞：1)

这道题我JJ4次，******************套路深啊******************

一不小心tle，mle就来了。可能卡struct。
```
#include<iostream>
#include<set>
#include<stdio.h>//洛谷可以用万能头，但vjudge不行会ce
using namespace std;
set<int>Q;//set的定义
set<int>::iterator it;
struct node//结构体的定义
{
    int l,r;
} que[100000005];
int main()
{
    int n,k=0,x;
    while(scanf("%d",&n))//我觉得没啥好说的，如果不会可以学一下结构体
    {
        int i=1;
        while(i<=n)
        {
            que[k].l=i;
            while(i<=n)
            {
                scanf("%d",&x);
                i++;
                it=Q.find(x);
                if(it!=Q.end())
                {
                    Q.clear();
                    que[k++].r=i-1;
                    break;
                }
                else
                {
                    Q.insert(x);
                }

            }
        }
        if(k==0)
            {
                printf("-1\n");
                return 0;
            }
        else
        {
            printf("%d\n",k);
            for(int i=0; i<k-1; i++)
            {
                printf("%d %d\n",que[i].l,que[i].r);
            }
            printf("%d %d\n",que[k-1].l,n);
            return 0;
        }
    }
    return 0;
}
```
AC代码

我也是醉了，要用map
```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>//map头文件
using namespace std;
map<int,int> M;//map的定义
int s[300030];
int ansl[300030],ansr[300030];
int main()
{
    int n;
    while (scanf("%d",&n)!=EOF)
    {
        M.clear();
        int num=0,ll=1;
        for (int i=1; i<=n; i++)
        {
            scanf("%d",&s[i]);
            if (M[s[i]]!=0)
            {
                ansl[num]=ll;
                ansr[num++]=i;
                ll=i+1;
                M.clear();
            }
            else
                M[s[i]]=1;
        }

        ansr[num-1]=n;
        if (num)
            printf("%d\n",num);
        else
            printf("-1\n");
        for (int i=0; i<num; i++)
            printf("%d %d\n",ansl[i],ansr[i]);


    }
}
```
蒟蒻发题解

大犇点个赞




---

