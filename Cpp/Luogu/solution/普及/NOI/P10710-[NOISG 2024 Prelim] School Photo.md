# [NOISG 2024 Prelim] School Photo

## 题目背景

翻译自 [NOI SG 2024 Prelim C.School Photo](https://github.com/noisg/noi-2024-prelim)。

## 题目描述

Zane 是 NOI 学校的校长。NOI 学校有 $n$ 个班，每个班有 $s$ 名同学。第 $i$ 个班中的第 $j$ 名同学的身高是 $a_{i,j}$。

现在 Zane 想从每个班上选出一名同学拍照，使得这 $n$ 名同学中最高的同学和最低的同学的身高差最小。

请你输出这个最小值。

## 说明/提示

### 【样例 #2 解释】

选择 $a_{1,3},a_{2,2},a_{3,2}$，答案为 $8-4=4$。

### 【数据范围】

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$0$|$0$|样例|
|$1$|$11$|$n=2$|
|$2$|$22$|$n,s\le100$|
|$3$|$9$|$n,s\le250$|
|$4$|$33$|$n,s\le500$|
|$5$|$25$|无|

对于 $100\%$ 的数据，$1\le n,s \le 1000,1\le a_{i,j} \le 10^9$。

## 样例 #1

### 输入

```
2 3
2 1 8
5 4 7
```

### 输出

```
1```

## 样例 #2

### 输入

```
3 3
3 1 4
2 7 18
9 8 10```

### 输出

```
4```

# 题解

## 作者：大宋宝宝 (赞：30)

[题目传送门](https://www.luogu.com.cn/problem/P10710)

# **思路**

首先把数组排序，然后用双指针维护数组，因为要想最大身高差最小，一定是选排序后在数组里连续的一段最优，其中一些人所在的班级有重复也没关系，可以不带他们拍照。

## **Code：**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,s,sum,l=1,ans=INT_MAX,cnt,tong[1001];
//ans表示最终答案，sum表示照片有几个不同班级的人 
struct ts {
	int sg,bj;
	//sg表示学生的身高，bj表示学生的班级 
}a[1000001];
bool cmp(ts a1,ts a2) {
	return a1.sg<a2.sg;
}
int main() {
	cin>>n>>s;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=s;j++) {
			cin>>a[++cnt].sg;
			a[cnt].bj=i;
			//读入，初始化学生的班级 
		}
	}
	sort(a+1,a+cnt+1,cmp);
	//按升序排序 
	for(int i=1;i<=cnt;i++) {
	//l表示左端点，i表示右端点 
		if(!tong[a[i].bj]) sum++;
		//如果这个学生所在的班级之前没有人在合照里出现过 
		//就让不同班级的人数加一 
		tong[a[i].bj]++;
		//这个班来的人数加一 
		if(sum==n) {
		//如果人齐了 
			while(tong[a[l].bj]>=2) tong[a[l++].bj]--; 
			//就尝试移动左端点，直到再移就不满足要求 
			ans=min(ans,a[i].sg-a[l].sg);
			//如果现在的答案更优，就更新答案 
		}
	}
	cout<<ans;
	//输出 
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/173818363)

本蒟蒻第一次写题解，求过

---

## 作者：Const_ (赞：11)

