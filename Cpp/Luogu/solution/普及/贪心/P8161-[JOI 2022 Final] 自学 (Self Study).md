# [JOI 2022 Final] 自学 (Self Study)

## 题目描述

在 JOI 高中高一的第三个学期的 $M$ 个星期的时间内，有 $N$ 门课，编号为 $1 \sim N$。每个星期有 $N$ 个课时，第 $i$ 个课时上课程 $i$ 的一节课。

比太郎是一位高一学生。对于 $N \times M$ 个课时中的每一个，他会选择如下行动中的一个：

- 行动 1：比太郎去上课。如果他去上了课程 $i$ 的一节课，那么他对课程 $i$ 的理解程度会增加 $A_i$。
- 行动 2：比太郎不去上课。他转而选择任意一门课，并且自学选中的那门课。如果他选中了课程 $i$ 进行了时长为一课时的自学，那么他对课程 $i$ 的理解程度会增加 $B_i$。

一开始，对每门课的理解程度都为 $0$。由于比太郎想要在课后练习算法竞赛，他在非上课时间内不会学习。当第三个学期的所有课时结束后，期末考就会举行。

比太郎不想挂科。所以他想要最大化在期末考时对每门课的理解程度的最小值。

给定学期的长度，课程的数量，以及对理解程度的提升数值，请写一个程序计算在期末考时对每门课的理解程度的最小值的最大可能值。

## 说明/提示

**【样例解释 \#1】**

举个例子，如果比太郎按如下方式学习，则他对课程 $1, 2, 3$ 的理解程度将分别为 $19, 18, 19$。

- 第一周课程 $1$ 的课：自学课程 $2$；
- 第一周课程 $2$ 的课：自学课程 $2$；
- 第一周课程 $3$ 的课：去上课程 $3$ 的课；
- 第二周课程 $1$ 的课：去上课程 $1$ 的课；
- 第二周课程 $2$ 的课：自学课程 $3$；
- 第二周课程 $3$ 的课：去上课程 $3$ 的课；
- 第三周课程 $1$ 的课：自学课程 $3$；
- 第三周课程 $2$ 的课：自学课程 $2$；
- 第三周课程 $3$ 的课：去上课程 $3$ 的课。

由于对每门课的最小的理解程度不能大于等于 $19$，输出 $18$。

这个样例满足子任务 $3, 5$ 的限制。

**【样例解释 \#2】**

这个样例满足子任务 $1, 3, 5$ 的限制。

**【样例解释 \#3】**

这个样例满足子任务 $3, 5$ 的限制。

**【样例解释 \#4】**

这个样例满足子任务 $2, 3, 4, 5$ 的限制。

----

**【数据范围】**

**本题采用捆绑测试。**

对于 $100 \%$ 的数据，$1 \le N \le 3 \times {10}^5$，$1 \le M \le {10}^9$，$1 \le A_i, B_i \le {10}^9$。

- 子任务 $1$（$10$ 分）：$M = 1$。
- 子任务 $2$（$25$ 分）：$N \cdot M \le 3 \times {10}^5$，$A_i = B_i$。
- 子任务 $3$（$27$ 分）：$N \cdot M \le 3 \times {10}^5$。
- 子任务 $4$（$29$ 分）：$A_i = B_i$。
- 子任务 $5$（$9$ 分）：无特殊限制。

----

