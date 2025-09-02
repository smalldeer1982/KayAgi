# New Year Ratings Change

## 题目描述

One very well-known internet resource site (let's call it X) has come up with a New Year adventure. Specifically, they decided to give ratings to all visitors.

There are $ n $ users on the site, for each user we know the rating value he wants to get as a New Year Present. We know that user $ i $ wants to get at least $ a_{i} $ rating units as a present.

The X site is administered by very creative and thrifty people. On the one hand, they want to give distinct ratings and on the other hand, the total sum of the ratings in the present must be as small as possible.

Help site X cope with the challenging task of rating distribution. Find the optimal distribution.

## 样例 #1

### 输入

```
3
5 1 1
```

### 输出

```
5 1 2
```

## 样例 #2

### 输入

```
1
1000000000
```

### 输出

```
1000000000
```

# 题解

## 作者：fls233666 (赞：5)

**2020年2月14日更新：修正题解排版格式**

--------

刚刚看到这道题，我的第一个想法是：开个 bool 数组，把用过的 rating 值标记，这样就不会有重复的 rating 值，那么问题就可以得到解决。

然后，看完测试数据大小，我马上否定了这个想法。

$0 \le a_i \le 10^9$

$10^9$ 大小的数组，早就炸了......

然后，我诞生了另一个想法：每确定一个 rating 值之前，先循环扫一遍数组，看有那些 rating 值被用过了，选出 $\ge a_i$ 的能用的最小的 rating 值。

但是这个想法也是不行的！还是测试数据范围的问题：

$0 \le n \le 3 \times 10^5$

上述想法的时间复杂度至少为 $O(n^2)$，也是过不去的。


------------


这时我再看这个 $n$ 的范围，发现算法的时间复杂度至少要为 $O(n \log(n))$。

那么我就想：**能否通过先处理较小的 $a_i$，然后来确定较大的 $a_i$ 值呢**？

于是，我先把每个 $a_i$ 按大小**排序**。

排序之后干什么呢？当时我一时半会没有思路，于是手动造了以下数据模拟一下：

**input**

	6
    1 3 5 1 5 1
    
**output**

	1 3 5 2 6 3
    
排序后:

    1 1 1 3 5 5

（**可以发现，会重复的 rating 值都被排到一起了**）

- 第一个数：$1$。**因为是最小的 rating 值，所以肯定是不用改的**。

- 第二个数：$1$。**对比之前的数，发现 $1$ 被用过了**。改成 $2$。

- 第三个数：$1$。**对比之前的数，发现 $1$ 和 $2$ 都被用过了**。改成 $3$。

- 第四个数：$3$。对比之前的数，发现 $3$ 被用过了。改成 $4$。

- 第五个数：$5$。**对比之前的数，发现 $5$ 并没有被使用**。不改。

- 第六个数：$5$。对比之前的数，发现 $5$ 被用过了。改成 $6$。

（上面被加粗的文字就是我们会遇到的全部情况，而这些情况中，第三个数要解决的情况就是我们耗时较大的情况，即**检查多个数被使用**）

更新完成后的数列：

    1 2 3 4 5 6

（可以发现，更新完成的序列是**递增的**）


------------


我们可以利用一下更新完成的序列是递增的特点：

**在排序后的数列中，当 $a_i \le a_{i-1}$ 时，表明 $a_i$ 已被使用，需要更新**

那么如何更新，才能保证结果最优呢？

我们发现，**如果在上面的数据中，在更新 $a_2$ 时，把 $a_{2}$ 改成 $2$，更新 $a_3$ 时，我们只要把 $a_3$ 更新成 $a_2+1$ 就得到了最优的答案**。

那么，得出本题的核心结论：

**在把所有的 $a$ 值排序后，从小到大更新，当 $a_i \le a_{i-1}$ 时，将 $a_i$ 更新为 $a_{i-1}+1$，否则 $a_i$ 值不变**


------------


看到这里，已经可以开始实现代码了。但是我们还有最后一个小问题没有解决。

题目要求不能改变顺序的输出每个 $a_i$ 对应的解。**那么怎么还原输入时 $a_i$ 的顺序呢？**

其实，我们可以把**输入时每个 $a_i$ 的位置（数组下标）记录下来**，和每个 $a_i$ 值封装成一个 struct （也可以写 pair ）。**更新 $a_i$ 的值时，把得到的答案按刚才记录的下标存到另一个数组 $\texttt{ans}$ 中，最后输出 $\texttt{ans}$ 数组即可**。


------------


最后总结一下上述的复杂度及算法思想：

- 时间复杂度：$O(n \log(n))$

- 空间复杂度：$O(n)$

- 算法思想：**排序&递推**

现在，放出代码：（本人采用 struct 实现）

```cpp
#include<iostream>
#include<algorithm> 
using namespace std;
struct people{
    int a;   //每个人想要的rating值
    int b;  //输入时的数组下标
};
bool cmp_p(struct people p1,struct people p2){
    return p1.a<p2.a;   //按a值从小到大排序
}
int main()
{
    int n;
    cin>>n;
    struct people p[n];
    int ans[n];
    for(int i=0;i<n;i++){
        cin>>p[i].a;
        p[i].b=i;  //记录数组下标
    }
    sort(p,p+n,cmp_p);
  //输入数据及排序
  
    ans[p[0].b]=p[0].a;  //特判第一个（最小的）rating值
    for(int i=1;i<n;i++)
        if(p[i].a>p[i-1].a)
            ans[p[i].b]=p[i].a;
        else{
            ans[p[i].b]=p[i-1].a+1;
            p[i].a=p[i-1].a+1;
        }
  //按上述结论更新
  
    for(int i=0;i<n;i++)
        cout<<ans[i]<<" ";  //输出答案
    return 0;
}
```


---

## 作者：xuezhe (赞：2)

为了使评级的总和最小，我们需要使每个人的评级都尽可能小。

这里采用一个贪心算法：按 $a_i$ 从小到大遍历，在所有不小于 $a_i$ 的没选过的 rating 中选一个**最小**的。

于是我采用了这样一个方法：~~瞎搞~~。

先把 $a$ 按非降序排序，然后搞一个数组 $u$ ，对于所有 $x$ 满足 $a_i \leq x < a_{i+1}$ ，$u_i$ 取 $x$ 的最小值。特殊的，对于 $i=n$ 这一情况， $u_i$ 取满足 $a_i \leq x$ 的 $x$ 中的最小值。每次在上一次查找的区间和当前区间中取更右边的区间找最小数，如果当前区间已经没数可选，则换下一个区间继续操作。这也是下面代码的打法。

然鹅，貌似并不需要分成一块一块的，直接记录上一个 $x$ 然后在 $x$ 和 $a_i$ 中取一个最大的即可。大家可以自己实现。

以上做法，若不算排序，时间复杂度皆为 $O(n)$ 。

输出的话，提前记录一下原序列的数在新序列的位置即可，按此输出即可。

C++代码：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
inline int mmax(int a,int b){
    return a>b?a:b;
}
int n;
struct Ps{
    int a,id;
}a[300002];
bool cmp(Ps a,Ps b){
    return a.a<b.a;
}
int to[300001],use[300001],b[300001];
int main(){
    scanf("%d",&n);
    int i,j=0;
    for(i=1;i<=n;++i){
        scanf("%d",&a[i].a);
        a[i].id=i;
    }
    sort(a+1,a+1+n,cmp);
    for(i=1;i<=n;++i){
        to[a[i].id]=i;
    }
    a[n+1].a=2147483647;
    for(i=1;i<=n;++i){
        use[i]=a[i].a;
    }
    for(i=1;i<=n;++i){
        for(j=mmax(j,i);j<=n;++j){
            if(use[j]<a[j+1].a){
                b[i]=use[j];
                ++use[j];
                break;
            }
        }
    }
    for(i=1;i<=n;++i){
        printf("%d ",b[to[i]]);
    }
    return 0;
}
```

---

## 作者：zjc5 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF379C)

**思路：**

这一题可以直接按照题目意思模拟。

开一个 **unordered_map**。因为 unordered_map 内部是用哈希表实现的，所以如果要频繁修改储存的值， unordered_map 比 map 快。

这里把 unordered_map 简称为 mp。

设 $mp_i=i$。因为无法让所有 $mp_i=i$，所以把 $mp_i=0$ 的情况当成 $mp_i=i$。

定义如果 $mp_{mp_{b_i}}=mp_{b_i}$ 那么 $b_i$ 的 rating 值就是 $mp_{b_i}$。

对于一个点 $b_i$，如果 $mp_{b_i}=b_i$ 为空就把 $mp_{b_i}$ 标记为 $b_i+1$。表示 $b_i$ 被占用，下次访问只能跳到 $b_i+1$。

如果 $mp_{b_i}>b_i$，则需要跳转到 $mp_{mp_{b_i}}$，直到出现 $mp_x=x$ 情况才停下来。

所以对于每一个 $b_i$ 进行一次递归求解就行了。

**CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b;
unordered_map<int,int>mp;
int find(int x){
    if(!mp[x]) {
        mp[x]=x+1;
        return x;
    }
    return mp[x]=find(mp[x]);
}
int main(){
	scanf("%d",&n);
	while(n--){
	    scanf("%d",&b);
	    printf("%d ",find(b));
	}
	return 0;
}
```

---

## 作者：_Memory (赞：0)

### 一、前言

这道题其实算法有很多，比如结构体排序，比如我用的 map 都是可以的。但是这道题有几个需要注意的点，待会会一一介绍。

### 二、思路

看到这道题的第一眼，兴奋了，妈呀一道水黄！想要用 bool 做标记，然后问题就会很愉快的解决。可是看到了一个叫做数据范围的东西。我承认我当时整个人都不好了，这不得把我炸上天？

不过，没有问题，蒟蒻的大脑飞速运转之后想起了一个叫做 map 的好东西，就用它了！

为了使得评分值之和最小，那就尽量让评分值较小的用户的评分值最小。如果多个用户有一样的评分值，那就依次递增就好。这个 map 就是已经分配的评分值。那么如果到了这个用户的时候，它本身的数在 map 里面不存在，皆大欢喜，我们给这个值和他自己的值加一的和一块塞到 map 里面去。如果已经存在于 map 之中的话，就把这个用户设置为下一个可用的值，并且将这个值直接分配给他本人就行。最后捏，就是输出所有用户分配的评分值就欧克力！

然后本蒟蒻满心欢喜的把代码交了上去：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,r;
map<int,int> mp;
int qwq(int a){
	if(!mp.count(a)){mp[a]=a+1;return a;}
	else return mp[a]=qwq(mp[a]);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>r;
		cout<<qwq(r)<<" ";
	}
	return 0;
}
```

结果呢，可爱的测评机送给了我一个大大的 TLE……
但是幸好只差了两毫秒左右，不慌，立刻反应过来把输入输出换成了 scanf 和 printf。然后就愉快的 AC 啦，这是 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,r;
map<int,int> mp;
int qwq(int a){
	if(!mp.count(a)){mp[a]=a+1;return a;}
	else return mp[a]=qwq(mp[a]);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
	    scanf("%d",&r);
	    printf("%d ",qwq(r));
	}
	return 0;
}
```
拜拜咯~

