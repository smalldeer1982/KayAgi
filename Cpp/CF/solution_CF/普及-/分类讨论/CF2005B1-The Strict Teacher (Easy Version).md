# The Strict Teacher (Easy Version)

## 题目描述

这是该问题的简单版本。两个版本的唯一区别在于 $m$ 和 $q$ 的约束条件。在本版本中，$m=2$，$q=1$。只有在两个版本都被解决后，你才能进行 hack。

Narek 和 Tsovak 忙于准备本轮比赛，所以他们没能完成作业，决定偷看 David 的作业。他们严格的老师发现 David 没有作业，现在想要惩罚他。她雇佣了其他老师来帮助她抓住 David。现在有 $m$ 位老师一起追赶他。幸运的是，教室很大，所以 David 有很多地方可以藏身。

教室可以表示为一条一维直线，包含从 $1$ 到 $n$ 的格子。

一开始，所有 $m$ 位老师和 David 都在不同的格子里。然后他们开始轮流移动。每一轮移动中：

- David 可以移动到相邻的格子，或者留在原地。
- 然后，$m$ 位老师每个人可以同时移动到相邻的格子，或者留在原地。

这个过程持续到 David 被抓住为止。如果有任意一位老师（可能不止一位）和 David 处于同一个格子，那么 David 就被抓住了。所有人都能看到彼此的移动，因此他们都会采取最优策略。

你的任务是计算，在所有人都采取最优策略的情况下，老师们抓住 David 需要多少步。

采取最优策略意味着学生会选择让老师们用尽可能多的步数才能抓住他；而老师们会协调一致，使得抓住学生所需的步数最少。

另外，由于 Narek 和 Tsovak 认为这个任务很简单，他们决定给你 $q$ 个关于 David 位置的询问。注意：这是简单版本，你只需要处理一个询问。

## 说明/提示

在第一个样例中，学生可以一直待在第 $2$ 个格子。最初位于第 $1$ 个格子的老师可以在一步内到达第 $2$ 个格子。因此答案是 $1$。

在第二个样例中，学生只需一直待在第 $1$ 个格子。最初位于第 $3$ 个格子的老师可以在两步内到达第 $1$ 个格子。因此答案是 $2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
10 2 1
1 4
2
8 2 1
3 6
1
8 2 1
3 6
8```

### 输出

```
1
2
2```

# 题解

## 作者：lxyz (赞：3)

## 题意
一个学生没交作业，两个老师在一条直线上去抓他，求最多几步抓住他。
## 思路
本题是非常明显的分类讨论。

我们假定 $b1$ 永远小于 $b2$。

- 如果 $a<b1$，则说明学生在两位老师的左边，应移到教室的最左侧，老师要走 $b1-1$ 步。
-  如果 $b1<a<b2$，则说明学生在两位老师的中间，应移到两位老师的中间，老师要走 $\displaystyle \frac{b1-b1}{2}$ 步。
-  如果 $a>b2$，则说明学生在两位老师的右边，应移到教室的最右侧，老师要走 $a-b2$ 步。
## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,q,b1,b2,a;
int main(){
	ios::sync_with_stdio(false);//快读快写 
	cin.tie(0), cout.tie(0);
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n>>m>>q>>b1>>b2>>a;
		if(b1>b2){
			int x=b1;
			b1=b2;
			b2=x; 
		} //手打交换更省时间 
		if(a<b1) cout<<b1-1<<"\n";//第一种情况 
        if(a>b1&&a<b2) cout<<(b2-b1)/2<<"\n";//第二种情况 
		if(a>b2) cout<<a-b2<<"\n";//第三种情况 
	}
	return 0;
}
```

---

## 作者：wuyouawa (赞：1)

### 题目大意

有一个学生没交作业，老师召集了共 $m$ 个老师去教室抓他，教室可以表示为一条单元格从 $1$ 到 $n$ 的一维线，并给出了每个教师在哪个单元格，有 $q$ 次询问，每次询问给出学生在哪个单元格，最初所有人的位置互不相同，每一步每个人都可以留在原地或者向相邻的房间走，问最多需要几步抓住学生。这道题保证 $m = 2$ 以及 $q = 1$。

