# Polycarp Training

## 题目描述

Polycarp wants to train before another programming competition. During the first day of his training he should solve exactly $ 1 $ problem, during the second day — exactly $ 2 $ problems, during the third day — exactly $ 3 $ problems, and so on. During the $ k $ -th day he should solve $ k $ problems.

Polycarp has a list of $ n $ contests, the $ i $ -th contest consists of $ a_i $ problems. During each day Polycarp has to choose exactly one of the contests he didn't solve yet and solve it. He solves exactly $ k $ problems from this contest. Other problems are discarded from it. If there are no contests consisting of at least $ k $ problems that Polycarp didn't solve yet during the $ k $ -th day, then Polycarp stops his training.

How many days Polycarp can train if he chooses the contests optimally?

## 样例 #1

### 输入

```
4
3 1 4 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5
1 1 1 2 2
```

### 输出

```
2
```

# 题解

## 作者：C3OG_YB (赞：2)

### CF1165B 题解 ###
这是一道贪心题，为了让做的比赛最多，我们要对数组进行从小到大排序。用 `if` 判断一下，如果可以参加比赛，就将储存答案的 `ans+1`。下面是代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2000005];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];//输入 
	sort(a+1,a+n+1);//将数组从小到大排序 
	int ans=1;//从第一天开始 
	for(int i=1;i<=n;i++){
		if(a[i]>=ans)ans++;//如果符合题目要求，那么答案+1 
	}
	cout<<ans-1;//由于从第一天开始 ，所以答案要-1 
}
```

---

## 作者：BlanketRice (赞：2)

### 前言
非常水，大水大水，太水了

### 题意
就是第 $ k $ 天打比赛能做 $ k $ 道题，给定 $ n $ 场比赛，每场比赛的题目数量 $ a_{i} $，第 $ i $ 场比赛要求 $ k \le a_{i} $，若达到不符合要求的比赛就不打了，直接放弃掉了。问最多能打几天？

### 思路
这道题是贪心算法，为了使能打的比赛数量最大化，我们从小到大排序后就可以使打比赛的天数最大化。在根据题目描述进行模拟，`if` 语句判断条件是否满足，如果满足 `++ans` 否则退出程序。很简单吧，下面是代码。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1919810];
signed main () {
    int n;
    cin >> n;
    for (register int i = 1; i <= n; ++ i) cin >> a[i];
    sort (a + 1, a + 1 + n);
    int ans = 0;
    for (register int i = 1; i <= n; ++ i)
        if (a[i] >= ans + 1) ++ ans;
    cout << ans << endl;
    return 0;
}
```

---

## 作者：OoXiao_QioO (赞：2)

# 思路
这道题其实蛮水的，显然是一道贪心题，因为题目说明了我们可以选择任意的一个比赛，而且还要求 $a_i \ge k$，于是我们就可以给 $a$ 数组从小到大排个序（这样可以保证参加比赛数目最大化），再来根据题目的条件进行训练天数 $+1$ 或者终止训练的决定，最后输出一下天数就好了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	//定义
	
	int n,i,days,a[200001];//days表示训练天数。 
	
	//输入

	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i];

	//变量初值 
	days = 1;//根据题目描述，天数是从 1 开始，所以 days 初值为 1。 
	
	//处理部分 
	
	sort(a+1,a+1+n);//根据贪心的思想，我们先给数组排个序，让数组内最小的数对上最小的天数 days(题目中的 K)，是最优方案。 
	for(i=1;i<=n;i++)//循环 
	{
		if(a[i]>=days)//根据题目描述 来进行判断 
			days++;
	}
	
	//输出
	 
	cout<<days-1<<endl;//因为天数是从 1 开始的，所以最后要减去 1。 
	return 0;//结束 
}
```


---

## 作者：scpchangyi (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1165B)
### [思路]
这是一道贪心~~水~~题，先对 $ a_i $ 进行排序，$ ans $ 用来记录天数和当做题目中的 $ K $，按题目的指示操作，最后将 $ ans $ 减去第一天也就是 $ ans - 1 $，输出就完成了。（代码里有注释）

### [代码]
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],ans;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);//从小到大排序 
    for(int i=1;i<=n;i++)
    {
    	if(a[i]>=ans)ans++;//按题目操作 
    }
    cout<<ans-1;//减去第一天 
    return 0;
}
```

---

## 作者：togeth1 (赞：0)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF1165B)

### [题意解析]
第 $k$ 天能做 $k$ 道题，如果第 $i$ 场比赛大于 $k$，那么就可以打这场比赛，否则就放弃，不打了。问这个人最多能打多少场比赛。

### [思路分析]
这是一道显而易见的~~水~~贪心，只要我们当前的 $a_i$ 越小，他能做到的天数就越多，也就是**局部最优解就是全局最优解**，而且没有后效性，所以不用考虑动态规划。所以我们需要做的操作就变成了：

