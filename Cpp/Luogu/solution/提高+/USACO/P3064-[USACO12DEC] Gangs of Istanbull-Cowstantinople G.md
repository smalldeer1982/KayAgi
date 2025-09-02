# [USACO12DEC] Gangs of Istanbull/Cowstantinople G

## 题目描述

Life is tough on the farm, and when life is tough you have to get tough. The cows have formed gangs (conveniently numbered 1 to M).  The gangs coexisted in peace for a while, but now things are really getting out of control!

The cows are competing over control of a great grazing field.  This conflict happens over a series of minutes.  Each minute a single cow walks into the field.  If the field is empty the new cow's gang is considered to take control of the field.  If the field is already controlled by the new cow's gang then the cow just starts grazing.  Otherwise, a single cow from the controlling gang that is grazing confronts the new cow.

These confrontations between two cows start with some arguing and inevitably end up with the pair coming to realize how much more more alike than different they are.  The cows, seeing the error in their ways, leave the gang and the field and get a cold glass of soy milk at FJ's tavern.  If after this confrontation the field is empty than no gang controls the field.

Bessie realizes how these confrontations will occur.  She knows how many cows are in each gang.  Bessie really wants her gang to control the field after the conflict is over and all cows are either on the field or at FJ's tavern.  Help Bessie determine if it is possible for her gang, labeled 1, to control the field in the end.

If it is possible, Bessie wants to know the maximum number of cows from her gang that could be on the field at the end.  Output this number and the lexicographically earliest ordering of cows that results in this number of cows from Bessie's gang at the end.  An ordering X is said to be lexicographically earlier than Y if there is some k such that X[k] < Y[k] and X[i] = Y[i] for i < k.

n头牛结成了m个帮派，现在它们争夺一块草地。每个单位时间内会有一头牛来。如果草地上还没有牛或者只有自己帮派的牛，他会留在这里。但如果已经有别的帮派的牛，它们会打一架，这使得当前牛和草地上的一头牛去找农夫思考人生。问如何安排来的牛的编号顺序，能使一  号帮派最后有最多的牛留在草地上，如果不为0，还要输出字典序最小的一组方案。


## 说明/提示

There are 5 cows and 3 gangs.  Bessie's gang (gang 1) has 2 members, gang 2 has 1 member, and gang 3 has 2 members.


Only one cow from Bessie's gang can end up on the field. 



## 样例 #1

### 输入

```
5 3 
2 
1 
2 
```

### 输出

```
YES 
1 
1 
3 
2 
3 
1 
```

# 题解

## 作者：SBofGaySchool (赞：13)

我来一篇构造的题解吧。

### 1.题目思路

本题的要求有二：

1. 一号帮派剩余牛数尽量多；
2. 在满足要求一的情况下，字典序尽量小。

我们首先思考如何构造能够使得一号帮派剩余牛数最多。为了达到这个目的，我们 **要让其他帮派的牛相互打架，剩下尽量少的牛去和一号帮派打**。

考虑 **除了一号帮派之外** 的其他牛。在初始状态下有两种情况，我们分别讨论。

- **情况一：任何帮派中牛的数量不超过总牛数（不考虑一号帮派）的一半（向上取整）**

设总牛数为 $S$，当前牛数最多的帮派牛数为 $X$，则这种情况可以表示成 $X \le \lceil S/2 \rceil$。在这种情况下我们可以证明，存在一种构造，使得这些牛打完架之后一头不剩（偶数）或只剩一头（奇数）。我们用数学归纳法来证明这个结论。

1. 当 $S=2$ 时，一共只有两头牛，满足条件的情况只有一个，即一头 $A$ 帮派的牛与一头 $B$ 帮派的牛。让他们打架后，一头牛都不剩，结论成立；
2. 当 $S=3$ 时，在满足条件的情况下，牛的帮派可以被表示为 $AAB$ 或 $ABC$。选取 $A$ 帮派的牛和另一个帮派的牛打架，最终只剩一头牛，结论成立；
3. 若 $S=K-2$ 时结论成立，则当 $S=K$ 时，我们选择当前牛数最多的帮派（设牛数为 $X$，此时满足$X \le \lceil S/2 \rceil$）中的一头牛和随便一个其他帮派的一头牛打架，则打完架后该帮派牛的数量 $X'=X-1$，同时 $S=K-2$，仍然满足 $X' \le \lceil S/2 \rceil$ ，情况转换为了 $S=K-2$ 时的情况。故若 $S=K-2$ 时结论成立，则当 $S=K$ 时结论仍成立。

综上，我们证明了这个结论。

