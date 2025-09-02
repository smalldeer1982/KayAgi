# マージ (Merge)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2020yo1a/tasks/joi2020_yo1a_c

長さ $ N $ の正整数列 $ A=(A_1,\ A_2,\ \ldots,\ A_N) $ と，長さ $ M $ の正整数列 $ B=(B_1,\ B_2,\ \ldots,\ B_M) $ が与えられる． これらの数列は，共に広義単調増加数列である．つまり，$ A_1\ \leqq\ A_2\ \leqq\ \cdots\ \leqq\ A_N $, $ B_1\ \leqq\ B_2\ \leqq\ \cdots\ \leqq\ B_M $ を満たす．

以下のアルゴリズムを用いて，これらの数列から，長さ $ N+M $ の正整数列 $ C=(C_1,\ C_2,\ \ldots,\ C_{N+M}) $ を生成する．

1. はじめ $ C $ は空とする．
2. $ A $ と $ B $ がどちらも空の場合，終了する．
3. $ A $ と $ B $ のどちらかが空の場合，そうでない数列を $ t $ とおく．どちらも空でない場合，先頭の要素が小さい数列を $ t $ とおく．ただし，$ A $ と $ B $ の先頭の要素が同じ値のときは $ A $ を $ t $ とおく．
4. $ t $ の先頭の要素を $ C $ の末尾に追加する．
5. $ t $ の先頭の要素を削除する．
6. 2. に戻る．

広義単調増加な正整数列 $ A $, $ B $ が与えられたとき，このアルゴリズムにより生成される正整数列 $ C $ を出力するプログラムを作成せよ．

## 说明/提示

### 制約

- $ 1\ \leqq\ N\ \leqq\ 500 $．
- $ 1\ \leqq\ M\ \leqq\ 500 $．
- $ 1\ \leqq\ A_1\ \leqq\ A_2\ \leqq\ \cdots\ \leqq\ A_N\ \leqq\ 2000 $．
- $ 1\ \leqq\ B_1\ \leqq\ B_2\ \leqq\ \cdots\ \leqq\ B_M\ \leqq\ 2000 $．

### Sample Explanation 1

アルゴリズムを行う前，$ A=(1,2),\ B=(2) $ である． 以下のように数列 $ C $ が生成される． - 数列 $ A $ の先頭の要素は $ 1 $，数列 $ B $ の先頭の要素は $ 2 $ なので，数列 $ A $ の先頭の要素を数列 $ C $ に追加しこれを数列 $ A $ から削除する． - 数列 $ A $ の先頭の要素は $ 2 $，数列 $ B $ の先頭の要素は $ 2 $ なので，数列 $ A $ の先頭の要素を数列 $ C $ に追加しこれを数列 $ A $ から削除する． - 数列 $ A $ は空なので，数列 $ B $ の先頭の要素を数列 $ C $ に追加しこれを数列 $ B $ から削除する． - 数列 $ A $ も数列 $ B $ も空なので，アルゴリズムを終了する． アルゴリズムが終了した後，数列 $ C=(1,2,2) $ である．

## 样例 #1

### 输入

```
2 1
1 2
2```

### 输出

```
1
2
2```

## 样例 #2

### 输入

```
3 8
1 3 8
3 3 4 5 6 7 8 9```

### 输出

```
1
3
3
3
4
5
6
7
8
8
9```

# 题解

## 作者：Light_az (赞：3)

其实，这道题可以 `sort` 一遍过，但是我们不可以过度依赖于自带函数，所以我推荐一个新的解法：冒泡排序

当我们输入第一个数时，这个数列本身就是有序的，因为整个序列只有一个数。那么对于我们每一个新输入的数来说：之前的数组成的数列一定有序，我们只需要将整个数列重新比较一遍，如果第 $i-1$ 个数大于第 $i$ 个数就交换，否则停止，因为下面的数是比第 $i-1$ 个数小的，第 $i$ 个数一定不会小于它们。下面是完整代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,k;
ll mini=INT_MAX,maxi=0;
ll a[2005];