---

## 作者：ZHANGyutao123 (赞：0)

## [CF379C New Year Ratings Change](https://www.luogu.com.cn/problem/CF379C)

# 题目描述：

有 $n$ 个用户，每个用户希望得到一个评分值，记为 $a_i$。评分值需要是正整数，且该用户想要的评分值不能低于 $a_i$。现要对这 $n$ 个用户分别发放一个评分值，使得这 $n$ 个评分值之和最小，并且所有 $n$ 个评分值都是不同的。

# 算法思路：

为了使得评分值之和最小，我们可以让得到评分值较小的用户的评分值尽量小。

如果有多个用户想获得同样的评分值，我们可以按顺序给这些用户分配评分值，从小到大依次分配。为了保证每个用户都得到评分值，我们需要将已分配的最大的评分值加一为下一个可分配的评分值。

# 算法实现：
 
我们可以使用 map 来实现评分值的分配。我们维护一个 map，map 的键是已分配的评分值，值是该评分值的下一个可分配的评分值。

在分配评分值时，如果该用户要求的评分值在 map 的键中不存在，我们会将该值和其自身加一的值全部加入到 map 中，然后分配其中的这个较小的值。

如果该值已经存在于 map 之中，我们会将该键的值设为它下一个可用的键值，并将这个新的键值分配给当前的用户即可。最后，我们输出所有用户分配的评分值即可。

