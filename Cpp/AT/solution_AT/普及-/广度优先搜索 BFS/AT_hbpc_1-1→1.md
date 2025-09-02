# 1→1

## 题目描述

$m$表示变化规则的数量，$n$表示要生成$1$的数量。

对于生成规则$a_{i},b_{i}$而言，它表示可以将原字符串中的$a_{i}$个$1$变为$b_{i}$个$1$。例如，$a_{i}=2,b_{i}=3$，表示原字符串中$11$可以变为$111$

现在，原字符串中只有$1$个$1$，要求你使用最少的变化次数将字符串变成$n$个$1$。

## 说明/提示

- $1≤m≤300^{2}$
- $1≤n≤10000$
- $1≤a_{i},b_{i}≤300$
- 当$i≠j$时保证$a_{i}≠a_{j}$且$b_{i}≠b_{j}$


### 样例$1$

规则为：

$1->11$

$111->11111$

那么一个$1$变成$11111$需要经过下面这些步骤：

1->11

11->111

111->1111

变化次数为$3$，故答案为$4$。

### 样例$2$

规则为：

$1->111$

$11111->111$

那么一个$1$不可能变成$111111$，故答案为$-1$。

# 题解

## 作者：翼德天尊 (赞：12)

**又是一道bfs的模板 ~~水~~ 题**
来吧，让我们一起分析这道题！


------------
### STEP 1 提炼题意

1.初始有1个1；

2.一次可以使用一个变化规则变成其它个数个1；

3.是否能变成n个1？如果能，**最少需要几步**？

看到上面粗体的条件没？啥也别说了，广搜~~没跑的~~！

~~因为这道题比较水，实际上是我懒得打了~~ 我们直接贴AC代码以及注释吧！相信你一定会看懂的！

------------
### STEP 2 介绍算法

**①什么是广搜？**

广搜，全名广度优先搜索，用来处理各种从起始点到终止点最少距离。

**②为什么要用广搜？**

广搜一般是用来处理地图的，但是在这道题里面，有起始点（1个1），有终止点（n个1），有行走方式（变化规则），需要求最短距离（最少所用的变化规则），所以，毋庸置疑，用广搜！

**③广搜比起深搜用什么优点？**

广搜是利用队列逐层搜索，而深搜是一条线路不撞南墙不回头地搜，搜到了才返回。

一般来说，广搜比较耗费空间（队列需要拉进去很多元素），深搜比较耗费时间（不但要回阙而且容易跑偏）。

而这道题里，因为要求最短路，而用广搜可以逐层搜索，不但节省时间，而且方便寻找，所以，这道题广搜比深搜好。


-------------
### STEP 3 AC代码&&完整注释
```
#include <bits/stdc++.h>//万能头文件
using namespace std;
int m,n,a[90001],b[90001],v[20000];
//分别记录如题的m,n，以及每个变化的第一个数和第二个数，还有记录每个数量的1是否走过的数组.
//刚开始我把300²看成300了……白提交了4次呜呜呜
struct node{
	int l,x;
};//结构体，记录每个点对应的个数以及变化次数
node ydn;//这个纯属没啥用（还是有那么一丁点的）
queue<node> q;//结构体队列
int main() {
	scanf("%d %d",&m,&n);
	for (int i=1;i<=m;i++){
		scanf("%d %d",&a[i],&b[i]);
	}//正常输入
	if (n==1){//因为后面是变化后判断，所以初始位置无法判断，要特判一下1
		printf("1\n");
		return 0;
	}
	ydn.l=1;ydn.x=1;//赋值起始点
	q.push(ydn); //放入起始点（看吧还是有用的）
	v[1]=1;//初始点以走过
	while (!q.empty()){
		node no=q.front();//提取队列第一项
		q.pop();//删除
		for (int i=1;i<=m;i++){//循环每一个变化规则
			if (no.x>=a[i]){//现有的1的数量要大于该变化规则至少需要的1的数量
				node noo;//新建一个结构体
				noo.l=no.l+1;
				noo.x=no.x-a[i]+b[i]; //放入下一个点的数据
				if (v[noo.x]==0&&noo.x<=n+300){//如果将要演变的点未走过且在范围内
					if (noo.x==n){//如果符合就输出（这就是为什么要特判1，因为轮不到1）
						printf("%d\n",noo.l);
						return 0;
					}
					v[noo.x]=1;//标记
					q.push(noo);//推入
				}
			}
			
		}
	}
	printf("-1\n");//循环完还没输出，那肯定无解
	return 0;//好习惯++
}
```


