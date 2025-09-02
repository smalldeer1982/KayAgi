# Hashing Trees

## 题目描述

Sasha is taking part in a programming competition. In one of the problems she should check if some rooted trees are isomorphic or not. She has never seen this problem before, but, being an experienced participant, she guessed that she should match trees to some sequences and then compare these sequences instead of trees. Sasha wants to match each tree with a sequence $ a_{0},a_{1},...,a_{h} $ , where $ h $ is the height of the tree, and $ a_{i} $ equals to the number of vertices that are at distance of $ i $ edges from root.

Unfortunately, this time Sasha's intuition was wrong, and there could be several trees matching the same sequence. To show it, you need to write a program that, given the sequence $ a_{i} $ , builds two non-isomorphic rooted trees that match that sequence, or determines that there is only one such tree.

Two rooted trees are isomorphic, if you can reenumerate the vertices of the first one in such a way, that the index of the root becomes equal the index of the root of the second tree, and these two trees become equal.

The height of a rooted tree is the maximum number of edges on a path from the root to any other vertex.

## 说明/提示

The only tree in the first example and the two printed trees from the second example are shown on the picture:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901A/b36c39150954d88fe8a1ed6f96a05d8a24b743af.png)

## 样例 #1

### 输入

```
2
1 1 1
```

### 输出

```
perfect
```

## 样例 #2

### 输入

```
2
1 2 2
```

### 输出

```
ambiguous
0 1 1 3 3
0 1 1 3 2
```

# 题解

## 作者：Wf_yjqd (赞：2)

我还在水构造题。

------------

很容易想到如果存在连续两层超过 $1$ 个节点，就无法确定相互之间的对应关系了。

根据以上结论判断对错即可。

考虑如何构造两颗不同的树。

我们在判断的过程中记录某个不唯一的位置。

其他位置按顺序构造树，这个位置单独考虑。

可以让其中一颗都连在父辈的同一个节点上，另一颗树中的则不在一个节点上。

这样构造出来的两颗树显然不会同构。

模拟复杂度线性。

------------

