# 試験

## 题目描述

有 $N$ 名 学生在 AtCoder 高中上学，他们有学生 ID ，叫学生 $1$ ，学生 $2$ ， $...$ ，学生 $N$ 。 一天，他们都参加了数学和英语的考试，学生 $i$ $(1\leq i\leq n)$ 的数学成绩是 $A_i$ ，英语成绩是 $B_i$ 。在这所学校，学生的排名规则如下：

- 学生数学和英语的总分更高排名更高。

- 两个学生总分相同时，数学成绩成绩更高排名更高。

- 当两个学生总分和数学成绩都相同时，学生 ID 较小的学生排名更高。

按排名降序输出 $N$ 名学生的 ID。

## 说明/提示

$2\leq N\leq 2\times 10^5$

$0\leq A_i\leq 10^9$

$0\leq B_i\leq 10^9$

translated by @[wangyinghao](https://www.luogu.com.cn/user/453759)

## 样例 #1

### 输入

```
5
5 10 10 12 5
10 10 5 0 10```

### 输出

```
2 3 1 5 4```

## 样例 #2

### 输入

```
2
0 1000000000
0 1000000000```

### 输出

```
2 1```

# 题解

## 作者：maomao233 (赞：1)

### 题意
给定 $N$ 名学生的数学成绩和英语成绩，求他们的排名次序。

### 分析
又有考试成绩，又有总分，又有 ID，很容易就能看出来这题要用结构体。

- 我们用 $a$ 来表示学生的数学成绩，用 $b$ 来表示英语成绩，用 $sum$ 表示两科的总分，用 $id$ 表示他们的编号。（其实英语成绩可以不需要存储，因为后面主要看的是数学成绩和总分）

- 开完数组之后，为了求出他们的排名次序，在排序的时候还需要写一个 `cmp` 函数。因为结构体数组是无法直接对 `sort` 使用的，会报错。排序的时候系统都会比较两个数的大小，那 `cmp` 函数就是要把这两个数引用进去，也就是要用结构体定义两个变量。代码这么写： `bool cmp(node x,node y)` 。

- 题目已经给出了排名的规则了，有 $3$ 点。首先是要判断总分，那就可以直接判断两个总分是否相等，如果不相等，直接返回 `x.sum>y.sum` 就行了。后面两点判断数学成绩和 ID 也是一个道理。

- 主函数里比较简单，在输入数学成绩时就可以把这位同学的 ID 存入他对应的数组里了。之后输入英语成绩时，就把这位同学的总分算出来。最后排序一下输出 ID 即可。



------------


### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int a,b;
	int sum=0;
	int id;
}a[200001];
bool cmp(node x,node y)
{
	if(x.sum!=y.sum)
		return x.sum>y.sum; 
	else if(x.a!=y.a)
		return x.a>y.a;
	return x.id<y.id;
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].a;
		a[i].id=i;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].b;
		a[i].sum=a[i].a+a[i].b;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		cout<<a[i].id<<" ";
	}
	return 0;
}
```


---

## 作者：____someone____ (赞：1)

## Description:

[题目传送门](https://www.luogu.com.cn/problem/AT_past202112_d)

[更好的食用效果](https://www.luogu.com.cn/blog/666someonebk999/solution-at-past202112-d)

#### 题意：

有 $N$ 名学生在 $\text{AtCoder}$ 高中上学，他们的学生 $ID$ 分别为 $1$，$2$，$3$，$\ldots\ldots$，$N$。一天，他们都参加了数学和英语的考试，学生 $i(1\leq i\leq n)$ 的数学成绩是 $A_i$，英语成绩是 $B_i$。在这所学校，学生的排名规则如下：

- 学生数学和英语的总分更高排名更高。

- 两个学生总分相同时，数学成绩成绩更高排名更高。

- 当两个学生总分和数学成绩都相同时，学生 $ID$ 较小的学生排名更高。

按排名降序输出 $N$ 名学生的 $ID$。

## Solution:

数组是一种数据形式，其特点是多个相同类型的元素集合起来；

结构体是另一种重要的数据形式，特点是将**不同类型的成员**组合起来。

数组和结构体形成了两种风格迥异的聚合方式，通过他们及其相互组合、嵌套的机制可以构造出复杂的、满足应用要求的自定义数据类型。

- 结构体：
```
bool cmp(node x,node y)
{
	return x.a<y.a;
}
```
用大于号就是从大到小排序，用小于号就是从小到大排序。

- sort 函数：
```
sort(a+1,a+1+n,cmp);
```

我们可以把学生的数学成绩、英语成绩、总分和 $ID$ 放在一个结构体中，再用 sort 排个序，就 $OK$ 啦！

cmp 函数代码:
```
bool cmp(node x,node y)
{
	if(x.c!=y.c)return x.c>y.c;
	else if(x.a!=y.a)return x.a>y.a;
	return x.id<y.id;
}
```
## AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;

struct node
{
	int id,a,b,c;
};

const int M=2e5+5;
int n;
node stu[M];

bool cmp(node x,node y)
{
	if(x.c!=y.c)return x.c>y.c;
	else if(x.a!=y.a)return x.a>y.a;
	return x.id<y.id;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>stu[i].a;
	for(int i=1;i<=n;i++)
	{
		cin>>stu[i].b;
		stu[i].c=stu[i].a+stu[i].b;
		stu[i].id=i;
	}
	sort(stu+1,stu+1+n,cmp);  //排序
	for(int i=1;i<=n;i++)
		cout<<stu[i].id<<" ";
	return 0;
}
```


