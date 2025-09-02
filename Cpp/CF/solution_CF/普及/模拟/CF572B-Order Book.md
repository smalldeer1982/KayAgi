# Order Book

## 题目描述

In this task you need to process a set of stock exchange orders and use them to create order book.

An order is an instruction of some participant to buy or sell stocks on stock exchange. The order number $ i $ has price $ p_{i} $ , direction $ d_{i} $ — buy or sell, and integer $ q_{i} $ . This means that the participant is ready to buy or sell $ q_{i} $ stocks at price $ p_{i} $ for one stock. A value $ q_{i} $ is also known as a volume of an order.

All orders with the same price $ p $ and direction $ d $ are merged into one aggregated order with price $ p $ and direction $ d $ . The volume of such order is a sum of volumes of the initial orders.

An order book is a list of aggregated orders, the first part of which contains sell orders sorted by price in descending order, the second contains buy orders also sorted by price in descending order.

An order book of depth $ s $ contains $ s $ best aggregated orders for each direction. A buy order is better if it has higher price and a sell order is better if it has lower price. If there are less than $ s $ aggregated orders for some direction then all of them will be in the final order book.

You are given $ n $ stock exhange orders. Your task is to print order book of depth $ s $ for these orders.

## 说明/提示

Denote (x, y) an order with price $ x $ and volume $ y $ . There are 3 aggregated buy orders (10, 3), (20, 4), (25, 10) and two sell orders (50, 8), (40, 1) in the sample.

You need to print no more than two best orders for each direction, so you shouldn't print the order (10 3) having the worst price among buy orders.

## 样例 #1

### 输入

```
6 2
B 10 3
S 50 2
S 40 1
S 50 6
B 20 4
B 25 10
```

### 输出

```
S 50 8
S 40 1
B 25 10
B 20 4
```

# 题解

## 作者：TheSky233 (赞：2)

## Description

给出 $n$ 条卖出和买入的记录，求这两类记录中交易数量最小和最大的 $s$ 条，均按降序输出。

## Solution

### 前置知识

map 和 set 的运用。

### 思路

创造两个 map 和两个 set，分别存储卖出和买进的记录，如果读到买入记录，就往 set 中插入这个元素对应的 $p_i$，并在 map 把下标为 $p_i$ 的元素加上 $q_i$，反之同理。

输出时，对于卖出记录，我们先正序访问最小的 $s$ 条记录，存进数组中，最后再倒序访问一遍数组输出，对于买进记录，直接输出最大的 $s$ 条即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n,s,a,b;
char ch;
map<int,int> _in;
map<int,int> _out;
set<int,greater<int> > in;
set<int> out;
struct node{
	int aa,bb;
}num[1000005];

int main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		cin>>ch>>a>>b;
		if(ch=='S'){
			_out[a]+=b;
			out.insert(a);
		}
		if(ch=='B'){
			_in[a]+=b;
			in.insert(a);
		}
	}
	set<int>::iterator it;
	t=1;
	for(it=out.begin();it!=out.end()&&t<=s;it++){
		num[t].aa=*it,num[t].bb=_out[*it];
		t++;
	}
	for(t-=1;t>=1;t--){
		cout<<"S "<<num[t].aa<<' '<<num[t].bb<<endl;
	}
	t=1;
	for(it=in.begin();it!=in.end()&&t<=s;it++){
		cout<<"B "<<*it<<' '<<_in[*it]<<endl;
		t++;
	}
	return 0;
}
```
## Conclusion
以 $165ms$ 排在最优解第三，码量也是最优解中最少的，祝大家 $\color{green}\texttt{AC}$ 愉快！

---

## 作者：__YancBuxIya (赞：1)

# Order Book 题解 

------------------

### 题目大意：

题目中说的很清楚，此处不再赘述。

------------------

### 题目分析：

阅读题目可知，整个过程可分为三大步：

- 读入数据，并将合并操作在线完成。

- 按照题意进行枚举，记录答案。
- 输出答案。

------------------ 

### 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i;
char a[1001];
int b[1001],c[1001],anss[100001],ansb[100001],ansss[100001],ansbb[100001],ansa=1,ansk=1;
int main(){
    cin>>n>>m;
    for(i=1;i<=n;i++){
        cin>>a[i]>>b[i]>>c[i];
        if(a[i]=='S') anss[b[i]]+=c[i];//进行合并操作 
        if(a[i]=='B') ansb[b[i]]+=c[i];
    } 
    /*************以上为第一步*************/
    for(i=0;i<=100000;i++){//枚举，桶排序  
        if(anss[i]>0) {
            ansss[ansa]=i;
            ansa++;
        }
        if(ansa>m) break;
    }
    for(i=100000;i>=0;i--){//枚举，桶排序  
        if(ansb[i]>0) {
            ansbb[ansk]=i;
            ansk++; 
        }
        if(ansk>m) break;
    }
    /*************以上为第二步*************/
    for(i=ansa-1;i>=1;i--) {//输出  
        cout<<"S"<<" "<<ansss[i]<<" "<<anss[ansss[i]]<<endl;
    }
    for(i=1;i<ansk;i++){
        cout<<"B"<<" "<<ansbb[i]<<" "<<ansb[ansbb[i]]<<endl;
    }
    return 0;
}
``` 