太水辣！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+84;
int h,a[maxn],ad,cnt;
int main(){
    scanf("%d",&h);
    h++;
    for(int i=1;i<=h;i++){
        scanf("%d",&a[i]);
        if(a[i]>1&&a[i-1]>1)
            ad=i;
    }
    if(!ad)
        puts("perfect");
    else{
        puts("ambiguous");
        for(int i=1;i<=h;i++){
            for(int j=1;j<=a[i];j++)
                printf("%d ",cnt);
            cnt+=a[i];
        }
        puts("");
        cnt=0;
        for(int i=1;i<ad;i++){
            for(int j=1;j<=a[i];j++)
                printf("%d ",cnt);
            cnt+=a[i];
        }
        for(int i=1;i<a[ad];i++)
            printf("%d ",cnt);
        printf("%d ",cnt-1);
        cnt+=a[ad];
        for(int i=ad+1;i<=h;i++){
            for(int j=1;j<=a[i];j++)
                printf("%d ",cnt);
            cnt+=a[i];
        }
    }
    return 0;
}
```


---

## 作者：PeterBei (赞：0)

有趣的构造题。

首先需要明确题目中所说的两棵树不同指他们的形态不同。若只是指向的节点编号不同则仍是相同的树。

也就是说下图中的两棵树在该题中被定义为相同的树。

![](https://cdn.luogu.com.cn/upload/image_hosting/vymon5el.png)

那么令 $dep_i$ 表示深度为 $i$ 的节点共有 $dep_i$ 个，则分以下几种情况讨论：

1. 若 $dep_i=dep_{i-1}=1$，那么只能以链的形式连接，构造方法唯一。

2. 若 $dep_i \neq 1,dep_{i-1}=1$，那么只能以菊花图的形式连接，构造方法唯一。

3. 若 $dep_i=1,dep_{i-1} \neq 1$，那么位于 $i-1$ 层的节点可以与任意一个位于 $i$ 层的节点连接。但按照上文对相同的树的定义，无论连在哪一个节点上，树的形态均相同，因此构造方法唯一。

4. 若 $dep_i \neq 1,dep_{i-1} \neq 1$，此时才会出现多种构造方案。我们取其中一种：在第一颗树上将第 $i$ 层的节点全部连接到第 $i-1$ 层的第一个节点上，在第二棵树上将其中一个第 $i$ 层的节点连接到另一个 $i-1$ 层的节点上即可。

综合上面的结论，发现当没有操作四时树的构造方法唯一，输出 ``perfect``，剩余的直接按照上面的情况输出即可。

```
int main(){
	int h = read(); dep[0] = 1;
	bool f = 1; int bj = 0;
	for(int i = 1; i <= h + 1; i++){
		dep[i] = read();
		if(dep[i] != 1 && dep[i - 1] != 1 && f){
			f = 0; bj = i;
		}
	} if(f){
		cout << "perfect\n";
		return 0;
	} cout << "ambiguous\n";
	int now = 0;
	for(int i = 1; i <= h + 1; i++){
		for(int j = 1; j <= dep[i]; j++){
			cout << now << ' ';
		} now += dep[i];
	} cout << '\n'; now = 0;
	for(int i = 1; i <= h + 1; i++){
		if(i == bj){
			cout << now - 1 << ' ';
			for(int j = 1; j < dep[i]; j++){
				cout << now << ' ';
			} now += dep[i];
		} else{
			for(int j = 1; j <= dep[i]; j++){
				cout << now << ' ';
			} now += dep[i];
		}
	}
	return 0;
}
```

---

## 作者：Zhao_daodao (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF901A)

# 题目描述

对于一棵树，告诉你每一个深度的节点数量，求这棵树是否唯一。

# 题目分析
### 首先
考虑一条链时的情况，此时输入即为每一层均为 `1`。

![](https://cdn.luogu.com.cn/upload/image_hosting/alisqk0f.png)

显然只有一种可能，输出 `perfect`。

### 然后
考虑一棵树，对于第 $k$ 层不止一个节点，如果 $k+1$ 层也不止一个节点，这棵树就不唯一。

如图:

![](https://cdn.luogu.com.cn/upload/image_hosting/i3bxzhke.png)

此时第二层和第三层均有超过一个节点（两个节点），可见，此时 $4$，$5$ 节点既可以分别接在 $2$，$3$ 节点上（如图 `A`），也可以都接在 $2$ 节点上（如图 `B`）。

此时这棵树的构造就不唯一了，输出 `ambiguous`。

构造方法：
1. 对于两个儿子，将两个儿子分别分到不同的两个父亲，如图 `A`。
2. 对于两个儿子，将两个儿子分到对应的两个父亲，如图 `B`。
### 但是
如果第 $k$ 层有超过一个节点，第 $k+1$ 层只有一个节点，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/f86ij9k5.png)

此时第 $4$ 层有两个节点，但是第 $5$ 层只有一个节点，所以 $6$ 号节点无论接在 $4$ 号节点下，还是接在 $5$ 号节点下，均不影响构造的唯一性。（第四层的节点必一个有儿子，一个无儿子）

此时不影响构造的唯一性，仍不影响答案。

### Tips
一旦发现又连续两层的节点数不为零，输出 `ambiguous`，立即构造，结束程序。

对于每连续两层，如果均未发现影响唯一性，输出 `perfect`。

---

## 作者：_slb (赞：0)

没人写题解的水题，我来水一下估值。

## Description

给定一棵树的深度 $h$（$h\leq 10^5$） 和每个深度的结点数（根节点的深度为 $0$），请您求出这样的树是否唯一，若不唯一，构造两棵不同构的树。

## Solution

稍微想一下就可以知道树唯一的充要条件：不存在两个相邻的深度，节点数都大于 $1$。

证明的话就分类讨论一下：如果父亲是 $1$，那么儿子只能全连到这一个点上去，就唯一了；如果儿子是 $1$，那么连到哪个父亲上都是一样的，树也是唯一的。如果都大于 $1$ 的话按照样例 $2$ 的方法构造就可以得到不同构的树了。

接下来就是构造两棵不同构的树了。

先构造一棵某层的所有点都连到上一层的一个点的树。

然后另一棵树中，如果某一层儿子父亲深度都大于 $1$，我们把儿子这一层中的一个点连到父亲的一个点上，儿子剩下的点都连到父亲的另一个点上即可，否则这层所有点都连到上一层的一个点上即可。

## Code

上面说的可能有点抽象，可以看看代码。

```cpp
namespace solve
{
    const int maxn = 3e5 + 10;

    int a[maxn], h;

    void main()
    {
        cin >> h;
        int ok = 1;
        for (int i = 0; i <= h; i++)
            cin >> a[i];
        for (int i = 1; i <= h; i++)
            if (a[i] > 1 && a[i - 1] > 1)
                ok = 0;
        if (ok)
        {
            cout << "perfect" << endl;
            return;
        }
        cout << "ambiguous" << endl;
        int now = 0;
        cout << now << " ", now += a[0];
        for (int i = 1; i <= h; i++)
        {
            for (int j = 0; j < a[i]; j++)
                cout << now << " ";
            now += a[i];
        }
        cout << endl;
        now = 0, cout << now << " ", now += a[0];
        for (int i = 1; i <= h; i++)
        {
            if (a[i] > 1 && a[i - 1] > 1)
            {
                cout << now - 1 << " ";
                for (int j = 0; j < a[i] - 1; j++)
                    cout << now << " ";
            }
            else
            {
                for (int j = 0; j < a[i]; j++)
                    cout << now << " ";
            }
            now += a[i];
        }
    }
}
```

---

