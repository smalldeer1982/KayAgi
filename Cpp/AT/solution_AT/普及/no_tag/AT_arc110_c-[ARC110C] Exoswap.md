# [ARC110C] Exoswap

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc110/tasks/arc110_c

$ 1,\ 2,\ \ldots,\ N $ を並び替えた数列 $ P\ =\ P_1,\ P_2,\ \ldots,\ P_N $ があります。

あなたは $ P $ に対して、以下の $ N\ -\ 1 $ 種類の操作を、任意の順番で**ちょうど $ 1 $ 回ずつ**行わなければなりません。

- $ P_1 $ と $ P_2 $ を入れ替える
- $ P_2 $ と $ P_3 $ を入れ替える
  
  $ \vdots $
- $ P_{N\ -\ 1} $ と $ P_N $ を入れ替える

操作の順番を適切に決めることで、$ P $ を昇順に並び替えてください。 もしそれが不可能な場合、`-1` を出力してください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ P $ は $ 1,\ 2,\ \ldots,\ N $ を並び替えた数列

### Sample Explanation 1

以下のような操作列が $ P $ を昇順に並び替えます。 - まず $ P_4 $ と $ P_5 $ を入れ替える。$ P $ は $ 2,\ 4,\ 1,\ 3,\ 5 $ になる - 次に $ P_2 $ と $ P_3 $ を入れ替える。$ P $ は $ 2,\ 1,\ 4,\ 3,\ 5 $ になる - 次に $ P_3 $ と $ P_4 $ を入れ替える。$ P $ は $ 2,\ 1,\ 3,\ 4,\ 5 $ になる - 次に $ P_1 $ と $ P_2 $ を入れ替える。$ P $ は $ 1,\ 2,\ 3,\ 4,\ 5 $ になる

## 样例 #1

### 输入

```
5
2 4 1 5 3```

### 输出

```
4
2
3
1```

## 样例 #2

### 输入

```
5
5 4 3 2 1```

### 输出

```
-1```

# 题解

## 作者：dongzhenmao (赞：4)