---

## 作者：Fkxxx (赞：1)

### 思路

首先，将 SELL 和 BUY 交易数据分别存放在两个桶。

接下来，从小到大遍历。取出最小的 $s$ 个：从大到小遍历，取出最大的 $s$ 个。分别存放在 `queue` 和 `stack` 中，如果不到 $s$ 就取完为止。

最后，输出 `queue` 和 `stack` 中的所有元素即可。

### 代码实现:

```cpp
#include<bits/stdc++.h>
using namespace std;
char c ;
int n , s , q[10005] , p[10005] , t1[100005] , t2[100005] , n1 , n2 ;
stack<int> s1 ;
queue<int> s2 ;
signed main(){
	cin >> n >> s ;
	for( int i = 1 ; i <= n ; i ++ ){
		cin >> c >> p[i] >> q[i] ;
		if( c == 'S' ){
			t1[p[i]] += q[i] ;
		}
		else{
			t2[p[i]] += q[i] ;
		}
	}
	for( int i = 1 ; i <= 100000 ; i ++ ){
		if( t1[i] > 0 && n1 < s ){
			s1.push( i ) ;
			n1 ++ ;
		}
	}
	for( int i = 100000 ; i >= 1 ; i -- ){
		if( t2[i] > 0 && n2 < s ){
			s2.push( i ) ;
			n2 ++ ;
		}
	}
	while( !s1.empty() ){
		cout << "S " << s1.top() << " " << t1[s1.top()] << "\n" ;
		s1.pop() ;
	}
	while( !s2.empty() ){
		cout << "B " << s2.front() << " " << t2[s2.front()] << "\n" ;
		s2.pop() ;
	}
	return 0 ;
}
```

---

## 作者：REAL_曼巴 (赞：1)

本文作者把这道题能踩的坑全都踩了一遍，所以特此来写这一篇题解，希望大家不要像我一样调那么久。

题意我认为翻译说的很明确了，我就不再阐述了。

本题是一个纯模拟题。我看到其他题解都用了结构体啊，排序啊，数据结构啊。本蒟蒻的这篇题解是纯用数组模拟出来的，所以新手可以放心看。

因为没有任何的技巧，所以有些步骤会比较繁琐，但是我都会详细解释。

首先是读入。我们可以运用桶的思想，开一个 $s$ 数组，用来存所有卖出的数量。再开一个 $b$ 数组，用来存所有买入的数量。只要在读入中把所有 $p$ 相同值加起来，合并这一步也就完成了。

注意在进行读入买入的时候，可取一下 $p$ 的最大值，方便之后从后往前枚举。也一定要统计一下每种操作后多少种不同的 $q$ 值，为了防止 $s$ 的值多于数据种数时或者没有某种操作时的输出溢出。

第二步就是输出答案了。

首先是对于 $s$ 的操作，我们要找到最小的倒序输出。我们可以正着枚举，之后把答案存到数组中，最后进行输出。

接着是对于 $s$ 的操作，我们要找到最大的倒序输出。我们这时候直接倒着枚举倒着输出即可。

输出的时候由于是数组，会溢出，我们判断一下输出的值是否溢出了，再进行输出。

