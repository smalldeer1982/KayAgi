# Matrix Rotation

## 题目描述

You have a matrix $ 2 \times 2 $ filled with distinct integers. You want your matrix to become beautiful. The matrix is beautiful if the following two conditions are satisfied:

- in each row, the first element is smaller than the second element;
- in each column, the first element is smaller than the second element.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1772B/3883cb5d5c3c3237649026ca712db7066e7d51ae.png)You can perform the following operation on the matrix any number of times: rotate it clockwise by $ 90 $ degrees, so the top left element shifts to the top right cell, the top right element shifts to the bottom right cell, and so on:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1772B/a844c7395726cf76b3147efc79ccce4d8f167fbf.png)Determine if it is possible to make the matrix beautiful by applying zero or more operations.

## 样例 #1

### 输入

```
6
1 3
5 7
8 10
3 4
8 10
4 3
6 1
9 2
7 5
4 2
1 2
4 3```

### 输出

```
YES
YES
NO
YES
YES
NO```

# 题解

## 作者：zajasi (赞：4)

## 题意
给你一个 $2 \times 2$ 的矩阵，这个矩阵是美丽的如果：$a_{1,1}<a_{1,2}$ 且 $a_{2,1}<a_{2,2}$ 且 $a_{1,1}<a_{2,1}$ 且 $a_{1,2}<a_{2,2}$。

你可以将这个矩阵中的数顺时针旋转若干次，问能不能将这个矩阵变得美丽？
## 解题思路
很明显，这个矩阵一旦旋转四次就会变成原样，所以我们只需要暴力枚举四次变化，然后判断一下是否合法就行了。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int a[3][3];
bool check(){
	if(a[1][1]<a[1][2]&&a[2][1]<a[2][2]&&a[1][1]<a[2][1]&&a[1][2]<a[2][2])return true;
	return false;
}
main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		int f=0;
		cin>>a[1][1]>>a[1][2]>>a[2][1]>>a[2][2];
		for(int i=1;i<=5;i++){
			int x=a[1][1];
			a[1][1]=a[2][1];
			a[2][1]=a[2][2];
			a[2][2]=a[1][2];
			a[1][2]=x;
			if(check()){
				cout<<"YES\n";
				f=1;
				break;
			}
	//		cout<<a[1][1]<<" "<<a[1][2]<<"\n"<<a[2][1]<<" "<<a[2][2]<<"\n\n";
		}
		if(f==0) cout<<"NO\n";	
	}
	return 0;
}

```

---

## 作者：LegendaryGrandmaster (赞：2)

## 题目大意

给定一个矩阵：
$\begin{bmatrix}
  a& b\\c
  & d
\end{bmatrix}$

你可以进行若干次操作（或者不操作），每次将矩阵旋转 $90^{\circ}$，要求：

* 每一**行**的第一个数**小于**第二个数
* 每一**列**的第一个数**小于**第二个数

如果满足，输出 `YES` ，否则输出 `NO` （不区分大小写）

---------------

## 解题思路

我们知道，如果这个矩阵旋转 $360^{\circ}$，它就便会原样了，我们以此可以知道矩阵可以变成以下情况：

1. 不旋转：
$\begin{bmatrix}
  a& b\\c
  & d
\end{bmatrix}$

2. 旋转$90^{\circ}$:
$\begin{bmatrix}
  c& a\\d
  & b
\end{bmatrix}$

3. 旋转$180^{\circ}$:
$\begin{bmatrix}
  d& c\\b
  & a
\end{bmatrix}$

4. 旋转$270^{\circ}$:
$\begin{bmatrix}
  b& d\\a
  & c
\end{bmatrix}$

我们只要依次判断即可。

代码如下：

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long LL;
int main()
{
	int t;
	cin>>t;
	while(t--){
		int a,b,c,d;
		cin>>a>>b;
		cin>>c>>d;
		bool ok=0;
		/*
		ab ca dc bd
		cd db ba ac
		*/
		if(a<b&&a<c&&b<d&&c<d)ok=1;
		else if(c<a&&c<d&&a<b&&d<b)ok=1;
		else if(d<c&&d<b&&c<a&&b<a)ok=1;
		else if(b<d&&b<a&&d<c&&a<c)ok=1;
		cout<<(ok?"YES":"NO")<<'\n';
	}
}
```

