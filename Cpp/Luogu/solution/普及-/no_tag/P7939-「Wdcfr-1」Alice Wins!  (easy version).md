# 「Wdcfr-1」Alice Wins!  (easy version)

## 题目描述

**版本之间的区别在于操作的限制。**

Alice 是一个可爱的女孩，她有很多玩偶。

有 $4 \cdot n$ 个玩偶在玩“石头剪刀布”。他们被分成两个队伍：A 队和 B 队。每个队伍包含 $2 \cdot n$ 个玩偶。

总共会进行 $2 \cdot n$ 轮比赛。在第 $i$ 轮中，A 队的第 $i$ 个玩偶将与 B 队的第 $i$ 个玩偶对战。如果 A 队的玩偶赢了，A 队将获得 $1$ 分。如果输了，A 队将失去 $1$ 分。如果打平，A 队将不获得分数。

Alice 知道所有玩偶在这场比赛中的选择。具体来说，她用两个数组 $a$ 和 $b$ 来表示两个队伍中玩偶的选择。$a_i$ 表示 A 队第 $i$ 个玩偶的选择，$b_i$ 表示 B 队第 $i$ 个玩偶的选择。在这个问题中，我们用 $1$ 表示石头，$2$ 表示剪刀，$3$ 表示布。

现在对于**每个队伍**，Alice 想要改变**最多** $n$ 个玩偶的选择，以使 A 队的得分尽可能高。

找出 A 队的最大得分及其构造方法。如果有多个答案，输出任意一个（你仍然需要最大化 A 队的得分）。

## 说明/提示

### 解释

对于第一个测试用例，我们可以将 $a_2$ 改为 $1$，将 $b_1$ 改为 $2$。然后 A 队可以得到 $2$ 分。可以证明这是 A 队可以获得的最大分数。

对于第二个测试用例，我们可以将 $a_1$ 改为 $3$，将 $a_2$ 改为 $1$。

### 约束

$1\le T,n \le 10^5; 1\le a_i,b_i \le 3$。所有测试用例中 $n$ 的总和 $\le 10^5$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
1
1 2
1 2
2
2 3 1 3
1 2 2 1```

### 输出

```
2
1 1
2 2
4
3 1 1 3
1 2 2 1```

# 题解

## 作者：封禁用户 (赞：5)

# 1.前言
因为用 $1$ 代表石头，$2$ 代表剪刀，$3$ 代表布。所以我们可以得到 "1>2,2>3,3>1"。

每一组的样例输入应该是这样的：
```
n
a[1] a[2] ... a[n]
b[1] b[2] ... b[n]
```
我们的目标是让 a 数组得分尽量高。
# 2.解析
- 样例第一行：分数的计算

因为我们每一组都能改变 $n$ 次，那我们相当于 a 数组和 b 数组一共能改 $2n$ 次，即使 b 数组每次都是胜利的，那我们可以通过 $n$ 次改变 a 数组使得分数 $+n$，通过 b 数组的 $n$ 次，让 b 输，使得分数 $+n$。

如果 a 本来就赢了一些分，那就可以省一些次数，还能保证分数是 $2n$。

- 输出结果

现在我们已经算出分数，只要构造一种结果：
显然全部让 a 数组大于 b 数组或者将 b 数组全部输给 a 数组都是不能满足“每一组改变 $n$ 次”的，那么我们如何保证每一组都改变 $n$ 次以内呢？

接下来我称改变一个数使得 a 赢为一次操作。

我们用一个 f 来记录是偶数次还是奇数次操作，初始的时候 $f=true$。如果是奇数次，我们改变 a 数组的数，然后让 $f=false$；到了偶数次的时候 $f=false$，改变 b 数组的数再让 $f=true$...这样一来，操作一次 a 数组，操作一次 b 数组，使得最后，每个数组的操作次数都小于等于 $n$，符合题意。

由 "1>2,2>3,3>1" 得到以下代码：
```cpp
	if(a[i]==1&&b[i]==3){
		if(f==1) a[i]=2,f=0;
		else b[i]=2,f=1;
	}//1<3，调整根据f调整a或b
	if(a[i]==2&&b[i]==1){
		if(f==1) a[i]=3,f=0;
		else b[i]=3,f=1;
	}//2<1，调整根据f调整a或b
	if(a[i]==3&&b[i]==2){
		if(f==1) a[i]=1,f=0;
		else b[i]=1,f=1;
	}//3<2，调整根据f调整a或b
