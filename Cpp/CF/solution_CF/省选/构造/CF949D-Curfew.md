# Curfew

## 题目描述

Instructors of Some Informatics School make students go to bed.

The house contains $ n $ rooms, in each room exactly $ b $ students were supposed to sleep. However, at the time of curfew it happened that many students are not located in their assigned rooms. The rooms are arranged in a row and numbered from $ 1 $ to $ n $ . Initially, in $ i $ -th room there are $ a_{i} $ students. All students are currently somewhere in the house, therefore $ a_{1}+a_{2}+...+a_{n}=nb $ . Also $ 2 $ instructors live in this house.

The process of curfew enforcement is the following. One instructor starts near room $ 1 $ and moves toward room $ n $ , while the second instructor starts near room $ n $ and moves toward room $ 1 $ . After processing current room, each instructor moves on to the next one. Both instructors enter rooms and move simultaneously, if $ n $ is odd, then only the first instructor processes the middle room. When all rooms are processed, the process ends.

When an instructor processes a room, she counts the number of students in the room, then turns off the light, and locks the room. Also, if the number of students inside the processed room is not equal to $ b $ , the instructor writes down the number of this room into her notebook (and turns off the light, and locks the room). Instructors are in a hurry (to prepare the study plan for the next day), so they don't care about who is in the room, but only about the number of students.

While instructors are inside the rooms, students can run between rooms that are not locked and not being processed. A student can run by at most $ d $ rooms, that is she can move to a room with number that differs my at most $ d $ . Also, after (or instead of) running each student can hide under a bed in a room she is in. In this case the instructor will not count her during the processing. In each room any number of students can hide simultaneously.

Formally, here is what's happening:

- A curfew is announced, at this point in room $ i $ there are $ a_{i} $ students.
- Each student can run to another room but not further than $ d $ rooms away from her initial room, or stay in place. After that each student can optionally hide under a bed.
- Instructors enter room $ 1 $ and room $ n $ , they count students there and lock the room (after it no one can enter or leave this room).
- Each student from rooms with numbers from $ 2 $ to $ n-1 $ can run to another room but not further than $ d $ rooms away from her current room, or stay in place. Each student can optionally hide under a bed.
- Instructors move from room $ 1 $ to room $ 2 $ and from room $ n $ to room $ n-1 $ .
- This process continues until all rooms are processed.

Let $ x_{1} $ denote the number of rooms in which the first instructor counted the number of non-hidden students different from $ b $ , and $ x_{2} $ be the same number for the second instructor. Students know that the principal will only listen to one complaint, therefore they want to minimize the maximum of numbers $ x_{i} $ . Help them find this value if they use the optimal strategy.

## 说明/提示

In the first sample the first three rooms are processed by the first instructor, and the last two are processed by the second instructor. One of the optimal strategies is the following: firstly three students run from room $ 5 $ to room $ 4 $ , on the next stage two of them run to room $ 3 $ , and one of those two hides under a bed. This way, the first instructor writes down room $ 2 $ , and the second writes down nothing.

In the second sample one of the optimal strategies is the following: firstly all students in room $ 1 $ hide, all students from room $ 2 $ run to room $ 3 $ . On the next stage one student runs from room $ 3 $ to room $ 4 $ , and $ 5 $ students hide. This way, the first instructor writes down rooms $ 1 $ and $ 2 $ , the second instructor writes down rooms $ 5 $ and $ 6 $ .

## 样例 #1

### 输入

```
5 1 1
1 0 0 0 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6 1 2
3 8 0 1 0 0
```

### 输出

```
2
```

# 题解

## 作者：Tyher (赞：11)

### $Greedy.$

#### 有一个很显然的性质就是，两个同学的路程不会相交。

具体一点就是，如果有两个人$i,j$，他们在一次的目的地分别是寝室$p,q$，且$i<j,p>q$，那么让$i$前往$q$，$j$前往$p$不会更糟糕。

考虑一个宿管大妈怎么做。

当然是所有同学都尽力往大妈那里走，能不被查就尽可能不被查。

#### 两个大妈呢？

首先很显然的是，在特别左边的同学尽量往左边走，特别右边的同学尽量右走。

假设当前时刻时令$l=i*d+i,r=n-i*d-i$，也就是两边同学能管辖到的全部地方。 

当$l<r$，两边的同学都分别到每个地方就行了。

$l>r$时，中间的同学怎么决策呢？

令$mid=\frac{n}{2}$，其实$i<mid$的同学全部去左边，剩下的同学去右边就行了。

