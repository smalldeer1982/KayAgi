# Doctor

## 题目描述

There are $ n $ animals in the queue to Dr. Dolittle. When an animal comes into the office, the doctor examines him, gives prescriptions, appoints tests and may appoint extra examination. Doc knows all the forest animals perfectly well and therefore knows exactly that the animal number $ i $ in the queue will have to visit his office exactly $ a_{i} $ times. We will assume that an examination takes much more time than making tests and other extra procedures, and therefore we will assume that once an animal leaves the room, it immediately gets to the end of the queue to the doctor. Of course, if the animal has visited the doctor as many times as necessary, then it doesn't have to stand at the end of the queue and it immediately goes home.

Doctor plans to go home after receiving $ k $ animals, and therefore what the queue will look like at that moment is important for him. Since the doctor works long hours and she can't get distracted like that after all, she asked you to figure it out.

## 说明/提示

In the first sample test:

- Before examination: $ {1,2,3} $
- After the first examination: $ {2,3} $
- After the second examination: $ {3,2} $
- After the third examination: $ {2} $

In the second sample test:

- Before examination: $ {1,2,3,4,5,6,7} $
- After the first examination: $ {2,3,4,5,6,7} $
- After the second examination: $ {3,4,5,6,7,2} $
- After the third examination: $ {4,5,6,7,2,3} $
- After the fourth examination: $ {5,6,7,2,3} $
- After the fifth examination: $ {6,7,2,3,5} $
- After the sixth examination: $ {7,2,3,5,6} $
- After the seventh examination: $ {2,3,5,6} $
- After the eighth examination: $ {3,5,6,2} $
- After the ninth examination: $ {5,6,2,3} $
- After the tenth examination: $ {6,2,3} $

## 样例 #1

### 输入

```
3 3
1 2 1
```

### 输出

```
2 ```

## 样例 #2

### 输入

```
4 10
3 3 2 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7 10
1 3 3 1 2 3 1
```

### 输出

```
6 2 3 ```

# 题解

## 作者：小杨小小杨 (赞：3)

## 题意
翻译非常好懂，非常敬业。
## 思路
~~目前的最优解，欢迎吊打。~~

看到题解是二分的，感觉，是不是有点小题大做了……     
提供一个利用数学中的周期问题的方法。   
假设每一个数都不会被消去，你只需要不停地减，那么相信大家一定都会做，即使那个 $k$ 这么大。     
但一个数是会被消去的。    
我们来考虑一下：如果一个数要被消去，那么它的数值要变成 $0$，所以我们可以算出，假设它的数值为 $x$，一共有 $y$ 个数而且其他数都不比它小，那么它理应会在第 $(x - 1 ) \times y + 1$ 次被消去。   
但是这样有两个限制：

1. 这个数不一定在第一位。
2. 剩下的数不一定都不比它小。

