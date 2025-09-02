# Interactive LowerBound

## 题目描述

This is an interactive problem.

You are given a sorted in increasing order singly linked list. You should find the minimum integer in the list which is greater than or equal to $ x $ .

More formally, there is a singly liked list built on an array of $ n $ elements. Element with index $ i $ contains two integers: $ value_{i} $ is the integer value in this element, and $ next_{i} $ that is the index of the next element of the singly linked list (or -1, if the current element is the last). The list is sorted, i.e. if $ next_{i}≠-1 $ , then $ value_{nexti}&gt;value_{i} $ .

You are given the number of elements in the list $ n $ , the index of the first element $ start $ , and the integer $ x $ .

You can make up to $ 2000 $ queries of the following two types:

- ? i ( $ 1<=i<=n $ ) — ask the values $ value_{i} $ and $ next_{i} $ ,
- ! ans — give the answer for the problem: the minimum integer, greater than or equal to $ x $ , or ! -1, if there are no such integers. Your program should terminate after this query.

Write a program that solves this problem.

## 说明/提示

You can read more about singly linked list by the following link: [https://en.wikipedia.org/wiki/Linked\_list#Singly\_linked\_list](https://en.wikipedia.org/wiki/Linked_list#Singly_linked_list)

The illustration for the first sample case. Start and finish elements are marked dark. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF843B/71961769b81bfa3a3f8829eda26d6883c0c5db50.png)

## 样例 #1

### 输入

```
5 3 80
97 -1
58 5
16 2
81 1
79 4
```

### 输出

```
? 1
? 2
? 3
? 4
? 5
! 81```

# 题解

## 作者：rui_er (赞：6)

有趣的交互题。

题意：有一个递增的单向链表，需要通过询问权值和下一项编号，求出其中 $\ge x$ 的最小元素。

这还不简单？挨个询问一遍就切了嘛（

$n\le 50000$，询问最多 $2000$ 次。

~~笑容逐渐凝固。~~

---

考虑其他方法：

因为已知该链表是递增的，可以先随机询问 $\min(n,1000)-1$ 个点，记录好 $\le x$ 的最大元素以及他下一项的地址。因为询问数远小于 $n$ 的最大可能值，我们将这些询问近似地看做随机的。

经过这些询问后，如果最大元素恰好为 $x$，直接输出即可，因为不能得到更小的解了。

否则，我们从下一项的地址开始询问最多 $1000$ 次（因为地址随机，两个被询问的数之间数的个数的期望可以通过除法求得，远小于 $1000$），每次移动到获取的 nxt 指针，直到该指针为 $-1$ 或找到 $\ge x$ 的数。对于第二种，因为单调递增的性质，可以知道获取到的是最优解，直接输出；对于第一种，跳出循环后判断最大值与 $x$ 的大小关系，输出该值或者 $-1$ 即可。

注意几点：

1. 经过几次错误，发现这里翻译得很毒瘤，实际上只能进行 $1999$ 次询问（原文如此，经尝试也确实如此），注意不要被坑。
2. C++ 的 `rand()` 好像被毒瘤出题人卡掉了，换了几种方式都在第六个点错了，这里可以利用 int 自然溢出手写一个随机。

甚至这个都被卡了：

```cpp
srand(time(0));
srand(rand()); srand(rand()+19849);
```

我是用的随机函数可以见代码。

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define loop while(true)
#define rep(x,y,z) for(int (x)=(y);(x)<=(z);(x)++)
#define per(x,y,z) for(int (x)=(y);(x)>=(z);(x)--)
#define fil(x,y) memset((x), (y), sizeof(x))
using namespace std;
typedef long long ll;
const int N = 5e4+5, inf = 0x3f3f3f3f;

int n, front, x, ans = -inf, nxt;
vector<int> interact(int _) {
	printf("? %d\n", _);
	fflush(stdout);
	int a, b;
	scanf("%d%d", &a, &b);
	return vector<int>({a, b});
}
void give(int _) {
	printf("! %d\n", _);
	fflush(stdout);
}

int seed, seed2;
void srand(int x, int y) {seed = x; seed2 = y;}
int frand() {return (seed *= 19260817) += ((seed2 += 114514) ^= 1919810);}
int rand() {int res = frand(); while(res <= 0) res += n; return res;}

