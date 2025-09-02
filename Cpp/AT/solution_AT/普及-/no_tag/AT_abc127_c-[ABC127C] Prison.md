# [ABC127C] Prison

## 题目描述

我们现在有 $N$ 张ID卡，有 $M$ 道门。

我们有第 $L_i$张、第 $L_i+1$张、…第 $R_i$张ID卡中的一张的时候，我们可以通过第 $i$ 道门。

总共有几张卡符合“只用一张卡就能通过全部门”？

~~好乱~~

## 说明/提示

- 所有输入都是整数
- $1\le N\le 10^5$
- $1\le M\le 10^5$
- $1\le L_i\le R_i\le N$

## 样例解释

### 样例1、样例4（相同的两个样例）

有2张ID卡满足“只用一张卡就能通过全部门”，如下：

- 第1张ID卡不能让我们通过第2道门
- 第2张ID卡能让我们通过所有的门
- 第3张ID卡能让我们通过所有的门
- 第4张ID卡不能让我们通过第1道门

所以总共满足“只用一张卡就能通过全部门”的ID卡数量为2张（第2、3张）

~~还是好乱orz~~

## 样例 #1

### 输入

```
4 2
1 3
2 4```

### 输出

```
2```

## 样例 #2

### 输入

```
10 3
3 6
5 7
6 9```

### 输出

```
1```

## 样例 #3

### 输入

```
100000 1
1 100000```

### 输出

```
100000```

# 题解

## 作者：Take_A_Single_6 (赞：4)

**哇，好水！（伦敦雾**  
这道题模拟一下就可以了，具体代码解释。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
//压行是陋习！
    int n,m,l,r,ansl=0,ansr=214748364;//初值保证l,r不越界即可。
    cin>>n>>m;
    int a[n+1];//可以开大，习惯而已。
    memset(a,0,sizeof a);
    for(int i=0;i<m;i++)
    {
    	cin>>l>>r;
    	if(l>ansl)//左右两个值，固定范围，根据每一次l,r变化。
    	ansl=l;
    	if(r<ansr)
    	ansr=r;
    }
    if(ansr>=ansl)
    cout<<ansr-ansl+1<<endl;//+1是重点，闭区间！！！
    else 
    cout<<0<<endl;//避免负数。
    //十年AT一场空，不加换行见祖宗！
    return 0;
}
```

---

## 作者：_Andy_Lin_ (赞：1)

树状数组裸题。

------------
我一开始的思路是：第$i$次，暴力将$l_i$到$r_i$加上$1$（这些ID卡可通过这扇门）。最后再看每一张ID卡，是否$m$条门都打得开。但这很明显会T飞。

------------
进一步分析，发现这是一个区间修改，单点查询的数列。直接用差分的树状数组即可。（不会的可以做一下[P3368](https://www.luogu.com.cn/problem/P3368)）

------------
然后就轻松AC啦！

------------
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,tree[100001],ans;
inline int lowbit(int x){
    return x&(-x);
}
inline void add(int x,int y){
    for(;x<=n;x+=lowbit(x))tree[x]+=y;
}
inline int ask(int x){
    int ans=0;
    for(;x;x-=lowbit(x))ans+=tree[x];
    return ans;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i){
        int l,r;
        scanf("%d%d",&l,&r);
        add(l,1),add(r+1,-1);
    }
    for(int i=1;i<=n;i++){
        if(ask(i)==m)ans++;
    }
    printf("%d\n",ans);
    return 0;
}
```
----------------
时间复杂度：$O((n+m)\log n)$，是可以接受的。

---