正确性？因为$\sum_{w_i}=n*b$，如果左边同学往左边跑，似乎会让右边的答案更差，但是往左边跑的原因是人不够了，所以右边的人一定是大于$n*b$的，右边的同学可以满足要求，这样不会更差。

所以**从中间分开两边分别做**，能往旁边走就往旁边走，这样贪心就好了，复杂度$O(n)$

代码只有$10$行，就不贴了。

---

## 作者：smoothset (赞：2)

[原文链接](https://blog.csdn.net/qq_43537070/article/details/107562089)
#### 这是一个贪心加二分的题
#### 题意
这个题是说在一个走廊上有n个房间，2个宿管从两端向中间查询，当宿管发现房间里的人数不足b个时，就记录下并锁门，两个宿管各自记录一边的，特别的，当n为奇数时，左边的宿管多查一个房间，求两个宿管记录数最大值的最小值。（P&S：当人数多于b个时，学生可以藏在床底下以躲过宿管的查房）
#### 思路
像这种题，一看就是个二分题，那么我们该怎么验证可行性呢？
很容易想到如果一个房间不能满足，那么我们的最优策略就是留下一个空房间，将人往中间集中
所以可以得到中间一定满足的是一段连续的序列，故我们可以二分这个序列的最左端（也可以说是最右端），然后得到一个最大值。
如图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200724152855922.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNTM3MDcw,size_16,color_FFFFFF,t_70)

#### 代码
具体操作见代码
```cpp
bool check(int x)
{
	ll dis = 1ll * d * (x + 1);
	int p1 = 1, p2 = n, s1 = x + 1, s2 = n - x;
	for (int i = 1; i <= n; i++)
		a[i] = t[i];
	while (s1 < s2)
	{
		int tmp = b;
		while (a[p1] < tmp) tmp -= a[p1++];
		a[p1] -= tmp;
		if (p1 - s1 > dis)
			return 0;
		if (n % 2 == 1 && s1 == (n + 1) / 2)
			break;
		tmp = b;
		while (a[p2] < tmp)	
			tmp -= a[p2--];
		a[p2] -= tmp;
		if (s2 - p2 > dis)
			return 0;
		dis += d, s1++, s2--;
	}
	return 1;
}
int main()
{
    rd(n), rd(d), rd(b);
	for (int i = 1; i <= n; i++)
		rd(t[i]);
	int l = 0, r = (n + 1) / 2, ans;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (check(mid))
			r = mid - 1, ans = mid;
		else
			l = mid + 1;
	}
	pt(ans);
    return 0;
}
```
#### 谢谢

---

## 作者：w33z8kqrqk8zzzx33 (赞：0)

考虑模拟这些学生跑到中间的过程。  
肯定会有一个方案和最优解等价并且在一个宿舍里面要么一个人都没有，要么有恰好 $b$ 人。  
显然如果有多余 $b$ 个人，要么可以用这些人去补另一个宿舍，要么可以藏起来。  
分别考虑左半部分和右半部分；  
我们对每一半都计算出最多有多少个宿舍可以补到 $b$ 人（等价于最少有多少个宿舍怎么都补不到 $b$ 人）。答案明显是（左边不能补到最少数量，右边不能补到最少数量）的 $\max$。注意计算时候可以搬过来另一半的人来减少本半的答案（具体为什么我不知道（（（。  
现在就很简单了：来处理一半，只需要对每个位置 $i$ 算“可以在 $i$ 关门之前跑到 $i$ 的位置”人数之和，如果这个数量 $>b$ 就直接“模拟搬过来” $b$ 人。  
观察到当 $i$ 更靠近中间，可以跑到它的区间更大，并且还永远包含任意里中间更远的 $j$ 的区间。这样就根本不需要管“搬过来”的人是从哪些宿舍搬过来，只需要记已经固定了（不能搬来搬去）多少人。  
两端这样模拟就好了。

主要代码：

```cpp
    int ar[100005];
     
    signed main() {
        ios_base::sync_with_stdio(false); cin.tie(0);
        ll n, d, b; gi(n), gi(d), gi(b);
    	rep1(i, n) gi(ar[i]), ar[i] += ar[i-1];
    	ll m = (n+1)/2, c1 = 0, c2 = 0;
    	for(int i=1; i<=m; i++) c1 += (ar[min(n,i*(d+1))]-c1*b>=b);
    	for(int i=n; i>m; i--) c2 += (n*b-ar[max(0ll,n-(n+1-i)*(d+1))]-c2*b>=b);
    	print(max(m-c1,n-m-c2));
    }
```