## 题目链接:
+ [**link**](https://www.luogu.com.cn/problem/AT_arc110_c)，点击这里喵。
## 题意简述:
+ 给出一个排列，长度为 $n$ 问是否能通过 $n-1$ 次交换（第 $i$ 位有且仅可以与 $i+1$ 位交换一次），使这个排列**递增**（必须交换 $n-1$ 次）。 
## 思路:
+ **仅**能使用一次，这意味着如果右边有一个数**应**在这个位置的左边，那么通过这**仅有一次机会**。 
+ 如果这一个机会被占用了，那么这个数就**不能**归位了喵 ~
## 做法:
+ 所以，应当使当前未归位**最小数**先归位，否则左边的交换会阻止其到达， 右边的交换则对此**无影响**。 
+ 定义一个变量 $use$ 为使用过的**右**侧边界，若当前要归位的数在 $use$ 左边，说明已经使用过，则不可行。 
```cpp
if(i<=use && date[i]!=i){
    puts("-1");          
    return 0;            
}             
```
+ 持续这样操作，直到所有数归位。
```cpp
for(int i=1;i<=n;++i){
    if(i<=use && date[i]!=i){
        puts("-1");
        return 0;
    }
    use=zb[i]-1;
    for(int e=use;e>=i;--e){
        swap(date[e],date[e+1]);
        zb[date[e]]=e;
        zb[date[e+1]]=e+1;
        ans.push_back(e);
    }
}
```
+ 当结束循环后，查看是否使用了 $n-1$ 次。
```cpp
if((int)ans.size()!=n-1){puts("-1");return 0;}
``````
## 小贴士:
+ 上述代码中使用了 $zb$ 数组来存储每个数的位置，而 $date$ 数组则是存每个位置是什么数，记得两个都要更新喵。 
+ 这里使用了 $\texttt{vecotr}$ 来存储答案，蒟蒻认为这样简单一些。 
## 时间复杂度分析
+ 由于 $use$ 每个点只能有一次，而 $use$ 单调不降，最多对 $use$ 进行 $n$ 次操作，故时间复杂度为 $O(n)$。 
## 代码:

```cpp
#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#include <vector>
#define lnt long long
using namespace std;
int xx;char ff,chh;inline int read(){
    xx=ff=0;while(!isdigit(chh)){if(chh=='-'){ff=1;}chh=getchar();}
    while(isdigit(chh)){xx=(xx<<1)+(xx<<3)+chh-'0';chh=getchar();}return ff? -xx: xx;
}
const int N=1e6;
int n,use,date[N],zb[N];
vector<int> ans;
int main(){
    n=read();
    for(int i=1;i<=n;++i){
        date[i]=read();
        zb[date[i]]=i;
    }
    for(int i=1;i<=n;++i){
        if(i<=use && date[i]!=i){
            puts("-1");
            return 0;
        }
        use=zb[i]-1;
        for(int e=use;e>=i;--e){
            swap(date[e],date[e+1]);
            zb[date[e]]=e;
            zb[date[e+1]]=e+1;
            ans.push_back(e);
        }
    }
    if((int)ans.size()!=n-1){puts("-1");return 0;}
    for(auto i: ans){printf("%d\n",i);}
    return 0;
}
```

---

## 作者：Confringo (赞：3)

### 思路
首先看到题面，第一个想到的算法应该是冒泡排序。因为冒泡排序就是每次交换相邻两个大小不满足题述关系的数。

但是这道题限制了相邻两个位置只能进行一次交换，这要怎么办呢？

我们回归冒泡排序的原理，是每一轮把一个最大（小）的数归位到最左边（最右边），那么既然题目要求的顺序是升序，我们就可以大胆猜测，每一次先把未归位的最大的数归位，然后如果交换过程中出现重复，那么一定不可能做到。

同时，我们没有必要记录所有位置有没有交换过，只要记录被交换过的最左边的位置即可。因为在先归位最大数的策略下，每一次归位后最大数原先位置到 $n$ 的位置都一定无法再次使用。

---
### 正确性证明
**先把最大的数归位一定是最优选择。**

如果不先归位最大的数，那么比当前归位的数小的数可能会被堵在右边。我们设当前归位的数为 $x$。

例如 $[1,3,4,5,2]$，如果选择先归位 $4$ 的话，由于归位 $4$ 后数组变为 $[1,3,5,4,2]$，这时 $2$ 就会被堵在里面，出不来，否则就会打乱 $4$ 的位置，此时先归位 $4$ 就失去了意义。

如果 $x$ 右侧全都是比 $x$ 大的数，那么这就等同于先归位最大的数，因为此时 $x$ 右边的交换次数都没有被使用，就相当于又一个归位问题，就可以用同样的方法（先归位最大的数）解决。

因为最大的数无论如何都要到最右边去，所以与其因为中间的数交换被堵住一定失败，不如先把最大的数归位。

先把最大的数归位一定不劣于其他方案。综上，采取先归位最大的数的方案最好。

---
### 空间复杂度
需要一个数组记录输入的所有数，一个数组记录交换顺序，一个数组记录每个数当前的位置，共 $\mathcal{O}(n)$。

---
### 时间复杂度
分类讨论如下：

如果不可行，在交换 $n-1$ 次后必然会发现矛盾，$\mathcal{O}(n)$。  
如果可行：必定交换 $n-1$ 次，$\mathcal{O}(n)$。

故时间复杂度为 $\mathcal{O}(n)$。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010],n,pos[200010],ans[200010],cnt,used;
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        pos[a[i]]=i;//记录每个数所在位置
    }
    int now=n;used=n+1;
    while (true){
        if (now<=0) break;//如果所有数都已归位，结束循环
        if (pos[now]==now){//如果已经归位，不管
            now--;continue;
        }
        else{
            int temp=pos[now];
            if (now-1>=used){
            	//如果最右侧一次交换已被使用，则一定无法完成
                //used 记录的是从 used 到 n 的交换都不能进行
                puts("-1");
                return 0;
            }
            for (int i=pos[now];i<now;i++){
                ans[++cnt]=i;
                swap(pos[now],pos[a[i+1]]);
                swap(a[i],a[i+1]);
            }//暴力交换
            used=temp;//已交换的位置不能再交换
        }
        now--;//继续归位第二大数
    }
    if (cnt!=n-1){//如果次数没用完输出 -1
        puts("-1");
        return 0;
    }
    for (int i=1;i<=cnt;i++){
        printf("%d\n",ans[i]);
    }
    //AT 不换行，WA 两行泪
    return 0;
}
```

---

## 作者：_xzhdsnh1364 (赞：3)

# 前言

本人也是参考了一下别人的才有些思路的（~~当然是因为我太蒟了~~）

# 题意理解

可能有一部分人和我一样，一看到题就一连蒙，这边题面意思就是一个序列含有 $1 \sim n$，让每一个编号对应上 $1 \sim n$，进行 $n-1$ 次交换相邻元素操作，最后输出任意一种可行的每一次交换的 $i$ 与 $i+1$ 的 $i$，若没有输出 $-1$。

题意就解释到这。

# 思路

思路这边我们分两个模块，判 $-1$ 与找出每次交换的位置。

1.判 $-1$

有两种输出 $-1$ 的情况，讲第一种前先介绍几个变量与数组，$r$、$a$、$w$，分别表示最右边搜索过的下标，每一个数代表的序列，每个数的位置，认识了这些东西，就可以继续往下看了。

- 当当前扫到的数在右边界的左边但没有归位输出 $-1$。

- 最后输出时不是经过了 $n-1$ 次交换输出 $-1$。

2.找出每次交换的位置

使用一次 for 循环遍历每一个数组中的数并进行交换，每一次交换操作可以用数组或 vector 容器存储，这边我就示范数组做法吧。每一次我们都要刷新一次右边界变为当前这个位置应有的数的位置减一，再套一层循环，从右区间遍历至当前的 $i$，每次对相邻数进行交换操作，记得每次调换位置数组并将交换位置存入数组，最后输出。

以上便是本题的思路了。

# AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int n , a[200005] , r , w[200005] , b[200005] , cur;
int main(){
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        w[a[i]] = i;//每个数的位置
    }
    for(int i = 1;i <= n;i++){
        if(i <= r && a[i] != i){//第一种输出-1的情况
            cout << -1;
            return 0;
        }
        r = w[i] - 1;//更新右区间
        for(int j = r;j >= i;j--){
            //交换操作
            swap(a[j] , a[j + 1]);
            w[a[j]] = j;
            w[a[j + 1]] = j + 1;
            b[++cur] = j;//存入数组
        }
    }
    if(cur != n - 1)cout << -1;//第二种输出-1的情况
    else{
        for(int i = 1;i <= cur;i++)cout << b[i] << '\n';//最后的输出
    }
    return 0;//华丽结束
}
```

# 后记

CSP 备战时发布，不易求赞，另外祝各位 CSP-J/S 2024 rp++。

###### 致谢各位

---

## 作者：FL_sleake (赞：2)

### 题意简述

一个长度为 $N$ 的序列，有 $N-1$ 次机会交换相邻两个数，且每两个位置上的数仅有一次机会进行交换，最终用完所有 $N-1$ 次交换使这个无序序列变为单调上升序列。如果可以，则按顺序输出每次交换的位置；如果不行，输出 $-1$。

### 解题思路

冒泡排序啥的还是太复杂了，考虑直接硬干。

首先我们证明每次只能交换 $a_i>a_{i+1}$ 的位置。我们假设第一次交换了**下标**为 $i,i+1$ 的位置。当交换完 $i,i+1$ 之后，就相当于在它们之间划了一道屏障，之后无论怎么交换，下标为 $1$ 到 $i$ 的数都不可能跑到 $i$ 右边，下标为 $i+1$ 到 $n$ 的数也都不可能跑到 $i+1$ 左边。因此，如果我们交换了某个 $a_i<a_{i+1}$ 的位置，那么就产生了一对逆序对，**并且这对逆序对无论无何都是无法消除的**。由此启发我们，只有每次消除一个逆序对，也即只有逆序对数恰好为 $n-1$ 时，才有可能有解。

因此我们直接找每次能交换的位置，将下标丢进队列里，交换后再往前判断一次，往后判断一次即可。此处，若 $a_i>a_{i+1}$，称 $i$ 为能交换的位置。

更具体地说，若当前要交换 $i,i+1$ 位置，先判断这个位置之前有没有被交换过，若被交换过，输出 `-1`。否则，交换这两个位置。再判断 $i-1,i$ 是否需要交换，$i+1,i+2$ 是否需要交换，需要则丢进队列。最后记得再判一下总交换次数是否为 $n-1$。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,vis[200010],a[200010];
queue<int> q;
vector<int> ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++) if(a[i]>a[i+1]) q.push(i);
	while(!q.empty()){
		int id=q.front();q.pop();
		if(vis[id]){
			cout<<-1<<endl;
			return 0;
		}
		ans.push_back(id);
		vis[id]=1;
		swap(a[id],a[id+1]);
		if(id>1&&a[id-1]>a[id]) q.push(id-1);
		if(id+1<n&&a[id+1]>a[id+2]) q.push(id+1);
	}
	if(ans.size()!=n-1) cout<<-1<<endl;
	else for(int x:ans) cout<<x<<endl;
	return 0;
}
```

