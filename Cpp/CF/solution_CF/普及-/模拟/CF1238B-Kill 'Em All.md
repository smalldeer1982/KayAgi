# Kill 'Em All

## 题目描述

Ivan plays an old action game called Heretic. He's stuck on one of the final levels of this game, so he needs some help with killing the monsters.

The main part of the level is a large corridor (so large and narrow that it can be represented as an infinite coordinate line). The corridor is divided into two parts; let's assume that the point $ x = 0 $ is where these parts meet.

The right part of the corridor is filled with $ n $ monsters — for each monster, its initial coordinate $ x_i $ is given (and since all monsters are in the right part, every $ x_i $ is positive).

The left part of the corridor is filled with crusher traps. If some monster enters the left part of the corridor or the origin (so, its current coordinate becomes less than or equal to $ 0 $ ), it gets instantly killed by a trap.

The main weapon Ivan uses to kill the monsters is the Phoenix Rod. It can launch a missile that explodes upon impact, obliterating every monster caught in the explosion and throwing all other monsters away from the epicenter. Formally, suppose that Ivan launches a missile so that it explodes in the point $ c $ . Then every monster is either killed by explosion or pushed away. Let some monster's current coordinate be $ y $ , then:

- if $ c = y $ , then the monster is killed;
- if $ y < c $ , then the monster is pushed $ r $ units to the left, so its current coordinate becomes $ y - r $ ;
- if $ y > c $ , then the monster is pushed $ r $ units to the right, so its current coordinate becomes $ y + r $ .

Ivan is going to kill the monsters as follows: choose some integer point $ d $ and launch a missile into that point, then wait until it explodes and all the monsters which are pushed to the left part of the corridor are killed by crusher traps, then, if at least one monster is still alive, choose another integer point (probably the one that was already used) and launch a missile there, and so on.

What is the minimum number of missiles Ivan has to launch in order to kill all of the monsters? You may assume that every time Ivan fires the Phoenix Rod, he chooses the impact point optimally.

You have to answer $ q $ independent queries.

## 说明/提示

In the first test case, Ivan acts as follows:

- choose the point $ 3 $ , the first monster dies from a crusher trap at the point $ -1 $ , the second monster dies from the explosion, the third monster is pushed to the point $ 7 $ ;
- choose the point $ 7 $ , the third monster dies from the explosion.

In the second test case, Ivan acts as follows:

- choose the point $ 5 $ , the first and fourth monsters die from the explosion, the second monster is pushed to the point $ 1 $ , the third monster is pushed to the point $ 2 $ ;
- choose the point $ 2 $ , the first monster dies from a crusher trap at the point $ 0 $ , the second monster dies from the explosion.

## 样例 #1

### 输入

```
2
3 2
1 3 5
4 1
5 2 3 5
```

### 输出

```
2
2
```

# 题解

## 作者：微香玉烛暗 (赞：5)

$update$ $on$ $:2019.10.14$     
修改内容:代码部分（其实看到有人在评论区骂我说连样例都过不掉，我想反问一句：那你为何要抄题解呢？）   
好心的我还是把正确代码放回来了，希望有助大家参考。

这题其实是个裸的贪心。       
那么如何贪心呢？思路很简单。    
题目已经告诉我们，怪物被打到0的左端，就会自爆，那么我们就一定会向怪物右边开炮，否则怪物就会离0端越来越远。

思路已经清晰，下面谈谈实现。     
把怪物按照坐标位置排序，从大到小枚举，每次炮轰坐标最大的怪物，这样不仅能够轰死它本身，还能够将它左边所有怪物再向左推进。枚举到枚举到每一个怪物时，只需判断它是否已经死在0左边，若没有，就耗一炮轰它，$ans++$；否则退出循环，因为如果该怪被轰到左边，坐标比它小的所有怪物一定都已经挂了，即结束。

代码：

```cpp
# include <cstdio>
# include <queue>
# include <iostream>
# include <algorithm>
using namespace std;
const int N=100005;
int t,n,m,ans,now,num,a[N];

bool cmp (int x,int y) {
	return x>y;
}

int main () {
	scanf ("%d",&t);
	while (t--) {
		ans=num=0; now=-1e9;
		scanf ("%d%d",&n,&m);
		for (int i=1;i<=n;i++) {
			scanf ("%d",&a[i]);
		}
		sort (a+1,a+1+n);
		for (int i=n;i>=1;i--) {
			if(a[i]==now) continue;
			if(a[i]-num<=0) break;
			ans++; num+=m; now=a[i];
		}
		printf("%d\n",ans);
	}
	return 0;
}
//By苍空的蓝耀 
//By苍空的蓝耀
```


---

## 作者：_segmenttree (赞：0)

### 思路

为了发射炮弹数量尽量小应该要使每次伤害尽量大。

为此，我们每次应该选择目前坐标最大的数。如果选择比它小的那么就会减少

炮弹打击到的数量，那么一定不会比选择坐标最大的更优

#### 注意

如果有坐标重复的不用再次计算

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,r,a[100010],jl,num,ans;
int main() {
	cin>>t;
	while(t--) {
		scanf("%d%d",&n,&r);
		for(int i=1; i<=n; i++)
			scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		jl=-1,num=0,ans=0;
		for(int i=n; i>=1; i--) {
			if(a[i]==jl) continue ;
			if(a[i]-num<=0) break ;
			ans++;
			num+=r;
			jl=a[i];
		}
		cout<<ans<<"\n";
	}
	return 0;
}

