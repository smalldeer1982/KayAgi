# New Year Contest

## 题目描述

As Gerald sets the table, Alexander sends the greeting cards, and Sergey and his twins create an army of clone snowmen, Gennady writes a New Year contest.

The New Year contest begins at 18:00 (6.00 P.M.) on December 31 and ends at 6:00 (6.00 A.M.) on January 1. There are $ n $ problems for the contest. The penalty time for each solved problem is set as the distance from the moment of solution submission to the New Year in minutes. For example, the problem submitted at 21:00 (9.00 P.M.) gets penalty time 180, as well as the problem submitted at 3:00 (3.00 A.M.). The total penalty time is calculated as the sum of penalty time for all solved problems. It is allowed to submit a problem exactly at the end of the contest, at 6:00 (6.00 A.M.).

Gennady opened the problems exactly at 18:00 (6.00 P.M.) and managed to estimate their complexity during the first 10 minutes of the contest. He believes that writing a solution for the $ i $ -th problem will take $ a_{i} $ minutes. Gennady can submit a solution for evaluation at any time after he completes writing it. Probably he will have to distract from writing some solution to send the solutions of other problems for evaluation. The time needed to send the solutions can be neglected, i.e. this time can be considered to equal zero. Gennady can simultaneously submit multiple solutions. Besides, he can move at any time from writing one problem to another, and then return to the first problem from the very same place, where he has left it. Thus the total solution writing time of the $ i $ -th problem always equals $ a_{i} $ minutes. Of course, Gennady does not commit wrong attempts, and his solutions are always correct and are accepted from the first attempt. He can begin to write the solutions starting from 18:10 (6.10 P.M.).

Help Gennady choose from the strategies that help him solve the maximum possible number of problems, the one with which his total penalty time will be minimum.

## 说明/提示

In the sample, one of Gennady's possible optimal strategies is as follows. At 18:10 (6:10 PM) he begins to write the first problem and solves it in 30 minutes (18:40 or 6.40 P.M.). At 18:40 (6.40 P.M.) he begins to write the second problem. There are 320 minutes left before the New Year, so Gennady does not have the time to finish writing the second problem before the New Year. At 0:00 (12.00 A.M.) he distracts from the second problem, submits the first one, and returns immediately to writing the second problem. At 0:10 (0.10 A.M.), he completes the solution for the second problem, submits it and gets 10 minute penalty time. Note that as the total duration of the contest is 720 minutes and Gennady has already spent 10 minutes on reading the problems, he will not have time to solve the third problem during the contest. Yes, such problems happen to exist.

Competitions by the given rules are held annually on the site http://b23.ru/3wvc

## 样例 #1

### 输入

```
3
30 330 720
```

### 输出

```
2 10
```

# 题解

## 作者：naroto2022 (赞：1)

# CF140D 题解

### 题意

有一个跨年比赛从晚上六点到次日早上六点，总共有 $n$ 道题，第 $i$ 题要花 $a_i$ 分钟，每题的罚时为提交时间与 $0$ 点的时间差，在比赛开始时，需要花 $10$ 分钟看题的难度，求能做的最答题数和。

### 思路

简单的贪心题。

要想做的题数最多而且罚时越少，那就先做花时间少的题，能在 $0$ 点前做完的题那就一起在 $0$ 点的时候交，这样在 $0$ 点前做的题全不用罚时。

### 总结

1. 需要花 $10$ 分钟看题的难度。
2. 每题的罚时为提交时间与 $0$ 点的时间差。
3. 总比赛的时间为 $12$ 时 $=720$ 分。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[105],ans,num,cnt=10;
//ans 为可以答题数。 
//num 为罚时。 
//cnt 记录目前用了多少时间。 
int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	sort(a+1,a+1+n);//将做题时间从小到大排序。 
	for(int i=1; i<=n; i++){
		cnt+=a[i];
		if(cnt>720) break;//做的时间大于720分。（比赛已经结束） 
		//总比赛的时间就是12小时，也就是720分钟。 
		ans=i;//更新做了几题。 
		if(cnt>360) num+=cnt-360;//如果超过0点罚时 
	}
	printf("%d %d",ans,num);
	return 0;
}
```


---

## 作者：Crism_qwq (赞：1)

**思路**：这道题思路还挺容易想到的，运用贪心思想，把时间从小到大排序，先做用时短的，这样罚时最小，能在零点前做完的就零点一起交这样前面的题目都无罚时。

**实现**：总时间分为两天分别处理，先处理第一天 $350$ 分钟，能做完的就先做了，然后把第一天剩余的时间加入到第二天的总时间中。

**代码**：
```
#include<bits/stdc++.h>
using namespace std;
int n,a[105];
long long time1=350,time2=360,sum;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);//从小到大排序 
	int k=1;//记录目前做到的题的序号 
	while(k<=n&&a[k]<=time1){
		time1-=a[k];
		k++;
	}
	time2+=time1;//把第一天剩余的时间加入第二天的总时间 
	while(k<=n&&a[k]<=time2){
		time2-=a[k];
		k++;
		sum+=360-time2;//累计罚时 
	}
	cout<<k-1<<" "<<sum;
   return 0;
}

