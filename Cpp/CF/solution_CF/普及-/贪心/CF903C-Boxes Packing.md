# Boxes Packing

## 题目描述

Mishka有$n$个空盒子，对于每一个$i(1 \le i \le n)$，第$i$个盒子是一个边长为$a_i$的正方体。

如果满足以下条件，Mishka可以将盒子$i$放入另一个盒子$j$中：

- 第$i$个盒子没有放进另一个盒子里；
- 第$j$个盒子不包含任何其他盒子；
- 第$i$个盒子比第$j$个盒子小$(a_i<a_j )$。

Mishka可以将盒子互相放置任意次数。 他希望尽可能减少可以看见的盒子的数量。 如果一个盒子没有被放入另一个盒子中，则该盒子为可见的。

现请你帮助Mishka确定可见的盒子的最小可能数量。

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
4 2 4 3
```

### 输出

```
2
```

# 题解

## 作者：Register (赞：2)

### ~~很奇怪，做的时候是红题，发题解的时候就是黄题了~~
### 真的只有红题难度！！！一个贪心就搞定了
	这道题就是让我们求最少有几个上升序列（顺序随意）
    因为盒子大小套法是从小到大，等于了就套不进去
    经过排序后：
    这道题如果没有相同的元素，那么结论就是1（1个上升序列）
    如果某处有max个元素相同，则结论就是1（max代表相同元素最多是多少）
	
![](https://cdn.luogu.com.cn/upload/pic/36882.png)

上代码：
```cpp
#include <iostream>
#include <algorithm>//sort、max库
using namespace std;
int n,a[5001],ans=1/*最多的元素*/,sum=1/*目前最多的元素*/;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);//升序排列
	for(int i=1;i<=n;i++)
		if(a[i]==a[i-1]) {sum++;ans=max(ans,sum);}//某某地方加宽了
		else sum=1;//到了下一个元素
	cout<<ans<<endl;
	return 0;
}
```
贪心真简单~~不然本蒟蒻做不起~~

---

## 作者：YUYGFGG (赞：1)

思路：求有几个上升序列，每一个都要尽量长

step1:用multiset排序

step2-1:如果没有相同的元素，上升序列数为1

step2-2:有x个元素相同，则结论就是max(x)

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=1,sum=1;
multiset<int> a;
int main(){
    int tmp;
    cin>>n;
    a.insert(-1);
    for(int i=1;i<=n;i++){
        cin>>tmp;
        a.insert(tmp);
    }
    set<int>::iterator it=a.begin();
    set<int>::iterator it2=it;
    it++;
    for(;it!=a.end();it++,it2++){
        if(*it2==*it){
            sum++;
            ans=max(ans,sum);
        }
        else sum=1;
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：Remake_ (赞：1)

这道题要用贪心？？？

这道题实际上就是一个变形的抽屉原理。

我们想象一下，可见盒子数为$1$是什么情况，情况就是，所有数不重复，然后递增着放就行了，小的放大的里面，这样一直套，一直套到最大的盒子里。

但是当有重复的数怎么办？

我们可以把它划分成多个可见盒子数为$1$的情况，保证每个划分出来的东西都满足其中没有任何重复的数即可。

最后我们应用抽屉原理即可：只有重复次数最多的数才需要考虑，记重复次数最多的数为$max$，我们设其它数的重复次数都等于$max$，那么将正好组出$max$组可见盒子数为$1$的情况，那么既然增加了几个数都是$max$，而又因为重复次数最多的数不能重复在一个可见盒子数为$1$的情况中，所以答案最小是$max$。

既然一个数最大是$max$最小是$max$，所以

## $ans=max$

再利用map数组$mp[i]$记录$i$出现的次数，最终取最大值即可，最后上没压行的代码（为了你们看的方便）：

```cpp
#include<bits/stdc++.h>
using namespace std;
map<long long,long long> mp;
long long a,b[5005],maxn=1;
int main(){
	cin>>a;
	for(int i=1;i<=a;i++){
		 cin>>b[i];
		 maxn=max(maxn,++mp[b[i]]);
	}
    cout<<maxn;
}
```


---

## 作者：fls233666 (赞：1)

要想尽可能的少看到盒子，就要**尽可能把小的盒子装到大的盒子中**，这就要用到**贪心**了。

考虑如何贪心，先分析一下样例：

样例1：显然从最小的盒子开始，逐个套到更大的盒子中即可。

样例2：不看样例解释，可以先把盒子**按大小排序**一遍。得：

	2 3 4 4
    
排序后，从最小的第1个盒子开始，逐个套到更大的盒子中，直到最大的盒子，同样可以得到最优策略。

由此，可以得到大致思路：**按盒子的大小排序，然后按一定顺序对盒子进行决策，即可得到最优答案。**

那么，再次回到我们最初的目标：尽可能把小的盒子装到大的盒子中

**我发现，可以先决策较大的盒子，看看能不能装到其他盒子中，然后再决策较小的盒子。**

为什么可以这样做呢？

因为本人在做此题时，联想到了另一道十分经典的谈心题：[拦截导弹](https://www.luogu.org/problem/P1020)。此题贪心策略与现在这题的贪心策略相同。

按照这个方法贪心，最后可以AC。下面是代码:

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
int main(){
    int n,ans;
    scanf("%d",&n);
    ans=n;
    int a[n];
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    sort(a,a+n);  //读入&从小到大排序
                         
    for(int i=n-2;i>=0;i--)  //从大到小决策
        for(int j=i+1;j<n;j++)
            if(a[i]<a[j]){  //如果能被放入其他盒子
                ans--;  //更新答案
                a[j]=a[i];
                a[i]=0;//标记已放入其他盒子
                break;
            }
    printf("%d",ans);  //输出
    return 0;
}
```


