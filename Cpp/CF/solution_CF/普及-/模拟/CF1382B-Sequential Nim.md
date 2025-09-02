# Sequential Nim

## 题目描述

There are $ n $ piles of stones, where the $ i $ -th pile has $ a_i $ stones. Two people play a game, where they take alternating turns removing stones.

In a move, a player may remove a positive number of stones from the first non-empty pile (the pile with the minimal index, that has at least one stone). The first player who cannot make a move (because all piles are empty) loses the game. If both players play optimally, determine the winner of the game.

## 说明/提示

In the first test case, the first player will win the game. His winning strategy is:

1. The first player should take the stones from the first pile. He will take $ 1 $ stone. The numbers of stones in piles will be $ [1, 5, 4] $ .
2. The second player should take the stones from the first pile. He will take $ 1 $ stone because he can't take any other number of stones. The numbers of stones in piles will be $ [0,         5, 4] $ .
3. The first player should take the stones from the second pile because the first pile is empty. He will take $ 4 $ stones. The numbers of stones in piles will be $ [0, 1, 4] $ .
4. The second player should take the stones from the second pile because the first pile is empty. He will take $ 1 $ stone because he can't take any other number of stones. The numbers of stones in piles will be $ [0, 0, 4] $ .
5. The first player should take the stones from the third pile because the first and second piles are empty. He will take $ 4 $ stones. The numbers of stones in piles will be $ [0, 0,         0] $ .
6. The second player will lose the game because all piles will be empty.

## 样例 #1

### 输入

```
7
3
2 5 4
8
1 1 1 1 1 1 1 1
6
1 2 3 4 5 6
6
1 1 2 1 2 2
1
1000000000
5
1 2 2 1 1
3
1 1 1```

### 输出

```
First
Second
Second
First
First
Second
First```

# 题解

## 作者：Rainy7 (赞：20)

- 分析

  我们可以发现对于**若干堆（第一堆数量大于 $1$ ）**，有这么一个贪心的取法：
  
  比如第一堆堆数量为 $n(n>1)$ 。**先手先取 $n-1$ 个。这样后手只能取 $1$ 个（无法不取）。**
  
  这样，先手就可以**先取第二堆**。
  
  后几堆的取法同上，直到先手可以先取最后一堆。
  
  **对于最后一堆，先手直接取完**。获胜。
  
  那如果**中间有一堆数量为 $1$ ，** 那么对于这一堆的前一堆，**直接全部取完**，后手只能取完这堆数量为 $1$ 的堆。**照样可以获得下一堆的先手**。
  
  以此类推。我们可以发现，影响最后结果的，**只有前缀 $1$ 的数量。**
  
  容易发现，如果**前缀 $1$ 数量为偶数个**，在轮流取完后，那么第一个非 $1$ 堆，是**先手**先取。即先手会胜利。
  
  如果是**奇数**个，那么第一个非 $1$ 堆，是**后手**先取。即后手会胜利。
  
  特殊的，如果这堆**只有 $1$ 。**那么**偶数**个胜利的为**后手**，**奇数**个胜利的为**先手**。
  
  

------------

  
- 代码

  ```
  #include<iostream>
  #include<cstdio>
  #include<cstring>
  using namespace std;
  const int Maxn=1e5+5;
  int T,n,a[Maxn];
  int main()
  {	
      scanf("%d",&T);
      while(T--)
      {	
          int cnt=0,i;
          scanf("%d",&n);
          for(i=1;i<=n;i++)
              scanf("%d",&a[i]);
          for(i=1;i<=n;i++)
              if(a[i]==1)cnt++;
              else break;
          if(i==n+1)
          {	
              if(cnt%2==0)printf("Second\n");
              else printf("First\n");
          }
          else{
              if(cnt%2==0)printf("First\n");
              else printf("Second\n");
          }
      }
      return 0;
  }
  ```

---

## 作者：chen_03 (赞：9)

~~SG 函数大法好！！！~~