# P10710 题解
本题类似于[P1638逛画展](https://www.luogu.com.cn/problem/P1638)，是一道练习双指针维护区间的好题。

## **解题思路**
  
进行排序，然后用双指针维护被选中的区间。

### 数据结构  
对于 $n,s\leq1000$ 的数据范围，暴力肯定拿不到分，可以建立结构体存储学生班级和身高，再全部放进一个列表里进行排序，尝试利用排序后的有序性解题，结构体代码如下：

```cpp
struct stu
{
	int cls,h;//班级，身高
}a[1000005];
bool cmp(stu x,stu y)
{
	return x.h<y.h;
}
```
### 维护区间  
考虑到使用 $l,r$ 两个指针来维护拍照同学的区间 $[l,r]$，利用 $a$ 数组的有序性，两个指针只需要前进就可以维护这个区间，不难想到：  
1. 当区间没有包含所有班级时，增加 $r$ 来扩大这个区间；   
2. 当序列包含所有班级时，记录答案，并增大 $l$ 来寻找更优解；   


### **如何判断区间内包含所有班级？**

使用一个数组 $cnt[]$ 和变量 $sum$，其中 $$cnt _ {i} $$ 表示区间内有几个 $i$ 班级的人，$sum$ 表示区间内有几个班级，对于 $$cnt _ {i}$$ 的每次修改，如果其从 $0$ 变为 $1$ 或从 $1$ 变为 $0$，则修改 $sum$ 的值，移动指针代码如下：

```cpp
void move_r()
{
	r++;
	if(!cnt[a[r].cls]) sum++;
	cnt[a[r].cls]++;
}
void move_l()
{
	ans=min(ans,a[r].h-a[l].h);
	cnt[a[l].cls]--;
	if(!cnt[a[l].cls]) sum--;
	l++;
}
```
最后进行循环，根据判断移动指针即可。
代码时间复杂度为 $O(n\log n)$ 级别的，其中双指针
是 $O(n)$ 级别，排序是 $O(n\log n)$ 级别，可以通过本题。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,i,j,top,l,r,sum,cnt[1005],ans=INT_MAX;
struct stu
{
	int cls,h;//班级，身高
}a[1000005];
bool cmp(stu x,stu y)
{
	return x.h<y.h;
}
void move_r()//更新右指针
{
	r++;
	if(!cnt[a[r].cls]) sum++;
	cnt[a[r].cls]++;
}//cnt用于记录区间内每个班级的人数
void move_l()//更新左指针
{
	ans=min(ans,a[r].h-a[l].h);//更新答案
	cnt[a[l].cls]--;
	if(!cnt[a[l].cls]) sum--;
	l++;
}//sum维护区间内有几个班级
int main()
{
    cin>>n>>s;
    for(i=1;i<=n;i++) 
	{
		for(j=1;j<=s;j++)
		{
			cin>>a[++top].h;
			a[top].cls=i;
		} 
	}//双指针的前提是序列有序
    sort(a+1,a+1+top,cmp);
	l=1,r=0,sum=0;//l指向区间内最低的人,r指向区间内最高的人
	while(l<=top&&r<=top)
	{//如果不满足条件,增大区间
		if(sum!=n) move_r();
		else move_l();
	}//如果满足条件,缩小区间(即缩小身高差)
	cout<<ans;
    return 0; 
}
```

---

## 作者：Moya_Rao (赞：8)

# 题目大意
一所学校有 $n$ 个班级，每个班级有 $s$ 人。  
现在要在每个班里选出一个人进行拍照。  
为了照片的美观性，要使选出的这 $n$ 个人中最高的人与最矮的人的身高差距最小，请你求出这个最小值。

# 思路
我们可以想到用双指针来解决这个问题。

“要在每个班里选出一个人”的问题很麻烦，我们不好去一个一个班级来挑，毕竟有 $n$ 个班级嘛，又不是只有两个。

因此，我们可以把所有同学放进一个一维数组里，而不是一个一个对应的放进二维数组。这样就好挑了。  
不过当然是要先排个序啦。

那么怎么挑选这些人呢？我们可以用一种类似于 [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)的方法，用两个指针 $l$ 和 $r$ 分别维护左端点和右端点。

当班级种类数不够时我们就不断的把右指针 $r$ 向右移，并把这个人加进来。当然了，加进来的时候要判断这个人是不是一个新的班级的人，如果是的话，班级种类数就要加上 $1$。

等班级种类够了以后，我们就要看，前面有没有多余的人可以排除掉，也就是把那些并不是唯一一个在这个班级里的人给删除掉。就一直让左指针 $l$ 向右移，直到左边再没有多余的人可以删掉了。

删完人以后，再看看班级种类数是不是正好为 $n$。如果是的话，就尝试更新答案。

没了么？不，我们还要删掉最左边的那个人，使得左右指针一直在移动。否则啊，你的程序就会一直死循环在那里。因为你没有让他去探索新的方案，而是一直呆在原地不动。  
因此操作完一轮后，要再让左指针 $l$ 往右移一个。那么班级种类数会不会减少呢？肯定会的，要不然早就被当成多余的人给删掉了。

---
### 举例

拿下面这组数据来看看吧。
```
3 2
13 1 
7 8
9 10
```

首先我们拿到所有的人，并把他们按照身高拍好了序，像这样：

```
下标：1 2 3 4 5  6
班级：1 2 2 3 3  1
身高：1 7 8 9 10 13
```

接着，我们的右端点 $r$ 先会移到下标为 $4$ 的位置。  
然后删掉多余的，但发现没有多余的可删。
这时更新我们的 $ans$ 变为 $9-1=8$。  
要再把 $l$ 变到 $2$，让后面继续推进。

下一轮，  
右端点 $r$ 变成了 $6$。  
再来删掉多余的，发现可以删掉一个，$l$ 变为 $3$。  
则此时的身高差距为 $13-8=5$，比之前 $ans$ 的 $9$ 要小，因此更新 $ans$ 为 $5$。  
把 $l$ 变到了 $4$，让后面继续推进。

再下一轮，  
右端点移不动。  
倒是可以删掉多余的，$l$ 移成了 $5$。  
但发现此时并没有把所有班级都包含在里面，因此不更新 $ans$。  
把 $l$ 变到了 $6$，让后面继续推进。

最后一轮，  
右端点还是移不动。  
也没有什么多余的人可删。  
也没有把所有班级含在里面，也不更新。  
$l$ 变成了 $7$，越界了，跳出循环。

因此最终的答案为 $5$，是选择 $1$ 号班级的第 $1$ 位同学（身高为 $13$）、$2$ 号班级的第 $2$ 位同学（身高为 $8$）和第三个班级的第 $1$ 位同学（身高为 $9$）或第 $2$ 位同学（身高为 $10$）来进行拍照的。  
其中最高身高为 $13$，最低身高为 $8$，差值为 $13-8=5$，是最小的。

---

懂了么？

#  [AC](https://www.luogu.com.cn/record/174343297) 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct student{
    int clss,heit;
    //clss 表示班级，heit 表示身高
}a[1000005];
int n,s,cnt,l,r,v[1005],num,ans=0x3f3f3f3f;//ans 赋极大值
bool cmp(student s1,student s2){
    return s1.heit<s2.heit;
}//按身高排序
int main(){
    cin>>n>>s;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=s;j++){
            int x;
            cin>>x;
            a[++cnt]=student{i,x};//塞进数组
        }
    }
    sort(a+1,a+cnt+1,cmp);//排个序
    l=1,r=1,num=1,v[a[1].clss]++;//初始化
    while(l<=r&&r<=cnt){//双指针
        while(num<n&&r<cnt){//如果班级不够，继续加
            v[a[++r].clss]++;
            if(v[a[r].clss]==1)num++;
        }
        while(v[a[l].clss]>1)
            v[a[l++].clss]--;//如果有多余班级的人，删掉
        if(num==n)
            ans=min(ans,a[r].heit-a[l].heit);//如果正好满足，更新答案
        v[a[l++].clss]--;//把这个人删掉
        num--;
        //由于他没有被上面的 while 删掉，因此他是这个班级的最后一员
        //所以班级种类减少了
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：zhang_Jimmy (赞：7)

我们可以用双指针法来解决这道题。

首先，如果想要用双指针法来解决问题，序列要满足有序性。所以这里我们要将所有身高从小到大排序。 

接下来我们就可以用双指针法来求解了。使用 $l,r$ 两个指针来维护拍照同学的区间 $[l,r)$：
- 如果区间没有包含所有的班级，让 $r$ 右移。
- 否则，让 $l$ 右移。

怎么判断区间有没有包含所有的班级呢？我们可以定义一个变量 $sum$，当每有一个元素加入的时候，判断区间里是不是没有这个班级的人，如果是，让 $sum \gets sum + 1$。在有元素退出的时候，要判断元素退出后区间里还有没有这个班级的人了，如果没有了，让 $sum \gets sum - 1$。

这里我还定义了一个 $cnt$ 数组，用来统计 $[l,r)$ 区间里每个班级被覆盖的次数。

代码：


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1e6 + 5;
struct student{int height, cls;}a[N];
int n, m, sum, top;
int cnt[N];

bool cmp(student a, student b){return a.height <= b.height;}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++){
            int x;
            scanf("%d", &x);
            a[++top].height = x;
            a[top].cls = i;
    }
    sort(a + 1, a + top + 1, cmp);
    int l = 1, r = 1, ans = 2e9;
    while(l <= r && r <= top + 1){
        if(sum < n){   
            cnt[a[r].cls] ++;
            if(cnt[a[r].cls] == 1) sum ++;
            r ++;
        } else {
            ans = min(ans, a[r - 1].height - a[l].height);
            cnt[a[l].cls] --;
            if(cnt[a[l].cls] == 0) sum --;
            l ++;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：zhangshiyan (赞：4)

# P10710 [NOISG2024 Prelim] School Photo
[提交记录：R170127599](https://www.luogu.com.cn/record/170127599)

## Main Idea
有所学校有 $n$ 个班，每个班有 $s$ 名同学。第 $i$ 个班中的第 $j$ 名同学的身高是 $a_{i,j}$。

现在从每个班上选出一名同学，使得这 $n$ 名同学中最高的同学和最低的同学的身高差最小。

## Solution
本题算法：双指针。
1. 先对这 $n \times m$ 人的身高进行排序。由于要使身高差尽可能小，所以同学身高在排完序后要尽可能相邻。

1. 定义两个指针 $l$ 和 $r$ 。

1. 每次先移动 $r$ ，直到 $\lbrack l , r \rbrack$ 包含所有班级的人。然后移动 $l$ ，也就是删掉 $l$ 这个位置的数，然后判断满不满足。

如果 $l$ 到 $r$ 间不包含所有班级的同学，那么将 $r$ 右移，否则记录答案并将 $l$ 右移。不断进行操作，直到 $l > r$ 或 $r$ 超出边界为止。

## Code
```cpp
#include <bits/stdc++.h>
#define INF 1e15
using namespace std;
typedef long long ll;
inline ll read()//快读
{
	register ll x = 0, f = 1;
	register char ans = getchar();
	while (ans < '0' || ans > '9')
	{
		if (ans == '-')
			f = -1;
		ans = getchar();
	}
	while (ans >= '0' && ans <= '9')
	{
		x = x * 10 + ans - 48;
		ans = getchar();
	}
	return x * f;
}

ll n, s, m;
ll cnt, ans = INF;
ll c[1000005], sum[1000005];

struct student
{
	ll h, id, c;
	// h:身高, id:在原数组的位置, c:从这个班选c名同学
} a[1000005];

bool cmp(student x, student y)//按照高度从小到大排序
{
	return x.h < y.h;
}


void add(ll r)
{
	if (++sum[a[r].id] == a[r].c)
	{
		cnt++;
	}
}

void del(ll l)
{
	if (--sum[a[l].id] < a[l].c)
	{
		cnt--;
	}
}

int main()
{
	n = read(), s = read();
	for (ll i = 1; i <= n; i++)
	{
		c[i] = 1;
		for (ll j = 1; j <= s; j++)
		{
			a[++m].h = read(), a[m].id = i, a[m].c = 1;
		}
	}
	sort(a + 1, a + m + 1, cmp);
	ll l = 1, r = 1;
	while (l <= r && r <= m + 1)
	{
		if (cnt < n)
		{
			add(r);
			r++;
		}
		else
		{
			ans = min(ans, a[r - 1].h - a[l].h); //由于a[]数组是有序的，所以可以直接用最后一个人的身高减去第一个人的身高
			del(l);
			l++;
		}
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：sherry_lover (赞：3)

# P10710 [NOISG2024 Prelim] School Photo 题解

[题目传送门](https://www.luogu.com.cn/problem/P10710)

### 思路

先对每个班级的身高分别排序，好找最小值和最大值。考虑利用双指针求解。

1. 初始化一个大小为 $n$ 的指针数组，每个指针初始指向每组数据的开头（即排序后的最小值）。
2. 维护一个当前最小值和当前最大值的区间。
3. 在每一步中，找到当前指针数组中的最小值和最大值，并计算它们的差值。记录当前差值和对应的区间。
4. 将指向最小值的指针向后移动一位，更新区间，直到某一个指针超出其组的范围为止。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1005][1005],p[1005],ans = 0x3f3f3f3f,minn,maxx,minidx,maxidx;
int main()
{
	cin >> n >> m;
    for(int i = 1;i <= n;i++)
	{
        for(int j = 1;j <= m;j++)
		{
            cin >> a[i][j];
        }
        sort(a[i]+1,a[i]+m+1);
    }
    for(int i = 1;i <= n;i++) p[i] = 1;
    while(1)
    {
    	minn = 0x3f3f3f3f,maxx = -0x3f3f3f3f,minidx = -1,maxidx = -1;
        for(int i = 1;i <= n;i++)
		{
            if(p[i] > m)
            {
            	cout << ans;
            	return 0;
			}
            if(a[i][p[i]] < minn)
			{
                minn = a[i][p[i]];
                minidx = i;
            }
            if(a[i][p[i]] > maxx)
			{
                maxx = a[i][p[i]];
                maxidx = i;
            }
        }
        ans = min(ans,maxx-minn);
        p[minidx]++;   	
	}
    return 0;
}
```

但这样时间复杂度是 $O(n^2m)$ 的，无法通过本题。考虑用优先队列优化找当前指针数组中的最小值和最大值的操作，这样时间复杂度是 $O(nm \log n)$ 的，可以通过本题。

[通过记录](https://www.luogu.com.cn/record/164576643)

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1005][1005],p[1005],ans = 0x3f3f3f3f,num;
priority_queue<int> maxx;
priority_queue<pair<int,int> > minn;
int main()
{
	cin >> n >> m;
    for(int i = 1;i <= n;i++)
	{
        for(int j = 1;j <= m;j++)
		{
            cin >> a[i][j];
        }
        sort(a[i]+1,a[i]+m+1);
        maxx.push(a[i][1]);
        minn.push({-a[i][1],i});
    }
    for(int i = 1;i <= n;i++) p[i] = 1;
    while(1)
    {
    	auto u = minn.top();
    	minn.pop();
    	num = maxx.top();
        ans = min(ans,num-(-u.first));
        p[u.second]++;
		if(p[u.second] > m) break;
		maxx.push(a[u.second][p[u.second]]);
		minn.push({-a[u.second][p[u.second]],u.second});
	}
	cout << ans;
    return 0;
}
```

---

## 作者：_H17_ (赞：2)

## 题目分析

考虑把整个班级从矩阵拍平成序列（记录高度、班级）。

然后按照高度从小到大排序。考虑使用队列维护所选区间，队首就是最小的，队尾是最大的。

以下我们称班级为“颜色”。

如果某一个颜色在队尾已经入队，同时队首也是这个颜色，那么就可以把队首出队，同时维护当前不同颜色的数量，当所有颜色都有时更新答案。

## 代码

```cpp
#include<bits/stdc++.h>
#define ALL(x) x.begin(),x.end() 
using namespace std;
int n,s,vis[1001],cnt,ans=0x3f3f3f3f;
vector<pair<int,int> >vec;
queue<pair<int,int> >q;
int main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++)
		for(int j=1,val;j<=s;j++){
			cin>>val;
			vec.push_back({val,i});//拍平
		}
	sort(ALL(vec));//排序
	for(int i=0;i<vec.size();i++){
		if(!vis[vec[i].second])
			cnt++;//记录颜色数
		vis[vec[i].second]++;
		q.push(vec[i]);
		while(vis[q.front().second]>1){
			vis[q.front().second]--;//删除多余的
			q.pop();
		}
		if(cnt==n)//符合条件
			ans=min(ans,q.back().first-q.front().first);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：xuchenxi (赞：2)

## P10710题解

[题目传送门](https://www.luogu.com.cn/problem/P10710)

### 题意理解

共有 $n$ 个班，每班 $s$ 名同学。已知每位同学的身高，分别从每班找一人使得身高最大值和最小值之差最小。输出这个最小值。

### 思路分析

一道双指针的题目~~题目标签上看到的~~。

用一个结构体 $node$ 存储每位学生的班级 $ban$ 和身高 $num$。用 $a$ 存储每位学生的信息。

因为要求最大值和最小值之差的最小值，所以可以先把所有人按身高大小进行排序。然后再用双指针 $(l,r)$ 遍历数组。

如果排序后 $a _ {l}$ 和 $a _ {r}$ 之间包含了所有班级的学生，$l+1$ 并更新最小值 $ans$，否则 $r+1$。注意区间范围在数组范围内。

AC Code

```
#include<bits/stdc++.h>
#define int long long
#define INF 2147483647
using namespace std;
const int maxn=1005;
struct node{int ban,num;};
int n,s;
int c[maxn];
bool vis[maxn];
int ans=INF;
node a[maxn*maxn];
bool cmp(node a,node b){return a.num<=b.num;}
signed main()
{
	cin>>n>>s;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=s;j++)
		{
			int x;
			cin>>x;
			a[(i-1)*s+j]=(node){i,x};
		}
	sort(a+1,a+n*s+1,cmp);
	int l=1,r=1,cnt=0;
	while(l<=r && r<=n*s+1)
	{
		if(cnt<n)
		{
			c[a[r].ban]++;
			if(c[a[r].ban]==1) cnt++;
			r++;
		}
		else
		{
			ans=min(ans,a[r-1].num-a[l].num);
			c[a[l].ban]--;
			if(!c[a[l].ban]) cnt--;
			l++;
		}
	}
	cout<<ans;
}
```
END

---

## 作者：Jorisy (赞：2)

首先很难不发现，我们如果把这 $n\times m$ 个数升序排起来，要使得差尽可能小，所选的那些数一定是靠得近的。

于是我们可以想到用双指针来处理这 $n\times m$ 个数。

如果 $[l,r]$ 内并不包含所有班级的人，那么 $r$ 右移；否则，处理答案，并将 $l$ 右移。
```cpp
#include<bits/stdc++.h>
using namespace std;

pair<int,int>a[1000005];
int n,m,f[1005],ans=INT_MAX; 

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			int p=(i-1)*m+j;
			cin>>a[p].first;
			a[p].second=i;
		}
	}
	sort(a+1,a+n*m+1);
	int l=1,r=1,t=1;
	f[a[1].second]++;
	while(l<=r)
	{
		if(t<n)
		{
			if(r<n*m) t+=++f[a[++r].second]<2;
			else break;
			continue;
		}
		ans=min(ans,a[r].first-a[l].first);
		t-=!--f[a[l++].second];
	}
	cout<<ans;
 	return 0;
}
```

---

## 作者：Guagua111 (赞：1)

## 思路
这道题我们使用双指针来解。

我们将 $a$ 数组拍平成一维数组，然后排序。利用 $a$ 数组的有序性，维护两个指针 $l, r$ 表示左边界与右边界。

接下来，我们会遇到两种情况：第一种，$[l, r]$ 这个区间里没有包含所有的班级。这时我们将 $r$ 自增。第二种，$[l, r]$ 包含了所有的班级。这时更新答案 $ans$，并令 $l$ 自增以进一步寻找最优解。

问题是，如何 $\mathcal O(1)$ 判断区间里是否包含所有的班级呢？

我们可以使用一个桶 $t$ 来维护区间里每个教室的同学数量，并使用 $sum$ 记录区间里不同教室的数量。这时我们写出以下代码：

```cpp
if (sum < n) { //如果没有包含所有教室
	r++; //右指针右移（新增一个同学）
	if (t[a[r].c] == 0) sum++; //如果这个同学来自一个新的教室，sum++
	t[a[r].c]++; //他所在教师的人数 ++
} else { //如果包含了全部教室
	ans = min(ans, a[r].h - a[l].h); //更新答案
	t[a[l].c]--; //由于将要失去左边界的同学，所以教室人数 --
	if (t[a[l].c] == 0) sum--; //这个教室没有学生了，意味着失去了一个教室，sum--
	l++; //左边界右移
}
```

最后输出 $ans$ 即可。

## 代码
```cpp
#include <algorithm> //sort
#include <iostream> //cin, cout
using namespace std;
int n, s, len, sum, t[1000005], ans = 0x7fffffff;