int main(){
	cin>>n>>m;
	for(int i=1;i<=n+m;i++){
		cin>>a[i];
		for(int j=i;j>1;j--){//排序新数列
			if(a[j]<a[j-1]){//可以交换
				swap(a[j],a[j-1]);
			}
			else{//终止比较，下面的数一定比a[i]小
			    break;
			}
		}
	}
	for(int i=1;i<=n+m;i++){
		cout<<a[i]<<endl;
	}
    return 0;
}
```


---

## 作者：Ray662 (赞：0)

[更好的阅读体验](https://www.luogu.com.cn/blog/sunrize/solution-at-joi2020-yo1a-c)

本题 $n, m \le 500$，可直接用 sort 排序。

我用的是 vector，开数组也可以，但要记得至少要开 $1000$ 的空间。

代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define _for(i, a, b)  for (int i = (a); i <= (b); i ++ )
#define _all(i, a, b)  for (int i = (a); i >= (b); i -- )
using namespace std;
const int N = 505;
int n, m, x;
vector<int> v;
int main() {
	ios :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	_for (i, 1, n)  cin >> x, v.push_back(x);
	_for (i, 1, m)  cin >> x, v.push_back(x);
	sort(v.begin(), v.end());
	for (int i : v)  cout << i << endl;
	return 0;
}
```

---

## 作者：Colorful_Unicorn (赞：0)

这题可以直接用 sort 水过。

# 思路

首先读入 $a_i$ 和 $b_i$。但它们并不存于同一个数组，于是我们可以在创建一个 $c$ 数组。每读入一个数，便将其存入 $c$ 数组。再将 $c$ 数组排序输出即可。

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000005],b[1000005],c[1000005],cnt;
int main()
{
    cin >> n >> m;
    for (int i=1;i<=n;i++)
    {
        cin >> a[i];
        c[++cnt]=a[i];
    }
    for (int i=1;i<=m;i++)
    {
        cin >> b[i];
        c[++cnt]=b[i];
    }
    sort(c+1,c+cnt+1);
    for (int i=1;i<=n+m;i++)
        cout << c[i] << "\n";
    return 0;
}
```

---

## 作者：Huhu12346 (赞：0)

# 题目大意
读入一个长度为 $n$ 的数组 $a$ 和一个长度为 $m$ 的数组 $b$ 输出他们合并后升序排列的序列。

# 思路
这题很简单，直接把两个数组一起读入（本人认为一起读入比分开读更简单），然后就偷个懒，用 `sort` 一下就行了，最后再输出。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int ss[10005],n,m;//数组可以开大一点，保证不RE
int main()
{
    	cin>>n>>m;
       	for(int i=1;i<=n+m;i++) 
	{
		cin>>ss[i];
   	}
   	sort(ss+1,ss+n+m+1);//偷懒神器：sort
    	for(int i=1;i<=n+m;i++) 
	{
		cout<<ss[i]<<endl;//最后输出
	}
    	return 0;//代码好习惯
}
```


---

## 作者：Samson2010 (赞：0)

# 题目大意
读入一个长度为 $n$ 的数组 $a$ 和一个长度为 $m$ 的数组 $b$ 输出他们合并后升序排列的序列。
# 思路  
如果按题意合并两个数组的话，不好做。干脆读入时读到一个数组，再排序。
# 代码
```cpp
#include<bits/stdc++.h>
#define N 1005
using namespace std;
int a[N],n,m;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n+m;i++) cin>>a[i];
    sort(a+1,a+n+m+1);
    for(int i=1;i<=n+m;i++) cout<<a[i]<<endl;
    return 0;
}
```


---

## 作者：NOI_AK_dreeeam (赞：0)

这题直接把 $a$ 数组和 $b$ 数组合起来输入，然后排序并输出即可。

**_AC code_**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1005];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n+m;i++) cin>>a[i];
	sort(a+1,a+n+m+1);
	for(int i=1;i<=n+m;i++) cout<<a[i]<<"\n";
	return 0;
} 
```


---

## 作者：lyh0217 (赞：0)

# 题目大意
读入一个长度为 $n$ 的数组 $a$ 和一个长度为 $m$ 的数组 $b$ 输出他们合并后升序排列的序列。
# 解析
既然要合并，就干脆读入读到一个数组中去，再排一遍序就行了。
# 代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005];
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n+m;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+m+1);
	for(int i=1;i<=n+m;i++)
	{
		cout<<a[i]<<endl;
	}
	return 0;
}
~~~

---