1. 把我们的 $a_i$ 排序；
2. 从小到大循环，算出最多可以打的天数。
### [贴上代码]
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],cnt;
/*数组要开到 2*100000 那么大，不要开小了*/
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++)cin>>a[i];
	sort(a+1,a+1+n);
	/*排序*/ 
	for(int i=1; i<=n; i++)
		if(cnt<a[i])cnt++;
	/*算出最多可以打的天数*/
	cout<<cnt;
	return 0;
}
```

---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门 ](https://www.luogu.com.cn/problem/CF1165B)

采用**贪心**思路。

我们先把比赛题目**排序**，把 $ans$ 设为 $1$，既能表示天数，又能记录答案，一举两得。

然后按照题目要求判断就行了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	int ans=1;
	for(int i=1;i<=n;i++)
		if(a[i]>=ans)ans++;
	cout<<ans-1;
	return 0;
}
```


---

## 作者：Jerry_heng (赞：0)

这题其实就是一个贪心~~水~~题。

要求每天匹配的 $a_i \ge k$，那么就让 $a_i$ 是能取的值中最小的。

原因很简单，小的给小的用，大的给大的用。

那么就先给 $a$ 数组排序，然后通过循环解决（详见代码）。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200001];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);//从小到大排序
	int k=1;//记录天数
	for(int i=1;i<=n;i++){
		if(a[i]<k)continue;
		k++;
	}
	cout<<k-1;//别忘减一
	return 0;
}
```


---

## 作者：qwq___qaq (赞：0)

好像没有人用 `multiset` 写题解？

我们考虑两个天数 $a,a'(a'>a)$，同时有两个问题数 $b,b'(b'>b)$，那么此时我们可以发现：$a$ 匹配 $b$ 显然比 $a$ 匹配 $b'$ 更优。

那么我们就有了一个初步的思路：我们可以在第 $k$ 天查找在所有比赛中的最小的 $\ge k$ 的数，然后完成掉它后就删除。

注意到这时这时我们需要一个求后继以及删除元素的数据结构，于是我们可以采用~~平衡树~~ `multiset` 维护，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,ans=1;
multiset<int> s;
int main(){
	scanf("%d",&n);
	for(int i=1,a;i<=n;++i)
		scanf("%d",&a),s.insert(a);
	while(s.lower_bound(ans)!=s.end()){
		s.erase(s.lower_bound(ans));
		++ans;
	}
	printf("%d\n",ans-1);
	return 0;
}
```

---

## 作者：Beep_Monkey (赞：0)

这道题显然是个贪心。

首先把 $a$ 数组排序，把小的放在前面

接着暴力枚举，若 $a_i \ge ans$，则 $ans$ 加 $1$ 。

注意 $ans$ 初值为 $1$ ,答案是 $ans-1$。

## 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=1,a[200005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		if(a[i]>=ans)
			ans++;
	printf("%d",ans-1);
	return 0;
}
```


---

## 作者：ForeverCC (赞：0)

因为每天能完成的题目是递增的，所以可以先解决题目数量小的比赛，尽可能的让 $k \le a_i$。

先把 $a$ 排序，遍历 $a$。如果可以解决（$k \le a_i$）就把 $k+1$，最后输出解决的比赛次数（$k-1$）即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],t=1;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
        t+=(a[i]>=t);
	printf("%d\n",t-1);
	return 0;
}
```


---

## 作者：liuyongle (赞：0)

#### 思路分析

对数组进行排序，我们可以在变量 $pos$ 中维护Polycarp可以训练的最后一天，其中 $pos$ 赋初始值为1。以不降序的顺序遍历排序数组的所有元素，如果当前元素 $a_i \geq pos$，则将 $pos$ 增加 $1$。答案将是 $pos-1$。

#### 完整代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int n,pos=1;

int main() {
	cin>>n;
	vector<int> a(n);
	for(int i=0;i<n;++i)
		cin>>a[i];
	sort(a.begin(),a.end());
	for(int i=0;i<n;++i)
		if(a[i]>=pos)
        	++pos;
	cout<<pos-1<<endl;
	return 0;
}
```

---

## 作者：A_Big_Jiong (赞：0)

# 题目大意

有n个场比赛，第i场比赛有ai个题目。

你需要第i天刷i道题，比如第一天需要做1道题，第10天需要做10道题，~~三年后需要做1095~1096道题（口算，可能会糊）~~。

每天只能参加一场未参加过的比赛，求问你能坚持几天

# 思路
### 贪心大法好！！！
- 因为时间越靠前你需要的题目数越少

- 显而易见，你应该尽可能的参加题目总数少的比赛

- ai可以支持1~ai天的做题，而aj=ai-k(k>0,k为整数)只能支持1~aj即1~ai-k天

- 数值越大能适应的天数越多，那么可应用型越大，就更应该往后用

# 代码

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<map>
#include<set>
#include<stack>
#include<queue>
#include<vector>
#include<string>
using namespace std;
const int maxn=200005;
int n;
int a[maxn];
int head=1;//定义一个指针
int ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)  scanf("%d",&a[i]);
	sort(a+1,a+1+n);//贪心，把小的放到前面
	for(int i=1;i<=n;i++){
		while(a[head]<i)  head++;//讲不足i的舍去
		if(head>n){
			printf("%d\n",ans);//一旦遍历完这n个数，输出个数
			return 0;
		}
		head++;
		ans++;//纪录可以延迟的天数加一天
	}
	printf("%d\n",n);//如果正好每天都能有比赛，直接输出天数
	return 0;
}
```


---