---

## 作者：_JF_ (赞：1)

## CF1772B Matrix Rotation 

[题目传送门](https://www.luogu.com.cn/problem/CF1772B)

我们定义一个“优秀”的矩阵当他满足以下特点：

- 在每行中，第一个元素总小于第二个元素。

- 在每列中，第一个元素总小于第二个元素。

现在给你一个 $2\times 2$ 的矩阵，每次可以旋转 $90^\circ$，请问一直旋转，看是否有一种情况满足他是一个“优秀”得矩阵？

不难发现，旋转 $360^\circ$这个矩阵就变得和原来一样了。因为他是 $2\times 2$ 的，数据较小，我们可以对这个矩阵手动进行三次翻转，对于每一次翻转，也就是，我们把四个数依次拿出来，记为 $a,b,c,d$。旋转 $90^\circ$，放在图中就是：


原来：$\begin{bmatrix}a&b\\c&d\end{bmatrix}$。

旋转 $90^\circ$：$\begin{bmatrix}c&a\\b&d\end{bmatrix}$。

按照上述方法进行旋转即可。

$Code$：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =300;
int a[N][N];
bool check()
{
	if(((a[1][1]<a[1][2])&&(a[2][1]<a[2][2]))&&((a[1][1]<a[2][1])&&(a[1][2]<a[2][2])))
		return true;
	else
		return false;
}
void Slove()
{
	int x1=a[1][1],x2=a[1][2],x3=a[2][1],x4=a[2][2];
	a[1][2]=x1,a[1][1]=x3,a[2][1]=x4,a[2][2]=x2;
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int t;
	cin>>t;
	while(t--)
	{
		cin>>a[1][1]>>a[1][2]>>a[2][1]>>a[2][2];
		if(check())
		{
			cout<<"YES"<<endl;
			continue;
		}
		Slove();
		if(check())
		{
			cout<<"YES"<<endl;
			continue;
		}
		Slove();
		if(check())
		{
			cout<<"YES"<<endl;
			continue;
		}
		Slove();
		if(check())
		{
			cout<<"YES"<<endl;
			continue;
		}
		cout<<"NO"<<endl; 
	}
	return 0;
}
```




---

## 作者：VertexNeko (赞：1)

题解都是暴力解法，此处提供找规律的解法。

设一个符合题意矩阵中四个元素分别为 $a, b, c, d$ 。并如下按照题目要求排列：
$$
\begin{aligned}
&a\qquad b\cr
&d\qquad c
\end{aligned}
$$
接下来开始转：
![](https://cdn.luogu.com.cn/upload/image_hosting/zu1i23d7.png)

观察旋转后的符合要求的矩阵，可以得出符合要求的矩阵 $map$ 会有如下特征：
 - 对于 $map[1][1],map[2][1]$ 和 $map[1][2],map[2][2]$ 大小关系相同。
 - 对于 $map[1][1],map[1][2]$ 和 $map[2][1],map[2][2]$ 大小关系相同。
 
每一个判断用异或运算，最后用或运算连接。如果最后得到的值为 $1$ ，说明上文必有一个大小关系不同，那么这个矩阵无法通过旋转得到符合题意的矩阵。

可能看了代码会更好理解：
```cpp
#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  int map[10][10];
  cin >> map[1][1] >> map[1][2];
  cin >> map[2][1] >> map[2][2];
  bool flag1 = (map[1][1] < map[2][1]) ^ (map[1][2] < map[2][2]);//对于第一条的大小关系的相同的判定，相同为0，不同为1
  bool flag2 = (map[1][1] < map[1][2]) ^ (map[2][1] < map[2][2]);//同理，第二条
  bool flag3 = flag1 | flag2;
  //如果flag3为true则大小关系不同
  if (flag3 == 1) {
    cout << "NO" << endl;
  } else {
    cout << "YES" << endl;
  }
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int tt; cin >> tt;
  while (tt--) {
    solve();
  }
  return 0;
}
```
蒟蒻第一篇题解，可能写得不是很好，望包容

---

## 作者：Micnation_AFO (赞：0)

每个矩阵都是 $2\times 2$ 的，因此可以直接把四个数读入。

每次对矩阵顺时针旋转九十度，是这样的：
```
a b
c d
 
