# Vasya and Books

## 题目描述

Vasya 有 $n$ 本书，编号从 $1$ 到 $n$，放在一个栈中，最上面的书的编号为 $a_{1}$，下一本书为 $a_{2}$，以此类推，栈底部的书编号为 $a_{n}$，所有书的数字都是不同的。

Vasya 想在 $n$ 次操作下，把所有书都移动到他的背包里，在第 $i$ 次操作中他想移动编号为 $b_{i}$ 的书到他的包里，如果这本书还在栈中，他将取走 $b_{i}$ 和 $b_{i}$ 以上的所有书，并且将它们都放到包里，否则他什么都不需要做，并且开始取下一本书。

请你帮助 Vasya，告诉他每一步他要取走几本书。

翻译提供：@Maysoul

## 说明/提示

$1\le n \le 2\times 10^{5}$。

$1\le a_{i}, b_i \le n $。

$1\le b_{i} \le n $。


在样例 $2$ 中，第一步 Vasya 取走了编号为 $4$ 及以上的三本书，在那之后，只有编号为 $2$ 和 $5$ 的书还在栈中，并且 $2$ 在 $5$ 上面，在下一步 Vasya 取走了编号为 $5$ 及以上的两本书，在之后的操作中，没有书可以再被移动了。

## 样例 #1

### 输入

```
3
1 2 3
2 1 3
```

### 输出

```
2 0 1 
```

## 样例 #2

### 输入

```
5
3 1 4 2 5
4 5 1 3 2
```

### 输出

```
3 2 0 0 0 
```

## 样例 #3

### 输入

```
6
6 5 4 3 2 1
6 5 3 4 2 1
```

### 输出

```
1 1 2 0 1 1 
```

# 题解

## 作者：梦里调音 (赞：5)

哇，绿题。

以下提供我的解题过程

注意是**过程**，所以，错误是正常滴

一开始，我是想用一个bool数组标记来着，但。。。

会超时。~~（也就1个点）~~


代码：

```
#include <bits/stdc++.h>
using namespace std;
//    编号的位置    编号          查找号码 
int pl[1000001],id[1000001],n,b[10000001];
bool f[10000001];//用来标记编号 
int main(){
	int i,j,k;
	cin>>n;
	memset(id,-1,sizeof(id));
	for(i=1;i<=n;i++)cin>>id[i],pl[id[i]]=i;
	for(i=1;i<=n;i++){
		cin>>b[i];
		if(f[b[i]]==1){
			cout<<"0 ";
			continue;
		}
		int c=0;
		for(int p=1;p<=pl[b[i]];p++)//这里就是超时问题所在
			if(f[id[p]]==0){//冗长的判断
				f[id[p]]=1;c++;
			}
		cout<<c<<" ";
	}
	return 0;
}
```


后来，想了一下，

```

		for(int p=1;p<=pl[b[i]];p++)
			if(f[id[p]]==0){
				f[id[p]]=1;c++;
			}
		cout<<c<<" ";
	}

```
这段判断太~~tmd~~耗时间了

有些书都已经被取走了，还要来走一遍过程，明显没必要

*于是，我开始用depth来记录取书的深度

*再输入查找号码是直接判断，比深度浅就肯定被取走了，输出“0 ”

*比深度深才来输出深度差，并且更新depth

```
#include <bits/stdc++.h>
using namespace std;
//    编号的位置    编号        查找号码 
int pl[1000001],id[1000001],n,b[10000001];
int depth;//深度 
int main(){
	int i,j,k;
	cin>>n;
	memset(id,-1,sizeof(id));
	for(i=1;i<=n;i++)cin>>id[i],pl[id[i]]=i;
	for(i=1;i<=n;i++){
		cin>>b[i];
		int c=pl[b[i]];
		if(c<depth){
			cout<<"0 ";
			continue;
		}
		cout<<c-depth<<" ";
		depth=c;
	}
	return 0;
}
```

好啦，就这么多

看来我还是太水了qwq

---

## 作者：zsc2003 (赞：5)

# codeforces 1073B div2 2018.10.25

## 题目大意:

给定 $n$ 本书,序号分别为$1$到$n$，现在执行$n$个操作，
第$i$个操作需要从栈内取出编号为$b_i$的书，如果该书已经取出，则输出```0```否则将该书从栈内取出，同时取出在栈内比$b_i$靠上的书，并且输出一共取出了几本书

下面附上我的代码

```
#include<bits/stdc++.h>
#define ll long long
#define ri register int
using namespace std;
inline int read()//读入优化
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}
const int N=210000;
int n,num,b,top;
int st[N];
bool vis[N];
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		st[i]=read(),vis[i]=1;//标记还在栈内
	top=1;//以栈的形式读入
	for(int i=1;i<=n;i++)
	{
		b=read();
		num=0;
		if(vis[b])//将书从栈内取出
		{
			while(st[top]!=b)
			{
				vis[st[top++]]=0;
				num++;
			}
			vis[st[top++]]=0;
			num++;
		}
		printf("%d ",num);
	}
	return 0;
}
```

---

## 作者：decoqwq (赞：1)

昨晚$cf$只切了四道题的蒟蒻来写个题解

这道题给你一个数列的两种排列，让你求出对于第二个排列中的每个数，删去它在第一个数列的位置的前面的所有数要删几个(前面删完的后面就不用再计算)

