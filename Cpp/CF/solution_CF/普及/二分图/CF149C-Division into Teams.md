# Division into Teams

## 题目描述

Petya loves football very much, especially when his parents aren't home. Each morning he comes to the yard, gathers his friends and they play all day. From time to time they have a break to have some food or do some chores (for example, water the flowers).

The key in football is to divide into teams fairly before the game begins. There are $ n $ boys playing football in the yard (including Petya), each boy's football playing skill is expressed with a non-negative characteristic $ a_{i} $ (the larger it is, the better the boy plays).

Let's denote the number of players in the first team as $ x $ , the number of players in the second team as $ y $ , the individual numbers of boys who play for the first team as $ p_{i} $ and the individual numbers of boys who play for the second team as $ q_{i} $ . Division $ n $ boys into two teams is considered fair if three conditions are fulfilled:

- Each boy plays for exactly one team ( $ x+y=n $ ).
- The sizes of teams differ in no more than one ( $ |x-y|<=1 $ ).
- The total football playing skills for two teams differ in no more than by the value of skill the best player in the yard has. More formally: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF149C/3138f273213b60ee92a7f26382963c42eacb0d68.png)

Your task is to help guys divide into two teams fairly. It is guaranteed that a fair division into two teams always exists.

## 说明/提示

Let's consider the first sample test. There we send the first and the second boy to the first team and the third boy to the second team. Let's check all three conditions of a fair division. The first limitation is fulfilled (all boys play), the second limitation on the sizes of groups ( $ |2-1|=1<=1 $ ) is fulfilled, the third limitation on the difference in skills ( $ (2+1)-(1)=2<=2 $ ) is fulfilled.

## 样例 #1

### 输入

```
3
1 2 1
```

### 输出

```
2
1 2 
1
3 
```

## 样例 #2

### 输入

```
5
2 3 3 1 1
```

### 输出

```
3
4 1 3 
2
5 2 
```

# 题解

## 作者：BYWYR (赞：2)

## $\texttt{Solution}$

先根据男孩们的能力大小从大到小进行排序，然后交替放入两个团队里面。

可以保证这样放入可以满足 第一队数的和 与 第二队数的和 的差值 小于等于 这 $n$ 个数中最大的那一个。

证明：

另这 $n$ 个数为：$a_1,a_2,a_3...a_n$，

且满足：$x_1 \geq x_2 \geq x_3 \geq ... \geq x_n$。

$\therefore x_1 $ 为最大数。

注意最后输出的是每一位男孩的**编号**。

分类讨论：

当 $n$ 为偶数时：

分成两份：

$$\begin{cases}x_1+x_3+...+x_{n-1}\\x_2+x_4+...+x_{n}\end{cases}$$

$$\because x_1 \geq x_2,x_3 \geq x_4,...,x_{n-1} \geq x_n$$

$$\therefore  x_1+x_3+...+x_{n-1} \geq x_2+x_4+...+x_{n}$$

设

$$ y=(x_1+x_3+...+x_{n-1})-(x_2+x_4+...+x_{n})$$

$$\therefore x_1 \geq (x_n-1+y) \geq x_n+y$$

由题得

$$x_n \geq 1$$

$$\therefore x_1 \geq y$$

当 $n$ 为奇数时：

分成两份：

$$\begin{cases}x_1+x_3+...+x_{n}\\x_2+x_4+...+x_{n-1}\end{cases}$$

先不管 $x_n$，得

$$\because x_1 \geq x_2,x_3 \geq x_4,...,x_{n-2} \geq x_{n-1}$$

$$\therefore  x_1+x_3+...+x_{n-2} \geq x_2+x_4+...+x_{n-1}$$

设

$$ y=(x_1+x_3+...+x_{n-2})-(x_2+x_4+...+x_{n-1})$$

$$\therefore x_1 \geq (x_n-1+y) \geq x_n+y$$

由题得

$$x_n \geq 1$$

$$\therefore x_1 \geq y$$

