# Unfair Poll

## 题目描述

On the Literature lesson Sergei noticed an awful injustice, it seems that some students are asked more often than others.

Seating in the class looks like a rectangle, where $ n $ rows with $ m $ pupils in each.

The teacher asks pupils in the following order: at first, she asks all pupils from the first row in the order of their seating, then she continues to ask pupils from the next row. If the teacher asked the last row, then the direction of the poll changes, it means that she asks the previous row. The order of asking the rows looks as follows: the $ 1 $ -st row, the $ 2 $ -nd row, $ ... $ , the $ n-1 $ -st row, the $ n $ -th row, the $ n-1 $ -st row, $ ... $ , the $ 2 $ -nd row, the $ 1 $ -st row, the $ 2 $ -nd row, $ ... $

The order of asking of pupils on the same row is always the same: the $ 1 $ -st pupil, the $ 2 $ -nd pupil, $ ... $ , the $ m $ -th pupil.

During the lesson the teacher managed to ask exactly $ k $ questions from pupils in order described above. Sergei seats on the $ x $ -th row, on the $ y $ -th place in the row. Sergei decided to prove to the teacher that pupils are asked irregularly, help him count three values:

1. the maximum number of questions a particular pupil is asked,
2. the minimum number of questions a particular pupil is asked,
3. how many times the teacher asked Sergei.

If there is only one row in the class, then the teacher always asks children from this row.

## 说明/提示

The order of asking pupils in the first test:

1. the pupil from the first row who seats at the first table, it means it is Sergei;
2. the pupil from the first row who seats at the second table;
3. the pupil from the first row who seats at the third table;
4. the pupil from the first row who seats at the first table, it means it is Sergei;
5. the pupil from the first row who seats at the second table;
6. the pupil from the first row who seats at the third table;
7. the pupil from the first row who seats at the first table, it means it is Sergei;
8. the pupil from the first row who seats at the second table;

The order of asking pupils in the second test:

1. the pupil from the first row who seats at the first table;
2. the pupil from the first row who seats at the second table;
3. the pupil from the second row who seats at the first table;
4. the pupil from the second row who seats at the second table;
5. the pupil from the third row who seats at the first table;
6. the pupil from the third row who seats at the second table;
7. the pupil from the fourth row who seats at the first table;
8. the pupil from the fourth row who seats at the second table, it means it is Sergei;
9. the pupil from the third row who seats at the first table;

## 样例 #1

### 输入

```
1 3 8 1 1
```

### 输出

```
3 2 3```

## 样例 #2

### 输入

```
4 2 9 4 2
```

### 输出

```
2 1 1```

## 样例 #3

### 输入

```
5 5 25 4 3
```

### 输出

```
1 1 1```

## 样例 #4

### 输入

```
100 100 1000000000000000000 100 100
```

### 输出

```
101010101010101 50505050505051 50505050505051```

# 题解

## 作者：Cloud_Umbrella (赞：1)

~~（终于抢到了首发）~~

## 题意

把教室看成一个 $n\times m$ 的矩阵，老师按照从 $1$ 到 $n$，再从 $n$ 到 $1$ 的顺序让学生回答问题。现给出老师的问题数 $k$ 及某位同学的坐标，问回答最多和最少的同学回答的数量，及这位同学回答的数量。

## 分析

我们可以先观察和分析一下题面，首先，老师问问题的顺序其实是从 $1$ 到 $n$，再从 $n-1$ 到 $2$，这才是一轮，所以，经过一轮后，只有第 $1$ 位和第 $n$ 位同学会被问到一次，其余同学是两次。不难得出，每轮问过的问题数就是 $2n-2$，总共问的问题数就 $(2n-2)\times m$ 注意，如果 $n$ 是 $1$，理论上说这个式子的结果是零，但其实并不是这样，所以别忘了特判。

然后，用一个变量 $tot$ 记下一共问的问题数，稍加分析，发现老师问问题的总轮数就是 $\large\lfloor \frac{k}{tot} \rfloor$，而 $k\bmod tot$ 则是最后一轮问到的同学。

至此，由于数据的原因，问题已经迎刃而解。

 ## Code
 
 ```c++
 #include<bits/stdc++.h>
using namespace std;
int n,m,x,y,tot,t;//ans1记录最多的数量，ans2记录最少的数量
long long ans1,ans2,k,a[110][110],s;//不开long long见那啥
int main(){
	scanf("%d%d%lld%d%d",&n,&m,&k,&x,&y);
	ans2=k,tot=max(2*n-2,1)*m;//别忘了特判
	s=k/tot,t=k%tot;//s是轮数，t是回答问题最后一位同学
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(i==1 || i==n) a[i][j]=s;//特判第1和第n位
			else a[i][j]=s<<1;//s<<1一般情况下等于s*2，在计算机编译下两者没有区别
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m && t;j++,t--)//遍历t同学前面的人，回答次数加1
			a[i][j]++;
	for(int i=n-1;i>1;i--)//倒着也要遍历一遍，防止遗漏
		for(int j=1;j<=m && t;j++,t--)
			a[i][j]++;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			ans1=max(a[i][j],ans1);
			ans2=min(a[i][j],ans2);
		}
	printf("%lld %lld %lld",ans1,ans2,a[x][y]);
	return 0;//终生养成好习惯
}




 ```

---

## 作者：zhengenzhe (赞：0)

## 【输入格式】
按顺序输入 $n,m,k,x,y$。

**输入：**

$n,m$ 指矩阵的大小。$k$ 指老师提问的问题数。$x,y$ 指第 $x$ 行，第 $y$ 列的人回答了几个问题。

## 【题目大意】
老师按从 $1 \sim n$ 行再从 $n \sim 1$ 行的顺序提问。