这个题很简单啊，我们直接记录每个点在第一个序列中的位置，用一个$map$存一下，然后存现在删除到第几个数了，因为删除的都是这个数原位置之前的，所以我们如果发现当前数字原位置小于删除到的数位置就输出$0$，否则输出中间数字个数并且更新删除到第几个了就可以了qwq

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
map<int,int> mp;
int xian[200010];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        mp[x]=i;
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&xian[i]);
    }
    int las=0;
    for(int i=1;i<=n;i++)
    {
        if(mp[xian[i]]>las)
        {
            cout<<mp[xian[i]]-las<<" ";
            las=mp[xian[i]];
        }
        else
        {
            cout<<0<<" ";
        }
    }
    
}
```

---

## 作者：Fantasy_421 (赞：0)

蒟蒻的第一篇题解，这道题居然是个绿题，其实完全可以用队列来进行模拟，实现取书的操作。
先将所有书入队，把队列第一个元素看成栈顶元素，由于题目只要求进行取书操作，直接把书取出来就行，相当于只有弹栈的操作，把弹栈操作换成出队，每次出队直到找到需要取得书为止。把弹出去的书标记一下，访问过得就不在队列里，直接输出0就是了，没有访问的加个计数器，访问过程中把出队的元素标记一下，最后输出计数器的值就OK。

代码如下：
```
#include <iostream>
#include <queue>
using namespace std;
int vis[200500];
int main()
{
    int n;
    queue <int> q;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        q.push(x);
    }
    while(n--)
    {
        int x,k=1;
        cin>>x;
        if(vis[x])
        {
            cout<<0<<' ';
        }
        else
        {
            while(q.front()!=x)
            {
                vis[q.front()]=1;
                q.pop();
                k++;
            }
            q.pop();
            cout<<k<<' ';
        }
    }
}
```


---

## 作者：HDWR (赞：0)

粗略看了一下 貌似没人和我的解法相同

那就来写一发题解吧

在读入的时候 我们用另一个数组`lead[i]`来存编号为`i`的书在**读入的数组`book[]`**的下标

这样我们在检测读入的书是否被取出时就不用遍历一遍`book[]`

---

弹出书本的时候，我们首先看一下这个书本是否被取出 

如果是就直接输出`0 `

否则就开始弹出书本

---

我们用一个变量`now = 0`记录当前弹出了几个书本，用一个数组`vis[i]`记录第`i`本书是否被弹出

在弹出之前，用一个变量`orin`记录一下**还没更新**的`now`

接着在每次弹出的时候更新`vis[++now]`为真，直到遇到当前要弹出的书本编号

最后`orin - now`即为答案

---

代码实现：

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::string;

const int MAXN = 2e5 + 10;

int n;
int book[MAXN];
int lead[MAXN];
bool vis[MAXN];

int now = 0;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", book + i);
        lead[book[i]] = i;
        // 让lead[]作为book[]的索引，查找的时候快一些
    }
    for (int i = 1; i <= n; ++i) {
        int o;
        scanf("%d", &o);
        if (vis[lead[o]]) printf("0 ");
        // 被弹过了，输出0
        else {
            int orin = now;
            while (book[++now] != o) {
                vis[now] = true;
                // 循环更新vis（弹出书本）
            }
            vis[now] = true;
            printf("%d ", now - orin);
        }
    }
    return 0;
}

```

~~总感觉自己的代码能被 Hack~~

---

## 作者：liuyz11 (赞：0)

原比赛题解：[https://www.cnblogs.com/nblyz2003/p/9909038.html](https://www.cnblogs.com/nblyz2003/p/9909038.html)
B.Vasya and Books

题意：有n本书在一个栈中，依次为a1, a2, …, an，现在有n个操作，对于每个操作i，将从栈顶到书本bi的所有书全部放入包中，如果已经在包中，就不进行操作。问你每次操作需要放几本书。

这题可以记录下对于每本书i在栈中的位置posi，然后再记录上一次操作后放入包的书本数used，假如posbi  < used， 那么这次需要放入used - posbi 本书，否则就为0。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define rep(x, l, r) for(int x = (int)l; x <= (int)r; x++)
#define repd(x, r, l) for(int x = (int)r; x >= (int)l; x--)
#define clr(x,y) memset(x, y, sizeof(x))
#define mp(x, y) make_pair(x, y)
#define all(x) begin(x), end(x)
#define MAXN 200005
#define fi first
#define se second;
#define Size(x) ((int)size(x))
using namespace std;
typedef long long LL;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 10000007;
//head by DYH

int id[MAXN];

int main(){
    int n;
    scanf("%d", &n);
    rep(i, 1, n){
        int x;
        scanf("%d", &x);
        id[x] = i;
    }
    int used = 0;
    rep(i, 1, n){
        int x;
        scanf("%d", &x);
        if(id[x] > used){
            printf("%d ", id[x] - used);
            used = id[x];
        }
        else printf("0 ");
    }
    puts("");
    return 0;
}
 Problem-B
```

---

## 作者：wwqf (赞：0)

```cpp
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
const int maxd = 200005;
int p[maxd];
int main(){

    cin >> n;
    int d;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &d);
        p[d] = i;
    }

    // 1. check 输入顺序
    // 2. 如果下一个数小于tot就输出0, 如果大于tot 输出num - tot
    // 3. 更新tot
    int tot = 0; // 最近弹出数据的下标
    for (int i = 0; i < n; i++) {
        scanf("%d", &d);
        int num = p[d];
        if (num < tot) {
            cout << "0 ";
        } else {
            cout << num - tot << " ";
            tot = num;
        }
    }
    return 0;
}
```

---

