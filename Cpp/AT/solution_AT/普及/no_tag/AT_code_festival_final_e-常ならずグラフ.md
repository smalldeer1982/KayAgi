# 常ならずグラフ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2014-final/tasks/code_festival_final_e

Tさんは，諸行無常をモットーにいろいろなことに挑戦しています． Tさんはあるコンテストに長期的に参加していますが，そのコンテストにはレーティング機能があり，一度参加する毎にレーティングが変動します．それらの変動はグラフにまとめられています．

今，Tさんは彼のレーティング変動がプロットされたグラフを眺めています．彼はふと，グラフから一部の点を取り除いてそれらを結び，常に上下に変動しているような折れ線グラフ，名付けて「常ならずグラフ」を作りたくなりました． さらに，グラフに含まれる点の数が最も多いものに興味があります．

さて，あなたはTさんのために，彼のレーティング変動がプロットされたグラフから作ることのできる「常ならずグラフ」の中での最大の点の数を求めてあげることにしました．

あなたには，Tさんのあるコンテスト参加後でのレーティングが，$ N $ 個，時系列で与えられます．その中からいくつかの点を取り除き「常ならずグラフ」を作るとき，ありうる点の最大数を求めなさい．常ならずグラフが作れないときは $ 0 $ を出力しなさい．

あるグラフ $ X=\{x_1,x_2,x_3,..x_n\} $ が「常ならずグラフ」であるとは， $ |X| $ が $ 3 $ 以上かつ， $ x_1＜x_2＞x_3＜x_4＞... $ もしくは $ x_1＞x_2＜x_3＞x_4\ <\ ...$ が成り立つことを意味します．
つまり，含まれる頂点数が $ 3 $ 未満のとき，「常ならずグラフ」ではありません．

## 样例 #1

### 输入

```
4
1 2 5 1```

### 输出

```
3```

## 样例 #2

### 输入

```
5
1 2 3 4 5```

### 输出

```
0```

# 题解

## 作者：A_grasser (赞：4)

## 题意简化

查找一个最大波浪长度。

## 需要注意的地方

1. 日本 AT 的题目输出都要记得换行。

## 解法分析

### 一级解法

直接暴力模拟做。

思路：从第三个开始挨个枚举，判断它与前面两项是否成为一个波浪，如果不成，那么就不要中间那个，把中间替换成最左边的那一个，答案减一。可能有点难以理解，最好结合配图代码理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/wcq56hck.png)

时间复杂度只有 $O(n)$ 级别，完全能过。


```cpp
//已通过 
#include<bits/stdc++.h>
//万能头文件 
using namespace std;
int n,ans;
int a[3005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	ans=n;//初始化答案 
	for(int i=3;i<=n;i++){//从第3个开始枚举
		if(!((a[i-1]>a[i] && a[i-1]>a[i-2]) || (a[i-1]<a[i] && a[i-1]<a[i-2]))){//不符合波浪 
			ans--;//答案更新 
			a[i-1]=a[i-2];//去掉中间不恰当的值 
		}
	}
	if(ans<3) cout<<"0\n";//按题意，答案小于3要输出0 
	else cout<<ans<<endl;
	return 0;
}
```


### 二级解法

这道题也可以用 dp 来解决，但是不建议这样做。毕竟，比赛是靠正确拿分，不是要你炫技，暴力简单，不易错，还能过，那就首选暴力，所以在此并不赘述。

最后说一句，我比较推荐万能头文件，这样可以省去很多不必要的麻烦。

## 完整代码

```cpp
//已通过 
#include<bits/stdc++.h>
//万能头文件 
using namespace std;
int n,ans;
int a[3005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	ans=n;//初始化答案 
	for(int i=3;i<=n;i++){
		if(!((a[i-1]>a[i] && a[i-1]>a[i-2]) || (a[i-1]<a[i] && a[i-1]<a[i-2]))){//不符合波浪 
			ans--;//答案更新 
			a[i-1]=a[i-2];//去掉中间不恰当的值 
		}
	}
	if(ans<3) cout<<"0\n";//按题意，答案小于3要输出0 
	else cout<<ans<<endl;
	return 0;
}
```

---

## 作者：andyli (赞：1)

与 LIS 类似，考虑 dp。设 $dp_{i, 0/1}$ 表示以 $a_i$ 为结尾接下来应该加入比 $a_i$ 小/大的数的波浪形序列长度。

转移：
$$ dp_{i,0}= \max\limits_{j\in[0,i), a_j<a_i} \{dp_{j,1}\}+1 $$
$$ dp_{i,1}= \max\limits_{j\in[0,i), a_j>a_i} \{dp_{j,0}\}+1 $$


