# [ABC275C] Counting Squares

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc275/tasks/abc275_c

二次元平面があります。$ 1 $ 以上 $ 9 $ 以下の整数 $ r,c $ について、$ S_{r} $ の $ c $ 番目の文字が `#` であるとき座標 $ (r,c) $ にポーンが置いてあり、$ S_{r} $ の $ c $ 番目の文字が `.` であるとき座標 $ (r,c) $ に何も置かれていません。

この平面上の正方形であって、$ 4 $ 頂点全てにポーンが置いてあるものの個数を求めてください。

## 说明/提示

### 制約

- $ S_1,\ldots,S_9 $ はそれぞれ `#` と `.` からなる長さ $ 9 $ の文字列

### Sample Explanation 1

座標 $ (1,1),(1,2),(2,2),(2,1) $ を頂点とする正方形は、$ 4 $ 頂点全てにポーンが置かれています。 座標 $ (4,8),(5,6),(7,7),(6,9) $ を頂点とする正方形も、$ 4 $ 頂点全てにポーンが置かれています。 よって答えは $ 2 $ です。

## 样例 #1

### 输入

```
##.......
##.......
.........
.......#.
.....#...
........#
......#..
.........
.........```

### 输出

```
2```

## 样例 #2

### 输入

```
.#.......
#.#......
.#.......
.........
....#.#.#
.........
....#.#.#
........#
.........```

### 输出

```
3```

# 题解

## 作者：_qingshu_ (赞：4)

# 题意：

给定一个 $9\times 9$ 的矩阵，询问可以以 `#` 为四个顶点构成一个正方形的数量。

# 思路：

首先开一个 set 来记录一下图中 `#` 的位置，方便我们后边枚举。

图非常的小，考虑直接在 set 中暴力枚举相对顶点 $i,j$，设另外两个点为 $p,q$。我们就可以利用 $q_x=i_x+(i_y-j_y),q_y=i_y-(i_x-j_x)$ 与 $p_x=j_x+(i_y-j_y),p_y=j_y-(i_x-j_x)$ 来求出 $p,q$ 的坐标。

再在 set 中查找一下存不存在 $p,q$ 就可以确认这个正方形存不存在了。

另外，因为在区分 $i,j$ 的情况下一共会有 $4$ 中情况会构成同一个正方形，所以输出答案需要除以 $4$。

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[5200][5200];
int ans;
set<pair<int,int> >ton;
int main(){
	for(int i=1;i<=9;i++){
		for(int j=1;j<=9;j++){
			cin>>a[i][j];
			if(a[i][j]=='#'){
				ton.insert({i,j});
			}
		} 
	}
	for(pair<int,int> i : ton){
		for(pair<int,int> j : ton){
			if(i!=j){
				int x=(i.second-j.second),y=(i.first-j.first);
				if( ton.find({i.first+x,i.second-y})!=ton.end()&&
				    ton.find({j.first+x,j.second-y})!=ton.end()){
				   	ans++;
				}
			}
		}
	}
	cout<<ans/4;
} 
```

---

## 作者：MAX007_CRN (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc275_c)

题意让我们在一个（$9\times 9$）的矩阵里找以四个 ``` # ```  为四个顶点组成正方形的个数。
## 思路
可以看到，本题**数据范围**非常小，最坏情况下，也仅有约 $2\times10^6$ ，完全可以用**暴力枚举**。我们可以用 vector 或 set 存一下 ``` # ``` 的位置，然后依次枚举选四个点能不能构成正方形。

重点来了，如何判断四个点能否构成正方形呢？众所周知，构成正方形需要对边相等，且四个角都是直角。

重点就在于判断边。学过初中的都知道，根据勾股定理，三角形的两条**直角边**的平方和 = **斜边**平方。所以我们可以把正方形分成两个一样的三角形，然后按上面去判断。

## [AC Code](https://www.luogu.com.cn/paste/p71z1u2n)

