# Exams

## 题目描述

学生进行期末考试，每个考试时间在$a_i$，Valera和老师约定提前于时间$b_i$进行考试，要求所有考试按照$a_i$的顺序，求Valera最早哪个时间可以结束考试。

## 样例 #1

### 输入

```
3
5 2
3 1
4 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
6 1
5 2
4 3
```

### 输出

```
6
```

# 题解

## 作者：清小秋ovo (赞：7)

# CF479C Exams

读了下翻译，还是有点懵。所以又去读了一遍英文，终于弄明白了。。

题目大意可以大致简略为如下：

```
一个人想要安排期末考试的时间。

考试有两个时间，一个是老师规定的时间，另外一个是他与老师商量好的考试时间。

如果错过了，那就只能按照原来的考试时间考试。

规定：只能按照原定考试的日期顺序进行考试的情况下，输出考完试的日期
```

这样理解是不是就很简单了

首先按照第一个日期（也就是老师规定的日期）排序。

随后检查自己跟老师商量的日期是否同样也为单调递增。

对于每一个 $a_i , b_i$：


如果当前日期小于自己商量的日期，则更新答案，否则设为老师规定的日期。

## 代码

~~（莫名其妙的打了个最优解）~~

```cpp

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;
#define PB push_back

const int N=6000;
int n,ans;

struct nodes{
	int a,b;
};

bool cmp(nodes a, nodes b){//按照ai排序，如果ai相同按照bi排序
	if(a.a!=b.a){
		return a.a<b.a;
	}else return a.b<b.b;
}

nodes q[N];
int main()
{
   ios::sync_with_stdio(0);
   cin.tie(0);
   cin>>n;
   for(int i=0;i<n;i++)cin>>q[i].a>>q[i].b;
   sort(q,q+n,cmp);
   ans=q[0].b; //答案初始为b[0]
   for(int i=0;i<n;i++){
   	if(q[i].b>=ans) ans=q[i].b; //如果答案小于当前日期
   	else ans=q[i].a; //否则只能等ai的时候考
   }
   cout<<ans<<endl;
   return 0;
}
```
完美通过！




---

## 作者：__3E24AC7002AD9292__ (赞：3)

萌新第二篇题解。

有 $n$ 场考试，每一场有一个标准考试的时间和一个提前的时间，如果想提前考必须按照标准考试的时间顺序，如果没有赶上某场考试的提前时间，就只能按照标准时间考试。输出最后一场考试的时间。

定义一个结构体 ```node``` 并存放每场考试的两个规定时间，根据题意规定，需要按照标准考试时间顺序排序来考试，然后如果在轮到某一场考试的时候，提前的那一场的开始的时间点已经过去，那就必须等标准的那一场咯，每场考试之后都记录当前的时间。然后就这样模拟一遍就行啦，很简单吧。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, sum;
struct node{
	int a, b;
} s[100005];
inline bool comp (node o, node p){
	if (o.a == p.a) return o.b < p.b;
	return o.a < p.a;
}
int main(){
	cin >> n;
	for (int i = 1; i <= n; i ++){
		cin >> s[i].a >> s[i].b;
	}
	sort(s + 1, s + n + 1, comp);
	for (int i = 1; i <= n; i ++){
		if (sum > s[i].b) sum = s[i].a;
		else sum = s[i].b;
	}
	cout << sum;
	return 0;
}
```


---

## 作者：幼儿园第一名 (赞：3)

#### 题意：
某个人要参加$n$场考试，每场考试需要$a[i]$或$b[i]$的时间，在所有考试结束后，使用的时间要是一个递增序列，输出最短时间。

#### 思路：
排序，每门课程需要选择最少的时间，如果这个时间$>$前一门课程的时间，就可以累加了。


---

## 作者：bitset_iTM (赞：2)

~~这题翻译太坑了。。。~~

### 题目大意：  
给你 $n$ 个 $a_i$ 和 $b_i$，其中 $a_i$ 表示这场考试原定的时间，而 $b_i$ 则表示这场考试提前的时间。如果想提前考必须按照标准考试的时间顺序。如果没有赶上某场考试的提前时间，就只能按照标准时间考试。输出考最后一场试的时间。  

### 思路：  
显然按照题意模拟。先排序，再定义一个变量 $res$，记录当前考得最后一场试的时间。  

- 当 $b_i > res$ 时，说明没赶上这场提前的考试，只能按照正常时间考：$res = a_i$  
- 否则说明赶上了，更新答案：$res = b_i$  

大概的思路就是这样，废话不多说。上代码  

### Code：  
```cpp
#include <bits/stdc++.h>
using namespace std;

struct node
{
    int a, b;
} f[5001]; //结构体，存储正常考试的时间和提前考的时间

