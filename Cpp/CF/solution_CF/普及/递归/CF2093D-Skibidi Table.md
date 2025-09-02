# Skibidi Table

## 题目描述

Vadim 喜欢用整数填充正方形表格。但今天他想出了一个有趣的方法！以 $2 \times 2$ 的表格为例，行从上到下编号，列从左到右编号。我们在左上角单元格放置 $1$，右下角放置 $2$，左下角放置 $3$，右上角放置 $4$。这就是他需要的全部乐趣！

幸运的是，Vadim 有一个大小为 $2^n \times 2^n$ 的表格。他计划用 $1$ 到 $2^{2n}$ 的整数按升序填充它。为了填充这么大的表格，Vadim 会将其分成 $4$ 个相等的正方形子表格，先填充左上角的子表格，然后是右下角的子表格，接着是左下角的子表格，最后是右上角的子表格。每个较小的子表格会继续被分割成更小的子表格，直到分割成 $2 \times 2$ 的表格，并按照上述顺序填充。

现在 Vadim 迫不及待要开始填充表格了，但他有 $q$ 个两种类型的问题：

1. 位于第 $x$ 行第 $y$ 列的单元格中的数字是多少；
2. 数字 $d$ 位于哪个单元格坐标中。

请帮助回答 Vadim 的问题。

## 说明/提示

第一个样例的填充表格如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2093D/02d87014c7c132f45a9dd8ced0465346348b00e4.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
2
5
-> 4 3
<- 15
<- 4
-> 3 1
-> 1 3
1
8
-> 1 1
-> 1 2
-> 2 1
-> 2 2
<- 1
<- 2
<- 3
<- 4```

### 输出

```
7
2 3
1 2
9
13
1
4
3
2
1 1
2 2
2 1
1 2```

# 题解

## 作者：dg114514 (赞：4)

怎么题解代码看起来都好复杂，遂自己写一篇。\
可以把这个 $2^n\times 2^n$ 的表格分成四个 $2^{n-1}\times2^{n-1}$ 的小表格。（左上、右上、左下、右下）令 $solve1(x,y,n)$ 表示在 $2^n\times 2^n$ 的表格中位于第 $x$ 行第 $y$ 列的单元格中的数字，则有：

- 当 $x,y$ 属于左上的小表格时，$solve1(x,y,n)=solve1(x,y,n-1)$，因为 Vadim 先从左上角开始填。
- 当 $x,y$ 属于右下的表格时，$solve1(x,y,n)=solve1(x,y,n-1)+2^{2n-2}$，因为 Vadim 先填完左上角，然后再填右下角的小表格。左上角共有 $2^{2n-2}$ 个数，所以加上 $2^{2n-2}$。
- 当 $x,y$ 属于左下角时，$solve1(x,y,n)=solve1(x,y,n-1)+2^{2n-1}$，Vadim 填完上述的两个小表格后再填左下角，两个小表格共有 $2^{2n-2}\times 2=2^{2n-1}$ 个数。
- 当 $x,y$ 在右上边时，$solve1(x,y,n)=solve1(x,y,n-1)+2^{2n-2}\times 3$，原因跟前面一样。

**边界条件：$solve(x,y,0)=1$，非常显然也非常重要。**

至此，操作一已经做完了，操作二其实也类似，也是看 $x,y$ 是属于哪个小表格，然后递归下去。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define UL 0//左上 
#define UR ((1ll<<(2*n-2))*3)//右上 
#define DL (1ll<<(2*n-1))//左下 
#define DR (1ll<<(2*n-2))//右下 
#define N (1ll<<n-1)//大小 
using namespace std;
inline int get1(int x,int y,int n){//query 1
	if(n==0)
		return 1;
	if(x>N){
		if(y>N) return DR+get1(x-N,y-N,n-1);
		else return DL+get1(x-N,y,n-1);
	}else if(y>N) return UR+get1(x,y-N,n-1);
	return UL+get1(x,y,n-1);
}
inline pair<int,int> get2(int d,int n){//query 2
	if(n==0) return make_pair(1,1);
	if(d>UL&&d<=DR) return get2(d-UL,n-1);
	if(d>DR&&d<=DL){
		auto [x,y]=get2(d-DR,n-1);
		return make_pair(x+N,y+N);
	}
	if(d>DL&&d<=UR){
		auto [x,y]=get2(d-DL,n-1);
		return make_pair(x+N,y);
	}
	auto [x,y]=get2(d-UR,n-1);
	return make_pair(x,y+N);
}
signed main() {
	cin.tie(0)->sync_with_stdio(0);
	int T,n,q,x,y;string s;
	cin>>T;
	while(T--){
		cin>>n>>q;
		while(q--){
			cin>>s>>x;
			if(s=="->")
				cin>>y,cout<<get1(x,y,n)<<"\n";
			else{
				auto [a,b]=get2(x,n);
				cout<<a<<" "<<b<<"\n";
			}
		}
	}
}
```

---

## 作者：枫原万叶 (赞：4)

# CF2093D Skibidi Table 题解

## 分析

