# The Closest Pair

## 题目描述

Currently Tiny is learning Computational Geometry. When trying to solve a problem called "The Closest Pair Of Points In The Plane", he found that a code which gave a wrong time complexity got Accepted instead of Time Limit Exceeded.

The problem is the follows. Given $ n $ points in the plane, find a pair of points between which the distance is minimized. Distance between $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF311A/22fd88ba9a7f84161b680cf39a97d9a06bc287ba.png).

The pseudo code of the unexpected code is as follows:

`<br></br>input n<br></br>for i from 1 to n<br></br>    input the i-th point's coordinates into p[i]<br></br>sort array p[] by increasing of x coordinate first and increasing of y coordinate second<br></br>d=INF        //here INF is a number big enough<br></br>tot=0<br></br>for i from 1 to n<br></br>    for j from (i+1) to n<br></br>        ++tot<br></br>        if (p[j].x-p[i].x>=d) then break    //notice that "break" is only to be<br></br>                                            //out of the loop "for j"<br></br>        d=min(d,distance(p[i],p[j]))<br></br>output d<br></br>`Here, $ tot $ can be regarded as the running time of the code. Due to the fact that a computer can only run a limited number of operations per second, $ tot $ should not be more than $ k $ in order not to get Time Limit Exceeded.

You are a great hacker. Would you please help Tiny generate a test data and let the code get Time Limit Exceeded?

## 样例 #1

### 输入

```
4 3
```

### 输出

```
0 0
0 1
1 0
1 1
```

## 样例 #2

### 输入

```
2 100
```

### 输出

```
no solution
```

# 题解

## 作者：dthythxth_Huge_Brain (赞：1)

伪代码：

```
input n
for i from 1 to n
    input the i-th point's coordinates into p[i]
sort array p[] by increasing of x coordinate first and increasing of y coordinate second
d=INF        //here INF is a number big enough
tot=0
for i from 1 to n
    for j from (i+1) to n
        ++tot
        if (p[j].x-p[i].x>=d) then break    //notice that "break" is only to be
                                            //out of the loop "for j"
        d=min(d,distance(p[i],p[j]))
output d

```

不难发现，当输入的的所有 $x$ 的值全部相等时，运行次数为 $n\times (n+1)/2$，运行次数最多，当 $k$ 的值比这个数大，就无解，输出 ```no solution```。

若 $k$ 的值小于 $n\times (n+1)/2$，就说明有解，要让循环次数尽可能多，就要让输入的 $n$ 行的 $x$ 的差尽可能小，也就是相等，然后 $y$ 只要随机但是互不相等就好了。

参考代码：

```
#include<bits/stdc++.h>
using namespace std;
#define over 
#define int long long
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int n,k;
	cin>>n>>k;//输入
	if(n*(n-1)/2<=k){//若无解，输出 no solution
		cout<<"no solution";
		return 0;
	}
	int x=114514,y=1919810;
	for(int i=0;i<n;i++){
		cout<<x<<' '<<y+i<<"\n";//输出
	}
	return 0;//完结撒花
}

```

---

## 作者：loser_seele (赞：1)

首先观察代码，发现只有当输入的所有 $ x $ 值全部相等的时候运行次数最大，为 $ \frac{n \times (n+1)}{2} $，如果 $ k $ 比这个值大则直接输出无解。

否则任意选定一个固定的 $ x $，再选一个随机的 $ y $ 即可。

但注意到题目里要求所有点的坐标不同，直接随机可能无法通过，于是应该不断随机 $ n $ 个 $ y $，直到所有 $ y $ 两两不同的时候再输出，否则重新生成即可。

由于值域为 $ 10^9 $，而数字只有 $ 2000 $ 个，所以生成重复的数字的概率很小，实测即使只生成一次数字也可以做到完全不生成重复数字。