# 代码实现：

```cpp
#include <bits/stdc++.h>  // 引入万能头文件
using namespace std;

int n, rating;  // n: 用户数，rating: 用户期望评分值
map<int, int> mp;  // mp: 评分值的下一个可分配的评分值

// 使用map查找评分为x的下一个可分配的评分值
int find(int x) {
    if (!mp.count(x)) {  // 如果x还没有被分配，则将该值和其自身加一的值全部加入到mp中
        mp[x] = x + 1;  // 将x的下一个可分配的评分值设为x+1
        return x;  // 返回x
    }
    // 否则，递归查找x的下一个可分配的评分值
    return mp[x] = find(mp[x]);  // 并将x的下一个可分配的评分值设为find(mp[x])的返回值
}

int main() {
    scanf("%d", &n);  // 读入用户数
    for (int i = 1; i <= n; i++) {  // 遍历每个用户
        scanf("%d", &rating);  // 读入该用户期望的评分值
        printf("%d ", find(rating));  // 输出该用户得到的评分值，并将评分值加入到并查集中
    }
    return 0;
}
```

## 算法复杂度：

时间复杂度：$O(n\log n)$，因为 map 的查询和修改的时间复杂度均为 $O(\log n)$。

空间复杂度：$O(n)$，我们需要使用 map 来存储每个评分值的下一个可分配的评分值。