我们设 $sg_{i,j}$ 为“前 $i-1$ 堆石子都已被取完，第 $i$ 堆石子还剩 $j$ 个没取”这个状态的 SG 函数值。这个状态的所有后继状态即为“前 $i-1$ 堆石子都已被取完，第 $i$ 堆石子还剩 $0,1,2,\dots,j-1$ 个石子没取”的状态，所以 $sg_{i,j}=\operatorname{mex}\{sg_{i,0},sg_{i,1},sg_{i,2},\dots,sg_{i,j-1}\}$。

如果直接这样做是过不了的，我们考虑优化。

显然 $sg_{n,j}=j$。对于 $1\le i<n$，由于 $sg_{i,0}$ 和 $sg_{i+1,a_{i+1}}$ 对应的是同一个状态，所以 $sg_{i,0}=sg_{i+1,a_{i+1}}$。

我们来看 $sg_{i,0}=sg_{i+1,a_{i+1}}=3,a_i=6$ 的情况。$sg_{i,0},sg_{i,1},sg_{i,2},\dots,sg_{i,a_i}$ 的值分别为：

$$3,0,1,2,4,5,6$$

可以发现，若 $a_i\le sg_{i+1,a_{i+1}}$，则 $sg_{i,a_i}=a_i-1$（因为 $a_i\ne 0$），否则 $sg_{i,a_i}=a_i$。

于是我们可以把 $j$ 这一维去掉，只保留第 $i$ 堆石子还剩 $a_i$ 个没取（即还没开始取）的情况，然后以 $sg_n=a_n$ 为初值，从后往前递推一遍即可。最后要看 $sg_1$ 是否等于 $0$。