### 思路

这道题的 $m$ 和 $q$ 很小，可考虑贪心与分类讨论。如果学生在两个老师的左边，那么学生跑到最左边是最优的，也就是说，学生和老师都向左跑，答案就是学生跑到最左的步数加上离学生最近的老师追学生的步数，设学生单元格为 $c$，离学生最近的老师单元格为 $m$，则答案为 $c - 1 + m - c$，化简一下就是 $m - 1$。如果学生在两个老师的右边，那么学生跑到最右边是最优的，也就是说，学生和老师都向右跑，答案就是学生跑到最右的步数加上离学生最近的老师追学生的步数，设学生单元格为 $c$，离学生最近的老师单元格为 $m$，则答案为 $n - c + c - m$，化简一下就是 $n - m$。如果学生在两个老师的中间，那么老师向中间走，学生不动是最优的，因为学生动的话，无论他去哪边，那边的老师都会和另一边的老师包围住他，显然不是最优的，综上所述，设一个老师单元格为 $ma$，另一个老师单元格为 $mi$，则答案为 $\frac{ma-mi}{2}$，注意有 $t$ 组数据。

### CODE


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,q,a,b,c,mi,ma;
int main(){
    cin>>t;
    while(t--)//t组数据
    {
        cin>>n>>m>>q>>a>>b>>c;
        mi=min(a,b);
        ma=max(a,b);
        if(c<mi)  
        {
        	cout<<mi-1;//第一种情况
        }
        else  if(c>ma)
        {
        	cout<<n-ma;//第二种情况
        }
        else
        {
        	cout<<(ma-mi)/2;//第三种情况
        }
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：MingRi_Doctor (赞：0)

## 思路：
本题只需分类讨论即可。

如果 $a < b_1$，说明老师 $b_1$ 离学生更近，输出老师 $b_1$ 离学生 $a$ 的距离 $$b_1 - 1$$。

如果 $a > b_1$，说明老师 $b_2$ 离学生更近，输出老师 $b_2$ 离学生 $a$ 的距离 $$a - b_2$$。

如果 $b_1 < a < b_2$，说明学生在老师 $b_1$ 和老师 $b_2$ 中间，两个老师会一起抓学生，所以输出 $$(b_2 - b_1) \div 2$$。

**注：因为我们要保证老师 $b_1$ 在老师 $b_2$ 左边，所以如果 $b_1 > b_2$，要交换 $b_1$ 和 $b_2$。**
## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,q,b1,b2,a;
int main(){
	cin>>t;
	for(int i=0;i<t;i++)
	{
		cin>>n>>m>>q>>b1>>b2>>a;
		if(b1>b2) swap(b1,b2);
		if(a<b1) cout<<b1-1;
		else if(a>b2) cout<<a-b2;
		else cout<<(b2-b1)/2;
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：xiaokang_suancai (赞：0)

[题目传送门（洛谷）](https://www.luogu.com.cn/problem/CF2005B1)
## 题目大意
两个老师在一个教室里抓一个学生，教室可以看做一条一维的线，给出老师和学生所在点的序号，求老师最少需要几步才能抓住学生。
## 题目分析
我们可以进行分类讨论：

为了方便，我们约定 $b_1<b_2$。

- 当 $a<b_1$ 时，学生移到教室的最左侧是最优解，所以老师要走 $b_1-1$ 步。
- 当 $b_1<a<b_2$ 时，学生移到两个老师的中间是最优解，所以老师要走 $\frac{b_2-b_1}{2}$ 步。
- 当 $a>b_2$ 时，学生移到教室的最右侧是最优解，所以老师要走 $n-b_2$ 步。

代码直接套用推导出来的公式即可。
## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,q,b1,b2,a;
int main()
{
	ios::sync_with_stdio(0); // 快读
	cin>>t;
	while(t--)
	{
		cin>>n>>m>>q;
		cin>>b1>>b2;
		cin>>a;
		if(b1>b2)
			swap(b1,b2); // 给老师位置排序
		if(a<b1)
			cout<<b1-1<<endl;
		else if(b1<a&&a<b2)
			cout<<(b2-b1)/2<<endl;
		else if(a>b2)
			cout<<n-b2<<endl; // 三种情况上面已经讲了，不再赘述
	}
	return 0;
}
```

---

## 作者：jubaoyi2011 (赞：0)

## 题目大意

首先需要注意的一点：教室是一条一维线。这就意味着每个老师都只能在学生的两个方向上，所以就可以分成三种情况。
在分之前，需要先对老师进行升序排序

```cpp
sort(teacher+1,teacher+2+1);
```

1.

   ![](https://cdn.luogu.com.cn/upload/image_hosting/7xqpqbcw.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

  （空心表示老师，实心表示学生）

  这个时候老师需要将学生逼到最右边的“墙角”，也就是编号为 $n$ 的单元格，所以结果就是 $n - teacher_2$，

  
```cpp
if(teacher[2]<student)cout<<n-teacher[2];
```


2.
  ![](https://cdn.luogu.com.cn/upload/image_hosting/l1mcfxn2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

  这个时候老师就需要将学生夹住，使学生无法动弹，所以这种情况的答案就是 $teacher_2 - teacher_1$。

  ```cpp
if(teacher[1]<student&&teacher[2]>student)cout<<teacher[1]-teacher[2];
```
3.
![](https://cdn.luogu.com.cn/upload/image_hosting/ydiyx656.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这个时候老师需要将学生逼到最左侧，也就是编号为 $1$ 的单元格，所以结果就是 $teacher_1-1$。

```cpp
if(teacher[1]>student)cout<<teacher[1]-1;
```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2005B1)

建议评红，确实很简单。

### 题目大意
一个学生在一个教室里。我们把这个教室看做一个数列。现在给出他的位置 $a$ 和 $2$ 个教师的位置 $b_1$ 和 $b_2$，求教师抓住这个学生需要的最少时间。（学生可以移动，当两人相遇时被视为抓住）

### 解题思路
分类讨论。这里假设 $b_1 \lt b_2$。
1. 当 $a \lt b_1 \lt b_2$ 时，这个学生只能移动到 $1$ 的位置。教师的移动距离为 $b_1-1$。
2. 当 $b_1 \lt a \lt b_2$ 时，这个学生应当移动到 $\lfloor \frac{b_1+b_2}{2} \rfloor$ 的位置。教师的移动距离为 $\lfloor \frac{b_1+b_2}{2} \rfloor$。
3. 当 $b_1 \lt b_2 \lt a$ 时，同第 $1$ 种情况，教师的移动距离为 $n-b_2$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,q,a,b1,b2;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>m>>q>>b1>>b2>>a;
		if(b1>b2) swap(b1,b2);
		if(a<b1) cout<<b1-1<<endl;
		else if(a<b2) cout<<(b2-b1)/2<<endl;
		else cout<<n-b2<<endl;
	}
}
```

---

## 作者：mc_xiexie (赞：0)

### 思路

只有 $2$ 个老师，其实就只有离大卫最近的两个或一个（在大卫在所有人最右边或最左边时）。

先把老师的位置排序，如果在最左边，答案为他右边第一个老师减一。

![](https://cdn.luogu.com.cn/upload/image_hosting/ui3dugrg.png)

如果在最右边，答案为 $n$ 减他左边第一个老师减一。

![](https://cdn.luogu.com.cn/upload/image_hosting/2bt4o16q.png)

如果在中间，答案为右边的减左边的在除以二（向下取整）。

![](https://cdn.luogu.com.cn/upload/image_hosting/u7hnlphx.png)

注:这是 CF2005B2 的图，与本题的区别为老师数不同。

---

## 作者：masonxiong (赞：0)

# 题目分析

首先是一个非常显然的事情：**David 不可能与老师发生位置交换。**
- 因为 David 比老师先行动，如果他想要与老师发生位置交换的话就必须要走到老师的位置上，而老师知道 David 的行动，所以老师会选择不动从而抓住 David。
- 由此我们可以知道，**David 与老师的相对位置关系永远不变。**

为了方便分析，我们不妨设 $b$（即老师的位置）是按照升序排序的。

鉴于这题仅有两个老师和一次询问，所以按照老师和 David 的分布情况，我们可以分 $3$ 类：

---

## 情况 1：David 在所有老师的左边。

由于 David 与老师的相对位置关系永远不变，所以 David 只可能一直在所有老师的左边。

而老师可以一步一步地向左逼近 David，直到他无处可退（到达 $1$ 单元格）。

此情况下，David 的最优解法是开头一直往左跑，然后靠墙角等死；老师就只需要一直向左走直到抓到 David 为止。

因此，**此情况下的答案为最靠左的老师抵达 $1$ 号单元格所需的时间，即 $b_1-1$。**

---

## 情况 2：David 在两个老师中间

由于 David 与老师的相对位置关系永远不变，所以 David 只可能一直在两个老师的中间。

而老师可以左右一步一步地包夹 David，直到他陷入两面包夹芝士。

此情况下，David 的最优解法是开头跑到两个老师的中点处，然后原地等死；老师就只需要互相靠近直到抓到 David 为止。

因此，**此情况下的答案为两个老师碰面所需的时间，即 $\lfloor(b_2-b_1)\div2\rfloor$。**

---

## 情况 3：David 在所有老师的右边

和情况 1 类似。但是 David 和老师都往右走。

因此，**此情况下的答案为最靠右的老师抵达 $n$ 号单元格所需的时间，即 $n-b_2$。**

---

# 题目做法

按照刚刚的分析，我们只需要将老师按位置升序排序，然后分类讨论就行。

分析一下时空复杂度：
- 时间复杂度：$O(\sum(m\log m)+\sum q)$。每次回答询问是 $O(1)$ 的，给老师排序是 $O(m\log m)$ 的。
- 空间复杂度：$O(m)$。我们需要存储每个老师的位置。

---

# 代码


```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	int t, n, m, q, a, b[2];
	for (cin >> t; t--; ) {
		cin >> n >> m >> q >> b[0] >> b[1] >> a;
		sort(b, b + 2);
		if (a < b[0])
			cout << b[0] - 1 << '\n';
		else if (a > b[1])
			cout << n - b[1] << '\n';
		else
			cout << (b[1] - b[0]) / 2 << '\n';
	}
	return 0;
}
```

---

## 作者：songhongying (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2005B1)

## 思路：
分类讨论。

-  $a_1 < b_1 < b_2$，说明学生在所有老师的左边，则学生只能一直在老师的左边，靠左的老师需要一直向左走，直到最后一个位置，答案为 $b_1 - 1$。
-  $b_1 < a_1 < b_2$，说明学生在两个老师的中间，则学生只能一直在老师的中间，老师需要同时一直向中间走，遇到学生，答案为 $(b_1 + b_2) \div 2$。
-  $b_1 < b_2 < a_1$，说明学生在所有老师的右边，则学生只能一直在老师的右边，靠右的老师需要一直向右走，直到最后一个位置，答案为 $n - b_2$。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int main(){
    
    cin>>T;
    while(T--)
    {
        int n,m,q,b[3]={0},a[2]={0};
        cin>>n>>m>>q;
        for(int i=1;i<=m;i++)  cin>>b[i];
        for(int i=1;i<=q;i++)  cin>>a[i];
        if(b[1]>b[2])  swap(b[1],b[2]);//找出老师大的位置
        if(a[1]<b[1])  cout<<b[1]-1<<endl;//第一种情况：学生在所有老师的左边
        else if(a[1]<b[2])  cout<<(b[2]-b[1])/2<<endl;//第二种情况：学生在两个老师中间
        else  cout<<n-b[2]<<endl;//第三种情况：学生在所有老师的右边
    }
    
	return 0;
}
```

---

