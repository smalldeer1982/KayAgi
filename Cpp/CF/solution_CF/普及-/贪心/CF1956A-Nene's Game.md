# Nene's Game

## 题目描述

有 $n$ 个人玩一个游戏，把这 $n$ 个人分别编号为 $1$ 到 $n$。

每一轮，编号为 $ a_1, a_2, \ldots, a_k $ 的人会被踢出这个游戏，剩下的人会补齐空位并重新从 $1$ 开始编号。

当某一轮没有人被踢出时，游戏结束，剩下没有被踢出的人成为赢家。

现在请你求出最后会有多少人成为赢家。

由于 Nene 还没有确定参加游戏的具体人数，所以她会问你 $q$ 个问题，请你对 $q$ 个 $n$ 分别给出答案。

## 样例 #1

### 输入

```
6
2 1
3 5
5
5 3
2 4 6 7 9
1 3 5
5 4
3 4 5 6 7
1 2 3 4
2 3
69 96
1 10 100
1 1
100
50
3 3
10 20 30
1 10 100```

### 输出

```
2 
1 1 1 
1 2 2 2 
1 10 68 
50 
1 9 9```

# 题解

## 作者：zhouchuer (赞：4)

## [题目传送门](https://www.luogu.com.cn/problem/CF1956A)
本篇题解和以下这篇题解思路基本相同，但是笔者确实只想到了这一种方法，希望这篇题解的作者能谅解。本文会尽量讲的详细一些。