时间复杂度 $\mathcal{O}(\sum n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int T,n,a[100005],sg[100005];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
			scanf("%d",a+i);
		sg[n]=a[n];
		for(int i=n-1;i;--i)
			sg[i]=a[i]<=sg[i+1]?a[i]-1:a[i];
		printf(sg[1]?"First\n":"Second\n");
	}
	return 0;
}
```

---

## 作者：gaozitao1 (赞：2)

**题目大意**：有 $n$ 堆石子，两个人轮流取石子，每个人可以取序号最小的堆的任意个石子，谁没有石子可以取，谁就输了。

这个题目刚看时没有什么思路，可以从样例入手分析。

看完样例之后，可以发现，有些样例有 $1$，有些样例全是 $1$，有些样例没有 $1$。

这可以给我们启发：**本题的关键就是只有 $1$ 个石子的堆**。

**首先，如果每一堆都只有 $1$ 个石子，那么每个人每次都只能取一个，所以如果有奇数堆，那么先手赢。如果有偶数堆，那么后手赢。**

**其次，如果没有只有 $1$ 个石子的堆，那么先手一定赢。**

分析：假如有一堆有 $a$ 个石子，那么先手可以拿 $a-1$ 个，那么后手就只能拿 $1$ 个。下一堆依然是先手拿。

这样，先手一直这么拿，拿到只剩一堆时，把最后一堆全部拿走就可以获胜。

**然后，在分析开头没有只有 $1$ 个石子的堆的情况。这样依然是先手必胜。**

假设有 $10$ 个堆，每个堆的石子数为 $a,b,c,1,1,1,1,d,e,f$。

那么，先手想要赢，就和上一种情况一样，使自己先拿到 $d$ 堆石子即可。

所以，只要控制 $d$ 堆前面 $1$ 的个数，使 $d$ 前面有奇数个 $1$ 即可。

如果 $d$ 堆前面本来就有奇数个 $1$，那么就用第二种情况的方法拿到 $1$ 前面的那一堆石子。

如果 $d$ 堆前面有偶数个 $1$，那么就用第二种方法，使 $1$ 前面的那一堆只剩 $1$ 个石子，那么就相当于有奇数个 $1$ 了。

**最后，分析开头有 $1$ 的情况。**

假设有 $10$ 个堆，每个堆的石子数为 $1,1,1,a,b,c,d,1,1,1$。

通过上一种情况的分析，可以得出：先拿到第 $a$ 堆的必胜。

也就是，先拿到非 $1$ 的堆的人必胜。

所以，如果第一个非 $1$ 的堆前有奇数个堆，那么后手必胜；否则，先手必胜。

将上面的四种情况结合一下，就可以发现本题的正解：

**如果所有的堆都只有 $1$ 个石子，那么输赢与堆数有关；**

**否则，输赢与前缀 $1$ 的个数有关。**

之后，就可以写出代码了。

**代码：**
```cpp
#include<cstdio>
#include<iostream>
const int N=100000;
int a[N+1];
int main()
{
	register int i,n,t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(i=1; i<=n; ++i)
			scanf("%d",&a[i]);
		for(i=1; i<=n; ++i)
			if(a[i]!=1)
				break;//找到第一个不是1的位置
		--i;//前缀1的个数是i-1
		if(i<n)//如果不是全是1，输赢与前缀1的个数有关
			if(i%2)
				puts("Second");
			else
				puts("First");
		else//如果全是1，输赢与堆数有关
			if(n%2)
				puts("First");
			else
				puts("Second");
	}
	return 0;
}
```

---

## 作者：LRL65 (赞：2)

这题我在比赛中想了15分钟（wtcl），~~然后竟然一遍a了~~。

本题解有一些例子，已经懂了的同学~~或者懒得看~~的同学可以跳过，直接看推导。

### 一、关于取法

讲讲思路，当你做这种题时无从下手时，我们应该先看看**样例和它的样例说明**(因为只给了第一个测试点的说明，所以只看样例中的第一个）：

样例：

3

2 5 4

说明（已翻译成中文）：
>在第一个测试案例中，第一个玩家将赢得比赛。他的制胜策略是：

>第一个玩家应该从第一堆中取出石头。他会带1个石头。石头堆的数量将是[ 1 ，5 ，4 ]。

>第二个玩家应该从第一堆中拿走石头。他会带1个石头，因为他不能再拿其他数量的石头了。石头堆的数量将是[ 0 ，5 ，4 ]。

>因为第一堆是空的，所以第一个玩家应该从第二堆中取出石头。他会带4石头。石头堆的数量将是[ 0 ，1 ，4 ]。

>第二个玩家应该从第二个桩中取出石头，因为第一个桩是空的。他会带1个石头，因为他不能再拿其他数量的石头了。石头堆的数量将是[ 0 ，0 ，4 ]。

>第一个玩家应该从第三堆中取出石头，因为第一堆和第二堆都是空的。他会带 4石头。石头堆的数量将是[ 0 ，0 ，0 ]。

>第二名玩家将输掉比赛，因为所有石子都没了。

仔细观察，不难研究出取的规律是：

**设一堆石头为 $x$ ,那么先手就应该取走 $x-1$, 这时就只剩下1个石头，另一个人只能取走这一个石头。但注意，到最后一堆时就全部取走。**

注：先手就是最后赢的人。

------------


#### 接下来是理性的分析：

为啥这种方法最优呢？**因为这样我们就限定了另一个人接下来的动作**。

那万一没有样例，我们怎么知道应取多少呢？我们注意一下题目中的这句话（不看也没事，是常识）：

>在移动中，玩家可以从第一个非空堆 (数量最少的堆至少有一个石头)中除去**正数**的石头。

所以除去石头的数量应该是正整数，所以最小是1，但最大没法求。所以我们应该将目光集中在**最小值1**上。也就是说我们应该使另一个人拿1个石头，那么我们就应该拿 $x-1$ 个石头。

------------



### 二、关于特殊的1

有一种特殊的情况：

**那就是 1**

**当这堆石子数为1的时候，就改变了先手**。因为你只能拿走这个石子。

所以当遇到**前缀1**时我们应该改变这个先手。有人可能注意到了，为啥是**前缀1**呢？难道后面的1就不能改变了吗？让我们来举个例子（可跳过）：

4

1 3 1 1

设采取第一步的是$A$,另一个人是$B$

第一堆：先手是$A,(0,3,1,1);$  **(后面的都是指这一堆先手走了第一步后还剩的石子数）**

第二堆：先手是$B,(0,0,1,1);$

第三堆：先手是$A,(0,0,0,1);$

第四堆：先手是$B,(0,0,0,0);$

所以你看，最后的赢家还是$B$,和第二堆的先手一样，后面的1并没起作用。

那有人说了，万一是这样的（其实是我一开始的疑问）：

3

1 3 1

再来看看结果：

第一堆：先手是$A,(0,3,1);$  **(后面的都是指这一堆先手走了第一步后还剩的石子数）**

第二堆：先手是$B,(0,1,1);$

第三堆：先手是$B,(0,0,0);$

所以你看，最后赢的还是$B$,和第二堆的先手一样。那么看来后面的1确实没啥用。



------------
细心的同学可能已经发现为什么了，因为如果后面有偶数个1时，这时的先手会将这一堆全部拿走，如果后面有奇数个1时，这时的先手会留下一个石子。这样，无论如何，他都会取得最后的胜利。**所以我们只要考虑前缀1。**


------------

### 三、关于程序

**从头到位扫一遍，如果遇到1，累加器加1；如果遇到不是1的数，就先加1，然后跳出。**

这样，我们就不仅统计了前缀1，还不会被这种例子坑到：

4

1 1 1 1

最后如果累加器为奇数，就输出 First，否则输出 Second。

最后上代码（很短）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[100005];
int main() {
    cin>>t;
    while(t--) {
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        int s=0;//累加器清零
        for(int i=1;i<=n;i++) {
            if(a[i]==1)s++;//如果是1就加1
            else {
                s++;break;否则加1跳出
            }
        }
        if(s%2==0)cout<<"Second"<<endl;//是偶数就是后走的人赢
        else cout<<"First"<<endl;//是奇数就是先走的人赢
    }
}
```

