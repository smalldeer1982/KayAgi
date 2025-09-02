# Fire and Ice

## 题目描述

The Fire Lord attacked the Frost Kingdom. He has already got to the Ice Fortress, where the Snow Queen dwells. He arranged his army on a segment $ n $ in length not far from the city walls. And only the frost magician Solomon can save the Frost Kingdom.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF89E/55432292a936aea49d5c5885282505297fa5e79d.png)The $ n $ -long segment is located at a distance equal exactly to $ 1 $ from the castle walls. It can be imaginarily divided into unit segments. On some of the unit segments fire demons are located — no more than one demon per position. Each demon is characterised by his strength - by some positive integer. We can regard the fire demons being idle.

Initially Solomon is positioned on the fortress wall. He can perform the following actions several times in a row:

- "L" — Solomon shifts one unit to the left. This movement cannot be performed on the castle wall.
- "R" — Solomon shifts one unit to the left. This movement cannot be performed if there's no ice block to the right.
- "A" — If there's nothing to the right of Solomon, then Solomon creates an ice block that immediately freezes to the block that Solomon is currently standing on. If there already is an ice block, then Solomon destroys it. At that the ice blocks to the right of the destroyed one can remain but they are left unsupported. Those ice blocks fall down.

Solomon spends exactly a second on each of these actions.

As the result of Solomon's actions, ice blocks' segments fall down. When an ice block falls on a fire demon, the block evaporates and the demon's strength is reduced by $ 1 $ . When the demons' strength is equal to $ 0 $ , the fire demon vanishes. The picture below shows how it happens. The ice block that falls on the position with no demon, breaks into lots of tiny pieces and vanishes without hurting anybody.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF89E/1affd585a4baef63755d860b7d8694acfacd2540.png)Help Solomon destroy all the Fire Lord's army in minimum time.

## 样例 #1

### 输入

```
3
1 0 1
```

### 输出

```
ARARARALLLA```

## 样例 #2

### 输入

```
3
0 2 0
```

### 输出

```
ARARALAARALA```

# 题解

## 作者：liuli688 (赞：0)

## 1 思路
最开始的想法：每次选择最后面的最长连续不上升子串进行攻击。

根据样例 \#1，我们可以得出一个结论：如果一次能打较多的怪，就要一次打完。

当然，为了防止诸如 `1 0 2` 这类情况打完一轮后（此时序列为 `0 0 1`）还要回到最后清怪，要挑最后面的最长连续不上升子串进行攻击，这样打完后面的怪后就可以连着将前面的怪打掉了。

可以使用近似于双指针的方法：定义两个变量 $l$ 和 $r$，分别代表有怪区间的断点（即打掉这个冰块就能攻击到有怪区间）左边的点和有怪区间的右端点。每次循环，暴力找 $r$，然后用打擂台的方法从 $r$ 开始向左找 $l$，模拟攻击的方法进行输出即可。

但是，如果我们按照这个思路写的话，会发生下面的情况。

```
Test: #18, time: 0 ms., memory: 4 KB, exit code: 0, checker exit code: 1, verdict: WRONG_ANSWER
Input
3
100 0 100
Output
ARARARALLLAARARARALLLAARARARALLLA（剩余部分不予展示）...
Answer
ARALAARALAARALAARALAARALA（剩余部分不予展示）...
Checker Log
wrong answer jury's solution better than participant's one
```
通过输出，我们能发现：我们的一次攻击是 `ARARARALLLA`，浪费了一个冰块（掉落到没有怪的位置上）。所以，我们可以改进一下。

改完后的想法：每次选择最前面的最长连续不下降子串进行攻击。另外我还做了一个优化（可能是负优化）：将一个怪打到 $1$ 血就适可而止，最后在回头对所有的怪进行一锅端。

根据样例 `100 0 100`，我们同样可以得出一个的结论，如上文所述。这本质是一种贪心的思路：尽量减少落在地上的冰块。但是，它没有判断对一个有怪区间是否该进行攻击。

但是，我们发现它又 WA 了。