c a
d b
 
d c
b a
 
b d
a c
```

然后直接按照题目意思，判断即可。

代码：

```cpp
#include <iostream>

using namespace std;

int T;

int main() {
    cin >> T;
    while (T--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (a < b && c < d && a < c && b < d) {
            puts("YES");
            continue;
        }
        if (c < a && d < b && c < d & a < b) {
            puts("YES");
            continue;
        }
        if (d < c && b < a && d < b && c < a) {
            puts("YES");
            continue;
        }
        if (b < d && a < c && b < a && d < c) {
            puts("YES");
            continue;
        }
        puts("NO");
    }
    return 0;
}

```

---

## 作者：tangrunxi (赞：0)

假设原来给的矩阵是：

$\begin{vmatrix}a&b\\c&d\end{vmatrix}$

首先判断原矩阵是否符合要求。

条件：$a< b,a< c,b< d,c< d$。

如果要求直接输出。如果不满足，进行一次操作，变为：

$\begin{vmatrix}c&a\\d&b\end{vmatrix}$

条件：$c< a,c< d,a< b,d< b$。

再次判断，若不满足，再次操作变为：

$\begin{vmatrix}d&c\\b&a\end{vmatrix}$

条件：$d< b,d< c,c< a,b< a$。

如果还不满足，再次操作变为：

$\begin{vmatrix}b&d\\a&c\end{vmatrix}$

条件：$b< d,b< a,d< c,a< c$。

如果这个矩阵还不满足，再次操作，就变成了：

$\begin{vmatrix}a&b\\c&d\end{vmatrix}$

发现回到了最原始的时候，这表明如果上述 $4$ 个矩阵都不满足，将会产生循环，即无法满足。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;++i){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		if((a<b&&a<c&&b<d&&c<d)||(c<a&&c<d&&a<b&&d<b)||(d<b&&d<c&&c<a&&b<a)||(b<d&&b<a&&d<c&&a<c)) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```


因此代码就是这 $4$ 个条件 **至少满足其一** 就输出 ```YES```，否则输出 ```NO```。

---

## 作者：loser_seele (赞：0)

直接推导出数学结论是困难的，虽然也能做。

但我们发现旋转 $ 4 $ 次之后显然会出现循环，于是暴力模拟旋转过程，每次旋转时判断这个矩形是否合法即可。

时间复杂度 $ \mathcal{O}(T) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
int a[2][2],b[2][2];
bool good() 
{
    return a[0][0] <= a[0][1] && a[1][0] <= a[1][1] && a[0][0] <= a[1][0] && a[0][1] <= a[1][1];
}
void rotate()
{
    b[0][0]=a[1][0];
    b[0][1]=a[0][0];
    b[1][0]=a[1][1];
    b[1][1]=a[0][1];
    a[0][0]=b[0][0];
    a[0][1]=b[0][1];
    a[1][0]=b[1][0];
    a[1][1]=b[1][1];
}
int main() 
{
    int T;
    cin>>T;
    while(T--)
    {
    cin>>a[0][0]>>a[0][1]>>a[1][0]>>a[1][1];;
    bool ok=0;
    ok|=good();
    for(int i=1;i<=4;i++)
    rotate(),ok|=good();
    if(ok)
    cout<<"YES\n";
    else
    cout << "NO\n";
    }
}
```


---