**各位大佬们点个赞再走吧，谢谢！**










---

## 作者：Luisvacson (赞：1)

显然当**石子数为1**时这一轮的玩家就**莫得选择** 经简单推理得若$a_i > 1$ 则第$i$轮的玩家必赢

简单推理过程：

若$i=n$，即这堆石子为最后一堆，那么本轮玩家可以直接取走所有。本轮玩家胜；

若$a_i=1$ ，则莫得选择，取完这堆，进入下一轮；

若$a_i>1$且$a_{i+1}=1$且$i+1\neq n$，则取完这一堆，让对方取下一堆的一个，再次进入下一轮；

若$a_i>1$且$a_{i+1}=1$且$i+1=n$，则取$a_i-1$个石子，留下一个给对方取，然后取掉最后一个石子，本轮玩家胜；

若$a_i>1$且$a_{i+1}>1$，则取$a_i-1$个石子，留下一个给对方取，进入下一轮；

经以上推理可以发现，手中石子数大于1的人拥有“**控制权**”，可以使比赛必胜

最后特判一下全是1的情况即可

$Complexity:O(2n)$

$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;

int T;
int n,a[100005];
signed main(){
    scanf("%d",&T);
    
    while(T--){
        scanf("%d",&n);
        register int i;
        
        bool flag=true;
        for(i=1;i<=n;++i) scanf("%d",&a[i]);
        for(i=1;i<=n;++i) if(a[i]!=1){flag=false;puts(i%2?"First":"Second");break;}
        
        if(flag) puts(n%2?"First":"Second");
    }
    
    return 0;
}
```


---

## 作者：xrdrsp (赞：0)

# Main Idea

有 $n$ 堆石子，第 $i$ 堆拥有 $A(i)$ 个石子。两个人轮流从当前第一个个数不为零的堆里拿出若干（正数）石子，那个没石子拿的人就输了。

# Analysis

定义 **“主动权”**：一个石子堆中先拿石子的人具有”主动权“。因为对于第 $i \left(A(i) > 1\right)$ 堆石子，先拿的人总是可以控制拿的石子的个数。由于他足够聪明，他有 $2$ 种方案来选择：

1. 拿 $A(i)$ 个，这堆石子被拿光了，在某些特殊情况下他应该采用这种方法；
2. 拿 $A(i) - 1$ 个，这堆石子剩下 $1$ 个，强制后拿的人拿走这一个，他在下一堆中仍然具有“主动权”，这种方法适用于一般情况。

下面开始讨论。

- 如果 $n$ 堆石子的个数全部大于 $1$，先拿的人在前 $n - 1$ 堆中采用第 $2$ 种，使他一直具有“主动权”。而在最后一堆拿走全部石子，他就赢了；
- 如果 $n$ 堆石子的个数全部等于 $1$，那么先拿的人与后拿的人总是没得选，每次全拿走：
  - 若 $2 \mid n$，则最后一堆后拿的人具有“主动权”，后拿的人就赢了；
  - 若 $2 \nmid n$，则最后一堆先拿的人具有“主动权”，先拿的人就赢了。
- 如果是其他情况，即有 $1$ 但不全是 $1$，那么在前缀 $1$ （前几堆连续 $1$）中，参照上一种情况；对于藏在中间的 $1$，足够聪明的选手可以通过与前面的堆调剂来保持自己的“主动权”，所以不必管。

# Code

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
int A[N];                                   // 每堆个数

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        bool all = 1, exist = 0;
        // all 表示是否全是 1，exist 表示是否存在 1
        int prefix1 = 0;                    // 前缀 1 的长度
        bool first = 0;                     // 先拿第一堆的人是否具有“主动权”
        int n;
        std::cin >> n;
        for (int i = 1; i <= n; i++) {
            std::cin >> A[i];
            if (A[i] == 1) {                // 判断是否全是 1 或 没有 1
                exist = true;
            } else {
                all = false;
            }
        }
        for (int i = 1; A[i] == 1; i++) {   // 寻找前缀 1 的长度
            prefix1++;
        }
        if (all) {                          // 判断
            if (n % 2 == 1) {
                first = 0;
            } else {
                first = 1;
            }
        } else if (!exist) {
            first = 0;
        } else {
            if (prefix1 % 2 == 1) {
                first = 1;
            } else {
                first = 0;
            }
        }
        if (!first) {
            std::cout << "First" << std::endl;
        } else {
            std::cout << "Second" << std::endl;
        }
    }
}
```

