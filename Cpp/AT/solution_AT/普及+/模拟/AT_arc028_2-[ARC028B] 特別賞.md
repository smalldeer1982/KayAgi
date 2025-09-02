# [ARC028B] 特別賞

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc028/tasks/arc028_2

高橋君はプログラミングコンテストを行い、$ N $ 人の人が参加しました。賞品がないと物足りないのではないかと思った高橋君は「$ i $ 位以上の人のうち、$ K $ 番目に若い人」に特別賞を出すことにしました。参加者全員の年齢は分かっています。$ K $ の値はもう既に決めているのですが、$ i $ の値はまだ決めていません。$ i $ の値を決めるために高橋君は、$ K $ 以上 $ N $ 以下の整数 $ i $ それぞれについて誰が特別賞を取ることが出来るのかを計算してみることにしました。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ N\ ≦\ 1000 $ を満たすテストケースすべてに正解した場合は $ 40 $ 点が与えられる。

### Sample Explanation 1

以下は、出力の各行についての説明です。 - $ 1 $ 行目： $ 2 $ 位以上の人のうち $ 2 $ 番目に若い人は $ 2 $ 位の人です。 - $ 2 $ 行目： $ 3 $ 位以上の人のうち $ 2 $ 番目に若い人は $ 1 $ 位の人です。 - $ 3 $ 行目： $ 4 $ 位以上の人のうち $ 2 $ 番目に若い人は $ 3 $ 位の人です。 - $ 4 $ 行目： $ 5 $ 位以上の人のうち $ 2 $ 番目に若い人は $ 5 $ 位の人です。

## 样例 #1

### 输入

```
5 2
4 5 3 1 2```

### 输出

```
2
1
3
5```

## 样例 #2

### 输入

```
3 1
2 3 1```

### 输出

```
1
1
3```

# 题解

## 作者：一只大龙猫 (赞：0)

不难发现，倒数第 $k$ 大就是第 $k$ 小。所以，题目的意思就是：

对于每个 $i$（$k \le i \le n$），求区间 $[1,i]$ 第 $k$ 小的数的位置。

有很多种方法能帮我们求出答案，如平衡树、值域线段树等等，但我们在这里使用**被 pb_ds 库封装的红黑树（平衡树的一种）**。

关于平衡树和红黑树是什么，这里不多讲，有需要的可以看看[这里](https://www.luogu.com.cn/blog/NorthPenguin/solution-p3369)。

然后你会发现：

- 手打红黑树代码太长；

- STL 里的`set`又不支持查第 $k$ 小。

怎么办？

别担心，上文提到的 pb_ds 库已经帮我们封装了红黑树，支持插入、删除、查第 $k$ 小等操作。（详细内容可以看看[这里](https://oi-wiki.org/lang/pb-ds/tree/)和[这里](https://www.luogu.com.cn/blog/Chanis/gnu-pbds)。）

因为数据保证不重复，所以不用担心重复问题；同时又因为 $1 \le X_i \le 100000$，所以可以直接用数组存下每个数出现的位置。

代码如下：

```cpp
#include<iostream>
#include<functional>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
__gnu_pbds::tree<int,__gnu_pbds::null_type,less<int>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update> rbt;
int n,k,p[1000001];//p数组存位置 
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		p[x]=i;
		rbt.insert(x);
		if(i>=k){
			cout<<p[*(rbt.find_by_order(k-1))]<<endl;//因为pb_ds中的最小数被视为第0小，所以第k小在pb_ds中其实是第k-1小 
		}
	}
	return 0;
}
```

每次插入和求第 $k$ 小的时间复杂度都是 $\log n$，总的时间复杂度为 $n \log n$，足够了。

---

