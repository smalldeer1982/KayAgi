# [ABC036C] 座圧

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc036/tasks/abc036_c



# 题解

## 作者：cff_0102 (赞：4)

这道题考离散化，可以说是离散化模板。

### 离散化是什么？

百度之后可以知道，离散化，把无限空间中有限的个体映射到有限的空间中去，以此提高算法的时空效率。通俗的说，离散化是在不改变数据相对大小的条件下，对数据进行相应的缩小。例如:

原数据：`1,999,100000,15`，处理后：`1,3,4,2`。

### 怎么做？

用两个数组存下输入的数组 $a$ 和 $a$ 每一个元素排序前的排名，最后输出排序后排名。但是要首先去重。

题目没有样例，所以输出格式不清楚，这里给出一组样例：

输入：
```
5
1
1000
15
999
1
```
输出：

```
0
3
1
2
0
```
这些输入输出格式就清楚了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int b[100005];
vector<int>a;
int out[100005];//输出排序后的排名 
int main(){
	ios::sync_with_stdio(false);
	int n;cin>>n;
    a.push_back(-1);//方便后面去重
	for(int i=1;i<=n;i++)cin>>b[i],a.push_back(b[i]);
	//输入完毕
	sort(a.begin()+1,a.end());//排序
    a.erase(unique(a.begin(),a.end()),a.end());//去重
	for(int i=1;i<=n;i++){
        //cout<<i<<" "<<a[i]<<endl;debug代码
        //查找a[i]排序前(b[i])在a的位置 
        int t=lower_bound(a.begin()+1,a.end(),b[i])-a.begin()-1;//lower_bound可以找到第一个≥n的数的地址
        cout<<t<<endl;//要换行，不是空格
    }
	return 0;
}
```


---

## 作者：a1ioua (赞：1)

题目挑明了离散化，所以我们按离散化的算法来编写程序。

所谓“离散化”，就是将很大的数据（指数据的最大值很大，最小值很小，数据间的差距大）缩小成较小范围内的一系列数据。

离散化步骤：

1. 将原始数据排序；
1. 去重（手写或 STL 中的 `unique`）；
1. 转化成从 $0$ 或 $1$ 或其他较小数开始的数据；
1. 根据题目要求应用离散化。

如果要查找某数离散化后变成了什么，那就可以使用 `std::lower_bound` 或手写二分来查找。

因为这道题是道裸的离散化，所以第 4 条就是查找。

------------
```cpp
// by a1ioua
#include <bits/stdc++.h>
// 以下为 int 快读快输。
namespace _{int read(){char _;int __=1;int ___=0;_=getchar();while(_>'9'||_<'0'){if(_=='-')__=-1;_=getchar();}while(_>='0'&&_<='9'){___=10*___+_-'0';_=getchar();}return __*___;}void write(int _){if(_<0){putchar('-');_=-_;}if(_>9)write(_/10);putchar(_%10+'0');}}
using namespace std;
using namespace _;
int n, a[100005], b[100005], c[100005], cnt = 0;
void lsh(int n) {
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
        if (i == 1 || a[i] != a[i - 1])
        b[++cnt] = a[i];
}
int f(int x) {
    return lower_bound(b + 1, b + cnt + 1, x) - b - 1; // 因为题目中离散化从 0 开始，所以一定要减 1！
}
signed solve() {
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read(), c[i] = a[i];
    lsh(n);
    for (int i = 1; i <= n; i++) {
        write(f(c[i]));
        putchar('\n');
    }
    return 0;
}
signed main() {
   return solve();
}
```

---

## 作者：MuelsyseU (赞：0)

## 1. 离散化

离散化是指将无限空间中有限的个体映射到有限的空间中去。在算法上主要是指将无限或较大值域上的数值按照相对顺序不变的方式编号，也就是把每个数与其排名建立双射。

离散化最简单的应用是下标计数。很多数据结构问题需要在值域上离线处理或在值域上建立数据结构，这时一般使用离散化。另外，查找指定值对应的离散化后值可以在 $O(\log n)$ 的时间内简单地通过二分查找实现，而查找一个离散化后值的原值是 $O(1)$ 的。

## 2. 实现

显然是需要通过排序。

这里需要进行分类，即在排序后，相同的元素一般映射到相同的单一排名而非每个都有不同的排名。但是在 OI 界确实存在相同元素分别映射的情况。

为了使相同元素映射到相同值，需要在排序后进行去重。最简单的办法是排序和去重均使用 STL 自带的函数。

```cpp
int n, num, a[100005], b[100005];
inline int read() {
    char c = getchar();
    int x = 0, f = 1;
    while (!isdigit(c)) f = (c == '-' ? -1 : f), c = getchar();
    while (isdigit(c)) x = (x << 3) + (x << 1) + c - '0', c = getchar();
    return x * f;
}
signed main() {
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read(), b[++num] = a[i];
    sort(b + 1, b + 1 + num);
    //unique 函数返回去重后新的序列尾指针，可以计算出去重后的不同元素数
    num = unique(b + 1, b + 1 + num) - b - 1;
    for (int i = 1; i <= n; i++)
        printf("%d\n", lower_bound(b + 1, b + 1 + num, a[i]) - b - 1);
    return 0;
}
```

---

## 作者：heaksicn (赞：0)

## 1 题意
给你一个长度为 $n$ 的数组 $a$，要求对其进行离散化处理。输出离散化后的数组 $b$。
## 2 思路
离散化模板题。

现将数组按从小到大排序。

设现在离散化后的数为 $now$。从小到大遍历一遍，如果和前面的数一样就直接赋 $now$，否则将 $now$ 加一后再赋值。

最后按原来的序号排序输出即可。

时间复杂度 $O(n\log n)$。
## 3 code
```
#include<bits/stdc++.h>
using namespace std;
struct node{
	int id,x;
}a[100001];
bool cmp(node a,node b){//按数字排序
	return a.x<b.x;
}
bool cmp2(node a,node b){//按序号排序
	return a.id<b.id;
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x;
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);//按大小排序
	int now=0,lst=a[1].x;
	a[1].x=0;
	for(int i=2;i<=n;i++){
		int nm=a[i].x;
		if(a[i].x==lst) a[i].x=now;//和前一个一样
		else a[i].x=++now;//不一样
		lst=nm;
	}
	sort(a+1,a+n+1,cmp2);//按序号排序
	for(int i=1;i<=n;i++){
		cout<<a[i].x<<endl;
	}
	return 0;
}
```


---

## 作者：Unnamed114514 (赞：0)

题目很清楚，就是一个离散化的模板题。
## 简介
离散化，是对于数组实现的一个基本操作，适用于一些离线题目。

离散化一般对于较大的数实现，离散化后数组会被压缩到 $O(n)$（元素个数）。如果对于桶一类的数据结构，存储值域过大，就可以先离散化。
## 实现
首先，离散化的第一步是去重。

我们知道 `unique` 可以在**有序数组**中实现去重，并返回最后一个元素的指针（可以转化为元素个数），然后在这个序列中 `lower_bound` 即可。

这里再提供一种方法：STL。

首先，对于去重并排序，我们可以用 `set` 实现，然后我们需要把离散化后的值记录下来，于是采用 `unordered_map`，并使用一个计数变量 `tot` 来计算离散化后的值，最后输出即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
set<int> s;
unordered_map<int,int> mp;
const int maxn=1e5+5;
int n,tot,a[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		s.insert(a[i]);
	}
	for(set<int>::iterator it=s.begin();it!=s.end();++it)
		mp[*it]=tot++;
	for(int i=1;i<=n;++i)
		printf("%d\n",mp[a[i]]);
	return 0;
} 
```

