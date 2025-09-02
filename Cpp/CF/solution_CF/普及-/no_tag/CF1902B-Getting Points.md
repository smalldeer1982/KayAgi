# Getting Points

## 题目描述

Monocarp is a student at Berland State University. Due to recent changes in the Berland education system, Monocarp has to study only one subject — programming.

The academic term consists of $ n $ days, and in order not to get expelled, Monocarp has to earn at least $ P $ points during those $ n $ days. There are two ways to earn points — completing practical tasks and attending lessons. For each practical task Monocarp fulfills, he earns $ t $ points, and for each lesson he attends, he earns $ l $ points.

Practical tasks are unlocked "each week" as the term goes on: the first task is unlocked on day $ 1 $ (and can be completed on any day from $ 1 $ to $ n $ ), the second task is unlocked on day $ 8 $ (and can be completed on any day from $ 8 $ to $ n $ ), the third task is unlocked on day $ 15 $ , and so on.

Every day from $ 1 $ to $ n $ , there is a lesson which can be attended by Monocarp. And every day, Monocarp chooses whether to study or to rest the whole day. When Monocarp decides to study, he attends a lesson and can complete no more than $ 2 $  tasks, which are already unlocked and not completed yet. If Monocarp rests the whole day, he skips a lesson and ignores tasks.

Monocarp wants to have as many days off as possible, i. e. he wants to maximize the number of days he rests. Help him calculate the maximum number of days he can rest!

## 说明/提示

In the first test case, the term lasts for $ 1 $ day, so Monocarp should attend at day $ 1 $ . Since attending one lesson already gives $ 5 $ points ( $ 5 \ge P $ ), so it doesn't matter, will Monocarp complete the task or not.

In the second test case, Monocarp can, for example, study at days $ 8 $ and $ 9 $ : at day $ 8 $ he will attend a lesson for $ 10^9 $ points and complete two tasks for another $ 5 \cdot 10^8 + 5 \cdot 10^8 $ points. And at day $ 9 $ he only attends a lesson for another $ 10^9 $ points.

In the third test case, Monocarp can, for example, study at day $ 42 $ : attending a lesson gives him $ 1 $ point and solving $ 2 $ out of $ 6 $ available tasks gives him another $ 2 \cdot 10 $ points.

In the fourth test case, Monocarp has to attend all lessons and complete all tasks to get $ 8 \cdot 10 + 2 \cdot 20 = 120 $ points.

In the fifth test case, Monocarp can, for example, study at days: $ 8 $ — one lesson and first and second tasks; $ 15 $ — one lesson and the third task; $ 22 $ — one lesson and the fourth task; $ 29 $ — one lesson and the fifth task; $ 36 $ — one lesson and the sixth task.

## 样例 #1

### 输入

```
5
1 5 5 2
14 3000000000 1000000000 500000000
100 20 1 10
8 120 10 20
42 280 13 37```

### 输出

```
0
12
99
0
37```

# 题解

## 作者：ATION001 (赞：2)

这题是二分板子不过分吧。
## 题目大意
你有一个任务，在 $n$ 天之内分数达到 $p$ 分，你的初始分数为 $0$。增加分数的任务为：

- 学习课程，可以增加 $l$ 分，频率为每天一次。
- 写作业，可以增加 $t$ 分，频率为每周一次，一次只能做两份作业。
## 思路
用二分其实很好写。

为啥用二分来写呢？因为 $n\le 10^9$，连 $O(n)$ 的复杂度都过不了，所以我们就要使用复杂度为 $O(\log n)$ 的算法。这么低的复杂度的算法也只有二分了吧。

