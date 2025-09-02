# Planning The Expedition

## 题目描述

Natasha is planning an expedition to Mars for $ n $ people. One of the important tasks is to provide food for each participant.

The warehouse has $ m $ daily food packages. Each package has some food type $ a_i $ .

Each participant must eat exactly one food package each day. Due to extreme loads, each participant must eat the same food type throughout the expedition. Different participants may eat different (or the same) types of food.

Formally, for each participant $ j $ Natasha should select his food type $ b_j $ and each day $ j $ -th participant will eat one food package of type $ b_j $ . The values $ b_j $ for different participants may be different.

What is the maximum possible number of days the expedition can last, following the requirements above?

## 说明/提示

In the first example, Natasha can assign type $ 1 $ food to the first participant, the same type $ 1 $ to the second, type $ 5 $ to the third and type $ 2 $ to the fourth. In this case, the expedition can last for $ 2 $ days, since each participant can get two food packages of his food type (there will be used $ 4 $ packages of type $ 1 $ , two packages of type $ 2 $ and two packages of type $ 5 $ ).

In the second example, there are $ 100 $ participants and only $ 1 $ food package. In this case, the expedition can't last even $ 1 $ day.

## 样例 #1

### 输入

```
4 10
1 5 2 1 1 1 2 5 7 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
100 1
1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2 5
5 4 3 2 1
```

### 输出

```
1
```

## 样例 #4

### 输入

```
3 9
42 42 42 42 42 42 42 42 42
```

### 输出

```
3
```

# 题解

## 作者：c20191623 (赞：4)

这个题本蒟蒻先特判了一丢丢~

要是人比食物多，那么直接输出0，完全不够嘛。

要是人和食物一样多，那就输出1

然后开始找正解了。

首先另开一个数组记录每种食物出现次数

再慢慢从1开始到最大存活天数，枚举下去，
然后定义sum累加每一类食物够多少天（for i,1~最大食物的数字）
若发现此时sum仍大于n，即仍可以活下去，就更新ans为i，若不满足，直接退粗输出即可

最后，附上~~大妈~~代码

```cpp
#include<bits/stdc++.h>
#define R register
#define num ch-'0'
using namespace std;
void read(int &res){    //读入优化不必在意
    char ch;bool flag=0;
    while(!isdigit(ch=getchar()))
        (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getchar());res=res*10+num);
    (flag)&&(res=-res);
}
int Tim[200],x,Max,maxnum=-0x3fffff;
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    if(n>m){
        putchar('0');
        return 0;
    }
    if(n==m){
        putchar('1');
        return 0;
    }
    for(R int i=1;i<=m;i++){
        read(x);
        maxnum=max(maxnum,x);
        Tim[x]++;
    }
    for(R int i=1;i<=100;i++){
        int sum=0;
        for(R int j=1;j<=maxnum;j++) sum+=(Tim[j]/i);
        if(sum>=n) Max=i;
        else{
		    printf("%d",Max);
		    return 0;
        }
    }
    return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：2)

一道比较水的 **二分**。

二分天数，然后判断是不是够吃。对于天数为 $x$，包数为 $g$ 的种类可以满足 $\left\lfloor\frac{g}{x}\right\rfloor$ 人。剩下的不够一个人吃。

然后跑一边判断就好。

时间复杂度 $O(100\log m)$，$100$ 是种类最大为 $100$，懒得记录最大种类了。

```cpp
#include <bits/stdc++.h>
#define int long long
#define db double
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

using namespace std;
const int N=105;

int n,m,g[N],l=1,r=0,mid;

inline bool check(int x){
	int sum=0;
	for(int i=0;i<=100;i++)sum+=(g[i]/x);//能不能够吃
	return sum>=n;
}

signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a;
		cin>>a;
		g[a]++;//记录包数，桶
		r=max(r,g[a]);//最优情况下就是一个人，然后吃这么多包
	}
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))l=mid+1;
		else r=mid-1; 
	}//二分板子
	cout<<l-1;//这里不用特判n>m，因为这样l=1，l-1仍然是0
	return 0; 
}
```

---

## 作者：封禁用户 (赞：2)

### 前言

[cnblogs](https://www.cnblogs.com/CM-0728/p/14614757.html)

### Solution

考虑 **二分** 。

首先要确定二分的对象，显然二分天数较为简单。

每次找到的 $mid$ 需要判断是否能让整队人吃饱，那就调用一个 `check()` 。

对于 `check()` ，求出每包食物可供的人数，相加后与 $n$ 相比较。

具体操作见下。

### Code

```cpp
#include<iostream>
using namespace std;
#define ll long long
#define max(x,y) x>y?x:y
ll n,m,l=1,r,a[1005],q[100005],d,o,mid,b;
inline bool check(int x)//判断
{
	ll t=0;
	for(int i=1;i<=d;++i)
		t+=q[i]/x;
	return t>=n;//能否供应需求
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=m;++i)
		cin>>a[i],++q[a[i]],d=max(d,a[i]),b=max(b,q[a[i]]);
	r=b;//确定右边界
	while(l<=r)//二分
	{
		mid=(l+r)/2;
		if(check(mid))
			l=mid+1,o=mid;
		else r=mid-1;
	}
	cout<<o<<"\n";
	return 0;
}
```


---

## 作者：BYWYR (赞：2)

这道题可以明显看得出主要用的是**二分**

那么我们怎么二分呢?

首先我们会发现我们要**二分的是最多能坚持的天数**

不难发现,二分的 $r$的初始值是出现最多的食物的出现次数

我们**只需要用二分枚举一下,再判断每一个枚举到的值是否可行即可**

我们可以稍微计算一下复杂度：$100*log(100)$是根本不会超时的

因此有了如下代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
int mps[100005], ansn;
int t[100005];
int n, k, ans, maxans;
bool check(int x) {//判断是否可行
	int l = 0;
	for(int i = 1;i <= maxans;i++) {
		l += t[i] / x;//每一种食物能够维持多少个人的生命
	}
	if(l < n) {//加起来没到总人数的话......
		return false;
	}
	return true;
}
int main() {
	cin >> n >> k;
	for(int i = 1;i <= k;i++) {
		cin >> mps[i];
		t[mps[i]] ++;
		maxans = max(maxans, mps[i]);//最大的食物编号,方便check函数枚举
		ans = max(ans, t[mps[i]]);//找到二分中的r,见上面解释
	}
	int l = 1, r = ans;
	while(l <= r) {//二分
		int mid = (l+r) / 2;
		if(check(mid)) {
			ansn = mid;
			l = mid+1;
		}
		else {
			r = mid-1;
		}
	}
	cout << ansn << endl;
}
```


---

## 作者：Mickey_snow (赞：2)

#### 二分答案 + 模拟

先将所有的食物读入，用类似于桶排序的方法存在一个数组中。

然后二分一下天数，检查是否可行。

对于一个确定的天数，可以使用贪心的方法模拟检查：首先将食物排序，数组中的数字代表着这种食物_剩余的_数量。创建一个指针指向数组的0号单元，这时判断指针指向的数是否大于这个天数，也就是这种类型的食物是否还够一个人吃上这么多天，如果够，人数减一，这种食物剩余量减去天数，如果不够，指针后移。特别地，如果人数等于0说明可行，指针超出数组范围反之。

上伪代码：
```
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CF1011B
{
    class Program
    {
        public static int _cmp(int a,int b) {
            if (a == b) return 0;
            else if (a > b) return -1;
            else return 1;
        }

        public static bool canSolve(int[] food, int days, int totPeo) {
            int now = 0;
            while (totPeo > 0) {
                while (food[now] < days)
                    if (++now > 100) return false;
                food[now] -= days;
                totPeo--;
            }
            return true;
        }

        static void Main(string[] args)
        {
            int totNums, totParticipant;

            string inp = Console.ReadLine(); string[] div;
            div = inp.Split(' ');
            totNums = Convert.ToInt32(div[1]);totParticipant = Convert.ToInt32(div[0]);

            int[] num = new int[101];
            for (int i = 0; i < 101; i++) num[i] = 0;
            inp = Console.ReadLine();div = inp.Split(' ');
            for (int i = 0; i < totNums; i++)
                num[Convert.ToInt32(div[i]) - 1]++;

            Array.Sort(num, _cmp);

            int fr = 0, to = 101, mid;
            int[] fd = new int[101];
            while (fr < to) {
                mid = ((fr + to) >> 1) + 1;
                for (int i = 0; i < 101; i++) fd[i] = num[i];
                if (canSolve(fd, mid, totParticipant)) fr = mid;
                else to = mid - 1;
            }
            Console.WriteLine(fr.ToString());
        }
    }
}
```

---

## 作者：_xxxxx_ (赞：0)

### 题意

现在有 $n$ 个人，$m$ 包食物。每种食物有自己的类型，每个人都不能吃 $2$ 包相同类型的食物，问这 $n$ 个人最多能吃多少天。

### 分析

先看数据范围，$n\le100$，很小，可以一个一个枚举。

先用用一个数组，把每种食物的个数存起来。然后用一个循环从大到小枚举天数，再用一个循环在里面枚举每类食物够多少个人吃，看看是否比 $n$ 大，如果大了，就直接输出，因为是从大到小枚举的。

时间复杂度 $O(n^2)$，可以通过。