细节很多，但是完结撒花！

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+7;
int s[maxn],b[maxn];
int ans1[maxn],ans2[maxn];
int main(){
    int n,s1;
    cin>>n>>s1;
    int maxb=-1;
    int ss=0,bb=0;
    while(n--){//读入，并且进行统计操作
        int p,q;
        char opt;
        cin>>opt;
        cin>>p>>q;
        if(opt=='S'){
            if(s[q]==0)ss++;
            s[p]+=q;
        }
        if(opt=='B'){
            if(b[q]==0)bb++;
            maxb=max(maxb,p);
            b[p]+=q;
        }
    }
    int ls=0,lb=0;
    int i=1;
    int j=1;
    if(ss>0){//防止没有操作溢出
        int y=min(s1,ss);//防止操作数比数据种数多
        while(ls!=y){
            if(s[i]!=0){
                ans1[j]=i,ans2[j]=s[i],j++;
                ++ls;
            }
            ++i;
        }
        for(int k=j-1;k>=1;--k){
            if(ans1[k]<1000001)cout<<"S "<<ans1[k]<<" "<<ans2[k]<<endl;
        }
    }
    if(bb>0){//这里同理
        int y=min(s1,bb);
        i=maxb;
        while(lb!=y){
            if(b[i]!=0){
                if(i>=0)cout<<"B "<<i<<" "<<b[i]<<endl;
                ++lb;
            }
            --i;
        }
    }
    return 0;
}
```





---

## 作者：某某某同学 (赞：1)

[题目](https://www.luogu.com.cn/problem/CF572B)

## 数据范围：

$1 \leq n \leq 1000,1 \leq s \leq 50$。

$0 \leq p_i \leq 10^5,1 \leq q_i \leq 10^4$。

**注意：$p_i$ 可能为 $0$。**

## 分析
首先，我们观察数据范围，发现 $0 \leq p_i \leq 10^5$，并且要对每个 $opt_i,p_i$ 均相等的记录合并，所以，我们可以使用数组储存每一种交易类型中，每一种交易金额的订单的数量。

即：

```cpp
int s[100005],b[100005];
//s[i]储存交易金额为i的卖出记录的数量，b[i]同理
```
之后，我们就可以处理输入：

```cpp
for(int i=1;i<=n;i++){
    cin>>opt>>p>>q;
    if(opt=='S'){
        s[p]+=q;//交易金额为p的记录的数量加上q
    }
    else{
        b[p]+=q;//同理
    }
}
```

输入处理完成后，考虑输出。

因为对于买入的记录，我们要按照 $p_i$ 降序输出前 $s$ 条记录，所以只需要从 $ \max(p_i) $ 到 $ \min(p_i) $ 取前 $s$ 条记录（一共不足 $s$ 条记录则全部输出）。

但是，对于卖出记录，因为是降序从大到小输出 $p_i$ 最小的 $s$ 条记录，所以我们从小到大遍历后，要将输出顺序反转一下。

（输出卖出记录的）代码：
```cpp
struct out{
    int cost,num; 
}sout[1005]; 
int s1,s2;
//避免与数组名重复,s1,s2意义同题目中的s

//... ...

for(int i=0;i<=100000;i++){//一定要从0开始
    if(s1==0)break;
    if(s[i]!=0){
       sout[s1].cost=i;
       sout[s1].num=s[i];
       //反转输出顺序，先遍历到的，p较小的，后输出
       s1--;
    }
}
for(int i=s1+1;i<=s2;i++){//考虑不足s个记录的情况，所以从s1+1开始遍历
    cout<<"S "<<sout[i].cost<<" "<<sout[i].num<<endl;
    //按照新顺序输出 
}
```

最后，~~全部加起来，AC 得出来~~。

```cpp
#include<bits/stdc++.h>
using namespace std;
int s[100005],b[100005];
struct out{
	int cost,num; 
}sout[1005]; 
int main(){
	int p,q,n,s1,s2;
	char opt;
	cin>>n>>s1;
	s2=s1;
	for(int i=1;i<=n;i++){
		cin>>opt>>p>>q;
		if(opt=='S'){
			s[p]+=q;
		}
		else{
			b[p]+=q;
		}
	}
    //卖出
	for(int i=0;i<=100000;i++){
		if(s1==0)break;
		if(s[i]!=0){
			sout[s1].cost=i;
			sout[s1].num=s[i]; 
			s1--;
		}
	}
	for(int i=s1+1;i<=s2;i++){
		cout<<"S "<<sout[i].cost<<" "<<sout[i].num<<endl; 
	}
	s1=s2;
    //买入
	for(int i=100000;i>=0;i--){
		if(s1==0)break;
		if(b[i]!=0){
			cout<<"B "<<i<<" "<<b[i]<<endl;
			s1--; 
		}
	}
	return 0;
}
```



---

## 作者：Eason_AC (赞：1)

## Content
账单里面有 $n$ 条记录，只有卖出记录和买入记录两种，并且都包含两个信息 $p_i,q_i$，现在根据这些记录，请执行如下操作：

- 将所有 $p_i$ 相等的同种记录合并（就是只能卖出记录和卖出记录合并，买入记录和买入记录合并，不能将卖出记录和买入记录合并）。
- 合并之后，将所有 $p_i$ 最小的 $s$ 条卖出记录按照 $p_i$ 降序输出。将所有 $p_i$ 最大的 $s$ 条买入记录按照 $p_i$ 降序输出。

**笔者提醒：买入卖出记录可能不足 $s$ 条，这时将所有的记录按照 $p_i$ 降序输出。**

**数据范围：$1\leqslant n\leqslant1000,1\leqslant s\leqslant 50,0\leqslant p_i\leqslant 10^5,1\leqslant q_i\leqslant 10^4$。**
## Solution
$n$ 很小，所以我们考虑直接 $\mathcal{O}(n^2)$ 遍历，看前面是否有 $p_i$ 和当前的 $p_i$ 相等，有的话直接合并，否则新开一个存储。然后卖出记录按照从小到大排序后倒序输出，买入记录按照从大到小排序后正序输出即可。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

int n, s, socnt, bucnt, visso[100007], visbu[100007];
struct node {
	int x, y;
	bool operator < (const node& cjy) const {return x < cjy.x;}
}so[1007];
struct node2 {
	int x, y;
	bool operator < (const node2& cjy) const {return x > cjy.x;}
}bu[1007];

int main() {
	scanf("%d%d", &n, &s);
	for(int i = 1; i <= n; ++i) {
		char opt[2]; int p, q;
		scanf("%s%d%d", opt, &p, &q);
		if(opt[0] == 'B') {
			if(visbu[p]) {
				for(int j = 1; j <= bucnt; ++j)
					if(bu[j].x == p) {
						bu[j].y += q;
						break;
					}
			}
			else {
				bu[++bucnt] = (node2){p, q};
				visbu[p] = 1;
			}
		} else {
			if(visso[p]) {
				for(int j = 1; j <= socnt; ++j)
					if(so[j].x == p) {
						so[j].y += q;
						break;
					}
			}
			else {
				so[++socnt] = (node){p, q};
				visso[p] = 1;
			}
		}
	}
	sort(so + 1, so + socnt + 1);
	sort(bu + 1, bu + bucnt + 1);
	for(int i = min(socnt, s); i >= 1; --i)
		printf("S %d %d\n", so[i].x, so[i].y);
	for(int i = 1; i <= min(bucnt, s); ++i)
		printf("B %d %d\n", bu[i].x, bu[i].y);
	return 0;
}

```