int main() {
//	srand(time(0));
//	srand(rand()); srand(rand()+19849);
	srand(998244353, 1000000007);
//	rep(i, 1, 100) printf("%d %d %d\n", seed, seed2, rand());
	scanf("%d%d%d", &n, &front, &x);
	nxt = front;
	rep(i, 1, min(n, 1000)-1) {
		int pos = rand() % n + 1;
		vector<int> res = interact(pos);
		if(res[0] <= x && res[0] > ans) nxt = res[1], ans = res[0];
	}
	if(ans == x) return give(x), 0;
	rep(i, 1, 1000) {
		if(nxt == -1) break;
		vector<int> res = interact(nxt);
		if(res[0] >= x) return give(res[0]), 0;
		ans = res[0]; nxt = res[1];
	}
	give(ans>=x?ans:-1);
	return 0;
}
```

---

## 作者：BADFIVE (赞：1)

**思路**：把链表读入进来，随机询问 $1000$ 次，找到最大的 $<x$ 的数，并记录下来。    
这 $1000$ 个点是在链表中均匀分布的。就直接用一个部分暴力询问。 

实际上，从整个序列里面随机选 $1000$ 个数出来询问，然后从里面找出比 $x$ 小的最大的那个，再往后面搜 $1000$ 个数。所以直接用随机化就可以了。     

因为已知该链表是递增的，可以先随机询问 $\min(n,1000)-1$ 个点，记录好 $\le x$ 的最大元素以及它的后面一项的地址。因为询问数 $< n$ 的最大可能值，我们将这些询问近似地看做随机的。   

参考代码：   
```
#include<bits/stdc++.h>
using namespace std;
int n,a,x,ans;
int arr[100001],brr[100001];
int main(){
    srand(time(0));
    cin>>n>>a>>x;
    ans=a;
    for(int i=1;i<=1000;i++){
        int res=1ll*rand()*rand()%n+1;
        cout<<"? "<<res<<endl;
        cin>>arr[res]>>brr[res];
        if(arr[ans]<arr[res]&&arr[res]<=x){
            ans=res;
        }
    }
    for(int i=ans;i!=-1;i=brr[i]){
        cout<<"? "<<i<<endl;
        cin>>arr[i]>>brr[i];
        if(arr[i]>=x){
            cout<<"! "<<arr[i]<<endl;
            return 0;
        }
    }
    cout<<"! -1"<<endl;
}
```

---

## 作者：lytqwq (赞：0)

$n \le 50000 $ ，最多询问两千次 ，一个一个问显然爆炸。

我们先随机询问 $q$ 次， 把链表分成 $q+1$ 个部分， $x$ 所在的部分的大小期望为 $\frac{n}{q+1}$ ，这样我们就能在这一个部分暴力询问了。

代码如下：（我是 $q=1000$ ）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50100;
int n,startt,x,dowz;
int val[N],nex[N];
int main(){
	srand(time(NULL));
	cin>>n>>startt>>x;
	dowz=startt;
	for(int i=1;i<=1000;i++){
		int nam=1ll*rand()*rand()%n+1;
		cout<<"? "<<nam<<endl;
		cin>>val[nam]>>nex[nam];
		if(val[dowz]<val[nam]&&val[nam]<=x){
			dowz=nam;
		}
	}
	for(int i=dowz;i!=-1;i=nex[i]){
		cout<<"? "<<i<<endl;
		cin>>val[i]>>nex[i];
		if(val[i]>=x){
			cout<<"! "<<val[i]<<endl;
			return 0;
		}
	}
	cout<<"! -1"<<endl;
}
```



---

## 作者：zi小眼聚光 (赞：0)

显然没法把整个链表读进来

分块做就好啦！（滑稽）

随机询问1000次，找到最大的不大于x的数，并记录nxt

因为是随机的且1000<<50000，所以基本上问到的这1000个点是在链表中均匀分布的

于是最好情况下链表被分成了50块，这时你还有999次询问，而你已经大概知道答案在哪块！

证明概率的话，因为询问了1000次，每次都不在x向前的1000节点的概率大概是(1-999/n)$^1$$^0$$^0$$^0$ ，脸不白都能过~~（虽说我连着wa了两次）~~

愉快的附上代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,start,x,nxt,ans=-1,a,b;
bool use[500005];
struct mker{//随机数怕被卡结果还是被卡了233
	int seed0,seed1,seed2;
	mker(){
		seed0=*(new int);
		seed1=*(new int);
		seed2=*(new int);
	}
	unsigned int rd(){
		seed0^=seed1^=seed2;
		seed0=(seed1<<3)|(seed2>>2)+rand();
		seed1=(seed0>>3)&(seed2<<1)-rand();
		seed2=(seed1<<4)^(seed0>>1)*rand();
		return seed0%n;
	}
}mk;
int main(){
	scanf("%d%d%d",&n,&start,&x);
	nxt=start;
	for(int i=1;i<min(n,1000);i++){
		int q=(n+mk.rd())%n+1;
		printf("? %d\n",q);
		fflush(stdout);
		scanf("%d%d",&a,&b);
		if(a<=x&&(ans==-1||a>ans)){
			nxt=b;
			ans=a;
		}
	}
	if(ans!=x){
		for(int i=1;i<=1000;i++){
			if(nxt==-1)break;
			printf("? %d\n",nxt);
			fflush(stdout);
			scanf("%d%d",&a,&b);
			nxt=b;
			if(a>=x){
				ans=a;
				break;
			}
			fflush(stdout);
		}
	}
	if(ans<x)ans=-1;
	printf("! %d\n",ans);
	fflush(stdout);
	return 0;
}
```


---

