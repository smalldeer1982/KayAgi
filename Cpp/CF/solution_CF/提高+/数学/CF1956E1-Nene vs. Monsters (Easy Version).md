# Nene vs. Monsters (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the versions is the constraints on $ a_i $ . You can make hacks only if both versions of the problem are solved.

Nene is fighting with $ n $ monsters, located in a circle. These monsters are numbered from $ 1 $ to $ n $ , and the $ i $ -th ( $ 1 \le i \le n $ ) monster's current energy level is $ a_i $ .

Since the monsters are too strong, Nene decided to fight with them using the Attack Your Neighbour spell. When Nene uses this spell, the following actions happen in the following order one by one:

- The $ 1 $ -st monster attacks the $ 2 $ -nd monster;
- The $ 2 $ -nd monster attacks the $ 3 $ -rd monster;
- $ \ldots $
- The $ (n-1) $ -th monster attacks the $ n $ -th monster;
- The $ n $ -th monster attacks the $ 1 $ -st monster.

When the monster with energy level $ x $ attacks the monster with the energy level $ y $ , the energy level of the defending monster becomes $ \max(0, y-x) $ (the energy level of the attacking monster remains equal to $ x $ ).

Nene is going to use this spell $ 10^{100} $ times and deal with the monsters that will still have a non-zero energy level herself. She wants you to determine which monsters will have a non-zero energy level once she will use the described spell $ 10^{100} $ times.

## 说明/提示

In the first test case, the following actions happen during the first $ 3 $ uses of the spell in this order:

- Nene uses the Attack Your Neighbour spell for the first time;
- the $ 1 $ -st monster attacks the $ 2 $ -nd monster, after the attack the energy level of the $ 2 $ -nd monster becomes equal to $ \max(0, 5-2)=3 $ ;
- the $ 2 $ -nd monster attacks the $ 3 $ -rd monster, after the attack the energy level of the $ 3 $ -rd monster becomes equal to $ \max(0, 3-3)=0 $ ;
- the $ 3 $ -rd monster attacks the $ 1 $ -st monster, after the attack the energy level of the $ 1 $ -st monster becomes equal to $ \max(0, 2-0)=2 $ ;
- Nene uses the Attack Your Neighbour spell for the second time;
- the $ 1 $ -st monster attacks the $ 2 $ -nd monster, after the attack the energy level of the $ 2 $ -nd monster becomes equal to $ \max(0, 3-2)=1 $ ;
- the $ 2 $ -nd monster attacks the $ 3 $ -rd monster, after the attack the energy level of the $ 3 $ -rd monster becomes equal to $ \max(0, 0-1)=0 $ ;
- the $ 3 $ -rd monster attacks the $ 1 $ -st monster, after the attack the energy level of the $ 1 $ -st monster becomes equal to $ \max(0, 2-0)=2 $ ;
- Nene uses the Attack Your Neighbour spell for the third time;
- the $ 1 $ -st monster attacks the $ 2 $ -nd monster, after the attack the energy level of the $ 2 $ -nd monster becomes equal to $ \max(0, 1-2)=0 $ ;
- the $ 2 $ -nd monster attacks the $ 3 $ -rd monster, after the attack the energy level of the $ 3 $ -rd monster becomes equal to $ \max(0, 0-0)=0 $ ;
- the $ 3 $ -rd monster attacks the $ 1 $ -st monster, after the attack the energy level of the $ 1 $ -st monster becomes equal to $ \max(0, 2-0)=2 $ .

After each of the next uses of the spell, energy levels of monsters do not change. Thus, only the $ 1 $ -st monster has a non-zero energy level in the end.

In the second test case, both monsters initially have zero energy level.

## 样例 #1

### 输入

```
5
3
2 5 3
2
0 0
4
1 5 7 2
4
4 2 1 2
13
1 1 4 5 1 4 1 9 1 9 8 1 0```

### 输出

```
1
1 
0

1
1 
2
1 3 
6
1 3 6 8 10 12```

# 题解

## 作者：FFTotoro (赞：6)

考虑暴力。直接模拟是不可取的，因为会被 $\ldots,0,1,V,\ldots$ 这种数据直接卡飞（其中 $V$ 为 $a$ 的值域）。

但是观察到对于两个相邻的怪兽 $x$ 和 $y$（$x$ 为攻击方），如果 $a_x=0$，那么 $a_y$ 就永远不变；进而考虑 $y$ 的攻击对象 $z$，如果 $a_y$ 非 $0$ 且不变，那么 $z$ 必然在有限次操作内死亡。

于是考虑用这条性质减少操作——我们只需不断模拟使得序列中**不存在三个相邻的 $a_i$ 满足三者均非零**；然后根据上面的性质，如果有两个相邻且均存活的怪兽，那么攻击方必活，防守方必死。

考虑该做法的时间复杂度。使用刚才卡暴力的方法（构造许多 $a_i=1$ 且 $a_{i+1}=V$）卡这种做法，发现对于三个数，只能构造 $a_i=1$，$a_{i+1}=\sqrt{V}$，$a_{i+2}=V$ 这样的数据能使操作轮数最多，为 $\sqrt{V}$ 量级的。由于 Easy Version 里 $V$ 很小，所以时间复杂度为 $O(n\sqrt{V})$ 的做法可以通过。

注意特判 $n=2$ 的情况。

放代码（C++17）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n; cin>>n;
    vector<int> a(n),r;
    for(auto &i:a)cin>>i;
    if(n==2){
      while(a[0]&&a[1])
        a[1]=max(0,a[1]-a[0]),a[0]=max(0,a[0]-a[1]);
      if(a[1])cout<<"1\n2\n";
      else if(a[0])cout<<"1\n1\n";
      else cout<<"0\n\n";
      continue;
    } // 此时直接模拟即可
    while([&](){
      for(int i=0;i<a.size();i++)
        if(a[i]&&a[(i+1)%a.size()]&&a[(i+2)%a.size()])
          return true;
      return false;
    }()) // 判断序列是否合法
      for(int i=0;i<n;i++)
        a[(i+1)%n]=max(0,a[(i+1)%n]-a[i]);
    for(int i=0;i<n;i++)
      if(a[i]&&!a[(i+n-1)%n])r.emplace_back(i);
    cout<<r.size()<<'\n';
    for(int i:r)cout<<i+1<<' ';
    cout<<'\n';
  }
  return 0;
}
```

---

## 作者：ReTF (赞：6)

> 题意：有 $n$ 个排成一圈的人，顺时针标号，第 $i$ 个血量为 $a_i$，从 $1$ 开始顺时针转圈，第 $i$ 个把第 $i+1$ 个的血量变为 $\max\{0,a_{i+1}-a_i\}$，问有哪些人在最后血量非零。

发现这个操作后面会受到前面的直接影响，难以直接维护，考虑发现题目中的性质。

性质：在操作 $O(\sqrt{w})$ 圈后，最大的非零连通块大小 $\le 2$。其中的 $w=\max\{a_i\}$。

考虑证明。假设在某一个时刻我们有一个大小 $= 3$ 的连通块 $a_i,a_{i+1},a_{i+2}$，$\sqrt{2w}$ 次操作后 $a_{i+1}$ 至少受到 $\sqrt{2w}$ 的伤害，$a_{i+2}$ 至少受到 $w+\dfrac{\sqrt{2w}}{2}$ 的伤害，其血量变为 $0$。

所以我们暴力操作 $650$ 圈，剩下的大小为 $1$ 的非零连通块一定活到最后，大小为 $2$ 的非零连通块一定是顺时针第一个活到最后。

[E2](https://www.luogu.com.cn/article/5ip0qldu)

---