---

## 作者：LeNotFound (赞：0)

### 题目分析

根据题目描述，每个盒子里不可能有两个边长相等的盒子，因为这样就不满足嵌套的要求了。

所以这边长相等的两个盒子最终必定会在两个不同的盒子里，得出结论：答案为最多的重复次数。

考虑边长值域可以使用 `map` 来存，类似计数排序的过程统计重复次数，最后输出最大的即可。

### 代码

```cpp
#include<bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

inline long long read()
{
    long long x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')
        {
            f=-1;
        }
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

map<ll,ll> m;

int main()
{
    ll n=read();

    for(ll i=0;i<n;i++)
    {
        m[read()]++;
    }

    ll ans=0;

    for(auto i:m)
    {
        ans=max(ans,i.second);
    }

    cout<<ans;

    return 0;
}
```

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

有 $n(1\le n\le 5000)$ 个空盒子，第 $i$ 个是边长为 $a_i$ 的立方体。你可以把盒子 $i$ 放进盒子 $j$ 当且仅当

+ 盒子 $i$ 没有被放进别的盒子里
+ 盒子 $j$ 里没有别的盒子
+ 盒子 $i$ 的边长小于盒子 $j$ 的边长($a_i<a_j$)

要求操作若干次之后，最终剩下的盒子个数的最小值。

## 思路1

$O(n^2)$ 暴力模拟，将数组从大到小排序，然后用数组 $em_i$ 来记录盒子 $i$ 是否为空(即里面没有盒子)，0 为空，1 为非空。

最后只需要输出空盒子总数，即满足
```
em[i]==0
```
的 $i$ 的个数即可。

#### 那如果 $1\le n\le 10^5$ 怎么做呢？

## 思路2

用 $map$ 存储 $cnt$ 数组，其中 $cnt_i$ 记录边长 $i$ 出现的次数。答案就是 $cnt_i$ 中的最大值。

接下来证明一下这个思路：设 $cnt_x$ 为最大值，则比边长 $x$ 小的都能够装入盒子，再将边长为 $x$ 的都装到比它大的盒子中去，大的盒子是不够的，则最少每一叠盒子中都有一个边长为 $x$ 的(没有多出来的大盒子)，因此答案就是 $cnt_x$。

## 代码