---

## 作者：Pretharp (赞：2)

讲一个比楼上简单很多的方法。

不难发现，因为每相邻的两个位置最多交换一次，也就是说一个数的位置必然非严格单调递增或者非严格单调递减，举例：

- 对于数列 $A=\{3,1,2\}$，如果交换 $A_2$ 和 $A_3$，那么 $A=\{3,2,1\}$，很显然，之后 $A_3=1$ 将无法再回到原本的位置（因为位置 $2$ 和 $3$ 已经交换过，$A_3$ 将无法通过交换使位置变为 $1$ 或 $2$）。

因此，对于 $1\le i<N$，当我们要交换 $A_i$ 和 $A_{i+1}$ 当且仅当 $A_i>i$ 且 $A_{i+1}<i+1$，同时也很容易发现如果要使 $A_i$ 和 $A_{i+1}$ 归位就必需交换 $A_i$ 和 $A_{i+1}$，与什么时候交换无关。接下来就很简单了，先扫一遍数组，对于每一个满足上述条件的 $i$，将其装进一个队列，每次处理完队头（设其为 $x$）再看看 $A_x$ 和 $A_{x-1}$ 能不能交换以及 $A_{x+1}$ 和 $A_{x+2}$ 能不能交换，若能则加入队列，重复直至队列为空。