这个时候，我们是否可以把最后的那一下补完一个周期，那么就可以对其进行排序，然后从数值小的开始一个个消去，最后的几个再暴力模拟一下就行了！
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,i,sum,x,flag;
struct Node{
	long long x,i;
}a[100010];
bool cmp(Node x,Node y){return x.x<y.x;}
bool cmp1(Node x,Node y){return x.i<y.i;}
int main(){
	scanf("%lld%lld",&n,&m);
	for (i=1;i<=n;i++) scanf("%lld",&a[i].x),a[i].i=i;
	sort(a+1,a+n+1,cmp);
	for (i=1;i<=n;i++)
		if (sum+(a[i].x-x)*(n-i+1)<=m) sum=sum+(a[i].x-x)*(n-i+1),x=a[i].x;
		else break;//周期判定消除
	if (i>n&&sum<m){printf("-1\n");return 0;}
	else if (i>n&&sum==m) return 0;
	x=x+(m-sum)/(n-i+1);m=(m-sum)%(n-i+1);
	i=1;sort(a+1,a+n+1,cmp1);
	while (m>0){
		if (a[i].x>x) a[i].x--,m--;
		i=i%n+1;
	}
	int h=i;
	for (i=1;i<=n;i++,h=h%n+1) if (a[h].x>x) printf("%lld ",a[h].i);
	return 0;
}
```
## 后记
理论上还可以优化，欢迎吊打。


---

## 作者：XXh0919 (赞：1)

纯属队列训练题

这题其实说的很明白，就是让你在 $n$ 个数里拿出第一个数，若这个数减 $1$ 不为零就将其放到队尾，否则将其弹出去，在 $k$ 次操作后输出剩下所有数的编号，若操作次数大于 $k$ 次，则输出 $-1$。

### 你们最爱的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,x,s;
queue<long long>que;
queue<long long>hao;
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;++i)
    {
    	cin>>x;
    	que.push(x);//输入
    	hao.push(i);//编号
	}
	for(int i=1;i<=k;++i)
    {
    	if(que.empty())//若队列为空
    	{
    		cout<<-1<<endl;//直接带走
    		return 0;
		}
    	x=que.front(),s=hao.front();
    	que.pop(),hao.pop();//先让第一个数“退休”
    	if(x-1>0)//若还没有到退休的时候（打个比方）
        que.push(x),hao.push(s);//快点回来上班儿
	}
	while(!hao.empty())//输出
	{
		cout<<hao.front()<<' ';
		hao.pop();
	}
    return 0;
}
```
管理员求过！！！！！！！

---

## 作者：yuchenren (赞：1)

### 题面大意

$n$ 只动物去看病，每只动物要看 $a_i$ 次，每只动物看完 $1$ 次病且还需要继续看病就排到队列尾，医生只看 $k$ 次病，问看完 $k$ 次后队列的情况。

### 解题思路

$0 \le k \le 10^{14}$ 显然不能用模拟。

本题可用二分答案来做，医生看 $1 \sim n$ 次为 $1$ 轮，通过二分求出需要多少轮，最后通过剩余的动物数输出队列的情况。

### 代码

详细解析在注释中。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, a[100001];
long long k, leftover;//记得开 long long

bool check(long long x) {
	long long sum = 0;
	for (int i = 0; i < n; i++) {
		sum += min((long long)a[i], x);//强转
		if (sum > k) {
			return false;
		}
	}
	return true;
}