查找代码：
```cpp
while(l<=r){
  mid=(l+r)/2;
  if(code(mid)){
    r=mid-1;
  }else{
    l=mid+1;
  }
}
```
重点是 check 函数，不过直接按照题意模拟一下就行了，别的题解已经讲的很详细了，这里就不讲了，不知道 check 函数咋写的[看这篇题解](https://www.luogu.com.cn/article/01o29ahd)，感觉比较详细。

温馨提示：**十年 OI 一场空，不开 long long 见祖宗。**
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int tc,n,m,l_1,t;
bool code(int x){
	int ans;
	int k=n/7+(n%7!=0);
	if(x*2<=k){
		ans=(l_1+2*t)*x;
	}else{
		ans=(l_1*x+t*k);
	}
	return ans>=m;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	for(cin>>tc;tc;tc--){
		cin>>n>>m>>l_1>>t;
		int l=1,r=n,mid;
		while(l<=r){
			mid=(l+r)/2;
			if(code(mid)){
				r=mid-1;
			}else{
				l=mid+1;
			}
		}
		cout<<n-l<<'\n';
	}
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：2)

翻译补充：输入的时候，输入天数 $n$，需要得到的总分 $P$，课程得分 $l$ 和测试得分 $t$。

显然，一天最多只可以得 $l+2t$ 分，最多只有 $\left\lfloor\dfrac{\left\lceil\dfrac{n}{7}\right\rceil}{2}\right\rfloor$ 次。

如果不够，那么，如果$\left\lceil\dfrac{n}{7}\right\rceil$ 为奇数，还有一次 $l+t$。

如果还是不够，那么 $t$ 已经用完了，就只能用 $l$ 了。

剩下需要的就是 $\left\lceil\dfrac{P_{res}}{l}\right\rceil$。

[code](https://codeforces.com/contest/1902/submission/237300264)。

---

## 作者：Francium_ (赞：1)

# 题目大意
一个学期有 $n$ 天，每 $7$ 天布置一次作业，上一次课有 $l$ 的收益，上一次课可以做 $2$ 次作业，每次作业有 $t$ 的收益，问最少上几天课能达到 $p$ 的收益。
# 解题思路
$n \leq 10^9$，暴力绝对超时，考虑二分。   
二分休息的天数，每次检验一次，设 $x$ 为作业份数，就会有 $\lceil \frac{n}{7} \rceil$ 份作业，$p1$ 为上课的总收益，$p2$ 为做作业的总收益，因为我们寻求最优，所以每次课如果有作业，就做两份，所以每节课最多有 $l + 2t$ 的收益，如果没作业就只有 $l$ 的收益。合法的话左指针右移，反之右指针左移。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//不开long long见祖宗，别问我怎么知道的
int n, p, l, t;

bool check(int mid) {
	int cl = (n - mid), x = ceil(n * 1.0 / 7);
  int p1 = cl * l, p2 = min(cl * 2, x) * t;//这里作业可能不够，所以取min
	return p1 + p2 >= p;
}

void qio() {
	ios::sync_with_stdio(false);//cin，cout加速
	cin.tie(0);
	cout.tie(0);
}

int find() {
	int l = 0, r = n, mid, ans;

	while (l <= r) {
		mid = l + r >> 1;

		if (check(mid)) {
			ans = mid;//记录答案
			l = mid + 1;
		} else
			r = mid - 1;
	}

	return ans;
}

signed main() {
	qio();
	int T;//多测！！！
	cin >> T;

	while (T--) {
		cin >> n >> p >> l >> t;
		cout << find() << '\n';
	}

	return 0;
}
```

---

## 作者：_Delete_ (赞：1)

### 思路

由题意可得：获得分数的途径是完成作业和上课，上一天课可以做两天作业，要用最少的天数获得超过 $P$ 分。

考虑贪心：

我们要让每一节课 ~~上的物超所值~~ 获得更多分数，即为一天上一节课做两份作业，如果把所有作业都做完都不能获得 $P$ 分，再考虑需要有几天上课但不做作业。

考虑代码实现：

首先计算任务数量（$rw$）为 $(n-1)/7+1$，再判断只是上课的分加做两份任务的分 $rw×t+((rw-1)/2+1)×l$，否则需要的天数为 $(rw-1)/2+1+(p-1)/l+1$。

$1\leqslant P\leqslant10^{18}$ 

**不开 long long 见祖宗**

### 代码

```cpp
#nclude<bits/stdc++.h>
using namespace std;
typedef long long ll;//不开long long见祖宗 
void solve(){
	ll n,p,l,t;
	cin>>n>>p>>l>>t;
	ll sum_rw=(n-1)/7+1;//表示总共有几份任务 
	if(sum_rw*t+((sum_rw-1)/2+1)*l>=p){
		//如果(总任务可获得的积分 + 上课获得的积分)可以获得超过P分 
		cout<<n-((p-1)/(l+2*t)+1)<<endl;
	}
	else{
		ll sum_day=0;//总共需要的天数 
		p-=sum_rw*t+((sum_rw-1)/2+1)*l;//计算不够的分数 
		sum_day+=(sum_rw-1)/2+1;//计算每晚有作业的天数 
		sum_day+=(p-1)/l+1;//计算只上课的天数 
		cout<<n-sum_day<<endl;
	}
	return;
}
int main(){
	ios::sync_with_stdio(0);//小寄巧 
	cin.tie(0);
	cout.tie(0);
	
	int T;
	cin>>T;
	while(T--){
		solve();
	} 
	
	return 0;
}
```


---

## 作者：WAis_WonderfulAnswer (赞：1)

## 题目大意

一个学期有 $n$ 天，每天有课程，每周第一天都有作业，作业可随时做。现在你每天可选择上课或休息，如果上课就上今天的课程并完成之前未完成的作业，每天最多做 $2$ 项作业。完成一项作业加 $t$ 分，上一节课加 $l$ 分，现在你必须在 $n$ 天内达到 $p$ 分，问你最多休息多少天。

## 二分算法
因为数据范围大，所以考虑二分。

考虑二分上课天数，如果上课 $mid$ 天可达到 $p$ 分，则上课 $mid+1$ 至 $n$ 天也肯定能达到 $p$ 分，这说明我们的二分设想是合理的。

那么如何判断上课 $mid$ 天是否可达到 $p$ 分呢？

很明显，我们知道总分 $=$ 作业得分 $+$ 上课得分。其中上课得分很好计算，是 $mid \times l$ 分。而作业得分如果不考虑作业总次数的话，也很容易计算，是 $mid \times 2 \times t$ 分，因为一天最多做两项作业，每次作业都将有 $t$ 分。但是这里有一个问题：可能 $n$ 天的作业总次数并未达到 $mid \times 2$ 次，所以我们可以把这两个值取一个最小值，最为最终作业分。即 $\min(y,mid \times 2 \times t)$( $y$ 表示 $n$ 天作业总次数）。

那么 $y$ 值该如何计算呢？因为每周留一次作业，所以总作业次数为 $\lfloor n \div 7 \rfloor$（当 $7 \mid n$ 时）或 $\lfloor n \div 7 \rfloor + 1$（当 $7 \mid n$ 不成立时）。

很明显如果最终得分达到 $p$ 说明这个 $mid$ 是合法的，最终答案就是 $n - mid$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int _,n,p,l,t;
bool check(int x)
{
	int rk=(n%7==0?n/7:n/7+1); //计算一周会布置的作业次数。
	return t*min(rk,2*x)+x*l>=p;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>_;
	while (_--)
	{
		cin>>n>>p>>l>>t;
		int l=0,r=n,best=-1;
  		//二分
		while (l<=r)
		{
			int mid=(l+r)/2;
			if (check(mid))
			{
				best=mid;
				r=mid-1;
			}
			else
			{
				l=mid+1;
			}
		}
     //因为best是上课天数，所以休息天数就是n-best。
		cout<<n-best<<'\n';
	}
	return 0;
}
```


---

## 作者：__bjxx0201__ (赞：0)

## 题目大意

在 $n$ 天的一个学期中，每一天都会有一个作业布置下去。作业可以随时地写。

上一次课有 $l$ 的利益，也可以做 $2$ 次作业，亦可以做一次作业加上 $t$ 的利益，请问多少天能够上课积累得到 $k$ 的利益？

## 思路

数据太大，所以使用二分法来查找答案。以及使用一定的贪心法。

为什么用二分呢？对于每一天，上课完之后再写作业（顺序可变换），也只能积攒 $2t+l$ 的收益，所以，至多需要 $\frac{n}{2}$ 天。

接下来我们假设 $l$ 为左指针，$r$ 为右指针，$mid$ 为中间数，则：

- 上课的得分为 $mid+l$ 分；
- 由于一天都能做到 $2$ 份作业，所以作业得分为 $mid\times 2 \times t$ 分；
- 注意：中间数 $mid$ 一定需要保证不大于 $n$，否则会错误。

之后，运用到贪心的思想，上文说到至少需要 $\frac{n}{2}$ 天完成，如果 $n$ 是一个奇数，则完不成，那么就要贪心：就是一点点的循环考虑，假设哪几次只上课不写作业或者只写作业不上课，达到 $p$ 的利益。

最后注意一个点：$1\le p \le 10^{18}$。所以我们不能希冀于 int。

---

## 作者：ZhaoV1 (赞：0)

# CF1902B Getting Points


### 题目解析
请大家学习一下二分原理后再来做这道题，毕竟这算是二分的一道板子题。首先我们记录下作业的总数 $Count$ ，注意，每次作业是从本周开始的第一天布置的，所以如果凑整数周还多出天数， $Count$ 还要增加一次。判断休息 $mid$ 天是否可行只需要判断最高可能得分是否高于 $p$ 期望得分即可，注意还要特别判断保证 $mid≤n$ 。

Code
------------

```cpp
#define int long long
int ti,n,p,l,t,Count = 0;

inline bool check(int mid){//休息id天 
	if(mid > n) return false;//休息天数不可多余总天数 
	int study = n-mid;//study天数
	if(study*2 >= Count){
		return (study*l+Count*t) >= p;
	}else{
		return (study*l+study*2*t) >= p;
	}
}

void solve(){
	cin >> n >> p >> l >> t;
	Count = n/7;
	if(n%7) Count++;//作业自每周的第一天布置 
	int left = 0, right = (int)1000000001;
	while(left + 1 < right){
		int mid = left + right >> 1;
		if(check(mid)){
			left = mid;
		}else{
			right = mid;
		}
	}
	cout << left << '\n';
}
```

---

## 作者：xujingyu (赞：0)

## 题意

这是一所大学（猜测），鸟语花香，同学相处融洽，在校内谈笑有鸿儒，往来无白丁。但是这终究还是学校，坚持“自我并非生命意义的全部，每一次学习都是对自我与世界的塑造”之类的原则，所以对学生有一个要求，那就是，学期末之前 $n$ 天必须拿到 $P$ 个学分。

获取学分有两种方法：

1. 写作业，写一次加 $t$ 分（一周的开始就会布置作业，学期末前要搞定，~~十分的良心~~）；
2. 上课，上一次加 $l$ 分。

每天都可以选择沐浴学习的海洋或者躺平。

* 当选择学习时，故事的主人公就会上一节课再写至多两个还没写的且已经布置了的作业；
* 否则一整天都会旷课并且忽略任务。

于是主人公问你他最多能躺多少天。

注意 $1\leq P\leq10^{18}$。

## 解答

求最多可以休息几天，那么就二分答案拿下。

二分休息天数设为 $x$，那么学习的天数就是 $n-x$。在 `check()` 中先以 $\dfrac{n}{7}(n\bmod7\ne0)$ 计算出布置作业的天数设为 $hd$，再计算出以这个学习天数来赚学分能赚多少分（$t\times hd+l\times(n-x)$），若高于 $P$，那么这个就可取，更新左端点；否则更新右端点。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int tc,n,p,l,t,L,R;

bool check(int x)
{
	int hd = n / 7;//homework days
	if(n % 7) hd++;
	hd = min(hd,2 * (n - x));
	if(t * hd + l * (n - x) >= p) return true;//可取
	return false;
}

signed main()
{
	scanf("%lld",&tc);
	while(tc--)
	{
		scanf("%lld%lld%lld%lld",&n,&p,&l,&t);
		L = 0,R = n;//二分
		while(L + 1 < R)
		{
			int mid = L + R >> 1;
			if(check(mid)) L = mid;
			else R = mid;
		}
		printf("%lld\n",L);
	}
	return 0;
}
```

~~结局：于是主人公大人就开始尽情摆烂 fx 了。~~

---

## 作者：qinshi0308 (赞：0)

## 题目大意：

~~先吐槽一下，题目翻译有点乱~~

一个学期有 $n$ 天，每七天会布置一次作业，布置了的作业可以在这天以后（含布置作业的这一天）的任意一天做（在学期结束以前）。另外每天有一次课，其中每上一次课可以获得 $l$ 点学分，每做一次作业可以获得 $t$ 点学分。在一天中，可以选择上一节课并做最多两次作业（可以不做）或休息。

现在要求在学期结束后总学分大于等于 $p$ 的情况下让休息的天数最多，输出最多的休息天数。

## 思路：

既然要让休息的天数最多（上课的天数最少），那么就要尽量加大上一天课的收益。

经过思考，我们发现上一节课做两次作业可以让收益最大化，也就是收获 $l+2\times t$ 点学分。而一个学期有 $x=\lceil \frac{n}{7} \rceil$ 次作业，所以最多有 $\lfloor \frac{x}{2} \rfloor$ 天可以达到这样的收益。注意如果 $x$ 是奇数，那么还有一天可以得到 $l+t$ 点学分。如果这些还不够 $p$，就只能考虑只上课不写作业（收益为 $l$）的情况了。

## 代码：

```cpp
# include <bits/stdc++.h>
using namespace std;
/*提醒：要开long long（不要问我是怎么知道的）*/ 
int main(){
	int t;
	cin>>t;
	for(int i=0;i<t;i++){
		long long n,p,a,b;
		cin>>n>>p>>a>>b;
		long long x=ceil(n/7.0);//一学期的作业总数 
		long long c=a+2*b;//上一节课+做两次作业的学分 
		long long d=a+b;//上一节课+做一次作业的学分 
		long long ans=0;//上课天数 
		long long e=x/2;// 有多少天可以拿到一节课+两次作业的学分 
		if(x%2){//作业总数为奇数 
			if(p<=c*e){//只使用收益最大的方案就可以达到目标
				ans=ceil(1.0*p/c);
			}else if(p<=c*e+d){//使用所有收益最大的答案+一次上课+一次作业可以达到目标
				ans=e+1;
			}else{//都加上还不够，再考虑只上课不写作业
				ans=e+1;
				ans+=ceil(1.0*(p-c*e-d)/a); 
			}
		}else{//作业总数为偶数 
			if(p<=c*e){//只使用收益最大的方案就可以达到目标
				ans=ceil(1.0*p/c);
			}else{//都加上还不够，再考虑只上课不写作业
				ans=e;
				ans+=ceil(1.0*(p-c*e)/a); 
			}
		}
		cout<<n-ans<<endl;//输出答案（总天数-上课天数=休息天数） 
	}
	return 0;
}

```


---

## 作者：linjinkun (赞：0)

首先看到数据范围很大，可以考虑二分，我们可以二分上课天数，制造一个 $\operatorname{check}$ 函数，里面的内容大概是这样的：
```cpp
bool check(int x)
{
    int s = n%7 == 0?n/7:n/7+1;
    return t*min(s,2*x)+x*l>=p;
}
```
这是什么意思呢？$s$ 代表的是 $n$ 天会布置的作业次数，$2 \times x$ 是最大的要写作业次数，因为有可能 $n$ 天没有 $2 \times x$ 这么多作业，所以取 $\min$，又因为每完成一个作业 $+t$ 分，所以是 $t \times \min(s,2 \times x)$，$x \times l$ 表示的是 $n$ 天的课程积分，如果加起来 $\ge p$，就返回 $1$，否则返回 $0$。

接下来是主函数部分：
```cpp
signed main()
{
	scanf("%lld",&num);
	while(num--)
    {
        scanf("%lld %lld %lld %lld",&n,&p,&l,&t);
        int l = 0,r = n,ans;
        while(l<=r)
        {
            int mid = l+r>>1;
            if(check(mid))
            {
                ans = mid;
                r = mid-1;
            }
            else
            {
                l = mid+1;
            }
        }
        printf("%lld\n",n-ans);//n-ans = 休息时间，ans = 上课时间
    }
	return 0;
}
```
完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int num,n,p,l,t;
bool check(int x)
{
    int s = n%7 == 0?n/7:n/7+1;
    return t*min(s,2*x)+x*l>=p;
}
signed main()
{
	scanf("%lld",&num);
	while(num--)
    {
        scanf("%lld %lld %lld %lld",&n,&p,&l,&t);
        int l = 0,r = n,ans;
        while(l<=r)
        {
            int mid = l+r>>1;
            if(check(mid))
            {
                ans = mid;
                r = mid-1;
            }
            else
            {
                l = mid+1;
            }
        }
        printf("%lld\n",n-ans);
    }
	return 0;
}
```
求过！！

---

