# [ABC128B] Guidebook

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc128/tasks/abc128_b

あなたは美味しいレストランを紹介する本を書くことにしました。 あなたは $ N $ 個のレストラン、レストラン $ 1 $、レストラン $ 2 $、$ … $、レストラン $ N $ を紹介しようとしています。レストラン $ i $ は $ S_i $ 市にあり、あなたは $ 100 $ 点満点中 $ P_i $ 点と評価しています。 異なる $ 2 $ 個のレストランに同じ点数がついていることはありません。

この本では、次のような順でレストランを紹介しようとしています。

- 市名が辞書順で早いものから紹介していく。
- 同じ市に複数レストランがある場合は、点数が高いものから紹介していく。

この本で紹介される順にレストランの番号を出力してください。

## 说明/提示

### 制約

- $ 1\ <\ =\ N\ <\ =\ 100 $
- $ S $ は英小文字のみからなる長さ $ 1 $ 以上 $ 10 $ 以下の文字列
- $ 0\ <\ =\ P_i\ <\ =\ 100 $
- $ P_i $ は整数
- $ P_i\ ≠\ P_j $ $ (1\ <\ =\ i\ <\ j\ <\ =\ N) $

### Sample Explanation 1

$ 3 $ 種類の市名は辞書順で `kazan` $ < $ `khabarovsk` $ < $ `moscow` です。 それぞれの市について、点数が高いレストランから順に紹介されていきます。よって、レストランは $ 3,4,6,1,5,2 $ の順に紹介されていきます。

## 样例 #1

### 输入

```
6
khabarovsk 20
moscow 10
kazan 50
kazan 35
moscow 60
khabarovsk 40```

### 输出

```
3
4
6
1
5
2```

## 样例 #2

### 输入

```
10
yakutsk 10
yakutsk 20
yakutsk 30
yakutsk 40
yakutsk 50
yakutsk 60
yakutsk 70
yakutsk 80
yakutsk 90
yakutsk 100```

### 输出

```
10
9
8
7
6
5
4
3
2
1```

# 题解

## 作者：苏联小渣 (赞：2)

## 题目大意

$n$ 个城市，按照字典序排列编号。如果城市相同按照分数**降序**排列。

## 分析
排序~~水~~题，按照题意排序即可。

**注意点1** 本题排序方法有很多种，这里推荐结构体内部**重载运算符**排序。模板如下：

```cpp
<类型> operator <运算符符号> (<参数表>){
	return <自定义规则>
}
```
这种方法好处在于，可以不用写排序函数，排序的时候规则不易搞错。

**注意点2** 关于字典序，C++ 内 string 类型变量可以按照**字典序**比较大小。如两个 string 类型变量 $s1,s2$，若 $s1$ 字典序大于 $s2$，则返回 $s1 > s2$。所以我们在比较的时候，只用写以下代码即可。

```cpp
bool operator < (const node &A) const{
		if (name == A.name) return sc > A.sc;
		else return name < A.name;
	}
```
然后注意要把每个城市初始编号赋初值，再 sort 一遍就可以了。

### Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	string name;
	int sc, id;
	bool operator < (const node &A) const{//此处最后一个const如果不写在某些oj上可能会报错
		if (name == A.name) return sc > A.sc;
		else return name < A.name;
	}
}a[107];
int n;
int main(){
	scanf ("%d", &n);
	for (int i=1; i<=n; i++){
		cin >> a[i].name >> a[i].sc;
		a[i].id = i;
	}
	sort (a+1, a+n+1);
	for (int i=1; i<=n; i++){
		printf ("%d\n", a[i].id);
	}
	return 0;
}
```

---

## 作者：JoseTony (赞：2)

# 思路与分析
这道题其实用到的基本思路就是结构体、函数还有排序。像这样每一行输入都有多组数据的时候，用 ```struct``` 函数建立一个结构体往往会更快一些。对于这个结构体，我们在里面分别定义一个字符串，代表城市名，再定义每个餐厅分数，最后还有每个餐厅的编号。这道题还让我们从小到大将字符串按字典序排序，所以还要用到 ```sort``` 函数来进行排序。但是，要将一个结构体排序，我们还需要一个排序函数，通常叫做 ```cmp``` 也就是英文的 compare 一词。在这个函数中，我们要先比较城市名，若城市名一样，再比较分数。最后按顺序输出他们的编号。
# 代码
```cpp
#include<iostream>
#include<algorithm>//sort函数所用头文件
using namespace std;
struct node{//结构体
    string city;//城市名
    int score,id;//分数与编号
};
node a[100001];
bool cmp(node a,node b){//排序函数
    if(a.city<b.city){
        return 1;
    }//第一层比较城市名
    if(a.city==b.city){
        if(a.score>b.score){
            return 1;//若城市名相等则比较分数
        }
    }
    return 0;
}
int main(){
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i].city >> a[i].score ;
        a[i].id=i+1;//记录编号
    }
    sort(a,a+n,cmp);//排序
    for(int i=0;i<n;i++){
        cout << a[i].id << endl;//输出编号
    }
    return 0;//程序结束
}
```


---

## 作者：GeChang (赞：1)

# 题解 AT4738 [ABC128B] Guidebook
~~这么氵的题，让我来氵一篇题解qwq~~
### 1.分析
思路显然，直接用结构体把城市，评分与编号存到一个结构体里排序就可以了，新手可以用来练排序。
### 2.代码
先用`struct`把数据存起来：
```cpp
struct node{
	string city;
	ll point,num;
};
```
当然`class`也可以，但是不太常用：
```cpp
class node2{
	public:
		string city;
		ll point,num;
	private:
};
```
然后说核心部分，**排序**。

因为结构体里包含了多个变量，这样计算机就不知道先为哪一个变量排序，也就是不知道优先级，所以`sort`是不能直接对结构体排序的，因此我们要自己写一个排序函数。

排序函数是布尔类型，通常会以`cmp`来命名，传入变量一般是两个结构体类型，内容就要自己写。就比如下面这个结构体：
```cpp
struct aaa{
	string name;
	ll score;
	ll weight;
};
```
如果要以`score`为排序标准，那么排序可以这么写：
```cpp
bool cmp(aaa x,aaa y){
	return x.score<y.score;
	//return x.score>y.score;
}
```
中间的这句表示以`score`为排序标准，从小到大排序；被注释的这句则是从大到小排序。

如果在`score`相等的时候以`weight`为标准，那么可以像这样改一下：
```cpp
bool cmp(aaa x,aaa y){
	if(x.score==y.score) return x.weight<y.weight;
	else return x.score<y.score; 
}
```
这样就不难写出来这道题的`cmp`了。

接下来`sort`一下，再输出，完美 $\color{green}\text{AC}$。

完整代码给一下：
```cpp
#include<bits/stdc艹.h>
#define ll long long
using namespace std;
struct node{
	string city;
	ll point,num;
};
//class node2{
//	public:
//		string city;
//		ll point,num;
//	private:
//};
ll n;
node a[10010];
bool cmp(node x,node y)
{
	//cmp已被和谐
}
int main()
{
	cin>>n;
	for(ll i=1;i<=n;i++)
	{
		cin>>a[i].ciｔy>>a[i].point;
		a[i].num=i; //编号也要存下来
	}
	sort(a+1,a+n+1,cmp); //排序
	for(ll i=1;i<=n;i++) cout<<a[i].num<<endl;
	return 0;
	//两处防抄袭qwq
}
```
# 莫抄袭，没了AC记录，空悲切！


---

## 作者：xgwpp6710 (赞：0)

这道题的思路很简单，就是结构体排序。

把一个餐厅的城市、得分以及编号存在一个结构体里面，进行结构体排序。

注：有一个坑，最后输出的是编号，我因为这个 `WA` 了一次。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	string s;
	int p,n;
}d[1009];
bool ev(string a,string b)
{
	if(a.size()!=b.size()) return 0;
	for(int i=0;i<a.size();i++)
		if(a[i]!=b[i]) return 0;
	return 1;
}//两个字符串是否相等，其实可以直接用 a==b 的，但我一开始不知道所以打了这玩意，就当参考一下原理吧
bool sm(node a,node b)
{
	if(ev(a.s,b.s)) return a.p>b.p;//根据题意 按得分排序
	return a.s<b.s;//其实可以直接用！！！！！
}
int n;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>d[i].s>>d[i].p,d[i].n=i;
	sort(d+1,d+1+n,sm);//基本的结构体排序
	for(int i=1;i<=n;i++) cout<<d[i].n<<endl;
	return 0;
}
```

---

## 作者：RBI_GL (赞：0)

## 题意

[题面](https://www.luogu.com.cn/problem/AT4738)

中文翻译已经的很清楚了。

## 思路

显然要进行排序。

为了方便操作，我们定义一个结构体，储存第 $i$ 个餐厅的名字，分数和编号。

然后自己按照题意写一个 ```cmp``` 控制快排。

排序后输出第 $i$ 个餐厅的编号即可。

时间复杂度为 $\texttt{O(n log n)}$。

## $Code:$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
struct node {
	string s;
	int p;
	int id;
}a[1005];
bool cmp(node x, node y) { // 结构体排序 
	if (x.s == y.s) return x.p > y.p;
	else return x.s < y.s;
}
int main() {
	cin >> n;
	for(int i = 1; i <= n; ++i) { //储存数据 
		cin >> a[i].s;
		scanf("%d", &a[i].p);
		a[i].id = i;
	}
	sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; ++i) printf("%d\n", a[i].id);
	return 0;
}
```

---

## 作者：奥斯卡小冰人 (赞：0)

这道题用结构体比较好做。
先是读入，用 $id$ 来记录一下每个餐厅的顺序，然后用 $sort$ 函数进行排序。结构体排序的话就用自己做一个 $cmp$ 函数，先比较城市，如果城市是一样的再比较分数。排完序后输出就行了。


```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
struct node//结构体
{
    string s;//城市
    int p,id;//分数与顺序
}r[100000];
bool cmp(node a,node b)
{
    if(a.s != b.s) return a.s < b.s;//如果城市不一样，就比城市
    return a.p > b.p;//城市是一样的就比分数
}
int main()
{
    cin >> n;
    for(int i = 0;i < n;i++) cin >> r[i].s >> r[i].p,r[i].id = i + 1;//顺序等于下标+1
    sort(r,r + n,cmp);//排序
    for(int i = 0;i < n;i++) cout << r[i].id << endl;//输出
    return 0;
}

    
```


---

## 作者：Iron_Heart (赞：0)

## 思路

结构体排序。

先将每间餐厅的城市名、分数和编号存到结构体。

然后排序，首先根据第一关键字城市名字典序排序。如果城市名相同，则按照分数从大到小排序。

最后输出排序后所有餐厅的编号。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

struct r
{
    string city;
    int pts, idx;
} rs[105];
int n;

bool cmp(r a, r b)
{
    if (a.city != b.city) return a.city < b.city;
    return a.pts > b.pts;
}

int main()
{
    ios::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> rs[i].city >> rs[i].pts, rs[i].idx = i + 1;
    sort(rs, rs + n, cmp);
    for (int i = 0; i < n; ++i) cout << rs[i].idx << endl;
    return 0;
}
```