struct Node {
	int c, h; //c 表示教室，h 表示身高
	Node (int c = 0, int h = 0) : c(c), h(h) //构造函数
} a[1000005];

bool cmp(Node x, Node y) { //比较函数
	return x.h < y.h;
}

int main() {
	cin >> n >> s;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= s; j++) {
			int h;
			cin >> h;
			a[++len] = Node(i, h); //输入
		}
	}
	sort(a + 1, a + len + 1, cmp); //排序
	int l = 1, r = 0; //定义左边界与右边界
	while (l <= len && r <= len) {
		if (sum < n) {
			r++;
			if (t[a[r].c] == 0) sum++;
			t[a[r].c]++;
		} else {
			ans = min(ans, a[r].h - a[l].h);
			t[a[l].c]--;
			if (t[a[l].c] == 0) sum--;
			l++;
		}
	}
	cout << ans; //输出答案
	return 0;
}

```
如果这篇题解能够通过，那么就是我的第一篇题解了。希望大家多多指教，也希望管理员认真审核！

---

## 作者：细数繁星 (赞：1)

## 做法

双指针练习题，定义指针 $l,r$，接着把整个矩阵打散，排序。不断去移动，如果包含的班级少了，移动右指针，否则移动左指针。

**一个班级只能被包含一次，所以要多定义一个变量，为 $[l,r]$ 区间，单个班级被覆盖的次数。**

## 代码

```cpp
#include <bits/stdc++.h>
#define rty printf("Yes\n");
#define RTY printf("YES\n");
#define rtn printf("No\n");
#define RTN printf("NO\n");
#define rep(v,b,e) for(int v=b;v<=e;v++)
#define repq(v,b,e) for(int v=b;v<e;v++)
#define rrep(v,e,b) for(int v=b;v>=e;v--)
#define rrepq(v,e,b) for(int v=b;v>e;v--)
#define stg string
#define vct vector
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void solve() {
	
}


