# [USACO19OPEN] Cow Evolution B

## 题目描述

现在是 3019 年，在过去的一千年里发生了不计其数的牛类进化，产生了具有各种有趣特性的奶牛。

牛类进化的记录可以用一棵树来表示，起源是位于树根位置的没有特殊特性的奶牛。树上每一个产生后代的结点，有可能所有的奶牛都进化出了一种新的特性（比如说喷火（fire breathing），如下图所示，其中所有斑点（spots）奶牛最后都能喷火），或者是奶牛种群产生了分支进化，其中有些进化出了新的特性（比如，飞（flying）），有的没有。 

![](https://cdn.luogu.com.cn/upload/image_hosting/q7v0zhg4.png)

树底部的叶结点表示 3019 年所有产生的奶牛的子种群。没有不同的叶结点（子种群）具有完全相同的一组特性。例如，子种群 #1 是没有特殊特性的奶牛，子种群 #3 是能够心灵感应的（telepathic）会飞的奶牛。相比之下，子种群 #2 是会飞但不能心灵感应的奶牛。子种群 #3 是唯一既会飞又会心灵感应的。

像上图这样每一种进化出的新特性都恰好在树中的一条边上产生（也就是说，在整个进化历史中仅在一个时间点产生），这样的进化树被称为是“合法的”。例如，如果斑点这一特性在两个不同分支中均进化产生，这棵进化树就不是合法的。给定 3019 年奶牛子种群的描述，请判断是否这可以由一棵合法的进化树所解释。 

## 说明/提示

### 样例解释 1


这个输入样例与上图所示的合法进化树一致。 

## 样例 #1

### 输入

```
4
2 spots firebreathing
0
1 flying
2 telepathic flying```

### 输出

```
yes```

# 题解

## 作者：cly312 (赞：2)

这题的关键就在于能否将问题转化成**集合之间是否有交集**。

首先，考虑一个我们无法形成进化树的例子，例如这样：
```
3
1 fly
1 man
2 fly man
```
![](https://cdn.luogu.com.cn/upload/image_hosting/1n37rfol.png)

如果我们想根据这个输入构建一棵树，我们需要在根上分割 A 或 B，但剩下的两个子树都需要有一条边来添加另一个特征。显然输出为"No"。

如果我们输入中的特征 A 和 B 中的任何两个表示如上所述的交集不为空，那么我们就无法构建一棵合适的树。

像下面的例子就可以用一棵树来表示：

![](https://cdn.luogu.com.cn/upload/image_hosting/gti6of4p.png)

画出来的树长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/1f24hpir.png)

相信你已经理解了我们只需要判断是否任意两个集合中交集是否为空就可以了，代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int N;
vector<string> c[25];
vector<string> allc;

//集合是否相交 
bool crossing(int a, int b) {
	int A=0, B=0, AB=0;
	for (int i=0; i<N; i++) {
		vector<string> &v = c[i];
		bool has_a = false, has_b = false;
		for (int j=0; j<v.size(); j++) {
			if (v[j]==allc[a]) has_a = true;
			if (v[j]==allc[b]) has_b = true;
		}
		if (has_a && has_b) AB++;
		else if (has_a) A++;
		else if (has_b) B++;
	}
	return AB>0 && A>0 && B>0;
}

int main() {
	cin >> N;
	string s;
	for (int i=0; i<N; i++) {
		int K;
		cin >> K;
		for (int j=0; j<K; j++) {
			cin >> s;
			c[i].push_back(s);
			bool found = false;
			for (int k=0; k<allc.size(); k++)
				if (allc[k] == s) found = true;
			if (!found) allc.push_back(s);
		}
	}
	int M = allc.size();
	bool ok = true;
	for (int a=0; a<M; a++)
		for (int b=a+1; b<M; b++)
			if (crossing(a, b)) ok = false;
	if (ok) cout << "yes\n";
	else cout << "no\n";
	return 0;
}
```

---

## 作者：luanXiPing_AKed_IOI (赞：2)

# 题意
[点这里](https://www.luogu.com.cn/problem/P1701)看原题
判断能否建一棵树，每条边不带名字/名字不重复，使得给出的几个集合每个集合都是一条从根节点到叶子节点的路径上所经过的所有带名字的边的名字的集合。
# 分析
本题重点在于判断所给的子种群会不会有冲突。子种群本身之间的联系不强，不好入手。手推几个样例试试，就会发现任意两个子种群的公共特征一定在这两个子种群的非公共特征的上面（深度更小）。举个栗子：$AD,AB,ABC$ 其中，$A,AB$ 都是在 $C$ 上面的从原点到某节点的路径。而这些路径还有一个特点，即都（应该）是同一路径的一部分。换言之，长度短的路径应是长度长的路径的一部分。判断这些路径（$A,AB$）是否合法就可以判断是否可以建一颗合法的进化树。
# 求解
$a_{i}$ 代表第 $i$ 个子种群所具有的特征（状态压缩bitset存储），遍历 $1 \le i \le n,1 \le j \le n$ 求出 $b_{i,j}=a_{i} \land b_{j}$ ，求出 $b$ 后遍历 $1 \le i \le n$ 将 $[b_{i,1},b_{i,n}]$ 按 $1$ 的数量（路径长度）升序排序，如果有 $j$ 满足 $(b_{i,j} \land b_{i,j+1}) \ne b_{i,j}$（$b_{i,j}$ 不被 $b_{i,j+1}$ 包含），那么就无法建一颗合法的进化树。
***
注意要用 unordered_map 建立特征到编号的映射。同时由于特征最多有 $N \times N=625$，要使用 bitset 存储。
# 代码
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <bitset>
using namespace std;
typedef long long LL;
const LL N = 30;
LL n, k, cnt = 0;
bitset<N * N> a[N], b[N][N];
unordered_map<string, LL> mp;
//路径长度升序排列比较器
bool cmp(bitset<N * N> x, bitset<N * N> y) {
    return x.count() < y.count();
}

int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i ++ ) {
        scanf("%lld", &k);
        while (k--) {
            string s;
            cin >> s;
            if (mp.find(s) == mp.end()) {
                mp[s] = ++cnt;
            }
            
            a[i][mp[s]] = 1;
        }
    }
    
    for (int i = 1; i <= n; i ++ ) {
        for (int j = 1; j <= n; j ++ ) {
            b[i][j] = a[i] & a[j];
        }
        
        sort(b[i] + 1, b[i] + n + 1, cmp);
        for (int j = 1; j <= n - 1; j ++ ) {
            if ((b[i][j] & b[i][j + 1]) != b[i][j]) {
                printf("no\n"); //不合法
                return 0;
            }
        }
    }
    
    printf("yes\n"); //如果没有不合法，那就不是不合法的，所以就是合法的
}
```
时间复杂度：$O(n^{2} \log{n})$  
空间复杂度：$O(n^{2})$

---

