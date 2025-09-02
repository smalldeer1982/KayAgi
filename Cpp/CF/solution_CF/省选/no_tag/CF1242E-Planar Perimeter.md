# Planar Perimeter

## 题目描述

Ujan终于把他的房子打扫干净了，现在想装饰一下室内。他决定放置一块漂亮的地毯，将客房真正地连接起来。

他对多边形图块组成的地毯感兴趣，这样的图块的每一边要么是另一个（不同）图块的一边，要么是整个地毯外侧的一边。换句话说，地毯可以被表示为一个平面图，每个图块都对应于图的一面，每一面都是一个简单的多边形。地毯的周长就是图的外侧边的数量。

如果一个地毯由 $f$ 个图块组成，其中第 $i$ 个图块正好有 $a_{i}$ 条边，并且周长是最小的，那么Ujan认为它是美丽的。找到一个这样的地毯，这样Ujan就可以订购它了!

## 样例 #1

### 输入

```
2
3 3
```

### 输出

```
4
2 1 4 
1 2 3 
```

## 样例 #2

### 输入

```
3
5 3 5
```

### 输出

```
6
1 2 3 4 5
4 5 6
1 3 4 6 5
```

# 题解

## 作者：jiangly (赞：11)

#### 题意

构造一个简单平面图，使得其每个内部区域的周长分别为 $a_1,a_2,\ldots,a_f$，且无穷大区域的周长最小。

#### 限制

$1\le f\le 10^5$, $3\le a_i\le 3\cdot 10^5$, $\sum_{i=1}^{f}a_i\le 3\cdot10^5$。

#### 题解

我们将 $a_i$ 降序排列，考虑最大的一个面 $a_1$。如果 $a_1-\sum_{i=2}^{f}(a_i-2)\ge 3$，则最终的周长为 $a_1-\sum_{i=2}^f(a_i-2)$，因为一个新加的面最多让周长减少 $a_i-2$。否则，答案为 $4-(\sum_{i=1}^fa_i)\bmod 2$，只要在构造到第 $i$ 个面时满足 $C\ge a_{i+1}$ 的条件下尽可能让周长变小。构造方案时用双端队列维护当前外部的边即可。

还有一个问题需要解决：我们构造出的图可能有重边。解决方案是每次添加一个面后平移一位，从下一条边开始添加。这样做的正确性可以这样考虑：出现重边的情况只可能是在一条边上先后添加两个三角形，但是每次产生了一条内部连边后都会被下一个三角形直接覆盖，所以不可能出现重边。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int f;
    cin >> f;
    vector<pair<int, int>> a(f);
    for (int i = 0; i < f; ++i) {
        int x;
        cin >> x;
        a[i] = {x, i};
    }
    sort(a.begin(), a.end(), greater<pair<int, int>>());
    int n = 0;
    deque<int> q;
    vector<vector<int>> v(f);
    for (int i = 0; i < a[0].first; ++i) {
        q.push_back(n);
        v[a[0].second].push_back(n);
        ++n;
    }
    for (int i = 1; i < f; ++i) {
        int e, k;
        tie(e, k) = a[i];
        int p = min(e - 1, ((int)q.size() + e - (i == f - 1 ? 3 : a[i + 1].first)) / 2);
        for (int j = 0; j < p - 1; ++j) {
            v[k].push_back(q.back());
            q.pop_back();
        }
        v[k].push_back(q.back());
        for (int j = p; j < e - 1; ++j) {
            v[k].push_back(n);
            q.push_back(n);
            ++n;
        }
        v[k].push_back(q.front());
        q.push_back(q.front());
        q.pop_front();
    }
    cout << n << "\n";
    for (int i = 0; i < f; ++i)
        for (int j : v[i])
            cout << j + 1 << " \n"[j == v[i].back()];
    return 0;
}
```



---

## 作者：Delusions_grandeur (赞：0)

>  ~~窝就是来水题解的~~，补充一下 @jiangly 没说的细节

还是把 $a_i$ 从大到小排序，可以发现如果一个新加入的多边形有 $p$ 条边与原多变形重合，则会减少 $p-(e-p)=2\times p-e$ 条露在外面的边，当 $p=e-1$ 时可以让周长最多减少 $e-2$。

如果 $a_1-\sum_{i=2}^{f}(a_i-2)\ge 3$，直接减即可；否则我们希望周长尽量小，用双端队列 $l$ 存最外围的点序列，则周长也就是 $l$ 的大小设为 $sz$，此时可以构造一个序列 $\lfloor\dfrac{p_i=sz+e_i-e_{i+1}}{2}\rfloor$，则加入这个多边形后 $sz$ 会减少 $2*p_i-e_i $，即 $sz^{\prime}=e_i$，注意因为下取整的原因等号不一定能取到，但至多相差 $1$，到最后一步时让 $e_{f+1} =3$ 即可 ； 由于$e_i$ 可能比 $p_i$ 还小，取个 $\min$ 即可。

另外，构造答案时不是随便覆盖到之前的一些边都能作为新加入多边形的重合边，只有能把原来图形的一部分先变凹（毕竟图形的凹凸性未规定嘛），才能再新开一些点进行连线；当覆盖的边为一个 $c+1$ 长的多边形的 $c$ 条边时，一定无法把这个多变形先弄凹。jiangly 给的方法是每次加一个多边形就把 $l$ 循环位移一位，每次取 $l$ 的最后几个点，正确性是显然的。

贴个丑陋的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define orzjly 998244353
const int N=1e5;
int f,n;struct item {int v,p;} a[N+5];
deque<int> q;vector<int> v[N+5];
int main()
{
	scanf("%d",&f);
	for(int i=0,x; i<f; i++) scanf("%d",&x),a[i]={x,i};
	sort(a,a+f,[](item n1,item n2) {return n1.v>n2.v;});
	for(int i=0; i<a[0].v; i++) q.push_back(n),v[a[0].p].push_back(n),++n;
	for(int i=1; i<f; i++)
	{
		int e=a[i].v,k=a[i].p;
		int p=min(e-1,((int)q.size()+e-(i==f-1?3:a[i+1].v))/2);
		for(int j=0; j<p-1; j++) v[k].push_back(q.back()),q.pop_back();
		//凑成p条边只需要p-1个凹进去的点
		v[k].push_back(q.back());
		for(int j=p; j<e-1; j++) v[k].push_back(n),q.push_back(n),++n;
		v[k].push_back(q.front());
		q.push_back(q.front());q.pop_front(); 
		//循环位移 
	}
	printf("%d\n",n);
	for(int i=0; i<f; i++) for(int j: v[i]) printf("%d%c",j+1,j==v[i].back()?'\n':' '); 
	return 0;
}
```



---