int n, s, cnt = 0, r = 1, l = 1, among = 0, ans = INT_MAX;
int isin[(int)1e6 + 5];
pair<int, int> p[(int)1e6 + 5];

main() {
//	int t; cin >> t; while (t--) solve();
  cin >> n >> s;
  rep(i, 1, n) {
    rep(j, 1, s) {
      cin >> p[++cnt].first;
      p[cnt].second = i;
    }
  }
  sort(p + 1, p + cnt + 1);
  while (l <= r && r <= cnt + 1) {
    if (among < n) {
      among += (++isin[p[r].second] == 1);
      r++;
    } else {
      ans = min(ans, p[r - 1].first - p[l].first);
      among -= (!(--isin[p[l].second]));
      l++;
    }
  } 
  cout << ans;
	return 0;
}
```

---

## 作者：llqw (赞：1)

### 思路：

很明显是个双指针，~~因为标签上面说了~~，暴力也很好打，直接爆搜就行。

这道题首先不能把它的班级拆开来看，要把它们整合到一个数组里面去，然后~~众所周知~~，双指针是需要单调性的，所以我们把数组排成升序（降序也行，无所谓的）。然后再在数组上操作，但题目要求我们要从每个班里都要选一个人出来，所以我们需要判断当前区间 $[l,r]$ 内是否包括了每一个班的人，如果区间 $[l,r]$ 包括了每一个班的人，我们才能更新答案，而当前区间内最大值减去最小值的值，即为 $high_{r}-high_{l}$ （因为我们排序了）。

那么现在问题来了：

1.如何判断当前这个人来自于哪个班？

很简单，将这个人的班级和身高整合为一个结构体，把数组开成结构体，就可以直接查询了。

2.$[l,r]$ 的长度是多少？

不需要去管他的长度是多少，灵活一点，当 $[l,r]$ 没有包含每一个班的人时，我们便一直让 `r++`，直到 $[l,r]$ 包含了每一个班的人。当 $[l,r]$ 包含了每一个的人时，我们便让 `l++`，缩小这个区间，以来减小极差，更新更优的答案，直到 $[l,r]$ 已经无法再缩小的时候。一直循环往复以上过程，即可得出最优解。

3.为什么 `l++` 可以缩小极差，更新到更优的答案

这就是为什么所有的双指针题都需要排序了，我们因为已经将数组排为升序，`l++` 时 $high_{l}$ 只会更大，而 $r$ 又不变，所以 $high_{r}-high_{l}$ 只会更小。

### 代码：


```cpp
#include<bits/stdc++.h>

