# Inna and Pink Pony

## 题目描述

Dima and Inna are doing so great! At the moment, Inna is sitting on the magic lawn playing with a pink pony. Dima wanted to play too. He brought an $ n×m $ chessboard, a very tasty candy and two numbers $ a $ and $ b $ .

Dima put the chessboard in front of Inna and placed the candy in position $ (i,j) $ on the board. The boy said he would give the candy if it reaches one of the corner cells of the board. He's got one more condition. There can only be actions of the following types:

- move the candy from position $ (x,y) $ on the board to position $ (x-a,y-b) $ ;
- move the candy from position $ (x,y) $ on the board to position $ (x+a,y-b) $ ;
- move the candy from position $ (x,y) $ on the board to position $ (x-a,y+b) $ ;
- move the candy from position $ (x,y) $ on the board to position $ (x+a,y+b) $ .

Naturally, Dima doesn't allow to move the candy beyond the chessboard borders.

Inna and the pony started shifting the candy around the board. They wonder what is the minimum number of allowed actions that they need to perform to move the candy from the initial position $ (i,j) $ to one of the chessboard corners. Help them cope with the task!

## 说明/提示

Note to sample 1:

Inna and the pony can move the candy to position $ (1+2,3+2)=(3,5) $ , from there they can move it to positions $ (3-2,5+2)=(1,7) $ and $ (3+2,5+2)=(5,7) $ . These positions correspond to the corner squares of the chess board. Thus, the answer to the test sample equals two.

## 样例 #1

### 输入

```
5 7 1 3 2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 5 2 3 1 1
```

### 输出

```
Poor Inna and pony!
```

# 题解

## 作者：CobaltChloride (赞：4)

```
#include<沙发>
#include<讲解尽在代码中>
#include<走过路过点个赞>
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,i,j;//题目要求
bool pd[5];//左上角为(1,1);pd[1]判断左上角, pd[2]判断右上角, pd[3]判断左下角, pd[4]判断右下角
int aa[5],bb[5],ab[5]={1000001,1000001,1000001,1000001,1000001};//次数 
int ans=1000001;
int main(){
    cin>>n>>m>>i>>j>>a>>b;
    if(n==i&&1==j||n==i&&m==j||1==i&&1==j||1==i&&m==j){
    	cout<<0;
        return 0;
	}//若已达成目标 
    if(n<=a||m<=b){
        cout<<"Poor Inna and pony!";
        return 0;
    }//若棋盘不够大移不了 
    if((i-1)%a==0&&(j-1)%b==0) pd[1]=1,aa[1]=(i-1)/a,bb[1]=(j-1)/b;
    if((n-i)%a==0&&(j-1)%b==0) pd[2]=1,aa[2]=(n-i)/a,bb[2]=(j-1)/b;
    if((i-1)%a==0&&(m-j)%b==0) pd[3]=1,aa[3]=(i-1)/a,bb[3]=(m-j)/b;
    if((n-i)%a==0&&(m-j)%b==0) pd[4]=1,aa[4]=(n-i)/a,bb[4]=(m-j)/b;
    //初始判断
    for(int k=1;k<=4;k++) if(pd[k]) if((aa[k]+bb[k])%2==0)/*否则解为小数*/ ab[k]=max(aa[k],bb[k]);//一次移动2段(a,b),至少移动max(aa[k],bb[k])次 
    for(int k=1;k<=4;k++) ans=ans<ab[k]?ans:ab[k];//比较次数
    if(ans<1000001) cout<<ans;
    else cout<<"Poor Inna and pony!";
    return 0; 
}
```

---

## 作者：Fuxh_18 (赞：2)