神仙给我 idea 的提交：

https://codeforces.com/contest/949/submission/63757814

---

## 作者：the_Death (赞：0)

### 题解 P949D Curfew

[Luogu](https://www.luogu.org/problem/CF949D)

##### 前排提示，这是根据英文题解翻译所得

-----------------

让我先假设这里只有一个宿管的方式来解决问题。在只有一个宿管的情况下，她的唯一的目标就是从左走到右的过程中，我们去最小化不符合条件的寝室数量。
我认定在这个情况下，以下方案为我的贪心策略：

1.	让学生们从左向右跑
2.	如果这里有太多的学生子啊一个寝室里，那么让多余的学生跑到下一个房间里
3. 如果这个寝室的学生数目不满足寝室学生数目的标准，但是这个寝室的人数可能会被它右侧的房间的多余人数填补至合格，那么我们就去填补。
4. 如果$3$不可能，那么就让所有的学生去之后的寝室
5. 如果这个是最后一个房间，让多余的学生藏起来

这个贪心可以以$O(N)$的方式实现：把最初的$a_{i}$的用一个前缀和数组来维护。这样做可以让你快速的检查是否可能让学生去往之后的房间。

为了去计算到底右多少学生将会在之后的房间里被移走，你可以维护一个变量来表示学生所带来的代价。当你一开始考虑房间的时候，你先考虑你在这个房间里可以减少的最多的代价，然后按照上面的贪心策略来贪心。因此，当学生数目符合标准的房间位置的左右端点的移动是单调的时，代价就会减少

注意，现在你只要注意的条件：“不同的学生所经过道路中不会有重叠的道路”，意味着如果第一个学生原本就在$i$并且移动到$a$，同时第二个学生是从$j$移动到$b$，那么就会满足：$j{\geq}i$且$a{\geq}b$。因为如果不是这样，你就可以交换学生，并且最终答案不会因此改变。

> **贪心证明(你可以跳过这一段)**

假设这里有一个更好的解决方案，使房间内人数为$a_{1},a_{2}...a_{k}$时达到更优解，而上面的贪心策略让房间内的人数为$b_{1},b_{2}...b_{l},l$<$k$。

我们假设在最优的方案里，所有学生的移动路径都是互不相交的，所以“多余”的学生都藏在随后一个房间，且所有的优质房间都是满员$b$，或者是一个人也没有。否则就可以用一种方法去更改答案，使得符合标准的房间不会减少。

我们认定$i$是使得$a_i≠b_i$的最小的标号。由于贪心策略通常尽可能先填补满$a_{i}$房间，所以$a_i$与$b_i$的关系为$a_i$>$b_i$

但是如果$a_i$>$b_i$，我们可以更改那个更优的方案，依据贪心的策略，将所有在$b_i$的学生转移到$a_i$

这样我们就可以增加符合标准的房间的数目。所以贪心正确

> **证明结束**

让我们从新回归到原题：处理有两个老师的情况。回想一下一个条件——“最优方案下不同的学生的走的路线不会相交”。所以对于学生数目会有一个边界值，若边界值为$x$，那么从$0$->$nb$的前$x$学生都会被一个老师所检查，剩下的被另一个老师检查到。

我们可以暴力枚举边界，并且用分治的方法去求解原数组的两边的答案。但是，这样做时间复杂度是$n^2*b$，将会超市。我们需要更高效的寻找这个边界。

令$f(m)$成为第一个老师巡查的答案，即第一个老师检查$m$个人之后得到的房间数，$g(m)$就是第二个老师的答案。

很显然的是，当$f(m)$增加的时候，$g(m)$会减少。但要注意的是，两者都没有严格的单调性。实际上，一个老师得到要检查的学生越多，他就有越多的机会检查到合格的房间。(由于多余的学生会藏起来，所以并不会对答案造成影响)。

我们的目标就是找到一个$m$，使得$ans(m)=max(f(m),g(m))$，并且使得$ans(m)$会是最小的。让我们再引进一个变量$z(m)=g(m)-f(m)$——它也是增加的。(但是并不是严格的)

令$m_0$是$z(m_0){\ge}0$的最小下标。可以看到，$min(ans(m_0),ans(m_0-1))$是最终答案。的确，如果一个人尝试一个比$m_0$大的数字$m'$，那么$g(m')$将成为$max$式子的主导地位，则$ans(m_0)$更优。否则，如果$m<m_0-1$，则$ans(m)$更好

---