```
重点来处理一下相等：

同样的，当 $f=true$。我们将 a 数组的数 $-1$，例如原来都是 $2$，a 数组 $-1$ 之后变成 $1$，因为 "1>2" 所以 a 得分；特别地，当 a 与 b 的数都是 $1$ 时，a 要变成 $3$，而不是 $0$，因为 "3>1"，而不是 "0>1"。然后让 $f=false$；偶数的时候 b 数组的数要 $+1$，特别地，当 a 与 b 都是 $3$ 的时候，b 要变成 $1$，而不是 $4$。

于是可以得到以下代码：
```cpp
	if(a[i]==b[i]){
		if(f==1){
			a[i]-=1;//a-1
			if(a[i]==0) a[i]=3;//1-1=0→3
			f=0;
		}
		else{
			b[i]+=1;//b+1
			if(b[i]==4) b[i]=1;//3+1=4→1
			f=1;
		}
	}
```
所以操作就完成了。
# 3.code
```cpp
#include<bits/stdc++.h>
using namespace std;
int q,n,a[1000010],b[1000010];
signed main(){
	scanf("%d",&q);
	while(q--){
		bool f=1;
		scanf("%d",&n);
		n*=2;//注意这里
		for(int i=1;i<=n;i++) scanf("%d ",&a[i]);
		for(int i=1;i<=n;i++) scanf("%d ",&b[i]);
		for(int i=1;i<=n;i++){
			if(a[i]==1&&b[i]==3){
				if(f==1) a[i]=2,f=0;
				else b[i]=2,f=1;
				continue;
			}
			if(a[i]==2&&b[i]==1){
				if(f==1) a[i]=3,f=0;
				else b[i]=3,f=1;
				continue;
			}
			if(a[i]==3&&b[i]==2){
				if(f==1) a[i]=1,f=0;
				else b[i]=1,f=1;
				continue;
			}
			if(a[i]==b[i]){
				if(f==1){
					a[i]-=1;
					if(a[i]==0) a[i]=3;
					f=0;
				}
				else{
					b[i]+=1;
					if(b[i]==4) b[i]=1;
					f=1;
				}
				continue;
			}
		}
		printf("%d\n",n);//结果是2n，输出n的原因是上面n*2
		for(int i=1;i<=n;i++) printf("%d ",a[i]);
		printf("\n");
		for(int i=1;i<=n;i++) printf("%d ",b[i]);
		printf("\n");
	}
}
```
虽然是 $n$ 次，但是有 $2n$ 个人比赛，所以将 $n$ 扩大 2 倍。为了提升速度，操作完成一次之后，不需要继续判断（此时 a 已经赢了），要加 continue。

求赞qwq

---

## 作者：zct_sky (赞：4)

### 思路：
为了使 $A$ 队得分尽量多，又因为 $A$ 队和 $B$ 队各有 $2n$ 人，都可以改变 $n$ 次。所以最好能让 $A$ 队全赢（~~这不是废话吗~~），那么最好将 $A$ 队前 $n$ 个人全部改成赢的，但是 $A$ 队后面 $n$ 个人不能改了，又因为 $B$ 队输了就等于 $A$ 队赢了，所以只需将 $B$ 队后面 $n$ 个人改成输的即可。 
### 代码：
```c++
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
using namespace std;
inline int read(){//快读 
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
inline void write(int x){//快输 
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+48);
	return;
}
int a[1000010],b[1000010],n,m; 
int main(){
	n=read();
	for(int i=0;i<n;i++){
		m=read();//输入 
		int M=m<<1;
		for(int j=0;j<M;j++)a[j]=read();
		for(int j=0;j<M;j++)b[j]=read();
		
		write(M),putchar('\n');//输出 
		for(int j=0;j<M;j++){
			if(j<m)//使A队前n个人赢
			   if(b[j]==1) a[j]=3;
			   else if(b[j]==2) a[j]=1;
			   else a[j]=2;
			write(a[j]),putchar(' ');//输出
		}
	    putchar('\n');
		for(int j=0;j<M;j++){
			if(j>=m)//使B队后n个人输
			   if(a[j]==1) b[j]=2;
			   else if(a[j]==2) b[j]=3;
			   else b[j]=1;
			write(b[j]),putchar(' ');//输出
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：ahawzlc (赞：1)

思路：简单贪心。

赛时时间不够，写完 A 跑路，结果 B 也很简单。T_T.

---

我们做过一些很经典的入门模拟题，比如基本的石头剪刀布。所以我们显然知道，当石头为 0 ，剪刀为 1 ，布为 2 时，如果 $(a+1) \equiv b \mod 3 $ 那么 A 胜利，B 失败。

题目要求我们对于**每个队伍**至多改 n 次，那么我们可以先对 A 队伍改至多 n 次，使得 A 全赢，然后再对 B 队伍改至多 n 次，使得 B 全输。这样显然会使 A 队伍拿到全部的，也是最大的分数。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=200005; 
int a[N],b[N],t,n;
int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		// n<<1 表示 n*2 想必都知道。 
		for(int i=1;i<=n<<1;i++) scanf("%d",&a[i]),a[i]--;//调整123为012 
		for(int i=1;i<=n<<1;i++) scanf("%d",&b[i]),b[i]--;
		for(int i=1;i<=n;i++) a[i]=(b[i]+2)%3;//A赢 
		for(int i=n+1;i<=n<<1;i++) b[i]=(a[i]+1)%3;//B输 
		printf("%d\n",n<<1);
		for(int i=1;i<=n<<1;i++) printf("%d ",a[i]+1);
		puts("");
		for(int i=1;i<=n<<1;i++) printf("%d ",b[i]+1);
		puts("");
	}
    return 0;
}

```


---

## 作者：Jerrlee✅ (赞：1)

~~赛时 hard 真不会……~~
## 题意
$\texttt{AB}$ 每队 $2n$ 人正在玩石头剪刀布。$\texttt{A}$ 队赢加一分，平不变，输扣一分。你可以至多改变每队 $n$ 个人的出拳方案，让 $\texttt{A}$ 队的得分最高。输出得分的最大值和一组构造方案。

$1$ 代表石头，$2$ 代表剪刀，$3$ 代表布。
## 思路
我们可以把两队的 $2n$ 人分成 $2$ 堆，第一堆改变 $\texttt{A}$ 队人，第二堆改变 $\texttt{B}$ 队人，把 $\texttt{B}$ 队赢或平 $\texttt{A}$ 队的改成输 $\texttt{A}$ 队，$\texttt{A}$ 队本就赢的不用管它，所以一定能把 $\texttt{A}$ 队改成全赢的状态。

第一行直接输出 $2n$ 即可。

处理构造方案：可以发现，$1$ 克 $2$，$2$ 克 $3$，$3$ 克 $1$，所以只要满足 $a_i=b_i-1$ 或 $a_i=3,b_i=1$ 即可满足题意。
## 代码
```cpp
#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        n*=2; //便于运算，防止出错
        int a[n+1],b[n+1];
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        for(int i=1;i<=n;i++){
            cin>>b[i];
        }
        for(int i=1;i<=n;i++){
            if(i<=n/2) if(a[i]==2&&b[i]==1||a[i]==3&&b[i]==2||a[i]==1&&b[i]==3||a[i]==1&&b[i]==1||a[i]==2&&b[i]==2||a[i]==3&&b[i]==3){a[i]=b[i]-1;if(a[i]==0) a[i]=3;} //前一半
            if(i>n/2) if(a[i]==2&&b[i]==1||a[i]==3&&b[i]==2||a[i]==1&&b[i]==3||a[i]==1&&b[i]==1||a[i]==2&&b[i]==2||a[i]==3&&b[i]==3){b[i]=a[i]+1;if(b[i]==4) b[i]=1;} //后一半
        }
        cout<<n<<endl;
        for(int i=1;i<=n;i++){
            cout<<a[i]<<" ";
        }
        cout<<endl;
        for(int i=1;i<=n;i++){
            cout<<b[i]<<" ";
        }
        cout<<endl;
    }
}
```
[AC记录](https://www.luogu.com.cn/record/61877928)

---

## 作者：Galois_Field_1048576 (赞：0)

题意：  
给定 $a$ 和 $b$ 两个长度为 $2n$ 的数组，**各改变** $n$ 个，使得满足 $a_i ~\operatorname{mod}~3 = b_i-1$ （即石头剪子布）的 $i$ 尽可能多。输出满足条件的 $i$ 的数量和改变的方案。  
简单来说，前 $n$ 个数把 A 改成能赢 B 的，后 $n$ 个把 B 改成能输 A 的。  
一百多行的丑代码：
```cpp
#include<iostream>
using namespace std;
signed t, n;
signed a[200005], b[200005];
signed main() {
	cin >> t;
	while (t--) {
		bool ok = 0;
		cin >> n;
		for (signed i = 1; i <= (n << 1); i++) {
			cin >> a[i];
		}
		for (signed i = 1; i <= (n << 1); i++) {
			cin >> b[i];
		}
		signed cnt1 = 0, cnt2 = 0;
		for (signed i = 1; i <= (n << 1); i++) {
			if (a[i] - b[i] == 1 || a[i] == 1 && b[i] == 3) { // 判断：A --输--> B
				if (cnt1 < n) { // 改A成B的克
					cnt1++;
					if (b[i] == 1)
						a[i] = 3;
					else if (b[i] == 2)
						a[i] = 1;
					else if (b[i] == 3)
						a[i] = 2;
				}
				else if (cnt2 < n) { // 改B成A的被克
					cnt2++;
					if (b[i] == 1)
						b[i] = 3;
					else if (b[i] == 2)
						b[i] = 1;
					else if (b[i] == 3)
						b[i] = 2;
				}
				else {
					ok = 1;
					break;
				}
			}
			else {
				continue;
			}
		}
		if (ok == 1) {
			signed ans = 0;
			for (signed i = 1; i <= (n << 1); i++) {
				if (a[i] - b[i] == -1 || a[i] == 3 && b[i] == 1) {
					ans++;
				}
				else if (a[i] == b[i]) {
					continue;
				}
				else {
					ans--;
				}
			}
			cout << ans << endl;
			for (signed i = 1; i <= (n << 1); i++) {
				cout << a[i] << " ";
			}
			cout << endl;
			for (signed i = 1; i <= (n << 1); i++) {
				cout << b[i] << " ";
			}
			cout << endl;
		}
		else {
			for (signed i = 1; i <= (n << 1); i++) {
				if (a[i] == b[i]) {
					if (cnt1 < n) {
						cnt1++;
						if (b[i] == 1) {
							a[i] = 3;
						}
						else if (b[i] == 2) {
							a[i] = 1;
						}
						else if (b[i] == 3) {
							a[i] = 2;
						}
					}
					else if (cnt2 < n) {
						cnt2++;
						if (b[i] == 1) {
							b[i] = 2;
						}
						else if (b[i] == 2) {
							b[i] = 3;
						}
						else if (b[i] == 3) {
							b[i] = 1;
						}
					}
					else {
						break;
					}
				}
			}
			signed ans = 0;
			for (signed i = 1; i <= (n << 1); i++) {
				if (a[i] - b[i] == -1 || a[i] == 3 && b[i] == 1) {
					ans++;
				}
				else if (a[i] == b[i]) {
					continue;
				}
				else {
					ans--;
				}
			}
			cout << ans << endl;
			for (signed i = 1; i <= (n << 1); i++) {
				cout << a[i] << " ";
			}
			cout << endl;
			for (signed i = 1; i <= (n << 1); i++) {
				cout << b[i] << " ";
			}
			cout << endl;
		}
	}
	return 0;
}
```
减少代码复制，共创文明洛谷！

---

## 作者：猜一猜我是谁 (赞：0)

# 思路
直接模拟，对于每组测试数据，分别调整 A 队前 n 个人和 B 队后 n 个人，得分最大值当然是 $2n$。

例如在第一组数据中，A 队和 B 队四个人都分别出石头和剪刀，那么我们可以把 A 队第一个人调整为布，再把 B 队第二个人调整为布。所以最后的得分就是 4。

# 代码
模拟思路即可
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010],b[200010];
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        for(int i=1;i<=2*n;i++) cin>>a[i];
        for(int i=1;i<=2*n;i++) cin>>b[i];
        cout<<2*n<<endl;
        for(int i=1;i<=n;i++){//调整 A 队前 n 个人
            if(b[i]==1) a[i]=3;
            if(b[i]==2) a[i]=1;
            if(b[i]==3) a[i]=2;
        }
        for(int i=1;i<=2*n;i++) cout<<a[i]<<" ";
        cout<<endl;//别忘了换行
        for(int i=n+1;i<=2*n;i++){//调整 B 队后 n 个人
            if(a[i]==1) b[i]=2;
            if(a[i]==2) b[i]=3;
            if(a[i]==3) b[i]=1;
        }
        for(int i=1;i<=2*n;i++) cout<<b[i]<<" ";
        cout<<endl;
    }
}
```