**求：**

输出回答问题最多与最少的人各回答了几个问题，并且输出第 $x$ 行，第 $y$ 列的人回答了几个问题。

## 【思路与代码】

- **1.进行分析**

首先再观察以下顺序就会发现老师的顺序其实是 $1 \sim n$ 再是 $n-1 \sim 2$ 这才是一轮提问。
这是经过一轮提问下的矩阵：

$1$ $1$

$2$ $2$

$2$ $2$

$1$ $1$

由此可以观察得出只有第 $1$ 行与第 $n$ 行被提问了 $1$ 次，再经过计算可得出一轮提问共问了 $n \times m \times 2-(2 \times m)$ 个问题（注意：$n=1$ 时要特判），接着又可以知道老师提问了 $ \frac {k}{n \times m \times 2-(2 \times m)}$ 轮，而 $k$ 取余 $n \times m \times 2-(2 \times m)$ 则是最后一次问到的人。

## Code：

```c++
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN=1e3+1;
ll ans1=-0x3f3f3f3f3f3f3f,ans2=0x3f3f3f3f3f3f3f,k,a[MAXN][MAXN],lunshu,n,m,x,y,cnt,last_student;
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
void pretreatment(){
	if(2*n-2>1){//特判n为1的情况
		cnt=(2*n-2)*m;
	}else{
		cnt=m;
	}
    lunshu=k/cnt;//计算轮数
	last_student=k%cnt;//计算最后一位同学
}
void work1(){//从1~n遍历
	for(ll i=1;i<=n;i++){
    	for(ll j=1;j<=m&&last_student>=1;j++,last_student--){
        	a[i][j]++;
		}
	}  
}
void work2(){//从n-1~2遍历
	for(ll i=n-1;i>=2;i--){
    	for(ll j=1;j<=m&&last_student>=1;j++,last_student--){
        	a[i][j]++;
		}
	}
}
void find(){//寻找最大最小值
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			if(a[i][j]>ans1){
				ans1=a[i][j];
			}
			if(a[i][j]<ans2){
				ans2=a[i][j];
			}
        }
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    read(n);
    read(m);
    read(k);
    read(x);
    read(y);
    pretreatment();//初始化，计算出轮数与最后一名同学
    for(ll i=1;i<=n;i++){
    	for(ll j=1;j<=m;j++){
            if(i==1||i==n){//即为解释中的第1行与第n行只回答了1次
            	a[i][j]=lunshu;
            	continue;
			}
			a[i][j]=lunshu*2;//其它地方回答了2倍的次数
			continue;
		}
	}
 	work1();
 	work2();
	find();
    cout<<ans1<<" "<<ans2<<" "<<a[x][y]<<'\n';
    return 0;
}
/*
1 1
2 2
2 2
1 1
*/
```


---

## 作者：_Kimi_ (赞：0)

# CF758C 题解

要掉绿了，赶紧来水一发题解（。

### 题意

老师会在课堂上按照 $1,2,3,4 \dots n,n-1,n-2,n-3 \dots 2,1,2,3$ 的行数来点人回答问题。

而每一行会按照 $1,2,3, \dots m$ 的列数来点人。

老师共会问 $k$ 个问题。

问回答问题最多的人和回答问题最少的人各回答了多少次，和位于 $(x,y)$ 座位上的人回答了多少问题。

### 思路

把 $1,2,3,4 \dots n,n-1,n-2,n-3 \dots 2$ 看成一个周期。

当 $n$ 大于 $1$ 的时候，行的周期是 $2 \times n - 2$。

注意特判 $n=1$ (也就是只有一行）的情况。

### 代码 

小知识：可以用 ```max_element``` 和 ```min_element``` 求数组或 vector 求最大值最小值，二者返回的都是迭代器或指针，可以通过 ```*``` 符号来获得值。

```cpp
#include<bits/stdc++.h>
#define int long long
#define WA AC
using namespace std;
const int inf = 1e18;
int n, m, k, x, y;
void input(){
    ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen("CF758C.in", "r", stdin);
	//freopen("CF758C.out", "w", stdout);
	cin >> n >> m >> k >> x >> y;
	x--;
	y--;
}
signed main(){
	input();
	if(n == 1){
		vector<int> A(m);
		for(int i = 0; i < m; i++){
			if(i < (k % m)) A[i]++;
			A[i] += (k / m);
		}
		int maxx = -inf, minn = inf;
		maxx = max(maxx, *max_element(A.begin(), A.end()));
    	minn = min(minn, *min_element(A.begin(), A.end()));
		cout << maxx << ' ' << minn << ' ' << A[y] << endl;
	}else{
		int cnt = (n * 2 - 2) * m;
  		int pos = (k / cnt);
  		int maxx = -inf, minn = inf;
  		k %= cnt;
  		vector<vector<int>> A(n, vector<int>(m));
		for (int i = 0; i < n; i++) {
		    for (int j = 0; j < m; j++) {
		      	if (i == n - 1 || i == 0) A[i][j] = pos;
		      	else A[i][j] = pos * 2;
		    }
		}
		for (int i = 0; i < n; i++) {
		    for (int j = 0; j < m; j++) {
		      	if (k) k--, A[i][j]++;
		    }
		}
		for (int i = n - 2; i >= 0; i--) {
		    for (int j = 0; j < m; j++) {
		    	if (k) k--, A[i][j]++;
		    }
		}
		for (int i = 0; i < n; i++) {
		    maxx = max(maxx, *max_element(A[i].begin(), A[i].end()));
    		minn = min(minn, *min_element(A[i].begin(), A[i].end()));
		}
		cout << maxx << ' ' << minn << ' ' << A[x][y] << endl;
	}
	return 0;
}
```


---

