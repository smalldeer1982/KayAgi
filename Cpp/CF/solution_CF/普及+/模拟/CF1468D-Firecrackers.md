# Firecrackers

## 题目描述

Consider a long corridor which can be divided into $ n $ square cells of size $ 1 \times 1 $ . These cells are numbered from $ 1 $ to $ n $ from left to right.

There are two people in this corridor, a hooligan and a security guard. Initially, the hooligan is in the $ a $ -th cell, the guard is in the $ b $ -th cell ( $ a \ne b $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1468D/09bf6496fc483fb53942bc6e21c9eb76729eb3aa.png)One of the possible situations. The corridor consists of $ 7 $ cells, the hooligan is in the $ 3 $ -rd cell, the guard is in the $ 6 $ -th ( $ n = 7 $ , $ a = 3 $ , $ b = 6 $ ).There are $ m $ firecrackers in the hooligan's pocket, the $ i $ -th firecracker explodes in $ s_i $ seconds after being lit.

The following events happen each second (sequentially, exactly in the following order):

1. firstly, the hooligan either moves into an adjacent cell (from the cell $ i $ , he can move to the cell $ (i + 1) $ or to the cell $ (i - 1) $ , and he cannot leave the corridor) or stays in the cell he is currently. If the hooligan doesn't move, he can light one of his firecrackers and drop it. The hooligan can't move into the cell where the guard is;
2. secondly, some firecrackers that were already dropped may explode. Formally, if the firecracker $ j $ is dropped on the $ T $ -th second, then it will explode on the $ (T + s_j) $ -th second (for example, if a firecracker with $ s_j = 2 $ is dropped on the $ 4 $ -th second, it explodes on the $ 6 $ -th second);
3. finally, the guard moves one cell closer to the hooligan. If the guard moves to the cell where the hooligan is, the hooligan is caught.

Obviously, the hooligan will be caught sooner or later, since the corridor is finite. His goal is to see the maximum number of firecrackers explode before he is caught; that is, he will act in order to maximize the number of firecrackers that explodes before he is caught.

Your task is to calculate the number of such firecrackers, if the hooligan acts optimally.

## 说明/提示

In the first test case, the hooligan should act, for example, as follows:

- second 1: drop the second firecracker, so it will explode on the $ 5 $ -th second. The guard moves to the cell $ 5 $ ;
- second 2: move to the cell $ 2 $ . The guard moves to the cell $ 4 $ ;
- second 3: drop the first firecracker, so it will explode on the $ 4 $ -th second. The guard moves to the cell $ 3 $ ;
- second 4: move to the cell $ 1 $ . The first firecracker explodes. The guard moves to the cell $ 2 $ ;
- second 5: stay in the cell $ 1 $ . The second firecracker explodes. The guard moves to the cell $ 1 $ and catches the hooligan.

## 样例 #1

### 输入

```
3
7 2 3 6
1 4
7 2 3 6
5 1
7 2 3 6
4 4```

### 输出

```
2
1
1```

# 题解

## 作者：ForwardStar (赞：3)

提供一种二分答案的写法。  
关于 $\texttt{check}$ 时的一些事项：  
+ 一定不会向警察的方向跑，这样肯定会加速被抓。
+ 警察和你速度一样，你逃跑的目的只是拖延时间让鞭炮炸掉。
+ 扔鞭炮和逃跑的顺序无所谓，你逃跑与警察相对位置不变。  

先扔够枚举的鞭炮数，先扔时间长的，如果鞭炮没扔完就被抓了代表答案不可行。然后逃跑拖延时间，一直逃到边缘。如果拖延的时间比最后炸的那个鞭炮长（或相等），则答案可行，否则不可行。  
时间复杂度 $O(m\log m)$。  
附上代码：
```cpp
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <cstdio>
using namespace std;
const int N=2e5+3,inf=2147483647;
int T,n,m,x,y,dis,ddis;
int a[N];
bool check(int p){
	if(p>=dis)return false;
	int mx=0;
	for(int i=1;i<=p;i++){
		mx=max(mx,a[i]+p-i+1);
	}
	return mx<=ddis;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d%d",&n,&m,&x,&y);
		for(int i=1;i<=m;i++)scanf("%d",&a[i]);
		sort(a+1,a+1+m);
		int l=0,r=m;
		dis=abs(x-y);
		if(x>y)ddis=dis+n-x;
		else ddis=dis+x-1;
		while(l<r){
			int mid=(l+r+1)/2;
			if(check(mid))l=mid;
			else r=mid-1;
		}
		printf("%d\n",l);
	}
	return 0;
}
```


---

## 作者：Fa1thful (赞：2)