### 代码

```
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 1e2 + 10;
const int INF = 0x3f3f3f3f;
int n, m, a[N], t[N];
signed main()
{
	cin >> n >> m;
	if(n > m)//人比食物还多，1天都不够吃 
	{
		puts("0");
		exit(0);
	}
	for(int i = 1; i <= m; i++)
	{
		cin >> a[i];
		t[a[i]]++;//记录下每种食物的个数 
	}
	for(int i = 100; i >= 1; i--)//枚举所有天数 
	{
		int now = 0;
		for(int j = 1; j <= 100; j++)
		{
			now += t[j] / i;//每种食物可以给多少个人吃，将和加起来，看能吃多少天 
		}
		if(now >= n)//合法就是最大答案 
		{
			cout << i << endl;
			exit(0);
		}
	}
	return 0;
}
```

---

## 作者：2012zxt (赞：0)

# CF1011B题解

## 思路

先看数据范围：

我们发现， $n$ 和 $m$ 都只有 $100$ 。

那这道题可就简单了，思路如下：

1. 统计每种食物出现了几次。

2. 从 $100$ 到 $1$ 枚举，再统计每一种食物可以供的人的个数的和，最后比较有没有到 $n$ ，如果到了，直接输出并结束程序。

3. 最后还没有结果输出 $0$ 。

## 易错点

在理论上，天数可以直接从 $100$ 枚举到 $0$ ，但如果你这么做，就会**喜提RE**！

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt[105];
bool cmp(int x,int y){
	return x>y;//从大到小排序，实际可以不排序
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int tmp;
		cin>>tmp;
		cnt[tmp]++;//统计该食物出现的次数
	}
	sort(cnt+1,cnt+1+n,cmp);
	for(int i=100;i>=1;i--){//枚举天数
		int tmp=0;//可以供的人数
		for(int j=1;j<=100;j++)//顶多100种食物
			tmp+=cnt[j]/i;//向下取整，不满i直接舍弃
		if(tmp>=n){//可以供n个人吃
			cout<<i;
			return 0;//结束程序
		}
	}
	cout<<0;
	return 0;
}

```

---

## 作者：小闸蟹 (赞：0)

```cpp
// 思路：先预处理一下每一个数共出现了多少次，然后枚举合法的天数
#include <iostream>
#include <unordered_map>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    if (n > m)  // 僧多粥少，明显一天都走不动
    {
        std::cout << 0 << std::endl;
    }
    else if (n == m)    // 刚好相等，一人一口，一天吃完
    {
        std::cout << 1 << std::endl;
    }
    else
    {
        std::unordered_map<int, int> Map;
        for (int i = 0; i < m; ++i) // 统计每个数各出现了多少次
        {
            int t;
            std::cin >> t;
            ++Map[t];
        }

        for (int k = m / n; k >= 1; --k)    // 枚举合法的天数（k代表天数），最高只能是(m / n)天
        {
            int Tol = 0;
            for (const auto &r : Map)
            {
                Tol += r.second / k;
            }

            if (Tol >= n)   // 一旦遇到一个合法的就退出，因为我们是从高向低枚举的
            {
                std::cout << k << std::endl;

                break;
            }
        }
    }

    return 0;
}
```

---

## 作者：sinsop90 (赞：0)

这道题可以明显看得出主要用的是二分

那么我们怎么二分呢?

首先我们会发现我们要二分的是最多能坚持的天数

不难发现,二分的 $r$ 的初始值是出现最多的食物的出现次数

我们只需要用二分枚举一下,再判断每一个枚举到的值是否可行即可

我们可以稍微计算一下复杂度：

$ 100 * log(100)$ 是根本不会超时的

因此有了如下代码:

```
#include <bits/stdc++.h>
using namespace std;
int mps[100005], ansn;
int t[100005];
int n, k, ans, maxans;
bool check(int x) {//判断是否可行
	int l = 0;
	for(int i = 1;i <= maxans;i++) {
		l += t[i] / x;//每一种食物能够维持多少个人的生命
	}
	if(l < n) {//加起来没到总人数的话......
		return false;
	}
	return true;
}
int main() {
	cin >> n >> k;
	for(int i = 1;i <= k;i++) {
		cin >> mps[i];
		t[mps[i]] ++;
		maxans = max(maxans, mps[i]);//最大的食物编号,方便check函数枚举
		ans = max(ans, t[mps[i]]);//找到二分中的r,见上面解释
	}
	int l = 1, r = ans;
	while(l <= r) {//二分
		int mid = (l+r) / 2;
		if(check(mid)) {
			ansn = mid;
			l = mid+1;
		}
		else {
			r = mid-1;
		}
	}
	cout << ansn << endl;
}
```


---