---

## 作者：Aehnuwx (赞：0)

**Warning: 本题解非标算**


------------
先特判所有数都为 $1$ 或都不为 $1$ 的情况。

- 所有数都为 $1$：判断奇偶性；
- 所有数都不为 $1$：先手必胜，原因略。


------------
对于其余情况，正难则反。

设 $\text{flag}_i=1/2$ 为取走第 $i$ 堆中的**最后一个石头**的人（**取完**石头）的编号。

>例如，若第 $2$ 堆中有 $3$ 个石头，1 取走前 $2$ 个，2 取走最后 $1$ 个，则 $\text{flag}_2=\textbf{2}$。

假设 $\text{flag}_n=1$，即 1 获胜。

枚举 $i=n-1,n-2,\cdots,1$。分类讨论：

- 若 $\text{flag}_{i+1}=1$

	- 若 $a_i=1$，即第 $i$ 堆中有 $1$ 个石头且第 $(i+1)$ 堆被 1 取完，则第 $i$ 堆必然被 2 取完。原因略；
    - 若 $a_i>1$，即第 $i$ 堆中有**多于** $1$ 个石头且第 $(i+1)$ 堆被 1 取完，则第 $i$ 堆必然被 1 取完。因为若第 $i$ 堆被 2 取完，则 2 在取第 $i$ 堆的时候会取 $(a_i-1)$ 个石头，而留下 $1$ 个石头给 1 取走。这样**先后手**关系便和假设矛盾，胜负也随之逆转。所以第 $i$ 堆不可能被 2 取完。

- 若 $\text{flag}_{i+1}=2$，即第 $(i+1)$ 堆被 2 取完，则第 $i$ 堆必然被 1 取完。因为若第 $i$ 堆被 2 取完，则 2 会取走 $a_i$ 个（即取完第 $i$ 堆），让先后手关系逆转。