---

## 作者：yinpeichu2021 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF379C)

# 思路 $1$

先考虑暴力，

要使得评级的总和尽可能小，就要使每一个人的评级都尽可能小。

所以可以从小到大遍历，并在没有选过的评级中选一个最小的。

但 $a_i$ 可以到达 $10^9$，所以用 map 来存储。

# 思路 $2$

思路 $1$ 时间复杂度为 $O(n^2)$，对于最坏情况（即全是 $1$ 的情况）时，在第 $i$ 次查找（$1\le i\le n$）中，每一次从 $1$ 找到 $i$，多次访问了同一个数，会 TLE。

我们可以用并查集算法中的**路径压缩**的思想，通俗点来讲，就是在访问时从 $1$ 直接跳到 $i$，而不用重新再访问一遍。

定义一个 map 类型的 $mp$，$mp_i$ 表示评级为 $i$ 的下一个未选过的评级是多少。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;
map<int,int>mp;
int find(int x){//返回值表示x的下一个未被选过的评级
    if(!mp.count(x)){//此时x没有被选过，就选择它
        mp[x]=x+1;//x已被选，其下一个未被选过的为x+1
        return x;
    }
    return mp[x]=find(mp[x]);//将x的下一个未被选过的存进mp[x]中，并返回mp[x]
}
int main(){
    scanf("%d",&n);
    while(~scanf("%d",&x))
        printf("%d ",find(x));
}
```

---

## 作者：drop (赞：0)

[题目](https://www.luogu.com.cn/problem/CF379C)

## 第一次尝试

### 分析

用 `map<int,int>b` 来存储每一个数用过没有，如果用过判断下一个用过没有，直到没有用过，就输出。

### 实现

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a;
map<int,bool>b;

int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a;
		while(b[a]) a++;
		cout<<a<<" ";
		b[a]=1;
	}
	return 0;
}

```