链接：[类似可参考文章](https://www.luogu.com.cn/article/dmkq0hii)。

### 思路
注意共有 $t$ 组数据，可以用一个 while 循环统计。

对于每一组数据，在第一个 for 循环中，输入 $k$ 个数 $a$，我们要找到可以被踢掉的人的编号中的最小值，为什么要找最小值呢？因为一轮游戏结束之后会从 $1$ 开始重新编号，只要有一个人的编号大于等于可以被踢出的人中最小编号，就可以踢人了。

第二个 for 循环，输入 $q$ 个数 $n$ 并输出答案，那么我们把人数和之前找到的可踢出编号中的最小值对比一下，如果 $n \le \min\{a_i\}$ 就输出 $\min\{a_i\} - 1$，否则一个人都踢不出去，直接输出 $n$。

注意，while 循环的每一轮开始之前都要有这么一句：
```c
int mn=INT_MAX;//设置成很大一个数
```
为什么要这样呢？你要知道一轮循环结束了数字可能很小，所以在每一轮开始前必须重置。

### 数据分析
由于本题数据较复杂，用样例中的部分数据说明一下。

首先有一组数据输入是这样的：
```c
5 3
2 4 6 7 9
1 3 5
```
然后分析一下，我们可以发现被踢出的人中最小编号为 $2$，那么就把 $3$ 个 $n$ 和 $2$ 对比，发现 $1$ 小于 $2$ 直接输出，$3$ 和 $5$ 都超过了 $2$，结果也都是 $1$，所以结果如下：
```c
1 1 1
```
这个太简单了，复杂一点的也举一个例子吧：
```c
2 3
69 96
1 10 100
```
我们发现可踢出的人中最小编号是 $69$，那么由于 $1$ 小于 $69$，答案是 $1$。然后 $10$ 也小于 $69$，答案是 $10$，最后 $100$ 大于 $69$，只要把 $69$ 减 $1$ 就行了，结果为 $68$。那么结果就是：
```c
1 10 68
```
很简单吧？以下是代码。

### 代码
```c
#include<bits/stdc++.h>
using namespace std;

int t,k,q;
int a,n;
int main() {
	cin>>t;
	while(t--) {
		int mn=INT_MAX;
		cin>>k>>q;
		for(int i=1;i<=k;i++){//更新最小值
			cin>>a;
			mn=min(mn,a);
		}
		for(int i=1;i<=q;i++){//选择是直接输出还是输出最小编号减一
			cin>>n;
			if(mn-1>=n){
            	cout<<n<<" ";  
        	}
			else{
              	cout<<mn-1<<" ";
			}
		}
		cout<<endl;
	}
	return 0;
}
```
记录：[提交通过](https://www.luogu.com.cn/record/158720072)。

---

## 作者：theb0t (赞：3)

这道题其实挺有意思，多测里面还套了个多测。

思路就是用向量模拟删除过程，具体请看代码里的注释。

```cpp
#include <bits/stdc++.h>
using namespace std;
int k,q,a[105];
void solve()
{
	int n;
	cin>>n;
	vector<int> ve;
	for(int i=1;i<=n;i++) ve.push_back(i);//把每个人放到向量里面
	while(!ve.size()<a[1]) //当还可以删除时
	{
		int cnt=1;
		/*
		 * cnt的作用
		 * 1. 把下标从0开始的ve与下标从1开始的a[]关联起来
		 * 2. vector的erase会自动补齐空位
		 * 如果没有cnt，第二次删除的则是错误的位置
		 * 所以用cnt统计目前删除了多少个数
		 * 
		 * (cnt为什么初始是1? 请看第一条)
		 *
		*/
		for(int i=1;i<=k;i++) 
			if(a[i]<=ve.size()) //当还可以删除时
			{
				ve.erase(ve.begin()+a[i]-cnt); //则删除，此时用上了cnt
				cnt++;//已删除+1
			}
	}
	cout<<ve.size()<<" ";
}
void Solve()
{
	cin>>k>>q;
	for(int i=1;i<=k;i++) cin>>a[i];
	sort(a+1,a+1+k); //排序是为了方便做这个 while(!ve.size()<a[1])
	while(q--) solve();//q次询问
	cout<<endl;
}
int main()
{
	int t;
	cin>>t;
	while(t--) Solve();//t组数据
	return 0;
}
```

---

## 作者：_Deer_Peach_ (赞：1)

这道题其实是一道比较简单的思维题。

#### 题意简述：
有 $n$ 个人编号分别为 $1$ 到 $n$，每轮有 $k$ 人被淘汰，分别为 $a_1$ 到 $a_k$。这道题挺有趣，多组数据里还加多组数据。

#### 思路：
根据规则，每一轮只会淘汰小于等于 $k$ 人，每次只会淘汰固定编号的人，那我们可以只考虑最小的那个编号：如果最小的编号都比总人数大，那么胜利的人就是 $n$；如果最小的编号等于总人数，那么只会淘汰这一个人，胜利者就是 $n-1$，相当于最小的编号减一；如果最小的编号比总人数小，那么最终只会剩下最小的编号减一个人。

看完可能有点不明白，那就举几个例子：

如果最小的编号比总人数小：
```
2 1
3 5
2
```
一共就 $2$ 人，哪来的 $3$ 和 $5$？直接输出 $2$。

如果最小的编号等于总人数：
```
2 1
2 3
2
```
这一次只能淘汰一个人，就是 $2$ 号，除了他就没人被淘汰了，所以答案就是最小的编号减一（总人数减一）。

如果最小的编号比总人数小：
```
2 1
3 5
4
```
每次淘汰 $3$ 号，直至没有 $3$ 号为止，答案为总人数减一。
#### 代码：
思路已经分析的很清楚了，接下来就是代码部分：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int t;
	cin>>t;
	while(t--){
		int k,q;
		cin>>k>>q;
		int a[k+1],n[q+1],minn=0x3f3f3f3f3f3f3f3f;
		for(int i=1;i<=k;i++){
			cin>>a[i];
			minn=min(minn,a[i]);
		}for(int i=1;i<=q;i++){
			cin>>n[i];
		}for(int i=1;i<=q;i++){
			if(n[i]-minn<0)cout<<n[i]<<" ";
			else cout<<minn-1<<" ";
		}cout<<endl;
	}
	return 0;
}
```

---

## 作者：___nyLittleT___ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1956A)  
## 题意
$n$ 个人，每次踢出一些人，再重新编号，问最后剩多少人。
## 思路
分两种情况讨论。  
- $n \ge \min\{a_i\}$，这时只要剩的人数 $x < \min\{a_i\}$ 就可以，答案为 $x=\min\{a_i\}-1$。
- $n<\min\{a_i\}$，这时踢不了一个人，答案为 $n$。

然后输出这两种情况最小值即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,k,q,a,n;
int minn;
int main() {
	scanf("%d",&t);
	while(t--) {
		minn=0x7f7f7f7f;//记得重载
		scanf("%d%d",&k,&q);
		for(int i=1; i<=k; i++){
			scanf("%d",&a);
			minn=min(minn,a);
		}
		for(int i=1; i<=q; i++){
			scanf("%d",&n);
			printf("%d ",min(minn-1,n));
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：zxh923 (赞：0)

# CF1956A Nene's Game 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1956A)

### 思路

可以发现一个小性质，由于 $a$ 已经有序，所以如果这个人站的位置不在 $a_1$ 前面，那么他如果不被后面的序号踢出去，就一定会被 $a_1$ 踢出去。

综上，我们发现，最终要么是人数太少 $a_1$ 踢不到，要么是被踢完了，于是答案是 $a_1-1$ 与 $n$ 的最小值。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,k,q;
void solve(){
	cin>>k>>q;
	int x,y;
	cin>>x;
	for(int i=2;i<=k;i++){
		cin>>y;
	}
	while(q--){
		int n;
		cin>>n;
		cout<<min(n,x-1)<<' ';
	}
	cout<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Hacker_Cracker (赞：0)

## CF1956A 题解
[站内地址](https://www.luogu.com.cn/problem/CF1956A)         [原址](http://codeforces.com/problemset/problem/1956/A)

#### 思路

由于  $a_i$  是升序排列的，所以每次会剩下  $a_1-1$  个人。

但是我们还需要注意，当 $n<a_1$ 时， $a_1-1$  可能会多减去一部分人，所以我们要判断  $n$  和  $a_1-1$  的最小值，即  $\min(n,a_1-1)$  。

注意多组测试数据。

#### [AC](https://www.luogu.com.cn/record/158137082)  代码：

```cpp
#include <iostream>
#include <cctype>
#include <cstring>
#include <map>
#define stO return
#define Orz 0 
#define m(x) memset(a , (x) , sizeof(a) );
using namespace std;
const int N = 1e2 + 10;
int a[N] , __T , n , k ,q;
inline rI() {
	int f = 1,res = 0;
	char ch = getchar();
	while (! isdigit (ch)) {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (isdigit (ch)) {
		res = res * 10 + (ch - '0');
		ch = getchar();
	}
	return res * f;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x>=10) write(x / 10);
	putchar((x % 10 ) + '0');
	stO ;
}
int main() {
	__T = rI();
	for (int i = 1 ; i <= __T ; i ++) {
		m(0);
		k = rI() , q = rI();
		for (int j = 1; j <= k ;j ++) {
			a[j] = rI();
		}
		for (int j = 1 ; j <= q ; j ++) {
			n = rI();
			write (min (a[1] - 1 , n)) , putchar (' ');
		}
		putchar ('\n');
	}
	stO Orz ;
}
```

至此本篇题解就完成了。

---

## 作者：ghx0052 (赞：0)

## 思路
简单贪心题,将 $a$ **排序**后统计结果即可。（注释中有更多细节的解释）
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[111], num[111];
bool idx_flag[111];
int main() {
	int t;
	cin >> t;
	while (t --) {
		int n, q;
		cin >> n >> q; // 输入 n, q
		for (int i = 1; i <= n; i ++) {
			cin >> a[i]; // 输入 a 数组 
		}
		for (int i = 1; i <= q; i ++) {
			cin >> num[i]; // 输入每次人数
		}
		sort(a + 1, a + 1 + n); // 排序（贪心重点！！！），以方便之后的判断 
		for (int x = 1; x <= q; x ++) {
            memset(idx_flag, 0, sizeof idx_flag);
			int q1 = num[x], ans = 0; // q1 当前剩下的数，ans 答案 
			while (1) {
                if (a[1] > q1) break; // 如果 a 中最小的下标都比当前剩下的数大，退出 
				int cnt = 0, now_idx = 1;
				for (int i = 1; i <= num[x]; i ++) { // 循环统计 
					if (!idx_flag[i]) cnt ++; // 模拟题目条件 
					if (cnt == a[now_idx]) idx_flag[i] = 1, now_idx ++; // 标记 
				}
				q1 -= now_idx, q1 ++; // 这里的 now_idx - 1 就是标记次数 
			}
			for (int i = 1; i <= num[x]; i ++) {
				if (!idx_flag[i]) ans ++; // 统计答案 
			}
			cout << ans << " "; // 输出 
		}
		cout << endl;
	}
}
```

---

## 作者：chenlongli (赞：0)

### 题意
现在有 $n$ 个人，每次编号为 $a_1,a_2,...,a_k$ 的人会被踢出游戏，问最后会留下几个人。
### 思路
因为题目中在 $a$ 中的最小值前面的人数就是答案，因为在 $a$ 中的最小值及以后的人一定会在某一次变为 $a$ 中最小值的编号，从而被踢出游戏，所以只要求出最小的 $a$ 减去 $1$ 就行了，不过有可能人数还不够最小的 $a$ 减 $1$，就要取总人数和最小的 $a$ 值 $-1$ 后两个的最小值。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t,zx,n,k,q;
    cin>>t;
    for (int i=0;i<t;i++)
    {
        cin>>n>>k;
        zx=10000000;
        for (int j=0;j<n;j++)
        {
            cin>>q;
            zx=min(zx,q);
        }
        for (int j=0;j<k;j++)
        {
            cin>>q;
            if (j!=k-1)
            {
                cout<<min(q,zx-1)<<" ";
            }
            else
            {
                cout<<min(q,zx-1);
            }
        }
        cout<<endl;
    }
}
```

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1956A)

## 思路

本题依照题目要求进行模拟即可。对于每次询问，都模拟一遍过程，直到当前的人数小于了当前的 $a_i$，就可以结束当前的询问了。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 110;

int a[N];

unordered_map<int, bool> mp;

int main(){
	int T;
	cin >> T;
	while(T--){
		int k, q;
		cin >> k >> q;
		for(int i = 1; i <= k; i++) cin >> a[i];
		while(q--){
			int n;
			cin >> n;
			int cnt = n;
			mp.clear();//清空。 
			while(cnt >= a[1]){ 
				int tmp = 0, c = 1;
				for(int i = 1; i <= n; i++){
					if(cnt < a[c]) break;//当前人数不够。 
					if(!mp[i]) tmp++;
					if(tmp == a[c]){
						c++; cnt--; mp[i] = true;//更新状态。
					}
				}
			}
			cout << cnt << " ";//输出当前的剩余人数。
		}
		cout << endl;
	}
}
```

---

## 作者：IOI_official (赞：0)

## 思路：

此题看起来很复杂，其实仔细推一推可以发现是有规律的。

分两种情况：

1. 当 $n\le min\left \{ a_{i} \right \}$ 时，答案为 $min\left \{ a_{i} \right \} -1$。

2. 当 $n> min\left \{ a_{i} \right \} $ 时，这时一个人都踢不了，所以答案为 $n$。

对于每一个 $n$，输出两种情况中的最小值即可。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,k,q,a,n;
int minn;
int main() {
	cin>>t;
	for(int j=1;j<=t;j++) {
		minn=1145141919;
		cin>>k>>q;
		for(int i=1; i<=k; i++) {
			cin>>a;
			minn=min(minn,a);//求最小的a[i]
		}
		for(int i=1;i<=q;i++) {
			cin>>n;
			cout<<min(minn-1,n);//输出两种情况中最优的。 
		}
		cout<<endl;
	}
	return 0;
}
```

---