bool cmp(node x, node y) // 排序函数，按以a为关键字从小到大排序
{
    if (x.a != y.a)
        return x.a < y.a;
    return x.b < y.b;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d %d", &f[i].a, &f[i].b);
    
    sort(f + 1, f + n + 1, cmp); //排序
    
    int res = 0;
    for (int i = 1; i <= n; i++) //按题意模拟
    {
        if (res > f[i].b) //见上面的解释
            res = f[i].a;
        else
            res = f[i].b;
    }
    
    printf("%d\n", res);
    return 0;
}
```


---

## 作者：AKPC (赞：2)

### 题意
有 $n$ 场考试，每场考的是不同科目，考试有一个固定的开始时间。  
现在小 V 有特殊情况，对于每场考试都希望能提前考试，所以每场考试小 V 都跟老师说了一个提前于正常考试的时间。  
小 V 如果要考试，则必须按照正常考试的科目顺序去考。如果在准备去按照考某一场考试的时候，发现那场考试已经开始了，就必须等到正常的考试时间之后再去考这一场。考试需要的时间忽略不计。  
求小 V 考完所有考试之后，最早能到什么时候。
### 思路
显然题目需要按照正常考试的科目顺序考，那么需要给正常的时间从小到大排序，然后如果有相同的，此时按照小 V 约定的时间从小到大排序，这显然是最优的（不需要解释）。

然后遍历每场考试，如果能按照提前约定的时间就按约定时间，反之只能按正常时间，每次遍历完记录一下当前的时间即可。
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int x=0;bool f=1;register char c=getchar();
    while (c<48||c>57){if(c=='-') f=0;c=getchar();}
    while (c>=48&&c<=57){x=x*10+(c^48);c=getchar();}
    return f?x:-x;
}
int n=read(),ans;
struct node{int a,b;}v[100005];
inline bool comp(node o,node p) {return o.a==p.a?o.b<p.b:o.a<p.a;}
signed main(){
	for (int i=1;i<=n;i++) v[i].a=read(),v[i].b=read();
	sort(v+1,v+n+1,comp);
	for (int i=1;i<=n;i++) ans>v[i].b?ans=v[i].a:ans=v[i].b;
	cout<<ans;
	return 0;
}
```


---

## 作者：King_duck (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF479C)

这道题的翻译就将题意解释出来了，~~但有些地方有毒~~。

直接进行思路分析。首先我用的是 $pair$ 来存储 $a_i$ 和 $b_i$，然后用 $sum$ 记录一下，如果 $ans$ 已经超过了提前时间，就只能在原时间考试了。

直接上核心代码。

```cpp
cin>>n;
for(long long i=1;i<=n;i++)//不开long long见祖宗 
{
    cin>>g[i].first>>g[i].second;
}
sort(g+1,g+n+1,cmp);//cmp函数自己写吧 
for(long long i=1;i<=n;i++)
{
    if(g[i].b>=ans) 
	{
		ans=g[i].b;
	}
    else 
	{
		ans=g[i].a;
	}
}
cout<<ans;//输出 
```

---

## 作者：To_Carpe_Diem (赞：1)

## 题目描述（翻译）

Valera 是大学的本科生。他的期末考试即将来临，他必须要通过恰好 $n$ 门考试。Valera 是一个聪明的人，他可以在**第一次尝试**时通过任何一门考试。此外，他可以**在一天内考多门考试**，并且可以以**任意顺序**进行考试。

根据考试时间表，他可以在第 $i$ 门课程上考试的日期是 $a _ {i}$ 。然而，Valera 与每一门课的教师都进行了安排，允许他在 $b _ {i}$ 之前的时间来进行考试（其中 $b _ {i} < a _ {i}$ ）。因此，Valera 可以选择在第 $i$ 门课程上的考试要么在 $a _ {i}$ 的日期上进行，要么在 $b _ {i}$ 的日期上进行。所有的教师都会在实际考试的日期将考试记录在学生的**记录册**中，并将考试的日期记为 $a _ {i}$。

Valera 认为，如果记录册中的记录**不按照**非递减的日期排序，那将会很奇怪。因此，他请你帮助他。找到当 Valera 按照**非递减的日期顺序进行考试**时，他可以进行最后一门考试的**最小日期**。

## 题目分析

Valera 需要按照**非递减**日期的顺序进行考试，所以我们需要找到最早可以进行最后一门考试的日期。

我们可以对考试时间表中的考试按照**开始时间**进行排序。

然后，我们用一个变量 `lastExam` 来记录最后一门考试的时间。我们从第一门考试开始，将其结束时间存储在 `lastExam` 中。

接下来，我们遍历剩余的考试，如果当前考试的结束时间**不小于** `lastExam`，则将 `lastExam` 更新为当前考试的结束时间；否则将 `lastExam` 更新为当前考试的开始时间（**即在老师允许的最早时间进行考试**）。

最后，输出最后一门考试的时间 `lastExam`。

## C++ 代码