得证。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct Boy{
	int num,talent;
	bool operator < (const Boy k)const{
		if(talent>k.talent) return true;
		else return false;
	}
}a[100005];
int n,cnt1,cnt2,team1[100005],team2[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].talent;
		a[i].num=i;
	}
	sort(a+1,a+1+n);//结构体排序
	for(int i=1;i<=n;i++){
		if(i%2==1) team1[++cnt1]=a[i].num;
		if(i%2==0) team2[++cnt2]=a[i].num;
	}//交替放入
	cout<<cnt1<<endl;
	for(int i=1;i<=cnt1;i++)
		cout<<team1[i]<<' ';
	cout<<endl;
	cout<<cnt2<<endl;
	for(int i=1;i<=cnt2;i++)
		cout<<team2[i]<<' ';
	return 0;
}
```



------------

应该是本题最完整的证明了，求赞 qwq。

感谢 @[201929w](/user/545095) 对此题证明提供的帮助。

---

## 作者：King_and_Grey (赞：1)

[洛谷CF149C · 题目传送门。](https://www.luogu.com.cn/problem/CF149C)


## 题目描述

给定 $n$ 个数，要求把它们分成两队:

第一队的元素个数为 $x$，第二队的元素个数为 $y$。

要求：

1. $x,y$ 的和是 $n$。

2. $x,y$ 差的绝对值小于等于 $1$。

3. 第一队中数的和与第二队中数的和的差值小于等于这 $n$ 个数中最大的那一个。

## 题目分析
要求 $1$：$x,y$ 的和是 $n$。~~这一点是必然的，给了等于没给~~。

要求 $2$：我们把人交替放入 $1$ 队， $2$ 队，$1$ 队， $2$ 队......这样就可以尽量避免两队人数绝对值之差大于 $1$ 的情况了。

要求 $3$：建立在要求 $2$ 的基础之上，我们可以先排序，然后交替放入 $1$ 队， $2$ 队，$1$ 队， $2$ 队......这样要求 $2$ 和要求 $3$ 就可以同时完成了。


对于要求 $3$ 的证明，不妨奇偶性分开讨论。

对于 $n$ 为奇数的情况，不难发现此时差值为 $a_n - ((a_2 - a_1) + (a_4 - a_3) + \cdots - (a_{n - 1} - a_{n - 2}))$ 的绝对值。考虑后面那个部分，注意到 $a_2 - a_1 + a_4 - a_3 \leq a_4 - a_1$，以此类推，就有 $((a_2 - a_1) + (a_4 - a_3) + \cdots - (a_{n - 1} + a_{n - 2})) \leq a_{n - 1} - a_{1}$，由于 $a_i \geq 1$，这个值显然小于 $a_{n - 1}$，但这个值显然又是大于等于 $0$ 的。

由此我们得到差值的一个范围是 $(a_n - a_{n - 1}, a_{n}]$ 显然在 $[-a_n, a_n]$ 范围之内。
对于 $n$ 为偶数的情况，此时差值就是 $(a_2 - a_1) + (a_4 - a_3) + \cdots - (a_{n} - a_{n - 1})$。


运用类似的证明方法，我们得到这个差值的范围是 $[0, a_n - a_1)$。显然在 $[-a_n, a_n]$ 范围之内。

因此，这个放置方法是满足条件的。证毕。

## 思路

我们可以先排序，然后把人交替放入第一个队伍与第二个队伍。在这里，我们可以使用[ pair ](https://www.luogu.com.cn/article/hi5av4p4)来存储队员的 $id$ 号码以及大小。

**注意**：`pair` 要导入 `utility` 头文件。~~（使用万能头文件的请屏蔽此句话）~~

## 最后奉上 AC 代码



```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define AC return 0
const int N = 1e5;

int n;
pair<int,int> a[N + 5];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i++){
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(a + 1,a + n + 1);
	cout << (int) n / 2 + n % 2 << endl;
	for(int i = 1;i <= n;i++){
		if(i % 2 != 0){
			cout << a[i].second << " ";
		}
	}
	cout << endl;
	cout << (int) n / 2 << endl;
	for(int i = 1;i <= n;i++){
		if(i % 2 == 0){
			cout << a[i].second << " ";
		}
	}
	cout << endl;
	AC;
}
```

---

## 作者：czh___ (赞：0)

题意：给你 $n$ 个人以及每人的 $val$ 值，要求选出两支队伍 $x$ 和 $y$，记 $sumx$ 为 $x$ 队伍所有人 $val$ 值之和，$sumy$ 同理。要求两支队伍人数之差不能超过 $1$ 且$\lvert sumx-sumy \rvert \le $ 所有人中最大的 $val$ 值。问你选人方案。

思路：把 $n$ 个人当做坐标轴的点，取点搞。显然轮流取是满足的，前面相邻奇偶数差之和不会超过最后那个数。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define MAXN 100010
#define Ri(a) scanf("%d", &a)
#define Pi(a) printf("%d\n", (a))
using namespace std;
int belong[MAXN];
struct Node{
    int val, id;
};
Node num[MAXN];
bool cmp(Node a, Node b){
    return a.val < b.val;
}
int main()
{
    int n; Ri(n);
    for(int i = 1; i <= n; i++)
    {
        Ri(num[i].val);
        num[i].id = i;
    }
    stable_sort(num+1, num+n+1, cmp);
    Pi(n & 1 ? n / 2 + 1 : n / 2); int cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        if(i & 1)
        {
            if(cnt) printf(" ");
            printf("%d", num[i].id);
            cnt++;
        }
    }
    printf("\n");
    Pi(n / 2); cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        if(i % 2 == 0)
        {
            if(cnt) printf(" ");
            printf("%d", num[i].id);
            cnt++;
        }
    }
    printf("\n");
    return 0;
}
```