- **情况二：牛数最多的那个帮派中牛的数量超过总牛数（不考虑一号帮派）的一半（向上取整）**

根据鸽笼原理，最后剩下的帮派一定是一开始牛数最多的那个帮派。此时最优策略就是让其他牛都去和这个帮派的牛打架，才能让这个帮派尽量少剩下牛。

### 2.构造方式

除了找出剩余牛数最少的构造方式，我们还需要考虑到字典序最小这个要求。对于上述两种情况，我们分别进行构造，使得在其他帮派的牛相互打架之后剩下的牛尽量少的前提下，字典序尽量小。

- **情况一：任何帮派中牛的数量不超过总牛数（不考虑一号帮派）的一半（向上取整）**

  - **当草场上没有牛的时候：** 选择序号最小的帮派，把所有牛都放上去。这样做不会对各个帮派中牛的数量造成影响；

  - **当草场上有牛的时候：** 此时要考虑派哪个帮派的牛去打架。根据刚才证明的结论，只要打完架之后没有破坏条件 $X \le \lceil S/2 \rceil$，我们最终一定能够让剩下的牛数最少。我们先尝试选择下一个序号最小的帮派中的一头牛去草场上打架；
  
    - **如果这样打完架之后条件 $X \le \lceil S/2 \rceil$ 未被破坏：** 那么我们这么做不会改变剩余牛数（剩下的牛数还是可以做到尽量少），还满足了字典序尽量小；
    
    - **如果这样打完架之后条件 $X \le \lceil S/2 \rceil$ 被破坏了：** 这意味着我们必须从当前牛数最多的帮派中找牛去打架（根据上文对结论的证明，这样构造不会破坏条件）。我们就撤销刚才的决策，改为从当前牛数最多的帮派中找牛去打架。

- **情况二：牛数最多的那个帮派中牛的数量超过总牛数（不考虑一号帮派）的一半（向上取整）**

  - **当草场上没有牛的时候：** 选择序号最小的帮派，把所有牛都放上去；

  - **当草场上有牛的时候：** 如果这个帮派不是牛数最多的帮派，为了让剩余牛数尽量少，我们就要从牛数最多的帮派中派牛去打架；否则，我们只需要让之后的帮派依次去打架即可。

总结上述情况，我们可以得到以下具体的构造方式：

  - **当草场上没有牛的时候：** 选择序号最小的帮派，把所有牛都放上去；

  - **当草场上有牛的时候：** 先尝试选择下一个序号最小的帮派中的一头牛去草场上打架。如果发现这么做会使得不在草场上的帮派中牛数最多的帮派中牛的数量超过总牛数一半（对于情况二而言，只要当前草场上的帮派的牛数不是最多的，此条件一定成立），就需要从牛数最多的那个帮派中选一头牛去草场上打架。

打完架之后，最后再让一号帮派的牛去草场上，就可以让一号帮派剩余牛数尽量多，同时让其他帮派打架顺序的字典序尽量小了。

这里还有最后一点需要注意的地方：为了让字典序最小，我们可以在不影响结果的基础上，先让一号帮派的牛去草场上，之后再让其他帮派去打架，最后再安排剩下的一号帮派的牛去草场上。