```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;

int main() {
    
    cin >> n;

    vector < pair < int, int > > exam(n);

    for (int i = 0; i < n; i++) {
        cin >> exam[i].first >> exam[i].second;
    }

    sort(exam.begin(), exam.end());

    int last = exam[0].second;
    for (int i = 1; i < n; i++) {
        if (exam[i].second >= last) {
            last = exam[i].second;
        } else {
            last = exam[i].first;
        }
    }

    cout << last << endl;

    return 0;
}
```
## [AC 记录](https://www.luogu.com.cn/record/118231385)

---

## 作者：PigJokerYellow (赞：0)

##  ~~此题题目翻译有毒~~

# 题意

给定 $ n $ 个考试，每个考试有 $ a $ （原本时间）和 $ b $ （提前时间）两个时间，求最早结束考试的时间。



------------

# 思路

用一个结构体存 $ a $ 数组和 $ b $ ，先排序，再用一个 $ ans $ 记录，如果 $ ans $ 已经超过了提前时间，就只能在原本时间考试。



------------
# $ Code $


```cpp
#include <bits/stdc++.h>
using namespace std;

long long ans;
const int N=1e6;
long long n;
struct node{
	long long a,b;
};
//a，b分别为原来时间和提前时间 
node g[N];
bool cmp(node x,node y){
	if(x.a!=y.a) return x.a<y.a;
	return x.b<y.b;
}
//排序，不解释 

int main(){
	cin>>n;
	for(long long i=1;i<=n;i++){
		cin>>g[i].a>>g[i].b;
	}
	sort(g+1,g+n+1,cmp);
	//按照a从小到大排序 
	for(long long i=1;i<=n;i++){
		if(g[i].b>=ans) ans=g[i].b;
		//如果能提前，就提前考试 
		else ans=g[i].a;
		//否则只能按原来时间考试 
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：So_noSlack (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF479C)&[CF 链接](http://codeforces.com/problemset/problem/479/C)

## 题目简述

一个人想要安排期末考试的时间。

有 $n$ 场考试，每场考试有两个时间 $x_i,y_i$，一个是老师规定的时间，另外一个是他与老师商量好的考试时间。

如果错过了，那就只能按照原来的考试时间考试。

规定：只**能按照原定考试的日期顺序进行考试的情况下，输出考完试的日期。**

## 思路

简单思维题，因为**只能按照原定顺序进行考试**，所以用结构体储存两个时间点，接着**按照 $x_i$ 的非递减顺序排序**，依次遍历，**如果当前 $ans$ 小于 $y_i$ 更新 $ans$ 的值即可，否则 $ans$ 赋值为当前 $x_i$ 的值。**

下面就是代码实现：

```cpp
#include<iostream>
#include<algorithm> 
using namespace std;

struct node {
	int x, y; // 记录两个时间点
} p[5005]; // 注意数据范围
int n; 

// 排序函数，上面解释过
bool cmp(node a, node b) {
	if(a.x == b.x) return a.y < b.y;
	return a.x < b.x; 
}

int main(){
	cin >> n;
	for(int i = 1; i <= n; i ++) cin >> p[i].x >> p[i].y; // 输入
	sort(p + 1, p + n + 1, cmp); // 按照 x 的非递减顺序排序
	int ans = p[1].y; // 初始化 ans
	for(int i = 1; i <= n; i ++)
		if(ans <= p[i].y) ans = p[i].y; // 上述情况 1
		else ans = p[i].x; // 上述情况 2
	cout << ans << endl; // 输出
	return 0;
}

```

[提交记录](https://www.luogu.com.cn/record/118616898)

$$\text{The End!}$$

---

## 作者：WaterSky (赞：0)

## 题目大意：
有 $n$ 场考试，每一场都有两个时间段，一个是本来考试的时间，另一个是老师约定好的时间，要按照原来考试的时间的顺序，如果不能按照老师约定好的顺序，就只能按照原来的顺序。输出最后一场考试的时间。

这一道题，考的内容是**结构体排序**，按照原来的顺序进行排序。然后再用一个变量记录每一场考试的时间，从第一个开始找，如果这一场考试的时间的约定时间比上一场考试的时间晚，那么这场考试可以在约定的时间进行，如果比上一场考试早，就只能用原来的时间。

```
#include<bits/stdc++.h>
using namespace std;
long long n,ans;
struct wbx{
	long long x,y;
}a[10005];
bool cmp(wbx x,wbx y)//按照原来的时间进行排序。
{
	if(x.x!=y.x) return x.x<y.x;
	else return x.y<y.y;
}
int main(){ 
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i].x,&a[i].y);
    sort(a+1,a+1+n,cmp);
    ans=a[1].y;
    for(int i=1;i<=n;i++)
    {
    	if(a[i].y>=ans) ans=a[i].y;//如果这一场考试的时间的约定时间比上一场考试的时间晚，那么这场考试可以在约定的时间进行，如果比上一场考试早，就只能用原来的时间。
    	else ans=a[i].x;
    }
    printf("%lld",ans);
	return 0;
}
```

---