#define MAXN 1005

using namespace std;

int n,m;
struct node{
	int idx,sg;
}stu[1000005];

int stot;
int f[MAXN];
int ans = INT_MAX-10;

bool cmp(node x,node y){
	return x.sg<y.sg;
}

int main(){
	
//	freopen("1.in","r",stdin);
//	freopen("2.in","w",stdout);

	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			stot++;
			stu[stot].idx=i;
			cin>>stu[stot].sg;
		}
	}
	
	sort(stu+1,stu+stot+1 ,cmp);//排序
	
	int l=1,r=1;
	int nown=0;
	
	while(l<=r and r<=stot+1){//开始双指针
		if(nown<n){//如果当前的班级数不够总班级数，说明还有一些班的人没有被选中
			f[stu[r].idx]++;
			if(f[stu[r].idx]==1){
				nown++;
			}
			r++;
      //扩大区间，选中更多的人
		}else{//说明当前区间满足了从每个班里都要选一个人出来的需求
			f[stu[l].idx]--;
			if(!f[stu[l].idx]){
				nown--;
			}
			ans=min(ans,stu[r-1].sg-stu[l].sg);
			l++;
      //更新答案，缩小区间，寻找更优解
		}
	}
	
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：CheeseFunction (赞：1)

分析下思路：

