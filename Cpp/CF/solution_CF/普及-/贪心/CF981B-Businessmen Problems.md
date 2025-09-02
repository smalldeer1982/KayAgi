# Businessmen Problems

## 题目描述

Two famous competing companies ChemForces and TopChemist decided to show their sets of recently discovered chemical elements on an exhibition. However they know that no element should be present in the sets of both companies.

In order to avoid this representatives of both companies decided to make an agreement on the sets the companies should present. The sets should be chosen in the way that maximizes the total income of the companies.

All elements are enumerated with integers. The ChemForces company has discovered $ n $ distinct chemical elements with indices $ a_1, a_2, \ldots, a_n $ , and will get an income of $ x_i $ Berland rubles if the $ i $ -th element from this list is in the set of this company.

The TopChemist company discovered $ m $ distinct chemical elements with indices $ b_1, b_2, \ldots, b_m $ , and it will get an income of $ y_j $ Berland rubles for including the $ j $ -th element from this list to its set.

In other words, the first company can present any subset of elements from $ \{a_1, a_2, \ldots, a_n\} $ (possibly empty subset), the second company can present any subset of elements from $ \{b_1, b_2, \ldots, b_m\} $ (possibly empty subset). There shouldn't be equal elements in the subsets.

Help the representatives select the sets in such a way that no element is presented in both sets and the total income is the maximum possible.

## 说明/提示

In the first example ChemForces can choose the set ( $ 3, 7 $ ), while TopChemist can choose ( $ 1, 2, 4 $ ). This way the total income is $ (10 + 2) + (4 + 4 + 4) = 24 $ .

In the second example ChemForces can choose the only element $ 10^9 $ , while TopChemist can choose ( $ 14, 92, 35 $ ). This way the total income is $ (239) + (15 + 65 + 89) = 408 $ .

## 样例 #1

### 输入

```
3
1 2
7 2
3 10
4
1 4
2 4
3 4
4 4
```

### 输出

```
24
```

## 样例 #2

### 输入

```
1
1000000000 239
3
14 15
92 65
35 89
```

### 输出

```
408
```

# 题解

## 作者：YUYGFGG (赞：2)

其实不要上面那个大佬讲得那么麻烦

用一个 $map$ 记录每个编号的最大价值，再遍历 $map$ 求总和就可以了

code:
```cpp
#include<bits/stdc++.h>
#define fol(i,a,b) for(int i=a;i<=(b);i++)
#define bor(i,a,b) for(int i=a;i>=(b);--i)
#define int long long
using namespace std;
map<int,int> mp;
signed main(){
    int n,m,tmp;
    cin>>n;
    fol(i,1,n){
        cin>>m>>tmp;
        mp[m]=max(mp[m],tmp);
    }
    cin>>n;
    fol(i,1,n){
        cin>>m>>tmp;
        mp[m]=max(mp[m],tmp);
    }
    int sum=0;
    for(map<int,int>::iterator it=mp.begin();it!=mp.end();it++){
        sum+=(*it).second;
    }
    cout<<sum<<endl;
    return 0;
}
```


---

## 作者：LJB00131 (赞：1)

简述题意：在两组元素中，选出最大不重复的多个元素，使其总价值最大。

于是我们有了第一种做法

**方法一**

就是我们最可爱的 
## 暴力

用一个数组num[i]存放第i号元素最大价值，
输入完之后扫一遍就可以了。

但是我们注意一下数据范围($ 1 \le a_i \le 10^9 $),所以数组根本开不下。

**预计得分：0**

**方法二**

既然一个数组存不下，那我们只能开两个数组了。那么怎么查找元素呢？

等等“**查找？**”

加快查找的方法是什么？

## 二分

依然要二分，那么数据必须要有序。在这道题中，元素位置是不影响他的编号与价值的。所以，我们可以在输入后排序。

剩下的就非常简单了
只需要查找一组，再在另一组里二分查找同编号的，返回价值大的就搞定了。

**预计得分：100**

最后上ac代码

```cpp
#include<bits/stdc++.h>

using namespace std;

struct s
{
	long long o,w;
};//元素

int n,m;

s a[100001];//第一个公司

s b[100001];//第二个公司

int used[100001];//在第二个公司查找后，需要标记他已被找过

long long ans = 0;

bool cmp(s x,s y)
{
	return x.o < y.o;
}

long long check(int x)
{
	int l = 1, r = m;//二分过程
	while(l <= r)
	{
		int mid = (l + r) / 2 ;
		//cout<<l<<' '<<r<<' '<<mid<<endl;
		if(b[mid].o == a[x].o)//如元素相同
		{
			used[mid] = 1; 
			return max(a[x].w,b[mid].w);
		}
		if(b[mid].o > a[x].o) r = mid - 1;
		else l = mid + 1;
	}
	return a[x].w;//只有第一个公司有的元素
}

int main()
{
	scanf("%d",&n);
	for(int i = 1; i <= n; i++)
		scanf("%I64d%I64d",&a[i].o,&a[i].w);
	sort(a + 1, a + n + 1,cmp);
	scanf("%d",&m);
	for(int i = 1; i <= m; i++)
		scanf("%I64d%I64d",&b[i].o,&b[i].w);
	sort(b + 1, b + m + 1,cmp);//输入与排序

	for(int i = 1; i <= n; i++)
		ans += check(i);
	for(int i = 1; i <= m; i++)
		if(!used[i]) ans += b[i].w;//只有第二个公司有的元素
	printf("%I64\n",ans);
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
有一个长度为 $n$ 的序列和长度为 $m$ 的序列，两个序列中的元素都有一个编号 $num$ 和一个值 $val$，且同一个序列的元素之间的编号互不相同。现在从这两个序列中选取一些元素，要求编号不能重复，求能够取到的最大价值。

**数据范围：$1\leqslant n,m\leqslant 10^5,1\leqslant num,val\leqslant 10^9$。**
## Solution
我们可以开个 $vis$ 数组来判断是否之前取过，同时它还起到储存当前编号的元素的价值。但是范围太大怎么办？用 $\texttt{map}$ 呗，直接映射来实现就好。

如果出现了两个编号相同的元素，怎么办？取相同编号之间价值的较大值就好。
## Code
```cpp
int n, m, a[100007], x, b[100007], y;
map<int, int> vis;
ll ans;

int main() {
	getint(n);
	_for(i, 1, n) {
		getint(a[i]), getint(x);
		vis[a[i]] = x;
		ans += x;
	}
	getint(m);
	_for(i, 1, m) {
		getint(b[i]), getint(y);
		if(vis[b[i]] < y) {
			ans += (y - vis[b[i]]);
			vis[b[i]] = y;
		}
	}
	writell(ans);
	return 0;
}
```

---