[改编于](https://blog.csdn.net/chenzhenyu123456/article/details/50491954?ops_request_misc=%257B%2522request%255Fid%2522%253A%25224F4871E4-9684-4B97-8114-27FFC8C19865%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=4F4871E4-9684-4B97-8114-27FFC8C19865&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-50491954-null-null.142^v100^pc_search_result_base5&utm_term=Division%20into%20Teams&spm=1018.2226.3001.4187)

---

## 作者：hard_learn (赞：0)

# 简要题意
题目要求将一组具有不同技能水平的人员分成两支球队，要求两支球队的人数差距不超过 $1$，并且两支球队的技能总和之差不超过技能最高的人的技能值。

# 思路
- 按照选手的技能值从大到小排序，这样可以确保我们在分组时，尽量使得每组的技能总和差距最小。
- 通过遍历排序后的选手列表，将选手按顺序交替分配到两组中。这样可以保证两组的技能总和尽可能接近。
- 输出每组的选手数量及其对应的选手编号。

# 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
struct st{
	int c,id;
}a[100005]; 
bool cmp(st a,st b){
	return a.c>b.c;
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].c;
        a[i].id=i;
    }
    sort(a+1,a+n+1,cmp);
    int ans,cnt=0;
    if(n%2==0){
    	cout<<n/2<<endl;
    	ans=n/2;
	}
	else{
		cout<<n/2+1<<endl;
		ans=n/2+1;
	}
    for(int i=1;i<=n;i+=2){
    	cout<<a[i].id<<" ";
    }
    cout<<endl;
    cout<<n-ans<<endl;
    for(int i=2;i<=n;i+=2){
    	cout<<a[i].id<<" ";
	}
    return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

先将 $a$ 从大到小排序，这样不影响结果。

然后奇偶交替选，设编号与 $n$ 奇偶性不同且值最小的对应的编号为 $k$。

因为这样最后的和为 $(a_n - a_{n - 1}) + (a_{n-2} - a_{n-3}) + (a_{n-4}-a_{n-5}) + \cdots$，然后由于 $a_{n - 2} \le a_{n-1}$，所以 $(a_n-a_{n-1})+(a_{n-2}-a_{n-3}) \le a_n - a_{n-3}$，以此类推的到 $(a_n - a_{n - 1}) + (a_{n-2} - a_{n-3}) + (a_{n-4}-a_{n-5}) + \cdots \le a_n - a_{k}$。

又由于 $a_i \ge 1$，所以 $a_n - a_{k} \le a_n$，所以 $(a_n - a_{n - 1}) + (a_{n-2} - a_{n-3}) + (a_{n-4}-a_{n-5}) + \cdots \le a_n - a_{k} \le a_n$。

所以这样是正确的。

```cpp
#include<bits/stdc++.h>

using namespace std;

int n;
pair<int, int> a[100010];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i].first), a[i].second = i;

	sort(a + 1, a + 1 + n);

	vector<int> id1, id2;

	for (int i = 1; i <= n; ++i) {
		if (i & 1) id1.push_back(a[i].second);
		else id2.push_back(a[i].second);
	}

	printf("%d\n", id1.size());
	for (auto v : id1) printf("%d ", v);
	printf("\n%d\n", id2.size());
	for (auto v : id2) printf("%d ", v);

	return 0;
}
```

---

## 作者：smydahaoren (赞：0)

### 题目思路

根据题目，要求把 $n$ 个数分为 $x$，$y$ 两组数。当总数为偶数时，两组数元素个数相等，当总数为奇数时，两者个数差为 $1$。

把这 $n$ 个数从小到大排序一下。根据其排完序后的编号奇偶性分别进入 $x$ 和 $y$ 两个组，这样的分配方法可以均匀的在两个数组中分配大数和小数，以满足题目的要求。