```
Test: #39, time: 0 ms., memory: 4 KB, exit code: 0, checker exit code: 1, verdict: WRONG_ANSWER
Input
1000
100 0 0 0 0 0 0 0 0 0 0 0 0 0 0（剩余部分不予展示）...
Output
ARALAARALAARALAARALAARALA（剩余部分不予展示）...
Answer
ARALAARALAARALAARALAARALA（剩余部分不予展示）...
Checker Log
wrong answer jury's solution better than participant's one
```
盲猜 Input 的末尾有一个数。因为我们的代码会不管 $1$ 血的怪，最后在长途跋涉回来进行最后一击，所以答案会比标答长。那么如何判断一个怪是现在打还是一锅端呢？我使用了一个十分暴力~~和不道德~~的方式：通过对每个动作的用时估算来确定动作。

这本质也是一个贪心想法：通过局部最优解来构造出整体最优解。贪心法的正确性请读者自行证明（或许可以由观察可得）。
## 2 代码实现
```cpp
#define speedup ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define namesp using namespace std

#include <bits/stdc++.h>
namesp;
//框架
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
//数据类型
const int INF = INT_MAX;
const int UINF = INT_MIN;
const ll LINF = LONG_LONG_MAX;
const ll ULINF = LONG_LONG_MIN;
//常量
#define fp(i,a,b) for(i = a;i < b;i++)
#define fm(i,a,b) for(i = a;i > b;i--)
#define fl(i,a,b) for(i = a;i <= b;i++)
#define fg(i,a,b) for(i = a;i >= b;i--)
#define bk break
#define ctn continue
#define reg register
//循环
#define freo(n,m) freopen(n,"r",stdin),freopen(m,"w",stdout)
#define frec(n) fclose(stdin),fclose(stdout)
//文件读写
#define mp make_pair
#define fir first
#define sec second
//pair
#define pb push_back
#define pf push_front
//序列式容器

int n,l,r,p = -1,tar,value,d,a[1001];
bool first;
signed main()
{
	speedup;
  	reg int i,j;
	cin >> n;
	a[0] = 0;
	l = n,r = 0;//l 为怪物区间左端点，r 为怪物区间右端点
	fl(i,1,n)
	{
		cin >> a[i];
		if(i < l && a[i] > 0)
			l = i;
		if(i > r && a[i] > 0)
			r = i;    
	}
	//边输入边记录 l,r. p 为 Solomon 的坐标
	while(r > 0){
		for(i = p+2;i <= r/*不越界*/ && !a[i];/*遇到怪物跳出*/i++)//向右走到怪物。    
			cout << "AR",p++;//记录坐标
		value = 1;//价值
		d = 0;//有怪段长度
		first = true;
		fl(i,p+2,r){//评估最近的怪物
			if(a[i] > 0){
				value += 4;//加价值
				if(first)//若有怪，则增加坐标 
					d++;
			}
			else{//减价值 
				value--;
				first = false;
			}
	    	if(value <= 0) //一个一个打 
	    	{
		    	//必须打破
		    	tar = d;
		    	fp(j,0,tar)
					cout << "AR";
		    	cout << 'A';
		    	fp(j,0,tar)
					cout << 'L';  
		    	cout << 'A';
		    	fl(j,p+2,p+d+2)
					if(a[j])
						a[j]--;      
		    	bk;
	    	}
	    } 
	    if(value > 0){//一锅端 
		    //修建道路到尽头
		    tar = r - p - 1;
		    fp(i,0,tar)
		    	cout << "AR";
		    cout << "AL";
		    p = r - 2;
		    if(a[r] == 1)//如果有地方可去的话，我们就回去。
		    	while(a[p+1] <= 1 && p+1 >= l){
					p--;
					cout << 'L';
				}
		    while(a[p+1] > 1 && p+1 >= l){
				p--;
				cout << 'L';
			}
		    cout << 'A'; //全部拆除
		    fl(i,p+2,r)
				if(a[i])
					a[i]--;  
	    }
	    //寻找新的边界
	    l = n;r = 0;
	    fl(i,1,n){//记录 l,r.
	    	if((i < l) && (a[i] > 0))
				l = i;
	    	if((i > r) && (a[i] > 0))
				r = i;    
	    }
	}  
	return 0;
}
```
### 3 代码解释
代码的主要难点在于 $value$。代码通过 $value$ 来判断下一步行动。如果这格有怪，那么 $value \gets value + 5$（`LAARA` 的长度）$-1$（在下面的 `else value--;`这里）即 $value \gets value + 4$，否则 $value \gets value - 1$。若 $value > 0$，则说明值得一锅端，否则立刻攻击。
### 4 提交结果
于是 [AC](https://www.luogu.com.cn/record/144286039) 啦！

------------

---

