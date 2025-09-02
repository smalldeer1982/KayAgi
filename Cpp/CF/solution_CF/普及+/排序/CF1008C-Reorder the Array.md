# Reorder the Array

## 题目描述

**题目大意：**

给定一个序列，序列里的元素可以以任意顺序重新排好

序列里某位置排序后的数可能会大于原数，问这样的位置最多能有多少个

## 样例 #1

### 输入

```
7
10 1 1 1 5 5 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1 1 1 1 1
```

### 输出

```
0
```

# 题解

## 作者：_Aghost (赞：7)

手推几个数，可以发现就是总数减去出现最多的那个数出现的次数。
（用map存一下就行）
~~应该是最短的代码吧。~~
```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
map<int,int> q;
int n,cnt=1,maxn,a[100010];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) q[a[i]]++,maxn=max(maxn,q[a[i]]);
	printf("%d\n",n-maxn);
}

```


---

## 作者：chengni (赞：7)

这题可以 $O(n)$ 处理，不用二分

首先很明显肯定是大的数对应原本小的数，将数组从大到小排个序先

我们可以认为操作是这样的：第一大的数对应第二大的，第二大的数对应第三大的，以此类推

但是有些数字是相同的，所以我们不能这么做

用一个 $l$ 来表示当前被用来对应的数字用到了第几个， $O(n)$ 扫一遍就行了

如果当前可以对应就对应，如果当前不能就不管这个数了

但是很不幸排序是 $nlog_n$ 的，所以还是 $nlog_n$

代码如下

```cpp
int a[101010];

bool cmp(int a,int b){
	return a>b;
}

int l=1;

int main(){
	int n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	sort(a+1,a+n+1,cmp);
	int s=0;//计数
	for(int i=2;i<=n;i++){//第一个数肯定不能被对应
		if(a[l]>a[i]) {//用第 l 个数对应第 i 个数
			s++;
			l++;
		}
	}
	cout<<s;
	return 0;
}

```




---

## 作者：codesonic (赞：2)

~~当时比赛的时候全房间只有我写二分，还以为自己要被叉死了~~

一句话题意：给n个数，$[a_1,a_2,a_3...a_n]$,重新排列成$[b_1,b_2,b_3...b_n]$，使得满足$[b_i>a_i]$的$i$值最多

因为原数组是无序的，所以可以对原数组进行排序，对于每一个数，选择满足没有被选过且比他小的最大数，发现排序后这样是有序的，所以可以二分做

我们可以只二分比小于等于它的部分，时间复杂度$O(nlogn)$

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>

using namespace std;

int n;
int a[100100];
int c[100100];

int judge(int l,int r,int x){
    int mid=(l+r)>>1;
    if(l==r&&a[r]<x&&!c[r]) return l;
    else if(l+1==r&&a[r]<x&&!c[r])return r;
    else if(l+1==r&&a[l]<x&&!c[l])return l;
    else if(l+1==r) return -1;
    else if(l==r) return -1;
    if(a[mid]==x||c[mid]) return judge(l,mid-1,x);
    else return judge(mid,r,x);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    int ans=0;
    sort(a+1,a+1+n);
    for(int i=n;i>=2;i--){
        int tmp=judge(1,i-1,a[i]);
        if(tmp==-1) break;
        c[tmp]=1;ans++;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：_xbn (赞：1)

话说这题不是 upper_bound 的裸题吗，怎么没有人用 upper_bound。

首先介绍一下 upper_bound 的作用，它可以在一个升序数组中找到大于给定值的第一个元素，返回它的下标。

再回到本题，我们有一个贪心想法就是先给数组排序，为了使答案尽量大，我们肯定截取数组的后一段与数组前一段比较。

那具体从那个位置为起点呢？想到 upper_bound 的作用，我们可以找到第一个大于 $a(1)$ 的位置作为起点之后暴力比较就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200002;
int n, m, k, p, ans, sum, t, tot, cnt, a[N], b[N], c[N], d[N], l;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch))
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(isdigit(ch))
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
int main()
{
    n = read();
    
    for(int i = 1; i <= n; i++)
    {
        a[i] = read();
    }
    sort(a + 1, a + n + 1);
    int t = upper_bound(a + 1, a + n + 1, a[1]) - a;
    l = 1;
    while(t <= n)
    {
        if(a[l] < a[t])
        {
            ans++;
            l++;
            t++;
        }
        else t++;
    }
    cout << ans;
    return 0;
}
```




---

## 作者：Bitter_Tea (赞：1)

 我的基本思路是**贪心**


很显然，我们应该先给小的数匹配重新排列后比它大的值，这样一定是**最优的**。

因为假设我们先给第二小的数匹配比它大的值，最理想的情况也是仅仅能和先给最小的匹配效果一样，而其他情况则会匹配数量更少。


于是就很简单了:我们先对数组$a$从小到大**排序**，然后维护一个变量$loc$表示我们当前较大值的位置，然后对数组$a$从前向后依次匹配即可。

其实没有那么复杂，就是**从前向后扫一遍**。

下面给出我的代码:

$Code$
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int n,a[N],ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	int loc=0;
	for(int i=1;i<=n;i++)
	{
		loc++;
		while(a[loc]<=a[i]&&loc<=n) loc++;
		if(a[loc]>a[i]) ans++;
		if(loc>n) break;
	}
	printf("%d\n",ans);
	return 0;
}

```