为了按照原始的输入编号来输出其编号，需要用 `pair` 容器来同时储存其 `id` 值和数值。


------------

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10000009;
int n,x[N],y[N];
pair<long long,long long> a[N]; 
void print(){
    cout<<ceil(n/2.0)<<endl;
    for(int i=0;i<ceil(n/2.0);i++)
        cout<<x[i]<<" ";
    cout<<endl;
    cout<<n/2<<endl;
    for(int i=0;i<n/2;i++)
        cout<<y[i]<<" ";
	
}
int main(){
	//freopen(" ","r",stdin);
	//freopen(" ","w",stdout);
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i].first;
	for(int i=0;i<n;i++)
		a[i].second=i;
	sort(a,a+n);
	for(int i=0;i<n;i++){
		if(i%2==0)
		x[i/2]=a[i].second+1;
		else
		y[i/2]=a[i].second+1;
	} 
	print();
	return 0;
}

```


---

## 作者：yutong_Seafloor (赞：0)

# [题目在这里 ·CF149C Division into Teams  ](https://www.luogu.com.cn/problem/CF149C) 

### 题目简要：
感觉题意有点描述不清……？

给你 $n$ 个元素，现在要求分成两队，记一队长度为 $x$，二队长度为 $y$，这两队有以下要求。

1. $x+y=n$。
2. $ |x-y| \le 1$。
3. 一队的和 $a$ 和二队的和 $b$ 的差小于这些元素中最大的那个，我们设最大的数是 $maxn$，也就是 $|a-b|\le maxn$。

现在要求依次输出 $x$、一队的元素在原队列的**编号**、$y$、二队的元素在原队列的**编号**。

------------
### 题意分析

看到楼上几个大佬写的我有点懵懵，整个蒟蒻也能看懂的版本。

首先由题我们能看出来最简单的方法是 $x$ 是 $n \div 2$ 或者 $n \div2 +1$，这个多出来的 $1$ 取决于 $n$：$n$ 是偶数，$x$ 就是 $n \div 2$；反之，$n$ 是奇数，$x$ 就是 $n \div 2+1$，然后 $y$ 是 $n \div 2$。

然后就是有关元素如何组合，简单来讲，我们能想到最快捷的肯定是分队，应该先从小到大排序，第一个去一队，第二个去二队，第三个去三队，第四个去四队，以此类推，这样也许不一定会使两队差最小，但一定是满足题目情况的，大数都被中和掉了，那么 $|a-b| \le maxn$ 一定成立。


------------
## 代码 
```cpp 
#include <bits/stdc++.h>
using namespace std;
struct node
{
	int a,bh;
}de[100010];
int n,i,x,y;
bool check(node qw,node we)
{
	return qw.a<we.a;
}
int main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>de[i].a;
		de[i].bh=i;//记下编号
	}
	y=n/2,x=n-y;//这里简单写，y一直是n/2，所以x就是n-y，满足条件1
	sort(de+1,de+n+1,check);//排序
	cout<<x<<"\n";
	for(i=1;i<=n;i+=2)//一次+2，把中间第二大的数跳过
	cout<<de[i].bh<<" ";
	cout<<"\n";
	cout<<y<<"\n";
	for(i=2;i<=n;i+=2)
	cout<<de[i].bh<<" ";
	return 0;
}//by·yutong_Seafloor
```

---

## 作者：fp0cy1tz6mn4rd_ (赞：0)

# CF149C 题解

## 题意简述

给定 $n$ 个数，要求把它们分成两队:

第一队的元素个数为 $x$，且第二队的元素个数为 $y$。

### 要求

1.$x+y=n$

2.$\left|x-y\right|\leqslant1$ 

3.$\left|\overset{x}{\underset{i=1}{\sum}}a_{p_i}-\overset{y}{\underset{i=1}{\sum}}a_{q_i}\right|\leqslant\overset{n}{\underset{i=1}{\max}}a_i$

## 思路

需要满足第一条第二条很简单，可以把数组分成相对平均的两段。

第三条表示的意思是第一组数的和和第二组数的和的差值小于等于这 $n$ 个数的和。

只需要将这 $n$ 个数排序，分成 $\lfloor \frac{n}{2} \rfloor$ 组，其中每一组序列包含两个元素，第一个元素放入第一个序列中，第二个元素放入第二个序列中即可。。

第一条和第二条规则肯定能满足，因为是把 $n$ 个数插空排队啊。

我们也不难发现，第三条也能满足。

~~啊，真是一道大水题！~~

## 代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
constexpr int N=100005;	//定义常量  
struct node{
	int num,ability;
} a[N];
int n,b,c,k[N],t[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		a[i].num=i;
		cin>>a[i].ability;
	}
	sort(a+1,a+n+1,[](node x,node y)->bool{return x.ability<y.ability;});	//lambda 表达式  
	for(int i=1;i<=n;i++){
		if(i&1) k[++b]=a[i].num;
		else t[++c]=a[i].num;
	}
	cout<<b<<endl;
	for(int i=1;i<=b;i++)
		cout<<k[i]<<" ";
	cout<<endl;
	cout<<c<<endl;
	for(int i=1;i<=c;i++)
		cout<<t[i]<<" ";
	return 0;
}
```



