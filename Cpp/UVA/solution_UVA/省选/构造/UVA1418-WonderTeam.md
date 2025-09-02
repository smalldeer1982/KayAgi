# WonderTeam

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4164

[PDF](https://uva.onlinejudge.org/external/14/p1418.pdf)

# 题解

## 作者：Carnival (赞：3)

### 大致思路：
首先观察到，Wonderteam 必须拥有最高的胜场数，其余两个要求对答案没什么用，在此不考虑。

之后分类讨论。

当队伍数等于 $3$ 时，显然，无论 Wonderteam 赢了几场比赛，另外几场比赛打得怎么样，排名也会为第一，因为总局数太少了。同理，可得当队伍数小于等于 $3$ 时它的最差排名皆为第一。

接下来我们考虑如何让 Wonderteam 排名最低。首先它赢一局，其余所有局（指整个联赛中的所有局）都平的策略肯定是不行的，因为这使得它在赢的那局中领先了三分，而由于平局，别的队分数不可能超过它，无论如何都是第一。当然，赢太多局也是不行的。因此让它赢两局，其余没有被它赢的队都赢它一局，其余所有局（同上）都打平，如图（图并不完整）。

![](https://cdn.luogu.com.cn/upload/image_hosting/0hkvlyrl.png)

当共有 $n$ 个队时，Wonderteam 获得 $n + 3$ 分，被 Wonderteam 打败的两个队（即图中的 A 队与 B 队）得到 $2n - 1$ 分，其余队获得 $2n$ 分。当 Wonderteam 倒数第一时，有 $2n - 1 > n + 3$，解得 $n > 4$。当 Wonderteam 没倒数但也不是第一时，此时它超过了被它打败的两个队，且有 $2n > n + 3$，解得 $n > 3$。所以，当 $n = 4$ 时，它排在第二，$n > 4$ 时它是倒数第一。

注意点：本题多测，且输入以 $0$ 结束。

### 代码：
```cpp
#include<bits/stdc++.h>
using  namespace  std;
int n;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
//	system("color 06");
	for(cin>>n; n; cin>>n) {//多组测试数据
		if(n<4)cout<<"1\n";
		else if(n==4)cout<<"2\n";
		else cout<<n<<'\n';
	}
	return 0;
}

---

## 作者：ncwzdlsd (赞：2)

一道巧妙的构造题。

对于题目中的 WonderTeam，因为要求是胜利场数最多的队，所以当 $n=2$ 时输出 $1$，当 $n=3$ 时，也输出 $1$，因为不能让别的球队胜利场数超过 WonderTeam，这两种情况下的最低排名都是 $1$。

当 $n>3$ 时，我们开始考虑如何让 WonderTeam 排名最低：

假设我们让 WonderTeam 赢 $1$ 局，其他比赛全部战平，那么显然别的队伍不能赶上由于 WonderTeam 的一场胜利带来的多出的 $2$ 分。

再考虑让 WonderTeam 赢两局，剩下的场次全输（即让每一个队都赢它一次），然后再让剩下的场次都平局。那么 WonderTeam 的得分为 $n+3$（$n-3$ 的平分，$6$ 分的胜利分）；被 WonderTeam 打败过的两支队伍得分为 $2n-1$ 分，剩下的队伍得分为 $2n$。考虑 $2n-1$ 和 $n+3$ 的大小关系可知，$n=4$ 时 WonderTeam 是第二，$n>4$ 时 WonderTeam 是倒数第一。
(注意这里每个队要打两场）

可以用一个表格直观地展示一下此时 WonderTeam（$a$）、WonderTeam 赢的两支队伍（$b$）、其他队伍（$c$）的胜负情况：

|  | 胜 | 败 | 平 | 得分 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $a$ | $2$ | $n-1$ | $n-3$ | $n+3$ |
| $b$ | $1$ | $1$ | $2n-4$ | $2n-1$ |
| $c$ | $1$ | $0$ | $2n-3$ | $2n$ |

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	while(cin>>n&&n)
	{
		if(n==1||n==2||n==3) cout<<1<<endl;
		else if(n==4) cout<<2<<endl;
		else cout<<n<<endl;
	}
	return 0;
}
```

---

## 作者：Siteyava_145 (赞：0)

构造题。。。

注：这是循环赛，每两队之间打两场。

$n=1$，输出 $1$。（~~自己和自己踢不可能吧~~）

$n=2$，因为 `WonderTeam` 要求胜场最多，所以只能胜利，输出 $1$.

$n=3$，同上，`WonderTeam` 至少胜一场，其他人只能打平（不能胜场超过 `WonderTeam`），输出 $1$。

$n\ge 4$ 时，情况不一定，（剩余队伍内部可能打平，得分变多，甚至超过 `WonderTeam`）。

这时我们开始构造。

1. `WonderTeam` 赢 $1$ 局。

这时其他队伍内部不能出现战胜（战败），只能互平。对 `Wonderteam` 不能胜（败也不行，那样使 `Wonderteam` 分变高，不符合构造条件），只能平。
但这时 `Wonderteam` 就比其他队伍多 $2-3$ 分，所以仍是第一。所以舍掉这种方案。

---

2. `Wonderteam` 赢 $2$ 局。

其他队伍都可以赢一局，最佳方案是 `Wonderteam` 只赢 $2$ 队，其他全输，其他队伍互平。

![](https://cdn.luogu.com.cn/upload/image_hosting/psibnrz4.png?x-oss-process=image/resize,m_lfit,h_370,w_575)

(图不好请见谅）（黄线为平，A->B 表示 A 战胜 B）

这时 `Wonderteam` 得分为 $n+3$（平有 $n-3$ 分，胜有 $6$ 分），与 `Wonderteam` 各胜一局的 $2$ 支队伍有 $2(n-2)+3=2n-1$ 分，其余队均有 $2(n-2)+1+3=2n$ 分。

当 $n=4$，`Wonderteam` 得 $7$ 分，被 `Wonderteam` 胜的 $2$ 支队伍也得 $7$ 分，所以这时 `Wonderteam` 排第二。其余情况下保证 $2n-1>n+3$，`Wonderteam` 为倒数第一。

---

3. `Wonderteam` 赢 $3$ 局

`Wonderteam` 得分 $n+5$。

被 `Wonderteam` 胜的 $3$ 支队伍得分 $2n-1$.

其余队得分 $2n$。

这时 $n>6$ 才能保证 `Wonderteam` 倒数第一，不如前一种情况。赢的场次更多也一样。

所以综上：$n<4$ 时 `Wonderteam` 最差第一，$n=4$ 时 `Wonderteam` 最差第二，$n>4$ 时 `Wonderteam` 最差倒数第一。

代码就不贴了。

---

## 作者：封禁用户 (赞：0)

## 广告
个人博客同步： http://www.cinema000.xyz/1462.ruby 
## 分析
这里的解直接就是构造出来的。
显然当n小于等于3时，梦之队只能当第一；
显然当n等于4时，梦之队最低可以是第二；
然后再来构造一个赢得次数最多，但分数很低的情况，就让梦之队赢2局，其他队都赢一局，这样梦之队有n + 3分，输的队有2n - 1分，其他队有2n分，列个不等式就有n大于等于5直接输出n就好了。
## 代码
```cpp
//
//  main.cpp
//  UVa 1418
//
//  Created by Louis Cinema on 2018/8/1.
//  Copyright © 2018年 Cinema Media Group. All rights reserved.
//

#include <cstdio>

int main(int argc, const char * argv[]) {
    int n;
    while (scanf("%d",&n) == 1 && n) {
        if(n <= 3) puts("1");
        else if(n == 4) puts("2");
        else printf("%d\n",n);
    }
    
    return 0;
}

```

---