### 题意：
有一个警察和一个放鞭炮的人，放鞭炮的人可以向左或右移动1格，也可以选择放一个鞭炮，鞭炮爆炸需要时间，而警察只能左走1格，问警察抓住他的时候最多能有多少个鞭炮炸掉。

### 思路：
这道题首先上来看到数据范围  
$ 1\le m\le2*10^5$

显然这是一个$O(nlog_2n)$的算法，所以很容易想到了贪心。
我们可以先制定一个贪心策略，就是先把所有的鞭炮都放了，然后再跑路。
可以看到这个策略是不太对的，因为有一种情况就是还没放完所有的鞭炮警察就追了上来。
所以可以改成尽可能多地放鞭炮，然后跑路为鞭炮爆炸争取时间。

那么为什么这样是正确的呢？我们可以来手推一下第一个样例

如果先跑路，再放鞭炮就是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/7nvdqu7p.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果先放鞭炮，再跑路，就是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/ovhpxvr1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

而且先放鞭炮在逻辑上也讲得通，因为提前放鞭炮之后可以边跑边等着鞭炮爆炸。

但是还有个要注意的地方：鞭炮一定要按照爆炸时间从高到低排序，因为爆炸时间长的鞭炮先放就可以先等待爆炸时间。

### 代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
int bianpao[1000000];
bool cmp(int x, int y)
{
    return x > y;                  //cmp从大到小给鞭炮爆炸时间排序 
}
int main()
{
    int a, b;
    int T;
    cin >> T;
    while (T--)
    {
        int ans = 0;
        int n, m;
        int bianpaoshu = 0, tuoyanshijian = 0;                //tuoyanshijian表示能为鞭炮爆炸争取多长的时间 
        cin >> n >> m >> a >> b;
        for (int i = 1; i <= m; i++)
        {
            cin >> bianpao[i];
        }
        sort(bianpao + 1, bianpao + 1 + m, cmp);              //cmp从大到小给鞭炮爆炸时间排序 
        bianpaoshu = abs(a - b) - 1;                          //能在b追上a前放的鞭炮数 
        if (a < b) tuoyanshijian = b - 2;
        if (a > b) tuoyanshijian = n - b - 1;
        for (int i = 1; i <= m; i++)
        {
            if (bianpaoshu <= 0) break;                      //如果一个也放不了 
            if (bianpao[i] <= tuoyanshijian)                //可以引爆 
            {
                bianpaoshu--;                                //还在等待的鞭炮数-- 
                ans++;                                      //爆炸计数++ 
                tuoyanshijian--;                            //还能再拖延的时间-- 
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

感谢观赏

---

## 作者：Chenyichen0420 (赞：0)

## 题目大意

给你一个活动区间 $[1,n]$，告诉你 $A$ 的位置 $a$ 和 $B$ 的位置 $b$，告诉你 $A$ 有 $m$ 个鞭炮，每个鞭炮会在点燃后 $t_i$ 的时间内爆炸。现在由你来操控 $A$ ，每次可以让他向左或者向右移动一个单位（如果移动完了仍然在 $[1,n]$ 的区间范围内），或者任选一个鞭炮点燃。而 $B$ 每秒会向 $A$ 移动一个单位长度。请问最多能有几个鞭炮可以在 $A$ 被 $B$ 抓住前爆炸。

# 思路分析

作为一个~~训练有素的~~ OIer， 题中 $m$ 的数据范围能迅速地引起我们的警觉，得知时间复杂度应该是 $O(m\log{m})$。然而，我的代码复杂度可能会更优。

我们先想一下直接贪心行不行呢？

显然不行。如果你贪鞭炮数量，肯定会先放时间更短的，然而同等情况下先放燃烧时间更长的更容易爆炸的更多。所以，这道题具有单调性，可以用二分解决，属于 $O(m\log{m})$。

但是本人的解法略为更优。我们可以预处理出每一个鞭炮到最后一个鞭炮开始燃放的爆炸的时间，并同时取出其所需等待时间，和预处理好的最大等待时间对比。排除掉排序，时间复杂度为 $O(m+\log{m})$，略优于 $O(m\log{m})$。

下面附上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a,b,f[200005],l,r,mid,mx[200005],rat;
signed main(){
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
    	cin>>n>>m>>a>>b;
    	for(int i=1;i<=m;++i) cin>>f[i];
    	sort(f+1,f+m+1); rat=(a<b?b:n-b+1);
    	for(int i=1;i<=m;++i) mx[i]=max(mx[i-1],f[i]-i+1);
    	l=0,r=min(m,abs(b-a)-1);
    	while(l<r){
    		mid=l+r+1>>1;
    		if(mx[mid]<rat-mid) l=mid;
    		else r=mid-1;
		}
		cout<<l<<endl;
	}
	return 0;
}
```

---