题目大概意思是把一个边长为 $ 2^n $ 的表格分割并填数字，以左上、右下、左下、右上的顺序填充（具体参考[题面](https://www.luogu.com.cn/problem/CF2093D)）。然后给两种问题：

- 给 $ (x,y) $ 坐标求对应数字。
- 给出数字求对应坐标。

这里分析一下大概思路：

对于坐标求数字我们可以用递归思路。

判断当前坐标是属于四个区块中的哪一个，然后调整当前区块的起点和数值基值，接下来就继续分治。

如果当前区块的大小为 $ 2 \times 2 $ 就根据它属于的区块直接返回数字即可。

同样的，我们也可以用递归找到数字对应的坐标。

判断数字属于四个区块中的哪一个，调整数值基值和区块的起点，然后继续分治。

如果当前区块的大小为 $ 2 \times 2 $ 就根据数值确定坐标。

就拿给出样例的输入 1 中的 $ n = 2 $（区块大小为 $ 4 \times 4 $）为例：

**查数字**`-> 4 3`:

表格分割为四个 $ 2 \times 2 $ 的子区块。

坐标 $ (4,3) $ 属于右下角的子区块，分治处理，数值基值为 $ 5 $。

在右下角子区块中，坐标为 $ (2,1) $，对应数值为 $ 5 + 2 = 7 $。

**查坐标**`<- 15`:

数值 $ 15 $ 属于右上角子块（右上角范围 $ 13 \sim 16 $ ），基值为 $ 13 $。

在右上角子区块，偏移距离为 $ 15 - 13 = 2 $，对应坐标为 $ (2,3) $。

由此就可以得到答案。

可能这里的描述不够详细，具体可以看代码注释。

## 代码

[记录](https://codeforces.com/problemset/submission/2093/316953572)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

// 根据数字d求坐标(x,y)
void f(ull d, int k, int x, int y, ull b, int &rx, int &ry) {
	if (k == 1) { // 递归到2x2块
		ull t = d - b;
		if (t == 0)
			rx = x, ry = y;
		else if (t == 1)
			rx = x + 1, ry = y + 1;
		else if (t == 2)
			rx = x + 1, ry = y;
		else
			rx = x, ry = y + 1;
	} else {
		ull s = 1ULL << (2 * (k - 1)); // 子块数值范围
		int h = 1 << (k - 1); // 子块边长的一半
		if (d < b + s)
			f(d, k - 1, x, y, b, rx, ry);
		else if (d < b + 2 * s)
			f(d, k - 1, x + h, y + h, b + s, rx, ry);
		else if (d < b + 3 * s)
			f(d, k - 1, x + h, y, b + 2 * s, rx, ry);
		else
			f(d, k - 1, x, y + h, b + 3 * s, rx, ry);
	}
}

// 根据坐标(x,y)求数字
ull c(int x, int y, int k, int x0, int y0, ull b) {
	if (k == 1) { // 递归到2x2块
		int dx = x - x0, dy = y - y0;
		if (!dx && !dy)
			return b;
		else if (dx == 1 && dy == 1)
			return b + 1;
		else if (dx == 1 && !dy)
			return b + 2;
		else
			return b + 3;
	} else {
		int h = 1 << (k - 1); // 当前块半长
		int mx = x0 + h - 1, my = y0 + h - 1; // 中间点
		ull s = 1ULL << (2 * (k - 1)); // 子块数值范围
		if (x <= mx && y <= my)
			return c(x, y, k - 1, x0, y0, b);
		else if (x > mx && y > my)
			return c(x, y, k - 1, x0 + h, y0 + h, b + s);
		else if (x > mx)
			return c(x, y, k - 1, x0 + h, y0, b + 2 * s);
		else
			return c(x, y, k - 1, x0, y0 + h, b + 3 * s);
	}
}

int main() {
	int T, n, q;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &q);
		while (q--) {
			char op[3];
			scanf("%s", op);
			if (op[0] == '-') { // 坐标转数字
				int x, y;
				scanf("%d%d", &x, &y);
				printf("%llu\n", c(x, y, n, 1, 1, 1));
			} else { // 数字转坐标
				ull d;
				scanf("%llu", &d);
				int x, y;
				f(d, n, 1, 1, 1, x, y);
				printf("%d %d\n", x, y);
			}
		}
	}
	return 0;
}
```

---

## 作者：Killer_Steven (赞：3)

# 题目大意  
有一个 $2^n \times 2^n$ 的矩阵，已经用 $1$ 到 $2^{2n}$ 的数字填满了这个矩阵，填充规则如下：  
1. 将矩阵平均分为四部分。
2. 按照左上、右下、左下、右上的顺序填涂。  
3. 将获得的新矩阵重复执行以上操作，直到矩阵大小为 $1 \times 1$。  

**~当然，矩阵长什么样要自己推。~**  
这是一个例子：  

![](https://cdn.luogu.com.cn/upload/image_hosting/3ayuuxsm.png)   
然后，给你 $q$ 次询问，分为两种情况：  
1. 给你 $x$ 和 $y$，让你求出这个坐标上的值。
2. 给你一个值 $d$，求出这个值所在的坐标。

# 做题思路  
有些类似于二分，不过是二维的。  
按题意把区间分为四块，判断给定的坐标（数值）属于哪一块，然后在这块里继续递归，直到矩阵只剩 $1 \times 1$。  
## 处理坐标  
就拿上面的例子来说，假如 $x=3$，$y=2$，那么先将整个矩阵分为平均四块，$x > 2$，所以要查找的值在矩阵的下侧，而 $y = 2$ 在矩阵左侧，所以将矩阵更新为：  
![](https://cdn.luogu.com.cn/upload/image_hosting/bkxade3z.png)    
**这里将 $x$ 的值更新了，并重新给矩阵的行列排序，方便进行操作。**  
再次按上述方法进行查找，又将矩阵更新为：
![](https://cdn.luogu.com.cn/upload/image_hosting/y996iygi.png)    
此时矩阵大小只剩 $1 \times 1$，返回并退出。   
代码：  
```cpp
inline ll sfen (ll MAX, ll zhi) {
	if (MAX == 1)
		return zhi;
	if (x <= sqrt (MAX) / 2) {
		if (y <= sqrt (MAX) / 2) {
			return sfen (MAX / 4, zhi);
		} else {
			y -= sqrt (MAX / 4);
			return sfen (MAX / 4, zhi + ( (MAX / 4) * 3) );
		}
	} else {
		if (y <= sqrt (MAX) / 2) {
			x -= sqrt (MAX / 4);
			return sfen (MAX / 4, zhi + (MAX / 2) );
		} else {
			x -= sqrt (MAX / 4), y -= sqrt (MAX / 4);
			return sfen (MAX / 4, zhi + (MAX / 4) );
		}
	}
}
```
## 处理数值  
和处理坐标差不多，也是将矩阵分为四个部分，假设 $d = 7$，仍然是上面给出的例子。
先分为 $4$ 个矩阵，可以明显发现 $4 < d < 8$，所以将矩阵更新为：  
![](https://cdn.luogu.com.cn/upload/image_hosting/mdgjjnv8.png)    
因为此时 $x$ 一定大于 $2$，$y$ 也一定大于 $2$，所以将它们分别更新为 $2$。
重复上述方法，又将矩阵更新为：
![](https://cdn.luogu.com.cn/upload/image_hosting/c0u5i2yz.png)    
$x$ 更新为 $2 + 1 = 3$，但 $y$ 在此时并不能判断出它会比以前的范围更小（因为两个变量单调不递减），所以 $y$ 值不变。  
此时矩阵大小只剩 $1 \times 1$，返回当前 $x$ 和 $y$ 位置上的值并退出。   
代码：  
```cpp
inline void sfn (ll MAX, ll zhi) {
	/*与所讲方法不同的是，这里在每一次更新矩阵
	后将给出的d值进行了修改，使它一定小于等于
	当前矩阵的大小，因为代码里的判断条件是现在
	查找的值处于矩阵的哪个位置，并不是按矩阵中
	的元素进行判断的，如样例中，在第一次更新后
	d应该更新为3，因为矩阵大小变为了4，要将所给
	的值的大小变得比矩阵小，然后3显然在2<3<4中，
	所以新找到的值位于左下角*/
	if (MAX == 1)
		return;
	if (zhi <= MAX / 4) {
		sfn (MAX / 4, zhi);
	} else if (zhi <= MAX / 2) {
		x += sqrt (MAX / 4), y += sqrt (MAX / 4);
		sfn (MAX / 4, zhi -= (MAX / 4) );
	} else if (zhi <= ( (MAX / 4) * 3) ) {
		x += sqrt (MAX / 4);
		sfn (MAX / 4, zhi -= (MAX / 2) );
	} else {
		y += sqrt (MAX / 4);
		sfn (MAX / 4, zhi -= ( (MAX / 4) * 3) );
	}
}
```
# code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define str string
#define db double
using namespace std;
ll t, n, q, x, y, d;           //习惯性开long long
str s;
//这个处理数值
inline void sfn (ll MAX, ll zhi) {
	if (MAX == 1)          //如果矩阵只剩1*1就退出
		return;
	if (zhi <= MAX / 4) {         //左上角
		sfn (MAX / 4, zhi);
	} else if (zhi <= MAX / 2) {  //右下角
		x += sqrt (MAX / 4), y += sqrt (MAX / 4);      //更改所求坐标的值
		sfn (MAX / 4, zhi -= (MAX / 4) );               //更改给定的值，方便后续操作
	} else if (zhi <= ( (MAX / 4) * 3) ) {  //左下角
		x += sqrt (MAX / 4);
		sfn (MAX / 4, zhi -= (MAX / 2) );
	} else {                       //右上角
		y += sqrt (MAX / 4);
		sfn (MAX / 4, zhi -= ( (MAX / 4) * 3) );
	}
}
//这个处理的是坐标
inline ll sfen (ll MAX, ll zhi) {
	if (MAX == 1)
		return zhi;
	if (x <= sqrt (MAX) / 2) {          //坐标在矩上面边这一半
		if (y <= sqrt (MAX) / 2) {
			return sfen (MAX / 4, zhi);
		} else {
			y -= sqrt (MAX / 4);         //限制x、y的值，方便操作
			return sfen (MAX / 4, zhi + ( (MAX / 4) * 3) );          //对所求的答案进行更改，并继续递归
		}
	} else {                 //坐标在矩阵下面这一半
		if (y <= sqrt (MAX) / 2) {
			x -= sqrt (MAX / 4);
			return sfen (MAX / 4, zhi + (MAX / 2) );
		} else {
			x -= sqrt (MAX / 4), y -= sqrt (MAX / 4);
			return sfen (MAX / 4, zhi + (MAX / 4) );
		}
	}
}
int main() {
	//输入输出加速
	ios::sync_with_stdio (false),cin.tie (0),cout.tie (0);
	cin >> t;
	while (t--) {
		cin >> n >> q;
		n = pow (2, 2 * n);      //将n赋值为最大的可以填入矩阵的值
		for (ll i = 1; i <= q; i++) {
			//题中给了，先给出->或<-提示接下来输入的是坐标还是数值
			cin >> s;
			if (s == "->") {
				//注意，这里的x指的是矩阵的行，y指的是列
				cin >> x >> y;
				ll zhi = sfen (n, 1);       //处理坐标
				cout << zhi << endl;
			} else {
				cin >> d, x = y = 1;
				sfn (n, d);        //处理数值
				cout << x << " " << y << endl;
			}
		}
	}
	return 0;
}
```

