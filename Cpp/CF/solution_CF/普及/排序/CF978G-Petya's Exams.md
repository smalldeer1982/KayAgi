# Petya's Exams

## 题目描述

Petya studies at university. The current academic year finishes with $ n $ special days. Petya needs to pass $ m $ exams in those special days. The special days in this problem are numbered from $ 1 $ to $ n $ .

There are three values about each exam:

- $ s_i $ — the day, when questions for the $ i $ -th exam will be published,
- $ d_i $ — the day of the $ i $ -th exam ( $ s_i < d_i $ ),
- $ c_i $ — number of days Petya needs to prepare for the $ i $ -th exam. For the $ i $ -th exam Petya should prepare in days between $ s_i $ and $ d_i-1 $ , inclusive.

There are three types of activities for Petya in each day: to spend a day doing nothing (taking a rest), to spend a day passing exactly one exam or to spend a day preparing for exactly one exam. So he can't pass/prepare for multiple exams in a day. He can't mix his activities in a day. If he is preparing for the $ i $ -th exam in day $ j $ , then $ s_i \le j < d_i $ .

It is allowed to have breaks in a preparation to an exam and to alternate preparations for different exams in consecutive days. So preparation for an exam is not required to be done in consecutive days.

Find the schedule for Petya to prepare for all exams and pass them, or report that it is impossible.

## 说明/提示

In the first example Petya can, for example, prepare for exam $ 1 $ in the first day, prepare for exam $ 2 $ in the second day, pass exam $ 1 $ in the third day, relax in the fourth day, and pass exam $ 2 $ in the fifth day. So, he can prepare and pass all exams.

In the second example, there are three days and two exams. So, Petya can prepare in only one day (because in two other days he should pass exams). Then Petya can not prepare and pass all exams.

## 样例 #1

### 输入

```
5 2
1 3 1
1 5 1
```

### 输出

```
1 2 3 0 3 
```

## 样例 #2

### 输入

```
3 2
1 3 1
1 2 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
10 3
4 7 2
1 10 3
8 9 1
```

### 输出

```
2 2 2 1 1 0 4 3 4 4 
```

# 题解

## 作者：风中の菜鸡 (赞：6)

总的来看，这是一道练习贪心算法的 CF ~~水~~~~题~~

题意：

有 $n$ 天时间，期间有 $m$ 场考试。

分三种情况：
* 考试
* 休息
* 复习

考试会公布时间，且考试时间伴随的就是它要复习的时间。

问：怎么安排时间才能应付每一门考试。

思路：

毫无疑问，贪心题。

贪心题就是最优，最优，最优...

那么我们可以按以下步骤来做：

第一步：按考试时间排序，先考的先安排复习。枚举考试公布时间到考试时间中所有天数，这天没计划就安排复习。

第二步：这里是一个判断，如果有哪天没有任务，就休息。

具体操作就是每天的计划存在一个数组里面。

代码：

code：

```
#include<bits/stdc++.h> 
using namespace std;
struct Exam{
    int promulgate,start,review,place;//分别表示公布时间，考试时间，复习时间和它是第几个考试（因为待会要排序，需记录下它初始位置） 
}exam[110];
int cmp(Exam x,Exam y){//排序函数 
    return x.start<y.start;
}
int m,n,jh[110],num;
int main(){
    cin>>n>>m;//输入 n,m 
    for(int i=1;i<=n;i++)//计划数组初始化为-1 
        jh[i]=-1;
    for(int i=1;i<=m;i++){
        cin>>exam[i].promulgate>>exam[i].start>>exam[i].review; 
        jh[exam[i].start]=m+1;//把考试的那一天初始化 
    }
    for(int i=1;i<=m;i++){
        exam[i].place=i;//记录每一次考试是第几次 （因为之后要排序会打乱考试编号） 
    }
    sort(exam+1,exam+m+1,cmp);
    for(int i=1;i<=m;i++){
        num=0;//num:第i次考试复习了num次 
        for(int j=exam[i].promulgate;j<exam[i].start;j++){//从考试公布时间到考试开始时间枚举 
            if(num==exam[i].review){//如果已经能应付第i次考试 
                break;//就退出 
            } 
            if(jh[j]==-1){//如果第j天没有安排计划 
                jh[j]=exam[i].place;//安排复习第i门功课 
                num++;//记录天数+1 
            }
        }
        if(num<exam[i].review){//如果不能应付第i次考试 
            cout<<"-1";
            return 0; 
        }
    }
    for(int i=1;i<=n;i++){
        if(jh[i]==-1)//如果没有安排计划 
            jh[i]=0;//就休息 
    }
        for(int i=1;i<=n;i++){
            cout<<jh[i]<<' ';
    }
return 0;//完结撒花！ 
}
```