### [结果](https://www.luogu.com.cn/record/96647581)


## 第二次尝试

### 分析
上一次尝试之所以 $\color{#052242}TLE$ 了，是因为循环找 `b[a]` 的时间太长了，复杂度 $O(nm)$ 满足不了题目要求，所以我只要把这个 $m$（`while(b[a]) a++;`）去掉，就可以用 $O(n)$ 的时间复杂度 就能 $\color{#52C41A}AC$ 了

怎么把这个 $m$（`while(b[a]) a++;`）去掉

可以用排序

上一项如果 $\geqslant$ 这一项，本项=上一项+1

最后再整理就行了

### 实现

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int num,ind;
}a[400010];
int n, b[400010];

bool cmp(node a,node b){
	if(a.num<b.num) return 1;
	else return 0;
}

int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i].num;
		a[i].ind=i;
	}
	sort(a,a+n,cmp);
	b[a[0].ind]=a[0].num;
	for(int i=1;i<n;i++){
		if(a[i].num>a[i-1].num) b[a[i].ind]=a[i].num;
		else{
			a[i].num=a[i-1].num+1;
			b[a[i].ind]=a[i].num;
		}
	}
	for(int i=0;i<n;i++) cout<<b[i]<<" ";
	return 0;
}

```

### [结果](https://www.luogu.com.cn/record/96651505)

---

## 作者：frankchenfu (赞：0)

本题可以使用时间复杂度为$\Theta (n\cdot log_2 n)$的算法解决。


------------

我们首先考虑本题出现的问题是什么。如果每个人希望要得到的rating各不相同，那么就是每个人想要的rating之和。但是，问题在于，如果有两个人的rating相同，那么必须要有一个人的rating得到的比期望值更高。在最差情况下，如果n个人的期望相同，那么一共就需要$\displaystyle\sum_{i=0}^{n-1}a_i+i$.

接下来我们来考虑如何避免重复。我们将数组排序，发现如果前一个人的最终rating（$b_{i-1}$）大于后一个人的期望rating（$a_i$），那么后一个人的最终rating（$b_i$）一定是$\ge b_{i-1}+1$。

证明如下：易知$b_i \ne b_{i-1}$。如果$b_i$可以选择$<b_{i-1}$的任意数$c$，那么说明$a_i<a_{i-1}$（不然$b_{i-1}$就可以选择$c$），与之前排序之后$a_i\le a_{i-1}$不符，所以一定只能选$b_{i-1}+1$。

那么如果$a_i>b_{i-1}$呢？那么$b_i$就取$a_i$就好了。

所以最后递推方程就是$b_i=max(b_{i-1}+1,a_i)$。

所以我们刚才的讨论都基于排好序的基础，所以我们还需要备份原数组，然后递推完再根据原数组顺序输出即可。

------------
代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=300010;
int b[MAXN];

struct D
{
    int num,val;
}data[MAXN];
bool cmp1(const D &a,const D &b)
{
    return a.num<b.num;
}
bool cmp2(const D &a,const D &b)
{
    return a.val<b.val;
}

int read()
{
    int res=0;char ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        res=(res<<3)+(res<<1)+ch-'0';
        ch=getchar();
    }
    return res;
}

int main()
{
    int n=read();
    for(int i=1;i<=n;i++)
    {
        b[i]=read();
        data[i].num=i;
        data[i].val=b[i];
    }
    std::sort(b+1,b+n+1);
    for(int i=1;i<=n;i++)
        if(b[i]-b[i-1]>1)
            b[i]=b[i];
        else
            b[i]=b[i-1]+1;
    std::sort(data+1,data+n+1,cmp2);
    for(int i=1;i<=n;i++)
        data[i].val=b[i];
    std::sort(data+1,data+n+1,cmp1);
    for(int i=1;i<=n;i++)
        printf("%d ",data[i].val);
    return 0;
}
```

---