---

## 作者：CmsMartin (赞：0)

## 题目描述

[题目传送门](https://atcoder.jp/contests/abc036/tasks/abc036_c)

## 思路

对数组按大小进行排序，排序完后扫一遍给每一个数标上序号，再按输入顺序排序，输出即可。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int N;

struct Node {
    int Value;
    int Hash;
    int Id;
}Num[100010];

int main() {
    ios::sync_with_stdio(false);
    cin >> N;
    for(int i = 1; i <= N; i++) { cin >> Num[i].Value; Num[i].Id = i; }
    sort(Num + 1 , Num + 1 + N , [](Node a , Node b) { return a.Value < b.Value; } );
    for(int i = 1 , hash = 0; i <= N; i++) {
        if(i == 1) Num[i].Hash = 0;
        else if(Num[i].Value != Num[i - 1].Value) Num[i].Hash = ++hash;
        else Num[i].Hash = hash;
    }
    sort(Num + 1 , Num + 1 + N , [](Node a , Node b) { return a.Id < b.Id; } );
    for(int i = 1; i <= N; i++) cout << Num[i].Hash << endl;
    return 0;
}

```

---

## 作者：happybob (赞：0)

## 题意

给定序列 $a$，对其离散化，输出离散化后的结果。

## 解法

先用 `vector` 储存并排序去重，然后 `lower_bound` 即可，注意从 $0$ 开始，要换行。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int a[N], n;
vector<int> b;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		b.push_back(a[i]);
	}
	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());
	for (int i = 1; i <= n; i++)
	{
		a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
		printf("%d\n", a[i]);
	}
	return 0;
}
```


---