[题目](https://www.luogu.com.cn/problem/CF374A)和[原题](https://codeforces.com/problemset/problem/374/A)。

## 题目大意
在一个 $n \times m$ 的棋盘中，把位于 $(i,j)$ 的糖果移到角落最少要几步。每步详情如下：

1. 移到 $(i+a,j+b)$。
2. 移到 $(i+a,j-b)$。
3. 移到 $(i-a,j+b)$。
4. 移到 $(i-a,j-b)$。
## 思路
最开始，有两个特判：
1. 最开始在角落上，输出 ```0```。
2. 若不在角落上，且 $a \ge n $ 或 $b \ge m$，无解，输出 ```Poor Inna and pony!```。

之后求出 $(i,j)$ 与四个角的横坐标的差与纵坐标的差，为了看着简洁，设 $x=(i,j)$ 到角落横坐标的差，$y=(i,j)$ 到角落纵坐标的差。 判断能到的标准如下：
1. $x \bmod a = 0$，$y \bmod b = 0$。
2. $\frac{x}{a} \bmod 2 = \frac{y}{b} \bmod 2$。

能到的话，答案为 $\max(\frac{x}{a},\frac{y}{b})$，并标记能到，最后判断最小。
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,a,b,ans=INT_MAX,f=0;
void zz(int x,int y){ //判断能否到达的函数
	if(x%a==0&&y%b==0&&x/a%2==y/b%2){
		ans=min(ans,max(x/a,y/b));
		f=1; //标记能到 
	}
}
int main(){
	cin>>n>>m>>i>>j>>a>>b;
	if((i==n&&j==m)||(i==n&&j==1)||(i==1&&j==m)||(i==1&&j==1)){ //特判是否已经在角落 
		cout<<0;
		return 0;
	} 
	if(a>=n||b>=m){ //特判是否会走出界 
		cout<<"Poor Inna and pony!";
		return 0;
	}
	zz(i-1,j-1);
	zz(i-1,m-j);
	zz(n-i,j-1);
	zz(n-i,m-j);
	if(f==0){ //如果不能到 
		cout<<"Poor Inna and pony!";
	}
	else{
		cout<<ans;
	}
	return 0;
}
```

---

## 作者：xiaorui2007 (赞：1)

## 思路
首先，先讨论从 $(x_1,y_1)$ 到 $(x_2,y_2)$ 的答案。  
1. 若 $|x_1-x_2|\bmod a\ne0$ 或 $|y_1-y_2|\bmod b\ne0$ 时，显然无法成功。
2. 否则，设 $t_1=\dfrac{|x_1-x_2|}{a},t_2=\dfrac{|y_1-y_2|}{b}$，若 $t_1\bmod2=t_2\bmod2$，存在方案，答案为 $\max{(t_1,t_2)}$，否则无法成功。

然后算一下到四个角的答案取最小值即可。

除此之外，还有特判。  
1. 走不了。  
在 $n<=a$ 或 $m<=b$ 时绝对走不了。  
如： 
>37.in: ```1 5 1 3 1 1```  
37.out: ```Poor Inna and pony!```
2. 出生在角落，答案为 $0$。

综合以上思路和特判，得出代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,a,b,t1,t2,ans=0x3f3f3f3f;

void f(int x,int y)//横向平移x格，纵向平移y格，即从(0,0)移至(x,y) 
{
	if(((x%a)==0)&&((y%b)==0))
	{
		t1=x/a;
		t2=y/b;
		if((t1+t2)&1^1)//判断t1%2==t2%2 
			ans=min(ans,max(t1,t2));
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin>>n>>m>>i>>j>>a>>b;
	f(i-1,j-1);//四个角讨论 
	f(i-1,m-j);
	f(n-i,j-1);
	f(n-i,m-j);
	if(ans==0x3f3f3f3f)
		cout<<"Poor Inna and pony!"<<endl;//在允许超出格子范围的情况下无解 
	else
		if(ans&&((n<=a)||(m<=b)))//ans=0时在角落，答案为0；ans>0，判断是否出界，出界是无解，没出是ans 
			cout<<"Poor Inna and pony!"<<endl;
		else
			cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ZJle (赞：0)

### CF374A Inna and Pink Pony
CF 评分：$2000$

这道题上来就很一眼，我们不难发现， $a$ 和 $b$ 分别只与 $x$ 与 $y$ 有关。

1. 将糖果的位置 $(x,y)$ 移动到位置 $(x-a,y-b)$ ；

2. 将糖果的位置 $(x,y)$ 移动到位置 $(x+a,y-b)$ ；

3. 将糖果的位置 $(x,y)$ 移动到位置 $(x-a,y+b)$ ；

4. 将糖果的位置 $(x,y)$ 移动到位置 $(x+a,y+b)$ 。

由此，我们只需要枚举这个点到平面的四个角上的曼哈顿距离，对于所有的距离 $d1 \bmod a=0$ 并且 $d2 \bmod b=0$ ，进行枚举即可，同时需要判断 $d1$ 和 $d2$ 的奇偶性，只有相同奇偶性才可以作为答案放入 $ans$ 。

同时应当特判已经在矩形之外的情形。

``` cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T;
void file(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    
}
const int inf=1e18;
pair<int,int>er[5];
void solve(){
    int ans=inf;
    int n,m,x1,y1,a,b;
    cin>>m>>n>>x1>>y1>>a>>b;
    if(x1>m||y1>n){
        cout << "Poor Inna and pony!";
        exit(0);
    }
    er[0].first=abs(1-x1);
    er[0].second=abs(1-y1);
    er[1].first=abs(m-x1);
    er[1].second=abs(1-y1);
    er[2].first=abs(x1-1);
    er[2].second=abs(y1-n);
    er[3].first=abs(m-x1);
    er[3].second=abs(n-y1);
    for(int i=0;i<4;i++){
        if(er[i].first%a==0&&er[i].second%b==0){
            int ans1=er[i].first/a;
            int ans2=er[i].second/b;
            if((ans1&1)==(ans2&1)){
                ans=min(ans,max(ans1,ans2));
                // cout<<ans<<' '<<er[i].first<<' '<<er[i].second<<endl;
            }
        }
    }
    if(ans==inf){
        cout << "Poor Inna and pony!";
        exit(0);
    }
    cout << ans;
}
signed main(){
    file();
    // cin>>T;?
    T=1;
    while(T--) solve();
}
```

~~勿鹤，有防作弊。~~

---

## 作者：Tjl0427 (赞：0)

# CF374A Inna and Pink Pony
## 思路以代码：
分类讨论从 $( x_1 , y_1 )$ 到 $( x_2 , y_2 )$ 的答案：

不妨设：$p , q$ 分别为 $| x_1 - x_2 |$ 和 $| y_1 - y_2 |$。  
再设：$s_1 , s_2$ 分别为 $\frac{p}{a}$ 和 $\frac{q}{b}$。
1. 如果在角落，就直接输出 $0$ 就好了。
2. 走不了了，输出 `Poor Inna and pony!`。
3. 当 $p \bmod a \ne 0$ 或者 $q \bmod b \ne 0$ 时，不成功。
4. 否则，若 $s_1 \bmod 2 = s_2 \bmod 2$，有方案且答案为 $\max ( s_1 , s_2 )$，否则不能成功。

取到四个角的答案的最小值就可以了。  
**其中 $1,2$ 是特判。**

结合过程，得出代码：
```c
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
int n,m,i,j,a,b,s1,s2,ans=inf;
void f(int x,int y){
	if(((x%a)==0)&&((y%b)==0)){
		s1=x/a,s2=y/b;
		if((s1+s2)&1^1){
			ans=min(ans,max(s1,s2));
		}
	}
}
int main(){
	cin>>n>>m>>i>>j>>a>>b;
	f(i-1,j-1);
	f(i-1,m-j);
	f(n-i,j-1);
	f(n-i,m-j);
	if(ans==0x3f3f3f3f){
		cout<<"Poor Inna and pony!"<<"\n";
    }
	else{
		if(ans&&((n<=a)||(m<=b))){
			cout<<"Poor Inna and pony!\n";
		}
		else{
			cout<<ans<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
细节非常多的一道模拟和思维题。
## 分析。
显然如果本来初始位置就在角上，那么显然直接输出 $0$ 即可。显然我们再判断一下无解的情况，剩下的直接模拟即可。

先放结论：如果初始位置不在角上时，这个初始坐标必须与某一个角的垂直距离为 $k_1\times a$ 同时水平距离为 $k_2\times b$。同时 $k_1$ 和 $k_2$ 的奇偶性相同。

首先其中的 $k_1$ 与 $k_2$ 为常数，且均为正整数。这个限制要求很显然，因为网格相当于一个平面直角坐标系。

我们重点解释为什么必须奇偶性相同，因为我们必须移动到这个点，所以既是我们现在到了这个目标点的这一行或者这一列时，我们还要在进行一些重复操作使得其直接平移到目标点。所以我们至少移动的此时为 $k_1$ 和 $k_2$ 中的较大数次。这个值显然可能比 $k_1$ 和 $k_2$ 中的某一个大，那么我们就可以拆开考虑。

那么我们这个点必须在某一方向上，先先左移动再向右移动，或者先向上移动后向下移动。这个过程就是消除掉多余的那一点操作此时，所以需要的操作次数为：这两个常数之间的较大值减去较小值，即它们之间的差值。同时，每次操作必须包含两次移动，所以它们奇偶性应该相同。证明完毕。

然后特判一些不要在上面的过程中跑出去就行了。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int n,m,x,y,a,b;
int ans=0x3f3f3f3f;
int main(){
	cin>>n>>m>>x>>y>>a>>b;
    if(((x-1)%a!=0)&&((n-x)%a!=0)){
    	cout<<"Poor Inna and pony!\n";
        return 0;
    }
	if((y-1)%b!=0&&(m-y)%b!=0){
        cout<<"Poor Inna and pony!\n";
        return 0;
    }//无解情况的判断。 
    if((x==1||(x==n))&&(y==1||(y == m))){
        cout<<"0\n";
        return 0;
    }//在角上情况的判断。 
    if((((x+a<=n)||(x-a>0))&&((y+b<=m)||(y-b>0)))&&(((x-1)%a==0)&&((y-1)%b==0))&&((((x-1)/a)&1)==(((y-1)/b)&1))){
        ans=min(ans,max((x-1)/a,(y-1)/b));
    }
    if((((x+a<=n)||(x-a>0))&&((y+b<=m)||(y-b>0)))&&(((x-1)%a==0)&&((m-y)%b==0))&&((((x-1)/a)&1)==(((m-y)/b)&1))){
        ans=min(ans,max((x-1)/a,(m-y)/b));
    }
    if((((x+a<=n)||(x-a>0))&&((y+b<=m)||(y-b>0)))&&(((n-x)%a==0)&&((y-1)%b==0))&&((((n-x)/a)&1)==(((y-1)/b)&1))){
        ans=min(ans,max((n-x)/a,(y-1)/b));
    }
    if((((x+a<=n)||(x-a>0))&&((y+b<=m)||(y-b>0)))&&(((n-x)%a==0)&&((m-y)%b==0))&&((((n-x)/a)&1)==(((m-y)/b)&1))){
        ans=min(ans,max((n-x)/a,(m-y)/b));
    }
    if(ans==0x3f3f3f3f){
	    cout<<"Poor Inna and pony!\n";
	}
    else cout<<ans<<"\n";
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：nxd_oxm (赞：0)

# 题意
题目说有个糖果，在一个 $n \times m$ 的棋盘上。我们要把糖果移到棋盘的四个角去，也就是 $(1,m),(1,n),(1,1),(n,m)$。

我们可以有四种方式移动糖果。

当糖果在 $(i,j)$ 时，

- 移动到 $(i+a,j+b)$。

- 移动到 $(i-a,j+b)$。

- 移动到 $(i+a,j-b)$。

- 移动到 $(i-a,j-b)$。

求最小的移动次数。

# 思路
模拟。

我们先来讨论到 $(n,m)$ 的情况。

首先如果要到达终点，首先要保证 $n-i$ 和 $m-j$ 要是分别被 $a$ 和 $b$ 整除。因为不被整除的话，$i$ 不管怎么加减 $a$ 都到不了 $n$，$j$ 也是。

其次，$(n-i) \div a$ 和 $(m-j) \div b$ 的奇偶性要相同。如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/u9obrybd.png)

若不同，$a$ 和 $b$ 不能同时等于终点 $(n,m)$。

再分别讨论其他四种就可以啦。

计算的话，选择 $(n-i) \div a$ 和 $(m-j) \div b$ 中较大的一个。因为如果选小的，大的那个会完成不了目标。

### 易错

题目有个条件是说糖果必须在棋盘内，所以要特判。

因为我们说了，$(n-i) \div a$ 和 $(m-j) \div b$ 是有大有小，所以小的那个要等大的那个正好走到，所以需要反复加减。

那这是需要空间的。所以只要 $i \sim i+a$ 或 $i-a \sim i$ 的空间。判断这两个区间在不在 $1 \sim n$ 内，有一个满足即可，$j$ 同理。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,m,a,b,i,j;
	cin>>n>>m>>i>>j>>a>>b;
	long long minn=INT_MAX/2;
//	minn(min,(n-i)%a<<" "<<(m-j)%b<<" "<<(n-i)/a<<" "<<(m-j)/b);
	if(abs(n-i)%a==0&&abs(m-j)%b==0&&abs(n-i)/a%2==abs(m-j)/b%2&&(i-a>=1||i+a<=n||(i==n&&j==m))&&(j-b>=1||j+b<=m||(i==n&&j==m))){
		if(abs(n-i)/a>abs(m-j)/b){
			minn=min(minn,abs(n-i)/a);
		}else{
			minn=min(minn,abs(m-j)/b);
		}
//		cout<<1;
	}
	if(abs(1-i)%a==0&&abs(1-j)%b==0&&abs(1-i)/a%2==abs(1-j)/b%2&&(i-a>=1||i+a<=n||(i==1&&j==1))&&(j-b>=1||j+b<=m||(i==1&&j==1))){
		if(abs(1-i)/a>abs(1-j)/b){
			minn=min(minn,abs(1-i)/a);
		}else{
			minn=min(minn,abs(1-j)/b);
		}
//		cout<<2;
	}
	if(abs(1-i)%a==0&&abs(m-j)%b==0&&abs(1-i)/a%2==abs(m-j)/b%2&&(i-a>=1||i+a<=n||(i==1&&j==m))&&(j-b>=1||j+b<=m||(i==1&&j==m))){
		if(abs(1-i)/a>abs(m-j)/b){
			minn=min(minn,abs(1-i)/a);
		}else{
			minn=min(minn,abs(m-j)/b);
		}
//		cout<<3;
	}
	if(abs(n-i)%a==0&&abs(1-j)%b==0&&abs(n-i)/a%2==abs(1-j)/b%2&&(i-a>=1||i+a<=n||(i==n&&j==1))&&(j-b>=1||j+b<=m||(i==n&&j==1))){
		if(abs(n-i)/a>abs(1-j)/b){
			minn=min(minn,abs(n-i)/a);
		}else{
			minn=min(minn,abs(1-j)/b);
		}
//		cout<<4;
	}
	if(minn==INT_MAX/2){
		cout<<"Poor Inna and pony!";
	}else{
		cout<<minn;
	}
	return 0;
}
```

---