---

## 作者：pengyule (赞：1)

可以证明，如果我们用较小的数去对应较小的数，较大的数去对应较大的数，可以获得最大的收益。

具体来说是这样的，首先我们对 $a$ 数组排序，然后我们用第二小的数去比第一小的数，第三小的数去比第二小的数，$\ldots$，第 $n$ 小的数去比第 $n-1$ 小的数。

好，我们就来模拟一下这个过程。

二号对一号，二号比一号大，匹配成功，匹配下个；

三号对二号，三号比二号小，匹配成功，匹配下个；

四号对三号，四号等于三号，不大于它，咋办？我们是应该继续用五号对三号还是用五号对四号呢？答案是显然的，四号会比三号大（或等于），那么我们五号比三号大的可能性一定是大于（或等于）五号比四号大的可能性的。这便是核心策略，只要匹配不成功，我们就用下一小的数对当前的数，还不成功就一直这样。

完整代码。
```
#include <iostream>
#include <algorithm>
using namespace std;
int a[100010];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    int j=2,ans=0;
    for(int i=1;i<=n-1 && j<=n;i++,j++) 
        if(a[j]>a[i]) ans++;
        else i--;
    cout<<ans<<endl;
    return 0;
}
```
谢谢观看。

---

## 作者：liyichun001 (赞：1)

看别人没用优先队列，那我就用吧。

思路：贪心，用优先队列不断判断统计即可。
```cpp
#include<iostream>
#include<queue>
#include<algorithm>
#define INF 0x3f3f3f3f
#define LL long long
using namespace std;
priority_queue <int,vector<int>,greater<int> > q;
LL a[100010];
int main() {
	int n,num=1,ans=0;
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>a[i];
		q.push(a[i]);
	}

	sort(a+1,a+1+n);

	for(int i=1; i<=n; i++)
		if(a[i]==a[1])
			q.pop();

	if(q.empty()) {
		cout<<0<<endl;
		return 0;
	}

	for(int i=1; i<=n&&q.size()!=0; i++) {
		if(q.top()>a[i]) {
			ans++;
			q.pop();
		} else {
			q.pop();
			i--;
		}
	}
	cout<<ans<<endl;
	return 0;
}

---

## 作者：BigJoker (赞：0)

# Solution

由于对于任意一种排列都会有至少一组排列是答案，所以考虑对无序的数组进行排序。

这里我们采用从小到大。

那么有一种贪心的思想，我们用尽可能接近数的作为比它大的数。

所以让一个指针 $r$ 从 $n\sim 1$，遇到 $a_r>a_i$ 的情况就将 $r-1$。

最后的答案就是 $n-r$，即总共的数减去已经处理过的数。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,r;
int a[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	r=n;
	for(int i=n;i>=1;i--) if(a[r]>a[i]) r--;
	printf("%d",n-r);
	return 0;
}
```

---

## 作者：Chocola4ever (赞：0)

## [题目](https://www.luogu.com.cn/problem/CF1008C)大意

>   给定一个序列，序列里的元素可以以任意顺序重新排好。
>
>   序列里某位置排序后的数可能会大于原数，问这样的位置最多能有多少个？

## 思路

首先，要想达到**排列后大于原数的位置的个数**最多，可以考虑将次小的数放在最小的位置上，将第三小的数放在次小的位置上 $\dots$

我们先把数列从小到大排序，然后从左到右扫一遍，当 $a_{i-1}<a_i$ 时，就说明 $a_i$ 可以放到 $a_{i-1}$ 上。

但是这会有一个问题：如何处理**相同的数**？

显然，这种方法通过不了这组数据：

```
6
1 1 1 2 3 3
```

正解答案为 $3$ ，而这种方法只能得到答案 $2$ 

**问题出在什么地方？**

