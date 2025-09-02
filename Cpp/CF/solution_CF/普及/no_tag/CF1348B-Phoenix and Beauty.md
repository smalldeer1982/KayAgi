# Phoenix and Beauty

## 题目描述

Phoenix loves beautiful arrays. An array is beautiful if all its subarrays of length $ k $ have the same sum. A subarray of an array is any sequence of consecutive elements.

Phoenix currently has an array $ a $ of length $ n $ . He wants to insert some number of integers, possibly zero, into his array such that it becomes beautiful. The inserted integers must be between $ 1 $ and $ n $ inclusive. Integers may be inserted anywhere (even before the first or after the last element), and he is not trying to minimize the number of inserted integers.

## 说明/提示

In the first test case, we can make array $ a $ beautiful by inserting the integer $ 1 $ at index $ 3 $ (in between the two existing $ 2 $ s). Now, all subarrays of length $ k=2 $ have the same sum $ 3 $ . There exists many other possible solutions, for example:

- $ 2, 1, 2, 1, 2, 1 $
- $ 1, 2, 1, 2, 1, 2 $

In the second test case, the array is already beautiful: all subarrays of length $ k=3 $ have the same sum $ 5 $ .

In the third test case, it can be shown that we cannot insert numbers to make array $ a $ beautiful.

In the fourth test case, the array $ b $ shown is beautiful and all subarrays of length $ k=4 $ have the same sum $ 10 $ . There exist other solutions also.

## 样例 #1

### 输入

```
4
4 2
1 2 2 1
4 3
1 2 2 1
3 2
1 2 3
4 4
4 3 4 2```

### 输出

```
5
1 2 1 2 1
4
1 2 2 1
-1
7
4 3 2 1 4 3 2```

# 题解

## 作者：do_while_true (赞：5)


显然构造后的序列一定是 $abcd...abcd...abcd...$ 这样循环的，循环节的长度为 $k$ ，这样才能使得任意连续 $k$ 个数加起来都是 $a+b+c+d+...$ 也就是一个循环节的和。

为了使得原序列中每一个数都出现在构造后的序列中，我们可以输出 $n$ 个循环节，这样保证了原序列的第 $i$ 个数一定会出现在第 $i$ 个循环节中。

如果我们原序列中不同的数的数量大于 $k$ 时无解。如果小于 $k$ 就去找到没出现的放到循环节里直到循环节长度等于 $k$。

### [$\mathcal{Code}$](https://codeforces.com/contest/1348/submission/78697789)

---

## 作者：沉石鱼惊旋 (赞：4)

### 题目翻译

有一个长度为 $n$ 的数组，里面有 $n$ 个元素，$a_1,a_2,a_3,...a_n$。

给定一个 $k$，可以通过在 $a$ 数组中插入 $[1,n]$ 之间的数字，使**任意** $k$ 个连续的元素之和相等。

如无解，输出 $-1$。

### 题目思路

我们可以考虑，把这个数组分成很多段，也就变成 $b_1,b_2,b_3,...,b_k,b_1,b_2,b_3,...,b_k,b_1,b_2,b_3......$ 这样的数组。

可以很明显的发现，任意 $k$ 个肯定是 $b_1,b_2,b_3,...,b_k$ 出现一次。

那么也就满足了和相等。

当然，如果我们输入的 $a$，**去重**后元素数量大于 $k$，肯定无法构造。

那么我们需要输出几次 $b_1,...b_k$ 呢？

答案很简单，$n$ 次。

我们用一个例子解释一下。

```
5 5
5 3 2 4 1
```

```
注：原数组元素会在下方标注，‘|’分割每组
1 2 3 4 5|1 2 3 4 5|1 2 3 4 5|1 2 3 4 5|1 2 3 4 5
        ^     ^       ^             ^   ^
```

当然，我们要进行去重。

```
5 5
5 5 5 5 5
```

```
5|5|5|5|5
^ 
```

但是，不要忘了刚才说的：
>如果我们输入的 $a$，**去重**后元素数量大于 $k$，肯定无法构造。

所以，像下组数据：

```
5 3
5 3 2 4 1
```

就得输出 $-1$。

### AC 代码

