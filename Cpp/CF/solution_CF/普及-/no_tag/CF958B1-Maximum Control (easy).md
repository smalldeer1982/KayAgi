# Maximum Control (easy)

## 题目描述

The Resistance is trying to take control over all planets in a particular solar system. This solar system is shaped like a tree. More precisely, some planets are connected by bidirectional hyperspace tunnels in such a way that there is a path between every pair of the planets, but removing any tunnel would disconnect some of them.

The Resistance already has measures in place that will, when the time is right, enable them to control every planet that is not remote. A planet is considered to be remote if it is connected to the rest of the planets only via a single hyperspace tunnel.

How much work is there left to be done: that is, how many remote planets are there?

## 说明/提示

In the first example, only planets $ 2 $ , $ 3 $ and $ 5 $ are connected by a single tunnel.

In the second example, the remote planets are $ 2 $ and $ 3 $ .

Note that this problem has only two versions – easy and medium.

## 样例 #1

### 输入

```
5
4 1
4 2
1 3
1 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1 2
4 3
1 4
```

### 输出

```
2
```

# 题解

## 作者：LiAuPb (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF958B1)

# 一、简要题意
给出有 $n$ 个点的树，求只与一个点相连的点的数量。

# 二、简要思路
定义一个用于统计的数组 $a_{i}$，边输入边统计，最后遍历一遍，再输出答案即可。

# 三、代码展示
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, x, y, a[1001], ans;//定义 
int main(){
	scanf("%d", &n);//输入有几个节点 
	for(int i = 1; i <= n - 1; i++){//注意是n - 1条边 
		scanf("%d%d", &x, &y);//输入相连的两个点 
		a[x]++;
		a[y]++;//统计到数组里去 
	}
	for(int i = 1; i <= 1000; i++){
		if(a[i] == 1){//如果与节点i相邻的只有一个点 
			ans++;//ans加一 
		}
	}
	printf("%d", ans);//输出答案 
	return 0;
}
```


---

## 作者：无钩七不改名 (赞：1)

+ 题目大意：给出 $n$ 个点，$n-1$ 条边，求只与一个点连通的点的数量。

+ 思路：很简单的一道题，直接开一个数组统计每个点的连边的数量即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a[1005],ans;

int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		a[x]++,a[y]++;
	}
	for(int i=1;i<=n;i++)if(a[i]==1)ans++;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：yinpeichu2021 (赞：0)

# 题意

给出一个 $n$ 个点的树，求只与一个点连通的点的数量。

# 思路

定义一个数组，统计点的度，当度为一时满足题意。

# CODE

```cpp
#include<bits/stdc++.h>
// #define int long long
// #define MOD 1000000007
using namespace std;
int n,a[1005],ans;
signed main(){
	cin>>n;
	for(int i=1,x;i<=n*2-2;i++)cin>>x,a[x]++;
	for(int i=1;i<=n;i++)
		if(a[i]==1)ans++;
	cout<<ans;

    return 0;
}
```

---

## 作者：WA_sir (赞：0)

### [题目](https://codeforces.com/problemset/problem/958/B1)[链接](https://www.luogu.com.cn/problem/CF958B1)

### 题目大意

给出 $n$ 个点的树，求**叶节点**（只与一个点连通的点）的数量。

### 题目分析

$n$ 个结点的树，必然有 $n-1$ 条边。

由于数据不大，在求叶结点的数量时，可以开一个桶。若一个结点在 $2$ 条或更多条边中出现过，这个节点必然不是叶节点。

在输入时记录结点的出现次数，接着一个循环判断每个节点是否为叶节点，最后输出。

---

## 作者：lkjzyd20 (赞：0)

# 题意

$N$ 个点， $N - 1$ 条边，求只与 $1$ 个点连通的点的数量。

# 思路
定义一个桶数组 $a_i$，表示第 $i$ 个点连通的点的数量，一边输入一边统计，最后遍历一遍，统计答案。

### 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001]; //表示第 i 个点连通的点的数量
x,y,n,ans;
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>x>>y;
		a[x]++;
		a[y]++;
	}
   for(int i=1;i<=n;i++)
		ans+=a[i]==1;
	cout<<ans;
} 
```

---

## 作者：ruruo (赞：0)

# 题意

给定一张无向图， $N$ 个点， $N - 1$ 条边，求度为 $1$ 的点的数量。

# 分析

定义一个桶数组 $a_i$ 表示点 $i$ 的度，一边输入一边统计，最后遍历一遍即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[1005];

int main() {
    int n;
    cin >> n;
    for(int i = 1; i < n; i++){
        int kkk, sc03;
        cin >> kkk >> sc03;
        a[kkk]++;
        a[sc03]++;
    }
    int ans = 0;
    for(int i = 1; i <= 1000; i++){
        if(a[i] == 1) ans++;
    }
    cout << ans;
    return 0;
}
```


---

## 作者：TheShuMo (赞：0)

## 题目大意

已知有 $N $ 个点，$N-1 $ 条边，求度为 $1$ 的点的个数。

### 输入格式

输入一行 $N$，表示点的个数。

接下来 $N-1$ 行，每行输入两个数字 $u,v$ 表示点 $u$ 与 $v$ 之间有连边。

### 输出格式

输出一行，表示度为 $1$ 的点的个数。

## 思路

输入的同时统计点的度数，最后遍历一遍统计输出即可。

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int a[10001];
int main(){
	int n,ans=0;
	cin>>n;
	int u,v;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		a[u]++;
		a[v]++;
	}for(int i=1;i<=n;i++){
		if(a[i]==1){
			ans++;
		}
	}cout<<ans;
} 
~~~

---