时间复杂度 $ \mathcal{O}(n\log{n}) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(1919810);
const int mod=1e9;
set<int>s;
signed main()
{
    int n,k;
    cin>>n>>k;
    if(n*(n-1)/2<=k)
	    return !printf("no solution\n");
    else
        while(1145141919810)
        {
            for(int i=1;i<=n;i++)
                s.insert(rnd()%mod);
            if(s.size()==n)
            {
                for(auto x:s)
                    cout<<114514<<' '<<x<<'\n';
                return 0;
            }
            else
                s.clear();
        }
}
```


---

## 作者：Feyn (赞：1)

洛谷上看不了伪代码，要去原网站上看。代码是这样的：

```
input n
for i from 1 to n
    input the i-th point's coordinates into p[i]
sort array p[] by increasing of x coordinate first and increasing of y coordinate second
d=INF        //here INF is a number big enough
tot=0
for i from 1 to n
    for j from (i+1) to n
        ++tot
        if (p[j].x-p[i].x>=d) then break    //notice that "break" is only to be
                                            //out of the loop "for j"
        d=min(d,distance(p[i],p[j]))
output d
```

大概思想是把那些点按照横坐标排序，然后枚举第一个点和第二个点并更新答案。然后它有一个聊胜于无的优化是，假如当前的点和第一个点的横坐标之差已经比最优答案还要大了，那么它以及后面的点肯定不会成为最优答案，直接跳出循环。

既然我们希望这段程序执行的次数多，就只需要让优化不起作用即可，一个显然的构造是钦定所有点的横坐标相同即可。纵坐标嘛，我不懂为什么别的题解会用到随机数，顺着输出不就好了吗。

代码：

```cpp
int m,n;

signed main(){
	
	read(m);read(n);
	if(m*(m-1)/2<=n)printf("no solution\n");
	else for(int i=1;i<=m;i++)printf("0 %d\n",i-1);
	
	return 0;
}
```

---

## 作者：Cloud_Umbrella (赞：1)

~~（还被困在伪代码里的笔者....）~~

## 题意

伪代码的意思大概是，给定 $n$ 和 $k$，定义 $tot$ 为循环次数，当 $k$ 大于最大的 $tot$ 时，输出 ```no solution```。否则，随意构造一组输出（真的很随意，只要不重复就行）。

## 分析

通过伪代码可得出，$tot$ 最大是 $\large\frac{n\times (n-1)}{2}$，如果 $k$ 大于这个值，输出 ```no solution```。否则，随意输出 $n$ 行，每行 $2$ 个数。

注：题目说不能有两个重复的点，所以只要控制一个定量，在配合一个变量，就能保证没有一对相同的 $(x,y)$。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main(){
	int x=114514;//主打的就是随意 
	scanf("%d%d",&n,&k);
	if(n*(n-1)/2<=k){
		printf("no solution\n");
		return 0;
	}
	for(int i=1;i<=n;i++)
		printf("%d %d\n",x,i);//用x当定量（用常量定义也行，反正没有变化），i为变量。 
	return 0;//好习惯伴终生 
}
```

---

## 作者：Transparent (赞：1)

### 题目大意

~~前面几个段都是废话~~

从伪代码开始（题面的排版……）：

```
input n
for i from 1 to n
    input the i-th point's coordinates into p[i]
sort array p[] by increasing of x coordinate first and increasing of y coordinate second
d=INF        //here INF is a number big enough
tot=0
for i from 1 to n
    for j from (i+1) to n
        ++tot
        if (p[j].x-p[i].x>=d) then break    //notice that "break" is only to be
                                            //out of the loop "for j"
        d=min(d,distance(p[i],p[j]))
output d
```

**题目要求**：给你两个整数 $n$ , $k$ （ $n$ 即为代码中的 $n$ ),你需要构造一组输入，让程序结束时 $tot$ 的值大于 $k$ ，如果不可能，就输出 `no solution`。

-------------

显然， $tot$ 的值即为循环次数，
而循环的次数最大为 $n \times (n-1) \div 2 $ ，
所以如果 $k$ 比这个值大，就直接输出 `no solution`。

程序中影响循环次数的主要是第 $10$ 行的 `break` ，
要让循环次数更多，
就要让 $p[j].x-p[i].x$ 尽量小，即差最小
所以每次输入的 $x$ 应该都相等。