### 3.代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 105
int N, M, a[MAXN];
// f为下一个帮派序号，sum为剩余牛总数，maxi为不在草场上的帮派中牛数最多的帮派序号
// cur为当前草场上的帮派序号，cnt为当前草场上牛的数量
int f, sum, maxi, cur, cnt;
// 重新计算上述各项变量
void calc() {
    f = sum = maxi = 0;
    for (int i = 2; i <= M; i++) {
        if (a[i] <= 0) {
            continue;
        }
        if (!f) {
            f = i;
        }
        sum += a[i];
        if (!maxi || a[i] > a[maxi]) {
            maxi = i;
        }
    }
}
int main() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        cin >> a[i];
    }
    calc();
    // 先计算其他帮派打完架之后最少会剩多少头牛
    int l = max(a[maxi] - (sum - a[maxi]), sum % 2);
    if (a[1] <= l) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl << a[1] - l << endl;
    // 为了让字典需最小，在不影响结果的情况下，先让一号帮派的牛去草场上
    while (a[maxi] > cnt + sum - a[maxi]) {
        cout << 1 << endl;
        a[1]--;
        cur = 1;
        cnt++;
    }
    if ((cnt + sum) % 2) {
        cout << 1 << endl;
        a[1]--;
        cur = 1;
        cnt++;
    }
    // 在还剩余牛的情况下，让其他帮派的牛打架
    while (sum) {
        if (cnt) {
            // 如果草场上有牛
            if (a[maxi] > cnt + sum - a[maxi] - 2) {
                // 如果派其他帮派的牛去打架会导致剩余牛数最多的帮派牛数超过总牛数的一半
                // 就需要派剩余牛数最多的帮派中的一头牛去草场上打架
                cout << maxi << endl;
                a[maxi]--;
            } else {
                // 否则，派任何帮派的牛都可以
                // 为了字典序号最小，我们派下一个序号最小的帮派中的一头牛去打架
                cout << f << endl;
                a[f]--;
            }
            cnt--;
            if (!cnt) {
                cur = 0;
            }
        } else {
            // 如果草场上没有牛，直接把下一个帮派中所有牛派去草场上
            cur = f;
            cnt = a[f];
            while (a[f]--) {
                cout << f << endl;
            }
        }
        // 重新计算派完牛之后各个帮派牛的数量
        calc();
        if (sum == a[maxi] && (!cnt || cur == 1)) {
            break;
        }
    }
    // 最后再让一号帮派的牛去草场上
    while (a[1]--) {
        cout << 1 << endl;
    }
    while (a[f]--) {
        cout << f << endl;
    }
    return 0;
}
```


---

## 作者：A4paper (赞：12)

既然没有题解，那就让蒟蒻来写一篇。

个人感觉，这是一道贪心题，实现在代码中写的很清楚，我就讲一下思路吧！

首先，我们的目标是让 $Bissie$ 所在的 1 号帮派占领草地，所以我们要**尽量让其他帮派打架**，最后再让 1 号帮派坐收渔翁之利，而对于其他帮派而言，牛数越多的帮派对 1 号帮派产生的威胁越大，所以要提前让牛数多的帮派打架。那么第 1、2 问就解决了，就是排序后从大的开始减，将除 1 号帮派以外的牛都放入草地后再判断 1 号能不能占领那里。

至于输出顺序，就是上面结论的推广，因为数据范围只有 100 ，这里引用某位大佬的一句名言“$n=100$ 引导我们 $n^3$” 所以我就暴力枚举出每一头牛，然后再利用上面的贪心判断是否与前两问求出的答案相符，如果相符，就直接输出这头牛的帮派号，如果不相符，就继续往后枚举。

```cpp
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 105

int m,n,gang,cow; //gang 表示当前占场的帮派编号，cow 表示草地上有几头牛
int a[MAXN];

void fight(int &Gang, int &x, int new_cow) //当前占场的帮派号、其奶牛数量和新来的奶牛帮派号
{
	if(x == 0) Gang = new_cow; //如果本来就没牛占领，那就被新来的奶牛占了
	if(Gang == new_cow) x++; //如果新来的奶牛属于当前占场的帮派，那牛数++（包括第一只奶牛）
	else				x--; //否则会有一只原先占场的奶牛去思考人生，牛数--
}

int result(int Gang, int Cow) //表示当前占场的帮派编号和其奶牛数量
{
	int temp[MAXN];
	for(int i=1;i<=n;i++) temp[i] = a[i];
	sort(temp+2,temp+1+n);
	while(temp[n])
	{
		for(int i=n;i>=2;i--) //先暂时忽略 Bissie 的帮派
		{
			fight(Gang,Cow,i);
			temp[i]--;
			if(temp[i] >= temp[i-1]) break; //贪心的将牛数最多的帮派放入草地。
		}
	}
	for(int i=1;i<=temp[1];i++)//最后再将 Bissie 的帮派放入草地
		fight(Gang,Cow,1);
	if(Gang == 1) return Cow; //如果 Bissie 的帮派占领了草地
	else		  return 0;
}

int main(void)
{
	cin >> m >> n;
	for(int i=1;i<=n;i++) cin >> a[i];
	int num = result(0,0);
	if(!num)
	{
		puts("NO");
		return 0;
	}
	cout << "YES\n" << num << "\n";
	for(int i=1;i<=m;i++)
	{
		int temp_gang = gang;
		int temp_cow  = cow;
		for(int j=1;j<=n;j++)
		{
			if(!a[j]) continue;
			a[j]--;
			fight(gang,cow,j); //先把一只奶牛放入草地，然后再判断这种情况是否合法
			if(result(gang,cow) == num)
			{
				cout << j << "\n";
				break; //由于要求字典序最小，所以合法的话就再从头找起
			}
			a[j]++; //不合法的话就赶紧还原状态，找下一个帮派是否合法
			gang = temp_gang;
			cow  = temp_cow;
		}
	}
	return 0;
}
```

求过求过，安利[博客](https://www.luogu.org/blog/A4paper/)


---