接下来放上思路 2 的完整代码。思路 1 大家可以自己尝试着去写。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,a[5005];
map<int,int>m;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=0;i<n;i++){
	cin>>a[i];
	m[a[i]]++;
	ans=max(ans,m[a[i]]);
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：Xdl_rp (赞：0)

## 简要题意
共有 $n$ 个盒子，小盒子可以放在大盒子里，一个大盒子可以叠若干个小盒子（类似俄罗斯套娃，但是要一个比一个小），问最后最少有多少个盒子？

solution
------------
先将数组排好序，因为大的可以包住小的，所以只要整一个数组没有相同的就可以一个最大的盒子包完。也就是说，将所有数出现的个数用一个 `q`（`q` 是一个 `map`，数组会爆空间）存起来，最后将 `q` 中的最大值输出就行了（因为相同的不可能在一个集合里）。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1000005];
map<int, int> q;//定义一个q
int main() {
	int n;
	scanf("%d", &n);
	for (register int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);//输入
		q[a[i]]++;//a[i]出现的个数加一
	}
	int ans = 0;//答案
	for (register int i = 1; i <= n; i++) {
		ans = max(ans, q[a[i]]);//打擂台，每次求一个最大值
	}
	printf("%d\n", ans);//输出答案
	return 0;
}
```


---

## 作者：wuwenjiong (赞：0)

## 题意：
有 $n$ 个盒子，并给出它们的大小，要求尽可能的将可见盒子变少，当一个盒子被放入另一个盒子后，它就不可见了。
## 思路：
首先应该排序一下，然后从大到小遍历，当遍历到的盒子没有被装入别的盒子时，再开一个循环,还是从大到小遍历，第一次遇到比它小的盒子就把这个小盒子放进去，然后将这个小盒子设为已被装入其他盒子的状态，最后将可见盒子减一。在此之后，这个盒子就只有比这次的小盒子的大小还小的盒子才能放进，也就是将这个大盒子的大小赋值为小盒子的大小。

思路明白了，接下来就放出部分重点代码
```cpp
sort(a+1,a+n+1);//从小到大排序
for(int i=n;i>1;i--)//倒序枚举
	if(!f[i])//当此时的盒子没有放入别的盒子
		for(int j=i-1;j>=1;j--)
			if(!f[j]&&a[i]>a[j]){//满足能被包含的所有条件
				f[j]=1;//标记一下
				s--;//可见盒子减一
				a[i]=a[j];//之后第i个盒子可装的变为了第j个盒子可装的
}
```
时间复杂度 $O(n^2)$ ， $1\le n\le 5000$ ，不会超时，可过此题。

---

## 作者：傅思维666 (赞：0)

## 题解：

套娃问题。

归纳一下题意，是求最少的严格上升序列使得这些序列覆盖整个原数列。

先排序，发现只有相同的数才会对答案造成影响。否则都可以一层一层套进去。

显然地，如果有若干块相同的数，答案就应该是最大的那块。

所以就代码显然了：

排序用的multiset，就喜欢STL。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=1,sum=1;
multiset<int> s;
multiset<int>::iterator it;
int main()
{
    scanf("%d",&n);
    s.insert(-1);
    for(int i=1;i<=n;i++)
    {
        int tmp;
        scanf("%d",&tmp);
        s.insert(tmp);
    }
    it=s.begin();
    multiset<int>::iterator it2=it;
    it++;
    for(;it!=s.end();it++,it2++)
    {
        if(*it2==*it)
        {
            sum++;
            ans=max(ans,sum);
        }
        else 
            sum=1;
    }
    printf("%d\n",ans);
    return 0;
}
```



---

## 作者：TLMPEX (赞：0)

算法：排序加枚举。

思路：把这个序列排序，排好后用两层循环枚举，看第i个盒子能不能被第j个盒子装下，具体思路见代码。

代码。
```c
#include<bits/stdc++.h>
using namespace std;
int k[5010],vis[5010];
int main(){
	int n,i,j,z;
	cin>>n;
	z=n;
	for(i=1;i<=n;i++)
		cin>>k[i];
	sort(k+1,k+n+1);
	for(i=1;i<n;i++)//枚举每一个盒子
		for(j=i+1;j<=n;j++)//枚举第i+1至第n个盒子
			if(k[j]>k[i]&&!vis[j]){//如果能背装下且没装其他的盒子，则把这个点标记为一，能看见的盒子数减一，兵退出这层循环
				vis[j]=1;
				z--;
				break;
			}
	cout<<z;
}
```


---