---

## 作者：ttq012 (赞：0)

模拟题。

首先将序列按照元素单调递增的顺序来排序。

对于排好序的序列，我们要将其分成两个序列，需要满足两个序列的长度的差的绝对值要小于等于 $1$，那么我们就将当前序列均分成两个序列，如果到最后剩下一个元素那么就放到第一个序列里。

然后要满足两个序列的差值小于等于 $n$ 个数中最大值，那么我们可以将序列分成 $\lfloor \frac{n}{2} \rfloor$ 组，其中每一组序列包含两个元素，第一个元素放入第一个序列中，第二个元素放入第二个序列中即可。如果到最后剩下一个元素不在任意的一组内部，那么我们将其放入第一个序列即可。

这样做满足条件的证明：如果不考虑最后有可能剩下的那一个元素，那么第一个序列一定小于等于第二个序列。最后剩下的那一个元素一定是最大的那一个元素，将这一个元素放入第一个序列里面一定是最优解，由于题目保证数据一定有解，那么输出最优方案即可。

**Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

struct Node {
    int x, id;
    Node () { x = id = 0; }
    friend bool operator < (const Node & _1, const Node & _2) {
        return _1.x < _2.x;
    }
} a[1000010];

signed main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        scanf ("%d", &a[i].x); a[i].id = i;
    } sort (a + 1, a + n + 1); // 按照关键字 `x`，也就是数字的大小从小到大排序
    cout << n - (n >> 1) << '\n'; // 输出第一个序列长度
    for (int i = 1; i <= n; i ++) {
        if (i & 1) cout << a[i].id << ' '; // 输出第一个序列的元素
    } cout << '\n' << (n >> 1) << '\n'; // 输出第二个序列的长度
    for (int i = 1; i <= n; i ++) {
        if (! (i & 1)) cout << a[i].id << ' '; // 输出第二个序列的元素
    } cout << '\n';
    return 0;
}

```


---

## 作者：Dimly_dust (赞：0)

### 题面

------------

翻译有点乱，看了英文题面才知道题目的意思。

给定 $n(n\leq 1e5)$ 个数，把数列分成两组，两组的元素个数分别为 $x$ 和 $y$  个。

数列必须满足：

- $x+y=n$

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF149C/3138f273213b60ee92a7f26382963c42eacb0d68.png) (简单来说就是两个数列的和的差的绝对值不能超过全部元素的最大值)

**输出格式**

第一行输出 $x$

第二行输出数列在原数列中的编号

第三行输出 $y$

第四行也是输出数列在原数列中的编号

------------

### 思路

首先 $x+y=n$ 必定成立，所以我们看第二个条件。

考虑怎么使数列和的差的绝对值最大且不超过最大值。

突然间发现如果第一个数列取排序后编号为奇数（不是原来的编号），第二个数列取编号为偶数这样的最大。

我们可以这样思考，因为有不能超过元素最大值这个条件，那么最大值所在数列一定满足除最大值的数列里其他的元素的和与另一个数列里的和的差**一定小于等于** $0$ 。

那么怎么使上面所说的最小呢？当然是小的和次小的配对这样两者差的绝对值最小。

于是问题就迎刃而解。（好像思路说的没有特别易懂![/jk](https://cdn.luogu.com.cn/upload/pic/62234.png)）

### Code

```
#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;
pair<int,int> a[N];

int  main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].first;
        a[i].second=i;
    }
    sort(a+1,a+n+1);
    cout<<n/2+(n%2)<<endl;
    for(int i=1;i<=n;i+=2)
        cout<<a[i].second<<" ";
    cout<<endl<<n/2<<endl;
    for(int i=2;i<=n;i+=2)
        cout<<a[i].second<<" ";
    return 0;
}
```


---