---

## 作者：SpeedStar (赞：0)

#### 算法分析

题意是对于城市名的字典序小的先输出编号，而对于同一城市的餐厅按照他们的评分从高到低输出编号。于是，我们可以利用C++的 $tuple$ 把城市，评分和 $id$ 绑定并把它存入 $vector$，其中评分需要取其相反数，然后用 $sort$ 函数对 $vector$ 进行排序即可（这里 $sort$ 的排序是按照关键字的先后顺序进行排序的）。

#### C++ 代码

```cpp
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::string;
using std::tuple;
using std::vector;

int main() {
	int n;
	cin >> n;
	
	vector<tuple<string, int, int>> a;
	string s;
	int p;
	for (int i = 1; i <= n; ++i) {
		cin >> s >> p;
		p = -p;
		a.push_back(tie(s, p, i));
	}
	
	sort(a.begin(), a.end());
	
	for (int i = 0; i < n; ++i) {
		cout << std::get<2>(a[i]) << '\n';
	}
	
	return 0;
}
```


---

## 作者：AlwaysForward (赞：0)

# 一个简单的排序即可，并不需要楼下的结构体

使用最简单的排序方法：

冒泡排序

先从大到小比较字符串，会按字典序比较，若比较的字符串相同，直接比较他们的分数

然后按现在的顺序输出开始的位置

~~为了防止更多人不成为作弊者~~(典型的病句)

为了防止更多人成为作弊者，代码已做反作弊处理~~一共三处~~

```
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    int a[n+1];
    string s[n+1];
    int p[n+1];
    int i,j;
    for(i=1;i<=n;i++){
        cin>>a[i]>>s[i];
        p[i]=i;
    }
    for(i=1;i<=n;i++){
        for(j=i+1;j<=n;j++){
            if(s[i]>s[j]){
                swap(s[i],s[j]);
                swap(a[i],a[j]);
                swap(p[i],p[j]);
            }
            if(s[i]==s[j]&&a[i]<a[j]){
                swap(s[i],s[j]);
                swap(a[i],a[j]);
                swap(p[i],p[j]);
            }
        }
    }
    for(i=1;i<=n;i++){
        cout<<s[i]<<endl;
    }
    return 0;
}
```
管理员大大辛苦了！希望通过~


---

## 作者：Zirnc (赞：0)

[ChungZH's blog](https://chungzh.cn) · [ChungZH's portfolio](https://chungzh.cc)


## 题目

您已决定写一本介绍美食餐厅的书，您要介绍 $N$ 家餐厅：餐厅 $1$，餐厅 $2$，$...$，餐厅 $N$。餐厅 $i$ 在城市 $S_i$ 中，您对餐厅 $i$ 的评估得分为 $P_i$（ $100$ 分制）。没有两家餐厅的分数相同。

您要按以下顺序介绍餐厅：

- 这些餐厅按其城市名称的字典顺序排列。
- 如果在同一城市中有多个餐厅，则它们按照得分的降序排列。

按照书中介绍的顺序打印餐厅的识别号。

## 题解

这道题很简单，用**结构体+自定义排序函数**的套路就好了。

排序函数：
1. 如果是不同城市，就比较城市名的大小（按字典序）。
2. 如果是相同城市，就比较分数。

结构体里还要记得计一个识别号（$i$）。

**代码里省略了很多内容，抄不了的啦~**

```cpp
···
struct restaurant {
  string cityn;
  int score;
  int index; // 识别号
} a[103]; 
bool cmp(restaurant x, restaurant y) {
  if (x.cityn != y.cityn) {
    return x.cityn < y.cityn;
  }
  return x.score > y.score;
}
int main() {
  ···
  for (int i = 1; i <= N; i++) {
    cin >> a[i].cityn >> a[i].score;
    a[i].index = i;
  }

  sort(a + 1, a + 1 + N, cmp);

  ···
}
```

---