---

## 作者：IGpig (赞：2)

## CF2093D

### Solution

分制模版题，先处理第一个问题。定义搜索状态 $\operatorname{dfs}(x,y,l,mn,mx)$ 表示当前在 $(x,y)$ 这个位置，当前块的边长为 $l$，当前块内的最大和最小值 $mx,mn$。

初始从最大的那个也就是右下角开始。

~~~cpp
void query1(LL x,LL y,LL l,LL mn,LL mx){
    if(l==1){//找到
        cout<<mn<<endl;
        return ;
    }
    LL len=mx-mn+1;//方便处理
    if(x<=l/2&&y<=l/2){//左上角
        query1(x,y,l/2,mn,mn+len/4-1);
    }
    if(x>l/2&&y>l/2){//右下角
        query1(x-l/2,y-l/2,l/2,mn+len/4,mn+len/2-1);
    }
    if(x>l/2&&y<=l/2){//左下角
        query1(x-l/2,y,l/2,mn+len/2,mn+len/4*3-1);
    }
    if(x<=l/2&&y>l/2){//右上角
        query1(x,y-l/2,l/2,mn+len/4*3,mx);
    }
}
~~~

在第二个问题中只需要加上当前查找的值 $d$ 即可。

从左上角开始，找范围。

~~~cpp
void query2(LL x,LL y,LL l,LL d,LL mn,LL mx){
    if(l==1){
        cout<<x<<' '<<y<<endl;
        return ;
    }
    LL len=mx-mn+1;
    if(d<=mn+len/4-1){
        query2(x,y,l/2,d,mn,mn+len/4-1);
    }
    if(d>=mn+len/4&&d<=mn+len/2-1){
        query2(x+l/2,y+l/2,l/2,d,mn+len/4,mn+len/2-1);
    }
    if(d>=mn+len/2&&d<=mn+len/4*3-1){
        query2(x+l/2,y,l/2,d,mn+len/2,mn+len/4*3-1);
    }
    if(d>=mn+len/4*3&&d<=mx){
        query2(x,y+l/2,l/2,d,mn+len/4*3,mx);
    }
}
~~~



### Code