```


---

## 作者：飞啾6373 (赞：1)

小提示：要注意的是，一开始会花费十分钟评估难度，所以可用时间会减少十分钟。

这题思路还是比较好想的，在凌晨零点整或零点之前做完的题可以攒一波在零点整一起提交（所以无罚时），而零点之后做完的做完后立即提交，目的是尽可能减少罚时。

由于目标是在做完的题最多的情况下尽量减少罚时，所以很容易就能想到要将每道题所需时间从小到大排序，这样两者都可以满足。

代码如下（内含注释）：

```
#include<bits/stdc++.h>
using namespace std;
int a[121];
int main()
{
	int n,i,times=0,ans=0,anst=0;//ans代表做题总数，anst代表总罚时
	cin>>n; 
	for(i=0;i<n;i++)cin>>a[i];//循环输入 
	sort(a,a+n);//从小到大排序 
	for(i=0;i<n;i++)
	{
		times+=a[i];
		if(times>350)break;
		if(times==350)//0点前做完0点整交，没有罚时 
		{
			ans++;break;
		}
		ans++;
	}
	i++;
	times=times-350;
	if(times>0)
	{
		if(times<=360)//下一道能做完 
		{
			ans++;
			anst+=times;
		}
	}
	for(;i<n;i++)
	{
		times+=a[i];
		if(times>360)break;//下一道做不完，跳出循环
		ans++;
		anst+=times;//做完立刻交，更新总罚时
	}
	cout<<ans<<" "<<anst; 
	return 0;
}
```


---

## 作者：Xhesika_Frost (赞：1)

很有趣的题目一道

显然的贪心就是按照时间顺序做，先最耗时短的，零点前的都零点交，零点后的都做完就交

正确性怎样保证呢

我们按照这个耗时进行排名后，假如交换两个任务的话

如果这两个任务都再零点前，没有影响，

如果后一个任务跨零点了，那么交换以后，后面的任务的罚时不会变，但前面的任务有可能也要罚时了，答案不可能更优

如果前一个任务跨零点，那么交换以后，后一个任务罚时不变，前一个任务罚时更大，答案更差

如果两个任务都在零点以后，显然应该先做耗时少的

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<stack>
#include<map>
#define lll long long
using namespace std;
int n;
int a[100001];
int kt=350;
int lim=710;
int ans;
int cnt;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
	}
	sort(a+1,a+n+1);
	int sum=0;
	for(int i=1;i<=n;++i){
		sum+=a[i];
		if(sum>lim){
			break;
		}
		cnt=i;
		if(sum<=kt){
			continue;
		}else{
			ans+=(sum-kt);
		}
	}
	cout<<cnt<<" "<<ans<<endl;
	return 0;
}
	
 
```



---

## 作者：Eason_AC (赞：1)

## Content
小 G 想打一场跨年比赛，比赛从下午 $18:00$ 开始一直持续到次日清晨 $6:00$，一共有 $n$ 道题目。小 G 在比赛开始之前需要花费 10 分钟考虑这些题目的复杂度，10 分钟之后 TA 会了解了每道题目需要做的时间 $a_1,a_2,a_3,...,a_n$，然后他就会开始做这些题目，但要注意的是，如果在 $0:00$ 之后交，就会有罚时，罚时为 $0:00$ 到现在距离的时间长度，多次罚时会累加进入总罚时。现在，小 G 想知道自己最多能够做的题目数量，以及在满足这个条件下的最小罚时。