------------
### STEP 4 完结撒花！

本篇题解就这么完美地结束了！如果还有什么不懂的问题，欢迎在评论区问我哦，我会第一时间回复的。

如果全部听懂了，就点个赞纪念一下你的成长吧！

---

## 作者：风急风也清 (赞：1)

广搜模板题。

[什么是广度优先搜索详细解答。](https://www.luogu.com.cn/blog/witherforever/post-bfs-guang-du-you-xian-sou-suo)

思路：

如果拓展过，则跳过。

如果没有，进行以下操作。

先判断一下够不够指定长度去转变，如果不可以就跳过。

再判断这个长度有没有标记过，或者长度比 $n+300$ 还大。

如果没有标记，也比 $n+300$ 要小，就可以将这个数放进队列中啦。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n;
bool vis[100005];//标记有没有这个长度。
struct st
{
	int x,y;
}a[90005];
struct node
{
	int l,cost;//当前长度和花费时间。
}cnt,num;
queue<node>sum; //队列。
void bfs()
{
	cnt.l=1;
	cnt.cost=1;// 初始值都是1。
	sum.push(cnt);
	while(!sum.empty())
	{
		cnt=sum.front();
		sum.pop();
		for(int i=1;i<=m;i++)
		{
			if(cnt.l<a[i].x) continue;//如果不够长度就不变。
			num.l=cnt.l-a[i].x+a[i].y;//改变当前长度
			num.cost=cnt.cost+1;
			if(num.l>n+300 || vis[num.l]==true) continue;//不合法条件
			if(num.l==n) { cout<<num.cost<<endl; return; }
			sum.push(num);
			vis[num.l]=true;
		}
	}
	cout<<"-1"<<endl;//不满足题目条件。
}
int main()
{
	cin>>m>>n;
	if(n==1) { cout<<"1"<<endl; return 0; }//特判
	for(int i=1;i<=m;i++)
	{
		cin>>a[i].x>>a[i].y;
	}
	bfs();
	return 0;
}
```


---

## 作者：EuphoricStar (赞：1)

这题不就是一道广搜的模板题嘛。~~（但为啥会是紫题）~~

思路：读入数据后开始 BFS。如果当前元素等于 n，则输出答案并直接退出程序；否则枚举每一个可能的 $a_i$ 和 $b_i$，变换后保存至队列中。

注意：

- 要判断当前状态是否重复，避免死循环。

- 需要剪枝，否则会 T。

- **ATCoder 的题输出记得换行。**

下面上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

struct rule
{
    int a, b;
} rules[90090]; // 变换规则
struct point
{
    int cur, step;
};
int m, n, ans;
queue<point> q;
bool vis[10000000];

int main()
{
    ios::sync_with_stdio(0); // 优化 cin, cout
    cin >> m >> n;
    for (int i = 0; i < m; ++i) cin >> rules[i].a >> rules[i].b;
    q.push({1, 1});
    vis[1] = 1;
    while (!q.empty())
    {
        int cur = q.front().cur, step = q.front().step;
        q.pop();
        if (cur == n) { cout << step << endl; return 0; }
        for (int i = 0; i < m; ++i)
        {
            int a = rules[i].a, b = rules[i].b, nn = cur;
            if (cur >= a) nn += b - a;
            if (vis[nn]) continue; // 已经访问过这种状态
            if (nn > n + 300) continue; // 一个小小的剪枝，剔除范围外的点
            vis[nn] = 1;
            q.push({nn, step + 1});
        }
    }
    cout << -1 << endl;
    return 0;
}
```


---

## 作者：JimmyF (赞：1)

这题很轻易就想到
$BFS$ 
，应该算是道板子题了。

与图论中求单源最短路径相似，本题思路如下：

-  如果被扩展过，跳过；
- 如果没被扩展过：

1. 检查这个状态能不能增加
$1$
的数量；
2. 数组是否越界；
3. 将此状态加入队列。

代码如下（码风较差还请多多包涵）

```cpp
#include<bits/stdc++.h>
using namespace std;
bool f[20010];
int m,n;
struct node
{
    int len;
    int step;
};
struct data
{
    int a;
    int b;
}p[90010];
queue <node> que;
//定义
int main()
{
    scanf("%d%d",&m,&n);
    if(n==1)
    {
        printf("1\n");
        return 0;
    }
    //特判
    for(int i=1; i<=m; i++)
    scanf("%d%d",&p[i].a,&p[i].b);
    //读入
    que.push(node{1,1}); 
    f[1]=1;   
    //初始状态
    while(!que.empty())
    {
        node u=que.front();
        que.pop();
        for(int i=1; i<=m; i++)
        {
            if(u.len<p[i].a)continue; 
            node v;
            v.len=u.len-p[i].a+p[i].b;
            v.step=u.step+1;  //新状态
            if(v.len>n+300)continue;
            if(f[v.len])continue;//判断越界
            if(v.len==n)
            {
                printf("%d\n",v.step);
                return 0;
            }
            //有就输出
            que.push(v);
            f[v.len]=1; //压入新状态
        }
    }
    //深搜
    printf("-1\n");//没有就是输出-1
    return 0;
}
```


---

## 作者：ZiRanGe_Jason (赞：1)

这道题目要让我们求最小变化次数，我们可以很轻松地想到BFS。

BFS时，我们需要记录当前变化次数和当前1的个数。

**那么问题来了，无法变化的情况怎么判断？**

根据题目的数据大小，我们可以知道在1的个数比n+300大时，就再也不可能变成n了。所以我们只需要在1的个数比n+300大时，直接continue。

如果直到队列空，都没有一种情况下在1的个数为n，那么就输出-1（详情请看代码）。

代码：


```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<utility>
#define P pair<int ,int > 
using namespace std;
P a[900009];
bool vis[20009];
int m,n;
int main(){
    scanf("%d %d",&m,&n);
    for(int i=1;i<=m;i++)cin>>a[i].first>>a[i].second;
    sort(a+1,a+m+1);
    queue<P >q;
    vis[1]=1;
    q.push(P(1,1));
    while(!q.empty()){
        P now=q.front();
        q.pop();
        if(now.first==n){
            printf("%d\n",now.second);
            return 0;
        }
        for(int i=1;i<=m;i++){
            if(now.first<a[i].first)break;
            P v;
            v.first=now.first-a[i].first+a[i].second;
            v.second=now.second+1;
            if(v.first>n+300)continue;
            if(vis[v.first])continue;
            else {
                q.push(v);
                vis[v.first]=1;
            }
        }
    }
    printf("-1\n");
    return 0;
}
```


---

## 作者：lzxhdxx (赞：1)

# 题解AT180

### 题意：

输入操作个数（m）和目标1的个数（n），然后输入每种操作，根据操作把1个1改成n个1，输出最短的操作次数，如果不能变成n个1，输出-1。

### 算法：

搜索。我们怎样想到搜索呢？我们结合更简单明显搜索题来看，当前1的个数就是当前状态，而每个操作就是一种偏移量，这样就可以顺利地联想到搜索

确定了搜索的算法，我们就应该选择哪种搜索（bfs or dfs），那么在这个题中，我们该选择哪种搜索呢？

众所周知深搜~~某已死算法~~常常超时，尤其是在这个题数据规模较大的情况下很可能超时，所以作者在这使用宽度优先搜索。

搜索策略：得到初始1的个数，然后不断bfs扩展新状态，到达目标状态，bfs完就输出

### 坑点：

1.输出必须换行！换行！

2.例如操作1 2，只能1->2，而不能像2->1这样变回来~~也许只有我一个蒟蒻犯了这个错误~~

# Code：
```cpp
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int m, n, vis[100010] = { 0 };//vis记录最小步数

struct operation { int start, end; }oper[100010];//记录操作

void bfs()
{
	queue<pair<int, int> >Q;//两个int分别存储这一步1的个数和来到这一步所用的步数
	Q.push(make_pair(1, 0));//压入初始状态
	while (!Q.empty())
	{
		int now = Q.front().first, stp = Q.front().second;//取出队头
		vis[now] = stp;//记录步数
		for (int i = 1; i <= m; i++)
		{//扩展
			int exp = now - oper[i].start + oper[i].end;//新状态
			if (exp > 0 && exp <= n + 300 && stp + 1 < vis[exp] && now != n && now - oper[i].start >= 0)
			{//exp<=n+300 阈值n+300就够
				Q.push(make_pair(exp, stp + 1));//符合条件就压入新状态
				vis[exp] = stp + 1;//记录步数
			}
		}
		Q.pop();//弹出队头
	}
}

int main()
{
	memset(vis, 127 / 3, sizeof(vis));//初始化为一个很大的数
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; i++) scanf("%d%d", &oper[i].start, &oper[i].end);
	bfs();
	if (vis[n] > 10000) printf("-1\n");//阈值10000就够，大于阈值就是没有方法能变成n个1
	else printf("%d\n", vis[n] + 1);
	return 0;
}
```
减少代码复制，创建美好洛谷！

求管理大大给过

---

## 作者：Max_Leo (赞：1)

#### 这题应该也可已算是bfs的模板题了
##### 坑点
1. 需要特判当目标就是一时
2. 输出必须加换行（AT风格）
3. 变化可以从多的变少

最后附上AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
bool used[20010];
int m,n;
struct node//记录状态
{
	int len;
	int step;
};
struct data//记录操作
{
	int a;
	int b;
}p[90010];
queue <node> Q;
int main()
{
	memset(used,0,sizeof(used));
	scanf("%d %d",&m,&n);
	if(n==1)
	{
		printf("1\n");
		return 0;
	}
	for(int i=1;i<=m;i++)
		scanf("%d %d",&p[i].a,&p[i].b);
	Q.push(node{1,1});
	used[1]=1;
	while(!Q.empty())
	{
		node u=Q.front();
		Q.pop();
		for(int i=1;i<=m;i++)
		{
			if(u.len<p[i].a)continue;//如果个数不够进行操作 
			node v;
			v.len=u.len-p[i].a+p[i].b;
			v.step=u.step+1;
			if(v.len>n+300)continue;
			if(used[v.len])continue;//已经存在过各种情况
			if(v.len==n)
			{
				printf("%d\n",v.step);
				return 0;
			}
			Q.push(v);
			used[v.len]=1;
		}
	}
	printf("-1\n");
	return 0;
}
```
可以进行的优化（没加上，就口述想法了）

刚输入进来时，按照这种操作需要的1的个数进行排序（这样在以后如果不行，之后的也都不可以进行了）

---

## 作者：FlyfishO25 (赞：0)

现在让我们看看这道BFS~~水~~题吧

### **1.题目分析**
先看题, 题目要求我们把一个1通过输入的某些规则变换成 $N$ 个1

```cpp
例子:

将一个1变成五个1, 

规则为：
1->111−>11;
111->11111

则:
一个11变成11111需要经过下面这些步骤：
1->11

11->111

111->1111
变化次数为3，故答案为4。
```
很容易能想到使用**BFS**算法

- **搜索要求**

	1. 起始点: 一个1
   2. 终止(跳出条件): N个1
   3. 答案: 在符合变化规则的情况下**最小的变化次数** (类似**最短路**)
   
### **3.代码区**

我知道这是你们想看的

#### 版本一(无优化):

```cpp
//1->1
#include<bits/stdc++.h>
using namespace std;

struct change{
    int first;
    int second;
}c[90001];//存放变化的结构体,first记录需要的1,second记录改变后变成了几个1

struct one{
    int x, change_time;
};//存放一的结构体,记录了现有一的数量和变化的次数

queue<one> Q;
int n, m;
bool vis[20000];

int main(){
    cin>>m>>n;
    for(int i = 1;i <= m;++i){
        cin>>c[i].first>>c[i].second;
    }
    if(n == 1){
        //注意, 由于下面的搜索无法遍历到一, 所以遇到一直接输出
        cout<<1<<endl;
        return 0;
    }
    sort(c+1, c+m+1, cmp);
    Q.push((one){1, 1});
    vis[1] = true;
    while(!Q.empty()){
        one tmp = Q.front();
        Q.pop();
        for(int i = 1;i <= m;++i){
            if(tmp.x >= c[i].first){
                //如果当前1的数量大于变化需要的1的数量
                one tp;
                tp.change_time = tmp.change_time + 1;
                tp.x = tmp.x-c[i].first+c[i].second;
                //这个数量之前没有遍历到且没有超限
                if(!vis[tp.x] && tp.x < n+300){
                    //一的个数达到了需求
                    if(tp.x == n){
                        //输出变化的次数                        
                        cout<<tp.change_time<<endl;
                        return 0;
                    }
                    //如果没有达到需求,标记
                    vis[tp.x] = true;
                    //放入队列供下次搜索
                    Q.push(tp);

                }
            }
        }
    }
    //遍历完也搜不到输出-1
    cout<<-1<<endl;
    return 0;
}
```

#### 版本2(参考[@Max_Leo](https://www.luogu.com.cn/user/126038)的优化思路):

```cpp
//1->1
/*
优化思路:
按照需要1的个数对规则进行排序
在搜索时因为已经排序所以如果一个没有搜到其他的也不需要搜了
*/
#include<bits/stdc++.h>
using namespace std;

struct change{
    int first;
    int second;
}c[90001];//存放变化的结构体,first记录需要的1,second记录改变后变成了几个1

struct one{
    int x, change_time;
};//存放一的结构体,记录了现有一的数量和变化的次数

bool cmp(const change &a, const change &b){
    return a.first < b.first;
}

queue<one> Q;
int n, m;
bool vis[20000];

int main(){
    cin>>m>>n;
    for(int i = 1;i <= m;++i){
        cin>>c[i].first>>c[i].second;
    }
    if(n == 1){
        //注意, 由于下面的搜索无法遍历到一, 所以遇到一直接输出
        cout<<1<<endl;
        return 0;
    }
    sort(c+1, c+m+1, cmp);
    Q.push((one){1, 1});
    vis[1] = true;
    while(!Q.empty()){
        one tmp = Q.front();
        Q.pop();
        for(int i = 1;i <= m;++i){
            if(tmp.x >= c[i].first){
                //如果当前1的数量大于变化需要的1的数量
                one tp;
                tp.change_time = tmp.change_time + 1;
                tp.x = tmp.x-c[i].first+c[i].second;
                //这个数量之前没有遍历到且没有超限
                if(!vis[tp.x] && tp.x < n+300){
                    //一的个数达到了需求
                    if(tp.x == n){
                        //输出变化的次数                        
                        cout<<tp.change_time<<endl;
                        return 0;
                    }
                    //如果没有达到需求,标记
                    vis[tp.x] = true;
                    //放入队列供下次搜索
                    Q.push(tp);

                }
            }
            else{
                break;
            }
        }
    }
    //遍历完也搜不到输出-1
    cout<<-1<<endl;
    return 0;
}
```

##### 题外话:这个优化竟然比没优化还慢就离谱


---