int main() {
	cin >> n >> k;
	long long sum = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	if (k > sum) {
		cout << -1 << endl;
		return 0;
	}
	long long l = 0, r = sum;
	while (l <= r) {//二分
		long long mid = (l + r) / 2;
		if (check(mid)) {
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	sum = 0;
	for (int i = 0; i < n; i++) {
		sum += min((long long)a[i], r);//强转
	}
	leftover = k - sum;
	int st = 0;//没排到的开始
	bool flag = true;
	for (int i = 0; i < n; i++) {
		a[i] -= min((long long)a[i], r);//强转
		if (a[i]) {
			if (leftover == 0 && flag == true) {
				flag = false;
				st = i;
			} else if (leftover > 0) {
				leftover--;
				a[i]--;
			}
		}
	}
	for (int i = st; i < n; i++) {//先是上一轮
		if (a[i]) {
			cout << i + 1 << " ";//别忘了+1
		}
	}
	for (int i = 0; i < st; i++) {//再是第二轮开始
		if (a[i]) {
			cout << i + 1 << " ";
		}
	}
	cout << endl;
	return 0;
}
```

---

## 作者：zym20249_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF83B)

## 题意
给定一个包含 $n$ 个数的序列 $a_1,a_2,\dots,a_n$，$a_i$ 的编号为 $i$，注意编号不会因为数字的移动而改变。

现在请你执行 $k$ 次操作，每次操作为取出序列的第一个数并将其值减一，若其值大于 $0$，则将其放到序列的最尾端，否则将其删除。

求最后的序列剩下的数的编号（若 $k$ 次操作还未执行完，序列已经为空则输出 `-1`）。

## 思路
这道题可以用队列做。如果大于 $0$ 的话，将这个数减 $1$ 然后放到这 $n$ 个数的最后面，再进行 $k$ 次操作后输出剩下数。最后需要注意如果在 $k$ 次操作中所有数都没了的话，就跳出操作，输出 `−1`。

## code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,k,x,s;
queue<ll>que;
queue<ll>q;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;++i)
    {
    	cin>>x;
    	que.push(x);
    	q.push(i);
	}
	for(int i=1;i<=k;++i)
    {
    	if(que.empty())
    	{
    		cout<<-1<<endl;
    		return 0;
		}
    	x=que.front(),s=q.front();
    	que.pop(),q.pop();
    	if(x-1>0)que.push(x),q.push(s);
	}
	while(!q.empty())
	{
		cout<<q.front()<<" ";
		q.pop();
	}
    return 0;
}
```

---

## 作者：albccpp6 (赞：0)

## 题目大意：
给你一个有 $n$ 个数的序列，让你重复 $k$ 次操作，每次操作把序列的第 $1$ 个数减一，如果其值大于 $0$，那么把他放到序列最后面，否则，直接去掉。求最后剩下的数的编号，如果还没执行完 $k$ 次序列就空了，就输出 $-1$。
## 思路：
用一个结构体数组来存这 $n$ 个数的值和编号，用 $n$ 来存储个数，然后直接模拟。
## Code：
```cpp
#include <iostream>
using namespace std;
struct bb {
	long long c,d;		// c 用来存储值，d 用来存储编号  
};
bb a[100001];
void aa(int b){				//aa 就是整体往前移一位 
	for (long long i = 1 ; i <= b ; i ++){
		a[i] = a[i + 1];
	}
}
int main(){
	long long n,k,l,l1;		//l 用来存储 a[1]减玩后的值，l1用来存储a[1]的编号 
	cin >> n >> k;
	for (long long i = 1 ; i <= n ; i ++){	//输入 
		cin >> a[i].c;
		a[i].d = i;
	}
	for (long long i = 1 ; i <= k ; i ++){
		if (n == 0){		//判断是否为空，为空直接输出-1 
			cout << -1;
			return 0;
		}
		l = a[1].c - 1;
		l1 = a[1].d;
		if (l == 0){	//如果减完后等于 0，那么去掉 
			n --;
			aa(n);
		}
		else {			//否则，放到最后 
			aa(n-1);
			a[n].c = l;
			a[n].d = l1;
		}
	}
	for (long long i = 1 ; i <= n ; i ++) {		//输出 
		cout << a[i].d << ' ';		
	}
	return 0;
}
```

---

## 作者：taikongsha (赞：0)

# **题意**
这题很容易理解，就是给你 $n$ 个数，让他们循环 $k$ 次操作。


# **思路**

~~我认为这道题可以用队列做。~~

它给你 $n$ 个数，让你每次拿出他的第一个数，

然后判断这个数减 $1$ 后是否大于 $0$；

如果大的话，将这个数减 $1$ 然后放到这 $n$ 个数的最后面；

在进行 $k$ 次操作后输出剩下说有数的下标。

（这个下标是输入这 $n$ 个数是这 $n$ 个数分别的下标，并且下标会跟随数进行移动。）

否则就不管这个数（不把它加到队尾）。

如果在 $k$ 次操作中所有数都没了的话，就跳出操作，输出 $-1$。



# **接下来上代码**

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k;

int main(){
	cin>>n>>k;
	queue <long long> q;	//储存数的队列
	queue <long long> xb;	//储存下标的队列
	for(int i=0;i<n;i++){	//输入 n 个数并储存他们的下标
		int a;
		cin>>a;
		q.push(a);
		xb.push(i+1);
	}
	for(int i=0;i<k;i++){	// k 次操作
		if(q.empty()==1){	//如果在操作中所有数都没了的话，就跳出操作，输出$-1$
			cout<<"-1"<<endl;
			return 0;
		}
		int a=q.front()-1,b=xb.front();
		q.pop();xb.pop();
		if(a>0){			//判断这个数在操作后是否大于 0
			q.push(a);
			xb.push(b);		//把数和下标放到各自的队列尾
		}
	}
	while(!xb.empty()){
		cout<<xb.front()<<" ";		//输出队列
		xb.pop();
	}
	cout<<endl;
	return 0;
}
```


---