**译自 [JOI 2022 Final](https://www.ioi-jp.org/joi/2021/2022-ho/index.html) T2「[自習](https://www.ioi-jp.org/joi/2021/2022-ho/2022-ho-t2.pdf) / [Self Study](https://www.ioi-jp.org/joi/2021/2022-ho/2022-ho-t2-en.pdf)」**

## 样例 #1

### 输入

```
3 3
19 4 5
2 6 2
```

### 输出

```
18
```

## 样例 #2

### 输入

```
2 1
9 7
2 6
```

### 输出

```
7
```

## 样例 #3

### 输入

```
5 60000
630510219 369411957 874325200 990002527 567203997
438920902 634940661 593780254 315929832 420627496
```

### 输出

```
41397427274960
```

## 样例 #4

### 输入

```
4 25
1 2 3 4
1 2 3 4
```

### 输出

```
48
```

# 题解

## 作者：sgl654321 (赞：15)

[传送门](https://www.luogu.com.cn/problem/P8161)
### 题目大意
定义一个长度为 $n$ 的数组 $K$ 代表理解程度，初始值全为 $0$。

遍历 $m$ 次，每次遍历到 $i$，可以选择让 $K_i$ 增加 $A_i$，或者让任意一个数 $K_j$ 增加 $B_j$。

求遍历 $m$ 次后，数组 $K$ 中的最小值最大可以是多少。
### 解题思路
暴力做肯定会超时。粗略思考后~~或点开标签~~后，发现可以用**二分答案加验证**的做法。一般来说，求**最大值最小，最小值最大**一类的问题，一般都可以使用二分答案加验证的做法。

什么是二分答案加验证？就是一个问题的**可行解**按某种单调规律排列，只需要二分答案再进行验证，最终就可以得到**最优解**。

本题答案最小为 $1$，最大不超过 $10^{18}$。而且预期越小，是可行解的可能性越大。所以就可以进行二分答案了。

那么二分答案之后怎么验证呢？本题我们可以用**贪心法**进行验证。

贪心策略：先传入一个目标值。

如果自学比上课更好，那么就去自学，直到达到目标值为止。

如果上课比自学更好，那么看一看仅仅上课能否达到目标值。如果可以，那就尽可能少地去上课。如果达不到目标，那就先上完课，然后再尽可能少地自学。

将自学与上课的总课程数记为 $num$。如果 $num\le n\times m$，则该目标值是可行解。反之，就是不可行解。

我们就用第一个样例来举例吧！首先我们不停地二分答案，最终二分答案到了 $18$ 这个数。遍历每一个课程。

- 课程 $1$：上课的理解程度较高，所以我们优先上课。每一次上课能增加 $19$ 的理解程度，为了达到 $18$ 的理解程度，我们只需要上 $1$ 节课。
- 课程 $2$：自学的理解程度较高，我们就全部自学。每一次自学能够增加 $6$ 的理解程度，为了达到 $18$ 的理解程度， 我们要自学 $3$ 次。
- 课程 $3$：上课的理解程度较高，我们优先上课。每一次上课能够增加 $5$ 的理解程度，但即使 $3$ 周都上课，还是无法达到 $18$ 的理解程度。因此，剩下的 $3$ 的理解程度我们需要自学。每一次自学，我们都可以增加 $2$ 的理解程度，所以我们需要再自学 $2$ 次。总共上课和自学，用了 $5$ 节课。

所以，$3$ 门课我们一共使用了 $9$ 节课，刚好用完。经检验，发现没有比这个答案更大的可行解。所以，应该输出 $18$。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,l,r,ans,num,mid;
struct study{
	long long teach,self;
}a[300010];
long long lesson_num(long long target,long long eta){//eta 代表工作效率
	 //工作时间=工作总量/工作效率，向上取整
	 if(target%eta==0)return target/eta;
	 else return target/eta+1; 
}
bool check(long long target){//target 代表目标 
	num=0;//num代表达到目标所需的上课次数 
	for(int i=1;i<=n;i++){//每一门课都要到达大于等于目标的理解程度 
		if(a[i].self>a[i].teach)//自学比上课好，就绝对去自学 
			num+=lesson_num(target,a[i].self);
		else{//上课理解程度高，优先选择上课 
			if(m*a[i].teach>=target)//仅靠上课，就可以达到目标：）
				num+=lesson_num(target,a[i].teach);
			else{//不仅要上课，还要去自学才能达成目标qwq 
				num+=m;//上课的次数先计算上； 
				num+=lesson_num(target-m*a[i].teach,a[i].self); 
				//剩下的全部自学。 
			}
		}
	//一轮下来，我们就得出所需的上课次数了！
	//如果此时总上课次数已经超标，就不必计算直接返回假值。 
		if(num>n*m)return 0;
	} 
	return 1;

}
int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i].teach);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i].self);
	l=1;r=1000000000000000010;
	while(l<=r){//二分答案加验证 
		mid=(l+r)>>1;
		if(check(mid)==true){
			ans=mid;
			l=mid+1;
		}else r=mid-1;
	}
	printf("%lld\n",ans);
	return 0;
}