~~~cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
LL n,q,t,pw[100]={1};
void query1(LL x,LL y,LL l,LL mn,LL mx){
    if(l==1){
        cout<<mn<<endl;
        return ;
    }
    LL len=mx-mn+1;
    if(x<=l/2&&y<=l/2){
        query1(x,y,l/2,mn,mn+len/4-1);
    }
    if(x>l/2&&y>l/2){
        query1(x-l/2,y-l/2,l/2,mn+len/4,mn+len/2-1);
    }
    if(x>l/2&&y<=l/2){
        query1(x-l/2,y,l/2,mn+len/2,mn+len/4*3-1);
    }
    if(x<=l/2&&y>l/2){
        query1(x,y-l/2,l/2,mn+len/4*3,mx);
    }
}
void query2(LL x,LL y,LL l,LL d,LL mn,LL mx){
    //cout<<x<<' '<<y<<endl;
    if(l==1){
        cout<<x<<' '<<y<<endl;
        return ;
    }
    LL len=mx-mn+1;
    if(d<=mn+len/4-1){
        query2(x,y,l/2,d,mn,mn+len/4-1);
    }
    if(d>=mn+len/4&&d<=mn+len/2-1){
        query2(x+l/2,y+l/2,l/2,d,mn+len/4,mn+len/2-1);
    }
    if(d>=mn+len/2&&d<=mn+len/4*3-1){
        query2(x+l/2,y,l/2,d,mn+len/2,mn+len/4*3-1);
    }
    if(d>=mn+len/4*3&&d<=mx){
        query2(x,y+l/2,l/2,d,mn+len/4*3,mx);
    }
}
int main(){
    for(int i=1;i<=60;i++) pw[i]=pw[i-1]*2;
    cin>>t;
    while(t--){
        cin>>n>>q;
        while(q--){
            LL x,y;char c1,c2;
            cin>>c1>>c2;
            if(c1=='-'){
                cin>>x>>y;
                query1(x,y,pw[n],1,pw[n*2]);
            }else {
                cin>>x;
                query2(1,1,pw[n],x,1,pw[n*2]);
            }
        }
    }
    return 0;
}
~~~

---

## 作者：残阳如血 (赞：1)

分治。

由于表格是递归定义的，所以考虑递归地查询。

## 查询 $(x,y)$ 的数字

递归查询。

假设当前的正方形左上角 $(a,b)$，右下角 $(c,d)$，记录当前左上角的值为 $w$。

容易得到正方形边长 $l=c-a=d-b$。

横渐近线为 $y=\dfrac{b+d}{2}$，竖渐近线为 $x=\dfrac{a+c}{2}$。

令 $t=\dfrac{l^2}{4}$，即一个小正方形的大小。

- 左上角 $w_1=w$。
- 右下角 $w_2=t+w$。
- 左下角 $w_3=2t+w$。
- 右上角 $w_4=3t+w$。

递归下去即可。

## 查询 $d$ 的位置

同上容易求出四个小正方形中的 $\min$ 和 $\max$。

找到 $d$ 在哪个区间中，递归下去即可。

## 时间复杂度

时间复杂度 $O(qn)$。

## 代码

