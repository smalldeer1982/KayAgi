# The Rank

## 题目描述

John Smith 知道他的儿子 Thomas Smith 是班级乃至全校最优秀的学生之一。在全校学生参加了英语、德语、数学和历史的考试后，形成了一张成绩表。

共有 $n$ 名学生，每位学生有一个唯一的编号（从 $1$ 到 $n$）。Thomas 的编号是 $1$。每位学生有四个分数，分别对应英语、德语、数学和历史。学生按照编号递增的顺序给出。

在成绩表中，学生们将按照总分从高到低排序。总分最高的学生排名第一。如果有两名或以上的学生总分相同，则按编号从小到大排序。

请帮助 John 找出他的儿子 Thomas Smith 的排名。

## 说明/提示

在第一个样例中，学生的总分分别为：$398$、$400$、$398$、$379$ 和 $357$。在 $5$ 名学生中，Thomas 和第三名学生总分并列第二，但 Thomas 的编号更小，所以他的排名是 $2$。

在第二个样例中，学生的总分分别为：$369$、$240$、$310$、$300$、$300$ 和 $0$。在 $6$ 名学生中，Thomas 的总分最高，所以他的排名是 $1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
100 98 100 100
100 100 100 100
100 100 99 99
90 99 90 100
100 98 60 99
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
100 80 90 99
60 60 60 60
90 60 100 60
60 100 60 80
100 100 0 100
0 0 0 0
```

### 输出

```
1
```

# 题解

## 作者：RioBlu (赞：4)

为什么大佬都喜欢结构体？

不用结构体空间就小了好多好多

我只是个蒟蒻，所以只有下面的简陋代码
```
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,d,e,ans=1,zf;
int main()
{
	cin>>a>>b>>c>>d>>e;zf=b+c+d+e;//输入 a 和 托马斯·史密斯的成绩
	for(int s=1;s<a;s++)
	{
		cin>>b>>c>>d>>e;//输入其他人的成绩
		if(zf<b+c+d+e)ans++;//别人的成绩比他高，那么排名也就落下去了
	}
	cout<<ans<<endl;
}
```

---

## 作者：KagurazakaKano (赞：1)

~~水到爆炸啊~~

CF那场比赛当时一大群人十分钟之内就成功切掉了这道题。

不多说上代码

```
#include <bits/stdc++.h>

using namespace std;

struct node{  //通过结构体存储每个学生的信息，比数组直接存储方便很多
	int mk1,mk2,mk3,mk4,id,tot;
}stu[1005];

bool cmp(node a, node b){  //自定义cmp，排序用
	if(a.tot != b.tot){
		return a.tot > b.tot;  //如果总分不同就返回a > b
	} else {
		return a.id < b.id;  //否则返回a < b
	}
}

int main(){
	int n;
	scanf("%d",&n);
	for(int i = 1; i <= n; i++){
		scanf("%d%d%d%d",&stu[i].mk1,&stu[i].mk2,&stu[i].mk3,&stu[i].mk4);  //读入
		stu[i].id = i;
		stu[i].tot = stu[i].mk1 + stu[i].mk2 + stu[i].mk3 + stu[i].mk4;  //累加
	}
	sort(stu + 1, stu + 1 + n, cmp); //排序
	for(int i = 1; i <= n; i++){  //枚举编号为1的学生
		if(stu[i].id == 1){
			printf("%d",i);
			return 0;
		}
	}
}

```

---

## 作者：封禁用户 (赞：0)

# CF1017A The Rank 题解

这道题目其实很简单，简单思路如下：

- 算出每个人的平均分
- 对平均分进行排序
- 找出对应排名

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//using
bool cmp(int a,int b)//快排附加程序，使排序从小到大
{
    return a>b;
}
int main()
{
    int n,sum[10001],flag;//定义
    cin>>n;//输入
    for(int i=1;i<=n;i++)//循环输入
    {
        int a,b,c,d;//定义
        cin>>a>>b>>c>>d;//输入
        sum[i]=a+b+c+d;//按照题目要求，算出总分
        if(i==1) flag=sum[1];//标记一下，按照题目标记一下托马斯·史密斯的成绩
    }
    sort(sum+1,sum+n+1,cmp);//从大到小排序
    for(int i=1;i<=n;i++)//循环查找
        if(flag==sum[i])//如果找到托马斯·史密斯成绩 
        {
            cout<<i;//输出
            return 0;//爆掉程序
        }
    return 0;//华丽结束
}
```

学会了吗？

[Thomas_ 的博客](https://zyy-txws-noip.blog.luogu.org/)

原创，侵权必究

---

## 作者：_zjr (赞：0)

# 我见过的最水的比赛题！！
#### 其实像dalao们说的双关键字排序，没必要啊，按总成绩搜一边就好了，如果总分高的话，他的rank++，其他情况不用考虑啊
下面上本蒟蒻的代码
```cpp
#include <bits/stdc++.h>//万能头文件，NOIP慎用！
using namespace std;
const int maxn = 1010;
int n;
struct Stu
{
	int id, sco; //
}s[maxn];
int main()
{
	scanf("%d", &n);
	int a, b, c, d, rank = 1;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d %d %d %d", &a, &b, &c, &d); //输入成绩
		s[i].id = i;
		s[i].sco = a + b + c + d;     //计算总成绩
	}
	for(int i = 2; i <= n; i++)
	{
		if(s[i].sco > s[1].sco) rank++; //如果当前学生分数比他高，他的rank++就可以啦
	}
	printf("%d\n", rank);
	return 0;
}
```
##### ~~其实，那个结构体没必要开的（这是比赛代码）~~

---

## 作者：Aehnuwx (赞：0)

$CF$水题。

用一个双关键字排序就可以很好地解决这个问题。

$code$

```cpp
#include <iostream>
#include <algorithm> 
using namespace std;

const int maxN = 1001;
namespace The_Rank
{
	struct Stu
	{
		int a, b, c, d, sum, id; //定义四门课的成绩，总分和编号
	}stu[maxN];
	int n;
	bool cmp(Stu x, Stu y)
	{
		if(x.sum != y.sum) return x.sum > y.sum;
		return x.id < y.id; 
	}
	void work()
	{
		cin >> n;
		for(int i = 1; i <= n; i ++)
		{
			cin >> stu[i].a >> stu[i].b >> stu[i].c >> stu[i].d;
			stu[i].sum = stu[i].a + stu[i].b + stu[i].c + stu[i].d; //总分就是四门课成绩之和
			stu[i].id = i; //id初始时就是i
		}
		sort(stu + 1, stu + 1 + n, cmp); //sort排序
		for(int i = 1; i <= n; i ++)
			if(stu[i].id == 1) cout << i; //如果找到了正确的人就输出他的排名，因为已经排过序了，所以第i个人的排名就是i，输出i即可
	}
}

int main()
{
	The_Rank::work();
}
```

---