```
写在最后：管理大大求过。

---

## 作者：龙水流深 (赞：6)

## 思路

题目要求最大化最小值，联想到二分答案。

但是不保证 $a_i \ge b_i$ 就很不舒服。这样不好计算答案。

但是你可以在翘掉当前这门课，自己偷学，所以把 $a_i$ 与 $b_i$ 取较大值就好。

这样保证了去上课严格优于或等于翘课，所以贪心地选上课，上课不行再翘课补。

或者看我后面几次的码，``check`` 函数略有不同。

## code

```cpp
#include <iostream>
using namespace std;

constexpr int N = 3e5+7;

int n; long long m;
int a[N],b[N];

inline bool check(long long lim)
{
	__int128_t s = 0;//long long = 62 pts
	for(int i=1;i<=n;++i)
	{
		if(a[i]*m>=lim) s += (a[i]*m - lim) / a[i];//多余的
		else s -= (lim - a[i]*m + b[i]-1) / b[i];//缺少的
	}
	return s>=0;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	
	cin >> n >> m;
	for(int *i=a+1,*ed=a+n+1; i!=ed; ++i) cin >> (*i);
	int mx = 0;
	for(int i=1; i<=n; ++i)
	{
		cin >> b[i];
		a[i] = max(a[i],b[i]);
		mx = max(mx,a[i]);
	}
	long long l = 0, r = 1ll*mx*m;
	while(l<=r)
	{
		long long mid = (l+r)>>1;
		if(check(mid)) l = mid+1;
		else r = mid-1;
	}
	cout << l-1;
	return 0;
}
```


## 后记

我们学校提高模拟赛 T1，还是好拿满分的。

~~水题解刷咕值~~

---

## 作者：南阳刘子骥 (赞：6)

首先我们可以确定，如果我们某一门课自学的效果比老师讲的效果都好的话就不需要去上课了，所以我们让 $a_i = \max(a_i,b_i)$。

根据题目给定的数据范围，我们肯定不能用暴力。
我们需要一个至少 $O(n \log n)$ 的算法。

数据结构虽然能带一个 $\log$，但是我没有想到任何能够维护这个信息的数据结构。

那就只剩二分了。  
我们来观察一下到底可不可以二分。

我们二分就只能二分答案了，也就是预期的最低熟练度。
而我们能够发现，一旦我们一个预期熟练度 $k$ 能够被满足，那么 $\leq k$ 的所有预期熟练度都可以被满足，这就为我们的二分提供了保障。

那么我们怎么判断一个 $k$ 能否被满足呢？

我们考虑这样一个思路：

我们遍历每一门课程，记录一下这门课的空余时间 $t_i$。$t_i$ 为正时表示该门课可以空出来的时间为 $t_i$ 节课，而为负时表示该门课需要的额外的时间为 $-t_i$ 节课。
- 如果 $ma_i \geq k$，那就意味着这门课不需要听满 $m$ 节，只需要听 $\lceil \dfrac{k}{a_i} \rceil$ 节即可，这给我们留出了 $m - \lceil \dfrac{k}{a_i} \rceil$ 节课的空余时间。令 $t_i = m - \lceil \dfrac{k}{a_i} \rceil$。
- 如果 $ma_i < k$，那么我们就需要用额外的时间来补这门课，所需的额外时间为 $\lceil \dfrac{k - ma_i}{b_i} \rceil$。令 $t_i = -\lceil \dfrac{k - ma_i}{b_i} \rceil$。

最后将所有的 $t_i$ 加起来，看总和是否为负数。如果为负，那就意味着我们需要花比我们所拥有的时间更多的时间来学习，而这是不可能的，代表着当前最小值不能达成。

----

一个小细节：不开`long long`会炸。  
同时判断函数中间可能会出现爆`long long`的情况，并且二分区间右端点必须为 $10^{18}$ 及以上（$m \leq 10^9,a_i \leq 10^9$），请大家酌情考虑使用`__int128`或 Python。

示例代码：

``` cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010;
ll n, m;
ll a[N], b[N];
ll calc(ll a, ll b)
{//不需要double的ceil
	if (a % b == 0)return a / b;
	else return a / b + 1;
}
bool chq(ll k)
{
	__int128 tot = 0;
	for (int i = 1; i <= n; i++)
	{
		if (m * a[i] >= k)tot += m - calc(k, a[i]);
		else tot -= calc((k - m * a[i]), b[i]);
	}
	return tot >= 0;
}
int main()
{
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &b[i]);
		a[i] = max(a[i], b[i]);
	}
	ll l = 1, r = 1e18;
	ll ans;
	while (l <= r)
	{
		ll mid = (l + r) >> 1;
		if (chq(mid))l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：Henry_ji (赞：4)

本题解所有程序部分均有 C++ 和 Python 两种语言，供大家参考。

注：python 由于其众所周知的缺点，在数据量较大的检查点会超时，仅供参考。
## Part1  题目分析
首先，我们浏览一遍题目。先将我们的视线移向【数据范围】：$1 \le N \le 3 \times 10^5$。这让我们意识到应该立刻打消暴力求解的念头。所以，我们需要一种高效的方法。

让我们~~点开算法标签~~仔细思考，发现对于这种最大最小问题，二分加检查是一个很好的方法。

那么什么是二分加检查？简单来说就是如果一个问题的**可行解**按**单调规律**排列，我们只需要二分答案再进行检查，最终就可以得到**最优解**。

那么对于本道题，我们应该使用何种方法来进行检查呢？对于**最优解**问题，**贪心算法**必然是首选算法中的一个。所以，本道题我们就使用贪心算法进行检查。

## Part2  贪心策略
我自己做了一个流程图，希望帮助大家理解：
![贪心策略流程图](https://cdn.luogu.com.cn/upload/image_hosting/02g56ul2.png)

将总课程数记为 $total$ ，那么判断一个方法合法的标准就是 $total \le N + M$。

我们以题目中的样例 1 作为例子来了解一下如何进行合法性判断。

假设我们已经一通二分做出了 18 这个解。我们来遍历这 3 节课：
- 第 1 节课：上课比较好，一次上课可以获得 19 理解度，已经超出目标值，所以上1课时的课就够了。
- 第 2 节课：自学比较好，每次自学可以获得 6 理解度，果断自学 3 天，完成目标。
- 第 3 节课：上课比较好，一次上课可以获得 5 理解度，所以应该尽可能上课。但是总共只有 3 周，也就是 3 课时的课，可以获得 15 理解度。所以还需要再自学 2 课时，总共获得 19 理解度。

在这 3 节课中，我们自学了 6 个课时，上课了 3 个小时，总共 9 个课时，正好成立。

而我们找不到更好的解了，所以应当输出 18。

## Part3  编程思路
说在前面：所有变量都要用 long long
#### 1、定义结构体/类
C++
```cpp
struct subject{
	long long have_lesson, self_study;
};
```
Python
```python
class subject(object):
    def __init__(self):
        self.have_class, self.self_study = 0, 0
```
#### 2、学习时间计算函数
P.S. 这个函数也可以不用，写出来只是为了主程序好看一点罢了

C++
```cpp
long long study_time(long long target, long long efficiency){
	if (target % efficiency == 0) return target / efficiency;
	return target / efficiency + 1;
	//学习时间=目标量/效率，向上取整
}
```
Python
```python
def study_time(target, efficiency):
    if target % efficiency == 0:
        return target / efficiency
    return target // efficiency + 1  #学习时间=目标量/效率，向上取整
```

#### 3、合法性检查函数
P.S. 这个是最精髓的部分

C++
```cpp
bool check(long long target){//目标值 
	num=0;//所需的总次数 
	for(int i=1;i<=n;i++){//每一门课都要到达大于等于目标的理解程度 
		if(s[i].self_study>s[i].have_lesson)//自学比较好，去自学 
			num+=study_time(target,s[i].self_study);
		else{//上课比较好，优先选择上课 
			if(m*s[i].have_lesson>=target)//仅靠上课，就可以达到目标：）
				num+=study_time(target,s[i].have_lesson);
			else{//不仅要上课，还要去自学才能达成目标qwq 
				num+=m;//上课的次数先计算上； 
				num+=study_time(target-m*s[i].have_lesson,s[i].self_study); 
				//剩下的全部自学。 
			}
		}
		//如果总上课次数已经超标，直接返回假值。 
		if(num>n*m)return false;
	} 
	return true;
}
```
Python
```python
def check(target):  # 目标值
    num = 0
    for i in range(n):
        if subjectList[i].self_study > subjectList[i].have_lesson:
            num += study_time(target, subjectList[i].self_study)
        elif m * subjectList[i].have_lesson >= target:
            num += study_time(target, subjectList[i].have_lesson)
        else:
            num += m
            num += study_time(target - m * subjectList[i].have_lesson, subjectList[i].self_study)
        if num > (n * m):
            return False
    return True
```
## Part4  参考代码
C++
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,l,r,ans,num,mid;

struct subject{
	long long have_lesson, self_study;
}s[300010];

long long study_time(long long target, long long efficiency){
	if (target % efficiency == 0) return target / efficiency;
	return target / efficiency + 1;
	//学习时间=目标量/效率，向上取整
}

bool check(long long target){//目标值 
	num=0;//所需的总次数 
	for(int i=1;i<=n;i++){//每一门课都要到达大于等于目标的理解程度 
		if(s[i].self_study>s[i].have_lesson)//自学比较好，去自学 
			num+=study_time(target,s[i].self_study);
		else{//上课比较好，优先选择上课 
			if(m*s[i].have_lesson>=target)//仅靠上课，就可以达到目标：）
				num+=study_time(target,s[i].have_lesson);
			else{//不仅要上课，还要去自学才能达成目标qwq 
				num+=m;//上课的次数先计算上； 
				num+=study_time(target-m*s[i].have_lesson,s[i].self_study); 
				//剩下的全部自学。 
			}
		}
		//如果总上课次数已经超标，直接返回假值。 
		if(num>n*m){/*cout<<" "<<num<<endl;*/return false;}
	} 
	//cout<<"True "<<num<<endl;
	return true;
}

int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&s[i].have_lesson);
	for(int i=1;i<=n;i++)scanf("%lld",&s[i].self_study);
	l=1;r=1000000000000000010;
	while(l<=r){//二分答案加验证 
		mid=(l+r) / 2;
		//cout<<mid<<" "<<l<<" "<<r;
		if(check(mid)==true){
			ans=mid;
			l=mid+1;
		}else r=mid-1;
	}
	printf("%lld\n",ans);
	return 0;
}
```
Python
```python
class subject(object):
    def __init__(self, t, s):
        self.have_lesson, self.self_study = t, s