```cpp
void solve()
{
    set<int>s;
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        s.insert (x);
    }
    if (s.size() > k)
    {
        puts ("-1");
        return;
    }
    cout << n * k << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int it : s)
        {
            cout << it << " ";
        }
        for (int j = 1; j <= k - s.size(); j++)
        {
            cout << n << " ";
        }
    }
    cout << endl;
}
```





---

## 作者：tuzhewen (赞：3)

既然楼下的大佬已经提到了`复制`数组的这种做法，我就来好好的剖析一下（滑稽）

首先，如何判断`-1`？我们把所有数字塞到一个`set`里面，看看`set`的`size`是否小于$k$，也就是说看看不同的数的个数是否小于$k$，如果不，那就`puts("-1");`即珂。

剩下的思路就是我们把那些不同的数字（就是塞到`set`里面的数字）复制$n$遍，然后要是这些数字不足$k$个怎么办？~~凉拌~~我们就随便输出一些数字，比如说~~114514,1919810~~ 1,2,2147483647之类的（但是要在$1$~$n$之内！）。不明白？那就自己举个栗子呗！

$for\ example:$
$k=3,n=5,a={1,3,4,5,4}$

此时就`puts("-1")`

$for\ example:$
$k=5,n=5,a={1,3,4,5,4}$

此时就输出：
`1 3 4 5 5 1 3 4 5 5 1 3 4 5 5 1 3 4 5 5 1 3 4 5 5`
(我倒是很好奇它怎么spj的……)

那么这题就愉快的解完啦！
```
#include <bits/stdc++.h>
using namespace std;
int n,k,T;
set<int> S;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++) {
			int q;
			scanf("%d",&q);
			S.insert(q);//全部塞到set里
		}
		//多出k个不同的数就是-1！
		if(S.size()>k) puts("-1");
		else {
			printf("%d\n",n*k);
			for(int i=1;i<=n;i++) {//复制n遍
				for(auto it=S.begin();it!=S.end();++it) printf("%d ",*it);
				for(int j=1;j<=k-S.size();j++) printf("1 ");//不足k个就随便输出其他的数字
			}
			puts("");
		}
		S.clear();//千万要清空！
	}
	return 0;
}
```
有的小伙伴珂能会问了：为啥要复制$n$遍呢？

1. 首先题目的数据说不能超过10000，而$n*k$的最大值是$10000$所以复制$n$遍 ~~（瞎扯）~~
2. 因为我们考虑数组$4\ 4\ 4$如果说我们不复制$n$遍`set`的话，那么原来的三个$4$就不足了，那么也不符合题意的“插入”了，所以只能正正好好复制$n$遍（也不能多，不然长度会超过$10000$滴！）

---

## 作者：huayucaiji (赞：1)

这道题很有意思。

首先我们来理解一下题意：“An array is beautiful if all its subarrays of length k have the same sum. ”这句话的意思也就是告诉你，这个数组的形式一定是这样的：

$$c_1,c_2,c_3...,c_{k-1},c_k,c_1,c_2,c_3,...c_{k-1},c_k,c_1,c_2...$$

只有这种轮换式的数组满足他的要求，这个应该是很好想到的，也是这道题的一个关键。这里一定要理解。

接着，我们发现，如果原来的数组中不同的数的个数大于 $k$，那么一定是无法配成上述的数组的。直接输出 $-1$。