边界 $dp_{i,0}=dp_{i,1}=1$，答案为 $\max\{dp_{n,0}, dp_{n,1}\}$。注意如果答案不满 $3$ 则输出 $0$。
```python
def main():
    n, *a = map(int, open(0).read().split())
    dp = [[1, 1] for _ in range(n)]
    for i in range(n):
        for j in range(i):
            if a[j] < a[i]:
                dp[i][0] = max(dp[i][0], dp[j][1] + 1)
            if a[j] > a[i]:
                dp[i][1] = max(dp[i][1], dp[j][0] + 1)
    ans = max(dp[-1][0], dp[-1][1])
    if ans < 3:
        ans = 0
    print(ans)

main()
```

---

## 作者：awdereye (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_code_festival_final_e)
### 输出描述
本题要求输出长度为 $N$ 的成绩中删除一些数后波浪的长度（长度 $\le 3$ 的话就输出 `0`）。

- 注：本题对于波浪的要求为 $R _ i$ 比它两边的数都小或大。

### 解题思路
本题需要模拟波浪长度，同时用变量储存长度，于是就有了两种情况：

- 满足波浪条件，不作处理。
- 不满足删除这个成绩。

本题所使用的删除操作是用 `swap` 函数实现，可以理解为把要删除的数转移到一个不会再次处理的地方，同时让它的前一个 $R _ {i-1}$ 来替换它的位置。

- 前置知识： `swap` 函数，写作 `swap(a,b)` 表示把 $a$ 和 $b$ 的位置互换。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,node[11451],cnt=0;
void qwq(int begin){
		for(int i=begin-1;i>=1;i--){
			swap(node[i+1],node[i]);//互换函数
		}
}
bool find(int ii){
		return (bool)((node[ii]>node[ii-1]&&node[ii]>node[ii+1])||(node[ii]<node[ii-1]&&node[ii]<node[ii+1]));//波浪条件
}
int main(){
		cin>>n;	
		for(int i=1;i<=n;i++){
			cin>>node[i];
		}
		cnt=n;//一开始全是波浪
		for(int i=2;i<=n-1;i++){
			if(find(i)){
				continue;//是波浪不做处理
			}
			cnt--;//不是删除，-1
			qwq(i);//互换
		}
		if(cnt<3){
			cout<<0<<endl;//特判
			return 0;
		}
		cout<<cnt<<endl;
		return 0;
}
```

---

## 作者：Lovely_Elaina (赞：0)

一道很有意思的水题。

当前处理区间，如果中值不是最值，替换成左值就行了。

因为中值不是最值，那么左值和右值肯定是最值。

并且当前处理区间的中值是下次处理区间的左值，当前处理区间的右值是下次处理区间的中值。

一模拟样例就懂。

暴力过得了，记得输出要换行。

```cpp
#include <bits/stdc++.h>
// #include <iostream>
#define endl '\n'
// #define int long long
using namespace std;

int n,x,y,z;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    
    cin >> n;
    int ans = n;
    
    cin >> y >> z;
    for(int i = 3; i <= n; i++){
        x = y,y = z;
        cin >> z;
        
        // 不是最大也不是最小
        if(!((y > z && y > x) || (y < z && y < x))){
            y = x;
            ans--;
        }
    }
    
    if(ans < 3) cout << 0 << endl;
    else cout << ans << endl;
    return 0;
}
```

---

## 作者：SunnyLi (赞：0)

## 思路

我们直接从开始暴力枚举，每三个算一次。

如果这三个不构成波浪，那么我们就需要将答案减一，即剔除掉这个数。这个时候，我们就需要把这前一个数给赋值到这个数，这样的话就可以与剔除的前一个数进行比较。

## AC 代码

（人生苦短，我用 Python）

```python
n = int(input())
a = list(map(int,input().split(" ")))
ans = n
for i in range(2,n):
    if ((a[i-1]>a[i] and a[i-1]>a[i-2]) or (a[i-1]<a[i] and a[i-1]<a[i-2]))==False:
        ans -= 1
        a[i-1]=a[i-2]
if ans<3:
    print("0")
else:
    print(ans)
```

---

## 作者：hmh100211 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_code_festival_final_e)

## 题意分析：

给定一个长度为 $n$ 的序列 $r$，问最多保留几个元素，才能使序列 $r$ 变成“**波浪形**”。

波浪形的定义：

- 元素数量至少为 $3$。

- 每相邻三项的中间一项为**最大者**或**最小者**（**不能相等**）。

数据范围为

$ 1 \leq n \leq 3000 $

$ -10^5 \leq  r_i \leq 10^5 $

数据范围很小，正常开 `int` 即可。

## 思路：

读完题很容易想到直接模拟，而且数据范围很小，不会超，按题意模拟即可（~~好水的黄题~~）。

# AC code：

``` c
#include<bits/stdc++.h> 

using namespace std;

int r[114514],n,retain; //定义数组r,序列长度n,需要保留的元素个数retain

bool not_wave(int a,int b,int c) //判断是否是波浪形
{
	if((a>b&&b<c)||(a<b&&b>c)) return 0; //不是，返回0
	else return 1; //是，返回1
}