def study_time(target, efficiency):
    if not target % efficiency:
        return target // efficiency
    return target // efficiency + 1  # 学习时间=目标量/效率，向上取整


def check(target):  # 目标值
    num = 0
    for i in range(n):
        if subjectList[i].self_study > subjectList[i].have_lesson:
            num += study_time(target, subjectList[i].self_study)
        elif m * subjectList[i].have_lesson >= target:
            num += study_time(target, subjectList[i].have_lesson)
        else:
            num += m
            num += study_time(target - m * subjectList[i].have_lesson, subjectList[i].self_study)
        if num > (n * m):
            return False
    return True


n, m = input().split()
n, m = int(n), int(m)
subjectList = []
tList = input().split()
sList = input().split()
for i in range(n):
    subjectList.append(subject(int(tList[i]), int(sList[i])))
l, r = 1, 1000000000000000010
while l <= r:
    mid = (l + r) // 2
    if check(mid):
        ans = mid
        l = mid + 1
    else:
        r = mid - 1
print(ans)
```
写在最后：求管理员通过

---

## 作者：_lfxxx_ (赞：3)

### 题意：
有长度为 $n$ 的序列 $A,B$。同时初始有一个长度为 $n$ 的全 $0$ 序列 $S$。你可以进行次 $m$ 次操作，每次操作遍历 $1\sim n$，遍历到 $i$ 时，你可以使 $S_i\gets S_i+A_i$ 或 $S_j\gets S_j+B_j$。

最大化 $\min\{S_i\}$。
### 思路：
由于要求最大的最小，容易想到二分，将问题转换为判定性问题。

问题就在于如何判断。

按每次选择哪种方案并不好想，可以从课程的角度出发。

容易看出，想要让某种课快速完成，要选理解程度最高的进行学习，但是用那些步骤进行选择呢？肯定用自己的课学（遍历到该课程的标号时），这样是对其他课程影响最少的。如果不行，找其他时间学。

可这会对其他课的选择依然造成影响，怎么才能保证不会影响到没选的课呢？这里有一个巧妙的办法，先按 $\max\{A_i,B_i\}$ 从大按小排序，然后按照上面的思路做。有 $m$ 次自己的机会，如果不行，就找之前多余的课借；如果可以，可以提供时间。

这样做之所以没有影响是因为如果当前这么大的课都不行，后面那些小的课肯定不行，可以直接退出。

时间复杂度 $O(n\log(m\cdot\max\{a_i,b_i\}))$。
### 代码：
一个小技巧：在计算上几次可以时答案为 $\left\lceil\dfrac{s}{v}\right\rceil$（$s$ 为总量， $v$ 为效率），上去整有点麻烦，可以将其转换为 $\left\lfloor\dfrac{s+v-1}{v}\right\rfloor$。

不开 `long long` 见祖宗。
```cpp
namespace solution{
#define ll long long
int n,m;
struct lesson{
	int a,b;
}a[300005];
inline bool check(ll k){
	ll cnt(0),x;
	for(int i=1;i<=n;++i){
		x=(k+max(a[i].a,a[i].b)-1)/max(a[i].a,a[i].b);
		if(x<=m)
			cnt+=m-x;
		else{
			cnt-=(k-(ll)m*max(a[i].a,a[i].b)+a[i].b-1)/a[i].b;
			if(cnt<0)
				return false;
		}
	}
	return true;
}
void main(){
#ifdef IAKIOI
	freopen("in.txt","r",stdin);
#endif
	ll l(1e9),r(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		cin>>a[i].a,l=min((int)l,a[i].a),r=max((int)r,a[i].a);
	for(int i=1;i<=n;++i)
		cin>>a[i].b,l=min((int)l,a[i].b),r=max((int)r,a[i].b);
	l*=m,r*=m,sort(a+1,a+1+n,[](const lesson&a,const lesson&b){return max(a.a,a.b)>max(b.a,b.b);});
	while(l<=r){
		ll mid(l+r>>1);
		if(check(mid))
			l=mid+1;
		else
			r=mid-1;
	}
	cout<<r<<'\n';
}
}
```

---

## 作者：_k_e_v_i_n_ (赞：2)

# 题意

有两个长度为 $n$ 的序列 $a$ 和 $b$，可以遍历 $m$ 次，遍历到第到 $i$ 个时，可以选择让 $S_i$ 加上 $a_i$ 或 $b_i$。

让 $\min \left\{ S_i \right \}$ 最大化。

# 思路

## 确定算法

当我看到这题时，以为是暴力，然后我翻到了最下面的数据范围~~并打开了题目标签~~，发现是二分。那么是二分查找还是二分答案呢？查找肯定是不适用的，那么就是二分答案了。

## 思路+代码

**部分注释在代码里面。**

定义变量，极端情况 $300000 \times 1000000000$ 超出 ```int``` 范围，要开 ``` long long```。

```
#include<bits/stdc++.h>
#define ll long long	//要开 long long，为了方便，这里使用宏定义 
using namespace std;
ll n,m,ans,l=1,r=1e18,mid;	//初始化 l=1,r=1e18 (1000000000000000000) 
struct node{
	ll a,b;
}a[300001];
```

然后输入。

```
cin>>n>>m;
for(int i=1;i<=n;i++){
	cin>>a[i].a;
}
for(int i=1;i<=n;i++){
	cin>>a[i].b;
}
```

写到这里，我们可以做一个优化，如果 $n$ 和 $m$ 都为 $1$，$a_1$ 和 $b_1$ 谁大选谁。

```
if(m==1&&n==1)	cout<<max(a[1].a,a[1].b),exit(0);
//优化，如果只有一种课程并且只能学一次的话，上课和自学增加的理解程度谁高就选谁 
```

开始二分。

```
while(l<=r){	//基础二分算法
	mid=(l+r)/2;
	if(check(mid)){	//二分答案判断函数
		l=mid+1;
		ans=mid;
	}else{
		r=mid-1;
	}
}
```

输出。

```
cout<<ans;
return 0;	//好习惯，return 0
```

**接下来，就是重中之重——```check``` 函数**

定义一个 $sum$ 变量来记录上课或自学的次数，然后需要用一个 ```for``` 循环来遍历 $1$ 到 $n$。如果上课更理解程度高，那么上课，并让 $sum$ 加上上课的次数，自学同理。如果 $sum$ 超出限制次数，返回假值。循环结束，返回真值。、

完整 ```check``` 函数 + 注释。

```
bool check(ll x){
	ll sum=0;	//记录上课或自学的次数 
	for(int i=1;i<=n;i++){	//从 1 枚举到 n 
		if(a[i].a>=a[i].b){	//如果上课理解程度高，那么上课 
			if(m*a[i].a>=x){
				sum+=calc(x,a[i].a);	//上课 
			}else{
				sum+=m;
				sum+=calc(x-m*a[i].a,a[i].b);	//上课 + 自学 
			}
			//以上的判断等价于 sum+=m*a[i].a>=x?calc(x,a[i].a):m+calc(x-m*a[i].a,a[i].b); 
		}else{	//否则自学 
			sum+=calc(x,a[i].b);
		}
		if(sum>n*m){	//如果上课或自学的次数超出限制 
			return 0;
		}
	}
	return 1; 
}
```

# 完整 AC 代码：

```
#include<bits/stdc++.h>
#define ll long long	//300000*1000000000 超出 int 范围，要开 long long，为了方便，这里使用宏定义 
using namespace std;
ll n,m,ans,l=1,r=1e18,mid;	//初始化 l=1,r=1e18 (1000000000000000000) 
struct node{
	ll a,b;
}a[300001];
ll calc(ll x,ll e){	//计算所消耗的时间 
	if(x%e==0)	return x/e;	//要向上取整，这里作为一个思考题，暂时不说为什么 
	else	return x/e+1;
}
bool check(ll x){
	ll sum=0;	//记录上课或自学的次数 
	for(int i=1;i<=n;i++){	//从 1 枚举到 n 
		if(a[i].a>=a[i].b){	//如果上课理解程度高，那么上课 
			if(m*a[i].a>=x){
				sum+=calc(x,a[i].a);	//上课 
			}else{
				sum+=m;
				sum+=calc(x-m*a[i].a,a[i].b);	//上课 + 自学 
			}
			//以上的判断等价于 sum+=m*a[i].a>=x?calc(x,a[i].a):m+calc(x-m*a[i].a,a[i].b); 
		}else{	//否则自学 
			sum+=calc(x,a[i].b);
		}
		if(sum>n*m){	//如果上课或自学的次数超出限制 
			return 0;
		}
	}
	return 1; 
}
int main(){
	cin>>n>>m;	//输入 
	for(int i=1;i<=n;i++){
		cin>>a[i].a;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i].b;
	}
	if(m==1&&n==1)	cout<<max(a[1].a,a[1].b),exit(0);
	//优化，如果只有一种课程并且只能学一次的话，上课和自学增加的理解程度谁高就选谁 
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid)){
			l=mid+1;
			ans=mid;
		}else{
			r=mid-1;
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Aisaka_Taiga (赞：1)

#### 思路来源：431956

## 基本思路

#### 二分答案+分类讨论

分析一下题意可以发现每一科有自学和上课两种选择，所以分类讨论。

第一种情况：当上课效率比自学效率高的时候，可以选择一直上课来把掌握程度给刷满；

第二种情况：上课效率高，但由于一科最多只能上 m 课时，所以导致必须要再拿出一些课时来自学补满掌握程度；

第三种情况：自学效率高，一直自学刷满掌握程度。

好的分类讨论完了我们就要再思考如何二分。

题目中问的是最大的每一科的最小掌握程度，所以我们可以二分每一科的最小掌握程度，之后用子函数来检验一下再根据结果二分就好了

## 代码分段讲解

#### 头文件部分

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans;
struct qwq{//每一科的上课自学理解度 
	int a,b;
}e[300010];//一定不要开小 
```
结构体数组一定要开至少三十万以上，不然会运行错误，第二行的意思是把 int 全改成 long long ，主函数的 int 改为 signed 就可以。

 ans 存放最后的答案

#### 子函数部分

```cpp
int js(int x,int y)//计算掌握程度为x时需要课时 
{
	if(x%y==0)return x/y;//如果刚好整除就直接加x/y 
	else return x/y+1;//否则还要多用一课时来到x的程度 
}
int check(int x)//检验每一科都掌握程度x是否可以 
{
	int sum=0;//sum是总的学习的课时 
	for(int i=1;i<=n;i++)//从第一科开始遍历 
	{
		if(e[i].a>=e[i].b)//如果上课效率高就上课 
		{
			if(m*e[i].a>=x)//如果一直上课可以完成x的程度就一直上课 
			  sum+=js(x,e[i].a);//加上所学课时 
			else//当必须要自学时 
			{
			  sum+=m;//加上全上课的课时 
			  sum+=js(x-m*e[i].a,e[i].b);//计算剩下需要自学的课时，x要减去全上课已经得到的掌握程度 
			}
		}
		else //如果自己学效率高就自学 
			sum+=js(x,e[i].b);//计算自学所需的课时 
		if(sum>n*m)//如果算下来所需课时超出限制 
			return 0;//证明设置的x太大了，掌握不了这么多 
	}
	return 1;//否则就是x的值可能小了 
}
```

计算函数用来计算每一科需要以自学或上课的方式所需的课时，检验函数用于检验以当前 mid 为每一科的掌握程度是否可以，主要是看所需的课时数量是否大于总共的课时数量。而且在循环里面用了分类讨论，把第一种情况和第二种情况合成上课效率比自学高的情况，其他注释都有。

#### 主函数部分

```cpp
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	cin>>e[i].a;//输入每一科上课可以得到的掌握程度 
	for(int i=1;i<=n;i++)
	cin>>e[i].b;//输入每一科自学可以得到的掌握程度 
	int l=1,r=1e18;//设置左右边界 
	while(l<=r)//二分 
	{
		int mid=(l+r)>>1;//相当于mid=(l+r)/2; 
		if(check(mid))//检验mid可不可以 
		  l=mid+1,ans=mid;//x取小了，左边界右移，顺便把答案存一下 
		else r=mid-1;//x取大了，右边界左移 
	}
	cout<<ans<<endl;//输出答案 
	return 0;//好习惯 
} 
```

主要二分的代码，右边界一定要大，样例调了半天

---