---

## 作者：zhujiangyuan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_past202112_d)

## 题意
有 $N$ 名学生在AtCoder高中上学，他们有学生ID，叫学生 $1,2,\cdot \cdot\cdot ,N$。一天，他们都参加了数学和英语的考试，学生 $i$ $(1\leq i\leq n)$ 的数学成绩是 $A_i$ ，英语成绩是 $B_i$ 。在这所学校，学生的排名规则如下：

- 学生数学和英语的总分更高排名更高。

- 两个学生总分相同时，数学成绩成绩更高排名更高。

- 当两个学生总分和数学成绩都相同时，学生ID较小的学生排名更高。

按排名降序输出 $N$ 名学生的ID。

## 分析
结构体基础题。

开一个结构体:
```cpp
struct node
{
	int a,b,x,id;
}stu[N];
```
$a$ 是数学分数，$b$ 是英语分数，$x$ 是数学分数和英语分数的总和，$id$ 是编号。

输入之后做一个排序（**重点，仔细理解**）：
```cpp
bool mysort(node a1,node a2)
{
	return a1.x>a2.x||(a1.x==a2.x&&a1.a>a2.a)||((a1.x==a2.x&&a1.a==a2.a)&&a1.id<a2.id);
}
```

`a1.x>a2.x`表示学生数学和英语的总分更高排名更高。

`a1.x==a2.x&&a1.a>a2.a`表示两个学生总分相同时，数学成绩成绩更高排名更高。

`(a1.x==a2.x&&a1.a==a2.a)&&a1.id<a2.id`表示当两个学生总分和数学成绩都相同时，学生ID较小的学生排名更高。

排完序后依次输出每个学生的编号即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2*pow(10,5)+1;
int n;
struct node
{
	int a,b,x,id;
}stu[N];
bool mysort(node a1,node a2)
{
	return a1.x>a2.x||(a1.x==a2.x&&a1.a>a2.a)||((a1.x==a2.x&&a1.a==a2.a)&&a1.id<a2.id);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&stu[i].a);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&stu[i].b);
		stu[i].id=i;
		stu[i].x=stu[i].a+stu[i].b;
	}
	sort(stu+1,stu+n+1,mysort);
	for(int i=1;i<=n;i++) cout<<stu[i].id<<' ';
    	return 0;
}

```


---

## 作者：Ja50nY0un9_as_AgNO3 (赞：0)

笔者看到了楼上可爱 NAd 的题解，发现可以更简洁一点，于是就来水一篇。

这是一篇萌新向的题解，码风松散，讲解详细。建议更高阶的选手看其他人的题解。

首先我们定义结构体存储每一个学生的信息。
```cpp
const int MAXN = 2e5 + 10;

struct Student{
    int sx, id, sum;
    //数学，学号，总分
};
Student s[MAXN];
```
为什么不存英语成绩呢？因为排序的时候不会用到它，只需要在总分中体现就好了。

随后我们输入数学成绩。这一块很简单。

同时，我们也可以在同一个循环里处理学号。
```cpp
for (int i = 1; i <= n; i++){
    cin >> s[i].sx;
    s[i].id = i;
}
```
然后我们处理英语成绩。

我们首先把总分设为英语成绩，然后加上刚刚输入的数学成绩，就是真正的总分了。
```cpp
for (int i = 1; i <= n; i++){
    cin >> s[i].sum;
    s[i].sum += s[i].sx;
}
```

排序的时候，因为是结构体排序，我们需要自己定义一个函数用于比较。
```cpp
bool cmp(Student x, Student y){
    if (x.sum != y.sum) return x.sum > y.sum;//总分不同
    return x.sx > y.sx;//总分相同，数学高的在前
}
```
为什么不比较学号呢？我们知道，`sort` 是不稳定的排序算法，也就是说它不能保证相同的变量排序前后顺序相同。

所以我们使用 `stable_sort`，这是稳定但稍慢的排序算法，由于原来学号是有序的，所以当总分和数学成绩一致时，学号排序后仍然是有序的。

最后我们输出。
```cpp
stable_sort(s + 1, s + n + 1, cmp);
for (int i = 1; i <= n; i++){
    cout << s[i].id << ' ';
}
return 0;
```
注意，`stable_sort` 包含在 `algorithm` 头文件中，一定要记得加上这个头文件。

至此，我们就做完了这一题。

---

## 作者：NOI_AK_dreeeam (赞：0)

这题因为数据较大，所以要用结构体排序。

首先我们要在结构体里定义学生的数学成绩，英语成绩，两科成绩总和以及编号。然后排序时先判断要比较的学生中两科成绩是否相同，如果相同就继续判断数学成绩是否相同，以此类推。

**_AC code_**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x;
struct node{
    int ma,en,id,me;
}a[200005];
bool cmp(node x,node y){
    if(x.me!=y.me) return x.me>y.me;
    else if(x.ma!=y.ma) return x.ma>y.ma;
    else return x.id<y.id;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].ma,a[i].id=i;
	for(int i=1;i<=n;i++) cin>>a[i].en,a[i].me=a[i].ma+a[i].en;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++) cout<<a[i].id<<" ";
	cout<<"\n";
    return 0;
}
```


---