---

## 作者：一只书虫仔 (赞：0)

#### Description

> 有两队 A,B，每队都会出 $2n$ 次拳，并给出他们玩石头剪刀布时的出拳情况，每队**至多**可以改 $n$ 次出拳情况，求通过修改后 A 队赢得次数最多是多少，并输出一种情况。

#### Solution

既然是每队至多 $n$ 次，我们可以考虑前 $n$ 次修改 A，后 $n$ 次修改 B。

1. 前 $n$ 次修改 A：
	- 如果 A 已经赢了，就直接跳过；
    - 如果 A 没有赢，就改成赢；
2. 后 $n$ 次修改 B：
	- 如果 B 已经输了，就直接跳过；
    - 如果 B 是赢的，就改成输。

不难得知 A 一定是全赢的。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int a[200015];
int b[200015];

int main () {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 1; i <= 2 * n; i++) scanf("%d", &a[i]);
		for (int i = 1; i <= 2 * n; i++) scanf("%d", &b[i]);
		for (int i = 1; i <= n; i++) {
			if (b[i] == 1) a[i] = 3;
			if (b[i] == 2) a[i] = 1;
			if (b[i] == 3) a[i] = 2;
		}
		for (int i = n + 1; i <= 2 * n; i++) {
			if (a[i] == 1) b[i] = 2;
			if (a[i] == 2) b[i] = 3;
			if (a[i] == 3) b[i] = 1;
		}
		printf("%d\n", 2 * n);
		for (int i = 1; i <= 2 * n; i++) printf("%d ", a[i]);
		puts("");
		for (int i = 1; i <= 2 * n; i++) printf("%d ", b[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：jxbe6666 (赞：0)

~~感觉别的 dalao 的取模太过麻烦，还不如 if 判断呢~~（逃）  
### 题目分析：
要使 A 队的分数尽量多，只能这样子：在前 n 个中修改 A 队的出拳方案，都为 A 队赢；而在后 n 个中修改 B 队的出拳方案，让 B 队都输给 A 队（对于交换前后顺序也是一样的）。A 队全胜，得分肯定最高，为$ 2\times n$ 分。有了必胜的策略，AC 还会远吗？

$AC\ Code$ ↓：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2 * 1e5 + 5;
int a[N], b[N];
inline int read()
{
	int number = 0, check = 1;
	char ch = getchar();
	while (ch < 48 || ch > 57)
	{
		check = ch == 45 ? -1 : 1;
		ch = getchar();
	}
	while (ch >= 48 && ch <= 57)
	{
		number = (number << 1) + (number << 3) + (ch ^ 48);
		ch = getchar();
	}
	return number * check;
}
inline void write(int X)
{
	if (X < 0)
	{
		X = ~(X - 1);
		putchar('-');
	}
	if (X > 9)
		write(X / 10);
	putchar(X % 10 + '0');
}
int main()
{
	int m = read();
	while (m--)
	{
		int n = read();
		for (int i = 1; i <= 2 * n; i++)
		{
			a[i] = read();
		}
		for (int i = 1; i <= 2 * n; i++)
		{
			b[i] = read();
		}
		//前 n 个修改 A 数组
		for (int i = 1; i <= n; i++)
		{
			if (b[i] == 1) a[i] = 3;
			if (b[i] == 2) a[i] = 1;
			if (b[i] == 3) a[i] = 2;
		}
        
		//---------------分割线---------------
        
		//后 n 个修改 B 数组
		for (int i = n + 1; i <= 2 * n; i++)
		{
			if (a[i] == 1) b[i] = 2;
			if (a[i] == 2) b[i] = 3;
			if (a[i] == 3) b[i] = 1;
		}
		write(2 * n);
		putchar('\n');
		for (int i = 1; i <= 2 * n; i++)
		{
			write(a[i]);
			putchar(' ');
		}
		putchar('\n');
		for (int i = 1; i <= 2 * n; i++)
		{
			write(b[i]);
			putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}

```
[AC 记录](https://www.luogu.com.cn/record/64038988)

祝你们成功！qwq

---

## 作者：Starw (赞：0)

### 思路：

由于 $A$ 队 $B$ 队都可以改 $n$ 次，每队有 $2n$ 人，我们可以得出:

若将 $A$ 队的前 $n$ 个人改成全赢 $B$ 队的，且将 $B$ 队的后 $n$ 个人改成全输 $A$ 队的，这样构造的话 $A$ 队就全赢了，此时答案为 $2n$，显然是最优的。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int fail[5]={0,2,3,1},win[5]={0,3,1,2},a[1000005],b[1000005];
//fail数组表式要输给该下标的数需改为什么数;
//win数组则表式要赢该下标的数需改为什么数;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n,N;
		scanf("%d",&n);
		N=(n<<1);//N就是2n
		printf("%d\n",N);
		for(int i=1;i<=N;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=N;i++)
			scanf("%d",&b[i]);
		for(int i=1;i<=n;i++)
			printf("%d ",win[b[i]]);//a数组前n个数输出赢b数组的
		for(int i=n+1;i<=N;i++)
			printf("%d ",a[i]);
		putchar(10);
		for(int i=1;i<=n;i++)
			printf("%d ",b[i]);
		for(int i=n+1;i<=N;i++)
			printf("%d ",fail[a[i]]);//b数组后n个数输出输a数组的
		putchar(10);
	}
	return 0;//好习惯
}
```


---

## 作者：FuriousC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7939)

大众想法：直接模拟，首先对 $A$ 对进行遍历，判断有哪些情况是平局或 $A$ 对输的，然后改变 $A$ 对出的，

如果 $A$ 对改变次数 $>n$ 就改变 $B$ 对的，直到全改变完。

本题我的代码有点奇怪（

~~又臭又长的~~代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct num{
	int num,c;//num 是原来出的，c 是要改变成的
}a[200005],b[200005];
bool need[200005],need1[200005];//分别记录A队和B队有哪些要改变的
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		//memset(need,0,sizeof(need));
		//memset(need1,0,sizeof(need1));
		int n;
		scanf("%d",&n);
		n*=2;
		for(int i=1;i<=n;i++){
			need[i]=need1[i]=0;
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i].num);
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&b[i].num);
		}
		for(int i=1;i<=n;i++){
			if(a[i].num==1&&b[i].num==3){
				need[i]=1;
				b[i].c=2;
				a[i].c=2;
			}
			if(a[i].num==3&&b[i].num==2){
				need[i]=1;
				b[i].c=1;
				a[i].c=1;
			}
			if(a[i].num==2&&b[i].num==1){
				need[i]=1;
				b[i].c=3;
				a[i].c=3;
			}
		}
		int res=n/2,res1=n/2,ans=0;
		for(int i=1;i<=n;i++){
			if(!need[i]){
				continue;
			}
			if(res>0){
				res--;
				a[i].num=a[i].c;
			}else if(res1>0){
				res1--;
				b[i].num=b[i].c;
			}else{
				break;
			}
		}
		for(int i=1;i<=n;i++){
			if(a[i].num==1&&b[i].num==1){
				need1[i]=1;
				b[i].c=2;
				a[i].c=3;
			}
			if(a[i].num==3&&b[i].num==3){
				need1[i]=1;
				b[i].c=1;
				a[i].c=2;
			}
			if(a[i].num==2&&b[i].num==2){
				need1[i]=1;
				b[i].c=3;
				a[i].c=1;
			}
		}
		for(int i=1;i<=n;i++){
			if(!need1[i]){
				continue;
			}
			if(res>0){
				res--;
				a[i].num=a[i].c;
			}else if(res1>0){
				res1--;
				b[i].num=b[i].c;
				//cout<<b[i].c<<"\n";
			}else{
				break;
			}
		}
		//cout<<res<<" "<<res1<<"\n";
		for(int i=1;i<=n;i++){
			if(a[i].num==b[i].num){
				continue;
			}else if(a[i].num==1&&b[i].num==2){
				ans++;
			}else if(a[i].num==1&&b[i].num==3){
				ans--;
			}else if(a[i].num==2&&b[i].num==1){
				ans--;
			}else if(a[i].num==2&&b[i].num==3){
				ans++;
			}else if(a[i].num==3&&b[i].num==1){
				ans++;
			}else if(a[i].num==3&&b[i].num==2){
				ans--;
			}
		}
		printf("%d\n",ans);
		for(int i=1;i<=n;i++){
			printf("%d ",a[i].num);
		}
		printf("\n");
		for(int i=1;i<=n;i++){
			printf("%d ",b[i].num);
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：user470883 (赞：0)

## 思路：
规律题。

我们需要尽力的让 `A` 队多赢（也就是 `B` 队少输）。

经过观察，不难发现：前 $n$ 个人，我们只需要去修改 `A` 数组，就可以保证必胜，同时也满足题目里的条件：对 `A` 数组的至多修改为 $n$ 次。

但是后 $n$ 个人，由于前 $n$ 个人已经把 `A` 数组修改次数用完了，所以我们只能修改 `B` 数组保证获胜，我们在将 `B` 数组去修改 $n$ 次即可。

然后最简单的石头剪刀布规则： $1$ 胜 $2$，$2$ 胜 $3$，$3$ 胜 $1$。

不过第一行直接输出 $2n$ 即可。

## AC CODE:
```
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        n*=2; 
        int a[n+1],b[n+1];
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
        }
        for(int i=1;i<=n;i++)
        {
            cin>>b[i];
        }//输入
        for(int i=1;i<=n;i++)
        {
            if(i<=n/2) 
            {
                if(a[i]==2 && b[i]==1 || a[i]==3 && b[i]==2 || a[i]==1 && b[i]==3 || a[i]==1 && b[i]==1 || a[i]==2 && b[i]==2 || a[i]==3 && b[i]==3)//进行输赢判断
                {   
                    a[i]=b[i]-1;
                    if(a[i]==0) 
                    {
                        a[i]=3;
                    }
                }
            }
            if(i>n/2)
            {
                if(a[i]==2 && b[i]==1 || a[i]==3 && b[i]==2 || a[i]==1 && b[i]==3 || a[i]==1 && b[i]==1 || a[i]==2 && b[i]==2 || a[i]==3 && b[i]==3)//进行输赢判断
                {
                    b[i]=a[i]+1;
                    if(b[i]==4)
                    {
                        b[i]=1;
                    } 
                }
            }
        }
        cout<<n<<endl;
        for(int i=1;i<=n;i++)
        {
            cout<<a[i]<<" ";
        }
        cout<<endl;
        for(int i=1;i<=n;i++){
            cout<<b[i]<<" ";
        }
        cout<<endl;//输出
    }
}
```

[AC记录](https://www.luogu.com.cn/record/63076642)

球管理通过。

---

## 作者：yzy1 (赞：0)

对于 easy version，有一个显然的结论：最优方案一定能使 A 队每一局都赢。

- 对于前 $n$ 个人，通过修改 $a$ 数组使得 A 队全胜，这样可以保证对于 $a$ 数组的修改至多为 $n$ 次；
- 对于后 $n$ 个人，通过修改 $b$ 数组使得 A 队全胜，这样可以保证对于 $b$ 数组的修改至多为 $n$ 次。

```cpp
int a[N], b[N], n, T;
signed main() {
  in(T); while(T--){
    in(n)(a, 2 * n)(b, 2 * n);
    out(2 * n)('\n');
    re (i, n)
      out((b[i] - 2 + 3) % 3 + 1)(' ');
    rep (i, n + 1, 2 * n)
      out(a[i])(' ');
    out('\n');
    re (i, n)
      out(b[i])(' ');
    rep (i, n + 1, 2 * n)
      out(a[i] % 3 + 1)(' ');
    out('\n');
  }
  return 0;
}
```

---