最后，劝大家一句，不要抄袭，AC 记录都没了可不要来找我。

---

## 作者：kczw (赞：2)

# 题意
给定一个 $9\times9$ 大小的图，上面标有一些点，问你这些点总共可以构成多少个正方形。
# 思路
首先，**极限**下有 $81$ 个点，每次从中选出 $4$ 个点判断，我们暴力地匹配地话，时间复杂度最多也就 $O(C_{81}^4)$，而 $C_{81}^4$ 约为 $2\times10^6$，然后还有两秒的时间，所以这道题是不难的，毕竟暴力都能够。

这里推荐一种 set 的写法。

我们将所有点存在 set 里，然后去枚举，枚举时每次固定一条边 $AB$ 和两个点 $A,B$ ，**读过初中的**都知道，知道一个边的两个点就能确定两个可能的正方形。然后在 set 里查找构成正方形的点是否存在，若存在，则计入答案。

最后因为对于一个正方形的每条边都会计入一次，然后加上点的枚举的先后，所以最后答案会变成正确答案的 $8$ 倍，所以最后需要除以 $8$。（当然，可以用其他方式在计数过程中去除多余的部分，此处是为了方便，反正效率够。）

如果你没读过初中请看下面。
![](https://cdn.luogu.com.cn/upload/image_hosting/usjtehaw.png)

首先这个模型中有一个**等腰直角三角形**，易得如果我们将这张图中的 $\triangle ACE$ 以 $AF$ 中点旋转 $180$ 度到 $\triangle EC'A$，中间就可以得到一个正方形 $ACEC'$。

我们把这个模型放到一个**直角坐标系**上，然后就会发现，**构成这个正方形的四点之间坐标的差距其实就是 $a$ 和 $b$ 及其相反数**。

$A_x=C_x-b=C'_x-a,A_y=C_y+a=C'_y-b$

$E_x=C_x+a=C'_x+b,E_y=C_y+b=C'_y-a$

根据这个规律，知道两点就可以知道 $a$ 和 $b$，然后可以推导出其他点。
# 实现
```cpp
#include<iostream>
#include<set>
using namespace std;
set<pair<int,int>> v;
char mp;
int ans;
int main(){
	for(int i=1;i<=9;i++)
	for(int j=1;j<=9;j++){
		cin>>mp;
		if(mp=='#')v.insert({i,j});
	}for(auto p:v)
	for(auto P:v)
	if(p.first!=P.first||p.second!=P.second){
		int b=P.first-p.first,a=P.second-p.second,l=ans;b,P.first+a,P.second-b,p.first-a,p.second+b,P.first-a,P.second+b);
		if(v.count({p.first+a,p.second-b})&&v.count({P.first+a,P.second-b}))ans++;
		if(v.count({p.first-a,p.second+b})&&v.count({P.first-a,P.second+b}))ans++;
	}printf("%d",ans>>3);
	return 0;
}
```

---

## 作者：WS_ZZM (赞：2)

题意让我们在一个固定面积（$9 \times 9$）的矩阵内找到所有由四个 `#` 分别作为四个顶点的正方形的个数。

分析一下，很容易观察到，此题的**数据范围**非常小，可以完全**暴力枚举**。在枚举之前，可以用一个结构体或 `vector` 存储所有 `#` 所在位置。

问题来了，怎么判正方形呢？让我们想想正方形的性质：一个正方形，它的四个角必须都是 $90$ 度，其次，它的边必须完全相等。

重点就在于判边。不妨假设有正方形 $A$，我们可以把 $A$ 一分为二，分成两个同样的三角形。根据 勾股定理，三角形的两条**直角边**（也就是 $A$ 的边长） 的平方和一定等于斜边的平方。所以，我们可以利用该性质去判边。


# AC Code

```cpp
#include<cstdio>
//#include<cmath>
using namespace std;

struct zxc{
    int x,y;
}a[99];
inline int ED(const zxc &a,const zxc &b)
    {return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);}
/*
inline int __ED(const zxc &a,const zxc &b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
    //欧几里得距离（有精度误差）
}
*/
int main(){
    int len=0;
    for(int i=1;i<10;++i){
        for(int j=1;j<10;++j)
            if(getchar()=='#')
                a[++len].x=i,a[len].y=j;
        getchar();
    }
    int ans=0;
    for(int i=1,d1,d2,d3;i<=len;++i)
        for(int j=i+1;j<=len;++j)
            for(int k=j+1;k<=len;++k)
                for(int l=k+1;l<=len;++l)
                    if(a[i].x-a[j].x==a[k].x-a[l].x&&a[i].y-a[j].y==a[k].y-a[l].y){
                        d1=ED(a[i],a[j]),d2=ED(a[i],a[k]),d3=ED(a[i],a[l]);
                        if(d1==d2&&d1+d2==d3)++ans;
                        /*
                        d1=__ED(a[i],a[j]),d2=__ED(a[i],a[k]),d3=__ED(a[i],a[l]);
                        if(d1==d2&&d1*d1+d2*d2==d3*d3)++ans;
                        */
                    }
    printf("%d\n",ans);
    return 0;
}
```

再次**强调**：注意，不要完全采用欧几里得距离求法，会有精度误差。

---

## 作者：Tooler_Yang (赞：2)

这道题目数据太小，直接枚举即可。

判断四个点是否能构成正方形的方式是先判断是否有三个直角，再判断是否有边相等。

```cpp
#include<bits/stdc++.h>
using namespace std;

vector<pair<int,int> > pl;
int main(){
	string s[9];
	for(int i=0;i<9;i++){
		cin>>s[i];
		for(int j=0;j<s[i].size();j++)
			if(s[i][j]=='#'){
				pl.push_back({i,j});
			}
	}
	int ans=0;
	for(int i=0;i<pl.size();i++){
		for(int j=i+1;j<pl.size();j++){
			for(int k=j+1;k<pl.size();k++){
				for(int p=k+1;p<pl.size();p++){
					if(pl[i].first-pl[j].first==pl[k].first-pl[p].first&&pl[i].second-pl[j].second==pl[k].second-pl[p].second){
						int dis1=(pl[i].first-pl[j].first)*(pl[i].first-pl[j].first)+(pl[i].second-pl[j].second)*(pl[i].second-pl[j].second);
                        int dis2=(pl[i].first-pl[k].first)*(pl[i].first-pl[k].first)+(pl[i].second-pl[k].second)*(pl[i].second-pl[k].second);
                        int dis3=(pl[i].first-pl[p].first)*(pl[i].first-pl[p].first)+(pl[i].second-pl[p].second)*(pl[i].second-pl[p].second);
						if(dis1==dis2&&dis1+dis2==dis3){
							ans++;
						}
					}
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：二叉苹果树 (赞：1)

## 题意

统计出以 ```#``` 作为四个顶点，构成的正方形的个数。

## 做法

数据范围很小，我们可以直接暴力枚举，依据题意判断并统计答案即可。

正方形既是平行四边形，也是矩形，也是菱形，只要满足上述三种图形的其中三个判定条件即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans;
vector<pair<int,int> >e;
int main()
{
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
        {
            char s;
            cin>>s;
            if(s=='#')
                e.push_back(make_pair(i,j));
        }
    sort(e.begin(),e.end());
    for(int i=0;i<e.size();i++)
        for(int j=i+1;j<e.size();j++)
            for(int k=j+1;k<e.size();k++)
                for(int l=k+1;l<e.size();l++)
                    if(e[i].first-e[j].first==e[k].first-e[l].first&&e[i].second-e[j].second==e[k].second-e[l].second)
                    {
                        int l1=(e[i].first-e[j].first)*(e[i].first-e[j].first)+(e[i].second-e[j].second)*(e[i].second-e[j].second);
                        int l2=(e[i].first-e[k].first)*(e[i].first-e[k].first)+(e[i].second-e[k].second)*(e[i].second-e[k].second);
                        int l3=(e[i].first-e[l].first)*(e[i].first-e[l].first)+(e[i].second-e[l].second)*(e[i].second-e[l].second);
                        if(l1==l2&&l1+l2==l3)
                            ans++;
                    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：xzz_0611 (赞：0)

[AtCoder 传送门](https://atcoder.jp/contests/abc275/tasks/abc275_c)  
[洛谷传送门](/problem/AT_abc275_c)
### 大致题意
求以 `#` 为顶点的正方形个数。
### 思路分析
一道水黄。

首先我们可以看到题目范围非常小，仅仅只是一个 $9\times9$ 的字符矩阵，而且还给了 $2$ 秒的时间，所以是完全可以暴力的。

可以用 `set` 存储每个 `#` 号的位置，枚举正方形的两个点 $i$ 和 $j$，设另外两个点为 $n$ 和 $m$，容易得到 $n_x=i_x+i_y-j_y,n_y=i_y-i_x+j_x$ 和 $m_x=j_x+i_y-j_y,m_y=j_y-i_x+j_x$ 四个公式求出 $n$ 和 $m$ 的坐标，在判断是否是 `#` 即可。

需要注意的是，由于每个角在枚举时都会算一遍，所以答案要乘 $\frac{1}{4}$。
### Code
代码如下：
```cpp
#include <iostream>
#include <set>
using namespace std;
signed main() {
	ios::sync_with_stdio(false), cin.tie(), cout.tie();
	char ch;
	int ans = 0;
	set <pair<int, int>> s;
	for (int i = 1; i <= 9; ++i)
		for (int j = 1; j <= 9; ++j) {
			cin >> ch;
			if (ch == '#') s.insert({i,j});//初始化 s
		}
	for (pair <int, int> i : s)
		for (pair <int, int> j : s)
			if (i != j) {//如果不是同一个点才进行操作
				int x = i.second - j.second, y = i.first - j.first;
				if (s.find({i.first + x, i.second - y}) != s.end() && s.find({j.first + x, j.second - y}) != s.end()) ++ans;//判断，累加答案
			}
	cout << ans / 4;//答案要除以 4
	return 0;
}
```

---

## 作者：Lydia1010__ (赞：0)

## 本题思路：
这道题其实就是一道大模拟，我们可以直接把四个点都枚举出来，然后我们可以直接算出四条边的边长是多少。

如果四条边都相等，我们就可以利用勾股定理，因为正方形连接对角线就是一个等腰直角三角形，那么我们就可以算出对角线的长度，然后用勾股定理去判断直角就可以了。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
char a[10][10];
int pd(int i,int i1,int j,int j1,int k,int k1,int l,int l1){
	int sum=(j-i)*(j-i)+(j1-i1)*(j1-i1);
	int sum1=(j-k)*(j-k)+(j1-k1)*(j1-k1);
	int sum2=(l-k)*(l-k)+(l1-k1)*(l1-k1);
	int sum3=(l-i)*(l-i)+(l1-i1)*(l1-i1);
	if(sum!=sum1||sum!=sum2||sum!=sum3) return 0;
	int pd1=(l-j)*(l-j)+(l1-j1)*(l1-j1);
	if(pd1!=sum*2) return 0;
	return 1;
}
signed main(){
	for(int i=1;i<=9;i++){
		for(int j=1;j<=9;j++){
			cin>>a[i][j];
		}
	}
	int ans=0;
	for(int i=1;i<=9;i++){
	for(int i1=1;i1<=9;i1++){
		if(a[i][i1]!='#') continue;
		for(int j=1;j<=9;j++){
		for(int j1=1;j1<=9;j1++){
			if(a[j][j1]!='#') continue;
			for(int k=1;k<=9;k++){
			for(int k1=1;k1<=9;k1++){
				if(a[k][k1]!='#') continue;
				for(int l=1;l<=9;l++){
				for(int l1=1;l1<=9;l1++){
					if(a[l][l1]!='#') continue;
					if((i==j&&i1==j1)||(i==k&&i1==k1)||(i==l&&i1==l1)||(j==k&&j1==k1)||(j==l&&j1==l1)||(k==l&&k1==l1)) continue;
//					cout<<1;
					if(pd(i,i1,j,j1,k,k1,l,l1)) ans++;
				}
				}
			}
			}
		}
		}
	}
	}
	cout<<ans/8;
	return 0;
}
```

---

## 作者：NEKO_Daze (赞：0)

[洛谷AT_abc275_c](https://www.luogu.com.cn/problem/AT_abc275_c)

### 简要题意

给出一个 $9\times 9$ 的字符矩形，仅包含 `.` 和 `#`。求出有多少个四个角为 `#` 的正方形。

### 思路

考虑暴力枚举。由于数据量小，完全可以直接枚举四个点的位置来判断是否为正方形。

至于判断是否为正方形，使用勾股定理判断是否为直角，再判断相邻两边是否相等即可（邻边相等的矩形为正方形）。

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

这次先上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char mp; vector<pair<int, int>>ps;
set<pair<double, double>>st; int ans;
signed main() {
	ios::sync_with_stdio(0);
	for (int i = 1; i != 10; ++i)
		for (int j = 1; j != 10; ++j)
			if (cin >> mp, mp == '#')
				ps.emplace_back(make_pair(i, j)),
				st.insert(make_pair(i, j));
	for (int i = 0; i != ps.size(); ++i)
		for (int j = i + 1; j != ps.size(); ++j) {
			pair<double, double>p1 =
				make_pair((ps[i].first + ps[j].first + ps[i].second - ps[j].second) * 0.5,
						  (ps[i].second + ps[j].second + ps[j].first - ps[i].first) * 0.5);
			pair<double, double>p2 =
				make_pair((ps[i].first + ps[j].first - ps[i].second + ps[j].second) * 0.5,
					   	  (ps[i].second + ps[j].second - ps[j].first + ps[i].first) * 0.5);
			if (st.count(p1) && st.count(p2)) ans++;
		}
	cout << ans / 2 << endl;
	return 0;
}
//私は猫です
```

虽然但是，这就是截至这篇文章创建时的最优解。

其实思路很简单，就是去枚举对角线上的点，然后用数学知识推出另外两个点的坐标，最后判断这两个点在不在点集中。点的坐标公式在代码中。其实只需要两个知识：线段中点坐标公式，全等的构造。没别的了。

---

## 作者：__hjwucj__ (赞：0)

# 题解：AT_abc275_c [ABC275C] Counting Squares

[题目传送门](https://www.luogu.com.cn/problem/AT_abc275_c)

## 思路

由于数据太弱，我们可以考虑存储每个 `'#'` 的位置，然后逐一枚举即可。

但是，我们要怎么存储每对坐标的位置呢？？？（map 会编译错误）

这就要使用 C++ 中非常强悍的一项容器：set。

set 可以存储成对的数据，如 pair 容器（只能存单个）。

### set的定义

```cpp
set<类型（可以是 pair，也可以是自己编的结构体）> 变量名;
```

### set的成员函数

1.`begin ()` 

返回指向容器中第一个（注意，是已排好序的第一个）元素的双向迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。

2.`end ()`

返回指向容器最后一个元素（注意，是已排好序的最后一个）所在位置后一个位置的双向迭代器，通常和 begin() 结合使用。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。

3.`find (x)`

在 set 容器中查找值为 $x$ 的元素，如果成功找到，则返回指向该元素的双向迭代器；反之，则返回和 `end ()` 方法一样的迭代器。另外，如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。

4.`lower_bound (x)`

返回一个指向当前 set 容器中第一个大于或等于 $x$ 的元素的双向迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。

5.`upper_bound (x)`

返回一个指向当前 set 容器中第一个大于 $x$ 的元素的迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。

6.`equal_range (x)`

该方法返回一个 pair 对象（包含 2 个双向迭代器），其中 `pair.first` 和 `lower_bound ()` 方法的返回值等价，`pair.second` 和 `upper_bound ()` 方法的返回值等价。也就是说，该方法将返回一个范围，该范围中包含的值为 $x$ 的元素（set 容器中各个元素是唯一的，因此该范围最多包含一个元素）。

7.`empty ()`

若容器为空，则返回 true；否则 false。

8.`size ()`

返回当前 set 容器中存有元素的个数。

9.`max_size ()`

返回 set 容器所能容纳元素的最大个数，不同的操作系统，其返回值亦不相同。

10.`insert (x)`

向 set 容器中插入元素 $x$。

11.`erase (x)`

删除 set 容器中存储的元素 $x$。

12.`swap`

交换 $2$ 个 set 容器中存储的所有元素。这意味着，操作的 $2$ 个 set 容器的类型必须相同。

13.`clear ()`

清空 set 容器中所有的元素，即令 set 容器的 `size ()` 为 $0$。

14.`emplace (x)`

在当前 set 容器中的指定位置直接构造新元素 $x$。其效果和 `insert ()` 一样，但效率更高。

15.`emplace_hint (x)`

在本质上和 `emplace ()` 在 set 容器中构造新元素的方式是一样的，不同之处在于，使用者必须为该方法提供一个指示新元素生成位置的迭代器，并作为该方法的第一个参数。

16.`count (x)`

在当前 set 容器中，查找值为 $x$ 的元素的个数，并返回。注意，由于 set 容器中各元素的值是唯一的，因此该函数的返回值最大为 $1$。

## 实现

不难想到，可以用 set 存储所有 `'#'` 的坐标，然后枚举即可。

**注意：答案要除以 $4$！！！**

## 代码参考

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace drest {
#define _fcfo friend const fast_io& operator
#define _io const fast_io& io
#define _gething1(_ch) (bool) ((_ch=getchar())==' '||_ch=='\n'||_ch=='\t'||_ch==4)
#define _gething2(_ch) (bool) ((_ch = getchar())<'0'||_ch>'9')
    /* code by Drest */
    const char* _website_ = "dresteam.online";
    using std::string;	using std::pair;	using std::map;		using std::set;
    using std::vector;	using std::queue;	using std::deque;   using std::priority_queue;
    using std::sort;    using std::swap;	using std::min;	    using std::max;
    using std::floor;   using std::ceil;    char _ch_;
    template<class T> T abs(const T & x) {return x < 0 ? -x : x;}
    class fast_io {
        template<class T> static const fast_io& input_integer(_io, T &x) {
            T f = 1, res;   while(_gething2(_ch_)) if(_ch_ == '-') f = -1; res = _ch_ ^ 48;
            while(!_gething2(_ch_)) res= (res << 1) + (res << 3) + (_ch_ ^ 48); x = res * f;	return io;
        }
        template<class T> static const fast_io& output_integer(_io, T &x)
        {if(x<0)putchar('-'); x = abs(x); if(x>9)io<<(T)(x/10); putchar(x%10+'0'); return io;}
        _fcfo >> (_io, bool &x) 	    {return input_integer(io, x);}
        _fcfo >> (_io, short &x) 		{return input_integer(io, x);}
        _fcfo >> (_io, int &x)     	    {return input_integer(io, x);}
        _fcfo >> (_io, long &x) 		{return input_integer(io, x);}
        _fcfo >> (_io, long long &x)	{return input_integer(io, x);}
        _fcfo >> (_io, __int128 &x)	    {return input_integer(io, x);}
        _fcfo << (_io, short x)		    {return output_integer(io, x);}
        _fcfo << (_io, int x)	    	{return output_integer(io, x);}
        _fcfo << (_io, long x)	    	{return output_integer(io, x);}
        _fcfo << (_io, long long x)  	{return output_integer(io, x);}
        _fcfo << (_io, __int128 x)   	{return output_integer(io, x);}
        _fcfo >> (_io, float &x)	    {scanf ("%f", &x);   return io;}
        _fcfo >> (_io, double &x)   	{scanf ("%lf", &x);  return io;}
        _fcfo << (_io, float x)      	{printf ("%f", x);   return io;}
        _fcfo << (_io, double x)     	{printf ("%lf", x);  return io;}
        _fcfo >> (_io, char &x) 	    {while (_gething1(x)) {}    return io;}
        _fcfo << (_io, char x)       	{putchar (x);	    return io;}
        _fcfo >> (_io, string &x)    	{while(_gething1 (_ch_)) {} x = _ch_; while (!_gething1(_ch_)) x += _ch_; return io;}
        _fcfo << (_io, string x)	  	{for(int i=0; i < x.size (); i++)putchar (x[i]); return io;}
        _fcfo >> (_io, char* &x)     	{string res; io >> res; x=&res[0]; return io;}
        _fcfo << (_io, char* x)	        {for (int i=0; i < strlen(x); i++) putchar (x[i]); return io;}
        public:
            fast_io& getline(string &x) {x = ""; while ((_ch_ = getchar ()) != '\n' && _ch_ != 4) x += _ch_; return *this;}
            fast_io& getline(char* &x)  {string res;     this->getline (res);     x = &res[0];	  return *this;}
    };
    fast_io io, cin, cout;  const char & endl = '\n';
}
#define cin io
#define cout io
#define endl '\n'
#define f first
#define s second
using namespace drest;
char c;
int ans=0;
set<pair<int,int>> st;
int main ()
{
	for (int i=1;i<=9;i++)
		for (int j=1;j<=9;j++)
		{
			cin>>c;
			if (c=='#') st.insert ({i,j});
		}
	for (auto i:st)
		for (auto j:st)
			if (i!=j)
			{
				int l=i.s-j.s,r=i.f-j.f;
				if (st.find ({i.f+l,i.s-r})!=st.end ()&&st.find ({j.f+l,j.s-r})!=st.end ())
					ans++;
			}
	cout<<ans/4;
	return 0;
}
```

---

## 作者：Forever_LYD (赞：0)

这年头能有暴力模拟就能过的题实在太少了，按题意去进行模拟，是否是正方形就需要判定直角与等边，直角随便考虑就想到勾股，等边当然也可以用勾股求证，如果二者都满足，正方形数量 $tot$ 就增加。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>>point;
string s[100];
int tot;
int sc,cs,la;
int main(){
	for(int i=0;i<9;i++){
		cin>>s[i];
		for(int j=0;j<s[i].size();j++)if(s[i][j]=='#')point.push_back({i,j});
	}
	for(int i=0;i<point.size();i++){
		for(int j=i+1;j<point.size();j++){
			for(int as=j+1;as<point.size();as++){
				for(int ind=as+1;ind<point.size();ind++){
					if(point[i].first-point[j].first==point[as].first-point[ind].first&&point[i].second-point[j].second==point[as].second-point[ind].second){
						sc=(point[i].first-point[j].first)*(point[i].first-point[j].first)+(point[i].second-point[j].second)*(point[i].second-point[j].second);
                        cs=(point[i].first-point[as].first)*(point[i].first-point[as].first)+(point[i].second-point[as].second)*(point[i].second-point[as].second);
                        la=(point[i].first-point[ind].first)*(point[i].first-point[ind].first)+(point[i].second-point[ind].second)*(point[i].second-point[ind].second);
						if(sc==cs&&sc+cs==la)tot++;
					}
				}
			}
		}
	}
	cout<<tot<<"\n";
	return 0;
}
```


---