如果开一个二维数组用于存储同学们的身高，就要另开一个数组做为指针，这里 $n$ ,$m$ 不大，空间的消耗也不明显，可本着精益求精的精神，优化一下：
  1. 本身 $2$ 维数组就是可以展开为 $1$ 维数组（详见图1）：
    图1：

  ![图1](https://cdn.luogu.com.cn/upload/image_hosting/tj6qqin0.png)
  2. 如果利用其可展开性，那么就可以直接双指针
  
  3. 怎么双指针：数据不具备单调性，所以得开个结构体存身高和班级（以方便看区间内是否一个班上就一人选中），接着双指针：
      - 两个距离越近的数差越小。
      - 利用上述思路，就可以判断，打快慢指针。
      - 定义 `left`,`right` 开找，且`right`在找到大小为 $n$ 且满足每个班上的成员数 $\ge 1$ 时就停
      - 找到 `left` = `right` 或 `right`=n 为止。
  
  4. 要一边双指针一边，利用上述思路就可以利用这个特点更新答案。
  5. 最后，就可以提交了！
     
  看一下最后的代码：
```cpp
#include<bits/stdc++.h>
#define ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
struct stu{
	long long xh,value;
};

stu a[1001000]; //写的时候忘看数据了，开这么大也不会爆
int ket[int(1e6+100)];
bool cmp(stu x,stu y){
	return x.value<y.value; 
}
#define int long long
signed main(){
	int n,m,siz=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			int x;
			cin>>x;
			a[++siz].xh=i;	//要么++siz(初始0 ) ，不然一步错，步步错
			a[siz].value=x;
		} 
	sort(a+1,a+siz+1,cmp);
	int l=1,r=1,cnt=0,ans=1e9;	//ans为0就废了(毕竟差不会比零小) 
	while(l<=r && r<=siz+1){
      if(cnt<n){ //一定一定要小于n，等于n是要更新答案的
			ket[a[r].xh]++;
			if(ket[a[r].xh]==1)cnt++;
			r++;
		}else{
			ans=min(ans,a[r-1].value - a[l].value);	//差值，两个越接近的数差值越小
			ket[a[l].xh]--;
			if(ket[a[l].xh] == 0)cnt--;
			l++;
		}
	}
	cout<<ans;	//完结撒花！ 
} 

```

---

## 作者：qfy123 (赞：1)

# P10710
[传送门](https://www.luogu.com.cn/problem/P10710)
## 思路
定义一个结构体，记录一个学生所在的班级 $c$ 以及高度 $h$，并在读入时将所有学生的信息记录在这一个结构体数组 $a$ 里，按照身高升序排列。

现在，这个结构体数组中身高元素具有了单调性。如果你做过[这道题](https://www.luogu.com.cn/problem/P1638)（没做过的建议去做一下），你就很容易想到用双指针维护一个区间内学生所在班级的种类数。当可以在 $[l,r]$ 区间内选出 $n$ 个来自不同班级的人拍照的时候，即在这个区间内班级种类数等于 $n$ 的时候，由于身高具有单调性，那么**左端点对应的学生是这个区间内身高最矮的，右端点对应的学生是这个区间内身高最高的**，此时这个区间内身高的极差就是左右端点的身高之差，统计一次答案，与 $ans$ 取最小值，最后输出 $ans$ 即可。

记 $a$ 数组的长度为 $L$，则总时间复杂度为 $O(L \log L)$，其中 $L = n \times s$。双指针是线性的，瓶颈在于排序。

注：由于个人习惯，在代码里出现的区间是 $[l,r)$ 而非 $[l,r]$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
struct S{
	int c,h;
}s[N*N];
int n,m,tot,l=1,r=1,cnt,bucket[N],ans = 1e9 + 10;
bool cmp(S x,S y){
	return x.h < y.h;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x;
			scanf("%d",&x);
			s[++tot].c = i;
			s[tot].h = x;
		}
	}
	sort(s+1,s+tot+1,cmp);
	while(l<=r && r<=tot+1){
		if(cnt < n){ // 如果区间内学生所在的班级种类数没有到n，就将右端点向右移，扩大区间
			bucket[s[r].c]++;
			if(bucket[s[r].c] == 1) cnt++;
			r++;
		}else{// 如果区间内学生所在的班级种类数达到了n，就统计答案，并将左端点向右移，缩小区间
			ans = min(ans,s[r-1].h - s[l].h);
			bucket[s[l].c]--;
			if(bucket[s[l].c] == 0) cnt--;
			l++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/166913333)

---

## 作者：Tomle (赞：0)

# 思路

首先，我们每个班所有人的身高排序，这是为了得到一个**单调性**，对之后统计答案有帮助。

我们令 $p_i$ 表示班级 $i$ 选的人的编号（下标），初始时默认 $p_{1\sim n} = 1$。

为了让答案变小，我们要让选的人身高最小的班级（设为 $a$）往后选人（$p_a\gets p_a+1$），若 $p_a=s$，则不变。

上述操作我们可以使用**优先队列**（`priority_queue`）维护。

答案为 $maxn-minn$，$minn$ 正是我们维护的，而 $maxn$ 因为每个班的身高是**有序**的，所以其值是**单调不降**的，因此我们可以全局维护 $maxn$。

# 小细节

每次查询优先队列（`q.top()`）的值不一定就是 $minn$，这样忽略了那些 $p_i=s$ 的班级所带来的贡献，因此，我们还要记录下这些班级的最小值。

# code

随手卡常，码风轻喷。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef pair <int, int> pii;

int a[1005][1005], b[1005], c[100005];

inline void read(register int &a, register int ch = 0) {
	while (!isdigit(ch = getchar()));
	for (a = 0; isdigit(ch); ch = getchar()) a = (a << 3) + (a << 1) + (ch ^ 48);
}
int main() {
	register int n, s, maxx = 0, ans = INT_MAX, r = INT_MAX, p[1005];
	register priority_queue <pii, vector <pii>, greater <pii> > q;
	read(n), read(s);
	for (register int i = 1; i <= n; ++i) {
		for (register int j = 1; j <= s; ++j) read(a[i][j]);
		for (register int k = 0; k < 32; k += 8) {
			for (register int j = 0; j <= 0xFF; ++j) c[j] = 0;
			for (register int j = 1; j <= s; ++j) ++c[((b[j] = a[i][j]) >> k) & 0xFF];
			for (register int j = 1; j <= 0xFF; ++j) c[j] += c[j - 1];
			for (register int j = s; j; j--) a[i][c[(b[j] >> k) & 0xFF]--] = b[j];
		} // 基数排序
		maxx = max(maxx, a[i][1]);
		q.push({a[i][1], i});
		p[i] = 1;
	}
	while (q.size()) {
		register int x = q.top().first, y = q.top().second; q.pop();
		ans = min(ans, maxx - min(x, r));
		if (++p[y] <= s) {
			maxx = max(maxx, a[y][p[y]]);
			q.push({a[y][p[y]], y});
		} else r = min(r, a[y][s]);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：wangzc2012 (赞：0)

# P10710 [NOISG2024 Prelim] School Photo
## 题目大意
一所学校有 $m$ 个班级，每个班级有 $s$ 名同学，给出每位同学的身高，请从每个班级选出一名同学，使被选出的同学中最高的同学和最低的同学的身高差最小。
## 思路分析
本题使用双指针求解。  
先对所有人的身高进行排序。由于要使身高差尽可能小，所以同学身高在排完序后要尽可能相邻。  
因此，定义两个指针 $l$ 和 $r$。如果 $l$ 到 $r$ 间不包含所有班级的同学，那么将 $r$ 右移，否则记录答案并将 $l$ 右移。不断进行操作，直到 $l>r$ 或 $r$ 超出边界为止。
## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,studentsi=0,sum[1000005];
struct students{  //结构体
    int tall; //身高
    int clas;  //班级
}a[1000005];
bool cmp(students x,students y){
    return x.tall<y.tall;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);  //优化
    cin>>n>>s;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=s;j++){
            cin>>a[++studentsi].tall;  //输入身高
            a[studentsi].clas=i;  //记录班级
        }
    }
    sort(a+1,a+studentsi+1,cmp);  //排序
    int l=1,r=1,cnt=0,ans=1000000000;  //左指针、右指针、指针间包含几个班级的学生、答案
    while (l<=r and r<=studentsi+1){  //注意第29行代码  这里要+1
        if (cnt<n){  //如果不包含所有班级的学生
            sum[a[r].clas]++;  //记录有几个当前班级的学生
            if (sum[a[r].clas]==1) cnt++;  //如果这个班级是新加进来的，班级数量加1
            r++;  //右指针右移
        }
        else{  //包含所有班级的学生
            ans=min(ans,a[r-1].tall-a[l].tall);  //记录答案
            sum[a[l].clas]--;  //将左指针对应的同学的班级数量间1
            if (sum[a[l].clas]==0) cnt--;  //如果这个班级的学生数量为0，包含的班级数量减1
            l++;  //右移左指针
        }
    }
    cout<<ans;  //输出答案
    return 0;
}
```

---

## 作者：zxh923 (赞：0)

# P10710 [NOISG2024 Prelim] School Photo 题解

[题目传送门](https://www.luogu.com.cn/problem/P10710)。

### 思路

考虑双指针。我们把所有数的值和所在班级存下来，然后跑一个双指针。每次先移动 $r$，直到 $[l,r]$ 包含所有班级的人。然后移动 $l$。事实上是先删掉 $l$ 这个位置的数，然后判断满不满足。

这样在把 $l$ 这个位置的值删掉后，判断的是 $[l+1,r]$ 不满足要求了，但是 $[l,r]$ 这个区间事实上还是满足的，而且是一个当前的最优区间。

比方说第一个样例。第一次移动 $r$ 变成 $[1,3]$ 然后移动 $l$ 变成 $[2,3]$，这里的判断是删掉 $2$ 位置就不满足了，但是没有移动，相当于 $[2,3]$ 是其中一个最优合法区间。

### 代码

```
#include<bits/stdc++.h>
#define int long long
#define N 1005
using namespace std;
struct node{
	int id,val;
	bool operator<(const node &t)const{
		if(val!=t.val)return val<t.val;
		return id<t.id; 
	}
}a[N*N];
int n,m,cnt[N],sum;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x;
			cin>>x;
			a[(i-1)*m+j]={i,x};
		}
	}
	sort(a+1,a+n*m+1);
	int l=0,r=0,res=2e18;
	while(l<=n*m&&r<=n*m){
		while(sum!=n){
			r++;
			if(r>n*m)break;
			if(cnt[a[r].id]==0)sum++;
			cnt[a[r].id]++;
		}
		while(sum==n){
			l++;
			if(l>n*m)break;
			if(cnt[a[l].id]==1)sum--;
			cnt[a[l].id]--;
		}
		if(r>n*m)break;
		res=min(res,a[r].val-a[l].val);
	}
	cout<<res;
	return 0;
}
```

---

## 作者：TheForgotten (赞：0)

# P10710 [NOISG2024 Prelim] School Photo 题解

[题目传送门](https://www.luogu.com.cn/problem/P10710#submit)

## 题目大意

有 $n$ 个序列，每个序列有 $s$ 个数，现在从每个序列上选出一个数，使得这 $n$ 个数中最大的数和最小的数的差最小。

## 思路

首先我想起了之前做过的一道双指针模板题，如果 $[l,r]$ 内并不包含所有需要满足的数，那么将右边的指针右移；否则将 $l$ 右移，并且将答案更新。
这道题其实本质上是相同的，但是长度固定为 $n$，所以双指针代码实现更加简单。每次移动后考虑 $n$ 个班级是否全部到齐，到齐后记录答案，取最小值即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
pair<int,int>a[1000005];
int n,s,o[1005],ans=INT_MAX; 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(),cout.tie();
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=s;j++){
			int p=(i-1)*s+j;
			cin>>a[p].first;
			a[p].second=i;
		}
	}
	sort(a+1,a+n*s+1);
	int l=1,r=1,t=1;
	o[a[1].second]+=1;
	while(l<=r){
		if(t<n){
			if(r<n*s) t+=++o[a[++r].second]<2;
			else break;
			continue;
		}
		ans=min(ans,a[r].first-a[l].first);
		t-=!--o[a[l++].second];
	}
	cout<<ans;
 	return 0;
}
```

---