因为 $y$ 不影响循环次数，
所以 $y$ 可以取任意值。
**但是**，题目要求每次输入的 $x$ , $y$ 对应的点不能有重合，
所以~~不要用rand()~~ 要按照一定的逻辑~~随意~~ 输出 $y$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main()
{
	srand(time(NULL));
	const int x=rand();//随便选一个x 
	scanf("%d%d",&n,&k);
	if(n*(n-1)/2<=k)//判断最大循环次数是否小于等于k 
	{
		printf("no solution\n");//没有解 
		return 0;
	}
	for(register int i=1; i<=n; i++)
	{
		printf("%d %d\n",x,i);//输出一定的x，不定且不重复的y 
	}
	return 0;
}
```
~~如果你有办法产生小于 1e9 且不重复的随机数，
那一定要试试随机输出y（逃~~

---

## 作者：ggc123 (赞：0)

~~吐槽一下：题面十分美观，翻译简单易懂。~~

建议更新一下。
## 思路

$tot$ 是代码的循环次数，所以根据代码得出 $tot$ 最大为 $\dfrac{n^{2}-n}{2}$，即所有的点 $x$ 坐标相等。

因此，当 $k > tot$ 时，就一定 `cout << "no solution"`。当 $k \le tot$ 时，就应当将 $x$ 坐标尽量相等，$y$ 坐标随机但不相等。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k;
int main() {
	cin >> n >> k;
	if (n * (n - 1) / 2 <= k)
		cout<<"no solution\n";
	else
		for (int i = 1; i <= n; i++)	
			cout << 114514 << " " << i << "\n";
	return 0;
}
```

---

## 作者：zhengenzhe (赞：0)

这里先放一下伪代码：
```c++
input n
for i from 1 to n
    input the i-th point's coordinates into p[i]
sort array p[] by increasing of x coordinate first and increasing of y coordinate second
d=INF        //here INF is a number big enough
tot=0
for i from 1 to n
    for j from (i+1) to n
        ++tot
        if (p[j].x-p[i].x>=d) then break    //notice that "break" is only to be
                                            //out of the loop "for j"
        d=min(d,distance(p[i],p[j]))
output d
```
## 【题目大意】

给你两个整数 $n,k$ 你需要构造一组输入，让程序结束时 $tot$ 的值大于 $k$，如果不可能，就输出 no solution。$tot$ 为循环次数。

## 【思路】

分析一下伪代码可得知，$tot$ 最大等于 $\frac{n^2-n}{2}$，一旦$k>tot$ 就是无解的，输出 no solution，否则就任意数出两个数（不重复）

## Code：

```c++
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,k;
namespace IO {//快速读入
    const int MAXR = 10000000;
    char _READ_[MAXR], _PRINT_[MAXR];
    int _READ_POS_, _PRINT_POS_, _READ_LEN_;
    inline char readc() {
    #ifndef ONLINE_JUDGE
        return getchar();
    #endif
        if (!_READ_POS_) {
            if (feof(stdin)) return -1;
            _READ_LEN_ = fread(_READ_, 1, MAXR, stdin);
        }
        char c = _READ_[_READ_POS_++];
        if (_READ_POS_ == _READ_LEN_) _READ_POS_ = 0;
        return c;
    }
    template<typename T> inline int read(T &x) {
        x = 0; register int flag = 1, c;
        while (((c = readc()) < '0' || c > '9') && c != '-')
            if (c < 0) return -1;
        if (c == '-') flag = -1; else x = c - '0';
        while ((c = readc()) >= '0' && c <= '9') x = x * 10 - '0' + c;
        x *= flag; return 0;
    }
}
using namespace IO;
int main(){
	read(n);
	read(k);
	if((n*(n-1))/2<=k){//无解情况
		puts("no solution");
		return 0;
	}
	for(ll i=1;i<=n;i++){
		cout<<"1"<<" "<<i<<'\n';//只控制1个数变就可以答到不重复的效果
	}
	return 0;
}
```

---

