# Bear and Elections

## 题目描述

`Limak`前来参加选举。

在选举中，候选人总共有$n$位，第$i$位候选人当前的选票是$a_{i}$。

`Limak`十分渴望权力，于是他决定使用下作的手段赢得选举——贿赂市民。对于每一个市民，`Limak`只需要一颗糖果就可以贿赂他。

请问，`Limak`至少需要几颗糖果才能赢得选举？

## 说明/提示

$2 \leq n \leq 100$；

$1 \leq a_{i} \leq 1000$；

## 样例 #1

### 输入

```
5
5 1 11 2 8
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
1 8 8 8
```

### 输出

```
6
```

## 样例 #3

### 输入

```
2
7 6
```

### 输出

```
0
```

# 题解

## 作者：lichenzhen (赞：5)

## 题目大意
`Limak`参加竞选，为了赢得竞选，他要贿赂投票的市民。

现在给出参加竞选的人数、`Limak`的票数以及其他人的票数。

求`Limak`至少需要几颗糖果才能赢得选举。

这里要补充一下：输入第二行的第一个数据是`Limak`的票数

## 题目解法
这是一道比较水的题目，策略就是一直贿赂给当前票数最高的人投票的市民，每次贿赂一位，直到`Limak`的票数是最高的为止。

实现方法可以每次贿赂完都用`sort`排一遍序，由于这道题的数据比较水，所以不会超时。但是这样复杂度太高了。

这里我用的是另外一种方法，就是用优先队列`priority_queue`。这是C++里的一种数据结构，在头文件`queue`里，它有两种类型，一个是大根堆（默认是大根堆），一个是小根堆。（详细介绍可以自行百度）

这里我们用到的是大根堆，它有一个特性，就是它会把最大的数据放在最前面。所以我们可以用的这个特性，省去每次排序。具体用法看参考代码。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,z,ans;
int main()
{
    priority_queue<int>p;//定义一个int类型名字为p的大根堆
    cin>>n>>z;//z是Limak的票数，我们单独读入，方便后面使用。
    for(int i=2;i<=n;i++){
        cin>>a;
        p.push(a);//push是将数据放入到p中
    }
    while(z<=p.top()){//top指的是队列中的第一个数据(在这里是最大的)
        int maxn=p.top();//代表的是当前最高票数的人
        p.pop();//pop是将队列的第一个数据删除。
        p.push(maxn-1);//贿赂了一位市民那个人的票数就少了一票
        ans++;//贿赂的人数加1
        z++;//Limak的票数加1
    }
    cout<<ans;
}
```


---

## 作者：Fcersoka (赞：2)

~~很明显 ，这是一道水题 ！~~  
这里对题目补充一点 ，Lamik 是第一位候选人 。  
这道题的思路已经很明显了 ，直接暴力 ，每次贿赂投给票数最高的候选人的人 ，让他给 Lamik 投票 ，直到 Lamik 成为票数最高的候选人 。这样说应该能听懂吧 。    
如果你还是不懂 ，可以参考代码 。  
OK，直接上代码 。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[101],ans;
int main() {
	cin>>n;
	for(int i=1; i<=n; i++)
		cin>>a[i];
	sort(a+2,a+n+1);
    //先排序，如果Lamik的票数已经是最高的，那么就不用贿赂
	while(a[n]>=a[1])
		ans++,a[n]--,a[1]++,sort(a+2,a+n+1);
    //这里要先让Lamik的票数加1，票数最高的人的票数减1，再排序
	cout<<ans;
	return 0;
}
```
代码够简短了吧 。  
感谢您的观看 ！

---

## 作者：CQ_Bab (赞：1)

#  思路

因为第一个是 Limak 的票数所以我们将 $a[2] \sim a[n]$ 由小到大进行排序，用 while 去给糖，因为每次给了糖果之后之前的顺序可能与现在不同，所以就再排一次，注意：每次给了糖之后要将自己的票数加一再将第一的票数减一，直到 Limak 的票数大于除他以外第一的票数

# AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=110;
int n,a[N],res; 
int main(){
	cin>>n; // 输入 
	for(int i=1;i<=n;i++) cin>>a[i]; // 输入 
	sort(a+2,a+1+n); // 因为a[1]为Limak自己的票数所以从a[2]开始排序
	while(a[1]<a[n]){
		a[1]++; //  Limak自己的票数加加 
		a[n]--; // 最高的票数减减 
		sort(a+2,a+1+n); // 因为每次给了糖果之后之前的顺序可能与现在不同，所以就再排一次
		res++; // 次数加加 
	} 
	cout<<res<<endl; 
	return 0; // 完美散花
}
```


---

## 作者：ttq012 (赞：0)

分类讨论。

当 `Limik` 的票数已经是全场最多的了，那么就一个糖果也不用发。

否则，暴力枚举当前票数最高的人，贿赂一名投这个人的市民，将 `Limik` 的票数自增 $1$，贿赂的糖果数自增 $1$，这个人的票数自减 $1$，然后继续枚举当前票数最多的人，执行这些命令，一直到 `Limik` 成为当前票数最多的人为止。

**Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

int a[3000010];
int arr[3000010];

signed main(int arg_c,char *arg_v[]) {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i ++) cin >> a[i];
	int td = a[1];
	bool flag = true;
	for (int i = 2; i <= n; i ++) if (a[i] >= a[1]) {
	    flag = false;
	    break;
    } if (flag) {
        cout << 0 << '\n';
        return 0;
    } sort (a + 1, a + n + 1, greater <int> ());
	int ans = 0;
	while (a[1] >= td) {
		ans ++;
		td ++;
		a[1] --;
		sort (a + 1, a + n + 1, greater <int> ());
	}
	cout << ans << '\n';
	return 0;
}

```


---

## 作者：_easy_ (赞：0)

# 思路
根据题意，我们要让 $\texttt{Limak}$ 的选票数最高，也就是贿赂给目前最高的人投票的市民。换句或说，我们就是要将目前最高的人的投票数减去 $\texttt{1}$，给需要的糖果数和 $\texttt{Limak}$ 的选票数加上 $\texttt{1}$。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[105],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+2,a+n+1);//这里说明一下，输入的a[1]表示Limak的选票数，所以需要从a[2]开始排序
	if(a[1]>a[n]){
		cout<<0;
		return 0;
	}
	while(a[1]<=a[n]){
		a[1]++;
		a[n]--;
		sort(a+2,a+n+1);//同上
		ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：agicy (赞：0)

享受最佳阅读体验请进入[传送门](https://lu-anlai.github.io/2019/02/09/%E3%80%90%E9%A2%98%E8%A7%A3%E3%80%91%E3%80%90Codeforces-574A%E3%80%91-Bear-and-Elections/)。

## 原题

题面请查看[Codeforces 574A Bear and Elections](http://codeforces.com/problemset/problem/574/A)。

也可在洛谷上查看：[传送门](https://www.luogu.org/problemnew/show/CF574A)。

洛谷题面翻译来自[@卢安来](https://www.luogu.org/space/show?uid=38502)，~~其实就是我~~。

## 题解

模拟+排序

### 思路

根据正常人的想法和思维，选票最多的人是`Limak`最大的敌人，我们应该多贿赂他的支持者。

因为每次贿赂后，选票最多的人都会改变，所以我们每次操作（实行贿赂）后进行排序即可。

#### 具体实现

设`vote`为`Limak`当前选票，那么每次的操作就可以写成这样：

```cpp
while (a[n - 1] >= vote) //如果Limak无法获胜
{                        //开始贿赂
    --a[n - 1];          //贿赂选票最多的人的一名支持者
    sort(a + 1, a + n);  //重新排序
    ++vote;              //Limak的选票增加
    ++ans;               //计数器自增
}
```


### 代码

代码如下：

```cpp
#include <algorithm>
#include <cstdio>
using std::sort; //排序

int n, vote, a[101]; //变量如上文所述

int main(void)
{
    register int i, ans = 0;
    scanf("%d%d", &n, &vote); //读入
    for (i = 1; i < n; ++i)   //除去Limak还有n-1个人
        scanf("%d", &a[i]);
    sort(a + 1, a + n);      //要先排序
    while (a[n - 1] >= vote) //如果Limak无法获胜
    {                        //开始贿赂
        --a[n - 1];          //贿赂选票最多的人的一名支持者
        sort(a + 1, a + n);  //重新排序
        ++vote;              //Limak的选票增加
        ++ans;               //计数器自增
    }
    printf("%d\n", ans); //输出并换行
    return 0;
}
```

### 我的评测记录

- [Codeforces](http://codeforces.com/contest/574/submission/49663968)；

- [洛谷](https://www.luogu.org/recordnew/show/16146974)。


---