我们需要将数字**尽可能向左地**匹配，而不是每次只尝试匹配 $a_{i-1}$ ，这样就能得到最大答案。

## 题解

我们先将整个数列**从小到大**排序，然后定义一个 $cnt$ ，当 $a_{cnt}<a_i$ 时，说明我们可以把 $a_i$ 放到 $a_{cnt}$ 的位置上。

核心代码：

```cpp
int cnt=1,ans=0;
sort(a+1,a+1+n);//从小到大排序
for (int i=1;i<=n;++i)
	if (a[i]>a[cnt])
		++cnt,++ans;
```



---

## 作者：小坦克 (赞：0)

### **题意**：给你一串数字，打乱顺序之后，每个位置上的数字如果比原来大的话，结果$+1$.

**在进行排序之后优先使用最小的数字进行对比即可。**

---------
**$Code:$**
```cpp
    #include<iostream>
    #include<algorithm>
    #include<cstring>
    #include<string>
    #include<cstdio>
    #include<stack>
    #include<cmath>
    #include<set>
    #include<map>
    using namespace std;
    #define inf 0x3f3f3f3f
    #define ll long long
     
    int a[100005];
    int main()
    {
    	int n,i,j=0;
    	cin>>n;
    	for(i=0;i<n;i++)
    	cin>>a[i];
    	sort(a,a+n);
    	for(i=1;i<n;i++)
    	{
    		if(a[i]>a[j])
    		j++;
    	}
    	cout<<j<<endl;
    	return 0;
    }
  ```
  ------
  **简洁版：**
  ```cpp
 #include<bits/stdc++.h>
using namespace std;
int a[100005];
int main(){
	int n,i,j=0;
	cin>>n;
	for(i=0;i<n;i++) cin>>a[i];
	sort(a,a+n);
	for(i=1;i<n;i++)
		if(a[i]>a[j])
			j++;
	cout<<j<<endl;
	return 0;
}
```
  
###   完结撒花！！！

---

## 作者：MuYC (赞：0)

#### 前言

挺水的一道题。

#### 思路

因为可以任意交换元素，那么不妨就直接把元素排序。

本着贪心的原则，我们总是希望一个数能够被自己的后继(比它大的最小的数)来填。

**怎么找后继？**

因为是序列是排好序的，拿一个指针，指针从$1$开始。

从$2$到$n$遍历一遍，第一个扫到的大于这个指针的数肯定就是目前指针指到的数的后继。

如果扫到了当前指针指到的数的后继，那么指针往后移动，同时不难发现，指针指的数的后继随着指针的移动不断在变大，所以这样扫是对的。

总的时间复杂度是:O($nlog(n) + n$)，瓶颈在排序上。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int a[100005];
int main()
{
	cin >> n;
	for(int i = 1 ; i <= n; i ++)cin >> a[i];
	sort( a + 1 , a + 1 + n );
	int now = 1,Ans = 0;
	for(int i = 2 ; i <= n ; i ++)
		if(a[i] > a[now])now ++ , Ans ++;//指针扫描即可
	cout << Ans;
	return 0;
}
```

---

## 作者：happybob (赞：0)

这个题目一看就是大的对小的，所以要从大到小排序，因为已经有人用sort了，这里就来一发map+桶排吧！

先来解释一下桶排为什么用map，首先这道题目限时2s，正常桶排是要从1~MAXai，这里ai≤10^9，1s就用掉了，加上两遍n次遍历，2s可能会TLE。

而map有个好处：

```cpp
map <int, int> mp;
  
mp[1] = 1;
mp[3] = 3;
```
mp[2]是空的，所以如果使用迭代器遍历输入数据没有的下标就不用花时间遍历了！！！

代码如下：

```cpp
#include <iostream>
#include <map>
using namespace std;

map <int, int> box, mp;

int main()
{
    int n, a, cur = 0, x = 1, ans = 0;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> a;
        mp[a]++;
    }
    for(map <int, int>::reverse_iterator it = mp.rbegin(); it != mp.rend(); ++it)
    {
        int v = it -> first;
        int w = it -> second;
        for(int j = 1; j <= w; j++)
        {
            cur++;
            box[cur] = v;
        }
    }
    for(map <int, int>::iterator it = box.begin(); it != box.end(); ++it)
    {
        if(box[x] > it -> second)
        {
            ans++;
            x++;
        }
    }
    cout << ans << endl;
    return 0;
}
```

这里说下：

```cpp
reverse_iterator
```
因为我们要从大到小排序，桶排迭代器肯定要从rbegin到rend，而map的iterator不支持反向遍历，要用reverse_iterator
  

---