[Record](https://codeforces.com/contest/2093/submission/317906681)。

```cpp
#include <bits/stdc++.h>
using lint = long long;
using pll = std::pair<lint, lint>;

int T, n, q;

lint get_val(lint a, lint b, lint c, lint d, lint w, int qx, int qy) {
  lint y = b + d >> 1, x = a + c >> 1;
  lint len = c - a + 1 >> 1;
  lint t = len * len;
  if (a == c) return w;
  if (qx <= x && qy <= y) { // 左上角
    return get_val(a, b, x, y, w, qx, qy);
  } else if (qx > x && qy > y) { // 右下角
    return get_val(x + 1, y + 1, c, d, w + t, qx, qy);
  } else if (qx <= x && qy > y) { // 左下角
    return get_val(a, y + 1, x, d, w + 2 * t, qx, qy);
  } else { // 右上角
    return get_val(x + 1, b, c, y, w + 3 * t, qx, qy);
  }
}

pll get_pos(lint a, lint b, lint c, lint d, lint w, lint val) {
  lint y = b + d >> 1, x = a + c >> 1;
  lint len = c - a + 1 >> 1;
  lint t = len * len;
  if (a == c) return {a, b};
  if (val < w + t) {
    return get_pos(a, b, x, y, w, val);
  } else if (val < w + 2 * t) {
    return get_pos(x + 1, y + 1, c, d, w + t, val);
  } else if (val < w + 3 * t) {
    return get_pos(a, y + 1, x, d, w + 2 * t, val);
  } else {
    return get_pos(x + 1, b, c, y, w + 3 * t, val);
  }
}

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  for (std::cin >> T; T; --T) {
    for (std::cin >> n >> q; q; --q) {
      std::string op; std::cin >> op;
      if (op[0] == '-') {
        lint x, y; std::cin >> x >> y;
        std::cout << get_val(1, 1, 1ll << n, 1ll << n, 1, y, x) << "\n";
      } else {
        lint d; std::cin >> d;
        auto ans = get_pos(1, 1, 1ll << n, 1ll << n, 1, d);
        std::cout << ans.second << " " << ans.first << "\n";
      }
    }
  }
  std::cout.flush();
  return 0;
}
```

---

## 作者：Kendieer (赞：1)

**Links：**[**\[luogu\]**](\problem\CF2093D)、[**\[Codeforces\]**](https://codeforces.com/contest/2093/problem/D)。

## 思路

对于两种查询，我们分开来讨论。

### 查询1

给定表格中的位置 $(x,y)$，求里面的数字是多少。

对于表格中的部分，我们可以以边长为 $2^{n}$ 的正方形作为一个单元，于是原表格就可以划分成 $4$ 个单元格，每个单元格有 $2^{2n}=4^n$ 个格子，并且可以进一步得知里面的每一部分的值域：

**左上角：**$1\sim 2^n$，
**右上角：**$3\times2^n+1\sim 4\times 2^n$\
**左下角：**$2\times2^n+1\sim3\times 2^n$，
**右下角：**$2^n+1\sim 2\times2^n$。

如果这个过程计数从 $0$ 开始，就可以将四个区域值域分为 $[0,4^{n}),[4^n,2\cdot4^n),[2\cdot4^n,3\cdot4^n)$ 和 $[3\cdot4^n,4^{n+1})$。

得到相应的划分区域后，我们又可以将得到的区域在重新按题意划分成 $4$ 个边长为 $2^{n-1}$ 的格子，以此类推。

于是，我们可以轻松地使用 4 进制来模拟这一过程。

### 查询2

我们可以将查询 1 的方式，将一个数字按 4 进制转换，得出的结果再依次按边长为 $2^n,2^{n-1},\cdots$ 的区域划分即可定位到相应位置。

时间复杂度为 $O(qn)$。

## Code

[赛时 Submission](https://codeforces.com/contest/2093/submission/314559409)。

``` cpp
#include <bits/stdc++.h>
#define endl '\n'
#define rep(i,a,b) for(ll i = (a);i < (b);i++)
#define repr(i,a,b) for(ll i = (b) - 1;i>= (a);i--)
#define Code_by_Kendieer while(n--) solve()
// Base type
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using i128 = __int128;
using oiType = ll;
// Container
using namespace std;
using v1d = vector<ll>;
using v2d = vector<v1d>;
using pair_i32 = pair<int,int>;

inline oiType qread(int t=10);
void qwrite(oiType x,int t = 10);
inline char readChar();
std::istream& operator>>(std::istream &is,i128 &x);
std::ostream& operator<<(std::ostream &os,i128 x);
template <typename T> std::ostream& operator<<(std::ostream &os,vector<T> &x);
template <typename T,typename E> std::vector<T>& operator+=(vector<T>& arr,E ele);

constexpr ll inf = 0x3f7f7f7f7f7f7f7f;
constexpr int maxn = 2e5 + 7;
int N = maxn;
constexpr int mod = 998244353;
//mt19937 rnd(time(0));

struct Node {};

void solve(){
    ll n,q;
    cin >> n >> q;
    rep(i,0,q){
        string cmd;
        cin >> cmd;
        ll x,y;
        cin >> x;
        if (cmd == "->"){
            cin >> y;
            ll val = 0;
            x--,y--;
            repr(i,0,n){
                if (x < (1ll<<i)){
                    if (y >= (1ll<<i)){
                        val += (1ll<<i) * (1ll<<i) * 3;
                    }
                } else {
                    if (y < (1ll<<i)){
                        val += (1ll<<i) * (1ll<<i) * 2;
                    } else {
                        val += (1ll<<i) * (1ll<<i) * 1;
                    }
                }
                x %= (1ll<<i),y %= (1ll<<i);
            }
            cout << val+1 << endl;
        } else {
            ll a = 0,b = 0;
            x--;
            repr(i,0,n){
                ll d = x / ((1ll<<(i<<1)));
                if (d == 1){
                    a += (1ll<<i),b += (1ll<<i);
                } else if (d == 2){
                    a += (1ll<<i);
                } else if (d == 3) {
                    b += (1ll<<i);
                }
                x %= (1ll<<(i<<1));
            }
            cout << a + 1 << " " << b+1 << endl;
        }
    }
}

signed main(){
    std::cin.tie(0),std::cout.tie(0);
    std::ios::sync_with_stdio(0);
    int n = 1;
    std::cin >> n;
    Code_by_Kendieer;
    return 0;
}
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 |  Tips: QuickOI: 快速输入输出，仅需使用 qio >> (变量) 即可读入，qio << (变量) 即可输出，qio.base 是输入输出的进制。
 |            qread() 为快读函数，读取下一个 t 进制整数（默认为十进制）。
 |            qwrite(x,t) 为快写函数，以t进制形式输出一个整数 x（默认为十进制）。
 |            readChar() 为读取下一个非空字符（跳过空格、换行）
 |        rep(变量名,a,b) 为 for 循环，自变量为变量名，循环为 [a,b) 顺序走。
 |        repr(变量名,a,b) 为 for 循环，自变量为变量名，循环为 [a,b) 倒序走。
 |        endl 已被重定义为 '\n'，而不是 "\r\n"。
 |        cin >> __int128, cout << __int128 已经被重载，能正常使用。
 |        vector<T> += 已被重定义为push_back()
 |
 |   main 函数仅包含实现 t 组测试，无需关注，具体每组实现只需查看 solve() 即可。
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
inline oiType qread(int t){
    oiType r = 0,s = 1,ch = getchar();
    while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
    if (ch == '-') ch = getchar(),s = -1;
    while ((ch >= '0'&&ch <= '9')||(ch>='A'&&ch<='Z')) r=r*t+ch-'0'+(ch>='A'?10:0),ch = getchar();
    return r * s;
}
inline char readChar(){
    int ch = getchar();
    while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
    return ch;
}
void qwrite(oiType x,int t){
    if (x<0) putchar('-'),x=-x;
    if (x>=t) qwrite(x/t,t);
    putchar(x%t<10?'0'+x%t:'A'-10+x%t);
}
std::istream& operator>>(std::istream& is,i128 &x){
    std::string s;i128 sign = 1;
    is >> s,x = 0;
    for(int i(0);i<s.size();i++)if (s[i] == '-') sign = -1;else x*=10,x+=s[i]-'0';
    x *= sign;
    return is;
}
std::ostream& operator<<(std::ostream& os,i128 x){
    if (x == 0) {
        return os << 0;
    } else if (x < 0)
        os << "-",x = -x;
    std::string s = "";
    while(x) s += x%10+'0',x /= 10;
    std::reverse(s.begin(), s.end());
    os << s;
    return os;
}
template <typename T>
std::ostream& operator<<(std::ostream &os,vector<T> &x){
    for (int i = 0; i < x.size(); ++i) {
        os << x[i] << " \n"[i==x.size()-1];
    }
    return os;
}
template <typename T,typename E>
std::vector<T>& operator+=(vector<T>& arr,E ele){
    arr.push_back((T)ele);
    return arr;
}
/*
 >> Model Last updated: 04/08/2025 <<
=============================================================================
  ___         _       _           _  __            _ _
 / __|___  __| |___  | |__ _  _  | |/ /___ _ _  __| (_)___ ___ _ _
| (__/ _ \/ _` / -_) | '_ \ || | | ' </ -_) ' \/ _` | / -_) -_) '_|
 \___\___/\__,_\___| |_.__/\_, | |_|\_\___|_||_\__,_|_\___\___|_|
                           |__/
==============================================================================
*/
```

---

## 作者：x1489631649 (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/CF2093D)
### 分析
按照左上，右下，左下，右上的顺序排列数字，具体可参照样例，询问某个格子里的数字以及某个数字在哪个格子里，这题我们可以使用二分的思想，不断枚举即可，分为两种情况解决。

当问题询问格子编号的时候我们可以分别枚举 $x$ 和 $y$ 的大小。

当枚举数字的时候，我们可以枚举数字大小。

此处的枚举都是按照 $2$ 的倍数来枚举的，和二分有点相似。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
void slove1(int n,int s,int x,int y)
{
	if(s==1)
	{
		cout<<x<<" "<<y<<endl;
		return;
	}
	int p=(s/2)*(s/2);
	if(n<=p)//左上
		slove1(n,s/2,x,y);
	else if(n<=2*p)//右下
		slove1(n-p,s/2,x+(s/2),y+(s/2));
	else if(n<=3*p)//左下
		slove1(n-2*p,s/2,x+(s/2),y);
	else slove1(n-3*p,s/2,x,y+(s/2));//右上
	return;
}
void slove2(int x,int y,int n,int s)//同理逆推
{
	if(s==1)
	{
		cout<<n<<endl;
		return;
	}
	int p=(s/2)*(s/2);
	if(x>s/2&&y>s/2)
		slove2(x-s/2,y-s/2,n+p,s/2);
	else if(x>s/2&&y<=s/2)
		slove2(x-s/2,y,n+2*p,s/2);
	else if(x<=s/2&&y>s/2)
		slove2(x,y-s/2,n+3*p,s/2);
	else slove2(x,y,n,s/2);
	return;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,q;
		cin>>n>>q;
		int s=1;
		for(int i=1;i<=n;i++)
			s*=2;
		while(q--)
		{
			string str;
			int x,y;
			cin>>str;
			if(str[0]=='<')
			{
				cin>>x;
				slove1(x,s,1,1);
			}
			else{
				cin>>x>>y;
				slove2(x,y,1,s);
			}
		}
	}
	return 0;
}
```
### 时间复杂度
每块方格最多走一次，时间复杂度为 $O(\log n)$，显然可以通过。

---

## 作者：cwxcplh (赞：0)

~~一道很水的分治……~~

**题目大意：** 已知瓦迪姆喜欢按照左上、右下、左下、右上的顺序填格子，现在请问：

1. 第 $x$ 行 $y$ 列的数是什么。
2. 数字 $d$ 在哪。

这是一道明显的分治题，因为他填格子的方法全都是一样的，我们只需要找出这个分治怎么分就对了。

首先我们看第一个问题。定义一个 `dfs1` 表示当前分治所用的深搜函数。我们来思考一下我们需要传哪些参数。

首先肯定要当前的取值范围，这是我们锁定一个值的必要东西。其次就是当前坐标，因为我们到每一个小格子后的坐标会变，所以我们不能一直拿先前的坐标来更新。最后就是当前放个的边长，这个主要是帮忙进行坐标转化。

那么我们就可以定义 `dfs1(int x,int y,int l,int sl,int sr)`，分别表示当前的横坐标、当前的纵坐标、当前格子的边长、当前的最低取值、当前的最高取值，然后我们就可以开始转化了：

$$\begin{cases}\operatorname{dfs1}(x,y,\frac{l}{2},sl,sl+\frac{(sr-sl+1)}{4}-1)&\operatorname{if}1\le x\le \frac{l}{2},1\le y \le \frac{l}{2}\\\operatorname{dfs1}(x-\frac{l}{2},y-\frac{l}{2},\frac{l}{2},sl+\frac{(sr-sl+1)}{4},sl+\frac{(sr-sl+1)}{2}-1)&\operatorname{if}\frac{l}{2}\lt x\le l,\frac{l}{2}\lt y \le l\\\operatorname{dfs1}(x-\frac{l}{2},y,\frac{l}{2},sl+\frac{(sr-sl+1)}{2},sl+\frac{(sr-sl+1)}{4}\times3-1)&\operatorname{if}\frac{l}{2}\lt x\le l,1\le y \le \frac{l}{2}\\\operatorname{dfs1}(x,y-\frac{l}{2},\frac{l}{2},sl+\frac{(sr-sl+1)}{4}\times3,sr)&\operatorname{if}1\le x\le \frac{l}{2},\frac{l}{2}\lt y \le l\end{cases}$$

另一种问题同样如此（转化自己推）。

**代码实现：**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,q,pw_2[66];
void dfs1(int x,int y,int l,int sl,int sr)
{
    if(l==1)
    {
        cout<<sl<<endl;
        return;
    }
    if(x>=1&&x<=l/2&&y>=1&&y<=l/2)
    {
        dfs1(x,y,l/2,sl,sl+(sr-sl+1)/4-1);
    }
    else if(x>l/2&&x<=l&&y>l/2&&y<=l)
    {
        dfs1(x-l/2,y-l/2,l/2,sl+(sr-sl+1)/4,sl+(sr-sl+1)/2-1);
    }
    else if(x>l/2&&x<=l&&y>=1&&y<=l/2)
    {
        dfs1(x-l/2,y,l/2,sl+(sr-sl+1)/2,sl+(sr-sl+1)/4+(sr-sl+1)/2-1);
    }
    else
    {
        dfs1(x,y-l/2,l/2,sl+(sr-sl+1)/2+(sr-sl+1)/4,sr);
    }
}
void dfs2(int x,int y,int s,int l,int sl,int sr)
{
    if(l==1)
    {
        cout<<x<<" "<<y<<endl;
        return;
    }
    if(s>=sl&&s<=sl+(sr-sl+1)/4-1)
    {
        dfs2(x,y,s,l/2,sl,sl+(sr-sl+1)/4-1);
    }
    else if(s>=sl+(sr-sl+1)/4&&s<=sl+(sr-sl+1)/2-1)
    {
        dfs2(x+l/2,y+l/2,s,l/2,sl+(sr-sl+1)/4,sl+(sr-sl+1)/2-1);
    }
    else if(s>=sl+(sr-sl+1)/2&&s<=sl+(sr-sl+1)/2+(sr-sl+1)/4-1)
    {
        dfs2(x+l/2,y,s,l/2,sl+(sr-sl+1)/2,sl+(sr-sl+1)/2+(sr-sl+1)/4-1);
    }
    else
    {
        dfs2(x,y+l/2,s,l/2,sl+(sr-sl+1)/2+(sr-sl+1)/4,sr);
    }
}
string s;
signed main()
{
    pw_2[0]=1;
    for(int i=1;i<=65;i++)
    {
        pw_2[i]=pw_2[i-1]<<1;
    }
    cin>>t;
    while(t--)
    {
        cin>>n>>q;
        int x=0,y=0;
        while(q--)
        {
            cin>>s;
            if(s=="->")
            {
                cin>>x>>y;
                dfs1(x,y,pw_2[n],1,pw_2[2*n]);
            }
            else
            {
                cin>>x;
                dfs2(1,1,x,pw_2[n],1,pw_2[n*2]);
            }
        }
    }
    return 0;
}
```

---

## 作者：Ag2WO4 (赞：0)

观察样例可以发现，假设表起点为 $0$，每个四数块内数除以四的商数相等，而且合并之后和另外三个四数块组成和原来一样的四数块。总结得到每个单元块扩展都是横竖倍增，高低位互不影响，于是每两位为单位，四角和样例一样，按位模拟即可。

具体的做法是找到一一对应的映射：$\sum2^{2k}x(k)\leftrightarrow(\sum2^kf(k),\sum2^kg(k))$，其中 $f$ 和 $g$ 关于 $x$ 的双向映射如下表：



|$x$|$f$|$g$|
|:-:|:-:|:-:|
|0|0|0|
|1|1|1|
|2|1|0|
|3|0|1|



复杂度 $O(nq)$。
```python
for _ in range(int(input())):
    n=int(input())
    for i in range(int(input())):
        a=input()
        if'-'==a[0]:
            a,b,c=a.split();a=0;b=int(b)-1;c=int(c)-1
            for j in range(n):
                if b&(1<<j):
                    if c&(1<<j):a+=1<<(j*2)
                    else:a+=2<<(j*2)
                elif c&(1<<j):a+=(1<<(j*2))+(2<<(j*2))
            print(a+1)
        else:
            a,b=a.split();c=int(b)-1;a=b=0
            for j in range(n):
                if c&(2<<(j*2)):
                    if c&(1<<(j*2)):b+=1<<j
                    else:a+=1<<j
                elif c&(1<<(j*2)):a+=1<<j;b+=1<<j
            print(a+1,b+1)
```

---

## 作者：lw393 (赞：0)

这道题难点在于怎么高效实现 $O(n)$ 的查询（$n$ 为题目中给出的 $n$）。

我们在这道题中不难想到利用当前正方形的中心，将这个正方形一分为四。

在第一类查询中我们设当前查询到了以 $(x1, y1)$ 与 $(x2, y2)$ 为左上与右下格点的矩形，左上格的值为 $now$。我们需要找到 $(qx, qy)$ 格子的值。设 $midx = \lfloor \frac{x1 + x2}{2} \rfloor, midy = \lfloor \frac{y1 + y2}{now}\rfloor$，那么有四种情况：

1. 若 $qx \in [x1, midx]$ 且 $qy \in [y1, midy]$ 那么将矩形转移到 $(x1, y1),(midx, midy)$，这种情况下 $now$ 不变。

2. 若 $qx \in (midx, x2]$ 且 $qy \in [y1, midy]$ 那么将矩形转移到 $(midx + 1, y1), (x2, midy)$，将 $now$ 修改为 $now + (midx - x1 + 1)(midy - y1 + 1)$。

3. 若 $qx \in [x1, midx]$ 且 $qy \in (midy, y2]$ 那么将矩形转移到 $(x1, midy + 1), (midx, y2)$，将 $now$ 修改为 $now + 2(midx - x1 + 1)(midy - y1 + 1)$。

4. 若 $qx \in (midx, x2]$ 且 $qy \in (midy, y2]$ 那么将矩形转移到 $(midx + 1, midy + 1), (x2, y2)$，将 $now$ 修改为 $now + 3(midx - x1 + 1)(midy - y1 + 1)$。

我们类似地递归处理第二类查询。

设求 $qnow$ 对应的格子的 $x,y$ 坐标，这次我们只需要判断 $now + k(midx - x1 + 1)(midy - y1 + 1)$ 其中 $(k\in \{0,1,2,3\})$ 与 $qnow$ 的关系就好了，这与第一类的查询是十分相似的。

给出查询代码：
```cpp
int calc1(int x1, int x2, int y1, int y2, int now, int qx, int qy) {
  if(x1 == x2 && y1 == y2) return now;
  int midx = (x1 + x2) >> 1;
  int midy = (y1 + y2) >> 1;
  int len = midx - x1 + 1;
  int add = len * len;
  if(qx <= midx && qy <= midy) return calc1(x1, midx, y1, midy, now, qx, qy);
  else if(qx > midx && qy > midy) return calc1(midx + 1, x2, midy + 1, y2, now + add, qx, qy);
  else if(qx > midx && qy <= midy) return calc1(midx + 1, x2, y1, midy, now + 2 * add, qx, qy);
  else return calc1(x1, midx, midy + 1, y2, now + 3 * add, qx, qy);
}
 
pair<int, int> calc2(int x1, int x2, int y1, int y2, int now, int qd) {
  if(x1 == x2 && y1 == y2) return {x1, y1};
  int midx = (x1 + x2) >> 1;
  int midy = (y1 + y2) >> 1;
  int len = midx - x1 + 1;
  int add = len * len;
  if(qd < now + add) return calc2(x1, midx, y1, midy, now, qd);
  else if(qd < now + 2 * add) return calc2(midx + 1, x2, midy + 1, y2, now + add, qd);
  else if(qd < now + 3 * add) return calc2(midx + 1, x2, y1, midy, now + 2 * add, qd);
  else return calc2(x1, midx, midy + 1, y2, now + 3 * add, qd);
}
```

---

## 作者：metrixgo_caozhendi (赞：0)

题目大意是给定 $2^n\times2^n$ 的表格，将该表格填满后会问你一些问题。填满的定义是如果当前就剩一格，则填入 $x$（$x$ 初始为 $0$），随后将 $x$ 加上 $1$；否则将当前表格四等分，然后依次填满左上角，右下角，左下角，和右上角。有点类似递归。我们来分析一下：

首先，最大的难点在于 $n\le30$ 就会导致最大要 $2^{30}\times2^{30}$ 的数组，这显然太大了，所以不能模拟，只能用算法推导。我们可以这么想：给定一个坐标或一个数后，我们可以轻松判断它在哪个角落（举例：在 $n=2$ 时给定数 $15$，由于 $15\ge13$，我们可以知道它在右上角）。随后在那个角落里继续判断它在哪个更小的角落（注意要减去对应的数，保证新的角落就是从 $1$ 开始），不断重复直到确定了要找的位置。记录下来每一次判断的角落，塞到一个队列或者栈里，然后再递归回去并进行相应的运算，就可以得到最后的结果。

有点懵？这里举个具体的例子：$n=2$ 时给定数 $15$。我们知道左上角是 $1\le x\le4$，右下角是 $5\le x\le8$，左下角是 $9\le x\le12$，右上角是 $13\le x\le16$，所以判断到它在右上角。将右上角这一信息推入一个栈中。然后，将 $15$ 减去 $12$ 得到 $3$，这样在右上角就是一个新的网格，大小变为 $2\times2$。我们知道左上角是 $1$，右下角是 $2$，左下角是 $3$，右上角是 $4$，所以判断到它在左下角。将左下角这一信息推入一个栈中。至此信息储存完毕，开始往回递归：第一个信息是左下角，所以位移是 $(1,0)$。下一个信息是右上角，但是这一次是在 $4\times4$ 的网格中，所以位移是 $(0,2)$。将两次位移叠加在初始的 $(1,1)$ 上得到正确答案 $(2,3)$。对比下面的图片可以更好理解。对于给定坐标求数也是同一个道理，只不过需要用队列，因为数优先关注的是在初始网格的哪个角落（自己模拟一下就知道了）。

![4 by 4](https://espresso.codeforces.com/f70a390d49a50f7cdab1f0d592a840a0fd81b309.png)

仅凭文字无法准确描述，下面是代码，手动模拟可以更好地理解：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,m,t,a,b,c,ans,ans2;
string d;
queue<int> q;
stack<int> s;
int main()
{
	cin>>t;
  	while(t--){
		cin>>n>>m;
		while(m--){
			cin>>d;
			if(d=="->"){
				cin>>a>>b;
				c=pow(2,n-1);
				while(q.size()) q.pop();
				while(c){
					if(a<=c&&b<=c) q.push(1);
					else if(a<=c&&b>c){
					    q.push(4);
					    b-=c;
				    }
					else if(a>c&&b<=c){
					    q.push(3);
					    a-=c;
					} 
					else{
					    q.push(2);
					    a-=c,b-=c;
					}
					c/=2;
				}
				c=pow(2,2*n-2);
				ans=1;
				while(q.size()){
					ans+=(q.front()-1)*c;
					c/=4;
					q.pop();
				}
				cout<<ans<<endl;
			}
			else{
				cin>>a;
				c=pow(2,2*n-2);
				while(s.size()) s.pop();
				while(c){
				    if(a>3*c){
				        s.push(2);
				        a-=3*c;
				    }
					else if(a>2*c){
					    s.push(3);
					    a-=2*c;
					}
					else if(a>c){
					    s.push(4);
					    a-=c;
					}
					else s.push(1);
					c/=4;
				}
				c=1;
				ans=1,ans2=1;
				while(s.size()){
				    if(s.top()==2) ans2+=c;
				    else if(s.top()==3) ans+=c;
				    else if(s.top()==4) ans+=c,ans2+=c;
				    c*=2;
				    s.pop();
				}
				cout<<ans<<" "<<ans2<<endl;
			}
		}
	}
   return 0;
}
```

---

## 作者：Phigros_11calors (赞：0)

### 题意

这道题的意思是有一个 $2^n \times 2^n$ 的表格，填数方法如下：
- 如果 $n$ 等于 $0$，填上没有填过的最小正整数。
- 否则，把表格分为 $4$ 个 $2^{n-1} \times 2^{n-1}$ 的小表格，按左上、右下、左下、右上的顺序递归填充每一个小表格。

有两种操作：
- 给两个数 $x,y$，问你第 $x$ 行第 $y$ 列的数填的是多少。
- 给一个数 $d$，问你这个数在第几行第几列。

### 思路
直接模拟肯定 TLE。

注意到每次把表格分成 $4$ 个小表格，右下表格的每个数都比左上表格的对应数大 $2^{2(k-1)}$（这里 $k$ 是当前表格的层数），左下表格的每个数比右下表格的对应数大 $2^{2(k-1)}$，右上同理。因此我们可以使用递归方法解决这道题。

对于第一种操作，每次确定要查询的位置在哪一个小表格里，然后通过位运算递归统计结果。对于第二种操作，每次确定要查询的数在哪一个小表格里，然后通过一个 `pair` 返回坐标。

### 代码

代码中递归函数为了方便位运算处理，将原本题意的坐标从 $1$ 开始改为了从 $0$ 开始，因此最终答案要加 $1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
typedef long long ll;
typedef pair<int,int> pii;
int n;
ll sol1(ll a,ll b,int m){
	if(m<0)return 0;
	if(!(a>>m)&&!(b>>m))return sol1(a,b,m-1);
	if((a>>m)&&(b>>m))return (1ll<<(m<<1))+sol1(a&((1<<m)-1),b&((1<<m)-1),m-1);
	if((a>>m)==1&&!(b>>m))return (2ll<<(m<<1))+sol1(a&((1<<m)-1),b&((1<<m)-1),m-1);
	if(!(a>>m)&&(b>>m))return (3ll<<(m<<1))+sol1(a&((1<<m)-1),b&((1<<m)-1),m-1);
}
pair<ll,ll> sol2(ll d,int m){
	pair<ll,ll> ans;
	if(m<0){
		ans.first=ans.second=0;
		return ans;
	}
	if(d>>(m<<1)==0)return sol2(d,m-1);
	if(d>>(m<<1)==1){
		ans=sol2(d&((1ll<<(m<<1))-1),m-1);
		ans.first+=(1ll<<m);
		ans.second+=(1ll<<m);
	}
	if(d>>(m<<1)==2){
		ans=sol2(d&((1ll<<(m<<1))-1),m-1);
		ans.first+=(1ll<<m);
	}
	if(d>>(m<<1)==3){
		ans=sol2(d&((1ll<<(m<<1))-1),m-1);
		ans.second+=(1ll<<m);
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		int q;
		cin>>q;
		while(q--){
			char a;
			cin>>a;
			cin>>a;
			if(a=='>'){
				ll c,d;
				cin>>c>>d;
				cout<<sol1(c-1,d-1,n-1)+1<<endl;
			}
			else{
				ll k;
				cin>>k;
				auto j=sol2(k-1,n-1);
				cout<<j.first+1<<" "<<j.second+1<<endl;
			}
		}
	}
}


```

[AC 记录](https://codeforces.com/contest/2093/submission/314562728)

---