int main()
{
	
	cin>>n; //输入序列长度
	retain=n; //初始化需要保留的元素个数
    
	for(int i=0;i<n;i++) cin>>r[i]; //输入序列r
    
	for(int i=2;i<n;i++) //遍历序列r，注意要留出两个元素的位置
	{
		if(not_wave(r[i-2],r[i-1],r[i])) //如果不是“波浪形”
		{
			retain--; //需要保留的元素个数-1
			r[i-1]=r[i-2]; //更新序列r
		}
	}
	if(retain<3) retain=0; //如果需要保留的元素个数小于3，则不符题意，改为0
    
	cout<<retain<<endl; //输出需要保留的元素个数（要加换行！！！AT的题要加换行才能AC！本蒟蒻因为这个WA了三遍）
	
	return 0; //华丽的结尾
}
```

# [AC](https://www.luogu.com.cn/record/114775168)

---

## 作者：Ja50nY0un9_as_AgNO3 (赞：0)

警示一下读者，本题翻译有误，正确翻译是求删去一些点后最大的波浪形序列长度。

那么，既然所有点都要满足它与它左右的元素大小关系不同，这里就可以用一重循环解决。

我们维护上一个我们挑选出的数的位置，与我们现在枚举到的数和它的下一个数相比较，如果其大小关系不同，我们就可以确定它们组成了一个“波浪”。

注意，我们要从第 $2$ 个数枚举到第 $n-1$ 个（防止数组越界），因为由我们的构造方法，原数列首尾的数一定在最终数列中。

注意，根据题目定义，相邻元素是不能相等的，否则会 WA on #15。

剩下的细节见代码注释。

```cpp
# include <iostream>
using namespace std;
long long a[3001];
//下文的偷懒方法可能会爆 int
//不开 long long 可能 WA on #5

int main(){
    int n;
    cin >> n;
    for (int i=1; i <= n; i++)
        cin >> a[i];
    int ans=n, cur=1;
    //因为第一个元素肯定在序列中，cur 的初始值为 1
    for (int i = 2; i < n; i++){
        if ((a[i] - a[cur]) * (a[i+1] - a[i]) >= 0){
            //偷懒，如果大小关系相同则结果大于 0，反之则小于 0。
            ans--;
        }
        else {
            //cur 更新为波浪序列中新加入的的元素
            cur = i;
        }
    }
    if (ans <= 2){
        //根据题目定义，波浪序列长度不小于 3
        ans = 0;
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_code_festival_final_e)    
水黄。    
这道题我们要先理解什么叫做波浪。   
这里的“波浪”实际上指的是对于 $a_i(i>1)$ 来说，$a_{i-1}$ 和 $a_{i+1}$ 与 $a_i$ 的关系相反（可以相等），这里的关系指 $<$ 和 $>$。我们下文称这样的元素叫“波浪元素”。    
对于不是“波浪元素”的数字，不能满足任何波浪元素的条件，否则我们就应该删掉。   
按照这样的思路，我们直接模拟即可。   
CODE：   
```
#include <iostream>
using namespace std;
int n,a[3030],ans;
int main(void){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	ans=n;//往下递减
	for(int i=2;i<n;i++){
		if(a[i-2]<=a[i-1]&&a[i-1]<=a[i]){//判断是否有满足任一条件但不是“波浪元素”的元素
			ans--;
			a[i-1]=a[i-2];
		}else if(a[i-2]>=a[i-1]&&a[i-1]>=a[i]){
			ans--;
			a[i-1]=a[i-2];
		}
	} 
	if(ans<3){//肯定无解的情况
		ans=0;
	}
	cout<<ans<<endl;
}
```


---

## 作者：Y_J_Y (赞：0)

没错,又是我
这回这道题的主要意思是:一个人有n个成绩
然后问你删掉几个能使这些成绩成波浪形
如果不能,输出0

首先,我们先读入这些东西
然后就是模拟了

对于每三个数据,要么保证(1>2<3)
要么保证(1<2>3)

而且这回数据量也不是很大
所以只要模拟循环判断

总的来说难度不是很大
下面的注释我也会提供一些助于理解
```
#include <bits/stdc++.h>
using namespace std;
int cj[12345678];//用于记录成绩
int main() {
	int n,m,a,ans=0;
	cin>>n;
	ans=n;
	for(int i=0;i<n;i++) {
		cin>>cj[i];//输入
	}
	for(int i=2;i<n;i++) {//下面是最重要的模拟了
		if(cj[i-2]<=cj[i-1]&&cj[i-1]<=cj[i]) {//就是上面说的不满足的情况
			ans--;
			cj[i-1]=cj[i-2];
		}
		else if(cj[i-2]>=cj[i-1]&&cj[i-1]>=cj[i]) {//同理
			ans--;
			cj[i-1]=cj[i-2];
		}
	}
	if(ans<=2) {//没办法输出0
		cout<<"0"<<endl;
		return 0;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