---

## 作者：codeLJH114514 (赞：0)

[$\fcolorbox{black}{#4169E1}{\color{white}{\texttt{返回题目}}}$](https://www.luogu.com.cn/problem/CF572B)

# 题目描述

给你 $n$ 条买入和卖出的记录，让你输出单价最大或最小的 $s$ 条记录，再按照单价**降序**输出。

# 解法描述

这道题目就用 `STL map` 乱杀。

他说合并，我们就用 `map` 分别记录买入和卖出的记录，来一个记录就合并上。

也就是用两个 `map` 分别记录剩下的所有买入和卖出的记录。

比如：`sel[20] = 10` 就表示单价为 $20$ 的产品一共卖出去了 $10$ 件，以此类推。

记录完了之后就把单价最小/最大的记录取出来放在 `STL vector` 中，然后再排序就可以了。

# 注意事项

- 因为买入记录要求找出最大的 $s$ 条记录所以可以直接在 `map` 里就把排序规则改成降序。
- 因为可能记录不足 $s$ 项，所以取的时候需要判断。

# 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, s;
map<int, int> sel;
map<int, int, greater<int>> buy; // greater<int> 表示排序方式，也就是降序。
class element{
    public:
        int p, q;
        element(): p(0), q(0) {}
        element(int _p, int _q): p(_p), q(_q) {}
} ;
vector<element> sela;
vector<element> buya;
int main() {
    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        string s;
        int p, q;
        cin >> s >> p >> q;
        if (s == "B")
            buy[p] += q;
        if (s == "S")
            sel[p] += q;
    }
    int i = 0;
    auto it = sel.begin();
    while (it != sel.end() and i < s) { // 因为可能记录不足 s 项，所以需要判断。
        sela.emplace_back(it->first, it->second); // 存入 vector 中。
        it = next(it, 1);
        i += 1;
    }
    i = 0;
    auto jt = buy.begin();
    while (jt != buy.end() and i < s) {
        buya.emplace_back(jt->first, jt->second); // 同理
        jt = next(jt, 1);
        i += 1;
    }
    sort(sela.begin(), sela.end(), [] (element& a, element& b) {return a.p > b.p; });
    sort(buya.begin(), buya.end(), [] (element& a, element& b) {return a.p > b.p; }); // 取出后排序
    for (auto i : sela)
        cout << "S " << i.p << " " << i.q << "\n";
    for (auto i : buya)
        cout << "B " << i.p << " " << i.q << "\n"; // 最后输出。（记得先输出卖再输出买哦！）
    return 0;
}
```

拒绝抄袭题解，共创美好洛谷。

---