```

---

## 作者：清清老大 (赞：0)

## 思路

本题可以通过贪心做。为了使尽可能多的怪物到原点左边，每次在离原点最远的怪物上开炮。

由于两个在同一处的怪物没有区别，所以排序后去重。排序后，从大往小开始模拟，如果有一个怪物在被打到之前就到原点左边，那么剩下的怪物也都在原点左边，此时输出已经开过的炮数，如果到最后都没有到原点的怪物，就输出怪物的数量。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int q;
    cin >> q;
    while(q --)
    {
        int n,r,x[120323];
        bool flag = false;
        cin >> n >> r;
        for(int i = 0;i < n;i ++)
        {
            cin >> x[i];
        }
        sort(x,x + n,greater<int>());
        n = unique(x,x + n) - x;
        for(int i = 0;i < n;i ++)
        {
            if(x[i] - i * r <= 0)
            {
                cout << i << endl;
                flag = true;
                break;
            }
        }
        if(flag)
        {
            continue;
        }
        cout << n << endl;
    }
}
```


---

## 作者：FJ·不觉·莫笑 (赞：0)

### **贪心可过！**  


------------
### **读题：**  
  一个水平的坐标轴，怪兽都在原点右边，若使得怪物到达原点右边，则怪兽死亡。

当在c点发射导弹，则：
 1. $y=c$：怪兽死亡
 2. $y<c$：怪兽向左移动r个单位，坐标变为 $y -r$
 3. $y>c$：怪兽向右移动r个单位，坐标为$y+r$  
为了杀死怪兽，至少要发射多少导弹。  


------------
### **思路：**  
  **贪心**,因为怪物被打到0的左端，就会KO，所以我们每一炮都要轰到怪物的右边。  完整思路如下：   
   把怪物按照坐标位置从大到小排序，每次炮轰坐标最大的怪物。循环到每一个怪物时，只需判断它是否已经死在0左边，若没有，就再打它一炮，计数器加一；否则退出循环，因为如果该怪被轰到左边，坐标比它小的所有怪物一定都已经KO了，结束。  


------------
### **上代码：**  
```cpp
# include<bits/stdc++.h>
using namespace std;
int a[100000];
int main () {
	int t,n,m,ans=0,now=-99999,num=0;
	cin>>t;
	for(int i=1; i<=t; i++) {
		ans=0;
		num=0;
		now=-999999;
		cin>>n>>m;
		for (int j=1; j<=n; j++)
			cin>>a[j];
		sort (a+1,a+1+n);
		for (int j=n; j>=1; j--) {
			if(a[j]==now)
				continue;
			if(a[j]-num<=0)
				break;
			ans++;
			num+=m;
			now=a[j];
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：HoshizoraZ (赞：0)

**题意**

数轴正半轴上有 $n$ 个点，现在有一个炮，它每发射一次就可以让其中一个位置上的所有点消灭，同时把所有这个位置左边的点坐标减少 $r$，右边的点坐标增加 $r.$

如果某个点移动到负半轴或原点，那么它也会消灭。

问：炮最少要发射多少次才可以消灭所有的点？

**分析**

我们发现，如果有多个位置的点在同一个位置，那么它们无论大炮怎么发射，这些点都只在一个位置上，直至消灭。

所以，相同坐标的点我们只看作一个点（即去重）；

在此基础上，可以得出每一炮**直接**消灭的点数最多为 $1.$

因此，我们要最大化坐标变成非正数的点的个数。

**解决方式**

不难看出，把数轴上最右边的点移动到非正数区域需要发射最多的炮。

对于此情况，最优的选择肯定是直接炮轰消灭，并让其它所有点左移；

之后，找到当前数轴最右边的点，重复上述操作；

最后，若剩下的最右边的点在负半轴或原点上，那么代表所有点都消灭了，停止发射。

至此，我们已经得到了贪心策略：

**每次让当前剩余点中最右处的直接消灭，直到剩下的点坐标均非正。**

而判断一个点现在在负半轴或原点上，只需推断出

$$\text{点的初始坐标}-r*\text{已经炮轰次数} ≤ 0.$$

通过如上方式，就可以得出最优的答案了。

---

## 作者：zgy_123 (赞：0)

很简单的模拟 + 贪心。

首先，显然对于最右边的怪兽，直接打它是最优的选择，我们的代码就是建立在这个基础上的。

代码的思路：首先排序，每次枚举最后一个怪物，将与他坐标相同的全都删除，然后将剩余所有怪物的坐标都减 $r$。但是这样明显是 $O(qn^2)$ 的。这时候，只需要将这个操作等价于将原点右移 $r$ 个单位，相应的，每次选取最后一个怪物是要判断是否已经被打死了，如果是就直接跳出。

时间复杂度 $O(nq)$，能过是因为翻译少了一句 `It is guaranteed that sum of all $ n $ over all queries does not exceed $ 10^5 $ .`。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
bool b[100005];
int main(){
	int T,n,r;
	cin>>T;
	while(T--){
		memset(b,0,sizeof(b));
		cin>>n>>r;
		for(int i=1;i<=n;i++) cin>>a[i];
		int t=0;//t代表原点移动了几个单位
		sort(a+1,a+n+1);
		while(1){
			int x=a[n];
			if(x<=t) break;//已经被打死了
			while(a[n]==x) n--;//删除打死的怪物
			t+=r;
		}
		cout<<t/r<<endl;//就是打了多少次
	}
	return 0;
}

```

---