记得判断是否无解。

[代码](https://atcoder.jp/contests/arc110/submissions/43746015)

---

## 作者：FISH酱 (赞：1)

## 思路

通过题目描述后，是个人都会想到冒泡排序。因为冒泡排序与题目要求大部分相符。但是对于每两个元素只能交换一次，因此需要在冒泡上进行部分修改实现。

冒泡排序的原理每一轮把一个极端值放在一个极端位置上，我们需要排为升序，那么我们就可以利用冒泡的原理进行以下操作：

每一次先把未归位的最大的数归位，如果交换过程出现了交换多次相同数字的情况，那么一定不可能做到，直接输出 $-1$。

## 补充说明

我们来看一下交换部分怎么写：

```cpp
while(i != b[i]){
    c[b[i]]++;
    d[q] = b[i];
    q++;
    swap(a[b[i]], a[b[i]+1]);
    swap(b[a[b[i]]], b[a[b[i]+1]]);
}
```

还是看看完整代码吧：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double
#define endl "\n"

int n,u,sum;
string ans="";
int a[2000000];
int cnt[2000000];

void bubble_sort(int n) {
    for(int i=1;i<=n;i++){
      	if(i<=u && a[i]!=i){
      		cout<<-1<<endl;
      		return;
		}
		
		u=cnt[i];u--;
		
		for(int j=u;j>=i;j-=1){
			swap(a[j],a[j+1]);
			
			cnt[a[j]] = j;
			cnt[a[j+1]] = j+1;
			
			ans += to_string(j)+"\n";
			sum++;
		}
    }
    
	if(sum!=n-1){
		cout<<"-1\n";
	}else{
		cout<<ans;
	}
}

int main(){
	cin >> n;
	
	for(int i=1;i<=n;i++){
		cin>>a[i];cnt[a[i]]=i;
	}
	
	bubble_sort(n);

	return 0;
}
```

---

## 作者：Chenaknoip (赞：0)

观察这道题，可以联想到冒泡排序。但这道题加了一个限制：同一位置的交换次数必须是一次。

因此，可以不断地将数列中的最大值移动到末尾，并记录下每个位置是否发生过交换。如果发现曾经交换过则返回错误。与此同时，还应在排序完成后检查是否正好交换了 $n-1$ 次。

实现细节见代码。由于交换 $n-1$ 次，复杂度为 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, a[N], b[N];
bool used[N];
vector<int> v;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[a[i]] = i;
    }
    for (int i = n; i >= 1; i--) {
        if (b[i] > i) {
            printf("-1\n");
            return 0;
        }
        while (b[i] != i) { // 交换过程，优先将大的数移动到末尾
            int tmp = b[i];
            if (used[tmp]) {
                printf("-1\n");
                return 0;
            }
            b[i]++;
            b[a[b[i]]]--;
            swap(a[tmp], a[tmp + 1]);
            v.push_back(tmp);
            used[tmp] = true;
        }
    }
    if (v.size() != n - 1) { // 不是 n-1 步
        printf("-1\n");
        return 0;
    }
    for (int i = 0; i < n - 1; i++) printf("%d\n", v[i]);
    return 0;
}
```

---

## 作者：New_hope (赞：0)

显然合法的一个必要条件是 **有且仅有** $n - 1$ 个逆序对，这个用树状数组判一下。

然后模拟冒泡，在交换的时候判断该位置是否被操作了两次。

但这样会被如下的两组数据卡掉。

$$
1,n-1,n-2,....2
$$

或

$$
n,1,2,...,n-1
$$

我们一开始就把这样的极端数据判掉。

因为数据过水，如上的 $O(n^2)$ 可过。

参考代码：


```cpp
#include <bits/stdc++.h>
#define _ 200005
using namespace std;

int n;
int p[_], ans[_];
bool tg[_];

struct BIT
{
  int t[_];
  int lb (int x) { return x & (-x); }
  void insert (int x) {
    while (x <= _ - 1) {
      t[x] += 1;
      x += lb(x);
    }
  }
  int q (int x) {
    int r = 0;
    while (x) {
      r += t[x];
      x -= lb(x);
    }
    return r;
  }
} tr;

bool check(int n)
{
  bool f = 1;
  f &= (p[1] == n);
  for (int i = 2; i <= n; i ++) {
    f &= (p[i] == (i - 1));
  } return f;
}
int main()
{
  scanf ("%d", &n);
  
  int c = 0;
  for (int i = 1; i <= n; i ++) {
    scanf ("%d", &p[i]);
    int l = tr.q(p[i] - 1), r = tr.q(n);
    c += r - l;
    tr.insert(p[i]);
  }
  if (c != n - 1) { cout << -1; return 0; }

  int t = 0;
  if (check(n)) {
    for (int i = 1; i < n; i ++) cout << i << ' ';
    return 0;
  }
  while (c) {
    for (int i = n - 1 ; i >= 1; i --) {
      if (p[i] > p[i + 1]) {
        if (tg[i]) { cout << -1; return 0; }
        tg[i] = 1;
        swap (p[i], p[i + 1]);
        ans[++t] = i;
        c --;
      }
      if (c <= 0) break;
    }
  }
  for (int i = 1; i < n; i ++) {
    printf ("%d\n", ans[i]);
  }

  return 0;
}
/*
g++ AT_arc110_c.cpp -o c.exe -O2 -std=c++14
*/
```

---

## 作者：XYQ_102 (赞：0)

[原题传送门](https://atcoder.jp/contests/arc110/tasks/arc110_c)
## 思路
交换两个相邻的元素，逆序对增减量为 $1$。那么如果总逆序对个数多于 $n$ 个，显然 `Impossible`。

如果有三个连续元素递减，那么显然 `Impossible`。

对于所有连续逆序对 $P_i>P_{i+1}$，将 $i$ 放入队列中，依次处理：
  - 每次取出队首，如果仍然为逆序对，那么交换，`cnt++`；
  - 判断前一个和后一个，如果出现逆序对，入队；
- 最后判断是否恰好交换 $n−1$ 次，和是否所有元素都归位。
## 代码
```cpp
//Author: XYQ_102
#define lowbit(x) ((x)&(-x))
#define PII pair<int,int>
const int N=2e5+10;
int n,p[N],c[N],ans[N];
queue<int> q;

void add( int x,int val ) { for ( ; x<=n; x+=lowbit(x) ) c[x]++; }
int get_sum( int x ) { int res=0; for ( ; x; x-=lowbit(x) ) res+=c[x]; return res; }

int main()
{
	n=read(); 
	for ( int i=1; i<=n; i++ )
		p[i]=read();
	
	int cnt=0;
	for ( int i=n; i>=1; i-- )
	{
		cnt+=get_sum( p[i]-1 );
		if ( cnt>n ) { printf( "-1" ); return 0; }
		add( p[i],1 );
	}
	if ( cnt>n ) { printf( "-1" ); return 0; }
	for ( int i=1; i<n-1; i++ )
		if ( (p[i]>p[i+1]) && (p[i+1]>p[i+2]) ) { printf( "-1" ); return 0; }
	for ( int i=1; i<n; i++ )
		if ( (p[i]>p[i+1]) ) q.push( i );
	cnt=0;
	while ( !q.empty() )
	{
		int u=q.front(); q.pop();
		if ( p[u]>p[u+1] ) swap( p[u],p[u+1] ),ans[++cnt]=u;
		if ( (u>1) && (p[u-1]>p[u]) ) q.push( u-1 );
		if ( (u<n-1) && (p[u+1]>p[u+2]) ) q.push( u+1 );
	}
	
	if ( cnt!=(n-1) ) { printf( "-1" ); return 0; }
	for ( int i=1; i<=n; i++ )
		if ( p[i]!=i ) { printf( "-1" ); return 0; }
	for ( int i=1; i<n; i++ )
		printf( "%d\n",ans[i] );
}
```

---

## 作者：Tulip_ (赞：0)

### 题意

#### 问题陈述

我们有一个 $1, 2, \ldots, N$ 的排列组合 $P = P_1, P_2, \ldots, P_N$。

你必须按一定的顺序对 $P$ 进行以下 $N - 1$ 次运算，**每次正好**一次：

- 交换 $P_1$ 和 $P_2$。

- 交换 $P_2$ 和 $P_3$。

  $\vdots$

- 将 $P_{N-1}$ 和 $P_N$ 对调。

您的任务是通过配置操作顺序，将 $P$ 按升序排序。如果不可能，则打印 `-1`。

### 思路

使用数组 $b$ 来储存每一个数的位置。

- 依次判断：**数是否在正确的位置，数是否在正确的位置的左边，数是否在正确的位置的右边。**

再用数组 $c$ 和数组 $d$ 来**储存交换的位置。**

- 运用 `swap` 来交换数组中数的位置。

接着用变量 $q$ 来**标记。**

- 如果变量 $q \ge n$ 说明不满足，输出 `-1`。

循环判断完之后，我们还需要判断每一个数**是否在该在的位置上。**

- 如果不在该在的位置上，那就输出 `-1`；否则**输出方案**。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int a[N],b[N],c[N],d[N];
int main(){
	int  q=0,flag=0;;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],b[a[i]]=i;
	for(int i=n;i>=1;i--){
		if(i>b[i]) 
			while(i!=b[i]){
				c[b[i]]++;
				d[q++]=b[i];
				swap(a[b[i]],a[b[i]+1]);
				swap(b[a[b[i]]],b[a[b[i]+1]]);
				if(q>=n){
					flag=1;
					break;
				}
			}
		 else if(i<b[i]) 
			while(i!=b[i]){
				c[b[i]-1]++;
				d[q++]=b[i]-1;
				swap(a[b[i]],a[b[i]-1]);
				swap(b[a[b[i]]],b[a[b[i]-1]]);
				if(q>=n){
					flag=1;
					break;
				}
			}
		if(q>=n){
			flag=1;
			break;
		}
	}
	for(int i=1;i<n;i++)
		if(c[i]!=1)
			flag=1;
	if(flag==1)  cout<<-1;
	else
		for(int i=0;i<q;i++)
			cout<<d[i]<<endl;
	return 0;
}
```

**~~就完成啦！~~**

#### [AC](https://www.luogu.com.cn/record/162783197)

---

## 作者：DuZhaoR (赞：0)

# 可爱的题解

不知道其他人怎么做的。

我的做法是画一个有向图，来表明每个操作的顺序关系，如果有环就证明无法变成升序序列。具体的解释如这个例子：

```
6
4 1 2 5 6 3
```

我们从 $1$ 开始遍历：

- $1$ 需要进行交换 $1$
- $2$ 需要进行交换 $2$
- $3$ 需要进行交换 $5$ -> $4$ -> $3$ -> $2$
- $4$ 需要进行交换 $1$ -> $2$ -> $3$
- $5$ 需要进行交换 $4$
- $6$ 需要进行交换 $4$

将所有箭头做成有向图：

![可爱的图片](https://cdn.luogu.com.cn/upload/image_hosting/tigkpmjm.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以允许的交换顺序是 $5$ -> $4$ -> $1$ -> $2$ -> $3$ 或 $5$ -> $1$ -> $2$ -> $4$ -> $3$ 或 $5$ -> $1$ -> $4$ -> $2$ -> $3$ 或 $1$ -> $2$ -> $5$ -> $4$ -> $3$ 或 $1$ -> $5$ -> $2$ -> $4$ -> $3$ 或 $1$ -> $5$ -> $4$ -> $2$ -> $3$。

同时注意这个例子：

![灰常可爱の图片](https://cdn.luogu.com.cn/upload/image_hosting/ez2r3mc0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果我们给每个点全部遍历的话，初始化有向图阶段遍历交换 $1$ 与交换 $5$  带来的后继就会被遍历 $2$ 次，因此这样做的复杂度为 $O(n^2)$ 会爆。所以我们应该在初始化有向图阶段碰到遍历过的点时就剪枝。这会导致图中没有环而无法判断可行性，我们只需要检查最后交换完成的图是否升序就行了。

上代码：

```c++
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int first[N],nxt[N],to[N],tot,son[N],req[N],l=1,r,n,b[N];
bool mp[N];
void add(int x,int y){
	nxt[++tot]=first[x];
	first[x]=tot;
	to[tot]=y;
	++son[y];
	return;
}
struct numb{
	int x,i;
	bool operator < (numb b){return x<b.x;}
}a[N];
int main(){
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	memset(mp,0,sizeof(mp));
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i].x);
		b[i]=a[i].x;
		a[i].i=i;
		if(i>a[i].x)for(int j=i-2;j>=a[i].x;--j){
			add(j+1,j);
			if(son[j]>1)break;
		}else if(i<a[i].x)for(int j=i;j<=a[i].x-2;++j){
			add(j,j+1);
			if(son[j+1]>1)break;
		}else goto imp;
	}
	for(int i=1;i<n;++i)
		if(son[i]==0)req[++r]=i;
	while(l<=r){
		int x=req[l];
		++l;
		mp[x]=1;
		for(int e=first[x];e;e=nxt[e]){
			int u=to[e];
			if(mp[u]){
				if(son[u]!=0) goto imp;
				continue;
			}
			--son[u];
			if(son[u]==0)req[++r]=u;
		}
	}
	if(r!=n-1)goto imp;
	for(int i=1;i<=r;++i)swap(b[req[i]],b[req[i]+1]);
	for(int i=1;i<=n;++i)if(b[i]!=i)goto imp;
	for(int i=1;i<=r;++i)printf("%d\n",req[i]);
	return 0;
	imp:printf("-1");
	return 0;
}

---