枚举过后检查 $\text{flag}_1$ 是否为 $1$ 即得到答案（通过判断与假设是否矛盾，得到答案）。

时间复杂度线性。

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxN=100005;
int flag[maxN];
int main() {
	int t; scanf("%d",&t);
for (;t;t--) {
	int n; scanf("%d",&n);
	vector<int> a(n+1);
	int one=0;
	for (int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		if (a[i]==1) one++;
	}
	if (!one) puts("First");
	else if (one==n) puts(n&1?"First":"Second");
	else {
		flag[n]=1;
		for (int i=n-1;i;i--)
			if (flag[i+1]==1)
				if (a[i]==1) flag[i]=2;
				else flag[i]=1;
			else flag[i]=1;
		puts(flag[1]==1?"First":"Second");
	}
}
}
```


---

## 作者：Anita_Hailey (赞：0)

## 正文

看起来像是 nim 游戏，实则不然。(我不会告诉你我想把nim游戏的板子套上去的。

然后读了下题目，发现按只能从开始的堆取。

那么，考虑开头没有 1 的情况且还有两个以上的堆，那么很明显此时的这个人，都可以个后手留一个石子数为 1 的一个堆，这样这个人一直都可以保证先手，在这种情况下，先手是必胜的。

因为加入后边还有**一个堆**，那么它给后手剩一个，然后拿一堆。

要是只剩下一个堆了，那么它直接拿走就完了。

所以只要统计开头有多少个连续的石子数为1的堆就好了，注意最后一个不算。因为，先手可以直接拿完。

这样子的话，我们可以得到。

- 如果开始有奇数个堆 后手必胜，因为后手可以在取完这些东西之后变成先手
- 如果开始有偶数个堆 先手必胜

```cpp
#include <bits/stdc++.h>

#define gc( ) std::getchar( )
#define pc( i ) std::putchar( i )

template < typename T >
inline T read( )
{
	register T x = 0;
	register char ch = gc( );
	register bool f = 0;
	while( !std::isdigit( ch ) )
	{
		f = ( ch == '-' );
		ch = gc( );
	}
	while( std::isdigit( ch ) )
	{
		x = x * 10 + ( ch - '0' );
		ch = gc( );
	}
	return f ? -x : x;
}

template < typename T >
void print( T x )
{
	if( x < 0 )
	{
		x = -x;
		pc( '-' );
	}
	if( x < 10 )
	{
		pc( x + 48 );
		return;
	}
	print < T > ( x / 10 );
	pc( x % 10 + 48 );
	return ;
}

namespace Solution
{
#define IOS std::ios::sync_with_stdio( false ), std::cin.tie( 0 ), std::cout.tie( 0 )
#define Rep( i, j, k ) for( int i = j; i >= k; --i )
#define rdi( ) read < int > ( )
#define rdl( ) read < long long > ( )
#define pti( i ) print < int > ( i ), putchar( '\n' )
#define ptl( i ) print < long long > ( i ), putchar( '\n' )
#define For( i, j, k ) for( int i = j; i <= k; ++i )
	using std::cin;
	using std::cout;
	using std::endl;
	using std::vector;
	using std::map;
	using std::queue;
	using std::deque;
	using std::set;
	using std::pair;
	const int Maxn = 204001;
	int t, n;
	void fakemain( )
	{
		IOS;
		cin >> t;
		while( t-- )
		{
			cin >> n;
			int i, tmp, len = 0;
			for( i = 1; i <= n - 1; ++i )
			{
				cin >> tmp;
				len += tmp == 1;
				if( tmp != 1 ) break;
			}
			if( i < n )
				++i;
			for( ; i <= n; ++i )
			 cin >> tmp;
			cout << ( ( len & 1 ) ? "Second" : "First" ) << '\n';
		}
		return;
	}

} // namespace Solution

int main( int argc, char* argv[] )
{
	Solution::fakemain( );
	return 0;
}
```

---