**数据范围：$1\leqslant n\leqslant 100,1\leqslant a_i\leqslant 720$。**
## Solution
我们利用贪心的思想，先将每道题目按照需要做的时间从小到大排序，然后依次去做，就能够保证做题数量最多，并且罚时也会是最少的。一句话，排完序之后只需要模拟就完事。
## Code
```cpp
int n, a[107], s[107], ans, res;

int main() {
	//This program is written in Windows 10 by Eason_AC
	getint(n);
	_for(i, 1, n)	getint(a[i]);
	sort(a + 1, a + n + 1);
	_for(i, 1, n) {
		if(s[i - 1] + a[i] > 710) {
			writeint(ans = i - 1), putchar(' '), writeint(res);
			return 0;
		}
		s[i] = s[i - 1] + a[i];
		res += max(0, s[i] - 350);
	}
	writeint(ans = n), putchar(' '), writeint(res);
	return 0;
}
```

---

## 作者：infinities (赞：1)

首先不得不吐槽：翻译差评！（详情看下面）

这是一道贪心题，英文题面里有这么一句，题目翻译里居然没写（很重要）："并在比赛的前10分钟内估计了问题的时间复杂度"这就意味着，我们要将比赛的前十分钟减去，不能算在内，不然就是WA光没商量。

思路：

- 先输入，从小到大sort一遍（贪心）

- 计算一共能做几道题，注意当时间仅剩0的时候做完最后一题，最后一题也算能做的

- 计算在00:00之前能做几道题（因为之前做完的我们可以在0点整提交，没有罚时）

- 计算剩下的题的罚时，最后输出，然后就做完啦

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans=710,num,lol,ana,lll;//比赛对我们的主人公来说共710min
int main(){
    int n,a[101+10];
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+1+n);//sort一遍
    for(int i=1;i<=n;i++){
        if(ans-a[i]>=0)ans-=a[i],num++;//计算能做几道，注意别忘打等于号
        else break;
    }
    cout<<num<<" ";//输出可做题
    ans=350;
    for(int i=1;i<=num;i++){
        if(ans-a[i]>=0)ans-=a[i];//贪心计算不消耗罚时的题目
        else{lol=i;break;}
    }
    if(lol==0)lol=num;
    ana=350-ans;
    ans=350;
    for(int i=lol;i<=num;i++){
        ana=a[i]+ana;
        lll+=ana-ans;//计算其他可做题的罚时
    }
    cout<<max(0,lll);//输出，这个做法可能输出负数，所以这里和0取最大值
    //这里应该没有防伪语句，各位应该可以放心去复制
}//perfect（/xyx（
```
说句题外话：注意到底下的“网址”“http://b23.ru/3wvc” 了吗？此网址是出题人瞎编的，但是我竟然尝试打开过...

---

## 作者：zhu_wen (赞：0)

# New Year Contest
## 主要题意
### [原题传送门](https://codeforces.com/problemset/problem/140/D)
本题已经有了翻译，我就不过多阐述了，就拉下了一个点：我们需要减去他估计题目难度的那 10 分钟。
## 思路
这道题可以运用贪心的思想，把能做到的题目时间进行累加，只要在 0 点之前，我们就可以一直做题，之后的我们我们就进行模拟，只要有了罚时，我们就进行累加，最后算出总罚时。

本题就通过**贪心**和**模拟**的算法来进行计算，其实这道黄题不难。
## 代码
```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fi first
#define se second
#define re register
#define swap(a, b) a ^= b, b ^= a, a ^= b
#define pb push_back
#define all(x) x.begin(), x.end()
#define fst                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int Max = 1e3 + 5;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

inline int read()
{
    int x = 0;
    bool f = true;
    char c = getchar();
    while (c < 48 || c > 57)
    {
        if (c == '-')
            f = false;
        c = getchar();
    }
    while (c >= 48 && c <= 57)
        x = (x << 3) + (x << 1) + c - 48, c = getchar();
    return f ? x : -x;
}
inline void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + 48);
}
inline void wsp(int x) { write(x), putchar(' '); }
inline void wel(int x) { write(x), putchar('\n'); }

int n;
int a[N], res;            // res记录做题数
int t = 710, f = 350, id; // t表示做题总时间，id表示做了哪道题