再来想一个问题，如果我们现在知道了我们的 $c_1,c_2,c_3...,c_{k-1},c_k$。那么我们的答案数组一定很好求。所以我们这道题就转化成了求 $c$ 数组。求的方法很简单，就是先把所有的不同的数填进去，然后在把剩下的空位随便填一些数，就可以了。因为这样保证了我们一定有解。至于说题目里说答案数组的长度 $m\leq 10^4$。我们可以证明，答案数组的长度最坏情况下为 $n\cdot k\leq 10^4$所以不用担心具体证明可以参考这道题，思想是差不多的：[CopyCopyCopyCopyCopy](https://codeforces.com/contest/1325/problem/B)。

下面介绍两种已求出 $c$ 数组，求答案数组的方法。

### 复制

这个方法就是把 $c$ 数组复制 $k$ 遍即可，[CopyCopyCopyCopyCopy](https://codeforces.com/contest/1325/problem/B)的想法就一样了。

~~比赛咋就没想到这种方法呢~~

### 正经求解

我们对着 $a$ 数组扫一遍。如果我们现在需要的数正好是目前指针指向的 $a$ 数组里的数，我们就直接把这个数放到里面来，并且指针指向下一个 $a$ 里的数。否则我们就把这个数放到 $b$ 数组里，指针不动。这个想法我给代码吧。

~~主要是比赛里只想到这种qwq~~

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=1e4+10;

int n,t,m,a[maxn],b[maxn],c[maxn],k;
bool ex[maxn];

signed main() {
	t=read();
	while(t--) {
		fill(ex,ex+n+1,0);
		n=read();k=read();
		m=0;
		int num=0;
		for(int i=1;i<=n;i++) {
			a[i]=read();
			if(!ex[a[i]]) {
				ex[a[i]]=1;
				num++;
			}
		}
		if(num>k) {
			cout<<-1<<endl;
			continue;
		}//判断-1
		int q=1,mark=0x7fffffffffffffff;
		for(int i=1;i<=n;i++) {
			if(ex[i]) {
				c[q++]=i;
				mark=i;
			}
		}
		while(q<=k) {
			c[q++]=mark;
		}
		q--;
		//构造c数组。答案数组是b
		int now=1,con=0;//指针是now
		num=1;
		bool flag=1;
		while(1) {
			if(a[now]==c[num]) {
				b[++m]=a[now];
				now++;//第一种情况
			}
			else {
				b[++m]=c[num];//第二种情况
			}
			num++;
			if(num==k+1) {
				num=1;
			}//开启新的循环
			if(now>n) {
				break;
			}//已经找到答案，退出循环。
		}
		cout<<m<<endl;
		for(int i=1;i<=m;i++) {
			cout<<b[i]<<" ";
		}//输出
		cout<<endl;
	}
	return 0;
}

```

---

## 作者：Isshiki_Hugh (赞：1)

个人认为代码比楼上精简(小声

给出数组，要求插入一些数后连续 k 个数字的和相同，容易得到这需要保证每一个`a[i] = a[i+k]`，(i+k <= n) 且只要输出合法的数组就行

也就是说，我们可以把题目从选数看成队列的出队入队，每一次出队的数和入队的数还得是一样的。于是我们想到这可能是个长度为 k 的循环队列。而这个循环队列多次展开就可以得到题目所需求的数组。

而这个循环队列如何求得呢。实际上只要按照给定的数组按照顺序得到每一个数字第一次出现的顺序就可以了。

代码：


```cpp

#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
#include<set>
#include<vector>
#include<queue>
#include<cstdlib>//rand()
#define rep(i,a,b) for(register long long i = (a);i <= (b);++i)
#define per(i,a,b) for(register long long i = (a);i >= (b);--i)
typedef long long ll;
typedef unsigned long long ull;
using std::string;using std::cin;using std::cout;

int T,n,k,a[111],b[111],m;
bool flag[111];

int main(){
    //std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("in.in", "r", stdin);
    cin >> T;
    while(T--){
        n = k = m = 0;
        cin >> n >> k;
        rep(i,1,111) flag[i] = false;
        rep(i,1,n){
            cin >> a[i];
            if(flag[ a[i] ] == false) flag[ a[i] ] = true , b[++m] = a[i];
        }
        if(m > k){
            cout << "-1\n";
            continue;
        } else {
            rep(i,m+1,k){
                b[i] = b[i-m];
            }
            cout << n * k << "\n";
            rep(i,1,n){
                rep(j,1,k){
                    cout << b[j] << " ";
                }
            }
            cout << "\n";
        }

    }
    return 0;
}
```

---

## 作者：_czy (赞：0)

## 分析
显然，符合要求的序列一定形如
$$$a,b,c,d,a\dots d,a,b,c,d$$$
是一个循环节长度为 $k$ 的序列。

我们为了尽量将每个数字放入序列，可以先去重，再将序列复制 $n$ 次，这样可以保证循环节和存在原来的子序列。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a;
set<int>s;
int read(){
	char c;
	while(!isdigit(c=getchar()));
	int x=c-'0';
	while(isdigit(c=getchar()))x=x*10+c-'0';
	return x;
}
int main(){
	t=read();
	while(t--){
		s.clear();
		n=read(),k=read();
		for(int i=1;i<=n;i++)s.insert(read());
		if(s.size()>k){
			cout<<"-1\n";
			continue;
		}
		cout<<n*k<<'\n';
		for(int j=1;j<=n;j++){
			for(int i:s)cout<<i<<' ';
			for(int i=k-s.size();i;i--)cout<<"0 ";
		}
		cout<<'\n';
	}
}
```

---

## 作者：Fairicle (赞：0)

第一眼看到这题以为是个神题，跳题去做 C 了，结果最后凉凉，D 都没出。

我做这种题习惯先判断哪些情况是无解的。在这题中，我们发现，如果能满足题目要求，那么序列中不同的数必定不能超过题目给定的 $k$。

那么无解的判断就很简单了，记录不同的数与 $k$ 比较即可。

接下来就是答案的计算。这题看似很复杂，实则有一种十分暴力的做法。我们构造一个序列 $b_1,b_2,b_3,...,b_k$，其中包含了 $a$ 数组中所有的数，可能还存在一些本不存在于 $a$ 数组中的数（$a$ 中不同数字个数不一定恰好等于 $k$）

得到这个序列，我们只需要把它复制 n 遍,那么它必定能满足题目要求。

也就是 $b_1,b_2,..,b_k,b_1,b_2,...,b_k,b_1,b_2,...$

以一组数据为例：

$n=4,k=4,a[4]={1,2,3,1}$

那么一种可行的答案为 $1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4$。

代码很好写，就不放了。

---

## 作者：Nozebry (赞：0)

## $Problems$
总共有 $T$ 组数据，每组数据输入两个数 $n$ 和 $k$ $(1\le n,k \le100)$，接下来有一个长度为 $n$ 的数组，$(1\le ai \le n)$。

问能否添加一些范围在 $1-n$ 之间的数，使得数组长度为 $k$ 的子序列的和为定值。否则输出-1。
## $Answer$
我们先拿样例来说，$n=4,k=2$,$a[1..4]=1,2,2,1$
要使任意 $2$ 个连续的子序列的和为定值，则只需在 $a$ 数组中插入一个元素 $2$，则序列 $a[1..4]=1,2,1,2,1$，任意两个数的和均为定值 $3$。

那么要使一个数组对于 $k$ 来说是存在定值的，则这个数组必须以 $k$ 为周期。

如果数组 $a$ 中存在多于 $k$ 个不同的数字，则没有答案，我们输出 $-1$ (因为数组不能以 $k$ 为周期)。

那么我们就只需要考虑不同种类数的个数小于 $k$ 的数组 $a$。

$a_1$ 到 $a_k$ 的子段和为定值，说明 $a_2$ 到 $a_{k+1}$ 也等于这个定值，由此可知 $a_{k+1}=a_1$

那么现在很简单，我们只需要 $a_1$ 到 $a_k$ 就可以一直往后构造一个循环节，即 $a_{k+1}=a_1,a_{k+2}=a_2...$

接下来我们只需要重复此操作，直接循环到 $n$ 为止。
## $Code$
```pascal
var
	t,n,k,tt,i,j,x,num:longint;
	a,b:array[0..10010]of longint;
begin
	readln(t);
	while (t>0) do
	begin
		readln(n,k);dec(t);
		fillchar(a,sizeof(a),0);
		for i:=1 to n do
		begin
			read(x);
			inc(a[x]);
		end;
		num:=0;
		for i:=1 to n do
			if (a[i]<>0) then inc(num);
		if (num>k) then writeln(-1)
		else
		begin
			fillchar(b,sizeof(b),0);
			tt:=0;
			for i:=1 to n do
				if (a[i]<>0) then
				begin
					inc(tt);
					b[tt]:=i;
				end;
			if (num<k) then
			begin
				i:=1;
				while (num<>k) do
				begin
					if (a[i]<>0) then begin inc(num);b[num]:=i;end;
					inc(i);
				end;
			end;
			writeln(n*k);
			for i:=1 to n do
				for j:=1 to num do write(b[j],' ');
			writeln;
		end;
	end;
end.

```

---