做完本题后，推荐练习：[P1230](https://www.luogu.com.cn/problem/P1230) 智力大冲浪。

和本题思路，难度都差不多（~~个人感觉~~）。

---

## 作者：fls233666 (赞：4)

要尽可能多的安排好复习时间以应付考试，我们采用**贪心**策略。

下面考虑如何贪心。

首先第一个容易想到的是：**优先安排考试时间更早的考试**。

那么，按照 $d_i$ 为关键字，对于每个考试排序即可。

其次，我们要**优先安排在早的时间复习**。

因为，$d_i$ 更大的考试，如果可以用来复习的时间少，那么 $d_i$ 小的考试的复习就要安排到前面。因此要提前安排复习。

于是可以先把要参加考试的那几天安排上考试，然后对于排序后的每个考试，从 $s_i$ 到 $d_i-1$ 扫一遍，检查一下这几天有没有安排。如果没有，则安排上对应考试的复习。

在安排的过程中，如果出现无法安排出 $c_i$ 天的情况，就是无解。

下面是代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define rgt register int
using namespace std;

int plan[111];  //计划安排

int n,m;

struct exams{
	int si;
	int di;
	int ci;
	int id;
}e[111];  //将要到来的考试

inline bool cmp(struct exams e1,struct exams e2){
	return e1.di<e2.di;
}  //以di为关键字排序

int main(){

	scanf("%d%d",&n,&m);
	for(rgt i=1;i<=m;i++){
		scanf("%d%d%d",&e[i].si,&e[i].di,&e[i].ci);
		e[i].id=i;
		plan[e[i].di]=m+1;  //先把要参加考试的那几天安排上
	}
    
	sort(e+1,e+1+m,cmp);  //排序
	for(rgt i=1;i<=m;i++){
		for(rgt j=e[i].si;j<e[i].di;j++){  //从si到di-1安排复习
			if(!plan[j]){   //如果第j天空闲，安排复习
				plan[j]=e[i].id;
				e[i].ci--;  //统计已经安排了几天
				if(!e[i].ci)
					break;
			}
		}
		if(e[i].ci){  //如果找不出ci天复习，无解
			printf("-1");
			return 0;
		}
	}
    
	for(rgt i=1;i<=n;i++)
		printf("%d ",plan[i]);  //输出计划
	return 0;
}
```


---

## 作者：「已注销」 (赞：2)

贪心策略：准备最早的考试

~~极不严谨的~~证明：如果有解，先准备早的考试一定没错；如果这样做无解，先准备晚的考试一定也无解

由于$n\le100$，可以用很暴力的方法：每天都把当天公布题目的考试加入队列，按考试时间sort一遍，复习队首考试，复习完成后pop

用结构体存每场考试，并记录每天的考试编号（如果当天要考试）。按天计算，把答案存在$ans$数组中，如果不用考试就按上述算法求出要复习的考试编号，否则判断这场考试是否复习完，未复习完直接输出`-1`
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,a[101],head=1,tail,b[101],ans[101];
struct exam{
	int num,s,d,c;
}e[101],r[101];
bool cmp(exam a,exam b){
	return a.d<b.d;
}
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;++i)cin>>e[i].s>>e[i].d>>e[i].c,e[i].num=i,b[e[i].d]=i;
	for(int i=1;i<=m;++i){
		for(int j=1;j<=n;++j)if(e[j].s==i)r[++tail]=e[j];
		if(head<tail)sort(r+head,r+tail+1,cmp);
		if(b[i]){
			for(int j=head;j<=tail;++j)if(r[j].num==b[i]){
				cout<<-1;
				return 0;
			}
			ans[i]=n+1;
		}
		else if(head<=tail){
				ans[i]=r[head].num;
				--r[head].c;
				if(r[head].c<1)++head;
			}
	}
	for(int i=1;i<=m;++i)cout<<ans[i]<<' ';
}
```

---

## 作者：kimidonatsu (赞：1)

# CF978G Petya's Exams 题解

## 题意简述

正如题意所述，其实就是给定 $n$ 天与 $m$ 场考试，对于每场考试 $m_i$ 都会有以下属性：

1. 在 $s_i$ 天公布考试
2. 在 $d_i$ 天考试
3. 需要 $c_i$ 天来复习

Petya 的每一天都可以用来复习某一场考试的内容、休息或者考试。我们需要输出这 $n$ 天的时间安排计划，使他可以应付所有的考试；如果无法应付所有考试，就输出 `-1`。

## 题目分析

一道很明显的 **贪心** 题。

> 贪心算法（英语：greedy algorithm），是用计算机来模拟一个「贪心」的人做出决策的过程。这个人十分贪婪，每一步行动总是按某种指标选取最优的操作。而且他目光短浅，总是只看眼前，并不考虑以后可能造成的影响。	—— OI Wiki

对于这道题，有一个非常浅显的贪心做法：**将时间尽可能用来安排复习最近的考试**。证明通过反证法易得：如果连最近的考试都无法复习完，那么复习后面的考试也一定复习不完，毕竟我们后面的时间要更多地留给后面的考试，交换处理的元素位置后却无法取得更优解，由此可以推定目前的解已经是最优解了。

## 代码实现

代码的实现和模拟类似，有以下需要注意的地方：

* 对于每场考试，我们需要根据题目描述建立起一个包含公布时间、考试时间、复习时间、以及这场考试 id 的结构体（即 $s_i$、$d_i$、$c_i$ 与考试 id）
*  看一下题面翻译，我们需要在读入时将考试天数在我们的答案数组中设置为 $m + 1$ 以标记

最重要的就是如何排序以完成我们的贪心了，这里我们需要手写一个 `cmp`，根据 $d_i$ 这个属性，将考试天数靠前的考试优先排到前面来准备。

到了这里，相信各位同学已经有眉目了，我们接下来需要做的就是在安排考试的过程中，从 $s_i$ 一直到考试的前一天 $d_i - 1$ 进行一遍枚举，如果这几天没有安排考试，就安排上当前对应考试的复习。

在安排的过程中，如果我们发现无法安排出 $c_i$ 的时间来复习，那么就直接输出 `-1` 并终止程序。

## 代码

```cpp
#include <bits/stdc++.h>

#define re register

using namespace std;
const int N = 2e5;

int n, m;
int ans[N];

struct node {
	// 与题目中的考试公布时间, 考试时间, 复习时间相对应
	int s, d, c, id;
} exams[N];


/* 排序 */
inline bool cmp(const node x, const node y) {
	return x.d < y.d;
}

void read() {
	/* 读入 */
	scanf("%d %d", &n, &m);
	for (re int i = 1; i <= m; i++) {
		scanf("%d %d %d", &exams[i].s, &exams[i].d, &exams[i].c);
		exams[i].id = i;
		ans[exams[i].d] = m + 1; 	// 在读入过程中现将要安排考试的那几天做标记
	}
}

void work() {
	/* 程序核心 —— 贪心 */
	stable_sort(exams + 1, exams + m + 1, cmp);
	for (re int i = 1; i <= m; i++) {
		for (re int j = exams[i].s; j < exams[i].d; j++) {	// 枚举这些日子是否空闲
			if (!ans[j]) {
            // 安排上复习
				ans[j] = exams[i].id;
				exams[i].c--;
				if (!exams[i].c) break;
			}
		}
		if (exams[i].c) {
        // 无法全部安排上考试
			printf("-1\n");
			exit(0);
		}
	}
}

void write() {
	/* 输出 */
	for (re int i = 1; i <= n; i++) printf("%d ", ans[i]);
	printf("\n");
}

int main() {
	read(), work(), write();
	return 0;
}

```


---

## 作者：玉环小姐姐 (赞：1)

###### 贪心！
#### 贪心！
## 贪心！
重要的事说三遍。

贪心准则：要复习就尽量往前排，毕竟后面的时间要更多地留给后面的考试。

程序内容：

1.建立结构体，包含四个数据（考试序号，题目发布时间，考试时间，复习需要时间）。考试序号需要的原因是后面要排序，会乱掉。

2.读入，读入要注意的是最好一边读入就一边在答案数组里将考试那一天定为m+1.（m+1的原因不多阐述，可自己看样例）。

3.排序，这里的排序比较特殊，是多关键字的排序，先按结束时间排，小的在前，一样时，再按题目发布时间排，小的在前，一样时，再按复习时间排，小的在前。（越早的考试越要赶紧复习嘛）。由于鄙人sort写的不是很好，就用了一个最朴素的排序【暴汗】，大牛们可以写sort的第三个参数作为排序准则。

4.模拟，在排好序的结构体数组中依次操作，从发布题目开始，一天一天判断，若为0则改为考试编号，只要复习时间达到就跳出。若复习时间仍未满但已经到了考试时间，输出-1，结束程序。

5.输出，提醒一下，两个数中要空格，我栽过一次【尴尬】。然后，就没有然后了。

OK程序附上：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct a{
	int nember;
	int begin,end,wait;
};
a a[1001];
int main()
{
	int n;
	int m;
	cin>>n>>m;
	int s[n+1]={0};
	for(int i=1;i<=m;i++)
	{
		a[i].nember=i;
		cin>>a[i].begin>>a[i].end>>a[i].wait;
		s[a[i].end]=m+1;
	}
	for(int i=1;i<=m-1;i++)
	{
		for(int j=i+1;j<=m;j++)
		{
			if(a[j].end<a[i].end)
			{
				a[0]=a[i];
				a[i]=a[j];
				a[j]=a[0];
			}
			else
			{
				if(a[j].end==a[i].end)
				{
					if(a[j].begin<a[i].begin)
					{
						a[0]=a[i];
						a[i]=a[j];
						a[j]=a[0];						
					}
					else
					{
						if(a[j].begin==a[i].begin)
						{
							if(a[j].wait<a[i].wait)
							{
								a[0]=a[i];
								a[i]=a[j];
								a[j]=a[0];								
							}
						}
					}
				}
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		for(int w=a[i].begin;w<a[i].end;w++)
		{
			if(s[w]==0)
			{
				s[w]=a[i].nember;
				a[i].wait--;
			}
			if(a[i].wait==0)
			{
				break;
			}
		}
		if(a[i].wait!=0)
		{
			cout<<"-1";
			return 0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<s[i]<<' ';
	}
	return 0;
} 
```

---

## 作者：I_AK_IOI_and_NOI (赞：0)

## 思路

采用贪心的策略，让先考的先复习，后考的复习时间往后面推，如果先考的都没有复习完，就可以输出 $-1$ 了，小小的证明：如果先复习先考的都复习不完，则先复习后考的一定复习不完，将它换个意思就是：如果能复习完，则先复习先考的。

## 代码
```
#include<bits/stdc++.h>
const int N = 1e6 + 10;
using namespace std;
int n,m;
struct S{
    int s,d,c;
}p[N];
int ans[N];
int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
     for(int i=1;i<=m;++i){
         cin>>p[i].s>>p[i].d>>p[i].c;
     }
     for(int i=1;i<=n;++i){
         int cnt=-1,mi=n+1;
         for(int j=1;j<=m;++j){
             if(p[j].d==i) ans[i]=m+1;
             if(p[j].s<=i && p[j].d>i && p[j].c>0 && (p[j].d<mi)){
                 mi=p[j].d;
                 cnt=j;
             }
         }
         if(ans[i]==0 && cnt!=-1) ans[i]=cnt,p[cnt].c--;
     }
     for(int i=1;i<=m;++i){
         if(p[i].c>0){
             puts("-1");
             return 0;
         }
     }
     for(int i=1;i<=n;++i){
         printf("%d ",ans[i]);
     }
    return 0;
}
```


---

## 作者：atarashiTLE (赞：0)

吐槽hack数据数量
### 一通乱搞贪心题
-----
#### 题目思路
我们发现这是一道贪心题。

__首先__，我们按$d_i$排序(优先安排考试时间更早的考试)。

__其次__，我们按$d_i$与$s_i$的差排序(优先安排复习时间短的考试)。

__最后__，我们按$c_i$排序(优先安排需要复习时间长的考试)。

由上，我们得出了本题数据排序时的`cmp()`函数。

~~这个比较函数是凝聚了无数提交的精华啊~~

我们在排序后，在每个能安排的时间尽量早地安排复习。如果有复习时间过少的考试，直接在循环内部输出`-1`后`return 0`即可。

---
code:
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
struct exam
{
    int s, d, c, bh, cha;
} exams[110];
bool cmp(exam a, exam b)
{
    if (a.d == b.d)
        if (a.cha == b.cha)
            return a.c > b.c;
        else
            return a.cha < b.cha;
    return a.d < b.d;
}
int ans[110];
int main()
{
    int m, n, a = 1, sle = 1;
    cin >> m >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> exams[i].s >> exams[i].d >> exams[i].c;
        exams[i].bh = i;
        exams[i].cha = exams[i].d - exams[i].s;
        ans[exams[i].d] = n + 1;
    }
    sort(exams + 1, exams + n + 1, cmp);
    for (int i = 1; i <= n; i++)
    {
        int tot = 0;
        for (int j = exams[i].s; j <= exams[i].d && tot < exams[i].c; j++)
            if (!ans[j])
            {
                ans[j] = exams[i].bh;
                tot++;
            }
        if (tot < exams[i].c)
        {
            cout << -1 << endl;
            return 0;
        }
    }
    for (int i = 1; i <= m; i++)
        cout << ans[i] << ' ';
    return 0;
    //return 20071007;
}
```

---

## 作者：codeLJH114514 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF978G)

# $\textbf{Problem}$

Petya 有 $m$ 场考试，第 $i$ 场考试在 $s_i$ 天公布，在 $d_i$ 天开考，必须要复习至少 $c_i$ 天才能 AK。

Petya 每天只能干如下三件事之一：考试、复习、休息，问如果要 Petya 每场考试都 AK 的作息表，如果不能输出 `-1`。

# $\textbf{Solution}$

不用排序的解法（雾）

贪心：考虑每天都复习距离开考最近的那场考试。

维护距离开考最近的考试？容易想到 `STL` 的 `set`。

枚举天数，如果今天有考试开考判断复习够了没如果没够就输出 `-1` 否则今天就考试；如果没考试那么判断今天有没有考试被公布如果有加入 `set`；最后如果今天没考试判断 `set` 是否为空（`set` 为空表示没有可以复习的考试），如果是那么今天就休息，否则输出 `set` 中的第一场考试，如果复习完发现够了那么删除这场考试。

本代码时间复杂度 $\mathcal{O}(nm \log_2 m)$ 虽然多了一个 $\log$ 但是也可以过。

# $\textbf{Code}$

```cpp
#include <iostream>
#include <set>
#define PrintLn(say) //std::cout << say << "\n";
#define maxn 128
struct Exam {
    public:
        int s, d, c, k, index;
        bool operator<(const Exam& exam) const& { return d < exam.d; }
} E[maxn];
std::set<Exam> S;
int n, m, A[maxn];
int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) 
        std::cin >> E[i].s >> E[i].d >> E[i].c,
        E[i].k = 0,
        E[i].index = i;
    for (int i = 1; i <= n; i++) {
        bool FLAG = false;
        for (int j = 1; j <= m; j++)
            if (E[j].d == i) {
                if (S.count(E[j])) S.erase(E[j]);
                if (E[j].k != E[j].c) {
                    PrintLn("Petya was slain by exam in age " << i);
                    std::cout << "-1\n";
                    return 0;
                } else {
                    PrintLn("Petya was fight with exam " << j);
                    A[i] = m + 1;
                    FLAG = true;
                }
            }
        for (int j = 1; j <= m; j++)
            if (E[j].s == i)
                S.insert(E[j]);
        if (FLAG) continue;
        if (S.empty()) {
            A[i] = 0;
            PrintLn("Petya was sleeping.");
            continue;
        }
        Exam top = *S.begin();
        S.erase(S.begin());
        A[i] = top.index;
        top.k += 1;
        E[top.index].k += 1;
        if (top.k != top.c)
            S.insert(top);
        PrintLn("Petya was doing exam " << top.index)
    }
    for (int i = 1; i <= n; i++)
        std::cout << A[i] << " \n"[i == n];
    return 0;
}
```

---