signed main()
{
    fst;
    n = read();
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
    }
    sort(a + 1, a + n + 1);
    int q = 0;
    for (int i = 1; i <= n; i++)
    {
        q += a[i];
        if (q > t)
            break; // 用完了总时间
        id = i;
        if (q < f)
            continue; // 没有造成罚时
        else
            res += q - f; // 罚时了多少时间
    }
    cout << id << " " << res << endl;
    return 0;
}
```


---

## 作者：ylch (赞：0)

# CF140D New Year Contest 题解

### 提示

题目翻译漏掉了题面里一句非常非常重要的话：

> "Gennady opened the problems exactly at 18:00 (6.00 P.M.) and managed to estimate their complexity during the first 10 minutes of the contest."

翻译过来是

> Gennady 在 18:00（下午6点）准确地打开了问题，并在比赛的前 10 分钟内估计了问题的复杂性。

也就是说最后的时间要减去用来估计的 10 分钟，请大家一定注意！

### 思路

这是一道**贪心**的题目，我们可以先在 0 点前把能做完的都做完，攒在一块提交，把罚时降到最小；接下来的题目做完直接提交，减少罚时。

由此看出，我们是需要对做题时间排序的。

接下来按照贪心的思路去模拟就行。

### 代码

注释写得很详细，思路不懂可以看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[105];
int n;

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(),	cout.tie();	//输出优化
	
	cin >> n;
	for (int i=1; i<=n; i++)	cin >> a[i];
	sort(a+1, a+1+n);   //从小到大排序
    
	int s = 0, tim = 0;	//做的题目数、当前消耗分钟数
	int i;	//全局循环变量
	for (i=1; i<=n; i++)
	{
		tim += a[i];	//当前时间加上
		if (tim >= 350)	//如果超过 0 点，把之前做完的一起提交（没做完不算）
		{
			s += (tim == 350);	//相等的话算正好做完
			break;
		}
		s++;	//题目数累加
	} i++;	//完成 break 前未完成的 "i++" 语句
	tim -= 350;	//减去 0 点之前完成的
	int ans = 0;	//记录罚时//
	if (tim > 0 && tim <= 360)	//退出前一道题能做完
	{
		s ++;	//累加
		ans += tim;	//记录罚时
	}
	for (; i<=n; i++)	//继续遍历后面的
	{
		tim += a[i];	//计时器累加
		if (tim > 360)	break;	//超过次日 6 点，退出
		s++;	//计数器累加
		ans += tim;	//加上罚时
	}
	cout << s << " " << ans << endl;
	return 0;
}
```

管理员大大辛苦啦~

谢谢大家！我们一起进步，一起 $rp++$！

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF140D)

这题是一道贪心题，我们按照题意贪心即可。

# 思路
因为一开始要花费 10 分钟时间评估难度，所以可用时间要减 10 分钟。首先要先从小到大 $ \operatorname{sort} $ 一遍，然后进行贪心模拟。（答题思路看代码注释）

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005];
int res=710,ans,k=350,pos;//这里我们的主人公有710分钟的总时间可用，ans记录罚时，pos记录题目
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);//排序
	int sum=0;
	for(int i=1;i<=n;i++){
		sum+=a[i];//求和方便贪心
		if(sum>res)
			break;//如果时间超过最大时间，直接break
		pos=i;//记录题目编号
		if(sum<=k)//没有罚时
			continue;
		else
			ans+=sum-k;//记录罚时
	}
	cout<<pos<<" "<<ans<<endl;
	return 0;
}
```


---

## 作者：Leaves_xw (赞：0)

很好的一道贪心题。

**大意：**

有一场跨年比赛从 $18:00$ 举行到次日 $6:00$。给定做每道题所需的时间，求最多能做多少道题目，以及在此基础上罚时最少是多少。一道题目的罚时是提交时间与零点的时间差；做完某道题目之后可以在任意时刻提交；做题过程中可以暂时去做别的事情。

**贪心思路：**

从小到大将 $a_1,a_2…a_n$ 排序，求出在 $00:00$ 之前最多能做多少题，之后的题写完就提交，这样能保证最多的做题数以及最少罚时。

__注意：__ 比赛 $00:00$ 前要先减 $10$ 分钟。

不给予代码，防止ctj。

---

## 作者：Juskko (赞：0)

## CF140D New Year Contest 题解

按时长排序，在 $0$ 时之前做的都在 $0$ 时提交，$0$ 时之后的都直接提交，然后贪心做。

理解其正确性：

考虑对 $0$ 时后罚时的理解：如果有没做出来的题，那么每一分钟都会对罚时有贡献，所以我们要使题的数量尽可能小，所以贪心是正确的。

## 代码如下 ：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 105;
int a[maxn];
int n, i, ans = 0, sum = 0;
signed main()
{
    ios::sync_with_stdio;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + 1 + n); // 排序
    for (i = 1; i <= n; i++)
    {
        if (sum + a[i] > 710)
        {
            break;
        }
        else if (sum + a[i] <= 350)
        {
            sum += a[i];
        }
        else
        {
            sum += a[i];
            ans += sum - 350;
        }
    }
    cout << i - 1 << " " << ans << endl;
    return 0;
}
```



---

