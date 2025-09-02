# Create The Teams

## 题目描述

There are $ n $ programmers that you want to split into several non-empty teams. The skill of the $ i $ -th programmer is $ a_i $ . You want to assemble the maximum number of teams from them. There is a restriction for each team: the number of programmers in the team multiplied by the minimum skill among all programmers in the team must be at least $ x $ .

Each programmer should belong to at most one team. Some programmers may be left without a team.

Calculate the maximum number of teams that you can assemble.

## 样例 #1

### 输入

```
3
5 10
7 11 2 9 5
4 8
2 4 2 3
4 11
1 3 3 7```

### 输出

```
2
1
0```

# 题解

## 作者：Accepted_Error (赞：2)

[传送门](https://www.luogu.com.cn/problem/solution/CF1380C)

## 题目分析
题目要求能分成最大的组数，因此我们可以使用贪心的思路解决。

我们可以先以程序员的技能来**从大到小**排序，为什么呢？因为如果让技能大的程序员和技能小的程序员分到一组的话，需要的人数就肯定会比技能大的在一起的情况多，就达不到最多的组数。

再进行判断：

如果技能$\times$人数超过 $x$，也就是能组成一组，那么就进行下一组判断，否则增加人数再进行判断，这样就会达到最优策略。
## AC Code
```cpp
#include<iostream>
#include<cstdio>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#include<utility>
#include<cmath>
#include<cstring>
#include<string>
#include<map>
#include<set>
#include<cstdlib>
#define ll long long
using namespace std;
const int N=1e5+10;
int t,n,x,cnt1,cnt2,minn=1e9;
int a[N];
bool cmp(int x,int y)
{
	return x>y;
}
int main()
{
	cin>>t;
	while(t--)//多组输入 
	{
		cnt1=0;
		cnt2=0;
		minn=1e9;
		cin>>n>>x;
		for(int i=1;i<=n;++i)
		{
			cin>>a[i];
		}
		sort(a+1,a+n+1,cmp);//排序 
		for(int i=1;i<=n;i++)
		{
			minn=min(minn,a[i]);
			cnt2++;//cnt2记录人数 
			if(minn*cnt2>=x)//能组成一组 
			{
				minn=1e9;
				cnt2=0;
				cnt1++;
			}
		}
		cout<<cnt1<<endl;
	}
	return 0;
}
```

---

## 作者：Yizhixiaoyun (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1380C)

## 题目分析

本题数据量较大，所以我们不能使用暴力。本题的方法使用**贪心**。

因为我们需要让组数尽量多，所以一旦多余 $x$ 我们就计入，可以确保组数最多。

我们先将数据**排序**，然后从高向低枚举，如果**人数**乘**当前程序员的技能**大于等于 $x$ ，则算作一种情况。

## 注意事项

数组记得不要开小！

## 贴上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
int T;
int n,x,a[maxn];
int main(){
	cin>>T;
	while(T--){
		cin>>n>>x;
		for(register int i=1;i<=n;++i) cin>>a[i];
		sort(a+1,a+n+1);
		int ans=0,cnt=1;
		for(register int i=n;i>=1;--i){
			if(cnt*a[i]>=x){
				ans++;cnt=1;
			}
			else cnt++;
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：linyihdfj (赞：1)

## C.Create The Teams ##
[博客食用效果更佳](https://www.cnblogs.com/linyihdfj/p/16450318.html)
### 题目描述： ###
[原题面](https://codeforces.com/problemset/problem/1380/C)
### 题目分析： ###
为了让组数更多，那么很显然我们要按能力值从大到小进行分组，如果当前选择的这一部分可以组成一组就组成一组，然后考虑下一组。这样肯定就是最优的策略，因为如果不是从大到小就可能会让很强的和很弱的分为一组那么就浪费了这个很强的人。
### 代码详解： ###
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN = 1e5+5;
const long long INF = 1e9+5;
long long a[MAXN];
bool cmp(long long l,long long r){
	return l > r; 
}
int main(){
	long long t;
	cin>>t;
	while(t--){
		long long n,x;
		long long ans = 0;
		cin>>n>>x;
		for(long long i=1; i<=n; i++){
			cin>>a[i];
		} 
		sort(a+1,a+n+1,cmp);
		long long now_mn = INF,now_size = 0; 
		for(long long i=1; i<=n; i++){
			now_mn = min(now_mn,a[i]);
			now_size++;
			if(now_mn * now_size >= x){
				now_mn = INF;
				now_size = 0;
				ans++; 
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：liukangyi (赞：0)

# 题目大意
给你 $t$ 组数据，每组数据中有一个长度为 $n$ 的数组 $a$ 与一个数字 $x$，现在要将 $a$ 数组进行分组，而且必须保证分得的每一组中**最小数值乘数值个数**要大于或等于 $x$。现在想让你求出最多能分成的组数。


------------
# 分析
这道题给了我们分组要求，所以我们完全可以按照要求来模拟分组情况，但要怎么枚举呢？遍历的顺序又是怎么样呢？其实很简单！因为它是要涉及到最小数值，所以我们要**从大到小对数组进行遍历**，这样才能确保在枚举过程中最小值尽量大，从而更容易达到大于或等于 $x$ 的要求。顺序确定好了，但具体怎么模拟呢？我们在遍历过程中，因为是下降序列，所以当前下标指向的值即为最小值，我们可以看看**当前数值乘当前组内数值个数**（这里我们可以用计数器来统计个数）是否大于或等于 $x$，如果是的话，就证明符合要求了，可以将答案组数加加，并把计数器清 $1$，否则的话就继续将计数器加加，直到满足条件。最后输出答案即可。


------------
**注意：计数器初始化与中途初始化都必须要清 $1$，而不是清 $0$，因为组内个数是要算上遍历到的那一个数值的，所以得先算上 $1$ 个。**


------------
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x;
int a[100010]; 
//定义变量 
int main(){
	cin>>t;
	while(t--){
		int res=0,count=1; //初始化。注意计数器要清1 
		cin>>n>>x;
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		sort(a+1,a+1+n,greater<int>()); //按倒序排序 
		for(int i=1;i<=n;i++)
			count*a[i]>=x?(res++,count=1):(count++); //如果符合要求，那么答案数+1且计数器清1。否则计数器++  
		cout<<res<<'\n'; 
	}
	return 0;
}

```


---

## 作者：togeth1 (赞：0)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF1380C)

### **[题意解析]**
让我们对 $n$ 个程序员进行分组，要求分的组中的最小技能值乘以组员人数大于 $x$，要求我们分的组数尽量大。

### **[思路分析]**
很明显，这是一道贪心题。那我们考虑是让技能值大的程序员和技能值小的程序员分在一起吗？显然不是，如果让技能值大的程序员和技能值小的程序员分在一起，那需要的组员人数就会更多，这显然不是最优解。那我们就考虑让技能值大的程序员分在一起，那需要的组员人数肯定会少些，让后面技能值少的程序员可以凑多几组。所以我们只需要把 $a_i$ 进行**从大到小**的排序，再把技能值大的分在一组，统计组数就好了。

### **[贴上代码]**
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,x,a[100010];
bool cmp(int a,int b){return a>b;}
/*大到小*/
int main()
{
	cin>>T;
	while(T--){
		cin>>n>>x;
		for(int i=1; i<=n; i++)cin>>a[i];
		int s=1,ans=0;
		/*注意一开始一个组最少有一个人*/
		sort(a+1,a+1+n,cmp);
		/*从大到小进行排序*/
		for(int i=1; i<=n; i++){
			if(s*a[i]>=x)ans++,s=1;/*清1*/
			else s++;/*人数加1*/
		}
		cout<<ans<<"\n";
	}
	return 0; 
}
```


---

## 作者：lmndiscyhyzdxss (赞：0)

## 题目分析
题目求最大组数，我们可以使用贪心解决。

我们可以先从大到小排序，为什么呢？因为如果让技能大的程序员和技能小的程序员分到一组的话，还是按弱的程序员计算，就浪费了这个强程序员，需要的人数就肯定会比技能大的在一起多，就达不到最多的组数。

再循环判断：

如果最低技能数 $ \times $ 人数超过 $ x $，也就是能组成一组，组数增加，那么就进行下一组判断，否则增加人数再进行判断，这样就会达到最优策略。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,a[100010],l,g;
int main(){
	cin>>t;
	for(int j=1;j<=t;j++)
	{
		cin>>n>>x;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+n+1);l=0,g=1;//排序和初始化 
		for(int i=n;i>=1;i--)//从大到小循环 
		{
			if(g*a[i]>=x)l++,g=1;//因为是从小到大排序的，省去了求最小值的步骤，分成一组，记录。 
			else g++;//否则继续 
		}
		cout<<l<<endl;
	}
	return 0;
}
```


---

## 作者：TheShuMo (赞：0)

## 注意
数组至少要开到 $10^5$ 以上，否则会爆空间。

## 思路

这道题的思路是贪心：由于一组程序员的技能点取决于技能点最小的那个程序员，所以很明显如果技能点高的程序员和技能点低的程序员放在了一起。技能点较高的程序员的技能点就被浪费了，所以我们就需要从大到小排序！

每当当前组的技能点大于 $x$ 就新建另一个小组。继续枚举，明显这种情况是最优的。

## 代码
~~丑的要死~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000001];
bool cmp(int a,int b){
    return a>b;
}//从大到小排序
int main(){
    int T;//T组
    cin>>T;
    while(T--){
        int n,x,ans=0,minn=0x3f3f3f3f,dq=0;
        cin>>n>>x;
        for(int i=0;i<n;i++){
            cin>>a[i];
        }sort(a,a+n,cmp);
        for(int i=0;i<n;i++){
            minn=min(minn,a[i]);//取当前最小值
            if(minn*++dq>=x){
                ans++;//组数加1
                minn=0x3f3f3f3f;
                dq=0;//重置
            }
        }cout<<ans<<endl;
    }
}
```



---

## 作者：linyuhao (赞：0)

# 思路
本题使用**贪心**策略。由于人数是一定的，而贡献的是技能最低的程序员。因此要优先选择技能高的。   
对数据 $7,11,2,9,5$。要是考虑 $2$，那么组数只能有 $1$ 组。若选择 $11$ 一组，$9,7$ 一组，$2,5$ 舍去，则有 $2$ 组。
# 代码实现   
对贡献值从大到小进行排序，若满足条件则编为一组。  
**重点** 由于已经排序则组内最小值为新加入的程序员技能。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
bool cmp(int x,int y){
	return x>y;
}
int main(){
  	int t;
  	cin>>t;
  	while(t--){
  		int n,x;
  		cin>>n>>x;
  		for(int i=1;i<=n;i++)cin>>a[i];
  		sort(a+1,a+n+1,cmp);
  		int rs=1,s=0;
  		for(int i=1;i<=n;i++){
  			if(rs*a[i]>=x){
  				s++;
  				rs=1;
  			}
  			else{
  				rs++;
  			}
  		}
  		printf("%d\n",s);
  	}
    return 0;
}

```


---

## 作者：BlanketRice (赞：0)

### 前言
水水水水水，大水！

### 题意
将数组 $ a $ 分组，定义一组的分数为组内最低分数 $ \times $ 人数，并且每组的分数不能小于 $ x $。求最大分组数。

### 思路
通过善良的出题人的种种提示，我们可以猜到，这道题是贪心！！！我们可以将数组 $ a $ 排序，从高到低枚举，为了尽可能让组数最大，我们一组的分数就要尽可能大，也就是放最大的数进一组。先 `sort` 一下，然后用 `for` 循环枚举数组 $ a $，如果加上这个数该组的分数超过了 $ x $，就默认这个组满人了，不再添加，向下一个组进军，即 `ans++` 如果加上这个数没有到达 $ x $，就将组内人数加 `1` 然后接着枚举即可。

### 代码
用 $ cnt $ 表示组内人数， $ ans $ 记录答案。因为从高到低排序，所以每进一个数都会更新组内最小值，就用 $ a_{i} $ 表示组内最小值即可。

代码他来了：：：

``` cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, x, a[1000005], ans, cnt;
inline bool cmp (int a, int b) {
    return a > b;
}
signed main () {
    ios :: sync_with_stdio (0), cin.tie (0), cout.tie (0);
    cin >> T;
    while (T --) {
        cin >> n >> x;
        ans = 0, cnt = 1; for (register int i = 1; i <= n; ++ i) cin >> a[i];
        sort (a + 1, a + 1 + n, cmp);
        for (register int i = 1; i <= n; ++ i)
            if (cnt * a[i] >= x) ++ ans, cnt = 1;
            else ++ cnt;
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：OoXiao_QioO (赞：0)

# 思路

首先看测试数据，暴力肯定过不了，而且题目说了最多的分组、至少是 $x$ 等短语说明了这道题是一道贪心的题目。

我们不妨这样想，首先给数组从大到小排个序，用 $cnt$ 表示当前小组内人数，用 $s$ 表示最多的组数。此时就可以挨个枚举所有人，只要 $cnt \times a_i < x$，说明小组的人数还不够，此时 $cnt+1$，进行下一次枚举。否则说明小组内人数够了，将 $s+1$，并且组内人数设为 $1$（总不能第一个人不算上吧）。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	//定义
	 
	int n,i,x,t,a[100001],cnt,s;
	
	//输入
	 
	cin>>t;
	
	//处理
	 
	while(t--)
	{
		cin>>n>>x;
		cnt = 1;//先把组内人数设为 1，总不能不算上组内第一个人吧。 
		s = 0;//注意每次循环方案数要清空。 
		for(i=1;i<=n;i++)
			cin>>a[i];
		sort(a+1,a+1+n);//小到大排序。 
		for(i=n;i>=1;i--)//因为我们是从小到大排序，所以要倒着枚举。 
		{
			if(cnt*a[i]<x)//满足不了条件 
				cnt++;//组内人数 +1。 
			else
				s++,cnt = 1;//满足条件，方案数 +1，并且组内人数设成 1。 
		}
		cout<<s<<endl;//输出 
	}
	return 0;
}
```


---

## 作者：cxy000 (赞：0)

题目描述：

输入 $n$ 个数，再输入 $a_i$ 。

然后我们应该这么做：

先排序。排序应从小到大排（直接用 $sort$ 从小到大排序即可）

然后就用贪心从 $a_n$ 开始枚举，如果成立就 $zu$ 增加 $1$。

成立条件：

目前的 $sun$ 值（$sun$ 即个数）乘以目前的最小值 $a_i$（因为从小到大，所以是最小值）大于题目要求即可成立，$zu$ 增加。

最后输出。

所以这道题就没有什么难的了。

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1000100];
int main(){
	int n;
	cin>>n;
	int t,w;
	int zu=0;
	while(n--){
		cin>>t>>w;
		for(int i=1;i<=t;i++){
			cin>>a[i];
		}
		sort(a+1,a+1+t);
		int sun=1;
		for(int i=t;i>=1;i--){
			if(sun*a[i]>=w){
				zu++;
				sun=1;//记得重置默认为1
			}
			else {
				sun++;//增加目前个数
			}
		}
		cout<<zu<<endl;//输出答案！
		zu=0;
	}
	return 0;
}
```


---

## 作者：_lgh_ (赞：0)

### 思路：
贪心，即如果当前累加的人数乘现在程序员的技能大于 $x$ ,就计入并归零。

**证明：**

设每个组最后的技能为 $ans$ 。因为分组越多越好，所以每个组都要尽量 $\ge x$ ，并且保证 $\left\vert {ans-x}\right\vert$  尽量小。于是直接从技能最高的向技能最低的枚举累加就可以了。
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005],n,x,T;
int main()
{
  scanf("%d",&T);
  while(T--)
  {
    scanf("%d%d",&n,&x);
    for(int i=0; i<n; i++) scanf("%d",&a[i]);
    sort(a,a+n);
    int sz=1,ans=0;
    for(int i=n-1; i>=0; i--) if(a[i]*sz*1LL>=x) ++ans,sz=1;
      else ++sz;
    printf("%d\n",ans);
  }
}
```


---

## 作者：lgmulti (赞：0)

这是一个分组问题。组内所有人的最低技能越大，这个组需要的人数就越少，这样的问题具有单调性，所以我们需要先排序。

排序完成后，就可以按顺序分组了，设$val_i$为从第$i$项开始作为一组，需要在第$val_i-1$项结束。当然，如果这组无法结束，则将$val_i$设为$-1$。

```cpp
for(i=0;i<n;i++)
    val[i]=(i+divv(m,a[i])>n ? -1 : j+divv(m,a[i]));
```

接下来，就是找最大组数了，暴力会超时，所以只能用dp。

>状态：设$dp_x$为到$x$为止的最大组数

>转移：$dp_{dp_x}=\max(dp_{dp_x},dp_x+1)$

>初值：$dp_x=0$

>目标：$dp_n$

然后这题就做完了，完整代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int t,n,m;
int a[100005];
int val[100005],dp[100005];

int divv(int a,int b){
    int i,j;
    if(a%b==0)
        return a/b;
    else
        return a/b+1;
}

int main(){
    int i,j;
    cin>>t;
    for(i=0;i<t;i++){
        memset(val,0,sizeof(val));
        memset(dp,0,sizeof(dp));
        cin>>n>>m;
        for(j=0;j<n;j++)
            cin>>a[j];
        sort(a,a+n);
        for(j=0;j<n;j++)
            val[j]=(j+divv(m,a[j])>n ? -1 : j+divv(m,a[j]));
        for(j=0;j<=n;j++)
            if(val[j]!=-1)
                dp[val[j]]=max(dp[val[j]],dp[j]+1);
        cout<<dp[n]<<endl;
    }
    return 0;
}
```

---

